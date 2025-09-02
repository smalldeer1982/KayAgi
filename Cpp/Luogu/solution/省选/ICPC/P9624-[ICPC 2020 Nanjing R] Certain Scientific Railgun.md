# [ICPC 2020 Nanjing R] Certain Scientific Railgun

## 题目描述

御坂美琴是“学园都市”中排名第三的 Level 5 超能力者，由于她的标志性招式而被昵称为“Railgun”。一天，几个邪恶的机器人入侵了学园都市，御坂计划消灭它们。  

将学园都市视为一个二维平面。总共有 $n$ 个机器人，第 $i$ 个机器人的位置是 $(x_i, y_i)$。御坂将从 $(0, 0)$ 开始移动，她的 Railgun 能力将消灭所有与她共享相同 $x$ 或 $y$ 坐标的机器人。更正式地说，如果御坂现在位于 $(x_m, y_m)$，则所有 $x_i = x_m$ 或 $y_i = y_m$ 的机器人将被消灭。

由于御坂讨厌小数和欧几里得几何，她只会从一个整数点移动到另一个整数点，并且只能水平（平行于 $x$ 轴）或垂直（平行于 $y$ 轴）移动。由于在城市中移动相当累人，御坂请你计算她需要移动的最小距离以消灭所有机器人。

请记住，整数点是指 $x$ 坐标和 $y$ 坐标都是整数的点。

## 说明/提示

### 提示

对于第二个样例测试用例，御坂应该先到 $(0, 1)$，然后到 $(0, 2)$，再到 $(0, -3)$，最后到 $(0, -4)$。

对于第三个样例测试用例，御坂应该先到 $(1, 0)$，然后到 $(1, 1)$，再到 $(3, 1)$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
2
0 1
1 0
4
1 1
-3 -3
4 -4
-2 2
4
1 100
3 100
-100 1
3 -100
```

### 输出

```
0
8
4
```

# 题解

## 作者：__staring__ (赞：6)

由于 $x$ 轴与 $y$ 轴的移动相互独立，所有移动路径总是可以拆分成如下形式：在 $x$ 轴上走了 $[-a,b]$，即往上最远走到了 $b$，往下最远走到了 $-a$，在 $y$ 轴上走了 $[-c,d]$，即往右最远走到了 $d$，往左最远走到了 $-c$，其中 $a,b,c,d \ge 0$。

拆分后，路径的代价为 $a+b+c+d+\min(a,b)+\min(c,d)$，所求为所有代价的 $\min$，那么可以枚举 $\min$ 的取向，此时路径的代价为 $\min(2a+b+2c+d,2a+b+c+2d,a+2b+2c+d,a+2b+c+2d)$。

如果所求式子带有 $2a$，可以将所有 $x_i \le 0$ 的点横坐标翻倍，即 $x_i \leftarrow 2x_i$，$2b,2c,2d$ 同理，将对应方向的点对应坐标翻倍。

现在所求为：找到 $a,b,c,d \ge 0$，使得每个点满足 $x_i \in [-a,b]$ 或 $y_i \in [-c,d]$，且 $a+b+c+d$ 最小。

注意到当 $a,b$ 固定时，$c,d$ 的取值也固定，可以对 $a$ 进行扫描线，用数据结构维护 $c,d$ 关于 $b$ 的答案。

当 $a-1 \rightarrow a$ 时，找到 $x_i=a-1$ 的 $\max y_i$ 和 $\min y_i$，全局对 $c,d$ 进行 `chkmax`，即 $c \leftarrow \max(c,-\min y_i),d \leftarrow \max(d,\max y_i)$，可以用吉司机线段树处理。

但注意到，当 $a=-\inf$ 时，$c,d$ 关于 $b$ 不升，因此 $c,d$ 总是具有单调性，可以在线段树上二分，做区间覆盖

这里的代码实现比较暴力，读者可自行优化

```cpp

#include<bits/stdc++.h>
using namespace std;
namespace staring
{
    typedef long long LL;
    typedef vector<int> VEC;
    typedef pair<int,int> PII;
    typedef pair<LL,LL> PLL;
    #define fir first
    #define sec second

    #define FOR(i,a,b) for(int i=(a),__i=(b);i<=__i;i++)
    #define ROF(i,a,b) for(int i=(a),__i=(b);i>=__i;i--)

