# Jury Meeting

## 题目描述

Country of Metropolia is holding Olympiad of Metrpolises soon. It mean that all jury members of the olympiad should meet together in Metropolis (the capital of the country) for the problem preparation process.

There are $ n+1 $ cities consecutively numbered from $ 0 $ to $ n $ . City $ 0 $ is Metropolis that is the meeting point for all jury members. For each city from $ 1 $ to $ n $ there is exactly one jury member living there. Olympiad preparation is a long and demanding process that requires $ k $ days of work. For all of these $ k $ days each of the $ n $ jury members should be present in Metropolis to be able to work on problems.

You know the flight schedule in the country (jury members consider themselves important enough to only use flights for transportation). All flights in Metropolia are either going to Metropolis or out of Metropolis. There are no night flights in Metropolia, or in the other words, plane always takes off at the same day it arrives. On his arrival day and departure day jury member is not able to discuss the olympiad. All flights in Megapolia depart and arrive at the same day.

Gather everybody for $ k $ days in the capital is a hard objective, doing that while spending the minimum possible money is even harder. Nevertheless, your task is to arrange the cheapest way to bring all of the jury members to Metrpolis, so that they can work together for $ k $ days and then send them back to their home cities. Cost of the arrangement is defined as a total cost of tickets for all used flights. It is allowed for jury member to stay in Metropolis for more than $ k $ days.

## 说明/提示

The optimal way to gather everybody in Metropolis in the first sample test is to use flights that take place on days $ 1 $ , $ 2 $ , $ 8 $ and $ 9 $ . The only alternative option is to send jury member from second city back home on day $ 15 $ , that would cost 2500 more.

In the second sample it is impossible to send jury member from city $ 2 $ back home from Metropolis.

## 样例 #1

### 输入

```
2 6 5
1 1 0 5000
3 2 0 5500
2 2 0 6000
15 0 2 9000
9 0 1 7000
8 0 2 6500
```

### 输出

```
24500
```

## 样例 #2

### 输入

```
2 4 5
1 2 0 5000
2 1 0 4500
2 1 0 3000
8 0 1 6000
```

### 输出

```
-1
```

# 题解

## 作者：LuckiestShawn (赞：6)

**题意简述**
- 有 $n$ 个人，编号为 $1,2,\dots,n$ 并分别在于其同编号的城市中。
- 他们需要通过航班前往大都会（$0$ 号城市）**共同**参与长达 $k$ 天会议（不小于 $k$ 天），他们可以从任意一天出发并**在当天到达**大都会，但需要当天有**这两个城市**之间的航班，每趟航班有各自的费用。在进行至少 $k$ 天的会议后再次通过航班回到各自的城市。
- 求最少需要花费的机票总价钱。

**输入**
- 第一行三个整数 $n,m,k$，$n$ 表示城市数也就是人数，$m$ 表示航班数，$k$ 表示 $n$ 个人需要一起讨论的天数。
- 接下来的 $m$ 有三个整数 $d,f,t$，$d$ 表示航班所在日期，$f(from)$ 表示出发城市，$t(to)$ 表示终点城市，$t$ 表示航班花费。

### **题目分析**
- 航班可以分为两类，一类为去往大都会的航班，另一类为离开大都会的航班，然后我们分开进行操作。

**操作一 来到大都会**

因为第 $x$ 个人在第 $k$ 天及之前到达可以有多个航班，所以他在第 $k$ 天之前到达的费用最小为前几天的有关航班的最小价钱。

记录一个结构体。
```cpp
struct AB{
	map <long long,long long> k;
	long long tot,money; 
}come[10000001],leave[10000001];
```
- `come[k].map[i]` 储存第 $x$ 个人在第 $k$ 天及之前到达的最小价钱。
- $tot$ 表示在这一天一共有多少个人可以到达大都会，如果能到达的人数小于总人数则这天不可以一起进行讨论。
- $money$ 表示这一天能够到达的人到达大都会的最小价钱的总和。

拿样例模拟模拟
样例中前往大都会的航班有：

