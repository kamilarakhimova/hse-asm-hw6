section .rodata           ; for constant objects
  const dq 3.0

section .text
global f3                 ; f3 = (1 - x) / 3
f3:
  fld1
  fld qword[esp + 4]
  fsubp
  fld qword[const]
  fdivp
  ret
