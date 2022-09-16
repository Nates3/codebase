
#include "base_math.h"

/////////////////////////////////////
// NOTE(nates): Integer math functions


func_ s16
AbsValueS16(s16 Value)
{
	if(Value < 0)
	{
		Value *= -1;
	}
	s16 Result = Value;
	return(Result);
}

func_ u64
U64EncodeFromS64(s64 number)
{
	// NOTE(nates): rotleft(x, 1)
	u64 result = (((s64)number) << 1) | (((u64)number) >> 63);
	return(result);
}

func_ s64
S64DecodeFromU64(u64 number)
{
	s64 result = (s64)((number >> 1) | (number << 63));
	return(result);
}

///////////////////////////////////
// NOTE(nates): Real Math Functions


func_ s32
RoundR32ToS32(r32 Value)
{
	s32 Result = (s32)roundf(Value);
	return(Result);
}

func_ u32
RoundR32ToU32(r32 Value)
{
	u32 Result = (u32)roundf(Value);
	return(Result);
}

func_ s32
FloorR32ToS32(r32 Value)
{
	s32 Result = (s32)floorf(Value);
	return(Result);
}

func_ u32
FloorR32ToU32(r32 Value)
{
	u32 Result = (u32)floorf(Value);
	return(Result);
}

func_ s32
CeilR32ToS32(r32 Value)
{
	s32 Result = (s32)ceilf(Value);
	return(Result);
}

func_ u32
CeilR32ToU32(r32 Value)
{
	u32 Result = (u32)ceilf(Value);
	return(Result);
}

func_ r32
Square(r32 Value)
{
	r32 Result = Value*Value;
	return(Result);
}

func_ r32
SafeRatioN(r32 Numerator, r32 Divisor, r32 N)
{
	r32 Result = N;
	if(Divisor != 0.0f)
	{
		Result = Numerator / Divisor;
	}
	return(Result);
}

func_ r32
SafeRatio0(r32 Numerator, r32 Divisor)
{
	r32 Result = SafeRatioN(Numerator, Divisor, 0.0f);
	
	return(Result);
}

func_ r32
SafeRatio1(r32 Numerator, r32 Divisor)
{
	r32 Result = SafeRatioN(Numerator, Divisor, 1.0f);
	return(Result);
}

func_ r32
R32PosInf(void)
{
	typedef union { r32 f; u32 u; } un;
	
	un r = {0};
	r.u = 0x7f800000;
	return(r.f);
}

func_ r32
R32NegInf(void)
{
	typedef union { r32 f; u32 u; } un;
	
	un r = {0};
	r.u = 0xff800000;
	return(r.f);
}

func_ r32
R32NegZero(void)
{
	typedef union { r32 f; u32 u; } un;
	
	un r = {0};
	r.u = 0x80000000;
	return(r.f);
}


func_ r32 
AbsValue(r32 Value)
{
	typedef union { r32 f; u32 u; } un;
	un r;
	r.f = Value;
	r.u &= 0x7fffffff;
	return(r.f);
}

func_ r32 
Sqrt(r32 Value)
{
	r32 Result = sqrtf(Value);
	return(Result);
}

func_ r32
Sin(r32 Value)
{
	r32 Result = sinf(Value);
	return(Result);
}

func_ r32
Cos(r32 Value)
{
	r32 Result = cosf(Value);
	return(Result);
}

func_ r32
Tan(r32 Value)
{ 
	r32 Result = tanf(Value);
	return(Result);
}

func_ r32
Lerp(r32 A, r32 t, r32 B)
{
	r32 Result = (1.0f - t)*A + B;
	return(Result);
}

func_ r32
FindT(r32 Start, r32 Between, r32 End)
{
	r32 t = 0.0f;
	if(Start != End)
	{
		t = (Between - Start) / (End - Start);
	}
	
	return(t);
}

////////////////////
// NOTE(nates): r64 Math Functions

func_ s64
RoundR64ToS64(r64 Value)
{
	s64 Result = (s64)round(Value);
	return(Result);
}

func_ u64
RoundR64ToU64(r64 Value)
{
	u64 Result = (u64)round(Value);
	return(Result);
}

func_ s64
FloorR64ToS64(r64 Value)
{
	s64 Result = (s64)floor(Value);
	return(Result);
}

func_ u64
FloorR64ToU64(r64 Value)
{
	u64 Result = (u64)floor(Value);
	return(Result);
}

