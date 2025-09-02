# Mark and Professor Koro

## 题目描述

After watching a certain anime before going to sleep, Mark dreams of standing in an old classroom with a blackboard that has a sequence of $ n $ positive integers $ a_1, a_2,\dots,a_n $ on it.

Then, professor Koro comes in. He can perform the following operation:

- select an integer $ x $ that appears at least $ 2 $ times on the board,
- erase those $ 2 $ appearances, and
- write $ x+1 $ on the board.

Professor Koro then asks Mark the question, "what is the maximum possible number that could appear on the board after some operations?"

Mark quickly solves this question, but he is still slower than professor Koro. Thus, professor Koro decides to give Mark additional challenges. He will update the initial sequence of integers $ q $ times. Each time, he will choose positive integers $ k $ and $ l $ , then change $ a_k $ to $ l $ . After each update, he will ask Mark the same question again.

Help Mark answer these questions faster than Professor Koro!

Note that the updates are persistent. Changes made to the sequence $ a $ will apply when processing future updates.

## 说明/提示

In the first example test, the program must proceed through $ 4 $ updates.

The sequence after the first update is $ [2,3,2,4,5] $ . One sequence of operations that achieves the number $ 6 $ the following.

- Initially, the blackboard has numbers $ [2,3,2,4,5] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,5,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [4,5,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [5,\color{red}{5}] $ .
- Erase two copies of $ 5 $ and write $ 6 $ , yielding $ [\color{red}{6}] $ .

Then, in the second update, the array is changed to $ [2,3,2,4,3] $ . This time, Mark cannot achieve $ 6 $ . However, one sequence that Mark can use to achieve $ 5 $ is shown below.

- Initially, the blackboard has $ [2,3,2,4,3] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,3,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [3,4,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [3,\color{red}{5}] $ .

In the third update, the array is changed to $ [2,3,2,1,3] $ . One way to achieve $ 4 $ is shown below.

- Initially, the blackboard has $ [2,3,2,1,3] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [2,2,1,\color{red}{4}] $ .

## 样例 #1

### 输入

```
5 4
2 2 2 4 5
2 3
5 3
4 1
1 4```

### 输出

```
6
5
4
5```

## 样例 #2

### 输入

```
2 1
200000 1
2 200000```

### 输出

```
200001```

# 题解

## 作者：Chancylaser (赞：19)

此篇题解既作为题目总结，也作为我对线段树二分的梳理。

------

首先，我们先把一开始读入的数组进行题目所描述的，能合并就尽量合并。这样的话，容易发现**处理后的数组中每个数字出现的次数不大于 $1$ 次**。我们把一开始的数组设为 $a$ 数组，把处理后的数组设为 $cnt$ 数组。

然后我们考虑修改操作，每次修改的实质是删除一个数，再添加一个数。我们设删除的数为 $del$，添加的数为 $l$。

**我们首先先删除 $del$，分为两种情况**。  
$1.$ 在目前的 $cnt$ 数组中，出现了 $1$ 次。这种情况下，容易发现直接在 $cnt[del]$ 处赋值为 $0$ 即可。因为即使我们删除这个数，也不会对其它的合并有影响。  
$2.$ 在目前的 $cnt$ 数组中，出现了 $0$ 次。因为题目所给出的删除一定是合法的，所以在原数组中 $del$ 一定是合并到比它大的数里去了。所以我们找出 $del$ 后第一个 $cnt[res]$ 为 $1$ 的 $res$，并把 $del \sim res-1$ 的 $cnt$ 值全部赋值为 $1$ 即可，同时把 $res$ 位置的 $cnt$ 值赋值为 $0$。

**我们再添加 $l$，同理分为两种情况**。

$1.$ 在目前的 $cnt$ 数组中，出现了 $0$ 次。这种情况下，容易发现直接在 $cnt[del]$ 处赋值为 $1$ 即可。因为即使我们添加这个数，也不会对其它的合并有影响。  
$2.$ 在目前的 $cnt$ 数组中，出现了 $1$ 次。这时候我们找出 $del$ 后第一个 $cnt[res]$ 为 $0$ 的 $res$，显然 $del \sim res-1$ 都可以一直合并，直到 $res$，所以将 $del \sim res-1$ 全部赋值为 $0$，同时把 $res$ 位置的 $cnt$ 值赋值为 $1$。

**查询答案的时候**，只要找出最大的 $res$，使得 $cnt[res]=1$ 即可。

----------------------

此时我们如果暴力覆盖，设 $M$ 为最大可能合并到的数字，时间复杂度则是 $O(Mq)$，$q$ 的意义同题面，此时无法通过此题。

发现可以使用线段树来维护 $cnt$ 数组，此时有两种实现方式，主要是对于上面 $res$ 的寻找方式不同，时间复杂度也不同，但均能通过此题。  
$1.$ 二分套线段树，发现 $cnt$ 数组的前缀和满足单调性，所以可以使用二分查找到我们需要的 $res$，每次查询 $1$ 到目前 $res$ 的 $1$（或者是 $0$）的个数。时间复杂度 $O(q\log^2 M)$。  
$2.$ 线段树二分，注意这与 $1.$ 做法并不相同。我们发现线段树本身就有二分的性质，所以快速从根节点往下跳找到我们需要的 $res$。由于默认读者会此技巧，这里便不再详细赘述。如果读者不详知此技巧，请选择更简单的线段树二分题目来进行练习，再来做此题会更加便利。此时间复杂度为 $O(q \log M)$。

------------

这里我给出第二种实现方式的全部代码。我认为写得还是比较通俗易懂的，另外，我代码里的 $dl$ 即是上面所说的 $del$，其余的思路完全符合上面的讲述。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=4e5+5,MAX=4e5;

int n,q;
int a[N],sum[N];

struct qwq{
	int l,r,sum;
	int fg;
	qwq(){
		l=r=sum=0;
		fg=N;
	}
	void fugai(int k){
		sum=(r-l+1)*k;
		fg=k;
	}
}t[N<<2];

void pushup(int p){
	t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
}

void pushdown(int p){
	if(t[p].fg!=N){
		t[p<<1].fugai(t[p].fg);
		t[p<<1|1].fugai(t[p].fg);
		t[p].fg=N;
	}
}

void build(int p,int l,int r){
	t[p].l=l; t[p].r=r;
	if(l==r){
		t[p].sum=sum[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}

void copy(int p,int l,int r,int val){
	if(t[p].l>=l && t[p].r<=r){
		t[p].fugai(val);
		return;
	}
	pushdown(p);
	
	int mid=(t[p].l+t[p].r)>>1;
	if(l<=mid) copy(p<<1,l,r,val);
	if(r>mid) copy(p<<1|1,l,r,val);
	pushup(p);
}

int getsum(int p,int l,int r){
	if(t[p].l>=l && t[p].r<=r) return t[p].sum;
	pushdown(p);
	
	int mid=(t[p].l+t[p].r)>>1;
	int ans=0;
	if(l<=mid) ans+=getsum(p<<1,l,r);
	if(r>mid) ans+=getsum(p<<1|1,l,r);
	return ans;
}

int getpos(int p,int k){
	if(t[p].l==t[p].r) return t[p].l;
	pushdown(p);
	
	int nw=t[p<<1].sum;
	if(nw>=k) return getpos(p<<1,k);
	else return getpos(p<<1|1,k-nw);
}

int getpos2(int p,int k){
	if(t[p].l==t[p].r) return t[p].l;
	pushdown(p);
	
	int nw=(t[p<<1].r-t[p<<1].l+1) - t[p<<1].sum;
	if(nw>=k) return getpos2(p<<1,k);
	else return getpos2(p<<1|1,k-nw);
}

int getmax(int p){
	if(t[p].l==t[p].r) return t[p].l;
	pushdown(p);
	
	if(t[p<<1|1].sum) return getmax(p<<1|1);
	else return getmax(p<<1);
}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum[a[i]]++;
	}
	for(int i=1;i<=MAX;i++){
		sum[i+1]+=sum[i]/2;
		sum[i]%=2;
	}
	
	build(1,1,MAX);
	
	int k,l;
	for(int i=1;i<=q;i++){
		scanf("%d%d",&k,&l);
		int dl=a[k],lsum=0;
		int res;
		a[k]=l;
		
		if(getsum(1,dl,dl)) copy(1,dl,dl,0);
		else{
			lsum=getsum(1,1,dl);
			res=getpos(1,lsum+1);
			copy(1,dl,res-1,1);
			copy(1,res,res,0);			
		}
		
		if(!getsum(1,l,l)) copy(1,l,l,1);
		else{
			lsum=l-getsum(1,1,l);
			res=getpos2(1,lsum+1);
			copy(1,l,res-1,0);
			copy(1,res,res,1);
		}
		
		printf("%d\n",getmax(1));
	}
	return 0;
}
```







---

## 作者：WOL_GO (赞：19)

**思路**

抽象一下题目，我们把每个 $a_{i}$，构成一个二进制数 $q=\overline{a_{n}a_{n-1}\dots a_{1}}$，所以询问就变成了问这个数有多少位，即 $n$ 为多少。对于每一次修改操作，我们假设 $a_{x}$ 被修改为了 $y$，那么即将 $q$ 的第 $a_{x}$ 位 $-1$，然后将第 $y$ 位 $+1$。举个例子，当 $q=1000001,a_{x}=1,y=7$ 时，$q$ 会变为 $2000000$，进位后是 $10000000$，答案为 $8$。可以见得，当进退位次数变多时，暴力算法将会退化到 $O(n^2)$ 级别，不能通过本题。

如何处理多次进退位问题？

首先，对于进位许多的情况，如 $111111+1$ 变为 $1000000$ ，我们会发现我们把 $a_{6}a_{5}\dots a_{1}$ 都变为了 $0$，把 $a_{7}$ 变为了 $1$。我们发现，算法的瓶颈在赋值 $a_{6}a_{5}\dots a_{1}$ 的时候。那么，有没有什么算法能维护区间推平？最方便的是珂朵莉树，于是，我们对于每一次修改操作，设修改点为 $x$，如果 $a_{x}=1$，那我们可以找到当前区间最左端的点 $a_{k}$（最接近 $a_{n}$ 的 ）使 $a_{x}=a_{x+1}=\dots=a_{k}=1$ 且 $a_{k+1}\ne 1$，然后把 $a_{k}\dots a_{x}$ 都变为 $0$，把 $a_{k+1}$ 变为 $1$。退位同理。对于查询操作，只需找到最左端的权值为 $1$ 的点方可。

**代码**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ite set<node>::iterator
using namespace std;
const int maxn=1e6+5;
int a[maxn],n,m;
struct node{
	int l,r;
	mutable int v;
	node(int l,int r=0,int v=0):l(l),r(r),v(v){}
	bool operator < (const node& o)const{
		return l<o.l;
	}
};
set<node>q;
ite split(int p){
	ite it=q.lower_bound(node(p));
	if (it!=q.end()&&it->l==p)return it;
	it--;
	if(it->r<p)return q.end();
	int l=it->l,r=it->r,v=it->v;
	q.erase(it);
	q.emplace(l,p-1,v);
	return q.emplace(p,r,v).first;
}
void update(int l,int r,int x){
	ite itr=split(r+1),itl=split(l);
	q.erase(itl,itr);
	q.emplace(l,r,x);
}
void add(int x,int y){
	ite itr=split(x+1),itl=split(x);
	if(itl->v!=y){
		itl->v=y;
		return;
	}
	else{
        int l=itl->l;
        for(;itl->v==y;itl++);
        int r=itl->l-1;
        update(l,r,!y);
        split(r+2);
        split(r+1)->v=y;
    }
}
int query(){
	ite itr=q.end();
	itr--;
	for(;;itr--){
		if(itr->v==1){
			update(itr->r+1,(--q.end())->r,0);
			return itr->r;
		}
		if(itr==q.begin())return 0;
	}
}
int main(){
    #ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #endif
	cin>>n>>m;
    q.emplace(1,maxn-1,0);
	for(int i=1;i<=n;i++)cin>>a[i],add(a[i],1);
	while(m--){
		int x,y;
		cin>>x>>y;
		add(a[x],0);
		a[x]=y;
		add(y,1);
		cout<<query()<<"\n";
	}
	return 0;
}

```


---

## 作者：_cyle_King (赞：5)

# CF1705E 题解

## 题意

给出一个长度为 $n$ 的序列，每两个相同的数 $x$ 可以合并成一个更大的数 $x+1$。每次操作都会将一个数变成另一个数。要求在每次操作完后输出**合并到最终时最大的数**。

## 分析

每两个数能合并成一个 $x+1$，这个形式与二进制的进位极其类似，很容易证明最终合并完后每个数出现次数不会大于 $1$，因此，**将整个序列看做一个二进制数**，从低到高第 $i$ 为表示**合并完后** $i$ 在序列中出现的次数。每一次对 $a_k$ 的操作，可以转化为对这个二进制数减去 $2^{a_k-1}$，在加上 $2^{y-1}$，输出这个二进制数的最高位。

考虑怎么维护这一个东西。加上一个数 $2^{y-1}$，相当于找到 $y-1$ 位之后的第一个 $0$ 的位置（记作 $\texttt{pos}$，将 $\texttt{pos}$ 上的数变为 $1$，再将 $\left[y-1,\texttt{pos}-1\right]$ 全部刷 $0$。

理解起来也比较容易，因为在 $y-1$ 位上加 $1$，可能会向高位连环进位，而遇到第一个 $0$ 的位置，连环进位就会停止，而之前进位的地方就会全部变为 $0$。

减去一个数与上面同理，只是 $0,1$ 互换，这里就不在累述。

## 实现

由于有区间操作，数据范围在 $10^5$ 量级，直接模拟 $O(n^2)$ 过不去，可以考虑使用线段树维护（但是由于CF的评测机的速度实在太快，bitset 暴力模拟+卡常能过去）。

线段树维护两个 bool 类型的标记，$f_0$ 和 $f_1$，$f_0$表示区间**或运算和**，$f_1$ 表示区间**与运算和**，当找第一个 $0$ 时，使用线段树上二分（我说我在做完了这道题之后才知道这种方法叫做线段树上二分你信吗？）如果当前询区间在查询区间内且 $f_1$ 的值为 true 就可以直接返回，因为此时的区间内没有任何的 $0$；找第一个 $0$ 同理。发现这两个操作长得很像，可以用同一个函数实现。

至于区间刷值，在加上一个懒标记 $\texttt{lz}$，值为 $-1$ 时表示该区间没有赋值操作，否则为当前区间刷的数。当然你也可以将区间赋值看做区间翻转（不是文艺平衡树的那个区间翻转，而是区间上的数取反），维护一个区间翻转标记。

查询的话，采用贪心思想，尽量走右子树，在右子树有 $1$ 的情况下走右子树（即右子树的 $f_{0}$ 为 $1$），否则再走左子树。

为了维护方便，将二进制数的对应节点向右移了一位，在就可以直接用 $y$ 而不是 $y-1$ 了。

具体细节都在代码上，自己看就行了。

### Code

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#define rep(i,x,y) for(int i=(x),_=(y);i<=_;i++)
#define per(i,x,y) for(int i=(x),_=(y);i>=_;i--)
using namespace std;

const int N=2e5+10,M=2e5+17;//由于数最终可能会比 n 大log n，因此线段树的下标多开几个

int n,m,a[N+1],pos;//pos表示在函数中找到的位置
struct
SegTree{
	int lz;
	bool f[2];
	#define f(p,k) tree[p].f[k]
	#define lz(p) tree[p].lz
}tree[M<<2|1];
#define lc (p<<1)
#define rc (p<<1|1)

inline void push_up(int p){f(p,0)=f(lc,0)|f(rc,0);f(p,1)=f(lc,1)&f(rc,1);}

inline void//标记下传
push_down(int p){
	if(lz(p)!=-1){
		lz(lc)=lz(rc)=lz(p);
		f(lc,1)=f(rc,1)=f(lc,0)=f(rc,0)=lz(p);
		lz(p)=-1;
	}
}

inline void//区间赋值
update_all(int p,int l,int r,int L,int R,int k){
	if(L>R)  return ;//注意这里，因为在可能刚好没有引起连环进位，在区间赋值时会碰到L>R的情况，这时由于不需要赋值，直接返回。
    //如果是区间翻转的写法，可以不用判断，将找到的0或1的位置一并翻转就行了（感性理解）
	if(l>=L&&r<=R){
		f(p,1)=f(p,0)=k;
		lz(p)=k;
		return ;
	}
	push_down(p);int mid=l+r>>1;
	if(L<=mid) update_all(lc,l,mid,L,R,k);
	if(mid<R) update_all(rc,mid+1,r,L,R,k);
	push_up(p);
}

inline bool//返回是否赋值成功
update_add(int p,int l,int r,int L,int R,bool k){//找到第一个非k的位置，并将那个位置的数变为k，区间翻转的写法不需要在该函数内赋值
	if(l>=L&&r<=R){
		bool f=0;
		if(f(p,k)==k) return 0;//当前区间没有符合条件的数，直接返回
		if(l==r){pos=l;f(p,1)=f(p,0)=k;return 1;}//找到，记录位置并且赋值，返回 true 
         //区间翻转的写法不需要赋值
		push_down(p);int mid=l+r>>1;//注意这里也要push_down，不然你连样例都过不了
		if(f(lc,k)!=k) f=update_add(lc,l,mid,L,R,k);//左子树满足条件，递归左子树
		else f=update_add(rc,mid+1,r,L,R,k);//否则递归右子树
		push_up(p);return f;//返回是否成功
	}
	push_down(p);
	int mid=l+r>>1;bool fl=0;
	if(L<=mid) fl=update_add(lc,l,mid,L,R,k);
	if(mid<R&&!fl) fl=update_add(rc,mid+1,r,L,R,k);//左子树操作成功了就不用递归右子树
	push_up(p);return fl;
}

inline int
query(int p,int l,int r){//查询
	if(l==r) return l;
	push_down(p);int mid=l+r>>1; 
	if(f(rc,0)) return query(rc,mid+1,r);//右子树有1，走右子树
	return query(lc,l,mid);//否则走左子树
}

int
main(){
	#ifndef ONLINE_JUDGE
	freopen("1.txt","r",stdin);
	#endif
	scanf("%d%d",&n,&m);
	//lz不用初始化，因为一开始没有操作相当于区间赋值为 0 
	rep(i,1,n) scanf("%d",a+i),update_add(1,1,M,a[i],M,1),update_all(1,1,M,a[i],pos-1,0);//将原来的数一个个的插入到树中
	int x,y;
	while(m--){
		scanf("%d%d",&x,&y);
		update_add(1,1,M,a[x],M,0);update_all(1,1,M,a[x],pos-1,1);//先减去原来的数
		a[x]=y;update_add(1,1,M,a[x],M,1);update_all(1,1,M,a[x],pos-1,0);//再加上后来的数
		printf("%d\n",query(1,1,M));//输出
	}
	return 0;
}
```

在寻找 $0,1$ 时，由于一棵线段树内与能拼合包含给定区间的区间总数最少为 $O(\log n)$ 个，而只有一个区间会进行单向递归，因此一次操作最多经过的区间总数为 $O(\log n)$ 个。赋值操作本身就是线段树的常规操作，时间复杂度为 $O(\log n)$；查询从操作是单点查询，复杂度一样，因此，总时间复杂度为 $O((n+m)\log n)$。

因为区间赋值操作是区间推平，也可以用 ODT 在 $O((n+m)\log n)$ 的时间范围内维护（貌似因为线段树的 leafy 结构带来的两倍常数，线段树不一定能跑过 ODT ）。



# End









---

## 作者：__stick (赞：4)

# 题意

给出一些数，对于每两个相同的数 $x$ ，可以将他们合并成 $x+1$，每次替换掉一个数，操作后输出可得到的最大数。

# 思路

首先观察到值域非常小，所以可以直接开桶记录，暴力模拟合并操作，不难写出以下程序：
```cpp
for(int i=1;i<=n;i++)cnt[a[i]]++;
for(int i=0;i<=210000;i++)cnt[i+1]+=cnt[i]/2,cnt[i]%=2;
```
会发现这玩意和高精度进位非常像，考虑维护一个二进制数，每次加数就是在对应位加一，反之就是对应位减一，处理进位退位操作即可。

如何处理进位退位操作？手算两个会发现，加一有两种情况，一是对应位是 $0$，可以直接加，反之找到比当前位高的第一个 $0$，一路进位到这个 $0$，并使它变成 $1$，中间经过的所有 $1$ 都变成了 $0$，减一通力，不过 $0,1$互换位置。

如何高效维护？考场上看到区间赋值，啪一下，很快啊，掏出了珂朵莉树，然后光荣 TLE 10 ([惨案](https://codeforces.com/contest/1705/submission/164330271))，这时只剩下 20 分钟了，然后发现线段树可以高效维护。只需要一个区间赋值函数，找最靠前的 $1/0$ 可以通过维护 $pre0,pre1$，表示对应区间内最靠前的 $0/1$，高效查询，每次查询时像一般操作一样找到对应区间，将区间内所有 $pre1/pre0$ 取 $\min$ 即可，找后缀第一个 $1$ 也是同理 。

# 代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bitset>
#include<iomanip>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
using LD = long double ;
#define Y second
#define mp make_pair
#define double long double
int cnt[210009];
struct xds
{
	#define mid ((l+r)>>1)
	xds* ls,*rs;
	int l,r,cnt,cov;
	vi pre,suf;
	xds(int L,int R)
	{
		l=L,r=R;
		pre={0x3f3f3f3f,0x3f3f3f3f},suf={-0x3f3f3f3f,-0x3f3f3f3f};//记得赋初值 
		cov=-1;
		if(L==R)
		{
			cnt=::cnt[L];
			if(cnt)pre={0x3f3f3f3f,l},suf={-0x3f3f3f3f,l};
			else pre={l,0x3f3f3f3f},suf={l,-0x3f3f3f3f};
			return ;
		}
		ls=new xds(L,mid),rs=new xds(mid+1,R);
		push_up();
	}
	inline void push_up()
	{
		cnt=ls->cnt+rs->cnt;
		for(int k=0;k<2;k++)
		pre[k]=min(ls->pre[k],rs->pre[k]),
		suf[k]=max(ls->suf[k],rs->suf[k]);
	}
	inline void cove(int k)
	{
		cov=cnt=k;
		if(cnt)pre={0x3f3f3f3f,l},suf={-0x3f3f3f3f,r};
		else pre={l,0x3f3f3f3f},suf={r,-0x3f3f3f3f};
	}
	inline void push_down()
	{
		if(~cov) ls->cove(cov),rs->cove(cov),cov=-1;
	}
	inline int operator[](int x)
	{
		if(l==r)return cnt;
		push_down();
		if(x<=mid)return (*ls)[x];
		else return (*rs)[x];
	}
	inline void set(int ql,int qr,int k)
	{
		if(ql<=l&&r<=qr)return cove(k);
		push_down();
		if(ql<=mid) ls->set(ql,qr,k);
		if(qr>mid) rs->set(ql,qr,k);
		push_up();
	}
	inline int askpre(int ql,int qr,int k)
	{
		if(ql<=l&&r<=qr)return pre[k];
		push_down();
		if(qr<=mid)return ls->askpre(ql,qr,k);
		else if(ql>mid)return rs->askpre(ql,qr,k);
		else return min(ls->askpre(ql,qr,k),rs->askpre(ql,qr,k));
	}
	inline int asksuf(int ql,int qr,int k)
	{
		if(ql<=l&&r<=qr)return suf[k];
		push_down();
		if(qr<=mid)return ls->asksuf(ql,qr,k);
		else if(ql>mid)return rs->asksuf(ql,qr,k);
		else return max(ls->asksuf(ql,qr,k),rs->asksuf(ql,qr,k));
	}
};
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,T;cin>>n>>T;
	vi a(n+1);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cnt[a[i]]++;
	for(int i=0;i<=210000;i++)cnt[i+1]+=cnt[i]/2,cnt[i]%=2;
	xds s(1,210000);//稍微多开一点 
	while(T--)
	{
	    int k,x;cin>>k>>x;
	    if(s[a[k]]) s.set(a[k],a[k],0);
	    else
	    {
	    	int r=s.askpre(a[k],210000,1);
	    	s.set(a[k],r-1,1),s.set(r,r,0);
		}
	    a[k]=x;
	    if(!s[a[k]]) s.set(a[k],a[k],1);
	    else
	    {
	    	int r=s.askpre(a[k],210000,0);
	    	s.set(a[k],r-1,0),s.set(r,r,1);
		}
		cout<<s.asksuf(1,210000,1)<<'\n';
	}
	
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：3)

### 1 视频题解

![](bilibili:BV1ud4y1Q7f5)

### 2 思路

我们用一个权值线段树来维护**进行完毕所有操作后**的数列。我们可以发现，每一个数最多出现 $1$ 次。

我们可以发现，数在数列中的顺序并不影响结果。所以设每一次的修改是删掉一个 $v$ 后增加一个 $w$。

首先删掉一个 $v$。

+ 如果**在线段树里**，$v$ 出现过，那么直接删掉即可；

+ 否则，利用二分，找出一个数 $res$，使得 $res$ 出现过一次，但是 $v$ 到 $res-1$ 的数都没出现过，然后将 $v$ 到 $res-1$ 的出现次数更新为 $1$，$res$ 的出现次数更新为 $0$。

然后增加一个 $w$。

+ 如果**在线段树里**，$w$ 没出现过，那么直接增加即可；

+ 否则，利用二分，找出一个数 $res$ 使得 $res$ 没出现过，但是 $w$ 到 $res-1$ 的数都出现过一次，然后将 $w$ 到 $res-1$ 的出现次数更新为 $0$，$res$ 的出现次数更新为 $1$。 这是在模拟一系列的操作后的结果。

每一次操作后利用二分求出出现过的最大数即可。

### 3 样例解释

最开始的数列经过操作后是 $[2,3,4,5]$。

第 $1$ 次操作本质上是删除 $2$ 增加 $3$。我们可以发现，$2$ 出现过，直接删除即可。$3$ 到 $5$ 都出现过但是 $6$ 没出现过，那么直接删除 $3$ 到 $5$ 并且增加 $6$。

此时数列为 $[6]$，最大值为 $6$。

第 $2$ 次操作本质上是删除 $5$ 增加 $3$。$5$ 没出现过但是 $6$ 出现过，那么将 $5$ 添加将 $6$ 删除。$3$ 没出现过，直接增加。

此时数列为 $[3,5]$，最大值为 $5$。

以此类推即可。

### 4 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 300000
int n;
int q;
int a[max_n+2];
int cnt[max_n+2];
struct T{
	int l,r,len,s,la;
}tr[max_n<<2];
void pushup(int o){
	tr[o].s=tr[o<<1].s+tr[(o<<1)|1].s;
}
void pushdown(int o){
	tr[o<<1].s=tr[o<<1].len*tr[o].la;
	tr[(o<<1)|1].s=tr[(o<<1)|1].len*tr[o].la;
	tr[o<<1].la=tr[(o<<1)|1].la=tr[o].la;
	tr[o].la=-1;
}
void build(int o,int l,int r){
	tr[o]=(T){l,r,r-l+1,0,-1};
	if(l>=r){
		tr[o].s=cnt[l];
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build((o<<1)|1,mid+1,r);
	pushup(o);
}
void upd(int o,int ql,int qr,int w){
	int l=tr[o].l,r=tr[o].r;
	if(ql<=l&&r<=qr){
		tr[o].s=tr[o].len*w;
		tr[o].la=w;
		return;
	}
	if(tr[o].la!=-1)pushdown(o);
	int mid=(l+r)>>1;
	if(ql<=mid)upd(o<<1,ql,qr,w);
	if(qr>mid)upd((o<<1)|1,ql,qr,w);
	pushup(o);
}
int query(int o,int ql,int qr){
	int l=tr[o].l,r=tr[o].r;
	if(ql<=l&&r<=qr)return tr[o].s;
	if(tr[o].la!=-1)pushdown(o);
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(o<<1,ql,qr);
	if(qr>mid)res+=query((o<<1)|1,ql,qr);
	return res;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1705E_1.in","r",stdin);
	freopen("CF1705E_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;++i)++cnt[a[i]];
	for(int i=1;i<=max_n;++i){//算出现在的最大数s
		cnt[i+1]+=(cnt[i]>>1);
		cnt[i]&=1;
	}
	build(1,1,max_n);//建树
	for(int i=1,x,v,w,ans;i<=q;++i){
		scanf("%d%d",&x,&w);
		v=a[x];
		a[x]=w;
		//删除
		if(query(1,v,v)>0)upd(1,v,v,0);
		else{
			int l=v,r=max_n,mid,res;
			while(l<=r){
				mid=(l+r)>>1;
				if(query(1,v,mid)>0){
					r=mid-1;
					res=mid;
				}
				else l=mid+1;
			}
			//res是v之后第一个存在的数
			upd(1,v,res-1,1);
			upd(1,res,res,0);
		}
		//添加
		if(query(1,w,w)==0)upd(1,w,w,1);
		else{
			int l=w,r=max_n,mid,res;
			while(l<=r){
				mid=(l+r)>>1;
				if(query(1,w,mid)==mid-w+1)l=mid+1;
				else{
					r=mid-1;
					res=mid;
				}
			}
			//res是w之后第一个不存在的数
			upd(1,w,res-1,0);
			upd(1,res,res,1);
		}
		//计算答案
		for(int l=1,r=max_n,mid;l<=r;){
			mid=(l+r)>>1;
			if(query(1,mid,max_n)>0){
				l=mid+1;
				ans=mid;
			}
			else r=mid-1;
		}
		printf("%d\n",ans);//ans是最大的数
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80111657)

By **dengziyue**

---

## 作者：Sellaris (赞：3)

- **TAG:** 线段树、二分、分治

- 提供了形式化的公式。

- 对于一个数 $i$ ，我们令 $c_i$ 为原出现次数。令 $f_i$ 为合并小于 $i$ 的数字后的个数。于是有：

$$f_i =\lfloor \frac { \lfloor \frac { \lfloor \frac { \lfloor \frac {c_1}{2} \rfloor + c_2}{2} \rfloor +c_3 }{2} \rfloor \dots +c_i}{2} \rfloor $$

- 化成递推式，即：

$$f_i =\frac {\lfloor f_{i-1} + c_i \rfloor}{2}$$ 

- 考虑线段树直接维护函数 $f$ 。发现函数和分子的奇偶性有关，于是再令 $g_i = ( f_{i-1} + c_i )\&1$ 。于是同时维护这两个函数。

- 考虑一个 $c_i$ 增加只会在 $g_i = 1$ 时有贡献 ，于是分类讨论一下并在线段树上分治找 $g_i$ 为首的最长连续相同的段 ，再区间维护即可。**减少的贡献相反。** 

- **注意段尾后一位也要更改奇偶性。**

- 查询即为二分找最右端 $f_{i-1} > 0$ 的 $i$ 。

- 综上，线段树维护 $g$ 函数单点修改，区间修改 ，单点查询，区间查询 ，分治找一个数开始的 $g$ 的最长连续相同段。维护 $f$ 函数的单点修改，区间修改，区间查询即可。分治是 $O(n \log n)$ 的 ，每次只有一个区间递归下去。所以总复杂度也是 $O(n \log n)$ 的。

- 代码：

```cpp
///*****Sellaris*****///
#pragma once
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
using namespace std;
using namespace __gnu_pbds;
const int maxn=2e5+20;
const int mo=1e9+7;
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}
inline int mod(int x){return x>=mo? x%mo :x;}

int a[maxn*5]={0};
int c[maxn*5]={0};//桶 
int d[maxn*5]={0};//删 
int f[maxn*5]={0}; 
priority_queue<int> q;
inline void q_del(){
	while(!q.empty() && d[q.top()]){
		d[q.top()]--;
		q.pop();
	}
}

int cnt;
int n,m;
struct seg{
	int l,r,len,tagg,tagf,g,f;
	int ls,rs;
}tr[maxn*6];
//区间/单点修改（加），
//区间（单点）查询，
//找从l开始g为k的极长段，
//找最靠右的fi>0的i
/*
显然c_i++只会在gi为奇数的时候使fi++,fi++又往fi+1贡献。
发现是找到从i开始到r满足g都为1的极大段满足(g_{r+1}=0)，
然后把f_l....f_r区间+1，g_l...g_r,g_r+1区间反转，
c_i--的增量以及奇偶性判断恰好是反过来的。
*///维护g_i表示f_{i-1}+c_i为奇(1)/偶(0)。

//记住线段树维护的是 f g的前缀和
inline void pushup(int p){
	tr[p].g=tr[tr[p].ls].g+tr[tr[p].rs].g;
	tr[p].f=tr[tr[p].ls].f+tr[tr[p].rs].f;
}
inline void pushdown(int p){
	if(tr[p].tagg!=-1){
		tr[tr[p].ls].tagg=tr[p].tagg;
		tr[tr[p].rs].tagg=tr[p].tagg;
		if(tr[p].tagg==0){
			tr[tr[p].ls].g=0;
			tr[tr[p].rs].g=0;
		}else {
			tr[tr[p].ls].g=tr[tr[p].ls].len;
			tr[tr[p].rs].g=tr[tr[p].rs].len;
		}
		tr[p].tagg=-1;
	}
	if(tr[p].tagf!=0){
		tr[tr[p].ls].tagf+=tr[p].tagf;
		tr[tr[p].rs].tagf+=tr[p].tagf;
		tr[tr[p].ls].f+=tr[p].tagf*tr[tr[p].ls].len;
		tr[tr[p].rs].f+=tr[p].tagf*tr[tr[p].rs].len;
		tr[p].tagf=0;
	}
}
void build(int &p,int l,int r){
	p=++cnt;
	tr[p].l=l;
	tr[p].r=r;
	tr[p].len=r-l+1;
	tr[p].tagg=-1;
	tr[p].tagf=0;
	tr[p].g=0;
	tr[p].f=0;
	if(l==r) {
		tr[p].f=f[l];
		tr[p].g=((f[l-1]+c[l])&1);
		return;
	}
	int mid=l+r>>1;
	build(tr[p].ls,l,mid);
	build(tr[p].rs,mid+1,r);
	pushup(p);
}
void gmodify(int p,int k){
	if(tr[p].l==tr[p].r) {
		tr[p].g^=1;return ;
	}
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	if(mid<k) gmodify(tr[p].rs,k);
	else gmodify(tr[p].ls,k);
	pushup(p);
}
void lenmodify(int p,int l,int r,int vg,int vf){
	if(tr[p].l>=l && tr[p].r<=r) {
		tr[p].f+=tr[p].len*vf;
		if(vg==0) tr[p].g=0;
		else tr[p].g=tr[p].len;
		tr[p].tagf+=vf;
		tr[p].tagg=vg;
		return ;
	}
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	if(l<=mid) lenmodify(tr[p].ls,l,r,vg,vf);
	if(r>mid) lenmodify(tr[p].rs,l,r,vg,vf);
	pushup(p);
}
int gquery(int p,int k){
	if(tr[p].l==tr[p].r) return tr[p].g;
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	if(mid<k) return gquery(tr[p].rs,k);
	else return gquery(tr[p].ls,k);
}

inline bool check(int p,int vg){
	if(vg==0) return (tr[p].g==0) ? true :false;
	else return (tr[p].g==tr[p].len)? true :false;
}
int findg(int p,int k,int vg){//分治，在线段树上分类讨论 nlogn
	if(tr[p].r<k) return -1;
	if(tr[p].l==tr[p].r) {
		if(!check(p,vg)) return -1;
		else return tr[p].l; 
	}
	if(tr[p].l>=k){
		if(check(p,vg)) return tr[p].r;
		pushdown(p);
		if(check(tr[p].ls,vg)) return max(tr[tr[p].ls].r,findg(tr[p].rs,k,vg));
		return findg(tr[p].ls,k,vg);
	}
	pushdown(p);///先找到 [k,n]的划分
	int mid=tr[tr[p].ls].r;
	if(mid<k) return findg(tr[p].rs,k,vg);
	else if(mid>=k){
		int reg=findg(tr[p].ls,k,vg);
		if(reg==mid) return max(reg,findg(tr[p].rs,k,vg));
		return reg;
	}
}
int findf(int p,int k){
	if(tr[p].r<k) return -1;
	if(tr[p].l==tr[p].r) {
		if(tr[p].f==0) return -1;
		else return tr[p].l;
	}
	pushdown(p);
	if(tr[tr[p].rs].f==0) return findf(tr[p].ls,k);
	else return findf(tr[p].rs,k);
}
void del(int k){
	int reg=gquery(1,k);
	if((reg%2)==0){//偶 
		int r_mx=findg(1,k,0);
		lenmodify(1,k,r_mx,1,-1);//f-1,g->奇 
		if(r_mx<maxn)gmodify(1,r_mx+1);
	}
	else gmodify(1,k);
	c[k]--;
}
void add(int k){
	int reg=gquery(1,k);
	if((reg%2)==1){//奇
		int r_mx=findg(1,k,1);
		lenmodify(1,k,r_mx,0,1);
		if(r_mx<maxn)gmodify(1,r_mx+1);
	}
	else gmodify(1,k);
	c[k]++;
}

signed main(){
    //std::ios::sync_with_stdio(false);std::cin.tie(NULL);std::cout.tie(NULL);
    //freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	n=read();
	m=read();
	for(int i=1;i<=n;i++) a[i]=read(),c[a[i]]++,q.push(a[i]);
	for(int i=1;i<maxn;i++) f[i]=(f[i-1]+c[i])/2;
	int rt=0;build(rt,1,maxn);
	while(m--){
		int x=read(),k=read();
		d[a[x]]++;
		q.push(k);q_del();
		del(a[x]);
		add(k);
		a[x]=k;
		int mx=q.top();
		int reg=findf(1,mx);
		cout<<((reg==-1)?mx:reg+1)<<endl;
	}
    return 0;
}

```


---

## 作者：jiangtaizhe001 (赞：2)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16491542.html)

[题目传送门](http://codeforces.com/problemset/problem/1705/E)
### 题目大意
黑板上有 $n$ 个数字 $a_1,a_2,\dots,a_n$，现在你可以将黑板上相同的两个数字 $x$ 擦掉，然后写上 $x+1$，求最后能得到的最大数字。  
当然你需要支持单点修改。  
$1\le n,q,a_i\le 2\times10^5$
### 题目解析
不难发现题目给定的操作比较像二进制加法。如果把所有能够合并的数字都合并，那么每个数字最多出现一次，如果出现了数字 $x$ 那么就说明二进制下从右往左第 $x$ 位是 $1$，否则是 $0$。  
考虑修改其实就是删去一个数字，然后加上一个数字。如果说把 $a_x$ 改为 $y$，也就是减去 $2^{a_x}$，加上 $2^{y}$。  
这样也就是维护一个大整数。  

考虑加上一个数字，如果这一位是 $0$，直接把这一位改成 $1$，否则找到更高位出现的第一个 $0$，把这个 $0$ 改成 $1$，然后把这一段 $1$ 改成 $0$。  
删除其实是一样的。如果这一位是 $1$，就把这一位改成 $0$，否则找到更高位的第一个 $1$，改成 $0$，然后把连续的 $1$ 改成 $0$。

也就是说需要维护一个数据结构支持区间修改，查询一个点右边第一个 $0/1$，并且能查询最高位的 $1$。  
用线段树+线段树二分维护就可以了，维护区间最小值和最大值以及区间覆盖的懒惰标记即可。

最后注意答案可能超过 $2\times 10^5$，数组要开大一点。

时间复杂度 $O(T\log n)$
```cpp
int n,T,x,y,tmp,a[maxn],t[maxn],minx[maxn<<2],maxx[maxn<<2],f[maxn<<2],L,R,C;
void up(int rt){
	minx[rt]=mmin(minx[rt<<1],minx[rt<<1|1]);
	maxx[rt]=mmax(maxx[rt<<1],maxx[rt<<1|1]);
	return;
}
void down(int rt){
	if(f[rt]!=-1){
		minx[rt<<1]=maxx[rt<<1]=f[rt<<1]=f[rt];
		minx[rt<<1|1]=maxx[rt<<1|1]=f[rt<<1|1]=f[rt];
		f[rt]=-1;
	} return;
}
void build(int l,int r,int rt){
	f[rt]=-1; if(l==r){ maxx[rt]=minx[rt]=t[l]; return; } int mid=(l+r)>>1;
	build(l,mid,rt<<1); build(mid+1,r,rt<<1|1); up(rt); return;
}
void update(int l,int r,int rt){
	if(L<=l&&r<=R){ minx[rt]=maxx[rt]=f[rt]=C; return; } int mid=(l+r)>>1; down(rt);
	if(mid>=L) update(l,mid,rt<<1); if(mid<R) update(mid+1,r,rt<<1|1); up(rt); return;
}
int query1(int l,int r,int rt){
	if(maxx[rt]==0) return INF;
	if(l==r) return l; int mid=(l+r)>>1; down(rt);
	if(mid>=L&&maxx[rt<<1]){
		int tmp=query1(l,mid,rt<<1);
		if(tmp!=INF) return tmp;
	} return query1(mid+1,r,rt<<1|1);
}
int query0(int l,int r,int rt){
	if(minx[rt]) return INF;
	if(l==r) return l; int mid=(l+r)>>1; down(rt);
	if(mid>=L&&!minx[rt<<1]){
		int tmp=query0(l,mid,rt<<1);
		if(tmp!=INF) return tmp;
	} return query0(mid+1,r,rt<<1|1);
}
int findans(int l,int r,int rt){
	if(!maxx[rt]) return -1;
	if(l==r) return l; int mid=(l+r)>>1; down(rt);
	if(maxx[rt<<1|1]) return findans(mid+1,r,rt<<1|1);
	else return findans(l,mid,rt<<1);
}
int main(){
	n=read(); T=read(); int i; for(i=1;i<=n;i++) a[i]=read(),t[a[i]]++;
	for(i=1;i<=N;i++) t[i+1]+=t[i]/2,t[i]&=1; build(1,N,1);
	while(T--){
		x=read(); y=read();
		L=a[x]; tmp=query1(1,N,1); L=R=tmp; C=0; update(1,N,1);
		if(tmp>a[x]){ L=a[x]; R=tmp-1; C=1; update(1,N,1); }
		L=y; tmp=query0(1,N,1); L=R=tmp; C=1; update(1,N,1);
		if(tmp>y){ L=y; R=tmp-1; C=0; update(1,N,1); }
		a[x]=y; print(findans(1,N,1)),pc('\n');
	} return 0;
}
```

---

## 作者：Anguei (赞：2)


## 题意

给定一个数列 $a$，可以进行若干次操作，每次操作可以选择 $a$ 中出现过至少两次的 $x$，删除掉这两个 $x$，再插入新元素 $x+1$。

有 $q$ 次询问，每次询问都**永久**地将 $a_x$ 修改为 $y$，即强制在线。求：每次询问后，进行若干次操作，可以得到的最大的数值是多少。

## 分析

将两个相同的数字 $x$ 替换为一个 $x+1$，不难想到转化为二进制数的进位：$2^x + 2^x = 2^{x + 1}$。

而将 $a_x$ 修改为 $y$，可以类似地转化为，先给二进制数减去 $2^{a_x}$ 再加上一个 $2^y$。

将所有可以进位的位置全部进位，直到不能继续操作，即得到了最大的数值。

于是这道题目就转化成了一个高精度计算二进制加减法的题目。当然，由于数据范围较大，python 等语言自带的高精度运算无法通过此题。

可以使用一段伪代码来表示这个过程。

```python
read n, q, a
for i in range(n):
    ans += 2 ** a[i]
for i in range(q):
    read k, l
    k = k - 1
    ans -= 2 ** a[k]
    a[k] = l
    ans += 2 ** a[k]
    print log2(ans)
```

注意到二进制数的特殊性：每一位上的值，要么是 $0$，要么是 $1$。同时，这道题目也具有特殊性：每次进行加减法的数字，都是 $2$ 的幂，即某个确定的二进制位。

那么我们只需要在程序中模拟二进制数加减法的进位、退位即可。

考虑用树状数组维护该二进制数的一段区间内，位为 $1$ 的个数。

如果一次加法操作之后，第 $x$ 位的值是 $2$，意味着需要进位。可以二分查找第 $x$ 位之后的第一个 $0$ 的位置 $y$，将第 $y$ 位进到 $1$，而 $x \sim y-1$ 位全部修改为 $0$。

如果一次减法操作之后，第 $x$ 位的值是 $-1$，意味着需要借位退位。可以二分查找第 $x$ 位之后第一个 $1$ 的位置 $y$，将第 $y$ 位的值修改为 $0$，而 $x \sim y-1$ 位全部修改为 $1$。

可以在树状数组当中同时维护差分数组 $d_i$ 和 $(i-1)\times d_i$ 的值，实现区间修改和区间查询。

总时间复杂度是 $\mathcal{O}((n+q)\log^2S)$，其中 $S = \sum a_i$。树状数组常数较小，可以轻松通过。


## 代码

主函数部分代码较长，主要是因为进位、退位部分代码写的比较臭，可重用性比较差，复制粘贴了三遍（

```cpp
struct FenwickRange {
  int n;
  std::vector<ll> a, b;
  FenwickRange() {}
  FenwickRange(int n) : n(n) { a.resize(n + 1, 0), b.resize(n + 1, 0); }
  int lowbit(int x) { return x & -x; }
  void rangeAdd(int l, int r, ll val) {
    if (l > r) return;
    add(a, l, val);
    add(b, l, (l - 1) * val);
    add(a, r + 1, -val);
    add(b, r + 1, -r * val);
  }
  ll rangeSum(int l, int r) {
    if (l > r) return 0;
    if (l == 0) return rangeSum(1, r);
    ll R = r * sum(a, r) - sum(b, r);
    ll L = (l - 1) * sum(a, l - 1) - sum(b, l - 1);
    return R - L;
  }

 private:
  void add(std::vector<ll>& a, int x, ll val) {
    while (x <= n) {
      a[x] += val;
      x += lowbit(x);
    }
  }
  ll sum(std::vector<ll>& a, int pos) {
    ll res = 0;
    while (pos) {
      res += a[pos];
      pos -= lowbit(pos);
    }
    return res;
  }
};

void solution() {
  int n, q;
  read(n, q);
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) read(a[i]);
  const int maxBit = 2e5 + 50;
  FenwickRange fwk(maxBit);
  for (int i = 1; i <= n; ++i) {
    fwk.rangeAdd(a[i], a[i], 1);
    if (fwk.rangeSum(a[i], a[i]) >= 2) {  // 进位
      assert(fwk.rangeSum(a[i], a[i]) == 2);
      // 二分 a[i] 这一位之后的第一个 0 的位置
      int l = 1, r = maxBit - a[i], mid = (l + r) / 2;
      while (l < r) {
        int cnt1 = fwk.rangeSum(a[i] + 1, a[i] + mid);
        int need = mid;
        if (cnt1 >= need) {
          assert(cnt1 == need);
          l = mid + 1;
        } else {
          r = mid;
        }
        mid = (l + r) / 2;
      }
      fwk.rangeAdd(a[i], a[i], -2);
      assert(fwk.rangeSum(a[i] + 1, a[i] + mid - 1) == mid - 1);
      fwk.rangeAdd(a[i] + 1, a[i] + mid - 1, -1);
      fwk.rangeAdd(a[i] + mid, a[i] + mid, 1);
    }
  }

  for (int i = 1; i <= q; ++i) {
    int x, y;
    read(x, y);  // a[x] = y
    int del = a[x];
    fwk.rangeAdd(del, del, -1);
    if (fwk.rangeSum(del, del) <= -1) {  // 退位
      assert(fwk.rangeSum(del, del) == -1);
      // 二分 del 这一位之后的第一个 1 的位置
      int l = 1, r = maxBit - del, mid = (l + r) / 2;
      while (l < r) {
        int cnt1 = fwk.rangeSum(del + 1, del + mid);
        int cnt0 = mid - cnt1;
        int need = mid;
        if (cnt0 >= need) {
          assert(cnt0 == need);
          l = mid + 1;
        } else {
          r = mid;
        }
        mid = (l + r) / 2;
      }
      fwk.rangeAdd(del, del, 2);
      assert(mid - 1 - fwk.rangeSum(del + 1, mid - 1) == mid - 1);
      fwk.rangeAdd(del + 1, del + mid - 1, 1);
      fwk.rangeAdd(del + mid, del + mid, -1);
    }
    a[x] = y;
    fwk.rangeAdd(y, y, 1);
    if (fwk.rangeSum(y, y) >= 2) {  // 进位
      assert(fwk.rangeSum(y, y) == 2);
      // 二分 y 这一位之后的第一个 0 的位置
      int l = 1, r = maxBit - y, mid = (l + r) / 2;
      while (l < r) {
        int cnt1 = fwk.rangeSum(y + 1, y + mid);
        int need = mid;
        if (cnt1 >= need) {
          assert(cnt1 == need);
          l = mid + 1;
        } else {
          r = mid;
        }
        mid = (l + r) / 2;
      }
      fwk.rangeAdd(y, y, -2);
      assert(fwk.rangeSum(y + 1, y + mid - 1) == mid - 1);
      fwk.rangeAdd(y + 1, y + mid - 1, -1);
      fwk.rangeAdd(y + mid, y + mid, 1);
    }

    // 查找最高位
    int l = 1, r = maxBit, mid = (l + r + 1) / 2;
    while (l < r) {
      int cnt1 = fwk.rangeSum(mid, r);
      if (cnt1 >= 1) {
        l = mid;
      } else {
        r = mid - 1;
      }
      mid = (l + r + 1) / 2;
    }
    print(mid);
  }
}
```

---

## 作者：jucason_xu (赞：2)



温馨提示：__本篇内容最好在学会使用 `set` 和 `map` 维护区间之后食用。__

看了一下榜，这题各种各样的办法都有，这就来写一篇 _红黑树维护区间优化二进制_ 的奇妙做法。

### 暴力思路

明显地，我们可以给序列里的每一个 $x$ 赋值，我们发现，两个 $x$ 可以合并成一个 $x+1$ ，这不是以 $2$ 为底的对数吗？

（$2^{x}+2^{x}=2^{x+1}$）

所以很自然的想到，我们可以维护一个二进制长度为 $N+\log{N}$ 的二进制数 $p$，在序列中加入 $x$，就相当于在 $p$ 中加上 $2^{x}$，删去也一样。

而“删除两个 $x$，加上一个 $x+1$”，就是再自然不过的二进制进位。由于减掉一个数，把原先的 $x+1$ 拆分成两个 $x$ 的行为，也就是退位了。序列中的最大值，也就是 $p$ 的最高位。

自此，我们把原问题转化成了在一个巨大的二进制数上，每次挑出其中第 $a_k$ 位减一，第 $l$ 位加一的问题。

乐观的人就会想到，其实虽然二进制数的长度是 $N$ 级别的， __但是每次只对某一位进行操作，不太可能每次都跑满__ 。有些人甚至想到对于一个二进制数，每次在尾部加一的时间复杂度是 $O(1)$ 的，那么这样也可以跑过去咯？

错！关键在于我们不仅有 $+1$ 的操作，还有 $-1$ 的操作！

考虑极端的情况，假如 $p$ 原来每一位都是 $1$，现在在它的个位 $+1$，就要跑满整个 $p$，再在它的个位 $-1$，又要跑满整个 $p$，回到最初的情况。如果我们每次循环执行这两次操作，每次操作就是 $O(N)$，$q$ 次操作就是 $O(Nq)$。

这里贴出暴力的代码，它会 TLE on test 7。

我们用一个 `bitset` 来维护二进制数，用 `tp` 存储当前的最高位。

```cpp

