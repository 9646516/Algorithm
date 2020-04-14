int Get_min(){
    int n = strlen(s);
    int i = 0,j = 1,k = 0,t;
    while(i < n && j < n && k < n){
        t = s[(i+k)%n] - s[(j+k)%n];
        if(!t) k++;
        else{
            if(t > 0) i += k+1;//i位置大,最大表示法: j += k+1
            else j += k+1;//j位置大,最大表示法: i += k+1
            if(i == j) j++;
            k = 0;
        }
    }
    return i >j ?j :i;
}
