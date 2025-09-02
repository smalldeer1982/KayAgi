# Connectivity Addicts

## 题目描述

This is an interactive problem.

Given a simple undirected graph with $ n $ vertices numbered from $ 1 $ to $ n $ , your task is to color all the vertices such that for every color $ c $ , the following conditions hold:

1. The set of vertices with color $ c $ is connected;
2. $ s_c \leq n_c^2 $ , where $ n_c $ is the number of vertices with color $ c $ , and $ s_c $ is the sum of degrees of vertices with color $ c $ .

 It can be shown that there always exists a way to color all the vertices such that the above conditions hold. Initially, you are only given the number $ n $ of vertices and the degree of each vertex.

In each query, you can choose a vertex $ u $ . As a response, you will be given the $ k $ -th edge incident to $ u $ , if this is the $ k $ -th query on vertex $ u $ .

You are allowed to make at most $ n $ queries.

An undirected graph is simple if it does not contain multiple edges or self-loops.

The degree of a vertex is the number of edges incident to it.

A set $ S $ of vertices is connected if for every two different vertices $ u, v \in S $ , there is a path, which only passes through vertices in $ S $ , that connects $ u $ and $ v $ . That is, there is a sequence of edges $ (u_1, v_1), (u_2, v_2), \dots, (u_k, v_k) $ with $ k \geq 1 $ such that

1. $ u_1 = u $ , $ v_k = v $ , and $ v_i = u_{i+1} $ for every $ 1 \leq i < k $ ; and
2. $ u_k \in S $ and $ v_k \in S $ for every $ 1 \leq i \leq k $ .

 Especially, a set containing only one vertex is connected.

## 说明/提示

In the example, there is only one test case.

In the test case, there are $ n = 5 $ vertices with vertices $ 1, 2, 3, 4 $ of degree $ 2 $ and vertex $ 5 $ of degree $ 0 $ . It is obvious that vertex $ 5 $ is isolated, i.e., it does not connect to any other vertices.

A possible interaction is shown in the sample input and output, where $ 4 $ "?" queries are made on vertex $ 1 $ twice and vertex $ 3 $ twice. According to the responses to these queries, we know that each of vertex $ 1 $ and vertex $ 3 $ connects to two vertices $ 2 $ and $ 4 $ .

A possible solution is shown in the sample output, where vertex $ 1 $ and vertex $ 2 $ are colored by $ 1 $ , vertex $ 3 $ and vertex $ 4 $ are colored by $ 2 $ , and vertex $ 5 $ is colored by $ 3 $ . It can be seen that this solution satisfies the required conditions as follows.

- For color $ c = 1 $ , vertex $ 1 $ and vertex $ 2 $ are connected. Moreover, $ n_1 = 2 $ and $ s_1 = d_1 + d_2 = 2 + 2 = 4 \leq n_1^2 = 2^2 = 4 $ ;
- For color $ c = 2 $ , vertex $ 3 $ and vertex $ 4 $ are connected. Moreover, $ n_2 = 2 $ and $ s_2 = d_3 + d_4 = 2 + 2 = 4 \leq n_2^2 = 2^2 = 4 $ ;
- For color $ c = 3 $ , there is only one vertex (vertex $ 5 $ ) colored by $ 3 $ . Moreover, $ n_3 = 1 $ and $ s_3 = d_5 = 0 \leq n_3^2 = 1^2 = 1 $ .

## 样例 #1

### 输入

```
1
5
2 2 2 2 0

2

4

2

4```

### 输出

```
? 1

? 1

? 3

? 3

! 1 1 2 2 3```

# 题解

## 作者：周子衡 (赞：4)

一个简单的想法是：我们直接找出图中的每个连通分量，每个连通分量染一种颜色。但询问的信息似乎并不足以我们确定所有连通分量，考虑换一种操作方式。

考虑找到度数最大的节点 $u$。注意到

**引理** 设 $u$ 是图中度数最大的节点，如果某个连通块包含了 $u$ 以及 $u$ 的所有邻点，那么这个连通块是合法的。

**证明** 设 $u$ 的度数为 $d_u$。注意到此时联通块的大小 $n_u > d_u$，且每个点度数都 $\leq d_u$，那么度数总和 $\leq d_un_u < n_u^2$，符合题意。

进一步地，我们可以进一步加强这个引理：

**引理** 对任意节点 $u$，如果某个连通块中所有节点的度数都不超过 $u$ 的度数，且这个连通块包含了 $u$ 的所有邻点，那么这个连通块是合法的。

