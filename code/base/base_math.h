/* date = July 7th 2022 7:59 pm */

#ifndef BASE_MATH_H
#define BASE_MATH_H

typedef enum Axis2
{
	Axis2X,
	Axis2Y,
} Axis2;

typedef enum Axis4
{
	Axis4X,
	Axis4Y,
	Axis4Z,
	Axis4W,
} Axis4;

typedef enum Side
{
	SideMin,
	SideMax,
} Side;

global_ S8 S8Min = (S8)0x80;
global_ S16 S16Min = (S16)0x8000;
global_ S32 S32Min = (S32)0x80000000;
global_ S64 S64Min = (S64)0x8000000000000000llu;

global_ S8 S8Max = (S8)0x7f;
global_ S16 S16Max = (S16)0x7fff;
global_ S32 S32Max = (S32)0x7fffffff;
global_ S64 S64Max = (S64)0x7fffffffffffffffllu;

global_ U8 U8Max = (U8)0xff;
global_ U16 U16Max = (U16)0xffff;
global_ U32 U32Max = (U32)0xffffffff;
global_ U64 U64Max = (U64)0xffffffffffffffffllu;

#include <float.h>
#include <limits.h>
#define R32MAX FLT_MAX
#define S32MAX INT_MAX
#define S32MIN INT_MIN
#define U32MAX UINT_MAX
#define U32MIN 0

#define PI32 3.14159265359f
#define TAU32 6.28318530718f

#define DegToRad (PI32 / 180.0f)
#define RadToDeg (180.0f / PI32)

#include "math.h"

typedef union V2
{
	F32 e[2];
	struct
	{
		F32 x, y;
	};
} V2;

typedef union V2I
{
	S32 e[2];
	struct
	{
		S32 x, y;
	};
} V2I;

typedef union V3
{
	F32 e[3];
	struct
	{
		F32 x, y, z;
	};
	struct
	{
		F32 r, g, b;
	};
	struct
	{
		V2 xy;
		F32 IGNOREDZ_0;
	};
	struct
	{
		F32 IGNORED_X;
		F32 yz;
	};
}V3;

typedef union V4
{
	F32 e[4];
	union
	{
		struct
		{
			F32 x, y, z, w;
		};
		
		struct
		{
			V3 xyz;
			F32 IGNORED_0;
		};
	};
	
	union
	{
		struct
		{
			F32 r, g, b, a;
		};
		
		struct
		{
			V3 rgb;
			F32 IGNORED_1;
		};
	};
} V4;

typedef union R1
{
	F32 e[2];
	F32 min, max;
} R1;

typedef union R1I
{
	S32 e[2];
	S32 Min, Max;
}R1I;

typedef union R2
{
	F32 e[4];
	struct 
	{
		V2 p0, p1;
	};
	struct 
	{
		V2 min, max;
	};
	struct
	{
		F32 x0, y0;
		F32 x1, y1;
	};
} R2;

typedef union R2I
{
	S32 e[4];
	struct
	{
		V2I p0, p1;
	};
	struct
	{
		V2I min, max;
	};
	struct
	{
		S32 x0, y0;
		S32 x1, y1;
	};
} R2I;

typedef union R3
{
	F32 e[6];
	struct
	{
		V3 min;
		V3 max;
	};
	struct
	{
		F32 x0, y0, z0;
		F32 x1, y1, z1;
	};
} R3;

typedef struct M44
{
	F32 e[4][4];
} M44;

typedef union Qur
{
	struct
	{
		F32 x, y, z, w;
	};
	
	struct
	{
		V3 xyz;
		F32 IGNORED_0;
	};
} Qur;

///////////////////////////
// NOTE(nates): Integer math functions

func_ S16 AbsValueS16(S16 value);
func_ U64 U64EncodeFromS64(S64 number);
func_ S64 S64DecodeFromU64(U64 number);

///////////////////////////
// NOTE(nates): Real math functions

