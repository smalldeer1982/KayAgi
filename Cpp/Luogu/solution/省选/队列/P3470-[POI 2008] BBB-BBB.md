# [POI 2008] BBB-BBB

## 题目描述

Byteasar 在 Byteotian Bit Bank（简称 BBB）有一个账户。  一开始账户里有 $p$ 个 bythaler，最后有 $q$ 个 bythaler。  每笔交易要么是存入一个 bythaler，要么是取出一个 bythaler。  账户余额从未为负。  一位银行柜员准备了一份银行对账单：一条纸带，上面有一系列的加号和减号（加号表示存入一个 bythaler，减号表示取出一个 bythaler）。  很快发现，有些交易记录不正确。  银行柜员不能打印另一份对账单，但必须修改已经打印的那一份。  对账单不必与事实一致，只要交易序列满足以下两个条件即可：  最终余额与初始余额和对账单中的交易序列一致，根据对账单中的交易序列，账户余额从未为负。  你需要计算银行柜员需要多少最少时间来修正对账单。  银行柜员可以：  - 在 $x$ 秒内将任意选择的交易变为其相反的交易，或者 - 在 $y$ 秒内将最后一笔交易移到对账单的开头。  例如，如果 $p=2,q=3$，那么 `--++-+-++-+-+` 是一个正确的对账单。  另一方面，对账单 `---++++++` 是不正确的，因为账户余额在第三笔交易后会变为负数，而且最终余额应该是 3，而不是 5。  然而，可以通过将倒数第二个符号变为其相反的符号，并将最后一笔交易移到对账单的开头来修正。  ### 任务  编写一个程序：  - 从标准输入中读取 Byteasar 账户的当前对账单（一个加号和减号的序列）以及数字 $p,q,x$ 和 $y$。 - 输出修正对账单所需的最少秒数，使得初始和最终余额一致，并且余额从未为负。 

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
9 2 3 2 1
---++++++
```

### 输出

```
3
```

# 题解

## 作者：jjsnam (赞：17)

# 写在前面

学校的作业。翻了一遍题解区，看不懂或者没有 LaTeX，补一个比较详细的题解。

## 题目描述（戳这里[查看原题](https://www.luogu.com.cn/problem/P3470)）

- 给定一个银行存折，初始存款是 $p$，最终存款是 $q$。

- 给出一个**可能错误**的账单明细，即由 $n$ 个操作组成的序列，由 ```+```、```-``` 组成。分别表示操作：存 $1$ 块钱，取 $1$ 块钱。

- 两种修改：①对于某个操作符号取反，即 ```+``` $\rightarrow$ ```-``` 或 ```-``` $\rightarrow$ ```+```，代价为 $x$。②将最后一个操作移到操作序列最前端，代价为 $y$。

- 求如何修改使**代价最小**的同时满足最终存款为 $q$，且任意操作后账户余额不为负数，求出最小代价。

- $n,p,q ≤ 1\times 10^6$，$x,y ≤ 1000$。

# 正文

乍一看好像是个 DP。但是仔细想想方案数设出来总是在 $O(n^2)$ 左右。所以我们把几个操作分开看，因为互相似乎没有什么影响。

## 分析

先来看取反操作。如果说对一个操作符取反，那么最终答案会有什么变化？首先，定义 $sum_i$ 表示整个操作从头到 $i$ 位置总的变化量（即前缀和）。容易想到 ```+``` 对应 $sum_i=sum_{i-1}+1$，反之同理。那么，如果将一个符号取反，比如 ```+``` $\rightarrow$ ```-```，那么对最终 $sum_n$ 的影响是一定的，即 $-2$，反过来就是 $+2$。

再者，**移动操作对 $sum_n$ 没有影响**。因为旋转不会改变序列中总的操作符数量和种类。那么，为了使 $p+sum_n = q$，我们首先可以确定至少需要取反的操作符个数 $m$，记为代价一。即：
$$m = \dfrac{q - (p+sum_m)}{2}$$
$$Cost1 = x\times \left|m \right|$$

而且注意，这种**必要取反操作只会发生在一种操作符**。（毕竟如果两种都操作有一些变化能抵消，那就不是最小代价了）

这样我们首先满足了最终存款是 $q$，再来考虑怎么满足任意时刻余额不为负。

数学化的，$\forall i\in[1,n]$，$p+sum_i≥0$。那么，因为有 ```-``` 的存在，所有 $sum_i$ 中一定会有一个最小值，我们可以找出这个最小值 $sum_i$。可能  $p+sum_i<0$，考虑什么操作可以让 $p+sum_i$ 变大。一种是通过移动操作，通过移动一些操作符，让更多的 ```+``` 到前面，使所有 $sum_i$ 尽可能的大。还有一种操作，就是“交换”，即在操作序列后部让一个 ```+``` $\rightarrow$ ```-```，在前部让一个 ```-``` $\rightarrow$ ```+```，这样 $sum_n$ 不会改变，但是最小的 $sum_i$ 就会变大。

接下来想一想最终答案怎么求。

移动操作不好确定，我们尝试 $O(n)$ 枚举移动了几个操作符，那么就钦定了所有移动情况，此时的基础移动代价记作代价二。假设移动了 $k$ 个操作符：
$$Cost2 = y \times k$$
我们定义 $Min[k]$ 表示钦定移动了 $n-k$ 个操作符，此时序列末尾是原来的 $k$ 时的操作序列，最小的 $sum_i$。那么先把至少要改的操作符改掉。这里要贪心的想，为了让 $p+sum_i$ 尽可能大，如果是 ```-``` $\rightarrow$ ```+```，这种变化更靠前是最好的，这样能使 $p+sum_i$ 变大；如果是 ```+``` $\rightarrow$ ```-``` 则越靠后越好，这样对 $p+sum_i$ 不会产生负影响。（先假定这样，证明会在后文提及）我们加入对 $p+sum_i$ 的影响，记作 $temp$。那么如果此时仍然有 $temp < 0$。就只能通过刚才定义的“交换操作”让 $temp$ 变大（注意一次“交换操作”的代价是 $2x$）。

## 细节与实现

其实刚才的很多做法都是我们猜的，我们尝试证明一下，这也是这道题的难点。

1.	上文中必要的取反操作，贪心选取 ```+``` $\rightarrow$ ```-``` 时越靠后越好，因为对 $p+sum_i$ 无影响，为什么？

	我们考虑一下如果有影响会是什么情况。比如这样 ```---+-```，如果按照贪心思路把这个 ```+``` 变成 ```-```，那 $p+sum_i$ 不就更小了吗？
    
    其实不然。如果出现这种情况，证明后面已经没有可以选择的 ```+``` 了，那么此时因为有影响，$i$ 变成 $n$，即更改完 $q=p+sum_n<0$。在题目保证有解的条件下这种情况**不合法**。因此不会有这种有影响的事情发生。
    
2.	必要的取反操作在 ```-``` $\rightarrow$ ```+``` 时为什么能全部贡献给 $sum_i$？
	
    也不一定是全部。如果此时 $i$ 前面的 ```-``` 很多，那么一定能全部贡献给 $sum_i$。如果比较少，那么不用全部贡献就能使 $p+sum_i≥0$ 了，而且也**不必进行后面的操作**。所以计算影响的时候都视作全部贡献**对最终答案是不会有影响**的。

3.	为什么只用考虑操作序列中最小的 $sum_i$？是否存在 $j$，使 $j≠i$ 且 $p+sum_j<0$？

	存在的。但是，在我们处理 $sum_i$ 时，一定也可以顺便把 $sum_j$ 都处理了。两种情况：
    
    - 若 $j>i$。那么我们通过处理让 $p+sum_i≥0$。根据定义 $sum_i≤sum_j$，由前缀和性质前面增加的量会传递到后面，则 $p+sum_j≥0$。
    - 若 $j<i$。如果更改的符号在 $[1,j]$，则一定能同时让 $sum_j$ 和 $sum_i$ 增加。因为 $sum_i≤sum_j$，因此满足 $p+sum_j≥0$ 的时刻**一定不晚于** $p+sum_i≥0$。如果更改的符号在 $(j,i]$，但这是不可能的。因为根据贪心思想，此时出现的情况一定是如 ```----++```，且不能通过取反操作完成 ```-``` $\rightarrow$ ```+```，则只能通过交换操作变成```+----+``` 这样，则又可以回到前一种情况。

4.	交换操作为什么一定可行？是否会因为交换导致出现一个新的最小值 $sum_j$？
	
    不会。根据我们交换操作时的贪心，选取尽可能靠后的 ```+``` 变成 ```-```，尽可能前的 ```-``` 变成 ```+```。如果出现了新的 $sum_j$，那只有可能是 ```+++-...---```，那此时 $j$ 又变成了 $n$，根据证明 1 这种情况也不可能出现。
    
这样我们刚才思路里所有可能出锅的点都证明完了，所以这个思路是没有问题的。接下来看看具体实现。

1.	如何求出每一种移动情况下的 $Min[i]$？

	其实这个移动操作很明显的有一种绕环转的意味，而且是反着转。那么我们按照套路将原序列倍长，同样前缀和也倍长，就可以求出每一个 $Min[i]$ 了。比如当 $i=n$ 时我们应该在 $[n+1,n+n]$ 里取最小值；这样当 $i=1$ 时就可以在 $[2,n+1]$ 里决策，不会 RE。下面是**化简过的式子**：
    
    $$Min[i]=\min_{i<j≤i+n}(sum_j)-sum_i$$
    
    观察这个式子，明显是 RMQ 问题。可以用线段树，当然 $10^6$ 有点悬。注意到决策区间是连续的，类似[滑动窗口](https://www.luogu.com.cn/problem/P1886)，故可以使用**单调队列**。

2.	交换操作的具体代价是什么？
	
    交换操作是两次取反，一次在 $sum_i$ 的 $i$ 前，一次在后。前面那个对 $sum_i$ 有影响，后面的无。那么根据一次 ```-``` $\rightarrow$ ```+``` 的变化是 $+2$，只需要 $\lceil\dfrac{\left|p+sum_i\right|}{2}\rceil$ 次交换操作就能是剩下的 $p+sum_i≥0$。记为代价三：
    $$Cost3=2\times x\times\lceil\dfrac{ \left|p+sum_i\right|}{2}\rceil\ \ \ (p+sum_i < 0)$$

最后每种情况的总代价就是上述三个代价和。

$O(n)$ 单调队列预处理所有 $Min[i]$，$O(n)$ 枚举所有移动情况，每种情况的代价都可以 $O(1)$ 求出。最终的总时间复杂度是 $O(n)$。

# 代码

最终的代码比较短。变量名和函数功能见注释。      
要注意的是**文章中为了便于理解用的 $sum_i$ 来表示 $Min[i]$。**

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int maxn = 1000006;

int Min[maxn];
int sum[maxn << 1];
int n, p, q, x, y;

int abs(int x){//绝对值函数
    return x > 0 ? x : -x;
}

void init(){
    /* 处理前缀和 */
    for (int i = 1; i <= n << 1; i ++){
        sum[i] += sum[i - 1];
    }

    /* 单调队列求 Min[i] */
    int q[maxn << 1], hh = 0, tt = -1;
    for (int i = n, j = n << 1; i > 0; i --){
        while (hh <= tt && q[hh] > i + n) hh ++;
        while (j > i){
            while (hh <= tt && sum[q[tt]] >= sum[j]) tt --;
            q[++ tt] = j --;
        }
        Min[i] = sum[q[hh]] - sum[i];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> p >> q >> x >> y;
    char op;
    for (int i = 1; i <= n; i ++){
        cin >> op;
        sum[i] = sum[i + n] = (op == '+' ? 1 : -1);
    }

    init();
    int m = (q - (p + sum[n])) >> 1;//至少要取反的操作符数量

    int ans = 0x7fffffff;
    for (int i = n; i > 0; i --){
        int cost = abs(m) * x + (n - i) * y; // 代价1 + 代价2
        int temp = p + Min[i];
        if (m > 0){//对temp能有贡献
            temp += m << 1;
        }
        if (temp < 0){//需要交换操作
            cost += 2 * x * ((abs(temp) + 1) / 2);// 代价3
        }
        ans = min(ans, cost);
    }

    cout << ans << endl;

    return 0;
}
```

