# [USACO07JAN] Cow School G

## 题目描述

Bessy is going to school and doing well. She has taken N (1 ≤ N ≤ 5000 -- except one case where 1 ≤ N ≤ 50,000) tests and recorded the scores (Ti points out of Pi points for test i; 0 ≤ Ti ≤ Pi < 40,000; 0 < Pi) as this task's input.

Her teacher will drop the D tests with the lowest percentage (Ti⁄Pi) before calculating Bessie's final grade (which is the sum of the remaining test score points over the sum of the remaining total test points). Bessy is good at math and quickly realizes that this does not benefit her as much as it might.

To prove her point, Bessy wants to find all values of D for which she could have ended up with a higher grade by choosing to drop different tests than the teacher would have. Help her by finding and printing all values of D for which this is possible.

Bessy has noted that, amazingly, she has never scored the same percentage on two different tests.

一个人参加了 $N$ 场考试，第 $i$ 场满分为 $P_i$，其得分为 $T_i$。现在要删去其中 $D$ 次考试的成绩，用剩下的总得分除以剩下的满分之和，作为其最终成绩。问对于哪些 $D$ 而言，删除得分比（即 $\dfrac{T_i}{P_i}$）最小的 $D$ 场得到的最终成绩不是最优的（用其他方法可以得到更高的最终成绩）。

## 样例 #1

### 输入

```
5
1 2
5 9
3 8
4 10
1 3```

### 输出

```
2
1
2```

# 题解

## 作者：javalyc (赞：10)

### [此题博客传送门qwq](https://www.cnblogs.com/LLTYYC/p/10747067.html)
首先需要懂得$01$规划

考虑先将每一科按 $t/p$ 从小到大排序，枚举每一个 $D$（删除的考试数量）

显然一开始的成绩是 $\frac{\sum_{i=d+1}^nt[i]}{\sum_{i=d+1}^{n}p[i]}$，设它为 $st[D]/sp[D]$

然后根据$01$规划的套路考虑把所有的成绩 $t[i]$ 减去 $st[D]/sp[D]*p[i]$

这样做了以后，如果可以使成绩更优，那么说明区间 $[d+1,n]$ 的 $t[i]$ 的最小值小于区间 $[1,d]$ 的 $t[i]$ 的最大值

（就是说我们本来可以选一个区间 $[1,d]$ 的更优的数，但是被删掉了）

然后就有一个 $n^2$ 的算法，枚举 $D$，然后把 $t$ 按套路操作，然后求 $[1,d]$ 区间最大值，$[d+1,n]$ 区间最小值，比较一下就好了

接下来，发现有很多东西是冗余的，没有必要每次都重新算，考虑 $D$ 的变化产生的影响

想想前面枚举完一个 $D$ 了以后要干嘛，求区间 $[d+1,n]$ 的 $t[i]-st[D]/sp[D]*p[i]$ 的最小值，

求区间 $[1,d]$ 的 $t[i]-st[D]/sp[D]*p[i]$ 的最大值。

设 $f[i]$ 表示区间 $[1,d]$，$t$ 变换后的最大值，那么显然 

$f[i]=max(t[j]-st[i]/sp[i]*p[j])\ ,\ j \in [1,d]$，

发现好像可以斜率优化？

$st[i]/sp[i]*p[j]+f[i]=t[j]$，那么 

$k=st[i]/sp[i],x=p[j],b=f[i],y=t[j] $，

原式就变成了 $kx+b=y$ 的形式，可以斜率优化！

同样的设 $g[i]$ 表示区间 $[i+1,n]$，$t$ 变换后的最小值，那么 

$g[i]=min(t[j]-st[i]/sp[i]*p[j]),\ j \in [i+1,n]$，同样可以斜率优化

可以发现，随着 $i$ 的增加 $k=st[i]/sp[i]$ 是不降的，但是显然 $x$ 是不单调的

所以我无脑强行上了两遍 $CDQ$ 求 $f$ 和 $g$，貌似有 $O(n)$ 用 $Graham$ 维护凸包的更优解法？

最后枚举 $D$ ，比较一下 $f[d]$ 和 $g[d]$ 的大小关系就好啦

