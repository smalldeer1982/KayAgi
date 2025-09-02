# [ABC213F] Common Prefixes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc213/tasks/abc213_f

$ 2 $ つの文字列 $ X,Y $ に対して、その**類似度** $ f(X,Y) $ を、$ X $ と $ Y $ を先頭から見て一致している文字数とします。  
 例えば `abc` と `axbc` の類似度は $ 1 $ 、`aaa` と `aaaa` の類似度は $ 3 $ です。

長さ $ N $ の文字列 $ S $ が与えられます。$ S $ の $ i $ 文字目以降からなる文字列を $ S_i $ とします。$ k=1,\ldots,N $ のそれぞれについて、$ f(S_k,S_1)+f(S_k,S_2)+\ldots+f(S_k,S_N) $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^6 $
- $ S $ は英小文字のみからなる長さ $ N $ の文字列

### Sample Explanation 1

$ S_1,S_2,S_3 $ はそれぞれ `abb`, `bb`, `b` です。 - $ k=1 $ のとき $ f(S_1,S_1)+f(S_1,S_2)+f(S_1,S_3)=3+0+0=3 $ - $ k=2 $ のとき $ f(S_2,S_1)+f(S_2,S_2)+f(S_2,S_3)=0+2+1=3 $ - $ k=3 $ のとき $ f(S_3,S_1)+f(S_3,S_2)+f(S_3,S_3)=0+1+1=2 $

## 样例 #1

### 输入

```
3
abb```

### 输出

```
3
3
2```

## 样例 #2

### 输入

```
11
mississippi```

### 输出

```
11
16
14
12
13
11
9
7
4
3
4```

# 题解

## 作者：loser_seele (赞：2)

部分内容参考自官方题解。

前置知识：SA。

首先对原数组跑一遍 SA，计算出 $ sa $ 数组，$ h $ 数组和 $ rnk $ 数组。

众所周知，LCP 有一个重要性质：$ \operatorname{LCP}(suf_i,suf_j)(rnk_i<rnk_j)=\min\limits_{k=i}^j \{h_{rnk_k} \} $。

于是按 $ rnk $ 排序后，问题转化为了：

给定数组 $ a $，对于每个 $ i $，求出所有以 $ i $ 为一个端点的区间内最小值之和。

这是一个经典问题，开栈即可，线性时间复杂度解决问题。

具体流程如下：

首先设 $ B_k=\sum_{i=1}^{k-1} g(i,k) $，其中 $ g(i,k) $ 表示区间 $ [i,k] $ 内的最小值，然后分析 $ B_k $ 与 $ B_{k+1} $ 之间的关系：

$ B_{k+1}=A_k+\sum_{i=1}^{k-1} \min (A_k,g(i,k)) $，这步是显然的，对每个元素分类讨论不难得到。

于是 $ B_k $ 不难计算，考虑暴力：

设 $ X $ 为初始集合，对于每个 $ k $，首先将 $ X $ 里所有集合与 $ A_{k-1} $ 取 $ \min $，然后将 $ A_{k-1} $ 塞入集合，之后求出集合内元素之和作为答案。朴素实现是 $ \mathcal{O}(n^2) $，考虑优化。

但实际上，注意到每次第一步操作都会减少不同的数字个数，所以不难发现操作次数的上限是 $ \mathcal{O}(n) $ 级别的，于是可以用平衡树实现。现在我们企图优化这个过程。

发现由于在第二步操作中加入的数显然不小于 $ X $ 中的最大值，所以可以直接开栈来维护集合 $ X $，于是做到了线性复杂度。

时间复杂度为求后缀数组的时间复杂度。

代码实现上使用了 Atcoder 自带的字符串库里的后缀数组函数，当然也可以手写。

代码：

