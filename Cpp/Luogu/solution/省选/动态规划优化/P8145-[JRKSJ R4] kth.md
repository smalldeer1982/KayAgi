# [JRKSJ R4] kth

## 题目背景

> 时刻记住自己是人类，不是动物。

在吃玉米番茄炖山羊肉之前，你需要回答一个问题。

## 题目描述

给定 $n,m$，称一个“合法”的整数序列为（设该序列为 $s$）：

* $s$ 长度为 $m$。
* $\forall i\in[1,m],s_i\in[1,n]$。
* $\forall i\in[2,m],|s_i-s_{i-1}|=1$。

给定一个 $[1,n]$ 的排列 $p$，并定义一个整数序列 $s$ 的“对应序列” $s'$：$s'$ 的长度和 $s$ 相同；设其长度为 $l$，那么 $\forall i\in [1,l],s'_i=p_{s_i}$。

再给定 $k$，求所有不同的合法的整数序列的对应序列中，字典序第 $k$ 小的对应序列中所有元素的和对 $2^{32}$ 取模的值。

若不存在第 $k$ 小的对应序列，输出 $-1$。

## 说明/提示

**本题输入文件较大，请使用恰当的读入方式。**

### 样例解释
对于样例 $1$，所有不同的合法的整数序列的对应序列中，字典序前三小的分别是：

$$\{1,9,1,9,1,9\}$$
$$\{1,9,1,9,8,9\}$$
$$\{1,9,1,9,8,10\}$$

所以答案为 $1+9+1+9+8+10=38$。

对于样例 $2$，所有不同的合法的整数序列的对应序列中，字典序前二小的分别是：

$$\{1,2,1,2,1\}$$
$$\{2,1,2,1,2\}$$

所以答案为 $2+1+2+1+2=8$。
### 数据规模
| $\text{Subtask}$ | $n\le$ | $m\le$ | $k\le$ | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $20$ | $10$ | $10^{18}$ | $5$ |
| $2$ | $70$ | $70$ | $10^{18}$ | $15$ |
| $3$ | $100$ | $300$ | $10^{18}$ | $20$ |
| $4$ | $10^4$ | $10^4$ | $10^{18}$ | $15$ |
| $5$ | $10^4$ | $10^{18}$ | $10^{18}$ | $10$ |
| $6$ | $10^6$ | $10^{18}$ | $1$ | $5$ |
| $7$ |$2\times10^7$| $10^{18}$ | $10^{18}$ | $30$ |


对于 $100\%$ 的数据，$1\le n\le 2\times10^7$，$2\le m\le 10^{18}$，$1\le k\le 10^{18}$。
### 特殊计分方式
本题开启子任务依赖，具体如下：
- 对于子任务 $i\in\{1,6\}$，您只需答对子任务 $i$ 即可获得子任务 $i$ 的分数。
- 对于子任务 $i\in\{2,3,4,5,7\}$，您需要答对所有 $j\in[1,i]$ 的子任务 $j$ 才能获得子任务 $i$ 的分数。

## 样例 #1

### 输入

```
10 6 3
5 7 4 3 6 2 10 8 9 1```

### 输出

```
38```

## 样例 #2

### 输入

```
2 5 2
1 2```

### 输出

```
8```

## 样例 #3

### 输入

```
2 114514 1
2 1```

### 输出

```
171771```

## 样例 #4

### 输入

```
3 1000000000000000000 3
2 1 3```

### 输出

```
2065039361```

# 题解

## 作者：cyffff (赞：3)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8145)

$\text{Update2024.8.16}$：大幅度修改，优化表述。
## 题意
给你一个 $n$ 阶排列 $p$，任选一个起始点，走 $m-1$ 步，并将走过的所有数按走到的顺序写下，形成一个长度为 $m$ 的序列。求出所有以上面的方法生成的序列中字典序第 $k$ 小的序列的所有元素的和。

