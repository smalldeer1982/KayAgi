# Checker for Array Shuffling

## 题目描述

oolimry has an array $ a $ of length $ n $ which he really likes. Today, you have changed his array to $ b $ , a permutation of $ a $ , to make him sad.

Because oolimry is only a duck, he can only perform the following operation to restore his array:

- Choose two integers $ i,j $ such that $ 1 \leq i,j \leq n $ .
- Swap $ b_i $ and $ b_j $ .

The sadness of the array $ b $ is the minimum number of operations needed to transform $ b $ into $ a $ .

Given the arrays $ a $ and $ b $ , where $ b $ is a permutation of $ a $ , determine if $ b $ has the maximum sadness over all permutations of $ a $ .

## 说明/提示

In the first test case, the array $ [1,2] $ has sadness $ 1 $ . We can transform $ [1,2] $ into $ [2,1] $ using one operation with $ (i,j)=(1,2) $ .

In the second test case, the array $ [3,3,2,1] $ has sadness $ 2 $ . We can transform $ [3,3,2,1] $ into $ [1,2,3,3] $ with two operations with $ (i,j)=(1,4) $ and $ (i,j)=(2,3) $ respectively.

In the third test case, the array $ [2,1] $ has sadness $ 0 $ .

In the fourth test case, the array $ [3,2,3,1] $ has sadness $ 1 $ .

## 样例 #1

### 输入

```
4
2
2 1
1 2
4
1 2 3 3
3 3 2 1
2
2 1
2 1
4
1 2 3 3
3 2 3 1```

### 输出

```
AC
AC
WA
WA```

# 题解

## 作者：chzhc (赞：5)

### 题意

前情提要为 CF1672F1。

给出两个长度为 $n$ 的数组 $a$ 和 $b$，你需要判断 $b$ 是否是满足**最少交换次数最大**的一个置换。

数据范围：$2 \leq n \leq 2 \times 10^5$，$1 \leq a_i \leq n$，$1 \leq b_i \leq n$。

### 做法

