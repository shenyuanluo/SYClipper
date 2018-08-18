//
//  Converter.h
//  SYColorConverterExample
//
//  Created by shenyuanluo on 2018/7/16.
//  Copyright © 2018年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Converter_h
#define Converter_h

// 夹紧函数定义：限制在两者范围之间
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

/* 转换矩阵类型 */
typedef enum __matrixType {
    Matrix_normal           = 0,    // 常规转换标准
    Matrix_bt_601           = 1,    // 标清电视标准：BT.601
    Matrix_bt_709           = 2,    // 高清电视标准：BT.709
}MatrixType;

/* 转换方法类型 */
typedef enum __convertType {
    Convert_normal          = 0,    // 常规方法：浮点运算，精度高
    Convert_bitMult         = 1,    // 通过位移来避免浮点运算，精度低
    Convert_bitAdd          = 2,    // 通过位移来避免乘法运算，精度低
    Convert_table           = 3,    // 查表法（也是位移计算），精度低
}ConvertType;

/* 大小端类型 */
typedef enum __endianType {
    Endian_little           = 0,    // 小端
    Endian_big              = 1,    // 大端
}EndianType;

/* RGB 颜色结构体 */
typedef struct __rgb {
    unsigned char R;    // R 分量
    unsigned char G;    // G 分量
    unsigned char B;    // B 分量
}RGB;

/* YUV 颜色结构体 */
typedef struct __yuv {
    unsigned char Y;    // Y 分量
    unsigned char U;    // U 分量
    unsigned char V;    // V 分量
}YUV;


/* BMP 头结构体：14 字节（注意内存对齐问题） */
typedef struct __bmpHeader
{
    /* 注意，在这个 BMP 头结构体里，bfType 是必需的，
     但是不能通过结构体属性实现，必须现在文件写入，
     因为直接在结构体这里，会引发内存对齐问题，导致 BMP 图像无法正常显示
     （或者通过编译指令：#pragma pack(n)，n = 1,2,4,8,16 来改变内存对齐系数）*/
//    unsigned short  bfType;         // 2 byte -- BMP 文件类型标识（必须为 'BM' 即：0x4D42）
    unsigned int    bfSize;         // 4 byte -- BMP 文件大小（单位：字节）
    unsigned short  bfReserverd1;   // 2 byte -- BMP 文件保留字（必须为 0）
    unsigned short  bfReserverd2;   // 2 byte -- BMP 文件保留字（必须为 0）
    unsigned int    bfbfOffBits;    // 4 byte -- BMP 文件头到数据的偏移量（单位：字节）
}BitMapHeader;

/* BMP 文件信息头结构体：40 字节 */
typedef struct __bmpFileInfo
{
    unsigned int    biSize;             // 4 byte -- 该结构大小（单位：字节）
    unsigned int    biWidth;            // 4 byte --图像帧宽度（单位：像素）
    unsigned int    biHeight;           // 4 byte --图像帧高度（单位：像素）
    unsigned short  biPlanes;           // 2 byte --目标设备的级别（必须为 1）
    unsigned short  biBitcount;         // 2 byte --颜色深度（每个象素所需要的位数）
    unsigned int    biCompression;      // 4 byte --BMP 的压缩类型
    unsigned int    biSizeImage;        // 4 byte --BMP 的大小（单位：字节）
    unsigned int    biXPelsPermeter;    // 4 byte --BMP 水平分辨率，每米像素数
    unsigned int    biYPelsPermeter;    // 4 byte --BMP 垂直分辨率，每米像素数
    unsigned int    biClrUsed;          // 4 byte --BMP 实际使用的颜色表中的颜色数
    unsigned int    biClrImportant;     // 4 byte --BMP 显示过程中重要的颜色数
}BitMapFileInfo;

#endif /* Converter_h */
