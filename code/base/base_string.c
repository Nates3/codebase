
func_ u8 
U8Uppercase(u8 value)
{
	if('a' < value && value < 'z') {
		value -= 0x20;
	}
	return(value);
}

func_ u8 
U8Lowercase(u8 value)
{
	if('A' < value && value < 'Z') {
		value += 0x20;
	}
	return(value);
}

func_ b32
CharIsSlash(u8 character)
{
	b32 result = ((character == '\\') || (character == '/'));
	return(result);
}

func_ string8
Str8(u8 *str, u64 size)
{
	string8 result = {str, size};
	return(result);
}

func_ string8 
Str8Rng(u8 *first, u8 *opl)
{
	u64 string_size = (u64)opl - (u64)first;
	string8 result = Str8(first, string_size);
	return(result);
}

func_ string8 
Str8Cstr(u8 *cstr)
{
	u8 *search = cstr;
	for(;;) {
		if(*search == 0) {
			break;
		}
		search += 1;
	}
	
	u64 size = (u64)search - (u64)cstr;
	string8 result = {cstr, size};
	return(result);
}

func_ char *
CstrStr8(arena *Arena, string8 string)
{
	u8 *memory = PushArray(Arena, u8, string.Size + 1);
	u8 *ptr = memory;
	for(u32 index = 0;
			index < string.Size;
			++index) {
		*ptr = string.M[index];
		ptr += 1;
	}
	
	*ptr = 0;
	return((char *)memory);
}

func_ string8
CopyStr8(arena *Arena, string8 string)
{
	u8 *memory = PushArray(Arena, u8, string.Size + 1);
	MemoryCopy(memory, string.M, string.Size);
	memory[string.Size] = 0;
	string8 result = {
		.M = memory,
		.Size = string.Size,
	};
	return(result);
}



/////////////////////////
// NOTE(nates): string16 functions

func_ string16
Str16(u16 *str, u64 size)
{
	string16 result = {str, size};
	return(result);
}

func_ string16 
Str16Cstr(u16 *str)
{
	string16 result = {0};
	result.M = str;
	u16 *ptr = str;
	for(;*ptr != 0; ptr += 1);
	result.Size = ptr - str;
	return(result);
}

//////////////////////////////////////////////////
// NOTE(nates): string8 manipulation functions

func_ string8
PrefixStr8(string8 str, u64 size)
{
	u64 size_clamped = ClampTop(size, str.Size);
	string8 result = {str.M, size_clamped};
	return(result);
}

func_ string8
ChopStr8(string8 str, u64 amount)
{
	u64 amount_clamped = ClampTop(amount, str.Size);
	u64 remaining_size = str.Size - amount_clamped;
	string8 result = {str.M, remaining_size};
	return(result);
}

func_ string8
PostfixStr8(string8 str, u64 size)
{
	u64 size_clamped = ClampTop(size, str.Size);
	u64 skip_to = str.Size - size_clamped;
	string8 result = {str.M + skip_to, size_clamped};
	return(result);
}

func_ string8
SkipStr8(string8 str, u64 amount)
{
	u64 skip_clamped = ClampTop(amount, str.Size);
	u64 remaining_size = str.Size - skip_clamped;
	string8 result = {str.M + skip_clamped, remaining_size };
	return(result);
}

func_ string8 
SubstrStr8(string8 str, u64 first, u64 opl)
{
	u64 clamped_end = ClampTop(opl, str.Size);
	u64 string_size = clamped_end - first;
	string8 result = {str.M + first, string_size};
	return(result);
}

func_ string8
SubsizeStr8(string8 str, u64 first, u64 size)
{
	string8 result = SubstrStr8(str, first, first + size);
	return(result);
}

func_ string8 
ChopAtLastSlashStr8(string8 str)
{
	string8 result = str;
	if(str.Size)
	{
		u64 last_slash = 0;
		u8 *opl = str.M + str.Size;
		for(u8 *ptr = str.M; ptr < opl;ptr += 1) {
			if(CharIsSlash(*ptr)) {
				last_slash = (u64)(ptr - str.M);
			}
		}
		
		result = PrefixStr8(str, last_slash + 1);
	}
	return(result);
}

