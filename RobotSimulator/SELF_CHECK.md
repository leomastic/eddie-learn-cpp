1. Why do we split projects into multiple files?
- Easy to manage: Shorter code, easy to read.
- Used to be use mutiple times.
- For faster compilation:
+ If we just fix a dot or a comma, the robot will read all the programme again.
+ Instead of that, if we split projects into multiple files, the robot only read the fixed file, it doesn't read the rest.

2. What belongs in a header?
- Declarations;
- The function without body;
- Classes;
- Constant.

3. What belongs in a cpp?
- Real codes (Logic codes, function bodies,...).

4. Why do we use #pragma once?
- Anti-duplication: Prevents header files from being included multiple times.
- Prevents redefinition.

5. What is the difference between "robot.h" and <vector>?
- "robot.h": file hand-coded by programmer;
- <vector>: A standard library file available in the C++ language.

6. What does #include actually do?
- Copy all the called contents.

7. How does CMake know which files to compile?
- Configuration: It reads the CMakeLists.txt file.
- Commands: It looks at the add_executable() commands where the programmer explicitly lists the source (.cpp) files.

// manage: quản lý

// compilation: biên dịch

// comma: dấu phẩy

// Declarations: Khai báo

// Constant: Hằng số

// redefinition: Định nghĩa lại

// compile: Trương trình biên dịch gồm:
// + Tiền xử lý: Trình biên dịch đọc các chỉ thị bắt đầu bằng dấu # (như #include, #define), chuẩn bị các thư viện cần thiết trước khi tiến hành dịch.
// + Biên dịch (Compilation): Mã nguồn C++ sẽ được dịch sang mã Assembly (ngôn ngữ trung gian giữa mã nguồn và mã máy), sau đó tiếp tục được chuyển thành các tệp mã đối tượng (Object file - đuôi .obj hoặc .o).   
// + Liên kết (Linking): Trình liên kết (Linker) sẽ ghép nối các tệp mã đối tượng vừa tạo ra với các thư viện hệ thống để tạo thành một tệp thực thi hoàn chỉnh (thường có đuôi .exe trên Windows).

// Configuration: File cấu hình

// explicitly: một cách rõ ràng

// source: nguồn