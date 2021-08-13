# Algorithm steps
There are 5 steps of the algorithm

The example: 
$ echo -n "5" | md5     
e4da3b7fbbce2345d7772b0674a318d5

## Preparation
"5" is 53 in decimal and 00110101 in binary

## First step: Prepare 512-bit blocks
The padding works as follows: first a single bit, 1, is appended to the end of the message. This is followed by as many zeros as are required to bring the length of the message up to 64 bits fewer than a multiple of 512.

1. We take our string in binary:
00110101
length = 8 bit
Our message was a string where each char is one byte or 8 bit.

2. Our message contains 8 bit. The message will be padded to make it 448 mod 512 bits long. Since our message is 8 bit we add 440 bit because 448 MOD 512 = 448. We add one bit and 439 zeros:
00110101 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
length = 448 bit

3. We add the length of the message as 32 least significant bit and 32 most significant bit. That means that we add a 64 bit value which represents the original length of the message. Our original message length is 8 bit where number 8 in 64-bit representation is:
00000000 00000000 00000000 00000000
00000000 00000000 00000000 00001000
As programming calculators show.

4. So we add the length to the message and have the following
message prepared for the algoriphm:
00110101 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00001000

WARNING: It is necessary how the machine is saving bytes: in little-endian or big-endian order.

## Second step: Prepare buffers for calculations
We will use the following formula:
[abcd k s i]
a = b + ((a + {Fun}(b,c,d) + X[k] + T[i]) <<< s)
And have 4 plays with 16 rounds in each.

1. Prepare the init vector:
For little-endian:
a0 = 01 23 45 67; // 0x67452301
b0 = 89 AB CD EF; // 0xEFCDAB89
c0 = FE DC BA 98; // 0x98BADCFE
d0 = 76 54 32 10. // 0x10325476

For big-endian:
a0 = 0x01234567;
b0 = 0x89abcdef;
c0 = 0xfedcba98;
d0 = 0x76543210;
These 4 variables will save the middle state during the calculations.
Each variable is a 32bit number (uint32_t)

2. Specify the per-round shift amounts - variable s (shifts)
var int s[64]
s[0..15] := {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22} - 1st play
4 values are the same eah 4 rounds
s[16..31] := {5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20} - 2nd play
4 values are the same eah 4 rounds
s[32..47] := {4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23} - 3rd play
4 values are the same eah 4 rounds
s[48..63] := {6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21} - 4th play
4 values are the same eah 4 rounds
These variables are stated.
Each s is an array of 32bit numbers (uint32_t).

3. Specify the table of constants according to formula
T[1...64] 
T[n]={int}(2^{32}*|sin n|)

There are ready tables:
Tx[0..3] := {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee}
Tx[4..7] := {0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501}
Tx[8..11] := {0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be}
Tx[12..15] := {0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821}
Tx[16..19] := {0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa}
Tx[20..23] := {0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8}
Tx[24..27] := {0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed}
Tx[28..31] := {0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a}
Tx[32..35] := {0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c}
Tx[36..39] := {0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70}
Tx[40..43] := {0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05}
Tx[44..47] := {0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665}
Tx[48..51] := {0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039}
Tx[52..55] := {0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1}
Tx[56..59] := {0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1}
Tx[60..63] := {0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391}
Each Tx is an array of 32bit numbers (uint32_t)

## Third step: Perform the calculations

1. Break our ready message (we have only one 512-bit block) into 16 blocks of 32 bit
00110101 10000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00000000 \
00000000 00000000 00000000 00001000

2. Save state of the variables before the calculations of 512-bit block:

var int_32 a_before = a0
var int_32 b_before = b0
var int_32 c_before = c0
var int_32 d_before = d0

3. Save functions that will be used:
{FunF}(X,Y,Z)=(X and Y) or (not X and Z)
{FunG}(X,Y,Z)=(X and Z) or (not Z and Y)
{FunH}(X,Y,Z)=(X xor Y xor Z)
{FunI}(X,Y,Z)=(Y xor (not Z or X))

