# [AGC058E] Nearer Permutation

## 题目描述

在本题中，提到“顺序排列”时，指的是 $ (1,2,\cdots,N) $ 的一个排列。

对于两个排列 $ p,q $，定义它们的距离 $ d(p,q) $ 如下：

- 通过不断交换 $ p $ 中相邻的两个元素，将 $ p $ 变为 $ q $。所需的最小操作次数即为 $ d(p,q) $。

进一步地，对于排列 $ x $，定义排列 $ f(x) $ 如下：

- 设 $ y=(1,2,\cdots,N) $。考虑所有排列 $ z $，满足 $ d(x,z)\leq d(y,z) $。在这些排列中，字典序最小的排列即为 $ f(x) $。

例如，当 $ x=(2,3,1) $ 时，满足 $ d(x,z)\leq d(y,z) $ 的排列有 $ z=(2,1,3),(2,3,1),(3,1,2),(3,2,1) $。其中字典序最小的是 $ (2,1,3) $，因此 $ f(x)=(2,1,3) $。

给定排列 $ A=(A_1,A_2,\cdots,A_N) $，请判断是否存在排列 $ x $，使得 $ f(x)=A $。

每个输入文件包含 $ T $ 个测试用例。

什么是数列的字典序？判断两个不同数列 $ S $ 和 $ T $ 的大小的算法如下：

记 $ S $ 的第 $ i $ 个元素为 $ S_i $。若 $ S $ 的字典序小于 $ T $，记为 $ S<T $，大于则记为 $ S>T $。

1. 取 $ S $ 和 $ T $ 中较短的长度为 $ L $。依次比较 $ i=1,2,\dots,L $ 时 $ S_i $ 和 $ T_i $ 是否相等。
2. 若存在 $ S_i\neq T_i $ 的 $ i $，取最小的此类 $ i $ 为 $ j $。若 $ S_j $ 小于 $ T_j $，则 $ S<T $，否则 $ S>T $，算法结束。
3. 若所有 $ S_i=T_i $，则比较 $ S $ 和 $ T $ 的长度，短者字典序小。若 $ S $ 比 $ T $ 短，则 $ S<T $，否则 $ S>T $，算法结束。

## 说明/提示

### 限制条件

- $ 1\leq T\leq 150000 $
- $ 2\leq N\leq 300000 $
- $ (A_1,A_2,\cdots,A_N) $ 是 $ (1,2,\cdots,N) $ 的一个排列
- 每个输入文件中 $ N $ 的总和不超过 $ 300000 $
- 所有输入值均为整数

### 样例解释 1

例如 $ A=(2,1) $ 时，取 $ x=(2,1) $，则 $ f(x)=A $。

### 样例解释 2

