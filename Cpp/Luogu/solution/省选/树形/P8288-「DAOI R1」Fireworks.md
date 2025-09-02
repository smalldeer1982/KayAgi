# 「DAOI R1」Fireworks

## 题目背景

> 俯首，满城灯火交辉。
> 
> 回眸，漫天流星逆飞。

## 题目描述

人们以前通常会放烟花，而每个烟花都有它本身的美观度。

$ \texttt{Iratis} $ 想要在户外放烟花，但是有烟花之间有一些关系：

- 关系一：对于烟花 $ x $ ，有一个对应烟花 $ a_x $ ，若烟花 $ x $ 与烟花 $ a_x $ 一起燃放，就会使烟花 $ x $ 的美观度减少 $ b_x $ 。

- 关系二：有一些烟花是一个系列，必须同时燃放，其中有一个是主烟花，**每个烟花只会属于一个系列**。

特别地，若有一系列 $ S_1 $ （主烟花为 $ p_1 $ ） 。 $ p_1 $ 关系一所对应的烟花为系列 $ S_2 $ 中的烟花。而 $ S_1 $ 系列中的其他烟花与非 $ S_1,S_2 $ 系列中的烟花形成关系一。**那么对于这条关系一，它不会降低美观度。**

$ \texttt{Iratis} $ 家里有 $ n $ 个烟花，他希望选择其中的一些烟花燃放，使得这些**烟花的美观度总和**最大。

## 说明/提示

### 样例解释
#### 样例1解释

烟花 $ 1,2,3 $ 一起燃放，最大美观度为 $ 2+2+2-1-1-1=3 $ 。

#### 样例2解释

烟花 $ 1,3,4 $ 一起燃放。

由于 $ 1,3 $ 为同一系列且 $ 1 $ 为主烟花，所以 $ 3 $ 烟花的关系一不会生效。

故总的美观度为 $ 3 \times 3-2=7 $ 。

### 数据规模

**本题采用捆绑测试**

| Subtask | $ m $  | 分值 |
| :----------: | :----------: | :----------: |
| $ 0 $ | $ =0 $ | $ 30 $ |
| $ 1 $ | 无特殊限制 | $ 70 $ |

对于 $ 100\% $ 的数据，满足 $ 0 \leq m \leq n \leq 5 \times 10^5,0 \leq b_i \leq v_i \leq 10^{12},1 \leq a_i \leq n,a_i \neq i $ 。 

## 样例 #1

### 输入

```
3 0
2 2 1
2 3 1
2 1 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
4 1
3 2 1
3 1 3
3 4 2
3 3 2
1 2 1 3
```

### 输出

```
7```

# 题解

## 作者：Yanami_Anna (赞：2)

### 前言

我从来不使用 STL，使用 STL 让我感到不舒服，我不会再使用 STL 写题，望周知。

为什么题解区官方题解都没有啊，不是很能理解。

关注莲莲，好运连连！

### 思路

#### Subtask 1

一种烟花只会指向另一种烟花，非常像基环树。

$m=0$，我们考虑基环树上动态规划。

我们考虑先在子树上动态规划，然后再把答案丢到环上统计起来。

设 $dp_{i,0/1}$ 表示 在以 $i$ 为根的子树中，第 $i$ 个点取还是不取得到的最大点权。

转移方程非常明显，$dp_{i,0}=dp_{i,0}+\max\left(dp_{v,0},dp_{v,1}\right)$，$dp_{i,1}=dp_{i,0}+\max\left(dp_{v,0},dp_{v,1}-w\right)$，其中 $v$ 为 $i$ 的子结点，$w$ 为 $i$ 到 $v$ 的这条边的边权。

你可能会想，拉到环上像树一样动态规划就能解决这个难题，可事实并非如此，起点会说：你真以为终点只由终点的前驱更新啊？你爹都不认识了是吧？

在环上合并这些信息，你应该做过 P2607，像这个题一样，钦点环上的一个起点的状态，一个环就会被破成一条链，在这条链上动态规划，而如果起点的状态为选，终点的状态也为选，就需要额外减掉起点与终点的边权，在合计 $4$ 种情况中取出最大值即可。

虽然这种做法只能在及其罕见的情况下起到作用，但是可以拿到 $30$ 分。

#### Subtask 2

无特殊情况。

考虑到关系 $2$，即限制一些烟花必须一起燃放，考虑用并查集将他们合并，合并起来后用他们的关系建立新图，由于题目给出的限制，一个大点至多连出去一条边。

于是新的图就会是一个基环树与树的森林，在上面动态规划就能解决这个难题。

