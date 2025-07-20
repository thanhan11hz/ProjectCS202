#include "GUI/Container.hpp"

Container::Container(): mChildren(), mSelectedChildren(-1) {}

Container::~Container() {
    for (auto& child: mChildren) {
        delete child;
        child = nullptr;
    }
}

void Container::pack(Component* component) {
    mChildren.push_back(component);
    if (!hasSelection() && mChildren.back()->isSelectable()) {
        select(mChildren.size() - 1);
    }
}
        
bool Container::isSelectable() {
    return false;
}
        
void Container::handle() {
    for (auto& child: mChildren) {
        child->handle();
    }
}

void Container::draw() {
    std::cout << mChildren.size();
    for (const auto& child: mChildren) {
        child->draw();
    }
}
        
bool Container::hasSelection() {
    return mSelectedChildren >= 0;
}
        
void Container::select(std::size_t index) {
    if (mChildren[index]->isSelectable())
    {
        if (hasSelection()) mChildren[mSelectedChildren]->deselect();
        mChildren[index]->select();
        mSelectedChildren = static_cast<int>(index);
    }
}
        
void Container::selectNext() {
    if (!hasSelection()) return;
    int next = mSelectedChildren;
    do { next = (next + 1) % mChildren.size(); }
    while (!mChildren[next]->isSelectable());
    select(next);
}
        
void Container::selectPrevious() {
    if (!hasSelection()) return;
    int prev = mSelectedChildren;
    do { prev = (prev + mChildren.size() - 1) % mChildren.size(); }
    while (!mChildren[prev]->isSelectable());
    select(prev);
}
// void Container::clear() {
//     for (auto& child: mChildren) {
//         delete child;
//         child = nullptr;
//     }
//     mChildren.clear();
//     mSelectedChildren = -1;
// }