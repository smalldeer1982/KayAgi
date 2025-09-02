# Hot Start Up (hard version)

## 题目描述

This is a hard version of the problem. The constraints of $ t $ , $ n $ , $ k $ are the only difference between versions.

You have a device with two CPUs. You also have $ k $ programs, numbered $ 1 $ through $ k $ , that you can run on the CPUs.

The $ i $ -th program ( $ 1 \le i \le k $ ) takes $ cold_i $ seconds to run on some CPU. However, if the last program we ran on this CPU was also program $ i $ , it only takes $ hot_i $ seconds ( $ hot_i \le cold_i $ ). Note that this only applies if we run program $ i $ multiple times consecutively — if we run program $ i $ , then some different program, then program $ i $ again, it will take $ cold_i $ seconds the second time.

You are given a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of integers from $ 1 $ to $ k $ . You need to use your device to run programs $ a_1, a_2, \ldots, a_n $ in sequence. For all $ 2 \le i \le n $ , you cannot start running program $ a_i $ until program $ a_{i - 1} $ has completed.

Find the minimum amount of time needed to run all programs $ a_1, a_2, \ldots, a_n $ in sequence.

## 说明/提示

In the first test case, we can do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 3 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 2 $ seconds to run.
- Run program $ a_3 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 3 + 2 + 1 = 6 $ seconds to run them all. We can show this is optimal.

In the second test case, we can use do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 5 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 3 $ seconds to run.
- Run program $ a_3 = 1 $ on CPU $ 1 $ . The last program run on this CPU was also program $ 1 $ , so it takes $ hot_1 = 2 $ seconds to run.
- Run program $ a_4 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 5 + 3 + 2 + 1 = 11 $ seconds. We can show this is optimal.

## 样例 #1

### 输入

```
9
3 2
1 2 2
3 2
2 1
4 2
1 2 1 2
5 3
2 1
4 3
1 2 3 1
100 100 100
1 1 1
5 2
2 1 2 1 1
65 45
54 7
5 3
1 3 2 1 2
2 2 2
1 1 1
5 1
1 1 1 1 1
1000000000
999999999
5 6
1 6 1 4 1
3 6 4 1 4 5
1 1 1 1 4 1
1 3
3
4 5 6
1 2 3
8 3
3 3 3 1 2 3 2 1
10 10 8
10 10 5```

### 输出

```
6
11
301
225
8
4999999996
11
6
63```

# 题解

## 作者：thostever (赞：14)

神奇的 DP 题。

（以下题解中的 $k$ 为单独变量，不同于题目中的 $k$。题目中的 $k$ 用 $m$ 表示）

我们先考虑最朴素的 $dp$，我们枚举当前位 $a_k$，令 $dp_{i,j}$ 表示选完 $a_k$，第一堆的最后一个是 $i$，第二堆的最后一个是 $j$，最小的用时。

我们可以省略掉第一维 $k$。转移如下：

