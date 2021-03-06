/* 
 * CS:APP Data Lab 
 * 
 * <Jie He 811050742>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
	int result = ~((~x)&(~y)); // DeMorgan's Law => x|y
	return result;
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
	int i = 1;
	i |= i << 2; // i = i|i << 2 can cover 2*2 = 4(bits)
	i |= i << 4; // can cover 4*2 = 8(bits)
	i |= i << 8; // can cover 8*2 = 16(bits)
	i |= i << 16; // can cover 16*2 = 32(bits)
	return i; // return 0101 ... 0101 
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  int result = ~0; //complement of 0; ~0 has all bits equal to 1; based on the definition, we have -1
  return result;
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  int bit;
  int allOddbit = (0xAA << 8) | 0xAA; //0xAA <=> 10101010; this line will give you 0xAAAA
  allOddbit = allOddbit | (allOddbit << 16); // "|" bitwise OR; this line will give you 0xAAAAAAAA
  bit = allOddbit | x;
  bit = ~bit;
  return !bit; // return an int (0 or 1) which represents true or false
} // 0101 all even-numbered bits are 1 in this case 
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
    int m, a, b, c, d, result;
    m = 0xAA;
    a = x & m;
    b = (x >> 8) & m;
    c = (x >> 16) & m;
    d = (x >> 24) & m;
    result = a + b + c + d;
    return !(!result);
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    int a = 0xFF;
	
	int n_shift = n << 3;
	int m_shift = m << 3;
	
	int nbyte = (a << n_shift)&x;
	int mbyte = (a << m_shift)&x;
	int c = (a << n_shift) | (a << m_shift);
	
	nbyte = (nbyte >> n_shift)&a;
	mbyte = (mbyte >> m_shift)&a;

	nbyte = nbyte << m_shift;
	mbyte = mbyte << n_shift;
	c = ~c & x;

	return c | mbyte | nbyte;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int totala = x + y;
  int totalx = x >> 31;
  int totaly = y >> 31;
  int totalb = totala >> 31;
 
  return !( ~(totalx ^ totaly) & (totalx ^ totalb));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  x = !!x;
  x = ~x+1;
  return (x & y) | (~x & z);
} /* if(x)
		return y;
	 else
		return z;*/
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int i = 1 << 31; // i is the sign bit
  int upper = ~(i | 0x39);
  int lower = ~0X30;
  upper = i & (upper+x) >> 31;
  lower = i & (lower+1+x) >> 31;
  return !(upper | lower);
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB) // LSB: least significant bit (10010; the last digit 0 has the index 0)
 *   MSB: most significant bit (10010; the first digit 1 has the index 0)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78 // one byte = 8 bits
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
	int m, s;
	m = 255;
	s = n << 3;
	m = ~(m << s); 
	c = c << s; 
	return (x & m) | c;
}
/* reverseBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: reverseBits(0x11111111) = 0x88888888
 *            reverseBits(0xdeadbeef) = 0xf77db57b
 *            reverseBits(0x88888888) = 0x11111111
 *            reverseBits(0)  = 0
 *            reverseBits(-1) = -1
 *            reverseBits(0x9) = 0x90000000
 *  Legal ops: ! ~ & ^ | + << >> and unsigned int type
 *  Max ops: 90
 *  Rating: 4
 */
int reverseBits(int x) {
	unsigned int odd1   = ((0xAA << 8)|0xAA);
	unsigned int odd01   = (odd1<<16)|odd1;
	unsigned int odd     = (x&odd01)>>1;     
	unsigned int even    = (x&(~odd01))<<1;
	unsigned int part1   = odd|even;
 
	unsigned int odd16     = ((0xff << 8)|0xff);
	unsigned int odd016    = (odd16<<16);
	unsigned int odd2     = (part1&odd016)>>16;     
	unsigned int even2    = (part1&(~odd016))<<16;
	unsigned int part2     = odd2|even2;
 
	unsigned int odd8   = (0xff<<8);
	unsigned int odd08    = (odd8<<16)|odd8;
	unsigned int odd3      = (part2&odd08)>>8;     
	unsigned int even3     = (part2&(~odd08))<<8;
	unsigned int part3   = odd3|even3;
 
	unsigned int odd4      = ((0xf0 << 8)|0xf0);
	unsigned int odd04     = (odd4<<16)|odd4;
	unsigned int odd_4     = (part3&odd04)>>4;     
	unsigned int even_4    = (part3&(~odd04))<<4;
	unsigned int part4     = odd_4|even_4;
 
	unsigned int odd22      = ((0x33 << 8)|0x33);
	unsigned int odd022     = (odd22<<16)|odd22;
	unsigned int odd_2     = (part4&odd022)<<2;     
	unsigned int even_2    = (part4&(~odd022))>>2;
	unsigned int part5     = odd_2|even_2;
	return part5;;
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  int sum = x + y;
  int OverFlow = ((sum ^ x) & (sum ^ y)) >> 31;  
    
  return (sum >> (OverFlow & 31)) + (OverFlow << 31);
}
/*
 * Extra credit
 */
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
	unsigned m = 0x7FFFFFFF;
	unsigned minnan = 0x7F800001;
	unsigned res = uf & m;

	if (res >= minnan){
		return uf;
	}
	else{
		return res;
	}
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
	int exp = (uf >> 23) & 0xFF; 
	int f = uf & 0x7FFFFF; 
	int e = exp - 127; 
	
	if(exp == 0x7F800000)
		return 0x80000000u;
	if(!exp)
		return 0;
	if(e < 0)
		return 0;
	if(e > 30)
		return 0x80000000u;
	
	f = f | 0x800000;
	if (e >= 23)
		f = f<< (e-23);
	else
		f = f >> (23 -e);

	if(( uf >> 31 ) & 1)
		return ~f + 1;
	
	return f;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
	int s_mask = 1 << 31;
	int t_mask = (s_mask >> 8);
	int e_mask = s_mask^t_mask;
	int neg_1 = s_mask >> 31;
	int f_mask = ~t_mask;
	int odd_mask = 3;
	int case_mask = 1 << 22;
	int s = s_mask & uf;
	int e = e_mask & uf;
	int f = f_mask & uf;
	int E = e_mask ^ e;
	int odd = odd_mask & f;
	int O = !(odd^3);
	int shift = (f + O) >> 1;
	
	if (!E)
		return uf;
	if (!e){
		return s | shift;
	}
	if (!((e >> 23)^1)){
		return s | case_mask | shift;
	}
	
	return s | ((e + neg_1)&e_mask) | f;
}
