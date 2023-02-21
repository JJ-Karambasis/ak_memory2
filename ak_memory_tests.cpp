#define  UTEST_IMPLEMENTATION
//#include "utest.h"

#include <stdio.h>

#define AK_MEMORY_IMPLEMENTATION
#include "ak_memory.h"

using namespace akm;

int main()
{
    auto_ptr<os_allocator> OSAllocator =  auto_ptr<os_allocator>(new os_allocator);
    //auto_ptr<arena_allocator> ArenaAllocator = auto_ptr<arena_allocator>(new(OSAllocator.Ptr()) arena_allocator(OSAllocator.Ptr()));
    
    str Str = AKM_StrC_Lit("Hello World");
    str Str2 = AKM_Str8_Lit("Hello World");
    str Str3("Hello World3");
    str Str4("Hello World %f. My name is %.*s", 4.2f, Str3.Count(), Str3.Ansii());
    
    str Str5 = Str3;
}

//UTEST_MAIN();