func_ s64
CeilR64ToS64(r64 Value)
{
	s64 Result = (s64)ceil(Value);
	return(Result);
}

func_ u64
CeilR64ToU64(r64 Value)
{
	u64 Result = (u64)ceil(Value);
	return(Result);
}

func_ r64
SquareR64(r64 Value)
{
	r64 Result = Value*Value;
	return(Result);
}

func_ r64
SafeRationNR64(r64 Numerator, r64 Divisor, r64 N)
{
	r64 Result = N;
	if(Divisor != 0.0)
	{
		Result = Numerator / Divisor;
	}
	return(Result);
}

func_ r64
SafeRatio0R64(r64 Numerator, r64 Divisor)
{
	r64 Result = SafeRatioNR64(Numerator, Divisor, 0.0);
	
	return(Result);
}

func_ r64
SafeRatio1R64(r64 Numerator, r64 Divisor)
{
	r64 Result = SafeRatioNR64(Numerator, Divisor, 1.0);
	return(Result);
}

func_ r64
R64PosInf(void)
{
	typedef union { r64 f; u64 u; } un;
	
	un r = {0};
	r.u = 0x7f800000;
	return(r.f);
}

func_ r64
R64NegInf(void)
{
	typedef union { r64 f; u64 u; } un;
	
	un r = {0};
	r.u = 0xff800000;
	return(r.f);
}

func_ r64
R64NegZero(void)
{
	typedef union { r64 f; u64 u; } un;
	
	un r = {0};
	r.u = 0x80000000;
	return(r.f);
}

func_ r64 
AbsValueR64(r64 Value)
{
	typedef union { r64 f; u64 u; } un;
	un r;
	r.f = Value;
	r.u &= 0x7fffffff;
	return(r.f);
}

func_ r64 
SqrtR64(r64 Value)
{
	r64 Result = sqrt(Value);
	return(Result);
}

func_ r64
SinR64(r64 Value)
{
	r64 Result = sin(Value);
	return(Result);
}

func_ r64
CosR64(r64 Value)
{
	r64 Result = cos(Value);
	return(Result);
}

func_ r64
TanR64(r64 Value)
{ 
	r64 Result = tan(Value);
	return(Result);
}

func_ r64
LerpR64(r64 A, r64 t, r64 B)
{
	r64 Result = (1.0 - t)*A + B;
	return(Result);
}

func_ r64
FindTR64(r64 Start, r64 Between, r64 End)
{
	r64 t = 0.0;
	if(Start != End)
	{
		t = (Between - Start) / (End - Start);
	}
	
	return(t);
}

/////////////////////////////////////////
//~ NOTE(nates): Range functions

func_ rng1 R1R32(r32 x, r32 y)
{
	rng1 result = {x, y};
	return(result);
}

func_ rng1i R1S32(s32 x, s32 y)
{
	rng1i result = {x, y};
	return(result);
}

func_ rng2 R2R32(r32 x0, r32 y0, r32 x1, r32 y1)
{
	rng2 result = {x0, y0, x1, y1};
	return(result);
}

func_ rng2i R2S32(s32 x0, s32 y0, s32 x1, s32 y1)
{
	rng2i result = {x0, y0, x1, y1};
	return(result);
}
func_ rng2 R2R32R(rng1 a, rng1 b)
{
	rng2 result = {a.Min, b.Min, a.Max, b.Max};
	return(result);
}

func_ rng2 R2R32V(v2 a, v2 b)
{
	rng2 result = {a.x, b.x, a.y, b.y};
	return(result);
}

func_ rng3 R3R32(r32 x0, r32 y0, r32 z0, r32 x1, r32 y1, r32 z1)
{
	rng3 result = {x0, y0, z0, x1, y1, z1};
	return(result);
}

func_ rng3 R3R32R(rng1 a, rng1 b, rng1 c)
{
	rng3 result = {a.Min, b.Min, c.Min, a.Max, b.Max, c.Max};
	return(result);
}
func_ rng3 R3R32V(v3 a, v3 b, v3 c)
{
	rng3 result = {a.x, b.x, c.x, a.y, b.y, c.y};
	return(result);
}



////////////////////////
//~ NOTE(nates): Vector2!

func_ v2
V2(r32 x, r32 y)
{
	v2 Result = {x, y};
	return(Result);
}

func_ v2
V2a(r32 S)
{
	v2 Result = {
		.x = S,
		.y = S,
	};
	
	return(Result);
}

