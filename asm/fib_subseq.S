	.file   "fib_subseq.S.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	
	.text
	.align   1
	.globl   lenLongestFibSubseq
	.type    lenLongestFibSubseq, @function
lenLongestFibSubseq:
	addi    sp, sp, -240
	sd      ra, 232(sp)
	sd      s0, 224(sp)
	addi    s0, sp, 240
	sw      a0, -20(s0)
	li      s1, 1
	sw      s1, -28(s0)
	li      s1, 0
	sw      s1, -36(s0)
	lw     t3, -28(s0)
	mv      t4, a0
	blt     t3, t4, L2
	j       L1
L2:
	lw     t1, -28(s0)
	li      t2, 1
	addw     t0, t1, t2
	sw     t0, -48(s0)
	mv      s7, t0
	sw     s7, -44(s0)
	mv      t3, s7
	lw     t4, -20(s0)
	blt     t3, t4, L6
	j       L5
L6:
	lw     t1, -44(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -52(s0)
	lw     t1, -28(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -56(s0)
	mv      s3, t0
	la      s4, GVAR1
	add     s4, s4, s3
	lw     t1, 0(s4)
	li      t2, 1
	sll     t0, t1, t2
	sw     t0, -60(s0)
	lw     s3, -52(s0)
	la      s4, GVAR1
	add     s4, s4, s3
	lw     t3, 0(s4)
	mv      t4, t0
	blt     t4, t3, L5
	j       L8
L8:
	lw     t1, -44(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -104(s0)
	lw     t1, -28(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -108(s0)
	lw     s3, -104(s0)
	la      s4, GVAR1
	add     s4, s4, s3
	lw     t1, 0(s4)
	mv      s3, t0
	la      s4, GVAR1
	add     s4, s4, s3
	lw     t2, 0(s4)
	subw     t0, t1, t2
	sw     t0, -112(s0)
	mv      s7, t0
	sw     s7, -68(s0)
	li      s7, 0
	sw     s7, -76(s0)
	lw     t1, -28(s0)
	li      t2, 1
	subw     t0, t1, t2
	sw     t0, -116(s0)
	mv      s7, t0
	sw     s7, -84(s0)
	li      s7, -1
	sw     s7, -92(s0)
	lw     t3, -76(s0)
	lw     t4, -84(s0)
	ble     t3, t4, L13
	lw     t3, -92(s0)
	li      t4, 0
	ble     t4, t3, L24
	j       L23
L13:
	lw     t1, -84(s0)
	lw     t2, -76(s0)
	subw     t0, t1, t2
	sw     t0, -120(s0)
	mv      t1, t0
	li      t2, 1
	sra     t0, t1, t2
	sw     t0, -124(s0)
	mv      t1, t0
	lw     t2, -76(s0)
	addw     t0, t1, t2
	sw     t0, -128(s0)
	mv      s7, t0
	sw     s7, -100(s0)
	mv      t1, s7
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -132(s0)
	mv      s3, t0
	la      s4, GVAR1
	add     s4, s4, s3
	lw     t3, 0(s4)
	lw     t4, -68(s0)
	beq     t3, t4, L16
	j       L17
L16:
	lw     s7, -100(s0)
	sw     s7, -92(s0)
	mv      t3, s7
	li      t4, 0
	ble     t4, t3, L24
	j       L23
	lw     t3, -76(s0)
	lw     t4, -84(s0)
	ble     t3, t4, L13
	lw     t3, -92(s0)
	li      t4, 0
	ble     t4, t3, L24
	j       L23
L17:
	lw     t1, -100(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -136(s0)
	mv      s3, t0
	la      s4, GVAR1
	add     s4, s4, s3
	lw     t3, 0(s4)
	lw     t4, -68(s0)
	blt     t3, t4, L20
	j       L21
L20:
	lw     t1, -100(s0)
	li      t2, 1
	addw     t0, t1, t2
	sw     t0, -140(s0)
	mv      s7, t0
	sw     s7, -76(s0)
	j       L19
L21:
	lw     t1, -100(s0)
	li      t2, 1
	subw     t0, t1, t2
	sw     t0, -144(s0)
	mv      s7, t0
	sw     s7, -84(s0)
L19:
	lw     t3, -76(s0)
	lw     t4, -84(s0)
	ble     t3, t4, L13
	lw     t3, -92(s0)
	li      t4, 0
	ble     t4, t3, L24
	j       L23
L24:
	lw     t1, -28(s0)
	li      t2, 10
	sll     t0, t1, t2
	sw     t0, -148(s0)
	lw     t1, -44(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -152(s0)
	lw     t1, -148(s0)
	mv      t2, t0
	addw     t0, t1, t2
	sw     t0, -156(s0)
	lw     t1, -92(s0)
	li      t2, 10
	sll     t0, t1, t2
	sw     t0, -160(s0)
	lw     t1, -28(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -164(s0)
	lw     t1, -160(s0)
	mv      t2, t0
	addw     t0, t1, t2
	sw     t0, -168(s0)
	mv      s3, t0
	la      s4, GVAR0
	add     s4, s4, s3
	lw     t1, 0(s4)
	li      t2, 1
	addw     t0, t1, t2
	sw     t0, -172(s0)
	mv      s7, t0
	lw     s5, -156(s0)
	la      s6, GVAR0
	add     s6, s6, s5
	sw     s7, 0(s6)
	lw     s7, -156(s0)
	sw     s7, -184(s0)
	mv      s3, s7
	la      s4, GVAR0
	add     s4, s4, s3
	lw     t3, 0(s4)
	li      t4, 3
	blt     t3, t4, L27
	j       L26
L27:
	lw     t1, -28(s0)
	li      t2, 10
	sll     t0, t1, t2
	sw     t0, -188(s0)
	lw     t1, -44(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -192(s0)
	lw     t1, -188(s0)
	mv      t2, t0
	addw     t0, t1, t2
	sw     t0, -196(s0)
	li      s7, 3
	mv      s5, t0
	la      s6, GVAR0
	add     s6, s6, s5
	sw     s7, 0(s6)
L26:
	lw     t1, -28(s0)
	li      t2, 10
	sll     t0, t1, t2
	sw     t0, -200(s0)
	lw     t1, -44(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -204(s0)
	lw     t1, -200(s0)
	mv      t2, t0
	addw     t0, t1, t2
	sw     t0, -208(s0)
	mv      s3, t0
	la      s4, GVAR0
	add     s4, s4, s3
	lw     t3, 0(s4)
	lw     t4, -36(s0)
	blt     t4, t3, L30
	j       L29
L30:
	lw     t1, -28(s0)
	li      t2, 10
	sll     t0, t1, t2
	sw     t0, -212(s0)
	lw     t1, -44(s0)
	li      t2, 2
	sll     t0, t1, t2
	sw     t0, -216(s0)
	lw     t1, -212(s0)
	mv      t2, t0
	addw     t0, t1, t2
	sw     t0, -220(s0)
	mv      s3, t0
	la      s4, GVAR0
	add     s4, s4, s3
	lw     s7, 0(s4)
	sw     s7, -36(s0)
L29:
L23:
	lw     t1, -44(s0)
	li      t2, 1
	addw     t0, t1, t2
	sw     t0, -224(s0)
	mv      s7, t0
	sw     s7, -44(s0)
	mv      t3, s7
	lw     t4, -20(s0)
	blt     t3, t4, L6
	j       L5
L5:
	lw     t1, -28(s0)
	li      t2, 1
	addw     t0, t1, t2
	sw     t0, -228(s0)
	mv      s7, t0
	sw     s7, -28(s0)
	mv      t3, s7
	lw     t4, -20(s0)
	blt     t3, t4, L2
	j       L1
L1:
	lw     a0, -36(s0)
	ld      ra, 232(sp)
	ld      s0, 224(sp)
	addi    sp, sp, 240
	jr      ra
	.size   lenLongestFibSubseq, .-lenLongestFibSubseq
	
	.text
	.align   1
	.globl   main
	.type    main, @function
main:
	addi    sp, sp, -48
	sd      ra, 40(sp)
	sd      s0, 32(sp)
	addi    s0, sp, 48
	call    get_int
	nop
	sw     a0, -36(s0)
	mv      s7, a0
	sw     s7, -24(s0)
	mv      a0, s7
	call    lenLongestFibSubseq
	nop
	sw     a0, -40(s0)
	mv      s7, a0
	sw     s7, -32(s0)
	mv      a0, s7
	call    print_int
	nop
	li      a0, 0
	ld      ra, 40(sp)
	ld      s0, 32(sp)
	addi    sp, sp, 48
	jr      ra
	.size   main, .-main
	
	.globl  GVAR0
	.bss
	.align  3
	.type   GVAR0, @object
	.size   GVAR0, 283024
GVAR0:
	.zero   283024
	
	.globl  GVAR1
	.data
	.align  3
	.type   GVAR1, @object
	.size   GVAR1, 1064
GVAR1:
	.word   0
	.word   3
	.word   4
	.word   5
	.word   8
	.word   9
	.word   10
	.word   11
	.word   13
	.word   15
	.word   19
	.word   20
	.word   21
	.word   24
	.word   31
	.word   33
	.word   34
	.word   40
	.word   45
	.word   46
	.word   55
	.word   57
	.word   58
	.word   59
	.word   64
	.word   66
	.word   67
	.word   73
	.word   75
	.word   77
	.word   79
	.word   80
	.word   82
	.word   86
	.word   90
	.word   93
	.word   95
	.word   96
	.word   102
	.word   108
	.word   110
	.word   111
	.word   114
	.word   117
	.word   118
	.word   119
	.word   124
	.word   130
	.word   133
	.word   138
	.word   149
	.word   153
	.word   156
	.word   157
	.word   164
	.word   165
	.word   166
	.word   167
	.word   171
	.word   172
	.word   181
	.word   182
	.word   187
	.word   188
	.word   192
	.word   204
	.word   207
	.word   210
	.word   211
	.word   213
	.word   214
	.word   215
	.word   217
	.word   219
	.word   220
	.word   222
	.word   224
	.word   225
	.word   227
	.word   229
	.word   230
	.word   231
	.word   239
	.word   241
	.word   243
	.word   244
	.word   247
	.word   248
	.word   250
	.word   252
	.word   253
	.word   260
	.word   262
	.word   264
	.word   265
	.word   270
	.word   272
	.word   278
	.word   282
	.word   286
	.word   287
	.word   288
	.word   289
	.word   291
	.word   294
	.word   298
	.word   300
	.word   312
	.word   313
	.word   314
	.word   317
	.word   319
	.word   320
	.word   322
	.word   323
	.word   324
	.word   326
	.word   331
	.word   334
	.word   338
	.word   340
	.word   342
	.word   343
	.word   345
	.word   348
	.word   357
	.word   367
	.word   370
	.word   372
	.word   373
	.word   375
	.word   377
	.word   379
	.word   381
	.word   382
	.word   386
	.word   387
	.word   390
	.word   391
	.word   401
	.word   402
	.word   404
	.word   406
	.word   409
	.word   416
	.word   417
	.word   426
	.word   432
	.word   433
	.word   436
	.word   438
	.word   439
	.word   441
	.word   446
	.word   449
	.word   450
	.word   453
	.word   457
	.word   458
	.word   460
	.word   466
	.word   472
	.word   475
	.word   483
	.word   485
	.word   487
	.word   488
	.word   491
	.word   492
	.word   493
	.word   494
	.word   495
	.word   498
	.word   500
	.word   502
	.word   504
	.word   507
	.word   510
	.word   511
	.word   513
	.word   516
	.word   517
	.word   519
	.word   520
	.word   521
	.word   526
	.word   528
	.word   535
	.word   540
	.word   542
	.word   547
	.word   551
	.word   554
	.word   564
	.word   566
	.word   569
	.word   574
	.word   577
	.word   591
	.word   593
	.word   598
	.word   602
	.word   603
	.word   605
	.word   610
	.word   611
	.word   616
	.word   617
	.word   619
	.word   623
	.word   624
	.word   625
	.word   629
	.word   633
	.word   639
	.word   643
	.word   645
	.word   646
	.word   647
	.word   648
	.word   649
	.word   652
	.word   658
	.word   659
	.word   662
	.word   663
	.word   664
	.word   669
	.word   672
	.word   679
	.word   680
	.word   685
	.word   692
	.word   701
	.word   704
	.word   705
	.word   707
	.word   708
	.word   710
	.word   713
	.word   728
	.word   732
	.word   733
	.word   735
	.word   737
	.word   741
	.word   742
	.word   744
	.word   749
	.word   752
	.word   762
	.word   763
	.word   764
	.word   765
	.word   767
	.word   771
	.word   773
	.word   776
	.word   777
	.word   780
	.word   781
	.word   782
	.word   787
	.word   793
	.word   796
	.word   797
	
	.section    .rodata
	
	.section    .rodata
