# Đề bài
[LegoClicker_umass.apk](./LegoClicker_umass.apk)

Hackers have taken over and corrupted your beloved Lego Clicker game, can you reclaim the top of the leaderboard? Note: There are fake flags throughout the challenge which should be obvious to tell based on contents.

# Phân tích
Đây là file apk, để mở nó ta cần dùng trình giả lập Android, như trong bài này tôi dùng NoxPlayer. Giao diện khi mở lên có thể thấy là 1 game dạng cày cuốc, người chơi bấm liên tục vào cục gạch để nâng điểm, sau đó dùng điểm mua các loại nâng điểm tự động khác nhau và các skills để tốc độ nâng điểm tăng nhanh hơn. Bấm vào ô Score thì thấy người chơi đứng đầu đang có 1 nghìn tỷ điểm. Do đề bài hỏi rằng "can you reclaim the top of the leaderboard?" nên rõ ràng mục tiêu của ta là cần đạt hơn 1 nghìn tỷ điểm để vượt mặt người chơi đứng đầu đó.

<img width="1240" height="716" alt="image" src="https://github.com/user-attachments/assets/166b7ee8-2142-4b29-9d47-915706fc9e6b" />

<img width="1240" height="716" alt="image" src="https://github.com/user-attachments/assets/30b6ee5d-2c5d-4df0-b3ae-0b0314d78f9c" />

Nhưng chắc chắn chẳng ai rảnh ngồi chơi để đạt 1 nghìn tỷ điểm cả! Sử dụng `JADX` để mở game lên, xem mục `AndroidManifest.xml` thì ta thấy:

<img width="1361" height="548" alt="image" src="https://github.com/user-attachments/assets/0ed828a7-7a23-4403-8907-9d3d2c634a48" />

MA có vẻ là viết tắt cho MainActivity, do đó mục tiếp theo ta cần xem là `com.example.LegoClicker`. Mở ra ta thấy có các mục như 