    template<typename TYPE>
    TYPE gmax(TYPE &x,const TYPE y){return x<y?x=y:x;}
    template<typename TYPE>
    TYPE gmin(TYPE &x,const TYPE y){return y<x?x=y:x;}

    static constexpr int SIZE=1<<20;
    static char buffin[SIZE]{},*pin1{},*pin2{};
    static char buffout[SIZE]{},*pout{buffout};
    #define GETC() (pin1==pin2&&(pin2=(pin1=buffin)+fread(buffin,1,SIZE,stdin),pin1==pin2)?EOF:*pin1++)
    #define PUTC(c) (pout-buffout==SIZE&&(fwrite(buffout,1,SIZE,stdout),pout=buffout),*pout++=c)
    template<typename TYPE>
    void read(TYPE &x)
    {
        static int signf{0},chin{0};
        x=signf=0,chin=GETC();
        while(chin<'0'||chin>'9')signf|=chin=='-',chin=GETC();
        while(chin>='0'&&chin<='9')x=(x<<3)+(x<<1)+(chin^48),chin=GETC();
        if(signf)x=-x;
    }
    template<typename TYPE>
    void write(TYPE x,char ch=' ',bool f=0)
    {
        static char stack[64]{},top{0};
        !x&&PUTC('0'),x<0&&(x=-x,PUTC('-'));
        while(x)stack[top++]=x%10|48,x/=10;
        while(top)PUTC(stack[--top]);
        if(ch)PUTC(ch);
    }

}using namespace staring;

constexpr int N=1e5+5,M=N<<2;

PII p[N];
LL lsh[N],mny[N],mxy[N];
LL sufc[N],sufd[N];
LL c[M],d[M],b[M];
LL cdb[M],cb[M],db[M];
LL maxc[M],maxd[M];
LL tagc[M],tagd[M];

#define lp (p<<1)
#define rp (p<<1|1)
#define mid (l+r>>1)

void pushup(int p)
{
    c[p]=min(c[lp],c[rp]);
    d[p]=min(d[lp],d[rp]);
    b[p]=min(b[lp],b[rp]);
    cb[p]=min(cb[lp],cb[rp]);
    db[p]=min(db[lp],db[rp]);
    cdb[p]=min(cdb[lp],cdb[rp]);
    maxc[p]=max(maxc[lp],maxc[rp]);
    maxd[p]=max(maxd[lp],maxd[rp]);
}

void cover(int p,LL vc,LL vd)
{
    if(vd)
    {
        d[p]=maxd[p]=tagd[p]=vd;
        db[p]=vd+b[p],cdb[p]=vd+cb[p];
    }
    if(vc)
    {
        c[p]=maxc[p]=tagc[p]=vc;
        cb[p]=vc+b[p],cdb[p]=vc+db[p];
    }
}

void pushdown(int p)
{
    cover(lp,tagc[p],tagd[p]);
    cover(rp,tagc[p],tagd[p]);
    tagc[p]=tagd[p]=0;
}

void build(int p,int l,int r)
{
    tagc[p]=tagd[p]=0;
    if(l==r)
    {
        c[p]=sufc[l],d[p]=sufd[l],b[p]=lsh[l];
        cb[p]=c[p]+b[p],db[p]=d[p]+b[p];
        cdb[p]=c[p]+d[p]+b[p];
        maxc[p]=c[p],maxd[p]=d[p];
    }
    else build(lp,l,mid),build(rp,mid+1,r),pushup(p);
}

void modifyC(LL v,int p,int l,int r)
{
    if(l==r)return cover(p,v>maxc[p]?v:0,0);
    pushdown(p);
    if(v>maxc[rp])cover(rp,v,0),modifyC(v,lp,l,mid);
    else modifyC(v,rp,mid+1,r);
    pushup(p);
}

void modifyD(LL v,int p,int l,int r)
{
    if(l==r)return cover(p,0,v>maxd[p]?v:0);
    pushdown(p);
    if(v>maxd[rp])cover(rp,0,v),modifyD(v,lp,l,mid);
    else modifyD(v,rp,mid+1,r);
    pushup(p);
}