| 日期 | $1$ | $2$ | $3$ |
| :----------: | :----------: | :----------: | :----------: |
| 起点城市 | $1$ | $2$ | $2$ |
| 机票价格 | $5000$ | $6000$ | $5500$ |
| $MIN - 1$ | $5000$ | $5000$ | $5000$ |
| $MIN - 2$ | $can't$ | $6000$ | $5500$ |
| $money$ | $5000$ | $11000$ | $10500$ |
| $tot$ | $1$ | $2$ | $2$ |

注：需要先将航班按日期先后排序，日期前的在后。

这样操作一就结束了。

**操作二 离开大都会**

大部分同操作一，但是航班排序时需要日期在后的航班在前排序。

| 日期 | $15$ | $9$ | $8$ |
| :----------: | :----------: | :----------: | :----------: |
| 终点城市 | $2$ | $1$ | $2$ |
| 机票价格 | $9000$ | $7000$ | $6500$ |
| $MIN - 1$ | $can't$ | $7000$ | $7000$ |
| $MIN - 2$ | $9000$ | $9000$ | $6500$ |
| $money$ | $9000$ | $16000$ | $13500$ |
| $tot$ | $1$ | $2$ | $2$ |

**贪心**

我们先把操作一、二中的 $money,tot$ 一起提出来。

| 日期 | $1$ | $2$ | $3$ | $8$ | $9$ | $15$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $money$ | $5000$ | $11000$ | $10500$ | $13500$ | $16000$ | $9000$ |
| $tot$ | $1$ | $2$ | $2$ | $2$ | $2$ | $1$ |
定义 $kcome$ 为所有人中最晚到达大都会的日期，$kleave$ 为所有人中最早离开都到达大都会的日期

$kcome$ 初始为有关前往大都会航班中最后的日期，即样例中的 $3$，
$kleave$ 初始为有关离开大都会航班中最早的日期，即样例中的 $8$。

注：$leave$ 结构体数组日期顺序是单调递减的。

如果 $kleave-kcome\le k$ 时，所有人一起参与讨论的时间将小于 $k$ 天，不满足题意。所以因该将 $kcome$ 时间向前推或将 $kleave$ 时间向后推。
- 如果 `come[kcome的上一次航班].money-come[kcome]<come[kleave的下一次航班].money-come[kleave]`，说明将 $kcome$ 时间向前推产生的新费用会小于将 $kleave$ 时间向前推产生的新作用，所以因把 $kcome$ 向前推。
- 反之应把 $kleava$ 时间向后推，同理。
- 如果 $kcome,kleave$ 所对应的日期能够到达 $(kcome)$ 或离开  $(kleave)$ 的人数小于 $n$，即结构体中的 $tot<n$，那么这一天必定不能作为讨论的日期，所以这一天及其之前 $(kcome)$ 或之后 $(kleave)$ 的日期应舍去。

最后，
如果此时 $kleave-kcome\le k$，说明没有符合题意的方案，输出 $-1$，否则输出 $come[kcome].money+leave[kleave].money$。

注：
- 存储航班信息至结构体数组时应按照日期进行 hash，避免无意义运算，但同时也要反向记录此 hash 值所对应的天数。

~完结撒花~