这个题是比较卡的，如果你使用了大量 STL，就会出现罕见的 TLE，但是没关系，开 O2 就能跑过，任何 STL 终将绳之以法。

如果你因为某些原因 RE 或者 WA 了，我给出一组 hack。

```
input:
10 2
7 4 65
40 1 74
48 8 32
77 5 94
74 3 79
65 8 19
38 5 80
60 4 48
60 3 1
15 9 25
1 3 1 7 6
4 3 4 9 2

output:
270
```

### 代码

```cpp
#include<bits/stdc++.h>
#define mkpr make_pair
#define int long long
using namespace std;
const int MAXN=5e5+5;
int n,q;
class UFS{
    public:
    int father[MAXN];
    void init(){
        for(int i=1;i<=n;i++)father[i]=i;
        return;
    }
    int find(int x){
        if(father[x]==x)return x;
        return father[x]=find(father[x]);
    }
    void unionn(int x,int y){
        x=find(x),y=find(y);
        if(x^y)father[x]=y;
        return;
    }
}P;
int cnt=1;
struct edge{
    int v,w;
    int nxt;
}E[MAXN<<1];
int head[MAXN];
struct node{
    int v,a,b;
}Fir[MAXN];
struct point{
    int v,w;
};
int D[MAXN];
int C[MAXN];
bool vis[MAXN];
int R[MAXN];
bool tag[MAXN];
bool bj[MAXN];
vector<point> ljb[MAXN];
int dp[MAXN][2];
int num[MAXN][2];
int id[MAXN];
void init(){
    scanf("%lld%lld",&n,&q);
    P.init();
    for(int i=1;i<=n;i++){
        int v,a,b;
        scanf("%lld%lld%lld",&v,&a,&b);
        Fir[i]=node{v,a,b};
    }
    for(int i=1;i<=q;i++){
        int p,k;
        scanf("%lld%lld",&p,&k);
        while(k--){
            int x;
            scanf("%lld",&x);
            P.father[x]=p;
        }
    }
    return;
}
void addedge(int u,int v,int w){
    cnt++;
    E[cnt].v=v;
    E[cnt].w=w;
    E[cnt].nxt=head[u];
    head[u]=cnt;
    return;
}
void getE(){
    map<pair<int,int>,bool> mp;
    for(int i=1;i<=n;i++){
        if(P.father[i]==i){
            int u=i;
            int v=P.find(Fir[i].a);
            if(u>v)swap(u,v);
            if(mp[mkpr(u,v)]){
                int tmp=i^u^v;
                C[i]=C[tmp]^1;
                continue;
            }
            if(u==v)continue;
            mp[mkpr(u,v)]=true;
            addedge(u,v,0);
            addedge(v,u,0);
            C[i]=cnt-1;
        }
    }
    for(int i=1;i<=n;i++){
        int v1=P.find(Fir[i].a);
        int v2=P.find(Fir[P.find(i)].a);
        if(v1==v2){
            int fx=P.find(i);
            int e=C[fx];
            E[e].w+=Fir[i].b;
            E[e^1].w+=Fir[i].b;
        }
    }
    return;
}
void getD(){
    for(int i=1;i<=n;i++){
        D[P.find(i)]+=Fir[i].v;
    }
    for(int i=1;i<=n;i++){
        int fx=P.find(i);
        int v=P.find(Fir[i].a);
        if(v==fx){
            D[fx]-=Fir[i].b;
        }
    }
    return;
}
void getnew(){
    vector<int> A;
    for(int i=1;i<=n;i++){
        if(P.find(i)==i)A.push_back(i);
    }
    for(int i=0;i<A.size();i++){
        id[A[i]]=i+1;
    }
    for(int i=0;i<A.size();i++){
        int tmp=A[i];
        D[id[tmp]]=D[tmp];
        for(int j=head[tmp];j;j=E[j].nxt){
            int v=E[j].v;
            int w=E[j].w;
            ljb[id[tmp]].push_back(point{id[v],w});
        }
    }
    n=A.size();
    return;
}
void getR(){
    for(int i=1;i<=n;i++){
        for(int j=0;j<ljb[i].size();j++){
            int v=ljb[i][j].v;
            R[v]++;
        }
    }
    return;
}
vector<point> cir;
bool pos[MAXN];
void find(int cur,int fa,int w){
    cir.push_back(point{cur,w});
    pos[cur]=true;
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i].v;
        int w=ljb[cur][i].w;
        if(v==fa)continue;
        if(!pos[v]&&vis[v]){
            find(v,cur,w);
            break;
        }
        if(pos[v])cir[0].w+=w;
    }
    return;
}
void gettag(int cur){
    bj[cur]=true;
    tag[cur]=true;
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i].v;
        if(!tag[v])gettag(v);
    }
    return;
}
void getcir(int S){
    for(int i=1;i<=n;i++)tag[i]=false;
    cir.clear();
    gettag(S);
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(R[i]==1&&tag[i])q.push(i);
        vis[i]=false;
    }
    while(!q.empty()){
        int t=q.front();
        vis[t]=true;
        q.pop();
        for(int i=0;i<ljb[t].size();i++){
            int v=ljb[t][i].v;
            R[v]--;
            if(vis[v])continue;
            if(R[v]==1)q.push(v);
        }
    }
    for(int i=1;i<=n;i++){
        vis[i]^=1;
    }
    for(int i=1;i<=n;i++){
        if(vis[i]&&tag[i]){
            find(i,0ll,0ll);
            break;
        }
    }
    return;
}
void getDP(int cur,int fa){
    dp[cur][0]=0;
    dp[cur][1]=D[cur];
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i].v;
        int w=ljb[cur][i].w;
        if((v^fa)&&!vis[v]){
            getDP(v,cur);
            dp[cur][0]+=max(dp[v][0],dp[v][1]);
            dp[cur][1]+=max(dp[v][0],dp[v][1]-w);
        }
    }
    return;
}
void getG(){
    init();//读入
    getE();//建边
    getD();//建点
    getnew();//重置整张图
    getR();//统计度数方便拓扑
    return;
}
int getans(){
    int ans=0;
    for(int i=1;i<=n;i++){
        if(bj[i])continue;
        getcir(i);//找环，塞进cir数组里面
        int len=cir.size();
        if(len==0){//无环，树，直接跑树形dp
            getDP(i,0);
            ans+=max(dp[i][0],dp[i][1]);
            continue;
        }
        for(point S:cir){//处理挂在环上的子树
            getDP(S.v,0);
        }
        int sum1=0;
        int sum2=0;
        num[0][0]=dp[cir[0].v][0];//强制起点不取
        num[0][1]=-1e18;
        for(int i=1;i<cir.size();i++){
            num[i][0]=max(num[i-1][0],num[i-1][1])+dp[cir[i].v][0];
            num[i][1]=max(num[i-1][0],num[i-1][1]-cir[i].w)+dp[cir[i].v][1];
        }
        sum1=max(num[len-1][0],num[len-1][1]);
        num[0][1]=dp[cir[0].v][1];//强制起点取
        num[0][0]=-1e18;
        for(int i=1;i<len;i++){
            num[i][0]=max(num[i-1][0],num[i-1][1])+dp[cir[i].v][0];
            num[i][1]=max(num[i-1][0],num[i-1][1]-cir[i].w)+dp[cir[i].v][1];
        }
        sum2=max(num[len-1][0],num[len-1][1]-cir[0].w);
        ans+=max(sum1,sum2);
    }
    return ans;
}
int solve(){
    getG();//建立新图
    return getans();
}
signed main(){
    printf("%lld\n",solve());
    return 0;
}
```

