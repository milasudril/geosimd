	.file	"add_vec3.asm_test.cpp"
	.text
	.section	.rodata
	.align 8
	.type	_ZN7geosimd13vector_limitsL20min_vector_byte_sizeE, @object
	.size	_ZN7geosimd13vector_limitsL20min_vector_byte_sizeE, 8
_ZN7geosimd13vector_limitsL20min_vector_byte_sizeE:
	.quad	16
	.type	_ZN7geosimd13vector_limitsL8has_sse1E, @object
	.size	_ZN7geosimd13vector_limitsL8has_sse1E, 1
_ZN7geosimd13vector_limitsL8has_sse1E:
	.byte	1
	.type	_ZN7geosimd13vector_limitsL8has_sse2E, @object
	.size	_ZN7geosimd13vector_limitsL8has_sse2E, 1
_ZN7geosimd13vector_limitsL8has_sse2E:
	.byte	1
	.type	_ZN7geosimd13vector_limitsL8has_sse3E, @object
	.size	_ZN7geosimd13vector_limitsL8has_sse3E, 1
_ZN7geosimd13vector_limitsL8has_sse3E:
	.zero	1
	.type	_ZN7geosimd13vector_limitsL8has_sse4E, @object
	.size	_ZN7geosimd13vector_limitsL8has_sse4E, 1
_ZN7geosimd13vector_limitsL8has_sse4E:
	.zero	1
	.type	_ZN7geosimd13vector_limitsL7has_avxE, @object
	.size	_ZN7geosimd13vector_limitsL7has_avxE, 1
_ZN7geosimd13vector_limitsL7has_avxE:
	.zero	1
	.type	_ZN7geosimd13vector_limitsL11has_avx_512E, @object
	.size	_ZN7geosimd13vector_limitsL11has_avx_512E, 1
_ZN7geosimd13vector_limitsL11has_avx_512E:
	.zero	1
	.type	_ZN7geosimd13vector_limitsL16has_extended_sseE, @object
	.size	_ZN7geosimd13vector_limitsL16has_extended_sseE, 1
_ZN7geosimd13vector_limitsL16has_extended_sseE:
	.byte	1
	.type	_ZN7geosimd13vector_limitsL7has_sseE, @object
	.size	_ZN7geosimd13vector_limitsL7has_sseE, 1
_ZN7geosimd13vector_limitsL7has_sseE:
	.byte	1
	.align 8
	.type	_ZN7geosimd13vector_limitsL20max_vector_byte_sizeE, @object
	.size	_ZN7geosimd13vector_limitsL20max_vector_byte_sizeE, 8
_ZN7geosimd13vector_limitsL20max_vector_byte_sizeE:
	.quad	16
	.text
	.p2align 4
	.globl	_ZN12geosimd_test3addEN7geosimd5vec_tIiLm4EEES2_
	.type	_ZN12geosimd_test3addEN7geosimd5vec_tIiLm4EEES2_, @function
_ZN12geosimd_test3addEN7geosimd5vec_tIiLm4EEES2_:
.LFB3417:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movaps	%xmm0, -80(%rbp)
	movaps	%xmm1, -96(%rbp)
	movdqa	-80(%rbp), %xmm0
	movaps	%xmm0, -64(%rbp)
	movdqa	-96(%rbp), %xmm0
	movaps	%xmm0, -48(%rbp)
	movdqa	-64(%rbp), %xmm0
	movaps	%xmm0, -32(%rbp)
	movdqa	-48(%rbp), %xmm0
	movaps	%xmm0, -16(%rbp)
	movdqa	-32(%rbp), %xmm0
	paddd	-16(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3417:
	.size	_ZN12geosimd_test3addEN7geosimd5vec_tIiLm4EEES2_, .-_ZN12geosimd_test3addEN7geosimd5vec_tIiLm4EEES2_
	.p2align 4
	.globl	_ZN12geosimd_test3addEN7geosimd12basic_vectorINS_18my_vector_space_3dEEES3_
	.type	_ZN12geosimd_test3addEN7geosimd12basic_vectorINS_18my_vector_space_3dEEES3_, @function
_ZN12geosimd_test3addEN7geosimd12basic_vectorINS_18my_vector_space_3dEEES3_:
.LFB3418:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movaps	%xmm0, -80(%rbp)
	movaps	%xmm1, -96(%rbp)
	movdqa	-80(%rbp), %xmm0
	movaps	%xmm0, -64(%rbp)
	movdqa	-96(%rbp), %xmm0
	movaps	%xmm0, -48(%rbp)
	movdqa	-64(%rbp), %xmm0
	movaps	%xmm0, -32(%rbp)
	movdqa	-48(%rbp), %xmm0
	movaps	%xmm0, -16(%rbp)
	movdqa	-32(%rbp), %xmm0
	paddd	-16(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3418:
	.size	_ZN12geosimd_test3addEN7geosimd12basic_vectorINS_18my_vector_space_3dEEES3_, .-_ZN12geosimd_test3addEN7geosimd12basic_vectorINS_18my_vector_space_3dEEES3_
	.p2align 4
	.globl	_ZN12geosimd_test3addEDv4_iS0_
	.type	_ZN12geosimd_test3addEDv4_iS0_, @function
_ZN12geosimd_test3addEDv4_iS0_:
.LFB3423:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movaps	%xmm0, -16(%rbp)
	movaps	%xmm1, -32(%rbp)
	movdqa	-16(%rbp), %xmm0
	paddd	-32(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3423:
	.size	_ZN12geosimd_test3addEDv4_iS0_, .-_ZN12geosimd_test3addEDv4_iS0_
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