#include<bits/stdc++.h>
using namespace std;
#define rd(i,n) for(int i=0;i<n;i++)
#define rp(i,n) for(int i=1;i<=n;i++)
typedef long long ll;
int n,q,a[200005],tp,k,l;
bitset<400005>bs;
inline void add(int x){
	while(bs[x]){
		bs[x]=0;
		x++;
	}
	tp=max(tp,x),bs[x]=1;
}
inline void mns(int x){
	while(!bs[x]){
		bs[x]=1;
		x++;
	}
	bs[x]=0;
	while(!bs[tp])tp--;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	tp=0;
	cin>>n>>q;
	rp(i,n)cin>>a[i];
	rp(i,n)add(a[i]);
	rp(i,q){
		cin>>k>>l;
		if(a[k]!=l){
			mns(a[k]);
			a[k]=l;
			add(a[k]);
		}
		cout<<tp<<endl;
	}
	return 0;
}

```
### 区间优化

暴力维护二进制数的办法正式寄了。我们想想有什么办法可以优化它。

好巧不巧，我们来回顾 [这场比赛的 D](https://codeforces.com/contest/1705/problem/D) 。想想我们在 D 中用了什么技巧呢？储存连续的 $1$ 组成的区间！所以，作者从这里有端联想，能否只储存二进制数中连续的 $1$ 构成的区间， __从而使得每一次的操作只是对单一的区间进行操作__ ？

（我的意思并不是这场比赛的 D 和 E 互相关联，只是想阐释自己真实的思路历程）

我们理清思路，来看看加一和减一的操作对应到区间上是什么情况。

1. 对于 $x$ 位 $+1$ 的操作：

   + 如果落在 $0$ 上，建立新区间 $[x,x]$，然后将其和 $[a,x-1]$、$[x+1,b]$（如果存在）合并。
   
   + 如果落在 $1$ 上，这个区间 $[l,r]$ 从 $x$ 位断开，$[l,x-1]$ 不变，$[x,r]$ 都变成 $0$，然后 $r+1$ 的位置变成 $1$，建立新区间 $[r+1,r+1]$。将其和 $[r+2,b]$（如果存在）合并。
   
2. 对于某一位 $-1$ 的操作：

   + 如果落在 $1$ 上，考虑它所属的区间 $[l,r]$，从 $x$ 处断开成 $[l,x-1]$ 和 $[x+1,r]$。$x$ 变成 $0$。
   
   + 如果落在 $0$ 上，找到后面的一个区间 $[l,r]$（$l>x$），把 $[x,l-1]$ 全部变成 $1$，建立新区间，原来的区间变成 $[l+1,r]$。将新区间和 $[a,x-1]$（如果存在）合并。

这样我们就分析完了全部可能的情况和对应的做法。

大多数区间维护都是使用 `set` ，可惜作者水平太菜，把 `set` 写 T 了。那么，我们使用 `map` 来存储每一个连续 $1$ 区间。

如何使用 `map` 维护区间呢？很简单。 `map` 有一个重要的性质，就是 __内部的数据有序__ ！这就促使我们用 `map` 的下标作为区间左端点，存储区间右端点。

说到底，我们需要完成这么几件事情：

1. 查找 $x$ 被哪个区间包含

1. 查找 $x$ 的后一个区间是什么

2. 将区间 $[l,r]$ 断开

3. 将区间和两边的相邻区间合并

但是这些却是有技巧的。

对于操作 $2$，直接 `upper_bound` ，记得判断读到的是否是 `end`

对于操作 $1$，用 `upper_bound` 得到的迭代器前移，记得判断前移之前是否是 `begin`

对于操作 $3$，记得在删除一个区间的时候使用 `erase` 而不是单纯的赋为 $0$，否则仍会在 `map` 中存在。

对于操作 $4$，后面的比较好判断，查找左端点是 $r+1$ 的区间。对于前面的，先 `lower_bound` 再前移，判断相邻即可。

输出的时候，输出最后一个区间（也就是 `rbegin` ）的右端点即可。

### AC代码

```cpp