func_ v2
V2s(s32 X, s32 Y)
{
	v2 Result = V2((r32)X, (r32)Y);
	return(Result);
}

func_ v2 
V2Neg(v2 A)
{
	v2 Result = {
		.x = -A.x,
		.y = -A.y,
	};
	return(Result);
}

func_ v2
V2Add(v2 A, v2 B)
{
	v2 Result;
	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	
	return(Result);
}

func_ v2
V2Sub(v2 A, v2 B)
{
	v2 Result;
	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	return(Result);
}

func_ v2
V2MS(v2 A, r32 B)
{
	v2 Result = {
		.x = A.x*B,
		.y = A.y*B,
	};
	return(Result);
}

func_ v2
V2DS(v2 A, r32 B)
{
	v2 Result = {
		.x = A.x/B,
		.y = A.y/B,
	};
	return(Result);
}

func_ r32
V2Dot(v2 A, v2 B)
{
	r32 Result = A.x*B.x + A.y*B.y;
	return(Result);
}

func_ v2
V2Had(v2 A, v2 B)
{
	v2 Result = {A.x*B.x, A.y*B.y};
	return(Result);
}

func_ r32
V2LenSq(v2 A)
{
	r32 Result = V2Dot(A, A);
	return(Result);
}

func_ r32
V2Len(v2 A)
{
	r32 Result = sqrt(V2Dot(A, A));
	return(Result);
}

func_ v2
V2Norm(v2 A)
{
	v2 Result = {0};
	if(v2LenSq(A) != 0.0f)
	{
		Result = V2DS(A, V2Len(A));
	}
	
	return(Result);
}

func_ v2
V2Perp(v2 A)
{
	v2 Result;
	Result.x = -A.y;
	Result.y = A.x;
	return(Result);
}

func_ v2
V2Lerp(v2 A, r32 t, v2 B)
{
	v2 Result = V2Add(V2MS(A, (1.0f - t)),
										V2MS(B, t));
	return(Result);
}

func_ v2
V2TriProd(v2 A2, v2 B2)
{
	v3 A = V3xy(A2, 0.0f);
	v3 B = V3xy(B2, 0.0f);
	v3 Cross = V3Cross(A, B);
	v2 Result = V3Cross(Cross, A).xy;
	return(Result);
}

/////////////////////////
// NOTE(nates): v2i

func_ v2i
V2I(s32 x, s32 y)
{
	v2i result = {x, y};
	return(result);
}

func_ v2i
V2IAdd(v2i a, v2i b)
{
	v2i result = {
		a.x + b.x,
		a.y + b.y,
	};
	return(result);
}

func_ v2i
V2ISub(v2i a, v2i b)
{
	v2i result = {
		a.x - b.x,
		a.y - b.y,
	};
	return(result);
}

///////////////////////
// NOTE(nates): Vector3!

func_ v3
V3(r32 x, r32 y, r32 z)
{
	v3 Result = {x, y, z};
	return(Result);
}

func_ v3
V3a(r32 S)
{
	v3 Result = {S, S, S};
	return(Result);
}

func_ v3
V3xy(v2 XY, r32 z)
{
	v3 Result;
	Result.x = XY.x;
	Result.y = XY.y;
	Result.z = z;
	
	return(Result);
}

func_ v3
V3yz(r32 x, v2 YZ)
{
	v3 Result;
	Result.x = x;
	Result.y = YZ.x;
	Result.z = YZ.y;
	return(Result);
}

func_ v3 
V3Neg(v3 A)
{
	v3 Result = {
		.x = -A.x,
		.y = -A.y,
		.z = -A.z,
	};
	return(Result);
}

func_ v3
V3Add(v3 A, v3 B)
{
	v3 Result;
	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	Result.z = A.z + B.z;
	
	return(Result);
}

func_ v3
V3Sub(v3 A, v3 B)
{
	v3 Result;
	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	Result.z = A.z - B.z;
	
	return(Result);
}

func_ v3
V3MS(v3 A, r32 B)
{
	v3 Result = {
		.x = A.x*B,
		.y = A.y*B,
		.z = A.z*B,
	};
	
	return(Result);
}

func_ v3
V3DS(v3 A, r32 B)
{
	v3 Result = {
		.x = A.x/B,
		.y = A.y/B,
		.z = A.z/B,
	};
	return(Result);
}

func_ r32
V3Dot(v3 A, v3 B)
{
	r32 Result = A.x*B.x + A.y*B.y + A.z*B.z;
	return(Result);
}


