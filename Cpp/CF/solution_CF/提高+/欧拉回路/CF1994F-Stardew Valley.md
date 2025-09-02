# Stardew Valley

## 题目描述

Pelican Town 有 $n$ 个房屋，通过 $m$ 条双向道路相连。有些道路上站着 NPC。农夫 Buba 需要走过每一条有 NPC 的道路，并与他们交谈。

请帮助农夫找到一条满足以下条件的路线：

- 路线从某个房屋出发，沿着道路行走，最终回到同一个房屋。
- 路线不会重复经过任何一条道路（无论方向）。
- 路线恰好经过每一条有 NPC 的道路一次。

注意，路线可以经过没有 NPC 的道路，并且不需要使路线最短。保证仅通过有 NPC 的道路可以从任意房屋到达任意其他房屋。

## 说明/提示

注意，在第三个测试用例中，存在多条 $(5, 2)$ 的重边。你必须分别走过这两条道路。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3 2
1 2 1
2 3 1
3 3
1 2 1
1 3 1
2 3 0
5 9
1 2 0
5 2 1
5 4 1
5 1 1
2 3 1
5 2 1
4 1 0
4 3 0
5 2 0```

### 输出

```
NO
YES
3
1 2 3 1 
YES
7
1 2 5 4 3 2 5 1```

# 题解

## 作者：ZhongYuLin (赞：9)

不难发现题目让我们求一条欧拉回路。但是，与一般题目不同，这道题存在**必经边**与**可行边**。于是，去考虑删去一些可行边，使得图构成一个欧拉回路。不妨先去除自环。

具体地，我们只走可行边，构造出 dfs 生成森林。每个节点回溯时，其父亲节点判断其度数是否为偶数。如果不为偶数，删去其父亲到它的边。这么构造，使得影响总是自生成树下而上的，避免了奇奇怪怪的后效性，使得我们不会漏掉成立的情况。

然后我们就可以在无向图上生成一条欧拉路径。类似于链表，我们可以使用链式前项星，额外记录每个节点的前驱，来方便地删去某一条边，再方便地删去其对边。使用指针可以避免判断前驱是头还是节点。同时，将当前节点没有前驱作为遍历终止条件，可以避免一些神秘的问题（例如访问空指针），这是因为不知道从哪里来，就不可能走向正确的方向。

```cpp
#include<bits/stdc++.h>
#define se second 
#define fi first
#define pii pair<int,int>
using namespace std;
const int N=5e5+3;
struct Edge{
    int nxt,to,w;
    int *frm;
}e[N<<1];
int head[N],dep[N],d[N],st[N],sum[N];
int tot=1,n,m,top;
bitset<N>vis;
void add(int u,int v,int w=0){
    e[++tot]={head[u],v,w,&head[u]};
    if(head[u])e[head[u]].frm=&e[tot].nxt;
    head[u]=tot;
}
void dlt(int i){
    *e[i].frm=e[i].nxt;
    if(e[i].nxt)e[e[i].nxt].frm=e[i].frm;
    e[i].frm=NULL;
}
void dfs(int x){
    vis[x]=1;
    for(int i=head[x];e[i].frm!=NULL;i=e[i].nxt){
        int y=e[i].to;
        if(vis[y]||e[i].w)continue;
        dfs(y);
        if(d[y]&1){
            dlt(i);dlt(i^1);
            --d[y];--d[x];
        }
    }
}
void work(int x){
    vis[x]=1;
    for(int i=head[x];e[i].frm!=NULL;i=e[i].nxt){
        int y=e[i].to;
        dlt(i);dlt(i^1);
        work(y);
    }
    st[++top]=x;
    for(;sum[x];--sum[x])st[++top]=x;
}
void solve(){
    int u,v,w,x,y,z;
    cin>>n>>m;tot=1;
    for(int i=1;i<=n;++i)sum[i]=vis[i]=d[i]=head[i]=0;
    for(int i=1;i<=m;++i){
        cin>>u>>v>>w;
        if(u==v){
            if(w)++sum[u];
            continue;
        }
        add(u,v,w);add(v,u,w);
        ++d[u];++d[v];
    }
    for(int x=1;x<=n;++x)
        if(!vis[x])dfs(x);
    for(int i=1;i<=n;++i)
        if(d[i]&1){puts("No");return;}
    vector<pii>E;
    for(int x=1;x<=n;++x)
        for(int i=head[x];i;i=e[i].nxt){
            int y=e[i].to;
            E.push_back({x,y});
            dlt(i);dlt(i^1);
        }
    for(int i=1;i<=n;++i)head[i]=0;tot=1;
    for(auto p:E)add(p.fi,p.se),add(p.se,p.fi);
    work(1);printf("Yes\n%d\n",top-1);
    while(top)printf("%d ",st[top--]);puts("");
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;for(cin>>T;T--;)solve();
    return 0;
}
```

---

## 作者：Disjoint_cat (赞：8)

# CF1994F

唉，没赶上上分场。（VP rk ~80）

## 题意

给定一张 $n$ 点 $m$ 边的无向图。你需要找到一个环，使得给定的一些边**恰好**经过一次，其他边**至多**经过一次。

$n,m\le5\times10^5$。**数据保证即使只保留必须经过的边，图仍是连通的。**

## 题解

首先题目可以转化为，你可以删除一些（不必须经过的）边，然后你需要找到一个欧拉回路。

而我们即使将所有不必经过的边都删除，图也是连通的。所以不需要考虑连通性，只要所有点度数为偶数即可。

考虑只由非必经边构成的子图的连通块。我们想把这个连通块内所有点的调成偶点。考虑它的 dfs 树，如果一个点是奇点就删掉它连向父亲的边。如果调完后根节点是奇点，说明整个连通块的奇点个数是奇数，而删一条边奇点数奇偶性不变，所以直接就寄了。

一切搞完之后跑个欧拉回路就行了。时间复杂度 $\Theta(n+m)$。

[赛时 submission](https://codeforces.com/contest/1994/submission/271871610)。

---

## 作者：刘梓轩2010 (赞：1)

题目传送门：

[luogu](https://www.luogu.com.cn/problem/CF1994F)

[CF1994F](https://codeforces.com/problemset/problem/1994/F)

## 题意

给你一张 $n$ 个点 $m$ 条边的图，上面有重要的和不重要的边，重要的边必须走，不重要的可走可不走，问你能不能构造出欧拉回路。

## 思路

首先，我们可以先把所有重要的边放到实际的图里，然后考虑加上某一些不重要的边，使得这张图上有欧拉回路。

让我们考虑如何构造。

首先，题目里已经保证了重要的边可以使得图联通，那么我们只用考虑度数的问题。我们只把不重要的边拿出来，我们发现，在一个连通块内，如果有奇数个奇度点，那么无论如何加边，我们都无法使得这张图满足条件，因为加边后奇度点的个数一定是 $+2$ 或者 $-2$ 的关系。

否则，贪心的加边，用不重要的边去跑出一个生成树森林，如果一个点是奇度点，那么就在实际的图上加上这个点到它父亲的边。到最后，如果根节点的度数是奇数，此时所有的非根节点都已经是偶度点了，说明原来这个连通块就有奇数个奇度点，说明没有合法方案。

最后，在实际图上跑出欧拉回路即可。

对于一组数据，时间复杂度是 $O(n+m)$，可以通过。

温馨提示，用 vector 存图跑欧拉回路时千万不能用 auto，否则每次遍历点的时候都会从 vector 的开头开始跑，会 TLE。

## Code
```c++
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define fi first
#define se second
using namespace std;
const int N=5e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
struct Node
{
    int v,id;
};
stack<int> st;
int t;
int n,m;
vector<Node> G[N],el[N];//1边,0边 
int deg[N];
bool vis[N];//点 
bool del[N];//边 
int cnt;
void dfs(int u)
{
    vis[u]=1;
    for(auto x:el[u])
    {
        int v=x.v;
        int id=x.id;
        if(vis[v]) continue;
        dfs(v);
        if(deg[v])
        {
            G[u].push_back({v,id});
            G[v].push_back({u,id});
            deg[u]^=1;
            deg[v]^=1;
            cnt++;
        }
    }
}
int ne[N];
void euler(int u)
{
    for(int i=ne[u];i<G[u].size();i=ne[u])
    {
        ne[u]=i+1;
        int v=G[u][i].v;
        int id=G[u][i].id;
        if(del[id]) continue;
        del[id]=1;
        euler(v);
    }
    st.push(u);
}
signed main()
{
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--)
	{
	    cin>>n>>m;
	    for(int i=1;i<=n;i++)
	    {
	        ne[i]=deg[i]=vis[i]=0;
	        G[i].clear();
	        el[i].clear();
        }
        for(int i=1;i<=m;i++) del[i]=0;
	    cnt=0;
	    for(int i=1;i<=m;i++)
	    {
	        int u,v,c;
	        cin>>u>>v>>c;
	        if(c)
	        {
	            G[u].push_back({v,i});
	            G[v].push_back({u,i});
	            deg[u]^=1;
	            deg[v]^=1;
	            cnt++;
            }
            else
            {
                el[u].push_back({v,i});
                el[v].push_back({u,i});
            }
        }
        bool fl=1;
        for(int i=1;i<=n;i++)
        {
            if(!vis[i])
            {
                dfs(i);
                if(deg[i])
                {
                    fl=0;
                    break;
                }
            }
        }
        if(!fl)
        {
            cout<<"NO"<<endl;
            continue;
        }
        cout<<"YES"<<endl<<cnt<<endl;
        euler(1);
        while(!st.empty())
        {
            cout<<st.top()<<" ";
            st.pop();
        }
        cout<<endl;
    }
    return 0;
}
```

---

