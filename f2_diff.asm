section .data           ; for constant objects
  const dq 5.0

section .text
global f2_diff          ; f2_diff = 5 * x**4 = 5 * x * x * x * x
f2_diff:
  fld qword[const]
  fld qword[esp + 4]
  fld qword[esp + 4]
  fld qword[esp + 4]
  fld qword[esp + 4]
  fmulp
  fmulp
  fmulp
  fmulp
  ret
