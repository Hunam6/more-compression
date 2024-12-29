#include "more_compression.h"

using namespace godot;

DEFINE_SINGLETON(MoreCompression);

void MoreCompression::_bind_methods() {
    ClassDB::bind_method(D_METHOD("hello_singleton", "label"), &MoreCompression::hello_singleton);
}

void MoreCompression::hello_singleton(Label *label) {
    label->set_text(label->get_text() + "Hello GDExtension Singleton!\n");
}
