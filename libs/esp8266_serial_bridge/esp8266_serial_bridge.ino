// ESP8266 WiFi + Serial bridge for Arduino projects.
// - Keeps a setup AP enabled by default
// - Serves a status/config page at http://esp8266.local/
// - Forwards arbitrary serial payloads with /serial?data=...
// - Appends '#' to each forwarded serial message by default

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "Your-2.4G-WiFi"
#define STAPSK  "ChangeMe123"
#endif

const char* kDefaultSsid = STASSID;
const char* kDefaultPassword = STAPSK;
const char* kSetupApSsid = "KE3066-Setup";
const char* kSetupApPassword = "12345678";
const char* kMdnsName = "esp8266";

const uint32_t kConnectTimeoutMs = 15000;
const int kEepromSize = 192;
const int kMaxCredentialLength = 31;
const int kSerialLogMaxChars = 1600;

struct WifiConfigData {
  char marker[4];
  char ssid[32];
  char password[32];
  uint8_t setup_ap_enabled;
  uint8_t append_hash;
};

WiFiServer server(80);

String currentSsid;
String currentPassword;
bool setupApEnabled = true;
bool appendHash = true;
bool staConnected = false;
bool mdnsStarted = false;
bool shouldPrintSummary = false;
String serialLog;
String currentSerialLine;

String urlDecode(const String& value) {
  String decoded;
  decoded.reserve(value.length());
  for (unsigned int i = 0; i < value.length(); ++i) {
    char c = value[i];
    if (c == '+') {
      decoded += ' ';
      continue;
    }
    if (c == '%' && i + 2 < value.length()) {
      char hi = value[i + 1];
      char lo = value[i + 2];
      int hiVal = isDigit(hi) ? hi - '0' : toupper(hi) - 'A' + 10;
      int loVal = isDigit(lo) ? lo - '0' : toupper(lo) - 'A' + 10;
      decoded += char((hiVal << 4) | loVal);
      i += 2;
      continue;
    }
    decoded += c;
  }
  return decoded;
}

String htmlEscape(const String& value) {
  String escaped;
  escaped.reserve(value.length());
  for (unsigned int i = 0; i < value.length(); ++i) {
    char c = value[i];
    if (c == '&') escaped += F("&amp;");
    else if (c == '<') escaped += F("&lt;");
    else if (c == '>') escaped += F("&gt;");
    else if (c == '"') escaped += F("&quot;");
    else escaped += c;
  }
  return escaped;
}

String getQueryValue(const String& path, const String& key) {
  String token = key + "=";
  int queryStart = path.indexOf('?');
  if (queryStart < 0) {
    return "";
  }
  int keyStart = path.indexOf(token, queryStart + 1);
  if (keyStart < 0) {
    return "";
  }
  int valueStart = keyStart + token.length();
  int valueEnd = path.indexOf('&', valueStart);
  if (valueEnd < 0) {
    valueEnd = path.length();
  }
  return urlDecode(path.substring(valueStart, valueEnd));
}

void writeHttpResponse(WiFiClient& client, const String& body, const String& status = "200 OK", const String& contentType = "text/html") {
  client.print(F("HTTP/1.1 "));
  client.println(status);
  client.print(F("Content-Type: "));
  client.println(contentType);
  client.println(F("Connection: close"));
  client.println();
  client.print(body);
}

void writeHttpText(WiFiClient& client, const String& body, const String& status = "200 OK") {
  writeHttpResponse(client, body, status, "text/plain");
}

void loadWifiConfig() {
  WifiConfigData config = {};
  EEPROM.begin(kEepromSize);
  EEPROM.get(0, config);
  if (strncmp(config.marker, "WFC", 3) == 0 && config.ssid[0] != '\0') {
    currentSsid = config.ssid;
    currentPassword = config.password;
    setupApEnabled = config.setup_ap_enabled != 0;
    appendHash = config.append_hash != 0;
  } else {
    currentSsid = kDefaultSsid;
    currentPassword = kDefaultPassword;
    setupApEnabled = true;
    appendHash = true;
  }
}

