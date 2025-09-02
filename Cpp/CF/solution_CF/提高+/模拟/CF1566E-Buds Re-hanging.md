# Buds Re-hanging

## 题目描述

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. The parent of a vertex $ v $ (different from root) is the previous to $ v $ vertex on the shortest path from the root to the vertex $ v $ . Children of the vertex $ v $ are all vertices for which $ v $ is the parent.

A vertex is a leaf if it has no children. We call a vertex a bud, if the following three conditions are satisfied:

- it is not a root,
- it has at least one child, and
- all its children are leaves.

You are given a rooted tree with $ n $ vertices. The vertex $ 1 $ is the root. In one operation you can choose any bud with all its children (they are leaves) and re-hang them to any other vertex of the tree. By doing that you delete the edge connecting the bud and its parent and add an edge between the bud and the chosen vertex of the tree. The chosen vertex cannot be the bud itself or any of its children. All children of the bud stay connected to the bud.

What is the minimum number of leaves it is possible to get if you can make any number of the above-mentioned operations (possibly zero)?

## 说明/提示

In the first test case the tree looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1566E/0d2a2e94983d55330dac54f278d1a33d1eb1221d.png)Firstly you can choose a bud vertex $ 4 $ and re-hang it to vertex $ 3 $ . After that you can choose a bud vertex $ 2 $ and re-hang it to vertex $ 7 $ . As a result, you will have the following tree with $ 2 $ leaves:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1566E/146e9305c79679a883d051dcc15fe610857df849.png)It can be proved that it is the minimal number of leaves possible to get.

In the second test case the tree looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1566E/c78997ae531f85421ad1ff3c7eaaf49571559377.png)You can choose a bud vertex $ 3 $ and re-hang it to vertex $ 5 $ . As a result, you will have the following tree with $ 2 $ leaves:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1566E/b4fd18b6b31191b690cb273c6f18bb397eaf968d.png)It can be proved that it is the minimal number of leaves possible to get.

## 样例 #1

### 输入

```
5
7
1 2
1 3
1 4
2 5
2 6
4 7
6
1 2
1 3
2 4
2 5
3 6
2
1 2
7
7 3
1 5
1 3
4 6
4 7
2 1
6
2 1
2 3
4 5
3 4
3 6```

### 输出

```
2
2
1
2
1```

# 题解

## 作者：devans (赞：11)

首先，最终这棵树的叶子节点数量显然与叶子节点数和 `bud` 节点数有关系，因为通过将一个 `bud` 节点直接连在某个叶子节点下面我们可以将整棵树的叶子节点数减去 $1$。  
我们还可以发现，进行一次移动 `bud` 节点的操作之后可以随时再移回去（只要它还是 `bud` 节点），因此我们随便操作都不会对这棵树最终得到的答案有任何影响。  