func_ s32 
S32FromStr8(string8 str)
{
	string8 num_part = str;
	b32 is_negative = false;
	if(str.M[0] == '-')
	{
		num_part = SkipStr8(str, 1);
		is_negative = true;
	}
	
	u32 result = 0;
	u64 exponent = num_part.Size;
	for(u8 *ptr = num_part.M, *opl = num_part.M + num_part.Size; ptr < opl; ptr += 1) {
		u32 digit = (u32)(*ptr) - 0x30;
		if(0 > digit || digit > 9) {
			InvalidPath;
		}
		for(u64 i = 1; i < exponent; ++i) {
			digit *= 10;
		}
		result += digit;
		exponent--;
	}
	
	if(is_negative)
	{
		result *= -1;
	}
	
	return(result);
}

func_ s64 
S64FromStr8(string8 str)
{
	string8 num_part = str;
	b32 is_negative = false;
	if(str.M[0] = '-')
	{
		num_part = SkipStr8(str, 1);
		is_negative = true;
	}
	
	u64 result = 0;
	u64 exponent = num_part.Size;
	for(u8 *ptr = num_part.M, *opl = num_part.M + num_part.Size; ptr < opl; ptr += 1) {
		u64 digit = (u64)(*ptr) - 0x30;
		if(0 > digit || digit > 9) {
			InvalidPath;
		}
		for(u64 i = 1; i < exponent; ++i) {
			digit *= 10;
		}
		result += digit;
		exponent--;
	}
	
	if(is_negative)
	{
		result *= -1;
	}
	
	return(result);
}

func_ u32 
U32FromStr8(string8 str)
{
	u32 result = 0;
	u64 exponent = str.Size;
	for(u8 *ptr = str.M, *opl = str.M + str.Size; ptr < opl; ptr += 1) {
		u32 digit = (u32)(*ptr) - 0x30;
		if(0 > digit || digit > 9) {
			InvalidPath;
		}
		for(u64 i = 1; i < exponent; ++i) {
			digit *= 10;
		}
		result += digit;
		exponent--;
	}
	return(result);
}
func_ u64 
U64FromStr8(string8 str)
{
	u64 result = 0;
	u64 exponent = str.Size;
	for(u8 *ptr = str.M, *opl = str.M + str.Size; ptr < opl; ptr += 1) {
		u64 digit = (u64)(*ptr) - 0x30;
		if(0 > digit || digit > 9) {
			InvalidPath;
		}
		for(u64 i = 1; i < exponent; ++i) {
			digit *= 10;
		}
		result += digit;
		exponent--;
	}
	return(result);
}

func_ string8
Str8FromU64(arena *Arena, u64 num)
{
	arena_temp scratch = GetScratch(Arena, 0);
	string8 result = {0};
	string8_list digits = {0};
	for(;;) {
		u64 bottom_digit = num % 10;
		num /= 10;
		string8_node *node = PushArray(scratch.Arena, string8_node, 1);
		node->String.M = PushArray(scratch.Arena, u8, 1);
		node->String.M[0] = bottom_digit + 0x30;
		node->String.Size = 1;
		QueuePushFront(digits.First, digits.Last, node);
		digits.Count += 1;
		digits.TotalSize += node->String.Size;
		if(num == 0) { break; }
	}
	
	result = JoinStr8List(Arena, &digits);
	return(result);
}