LL calc(int zero,int tot)
{
    sufc[tot]=sufd[tot]=0;
    ROF(b,tot-1,zero)
    {
        sufc[b]=max(sufc[b+1],-mny[b+1]);
        sufd[b]=max(sufd[b+1],mxy[b+1]);
    }
    build(1,zero,tot);

    LL res=1e12;
    FOR(a,1,zero)
    {
        gmin(res,-lsh[a]+cdb[1]);
        modifyC(-mny[a],1,zero,tot);
        modifyD(mxy[a],1,zero,tot);
    }
    return res;
}

void solve()
{
    int n;read(n);
    FOR(i,1,n)read(p[i].fir),read(p[i].sec);
    p[++n]={0,0};

    int tot=0,zero=0;
    sort(p+1,p+n+1);
    FOR(i,1,n)
    {
        if(i==1||p[i].fir!=p[i-1].fir)
        {
            lsh[++tot]=p[i].fir,mny[tot]=p[i].sec;
            if(!p[i].fir)zero=tot;
        }
        mxy[tot]=p[i].sec;
    }

    LL res=1e12;

    FOR(i,1,zero)lsh[i]*=2;
    FOR(i,1,tot)(mny[i]<=0)&&(mny[i]*=2),(mxy[i]<=0)&&(mxy[i]*=2);
    gmin(res,calc(zero,tot));
    FOR(i,1,zero)lsh[i]/=2;
    FOR(i,1,tot)(mny[i]<=0)&&(mny[i]/=2),(mxy[i]<=0)&&(mxy[i]/=2);

    FOR(i,1,zero)lsh[i]*=2;
    FOR(i,1,tot)(mny[i]>=0)&&(mny[i]*=2),(mxy[i]>=0)&&(mxy[i]*=2);
    gmin(res,calc(zero,tot));
    FOR(i,1,zero)lsh[i]/=2;
    FOR(i,1,tot)(mny[i]>=0)&&(mny[i]/=2),(mxy[i]>=0)&&(mxy[i]/=2);
    
    FOR(i,zero,tot)lsh[i]*=2;
    FOR(i,1,tot)(mny[i]<=0)&&(mny[i]*=2),(mxy[i]<=0)&&(mxy[i]*=2);
    gmin(res,calc(zero,tot));
    FOR(i,zero,tot)lsh[i]/=2;
    FOR(i,1,tot)(mny[i]<=0)&&(mny[i]/=2),(mxy[i]<=0)&&(mxy[i]/=2);
    
    FOR(i,zero,tot)lsh[i]*=2;
    FOR(i,1,tot)(mny[i]>=0)&&(mny[i]*=2),(mxy[i]>=0)&&(mxy[i]*=2);
    gmin(res,calc(zero,tot));
    FOR(i,zero,tot)lsh[i]/=2;
    FOR(i,1,tot)(mny[i]>=0)&&(mny[i]/=2),(mxy[i]>=0)&&(mxy[i]/=2);
    
    write(res,'\n');
}

int main()
{
    int T;read(T);
    while(T--)solve();

    fwrite(buffout,1,pout-buffout,stdout);
    return 0;
}

