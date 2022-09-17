/* date = August 18th 2022 4:04 pm */
#ifndef BASE_STRING_H
#define BASE_STRING_H

////////////////////////////////
//~ NOTE(nates): String8 types

typedef struct Str8
{
  U8 *m;
  U64 size;
} Str8;

typedef struct Str8Node Str8Node;
struct Str8Node
{
	Str8Node *next;
	Str8 str;
};

typedef struct Str8List
{
	Str8Node *first;
	Str8Node*last;
	U64 count;
	U64 total_size;
}Str8List;

typedef U32 StrMatchFlags;
enum
{
	StringMatchFlag_NoCase = (1 << 0),
};

///////////////////////////////////////
//~ NOTE(nates): Unicode string type

typedef struct Str16
{
	U16 *m;
	U64 size;
} Str16;

typedef struct Str32
{
	U32 *m;
	U64 size;
} Str32;

typedef struct StrDecode
{
	U32 codepoint;
	U32 size;
} StrDecode;

///////////////////////////////////////////////////
//~ NOTE(nates): Character functions

func_ U8 U8Uppercase(U8 value);
func_ U8 U8Lowercase(U8 value);
func_ B32 U8IsSlash(U8 character);

////////////////////////////////////////////////////
//~ NOTE(nates): Immutable string8 helper functions

func_ Str8 MStr8(U8 *str, U64 size);
func_ Str8 Str8Rng(U8 *first, U8 *opl);
func_ Str8 Str8FromCstr(U8 *cstr);
func_ char*CstrFromStr8(Arena *arena, Str8 str);
func_ Str8 Str8Copy(Arena *arena, Str8 str);

///////////////////////////////////////////////
//~ NOTE(nates): Immutable s_s16 helper functions

func_ Str16 MStr16(U16 *str, U64 size);
func_ Str16 Str16FromCstr(U16 *str);

////////////////////////////////////////////////
//~ NOTE(nates): String8 manipulation functions

#define Str8Lit(s) MStr8((U8 *)(s), sizeof(s) - 1)

func_ Str8 Str8Prefix(Str8 str, U64 size);
func_ Str8 Str8Chop(Str8 str, U64 amount);
func_ Str8 Str8Postfix(Str8 str, U64 size);
func_ Str8 Str8Skip(Str8 str, U64 amount);
func_ Str8 Str8Substr(Str8 str, U64 first, U64 opl);
func_ Str8 Str8Subsize(Str8 str, U64 first, U64 size);

#define Str8Expand(s) (int)((s).size), ((s).m)

func_ Str8 Str8ChopAtLastSlash(Str8 str);

func_ S32 S32FromStr8(Str8 str);
func_ S64 S64FromStr8(Str8 str);
func_ U32 U32FromStr8(Str8 str);
func_ U64 U64FromStr8(Str8 str);

func_ Str8 Str8FromU64(Arena *arena, U64 num);
func_ Str8 Str8FromS64(Arena *arena, S64 num);

/////////////////////////////////////////////////
//~ NOTE(nates): String helper functions

func_ B32 Str8Match(Str8 a, Str8 b, StrMatchFlags flags);
func_ Str8 Str8FindFirst(Str8 haystack, Str8 needle, StrMatchFlags flags);

// NOTE(nates): Hashing

func_ U64 Str8Hash(Str8 str);

/////////////////////////////////////////
//~ NOTE(nates): String list functions

func_ void Str8ListPushExplicit(Str8List *List, Str8 str, Str8Node *node);
func_ void Str8ListPush(Arena *arena, Str8List *list, Str8 str);
func_ Str8 Str8ListJoin(Arena *arena, Str8List *list);
func_ Str8List Str8ListSplit(Arena *arena, Str8 string, U8 *splits, U32 count);

/////////////////////////////////////
//~ NOTE(nates): Format s_ss

func_ Str8 Str8PushFV(Arena *arena, char *fmt, va_list args);
func_ Str8 Str8PushF(Arena *arena, char *fmt, ...);
func_ void Str8ListPushF(Arena *arena, Str8List *list, char *fmt, ...);

/////////////////////////////////////////
//~ NOTE(nates): Unicode Helpers

func_ StrDecode DecodeUtf8(U8 *str, U64 cap);
func_ U32 EncodeUtf8(U8 *dst, U32 codepoint);
func_ StrDecode DecodeUtf16(U16 *str, U32 cap);
func_ U32 EncodeUtf16(U16 *dst, U32 codepoint);

func_ Str32 Str32FromStr8(Arena *arena, Str8 str);
func_ Str8 Str8FromStr32(Arena *arena, Str32 str);
func_ Str16 Str16FromStr8(Arena *arena, Str8 str);
func_ Str8 Str8FromStr16(Arena *arena, Str16 str);


#endif //BASE_STRING_H
