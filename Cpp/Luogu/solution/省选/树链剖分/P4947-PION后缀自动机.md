# PION后缀自动机

## 题目背景

NOIP2018原创模拟题T6

NOIP2018原创模拟赛DAY2 T3

NOIP DAY1 T3+ or DAY2 T3 难度

鉴于 NOIP2017 DAY2 T3 的难度，就有了这道题。**然而这道题考察的知识并不是后缀自动机**

## 题目描述

小P是一个技术高超的程序员，他开发了一套自己的操作系统，称为PION系统，该系统与Windows和Linux有很大不同，目前他正在测试该系统。

PION系统与Windows系统最大的不同在于文件的储存与操作，POIN的文件夹没有父子之分。我们知道，在Windows系统中，可以在文件夹里新建子文件夹。但是，PION系统文件夹不分父子关系，**但是部分文件夹之间可以互相直接访问，我们称这种关系为互访关系，而且，对于一个有$n$个文件夹的系统来说，这种互访关系有$n-1$个，且保证所有文件夹均可以通过互访关系而互相访问。也就是说：我们可以把Windows中的文件夹的集合看作一棵有根树，而把PION系统中的文件夹集合看作为无根树。**

在PION系统中，每个文件夹都可以储存文件，和Windows一样，文件名包含后缀名。

现在小P正在构思一种可以对文件夹中文件后缀进行方便操作的交互式程序dmc，他也将其称为**PION后缀自动机**。由于他太忙了，所以他希望你帮他实现**部分功能**。

他希望你帮他实现三个功能：

1.计算两个文件夹之间的距离。我们定义：文件夹之间的距离为其中一个文件夹通过互访达到另一个文件夹最少互访次数。比如：同一个文件夹距离为0，两个有互访关系的文件夹距离为1。

2.计算两个文件夹路径之间（包含这两个文件夹）的文件夹中的文件的后缀名为A的文件数量，**其中A是一个小写字符串。提示：我们可以把PION文件夹之间的路径理解为树中两节点之间的路径。**

3.删除两个文件夹路径之间（包含这两个文件夹）的文件夹中的文件的后缀名为A的文件，并统计被删除文件的数量。

由于dmc是一个交互系统，所以我们用tab语言描述这三个操作：

```
query /p u v
```

表示操作一，其中 u,v 表示两文件夹的编号

```
query /e u v *.A
```

表示操作二，其中 u,v 表示两文件夹的编号，$'*'$ 为通配符，$'.'$用于分隔文件名与后缀，**A是一个小写字符串**。

```
del /e u v *.A
```

表示操作三， $u,v, *.A$ 意义与操作二相同。

**如果没有看懂题目请结合样例及样例解释来理解。**

最后，这个困难的任务就交给你了。

## 说明/提示

**样例一解释：**

