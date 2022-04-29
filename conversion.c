/**
 * @brief converts input x and y from cartesian to isometic
 * 
 * @param x x coordinate pointer
 * @param y y coordinate pointer
 */
void cti(float* x, float* y){
    float nx = *x + *y;
    float ny = -0.5 * *x + 0.5 * *y;
    *x = nx / 2;
    *y = ny / 2;
}
/**
 * @brief converts input x and y from isometric to cartesian
 * 
 * @param x x coordinate pointer
 * @param y y coordinate pointer
 */
void itc(float* x, float* y){
    float nx = (0.5 * *x  * 2) - *y  * 2;
    float ny = (0.5 * *x  * 2) + *y  * 2;
    *x = nx;
    *y = ny;
}