证明完全一致。

----------------------

我们依据上面的引理设计算法。初始时，将所有节点标记为未染色。接着不断执行下面的操作，直到所有节点都被染色为止：

- 在所有未染色的节点中选取度数最大的节点，设为 $u$。（如有多个任取一个）
- 顺次扫描 $u$ 的出边，如果扫到一个已访问节点（设为 $v$），那么把 $u$ 以及之前扫描到的 $u$ 的邻点全部和 $v$ 染上同一种颜色。如果一直没有找到，那么将 $u$ 和 $u$ 的全部邻点染成一种全新的颜色。

显见给出的染色方案是合法的。总询问次数 $=n-$ 最后的颜色数 $ < n$，符合要求。朴素地实现这个做法，时间复杂度为 $O(n^2)$，已经符合要求；当然也可以进一步优化至 $O(n)$。

---

## 作者：zac2010 (赞：3)

这类题着重于抓住充分条件进行构造。

解决这道题，就得抓住题目中最为特殊的条件：$s_c\leq {n_c}^2$。我们不难找出一种关于它的充分条件：$\max_{u\in S_c}d_u\leq n_c$。

尝试在此充分条件下设计构造方法：不妨按照 $d_u$ 进行排序，之后从大到小考虑每个未染色的 $u$。我们逐个对 $u$ 的所有邻节点进行询问。具体的，会有以下情况：

1. $u$ 的邻节点是染过色的

   把 $u$ 以及之前询问到的未染色邻节点染上 $v$ 的颜色，并结束对 $u$ 的操作。

2. $u$ 的邻节点未染色

   无事发生。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 1e5 + 10;
