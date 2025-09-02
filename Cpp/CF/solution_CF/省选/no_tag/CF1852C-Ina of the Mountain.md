# Ina of the Mountain

## 题目描述

To prepare her "Takodachi" dumbo octopuses for world domination, Ninomae Ina'nis, a.k.a. Ina of the Mountain, orders Hoshimachi Suisei to throw boulders at them. Ina asks you, Kiryu Coco, to help choose where the boulders are thrown.

There are $ n $ octopuses on a single-file trail on Ina's mountain, numbered $ 1, 2, \ldots, n $ . The $ i $ -th octopus has a certain initial health value $ a_i $ , where $ 1 \leq a_i \leq k $ .

Each boulder crushes consecutive octopuses with indexes $ l, l+1, \ldots, r $ , where $ 1 \leq l \leq r \leq n $ . You can choose the numbers $ l $ and $ r $ arbitrarily for each boulder.

For each boulder, the health value of each octopus the boulder crushes is reduced by $ 1 $ . However, as octopuses are immortal, once they reach a health value of $ 0 $ , they will immediately regenerate to a health value of $ k $ .

Given the octopuses' initial health values, find the minimum number of boulders that need to be thrown to make the health of all octopuses equal to $ k $ .

## 说明/提示

In the first test case, the minimum number of boulders thrown is $ 2 $ :

- Throw the first boulder between $ [l,r] = [1,3] $ . Then, the octopuses' health values become $ [3, 1, 3, 3] $ .
- Throw the second boulder between $ [l,r] = [2,2] $ . Then, the octopuses' health values become $ [3, 3, 3, 3] $ .

In the second test case, the minimum number of boulders thrown is $ 4 $ . The $ [l,r] $ ranges are $ [1,7], [2, 6], [3, 5], [4, 4] $ .

## 样例 #1

### 输入

```
2
4 3
1 2 1 3
7 3
1 2 3 1 3 2 1```

### 输出

```
2
4```

# 题解

## 作者：Kedit2007 (赞：20)

## CF1852C Ina of the Mountain 题解

首先将题目进行一定的转化，注意到对于一个章鱼（数字）$a_i$，我们可以执行 $(a_i \mod k) + mk$ 次操作来使其符合条件（$n$ 为非负整数）。当确定了每个章鱼需要被执行的操作次数后，我们便可以容易地得出答案。

假设确定了每个章鱼需要被执行的操作次数为 $[1, 2, 3, 0, 2, 4]$，如下图所示，总共需要执行的操作次数即为红线标出的总长度，即 $1 + 1 + 1 + 2 + 2 = 7$。

![](https://cdn.luogu.com.cn/upload/image_hosting/nd2sqx9u.png)

---

不妨将每个章鱼的取值看作**高度**，将一个章鱼需要被操作的次数加上 $k$ 称作**提升**。同时，由题意，高度恰好等于 $k$ 的章鱼可以视为高度为 $0$，在下文中默认将所有高度恰好为 $k$ 的章鱼的高度看作 $0$。

假设已经确定了 $i$ 个章鱼需要被操作的次数，考虑第 $i + 1$ 个章鱼，将第 $i$ 个章鱼的高度记作 $h_i$。

1. 若 $h_{i+1} \le h_i$，那么可以直接不做任何提升操作。
2. 若 $h_{i + 1} \gt h_i$，有以下两种选择：

	- 不做任何抬升操作，将答案增加 $h_{i + 1} - h_{i}$；
    - 选择一个 $j \le i$，使得 $h_j + k - h_{j- 1} - \max(0, h_j - h_{j - 1})$ 最小（这个最小值后文记作 $\Delta_i$），并提升 $[j, i]$ 范围中的每个章鱼，将答案增加 $\Delta_i$。
    
第一种操作很好理解，第二种操作的思想是将新增的章鱼前的章鱼提升，使得新增的章鱼不对答案产生贡献。同时，容易得知，如果选定一个章鱼，并将其及其后所有章鱼提升，其后章鱼产生的贡献不变，只有被选定的章鱼贡献产生变化。可参考下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/odldfe9v.png)

在两种操作中选择一个贡献较小的，就完成了第 $i + 1$ 个章鱼的计算。

这里按照这个思路直接模拟两种操作即可，不提供参考代码。