$$
{\large
\left\{
\begin{matrix}
dp_{i,j} + cold_{a_k}\to dp_{i,a_k}
\\dp_{i,j} + cold_{a_k}\to dp_{a_k,j}
\\dp_{i,a_k} + hot_{a_k}\to dp_{i,a_k}
\\dp_{a_k,j} + hot_{a_k}\to dp_{a_k,j}
\end{matrix}
\right.
}
$$

很显然，这样子时间是 $O(nm^2)$ 的。甚至过不了 D1。

我们发现，每次转移 $a_k$ 时，所有 $dp_{i,j}$ 中只有 $dp_{i,a_{k-1}}$ 和 $dp_{a_{k-1},j}$ 有值，并且只用转移到 $dp_{i,a_k}$ 和 $dp_{a_k,j}$，其他位置都是 $inf$。因此转移只需要考虑那 $m$ 个位置即可。复杂度 $O(nm)$。可过 D1。

我们考虑进一步优化：

我们可以将 dp 状态压缩成一维，令 $dp_i$ 表示 $dp_{a_k,i}$，转移变成如下：

（注：显然有 $dp_{i,j}=dp_{j,i}$）

若 $a_k\neq a_{k-1}$：

$$
{\large
\left\{
\begin{matrix}
dp_{a_{k-1},i} + cold_{a_k}\to dp_{a_{k-1},a_k}\Rightarrow dp_i+cold_{a_k}\to dp_{a_{k-1}}
\\dp_{a_{k-1},i} + cold_{a_k}\to dp_{a_k,i}\Rightarrow dp_i+cold_{a_k}\to dp_i
\\dp_{a_{k-1},a_k} + hot_{a_k}\to dp_{a_{k-1},a_k}\Rightarrow dp_{a_k}+hot_{a_k}\to dp_{a_{k-1}}
\end{matrix}
\right.
}
$$

对于第二条式子，我们可以记一个变量 $s$ 表示所有 $dp$ 值一共增加了多少。$s$ 每次增加 $cold_{a_k}$ 即可。而 $dp$ 值本身不变化。

第三条式子直接转移即可。

而对于第一条，我们记一个最小值 $mn$，然后直接转移。

注意第二条式子把所有值加上了 $cold_{a_k}$，所以一三条式子转移时答案要减去 $cold_{a_k}$。

显然，只有 $dp_{a_{k-1}}$ 会有值的变化。而第一条和第三条一定比第二条优，所以 $dp_{a_{k-1}}$ 每次都会变小，因此 $mn$ 每次只需要用 $dp_{a_{k-1}}$ 更新即可。

若 $a_k=a_{k-1}$，直接将 $s$ 加上 $hot_{a_k}$ 即可。

复杂度 $O(n+m)$，代码很短。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f3f3f3f3f;
int n,m;
int a[300010];
ll dp[300010];
ll s,minn;
int cold[300010],hot[300010];
void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&cold[i]);
	for(int i=1;i<=m;i++) scanf("%d",&hot[i]);
	for(int i=1;i<=m;i++) dp[i]=inf;
	dp[0]=0; minn=0; s=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]==a[i-1])
		{
			s+=hot[a[i]];
		}
		else
		{
			s+=cold[a[i]];
			dp[a[i-1]]=min(dp[a[i]]+hot[a[i]],minn+cold[a[i]])-cold[a[i]];
			minn=min(minn,dp[a[i-1]]);
		}
	}
	printf("%lld\n",minn+s);
}
int main()
{
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
/*

*/

```


---

## 作者：y_kx_b (赞：7)

这场我做的不太顺利，但我发现别人好像也不太顺利，于是（相对之前）我就起飞了。| B 和 C 都是瞎猜的结论/kk。 | 好可惜，D2 只要多写一个线段树就好了，但是考场上太困了 打完 D1 就跑路了/kk。

---
我们先看 Easy Version，$n, k\leqslant 5000$。

发现第 $i$ 个程序运行的时间只与两个 CPU 之前跑的程序有关，于是我们很容易想出状态机 dp：设 $dp_{i, j, k}$ 表示跑完了前 $i$ 个程序，CPU1 上刚跑完程序 $j$，CPU2 上刚跑完程序 $k$，所要的时间最小值。状态复杂度为 $O(nk^2)$，已经 T 了。

考虑优化状态。又容易发现第 $i$ 个程序必定在 CPU1 或 CPU2 上跑（废话），所以我们不妨钦定第 $i$ 个程序在 CPU2 上跑（两个 CPU 本质相同，可以交换），那么状态就可以压缩为：设 $dp_{i, j}$ 表示跑完了前 $i$ 个程序，CPU1 上刚跑完程序 $j$，CPU2 上刚跑完程序 $a_i$，所要的时间最小值。

注意 $j$ 可以为 $0$，此时代表该 CPU 上没有跑过任何程序。所以初始状态显然就是 $dp_{0,0}=0,dp_{0,1\sim k}=+\infty$。

转移：

首先枚举 $i,j$。
- 如果第 $i$ 个程序是在之前的 CPU2 上跑，那么之前 CPU2 跑的程序是 $a_{i-1}$，跑完第 $i$ 个程序后 CPU1：$j$，CPU2：$a_i$，所以有 $dp_{i,j}=\min\left(dp_{i,j}, dp_{i-1,j}+\begin{cases}hot_{a_i},a_i=a_{i-1}\\cold_{a_i},\text{otherwise}\end{cases}\right)$；
- 如果第 $i$ 个程序是在之前的 CPU1 上跑，那么之前 CPU1 跑的程序是 $j$，跑完第 $i$ 个程序后 CPU1：$a_i$，CPU2：$a_{i-1}$，此时交换两个 CPU，有 $dp_{i,a_{i-1}}=\min\left(dp_{i,a_{i-1}}, dp_{i-1,j}+\begin{cases}hot_{a_i},a_i=j\\cold_{a_i},\text{otherwise}\end{cases}\right)$。

时间复杂度 $O(nk)$。
```cpp
dp[0][0] = 0;
for(int i = 1; i <= k; i++) dp[0][i] = inf;
ll ans = inf;
for(int i = 1; i <= n; i++) {
	for(int j = 0; j <= k; j++)
		dp[i][j] = inf;
	for(int j = 0; j <= k; j++) {
		dp[i][j] = min(dp[i][j],
			dp[i - 1][j] + (a[i] == a[i - 1] ? hot[a[i]] : cold[a[i]]));//ith program on CPU2
		dp[i][a[i - 1]] = min(dp[i][a[i - 1]],
			dp[i - 1][j] + (a[i] == j ? hot[a[i]] : cold[a[i]]));//ith program on CPU1
	}
}
for(int j = 0; j <= k; j++)
	ans = min(ans, dp[n][j]);
printf("%lld\n", ans);
```
考虑 Hard Version（$n, k\leqslant 3\times10^5$）的优化。
> dp 的优化基本就是对着原来的代码做等价变形。 —— yxc

对于此题可以无脑线段树维护区间操作，~~那么做完了。~~

首先发现上述代码里的 `dp` 数组可以优化到一维：首先把可以更新 $dp_{i,a_{i-1}}$ 的值先记下来（转移 2），然后全局加（转移1），然后更新 $dp_{i,a_{i-1}}$。[一维的代码。](https://codeforces.com/contest/1799/submission/195218681)

~~看题解知道~~发现这些操作都可以在线段树上进行，那么做完了。[D2 代码。](https://codeforces.com/contest/1799/submission/195219315)

---
感谢您看到这里，祝您享受切题的快感！

如果有什么不懂的欢迎回复 qwq

---

## 作者：2018ljw (赞：5)

赛时唯唯诺诺，vp 重拳出击。（假的，这场赛时没打）

考虑将问题转化一下，将我们要完成的任务划分为若干段区间，然后两个处理器交错处理这些区间。显然，这和原问题等价，考虑以此为切入点 dp。

设 $f(i,j)$ 表示先执行 $i$ 再执行 $j$，$j$ 的花费，$calc(l,r)$ 表示处理完任务 $l$ 后，顺次执行区间 $[l+1,r]$ 内所有任务的总花费。

设 $dp_{i}$ 表示以 $i$ 为一段区间结尾，前面划分后的最小代价。

那么枚举上一段区间结束位置，不难得到转移式：$dp_{i}=\min\limits_{k<i}\{dp_{k}+calc(k+1,i)+f(las,k+1)\}$。

此时我们会发现遇到了一点问题：我们无从得知 $f(las,k+1)$ 的值。如果要再记录一维 $las$，状态数肯定爆炸。

这里采用一个很经典的思想：费用预支。

$f(las,k+1)$ 无法在 $(k+1,i)$ 的区间里处理，那么我们就在 $(las+1,k)$ 的区间转移时把它求出来。

所以正确的转移式为：

$$
dp_{i}=\min_{k<i}\{dp_k+calc(k+1,i)+f(k,i+1)\}
$$

特别的，我们在 $0$ 和 $n+1$ 处均加入一个花费恒为 $0$ 的任务，规避掉一些特殊情况。

固定左端点，不断扩大右端点即可在 $O(n^2)$ 内预处理所有的 $calc(l,r)$，转移 $O(n^2)$，可以通过 easy version。

接下来考虑优化，先处理 $calc$ 函数。

令 $g_i=f(i,i+1)$，则有 $calc(l,r)=\sum\limits_{i=l}^{r-1}g_i$。

所以我们求出 $g$ 的前缀和数组 $sum_i=\sum\limits_{j=0}^ig_j$，即可得到 $calc(l,r)=sum_{r-1}-sum_{l-1}$。

将其代回原转移式可得 $dp_{i}=\min\limits_{k<i}\{dp_k+sum_{i-1}-sum_k+f(k,i+1)\}$。

按下标分类一下，$dp_i=\min\limits_{k<i}\{dp_k-sum_k+f(k,i+1)\}+sum_{i-1}$。

前面部分的 $dp$ 求完后，$dp_k-sum_k$ 是可以统一维护的，那么只剩下 $f(k,i+1)$ 一项了。考虑这东西等于什么。

$$
f(x,y)=\begin{cases}hot_{a_y}& a_x=a_y\\cold_{a_y}& a_x\neq a_y\end{cases}
$$

由于保证 $hot_i\le cold_i$，所以实际上还可以更进一步得到：

$$f(x,y)=\min\begin{cases}hot_{a_y}& a_x=a_y\\cold_{a_y}\end{cases}$$

因此转移式也可以进行调整。

$$
dp_{i}=sum_{i-1}+\min_{k<i}\begin{cases}dp_{k}-sum_k+cold_{a_{i+1}}\\ dp_k-sum_k+hot_{a_{i+1}}&a_k=a_{i+1}\end{cases}
$$

那么我们只需要在 dp 的过程中顺带维护 $dp_i-sum_i$ 的全局最小值和每类最小值即可，复杂度 $O(n)$。

~~数据结构是什么？真不熟。~~

```cpp
#include<cstdio>
#include<cstring>
const long long inf=1e18;
int n,k,a[300002];
int hot[300002],cold[300002];
long long sum[300002],dp[300002],mn[300002];
long long min(long long x,long long y){return x<y?x:y;}
long long f(int x,int y){
	return a[x]==a[y]?hot[a[y]]:cold[a[y]];
}
int main(){
	int i,j,t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(i=1;i<=n;i++)sum[i]=dp[i]=0;
		for(i=1;i<=k;i++)mn[i]=inf;
		a[n+1]=hot[n+1]=cold[n+1]=0;
		for(i=1;i<=n;i++)scanf("%d",&a[i]);
		for(i=1;i<=k;i++)scanf("%d",&cold[i]);
		for(i=1;i<=k;i++)scanf("%d",&hot[i]);
		sum[0]=f(0,1);
		for(i=1;i<=n;i++)sum[i]=sum[i-1]+f(i,i+1);
		long long alm=0;
		for(i=1;i<=n;i++){
			dp[i]=alm+cold[a[i+1]]+sum[i-1];
			dp[i]=min(dp[i],mn[a[i+1]]+hot[a[i+1]]+sum[i-1]);
			mn[a[i]]=min(mn[a[i]],dp[i]-sum[i]);
			alm=min(alm,dp[i]-sum[i]);
		}
		printf("%lld\n",dp[n]);
	}
}
```

---

## 作者：Super_Cube (赞：3)

# Solution

我唐完了。

记 $cold_i$ 为 $b_i$，$hot_i$ 为 $c_i$。

设 $l_i$ 为从 $i$ 开始往前找到的第一个位置满足数值与 $a_i$ 相等，$dp_i$ 表示考虑到 $i$ 个数时的最大价值。有个很显然的转移：$dp_i=dp_{l_i+1}+f(l_i+2,i-1)+c_{a_i}$，其中 $f(l,r)$ 表示把 $l\sim r$ 涂成同色的总贡献。就是让 $a_i$ 与 $a_{l_i}$ 配对做出贡献，把中间一段涂成与 $a_i$ 异色。答案即为 $dp_n$。好的我考场想到这里就没了，愣是被硬控之后怀疑自己思路有问题就放弃这个做法了，因为这样打过不了样例，我也没想出来这个转移有啥问题。很好笑的是 $i$ 可以不做贡献的，也即转移 $dp_i\gets dp_{i-1}+b_{a_i}$；还有之前那个方程当 $l_i=i-1$ 时，会有越界的问题，于是特判这种情况，改为 $dp_i=dp_{i-1}+c_{a_i}$ 就行了；最后是 $l_i$ 不存在的情况，那就直接 $dp_i=f(1,i)$。

时间复杂度：$O(Tn)$。

# Code

```cpp
#include<bits/stdc++.h>
long long dp[300005];
long long s[300005];
int b[300005],c[300005];
int vis[300005];
int lst[300005];
int a[300005];
int T,n,m;
int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);std::cout.tie(0);
	std::cin>>T;
	while(T--){
		std::cin>>n>>m;
		for(int i=1;i<=n;++i)
			std::cin>>a[i],lst[i]=vis[a[i]],vis[a[i]]=i;
		for(int i=1;i<=m;std::cin>>b[i++]);
		for(int i=1;i<=m;std::cin>>c[i++]);
		for(int i=1;i<=n;++i)
			s[i]=s[i-1]+(a[i]==a[i-1]?c[a[i]]:b[a[i]]);
		for(int i=1;i<=n;++i)
			dp[i]=std::min(dp[i-1]+b[a[i]],lst[i]?lst[i]==i-1?dp[i-1]+c[a[i]]:dp[lst[i]+1]+c[a[i]]+s[i-1]-s[lst[i]+1]:s[i]);
		std::cout<<dp[n]<<'\n';
		for(int i=1;i<=n;++i)vis[a[i]]=0;
	}
	return 0;
}
```

所以说有三道简单题的 CSP 我是怎么考出这么小丑的成绩的。

---

## 作者：FBW2010 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1799D2)

# 思路

由于每次决定只与上次两个 CPU 的状态有关，我们不妨考虑 **dp**。因为我们知道上一次运行的程序是哪一种，所以只需要考虑另一个 CPU 运行的程序是什么。设 $dp_{i,j}$ 为考虑到第 $i$ 个程序，另一个 CPU 上次运行的程序为 $j$ 的最短时间，便可以分情况转移：

+ 若 $a_i=a_{i-1}$，那么肯定是用上一次运行的 CPU 更优，于是 $dp_{i,j}=dp_{i-1,j}+hot_{a_i}$。

+ 若 $a_i \ne a_{i-1}$，那又得分两种：

	+ 对于 $dp_{i,a_{i-1}}$，那么这次使用的一定不是上次使用的 CPU，如果上次的另一个 CPU 上次运行的程序和这次运行的一样，便加上 $hot_{a_i}$，其他的便是 $cold_{a_i}$。转移方程便是 $dp_{i,a_{i-1}}=\min(dp_{i-1,a_i}+hot_{a_i},\min(dp_{i-1,t}(1 \le t \le k,t \ne a_i))+cold_{a_i})$。
    
   + 对于其他情况，肯定不会有相同的情况，于是 $dp_{i,j}=dp_{i-1,j}+cold_{a_i}$
   
这时，我们便拥有了一个时间复杂度 $O(nk^2)$，空间复杂度为 $O(nk)$ 的~~优秀算法~~。用**滚动数组**可以滚掉一维，而转移就相当于是将滚动数组区间修改，不难想到可以用**线段树**维护，时间复杂度便降为了 $O(n\log k)$，空间复杂度便降为了 $O(n+k)$，可以通过此题。

~~PS：貌似只有全局的修改，直接用变量存就可以了，复杂度还低一些，但本蒟蒻没想到。~~

# 代码

~~接下来便献上我又臭又长的线段树吧！~~

~~不开 long long 见祖宗！~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int t,a[N],c[N],h[N];
struct node{
	int l,r;
	long long min/*区间最小值*/,flag/*懒标记*/;
}tree[N*4];
void pu(int k){ //push_up
	tree[k].min=min(tree[k*2].min,tree[k*2+1].min);
}
void pd(int k){ //push_down
	if(tree[k].flag){
		tree[k*2].min+=tree[k].flag;
		tree[k*2].flag+=tree[k].flag;
		tree[k*2+1].min+=tree[k].flag;
		tree[k*2+1].flag+=tree[k].flag;
		tree[k].flag=0;
	}
}
void bui(int k,int l,int r){ //建树 
	tree[k].l=l;
	tree[k].r=r;
	tree[k].min=tree[k].flag=0;
	if(l==r){
		tree[k].min=1e15;
		return;
	}
	int mid=(l+r)>>1;
	bui(k*2,l,mid);
	bui(k*2+1,mid+1,r);
	pu(k);
}
void cha(int k,int x,int y,int v){ //区间加和 
	if(tree[k].l>y||tree[k].r<x)return;
	if(tree[k].l>=x&&tree[k].r<=y){
		tree[k].min+=v;
		tree[k].flag+=v;
		return;
	}
	pd(k);
	cha(k*2,x,y,v);
	cha(k*2+1,x,y,v);
	pu(k);
}
void cha2(int k,int x,long long v){ //单点赋值 
	if(tree[k].l>x||tree[k].r<x)return;
	if(tree[k].l==tree[k].r){
		tree[k].min=v;
		return;
	}
	pd(k);
	cha2(k*2,x,v);
	cha2(k*2+1,x,v);
	pu(k);
}
long long ask(int k,int x,int y){ //区间查询 
	if(tree[k].l>y||tree[k].r<x)return 1e15;
	if(tree[k].l>=x&&tree[k].r<=y){
		return tree[k].min;
	}
	pd(k);
	return min(ask(k*2,x,y),ask(k*2+1,x,y));
}
int main(){
	scanf("%d",&t);
	while(t--){
		int n,k;
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=k;i++){
			scanf("%d",&c[i]);
		}
		for(int i=1;i<=k;i++){
			scanf("%d",&h[i]);
		}
		bui(1,1,k+1);
		cha2(1,k+1,0);
		for(int i=1;i<=n;i++){
			if(a[i]==a[i-1]){
				cha(1,1,k+1,h[a[i]]);
			}
			else{
				cha2(1,a[i-1],min(ask(1,a[i],a[i])+h[a[i]],ask(1,1,k+1)+c[a[i]]));
				cha(1,1,k+1,c[a[i]]);
				cha(1,a[i-1],a[i-1],-c[a[i]]);
			}
		}
		printf("%lld\n",ask(1,1,k+1));
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：1)

## [CF1799D Hot Start Up](https://www.luogu.com.cn/problem/CF1799D2)

本题解基于对[这篇题解](https://www.luogu.com.cn/blog/CGY/solution-cf1799d2)的补充。

### 题意

你有两个 CPU 和若干类型的程序，处理第 $i$ 个程序时，若你选择的 CPU 上一个处理的程序和 $i$ 是一个类型，那么会花费 $hot_i$，否则花费 $cold_i$。

求处理完所有程序的最小花费。

$n\le 3\times 10^5$。

### 解法

我们现在处理到了第 $k$ 个程序，其类型为 $t_k$。设 $f_{i,j}$ 表示当前 CPU 状态为一个处理完 $i$，一个处理完 $j$。

于是我们可以得到下列转移方程：

$$\begin{cases}f_{i,j}+cold_i\to f_{i,t_k},f_{t_k,j}\\f_{i,t_k}+hot_i\to f_{i,t_k}\\f_{t_k,j}+hot_i\to f_{t_k,j}\end{cases}$$

当 $t_k=t_{k-1}$ 时，我们肯定用 $hot_i$ 的花费放入同一个 CPU 处理。于是考虑 $t_k\ne t_{k-1}$ 的情况。

显然每次转移中 $i,j$ 里必有一个为 $t_{k-1}$，于是将方程转换：

$$\begin{cases}f_{i,t_{k-1}}+cold_i\to f_{t_k,t_{k-1}}\\f_{i,t_{k-1}}+cold_i\to f_{i,t_k}\\f_{t_{k-1},t_k}+hot_i\to f_{t_{k-1},t_k}\end{cases}$$

尝试再压一维，我们设 $f_i$ 表示 $f_{i,t_k}$，注意 $f_{i,t_k}$ 和 $f_{t_k,i}$ 是等价的。

于是再将方程转换：

$$\begin{cases}f_{i}(pre)+cold_i\to f_{t_{k-1}}\\f_i(pre)+cold_i\to f_i\\f_{t_k}(pre)+hot_i\to f_{t_{k-1}}\end{cases}$$

这里 $(pre)$ 指上一层的 $f$，即 $f_i$ 表示 $f_{i,t_{k-1}}$。

由于无法同时转移所有状态，我们不能直接转移。

* 对于第二条方程，我们给所有 $f$ 增加了 $cold_i$，但我们只需记录一个 $s$ 表示所有 $f$ 增加的和，而无需真正修改 $f_i$。

* 对于第一条方程，我们可以找出 $f$ 的最小值 $mn$，直接转移。

* 第三条方程两边下标已知，可以直接转移。

最终我们输出 $mn+s$ 即可。

### [代码](https://www.luogu.com.cn/paste/qkmyamx7)


---

## 作者：sjr3065335594 (赞：1)

一道很奇妙的 dp。

令 $f[i]$ 表示做完第 $i$ 个任务的最小花费。我们在定义以下内容：$las(x,y)$ 表示如果这个 CPU 上一个做的是 $x$ 的时候做 $y$ 所花费的时间，当且仅当 $a[x]$ 与 $a[y]$ 相等的时候取得 $hot[a[y]]$，否则为 $cold[a[y]]$；$cal(x,y)$ 表示一个 CPU 已经做完第 $x$ 个任务且依次从第 $x+1$ 个任务做到第 $y$ 个任务所花费的时间，$pre(x)$ 表示做到第 $i$ 个任务时做这个任务的 CPU 的上一个任务是什么。

那么此时，我们就可以进行转移了。

$$f[i]=\min\limits_{j<i}\{f[j]+cal(j+1,i)+las(pre(j),j+1)\}$$

可以理解为枚举是从哪一个地方分割，$j+1$ 是因为 $j$ 被 $f[j]$ 计算且 $j+1$ 被 $las()$ 计算。

首先考虑如何计算 $cal()$。

令 $g(i)$ 表示 $las(i,i+1)$，则

$$cal(x,y)=\sum\limits_{i=x}^{y-1}g(i)$$

于是维护 $g$ 的前缀和。令

$$s(i)=\sum\limits_{i=0}^{i}g(i)$$

可得

$$cal(x,y)=s(y-1)-s(x-1)$$

所以原来的式子就可以化简了

$$f[i]=\min\limits_{j<i}\{f[j]+s(i-1)-s(j)+las(pre(j),j+1)\}$$

接下来想如何计算 $pre()$，$pre()$ 这个东西不好后边由前边转移，于是可以在转移 $j$ 的时候计算出来，将其替换为 $las(j,i+1)$。

所以

$$f[i]=\min\limits_{j<i}\{f[j]+s(i-1)-s(j)+las(j,i+1)\}$$

由于这个 $\min$ 只和 $j$ 有关，所以可以把没有 $j$ 的放外边。

$$f[i]=\min\limits_{j<i}\{f[j]-s(j)+las(j,i+1)\}+s(i-1)$$

这一个式子里边，$f[j]-s(j)$ 是可以边做边处理的，关键在于 $las(j,i+1)$，可以将其按照题目中意思更换。

$$las(j,i+1)=\min\begin{cases}hot_{i+1}&a[j]=a[i+1]\\cold_{i+1}&\text{otherwise}\end{cases}$$

带回原式子

$$f[i]=s(i-1)+\min\begin{cases}f[j]-s(j)+hot_{i+1}&a[j]=a[i+1]\\f[j]-s(j)+cold_{i+1}&\text{otherwise}\end{cases}$$

于是边做边处理出 $hot$ 和 $cold$ 两种情况的最小值即可，时间复杂度 $O(n)$，可以通过本题。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp(x,y) make_pair(x,y)
#define CLR(a,x) memset(a,x,sizeof(a))
#define int long long
//#define int __int128
using namespace std;
const int N=3e5+5;
const int M=1e6+5;
const int INF=2e9+5;
int t,n,k,a[N],hot[N],cold[N];
ll sum[N],f[N],minn[N];
ll calc(int x,int y) {
    if(a[x]==a[y])return hot[a[y]];
    return cold[a[y]];
}
signed main() {
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
    scanf("%lld",&t);
    while(t--) {
        scanf("%lld%lld",&n,&k);
        a[n+1]=hot[n+1]=cold[n+1]=0;
        for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]),sum[i]=f[i]=0;
        for(int i=1;i<=k;i++)
            scanf("%lld",&cold[i]),minn[i]=1e17;
        for(int i=1;i<=k;i++)
            scanf("%lld",&hot[i]);
        sum[0]=calc(0,1);
        for(int i=1;i<=n;i++)
            sum[i]=sum[i-1]+calc(i,i+1);
        ll res=0;
        for(int i=1;i<=n;i++) {
            f[i]=sum[i-1]+res+cold[a[i+1]];
            f[i]=min(f[i],minn[a[i+1]]+hot[a[i+1]]+sum[i-1]);
            minn[a[i]]=min(minn[a[i]],f[i]-sum[i]);
            res=min(res,f[i]-sum[i]);
        }
        printf("%lld\n",f[n]);
    }
    return 0;
}
/*
1
5 6
1 6 1 4 1
3 6 4 1 4 5
1 1 1 1 4 1
*/
```


