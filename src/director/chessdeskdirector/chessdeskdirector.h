#ifndef CHESSDESKDIRECTOR_H
#define CHESSDESKDIRECTOR_H

#include <director/basedirector.h>

class ChessDeskDirector: public BaseDirector
{
public:
    std::shared_ptr<Object> construct(std::shared_ptr<BaseBuilder> builder)
    {
        builder->build();

        return builder->get();
    };
};

#endif // CHESSDESKDIRECTOR_H