然而，每新增一个章鱼，这种方法就要向前遍历每一个章鱼，时间复杂度为 $O(n^2)$，无法通过此题。

---
### 优先队列优化

注意到，在上面的方法中，每个 $j$ 最多被选中一次，且选择任意一个 $j$ 进行操作后都不会影响其他任意一个 $\Delta_i$。那么，在每次新增一个章鱼后，我们可以预先计算好这个章鱼的 $\Delta_i$，并将其压入一个优先队列，这样之后的查询可以以 $O(1)$ 的复杂度完成。同时，由于每个 $j$ 最多被选中一次，当我们通过优先队列获取到对应的 $j$ 后，只需要将其出队而不需重新计算并入队。

引入优先队列进行优化后，每个章鱼需要花费 $O(\log{n})$ 的时间计算 $\Delta_i$ 并入队，另外还可能需要  $O(\log{n})$ 的时间出队。总体时间复杂度为 $O(n \log{n})$，使用的额外空间主要来自优先队列，空间复杂度 $O(n)$。

---
### 参考代码
```cpp
void work()
{
	int n, k;
	cin >> n >> k;
	vector<int> arr(n + 2);
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
		arr[i] %= k;
	}
	priority_queue<long long, vector<long long>, greater<long long>> q;
	long long ans = 0;
	for (int i = 1; i <= n + 1; i++)
	{
		if (arr[i - 1] == arr[i]) continue;
		if (arr[i - 1] > arr[i])
		{
			q.push(arr[i] + k - arr[i - 1]);
		}
		else // arr[i - 1] < arr[i]
		{
			q.push(arr[i] - arr[i - 1]);
			ans += q.top();
			q.pop();
		}
	}
	
	cout << ans << endl;
}
```

---

## 作者：Demeanor_Roy (赞：14)

