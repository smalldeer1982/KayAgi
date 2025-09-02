# [IOI 2008] Pyramid Base

## 题目描述

你要在自己财力许可的范围内寻找一个尽可能大的地方，以便兴建一个新的金字塔。为帮助你作出决定，为你提供了土地测绘图。为方便起见，该地块被划分为由$M\times N$个小正方形构成的网格。金字塔的地基部份必须是正方形，而且各边要与这些方格平行。

测绘图中标出了$P$个有可能重叠的障碍物，这些障碍物是上述网格上的长方形，其各边与方格平行。为了建造金字塔，任何塔基所占方格中的障碍物必须被移走。移除障碍物$i$需要付出成本$C_i$。当移除一个障碍物时，需要将障碍物整个地移除，即不能只移除障碍物的一部份。同时，移除一个障碍物对与其重叠的其他障碍物无任何影响。

已知测绘图中$M$和$N$的大小，对$P$个障碍物的描述，移走每个障碍物的成本以及你的预算$B$。编写程序，找出在移走障碍物总成本不超过$B$的前提下金字塔地基的最大边长。 



## 说明/提示

### 样例说明

样例1：

![](https://cdn.luogu.com.cn/upload/pic/20909.png )

样例2：

![](https://cdn.luogu.com.cn/upload/pic/20910.png )

### 数据范围

程序用三组不相交的数据进行评测。以下限制适用于所有的测试数据： $1 \leq M, N \leq 1,000,000$ 网格的尺寸。 $1 \leq Ci \leq 7,000$ 移除障碍物i的成本。 对每个障碍物$i$均有 $1 \leq X_{i1} \leq X_{i2} \leq M$ 并且 $1 \leq Y_{i1} \leq Y_{i2}\leq N$。 

第一组测试总分值35分： 

- $B = 0$ ——可以付出的最大成本。（不可移除任何障碍物）
- $1\leq P \leq 1,000$ ——网格中障碍物的数目。

第二组测试总分值35分：

- $0 < B \leq 2,000,000,000$ ——你的预算。

- $1\leq P \leq 30,000$ ——网格中障碍物的数目。 

第三组测试值30分：

- $B = 0$ ——你的预算。（不可以移除任何障碍物）

- $1\leq P \leq 400,000$ ——网格中障碍物的数目。 

## 样例 #1

### 输入

```
6 9
42
5
4 1 6 3 12
3 6 5 6 9
1 3 3 8 24
3 8 6 9 21
5 1 6 2 20```

### 输出

```
4```

## 样例 #2

### 输入

```
13 5
0
8
8 4 10 4 1
4 3 4 4 1
10 2 12 2 2
8 2 8 4 3
2 4 6 4 5
10 3 10 4 8
12 3 12 4 13
2 2 4 2 21```

### 输出

```
3```

# 题解

## 作者：miaokehao (赞：12)

#### 首先考虑B=0的情况
#### B=0时数据要求一个nlogn的算法，用扫描线维护第i列到第j列的最大空出的距离，若大于j-i+1，那么说明什么呢？我们可以右移j。当我们改变i时，又可以发现如果i到j是满足要求的，那么i+1到j也是满足要求的。于是尺取法+线段树成功得到65分
```
namespace Subtask1
{
  vector<pi > st[N],ed[N];
  namespace T
  {
#define ls (now<<1)
#define rs (now<<1|1)
    struct papa
    {
      int maxn,lmax,rmax,tag,len;
      papa():tag(0) {};
    } tr[N<<2];
    inline void pushup(res now)
    {
      if(tr[now].tag)
      {
        tr[now].lmax=tr[now].rmax=tr[now].maxn=0;
        return;
      }
      if(tr[now].len==1)
      {
        tr[now].lmax=tr[now].rmax=tr[now].maxn=1;
        return;
      }
      if(tr[ls].lmax==tr[ls].len)
        tr[now].lmax=tr[ls].lmax+tr[rs].lmax;
      else
        tr[now].lmax=tr[ls].lmax;
      if(tr[rs].rmax==tr[rs].len)
        tr[now].rmax=tr[rs].rmax+tr[ls].rmax;
      else
        tr[now].rmax=tr[rs].rmax;
      tr[now].maxn=max(tr[ls].rmax+tr[rs].lmax,max(tr[ls].maxn,tr[rs].maxn));
    }
    void build_up(res now,res l,res r)
    {
      tr[now].maxn=tr[now].lmax=tr[now].rmax=tr[now].len=r-l+1;
      if(l==r)
        return;
      res mid=l+r>>1;
      build_up(ls,l,mid);
      build_up(rs,mid+1,r);
    }
    void update(res now,res l,res r,res ql,res qr,res c)
    {
      if(ql<=l&&r<=qr)
      {
        tr[now].tag+=c;
        pushup(now);
        return;
      }
      res mid=l+r>>1;
      if(mid>=ql) update(ls,l,mid,ql,qr,c);
      if(mid<qr) update(rs,mid+1,r,ql,qr,c);
      pushup(now);
    }
  }
  inline void MAIN()
  {
    for(res i=1; i<=p; i++)
    {
      res A=read(),B=read(),C=read(),D=read(),k=read();
      st[A].push_back(make_pair(B,D));
      ed[C].push_back(make_pair(B,D));
    }
    T::build_up(1,1,m);
    res j=0;
    for(res i=1; i<=n; i++)
    {
      for(; T::tr[1].maxn>=j-i+1&&j<=n;)
      {
        j++;
        for(res k=0; k<st[j].size(); k++)
          T::update(1,1,m,st[j][k].fi,st[j][k].se,1);
      }
      for(res j=0; j<ed[i].size(); j++)
        T::update(1,1,m,ed[i][j].fi,ed[i][j].se,-1);
      ans=max(ans,j-i);
    }
    printf("%d\n",ans);
  }
}
```
#### 现在考虑B>0的情况，二分答案是显然的。
#### 之后我们可以再次使用扫描线，枚举每一列，用线段树维护每一行作为左上角的最小代价，则第一个节点就可以表示这一列的最小代价。每次一个矩形的覆盖，我们可以看成两次区间覆盖，{(x1,y1),(x2,y2)}影响的范围是{（x1-l+1,x2）,(y1-l+1),y2}(l为二分的长度)
```
namespace Subtask2
{
  int ans;
  struct papa1
  {
    int A,B,C,D,k;
  } a[N];
  struct papa
  {
    int l,r,w;
    papa():w(0) {};
    papa(int l0,int r0,int w0):l(l0),r(r0),w(w0) {};
  };
  vector<papa> st[N],ed[N];
  namespace T
  {
#define lson (now<<1)
#define rson (now<<1|1)
    int tr[N<<2],tag[N<<2];
    inline void build_up(res now,res l,res r)
    {
      tag[now]=tr[now]=0;
      if(l==r) return;
      res mid=l+r>>1;
      build_up(lson,l,mid);
      build_up(rson,mid+1,r);
    }
    inline void pushdown(res now)
    {
      if(!tag[now]) return;
      tag[lson]+=tag[now];
      tag[rson]+=tag[now];
      tr[lson]+=tag[now];
      tr[rson]+=tag[now];
      tag[now]=0;
    }
    inline void pushup(res now)
    {
      tr[now]=min(tr[lson],tr[rson]);
    }
    inline void update(res now,res l,res r,res ql,res qr,res c)
    {
      if(ql<=l&&r<=qr)
      {
        tag[now]+=c;
        tr[now]+=c;
        return;
      }
      pushdown(now);
      res mid=l+r>>1;
      if(mid>=ql) update(lson,l,mid,ql,qr,c);
      if(mid<qr) update(rson,mid+1,r,ql,qr,c);
      pushup(now);
    }
  }
  inline bool check(res l)
  {
    for(res i=1; i<=n-l+1; i++)
      st[i].clear(),ed[i].clear();
    T::build_up(1,1,m-l+1);
    for(res i=1; i<=p; i++)
    {
      res A=a[i].A-l+1,B=a[i].B-l+1,C=a[i].C,D=a[i].D,k=a[i].k;
      A=max(A,1),B=max(B,1);
      C=min(C,n-l+1),D=min(D,m-l+1);
      if(A>C||B>D) continue;
      st[A].push_back(papa(B,D,k));
      ed[C].push_back(papa(B,D,-k));
    }
    for(res i=1; i<=n-l+1; i++)
    {
      for(res j=0; j<st[i].size(); j++)
        T::update(1,1,m-l+1,st[i][j].l,st[i][j].r,st[i][j].w);
      if(T::tr[1]<=b)
      {
        //printf("%d %d\n",i,l);
        return 1;
      }
      for(res j=0; j<ed[i].size(); j++)
        T::update(1,1,m-l+1,ed[i][j].l,ed[i][j].r,ed[i][j].w);
    }
    return 0;
  }
  inline void MAIN()
  {
    for(res i=1; i<=p; i++)
      a[i].A=read(),a[i].B=read(),a[i].C=read(),a[i].D=read(),a[i].k=read();
    res l=1,r=min(n,m);
    while(l<=r)
    {
      res mid=l+r>>1;
      if(check(mid)) ans=mid,l=mid+1;
      else r=mid-1;
    }
    printf("%d\n",ans);
  }
}
```

---

## 作者：xtx1092515503 (赞：7)

经 典 二 合 一

------------

首先，我们看到三档部分分：$B=0$ 时，最多障碍数是 $4\times10^5$；而 $B\neq0$ 时，最多障碍数仅有 $3\times10^4$。

这启示我们对于要对于两种情形分开写一个算法。

# $B=0$

此种情形意味着无法消除任何障碍。若我们把障碍看作是矩形赋 $1$ 的话，问题就转换为最大全零正方形。

同用单调栈解决的最大全零矩形不同，最大全零正方形可以使用two-pointers+扫描线+线段树解决。

具体而言，我们考虑固定一个指针 $i$，再设另一个指针 $j<i$。则，我们想知道所有以 $i,j$ 为两边的矩形中，另一维最长的那一个。因为随着 $j$ 的增加，$i-j$ 这一维的长度会不断减小，而另一维的长度会不断增加，所以当正方形边长最大时，一定有两维差最小。于是我们不断增加 $j$，直到另一维的长度大于 $i-j$ 这一维。

现在问题就变成了仅需维护 $i,j$ 间没有任何障碍物的最大子段。因为我们仍然可以把一坨障碍物看作是区间加一，所以问题变为区间加、全局最大全零子段。子段问题只需在线段树上维护左端点、右端点、全局等一大坨玩意然后合并即可，不再赘述。

时间复杂度 $O(n\log n)$。

# $B\neq 0$

此种情形意味着可以消除障碍。但是，因为数据范围明显减少，我们可以思考复杂度更高的算法。

明显金字塔边长具有可二分性。于是我们二分边长。二分边长以后，我们考虑在金字塔的右上角位置储存该金字塔需要消除的障碍的代价和。考虑一个障碍，则其会对其内部，以及其右方上方一定距离（准确说，二分的边长再减一）的位置的金字塔造成影响。于是问题就变成了最小矩形覆盖问题。直接上扫描线维护即可。

时间复杂度 $O(n\log^2n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define y1 __17680321
int n,m,c,q,xx,yy;
vector<int>X,Y;
struct edge{
	int y1,y2,val;
	edge(int a,int b,int c){y1=a,y2=b,val=c;}
};
vector<edge>v[800100];
struct rect{
	int x1,y1,x2,y2,cost;
	void input(){scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&cost),x1--,y1--;}
	void isput(){X.push_back(x1),X.push_back(x2),Y.push_back(y1),Y.push_back(y2);}
	void reput(){
		x1=lower_bound(X.begin(),X.end(),x1)-X.begin();
		x2=lower_bound(X.begin(),X.end(),x2)-X.begin();
		y1=lower_bound(Y.begin(),Y.end(),y1)-Y.begin();
		y2=lower_bound(Y.begin(),Y.end(),y2)-Y.begin();
	}
}r[400100],t[30100];
void discrete(vector<int>&v,int&vv){sort(v.begin(),v.end()),v.resize(vv=unique(v.begin(),v.end())-v.begin()-1);}
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
namespace S1{
	struct SegTree{int tag,mn,len,lval,lln,rval,rln;}seg[3200100];
	void ADD(int x,int y){seg[x].tag+=y,seg[x].mn+=y,seg[x].lval+=y,seg[x].rval+=y;}
	void pushdown(int x){ADD(lson,seg[x].tag),ADD(rson,seg[x].tag),seg[x].tag=0;}
	void pushup(int x,int l,int r){
		seg[x].lval=seg[lson].lval,seg[x].rval=seg[rson].rval;
		if(seg[lson].lln==Y[mid]-Y[l]&&seg[lson].rval==seg[rson].lval)seg[x].lln=seg[lson].lln+seg[rson].lln;
		else seg[x].lln=seg[lson].lln;
		if(seg[rson].rln==Y[r]-Y[mid]&&seg[lson].rval==seg[rson].lval)seg[x].rln=seg[rson].rln+seg[lson].rln;
		else seg[x].rln=seg[rson].rln;
		seg[x].mn=min(seg[lson].mn,seg[rson].mn),seg[x].len=0;
		if(seg[x].mn==seg[lson].mn)seg[x].len=max(seg[x].len,seg[lson].len);
		if(seg[x].mn==seg[rson].mn)seg[x].len=max(seg[x].len,seg[rson].len);
		if(seg[lson].rval==seg[x].mn&&seg[rson].lval==seg[x].mn)seg[x].len=max(seg[x].len,seg[lson].rln+seg[rson].lln);
	}
	void build(int x,int l,int r){
		if(l+1==r){seg[x].lln=seg[x].rln=seg[x].len=Y[r]-Y[l];return;}
		build(lson,l,mid),build(rson,mid,r),pushup(x,l,r);
	}
	void modify(int x,int l,int r,int L,int R,int val){
//		printf("%d %d %d %d %d %d\n",x,l,r,L,R,val);
		if(l>=R||r<=L)return;
		if(L<=l&&r<=R){ADD(x,val);return;}
		pushdown(x),modify(lson,l,mid,L,R,val),modify(rson,mid,r,L,R,val),pushup(x,l,r);
	}
//	void iterate(int x,int l,int r){
//		printf("%d(%d,%d]:MN:%d LN:%d LV:%d LL:%d RV:%d RL:%d\n",x,l,r,seg[x].mn,seg[x].len,seg[x].lval,seg[x].lln,seg[x].rval,seg[x].rln);
//		if(l+1!=r)pushdown(x),iterate(lson,l,mid),iterate(rson,mid,r),pushup(x,l,r);
//	}
	int calc(){
		X.push_back(0),X.push_back(n),Y.push_back(0),Y.push_back(m);
		for(int i=1;i<=q;i++)r[i].isput();
		discrete(X,xx),discrete(Y,yy);
		for(int i=1;i<=q;i++)r[i].reput();
		for(int i=1;i<=q;i++)v[r[i].x1].push_back(edge(r[i].y1,r[i].y2,1)),v[r[i].x2].push_back(edge(r[i].y1,r[i].y2,-1));
		build(1,0,yy);
		int res=0;
		for(int i=0,j=0;i<=xx;i++){
//			printf("%d:%d\n",i,j);
//			iterate(1,0,yy);
//			for(auto k:v[i])printf("(%d,%d,%d)",k.y1,k.y2,k.val);puts("");
			if(!seg[1].mn)res=max(res,min(X[i]-X[j],seg[1].len));
//			printf("SQR:%d %d\n",X[i]-X[j],seg[1].len);
			while(j<i&&(seg[1].mn||seg[1].len<=X[i]-X[j])){
				j++;
				for(auto k:v[j])if(k.val<0)modify(1,0,yy,k.y1,k.y2,k.val);
				res=max(res,min(X[i]-X[j],seg[1].len));
			}
//			puts("IN");
			for(auto k:v[i])if(k.val>0)modify(1,0,yy,k.y1,k.y2,k.val);
		}
		return res;
	}
}
namespace S2{
	struct SegTree{int tag,mn;}seg[240100];
	void ADD(int x,int y){seg[x].tag+=y,seg[x].mn+=y;}
	void pushdown(int x){ADD(lson,seg[x].tag),ADD(rson,seg[x].tag),seg[x].tag=0;}
	void pushup(int x){seg[x].mn=min(seg[lson].mn,seg[rson].mn);}
	void modify(int x,int l,int r,int L,int R,int val){
		if(l>=R||r<=L)return;
		if(L<=l&&r<=R){ADD(x,val);return;}
		pushdown(x),modify(lson,l,mid,L,R,val),modify(rson,mid,r,L,R,val),pushup(x);
	}
	bool che(int ip){
		X.push_back(0),X.push_back(n),Y.push_back(0),Y.push_back(m);
		for(int i=1;i<=q;i++)t[i]=r[i],t[i].x2=min(n,t[i].x2+ip-1),t[i].y2=min(m,t[i].y2+ip-1),t[i].isput();
		discrete(X,xx),discrete(Y,yy);
		for(int i=1;i<=q;i++)t[i].reput();
		for(int i=1;i<=q;i++)v[t[i].x1].push_back(edge(t[i].y1,t[i].y2,t[i].cost)),v[t[i].x2].push_back(edge(t[i].y1,t[i].y2,-t[i].cost));
		int lim=lower_bound(Y.begin(),Y.end(),ip)-Y.begin()-1;
		int mn=0x7f7f7f7f;
		memset(seg,0,sizeof(seg));
		for(int i=0;i<=xx;i++){
			if(X[i]>=ip)mn=min(mn,seg[1].mn);
			for(auto j:v[i])modify(1,lim,yy,j.y1,j.y2,j.val);
		}
		X.clear(),Y.clear();for(int i=0;i<=xx;i++)v[i].clear();
		return mn<=c;
	}
	int calc(){
		int l=0,r=min(n,m);
		while(l<r){
			int md=(l+r+1)>>1;
			if(che(md))l=md;
			else r=md-1;
		}
		return l;
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&c,&q);
	for(int i=1;i<=q;i++)r[i].input();
//	for(int i=0;i<=xx;i++)printf("%d ",X[i]);puts("");
//	for(int i=0;i<=yy;i++)printf("%d ",Y[i]);puts("");
//	for(int i=1;i<=q;i++)printf("%d %d %d %d\n",r[i].x1,r[i].x2,r[i].y1,r[i].y2);
	if(!c)printf("%d\n",S1::calc());
	else printf("%d\n",S2::calc());
	return 0;
}
```



---

## 作者：lzyqwq (赞：0)

为啥这种无脑二合一都做不出来了？哈哈哈，我真菜！

---



**[P4687 [IOI2008] Pyramid Base](https://www.luogu.com.cn/problem/P4687)**

> - 给出一个 $N$ 列 $M$ 行的网格，称 **从左往右** 第 $i$ 列、**从下往上** 第 $j$ 行的网格坐标为 $(i,j)$。有 $P$ 个矩形障碍，第 $i$ 个矩形障碍左下角、右上角坐标分别为 $(X_{i_1},Y_{i_1})$ 和 $(X_{i_2},Y_{i_2})$，移除这个障碍需要 $C_i$ 的代价。小 L 希望在代价和不超过 $B$ 的情况移除一些障碍，并在网格中选取一个边长尽可能大的 **正方形**，满足她和所有障碍无交。
> - Case 1：$P\le 10^3$，$B=0$，$N,M\le 10^6$。
> - Case 2：$P\le 3\times 10^4$，$0<B\le 2\times 10^9$，$N,M\le 10^6$。
> - Case 3：$P\le 4\times 10^5$，$B=0$，$N,M\le 10^6$。


默认 $\mathcal{O}(N)=\mathcal{O}(M)$。

---


**Case 2**

考虑二分。记当前二分的边长为 $L$，考虑对于以 $(L,L)$ 为左下角、$(N,M)$ 为右上角的矩形中的任意一个点维护一个信息（称这个矩形为信息的定义域）：以她为右上角边长为 $L$ 的正方形变得合法需要移除多少个障碍。显然所有与她相交的障碍都要删除。

考虑一个障碍 $i$ 对哪些点产生贡献，则会与这个障碍相交的点的正方形的右上角坐标一定位于以 $(X_{i_1},Y_{i_1})$ 为左下角、$(X_{i_2}+L-1,Y_{i_2}+L-1)$ 为右上角的矩形内（自动对信息的定义域取交）。

此时问题变成平面加，全部加完后求平面最大值。考对列虑扫描线，值域不大不需要离散化。枚举列坐标，维护这一列与上一列的变化量。考虑使用线段树维护区间加、区间最大值，在需要变化的区间上面区间加即可。使用标记永久化会方便一点。加完后，查询 $[L,M]$ 的最大值。注意到此时查询次数为 $\mathcal{O}(N)$ 而修改次数为 $\mathcal{O}(P)$ 二者不对等，可以考虑对 $[L,M]$ 建线段树而非 $[1,M]$，这样变成全局查询，容易 $\mathcal{O}(1)$ 时间。

时间复杂度为 $\mathcal{O}\left(N\log N + P\log^2 N\right)$。



---
**Case 3**

为啥 $4\times 10^5$ 和 $5\,\text{s}$ 会卡上面这个时间复杂度啊，无语。。。

此时 $B=0$ 不能移除任何障碍。考虑将正方形表示成行和列的区间 $[x,y],[i,j]$，满足 $j-i+1=y-x+1$。此时正方形的边长为 $j-i+1$，则求对于 $i$，以她为左边界列的边长最大的正方形可以转化为求最大的右边界列 $j$。

尝试枚举正方形最左边的列 $i$，考虑存在 $[i,j]$ 为列区间的正方形的充要条件。

记 $a_x$ 表示第 $x$ 行 $[i,j]$ 这些列被多少个障碍矩形覆盖，则存在左边界列为 $i$ 右边界列为 $j$ 的正方形，等价于存在长度 $\ge j-i+1$ 的 $a_x$ 全 $0$ 连续段。充分性考虑选择这个连续段任意一个长度为 $j-i+1$ 的子段均能与 $[i,j]$ 构成正方形；必要性考虑 $[x,y]$ 这个行区间就是一个长度 $\ge j-i+1$ 的 $a_x$ 全 $0$ 连续段。

不难发现当 $i$ 变大时，最大的右边界列 $j$ 不降，因为 $i$ 变大时，$a_x$ 不升，因此最长全 $0$ 连续段长度不降。只需选取同一个 $j$ 时，就能得到一个合法的正方形。考虑双指针维护，这部分被细节创飞了。

考虑实现时找到第一个不合法位置的然后她减一就是要求的最大的右边界列 $j$。记当前 **闭区间** 为 $[i,j]$，**此时已经维护好** $[i,j]$ 对应的 $a_x$。若不合法，则退出循环；否则需要维护 $[i,j+1]$ 对应的 $a_x$ 进入下一轮判断。考虑 $[i,j+1]$ 对应的 $a_x$ 会发生哪些变化，显然左边界列为 $j+1$ 的障碍矩形会新覆盖 $[i,j+1]$ 列上其对应的行区间，使得这些 $a_x$ 加 $1$。问题变成区间加、求全局最长全 $0$ 段长度。同样考虑线段树标记永久化维护。注意到任意时刻 $a_x\ge 0$，因此只需要维护区间最长的最小值连续段长度，并判断最小值是否为 $0$ 即可。若两个子节点最小值不同，则继承更小的那个儿子的部分信息；否则类似区间最大子段和那样合并两个孩子的信息。反正是容易合并的。

从 $[1,0]$ 开始双指针即可。

当 $i$ 右移 $1$ 时，也要考虑 $a_x$ 的变化量。显然右边界列为 $i$ 的矩形会少覆盖其 $[i+1,j]$ 上其对应的行区间。$a_x$ 区间减 $1$ 即可。

对于每个 $i$ 计算得到的最大值即为答案。由于指针移动 $\mathcal{O}(N)$ 次且不会重复进行一列的区间修改，因此修改次数的总和与矩形个数同阶为 $\mathcal{O}(P)$。所以时间复杂度为 $\mathcal{O}(N+P\log N)$。



---

空间复杂度均为 $\mathcal{O}(N)$。

**[AC Link](https://www.luogu.com.cn/record/173096664)**

**[AC Code](https://www.luogu.com.cn/paste/3hatlpsd)**

---

