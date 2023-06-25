section .text
global f1_diff          ; f1_diff = 2**x * ln(2)
f1_diff:
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
  fldln2
  fmulp
  ret
