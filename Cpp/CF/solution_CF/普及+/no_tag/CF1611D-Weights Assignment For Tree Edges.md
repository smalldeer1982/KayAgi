# Weights Assignment For Tree Edges

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. Vertices are numbered from $ 1 $ to $ n $ . Any vertex can be the root of a tree.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root.

The tree is specified by an array of ancestors $ b $ containing $ n $ numbers: $ b_i $ is an ancestor of the vertex with the number $ i $ . The ancestor of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root. For example, on the simple path from $ 5 $ to $ 3 $ (the root), the next vertex would be $ 1 $ , so the ancestor of $ 5 $ is $ 1 $ .

The root has no ancestor, so for it, the value of $ b_i $ is $ i $ (the root is the only vertex for which $ b_i=i $ ).

For example, if $ n=5 $ and $ b=[3, 1, 3, 3, 1] $ , then the tree looks like this.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611D/d1bc9693f3c37aa82543dc99b8156e197e08fb59.png)An example of a rooted tree for $ n=5 $ , the root of the tree is a vertex number $ 3 $ .You are given an array $ p $ — a permutation of the vertices of the tree. If it is possible, assign any positive integer weights on the edges, so that the vertices sorted by distance from the root would form the given permutation $ p $ .

In other words, for a given permutation of vertices $ p $ , it is necessary to choose such edge weights so that the condition $ dist[p_i]<dist[p_{i+1}] $ is true for each $ i $ from $ 1 $ to $ n-1 $ . $ dist[u] $ is a sum of the weights of the edges on the path from the root to $ u $ . In particular, $ dist[u]=0 $ if the vertex $ u $ is the root of the tree.

For example, assume that $ p=[3, 1, 2, 5, 4] $ . In this case, the following edge weights satisfy this permutation:

- the edge ( $ 3, 4 $ ) has a weight of $ 102 $ ;
- the edge ( $ 3, 1 $ ) has weight of $ 1 $ ;
- the edge ( $ 1, 2 $ ) has a weight of $ 10 $ ;
- the edge ( $ 1, 5 $ ) has a weight of $ 100 $ .

The array of distances from the root looks like: $ dist=[1,11,0,102,101] $ . The vertices sorted by increasing the distance from the root form the given permutation $ p $ .

Print the required edge weights or determine that there is no suitable way to assign weights. If there are several solutions, then print any of them.

## 说明/提示

The first set of input data of the example is analyzed in the main part of the statement.

In the second set of input data of the example, it is impossible to assign the positive weights to obtain a given permutation of vertices.

## 样例 #1

### 输入

```
4
5
3 1 3 3 1
3 1 2 5 4
3
1 1 2
3 1 2
7
1 1 2 3 4 5 6
1 2 3 4 5 6 7
6
4 4 4 4 1 1
4 2 1 5 6 3```

### 输出

```
1 10 0 102 100
-1
0 3 100 1 1 2 4
6 5 10 0 2 3```

# 题解

## 作者：JCLinux (赞：4)

这个题是一道**阅读理解题**，首先要读懂题目要求。

## 题目大意：

用数组 tree 来表示**树**，其中 $tree[i]$ 代表节点 i 的父节点。树的大小是 n .

给你一个大小也为 n 的全排列 p ，  $p[i]$ 顾名思义.

现在你的工作是赋予树上的每条边一个长度，使得树上所有节点**按照到根节点的长度排序**之后的结果与全排列 p 相同，做不到就输出 $-1$ .

## 思路分析：

现在我们知道，树上的点，和全排列是能够一一对应的，也就是说通过赋予每个边长度，让这棵树上所有点**按照**到根节点的距离**排序**之后的**顺序**是全排列 p 的顺序（还是那句话，阅读理解）.

那么我们不妨假设，全排列 p 中第 i 个点 $p[i]$ 到树根的距离就是 i ，以此为据，来推导出每个边应有的长度.

我们能够发现：根节点必须在全排列的第一位 $p[1]$ ，这是因为树上没有任何一个点，到根节点的距离比根节点自身到根节点的距离更小，排序完成之后根节点一定~~首当其冲~~.