int n, u, col, d[N], c[N], id[N];
vector<int> v;
bool cmp(const int &i, const int &j){return d[i] > d[j];}
void solve(){
	cin >> n, col = 0;
	FL(i, 1, n) cin >> d[id[i] = i], c[i] = 0;
	sort(id + 1, id + n + 1, cmp);
	FL(i, 1, n) if(!c[id[i]]){
		vector<int>().swap(v), u = id[i];
		FL(j, 1, d[id[i]]){
			cout << "? " << id[i] << endl;
			cin >> u; if(c[u]) break;
			v.emplace_back(u);
		}
		c[id[i]] = c[u]? c[u] : ++col;
		for(const int &x: v) c[x] = c[id[i]];
	}
	cout << "! ";
	FL(i, 1, n) cout << c[i] << " ";
	cout << endl;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
} 
```

---

## 作者：Alex_Wei (赞：3)

- Update on 2022.10.19：修改错误。

非常神秘的一道题。

将 $s_c \leq n_c ^ 2$ 写成 $0\leq \sum_{col(u) = c} n_c - deg(u)$，尝试保证 $n_{col(u)} - deg(u) \geq 0$。

若两个点相连，则它们颜色相同。

考虑限制最大即度数最大的点 $u$，如果 $u$ 向所有邻居 $v_i$ 连边，则形成的菊花一定符合要求，因为 $u$ 是度数最大的点，又因为 $n_{col(u)} = deg(u) + 1$ 且 $col(v_i) = col(u)$，所以 $n_{col(v_i)} - deg(v_i)\geq 0$。

删去 $u$ 和所有邻居，继续考虑剩余度数最大的点 $u'$ 并向所有邻居连边。任意时刻若 $u'$ 向已经删除的点 $v'$ 连边，则会合并当前 $u'$ 连出的菊花和 $v'$ 所在连通块。因为我们按照度数从大到小的顺序处理，所以任意时刻连通块大小大于其中所有节点的最大度数，使得合并形成的新连通块大小同样大于其中所有节点的最大度数。

$u'$ 被合并之后就不用继续查 $u'$ 的邻居了，因为 $u'$ 所在连通块已经合法。

查询次数 $n - 1$，时间复杂度 $\mathcal{O}(n\log n)$。$n = 1000$ 应该是为了支持 hack。[代码](https://codeforces.com/contest/1738/submission/174186380)。

---

## 作者：liangbowen (赞：1)

[blog](https://www.cnblogs.com/liangbowen/p/18509124)。duel 的时候对上了脑电波很快过了，记一下这种我本来完全不会的题。

---

肯定是搞掉平方。把 $n_c$ 移到左边：$\dfrac{\sum\limits_{u\in S} deg_u}{|S|}=\text{平均数}\le |S|$。直接放缩左边，一个充分条件是：

$$\max\limits_{u\in S} deg_u\le|S|$$

考虑构造合法解。

观察到，假设 $u$ 在集合 $S$ 内，只需要将他的邻居全部放同一个颜色就行。于是有下面的简单算法：

+ 将 $deg$ 从大到小排序。
+ 对于当前点 $u$，如果邻居都没有被染色，直接新开一个颜色就行。
+ 如果邻居有颜色，直接把 $u$ 的颜色改成那个邻居的颜色就行。

容易证明其正确性。[code](https://codeforces.com/contest/1738/submission/288263409)，操作次数 $O(n)$。

---

## 作者：Sol1 (赞：1)

首先观察到如果知道整个图，那么一个连通块染两个颜色非常愚蠢。

但这没用啊，因为 $n$ 次询问咋说也找不出整个图。所以可以考虑到这题实际上是希望我们在 $n$ 次询问内找出一些边使得这个图“足够连通”。

然后有个简单的想法，就是每次选一个点出来遍历一圈，把遍历到的点记录一下，然后只遍历之前没遍历过的点。从贪心的角度讲，选点自然是选度数最大的那个让它尽量连通。这样找出若干条边之后，把找出的边生成的连通块（在原图里面一定也是连通块）染成一个颜色。

注意到这样找出边一定可以满足那个 $s<n^2$ 的条件，因为每一个点一定处于一个大小比本身度数更大的连通块里面。

然后交上去发现 WA 了，冷静一下会发现这样做会超出 $n$ 次操作。

为了优化，考虑一下上面那个“每一个点一定处于一个大小比本身度数更大的连通块里面”。

注意到由于我们按度数从大到小选，所以如果在遍历的过程中遍历到了一个之前遍历过的点，那么连上这条边之后当前点就满足上述条件了，就可以直接 break。

这样由于每条新边都会改变连通性，于是操作总数 $\leq n-1$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int d[1005], idx[1005], f[1005], rnk[1005];
bool vis[1005];

inline int GetRoot(int v) {
    if (f[v] == v) return v;
    return f[v] = GetRoot(f[v]);
}

inline void Merge(int x, int y) {
    int u = GetRoot(x), v = GetRoot(y);
    f[u] = v;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1;i <= n;i++) cin >> d[idx[i] = i];
        for (int i = 1;i <= n;i++) vis[i] = 0;
        for (int i = 1;i <= n;i++) f[i] = i;
        sort(idx + 1, idx + n + 1, [&](const int &x, const int &y) {
            return d[x] > d[y];
        });
        for (int i = 1;i <= n;i++) rnk[idx[i]] = i;
        for (int i = 1;i <= n;i++) {
            if (!vis[idx[i]]) {
                for (int j = 1;j <= d[idx[i]];j++) {
                    cout << "? " << idx[i] << endl;
                    int v; cin >> v; vis[v] = 1;
                    if (rnk[GetRoot(v)] < i) {
                        Merge(v, idx[i]);
                        break;
                    }
                    Merge(v, idx[i]);
                }
            }
        }
        cout << "! ";
        for (int i = 1;i <= n;i++) cout << GetRoot(i) << " ";
        cout << endl;
    }
    return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1738F Connectivity Addicts](https://www.luogu.com.cn/problem/CF1738F)

# 解题思路

我们发现取度数大的点可以建的图显然最优秀，具体原因下面会讲，并且同一个连通块内的节点染成一种颜色一定合法。那么此时我们将所有节点从大到小排序，然后直接暴力建图即可，我们每次询问会存在两种情况，我们设询问到的节点为 $x$：

- 若 $x$ 已经被染上颜色了，那么直接将此节点与 $x$ 节点连边，退出此节点查询。

- 若 $x$ 没有被染上颜色，那么直接将此节点与 $x$ 节点连边，继续进行此节点的查询。

那么此时由于度数是从大到小连边，此时必定有 $s_c \le d_c^2$，因为此时点已经与 $s_c$ 个节点连边，此时设询问的节点为 $x$，$i$ 与为 $x$ 连通的点，设 $d_x$ 为节点 $x$ 的度数，由于是从大到小枚举的，那么此时一定有 $d_i \le d_x$，而连入的点可能会变多，但绝不会变小，若新连入的点为 $y$，则也必有 $d_y \le d_x$，此时根据完全平方公式可知原条件一定仍满足，因此该构造方式是正确的。

# 参考代码

```cpp
ll ask(ll x)
{
    cout<<"? "<<x<<endl;
    ll y;
    cin>>y;
    return y;
}
ll n;
pii a[1000010];
ll col[1000010];
ll id;
void solve()
{
    id=0;
    cin>>n;
    forl(i,0,n+5)
        col[i]=0;
    forl(i,1,n)
        cin>>a[i].x,
        a[i].y=i;
    sort(a+1,a+1+n);
    reverse(a+1,a+1+n);
    forl(i,1,n)
        if(!col[a[i].y])
        {
            vector<ll>v;
            ll num=0;
            forl(j,1,a[i].x)
            {
                num=ask(a[i].y);
                v.pb(num);
                if(col[num])
                    break;
            }
            ll Col=col[num]?col[num]:++id;
            col[a[i].y]=Col;
            for(auto j:v)
                col[j]=Col;
        }
    cout<<"! ";
    forl(i,1,n)
        cout<<col[i]<<' ';
    cout<<endl;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

我们问出来了一些边，那么染色的时候肯定是把每个问出来的连通块染一种颜色。

考虑怎么去询问，我们先把度数从大到小排序。考虑从前往后满足，对每个还没有满足的点 $u$，肯定是孤立点（见下面流程），然后考虑不断去问其邻域，如果某次问出来在其前面（即度数比其大的）那么把这整个连通块合并起来就可以了。否则，我们问出了其所有领域，那么由于其领域度数比其小，所以这个连通块也是满足要求的。

每次询问都会减少一个连通分量。询问次数是 $n-1$。

---

## 作者：william555 (赞：0)

### 简要题意
这是一道交互题。  
有一张 $ n $ 个点的图，告诉你每个点的度数 $ d_i $，但是不告诉你有哪些边。  
你需要把这些点染色，要求对于每一种颜色，染成这种颜色的点是连通的，且需要满足 $ s_c \le n_c^2 $，其中 $ s_c $ 是这些点的度数之和，$ n_c $ 是这些点的个数。  
你可以进行不超过 $n$ 次询问，每次询问 "? u"，当第 $k$ 次询问 $ u $，交互库会告诉你第 $k$ 个与 $u$ 相邻的点。  
请你给出一种染色方案。

### 题解
发现对于每一种颜色的限制 $ s_c \le n_c^2 $ 很奇怪，但是不难想到，如果每一种颜色的点数都大于其所有点的度数最大值，则这个颜色是满足条件的。

从这个角度思考，假设先构造出一个满足条件的颜色，可以考虑找出度数最大的点 $x$，然后使用 $d_x$ 次询问，找出所有与 $x$ 相邻的点，然后将这些点和 $x$ 染成一样的颜色。这些点显然是连通的，并且点数超过了最大度数。

继续从这个角度思考，把所有点按度数排序，如果一个点已经被染色了，那么他就已经满足了条件，跳过它。  
对于一个没有被染色的点 $x$，暴力询问所有与它相邻的点。  
1. 如果询问到一个没有染过色的点 $y$，就把它染成和 $x$ 一样的颜色。  
2. 如果询问到一个已经被染过色的点 $y$，$y$ 当前所在颜色的点数一定不小于 $d_x$ 于是可以将 $x$ 染成和 $y$ 一样的颜色，然后 $x$ 直接满足了条件，于是结束对 $x$ 的询问。

不难发现这样所有颜色一定满足条件。  
分析一下询问次数：对于 1 类询问，每个点 $y$ 至多被询问一次；对于第 2 类询问，每个点 $x$ 至多询问出一次 2 类询问，并且 $x$ 一定是没有被 1 类询问问到的点。  
所以两种询问加起来次数一定不超过 $n$。

染色可以使用并查集来维护。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,d[N];
int mark[N];
int fa[N];
int gf(int x){return x==fa[x]?x:fa[x]=gf(fa[x]);}
bool solve(){
	int id=0;
	for(int i=1;i<=n;i++)
		if(!mark[i]&&d[i]>d[id])id=i;	
	if(!id)return 0;
	mark[id]=1;
	for(int i=1;i<=d[id];i++){
		cout<<"? "<<id<<endl;
		int x;cin>>x;
		fa[gf(x)]=gf(id);
		if(mark[x])break;
		mark[x]=1;	
	}
	return 1;
}
void mymain(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>d[i],fa[i]=i,mark[i]=0;
	while(solve());
	cout<<"! ";
	for(int i=1;i<=n;i++)cout<<gf(i)<<' ';
	cout<<endl;	
}
int main(){
	int t;cin>>t;
	while(t--)mymain();
	return 0;
}
```

---

