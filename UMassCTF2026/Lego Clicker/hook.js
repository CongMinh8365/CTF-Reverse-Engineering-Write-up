Java.perform(function() {
    console.log("[*] Dang trien khai Radar tim kiem ClassLoader...");

    var found = false;
    Java.enumerateClassLoaders({
        onMatch: function(loader) {
            try {
                if (loader.findClass("com.example.LegoClicker.SessionValidator")) {
                    console.log("[+] Tim thay ClassLoader: " + loader);
                    Java.classFactory.loader = loader; 
                    found = true;
                    
                    // CÚ ĐẤM XUYÊN THỦNG LAZY LOAD (Chuẩn Java 100%)
                    // Ép JVM nạp class và bắt buộc chạy khối static {} ngay lập tức
                    var Class = Java.use("java.lang.Class");
                    Class.forName("com.example.LegoClicker.SessionValidator", true, loader);
                    console.log("[+] Da ep chay khoi static, liblegocore.so DA VAO RAM!");

                    // Lúc này file .so chắc chắn 100% đã có mặt
                    var targetModule = Process.findModuleByName("liblegocore.so");
                    if (targetModule) {
                        console.log("[+] Da tim thay liblegocore.so tai: " + targetModule.base);
                        var antiDebugTarget = targetModule.base.add(0x21E80);
                        Interceptor.attach(antiDebugTarget, {
                            onLeave: function(retval) {
                                console.log("[!] Phat hien Anti-Debug! Da ep tra ve 0.");
                                retval.replace(ptr(0));
                            }
                        });

                        var SessionValidator = Java.use("com.example.LegoClicker.SessionValidator");
                        console.log("[*] Buoc 3: Ép điểm Top 1 Sever và lấy cờ xịn...");
                        
                        var score = int64("1000000000000000"); // 15 số 0 (1 Triệu Tỷ)
                        var magic_j8 = int64("4521136641424654587"); // Mã tương ứng
                        
                        var flag = SessionValidator.syncBrickCache(score, magic_j8);
                        console.log("\n==================================");
                        console.log("[!] BINGO! CỜ XỊN TOP 1 CỦA ÔNG ĐÂY: " + flag);
                        console.log("==================================\n");
                    } else {
                        console.log("[-] Loi: Khong the tin duoc, van khong thay .so!");
                    }
                }
            } catch (e) {}
        },
        onComplete: function() {
            if (!found) {
                console.log("[-] Van chua thay class. Ong quay sang Nox BAM VAO NÚT LEADERBOARD di!");
            }
        }
    });
});