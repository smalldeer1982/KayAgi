# [AGC019C] Fountain Walk

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc019/tasks/agc019_c

都市ネバーモアには、$ 10^8 $ 本の東西方向の通りと $ 10^8 $ 本の南北方向の通りがあり、どちらにも $ 0 $ から $ 10^8-1 $ の番号が付けられています。隣接する二本の東西方向の通りの間の距離はちょうど $ 100 $ メートルで、隣接する二本の南北方向の通りの間の距離もちょうど $ 100 $ メートルです。

すべての東西方向の通りは、すべての南北方向の通りと交わります。すべての交差点は、交差する南北方向の通りの番号を $ x $、東西方向の通りの番号を $ y $ として組 $ (x,\ y) $ で表されます。

この都市には $ N $ 個の噴水があり、交差点 $ (X_i,\ Y_i) $ に設置されています。 通常の交差点と異なり、これらの交差点には交差点を中心とした半径 $ 10 $ メートルの円が噴水の外周として描かれており、その内部に道路はありません。

下の図に、都市の一角の道路や噴水の光景の例を示します。

 ![1f931bf0c98ec6f07e612b0282cdb094.png](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc019_c/8ed452b1f7546ae320f6bcf912b66ca869baab8b.png)

市長たちは、同じ通りを歩いている間に噴水を二回以上見たくありません。ですから、どの東西方向の通りにも噴水は一つまでしか設置されていませんし、南北方向の通りについても同様です。

市民が通行できるのは東西、南北方向の通りと噴水の外周です。交差点 $ (x_1,\ y_1) $ から $ (x_2,\ y_2) $ に移動するには、最短で何メートル歩く必要があるでしょうか？

## 说明/提示

### 制約

- $ 0\ \leq\ x_1,\ y_1,\ x_2,\ y_2\ <\ 10^8 $
- $ 1\ \leq\ N\ \leq\ 200,000 $
- $ 0\ \leq\ X_i,\ Y_i\ <\ 10^8 $
- $ i\ \neq\ j $ のとき $ X_i\ \neq\ X_j $
- $ i\ \neq\ j $ のとき $ Y_i\ \neq\ Y_j $
- 交差点 $ (x_1,\ y_1),\ (x_2,\ y_2) $ は異なり、これらの位置に噴水は設置されていない。
- 入力値はすべて整数である。

### Sample Explanation 1