```cpp
#import <atcoder/string.hpp>
#import <bits/stdc++.h>
using namespace std;
int main() 
{
    ios::sync_with_stdio(0);
    int n;
    string s;
    cin >> n >> s;
    auto sa = atcoder::suffix_array(s);
    auto lcp = atcoder::lcp_array(s, sa);
    lcp.insert(lcp.begin(), 0);
    vector<long long> pre(n + 5), suf(n + 5), stk(n << 1);
    int top = 0;
    stk[top = 0] = -1;
    for (int i = 0; i < n; ++i) 
    {
        if (i > 0)
            pre[i] = pre[i - 1];
        while (top && lcp[stk[top]] > lcp[i]) 
        {
            pre[i] -= (stk[top] - stk[top - 1]) * lcp[stk[top]];
            --top;
        }
        pre[i] += (i - stk[top]) * lcp[i];
        stk[++top] = i;
    }
    top=0;
    stk[top] = n;
    for (int i = n - 1; i >= 0; --i) 
    {
        if (i < n - 1)
            suf[i] = suf[i + 1];
        while (top && lcp[stk[top]] > lcp[i]) 
        {
            suf[i] -= (stk[top - 1] - stk[top]) * lcp[stk[top]];
            --top;
        }
        suf[i] += (stk[top] - i) * lcp[i];
        stk[++top] = i;
    }
    vector<int> rk(n);
    for (int i = 0; i < n; ++i)
        rk[sa[i]] = i;
    for (int i = 0; i < n; ++i) 
        cout << pre[rk[i]] + suf[rk[i] + 1] + n - i << '\n';
}
```


---

## 作者：Reunite (赞：1)

来个 SAM 和后缀树的题解。

## 一
---

看到一大车 $\operatorname{lcp}$，考虑把串丢到后缀树上去，可以直接把反串建 SAM，其 parent 树就是原串的后缀树。后缀树的一个很好的性质是，任意两后缀的 $\operatorname{lcp}$ 等于 其 $\operatorname{lca}$ 所对应的 $len$。

然后这个题要求的是每个后缀与所有后缀的 $\operatorname{lcp}$ 之和，联想到 [LNOI2014 LCA](https://www.luogu.com.cn/problem/P4211) 这题的经典拆 $\operatorname{lca}$ 的方法，把直接求 $\operatorname{lca}$ 转化为每个点到根链上所有点 $+1$，查询就是求改点到根链上的点权和。但是这题是静态的，所以直接树上差分就行。还有一个小问题就是，后缀树是经过压缩的，不能直接简单 $+1$，考虑 $+1$ 操作的本质，其实就是一点到其父亲的 $dep$ 之差，所以在后缀树上就是 $len_u-len_{fa_u}$ 了。

---
## 二
---

实现是简单的，把后缀树建出来，一遍 dfs 树上差分，再一遍 dfs 维护到根链的和即可。

时间复杂度 $O(n)$，空间 $O(n|\sum|)$，其中 $|\sum|=26$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

int n,tot=1;
char c[2000005];
int fa[2000005];
int len[2000005];
int pos[2000005];
int cnt[2000005];
ll ans[2000005];
int mp[2000005][26];
vector <int> g[2000005];

inline int ins(int c,int las){
	if(mp[las][c]){
		int p=las,v=mp[p][c];
		if(len[p]+1==len[v]) return v;
		int x=++tot;
		len[x]=len[p]+1;
		for(int i=0;i<26;i++) mp[x][i]=mp[v][i];
		while(mp[p][c]==v) mp[p][c]=x,p=fa[p];
		fa[x]=fa[v],fa[v]=x;
		return x;
	}
	int x=++tot,p=las;
	len[x]=len[p]+1;
	while(p&&!mp[p][c]) mp[p][c]=x,p=fa[p];
	if(!p) fa[x]=1;
	else{
		int v=mp[p][c];
		if(len[p]+1==len[v]) fa[x]=v;
		else{
			int y=++tot;
			len[y]=len[p]+1;
			for(int i=0;i<26;i++) mp[y][i]=mp[v][i];
			while(mp[p][c]==v) mp[p][c]=y,p=fa[p];
			fa[y]=fa[v],fa[x]=fa[v]=y;
		}
	}
	return x;
}

inline void init(int u){
	cnt[u]=(pos[u]>0);
	for(int v:g[u]) init(v),cnt[u]+=cnt[v];
	return ;
}

inline void solve(int u,ll s){
	ans[pos[u]]=s;
	for(int v:g[u])
		solve(v,s+1ll*cnt[v]*(len[v]-len[u]));
	return ;
}

int main(){
	scanf("%d",&n);
	scanf("%s",c+1);
	int las=1;
	for(int i=n;i>=1;i--) pos[las=ins(c[i]-'a',las)]=i;
	for(int i=2;i<=tot;i++) g[fa[i]].emplace_back(i);
	init(1);
	solve(1,0);
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);

	return 0;
}
```

---

