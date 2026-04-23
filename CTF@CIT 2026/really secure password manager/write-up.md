# Đề bài
### [reallysecurepasswordmanager](./reallysecurepasswordmanager)
## Phân tích
Chạy thử file ta thấy hiện lên 1 menu đăng nhập:

<img width="1365" height="180" alt="image" src="https://github.com/user-attachments/assets/f35cae84-c3ab-4c7e-be8d-86902a9b3396" />

Thử nhập 1 và 2 đều không thấy có gì, nhập 3 thì xuất hiện dòng `Account name`, tiêp tục nhập bừa chuỗi `hehe` thấy dòng thông báo `hehe password: ERROR_NOT_AUTHENTICATED`, cuối cùng thử nhập 4 thì nó cũng hiện thông báo `ERROR_NOT_AUTHENTICATED`:

<img width="1366" height="534" alt="image" src="https://github.com/user-attachments/assets/ba450af9-ae93-4c07-8d65-ced2f83bd990" />

Có vẻ như ở bài này ta sẽ cần login được và nhập đúng account name thì password mới hiện ra, nếu không nó sẽ chỉ báo lỗi `ERROR_NOT_AUTHENTICATED`.   
Mở IDA lên và phân tích hàm `main` ta có:
```C
int __fastcall __noreturn main(int argc, const char **argv, const char **envp)
{
  std::ostream *v3; // rax
  std::ostream *v4; // rbx
  void *v5; // rax
  std::ostream *v6; // rax
  std::ostream *v7; // rax
  char v8; // [rsp+17h] [rbp-49h] BYREF
  char *v9; // [rsp+18h] [rbp-48h]
  _BYTE v10[40]; // [rsp+20h] [rbp-40h] BYREF
  unsigned __int64 v11; // [rsp+48h] [rbp-18h]

  v11 = __readfsqword(0x28u);
  while ( 1 )
  {
    v3 = std::operator<<<std::char_traits<char>>(
           (std::ostream *)&std::cout,
           (__int64)"Welcome to my password manager!\n"
                    "Please select an option below\n"
                    "=========================\n"
                    "1. log in\n"
                    "2. log out\n"
                    "3. read a password\n"
                    "4. save a password\n"
                    "=========================");
    std::ostream::operator<<(v3, std::endl<char,std::char_traits<char>>);
    if ( authenticated )
    {
      v4 = std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout, (__int64)"Authenticated as: ");
      v5 = getlogin();
      v6 = std::operator<<<std::char_traits<char>>(v4, (__int64)v5);
      std::ostream::operator<<(v6, std::endl<char,std::char_traits<char>>);
    }
    v9 = &v8;
    std::string::basic_string<std::allocator<char>>(v10, (const char *)&unk_59D400, &v8);
    std::__new_allocator<char>::~__new_allocator(&v8);
    std::getline<char,std::char_traits<char>,std::allocator<char>>((std::istream *)&std::cin);
    if ( (unsigned __int8)std::operator==<char>(v10, "1") )
    {
      authenticated = auth();
    }
    else if ( (unsigned __int8)std::operator==<char>(v10, "2") )
    {
      authenticated = 0;
    }
    else if ( (unsigned __int8)std::operator==<char>(v10, "3") )
    {
      getPass();
    }
    else if ( (unsigned __int8)std::operator==<char>(v10, "4") )
    {
      v7 = std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout, (__int64)"ERROR_NOT_AUTHENTICATED");
      std::ostream::operator<<(v7, std::endl<char,std::char_traits<char>>);
    }
    std::string::~string(v10);
  }
}
```
Để ý vào biến toàn cục `authenticated`, flow chương trình có thể thấy chỉ loanh quanh biến này. Nếu `authenticated` = 1 thì chương trình in ra dòng chữ `Authenticated as:` và gọi hàm `getlogin`. Kiểm tra hàm này ta biết đây là hàm của hệ thống để lấy tên người dùng (ví dụ tên người dùng là "kali" thì sẽ là "Authenticated as: kali").  

Tiếp theo, ta thấy nếu ta chọn 1 (log in) chương trình sẽ gọi hàm `auth`. Code hàm `auth` như sau:
```C
__int64 __fastcall auth()
{
  const char *v0; // rax
  char v2; // [rsp+7h] [rbp-49h] BYREF
  char *v3; // [rsp+8h] [rbp-48h]
  _BYTE v4[40]; // [rsp+10h] [rbp-40h] BYREF
  unsigned __int64 v5; // [rsp+38h] [rbp-18h]

  v5 = __readfsqword(0x28u);
  v3 = &v2;
  v0 = (const char *)getlogin();
  std::string::basic_string<std::allocator<char>>(v4, v0, &v2);
  std::__new_allocator<char>::~__new_allocator(&v2);
  std::operator==<char>(v4, "notronnie");
  std::string::~string(v4);
  return 1;
}
```
Nó sẽ gọi hàm `getlogin` để lấy username, sau đó so sánh với "notronnie" => Ta đã hiểu vì sao khi chạy chương trình chọn 1 thì nó ko hiện ra gì, đó là do ta ko phải "notronnie", và ta cũng đã biết cách làm cho biến `authenticated` = 1, đó là khiến ta trở thành "notronnie" (hoặc ngược lại)   

