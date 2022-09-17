
func_ void
PushVertexV3(R_Group *render_group, V3 vertex)
{
	V3 *data = PushArray(render_group->varena, V3, 1);
	data[0] = vertex;
	render_group->vcount++;
}

func_ void
PushVertexV3C3(R_Group *render_group, V3 vertex, V3 color)
{
	V3 *data = PushArray(render_group->varena, V3, 2);
	data[0] = vertex;
	data[1] = color;
	render_group->vcount++;
}

func_ void
PushVertexV3T2(R_Group *render_group, V3 vertex, V2 tex_coord)
{
	V3 *v = PushArray(render_group->varena, V3, 1);
	*v = vertex;
	V2 *t = PushArray(render_group->varena, V2, 1);
	*t = tex_coord;
	render_group->vcount++;
}

func_ void
PushIndex(R_Group *render_group, U32 index)
{
	U32 *data = PushArray(render_group->iarena, U32, 1);
	*data = index;
	render_group->icount++;
}


func_ void
PushVTriangleV3(R_Group *render_group, V3 p0, V3 p1, V3 p2)
{
	PushVertexV3(render_group, p0);
	PushVertexV3(render_group, p1);
	PushVertexV3(render_group, p2);
}

func_ void 
PushVTriangleV3C3(R_Group *render_group, V3 p0, V3 p1, V3 p2, V3 color)
{
	PushVertexV3C3(render_group, p0, color);
	PushVertexV3C3(render_group, p1, color);
	PushVertexV3C3(render_group, p2, color);
}

func_ void PushVTriangleV3T2(R_Group *render_group, V3 p0, V3 p1, V3 p2, 
														 V2 t0, V2 t1, V2 t2)
{
	PushVertexV3T2(render_group, p0, t0);
	PushVertexV3T2(render_group, p1, t1);
	PushVertexV3T2(render_group, p2, t2);
}


func_ void
PushITriangleV3(R_Group *render_group, V3 p0, V3 p1, V3 p2)
{
	PushVertexV3(render_group, p0);
	PushVertexV3(render_group, p1);
	PushVertexV3(render_group, p2);
	
	PushIndex(render_group, render_group->icount);
	PushIndex(render_group, render_group->icount);
	PushIndex(render_group, render_group->icount);
}

func_ void 
PushITriangleV3C3(R_Group *render_group, V3 p0, V3 p1, V3 p2, V3 color)
{
	push_vertex_V3c3(render_group, p0, color);
	push_vertex_V3c3(render_group, p1, color);
	push_vertex_V3c3(render_group, p2, color);
	
	push_index(render_group, render_group->icount);
	push_index(render_group, render_group->icount);
	push_index(render_group, render_group->icount);
}

func_ void PushITriangleV3T2(R_Group *render_group, V3 p0, V3 p1, V3 p2, 
														 V2 t0, V2 t1, V2 t2)
{
	push_vertex_V3t2(render_group, p0, t0);
	push_vertex_V3t2(render_group, p1, t1);
	push_vertex_V3t2(render_group, p2, t2);
	
	push_index(render_group, render_group->icount);
	push_index(render_group, render_group->icount);
	push_index(render_group, render_group->icount);
}

#define PushUniformData(render_group, data) PushUniformData_(render_group, &data, sizeof(data))
func_ void
PushUniformData_(R_Group *render_group, 
								 void *data, U32 data_size)
{
	void *dest = PushArray(render_group->uarena, U8, data_size);
	MemoryCopy(dest, data, data_size);
}

func_ void InitRenderGroupBufferEntries(U64 vbuffer_size, U64 ibuffer_size, U64 ubuffer_size)
{
	for(U32 i = 0; i < MAX_RENDERGROUP_BUFFER_ENTRIES; ++i)
	{
		R_Buffer vbuffer = Gfx_MakeDynamicVBuffer(vbuffer_size);
		R_Buffer ibuffer = Gfx_MakeDynamicIBuffer(ibuffer_size);
		R_Buffer ubuffer = Gfx_MakeDynamicUBuffer(ubuffer_size);
		
		g_rgroup_vbuffer_entries[i].buffer = vbuffer;
		g_rgroup_vbuffer_entries[i].being_used = false;
		g_rgroup_ibuffer_entries[i].buffer = ibuffer;
		g_rgroup_ibuffer_entries[i].being_used = false;
		g_rgroup_ubuffer_entries[i].buffer = ubuffer;
		g_rgroup_ubuffer_entries[i].being_used = false;
	}
}

func_ void PushRenderInfo(R_Group *render_group, R_Info info)
{
	Assert(info.vshader != 0 && info.fshader != 0);
	Assert(info.layout.handle != 0 && info.layout.stride != 0);
	render_group->info = info;
}

func_ void PushVertexBuffer(R_Group *render_group)
{
	R_BufferEntry *entry = 0;
	for(U32 i = 0; i < MAX_RENDERGROUP_BUFFER_ENTRIES; ++i)
	{
		R_BufferEntry *current = g_rgroup_vbuffer_entries + i;
		if(current->being_used == false) {
			entry = current;
			Assert(entry->buffer.handle != 0);
			break;
		}
	}
	if(entry) {
		render_group->ventry = entry;
	}
	else {
		InvalidPath;
	}
	
	render_group->varena = ArenaAlloc(entry->buffer.size);
	render_group->varena->align = 1;
}

