# [ARC082F] Sandglass

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc082/tasks/arc082_d

パーツAとパーツBからなる砂時計があります。これらのパーツにはいくらかの砂が入っています。 砂時計を置くときはパーツAとパーツBのどちらかが上になり、そうでないほうが下になります。

$ 1 $ 秒間に $ 1 $ \[g\] の砂が上にあるパーツから下にあるパーツに落ちます。 ただし、上のパーツにもう砂が残っていない場合は砂は落ちません。

はじめ時刻 $ 0 $ にパーツAが上にあり、$ a $ \[g\] の砂がパーツAに入っていて、$ X-a $ \[g\] の砂がパーツBに入っています(すなわち、合計 $ X $ \[g\] の砂が入っています)。

時刻 $ r_1,r_2,\ ..,\ r_K $ に砂時計をひっくり返します。この操作は瞬間的に行われ、時間はかからないものとします。なお、時刻 $ t $ とは時刻 $ 0 $ の $ t $ 秒後を指します。

クエリが $ Q $ 個与えられます。 各クエリは $ (t_i,a_i) $ の形をしています。 各クエリに対し、$ a=a_i $ だとして、時刻 $ t_i $ にパーツAに入っている砂の量が何gか答えてください。

## 说明/提示

### 制約

- $ 1\ <\ =X\ <\ =10^9 $
- $ 1\ <\ =K\ <\ =10^5 $
- $ 1\ <\ =r_1\ <\ r_2\ <\ ..\ <\ r_K\ <\ =10^9 $
- $ 1\ <\ =Q\ <\ =10^5 $
- $ 0\ <\ =t_1\ <\ t_2\ <\ ..\ <\ t_Q\ <\ =10^9 $
- $ 0\ <\ =a_i\ <\ =X\ (1\ <\ =i\ <\ =Q) $
- 入力値はすべて整数

### Sample Explanation 1

$ 1 $ つめのクエリでは、はじめパーツAに $ 90 $ \\\[g\\\] 入っていた砂が $ 30 $ \\\[g\\\] 減り、$ 60 $ \\\[g\\\] になります。 $ 2 $ つめのクエリでは、はじめパーツAに入っていた $ 1 $ \\\[g\\\] の砂がパーツBに落ちた後、$ 59 $ 秒間変化は起こりません。ここで砂時計をひっくり返し、その $ 1 $ 秒後にパーツAに入っている砂の量を聞かれているため、答えは $ 1 $ \\\[g\\\] になります。

### Sample Explanation 2

どのクエリでもはじめにパーツAに入っている砂は $ 100 $ \\\[g\\\] で、砂時計をひっくり返す前の時間での値を聞いています。

## 样例 #1

### 输入

```
180
3
60 120 180
3
30 90
61 1
180 180```

### 输出

```
60
1
120```

## 样例 #2

### 输入

```
100
1
100000
4
0 100
90 100
100 100
101 100```

### 输出

```
100
10
0
0```

## 样例 #3

### 输入

```
100
5
48 141 231 314 425
7
0 19
50 98
143 30
231 55
342 0
365 100
600 10```

### 输出

```
19
52
91
10
58
42
100```

# 题解

## 作者：ez_lcw (赞：13)

~~吐槽：怎么只有蓝，ARC 的 F 什么时候才能站起来~~

这题其实做法挺多的，有正常的 $O(n\log n)$ 做法，也有我同学强行卡过去的 $O(n\log X)$ 做法，这里我提供一个比较巧妙的 $O(n+m)$ 的快很多的线性做法。（$n$ 指翻转次数，$m$ 指询问次数）

首先翻转一次可以看成是沙子从 $A$ 中的沙子数由增加变为减少或者由减少变为增加。

由于沙子总数 $X$ 不变，所以我们可以通过 $A$ 中的沙子数反映 $B$ 中的沙子数。

设 $f_{st}(t)$ 表示初始时 $A$ 中沙子数为 $st$，时间为 $t$ 秒时 $A$ 中剩余的沙子数。

