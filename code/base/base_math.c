
#include "base_math.h"

/////////////////////////////////////
// NOTE(nates): Integer math functions


func_ S16
AbsValueS16(S16 Value)
{
	if(Value < 0)
	{
		Value *= -1;
	}
	S16 Result = Value;
	return(Result);
}

func_ U64
U64EncodeFromS64(S64 number)
{
	// NOTE(nates): rotleft(x, 1)
	U64 result = (((S64)number) << 1) | (((U64)number) >> 63);
	return(result);
}

func_ S64
S64DecodeFromU64(U64 number)
{
	S64 result = (S64)((number >> 1) | (number << 63));
	return(result);
}

///////////////////////////////////
// NOTE(nates): Real Math Functions


func_ S32
RoundToS(F32 Value)
{
	S32 Result = (S32)roundf(Value);
	return(Result);
}

func_ U32
RoundToU(F32 Value)
{
	U32 Result = (U32)roundf(Value);
	return(Result);
}

func_ S32
FloorToS(F32 Value)
{
	S32 Result = (S32)floorf(Value);
	return(Result);
}

func_ U32
FloorToU(F32 Value)
{
	U32 Result = (U32)floorf(Value);
	return(Result);
}

func_ S32
CeilToS(F32 Value)
{
	S32 Result = (S32)ceilf(Value);
	return(Result);
}

func_ U32
CeilToU(F32 Value)
{
	U32 Result = (U32)ceilf(Value);
	return(Result);
}

func_ F32
Square(F32 Value)
{
	F32 Result = Value*Value;
	return(Result);
}

func_ F32
SafeRatioN(F32 Numerator, F32 Divisor, F32 N)
{
	F32 Result = N;
	if(Divisor != 0.0f)
	{
		Result = Numerator / Divisor;
	}
	return(Result);
}

func_ F32
SafeRatio0(F32 Numerator, F32 Divisor)
{
	F32 Result = SafeRatioN(Numerator, Divisor, 0.0f);
	
	return(Result);
}

func_ F32
SafeRatio1(F32 Numerator, F32 Divisor)
{
	F32 Result = SafeRatioN(Numerator, Divisor, 1.0f);
	return(Result);
}

func_ F32
PosInf(void)
{
	typedef union { F32 f; U32 u; } un;
	
	un r = {0};
	r.u = 0x7f800000;
	return(r.f);
}

func_ F32
NegInf(void)
{
	typedef union { F32 f; U32 u; } un;
	
	un r = {0};
	r.u = 0xff800000;
	return(r.f);
}

func_ F32
NegZero(void)
{
	typedef union { F32 f; U32 u; } un;
	
	un r = {0};
	r.u = 0x80000000;
	return(r.f);
}


func_ F32 
AbsValue(F32 Value)
{
	typedef union { F32 f; U32 u; } un;
	un r;
	r.f = Value;
	r.u &= 0x7fffffff;
	return(r.f);
}

func_ F32 
Sqrt(F32 Value)
{
	F32 Result = sqrtf(Value);
	return(Result);
}

func_ F32
Sin(F32 Value)
{
	F32 Result = sinf(Value);
	return(Result);
}

func_ F32
Cos(F32 Value)
{
	F32 Result = cosf(Value);
	return(Result);
}

func_ F32
Tan(F32 Value)
{ 
	F32 Result = tanf(Value);
	return(Result);
}

func_ F32
Lerp(F32 A, F32 t, F32 B)
{
	F32 Result = (1.0f - t)*A + B;
	return(Result);
}

func_ F32
FindT(F32 Start, F32 Between, F32 End)
{
	F32 t = 0.0f;
	if(Start != End)
	{
		t = (Between - Start) / (End - Start);
	}
	
	return(t);
}

////////////////////
// NOTE(nates): R64 Math Functions

func_ S64
F64_RoundToS(F64 Value)
{
	S64 Result = (S64)round(Value);
	return(Result);
}

func_ U64
F64_RoundToU(F64 Value)
{
	U64 Result = (U64)round(Value);
	return(Result);
}

func_ S64
F64_FloorToS(F64 Value)
{
	S64 Result = (S64)floor(Value);
	return(Result);
}

func_ U64
F64_FloorToU(F64 Value)
{
	U64 Result = (U64)floor(Value);
	return(Result);
}

