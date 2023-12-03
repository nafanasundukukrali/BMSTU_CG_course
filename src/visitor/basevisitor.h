#ifndef BASEVISITOR_H
#define BASEVISITOR_H

#include <object/composite.h>
#include <object/brep_model/basemodel.h>
#include <object/brep_model/surfaces/basesurface.h>
#include <camera/camera.h>
#include <utils/intensity/intensity.h>

class BaseVisitor
{
public:
//    virtual void visit(Camera &camera) = 0;
    virtual void visit(std::shared_ptr<Composite> models_composite) = 0;
 //   virtual std::shared_ptr<BaseSurface> visit(std::shared_ptr<Object> &model, ParametricLine &line);
};

#endif // BASEVISITOR_H