```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
// 离散化 
map <long long,long long> k;
map <long long,long long> rek;
map <long long,long long> _k;
map <long long,long long> _rek;
struct AB{
	//  第 x天 第 i个人到达的最小航班花费 
	map <long long,long long> k;
	long long tot,money; 
}come[10000001],leave[10000001];
struct CD{
	long long d,f,t,c;
}pc[10000001],pl[10000001];
bool spc(CD a,CD b)
{
	return a.d<b.d;
}
bool spl(CD a,CD b)
{
	return a.d>b.d;
}
long long n,m,tc,tl,d,f,t,c,tot,K,cnt,k1,k2,cm,lm;
int main()
{
	scanf("%lld%lld%lld",&n,&m,&K);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld%lld",&d,&f,&t,&c);
		if(f)
		{
			pc[++tc].d = d;
			pc[tc].f = f;
			pc[tc].t = t;
			pc[tc].c = c;
		}
		else
		{
			pl[++tl].d = d;
			pl[tl].f = f;
			pl[tl].t = t;
			pl[tl].c = c;
		}
	}
	sort(pc+1,pc+tc+1,spc);
	sort(pl+1,pl+tl+1,spl);
	for(int i=1;i<=tc;i++)
	{
		d = pc[i].d;
		f = pc[i].f;
		t = pc[i].t;
		c = pc[i].c;
		if(k[d]==0)
		{
			k[d] = ++tot;
			rek[tot] = d;
		}
		if(come[k[d]].money==0)
		{
			come[k[d]].k = come[k[d]-1].k;
			come[k[d]].tot = come[k[d]-1].tot;
			come[k[d]].money = come[k[d]-1].money;
		}
		
		if(come[k[d]].k[f]==0)
			come[k[d]].tot++;
		if(come[k[d]].k[f]==0||come[k[d]].k[f]>c)
		{
			come[k[d]].money += c;
			come[k[d]].money -= come[k[d]].k[f];
			come[k[d]].k[f] = c;
		}
	}
	for(int i=1;i<=tl;i++)
	{
		d = pl[i].d;
		f = pl[i].f;
		t = pl[i].t;
		c = pl[i].c;
		if(_k[d]==0)
		{
			_k[d] = ++cnt;
			_rek[cnt] = d;
		}
		if(leave[_k[d]].money==0)
		{
			leave[_k[d]].k = leave[_k[d]-1].k;
			leave[_k[d]].tot = leave[_k[d]-1].tot;
			leave[_k[d]].money = leave[_k[d]-1].money;
		}
		if(leave[_k[d]].k[t]==0)
			leave[_k[d]].tot++;
		if(leave[_k[d]].k[t]==0||leave[_k[d]].k[t]>c)
		{
			leave[_k[d]].money += c;
			leave[_k[d]].money -= leave[_k[d]].k[t];
			leave[_k[d]].k[t] = c;
		}
	}
	while(come[++k1].tot!=n&&k1<=tot+1);
	while(leave[++k2].tot!=n&&k2<=cnt+1);
	
   // 这里我是从外向里查找的，逻辑略有不同
	while(k1<=tot&&k2<=cnt)
	{
		cm = come[k1].money-come[k1+1].money;
		lm = leave[k2].money-leave[k2+1].money;
		if(come[k1+1].money==0)
			cm = 0; 
		if(leave[k2+1].money==0)
			lm = 0;
		
		if(cm>lm&&_rek[k2]-rek[k1+1]>K)
			k1++;
		else if(cm<lm&&_rek[k2+1]-rek[k1]>K)
			k2++;
		else
			break;
		
	}
	if(_rek[k2]-rek[k1]<=K)	
	{
		printf("-1");
		return 0;
	}
	printf("%lld",come[k1].money+leave[k2].money);
	return 0;
}
```


---

## 作者：Mihari (赞：3)

[TOC]

# 题目