# 总结

一开始看到单调队列就往 DP 想了，但是我们要知道的是单调队列的本质是数据结构，所以不仅仅只有优化 DP 一种功能，和贪心结合也是很常见的。

本题的难点不在单调队列，在于复杂的贪心能否想出来以及对于不确定的思路敢不敢继续深入，最后能否对不确定的思路都证明正确性。

谢谢观看！

---

## 作者：kczno1 (赞：13)

先枚举位移几次，然后算最少取反几次。


对于$p+sum_{i}>=0$的限制，只要求$min{ sum_{i} }$，把他$+2$一直加到$>=-p$即可，可以$O(1)$计算。


然后再考虑$p+sum_{n}=q$，相当于总的取反的次数是一定的，可以轻松计算。


现在只用维护好$min{ sum_{i} }$即可。


根据最小值的位置分两类讨论


一类是原来的未移动的，先$dp$出来，$dp$值加上移动的数的和即可。


一类是移动到前面的，每次移的时候维护一下即可。


```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
    if(x>y)x=y;
}
#define rep(i,l,r) for(int i=l;i<=r;++i)
const int N=1e6+5,inf=2e9;
char s[N];
int a[N],mn_a[N],b[N];

int main()
{
    freopen("1.in","r",stdin);
    int n,p,q,x,y;
    cin>>n>>p>>q>>x>>y;
    scanf("%s",s+1);
    rep(i,1,n)s[i]=s[i]=='-'?-1:1;
    rep(i,1,n)a[i]=a[i-1]+s[i];
    rep(i,1,n)mn_a[i]=min(mn_a[i-1],a[i]);
    int d=(q-p-a[n])/2;
    int ans=inf;
    rep(i,1,n)
    {
        int n_mn=min(a[n]-a[n-i+1]+mn_a[n-i+1],b[i-1]);
        int now=max(0,(-p-n_mn+1)/2);
        chmin(ans,(i-1)*y+(now+abs(d-now))*x);
        
        b[i]=min(b[i-1]+s[n-i+1],0);
    }
    cout<<ans;
}
```

