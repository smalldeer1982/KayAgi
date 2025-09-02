# Odd Federalization

## 题目描述

Berland has $ n $ cities, some of which are connected by roads. Each road is bidirectional, connects two distinct cities and for each two cities there's at most one road connecting them.

The president of Berland decided to split country into $ r $ states in such a way that each city will belong to exactly one of these $ r $ states.

After this split each road will connect either cities of the same state or cities of the different states. Let's call roads that connect two cities of the same state "inner" roads.

The president doesn't like odd people, odd cities and odd numbers, so he wants this split to be done in such a way that each city would have even number of "inner" roads connected to it.

Please help president to find smallest possible $ r $ for which such a split exists.

## 样例 #1

### 输入

```
2
 
5 3
1 2
2 5
1 5
 
6 5
1 2
2 3
3 4
4 2
4 1
```

### 输出

```
1
1 1 1 1 1 
2
2 1 1 1 1 1
```

# 题解

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1070L)

## 思路

首先盲猜答案要么是 $1$ 要么是 $2$。

如果答案是 $1$，那么就是每个点的度数都是偶数，这是简单的。

如果答案是 $2$ 呢？考虑列出一个异或方程组，我们对于每个点设 $1$ 表示归到第一个集合，$0$ 表示归到第二个集合。若 $u$ 归到第一个集合，且 $u$ 的度数是奇数，则与 $u$ 相连的点必须有奇数个是 $1$，否则有偶数个是 $1$，发现这个限制等价于 $u$ 和与它相连的点异或起来是 $1$，$u$ 归到第二个集合同理，用高斯消元解出来即可。

接下来我们考虑如何证明答案一定 $\le 2$，~~但是事实上猜出这个结论就行了，不需证明~~。

如果 $r>2$，意味着上面的异或方程组无解。无解则存在某些异或方程能够异或得到 $0=1$。右式为 $1$ 意味着有奇数个入度为奇数的点，而左式为 $0$ 意味着所有点在这些异或方程中都出现了偶数次，而度数为奇数的点会在自己的方程中出现一次，所以在这个导出子图中，度数为奇数的点连接了奇数个点，度数为偶数的点连接了偶数个点，这意味着这个导出子图的度数和为奇数。但对于一个无向图度数无论如何都是偶数，所以不存在无解情况，所以 $r \le 2$。

证明 $\rm from$ [传送门](https://www.cnblogs.com/Itst/p/10423837.html)

一个小细节：高斯消元解异或方程组直接来是 $\mathcal O(n^3)$ 的，但是可以用 $\rm bitset$ 优化成 $\mathcal O(\dfrac{n^3}{w})$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
int const N=2e3+10;
vector<int>a[N];
int du[N],an[N];bitset<N>g[N];
inline void solve(){
	int n,m;cin>>n>>m;
	memset(an,0,sizeof(int)*(n+5));
	memset(du,0,sizeof(int)*(n+5));
	for (int i=1;i<=n;++i) a[i].clear(),a[i].shrink_to_fit();
	for (int i=1;i<=n;++i) g[i].reset();
	while (m--){
		int u,v;cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
		++du[u],++du[v],g[u][v]=g[v][u]=1;
	}
	int flg=1;
	for (int i=1;i<=n;++i) flg&=(!(du[i]&1));
	if (flg){
		cout<<"1\n";
		for (int i=1;i<=n;++i) cout<<1<<' ';
		cout<<'\n';return;
	}
	for (int i=1;i<=n;++i)
		g[i][n+1]=du[i]&1,g[i][i]=g[i][n+1];
	for (int i=1;i<=n;++i){
		int t=0;
		for (int j=i;j<=n;++j) if (g[j][i]){t=j;break;}
		swap(g[i],g[t]);
		for (int j=i+1;j<=n;++j) if (g[j][i]) g[j]^=g[i];
	}
	for (int i=n;i;--i){
		an[i]=g[i][n+1];
		for (int j=i+1;j<=n;++j)
			an[i]^=(g[i][j]*an[j]);
	}
	cout<<"2\n";
	for (int i=1;i<=n;++i) cout<<an[i]+1<<' ';
	cout<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while (t--) solve();
    return 0;
}
```

---