---

## 作者：tribool4_in (赞：1)

显然考虑 DP。注意到影响当前情况决策的只有两个 CPU 最后执行的程序类型，且当前最后执行的程序 $a_i$ 一定为某个 CPU 最后执行的。可以令 $dp_{i, x}$ 表示当前考虑到前 $i$ 个程序，另一个 CPU 最后执行的程序类型为 $x$。则可以写出初始状态和转移：

```cpp
dp[1][0] = cold[a[1]];
dp[i + 1][x] = dp[i][x] + ((a[i] == a[i + 1]) ? hot[a[i + 1]] : cold[a[i + 1]]);
dp[i + 1][a[i]] = dp[i][x] + ((x == a[i + 1]) ? hot[a[i + 1]] : cold[a[i + 1]]);
```

然后就可以通过 Eazy Version 了。

考虑对此优化。注意到 dp 数组的第一维可以滚动数组优化，考虑将第二维用线段树维护。对于第一个转移直接整个区间加，对于第二个转移，预先处理并进行单点取 min 即可。

代码：

```cpp
for (int i = 1; i < n; i++) {
    int val = ((a[i] == a[i + 1]) ? hot[a[i + 1]] : cold[a[i + 1]]);
    int val2 = min(query(1, 0, m) + cold[a[i + 1]], query(1, a[i + 1], a[i + 1]) + hot[a[i + 1]]);
    update(1, 0, m, val);
    update_min(1, a[i], val2);
}

---

## 作者：why_cb (赞：1)

~~祭， CF 第一次 A 看不懂摆烂去做 D 结果 D2 混杂 D1 代码交赛后十秒发现数组没开大。~~

（我还是太逊了）

---
首先先看 D1 ，

我们发现两个 CPU 显然是等价的，所以确定了一个 CPU 运行的程序，那么另一个便确定了。

由此，对于暴力的 $n^3$ DP，我们考虑简化状态。

**对于当前 $f_{i,j}$ 表示第 $i$ 次程序在一个 CPU 上运行完，另一个 CPU 上一次运行的程序是 $j$**，

这样就可以分两种情况 $n^2$ 从 $f_i$ 转移到 $f_{i+1}$：

- $a_i$ 与 $a_{i+1}$ 在同一个 CPU 上运行：
```cpp 
f[i+1][j]=min(f[i+1][j],f[i][j]+(a[i]==a[i+1]?h[a[i+1]]:c[a[i+1]]))
```

- $a_{i+1}$ 与 ${a_i}$ 在不同的 CPU 上运行：
```cpp
f[i+1][a[i]]=min(f[i+1][a[i]],f[i][j]+(j==a[i+1]?h[a[i+1]]:c[a[i+1]]));
```

最后在 $f_n$ 中取最小值即可。

再看 D2 ，显然是要求优化 DP 是复杂度降低到 $O(n\log n)$。

观察之前的二维 DP ， $f_{i-1}$ 与 $f_i$ （此时反过来好思考一点）之间的转移也分为两种情况（与之前的两个情况相对应）：

- 对于所有的 $f_{i,j}$ 等于 $f_{i-1,j}$ 加上 $c_{a[i]}$ 或者 $h_{a[i]}$（由 $a_i$ 是否等于 $a_{i-1}$ 决定）。

- 对于 $f_{i,a[i-1]}$ 还可以取 $\min{f_{i-1}}+c_{a[i]}$ 与 $f_{i-1,a[i]}+h_{a[i]}$ 中间的最小值

（由之前的转移方程直接抽象而来，可以画图理解）。

区间查询最小值，区间加，单点修改的线段树便可以实现。

---
Code：

```cpp
build(1,0,k);
for(int i=1;i<=n;i++)
{
    ll res=min(query(1,0,k)+c[a[i]],query(1,a[i],a[i])+h[a[i]]);//区间查询
    update(1,0,k,a[i]==a[i-1]?h[a[i]]:c[a[i]]);//区间加
    if(res<query(1,a[i-1],a[i-1])) update(1,a[i-1],res);//单点修改
}
printf("%lld\n",query(1,0,k));

