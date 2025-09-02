# Deterministic Heap (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the two versions is the definition of deterministic max-heap, time limit, and constraints on $ n $ and $ t $ . You can make hacks only if both versions of the problem are solved.

Consider a perfect binary tree with size $ 2^n - 1 $ , with nodes numbered from $ 1 $ to $ 2^n-1 $ and rooted at $ 1 $ . For each vertex $ v $ ( $ 1 \le v \le 2^{n - 1} - 1 $ ), vertex $ 2v $ is its left child and vertex $ 2v + 1 $ is its right child. Each node $ v $ also has a value $ a_v $ assigned to it.

Define the operation $ \mathrm{pop} $ as follows:

1. initialize variable $ v $ as $ 1 $ ;
2. repeat the following process until vertex $ v $ is a leaf (i.e. until $ 2^{n - 1} \le v \le 2^n - 1 $ ); 
  1. among the children of $ v $ , choose the one with the larger value on it and denote such vertex as $ x $ ; if the values on them are equal (i.e. $ a_{2v} = a_{2v + 1} $ ), you can choose any of them;
  2. assign $ a_x $ to $ a_v $ (i.e. $ a_v := a_x $ );
  3. assign $ x $ to $ v $ (i.e. $ v := x $ );
3. assign $ -1 $ to $ a_v $ (i.e. $ a_v := -1 $ ).

Then we say the $ \mathrm{pop} $ operation is deterministic if there is a unique way to do such operation. In other words, $ a_{2v} \neq a_{2v + 1} $ would hold whenever choosing between them.

A binary tree is called a max-heap if for every vertex $ v $ ( $ 1 \le v \le 2^{n - 1} - 1 $ ), both $ a_v \ge a_{2v} $ and $ a_v \ge a_{2v + 1} $ hold.

A max-heap is deterministic if the $ \mathrm{pop} $ operation is deterministic to the heap when we do it for the first time.

Initially, $ a_v := 0 $ for every vertex $ v $ ( $ 1 \le v \le 2^n - 1 $ ), and your goal is to count the number of different deterministic max-heaps produced by applying the following operation $ \mathrm{add} $ exactly $ k $ times:

- Choose an integer $ v $ ( $ 1 \le v \le 2^n - 1 $ ) and, for every vertex $ x $ on the path between $ 1 $ and $ v $ , add $ 1 $ to $ a_x $ .

Two heaps are considered different if there is a node which has different values in the heaps.

Since the answer might be large, print it modulo $ p $ .

## 说明/提示

For the first testcase, there is only one way to generate $ a $ , and such sequence is a deterministic max-heap, so the answer is $ 1 $ .

For the second testcase, if we choose $ v = 1 $ and do the operation, we would have $ a = [1, 0, 0] $ , and since $ a_2 = a_3 $ , we can choose either of them when doing the first $ \mathrm{pop} $ operation, so such heap is not a deterministic max-heap.

And if we choose $ v = 2 $ , we would have $ a = [1, 1, 0] $ , during the first $ \mathrm{pop} $ , the following would happen:

- initialize $ v $ as $ 1 $
- since $ a_{2v} > a_{2v + 1} $ , choose $ 2v $ as $ x $ , then $ x = 2 $
- assign $ a_x $ to $ a_v $ , then $ a = [1, 1, 0] $
- assign $ x $ to $ v $ , then $ v = 2 $
- since $ v $ is a leaf, assign $ -1 $ to $ a_v $ , then $ a = [1, -1, 0] $