func_ S64
F64_CeilToS(F64 Value)
{
	S64 Result = (S64)ceil(Value);
	return(Result);
}

func_ U64
F64_CeilToU(F64 Value)
{
	U64 Result = (U64)ceil(Value);
	return(Result);
}

func_ F64
F64_Square(F64 Value)
{
	F64 Result = Value*Value;
	return(Result);
}

func_ F64
F64_SafeRatioN(F64 Numerator, F64 Divisor, F64 N)
{
	F64 Result = N;
	if(Divisor != 0.0)
	{
		Result = Numerator / Divisor;
	}
	return(Result);
}

func_ F64
F64_SafeRatio0(F64 Numerator, F64 Divisor)
{
	F64 Result = SafeRatioNF64(Numerator, Divisor, 0.0);
	
	return(Result);
}

func_ F64
F64_SafeRatio1(F64 Numerator, F64 Divisor)
{
	F64 Result = SafeRatioNF64(Numerator, Divisor, 1.0);
	return(Result);
}

func_ F64
F64_PosInf(void)
{
	typedef union { F64 f; U64 u; } un;
	
	un r = {0};
	r.u = 0x7f800000;
	return(r.f);
}

func_ F64
F64_NegInf(void)
{
	typedef union { F64 f; U64 u; } un;
	
	un r = {0};
	r.u = 0xff800000;
	return(r.f);
}

func_ F64
F64_NegZero(void)
{
	typedef union { F64 f; U64 u; } un;
	
	un r = {0};
	r.u = 0x80000000;
	return(r.f);
}

func_ F64 
F64_AbsValue(F64 Value)
{
	typedef union { F64 f; U64 u; } un;
	un r;
	r.f = Value;
	r.u &= 0x7fffffff;
	return(r.f);
}

func_ F64 
F64_Sqrt(F64 Value)
{
	F64 Result = sqrt(Value);
	return(Result);
}

func_ F64
F64_Sin(F64 Value)
{
	F64 Result = sin(Value);
	return(Result);
}

func_ F64
F64_Cos(F64 Value)
{
	F64 Result = cos(Value);
	return(Result);
}

func_ F64
F64_Tan(F64 Value)
{ 
	F64 Result = tan(Value);
	return(Result);
}

func_ F64
F64_Lerp(F64 A, F64 t, F64 B)
{
	F64 Result = (1.0 - t)*A + B;
	return(Result);
}

func_ F64
F64_FindT(F64 Start, F64 Between, F64 End)
{
	F64 t = 0.0;
	if(Start != End)
	{
		t = (Between - Start) / (End - Start);
	}
	
	return(t);
}

/////////////////////////////////////////
//~ NOTE(nates): Range functions

func_ R1 MR1(F32 x, F32 y)
{
	R1 result = {x, y};
	return(result);
}

func_ R1I MR1I(S32 x, S32 y)
{
	R1I result = {x, y};
	return(result);
}

func_ R2 MR2(F32 x0, F32 y0, F32 x1, F32 y1)
{
	R2 result = {x0, y0, x1, y1};
	return(result);
}

func_ R2I MR2I(S32 x0, S32 y0, S32 x1, S32 y1)
{
	R2I result = {x0, y0, x1, y1};
	return(result);
}
func_ R2 R2R(R1 a, R1 b)
{
	R2 result = {a.min, b.min, a.max, b.max};
	return(result);
}

func_ R2 R2V(V2 a, V2 b)
{
	R2 result = {a.x, b.x, a.y, b.y};
	return(result);
}

func_ R3 MR3(F32 x0, F32 y0, F32 z0, F32 x1, F32 y1, F32 z1)
{
	R3 result = {x0, y0, z0, x1, y1, z1};
	return(result);
}

func_ R3 R3R(R1 a, R1 b, R1 c)
{
	R3 result = {a.min, b.min, c.min, a.max, b.max, c.max};
	return(result);
}
func_ R3 R3V(V3 a, V3 b, V3 c)
{
	R3 result = {a.x, b.x, c.x, a.y, b.y, c.y};
	return(result);
}



////////////////////////
//~ NOTE(nates): Vector2!

func_ V2
MV2(F32 x, F32 y)
{
	V2 Result = {x, y};
	return(Result);
}