![T6](https://cdn.luogu.com.cn/upload/pic/34166.png)

如图为样例一大致结构，橙色方框为文件夹，灰色文字表示文件后缀名，红色线条表示文件互访关系。

对于第一个操作：文件夹1到5之间txt文件有3个所以输出3  
对于第二个操作：文件夹1与4距离为2  
对于第三个操作：删除的为文件夹2的文件，txt文件有两个，所以输出2  
对于第四个操作：由于文件夹2的txt文件被删除了，所以1到5之间txt文件只有1个  
对于第五个操作：文件夹3到4之间vbs文件有2个所以输出2

**数据范围：**

30%数据满足：$n,m<=100,k<=3$

50%数据满足：$n,m<=5000,k<=10$

70%数据满足：$n,m<=2 \times 10^4,k<=50$

90%数据满足：$n,m<=5 \times 10^4$

100%数据满足：$n,m<=10^5$，文件总数小于$5 \times 10^5$，文件后缀名为小写字符串且不超过6个字符

其他说明：

1.约50%的数据为完全随机生成

2.数据弱化版：[PION后缀自动机（数据弱化版）](https://www.luogu.org/problemnew/show/U41487)

## 样例 #1

### 输入

```
5 5
1 2
2 4
2 5
1 3
2 cpp c
3 pas txt txt
2 vbs bat
3 vbs cpp pas
4 cpp c pas txt
query /e 1 5 *.txt
query /p 1 4
del /e 2 2 *.txt
query /e 1 5 *.txt
query /e 4 3 *.vbs```

### 输出

```
3
2
2
1
2```

## 样例 #2

### 输入

```
12 7
1 2
1 3
1 4
2 5
2 6
3 7
7 12
8 4
8 9
10 9
11 9
0
2 c c
3 zz c c
0
1 gif
2 png bmp
3 avl avl mpshi
0
4 cpp c pas js
5 a b c d e
0
3 a b c
query /p 11 12
query /e 1 2 *.gif
query /e 6 10 *.c
del /e 2 9 *.c
del /e 3 12 *.c
query /e 5 6 *.gif
query /e 6 1 *.c```

### 输出

```
7
0
4
3
3
1
0```

# 题解

## 作者：mrsrz (赞：6)

一道比较简单的数据结构题。

如果只有一种字符串，那么我们可以直接树链剖分+线段树来解决。

这里有多种字符串，那么我们还是树链剖分，然后对每种不同的字符串开线段树就可以了。空间用动态开点来解决。

操作2、3就是基本的线段树区间修改区间查询。操作1直接询问LCA即可。

对于判断字符串相等的问题，由于字符串长度不超过6，因此我们把字符串看做一个**27**进制数，用```long long```存，```map```离散化即可。

设字符串总数为$S$，则时间复杂度$O(n+m\log^2 n+S\log n)$，空间复杂度$O(n+S\log n)$。

## Code：
```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<map>
using namespace std;
typedef long long LL;
const int N=1e5+5,M=N*5;
char ss[233];
vector<int>G[N];
int n,m,fa[N],son[N],top[N],sz[N],dfn[N],idx,dep[N],rt[M],ls[M*20],rs[M*20],d[M*20],tot,num;
map<LL,int>ys;
inline LL Hx(char*s,int n){
	LL ret=0,x=1;
	for(int i=2;i<n;++i,x*=27)
	ret+=(s[i]-'a'+1)*x;
	return ret;
}
void dfs(int now){
	sz[now]=1;
	for(int to:G[now])
	if(!dep[to]){
		dep[to]=dep[now]+1,fa[to]=now,dfs(to);
		sz[now]+=sz[to];
		if(!son[now]||sz[son[now]]<sz[to])son[now]=to;
	}
}
void dfs2(int now){
	dfn[now]=++idx;
	if(son[now])top[son[now]]=top[now],dfs2(son[now]);
	for(int to:G[now])
	if(to!=son[now]&&to!=fa[now])dfs2(top[to]=to);
}
inline int LCA(int x,int y){
	while(top[x]!=top[y])
	if(dep[top[x]]>dep[top[y]])x=fa[top[x]];else y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}
inline int dist(int u,int v){return dep[u]+dep[v]-2*dep[LCA(u,v)];}
void add(int&o,int l,int r,const int&pos){
	if(!o)o=++tot;
	++d[o];
	if(l<r){
		const int mid=l+r>>1;
		if(pos<=mid)add(ls[o],l,mid,pos);else add(rs[o],mid+1,r,pos);
	}
}
int erase(int&o,int l,int r,const int&L,const int&R){
	if(!o)return 0;
	int ret=0;
	if(L<=l&&r<=R){
		ret+=d[o],o=0;return ret;
	}
	const int mid=l+r>>1;
	if(L<=mid)ret+=erase(ls[o],l,mid,L,R);
	if(mid<R)ret+=erase(rs[o],mid+1,r,L,R);
	d[o]=d[ls[o]]+d[rs[o]];
	if(!d[o])o=0;
	return ret;
}
int erase(int&o,int x,int y){
	int ret=0;
	while(top[x]!=top[y])
	if(dep[top[x]]>dep[top[y]])
	ret+=erase(o,1,n,dfn[top[x]],dfn[x]),x=fa[top[x]];else
	ret+=erase(o,1,n,dfn[top[y]],dfn[y]),y=fa[top[y]];
	if(dep[x]<dep[y])ret+=erase(o,1,n,dfn[x],dfn[y]);else ret+=erase(o,1,n,dfn[y],dfn[x]);
	return ret;
}
int query(int o,int l,int r,const int&L,const int&R){
	if(!o)return 0;
	if(L<=l&&r<=R)return d[o];
	const int mid=l+r>>1;
	if(L<=mid&&mid<R)return query(ls[o],l,mid,L,R)+query(rs[o],mid+1,r,L,R);
	if(L<=mid)return query(ls[o],l,mid,L,R);return query(rs[o],mid+1,r,L,R);
}
int query(int o,int x,int y){
	int ret=0;
	while(top[x]!=top[y])
	if(dep[top[x]]>dep[top[y]])
	ret+=query(o,1,n,dfn[top[x]],dfn[x]),x=fa[top[x]];else
	ret+=query(o,1,n,dfn[top[y]],dfn[y]),y=fa[top[y]];
	if(dep[x]<dep[y])ret+=query(o,1,n,dfn[x],dfn[y]);else ret+=query(o,1,n,dfn[y],dfn[x]);
	return ret;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;++i){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v),G[v].push_back(u);
	}
	dfs(dep[1]=1),dfs2(1);
	ss[0]=ss[1]=' ';
	for(int i=1,k;i<=n;++i)
	for(cin>>k;k--;){
		cin>>(ss+2);
		LL hx=Hx(ss,strlen(ss));
		if(!ys.count(hx))ys[hx]=++num;
		add(rt[ys[hx]],1,n,dfn[i]);
	}
	while(m--){
		cin>>ss;
		if(*ss=='q'){
			cin>>ss;
			if(ss[1]=='p'){
				int u,v;
				cin>>u>>v;
				cout<<dist(u,v)<<'\n';
			}else{
				int u,v;
				cin>>u>>v>>ss;
				LL hx=Hx(ss,strlen(ss));
				if(!ys.count(hx))cout<<"0\n";else
				cout<<query(rt[ys[hx]],u,v)<<'\n';
			}
		}else{
			int u,v;
			cin>>ss>>u>>v>>ss;
			LL hx=Hx(ss,strlen(ss));
			if(!ys.count(hx))cout<<"0\n";else
			cout<<erase(rt[ys[hx]],u,v)<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Voldermod (赞：3)


**前言：**

1.我的方法是我在出好这道题之前想出的，当时先想的对线性序列的操作，出这道题时改为树上操作，而且为了增加难度，每个节点上元素数量可能不相同，于是需要对树链剖分进行较大的变形。

2.很幸运，这道题方法不唯一，它可以用我不会的数据结构做，但具体怎么做我就不知道了。（可以请教AC的大佬）。

---

考察知识：树链剖分，线段树，链表，排序，二分，字符串处理

算法难度：XXXXX 实现难度：XXXXX

---

分析：算法较复杂，代码量大（板子太多）！这是一道典型的考场上正解不如写暴力的题！

先介绍**暴力算法**（55分）：

如果你的程序超时，你可以先尝试这道题：[PION后缀自动机（数据弱化版）](https://www.luogu.org/problemnew/show/U41487)

算法难度：XXX 实现难度：XXX+

显然储存文件后缀信息不能用数组，空间开不下，所以我们用链表储存所有文件夹中文件的后缀信息；

然后是后缀的处理，注意到字符串长度小于6，如果我们用 1 表示 a ，2 表示 b ，... ... ，26 表示 z，这就相当于将字符串看做一个27进制数，这样我们就可以在 int 范围内用数字表示字符串了

解决了上面两个问题之后，我们就可以建树然后对每个操作用暴力的 “逐步爬山法” （即按路径一个节点一个节点的统计）解决了，实现难度不大

其实这种方法对随机数据效果还是比较好的（甚至比下面的满分算法还略快一点），但是你觉得数据可能完全随机么？

时间复杂度：极端情况约$O(mn)$

**满分算法：**

代码量比较大。

看到这道题我们应该可以想到用树链剖分来做。

我们先考虑怎么对序列进行统计和修改，对于操作2，我们需要找到一个序列中的子序列。我们可以用一个结构体来储存，结构体储存序列中每个元素的值（字符串的hash值）和序列中每个元素在序列中的位置。然后将这个结构体序列按元素值的排序（元素值相同的按在序列中的位置排序）。当我们需要查找一个序列相同数值所在的区间的时候用 lower_bound 和 upper_bound 就可以完成，对于查找出来的目标区间，还需要用二分法来查找该区间中元素的下标在目标子序列中的数量。

至于修改，用线段树的区间维护实现。

解决了对序列的修改，我们还要解决树中每个节点含有的文件数目不相同的问题，如果一个节点没有文件，那么一个简单的方法是新建一个伪文件，可以将hash值赋为 -1。

之后就是树链剖分了，不同于树链剖分模板，我们还要新建一个辅助数组 low[i] ，表示节点 i 的重子孙可以到达的最深节子节点的编号，我们先对$[\,top[i],low[i]\,]$排序，之后查询的时候我们按树链剖分树上路径查询的方法查询$[\,top[i],low[i]\,]$之间的序列即可。

这道题在树上将路径拆开查询的思想类似于分块。

其实吧，上面只是代码实现的一部分，具体细节远不止这些，更多的细节请参考代码。

时间复杂度：极端情况约$O((n+m)log^2n)$

---

代码请参考：[【洛谷】NOIP2018原创模拟赛DAY2题解T3](https://blog.csdn.net/hi_ker/article/details/82820861#t3)

---

## 作者：a_small_penguin (赞：2)

这道题好像基本上没什么难的？

### 思路

先对每个文件后缀名进行离散化。

再开 $5 \times 10^5$ 棵能够实现区间赋值、区间和的线段树。每棵树用于对每种离散化后的后缀名进行维护。

当然，直接开显然会 MLE，所以要用动态开点。

接下来分操作分析：

1. 就是 $x$ 到 $y$ 之间的点的数量 $-1$。如果你为了求点数再开一个线段树也没人拦你。
2. 就是重链剖分求区间和。
3. 就是重链剖分求区间和后再区间赋值。

然后……没然后了，结束了。做完这些后就可以获得 AC 的好成绩。


### code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100009
#define sp(i,j)i^=j,j^=i,i^=j
#define pd tree[tree[i].ls].d=tree[tree[i].rs].d=0,tree[tree[i].ls].lazy=tree[tree[i].rs].lazy=1
int n,m,res,rk[N],sum;
struct V{
    vector<int> e;
    int size,top,h,d,id,fa,son;
}v[N];
namespace xds{
    int cnt;
    int rt[5*N];
    struct TREE_V{
        int ls,rs,d,lazy;
    }tree[10000009];
    inline void add(int &i,int l,int r,int x,int y){
        if(!i)i=++cnt;
        if(l==r){
            tree[i].d+=y;
            return;
        }
        int mid=(l+r)>> 1;
        if(x<=mid)add(tree[i].ls,l,mid,x,y);
        else add(tree[i].rs,mid+1,r,x,y);
        tree[i].d=tree[tree[i].ls].d+tree[tree[i].rs].d;
    }
    inline void change(int i,int l,int r,int x,int y){
        if(!i)return;
        if(x<=l&&r<=y){
            tree[i].d=0;
            tree[i].lazy=1;
            return;
        }
        if(tree[i].lazy)pd;
        int mid=(l+r)>> 1;
        if(x<=mid)change(tree[i].ls,l,mid,x,y);
        if(mid<y)change(tree[i].rs,mid+1,r,x,y);
        tree[i].d=tree[tree[i].ls].d+tree[tree[i].rs].d;
    }
    inline int ask(int i,int l,int r,int x,int y){
        if(!i)return 0;
        if(x<=l&&r<=y)return tree[i].d;
        if(tree[i].lazy)pd;
        int mid=(l+r)>> 1,t=0;
        if(x<=mid)t+=ask(tree[i].ls,l,mid,x,y);
        if(mid<y)t+=ask(tree[i].rs,mid+1,r,x,y);
        return t;
    }
}
inline void dfs(int u,int fa,int h){
    v[u].h=h,v[u].fa=fa, v[u].size=1,sum=-1;
    for(auto to:v[u].e){
        if(to==fa)continue;
        dfs(to,u,h+1);
        v[u].size+=v[to].size;
        if(sum<v[to].size)v[u].son=to,sum=v[to].size;
    }
}
inline void dfs2(int u,int top){
    v[u].top=top,v[u].id=++res,rk[res]=u;
    if(!v[u].son)return;
    dfs2(v[u].son,top);
    for(auto to:v[u].e){
        if(to==v[u].fa)continue;
        if(to==v[u].son)continue;
        dfs2(to,to);
    }
}
vector<pair<string,int> > _;
unordered_set<string> __;
map<string,int> mp;
inline void slh(){
    res=0;
    for(auto it:__) mp[it]=++res;
    for(auto it:_)xds::add(xds::rt[mp[it.first]],1,n,v[it.second].id,1);
}
inline int dis(int x,int y){
    int ans=0;
    while(v[x].top^v[y].top){
        if(v[v[x].top].h<v[v[y].top].h)sp(x,y);
        ans+=v[x].id-v[v[x].top].id+1,x=v[v[x].top].fa;
    }
    if(v[x].id>v[y].id)sp(x,y);
    ans+=v[y].id-v[x].id+1;
    return ans;
}
inline int ask(int x,int y,int c){
    int ans=0;
    while(v[x].top^v[y].top){
        if(v[v[x].top].h<v[v[y].top].h)sp(x,y);
        ans+=xds::ask(xds::rt[c],1,n,v[v[x].top].id,v[x].id);
        x=v[v[x].top].fa;
    }
    if(v[x].id>v[y].id)sp(x,y);
    ans+=xds::ask(xds::rt[c],1,n,v[x].id,v[y].id);
    return ans;
}
inline void change(int x,int y,int c){
    while(v[x].top^v[y].top){
        if(v[v[x].top].h<v[v[y].top].h)sp(x,y);
        xds::change(xds::rt[c],1,n,v[v[x].top].id,v[x].id);
        x=v[v[x].top].fa;
    }
    if(v[x].id>v[y].id)sp(x,y);
    xds::change(xds::rt[c],1,n,v[x].id,v[y].id);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1,_u,_v;i<n;i++){
        cin>>_u>>_v;
        v[_u].e.push_back(_v),v[_v].e.push_back(_u);
    }
    for(int i=1,k;i<=n;i++){
        cin>>k;
        for(int j=1;j<=k;j++){
            string s;
            cin>>s;
            _.push_back({s,i});
            __.insert(s);
        }
    }
    dfs(1,0,1),dfs2(1,1),slh();
    for(int i=1;i<=m;i++){
        string o,p,z;
        char c;
        int x,y;
        cin>>o>>c>>p>>x>>y;
        if(o=="query"&&p=="p"){
            cout<<dis(x,y)- 1<<"\n";
        }
        if(o=="query"&&p=="e"){
            cin>>c>>c>>z;
            cout<<ask(x,y,mp[z])<<"\n";
        }
        if(o=="del"&&p=="e"){
            cin>>c>>c>>z;
            cout<<ask(x,y,mp[z])<<"\n";
            change(x,y,mp[z]);
        }
    }
    return 0;
}
```

---

## 作者：hzjnsy (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/P4947 "题目传送门")**

> - 给出一棵 $n$ 个点的树，每个点上有若干字符串，有 $m$ 次操作，分为三种：
>
>    - $\texttt{query /p }u\texttt{ }v$，查询 $u,v$ 简单路径上的边数。
>
>    - $\texttt{query /e }u \texttt{ }v\texttt{ *.}s$，查询 $u,v$ 简单路径上字符串 $s$ 出现了几次。
>
>    - $\texttt{del /e }u \texttt{ }v\texttt{ *.}s$，查询 $u,v$ 简单路径上字符串 $s$ 出现了几次，并删除这些 $s$。
>
> - $n,m\le 10^5$，字符串总数 $k$ 不超过 $5\times 10^5$，字符串长度不超过 $8$。

$\texttt{query /p}$ 操作比较简单，答案为 $dep_u+dep_v-2\times dep_{\text{LCA}(u,v)}$。考虑解决剩下两个操作。

字符串的种数很少，考虑使用 [P5838](https://www.luogu.com.cn/problem/P5838 "P5838") 的套路，有两种方法：

- **【方法一】**

  对每种字符串维护一棵动态开点线段树，线段树的节点维护对应 $dfn$ 序区间内该字符串的出现次数。
  
  - 对于 $\texttt{query /e}$ 操作，跳链时在对应的线段树上查询当前重链的贡献。
  
  - 对于 $\texttt{del /e}$ 操作，则先做一遍 $\texttt{query /e}$ 操作，然后再进行删除。删除的时候，在跳链时将当前重链对应的 $dfn$ 区间推平成 $0$。
 
  时间复杂度为 $\mathcal{O}(m\log^2 n)$，空间复杂度为 $\mathcal{O}(k\log n)$。
  
- **【方法二】**

   对每种字符串维护一棵平衡树（这里使用 `__gnu_pbds::tree`），有序存放有该字符的点的 $dfn$ 序，注意可能会重复，所以元素类型为 `pair`，`second` 的作用是区分同一个点的两个相同字符串。
   
   - 对于 $\texttt{query /e}$ 操作，设当前在点 $u$，跳链时使用 `order_of_key` 找到在 $[1,dfn_{top_u})$ 和 $[1,dfn_u]$ 中的值个数，相减即为当前重链上该字符串的出现次数。
   
   - 对于 $\texttt{del /e}$ 操作，同样先做一遍 $\texttt{query /e}$ 操作，然后再进行删除。删除的时候，使用 `lower_bound` 找到第一个大于等于 $dfn_{top_u}$ 的迭代器 $l$ 和第一个大于 $dfn_u$ 的迭代器 $r$，**暴力删除 $[l,r)$** 之间的所有迭代器。
   
   看上去很暴力，但是一开始插入了 $k$ 个元素，一个元素只能被删除一次，因此时间复杂度为 $\mathcal{O}(m\log^2 n)$，空间复杂度为 $\mathcal{O}(k+n)$。
   
给的是【方法二】的代码。笔者因为看到 [P7735](https://www.luogu.com.cn/problem/P7735 "P7735") 的一种新写法，即求出 $\texttt{LCA}(u,v)$ 后分别算 $u\rightsquigarrow \text{LCA}(u,v)$ 和 $v\rightsquigarrow \text{LCA}(u,v)$ 的信息，以为会更好写，结果那种写法会算重 $\text{LCA}(u,v)$ 的信息。在 P7735 中单点是没有贡献的，但是这题有，于是调了很久才发现要单独减去 $\text{LCA}(u,v)$ 的贡献。因此部分代码不建议读者参考，还是建议读者去参考[更常见的跳链查询](https://www.cnblogs.com/MnZnOIerLzy/articles/17438805.html "更常见的跳链查询")。

**[评测记录](https://www.luogu.com.cn/record/124722556 "评测记录")**

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define G __gnu_pbds
#define TOSNU tree_order_statistics_node_update
#define rnk order_of_key
#define lb lower_bound 
#define pii pair<int, int>
#define P make_pair 
#define fi first 
#define se second
#define vec vector
#define umap unordered_map
using namespace std; const int N = 1e5 + 5, inf = 1e9; typedef string str;
vec<int> g[N]; vector<pii> bin; vec<str> a[N]; str op1, op2, op3;
int n, m, dep[N], top[N], fa[N], hson[N], idx, dfn[N], siz[N], file;
umap<str, G::tree<pii, G::null_type, less<pii>, G::rb_tree_tag, G::TOSNU>> rbt;
void dfs1(int u) {
    siz[u] = 1;
    for (int v : g[u]) 
        if (v != fa[u]) dep[v] = dep[fa[v] = u] + 1, dfs1(v), siz[u] += siz[v];
}
void dfs2(int u) {
    for (int v : g[u]) {
        if (v == fa[u]) continue;
        if ((siz[v] << 1) > siz[u]) top[hson[u] = v] = top[u];
        else top[v] = v; dfs2(v);
    }
}
void dfs3(int u) {
    dfn[u] = ++idx; for (str s : a[u]) rbt[s].insert(P(idx, ++file));
    if (hson[u]) dfs3(hson[u]);
    for (int v : g[u]) if (v != fa[u] && v != hson[u]) dfs3(v);
}
int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
int chain(int u, int v, str suf) {
    int ret = 0;
    while (top[u] != top[v]) {
        ret += rbt[suf].rnk(P(dfn[u], inf)) - rbt[suf].rnk(P(dfn[top[u]], 0));
        u = fa[top[u]];
    }
    return ret + rbt[suf].rnk(P(dfn[u], inf)) - rbt[suf].rnk(P(dfn[v], 0));
}
void erase(int u, int v, str suf) {
    while (top[u] != top[v]) {
        auto l = rbt[suf].lb(P(dfn[top[u]], 0)), r = rbt[suf].lb(P(dfn[u], inf)); 
        bin.clear(); for (auto it = l; it != r; ++it) bin.emplace_back(*it);
        for (pii i : bin) rbt[suf].erase(i); u = fa[top[u]];
    }
    auto l = rbt[suf].lb(P(dfn[v],0)), r = rbt[suf].lb(P(dfn[u], inf)); 
    bin.clear(); for (auto it = l; it != r; ++it) bin.emplace_back(*it);
    for (pii i : bin) rbt[suf].erase(i);
}
int query(int u, int v, int lca, str suf) {
    if (lca == u) return chain(v, u, suf);
    if (lca == v) return chain(u, v, suf);
    return chain(u, lca, suf) + chain(v, lca, suf) - chain(lca, lca, suf);
}
void del(int u, int v, int lca, str suf) { 
    if (lca == u) return erase(v, u, suf), void();
    if (lca == v) return erase(u, v, suf), void();
    erase(u, lca, suf), erase(v, lca, suf);
}
signed main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0); cin >> n >> m;
    for (int i = 1, u, v; i < n; ++i)
        cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; 
        for (str tmp; x--;) cin >> tmp, a[i].emplace_back(tmp);
    }
    dfs1(1), dfs2(top[1] = 1), dfs3(1);
    for (int i = 1, u, v, lca; i <= m; ++i) {
        cin >> op1 >> op2 >> u >> v; lca = LCA(u, v);
        if (op2 == "/p")
            cout << dep[u] + dep[v] - (dep[lca] << 1) << '\n';
        else {
            cin >> op3; op3 = op3.substr(2);
            cout << query(u, v, lca, op3) << '\n';
            if (op1 == "del") del(u, v, lca, op3);
        }
    }
    return 0;
}
```

---

## 作者：reinforest (赞：0)

我们可以首先把所有的出现过的字符串存到一个 set 中，记 set 的大小为 $|S|$，然后对于所有的字符串都赋予一个离散化后的值。这个用 map 很容易维护。

然后我们分析三个操作：

第一个操作就是询问树上点 $(x,y)$ 之间的距离，这个可以找到它们的 lca 之后非常容易维护。

第二个操作和第三个操作看起来比较难维护。

我们不妨先考虑只有一种文件后缀名的情况。如果单独看一种字符串 $s$，相当于每个点的点权就是 $s$ 的个数，对于这道题就是路径的点权和。同时第三个操作相当于区间置零，这个用线段树+树链剖分很容易维护。（第三个操作要求输出删除了多少个 $s$，实际上就是第二个操作）

现在我们考虑多种字符串，我们仍然可以开 $|S|$ 个线段树，对于每一次操作可以找到字符串 $s$ 对应的线段树进行操作。

但是这样空间复杂度不能接受，容易发现有很多节点都用不到，所以可以使用动态开点线段树。简单来说，就是如果需要访问线段树上的一个节点，才会把这个节点新建出来。

这样空间复杂度就可以接受了。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr ll maxn=5e5+5;
typedef pair<string,ll> Pii;
ll n,q,tot,siz[maxn],hson[maxn],dep[maxn],fa[maxn],dfn[maxn],top[maxn];
struct node{
    ll ls,rs,val,tag;
};
vector<ll> G[maxn];
vector<Pii> addstr;
set<string> strs;
map<string,ll> mp;
struct SGT{
    ll rt[maxn],cnt;
    node s[maxn*40];
    void pushup(ll rt){
        s[rt].val=s[s[rt].ls].val+s[s[rt].rs].val;
    }
    void pushdown(ll rt){
        if(s[rt].tag){
            s[s[rt].ls].val=s[s[rt].rs].val=0;
            s[s[rt].ls].tag=s[s[rt].rs].tag=1;
            s[rt].tag=0;
        }
    }
    void add(ll l,ll r,ll x,ll c,ll &rt){
        if(!rt)rt=++cnt;
        if(l==r && r==x){
            s[rt].val+=c;
            return;
        }
        pushdown(rt);
        ll m=(l+r)>>1;
        if(x<=m)add(l,m,x,c,s[rt].ls);
        if(m<x)add(m+1,r,x,c,s[rt].rs);
        pushup(rt);
    }
    void update(ll l,ll r,ll L,ll R,ll &rt){
        if(!rt)rt=++cnt;
        if(L<=l && r<=R){
            s[rt].val=0;
            s[rt].tag=1;
            return;
        }
        pushdown(rt);
        ll m=(l+r)>>1;
        if(L<=m)update(l,m,L,R,s[rt].ls);
        if(m<R)update(m+1,r,L,R,s[rt].rs);
        pushup(rt);
    }
    ll query(ll l,ll r,ll L,ll R,ll rt){
        if(!rt)return 0;
        if(L<=l && r<=R)return s[rt].val;
        ll m=(l+r)>>1,ret=0;
        pushdown(rt);
        if(L<=m)ret+=query(l,m,L,R,s[rt].ls);
        if(m<R)ret+=query(m+1,r,L,R,s[rt].rs);
        return ret;
    }
}T;
void getsiz(ll x,ll f){
    siz[x]=1;fa[x]=f;dep[x]=dep[f]+1;
    for(auto v:G[x]){
        if(v==f)continue;
        getsiz(v,x);
        siz[x]+=siz[v];
        if(siz[v]>siz[hson[x]])hson[x]=v;
    }
}
void getdfn(ll x,ll f){
    dfn[x]=++tot;
    if(hson[x]){
        top[hson[x]]=top[x];
        getdfn(hson[x],x);
    }
    for(auto v:G[x]){
        if(v==f || v==hson[x])continue;
        top[v]=v;
        getdfn(v,x);
    }
}
void build(){
    ll id=0;
    for(auto it:strs){
        mp[it]=++id;
    }
    for(auto it:addstr){
        T.add(1,n,dfn[it.second],1,T.rt[mp[it.first]]);
    }
}
ll dis(ll x,ll y){
    ll ret=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        ret+=dfn[x]-dfn[top[x]]+1;
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])swap(x,y);
    return ret+dfn[x]-dfn[y]+1;
}
ll querypath(ll x,ll y,ll root){
    ll ret=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        ret+=T.query(1,n,dfn[top[x]],dfn[x],T.rt[root]);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])swap(x,y);
    return ret+T.query(1,n,dfn[y],dfn[x],T.rt[root]);
}
void updatepath(ll x,ll y,ll root){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        T.update(1,n,dfn[top[x]],dfn[x],T.rt[root]);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])swap(x,y);
    T.update(1,n,dfn[y],dfn[x],T.rt[root]);
}
int main(){
    //freopen("1.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<n;i++){
        ll x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    getsiz(1,0);
    top[1]=1;
    getdfn(1,0);
    for(int i=1;i<=n;i++){
        ll k;string stt;
        cin>>k;
        for(int j=1;j<=k;j++){
            cin>>stt;
            addstr.push_back(make_pair(stt,i));
            strs.insert(stt);
        }
    }
    build();
    while(q--){
        char c;
        string op1,op2,name;
        ll x,y;
        cin>>op1>>op2>>x>>y;
        if(op1[0]=='q' && op2[1]=='p'){
            cout<<dis(x,y)-1<<"\n";
        }else if(op1[0]=='q' && op2[1]=='e'){
            cin>>c>>c>>name;
            cout<<querypath(x,y,mp[name])<<"\n";
        }else{
            cin>>c>>c>>name;
            cout<<querypath(x,y,mp[name])<<"\n";
            updatepath(x,y,mp[name]);            
        }
    }
    return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

太美味了，孩子吃了都说好！

看到在一个树形结构上进行查询修改不难想到树剖。

对于每个文件后缀，因为总数不超过 $5 \times 10^5$ 且长度不超过 $6$，可以考虑求出哈希值，然后进行离散化，注意此处求哈希值时候不能存在某个字符对应的是 $0$ 值。

对于不知道这个字符种类总数的查询修改，可以考虑动态开点，然后内存是 $n \log n$ 的，其他都是正常树剖操作。

写完你就会发现你的写史能力很强！

[代码](https://www.luogu.com.cn/paste/eixel1aq)。

---

## 作者：Milthm (赞：0)

一道可爱的数据结构。

如果只有一个文件后缀名的话，那就是树链剖分板子了。

现在有很多个，我们可以考虑给每一个后缀名都开一个线段树，但是这样会炸空间，所以我们需要动态开点。

操作 $1$ 的 LCA 操作此时可以直接用树链剖分实现。操作 $2$ 就是普通的查询，操作 $3$ 就是先跑一遍操作 $2$，再删一次就可以了。

另外对于字符串转编号的操作，我直接用的 `unordered_map`，虽然常数大但是挺方便的。

### AC code

~~代码有点长，过不去不要紧，多调一下就出来了。~~

记住一定要想清楚你用的**这个点原来的编号**还是**这个点的新编号**。


```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
int n,m,syx,dep[N],son[N],top[N],siz[N],f[N],id[N],cnt,rt[N],yhb;
struct Seg{
	int l,r,sum;
}a[N*20];
vector<int>e[N];
unordered_map<string,int>qwq;
void dfs(int u,int fa){
	dep[u]=dep[fa]+1,f[u]=fa;siz[u]=1;
	for(int i=0;i<e[u].size();++i){
		int v=e[u][i];
		if(v!=fa){
			dfs(v,u);siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])son[u]=v;
		}
	}
}
void dfs2(int u,int t){
	id[u]=++cnt;top[u]=t;
	if(!son[u])return;
	dfs2(son[u],t);
	for(int i=0;i<e[u].size();++i){
		int v=e[u][i];
		if(v!=f[u]&&v!=son[u])dfs2(v,v);
	}
}
void pushup(int x){
	a[x].sum=a[a[x].l].sum+a[a[x].r].sum;
}
int update(int x,int l,int r,int k){
	if(!x)x=++yhb;
	//else a[++yhb]=a[x],x=yhb;
	if(l==r)a[x].sum++;
	else{
		int mid=(l+r)>>1;
		if(k<=mid)a[x].l=update(a[x].l,l,mid,k);
		else a[x].r=update(a[x].r,mid+1,r,k);
		pushup(x);
	}
	return x;
}
int query(int x,int l,int r,int ql,int qr){
	if(!x)return 0;
	if(ql<=l&&r<=qr)return a[x].sum;
	int mid=(l+r)>>1,ans=0;
	if(ql<=mid)ans+=query(a[x].l,l,mid,ql,qr);
	if(qr>mid)ans+=query(a[x].r,mid+1,r,ql,qr);
	return ans;
}
int del(int x,int l,int r,int ql,int qr){
	if(!x)return 0;
	if(ql<=l&&r<=qr){
		a[x].sum=0;return 0;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)a[x].l=del(a[x].l,l,mid,ql,qr);
	if(qr>mid)a[x].r=del(a[x].r,mid+1,r,ql,qr);
	pushup(x);
	if(!a[x].sum)return 0;
	return x;
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=f[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int dist(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int query(int x,int y,int k){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=query(rt[k],1,n,id[top[x]],id[x]);
		x=f[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans+=query(rt[k],1,n,id[x],id[y]);
	return ans;
}
void del(int x,int y,int k){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		rt[k]=del(rt[k],1,n,id[top[x]],id[x]);
		x=f[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	rt[k]=del(rt[k],1,n,id[x],id[y]);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;++i){
		int u,v;cin>>u>>v;
		e[u].push_back(v);e[v].push_back(u);
	}
	dfs(1,0);dfs2(1,1); 
	for(int i=1;i<=n;++i){
		int k;cin>>k;
		for(int j=1;j<=k;++j){
			string s;cin>>s;
			if(!qwq.count(s))qwq[s]=++syx;
			rt[qwq[s]]=update(rt[qwq[s]],1,n,id[i]);
		} 
	}
	while(m--){
		string s;
		cin>>s;
		if(s[0]=='q'){
			cin>>s;
			int u,v;cin>>u>>v;
			if(s[1]=='p')cout<<dist(u,v)<<'\n';
			else{
				cin>>s;
				s.erase(0,2);
				if(!qwq.count(s))cout<<"0\n";
				else cout<<query(u,v,qwq[s])<<'\n';
			}
		}
		else{
			cin>>s;int u,v;cin>>u>>v;
			cin>>s;s.erase(0,2);
			if(!qwq.count(s))cout<<"0\n";
			else cout<<query(u,v,qwq[s])<<'\n',del(u,v,qwq[s]);
		}
	}
	return 0;
}
```


---

## 作者：BFSDFS123 (赞：0)

数据结构好题。

我们考虑对这颗树进行树链剖分。

每次询问的时候，我们要查询一条路径上的有该后缀名的个数。

因为一个点上可能有多个后缀名，我们对每个后缀名建一颗线段树。

因为空间可能会很大，所以我们使用动态开点线段树。

操作一就是求两点之间距离，用树剖求 lca 即可。

后面两个操作，即为线段树的区间修改和区间求和的操作。

对于建树问题，其它两篇题解都是将字符串转为 $26$ 进制，然而但是没有必要。我们直接用 map 对字符串进行数值赋值就行了。


```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
#define ull unsigned long long
#define ll long long
using namespace std;
//#define int long long
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return w*s;
}
void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x<10)
	{
		putchar(x+'0');
		return ;
	}
	write(x/10);
	putchar(x%10+'0');
}
const int Maxn=4e5+10;
int n,m;
int son[Maxn],siz[Maxn];
int Top[Maxn],dfn[Maxn];
int dep[Maxn],fat[Maxn];
int dfsTime;
int head[Maxn],tot;
struct Edge{
	int to;
	int nxt;
}E[Maxn<<1];
void addedge(int u,int v)
{
	tot++;
	E[tot].to=v;
	E[tot].nxt=head[u];
	head[u]=tot;
}
void dfs1(int u,int fa)
{
	dep[u]=dep[fa]+1;
	fat[u]=fa;
	siz[u]=1;
	for(int i=head[u];i;i=E[i].nxt)
	{
		int v=E[i].to;
		if(v==fa) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])
		{
			son[u]=v;
		}
	}
}
void dfs2(int u,int tp)
{
	Top[u]=tp;
	dfn[u]=++dfsTime;
	if(!son[u])
	{
		return ;
	}
	dfs2(son[u],tp);
	for(int i=head[u];i;i=E[i].nxt)
	{
		int v=E[i].to;
		if(v==fat[u] || v==son[u])
		{
			continue;
		}
		dfs2(v,v);
	}
}
int root[Maxn<<5];
struct Segmenttree{
	struct segtree{
		int lson,rson;
		int nums;
	}t[Maxn<<5];
	int totnum;
	int newnode()
	{
		return ++totnum;
	}
	void pushup(int node)
	{
		t[node].nums=t[t[node].lson].nums+t[t[node].rson].nums;
	}
	void update(int &node,int l,int r,int pos)
	{
		if(!node)
		{
			node=newnode();
		}
		t[node].nums++;
		if(l==r)
		{
			return ;
		}
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			update(t[node].lson,l,mid,pos);
		}else{
			update(t[node].rson,mid+1,r,pos);
		}
	}
	int delet(int &node,int l,int r,int ql,int qr)
	{
		if(!node)
		{
			return 0;
		}
		int res=0;
		if(ql<=l && r<=qr)
		{
			res=t[node].nums;
			node=0;
			return res;
		}
		int mid=(l+r)>>1;
		if(ql<=mid)
		{
			res+=delet(t[node].lson,l,mid,ql,qr);
		}
		if(qr>mid)
		{
			res+=delet(t[node].rson,mid+1,r,ql,qr);
		}
		pushup(node);
		if(!t[node].nums)
		{
			node=0;
		}
		return res;
	}
	int query(int &node,int l,int r,int ql,int qr)
	{
		if(!node) return 0;
		if(ql<=l && r<=qr)
		{
			return t[node].nums;
		}
		int mid=(l+r)>>1,ans=0;
		if(ql<=mid)
		{
			ans+=query(t[node].lson,l,mid,ql,qr);
		}
		if(qr>mid)
		{
			ans+=query(t[node].rson,mid+1,r,ql,qr);
		}
		return ans;
	}
}seg;

