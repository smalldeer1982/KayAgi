# Maximize the Difference

## 题目描述

For an array $ b $ of $ m $ non-negative integers, define $ f(b) $ as the maximum value of $ \max\limits_{i = 1}^{m} (b_i | x) - \min\limits_{i = 1}^{m} (b_i | x) $ over all possible non-negative integers $ x $ , where $ | $ is [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

You are given integers $ n $ and $ q $ . You start with an empty array $ a $ . Process the following $ q $ queries:

- $ v $ : append $ v $ to the back of $ a $ and then output $ f(a) $ . It is guaranteed that $ 0 \leq v < n $ .

The queries are given in a modified way.

## 说明/提示

In the first test case, the final $ a=[1,2] $ . For $ i=1 $ , the answer is always $ 0 $ , irrespective of $ x $ . For $ i=2 $ , we can select $ x=5 $ .

In the second test case, the final $ a=[3,1,0,5] $ .

## 样例 #1

### 输入

```
2
5 2
1 2
7 4
3 1 5 2```

### 输出

```
0 2
0 2 3 5```

# 题解

## 作者：murder_drones (赞：8)

## 简要题意

维护一个值域为 $[0,n)$ 的集合 $a$，有 $q$ 次插入，在每次插入之后输出以下式子。

$$\max_x (\max_{i=1}^{\lvert a \rvert} {(a_i \operatorname{or} x)} - \min_{i=1}^{\lvert a \rvert} {(a_i \operatorname{or} x)})$$

其中 $n \le 2^{22}$，$q \le 10^6$，要求强制在线。

## 题目分析

假设产生答案的 $max$ 项的 $i$ 为 $s$，产生答案的 $min$ 项的 $i$ 为 $t$。

考虑在已知 $s$ 和 $t$ 的情况下怎么算答案。

先给出结论，答案会是 $a_s-a_s \operatorname{and} a_t$。

至于原因，我们对于每一位单独考虑（因为位与位之间无关）。

1. 若 $a_s$ 与 $a_t$ 的第 $i$ 位均为 $1$，显然 $x$ 这一位是什么不要紧，此时贡献为 $0$；
2. 若 $a_s$ 与 $a_t$ 的第 $i$ 位均为 $0$，显然 $x$ 这一位是什么也不要紧，此时贡献为 $0$；
3. 若 $a_s$ 的第 $i$ 位为 $0$，$a_t$ 的这一位为 $1$，贡献为 $-2^i$。$x$ 这一位填 $1$ 就能使贡献为 $0$；
4. 若 $a_s$ 的第 $i$ 位为 $1$，$a_t$ 的这一位为 $0$，$x$ 这一位应该填 $0$，此时贡献为 $2^i$。

由此我们发现答案就是第4种情况的贡献和，即如下式子。

$$a_s-a_s \operatorname{and} a_t$$

回到题目，假设新插入的数为 $v$，则新的 $s$ 与 $t$ 只能是以下三种情况。

1. $a_s$ 和 $a_t$ 中的任何一个都不是 $v$。
2. $a_s$ 是 $v$。
3. $a_t$ 是 $v$。

对于第一种情况，直接继承上一次的答案。

对于第二种，答案为以下式子。

$$\max_{i=1}^{\lvert a \rvert -1} {(v-v \operatorname{and} a_i)}$$

于是问题转化成维护给定 $v$，维护以下式子。

$$\min_{i=1}^{\lvert a \rvert -1} {(v \operatorname{and} a_i)}$$

这是一个经典问题，使用按位贪心即可解决。

具体地，只需要记录 $f_S$ 表示 $a$ 中是否有某个数的**超集**为 $S$ 。

$f_S$ 的处理可以使用如下的记忆化代码来做。

```cpp
void dfs(int S)
{
	f[S]=1;
	for(int i=0;i<=n;i++)
	{
		if(!(S&(1<<i)) && !(f[S^(1<<i)]))
			dfs(S^(1<<i));
	}
}
```


处理完 $f_S$ 后有如下代码计算$\min_{i=1}^{\lvert a \rvert -1} {(v \operatorname{and} a_i)}$。

```cpp
int now=(1<<22)-1;
for(int i=22;i!=-1;i--)
{
	if((v&(1<<i))&&f[now^(1<<i)])
		now^=1<<i;
}
ans=now&v;
```

大致的思路是对于 $v$ 的第 $i$ 位，如果为 $1$ 就看集合中有没有这一位是 $0$ ，且满足前面已经选择的要求（即 $now$ 所记录的）的数。

计算出结果直接代入式子即可。

第三种情况类似，即求以下式子。

$$\max_{i=1}^{\lvert a \rvert -1} {(a_i-v \operatorname{and} a_i)}$$

尝试变形，将位运算以外变成与只与 $v$ 相关的样子。

$$\max_{i=1}^{\lvert a \rvert -1} {(v \operatorname{or} a_i - v)}$$

这个变形是好理解的，从意义上来理解就是 $a_i$ 与 $v$ 中至少有一个是 $1$ 的位数减去 $v$ 上是 $1$ 的位数，即 $a_i$ 的这一位为 $1$，$v$ 的这一位为 $0$ 的位数。

即变成了求如下式子。

$$\max_{i=1}^{\lvert a \rvert -1} {(v \operatorname{or} a_i)}$$

需要维护子集，进行按位贪心。

于是这道题就做完了。

## CODE

稍微注意一下我的代码里面的 $n$ 不是题目里的意义，而是实际上的 $\log_2 n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1<<23;

int n;
bool mor[maxn];//超集的f
bool les[maxn];//子集的f

void dfs1(int x)
{
	mor[x]=1;
	for(int i=0;i<=n;i++)
	{
		if(!(x&(1<<i)) && !(mor[x^(1<<i)]))
			dfs1(x^(1<<i));
	}
}
void dfs2(int x)
{
	les[x]=1;
	for(int i=0;i<=n;i++)
	{
		if((x&(1<<i)) && !(les[x^(1<<i)]))
			dfs2(x^(1<<i));
	}
}

int t;
int tn;
int q;
int U;

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&q);
		tn=n;
		n=__lg(n);
		U=(1<<(n+1))-1;
		for(int i=0;i<=U;i++)
			les[i]=mor[i]=0;
		int ans=0;
		for(int i=1;i<=q;i++)
		{
			int v;
			scanf("%d",&v);
			v=(v+ans)%tn;
			int now=U;
			for(int i=n;~i;i--)
			{
				if((v&(1<<i))&&mor[now^(1<<i)])
				  now^=1<<i;
			}
			ans=max(ans,v-(now&v));
//			printf("%d ",now&v);
			now=0;
			for(int i=n;~i;i--)
			{
				if(!(v&(1<<i))&&les[now|1<<i])
				  now|=1<<i;
			}
			ans=max(ans,(now|v)-v);
//			printf("%d ",now|v);
			dfs1(v);
			dfs2(v);
			printf("%d ",ans);
		}
		printf("\n");
	}
	
	return 0;
}

