// clang++ main.cpp -std=c++17 -Wall -Wextra -stdlib=libc++

#include <cstring>
#include <cstdio>
#include <optional>

#include <unistd.h>

void *global_base = nullptr;

struct block_meta {
    size_t size;
    block_meta *next;
    bool free;
};

block_meta *find_free_block(block_meta **last, const size_t size)
{
    block_meta *current = static_cast<block_meta *>(global_base);
    while (current && !(current->free && current->size >= size)) {
        *last   = current;
        current = current->next;
    }
    return current;
}


block_meta *request_space(block_meta *last, const size_t size)
{
    block_meta *block = static_cast<block_meta *>(sbrk(0));
    void *request     = sbrk(size + sizeof(block_meta));
    if (request == (void *) -1) {
        return nullptr;
    }

    if (last) {
        last->next = block;
    }
    block->size = size;
    block->next = nullptr;
    block->free = false;
    return block;
}

std::optional<void *> my_malloc(const size_t size)
{
    if (size == 0) {
        return {};
    }
    block_meta *block;
    if (!global_base) {
        block = request_space(nullptr, size);
        if (!block) {
            return {};
        }
        global_base = block;
    } else {
        block_meta *last = static_cast<block_meta *>(global_base);
        block            = find_free_block(&last, size);
        if (block) {
            block->free = false;
        } else if (block = request_space(last, size); !block) {
            return {};
        }
    }

    return (block + 1);
}

void my_free(void *ptr)
{
    if (ptr) {
        const auto block_ptr = static_cast<block_meta *>(ptr) - 1;
        block_ptr->free      = true;
    }
}

std::optional<void *> my_realloc(void *ptr, size_t size)
{
    if (!ptr) {
        return my_malloc(size);
    }

    block_meta *block_ptr = static_cast<block_meta *>(ptr) - 1;
    if (block_ptr->size >= size) {
        return ptr;
    }

    if (auto new_ptr = my_malloc(size); *new_ptr) {
        memcpy(*new_ptr, ptr, block_ptr->size);
        my_free(ptr);
        return *new_ptr;
    } else {
        return {};
    }
}

std::optional<void *> my_calloc(size_t numElems, size_t elemSize)
{
    size_t size = numElems * elemSize;
    if (auto result = my_malloc(size); *result) {
        memset(*result, 0, size);
        return *result;
    } else {
        return {};
    }
}

int main()
{
    // prevent any allocations on clang by providing buffer to stdout
    char buffer[256];
    setvbuf(stdout, buffer, _IOLBF, sizeof(buffer));

    for (const auto i : { 3, 4, 1, 5, 2 }) {
        const auto p = my_malloc(i * 8);
        if (p) {
            printf("%d: %p\n", i, (void *) *p);
        } else {
            puts("\nAllocation failed!!\n");
        }
        my_free(*p);
    }
}