Tiếp theo nếu chọn 2 (log out) chương trình đơn giản gán `authenticated` = 0, còn chọn 4 thì in ra dòng chữ báo lỗi `ERROR_NOT_AUTHENTICATED`. Nói chung không còn gì để phân tích ở 2 nhánh này.

Cuối cùng là nếu chọn 3 (read a password) chương trình sẽ gọi hàm `getPass`:
```C
unsigned __int64 __fastcall getPass()
{
  std::ostream *v0; // rax
  std::ostream *v1; // rbx
  __int64 v2; // rax
  _BYTE v4[32]; // [rsp+0h] [rbp-60h] BYREF
  _BYTE v5[40]; // [rsp+20h] [rbp-40h] BYREF
  unsigned __int64 v6; // [rsp+48h] [rbp-18h]

  v6 = __readfsqword(0x28u);
  std::string::basic_string(v4);
  std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout, (__int64)"Account name: ");
  std::getline<char,std::char_traits<char>,std::allocator<char>>((std::istream *)&std::cin);
  v0 = (std::ostream *)std::operator<<<char>(&std::cout, v4);
  v1 = std::operator<<<std::char_traits<char>>(v0, (__int64)" password: ");
  generatePassword((__int64)v5, (__int64)v4);
  v2 = std::operator<<<char>(v1, v5);
  std::ostream::operator<<(v2, std::endl<char,std::char_traits<char>>);
  std::string::~string(v5);
  std::string::~string(v4);
  return v6 - __readfsqword(0x28u);
}
```
Đầu tiên nó sẽ in ra dòng chữ `Account name: ` để mình nhập vào, sau đó nó sẽ truyền input của mình vào hàm `generatePassword` (có lẽ để tạo ra mật khẩu tương ứng với input). Tiếp tục kiểm tra hàm `generatePassword`:
```C
__int64 __fastcall generatePassword(__int64 a1, __int64 a2)
{
  int v2; // eax
  int v3; // eax
  char *v4; // rax
  char v6; // [rsp+17h] [rbp-1429h] BYREF
  unsigned __int64 i; // [rsp+18h] [rbp-1428h]
  __int64 v8; // [rsp+20h] [rbp-1420h]
  __int64 v9; // [rsp+28h] [rbp-1418h]
  _BYTE *v10; // [rsp+30h] [rbp-1410h]
  _BYTE v11[8]; // [rsp+38h] [rbp-1408h] BYREF
  _BYTE v12[32]; // [rsp+40h] [rbp-1400h] BYREF
  _BYTE v13[32]; // [rsp+60h] [rbp-13E0h] BYREF
  _BYTE v14[32]; // [rsp+80h] [rbp-13C0h] BYREF
  _BYTE v15[5000]; // [rsp+A0h] [rbp-13A0h] BYREF
  unsigned __int64 v16; // [rsp+1428h] [rbp-18h]

  v16 = __readfsqword(0x28u);
  v10 = v11;
  std::string::basic_string<std::allocator<char>>(
    v12,
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()",
    v11);
  std::__new_allocator<char>::~__new_allocator(v11);
  v8 = 16;
  v9 = std::__str_hash_base<char,std::allocator<char>,std::string>::operator()(&v6, a2);
  std::mersenne_twister_engine<unsigned long,32ul,624ul,397ul,31ul,2567483615ul,11ul,4294967295ul,7ul,2636928640ul,15ul,4022730752ul,18ul,1812433253ul>::mersenne_twister_engine(
    v15,
    (unsigned int)v9);
  v2 = std::string::size(v12);
  std::uniform_int_distribution<int>::uniform_int_distribution(v11, 0, (unsigned int)(v2 - 1));
  std::string::basic_string(a1);
  for ( i = 0; i <= 0xF; ++i )
  {
    v3 = std::uniform_int_distribution<int>::operator()<std::mersenne_twister_engine<unsigned long,32ul,624ul,397ul,31ul,2567483615ul,11ul,4294967295ul,7ul,2636928640ul,15ul,4022730752ul,18ul,1812433253ul>>(
           v11,
           v15);
    v4 = (char *)std::string::operator[](v12, v3);
    std::string::push_back(a1, (unsigned int)*v4);
  }
  std::string::basic_string(v13, a1);
  validate((__int64)v14, (__int64)v13);
  std::string::operator=(a1, v14);
  std::string::~string(v14);
  std::string::~string(v13);
  std::string::~string(v12);
  return a1;
}
```
Hàm này nhận input của ta vào và dùng 1 thuật toán hash để ra 1 chuỗi 16 kí tự, sau đó chuỗi này lại được truyền vào hàm `validate`:
```C
void __fastcall validate()
{
  __int64 i; // rbp
  int v1; // edi
  _QWORD *v2; // rax
  __int64 j; // rdx
  __int64 k; // rbx
  __int64 v5; // rbp
  __int64 v6; // [rsp+78h] [rbp-48h]

  __getcallerseflags();
  v6 = v5;
  for ( i = 11398436; ; i = 11398436 )
  {
    v1 = 32;
    do
    {
      if ( !_InterlockedCompareExchange((volatile signed __int32 *)(i + 211), 1, 0) )
      {
        *(_QWORD *)(i + 187) = 0x400000;
        *(_QWORD *)(i + 243) = 1599713120;
        *(_QWORD *)(i + 243) ^= 0x5FF1AF60uLL;
        if ( i == 11398436 )
        {
          qword_AA8A48[53] = 32391;
          *(__int64 *)((char *)&qword_ADEDF8[2] + 7) = 11176944;
        }
        *(_QWORD *)(i + 195) = v6 ^ 0x7FD40EA4;
        *(_QWORD *)(i + 195) ^= 0x7FD40EA4uLL;
        *(_QWORD *)(i + 178) = 11754253;
        v2 = qword_ABE200 + 2580;
        for ( j = *(__int64 *)((char *)qword_ADEDF8 + 3);
              j != 11267092 && i != 11398436;
              j = *(__int64 *)((char *)qword_ADEDF8 + 3) )
        {
          _mm_pause();
        }
        if ( j != 11267092 )
        {
          for ( k = 658; k; k = (unsigned int)(k - 1) )
            *v2++ += 0x400000LL;
          *(__int64 *)((char *)qword_ADEDF8 + 3) = 11267092;
        }
        if ( *(_QWORD *)(i + 215) != 11267092 )
          *(_QWORD *)(i + 215) = 11267092;
        __asm { jmp     qword ptr [rax] }
      }
      i = i - 0x17BA7A992LL + 0x17BA7AB12LL;
      --v1;
    }
    while ( v1 );
    _mm_pause();
  }
}
```
Đến đây ta phát hiện hàm này đã bị Obfuscation bằng Control Flow Flattening. Tuy nhiên đoạn code này ta cũng không cần quan tâm lắm, cái thật sự đáng lưu ý chính là câu lệnh `__asm { jmp     qword ptr [rax]`. Có vẻ như nó sẽ nhảy đến 1 chỗ nào đó để tiếp tục thực thi lệnh

