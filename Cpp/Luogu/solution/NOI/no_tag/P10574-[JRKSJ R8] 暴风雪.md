# [JRKSJ R8] 暴风雪

## 题目背景

![]( https://cdn.luogu.com.cn/upload/image_hosting/ok3qwkac.png)

## 题目描述

层叠都市可以被抽象为一棵树。于是给你一棵带点权 $v_i$ 的树，树以 $1$ 为根。初始点权 $v_i$ 均为 $0$。

定义 $\text{dis}(x,y)$ 为树上 $x,y$ 之间的距离，即 $x\to y$ 的简单路径上的边数。

设 $\text{subtree}(x)$ 为树上以 $x$ 为根的子树，定义 $f(x)=\max_{d\ge 0} \sum_{y\in\text{subtree}(x)} v_y[\text{dis}(x,y)=d]$。也就是说，$f(x)$ 表示 $x$ 子树中的每一层的点权和的最大值。

现在给出 $m$ 次操作，每次操作中给出 $x,w,y$，先令 $v_x\gets v_x+w$，然后求 $\sum_{i\in \text{subtree}(y)} f(i)$。

## 说明/提示

### 数据规模与约定

**本题采用捆绑测试。**

| $\text{Subtask}$ | $n,m\le$ |  特殊性质 |  $\text{Score}$ | 时间限制|
| :----------: | :----------: | :----------: | :----------: |  :----------: |  
| $1$ | $100$ |  | $5$ | 1s |
| $2$ | $5000$ |  | $15$ | 1s |
| $3$ | $3\times10^5$ | $f_i=i-1$ | $10$ | 4.5s |
| $4$ | $7\times 10^4$ |  | $20$ | 4.5s |
| $5$ | $3\times10^5$ |  | $50$ | 4.5s |

对于所有数据，$1\le n,m\le3\times 10^5$，$1\le x,y\le n$，$1\le w \le 10^8$，$1\le f_i\le n$。

## 样例 #1

### 输入

```
5 7
1 1 1 4
2 1 5
4 2 1
3 4 1
2 5 5
2 4 5
4 4 4
3 2 2```

### 输出

```
0
6
14
0
0
6
10```

## 样例 #2

### 输入

```
6 10
1 1 1 1 2
6 4 1
3 1 1
1 1 1
3 4 1
5 2 1
3 3 1
3 4 1
2 2 1
2 5 1
3 1 1```

### 输出

```
12
13
13
18
22
28
36
38
46
48```

## 样例 #3

### 输入

```
8 10
1 1 2 1 3 3 3
7 3 1
2 4 1
5 2 1
5 2 1
3 1 1
6 2 1
1 4 1
8 4 1
6 4 1
3 2 1```

### 输出

```
9
14
18
22
23
27
27
35
47
47```

# 题解

## 作者：critnos (赞：13)

小清新数据结构题。

容易发现，单点加其实是把该点到根的路径上的 $f$ 值分段取 $\max$。

考虑其祖先 $x$，如果 $x$ 的位置进行了分段。那么 $x$ 具有另外一个深度不小于 $x$ 到叶子距离的子树，那么分的段数显然是根号的。

先考虑求出这些分段。

轻重剖。如果从轻边跳上来，直接对整棵树的每一层维护个 BIT，直接 $O(\log n)$ 求和重置答案。

对于从重边跳上来，维护某个点所有轻子树每一层的和，然后对 $x$ 的祖先距离进行根号分治。

$\le \sqrt n$ 的直接做，对于 $>\sqrt n$ 的，把存在一个轻子树深度不小于 $\sqrt n$ 的结点标记出来，只有这些结点可能新增分段。

直接对重链维护线段树，对于每个分段直接在线段树上操作，注意到重链权值单增，取 $\max$ 可以维护个区间最小最大值然后大力递归。

然后直接做是 $O(n\sqrt n\log n)$ 的，可以获得 50 分。

可以优化至 $n\sqrt{n\log n}$：把距离 $x$ 不超过 $\sqrt{n\log n}$ 的点暴力修改，剩余不超过 $\sqrt{n/\log n}$ 个线段树操作。

有若干优化到 $O(n\sqrt n)$ 的方法，这里介绍一个最优雅的 zky 的方法。

注意到所有区间的长度对数值之和为 $O(\sqrt n)$。就是 $\sum a_i \le n$，那么 $\sum \log(a_i-a_{i-1})=O(\sqrt n))$，这是个经典结论。

还是贺个证明，考虑 $a$ 的差分数组翻转后设为 $b$，那么就是 $\sum b_i \times i\le n$，$\sum \log(b_i)=O(\sqrt n)$。记 $|b|=m$，考虑均值不等式 $\prod (b_i\times i)^{1/m}\le (\sum b_i \times i)/m\le n/m$，也即 $\prod b_i\le (n/m)^m/m!$。两边取对数，把 $\log(m!)$ 近似为 $\log$ 的积分得到 $\sum \log(b_i)\le m(\log n-\log m)-(m\log m-m)=m(\log n-2\log m)+m$。导一下发现是 $\log n-2\log m-1$，所以 $m$ 大概就是 $\sqrt n$ 的时候最大（因为 $m\le \sqrt n$，常数项不影响），取到 $O(\sqrt n)$。