#include<bits/stdc++.h>
using namespace std;
#define rp(i,n) for(int i=1;i<=n;i++)
int n,q,a[200005],k,l;
map<int,int>mp;
void add(int x){
	auto k=mp.upper_bound(x);
	if(k!=mp.begin()){//如果存在左端点比x小的区间
		k--;
		int r=k->second,l=k->first;
		if(r>=x){//如果包含x
			if(l<x)mp[l]=x-1;
			else mp.erase(l);
			x=r+1;//插入[r+1,r+1]，统一后面的程序
		}
	}mp[x]=x;
	if(mp.count(x+1)){//如果有相邻右区间
		int r=mp[x+1];
		mp.erase(x+1);
		mp[x]=r;
	}
	k=mp.upper_bound(x);
	k--;
	int r=k->second;
	if(k==mp.begin())return;
	k--;//如果有相邻左区间
	int d=k->first;
	if(k->second==x-1){
		mp[d]=r;
		mp.erase(x);
	}
}
void mns(int x){
	auto k=mp.upper_bound(x);
	if(k==mp.begin()){//如果不存在左端点比x小的区间
		int l=k->first,r=k->second;
		mp.erase(k);
		if(r>l)mp[l+1]=r;//退位
		mp[x]=l-1; 
	}else{
		k--;
		if(k->second>=x){//如果被包含
			int l=k->first,r=k->second;
			mp.erase(k);
			if(l<x)mp[l]=x-1;
			if(r>x)mp[x+1]=r;//在x处断开
			return;
		}else{
			k++;
			int l=k->first,r=k->second;
			mp.erase(k);
			if(r>l)mp[l+1]=r;//退位
			mp[x]=l-1;
		}
	}
   //此时，如果x和x的右边都是1，一定是退位得到的，处在同一个区间中，已经不可能有相邻右区间了，查找左区间即可
	k=mp.lower_bound(x);
	if(k==mp.begin())return;
	k--;
	int l=k->first,r=k->second;
	if(r==x-1){
		int d=mp[x];
		mp.erase(x);
		mp[l]=d;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>q;
	rp(i,n)cin>>a[i];
	rp(i,n)add(a[i]);
	rp(i,q){
		cin>>k>>l;
		if(a[k]!=l){
			mns(a[k]);
			add(a[k]=l);
		}
		cout<<mp.rbegin()->second<<endl;
	}
	return 0;
}
//Accepted!

```



---

## 作者：喵喵喵__ (赞：1)

正解是线段树，但是题目性质很适合珂朵莉树。

题意相当于模拟一个 $ 2 \times  10^5 $ 位（其实略微大一点）的二进制数 $w$ , $w = \sum_{i = 1}^{n}2^{a_i}$ 。
每一次操作相当于 $w = w - 2^{a_k} + 2^l$ 并询问 $w$ 的最高二进制位。

可能会想到直接模拟，但是不可。因为减法借位可能会将一段区间的 `0` 修改为 `1`，加法进位可能会将一段区间的 `1` 修改为 `0`。于是发现区间推平很适合珂朵莉树，且查询高位 `1` 很容易实现。

注意在查询时，推平末尾 `0` 区间，以免复杂度退化到 $O(q\cdot \max_{i = 1}^{n} a_i) $




```cpp

#include<iostream>
#include<set>

using namespace std;

#define MAXn 210005
#define ll long long
#define cnd Chtholly_Node
#define cit set<cnd>::iterator

int a[MAXn];

struct Chtholly_Node {
	int l, r;
	mutable int v;
	Chtholly_Node(int l, int r = 0, int v = 0) :l(l), r(r), v(v) {}
	bool operator < (const cnd& o)const {
		return l < o.l;
	}
};

struct ChthollyNotaSeniorious_Tree {
	set<cnd> s;

	cit split(int p) {
		cit it = s.lower_bound(cnd(p));
		if (it != s.end() && it->l == p) {
			return it;
		}
		it--;
		if (it->r < p)return s.end();
		int l = it->l, r = it->r, v = it->v;
		s.erase(it);
		s.emplace(l, p - 1, v);
		return s.emplace(p, r, v).first;
	}
	void assign(int l, int r, int v) {
		cit itr = split(r + 1), itl = split(l);
		s.erase(itl, itr);
		s.emplace(l, r, v);
	}


	void add(int p) {
		cit itr = split(p + 1), itl = split(p);
		if (itl->v == 0) {
			itl->v = 1;
			return;
		}
		int l = itl->l;
		for (; itl->v; itl++) {
		}
		int r = itl->l - 1;
		assign(l, r, 0);
		split(r + 2);
		split(r + 1)->v = 1;
	}
	void sub(int p) {
		cit itr = split(p + 1), itl = split(p);
		if (itl->v == 1) {
			itl->v = 0;
			return;
		}
		int l = itl->l;
		for (; itl->v == 0; itl++) {
		}
		int r = itl->l - 1;
		assign(l, r, 1);
		split(r + 2);
		split(r + 1)->v = 0;
	}
	int top() {
		cit itr = s.end();
		itr--;
		for (;; itr--) {
			if (itr->v == 1) {
           //这里得推平一下末尾区间
				assign(itr->r + 1, (--s.end())->r, 0);
				return itr->r;
			}
			if (itr == s.begin()) {
				break;
			}
		}
		return 0;
	}
}cht;

int main() {
	int n, m;
	cin >> n >> m;

	cht.s.emplace(1, MAXn, 0);

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cht.add(a[i]);
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		cht.sub(a[u]);
		a[u] = v;
		cht.add(a[u]);
		cout << cht.top() << "\n";
	}
	return 0;
}