func_ string8
Str8FromS64(arena *Arena, s64 num)
{
	arena_temp scratch = GetScratch(Arena, 0);
	string8 result = {0};
	string8_list digits = {0};
	b32 push_hyphen = false;
	if(num < 0) {
		push_hyphen = true;
		num *= -1;
	}
	
	for(;;) {
		u64 bottom_digit = num % 10;
		num /= 10;
		string8_node *node = PushArray(scratch.Arena, string8_node, 1);
		QueuePushFront(digits.First, digits.Last, node);
		node->String.M = PushArray(scratch.Arena, u8, 1);
		node->String.M[0] = bottom_digit + 0x30;
		node->String.Size = 1;
		digits.Count += 1;
		digits.TotalSize += node->String.Size;
		if(num == 0) { break; }
	}
	
	// nates: push a negative to the front of a list
	if(push_hyphen)
	{
		string8_node *node = PushArray(scratch.Arena, string8_node, 1);
		QueuePushFront(digits.First, digits.Last, node);
		node->String.M = PushArray(scratch.Arena, u8, 1);
		node->String.M[0] = '-';
		node->String.Size = 1;
		digits.Count += 1;
		digits.TotalSize += node->String.Size;
	}
	
	result = JoinStr8List(Arena, &digits);
	return(result);
}


func_ b32 
Str8Match(string8 a, string8 b, string_match_flags flags)
{
	b32 result = false;
	if(a.Size == b.Size) {
		result = true;
		for(u32 index = 0; index < a.Size; ++index) {
			b32 no_case = HasFlags(flags, StringMatchFlag_NoCase);
			u8 ca = a.M[index];
			u8 cb = b.M[index];
			if(no_case) {
				ca = U8Uppercase(ca);
				cb = U8Uppercase(cb);
			}
			if(ca != cb) {
				result = false;
				break;
			}
		}
	}
	return(result);
}

func_ string8 
FindFirstStr8(string8 haystack, string8 needle, string_match_flags flags)
{
	string8 result = {0};
	if(haystack.Size >= needle.Size) {
		u64 constrained_size = haystack.Size - needle.Size;
		for(u64 pos = 0; pos <= constrained_size; ++pos) {
			string8 test = Str8(haystack.M + pos, needle.Size);
			if(Str8Match(test, needle, flags)) {
				result = test;
				break;
			}
		}
	}
	
	
	return(result);
}

func_ u64
HashStr8(string8 string)
{
	u64 hash = 0;
	for(u8 *p = string.M, *opl = string.M + string.Size;
			p < opl; p += 1) {
		u8 v = *p;
		hash = ((hash << 5) + hash) + v;
	}
	return(hash);
}

func_ void 
PushExplicitStr8List(string8_list *list, string8 string, 
										 string8_node *node)
{
	node->String = string;
	QueuePush(list->First, list->Last, node);
	list->Count += 1;
	list->TotalSize += string.Size;
}

func_ void 
PushStr8List(arena *Arena, string8_list *list, string8 string)
{
	string8_node *new_node = PushArray(Arena, string8_node, 1);
	PushExplicitStr8List(list, string, new_node);
}

func_ string8 
JoinStr8List(arena *Arena, string8_list *list)
{
	u64 size = list->TotalSize;
	
	u8 *str = PushArray(Arena, u8, size + 1);
	u8 *ptr = str;
	
	for(string8_node *node = list->First;
			node != 0;
			node = node->Next) {
		MemoryCopy(ptr, node->String.M, node->String.Size);
		ptr += node->String.Size;
	}
	MemoryZero(ptr, 1);
	
	string8 result = {
		.M = str,
		.Size = size,
	};
	
	return(result);
}

func_ string8_list 
SplitStr8List(arena *Arena, string8 string, u8 *splits, u32 count)
{
	string8_list result = {0};
	
	u8 *ptr = string.M;
	u8 *word_first = ptr;
	u8 *opl = string.M + string.Size;
	
	for(;ptr < opl; ptr += 1) {
		u8 byte = *ptr;
		b32 is_split_byte = false;
		for(u32 i = 0; i < count; ++i) {
			if(byte == splits[i]) {
				is_split_byte = true;
				break;
			}
		}
		
		if(is_split_byte) {
			if(word_first < ptr) {
				Str8ListPush(Arena, &result, Str8Rng(word_first, ptr));
			}
			word_first = ptr + 1;
		}
	}
	
	if(word_first < ptr) {
		Str8ListPush(Arena, &result, Str8Rng(word_first, ptr));
	}
	return(result);
}

