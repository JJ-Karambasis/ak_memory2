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

#ifndef AKM_DEFAULT_ARENA_BLOCK_SIZE
#define AKM_DEFAULT_ARENA_BLOCK_SIZE (1024*1024)
#endif

#ifndef AKM_DEFAULT_HEAP_BLOCK_SIZE
#define AKM_DEFAULT_HEAP_BLOCK_SIZE (1024*1024)
#endif

#ifndef AKM_DEFAULT_FAST_ALLOCATOR_BLOCK_SIZE
#define AKM_DEFAULT_FAST_ALLOCATOR_BLOCK_SIZE (1024*1024)
#endif

#ifndef AKM_DEFAULT_VECTOR_CAPACITY
#define AKM_DEFAULT_VECTOR_CAPACITY 128
#endif

#ifndef AKM_DEFAULT_HASHMAP_SLOT_CAPACITY
#define AKM_DEFAULT_HASHMAP_SLOT_CAPACITY 128
#endif

#ifndef AKM_DEFAULT_POOL_CAPACITY
#define AKM_DEFAULT_POOL_CAPACITY 128
#endif

typedef uint8_t   akm_u8;
typedef uint16_t  akm_u16;
typedef uint32_t  akm_u32;
typedef uint64_t  akm_u64;
typedef int8_t    akm_s8;
typedef int16_t   akm_s16;
typedef int32_t   akm_s32;
typedef int64_t   akm_s64;
typedef akm_s32   akm_b32;
typedef uintptr_t akm_size;

namespace akm
{
    template <typename type> class auto_ptr
    {
        private:
        akm_b32 m_ShouldDelete;
        type*   m_Ptr;
        
        public:
        auto_ptr(type* Ptr);
        type* operator->();
        type* Release();
        type* Ptr();
        ~auto_ptr();
    };
    
    class allocator;
    template <typename type> class array;
    template <typename type> class vector;
    
    template <typename type> class span
    {
        private:
        const type* m_First;
        const type* m_End;
        
        public:
        span();
        span(const type* First, const type* Last);
        span(const type* First, akm_size Count);
        span(const array<type>& Array);
        span(const vector<type>& Vector);
        
        const type& operator[] (akm_size Index) const;
        akm_size Count() const;
        akm_size Byte_Size() const;
        bool Is_Empty() const;
        
        const type* begin() const;
        const type* end() const;
    };
    
    template <typename type> class array
    {
        private:
        type*    m_First;
        akm_size m_Count;
        
        public:
        array();
        array(type* First, type* Last);
        array(type* First, akm_size Count);
        array(const vector<type>& Vector);
        
        type& operator[](akm_size Index);
        const type& operator[](akm_size Index) const;
        akm_size Count() const;
        akm_size Byte_Size() const;
        bool Is_Empty() const;
        
        const type* begin() const;
        const type* end() const;
        
        type* begin();
        type* end();
    };
    
    template <typename type> class vector
    {
        private:
        allocator* m_Allocator;
        type*      m_Data;
        akm_size   m_Count;
        akm_size   m_Capacity;
        
        public:
        vector(allocator* Allocator, akm_size Size=AKM_DEFAULT_VECTOR_CAPACITY);
        vector(allocator* Allocator, type* First, akm_size Count);
        vector(allocator* Allocator, type* First, type* Last);
        vector(allocator* Allocator, const array<type>& Array);
        
        type& operator[](akm_size Index);
        const type& operator[](akm_size Index) const;
        akm_size Count() const;
        akm_size Byte_Size() const;
        bool Is_Empty() const;
        
        void Add(const type& Type);
        void Add_Range(const type* Type, akm_size Count);
        void Pop();
        
        void Clear();
        void Release();
        void Resize(akm_size Size);
        void Reserve(akm_size Size);
        
        const type* begin() const;
        const type* end() const;
        
        type* begin();
        type* end();
        
        void operator delete(void* Vector);
    };
    
    
    template <typename key, typename value> class hashmap
    {
        public:
        hashmap(allocator* Allocator, akm_size SlotCapacity=AKM_DEFAULT_HASHMAP_SLOT_CAPACITY);
        
        void         Add(const key& Key, const value& Value);
        value*       Get(const key& Key);
        const value* Get(const key& Key) const;
        value&       operator[](const key& Key);
        const value& operator[](const key& Key) const;
        void         Remove(const key& Key);
        
        void Clear();
        void Release();
        
        void operator delete(void* Hashmap);
    };
    