```

参考资料：

[NOIP模拟-----位运算](https://www.cnblogs.com/forever-/p/9736088.html)

[位运算](https://www.cnblogs.com/Mars-LG/p/0x01_bit.html)

---

## 作者：sunkuangzheng (赞：4)

$\textbf{CF1930F *2600}$

> - 给定 $n,q$，支持 $q$ 次操作：先在序列 $a$ 末尾插入 $a_i$，再求在所有非负整数 $x$ 里 $\max (a_i|x) - \min(a_i|x)$ 的 $\max$。

> - $0 \le a_i < n,1 \le n \le 2^{22},1 \le q \le 10^6$。


位运算题常见套路是转化题意。考虑如果只有两个数字 $a,b$，式子的最大值该怎么求。如果希望 $a | x$ 成为 $\max$，那么只有 $a_i = 1,b_i = 0$ 的位置可以产生贡献，也就是 $a \operatorname{AND} -b$ 的值。对于序列长度 $> 2$ 的情况，我们可以枚举 $(a,b)$，计算 $\max(a \operatorname{AND} -b,b \operatorname{AND} -a)$ 的值取 $\max$。

考虑每次插入一个新元素 $a$，我们都需要在前面找到元素 $b$，求出 $\max(a \operatorname{AND} -b,b \operatorname{AND} -a)$ 的 $\max$。注意到 $\sum n \le 2^{22}$，考虑和值域有关的做法。暴力枚举 $a$ 和 $a$ 的补集的子集，如果 $a$ 的子集 $p$ 和之前某个 $-b$ 的子集 $q$ 相等，则 $p$ 是一个合法答案。记忆化搜索，一共只有 $\mathcal O(n)$ 个数。枚举子集时，只寻找只比它少一位的数字，这样复杂度即为 $\mathcal O(n \log n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 18.02.2024 09:00:50
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = (1 << 22) + 1;
using namespace std;
int T,n,q,li,x,lst,f[N][2];
void los(){
    cin >> n >> q,li = (1 << __lg(n - 1) + 1),lst = 0; 
    for(int i = 0;i <= li;i ++) f[i][0] = f[i][1] = 0;
    while(q --){
        cin >> x,x = (x + lst) % n;
        for(int tp = 0;tp <= 1;tp ++){
            queue<int> q; q.push((tp ? x : li - 1 - x));
            while(q.size()){
                int x = q.front(); q.pop();
                if(f[x][tp]) continue; f[x][tp] = 1;
                if(f[x][!tp]) lst = max(lst,x);
                for(int i = 1;i <= li;i *= 2) if(x & i) q.push(x ^ i); 
            }
        }cout << lst << " ";
    }cout << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
    
```