[传送门](https://www.luogu.com.cn/problem/CF853B)

# 思路

十分巧妙的差分前缀和好题。

题目板块完结之后，我看到有很多处理此题的方法，但总感觉差分前缀和比较巧妙。

首先，通过输入我们可以将每个人能在 $0$ 号点停留的最大时间区间 $[tl,tr]$ ，并将所有人的 $[tl,tr]$ 取交集，得到 $[ll,rr]$ 即表示只有在这个区间中所有人能够聚集在一起。

显然，如果 $rr-ll-1<k$ 则直接 `puts("-1")` 即可。

然后怎么办？假设所有人聚集的时间从 $i$ 开始到 $i+k+1$ 或者更久，那么我们可以保证他们工作的时常至少为 $k$ ，那么我们需要找的就是所有人在 $[1,i]$ 时间段内到 $0$ 的最小花费以及 $[i+k+1,n]$ 时间段返回的最小花费之和。

两种情况是一样的，我们只讨论其中一种，不妨讨论前往 $0$ 的情况。

对于一个人，我们假设他在 $i$ 时刻到达 $0$ 最便宜的价格为 $m_i$，再将他的所有前往 $0$ 的航班按时间顺序由小到大排序。

规定：$t_i$ 表示第 $i$ 趟航班起飞的时间，$c_i$ 为其花费，$m_i$ 为这个人在 $i$ 时刻到达 $0$ 的最小花费。

现在我们分析他的第一堂航班和第二趟航班，由于 $t$ 我们已经按序排序了，现在讨论 $c$ 的大小关系：

1. $c_1\le c_2$ ，那么这个人坐第一趟航班肯定是最便宜的，而且我们可以对 $m_i$ 数组进行修改，即 $\forall m_i,t_1\le i<t_3,m_i=c_1$ ，注意，此处 $i<t_3$ 而非 $t_2$ （仔细想想，为什么？）；
2. $c_1>c_2$ ，此刻我们发现，在时间 $i$ 介于区间 $[t_1,t_2)$ 的时候，肯定只能乘坐第一趟航班，但如果 $i\ge t_2$ ，我们乘坐第二趟航班无疑最优，即当 $t_1\le i < t_2$ 时，$m_i=c_1$ ，当 $i\le t_2$ 时，$m_i=c_2$ ；

将我们的分析推广到整个体系当中：

在枚举当前是第 $i$ 趟航班时，保留 $1,2,\ldots i-1$ 趟航班中的最小花费 $\min$ 。

- 如果 $c_i<\min$ ，那么我们更新 $\min$ ，并用 $c_i$ 将 $m_i,i\in [t_i,t_{i+1})$ 全部更新；
- 如果 $c_i\ge \min$ ，那么我们保留 $\min$ ，并用 $\min$ 将 $m_i,i\in [t_i,t_{i+1}]$ 全部更新；

> 至于从 $0$ 返回希望大家自行分析，因为代码中有一些 $+1$ 如果没有分析是很难弄懂的。

经过分析，我们发现这个操作十分像**区间赋值**，那么这里就有许多数据结构和思想值得我们使用：

- 线段树
- 树状数组
- 差分前缀和

个人推荐差分前缀和，因为前两者的修改、询问都是 $\mathcal O(\log N)$ 的，后者修改 $\mathcal O(1)$ ，询问 $\mathcal O(\log N)$，而基于我们的分析似乎修改操作十分繁杂，而询问操作只有在最后计算答案时使用。

那么我们对于每一个人，可以开一个 $ansl[i][t]$ 表示这个人 $i$ 在 $t$ 时刻到 $0$ ，再开一个 $ansr[i][t]$ 表示这个人再 $t$ 时刻离开 $0$ 。但是人有 $10^5$ 个，时间刻度有 $10^6$ 个，开二维肯定不限时，但由于人与人之间相互独立，没有什么影响，我们考虑所有人共用一个 $ansl$ 和一个 $ansr$ 数组。

具体细节见代码。

# 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<utility>
using namespace std;

#define rep(i,__l,__r) for(signed i=__l,i##_end_=__r;i<=i##_end_;++i)
#define fep(i,__l,__r) for(signed i=__l,i##_end_=__r;i>=i##_end_;--i)
#define writc(a,b) fwrit(a),putchar(b)
#define mp(a,b) make_pair(a,b)
#define ft first
#define sd second
#define LL long long
#define ull unsigned long long
#define uint unsigned int
#define pii pair< int,int >
#define Endl putchar('\n')
#define CODEFAIL puts("-1"),exit(0)
// #define FILEOI
// #define int long long
// #define int unsigned

#ifdef FILEOI
# define MAXBUFFERSIZE 500000
    inline char fgetc(){
        static char buf[MAXBUFFERSIZE+5],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,MAXBUFFERSIZE,stdin),p1==p2)?EOF:*p1++;
    }
