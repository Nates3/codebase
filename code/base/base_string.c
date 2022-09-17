
func_ U8 
U8Uppercase(U8 value)
{
	if('a' < value && value < 'z') {
		value -= 0x20;
	}
	return(value);
}

func_ U8 
U8Lowercase(U8 value)
{
	if('A' < value && value < 'Z') {
		value += 0x20;
	}
	return(value);
}

func_ B32
U8IsSlash(U8 character)
{
	B32 result = ((character == '\\') || (character == '/'));
	return(result);
}

func_ Str8
MStr8(U8 *str, U64 size)
{
	Str8 result = {str, size};
	return(result);
}

func_ Str8 
Str8Rng(U8 *first, U8 *opl)
{
	U64 string_size = (U64)opl - (U64)first;
	Str8 result = MStr8(first, string_size);
	return(result);
}

func_ Str8 
Str8FromCstr(U8 *cstr)
{
	U8 *search = cstr;
	for(;;) {
		if(*search == 0) {
			break;
		}
		search += 1;
	}
	
	U64 size = (U64)search - (U64)cstr;
	Str8 result = {cstr, size};
	return(result);
}

func_ char *
CstrFromStr8(Arena *arena, Str8 string)
{
	U8 *memory = PushArray(arena, U8, string.size + 1);
	U8 *ptr = memory;
	for(U32 index = 0;
			index < string.size;
			++index) {
		*ptr = string.m[index];
		ptr += 1;
	}
	
	*ptr = 0;
	return((char *)memory);
}

func_ Str8
Str8Copy(Arena *arena, Str8 string)
{
	U8 *memory = PushArray(arena, U8, string.size + 1);
	MemoryCopy(memory, string.m, string.size);
	memory[string.size] = 0;
	Str8 result = {
		.m = memory,
		.size = string.size,
	};
	return(result);
}



/////////////////////////
// NOTE(nates): string16 functions

func_ Str16
MStr16(U16 *str, U64 size)
{
	Str16 result = {str, size};
	return(result);
}

func_ Str16 
Str16FromCstr(U16 *str)
{
	Str16 result = {0};
	result.m = str;
	U16 *ptr = str;
	for(;*ptr != 0; ptr += 1);
	result.size = ptr - str;
	return(result);
}

//////////////////////////////////////////////////
// NOTE(nates): Str8 manipulation functions

func_ Str8
Str8Prefix(Str8 str, U64 size)
{
	U64 size_clamped = ClampTop(size, str.size);
	Str8 result = {str.m, size_clamped};
	return(result);
}

func_ Str8
Str8Chop(Str8 str, U64 amount)
{
	U64 amount_clamped = ClampTop(amount, str.size);
	U64 remaining_size = str.size - amount_clamped;
	Str8 result = {str.m, remaining_size};
	return(result);
}

func_ Str8
Str8Postfix(Str8 str, U64 size)
{
	U64 size_clamped = ClampTop(size, str.size);
	U64 skip_to = str.size - size_clamped;
	Str8 result = {str.m + skip_to, size_clamped};
	return(result);
}

func_ Str8
Str8Skip(Str8 str, U64 amount)
{
	U64 skip_clamped = ClampTop(amount, str.size);
	U64 remaining_size = str.size - skip_clamped;
	Str8 result = {str.m + skip_clamped, remaining_size };
	return(result);
}

func_ Str8 
Str8Substr(Str8 str, U64 first, U64 opl)
{
	U64 clamped_end = ClampTop(opl, str.size);
	U64 string_size = clamped_end - first;
	Str8 result = {str.m + first, string_size};
	return(result);
}

func_ Str8
Str8Subsize(Str8 str, U64 first, U64 size)
{
	Str8 result = Str8Substr(str, first, first + size);
	return(result);
}

func_ Str8 
Str8ChopAtLastSlash(Str8 str)
{
	Str8 result = str;
	if(str.size)
	{
		U64 last_slash = 0;
		U8 *opl = str.m + str.size;
		for(U8 *ptr = str.m; ptr < opl;ptr += 1) {
			if(CharIsSlash(*ptr)) {
				last_slash = (U64)(ptr - str.m);
			}
		}
		
		result = Str8Prefix(str, last_slash + 1);
	}
	return(result);
}

