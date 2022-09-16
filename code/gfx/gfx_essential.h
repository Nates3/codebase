/* date = September 15th 2022 3:41 pm */
#ifndef GFX_ESSENTIAL_H
#define GFX_ESSENTIAL_H

func_ void Gfx_Startup(os_handle Window);
func_ void Gfx_ResizeRenderTarget(u32 NewWidth, u32 NewHeight);

func_ r_buffer Gfx_MakeDynamicVBuffer(u64 BufferSize);
func_ r_buffer Gfx_MakeDynamicIBuffer(u64 BufferSize);
func_ r_buffer Gfx_MakeDynamicUBuffer(u64 BufferSize);

func_ void Gfx_SetVertexBufferData(r_buffer vbuffer, void *memory, u64 memory_size);
func_ void Gfx_SetIndexBufferData(r_buffer ibuffer, void *memory, u64 memory_size);
func_ void Gfx_SetUniformBufferData(r_buffer ubuffer, void *memory, u64 memory_size);

func_ r_shader Gfx_MakeVertexShader(string8 filename);
func_ r_shader Gfx_MakeFragmentShader(string8 filename);
func_ r_shader Gfx_MakeGeometryShader(string8 filename);

#define Gfx_MakeInputLayout(vertex_shader, elements) Gfx_MakeInputLayout_(vertex_shader, elements, ArrayCount(elements));
func_ r_layout Gfx_MakeInputLayout_(r_handle vertex_shader, r_layout_element *elements, u32 element_count);

func_ r_handle Gfx_MakeFullViewport(void);
func_ r_handle Gfx_MakeViewport(rng2 rect);

func_ r_handle Gfx_MakeTexture(void *data, u32 width, u32 height);
func_ r_handle Gfx_MakeTextureContext(b32 blending);

// nates: these functions should be called in the order top down
func_ void Gfx_BindViewport(r_handle viewport);
func_ void Gfx_SetRenderTarget(void);

func_ void Gfx_BindInputLayout(r_layout layout);

func_ void Gfx_BindVertexBuffer(r_buffer vbuffer, u32 stride, u32 offset);
func_ void Gfx_BindIndexBuffer(r_buffer ibuffer);
func_ void Gfx_BindUniformBuffer(r_buffer ubuffer, r_shader_kind kind);

func_ void Gfx_BindInputLayout(r_layout layout);

func_ void Gfx_BindVertexShader(r_shader vertex_shader);
func_ void Gfx_BindFragmentShader(r_shader pixel_shader);

func_ void Gfx_FillRenderTarget(v4 background_color);
func_ void Gfx_ClearDepthBuffer(void);
func_ void Gfx_SetRenderMode(r_mode mode);
func_ void Gfx_DrawIndices(u32 index_array_count);
func_ void Gfx_DrawVertices(u32 vertex_array_count);
func_ void Gfx_SwapBuffers(void);



#endif //GFX_ESSENTIAL_H
