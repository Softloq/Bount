#pragma once

#define BOUNT_SINGLETON_CLASS_FIELDS(API, CLASS)\
public:\
    API static CLASS& get();\
\
private:\
    API CLASS() = default;\
    API ~CLASS() = default;\
\
    CLASS(const CLASS&) = delete;\
    CLASS& operator=(const CLASS&) = delete;\
\
    CLASS(CLASS&&) = delete;\
    CLASS& operator=(CLASS&&) = delete;

#define BOUNT_SINGLETON_CLASS_IMPL(CLASS)\
CLASS& CLASS::get()\
{\
    constinit static CLASS instance;\
    return instance;\
}