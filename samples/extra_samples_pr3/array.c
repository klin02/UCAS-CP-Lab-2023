int b;
int a1[3][3] = {{1},{2,3},{4}};
int func(int a[3],float e[]){
    const int c=3;
    // float f;
    // f = e[2];
    int a4[4]={1,2,3,4};
    a4[3]=6;
    return a[2];
}
int main(){
    int a2[3][3] = {{1},{2,3},{4}};
    a1[0][0] = 3;
    a2[2][2]=5;
    // int d = a2[2][3];
    float e[4];
    e[2]=1.3f;
    int b;
    b = func(a1[2],e);
    double a1[3][3] = {{1.2},{2.1,3.3},{4.2}};
    return 0;
}