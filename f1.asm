section .text
global f1               ; f1 = 2**x + 1
f1:
  fld qword[esp + 4]
  fld qword[esp + 4]
  fld qword[esp + 4]
  frndint
  fsubp
  f2xm1
  fld1
  faddp
  fscale
  fstp st1
  fld1
  faddp
  ret
