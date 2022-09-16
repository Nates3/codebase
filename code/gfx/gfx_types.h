/* date = September 12th 2022 10:30 pm */
#ifndef GFX_TYPES_H
#define GFX_TYPES_H

typedef u64 r_handle;
typedef enum r_buffer_kind
{
	R_Buffer_Kind_Null,
	R_Buffer_Kind_Vertex,
	R_Buffer_Kind_Index,
	R_Buffer_Kind_Constant,
} r_buffer_kind;

typedef enum r_shader_kind
{
	R_Shader_Kind_Null,
	R_Shader_Kind_Vertex,
	R_Shader_Kind_Fragment,
	R_Shader_Kind_Geometry,
} r_shader_kind;

typedef enum r_mode
{
	R_Mode_Null,
	R_Mode_PointList,
	R_Mode_LineList,
	R_Mode_TriangleList,
} r_mode;

#include "generated/layout_table.c"

typedef struct r_layout
{
	r_handle Handle;
	u32 Stride;
} r_layout;

typedef struct r_buffer
{
	r_handle Handle;
	u32 Size;
} r_buffer;

typedef r_handle r_shader;

typedef struct r_info
{
	r_handle VShader;
	r_handle FShader;
	r_layout Layout;
	r_handle TextureContext;
} r_info;

#endif //GFX_TYPES_H