具体可以看代码来理解
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;
typedef double db;
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
    return x*f;
}
const int N=2e5+7;
const ll INF=1e18;
int n,st[N],sp[N];
db f[N],g[N];
struct nod {//存每一科的数据 
    int p,t;//分母，分子 
    inline bool operator < (const nod &tmp) const {//按分子除分母排序 
        return t*tmp.p<tmp.t*p;//避免除法，用等价的乘法是好习惯 
    }
}d[N];
struct Poi {//斜率优化的点 （或向量） 
    int x,y;
    Poi (int x=0,int y=0) : x(x) , y(y) {}
    inline Poi operator - (const Poi &tmp) const {//点减点就是向量，用向量维护凸包可以避免精度问题，速度也快 
        return Poi(x-tmp.x,y-tmp.y);
    }
}T[N],tmp[N];
int Q[N];//存当前凸包 
inline ll Cross(Poi A,Poi B) { return 1ll*A.x*B.y-1ll*B.x*A.y; }//向量叉积维护凸包 
inline db calc(int i,int j) { return 1.0*T[j].y-1.0*st[i]/sp[i]*T[j].x; }//计算dp值 
inline void merge(int l,int r,int mid)//按x归并排序 
{
    int pl=l,pr=mid+1;
    for(int p=l;p<=r;p++)
    {
        if( pl<=mid && (pr>r||T[pl].x<T[pr].x) ) tmp[p]=T[pl++];
        else tmp[p]=T[pr++];
    }
    for(int p=l;p<=r;p++) T[p]=tmp[p];
}
void CDQ_f(int l,int r)//CDQ求f，求i属于[l,r]的f[i]值  
{
    if(l==r) { f[l]=max(f[l],calc(l,l)); return; }//当前区间只有一个点了，用自己更新自己 
    int mid=l+r>>1,L=1,R=0;
    CDQ_f(l,mid);//先处理左边[l,mid]的所有f 
    //此时左边所有点已经按x排好序了 
    for(int i=l;i<=mid;i++)//维护左边所有点的凸包 
    {
        while( L<R && Cross(T[i]-T[Q[R-1]],T[Q[R]]-T[Q[R-1]])<=0 ) R--; 
        Q[++R]=i;
    }
    for(int i=mid+1;i<=r;i++)//斜率有序，直接用刚刚维护好的凸包更新[mid+1,r]的f 
    {
        while( L<R && calc(i,Q[R-1])>=calc(i,Q[R]) ) R--;
        int j=Q[R]; f[i]=max(f[i],calc(i,j));
    }
    CDQ_f(mid+1,r); merge(l,r,mid);//处理完记得按x排序 
}
void CDQ_g(int l,int r)//处理g同理 
{
    if(l==r) return;//注意g[i]的区间不包含i (i<j<=n)
    int mid=l+r>>1,L=1,R=0;
    CDQ_g(mid+1,r);//注意现在是先处理右边的g了 
    for(int i=mid+1;i<=r;i++)//维护右边的凸包 
    {
        while( L<R && Cross(T[i]-T[Q[R-1]],T[Q[R]]-T[Q[R-1]])>=0 ) R--;
        Q[++R]=i;
    }
    for(int i=l;i<=mid;i++)//更新左边 
    {
        while( L<R && calc(i,Q[L])>=calc(i,Q[L+1]) ) L++;
        int j=Q[L]; g[i]=min(g[i],calc(i,j));
    }
    CDQ_g(l,mid); merge(l,r,mid);//同样记得merge 
}
vector <int> ans;//维护答案 
int main()
{
    n=read();
    for(int i=1;i<=n;i++) d[i].t=read(),d[i].p=read();
    sort(d+1,d+n+1);//先按t/p排序 
    for(int i=n-1;i;i--) { st[i]=st[i+1]+d[i+1].t; sp[i]=sp[i+1]+d[i+1].p; }//求出st,sp 
    for(int i=1;i<=n;i++)
    {
        T[i]=Poi(d[i].p,d[i].t);//初始化点 
        f[i]=-INF; g[i]=INF;//注意初始值 
    }
    //斜率有序
    CDQ_f(1,n);
    for(int i=1;i<=n;i++) T[i]=Poi(d[i].p,d[i].t);//记得还原回初始值 
    CDQ_g(1,n);
    for(int i=1;i<=n;i++)//枚举d,更新ans 
        if(f[i]>g[i]) ans.push_back(i);
    int len=ans.size();
    printf("%d\n",len);
    for(int i=0;i<len;i++) printf("%d\n",ans[i]);
    return 0;
}