我的写法比较愚蠢，要开 O2 才能过，这里仅作参考。

---

## 作者：leihonglongyin (赞：2)

## 题解时间

### subtask 1

一个简单的环套树 DP。

每个关系一都建 $ 1 $ 条边，然后正常地 DP 就行了。

DP 就很简单，一个使用根，一个不使用根，然后取 max。

最后所有基环树的 asw 之和即为所求。

### subtask 2

在 subtask 2 的基础上有了关系二。

因为每个系列都要一起选，所以就从选点变成了选系列，所以可以把每个系列的所有点都缩成一个点，每个系列的权值为其中所有的烟花的权值之和。(没有系列的烟花当成一个系列，主烟花为自己)

其中的每个烟花的关系一，如果与主烟花的关系一是一个系列的，就把这两个系列之间的边的权值加上这个关系一的权值。如果这个烟花的关系一与这个烟花是同一个系列的，就把这个系列的权值减去这个关系一的权值。

用并查集找环，但有可能一个系列的主烟花的关系一与这个烟花为同一个系列，所以这是一个 树加基环树 森林。再利用建反边，便可解决问题。

把有入度的点标记一下，这样没别标记的点为一个树的根，再在找到环的时候把两个点记录下来，作为基环树的根，最后依次 DP，把每次得到的结果加和，就是答案。

**注：记得开 long long.**