```


---

## 作者：TTpandaS (赞：0)

首先如果一个机器贡献是 $hot$，那么一定是与上一个和它类型相同的匹配，所以转移只需要考虑 $lst_{a_i}$ 即可。现在需要算出 $[lst_{a_i}+1,i]$ 全部为另一种颜色的贡献，发现 $[lst_{a_i}+2,i]$ 是好算的，$lst_{a_i}+1$ 的贡献是不知道的，但是此时 $lst_{a_i}$ 和 $lst_{a_i}+1$ 颜色是确定的，所以用 $lst_{a_i}+1$ 的 DP 值转移即可，DP 只需要记录这一位和上一位的颜色即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int T;
int n,k,a[N],cold[N],hot[N];
int sum[N],dp[N][2][2],lst[N];
void solve(){
	scanf("%lld %lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		lst[a[i]]=0;
	}
	for(int i=1;i<=k;i++){
		scanf("%lld",&cold[i]);
	}
	for(int i=1;i<=k;i++){
		scanf("%lld",&hot[i]);
	}	
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1];
		if(a[i]==a[i-1]){
			sum[i]+=hot[a[i]];
		}
		else{
			sum[i]+=cold[a[i]];
		}
	}
	if(n==1){
		printf("%lld\n",cold[a[1]]);
		return;
	}
	dp[2][1][0]=dp[2][0][1]=cold[a[1]]+cold[a[2]];
	if(a[1]==a[2]){
		dp[2][1][1]=dp[2][0][0]=cold[a[1]]+hot[a[2]];
	}
	else{
		dp[2][1][1]=dp[2][0][0]=cold[a[1]]+cold[a[2]];
	}
	lst[a[1]]=1;
	lst[a[2]]=2;
	for(int i=3;i<=n;i++){
		dp[i][0][0]=min(dp[i-1][0][0],dp[i-1][0][1])+cold[a[i]];
		dp[i][1][0]=min(dp[i-1][0][0],dp[i-1][0][1])+cold[a[i]];
		dp[i][0][1]=min(dp[i-1][1][0],dp[i-1][1][1])+cold[a[i]];
		dp[i][1][1]=min(dp[i-1][1][0],dp[i-1][1][1])+cold[a[i]];
		if(lst[a[i]]!=0){
			if(lst[a[i]]==i-1){
				dp[i][1][1]=min(dp[i][1][1],min(dp[i-1][1][0],dp[i-1][1][1])+hot[a[i]]);
				dp[i][0][0]=min(dp[i][0][0],min(dp[i-1][0][0],dp[i-1][0][1])+hot[a[i]]);
			}
			else{
				dp[i][0][1]=min(dp[i][0][1],dp[lst[a[i]]+1][1][0]+(sum[i-1]-sum[lst[a[i]]+1])+hot[a[i]]);
				dp[i][1][0]=min(dp[i][1][0],dp[lst[a[i]]+1][0][1]+(sum[i-1]-sum[lst[a[i]]+1])+hot[a[i]]);
			}
		}
		lst[a[i]]=i;
	}
	printf("%lld\n",min(min(dp[n][0][0],dp[n][0][1]),min(dp[n][1][0],dp[n][1][1])));
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		solve();
	} 
	return 0;
} 
```