func_ v3
V3Had(v3 A, v3 B)
{
	v3 Result = {A.x*B.x, A.y*B.y, A.z*B.z};
	return(Result);
}

func_ r32
V3Len(v3 A)
{
	r32 Result = sqrt(V3Dot(A, A));
	return(Result);
}

func_ r32
V3LenSq(v3 A)
{
	r32 Result = V3Dot(A, A);
	return(Result);
}

func_ v3
V3Norm(v3 A)
{
	v3 Result = {0};
	if(V3LenSq(A) != 0.0f)
	{
		Result = V3DS(A, V3Len(A));
	}
	
	return(Result);
}

func_ v3
V3Cross(v3 A, v3 B)
{
	v3 Result;
	Result.x = A.y*B.z - A.z*B.y;
	Result.y = A.z*B.x - A.x*B.z;
	Result.z = A.x*B.y - A.y*B.x;
	return(Result);
}

func_ v3
V3Lerp(v3 A, r32 t, v3 B)
{
	v3 Result = V3Add(V3MS(A, (1.0f - t)),
										V3MS(B, t));
	return(Result);
}

func_ r32
PlaneIntersectT(v3 PlaneP, v3 PlaneNormal, v3 LineStart, v3 LineEnd)
{
	Assert(v3Len(PlaneNormal) <= 1.01f);
	r32 PlaneProjection = V3Dot(PlaneNormal, PlaneP);
	r32 StartProjection = V3Dot(LineStart, PlaneNormal);
	r32 EndProjection = V3Dot(LineEnd, PlaneNormal);
	r32 t = (PlaneProjection - StartProjection) / (EndProjection - StartProjection);
	return(t);
}

func_ v3
PlaneIntersection(v3 PlaneP, v3 PlaneNormal, v3 LineStart, v3 LineEnd)
{
	// NOTE(nates): Finds intersection point between line and a plane
	Assert(v3Len(PlaneNormal) <= 1.01f);
	r32 PlaneProjection = V3Dot(PlaneNormal, PlaneP);
	r32 StartProjection = V3Dot(LineStart, PlaneNormal);
	r32 EndProjection = V3Dot(LineEnd, PlaneNormal);
	r32 t = (PlaneProjection - StartProjection) / (EndProjection - StartProjection);
	v3 Result = V3Add(LineStart, V3MS(V3Sub(LineEnd, LineStart), t));
	return(Result);
}

func_ v3
V3AARot(v3 Point, v3 axis, r32 Angle)
{
	Angle = Angle*DegreesToRadians;
	
	r32 Proj = v3dot(Point, axis);
	v3 p = V3MS(axis, Proj);
	v3 e = V3Sub(Point, p);
	v3 f = V3Cross(axis, Point);
	v3 ep = V3Add(V3MS(e, Cos(Angle)), V3MS(f, Sin(Angle)));
	
	v3 Result = V3Add(p,ep);
	return(Result);
}

//////////////////////////////
// NOTE(nates): Vector 4!!

func_ v4
V4(r32 x, r32 y, r32 z, r32 w)
{
	v4 Result = {x, y, z, w};
	return(Result);
}

func_ v4
V4a(r32 S)
{
	v4 Result = 
	{
		.x = S, .y = S, .z = S, .w = S,
	};
	return(Result);
}

func_ v4
V4xyz(v3 XYZ, r32 w)
{
	v4 Result;
	Result.x = XYZ.x;
	Result.y = XYZ.y;
	Result.z = XYZ.z;
	Result.w = w;
	
	return(Result);
}


func_ v4
V4Add(v4 A, v4 B)
{
	v4 Result;
	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	Result.z = A.z + B.z;
	Result.w = A.w + B.w;
	
	return(Result);
}

func_ v4
V4Sub(v4 A, v4 B)
{
	v4 Result;
	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	Result.z = A.z - B.z;
	Result.w = A.w - B.w;
	
	return(Result);
}

func_ v4
V4MS(v4 A, r32 B)
{
	v4 Result = {
		.x = A.x*B,
		.y = A.y*B,
		.z = A.z*B,
		.w = A.w*B,
	};
	return(Result);
}

func_ v4
V4DS(v4 A, r32 B)
{
	v4 Result = {
		.x = A.x/B,
		.y = A.y/B,
		.z = A.z/B,
		.w = A.w/B,
	};
	return(Result);
}

