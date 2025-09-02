# Lorenzo Von Matterhorn

## 题目描述

Barney lives in NYC. NYC has infinite number of intersections numbered with positive integers starting from 1. There exists a bidirectional road between intersections $ i $ and $ 2i $ and another road between $ i $ and $ 2i+1 $ for every positive integer $ i $ . You can clearly see that there exists a unique shortest path between any two intersections.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696A/61a3ff7e8c29b0fc174f08897786128f1c443049.png)Initially anyone can pass any road for free. But since SlapsGiving is ahead of us, there will $ q $ consecutive events happen soon. There are two types of events:

1\. Government makes a new rule. A rule can be denoted by integers $ v $ , $ u $ and $ w $ . As the result of this action, the passing fee of all roads on the shortest path from $ u $ to $ v $ increases by $ w $ dollars.

2\. Barney starts moving from some intersection $ v $ and goes to intersection $ u $ where there's a girl he wants to cuddle (using his fake name Lorenzo Von Matterhorn). He always uses the shortest path (visiting minimum number of intersections or roads) between two intersections.

Government needs your calculations. For each time Barney goes to cuddle a girl, you need to tell the government how much money he should pay (sum of passing fee of all roads he passes).

## 说明/提示

In the example testcase:

Here are the intersections used:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696A/fd9f1cc0cd9bb95a97335a4462bfd7b1491ad15a.png)1. Intersections on the path are $ 3 $ , $ 1 $ , $ 2 $ and $ 4 $ .
2. Intersections on the path are $ 4 $ , $ 2 $ and $ 1 $ .
3. Intersections on the path are only $ 3 $ and $ 6 $ .
4. Intersections on the path are $ 4 $ , $ 2 $ , $ 1 $ and $ 3 $ . Passing fee of roads on the path are $ 32 $ , $ 32 $ and $ 30 $ in order. So answer equals to $ 32+32+30=94 $ .
5. Intersections on the path are $ 6 $ , $ 3 $ and $ 1 $ .
6. Intersections on the path are $ 3 $ and $ 7 $ . Passing fee of the road between them is $ 0 $ .
7. Intersections on the path are $ 2 $ and $ 4 $ . Passing fee of the road between them is $ 32 $ (increased by $ 30 $ in the first event and by $ 2 $ in the second).

## 样例 #1

### 输入

```
7
1 3 4 30
1 4 1 2
1 3 6 8
2 4 3
1 6 1 40
2 3 7
2 2 4
```

### 输出

```
94
0
32
```

# 题解

## 作者：_xxxxx_ (赞：3)

### 分析

不要把这题想的太复杂了。

树上路径加，路径求和，正常人一眼想到树剖，但是这棵树有无限个节点，树剖不可取。

虽然这棵树有无限个节点，但是题目告诉了我们一个十分友好的性质：这是一颗满二叉树。

由于 $u,v \le 10^{18}$，所以操作节点爬到根最多只需要 $\log_{2}{10^{18}}$ 次，那我们可以直接暴力向上跳，过程中给边加权即可，类似龟速的树剖。

每次选两个点中更深的那个点，在满二叉树，即本题中则更大的那个点，使其走向他的父亲，在走的时候对边进行修改。

由于这棵树有无限个节点，不可能全部存下来，因此只用 `map` 存下来每个点及其父亲之间的边即可，操作与查询都只与这些边有关。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <map>
#include <string.h>
#include <cstdio>
#include <algorithm>
#define int long long   //////////
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
map<int, map<int, int> > mp;//  看上面 
void add_way(int u, int v, int w)
{
	while(u != v)
	{
		if(u < v) swap(u, v);//选更深 
		mp[u / 2][u] += w;
		mp[u][u / 2] += w;
		u /= 2;//跳 
	}
}
int query_way(int u, int v)
{
	int ans = 0;
	while(u != v)
	{
		if(u < v) swap(u, v);
		ans += mp[u / 2][u];
		u /= 2;
	}
	return ans;
	//同上 
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> q;
	while(q--)
	{
		int opt, u, v, w;
		cin >> opt >> u >> v;
		if(opt == 1)
		{
			cin >> w;
			add_way(u, v, w);
		}
		if(opt == 2)
		{
			cout << query_way(u, v) << endl;
		}
	}
	return 0;
}
```

---

## 作者：Cloud_Umbrella (赞：3)

## 初步分析

因为这是一棵满二叉树，所以整棵树只有 $\log(n)$ 层，每次最多只和 $\log(n)\times 2$ 个点有关。直接用 ```map``` 来存树。

## 位运算思路

首先，编号为 $i$ 的结点的左儿子编号是 $2\times i$，右儿子的编号是 $2\times i+1$（当且仅当此结点有左右儿子的情况下）。所以任意结点 $i$（$i$ 不是根结点）的父亲就是 $\large\lfloor{\frac{i}{2}}\rfloor$。

其次，$u$，$v$（$u\ne v$）两点间的最短路是先从点 $u$ 开始，一直往上找到根节点，再往下找到点 $v$。这里有一个很好推的结论：一个深度为 $d$ 的点转成二进制数的第 $d$ 位一定为 $1$。所以，假如点 $u$ 和点 $v$ 位于同一层上，它们“异或”起来后原来的最高位一定为零。反之，它们“与”起来后原来的最高位一定为 $1$。这就是我们判断两点是否在同一层上的方法。当我们做了这个操作后，再分别从点 $u$ 和 $v$ 向上跳，一直到它们同时到达根节点停止。代码看上去有些晦涩，消化一下还是能懂的。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int Q;
map<long long,long long> mp;//不开long long见昊天大帝
int main(){
	scanf("%d",&Q);
	while(Q--){
		int opt;
		long long u,v,w;
		scanf("%d%lld%lld",&opt,&u,&v);
		if(u>v) swap(u,v);//编号越大深度越大，交换条件看个人喜好
		if(opt==1){
			scanf("%lld",&w);
			for(;(u^v)>(u&v);v>>=1) mp[v]+=w;//v>>=1相当与v/=2
			for(;u!=v;u>>=1,v>>=1) mp[u]+=w,mp[v]+=w;
		}
		else{
			long long ans=0;
			for(;(u^v)>(u&v);v>>=1) ans+=mp[v];//和上面一样，用ans加上边权即可
			for(;u!=v;u>>=1,v>>=1) ans+=mp[u],ans+=mp[v];
			printf("%lld\n",ans);
		}
	}
	return 0;//好习惯养成记
}
```