---

## 作者：ivyjiao (赞：0)

三倍经验：P11233，CF1799D1，CF1799D2。

以下 $b_i=cold_i,c_i=hot_i,m=k$。

---

由于这是 CCF（Codeforces Copying Foundation）的题，所以先看数据范围：$c_i\leq b_i$，记住这条性质，这意味着能选 $c_i$ 一定选 $c_i$。

- D0（$1\leq t\leq 500,1\leq n,m\leq 500,1\leq \sum n,\sum m \leq 500$，自己 yy 出来的东西，大概 CF1600 黄）：

这题一眼看上去，肯定是 dp，对于单组数据，考虑状态的设计：

设 $dp_{i,x,y}$ 为枚举到 $a_i$ 后，第一个 CPU 上一次运行的程序为 $x$，第二个 CPU 上一次运行的程序为 $y$ 时，最小的花费。dp 数组初始值为极大值，$dp_{0,x,y}$ 全是 $0$。

本题 $n,m\leq 500,1\leq \sum n,\sum m \leq 500$，而这个程序的时间复杂度是 $O(tnm^2)$ 的，空间复杂度是 $O(nm^2)$ 的，可以通过。

- D1（CF1900 蓝）：

D0 空间复杂度是 $O(nm^2)$ 的，直接炸飞，考虑优化空间。容易发现第一维 $i$ 可以就地滚动，于是 $dp_{x,y}$ 为枚举到 $a_i$ 后，第一个 CPU 上一次运行的程序为 $x$，第二个 CPU 上一次运行的程序为 $y$ 时，最小的花费，答案为 $\min \{dp_{x,y}\}$，这样空间复杂度就是 $O(m^2)$ 的了。

