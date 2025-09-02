# Tree Folding

## 题目描述

Vanya wants to minimize a tree. He can perform the following operation multiple times: choose a vertex $ v $ , and two disjoint (except for $ v $ ) paths of equal length $ a_{0}=v $ , $ a_{1} $ , ..., $ a_{k} $ , and $ b_{0}=v $ , $ b_{1} $ , ..., $ b_{k} $ . Additionally, vertices $ a_{1} $ , ..., $ a_{k} $ , $ b_{1} $ , ..., $ b_{k} $ must not have any neighbours in the tree other than adjacent vertices of corresponding paths. After that, one of the paths may be merged into the other, that is, the vertices $ b_{1} $ , ..., $ b_{k} $ can be effectively erased:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF765E/8a327dc5b22e7a12ad1fd6e8837e08cb4a661c45.png)Help Vanya determine if it possible to make the tree into a path via a sequence of described operations, and if the answer is positive, also determine the shortest length of such path.

## 说明/提示

In the first sample case, a path of three edges is obtained after merging paths $ 2-1-6 $ and $ 2-4-5 $ .

It is impossible to perform any operation in the second sample case. For example, it is impossible to merge paths $ 1-3-4 $ and $ 1-5-6 $ , since vertex 6 additionally has a neighbour 7 that is not present in the corresponding path.

## 样例 #1

### 输入

```
6
1 2
2 3
2 4
4 5
1 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
1 2
1 3
3 4
1 5
5 6
6 7
```

### 输出

```
-1
```

# 题解

## 作者：fighter (赞：5)

## 题意

​	给你一棵树，可以把树上父亲相同的两条长度相同的链合并。（如图）问你最后能不能变成一条链，能的话求链的最短长度。（n<2*10^5）

## 解题思路

​	由于我们不知道最后的根是哪个节点，于是我们先随便找一个点dfs一次，并用一个set来记录当前节点为根的子树中所有链的长度。由于set自动去重，那么set中的元素个数$num$就只有以下几种情况：

1. $num = 0$，此时说明已经是叶子节点，直接返回0
2. $num=1$，此时说明子树中所有链都可以合并成为一条链，返回链长```*s.begin()```。
3. $num=2$，这种情况稍稍复杂一些，若当前节点为根节点，那么显然是符合题意的，且根节点就是链中间的一部分，返回链长``` *s.begin()+*--s.end()```。若当前节点不是根节点，则它头上会有一些奇奇怪怪的东西，显然不符合题意，返回-1。
4. $num>2$，不符合题意，返回-1。

如果在当前节点失败，那么我们就把第二次搜索的root赋值为当前节点。再用上述方法dfs一遍即可。

## 代码

```cpp
//参考 http://www.cnblogs.com/RUSH-D-CAT/p/6404742.html
#include <bits/stdc++.h>
#define MAX 200005
using namespace std;

int cnt, n, root;
int head[MAX], vet[MAX*2], Next[MAX*2], d[MAX];

void add(int x, int y){
    cnt++;
    Next[cnt] = head[x];
    head[x] = cnt;
    vet[cnt] = y;
}

int dfs(int x, int fa){
    set<int> s;
    d[x] = d[fa]+1;
    for(int i = head[x]; i; i = Next[i]){
        int v = vet[i];
        if(v == fa)	continue;
        int t = dfs(v, x);
        if(t == -1){
            return -1;
        }
        s.insert(t+1);
    }
    if(s.size() == 0){
        return 0;
    }
    else if(s.size() == 1){
        return *s.begin();
    }
    else if(s.size() == 2 && !fa){
        return *s.begin()+*--s.end();
    }
    root = x;
    return -1;
}

int main()
{
    cin >> n;
    int x, y;
    for(int i = 1; i < n; i++){
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    int ans = dfs(1, 0);
    if(ans == -1 && root){
        ans = dfs(root, 0);
    }
    while(!(ans&1)){
        ans >>= 1;
    }
    cout << ans << endl;
    
    return 0;
}
```



---

## 作者：zac2010 (赞：4)