void saveWifiConfig() {
  WifiConfigData config = {};
  memcpy(config.marker, "WFC", 4);
  currentSsid.substring(0, kMaxCredentialLength).toCharArray(config.ssid, sizeof(config.ssid));
  currentPassword.substring(0, kMaxCredentialLength).toCharArray(config.password, sizeof(config.password));
  config.setup_ap_enabled = setupApEnabled ? 1 : 0;
  config.append_hash = appendHash ? 1 : 0;
  EEPROM.put(0, config);
  EEPROM.commit();
}

void ensureMdns() {
  if (!mdnsStarted) {
    mdnsStarted = MDNS.begin(kMdnsName);
  }
}

void setApState(bool enabled) {
  setupApEnabled = enabled;
  if (enabled) {
    WiFi.mode(staConnected ? WIFI_AP_STA : WIFI_AP);
    WiFi.softAP(kSetupApSsid, kSetupApPassword);
  } else {
    WiFi.softAPdisconnect(true);
    WiFi.mode(staConnected ? WIFI_STA : WIFI_OFF);
  }
}

bool connectToWifi() {
  WiFi.mode(setupApEnabled ? WIFI_AP_STA : WIFI_STA);
  WiFi.begin(currentSsid.c_str(), currentPassword.c_str());
  uint32_t startMs = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startMs < kConnectTimeoutMs) {
    delay(500);
    Serial.print(".");
  }
  staConnected = WiFi.status() == WL_CONNECTED;
  if (staConnected) {
    Serial.print("IP ADDRESS: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(" STA connect failed");
  }
  if (setupApEnabled) {
    WiFi.softAP(kSetupApSsid, kSetupApPassword);
  }
  ensureMdns();
  return staConnected;
}

String wifiModeLabel() {
  if (setupApEnabled && staConnected) return "AP+STA";
  if (setupApEnabled) return "AP";
  if (staConnected) return "STA";
  return "OFF";
}

void printIpSummary() {
  if (staConnected) {
    Serial.print("IP: ");
    Serial.print(WiFi.localIP());
    Serial.println('#');
  }
  if (setupApEnabled) {
    Serial.print("AP: ");
    Serial.print(WiFi.softAPIP());
    Serial.println('#');
  }
}

void sendSerialPayload(const String& payload) {
  Serial.print(payload);
  if (appendHash) {
    Serial.print('#');
  }
}

void appendSerialLogLine(const String& line) {
  serialLog += line;
  serialLog += '\n';
  if (serialLog.length() > kSerialLogMaxChars) {
    serialLog.remove(0, serialLog.length() - kSerialLogMaxChars);
    int firstNewline = serialLog.indexOf('\n');
    if (firstNewline >= 0) {
      serialLog.remove(0, firstNewline + 1);
    }
  }
}

void pollSerialInput() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\r') {
      continue;
    }
    if (c == '\n' || c == '#') {
      if (currentSerialLine.length() > 0) {
        appendSerialLogLine(currentSerialLine);
        currentSerialLine = "";
      }
      continue;
    }
    currentSerialLine += c;
    if (currentSerialLine.length() > 120) {
      appendSerialLogLine(currentSerialLine);
      currentSerialLine = "";
    }
  }
}

String getSerialLogSnapshot() {
  String snapshot = serialLog;
  if (currentSerialLine.length() > 0) {
    if (snapshot.length() > 0 && snapshot[snapshot.length() - 1] != '\n') {
      snapshot += '\n';
    }
    snapshot += currentSerialLine;
  }
  return snapshot;
}

