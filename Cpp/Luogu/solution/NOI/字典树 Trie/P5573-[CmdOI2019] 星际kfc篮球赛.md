# [CmdOI2019] 星际kfc篮球赛

## 题目背景

公元 $3100$ 年，地球联盟的银河系内 $N$ 个星球已经完成了道路大建设，从原来的 $N-1$ 条双向时空隧道变成了**无向完全图**。

Louis Paosen 是一个星际旅行家，上次你~~虐队的时候~~顺便帮他解决了难题，于是他又来请求你帮忙啦。

## 题目描述

仍然是出于资金的考虑，地球联盟没能将所有的道路都建造得尽善尽美。通过某条道路**对于飞船的性能有一定的要求**。

Louis Paosen 在联盟内举办了盛大的 kfc 三人篮球赛，一时间，许多来自不同星球的选手纷纷赶来参赛。

整个地球联盟的内部正在热卖三种飞船 (A/B/C 类)，由于收了广告费的缘故，组队的时候要求 $3$ 人中第一人使用 A，第二人使用 B，第三人使用 C (这样可以获得加分)。

现在有许许多多个三人小组准备参赛，他们准备好了飞船(符合加分条件)，但是他们可能来自不同的星球，由于飞船性能的限制，他们可能无法一起到达某个星球。

由于这三家公司制造工艺大相径庭，飞船对同一条道路环境的耐受力区别很大，而有奇怪的规律。

点 $u$ 有三组系数 $P_A[u],P_B[u],P_C[u]$ ，边 $u\leftrightarrow v$ 的通过难度为:

$$\begin{cases}\text{A形飞船通过难度}=P_A[u]\ {\rm xor}\ P_A[v]\\\text{B形飞船通过难度}=P_B[u]\ {\rm xor}\ P_B[v]\\\text{C形飞船通过难度}=P_C[u]\ {\rm xor}\ P_C[v]\end{cases}$$

当一个飞船的性能指数不低于某条边对应种类的通过难度时,这个飞船才能够通过 (具体见样例解释)。

Louis Paosen 在每个星球上都准备了比赛点，所以你只要对每个三人小组，给出其可行的集合点个数就好了。

## 说明/提示

| 　编号　 | 　　n　　 | 　　q　　 | ① | ② | ③ |
| :--: | :--: | :--: | :--: | :--: | :--: |
| #1-3 | $100$ | $100$ | - | - | - |
| #4 | $4\times 10^4$ | $4\times 10^4$ | * | * | * |
| #5 | $4\times 10^4$ | $4\times 10^4$ | * | * | - |
| #6 | $4\times 10^4$ | $4\times 10^4$ | * | - | * |
| #7 | $4\times 10^4$ | $4\times 10^4$ | * | - | - |
| #8 | $4\times 10^4$ | $4\times 10^4$ | - | - | - |
| #9 | $4\times 10^4$ | $8\times 10^4$ | - | - | * |
| #10~13 | $4\times 10^4$ | $8\times 10^4$ | - | - | - |

- 性质①：$P_C[1\sim n]$ 都相等；
- 性质②：$P_B[1\sim n]$ 都相等；
- 性质③：$P_A[1\sim n], P_B[1\sim n], P_C[1\sim n]\in \{0,1\}$。

（#1~#9 每个 $6$ 分，#10~#13 共 $46$ 分；#1~#7 空间限制为 500MB，其余测试点空间限制为 125MB）。

所有输入中的数都是 $[0,10^8]$ 内的整数。

### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/gn9va8wd.png)

三张性能图如上。

如 A 图，$\begin{cases}(1,2)=P_A[1]\ {\rm xor}\ P_A[2]=3;\\(1,3)=P_A[1]\ {\rm xor}\ P_A[3]=2;\\(2,3)=P_A[1]\ {\rm xor}\ P_A[2]=1;\end{cases}$

(边的产生方式就是根据三个数组异或)

第一组人:

- 从 $1$ 出发的 A 飞船性能高达 $5$，能到达所有的星球。
- 从 $2$ 出发的 B 飞船性能仅为 $2$，不能经过$(3,2)=3$，但是还能到达所有的星球。
- 从 $3$ 出发的 B 飞船性能仅为 $3$，只能经过$(2,3)=0$，能到达 $2,3$ 号星球。
- 综上，第一组所有人都能到达的星球有 $2$ 个。

## 样例 #1

### 输入

```
3 3
1 2 3
3 2 1
4 2 2
5 1 2 2 3 3
3 3 3 3 3 3
6 3 5 2 3 1```

### 输出

```
2
2
1```

## 样例 #2

### 输入

```
10 10
43 24 8 66 96 25 43 87 62 8 
80 25 94 72 43 18 94 96 11 54 
19 25 92 87 76 36 89 91 69 22 
82 2 82 5 82 3
70 10 96 8 70 8
52 7 23 5 52 10
85 1 62 4 85 5
1 5 49 7 1 6
32 7 54 8 32 9
6 1 89 4 6 10
82 10 38 5 82 7
87 2 1 10 87 2
12 3 77 5 12 8```

### 输出

```
10
7
0
5
0
1
1
5
1
1```

# 题解

## 作者：Y_B_X (赞：4)

