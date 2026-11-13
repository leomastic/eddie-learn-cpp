
Câu 1. Kiểu dữ liệu cơ bản và cấu trúc điều khiển (4,00 điểm)

Mức độ này kiểm tra khả năng đọc hiểu đề và lập trình cơ bản không bị lỗi cú pháp hay tràn số.
• Xử lý tràn số. Luôn ưu tiên dùng kiểu long long cho các phép tính nhân hoặc cộng dồn số lớn để tránh tràn bộ nhớ của kiểu int.
• Công thức toán học trực tiếp. Thay vì dùng vòng lặp chạy từ 1 đến \(N\) gây quá thời gian, hãy áp dụng công thức tính tổng cấp số cộng hoặc chia hết trong \(O(1)\).
• Tối ưu nhập xuất. Thêm hai dòng ios_base::sync_with_stdio(false); và cin.tie(NULL); ở đầu hàm main để tăng tốc độ đọc dữ liệu.

Câu 2. Mảng và Xâu ký tự cơ bản (4,00 điểm)

Dạng bài này giống với bài Sensor Data Report bạn vừa làm, yêu cầu kết hợp cấu trúc dữ liệu với vòng lặp.
• Mảng đánh dấu (Mảng tần suất). Dùng một mảng phụ hoặc std::map để đếm số lần xuất hiện của từng phần tử trong mảng hoặc từng ký tự trong xâu.
• Kỹ thuật xử lý xâu (std::string). Thành thạo các hàm như substr() để cắt xâu, find() để tìm xâu con, và chuyển đổi qua lại giữa ký tự số và số nguyên.
• Sắp xếp kết hợp thống kê. Sử dụng std::sort để gom các phần tử giống nhau nằm cạnh nhau giúp việc tìm trung vị hoặc đếm tần suất dễ dàng hơn.

Câu 3. Thuật toán cơ bản và Số học (4,00 điểm)

Bắt đầu từ câu này đề thi có chia subtask, đòi hỏi thuật toán phải chạy nhanh với dữ liệu lớn (\(N \le 10^5\) hoặc \(10^{6}\)).
• Tìm kiếm nhị phân (Binary Search). Áp dụng lower_bound, upper_bound hoặc tự viết hàm chặt nhị phân theo kết quả để giảm độ phức tạp từ \(O(N)\) xuống \(O(\log N)\).
• Sàng số nguyên tố Eratosthenes. Dùng để kiểm tra số nguyên tố hoặc đếm số lượng ước số của hàng loạt số cùng lúc trong thời gian \(O(N \log \log N)\).
• Ước chung lớn nhất và Lũy thừa nhị phân. Dùng hàm std::gcd() có sẵn trong C++17 và kỹ thuật chia đôi số mũ để tính lũy thừa lớn có chia lấy dư.

Câu 4. Thuật toán tối ưu thời gian và bộ nhớ (4,00 điểm)

Đây là câu phân loại thí sinh, yêu cầu tư duy giải thuật tốt để ăn trọn điểm các subtask cuối.
• Mảng cộng dồn (Prefix Sum) và Mảng hiệu. Giúp tính tổng một đoạn con bất kỳ trong \(O(1)\) thay vì phải dùng vòng lặp duyệt lại nhiều lần.
• Hai con trỏ (Two Pointers) và Cửa sổ trượt. Sử dụng hai biến chỉ số di chuyển cùng chiều hoặc ngược chiều trên mảng đã sắp xếp để tìm cặp số hoặc đoạn con thỏa mãn điều kiện trong \(O(N)\).
• Quy hoạch động cơ bản và Tham lam. Làm quen với các bài toán kinh điển như tìm đoạn con có tổng lớn nhất (Kadane), bài toán cái túi, hoặc dãy con tăng dài nhất.

Câu 5. Bài toán đếm và Tổ hợp (4,00 điểm)

Câu này thường kết hợp kiến thức toán tổ hợp với kỹ thuật lập trình để đếm số lượng cấu hình thỏa mãn điều kiện.
• Quy tắc cộng và Quy tắc nhân. Chia bài toán thành các trường hợp độc lập hoặc các bước liên tiếp, kết hợp phép chia lấy dư (% 1000000007) sau mỗi phép tính.
• Đếm cặp phần tử bằng mảng đánh dấu hoặc Map. Thay vì dùng hai vòng lặp lồng nhau \(O(N^2)\) để đếm cặp \((i, j)\) thỏa mãn \(a_i + a_j = K\), hãy lưu các số đã duyệt vào map để tìm phần bù trong \(O(\log N)\).
• Tổ hợp chập \(k\) của \(n\) (\(C_{n}^{k}\)). Biết cách tính tổ hợp bằng công thức nhân nghịch đảo modulo (định lý Fermat nhỏ) hoặc dùng tam giác Pascal khi \(N\) nhỏ.
Ma trận này bám sát cấu trúc đề thi Học sinh giỏi Tin học. Bạn muốn bắt đầu luyện tập chuyên sâu từ nhóm kỹ thuật của Câu 3 (Số học & Tìm kiếm nhị phân) hay Câu 4 (Mảng cộng dồn & Hai con trỏ) để mình gửi bài tập mẫu kèm hướng dẫn giải chi tiết?