```

---

## 作者：Jerrycyx (赞：3)

## 分析

首先，因为移动是连续的，所以如果从 $(x_1,y)$ 走到 $(x_2,y)$，那么 $x \in [x_1,x_2]$ 的所有点都会被覆盖；$y$ 轴上的移动同理。

由此，设移动路径最左端为 $-a$，最右端为 $b$，最上端为 $c$，最下端为 $-d$，那么一个点是否被覆盖就只与 $a,b,c,d$ 有关，而与具体路径无关。因此，**移动的效果也只与其 $x$ 和 $y$ 轴的范围有关**。

![](https://s21.ax1x.com/2025/05/09/pEO94Ve.png)

接下来考虑怎么样以最小的步数走出这组 $a,b,c,d$。按照如图所示的路径，先左再右、先上再下，即可获得 $2a+b+2c+d$ 的步数。同理，左边先走或右边先走、上边先走或下边先走，**一共可以组合出四种可能的答案**，分别是：

+ $a+2b+c+2d$
+ $a+2b+2c+d$
+ $2a+b+c+2d$
+ $2a+b+2c+d$

以上四种情况计算最小值即为答案。

某些参数中带有 $2$ 的系数，而另外一些没有。如果以第一组（$a+2b+c+2d$）为例，那么此时的子问题即为：求最小的 $a+2b+c+2d$，满足对于任意 $(x_i,y_i)$，$x_i \in [-a,c]$ 或 $y_i \in[-d,c]$。

> 当 $a,b$ 已经确定的时候，我们可以很轻松地求得此时 $c,d$ 的最小值。
>
> $x \in [-a,b]$ 的范围内包含了一些点，而剩下的外侧的点只能通过 $c,d$ 来覆盖。即 $c,d$ 分别是这些外侧点的正或负 $y$ 坐标的最大绝对值：
> 
> $$c=\max_{y_i>0} y_i,\  x_i \notin [-a,b]$$
> 
> $$d=\max_{y_i<0} \lvert y_i \rvert,\  x_i \notin [-a,b]$$
> 
> 于是**当 $a,b$ 的值确定时， $c,d$ 的值也随之确定**。

为方便叙述，**下文把系数全部当作 $1$**，求的是满足条件的最小 $a+b+c+d$ 值。转换成需要的形式仅需计算过程中乘上一个系数即可。

## 扫描线

我们尝试使用**扫描线**解决这个问题。

> 最优的 $a$ 一定是刚好卡在某个点的 $x$ 坐标上，否则可以缩小 $a$ 而不损失覆盖点；最优的 $b,c,d$ 同理，也**一定是卡在某个点上，即恰好覆盖到某个点**的。
>
> 所以我们可以省略掉离散化这一步。

首先在坐标序列中插入两个 $(0,0)$（有妙用，后面说），将所有坐标 $(x_i,y_i)$ 按照 $x$ 从小到大**排序**，找到第一个 $(0,0)$ 的位置，**此位置及以前的 $x$ 坐标即为 $-a$ 的可能取值，之后的 $x$ 即为 $b$ 的可能取值**。

然后我们需要一些**预处理**：设 $lc_i$ 表示 $a$ 管辖的范围刚离开 $x_i$，即 $-a=x_{i+1}$ 时，左边外侧所需的最小 $c$ 值；$ld_i$ 为此时左边外侧所需的最小 $d$ 值，即：

$$lc_i = \max_{y_i>0} y_i,\  x_i < -a$$

$$ld_i = \max_{y_i<0} \lvert y_i \rvert,\  x_i < -a$$

同理，设 $rc_i$ 表示 $b$ 管辖的范围刚离开 $x_i$，即 $b=x_{i-1}$ 时，右边外侧所需的最小 $c$ 值；$rd_i$ 为此时右边外侧所需的最小 $d$ 值，即：

$$rc_i = \max_{y_i>0} y_i,\  x_i > b$$

$$rd_i = \max_{y_i<0} \lvert y_i \rvert,\  x_i > b$$

然后利用扫描线，**将 $a$ 从大到小（左边界从左到右）枚举**，我们需要快速求出：

$$\begin{aligned}
&\min_{-a=x_i,b=x_j} \{ a + b + \max(lc_{i-1},rc_{j+1}) + \max(ld_{i-1}, rd_{j+1})\}\\
=& -x_i + \min\{x_j + \max(lc_{i-1},rc_{j+1}) + \max(ld_{i-1},rd_{j+1})\}
\end{aligned}$$

设 $c^*_j=\max(lc_{i-1},rc_{j+1})$，$d^*_j=\max(ld_{i-1},rd_{j+1})$，那么原式可以简写为：

$$\boxed{-x_i + \min\{x_j + c^*_j + d^*_j\}}$$

~~总算有点数据结构题的样子了。~~

考虑当 $a$ 所代表的左边界右移时会发生什么：之前 $a$ 卡住的点不再可以被横坐标 $[-a,b]$ 覆盖，而这些多出来的点将成为 $c$ 和 $d$ 钉死的下限。

例如：如果 $(-3,2)$ 和 $(-3,-1)$ 不再能被横坐标覆盖，那么覆盖这两个点的任务就不得不交给 $c,d$。那么就相当于所有的 $c^*_j$ 都不得小于 $2$，而 $d^*_j$ 都不得小于 $\lvert -1 \rvert = 1$。

因此，我们需要的数据结构需要支持三种操作：

+ **对于所有 $j$，令 $c^*_j \leftarrow \max(c^*_j, v)$，其中 $v=y_i$；**
+ **对于所有 $j$，令 $d^*_j \leftarrow \max(d^*_j, v)$，其中 $v=\lvert y_i \rvert$；**
+ **对于所有 $j$，求 $\min\{x_j+c^*_j+d^*_j\}$。**

## 数据结构

所需数据结构有区间最大值操作和区间查询操作，看起来就很像吉司机线段树，所以这道题要用**吉司机线段树**~~（什么暴论）~~。

首先我们需要在记录如下信息：

+ `mxc`：区间最大 $c^*_j$ 值（最大值操作用）；
+ `mxd`：区间最大 $d^*_j$ 值（最大值操作用）；
+ `mnbc`：区间最小 $x_j+c^*_j$ 值（更新 `mnbcd` 用）；
+ `mnbd`：区间最小 $x_j+d^*_j$ 值（更新 `mnbcd` 用）；
+ `mnbcd`：区间最小 $x_j+c^*_j+d^*_j$ 值（答案）。

然后建树就是正常建树，`pushup` 也是正常写法。

关键是如何做最大值操作。这里由于 **$c^*_j$ 和 $d^*_j$ 具有非严格单调递减的性质**，所以**最大值操作实际上操作的是从最右侧开始的一段连续区间**。

> $c^*_j$ 和 $d^*_j$ 非严格单调递减的原因：
>
> 当左端点固定时，考虑当右端点左移时，$c$ 和 $d$ 需要囊括的点越来越多，所以 $c,d$ 作为这些点的纵坐标（的绝对值）的最大值，是不降的。
>
> 因此，$c^*_j,d^*_j$ 随 $j$ 的减小而不降，也就是随 $j$ 的增大而不升。即它们是单调非严格单调递减的。

以 $c^*_j$ 为例，最大值操作如图示：

![](https://s21.ax1x.com/2025/05/09/pEOZXqI.png)

 _（上图 $b$ 表示 $x_j$，$c$ 表示 $c^*_j$，$v$ 为最大值操作所用的 $\lvert y_i \rvert$）_ 

我们只需要**用类似线段树二分的查询方式找到这个连续区间的左端点，然后正常执行区间覆盖操作**即可（我的代码中把二分和最大值操作/区间覆盖操作放在一起了）。

以查找和覆盖 $c^*_j$ 为例，代码：

```cpp
void OpMaxC(int v, int p)
{
	if(mxc(p)<=v) //当该区间最大c值都小于v时，整个区间c值都小于v，可以覆盖
	{
		tr[p].cover_c(v); //具体覆盖操作，见下文
		return;
	}
	if(tr[p].is_leaf()) return;
	pushdown(p);
	if(v>mxc(p<<1|1)) OpMaxC(v, p<<1);
	//右子区间的最大c值小于v，那么左子区间可能有c小于v的部分
	//否则，右子区间都无法被目标区间完全覆盖，左子区间更不可能有能被覆盖的部分
	OpMaxC(v, p<<1|1); //无论如何，右子区间都可能有能被覆盖的部分
	pushup(p);
	return;
}
```

_（类似 `mxc(p)` 的写法被 `#define` 为 `tr[p].mxc`，下同）_

