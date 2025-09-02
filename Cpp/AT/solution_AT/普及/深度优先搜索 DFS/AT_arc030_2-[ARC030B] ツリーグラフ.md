# [ARC030B] ツリーグラフ

## 题目描述

### 题目大意

给定一棵 $n$ 无权树，树上每个结点有 $0$ 或 $1$ 个宝石，求从结点 $x$ 出发拿到所有宝石再回到 $x$ 的最短路径。

## 样例 #1

### 输入

```
5 1
1 0 1 0 1
1 2
2 3
2 4
1 5```

### 输出

```
6```

## 样例 #2

### 输入

```
3 2
0 1 0
1 2
2 3```

### 输出

```
0```

# 题解

## 作者：Y204335 (赞：4)

# \[ARC030B] ツリーグラフ

想到一种很简洁的写法，发篇题解记录一下。

## 题意简析

给一棵树以及起点 $x$，每个节点上有 $0$ 或 $1$ 的值，求从起点出发经过所有值为 $1$ 的节点再回到起点的最短路径。

## 题目分析

由于所给的是一棵树，在树上两点之间的简单路径**有且仅有一条**，所以如果只有两个点，最短路径应该是简单路径的**两倍**。

再考虑多个点的情况，可以发现如果点 $B$ 在点 $X$ 到点 $A$ 的路径上的某一节点的子树中，那么在走到 $A$ 时**顺便走** $B$ **一定是最优的**，并且最短路径是 $X$ 到 $A$ 的简单路径与 $B$ 到 $X \longrightarrow A$ 路径上节点的简单路径之和乘二，如下图。![](https://cdn.luogu.com.cn/upload/image_hosting/2nih4htp.png)这样各子树的最短路径就可以求出，并且由于最后**一定要返回起点**，所以从哪个子树出发是**不重要的**，只需要求出**各子树的情况**即可，具体就是要求出每个子树内最短的能连接所有 $1$ 节点的路径。形式化的说，最短路径一定是 **含 $1$ 节点的子树的边数 $-$ 不含 $1$ 节点的子树的边数**，为方便计算，边数可以由 $节点数-1$ 代替。

${\large 最短路径=(size_{含1节点的子树} - size_{不含1节点的子树}-1) \times 2}$

在实现中，**不需要分别求出**含 $1$ 节点和不含 $1$ 的子树的大小，只需要 $dfs$ 统计从最低的 $1$ 节点到 $X$ 点的节点数即可。

当节点数为 $0$ 时，需要**特判**输出 $0$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 101;
int n, h[N], x, siz[N];
vector<int> d[N];
void dfs(int nw, int fa)
{
    if (h[nw])
        siz[nw]++; // 如果为1节点，siz初始化为1
    for (auto i : d[nw]) {
        if (i == fa)
            continue;
        dfs(i, nw);
        siz[nw] += siz[i];
    }
    if (siz[nw] && !h[nw])
        siz[nw]++; // 如果子树中有1节点，这个节点就要算上
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        d[u].push_back(v);
        d[v].push_back(u);
    }
    dfs(x, 0);
    if (siz[x] == 0)
        cout << 0 << endl;
    else
        cout << (siz[x] - 1) * 2 << endl;
    return 0;
}
```

---

## 作者：qianyuzhe (赞：4)

作为本题的首 A，蒟蒻非常高兴，于是特意写了一篇题解来纪念。

## 题意简述

给定一棵树，其中每条边的权值为 $1$，树上每个结点有 $0$ 或 $1$ 个宝石，求从某个结点出发拿到所有宝石再回来的最短路径。

## 题目分析

先考虑从 $x$ 到一个宝石的最短路径。众所周知，树上最短路径可以用最近公共祖先来求。在这里我们可以以 $x$ 为根预处理树上每个结点 $i$ 的深度 $deep_i$，则结点 $i$ 和 $x$ 之间的最短路径就是从 $i$ 开始向上跳到根节点的路径。

接下来再考虑从 $x$ 出发拿到所有宝石的最短路径。通过分析题目，我们可以得出如下结论：

- **从 $x$ 出发拿到所有宝石的最短路径必然都是从 $x$ 到所有宝石的最短路径的子集。**

- **为保证从 $x$ 到所有宝石的最短路径最短，树上的任意一条边的经过次数都不应该超过 $2$。**

于是我们就可以用从 $x$ 到每个宝石的最短路径的并集构造出一棵树，这棵树的边集就是从 $x$ 出发拿到所有宝石的最短路径。由于拿到所有宝石还要再回到出发点，所以最短路径的权值还要乘上 $2$。

**注意：宝石的数量可能为 $0$，此时直接输出 $0$ 即可。**

## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,x,i,s,e,h,c,d[105],f[105],b[105];//c为计数器，d存储某结点的深度，f存储某结点的父节点 
vector<int>v[105];
queue<int>q;
void dfs(int x,int y){
	d[x]=y;
	b[x]=1;
	for(int i=0;i<v[x].size();i++){
		if(!b[v[x][i]]){
			f[v[x][i]]=x;
			dfs(v[x][i],y+1);
		}
	}
}
void lca(int x,int y){
	if(d[x]<d[y])swap(x,y);
	while(d[x]>d[y]){
		x=f[x];//注意和倍增有所区别，是一步一步往上跳
		b[x]=2;
	}
}
int main(){
	ios::sync_with_stdio(false);
    	cin>>n>>x;
    	for(i=1;i<=n;i++){
    		cin>>h;
    		if(h)q.push(i);//用队列存储有宝石的结点 
	}
	if(q.empty())return puts("0"),0;//当宝石数量为0时，直接输出0 
	for(i=n;--i;){
		cin>>s>>e;
		v[s].push_back(e);
		v[e].push_back(s);
	}
	dfs(x,1);
	memset(b,0,sizeof(b));
	while(!q.empty()){
		b[x]=b[q.front()]=2;//两端点也要并入点集 
		lca(x,q.front());
		q.pop();
	}
	for(i=1;i<=n;i++)c+=b[i];
	cout<<c-2<<endl;//岛国题目要换行，否则会WA
	/*
	树上边数=树上点数-1
	答案=树上边数*2
	*/ 
}
```