---

## 作者：noble_ (赞：2)

显然这是这张图是一个满二叉树。

那我们就暴力往上面找父亲，log级别的。

当高度不同时要先跳到一样再找。

由于u,v都很大，所以我们要套一层map

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<ll,ll> mp;
int Log(ll x) {
	int ans=0; 
	while(x>0) {ans++; x/=2;}
	return ans;
}
int main() {
	 int q; scanf("%d",&q);
	 while(q--) {
	 	int opt; ll u, v, w;
	 	scanf("%d",&opt);
	 	if(opt==1) {
	 		scanf("%I64d%I64d%I64d",&u,&v,&w);
	 		if(u<v) swap(u,v);
	 		while(Log(u) != Log(v)) {
	 			// printf("----- %d\n",u);
	 			mp[u]+=w; u/=2;
	 		}
	 		while(u!=v) {
	 			// printf("----- %d %d\n",u,v);
	 			mp[u]+=w; mp[v]+=w; u/=2; v/=2;
	 		}
	 	}
	 	else {
	 		scanf("%I64d%I64d",&u,&v);
	 		if(u<v) swap(u,v);
	 		ll ans=0;
	 		while(Log(u) != Log(v)) {
	 			ans+=mp[u] ; u/=2;
	 		}
	 		while(u!=v) {
	 			ans+=mp[u]; ans+=mp[v];  u/=2; v/=2;
	 		}
	 		printf("%I64d\n",ans);
	 	}
	 }
}
```

---

## 作者：GWBailang (赞：1)

[原题传送](https://www.luogu.com.cn/problem/CF696A)

~~看到题的第一眼：这图片是啥东西！~~

应该算是道比较模版的题吧，顶多算是道黄题。

题目给出了两种操作：

1.将 $u$ 到 $v$ 的最短路上的所有边的权值都加上 $w$。

2.求 $u$ 到 $v$ 的最短路上的所有边的权值之和。

在二叉树上找 $u$ 和 $v$ 之间的最短路，只需要找到两个节点公共的“祖先”即可。于是我写了 $6$ 个 dfs，结果调了半天样例都没过，只好换了个思路：

事实上有一种很简单的办法找 $u$ 和 $v$ 的公共“祖先”，每一个节点的“父亲”都只有一个，$u$ 的父亲是 $\lfloor{\frac{u}{2}}\rfloor$，所以我们可以先“优化”存树的方法：只存每个点到它“父亲”的那条边的权值。这样存就够了。注意这棵树是有无限的节点，因此我们需要用 ```map<long long,long long>``` 来存。

接下来我们这样来找：

在 $u$ 和 $v$ 中选一个大的数，将这个点到它“父亲”的那条边的权值加上 $w$，然后将这个数除以 $2$，也就是变成这个点的父节点。一直循环直到 $u=v$ 为止。想要找最短路上的权值之和同理。

可以看到每一次（一共 $q$ 次）操作的复杂度都在 $\log$ 级别，所以不会 TLE。

那么上代码：
```cpp

