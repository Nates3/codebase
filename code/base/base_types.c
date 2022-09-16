

 func_ operating_system
OS_Context(void)
{
	operating_system Result = OperatingSystem_Null;
#if OS_WINDOWS
	Result = OperatingSystem_Windows;
#elif OS_LINUX
	Result = OperatingSystem_Linux;
#elif OS_MAC
	Result = OperatingSystem_Mac;
#endif
	return(Result);
}


func_ architecture 
Arch_Context(void)
{
	architecture Result = Architecture_Null;
#if ARCH_X64
	Result = Architecture_X64;
#elif ARCH_X86
	Result = Architecture_X86;
#elif ARCH_ARM
	Result = Architecture_Arm;
#endif
	return(Result);
}

func_ char *
CstrFromOS(operating_system OS)
{
	char *Result = 0;
	switch(OS) {
		case OperatingSystem_Null: {
			Result = "Null";
		} break;
		case OperatingSystem_Windows: {
			Result = "Windows";
		} break;
		case OperatingSystem_Linux: {
			Result = "Linux";
		} break;
		case OperatingSystem_Mac: {
			Result = "Mac";
		} break;
	}
	return(Result);
}

func_ char *
CstrFromArch(architecture Arch)
{
	char *Result = 0;
	switch(Arch)
	{
		case Architecture_Null: {
			Result = "Null";
		} break;
		case Architecture_X64: {
			Result = "X64";
		} break;
		case Architecture_X86: {
			Result = "X86";
		} break;
		case Architecture_Arm: {
			Result = "Arm";
		} break;
		
		InvalidCase;
	}
	return(Result);
}

func_ char *
CstrFromMonth(month Month)
{
	char *Result = 0;
	switch(Month)
	{
		case Month_Jan: {
			Result = "January";
		} break;
		case Month_Feb: {
			Result = "Feburary";
		} break;
		case Month_Mar: {
			Result = "March";
		} break;
		case Month_Apr: {
			Result = "April";
		} break;
		case Month_May: {
			Result = "May";
		} break;
		case Month_Jun: {
			Result = "June";
		} break;
		case Month_Jul: {
			Result = "July";
		} break;
		case Month_Aug: {
			Result = "August";
		} break;
		case Month_Sep: {
			Result = "September";
		} break;
		case Month_Oct: {
			Result = "October";
		} break;
		case Month_Nov: {
			Result = "November";
		} break;
		case Month_Dec: {
			Result = "Decemeber";
		} break;
		
		InvalidCase;
	}
	return(Result);
}

func_ char *
CstrFromWeekday(week_day day)
{
	char *Result = 0;
	switch(day)
	{
		case WeekDay_Monday: {
			Result = "Monday";
		} break;
		case WeekDay_Tuesday: {
			Result = "Tuesday";
		} break;
		case WeekDay_Wednsday: {
			Result = "Wednsday";
		} break;
		case WeekDay_Thursday: {
			Result = "Thursday";
		} break;
		case WeekDay_Friday: {
			Result = "Friday";
		} break;
		case WeekDay_Saturday: {
			Result = "Saturday";
		} break;
		case WeekDay_Sunday: {
			Result = "Sunday";
		} break;
		
		InvalidCase;
	}
	return(Result);
}

////////////////////////////////////
// NOTE(nates): Time functions

func_ dense_time
DenseTimeFromDateTime(date_time *time)
{
	u64 result = 0;
	u32 year_decoded = (u32)((s32)time->Year + 0x8000);
	result += year_decoded;
	result *= 12;
	result += (time->Mon + 1);
	result *= 31;
	result += time->Day;
	result *= 24;
	result += time->Hour;
	result *= 60;
	result += time->Min;
	result *= 61;
	result += time->Sec;
	result *= 1000;
	result += time->Ms;
	return(result);
}

func_ date_time
DateTimeFromDenseTime(dense_time time)
{
	date_time result = {0};
	result.Ms = time%1000;
	time /= 1000;
	result.Sec = time%61;
	time /= 61;
	result.Min = time%60;
	time /= 60;
	result.Hour = time%24;
	time /= 24;
	result.Day = time%31;
	time /= 31;
	result.Mon = (time%12) + 1;
	time /= 12;
	s32 year_encoded = (s32)time;
	result.Year = (u32)(year_encoded - 0x8000);
	return(result);
}