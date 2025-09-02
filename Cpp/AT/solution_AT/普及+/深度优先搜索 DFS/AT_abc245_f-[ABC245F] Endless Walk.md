# [ABC245F] Endless Walk

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc245/tasks/abc245_f

$ N $ 頂点 $ M $ 辺からなる単純な有向グラフ $ G $ があり、頂点には頂点 $ 1 $, 頂点 $ 2 $, $ \ldots $, 頂点 $ N $ と番号がついています。 また、$ i $ $ (1\leq\ i\leq\ M) $ 本目の辺は頂点 $ U_i $ から頂点 $ V_i $ へ張られています。

高橋君がある頂点から始めて、$ G $ の上を有向辺に沿って頂点から頂点へ移動することを繰り返します。 $ G $ の頂点のうち、高橋君がうまく経路を選ぶことで、その頂点から始めていくらでも移動を繰り返すことができるようなものの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min(N(N-1),\ 2\times\ 10^5) $
- $ 1\ \leq\ U_i,V_i\leq\ N $
- $ U_i\neq\ V_i $
- $ i\neq\ j $ ならば $ (U_i,V_i)\neq\ (U_j,V_j) $
- 入力はすべて整数である。

### Sample Explanation 1

頂点 $ 2 $ を始点とした場合、頂点 $ 2 $ $ \to $ 頂点 $ 3 $ $ \to $ 頂点 $ 4 $ $ \to $ 頂点 $ 2 $ $ \to $ 頂点 $ 3 $ $ \to $ $ \cdots $ と高橋君はいくらでも移動を繰り返す事ができます。 頂点 $ 3 $, 頂点 $ 4 $ を始点とした場合も同様です。 頂点 $ 1 $ からは最初に頂点 $ 2 $ に移動して、以下同様にいくらでも行動を繰り返すことができます。 一方、頂点 $ 5 $ からは一度も移動することができません。 よって、条件を満たすのは頂点 $ 1 $, $ 2 $, $ 3 $, $ 4 $ の $ 4 $ つであるので、 $ 4 $ を出力します。

### Sample Explanation 2

単純な有向グラフにおいて、$ 2 $ つの頂点の間を互いに逆向きに結ぶ辺が、ともに存在する事はあり得ることに注意してください。 また、$ G $ は連結であるとは限りません。

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 4
4 2
4 5```

### 输出

```
4```

## 样例 #2

### 输入

```
3 2
1 2
2 1```

### 输出

```
2```

# 题解

## 作者：iiiiiyang (赞：6)

[更好的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/16888933.html)

[题目链接](https://www.luogu.com.cn/problem/AT_abc245_f)

本题解适合像我这样的不具备思维能力的选手。

首先根据题意，一个点如果符合要求，那它必然在一个点数大于 $2$ 的强联通分量里，因为如果只有一个点它就哪里都去不了。所以首先先对图进行缩点，顺带记录下每个强连通分量的大小。然后如果一个点它可以走入这个强连通分量里，就也是符合条件的，所以在缩点后的新图上反向建边，遍历一遍看看符合条件的强连通分量可以走到哪些点，最后看哪些被打上标记即可。

$Code$
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
    int s=0,w=1; char c=getchar();
    while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
    while(isdigit(c)) s=(s<<3)+(s<<1)+(c^48),c=getchar();
    return s*w;
}

namespace LgxTpre
{
    static const int MAX = 2000010;
    static const int INF = 20070707070707;

    int n,m;
    int x,y;

    struct Graph
    {
        struct edge
        {
            int nex,to;
        }e[MAX<<1];
        int head[MAX],cnt;
        inline void add(int x,int y)
        {
            e[++cnt].nex=head[x];
            head[x]=cnt;
            e[cnt].to=y;
            return;
        }
    }G1,G2;

    int dfn[MAX],low[MAX],tot;
    int stk[MAX],top;
    int sizcol[MAX],col[MAX],num;
    int vis[MAX];
    void tarjan(int now)
    {
        dfn[now]=low[now]=++tot;
        stk[++top]=now;
        vis[now]=1;
        for(int i=G1.head[now];i;i=G1.e[i].nex)
        {
            int to=G1.e[i].to;
            if(!dfn[to]) 
                tarjan(to),
                low[now]=min(low[now],low[to]);
            else    
                if(vis[to])
                    low[now]=min(low[now],dfn[to]);
        }
        if(low[now]==dfn[now])
        {
            vis[now]=0;
            col[now]=++num;
            ++sizcol[num];
            while(stk[top]!=now) col[stk[top]]=num,++sizcol[num],vis[stk[top]]=0,--top;
            --top;
        }
        return;
    }

    int deg[MAX],flag[MAX],ans;
    inline void dfs(int now)
    {
        flag[now]=1;
        for(int i=G2.head[now];i;i=G2.e[i].nex)
        {
            int to=G2.e[i].to;
            if(!flag[to]) dfs(to);
        }
        return;
    }

    inline void lmy_forever()
    {
        n=read(),m=read();
        for(int i=1;i<=m;++i)
            x=read(),y=read(),G1.add(x,y);
        for(int i=1;i<=n;++i)
            if(!dfn[i])
                tarjan(i);
        for(int i=1;i<=n;++i)
            for(int j=G1.head[i],to;j;j=G1.e[j].nex)
                if(col[i]!=col[to=G1.e[j].to])
                    ++deg[i],G2.add(col[to],col[i]);
        for(int i=1;i<=num;++i)
            if(sizcol[i]>=2)
                dfs(i);
        for(int i=1;i<=num;++i)
            if(flag[i])
                ans+=sizcol[i];
        cout<<ans;
    }
};

signed main()
{
    LgxTpre::lmy_forever();
    return (0-0);
}
```

