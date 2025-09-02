# Graph Coloring (easy version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3```

### 输出

```
6```

## 样例 #2

### 输入

```
4```

### 输出

```
50```

## 样例 #3

### 输入

```
100```

### 输出

```
878752271```

## 样例 #4

### 输入

```
1337```

### 输出

```
520628749```

# 题解

## 作者：Purslane (赞：6)

## Solution

先摆一个引理：

> 一个图，如果不连通，那么其补图必然联通。

证明比较显然。对于一个点 $u$，和它不在一个联通块内的任意一个节点在补图中都是联通的。而对于和它在一个联通块内的节点，必然存在一个在另一个连通块里面的中介把他们联通起来了。所以任意两个点都是联通的，即得证。

所以，由蓝边构成的图和由红边构成的图互为补图，其中必有一个联通。那么一个集合是某种颜色联通肯定能保证。

再观察到，当 $S=V$ 时，不能两种颜色都联通，所以原图之中必有且仅有一种颜色不连通，不妨设是蓝色。

那么就是求 $dp_n$ 为大小为 $n$ 的不是蓝色联通的符合要求的图。

那么考虑 $1$ 所在的蓝色边构成的连通块，记大小为 $x$。那么单独抽出这 $x$ 个点，方案数为 $dp_x$（因为我们假设的是蓝色不连通，这个子图中蓝色必然联通，那么让红色不连通，二者等价）。

剩下的 $n-x$ 个点呢？他们无所谓，要么是蓝色不连通要么是红色不连通，答案是 $2dp_{n-x}$。有一个例外是 $x=n-1$ 时，这时候剩下的一个点只有一种选法，所以不能乘以二。

这 $x$ 点和 $n-x$ 点之间由定义都是红边。

所以转移为：

$$dp_n = \sum_{x=1}^{n-1} C_{n-1}^{x-1} \times dp_{x} \times dp_{n-x} \times (2 - [n-x=1])$$

