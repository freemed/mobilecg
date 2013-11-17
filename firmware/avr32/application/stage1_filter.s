	.file	"stage1_filter.cpp"
	.section	.text._Z17Stage1Filter_initP12Stage1Filter,"ax",@progbits
	.align	1
	.global	_Z17Stage1Filter_initP12Stage1Filter
	.type	_Z17Stage1Filter_initP12Stage1Filter, @function
_Z17Stage1Filter_initP12Stage1Filter:
.LFB0:
	# args = 0, frame = 0, pretend = 0
	# frame_needed = 0, leaf_function = 1
	# uses_anonymous_args = 0
	mov	r8, 0
	mov	r9, r8
.L2:
	st.w	r12[r8], r9
	sub     r8, -4
	cp.w	r8, 128
	brne .L2
	st.w	r12[128], r9
	retal	r12
.LFE0:
	.size	_Z17Stage1Filter_initP12Stage1Filter, .-_Z17Stage1Filter_initP12Stage1Filter
	.section	.text._Z16Stage1Filter_putP12Stage1Filteri,"ax",@progbits
	.align	1
	.global	_Z16Stage1Filter_putP12Stage1Filteri
	.type	_Z16Stage1Filter_putP12Stage1Filteri, @function
_Z16Stage1Filter_putP12Stage1Filteri:
.LFB1:
	# args = 0, frame = 0, pretend = 0
	# frame_needed = 0, leaf_function = 1
	# uses_anonymous_args = 0
	ld.w	r8, r12[128]
	sub     r9, r8, -1
	bfextu	r8, r8, 0, 5
	st.w	r12[128], r9
	st.w	r12[r8 << 2], r11
	retal	r12
.LFE1:
	.size	_Z16Stage1Filter_putP12Stage1Filteri, .-_Z16Stage1Filter_putP12Stage1Filteri
	.section	.text._Z16Stage1Filter_getP12Stage1Filter,"ax",@progbits
	.align	1
	.global	_Z16Stage1Filter_getP12Stage1Filter
	.type	_Z16Stage1Filter_getP12Stage1Filter, @function
_Z16Stage1Filter_getP12Stage1Filter:
.LFB2:
	# args = 0, frame = 116, pretend = 0
	# frame_needed = 0, leaf_function = 1
	# uses_anonymous_args = 0
	pushm	r0-r3, r4-r7, lr
.LCFI0:
	sub     sp, 116