$n\le2\times 10^7$，$m,k\le10^{18}$。
## 思路
先特判掉 $n\le 2$ 的情况，接下来默认 $n\ge 3$。

设 $f_{i,j}$ 表示从 $i$ 出发走 $j$ 步的方案数，转移显然。按 $p_i$ 从小到大枚举起始点，如果 $f_{i,m-1}<k$ 则将 $k$ 减去 $f_{i,m-1}$，否则我们就确认了起始点为 $i$ 即序列第一位为 $p_i$。接下来的每一步也是类似的，对第 $i$ 步，不妨设现在在 $x$ 且 $p_{x-1}<p_{x+1}$，则判断 $f_{x-1,m-i}$ 与 $k$ 的大小关系即可。

时间复杂度 $O(nm)$，无法通过。

$f_{i,j}$ 的值可能很大，而 $k\le 10^{18}$ 且我们只需要比较 $f_{i,j}$ 与 $k$ 的大小关系。于是当 $f_{i,j}\ge k$ 时，不妨令 $f_{i,j}=+\infty$。注意到 $j\ge 2\log k$ 时 $f_{i,j}$ 必然为 $+\infty$（这个下界只在 $n=3$ 时取到）。令 $c=2\log k$，可以发现除了最后 $c$ 步需要决策，其余全部向相邻位置中较小的走。

考虑前面的部分，一定是走到某个地方开始在 $i$ 和 ${i+1}$ 之间反复走。所以我们可以 $O(n)$ 走完前面的步数，最后 $c$ 步按照决策来走。

时间复杂度 $O(n\log k)$，无法通过，瓶颈仍在计算所有 $f_{i,j}$。

继续优化 $f_{i,j}$ 的预处理。由于我们只需要求走不超过 $c$ 步的方案数，所以如果 $c<i<n-c$，则 $i$ 走 $c$ 步的过程中不可能碰到边界，即 $f_{i,j}=2^j$。于是我们只需要求 $i\le c$ 和 $i\ge n-c$ 的这 $O(\log k)$ 个位置的 $f_{i,j}$ 即可。

时间复杂度 $O(n+\log^2k)$，可以通过。

---

## 作者：Sakura_xyz (赞：2)

### 题意

给定一个 $[1,n]$ 的排列 $p$ ，以任意点为起点出发，每次可以向左或向右移动一步，求经过 $m$ 个点（即相当于走 $m-1$ 步）后可以产生的序列中字典序第 $k$ 小的序列。

### 分析

对于 $20\%$ 的数据，有 $m,n\leq70$ 。我们很显然可以利用 dp 来求解，设 $dp_{i,j}$ 表示从第 $i$ 个位置开始，走 $j-1$ 步，经过 $j$ 个点的方案数，则有转移方程：

$dp_{i,j}=dp_{i-1,j-1}+dp_{i+1,j-1}$

考虑第一步可以走到第 $i-1$ 个位置或者第 $i+1$ 个位置，很容易知道，这个转移方程是显然的。

我们预处理出所有方案数，利用 dfs 找出每一步应走的位置，具体方法为：

设当前位置为 $i$ ,还需要经过 $x$ 个点（还需走 $x$ 步），查找第 $k$ 小的排列。若 $p_{i-1}<p_{i+1}$ ，令 $j=i-1$ ,否则令 $j=i+1$ ，此时若 $dp_{j,x}\geq k$ ，则直接进入 $j$ 继续搜索，反之，则令 $k$ 减去 $dp_{j,x}$ ，进入另一侧进行搜索。

### 代码

dp 部分

```cpp
for(int i=1;i<=n;i++) dp[i][1]=1;
for(int j=2;j<=m;j++){
	for(int i=1;i<=n;i++){
		dp[i][j]=dp[i-1][j-1]+dp[i+1][j-1];
	}
}
```

