# [NWRRC 2017] Grand Test

## 题目描述

给定一张 $n$ 个节点 $m$ 条边的无向图，请在图中找出两个点 $S$ 和 $F$，使得这两点间至少存在三条不相交的路径。

## 样例 #1

### 输入

```
2
6 6
3 6
3 4
1 4
1 2
1 3
2 3
3 1
1 2
```

### 输出

```
1 3
3 1 2 3
2 1 3
3 1 4 3
-1
```

# 题解

## 作者：agicy (赞：5)

本文将同步发布于：

- [洛谷博客](https://www.luogu.com.cn/blog/Lu-Anlai/solution-p7025)；
- [csdn](https://blog.csdn.net/Lu_Anlai/article/details/117371460)；
- [博客园](https://www.cnblogs.com/Lu-Anlai/p/14823507.html)；
- [简书](https://www.jianshu.com/p/98bfd4cf8c73)。

## 题目

题目链接：[洛谷 P7025](https://www.luogu.com.cn/problem/P7025)、[gym101612G](https://codeforces.com/gym/101612/problem/G)。

### 题意概述

给你一张有 $n$ 个点 $m$ 条边的无向图，无重边无自环，请你求出两个点 $s,t$ 使得 $s,t$ 之间有三条不重合的简单路径。

$1\leq\sum n,\sum m\leq 10^5$

## 题解

### 探究图的性质

考虑到本题是无向图，我们不难想到一个引理。

> 引理：无向图的 dfs 树上只存在树边和返祖边。

考虑到 dfs 树中只会存在树边、返祖边、横叉边，因此我们只需要证明无向图的 dfs 树上不存在横叉边即可。

考虑反证法。

假设存在一条横叉边 $(u,v)$，目前遍历到 $u$，$v$ 在之前被访问过，根据横叉边的定义，$v$ 不是 $u$ 的祖先。

根据深度优先搜索的深度优先原则，此时一定访问完了所有与 $v$ 相连的节点，但 $u$ 却未被访问到，造成矛盾，假设不成立，引理得证。

### 利用性质构造方案

考虑到 dfs 树上只有额外的返祖边，我们不难构造出一种方案。

对于一个点 $u$，如果它的两棵子树内存在两个节点 $x,y$ 使得有两条返祖边 $(x,p_1),(y,p_2)$ 满足 $p_1,p_2$ 是节点 $u$ 的祖先，则 $s=p_1,t=u$ 符合条件。

画成图长下面这样：

![gym101612G.png](https://i.loli.net/2021/05/28/GaVfW4ClTNogy96.png)

充分性十分显然，下面我们考虑证明必要性。即不存在上述情况，也有满足条件的三条路径和两个节点。

不难发现这是不可能的，因为只要存在起点与终点，它们在 dfs 树上必然是祖先关系，因此一定满足上述情况，矛盾。

因此我们证明了这个条件的充分必要性，用 tarjan 算法判定即可。时间复杂度 $\Theta(n)$。

### 参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;

int n,m;
vector<int> G[MAXN];
int fa[MAXN];
int tim,dfn[MAXN],rnk[MAXN],low[MAXN],ed[MAXN],clow[MAXN],ced[MAXN];
int s,t;

inline void tarjan(reg int u,reg int father){
	fa[u]=father;
	dfn[u]=low[u]=clow[u]=++tim;
	rnk[tim]=u;
	ed[u]=ced[u]=u;
	for(int v:G[u])
		if(v!=father){
			if(!dfn[v]){
				tarjan(v,u);
				if(low[v]<low[u]){
					clow[u]=low[u],ced[u]=ed[u];
					low[u]=low[v],ed[u]=ed[v];
				}
				else if(low[v]<clow[u])
					clow[u]=low[v],ced[u]=ed[v];
			}
			else{
				if(dfn[v]<low[u]){
					clow[u]=low[u],ced[u]=ed[u];
					low[u]=dfn[v],ed[u]=u;
				}
				else if(dfn[v]<clow[u])
					clow[u]=dfn[v],ced[u]=u;
			}
		}
	if(!s&&!t&&clow[u]<dfn[u])
		s=u,t=rnk[clow[u]];
	return;
}

inline vector<int> getPath(reg int son,int father){
	vector<int> res;
	for(int p=son;p!=father;p=fa[p])
		res.push_back(p);
	res.push_back(father);
	return res;
}

inline vector<int> reverse(vector<int> a){
	reverse(a.begin(),a.end());
	return a;
}

inline vector<int> merge(vector<int> a,vector<int> b){
	a.insert(a.end(),b.begin(),b.end());
	return a;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),m=read();
		for(reg int i=1;i<=n;++i)
			G[i].clear();
		for(reg int i=1;i<=m;++i){
			static int u,v;
			u=read(),v=read();
			G[u].push_back(v),G[v].push_back(u);
		}
		tim=0,fill(dfn+1,dfn+n+1,0);
		s=0,t=0;
		for(reg int i=1;i<=n;++i)
			if(!dfn[i])
				tarjan(i,0);
		if(!s&&!t)
			write(-1),putchar('\n');
		else{
			write(s),putchar(' '),write(t),putchar('\n');
			vector<int> ans1=getPath(s,t);
			write(ans1.size()),putchar(' ');
			for(reg int i=0,siz=ans1.size();i<siz;++i)
				write(ans1[i]),putchar(i==siz-1?'\n':' ');
			vector<int> ans2=merge(reverse(getPath(ed[s],s)),reverse(getPath(t,rnk[low[s]])));
			write(ans2.size()),putchar(' ');
			for(reg int i=0,siz=ans2.size();i<siz;++i)
				write(ans2[i]),putchar(i==siz-1?'\n':' ');
			vector<int> ans3=merge(reverse(getPath(ced[s],s)),getPath(rnk[clow[s]],rnk[clow[s]]));
			write(ans3.size()),putchar(' ');
			for(reg int i=0,siz=ans3.size();i<siz;++i)
				write(ans3[i]),putchar(i==siz-1?'\n':' ');
		}
	}
	flush();
	return 0;
}
```


---

## 作者：zcz0263 (赞：2)

## 题意
有一张无向图，让你找出任意一对点对 $(u,v)$ 以及 $u\rightarrow v$ 的三条简单路径，使得这三条路径经过的非 $u,v$ 点没有交集，找不到输出 $-1$。

## 做法
放到 DFS 树上考虑，使用 Tarjan 算法，在原本 Tarjan 算法的基础上做修改。 
- 定义
  - $subtree_u$：表示 DFS 树中以 $u$ 为根的子树。
  - $fa_u$：表示 DFS 树中 $u$ 点的父亲结点。
  - $rnk_x$：表示 dfn 序为 $x$ 的点。
  - $low_1[u]$：表示 $subtree_u$ 中不直接走向 $fa_u$ 可以直接到达的最小 dfn 序。即原算法中的 $low$。
  - $ed_1[u]$：表示 $subtree_u$ 中更新 $low_1[u]$ 的点。
  - $low_2[u]$：表示 $subtree_u$ 中不通过 $ed_1[u]$ 所在的以 $u$ 的儿子为根的子树，且不直接走向 $fa_u$ 可以直接到达的最小 dfn 序。
  - $ed_2[u]$：表示 $subtree_u$ 中更新 $low_2[u]$ 的点。

我们分类讨论在什么情况下才会有满足题目要求的 $(u,v)$ ： 

  
- 情况 $1$：$lc=u$ 或 $lc=v$：  
    将 $ed_1[u]$ 记作 $x$，$ed_2[u]$ 记作 $y$，$rnk_{low_1[u]}$ 记作 $p_1$，$rnk_{low_2[u]}$ 记作 $p_2$，$lca(u,v)$ 记作 $lc$。
  
    
  先假设一种情况：  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/jii9k13r.png)
  
  此时 $p_2$ 即为一个与 $u$ 配对的合法的 $v$，三条道路分别为 $u\rightarrow p_2$、$u\rightarrow x\rightarrow p_2$、$u\rightarrow y\rightarrow p_1\rightarrow p_2$，不难看出在这种情况下，只有图中的构造才有可能使 $v$ 为 $u$ 的祖先（或考虑连向的 dfn 序更大的返祖边，但一定被图中构造包括）。反之亦然。  

- 情况 $2$：$lc\not=v$ 且 $lc\not=u$：  
  将 $rnk_{low_1[u]}$ 记作 $p$，$rnk_{low_1[v]}$ 记作 $q$，$lca(u,v)$ 记作 $lc$。

  我们先假设一组 $u,v$ 并尝试构造至满足条件：  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/rm0apuef.png)  
  根据无向图的 DFS 树没有横叉边的性质，只能从 $u$ 或 $v$ 向 $lc$ 以上的点建返祖边才可能满足条件。

  建边后，以 $p$ 更深的构造为例（其他方式同理）：  
    ![](https://cdn.luogu.com.cn/upload/image_hosting/m2o8pkyr.png)

    此时 $lc$ 和 $p$ 的关系满足情况 $1$，所以这种情况不需要考虑。 

最后发现我们只需要在 $x$ 点的 tarjan 结束后判断是否存在 $low_2[x]$ 即可，如果有，则 $(x,low_1[x])$ 为一组解。 
  
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define bi basic_string<int>
#define vvi vector<vi>
#define pb push_back
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define all(x) x.begin(),x.end()
int _;
void solve();
main(){
    ios::sync_with_stdio(0),cin.tie(nullptr);
    for(cin>>_;_--;solve());
}
void solve(){
    int n,m;
    cin>>n>>m;
    int dnt=0,s=0,t=0;
    vvi g(n+5);
    vi dfn(n+5),low1(n+5),low2(n+5),ed1(n+5),ed2(n+5),fa(n+5),rnk(n+5);
    rep(i,1,m){
        int u,v;
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
    }
    auto tarjan=[&](int u,int f,auto&&self)->void {
        fa[u]=f;
        rnk[dfn[u]=low1[u]=low2[u]=++dnt]=u;
        ed1[u]=ed2[u]=u;
        for(int&v:g[u]){
            if(s|t) return;
            if(v==f) continue;
            if(!dfn[v]){
                self(v,u,self);
                if(low1[v]<low1[u]){
                    low2[u]=low1[u];
                    ed2[u]=ed1[u];
                    low1[u]=low1[v];
                    ed1[u]=ed1[v];
                }else if(low1[v]<low2[u]){
                    low2[u]=low1[v];
                    ed2[u]=ed1[v];
                }
            }else{
                if(dfn[v]<low1[u]){
                    low2[u]=low1[u];
                    ed2[u]=ed1[u];
                    low1[u]=dfn[v];
                    ed1[u]=u;
                }else if(dfn[v]<low2[u]){
                    low2[u]=dfn[v];
                    ed2[u]=u;
                }
            }
            if(low2[u]<dfn[u]) s=u,t=rnk[low2[u]];
        }
    };
    auto getpth=[&](int u,int v)->bi {
        bi res;
        for(;v^u;v=fa[v]) res+=v;
        res+=v;
        reverse(all(res));
        return res;
    };
    rep(i,1,n) if(!dfn[i]) tarjan(i,0,tarjan); 
    auto prt=[&](const auto&s)->void {
        cout<<s.size()<<" ";
        for(int i:s) cout<<i<<" ";
        cout<<"\n";
    };
    if(!(s|t)){
        cout<<"-1\n";
    }else{
        cout<<s<<" "<<t<<"\n";
        prt(getpth(t,s)|views::reverse);
        prt(getpth(s,ed1[s])+getpth(rnk[low1[s]],t));
        prt(getpth(s,ed2[s])+t);
    }
}
```
---
特别感谢：[@RailgunZzzz](https://www.luogu.com.cn/user/586905#article)

---

## 作者：toolong114514 (赞：1)

## 题面大意
给定一个 $n$ 点 $m$ 边的无向图，判断是否存在一对点 $S$ 和 $F$，使得从 $S$ 点出发有三条除 $S$ 和 $F$ 外没有任何相交的路径，并输出。多组测试数据。
## 解题思路
引理：无向图的 DFS 树没有横叉边。

证明：若一颗有横叉边的生成树为 DFS 树，那么两端点之一一定会沿这条边搜过去，消灭横叉边，存在矛盾，引理得证。

基于这一特殊的性质，不妨在原图上跑一个 DFS 生成树(有根)，并考虑原问题在 DFS 树上的性质。

对于一条返祖边 $(u,v)$，我们称 $(u,v)$ 覆盖了边 $(u',v')$，当且仅当边 $(u',v')$ 在生成树上从 $u$ 到 $v$ 的树链中。

当树上的一条边被两条返祖边覆盖，那么存在这样的路径。

我们分别记两条返祖边为 $(u_1,v_1),(u_2,v_2)$。

不妨设 $u_1$ 的深度小于 $v_1$，$u_2,v_2$ 同理，且 $u_1$ 深度小于 $u_2$。

接下来定义 $lca(v_1,v_2)$ 为 $v_1,v_2$ 的 LCA。

观察样例不难得出，存在的三条路径，一定构成形如一个简单环中加了一条链的子图。

那么根据上面的描述，我们可以得到一个环：

从 $lca(v_1,v_2)$ 到 $u_1$，再到 $u_2$，下到 $v_2$，最后返回 $lca(v_1,v_2)$。

同时环中间加了一条从 $lca(v_1,v_2)$ 到 $u_2$ 的链。

这与我们观察三条路径得到的性质相同。

于是，“当树上的一条边被两条返祖边覆盖，那么存在这样的路径”得证，同时我们也确定了三条路径上的点。

共同起点为 $lca(v_1,v_2)$，共同重点为 $u_2$。

三条路径分别如下：

- 从 $lca(v_1,v_2)$ 沿树边跳到 $u_2$。

- 从 $lca(v_1,v_2)$ 沿树边下到 $v_1$，沿返祖边到 $u_1$，再沿树边下到 $u_2$。

- 从 $lca(v_1,v_2)$ 沿树边下到 $v_2$，沿返祖边到 $u_2$。

这样就做完了，输出答案即可。

时间复杂度 $O(n+m)$，可以通过本题。

双倍经验：[CF521E](/problem/CF521E)
## 参考代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int N=1e6+10;
struct node{
	int to,nxt;
}edge[N];
int head[N];
int cnt;
void add(int u,int v){
	edge[++cnt]={v,head[u]};
	head[u]=cnt;
}
int fa[N],tu[N],tv[N],dep[N];
bool vst[N],used[N];
struct ccf{
	int l,r;
};
int get_lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	while(dep[x]>dep[y]) x=fa[x];
	if(x==y) return x;
	while(x!=y) x=fa[x],y=fa[y];
	return x; 
}
void get_ans(int u1,int v1,int u2,int v2){
	vector<ccf> ans1,ans2,ans3,tmp;
	if(dep[u1]>dep[v1]) swap(u1,v1);
	if(dep[u2]>dep[v2]) swap(u2,v2);
	int lca=get_lca(v1,v2);
	for(int i=lca;dep[i]>max(dep[u1],dep[u2]);i=fa[i]){
		ans1.push_back({i,fa[i]});
	}
	for(int i=v1;dep[i]>dep[lca];i=fa[i]){
		ans2.push_back({fa[i],i});
	}
	reverse(ans2.begin(),ans2.end());
	for(int i=v2;dep[i]>dep[lca];i=fa[i]){
		ans3.push_back({fa[i],i});
	}
	reverse(ans3.begin(),ans3.end());
	ans2.push_back({v1,u1}),ans3.push_back({v2,u2});
	if(dep[u1]<dep[u2]){
		cout<<lca<<" "<<u2<<'\n';
		for(int i=u2;dep[i]>dep[u1];i=fa[i]){
			tmp.push_back({fa[i],i});
		}
		reverse(tmp.begin(),tmp.end());
		for(int i=0;i<tmp.size();i++){
			ans2.push_back(tmp[i]);
		}
	}else{
		cout<<lca<<" "<<u1<<'\n';
		for(int i=u1;dep[i]>dep[u2];i=fa[i]){
			tmp.push_back({fa[i],i});
		}
		reverse(tmp.begin(),tmp.end());
		for(int i=0;i<tmp.size();i++){
			ans3.push_back(tmp[i]);
		}
	}
	cout<<ans1.size()+1<<" ";
	for(int i=0;i<ans1.size();i++){
		cout<<ans1[i].l<<" ";
	}
	cout<<ans1[ans1.size()-1].r<<'\n'<<ans2.size()+1<<" ";
	for(int i=0;i<ans2.size();i++){
		cout<<ans2[i].l<<" ";
	}
	cout<<ans2[ans2.size()-1].r<<'\n'<<ans3.size()+1<<" ";
	for(int i=0;i<ans3.size();i++){
		cout<<ans3[i].l<<" ";
	}
	cout<<ans3[ans3.size()-1].r<<'\n';
}
bool flag;
void dfs(int x,int last){
	vst[x]=used[x]=true;
	fa[x]=last;
	dep[x]=dep[last]+1; 
	if(flag) return;
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		if(edge[i].to==last) continue;
		if(!vst[edge[i].to]){
			dfs(edge[i].to,x);
		}else if(used[edge[i].to]){
			int pos=x;
			while(pos!=edge[i].to){
				if(tu[pos]&&tv[pos]){
					get_ans(tu[pos],tv[pos],x,edge[i].to);
					flag=true;
					return;
				}else{
					tu[pos]=x;
					tv[pos]=edge[i].to;
				}
				pos=fa[pos];
			}
		}
		if(flag) return;
	}
	used[x]=false;
}
int t,n,m;
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			head[i]=-1;
			vst[i]=used[i]=tu[i]=tv[i]=0; 
		}
		cnt=flag=0;
		while(m--){
		int uu,vv;
			cin>>uu>>vv;
			add(uu,vv);
			add(vv,uu);
		}
		for(int i=1;i<=n;i++){
			if(!vst[i]) dfs(i,0);
		}
		if(!flag) cout<<"-1\n";	
	}
	return 0;
}
```
[本代码可以通过洛谷评测。](https://www.luogu.com.cn/record/181191884)

Written by [toolong114514](https://www.luogu.com/user/477821) on 2024/10/10.

---

## 作者：UMS2 (赞：1)

### 题目概述
对于一个有 $n$ 个点，$m$ 条边的无向图，找到两个点 $S$ 与 $T$，存在三条**完全不同**的路径。

$1\le \sum n, \sum m \le 1\times 10^5$。

### 思路
先考虑图为一颗树的情况，此时任意两点间只有一条路径。若存在一条额外的边 $(u,v)$，则除 $u,v$ 之外，处于环内的点对于其他点都有两条不相交的路径。而扩展到第二个环，即可得到第三条路径，所以，问题就转化为找到被同时处于两个环内的边。

由于一个图的 `dfs` 树除树边外不存在横叉边，只存在返祖边，所以可以只考虑两条额外的边均为返祖边的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/ehu636ps.png)

由于一个环可以由额外边确定，可使用边 $(u,v)$ 来指代环，其中 $u$ 为 $v$ 的祖先。若用 $(u,v)$ 指代祖先深度更小的环，$(x,y)$指代深度更大的环，则不难发现三条路径分别是：

1. $x$ -> $y$ -> $lca(v,y)$。
2. $x$ -> $u$ -> $v$ -> $lca(v,y)$。
3. $x$ -> $lca(v,y)$。

这样就找到了符合条件的方案，可以在 dfs 时同时记录边的覆盖情况，发现合法方案后直接记录输出即可。

### Code
这里只展示 dfs 过程和方案的输出。
```cpp
void gpath(int lu,int ru,int lv,int rv){
	int lca=glca(lu,ru);
	if(dep[lv]<dep[rv]){
		swap(lv,rv);
		swap(lu,ru);
	}
	
	t=0;
	int tp=lca;
	cout<<lv<<' '<<lca<<endl;

	while(tp!=lv){
		res[++t]=tp;
		tp=fa[tp];
	}
	res[++t]=tp;

	cout<<t<<' ';
	for(int i=t;i;i--)cout<<res[i]<<' ';
	cout<<endl;
	t=0;
	
	tp=lv;
	while(tp!=rv){
		res[++t]=tp;
		tp=fa[tp];
	}
	res[++t]=tp;
	tp=ru;
	while(tp!=lca){
		res[++t]=tp;
		tp=fa[tp];
	}
	res[++t]=tp;
	
	cout<<t<<' ';
	for(int i=1;i<=t;i++)cout<<res[i]<<' ';
	cout<<endl;
	t=0;
	
	tp=lu;
	while(tp!=lca){
		res[++t]=tp;
		tp=fa[tp];
	}
	res[++t]=tp;
	
	cout<<(t+1)<<' '<<lv<<' ';
	for(int i=1;i<=t;i++)cout<<res[i]<<' ';
	cout<<endl;
	ed=1;
}

void dfs(int u){
	if(ed)return;
	dep[u]=dep[fa[u]]+1;
	vis[u]=inst[u]=1;
	for(int i=h[u],v;i&&!ed;i=e[i].u){
		v=e[i].v;
		if(v==fa[u])continue;
		if(!vis[v]){//未记录的点
			fa[v]=u;
			dfs(v);
		}
		else if(inst[v]){//发现环
			for(int p=u;p!=v;p=fa[p]){
				if(covu[p]&&covv[p]){
					gpath(covu[p],u,covv[p],v);
					break;
				}
				covu[p]=u;//标记环的两端点
				covv[p]=v;
			}
		}
	}
	inst[u]=0;
}
```

---