---

## 作者：小塘空明 (赞：4)

显然把0-n-1个数移到开头后，每种情况下的判定方案是一定的，所以我们考虑没有翻转的计算。

先计算出初始状态下的最终账本收益，计算要取反几次，如果把-变+就尽量让前面的负号变为正，反之则尽量让后面的+号变负。

可以发现进行上述操作对并不会让最小值减小，显然增加操作只会让最小值变大，减小操作因为最终的q大于0所以将末尾的正号取反也不会让最小值变小。

假如完成操作后中间某一位置最小值小于0，那么就把这一位置前的一些数改为正，后面的一些数改为负。

所以预处理出每一个位置开始的最小值，每次计算序列的贡献+以第i个数开头所需要的前移操作的贡献，取最小值即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
const int N=2e6+10;
int n,p,q,x,y,l=1,r=1,num,f[N],a[N],s[N],que[N];ll ans=1e18;char ch[N];
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	n=read();p=read();q=read();x=read();y=read();scanf("%s",ch+1);
	for(int i=1;i<=n;i++) a[i]=a[i+n]=(ch[i]=='+'?1:-1),s[i]=s[i-1]+a[i];
	for(int i=n+1;i<=2*n;i++) s[i]=s[i-1]+a[i];
	que[l]=2*n;num=(p+s[n]-q)/2;
	for(int i=2*n-1;i;i--){
		while(l<=r&&que[l]>i+n-1) l++;
		while(l<=r&&s[que[r]]>=s[i]) r--;
		que[++r]=i;
		f[i]=s[que[l]]-s[i-1];
	}
	for(int i=1;i<=n;i++){
		int sum=(i==1?0:n+1-i);
		ll res=1ll*sum*y+1ll*abs(num)*x;
		ll v=num<0?p+f[i]-num*2:p+f[i];
		if(v<0) res+=2*x*((1-v)/2);
		ans=min(ans,res);
	}
	return printf("%lld\n",ans),0;
}
```


---

## 作者：樱洛CHANGE (赞：3)

发现没有**线段树**的题解所以来补一发线段树qwq。

-------------------
### 题目大意
给你一个 $+/-$ 序列，$+$ 表示 $+1$，$-$ 表示 $-1$ 。
给出 $p,q$，要求：
$$q+s_n=p\ \&\&\ q+s_i\ge0$$
其中 $s$ 为前缀和。

你可以执行两个操作：

- 将某一位取反（变号），花费为 $x$ 。
- 将最后一位丢掉第一位，花费为 $y$ 。

问最小花费。

--------------
### 题解
只考虑第一个操作，分类讨论：

- 若已经有 $q+s_n=p$，则答案显然为 $\max\{-q-s_i,0\}*2*x$
- 否则，若等号两侧不同，则考虑将二者合并计算，则答案为 $\left(\frac{\max\{-q-s_i,0\}}{2}+\left|\frac{\max\{-q-s_i,0\}-(s_n+q-p)}{2}\right|\right)*x$

发现二者都可以 $O(1)$ 计算，所以我们直接枚举转移次数，复杂度也是可以接受的。

发现上式中的 $\max\{-q-s_i,0\}$ 易用线段树进行维护，时间复杂度 $O(n\log n)$，数据范围 $10^6$ 可以承受。

-------------
### 代码
```
#include<bits/stdc++.h>
#define awa 2147483647
#define zhale exit(0)
#define re register
#define rint re int