每次转移只有 $dp_{a_{i-1},y}$ 和 $dp_{x,a_{i-1}}$ 有值，其它的地方都是极大值，且只转移到 $dp_{x,a_i}$ 和 $dp_{a_i,y}$。考虑只转移这些值，其它的忽略掉，时间复杂度 $O(nm)$。

DP 转移式如下：

$$
\begin{cases}
  dp_{x,a_i}=\min\{dp_{x,y}+b_{a_i},dp_{x,a_i}+c_{a_i}\}\\
  dp_{a_i,y}=\min\{dp_{x,y}+b_{a_i},dp_{a_i,y}+c_{a_i}\}
\end{cases}
$$

本题 $n,m\leq 5000,1\leq \sum n,\sum m \leq 5000$，而这个程序的时间复杂度是 $O(tnm)$ 的，空间复杂度是 $O(m^2)$ 的，可以通过。

- D2（CF2100 蓝）：

D1 空间复杂度是 $O(m^2)$ 的，直接炸飞，考虑优化空间。我们之前说到：每次转移只有 $dp_{a_{i-1},y}$ 和 $dp_{x,a_{i-1}}$ 有值，其它的地方都是极大值，且只转移到 $dp_{x,a_i}$ 和 $dp_{a_i,y}$。那能不能以这个为突破口，把其余地方的空间全都优化掉呢？