String makeStatusPage(const String& message = "") {
  String body = F("<!doctype html><html><head><meta charset='utf-8'><title>ESP8266 Serial Bridge</title>");
  body += F("<style>body{font-family:sans-serif;max-width:860px;margin:24px auto;padding:0 16px}table{border-collapse:collapse}td,th{border:1px solid #bbb;padding:6px 10px;text-align:left}input{min-width:300px}code{background:#f4f4f4;padding:2px 4px}</style></head><body>");
  body += F("<h1>ESP8266 Serial Bridge</h1>");
  if (message.length() > 0) {
    body += F("<p><strong>");
    body += htmlEscape(message);
    body += F("</strong></p>");
  }

  body += F("<h2>Network</h2><table>");
  body += F("<tr><th>Mode</th><td>");
  body += wifiModeLabel();
  body += F("</td></tr><tr><th>Saved SSID</th><td>");
  body += htmlEscape(currentSsid);
  body += F("</td></tr><tr><th>STA status</th><td>");
  body += staConnected ? F("Connected") : F("Disconnected");
  body += F("</td></tr><tr><th>STA IP</th><td>");
  body += staConnected ? WiFi.localIP().toString() : String("-");
  body += F("</td></tr><tr><th>Setup AP</th><td>");
  body += setupApEnabled ? F("Enabled") : F("Disabled");
  body += F("</td></tr><tr><th>AP SSID</th><td>");
  body += setupApEnabled ? String(kSetupApSsid) : String("-");
  body += F("</td></tr><tr><th>AP IP</th><td>");
  body += setupApEnabled ? WiFi.softAPIP().toString() : String("-");
  body += F("</td></tr><tr><th>mDNS</th><td><code>http://");
  body += kMdnsName;
  body += F(".local/</code></td></tr><tr><th>MAC</th><td>");
  body += WiFi.macAddress();
  body += F("</td></tr><tr><th>RSSI</th><td>");
  body += staConnected ? String(WiFi.RSSI()) + " dBm" : String("-");
  body += F("</td></tr><tr><th>Uptime</th><td>");
  body += String(millis() / 1000);
  body += F(" s</td></tr><tr><th>Free Heap</th><td>");
  body += String(ESP.getFreeHeap());
  body += F(" bytes</td></tr><tr><th>Append '#'</th><td>");
  body += appendHash ? F("Yes") : F("No");
  body += F("</td></tr></table>");

  body += F("<h2>Quick Controls</h2>");
  body += F("<form method='get' action='/serial' style='display:inline-block;margin-right:12px'>");
  body += F("<input type='hidden' name='data' value='PAUSE'><button type='submit'>PAUSE</button></form>");
  body += F("<form method='get' action='/serial' style='display:inline-block'>");
  body += F("<input type='hidden' name='data' value='RESUME'><button type='submit'>RESUME</button></form>");

  body += F("<h2>Serial Send</h2><form method='get' action='/serial'>");
  body += F("<label>Data to send<br><input name='data' maxlength='120' placeholder='TEXT:HELLO'></label><br><br>");
  body += F("<button type='submit'>Send to Arduino</button></form>");
  body += F("<p>Direct API: <code>/serial?data=TEXT:HELLO</code></p>");
  body += F("<h2>Serial Monitor</h2><p>Read-only serial output captured from the Arduino.</p><pre>");
  body += htmlEscape(getSerialLogSnapshot());
  body += F("</pre><p>Raw endpoint: <code>/serial-read</code></p>");

  body += F("<h2>WiFi Settings</h2><form method='get' action='/config'>");
  body += F("<label>WiFi name<br><input name='ssid' maxlength='31' value='");
  body += htmlEscape(currentSsid);
  body += F("'></label><br><br><label>Password<br><input name='password' maxlength='31' value='");
  body += htmlEscape(currentPassword);
  body += F("'></label><br><br><button type='submit'>Save and reconnect</button></form>");

  body += F("<h2>Setup Hotspot</h2><p>Current hotspot: <code>");
  body += kSetupApSsid;
  body += F("</code> / password <code>");
  body += kSetupApPassword;
  body += F("</code></p><form method='get' action='/ap'>");
  body += F("<input type='hidden' name='enabled' value='");
  body += setupApEnabled ? F("0") : F("1");
  body += F("'><button type='submit'>");
  body += setupApEnabled ? F("Turn setup hotspot off") : F("Turn setup hotspot on");
  body += F("</button></form>");

  body += F("<form method='get' action='/hash' style='margin-top:12px'>");
  body += F("<input type='hidden' name='enabled' value='");
  body += appendHash ? F("0") : F("1");
  body += F("'><button type='submit'>");
  body += appendHash ? F("Stop appending # to serial payloads") : F("Append # to serial payloads");
  body += F("</button></form>");

  body += F("<h2>Useful Endpoints</h2><ul>");
  body += F("<li><code>/</code> status and controls</li>");
  body += F("<li><code>/serial?data=YOUR_TEXT</code> send serial data to Arduino</li>");
  body += F("<li><code>/serial?data=PAUSE</code> pause the Arduino loop</li>");
  body += F("<li><code>/serial?data=RESUME</code> resume the Arduino loop</li>");
  body += F("<li><code>/serial-read</code> read recent Arduino serial output</li>");
  body += F("<li><code>/config?ssid=...&password=...</code> update WiFi credentials</li>");
  body += F("<li><code>/ap?enabled=1</code> or <code>/ap?enabled=0</code> toggle setup hotspot</li>");
  body += F("<li><code>/hash?enabled=1</code> or <code>/hash?enabled=0</code> toggle trailing #</li>");
  body += F("</ul></body></html>");
  return body;
}