- [原题链接](https://www.luogu.com.cn/problem/CF1852C)。

------------

发现其它题解都略显复杂，没怎么解释清楚。

显然原问题等价于你有一个初始全 $0$ 的序列，你每次可以区间加 $1$，问最少多少次操作可以使序列在模 $k$ 意义下为目标序列。

发现如果没有模 $k$，那这就是一个经典问题。令目标序列为 $A$，其差分序列为 $B$，那么答案为：

$$ \sum_{i}[B_i>0]B_i$$

现在考虑模 $k$，那么我们可以将其思考为**预先**对目标序列 $A$ 进行若干次区间加 $k$，求在所有可以得到的 $A'$ 序列中答案的最小值。

而 $A$ 序列上的区间加可以视作 $B$ 序列上两端点的加减。那么问题就转化为给定序列 B，你可以进行若干次操作，每次操作形如选定 $x,y$ 满足 $x<y$，使 $B_x \rightarrow B_x + k$，$B_y \rightarrow B_y -k$。目标是最小化上面那个式子。

从前往后考虑，假设当前考虑到第 $x$ 个数，分两种情况讨论：

- $B_x < 0$：此时我们将 $B_x$ 放入一个待选集合，集合中储存的是可能作为操作前一项，与后面元素一起操作的数。

- $B_x \geq 0$：此时我们从待选集合中贪心地选出最小数，如果其与当前数进行一次操作能使答案更优，我们就操作，注意到操作后当前数一定为负数，将它放入待选集合即可。不难发现，由于保留最小数不能给我们带来更大的收益，所以这样的贪心是可行的。

用一个优先队列维护上述过程即可。时间复杂度 $O(n \log n)$。

代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;

const int N=2e5+10;
int T,n,m,v[N];
inline void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]),v[i]%=m;
	for(int i=n;i>=1;i--) v[i]-=v[i-1];
	priority_queue<int,vector<int>,greater<int>> q;
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		if(v[i]<0) q.push(v[i]);
		else
		{
			if(q.empty()){ans+=v[i];continue;}
			int now=q.top();q.pop();
			if(now+m<v[i]) ans+=now+m,v[i]-=m,q.push(v[i]);
			else ans+=v[i],q.push(now);
		}
	}
	printf("%lld\n",ans);
}
int main()
{
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```


---

## 作者：Zooping (赞：14)

## CF1852C Ina of the Mountain 题解

### 如果没有思路

可以去看一下 [P4053 \[JSOI2007\] 建筑抢修](https://www.luogu.com.cn/problem/P4053)，一个**反悔贪心**，会有所启发。

## 分析

将每个数值抽象为对应高度的矩形（$k$ 看作 $0$）并按索引排列在一起，假设数字变为 $0$ 后不能变成 $k$，目标就变为了“将所有数字变为 $0$”，那么总操作数为所有相邻矩形高度上升的总和。

那我们如何减少这个总和呢？

如何将“高度变为 $0$ 后重新变为 $k$”转化成更加直观的条件？

我们将章鱼的转化变成这个**矩形高度增加 $k$**。

1. 每个矩形的转化最多会有几次？可以证明的，每个最多会有一次转化，假设出现两次转化，矩形间的上升必定大于一个 $k$ 而其他上升不可能大于一个 $k$，所以最多转化一次。

2. 假如枚举每个矩形有无转化，那么最多有 $\displaystyle2^{2  \times 10^{5}}$ 种情况，这显然会 TLE，那有无更快的方法呢？

3. 我们目标是减少上升高度，举个例子如下图左：

![图](https://cdn.luogu.com.cn/upload/image_hosting/3k25nf8y.png)

红色为对结果次数有影响的上升高度，而蓝色为对结果无影响的下降高度，我们不妨将第二、三列补一个 $k$，如上图右。我们用过长的蓝色长度换取了更短的红色长度，就是说，我们只要用贪心来求哪里增加 $k$。

例如：

我们在读到第四个矩形时发现三到四需要将 $ans$ 增加 $3$，但是一到二有 $4$ 的下降，不妨在二、三增加一个 $k$ 此时一到二变为上升 $k-4=2$ 但是三到四变为下降，总体对 $ans$ 的影响从 $5+0+0+3=8$ 变成了 $5+2+0+0=7$ 总体减小而且对四之后无影响。即**记后一个高度减前一个高度为 $cha$（红则正蓝则负），矩形增加 $k$ 的情况为 $\exists i \lt j $ 使 $ k+cha_i \lt cha_j$**。此时 $i\sim {j -1}$ 为增加 $k$ 的区间。显然地，$cha_i \lt 0$ 且 $cha_i$ 越小越好。

### 那我们如何找最小的 $cha_i$ 呢？

**优先队列**：每产生一个负数 $cha$ 都丢入小根堆，堆顶便是最小的 $cha$，当某个 $cha$ 被使用时，弹出即可。

## 参考代码

```cpp
#include<iostream>
#include<queue>
using namespace std;
int a[200009];
void s()
{
	int n,k;
	cin>>n>>k;
	for(int i=1; i<=n; i++)
	{
		cin>>a[i];
		if(a[i]==k)a[i]=0;
	}
	long long ans=0;
	priority_queue<long long , vector<long long> , greater<long long> >que;//小根堆
	for(int i=1; i<=n; i++)
	{
		//上升 a[i]-a[i-1];
		int cha=a[i]-a[i-1];
		if(!que.empty()&&que.top()+k<cha)//可以贪
		{
			ans+=(que.top()+k);
			que.pop();
			que.push(cha-k);//将改变后的下降高度继续丢入小根堆
		}
		else
		{
			if(cha<0)que.push(cha);
			ans+=max(0,cha);//只加上升量
		}

	}
	cout<<ans<<endl;
}

int main()
{
	int t;
	cin>>t;
	while(t--)s();
}

```

---

## 作者：ducati (赞：7)

## Description

[传送门](https://www.luogu.com.cn/problem/CF1852C)

## Solution

令 $c_i$ 为 $a_i$ 被区间覆盖的次数。因为所有章鱼的最终健康值均为 $k$，所以需要满足 $\forall a_i \equiv c_i \pmod k$。

若已确定 $c$，求答案是容易的，和 [积木大赛](https://www.luogu.com.cn/problem/P1969) 几乎一样。具体来说，令 $d_i = c_i - c_{i-1}(c_0 = 0)$，则答案为 $d$ 中正数的和。

令 $b_i = a_i - a_{i-1}(a_0 = 0)$，则 $\forall b_i \equiv d_i \pmod k$。可以证明，存在一组最优解，满足所有 $d \in (-k,k)$。

这样一来，每个 $d_i$ 最多只有两种取值，关键在于有两种取值 $A_i,B_i(A_i<0,B_i>0)$ 的情况。选择 $A_i$ 不会产生代价，选择 $B_i$ 会产生 $B_i$ 的代价，且各段前缀中选的数的和要 $\ge 0$。

考虑反悔贪心，若能选 $A_i$ 就选 $A_i$，否则取下面两种情况的较优者：

- 将之前的某个 $A$ 改成 $B$ 并选 $A_i$。
- 选 $B_i$。

使用小根堆维护即可，时间复杂度 $O(n \log n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;

namespace IO{
	inline char nc(){
		static char buf[500001],*p1=buf,*p2=buf;
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,500000,stdin),p1==p2)?EOF:*p1++;
	}
	char out[500001],*pout=out,*eout=out+500000;
	template<typename T> inline T read(){
		char ch=nc(); T sum=0; bool f=false;
		for(;ch<'0'||ch>'9';ch=nc()) if(ch=='-') f=1;
		while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=nc();
		return f?-sum:sum;
	}
}
#define read IO::read<int>

int n,k,ans,a[N];
void solve(){
	priority_queue<int,vector<int>,greater<int>> pq; n=read(),k=read(),ans=0;
	for (int i=1;i<=n;i++)  a[i]=read();
	for (int i=1,sum=0;i<=n;i++){
		int y=(a[i]-a[i-1]+k)%k;
		if (!y)  continue;
		
		int x=y-k;
		if (sum+x>=0)  sum+=x,pq.emplace(y);
		else{
			int num=(pq.empty()?inf:pq.top());
			if (num<y)  ans+=num,pq.pop(),pq.emplace(y),sum+=k+x;
			else ans+=y,sum+=y;
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	int T=read();
	while (T--)  solve();
	return 0;
}
```



---

## 作者：Zi_Gao (赞：2)

## 前言

一个有意思的贪心，但是很少有题解证明了正确性，至少我看着有点迷迷糊糊的，总结一下。

## 正文

### 0x00 题目分析

转化一下题目就是给定一个序列 $a$，可以进行若干次操作每次操作选择一个区间使得这个区间元素值减一，求在 $\bmod\, k$ 意义下使得数列变成全 $0$ 数列所需的最小操作次数。

发现这个题的难点在于：$\bmod\, k$ 意义下十分难受。那么自然考虑去掉 $\bmod\, k$ 的条件，求答案。十分经典，对于 $a$ 序列的差分序列 $b$，有答案为：

$$\sum_i b_i\left[b_i\gt0\right]$$

具体证明可以理解为，每当有一个元素上升，那么上升的这一格就不能用之前的区间覆盖掉了，答案贡献 $1$。但是在这个题中需要 $\bmod\, k$ 而主要的问题就是当这个数到 $-1$ 后会重新变成 $k-1$，这里需要读者思考一下。

### 0x01 找到联系

我们不妨想成是把这个值加上了 $k$，然后不 $\bmod$ 计算答案，不难发现这和直接在 $\bmod\, k$ 下计算答案是等价的。那么现在可能对答案的贡献有两个东西了：

1. 差分序列的贡献。

2. 区间加 $k$ 的贡献。

考虑区间加 $k$ 这个东西有什么用？发现有这样一种情况就是当差分数组 $b_i$ 特别大时，我们对 $i$ 加上 $k$ 即可抹去 $b_i$ 让 $b_i\leq 0$，因为 $\bmod\, k$ 了，元素大小不会超过 $k$。这两种选择像是一种决策性质的东西，对于每一个点看是直接计算 $b_i$ 更优；还是选择一个以 $i$ 为开右边界的区间加上 $k$ 更好。要衡量哪个方案更好考虑量化这两个决策：

1. 对于 $b_i\le0$ 时，选择这个决策的答案贡献为 $b_i$；否则答案贡献为 $0$，且容易证明 $b_i\leq 0$ 时无脑选择这个决策答案不会更劣。

2. 选择一个左端点 $j$，对于 $\left[j,i\right)$ 区间元素加上 $k$，由于加上了 $k$ 在区间内部的元素大小相对作差关系不会变化，则无答案贡献；而区间两个端点的贡献只有左端点，应为右端点直接变成下降，计算左端点答案贡献为 $b_j+k-\min(b_j,0)$ 应为这个地方差分会变大，新的贡献是 $b_j+k$，而原来的贡献是 $\min(b_j,0)$，并且 $b_j+k\geq0$。

可以从这个地方开始 DP 了，但是实际上不需要。


### 0x02 继续观察性质：

1. 一个点不可能作为左端点两次，这样答案只会更劣。意味着我们可以把某个点拿来决策了就扔。

2. 选择一段区间加 $k$，对其他地方完全不影响可以正常执行。

3. 在某一个点选择了一段区间加 $k$，在后续中不会出现这里不执行这个操作让答案更劣的情况，这样操作后后续不管想选哪个点作为左端点都不于这个操作冲突，因为这个操作只会影响两个端点，其他点的差分值不变，而左端点和又端点对答案的贡献又是最优的。

那么考虑贪心，用小根堆维护 $b_i+k$ 的值，每次找最小的点出来，看看哪个决策更优。

### 0x03 代码实现

分类讨论执行：

1. $b_i\le0$ 时直接忽略，把 $b_i+k$ 入堆。

2. $b_i\ge0$ 时可以考虑一种更精巧的实现，考虑进行区间加 $k$ 还是朴素贡献

	- 当 $b_i$ 大于堆顶时，选择堆顶的答案贡献，弹出堆顶并且把 $b_i-k+k$ 放入堆。
    
   - 否则选择 $b_i$。
   
这种时候直接一开始就放入 $b_i$ 然后选择堆顶答案并且弹出，即可自动维护好答案。

AC CODE

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE long long
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

void solve(){
    std::priority_queue<int,std::vector<int>,std::greater<int>> Q;
    register int i,lat=0,a,diff;
    register long long ans=0;
    int n=read();
    int k=read();
    for(i=0;i<n;++i){
        diff=(a=read()%k)-lat,lat=a;
        if(diff<=0) Q.push(diff+k);
        else Q.push(diff),ans+=Q.top(),Q.pop();
    }
    print(ans);putchar('\n');
    return;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    int T=read();
    while(T--) solve();

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

## 总结

这个题考察两个能力，转化困难问题的能力和观察性质的能力。

---

## 作者：BreakPlus (赞：2)

+ 不难发现如果没有取模是典题，对于相邻两个数，如果差为正，那么这个差值会对答案有贡献。

+ 加入取模后，我们不难想到先作原序列的差分。但是这个差分会有两种取值，一种是正的，一种是负的。而差分值加很多个 $k$ 或这减很多个 $k$ 都没有意义，这是不难发现的。

+ 我们发现，选取每个值正负的同时，我们要在其是类似括号序列的东西（任意前缀 $\ge 0$）的条件下答案尽量小。

+ 想到这里我就寄了，难过。其实这种其他做法根本没有头绪的可以尝试贪心。

+ 而这里有 $\ge 0$ 的条件，不难想到带悔贪心。先选负数，如果选了会导致前缀和 $< 0$，那么两种选择：改成选正数；将前面的一个负数改成正数。不难发现一个负数改成正数会 $+k$，那么改多个负数没有意义。

+ 小根堆维护即可。

```cpp
ll n,k,a[1000005]; 
priority_queue<ll,vector<ll>,greater<ll> >Q; 
void solve(){
	while(!Q.empty()) Q.pop();
	n=read(),k=read();
	ll ans=0, sum=0; 
	for(ll i=1;i<=n;i++){
		a[i]=read();
		ll now=(a[i]-a[i-1]+k)%k;
		if(sum+now-k>=0){
			sum+=now-k;
			Q.push(now);
		}else{
			ll x=(Q.empty()?1e18:Q.top());
			if(x<=now) {
				Q.pop();
				ans+=x; sum+=now; Q.push(now);
			}else{
				ans+=now; sum+=now;
			}
		} 
	}
	printf("%lld\n",ans);
} 
```

---

## 作者：Zimo_666 (赞：1)

#### E. Ina of the Mountain

假设我们已经确定了前 $a_i$ 个序列的操作次数，下面我们考虑加入 $a_{i+1}$。

我们考虑它的可能贡献。

若 $a_{i+1}\le a_{i}$，则显然可以不做任何操作。

若 $a_{i+1}>a_i$，那么有如下两种操作方案。

- 不考虑对前面 $1\le j\le i$ 做任何抬升方案，直接答案增加 $a_{i+1}-a_i$。
- 我们考虑选择一个 $j\le i$，使得 $a_j+k-a_{j-1}-\max(0,a_j-a_{j-1})$ 最小，含义即我们把一个 $a_j$ 提升 $k$，而后或许需要考虑可能会减少 $a_{j-1}$ 所需要的答案。也就是说对于 $i\in[j,i]$，所有答案增加这些。

我们显然对于第二个有 $O(n^2)$ 的做法，但是显然不是最优。

注意到上面的选取 $j$ 的方案，对于每一个 $j$ 显然只能被充当一次答案。于是我们考虑使用优先队列维护上面两种情况。对于 $a_{i+1}\le a_i$ 显然有可以贡献上面的情况，于是计算好贡献并入队。最后统计到需要做操作的情况时，直接取出队首即可。复杂度 $O(n\log n)$。

[Code](https://codeforces.com/contest/1853/submission/222157342)

---

## 作者：Mashu77 (赞：0)

我们先从题目的一部分入手。

如果说，我们没有当一个数为 $0$
 时，让这个数变成 $k$
 的性质，我们如何求答案呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/3fputswx.png)

很简单，在图上就是：


绿色线段的长度加起来即为答案，本图中是 $6$。

我们考虑很显然地，将一个数从 $0$
 变为 $k$
 即为将一个数一开始加上 $k$。

我们如果要让第 $i$
 列格子前面的数的代价减小，那么一定会在 $i$
 前面找一个 $j$
 让 $[j,i-1]$
 的区间内的所有数都加上 $k$，而代价为 $a_j+k-a_{j-1}$
 我们只需要将所有的 $a_j+k-a_{j-1}$
 放进优先队列里面，每次取最小的，和现在的 $a_i-a_{i-1}$
 取 $\min$
 即可。
 ```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int NN = 2e5 + 8;
int n,k;
ll a[NN];
void solve(){
	scanf("%d%d",&n,&k);
	for(int i = 1; i <= n; ++i) scanf("%lld",&a[i]),a[i] %= k;
	a[n+1] = 0;
	priority_queue<ll, vector<ll>, greater<ll> > q;
	while(!q.empty()) q.pop();
	ll ans = 0;
	for(int i = 1; i <= n + 1; ++i){
		if(a[i - 1] == a[i]) continue;
		if(a[i - 1] > a[i]) q.push(a[i] + k - a[i - 1]);
		else{
			q.push(a[i] - a[i - 1]);
			ans += q.top();
			q.pop();
		}
	}
	printf("%lld\n",ans);
}
int T;
int main(){
	scanf("%d",&T);
	while(T--) solve();
}

---

## 作者：hfjh (赞：0)

# CF1852C 题解
先考虑如果没有 “$a_{i} = 0$，则将 $a_{i}$ 变为 $k$”，直接差分后统计所有正数加起来。

> 因为原序列全是正数，所以差分序列正数的和一定比负数的和的绝对值多，如果一般情况原序列有正有负那么需要对正数和负数分别求和取绝对值然后取 max。

现在就是多一种操作，区间 $+k$ 并且不消耗操作次数。

对应差分序列就是一个点 $+k$，后面的一个点 $-k$（也有可能不减）。

显然原序列上一个负数 $+k$， 一个正数 $-k$ 可能让答案更优秀。

设负数是 $a_i$，正数是 $a_j(i<j)$，那么如果 $a_i + k < a_j$ 就可以选。

用优先队列存负数 $a_i$，遇到一个正数就取出最小的那个判断。
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 2e5 + 10;
int t;
int n, k;
int a[N], p[N];
ll ans = 0;
priority_queue<int, vector<int>, greater<int> > q;
void input(){
	cin>>n >> k;
	for(int i = 1; i <= n; ++i){
		cin>>a[i];
		if(a[i] == k) a[i] = 0;
		p[i] = a[i] - a[i - 1];
	}
}
void op(){
	while(!q.empty()) q.pop();
	for(int i = 1; i <= n; ++i){
		if(p[i] < 0)q.push(p[i]);
		else{
			if((!q.empty()) && q.top() + k < p[i]){
				ans = ans + q.top() + k;
				q.pop();
				q.push(p[i] - k);
			}else ans += p[i];
		}
	}
}
int main(){
	cin>>t;
	while(t--){
		ans = 0;
		input();
		op();
		cout<<ans<<'\n';
	}
} 
```

---

## 作者：5k_sync_closer (赞：0)

设 $i$ 章鱼最终被打了 $c_i|c_i\equiv a_i\pmod k$，则答案为 $\sum\limits_{i=1}^n\max(c_i-c_{i-1},0)$。

有结论：$\forall i,-k<c_i-c_{i-1}<k$。

（证明：若 $c_i-c_{i-1}\ge k$，那将 $c_i\gets c_i-k$ 满足结论，此时 $c_i-c_{i-1}$ 减少 $k$，而 $c_{i+1}-c_i$ 至多增加 $k$，不会变劣）

于是每个 $c_i-c_{i-1}$ 只会有两种取值 $A_i<0,B_i>0$，考虑对每一位选择 $A_i$ 或 $B_i$，

同时需要保证每段前缀选择的数之和（即为 $c_i$）非负。

从前往后依次选择，能选 $A_i$ 就选 $A_i$（贡献为 $0$），否则考虑：

- 选 $B_i$（贡献为 $B_i$），
- 把之前某个 $A_j$ 改成 $B_j$（贡献为 $B_j$），然后选 $A_i$。

堆维护之。

```cpp
#include <queue>
#include <cstdio>
#define int long long
using namespace std;
int T, n, k, s, z, a[200050];
signed main()
{
    scanf("%lld", &T);
    while (T--)
    {
        s = z = 0;
        priority_queue<int, vector<int>, greater<int>> q;
        scanf("%lld%lld", &n, &k);
        for (int i = 1, A, B, C; i <= n; ++i)
        {
            scanf("%lld", a + i);
            if (!(B = (a[i] - a[i - 1] + k) % k))
                continue;
            A = B - k;
            if (s + A >= 0)
                s += A, q.push(B);
            else
            {
                C = q.empty() ? 1e18 : q.top();
                if (C < B)
                    s += A + k, z += C, q.pop(), q.push(B);
                else
                    s += B, z += B;
            }
        }
        printf("%lld\n", z);
    }
    return 0;
}
```


---

## 作者：muzqingt (赞：0)

## [CF1852C Ina of the Mountain](https://www.luogu.com.cn/problem/CF1852C)题解

我们把章鱼的生命值转化为矩形高度，红色部分为章鱼的生命值，黑色直线为选择的区间。我们发现只有后面章鱼的生命值相对于前一个章鱼增加时才会增加代价。

![](https://cdn.luogu.com.cn/upload/image_hosting/x9ivm0dw.png)

对于章鱼的生命值有两种情况，设章鱼的生命值分别为 $a_1$，$a_2$。

1. 前一个章鱼生命值小于后面一个章鱼。$a_1 < a_2$。

2. 前一个章鱼的生命值大于后面一个章鱼。$a_1 > a_2$。

对于第一种情况，我们可以让这个章鱼前方一部分加 $k$，转换为第二种情况。或者答案加上后一个章鱼和前一个章鱼的生命值的差值，代价是答案加上 $a_2-a_1$。

对于第二种情况，我们可以在此时把后面的章鱼的生命值增加 $k$，代价是答案增加 $a_2 + k-a_1$，或者不进行任何操作。

我们可以把每一种方案的代价放入优先队列中，每次遇到第一种情况时选出代价最小的方案统计到答案中。

### code

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define ll long long
using namespace std;
int n,k,a[200010];
ll ans;
int work(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i]%=k;
    }
    priority_queue<int,vector<int>,greater<int> >q;
    for(int i=1;i<=n;i++){
        if(a[i]>a[i-1]){
            q.push(a[i]-a[i-1]);
            ans+=q.top();
            q.pop();
        }
        if(a[i]<a[i-1]){
            q.push(a[i]+k-a[i-1]);
        }
    }
    printf("%lld\n",ans);
    ans=0;
    return 0;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        work();
    }
}

```

---