对 $d^*_j$ 的查找和覆盖操作同理。

在覆盖的时候，以覆盖 $c^*_j$ 为 $v$ 为例：**更新后该区间内的 $c^*_j$ 全部等于 $v$**。根据这一点，只需要：
+ 将 `mxc` 改成 `v`；
+ 把 `mnbc` 改成 `v+x[l]`（左端点的 `x` 值一定是最小的）；
+ 把 `mnbcd` 改成 `v+mnbd`；
+ 打一个区间覆盖的延迟标记。

这部分代码如下：

```cpp
inline void cover_c(int v)
{
	mxc=v;
	mnbc=v+rb[l]; //rb即为乘过所需系数后的x
	mnbcd=v+mnbd;
	lzyc=v;
	return;
}
```

对 $d^*_j$ 的覆盖操作同理。

至于查询操作，因为整个程序只查询了总区间的 `mnbcd`，所以你甚至不需要专门写一个函数，直接调用根节点的 `mnbcd` 就行。

对于 `pushdown`，也是常规操作，有表示需要区间整体覆盖的延迟标记时，直接对子区间 `cover` 就行。

## 细节

最后说一些细节和警示后人。

### 最开始插入的那两个 $(0,0)$ 有何作用？

以 $x$ 坐标为例。显然，我们上面所做的都是基于所走一定是“先往左/右走到一个点位，再向右/左跨过原点走到另一个点位”。

