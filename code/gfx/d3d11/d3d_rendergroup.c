
func_ void
PushVertexV3(render_group *RenderGroup, v3 vertex)
{
	v3 *data = PushArray(RenderGroup->VArena, v3, 1);
	data[0] = vertex;
	RenderGroup->VCount++;
}

func_ void
PushVertexV3C3(render_group *RenderGroup, v3 vertex, v3 color)
{
	v3 *data = PushArray(RenderGroup->VArena, v3, 2);
	data[0] = vertex;
	data[1] = color;
	RenderGroup->VCount++;
}

func_ void
PushVertexV3T2(render_group *RenderGroup, v3 vertex, v2 tex_coord)
{
	v3 *v = PushArray(RenderGroup->VArena, v3, 1);
	*v = vertex;
	v2 *t = PushArray(RenderGroup->VArena, v2, 1);
	*t = tex_coord;
	RenderGroup->VCount++;
}

func_ void
PushIndex(render_group *RenderGroup, u32 index)
{
	u32 *data = PushArray(RenderGroup->IArena, u32, 1);
	*data = index;
	RenderGroup->ICount++;
}


func_ void
PushVTriangleV3(render_group *RenderGroup, v3 p0, v3 p1, v3 p2)
{
	PushVertexV3(RenderGroup, p0);
	PushVertexV3(RenderGroup, p1);
	PushVertexV3(RenderGroup, p2);
}

func_ void 
PushVTriangleV3C3(render_group *RenderGroup, v3 p0, v3 p1, v3 p2, v3 color)
{
	PushVertexV3C3(RenderGroup, p0, color);
	PushVertexV3C3(RenderGroup, p1, color);
	PushVertexV3C3(RenderGroup, p2, color);
}

func_ void PushVTriangleV3T2(render_group *RenderGroup, v3 p0, v3 p1, v3 p2, 
														 v2 t0, v2 t1, v2 t2)
{
	PushVertexV3T2(RenderGroup, p0, t0);
	PushVertexV3T2(RenderGroup, p1, t1);
	PushVertexV3T2(RenderGroup, p2, t2);
}


func_ void
PushITriangleV3(render_group *RenderGroup, v3 p0, v3 p1, v3 p2)
{
	PushVertexV3(RenderGroup, p0);
	PushVertexV3(RenderGroup, p1);
	PushVertexV3(RenderGroup, p2);
	
	PushIndex(RenderGroup, RenderGroup->ICount);
	PushIndex(RenderGroup, RenderGroup->ICount);
	PushIndex(RenderGroup, RenderGroup->ICount);
}

func_ void 
PushITriangleV3C3(render_group *RenderGroup, v3 p0, v3 p1, v3 p2, v3 color)
{
	push_vertex_v3c3(RenderGroup, p0, color);
	push_vertex_v3c3(RenderGroup, p1, color);
	push_vertex_v3c3(RenderGroup, p2, color);
	
	push_index(RenderGroup, RenderGroup->ICount);
	push_index(RenderGroup, RenderGroup->ICount);
	push_index(RenderGroup, RenderGroup->ICount);
}

func_ void PushITriangleV3T2(render_group *RenderGroup, v3 p0, v3 p1, v3 p2, 
														 v2 t0, v2 t1, v2 t2)
{
	push_vertex_v3t2(RenderGroup, p0, t0);
	push_vertex_v3t2(RenderGroup, p1, t1);
	push_vertex_v3t2(RenderGroup, p2, t2);
	
	push_index(RenderGroup, RenderGroup->ICount);
	push_index(RenderGroup, RenderGroup->ICount);
	push_index(RenderGroup, RenderGroup->ICount);
}

#define PushUniformData(RenderGroup, data) PushUniformData_(RenderGroup, &data, sizeof(data))
func_ void
PushUniformData_(render_group *RenderGroup, 
								 void *data, u32 data_size)
{
	void *dest = PushArray(RenderGroup->UArena, u8, data_size);
	MemoryCopy(dest, data, data_size);
}