# undef MAXBUFFERSIZE
# define cg (c=fgetc())
#else
# define cg (c=getchar())
#endif
template<class T>inline void qread(T& x){
    char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    if(f)x=-x;
}
inline int qread(){
    int x=0;char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    return f?-x:x;
}
// template<class T,class... Args>inline void qread(T& x,Args&... args){qread(x),qread(args...);}
template<class T>inline T Max(const T x,const T y){return x>y?x:y;}
template<class T>inline T Min(const T x,const T y){return x<y?x:y;}
template<class T>inline T fab(const T x){return x>0?x:-x;}
inline int gcd(const int a,const int b){return b?gcd(b,a%b):a;}
inline void getInv(int inv[],const int lim,const int MOD){
    inv[0]=inv[1]=1;for(int i=2;i<=lim;++i)inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
}
template<class T>void fwrit(const T x){
    if(x<0)return (void)(putchar('-'),fwrit(-x));
    if(x>9)fwrit(x/10);
    putchar(x%10^48);
}
inline LL mulMod(const LL a,const LL b,const LL mod){//long long multiplie_mod
    return ((a*b-(LL)((long double)a/mod*b+1e-8)*mod)%mod+mod)%mod;
}

const int MAXN=1e5;
const int MAXM=1e5;
const int MAXK=1e6;
const int INF=(1<<30)-1;

int n,m,k,ll,rr;
vector< pii >a[MAXN+5],b[MAXN+5];
//a[i] : 第 i 个点到 0 点的时间, 花费
//b[i] : 0 点到 i 点的时间, 花费

inline void input(){
    n=qread(),m=qread(),k=qread();
    for(int i=1,d,f,t,c;i<=m;++i){//照常规输入即可
        d=qread(),f=qread(),t=qread(),c=qread();
        if(f==0)b[t].push_back(mp(d,c));
        else a[f].push_back(mp(d,c));
    }
}

inline void init(){
    ll=-1,rr=INF;
    int tl,tr;
    rep(i,1,n){
        sort(a[i].begin(),a[i].end());
        sort(b[i].begin(),b[i].end());
        tl=INF,tr=-1;
        if(!a[i].empty())tl=a[i].begin()->first;
        if(!b[i].empty())tr=b[i].back().first;
        if(tl==INF || tr==-1)CODEFAIL;//如果连来的机票或者回去的机票的没有, 直接 gg
        ll=Max(ll,tl),rr=Min(rr,tr);//取交集
        // printf("i == %d, tl == %d, tr == %d\n",i,tl,tr);
    }
    // printf("ll == %d, rr == %d\n",ll,rr);
    if(ll==-1 || rr==INF || rr-ll-1<k)CODEFAIL;//如果缺机票或者全部人最大的交集都不够 k 天也 gg 了
}

LL ansl[MAXK+5],ansr[MAXK+5],res=(1ll<<60)-1;
inline void solve(){
    for(int i=1,now,cost;i<=n;++i){
        now=1,cost=INF;//初始化
        // puts("For into ansl");
        for(int t=0,siz=a[i].size(),tmp;t<siz;++t){
            // printf("When i == %d, now == %d, cost == %d\n",i,now,cost);
            tmp=a[i][t].first;
            ansl[tmp]-=cost;
            ansl[now]+=cost;
            //差分前缀和的基本操作
            //注意:此处有别于下面, 原因在于这里是处理前往 0 点而非离开 0 点
            now=tmp,cost=Min(cost,a[i][t].second);
            // printf("After i == %d, now == %d, cost == %d\n",i,now,cost);
        }
        ansl[MAXK+1]-=cost;
        ansl[now]+=cost;
        now=MAXK,cost=INF;//倒着处理
        for(int t=b[i].size()-1,tmp;t>=0;--t){
            tmp=b[i][t].first;
            ansr[now+1]-=cost,ansr[tmp+1]+=cost;
            now=tmp,cost=Min(cost,b[i][t].second);
        }
        ansr[1]+=cost,ansr[now+1]-=cost;
        // printf("After i == %d, the two arr:\n",i);
        // rep(t,1,20)writc(ansl[t],' ');Endl;
        // rep(t,1,20)writc(ansr[t],' ');Endl;
    }
    rep(i,1,MAXK)ansl[i]+=ansl[i-1],ansr[i]+=ansr[i-1];//差分前缀和数组的最后一步
    // rep(i,1,20)writc(ansl[i],' ');
    // Endl;
    // rep(i,1,20)writc(ansr[i],' ');
    // Endl;
    for(int i=ll;i+k+1<=rr;++i)res=Min(res,ansl[i]+ansr[i+k+1]);
    writc(res,'\n');
}

