# Đề bài
[escaperoom](./escaperoom)
# Phân tích
Chạy thử file ta thấy 1 terminal hiện ra có các lựa chọn như đọc log, bật tắt đèn, đổi đường ống thông gió,.... Đây chắc chắn là 1 bài về hệ thống. Trong dạng bài kiểu này việc đầu tiên thường phải làm đó là đưa hệ thống về trạng thái mà đề bài mong muốn

<img width="502" height="358" alt="image" src="https://github.com/user-attachments/assets/1f1560af-6b5a-4420-ba7f-e202e629253e" />

Để làm được điều đó, ta sẽ mở IDA lên phân tích, đọc nội dung hàm `main`:
```C
int __fastcall main(int argc, const char **argv, const char **envp)
{
  __int16 *v3; // rsi
  _QWORD *v4; // rax
  int v5; // ebx
  _BYTE v7[40]; // [rsp+0h] [rbp-40h] BYREF
  unsigned __int64 v8; // [rsp+28h] [rbp-18h]

  v8 = __readfsqword(0x28u);
  touchVisibleProtections();
  std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
  v3 = (__int16 *)"Tip: maintenance logs may be dirty, reflected, or rotated.\n";
  std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
  do
  {
    printMenu(); // In ra menu các lựa chọn 
    std::string::basic_string(v7, v3);
    v3 = (__int16 *)v7;
    v4 = (_QWORD *)std::getline<char,std::char_traits<char>,std::allocator<char>>((std::istream *)&std::cin);
    if ( (unsigned __int8)std::ios::operator!((char *)v4 + *(_QWORD *)(*v4 - 24LL), v7) )
    {
      v5 = 0;
      goto LABEL_26;
    }
    v3 = a1234567890;
    if ( (unsigned __int8)std::operator==<char>(v7, a1234567890) )
    {
      readFacilityLog(); // Lựa chọn 1
    }
    else
    {
      v3 = &a1234567890[1];
      if ( (unsigned __int8)std::operator==<char>(v7, &a1234567890[1]) )
      {
        toggleLights(); // Lựa chọn 2
      }
      else
      {
        v3 = &a1234567890[2];
        if ( (unsigned __int8)std::operator==<char>(v7, &a1234567890[2]) )
        {
          cycleVentRoute(); // Lựa chọn 3
        }
        else
        {
          v3 = &a1234567890[3];
          if ( (unsigned __int8)std::operator==<char>(v7, &a1234567890[3]) )
          {
            rotateCameraBus(); // Lựa chọn 4
          }
          else
          {
            v3 = &a1234567890[4];
            if ( (unsigned __int8)std::operator==<char>(v7, &a1234567890[4]) )
            {
              applyDoorPatch(); // Lựa chọn 5
            }
            else
            {
              v3 = &a1234567890[5];
              if ( (unsigned __int8)std::operator==<char>(v7, &a1234567890[5]) )
              {
                toggleBatteryBridge(); // Lựa chọn 6
              }
              else
              {
                v3 = &a1234567890[6];
                if ( (unsigned __int8)std::operator==<char>(v7, &a1234567890[6]) )
                {
                  maintenanceConsole(); // Lựa chọn 7
                }
                else
                {
                  v3 = &a1234567890[7];
                  if ( (unsigned __int8)std::operator==<char>(v7, &a1234567890[7]) )
                  {
                    enterOverrideToken(); // Lựa chọn 8
                  }
                  else
                  {
                    v3 = &a1234567890[8];
                    if ( (unsigned __int8)std::operator==<char>(v7, &a1234567890[8]) )
                    {
                      showStatus(); // Lựa chọn 9
                    }
                    else
                    {
                      if ( (unsigned __int8)std::operator==<char>(v7, &a1234567890[9]) )
                      {
                        v3 = (__int16 *)"Terminal shutting down.\n";
                        std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
                        v5 = 0;
                        goto LABEL_26;
                      }
                      v3 = (__int16 *)"Unknown selection.\n";
                      std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    v5 = 1;
LABEL_26:
    std::string::~string(v7);
  }
  while ( v5 == 1 );
  return 0;
}
```
Hàm `main` đơn giản là 1 bộ điều phối lệnh, nó kiểm tra số ta nhập vào từ 0-9 và thực hiện hàm chức năng tương ứng. Check hàm đầu tiên `readFacilityLog()`, ta sẽ thu được các dòng thông báo nghe giống như chỉ dẫn ta cách lựa chọn đúng:
```
[ops/07] Corridor override refuses to arm while hallway lights are ON.
[maint/11] East bypass keeps enough pressure in the service hatch to avoid feedback.
[cam/03] Camera bus 3 loses sight of the mirror relay for 4.2 seconds each sweep.
[patch/02] Apply the door patch twice. The third write trips watchdog.
[svc/01] Mirror first. Then hush.
[power/06] Bridge emergency battery before maintenance work or the speaker amp browns out.
```
Dịch nghĩa ra, ta hiểu rằng để đạt trạng thái đúng, ta cần phải làm cho đèn tắt, cửa thông gió ở phía đông, camera bus đạt số 3, door patch 2 lần, chạy lệnh `mirror` trước `hush` sau, và bật pin lên.    
Tiếp theo là các hàm `toggleLights`, `cycleVentRoute`, `rotateCameraBus`, `applyDoorPatch`, `toggleBatteryBridge` đơn giản chỉ là các hàm thay đổi trạng thái của các thiết bị trên. Ta sẽ đi check hàm số 7 `maintenanceConsole`. Nhìn vào điều kiện khi chạy lệnh `mirror`:
```C
else if ( (unsigned __int8)std::operator==<char>(v10, "mirror") )
      {
        if ( dword_5D90E8 == 3 )
        {
          byte_5D90F1 = 1;
          std::operator<<<std::char_traits<char>>(
            (std::ostream *)&std::cout,
            (__int64)"[svc] mirror relay aligned. inspection mode enabled.\n");
        }
        else
        {
          std::operator<<<std::char_traits<char>>(
            (std::ostream *)&std::cout,
            (__int64)"[svc] mirror relay unreachable from current camera bus.\n");
        }
      }
```
Ta thấy rằng nếu lệnh kiểm tra `dword_5D90E8 == 3` sai thì nó sẽ in ra dòng chữ `[svc] mirror relay unreachable from current camera bus.` Điều này có nghĩa là camera bus phải bằng 3 trước khi chạy lệnh `mirror`. Tương tự nhìn vào điều kiện chạy lệnh `hush`:
```C
else if ( (unsigned __int8)std::operator==<char>(v10, "hush") )
      {
        if ( byte_5D90F0 != 1 )
        {
          std::operator<<<std::char_traits<char>>(
            (std::ostream *)&std::cout,
            (__int64)"[svc] hush rejected: bridge the emergency battery first.\n");
        }
        else if ( g_state )
        {
          std::operator<<<std::char_traits<char>>(
            (std::ostream *)&std::cout,
            (__int64)"[svc] hush rejected: corridor glare is saturating the speaker sensor.\n");
        }
        else if ( dword_5D90E4 == 1 )
        {
          if ( byte_5D90F1 != 1 )
          {
            std::operator<<<std::char_traits<char>>(
              (std::ostream *)&std::cout,
              (__int64)"[svc] hush rejected: mirror relay not armed.\n");
          }
          else
          {
            byte_5D90F2 = 1;
            std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout, (__int64)"[svc] alarm speaker muted.\n");
          }
        }
        else
        {
          std::operator<<<std::char_traits<char>>(
            (std::ostream *)&std::cout,
            (__int64)"[svc] hush rejected: airflow noise too high on current vent route.\n");
        }
      }
```
Ta hiểu rằng để chạy được lệnh `hush` ta cần phải setup trước emergency battery, lights OFF, mirror READY và east bypass. Gom hết các điều kiện trên lại, ta thu được cách đạt trạng thái đúng yêu cầu đề bài như sau:
```
(1) lights OFF, east bypass, camera bus 3, door patch 2 times, battery ENGAGED
(2) mirror READY
(3) hush => alarm muted

=> Thứ tự bấm: 2 -> 3 -> 4 (3 lần) -> 5 (2 lần) -> 6 -> 7 -> Gõ `mirror` -> Gõ `hush` -> back
```
Sau khi bấm xong ta chọn `9` để check thử status:

<img width="333" height="169" alt="image" src="https://github.com/user-attachments/assets/7d0f341e-40ea-4cce-b76e-b46e63449996" />

Ta đã thành công đưa về đúng trạng thái. 