最短経路の一つを下の図に示します。スタート地点は青の点、ゴール地点は紫の点、途中経路は赤の線です。 !\[c49e52b9b79003f61b8a6efa5dad8ba3.png\](https://img.atcoder.jp/agc019/c49e52b9b79003f61b8a6efa5dad8ba3.png)

### Sample Explanation 2

!\[f9090ab734c89424c413f3b583376990.png\](https://img.atcoder.jp/agc019/f9090ab734c89424c413f3b583376990.png)

### Sample Explanation 3

!\[4b76416161f27cad20333a9ac636e00f.png\](https://img.atcoder.jp/agc019/4b76416161f27cad20333a9ac636e00f.png)

## 样例 #1

### 输入

```
1 1 6 5
3
3 2
5 3
2 4```

### 输出

```
891.415926535897938```

## 样例 #2

### 输入

```
3 5 6 4
3
3 2
5 3
2 4```

### 输出

```
400.000000000000000```

## 样例 #3

### 输入

```
4 2 2 2
3
3 2
5 3
2 4```

### 输出

```
211.415926535897938```

# 题解

## 作者：Ebola (赞：7)

先通过镜像翻转使得目标点在出发点的右上方，这样能简化问题

每行每列都只会有一个转盘，这是一个重要条件

想象一下我们的路径，就是不断往右上方走，遇到转盘就绕1/4周转弯，可以把原来转弯的20优化成5π，我们希望在路径上遇到尽可能多的转盘。

于是这就可以建立LIS模型。取出(x1,y1)到(x2,y2)区域内的转盘，以横坐标为下标，纵坐标为值，跑一遍LIS，得到的答案就是我们路径上能经过的最多圆盘数量

但这样会有一些小问题。比如说当每一行都经过一个转盘时，最顶上那一行的转盘必然要绕1/2周。因此需要加一个特判，若每一行都经过一个圆盘，或每一列都经过一个圆盘，则答案加上1/4圆周的长度

```cpp
#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

typedef pair<int,int> pii;
const double pi=acos(-1);
const int N=200010;
const int MX=1e8+5;
int x1,yy1,x2,yy2,n,tot=0,lis;
int g[N],idx[N],a[N],f[N],gx[N],ax[N];
pii pnt[N];
bool deled[N];

int LIS()
{
    int res=0;
    memset(g,0x7f,sizeof(g));
    for(int i=1;i<=tot;i++)
    {
        auto it=lower_bound(g+1,g+1+n,a[i]);
        if(*it==0x7f7f7f7f) res++;
        *it=a[i];
    }
    return res;
}

int main()
{
    x1=read();yy1=read();x2=read();yy2=read();n=read();
    for(int i=1;i<=n;i++) pnt[i].X=read(),pnt[i].Y=read();
    if(x2<x1||yy2<yy1)
    {
        if(x1<=x2) goto swap2;
        x1=MX-x1;x2=MX-x2;
        for(int i=1;i<=n;i++) pnt[i].X=MX-pnt[i].X;
        if(yy1<=yy2) goto work;
        swap2: yy1=MX-yy1;yy2=MX-yy2;
        for(int i=1;i<=n;i++) pnt[i].Y=MX-pnt[i].Y;
    }
    work: sort(pnt+1,pnt+1+n);
    for(int i=1;i<=n;i++)
        if(pnt[i].X>=x1&&pnt[i].X<=x2&&pnt[i].Y>=yy1&&pnt[i].Y<=yy2) a[++tot]=pnt[i].Y;
    double ans=100.0*(x2-x1+yy2-yy1)+(pi*5-20)*(lis=LIS());
    if(lis==min(x2-x1,yy2-yy1)+1) ans+=pi*5;
    output: printf("%.12lf\n",ans);
    return 0;
}
```



---

## 作者：myee (赞：4)

### 前言

一种复杂并且需要大分类讨论，但是没有大思维量的做法。~~我会说我调了一天吗。~~

### 思路

首先容易发现只用考虑在起点终点构成矩形中的喷泉，不妨起点在左下方，终点在右上方。

于是我们考虑，对正常的路径，我们只可能向右、向上走。

我们把这部分贡献算出来，然后每个喷泉处有一个附加的贡献。

考虑如何计算这部分附加的贡献。

考虑每个喷泉必然从一个 **左插头** 或者 **下插头** 进入，必然从一个 **上插头** 或者 **右插头** 离开。

我们发现，假设已知从左插头、下插头的最小权值，则可以知道从右插头、上插头出去的最小权值。

我们只用知道哪些节点可以更新到当前点。

我们称两个节点 $(x_1,y_1)(x_2,y_2)$ 构成 $(x_1,y_1)\rightarrow(x_2,y_2)$ 的 **偏序**，当且仅当 $x_1<x_2\land y_1<y_2$。

一个节点的右插头可以更新到当前节点的下插头，当且仅当其往当前点构成偏序。

一个节点的上插头可以更新到当前节点的下插头，当且仅当其往当前点构成偏序，且 **两点之间至少存在一行满足不存在能同时与两节点之间所有节点构成偏序的点**。（正确性证明：如果存在空行那么显然，如果不存在则可以从两个不构成偏序的节点间穿过去；除此之外，总是不可行）容易发现这样的节点的 $y$ 一定小于一个定值，可以用并查集找出。

剩下两类贡献同理。

和起点、终点的连边贡献可以类似地分类讨论。

整个过程于是即可离散化，扫描线，并用 BIT 维护前缀 $\min$，从而进行 dp。

总复杂度为 $O(n\log n)$。

### Code

注意，为了避免离散化丢失“空行”的信息，我们要在离散化数组中手动加入空行。

由于细节很多，放出核心代码，有较为详细的注释。

（读入并校准的代码由于不是核心，直接省略了）

```cpp
namespace BIT1{ // 单点取 min，前缀求 min 的 BIT
    dbl A[500005];voi clear(){for(auto&s:A)s=1e18;} // 初始化为 inf
    voi chg(uint p,dbl v){p++;while(p<=500000)_min(A[p],v),p+=lowbit(p);} // 把 p 处向 v 取 min，注意是 0 标号
    dbl find(uint r){ // 查询 [0,r) 最小值
        dbl ans=1e18;while(r)_min(ans,A[r]),r-=lowbit(r);
        return ans;
    }
}
namespace BIT2{ // 同上
    dbl A[500005];voi clear(){for(auto&s:A)s=1e18;}
    voi chg(uint p,dbl v){p++;while(p<=500000)_min(A[p],v),p+=lowbit(p);}
    dbl find(uint r){
        dbl ans=1e18;while(r)_min(ans,A[r]),r-=lowbit(r);
        return ans;
    }
}
const dbl Pi=acos(-1); // 注意需要 math 库
int main()
{
    uint n,x,y;
    std::vector<std::pair<uint,uint> >P;
    // ??? ... ...
    // 读入并校准成起点 (0,0)，终点 (x,y) 的过程，把矩形内节点存入 P，该部分代码略。
    if(P.empty()){printf("%.15lf\n",100.*(x+y));return 0;} // 判掉没点的情况
    if(!x||!y){printf("%.15lf\n",100.*(x+y)+10*Pi-20);return 0;} // 判掉路径是线段的情况
    std::vector<uint>X{0,x},Y{0,y};
    for(auto s:P)if(s.first)X.push_back(s.first),X.push_back(s.first-1); // 方便判断是否相邻
    for(auto s:P)if(s.second)Y.push_back(s.second),Y.push_back(s.second-1);
    std::sort(X.begin(),X.end()),std::sort(Y.begin(),Y.end());
    X.erase(std::unique(X.begin(),X.end()),X.end());
    Y.erase(std::unique(Y.begin(),Y.end()),Y.end());
    for(auto&s:P) // 离散化
        s.first=std::lower_bound(X.begin(),X.end(),s.first)-X.begin(),
        s.second=std::lower_bound(Y.begin(),Y.end(),s.second)-Y.begin();
    n=P.size();
    std::sort(P.begin(),P.end()); // 排序，方便后面扫描线
    BIT1::clear(),BIT2::clear();
    static bol GoneX[500005],GoneY[500005]; // 目前还有没有这种 x / y
    static uint FathX[500005],FathY[500005]; // 并查集，找到最远的一个 x / y 方向上的连续偏序对
    static dbl _L[500005],_D[500005];
    static std::vector<uint>V[500005];
    for(uint i=0;i<X.size();i++)FathX[i]=i;
    for(uint i=0;i<Y.size();i++)FathY[i]=i;
    for(uint i=0;i<n;i++){ // 第一轮扫描线，维护出并查集形态，并判断出从原点到目前点左 / 下插头是否可达
        uint u=P[i].first,v=P[i].second;
        GoneX[u]=GoneY[v]=1;
        if(u&&GoneX[u-1]&&P[i-1].second<v)FathX[u]=FathX[u-1];
        if(v&&GoneY[v-1])FathY[v]=FathY[v-1];
        _L[i]=!GoneX[0]||P[0].second>v||FathX[u]?0:1e18;
        _D[i]=!GoneY[0]||FathY[v]?0:1e18;
        V[FathX[u]].push_back(i); // 由于是二维数点，离线 BIT 提前存下询问
    }
    dbl w=(!GoneX[0]&&FathY[Y.size()-1])||(!GoneY[0]&&FathX[X.size()-1])?0:1e18; // 原点是否可以直接到达终点
    for(uint i=0;i<n;i++){ // 第二轮扫描线，计算左 / 下插头最小值，并更新答案
        for(auto s:V[i])_min(_L[s],BIT1::find(P[s].second));
        uint u=P[i].first,v=P[i].second;
        dbl L=std::min({_L[i],BIT2::find(v)}),D=std::min({_D[i],BIT1::find(v),BIT2::find(FathY[v])}); // 左插头、下插头的最小贡献
        dbl R=std::min(L+10*Pi-20,D+5*Pi-20),U=std::min(L+5*Pi-20,D+10*Pi-20); // 用左、下插头更新右、上插头
        BIT1::chg(v,R),BIT2::chg(v,U);
        if(u<FathX[X.size()-1])_min(w,R);
        if(v<FathY[Y.size()-1])_min(w,U);
    }
    printf("%.15lf\n",100.*(x+y)+w);
    return 0;
}
```



---

## 作者：ysl_wf (赞：2)

# 【题解】[AGC019C] Fountain Walk【保姆级】

## 前言

- [Blog食用更佳~](https://www.cnblogs.com/ysl-fengem/articles/18159043)

- 楼中的 [Ebola](https://www.luogu.com.cn/user/20158) 是我的老师，所以可以认为我的题解更加“平民化”，请放心食用！

## 前置题目
[【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)

## 分析问题

### 简化题目

> 给定一个只有第一象限的直角坐标系，每两条横行纵列上，只能有一个“喷泉”，半径为 $10$，坐标系的单位长度为 $100$，给定两个点，求两者之间的最短距离。

### 假设

> 起点在左下，终点在右上。 

### Solve-1 走走看

也就是说我们会不断的往右上方走，遇到喷泉就绕 $1/4$ 周转弯，通过这样，我们可以把原来的转弯的 $20$ 优化成 $5π$。  
但如果绕 $1/2$ 圆周，你一定又会很容易的想到两点之间线段最短！  
因此，我们的策略便是：

> 我们希望在往右上走的过程中，尽可能遇到多的圆盘！

### Solve-2 怎么走

因为我们要一直往右上走，绝对不可以回头或者向下，也就是说，我们希望喷泉可以一直往右上，横纵坐标依次 **上升**！

但是，喷泉的位置是随机的！可是，喷泉仍然有规律可循：喷泉的横坐标从左往右可以依次 **遍历上升**！

我们可以想象这是某个数组的 **下标**，然后喷泉的纵坐标为数组对应的内容，那么解决问题的关键便是 **最长上升子序列**！

### Solve-3 优化呗

#### 保留

保留由起点和终点的横纵坐标包围而成的矩形！（这很好理解）

```cpp
scanf("%lld%lld%lld%lld", &ax, &ay, &bx, &by);
lt minx = min(ax, bx), maxx = max(ax, bx);
lt miny = min(ay, by), maxy = max(ay, by);
scanf("%lld", &n);
while(n--){
    scanf("%lld%lld", &a, &b);
    if(a >= minx && a <= maxx && b >= miny && b <= maxy)
        g.push_back({a, b});
}
```

#### 镜像翻转

上述的内容都基于：起点在左下，终点在右上。如果以此类推，那么你一定会崩溃！

这时，我们只需要通过镜像翻转的技巧！

1. 改变坐标的数据，让起点成为坐标原点！

2. 这时你会很容易的想到不断通过对称，将终点的新坐标变换到第一象限即可，也就是横纵坐标皆为正数！

```cpp
//以起点a为坐标原点(镜像翻转时我只需要让所有的点在第一象限（也就是说横纵坐标都为正数）。
void chg(){
    bx = bx - ax > 0 ? bx - ax : ax - bx;
    by = by - ay > 0 ? by - ay : ay - by;
    for(T v : g){
        v.x = v.x - ax > 0 ? v.x - ax : ax - v.x;
        v.y = v.y - ay > 0 ? v.y - ay : ay - v.y;
        as[++num].y = v.y, as[num].x = v.x;
    }
    ax = 0, ay = 0;
}
```

#### 离散化

实话说，不离散化，我真不知道道友要如何完成 LIS，这是非常重要的操作，否则不管是数组大小还是求解，难度和内存上都是说不过去的！

```cpp
for(T v : g) as[++num].y = v.y, as[num].x = v.x;
```

#### 计算

~~找规律的东西不会有人要暴力模拟吧。~~ 其实只要找到要经过几个喷泉就可以！

到时这里有一个大问题：

> 若每一行都经过一个圆盘，或每一列都经过一个圆盘，则答案加上1/4圆周的长度！（应该好理解）

```cpp
z = LIS();//求最多经过几个
ans = (bx - ax + by - ay) * dl;
ans = ans - z * r * 2;
ans = ans + (double)z * (double)5 * pi;
if(z == by - ay + 1 || z == bx - ax + 1) 
    ans = ans + (double)5 * pi;
```

### 提醒

- 半径的大小为 $10$！！！
- 我们只需要 $11$ 位的精度！！！

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 2e5 + 10, dl = 100, r = 10;
const long double pi = 3.141592653589793;
lt ax, ay, bx, by, a, b, z;
long double ans;

lt n, num;
struct T{
    lt x, y;
};
vector<T> g;

T as[N];
lt d[N], L;

bool cmp(T a, T b){
    return a.x < b.x;
}

void scin(){//输入
    scanf("%lld%lld%lld%lld", &ax, &ay, &bx, &by);
    lt minx = min(ax, bx), maxx = max(ax, bx);
    lt miny = min(ay, by), maxy = max(ay, by);
    scanf("%lld", &n);
    while(n--){
        scanf("%lld%lld", &a, &b);
        if(a >= minx && a <= maxx && b >= miny && b <= maxy)
            g.push_back({a, b});
    }
}

void chg(){
    bx = bx - ax > 0 ? bx - ax : ax - bx;
    by = by - ay > 0 ? by - ay : ay - by;
    for(T v : g){
        v.x = v.x - ax > 0 ? v.x - ax : ax - v.x;
        v.y = v.y - ay > 0 ? v.y - ay : ay - v.y;
        as[++num].y = v.y, as[num].x = v.x;
    }
    ax = 0, ay = 0;
}

lt LIS(){
    sort(as+1, as+1+num, cmp);
    for(int i = 1; i <= num; i++){
        if(as[i].y >= d[L]){
            L++;
            d[L] = as[i].y;
        }
        else{
            int l = upper_bound(d+1, d+1+L, as[i].y) - d;
            d[l] = as[i].y;
        }
    }
    return L;
}

void count(){
    ans = (bx - ax + by - ay) * dl;
    ans = ans - z * r * 2;
    ans = ans + (double)z * (double)5 * pi;
    if(z == by - ay + 1 || z == bx - ax + 1) ans = ans + (double)5 * pi;
}

int main(){
    scin();//输入

    chg();
    //以起点a为坐标原点(镜像翻转时我只需要让所有的点在第一象限（也就是说横纵坐标都为正数）。

    z = LIS();//求最多经过几个

    count();//计算~

    printf("%.15Lf", ans);
    return 0;
}
//虽然答案要保留15位小数输出，但是实际只要11位的精度
```

## 后记

- 愿诸君如愿以偿。

---

## 作者：Harp_Skier (赞：1)

# [AGC019C] Fountain Walk

## 题意：

给一个 $0$ 至 $10^8$ 的平面直角坐标系。这样上面每个单位长度对应的是 $100$ 个实际单位长度。
有一些位置有喷泉，喷泉会让原来的网格交点处半径 $10$ 个单位长度以内没有路，但是可以沿着喷泉走。给定起点和终点，问从起点到终点的最短实际距离。

## Sulotion:

读完题，我们发现可以先做做起点或终点行相同或者列相同的情况，这种情况下我们直接走可能会与到一个喷泉，让答案多了 $10 \pi -20$ 个单位长度，但是由于每一行每一列都只有一个喷泉，所以这样走比绕远路一定更优，因为绕远路至少要多走 $200$ 个单位长度。

再想想其他情况并观察样例，我们发现，在每个转角的位置，走喷泉比走直线更优，省去了 $20-5 \pi$ 个单位长度的路程。

这启示我们贪着选，尽量让走的转角处的喷泉变多。有了上面行相同或列相同的结论，我们发现走出起点和终点围成的矩形也是更劣的。所以我们保留这里面的喷泉，然后想一下怎么经过更多的喷泉。

若起点为 $(sx,sy)$，终点为 $(tx,ty)$ 且 $sx \leq tx,sy \leq ty$:

显然可以给这些喷泉按 $x$ 坐标从小到大，$y$ 坐标从小到大排序，然后发现这可以直接 dp ，设 $f_i$ 表示第$i$个喷泉最大是第几个被走到的，那我们就可以从一个 $y_j \leq y_i,j<i$ 的位置转移过来，发现这样是       $O(n^2)$ 的，于是考虑优化这个 dp，直接上线段树，那我们就从 $[1,y_i]$ 这一段取 $max$ 转移过来，也就是线段树维护好区间 $max$，直接查就好。

然后可以直接算答案了，答案就是 $|sx-tx|+|sy-ty|-f_{max} \times (20-5 \pi)$。

交上去发现 WA 了。通过 dropbox 我们发现自己的答案少了一个 $5 \pi$，想了一下发现如果起点和终点之间的每列或者每行都有喷泉被选了，也就是 $f_{max}= \min (|sx-tx|,|sy-ty|)$，那么最后一个喷泉会走 $10 \pi$ 的路程，这个就多走了 $10 \pi -20$ 的路程，也就是又多走了 $5 \pi$，所以特判一下这种情况加上 $5 \pi$ 即可。

tips :

1.我们钦定 $sx \leq tx$，这是容易做到的，然后对于 $sy \geq ty$ 的情况我们只用改变 $y$ 坐标的排序顺序即可。做法是一样的。

2.用线段树之前要离散化。
```
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
ll sx,sy,tx,ty;
const int N=2e6+2;
int n;
struct node {
	ll x,y;
}a[N],b[N];
unordered_map<ll,ld>mp;
const ld pi=acos(-1.0);
ll lsh[N];
struct sgt{
	int t[N];
	void upd(int v,int l,int r,int p,int k){
		if(l==r){
			t[v]=max(t[v],k);
			return ;
		}
		int mid=l+r>>1;
		if(p<=mid)upd(v<<1,l,mid,p,k);
		else upd(v<<1|1,mid+1,r,p,k);
		t[v]=max(t[v<<1],t[v<<1|1]);
	}
	int ask(int v,int l,int r,int L,int R){
		if(l>=L&&r<=R)return t[v];
		int mid=l+r>>1;
		if(R<=mid)return ask(v<<1,l,mid,L,R);
		else if(L>mid)return ask(v<<1|1,mid+1,r,L,R);
		return max(ask(v<<1,l,mid,L,mid),ask(v<<1|1,mid+1,r,mid+1,R));
	}
}tr;//线段树，只用单点改和区间查
int f[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>sx>>sy>>tx>>ty>>n;
	for(int i=1;i<=n;++i)cin>>a[i].x>>a[i].y;
	sort(a+1,a+1+n,[](node A,node B){return A.x==B.x?A.y<B.y:A.x<B.x;});
	if(sx>tx)swap(sx,tx),swap(sy,ty);
	if(sy>ty){
		int cnt=0;
		for(int i=1;i<=n;++i)if(a[i].x>=sx&&a[i].x<=tx&&a[i].y>=ty&&a[i].y<=sy)b[++cnt]=a[i];
		int tot=0;
		for(int i=1;i<=cnt;++i)lsh[++tot]=b[i].x;//离散化
		sort(lsh+1,lsh+1+tot);
		tot=unique(lsh+1,lsh+1+tot)-lsh-1;
		for(int i=1;i<=cnt;++i)b[i].x=lower_bound(lsh+1,lsh+1+tot,b[i].x)-lsh;
		tot=0;
		for(int i=1;i<=cnt;++i)lsh[++tot]=b[i].y;
		sort(lsh+1,lsh+1+tot);
		tot=unique(lsh+1,lsh+1+tot)-lsh-1;
		for(int i=1;i<=cnt;++i)b[i].y=lower_bound(lsh+1,lsh+1+tot,b[i].y)-lsh;
		sort(b+1,b+1+tot,[](node A,node B){return A.x==B.x?A.y>B.y:A.x>B.x;});
		int ans=0;
		for(int i=1;i<=cnt;++i){
			f[i]=tr.ask(1,1,tot,1,b[i].y)+1;
			tr.upd(1,1,tot,b[i].y,f[i]);//线段树维护一下max
			ans=max(ans,f[i]); 
		}
		ld per=20.0-5.0*pi;
		ld sum=per*ans;
		cout<<fixed<<setprecision(15)<<abs(tx-sx)*100+abs(ty-sy)*100-sum+(ans==abs(sx-tx)+1||ans==abs(sy-ty)+1)*5*pi<<'\n';
		return 0;
	}
	else {
		int cnt=0;
		for(int i=1;i<=n;++i)if(a[i].x>=sx&&a[i].x<=tx&&a[i].y>=sy&&a[i].y<=ty)b[++cnt]=a[i];
		int tot=0;
		for(int i=1;i<=cnt;++i)lsh[++tot]=b[i].x;
		sort(lsh+1,lsh+1+tot);
		tot=unique(lsh+1,lsh+1+tot)-lsh-1;
		for(int i=1;i<=cnt;++i)b[i].x=lower_bound(lsh+1,lsh+1+tot,b[i].x)-lsh;//排序的依据和上面不一样
		tot=0;
		for(int i=1;i<=cnt;++i)lsh[++tot]=b[i].y;
		sort(lsh+1,lsh+1+tot);
		tot=unique(lsh+1,lsh+1+tot)-lsh-1;
		for(int i=1;i<=cnt;++i)b[i].y=lower_bound(lsh+1,lsh+1+tot,b[i].y)-lsh;
		int ans=0;
		sort(b+1,b+1+cnt,[](node A,node B){return A.x==B.x?A.y<B.y:A.x<B.x;});
		for(int i=1;i<=cnt;++i){
			f[i]=tr.ask(1,1,tot,1,b[i].y)+1;
			tr.upd(1,1,tot,b[i].y,f[i]);
			ans=max(ans,f[i]);
		}
		ld per=20.0-5.0*pi;
		ld sum=per*ans;
		cout<<fixed<<setprecision(15)<<abs(tx-sx)*100+abs(ty-sy)*100-sum+(ans==abs(sx-tx)+1||ans==abs(sy-ty)+1)*5*pi<<'\n';
	}
	return 0;
}
```

---

## 作者：红黑树 (赞：0)

[可能更好的阅读体验](https://rbtr.ee/agc-019-c)

## [题意](https://atcoder.jp/contests/agc019/tasks/agc019_c)
在一张网格图上，每两个整点相距 $100$ 米，你要从 $\left(x_1, y_1\right)$ 走到 $\left(x_2, y_2\right)$，正常来说你只能沿着位于整数位置的线走，但是你发现，这里有 $n$ 个喷泉，每个喷泉是一个半径为 $10$ 米的圆，你可以选择在喷泉的外圈走。求最小可能的距离。

![](https://img.atcoder.jp/agc019/c49e52b9b79003f61b8a6efa5dad8ba3.png)

## 题解
首先你会发现，你绝对不可能走出 以 $\left(x_1, y_1\right)$ 和 $\left(x_2, y_2\right)$ 为定点 的矩形。

然后你会发现，你会尽可能的走到喷泉上去，因为每走上一个喷泉，你的路径长度都可以减少 $20 - 5\pi$。

为了方便描述，我们把 $\left(x_1, y_1\right)$ 移动到原点，把 $\left(x_2, y_2\right)$ 对称到第一象限。

于是你只需要求出在 以 $\left(x_1, y_1\right)$ 和 $\left(x_2, y_2\right)$ 为定点 的矩形中的点的最长上升子序列即可。

最后要注意的一点是，如果每个行或列都有走到喷泉上，那么要多绕一个 $1/4$ 圆。如果你没听懂，看第三个样例。

![](https://img.atcoder.jp/agc019/4b76416161f27cad20333a9ac636e00f.png)

时间复杂度：$\mathcal O\left(n \log n\right)$

## 代码
```cpp
// :/

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  const double c = 20 - 5 * acos(-1);
  tp x1, y1, x2, y2; bin >> x1 >> y1 >> x2 >> y2; x2 -= x1; y2 -= y1;
  tp n = bin;
  vector<PTT> a;
  while (n--) {
    tp x, y; bin >> x >> y;
    x -= x1; y -= y1;
    x *= x2 / abs(x2);
    y *= y2 / abs(y2);
    if (x >= 0 && y >= 0 && x <= abs(x2) && y <= abs(y2)) a.emplace_back(x, y);
  }
  stable_sort(FULL(a));
  vector<tp> s;
  for (tp i = 0; i < a.size(); ++i) {
    if (s.empty() || a[i].second > s.back()) s.push_back(a[i].second);
    else *lower_bound(FULL(s), a[i].second) = a[i].second;
  }
  x2 = abs(x2); y2 = abs(y2);
  double tar = (x2 + y2) * 100;
  if (s.size() == min(x2, y2) + 1) tar += 5 * acos(-1);
  tar -= s.size() * c;
  bin << tar << '\n';
  return 0;
}

void MIST() {
}

// :\ */
```

---

