.thumb
.global ItemTypeWTA
.type ItemTypeWTA, %function

@attack struct is passed in via r0 with the defense struct in r1
ItemTypeWTA:
push {r4-r7,r14}

mov r4,r0
mov r5,r1

mov r0,r4
add r0,#0x4A
ldrh r0,[r0]
mov r2,#0xFF
and r0,r2

mov		r1,r5
add 	r1,#0x50
ldrh 	r1,[r1]
cmp 	r1, #0xFF		@if no weapon, end
beq 	End

ldr r3,=ItemTypeWTAList

LoopStart:
ldrb r2,[r3]
cmp r2,#0
beq CheckDefender

cmp r2,r0
bne LoopRestart

ldrb r2,[r3,#1]
cmp r2,r1
beq SetWTAStuff

LoopRestart:
add r3,#4
b LoopStart

SetWTAStuff:
ldrb r0,[r3,#2]
ldrb r1,[r3,#3]

mov r3,r4
add r3,#0x53
ldrb r2,[r3]
add r2,r0
strb r2,[r3]
add r3,#1
ldrb r2,[r3]
add r2,r1
strb r2,[r3]

mov r3,r5
add r3,#0x53
ldrb r2,[r3]
sub r2,r0
strb r2,[r3]
add r3,#1
ldrb r2,[r3]
sub r2,r1
strb r2,[r3]

@ defender side
CheckDefender:

mov r6,r4
mov r4,r5
mov r5,r6


mov r0,r4
add r0,#0x4A
ldrh r0,[r0]
mov r2,#0xFF
and r0,r2

mov		r1,r5
add 	r1,#0x50
ldrh 	r1,[r1]
cmp 	r1, #0xFF		@if no weapon, end
beq 	End

ldr r3,=ItemTypeWTAList

LoopStart2:
ldrb r2,[r3]
cmp r2,#0
beq End

cmp r2,r0
bne LoopRestart2

ldrb r2,[r3,#1]
cmp r2,r1
beq SetWTAStuff2

LoopRestart2:
add r3,#4
b LoopStart2

SetWTAStuff2:
ldrb r0,[r3,#2]
ldrb r1,[r3,#3]

mov r3,r4
add r3,#0x53
ldrb r2,[r3]
add r2,r0
strb r2,[r3]
add r3,#1
ldrb r2,[r3]
add r2,r1
strb r2,[r3]

mov r3,r5
add r3,#0x53
ldrb r2,[r3]
sub r2,r0
strb r2,[r3]
add r3,#1
ldrb r2,[r3]
sub r2,r1
strb r2,[r3]


End:
pop {r4-r7}
pop {r0}
bx r0

.ltorg
.align