[题目链接](https://codeforces.com/problemset/problem/765/E "题目链接")

## 题意

给出一颗无根树，你可以钦定一个根，并进行若干次下述操作：

* 选择一个点 $v$，以及 $v$ 延伸出去的两条长度相同的路径（两条路径没有重叠的边）。删去其中任意一条（不删 $v$）。

现在，操作次数、$v$ 以及两条路径都由你决定，但你需要求出，是否可以把这颗无根树删成一条链；假若能，最短的链长是多少。

## 解题思路

任取一个根，进行一遍 $\text{DFS}$，同时计算每颗子树是否可以合并成一条链/链的长度。

但问题在于如何把节点 $u$ 的所有儿子子树的信息合并为整颗子树的信息。先特判掉部分不合法的情况——有至少一颗子树返回不合法状态。之后考虑在 $u$ 的位置维护一个链长可重集，合并某颗儿子的子树时就直接把链长加进可重集里。

合并完后，我们进行一个分类讨论：

1. 有 $0$ 种不同的链长

   证明这个节点是叶节点，返回 $0$。

2. 只有 $1$ 种链长（设它为 $l$）

   子树合并后的链长为 $l$。

3. 有两种不同的链长

   1. 当前节点不是根节点

      会发现在当前的树最后不可能变成一条链，同时记录一个 $rt2$，$rt2=u$。

   2. 当前节点为根节点

      形成了一条链，返回两种链长相加。

3. 有 $>2$ 种不同的链长

   最终不可能变成一条链。

这样的策略是在钦定了一个根的情况下。假设通过上述流程，最终没法变成一条链，考虑把 $rt2$ 提为根再做一遍。这样便可保证答案正确（假设 $rt2$ 为根还不行，归纳一下便可得这棵树确实不合法）。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e5 + 10;
unordered_map<int, int> mp[N];
int n, r, ans, rt = 1;
vector<int> e[N];
int dfs(int u, int p){
	unordered_map<int, int>().swap(mp[u]);
	for(int &v: e[u]) if(v != p){
		mp[u][r = dfs(v, u) + 1] = 1;
		if(!r) return -1;
	}
	if(!mp[u].size()) return 0;
	if(mp[u].size() <= 1 + (!p)){
		r = 0; for(auto &it: mp[u]) r += it.first;
		return r;
	}
	rt = u; return -1;
}
int main(){
	scanf("%d", &n);
	FL(i, 2, n){
		int u, v; scanf("%d%d", &u, &v);
		e[u].emplace_back(v), e[v].emplace_back(u);
	}
	dfs(1, 0), ans = dfs(rt, 0);
	printf("%d\n", ans >> __builtin_ctz(ans));
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

分享一种我认为很优美的解法。

首先发现，如果有一个点 $root$ 使得以它为根，所有叶子深度相等，那么这一定是可行的。可以想象成将它拎出来并且把其他点横向拍扁。

然后，容易发现两个 $root$ 相同的，满足上面要求的树组合在一起也是可以的，即分成上下两部分分别拍扁。

所以可以想到，如果能找出这个点，那么问题就解决了。

**Lemma 1：只要最后能并成一条链，则该链最小长度一定。**

Proof：如图，红线，蓝线分别为两种不同答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/w9ir9nzg.png)

则一定有两段红蓝线对应相等，否则它们将无法合并。

**Lemma 2：这个点一定是直径的两个端点之一或直径中点（如果存在）。**

Proof：考虑直径在这棵树中的位置。下图中上、下两个三角形代表的子树内叶子深度相同，红线为直径。

- 如果直径跨越两树。

![](https://cdn.luogu.com.cn/upload/image_hosting/smwaospt.png)

如果有上下有一边只有一棵子树，则一定有一个直径端点可行。

否则，不妨假设下半子树深度大于上半，且 $root$ 不为直径中点，则一定有蓝线长于红线，则红线不为直径，矛盾。

- 如果直径只在一棵子树内。

![](https://cdn.luogu.com.cn/upload/image_hosting/1ser7mpf.png)

则一定有直径拐点两边长度相等，则 $root$ 为直径中点。

综上，我们只需要对直径两个端点和中点分别做一遍，即可找到答案。

时间复杂度 $O(n)$，优于现在有的题解。

code：

```cpp
int n,m,t,dep[N],dp[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
vector<int> g,d;
il void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void find_t(int u,int f){
	dep[u]=dep[f]+1;
	if(dep[u]>dep[t])
		t=u;
	go(i,u){
		int v=e[i].to;
		if(v==f)
			continue;
		find_t(v,u);
	}
}
void find_l(int u,int f){
	g.eb(u);
	if(g.back()==t)return;
	go(i,u){
		int v=e[i].to;
		if(v==f)
			continue;
		find_l(v,u);
		if(g.back()==t)return;
	}
	g.pop_back();
}
void dfs(int u,int f){
	dep[u]=dep[f]+1;
	go(i,u){
		int v=e[i].to;
		if(v==f)
			continue;
		dfs(v,u);
		if(!f){
			d.eb(dp[v]);
			continue;
		}
		if(!dp[u])dp[u]=dp[v];
		else if(dp[v]!=dp[u])dp[u]=-1;
	}
	if(!dp[u])dp[u]=dep[u];
}
void solve(int u){
	mems(dp,0);
	d.clear();
	dfs(u,0);
	int x=0,y=0;
	for(int i:d){
		if(i==-1)return;
		if(!x)x=i;
		else if(x!=i){
			if(!y)y=i;
			else if(y!=i)return;
		}
	}
	int ans=x&&y?x+y-2:x+y-1;
	while(ans%2==0)ans/=2;
	printf("%d\n",ans);
	exit(0);
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	find_t(1,0);
	int x=t;t=0;
	find_t(x,0);
	int y=t;
	find_l(x,0);
	solve(x),solve(y);
	if(g.size()&1)solve(g[g.size()/2]);
	puts("-1");
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