using namespace std;
/*Shioiri Kukuri*/

typedef long long ll;
typedef unsigned long long ull;
typedef double qwq;
typedef pair<int,int> P;
typedef pair<ll,ll> llP;
#define rll re ll
#define rqwq re qwq

/*Otho Ai*/

template<class T>
void Swap(T &x,T &y)
{
	T z=x;
	x=y;
	y=z;
}

//#define PairOP
#ifdef PairOP
template<class T1,class T2>
inline const pair<T1,T2> operator + (const pair<T1,T2> &p1,const pair<T1,T2> &p2){
	return pair<T1,T2>(p1.first+p2.first,p1.second+p2.second);
}

template<class T1,class T2>
inline const pair<T1,T2> operator - (const pair<T1,T2> &p1,const pair<T1,T2> &p2){
	return pair<T1,T2>(p1.first-p2.first,p1.second-p2.second);
}
#endif

//#define FastIO
#ifdef FastIO
	char buf[1<<21],*p1,*p2;
	#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif

template<class T>
T Read()
{
	T x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^'0');
		ch=getchar();
	}
	return x*f;
}
//int (*read)()=Read<int>;
ll (*readll)()=Read<ll>;
#define read Read<int>

const int N=1e6+5;
char c[N];

int sum[N],n;
class SegmentTree{
	private:
		class Node{
			public:
				int val,lz;
				Node():val(0),lz(0){}
		}t[N<<2];
		#define mid (l+((r-l)>>1))
		#define ls (p<<1)
		#define rs (p<<1|1)
		inline void Pushdown(rint p,rint l,rint r){
			if(t[p].lz){
				t[ls].lz+=t[p].lz,t[rs].lz+=t[p].lz;
				t[ls].val+=t[p].lz,t[rs].val+=t[p].lz;
				t[p].lz=0;
			}
		}
		inline void Pushup(rint p,rint l,rint r){
			t[p].val=max(t[ls].val,t[rs].val);
		}
	public:
		inline void Build(rint p,rint l,rint r){
			if(l==r) return t[p].val=sum[l],void();
			Build(ls,l,mid),Build(rs,mid+1,r);
			Pushup(p,l,r);
		}
		inline void Change(rint p,rint l,rint r,rint x,rint y,rint k){
			if(l>y||r<x) return ;
			if(l>=x&&r<=y) return t[p].val+=k,t[p].lz+=k,void();
			Pushdown(p,l,r);
			Change(ls,l,mid,x,y,k),Change(rs,mid+1,r,x,y,k);
			Pushup(p,l,r);
		}
		inline int Sum(){
			return t[1].val;
		}
		inline void Debug(){
			for(rint i=1;i<=4*n;++i)
			cout<<t[i].val<<" ";
		}
		#undef mid
		#undef ls
		#undef rs
}t;

