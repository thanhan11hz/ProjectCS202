#pragma once

#include <vector>
#include <functional>
#include <unordered_map>
#include <memory>

#include "State/State.hpp"
#include "State/StateIdentifier.hpp"

class StateStack {
    public:
        explicit StateStack(Context ctx);
        
        template<typename S>
        void registerState(StateIdentifier id);

        void pushState(StateIdentifier id);
        void popState();
        void clearState();
        void update(float dt);
        void draw();
        void handle();
        bool isEmpty();
        std::unique_ptr<State> creatState(StateIdentifier);
        void applyPendingChanges();
        Context mContext;

    private:

        enum class Action {
            PUSH,
            POP,
            CLEAR
        };

        struct PendingChange {
            Action action;
            StateIdentifier id;
            explicit PendingChange(Action action, StateIdentifier id = StateIdentifier::NONE);
        };

        std::vector<std::unique_ptr<State>> mStack;
        std::vector<PendingChange> mPendingList;
        std::unordered_map<StateIdentifier, std::function<std::unique_ptr<State>()>> mFactories;
};

template<typename S>
void StateStack::registerState(StateIdentifier id) {
    mFactories[id] = [this]() {
        return std::make_unique<S>(*this, mContext);
    };
}