.LCFI1:
	lda.w	r8, .LANCHOR0
	ld.w	r1, r12[128]
	ld.w	r10, r8[0]
	bfextu	r9, r1, 0, 5
	ld.w	r9, r12[r9 << 2]
	muls.d  r6, r10, r9
	sub     r1, 1
	st.d	sp[24], r6
	sub     r2, r1, 1
	sub     r3, r2, 1
	sub     r4, r3, 1
	sub     r5, r4, 1
	sub     r6, r5, 1
	sub     r7, r6, 1
	sub     lr, r7, 1
	sub     r0, lr, 1
	stdsp	sp[0], r0
	sub     r0, 1
	stdsp	sp[4], r0
	mov	r9, r0
	sub     r0, 21
	sub     r9, 1
	bfextu	r0, r0, 0, 5
	sub     r10, r9, 1
	ld.w	r0, r12[r0 << 2]
	stdsp	sp[104], r10
	sub     r10, 1
	stdsp	sp[100], r10
	sub     r10, 1
	stdsp	sp[96], r10
	sub     r10, 1
	stdsp	sp[92], r10
	sub     r10, 1
	stdsp	sp[88], r10
	sub     r10, 1
	stdsp	sp[84], r10
	sub     r10, 1
	stdsp	sp[80], r10
	sub     r10, 1
	stdsp	sp[76], r10
	sub     r10, 1
	stdsp	sp[72], r10
	sub     r10, 1
	stdsp	sp[68], r10
	sub     r10, 1
	stdsp	sp[64], r10
	sub     r10, 1
	stdsp	sp[60], r10
	sub     r10, 1
	stdsp	sp[56], r10
	sub     r10, 1
	stdsp	sp[52], r10
	sub     r10, 1
	stdsp	sp[48], r10
	sub     r10, 1
	stdsp	sp[44], r10
	sub     r10, 1
	stdsp	sp[40], r10
	sub     r10, 1
	stdsp	sp[36], r10
	sub     r10, 1
	ld.w	r11, r8[4]
	stdsp	sp[32], r10
	stdsp	sp[112], r0
	bfextu	r1, r1, 0, 5
	ld.w	r0, r8[8]
	ld.w	r10, r12[r1 << 2]
	stdsp	sp[108], r0
	muls.d  r0, r11, r10
	ld.d	r10, sp[24]
	add     r0, r10
	adc    r1, r1, r11
	st.d	sp[16], r0
	ld.w	r10, r8[12]
	bfextu	r2, r2, 0, 5
	stdsp	sp[24], r10
	ld.w	r1, r12[r2 << 2]
	lddsp	r10, sp[108]
	muls.d  r10, r10, r1
	ld.d	r0, sp[16]
	add     r0, r10
	adc    r1, r1, r11
	bfextu	r3, r3, 0, 5
	st.d	sp[16], r0
	ld.w	r0, r8[16]
	ld.w	r1, r12[r3 << 2]
	lddsp	r11, sp[24]
	ld.d	r2, sp[16]
	stdsp	sp[108], r0
	muls.d  r0, r11, r1
	add     r2, r0
	adc    r3, r3, r1
	st.d	sp[16], r2
	ld.w	r2, r8[20]
	lddsp	r11, sp[108]
	stdsp	sp[24], r2
	bfextu	r4, r4, 0, 5
	ld.d	r2, sp[16]
	ld.w	r1, r12[r4 << 2]
	muls.d  r0, r11, r1
	add     r2, r0
	adc    r3, r3, r1
	ld.w	r4, r8[24]
	st.d	sp[16], r2
	lddsp	r0, sp[24]
	ld.d	r10, sp[16]
	bfextu	r5, r5, 0, 5
	ld.w	r1, r12[r5 << 2]
	muls.d  r2, r0, r1
	add     r2, r10, r2
	adc    r3, r11, r3
	ld.w	r5, r8[28]
	bfextu	r6, r6, 0, 5
	bfextu	r7, r7, 0, 5
	ld.w	r1, r12[r6 << 2]
	muls.d  r0, r4, r1
	add     r0, r2, r0
	adc    r1, r3, r1
	ld.w	r3, r12[r7 << 2]
	muls.d  r4, r5, r3
	ld.w	r6, r8[32]
	add     r0, r4
	adc    r1, r1, r5
	bfextu	lr, lr, 0, 5
	ld.w	r5, r12[lr << 2]
	muls.d  r4, r6, r5
	ld.w	r7, r8[36]
	add     r0, r4
	adc    r1, r1, r5
	lddsp	r10, sp[0]
	bfextu	r11, r10, 0, 5
	ld.w	r5, r12[r11 << 2]
	muls.d  r6, r7, r5
	add     r0, r6
	adc    r1, r1, r7
	lddsp	r7, sp[4]
	ld.w	lr, r8[40]
	bfextu	r10, r7, 0, 5
	ld.w	r7, r12[r10 << 2]
	muls.d  r6, lr, r7
	ld.w	r11, r8[44]
	add     r0, r6
	adc    r1, r1, r7
	bfextu	r9, r9, 0, 5
	ld.w	r7, r12[r9 << 2]
	muls.d  r6, r11, r7
	ld.w	r10, r8[48]
	add     r0, r6
	adc    r1, r1, r7
	lddsp	r6, sp[104]
	lddsp	r3, sp[100]
	bfextu	r11, r6, 0, 5
	ld.w	r7, r12[r11 << 2]
	muls.d  r6, r10, r7
	bfextu	r10, r3, 0, 5
	ld.w	r9, r8[52]
	ld.w	r11, r12[r10 << 2]
	muls.d  r10, r9, r11
	add     r0, r6
	adc    r1, r1, r7
	lddsp	r2, sp[96]
	ld.w	r6, r8[56]
	add     r0, r10
	adc    r1, r1, r11
	bfextu	r9, r2, 0, 5
	ld.w	r11, r12[r9 << 2]
	muls.d  r10, r6, r11
	add     r0, r10
	adc    r1, r1, r11
	lddsp	r11, sp[92]
	bfextu	r9, r11, 0, 5
	ld.w	r5, r8[60]
	ld.w	r11, r12[r9 << 2]
	lddsp	r10, sp[88]
	muls.d  r4, r5, r11
	bfextu	r9, r10, 0, 5
	ld.w	lr, r8[64]
	ld.w	r11, r12[r9 << 2]
	add     r0, r4
	adc    r1, r1, r5
	muls.d  r10, lr, r11
	ld.w	r4, r8[68]
	lddsp	r7, sp[84]
	bfextu	r9, r7, 0, 5
	ld.w	r5, r12[r9 << 2]
	muls.d  r4, r4, r5
	add     r0, r10
	adc    r1, r1, r11
	lddsp	r6, sp[80]
	ld.w	r10, r8[72]
	add     r0, r4
	adc    r1, r1, r5
	ld.w	r9, r8[76]
	bfextu	r11, r6, 0, 5
	ld.w	r5, r12[r11 << 2]
	muls.d  r4, r10, r5
	lddsp	r3, sp[76]
	add     r0, r4
	adc    r1, r1, r5
	bfextu	r10, r3, 0, 5
	lddsp	r2, sp[72]
	ld.w	r5, r12[r10 << 2]
	muls.d  r4, r9, r5
	bfextu	r9, r2, 0, 5
	ld.w	r7, r8[80]
	add     r0, r4
	adc    r1, r1, r5
	lddsp	r11, sp[68]
	ld.w	r5, r12[r9 << 2]
	bfextu	r9, r11, 0, 5
	muls.d  r4, r7, r5
	ld.w	r6, r8[84]
	add     r0, r4
	adc    r1, r1, r5
	lddsp	r10, sp[64]
	ld.w	r5, r12[r9 << 2]
	bfextu	r9, r10, 0, 5
	muls.d  r4, r6, r5
	ld.w	lr, r8[88]
	add     r0, r4
	adc    r1, r1, r5
	lddsp	r7, sp[60]
	ld.w	r5, r12[r9 << 2]
	bfextu	r9, r7, 0, 5
	muls.d  r4, lr, r5
	ld.w	r11, r8[92]
	add     r0, r4
	adc    r1, r1, r5
	ld.w	r10, r8[96]
	ld.w	r5, r12[r9 << 2]
	lddsp	r6, sp[56]
	bfextu	r9, r6, 0, 5
	ld.w	r3, r12[r9 << 2]
	muls.d  r2, r10, r3
	muls.d  r4, r11, r5
	add     r0, r4
	adc    r1, r1, r5
	add     r0, r2
	adc    r1, r1, r3
	lddsp	r3, sp[52]
	bfextu	r9, r3, 0, 5
	ld.w	r4, r8[100]
	ld.w	r3, r12[r9 << 2]
	muls.d  r2, r4, r3
	add     r2, r0, r2
	adc    r3, r1, r3
	lddsp	r1, sp[48]
	bfextu	r9, r1, 0, 5
	ld.w	r9, r12[r9 << 2]
	ld.w	r11, r8[104]
	lddsp	r0, sp[44]
	muls.d  r10, r11, r9
	bfextu	r9, r0, 0, 5
	ld.w	r9, r12[r9 << 2]
	ld.w	r7, r8[108]
	add     r2, r10
	adc    r3, r3, r11
	muls.d  r6, r7, r9
	ld.w	r11, r8[112]
	lddsp	lr, sp[40]
	bfextu	r9, lr, 0, 5
	ld.w	r9, r12[r9 << 2]
	muls.d  r10, r11, r9
	ld.w	r5, r8[116]
	add     r2, r6
	adc    r3, r3, r7
	lddsp	r9, sp[112]
	add     r2, r10
	adc    r3, r3, r11
	ld.w	r7, r8[120]
	lddsp	r6, sp[36]
	ld.w	r11, r8[124]
	bfextu	r8, r6, 0, 5
	ld.w	r8, r12[r8 << 2]
	muls.d  r10, r11, r9
	muls.d  r4, r5, r8
	add     r8, r2, r4
	adc    r9, r3, r5
	lddsp	r3, sp[32]
	bfextu	lr, r3, 0, 5
	ld.w	r12, r12[lr << 2]
	muls.d  r6, r7, r12
	add     r8, r6
	adc    r9, r9, r7
	add     r8, r10
	adc    r9, r9, r11
	mov	r12, r9
	sub	sp, -116 # Reset Frame Pointer
	popm	r0-r3, r4-r7, pc
	.cpool
	.align	2