func_ void InitRenderGroupBufferEntries(u64 vbuffer_size, u64 ibuffer_size, u64 ubuffer_size)
{
	for(u32 i = 0; i < MAX_RENDERGROUP_BUFFER_ENTRIES; ++i)
	{
		r_buffer vbuffer = Gfx_MakeDynamicVBuffer(vbuffer_size);
		r_buffer ibuffer = Gfx_MakeDynamicIBuffer(ibuffer_size);
		r_buffer ubuffer = Gfx_MakeDynamicUBuffer(ubuffer_size);
		
		GRenderGroupVBufferEntries[i].Buffer = vbuffer;
		GRenderGroupVBufferEntries[i].BeingUsed = false;
		GRenderGroupIBufferEntries[i].Buffer = ibuffer;
		GRenderGroupIBufferEntries[i].BeingUsed = false;
		GRenderGroupUBufferEntries[i].Buffer = ubuffer;
		GRenderGroupIBufferEntries[i].BeingUsed = false;
	}
}

func_ void PushRenderInfo(render_group *RenderGroup, r_info info)
{
	Assert(info.VShader != 0 && info.FShader != 0);
	Assert(info.Layout.Handle != 0 && info.Layout.Stride != 0);
	RenderGroup->Info = info;
}

func_ void PushVertexBuffer(render_group *RenderGroup)
{
	r_buffer_entry *entry = 0;
	for(u32 i = 0; i < MAX_RENDERGROUP_BUFFER_ENTRIES; ++i)
	{
		r_buffer_entry *current = GRenderGroupVBufferEntries + i;
		if(current->BeingUsed == false) {
			entry = current;
			Assert(entry->Buffer.Handle != 0);
			break;
		}
	}
	if(entry) {
		RenderGroup->VEntry = entry;
	}
	else {
		InvalidPath;
	}
	
	RenderGroup->VArena = ArenaAlloc(entry->Buffer.Size);
	RenderGroup->VArena->Align = 1;
}

func_ void PushIndexBuffer(render_group *RenderGroup)
{
	r_buffer_entry *entry = 0;
	for(u32 i = 0; i < MAX_RENDERGROUP_BUFFER_ENTRIES; ++i)
	{
		r_buffer_entry *current = GRenderGroupIBufferEntries + i;
		if(current->BeingUsed == false) {
			entry = current;
			Assert(entry->Buffer.Handle != 0);
			break;
		}
	}
	
	if(entry) {
		RenderGroup->IEntry = entry;
	}
	else {
		InvalidPath;
	}
	RenderGroup->IndexDrawingEnabled = true;
	
	RenderGroup->IArena = ArenaAlloc(entry->Buffer.Size);
	RenderGroup->IArena->Align = 1;
}

func_ void PushUniformBuffer(render_group *RenderGroup)
{
	r_buffer_entry *entry = 0;
	for(u32 i = 0; i < MAX_RENDERGROUP_BUFFER_ENTRIES; ++i)
	{
		r_buffer_entry *current = GRenderGroupUBufferEntries + i;
		if(current->BeingUsed == false) {
			entry = current;
			Assert(entry->Buffer.Handle != 0);
			break;
		}
	}
	
	if(entry) {
		RenderGroup->UEntry = entry;
	}
	else {
		InvalidPath;
	}
	
	RenderGroup->CBufferEnabled = true;
	RenderGroup->UArena = ArenaAlloc(entry->Buffer.Size);
	RenderGroup->UArena->Align = 1;
}


func_ void PushClipRect(render_group *RenderGroup, rng2 rect)
{
	Assert(RenderGroup->ClipRectEnabled == false);
	RenderGroup->ClipRectEnabled = true;
	RenderGroup->ClipRect = rect;
}