int queryedge(int &node,int u,int v)
{
	int ans=0;
	while(Top[u]!=Top[v])
	{
		if(dep[Top[u]]<dep[Top[v]])
		{
			swap(u,v);
		}
		ans+=seg.query(node,1,n,dfn[Top[u]],dfn[u]);
		u=fat[Top[u]];
	}
	if(dep[u]>dep[v])
	{
		swap(u,v);
	}
	ans+=seg.query(node,1,n,dfn[u],dfn[v]);
	return ans;
}
int deledge(int &node,int u,int v)
{
	int ans=0;
	while(Top[u]!=Top[v])
	{
		if(dep[Top[u]]<dep[Top[v]])
		{
			swap(u,v);
		}
		ans+=seg.delet(node,1,n,dfn[Top[u]],dfn[u]);
		u=fat[Top[u]];
	}
	if(dep[u]>dep[v])
	{
		swap(u,v);
	}
	ans+=seg.delet(node,1,n,dfn[u],dfn[v]);
	return ans;
}
int lca(int u,int v)
{
	while(Top[u]!=Top[v])
	{
		if(dep[Top[u]]<dep[Top[v]])
		{
			swap(u,v);
		}
		u=fat[Top[u]];
	}
	if(dep[u]>dep[v])
	{
		swap(u,v);
	}
	return u;
}
int main()
{
	n=read();
	m=read();
	for(int i=1;i<n;i++)
	{
		int u,v;
		u=read(),v=read();
		addedge(u,v);
		addedge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	unordered_map<string,int> mp;
	int cnts=0;
	for(int i=1;i<=n;i++)
	{
		int nums;
		nums=read();
		while(nums--)
		{
			string str;
			cin>>str;
			if(mp[str]==0)
			{
				mp[str]=++cnts;
			}
			seg.update(root[mp[str]],1,n,dfn[i]);
		}
	}
	int tot=0;
	while(m--)
	{
		string str;
		cin>>str;
		if(str=="query")
		{
			string str2;
			cin>>str2;
			if(str2=="/p")
			{
				int u,v;
				u=read();
				v=read();
				int Lca=lca(u,v);
				write(dep[u]+dep[v]-2*dep[Lca]);
				putchar('\n');
			}else{
				int u,v;
				u=read(),v=read();
				string qaq;
				cin>>qaq;
				string tmp="";
				bool flags=0;
				for(int i=0;i<qaq.size();i++)
				{
					if(qaq[i]=='.')
					{
						flags=1;
						continue;
					}
					if(flags) tmp+=qaq[i];
				}
//				cout<<"tmp="<<tmp<<endl;
				if(mp[tmp]==0) puts("0");
				else{
					write(queryedge(root[mp[tmp]],u,v));
					putchar('\n');
				}
			}
		}else{
			string lrh;
			cin>>lrh;
			int u,v;
			u=read();
			v=read();
			string qaq;
			cin>>qaq;
			string tmp="";
			bool flags=0;
			for(int i=0;i<qaq.size();i++)
			{
				if(qaq[i]=='.')
				{
					flags=1;
					continue;
				}
				if(flags) tmp+=qaq[i];
			}
			if(mp[tmp]==0) puts("0");
			else{
				write(deledge(root[mp[tmp]],u,v));
				putchar('\n');
			}
		}
	}
	return 0;
}

```

---

