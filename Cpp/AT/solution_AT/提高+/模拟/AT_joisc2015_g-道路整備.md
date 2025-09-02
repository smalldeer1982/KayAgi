# 道路整備

## 题目描述

## JOISC2015 Day2T3 道路整备


给定一个$N$个点的森林，初始森林上没有边。接下来进行$Q$次操作，操作有以下两种：

$1\ u\ v$：如果当前$u\ v$不连通，则在森林上添加一条边$(u,v)$，边权为$1$；否则将森林中路径$(u,v)$上的所有边的边权赋为$0$。

$2\ u\ v$：询问此时森林上$(u,v)$对应的路径的边权和。

## 说明/提示

$1 \leq N \leq 10^5$

$1 \leq Q \leq 3 \times 10^5$

$type \in \{1,2\} , 1 \leq u,v \leq N , u \neq v$

### 样例

#### 样例输入1

```
3 7
1 1 2
2 2 1
2 2 3
1 2 1
2 1 2
1 2 3
2 1 3
```

#### 样例输出1

```
1
-1
0
1
```

#### 样例输入2

```
6 8
1 1 3
1 6 1
1 2 5
2 3 6
1 3 6
1 4 1
2 4 3
2 2 5
```

#### 样例输出2

```
2
1
1
```

#### 样例输入3

```
7 11
1 5 1
1 6 2
1 1 3
1 3 5
1 5 7
1 4 5
1 4 1
2 1 3
2 3 7
2 4 3
2 5 6
```

#### 样例输出3

```
0
1
0
-1
```

# 题解

## 作者：Let_Fly (赞：1)

#  ATjoisc2015g 道路整備

思路：看到修改树上一段边，首先想到树链剖分，但是有一个问题困扰了我们，
那就是它会动态地加一些边。不过可以发现只加不减，故可以把所有修改离线下来。用并查集记录当前操作时是否联通就行了。代码里有注释。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=4e5+5;
//
int n,q;
vector<int> to[N];
bool vis[N];
//
int p[N];
int find(int x){//并查集判断联通性
    if(x!=p[x])p[x]=find(p[x]);
    return p[x];
}
//
int cnt;//树剖基操
int top[N],fa[N],son[N],sz[N],id[N],dep[N];
void dfs1(int u,int f){
    fa[u]=f;
    sz[u]=1;
    dep[u]=dep[f]+1;
    for(int v:to[u]){
        if(v==f)continue;
        dfs1(v,u);
        sz[u]+=sz[v];
		if(sz[son[u]]<sz[v])son[u]=v;
    }
}
void dfs2(int u,int t){
    id[u]=++cnt;
    top[u]=t;
    if(!son[u])return;
    dfs2(son[u],t);
    for(int v:to[u]){
        if(v==fa[u]||v==son[u])continue;
        dfs2(v,v);
    }
}
//线段树部分
int sum[N<<4],tag[N<<4];//有tag就是要修改为0
void pushup(int u){
    sum[u]=sum[u<<1]+sum[u<<1|1];
}
void pushdown(int u,int l,int r){
    if(tag[u]){
        tag[u]=0;
        sum[u<<1]=0;
        sum[u<<1|1]=0;
        tag[u<<1]=1;
        tag[u<<1|1]=1;
    }
}
void build(int u,int l,int r){
    if(l==r){
        sum[u]=1;
        tag[u]=0;
        return;
    }
    int mid=l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    pushup(u);
}
void update(int u,int l,int r,int cl,int cr){
    if(cl<=l&&r<=cr){
        tag[u]=1;
        sum[u]=0;
        return;
    }
    pushdown(u,l,r);
    int mid=l+r>>1;
    if(cl<=mid)update(u<<1,l,mid,cl,cr);
    if(cr>mid)update(u<<1|1,mid+1,r,cl,cr);
    pushup(u);
}
int query(int u,int l,int r,int cl,int cr){
    if(cl<=l&&r<=cr){
        return sum[u];
    }
    int mid=l+r>>1;
    pushdown(u,l,r);
    int res=0;
    if(cl<=mid)res+=query(u<<1,l,mid,cl,cr);
    if(cr>mid)res+=query(u<<1|1,mid+1,r,cl,cr);
    return res;
}
//树剖
int qr(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=query(1,1,n,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans+=query(1,1,n,id[x]+1,id[y]);
	return ans;
}
void ud(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		update(1,1,n,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	update(1,1,n,id[x]+1,id[y]);
}
//离线操作
struct Cz{
    int bh,u,v;
}cz[N];
int czcnt;
//

int main(){
    cin>>n>>q;
    n++;//超级根占用了编号
    for(int i=1;i<=n;i++)p[i]=i;
    for(int i=1;i<=q;i++){
        int op,u,v;
        cin>>op>>u>>v;
        u++,v++;
        int k=find(u),l=find(v);
        if(op==1){
            if(k==l){//如果联通
                cz[++czcnt]={1,u,v};//那么这是一次修改
            }else{
                to[u].push_back(v);
                to[v].push_back(u);
                p[k]=l;//否则加边
            }
        }else{
            if(k==l){//如果联通
                cz[++czcnt]={2,u,v};//那么这是一次有效查询
            }else{
                cz[++czcnt]={-1,0,0};//直接是负一
            }
        }
    }
    for(int i=2;i<=n;i++){//由于树剖时可能是森林，所以要连一个超级根
        int ff=find(i);
        if(!vis[ff]){
            to[1].push_back(ff);
            vis[ff]=1;
        }
    }
    dfs1(1,0);
    dfs2(1,0);
    build(1,1,n);
    for(int i=1;i<=czcnt;i++){//操作
        auto g=cz[i];
        if(g.bh==1){
            ud(g.u,g.v);
        }else if(g.bh==2){
            cout<<qr(g.u,g.v)<<'\n';
        }else{
            cout<<g.bh<<'\n';
        }
    }
    return 0;
}
```


---

## 作者：Unnamed114514 (赞：0)

这个 joker 莽了 1.5h 的在线做法，以开摆告终。

如果不是动态加边的话，就是树剖的板子。

发现在线做法不是很好做，遂考虑离线。

这样树的形态就是固定的了，用并查集判断连通性，剩下的直接树剖即可。

---

