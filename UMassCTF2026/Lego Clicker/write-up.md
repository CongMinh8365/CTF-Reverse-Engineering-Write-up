# Đề bài
[LegoClicker_umass.apk](./LegoClicker_umass.apk)

Hackers have taken over and corrupted your beloved Lego Clicker game, can you reclaim the top of the leaderboard? Note: There are fake flags throughout the challenge which should be obvious to tell based on contents.

# Phân tích
Đây là file apk, để mở nó ta cần dùng trình giả lập Android, như trong bài này tôi dùng NoxPlayer. Giao diện khi mở lên có thể thấy là 1 game dạng cày cuốc, người chơi bấm liên tục vào cục gạch để nâng điểm, sau đó dùng điểm mua các loại nâng điểm tự động khác nhau và các skills để tốc độ nâng điểm tăng nhanh hơn. Bấm vào ô Score thì thấy người chơi đứng đầu đang có 1 nghìn tỷ điểm. Do đề bài hỏi rằng "can you reclaim the top of the leaderboard?" nên rõ ràng mục tiêu của ta là cần đạt hơn 1 nghìn tỷ điểm để vượt mặt người chơi đứng đầu đó.

<img width="1240" height="716" alt="image" src="https://github.com/user-attachments/assets/166b7ee8-2142-4b29-9d47-915706fc9e6b" />

<img width="1240" height="716" alt="image" src="https://github.com/user-attachments/assets/30b6ee5d-2c5d-4df0-b3ae-0b0314d78f9c" />

Nhưng chắc chắn chẳng ai rảnh ngồi chơi để đạt 1 nghìn tỷ điểm cả! Sử dụng `JADX` để mở game lên, xem mục `AndroidManifest.xml` thì ta thấy đoạn code sau:

<img width="1361" height="548" alt="image" src="https://github.com/user-attachments/assets/0ed828a7-7a23-4403-8907-9d3d2c634a48" />

MA có vẻ là viết tắt cho MainActivity, do đó mục tiếp theo ta cần xem là `com.example.LegoClicker`. Mở lên ta thấy có nhiều mục có tên khá vô nghĩa như MA, AA, LA,... nhưng bên cạnh đó có 2 cái tên đáng lưu ý `FlagEngine` và `SessionValidator`. Trước tiên mở `FlagEngine` lên xem, ta thấy cấu trúc của nó khá rõ ràng với các hàm xử lý tính toán điểm số:

<img width="1366" height="671" alt="image" src="https://github.com/user-attachments/assets/65d30223-7a17-4d72-8125-cd0b3175cade" />

- Hàm b(double d): Kiểm tra số điểm của người chơi và trả về các mốc level (1 đến 5).
- Hàm c(int i): Gắn nhãn cho các level đó, tương ứng từ NOVICE (Tân binh) đến LEGEND (Huyền thoại).
- Hàm e(int i): Một vòng lặp giải mã XOR cơ bản trên mảng byte tĩnh kLabelEnc.
- Hàm d(double d): Thực hiện các phép toán Bitwise (XOR, Shift) phức tạp để băm (hash) điểm số.

Đây khả năng cao là bẫy Fake Flag của tác giả! Bởi hãy nhìn lại vào hàm `b()`: Ngưỡng điểm cao nhất mà `FlagEngine` xử lý chỉ dừng lại ở 1 000 000 điểm, trong khi mục tiêu của ta là cần phải vượt qua 1 nghìn tỷ điểm của người đứng đầu. Nghĩa là hàm này chỉ phục vụ cho việc cấp rank và nhả cờ cho những người chơi ở đáy bảng xếp hạng.

Tiếp theo ta kiểm tra hàm `SessionValidator`:
```java
package com.example.LegoClicker;
public final class SessionValidator {
    public static final boolean a;

    /* JADX INFO: compiled from: r8-map-id-51b54c9e59b63e0fb0abe04daff984b4fb85d07ef3fcb7973595bce215c10515 */
    public static final class SessionToken {
        public long mask() {
            return 0L;
        }
    }

    static {
        boolean z = false;
        try {
            int[] iArr = {86, 95, 93, 85, 89, 85, 72, 95};
            char[] cArr = new char[8];
            for (int i = 0; i < 8; i++) {
                cArr[i] = (char) (iArr[i] ^ 58);
            }
            System.loadLibrary(new String(cArr));
            z = true;
        } catch (Throwable unused) {
        }
        a = z;
    }

    public static String a(long j, long j2) {
        if (!a) {
            return "";
        }
        try {
            SessionToken sessionToken = new SessionToken();
            int[] iArr = {47, 37, 50, 63, 30, 46, 53, 63, 55, 31, 61, 63, 52, 57};
            char[] cArr = new char[14];
            for (int i = 0; i < 14; i++) {
                cArr[i] = (char) (iArr[i] ^ 92);
            }
            String str = new String(cArr);
            Class cls = Long.TYPE;
            return (String) SessionValidator.class.getDeclaredMethod(str, cls, cls).invoke(null, Long.valueOf(j + sessionToken.mask()), Long.valueOf(j2 + sessionToken.mask()));
        } catch (Throwable unused) {
            return "";
        }
    }

    public static native String refreshTileMap(long j, long j2);
    @Deprecated
    public static native String syncBrickCache(long j, long j2);
    @Deprecated
    public static native String validateBrickToken(long j, long j2);
}
```
Ngay khi class được gọi, khối lệnh `static` sẽ chạy đầu tiên. Ở đây, tác giả không gọi tên thư viện một cách trực tiếp mà giấu nó dưới mảng số nguyên `iArr`, sau đó đem XOR từng phần tử với số `58`. Kết quả thu được chính là chuỗi `legocore`. Hệ thống sẽ gọi `System.loadLibrary("legocore")` để nạp file `liblegocore.so` vào bộ nhớ và gán biến `boolean a = true`. Tiếp theo là hàm xử lý chính. Lần này mảng `iArr` được XOR với key `92`. Đem giải mã, ta thu được chuỗi `syncBrickCache`. Đây là tên 1 hàm nhưng tác giả không gọi thẳng nó mà thay vào đó, tác giả sử dụng Java Reflection (getDeclaredMethod().invoke()) để gọi một cách gián tiếp thông qua chuỗi string vừa giải mã.

Cuối cùng, ta nhìn thấy 3 khai báo hàm C/C++:
```java
public static native String refreshTileMap(long j, long j2);
public static native String syncBrickCache(long j, long j2);
public static native String validateBrickToken(long j, long j2);
```
Ta thấy rằng để lấy được Flag, mục tiêu là phải gọi được hàm `syncBrickCache`. Hàm này yêu cầu truyền vào biến j là số điểm khổng lồ ta muốn ép vào hệ thống và biến j2 là mã xác thực tương ứng với số điểm j đó. Đây là cơ chế Anti-Cheat của game để đảm bảo người chơi không thể tùy ý sửa điểm bằng Memory Editor (như Cheat Engine) nếu không biết thuật toán mã hóa sinh ra token.

Tuy nhiên, thuật toán để tính ra cái mã xác thưc j2 này, cũng như logic nhả cờ thực sự, hoàn toàn bị che giấu đằng sau từ khóa native. 