Since the first $ \mathrm{pop} $ operation is deterministic, this is a deterministic max-heap. Also, if we choose $ v = 3 $ , $ a $ would be a deterministic max-heap, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
7
1 13 998244353
2 1 998244353
3 2 998244853
3 3 998244353
3 4 100000037
4 2 100000039
4 3 100000037```

### 输出

```
1
2
12
52
124
32
304```

## 样例 #2

### 输入

```
1
500 500 100000007```

### 输出

```
76297230```

## 样例 #3

### 输入

```
6
87 63 100000037
77 77 100000039
100 200 998244353
200 100 998244353
32 59 998244853
1 1 998244353```

### 输出

```
26831232
94573603
37147649
847564946
727060898
1```

# 题解

## 作者：Sai0511 (赞：6)

写篇题解！      
首先根据套路，不难设计出状态 $f_{i,j}$ 表示一颗**层数**为 $i$ 的二叉树，根节点的值为 $j$ 时的合法方案数。（显然对于每一颗层数为 $i$ 的二叉树，情形类似）。      
之后根据题意，**可以转移**的充要条件即是根节点的两个儿子权值不等（这样一定是往权值大的儿子的子树转移，与另一颗无关）。所以我们由此设计出另一状态，$g_{i,j}$ 表示一颗 $i$ 层的二叉树根节点值为 $j$ 的**任意**方案数（即无需关注是否合法）。     
可以得到：      
$$
\begin{equation*}
\large{f_{i,j} = 2 \times \sum_{x=0}^j \sum_{y=\lfloor \frac{x}{2} \rfloor +1}^{x}} f_{i+1,y} \times g_{i+1,x-y} 
\end{equation*} 
$$   
这个式子的本质就是：枚举根节点两个儿子的和 $x$（因为根节点的值可能有部分是直接选中根节点而来的）。同时由 $x$ 枚举**较大**的儿子值 $y$，表明下次要进入 $y$ 侧的子树，所以此侧需要是合法的方案数 $f$，另一侧就是任意的 $g$ 了。（因为左右子树情况等价所以还需乘 $2$）。      

同理，我们也可以得到 $g$ 的转移式：   
$$
\begin{equation*}
\large{g_{i,j} = \sum_{x=0}^j \sum_{y=0}^{x}} g_{i+1,y} \times g_{i+1,x-y} 
\end{equation*} 
$$     
区别就是 $g$ 的转移不需要关注根节点儿子的值的相对大小。      
由此得到了一种 $\mathcal{O(nm^3)}$ 的做法，显然无法通过。所以我们需要考虑降复杂度（即少掉一个 $\sum$）。      
观察得知，**枚举 $x$ 过于累赘**，我们不如直接枚举较大的儿子值 $y$。那么另一颗子树可以取的值即为 $0 \to \text{min}(y-1,j-y)$（表示另一颗子树的值必然小于 $y$，且两棵子树的和应小于根节点的值 $j$）。这里就可以通过**前缀和**优化了。       
$$
\begin{equation*}
\large{f_{i,j} = 2 \times \sum_{x=0}^j \ \ f_{i+1,x} \sum_{y=0}^{\text{min}(x-1,j-x)} g_{i+1,y}}  
\end{equation*} 
$$     
这里的 $x$ 即是上述的 $y$，$y$ 既是 $x$ 对映的范围。    
同样地，$g$ 也可以做类似优化  
$$
\begin{equation*}
\large{g_{i,j} = \sum_{x=0}^j \ \ g_{i+1,x} \sum_{y=0}^{j-x} g_{i+1,y}}  
\end{equation*} 
$$         
最后的 $\sum$ 均可通过前缀和 $\mathcal{O}(1)$ 求出，所以复杂度降为 $\mathcal{O}(nm^2)$，可以通过。  
给出核心代码：
```cpp
inline void Solve() {
	scanf("%d %d %d", &n, &K, &P);
	Sg[0] = 0ll;      
	for (int i = 0; i <= K; i++) {
		f[1][i] = g[1][i] = 1ll;
		Sg[i + 1] = (Sg[i] + g[1][i]) % P;
	}   
	for (int i = 2; i <= n; i++) {         
		auto Sumg = [&](int l, int r) {                  
			return l > r ? 0ll : (Sg[r + 1] - Sg[l]) % P;    
		};  
		for (int j = 0; j <= K; j++) {  
			f[i][j] = g[i][j] = 0ll;
			for (int x = 0; x <= j; x++) {
				f[i][j] = (f[i][j] + 2ll * f[i - 1][x] * Sumg(0, std::min(x - 1, j - x)) % P) % P;
				g[i][j] = (g[i][j] + 1ll * g[i - 1][x] * Sumg(0, j - x) % P) % P;
			}	
		} 
		Sg[0] = 0ll; for (int j = 0; j <= K; j++) Sg[j + 1] = (Sg[j] + g[i][j]) % P;      
	} 
	printf("%lld\n", f[n][K]);  
	return;  
} 
```
更多思考，其实求解 $g_{i,j}$ 的值可以转化为经典的组合数学问题。即有 $2^{i}-1$ 个数，要选 $j$ 个（选的数可以重复），求方案数。     
考虑通俗化，有 $n$ 个数，要选 $m$ 个，可以重复选，求方案数。设 $x_i$ 表示第 $i$ 个数被选了几次，那答案等价于   
$$x_1+x_2+x_3+...+x_n=m$$    
有多少组**非负整数**解。我们设 $y_i=x_i+1$，所以又等价于   
$$y_1+y_2+y_3+...+y_n=m+n$$  
有多少组**正整数**解（因为一个 $y_i$ 对映一个 $x_i$）。  
根据经典的**隔板法**，考虑有 $m+n$ 个 $1$，其中有 $m+n-1$ 个空隙，而你只要在这 $m+n-1$ 中档 $n-1$ 个板，就可以将这若干个 $1$ 分成 $n$ 份，其中每一份的和就是一组解中 $y_i$ 的值。因此答案即为 $\binom{m+n-1}{n-1} = \binom{m+n-1}{m}$。  

因此 $\large{g_{i,j}= \binom{2^{i}+x-2}{x}}$。

---

## 作者：littlebug (赞：4)

dp 的状态是一点点推出来的，而不是一下子就能得出来的（一眼秒掉这道题的 dalao 们请无视这句话）。

## Solution

~~很显然~~这是一道 dp 题。

很自然地写出了状态 $f_{i,j}$ 为第 $i$ 层操作 $j$ 次的答案。考虑如何转移，因为只要保证左右儿子不相同就可以了，所以我们不妨假设左儿子 $>$ 右儿子，最后再将结果乘 $2$。

先不管复杂度，暴力枚举左右儿子，然后发现好像没法转移，因为下一步 $u$ 一定会跑到左儿子上，所以右儿子是否合法是不重要的，那么我们不妨在设一个 dp 数组 $g_{i,j}$ 表示**不保证左右儿子不相同**的方案数，然后就好转移了。

很容易推出来的方程：

$$f_{i,j} = 2 \times \sum _{x=0} ^j \sum _{y=0} ^{\min(x-1,j-x)} f_{i+1,x} \times g_{i+1,y}$$

$$g_{i,j} = \sum _{x=0} ^j \sum _{y=0} ^{j-x} g_{i+1,x} \times g_{i+1,y}$$

tips：$f_{i,j}$ 的转移别忘记乘 $2$ 哦~

然后发现第二个 $\sum$ 可以前缀和优化掉，复杂度 $O(nk^2)$。

当然，$f$ 和 $g$ 都是可以滚掉一维的，但不卡空间，没必要。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define int long long
#define il inline
using namespace std;

const int MAXN=500+5;
int n,k,p;
int f[MAXN][MAXN],g[MAXN][MAXN],s[MAXN][MAXN];

il void solve()
{
	cin>>n>>k>>p;
	
	const int mod=p;
	
	for(int j=0;j<=k;++j) f[n][j]=g[n][j]=1ll,s[n][j]=(j+1)%mod;
	
	for(int i=n-1;i>=1;--i) for(int j=0;j<=k;++j)
	{
		f[i][j]=g[i][j]=0ll; //记得清空 dp 数组！
		for(int x=0;x<=j;++x)
		{
			if(x) f[i][j]+=2ll*f[i+1][x]*s[i+1][min(x-1,j-x)]%mod;
			g[i][j]+=g[i+1][x]*s[i+1][j-x]%mod;
		}
		f[i][j]%=mod,g[i][j]%=mod;
		
		s[i][j]=((j ? s[i][j-1] : 0ll)+g[i][j])%mod;
	}
	
	cout<<f[1][k]<<'\n';
}

signed main()
{
	ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
	int T; cin>>T; while(T--) solve();
	return 0;
}
```