func_ string8
PushFVStr8(arena *Arena, char *fmt, va_list args)
{
	va_list args2;
	va_copy(args2, args);
	
	u64 buffer_size = 1024;
	u8 *buffer = PushArray(Arena, u8, buffer_size);
	u64 actual_size = vsnprintf((char *)buffer, buffer_size, fmt, args);
	
	string8 result = {0};
	if(actual_size < buffer_size) {
		u64 size_that_we_didnt_use = buffer_size - actual_size;
		ArenaPop(Arena, size_that_we_didnt_use);
	}
	else {
		ArenaPop(Arena, buffer_size);
		u8 *fixed_buffer = PushArray(Arena, u8, actual_size + 1);
		u64 final_size = vsnprintf((char *)fixed_buffer, actual_size + 1, fmt, args2);
		result = Str8(fixed_buffer, final_size);
	}
	va_end(args2);
	return(result);
}

func_ string8
PushFStr8(arena *Arena, char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	string8 result = PushFVStr8(Arena, fmt, args);
	va_end(args);
	return(result);
}

func_ void
PushFStr8List(arena *Arena, string8_list *list, char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	string8 string = PushFVStr8(Arena, fmt, args);
	va_end(args);
	Str8ListPush(Arena, list, string);
}

//~ NOTE(nates): Unicode helpers implementation

func_ string_decode 
DecodeUtf8Str(u8 *str, u64 cap)
{
	local_ u8 lengths[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 
		2, 2, 2, 2, 
		3, 3, 
		4,
		0,
	};
	
	local_ u8 first_byte_masks[5] = {0x0, 0x7f, 0x1f, 0x0f, 0x07};
	local_ u8 final_shifts[5] = {18, 12, 6, 0};
	
	string_decode result = {
		.Codepoint = '#',
		.Size = 1,
	};
	
	if(cap > 0) {
		u8 len = lengths[str[0] >> 3];
		u32 codepoint = 0;
		if(0 < len && len <= cap) {
			codepoint |= (str[0]&first_byte_masks[len]) << 18;
			result.Size = len;
			len--;
			switch(len) {
				case 3: codepoint |= (str[3]&0x3f) << 0;
				case 2: codepoint |= (str[2]&0x3f) << 6;
				case 1: codepoint |= (str[1]&0x3f) << 12;
				case 0: codepoint >>= final_shifts[len];
			}
			result.Codepoint = codepoint;
		}
	}
	return(result);
}

func_ u32 
EncodeUtf8Str(u8 *dst, u32 codepoint)
{
	u32 size = 0;
	if(codepoint < (1 << 8)) {
		dst[0] = codepoint;
		size = 1;
	}
	else if(codepoint < (1 << 11)) {
		dst[0] = 0xc0 | (codepoint >> 6);
		dst[1] = 0x80 | (codepoint&0x3f);
		size = 2;
	}
	else if(codepoint < (1 << 16)) {
		dst[0] = 0xe0 | (codepoint >> 12);
		dst[1] = 0x80 | ((codepoint >> 6)&0x3f);
		dst[2] = 0x80 | (codepoint&0x3f);
		size = 3;
	}
	else if(codepoint < (1 << 21)) {
		dst[0] = 0xf0 | (codepoint >> 18);
		dst[1] = 0x80 | ((codepoint >> 12)&0x3f);
		dst[2] = 0x80 | ((codepoint >> 6)&0x3f);
		dst[3] = 0x80 | (codepoint&0x3f);
		size = 4;
	}
	else {
		dst[0] = '#';
		size = 1;
	}
	
	return(size);
}

func_ string_decode 
DecodeUtf16Str(u16 *str, u32 cap)
{
	string_decode result = {'#', 1};
	u16 x = str[0];
	if(0xD800 < x && x < 0xDFFF) {
		if(cap >= 2) {
			u16 y = str[1];
			if((0xD800 <= x && x < 0xDC00) &&
				 (0xDC00 <= y && y < 0xDE00)) {
				u16 xj = x - 0xD800;
				u16 yj = y - 0xDC00;
				
				result.Codepoint = ((y << 10) | (x)) + 0x10000;
				result.Size = 2;
			}
		}
	}
	else {
		result.Codepoint = str[0];
		result.Size = 1;
	}
	
	return(result);
}