    template <typename type> class pool;
    
    template <typename type> struct handle
    {
        akm_u64     ID;
        pool<type>* Pool;
    };
    
    template <typename type> class pool
    {
        public:
        pool(allocator* Allocator, akm_size Capacity=AKM_DEFAULT_POOL_CAPACITY);
        
        handle<type> Allocate();
        void         Free(const handle<type>& Handle);
        type*        Get(const handle<type>& Handle);
        const type*  Get(const handle<type>& Handle) const;
        type&        operator[](const handle<type>& Handle);
        const type&  operator[](const handle<type>& Handle) const;
        
        void Clear();
        void Release();
        
        void operator delete(void* Pool);
    };
    
    enum class str_encoding
    {
        ANSII,
        UTF8,
        UTF16,
        UTF32
    };
    
    class strc
    {
        private:
        const char* m_Str;
        akm_size    m_Count;
        
        public:
        strc();
        strc(const char* Str, ...);
        strc(const char* Str, akm_size Count);
        strc(const char* First, const char* End);
        strc(const strc& Str, ...);
        strc(const str8& Str, ...);
        strc(const str16& Str);
        strc(const str32& Str);
    };
    
    class str8
    {
        private:
        const akm_u8* m_Str;
        akm_size      m_Count;
        
        public:
        str8();
        str8(const akm_u8* Str, ...);
        str8(const akm_u8* Str,   akm_size Count);
        str8(const akm_u8* First, const akm_u8* End);
    };
    
    class str16
    {
        private:
        const akm_u16* m_Str;
        akm_size       m_Count;
        
        public:
        str16();
        str16(const akm_u16* Str);
        str16(const akm_u16* Str,   akm_size Count);
        str16(const akm_u16* First, const akm_u16* End);
    };
    
    class str32
    {
        private:
        const akm_u32* Str;
        akm_size       Count;
        
        public:
        str32(const akm_u32* Str);
        str32(const akm_u32* Str,   akm_size Count);
        str32(const akm_u32* First, const akm_u32* End);
    };
    
    class str
    {
        private:
        str_encoding m_Encoding;
        union
        {
            strc  m_Ansii;
            str8  m_UTF8;
            str16 m_UTF16;
            str32 m_UTF32;
        };
        
        public:
        str(const char*    Str, ...);
        str(const akm_u8*  Str, ...);
        str(const akm_u16* Str);
        str(const akm_u32* Str);
        str(const char*    Str, akm_size Count);
        str(const akm_u8*  Str, akm_size Count);
        str(const akm_u16* Str, akm_size Count);
        str(const akm_u32* Str, akm_size Count);
        str(const strc& Str, ...);
        str(const str8& Str, ...);
        str(const str16& Str);
        str(const str32& Str);
        str(const void* Str, akm_size Count, str_encoding Encoding);
        
        akm_size       Count() const;
        const char*    Ansii() const;
        const akm_u8*  UTF8() const;
        const akm_u16* UTF16() const;
        const akm_u32* UTF32() const;
    };
    
    enum class clear_flag
    {
        Clear,
        NoClear
    };
    
    class allocator
    {
        public:
        virtual void* Allocate(akm_size Size, clear_flag Flag) = 0;
        virtual void  Free(void* Memory) = 0;
    };
    
    class os_allocator : public allocator
    {
        public:
        void* Allocate(akm_size Size, clear_flag Flag) override;
        void  Free(void* Memory) override;
        
        void* Reserve(akm_size Size);
        void* Commit(void* Memory, akm_size Size);
        void  Decommit(void* Memory, akm_size Size);
        void  Release(void* Memory, akm_size Size);
        
        void* operator new(akm_size Size);
        void  operator delete(void* Allocator);
    };
    
    struct arena_marker
    {
        class  arena_allocator* Arena;
        struct arena__block*    CurrentBlock;
        akm_size Marker;
    };
    
    class arena_allocator : public allocator
    {
        private:
        allocator* m_Allocator;
        
        public:
        arena_allocator(allocator* Allocator, akm_size BlockSize=AKM_DEFAULT_ARENA_BLOCK_SIZE);
        
        void* Allocate(akm_size Size, clear_flag Flag) override;
        void  Free(void* Memory) override;
        
        void*                                Push(akm_size Size, clear_flag Flag);
        template <typename type> type*       Push(clear_flag Flag);
        template <typename type> array<type> Push(akm_size Count, clear_flag Flag);
        
