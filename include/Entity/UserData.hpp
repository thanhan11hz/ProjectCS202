#pragma once

#include "Entity/Listener.hpp"

enum class UserDataType {
    MAPTILE,
    MARIO
};

class UserData {
    public: 
        Listener* mListener;
        UserDataType mType;
};