[题目链接](https://www.luogu.com.cn/problem/P5573)

>题意:  
给定一张完全图，每两个点 $(i,j)$ 之间有三种边 $A_{(i,j)},B_{(i,j)},C_{(i,j)}$ 。  
其中 $A_{(i,j)}=a_i\operatorname{xor} a_j,B{(i,j)}=b_i\operatorname{xor} b_j,C_{(i,j)}=c_i\operatorname{xor} c_j$。  
每次查询对三种边分别给出一个起点与阀值，  
问从三种图中分别从各自起点开始，经过不大于各自阀值的边到达的点的交集。

这道题几乎是强行拼题。

首先对每张图求出各自的 $\text{Kruskal}$ 重构树，就是[这题](https://www.luogu.com.cn/problem/CF888G)。

从大到小枚举每一位，将这一位为 $0,1$ 的分开考虑，建出将两边各自的 $\text{Kruskal}$ 重构树，然后用 $\text{01trie}$ 查询两边 $\operatorname{xor}$ 得到的最小值，得到当前这层的 $\text{Kruskal}$ 重构树。

正确性是因为每次让大的位出现得尽量小，使位数更低的妥协，而 $2\times 2^{d-1}\leq 2^d$，得到的一定是最优方案之一。

每个点会被查询至多 $\log V$ 次，每次 $\text{01trie}$ 上的点查询需要 $O(\log V)$，这部分总时间为 $O(n\log^2V)$。

注意这样将相同的数分到一份时异或为 $0$，也要建出其重构树。

这之后每次查询就能在 $\text{Kruskal}$ 重构树上，倍增得到能到达的点集所在的 $dfn$ 序范围。

设 $A,B,C$ 三图各自 $dfn$ 序范围是 $[la,ra],[lb,rb],[lc,rc]$。

那查询转为询问满足 $\begin{cases}la\leq dfna_i\leq ra\\lb\leq dfnb_i\leq rb\\lc\leq dfnc_i\leq rc\end{cases}$ 的 $i$ 的个数。

这就是个明显的三维偏序，可以通过三维差分拆成八个询问后，一个 $\text{cdq}$ 分治轻松解决。

这部分时间复杂度为 $O(m\log m\log n)$。

总时间复杂度为 $O(n\log^2V+m\log n\log m)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,K=28;
const int inf=2e8;
int n,m,x,y,nn,tt,v,tot;char ch;
int a[N][3],son[N][2][3],w[N][3];
struct trie{int son[2],sz;}_[N*K];
int _rt,_tot,_v;bool _b;
inline void read(int &x){
	x=0;ch=getchar();while(ch<48)ch=getchar();
	while(ch>47)x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}
void write(int x){if(x>9)write(x/10);putchar(48+x%10);}
void update(int &k,int x,int i){
	if(!k)k=++_tot;++_[k].sz;
	if(~i)update(_[k].son[(x>>i)&1],x,i-1);
}
void inquiry(int k,int x,int i){if(~i){
	_b=(x>>i)&1;
	if(_[_[k].son[_b]].sz)inquiry(_[k].son[_b],x,i-1);
	else _v+=1<<i,inquiry(_[k].son[!_b],x,i-1);
}}
inline void _init(){
	static int i;
	for(i=1;i<=_tot;++i)_[i].son[0]=_[i].son[1]=_[i].sz=0;
	_rt=_tot=0;
}
struct node{
	int v,id;node()=default;
	node(int _v,int _id):v(_v),id(_id){}
}p[N],pl[N],pr[N];
inline int build_(int l,int r,int j){
	if(l^r){
		int mid=(l+r)>>1,tmp=++nn;
		son[tmp][0][j]=build_(l,mid,j);
		son[tmp][1][j]=build_(mid+1,r,j);
		return tmp;
	}
	return p[l].id;
}//权值相同时建树 
int build(int l,int r,int d,int j){
	int i;
	if(l^r&&~d){
		int lcnt=0,rcnt=0,tmp;bool b;
		for(i=l;i<=r;++i){
			b=(p[i].v>>d)&1;
			if(b)pr[++rcnt]=p[i];
			else pl[++lcnt]=p[i];
		}
		for(i=1;i<=lcnt;++i)p[l+i-1]=pl[i];
		for(i=1;i<=rcnt;++i)p[r-i+1]=pr[i];
		if(lcnt&&rcnt){
			tmp=++nn;w[tmp][j]=inf;
			son[tmp][0][j]=build(l,l+lcnt-1,d-1,j);
			for(i=r-rcnt+1;i<=r;++i){
				_v=0,inquiry(_rt,p[i].v,K);
				w[tmp][j]=min(w[tmp][j],_v);
			}
			son[tmp][1][j]=build(r-rcnt+1,r,d-1,j);
			return tmp;
		}
		else return build(l,r,d-1,j);
	}
	else {update(_rt,p[l].v,K);return build_(l,r,j);}
}//建kruskal重构树 
int dfn[N][3],dfnr[N][3],rev[N],sz[N][3],f[N][19][3];
void dfs(int x,int anc,int j){
	f[x][0][j]=anc;int i,y;
	for(i=1;i^19;++i)f[x][i][j]=f[f[x][i-1][j]][i-1][j];
	if(y=son[x][0][j])dfs(y,x,j),sz[x][j]+=sz[y][j];
	if(y=son[x][0][j])dfn[x][j]=dfn[y][j];
	if(y=son[x][1][j])dfs(y,x,j),sz[x][j]+=sz[y][j];
	else dfn[x][j]=++tt,sz[x][j]=1;
}
void init(){
	register int i,j,rt;
	for(j=0;j<3;++j){
		for(i=1;i<=n;++i)p[i]=node(a[i][j],i);
		nn=n;rt=build(1,n,K,j);tt=0;dfs(rt,0,j);w[0][j]=inf;
		for(i=1;i<=nn;++i)dfnr[i][j]=dfn[i][j]+sz[i][j]-1;
		_init();
	}
	for(i=1;i<=n;++i)if(sz[i][0]==1)rev[dfn[i][0]]=i;
}
inline int find(int x,int v,int j){
	static int i;
	for(i=18;~i;--i)if(w[f[x][i][j]][j]<=v)x=f[x][i][j];
	return x;
}//倍增 
struct cdq{
	int a,b,c,id;char opt;cdq()=default;//opt=0 : mdf || opt=1,-1 : inq
	cdq(int _a,int _b,int _c,int _id,char _opt):
		a(_a),b(_b),c(_c),id(_id),opt(_opt){}
}q[N<<2],q0[N<<2];
inline bool cmpa(cdq x,cdq y){return x.a^y.a?x.a<y.a:!x.opt;}
inline bool cmpb(cdq x,cdq y){return x.b^y.b?x.b<y.b:!x.opt;}
int t_[N],ti,res,t[3],ans[N];
#define lowbit(i) i&(-i)
inline void update(int pos,int v){for(ti=pos;ti<=n;ti+=lowbit(ti))t_[ti]+=v;}
inline void inquiry(int pos){res=0;for(ti=pos;ti;ti-=lowbit(ti))res+=t_[ti];}
void solve(int l,int r){if(l^r){
	int mid=(l+r)>>1,i;
	solve(l,mid);solve(mid+1,r);
	merge(q+l,q+mid+1,q+mid+1,q+r+1,q0+l,cmpb);
	for(i=l;i<=r;++i)q[i]=q0[i];
	for(i=l;i<=r;++i){
		if(q[i].opt&&q[i].a>mid)inquiry(q[i].c),ans[q[i].id]+=res*q[i].opt;
		else if(!q[i].opt&&q[i].a<=mid)update(q[i].c,1);
	}
	for(i=l;i<=r;++i)if(!q[i].opt&&q[i].a<=mid)update(q[i].c,-1);
}}//cdq
inline void cdq_add(int i){
	static int la,ra,lb,rb,lc,rc;
	la=dfn[t[0]][0]-1,ra=dfnr[t[0]][0];
	lb=dfn[t[1]][1]-1,rb=dfnr[t[1]][1];
	lc=dfn[t[2]][2]-1,rc=dfnr[t[2]][2];
	q[++tot]=cdq(ra,rb,rc,i,1);q[++tot]=cdq(la,lb,lc,i,-1);
	q[++tot]=cdq(la,rb,rc,i,-1);q[++tot]=cdq(ra,lb,lc,i,1);
	q[++tot]=cdq(ra,lb,rc,i,-1);q[++tot]=cdq(la,rb,lc,i,1);
	q[++tot]=cdq(ra,rb,lc,i,-1);q[++tot]=cdq(la,lb,rc,i,1);
}//三维差分 
main(){
	read(n);read(m);register int i,j;
	for(j=0;j<3;++j)for(i=1;i<=n;++i)read(a[i][j]);
	init();
	for(i=1;i<=m;++i){
		for(j=0;j<3;++j)read(v),read(x),t[j]=find(x,v,j);
		cdq_add(i);
	}
	for(i=1;x=rev[i],i<=n;++i)q[++tot]=cdq(i,dfn[x][1],dfn[x][2],0,0);
	sort(q+1,q+tot+1,cmpa);
	for(i=1;i<=tot;++i)q[i].a=i;
	solve(1,tot);
	for(i=1;i<=m;++i)write(ans[i]),putchar('\n');
}
```


---

## 作者：command_block (赞：2)

# 官方题解:星际kfc篮球赛

这道题是出来防$AK$的,毕竟std码了5.64K。

这是一道丧心病狂的**三合一**毒瘤题……

~~暴力bfs就不讲了~~

这题的部分分都是假的,只是来帮助写到一半的大佬检验代码是否有锅。

所以就直接讲正解吧!

**第一式:** 异或图最小生成树

想必大家看完题目就想到重构树了吧,问题在于大家平时都是用克鲁斯卡尔来求解重构树,这题绕了个弯。

(如果您用异或粽子来实现克鲁斯卡尔,恭喜您被随机数据卡到了$O(n^2)$……)

现在要先求出这个不知叫啥的完全图的最小生成树,再弄出重构树。

看到$xor$就想到贪心?

首先把点按照权值塞进01Trie里面。

考虑如下图:

```cpp

    *
  0/ \1
  /   \
 l     r
...   ...

```

现在左子树中还有某两个节点没联通,你选择:

1.连向右子树,反正右子树后来也要与左子树联通的。

2.连向左子树。

连向左子树一定要比连向右子树优,因为左右子树有一个很高的位不同,异或起来很吃亏。

这就有了一个结论:子树内能连边尽量连边,也就是说路过上述图的时候只需要把左右子树间连一条代价最小的边就好了,这可以一边dfs一边做。

如何找到代价最小的那条边?我们把size小的子树里的点都取出来,一个个询问对面的xor最小值就好了(启发式合并),复杂度$O(nlog^2n)$。

**P.S:** 如果遇到权值相同的点直接连上就好,反正代价为0,可以省去很多细节。

**第二式:** 克鲁斯卡尔重构树

见[P4768 [NOI2018]归程](https://www.luogu.org/problemnew/show/P4768)

看到满足$>=$的边都可以走,我们毫不犹豫搞出重构树。

(注意要把边排序)

对三张性能图如法炮制就可以弄出三颗重构树了。

**第三式:** 差分莫队

类似的一道题目[P5268 [SNOI2017 / THUWC2019]一个简单的询问](https://www.luogu.org/problemnew/show/P5268)

我们得到了三棵树。

我们按照重构树的套路求出一颗子树,那么这棵子树中的所有点都是可达的。

我们把三棵**子树**求个交即可。

(如果是两棵树貌似离线树状数组/主席树就好)

我们把三棵树弄出欧拉序(**三棵树都变成序列了**),前两棵树的编号根据第三棵树的欧拉序映射。

然后把前两棵树的两个子树对应的区间的映射结果++,和为2的就是前两棵树的交。

然后在第三棵树上区间统计2的个数即可。

这是可以莫队+分块维护的。

第一课子树$[l1,r1]$,第二棵$[l2,r2]$,貌似要维护4个指针。

这是满足差分的,所以(二维)差分以下变成4个询问,就只用维护两个指针了。

复杂度$O(n\sqrt{n})$,由于异或图的毒瘤性质根本造不出非随机的数据,虽然有分块常数,但还是跑得飞快。

大常数(log部分)标程:

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<ctime>
#define MaxN 40500
#define MaxT 80500
using namespace std;
namespace IO
{
    const unsigned int Buffsize=1<<15;
    static char Ch[Buffsize],*S=Ch,*T=Ch;
    inline char getc()
    {
        return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
    }
    inline int read()
    {
      int X=0;char ch=0,minus=0;
      while(ch<48||ch>57)ch=getc(),minus|=ch=='-';
      while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getc();
      return minus ? -X:X;
    }

}using namespace IO;

int n,q;
struct Line
{int f,t,c;};
bool cmpLine(Line A,Line B)
{return A.c<B.c;}
struct BCJ
{
  int f[MaxT];
  void Init()
  {for (int i=1;i<=n+n;i++)f[i]=i;}
  int findf(int x)
  {return f[x]==x ? x :f[x]=findf(f[x]);}
  bool check(int x,int y)
  {
    x=findf(x);y=findf(y);
    return x==y;
  }
  inline void marge(int x,int y)
  {f[x]=y;}
};
struct KlTree
{
  Line l[MaxN];BCJ S;
  int in[MaxT],out[MaxT],id[MaxT],tim,tot;
  int f[MaxT][17],cc[MaxT];
  vector<int> g[MaxT];
  void dfs(int num)
  {
    in[num]=tim;
    if (num<=n)id[num]=tim++;
    for (int i=0,v;i<g[num].size();i++)
     if (!in[v=g[num][i]])
      dfs(v);
    out[num]=tim-1;
  }
  void build()
  {
    S.Init();tot=n;tim=1;
    sort(l+1,l+n,cmpLine);
    for (int i=1,u,v;i<n;i++)
     if (!S.check(u=l[i].f,v=l[i].t)){
       cc[++tot]=l[i].c;
       S.marge(u=S.findf(u),tot);
       S.marge(v=S.findf(v),tot);
       f[u][0]=f[v][0]=tot;
       g[u].push_back(tot);
       g[v].push_back(tot);
       g[tot].push_back(u);
       g[tot].push_back(v);
     }
    dfs(tot);
    for (int j=1;j<16;j++)
     for (int i=1;i<=n+n;i++)
      f[i][j]=f[f[i][j-1]][j-1];
    cc[0]=1<<30;
  }
  inline Line up(int x,int lim)
  {
    int k=16;
    while(k--)
      while(cc[f[x][k]]<=lim)
        x=f[x][k];
    return (Line){in[x],out[x]};
  }
}ka,kb,kc;
struct Trie_Node
{int l,r,c;};
int aaa;
struct Trie_Graph
{
  Trie_Node t[MaxN*29];
  Line *l;
  int tn,tot;
  void clear(Line *arr)
  {
    memset(t,0,sizeof(Trie_Node)*(tn+5));
    tn=1;l=arr;tot=0;
  }
  void add(int num,int x,int pos)
  {
    for (int i=1<<27;i;i>>=1){
      aaa++;
      t[num].c++;
      if (x&i){
      	if (!t[num].r)t[num].r=++tn;
    	  num=t[num].r;
    	}else {
    	  if (!t[num].l)t[num].l=++tn;
    	  num=t[num].l;
    	}
    }
    if (t[num].c)
      l[++tot]=(Line){t[num].c,pos,0};
    else t[num].c=pos;
  }
  void query(int num,int x,int d,int from)
  {
    if (d==-1){
      tl=(Line){from,t[num].c,0};
      return ;
    }int ansx=0;
    for (int i=1<<d;i;i>>=1){
      if (x&i)if (t[num].r){num=t[num].r;ansx|=i;}
        else num=t[num].l;
      else if (!t[num].l){num=t[num].r;ansx|=i;}
        else num=t[num].l;
      }
    x^=ansx;
    if (x<minn){
      minn=x;
      tl=(Line){from,t[num].c,x};
    }
  }
  int minn;
  Line tl;
  void tmarge(int num,int qnum,int d,int val,int sd)
  {
    if (d==-1)query(qnum,val,sd,t[num].c);
    if (t[num].l)tmarge(t[num].l,qnum,d-1,val,sd);
    if (t[num].r)tmarge(t[num].r,qnum,d-1,val|(1<<d),sd);
  }
  void dfs(int num,int d)
  {
    if (d==-1)return ;
    if (t[num].l)dfs(t[num].l,d-1);
    if (t[num].r)dfs(t[num].r,d-1);
    if (!t[num].l||!t[num].r)return ;
    minn=1<<30;
    if (t[t[num].l].c<t[t[num].r].c)
      tmarge(t[num].l,t[num].r,d-1,0,d-1);
    else tmarge(t[num].r,t[num].l,d-1,0,d-1);
    tl.c+=1<<d;
    l[++tot]=tl;
  }
}t;
int sav[MaxT];
void buildTree()
{
  t.clear(ka.l);
  for (int i=1;i<=n;i++)t.add(1,read(),i);
  t.dfs(1,27);
  t.clear(kb.l);
  for (int i=1;i<=n;i++)t.add(1,read(),i);
  t.dfs(1,27);
  t.clear(kc.l);
  for (int i=1;i<=n;i++)t.add(1,read(),i);
  t.dfs(1,27);
  ka.build();kb.build();kc.build();
  for (int i=1;i<=n;i++)sav[ka.id[i]]=i;
  for (int i=1;i<=n;i++)ka.id[i]=kc.id[sav[i]];
  for (int i=1;i<=n;i++)sav[kb.id[i]]=i;
  for (int i=1;i<=n;i++)kb.id[i]=kc.id[sav[i]];
}
int ans[MaxT];
struct Data
{int p1,p2,l,r,pos;}
b[MaxT<<2];
int tn,BS;
bool cmpData(Data A,Data B)
{return A.p1/BS==B.p1/BS ? A.p2<B.p2 : A.p1<B.p1;}
int o[MaxN],bo[MaxN],nBS;
inline void add(int pos)
{
  o[pos]++;
  bo[(pos-1)/nBS]+=o[pos]==2;
}
inline void del(int pos)
{
  bo[(pos-1)/nBS]-=o[pos]==2;
  o[pos]--;
}
void moQueue()
{
  while(BS*BS<=q)BS++;
  while(nBS*nBS<=n)nBS++;
  BS=n/BS+10;nBS+=10;
  sort(b+1,b+tn+1,cmpData);
  int p1=0,p2=0,ll,rr,sum;
  for (int i=1;i<=tn;i++){
    while(b[i].p1<p1)del(ka.id[p1--]);
    while(p1<b[i].p1)add(ka.id[++p1]);
    while(b[i].p2<p2)del(kb.id[p2--]);
    while(p2<b[i].p2)add(kb.id[++p2]);
    sum=0;
    if (b[i].r-b[i].l<=2*nBS){
      for (int j=b[i].l;j<=b[i].r;j++)if (o[j]==2)sum++;
    }else {
      ll=(b[i].l-1)/nBS+1;rr=(b[i].r-1)/nBS;
      for (int j=b[i].l;j<=ll*nBS;j++)if (o[j]==2)sum++;
      for (int j=rr*nBS+1;j<=b[i].r;j++)if (o[j]==2)sum++;
      for (int j=ll;j<rr;j++)sum+=bo[j];
    }if (b[i].pos<0)ans[-b[i].pos]-=sum;
    else ans[b[i].pos]+=sum;
  }
}
int main()
{
  n=read();q=read();
  buildTree();
  Line la,lb,lc;
  for (int i=1,A,B,C,u;i<=q;i++){
    A=read();u=read(); la=ka.up(u,A);
    B=read();u=read(); lb=kb.up(u,B);
    C=read();u=read(); lc=kc.up(u,C);
    la.f--;lb.f--;
    b[++tn]=(Data){la.f,lb.f,lc.f,lc.t,i};
    b[++tn]=(Data){la.t,lb.f,lc.f,lc.t,-i};
    b[++tn]=(Data){la.f,lb.t,lc.f,lc.t,-i};
    b[++tn]=(Data){la.t,lb.t,lc.f,lc.t,i};
  }moQueue();
  for (int i=1;i<=q;i++)
    printf("%d\n",ans[i]);
  return 0;
}
```

## 其他解法

@wuzhaoxin 大佬利用bitset来代替第三式中的莫队,成功切题。

然而直接开$n$个完整的bitset空间会炸,考虑把询问存下来,分段用bitset,内存/8,卡着过去了。

具体细节静待大佬发题解……

---

## 作者：Miss_SGT (赞：1)

一篇题解中提到的 bitset 做法。
感觉这个题就是两个题拼起来。

首先就是 $w(u,v) = a_u \oplus a_v$ 的最小生成树，经典的 [CF888G](https://www.luogu.com.cn/problem/CF888G)。
把所有数放到 trie 上，考虑在 trie 树上合并。一个子树内的肯定优先合并，合并左右儿子一定会产生一次连边，把左儿子里的数放进 trie 里，用另一个儿子里的数去查，取最小值即可，时间复杂度 $O(n \log^2 V)$。启发式合并可以做到 $O(n \log n \log V)$ 但是没必要。

对于三个图我们已经把他们的最小生成树上的边求出来了。现在对于询问 $i$ 需要求出把所有 $边权 \le h_{i,j}$ 的边连起来后 $u_{i,j}$ 所在连通块的点集，答案就是三个图的点集的并。可以把询问离线后对每个图用 bitset 动态维护连通块的点集，就做完了？时间复杂度 $O\left( \frac{n(n+q)}{w} \right)$。

然后空间不够，比较经典的方法是设一个块长 $B$，将 $n$ 个点分成 $\frac{n}{B}$ 个块，每次只对一个块做，最后答案加起来。这样空间除以 $\frac{n}{B}$，时间复杂度不变，因为 $\frac{n(n+q)}{w B} \times B = \frac{n(n+q)}{w} $。

最后时间复杂度 $O\left(n \log^2 V + \frac{n(n+q)}{w} + \frac{n(n+q)}{B} \right)$。$B$ 只要不是太小就行，所以我开到了 $B = 2000$。

虽然这个做法复杂度可能不比 cdq 优秀，但是显然可以拓展到 $k$ 个图。


```cpp
#include<bits/stdc++.h>
using namespace std;
bool Miss;
const int N=4e4+1,M=N*28;
int n,q,son[M][2],dfn[M],low[M],xl[N],idx,tot,ptot,son2[M][2];
bitset<2001> S[N];
struct edge{
	int u,v,w;
	inline bool operator<(edge y)const{return w<y.w;}
};
struct DSU{
	int a[N],cnt,f[N];
	edge e[N];
	inline void ins(int x,int fir){
		int p=1;
		for(int i=fir;~i;--i){
			int &to=son2[p][(a[x]>>i)&1];
			if(!to) to=++ptot;
			p=to;
		}
		son2[p][0]=x;
	}
	inline edge query(int x,int mi,int fir){
		int p=1,res=0;
		for(int i=fir;~i;--i){
			bool w=(a[x]>>i)&1;
			if(!son2[p][w]) res|=1<<i,p=son2[p][!w];
			else p=son2[p][w];
			if(res>=mi) return (edge){0,0,1<<30};
		}
		return (edge){x,son2[p][0],res};
	}
	void dfs(int p,int dep){
		if(dep<0) return xl[dfn[p]=low[p]=++idx]=son[p][0],void();
		if(son[p][0]) dfs(son[p][0],dep-1);
		if(son[p][1]) dfs(son[p][1],dep-1);
		if(son[p][0]&&son[p][1]){
			dfn[p]=dfn[son[p][0]],low[p]=low[son[p][1]];
			e[++cnt]=(edge){0,0,1<<30};
			ptot=1;
			for(int i=dfn[son[p][0]];i<=low[son[p][0]];++i) ins(xl[i],dep);
			for(int i=dfn[son[p][1]];i<=low[son[p][1]];++i) e[cnt]=min(e[cnt],query(xl[i],e[cnt].w,dep));
			while(ptot) son2[ptot][0]=son2[ptot][1]=0,--ptot;
		}else{
			int x=son[p][0]^son[p][1];
			dfn[p]=dfn[x],low[p]=low[x];
		}
	}
	inline void init(){
		while(tot) son[tot][0]=son[tot][1]=0,--tot;
		tot=1;idx=0;
		for(int i=1;i<=n;++i){
			int p=1;
			for(int j=27;~j;--j){
				int &to=son[p][(a[i]>>j)&1];
				if(!to) to=++tot;
				p=to;
			}
			if(son[p][0]) e[++cnt]={son[p][0],i,0};
			else son[p][0]=i;
		}
		dfs(1,27);
		sort(e+1,e+cnt+1);
	}
	inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
	int cur;
	inline void init(int l,int r){
		cur=1;
		for(int i=1;i<=n;++i){
			S[i].reset();
			f[i]=i;
			if(l<=i&&i<=r) S[i][i-l]=1;
		}
	}
	inline void sol(int lim){
		while(cur<=cnt&&e[cur].w<=lim){
			int x=find(e[cur].u),y=find(e[cur].v);++cur;
			f[y]=x;
			S[x]|=S[y];
		}
	}
}T[3]; 
bitset<2001> Q[N<<1];
int ans[N<<1];
edge h[3][N<<1];
bool SGT;
int main(){
	cerr<<(&Miss-&SGT)/1024/1024<<"MB\n";
	read(n),read(q);
	for(int j=0;j<3;++j){
		for(int i=1;i<=n;++i) read(T[j].a[i]);
		T[j].init();
	}
	for(int i=1;i<=q;++i)
	for(int j=0;j<3;++j) read(h[j][i].w),h[j][i].v=i,read(h[j][i].u);
	for(int j=0;j<3;++j) sort(h[j]+1,h[j]+q+1);
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+2000-1,n);
		for(int i=1;i<=q;++i) Q[i].set();
		for(int j=0;j<3;++j){
			T[j].init(l,r);
			for(int i=1;i<=q;++i) T[j].sol(h[j][i].w),Q[h[j][i].v]&=S[T[j].find(h[j][i].u)];
		}
		for(int i=1;i<=q;++i) ans[i]+=Q[i].count();
	}
	for(int i=1;i<=q;++i) print(ans[i]),pc('\n');
	flush();
	return 0;
}
```

---