答案是可以的。显然有 $dp_{x,y}=dp_{y,x}$，我们可以将 dp 状态压缩成一维，优化掉 $x$ 或 $y$（以下以 $x$ 为例）令 $dp_y$ 表示 $dp_{a_i,y}$，则转移变成如下：

$$
\begin{cases}
  dp_{a_i,a_{i-1}}=\min\{dp_{a_{i-1},y}+b_{a_i},dp_{a_{i-1},a_i}+c_{a_i}\}\\
  dp_{a_i,y}=dp_{a_{i-1},y}+b_{a_i}
\end{cases}
$$

再优化到：

$$
\begin{cases}
  dp_{a_{i-1}}=\min\{dp_y+b_{a_i},dp_{a_i}+c_{a_i}\}\\
  dp_{y}=dp_y+b_{a_i}
\end{cases}
$$

看完这个式子突然有一种很显然的的感觉（不然为什么 D1 D2 就差 200），感觉那些注意力惊人的大佬能一眼秒？

发现这个式子转移还是 $O(m)$ 的，怎么办？

~~注意到~~第二个式子在就地滚动，可以直接省略，用一个变量 $ans$ 来记录第二个式子的 $dp_y$ 加了多少，则有：

$$
\begin{cases}
  ans=ans+c_{a_i} & a_i=a_{i-1}\\
  ans=ans+b_{a_i} & a_i\neq a_{i-1}
\end{cases}
$$

此时式子只剩：

$dp_{a_{i-1}}=\min\{dp_y+b_{a_i},dp_{a_i}+c_{a_i}\}-c_{a_i}$

转移还是 $O(m)$？

对于 $dp_y$，我们记一个 $minn=\min\{dp_{a_{i-1}}\}$，式子变为：

$dp_{a_{i-1}}=\min\{minn+b_{a_i},dp_{a_i}+c_{a_i}\}-c_{a_i}$

转移 $O(1)$，总共时间复杂度 $O(tn)$，空间复杂度 $O(n+m)$ 可以通过。