---

## 作者：OldDriverTree (赞：3)

# Solution
下文令 $\operatorname{or}$ 表示按位或，$\operatorname{and}$ 表示按位与，$\operatorname{not}$ 表示按位取反。

我们先考虑如何快速处理单次询问。

先枚举最大值的位置 $i$，这时 $x$ 取 $\operatorname{not} a_i$ 显然最优，这时的答案就是 $\operatorname{not}\min\limits_{j=1}^n\{ a_j\operatorname{or}\operatorname{not} a_i\}=\max\limits_{j=1}^n\{\operatorname{not}(a_j\operatorname{or} \operatorname{not} a_i)\}$（这里令 $n$ 为序列长度）。

先化简一下这个 $\operatorname{not}(a_j \operatorname{or} \operatorname{not} a_i)$。

按位考虑 $a_i$ 和 $a_j$ 的每一位：
+ 如果 $a_i=0$ 且 $a_j=0$，答案为 $0$。
+ 如果 $a_i=0$ 且 $a_j=1$，答案为 $0$。
+ 如果 $a_i=1$ 且 $a_j=0$，答案为 $1$。
+ 如果 $a_i=1$ 且 $a_j=1$，答案为 $0$。

可以发现这个式子就等于 $\operatorname{not} a_i\operatorname{and} a_j$。

对于单次询问，就转化为了求 $\max\limits_{i=1}^n\max\limits_{j=1}^n\{ \operatorname{not} a_i\operatorname{and} a_j\}$。

直接枚举 $i$ 和 $j$ 时间复杂度显然是 $O(n^2)$ 的，考虑如何优化。

设 $f_S$ 表示是否存在一个 $i$ 满足 $S\subseteq a_i$，$g_S$ 表示是否存在一个 $i$ 满足 $S\subseteq \operatorname{not} a_i$，答案就为同时满足 $f_S$ 和 $g_S$ 的最大值。

问题变为如何快速维护 $f$ 和 $g$，可以发现每次插入只会让一部分为 $0$ 的位置变为 $1$，一共最多只会发生 $O(n)$ 次变化（下面的 $n$ 为题目中给出的 $n$），每次插入时 $\texttt{DFS}$ 可以做到 $O(q+n\log n)$，可以通过。