func_ S32 
S32FromStr8(Str8 str)
{
	Str8 num_part = str;
	B32 is_negative = false;
	if(str.m[0] == '-')
	{
		num_part = Str8Skip(str, 1);
		is_negative = true;
	}
	
	U32 result = 0;
	U64 exponent = num_part.size;
	for(U8 *ptr = num_part.m, *opl = num_part.m + num_part.size; ptr < opl; ptr += 1) {
		U32 digit = (U32)(*ptr) - 0x30;
		if(0 > digit || digit > 9) {
			InvalidPath;
		}
		for(U64 i = 1; i < exponent; ++i) {
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

func_ S64 
S64FromStr8(Str8 str)
{
	Str8 num_part = str;
	B32 is_negative = false;
	if(str.m[0] = '-')
	{
		num_part = Str8Skip(str, 1);
		is_negative = true;
	}
	
	U64 result = 0;
	U64 exponent = num_part.size;
	for(U8 *ptr = num_part.m, *opl = num_part.m + num_part.size; ptr < opl; ptr += 1) {
		U64 digit = (U64)(*ptr) - 0x30;
		if(0 > digit || digit > 9) {
			InvalidPath;
		}
		for(U64 i = 1; i < exponent; ++i) {
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

func_ U32 
U32FromStr8(Str8 str)
{
	U32 result = 0;
	U64 exponent = str.size;
	for(U8 *ptr = str.m, *opl = str.m + str.size; ptr < opl; ptr += 1) {
		U32 digit = (U32)(*ptr) - 0x30;
		if(0 > digit || digit > 9) {
			InvalidPath;
		}
		for(U64 i = 1; i < exponent; ++i) {
			digit *= 10;
		}
		result += digit;
		exponent--;
	}
	return(result);
}
func_ U64 
U64FromStr8(Str8 str)
{
	U64 result = 0;
	U64 exponent = str.size;
	for(U8 *ptr = str.m, *opl = str.m + str.size; ptr < opl; ptr += 1) {
		U64 digit = (U64)(*ptr) - 0x30;
		if(0 > digit || digit > 9) {
			InvalidPath;
		}
		for(U64 i = 1; i < exponent; ++i) {
			digit *= 10;
		}
		result += digit;
		exponent--;
	}
	return(result);
}

func_ Str8
Str8FromU64(Arena *arena, U64 num)
{
	ArenaTemp scratch = GetScratch(arena, 0);
	Str8 result = {0};
	Str8List digits = {0};
	for(;;) {
		U64 bottom_digit = num % 10;
		num /= 10;
		Str8Node *node = PushArray(scratch.arena, Str8Node, 1);
		node->str.m = PushArray(scratch.arena, U8, 1);
		node->str.m[0] = bottom_digit + 0x30;
		node->str.size = 1;
		QueuePushFront(digits.first, digits.last, node);
		digits.count += 1;
		digits.total_size += node->str.size;
		if(num == 0) { break; }
	}
	
	result = Str8ListJoin(arena, &digits);
	return(result);
}

func_ Str8
Str8FromS64(Arena *arena, S64 num)
{
	ArenaTemp scratch = GetScratch(arena, 0);
	Str8 result = {0};
	Str8List digits = {0};
	B32 push_hyphen = false;
	if(num < 0) {
		push_hyphen = true;
		num *= -1;
	}
	
	for(;;) {
		U64 bottom_digit = num % 10;
		num /= 10;
		Str8Node *node = PushArray(scratch.arena, Str8Node, 1);
		QueuePushFront(digits.first, digits.last, node);
		node->str.m = PushArray(scratch.arena, U8, 1);
		node->str.m[0] = bottom_digit + 0x30;
		node->str.size = 1;
		digits.count += 1;
		digits.total_size += node->str.size;
		if(num == 0) { break; }
	}
	
	// nates: push a negative to the front of a list
	if(push_hyphen)
	{
		Str8Node *node = PushArray(scratch.arena, Str8Node, 1);
		QueuePushFront(digits.first, digits.last, node);
		node->str.m = PushArray(scratch.arena, U8, 1);
		node->str.m[0] = '-';
		node->str.size = 1;
		digits.count += 1;
		digits.total_size += node->str.size;
	}
	
	result = Str8ListJoin(arena, &digits);
	return(result);
}


func_ B32 
Str8Match(Str8 a, Str8 b, StrMatchFlags flags)
{
	B32 result = false;
	if(a.size == b.size) {
		result = true;
		for(U32 index = 0; index < a.size; ++index) {
			B32 no_case = HasFlags(flags, StringMatchFlag_NoCase);
			U8 ca = a.m[index];
			U8 cb = b.m[index];
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

func_ Str8 
Str8FindFirst(Str8 haystack, Str8 needle, StrMatchFlags flags)
{
	Str8 result = {0};
	if(haystack.size >= needle.size) {
		U64 constrained_size = haystack.size - needle.size;
		for(U64 pos = 0; pos <= constrained_size; ++pos) {
			Str8 test = MStr8(haystack.m + pos, needle.size);
			if(Str8Match(test, needle, flags)) {
				result = test;
				break;
			}
		}
	}
	
	
	return(result);
}

func_ U64
Str8Hash(Str8 string)
{
	U64 hash = 0;
	for(U8 *p = string.m, *opl = string.m + string.size;
			p < opl; p += 1) {
		U8 v = *p;
		hash = ((hash << 5) + hash) + v;
	}
	return(hash);
}

func_ void 
Str8ListPushExplicit(Str8List *list, Str8 string, 
										 Str8Node *node)
{
	node->str = string;
	QueuePush(list->first, list->last, node);
	list->count += 1;
	list->total_size += string.size;
}

func_ void 
Str8ListPush(Arena *arena, Str8List *list, Str8 string)
{
	Str8Node *new_node = PushArray(arena, Str8Node, 1);
	Str8ListPushExplicit(list, string, new_node);
}

func_ Str8 
Str8ListJoin(Arena *arena, Str8List *list)
{
	U64 size = list->total_size;
	
	U8 *str = PushArray(arena, U8, size + 1);
	U8 *ptr = str;
	
	for(Str8Node *node = list->first;
			node != 0;
			node = node->next) {
		MemoryCopy(ptr, node->str.m, node->str.size);
		ptr += node->str.size;
	}
	MemoryZero(ptr, 1);
	
	Str8 result = {
		.m = str,
		.size = size,
	};
	
	return(result);
}

func_ Str8List 
Str8ListSplit(Arena *arena, Str8 string, U8 *splits, U32 count)
{
	Str8List result = {0};
	
	U8 *ptr = string.m;
	U8 *word_first = ptr;
	U8 *opl = string.m + string.size;
	
	for(;ptr < opl; ptr += 1) {
		U8 byte = *ptr;
		B32 is_split_byte = false;
		for(U32 i = 0; i < count; ++i) {
			if(byte == splits[i]) {
				is_split_byte = true;
				break;
			}
		}
		
		if(is_split_byte) {
			if(word_first < ptr) {
				Str8ListPush(arena, &result, Str8Rng(word_first, ptr));
			}
			word_first = ptr + 1;
		}
	}
	
	if(word_first < ptr) {
		Str8ListPush(arena, &result, Str8Rng(word_first, ptr));
	}
	return(result);
}

func_ Str8
Str8PushFV(Arena *arena, char *fmt, va_list args)
{
	va_list args2;
	va_copy(args2, args);
	
	U64 buffer_size = 1024;
	U8 *buffer = PushArray(arena, U8, buffer_size);
	U64 actual_size = vsnprintf((char *)buffer, buffer_size, fmt, args);
	
	Str8 result = {0};
	if(actual_size < buffer_size) {
		U64 size_that_we_didnt_use = buffer_size - actual_size;
		arenaPop(arena, size_that_we_didnt_use);
	}
	else {
		arenaPop(arena, buffer_size);
		U8 *fixed_buffer = PushArray(arena, U8, actual_size + 1);
		U64 final_size = vsnprintf((char *)fixed_buffer, actual_size + 1, fmt, args2);
		result = MStr8(fixed_buffer, final_size);
	}
	va_end(args2);
	return(result);
}

func_ Str8
Str8PushF(Arena *arena, char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Str8 result = Str8PushFV(arena, fmt, args);
	va_end(args);
	return(result);
}

func_ void
Str8ListPushF(Arena *arena, Str8List *list, char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Str8 string = Str8PushFV(arena, fmt, args);
	va_end(args);
	Str8ListPush(arena, list, string);
}

//~ NOTE(nates): Unicode helpers implementation

func_ StrDecode 
DecodeUtf8(U8 *str, U64 cap)
{
	local_ U8 lengths[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 
		2, 2, 2, 2, 
		3, 3, 
		4,
		0,
	};
	
	local_ U8 first_byte_masks[5] = {0x0, 0x7f, 0x1f, 0x0f, 0x07};
	local_ U8 final_shifts[5] = {18, 12, 6, 0};
	
	StrDecode result = {
		.codepoint = '#',
		.size = 1,
	};
	
	if(cap > 0) {
		U8 len = lengths[str[0] >> 3];
		U32 codepoint = 0;
		if(0 < len && len <= cap) {
			codepoint |= (str[0]&first_byte_masks[len]) << 18;
			result.size = len;
			len--;
			switch(len) {
				case 3: codepoint |= (str[3]&0x3f) << 0;
				case 2: codepoint |= (str[2]&0x3f) << 6;
				case 1: codepoint |= (str[1]&0x3f) << 12;
				case 0: codepoint >>= final_shifts[len];
			}
			result.codepoint = codepoint;
		}
	}
	return(result);
}

func_ U32 
EncodeUtf8(U8 *dst, U32 codepoint)
{
	U32 size = 0;
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

func_ StrDecode 
DecodeUtf16(U16 *str, U32 cap)
{
	StrDecode result = {'#', 1};
	U16 x = str[0];
	if(0xD800 < x && x < 0xDFFF) {
		if(cap >= 2) {
			U16 y = str[1];
			if((0xD800 <= x && x < 0xDC00) &&
				 (0xDC00 <= y && y < 0xDE00)) {
				U16 xj = x - 0xD800;
				U16 yj = y - 0xDC00;
				
				result.codepoint = ((y << 10) | (x)) + 0x10000;
				result.size = 2;
			}
		}
	}
	else {
		result.codepoint = str[0];
		result.size = 1;
	}
	
	return(result);
}

func_ U32 
EncodeUtf16(U16 *dst, U32 codepoint)
{
	U32 size = 0;
	if(codepoint < 0x10000) {
		dst[0] = codepoint;
		size = 1;
	}
	else {
		U32 cpj = codepoint - 0x10000;
		dst[0] = (cpj >> 10) + 0xD800;
		dst[1] = (cpj&0x3FF) + 0xDC00;
		size = 2;
	}
	return(size);
}

func_ Str32 
Str32FromStr8(Arena *arena, Str8 string)
{
	U64 alloc_count = string.size + 1;
	U32 *memory = PushArray(arena, U32, alloc_count);
	
	U32 *dptr = memory;
	U8 *ptr = string.m;
	U8 *opl = string.m + string.size;
	for(;;) {
		StrDecode decode = DecodeUtf8(ptr, (U64)(opl - ptr));
		*dptr = decode.codepoint;
		ptr += decode.size;
		dptr += 1;
		
		if(ptr == opl) {
			break;
		}
	}
	
	*dptr = 0;
	
	U64 string_count = (U64)(dptr - memory);
	U64 unused_count = alloc_count - string_count - 1;
	ArenaPop(arena, unused_count*sizeof(*memory));
	
	Str32 result = {0};
	result.m = memory;
	result.size = string_count;
	return(result);
}

func_ Str8
Str8FromStr32(Arena *arena, Str32 string)
{
	U64 alloc_count = string.size*4 + 1;
	U8 *memory = PushArray(arena, U8, alloc_count);
	
	U8 *dptr = memory;
	U32 *ptr = string.m;
	U32 *opl = string.m + string.size;
	for(;;) {
		U64 size = encode_utf8str(dptr, *ptr);
		ptr += 1;
		dptr += size;
		
		if(ptr == opl) {
			break;
		}
	}
	
	*dptr = 0;
	
	U64 string_count = (U64)(dptr - memory);
	U64 unused_count = alloc_count - string_count - 1;
	arenaPop(arena, unused_count);
	
	Str8 result = {0};
	result.m = memory;
	result.size = string_count;
	
	return(result);
}



func_ Str16
Str16FromStr8(Arena *arena, Str8 string)
{
	U64 alloc_count = string.size*2 + 1;
	U16 *memory = PushArray(arena, U16, alloc_count);
	
	U16 *dptr = memory;
	U8 *ptr = string.m;
	U8 *opl = string.m + string.size;
	for(;;) {
		StrDecode decode = DecodeUtf8(ptr, (U64)(opl - ptr));
		U32 enc_size = EncodeUtf16(dptr, decode.codepoint);
		ptr += decode.size;
		dptr += enc_size;
		
		if(ptr == opl) {
			break;
		}
	}
	
	*dptr = 0;
	
	U64 string_count = (U64)(dptr - memory);
	U64 unused_count = alloc_count - string_count - 1;
	ArenaPop(arena, unused_count*sizeof(*memory));
	
	Str16 result = {0};
	result.m = memory;
	result.size = string_count;
	return(result);
}

func_ Str8
Str8FromStr16(Arena *arena, Str16 string)
{
	U64 alloc_count = string.size*3 + 1;
	U8 *memory = PushArray(arena, U8, alloc_count);
	
	U8 *dptr = memory;
	U16 *ptr = string.m;
	U16 *opl = string.m + string.size;
	for(;;) {
		StrDecode decode = DecodeUtf16(ptr, (U64)(opl - ptr));
		U64 enc_size = EncodeUtf8(dptr, decode.codepoint);
		ptr += decode.size;
		dptr += enc_size;
		
		if(ptr == opl) {
			break;
		}
	}
	
	*dptr = 0;
	
	U64 string_count = (U64)(dptr - memory);
	U64 unused_count = alloc_count - string_count - 1;
	ArenaPop(arena, unused_count);
	
	Str8 result = {0};
	result.m = memory;
	result.size = string_count;
	
	return(result);
}