/*
    f[i]=T[j]-st[i]/sp[i]*P[j] j<=i
    st[i]/sp[i]*P[j]+f[i]=T[j] j<=i
    k=st[i]/sp[i],x=P[j],b=f[i],y=T[j]
    max,维护上凸包
    g[i]=T[j]-st[i]/sp[i]*P[j] j>i
    st[i]/sp[i]*P[j]+g[i]=T[j] j>i
    min,维护下凸包
*/
```


---

## 作者：jyz666 (赞：8)

# 题解 P2877 【[USACO07JAN]牛校Cow School】

[传送门](https://www.luogu.com.cn/problem/P2877)

这道题可以用01规划加决策单调性分治来做。

[什么是01规划（转）](https://blog.csdn.net/hzoi_ztx/article/details/54898323)

而决策性分治可以解决（且不限于）一些斜率优化问题。

~~具体证明可以打表。~~

我们用
$ask(l,r,dl,dr)$
表示处理区间
$[l,r]$
时，这段区间的决策点已固定在
$[dl,dr]$
中
设
$mid=(l+r)/2$
，暴力处理
$mid$
的最优决策点
$dm$
再向下分治$ask(l,mid−1,dl,dm)$，
$ask(mid+1,r,dm,dr)$
对于本题，先按
$t[i]/p[i]$
从大到小排序，排序后的默认方案（删掉后D个）即为
取区间
[1,n−D]
，舍去区间
[n−D+1,D]

那么如何求最优解叻？

根据01规划基本思路，我们可以得到设
r=st[i]/sp[i]
（
$st[i],sp[i]$
为排序后
$t,p$
的前缀和）
在
[1,n−D]
中找到A=mint[i]−r∗p[i]
,在[n−D+1,n]
中找到 B=maxt[i]−r*p[i]
如果
$A<B$
，那么交换$A,B$可以使答案更优，即默认方案不是最佳方案
于是就可以分治处理辣
复杂度
$O(nlogn)$

上代码~
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define N 50005
struct data{ll t,p;}a[N];
int n,ans; ll f[N],g[N],st[N],sp[N];
inline bool cmp(data A,data B){return A.t*B.p>A.p*B.t;}
void getf(int l,int r,int dl,int dr){
    int mid=(l+r)>>1,dm;
    f[mid]=1e16;
    for(int i=dl;i<=min(mid,dr);++i){
        ll tt=sp[mid]*a[i].t-st[mid]*a[i].p;
        if(tt<f[mid]) f[mid]=tt,dm=i;
    }
    if(l<mid) getf(l,mid-1,dl,dm);
    if(r>mid) getf(mid+1,r,dm,dr);
}
void getg(int l,int r,int dl,int dr){
    int mid=(l+r)>>1,dm;
    g[mid]=-1e16;
    for(int i=dr;i>=max(mid+1,dl);--i){
        ll tt=sp[mid]*a[i].t-st[mid]*a[i].p;
        if(tt>g[mid]) g[mid]=tt,dm=i;
    }
    if(l<mid) getg(l,mid-1,dl,dm);
    if(r>mid) getg(mid+1,r,dm,dr);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld%lld",&a[i].t,&a[i].p);
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i) st[i]=a[i].t+st[i-1],sp[i]=a[i].p+sp[i-1];
    getf(1,n-1,1,n); getg(1,n-1,1,n);
    for(int i=1;i<n;++i) if(f[i]<g[i]) ++ans;
    printf("%d\n",ans);
    for(int i=n-1;i;--i) if(f[i]<g[i]) printf("%d\n",n-i);
    return 0;
}
```
萌新求赞，QwQ

---

## 作者：一颗赛艇 (赞：6)

好吧，居然没人发题解？？？~~蒟蒻表示很不解~~

# 正式开始！Cow School 分数规划

这个题目难度非常大，首先对于老师的一种方案，应用分数规划的一般做法，求出所有的c=t-rate*p，如果没有选择的c值中的最大值比选择了的c值中的最小值大，那么这个解是可以改进的。

那么问题就转化成了怎么求最小的c和最大的c。

t-rate*p 求这种类型的最值，并且rate是单调的，那么就可以考虑利用斜率优化的那种办法来维护决策点。

考虑两个决策点，得到ti-tj>rate(pi-pj)  但是这个pi pj的大小不能确定，我们知道可以利用斜率优化的问题不仅仅要rate单调，还需要pi 单调 这个时候我们需要利用题目中的条件，题目中保证了t/p单调，根据这个条件，可以推出求两种最值的时候都只有单调的p才是有可能成为决策点的。那么就可以按照斜率优化步骤来解题了。一个是用单调栈维护，另外一个利用单调队列维护。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=5e4+9;
double high[maxn],low[maxn];
long long sumt[maxn],sump[maxn];
struct D
{
    long long t,p;
    bool operator <(const D & xx) const
    {
        return t*xx.p>xx.t*p;
    }
}test[maxn];
int que[maxn];
 