func_ V2
MV2a(F32 S)
{
	V2 Result = {
		.x = S,
		.y = S,
	};
	
	return(Result);
}

func_ V2
MV2s(S32 X, S32 Y)
{
	V2 Result = MV2((F32)X, (F32)Y);
	return(Result);
}

func_ V2 
V2Neg(V2 A)
{
	V2 Result = {
		.x = -A.x,
		.y = -A.y,
	};
	return(Result);
}

func_ V2
V2Add(V2 A, V2 B)
{
	V2 Result;
	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	
	return(Result);
}

func_ V2
V2Sub(V2 A, V2 B)
{
	V2 Result;
	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	return(Result);
}

func_ V2
V2MS(V2 A, F32 B)
{
	V2 Result = {
		.x = A.x*B,
		.y = A.y*B,
	};
	return(Result);
}

func_ V2
V2DS(V2 A, F32 B)
{
	V2 Result = {
		.x = A.x/B,
		.y = A.y/B,
	};
	return(Result);
}

func_ F32
V2Dot(V2 A, V2 B)
{
	F32 Result = A.x*B.x + A.y*B.y;
	return(Result);
}

func_ V2
V2Had(V2 A, V2 B)
{
	V2 Result = {A.x*B.x, A.y*B.y};
	return(Result);
}

func_ F32
V2LenSq(V2 A)
{
	F32 Result = V2Dot(A, A);
	return(Result);
}

func_ F32
V2Len(V2 A)
{
	F32 Result = sqrt(V2Dot(A, A));
	return(Result);
}

func_ V2
V2Norm(V2 A)
{
	V2 Result = {0};
	if(V2LenSq(A) != 0.0f)
	{
		Result = V2DS(A, V2Len(A));
	}
	
	return(Result);
}

func_ V2
V2Perp(V2 A)
{
	V2 Result;
	Result.x = -A.y;
	Result.y = A.x;
	return(Result);
}

func_ V2
V2Lerp(V2 A, F32 t, V2 B)
{
	V2 Result = V2Add(V2MS(A, (1.0f - t)),
										V2MS(B, t));
	return(Result);
}

func_ V2
V2TriProd(V2 A2, V2 B2)
{
	V3 A = MV3xy(A2, 0.0f);
	V3 B = MV3xy(B2, 0.0f);
	V3 Cross = V3Cross(A, B);
	V2 Result = V3Cross(Cross, A).xy;
	return(Result);
}

/////////////////////////
// NOTE(nates): V2I

func_ V2I
MV2I(S32 x, S32 y)
{
	V2I result = {x, y};
	return(result);
}

func_ V2I
V2IAdd(V2I a, V2I b)
{
	V2I result = {
		a.x + b.x,
		a.y + b.y,
	};
	return(result);
}

func_ V2I
V2ISub(V2I a, V2I b)
{
	V2I result = {
		a.x - b.x,
		a.y - b.y,
	};
	return(result);
}

///////////////////////
// NOTE(nates): Vector3!

func_ V3
MV3(F32 x, F32 y, F32 z)
{
	V3 Result = {x, y, z};
	return(Result);
}

func_ V3
MV3a(F32 S)
{
	V3 Result = {S, S, S};
	return(Result);
}

func_ V3
MV3xy(V2 XY, F32 z)
{
	V3 Result;
	Result.x = XY.x;
	Result.y = XY.y;
	Result.z = z;
	
	return(Result);
}

func_ V3
MV3yz(F32 x, V2 YZ)
{
	V3 Result;
	Result.x = x;
	Result.y = YZ.x;
	Result.z = YZ.y;
	return(Result);
}

func_ V3 
V3Neg(V3 A)
{
	V3 Result = {
		.x = -A.x,
		.y = -A.y,
		.z = -A.z,
	};
	return(Result);
}

func_ V3
V3Add(V3 A, V3 B)
{
	V3 Result;
	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	Result.z = A.z + B.z;
	
	return(Result);
}

func_ V3
V3Sub(V3 A, V3 B)
{
	V3 Result;
	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	Result.z = A.z - B.z;
	
	return(Result);
}

func_ V3
V3MS(V3 A, F32 B)
{
	V3 Result = {
		.x = A.x*B,
		.y = A.y*B,
		.z = A.z*B,
	};
	
	return(Result);
}

