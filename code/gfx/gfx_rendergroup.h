/* date = September 12th 2022 10:26 pm */
#ifndef GFX_RENDERGROUP_H
#define GFX_RENDERGROUP_H

typedef struct r_buffer_entry
{
	r_buffer Buffer;
	b32 BeingUsed;
} r_buffer_entry;

typedef struct render_group
{
	u32 VCount;
	u32 ICount;
	
	r_info Info;
	
	b8 IndexDrawingEnabled;
	b8 CBufferEnabled;
	b8 ClipRectEnabled;
	b8 WireFrameEnabled;
	
	arena *VArena;
	arena *IArena;
	arena *UArena;
	// TODO(nates): buffer sizes tells the state of the
	// render group which calls to make
	r_buffer_entry *VEntry;
	r_buffer_entry *IEntry;
	r_buffer_entry *UEntry;
	
	rng2 ClipRect;
}render_group;


// TODO(nates): Organize these funcctions
func_ void PushVertexV3(render_group *RenderGroup, v3 Vertex);
func_ void PushVertexV3C3(render_group *RenderGroup, v3 Vertex, v3 Color);
func_ void PushVertexV3T2(render_group *RenderGroup, v3 Vertex, v2 TexCoord);
func_ void PushIndex(render_group *RenderGroup, u32 Index);
func_ void PushVTriangleV3(render_group *RenderGroup, v3 p0, v3 p1, v3 p2);
func_ void PushVTriangleV3C3(render_group *RenderGroup, v3 p0, v3 p1, v3 p2, v3 Color);
func_ void PushVTriangleV3T2(render_group *RenderGroup, v3 p0, v3 p1, v3 p2, v2 t0, v2 t1, v2 t2);
func_ void PushITriangleV3(render_group *RenderGroup, v3 p0, v3 p1, v3 p2);
func_ void PushITriangleV3C3(render_group *RenderGroup, v3 p0, v3 p1, v3 p2, v3 Color);
func_ void PushITriangleV3T2(render_group *RenderGroup, v3 p0, v3 p1, v3 p2, v2 t0, v2 t1, v2 t2);
func_ void PushUniformData(render_group *RenderGroup, void *Data, u32 DataSize);

#define MAX_RENDERGROUP_BUFFER_ENTRIES 16
global_ r_buffer_entry GRenderGroupVBufferEntries[MAX_RENDERGROUP_BUFFER_ENTRIES] = {0};
global_ r_buffer_entry GRenderGroupIBufferEntries[MAX_RENDERGROUP_BUFFER_ENTRIES] = {0};
global_ r_buffer_entry GRenderGroupUBufferEntries[MAX_RENDERGROUP_BUFFER_ENTRIES] = {0};


// TODO(nates): Be able to resize the buffer entries
func_ void InitRenderGroupBufferEntries(u64 VBufferSize, u64 IBufferSize, u64 UBufferSize);
func_ void PushRenderInfo(render_group *RenderGroup, r_info Info);
func_ void PushVertexBuffer(render_group *RenderGroup);
func_ void PushIndexBuffer(render_group *RenderGroup);
func_ void PushUniformBuffer(render_group *RenderGroup);
func_ void PushClipRect(render_group *RenderGroup, rng2 Rect);
func_ void RenderGroupToOutput(render_group *RenderGroup, r_handle Viewport, r_handle Texture);


#endif //GFX_RENDERGROUP_H