**这就忽略了一种可能：一开始就往一个方向走而不再回去，另一边的点全部由纵坐标覆盖。**

为了解决这个问题，引入 $(0,0)$ 这样一个点可以提供一种路径：一开始向左/右走到 $0$（相当于啥也没干），然后再向右/左走到某个点位。这种走法和上面忽略的那种可能性实际上是一样的，所以如此便可**将那种可能也纳入考虑而无需多写一堆特判代码**。

至于为何要引入两个 $(0,0)$，这是因为一个作为纵轴左侧点的末尾，一个作为纵轴右侧点的开头。这样可以省去讨论 $0$ 到底作为 $-a$ 的可能取值，还是作为 $b$ 的可能取值的问题。最终结果就是：**可以让往左和往右都能够考虑到“一开始就往另一边走”的可能性**。

### 为什么必须要用线段树二分？

其实你也可以不用线段树二分，只用普通的吉司机线段树处理方法。但是这样的时间复杂度似乎是 $O(n \log^2 n)$ 的，再加上本题扫描线要跑四遍，还只给 $1$ 秒的时间，不用线段树二分大概跑不过去（本人亲测）。

### 其它注意点

这题坑点很多，特别要注意的是：

+ 查询和修改的顺序问题：注意是先查询再将移动的贡献算进线段树（或者你也可以给下标加或减一个 $1$）；
+ 数组清空问题，特别要注意的：
  + 每次要把 `rc[n+1]` 和 `rd[n+1]` 置零，因为线段树初始化时，最右端点要求这两个必须是 $0$（这个问题导致我对拍了一下午，$10^5+$ 数据硬是没拍出来）；
  + 线段树的延迟标记每次建树时都要记得清空；
+ 坐标范围较大，某些地方需要开 `long long`。）。

## 代码

