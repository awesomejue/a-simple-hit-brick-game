//
//  VisibleRect.h
//  PingPang
//
//  Created by lanou3g on 14-3-15.
//
//

#ifndef __PingPang__VisibleRect__
#define __PingPang__VisibleRect__

#include "cocos2d.h"

USING_NS_CC;

class VisibleRect {
    
public:
    static CCRect getVisibleRect();
    
    static CCPoint left();
    static CCPoint right();
    static CCPoint top();
    static CCPoint bottom();
    static CCPoint center();
    static CCPoint leftTop();
    static CCPoint rightTop();
    static CCPoint leftBottom();
    static CCPoint rightBottom();
private:
    static void lazyInit();
    static CCRect s_visibleRect;

};

#endif /* defined(__PingPang__VisibleRect__) */