func_ r32
V4Dot(v4 A, v4 B)
{
	r32 Result = A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;
	return(Result);
}

func_ r32
V4Len(v4 A)
{
	r32 Result = Sqrt(V4Dot(A, A));
	return(Result);
}

func_ r32
V4LenSq(v4 A)
{
	r32 Result = V4Dot(A, A);
	return(Result);
}

func_ v4
V4UnpackColor(u32 color)
{
	r32 inv255 = 1.f / 255.f;
	v4 result = V4((r32)((color >> 16) & 0xff),
								 (r32)((color >> 8) & 0xff),
								 (r32)((color & 0xff)),
								 (r32)(color >> 24));
	result = V4MS(result, inv255);
	return(result);
}

func_ u32
V4PackColor(v4 color)
{
	u32 result = ((u32)(color.a*255.0f) << 24,
								(u32)(color.r*255.0f) << 16,
								(u32)(color.g*255.0f) << 8,
								(u32)(color.b*255.0f));
	return(result);
}


//////////////////////////////////
// NOTE(nates): m44


func_ m44
M44Mul(m44 A, m44 B)
{
	m44 Result = {0};
	
	for(u32 r = 0;
			r < 4;
			++r)
	{
		for(u32 c = 0;
				c < 4;
				++c)
		{
			for(u32 i = 0;
					i < 4;
					++i)
			{
				Result.e[r][c] += A.e[r][i]*B.e[i][c];
			}
		}
	}
	
	return(Result);
}

func_ m44
M44Transpose(m44 A)
{
	m44 Result;
	for(u32 r = 0;
			r < 4;
			++r)
	{
		for(u32 c = 0;
				c < 4;
				++c)
		{
			Result.e[r][c] = A.e[c][r];
		}
	}
	
	return(Result);
}

func_ m44
M44Perspective(r32 screen_width_in_meters, r32 screen_height_in_meters, 
							 r32 near_plane, r32 far_plane)
{
	// NOTE(nates): Aspect ratio is height / width
	
	r32 w = screen_width_in_meters;
	r32 h = screen_height_in_meters;
	r32 n = near_plane;
	r32 f = far_plane;
	r32 d = f/(f-n);
	
	m44 result = {
		{ 
			{2*n/w, 0,     0,  0}, 
			{0,     2*n/h, 0,  0},
			{0,     0,     d, -n*d},
			{0,     0,     1,  0},
		},
	};
	
#if 0
	// minimal d3d example
	{2*n/w, 0,     0,           0, 
		0,     2*n/h, 0,           0, 
		0,     0,     f/(f - n),   n*f/(n - f), 
		0,     0,     1,           0 };
#endif
	
	return(result);
}

func_ m44
M44Orthographic(r32 screen_width_in_meters, r32 screen_height_in_meters, 
								r32 near_plane, r32 far_plane)
{
	// NOTE(nates): Aspect ratio is height / width
	
	r32 w = screen_width_in_meters;
	r32 h = screen_height_in_meters;
	r32 n = near_plane;
	r32 f = far_plane;
	r32 d = 1.f/(f-n);
	
	m44 result = {
		{ 
			{2*n/w, 0,     0,  0}, 
			{0,     2*n/h, 0,  0},
			{0,     0,     d, -n*d},
			{0,     0,     0,  1},
		},
	};
	
	return(result);
}

func_ m44
M44CameraTransform(v3 xaxis, v3 yaxis, v3 zaxis, v3 camerap)
{
	m44 result = M44Row3x3(xaxis, yaxis, zaxis);
	v3 translation = V3Neg(M44MulV3(result, camerap));
	result = M44AddTranslation(result, translation);
	return(result);
}

func_ v4
M44MulV4(m44 A, v4 B)
{
	v4 Result;
	Result.x = B.x*A.e[0][0] + B.y*A.e[0][1] + B.z*A.e[0][2] + B.w*A.e[0][3];
	Result.y = B.x*A.e[1][0] + B.y*A.e[1][1] + B.z*A.e[1][2] + B.w*A.e[1][3];
	Result.z = B.x*A.e[2][0] + B.y*A.e[2][1] + B.z*A.e[2][2] + B.w*A.e[2][3];
	Result.w = B.x*A.e[3][0] + B.y*A.e[3][1] + B.z*A.e[3][2] + B.w*A.e[3][3];
	
	return(Result);
}