int p,q,x,y,ans=awa;
inline int True()
{
//#define Freopen
#ifdef Freopen
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif

//#define Clock
#ifdef Clock
	rint STR=clock();
#endif

	n=read(),p=read(),q=read(),x=read(),y=read();
	scanf("%s",c+1);
	for(rint i=1;i<=n;++i)
	sum[i]=sum[i-1]+(c[i]=='-'?1:-1);
	t.Build(1,1,n);
	rint k=(sum[n]+q-p)/2;
	for(rint i=0,r=0;i<n;++i)
	{
		if(i*y>ans) break;
		rint now=(t.Sum()-p+1)/2;
		ans=min(ans,i*y+(now+abs(now-k))*x);
		t.Change(1,1,n,n-i,n-i,-r-sum[n-i]),t.Change(1,1,n,1,n,(c[n-i]=='-'?1:-1));
		r+=(c[n-i]=='-'?1:-1);
	}
	printf("%d\n",ans);

#ifdef Clock
	rint END=clock();
	printf("Time:%dms\n",int((END-STR)/(qwq)CLOCKS_PER_SEC*1000));
	printf("Time:%ds\n",int((END-STR)/(qwq)CLOCKS_PER_SEC));
#endif
	return (0-0);//q(0-0)p q(>-<)p
}

int Love=True();

signed main(){;}
```

---

## 作者：机房冒火 (赞：3)


觉得大家在阅读的时候可能有些困难
发表一下注释版
思路大体和 [kcznol大佬](https://www.luogu.org/blog/user9168/solution-p3470)一样
先枚举位移几次，然后算最少取反几次。

对于p+sum_{i}>=0p+sum
i
​	 >=0的限制，只要求min{ sum_{i} }minsum 
i
​	 ，把他+2+2一直加到>=-p>=−p即可，可以O(1)O(1)计算。

然后再考虑p+sum_{n}=qp+sum 
n
​	 =q，相当于总的取反的次数是一定的，可以轻松计算。

现在只用维护好min{ sum_{i} }minsum 
i
​	 即可。

根据最小值的位置分两类讨论

一类是原来的未移动的，先dp出来，dp值加上移动的数的和即可。

一类是移动到前面的，每次移的时候维护一下即可。

------------
```cpp
#include<iostream>  
#include<cstdio>
#include<cstdlib>
using namespace std;
const int N=1e6+7;