bool chk(int i,int j,int t,int s)
{
    long long a=(test[i].t-test[j].t)*(test[t].p-test[s].p);
    long long b=(test[t].t-test[s].t)*(test[i].p-test[j].p);
    return a>b;
}
 
bool chk2(int i,int j,long long t,long long p)
{
    long long a=(test[i].t-test[j].t)*p;
    long long b=t*(test[i].p-test[j].p);
    return a>b;
}
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;i++)
        scanf("%lld %lld",&test[i].t,&test[i].p);
        sort(test+1,test+1+n);
 
        for(int i=1;i<=n;i++)
        {
            sumt[i]=sumt[i-1]+test[i].t;
            sump[i]=sump[i-1]+test[i].p;
        }
 
        int front=1,end=0;
        for(int i=1;i<=n;i++)
        {
            while(end>=front&&test[i].p>=test[que[end]].p)
            end--;
            while(end>front&&chk(que[end],i,que[end-1],que[end]))
            end--;
            que[++end]=i;
            while(front<end&&chk2(que[front],que[front+1],sumt[i],sump[i])==1)
            front++;
            int u=que[front];
            low[i]=test[u].t-(double)sumt[i]/sump[i]*test[u].p;
        }
        int top=0;
        for(int i=n;i>=1;i--)
        {
            while(top>0&&test[i].p<=test[que[top]].p)
            top--;
            while(top>1&&chk(i,que[top],que[top],que[top-1]))
            top--;
            que[++top]=i;
            while(top>1&&chk2(que[top],que[top-1],sumt[i-1],sump[i-1])==0)
            top--;
            int u=que[top];
            high[i]=test[u].t-(double)sumt[i-1]/sump[i-1]*test[u].p;
        }
        int ans=0;
        for(int i=1;i<n;i++)
        if(high[i+1]>low[i])
        ans++;
        cout<<ans<<endl;
        for(int i=n-1;i>=1;i--)
        if(high[i+1]>low[i])
        printf("%d\n",n-i);
    }
    return 0;
}