signed main(){
#ifdef FILEOI
    freopen("file.in","r",stdin);
    freopen("file.out","w",stdout);
#endif
    input();
    init();
    solve();
    return 0;
}
```

~~似乎有点贪心？~~

---

## 作者：ctq1999 (赞：2)

思路和实现参考了 Codeforces 上的一个提交记录。

## 题目简述

有 $n$ 给城市，编号从 $1$ 到 $n$。给定 $m$ 班次航班，第 $i$ 班次航班的信息有 $d_i$、$f_i$、$t_i$、$c_i$，分别表示第 $i$ 班次航班在第 $d_i$ 天起飞且到达，从 $f_i$ 城市起飞，在 $t_i$ 降落，需要花费 $c_i$。

每个城市各一个人，共 $n$ 个人要去 $0$ 号城市，且要在 $0$ 号城市至少停留 $k$ 天。停留期间不能乘坐飞机。问至少需要多少费用才能到达要求。

## 思路

首先对于每个人，有两部分需要处理：起飞的班次和降落的班次。考虑把他们两个分开了处理，最后再扫描取最小值。

设 $f_i$ 为前 $[1,i-1]$ 天所有人前往 $0$ 所需最小的费用。特别的，若一个人在 $[1,i-1]$ 没有可以乘坐的班次，那么设他的费用是极大值。

再设 $g_i$ 为后 $[i+k,n]$ 天所有人返回各自城市所需最小的费用。特别的，若一个人在 $[i+k,n]$ 没有可以乘坐的班次，那么设他的费用为极大值。

那么最后的答案就是：

$$ans=\min\{f_i+g_i\}$$

这个形式和最大两个子段和异曲同工。

那么 $f$、$g$ 的转移同样的，可以从上一个转移过来。

时间复杂度：$O(10^6+m)$。

## 实现

详细地讲一下 $f$、$g$ 的实现。

把 $f$、$g$ 初始成 $n\times\text{INF}$。

定义两个数组 $st$ 和 $ed$。$st_i$ 表示目前从 $i$ 到 $0$ 的班次中费用最小值。初始值为 $\text{INF}$。$ed_i$ 同理。

把班次从小到大排序。

可以发现 $f_i$ 一定是在 $[1,i-1]$ 中，各自城市到 $0$ 费用的最小值的和。

首先 $f_i$ 可以从 $f_{i-1}$ 直接转移，即 $f_i=f_{i-1}$。

然后 j 从上次的下标开始一直扫描到最后一个在 $[1,i-1]$ 的班次，然后进行更新。

如果城市 $x$ 在第 $i$ 天有了第一个去 $0$ 的班次，那么就把 $f_i$ 减去 $st_x$，同时加上这个班次的花费，把 $st_x$ 的值更新这个花费。

之后这个城市有了更便宜的班次，也就是花费小于 $st_x$，那么就把 $f_i$ 减去 $st_x$ 与花费的差，更新 $st_x$ 的值为这个花费，来达到维护 $f$ 的目的。

```
while (j <= m && a[j].d < i) {
	if (!a[j].t && st[a[j].f] > a[j].c) {
		f[i] -= st[a[j].f] - a[j].c;
		st[a[j].f] = a[j].c;
	}
	++j;
}
```


若有城市在 $[1,i-1]$ 中没有去 $0$ 的班次，那么 $f_i$ 的值一定会比 $\text{INF}$ 大，最后的答案 $ans$ 若大于 $\text{INF}$ 就说明无解。

$g$ 的维护同理。

## 代码

```
#include <bits/stdc++.h>

#define ll long long
#define fi first
#define se second
#define Re register
#define I inline

using namespace std;

const int MAXN = 200010;
const int MAXM = 1000010;
const ll INF = 1e12;
const int mod = 1e9 + 7;