func_ v3
M44MulV3(m44 A, v3 B)
{
	v4 HomogeneousCoord = V4xyz(B, 1.0f);
	v3 Result = M44MulV4(A, HomogeneousCoord).xyz;
	return(Result);
}

func_ m44
M44Col3x3(v3 X, v3 Y, v3 Z)
{
	m44 Result = {
		{
			{X.x,  Y.x,  Z.x,  0.0f},
			{X.y,  Y.y,  Z.y,  0.0f},
			{X.z,  Y.z,  Z.z,  0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	return(Result);
}

func_ m44
M44Row3x3(v3 X, v3 Y, v3 Z)
{
	m44 Result = {
		{
			{X.x,  X.y,  X.z,  0.0f},
			{Y.x,  Y.y,  Y.z,  0.0f},
			{Z.x,  Z.y,  Z.z,  0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}


func_ v3  
M44Col3(m44 A, u32 ColIndex)
{
	v3 Result = {
		A.e[0][ColIndex],
		A.e[1][ColIndex],
		A.e[2][ColIndex],
	};
	
	return(Result);
}

func_ v3  
M44Row3(m44 A, u32 RowIndex)
{
	v3 Result = {
		A.e[RowIndex][0],
		A.e[RowIndex][1],
		A.e[RowIndex][2],
	};
	
	return(Result);
}

func_ m44
M44AddTranslation(m44 A, v3 T)
{
	m44 R = A;
	R.e[0][3] += T.x;
	R.e[1][3] += T.y;
	R.e[2][3] += T.z;
	return(R);
}

func_ m44 
M44Translation(v3 t)
{
	m44 result = {
		1, 0, 0, t.x,
		0, 1, 0, t.y,
		0, 0, 1, t.z,
		0, 0, 0, 1
	};
	return(result);
}


func_ m44 
M44Scale(v3 s)
{
	m44 result = {
		s.x, 0,   0,   0,
		0,   s.y, 0,   0,
		0,   0,   s.z, 0,
		0,   0,   0,   1,
	};
	return(result);
}

func_ m44
M44Identity(void)
{
	m44 Result = {
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ m44
M44XRotDeg(r32 Angle)
{
	Angle = Angle*DegreesToRadians;
	
	r32 s = Sin(Angle);
	r32 c = Cos(Angle);
	
	m44 Result = {
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f,  c,   -s,   0.0f},
			{0.0f,  s,   c,    0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ m44
M44YRotDeg(r32 Angle)
{
	Angle = Angle*DegreesToRadians;
	r32 s = Sin(Angle);
	r32 c = Cos(Angle);
	
	m44 Result = {
		{
			{c,    0.0f, s,    0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{-s,   0.0f, c,    0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ m44
M44ZRotDeg(r32 Angle)
{
	Angle = Angle*DegreesToRadians;
	r32 s = Sin(Angle);
	r32 c = Cos(Angle);
	
	m44 Result = {
		{
			{c,    -s,   0.0f, 0.0f},
			{s,     c,   0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}


func_ m44
M44XRotRad(r32 Angle)
{
	r32 s = Sin(Angle);
	r32 c = Cos(Angle);
	
	m44 Result = {
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f,  c,   -s,   0.0f},
			{0.0f,  s,   c,    0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ m44
M44YRotRad(r32 Angle)
{
	r32 s = Sin(Angle);
	r32 c = Cos(Angle);
	
	m44 Result = {
		{
			{c,    0.0f, s,    0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{-s,   0.0f, c,    0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ m44
M44ZRotRad(r32 Angle)
{
	r32 s = Sin(Angle);
	r32 c = Cos(Angle);
	
	m44 Result = {
		{
			{c,    -s,   0.0f, 0.0f},
			{s,     c,   0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

//////////////////////////////////
// nates: rect functions

func_ rng2 Rng2MM(v2 min, v2 max)
{
	rng2 result = {
		.Min = min,
		.Max = max,
	};
	return(result);
}

func_ rng2 Rng2CR(v2 center, v2 radius)
{
	rng2 result = {
		.Min = v2sub(center, radius),
		.Max = v2add(center, radius),
	};
	return(result);
}

func_ rng2 Rng2CD(v2 center, v2 dim)
{
	rng2 result = Rng2CR(center, V2MS(dim, .5f));
	return(result);
}

////////////////////////////////
// nates: rect s32 functions

func_ rng2i Rng2IMM(v2i min, v2i max)
{
	rng2i result = {
		.Min = min,
		.Max = max,
	};
	return(result);
}