int i,j,k,n,m,x,y,p,q,o;
int d[N],t[N],mint[N],downmint[N],ans;
char ch;
int main(){
	cin>>n>>p>>q>>x>>y;
	for(i=1;i<=n;++i)
	{
		cin>>ch;
		if(ch=='-')d[i]=-1;
		else d[i]=1;
		t[i]+=t[i-1]+d[i];
	}
  
	for(i=1;i<=n;++i)                   
	mint[i]=min(t[i],mint[i-1]);                    
	o=(q-p-t[n])/2;

	int ans=1e9;
	for(i=1;i<=n;++i)
	{
		int nm=min(t[n]-t[n-i+1]+mint[n-i+1],downmint[i-1]);//最小前缀和 
		int rep=max(0,(-p-nm+1)/2);//-(nm+p-1)/2  即改变量的值 且考虑到 nm+p可能是奇数 减1
		 //rep 是 表示将前面rep个-1变为1 rep>=0  
		 //o如果>0   o 个1 ---> -1  o<0  o个-1 ------>1 
		ans=min(ans,(rep+abs(o-rep))*x+(i-1)*y);//if o<0 说明无重复 1-->-1 用减法 if o>0 说明有重复 -1-->1,  
		downmint[i]=min(downmint[i-1]+d[n-i+1],0);
	 } 
	 
	cout<<ans;
	
	fclose(stdin);fclose(stdout);
	return 0;
}
```

---

## 作者：CLRLSP (赞：1)

## BBB-BBB

#### 题目大意

> 给定一个由 $+1$ 和 $-1$ 构成的长度为 $n$ 的序列，提供两种操作：
>
> 1.将某一位取反，花销为 $x$
>
> 2.将最后一位移动到第一位，花销为 $y$
>
> 给你初状态 $p$，末状态 $q$,使 $p+sum_n=q$,$p+sum_i \ge 0(1\le i\le n)$ ,求最小花销
>
> $sum_i$ 为此序列的前缀和

你看到 $sum_i$，你想，我为什么要用 $sum_i$ 啊？

因为 $p+sum_i$ 就是当前的**余额**啊。

首先，我们知道我们最初的钱和最终的钱。

所以，我们需要的 $+1$ 和 $-1$ 的数量是很好算出来哒。

进而可以求出**最少需要取反**的个数。

显然，我们要让前面的 $+1$ 尽可能多，防止 $p+sum_i<0$,因此，我们首先对**前面**的 $-$ 进行取反，对后面的 $+$ 进行取反。

很显然，我们只需要进行一次（很大的一次，指搬过来一个区间）二操作。

假如在*sum*序列中的最小值小于 $0$，则将这一位置之前的尽量靠前的一些数改为 $+1$，后面的一些数改为 $-1$

所以我们预处理出来每个二操作之后的 $sum$ 序列中的最小值，枚举以 $i$ 为开头长度为 $n$ 的序列中的最小值，也就是需要的前移操作，取最小值

#### 关于如何预处理

（~~线段树啊~~）

单调队列拥有**优秀且稳定**的 $O(n)$  的时空复杂度

我们将原序列复制一遍到原序列后面，来模拟交换后的样子，然后求出全部的前缀和

维护一个维护长度为 $n$ 的区间的最小值的**单调队列**

用 $f[i]$ 表示以 $i$ 为开头的长度为 $n$ 的余额序列中的最小值

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4e5+100;
int n,p,q,x,y;
char s[N];
int Sum[N],a[N];
int Need;
int Q[10*N],f[ma];
int l=1,r=1;

inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (isdigit(ch)) {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}

void Arknights() {
	//维护一个钱数单调递增的队列
	//即,维护在一个长度为n的区间内的最小值余额
	Q[1]=2*n;
	for(int i=2*n-1; i; i--) {
		while(l<=r && Q[l]>i+n-1) l++;//判断边界是否取多了
		while(l<=r && Sum[Q[r]]>=Sum[i]) r--;
		Q[++r]=i;
		f[i]=Sum[Q[l]]-Sum[i-1];
		//f[i]维护的是以i为开头的长度为n的余额序列的最小值
		//因为是前缀和,维护的是很长的前缀和,要减去Sum[i-1]才是真正的Sum
	}
}

int main() {
	n=read(),p=read(),q=read(),x=read(),y=read();
	scanf("%s",s+1);
	for(int i=1; i<=n; i++) {
		if(s[i]=='+') a[i]=1;
		else a[i]=-1;
		a[i+n]=a[i];
		Sum[i]=Sum[i-1]+a[i];//前缀和
	}

	for(int i=n+1; i<=n*2; i++) {
		Sum[i]=Sum[i-1]+a[i];
	}

	Need=(p-q+Sum[n]);//需要多少x变为y(事实上这个是二倍,(1-(-1)=2))
	Arknights();
	ll ans=1192418613;
	for(int i=1; i<=n; i++) {
		int sum;
		if(i==1) sum=0;//相当于没有搬
		else sum=n-i+1;
		ll rst=sum*y+abs(Need/2)*x;//将i位及以后的搬到前面去的所需的代价+取反的代价
		ll v;
		if(Need/2<0) v=p+f[i]-Need;//如果是超过了应有的钱,
		else v=p+f[i];//v=p+Sum[i]-Sum[min];
		if(v<0) rst+=x*2*((abs(v)+1)/2);//写一个好康(懂)的形式
		ans=min(ans,rst);
	}
	printf("%d",ans);
}

```

