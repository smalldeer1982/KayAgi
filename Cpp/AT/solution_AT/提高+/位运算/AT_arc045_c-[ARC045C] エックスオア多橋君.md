# [ARC045C] エックスオア多橋君

## 题目描述

### 题意简述

有一棵 $N$ 个点的树，每条边上有边权，给定整数 $X$，求树上点对 $\left(a,b\right)\left(1\le a<b\le N\right)$ 的个数，使得 $a$ 到 $b$ 的简单路径上边权的异或和等于 $X$。

## 说明/提示

$1\le N\le10^5,0\le X\le10^9,1\le x_i,y_i\le N,0\le c_i\le10^9$。

[Y204335](https://www.luogu.com.cn/user/360974)翻译

## 样例 #1

### 输入

```
6 7
1 2 5
2 3 3
3 4 6
2 5 2
5 6 7```

### 输出

```
3```

## 样例 #2

### 输入

```
6 3
1 2 1
2 3 3
3 4 2
4 5 3
4 6 1```

### 输出

```
4```

## 样例 #3

### 输入

```
10 1
9 10 1
6 10 1
5 2 1
8 6 1
4 5 1
7 6 0
3 8 0
3 1 1
8 2 0```

### 输出

```
25```

# 题解

## 作者：Y204335 (赞：3)

# \[ARC045C] エックスオア多橋君

## 题目大意

有一棵 $N$ 个点、有边权的树，给定 $X$，求 $a$ 到 $b$ 的简单路径上边权的异或和等于 $X$ 的点对 $\left(a,b\right)$ 的个数。

## 题目分析

直接算两点路径上的异或和比较难处理，可以考虑将其转化为方便处理的形式，可以记录每个点**到根节点的异或和** $w$，这样 $a,b$ 两点路径上的异或和就等于 $w_a\operatorname{xor}w_b$（两点 lca 以上的部分会直接异或消掉），用哈希表存一下每种 $w$ 的个数，之后对每个点的 $w_i$ 将其异或 $X$ 得到合法的另一个点的 $w_j$，再在哈希表上查 $w_j$ 的个数，统计即可。

时间复杂度 $O\left(n\right)$。

注意一条路径会被算两遍，所以答案要除二，并且当 $w_i\operatorname{xor}X=w_i$ 时，会把自己也算上，要记得减去。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define fir first
#define sec second
using namespace std;
const int N = 1e5 + 10;
int n, x;
ll w[N], ans;
vector<pair<int, ll>> e[N];
unordered_map<ll, int> ma;
void dfs(int nw, int fa, ll w)
{
    ::w[nw] = w;
    ma[w]++;
    for (auto i : e[nw]) {
        if (i.fir == fa)
            continue;
        dfs(i.fir, nw, w ^ i.sec);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> x;
    for (int i = 1; i <= n - 1; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        e[x].push_back({ y, c });
        e[y].push_back({ x, c });
    }
    dfs(1, 0, 0);
    for (int i = 1; i <= n; i++) {
        ans += ma[w[i] ^ x];
        if ((w[i] ^ x) == w[i])
            ans--;
    }
    ans /= 2;
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：RainySoul (赞：2)

### 题意

给定一颗树，需要你求出有多少个点对 $(u,v)$ 满足 $u$ 到 $v$ 路径上的边权异或和为 $X$。注意 $(1,2)$ 和 $(2,1)$ 视为同一个点对。

### 思路

下面记 $(a,b)$ 两点之间的路径异或和为 $\text{path}(a,b)$。

如果你做过树上两点之间的路径异或和问题的话你可以轻松发现这题有一个很好用的结论：

固定 $1$ 为根节点，那么 $\text{path}(u,v)=\text{path}(1,u) \operatorname{xor} \text{path}(1,v)$。

简单的推导过程：因为 $\text{path}(1, \operatorname{LCA}(u,v))$ 这一段被两次异或直接抵消掉了，所以 $\text{path}(1,u) \operatorname{xor} \text{path}(1,v)$ 就等于 $\text{path}(u, \operatorname{LCA}(u,v)) \operatorname{xor} \text{path}(v, \operatorname{LCA}(u,v))$ 即 $\text{path}(u,v)$。

有了这个结论之后此题的做法就呼之欲出了，`dfs` 预处理出 $1$ 到每个点的路径异或和，统计一下每个值出现过多少次，最后就可以 $O(n)$ 算了。

时间复杂度 $O(n)$。

另有一些细节详见代码注释。

AC code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100010;
struct zyx{
	int to,w;
};
int n,x,d[N];
unordered_map<int,int> cnt;
vector<zyx> e[N];
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
void dfs(int now,int fa,int dis){
	d[now]=dis;
	cnt[dis]++;//记录每个 dis 值出现次数 
	for(int i=0;i<e[now].size();i++){
		int to=e[now][i].to,w=e[now][i].w;
		if(to!=fa){
			dfs(to,now,dis^w);
		}
	}
}
signed main(){
	n=read(),x=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		e[u].push_back((zyx){v,w});
		e[v].push_back((zyx){u,w});
	}
	dfs(1,0,0);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=cnt[d[i]^x];
		if((d[i]^x)==d[i])ans--;//此处要注意去除 (u,u) 这样的点对
		// == 的优先级高于 ^，记得打括号 
	}
	cout<<ans/2<<'\n';//因为 (1,2) 和 (2,1) 都被计算过一遍，所以 ans/2 
	return 0;
}
```

---

## 作者：Hell0_W0rld (赞：1)

题意翻译的挺清楚的，就不翻译了。

我们考虑每条路径 $a\to b$ 上所有边权的异或和为 $d_a\oplus d_b$，其中 $\oplus$ 表示异或运算，$d_x$ 表示从根到 $x$ 路径上所有边的边权异或和。可通过 $d_{lca(x,y)}\oplus d_{lca(x,y)}=0$ 证明。

于是我们考虑跑一遍 dfs 求出所有 $d$ 值。答案统计时，用一个 `map` 统计出所有的 $d$ 值的出现次数，则一个点 $u$ 对答案的贡献即为 $cnt_{d_u\oplus k}$。累加所有贡献和即可。

远古时期写作，代码较为丑陋，就不放了。

---

