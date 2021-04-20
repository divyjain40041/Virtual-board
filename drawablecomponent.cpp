#include "drawablecomponent.h"

#include <QDebug>

QString DrawableComponent::getComponentName() const
{
    return componentName;
}

void DrawableComponent::setComponentName(const QString &value)
{
    componentName = value;
}
bool DrawableComponent::getIsSelected() const
{
    return isSelected;
}

void DrawableComponent::setIsSelected(bool value)
{
    isSelected = value;
}

void DrawableComponent::changePosition(int x, int y)
{
    //do nothing
}

void DrawableComponent::resizeComponent(int x, int y)
{
    //do nothing
}

DrawableComponent::DrawableComponent()
{
    
}
QString DrawableComponent::toString()
{
    return "";
}
void DrawableComponent::setSelection(int x,int y)
{
    //do nothing
}
