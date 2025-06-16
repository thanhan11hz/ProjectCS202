#include "Command/Category.hpp"

Category operator|(Category lhs, Category rhs) {
    return static_cast<Category>(
        static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs)
    );
}

Category operator&(Category lhs, Category rhs) {
    return static_cast<Category>(
        static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs)
    );
}

Category operator~(Category c) {
    return static_cast<Category>(~static_cast<uint32_t>(c));
}

bool any(Category c) {
    return static_cast<uint32_t>(c) != 0;
}