[Submission #190643824](https://codeforces.com/problemset/submission/1792/190643824)

lzm 场切这道题，进步速度堪比 jly，看来明年 MAS rank 1 肯定是他了 /dk

---

## 作者：InoueTakina (赞：2)

注意到由红色边生成的子图和蓝色边生成的子图互为补图，因此不存在点集 $S$ 满足其既不是蓝色也不是红色，考察 $\lvert S\rvert=n$ 的情况，不难发现，红色或蓝色必然有一个是不连通的，注意到两种情况完全等价，因此仅仅考察红色不连通的情况。

记 $f_i$ 表示 $n=i$ 时满足条件的蓝色不连通图方案，如何转移能不重不漏的统计方案？发现我们每次肯定是通过将两个图拼合在一起的方式转移，大概会形如 $f_i\gets f_{j}\oplus f_{i-j}$，其中 $\oplus$ 无实际含义。可以发现如果我们在转移的时候钦定了包含 $1$ 的蓝色连通块大小，那么不会有重复转移。不难有转移：
$$
f_{i}=\sum\limits_{j=1}^n f_j\times f_{i-j}\times {n-1\choose k-1} \times (2-[i=j+1])
$$
解释转移中的几个点：

- 因为红色不连通和蓝色不连通的方案数相等，因此包含 $1$ 的大小为 $j$ 的蓝色连通块满足红色的不连通的方案数是 $f_j$。
- 剩下的部分是蓝色不连通还是红色不连通是无所谓，方案数为 $2\times f_{i-j}$。注意到 $i-j=1$ 时要特判。
- 为了满足钦定的内容，包含 $1$ 的大小为 $j$ 的蓝色连通块和剩余部分的边一定要是红色，否则我们的钦定是无效的。



---

## 作者：_ANIG_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1792F1)

首先有个结论：一个不连通的图的补图一定连通。

比较显然：一个点在补图中与任意一个不连通的点有边。

于是可以先走到其它连通块，然后就可以到达自己原本的连通块的其它点。

设合法图为满足题目给定条件的图。

设 $f_n$ 为 $n$ 个点的连通合法图的数量，$g_n$ 为 $n$ 个点的不连通合法图数量，则有：$f_n=g_n$。

对于任意一个不连通合法图，直接取其补图可以得到连通合法图，这是一个双射。

所以最终答案为 $2f_n-2$。

考虑如何转移。

枚举一号点所在连通块大小，可得：

$$f_n=2f_{n-1}+\sum\limits_{j<i}2f_jf_{i-j}\binom{i-1}{j-1}$$

于是即可 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mods=998244353,N=5e4+5;
int pows(int a,int b){
	if(b==0)return 1;
	int res=pows(a,b>>1);
	res=res*res%mods;
	if(b&1)res=res*a%mods;
	return res;
}
int n,f[N],jc[N],ny[N],f1[N],f2[N];
int C(int a,int b){
	return jc[a]*ny[b]%mods*ny[a-b]%mods;
}
signed main(){
	cin>>n;
	jc[0]=ny[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%mods,ny[i]=pows(jc[i],mods-2);
	f[1]=pows(2,mods-2);
	f2[1]=f[1]*ny[1];
	for(int i=2;i<=n;i++){
		f[i]=f[i-1]*ny[i-1]%mods;
		__int128 res=0;
		for(int j=2;j<i;j++){
			res+=f1[j]*f2[i-j];
		}
		f[i]=res%mods;
		f[i]=f[i]*2%mods*jc[i-1]%mods;
		f1[i]=f[i]*ny[i-1]%mods;
		f2[i]=f[i]*ny[i]%mods;
	}
	cout<<(2*f[n]-2)%mods;
}
```

---

## 作者：寄风 (赞：0)

## 题解
### F1做法
一个很显然的结论一个图的补图和这个图不可能都不连通。

然后又因为由蓝边构成的图和由红边构成的图互为补图，所以不可能都不连通。

然后对于任意点集 $S$，由蓝边构成的图和由红边构成的图不能都连通，然后又因为由蓝边构成的图和由红边构成的图是完全等价的，所以不妨设蓝边构成的图不连通。

设 $dp_i$ 表示大小为 $i$ 的满足约束的图的个数。

转移的话，考虑 $1$ 所在蓝色边构成的连通块，设大小为 $s$，那么这个块就是蓝色连接的，但由于蓝色连接和红色连接完全的等价，所以方案数还是 $dp_s$。

剩下的点呢？它们是红色还是蓝色没有影响，都可以选。

但是注意当只剩余一个点的时候只有一种选法。

答案最后要减 $2$，因为至少要染一条红边和一条蓝边。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n , dp[1000005] , C[1000005];
inline void add(int &x,int y){
    x+=y-mod;
    x+=(x>>31)&mod;
} 
int main(){
	cin>>n; 
	dp[1]=C[0]=1;
	for(int i=2;i<=n;i++) {
		for(int j=i-1;j;j--) add(C[j],C[j-1]);		
		for(int j=1;j<i;j++) add(dp[i],1LL*C[j-1]*dp[j]%mod*dp[i-j]%mod*(2-(j==i-1?1:0))%mod);
	}
    add(dp[n],dp[n]-2);
	cout<<dp[n]<<endl;
	return 0;
}
```
### F2做法
你发现数据范围从 $5\times 10^3$ 扩大到了 $5\times 10^4$，$n^2$ 的运算量达到了 $2.5\times 10^9$，但是时限有 $5.5$ s，按理说能过。

自信的交了一法 F1 的代码上去，T 了。

于是开始卡常。

有位卡常带师说过，
>数组的 Cache miss 是致命的。

我们看到我们 F1 的代码，$dp$ 数组的内存访问极其不连续，`dp[j]` 和 `dp[i-j]` 造成了大量的 Cache miss，所以我们再开一个 $dp2$，里面存的东西和 $dp$ 一模一样，但我们更新的时候只访问 `dp[j]`，访问 `dp[i-j]` 改成访问 `dp2[i-j]`，这样就减少了 Cache miss。

然后这个问号表达式很烦，注意到只有 $j=i-1$ 的时候才不会乘 $2$，这个时候访问到的 `dp2[i-j]` 就是 `dp2[1]`，所以我们把 `dp2[1]` 设成和 `dp1[1]` 一样，其余的设成 $dp1$ 的两倍，这样就避免了问号表达式的计算，减小了常数。

然后交一发就过了。

多说一句，较为正常的正解大概 3s 就能跑完，为啥要开 5.5s 呢，这不是放暴力过吗？

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n , dp1[1000005] , dp2[1000005] , C[1000005];
//use one dp can make Cache miss and TLE
inline void add(int &x,int y){
    x+=y-mod;
    x+=(x>>31)&mod;
} 
int main(){
	cin>>n; 
	dp1[1]=dp2[1]=C[0]=1;
	for(int i=2;i<=n;i++) {
		for(int j=i-1;j;j--) add(C[j],C[j-1]);		
		for(int j=1,k=i-1;j<i;j++,k--) add(dp1[i],(1LL*C[j-1]*dp1[j]%mod*dp2[k]%mod)%mod);
        dp2[i]=dp1[i]<<1;
        if(dp2[i]>mod)dp2[i]-=mod;
	}
	cout<<(dp2[n]-2+mod)%mod;
	return 0;
}
```

---

## 作者：zzzYheng (赞：0)

#### 题意：

现在有一个 $n$ 阶完全图，你要给它的每条边染上红色或蓝色。

满足：

- 至少有一条红边。
- 至少有一条蓝边。
- 对于任何一个大小不小与 $2$ 的顶点集 $S$（$|S| \ge 2$），$S$ 的红边导出子图或蓝边导出子图连通，但不能都连通。

#### 思路：

显然红蓝是互补的，所以我们可以把问题转化为：找到一个 $n$ 个点的图 $G$，其任何点集 $S$（$|S|\ge 2$）都满足 $S$ 的导出子图连通，或者导出子图的补图连通，但不能都连通。（题目要求红蓝边都有，所以最终答案要减 $2$）

观察：如果一个图不连通，那么其补图必然连通。

证明：图不连通说明存在一组割 $A,B$（$A$ 和 $B$ 均为点集），$A$ 和 $B$ 间没有任何边，那么补图中 $\forall i\in A,j \in B$ 就都存在边 $(i,j)$，易得补图连通。

所以我们只需保证 $S$ 的导出子图和导出子图的补图不都连通即可。

首先考虑第一个限制，$G$ 本身不能和其导出子图 $G'$ 都连通。

$G$ 连通 $G'$ 不连通和 $G$ 不连通 $G'$ 连通两种情况对称，因此假设 $G$ 连通。此时所有 $G$ 中不连通的 $S$ 都不用考虑，只需考虑 $G$ 中连通的 $S$ 的合法性。

$G'$ 不连通，说明存在一组割 $A,B$，在 $G$ 中任何 $i \in A,j \in B$ 都存在。

而一但存在这样的割，任何在 $A$ 和 $B$ 中都有点的 $S$ 也都必然满足在 $G'$ 中不连通，取割 $A\cap S,B\cap S$ 即可。

因此只有满足 $S\subseteq A$ 或 $S\subseteq B$ 的 $S$ 需要考虑，这相当于变成了对 $A$ 和 $B$ 两部分的独立判断。

考虑对着这个判定方式进行 $\text{dp}$，不过会算重，因为一个图可能存在多种分成 $A$ 和 $B$ 的方案。

考虑经典套路，对等价类计数可以转化为对满足每个等价类中恰好有一个的特殊元素计数。

因此考虑给每个图找到一种唯一的特殊割。

首先考虑如果存在多种割会发生什么。假设将 $A$ 分成 $A_1,A_2$，将 $B$ 分成 $B_1,B_2$，$(A_1\cup B_1,A_2\cup B_2)$ 是一个合法的割。

$(A_1,B_2)$，$(B_1,A_2)$ 这两组点集中间边必然连满，但是 $(A_1,A_2)$ 和 $(B_1,B_2)$ 中间边不一定连满。

因为 $A$ 递归下去判断是合法的，所以 $A$ 存在 $(A_1,A_2)$ 这组割就等价于 $A$ 连通且大小不为 $1$，$B$ 也同理。

因此，只要 $A$ 或 $B$ 连通且大小不为 $1$，就可以将 $A$ 或 $B$ 的割中的一部分划分到另一个集合中，得到一个新的割。

假设 $A$ 中包含节点 $1$，不断将 $A$ 划分开来将一部分放入 $B$ 中，最终使得 $A$ 不连通或大小为 $1$。这样的 $(A,B)$ 划分一定是唯一的，我们将其当作特殊割即可。

对这 $\text{dp}$ 即可，令 $f_{i}$ 表示 $i$ 个点的连通图满足条件的方案数，$g_i$ 表示 $i$ 个点的大小为 $1$ 或不连通的合法图的方案数，$h_i$ 表示 $i$ 个点任意图的方案数。

显然有 $f_1=g_1=h_1=1$。

转移：

- $f_i=\sum_{j=1}^{i-1} {i-1\choose j-1} g_j\cdot h_{i-j}$
- $g_i=\sum_{j=1}^{i-1}{i-1\choose j-1} f_i\cdot h_{i-j}$
- $h_i=f_i+g_i$。

这样就可以做到 $\Theta(n^2)$。转移明显是卷积形式，利用多项式科技可以做到更优的复杂度。

---

