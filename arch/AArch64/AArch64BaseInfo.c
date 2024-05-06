//===-- AArch64BaseInfo.cpp - AArch64 Base encoding information------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides basic encoding and assembly information for AArch64.
//
//===----------------------------------------------------------------------===//

/* Capstone Disassembly Engine */
/* By Nguyen Anh Quynh <aquynh@gmail.com>, 2013-2019 */

#ifdef CAPSTONE_HAS_ARM64

#if defined (WIN32) || defined (WIN64) || defined (_WIN32) || defined (_WIN64)
#pragma warning(disable:4996)			// disable MSVC's warning on strcpy()
#pragma warning(disable:28719)		// disable MSVC's warning on strcpy()
#endif

#include "../../utils.h"

#include <stdio.h>
#include <stdlib.h>

#include "AArch64BaseInfo.h"

#include "AArch64GenSystemOperands.inc"
#if defined(CAPSTONE_SECRETGRIND)
#	include "../../VG_defines.h"
#endif

char *A64NamedImmMapper_toString(A64NamedImmMapper *N, uint32_t Value, bool *Valid)
{
	unsigned i;
	for (i = 0; i < N->NumPairs; ++i) {
		if (N->Pairs[i].Value == Value) {
			*Valid = true;
			return N->Pairs[i].Name;
		}
	}

	*Valid = false;
	return 0;
}

// compare s1 with lower(s2)
// return true if s1 == lower(f2), and false otherwise
static bool compare_lower_str(char *s1, char *s2)
{
	bool res;
	char *lower = cs_strdup(s2), *c;
	for (c = lower; *c; c++)
		*c = (char)cs_tolower((int) *c);

	res = (cs_strcmp(s1, lower) == 0);
	cs_mem_free(lower);

	return res;
}

uint32_t A64NamedImmMapper_fromString(A64NamedImmMapper *N, char *Name, bool *Valid)
{
	unsigned i;
	for (i = 0; i < N->NumPairs; ++i) {
		if (compare_lower_str(N->Pairs[i].Name, Name)) {
			*Valid = true;
			return N->Pairs[i].Value;
		}
	}

	*Valid = false;
	return (uint32_t)-1;
}

bool A64NamedImmMapper_validImm(A64NamedImmMapper *N, uint32_t Value)
{
	return Value < N->TooBigImm;
}

// return a string representing the number X
// NOTE: result must be big enough to contain the data
static void utostr(uint64_t X, bool isNeg, char *result)
{
	char Buffer[22];
	char *BufPtr = Buffer + 21;

	Buffer[21] = '\0';
	if (X == 0) *--BufPtr = '0';  // Handle special case...

	while (X) {
		*--BufPtr = X % 10 + '0';
		X /= 10;
	}

	if (isNeg) *--BufPtr = '-';   // Add negative sign...

	// suppose that result is big enough
	strncpy(result, BufPtr, sizeof(Buffer));
}

// NOTE: result must be big enough to contain the result
void AArch64SysReg_genericRegisterString(uint32_t Bits, char *result)
{
	// assert(Bits < 0x10000);
	char Op0Str[32], Op1Str[32], CRnStr[32], CRmStr[32], Op2Str[32];
	int dummy;
	uint32_t Op0 = (Bits >> 14) & 0x3;
	uint32_t Op1 = (Bits >> 11) & 0x7;
	uint32_t CRn = (Bits >> 7) & 0xf;
	uint32_t CRm = (Bits >> 3) & 0xf;
	uint32_t Op2 = Bits & 0x7;

	utostr(Op0, false, Op0Str);
	utostr(Op1, false, Op1Str);
	utostr(Op2, false, Op2Str);
	utostr(CRn, false, CRnStr);
	utostr(CRm, false, CRmStr);

	dummy = cs_snprintf(result, 128, "s%s_%s_c%s_c%s_%s",
			Op0Str, Op1Str, CRnStr, CRmStr, Op2Str);
	// First search the registers shared by all
	for (i = 0; i < ARR_SIZE(SysRegPairs); ++i) {
		if (SysRegPairs[i].Value == Bits) {
			*Valid = true;
			cs_strcpy(result, SysRegPairs[i].Name);
			return;
		}
	}

	// Next search for target specific registers
	// if (FeatureBits & AArch64_ProcCyclone) {
	if (true) {
		for (i = 0; i < ARR_SIZE(CycloneSysRegPairs); ++i) {
			if (CycloneSysRegPairs[i].Value == Bits) {
				*Valid = true;
				cs_strcpy(result, CycloneSysRegPairs[i].Name);
				return;
			}
		}
	}

	// Now try the instruction-specific registers (either read-only or
	// write-only).
	for (i = 0; i < S->NumInstPairs; ++i) {
		if (S->InstPairs[i].Value == Bits) {
			*Valid = true;
			cs_strcpy(result, S->InstPairs[i].Name);
			return;
		}
	}

	Op0 = (Bits >> 14) & 0x3;
	Op1 = (Bits >> 11) & 0x7;
	CRn = (Bits >> 7) & 0xf;
	CRm = (Bits >> 3) & 0xf;
	Op2 = Bits & 0x7;

	// Only combinations matching: 11 xxx 1x11 xxxx xxx are valid for a generic
	// name.
	if (Op0 != 3 || (CRn != 11 && CRn != 15)) {
		*Valid = false;
		return;
	}

	//assert(Op0 == 3 && (CRn == 11 || CRn == 15) && "Invalid generic sysreg");

	*Valid = true;

	Op1S = utostr(Op1, false);
	CRnS = utostr(CRn, false);
	CRmS = utostr(CRm, false);
	Op2S = utostr(Op2, false);

	//printf("Op1S: %s, CRnS: %s, CRmS: %s, Op2S: %s\n", Op1S, CRnS, CRmS, Op2S);
	dummy = cs_sprintf(result, "s3_%s_c%s_c%s_%s", Op1S, CRnS, CRmS, Op2S);
	(void)dummy;
}

#endif