那么我们把时间 $t$ 当为 $x$ 轴，$A$ 中的沙子数当作 $y$ 轴，将初始时 $A$ 中沙子数为 $0\sim X$ 的折线图像画出来：（即 $f_{0\sim X}$ 的图像）

![](https://cdn.luogu.com.cn/upload/image_hosting/6vg8jt35.png)

如图，红线为初始时 $A$ 中沙子数为 $X$ 时的折线图像（$f_X$），蓝线为初始时 $A$ 中沙子数为 $0$ 时的折线图像（$f_0$）。

发现不论初始时 $A$ 中有多少沙子，对于任意时刻 $t$，都有 $f_0(t)\leq f_1(t) \leq\cdots \leq f_X(t)$。

那么对于询问 $(t_i,a_i)$，有了 $f_{a_i}(t_i)$ 的上下界 $[f_0(t),f_X(t)]$，就很好做了。

又发现如果折线 $f_{a_i}$ 在某一时刻触碰到了 $f_0$（或者 $f_X$），那么在这个时刻以后，$f_{a_i}$ 的折线就和 $f_0$（$f_X$）重合了。

所以当 $t\leq t_i$ 时，要么折线 $f_{a_i}$ 在 $t\leq t_i$ 的时候触碰到了 $f_0$（$f_X$），此时 $f_{a_i}(t_i)$ 就等于 $f_{0}(t_i)$（$f_{X}(t_i)$）。

要么折线 $f_{a_i}$ 在 $t\leq t_i$ 的时候没有触碰过 $f_0$ 或 $f_X$，那这种情况怎么计算呢？

发现若 $f_{a_i}$ 触碰了 $f_0$ 或 $f_X$（不妨设触碰了 $f_0$，触碰到 $f_X$ 是同理的），肯定是在 $y=0$ 或 $y=X$ 的时候碰到的，因为只有当 $f_0$ 横着走，$f_{a_i}$ 斜着走的时候他们才会相遇，且只有当 $f_0=0$ 或 $f_0=X$ 的时候 $f_0$ 才会横着走。

所以当 $t\leq t_i$ 时，若 $f_{a_i}$ 没有触碰过 $f_0$ 或 $f_X$，那么折线 $f_{a_i}$ 就肯定没有触碰过 $y=0$ 或 $y=X$，也就是说，不存在任意一个时刻 $t$（$t\leq t_i$），使得沙漏 $A$ 或 $B$ 中没有沙子。

~~那这个时候我让你求 $\sout{f_{a_i}(t_i)}$ 不是sb题吗~~

统计一下 $sum$，然后加上 $a_i$ 就好了（详见代码）。

那么现在问题来了：如何判断 $f_{a_i}$ 是否触碰 $f_0$ 或 $f_X$？

其实很简单，我们先设此时 $f_0$ 答案为 $down=f_0(t_i)$，$f_X$ 答案为 $up=f_X(t_i)$，那么此时答案的上下界为 $[down,up]$。假设 $f_{a_i}$ 没有触碰过 $f_0$ 或 $f_X$ 时用 $sum$ 算出来的答案 $tmp$。

然后如果 $tmp>up$，答案就是 $up$；如果 $tmp<down$，答案就是 $down$；否则答案就是 $tmp$。

因为如果你用 $sum$ 算出来的折线某一时刻超过了 $y=0$ 或 $y=X$，那么它永远不可能回到区间 $[down,up]$，除非此时 $down=up$。

那么我们只用维护 $3$ 个值，就可以维护所有值的范围了：$f_0$、$f_X$、$sum$。

由于给出的 $r_i$ 和 $t_i$ 是递增的，所以可以在 $O(n+m)$ 的时间内维护。

~~否则加个排序就要带个 $\sout{\log n}$ 了。~~

代码如下：

```cpp
#include<bits/stdc++.h>

#define N 100010

using namespace std;

int x,n,m,r[N];

int main()
{
	scanf("%d%d",&x,&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&r[i]);
	scanf("%d",&m);
	int up=x,down=0,sum=0,tmp=0,tag=-1;
	while(m--)
	{
		int t,a;
		scanf("%d%d",&t,&a);
		while(tmp<n&&r[tmp+1]<=t)
		{
			down=min(x,max(0,down+tag*(r[tmp+1]-r[tmp])));
			up=min(x,max(0,up+tag*(r[tmp+1]-r[tmp])));
			sum=sum+tag*(r[tmp+1]-r[tmp]);
			tag=-tag,tmp++;
		}
		int down1=min(x,max(0,down+tag*(t-r[tmp])));
		int up1=min(x,max(0,up+tag*(t-r[tmp])));
		int sum1=sum+tag*(t-r[tmp]);
		printf("%d\n",min(up1,max(down1,sum1+a)));
	}
	return 0;
}
```

---

## 作者：ezoiLZH (赞：4)

**我的[blog](https://www.cnblogs.com/ezoiLZH/p/9494058.html)**

## 题解：
神题啊！

这题可以用线段树做，我们维护 1~X 中，每个 a 经过一系列操作后的值，我们只用求每个询问中的 a，为了避免爆空间，我们动态开点。

我们把询问按时间排序，同时操作 r 数组，如果A再上面就减区间长度，和0取max，不然就加，与X取min。

像这样：
```cpp
for(int i=0,j=1,rev=0;i<=n;i++,rev^=1){
	while(j<=m&&q[j].t<=r[i+1]){
		int tmp=query(root,1,X+1,q[j].a);
		if(rev)tmp=min(X,tmp+q[j].t-r[i]);
		else tmp=max(0,tmp-q[j].t+r[i]);
		ans[q[j++].id]=tmp;
	}
	if(j>m)break;
	int tmp=r[i+1]-r[i];
	if(rev)Add(root,1,X+1,tmp);
	else Sub(root,1,X+1,tmp);
}
```
然后每个线段树节点维护当前区间的最小值和最大值。

加的话，这样：
```cpp
if(minv[o]>=X-x)
	maxv[o]=minv[o]=set[o]=X,add[o]=0;
else if(maxv[o]<=X-x)
	maxv[o]+=x,minv[o]+=x,add[o]+=x;
```

减就这样：
```cpp
if(maxv[o]<=x)
	maxv[o]=minv[o]=add[o]=set[o]=0;
else if(minv[o]>=x)
	maxv[o]-=x,minv[o]-=x,add[o]-=x;
```

思路还是很简单的，这题主要还是码码。

## COMPLETE CODE：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int n,m,X,tot=0,root,r[100005];
int lch[8000005],rch[8000005];
int minv[8000005],maxv[8000005];
int set[8000005],add[8000005];
struct Question{
	int t,a,id;
}q[100005];
int ans[100005];

bool comp(Question a,Question b){return a.t<b.t;}

int newnode(int &o,int x,int y){
	o=++tot,minv[o]=x,maxv[o]=y,set[o]=-1;
}

void pushup(int o){
	minv[o]=min(minv[lch[o]],minv[rch[o]]);
	maxv[o]=max(maxv[lch[o]],maxv[rch[o]]);
}

void pushdown(int o,int l,int r){
	int mid=l+r>>1;
	int &lc=lch[o],&rc=rch[o];
	if(!lc)newnode(lc,l,mid-1);
	if(!rc)newnode(rc,mid,r-1);
	if(~set[o]){
		minv[lc]=maxv[lc]=set[lc]=set[o];
		minv[rc]=maxv[rc]=set[rc]=set[o];
		add[lc]=add[rc]=0,set[o]=-1;
	}
	if(add[o]){
		minv[lc]+=add[o],maxv[lc]+=add[o],add[lc]+=add[o];
		minv[rc]+=add[o],maxv[rc]+=add[o],add[rc]+=add[o];
		add[o]=0;
	}
}

void Sub(int &o,int l,int r,int x){
	if(o==0)newnode(o,l,r-1);
	if(maxv[o]<=x)
		maxv[o]=minv[o]=add[o]=set[o]=0;
	else if(minv[o]>=x)
		maxv[o]-=x,minv[o]-=x,add[o]-=x;
	else{
		pushdown(o,l,r);
		int mid=l+r>>1;
		Sub(lch[o],l,mid,x),Sub(rch[o],mid,r,x);
		pushup(o);
	}
}

void Add(int &o,int l,int r,int x){
	if(o==0)newnode(o,l,r-1);
	if(minv[o]>=X-x)
		maxv[o]=minv[o]=set[o]=X,add[o]=0;
	else if(maxv[o]<=X-x)
		maxv[o]+=x,minv[o]+=x,add[o]+=x;
	else{
		pushdown(o,l,r);
		int mid=l+r>>1;
		Add(lch[o],l,mid,x),Add(rch[o],mid,r,x);
		pushup(o);
	}
}

int query(int o,int l,int r,int x){
	if(o==0)newnode(o,l,r-1);
	if(r-l==1)return minv[o];
	pushdown(o,l,r);
	int mid=l+r>>1;
	if(x<mid)return query(lch[o],l,mid,x);
	else return query(rch[o],mid,r,x);
}

int main(){
	scanf("%d%d",&X,&n);
	for(int i=1;i<=n;i++)scanf("%d",r+i);
	r[n+1]=1e9;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&q[i].t,&q[i].a);
		q[i].id=i;
	}
	sort(q+1,q+m+1,comp);
	for(int i=0,j=1,rev=0;i<=n;i++,rev^=1){
		while(j<=m&&q[j].t<=r[i+1]){
			int tmp=query(root,1,X+1,q[j].a);
			if(rev)tmp=min(X,tmp+q[j].t-r[i]);
			else tmp=max(0,tmp-q[j].t+r[i]);
			ans[q[j++].id]=tmp;
		}
		if(j>m)break;
		int tmp=r[i+1]-r[i];
		if(rev)Add(root,1,X+1,tmp);
		else Sub(root,1,X+1,tmp);
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
} 
```

---

## 作者：约瑟夫用脑玩 (赞：1)

口胡一个严格被优于 $O(K+Q)$ 的分段函数解法的解法（悲）

形式化的转化一下题意就是：

- 只考虑一个沙漏的沙，初始为一个数 $a$。

- 每次对这个数进行 $+v_i$ 或 $-v_i$ 的操作，但时刻保证 $a\in[0,X]$。

  也就是每做完一次后对 $0$ 取 $\max$，对 $X$ 取 $\min$。
  
  其中 $v_i$ 可以由初始给定的值推出。
  
- 询问在某个操作中途 $t$ 时刻 $a$ 的值。

考虑一次询问，发现 $a$ 的行走过程只与第一次碰 $0$ 的底或是碰 $X$ 的顶有关。

后面就转化为了询问从某个操作后的 $0$ 出发或是某个位置的 $X$ 出发的答案，就可以在预处理上下功夫了。

先假设这个数一直没有触顶或底，那么第 $i$ 个操作完后的值为 $a+\sum_{j=1}^iv_j$，不妨令 $S_i=\sum_{j=1}^iv_j$，也就是 $a+S_i$。

如果一个数在 $i$ 之前触底了，也就是 $\exists j\le i,a+S_i\le0$，不难看出就是 $a+\min\limits_{1\le j\le i}S_j\le0$。

于是我们可以预处理出 $S_i$ 的前缀 $\min$，然后二分来判断在哪里第一次触底，触顶也是同理，处理前缀 $\max$ 即可。

第一次触边界显然就是第一次触底和第一次触顶中更小的那个。

现在考虑从一个操作 $i$ 后从 $0$ 或 $X$ 开始的行走过程，我们又发现它只与下一次碰 $0$ 的底或是碰 $X$ 的顶有关。

于是我们同上一个做法处理出它第一次触底或触顶的位置，注意这里就要用 RMQ 来处理区间最小/最大值了。

用 $(i,0/1)$ 表示操作 $i$ 后为 $0$ 或 $X$ 的状态，$nxt_{(i,0/1)}$ 表示第一次触边界后的状态，显然是可以预处理的。

然后我们直接设 $N_{(i,0/1),j}$ 表示第 $2^j$ 次触边界的状态，就可以倍增了。

令 $T_{(i,0/1)}$ 为 $i$ 操作后的时间，对于一次询问直接倍增到 $T_{nxt_{(x,0/1)}}\ge t$ 的第一个 $(x,0/1)$ 的状态就可以直接回答了，因为从这个状态走到 $t$ 都不会触边界，直接算位置就是对的。

上述算法复杂度 $O((K+Q)\log K)$，顺便口胡一下分段函数，真的是严格优于上述算法。

考虑函数 $f_{t}(a)$ 表示在时间 $t$ 时，初始为 $a$ 的答案，是以 $a$ 作为变量的一个函数，也就是固定了 $t$。

发现这个函数的样子一定形如：

初始 $t=0$：

![](https://cdn.luogu.com.cn/upload/image_hosting/3wg7qyiq.png)

操作一次 $t=T_{(1,0/1)}$：

![](https://cdn.luogu.com.cn/upload/image_hosting/9lr7v5sm.png)

操作两次 $t=T_{(2,0/1)}$：

![](https://cdn.luogu.com.cn/upload/image_hosting/x44nenud.png)

操作三次 $t=T_{(3,0/1)}$：

![](https://cdn.luogu.com.cn/upload/image_hosting/mfxoee4i.png)

不难发现就是个只有两个转折点的简单分段函数，对于从头模拟一遍，对于每个时间 $t$ 记录一下两个转折点的位置即可快速回答答案。

发现这个算法离线时显然就是 $O(K+Q)$ 的了，在线也是 $O(K+Q\log K)$ 优于之前的倍增算法。

---

## 作者：TLE_AK (赞：0)

当你像我一样又没有思维又不想线段树时的玄学做法 qwq。

我们发现当询问按初始 $a_i$ 排序时，对于每个 $j < i$，无论何时都满足 $a'_j\le a'_i$（最新的 $a_i$，不受范围限制），因为它们是同时等量加减的。

我们又发现了：
- 对于每个 $j < i$，若 $a'_j > X$，那么 $a'_i > X$。
- 对于每个 $j > i$，若 $a'_j < 0$，那么 $a'_i < 0$。
- 对于满足以上任一条件的一对 $i,j$，在之后$a_i=a_j$。

那么我们可以将所有翻转与询问的 $t_i$ 排序，记录变化量。   
同时拿两个指针扫按初始 $a_i$ 排序的询问数组，用并查集来维护相同的数，这样就做完了。

时间复杂度 $O(n \log n)$。
#### 代码
写的很丑，有分讨。
```
#include<bits/stdc++.h>
using namespace std;

namespace acac
{
	struct node
	{
		int t,v,id;
	}A[100010],C[200010];
	
	bool cmp(node a,node b)
	{
		return a.v<b.v;
	}
	bool cmpt(node a,node b)
	{
		if(a.t==b.t)return a.v<b.v; 
		return a.t<b.t;
	}
	
	int bcj[200010],id[200010];
	
	int find(int u)
	{
		if(bcj[u]!=u)return bcj[u]=find(bcj[u]);
		return u;
	}
	

	int main()
	{
		int X,n,q,cz=0;
		scanf("%d%d",&X,&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&C[i].t);
		}
		scanf("%d",&q);
		for(int i=1;i<=q;i++)
		{
			scanf("%d%d",&A[i].t,&A[i].v);
			C[i+n].v=A[i].id=i;
			C[i+n].t=A[i].t;
			bcj[i]=i,bcj[i+q]=i+q;
		}
		sort(A+1,A+1+q,cmp);
		sort(C+1,C+1+q+n,cmpt);
		for(int i=1;i<=q;i++)
		{
			id[A[i].id]=i;
		}
		int l=1,r=q,zt=-1,lr=1;
		bcj[0]=1;
		for(int i=1;i<=n+q;i++)
		{
			cz+=(C[i].t-C[i-1].t)*zt;
			if(l>1&&l<=r&&A[l-1].v+cz<0)A[l-1].v=-cz;
			if(r<q&&l<=r&&A[r+1].v+cz>X)A[r+1].v=X-cz;
			while(l<=r&&A[l].v+cz<0)
			{
				A[l].v=-cz;
				if(l>1)bcj[l-1]=l;
				l++;
				if(!l)lr=0;
			}
			while(l<=r&&A[r].v+cz>X)
			{
				A[r].v=X-cz;
				if(r<q)bcj[r+1]=r;
				r--;
				if(!r)lr=0;
			}

			if(lr&&l>r&&A[l].v+cz<0)bcj[l]=r,lr=0;
			if(lr&&l>r&&A[r].v+cz>X)bcj[r]=l,lr=0;
			if(lr)
			{
				if(l>r&&A[r].v+cz<0)A[r].v=-cz;
				if(l>r&&A[l].v+cz>X)A[l].v=X-cz;
			}
			else 
			{
				if(l>r&&A[find(l)].v+cz<0)A[find(l)].v=-cz;
				if(l>r&&A[find(l)].v+cz>X)A[find(l)].v=X-cz;
			}	
			if(!C[i].v)zt*=-1;
			else 
			{
				int al=find(id[C[i].v]);
				cout<<A[al].v+cz<<'\n';
			}	
		}
		return 0;
	}
}

