#pragma once

#include <cstdint>

enum class Category : uint32_t
{
    NONE           = 0,
    SCENE          = 1 << 0
};

Category operator|(Category lhs, Category rhs);

Category operator&(Category lhs, Category rhs);

Category operator~(Category c);

bool any(Category c);