代码（only D2）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+1;
int t,n,m,a[N],b[N],c[N],dp[N],minn,ans;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    memset(dp,0x3f,sizeof dp);
    while(t--){
        minn=0;
        ans=0;
        for(int i=1;i<=n;i++) dp[a[i]]=0x3f3f3f3f;
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=m;i++) cin>>b[i];
        for(int i=1;i<=m;i++) cin>>c[i];
        dp[0]=0;
        for(int i=1;i<=n;i++){
            if(a[i]==a[i-1]) ans+=c[a[i]];
            else{
                ans+=b[a[i]];
                dp[a[i-1]]=min(dp[a[i]]+c[a[i]],minn+b[a[i]])-b[a[i]];
                minn=min(minn,dp[a[i-1]]);
            }
        }
        cout<<minn+ans<<'\n';
    }
}
```

---

## 作者：banned_gutongxing (赞：0)

## 思路

一道特别简单的 DP 题。

定义：$f_{i,j}$ 表示现在已经处理了第 $i$ 个程序，另外一个 CPU 最后一个处理的程序类型为 $j$。

状态转移：
1. 首先每一个类型 $j$ 都可以将现在的程序放在前一个程序上方来得到，那么此时方程为 $f_{i,j}=f_{i,j}+val(i,i-1)$，其中 $val(x,y)$ 表示在第 $y$ 个程序放在第 $x$ 个程序上的代价。
2. 如果将第 $i$ 个程序放在另外一个 CPU 上运行，那么此时 $f_{i,a_{i-1}}=\min_{j\in[1,k]}\{ f_{i-1,j}+val(a_{i},j)\}$。

时间复杂度为 $O(nk^2)$。

此时在转移时记录一个最小值就行了。

时间复杂度为 $O(nk)$。

明显过不了。我们不妨把这个数组滚动一下，我们观察一下第 1 个状态转移方程，发现对于每个 $f_i$ 都要加上 $val(i,i-1)$，那么可以用一个偏移量 $\Delta$ 来记录增加。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 3e5+10;
const int INF = 0X3F3F3F3F;
int T,n,k,delta,minn,a[MAXN],hot[MAXN],cold[MAXN],f[MAXN];
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		minn = 0;delta = 0;
		for(int i = 1;i<=n;i++) scanf("%lld",a+i);
		for(int i = 1;i<=k;i++) scanf("%lld",cold+i),f[i]=INF;
		for(int i = 1;i<=k;i++) scanf("%lld",hot+i);
		f[0] = 0;
		for(int i = 1;i<=n;i++){
			int delta_ = delta;
			delta += (a[i]==a[i-1])?hot[a[i]]:cold[a[i]];
			f[a[i-1]] = min({f[a[i-1]],minn+delta_+cold[a[i]]-delta,f[a[i]]+delta_+hot[a[i]]-delta});
			minn = min(minn,f[a[i-1]]);
		}
		printf("%lld\n",minn+delta);
	}
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

考虑一个比较朴素的动态规划，设 $f(i,j)$ 表示一个 cpu 处理到 $i$，另一个在处理的类型是 $j$。设 $\omega(x,y)$ 表示一个 cpu 处理完 $x$ 再处理 $y$ 产生的费用，显然 $\omega(x,y)\in\{cold_{a_y},hot_{a_y}\}$。

考虑两种情况，一种是 $f(i,j)$ 的 $i$ 连着上面的 $i-1$。

+ $f(i,j)=f(i-1,j)+\omega(i-1,i)$。

其次是 $i$ 不知道从哪个连过来，这个时候显然的另一个 cpu 应该在处理 $a_{i-1}$。

+ $f(i,a_{i-1})=\min\{f(i-1,j)+\omega(j,i)\}$。

将 $f(i-1,\cdots)$ 和 $f(i,\cdots)$ 这两行领出来看，对于第一种转移，其实相当于一个简单的全局加法。

对于第二种转移，则是在查询的一个基础上进行单点修改。

不难发现只需要一颗能够维护区间加和区间查询最小值和单点修改的线段树就可以显著优化转移。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define lc(id) (id<<1)
#define rc(id) (id<<1|1)
#define mid (l+r>>1)
using namespace std; using ll=long long;
const int N=3e5+5; ll inf=1e17;
ll tag[N<<2], tr[N<<2];
int cold[N], hot[N], a[N];
int t, n, i, k; ll tmp1, tmp2, w, tmp;
inline void pushup(int x) {tr[x]=min(tr[lc(x)], tr[rc(x)]);}
inline void pushdown(int x)
{
	tag[lc(x)]+=tag[x]; tag[rc(x)]+=tag[x];
	tr[lc(x)]+=tag[x]; tr[rc(x)]+=tag[x];
	tag[x]=0;
	return ;
}
inline void build(int u, int l, int r)
{
	if(l==r)
	{
		tr[u]=inf; tag[u]=0;
		return ;
	}
	build(lc(u), l, mid);
	build(rc(u), mid+1, r);
}
inline void modify(int u, int l, int r, int ql, int qr, ll k)
{
	if(r<ql || l>qr) return ;
	if(ql<=l && r<=qr)
	{
		tr[u]+=k;
		tag[u]+=k;
		return ;
	}
	pushdown(u);
	modify(lc(u), l, mid, ql, qr, k);
	modify(rc(u), mid+1, r, ql, qr, k);
	pushup(u);
	return ;
}
inline void modify(int u, int l, int r, int p, ll x)
{
	if(r<p || p<l) return ;
	if(l==r)
	{
		tr[u]=min(tr[u], x);
		return ;
	}
	pushdown(u);
	modify(lc(u), l, mid, p, x);
	modify(rc(u), mid+1, r, p, x);
	pushup(u);
}
inline ll query(int u, int l, int r, int ql, int qr)
{
	if(ql>qr) return inf;
	if(r<ql || l>qr) return inf;
	if(ql<=l && r<=qr) return tr[u];
	pushdown(u);
	return min(query(lc(u), l, mid, ql, qr), query(rc(u), mid+1, r, ql, qr));
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d", &n, &k); rep(i, 1, n) scanf("%d", a+i); rep(i, 1, k) scanf("%d", cold+i); rep(i, 1, k) scanf("%d", hot+i);
		build(1,0,k); modify(1,0,k,0,0);
		rep(i, 1, n)
		{
			tmp=min(query(1, 0, k, 0, a[i]-1)+cold[a[i]], min(query(1, 0, k, a[i], a[i])+hot[a[i]], query(1, 0, k, a[i]+1, k)+cold[a[i]]));
			modify(1, 0, k, 0, k, a[i]==a[i-1]? hot[a[i]]: cold[a[i]]);
			modify(1, 0, k, a[i-1], tmp);
		}
		printf("%lld\n",query(1,0,k,0,k));
	}
	return 0;
}
```

---