dfs 部分
```cpp
void dfs(int pos,int last,int num){
	if(!pos) return;
	int now=0,tmp=n;
	if(last==1){
		ans+=p[2]; ans%=mod;
		return dfs(pos-1,2,num);
	}
	if(last==n){
		ans+=p[n-1]; ans%=mod;
		return dfs(pos-1,n-1,num);
	}
    if(p[last-1]>p[last+1]){
    	if(num>dp[last+1][pos]){
    		ans+=p[last-1]; ans%=mod;
			dfs(pos-1,last-1,num-dp[last+1][pos]);
		}
		else{
			ans+=p[last+1]; ans%=mod;
			dfs(pos-1,last+1,num);
		}
	}
	else{
		if(num>dp[last-1][pos]){
			ans+=p[last+1]; ans%=mod;
			dfs(pos-1,last+1,num-dp[last-1][pos]);
		}
		else{
			ans+=p[last-1]; ans%=mod;
			dfs(pos-1,last-1,num);
		}
	}
}
```
### 优化

我们发现，这个转移的时间复杂度是 $O(nm)$ ， dfs 的时间复杂度是 $O(m)$ ，显然无法通过本题数据范围的数据，并且， dp 的转移过程中，数据呈现指数级增长，即使采用高精度也不能在合理的空间复杂度内存储。然而， $k$ 很小，在 $10^{18}$ 范围内。而我们可以推断出，比 $k$ 小的 dp 值，一定在 $\log_2k$ 的量级左右。因此，前面的大多数步一定在取字典序最小的部分，也就是说，一直在 $1$ 与 $1$ 左右两侧中较小的数中循环。所以，这样我们将 $m$ 转化为 $\log_2k$ 的量级，时间复杂度和空间复杂度均为 $O(n\log k)$ ，可以拿到 $70$ 分的成绩。

再进一步，发现在 $i\geq j$ 时，每一步均有两种走法，即有 $dp_{i,j}=2^{j-1}$ ，因此，考虑只转移 $i<j$ 的部分，当 ${i\geq j}$ 时，直接返回 $2^{j-1}$ 即可。利用记忆化搜索可以更方便实现。

最终，我们成功地把转移过程中对于 $n,m$ 的计算均降到了 $\log_2k$ 的量级内，可以通过本题。

时间复杂度为 $O(n)$ （读入数据的时间复杂度）。

### tips : 

这道题读入量非常大，对于代码常数要求很高，赛时提供了快速读入模板，若常数过大，可使用赛时提供的快读模板（我的代码中使用的读入方式）减小读入的时间常数。

### AC 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define int __int128

using namespace std;

signed p[20000005]={}; int ans=0;

signed unp[20000005]={}; long long n,m,k;

const int mod=1ll<<32;

inline int Fpnomod(int x,int tms){
	int ret=1;
	while(tms){
		if(tms&1) ret*=x;
		x*=x; tms>>=1;
	}
	return ret;
}