(p.s:感谢管理员不厌其烦的修改)

---

## 作者：Zwaire (赞：0)

# P3470 [POI2008]BBB-BBB

（~~当时看这题的题面确实很懵逼~~）

##  题目描述

```
一个长度为n的记账单，+ 表示存 ￥1，- 表示取￥1。
现在发现记账单有问题。一开始本来已经存了￥p，
并且知道最后账户上还有 ￥q。
你要把记账单修改正确。
使得 1：账户永远不会出现负数； 
2：最后账户上还有￥q。
你有 2 种操作： 
1：对某一位取反，耗时 x；
2：把最后一位移到第一位，耗时 y。

```

依次输入 n，p，q，x，y，下面的是我操作的字符串

## 题目分析：

### 首先，我们先分析一下两个操作：

$\bullet$ 1. 进行取反，我们暂时没有好的方法

$\bullet$ 2. 把最后一位挪到第一位，这是一个很好的突破点，那我们考虑是不是相当于把整个区间进行向右挪一位呢。

（~~蒟蒻深知无图的痛苦~~）

 
![](https://cdn.luogu.com.cn/upload/image_hosting/osx9arxm.png))


（PS：电脑画图确实没那功底，画的不好请见谅）

根据我们上面的图可以得到，只需要把原来的进行一次倍长，之后挪区间就可以解决这个问题了。

对应有 

```c++
    for(int i = 1; i <= n; ++i)
//进行转化，倍长成链，把第二个操作看成是挪动区间 
    {
        a[i] = s[i] == '+' ? 1 : -1;
        a[i + n] = a[i];
    }
```

那么我们只剩下第一个操作了，我们没有好的方法，对于每一次区间的挪动，只需要暴力算我们的答案就好了。

**但是**，这好像少了点什么。
$$
p+sum_i≥0(1≤i≤n)
$$
我们并不能完成这个操作，所以我们可以在每一个位置维护一个最小值，如果当前的 p 加上最小值还是小于  0，那肯定是不合法了，我们不需要这个操作。

所以，怎么维护最小值呢？？？

**单调队列啊**！！

只是需要维护一个从这个位置开始的最小值就行了。

```c++
/*记录的是后缀的最大值，
其中 b 数组是以 i 这个位置开始，
其以后最小的后缀和（能达到的最低价值），
单调队列
*/
	int head, tail;
    head = tail = 1;
    for(int i = 2 * n; i >= 1; --i)
    {
        if(i <= n) b[i] = sum[i] - sum[que[head]];
        while(head <= tail and sum[que[tail]] <= sum[i]) tail--;
        que[++tail] = i;
        while(head <= tail and que[head] >= i + n) head++;
    }
//十分的简单易懂
```

还有一个小贪心，我们在暴力进行转化的时候，如果我们现在的值大于最终的值，那么我们尽量更新后面的 + 号，并不会影响我们的 b 数组，但是我们的值小于最终值得时候，肯定尽量换前面的 - 号，因此要更新 b 数组。

具体的操作细节请根据注释理解：

```c++
#include<bits/stdc++.h>
#include<map>
#define il inline

using namespace std;
const int N = 1e7 + 10;
const int INF = 0x3f3f3f3f;

il int re()
{
	int x = 0, p = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') p = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
	return x * p;
}

int n, p, q, x, y, ans = INF;
int a[N], sum[N], b[N], que[N];
char s[N];

signed main()
{
    n = re(), p = re(), q = re(), x = re(), y = re();//长度为 n，初始 p 元，改后 q 元 
    scanf("%s", s + 1);
    for(int i = 1; i <= n; ++i)//进行转化，倍长成链，把第二个操作看成是挪动区间 
    {
        a[i] = s[i] == '+' ? 1 : -1;
        a[i + n] = a[i];
    }
    for(int i = 2 * n; i >= 1; --i)//记录前缀和 
    {
        sum[i] = sum[i + 1] + a[i];
    }
/*记录的是后缀的最大值，其中 b 数组是以 i 这个位置开始，
其以后最小的后缀和（能达到的最低价值），单调队列 *、
    int head, tail;
    head = tail = 1;
    for(int i = 2 * n; i >= 1; --i)
    {
        if(i <= n) b[i] = sum[i] - sum[que[head]];
        while(head <= tail and sum[que[tail]] <= sum[i]) tail--;
        que[++tail] = i;
        while(head <= tail and que[head] >= i + n) head++;
    }
    for(int i = 1; i <= n; ++i)
    {
        int now = y * ((n - i + 1) % n);
//考虑我们的问题转化，这里相当于是先硬枚举第二种操作，now 是我现在二操作所需要的值 
        if(p + sum[n + 1] >= q)//这里是我所多出来的部分，需要删去 
        {
            now += (p + sum[n + 1] - q) / 2 * x;
	//根据我的贪心策略，b 肯定先换后面的所以不用更新b 
        }
        else{
            now += (q - p - sum[n + 1]) / 2 * x;
            //这里是我需要补上的 
            b[i] += (q - p - sum[n + 1]);
            //当然，补上的需要更新一下我们的 b[i]，对下面会有影响 
        }
        if(p + b[i] < 0) now -= (p + b[i] - 1) / 2 * 2 * x;
/*这里比较的难理解，p+b[i] 不就是加上当前的最大后缀，
但是还是小于 0 的话，那就相当于在中间就不合法了。注意 */
        ans = min(ans, now);
    }
    cout<<ans;
}
```

完结撒花✿✿ヽ(°▽°)ノ✿。

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3470)