所以倘若 $p[1] != root$ ，对不起，直接 $-1$，这个可以算是一个小小的特判吧，其实没有也行，但是它能够帮助我们更好地理解题意.

那么现在开始考虑普遍情况，对于排列 p 中第 $i$ 个元素，对应在树上也就是节点 $p[i]$ ，它到根节点的距离是 $i$ .

那么我们**可以肯定**的一点就是：

它的父节点 $tree[ p[i] ]$ 到根节点的距离必须得是已知的，而已知的就说明我们在 $p[i]$ 之前就求过它的距离，因为距离就等于 $i$ ，也就是说，他的**父节点到根节点的距离一定比当前节点小**，这不刚好就是树（没有负边）的性质吗！！

反过来想，如果它父节点还没被求出来，就说明它父节点一定在 $p[i]$  的后面出现，那么它的**父节点到树根的距离就一定比子节点大，这是不可能的**

所以，这是我们判断能否成功构建的依据.

如果在中途出现不满足上述约束的情况出现，就说明没办法构建.

在知到构建约束之后，构建方法会比较好想一些.

我们令 $tall[i]$ 代表节点 $i$ 到根节点的距离，用 $ans[i]$ 代表第 $i$ 个节点与其父节点之间的边的距离（即题目所求的答案）.

那么 $ans[i] = i- tall[ tree[ p[i] ] ]$ .

同时别忘了更新当前点到根节点的距离: $tall[ p[i] ]=i$ .

别嫌我罗嗦，这种思维偏重一点的题目，要讲就要讲得非常详细，因为哪怕有一点卡住，也没办法做.

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int tree[200005];//树上某个节点的父节点
int p[200005];//要求树按照距离树根的排列顺序
int tall[200005];//树上某个节点到根节点的距离
int ans[200005];//记录答案（边的长度）
int main()
{
    cin.sync_with_stdio(false);
    cin >> t;
    while(t--)
    {
        cin >> n;
        int root;
        for(int i=1;i<=n;i++)
        {
            cin >> tree[i];
            if(tree[i]==i) root=i;//寻找根节点
            tall[i]=-1;
        }
        for(int i=1;i<=n;i++) cin >> p[i];
        tall[root]=0;//根节点的距离是0
        ans[root]=0;
        if(p[1]!=root)//排列中的第一个点必然是root才行
        {
            cout << -1 << endl;
            continue;
        }
        bool flag=1;
        for(int i=2;i<=n;i++)//核心代码
        {
            if( tall[ tree[ p[i] ] ] <0 )//对于第i个排列来说，p[i] 的父节点必须比p[i]距离根要近，即在[1,i)中已经出现过才行，因为不可能做到父节点比子节点更远
            {
                flag=0;//出现矛盾
                break;
            }
            else
            {
                ans[ p[i] ] = i- tall[ tree[ p[i] ] ];//记录答案：假设第i个出现的点距离根节点的距离就是i，那么，这条边的长度就等于  i-父节点[ p[i] ] (即：i-tall[ tree[ p[i] ] ])
                tall[ p[i] ] =i;
            }
        }
        if(flag)
        {
            for(int i=1;i<=n;i++) cout << ans[ i ] << " ";
            cout << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}

```


---

## 作者：Inui_Sana (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1611D)

~~一眼题，好像不至于绿？~~

既然给出最后到根距离排名，想到构造使排第 $i$ 的节点到根的距离为 $i-1$。这样就满足了排列的要求。

然后处理出答案：设一个点 $i$ 排名 $rk_i$，其父亲节点为 $fa_i$，因为 $i$ 到根节点距离 $rk_i-1$，$fa_i$ 到根节点距离 $rk_{fa_i}-1$，所以该节点到它父亲的边权为 $(rk_i-1)-(rk_{fa_i}-1)=rk_i-rk_{fa_i}$。

接下来就要尝试证明在这种构造中边权全为正。可以发现，除根节点外的节点的排名一定大于父亲节点的排名，否则边权就会出现负数，保证了边权为正，构造成立。

如果边权有负数，即任意一个 $rk_i-rk_{fa_i}<0$，则无解。

注意：根节点的父亲在输入中表示为它本身。

code：

```cpp
int n,rk[N],dep[N],ans[N];
bool flag;
int tot,head[N];struct node{int to,nxt;}e[N];
inline void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
void dfs(int u,int f){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)continue;
		ans[v]=rk[v]-rk[u];
		if(ans[v]<0)flag=false;
		dep[v]=dep[u]+ans[v];
		dfs(v,u);
	}
}
inline void init(){mems(ans,0),mems(dep,0),mems(head,0),tot=0;}
void solve(){
	init();
	scanf("%d",&n);
	int root;
	for(int v=1,u;v<=n;v++){
		scanf("%d",&u);
		if(u!=v)add(u,v);
		else root=v;
	}
	for(int i=1,x;i<=n;i++)scanf("%d",&x),rk[x]=i;
	flag=true,dfs(root,0);
	if(!flag){puts("-1");return;}
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	putchar('\n');
}
signed main(){
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1500}$

