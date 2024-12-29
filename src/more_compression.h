#pragma once

#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/object.hpp"
#include "util/define.h"

using namespace godot;

class MoreCompression : public Object
{
    GDCLASS(MoreCompression, Object);
    DECLARE_SINGLETON(MoreCompression);

  protected:
    static void _bind_methods();

  public:
    void hello_singleton(Label *label);
};