做完了之后可以尝试去看看 E2，是个挺复杂的大 dp。

---

## 作者：bsdsdb (赞：4)

[![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/syvmhron)](https://benben.sbs/feed/4243917)

很遗憾，您的《题解：CF2001E1 Deterministic Heap (Easy Version)》不符合推荐标准。原因是：感觉，把 我们 全部换成 哥们 之后，语义不怎么通顺了！！！

---

我们可以注意到不论最后的 $v$ 走到哪里，填数方法都可以与 $v$ 走到最右边的填数方法形成对应。所以我们可以只算 $v$ 走到最右边时的填数方法，然后再乘上 $2^{n-1}$ 就是题目的答案了。

为了方便表述，我们定义「右节点」为编号恰好为 $2^i-1$ 的节点，即一直往右子树走能到达的节点；定义「层数」为这个点到根节点的距离 $+1$，也就是说根节点的层数为 $1$；定义「$i$ 层子树」为以层数为 $i$ 的右节点为根的子树，定义函数 $\operatorname{sz}(i)$ 为 $i$ 层子树的节点数，即 $\operatorname{sz}(i)=2^{n-i+1}-1$.

我们先假设现在在计算 $d$ 层子树操作 $o$ 次的方法数，将其记为 $\mathrm{dp}_{d,o}$. 根据题意，我们发现如果右子树操作 $o1$ 次，左子树操作 $o2$ 次的话，那么这两个数就要满足 $o1>o2,o1+o2\le o$. 右子树操作 $o1$ 次的方案数其实就是 $\mathrm{dp}_{d+1,o1}$. 左子树操作 $o2$ 次其实就是将 $o2$ 个操作分给 $\operatorname{sz}(d+1)$ 个节点，根据小学二年级知识得知其方案数为 $\binom{o2+\operatorname{sz}(d+1)-1}{\operatorname{sz}(d+1)-1}$. 至此，我们得出了转移方程（初始情况显然是 $\forall 0\le j\le k,\mathrm{dp}_{n,j}=1$）：

$$
\mathrm{dp}_{d,o}=\sum_{o1>o2,o1+o2\le o}\mathrm{dp}_{d+1,o1}\cdot\binom{o2+\operatorname{sz}(d+1)-1}{\operatorname{sz}(d+1)-1}
$$

我们不难发现，那个 $\Sigma$ 底下就有 $O(o^2)$ 种情况，然后又有 $O(nk)$ 个状态，所以复杂度至少是 $O(nk^3)$. 如果能把那个小于等于改成等于就好了。此时我们注意到：

$$
\begin{aligned}
\mathrm{dp}_{d,o-1}=&\sum_{o1>o2,o1+o2\le o-1}\mathrm{dp}_{d+1,o1}\cdot\binom{o2+\operatorname{sz}(d+1)-1}{\operatorname{sz}(d+1)-1}\\
\mathrm{dp}_{d,o}-\mathrm{dp}_{d,o-1}=&\sum_{o1>o2,o1+o2\le o}\mathrm{dp}_{d+1,o1}\cdot\binom{o2+\operatorname{sz}(d+1)-1}{\operatorname{sz}(d+1)-1}\\
&-\sum_{o1>o2,o1+o2\le o-1}\mathrm{dp}_{d+1,o1}\cdot\binom{o2+\operatorname{sz}(d+1)-1}{\operatorname{sz}(d+1)-1}\\
=&\sum_{o1>o2,o1+o2=o}\mathrm{dp}_{d+1,o1}\cdot\binom{o2+\operatorname{sz}(d+1)-1}{\operatorname{sz}(d+1)-1}\\
\mathrm{dp}_{d,o}=&\mathrm{dp}_{d,o-1}+\sum_{o1>o2,o1+o2=o}\mathrm{dp}_{d+1,o1}\cdot\binom{o2+\operatorname{sz}(d+1)-1}{\operatorname{sz}(d+1)-1}
\end{aligned}
$$

现在 $\Sigma$ 的总复杂度是 $O(nk^2)$ 的了，但是还有个组合数我们没有解决。即使是用 Lucas 定理加个预处理，总复杂度也是 $O(p)$ 的，而且我们很难知道那么大个数除以 $p$ 是多少，所以也很难用 Lucas. 用组合数的定义连乘的话，由于要有理数取模，所以总复杂度会来到 $O(nk^2\log p)$，虽然能过但不太理想。但是聪明的同学可以注意到：

$$
\begin{aligned}
\mathrm{binom}_{o2}\leftarrow&\binom{o2+\operatorname{sz}(d+1)-1}{\operatorname{sz}(d+1)-1}\\
&\Downarrow\\
\mathrm{binom}_{o2}=&\dfrac{(o2+\operatorname{sz}(d+1)-1)!}{(\operatorname{sz}(d+1)-1)!o2!}\\
=&\mathrm{binom}_{o2-1}\cdot\dfrac{o2+\operatorname{sz}(d+1)-1}{o2}
\end{aligned}
$$

这样子，当我们固定 $d$（即固定 $\operatorname{sz}(d+1)$）时，可以 $O(k\log p)$ 递推出我们在这个 $d$ 下所需的所有组合数，$\log p$ 是因为要有理数取模。

总时间复杂度 $O(nk^2+nk\log p)$，空间复杂度 $O(nk)$（也可以用滚动数组优化到 $O(k)$，但是我没写）。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
#pragma G++ optimize(3,"Ofast","inline")
typedef long long ll;
using namespace std;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline string readstr(){string ret;char c;do{c=getchar();}while((c=='\n')|(c==' '));do{ret+=c;c=getchar();}while((c!='\n')&(c!=' '));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
// fastIO------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ll n = 0, k = 0, p, dp[505][505];

void init() {
	for (ll i = 1; i <= n; ++i) {
		for (ll j = 0; j <= k; ++j) {
			dp[i][j] = 0;
		}
	}
}

ll qpow(ll x, ll y) {
	if (y == 0) {
		return 1;
	} else if (y & 1) {
		return x * qpow(x, y - 1) % p;
	} else {
		return qpow(x * x % p, y / 2) % p;
	}
}
ll inv(ll x) {
	return qpow(x, p - 2) % p;
}
ll rnm(ll x, ll y) { // rational number mod
	return x * inv(y) % p;
}

ll sz(ll dpt) {
	return (qpow(2, n - dpt + 1) - 1 + p) % p;
}

int mian() {
	read(n), read(k), read(p);
	for (ll i = 0; i <= k; ++i) {
		dp[n][i] = 1;
	}
	for (ll d = n - 1; d >= 1; --d) {
		ll szd = sz(d + 1);
		ll bnm[505] = {1}; // binom
		for (ll i = 1; i <= k; ++i) {
			bnm[i] = bnm[i - 1] * rnm(i - 1 + szd, i) % p;
		}
		for (ll o = 0; o <= k; ++o) {
			if (o) {
				dp[d][o] = dp[d][o - 1];
			}
			for (ll o1 = (o + 1) >> 2; o1 <= o; ++o1) {
				ll o2 = o - o1;
				if (o1 <= o2) { // o = 2k, o1 = o2 = k, which is cannot be calculated
					continue;
				}
				dp[d][o] = (dp[d][o] + dp[d + 1][o1] * bnm[o2] % p) % p;
			}
		}
	}
	write(dp[1][k] * qpow(2, n - 1) % p), enter();
	return 0;
}

int main() {
	ll T;
	read(T);
	while (T--) {
		init();
		mian();
	}
	return 0;
}
```

---

## 作者：_lfxxx_ (赞：3)

### 题意

对于一个大小为 $2^n-1$ 的完全二叉大根堆，我们定义它的 $\operatorname{pop}$ 操作是好的，当且仅当此次操作中任意时刻，我们 $\operatorname{pop}$ 的结点在变成叶子弹出之前左右儿子权值不相等，也就是只有一种将根节点弹出去的方案。

我们将会进行恰好 $k$ 次 $\operatorname{add}$ 操作，其中每次操作你可以选一个结点，然后将根到这个节点的路径上的所有节点加 $1$。

初始我们有一个大小 $2^n-1$ 的完全二叉大根堆，每个结点权值均为 $0$。

问最后会有多少个本质不同的完全二叉大根堆的第一次 $\operatorname{pop}$ 操作是好的。

对给定质数 $p$ 取模。

$1 \le n,k \le 500$。

------

可以发现，操作完以后，这一定是一个大根堆，因为每次操作完以后，每个路径是从根到某个节点，因此父亲一定比儿子大。

因此我们只需要考虑这次 $\operatorname{pop}$ 操作的路径上左右儿子不能有相等的。

注意到如果我们对一个初始的堆进行 $k$ 次操作，根节点最后权值一定是 $k$。

那么我们可以设 $f_{i,j}$ 表示 $i$ 层（即大小 $2^i-1$）进行 $j$ 次操作有多少种合法的堆，$g_{i,j}$ 表示进行 $j$ 次操作有多少种堆（不要求合法）。
$$
f_{i,j} = f_{i,j-1} + \sum_{k=0,k \not = j - k}^i f_{i-1,k} \times g_{i-1,j-k}
$$
从 $f_{i,j-1}$ 表示第一次操作操作根节点，$g$ 的转移是类似的，只不过没有了不相等的限制。

注意尽管操作的顺序不一样但只算一种。

时间复杂度 $O(nk^2)$。

[提交记录](https://mirror.codeforces.com/contest/2001/submission/278257931)

---

## 作者：incra (赞：2)

### Sol
简单 DP，感觉 *2400 虚高了。

设 $f_{i,j}$ 表示第 $i$ 层的节点，子树内操作了 $j$ 次，满足以当前点为根的子树是一个确定的堆（也就是满足题目限制）的操作方案数，注意这里 $f_{i,j}$ 并不表示第 $i$ 个点，而是第 $i$ 层的任一点，显然第 $i$ 层的任意点方案数都是等价的，所以这样设计状态是正确的。

同理再设计状态 $g_{i,j}$，状态设计同 $f$，但是不一定要满足条件的操作方案数。

根据状态 $f_{i,j}$ 定义，得到此时这个节点的权值为 $j$。

不难得到 $f_{i,j}=\displaystyle\sum_{k=0}^j\sum_{l=0}^{j-k \operatorname{and}j\neq l}f_{i + 1,j}\times g_{i + 1,l}$，$g_{i,j}=\displaystyle\sum_{k=0}^j\sum_{l=0}^{j-k }g_{i + 1,j}\times g_{i + 1,l}$

但是这样做是 $O(nm^3)$，显然 TLE，考虑优化。

注意到我们不用考虑根节点没有操作的具体次数，所以，我们先考虑求出根节点没有操作的方案数，然后我们考虑把他加上根节点的次数，设 $h_{i,j}$ 此时是根节点没有操作过的方案数，那么 $f_{i,j}=\displaystyle\sum_{k=0}^{j}h_{j,k}$，显然可以前缀和优化，时间复杂度 $O(nm^2)$。

### Code
[Link](https://codeforces.com/contest/2001/submission/277469269)

---

## 作者：ケロシ (赞：1)

随便 DP。

设大小为 $2^i-1$ 的树，操作了 $j$ 次，是否已经确定，的方案数为 $f_{i,j,0/1}$，这里 $0$ 为确定树，$1$ 为不确定树。

初始条件肯定是 $f_{1,j,0}=1$。

考虑转移，枚举左右子树的操作次数和确定性，考虑 $f_{i-1,l,o}$ 和 $f_{i-1,r,e}$ 如何贡献到 $f_{i,l+r,0/1}$，肯定是考虑是否确定，直接判断确定性：

$v = 
[l > r ~ \mathrm{and} ~ o] 
~ \mathrm{or} ~ 
[l < r ~ \mathrm{and} ~ e] 
~ \mathrm{or} ~ 
[l=r]$

那么 $f_{i,l+r,v} \gets f_{i-1,l,o}f_{i-1,r,e}$

不难发现新树的根节点也可以操作，所以对 $f_{i}$ 再做一遍前缀和即可。

时间复杂度 $O(nk^2)$。

```cpp
const int N = 5e2 + 5;
int n, k, P;
int f[N][N][2];
inline int add(int x, int y) { return (x + y < P ? x + y : x + y - P); }
inline void Add(int &x, int y) { x = (x + y < P ? x + y : x + y - P); }
inline int mul(int x, int y) { return (1ll * x * y) % P; }
inline void Mul(int &x, int y) { x = (1ll * x * y) % P; }
void solve() {
	cin >> n >> k >> P;
	FOR(i, 1, n) FOR(j, 0, k) REP(o, 2) f[i][j][o] = 0;
	FOR(i, 0, k) f[1][i][0] = 1;
	FOR(i, 2, n) {
		FOR(l, 0, k) FOR(r, 0, k - l) REP(o, 2) REP(e, 2) {
			int v = (l > r && o) || (l < r && e) || (l == r);
			Add(f[i][l + r][v], mul(f[i - 1][l][o], f[i - 1][r][e]));
		}
		FOR(l, 1, k) Add(f[i][l][0], f[i][l - 1][0]);
		FOR(l, 1, k) Add(f[i][l][1], f[i][l - 1][1]);
	}
	cout << f[n][k][0] << endl;
}
```

---

## 作者：EricWan (赞：1)

不妨假设最终 $1$ 号点会在最后一层的最左侧被弹出，我们计算出这个问题的答案后乘以 $2^{n-1}$ 便是答案。

考虑 DP，设 $dp_{i,j}$ 为 $n=i$ 且 $m=j$ 时的答案。

我们可以算出转移方程：

$$dp_{i,j}=dp_{i,j-1}+\sum_{k=\lfloor\frac{j+2}2\rfloor}^jdp_{i-1,k}\times\begin{pmatrix}2^{i-1}-1+j-k\\2^{i-1}-2\end{pmatrix}$$

前者为从状态 $(i,j-1)$ 在当前根节点进行一次操作的转移。

后者为从状态 $(i-1,k)$ 增加一个总操作数为 $j-k$ 的右子树的转移。

上面的式子中除了那个大组合数，都可求了，考虑以 $i-1$ 和 $j-k$ 为关键字对这类组合数进行预处理即可，我们预处理 $1$ 到 $1000$ 的逆元，然后通过公式 $\begin{pmatrix}n\\m\end{pmatrix}=\frac{\prod_{i=n-m+1}^ni}{\prod_{i=1}^mi}$ 递推即可。

---

## 作者：快斗游鹿 (赞：0)

简单计数。

首先你发现无论做几次题目中的操作，大根堆的性质肯定都会被满足，证明显然。

然后考虑对最终路径做 dp，即每次走 $\max$ 后走出来的那条路径，从上往下有后效性，因此从下往上 dp。设 $f_{i,j}$ 表示到第 $i$ 个点，已经做了 $j$ 次操作。考虑往它的父亲转移，假设父亲会被**操作到** $p$ 次，这 $p$ 次可以是对父亲操作，也可以是对它的兄弟操作。而对他兄弟的操作次数 $k$ 显然需要满足 $k\le \min(p,j-1)$，否则最大值不唯一/它不是最大值。再枚举 $k$，那么就有转移：

$$f_{i,j}\times \binom{2^i-1+k-1}{2^i-1-1}\to f_{i+1,j+p}$$

后面那个组合数表示从兄弟子树中选出 $k$ 个可重复点进行操作的答案。直接暴力是 $O(n^4)$，无法通过。

然后会发现没必要枚举 $k$，可以放到外面去预处理，这样预处理和转移复杂度都是 $O(n^3)$，可以通过。由于是对路径 dp，最后记得乘上选路径的方案数。

核心代码：


```cpp
n=read();k=read();mod=read();
    inv[0]=1;inv[1]=1;
    for(int i=2;i<=k;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    for(int i=2;i<=k;i++)inv[i]*=inv[i-1],inv[i]%=mod;
    pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
    for(int p=1;p<=n;p++){
        for(int j=0;j<=k;j++){
            if(j){
                w[p][j]=w[p][j-1];
                add(w[p][j],C(p,j));
            }
            else w[p][0]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++)f[i][j]=0;
    }
    for(int i=1;i<=k;i++)f[1][i]=1;
    for(int i=1;i<n;i++){
        for(int j=0;j<=k;j++){
            for(int p=0;p+j<=k;p++){
                if(j)add(f[i+1][j+p],f[i][j]*w[i][min(j-1,p)]%mod);
            }
        }
    }
    cout<<f[n][k]*pw[n-1]%mod<<'\n';
```

---

## 作者：happybob (赞：0)

题意：

给定一棵 $n$ 层的满二叉树，节点编号范围为 $[1,2^n-1]$，并且对于任意非叶子节点 $i$，满足左节点是 $2i$，右节点是 $2i+1$，并且每个点有点权 $a_i$。

定义一次 $\texttt{pop}$ 操作为如下：

1. 令 $v\gets1$。

2. 重复以下操作直到 $v$ 是叶子节点：

   a. 对于 $v$ 的两个子节点，假设点权较大的一个点编号为 $x$。

   b. $a_x\gets a_v$。

   c. $x \gets v$。

3. $a_v\gets -1$。

我们定义 $\texttt{pop}$ 操作是确定的，当且仅当满足上述过程中，$a_{2v}\neq a_{2v+1}$。

定义一棵满二叉树是大根堆当且仅当对于所有非叶子节点 $v$ 满足 $a_v\ge a_{2v}$ 且 $a_v\ge a_{2v+1}$。

定义一个大根堆是 $\texttt{pop}$ 操作确定的当且仅当第一次 $\texttt{pop}$ 操作时 $\texttt{pop}$ 操作是确定的。

初始时，$a_v=0$，定义给一个节点 $x$ 操作一次为把 $1\rightsquigarrow x$ 路径上所有点点权加上 $1$，并求出满足**恰好**操作 $k$ 次后，不同的 $\texttt{pop}$ 操作确定的大根堆的数量，模上 $P$。

多测，$T \leq 500$，$1 \leq \sum n, \sum k \leq 500$，$10^8 \leq P \leq 10^9$，$P$ 是质数。

解法：

一眼题。

考虑 DP，记 $f_{i,j}$ 表示高度为 $i$ 的满二叉树操作 $j$ 次且 $\texttt{pop}$ 操作确定的方案数，$g_{i,j}$ 同理，但是不要求 $\texttt{pop}$ 操作确定。转移是卷积。具体地，枚举左右儿子子树操作次数，使用差分维护转移即可。直接做复杂度 $O(nm^2)$，可以通过。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <array>
using namespace std;

using ll = long long;

constexpr int N = 505;

int n, m;
ll MOD;
int t;
array<array<ll, N>, N> f, g;
array<ll, N> cf;

inline void subadd(int l, int r, ll v)
{
	cf[l] += v;
	cf[l] >= MOD ? cf[l] -= MOD : 0;
	cf[r + 1] = cf[r + 1] - v + MOD;
	cf[r + 1] >= MOD ? cf[r + 1] -= MOD : 0;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> m >> MOD;
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= m; j++) f[i][j] = g[i][j] = 0;
		}
		for (int i = 0; i <= m; i++) f[1][i] = 1, g[1][i] = 1;
		for (int i = 2; i <= n; i++)
		{
			g[i][0] = 1ll;
			for (int j = 0; j <= m + 1; j++) cf[j] = 0;
			for (int x = 0; x <= m; x++) // 左子树选x个
			{
				for (int y = 0; y + x <= m; y++)
				{
					subadd(x + y, m, g[i - 1][x] * g[i - 1][y] % MOD);
				}
			}
			for (int x = 1; x <= m; x++)
			{
				cf[x] = cf[x] + cf[x - 1];
				cf[x] >= MOD ? cf[x] -= MOD : 0;
				g[i][x] = cf[x];
			}
			for (int j = 0; j <= m + 1; j++) cf[j] = 0;
			for (int x = 0; x <= m; x++)
			{
				for (int y = 0; y + x <= m; y++)
				{
					if (x == y) continue;
					subadd(x + y, m, f[i - 1][max(x, y)] * g[i - 1][min(x, y)] % MOD);
				}
			}
			for (int x = 1; x <= m; x++)
			{
				cf[x] = cf[x] + cf[x - 1];
				cf[x] >= MOD ? cf[x] -= MOD : 0;
				f[i][x] = cf[x];
			}
		}
		cout << f[n][m] << "\n";
	}
	return 0;
}
```

---

## 作者：Jordan_Pan (赞：0)

首先读懂题意：在一棵满二叉树上从根节点开始走，每次都走左右儿子中权值更大的那一个，如果走到了叶子并且没有遇到左右儿子相等的情况，那么这条路径就是合法的。

既然如此，那么每种路径的终点叶子其实是等价的——走到第一片叶子和走到第二片或第三片叶子的路径数完全相同，因为做几次对称就能让这些路径一一对应。

于是，因为有 $2^{n-1}$ 片叶子，我们不妨每次都往左边走，只计算走到最左边叶子的方案数，再把他乘上 $2^{n-1}$。

进一步发现，题目要求的 “必须进行恰好 $k$ 次加操作” 其实等价于 “不超过 $k$ 次”，因为我们对根节点进行任意次加操作是对左右儿子没有任何影响的。亵玩几组数字，在左子树操作若干次，在右子树操作若干次，在根节点操作若干次，我们发现在根节点的操作非常废物，答案与他无关。

既然如此，我们考虑从下往上 dp。

设计状态 $f_{i,j}$ 表示从下往上第 $i$ 层，要对这颗子树进行 $j$ 次“加操作”能够生成的合法路径数。注意，我们求的是最靠左的子树，这颗子树是唯一的，这样或许好理解一些。

然而为了求出在左右子树的操作次数，我们需要枚举在根节点进行的操作次数，这就很烦人了。于是我们求刚好向下转移 $j$ 次的答案，然后取前缀和。

也可以理解为，子树内进行不超过 $j$ 次操作可以表示成恰好在根节点操作 $j$ 次，$j-1$ 次，……，$0$ 次的总和。

那么现在要求的就是恰好在左右子树内进行了 $j$ 次操作的答案。于是直接枚举在左子树进行了 $l$ 次操作，那么在右子树进行了 $r=j-l$ 次操作。由于我们要一直向左走，所以枚举时要保证 $l>r$。

由于在左子树进行操作、在右子树进行操作这两件事情互不相关，根据乘法原理，两个乘起来即为答案。~~（废话）~~

左子树的答案，就是 $f_{i-1,l}$。我是从下往上枚举深度的，所以是 $i-1$。

右子树的答案，我们都不走那边了，随便选就行。这里的操作是没有顺序区别的，于是相当于在右子树的节点数（即为 $s=2^{i-1}-1$）里选 $r$ 个，可以不选。这部分就是 $\binom{r+s-1}{r}$。~~刚开始做的时候以为他是有顺序的，算成另一个美味的东西，甚至过了小样例？~~

然后的问题就是，组合数当场求的话会让复杂度乘上一个 $\log V$，会 T。可以发现这个组合数的式子和 $j$ 没有任何关系，提到 $i$ 的循环里递推预处理就行了。

注意边界条件，$f_{1,j}=1$。复杂度 $O(nk \log V+nk^2)$。第一部分是求组合数，第二部分是 dp。

写完了，自我感觉还是相当清晰的。~~不然我为什么滚过来写题解~~

代码中的变量名均与上文相同。

~~~cpp
p[0]=1;
for(int i=1;i<n;i++)
	p[i]=(p[i-1]<<1)%mod;
//预处理2的次幂 
for(int i=1;i<=k;i++)f[1][i]=1;
for(int i=2,s;i<=n;i++){
	C[0]=1;s=p[i-1]-1;
	for(int r=1;r<=k;r++)
		C[r]=1ll*C[r-1]*(r+s-1+mod)%mod*pw(r,mod-2)%mod;
	//预处理组合数 
	for(int j=1;j<=k;j++){
		f[i][j]=f[i][j-1];
		for(int l=j,r=0;l>r;l--,r++)
			f[i][j]=(f[i][j]+1ll*f[i-1][l]*C[r]%mod)%mod;
	}
}
printf("%d\n",1ll*f[n][k]*p[n-1]%mod);
~~~

---

