
typedef enum R_LayoutElement
{
 R_Layout_Element_Pos2,
R_Layout_Element_Pos3,
R_Layout_Element_Normal,
R_Layout_Element_TextureCoords,
R_Layout_Element_Color3,
R_Layout_Element_Color4,
} R_LayoutElement;

global_ char *g_layout_strings[] = 
{
 "POSTWO",
"POS",
"NOR",
"TEX",
"TCOLOR",
"QCOLOR",
};