namespace IO{//by cyffff
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;

template <typename T>
inline void write(T x){
	if(x>9) write(x/10);
	putchar(x%10+48);
}

int memory[1005][1005]={},base2[100]={};

const int inf=2e18;//大于maxk 确保不会炸

int f(int i,int j){
	if(i<=0||i>n) return 0;
	i=min(i,n+1-i); //两边对称 取小的
	if(i>=j&&j>70) return inf;
	if(i>=j) return base2[j-1];
	// 考虑 i>=j 时 左右走 完全是自由的 有(1<<j)种走法
	if(memory[i][j]) return memory[i][j];
	return memory[i][j]=min(inf,f(i-1,j-1)+f(i+1,j-1));
}


void dfs(int pos,int last,int num){
	//考虑 统计完dfs空间炸了
	//中间全是(1<<j) 特判两边 dp一边统计一边记忆化
	//阴间题 离谱码量 写**()
	if(!pos) return;
	int now=0,tmp=n;
	if(last==1){
		ans+=p[2]; ans%=mod;
		return dfs(pos-1,2,num);
	}
	if(last==n){
		ans+=p[n-1]; ans%=mod;
		return dfs(pos-1,n-1,num);
	}
    if(p[last-1]>p[last+1]){
    	if(num>f(last+1,pos)){
    		ans+=p[last-1]; ans%=mod;
			dfs(pos-1,last-1,num-f(last+1,pos));
		}
		else{
			ans+=p[last+1]; ans%=mod;
			dfs(pos-1,last+1,num);
		}
	}
	else{
		if(num>f(last-1,pos)){
			ans+=p[last+1]; ans%=mod;
			dfs(pos-1,last+1,num-f(last-1,pos));
		}
		else{
			ans+=p[last-1]; ans%=mod;
			dfs(pos-1,last-1,num);
		}
	}
}

void solveKequals1(){
	if(n==1) return (void) puts("-1");
	int t1=unp[1],t2;
	if(t1==1) t2=2; else if(t1==n) t2=n-1;
	else if(p[t1+1]>p[t1-1]) t2=t1-1; else t2=t1+1;
	int pt1=p[t1],pt2=p[t2],mpt=m/2;
	if(m%2==1) ans=((mpt)*(pt1+pt2)+pt1)%mod;
	else ans=((mpt)*((pt1+pt2)%mod))%mod;
	write(ans); puts("");
}

void solve20pts(){
	int tmp=0,pos=0;
	for(int i=1;i<=n;i++){
		tmp+=f(unp[i],m);
		if(tmp>=k){
			//cout << unp[i] << endl;
			ans+=i; ans%=mod;
			pos=i;
			break;
		}
	}
	if(!pos) return (void) puts("-1");
	dfs(m-1,unp[pos],k-tmp+f(unp[pos],m));
	write(ans); puts("");
}

void solve(){
	int tmp=log2(k)+1; if(Fpnomod(2,tmp)==k) tmp--;
	int t1=unp[1],t2;
	if(t1==1) t2=2; else if(t1==n) t2=n-1;
	else if(p[t1+1]>p[t1-1]) t2=t1-1; else t2=t1+1;
	ans=(((m-tmp)/2)*(p[t1]+p[t2])%mod+((m-tmp)%2)*p[t1]%mod)%mod;
	int st;
	if((m-tmp)%2) st=t1; else st=t2;
	int kk=0; bool flag=false;
	for(int i=1;i<=n;i++) kk+=f(i,tmp); if(kk>=k) flag=true;
	if(!flag) return (void) puts("-1");
	dfs(tmp,st,k);
	write(ans); puts("");
}

signed main(){
	base2[0]=1; for(int i=1;i<=70;i++) base2[i]=base2[i-1]*2;
	n=read(); m=read(); k=read();
	for(int i=1;i<=n;i++) p[i]=read(),unp[p[i]]=i;
	if(k==1) return solveKequals1(),0;
	int tmp=log2(k)+1; if(Fpnomod(2,tmp)==k) tmp--;
	if(m<tmp||m<=70) return solve20pts(),0;
	return solve(),0;
}
```


---

## 作者：critnos (赞：1)

这个题其实是：

一个小朋友，在排列上初始选定一个位置，然后走 $m-1$ 步，记录下走过的位置，形成一个序列，求字典序第 $k$ 小的。

从小到大枚举初始位置。然后考虑小朋友的方案：他可能向左或者向右。

显然向左或向右后形成的序列的字典序的大小关系取决于左右的数的大小。那么求出走向小的一边的方案数，若其 $<k$ 就把 $k$ 减掉这个，然后向另一边走；否则就向小的一边走。

然后考虑怎么选方案，这个就是 dp。设 $f_{i,j}$ 为走 $i$ 步到达点 $j$ 的方案数，那么 $f_{i,j}=f_{i-1,j-1}+f_{i-1,j+1}$。设求从 $x$ 走 $y$ 步的方案数，那么初始 $f_{0,x}=1$，$ans=\sum_{i=1}^n f_{y,i}$。

好看看这个做法的复杂度：枚举初始位置 $O(n)$，走 $m-1$ 步 $O(m)$，每次 dp $O(nm)$。。天哪复杂度竟然是 $O(n^2m^2)$。。

不过冷静一下：

这个 $k$ 和总方案数相比是沧海一粟。也就是说方案数 $<k$ 的情况是不多的。具体的，只会在最后剩几步没走的情况下发生！

实际上，当 $n>2$ 时（$n\le 2$ 的情况非常平凡），我们可以得到走 $m$ 步的方案数是 $\Omega(2^{m/2})$ 级别的，通过计算 $n=3$，初始位置为 $1$ 得到。

那么我们可以直接跳过前面一大段直接走最小值的部分。显然，经过一些移动之后最后会在两个数之间反复横跳。

那么最后的步数是 $O(\min(m,\log k))$ 级别的。

先要引入一个优化，就是上面的 dp 对于走 $m$ 步，我们可以只考虑距离初始点距离不超过 $m$ 的点，因为其他点不可能走到。那么复杂度优化到了 $O(m\min(n,m))$。

讨论两个 case：

1. 从一个位置出发的方案数 $<k$。这意味着 $2^{m/2}<k$ 即 $m<2\log k$。这种情况下可能要枚举所有的初始位置，但对一个初始位置求方案数的复杂度为 $O(m^2)$ 即 $O(\log^2 k)$。不过考虑到除了首尾 $m$ 位需要考虑边界的问题，其他都是随意走，即方案数均为 $2^{m-1}$！那么我们可以通过 $O(n+\log ^3 k)$ 的复杂度寻找到正确的初始位置并转到 case 2。

2. 从一个位置出发的方案数 $\ge k$。那么我们只用跑一次。并且在跳过大量的无用位置后，我们把剩余步数下降到了 $O(\log k)$ 级别。那么开始 dp，时间复杂度为 $O(\log^3 k)$。

综上，时间复杂度为 $O(n+\log^3 k)$。

---

## 作者：Lvlinxi2010 (赞：1)

## **题目大意**
简化之后为：给定一个 $ 1 $ 到 $ n $ 的排列 $ P $ ，可以从任意点出发，每次选择向左或向右移动一步，走 $ m-1 $ 步,每到达一个点就将这个点记录下来，求所有序列中字典序是第 $ k $ 小的序列。

## **思路**

第一眼看到数据范围，对于 $100\%$ 的数据，$ 1\le n\le 2\times10^7 $ ， $ 2\le m\le 10^{18} $，$ 1\le k\le 10^{18}$。

一开始先用 dp + dfs 拿点分。

1. 设状态：$ f_{i,j} $ 表示我们从第 $ i $ 个位置，经过 $ j $ 个点的方案数。
2. 转移方程：$ f_{i,j} = f_{i-1,j-1} + f_{i+1,j-1} $。由一个点上一步可能在左边一个点或右边一个点得出。

我们先用 dp 预处理出方案数，再用 dfs 算出具体应该走哪一步。

但这些还不够，还要加一些优化：

1. 这个转移的时间复杂度是 $ O(nm) $  ，dfs 的时间复杂度是 $ O(m) $,无法通过本题。
2. 但是这个 $ k $ 比总方案数小很多。也就是说方案数 $ <k $ 的情况是不多的。比 $ k $ 小的 dp 值，一定在 $\log_2k$ 的量级左右。
3. 我们又发现在 $ i\geq j $ 时，每一步均有两种走法，即有 $ dp_{i,j}=2^{j-1}$，因此，考虑只转移 $i<j$ 的部分，当 ${i\geq j}$ 时，直接返回 $2^{j-1}$ 就可以了。
4. 经过这些优化，时间复杂度为 $ O(n) $ ，可以通过。

代码太丑，不贴了。

（麻烦管理员审核一下）

---