例如 $ A=(2,3,1) $ 时，取 $ x=(3,2,1) $，则 $ f(x)=A $。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
2
1 2
2
2 1```

### 输出

```
Yes
Yes```

## 样例 #2

### 输入

```
6
3
1 2 3
3
1 3 2
3
2 1 3
3
2 3 1
3
3 1 2
3
3 2 1```

### 输出

```
Yes
Yes
Yes
Yes
No
No```

## 样例 #3

### 输入

```
24
4
1 2 3 4
4
1 2 4 3
4
1 3 2 4
4
1 3 4 2
4
1 4 2 3
4
1 4 3 2
4
2 1 3 4
4
2 1 4 3
4
2 3 1 4
4
2 3 4 1
4
2 4 1 3
4
2 4 3 1
4
3 1 2 4
4
3 1 4 2
4
3 2 1 4
4
3 2 4 1
4
3 4 1 2
4
3 4 2 1
4
4 1 2 3
4
4 1 3 2
4
4 2 1 3
4
4 2 3 1
4
4 3 1 2
4
4 3 2 1```

### 输出

```
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
No
No
No
No
No
No
No
No
No
No
No
No
No
No```

# 题解

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc058_e)

**题目大意**

> 对于两个长度为 $n$ 的排列 $p,q$，定义它们的距离 $d(p,q)$ 为：
>
> * 每次交换 $p$ 中相邻两个元素，使得 $p=q$ 的最小操作次数。
>
> 定义单位排列 $I=(1,2,\cdots,n)$，定义 $f(x)$ 为字典序最小的排列 $z$ 满足 $d(x,z)\le d(I,z)$。例如当 $n=3,x=(2,3,1)$ 时 $f(x)=(2,1,3)$。
>
> 给定排列 $q$，判断是否存在排列 $p$ 满足 $f(p)=q$。
>
> 数据范围：$n\le 3\times 10^5$。

**思路分析**

以下过程排列下标均为均为 $0\sim n-1$。

先考虑一种求 $f(p)$ 的算法：从 $f(p)=p$ 出发，每次尝试令字典序最小进行贪心调整：

- 记 $s=\mathrm{inv}(p)/2$。
- 进行如下操作 $n$ 次：求出 $\min\{p_0,p_1,\dots,p_s\}=p_k$，把 $p_k$ 插入答案序列 $q$ 的末尾并删除，然后令 $s\gets s-k$。

这个过程相当于贪心，每次这样的操作肯定会选取一个前缀最小值，而移动该前缀最小值对 $d(p,q)-d(I,q)$ 有 $-2k$ 的贡献，因此 $k$ 的上界就是 $\mathrm{inv}(p)/2$。

观察 $q$ 序列，如果存在某个位置使得 $q_k>q_{k+1}$（没有说明 $q=I$，显然 $f(I)=I$）。

那么说明 $q_{k+1}$ 在 $p$ 排列中一定是等到 $q_k$ 删掉后才进入可能被选范围内。

考虑删除 $q_k$ 前的 $p$ 序列，此时 $p_{s+1}=q_{k+1}$，$p_0=q_k$，并且插入 $q_{k+1}$ 后 $s=0$，因此 $q_{k+2}\sim q_n$ 与剩余的 $p$ 序列一致。

我们只需调整 $p_0\sim p_{k-1}$ 使得操作 $k$ 次后 $p$ 满足如上性质即可。

先令 $q=p$，然后依次考虑 $q_{k+1},q_{k-1},q_{k-2},\dots,q_0$，每次把当前元素 $q_i$ 向后移动 $c$ 位满足 $q_{i}\le q_{i+1}\sim q_{i+c}$，若 $i=k+1$ 则需满足 $q_k\le q_{i+1}\sim q_{i+c}$。

我们希望删除 $q_{k+1}$ 前其在 $p$ 中的位置 $x$ 与当前的 $s$ 差 $s-x=y$ 尽可能小。

那么把 $q_i$ 向后移动会使得原序列逆序对数 $+1$，删除时花费代价 $+1$，最终使得 $y$ 减小 $0.5$。

因此我们要让 $\sum c_i=\mathrm{inv}(q)/\mathrm{inv}(q)-1$，贪心让每次 $c_i$ 尽可能取最大即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5;
int n,p[MAXN],q[MAXN];
struct FenwickTree {
	int tr[MAXN],s;
	void clr() { fill(tr+1,tr+n+1,0); }
	void add(int x) { for(;x<=n;x+=x&-x) ++tr[x]; }
	int qry(int x) { for(s=0;x;x&=x-1) s+=tr[x]; return s; }
}	T;
bool check(ll d) {
	int k=0,r=n+1,c=0;
	for(int i=1;i<n;++i) if(p[i]>p[i+1]) { k=i; break; }
	for(int i=1;i<p[k];++i) {
		if(q[i]==k+1) {
			for(int j=q[i]+1;j<=n;++j) if(p[j]<p[k]) { r=j; break; }
			c=min(d,(ll)r-q[i]-1),d-=c,r=min(r,q[i]+c);
		} else if(q[i]<k) {
			if(r<=n&&d+c>=r-q[i]) return false;
			d=max(0ll,d-(r-q[i]-1));
		} else r=min(r,q[i]);
	}
	return !d;
}
void solve() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&p[i]),q[p[i]]=i;
	ll inv=0; T.clr();
	for(int i=n;i>=1;--i) inv+=T.qry(p[i]),T.add(p[i]);
	if(!inv) puts("Yes");
	else puts(check(inv)||check(inv-1)?"Yes":"No");
}
signed main() {
	int cas; scanf("%d",&cas);
	while(cas--) solve();
	return 0;
}
```

---

## 作者：UltiMadow (赞：1)

为了方便，以下下标及值域均为 $[0,n)$

先考虑对于一个 $x$ 如何求 $f(x)$，每一次我们都希望尽可能地把 $x$ 中最小的那个提到前面，于是有以下算法：

1. 记 $inv$ 为 $x$ 的逆序对数，$s=\frac {inv}2$，答案序列初始为空

2. 进行以下操作 $n$ 次（称其为操作 1）：找到 $\min\{x_0,\dots,x_{\lfloor s\rfloor}\}$，记其下标为 $i$，给 $s$ 减去 $i$，把 $x_i$ 加入答案序列，并将其从 $x$ 中删除