Ok, giờ mục tiêu của ta là cần phải nhảy đến địa chỉ đó để xem rốt cuộc nó sẽ làm gì, tuy nhiên hãy nhớ lại rằng trước đó ta sẽ cần tìm cách biến `notronnie` thành username thực sự để bypass được cái `login`

## Bypass username
Ta sẽ viết một scripts Python để làm điều này, có 2 cách làm: Hoặc là biến username trên máy thành `notronnie`, hoặc là làm ngược lại. Ta sẽ làm ngược lại, tức là khiến cho chương trình nhìn `notronnie` thành username trên máy ta luôn (ở máy này là `doanminh`). Cách này để khiến mọi thứ trở nên nhất quán, đề phòng chương trình ko chỉ kiểm tra username mà còn có thể kiểm tra các thứ liên quan như loginuid, getuid, geteuid, etc/passwd thì vẫn vượt qua được.   

Scripts Python như sau:
```python
import sys

USERNAME_OFF = 0x19D29C 
ORIGINAL = b"notronnie\x00"

def main():
    input_binary = "reallysecurepasswordmanager"
    output_binary = "rspm_patched"
    my_username = "doanminh"

    username_bytes = my_username.encode("ascii")
    
    # Đọc file gốc
    with open(input_binary, "rb") as f:
        data = bytearray(f.read())

    # Đè tên mới vào, phần thừa thì nhồi thêm byte Null (\x00) cho đủ 10 byte như cũ
    patch = username_bytes + b"\x00" + b"\x00" * (len(ORIGINAL) - len(username_bytes) - 1)
    data[USERNAME_OFF:USERNAME_OFF + len(ORIGINAL)] = patch

    # Ghi ra file mới
    with open(output_binary, "wb") as f:
        f.write(data)
    
    print(f"[+] Đã vá thành công! File mới: {output_binary}")

if __name__ == "__main__":
    main()
```
Chạy scripts trên, ta thu được file patched là [rspm_patched](./rspm_patched)