.L10:
.LFE2:
	.size	_Z16Stage1Filter_getP12Stage1Filter, .-_Z16Stage1Filter_getP12Stage1Filter
	.data
	.align	2
	.set	.LANCHOR0,. + 0
	.type	_ZL11filter_taps, @object
	.size	_ZL11filter_taps, 128
_ZL11filter_taps:
	.align 2
	.int	1161859
	.align 2
	.int	3958452
	.align 2
	.int	8271341
	.align 2
	.int	11706547
	.align 2
	.int	9506031
	.align 2
	.int	-3694568
	.align 2
	.int	-29961744
	.align 2
	.int	-63515426
	.align 2
	.int	-88355557
	.align 2
	.int	-80810086
	.align 2
	.int	-17759765
	.align 2
	.int	111922474
	.align 2
	.int	297875833
	.align 2
	.int	506192823
	.align 2
	.int	687519156
	.align 2
	.int	793229255
	.align 2
	.int	793229255
	.align 2
	.int	687519156
	.align 2
	.int	506192823
	.align 2
	.int	297875833
	.align 2
	.int	111922474
	.align 2
	.int	-17759765
	.align 2
	.int	-80810086
	.align 2
	.int	-88355557
	.align 2
	.int	-63515426
	.align 2
	.int	-29961744
	.align 2
	.int	-3694568
	.align 2
	.int	9506031
	.align 2
	.int	11706547
	.align 2
	.int	8271341
	.align 2
	.int	3958452
	.align 2
	.int	1161859
	.section	.debug_frame,"",@progbits