可以发现，修改涉及到的点数是 $O(\sqrt n)$。具体来说就是，一个区间在线段树上被拆成了 $O(\log(r-l+1))$ 个区间。然后考虑所有这 $O(\sqrt n)$ 个区间到根的并，可以发现，这里涉及到的结点就是 $O(\log^2 n)$ 个重链前缀拆出来的结点，和 $O(\sqrt n)$ 个左右子树都被涉及的结点。

那么做一些精细的实现即可做到 $O(n\sqrt n)$。

为了放过大常数的正解，将时间限制开到了 4.5s，不确定大力卡常的高复杂度做法能否通过。

---

## 作者：XZhuRen (赞：3)

图床挂了，重传。

**有趣的数据结构题。**

鲜花：题目背景是什么呢？

---

由于时限比较宽松，不太清楚我写的到底是什么复杂度，应该是根号级别的，如果有大佬能帮我看看就很好了 $\mathcal{OwO}$。

首先观察，求一个点被哪些值贡献并不现实，考虑反过来求一个点增加的时候的贡献（题目初始全 $0$ 也提醒了这一点）。

$d_x$ 为点 $x$ 的深度。

首先发现我们向上的过程中，对应的值会发生变化，设改变点为 $x$，有一祖先点 $u$，当且仅当 有 $v\in subtree_u,d_v>d_x$，且 $x,v$ 不属于同一子树。

则改变次数不超过 $\mathcal{O}(\sqrt{n})$，我们是对这些链上的点值 $\text{chkmx}$。

但是！这个东西很不友善，我们考虑对每个点求出来分界点不是很现实（空间不够），考虑直接对点进行根号分治来维护：

设阈值 $S$，对于 $d_u-d_x\le S$ 的，直接对到达每个 $u$ 点的点值暴力算出，反之若 $d_u-d_x>S$，就只有在 $u$ 有另一子树的 $mxdep-d_u>S$ 的时候再取了。

很自然地联想到重剖，直接对树重剖，则第二种点就是轻子树 $mxdep-d>S$ 的点，这个扫一遍就好。

回过头来考虑需要维护什么东西：

1. 跳链的时候，无法区分轻重，需要手动找子树内某层的和，这个按照层数维护一个 $\text{BIT}$，层内按照 $dfn[]$ 排序，每次找的时候二分一下区间求和。

2. 反之就加上轻子树内某层的和，这个拿桶记一下就好了，个数是 $\mathcal{O}(n\log_2n)$ 的。

第一种情况总复杂度 $\mathcal{O}(n\log_2^2n)$，第二种 $\mathcal{O}(S+\frac{n}{S})$。

考虑维护树剖，$\text{sgtbeats}$ 链修改，子树（区间）查询，平衡阈值情况下复杂度 $\mathcal{O}(n\sqrt{n\log_2n})$。

现在考虑怎么优化这个算法：

首先对于每条重链单独开线段树（这样也就不用真写 $\text{sgtbeats}$ 了）：

查询的时候只要用 $\text{BIT}$ 维护重链按照链头的顺序的和，并查询所在重链一段后缀和。

**以下内容由于本人实力有限，不会证明，所以只叙述思路了：**

对于每条链来说，我们会有多次对前缀的 $\text{chkmx}$ 操作，长成这个样子：