# Code
```c++
#include<bits/stdc++.h>
#define int unsigned
using namespace std;
const int N=1<<23;
int T,n,m,l,ans;
bool f[N],g[N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
void dfs(int x)
{
	if (f[x]) return; f[x]=true;
	if (g[x]) ans=max(ans,x);
	for (int i=0;i<l;i++)
	if (x>>i&1) dfs(x^(1<<i) );
}
void Dfs(int x)
{
	if (g[x]) return; g[x]=true;
	if (f[x]) ans=max(ans,x);
	for (int i=0;i<l;i++)
	if (x>>i&1) Dfs(x^(1<<i) );
}
main()
{
	T=read();
	while (T--)
	{
		n=read(),m=read(),ans=0;
		l=32-__builtin_clz(n);
		int ALL=(1<<l)-1;
		while (m--) {
			int x=(read()+ans)%n;
			dfs(x),Dfs(ALL^x),printf("%u ",ans);
		}
		for (int i=0;i<=ALL;i++)
		f[i]=g[i]=false;
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：3)

### [CF1930F Maximize the Difference](https://www.luogu.com.cn/problem/CF1930F)

考虑取到答案的 $b_i, b_j$ 和 $x$。考虑二进制下的某一位：

- 若 $b_i = b_j$，那么 $x$ 无论怎么取，贡献都为 $0$。
- 若 $b_i = 1$ 且 $b_j = 0$，则 $x = 0$，贡献为 $1$（$x = 1$ 时贡献为 $0$）。
- 若 $b_i = 0$ 且 $b_j = 1$，则 $x = 1$，贡献为 $0$（$x = 0$ 时贡献为 $-1$）。

可知 $b_i$ 和 $b_j$ 的贡献为 $(b_i | b_j) - b_j$。

对新加入的 $e_i$，如果它作为 $b_j$，则需要求 $e_k\mathop | e_i\ (1 \leq k < i)$ 的最大值。如果它作为 $b_i$，因为 $(b_i \mathop |b_j) - b_j$ 的两项均和 $b_j$ 有关，不好算，考虑根据 $a + b = (a \mathop| b) + (a \mathop \& b)$ 写成 $b_i - (b_i \mathop \& b_j)$，则需要求 $e_k \mathop \& e_i\ (1\leq k < i)$ 的最小值。两个问题是对称的，因为后者相当于求 $(2 ^ n - 1 - e_k)\, |\, (2 ^ n - 1 - e_i)$ 的最大值。

直接按位贪心，每次查询是否存在一个数以 $x$ 为子集，可以做到均摊 $\mathcal{O}(n2 ^ n)$：设 $f_x$ 表示是否存在以 $x$ 为子集的数。加入一个数的所有子集时，如果它已经被加入，即 $f_x = 1$，则不需要再加入。否则令 $f_x = 1$，并加入所有这个数去掉二进制下某个 $1$ 的数的子集。

时间复杂度 $\mathcal{O}((2 ^ n + q) n)$。[代码](https://codeforces.com/contest/1930/submission/246933000)。

---

## 作者：james1BadCreeper (赞：2)

考虑只有两个数字 $a,b$ 的时候怎么做。假定它们的值域是 $[0,2)$，那么只有在 $a=1,b=0$ 时才有贡献。因此答案应该是 $\max_{i\in A}\max_{j\in A} \{i\operatorname{and}\neg j\}$。

在加入一个数时枚举答案，答案应该是这个数的子集，使用记忆化搜索即可。时间复杂度 $O(n\log n+q)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64; 
const int N = (1 << 24) + 5; 
const int U = (1 << 23) - 1; 

int n, q; 
int f[N][2]; 

void solve(void) {
    cin >> n >> q; 
    int li = 1 << __lg(n - 1) + 1; 
    for (int i = 1; i <= li; ++i) f[i][0] = f[i][1] = 0; 

    for (int lst = 0; q--; ) {
        int x; cin >> x; x = (x + lst) % n; 
        for (int tp = 0; tp < 2; ++tp) {
            queue<int> q; 
            q.push(tp ? x : li - 1 - x); 
            while (!q.empty()) {
                int x = q.front(); q.pop(); 
                if (f[x][tp]) continue; f[x][tp] = 1;
                if (f[x][!tp]) lst = max(lst, x); 
                for (int i = 1; i <= li; i <<= 1) if (x & i) q.push(x ^ i); 
            }
        }       
        cout << lst << " "; 
    }
    cout << "\n"; 
}

int main(void) {
    ios::sync_with_stdio(0); cin.tie(0); 
    int T = 1; cin >> T; 
    while (T--) solve();
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF1930F)

**题目大意**

> 给定值域 $[0,n)$ 的集合 $S$，初始为空，$q$ 次插入，强制在线地询问：
> $$
> \max_x\{\max_{i\in S}(i\operatorname{OR}x)-\min_{j\in S}(j\operatorname{OR}x)\}
> $$
> 数据范围：$n\le 2^{22},q\le 10^6$。

**思路分析**

考虑枚举 $i,j$，那么上式一定在 $x=j$ 时取到最大值，再假如任何的二进制位都不可能只增加 $i\operatorname{OR}x$ 的值。

因此我们要求的就是 $\max i\setminus j$，其中 $i\setminus j$ 表示集合减，即 $i-i\operatorname{OR}j$。

每次加入 $x$ 时，求出 $\max i\setminus x$ 和 $\max x\setminus i$。

举个例子，考虑求 $i\setminus x$ 的最大值，从高到低枚举 $x$ 中为 $0$ 的每一位 $k$，如果存在某个数包含第 $k$ 位，那么答案这一位可以为 $k$。

不断进行，设我们当前维护到的最大值是 $w$，我们就要判断是否有一个数的子集为 $w+2^k$。

由于每个数只要被标记一次即可，因此考虑记搜，每次删除 $x$ 的一个位 $d$，如果删除后的数已经被标记过，那么就不用标记了。

因此每个集合至多标记一次。

同理，对于 $x\setminus i$，我们只要维护是否有一个数的超集为 $\overline{w+2^k}$，这也是简单的。

时间复杂度 $\mathcal O((n+q)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,U,d;
bool f[1<<22],g[1<<22];
void F(int x) {
	if(f[x]) return ;
	f[x]=1;
	for(int i=0;i<d;++i) if(x>>i&1) F(x^(1<<i));
}
void G(int x) {
	if(g[x]) return ;
	g[x]=1;
	for(int i=0;i<d;++i) if(!(x>>i&1)) G(x|(1<<i));
}
void solve() {
	scanf("%d%d",&n,&q);
	for(U=1,d=0;U<n;U<<=1,++d);
	memset(f,0,U),memset(g,0,U);
	for(int x=0,lst=0;q--;) {
		scanf("%d",&x),x=(x+lst)%n;
		int s=0,t=0;
		for(int k=d-1;~k;--k) {
			if(x>>k&1) {
				if(g[(U-1)^(s|(1<<k))]) s|=1<<k;
			} else {
				if(f[t|(1<<k)]) t|=1<<k;
			}
		}
		F(x),G(x),lst=max({lst,s,t});
		printf("%d ",lst);
	}
	puts("");
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

首先观察发现原问题等价于 $\max(a\operatorname{and}-b)$，其中 $-b$ 表示 $b$ 取反后的值。

考虑上 trie 维护。

有一个小问题是，查询 $x$ 的时候遇到 $x$ 的第 $i$ 位为 $0$ 时应当往哪个方向走。考虑插入 $x$ 的时候将所有 $y\subseteq x$（二进位上属于）的 $y$ 都加入 trie 树，记忆化一下即可保证时间复杂度没有问题。

总复杂度 $O(n+q\log n)$。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
int ulog[5000005],N;
struct trie{
	int trie[9000005][2],cnt;
	bool vis[5000005];
	void clear(){
		for(int i=0;i<=cnt;i++) trie[i][0]=trie[i][1]=0;
		for(int i=0;i<(1<<N);i++) vis[i]=0;
		cnt=0;
	}
	void add(int now,int x,int v,int i){
		if(i==-1){
			vis[v]=1;
			return ;
		}
		if(!((x>>i)&1)){
			if(!vis[x|v]){
				if(!trie[now][0]) trie[now][0]=++cnt;
				add(trie[now][0],x,v,i-1);
			}
			return ;
		}
		if(!vis[x|v]){
			if(!trie[now][1]) trie[now][1]=++cnt;
			add(trie[now][1],x^(1<<i),v^(1<<i),i-1);
		}
		if(!vis[(x^(1<<i))|v]){
			if(!trie[now][0]) trie[now][0]=++cnt;
			add(trie[now][0],x^(1<<i),v,i-1);
		}
	}
	int qry(int x){
		int ans=0,now=0;
		for(int i=N-1;i>=0;i--){
			if((x>>i)&1){
				if(trie[now][1]) ans+=(1<<i),now=trie[now][1];
				else now=trie[now][0];
			}
			else now=trie[now][0];
		}
		return ans;
	} 
}tree1,tree2;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	for(int i=1;i<4194304;i++) ulog[i]=ulog[i/2]+1;
	int t; cin>>t;
	while(t--){
		int n,q; cin>>n>>q;
		N=ulog[n-1];
		tree1.clear(),tree2.clear();
		int lst=0,maxv=0;
		while(q--){
			int e; cin>>e; e=(e+lst)%n;
			maxv=max(maxv,tree2.qry(e));
			maxv=max(maxv,tree1.qry(((1<<N)-1)^e));
			tree1.add(0,e,0,N-1);
			tree2.add(0,((1<<N)-1)^e,0,N-1);
			lst=maxv;
			cout<<maxv<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：是青白呀 (赞：1)

## 简要题意

$q$ 次询问，每次询问给序列 $a$ 中有后效性地插入一个大于等于 $0$、小于 $n$ 的数 $v$，并求 $\max_{i=1}^m(a_i\lor x)-\min_{i=1}^m(a_i\lor x)$ 的最大值，其中 $x$ 是任意非负整数，$m$ 是询问时序列 $a$ 的长度。

## 题解

首先观察到一个结论：$x$ 一定等于某个 $a_i$。

接下来证明这个结论。设 $a$ 序列中，取到最大时对应的下标为 $i$，取到最小时对应的下标为 $j$，考虑 $x$ 的取值。有下面两个事实：

1. 一定不会存在 $a_j$ 中为 $1$ 的某一位在 $x$ 中为 $0$。因为此时若将 $x$ 的这一位设成 $1$，则 $a_j\lor x$ 的对应位仍然为 $1$，但 $a_i\lor x$ 的对应位可能会保持为 $1$，也可能会从 $0$ 变成 $1$。这个操作可能使得整个式子的值增大，且一定不会使其减小，是更优的。

2. 一定不会存在 $a_j$ 中为 $0$ 的某一位在 $x$ 中为 $1$。因为此时若将 $x$ 的这一位设成 $0$，则 $a_j\lor x$ 的对应位一定会从 $1$ 变成 $0$，但 $a_i\lor x$ 的对应位可能从 $1$ 变成 $0$，也可能保持为 $0$。这个操作同样可能使得整个式子的值增大，且一定不会使其减小，也是更优的。

因此，最优情况下 $x=a_j$。故 $x$ 一定等于某个 $a_i$。

将 $x=a_j$ 代入原式，则原式可化简为 $\max_{i=1}^m(a_i\lor a_j)-a_j$。设 $a_i$ 各位取反之后得到的数为 $\neg a_i$，则上式等于 $\max_{i=1}^m a_i\land\neg a_j$。

考虑往序列 $a$ 中加数的过程，新加入的数 $a_m$ 对答案产生的影响仅有可能是 $a_m\land\neg a_i$ 或 $\neg a_m\land a_i$。于是我们需要维护一个集合 $S$，支持插入新值、对给定的数 $x$ 求集合中元素 $S_i\land x$ 的最大值。

这些操作可以使用 [RainFestival树](https://www.luogu.com.cn/blog/MiloRavenclaw/hei-ya-shu) 维护。

具体地，我们考虑从高位往低位贪心的过程，若 $x$ 的这一位为 $1$，则我们要尽可能选择 $S$ 中这一位为 $1$ 的元素，才能使得答案尽可能大；若 $x$ 的这一位为 $0$，则该位不受限制。为了解决“不受限制”这部分的要求，我们可以让每个 $a_i$ 都去覆盖其子集，维护所有要求为 $1$ 的位组成的数。若这个数被覆盖，则这些限制目前可以被满足，否则不能被满足。询问时贪心地从高位往低位扫一遍询问的 $x$ 即可。插入一个数时，枚举每一个为 $1$ 的位删除，若得到的新树未被覆盖，则递归地插入这个新数；否则直接返回，因为它的所有子集一定已经被覆盖。

每个数最多会被覆盖一次，每次会枚举每一位删除。所以插入和查询的复杂度均为 $O(\log V)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define lowbit(x) x&(-x)
#define mp make_pair
#define fir first
#define sec second
#define pii pair<int,int>
using namespace std;
typedef long long ll;
const int N=2e5+5,M=1e6+5,S=(1<<23)+5,mo=998244353,inf=1e9+7,bs=19491001;
const double eps=1e-8;
inline void read(int &p){
	int x=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int T;
int n,q,upp; 
bool vis[S][2];
void insert(int x,int op){
	if(vis[x][op])return;
	vis[x][op]=1;
	rep(i,0,upp-1){
		if(!((x>>i)&1))continue;
		insert(x^(1<<i),op);
	}
}
int query(int x,int op){
	int res=0;
	repp(i,upp-1,0){
		if(!((x>>i)&1))continue;
		if(vis[res|(1<<i)][op])res=res|(1<<i);
	}
	return res;
}
void solve(){
	read(n),read(q),upp=floor(log2(n))+1;
	int tot=(1<<upp)-1;
	rep(i,0,tot)
	    vis[i][0]=vis[i][1]=0;
	int ans=0,lst=0;
	while(q--){
		int x;
		read(x),x=(x+lst)%n;
		ans=max(ans,query(x,1)),insert(x,0);
		x=tot^x;
		ans=max(ans,query(x,0)),insert(x,1);
		printf("%d ",ans);
		lst=ans;
	}
	puts("");
}
int main(){
	read(T);
	while(T--)
	    solve();
	return 0;
}
```