        arena_marker Get_Marker();
        void         Set_Marker(arena_marker Marker);
        
        void Clear(clear_flag Flag);
        void Release();
        
        void* operator new(akm_size Size, allocator* Allocator);
        void  operator delete(void* Allocator);
    };
    
    class temporary_arena
    {
        private:
        arena_marker     Marker;
        arena_allocator* Arena;
        
        public:
        temporary_arena(arena_allocator* Allocator);
        ~temporary_arena();
    };
    
    class heap_allocator : public allocator
    {
        private:
        allocator* m_Allocator;
        
        public:
        heap_allocator(allocator* Allocator, akm_size BlockSize = AKM_DEFAULT_HEAP_BLOCK_SIZE);
        
        void* Allocate(akm_size Size, clear_flag Flag) override;
        void  Free(void* Memory) override;
        
        void  Clear(clear_flag Flag);
        void  Release();
        
        void* operator new(akm_size Size, allocator* Allocator);
        void  operator delete(void* Allocator);
    };
    
    class fast_allocator : public allocator
    {
        private:
        allocator* m_Allocator;
        
        public:
        fast_allocator(allocator* Allocator, akm_size BlockSize = AKM_DEFAULT_FAST_ALLOCATOR_BLOCK_SIZE);
        
        void* Allocate(akm_size Size, clear_flag Flag) override;
        void  Free(void* Memory) override;
        
        void Clear(clear_flag Flag); 
        void Release();
        
        void* operator new(akm_size Size, allocator* Allocator);
        void  operator delete(void* Allocator);
    };
};

#define AKM_StrC_Lit(Str) str((char*)(Str), sizeof((Str))-1)
#define AKM_Str8_Lit(Str) str((akm_u8*)(Str), sizeof((Str))-1)

#endif

#ifdef AK_MEMORY_IMPLEMENTATION

#ifdef _MSC_VER
#include <windows.h>
#endif

namespace akm
{
    template <typename type> auto_ptr<type>::auto_ptr(type* Ptr) : m_Ptr(Ptr), m_ShouldDelete(true) {}
    template <typename type> type* auto_ptr<type>::operator->() { return m_Ptr; }
    template <typename type> type* auto_ptr<type>::Release() { m_ShouldDelete = false; return m_Ptr; }
    template <typename type> type* auto_ptr<type>::Ptr() { return m_Ptr; }
    template <typename type> auto_ptr<type>::~auto_ptr() { if(m_ShouldDelete) delete m_Ptr; }
    
    void* os_allocator::Allocate(akm_size Size, clear_flag Flag)
    {
        akm_size TotalSize = Size+sizeof(size_t);
        size_t* Memory = (size_t*)Reserve(TotalSize);
        Commit(Memory, TotalSize);
        *Memory = TotalSize;
        return Memory+1;
    }
    
    void  os_allocator::Free(void* Memory)
    {
        size_t* MemoryPtr = ((size_t*)Memory)-1;
        size_t Size = *MemoryPtr;
        Decommit(MemoryPtr, Size);
        Release(MemoryPtr, Size);
    }
    
#ifdef _MSC_VER
    void* os_allocator::Reserve(akm_size Size)
    {
        return VirtualAlloc(NULL, Size, MEM_RESERVE, PAGE_READWRITE);
    }
    
    void* os_allocator::Commit(void* Memory, akm_size Size)
    {
        return VirtualAlloc(Memory, Size, MEM_COMMIT, PAGE_READWRITE);
    }
    
    void  os_allocator::Decommit(void* Memory, akm_size Size)
    {
        VirtualFree(Memory, Size, MEM_DECOMMIT);
    }
    
    void  os_allocator::Release(void* Memory, akm_size Size)
    {
        VirtualFree(Memory, 0, MEM_RELEASE);
    }
    
    void* os_allocator::operator new(akm_size Size)
    {
        printf("Allocated\n");
        void* Result = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
        return Result;
    }
    
    void os_allocator::operator delete(void* Allocator)
    {
        printf("Freed\n");
        HeapFree(GetProcessHeap(), 0, Allocator);
    }
#else
#error Not Implemented
#endif
    
    void* arena_allocator::operator new(akm_size Size, allocator* Allocator)
    {
        return Allocator->Allocate(Size, clear_flag::Clear);
    }
};

#endif