func_ void
RenderGroupToOutput(render_group *RenderGroup, 
										r_handle viewport,
										r_handle texture)
{
	void *vmemory = ArenaStart(RenderGroup->VArena);
	u64 vmemory_size = ArenaSize(RenderGroup->VArena);
	Gfx_SetVertexBufferData(RenderGroup->VEntry->Buffer, vmemory, vmemory_size);
	RenderGroup->VEntry->BeingUsed = false;
	
	if(RenderGroup->IndexDrawingEnabled) {
		void *imemory = ArenaStart(RenderGroup->IArena);
		u64 imemory_size = ArenaSize(RenderGroup->IArena);
		Gfx_SetIndexBufferData(RenderGroup->IEntry->Buffer, imemory, imemory_size);
		RenderGroup->IEntry->BeingUsed = false;
	}
	
	if(RenderGroup->CBufferEnabled) {
		void *umemory = ArenaStart(RenderGroup->UArena);
		u64 umemory_size = ArenaSize(RenderGroup->UArena);
		Gfx_SetUniformBufferData(RenderGroup->UEntry->Buffer, umemory, umemory_size);
		RenderGroup->UEntry->BeingUsed = false;
	}
	
	Gfx_BindViewport(viewport);
	Gfx_SetRenderTarget();
	
	Gfx_SetRenderMode(R_Mode_TriangleList);
	Gfx_BindInputLayout(RenderGroup->Info.Layout);
	
	ID3D11DeviceContext1_ClearDepthStencilView(GRenderContext, GDepthBufferView, D3D11_CLEAR_DEPTH, 1.f, 0);
	
	if(RenderGroup->Info.TextureContext) {
		Assert(texture);
		texture_context *TextureContext = (texture_context*)RenderGroup->Info.TextureContext;
		
		if(RenderGroup->WireFrameEnabled) {
			ID3D11DeviceContext1_RSSetState(GRenderContext, (ID3D11RasterizerState *)GRasterizerStateWire);
		}
		else {
			ID3D11DeviceContext1_RSSetState(GRenderContext, (ID3D11RasterizerState *)GRasterizerStateFill);
		}
		
		D3D11_RECT full_rect = {0, 0, GDepthBufferDesc.Width, GDepthBufferDesc.Height};
		if(RenderGroup->ClipRectEnabled) {
			v2i Min = V2I((s32)RenderGroup->ClipRect.x0, (s32)RenderGroup->ClipRect.y0);
			v2i Max = V2I((s32)RenderGroup->ClipRect.x1, (s32)RenderGroup->ClipRect.y1);
			rng2i rect = {
				.Min = Min,
				.Max = Max,
			};
			full_rect = (D3D11_RECT){rect.x0, rect.y0, rect.x1, rect.y1};
		}
		ID3D11DeviceContext1_RSSetScissorRects(GRenderContext, 1, &full_rect);
		
		ID3D11DeviceContext1_PSSetShaderResources(GRenderContext, 0, 1, (ID3D11ShaderResourceView **)&texture);
		ID3D11DeviceContext1_PSSetSamplers(GRenderContext, 0, 1, &TextureContext->SamplerState);
		
		ID3D11DeviceContext1_OMSetDepthStencilState(GRenderContext, TextureContext->DepthStencilState, 0);
		ID3D11DeviceContext1_OMSetBlendState(GRenderContext, TextureContext->BlendState, 0, 0xffffffff);
	}
	else {
		Assert(texture == 0);
	}
	
	Gfx_BindVertexBuffer(RenderGroup->VEntry->Buffer, RenderGroup->Info.Layout.Stride, 0);
	
	if(RenderGroup->IndexDrawingEnabled) {
		Gfx_BindIndexBuffer(RenderGroup->IEntry->Buffer);
	}
	
	if(RenderGroup->CBufferEnabled) {
		Gfx_BindUniformBuffer(RenderGroup->UEntry->Buffer, R_Shader_Kind_Vertex);
	}
	
	Gfx_BindVertexShader(RenderGroup->Info.VShader);
	Gfx_BindFragmentShader(RenderGroup->Info.FShader);
	
	if(RenderGroup->IndexDrawingEnabled) {
		Gfx_DrawIndices(RenderGroup->ICount);
	}
	else {
		Gfx_DrawVertices(RenderGroup->VCount);
	}
	
	// TODO(nates): I do not like this because it does a VirtualFree
	// each frame on windows. Research if that is that performance costly.
	ArenaRelease(RenderGroup->VArena);
	if(RenderGroup->IndexDrawingEnabled) {
		ArenaRelease(RenderGroup->IArena);
	}
	if(RenderGroup->CBufferEnabled) {
		ArenaRelease(RenderGroup->UArena);
	}
}