ll read() {
	ll s = 0, f = 1;
	char ch = getchar();
	while ('0' > ch || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while ('0' <= ch && ch <= '9') {s = (s << 3) + (s << 1) +  (ch - '0'); ch = getchar();}
	return s * f;
}

int n, m, k;
ll ans, cnt, tot;

string s;

struct Flight {
	ll d, f, t, c;
}a[MAXN];

bool cmp(Flight x, Flight y) {
	return x.d < y.d;
}

ll f[MAXM], g[MAXM];
ll st[MAXN], ed[MAXN];

int main() {
	int T;
	n = read(); m = read(); k = read(); 
	for (int i = 1; i <= m; i++) {
		a[i].d = read(); a[i].f = read(); a[i].t = read(); a[i].c = read();
	}
	sort(a + 1, a + m + 1, cmp);
	int dl = 1e6;
	for (int i = 0; i <= dl + 1; i++) {
		f[i] = g[i] = 1ll * INF * n;
	}
	for (int i = 1; i <= n; i++) {
		st[i] = ed[i] = INF;
	}
	int j = 1;
	for (int i = 1; i <= dl - k; i++) {
		f[i] = f[i - 1];
		while (j <= m && a[j].d < i) {
			if (!a[j].t && st[a[j].f] > a[j].c) {
				f[i] -= st[a[j].f] - a[j].c;
				st[a[j].f] = a[j].c;
			}
			++j;
		}
	}
	j = m;
	for (int i = dl - k; i >= 1; i--) {
		g[i] = g[i + 1];
		while (j >= 1 && a[j].d >= i + k) {
			if (!a[j].f && ed[a[j].t] > a[j].c) {
				g[i] -= ed[a[j].t] - a[j].c;
				ed[a[j].t] = a[j].c;
			}
			--j;
		}
	}
	ans = 1e12;
	for (int i = 1; i <= dl - k; i++) {
		ans = min(ans, f[i] + g[i]);
	}
	if (ans == 1e12) puts("-1");
	else printf("%lld\n", ans);
	return 0;
}

/*

*/
```




---

## 作者：泠小毒 (赞：1)

# Jury Meeting
现在有(n+1)个城市，其中第1~n个城市每个城市有一个人，第0个城市是人们需要聚集的地方。还有m条航班，每条航班从0到其他城市或从其他城市到0，当天即可抵达，现在需要选定一个时间段，长度为k天，使得这一个时间段里人们都在0城市工作(航班抵达和离开0城市的那一天不能进行工作)，问把n个人送到0城市，工作完成后再送回去的最小花费。
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190506/)
## 解法
预处理出a数组和b数组，其中a[i]表示i时间所有人到0号城市的最小消费，b[i]表示i时间所有人都回到自己所在城市的最小消费，处理这两个数组需要遍历所有时间与所有的边，所以复杂度是O(t+m)的，非常优了
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int to,next,w;}ea[100010],eb[100010];
int n,m,k,t,x,y,z,st,ed,cnta,cntb,heada[1000010],headb[1000010],disa[100010],disb[100010];
long long ans=-1,a[1000010],b[1000010];
void adda(){ea[++cnta]={x,heada[t],z},heada[t]=cnta;}
void addb(){eb[++cntb]={y,headb[t],z},headb[t]=cntb;}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&t,&x,&y,&z);
		if(!x)addb();else adda();
		//分为x去0的边和0去y的边，分开储存
	}
	cnta=cntb=0;
	for(int i=1;i<=1000000;i++)
	{
		a[i]=a[i-1];
		for(int j=heada[i];j;j=ea[j].next)
		{
			t=ea[j].to;
			if(!disa[t])cnta++,disa[t]=ea[j].w,a[i]+=disa[t];
			else if(disa[t]>ea[j].w)a[i]+=ea[j].w-disa[t],disa[t]=ea[j].w;
		}
		//计算当前a[i]
		if(!st&&cnta==n)st=i;
		//如果都能到达0号点，就从此刻开始
	}
	for(int i=1000000;i>=1;i--)
	{
		b[i]=b[i+1];
		for(int j=headb[i];j;j=eb[j].next)
		{
			t=eb[j].to;
			if(!disb[t])cntb++,disb[t]=eb[j].w,b[i]+=disb[t];
			else if(disb[t]>eb[j].w)b[i]+=eb[j].w-disb[t],disb[t]=eb[j].w;
		}
		//倒序计算当前b[i]
		if(!ed&&cntb==n)ed=i;
		//如果都能回到原来的城市，就最多遍历到此刻
	}
	if(st==0||ed==0){puts("-1");return 0;}
	//如果不能都到0号点或不能都回到原来的城市，无解
	for(int i=1;i<=1000000;i++)
	{
		if(i+k+1>ed)break;
		if(i<st)continue;
		if(ans==-1)ans=a[i]+b[i+k+1];
		else ans=min(ans,a[i]+b[i+k+1]);
	}
	//枚举计算答案
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意简述
有 $n+1$ 个序号 $0$ 到 $n$ 的点，$n$ 个点上都有人，它们需要到点 $0$ 一起待至少 $k+2$ 天再各自回到原来的点上。

现在给定一些有权值的单向边，它们只有特殊的时间点才可以通过。

问，要满足这 $n$ 个人的行动需求经过的边权值和最小为多少。如果不能满足，输出 $-1$。
# 思路
维护两个数据，一个是全部人都在时间点 $i$ 及其以前到达点 $0$ 只算前往的最少权值和，另一个是全部人都在时间点 $i$ 及其以后回到原来的点只算返回的最少权值和。

最后，枚举时间点 $i$ 和 $i+k+1$，求最小权值和就可以了。
# 实现
```cpp
#include<iostream>
#include<algorithm> 
#include<map>
#define N 100005
#define int long long
using namespace std;
map<int,int> v1,v2;
struct tmc{int d,u,v,w;}eg[N],ge[N];
bool cmp(tmc a,tmc b){return a.d<b.d;}
int id1,id2,n,m,k,tot1,tot2,p1,p2,ans=1e18,Pre=1e9,Bak=-1e9,go[N],bk[N],P,B,pre[N*10],bak[N*10],r1[N*10],r2[N*10];
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	v1[1000000]++;
	for(int i=1;i<=n;i++)go[i]=bk[i]=1e18;
	for(int i=1,d,u,v,w;i<=m;i++){
		scanf("%lld%lld%lld%lld",&d,&u,&v,&w);
		if(v==0)eg[++tot1]={d,u,v,w},v1[d]++;
		else ge[++tot2]={d,u,v,w},v2[d]++;
	}sort(eg+1,eg+tot1+1,cmp);
	sort(ge+1,ge+tot2+1,cmp);
	for(auto tc:v1){
		v1[tc.first]=++id1;
		r1[id1]=tc.first;
	}for(auto tc:v2){
		v2[tc.first]=++id2;
		r2[id2]=tc.first;
	}for(int i=1;i<=tot1;i++){
		int u=eg[i].u,w=eg[i].w;
		if(go[u]==1e18)p1++,P+=w;
		else P=min(P-go[u]+w,P);
		go[u]=min(go[u],w);
		if(Pre==1e9&&p1>=n)Pre=eg[i].d;
		if(p1>=n)for(int j=eg[i].d;j<r1[v1[eg[i].d]+1];j++)pre[j]=P;
	}if(Pre==1e9){
		printf("-1");
		return 0;
	}for(int i=tot2;i>=1;i--){
		int v=ge[i].v,w=ge[i].w;
		if(bk[v]==1e18)p2++,B+=w;
		else B=min(B-bk[v]+w,B);
		bk[v]=min(bk[v],w);
		if(Bak==-1e9&&p2>=n)Bak=ge[i].d;
		if(p2>=n)for(int j=ge[i].d;j>=r2[v2[ge[i].d]-1]+1;j--)bak[j]=B;
	}if(Bak==1e9||Bak-Pre-k<1){
		printf("-1");
		return 0;
	}for(int j=eg[tot1].d+1;j<=Bak;j++)pre[j]=P;
	for(int l=Pre,r=Pre+k+1;r<=Bak;l++,r++)ans=min(ans,pre[l]+bak[r]);
	printf("%lld",ans);
	return 0;
}
```

---

