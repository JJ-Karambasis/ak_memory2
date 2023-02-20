#ifndef AK_MEMORY_H
#define AK_MEMORY_H

#ifdef AK_MEMORY_STATIC
#define AK_MEMORY_DEF static
#else
#ifdef __cplusplus
#define AK_MEMORY_DEF extern "C"
#else
#define AK_MEMORY_DEF extern
#endif
#endif

#include <stdint.h>

typedef uintptr_t akm_size;

typedef struct akm_allocator akm_allocator;

typedef void* akm_allocate_memory(akm_allocator* Allocator, akm_size Size);
typedef void  akm_free_memory(akm_allocator* Allocator, void* Memory);

typedef enum akm_clear_flag
{
    AKM_CLEAR_FLAG_CLEAR,
    AKM_CLEAR_FLAG_NO_CLEAR
} akm_clear_flag;

typedef struct akm_allocator
{
    void*                UserData;
    akm_allocate_memory* Allocate_Memory;
    akm_free_memory*     Free_Memory;
} akm_allocator;

typedef struct akm_os_allocator          akm_os_allocator;
typedef struct akm_arena                 akm_arena;
typedef struct akm_heap                  akm_heap;
typedef struct akm_fast_allocator        akm_fast_allocator;
typedef struct akm_heap_offset           akm_heap_offset;
typedef struct akm_fast_allocator_offset akm_fast_allocator_offset;

AK_MEMORY_DEF void* AKM_Allocate_Memory(akm_allocator* Allocator, akm_size Size, akm_clear_flag ClearFlag);
AK_MEMORY_DEF void  AKM_Free_Memory(akm_allocator* Allocator, void* Memory);

AK_MEMORY_DEF akm_os_allocator* AKM_OS_Allocator_Create();
AK_MEMORY_DEF void* AKM_OS_Allocator_Reserve(akm_os_allocator* Allocator, akm_size Size);
AK_MEMORY_DEF void  AKM_OS_Allocator_Commit(akm_os_allocator* Allocator, void* Memory, akm_size Size);
AK_MEMORY_DEF void  AKM_OS_Allocator_Decommit(akm_os_allocator* Allocator, void* Memory, akm_size Size);
AK_MEMORY_DEF void  AKM_OS_Allocator_Release(akm_os_allocator* Allocator, void* Memory, akm_size Size);
AK_MEMORY_DEF void  AKM_OS_Allocator_Delete(akm_os_allocator* Allocator);

typedef struct akm_arena_marker
{
    akm_arena* Arena;
    akm_size   Marker;
} akm_arena_marker;

AK_MEMORY_DEF akm_arena*       AKM_Arena_Create(akm_allocator* Allocator, akm_size ArenaSize);
AK_MEMORY_DEF void*            AKM_Arena_Push(akm_arena* Arena, akm_size Size, akm_clear_flag ClearFlag);
AK_MEMORY_DEF akm_arena_marker AKM_Arena_Get_Marker(akm_arena* Arena);
AK_MEMORY_DEF void             AKM_Arena_Set_Marker(akm_arena* Arena, akm_arena_marker Marker);
AK_MEMORY_DEF void             AKM_Arena_Clear(akm_arena* Arena, akm_clear_flag ClearFlag);
AK_MEMORY_DEF void             AKM_Arena_Delete(akm_arena* Arena);

AK_MEMORY_DEF akm_heap* AKM_Heap_Create(akm_allocator* Allocator, akm_size HeapSize);
AK_MEMORY_DEF void*     AKM_Heap_Allocate(akm_heap* Heap, akm_size Size, akm_clear_flag ClearFlag);
AK_MEMORY_DEF void      AKM_Heap_Free(akm_heap* Heap, void* Memory);
AK_MEMORY_DEF void      AKM_Heap_Clear(akm_heap* Heap, akm_clear_flag ClearFlag);
AK_MEMORY_DEF void      AKM_Heap_Delete(akm_heap* Heap);

AK_MEMORY_DEF akm_fast_allocator* AKM_Fast_Allocator_Create(akm_allocator* Allocator, akm_size Size, akm_size MaxAllocations);
AK_MEMORY_DEF void*               AKM_Fast_Allocator_Allocate(akm_fast_allocator* Allocator, akm_size Size, akm_clear_flag ClearFlag);
AK_MEMORY_DEF void                AKM_Fast_Allocator_Free(akm_fast_allocator* Allocator, void* Memory);
AK_MEMORY_DEF void                AKM_Fast_Allocator_Clear(akm_fast_allocator* Allocator, akm_clear_flag ClearFlag);
AK_MEMORY_DEF void                AKM_Fast_Allocator_Delete(akm_fast_allocator* Allocator);

typedef struct akm_offset_allocation
{
    akm_size Offset;
    akm_size Metadata;
} akm_offset_allocation;

AK_MEMORY_DEF akm_heap_offset* AKM_Heap_Offset_Create(akm_allocator* Allocator, akm_size HeapSize);
AK_MEMORY_DEF akm_offset_allocation AKM_Heap_Offset_Allocate(akm_heap_offset* Heap, akm_size Size);
AK_MEMORY_DEF void      AKM_Heap_Offset_Free(akm_heap_offset* Heap, akm_offset_allocation Allocation);
AK_MEMORY_DEF void      AKM_Heap_Offset_Clear(akm_heap_offset* Heap);
AK_MEMORY_DEF void      AKM_Heap_Offset_Delete(akm_heap_offset* Heap);

AK_MEMORY_DEF akm_fast_allocator_offset* AKM_Fast_Allocator_Offset_Create(akm_allocator* Allocator, akm_size Size, akm_size MaxAllocations);
AK_MEMORY_DEF akm_offset_allocation AKM_Fast_Allocator_Offset_Allocate(akm_fast_allocator_offset* Allocator, akm_size Size);
AK_MEMORY_DEF void AKM_Fast_Allocator_Offset_Free(akm_fast_allocator_offset* Allocator, akm_offset_allocation Allocation);
AK_MEMORY_DEF void AKM_Fast_Allocator_Offset_Clear(akm_fast_allocator_offset* Allocator);
AK_MEMORY_DEF void AKM_Fast_Allocator_Offset_Delete(akm_fast_allocator_offset* Allocator);

#endif

#ifdef AK_MEMORY_IMPLEMENTATION

#endif