func_ void PushIndexBuffer(R_Group *render_group)
{
	R_BufferEntry *entry = 0;
	for(U32 i = 0; i < MAX_RENDERGROUP_BUFFER_ENTRIES; ++i)
	{
		R_BufferEntry *current = g_rgroup_ibuffer_entries + i;
		if(current->being_used == false) {
			entry = current;
			Assert(entry->buffer.handle != 0);
			break;
		}
	}
	
	if(entry) {
		render_group->ientry = entry;
	}
	else {
		InvalidPath;
	}
	render_group->index_drawing_enabled = true;
	
	render_group->iarena = ArenaAlloc(entry->buffer.size);
	render_group->iarena->align = 1;
}

func_ void PushUniformBuffer(R_Group *render_group)
{
	R_BufferEntry *entry = 0;
	for(U32 i = 0; i < MAX_RENDERGROUP_BUFFER_ENTRIES; ++i)
	{
		R_BufferEntry *current = g_rgroup_ubuffer_entries + i;
		if(current->being_used == false) {
			entry = current;
			Assert(entry->buffer.handle != 0);
			break;
		}
	}
	
	if(entry) {
		render_group->uentry = entry;
	}
	else {
		InvalidPath;
	}
	
	render_group->cbuffer_enabled = true;
	render_group->uarena = ArenaAlloc(entry->buffer.size);
	render_group->uarena->align = 1;
}


func_ void PushClipRect(R_Group *render_group, R2 rect)
{
	Assert(render_group->cliprect_enabled == false);
	render_group->cliprect_enabled = true;
	render_group->cliprect = rect;
}

func_ void
render_groupToOutput(R_Group *render_group, 
										 R_Handle viewport,
										 R_Handle texture)
{
	void *vmemory = ArenaStart(render_group->varena);
	U64 vmemory_size = ArenaSize(render_group->varena);
	Gfx_SetVertexBufferData(render_group->ventry->buffer, vmemory, vmemory_size);
	render_group->ventry->being_used = false;
	
	if(render_group->index_drawing_enabled) {
		void *imemory = ArenaStart(render_group->iarena);
		U64 imemory_size = ArenaSize(render_group->iarena);
		Gfx_SetIndexBufferData(render_group->ientry->buffer, imemory, imemory_size);
		render_group->ientry->being_used = false;
	}
	
	if(render_group->cbuffer_enabled) {
		void *umemory = ArenaStart(render_group->uarena);
		U64 umemory_size = ArenaSize(render_group->uarena);
		Gfx_SetUniformBufferData(render_group->uentry->buffer, umemory, umemory_size);
		render_group->uentry->being_used = false;
	}
	
	Gfx_BindViewport(viewport);
	Gfx_SetRenderTarget();
	
	Gfx_SetRenderMode(R_Mode_TriangleList);
	Gfx_BindInputLayout(render_group->info.layout);
	
	ID3D11DeviceContext1_ClearDepthStencilView(g_render_context, g_depth_buffer_view, D3D11_CLEAR_DEPTH, 1.f, 0);
	
	if(render_group->info.texture_context) {
		Assert(texture);
		Texture_Context *texture_context = (Texture_Context*)render_group->info.texture_context;
		
		if(render_group->wireframe_enabled) {
			ID3D11DeviceContext1_RSSetState(g_render_context, (ID3D11RasterizerState *)g_raster_state_wire);
		}
		else {
			ID3D11DeviceContext1_RSSetState(g_render_context, (ID3D11RasterizerState *)g_raster_state_fill);
		}
		
		D3D11_RECT full_rect = {0, 0, g_depth_buffer_desc.Width, g_depth_buffer_desc.Height};
		if(render_group->cliprect_enabled) {
			V2I min = MV2I((S32)render_group->cliprect.x0, (S32)render_group->cliprect.y0);
			V2I max = MV2I((S32)render_group->cliprect.x1, (S32)render_group->cliprect.y1);
			R2I rect = {
				.min = min,
				.max = max,
			};
			full_rect = (D3D11_RECT){rect.x0, rect.y0, rect.x1, rect.y1};
		}
		ID3D11DeviceContext1_RSSetScissorRects(g_render_context, 1, &full_rect);
		
		ID3D11DeviceContext1_PSSetShaderResources(g_render_context, 0, 1, (ID3D11ShaderResourceView **)&texture);
		ID3D11DeviceContext1_PSSetSamplers(g_render_context, 0, 1, &texture_context->sampler_state);
		
		ID3D11DeviceContext1_OMSetDepthStencilState(g_render_context, texture_context->depth_stencil_state, 0);
		ID3D11DeviceContext1_OMSetBlendState(g_render_context, texture_context->blend_state, 0, 0xffffffff);
	}
	else {
		Assert(texture == 0);
	}
	
	Gfx_BindVertexBuffer(render_group->ventry->buffer, render_group->info.layout.stride, 0);
	
	if(render_group->index_drawing_enabled) {
		Gfx_BindIndexBuffer(render_group->ientry->buffer);
	}
	
	if(render_group->cbuffer_enabled) {
		Gfx_BindUniformBuffer(render_group->uentry->buffer, R_Shader_Kind_Vertex);
	}
	
	Gfx_BindVertexShader(render_group->info.vshader);
	Gfx_BindFragmentShader(render_group->info.fshader);
	
	if(render_group->index_drawing_enabled) {
		Gfx_DrawIndices(render_group->icount);
	}
	else {
		Gfx_DrawVertices(render_group->vcount);
	}
	
	// TODO(nates): I do not like this because it does a VirtualFree
	// each frame on windows. Research if that is that performance costly.
	ArenaRelease(render_group->varena);
	if(render_group->index_drawing_enabled) {
		ArenaRelease(render_group->iarena);
	}
	if(render_group->cbuffer_enabled) {
		ArenaRelease(render_group->uarena);
	}
}
