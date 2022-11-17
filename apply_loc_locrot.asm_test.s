	.file	"apply_loc_locrot.asm_test.cpp"
	.text
	.section	.text._ZN7geosimdmlIfEEDaRKNS_7mat_4x4IT_EENS3_11column_typeE,"axG",@progbits,_ZN7geosimdmlIfEEDaRKNS_7mat_4x4IT_EENS3_11column_typeE,comdat
	.p2align 4
	.weak	_ZN7geosimdmlIfEEDaRKNS_7mat_4x4IT_EENS3_11column_typeE
	.type	_ZN7geosimdmlIfEEDaRKNS_7mat_4x4IT_EENS3_11column_typeE, @function
_ZN7geosimdmlIfEEDaRKNS_7mat_4x4IT_EENS3_11column_typeE:
.LFB3834:
	.cfi_startproc
	endbr64
	movss	48(%rdi), %xmm2
	movss	32(%rdi), %xmm1
	movss	(%rdi), %xmm4
	movss	4(%rdi), %xmm3
	unpcklps	%xmm2, %xmm1
	movss	16(%rdi), %xmm2
	movss	24(%rdi), %xmm5
	movss	28(%rdi), %xmm6
	unpcklps	%xmm2, %xmm4
	movss	52(%rdi), %xmm2
	movlhps	%xmm1, %xmm4
	movss	36(%rdi), %xmm1
	mulps	%xmm0, %xmm4
	unpcklps	%xmm2, %xmm1
	movss	20(%rdi), %xmm2
	unpcklps	%xmm2, %xmm3
	movss	56(%rdi), %xmm2
	movlhps	%xmm1, %xmm3
	movss	40(%rdi), %xmm1
	mulps	%xmm0, %xmm3
	unpcklps	%xmm2, %xmm1
	movss	8(%rdi), %xmm2
	unpcklps	%xmm5, %xmm2
	movss	44(%rdi), %xmm5
	movlhps	%xmm1, %xmm2
	movss	60(%rdi), %xmm1
	mulps	%xmm0, %xmm2
	unpcklps	%xmm1, %xmm5
	movss	12(%rdi), %xmm1
	unpcklps	%xmm6, %xmm1
	movlhps	%xmm5, %xmm1
	movaps	%xmm4, %xmm5
	mulps	%xmm0, %xmm1
	movaps	%xmm4, %xmm0
	shufps	$255, %xmm4, %xmm5
	unpckhps	%xmm4, %xmm0
	addss	%xmm5, %xmm0
	movaps	%xmm4, %xmm5
	shufps	$85, %xmm4, %xmm4
	addss	%xmm5, %xmm4
	movaps	%xmm3, %xmm5
	unpckhps	%xmm3, %xmm5
	addss	%xmm4, %xmm0
	movaps	%xmm3, %xmm4
	shufps	$255, %xmm3, %xmm4
	addss	%xmm5, %xmm4
	movaps	%xmm3, %xmm5
	shufps	$85, %xmm3, %xmm3
	addss	%xmm5, %xmm3
	movaps	%xmm2, %xmm5
	shufps	$255, %xmm2, %xmm5
	addss	%xmm3, %xmm4
	movaps	%xmm2, %xmm3
	shufps	$85, %xmm2, %xmm3
	addss	%xmm2, %xmm3
	unpckhps	%xmm2, %xmm2
	addss	%xmm5, %xmm2
	movaps	%xmm1, %xmm5
	shufps	$85, %xmm1, %xmm5
	unpcklps	%xmm4, %xmm0
	addss	%xmm2, %xmm3
	movaps	%xmm1, %xmm2
	addss	%xmm5, %xmm2
	movaps	%xmm1, %xmm5
	unpckhps	%xmm1, %xmm5
	shufps	$255, %xmm1, %xmm1
	addss	%xmm5, %xmm1
	addss	%xmm1, %xmm2
	unpcklps	%xmm2, %xmm3
	movlhps	%xmm3, %xmm0
	ret
	.cfi_endproc
.LFE3834:
	.size	_ZN7geosimdmlIfEEDaRKNS_7mat_4x4IT_EENS3_11column_typeE, .-_ZN7geosimdmlIfEEDaRKNS_7mat_4x4IT_EENS3_11column_typeE
	.text
	.p2align 4
	.globl	_Z5applyN7geosimd11basic_pointINS_15euclidian_spaceIfLm3EEEEERKNS_6locrotIS2_EE
	.type	_Z5applyN7geosimd11basic_pointINS_15euclidian_spaceIfLm3EEEEERKNS_6locrotIS2_EE, @function
_Z5applyN7geosimd11basic_pointINS_15euclidian_spaceIfLm3EEEEERKNS_6locrotIS2_EE:
.LFB3820:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_ZN7geosimdmlIfEEDaRKNS_7mat_4x4IT_EENS3_11column_typeE
	pxor	%xmm1, %xmm1
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	addps	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE3820:
	.size	_Z5applyN7geosimd11basic_pointINS_15euclidian_spaceIfLm3EEEEERKNS_6locrotIS2_EE, .-_Z5applyN7geosimd11basic_pointINS_15euclidian_spaceIfLm3EEEEERKNS_6locrotIS2_EE
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
