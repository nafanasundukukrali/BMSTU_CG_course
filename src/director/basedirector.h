#ifndef BASEDIRECTOR_H
#define BASEDIRECTOR_H

#include <builder/basebuilder.h>
#include <memory>
#include <object/object.h>

class BaseDirector
{
public:
    BaseDirector() = default;
    ~BaseDirector() = default;
    virtual std::shared_ptr<Object> construct(std::shared_ptr<BaseBuilder>) = 0;
};

#endif // BASEDIRECTOR_H