```





---

## 作者：Priestess_SLG (赞：0)

可以发现题目模拟的其实就是二进制加法和二进制减法。因此考虑用一个线段树来维护每一位的值（$0/1$），然后对于每一个操作：

+ 若要让第 $i$ 位 $+1$，则：
  + 若第 $i$ 位的值本来是 $0$，则直接将其变为 $1$。
  + 否则从 $i$ 开始往后找到第一个为 $0$ 的位 $p$，然后把 $p$ 位变为 $1$，$[i,p-1]$ 一段区间内所有位都变为 $0$。
+ 若要让第 $i$ 位 $-1$，则：
  + 若第 $i$ 位的值本来是 $1$，则直接将其变为 $0$。
  + 否则从 $i$ 开始往后找到第一个为 $1$ 的位 $p$，然后把 $p$ 位变为 $0$，$[i,p-1]$ 一段区间内所有位都变为 $1$。

答案就是从前往后第一个 $1$ 的位。

区间推平可以直接维护 lazy tag 处理，而其余的操作可以用线段树二分处理，但是【】不喜欢线段树二分，因此她选择使用二分套线段树求和，时间复杂度为 $O(n\log^2n)$。使用峮带菜的快读快写然后卡一卡常就能卡过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int N = 200030;
const int mod = 1e9 + 7;
int a[N], b[N];
struct Node {
    int l, r, sum, tag;
    void init(int p) {
        l = r = p;
        sum = a[p], tag = -1;
    }
    void push(int v) {
        sum = (r - l + 1) * v, tag = v;
    }
};
Node operator+(const Node &l, const Node &r) {
    return {l.l, r.r, l.sum + r.sum, -1};
}
class SegmentTree {
    Node tree[N << 2];
public:
    void pushup(int rt) {
        tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
    }
    void pushdown(int rt) {
        if (~tree[rt].tag) {
            tree[rt << 1].push(tree[rt].tag);
            tree[rt << 1 | 1].push(tree[rt].tag);
            tree[rt].tag = -1;
        }
    }
    void build(int l, int r, int rt) {
        if (l == r) return tree[rt].init(l);
        int mid = l + r >> 1;
        build(l, mid, rt << 1);
        build(mid + 1, r, rt << 1 | 1);
        pushup(rt);
    }
    void modify(int rt, int ll, int rr, int v) {
        int &l = tree[rt].l, &r = tree[rt].r;
        if (ll <= l && r <= rr) return tree[rt].push(v);
        int mid = l + r >> 1;
        pushdown(rt);
        if (ll <= mid) modify(rt << 1, ll, rr, v);
        if (mid < rr) modify(rt << 1 | 1, ll, rr, v);
        pushup(rt);
    }
    int query(int rt, int ll, int rr) {
        int &l = tree[rt].l, &r = tree[rt].r;
        if (ll <= l && r <= rr) return tree[rt].sum;
        int mid = l + r >> 1, s = 0;
        pushdown(rt);
        if (ll <= mid) s = query(rt << 1, ll, rr);
        if (mid < rr) s += query(rt << 1 | 1, ll, rr);
        return s;
    }
} sgt;
int slv[N];
namespace aimat {
    char *p1,*p2,buf[100010],obuf[100010],*p3=obuf;
    #define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
    #define pc(x) (p3==obuf+100000&&fwrite(p3=obuf,1,100000,stdout),*p3++=x)
    int read(){
        int x=0;
        char c=gc();
        while(c<48)c=gc();
        while(47<c)x=(x<<3)+(x<<1)+(c&15),c=gc();
        return x;
    }
    void write(int x){
        if(9<x)write(x/10);
        pc(x%10|48);
    }
} using namespace aimat;
signed main() {
    // cin.tie(0)->sync_with_stdio(false);
    int n, q;
    n = read(), q = read();
    for (int i = 1; i <= n; ++i) {
        int x;
        x = read();
        ++a[x];
        slv[i] = x;
    }
    for (int i = 1; i + 1 < N; ++i) a[i + 1] += a[i] >> 1, a[i] &= 1;
    sgt.build(1, N - 1, 1);
    while (q--) {
        int k, l;
        k = read(), l = read();
        // cin >> k >> l;
        do {
            int la = slv[k];
            int val = sgt.query(1, la, la);
            if (val == 1) {
                sgt.modify(1, la, la, 0);
            } else {
                int l = la + 1, r = N - 1, best = -1;
                while (l <= r) {
                    int mid = l + r >> 1;
                    int tv = sgt.query(1, la, mid);
                    if (tv) best = mid, r = mid - 1;
                    else l = mid + 1;
                }
                // cerr << "best = " << best << '\n';
                sgt.modify(1, best, best, 0);
                sgt.modify(1, la, best - 1, 1);
            }
        } while (0);
        slv[k] = l;
        do {
            int val = sgt.query(1, l, l);
            if (!val) {
                sgt.modify(1, l, l, 1);
            } else {
                int ll = l;
                int l = ll + 1, r = N - 1, best = -1;
                while (l <= r) {
                    int mid = l + r >> 1;
                    int tv = mid - ll + 1 - sgt.query(1, ll, mid);
                    if (tv) best = mid, r = mid - 1;
                    else l = mid + 1;
                }
                sgt.modify(1, best, best, 1);
                sgt.modify(1, ll, best - 1, 0);
            }
        } while (0);
        do {
            int l = 1, r = N - 1, best = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                int tv = sgt.query(1, mid, N - 1);
                if (tv > 0) best = mid, l = mid + 1;
                else r = mid - 1;
            }
            // cout << best << '\n';
            write(best); pc('\n');
        } while (0);
    }
    fwrite(obuf,1,p3-obuf,stdout);
    return 0;
}


```

