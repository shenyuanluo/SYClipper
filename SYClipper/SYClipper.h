//
//  SYClipper.h
//  SYClipperExample
//
//  Created by shenyuanluo on 2018/8/17.
//  Copyright © 2018年 http://blog.shenyuanluo.com/ All rights reserved.
//


/*
 YUV 裁剪（指定区域）
 */

#ifndef SYClipper_h
#define SYClipper_h

#include <iostream>


typedef enum __clipDataType {
    Clip_i420       = 0,        // I420
    Clip_nv12       = 1,        // NV12
    Clip_nv21       = 2,        // NV21
}ClipDataType;


/* 裁剪区域结构体 */
typedef struct __clipRect {
    unsigned int tlX;           // 左上角 X 坐标（Top-Left）
    unsigned int tlY;           // 左上角 Y 坐标（Top-Left）
    unsigned int brX;           // 右下角 X 坐标（Bottom-Right）
    unsigned int brY;           // 右下角 Y 坐标（Bottom-Right）
}ClipRect;


class SYClipper
{
private:
    ClipDataType        m_clipDataType;     // 裁剪数据（格式）类型
    unsigned int        m_frameWidth;       // YUV 数据帧宽度
    unsigned int        m_frameHeight;      // YUV 数据帧高度
    unsigned int        m_frameDataLen;     // YUV 数据长度（= m_frameWidth × m_frameHeight * 1.5）
    unsigned int        m_pixelCount;       // 像素点数（= m_frameWidth × m_frameHeight）
    unsigned char*      m_srcY;             // 源数据·Y 平面
    unsigned char*      m_srcU;             // 源数据·U 平面
    unsigned char*      m_srcV;             // 源数据·V 平面
    unsigned char*      m_dstYuv;           // 裁剪后的 YUV 数据缓冲
    
    void InitParam();

    
    /**
     适配裁剪区域（保证 tlX <= brX；tlY <= brY）

     @param srcRect 源裁剪区域
     @return 适配后的裁剪区域
     */
    ClipRect inline AdaptRect(ClipRect srcRect);
    
public:
    /**
     构造函数
     
     @param width 帧宽度
     @param height 帧高度
     */
    SYClipper(unsigned int width, unsigned int height);
    
    ~SYClipper();
    
    /**
     设置裁剪数据（格式）类型，默认：I420

     @param clipType YUV 数据格式类型
     */
    void setClipDataType(ClipDataType clipType);
    
    /**
     裁剪 YUV

     @param srcYuv 源 YUV 数据
     @param srcLen 源 YUV 数据大小
     @param dstYuv 裁剪后 YUV 数据数组
     @param dstLen 裁剪区域数据大小数组
     @param clipRect 裁剪区域数组，参见‘ClipRect’
     @param clipCount 裁剪区域数量
     @return 裁剪是否成功（-1：裁剪失败； 0：裁剪成功）
     */
    int ClipYuv(unsigned char* srcYuv, unsigned int srcLen, unsigned char* dstYuv[0], unsigned int dstLen[0], ClipRect clipRect[0], unsigned int clipCount);
};

#endif /* SYClipper_h */
