#include <iostream>
#include <stdint.h>
#include <string.h>

int grayThreshold[] = {0, 32, 64, 192, 255};

int left = 491;
int right = 589; // 491 - 588
int top = 0;
int bottom = 80; // 0 - 79
const size_t bpp = 4;

enum SubPix{
    SP_BLUE,
    SP_GREEN,
    SP_RED,
    SP_ALPHA
};

float gradientCompensation(int grayNow, int index, int* ratioArr){
    float newRatio =  ratioArr[index] + (grayNow - grayThreshold[index]) * 1.0f * 
        (ratioArr[index + 1] - ratioArr[index]) /  (grayThreshold[index + 1] - grayThreshold[index]);
        printf("newRatio=%f\n", newRatio);
    return newRatio;
}

/*
   补偿x, y处subPix分量
*/
float getNewTarget(uint8_t *pixBuf, int x, int y, int subPix, int* ratio){
    int target = pixBuf[(y * (right - left) + x) * bpp + subPix];
    printf("x=%d,y=%d,subPix=%d orignal=%d\n", x + left, bottom - y, subPix, target);
    float com = 0.0f;
    if(target == 255) {
        com = ratio[4] * 1.0 * target / 192;
    } else {
        uint32_t index = 0;
        uint8_t gray = 0;
        while(target >= grayThreshold[index + 1]){
            index++;
            gray = grayThreshold[index];
        }
        printf("index=%d\n", index);
        if (gray == target){
            com = ratio[index] * 1.0 * target / 192;
        } else {
            com = gradientCompensation(target, index, ratio) * target / 192;
        }
    }
    printf("com=%f\n", com);
    target +=  (int)com; 
    if (target < 0){
        target = 0;
    }
    if (target > 255){
        target = 255;
    }
    target = (uint8_t)target;
    memcpy(&pixBuf[(y * (right - left) + x) * bpp + subPix], &target, sizeof(uint8_t));
    printf("new=%d\n", target);
    return target;
}

void pixelCompensateXArray(uint8_t *pixBuf, uint32_t startX, uint32_t stepX, uint32_t endX, 
                                            uint32_t y, int *ratio, int subPix){
    int target;
    startX = startX - left; 
    endX = endX - left;
    y = bottom - y;
    for (uint32_t x = startX; x <= endX; x += stepX){
        target = getNewTarget(pixBuf, x, y, subPix, ratio);
    }
}

void pixelCompensateYArray(uint8_t *pixBuf, uint32_t startY, uint32_t stepY, uint32_t endY, 
                                        uint32_t x, int *ratio, int subPix){
    int target;
    x = x - left; // 493 - 491 
    startY = bottom - startY; // 80 - 2
    endY = bottom - endY;
    printf("startY=%d,endY=%d,stepY=%d\n", bottom - startY, bottom - endY, stepY);
    for (uint32_t y = startY; y >= endY; y -= stepY){
        target = getNewTarget(pixBuf, x, y, subPix, ratio);
    }
}

int main(){
    int width = (right - left);
    int height = (bottom - top);
    printf("chunming width=%d height=%d\n", width, height);

    
    uint8_t* pixelBuf = (uint8_t*) malloc(sizeof(uint8_t) * width * bpp * height);
    memset(pixelBuf, 0 ,sizeof(uint8_t) * width * bpp * height);

    // 注意OPENGL的坐标系的从下到上，读取出来以后，第一行是原来FBO中的最后一行
    uint8_t temp = 128;
    for(int i = 0; i < width * height  * bpp; i++){
        memcpy(&pixelBuf[i], &temp, sizeof(uint8_t));
        // temp++;
        //if (temp > 255){
        //    temp = 0;
        //}
    }

    printf("chunming (%d,%d,%d,%d,%d)\n",pixelBuf[0],pixelBuf[1],pixelBuf[2],pixelBuf[3],pixelBuf[4]);

    // auto-gen code
    int redX512_1_518Y79[] = {0, -120, -80, -40, -40};
    printf("run redX512_1_518Y79\n");
    pixelCompensateXArray(pixelBuf, 512, 1, 518, 79, redX512_1_518Y79, SP_RED);
    return 0;
}