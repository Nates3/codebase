/* date = September 12th 2022 10:26 pm */
#ifndef GFX_RENDERGROUP_H
#define GFX_RENDERGROUP_H

typedef struct R_BufferEntry
{
	R_Buffer buffer;
	B32 being_used;
} R_BufferEntry;

typedef struct R_Group
{
	U32 vcount;
	U32 icount;
	
	R_Info info;
	
	B8 index_drawing_enabled;
	B8 cbuffer_enabled;
	B8 cliprect_enabled;
	B8 wireframe_enabled;
	
	Arena *varena;
	Arena *iarena;
	Arena *uarena;
	// TODO(nates): buffer sizes tells the state of the
	// render group which calls to make
	R_BufferEntry *ventry;
	R_BufferEntry *ientry;
	R_BufferEntry *uentry;
	
	R2 cliprect;
} R_Group;


// TODO(nates): Organize these funcctions
func_ void PushVertexV3(R_Group *render_group, V3 vertex);
func_ void PushVertexV3C3(R_Group *render_group, V3 vertex, V3 color);
func_ void PushVertexV3T2(R_Group *render_group, V3 vertex, V2 tex_coord);
func_ void PushIndex(R_Group *render_group, U32 index);
func_ void PushVTriangleV3(R_Group *render_group, V3 v0, V3 v1, V3 v2);
func_ void PushVTriangleV3C3(R_Group *render_group, V3 v0, V3 v1, V3 v2, V3 color);
func_ void PushVTriangleV3T2(R_Group *render_group, V3 v0, V3 v1, V3 v2, V2 t0, V2 t1, V2 t2);
func_ void PushITriangleV3(R_Group *render_group, V3 v, V3 v1, V3 v2);
func_ void PushITriangleV3C3(R_Group *render_group, V3 v0, V3 v1, V3 v2, V3 color);
func_ void PushITriangleV3T2(R_Group *render_group, V3 v0, V3 v1, V3 v2, V2 t0, V2 t1, V2 t2);
func_ void PushUniformData(R_Group *render_group, void *Data, U32 DataSize);

#define MAX_RENDERGROUP_BUFFER_ENTRIES 16
global_ R_BufferEntry g_rgroup_vbuffer_entries[MAX_RENDERGROUP_BUFFER_ENTRIES] = {0};
global_ R_BufferEntry g_rgroup_ibuffer_entries[MAX_RENDERGROUP_BUFFER_ENTRIES] = {0};
global_ R_BufferEntry g_rgroup_ubuffer_entries[MAX_RENDERGROUP_BUFFER_ENTRIES] = {0};


// TODO(nates): Be able to resize the buffer entries
func_ void InitRenderGroupBufferEntries(U64 vbuffer_size, U64 ibuffer_size, U64 ubuffer_size);
func_ void PushRenderInfo(R_Group *render_group, R_Info info);
func_ void PushVertexBuffer(R_Group *render_group);
func_ void PushIndexBuffer(R_Group *render_group);
func_ void PushUniformBuffer(R_Group *render_group);
func_ void PushClipRect(R_Group *render_group, R2 rect);
func_ void RenderGroupToOutput(R_Group *render_group, R_Handle Viewport, R_Handle Texture);


#endif //GFX_RENDERGROUP_H
