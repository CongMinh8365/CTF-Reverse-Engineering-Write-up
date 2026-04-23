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