---

## 作者：K_srh (赞：0)

题目要求我们确定一个 $x$，然后再在集合中选两个值 $a_i$，$a_j$，使 $\max(a_i|x)-\min(a_j|x)$ 这个值越大越好，其实就是找一个或起来最大的 $a_i$ 和或起来最小的 $a_j$ 不妨先确定 $a_i$ 与 $a_j$，若 $a_i$ 某一位是 $1$，$a_j$ 这一位是 $0$，$x$ 这一位自然是取 $0$ 更合适，其他情况也可类似这样讨论。
在 $x$ 任取的情况下最终得到的答案最大是 $a_i-a_i\&a_j$，这每次插入新数只有三种情况，$a_i$ 是新数，$a_j$ 是新数，或者两者都不是新数，第三种情况已经算过了，就是上次的答案。
对于其他情况我们也分别计算，这里举个例子。
对于第一种情况也就是 $\max(x-x\operatorname{and}a_j)$，也就是求 $\min(x\operatorname{and}a_j)$，这个问题我们直接贪心，按位权从大到小枚举，若是 $x$ 这一位是 $1$，$a_j$ 这一位我们就希望他是 $0$，其他位我们也是尽量希望为 $0$，这就是为什么要统计一个超集，记一个 $f_s$ 表示是否有 $s$ 的子集存在，这里搜索过程中使用记忆化便可保证均摊的复杂度是 $O(n\log n)$，若是 $\mid$ 操作的时候我们便会希望其他也都是 $1$，这就是为什么统计子集，其他题解没有提这一点。
下面上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=8388608;
bool mor[N],les[N];
int n,q;
void dfs1(int x)
{
	mor[x]=1;
	for(int i=0;i<=n;i++)
	{
		if(!(x&(1<<i))&&!(mor[x^(1<<i)]))
		{
			dfs1(x^(1<<i));
		}
	}
}
void dfs2(int x)
{
	les[x]=1;
	for(int i=0;i<=n;i++)
	{
		if(x&(1<<i)&&!(les[x^(1<<i)]))
		{
			dfs2(x^(1<<i));
		}
	}
}
void solve()
{
	scanf("%d%d",&n,&q);
	int tn=n;
	n=__lg(n);
	int U=(1<<(n+1))-1;
	for(int i=0;i<=U;i++)les[i]=mor[i]=0;
	int ans=0;
	for(int i=1;i<=q;i++)
	{
		int v;
		scanf("%d",&v);
		v=(v+ans)%tn;
		int now=U;
		for(int i=n;i>=0;i--)
		{
			if(v&(1<<i)&&mor[now^(1<<i)])now^=(1<<i);
		}
		ans=max(ans,v-(now&v));
		now=0;
		for(int i=n;i>=0;i--)
		{
			if(!(v&(1<<i))&&les[now^(1<<i)])now^=(1<<i);
		}
		ans=max(ans,(now|v)-v);
		dfs1(v);dfs2(v);
		printf("%d ",ans);
	}
	printf("\n");
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)solve();
	return 0; 
 } 