4. Make calculations
/* [abcd k s i] a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s). */
where X[k] - k = 0..63 - value from the table of consts that also can be counted and X is a 512bit message block;
T[i] - i = 0..63 - index of the round and T - 32bit number from
the ready-table
s - const shift from the ready-table
There are 3 steps in the main formula that is also called round:

	1.1. aa += F(bb, cc, dd) + X[k] + T[i];
	1.2. aa = a <<< s (cycle shift);
	1.3. aa += b;

What is a cycle shift:
We have A value: 1000 0001. If we just shift it by 3(A << 3), we have the following result:
0000 1000 (or 8 in decimal)
If we shift it by 3 in cycle (A <<< 3), we have the following result:
0000 1100 (or 12 in decimal)

So there are 64 rounds:
First 16 rounds with first fun function F:
[ABCD  0 7  1][DABC  1 12  2][CDAB  2 17  3][BCDA  3 22  4]
[ABCD  4 7  5][DABC  5 12  6][CDAB  6 17  7][BCDA  7 22  8]
[ABCD  8 7  9][DABC  9 12 10][CDAB 10 17 11][BCDA 11 22 12]
[ABCD 12 7 13][DABC 13 12 14][CDAB 14 17 15][BCDA 15 22 16]
where numbers are k, s and i (round number) values

Second 16 rounds with second fun function G:
[ABCD  1 5 17][DABC  6 9 18][CDAB 11 14 19][BCDA  0 20 20]
[ABCD  5 5 21][DABC 10 9 22][CDAB 15 14 23][BCDA  4 20 24]
[ABCD  9 5 25][DABC 14 9 26][CDAB  3 14 27][BCDA  8 20 28]
[ABCD 13 5 29][DABC  2 9 30][CDAB  7 14 31][BCDA 12 20 32]

Third 16 rounds with third fun function H:
[ABCD  5 4 33][DABC  8 11 34][CDAB 11 16 35][BCDA 14 23 36]
[ABCD  1 4 37][DABC  4 11 38][CDAB  7 16 39][BCDA 10 23 40]
[ABCD 13 4 41][DABC  0 11 42][CDAB  3 16 43][BCDA  6 23 44]
[ABCD  9 4 45][DABC 12 11 46][CDAB 15 16 47][BCDA  2 23 48]

Last 16 rounds with fourth fun function I:
[ABCD  0 6 49][DABC  7 10 50][CDAB 14 15 51][BCDA  5 21 52]
[ABCD 12 6 53][DABC  3 10 54][CDAB 10 15 55][BCDA  1 21 56]
[ABCD  8 6 57][DABC 15 10 58][CDAB  6 15 59][BCDA 13 21 60]
[ABCD  4 6 61][DABC 11 10 62][CDAB  2 15 63][BCDA  9 21 64]
As we see in the round we save real abcd values to aa, bb, cc, dd parameters in different orders. So aa equals real A value only 16 times from 64.

5. Save abcd values to the buffer for this 512-bit message block:
a += a_before
b += b_before
c += c_before
d += d_before

6. If we have more than 512 bit in the message, save other part of the message to the 512 bit block and repeat calculations (save abcd values to some a_before and so on buffer, perform calculations, add before values to the new ones) 

## Fourth step: print the md5 hash value
We have 4 values abcd each of it consists of 4 8-bit blocks.
In order to print md5 hash value we need to make one 128-bit number from this 4 values and then count each 4 bits as a number in hexadecimal.
Example:
a value for "echo -n '5' | ./ft_ssl" will be (in little-endian):
01111111 00111011 11011010 11100100 
01000101 00100011 11001110 10111011 
00000110 00101011 01110111 11010111 
11010101 00011000 10100011 01110100
where:
first 4 bits 0111 is 0x7
1111 - 0xF
0011 - 0x3
1011 - 0xB
1101 - 0xD
1010 - 0xA
1110 - 0xE
0100 - 0x4
Therefore we have: e4da3b7f for A.
In general our md5 hash is e4da3b7fbbce2345d7772b0674a318d5.