**加上快读后代码大小为 $3.91$KB，总时间 $52$ms，暂居最优解（[评测记录](https://www.luogu.com.cn/record/216481336)）。**

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

namespace IO{
#ifndef JC_LOCAL
const int SIZE=1<<20; char buf[SIZE],*p1=buf,*p2=buf;
#define getchar() ((p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2))?EOF:*p1++)
#endif
template<typename TYPE> void read(TYPE &x)
{
	x=0; bool neg=false; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')neg=true;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^'0');ch=getchar();}
	if(neg){x=-x;} return;
}
template<typename TYPE> void write(TYPE x)
{
	if(!x){putchar('0');return;} if(x<0){putchar('-');x=-x;}
	static int sta[55];int statop=0; while(x){sta[++statop]=x%10;x/=10;}
	while(statop){putchar('0'+sta[statop--]);} return;
}
template<typename TYPE> void write(TYPE x,char ch){write(x);putchar(ch);return;}
} using IO::read; using IO::write;

#define PII pair<int,int>
#define fs first
#define sc second
using LL = long long;

const int N=2e5+5;
const LL INF_LL=1e18;
int n; PII crd[N];

int x0pos;
int rb[N],rc[N],rd[N];

/*========== Segment Tree Beats - Begin ==========*/

struct SegBeats{
	int l,r;
	LL mxc,mxd;
	LL mnbc,mnbd,mnbcd;
	int lzyc,lzyd;
	inline int mid(){return l+r>>1;}
	inline void cover_c(int v)
	{
		mxc=v;
		mnbc=v+rb[l];
		mnbcd=v+mnbd;
		lzyc=v;
		return;
	}
	inline void cover_d(int v)
	{
		mxd=v;
		mnbd=v+rb[l];
		mnbcd=v+mnbc;
		lzyd=v;
		return;
	}
}tr[N<<2];

#define l(p) (tr[p].l)
#define r(p) (tr[p].r)
#define mxc(p) (tr[p].mxc)
#define mxd(p) (tr[p].mxd)
#define mnbc(p) (tr[p].mnbc)
#define mnbd(p) (tr[p].mnbd)
#define mnbcd(p) (tr[p].mnbcd)
#define lzyc(p) (tr[p].lzyc)
#define lzyd(p) (tr[p].lzyd)

inline void pushup(int p)
{
	mxc(p)=max(mxc(p<<1),mxc(p<<1|1));
	mxd(p)=max(mxd(p<<1),mxd(p<<1|1));
	mnbc(p)=min(mnbc(p<<1),mnbc(p<<1|1));
	mnbd(p)=min(mnbd(p<<1),mnbd(p<<1|1));
	mnbcd(p)=min(mnbcd(p<<1),mnbcd(p<<1|1));
	return;
}
inline void pushdown(int p)
{
	if(lzyc(p))
	{
		tr[p<<1].cover_c(lzyc(p));
		tr[p<<1|1].cover_c(lzyc(p));
		lzyc(p)=0;
	}
	if(lzyd(p))
	{
		tr[p<<1].cover_d(lzyd(p));
		tr[p<<1|1].cover_d(lzyd(p));
		lzyd(p)=0;
	}
	return;
}

void Build(int p,int l,int r)
{
	l(p)=l,r(p)=r;
	lzyc(p)=lzyd(p)=0;
	if(l==r)
	{
		mxc(p)=rc[l+1], mxd(p)=rd[l+1];
		mnbc(p)=rb[l]+rc[l+1], mnbd(p)=rb[l]+rd[l+1];
		mnbcd(p)=rb[l]+rc[l+1]+rd[l+1];
		return;
	}
	int mid=tr[p].mid();
	Build(p<<1,l,mid),Build(p<<1|1,mid+1,r);
	pushup(p);
	return;
}

void OpMaxC(int v, int p)
{
	if(mxc(p)<=v)
	{
		tr[p].cover_c(v);
		return;
	}
	else if(l(p)==r(p)) return;
	pushdown(p);
	if(v>mxc(p<<1|1)) OpMaxC(v, p<<1);
	OpMaxC(v, p<<1|1);
	pushup(p);
	return;
}
void OpMaxD(int v, int p)
{
	if(mxd(p)<=v)
	{
		tr[p].cover_d(v);
		return;
	}
	else if(l(p)==r(p)) return;
	pushdown(p);
	if(v>mxd(p<<1|1)) OpMaxD(v, p<<1);
	OpMaxD(v, p<<1|1);
	pushup(p);
	return;
}

#undef l
#undef r
#undef mxc
#undef mxd
#undef mnbc
#undef mnbd
#undef mnbcd
#undef lzyc
#undef lzyd

/*========== Segment Tree Beats - End ==========*/

LL Solve(int ma,int mb,int mc,int md)
{
	rc[n+1]=rd[n+1]=0;
	for(int i=n,trc=0,trd=0;i>x0pos;i--)
	{
		if(crd[i].sc>0) trc=max(trc,crd[i].sc*mc);
		else trd=max(trd,-crd[i].sc*md);
		rb[i]=crd[i].fs*mb,rc[i]=trc,rd[i]=trd;
	}
	Build(1,x0pos+1,n);
	
	LL res=INF_LL;
	for(int i=1,tlc=0,tld=0;i<=x0pos;i++)
	{
		res=min(res, -crd[i].fs*ma + tr[1].mnbcd);
		if(crd[i].sc>0)
		{
			tlc=max(tlc,crd[i].sc*mc);
			OpMaxC(tlc, 1);
		}
		else
		{
			tld=max(tld,-crd[i].sc*md);
			OpMaxD(tld, 1);
		}
	}
	return res;
}

int main()
{
	int T; read(T);
	while(T--)
	{
		read(n);
		for(int i=1;i<=n;i++)
			read(crd[i].fs),read(crd[i].sc);
		crd[++n]={0,0},crd[++n]={0,0};
		sort(crd+1,crd+n+1);
		for(int i=1;i<=n;i++)
			if(crd[i]==(PII){0,0})
			{
				x0pos=i;
				break;
			}
		write(min({
			Solve(1,2,1,2),
			Solve(1,2,2,1),
			Solve(2,1,1,2),
			Solve(2,1,2,1)
		}),'\n');
	}
	return 0;
}
```

感谢阅读！求赞 QwQ。

---

