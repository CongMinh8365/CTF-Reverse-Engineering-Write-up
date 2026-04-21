unsigned __int64 __fastcall maintenanceConsole()
{
  _QWORD *v0; // rax
  int v1; // ebx
  std::ostream *v2; // rbx
  std::ostream *v3; // rax
  std::ostream *v4; // rbx
  std::ostream *v5; // rax
  char v7; // [rsp+Fh] [rbp-B1h] BYREF
  char *v8; // [rsp+10h] [rbp-B0h]
  char *v9; // [rsp+18h] [rbp-A8h]
  _BYTE v10[32]; // [rsp+20h] [rbp-A0h] BYREF
  _BYTE v11[32]; // [rsp+40h] [rbp-80h] BYREF
  _BYTE v12[32]; // [rsp+60h] [rbp-60h] BYREF
  _BYTE v13[40]; // [rsp+80h] [rbp-40h] BYREF
  unsigned __int64 v14; // [rsp+A8h] [rbp-18h]

  v14 = __readfsqword(0x28u);
  std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout, (__int64)"\n[maintenance shell]\n");
  std::operator<<<std::char_traits<char>>(
    (std::ostream *)&std::cout,
    (__int64)"commands: help, mirror, hush, decode, reset, back\n");
  do
  {
    std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout, (__int64)"svc> ");
    std::string::basic_string(v10, "svc> ");
    v0 = (_QWORD *)std::getline<char,std::char_traits<char>,std::allocator<char>>((std::istream *)&std::cin);
    if ( (unsigned __int8)std::ios::operator!((char *)v0 + *(_QWORD *)(*v0 - 24LL), v10) )
    {
      v1 = 0;
    }
    else if ( (unsigned __int8)std::operator==<char>(v10, "back") )
    {
      v1 = 0;
    }
    else
    {
      if ( (unsigned __int8)std::operator==<char>(v10, "help") )
      {
        std::operator<<<std::char_traits<char>>(
          (std::ostream *)&std::cout,
          (__int64)"mirror -> attempt to arm inspection relay\n");
        std::operator<<<std::char_traits<char>>(
          (std::ostream *)&std::cout,
          (__int64)"hush   -> mute alarm speaker if the room is staged correctly\n");
        std::operator<<<std::char_traits<char>>(
          (std::ostream *)&std::cout,
          (__int64)"decode -> print decoded maintenance hints when available\n");
        std::operator<<<std::char_traits<char>>(
          (std::ostream *)&std::cout,
          (__int64)"reset  -> drop maintenance-only flags\n");
      }
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
      else if ( (unsigned __int8)std::operator==<char>(v10, "decode") )
      {
        v2 = std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout, (__int64)"[decode] ");
        v8 = &v7;
        std::string::basic_string<std::allocator<char>>(
          v11,
          "[patch/02] Apply the door patch twice. The third write trips watchdog.",
          &v7);
        reverseCopy(v12, v11);
        reverseCopy(v13, v12);
        v3 = (std::ostream *)std::operator<<<char>(v2, v13);
        std::operator<<<std::char_traits<char>>(v3, (__int64)"\n");
        std::string::~string(v13);
        std::string::~string(v12);
        std::string::~string(v11);
        std::__new_allocator<char>::~__new_allocator(&v7);
        v4 = std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout, (__int64)"[decode] ");
        v9 = &v7;
        std::string::basic_string<std::allocator<char>>(v11, "[svc/01] Mirror first. Then hush.", &v7);
        rot13Copy(v12, v11);
        rot13Copy(v13, v12);
        v5 = (std::ostream *)std::operator<<<char>(v4, v13);
        std::operator<<<std::char_traits<char>>(v5, (__int64)"\n");
        std::string::~string(v13);
        std::string::~string(v12);
        std::string::~string(v11);
        std::__new_allocator<char>::~__new_allocator(&v7);
        if ( byte_5D90F1 )
          std::operator<<<std::char_traits<char>>(
            (std::ostream *)&std::cout,
            (__int64)"[decode] inspection confirms reflected and rotated maintenance text paths.\n");
        else
          std::operator<<<std::char_traits<char>>(
            (std::ostream *)&std::cout,
            (__int64)"[decode] mirror relay not armed; deeper inspection unavailable.\n");
      }
      else if ( (unsigned __int8)std::operator==<char>(v10, "reset") )
      {
        byte_5D90F1 = 0;
        byte_5D90F2 = 0;
        std::operator<<<std::char_traits<char>>(
          (std::ostream *)&std::cout,
          (__int64)"[svc] maintenance-only flags dropped.\n");
      }
      else
      {
        std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout, (__int64)"[svc] unknown command.\n");
      }
      v1 = 1;
    }
    std::string::~string(v10);
  }
  while ( v1 == 1 );
  return v14 - __readfsqword(0x28u);
}