---
### 解题思路：

思维题。

先转换一下 $p_i$ 为每一个点的排名，设为 $r_i$，不妨强制让 $r_i$ 到根的距离为 $r_i$（或者称 $p_i$ 到根的距离为 $i$，两者等价）。

知道了每一个点到根的距离以后直接遍历一下树就可以判断了。

更具体地，有每一个点的到其子节点的距离等于两者到根节点的距离之差，如果出现负数则一定无解。

---
这一转化与原条件等价还是比较显然的，首先题目要求到根节点的距离严格递增，不能有相等的情况，而且如果到排列中的相邻两个点到根节点的距离之差的绝对值比 $1$ 更大，则一定有方法将其转换为 $1$ 并且保持合法，这一步转化是为了让问题更加形式化。

---

当然以上只是一个比较规范的做法，其实随便一个什么差不多的严格递增数列都可以作为到达根节点的距离，注意不要超过 $10^9$ 的上限就行了。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
const int MAXN=400005;
int n,T,head[MAXN],nxt[MAXN],num[MAXN],x,dep[MAXN],w[MAXN],tot,flag,root;
void add(int x,int y){
	nxt[++tot]=head[x];head[x]=tot;num[tot]=y;
}
void dfs(int now,int deep){
	w[now]=dep[now]-deep;
	for(int i=head[now];i;i=nxt[i])
	dfs(num[i],deep+w[now]);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			if(i!=x)add(x,i);
			else root=i;
		}
		for(int i=1;i<=n;i++)scanf("%d",&x),dep[x]=i;
		dfs(root,0);
		flag=1;
		for(int i=1;i<=n;i++)
		if(w[i]<0){
			printf("-1\n");
			flag=0;break;
		}
		if(flag){
			for(int i=1;i<=n;i++)
			printf("%d ",i==root?0:w[i]);
			printf("\n");
		}
		tot=0;
		for(int i=1;i<=tot;i++)nxt[i]=0,num[i]=0;
		for(int i=1;i<=n;i++)dep[i]=w[i]=0,head[i]=0;
	}
	return 0;
}
```

---

## 作者：Chivas_Regal (赞：1)

~~想半天以为这道题难点在找根...，然后发现我真是个憨憨~~  
  
# 找根
如果一个点的父节点是自己，那它就是根...（不会就我一个人这地方看半天吧  

# 检查  
由于 $p[]$ 表示先后顺序，我们设 $p'[i]$ 表示 $i$ 是 $p[]$ 中第几个  

```cpp
int pr[N];
int rp[N];
for ( int i = 1; i <= n; i ++ ) 
		scanf("%d", &pr[i]),
		rp[pr[i]] = i;
