from z3 import *

solver = Solver()
P = [BitVec(f'p_{i}', 8) for i in range(12)]

# Ràng buộc cơ sở: Mỗi ký tự chỉ nằm trong bảng ALPHABET (từ 0 đến 15)
for i in range(12):
    solver.add(P[i] >= 0, P[i] <= 15)

# 1. Ràng buộc Stress
OBS_STRESS = [2, 5, 11, 10, 5, 1, 13, 4, 3, 3, 14]
for i in range(11):
    solver.add((2 * P[i] + 3 * P[i+1]) % 16 == OBS_STRESS[i])

# 2. Ràng buộc Shear (Phép XOR)
OBS_SHEAR = [5, 5, 15, 8, 5, 6, 7, 4, 5, 5]
for i in range(10):
    solver.add(P[i] ^ P[i+2] == OBS_SHEAR[i])

# 3. Ràng buộc Grain
OBS_GRAIN = [3, 11, 3, 4, 14, 4, 5, 6, 1]
for i in range(9):
    solver.add((P[i] + P[i+3] - P[i+1]) % 16 == OBS_GRAIN[i])

# 4. Ràng buộc Load
solver.add(Sum([P[i] for i in range(12)]) == 93)

# 5. Ràng buộc Seal
solver.add(Sum([(i + 5) * P[i] for i in range(12)]) % 16 == 9)

# Kích hoạt Solver
if solver.check() == sat:
    m = solver.model()
    ALPHABET = "BCDFGHJKLMNPQRST"
    
    # Ráp các giá trị tìm được lại thành chuỗi
    result = "".join([ALPHABET[m[P[i]].as_long()] for i in range(12)])
    print(f"\n[+] Token chuẩn: {result}")
else:
    print("[-] Không tìm được lời giải")
