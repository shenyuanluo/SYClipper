//
//  main.cpp
//  SYClipperExample
//
//  Created by shenyuanluo on 2018/8/17.
//  Copyright © 2018年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "SYClipper.h"
#include "YuvToBmp.h"


#define YUV_WIDTH   480              // 视频帧宽
#define YUV_HEIGHT  360              // 视频帧高
#define I420_BUFF_SIZE   259200      // I420 缓冲大小（YUV_WIDTH * YUV_HEIGHT * 1.5）

#define CLIP_COUNT 16    // 裁剪区域个数


#pragma mark -- 测试 I420 转 RGB565
void testClipYuv()
{
    unsigned char *srcYuv = (unsigned char *)malloc(I420_BUFF_SIZE);
    if (NULL == srcYuv)
    {
        printf("Malloc data buffer failure!\n");
        return;
    }
    FILE *fyuv = fopen("XinWenLianBo_480x360_I420.yuv", "rb+");   // 打开 YUV 文件
    if (NULL == fyuv)
    {
        printf("Open file failure!\n");
        free(srcYuv);
        srcYuv = NULL;
        
        return;
    }
    unsigned char* dstYuv[CLIP_COUNT];
    unsigned int   dstLen[CLIP_COUNT];
    ClipRect       clipRect[CLIP_COUNT];    // 平均分割 16 份
    
    // First row
    clipRect[0] = {0 * (YUV_WIDTH>>2), 0, 1 * (YUV_WIDTH>>2), 1 * (YUV_HEIGHT>>2)};
    clipRect[1] = {1 * (YUV_WIDTH>>2), 0, 2 * (YUV_WIDTH>>2), 1 * (YUV_HEIGHT>>2)};
    clipRect[2] = {2 * (YUV_WIDTH>>2), 0, 3 * (YUV_WIDTH>>2), 1 * (YUV_HEIGHT>>2)};
    clipRect[3] = {3 * (YUV_WIDTH>>2), 0, 4 * (YUV_WIDTH>>2), 1 * (YUV_HEIGHT>>2)};
    // Second row
    clipRect[4] = {0 * (YUV_WIDTH>>2), (YUV_HEIGHT>>2), 1 * (YUV_WIDTH>>2), 2 * (YUV_HEIGHT>>2)};
    clipRect[5] = {1 * (YUV_WIDTH>>2), (YUV_HEIGHT>>2), 2 * (YUV_WIDTH>>2), 2 * (YUV_HEIGHT>>2)};
    clipRect[6] = {2 * (YUV_WIDTH>>2), (YUV_HEIGHT>>2), 3 * (YUV_WIDTH>>2), 2 * (YUV_HEIGHT>>2)};
    clipRect[7] = {3 * (YUV_WIDTH>>2), (YUV_HEIGHT>>2), 4 * (YUV_WIDTH>>2), 2 * (YUV_HEIGHT>>2)};
    // third row
    clipRect[8]  = {0 * (YUV_WIDTH>>2), 2 * (YUV_HEIGHT>>2), 1 * (YUV_WIDTH>>2), 3 * (YUV_HEIGHT>>2)};
    clipRect[9]  = {1 * (YUV_WIDTH>>2), 2 * (YUV_HEIGHT>>2), 2 * (YUV_WIDTH>>2), 3 * (YUV_HEIGHT>>2)};
    clipRect[10] = {2 * (YUV_WIDTH>>2), 2 * (YUV_HEIGHT>>2), 3 * (YUV_WIDTH>>2), 3 * (YUV_HEIGHT>>2)};
    clipRect[11] = {3 * (YUV_WIDTH>>2), 2 * (YUV_HEIGHT>>2), 4 * (YUV_WIDTH>>2), 3 * (YUV_HEIGHT>>2)};
    // Fourth row
    clipRect[12] = {0 * (YUV_WIDTH>>2), 3 * (YUV_HEIGHT>>2), 1 * (YUV_WIDTH>>2), 4 * (YUV_HEIGHT>>2)};
    clipRect[13] = {1 * (YUV_WIDTH>>2), 3 * (YUV_HEIGHT>>2), 2 * (YUV_WIDTH>>2), 4 * (YUV_HEIGHT>>2)};
    clipRect[14] = {2 * (YUV_WIDTH>>2), 3 * (YUV_HEIGHT>>2), 3 * (YUV_WIDTH>>2), 4 * (YUV_HEIGHT>>2)};
    clipRect[15] = {3 * (YUV_WIDTH>>2), 3 * (YUV_HEIGHT>>2), 4 * (YUV_WIDTH>>2), 4 * (YUV_HEIGHT>>2)};
    
    SYClipper cliper(YUV_WIDTH, YUV_HEIGHT);
    YuvToBmp converter;
    converter.setConvertType(Convert_table);
    
    unsigned int frameNo = 0;
    char fileName[64];
    
    while (!feof(fyuv))
    {
        memset(srcYuv, 0, I420_BUFF_SIZE);
        fread(srcYuv, 1, I420_BUFF_SIZE, fyuv);  // 每次读取一帧 YUV 数据
        
        if (342 == frameNo)
        {
            cliper.ClipYuv(srcYuv, I420_BUFF_SIZE, dstYuv, dstLen, clipRect, CLIP_COUNT);
            
            sprintf(fileName, "./BMP/Frame_%d.bmp", frameNo);
            converter.I420ToBmp(srcYuv, YUV_WIDTH, YUV_HEIGHT, fileName);
            
            for (int j = 0; j < CLIP_COUNT; j++)
            {
                sprintf(fileName, "./BMP/Frame_%d_Clip_%d.bmp", frameNo, j);
                converter.I420ToBmp(dstYuv[j], clipRect[j].brX - clipRect[j].tlX, clipRect[j].brY - clipRect[j].tlY, fileName);    // 转换成 BMP
            }
            printf("裁剪完成：width-%d, height-%d\n", clipRect[0].brX - clipRect[0].tlX, clipRect[0].brY - clipRect[0].tlY);
            break;
        }
        frameNo++;
    }
    fclose(fyuv);
    free(srcYuv);
    srcYuv = NULL;
}

int main(int argc, const char * argv[])
{
    testClipYuv();
    
    return 0;
}
