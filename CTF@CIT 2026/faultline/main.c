int __fastcall main(int argc, const char **argv, const char **envp)
{
  int v5; // ebx
  char v8; // bl
  std::ostream *v9; // rax
  __int64 v10; // rbx
  std::ostream *v11; // rax
  char v14; // bl
  __int64 v15; // rbx
  unsigned int v16; // eax
  std::ostream *v17; // rax
  __int64 v18; // rbx
  unsigned int v19; // eax
  std::ostream *v20; // rax
  char v23; // bl
  std::ostream *v24; // rax
  char v28; // r12
  char v29; // r13
  bool v30; // r15
  std::ostream *v31; // rax
  __int64 v32; // rax
  std::ostream *v33; // rax
  std::ostream *v34; // rax
  __int64 v35; // rax
  std::ostream *v36; // rax
  __int64 v37; // rax
  std::ostream *v38; // rax
  char v41; // bl
  _DWORD *v42; // rax
  int v43; // ebx
  char *v44; // rax
  std::ostream *v45; // rax
  __int64 v46; // rax
  std::ostream *v47; // rax
  __int64 v48; // rbx
  std::ostream *v49; // rax
  std::ostream *v51; // rax
  char v53; // [rsp+12h] [rbp-18Eh] BYREF
  char v54; // [rsp+13h] [rbp-18Dh] BYREF
  signed int v55; // [rsp+14h] [rbp-18Ch]
  int v56; // [rsp+18h] [rbp-188h]
  unsigned int v57; // [rsp+1Ch] [rbp-184h]
  int v58; // [rsp+20h] [rbp-180h]
  unsigned int v59; // [rsp+24h] [rbp-17Ch]
  unsigned int v60; // [rsp+28h] [rbp-178h]
  unsigned int v61; // [rsp+2Ch] [rbp-174h]
  int *v62; // [rsp+30h] [rbp-170h]
  __m256 *v63; // [rsp+38h] [rbp-168h]
  __int64 v64; // [rsp+40h] [rbp-160h]
  char *v65; // [rsp+48h] [rbp-158h]
  char *v66; // [rsp+50h] [rbp-150h]
  char *v67; // [rsp+58h] [rbp-148h]
  char *v68; // [rsp+60h] [rbp-140h]
  char *v69; // [rsp+68h] [rbp-138h]
  char *v70; // [rsp+70h] [rbp-130h]
  char *v71; // [rsp+78h] [rbp-128h]
  char *v72; // [rsp+80h] [rbp-120h]
  char *v73; // [rsp+88h] [rbp-118h]
  char *v74; // [rsp+90h] [rbp-110h]
  char *v75; // [rsp+98h] [rbp-108h]
  _BYTE v76[32]; // [rsp+A0h] [rbp-100h] BYREF
  _BYTE v77[32]; // [rsp+C0h] [rbp-E0h] BYREF
  _BYTE v78[32]; // [rsp+E0h] [rbp-C0h] BYREF
  __m256i v79; // [rsp+100h] [rbp-A0h] BYREF
  __m256 v81; // [rsp+130h] [rbp-70h] BYREF
  unsigned __int64 v83; // [rsp+168h] [rbp-38h]

  v83 = __readfsqword(0x28u);
  touchVisibleProtections();
  if ( argc > 1 )
  {
    v65 = &v54;
    std::string::basic_string<std::allocator<char>>(v76, argv[1], &v54);
    std::__new_allocator<char>::~__new_allocator(&v54);
    if ( (unsigned __int8)std::operator==<char>(v76, "notes") )
    {
      printNotes();
      v5 = 0;
LABEL_65:
      std::string::~string(v76);
      return v5;
    }
    if ( (unsigned __int8)std::operator==<char>(v76, "score") && argc == 3 )
    {
      __asm
      {
        vpxor   xmm0, xmm0, xmm0
        vmovdqu [rsp+1A0h+var_70], ymm0
        vmovdqa [rsp+1A0h+var_50], xmm0
      }
      v66 = &v54;
      std::string::basic_string<std::allocator<char>>(&v79, argv[2], &v54);
      v8 = parseProfile(&v79, &v81) ^ 1;
      std::string::~string(&v79);
      std::__new_allocator<char>::~__new_allocator(&v54);
      if ( !v8 )
      {
        v61 = computeFaultlineScoreVisible(&v81);
        v9 = (std::ostream *)std::ostream::operator<<(&std::cout, v61);
        v10 = std::operator<<<std::char_traits<char>>(v9);
        gradeBandVisible((int)&v79);
        v11 = (std::ostream *)std::operator<<<char>(v10, &v79);
        std::operator<<<std::char_traits<char>>(v11);
        std::string::~string(&v79);
        v5 = 0;
        goto LABEL_65;
      }
    }
    else if ( (unsigned __int8)std::operator==<char>(v76, "trace") && argc == 3 )
    {
      __asm
      {
        vpxor   xmm0, xmm0, xmm0
        vmovdqu [rsp+1A0h+var_70], ymm0
        vmovdqa [rsp+1A0h+var_50], xmm0
      }
      v67 = &v54;
      std::string::basic_string<std::allocator<char>>(&v79, argv[2], &v54);
      v14 = parseProfile(&v79, &v81) ^ 1;
      std::string::~string(&v79);
      std::__new_allocator<char>::~__new_allocator(&v54);
      if ( !v14 )
      {
        stressTrace(&v79, &v81);
        printVec<11ul>("stress", &v79);
        shearTrace(&v79, &v81);
        printVec<10ul>("shear ", &v79);
        grainTrace(&v79, &v81);
        printVec<9ul>("grain ", &v79);
        v15 = std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
        v16 = loadMetric(&v81, "load: ");
        v17 = (std::ostream *)std::ostream::operator<<(v15, v16);
        std::operator<<<std::char_traits<char>>(v17);
        v18 = std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
        v19 = sealMetric(&v81, "seal: ");
        v20 = (std::ostream *)std::ostream::operator<<(v18, v19);
        std::operator<<<std::char_traits<char>>(v20);
        v5 = 0;
        goto LABEL_65;
      }
    }
    else if ( (unsigned __int8)std::operator==<char>(v76, "token") && argc == 3 )
    {
      __asm
      {
        vpxor   xmm0, xmm0, xmm0
        vmovdqu [rsp+1A0h+var_70], ymm0
        vmovdqa [rsp+1A0h+var_50], xmm0
      }
      v68 = &v54;
      std::string::basic_string<std::allocator<char>>(&v79, argv[2], &v54);
      v23 = parseProfile(&v79, &v81) ^ 1;
      std::string::~string(&v79);
      std::__new_allocator<char>::~__new_allocator(&v54);
      if ( !v23 )
      {
        buildSurveyTokenVisible(&v79, &v81);
        v24 = (std::ostream *)std::operator<<<char>(&std::cout, &v79);
        std::operator<<<std::char_traits<char>>(v24);
        std::string::~string(&v79);
        v5 = 0;
        goto LABEL_65;
      }
    }
    else
    {
      if ( (unsigned __int8)std::operator==<char>(v76, "compare") && argc == 4 )
      {
        __asm
        {
          vpxor   xmm0, xmm0, xmm0
          vmovdqu [rsp+1A0h+var_A0], ymm0
          vmovdqa [rsp+1A0h+var_80], xmm0
          vpxor   xmm0, xmm0, xmm0
          vmovdqu [rsp+1A0h+var_70], ymm0
          vmovdqa [rsp+1A0h+var_50], xmm0
        }
        v28 = 0;
        v29 = 0;
        v69 = &v53;
        std::string::basic_string<std::allocator<char>>(v77, argv[2], &v53);
        v30 = true;
        if ( (unsigned __int8)parseProfile(v77, &v79) == 1 )
        {
          v70 = &v54;
          v28 = 1;
          std::string::basic_string<std::allocator<char>>(v78, argv[3], &v54);
          v29 = 1;
          if ( (unsigned __int8)parseProfile(v78, &v81) == 1 )
            v30 = false;
        }
        if ( v29 )
          std::string::~string(v78);
        if ( v28 )
          std::__new_allocator<char>::~__new_allocator(&v54);
        std::string::~string(v77);
        std::__new_allocator<char>::~__new_allocator(&v53);
        if ( v30 )
        {
          std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
          v5 = 1;
        }
        else
        {
          v59 = computeFaultlineScoreVisible(&v79);
          v60 = computeFaultlineScoreVisible(&v81);
          v31 = (std::ostream *)std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
          v32 = std::operator<<<std::char_traits<char>>(v31);
          v33 = (std::ostream *)std::ostream::operator<<(v32, v59);
          std::operator<<<std::char_traits<char>>(v33);
          v34 = (std::ostream *)std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
          v35 = std::operator<<<std::char_traits<char>>(v34);
          v36 = (std::ostream *)std::ostream::operator<<(v35, v60);
          std::operator<<<std::char_traits<char>>(v36);
          v37 = std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
          v38 = (std::ostream *)std::ostream::operator<<(v37, v60 - v59);
          std::operator<<<std::char_traits<char>>(v38);
          v5 = 0;
        }
        goto LABEL_65;
      }
      if ( !(unsigned __int8)std::operator==<char>(v76, "nudge") || argc != 5 )
      {
        if ( (unsigned __int8)std::operator==<char>(v76, "submit") && argc == 4 )
        {
          v74 = &v54;
          std::string::basic_string<std::allocator<char>>(&v79, argv[3], &v54);
          v75 = &v53;
          std::string::basic_string<std::allocator<char>>(v78, argv[2], &v53);
          validate(&v81, v78, &v79);
          v51 = (std::ostream *)std::operator<<<char>(&std::cout, &v81);
          std::operator<<<std::char_traits<char>>(v51);
          std::string::~string(&v81);
          std::string::~string(v78);
          std::__new_allocator<char>::~__new_allocator(&v53);
          std::string::~string(&v79);
          std::__new_allocator<char>::~__new_allocator(&v54);
          v5 = 0;
        }
        else
        {
          printUsage(*argv);
          v5 = 1;
        }
        goto LABEL_65;
      }
      __asm
      {
        vpxor   xmm0, xmm0, xmm0
        vmovdqu [rsp+1A0h+var_70], ymm0
        vmovdqa [rsp+1A0h+var_50], xmm0
      }
      v71 = &v54;
      std::string::basic_string<std::allocator<char>>(&v79, argv[2], &v54);
      v41 = parseProfile(&v79, &v81) ^ 1;
      std::string::~string(&v79);
      std::__new_allocator<char>::~__new_allocator(&v54);
      if ( !v41 )
      {
        v72 = &v54;
        std::string::basic_string<std::allocator<char>>(&v79, argv[3], &v54);
        v55 = std::stoi(&v79, 0, 10);
        std::string::~string(&v79);
        std::__new_allocator<char>::~__new_allocator(&v54);
        v73 = &v54;
        std::string::basic_string<std::allocator<char>>(&v79, argv[4], &v54);
        v56 = std::stoi(&v79, 0, 10);
        std::string::~string(&v79);
        std::__new_allocator<char>::~__new_allocator(&v54);
        if ( (unsigned int)v55 < 0xC && v56 >= -15 && v56 <= 15 )
        {
          v42 = (_DWORD *)std::array<int,12ul>::operator[](&v81, v55);
          v43 = ((unsigned __int8)*v42 + (_BYTE)v56) & 0xF;
          *(_DWORD *)std::array<int,12ul>::operator[](&v81, v55) = v43;
          std::string::basic_string(v78);
          std::string::reserve(v78, 12);
          v63 = &v81;
          v62 = (int *)std::array<int,12ul>::begin(&v81);
          v64 = std::array<int,12ul>::end(v63);
          while ( v62 != (int *)v64 )
          {
            v58 = *v62;
            v44 = (char *)std::string::operator[](&ALPHABET, v58);
            std::string::push_back(v78, (unsigned int)*v44);
            ++v62;
          }
          v57 = computeFaultlineScoreVisible(&v81);
          v45 = (std::ostream *)std::operator<<<char>(&std::cout, v78);
          v46 = std::operator<<<std::char_traits<char>>(v45);
          v47 = (std::ostream *)std::ostream::operator<<(v46, v57);
          v48 = std::operator<<<std::char_traits<char>>(v47);
          gradeBandVisible((int)&v79);
          v49 = (std::ostream *)std::operator<<<char>(v48, &v79);
          std::operator<<<std::char_traits<char>>(v49);
          std::string::~string(&v79);
          v5 = 0;
          std::string::~string(v78);
          goto LABEL_65;
        }
      }
    }
    std::operator<<<std::char_traits<char>>((std::ostream *)&std::cout);
    v5 = 1;
    goto LABEL_65;
  }
  printUsage(*argv);
  return 0;
}
