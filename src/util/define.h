#pragma once

#include "godot_cpp/classes/engine.hpp"

#define DECLARE_SINGLETON(name)                                                                                        \
  public:                                                                                                              \
    name();                                                                                                            \
    ~name() override;                                                                                                  \
    static void initialize();                                                                                          \
    static void terminate();                                                                                           \
    static name *get_singleton();

#define DEFINE_SINGLETON(name)                                                                                         \
    static name *variable = nullptr;                                                                                   \
                                                                                                                       \
    name::name()                                                                                                       \
    {                                                                                                                  \
        ERR_FAIL_COND(variable != nullptr);                                                                            \
        variable = this;                                                                                               \
    }                                                                                                                  \
                                                                                                                       \
    name::~name()                                                                                                      \
    {                                                                                                                  \
        ERR_FAIL_COND(variable != this);                                                                               \
        variable = nullptr;                                                                                            \
    }                                                                                                                  \
                                                                                                                       \
    void name::initialize()                                                                                            \
    {                                                                                                                  \
        ClassDB::register_class<name>();                                                                               \
        variable = memnew(name);                                                                                       \
        Engine::get_singleton()->register_singleton(#name, name::get_singleton());                                     \
    }                                                                                                                  \
                                                                                                                       \
    void name::terminate()                                                                                             \
    {                                                                                                                  \
        Engine::get_singleton()->unregister_singleton(#name);                                                          \
        memdelete(variable);                                                                                           \
    }                                                                                                                  \
                                                                                                                       \
    name *name::get_singleton()                                                                                        \
    {                                                                                                                  \
        return variable;                                                                                               \
    }