---

## 作者：loser_seele (赞：4)

题意：问给定的有向图中有多少个顶点，从这个点出发可以经过无数条路径。

首先考虑原图中出度为 $ 0 $ 的顶点显然不满足条件。

然后每次删除这样的点之后更新到达它的点的度数，如果出现新的点出度为 $ 0 $ 则继续更新。

所以问题实际上转化为了一个拓扑排序，每次将出度为 $ 0 $ 的点入队并更新其前继的出度，因为更新出度不好操作于是反向建边改为统计入度即可。

每个元素最多入队一次，所以时间复杂度为 $ \mathcal{O}(n+m) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
vector<int>g[maxn];
int vis[maxn],in[maxn];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        g[y].push_back(x);
        in[x]++;
    }
    queue<int>q;
    for(int i=1;i<=n;i++)
    {
        if(!in[i]) 
        q.push(i),vis[i]=1;
    }
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        for(auto &v:g[t])
        {
            in[v]--;
            if(!in[v]) 
            q.push(v),vis[v]=1;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++) 
    ans+=!vis[i];
    cout<<ans;
}
```


---

## 作者：Demons_Killer (赞：0)

# 解题思路
找到每个点的出度，如果该节点所有连接的节点均不连通，那么这个节点也不联通。加边时要反向加边，因为我们要遍历指向该节点的边，对所有不能作为联通点的进行广搜，每次对它的出度减少，当它无点可连时，就对这个点进行标记，最后没被标记的点的个数就是我们的答案。

# code：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+10;
int n,m;
int e[N],ne[N],h[N],idx;
int r[N],c[N];
bool vis[N],Vis[N];
int ans;
int mx;
//map<int,int> mp;
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}
queue<int> q;
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	memset(h,-1,sizeof(h));
	cin>>n>>m;
	int u,v;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		add(v,u);
		r[u]++;
	}
	for(int i=1;i<=n;i++){
		if(!r[i]){
			q.push(i);
			vis[i]=true;
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=h[u];i!=-1;i=ne[i]){
			int j=e[i];
			r[j]--;
			if(!r[j]){
				q.push(j);
				vis[j]=true;
			}
		}
	}
	ans=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]) ans++;
	}	
	cout<<ans<<endl;
	return 0;
}
/*
5 6
2 3
1 2
2 4
4 3
3 5
5 1
*/
```

---

## 作者：AlicX (赞：0)

## Solution 

首先发现一个环内的点一定可以无限走，继续推导可以发现，可以走进环内的点一定也可以无限走。所以先缩点，然后倒着跑一遍拓扑排序，用环去走不是环的点，最后统计出有多少个环和多少个点就可以了。

```cpp

#include<bits/stdc++.h> 
//#define int long long 
#define x first 
#define y second 
#define il inline 
#define pb(x) push_back(x) 
#define debug() puts("-------") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=2e5+10; 
int n,m; 
int d[N]; 
int siz[N];  
bool st[N]; 
int times=0; 
int h[N],idx=0;
int s[N],top=0; 
int id[N],cnt=0; 
int he[N],idxe=0;  
int dfn[N],low[N]; 
struct Node{ 
	int to,ne; 
}tr[N],tre[N]; 
il void add(int u,int v){ 
	tr[idx].to=v,tr[idx].ne=h[u],h[u]=idx++; 
} 
il void adde(int u,int v){ 
	tre[idxe].to=v,tre[idxe].ne=he[u],he[u]=idxe++; 
} 
il void dfs(int u){ 
	dfn[u]=low[u]=++times; 
	s[++top]=u; st[u]=true; 
	for(int i=h[u];i!=-1;i=tr[i].ne){
		int to=tr[i].to; 
		if(!dfn[to]) dfs(to),low[u]=min(low[u],low[to]); 
		else if(st[to]) low[u]=min(low[u],dfn[to]); 
	} if(dfn[u]==low[u]){ 
		int key; cnt++; 
		do{ 
			key=s[top--]; siz[cnt]++; 
			id[key]=cnt; st[key]=false; 
		}while(key!=u); 
	} 
} 
il void work(){ queue<int> q; 
	memset(st,false,sizeof st); int ans=0;  
	for(int i=1;i<=cnt;i++) if(siz[i]>1) st[i]=true; 
	for(int u=1;u<=n;u++){ 
		for(int i=h[u];i!=-1;i=tr[i].ne){ 
			int to=tr[i].to; 
			if(id[u]==id[to]) continue; 
			adde(id[to],id[u]); d[id[u]]++; 
		} 
	} for(int i=1;i<=cnt;i++) if(!d[i]) q.push(i); 
	while(!q.empty()){ 
		int u=q.front(); q.pop(); 
		for(int i=he[u];i!=-1;i=tre[i].ne){
			int to=tre[i].to; 
			d[to]--,st[to]|=st[u];  
			if(!d[to]) q.push(to); 
		} 
	} for(int i=1;i<=cnt;i++) if(st[i]) ans+=siz[i]; printf("%d\n",ans); 
} 
signed main(){ 
//	freopen("endless.in","r",stdin); 
//	freopen("endless.out","w",stdout); 
	memset(h,-1,sizeof h); 
	memset(he,-1,sizeof he);  
	scanf("%d%d",&n,&m); 
	while(m--){ 
		int u,v; 
		scanf("%d%d",&u,&v); add(u,v);  
	} for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i); work();     
	return 0; 
} /*
5 5
1 2
2 3
3 4
4 2
4 5

3 2
1 2
2 1

8 9 
5 1 
1 3 
7 3
4 1 
3 4
4 6 
4 8
7 5
6 7
*/

```


---