void setup() {
  Serial.begin(9600);
  loadWifiConfig();
  connectToWifi();
  server.begin();
  shouldPrintSummary = true;
}

void loop() {
  pollSerialInput();

  if (shouldPrintSummary) {
    printIpSummary();
    shouldPrintSummary = false;
  }

  if (mdnsStarted) {
    MDNS.update();
  }

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (client.connected() && !client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  int addrStart = req.indexOf(' ');
  int addrEnd = req.indexOf(' ', addrStart + 1);
  if (addrStart == -1 || addrEnd == -1) {
    writeHttpText(client, "invalid request", "400 Bad Request");
    client.stop();
    return;
  }

  String path = req.substring(addrStart + 1, addrEnd);
  client.flush();

  if (path == "/") {
    writeHttpResponse(client, makeStatusPage());
  } else if (path.startsWith("/serial")) {
    String payload = getQueryValue(path, "data");
    if (path.startsWith("/serial-read")) {
      writeHttpText(client, getSerialLogSnapshot());
    } else if (payload.length() == 0) {
      writeHttpResponse(client, makeStatusPage("Nothing sent. Provide data=..."));
    } else {
      sendSerialPayload(payload);
      writeHttpResponse(client, makeStatusPage("Sent serial payload: " + payload));
    }
  } else if (path.startsWith("/config")) {
    String newSsid = getQueryValue(path, "ssid");
    String newPassword = getQueryValue(path, "password");
    if (newSsid.length() == 0) {
      writeHttpResponse(client, makeStatusPage("Enter a WiFi name."));
    } else {
      currentSsid = newSsid;
      currentPassword = newPassword;
      saveWifiConfig();
      staConnected = false;
      WiFi.disconnect();
      connectToWifi();
      shouldPrintSummary = true;
      writeHttpResponse(client, makeStatusPage("Saved WiFi settings and refreshed the connection."));
    }
  } else if (path.startsWith("/ap")) {
    String enabled = getQueryValue(path, "enabled");
    setApState(enabled != "0");
    saveWifiConfig();
    shouldPrintSummary = true;
    writeHttpResponse(client, makeStatusPage(setupApEnabled ? "Setup hotspot enabled." : "Setup hotspot disabled."));
  } else if (path.startsWith("/hash")) {
    String enabled = getQueryValue(path, "enabled");
    appendHash = enabled != "0";
    saveWifiConfig();
    writeHttpResponse(client, makeStatusPage(appendHash ? "Serial payloads will append #." : "Serial payloads will not append #."));
  } else {
    writeHttpText(client, "not found", "404 Not Found");
  }

  client.stop();
}