func_ S32 RoundToS(F32 value);
func_ U32 RoundToU(F32 value);
func_ S32 FloorToS(F32 value);
func_ U32 FloorToU(F32 value);
func_ S32 CeilToS(F32 value);
func_ U32 CeilToU(F32 value);
func_ F32 Square(F32 value);
func_ F32 SafeRatioN(F32 numerator, F32 divisor, F32 N);
func_ F32 SafeRatio0(F32 numerator, F32 divisor);
func_ F32 SafeRatio1(F32 numerator, F32 divisor);
func_ F32 PosInf(void);
func_ F32 NegInf(void);
func_ F32 NegZero(void);
func_ F32 AbsValue(F32 value);
func_ F32 Sqrt(F32 value);
func_ F32 Sin(F32 value);
func_ F32 Cos(F32 value);
func_ F32 Tan(F32 value);
func_ F32 Lerp(F32 a, F32 t, F32 b);
func_ F32 FindT(F32 start, F32 between, F32 end);

// F64

func_ S64 F64_RoundToS(F64 value);
func_ U64 F64_RoundToU(F64 value);
func_ S64 F64_FloorToS(F64 value);
func_ U64 F64_FloorToU(F64 value);
func_ S64 F64_CeilToS(F64 value);
func_ U64 F64_CeilToU(F64 value);
func_ F64 F64_Square(F64 value);
func_ F64 F64_SafeRatioN(F64 numerator, F64 divisor, F64 n);
func_ F64 F64_SafeRatio0(F64 numerator, F64 divisor);
func_ F64 F64_SafeRatio1(F64 numerator, F64 divisor);
func_ F64 F64_PosInf(void);
func_ F64 F64_NegInf(void);
func_ F64 F64_NegZero(void);
func_ F64 F64_AbsValue(F64 value);
func_ F64 F64_Sqrt(F64 value);
func_ F64 F64_Sin(F64 value);
func_ F64 F64_Cos(F64 value);
func_ F64 F64_Tan(F64 value);
func_ F64 F64_Lerp(F64 a, F64 t, F64 b);
func_ F64 F64_FindT(F64 start, F64 between, F64 end);

/////////////////////////////
//~ NOTE(nates): Range functions

func_ R1 MR1(F32 x, F32 y);
func_ R1I MR1I(S32 x, S32 y);

func_ R2 MR2(F32 x0, F32 y0, F32 x1, F32 y1);
func_ R2I MR2I(S32 x0, S32 y0, S32 x1, S32 y1);
func_ R2 R2R(R1 a, R1 b);
func_ R2 R2V(V2 a, V2 b);

func_ R3 MR3(F32 x0, F32 y0, F32 z0, F32 x1, F32 y1, F32 z1);
func_ R3 R3R(R1 a, R1 b, R1 c);
func_ R3 R3V(V3 a, V3 b, V3 c);

/////////////////////////////
// NOTE(nates): V2 Math Functions

func_ V2 MV2(F32 x, F32 y);
func_ V2 MV2a(F32 S);
func_ V2 MV2s(S32 X, S32 Y);
func_ V2 V2Neg(V2 A);
func_ V2 V2Add(V2 A, V2 B);
func_ V2 V2Sub(V2 A, V2 B);
func_ V2 V2MS(V2 A, F32 B);
func_ V2 V2DS(V2 A, F32 B);
func_ F32 V2Dot(V2 A, V2 B);
func_ V2 V2Had(V2 A, V2 B);
func_ F32 V2LenSq(V2 A);
func_ F32 V2Len(V2 A);
func_ V2 V2Norm(V2 A);
func_ V2 V2Perp(V2 A);
func_ V2 V2Lerp(V2 A, F32 t, V2 B);
func_ V2 V2TriProd(V2 A2, V2 B2);

/////////////////////////////////////
// nates: V2s functions

func_ V2I MV2I(S32 x, S32 y);
func_ V2I V2IAdd(V2I a, V2I b);
func_ V2I V2ISub(V2I a, V2I b);

