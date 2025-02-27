#ifndef __Game__MovingLabelLayer__
#define __Game__MovingLabelLayer__

#include "cocos2d.h"
#include "CocosUnits.h"

class MovingLabelLayer : public Node
{
public:
    static MovingLabelLayer * MovingLabelLayerWith(const char* str,Vec2 pos);
    bool initMovingLabelLayer(const char* str,Vec2 pos);
    MovingLabelLayer();
    ~MovingLabelLayer();
	void onActionDown(Node* obj);
};

#endif