.Lframe0:
	.int	.LECIE0-.LSCIE0
.LSCIE0:
	.int	0xffffffff
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.byte	0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0x0
	.align	2
.LECIE0:
.LSFDE0:
	.int	.LEFDE0-.LASFDE0
.LASFDE0:
	.int	.Lframe0
	.int	.LFB0
	.int	.LFE0-.LFB0
	.align	2
.LEFDE0:
.LSFDE2:
	.int	.LEFDE2-.LASFDE2
.LASFDE2:
	.int	.Lframe0
	.int	.LFB1
	.int	.LFE1-.LFB1
	.align	2
.LEFDE2:
.LSFDE4:
	.int	.LEFDE4-.LASFDE4
.LASFDE4:
	.int	.Lframe0
	.int	.LFB2
	.int	.LFE2-.LFB2
	.byte	0x4
	.int	.LCFI0-.LFB2
	.byte	0xe
	.uleb128 0x24
	.byte	0x4
	.int	.LCFI1-.LCFI0
	.byte	0xe
	.uleb128 0x98
	.byte	0x11
	.uleb128 0x0
	.sleb128 1
	.byte	0x11
	.uleb128 0x1
	.sleb128 2
	.byte	0x11
	.uleb128 0x2
	.sleb128 3
	.byte	0x11
	.uleb128 0x3
	.sleb128 4
	.byte	0x11
	.uleb128 0x4
	.sleb128 5
	.byte	0x11
	.uleb128 0x5
	.sleb128 6
	.byte	0x11
	.uleb128 0x6
	.sleb128 7
	.byte	0x11
	.uleb128 0x7
	.sleb128 8
	.byte	0x11
	.uleb128 0xe
	.sleb128 9
	.align	2
.LEFDE4:
	.ident	"GCC: (AVR_32_bit_GNU_Toolchain_3.4.1_348) 4.4.3"