```

原文：[haha](https://blog.csdn.net/yrleep/article/details/11540031#)

---

## 作者：_ctz (赞：4)


[传送门](https://www.luogu.com.cn/problem/P2877)

[My blog](https://ctz45562.github.io/2019/12/30/USACO-07JAN-Cow-School/)

试图用$kdt$强上凸包の翻车现场。

以下记$a_i$为$t[i]$，$b_i$为$p[i]$，$S$为去掉得分比前$d$小后的$\sum a_i$，$T$为去掉前$d$小后的$\sum b_i$。

如果存在一种更优的方案，一定可以在前$d$小里选$1$场替换掉已有的$1$场，使得分更大。

即$\dfrac{S-a_i+a_j}{T-b_i+b_j}>\dfrac{S}{T}(j\le d <i)$

化简一波这个式子就成了$Ta_j-Sb_j>Ta_i-Sb_i$

于是选出最大的$Ta_j-Sb_j$和最小的$Ta_i-Sb_i$判断一下即可。

怎么搞呢？

---

第一想法：我们发现这个式子长得很$kdt$（参见[巧克力王国](https://www.luogu.com.cn/problem/P4475)）。

直接上$kdt$瞎搞一搞就行了，计算矩形端点的取值剪枝。**复杂度没有保证，反正$kdt$是暴力**。

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <time.h>

#define maxn 50005

const long long inf = 1e18;

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
#define son(x,y) son[x][y]
#define ls(x) son(x,0)
#define rs(x) son(x,1)
#define up(f,a,b) a[node][c[node]]=f(f(a[ls(node)][c[node]],a[rs(node)][c[node]]),p[node][b])
#define dup(f,a) a[node][c[node]^1]=f(a[ls(node)][c[node]^1],a[rs(node)][c[node]^1])
long long s,t,res;
int ans[maxn],id[maxn],fa[maxn],son[maxn][2],xl[maxn][2],xr[maxn][2],yl[maxn][2],yr[maxn][2],p[maxn][2],root,cnt,D;
bool c[maxn];
struct grade{
	int a,b;
	bool operator < (const grade &x)const{return a*x.b<b*x.a;}
}g[maxn];
struct point{
	int pos[2],id;
	bool operator < (const point &x)const{return pos[D]<x.pos[D];}
}po[maxn];
inline void update(int node){
	up(min,xl,0),up(max,xr,0),up(min,yl,1),up(max,yr,1);
	dup(min,xl),dup(max,xr),dup(min,yl),dup(max,yr);
}
void build(int l,int r,int &node){
	if(l>r)return;
	int mid=l+r>>1;
	node=++cnt,D=rand()&1;
	nth_element(po+l,po+mid,po+r+1);
	memcpy(p[node],po[mid].pos,sizeof p[node]),id[po[mid].id]=node;
	build(l,mid-1,ls(node)),build(mid+1,r,rs(node));
	fa[ls(node)]=fa[rs(node)]=node;
	update(node);
}
inline void toggle(int node){
	c[node]=1;
	while(node)update(node),node=fa[node];
}
inline long long calc_max(int node){return node?t*xr[node][1]-s*yl[node][1]:-inf;}
inline long long calc_min(int node){return node?t*xl[node][0]-s*yr[node][0]:inf;}
void Max(int node){
	if(c[node])res=max(res,t*p[node][0]-s*p[node][1]);
	long long d[2]={calc_max(ls(node)),calc_max(rs(node))};
	int t=d[1]>d[0];
	if(d[t]>res)Max(son(node,t));
	if(d[t^1]>res)Max(son(node,t^1));
}
void Min(int node){
	if(!c[node])res=min(res,t*p[node][0]-s*p[node][1]);
	long long d[2]={calc_min(ls(node)),calc_min(rs(node))};
	int t=d[1]<d[0];
	if(d[t]<res)Min(son(node,t));
	if(d[t^1]<res)Min(son(node,t^1));
}
inline long long ma(){res=-inf,Max(root);return res;}
inline long long mi(){res=inf,Min(root);return res;}
int main(){
	srand(time(0));
	int n=read(),cnt=0;
	for(register int i=1;i<=n;++i)s+=(g[i].a=read()),t+=(g[i].b=read());
	sort(g+1,g+1+n);
	for(register int i=1;i<=n;++i)po[i].id=i,po[i].pos[0]=g[i].a,po[i].pos[1]=g[i].b;
	build(1,n,root);
	for(register int i=1;i<n;++i){
		s-=g[i].a,t-=g[i].b,toggle(id[i]);
		if(ma()>mi())ans[++cnt]=i;
	}
	printf("%d\n",cnt);
	for(register int i=1;i<=cnt;++i)printf("%d\n",ans[i]);
}
```

$kdt$丰硕的战果：

- **复杂度没有保证**：最后一个点跑了$29s$
- **反正$kdt$是暴力**：喜提和暴力一个分