[![pEDRczd.png](https://s21.ax1x.com/2025/03/26/pEDRczd.png)](https://imgse.com/i/pEDRczd)

单次操作的复杂度是对数的，但我们在多次操作的过程中，多次重复访问了很多点，**假设这些点只会访问一次**，是否就能使复杂度带的 $\mathcal{O}(\log)$ 大大退化？考虑把每个操作离线下来统一更新。

根据此思路写出的线段树区间修改代码：

```cpp

int nw=0;
int rts[N];ll1 dts[N];
void oper(int o,int l,int r){//前缀分段最大值
	if(l>rts[nw])return;
	while(rts[nw-1]>=r)nw--;
	if(r<=rts[nw]&&l>rts[nw-1]){
		chkmx(o,l,r,dts[nw]);
		return;
	}
	pushdown(o,l,r);
	oper(rs,mid+1,r),oper(ls,l,mid);
	pushup(o);
}

```

这一部分的复杂度不会证明，姑且认为在题目背景下是 $\mathcal{O}(n\sqrt{n})$ 的（手玩几种情况下的链修改）。

经过测试，未经优化的 $\mathcal{O}(n\sqrt{n\log_2n})$ （每次单独修改）复杂度算法并不能通过此题：[提交记录](https://www.luogu.com.cn/record/208422232)。

但是本算法（离线统一修改）可以轻松通过：[提交记录](https://www.luogu.com.cn/record/208419699)。

```cpp
ll1 w[N];
int n,q;
struct edge{
}g[N*2];
int head[N],tote=0;
void ae(int u,int v){
}
vector<int>steps[N];//每层的 dfn[] 集合
vector<int>roads;//所有重链链头集合
vector<ll1>sms[N];//每个节点轻子树每个深度和
int fa[N],sz[N],hs[N];
int mxdep[N],mxd[N];
int ups[N];//向上的下一个端点
int top[N],bot[N],id[N],trds=0;
int d[N],dfn[N],lstd[N],dfns[N],tdfn=0;
namespace bit1{//每层维护 bit	，（存储bfn）
}
namespace bit2{
}
int root[N];
namespace sgt{
/*由于是单增，问题转化为区间赋值，只要维护最小值就好*/
	struct Node{
		int lson,rson;
		ll1 sm,mx,mn;
		ll1 tag;
	}t[N*4];
	int totn=0;
#define ls t[o].lson
#define rs t[o].rson
#define mid ((l+r)>>1)
	void pushup(int o){
		t[o].sm=t[ls].sm+t[rs].sm;
		t[o].mx=max(t[ls].mx,t[rs].mx),t[o].mn=min(t[ls].mn,t[rs].mn);
	}
	void cover(int o,int l,int r,ll1 tg){t[o].mx=t[o].mn=tg,t[o].sm=(r-l+1)*tg;t[o].tag=tg;}
	void pushdown(int o,int l,int r){//对子结点进行覆盖（如有标记，必然更优）
		if(!t[o].tag)return;
		ll1 tg=t[o].tag;t[o].tag=0;
		cover(ls,l,mid,tg),cover(rs,mid+1,r,tg);
	}
	void chkmx(int o,int l,int r,ll1 tg){
		if(t[o].mn>=tg)return;//劣
		if(t[o].mx<=tg){cover(o,l,r,tg);return;}//优
		pushdown(o,l,r);
		chkmx(ls,l,mid,tg),chkmx(rs,mid+1,r,tg);
		pushup(o);
	}
	int build(int l,int r){
		int o=++totn;
		t[o]=(Node){0,0,0,0,0,0};
		if(l==r)return o;
		ls=build(l,mid),rs=build(mid+1,r);
		return o;
	}
int nw=0;
int rts[N];ll1 dts[N];
//注：rts[0]=0
	void oper(int o,int l,int r){//前缀分段最大值
		if(l>rts[nw])return;
		while(rts[nw-1]>=r)nw--;
		if(r<=rts[nw]&&l>rts[nw-1]){
			chkmx(o,l,r,dts[nw]);
			return;
		}
		pushdown(o,l,r);
		oper(rs,mid+1,r),oper(ls,l,mid);
		pushup(o);
	}
	void clr(){nw=0;rts[0]=dts[0]=0;}
	void ins(int x,ll1 dt){
		++nw;
		rts[nw]=x,dts[nw]=dt;
	}
	void mdf(int tp){
		if(!nw)return;
		for(int i=1;i<=nw/2;i++)
			swap(rts[i],rts[nw-i+1]),swap(dts[i],dts[nw-i+1]);
		oper(root[tp],dfn[tp],dfn[bot[tp]]);
	}
	ll1 query(int o,int l,int r,int lt,int rt){
		if(l>=lt&&r<=rt)return t[o].sm;
		pushdown(o,l,r);
		ll1 res=0;
		if(lt<=mid)res+=query(ls,l,mid,lt,rt);
		if(rt>mid)res+=query(rs,mid+1,r,lt,rt);
		return res;
	}
#undef ls
#undef rs
#undef mid
}
void dfs1(int u,int Fa,int D){
}
void dfs2(int u,int tp){
}
void dfs3(int u,int lst){
}
void init(){
}
void modify(int p,ll1 W){
	w[p]+=W;
	ll1 dt=w[p];
	bit1::Add(p,W);
	int u=p;
	while(u){//向上修改
		dt=bit1::Qry(u,d[p]);//跳链的询问
		int tps=top[u];
		sgt::clr();
		while(dfn[u]>=dfn[tps]){
			sgt::ins(dfn[u],dt);
			//跳重链
			u=(((d[p]-d[u])>S)?ups[u]:fa[u]);
			if(dfn[u]<dfn[tps])break;
			if((d[p]-d[u])<=mxd[u])dt+=sms[u][d[p]-d[u]];
		}
		sgt::mdf(tps);//修改这条链
		ll1 delta=sgt::t[root[tps]].sm-bit2::Qry(id[dfn[tps]],id[dfn[tps]]);
		bit2::Add(id[dfn[tps]],delta);
		if(!u)break;//跳轻边
		sms[u][d[p]-d[u]]+=W;
	}
}
ll1 query(int u){
}
void work(){
}
int main(){
	init();
	work();
	return 0;
}
```

---

尤莉可爱捏。

---

