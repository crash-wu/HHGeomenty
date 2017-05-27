//
//  HHGeometry.h
//  KaDa
//
//  Created by 吴小星 on 16/8/26.
//  Copyright © 2016年 吴小星. All rights reserved.
//

#ifndef HH_GEOMETRY
#define HH_GEOMETRY

#import <CoreGraphics/CGGeometry.h>
#import <UIKit/UIDevice.h>


#define HH_GEOMETRY_V(padValue, phoneValue) HHScaledVertical((padValue), (phoneValue))

#define HH_GEOMETRY_H(padValue, phoneValue) HHScaledHorizontal((padValue), (phoneValue))

#define HH_SCALE_V  HHStaticScreenGeometry().geoScale.vertical

#define HH_SCALE_H  HHStaticScreenGeometry().geoScale.horizontal

/**
 缩放比例
 */
typedef struct {
    CGFloat vertical;
    CGFloat horizontal;
} HHGeometryScale;


/**
 屏幕尺寸，iPad 以 9.7 寸横屏为基础，iPhone 以 4.0 寸竖屏为基础
 */
typedef struct {
    HHGeometryScale geoScale;
    CGSize size;
    CGRect bounds;
    BOOL isIPad;
} HHScreenGeometry;




/**
 默认的屏幕尺寸
 */
static inline HHScreenGeometry HHStaticScreenGeometry() {
    static HHScreenGeometry screen;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        CGSize size = [UIScreen mainScreen].bounds.size;
        if (size.height < size.width) {
            CGFloat tmp = size.height;
            size.height = size.width;
            size.width = tmp;
        }
        
        screen.isIPad = UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad;
        
        if (screen.isIPad) {
            screen.geoScale.vertical = size.width / 768;
            screen.geoScale.horizontal = size.height / 1024;
            screen.size = CGSizeMake(size.height, size.width);
            screen.bounds = CGRectMake(0, 0, screen.size.width, screen.size.height);
        } else {
            screen.geoScale.vertical = size.height / 568;
            screen.geoScale.horizontal = size.width / 320;
            screen.size = size;
            screen.bounds = CGRectMake(0, 0, size.width, size.height);
        }
    });
    
    return screen;
}


static inline CGFloat HHScaledHorizontal(CGFloat padValue, CGFloat phoneValue) {
    HHScreenGeometry screen = HHStaticScreenGeometry();
    return (screen.isIPad ? padValue : phoneValue) * screen.geoScale.horizontal;
}


static inline CGFloat HHScaledVertical(CGFloat padValue, CGFloat phoneValue) {
    HHScreenGeometry screen = HHStaticScreenGeometry();
    return (screen.isIPad ? padValue : phoneValue) * screen.geoScale.vertical;
}


static inline CGPoint HHPointMake(CGFloat x, CGFloat y) {
    HHGeometryScale geoScale = HHStaticScreenGeometry().geoScale;
    return CGPointMake(x * geoScale.horizontal, y * geoScale.vertical);
}


static inline CGSize HHSizeMake(CGFloat width, CGFloat height) {
    HHGeometryScale geoScale = HHStaticScreenGeometry().geoScale;
    return CGSizeMake(width * geoScale.horizontal, height * geoScale.vertical);
}


static inline CGRect HHRectMake(CGFloat x, CGFloat y, CGFloat width, CGFloat height) {
    HHGeometryScale geoScale = HHStaticScreenGeometry().geoScale;
    return CGRectMake(x * geoScale.horizontal, y * geoScale.vertical, width * geoScale.horizontal, height * geoScale.vertical);
}

#endif