![](https://cdn.jsdelivr.net/gh/ctz45562/cdn@1.0/emojis/else/16.gif)

---

重新考察这个式子$Ta_j-Sb_j>Ta_i-Sb_i$：

令$Ta_i-Sb_i=C$，变形一波又成了$\frac{T}{S}a_i-\frac{C}{S}=b_i$。

把$\frac{T}{S}$看作斜率，$\frac{C}{S}$为截距。目的是最小/最大化$C$。

问题就很斜率优化了。维护若干个点，支持：

- 插入一个点
- 给定一条直线的斜率，使它过一个点，最大/小化截距

显然斜率是单调的。没什么高论，两遍$cdq$分治+单调队列维护凸包解决。

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 50005

const long long inf = 1e18;

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
inline double calc(int x1,int y1,int x2,int y2){if(x1==x2)return 1e18;return double(y2-y1)/(x2-x1);}
int ans[maxn];
long long mi[maxn],ma[maxn];
struct grade{
	int a,b;
	bool operator < (const grade &x)const{return a*x.b<b*x.a;}
}g[maxn];
struct operation{
	bool t;//0 insert  1 ask
	int id;
	long long x,y;//x:T   y:S
}A[maxn<<1],B[maxn<<1];
struct Monoqueue{
	int xx[maxn],yy[maxn],pos[maxn],head,tail;
	void clear(){head=1,tail=0;}
	void push1(int x,int y,int p){
		while(head<tail&&calc(xx[tail],yy[tail],xx[tail-1],yy[tail-1])>calc(xx[tail],yy[tail],x,y))--tail;
		xx[++tail]=x,yy[tail]=y,pos[tail]=p;
	}
	int front1(double k){
		while(head<tail&&calc(xx[head],yy[head],xx[head+1],yy[head+1])<k)++head;
		if(head<=tail)return pos[head];
		return -1;
	}
	void push2(int x,int y,int p){
		while(head<tail&&calc(xx[tail],yy[tail],xx[tail-1],yy[tail-1])<calc(xx[tail],yy[tail],x,y))--tail;
		xx[++tail]=x,yy[tail]=y,pos[tail]=p;
	}
	int front2(double k){
		while(head<tail&&calc(xx[head],yy[head],xx[head+1],yy[head+1])>k)++head;
		return pos[head];
	}
	Monoqueue(){clear();}
}q;
void cdq1(int l,int r){
	if(l==r)return;
	int mid=l+r>>1,pl=l,pr=mid+1,p=l;
	cdq1(l,mid),q.clear();
	for(register int i=l;i<=mid;++i)if(!A[i].t)q.push1(A[i].x,A[i].y,A[i].id);
	for(register int i=mid+1;i<=r;++i){
		if(!A[i].t)continue;
		int j=q.front1((double)A[i].x/A[i].y);
		if(~j)mi[A[i].id]=min(mi[A[i].id],A[i].x*g[j].a-A[i].y*g[j].b);
	}
	cdq1(mid+1,r),q.clear();
	while(pl<=mid&&pr<=r){
		if(A[pl].x>A[pr].x||(A[pl].x==A[pr].y&&A[pl].y<A[pr].y))B[p++]=A[pl++];
		else B[p++]=A[pr++];
	}
	while(pl<=mid)B[p++]=A[pl++];
	while(pr<=r)B[p++]=A[pr++];
	for(register int i=l;i<=r;++i)A[i]=B[i];
}
void cdq2(int l,int r){
	if(l==r)return;
	int mid=l+r>>1,pl=l,pr=mid+1,p=l;
	cdq2(l,mid),q.clear();
	for(register int i=l;i<=mid;++i)if(!A[i].t)q.push2(A[i].x,A[i].y,A[i].id);
	for(register int i=mid+1;i<=r;++i){
		if(!A[i].t)continue;
		int j=q.front2((double)A[i].x/A[i].y);
		if(~j)ma[A[i].id]=max(ma[A[i].id],A[i].x*g[j].a-A[i].y*g[j].b);
	}
	cdq2(mid+1,r),q.clear();
	while(pl<=mid&&pr<=r){
		if(A[pl].x>A[pr].x||(A[pl].x==A[pr].x&&A[pl].y>A[pr].y))B[p++]=A[pl++];
		else B[p++]=A[pr++];
	}
	while(pl<=mid)B[p++]=A[pl++];
	while(pr<=r)B[p++]=A[pr++];
	for(register int i=l;i<=r;++i)A[i]=B[i];
}
int main(){
	memset(mi,0x3f,sizeof mi),memset(ma,~0x3f,sizeof ma);
	long long s=0,t=0;
	int n=read(),cnt=0,len=0;
	for(register int i=1;i<=n;++i)g[i].a=read(),g[i].b=read();
	sort(g+1,g+1+n);
	for(register int i=n;i;--i){
		A[++len]=(operation){1,i,t,s};
		A[++len]=(operation){0,i,g[i].a,g[i].b};
		s+=g[i].a,t+=g[i].b;
	}
	cdq1(1,len);
	len=0;
	for(register int i=1;i<=n;++i){
		s-=g[i].a,t-=g[i].b;
		A[++len]=(operation){0,i,g[i].a,g[i].b};
		A[++len]=(operation){1,i,t,s};
	}
	cdq2(1,len);
	for(register int i=1;i<n;++i)if(ma[i]>mi[i])ans[++cnt]=i;
	printf("%d\n",cnt);
	for(register int i=1;i<=cnt;++i)printf("%d\n",ans[i]);
}
```

---

## 作者：Henry__Chen (赞：3)

显然可以对所有考试排序预处理出每个 $d$ 的原始方案所得分数 $\dfrac{S_d}{T_d}$。

考虑暴力，如果一个 $d$ 合法，则可以找到 $n-d$ 次考试，使得 $\dfrac{\sum a_{p_i}}{\sum b_{p_i}}>\dfrac{S_d}{T_d}$，其中 $p$ 表示一个方案的的下标集合。

问题转化为求 $\max\left\{\dfrac{\sum a_{p_i}}{\sum b_{p_i}}\right\}$，可以用 0/1 分数规划 + 0/1 背包在 $O(n^2\log n)$ 的时间复杂度下解决。

更进一步，如果一个 $d$ 合法，则可以在原始方案中替换一个 $i$ 变为 $j$，其中 $i\le d < j\le n$，使得方案更优，即 $\dfrac{S_d-a_i+a_j}{T_d-a_i+a_j}>\dfrac{S_d}{T_d}$，化简得  $b_iS_d-a_iT_d< b_jS_d-a_jT_d$，设
$$
f(d)=\min\{b_iS_d-a_iT_d\}(1\le i\le d)
$$
$$
g(d)=\max\{b_iS_d-a_iT_d\}(d< i\le n)
$$
则 $d$ 可以作为一个合法方案，当且仅当 $f(d)< g(d)$，可以 $O(n^2)$ 枚举解决。

考虑优化，发现这个式子很像斜率优化。

以 $f(d)$ 为例，原式可化为 $\dfrac{f(d)}{S_d}=\min\left\{b_i-\dfrac{T_d}{S_d}a_i\right\}$。

这里 $b=\dfrac{f(d)}{S_d}, y=b_i, k=\dfrac{T_d}{S_d}, x=a_i$。即 $b=\min\{y-kx\}$，可以维护一个下凸包，以保证决策最优。

与一般的斜率优化不同的是，这题的横坐标 $x$ 并不是递增的，即无法直接通过一般的数据结构（单调队列，单调栈）维护，这里通过 CDQ 分治维护。

在分治时维护凸包，先保证左半部分的横坐标 $x$ 递增（用归并排序保证时间复杂度），计算左半部分的凸包对右半部分的 $f(d)$ 的影响，不断向下递归即可解决问题。

最后，考虑 $k=\dfrac{T_d}{S_d}$ 的单调性。可以先证明 $\dfrac{b_1}{a_1}>\dfrac{b_1+b_2}{a_1+a_2}$（因为我们对考试进行了排序，即保证了 $\dfrac{a_i}{b_i}< \dfrac{a_j}{b_j}(i< j)$），然后用数学归纳法可以得出 $\dfrac{T_d}{S_d}$ 单调递减。根据斜率优化的基本操作，计算 $f$ 时用单调栈维护凸包，计算 $g$ 时用单调栈维护，即可在 $O(n\log n)$ 的时间复杂度下解决问题。

## 参考代码
```cpp
const int MAXN = 100000 + 5;

int n, S[MAXN], T[MAXN], q[MAXN];
long long f[MAXN], g[MAXN];

struct node {
    int a, b;
    bool operator < (const node A) {return 1.0 * a / b < 1.0 * A.a / A.b;}
} p[MAXN];

struct Query {int x, y;} Q[MAXN], tmp[MAXN];

long double slope(int i, int j) {
    if (Q[i].x == Q[j].x) return Q[i].y < Q[j].y ? 1e18 : -1e18;
    return 1.0 * (Q[i].y - Q[j].y) / (Q[i].x - Q[j].x);
}

void solve_f(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1, R = 0;
    solve_f(l, mid);
    for (int i = l; i <= mid; i++) {
        while (R > 1 && slope(q[R - 1], q[R]) > slope(q[R], i)) R--;
        q[++R] = i;
    }
    for (int i = mid + 1; i <= r; i++) {
        while (R > 1 && slope(q[R - 1], q[R]) > 1.0 * T[i] / S[i]) R--;
        f[i] = std::min(f[i], 1ll * Q[q[R]].y * S[i] - 1ll * Q[q[R]].x * T[i]);
    }
    solve_f(mid + 1, r);
    for (int i = l, p1 = l, p2 = mid + 1; i <= r; i++)
        if (p2 > r || (p1 <= mid && Q[p1].x < Q[p2].x)) tmp[i] = Q[p1++];
        else tmp[i] = Q[p2++];
    for (int i = l; i <= r; i++) Q[i] = tmp[i];
}

void solve_g(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1, R = 0, L = 1;
    solve_g(mid + 1, r);
    for (int i = mid + 1; i <= r; i++) {
        while (L < R && slope(q[R - 1], q[R]) < slope(q[R], i)) R--;
        q[++R] = i;
    }
    for (int i = l; i <= mid; i++) {
        while (L < R && slope(q[L], q[L + 1]) > 1.0 * T[i] / S[i]) L++;
        g[i] = std::max(g[i], 1ll * Q[q[L]].y * S[i] - 1ll * Q[q[L]].x * T[i]);
    }
    solve_g(l, mid);
    for (int i = l, p1 = l, p2 = mid + 1; i <= r; i++)
        if (p2 > r || (p1 <= mid && Q[p1].x < Q[p2].x)) tmp[i] = Q[p1++];
        else tmp[i] = Q[p2++];
    for (int i = l; i <= r; i++) Q[i] = tmp[i];
}

std::vector<int> ans;

int main() {
    read(n);
    for (int i = 1; i <= n; i++) read(p[i].a, p[i].b);
    std::sort(p + 1, p + n + 1);
    for (int i = n - 1; i; i--) S[i] = S[i + 1] + p[i + 1].a, T[i] = T[i + 1] + p[i + 1].b;
    for (int i = 1; i <= n; i++) Q[i] = Query{p[i].a, p[i].b}, f[i] = 1ll * p[i].b * S[i] - 1ll * p[i].a * T[i];
    solve_f(1, n);
    memset(g, 0xcf, sizeof(g));
    for (int i = 1; i <= n; i++) Q[i] = Query{p[i].a, p[i].b};
    solve_g(1, n);
    for (int i = 1; i <= n; i++)
        if (f[i] < g[i]) ans.push_back(i);
    write(ans.size(), '\n');
    for (auto res : ans) write(res, '\n');
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

显然可以对所有考试排序预处理出每个 $d$ 的原始方案所得分数 $\frac{S_d}{T_d}$。

考虑暴力，如果一个 $d$ 合法，则可以找到 $n-d$ 次考试，使得 $\frac{\sum a_{p_i}}{\sum b_{p_i}}>\frac{S_d}{T_d}$，其中 $p$ 表示一个方案的的下标集合。

问题转化为求 $\max\{\frac{\sum a_{p_i}}{\sum b_{p_i}}\}$，可以用 $0/1$ 分数规划 + $0/1$ 背包在 $O(n^2 \log n)$ 的时间复杂度下解决。

更进一步，如果一个 $d$ 合法，则可以在原始方案中替换一个 $i$ 变为 $j$，其中 $i \le d \lt j \le n$，使得方案更优，即 $\frac{S_d-a_i+a_j}{T_d-a_i+a_j}>\frac{S_d}{T_d}$，化简得 $b_iS_d-a_iT_d<b_jS_d-a_jT_d$，设
$$
f(d)=\min\{b_iS_d-a_iT_d\}(1 \le i \le d)\\
g(d)=\max\{b_iS_d-a_iT_d\}(d < i \le n)
$$
则 $d$ 可以作为一个合法方案，当且仅当 $f(d)<g(d)$，可以 $O(n^2)$ 枚举解决。

代码：
```cpp
//分治优化
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(int i=l,_=r;i<_;++i)
#define per(i,l,r) for(int i=r-1,_=l;i>=_;--i)
typedef long long ll;
const ll LINF=0x3f3f3f3f3f3f3f3f;
const int N=50100;
 
struct nd{
    ll t,p;
    bool operator < (const nd&b)const{
        return t*b.p<p*b.t;
    }
}a[N];
 
ll st[N],sp[N];
ll f[N],g[N];
int cnt,ans[N];
int n;
void solveMax(int l,int r,int optL,int optR){
    if(l>r)return;
    int j=l+r>>1,u=optL;
    rep(i,optL,min(optR,j)+1){
        ll tmp=sp[j]*a[i].t-st[j]*a[i].p;
        if(tmp>g[j])g[j]=tmp,u=i;
    }
    solveMax(l, j-1, optL, u);
    solveMax(j+1, r, u, optR);
}
void solveMin(int l,int r,int optL,int optR){
    if(l>r)return;
    int j=l+r>>1,u=optL;
    rep(i,max(optL,j+1),optR+1){
        ll tmp=sp[j]*a[i].t-st[j]*a[i].p;
        if(tmp<f[j])f[j]=tmp,u=i;
    }
    solveMin(l, j-1, optL, u);
    solveMin(j+1, r, u, optR);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    rep(i,1,n+1)
        cin>>a[i].t>>a[i].p;
    sort(a+1,a+n+1);
    per(i,1,n+1){
        st[i-1]=st[i]+a[i].t;sp[i-1]=sp[i]+a[i].p;
        f[i]=LINF;g[i]=-LINF;
    }
    solveMax(1,n,1,n);
    solveMin(1,n,1,n);
    rep(i,1,n)
        if(f[i]<g[i])ans[cnt++]=i;
    cout<<cnt<<endl;
    rep(i,0,cnt)cout<<ans[i]<<endl;
    return 0;
}
```

---