最终得到的答案序列即为 $f(x)$ 的结果

记 $k$ 为第一次出现 $A_{k}>A_{k+1}$ 的地方，若不存在则 $A$ 显然一定合法

不难发现经过 $k$ 次操作 1 之后的 $x$ 序列和 $s$ 一定满足以下条件：

1. $x_0=A_k$，$x_{\lfloor s\rfloor+1}=A_{k+1}$

2. $x_0=\min\{x_0,\dots,x_{\lfloor s\rfloor}\}$

3. 将 $A_k,A_{k+1}$ 从 $x$ 序列中去掉后剩下的 $x$ 序列一定是 $A_{k+2},A_{k+3},\dots,A_{n}$

那么经过 $f$ 变化之后变成 $A$ 的序列 $B$ 一定可以通过以下操作得到：

1. 初始令 $B=A$

2. 从大到小遍历 $k+1,k-1,k-2,\dots,1$，每次可以把 $B_i$ 向后移 $j$ 个位置，其中 $j$ 要满足 $\forall x\in[1,j]$ 有 $B_i<B_{i+x}$，若此时 $i=k+1$ 则还要满足 $\forall x\in[1,j]$，$A_k<B_{i+x}$

记每个 $B_i$ 向后移的距离为 $c_i$，现在的目标即为确定 $c_i$

不妨考虑 $\Delta=s-p$，其中 $s,p$ 为 $k+1$ 次操作 1 之后的 $s$ 和 $A_k$ 所在 $x$ 序列中的位置，我们希望 $\Delta=0\lor \Delta=\frac 12$

考虑 $c_i$ 增加 $1$ 对 $\Delta$ 的影响：

1. 若 $i\not=k+1$，则 $c_i$ 增加 $1$ 会导致原来序列中的逆序对个数增加 $1$，在第 $i$ 次操作 1 中 $s$ 多减少 $1$，总共会导致 $\Delta$ 减少 $\frac 12$

2. 若 $i=k+1$，则 $c_i$ 增加 $1$ 会导致原来序列中的逆序对个数增加 $1$，同时 $p$ 增加 $1$，总共会导致 $\Delta$ 减少 $\frac 12$

综上，每个 $c_i$ 增加 $1$ 都会导致 $\Delta$ 减少 $\frac 12$

当 $\sum c_i$ 为 $0$ 时显然 $\Delta=\frac{inv}2$，我们只需要检验 $\sum c_i=inv-1$ 和 $\sum c_i=inv$ 时是否存在一组合法的 $c$ 即可

确定 $\sum c_i$ 之后，可以确定原来序列中的逆序对个数，考虑对于 $A_1,A_2,\dots,A_{k-1},A_{k+1}$ 中的每个数从小到大贪心地确定 $c_i$ 的大小（即 $c_i$ 取到能保证合法的最大值），不难发现这一定是最优的

在确定 $c_i$ 的同时判断是否满足最开始的算法中的条件即可

时间复杂度 $\mathcal O(n\log n)$，瓶颈在求逆序对数量

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 300010
using namespace std;
int tst,n,a[MAXN],pos[MAXN];
struct BIT{
	int t[MAXN];
	int lowbit(int x){return x&(-x);}
	void update(int x,int y){for(;x<=n;x+=lowbit(x))t[x]+=y;}
	int query(int x){int ret=0;for(;x;x-=lowbit(x))ret+=t[x];return ret;}
	void clear(){for(int i=1;i<=n;i++)t[i]=0;}
}T;
bool check(int inv,int sum){//cerr<<"check:"<<inv<<' '<<sum<<endl;
	int s=(inv+sum)/2,k=0;
	for(int i=1;i<n;i++)
		if(a[i]>a[i+1]){k=i;break;}
	if(!k)return true;int r=n+1;
	for(int i=1;i<a[k];i++){
		if(pos[i]==k+1){
			for(int j=k+2;j<=n;j++)if(a[j]<a[k])r=min(r,j);
			int now=min(sum,r-k-2);
			sum-=now;r=min(r,k+1+now);
		}else if(pos[i]<k){
			if(r<=n&&r-pos[i]<=s)return false;
			int now=min(sum,r-pos[i]-1);
			sum-=now;s-=now;
		}else r=min(r,pos[i]);
	}return sum==0;
}
signed main(){
	scanf("%lld",&tst);
	while(tst--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]),pos[a[i]]=i;
		T.clear();int inv=0;
		for(int i=n;i;i--)inv+=T.query(a[i]),T.update(a[i],1);
		if(check(inv,inv)||check(inv,inv-1))puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