根据 [CF1672F1 的做法](https://chzhc.blog.luogu.org/solution-cf1672f1)所述，若每个环中都有**出现次数最多**的元素，那么这个构造就是合法的，考虑将这个出现次数最多的元素删去，若剩下的图中还存在环，那么 $b$ 就是不合法的，否则 $b$ 就是合法的（原因是每个点都一定属于某个环）。

但是直接连边的边数是 $n^2$ 级别的，考虑建虚拟结点，对应的虚拟节点连向对应 $a_i$ 相同的结点，那么 $b_i$ 就只需要对对应的虚拟节点连边即可，这样不影响联通性，并且将边数降到了 $n$ 级别。跑拓扑判断有无环即可。

时间复杂度 $\mathcal O(n)$。

[评测链接](https://codeforces.com/contest/1672/submission/154955390)。

---

## 作者：dead_X (赞：3)

## 思路
注意到最优交换策略一定是将这个序列拆成若干段，每段 $a,b$ 组成的可重集相等，然后每段通过 $|S|-1$ 次操作还原。

于是 F1 就是叫你构造使得段数最大值最小，F2 就是让你判断最大值是否取到最小。

段数最大值最小可以通过出现次数最多的那个数来做，不难证明答案即为每个数出现次数的最大值，我们只需要设计一种方案让它取到。

假设现在有 $a_1$ 个 $1$，$a_2$ 个 $2$，以此类推，记 $a_1\geq a_2\geq\cdots$，一种策略就是每次先把 $a_i\neq 0$ 的全取出来一个，循环位移一位，不难证明这样的构造需要至少分成 $a_1$ 段。

对于 F2，我们考虑 F1 中每段的末尾都一定是 $i\to 1$，我们可以抓住这一点，考虑所有连向 $1$ 的边。手模可以发现，可以分成 $a_1$ 段当且仅当去掉所有连向 $1$ 的边之后图是 DAG。

---

## 作者：DaiRuiChen007 (赞：2)

# CF1672F2 题解



## 思路分析

先考虑如何计算一个 $\{a_i\}$ 的排列 $\{b_i\}$ 的权值：对于个 $i$，建立有向边 $a_i\to b_i$，得到一张有向图 $\mathbf G$。

定义 $\operatorname{cyc}(\mathbf G)$ 表示 $\mathbf G$ 的最大环拆分的大小，即把 $\mathbf G$ 拆成尽可能多的环使得每条边都恰好在一个环中时拆分成环的数量。

注意到如下的观察：

> 观察一：
>
> 那么 $\{b_i\}$ 的权值等于 $n-\operatorname{cyc}(\mathbf G)$。
>
> 证明如下：
>
> 注意到交换 $(b_i,b_j)$ 等价于交换 $a_i\to b_i$ 和 $a_i\to b_j$ 的终点，我们的目标就是使得 $\mathbf G$ 中产生 $n$ 个环。
>
> 而一次操作可以根据 $b_i,b_j$ 在 $\operatorname{cyc(\mathbf G)}$ 对应的分解中分成是否在同一个环中的两种情况。
>
> [![pSCKeKg.png](https://s1.ax1x.com/2023/01/01/pSCKeKg.png)](https://imgse.com/i/pSCKeKg)
>
> 由上图可得，只要 $b_i,b_j$ 在同一个环中，无论如何 $\mathbf G$ 中的环数会 $+1$，而如果 $b_i,b_j$ 不在同一个环中，那么 $\mathbf G$ 中的环数一定会 $-1$。
>
> 因此对于任意的大小为 $k$ 的环分解，至少需要操作 $n-k$ 次，而不断操作两个相邻的 $b_i,b_j$ 给了我们一种操作 $n-k$ 次的方法。
>
> 综上所述，将 $\{b_i\}$ 还原至少需要 $n-\operatorname{cyc}(\mathbf G)$ 次操作。

那么原问题就转化为了最小化 $\operatorname{cyc}(\mathbf G)$ 的问题。

记 $cnt_x$ 为 $x$ 在 $\{a_i\}$ 中的出现次数。

注意到如下的观察：

> 观察二：
>
> 对于所有 $\mathbf G$ 和正整数 $x\in [1,n]$，$\operatorname{cyc}(\mathbf G)\ge cnt_{x}$。
>
> 事实上 $cnt_x$ 等于 $\mathbf G$ 中 $x$ 的入度和出度，那么原命题可以等价于证明：
>
> 对于每个 $\mathbf G$ 的最大环拆分，不存在一个环经过某个 $x$ 两次。
>
> 而根据最大环拆分的定义，经过 $x$ 两次的环会在最大环拆分中拆成两个环，因此原命题得证。

我们假设 $\{a_i\}$ 中的众数 $m$ 出现了 $c$ 次，根据观察二，那么答案 $\ge n-c$。

猜测答案 $=n-c$，即我们需要构造一个 $\mathbf G$ 使得 $\operatorname{cyc}(\mathbf G)=c$。

考虑什么时候 $\operatorname{cyc}(\mathbf G)=c$，注意到如下的观察：

> 观察三：
>
> $\operatorname{cyc}(\mathbf G)=c \iff \operatorname{cycle}(\mathbf G-\mathbf G_m)=0$ 其中 $\operatorname{cycle}$ 定义为图中的环的数量，$\operatorname{cycle}(\mathbf G-\mathbf G_m=0)$ 即在 $\mathbf G$ 中删除 $m$ 和所有与 $m$ 相邻的边得到的新图 $\mathbf G-\mathbf G_m$ 中不存在环。
>
> 证明如下：
>
> 1. 证 $\operatorname{cyc}(\mathbf G)=c \implies \operatorname{cycle}(\mathbf G-\mathbf G_m)=0$：
>
> 考虑逆否命题 $\operatorname{cycle}(\mathbf G-\mathbf G_m)>0\implies \operatorname{cyc}(\mathbf G)>c $。
>
> 那么考虑 $\operatorname{cycle}(\mathbf G-\mathbf G_m)$ 中的一个环 $\mathbf C$：在子图 $\mathbf G-\mathbf C$ 中，最大的度（等价于众数的出现个数）依然是 $c$，根据观察二，得到 $\operatorname{cyc}(\mathbf G-\mathbf C)\ge c$。
>
> 所以 $\operatorname{cyc}(\mathbf G)=\operatorname{cyc}(\mathbf G-\mathbf C)+1\ge c+1>c$。
>
> 2. 证 $\operatorname{cycle}(\mathbf G-\mathbf G_m)=0\implies \operatorname{cyc}(\mathbf G)=c$。
>
> 考虑逆否命题 $\operatorname{cyc}(\mathbf G)>c \implies \operatorname{cycle}(\mathbf G-\mathbf G_m)>0$。
>
> 由于抽屉原理，在 $\operatorname{cyc}(\mathbf G)$ 个环中必然至少有一个不经过 $m$，那么这个环的存在会使得 $\operatorname{cycle}(\mathbf G-\mathbf G_m)>0$。

运用观察三即可解决本题：对 $\mathbf G-\mathbf G_m$ 进行拓扑排序，如果存在环说明不是最优解，否则是最优解。

时间复杂度 $\Theta(n)$。


## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int a[MAXN],b[MAXN],cnt[MAXN],deg[MAXN];
vector <int> G[MAXN];
inline void solve() {
	int n,u=1;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) deg[i]=0,cnt[i]=0,G[i].clear();
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),++cnt[a[i]];
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	for(int i=1;i<=n;++i) if(cnt[a[i]]>cnt[a[u]]) u=i;
	for(int i=1;i<=n;++i) {
		if(a[i]==a[u]||b[i]==a[u]) continue;
		G[a[i]].push_back(b[i]);
		++deg[b[i]];
	}
	queue <int> q;
	for(int i=1;i<=n;++i) if(!deg[i]) q.push(i);
	while(!q.empty()) {
		int p=q.front(); q.pop();
		for(int v:G[p]) {
			--deg[v];
			if(!deg[v]) q.push(v);
		}
	}
	for(int i=1;i<=n;++i) {
		if(deg[i]) {
			puts("WA");
			return ;
		}
	}
	puts("AC");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：Schi2oid (赞：1)


考虑对于一个特定的数组 $a$，其所有排列 $b$ 中价值的最大值是多少。

对于某一个 $b$，钦定一种方式将 $b$ 置换为 $a$，那么这种情况下的价值为 $n-cnt$，其中 $cnt$ 表示钦定的置换中环的个数。因此，只需找到一种环数最多的置换。显然最优置换方式中不存在一个置换环上出现某值超过一次，否则我们可以交换它们使得 $cnt+1$。那么环数 $\ge mx$，$mx$ 为 $a$ 中出现次数最多的元素 $x$ 的出现次数。

现在我们论证所有 $b$ 的价值的最大值恰好取到 $n-mx$，即存在一个 $b$ 使得置换环数量最多为 $mx$。取构造形如 $1\rightarrow 2\rightarrow 3\rightarrow\dots\rightarrow n\rightarrow1\rightarrow 2\rightarrow 3\rightarrow\dots\rightarrow n\rightarrow\dots$ 即可，如果某值的数量被用完则跳过。

现在考虑如何判定一个 $b$ 是否能取到该最大值。我们尝试说明：能取到该最大值等价于无法在 $b$ 中找到一个不包含 $x$ 的置换环。首先，若能找到一个不包含 $x$ 的置换环，根据最优置换方式中不存在一个置换环上出现某值超过一次，剩余点构成的环数一定 $\ge mx$，即 `WA`；另外，若找不到不包含 $x$ 的置换环，说明最优置换方式中，每个置换环一定都恰好包含一个 $x$，即 `AC`。因此我们得到形如 $p\rightarrow q,\neg p\rightarrow \neg q$，所以 $p\leftrightarrow q$，证毕。

关于环是否存在，可以对每种值 $i$ 建立一个点 $con_i$ 连向所有该值所在的位置，对于每一个 $i$，连向 $con_{b_i}$，禁用 $x$ 的连边跑拓扑排序判环即可，时间复杂度线性。



---

## 作者：YxYe (赞：0)

## [Checker for Array Shuffling](https://www.luogu.com.cn/problem/CF1672F2)

[CF1672F1](https://www.luogu.com.cn/problem/CF1672F1) 的升级版

## Pre

[**点我**](https://www.luogu.com.cn/blog/YxYe/solution-cf1672f1)

## Sol

根据基础版题目的做法，我们可以得到：

- 一张图中的每个环必定存在 $a$ 数组中出现最多的元素。

于是，我们可以按照之前的方案建图，把所有情况放在一张有向图中，然后删掉 $a$ 数组中出现最多的元素。如果剩下的图中还有环，那么说明改 $b$ 构造不符合题目要求，反之则符合题目要求。

我们发现这样建边的复杂度是 $O(n^2)$ 的，考虑存在很多重复的元素，只需要对于每个 $a$ 中的值建立虚点，这样可将复杂度优化到线性。

## Code

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(int i=(a);i<=(b);i++)
#define fs(i,u) for(int i=head[u];i;i=nxt[i])
#define pii pair<int, int>
#define fir first
#define sec second
using namespace std;
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
const int maxn=4e5+10;
int T,n,a[maxn],b[maxn],c[maxn];
int in[maxn],head[maxn],to[maxn<<1],nxt[maxn<<1],cnt=1;
void add_e(int u,int v){
	to[++cnt]=v;nxt[cnt]=head[u];head[u]=cnt;in[v]++;
}
void init(){//多测不清空，OI一场空
    memset(in,0,sizeof(in));
    memset(head,0,sizeof(head));
    cnt=0;
}
bool topsort(){//拓扑排序判环
	queue<int>q;
	fo(i,1,n<<1)if(!in[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		fs(i,u){
			int v=to[i];
			if(!--in[v])q.push(v);
		}
	}
	fo(i,1,n<<1)if(in[i])return false;
	return true;
}
int main(){
	T=rd();
	while(T--){
		n=rd();
		fo(i,1,n)a[i]=rd();
		fo(i,1,n)b[i]=rd();
		fo(i,1,n)c[i]=a[i];
		sort(c+1,c+n+1);
		int cnt=0,maxx=0,maxc=0;
		fo(i,1,n){
			if(c[i]==c[i-1])cnt++;
			else{
				if(maxx<cnt){
					maxx=cnt;
					maxc=c[i-1];
				}
				cnt=1;
			}
		}
		if(maxx<cnt)maxc=c[n];
        init();
		fo(i,1,n)if(a[i]^maxc)add_e(i,n+a[i]);
		fo(i,1,n)if(b[i]^maxc)add_e(n+b[i],i);
		puts(topsort()?"AC":"WA");
	}
	return 0;
}
```

---