最后附上 std:
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
vector<int>mm[500001];
struct nood {
	int to,next;
	long long v;
} g[1000001];
int num,m,top,cnt,n,fa[500001],fa1[500001],a[500001];
int xx[500001],root[500001],di[500001],zhi[500001],zhu[500001];
long long ans,f[500001][2],v[500001],vv[500001],ji[500001];
bool vi[500001];
char hhd;
inline void read1(int &k) {
	k=0,hhd=getchar();
	while(hhd>'9'||hhd<'0') hhd=getchar();
	while(hhd<='9'&&hhd>='0') k=k*10+hhd-'0',hhd=getchar();
}
inline void read2(long long &k) {
	k=0,hhd=getchar();
	while(hhd>'9'||hhd<'0') hhd=getchar();
	while(hhd<='9'&&hhd>='0') k=k*10+hhd-'0',hhd=getchar();
}
inline int get(int u) {
	if(fa[u]==u) return u;
	return fa[u]=get(fa[u]);
}
inline void dfs(int u) {
	f[u][1]=v[u];
	for(int i=a[u]; i; i=g[i].next) {
		int j=g[i].to;
		dfs(j);
		f[u][0]+=max(f[j][0],f[j][1]);
		f[u][1]+=max(f[j][0],f[j][1]-g[i].v);
	}
}
inline void dfs1(int u,int k) {
	f[u][1]=v[u];
	for(int i=a[u]; i; i=g[i].next) {
		int j=g[i].to;
		dfs1(j,k);
		if(j==di[k]) {
			f[u][0]+=max(f[j][0],f[j][1]-zhi[k]);
			f[u][1]+=max(f[j][0],f[j][1]-g[i].v-zhi[k]);
			continue;
		}
		f[u][0]+=max(f[j][0],f[j][1]);
		f[u][1]+=max(f[j][0],f[j][1]-g[i].v);
	}
}
int main() {
	read1(n),read1(m);
	for(int i=1; i<=n; i++) read2(vv[i]),read1(xx[i]),read2(ji[i]);
	for(int k,i=1; i<=m; i++) {
		read1(zhu[++num]),read1(k),fa[i]=num;
		for(int kk,j=1; j<=k; j++) {
			read1(kk),fa1[kk]=i,v[i]+=vv[kk],mm[i].push_back(kk);
		}
	}
	for(int i=1; i<=n; i++) if(!fa1[i]) {
			zhu[++num]=i,fa1[i]=num,fa[num]=num;
			v[num]=vv[i],mm[num].push_back(i);
		}
	for(int i=1; i<=num; i++) {
		int res=0,y=fa1[xx[zhu[i]]];
		for(int j=0; j<mm[i].size(); j++) {
			int x=fa1[xx[mm[i][j]]];
			if(i==x) v[x]-=ji[mm[i][j]];
			else if(y==x) res+=ji[mm[i][j]];
		}
		if(i==y) continue;
		vi[i]=1;
		if(get(i)==get(y)) root[++top]=i,di[top]=y,zhi[top]=res;
		else {
			fa[fa[i]]=fa[y],g[++cnt].v=res,g[cnt].to=i;
			g[cnt].next=a[y],a[y]=cnt;
		}
	}
	for(int i=1; i<=num; i++) if(!vi[i]) dfs(i),ans+=max(f[i][1],f[i][0]);
	for(int kk=1; kk<=top; kk++) {
		long long asw=0;
		dfs1(root[kk],kk),asw=f[root[kk]][1],memset(f,0,sizeof(f));
		dfs(root[kk]),asw=max(asw,f[root[kk]][0]),ans+=asw;
	}
	printf("%lld",ans);
}
```

---

## 作者：柳易辰 (赞：0)

## Subtask 1

将 $a_i$ 向 $i$ 连边，边权为 $b_i$，点权为 $v_i$，如果一条边相连的两个点都被选，权值需要减掉 $b_i$，求选点方案的最大权值。

题目提示的很明显，图是基环树森林。我们对每棵基环树处理即可。

显然我们需要 DP，分别考虑树和环怎么做。树的话可以设 $f_{p,0/1}$ 表示以 $p$ 为根的子树，点 $p$ 选 / 不选的最大权值，容易转移。环的话需要钦定破环为链，钦定链一端的状态，设 $g_{p,0/1}$ 进行类似的 DP，也容易转移。



## Subtask 2

引入了“点必须一起选”的限制，并且给出了特殊条件。

特殊条件的意思是，对于 $S_1$ 的点，只有连在 $S_1$ 内部或者 $S_1-S_2$ 之间的边才算数。提示的也很明显，把一组点合并成一个点进行处理。

需要注意：$S_1-S_2$ 的边权要累加，$S_1$ 内部的边需要减在点权上，这样可能会出现一个点没有入边，即树的情况，需要特判。剩下的就跟 Subtask 1 一样了。

---

