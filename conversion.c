void cti(float* x, float* y){
    float nx = *x + *y;
    float ny = -0.5 * *x + 0.5 * *y;
    *x = nx / 2;
    *y = ny / 2;
}
void itc(float* x, float* y){
    float nx = (0.5 * *x  * 2) - *y  * 2;
    float ny = (0.5 * *x  * 2) + *y  * 2;
    *x = nx;
    *y = ny;
}
