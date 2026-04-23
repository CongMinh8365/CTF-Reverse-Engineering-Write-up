# Đề bài
### [faultline](./faultline)
## Phân tích
Chạy thử file, ta thấy nó là một dạng CLI Tool có các lệnh như `score`, `trace`, `token`, `compare`, `nudge`, và `submit`. Có vẻ hàm submit là để lấy flag, nhưng hàm này yêu cầu một `PROFILE` và một `TOKEN` chuẩn. Từ 3 dòng gợi ý bên dưới, ta hiểu rằng `PROFILE` chỉ được tạo ra từ các chữ cái `BCDFGHJKLMNPQRST` và có độ dài là 12, điểm số đạt được phải là `2026`.

<img width="1366" height="281" alt="image" src="https://github.com/user-attachments/assets/79b28dc2-0e3e-4e26-aca8-183a4a0753cb" />

Cái điều kiện thứ 3 chưa thấy liên quan gì lắm đến 2 cái trên. Mở IDA ra phân tích hàm `main`, ta thấy các điều sau:
- Thực chất hàm `main` đóng vai trò như một bộ định tuyến (Router). Nó kiểm tra `argv[1]` để rẽ nhánh vào các chức năng tương ứng: score, trace, token, compare, nudge, và submit.
- Lệnh cuối cùng ta cần chạy là `submit` để lấy flag, nó gọi hàm `validate()` yêu cầu 2 tham số: `PROFILE` và `TOKEN`. Trong khi đó, lệnh `token` sẽ sinh ra token dựa trên `PROFILE`. Vậy mấu chốt của bài toán quy về một biến duy nhất: Phải tìm ra chuỗi `PROFILE` chuẩn xác. Và như phân tích ban đầu thì ta biết `PROFILE` chỉ được tạo ra từ các chữ cái `BCDFGHJKLMNPQRST` và có độ dài là 12
- Ta sẽ phân tích điều kiện cuối cùng "score = 2026" bằng cách đi vào nhánh `score`. Nó sẽ gọi `parseProfile()` để kiểm tra 2 điều kiện của chuỗi nhập vào. Nếu đúng, nó ném profile vào hàm `computeFaultlineScoreVisible()` để lấy điểm số, rồi truyền điểm này vào hàm `gradeBandVisible()` (hàm này sẽ kiểm tra xem score = 2026 không)

=> Chốt lại bước tiếp theo của ta là đi vào hàm `computeFaultlineScoreVisible` để phân tích cách tính toán điểm số:
```C
__int64 __fastcall computeFaultlineScoreVisible(__int64 a1)
{
  ............. (khai báo biến)

  v29 = __readfsqword(0x28u);
  v15 = 962;
  stressTrace(v28, a1);
  for ( i = 0; i < 0xB; ++i )
  {
    v1 = *(_DWORD *)std::array<int,11ul>::operator[](&OBS_STRESS, i);
    v2 = (int *)std::array<int,11ul>::operator[](v28, i);
    v22 = cycDist(*v2, v1);
    if ( v22 )
      v3 = -2 * v22 * v22;
    else
      v3 = 29;
    v15 += v3;
  }
  shearTrace(v27, a1);
  for ( j = 0; j < 0xA; ++j )
  {
    v4 = *(_DWORD *)std::array<int,10ul>::operator[](&OBS_SHEAR, j);
    v5 = (int *)std::array<int,10ul>::operator[](v27, j);
    v21 = cycDist(*v5, v4);
    if ( v21 )
      v6 = -3 * v21 * v21;
    else
      v6 = 31;
    v15 += v6;
  }
  v7 = a1;
  grainTrace(v26, a1);
  for ( k = 0; k < 9; ++k )
  {
    v8 = *(_DWORD *)std::array<int,9ul>::operator[](&OBS_GRAIN, k);
    v9 = (int *)std::array<int,9ul>::operator[](v26, k);
    v7 = v8;
    v20 = cycDist(*v9, v8);
    if ( v20 )
      v10 = -2 * v20 * v20;
    else
      v10 = 37;
    v15 += v10;
  }
  Metric = loadMetric(a1, v7);
  if ( Metric == 93 )
  {
    v12 = 61;
  }
  else
  {
    v11 = 93 - Metric;
    if ( 93 - Metric < 0 )
      v11 = Metric - 93;
    v12 = -4 * v11;
  }
  v16 = v12 + v15;
  v18 = sealMetric(a1, v7);
  v19 = cycDist(v18, 9);
  if ( v19 )
    v13 = -3 * v19 * v19;
  else
    v13 = 41;
  return (unsigned int)(v13 + v16);
}
```
Hàm này tiếp tục gọi 5 hàm con `stressTrace`, `shearTrace`, `grainTrace`, `loadMetric`, `sealMetric` với 3 hàm đầu sẽ sử dụng tương ứng các mảng dữ liệu `OBS_STRESS`, `OBS_SHEAR`, `OBS_GRAIN`. Gọi P là mảng `PROFILE`. Ta sẽ lần lượt phân tích từng hàm một. Đầu tiên là `stressTrace`:

<img width="1087" height="273" alt="image" src="https://github.com/user-attachments/assets/d2ade7ad-5b45-44c1-87d8-7b9e10df0ef4" />

Ta thu được hệ phương trình: $(2 \times P_i + 3 \times P_{i+1}) \pmod{16} == OBS\_STRESS_i$   
Trích xuất dữ liệu mảng `OBS_STRESS` ta có: OBS_STRESS = [2, 5, 11, 10, 5, 1, 13, 4, 3, 3, 14]

Tiếp theo là `shearTrace`:

<img width="1085" height="271" alt="image" src="https://github.com/user-attachments/assets/9f0e2d96-6b8f-4be3-9afb-cb5c93f6d9b4" />

Ta thu được hệ phương trình: $P_i \oplus P_{i+2} == OBS\_SHEAR_i$   
Trích xuất dữ liệu mảng `OBS_SHEAR` ta có: OBS_SHEAR = [5, 5, 15, 8, 5, 6, 7, 4, 5, 5]

Tiếp theo là `grainTrace`:

<img width="1094" height="274" alt="image" src="https://github.com/user-attachments/assets/2b2e8112-679c-4538-abda-82f88abf0634" />

Ta thu được hệ phương trình: $(P_i + P_{i+3} - P_{i+1}) \pmod{16} == OBS\_GRAIN_i$   
Trích xuất dữ liệu mảng `OBS_GRAIN` ta có: OBS_GRAIN = [3, 11, 3, 4, 14, 4, 5, 6, 1]

Tiếp theo là `loadMetric`:

<img width="1091" height="179" alt="image" src="https://github.com/user-attachments/assets/7e774409-5558-496e-a0ee-50e958c5715f" />

Ta thu được phương trình: $\sum_{i=0}^{11} P_i == 93$

Cuối cùng là `sealMetric`:

<img width="1094" height="143" alt="image" src="https://github.com/user-attachments/assets/ffb71be9-f6d3-4976-82fb-f3117cd58e17" />

Ta thu được phương trình: $\sum_{i=0}^{11} ((i + 5) \times P_i) \pmod{16} == 9$

## Z3 Solver
Cách đơn giản nhất để giải hệ trên là đáp hết đống phương trình và điều kiện này lên Z3. Ta viết scripts Python như sau:
```python
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
    print(f"\n[+] Profile chuẩn: {result}")
else:
    print("[-] Không tìm được lời giải")
```
Chạy scripts trên, ta thu được kết quả là `PROFILE` chuẩn:

<img width="1366" height="86" alt="image" src="https://github.com/user-attachments/assets/36b20b21-cce6-41bd-bb67-30b3dbd57592" />

Cuối cùng ta chỉ việc dùng nó để lấy nốt token rồi submit là thu được Flag:

<img width="1366" height="165" alt="image" src="https://github.com/user-attachments/assets/a61462d0-5473-43ed-b12e-f65b4021d734" />

## Flag: CIT{12z4PXVTa3x3}
