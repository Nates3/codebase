/* date = July 7th 2022 7:59 pm */

#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "math.h"

typedef union v2
{
	r32 e[2];
	struct
	{
		r32 x, y;
	};
} v2;

typedef union v2i
{
	s32 e[2];
	struct
	{
		s32 x, y;
	};
} v2i;

typedef union v3
{
	r32 e[3];
	struct
	{
		r32 x, y, z;
	};
	struct
	{
		r32 r, g, b;
	};
	struct
	{
		v2 xy;
		r32 IGNOREDZ_0;
	};
	struct
	{
		r32 IGNORED_X;
		r32 yz;
	};
}v3;

typedef union v4
{
	r32 e[4];
	union
	{
		struct
		{
			r32 x, y, z, w;
		};
		
		struct
		{
			v3 xyz;
			r32 IGNORED_0;
		};
	};
	
	union
	{
		struct
		{
			r32 r, g, b, a;
		};
		
		struct
		{
			v3 rgb;
			r32 IGNORED_1;
		};
	};
} v4;

typedef union rng1
{
	r32 e[2];
	r32 Min, Max;
}rng1;

typedef union rng1i
{
	s32 e[2];
	s32 Min, Max;
}rng1i;

typedef union rng2
{
	r32 e[4];
	struct 
	{
		v2 p0, p1;
	};
	struct 
	{
		v2 Min, Max;
	};
	struct
	{
		r32 x0, y0;
		r32 x1, y1;
	};
} rng2;

typedef union rng2i
{
	s32 e[4];
	struct
	{
		v2i p0, p1;
	};
	struct
	{
		v2i Min, Max;
	};
	struct
	{
		s32 x0, y0;
		s32 x1, y1;
	};
} rng2i;

typedef union rng3
{
	r32 e[6];
	struct
	{
		v3 min;
		v3 max;
	};
	struct
	{
		r32 x0, y0, z0;
		r32 x1, y1, z1;
	};
} rng3;

typedef struct m44
{
	r32 e[4][4];
} m44;

typedef union qur
{
	struct
	{
		r32 x, y, z, w;
	};
	
	struct
	{
		v3 xyz;
		r32 IGNORED_0;
	};
} qur;

///////////////////////////
// NOTE(nates): Integer math functions

func_ s16 AbsValueS16(s16 Value);
func_ u64 U64EncodeFromS64(s64 number);
func_ s64 S64DecodeFromU64(u64 number);

///////////////////////////
// NOTE(nates): Real math functions

func_ s32 RoundR32ToS32(r32 Value);
func_ u32 RoundR32ToU32(r32 Value);
func_ s32 FloorR32ToS32(r32 Value);
func_ u32 FloorR32ToU32(r32 Value);
func_ s32 CeilR32ToS32(r32 Value);
func_ u32 CeilR32ToU32(r32 Value);
func_ r32 Square(r32 Value);
func_ r32 SafeRatioN(r32 Numerator, r32 Divisor, r32 N);
func_ r32 SafeRatio0(r32 Numerator, r32 Divisor);
func_ r32 SafeRatio1(r32 Numerator, r32 Divisor);
func_ r32 R32PosInf(void);
func_ r32 R32NegInf(void);
func_ r32 R32NegZero(void);
func_ r32 AbsValue(r32 Value);
func_ r32 Sqrt(r32 Value);
func_ r32 Sin(r32 Value);
func_ r32 Cos(r32 Value);
func_ r32 Tan(r32 Value);
func_ r32 Lerp(r32 A, r32 t, r32 B);
func_ r32 FindT(r32 Start, r32 Between, r32 End);

// F64

func_ s64 RoundR64ToS64(r64 Value);
func_ u64 RoundR64ToU64(r64 Value);
func_ s64 FloorR64ToS64(r64 Value);
func_ u64 FloorR64ToU64(r64 Value);
func_ s64 CeilR64ToS64(r64 Value);
func_ u64 CeilR64ToU64(r64 Value);
func_ r64 SquareR64(r64 Value);
func_ r64 SafeRationNR64(r64 Numerator, r64 Divisor, r64 N);
func_ r64 SafeRatio0R64(r64 Numerator, r64 Divisor);
func_ r64 SafeRatio1R64(r64 Numerator, r64 Divisor);
func_ r64 R64PosInf(void);
func_ r64 R64NegInf(void);
func_ r64 R64NegZero(void);
func_ r64 AbsValueR64(r64 Value);
func_ r64 SqrtR64(r64 Value);
func_ r64 SinR64(r64 Value);
func_ r64 CosR64(r64 Value);
func_ r64 TanR64(r64 Value);
func_ r64 LerpR64(r64 A, r64 t, r64 B);
func_ r64 FindTR64(r64 Start, r64 Between, r64 End);

/////////////////////////////
//~ NOTE(nates): Range functions

func_ rng1 R1R32(r32 x, r32 y);
func_ rng1i R1S32(s32 x, s32 y);

func_ rng2 R2R32(r32 x0, r32 y0, r32 x1, r32 y1);
func_ rng2i R2S32(s32 x0, s32 y0, s32 x1, s32 y1);
func_ rng2 R2R32R(rng1 a, rng1 b);
func_ rng2 R2R32V(v2 a, v2 b);