---

## 作者：Chenyichen0420 (赞：3)

## 思路分析

很显然，当且仅当一个子树有宝石时才会向下走。跟着这个思路写就完了。

于是呢，我们将所有的有钻石的位置标记为一，然后向下搜索，发现有子树有钻石就将这个点置一，搜完所有子树后接着上传。完成标记。

然后再搜一遍，如果一个子树有钻石，就加上这个子树的答案再加二即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x; bool hss[1005];
vector<int>son[1005]; int ans[1005];
inline bool dff(int p, int fa) {
	for (int sp : son[p])
		if (sp != fa) hss[p] |= dff(sp, p);
	return hss[p];
}
inline int get(int p, int fa) {
	int ret = 0;
	for (int sp : son[p])
		if (sp != fa && hss[sp]) ret += get(sp, p) + 2;
	return ret;
}
int main() {
	ios::sync_with_stdio(false);
	cin >> n >> x;
	for (int i = 1, k; i <= n; ++i)
		cin >> k, hss[i] = k;
	for (int i = 1, a, b; i < n; ++i)
		cin >> a >> b,
		son[a].push_back(b),
		son[b].push_back(a);
	dff(x, 0); cout << get(x, 0) << endl;
	return 0;
}
```

---

## 作者：LJQ0808 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc030_2)

# 题解

我们可以发现拿到宝石之后也要返回点 $x$，但这个图为一棵树，保证没有环，所以每个点到另外的点一定只有当且仅当一条路径，故最后答案为走过去的路径乘 $2$。



于是，我们可以用 DFS 搜索答案。

在搜索过程中，用 $a_i$ 表示子树 $i$ 中是否有宝石。如果有，就向这个方向继续搜索答案。

搜索完之后，答案需要乘 $2$。

AC code:

```
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,k,px;
vector<int> g[N];
void add_edge(int u,int v){//建单向边。 
	g[u].push_back(v);
}
void add_und_edge(int u,int v){//建双向边。 
	add_edge(u,v);add_edge(v,u);
} 
bool a[N];//a[i] 表示子树 i 中是否有宝石。
void dfs1(int u,int f){//预处理。  
	for(int v:g[u]){//枚举 u 的儿子 v。
		if(v!=f){//不为父亲，不重复搜索。  
			dfs1(v,u);//搜索。 
			a[u]|=a[v];//子树 v 中有没有宝石。 
		} 
	}
}
int ans=0;
void dfs2(int u,int f){//求答案。 
	for(int v:g[u]){//枚举 u 的儿子 v。 
		if(v!=f && a[v]){//不为父亲且子树 v 中有宝石。
			ans+=2;//需要回原路。 
			dfs2(v,u);//搜索。 
		}
	}
}
signed main(){
	//HAPPY!
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n>>px;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add_und_edge(x,y);
	}
	dfs1(px,0);//搜索。 
	dfs2(px,0);//搜索。 
	cout<<ans<<"\n";
	return 0;
}
```

---

