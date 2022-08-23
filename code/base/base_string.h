/* date = August 18th 2022 4:04 pm */
#ifndef BASE_STRING_H
#define BASE_STRING_H

////////////////////////////////
//~ NOTE(nates): String8 types

typedef struct String8
{
  U8 *str;
  U64 size;
} String8;

typedef struct String8Node String8Node;
struct String8Node
{
  String8Node *next;
  String8 string;
};

typedef struct String8List
{
  String8Node *first;
  String8Node *last;
  U64 node_count;
  U64 total_size;
}String8List;

typedef struct StringJoin
{
  String8 pre;
  String8 mid;
  String8 post;
}StringJoin;

typedef U32 StringMatchFlags;
enum
{
  StringMatchFlag_NoCase = (1 << 0),
};

///////////////////////////////////////
//~ NOTE(nates): Unicode string type

typedef struct String16
{
  U16 *str;
  U64 size;
}String16;

typedef struct String32
{
  U32 *str;
  U64 size;
} String32;

typedef struct StringDecode
{
  U32 codepoint;
  U32 size;
} StringDecode;

///////////////////////////////////////////////////
//~ NOTE(nates): Character functions

func_ U8 U8Uppercase(U8 value);
func_ U8 U8Lowercase(U8 value);
func_ B32 CharIsSlash(U8 character);

////////////////////////////////////////////////////
//~ NOTE(nates): Immutable string8 helper functions

func_ String8 Str8(U8 *str, U64 size);
func_ String8 Str8Range(U8 *first, U8 *opl);
func_ String8 Str8CStr(U8 *cstr);
func_ char   *CStrStr8(Arena *arena, String8 string);
func_ String8 Str8PushCopy(Arena* arena, String8 string);

#define Str8Lit(s) Str8((U8 *)(s), sizeof(s) - 1)

func_ String8 Str8Prefix(String8 str, U64 size);
func_ String8 Str8Chop(String8 str, U64 amount);
func_ String8 Str8Postfix(String8 str, U64 size);
func_ String8 Str8Skip(String8 str, U64 amount);
func_ String8 Str8SubStr(String8 str, U64 first, U64 opl);

#define Str8Expand(s) (int)((s).size), ((s).str)

func_ String8 Str8ChopAtLastSlash(String8 str);

///////////////////////////////////////////////
//~ NOTE(nates): Immutable string16 helper functions

func_ String16 Str16(U16 *str, U64 size);
func_ String16 Str16CStr(U16 *str);

/////////////////////////////////////////////////
//~ NOTE(nates): String helper functions

func_ B32 Str8Match(String8 a, String8 b, StringMatchFlags flags);

/////////////////////////////////////////
//~ NOTE(nates): String list functions

func_ void Str8ListPushExplicit(String8List *list, String8 string, String8Node *node);
func_ void Str8ListPush(Arena *arena, String8List *list, String8 string);
func_ String8 Str8ListJoin(Arena *arena, String8List *list, StringJoin *optional_join);
func_ String8List Str8ListSplit(Arena *arena, String8 string, U8 *splits, U32 count);

/////////////////////////////////////
//~ NOTE(nates): Format strings

func_ String8 Str8PushFV(Arena *arena, char *fmt, va_list args);
func_ String8 Str8PushF(Arena *arena, char *fmt, ...);
func_ void Str8ListPushF(Arena *arena, String8List *list, char *fmt, ...);

/////////////////////////////////////////
//~ NOTE(nates): Unicode Helpers

func_ StringDecode StrDecodeUtf8(U8 *str, U64 cap);
func_ U32 StrEncodeUtf8(U8 *dst, U32 codepoint);
func_ StringDecode StrDecodeUtf16(U16 *str, U32 cap);
func_ U32 StrEncodeUtf16(U16 *dst, U32 codepoint);

func_ String32 Str32FromStr8(Arena *arena, String8 string);
func_ String8 Str8FromStr32(Arena *arena, String32 string);
func_ String16 Str16FromStr8(Arena *arena, String8 string);
func_ String8 Str8FromStr16(Arena *arena, String16 string);


#endif //BASE_STRING_H
