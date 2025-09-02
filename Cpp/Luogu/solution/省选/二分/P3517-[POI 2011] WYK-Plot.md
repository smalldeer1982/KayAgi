# [POI 2011] WYK-Plot

## 题目描述

**译自 POI 2011 Round 1. E「[Plot](https://szkopul.edu.pl/problemset/problem/mzrTn1kzVBOAwVYn55LUeAai/site/?key=statement)」**

给定 $n$ 个点 $ \left( P_1, \ldots, P_n \right) $，将其分成不多于 $m$ 个连续的段：

$$ \left( P_{k_0 + 1}, \ldots, P_{k_1} \right), \left( P_{k_1 + 1}, \ldots, P_{k_2} \right), \ldots, \left( P_{k_{s - 1}+ 1}, \ldots, P_{k_s} \right), $$

其中 $ 0 = k_0 \lt k_1 \lt k_2 \lt \ldots \lt k_s = n $，且对于 $ i = 1, \ldots, s $，子序列 $ \left( P_{k_{i - 1}+ 1}, \ldots, P_{k_i} \right) $ 用一个新点 $Q_i$ 替代。这时我们说 $ P_{k_i - 1}, \ldots, P_{k_i} $ 这些点被「收缩」到了点 $Q_i$，从而产生一个新的点集 $ Q_1, \ldots, Q_s $。两个点集的相似度定义为 $ P_1, \ldots, P_n $ 这些点与其对应的「收缩」后的点距离的最大值：

$$ \max_{i = 1, \ldots, s} \left( \max_{j = k_{i-1}+1, \ldots, k_i}\left( d\left( P_j, Q_i \right) \right) \right) ,$$

其中 $ d\left( P_j, Q_i \right) $ 表示 $P_j$ 和 $Q_i$ 之间的距离，公式为：

$$ d \left( \left(x_1, y_1 \right), \left( x_2, y_2 \right) \right) = \sqrt{ \left( x_2 - x_1 \right)^2 + \left( y_2 - y_1 \right)^2 } $$

 ![](https://cdn.luogu.com.cn/upload/pic/6975.png) 

上图为一个将 $ (P_1, \ldots, P_7) $ 收缩为 $ ( Q_1, Q_2 ) $ 的例子，其中 $ (P_1, \ldots, P_4) $ 被收缩为 $ Q_1 $，$ (P_5, P_6, P_7) $ 被收缩为 $Q_2$.

给定 $n$ 个点组成的序列，你需要将其「收缩」为最多 $m$ 个点，使得相似度最小。原序列可以任意切割。受限于浮点数的精度限制，只要答案比最优解多出不超过 $ 0.000001$ 即算正确。

## 样例 #1

### 输入

```
7 2
2 0
0 4
4 4
4 2
8 2
11 3
14 2```

### 输出

```
3.00000000
2
2.00000000 1.76393202
11.00000000 1.99998199```

# 题解

## 作者：ycyaw (赞：24)

显然的二分答案。

对于一个二分出的答案$mid$，我们要使分成的每一段中所有点离中心点的距离都小于等于$mid$，当然每一段的点是越多越好。

求**一段点**的最小圆覆盖，用随机增量法可以做到$O(len)$，不会的先去做[最小圆覆盖](https://www.luogu.org/problem/P1742)。

所以难点就是怎么写$check$函数。

以找第一个连续的最长段为例，当然可以一个一个枚举过去找到最远的右端点，但是发现如果第一段就是$[1,n]$的段的话，这样做的复杂度就达到$O(n^2)$。

考虑优化一下，对于一个左端点，可以二分一下右端点，这样看起来复杂度更优一点，但是考虑如果每一段长度都为$1$，那么每次都要二分$log$次，总的是$O(n^2\ log\ n)$，显然也不行。

发现复杂度瓶颈在于每次二分得到的区间长是$O(n)$级的，那么可不可以对于一个左端点，快速的找到右端点的范围呢？我们考虑倍增，设左端点为$l$，我们倍增求出右端点的范围。设倍增得到最大的满足条件的区间长度为$2^k$，那么我们二分的左端点为$i+2^k-1$，右端点为$min(n,i+2^{k+1}-1)$，在这段区间内二分，显然复杂度就正确了。

这题好像很卡精度，随机增量法用不同的随机种子还会$WA$。如果只$WA$一两个点，考虑换个随机种子。

总复杂度$O(n\ log^2\ n)$，但是常数很大所以跑得巨慢。

$Code\ Below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
#define pc putchar
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
const int N=100005;
int n,m,res[N][2],cnt,ci;
double eps=1e-10,R;
struct point{
    double x,y;
}a[N],b[N],O;
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+ch-'0';ch=getchar();}
    return ret*ff;
}
void write(int x){
    if(x<0){x=-x;putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+48);
}
void writeln(int x){write(x),hh;}
point Mid(point A,point B){
    return (point){(A.x+B.x)/2,(A.y+B.y)/2};
}
double dist(point A,point B){
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
void getO(point A,point B,point C){
    double aa,bb,cc,dd,ee,ff;
    aa=A.x-C.x;bb=A.y-C.y;
    cc=B.x-C.x;dd=B.y-C.y;
    ee=A.x*A.x+A.y*A.y-C.x*C.x-C.y*C.y;
    ff=B.x*B.x+B.y*B.y-C.x*C.x-C.y*C.y;
    O.x=(dd*ee-bb*ff)/(2*aa*dd-2*bb*cc);
    O.y=(aa*ff-cc*ee)/(2*aa*dd-2*bb*cc);
    R=dist(O,A);
//    printf("%.5lf %.5lf",O.x,O.y),hh;
//    printf("%.5lf %.5lf %.5lf",dist(O,A),dist(O,B),dist(O,C));
}
void work(int l,int r){//随机增量求最小圆覆盖,O(r-l+1)
    int tot=0;
    for(int i=l;i<=r;i++) b[++tot]=a[i];
    for(int i=1;i<=tot;i++) swap(b[i],b[rand()%tot+1]);
    O=b[1],R=0;
    for(int i=1;i<=tot;i++){
        if(dist(b[i],O)>R+eps){//i不在圆内 
            O=b[i],R=0;
            for(int j=1;j<i;j++){
                if(dist(b[j],O)>R+eps){//j不在圆内
                    O=Mid(b[i],b[j]);
                    R=dist(O,b[i]);
                    for(int k=1;k<j;k++)
                        if(dist(b[k],O)>R+eps)
                            getO(b[i],b[j],b[k]);
                }
            }
        }
    }
}
bool check(double lim){
    cnt=0;
    int ans;
    for(int i=1;i<=n;i=ans+1){
        int k;
        for(k=1;i+(1<<k)-1<=n;k++){//k=0显然可行,从1开始 
            work(i,i+(1<<k)-1);
            if(R>lim+eps) break;
        }
        ans=i;
        int l=i+(1<<(k-1))-1,r=min(n,i+(1<<k)-1);
        while(l<=r){
            int mid=(l+r)>>1;
            work(i,mid);
            if(R<lim+eps) l=mid+1,ans=mid;
            else r=mid-1;
        }
        cnt++;
        res[cnt][0]=i,res[cnt][1]=ans;
        if(cnt>m) return 0;
    }
    return 1;
}
signed main(){
    srand(20031128);
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i].x=read();
        a[i].y=read();
    }
    work(1,n);
    double l=0,r=R;
    if(m>1){
        ci=50;
        while(ci--&&r-l>eps){
            double mid=(l+r)/2;
            if(check(mid)) r=mid;
            else l=mid;
        }
    }
    check(r);
    printf("%.8lf\n",r);
    writeln(cnt);
    for(int i=1;i<=cnt;i++){
        work(res[i][0],res[i][1]);
        printf("%.8lf %.8lf\n",O.x,O.y);
    }
    return 0;
}
```


---

