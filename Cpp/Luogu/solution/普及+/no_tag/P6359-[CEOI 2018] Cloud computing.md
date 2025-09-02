# [CEOI 2018] Cloud computing

## 题目背景

译自 CEOI2018 Day1 T1. [Cloud Computing](https://ceoi2018.pl/wp-content/uploads/2018/08/clo.pdf)。

## 题目描述

Johnny 创立了 Bytecomp，一家提供云计算能力的公司。这样的公司通常拥有许多快速的计算机，可以让客户在上面进行计算。

Johnny 仍然没有购买任何机器。他去了一家计算机商店，收到了一个包含所有 $n$ 台可用的计算机的清单。每台计算机都可以用三个属性描述：处理器内核数 $c_i$，时钟频率 $f_i$ 和价格 $v_i$。这样的计算机包含 $c_i$ 个独立的内核，所以他们可以被分配不同的任务。

当客户订购资源时，她会指定所需的内核数 $C_j$ 和最小的时钟频率 $F_j$。订单还包含客户愿意支付的价格 $V_j$。如果接受订单，Bytecomp 需要提供客户所需计算能力的独占访问权。Johnny 需要选择 $C_j$ 个核心（可能来自不同的计算机），且它们的时钟频率至少为 $F_j$，这些核心不能被分配给其它订单。

帮助 Johnny 赚尽可能多的钱：接受一个最优的订单子集，选择所有计算机的一个子集来满足所有接受了的订单。你的目标是最大化利润，即为客户提供计算能力的收入与购买计算机的成本之差。

## 说明/提示

#### 样例解释

一共有四台可用的计算机和三个订单。

最佳方案是购买两台价格为 $700$ 和 $750$（总计 $1450$）的四内核的计算机，然后接受前两个订单获得 $300+1500=1800$ 的收益。

我们获得了四个时钟频率为 $2000$ 的内核，和四个时钟频率为 $2200$ 的内核。可以将其中六个分配给第二个订单（需要 $1900$ 的时钟频率），再将其中一个分配给第一个订单（需要 $1500$ 的时钟频率），剩下一个核心不使用，这是允许的。

总利润为 $1800-1450=350$。

#### 数据规模与约定

对于 $100\%$ 的数据，$1\le n\le 2\times 10^3,\ 1\le c_i,C_i\le 50,\ 1\le f_i,F_i,v_i,V_i\le 10^9$。

所有测试数据被划分成若干个有附加限制的子任务，每个子任务中包含若干测试点。

| 子任务 | 附加限制 | 分值 |
| :--: | :---: | :--: |
| $1$ | $n \le 15$ | $18$ |
| $2$ | $m \le 15$ | $18$ |
| $3$ | $n,m \le 100$，$c_i = C_j = 1$ | $18$ |
| $4$ | $f_i = F_j = 1$ | $18$ |
| $5$ | $v_i = V_j = 1$ | $18$ |
| $6$ | 无附加限制 | $10$ |

## 样例 #1

### 输入

```
4
4 2200 700
2 1800 10
20 2550 9999
4 2000 750
3
1 1500 300
6 1900 1500
3 2400 4550```

### 输出

```
350```

# 题解

## 作者：☯☯枫☯☯ (赞：13)

[题目传送门](https://www.luogu.com.cn/problem/P6359)

~~Day1 T1 就这种难度了……~~

**算法分析：01背包**

拿到题目真没什么思路，先简单讲一下部分分的做法。

- 对于 $\text{Subtask 1,2}$，考虑二进制枚举所有方案，然后计算利润。时间复杂度至少 $\mathcal{O}(2^n)$ 。~~码量比正解还大，就不放了……~~

- 观察 $\text{Subtask 3}$，$c_i=C_j=1$，就是一台计算机恰好完成一个订单，是不是很像匹配？可以用**[二分图带权最大匹配](https://oi-wiki.org/graph/graph-matching/bigraph-weight-match/)或者[最大流](https://oi-wiki.org/graph/flow/max-flow/)**（考试时没想到怎么切这个子任务……如果有更好的方法，欢迎交流）。~~码量更大了……这分还是别切了……~~

- 接下来是最重要的 $\text{Subtask 4}$，$f_i=F_i=1$，那么不需要考虑时钟频率的限制。比较像[01背包问题](https://oi-wiki.org/dp/knapsack/)。$v_i$ 和 $V_i$ 很明显是**价值**了，那么核心数应该就对应**体积**。相信一般的01背包大家都会。可是，这里有两种不同的“物体”，一个是计算机，一个是订单，显然不能分两次做。怎么办呢？那就把它们合到一起。只需要把计算机的价值改为 $-v_i$，在计算内核数时，注意区分加上或者减去，不就可以了吗？

- 最后 $\text{Subtask 5}$，$v_i=V_i=1$，就是买一台计算机，然后用这台计算机尽量解决多的订单。考虑贪心，如果买了这台计算机能赚，那就买，否则不买。（由于没有写过，如有错误，请指出，谢谢！）

**正解：**

事实上，$\text{Subtask 4}$ 的解法已经十分接近正解了。合并后，我们先对时钟功率进行排序，然后**按照时钟功率从大到小进行决策**。这样可以保证**之前买的核心之后一定可以使用**，就避免了原本时钟功率带来的后效性。

**注意：在时钟功率相同时，应当把计算机放在前面，即“先买后卖”。**~~（没买到怎么卖）~~

```cpp
struct P {
	int c,f,v;
	inline void inp(int k) {//input
		c=read(),f=read(),v=k*read();
	}
	bool operator <(const P& a)const {
		if(f==a.f)return v<a.v;
		//计算机的价值为负，所以价值小的优先 
		return f>a.f;
		//时钟功率大的优先 
	}
} a[N];
```

用 $dp_{i,j}$ 表示选到第 $i$ 个“物品”，拥有 $j$ 个核心时的情况。但是很明显会爆空间。那么我们内层**倒序枚举**，除去第一维第 $i$ 个“物品”，**保留 $dp_j$，表示拥有 $j$ 个核心时的最大利润**。
**对于计算机：**

$$dp_{j+c_i}=\max(dp_j+v_i)(j\in \left[0,cnt \right])$$

即：当前有 $j$ 个核心，又买了 $c_i$个，花了 $v_i$元（$v_i$ 是负数），到达状态 $dp_{j+c_i}$。

**对于订单：**

$$dp_j= \max(dp_{j+C_i}+V_i)(j \in\left[0,cnt-C_i\right])$$

即：当前有 $j+C_i$ 个核心，使用 $C_i$ 个核心接了第 $i$ 个订单，得到了 $V_i$ 元。

**记得倒序枚举！**

下面是~~喜闻乐见的~~代码：

```cpp
#include<bits/stdc++.h>
#define reg register
#define F(i,a,b) for(reg int i=(a);i<=(b);i++)
inline int read();
using namespace std;
const int N=4e3+10,M=1e5+10;
int n,m,cnt;
long long dp[M],ans;
struct P {
	int c,f,v;
	inline void inp(int k) {//input
		c=read(),f=read(),v=k*read();
	}
	bool operator <(const P& a)const {
		if(f==a.f)return v<a.v;
		//计算机的价值为负，所以价值小的优先 
		return f>a.f;
		//时钟功率大的优先 
	}
} a[N];
int main() {
	n=read();
	F(i,1,n)a[i].inp(-1);
	m=read();
	F(i,n+1,n+m)a[i].inp(1);
	sort(a+1,a+n+m+1);//排序 
	memset(dp,-0x3f,sizeof(dp));//初始化为极小值 
	dp[0]=0;//边界：dp[0]=0 
	F(i,1,n+m) {
		if(a[i].v<0) {//计算机 
			for(reg int j=cnt; j>=0; j--)//倒序转移 
				dp[j+a[i].c]=max(dp[j+a[i].c],dp[j]+a[i].v);
			cnt+=a[i].c;//cnt记录当前可能最大的核心数 
		} else {//订单 
			F(j,0,cnt-a[i].c)//由于是从下标较大的状态转移过来，事实上也是倒序 
				dp[j]=max(dp[j],dp[j+a[i].c]+a[i].v);
		}
	}
	F(i,0,cnt)ans=max(ans,dp[i]);//取最大值 
	printf("%lld",ans);
	return 0;
}
inline int read() {
	reg int x=0;
	reg char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x;
}
```

[AC](https://www.luogu.com.cn/record/49820226)

欢迎交流讨论，请点个赞哦~

---

## 作者：jianhe (赞：12)

## [P6359 [CEOI2018] Cloud computing](https://www.luogu.com.cn/problem/P6359)
### 算法：贪心+动态规划

- 可以将买进的电脑和订单存到**同一个**结构体数组里面，买进的价格用**负数**表示。

- 要卖出电脑，首先要买进数量 $\ge$ 订单需求的核心数并且时钟频率 $\ge$ 订单需求。因此，我们可以用贪心思想，把电脑按**时钟频率**从大到小排序，保证卖出时，之前买进的时钟频率 $\ge$ 订单需求。

- 排序时，若时钟频率**相同**，买进的电脑应排在前面，不然还没买进就要卖出了，结果显然偏小。

- 排完序后，我们对每一台电脑（订单），都有两种选择：买（卖）或不买（不卖）。很明显是**01 背包**。用 $dp_j$ 表示核心数为 $j$ 时，收获的最大收益。


### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;//不开long long见祖宗 
const ll N=2e5+10;
ll n,m,ct,ans,dp[N];
struct Pc{
	ll c,f,v;
}s[N];
bool cmp(Pc l,Pc r){
	//按时钟频率从大到小排序 
	if(l.f==r.f) return l.v<r.v;
	return l.f>r.f;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i].c>>s[i].f>>s[i].v;
		s[i].v=-s[i].v;//为了区分购进的电脑和订单，电脑的价格用负数存 
	}
	cin>>m;
	for(int i=n+1;i<=n+m;i++) cin>>s[i].c>>s[i].f>>s[i].v;
	//用一个结构体存电脑和订单 
	sort(s+1,s+n+m+1,cmp);
	memset(dp,128,sizeof(dp));
	//初始化收益为无穷小，因为购进电脑时，价格为负 
	dp[0]=0;
	for(int i=1;i<=n+m;i++){
		//01背包 
		if(s[i].v<0){
			for(int j=ct;j>=0;j--)
				dp[j+s[i].c]=max(dp[j+s[i].c],dp[j]+s[i].v);
			ct+=s[i].c;//ct记录当前的核心数，确定dp的范围 
		}else{
			for(int j=0;j<=ct-s[i].c;j++)
				dp[j]=max(dp[j],dp[j+s[i].c]+s[i].v);
		}
	}
	//ans初始化为0，因为不购进任何电脑时，收益为0 
	for(int j=0;j<=ct;j++) ans=max(ans,dp[j]);
	cout<<ans;
	return 0;
}
```

---

## 作者：cqbzhyf (赞：4)

此题可以看作是简单的背包问题+贪心……

然后你会发现它要开 long long 

### 排序规则

```cpp
inline bool cmp(Q x,Q y){return x.f==y.f?x.v<y.v:x.f>y.f;}
```

如图，按照 $f_i$ 从大到小排序，如果 $f_i$ 相等，则按照 $v_i$ 从小到大排序（贪心），比较大的 $f_i$ 可以满足更多的需求，而当 $f_i$ 相等，自然要选择比较小的 $v_i$。

### 动态规划的定义

首先是一个 $dp$ 一维数组， $dp_i$ 表示使用 $i$ 个内核可以获得的最大利润，而该题涉及两个操作，即买入和卖出，买入的价格为了和卖出统一，就变成负数。

注意排序要将 $n+m$ 个信息进行操作！用 $tot$ 来存储当前的核心数，方便进行背包处理，处理是最基础的背包问题（0/1 背包）。

### 答案的枚举

循环区间 $0$ ~ $tot$，求取 $dp$ 的最大值

#### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,dp[200005],tot,ans;
struct Q{
	int c,f,v;
}a[4005];
inline bool cmp(Q x,Q y){return x.f==y.f?x.v<y.v:x.f>y.f;}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
signed main(){
	memset(dp,128,sizeof(dp));
	dp[0]=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld %lld %lld",&a[i].c,&a[i].f,&a[i].v);
		a[i].v=-a[i].v;
	}
	scanf("%lld",&m);
	for(int i=n+1;i<=n+m;++i){
		scanf("%lld %lld %lld",&a[i].c,&a[i].f,&a[i].v);
	}
	stable_sort(a+1,a+1+n+m,cmp);
	for(int i=1;i<=n+m;++i){
		if(a[i].v<0){
			for(int j=tot;j+1;--j)dp[j+a[i].c]=max(dp[j+a[i].c],dp[j]+a[i].v);
			tot+=a[i].c;
		}else{
			for(int j=0;j<=tot;++j)dp[j]=max(dp[j],dp[j+a[i].c]+a[i].v);
		}
	}
	for(int i=0;i<=tot;++i)ans=max(ans,dp[i]);
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：Harry_Hedwig (赞：4)

# 0x00 思路
先看题。
>Johnny 仍然没有购买任何机器。他去了一家计算机商店，收到了一个包含所有 $n$ 台可用的计算机的清单。每台计算机都可以用三个属性描述：处理器内核数 $c_i$，时钟频率 $f_i$ 和价格 $v_i$。这样的计算机包含 $c_i$ 个**独立**的内核，所以他们**可以被分配不同的任务**。

>当客户订购资源时，她会指定所需的内核数 $C_j$ 和**最小**的时钟频率 $F_j$。订单还包含客户愿意支付的价格 $V_j$。如果接受订单，Bytecomp 需要提供客户所需计算能力的独占访问权。Johnny 需要选择 $C_j$ 个核心（**可能来自不同的计算机**），且它们的**时钟频率至少**为 $F_j$，**这些核心不能被分配给其它订单**。

>帮助 Johnny 赚**尽可能多**的钱：接受一个最优的**订单子集**，选择所有计算机的**一个子集**来满足所有接受了的订单。**你的目标是最大化利润，即为客户提供计算能力的收入与购买计算机的成本之差**。

那么，对于所有操作（无论是买计算机还是接受订单）都有两种操作：买（接受）或是不买（不接受）。那么我们很容易想到这些操作是非黑即白的，所以这是一个典型的 01 背包。

既然是背包，那么就需要两个东西：定义状态和状态转移方程。

# 0x01 前置
但是，在这个时候我们发现不好操作状态，所以需要再次读题。

接着，我们可以发现这两个操作是有相似点的。

为什么呢？

因为它们都有 $3$ 个参数，而且它们的参数表达的含义差不多，所以我们可以把这两个操作变为一个操作。

但是由于买电脑是支出，订单是收入，所以买电脑的价格应该取相反数。

而且由于在这里面最重要的是时钟频率，所以我们应该用时钟频率从大到小排序（因为越大越有用），在时钟频率相同时应该用价格小的排在前面（你总应该先买电脑吧……）。

# 0x02 定义状态
定义 `d[i][j]`：表示在前 `i` 个选择订单和电脑后剩下 `j` 个内核所获得的最大利润。当然，既然要最大，而且有负数，所以应该把 `d[i][j]` 赋极小值。

# 0x03 状态转移方程
当然，由于这里是两种不同的东西放在这里，所以我们也应该用不同的方式处理它们。

- 当 $v_i<0$ 时，说明是电脑。我们假设此时我们有 $j+c_i$  个内核，那么由于我们可以选择买或不买，所以 `d[i][j+c[i].c]=max(d[i-1][j+c[i].c],d[i-1][j]+c[i].v)`。

- 当 $v_i>0$ 时，说明是客户。我们假设此时有 $j$ 个内核，那么由于我们可以选择接或不接，所以 `d[i][j]=max(d[i-1][j],d[i-1][j+c[i].c]+c[i].v)`。

最后全部走一遍，找最大值即可。

# code
**不开 `long long` 见祖宗！！！**

```c++
/*众所周知，01 背包是可以压缩的，所以我们可以把第一维省略掉。*/
#include<bits/stdc++.h>
using namespace std;
typedef struct Bytecomp
{
	long long cor,fre,pri;//c,f,v
}BYTE;
BYTE com[4005];
bool cmp(BYTE a,BYTE b)
{
	return a.fre==b.fre?a.pri<b.pri:a.fre>b.fre;
}
long long d[1000005],x;
int main()
{
	int n,m,i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%lld %lld %lld",&com[i].cor,&com[i].fre,&com[i].pri),com[i].pri*=-1;
	scanf("%d",&m);
	for(i=1;i<=m;i++)
		scanf("%lld %lld %lld",&com[i+n].cor,&com[i+n].fre,&com[i+n].pri);
	sort(com+1,com+1+n+m,cmp);
	memset(d,128,sizeof(d));
	d[0]=0;
	for(i=1;i<=n+m;i++)
	{
		if(com[i].pri<0)
		{
			for(j=x;j>=0;j--)//x为假设我买了所有电脑然后没有买任何核心的核心总数
				d[j+com[i].cor]=max(d[j+com[i].cor],d[j]+com[i].pri);
			x+=com[i].cor;
		}
		else
			for(j=0;j<=x-com[i].cor;j++)
				d[j]=max(d[j],d[j+com[i].cor]+com[i].pri);
	}
	long long ans=0;
	for(i=0;i<=x;i++)
		ans=max(ans,d[i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Jasonshan10 (赞：2)

## 前置知识

$01$ 背包，指每个物品最多只能取一次的背包，时间复杂度 $O(nm)$，空间复杂度 $O(n)$。

## 思路

这道题就是**贪心和 $01$ 背包**，一道较好的 $DP$ 题。

### 如何转化

我们可以把原计算机定义为**真计算机**，顾客需求的计算机定义为**假计算机**。

将真计算机和假计算机一起做背包。

但是这道题还有频率这一个参数，所以我们考虑贪心。

对于这 $n+m$ 台计算机按照时钟频率从低到高排序，就能保证状态转移一定是**时钟频率高的转移到时钟频率低的**。

如果时钟频率一样，则真计算机放在前面，假计算机放在后面。对于此，我们可以让**真计算机所有的价值变为负数**。

### 如何做

**首先考虑状态的定义：**

$dp[i][j]$ 表示考虑前 $i$ 台计算机，能够获得 $j$ 个核心时，所能获得的最大价值。

当然，第一维可以优化，$dp[i]$ 表示能够获得 $i$ 个核心时，所能获得的最大价值。

**接着考虑状态转移方程。**

对于 $n$ 台**真**计算机，可得状态转移方程：

```cpp
dp[j+p[i].c]=max(dp[j+p[i].c],dp[j]+p[i].v); 
```

对于 $m$ 台**假**计算机，可得状态转移方程：

```cpp
dp[j]=max(dp[j],dp[j+p[i].c]+p[i].v);
```

有了状态转移方程，我们可以**考虑初始化**。因为要取 $\max$，所以开始所有数都要赋最小值，当然 $dp[0]$除外。

在这其中，我们可以用 $cnt$ 记录总共核心数量。

**输出答案时**，我们只需要让 $i$ 从 $0$ 枚举到 $cnt$，取 $\max$ 即可。

## 代码

[AC 记录](https://www.luogu.com.cn/record/118775433)

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2*1e3+5;
const int MAXM=2*1e5+5;
ll n,m;
ll dp[MAXM];
ll cnt,ans;
struct node{
	ll c,f,v;
}p[MAXN*2];
bool cmp(node x,node y){
	if (x.f!=y.f){
		return x.f>y.f;
	}
	return x.v<y.v;
}
int main(){
	memset(dp,-0x3f,sizeof(dp));
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld %lld %lld",&p[i].c,&p[i].f,&p[i].v);
		p[i].v=-p[i].v;
	}
	scanf("%lld",&m);
	for(int i=n+1;i<=n+m;++i){
		scanf("%lld %lld %lld",&p[i].c,&p[i].f,&p[i].v);
	}
	sort(p+1,p+n+m+1,cmp);
	dp[0]=0;
	for(int i=1;i<=n+m;++i){
		if (p[i].v>0){
			for(int j=0;j<=cnt;++j){
				dp[j]=max(dp[j],dp[j+p[i].c]+p[i].v);
			}
		}
		else{
			for(int j=cnt;j>=0;--j){
				dp[j+p[i].c]=max(dp[j+p[i].c],dp[j]+p[i].v);
			}
			cnt=cnt+p[i].c;
		}
	}
	for(int i=0;i<=cnt;++i){
		ans=max(ans,dp[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：2)

### 前置知识：
[01背包](https://baike.baidu.com/item/01%E8%83%8C%E5%8C%85/4301245?fr=aladdin)，为每个物品只能取一次的背包，通常的写法为时间 $O(nm)$，空间 $O(n)$，利用这种方法就行了。
### 思路
首先，我们输入完了以 $f$ 从大到小排序，如果相同，卖的排前面，可以使选择更多，然后我们就可以用类似 01 的方法来做，首先求出满足订单的所有核心数，然后我们使用 dp。枚举 j 为核心数，卖出的状态专题方程式为 $dp_{j+p_i.a} \gets \max{dp_{j+p_i.a},dp_j-p_i.c}$，此处要正序枚举；买入的状态转移方程 $dp_{j+p_i.a} \gets \max{dp_{j+p_i.a},dp_j-p_i.c}$，此处倒叙枚举，注意核心数 $sum\gets sum+p_i.c$。最后答案为 i 从 0 到 sum 的 $dp_i$ 的最大值，初始状态全部为极小值，因为要取 max。时间复杂度和和空间复杂度均为 $O(\sum\limits_{i=1}^n\ p_i.a)$，可以过。
### AC Code:
```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
int n,m,tot,dp[1000005],ans,sum;
inline int read(){
	int a;
	scanf("%lld",&a);
	return a;
}
struct node{
	int a,b,c;
	bool p;
	bool operator <(const node &t) const{
		if(b==t.b)
			return p<t.p;
		return b>t.b;//排序
	}
}p[4005];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		p[i]=node({read(),read(),read(),0});
	scanf("%lld",&m);
	for(int i=1;i<=m;i++)
		p[i+n]=node({read(),read(),read(),1});
	sort(p+1,p+n+m+1);
	memset(dp,-0x3f,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=m+n;i++){
		if(p[i].p){
			for(int j=0;j<=sum-p[i].a;j++)
				dp[j]=max(dp[j],dp[j+p[i].a]+p[i].c);
		} else{
			for(int j=sum;j>=0;j--)
				dp[j+p[i].a]=max(dp[j+p[i].a],dp[j]-p[i].c);
			sum+=p[i].a;
		}//状态转移比较好想
	}
	for(int i=0;i<=sum;i++)
		ans=max(ans,dp[i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：PosVII (赞：1)

**前言**

------------

暂居速度榜一。

这是一道简单背包，建议评绿。

**分析**

------------

无论如何，我们都能想到一个优化：我们可以将电脑和订单在一起以 $f$ 为第一关键字，$v$ 为第二关键字进行排序，这样我们就能保证在当前订单中，我们之前所买的所有内核都有用。

然后打优先队列存储输入。再来分析这道题，它就变成了一道简单的背包，压缩成一维即可通过。

这里有一个比其它代码更快的优化：我们单独拿出来一个布尔类型变量存储目前订单是属于购入还是卖出，可以优化约 $10ms$。

**code:**

------------

```
#include<bits/stdc++.h>
using namespace std;
#define min(x,y) x<y?x:y
const int N=1e5;
struct node{
	int c,f,v;
}t1;
bool operator<(const node &a,const node &b) {
	if(a.f==b.f) return a.v>b.v;
    return a.f<b.f;
}
priority_queue<node> q;
int n,m,sum;
long long dp[N+5],ans;
int main() {
	memset(dp,-128,sizeof(dp));
	dp[0]=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d %d %d",&t1.c,&t1.f,&t1.v);
		t1.v=-t1.v;
		q.push(t1);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;++i) {
		scanf("%d %d %d",&t1.c,&t1.f,&t1.v);
		q.push(t1);
	}
	while(!q.empty()) {
		t1=q.top();
		q.pop();
		if(t1.v>0) {
			for(int i=0;i+t1.c<=sum;++i) {
				dp[i]=max(dp[i+t1.c]+t1.v,dp[i]);
			}
		}
		else {
			sum+=t1.c;
			for(int i=sum;i-t1.c>=0;--i) {
				dp[i]=max(dp[i-t1.c]+t1.v,dp[i]);
			}
		}
	}
	for(int i=0;i<=sum;++i) ans=max(ans,dp[i]);
	printf("%lld",ans);
	return 0;
} 
/*
4 5 5 6 6
4 3 3 4 1
*/
```

---

## 作者：rq_kyz (赞：0)

# 【题解】 P6359 [CEOI2018] Cloud computing

### 传送门

[P6359 [CEOI2018] Cloud computing](https://www.luogu.com.cn/problem/P6359)

---

### 题意

现有 $n$ 台计算器，每个计算器有三个属性：内核数 $c_i$，时钟频率 $f_i$ 和价格 $v_i$。每台计算器的内核可以**在进货后**单独拆下来卖给客户（只能以计算机为单位购买内核，不能单独购买一个或多个内核）。

现有 $m$ 位顾客，每位顾客会指定他的订单的三个参数：他需要的内核数 $C_j$，每个内核至少的时钟频率 $F_j$ 以及他愿意支付的价格 $V_j$。

现在问应该购买哪些计算机、接哪些订单才能使利润最大化。输出最大的利润。

---

### 分析

本题毋庸置疑是一道 dp。但是我们为了统一，可以把每台计算机也看作一笔订单，只需要将价格转为负数，就实现了计算机和订单的统一。

这还不够，为了使时钟频率大于等于客户要求的，我们可以在输入完之后将所有的计算器和订单全部进行排序（因为已经统一），排序规则为时钟频率越大越靠前（这样前面买的计算机的内核就可以给后面的订单），频率一样的计算机在前面（因为要先买才能卖）。

到现在，正式 dp 之前的工作我们就处理完了，但 dp 状态还需要思考。可以肯定的是 dp 状态一定是二维的（数据范围只有 $2\times10^3$），而且第一维肯定是枚举计算机加订单。第二维也很好确定，我这里就直接给答案了，第二维枚举当前还剩下的内核个数。这里我们并不用记录每个内核的时钟频率，是因为在上面我们已经进行排序。

状态转移却有点麻烦。我们需要记录当前最多有可能的内核总数，因为这是 dp 第二维的范围。但如果我当前枚举到的是一台计算器，那么就算我记录了当前的数量，也不可能把之前所有的都记录一遍。所以我们可以反过来，用我当前这个去更新后面的，这样我循环的范围就是我记录的总数。至于我当前如果枚举到的是一笔订单，则与之前不变，用前面的更新我当前的。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct s{
	ll c,f,v;
}a[4001];
ll dp[100001];
bool f(s num1,s num2){//根据时钟频率从大到小排序，一样的再将计算机放在前面（价格从小到大）
	return num1.f==num2.f?num1.v<num2.v:num1.f>num2.f;
}
int main(){
	ll n,m;
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		scanf("%lld%lld%lld",&a[i].c,&a[i].f,&a[i].v);
		a[i].v=-a[i].v;//价格转为负数，实现统一
	}
	scanf("%lld",&m);
	for(ll i=1;i<=m;i++)
		scanf("%lld%lld%lld",&a[i+n].c,&a[i+n].f,&a[i+n].v);
	sort(a+1,a+n+m+1,f);
	memset(dp,0x80,sizeof(dp));
	dp[0]=0;
	ll now=0;//当前的内核总数
	for(ll i=1;i<=n+m;i++){
		if(a[i].v<0){//当前为计算机
			for(ll j=now;j>=0;j--)
				dp[j+a[i].c]=max(dp[j+a[i].c],dp[j]+a[i].v);//用自己去更新后面的状态
			now+=a[i].c;//更新
		}
		else//当前为订单
			for(ll j=0;j<=now-a[i].c;j++)
				dp[j]=max(dp[j],dp[j+a[i].c]+a[i].v);//用前面的状态更新自己
	}
	ll max_=0;
	for(ll j=0;j<=now;j++)
		max_=max(max_,dp[j]);
	printf("%lld",max_);
	return 0;
}
```

---

## 作者：FLORIZ (赞：0)

发现计算机和订单的信息是一样的，所以完全可以放在一起考虑，存到一起。

如果只考虑机核数量或者时钟频率，这就是比较经典的背包 dp，只不过有些物品的价值是负值。

时钟频率的限定需要满足选中的机核都满足，不太好作为 dp 的限定条件。但我们发现时钟频率能否选择是单调的，所以可以给所有计算机和订单按时钟频率排序，显然这样选中的机核都是满足时钟频率限定的。注意这里时钟频率相同的要计算机优先，要不然容易落下一些符合条件机核导致答案偏小。

这里就变成一个经典的 01 背包了，机核数可以看作体积，计算机或者订单就是物品，递推的时候判断一下是计算机还是订单就好了。当然如果你喜欢递归和比较大的常数你也可以 dfs。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
	{long long f(1),x(0);
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	return f*x;
	}
#define debug(x) cout<<"###"<<x<<endl;

#define maxn 2010
long long n,m,ans,cnt;
struct com
	{long long c,f,v;
	bool friend operator <(const com& x,const com& y)
		{if(x.f!=y.f) return x.f>y.f;
		else return x.v<y.v;
		}
	} ji[maxn<<1];

long long f[maxn*50];

int main()
	{n=read();
	for(long long i=1;i<=n;i++)
		{ji[i].c=read();
		ji[i].f=read();
		ji[i].v=read();
		ji[i].v*=-1;
		}
	m=read();
	for(long long i=n+1;i<=n+m;i++)
		{ji[i].c=read();
		ji[i].f=read();
		ji[i].v=read();
		}
	
	sort(ji+1,ji+1+n+m);
	memset(f,-51,sizeof(f));
	f[0]=0;
	for(long long i=1;i<=n+m;i++)
		{if(ji[i].v<0)
			{for(long long j=cnt;j>=0;j--)
				{f[j+ji[i].c]=max(f[j+ji[i].c],f[j]+ji[i].v);
				}
			cnt+=ji[i].c;
			}
		else
			{for(long long j=0;j<=cnt-ji[i].c;j++)
				{f[j]=max(f[j],f[j+ji[i].c]+ji[i].v);
				}
			}
		}
	
	for(long long i=0;i<=cnt;i++)
		{ans=max(ans,f[i]);
		}
	cout<<ans<<endl;
	return 0;
	}
```


---

## 作者：ybc2025chenyuyang (赞：0)

# P6359 [CEOI2018] Cloud computing 题解
一道学校周考题，当时想到了背包，但没做出来，我太菜了。
## 思路
这道题我们略微要用一下贪心的思想。

我们现在输入的时候预处理一下，即把输入的买进价格，也就是 $V_{i}$，转化成负数。然后按照时钟频率，也就是 $F_{j}$，按照从大到小的顺序排序。如果时钟频率相同，就要将价格从小到大排序（此时买进的价格变成了负数）。

具体排序代码如下。
```cpp
if(a.f==b.f){
	return a.v<b.v;
}
return a.f>b.f;
```
然后，我们就可以开始背包了。

我们通过分析题目，可以知道，此题是01背包，因为每一台电脑都有选与不选两种情况。

因此，我们设 $dp_{j}$ 为当核心数为 $j$ 时的最大利润。然后由于电脑分为买进和卖出两种情况，所以我们应当分类讨论。

### 对于买进的计算机
对于买进的计算机，思路比较好想，状态转移方程式如下。

$dp_{j+C_{i}}=\max\left\{dp_{j}+V_{i}\right\}$，其中 $j\in [0,cnt]$。

$cnt$ 为截止当前的买进的电脑的核心总数，循环为倒序。

### 对于订单
状态转移方程式如下。

$dp_{j}=\max\left\{dp_{j+C_{i}}+V_{i}\right\}$，其中 $j\in [0,cnt]$。循环为正序。

### Last
只需要从 $0$ 到 $cnt$ 枚举 $dp_{i}$ 的最大值就可以了，下面上代码。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,cnt,dp[2000005];
struct node{
	long long c,f,v;
	friend bool operator<(node a,node b){
		if(a.f==b.f){
			return a.v<b.v;
		}
		return a.f>b.f;
	}
}a[10005];
int main(){
	memset(dp,-0x3f3f3f3f,sizeof dp);
	dp[0]=0;
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>a[i].c>>a[i].f>>a[i].v;
		a[i].v=-a[i].v;
	}
	cin>>m;
	for(long long i=n+1;i<=m+n;i++){
		cin>>a[i].c>>a[i].f>>a[i].v;
	}
	sort(a+1,a+n+m+1);
	for(long long i=1;i<=n+m;i++){
		if(a[i].v<0){
			for(long long j=cnt;j>=0;j--){
				dp[j+a[i].c]=max(dp[j+a[i].c],dp[j]+a[i].v);
			}
			cnt+=a[i].c;
		}else{
			for(long long j=0;j<=cnt;j++){
				dp[j]=max(dp[j],dp[j+a[i].c]+a[i].v);
			}
		}
	}
	long long maxn=LONG_LONG_MIN;
	for(long long i=0;i<=cnt;i++){
		maxn=max(maxn,dp[i]);
	}
	cout<<maxn;
	return 0;
}
```


---

## 作者：cqbzjyh (赞：0)

### 思路

首先考虑贪心，按 $f$ 进行从小到大排序。特别的，当 $f$ 相等时，就按价格进行排序。

然后我们就可以用类似 01 背包的方法，为了方便，我们可以将计算机的价格置为负数。定义状态 $dp_j$ 表示内核数为 $j$ 时所得的最大利润。背包容量即为所购买的计算机内核的总和 $tot$。

所以状态转移方程即为

$$ 
dp_{j+c_i}\gets \max dp_{j+c_i}, dp_j+v_i
$$

这里要注意的是，当处理的是计算机时需要倒叙枚举，反正则倒叙

时间复杂度 $O((n+m)\displaystyle\sum_{i=1}^n p_i)$

### Code.
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
struct node {
	int c, f, v;
} a[4005];
bool cmp(node x, node y) {
	return x.f == y.f ? x.v < y.v : x.f > y.f;
}
int dp[200005], tot;
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
    	scanf("%lld %lld %lld", &a[i].c, &a[i].f, &a[i].v);
    	a[i].v *= -1;
	}
	scanf("%lld", &m);
	for (int i = n + 1; i <= m + n; i++) {
		scanf("%lld %lld %lld", &a[i].c, &a[i].f, &a[i].v);
	}
	sort(a + 1, a + n + m + 1, cmp);
	memset(dp, 128, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= n + m; i++) {
		if (a[i].v < 0) {
			for (int j = tot; j >= 0; j--) dp[j + a[i].c] = max(dp[j + a[i].c], dp[j] + a[i].v);
			tot += a[i].c;
		} else {
            for (int j = 0; j <= tot; ++j) dp[j] = max(dp[j], dp[j + a[i].c] + a[i].v);
        }
	}
	int ans = 0;
	for (int i = 0; i <= tot; i++) {
		ans = max(ans, dp[i]);
	}
	printf("%lld", ans);
    return 0;
}
```

---

## 作者：Liynw (赞：0)

### 前言

[题目链接](https://www.luogu.com.cn/problem/P6359)

我们教练十分努力，竟然找到了这个只有一百多人做的题目。

这是一道比较有思维难度的 01 背包题，建议评绿或者蓝？

***

### 确定容量和价值

~~这个输入的变量名很显然就是在提示你把计算机和客户订单混在一起嘛。~~

我们可以发现，对于每一个计算机，只有**买或不买两种情况**；对于每一个单子，只有**接或不接两种状态。** 而能不能接客户的单子取决于内核的数量够不够。于是，我们想到了这道题的算法——01 背包，内核数量相当于容量，钱相当于价值。

但是这时就有了一个问题：我怎么确定内核的数量？

注意到题目中还有另一个条件——时钟频率。因为客户要求有一个对于时钟频率的限制，换句话说，就是**每一个客户能使用的最大内核数量是确定的**。

所以我们可以把计算机和客户的单子放在一个结构体数组里面，拿一个 `bool` 区分一下计算机和客户。然后，按照时钟频率排序。

此时，对于任意一个客户的单子，它**前面的**所有内核数量之和就是对于它来说可以使用的最大内核数。

这里需要注意一点：如果时钟频率一样，计算机排在前面。如果类型和时钟频率都一样，计算机把价格低的排在前面，客户把价格高的排在前面。

```cpp
bool cmp(node x, node y) {
	if(x.f != y.f)
		return x.f > y.f;
	if(x.data != y.data)
		return x.data < y.data;
	if(!x.data) 
		return x.v < y.v;
	return x.v > y.v;
}
```

***

### 状态转移

接着就到了比较难的地方。

设 $dp_{i,j}$ 代表处理了前 $i$ 个请求之后还剩下 $j$ 个可用的内核时能获得的最大利润。

经上文分析，对于计算机和客户都有两种状态。那么，选择哪种更优呢？

我们用一个变量 $C$ 来统计**到目前为止**内核的总数量，相当于一个前缀和。然后分析：

#### 对于计算机

买的话，需要花钱，但是内核数量会增加。那么相对买之前来说，买后内核数量增加了 $c_i$，也就是说买之前内核数量比现在少 $c_i$，而买后，现在有的钱数量相较于买之前减少了 $v_i$，所以结果表达式如下：

$$dp_{i-1,j - c_i} - v_i$$

至于 $j$ 的循环范围很简单，保证数组下标不超过 $0\sim n$ 的范围即可。

所以就有对于计算机的状态转移方程：

$$dp_{i,j}=\max^{C}_{j=c_i}\{dp_{i-1,j-c_i}-v_i\}$$

对了，记得在转移之前把前缀和加上。

#### 对于客户

接客户的单子，可用的内核数量会减少，但会收获钱。那么接后相对于接前少了 $c_i$ 个内核，但钱增加了 $v_i$，所以结果表达式如下：

$$dp_{i-1,j+c_i}+v_i$$

那状态转移方程就是这样：

$$dp_{i,j}=\max^{C-c_i}_{j=0}\{dp_{i-1,j+c_i}+v_i\}$$

***

### 滚动数组

开二维数组空间不够，于是自然想到了让数组打滚。然而，滚起来之后，$j$ 到底该从小到大还是从大往小？

这个顺序只取决于一个因素，就是这个状态转移方程**所使用的** $dp$ 值在**需要求的值**的前面还是后面。如果在前面，就需要倒着枚举，如果在后面，就要正着枚举，以保证利用的是本来为 $dp_{i-1,?}$ 而非 $dp_{i,?}$。

所以，处理购买计算机的请求要从大到小枚举，处理客户单子需要从小到大枚举。

注意一下初始值，数组赋极小值，$dp_{0}=0$。

```cpp
for(int i = 1; i <= num; i++) {
	if(!a[i].data) { // 计算机 
		C += a[i].c;
		for(int j = C; j >= a[i].c; j--)
			dp[j] = std :: max(dp[j], dp[j - a[i].c] - a[i].v);
	} else { // 客户 
		for(int j = 0; j <= C - a[i].c; j++) 
			dp[j] = std :: max(dp[j], dp[j + a[i].c] + a[i].v);
	}
}
```

***

### 求答案

非常简单，长这样：

$$ans=\max_{i=\color{#FF0000}{0}}^{C}\{dp_i\}$$

注意我标红的地方，$i$ 的初始值为 $0$。

我最开始做的时候以为这个地方初始值是 $1$，因为 $ans$ 初始值就是 $0$ 嘛！于是喜提 $\text{18pts}$……

其实最终 $dp_0$ 不一定是没有购买计算机，也有可能是**内核数量刚好消耗完**。

~~Peter：这其实就和牛顿第一定律一样嘛，要么不受外力，要么合力为零，两种情况嘛。~~

~~我承认你说得很有道理，但是你是物理学疯了？~~

***

### Code

不开 `long long` 见祖宗。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long

const int maxn = (int) 2e5 + 5;

struct node { int c, f, v; bool data; } a[4005];
int C, n, m, num, ans, dp[maxn];

bool cmp(node x, node y) {
	if(x.f != y.f)
		return x.f > y.f;
	if(x.data != y.data)
		return x.data < y.data;
	if(!x.data) 
		return x.v < y.v;
	return x.v > y.v;
}

signed main() {
	memset(dp, -0x3f, sizeof(dp));
	dp[0] = 0;
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lld %lld %lld", &a[i].c, &a[i].f, &a[i].v);
		a[i].data = 0;
	}
	scanf("%lld", &m);
	for(int i = n + 1; i <= n + m; i++) {
		scanf("%lld %lld %lld", &a[i].c, &a[i].f, &a[i].v);
		a[i].data = 1;
	}
	num = m + n;
	std :: stable_sort(a + 1, a + num + 1, cmp);
	/*
	for(int i = 1; i <= num; i++) 
		printf("%d %d %d %d\n", a[i].c, a[i].f, a[i].v, a[i].data);
	*/
	for(int i = 1; i <= num; i++) {
		if(!a[i].data) { // 计算机 
			C += a[i].c;
			for(int j = C; j >= a[i].c; j--)
				dp[j] = std :: max(dp[j], dp[j - a[i].c] - a[i].v);
		} else { // 客户 
			for(int j = 0; j <= C - a[i].c; j++) 
				dp[j] = std :: max(dp[j], dp[j + a[i].c] + a[i].v);
		}
	}
	for(int i = 0; i <= C; i++)
		ans = std :: max(ans, dp[i]);
	printf("%lld", ans);
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/62378782)

---

## 作者：Martian148 (赞：0)

# Link
[P6359 [CEOI2018]Cloud computing](https://www.luogu.com.cn/problem/solution/P6359)

# Solve
这道题初看又是核心，又是电脑的很复杂，但是观察发现对于一同一台个电脑，核心频率都是一样的，对于一个任务，需要的核心的频率也是一样的

就想到把任务和电脑混在一起，按核心频率排序后处理。

每一个电脑或一个任务都可以考虑选或不选，于是就变成一个背包问题了，把电脑和任务都看成一个物品，频率是物品的大小，钱是物品的价值，$tot$是背包大小

如果是电脑，选的话要给别人钱，所以价值为$-V[i]$

如果是物品，要占核心，相对于电脑是反的，所以大小为$-C[i]$(这句话没理解也没关系，看下面的代码就知道，负负得正嘛~)

对于背包大小，如果加进来一个电脑，就相当于多了几个核心，$tot$要加上$C[i]$

处理前先按核心从大到小排序，就可以保证每次坐任务的时候前面的任何一个核心都可以做

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2005,maxm=2000005;
typedef long long LL;
int N,M,tot;
struct AS{
	int c,f,v;
	bool operator <(const AS B)const {return f>B.f||(f==B.f&&v<B.v);}
}a[maxn<<1];
LL F[maxm],ans;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	freopen("cloud.in","r",stdin);
	freopen("cloud.out","w",stdout);
	N=read();for(int i=1;i<=N;i++)a[i].c=read(),a[i].f=read(),a[i].v=-read();
	M=read();for(int i=1;i<=M;i++)a[i+N].c=-read(),a[i+N].f=read(),a[i+N].v=read();
	sort(a+1,a+1+N+M);
	memset(F,128,sizeof F);F[0]=0;
	for(int i=1;i<=N+M;i++){
		if(a[i].c>0){//电脑 
			for(int j=tot;j>=0;j--)
				F[j+a[i].c]=max(F[j+a[i].c],F[j]+a[i].v);
				tot+=a[i].c;
		}
		else {//任务 
			for(int j=0;j<=tot+a[i].c;j++)
				F[j]=max(F[j],F[j-a[i].c]+a[i].v);
		}
	}
	for(int i=0;i<=tot;i++)ans=max(ans,F[i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ModestCoder_ (赞：0)

用背包做，如果可以直接枚举物品以及核心数量

复杂度是$4000*50*2000=4e8$差不多可以

那么我们基本上就知道怎么做了

想着怎么把$f$的限制去掉

可以直接按照$f$从大到小排序，那么我们就能保证现在手里面拥有的肯定都可以用来做任务

然后就做一个背包

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 2010
#define maxm 200010
#define LL long long
using namespace std;
const LL inf = 1e12;
struct data{
	int c, v, f;
}a[maxn << 1];
LL dp[maxm];
int n, m;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

bool cmpf(data x, data y){
	return x.f == y.f ? x.v < y.v : x.f > y.f;
}

int main(){
	freopen("cloud.in", "r", stdin);
//	freopen("cloud.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; ++i){
		a[i].c = read(), a[i].f = read(), a[i].v = -read();
	}
	m = read();
	for (int i = 1; i <= m; ++i){
		a[n + i].c = read(), a[n + i].f = read(), a[n + i].v = read();
	}
	sort(a + 1, a + 1 + m + n, cmpf);
	dp[0] = 0;
	for (int i = 1; i < maxm; ++i) dp[i] = -inf;
	LL cnt = 0;
	for (int i = 1; i <= n + m; ++i){
		if (a[i].v < 0){
			for (int j = cnt; j >= 0; --j)
				dp[j + a[i].c] = max(dp[j + a[i].c], dp[j] + a[i].v);
			cnt += a[i].c;
		} else{
			for (int j = 0; j <= cnt; ++j)
				dp[j] = max(dp[j], dp[j + a[i].c] + a[i].v);
		}
	}
	LL ans = 0;
	for (int i = 0; i <= cnt; ++i) ans = max(ans, dp[i]);
	printf("%lld\n", ans);
	return 0;
}
```


---