int main()
{
//	freopen("in.in","r",stdin);
//	freopen("wa.out","w",stdout);
	acac::main();
	return 0;
}
/*
77
4
4 30 110 163 
8
71 55
151 58
230 39
263 59
337 4
388 59
389 60
442 19
*/
```

---

## 作者：kkxacj (赞：0)

#### 思路

先考虑将翻转和查询放一起按时间排序。

暴力的话肯定是扫一遍，每次给这 $m$ 个询问的值加减 $x$，$x$ 为上一个操作的时间到现在的时间差是多少，如果当前是询问操作就求出这个的答案，否则就翻转，即加和减互换。

考虑将 $m$ 个询问的初值 $a_i$ 排序，假设当前是加值，那么有一段会是全部变为 $X$，而另一段就是区间加，减则是有一段会是全部变为 $0$，而另一段就是区间减。

考虑二分找到分界点，用线段树维护区间加，区间覆盖就行了。

最后的答案就直接访问线段树上的节点就行了。

**注意刚开始是减值，不要以为是加。**

**code**


```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (p<<1)
#define rs ((p<<1)+1)
#define mid ((c[p].l+c[p].r)>>1) 
using namespace std;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 4e5+10;
map<int,int>mp;
int X,n,m,b[N],cnt,d[N],t,f,l,r,m1d,o;
struct w
{
	int op,t,x,id,ans;
}a[N<<1];
struct w1
{
	int l,r,mx,bj,fg;//不一定非要取max，随便取啥都可以 
}c[N<<1];
inline bool cmp(w x,w y)
{
	if(x.t == y.t) return x.op < y.op;
	return x.t<y.t;
}
inline bool cmp1(w x,w y)
{
	return x.id<y.id;
}
void build(int p,int l,int r)
{
	c[p].l = l,c[p].r = r,c[p].fg = -1;
	if(c[p].l == c[p].r)
	{
		c[p].mx = b[l];
		return;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	c[p].mx = max(c[ls].mx,c[rs].mx); 
}
inline void push_up(int p)
{
	c[ls].mx += c[p].bj,c[rs].mx += c[p].bj;
	c[ls].bj += c[p].bj,c[rs].bj += c[p].bj;
	c[p].bj = 0;
}
inline void push_up1(int p)
{
	c[ls].mx = c[rs].mx = c[p].fg;
	c[ls].bj = c[rs].bj = 0;
	c[ls].fg = c[rs].fg = c[p].fg; c[p].fg = -1;
}
void change(int p,int l,int r,int k)//区间加 
{
	if(l <= c[p].l && c[p].r <= r)
	{
		c[p].mx += k,c[p].bj += k;
		return;
	}
 	if(c[p].fg != -1) push_up1(p);
 	if(c[p].bj != 0) push_up(p);
	if(l <= mid) change(ls,l,r,k);
	if(mid < r) change(rs,l,r,k);
	c[p].mx = max(c[ls].mx,c[rs].mx); 
}
void change1(int p,int l,int r,int x)//区间覆盖 
{
	if(l <= c[p].l && c[p].r <= r)
	{
		c[p].mx = c[p].fg = x,c[p].bj = 0;
		return;
	}
 	if(c[p].fg != -1) push_up1(p);
 	if(c[p].bj != 0) push_up(p);
	if(l <= mid) change1(ls,l,r,x);
	if(mid < r) change1(rs,l,r,x);
	c[p].mx = max(c[ls].mx,c[rs].mx); 
}
int query(int p,int l,int r)
{
	if(l <= c[p].l && c[p].r <= r) return c[p].mx;
 	if(c[p].fg != -1) push_up1(p);
 	if(c[p].bj != 0) push_up(p);
	if(l <= mid) return query(ls,l,r);
	if(mid < r) return query(rs,l,r);
} 
inline void solve(int x)//找到第一个数减去后>=0 
{
	l = 1,r = cnt,o = cnt+1;
	while(l <= r)
	{
		m1d = (l+r)/2;
		if(query(1,m1d,m1d)+x >= 0) r = m1d-1,o = m1d;
		else l = m1d+1; 
	}
}
inline void solve1(int x)//找到最后一个数加上后<=X 
{
	l = 1,r = cnt,o = 0;
	while(l <= r)
	{
		m1d = (l+r)/2;
		if(query(1,m1d,m1d)+x <= X) l = m1d+1,o = m1d;
		else r = m1d-1; 
	}
}
signed main()
{
	read(X),read(n);
	for(int i = 1;i <= n;i++) read(a[i].t),a[i].op = 1;//翻转 
	read(m);
	for(int i = 1;i <= m;i++) read(a[i+n].t),read(a[i+n].x),a[i+n].op = 2,a[i+n].id = i,d[i] = b[i] = a[i+n].x;//询问
	sort(a+1,a+1+n+m,cmp); sort(b+1,b+1+m); t = 0,f = -1;
	for(int i = 1;i <= m;i++) if(!mp[b[i]]) b[++cnt] = b[i],mp[b[i]] = cnt;
	for(int i = 1;i <= m;i++) d[i] = mp[d[i]];
	build(1,1,cnt);
	for(int i = 1;i <= n+m;i++)
	{
		if(f == -1) 
		{
			solve(f*(a[i].t-t));
			if(o != 1) change1(1,1,o-1,0);
			if(o != 0) change(1,o,cnt,f*(a[i].t-t));
		}
		else 
		{
			solve1(f*(a[i].t-t));
			if(o != cnt) change1(1,o+1,cnt,X);
			if(o != 0) change(1,1,o,f*(a[i].t-t));
		}
		if(a[i].op == 1)
		{
			if(f == -1) f = 1;
			else f = -1;
		}
		else a[i].ans = query(1,d[a[i].id],d[a[i].id]);
		t = a[i].t;
	}
	sort(a+1,a+1+n+m,cmp1);
	for(int i = 1;i <= m;i++) print(a[n+i].ans),pc('\n');
	flush();
	return 0;
}



```

---