因此，考虑最大化 `bud` 节点数。我们可以一直直接把所有当前是 `bud` 节点的节点移到根上，直到没有还没连在根节点上的 `bud` 节点。这样就会得到一个深度不大于 $2$ 的树，像这样（黑色的是根，剩余任意灰色的都是移到根上的 `bud` 节点）：
![](https://cdn.luogu.com.cn/upload/image_hosting/k9dkk4yj.png)
然后我们直接使尽可能多的 `bud` 节点都连在叶子节点上以减少叶子节点的数目。具体的，设 $n$ 为总结点数，$k$ 为 `bud` 节点数，那么此时树有 $n-k-1$ 个叶子结点（总结点数去掉根和 `bud` 节点数）：

- 如果没有叶子结点直接连在根上，那么我们需要留一个 `bud` 节点连在根上，剩下的 `bud` 节点一定都可以连在一个叶子节点上。因此，答案为 $n-k-1-(k-1)$，即为 $n-2\times k$。
- 如果有至少一个叶子结点直接连在根上，那么我们可以直接把所有 `bud` 节点都连在叶子节点上。答案为 $n-k-1-k$，即为 $n-2\times k-1$。
![](https://cdn.luogu.com.cn/upload/image_hosting/wwuh7tt2.png)

感性理解正确性：

- 把一个 `bud` 节点移到根上这种操作要么使树增加一个叶子结点，要么不增加，而且我们在让 `bud` 节点去连叶子节点时一定会使叶子节点数减回去。
- 一个 `bud` 节点根据定义必定有至少一个叶子节点，因此不会出现叶子结点不够连的情况。  

如果不会找 `bud` 节点的话详见代码。  
时间复杂度 $O(n)$ 的。
```cpp
#include<bits/stdc++.h>
//#include"testlib.h"
using namespace std;
//And in that light,I find deliverance.
//#define int long long
template<typename T> void read(T &x) {
	x=0;int f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	x=x*f;
}
const int N=200020;
struct Edge{
	int p,next;	
}edge[N<<1];
int cnt=0,head[N],d[N];
void add(int u,int v){
	cnt++;
	edge[cnt]=(Edge){v,head[u]};
	head[u]=cnt;	
}
int T,n,k,s1,s2,s3;
void find(int cur,int fa){
	bool res=0;
	for(int i=head[cur];i;i=edge[i].next)
		if(edge[i].p!=fa){
			find(edge[i].p,cur);
			if(d[edge[i].p]==2) res=1;
		}
	if(fa!=-1){
		if(res) d[cur]=3,k++;
		else d[cur]=2;
	}
}
signed main(){
	read(T);
	while(T){
		T--;k=cnt=s3=0;
		read(n);
		for(int i=1;i<=n;i++) d[i]=head[i]=0;
		for(int i=1;i<n;i++) read(s1),read(s2),add(s1,s2),add(s2,s1);
		d[1]=1;
		find(1,-1);
		for(int i=head[1];i;i=edge[i].next)
			if(d[edge[i].p]==2){s3=1;break;}
		cout<<n-2*k-s3<<endl;
	}
	return 0;
}
```

---

## 作者：xuyifei0302 (赞：3)

读完题，我们不难发现，最后的树的样子是由若干个菊花连在一起。而每一个菊花就是一个芽。所以，我们考虑找出所有的芽，将他们连在一起。我们可以先搜索一遍，找到所有可以做芽。在搜索的过程中，每找到一个芽，就把这个芽从原树上分离开，统计芽的个数。设我们现在找到了 $x$ 个芽，那么我们的答案应为 $n - 2x + 1$，其中 $n - 2x$ 代表除去一个叶子节点外多出来的叶节点数，然后再加上整体合并而必然产生的一个叶节点。但是，因为根节点是不可以连接的，所以，如果根节点也是一个芽，那么芽的个数就要减一。

接下来是代码环节：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
bool mark[200005];
vector<int> v[200005];
void dfs(int u, int father) {
	bool p = false;
	for (auto i : v[u]) {
		if (i != father) {
			dfs(i, u);
			p |= mark[i];
		}
	}
	mark[u] = !p;
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i < n; i ++) {
			int x, y;
			cin >> x >> y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		dfs(1, 1);
		int ans = 0;
		for (int i = 1; i <= n; i ++) {
			if (!mark[i]) {
				ans ++;
			}
		}
		ans = n - (ans - 1) * 2 - 1;
		if (mark[1]) {
			ans --;
		}
		cout << ans << "\n";
		for (int i = 1; i <= n; i ++) {
			v[i].clear();
			mark[i] = false;
		}
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# CF1566E 题解



## 思路分析

首先注意到，每一次把一个 bud 节点放到一个叶子上，会使得叶子结点的总数 $-1$，因此考虑尽可能多地提取出 bud 节点。

假如我们已经把所有的 bud 节点都提取出来了，那么接下来考虑按照提取的顺序依次加入剩下的节点构成的剩余树上。

假设我们有 $k$ 个 bud 节点，对于剩下的 $n-k$ 个节点显然除了根就都是叶子，一次添加能够减少 $1$ 个叶子，因此的答案为 $n-2\times k-1$，特别地，如果删去所有 bud 节点，而剩下的点只有一个根的话，第一次添加并不会减少一个叶子，而此时答案为 $n-2\times k$。

而在求所有 bud 节点的时候，我们记录下每个点是否为 bud 节点，如果一个节点所有儿子中有一个不是 bud 节点，那么这个节点一定是 bud 节点，否则则不是 bud 节点，因此我们把“是不是 bud 节点”作为 dfs 的返回值即可。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int cnt=0;
vector <int> G[MAXN];
inline bool dfs(int p,int f) {
	if(f!=0&&G[p].size()==1) return false;
	bool ret=false;
	for(int v:G[p]) {
		if(v==f) continue;
		ret|=!dfs(v,p);
	}
	if(ret&&f!=0) ++cnt;
	return ret;
}
inline void solve() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) G[i].clear();
	for(int i=1;i<n;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cnt=0;
	bool ret=dfs(1,0);
	if(!ret) printf("%d\n",n-2*cnt);
	else printf("%d\n",n-2*cnt-1);
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
} 
```



---