///////////////////////////////
//NOTE(nates): V3 Math Functions

func_ V3 MV3(F32 x, F32 y, F32 z);
func_ V3 MV3a(F32 S);
func_ V3 MV3xy(V2 XY, F32 z);
func_ V3 MV3yz(F32 x, V2 YZ);
func_ V3 V3Neg(V3 a);
func_ V3 V3Add(V3 a, V3 b);
func_ V3 V3Sub(V3 a, V3 b);
func_ V3 V3MS(V3 a, F32 b);
func_ V3 V3DS(V3 a, F32 b);
func_ F32 V3Dot(V3 a, V3 b);
func_ V3 V3Had(V3 a, V3 b);
func_ F32 V3Len(V3 a);
func_ F32 V3LenSq(V3 a);
func_ V3 V3Norm(V3 a);
func_ V3 V3Cross(V3 a, V3 b);
func_ V3 V3Lerp(V3 a, F32 t, V3 b);
func_ F32 PlaneIntersectT(V3 planep, V3 plane_normal, V3 line_start, V3 line_end);
func_ V3 PlaneIntersection(V3 planep, V3 plane_normal, V3 line_, V3 line_end);
func_ V3 V3AARot(V3 point, V3 axis, F32 angle);


////////////////////////////////
// NOTE(nates): V4 Math Functions

func_ V4 MV4(F32 x, F32 y, F32 z, F32 w);
func_ V4 MV4a(F32 a);
func_ V4 MV4xyz(V3 XYZ, F32 w);
func_ V4 V4Add(V4 a, V4 b);
func_ V4 V4Sub(V4 a, V4 b);
func_ V4 V4MS(V4 a, F32 b);
func_ V4 V4DS(V4 a, F32 b);
func_ F32 V4Dot(V4 a, V4 b);
func_ F32 V4Len(V4 a);
func_ F32 V4LenSq(V4 a);
func_ V4 V4UnpackColor(U32 color);
func_ U32 V4PackColor(V4 color);
///////////////////////////////
// NOTE(nates): m44 functions

func_ M44 M44Mul(M44 A, M44 B);
func_ M44 M44Transpose(M44 A);
func_ M44 M44Perspective(F32 screen_width_in_meters, F32 screen_height_in_meters, F32 near_plane, F32 far_plane);
func_ M44 M44Orthographic(F32 screen_width_in_meters, F32 screen_height_in_meters, F32 near_plane, F32 far_plane);
func_ M44 M44CameraTransform(V3 xaxis, V3 yaxis, V3 zaxis, V3 camerap);
func_ V4  M44MulV4(M44 a, V4 b);
func_ V3  M44MulV3(M44 a, V3 b);
func_ M44 M44Col3x3(V3 x, V3 y, V3 z);
func_ M44 M44Row3x3(V3 x, V3 y, V3 z);
func_ V3  M44Col3(M44 a, U32 col_index);
func_ V3  M44Row3(M44 a, U32 row_index);
func_ M44 M44AddTranslation(M44 A, V3 T);
func_ M44 M44Translation(V3 t);
func_ M44 M44Scale(V3 s);
func_ M44 M44Identity(void);
func_ M44 M44XRotDeg(F32 angle);
func_ M44 M44YRotDeg(F32 angle);
func_ M44 M44ZRotDeg(F32 angle);
func_ M44 M44XRotRad(F32 angle);
func_ M44 M44YRotRad(F32 angle);
func_ M44 M44ZRotRad(F32 angle);

//////////////////////////////////
// nates: rect functions

func_ R2 R2MM(V2 min, V2 max);
func_ R2 R2CR(V2 center, V2 radius);
func_ R2 R2CD(V2 center, V2 dim);

//////////////////////////
// nates: rectS32 functions

func_ R2I R2IMM(V2I min, V2I max);



#endif //BASE_MATH_H