func_ V3
V3DS(V3 A, F32 B)
{
	V3 Result = {
		.x = A.x/B,
		.y = A.y/B,
		.z = A.z/B,
	};
	return(Result);
}

func_ F32
V3Dot(V3 A, V3 B)
{
	F32 Result = A.x*B.x + A.y*B.y + A.z*B.z;
	return(Result);
}


func_ V3
V3Had(V3 A, V3 B)
{
	V3 Result = {A.x*B.x, A.y*B.y, A.z*B.z};
	return(Result);
}

func_ F32
V3Len(V3 A)
{
	F32 Result = Sqrt(V3Dot(A, A));
	return(Result);
}

func_ F32
V3LenSq(V3 A)
{
	F32 Result = V3Dot(A, A);
	return(Result);
}

func_ V3
V3Norm(V3 A)
{
	V3 Result = {0};
	if(V3LenSq(A) != 0.0f)
	{
		Result = V3DS(A, V3Len(A));
	}
	
	return(Result);
}

func_ V3
V3Cross(V3 A, V3 B)
{
	V3 Result;
	Result.x = A.y*B.z - A.z*B.y;
	Result.y = A.z*B.x - A.x*B.z;
	Result.z = A.x*B.y - A.y*B.x;
	return(Result);
}

func_ V3
V3Lerp(V3 A, F32 t, V3 B)
{
	V3 Result = V3Add(V3MS(A, (1.0f - t)),
										V3MS(B, t));
	return(Result);
}

func_ F32
PlaneIntersectT(V3 PlaneP, V3 PlaneNormal, V3 LineStart, V3 LineEnd)
{
	Assert(V3Len(PlaneNormal) <= 1.01f);
	F32 PlaneProjection = V3Dot(PlaneNormal, PlaneP);
	F32 StartProjection = V3Dot(LineStart, PlaneNormal);
	F32 EndProjection = V3Dot(LineEnd, PlaneNormal);
	F32 t = (PlaneProjection - StartProjection) / (EndProjection - StartProjection);
	return(t);
}

func_ V3
PlaneIntersection(V3 PlaneP, V3 PlaneNormal, V3 LineStart, V3 LineEnd)
{
	// NOTE(nates): Finds intersection point between line and a plane
	Assert(V3Len(PlaneNormal) <= 1.01f);
	F32 PlaneProjection = V3Dot(PlaneNormal, PlaneP);
	F32 StartProjection = V3Dot(LineStart, PlaneNormal);
	F32 EndProjection = V3Dot(LineEnd, PlaneNormal);
	F32 t = (PlaneProjection - StartProjection) / (EndProjection - StartProjection);
	V3 Result = V3Add(LineStart, V3MS(V3Sub(LineEnd, LineStart), t));
	return(Result);
}

func_ V3
V3AARot(V3 Point, V3 axis, F32 Angle)
{
	Angle = Angle*DegToRad;
	
	F32 Proj = V3Dot(Point, axis);
	V3 p = V3MS(axis, Proj);
	V3 e = V3Sub(Point, p);
	V3 f = V3Cross(axis, Point);
	V3 ep = V3Add(V3MS(e, Cos(Angle)), V3MS(f, Sin(Angle)));
	
	V3 Result = V3Add(p,ep);
	return(Result);
}

//////////////////////////////
// NOTE(nates): Vector 4!!

func_ V4
MV4(F32 x, F32 y, F32 z, F32 w)
{
	V4 Result = {x, y, z, w};
	return(Result);
}

func_ V4
MV4a(F32 S)
{
	V4 Result = 
	{
		.x = S, .y = S, .z = S, .w = S,
	};
	return(Result);
}

func_ V4
MV4xyz(V3 XYZ, F32 w)
{
	V4 Result;
	Result.x = XYZ.x;
	Result.y = XYZ.y;
	Result.z = XYZ.z;
	Result.w = w;
	
	return(Result);
}


func_ V4
V4Add(V4 A, V4 B)
{
	V4 Result;
	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	Result.z = A.z + B.z;
	Result.w = A.w + B.w;
	
	return(Result);
}

func_ V4
V4Sub(V4 A, V4 B)
{
	V4 Result;
	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	Result.z = A.z - B.z;
	Result.w = A.w - B.w;
	
	return(Result);
}

