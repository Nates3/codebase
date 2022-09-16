/* date = August 18th 2022 4:04 pm */
#ifndef BASE_STRING_H
#define BASE_STRING_H

////////////////////////////////
//~ NOTE(nates): String8 types

typedef struct string8
{
  u8 *M;
  u64 Size;
} string8;

typedef struct string8_node string8_node;
struct string8_node
{
	string8_node *Next;
	string8 String;
};

typedef struct string8_list
{
	string8_node *First;
	string8_node *Last;
	u64 Count;
	u64 TotalSize;
}string8_list;

typedef u32 string_match_flags;
enum
{
	StringMatchFlag_NoCase = (1 << 0),
};

///////////////////////////////////////
//~ NOTE(nates): Unicode string type

typedef struct string16
{
	u16 *M;
	u64 Size;
}string16;

typedef struct string32
{
	u32 *M;
	u64 Size;
} string32;

typedef struct string_decode
{
	u32 Codepoint;
	u32 Size;
} string_decode;

///////////////////////////////////////////////////
//~ NOTE(nates): Character functions

func_ u8 U8Uppercase(u8 value);
func_ u8 U8Lowercase(u8 value);
func_ b32 CharIsSlash(u8 character);

////////////////////////////////////////////////////
//~ NOTE(nates): Immutable string8 helper functions

func_ string8 Str8(u8 *str, u64 size);
func_ string8 Str8Rng(u8 *first, u8 *opl);
func_ string8 Str8Cstr(u8 *cstr);
func_ char   *CstrStr8(arena *Arena, string8 String);
func_ string8 CopyStr8(arena *Arena, string8 String);

///////////////////////////////////////////////
//~ NOTE(nates): Immutable string16 helper functions

func_ string16 Str16(u16 *Str, u64 Size);
func_ string16 Str16Cstr(u16 *Str);

////////////////////////////////////////////////
//~ NOTE(nates): String8 manipulation functions

#define Str8Lit(s) Str8((u8 *)(s), sizeof(s) - 1)

func_ string8 PrefixStr8(string8 Str, u64 Size);
func_ string8 ChopStr8(string8 Str, u64 Amount);
func_ string8 PostfixStr8(string8 Str, u64 Size);
func_ string8 SkipStr8(string8 Str, u64 Amount);
func_ string8 SubstrStr8(string8 Str, u64 First, u64 opl);
func_ string8 SubsizeStr8(string8 Str, u64 First, u64 Size);

#define Str8Expand(s) (int)((s).size), ((s).str)

func_ string8 ChopAtLastSlashStr8(string8 Str);

func_ s32 S32FromStr8(string8 Str);
func_ s64 S64FromStr8(string8 Str);
func_ u32 U32FromStr8(string8 Str);
func_ u64 U64FromStr8(string8 Str);

func_ string8 Str8FromU64(arena *Arena, u64 Num);
func_ string8 Str8FromS64(arena *Arena, s64 Num);

/////////////////////////////////////////////////
//~ NOTE(nates): String helper functions

func_ b32 Str8Match(string8 A, string8 B, string_match_flags Flags);
func_ string8 FindFirstStr8(string8 Haystack, string8 Needle, string_match_flags Flags);

// NOTE(nates): Hashing

func_ u64 HashStr8(string8 String);

/////////////////////////////////////////
//~ NOTE(nates): String list functions

func_ void PushExplicitStr8List(string8_list *List, string8 String, string8_node *Node);
func_ void PushStr8List(arena *Arena, string8_list *List, string8 String);
func_ string8 JoinStr8List(arena *Arena, string8_list *List);
func_ string8_list SplitStr8List(arena *Arena, string8 String, u8 *Splits, u32 Count);

/////////////////////////////////////
//~ NOTE(nates): Format strings

func_ string8 PushFVStr8(arena *Arena, char *Fmt, va_list Args);
func_ string8 PushFStr8(arena *Arena, char *Fmt, ...);
func_ void PushFStr8List(arena *Arena, string8_list *List, char *Fmt, ...);

/////////////////////////////////////////
//~ NOTE(nates): Unicode Helpers

func_ string_decode DecodeUtf8Str(u8 *Str, u64 Cap);
func_ u32 EncodeUtf8Str(u8 *Dst, u32 Codepoint);
func_ string_decode DecodeUtf16Str(u16 *str, u32 Cap);
func_ u32 EncodeUtf16Str(u16 *Dst, u32 Codepoint);

func_ string32 Str32FromStr8(arena *Arena, string8 string);
func_ string8 Str8FromStr32(arena *Arena, string32 string);
func_ string16 Str16FromStr8(arena *Arena, string8 string);
func_ string8 Str8FromStr16(arena *Arena, string16 string);


#endif //BASE_STRING_H
