.thumb
.align

.global ObscuredTerrainFogHook
.type ObscuredTerrainFogHook, %function

.equ MapAddInRange,0x801AABD
.macro blh to, reg
    ldr \reg, =\to
    mov lr, \reg
    .short 0xF800
.endm

ObscuredTerrainFogHook: //hook @ 19FEC
mov r2,r0
mov r0,r4
mov r1,r5
mov r3,#1
push {r4}
blh MapAddInRange, r4
pop {r4}
bl ClearObscuredTerrainFromFogMap
ldr r0,=#0x8019FF9
bx r0

.ltorg
.align