func_ rng3 R3R32(r32 x0, r32 y0, r32 z0, r32 x1, r32 y1, r32 z1);
func_ rng3 R3R32R(rng1 a, rng1 b, rng1 c);
func_ rng3 R3R32V(v3 a, v3 b, v3 c);

/////////////////////////////
// NOTE(nates): v2 Math Functions

func_ v2 V2(r32 x, r32 y);
func_ v2 V2a(r32 S);
func_ v2 V2s(s32 X, s32 Y);
func_ v2 V2Neg(v2 A);
func_ v2 V2Add(v2 A, v2 B);
func_ v2 V2Sub(v2 A, v2 B);
func_ v2 V2MS(v2 A, r32 B);
func_ v2 V2DS(v2 A, r32 B);
func_ r32 V2Dot(v2 A, v2 B);
func_ v2 V2Had(v2 A, v2 B);
func_ r32 V2LenSq(v2 A);
func_ r32 V2Len(v2 A);
func_ v2 V2Norm(v2 A);
func_ v2 V2Perp(v2 A);
func_ v2 V2Lerp(v2 A, r32 t, v2 B);
func_ v2 V2TriProd(v2 A2, v2 B2);

/////////////////////////////////////
// nates: v2s functions

func_ v2i V2I(s32 x, s32 y);
func_ v2i V2IAdd(v2i a, v2i b);
func_ v2i V2ISub(v2i a, v2i b);

///////////////////////////////
//NOTE(nates): v3 Math Functions

func_ v3 V3(r32 x, r32 y, r32 z);
func_ v3 V3a(r32 S);
func_ v3 V3xy(v2 XY, r32 z);
func_ v3 V3yz(r32 x, v2 YZ);
func_ v3 V3Neg(v3 A);
func_ v3 V3Add(v3 A, v3 B);
func_ v3 V3Sub(v3 A, v3 B);
func_ v3 V3MS(v3 A, r32 B);
func_ v3 V3DS(v3 A, r32 B);
func_ r32 V3Dot(v3 A, v3 B);
func_ v3 V3Had(v3 A, v3 B);
func_ r32 V3Len(v3 A);
func_ r32 V3LenSq(v3 A);
func_ v3 V3Norm(v3 A);
func_ v3 V3Cross(v3 A, v3 B);
func_ v3 V3Lerp(v3 A, r32 t, v3 B);
func_ r32 PlaneIntersectT(v3 PlaneP, v3 PlaneNormal, v3 LineStart, v3 LineEnd);
func_ v3 PlaneIntersection(v3 PlaneP, v3 PlaneNormal, v3 LineStart, v3 LineEnd);
func_ v3 V3AARot(v3 Point, v3 Axis, r32 Angle);


////////////////////////////////
// NOTE(nates): v4 Math Functions

func_ v4 V4(r32 x, r32 y, r32 z, r32 w);
func_ v4 V4a(r32 A);
func_ v4 V4xyz(v3 XYZ, r32 w);
func_ v4 V4Add(v4 A, v4 B);
func_ v4 V4Sub(v4 A, v4 B);
func_ v4 V4MS(v4 A, r32 B);
func_ v4 V4DS(v4 A, r32 B);
func_ r32 V4Dot(v4 A, v4 B);
func_ r32 V4Len(v4 A);
func_ r32 V4LenSq(v4 A);
func_ v4 V4UnpackColor(u32 color);
func_ u32 V4PackColor(v4 color);
///////////////////////////////
// NOTE(nates): m44 functions

func_ m44 M44Mul(m44 A, m44 B);
func_ m44 M44Transpose(m44 A);
func_ m44 M44Perspective(r32 screen_width_in_meters, r32 screen_height_in_meters, r32 near_plane, r32 far_plane);
func_ m44 M44Orthographic(r32 screen_width_in_meters, r32 screen_height_in_meters, r32 near_plane, r32 far_plane);
func_ m44 M44CameraTransform(v3 xaxis, v3 yaxis, v3 zaxis, v3 camerap);
func_ v4  M44MulV4(m44 A, v4 B);
func_ v3  M44MulV3(m44 A, v3 B);
func_ m44 M44Col3x3(v3 X, v3 Y, v3 Z);
func_ m44 M44Row3x3(v3 X, v3 Y, v3 Z);
func_ v3  M44Col3(m44 A, u32 ColIndex);
func_ v3  M44Row3(m44 A, u32 RowIndex);
func_ m44 M44AddTranslation(m44 A, v3 T);
func_ m44 M44Translation(v3 t);
func_ m44 M44Scale(v3 s);
func_ m44 M44Identity(void);
func_ m44 M44XRotDeg(r32 Angle);
func_ m44 M44YRotDeg(r32 Angle);
func_ m44 M44ZRotDeg(r32 Angle);
func_ m44 M44XRotRad(r32 Angle);
func_ m44 M44YRotRad(r32 Angle);
func_ m44 M44ZRotRad(r32 Angle);

//////////////////////////////////
// nates: rect functions

func_ rng2 Rng2MM(v2 min, v2 max);
func_ rng2 Rng2CR(v2 center, v2 radius);
func_ rng2 Rng2CD(v2 center, v2 dim);

//////////////////////////
// nates: rects32 functions

func_ rng2i Rng2IMM(v2i min, v2i max);



#endif //BASE_MATH_H