```

---

## 作者：Purslane (赞：0)

# Solution

送分 `*2700`。

考虑 $\max_{i=1}^{|a|} (a_i \text{ or } x) - \min_{i=1}^{|a|} (a_i \text{ or }x) = \max_{1 \le i,j \le |a|} [(a_i \text{ or } x)-(a_j \text { or } x)]$，所以我们可以把 $i$ 和 $j$ 提到外面去，思考如何计算
$$
\max_x [(a_i \text{ or }x)-(a_j \text{ or }x)]
$$
这个是容易的，如果对应为 $a_i$ 比 $a_j$ 大，$x$ 这一位赋为 $0$（且答案中这一位为 $1$），否则赋为 $1$（且答案中这一位为 $0$）。

因此贪心的决策每一位，如果答案这一位能是 $1$，那将所有对应位为 $0$ 的从 $i$ 决策集合中删掉，对应位为 $1$ 的从 $j$ 的决策集合中删掉。

问题就变为：动态加数，询问集合 $S$ 中是否有 $x$ 满足：$x \subseteq S$，以及是否有 $x$ 满足 $x' \subseteq S$，其中 $S'$ 是 $S$ 的补集。

这是经典问题，直接爆搜 + 剪枝，复杂度就是 $O(k^22^k)$（每个位置只会被加一次，访问一个位置会访问 $O(k)$ 个子集），但是有剪枝跑得飞快（也许可以证明复杂度是 $O(k2^k)$ 的，但是我觉得不对。），其中 $k= \lceil \log_2 n \rceil$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e6+10;
int T,n,q,on,lstans,cov1[MAXN],cov2[MAXN];
void cov(int a,int *cova,int s) {
	if(cova[a]) return ;
	cova[a]=1;
	while(s<=a) {
		if(a&s) cov(a-s,cova,s<<1);
		s<<=1;
	}
	return ;
}
int calc(void) {
	int ans=0,o=(on+1)>>1;
	while(o) {
		if(cov1[ans|o]&&cov2[ans|o]) ans|=o;
		o>>=1;
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>q;
		ffor(i,1,22) if((1<<i)>=n) {on=(1<<i)-1;break ;}
		ffor(i,0,on) cov1[i]=cov2[i]=0;
		lstans=0;
		ffor(i,1,q) {
			int a;
			cin>>a,a=(a+lstans)%n;
			cov(a,cov1,1),cov(on^a,cov2,1);
			cout<<(lstans=calc())<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Albert_van (赞：0)

[题](https://www.luogu.com.cn/problem/CF1930F)。考虑对于确定的两个数 $a,b$ 如何选择一个数 $x$ 使得 $a|x-b|x$ 最大。按位考虑。若 $a,b$ 在这一位相同则为 $0$。若 $a=1,b=0$，令 $x=0$ 可以使答案在这一位为 $1$。若 $a=0,b=1$，令 $x=1$ 可以保证答案在这一位不造成负贡献。于是答案为所有 $a=1,b=0$ 的二进制位，即 $a\&\neg b$。

问题：每次向 $a$ 中加入一个数，求 $\max(a_i\&\neg a_j)$。考虑引入 [RainFestivalTree](https://www.luogu.com.cn/blog/MiloRavenclaw/hei-ya-shu)，支持在 $\mathcal O((q+V)\log V)$ 内维护集合 $S$，每次加入一个数 $x$ 或者查询 $\max_{a\in S}x\&a$。

具体地，维护 $e_v$ 表示是否有 $a\in S$ 满足 $v$ 的二进制表示为 $a$ 的子集。每次插入时进行搜索，枚举子集时只从当前数字中去除一位，可以以记忆化在总计 $\mathcal O(V\log V)$ 内完成。

查询时，按位贪心。从高到低枚举每一位，维护 $s$ 表示已经保证了 $s$ 中每一位都在结果上为 $1$。第 $i$ 位时，若 $x$ 在第 $i$ 位上为 $1$ 且 $e_{s|2^i}=1$，则令 $s\gets s|2^i$。

对于本题，维护两个集合 $S,T$，分别存储 $a_i$ 和 $\neg a_i$。加入 $v$ 时，分别在 $T$ 中查询 $v$、在 $S$ 中查询 $\neg v$，将答案与上次取 $\max$ 即可。

边界问题要想得仔细一些。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

namespace fIO{
}using fIO::re;using fIO::wr;

int I;

struct FakeKick{
	bool e[4200000];
	void ins(int x){
		if(e[x]) return ;
		e[x]=1;for(int i=0;i<I;++i) if(x&(1<<i)) ins(x^(1<<i));
	}
	int qry(int x){
		int s=0;for(int i=I-1;~i;--i) if(x&(1<<i)&&e[s|(1<<i)]) s|=(1<<i);
		return s&x;
	}
	void clr(int n){memset(e,0,n+1);}
}O,R;

int main()
{
	int T;re(T);while(T--){
		int n,q;re(n);re(q);I=__lg(n)+(__builtin_popcount(n)>1);int U=(1<<I)-1;
		int l=0,x;while(q--){
			re(x);(x+=l)%=n;
			wr(l=max(l,max(R.qry(x),O.qry(U^x))));putchar(' ');
			O.ins(x);R.ins(U^x);
		}puts("");
		O.clr(U);R.clr(U);
	}
}
```

---

