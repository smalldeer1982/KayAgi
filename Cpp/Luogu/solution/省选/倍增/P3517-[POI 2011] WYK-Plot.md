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

## 作者：ycyaw (赞：28)

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

## 作者：__xxy_free_ioi__ (赞：2)

# 题解：P3517 \[POI 2011] WYK-Plot

~~恶心的浮点数！！！~~

## 题意转换

要求我们将序列分为 $\le m$ 段，使最大的每一段的最小圆覆盖的半径最小。

## 解法

先做做[最小圆覆盖](https://www.luogu.com.cn/problem/P1742)吧。（随机增量法可以做到 $O(len)$，$len$ 是点集大小。）

推荐[一个大佬的题解（讲的很细）](https://www.luogu.com.cn/article/1zt84at2)以及随机增量法核心公式证明（源于[讨论](https://www.luogu.com.cn/discuss/436141)）：
![](https://cdn.luogu.com.cn/upload/image_hosting/44pdqpgb.png)

看到最大值最小，我们想到二分最大的每一段的最小圆覆盖的半径。

来看看怎样写 $judge$ 函数。

枚举每一个区间的左端点，然后通过二分来找到最小圆覆盖小于 $mid$ 的右端点，最坏情况下，每一段长度都是一，时间复杂度达到 $O(n^2 \log nr)$（$r$ 是所有点的最小圆覆盖的圆的半径），明显会超时。那怎么办呢？我们发现，会超时很明显是二分区间的问题，每次都二分左端点到 $n$ 的区间，浪费了很多时间，所以，我们想到可以确定一个大致的合法区间，所以我们想到了倍增算法。每次两倍两倍的跳，判断这一段的区间的最小圆覆盖是否 $\le mid$，这样，既可以在短时间内找到二分区间，又可以让二分区间没那么长，我们就可以通过这一题了。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define db double
#define eps 7e-9
// eps一定要注意，不能开太小（1e-12之类），否则精度不够。
#define sq(x) (x) * (x)
#define il inline
#define re register
#define rep(i, s, t) for (re int i = s; i <= t; i++)
#define point8 fixed << setprecision(8)

const int N = 1e5 + 10;

struct node { db x, y; } o, a[N], e[N]; // 圆心和点集
struct Range { int l, r; } range[N];

int n, m, len; // len -> 区间数量
db r; // 半径

il db dis(node a, node b) {return sqrt(sq(a.x - b.x) + sq(a.y - b.y));}
il void get(node a, node b, node c) {
    db a1 = b.x - a.x, a2 = c.x - a.x, b1 = b.y - a.y, b2 = c.y - a.y,
        c1 = (sq(b.x) - sq(a.x) + sq(b.y) - sq(a.y)) / 2,
        c2 = (sq(c.x) - sq(a.x) + sq(c.y) - sq(a.y)) / 2;
    o = {
        (b2 * c1 - b1 * c2) / (b2 * a1 - b1 * a2), 
        (a2 * c1 - a1 * c2) / (a2 * b1 - a1 * b2)
    };
    r = dis(a, o);
}
il void work(int ll, int rr) {
    int tot = 0;
    rep(i, ll, rr) e[++tot] = a[i];
    rep(i, 1, tot) swap(e[i], e[rand() % tot + 1]);
    // 随机增量法
    o = e[1], r = 0;
    rep(i, 2, tot) if (dis(o, e[i]) > r + eps) {
        o = e[i], r = 0;
        rep(j, 1, i - 1) if (dis(o, e[j]) > r + eps) {
            o.x = (e[i].x + e[j].x) / 2, o.y = (e[i].y + e[j].y) / 2;
            r = dis(o, e[j]);
            rep(k, 1, j - 1) if (dis(o, e[k]) > r + eps) get(e[i], e[j], e[k]);
        }
    }
}
bool judge(db x) {
    len = 0;
    for (int i = 1, last; i <= n; i = last + 1) {
        int k;
        for (k = 1; i + (1 << k) - 1 <= n; k++) {
            work(i, i + (1 << k) - 1);
            if (r > x + eps) break;
        }
        k--, last = i;
        // 算出 k 的值（二分范围）
        int L = i + (1 << k) - 1, R = min(i + (1 << k + 1) - 1, n);
        while (L <= R) {
            int mid = (L + R) >> 1;
            work(i, mid);
            if (r < x + eps) L = mid + 1, last = mid;
            else R = mid - 1;
        }
        len++;
        range[len] = {i, last};
        if (len > m) return 0; // 分的段数大于 m 了，退出
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(20031128);
    
    cin >> n >> m;
    rep(i, 1, n) cin >> a[i].x >> a[i].y;

    work(1, n);
    db L = 0, R = r;
//    cout << point8 << r << '\n';
    if (m > 1) {
        for (int i = 1; i <= 50 && R - L > eps; i++) {
            db mid = (L + R) / 2;
            if (judge(mid)) R = mid;
            else L = mid;
        }
    }
    judge(R);

    cout << point8 << R << '\n' << len << '\n';
    rep(i, 1, len) {
        work(range[i].l, range[i].r);
        cout << point8 << o.x << ' ' << o.y << '\n';
    }
    
    return 0;
}
```

~~其实二分还是蛮容易想到的，主要难在最小圆覆盖。~~

---

