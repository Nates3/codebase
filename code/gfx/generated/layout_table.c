
typedef enum r_layout_element
{
 R_Layout_Element_Pos2,
R_Layout_Element_Pos3,
R_Layout_Element_Normal,
R_Layout_Element_TextureCoords,
R_Layout_Element_Color3,
R_Layout_Element_Color4,
} r_layout_element;

global_ char *GLayoutStrings[] = 
{
 "POSTWO",
"POS",
"NOR",
"TEX",
"TCOLOR",
"QCOLOR",
};