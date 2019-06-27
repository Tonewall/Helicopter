	.syntax unified
	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.thumb
	.syntax unified
	.file	"provided.c"
	.text
	.align	2
	.global	waitForVBlank
	.code	16
	.thumb_func
	.type	waitForVBlank, %function
waitForVBlank:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
.L2:
	ldr	r3, .L4
	ldrh	r3, [r3]
	cmp	r3, #159
	bhi	.L2
	nop
.L3:
	ldr	r3, .L4
	ldrh	r3, [r3]
	cmp	r3, #159
	bls	.L3
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7}
	pop	{r0}
	bx	r0
.L5:
	.align	2
.L4:
	.word	67108870
	.size	waitForVBlank, .-waitForVBlank
	.align	2
	.global	drawFullscreenImage3
	.code	16
	.thumb_func
	.type	drawFullscreenImage3, %function
drawFullscreenImage3:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, .L7
	ldr	r2, [r7, #4]
	str	r2, [r3]
	ldr	r2, .L7
	ldr	r3, .L7+4
	ldr	r3, [r3]
	str	r3, [r2, #4]
	ldr	r3, .L7
	ldr	r2, .L7+8
	str	r2, [r3, #8]
	nop
	mov	sp, r7
	add	sp, sp, #8
	@ sp needed
	pop	{r7}
	pop	{r0}
	bx	r0
.L8:
	.align	2
.L7:
	.word	67109076
	.word	videoBuffer
	.word	-2147445248
	.size	drawFullscreenImage3, .-drawFullscreenImage3
	.ident	"GCC: (15:5.4.1+svn241155-1) 5.4.1 20160919"