func_ V4
V4MS(V4 A, F32 B)
{
	V4 Result = {
		.x = A.x*B,
		.y = A.y*B,
		.z = A.z*B,
		.w = A.w*B,
	};
	return(Result);
}

func_ V4
V4DS(V4 A, F32 B)
{
	V4 Result = {
		.x = A.x/B,
		.y = A.y/B,
		.z = A.z/B,
		.w = A.w/B,
	};
	return(Result);
}

func_ F32
V4Dot(V4 A, V4 B)
{
	F32 Result = A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;
	return(Result);
}

func_ F32
V4Len(V4 A)
{
	F32 Result = Sqrt(V4Dot(A, A));
	return(Result);
}

func_ F32
V4LenSq(V4 A)
{
	F32 Result = V4Dot(A, A);
	return(Result);
}

func_ V4
V4UnpackColor(U32 color)
{
	F32 inV255 = 1.f / 255.f;
	V4 result = MV4((F32)((color >> 16) & 0xff),
									(F32)((color >> 8) & 0xff),
									(F32)((color & 0xff)),
									(F32)(color >> 24));
	result = V4MS(result, inV255);
	return(result);
}

func_ U32
V4PackColor(V4 color)
{
	U32 result = ((U32)(color.a*255.0f) << 24,
								(U32)(color.r*255.0f) << 16,
								(U32)(color.g*255.0f) << 8,
								(U32)(color.b*255.0f));
	return(result);
}


//////////////////////////////////
// NOTE(nates): M44


func_ M44
M44Mul(M44 A, M44 B)
{
	M44 Result = {0};
	
	for(U32 r = 0;
			r < 4;
			++r)
	{
		for(U32 c = 0;
				c < 4;
				++c)
		{
			for(U32 i = 0;
					i < 4;
					++i)
			{
				Result.e[r][c] += A.e[r][i]*B.e[i][c];
			}
		}
	}
	
	return(Result);
}

func_ M44
M44Transpose(M44 A)
{
	M44 Result;
	for(U32 r = 0;
			r < 4;
			++r)
	{
		for(U32 c = 0;
				c < 4;
				++c)
		{
			Result.e[r][c] = A.e[c][r];
		}
	}
	
	return(Result);
}