---

## 作者：sunkuangzheng (赞：0)

$\textbf{CF1705E *2300}$

>  - 对于序列 $a$，一次操作可以选择一对 $i,j$ 满足 $a_i = a_j$，删去 $a_i,a_j$ 并添加 $a_i+1$。问最后序列的最大值最大是多少。
>  - 有 $q$ 次单点修改。
>  - $1 \le n,q \le 2\cdot 10^5$。

显然题意就是维护二进制数 $x$，支持某一位上的加减 $1$ 并输出最高位 $1$ 的位置。

注意到如果只有加法操作我们暴力做复杂度是均摊正确的，但是减法会使得我们的复杂度假掉。因此我们分开维护加减，维护 $a,b$ 表示当前 $x = a -b$，现在就只需要加法操作。

考虑我们怎么根据 $a,b$ 计算 $x$ 的最高位，这里是一些无聊的分讨。为了方便实现，注意 $a_i = b_i = 1$ 时，我们将其全部归零。记 $a$ 的最高位是 $p$，$b$ 的最高位是 $q$。

- 如果 $b = 0$，那么答案是 $p$。
- 如果 $q \ne p - 1$，那么答案是 $p-1$。
- 否则，找到 $b$ 的极长 $1$ 前缀，记前缀末尾的 $1$ 是 $r$，那么做完这些位的减法后 $a$ 的最高位变成 $r$ 且 $b$ 的 $r-1$ 位不是 $1$，转化为第二种情况。

