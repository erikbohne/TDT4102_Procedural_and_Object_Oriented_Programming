#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <string>

template <typename T, template <typename Stored, typename Alloc = std::allocator<Stored>> typename Collection>
void cleanup(Collection<std::shared_ptr<T>> &collection) {

    auto it = std::remove_if(std::begin(collection), std::end(collection), [] (auto sp) {
        return ! static_cast<bool>(sp);
    });

    collection.erase(it, collection.end());
}

constexpr auto count_invalids = [] (auto &stack) {
    auto &container = stack.get_container();
    auto i = std::count_if(std::begin(container), std::end(container), [] ( auto &x ) {
        return ! static_cast<bool>(x);
    });

    return i;
};

std::string extension_to_lower(const std::string &from);