func_ M44
M44Perspective(F32 screen_width_in_meters, F32 screen_height_in_meters, 
							 F32 near_plane, F32 far_plane)
{
	// NOTE(nates): Aspect ratio is height / width
	
	F32 w = screen_width_in_meters;
	F32 h = screen_height_in_meters;
	F32 n = near_plane;
	F32 f = far_plane;
	F32 d = f/(f-n);
	
	M44 result = {
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

func_ M44
M44Orthographic(F32 screen_width_in_meters, F32 screen_height_in_meters, 
								F32 near_plane, F32 far_plane)
{
	// NOTE(nates): Aspect ratio is height / width
	
	F32 w = screen_width_in_meters;
	F32 h = screen_height_in_meters;
	F32 n = near_plane;
	F32 f = far_plane;
	F32 d = 1.f/(f-n);
	
	M44 result = {
		{ 
			{2*n/w, 0,     0,  0}, 
			{0,     2*n/h, 0,  0},
			{0,     0,     d, -n*d},
			{0,     0,     0,  1},
		},
	};
	
	return(result);
}

func_ M44
M44CameraTransform(V3 xaxis, V3 yaxis, V3 zaxis, V3 camerap)
{
	M44 result = M44Row3x3(xaxis, yaxis, zaxis);
	V3 translation = V3Neg(M44MulV3(result, camerap));
	result = M44AddTranslation(result, translation);
	return(result);
}

func_ V4
M44MulV4(M44 A, V4 B)
{
	V4 Result;
	Result.x = B.x*A.e[0][0] + B.y*A.e[0][1] + B.z*A.e[0][2] + B.w*A.e[0][3];
	Result.y = B.x*A.e[1][0] + B.y*A.e[1][1] + B.z*A.e[1][2] + B.w*A.e[1][3];
	Result.z = B.x*A.e[2][0] + B.y*A.e[2][1] + B.z*A.e[2][2] + B.w*A.e[2][3];
	Result.w = B.x*A.e[3][0] + B.y*A.e[3][1] + B.z*A.e[3][2] + B.w*A.e[3][3];
	
	return(Result);
}

func_ V3
M44MulV3(M44 A, V3 B)
{
	V4 HomogeneousCoord = MV4xyz(B, 1.0f);
	V3 Result = M44MulV4(A, HomogeneousCoord).xyz;
	return(Result);
}

func_ M44
M44Col3x3(V3 X, V3 Y, V3 Z)
{
	M44 Result = {
		{
			{X.x,  Y.x,  Z.x,  0.0f},
			{X.y,  Y.y,  Z.y,  0.0f},
			{X.z,  Y.z,  Z.z,  0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	return(Result);
}

func_ M44
M44Row3x3(V3 X, V3 Y, V3 Z)
{
	M44 Result = {
		{
			{X.x,  X.y,  X.z,  0.0f},
			{Y.x,  Y.y,  Y.z,  0.0f},
			{Z.x,  Z.y,  Z.z,  0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}


func_ V3  
M44Col3(M44 A, U32 ColIndex)
{
	V3 Result = {
		A.e[0][ColIndex],
		A.e[1][ColIndex],
		A.e[2][ColIndex],
	};
	
	return(Result);
}

func_ V3  
M44Row3(M44 A, U32 RowIndex)
{
	V3 Result = {
		A.e[RowIndex][0],
		A.e[RowIndex][1],
		A.e[RowIndex][2],
	};
	
	return(Result);
}

func_ M44
M44AddTranslation(M44 A, V3 T)
{
	M44 R = A;
	R.e[0][3] += T.x;
	R.e[1][3] += T.y;
	R.e[2][3] += T.z;
	return(R);
}

func_ M44 
M44Translation(V3 t)
{
	M44 result = {
		1, 0, 0, t.x,
		0, 1, 0, t.y,
		0, 0, 1, t.z,
		0, 0, 0, 1
	};
	return(result);
}


func_ M44 
M44Scale(V3 s)
{
	M44 result = {
		s.x, 0,   0,   0,
		0,   s.y, 0,   0,
		0,   0,   s.z, 0,
		0,   0,   0,   1,
	};
	return(result);
}

func_ M44
M44Identity(void)
{
	M44 Result = {
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ M44
M44XRotDeg(F32 Angle)
{
	Angle = Angle*DegToRad;
	
	F32 s = Sin(Angle);
	F32 c = Cos(Angle);
	
	M44 Result = {
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f,  c,   -s,   0.0f},
			{0.0f,  s,   c,    0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ M44
M44YRotDeg(F32 Angle)
{
	Angle = Angle*DegToRad;
	F32 s = Sin(Angle);
	F32 c = Cos(Angle);
	
	M44 Result = {
		{
			{c,    0.0f, s,    0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{-s,   0.0f, c,    0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ M44
M44ZRotDeg(F32 Angle)
{
	Angle = Angle*DegToRad;
	F32 s = Sin(Angle);
	F32 c = Cos(Angle);
	
	M44 Result = {
		{
			{c,    -s,   0.0f, 0.0f},
			{s,     c,   0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}


func_ M44
M44XRotRad(F32 Angle)
{
	F32 s = Sin(Angle);
	F32 c = Cos(Angle);
	
	M44 Result = {
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f,  c,   -s,   0.0f},
			{0.0f,  s,   c,    0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ M44
M44YRotRad(F32 Angle)
{
	F32 s = Sin(Angle);
	F32 c = Cos(Angle);
	
	M44 Result = {
		{
			{c,    0.0f, s,    0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{-s,   0.0f, c,    0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		},
	};
	
	return(Result);
}

func_ M44
M44ZRotRad(F32 Angle)
{
	F32 s = Sin(Angle);
	F32 c = Cos(Angle);
	
	M44 Result = {
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

func_ R2 R2MM(V2 min, V2 max)
{
	R2 result = {
		.min = min,
		.max = max,
	};
	return(result);
}

func_ R2 R2CR(V2 center, V2 radius)
{
	R2 result = {
		.min = V2sub(center, radius),
		.max = V2add(center, radius),
	};
	return(result);
}

func_ R2 R2CD(V2 center, V2 dim)
{
	R2 result = R2CR(center, V2MS(dim, .5f));
	return(result);
}

////////////////////////////////
// nates: rect S32 functions

func_ R2I R2IMM(V2I min, V2I max)
{
	R2I result = {
		.min = min,
		.max = max,
	};
	return(result);
}
