import os
import pty
import select
import time
from concurrent.futures import ProcessPoolExecutor, as_completed

BINARY_PATH = "./rspm_patched"
WORDLIST_PATH = "10k-most-common.txt" 
ERROR_MSG = "ERROR_NOT_AUTHENTICATED"
WORKERS = 30  

def interact_with_binary(account_name):
    master, slave = pty.openpty()
    pid = os.fork()

    if pid == 0:
        os.close(master)
        os.dup2(slave, 0)
        os.dup2(slave, 1)
        os.dup2(slave, 2)
        os.execv(BINARY_PATH, [BINARY_PATH])
    
    os.close(slave)
    
    def send_input(text):
        os.write(master, text.encode() + b"\n")
        time.sleep(0.01)

    try:
        send_input("1")
        send_input("3")
        send_input(account_name)

        time.sleep(0.15)
        output = b""
        while True:
            r, _, _ = select.select([master], [], [], 0.1)
            if r:
                data = os.read(master, 4096)
                if not data: break
                output += data
            else:
                break
        
        return account_name, output.decode(errors='ignore')

    finally:
        os.close(master)
        os.kill(pid, 9)
        os.waitpid(pid, 0)

def main():
    wordlist = []
    try:
        with open(WORDLIST_PATH, "r", encoding="utf-8", errors="ignore") as f:
            wordlist = [line.strip() for line in f if line.strip()]
    except FileNotFoundError:
        print(f"[X] Không thấy file '{WORDLIST_PATH}'")
        return

    # Dùng ProcessPoolExecutor để tạo 30 tiến trình chạy cùng lúc
    with ProcessPoolExecutor(max_workers=WORKERS) as executor:
        futures = {executor.submit(interact_with_binary, name): name for name in wordlist}
        
        for future in as_completed(futures):
            name, result = future.result()
            
            if "password:" in result and ERROR_MSG not in result:
                print(f"\nCÓ SỰ THAY ĐỔI Ở ACCOUNT: '{name}'")
                print("=" * 60)
                for res_line in result.split('\n'):
                    if name in res_line:
                        print(res_line.strip())
                print("=" * 60)
                
                os._exit(0) 

if __name__ == "__main__":
    main()