func_ u32 
EncodeUtf16Str(u16 *dst, u32 codepoint)
{
	u32 size = 0;
	if(codepoint < 0x10000) {
		dst[0] = codepoint;
		size = 1;
	}
	else {
		u32 cpj = codepoint - 0x10000;
		dst[0] = (cpj >> 10) + 0xD800;
		dst[1] = (cpj&0x3FF) + 0xDC00;
		size = 2;
	}
	return(size);
}

func_ string32 
Str32FromStr8(arena *Arena, string8 string)
{
	u64 alloc_count = string.Size + 1;
	u32 *memory = PushArray(Arena, u32, alloc_count);
	
	u32 *dptr = memory;
	u8 *ptr = string.M;
	u8 *opl = string.M + string.Size;
	for(;;) {
		string_decode decode = DecodeUtf8Str(ptr, (u64)(opl - ptr));
		*dptr = decode.Codepoint;
		ptr += decode.Size;
		dptr += 1;
		
		if(ptr == opl) {
			break;
		}
	}
	
	*dptr = 0;
	
	u64 string_count = (u64)(dptr - memory);
	u64 unused_count = alloc_count - string_count - 1;
	ArenaPop(Arena, unused_count*sizeof(*memory));
	
	string32 result = {0};
	result.M = memory;
	result.Size = string_count;
	return(result);
}

func_ string8
Str8FromStr32(arena *Arena, string32 string)
{
	u64 alloc_count = string.Size*4 + 1;
	u8 *memory = PushArray(Arena, u8, alloc_count);
	
	u8 *dptr = memory;
	u32 *ptr = string.M;
	u32 *opl = string.M + string.Size;
	for(;;) {
		u64 size = encode_utf8str(dptr, *ptr);
		ptr += 1;
		dptr += size;
		
		if(ptr == opl) {
			break;
		}
	}
	
	*dptr = 0;
	
	u64 string_count = (u64)(dptr - memory);
	u64 unused_count = alloc_count - string_count - 1;
	ArenaPop(Arena, unused_count);
	
	string8 result = {0};
	result.M = memory;
	result.Size = string_count;
	
	return(result);
}



func_ string16
Str16FromStr8(arena *Arena, string8 string)
{
	u64 alloc_count = string.Size*2 + 1;
	u16 *memory = PushArray(Arena, u16, alloc_count);
	
	u16 *dptr = memory;
	u8 *ptr = string.M;
	u8 *opl = string.M + string.Size;
	for(;;) {
		string_decode decode = DecodeUtf8Str(ptr, (u64)(opl - ptr));
		u32 enc_size = EncodeUtf16Str(dptr, decode.Codepoint);
		ptr += decode.Size;
		dptr += enc_size;
		
		if(ptr == opl) {
			break;
		}
	}
	
	*dptr = 0;
	
	u64 string_count = (u64)(dptr - memory);
	u64 unused_count = alloc_count - string_count - 1;
	ArenaPop(Arena, unused_count*sizeof(*memory));
	
	string16 result = {0};
	result.M = memory;
	result.Size = string_count;
	return(result);
}

func_ string8
Str8FromStr16(arena *Arena, string16 string)
{
	u64 alloc_count = string.Size*3 + 1;
	u8 *memory = PushArray(Arena, u8, alloc_count);
	
	u8 *dptr = memory;
	u16 *ptr = string.M;
	u16 *opl = string.M + string.Size;
	for(;;) {
		string_decode decode = DecodeUtf16Str(ptr, (u64)(opl - ptr));
		u64 enc_size = EncodeUtf8Str(dptr, decode.Codepoint);
		ptr += decode.Size;
		dptr += enc_size;
		
		if(ptr == opl) {
			break;
		}
	}
	
	*dptr = 0;
	
	u64 string_count = (u64)(dptr - memory);
	u64 unused_count = alloc_count - string_count - 1;
	ArenaPop(Arena, unused_count);
	
	string8 result = {0};
	result.M = memory;
	result.Size = string_count;
	
	return(result);
}