#include<bits/stdc++.h>
using namespace std;
map<long long,long long>ma;
long long lu,u,v,w;
int main(){
	int q,p;
	cin>>q;
	while(q--){
		cin>>p;
		if(p==1){
			cin>>u>>v>>w;
			while(u!=v){
				if(v>u)swap(u,v);
				ma[u]+=w;//将u和v中大的数变成它的“父亲”。
				u/=2;//程序默认向下取整
			}
		}else if(p==2){
			cin>>u>>v;
			lu=0;//记录最短路上所有边的权值
			while(u!=v){
				if(v>u)swap(u,v);
				lu+=ma[u];
				u/=2;//同上
			}
			cout<<lu<<endl;
		}
	}
	return 0;
}
```

最后还是那句话：十年 OI 一场空，不开 ```long long``` 见祖宗！

---

## 作者：Uuuuuur_ (赞：0)

## 思路
首先，这是一棵[满二叉树](https://baike.baidu.com/item/%E6%BB%A1%E4%BA%8C%E5%8F%89%E6%A0%91/7773283?fr=aladdin)。

其次，我们计算的边，不太好存储，就可以利用树的性质。设 $c_i$ 为结点$i$到它父亲的边权。

对于 1 操作，因为在树上结点 $u$ 到结点 $v$ 的最短路径是唯一的，就是到它们到**最近公共祖先**的路径。在满二叉树里，我们可以直接暴力向上找父亲，过程中更新所遇到的$c_i$，时间复杂度 $O(\log n)$。

对于 2 操作，和 1 操作同理，将路径上的 $c_i$ 加起来。

由于这道题 $u,v$ 很大，但更新的次数很少，所以我们还要哈希一下。

## 代码
```cpp
#include <iostream>
#include <unordered_map>


using namespace std;
typedef long long ll;
int q;
unordered_map<ll, ll> c;
int lg2(ll x) {
    int cnt = 0;
    while (x >= 2) {
        x /= 2;
        cnt++;
    }
    return cnt;
}
int main() {
    cin >> q;
    while (q--) {
        int op;
        ll u, v, w;
        cin >> op;
        if (op == 1) {
            cin >> u >> v >> w;
            if (u > v) swap(u, v);
            while (lg2(u) != lg2(v)) {
                c[v] += w;
                v /= 2;
            }
            while (v != u) {
                c[u] += w;
                c[v] += w;
                u /= 2;
                v /= 2;
            }
        } else {
            cin >> u >> v;
            ll sum = 0;
            if (u > v) swap(u, v);
            while (lg2(u) != lg2(v)) {
                sum += c[v];
                v /= 2;
            }
            while (v != u) {
                sum += c[u] + c[v];
                u /= 2;
                v /= 2;
            }
            cout << sum << endl;
        }
    }
    return 0;
}
```


---

## 作者：codeLJH114514 (赞：0)

首先，题面的两个操作都是对于 $u$ 和 $v$ 之间的最短路。

因为这是一颗树，所以两个点之间有且仅有一条不重复经过边的路径，又因为 $w \geq 1$ 所以边权不可能为负数，所以 $u$ 到 $v$ 的最短路一定是 $u \to \text{lca}(u, v) \to v$（从 $u$ 到 $v$ 的路径一定会经过 $u$ 和 $v$ 的公共祖先，而 $\text{lca}(u, v)$ 就一定是最近的）。

对于本题，因为所有出现的 $u$ 和 $v$ 的深度一定不超过 $\log_2 10^{18} < 60$，因此我们先将 $u$ 和 $v$ 跳到同一高度，再一起向上跳直到找到 $\text{lca}$。

然后，我们考虑存储边权，我们用 $w_i$ 表示从 $i$ 到 $i$ 的父亲的边的边权即可。因为本题 $u$ 和 $v$ 过大，但是询问数 $q$ 很少，所以可以用 `map` 和 `unordered_map` 存储。

然后对于每个操作 $u$ 和 $v$ 分别向上跳到 $\text{lca}(u, v)$，对于路径上的每一条边都修改/累加即可。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long

int q, u, v, w;
int opr;
std::map<int, int> W;

int Depth(int u) {
	int len = 0;
	while (u != 1) {
		u >>= 1;
		len += 1;
	} return len;
}

int LCA(int x, int y) {
	if (Depth(x) > Depth(y)) std::swap(x, y);
	while (Depth(x) < Depth(y)) y >>= 1;
	if (x == y) return x;
	while (x != y) {
		x >>= 1;
		y >>= 1;
	}
	return x;
}

signed main() {
	std::cin.sync_with_stdio(0);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> q;
	for (int i = 1; i <= q; i++) {
		std::cin >> opr >> u >> v;
		
		int lca = LCA(u, v);
		
		if (opr == 1) {
			std::cin >> w;
			while (u != lca) {
				W[u] += w;
				u >>= 1;
			}
			while (v != lca) {
				W[v] += w;
				v >>= 1;
			}
		} else {
			int ans = 0;
			while (u != lca) {
				ans += W[u];
				u >>= 1;
			}
			while (v != lca) {
				ans += W[v];
				v >>= 1;
			}
			std::cout << ans << std::endl;
		}
	}
	return 0;
}
```

---