使用 set 简单维护即可，复杂度 $\mathcal O(n \log n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 22.07.2024 16:55:03
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#else
#define debug(...) 0
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,m,mx,a[N],x,y; set<int> s[2],t[2];
void fl1t(int x,int o){
    if(!s[o].count(x)) s[o].insert(x),t[o].erase(x);
    else s[o].erase(x),t[o].insert(x);
    if(s[o].count(x) && s[o^1].count(x)) s[o].erase(x),s[o^1].erase(x),t[o].insert(x),t[o^1].insert(x);
}void add(int x,int o){ for(;;fl1t(x ++,o)) if(!s[o].count(x)) return fl1t(x,o);}
int qry(){
    if(!m) debug(s[0],s[1]);
    if(!s[0].size()) return 0;
    int x = *(--s[0].end());
    if(!s[1].size() || s[0].size() > 1 && *(--(--s[0].end())) > *(--s[1].end())) return x;
    if(!t[1].size()) return 1;
    int y = (int)*(--t[1].upper_bound(x - 1)) + 1;
    auto it = s[0].upper_bound(y-1); int pos = *s[1].begin();
    if(it == s[0].begin() || pos >= y) return min(x-1,y - (pos < y));
    int p1 = *--s[1].upper_bound(y-1);
    return min(x-1,y - (p1 < y && p1 > *(--it)));
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= n;i ++) cin >> a[i],add(a[i],0);
    for(int i = 1;i <= 203333;i ++) t[0].insert(i),t[1].insert(i);
    debug(s[0]);
    while(m --)
        cin >> x >> y,add(a[x],1),debug("s",s[0],s[1]),add(a[x] = y,0),debug("e",s[0],s[1]),cout << qry() << "\n",debug("ok");
}
```

---

## 作者：封禁用户 (赞：0)

思路：由于 $1\leq a_i\leq2\times 10^5$，考虑从值域入手。将序列 $a$ 视为一个数字 $num$ ，则 $a_i$ 为 $num$ 进制下第 $a_i$ 位，从低位到高位依次进位。因此，问题转化为维护高精度二进制数字。

每次将 $a_k$ 修改为 $l$：相当于删除 $a_k$，添加 $l$。

删除 $a_k$：相当于 $num$ 减去 $2^{a_k}$，相当于 $num$ 二进制下第 $a_k$ 为减去 $1$，可能会向高位连续借 $1$，直至高位第一个 $a_{pos}=1$ 出现为止，借位结束后 $a_{pos}=0,a_i=1(i\in [k,pos-1])$。

添加 $l$：相当于 $num$ 增加 $2^l$，相当于 $num$ 二进制下第 $l$ 位增加 $1$，可能会向高位连续进 $1$，直至高位第一个 $a_{pos}=0$ 出现为止，进位结束后 $a_{pos}=1,a_i=0(i\in [k,pos-1])$。

考虑通过线段树维护上述过程：

由于 $1\leq n,a_i\le 2\times 10^5$，考虑长度为 $2\times 10^5$ 的序列 $a$ 中所有元素都为 $2\times 10^5$，一共进行 $\log_2 (2\times 10^5)$ 次合并，出现的最大数不超过 $2\times 10^5+100$，因此线段树的边界为 $[1,2\times 10^5+100]$。

对于删除操作，查询 $num$ 二进制下第 $a_k+1$ 位至第 $2\times 10^5+100$ 位之间，最靠近第 $a_k$ 位的最大值 $pos$，对 $[a_k,pos-1]$ 进行区间修改即可。

对于添加操作，查询 $num$ 二进制下第 $a_k+1$ 位至第 $2\times 10^5+100$ 位之间，最靠近第 $a_k$ 位的最小值 $pos$，对 $[a_k,pos-1]$ 进行区间修改即可。

代码就不放了。

---

## 作者：yanhao40340 (赞：0)

```
高精TLE，压位出奇迹。
```
### 题意
给定一个长度为 $n$ 的序列 $a$，对于序列 $a$ 中的相同的两个数 $x$，可以用一次操作将它们变成 $x+1$，求操作后序列 $a$ 中的最大值。

数据范围：$n \le 2 \times 10^5$ 。
### 分析
~~来自 2048 忠粉的窃喜。~~ 

由于题意中的操作性质较少，我们可以构造序列 $b$，使得 $b_i=2^{a_i}$，则题目中的操作对于序列 $b$ 来说相当于普通加法。那么题目就变成了这样：

- 给定长度为 $n$ 的序列 $b$，其中任意的 $b_i$ 均是 $2$ 的整数次幂。

- 定义一次操作为：将 $b$ 中相同的两个数用它们的和替代。

- 求 $\log_2{\max b}$ 的最大值。

显然将能加的都加起来即为最大值，但是寻找相同的数最快需要 $O(n)$，会 TLE，所以考虑二进制意义下的和 $s$。

如果数字 $b_x$ 没有被操作，那么在它对 $s$ 的贡献就是把和的第 $a_x$ 位变成 $1$，且下一位不会进位。（如果有进位，说明其它数合成了 $b_x$，那么它就可以被操作，矛盾。）

所以，没有被操作的数对 $s$ 的最大值无影响。

那么答案即为 $s$ 的最高位的 $1$ 所在的位置。
### 做法
因为 $n \le 2 \times 10^5$，所以需要高精度，但是一般的高精度的时间复杂度为 $O(n^2)$，是无法通过此题的。

对此，解决方案有以下几种（我只想到这些）：

- 用 set 或 map 维护区间中连续的 $1$，时间复杂度 $O(n \log n)$，可以通过。

- 打线段树，码量较大，时间复杂度 $O(n \log n)$，可以通过。

- bitset + 卡常，同机房巨佬过了，我反正没过。

- 压位高精，时间复杂度 $O(\dfrac{n^2}{B})$，是否通过取决于 $B$（压的位数）。

- 奇怪的方法……

我采用了压位高精的方法，但是用 long long 是过不了的，得用 __int128。（逃）

代码见 [link](https://codeforces.com/contest/1705/submission/165622299)。

---

## 作者：wmrqwq (赞：0)

一句话题解。

注意到题目中的序列可以直接转化成一个二进制数，具体的，对于一个数字 $a_i$ 就给这个二进制数的第 $a_i$ 位 $+1$，然后进行进位，原问题变成维护 $+2^k$ 或 $-2^k$。

注意到最多只改变二进制数中的一位，对于每次操作连续段变化数量 $\le 2$，因此直接 ODT 维护即可。

时间复杂度 $O(n + q + V \log V)$，其中 $V$ 为值域。

---

## 作者：intel_core (赞：0)

转化问题：求二进制数 $S=\sum 2^{a_i}$ 的最高位，需要支持 $\{a_i \}$ 的修改。

相当于快速维护一个二进制数的加或减一个 $2$ 的方幂。

可以无脑用 $\text{bitset}$ 模拟二进制加减法，复杂度 $O(\frac{nq}{w})$，可以手写压位跑过去。

但更简单的方法是用珂朵莉树维护二进制数中连续的 $1$ 段。

加上一个 $2^x$ 相当于加上一个 $1$ 段或者把一个 $1$ 段从第 $x$ 段以上的部分去掉再加上一个单独的 $1$。

减掉 $2^x$ 同理，可以用珂朵莉树轻松完成。

复杂度 $O(n \log n)$。

---

