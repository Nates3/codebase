/* date = September 12th 2022 10:30 pm */
#ifndef GFX_TYPES_H
#define GFX_TYPES_H

typedef U64 R_Handle;
typedef enum R_Buffer_kind
{
	R_Buffer_Kind_Null,
	R_Buffer_Kind_Vertex,
	R_Buffer_Kind_Index,
	R_Buffer_Kind_Constant,
} R_Buffer_kind;

typedef enum R_Shader_kind
{
	R_Shader_Kind_Null,
	R_Shader_Kind_Vertex,
	R_Shader_Kind_Fragment,
	R_Shader_Kind_Geometry,
} R_Shader_kind;

typedef enum R_Mode
{
	R_Mode_Null,
	R_Mode_PointList,
	R_Mode_LineList,
	R_Mode_TriangleList,
} R_Mode;

#include "generated/layout_table.c"

typedef struct R_Layout
{
	R_Handle handle;
	U32 stride;
} R_Layout;

typedef struct R_Buffer
{
	R_Handle handle;
	U32 size;
} R_Buffer;

typedef R_Handle R_Shader;

typedef struct R_Info
{
	R_Handle vshader;
	R_Handle fshader;
	R_Layout layout;
	R_Handle texture_context;
} R_Info;

#endif //GFX_TYPES_H
