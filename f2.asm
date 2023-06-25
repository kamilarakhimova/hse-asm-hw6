section .text
global f2               ; f2 = x**5 = x * x * x * x * x
f2:
  fld qword[esp + 4]
  fld qword[esp + 4]
  fld qword[esp + 4]
  fld qword[esp + 4]
  fld qword[esp + 4]
  fmulp
  fmulp
  fmulp
  fmulp
  ret
