int b;
int a1[3][3] = {{1},{2,3},{4}};
int func(int a[3]){
    const int c=3;
    int a4[4]={1,2,3,4};
    a4[3]=6;
    return a[2];
}
int main(){
    int a2[3][3] = {{1},{2,3},{4}};
    a2[3][2]=5;
    // int d = a2[2][3];
    int b = func(a1[2]);
    double a1[3][3] = {{1.2},{2.1,3.3},{4.2}};
    return 0;
}