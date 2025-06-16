#include "World/SceneNode.hpp"

void SceneNode::attachChild(Ptr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& ptr) {
        return ptr.get() == &node;
    });
    assert(found != mChildren.end());
    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::update(float dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

Category SceneNode::getCategory() {
    return Category::SCENE;
}

void SceneNode::onCommand(const Command& command, float dt) {
    if (any(command.mCategory & getCategory())) {
        command.action(*this, dt);
    }
    for (Ptr& children: mChildren) {
        children->onCommand(command,dt);
    }
}

void SceneNode::draw() {
    drawCurrent();
    drawChildren();
}
        
void SceneNode::drawCurrent() {}
        
void SceneNode::drawChildren() {
    for (const Ptr& children: mChildren) {
        children->draw();
    }
}
        
void SceneNode::updateCurrent(float dt) {}
        
void SceneNode::updateChildren(float dt) {
    for (Ptr& children: mChildren) {
        children->update(dt);
    }
}