```

一条链上的 $dis[]$ 必定越来越大， $p'[]$ 同样    
那么可以知道的是，如果一堆父子关系中，$p'[$ 父节点 $]\gt p'[$ 子节点 $]$ 那么一定不行   
这个跑一遍点就可以实现了，也要在输入 $b[]$ 的时候记录一下父子关系 

**记录**
```cpp
for ( int i = 1, x; i <= n; i ++ ) {
		scanf("%d", &x); b[i] = { x, i };
}
```

**检查**
```cpp
inline bool check() {
        for ( int i = 1; i <= n; i ++ ) {
                if ( rp[b[i].first] > rp[b[i].second] ) return false;
        }
        return true;
}

if ( !check() ) { printf("-1\n"); return;};
```

# 边权  
我们不想影响他们的先后顺序  
那么可以让 $dis[i]=p'[i]$  
这样的话一条边 $(fath\rightarrow son)$ 的边权就是 $p'[fath]-p'[son]$   

```cpp
for ( int i = 1; i <= n; i ++ ) {
		printf("%d ", rp[b[i].second] - rp[b[i].first]);
} printf("\n");
```

# 完整代码

```cpp
#include <iostream>
#include <queue>

#define ll long long

using namespace std;

const int N = 2e5 + 10;

int n;
pair<int, int> b[N]; // first: fath, second: son
int pr[N]; // 正p数组
int rp[N]; // 反p数组

inline bool check() {
        for ( int i = 1; i <= n; i ++ ) {
                if ( rp[b[i].first] > rp[b[i].second] ) return false;
        }
        return true;
}

inline void Solve () {

        scanf("%d", &n);
        for ( int i = 1, x; i <= n; i ++ ) {
                scanf("%d", &x); b[i] = { x, i };
        }
        for ( int i = 1; i <= n; i ++ ) 
                scanf("%d", &pr[i]),
                rp[pr[i]] = i;

        if ( !check() ) { printf("-1\n"); return;};

        for ( int i = 1; i <= n; i ++ ) {
                printf("%d ", rp[b[i].second] - rp[b[i].first]);
        } printf("\n");
        
}


int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve ();
        }
}
```

---

## 作者：智子 (赞：0)

## 题意

输入一棵 $n$ 个节点的有根树和一个排列 $p$，你需要给树上的每条边赋予一个权值，使得每个 $p_{i - 1}$ 到根结点的距离小于 $p_i$ 到根结点的距离。

## 思路

因为题目要求每个 $p_{i - 1}$ 到根结点的距离小于 $p_i$ 到根结点的距离，不妨令 $p_i$ 到根结点的距离为 $i - 1$，设为 $dis_{p_i}$，那么 $w_i$ 就等于 $dis_{p_i} - dis_{p_{fa_i}}$。

然后就需要判断无解。如果我们需要计算 $p_i$ 的答案时，$p_i$ 的父节点的答案还没被算出来，则可以直接判断为无解。另外，如果第一个 $p_1$ 不是根结点，显然无解，因为距离根结点最近的节点显然就是根结点本身，不可能是其他节点。

## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int MAXN = 200000 + 5;

vector<int> G[MAXN];
int fa[MAXN], pos[MAXN], ans[MAXN], dis[MAXN];
int n, rt;

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &fa[i]);
            G[i].clear();
        }
        rt = 0;
        for(int i = 1; i <= n; i++) {
            if(fa[i] == i) {
                rt = i;
                continue;
            }
            G[fa[i]].push_back(i);
        }
        for(int i = 1; i <= n; i++) {
            scanf("%d", &pos[i]);
        }
        int flag = 1;
        memset(ans, -1, sizeof(ans));
        memset(dis, 0, sizeof(dis));
        ans[rt] = 0;
        for(int i = 1; i <= n; i++) {
            if(ans[fa[pos[i]]] == -1) {
                flag = 0;
                break;
            }
            if(pos[i] == rt) {
                continue;
            }
            dis[pos[i]] = dis[pos[i - 1]] + 1;
            ans[pos[i]] = dis[pos[i]] - dis[fa[pos[i]]];
        }
        if(!flag || pos[1] != rt) {
            printf("-1\n");
            continue;
        }
        for(int i = 1; i <= n; i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }

    return 0;
}

```

---

