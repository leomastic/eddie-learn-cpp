#include <iostream>
#include <fstream> // Bắt buộc phải thêm thư viện này

using namespace std;

int main() {
    // 1. Mở file để đọc và ghi
    ifstream fin("CHOXUAN.INP");   // File dữ liệu vào
    ofstream fout("CHOXUAN.OUT"); // File dữ liệu ra

    // Kiểm tra xem file có mở thành công không (tuỳ chọn nhưng nên có)
    if (!fin.is_open()) {
        cout << "Khong mo duoc file CHOXUAN.INP!" << endl;
        return 1;
    }

    // 2. Khai báo biến kiểu long long (tránh tràn số khi K * 7 > 2 * 10^9)
    long long N, K;

    // 3. Đọc dữ liệu: 
    // Lần 1: fin >> N sẽ đọc số N ở dòng đầu tiên.
    // Lần 2: fin >> K sẽ tự động bỏ qua dấu xuống dòng và đọc số K ở dòng thứ hai.
    fin >> N >> K; 

    // Hoặc bạn viết tách ra 2 dòng cho rõ ràng cũng tương đương:
    // fin >> N;
    // fin >> K;

    // 4. Xử lý tính toán
    long long cost = K * 7;

    if (N < cost) {
        fout << -1; // Nếu không đủ tiền thì ghi -1
    } else {
        fout << N - cost; // Nếu đủ tiền thì ghi số tiền còn lại
    }

    // 5. Đóng file (C++ tự đóng khi kết thúc hàm main, nhưng viết rõ cho an toàn)
    fin.close();
    fout.close();

    return 0;
}