注意到二操作相当于选取一段后缀，截下之后拼在原串的前面，可以考枚举截下后缀的长度，将其拼接后整个串就是已知的了，那么显然，考察每一个位置的前缀和的最小值，若是负数，就必须要进行的相应次数的一操作以保证任意时刻账目都非负，最后再修正加号和减号的数量即可。

考虑如何维护拼接后的每一个位置的前缀和的最小值，可以提前算出原串的前缀 前缀和最小值，这样每次拼接相当于在原串前加上一段，每加一位就更新所有新加位的前缀和最小值，并给后面的串打上标记即可。

总复杂度 $O(n)$。

代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cassert>
#include<vector>
#include<cmath>
#include<set>
using namespace std;
#define ll long long
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;
int readint()
{
	char c=getchar(); int neg=1,ret=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') neg=-1;
	for(;'0'<=c&&c<='9';c=getchar()) ret=(ret<<3)+(ret<<1)+(c&15);
	return neg*ret;
}
ll readll()
{
	char c=getchar(); ll neg=1,ret=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') neg=-1;
	for(;'0'<=c&&c<='9';c=getchar()) ret=(ret<<3)+(ret<<1)+(c&15);
	return neg*ret;
}
void writeint(int x)
{
	if(x==0) {putchar('0'); return;}
	if(x<0) {putchar('-'); x=-x;}
	char stk[15]; int top=0;
	while(x) {int nxt=x/10; stk[++top]=x-nxt*10+'0'; x=nxt;}
	for(int i=top;i>=1;i--) putchar(stk[i]);
}
void writell(ll x)
{
	if(x==0) {putchar('0'); return;}
	if(x<0) {putchar('-'); x=-x;}
	char stk[25]; int top=0;
	while(x) {ll nxt=x/10; stk[++top]=x-nxt*10+'0'; x=nxt;}
	for(int i=top;i>=1;i--) putchar(stk[i]);
}
void Writeint(int x,char c)
{
	writeint(x); putchar(c);
}
void Writell(ll x,char c)
{
	writell(x); putchar(c);
}
bool memBeg;
const int maxlen=1e6+5;
int pre[maxlen],hlp[maxlen];
bool memEn;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n,p,q,x,y;
	cin>>n>>p>>q>>x>>y;
	string s; cin>>s;
	assert(!((n+p-q)&1));
	int cnt=0,minn=(n+q-p)>>1;
	for(int i=0;i<n;i++) cnt+=(s[i]=='+');
	hlp[0]=pre[0]=p+(s[0]=='+'?1:-1);
	for(int i=1;i<n;i++)
	{
		pre[i]=pre[i-1]+(s[i]=='+'?1:-1);
		hlp[i]=min(hlp[i-1],pre[i]);
	}
	int ret=inf,tag=0,ft=inf;
	for(int i=0;i<n;i++)
	{
		int aim=min(ft,hlp[n-i-1])+tag,cnt_=cnt+(aim<0?(-aim+1)>>1:0),ext=(aim<0?(-aim+1)>>1:0)*x;
		ret=min(ret,i*y+ext+x*abs(cnt_-minn)); ft=min(ft,-tag+p); tag+=(s[n-i-1]=='+'?1:-1);
	}
	cout<<ret<<'\n';
	return 0;
}
```

---

