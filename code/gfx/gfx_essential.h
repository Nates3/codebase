/* date = September 15th 2022 3:41 pm */
#ifndef GFX_ESSENTIAL_H
#define GFX_ESSENTIAL_H

func_ void Gfx_Startup(OS_Handle window);
func_ void Gfx_ResizeRenderTarget(U32 new_width, U32 new_height);

func_ R_Buffer Gfx_MakeDynamicVBuffer(U64 buffer_size);
func_ R_Buffer Gfx_MakeDynamicIBuffer(U64 buffer_size);
func_ R_Buffer Gfx_MakeDynamicUBuffer(U64 buffer_size);

func_ void Gfx_SetVertexBufferData(R_Buffer vbuffer, void *memory, U64 memory_size);
func_ void Gfx_SetIndexBufferData(R_Buffer ibuffer, void *memory, U64 memory_size);
func_ void Gfx_SetUniformBufferData(R_Buffer ubuffer, void *memory, U64 memory_size);

func_ R_Shader Gfx_MakeVertexShader(Str8 filename);
func_ R_Shader Gfx_MakeFragmentShader(Str8 filename);
func_ R_Shader Gfx_MakeGeometryShader(Str8 filename);

#define Gfx_MakeInputLayout(vertex_shader, elements) Gfx_MakeInputLayout_(vertex_shader, elements, ArrayCount(elements));
func_ R_Layout Gfx_MakeInputLayout_(R_Handle vertex_shader, R_LayoutElement *elements, U32 element_count);

func_ R_Handle Gfx_MakeFullViewport(void);
func_ R_Handle Gfx_MakeViewport(R2 rect);

func_ R_Handle Gfx_MakeTexture(void *data, U32 width, U32 height);
func_ R_Handle Gfx_MakeTextureContext(B32 blending);

// nates: these functions should be called in the order top down
func_ void Gfx_BindViewport(R_Handle viewport);
func_ void Gfx_SetRenderTarget(void);

func_ void Gfx_BindInputLayout(R_Layout layout);

func_ void Gfx_BindVertexBuffer(R_Buffer vbuffer, U32 stride, U32 offset);
func_ void Gfx_BindIndexBuffer(R_Buffer ibuffer);
func_ void Gfx_BindUniformBuffer(R_Buffer ubuffer, R_Shader_kind kind);

func_ void Gfx_BindInputLayout(R_Layout layout);

func_ void Gfx_BindVertexShader(R_Shader vertex_shader);
func_ void Gfx_BindFragmentShader(R_Shader pixel_shader);

func_ void Gfx_FillRenderTarget(V4 background_color);
func_ void Gfx_ClearDepthBuffer(void);
func_ void Gfx_SetRenderMode(R_Mode mode);
func_ void Gfx_DrawIndices(U32 index_array_count);
func_ void Gfx_DrawVertices(U32 vertex_array_count);
func_ void Gfx_SwapBuffers(void);



#endif //GFX_ESSENTIAL_H
