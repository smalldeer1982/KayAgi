# Mass Change Queries

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You have to process $ q $ queries to this array; each query is given as four numbers $ l $ , $ r $ , $ x $ and $ y $ , denoting that for every $ i $ such that $ l<=i<=r $ and $ a_{i}=x $ you have to set $ a_{i} $ equal to $ y $ .

Print the array after all queries are processed.

## 样例 #1

### 输入

```
5
1 2 3 4 5
3
3 5 3 5
1 5 5 1
1 5 1 5
```

### 输出

```
5 2 5 4 5 ```

# 题解

## 作者：人间过客 (赞：19)

~~线段树动态开点裸题~~

这是网上的一种说法，虽然我并不知道有多简单。

对一个序列进行操作，最常见的方法就是用线段树了。

可以发现，虽然序列很长，对整个序列用线段树维护比较困难（虽然大部分人都是这么搞的），但是不同的权值最多只有100种。因此，如果我们对不同的权值开线段树，最多也不过100棵线段树。

现在考虑对每个权值建一棵线段树。我们可以用是否存在儿子节点来表示某区间内是否有该权值。具体来说，若在权值ｘ的线段树内，对于一个区间［ｌ，ｒ］所对应的节点，如果这棵树内有该节点，说明该区间内有权值ｘ；反之若该节点不存在（为空），说明该区间内无权值ｘ。这样，我们可以往下递推到区间［ｌ，ｌ］，此时区间变成一个点，如果该节点存在，就说明序列中ｌ处权值为ｘ。

当我们需要进行一个操作，对区间［ｌ，ｒ］中ｘ变为ｙ时，就相当于把ｘ的线段树中区间［ｌ，ｒ］中的节点取出，放进ｙ的线段树中，也就是合并线段树。并且，由于序列中同一位置在某一时刻有且仅有一个权值，不会产生ｙ中也有对应节点的冲突。

最后，我们对100棵线段树都扫一遍，就可以得到最终序列了。

在这以上过程中，我们发现，这棵线段树除了动态开点，什么都不用保存，~~似乎真的很简单？~~

另外，题目并没有保证ｘ一定不等于ｙ，所以CF的数据绝对会卡特殊情况的，这时特判一下就可以了。

code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;
typedef pair<int,int> PII;

inline int rd() {
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0' or ch>'9'){if(ch=='-')ff=-1;ch=getchar();}
	while(ch>='0' and ch<='9'){xx=xx*10-'0'+ch;ch=getchar();}
	return xx*ff;
}

const int N=1e7+10;
const int M=2e6+10;
const int INF=(1<<30);

int n,m;
int cnt;
int lson[N],rson[N];

int root[120];

int merge(int a,int b)
{
	if(!a or !b)return a | b;
	
	lson[a] = merge(lson[a] , lson[b]);
	rson[a] = merge(rson[a] , rson[b]);
	
	return a;
}

void init(int& i,int l,int r,int goal)
{
	if(l > goal or r < goal)return ;
	
	if(!i)i = ++cnt;
	
	if(l == r)return ;
	
	int mid = (l + r) >> 1;
	init(lson[i],l,mid,goal);
	init(rson[i],mid+1,r,goal);
}

void modify(int& a,int& b,int l,int r,int x,int y)
{
	if(!a)return ;
	if(l > y or r < x)return ;
	
	if(l >= x and r <= y) 
	{
		b = merge(a , b);a = 0;
		return;
	}
	if(!b)
	{
		b = ++cnt;
	}
	int mid = (l + r) >> 1;
	modify(lson[a],lson[b],l,mid,x,y);
	modify(rson[a],rson[b],mid+1,r,x,y);
}

int ans[M];

void print(int i,int l,int r,int c)
{
	if(!i)return ;
	if(l == r)
	{
		ans[l] = c;
		return ;
	}
	int mid = (l + r) >> 1;
	print(lson[i],l,mid,c);
	print(rson[i],mid+1,r,c);
}

int main()
{
	n = rd(); 
	for(int i=1;i<=n;i++)
	{
		int x = rd();
		init(root[x],1,n,i);
	}
	
	m = rd();
	while(m--)
	{
		int l = rd(),r = rd();
		int x = rd(),y = rd();
		
		if(x == y)continue;//非常重要的一步，避免相同元素的更换出错 
		
		modify(root[x],root[y],1,n,l,r);
	}
	
	for(int i=1;i<=100;i++)
		print(root[i],1,n,i);
	
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	
	return 0;
}
```


---

## 作者：Limit (赞：18)

# 题目大意

给出一个序列,支持区间将某个数变为某个数,输出最终的序列.

# 分析

序列中的元素只有 $100$ 种,所以直接线段树上每个节点记录每个数出现的次数就好了.

但是,这样的做法时间复杂度并不优秀.

那么就从这个输出去考虑,可以发现在最终结果前没有必要知道每个点确切的值,那么考虑对每一种数建一颗线段树,将一种颜色变为令一种颜色只需要在原来的线段树中将修改区间部分分裂出来,在合并到变成的颜色的线段树中,最后遍历所有树就好了.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=2e5+7;
int n,m;
int arr[MAXN*2];
int answer[MAXN];
int root[MAXN*2];
struct SegmentTree//一颗动态开点的线段树
{
	int lson,rson;
	int num;
}sgt[MAXN*100];
int sgt_cnt=0,tot=0;
int rubbish[MAXN*100];//空间回收用的垃圾桶
#define LSON (sgt[now].lson)
#define RSON (sgt[now].rson)
#define MIDDLE ((left+right)>>1)
#define LEFT LSON,left,MIDDLE
#define RIGHT RSON,MIDDLE+1,right
#define NOW now_left,now_right
int NewPoint()//一个新个节点
{
	if(tot)
	{
		return rubbish[tot--];//如果垃圾桶不是空的就从垃圾桶里拿
	}
	return ++sgt_cnt;//否则就用一个全新的
}
void DeletePoint(int &now)//删除节点
{
	sgt[now].lson=sgt[now].rson=sgt[now].num=0;//注意要清空
	rubbish[++tot]=now;//扔垃圾桶里
	now=0;
}
void Merge(int &tree1,int &tree2,int left=1,int right=n)//合并两颗线段树
{
	if(!tree1||!tree2)
	{
		tree1+=tree2;
		tree2=0;//注意要将tree2改成0
		return;
	}
	if(left==right)
	{
		sgt[tree1].num+=sgt[tree2].num;
		DeletePoint(tree2);//删除节点,节省空间
		return;
	}
	Merge(sgt[tree1].lson,sgt[tree2].lson,left,MIDDLE);//继续向下合并
	Merge(sgt[tree1].rson,sgt[tree2].rson,MIDDLE+1,right);
	DeletePoint(tree2);
}
void Split(int now_left,int now_right,int &tree1,int &tree2,int left=1,int right=n)//将线段树中的一段区间分裂出来,代码可以参考模板题中的题解
{
	if(right<now_left||now_right<left)
	{
		return;
	}
	if(!tree1)
	{
		return;
	}
	if(now_left<=left&&right<=now_right)
	{
		tree2=tree1;
		tree1=0;
		return;
	}
	if(!tree2)
	{
		tree2=NewPoint();
	}
	Split(NOW,sgt[tree1].lson,sgt[tree2].lson,left,MIDDLE);
	Split(NOW,sgt[tree1].rson,sgt[tree2].rson,MIDDLE+1,right);
}
void Updata(int place,int &now,int left=1,int right=n)//单点修改
{
	if(place<left||right<place)
	{
		return;
	}
	if(!now)
	{
		now=NewPoint();
	}
	if(left==right)
	{
		sgt[now].num=1;//直接修改成1
		return;
	}
	Updata(place,LEFT);
	Updata(place,RIGHT);
}
void GetAnswer(int num,int now,int left=1,int right=n)//将这个线段树放到答案上
{
	if(!now)
	{
		return;
	}
	if(left==right)
	{
		answer[left]+=sgt[now].num*num;//计算这个位置的数
		return;
	}
	GetAnswer(num,LEFT);
	GetAnswer(num,RIGHT);
}
int main()
{
	scanf("%d",&n);
	REP(i,1,n)
	{
		scanf("%d",&arr[i]);
		Updata(i,root[arr[i]]);
	}
	scanf("%d",&m);
	int cnt=n;
	int left,right,x,y;
	int split_root;
	REP(i,1,m)
	{
		scanf("%d%d%d%d",&left,&right,&x,&y);
		if(root[x])//如果在现在的序列中存在x那么修改
		{
			arr[++cnt]=y;//方便最后的查询,将y放入数组
			split_root=0;
			Split(left,right,root[x],split_root);//在序列中将这段区间的x分裂出来
			Merge(root[y],split_root);//合并到y上面
		}
	}
	sort(arr+1,arr+1+cnt);//排序去重
	arr[0]=0;
	REP(i,1,cnt)
	{
		if(arr[i]^arr[i-1])
		{
			GetAnswer(arr[i],root[arr[i]]);//记录答案
		}
	}
	REP(i,1,n)
	{
		printf("%d ",answer[i]);//输出答案
	}
	return 0;
}
```



---

## 作者：wcyQwQ (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/CF911G)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/06/26/CF911G%20Mass%20Change%20Queries/)

## 前言

线段树里开了一百多个懒标记，直接暴力艹过。

### 前置芝士

线段树


## 分析

首先，这题最引人注目的就是这个 $[1,100]$ 的值域，那看到这种值域，我们考虑在线段树的每个节点开一个数组 $cover$，$cover[i]$ 就表示数 $i$ 现在变成了什么数。

对每个修改操作，因为值域很小，所以我们每次修改的时候直接遍历一下这个节点的 $cover$ 数组，把其中等于 $x$ 的改成 $y$ 就可以。

对于每个查询操作，我们直接从树根递归到叶子节点，把叶子结点变成的数输出即可。

最后注意一下，在懒标记下传的时候直接把左右节点的值暴力赋为父节点上对应的值即可。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10, M = 110;
struct node
{
    int l, r;
    int val;
    int cover[M];
} t[N << 2];
int a[N];

inline int read()
{
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline void build(int p, int l, int r)
{
    t[p].l = l;
    t[p].r = r;
    for (int i = 1; i <= 100; i++)
        t[p].cover[i] = i;
    if (l == r)
    {
        t[p].val = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

inline void pushdown(int p)
{
    node &u = t[p], &l = t[p << 1], &r = t[p << 1 | 1];
    for (int i = 1; i <= 100; i++)
        l.cover[i] = u.cover[l.cover[i]], r.cover[i] = u.cover[r.cover[i]];
    for (int i = 1; i <= 100; i++)
        u.cover[i] = i;
}

inline void modify(int p, int l, int r, int x, int y)
{
    if (l <= t[p].l && t[p].r <= r)
    {
        for (int i = 1; i <= 100; i++)
            if (t[p].cover[i] == x)
                t[p].cover[i] = y;
        return;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (l <= mid) modify(p << 1, l, r, x, y);
    if (r > mid) modify(p << 1 | 1, l, r, x, y);
}

inline void print(int p)
{
    if (t[p].l == t[p].r)
    {
        printf("%d ", t[p].cover[t[p].val]);
        return;
    }
    pushdown(p);
    print(p << 1);
    print(p << 1 | 1);
}

int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    build(1, 1, n);
    int m = read();
    while (m--)
    {
        int l = read(), r = read(), x = read(), y = read();
        modify(1, l, r, x, y);
    }
    print(1);
    return 0;
}
```



---

## 作者：tommymio (赞：12)

非常 $\text{Naive}$ 的一道题。

看到 $\max a_i\leq 100$，我们可以想到开 $100$ 棵线段树，第 $i$ 棵线段树维护一下 $l,r$ 内值为 $i$ 的数的个数，暴力乱搞。但是 $O(nm \log n)$ 的空间复杂度会爆炸，怎么办呢？

使用动态开点线段树即可避免 $\text{MLE}$。对于每个操作 $l,r,x,y$，我们将第 $x$ 棵线段树上 $l,r$ 的值清零，第 $y$ 棵线段树上的值对应加上第 $x$ 棵线段树清零前的值。但这样并不比暴力更优秀（

事实上，我们上述操作其实本质就是，在第 $x$ 棵线段树上去掉区间 $l,r$ 的贡献，在第 $y$ 棵线段树上加上第 $x$ 棵线段树在区间 $l,r$ 上的贡献。其实可以使用线段树合并和分裂，从第 $x$ 棵线段树上去掉 $l,r$ 贡献使用分裂，而在第 $y$ 棵线段树上加上第 $x$ 棵线段树在 $l,r$ 上的贡献使用合并。

即使使用动态开点线段树仍然有可能 $\text{MLE}$，为了稳妥，实现时使用回收空间的动态开点线段树即可（

时间复杂度为 $O(m \log n+nm \log n)$，由于线段树合并的特殊性，其实并跑不满。

**Show the Code**

```cpp
#include<cstdio>
const int M=100;
int n,top=0,tot=0;
int a[200005],rt[105],rub[20000005],sum[20000005],sonL[20000005],sonR[20000005]; 
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int newnode() {return top? rub[top--]:++tot;}
inline void delnode(int &x) {sonL[x]=sonR[x]=sum[x]=0;rub[++top]=x;x=0;}
inline void pushup(int p) {sum[p]=sum[sonL[p]]+sum[sonR[p]];}
inline void change(int &p,int x,int l=1,int r=n) {
	if(!p) p=newnode();
	if(l==r) {sum[p]=1;return;}
	int mid=l+r>>1;
	if(x<=mid) change(sonL[p],x,l,mid);
	else change(sonR[p],x,mid+1,r);
	pushup(p);
}
inline void merge(int &x,int &y,int l=1,int r=n) {//将 y 合并到 x 上 
	if(!x||!y) {x+=y;return;}
	if(l==r) {sum[x]+=sum[y];delnode(y);}
	int mid=l+r>>1;
	merge(sonL[x],sonL[y],l,mid);
	merge(sonR[x],sonR[y],mid+1,r);
	delnode(y); pushup(x);
}
inline void split(int &x,int &y,int L,int R,int l=1,int r=n) {
	if(!y) return;
	if(L<=l&&r<=R) {x=y;y=0;return;}
	if(!x) x=newnode();
	int mid=l+r>>1;
	if(L<=mid) split(sonL[x],sonL[y],L,R,l,mid);
	if(R>mid) split(sonR[x],sonR[y],L,R,mid+1,r);
	pushup(x); pushup(y);
}
inline void dfs(int p,int clr,int l=1,int r=n) {
	if(l==r) {a[l]=(sum[p]? clr:a[l]); return;}
	int mid=l+r>>1;
	dfs(sonL[p],clr,l,mid); dfs(sonR[p],clr,mid+1,r);
}
int main() {
	n=read();
	for(register int i=1;i<=n;++i) {a[i]=read();change(rt[a[i]],i);}
	int Q=read();
	while(Q--) {
		int l=read(),r=read(),x=read(),y=read();
		if(x!=y) {int tmp=0; split(tmp,rt[x],l,r); merge(rt[y],tmp);}
	}
	for(register int i=1;i<=M;++i) dfs(rt[i],i);
	for(register int i=1;i<=n;++i) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：warzone (赞：8)

## 题目大意
给定序列 $a_1,a_2,\cdots,a_n$。  
要求支持将区间 $[l,r]$ 中等于 $p$ 的数变成 $p'$。  
$q$ 次操作后输出最终的序列。

$\texttt{Data Range: }1\le n,q\le 2\times 10^5,1\le a_i,p,p'\le 100$ 。

## 题解

看到是序列操作，自然想到 线段树/平衡树/分块，  
然后排除平衡树（没有结构性的序列操作）。  

但按照序列维护的一般思维而言，  
将等于 $x$ 的数变成 $y$ 这一操作似乎非常的棘手。

-------------------
事实上，这是个数学题。  
前置芝士：[oi-wiki 置换群](https://oi-wiki.org/math/permutation-group/#_5)

置换群的思想给予我们以很大的启发。  
具体地，我们维护的不再是系数序列 $a_1,a_2,\cdots,a_n$，  
而是映射序列 $f_1(x),f_2(x),\cdots,f_n(x)$。  
初始时，这些映射均为恒等置换 $\epsilon(x)=x$。支持以下操作：    
- 给定映射 $g(x)$，将 $[l,r]$ 中的映射 $f_k(x)$ 变为 $(f_k\circ g)(x)=g(f_k(x))$。  
- 给定 $a_k$，输出 $f_k(a_k)$。

在本题中，$g(x)=\begin{cases}x&(x\not= p)\\q&(x=p)\end{cases}$，只需要最后输出映射的值。

由于值域大小为 $|S|=100$，可以以置换的形式暴力维护 $f_k\circ g$。 
- 复合算子 $\circ$ 满足结合律，可以用 线段树+标记下传 的方法维护，  
  空间复杂度 $\Theta(n)$，时间复杂度 $\Theta(q|S|\log n+n\log n)$。  
- 直接用分块维护，空间复杂度 $\Theta(n+|S|\sqrt{n})$，  
  时间复杂度 $\Theta(q|S|\sqrt{n}+n)$。

## Code
这里采用的线段树维护的，只给出核心代码。

```cpp
typedef unsigned int word;
typedef unsigned char byte;
struct replace{//映射
	word next[100];
	inline replace(){}
	inline replace(const replace &p){
		memcpy(next,p.next,sizeof(next));}
	inline word& operator[](word id){return next[id];}
	inline void operator*=(const replace &p){//复合算子
		for(register word i=0;i<100;++i)
			next[i]=p.next[next[i]];}
}idnt;//恒等置换
struct READ{//快读
	char c;
	inline READ():c(getchar()){//初始化恒等置换
		for(register word i=0;i<100;++i) idnt[i]=i;}
	template<typename type>
	inline READ& operator >>(register type& num){
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
template<word size>
struct segment_tree{//线段树
	segment_tree<(size>>1)> l,r;
	replace rep;
	byte tag;
	inline segment_tree():rep(idnt){}
	inline void operator()(word f,word t,word x,word y){
		if(f==0&&t==(size<<1)-1){
			for(register word i=0;i<100;++i)
				if(rep[i]==x) rep[i]=y;
			return void(tag=1);
		}
		if(tag){
			l.rep*=rep,r.rep*=rep;
			rep=idnt,tag=0,l.tag=r.tag=1;
		}
		if(f&size) r(f&~size,t&~size,x,y);
		else if((t&size)^size) l(f,t,x,y);
		else l(f,size-1,x,y),r(0,t&~size,x,y);
	}//区间乘映射
	inline word operator()(word id,word x){//求映射值
		return rep[id&size? r(id&~size,x):l(id,x)];}
};
template<>
struct segment_tree<0>{//模板特化底层结点
	replace rep;
	byte tag;
	inline segment_tree():rep(idnt){}
	inline void operator()(word f,word t,word x,word y){
		for(register word i=0;i<100;++i)
			if(rep[i]==x) rep[i]=y;
	}
	inline word operator()(word id,word x){return rep[x];}
};
segment_tree<(1<<17)> tree;
```

---

## 作者：hater (赞：7)

看完题面 操作莫名熟悉 

之后我们点开 [这道题](https://www.luogu.com.cn/problem/P4119) 

诶 怎么修改操作一模一样啊 

之后我们把那道题的AC记录xjb改改就过了 

------------


~~好吧上面当我没说~~ 

我们考虑分块 用并查集维护每个数的值 

先想想整块怎么操作 

$rt_{i,j}$ 表示在第i个块中  最左边值为j的下标 

假如我们在第i个块中 把值x的数改为y 

如果值y在块中出现过

那么把$rt_{i,x}$的father设为$rt_{i,y}$ 

如果没有出现过 

就把$rt_{i,y}$赋值$rt_{i,x}$ 并且把$rt_{i,x}$的值设为y

操作后 显然块内没有值为x的数 需把$rt_{i,x}$赋值为0 

边角的时候 

把块中的每个数都更新 重新做一遍$rt$数组 

时间复杂度是熟悉的根号 而空间复杂度可以做到$O(n)$ 

边角暴力有个小优化 ： 

我们更新的只是值为x和y的数 可以只把这两个子树拉出来重构 详见代码 

```cpp
#include<bits/stdc++.h>  
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i )  
using namespace std ; 
const int N = 2e5+10 , B_P = 450 , V=105 ;    
int rt[B_P][V] , fa[N] , a[N] , n , blo ;   
int lef[B_P] , rig[B_P] , pos[N] , sta[B_P] ;  
int f( int x ) { return fa[x] == x ? x : fa[x] = f(fa[x]) ; } 
void prep( int p ) { 
  fp( i , lef[p] , rig[p] ) 
    if( !rt[p][a[i]] ) fa[i]=i , rt[p][a[i]]=i ; 
	else fa[i]=rt[p][a[i]] ;  
} 
void upd( int p , int lx , int rx , int x , int y ) {
  int l = lef[p] , r = rig[p] , top=0 ;
  rt[p][x] = rt[p][y] = 0 ; 
  fp( i , l , r ) { 
     a[i] = a[f(i)] ; 
     if( a[i] == x || a[i] == y ) sta[++top] = i ; 
  } 
  fp( i , lx , rx ) if( a[i] == x ) a[i] = y ; 
  fp( i , 1 , top ) fa[sta[i]] = sta[i] ; 
  fp( i , 1 , top ) 
    if( !rt[p][a[sta[i]]] ) rt[p][a[sta[i]]] = sta[i] ; 
    else fa[sta[i]] = rt[p][a[sta[i]]] ; 
} 
void modify( int l , int r , int x , int y ) { 
  if( x == y ) return ; 
  int lv = pos[l] , rv = pos[r] , tp , nw=0 ; 
  if( lv == rv ) { upd( lv , l , r , x , y ) ;  return ; } 
  upd( lv , l , rig[lv] , x , y ) ; 
  upd( rv , lef[rv] , r , x , y ) ; 
  fp( i , lv+1 , rv-1 ) { 
    if( !rt[i][x] ) continue ; 
    if( rt[i][y] ) fa[rt[i][x]] = rt[i][y] ; 
	else rt[i][y] = rt[i][x] , a[rt[i][x]] = y ; 
    rt[i][x] = 0 ; 
  } 
} 
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  int q , opt , l , r , x , y ; 
  cin >> n ;  
  blo = sqrt(n) ; 
  fp( i , 1 , n ) cin >> a[i] , fa[i]=i ;   
  fp( i , 1 , n ) pos[i] = (i-1)/blo+1 ; 
  fq( i , 1 , n ) lef[pos[i]] = i ; 
  fp( i , 1 , n ) rig[pos[i]] = i ; 
  fp( i , 1 , pos[n] ) prep( i ) ; 
  cin >> q ; 
  while( q -- ) {  
    cin >> l >> r >> x >> y ; 
    modify( l , r , x , y ) ; 
  } 
  fp( i , 1 , n ) a[i] = a[f(i)] , cout << a[i] << ' ' ;  
  cout << '\n' ; 
  return 0 ; 
} 
```


跑的很优秀 不需要任何卡常即可1.5s过题 



---

## 作者：_•́へ•́╬_ (赞：4)

## 思路

观察到值域很小，我们可以对每个值都开一个数据结构维护每个数是否是这个值。

这个数据结构，我使用了手写 `bitset`。

写法大概很像分块。修改时先暴力修改两边散的，再整块修改中间的。

时间复杂度 $\mathcal O(\frac{nq}{w})$。跑得飞快。

## [code](https://codeforces.com/contest/911/submission/195328369)

```cpp
#include<stdio.h>
#define B 6
#define L 63
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,q,a[200000];unsigned long long b[100][(200000>>B)+1];
main()
{
	read(n);for(int i=0;i<n;read(a[i]),--a[i],b[a[i]][i>>B]|=1ull<<(i&L),++i);
	read(q);
	for(int l,r,x,y;q--;)
	{
		read(l);read(r);read(x);read(y);--l;--r;--x;--y;
		if(x==y)continue;
		for(;l<=r&&(l&L);++l)if(b[x][l>>B]>>(l&L)&1)
			b[y][l>>B]|=1ull<<(l&L),b[x][l>>B]^=1ull<<(l&L);
		for(;l<=r&&(~r&L);--r)if(b[x][r>>B]>>(r&L)&1)
			b[y][r>>B]|=1ull<<(r&L),b[x][r>>B]^=1ull<<(r&L);
		if(l<r)for(int i=l>>B;i<=r>>B;++i)b[y][i]|=b[x][i],b[x][i]=0;
	}
	for(int i=0;i<100;++i)for(int j=0;j<n;++j)if(b[i][j>>B]>>(j&L)&1)
		a[j]=i;
	for(int i=0;i<n;printf("%d ",a[i++]+1));
}
```



---

## 作者：little_gift (赞：4)

noip前写个题解.

提供两种做法.

第一种是开一棵线段树, 每个节点上维护100个tag, 表示区间中的每个数分别变成了什么.

下传的时候奇怪地操作一下.

```cpp
_rep(i, 1, 100) tag[ls[h]][i] = tag[h][tag[ls[h]][i]]
```

~~应该没写错~~

修改的时候暴力for一遍所有标记把等于x的都改成y.

最后一次查询把所有标记都下传就好.

每个点大概1s多.

~~代码就不贴了~~

算了还是贴下.

写的指针……

```cpp
#include <cstdio>
#include <cctype>
#define _rep(i, a, b) for (register int i = a; i <= b; ++i)
#define read_int(x) void(scanf("%d", &x))
struct Node {
    int l, r, x, t[101];
    Node *c[2];
    Node(const int& l = 0, const int& r = 0) : l(l), r(r) {
        c[0] = c[1] = 0;
        x = 0;
        _rep(i, 1, 100) t[i] = i;
    }
    int mid() {return (l + r) >> 1;}
    void pd() {
        if (l == r) return;
        _rep(i, 1, 100) {
            c[0]->t[i] = t[c[0]->t[i]];
            c[1]->t[i] = t[c[1]->t[i]];
        }
        _rep(i, 1, 100) t[i] = i;
    }
} *root;
void build(Node* o) {
    if (o->l == o->r) return read_int(o->x);
    int mid = o->mid();
    build(o->c[0] = new Node(o->l, mid));
    build(o->c[1] = new Node(mid + 1, o->r));
}
void modify(Node* o, const int& l, const int& r, const int& x, const int& y) {
    if (l <= o->l && o->r <= r) {
        _rep(i, 1, 100) if (o->t[i] == x) o->t[i] = y;
        return;
    }
    o->pd();
    int mid = o->mid();
    if (l <= mid) modify(o->c[0], l, r, x, y);
    if (mid < r) modify(o->c[1], l, r, x, y);
}
void query(Node* o) {
    if (o->l == o->r) {
        if (o->mid() != 1) putchar(' ');
        printf("%d", o->t[o->x]);
        return;
    }
    o->pd(); query(o->c[0]); query(o->c[1]);
}
const int maxa = 100;
int n, q, l, r, x, y;
int main() {
    read_int(n); build(root = new Node(1, n));
    read_int(q);
    for (register int i = 0; i < q; ++i) {
        read_int(l); read_int(r); read_int(x); read_int(y);
        modify(root, l, r, x, y);
    }
    query(root); putchar('\n');
}
```

第二种做法跑的比较快.

首先对每个数字开一棵线段树, 记录每个位置是不是有这个数(0/1).

修改的时候就把一棵线段树的区间合并到另一棵上面.然后把它自己清空.

最后一次查询.

共计快了140s……

因为我写的指针所以细节比较多吧. 数组动开也比这个好看.

```cpp
#include <cstdio>
#include <cctype>
#define _rep(i, a, b) for (register int i = a; i <= b; ++i)
#ifndef xyxtql
const int ri_top = 1e7;
char ri[ri_top + 1], *rich = ri, *rr = ri;
//别问我为什么是rich了……
inline void rd() {*(rr = ri + fread(rich = ri, 1, ri_top, stdin)) = 0;}
inline char nch() {if (++rich >= rr) rd(); return *rich;}
inline void read_int(int& x) {
	while (!isdigit(*rich)) nch();
	for (x = *rich - '0'; isdigit(nch()); x = x * 10 + *rich - '0');
}
#else
#define read_int(x) void(scanf("%d", &x))
#endif
struct Node {
	int s;
	Node* c[2];
	Node();
} *root[101], *null;
Node::Node() {s = 0; c[0] = c[1] = null;}
void add(Node* &o, const int& l, const int& r, const int& x) {
	if (o == null) o = new Node(); //顺手动开了……
	++o->s;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (x <= mid) add(o->c[0], l, mid, x);
	else add(o->c[1], mid + 1, r, x);
} //建树
void merge(Node* &o, Node* &p) {
	if (p == null) return;
	if (o == null) return void((o = p, p = null));
	o->s += p->s;
	merge(o->c[0], p->c[0]);
	merge(o->c[1], p->c[1]);
	p = null; //注意清空
} //合并线段树(还是比较套路的?)
//修改操作
void modify(Node* &o, Node* &p, const int& l, const int& r, const int& L, const int& R) {
	if (p == null) return;
	if (o == null) o = new Node(); //注意开点
	if (L <= l && r <= R) {
		merge(o, p); //区间包含直接合并.
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid) modify(o->c[0], p->c[0], l, mid, L, R);
	if (mid < R) modify(o->c[1], p->c[1], mid + 1, r, L, R);
	o->s = o->c[0]->s + o->c[1]->s;
	p->s = p->c[0]->s + p->c[1]->s; //维护
}
int a[200001];
void query(Node* o, const int& l, const int& r, const int& x) {
	if (!o->s) return; //如果区间没有数直接return
	if (l == r) return void(a[l] = x); //最后一次修改直接覆盖到a数组
	int mid = (l + r) >> 1;
	query(o->c[0], l, mid, x);
	query(o->c[1], mid + 1, r, x);
}
int n, q, l, r, x, y;
int main() {
	null = new Node(); null->c[0] = null->c[1] = null; //因为在调用new Node()的时候null还不存在所以它的孩子事实上是没有被初始化的, 需要手动打一下
	_rep(i, 1, 100) root[i] = null; //初始化
	read_int(n);
	for (register int i = 1; i <= n; ++i) {
		int x; read_int(x); add(root[x], 1, n, i);
	}
	for (read_int(q); q--; ) {
		read_int(l); read_int(r); read_int(x); read_int(y);
		if (x != y) modify(root[y], root[x], 1, n, l, r);
	}
	_rep(i, 1, 100) query(root[i], 1, n, i);
	_rep(i, 1, n) printf("%d%c", a[i], "\n "[i != n]);
}
```

---

## 作者：Mophie (赞：3)

直接上分块。

其他部分比较简单，只要考虑怎么打标记和如何下放标记即可。

因为值域 $\le 100$，可以尝试状压。

设 $f_{i,j}$ 为在第 $i$ 块内，哪些数最后会被修改为 $j$。

然后若有一个从 $x$ 到 $y$ 的修改，易得 $f_{i,y} = f_{i,y} + f_{i,x},f_{i,x} = 0$。

接下来考虑怎么进行整块标记的下放。

考虑使用 lowbit 来解决。每次求出一个 $f_{i,x}$ 的最低位，然后在一个 $g_i = 2^i$ 的数组中二分求出此最低位对应的位置。

然后直接暴力下放标记即可。

时间复杂度 $O(q\sqrt{n}+q \times 100 \times \log{100})$，可以轻松通过本题。

注意特判修改时 $x=y$ 的情况，否则会 WA on test 114。

```cpp

/*
	『月正笑，地正润潮，星正舞，风正凉。』
*/

/*
	『长夜伴浪破晓梦，梦晓破浪伴夜长。』
*/

//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;
//#define int long long
inline int read()
{
	int sum = 0, nega = 1;
	char ch = getchar();
	while (ch > '9'||ch < '0')
	{
	    if (ch == '-') nega = -1;
		ch = getchar();
	}
	while (ch <= '9' && ch >= '0') sum = sum * 10 + ch - '0', ch = getchar();
	return sum * nega;
}
inline void write(int X)
{
	if(X < 0) {putchar('-'); X = -X;}
	if(X > 9) write(X / 10);
	putchar(X % 10 + '0');
}
const int N = 2e5 + 9, M = 109, BL = 509;
int n, q, a[N], B, tag[N], L[BL], R[BL], m;
__int128 fa[BL][M], pown[M];
int to[109];
inline __int128 lowbit(__int128 x) {return x & (-x);}
inline void Set(int id) 
{
	for (int i = 1; i <= m; i++) to[i] = 0;
	for (int i = 1; i <= m; i++) 
		while(fa[id][i]) 
		{
			__int128 t = lowbit(fa[id][i]); fa[id][i] ^= t;
			int pos = lower_bound(pown + 1, pown + m + 1, t) - pown;
			to[pos] = i;
		}
	for (int i = L[id]; i <= R[id]; i++) a[i] = to[a[i]];
	for (int i = 1; i <= m; i++) fa[id][i] = pown[i];
	return ;
}
inline void update(int l, int r, int x, int y) 
{
	if(tag[l] == tag[r]) 
	{
		Set(tag[l]);
		for (int i = l; i <= r; i++) 
			if(a[i] == x) a[i] = y;
		return ;
	}
	Set(tag[l]);
	for (int i = l; i <= R[tag[l]]; i++) 
		if(a[i] == x) a[i] = y;
	Set(tag[r]);
	for (int i = L[tag[r]]; i <= r; i++) 
		if(a[i] == x) a[i] = y;
	for (int i = tag[l] + 1; i < tag[r]; i++) 
	{
		if(x != y) fa[i][y] |= fa[i][x], fa[i][x] = 0;
	}
	return ;
}
signed main()
{
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read(); m = 100;
	pown[0] = 1;
	for (int i = 1; i <= m; i++) pown[i] = (pown[i - 1] << 1);
	B = sqrt(n); 
	for (int i = 1; i <= n; i++) tag[i] = (i - 1) / B + 1;
	for (int i = 1; i <= tag[n]; i++)
		for (int j = 1; j <= m; j++)
			fa[i][j] = pown[j];
	for (int l = 1, r; l <= n; l = r + 1) 
	{
		r = min(n, l + B - 1); 
		L[tag[l]] = l; R[tag[r]] = r;
	//	cout << l << " " << r << endl;
		if(r == n) break;
	}
	q = read();
	for (int i = 1; i <= q; i++) 
	{
		int l = read(), r = read(), x = read(), y = read();
		update(l, r, x, y);
	//	for (int j = 1; j <= n; j++) cout << a[j] << " "; cout << endl;
	}
	for (int i = 1; i <= tag[n]; i++) Set(i);
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);
	return 0;
}

```


---

## 作者：DPair (赞：3)

大家好，我非常喜欢暴力数据结构，所以我用裸的分块过了这道题。

其实完全用不上另一篇分块题解所说的vector还有启发式合并什么的。

（~~但应该是能卡掉的~~）

## 【思路】
用分块的话思路异常简单而暴力。

首先分块是什么应该不用多说。

然后我们发现值域只有 $100$ 。

那么我们对于每一个块打 $100$ 个标记，表示 **当前块中值为 x 的数变成了什么数** 。

考虑维护。

对于散块，暴力重构以清除标记，此时块内所有值都为真实值，然后暴力扫描+赋值即可。

对于整块，我们需要维护这 $100$ 个标记，直接暴力扫描块中等于 $x$ 的 **标记** ，然后把这些标记的值赋为 $y$ 。

最后输出前每一个块暴力重构一遍以获取真实值，就可以输出了。

然后传统艺能块长设一个 $\sqrt{n}$ （~~这里注意了，要考的！~~），代码交上去，$\text{TLE on test113}$ 。 $\text{Oh no!}$ 我们的算法被卡了！

然后我突然意识到块长不应该设 $\sqrt{n}$ 。

我们来分析一下每一个操作的复杂度。

我们设块长为 $b$，值域为 $x$ 。

暴力重构一个块，要扫描块长+值域，是$O(b+x)$ 的。

处理整块，总共要处理 $\frac{n}{b}$ 个块，每一个块 $O(x)$ ，总共是 $O(\frac{nx}{b})$ 的。

我们意识到块长不应该取 $\sqrt{n}$ ，而应该取 $\sqrt{nx}$ 才能做到复杂度正确。

然而实测块长开 $2000$ 左右跑得更快。。。

## 【代码】

```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
inline char next_char(){
    char ch = getchar();
    while(ch == 9 || ch == 10 || ch == 32) ch = getchar();
    return ch;
}
#define MAXN 200005
#define block 2000
#define B MAXN / block + 5
int n, m;
int a[MAXN];
int bel[MAXN], fst[B], lst[B], fa[B][105];

inline void rebuild(int x){
    for (register int i = fst[x];i <= lst[x];i ++) a[i] = fa[x][a[i]];
    for (register int i = 1;i <= 100;i ++) fa[x][i] = i;
}

int main(){
    read(n);
    for (register int i = 1;i <= n;i ++) read(a[i]);
    for (register int i = 1;i <= n;i ++){
        bel[i] = (i - 1) / block + 1;
        if(!fst[bel[i]]) fst[bel[i]] = i;
        lst[bel[i]] = i;
    }
    for (register int i = 1;i <= bel[n];i ++)
        for (register int j = 1;j <= 100;j ++)
            fa[i][j] = j;
    read(m);
    while(m --){
        int l, r, x, y;
        read(l);read(r);read(x);read(y);
        int L = bel[l], R = bel[r];
        if(L == R){
            rebuild(L);
            for (register int i = l;i <= r;i ++) if(a[i] == x) a[i] = y;
        }
        else{
            rebuild(L);rebuild(R);
            for (register int i = l;i <= lst[L];i ++) if(a[i] == x) a[i] = y;
            for (register int i = fst[R];i <= r;i ++) if(a[i] == x) a[i] = y;
            for (register int i = L + 1;i < R;i ++){
                for (register int j = 1;j <= 100;j ++){
                    if(fa[i][j] == x) fa[i][j] = y;
                }
            }
        }
    }
    for (register int i = 1;i <= bel[n];i ++) rebuild(i);
    for (register int i = 1;i <= n;i ++) fprint(a[i], 32);
    putchar(10);
}
```

---

## 作者：良月澪二 (赞：3)

打过这一场

$But$ $G$看都没看就玩去了

线段树里面维护每个节点对应的区间里面，每个数将会变成哪个数

初始时$tag[i]=i$

下传标记时当前节点的$tag$等于父亲节点的$tag$

修改时枚举修改

递归输出
```cpp
/**
 * @Date:   2019-03-10T16:39:52+08:00
 * @Last modified time: 2019-03-10T16:39:53+08:00
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#define A 1000010
#define B 2010

using namespace std;
typedef long long ll;
struct node {
    int l, r, w, tag[101];
}tree[A];
int n, q, a, b, x, y;
void build(int k, int l, int r) {
    tree[k].l = l; tree[k].r = r;
    for (int i = 1; i <= 100; i++) tree[k].tag[i] = i;
    if (l == r) {
        scanf("%d", &tree[k].w);
        return;
    }
    int m = (l + r) >> 1;
    build(k << 1, l, m);
    build(k << 1 | 1, m + 1, r);
}
void down(int k) {
    if (tree[k].l == tree[k].r) return;
    for (int i = 1; i <= 100; i++)
        tree[k << 1].tag[i] = tree[k].tag[tree[k << 1].tag[i]],
        tree[k << 1 | 1].tag[i] = tree[k].tag[tree[k << 1 | 1].tag[i]];
    for (int i = 1; i <= 100; i++) tree[k].tag[i] = i;
}
void change(int k) {
    if (tree[k].l >= a and tree[k].r <= b) {
        for (int i = 1; i <= 100; i++)
            if (tree[k].tag[i] == x)
                tree[k].tag[i] = y;
        return;
    }
    down(k);
    int m = (tree[k].l + tree[k].r) >> 1;
    if (a <= m) change(k << 1);
    if (b > m) change(k << 1 | 1);
}
void output(int k) {
    if (tree[k].l == tree[k].r) {
        int m = (tree[k].l + tree[k].r) >> 1;
        cout << tree[k].tag[tree[k].w] << " ";
        return;
    }
    down(k); output(k << 1); output(k << 1 | 1);
}

int main(int argc, char const *argv[]) {
	cin >> n;
    build(1, 1, n);
    cin >> q;
    while (q--) {
        cin >> a >> b >> x >> y;
        change(1);
    }
    output(1);
    return 0;
}

```

---

## 作者：LJ07 (赞：3)

## 题目描述
 
[题目传送门](https://www.luogu.com.cn/problem/CF911G)

## 思路简述

简单题。观察到 $a$ 的值域很小，考虑对每个值维护一个存对应下标的平衡树。

每次操作就相当于将第 $x$ 棵平衡树值在 $l$ 到 $r$ 的节点分裂出来，再合并到第 $y$ 课平衡树中。由于要合并的两棵平衡树值域不存在严格大于等于这种关系，所以使用启发式合并。

这里写的是 FHQ treap（为什么题解区没人写平衡树合并 qwq，感觉平衡树比线段树更简单更好写一点啊）。

启发式合并实现的好好像是跟线段树合并一个复杂度的。

空间复杂度仅是 $O(n)$。写平衡树的好处就是好写并且空间小，在本题不加任何优化跑得比大多数线段树做法快。~~快来写 FHQ treap 啊。~~

## 丑陋の代码

```cpp
#include <bits/stdc++.h>
#define GC c=getchar()
#define IG isdigit(c)
#define rep(i,l,r) for(int i(l),_##i(r);i<=_##i;++i)
#define per(i,r,l) for(int i(r),_##i(l);i>=_##i;--i)
const int SZ(1<<23);
unsigned char buf[SZ],*s,*t;
#define getchar() (s==t&&(t=buf+fread(s=buf,1,SZ,stdin)),s==t?EOF:*s++)
template<class T=int>T frd(T x=0,char GC,bool f=1)
{
	for(;!IG;GC)f=c!='-';for(;IG;GC)x=x*10+(c^48);return f?x:-x;
}
using namespace std;
const int V(100),N(2e5+5);
int n,q,root[V+5],a[N+5];
mt19937 rnd(114514);
struct node {int ls,rs,rk; node() {ls=rs=0,rk=rnd();} }nd[N+5];
void split(int &x,int &y,int rt,int k)
{
	if(!rt) return (void)(x=y=0);
	if(rt<=k) x=rt,split(nd[x].rs,y,nd[x].rs,k);
	else y=rt,split(x,nd[y].ls,nd[y].ls,k);
}
int merge(int x,int y)
{
	if(!x||!y) return x+y; if(nd[x].rk>nd[y].rk) swap(x,y); int t1,t2;
	split(t1,t2,y,x),nd[x].ls=merge(nd[x].ls,t1),nd[x].rs=merge(nd[x].rs,t2);
	return x;
}
void put(int rt,int val)
{
	if(rt) a[rt]=val,put(nd[rt].ls,val),put(nd[rt].rs,val);
}
signed main()
{
	n=frd();
	rep(i,1,n) {int a(frd());root[a]=merge(root[a],i);}
	rep(q,1,frd())
	{
		int l(frd()),r(frd()),x(frd()),y(frd()),t1,t2,t3; 
		split(t1,t2,root[x],l-1),split(t2,t3,t2,r);
		root[x]=merge(t1,t3),root[y]=merge(root[y],t2);
	}
	rep(i,1,100) put(root[i],i);
	rep(i,1,n) printf("%d ",a[i]);
	return 0;
}
```

~~在我调完代码准备交的时候一不小心把局部的 $t1,t2,t3$ 手残开到全局了，浪费了 0.5h（哭死）。~~

---

## 作者：ExplodingKonjac (赞：2)

### [原题链接](https://www.luogu.com.cn/problem/CF911G)

## 解题思路

发现值域仅有 $[1,100]$，于是我们就可以考虑给每一个值开一颗线段树，线段树的节点记录该数在某个位置存不存在。

（嗯，所以每个节点除了左右儿子编号什么都不用记录）

当我们要将 $[l,r]$ 中的 $x$ 改为 $y$ 的时候，假设 $x,y$ 对应的线段树为 $t_x,t_y$，首先将 $t_x$ 中 $[l,r]$ 的部分分裂出来，然后把它合并到 $t_y$ 上。

输出的时候就对于某一个位置找一找有哪个数字在这个位置存在就行了。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,a[200005];
set<int> num;
struct TreeNode
{
    TreeNode *lc,*rc;
    TreeNode()
        { lc=rc=nullptr; }
}*rt[105],*zt;
typedef TreeNode *pNode;
void insert(int p,pNode &i,int l=1,int r=n)
{
    if(!i)  i=new TreeNode;
    if(l!=r)
    {
        int mid=(l+r)>>1;
        if(mid>=p)  insert(p,i->lc,l,mid);
        else    insert(p,i->rc,mid+1,r);
    }
}
void merge(pNode &dst,pNode &src)
{
    if(!src)    return;
    if(!dst)    return dst=src,src=nullptr,void();
    merge(dst->lc,src->lc);
    merge(dst->rc,src->rc);
    delete src;src=nullptr;
}
void split(int lq,int rq,pNode &dst,pNode &src,int l=1,int r=n)
{
    if(!src)	return;
    if(l>=lq && r<=rq)
        dst=src,src=nullptr;
    else
    {
        if(!dst)    dst=new TreeNode;
        int mid=(l+r)>>1;
        if(mid>=lq) split(lq,rq,dst->lc,src->lc,l,mid);
        if(mid<rq)  split(lq,rq,dst->rc,src->rc,mid+1,r);
    }
}
bool exist(int p,pNode &i,int l=1,int r=n)
{
    if(!i)  return false;
    if(l==r)    return true;
    int mid=(l+r)>>1;
    return (mid>=p)?exist(p,i->lc,l,mid):exist(p,i->rc,mid+1,r);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),insert(i,rt[a[i]]),num.insert(a[i]);
    scanf("%d",&q);
    while(q--)
    {
        int l,r,x,y;
        scanf("%d%d%d%d",&l,&r,&x,&y);
        if(x==y)    continue;
        num.insert(y);
        split(l,r,zt,rt[x]);
        merge(rt[y],zt);
    }
    for(int i=1;i<=n;i++)
    {
        int ai=0;
        for(int j: num)
            if(exist(i,rt[j]))
                { ai=j;break; }
        printf("%d ",ai);
    }
    return 0;
}
```

## 后记

线段树分裂合并真是个神奇的东西，本题127个测试点，有的大佬只用跑14s，而我这个菜鸡55s起步。。qwq

附录，为指针党宣传：
![指针好](https://cdn.luogu.com.cn/upload/image_hosting/c65wperd.png)

---

## 作者：逆流之时 (赞：2)

老师讲这道题时用的是线段树。一段时间后我从零开始做这道题时，想了 1h 多线段树的 `push_down()` 函数怎么写才能去掉 100 这个常数，然后才发现这题可以直接分块碾过去。自己很喜欢的数据结构竟然没有第一时间想到。

这题使用分块思路还是很简单的。

由于不能暴力修改，而普通的数组或者并查集又不能维护数与数之间的映射关系。所以我们为了使用延迟标记维护数的映射关系，需要考虑更加暴力的延迟标记维护方法：vector 启发式合并。

然后因为这个东西放到线段树上维护会常数巨大且非常难维护，所以我们考虑分块。

设最大值为 $size$，分块大小为 $maxn$，先对于每一块开 100 个 vector，然后使用两个函数：
- `merge()` 即对于修改 `l r x y` 按秩合并同一块中的 `x, y` 对应的两个 vector，时间复杂度均摊 $O(\log size)$，且常数较小，一般跑不满。
- `assign()` 即对于一整块，把 vector 维护的数的映射关系下传到单个数上，然后把 vector 恢复原状，时间复杂度 $O(maxn + size)$。初始时 vector 中 $v_{i, j} = \{j\}$。总的时间复杂度为每次修改 $\log size \frac{n}{maxn} + maxn + size$，最终对每一块 `assign()` 一遍的时间复杂度为 $O(n + \frac{n}{maxn} \times size)$。

由于分块常数小，虽然这题使用分块的时间复杂度很大，为 $O(n \sqrt n \log n)$，但实际上使用分块碾过去毫无压力，$maxn = \sqrt n$ 时用了 2.11min，最慢的一个点 1825ms，还算正常；而使用最优分块大小 $maxn = \sqrt {n \log size} + 1$ 时只用 1.58min，最慢的点 935ms。总用时大约是一般线段树用时的 3 倍。

如果实在要将这种方法卡到时间复杂度上界，可以考虑对这种方法进行更详细的时间复杂度势能分析，以找到构造数据的方法：

设一开始所有块都处于初态；

- `merge()`：每一轮修改中，可以对一块消耗 $O(\log size)$ 的时间复杂度。如果对初态下的同一块使用了 `size` 次 `merge()`，则该块到达终态，不能再消耗时间复杂度（不过遍历到这一块的时间复杂度仍为 $O(1)$）。每一轮可以对任意块使用 `merge()`（实际为连续的若干块，不过这里可以不考虑）。
- `assign()`：每一轮修改中，可以使一块恢复到初态。每一轮可以对最多 2 块使用 `assign()`。

所以如果要卡这种方法，可以设计这样的数据：先不断对区间 $1 n$ 执行可以将按秩合并卡到 $O(\log n)$ 的合并操作，然后再对区间 $[maxn * k + 1, maxn * k + 2 * maxn]$ 执行修改，这样就可以使用 $\frac{n}{2 \times maxn}$ 次操作使其恢复终态。

当然，以上的数据构造方法不能在实际情况下保证卡掉分块。因为分块 3s 跑 $n = 200000$ 的数据一般是可以过的，并且分块可以微调块大小，或者直接使块大小根据随机数波动，使别人根本没法卡。

这题里很多地方需要考虑 `(i + 1) * maxn <= n` 这样的边界情况，我还因此 Wa on 114 了几次。同时 CF 的 hack 机制非常毒瘤，导致 $n = 1, maxn = \sqrt {n \log n}$ 时会 RE，需要将 $maxn$ 改为 $maxn = \sqrt {n \log n} + 1$（不过设为 $maxn = \sqrt {n \log size} + 1$ 时不用考虑）。

```cpp
#include<cstdio>
#include<cmath>
#include<vector>
int n, q, maxn;
int a[200005];
std::vector<int> v[1900][105];
inline void merge(std::vector<int> &v1, std::vector<int> &v2) {
	if (v1.size() < v2.size()) std::swap(v1, v2);
	v1.insert(v1.end(), v2.begin(), v2.end());
	v2.clear();
}
inline void assign(int i, int x, int y, int l, int r) {
	static int vis[105] = {};
	if ((i + 1) * maxn <= n) {
		for (int j = 1; j <= 100; j++) {
			for (int k : v[i][j]) vis[k] = j;
			v[i][j].clear();
			v[i][j].push_back(j);
		}
		for (int j = i * maxn; j < (i + 1) * maxn; j++) a[j] = vis[a[j]];
	}
	for (int j = l; j < r; j++)
		if (a[j] == x) a[j] = y;
}
int main() {
	scanf("%d", &n);
	maxn = sqrt(n * log2(n)) + 1;
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; (i + 1) * maxn <= n; i++)
		for (int j = 1; j <= 100; j++) v[i][j].push_back(j);
	for (scanf("%d", &q); q--;) {
		int l, r, x, y, L, R;
		scanf("%d%d%d%d", &l, &r, &x, &y);
		if (x != y) {
			l--;
			L = l / maxn, R = r / maxn;
			if (L != R) {
				assign(L, x, y, l, (L + 1) * maxn);
				for (int i = L + 1; i < R; i++) merge(v[i][y], v[i][x]);
				assign(R, x, y, R * maxn, r);
			} else assign(L, x, y, l, r);
		}
	}
	for (int i = 0; (i + 1) * maxn <= n; i++) assign(i, 0, 0, 0, 0);
	for (int i = 0; i < n; i++) printf("%d ", a[i]);
}
```


---

## 作者：JWRuixi (赞：1)

~~竟然没有人用分块！！~~

- 题意

给定长度为 $n$ 的序列 $a$，$m$ 此操作：

```l r x y``` 将区间 $[l,r]$ 内等于 $x$ 的数赋值为 $y$。

输出操作后的序列。

- 分析

不知道在场的朋友们有没有做过最初分块的，如果有的话，拿着题应该是随手切了，~~由于我太菜调了好久~~。

我们才用暴力的分块思想，暴力重构边角块，中间块可以分三类：

1. 不存在 $x$，直接跳过。
2. 存在 $x$，不存在 $y$，将 $x$ 映射到 $y$，感觉好像是最初分块的重点，考虑用 $pos_x$ 表示目前真实值为 $x$ 的数对应的位置，每次操作时，将 $val_{pos_x} \leftarrow y,pos_y \leftarrow pos_x$，这样就保证了操作的正确性，下次修改 $y$ 为 $z$ 时就能访问到正确的数了！
3. 都存在，直接暴力合并，考虑每次暴力合并后块内的颜色数量减少 $1$，所以这样的操作最多 $\min(\omega,\sqrt n)\sqrt n$，所以总时间复杂度是 $O(\min(\omega,\sqrt n)n)$，可以接受。

好了，就这样了，简不简单？

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(2e5 + 500), maxk(450);
int n, m, sqn, len, id[maxn], a[maxn], ls[maxk], rs[maxk], cnt[maxk][105];

struct DSU {
	int now, pos[105], val[105];
	void init () {
		for (int i = 1; i <= 100; i++) pos[i] = val[i] = i, cnt[now][i] = 0;
		for (int i = ls[now]; i <= rs[now]; i++) cnt[now][a[i]]++;
	}
	void mdy (int x, int y) {
		val[pos[x]] = y;
		pos[y] = pos[x];
		pos[x] = 0;
	}
	inline int operator [] (const int &rhs) {
		return val[rhs];
	}
} b[maxk];

void mdy (int l, int r, int x, int y) {
	int now = id[r];
	for (int i = ls[now]; i <= rs[now]; i++) a[i] = b[now][a[i]];
	for (int i = l; i <= r; i++) if (a[i] == x) a[i] = y;
	b[now].init();
}

int main () {
	n = read(), sqn = sqrt(n);
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) id[i] = (i - 1) / sqn + 1; len = id[n];
	for (int i = 1; i <= len; i++) ls[i] = rs[i - 1] + 1, rs[i] = i * sqn, b[i].now = i, b[i].init(); rs[len] = n;
	m = read();
	while (m--) {
		int l = read(), r = read(), x = read(), y = read(), ll = id[l], rr = id[r];
		if (x == y) continue;
		if (ll == rr) {
			if (cnt[ll][x]) mdy(l, r, x, y);
			continue;
		}
		if (cnt[ll][x]) mdy(l, rs[ll], x, y);
		if (cnt[rr][x]) mdy(ls[rr], r, x, y);
		for (int i = ll + 1; i < rr; i++) {
			if (!cnt[i][x]) continue;
			if (cnt[i][y]) mdy(ls[i], rs[i], x, y);
			else b[i].mdy(x, y);
			cnt[i][y] += cnt[i][x], cnt[i][x] = 0; 
		}
	}
	for (int i = 1; i <= n; i++) a[i] = b[id[i]][a[i]];
	for (int i = 1; i <= n; i++) write(a[i]), putchar(' ');
}
```

---

## 作者：__stick (赞：1)

## 题意

给出 $n $ 个数，每个数值域 $[1,100]$。支持以下操作，将 $[l,r] $ 中等于 $x$ 的数变成 $y$。输出答案数组。

## 思路

这个题值域很小，肯定是个突破口。

一个想法是对线段树每个节点维护一个 tag 数组，表示当前区间为 $i$ 的值变成了多少，这样复杂度是 $100n\log n$ 的，不是很行（但是可以过，但是这样说的话这道题纯暴力也能过，而且比这么搞还快）。

考虑换个思路，对每个值维护一个线段树，权值是 $0/1$ 表示当前位置有没有数，但是修改不好解决。

我们在可接受复杂度内能做的就是找到两颗线段上修改区间对应的节点，但是将 $x$ 全部变成 $y$ 也就是要清空 $x$ 线段树上对应区间，将这些区间转移到线段树 $ y$  上，听着就很像线段树合并的操作，所以考虑对这些节点使用线段树合并，比如这玩意（网上随便扒的）：

![](https://pic1.zhimg.com/80/v2-08d7cb06efc8a445b26e3a22d7ddcf04_720w.webp)

被标记的几个节点就是本次操作涉及到的区间，则我们要做的就是把 $x$ 对应线段树上的所有节点合并到 $y$ 上，然后这里直接线段树合并就行了，代码如下（这里用节点的有无代表是否有这个数）

```c++
void merge(int& u,int& v)
{
	if(!u||!v)return u+=v,v=0,void();
	merge(t[u].l,t[v].l);
	merge(t[u].r,t[v].r);
	s[++top]=v;v=0;
}
void update(int& x,int &y,int l,int r,int ql,int qr)//split x to y
{
	if(!x)return;
	if(ql<=l&&r<=qr)
	{
		merge(y,x);
		return;
	}
	int mid=(l+r)>>1;
	if(!y)y=newnode(),t[y].l=t[y].r=0;// y 的结构必须完整，否则会合并到 0 上
	if(ql<=mid)update(t[x].l,t[y].l,l,mid,ql,qr);
	if(qr>mid)update(t[x].r,t[y].r,mid+1,r,ql,qr);
}
```
这里没有像其他题解一样新开一个节点链接要修改的节点，而是直接在找出区间的时候调用 merge 函数，这样跑的更快。

这里补个复杂度证明：

复杂度看起来不科学，但是观察 merge 函数，我们每次 merge 函数的调用一定会删除一个节点，然后线段树最多产生 $O((n+m)\log n)$ 个节点，所以我们消耗在 merge 函数上的复杂度不会超过 $O((n+m)\log n)$（每次 merge 的调用是 $O(1)$ 的）。

而其他部分的复杂度显然不会超过 $O((n+m)\log n)$， 所以复杂度就是 $O((n+m)\log m)$。

输出就遍历所有出现过权值的线段树即可。
## 思路2
提供一种不一样的分块方式，复杂度严格 $O(n\sqrt{n})$。

对于每个块维护一个 list 数组表示当前块中权值为 $i$ 的数的出现位置。

这里修改的时候，对于散块将 $x$ 的 list 中所有下标在 $[l,r]$ 之间的加入 $y$，整块将 $x$ 的 list 直接加入 $y$ 的 list 中，由于 list 的特殊性，前一个操作是 $O(\sqrt{n}) $  的，因为一个块的 list 最多 $O(\sqrt{n})$ 个数，而插入是 $O(1) $ 的，对于第二个操作，list 直接加复杂度是 $O(1)  $ 的，所以总复杂度是 $O(n\sqrt{n})$ 的。

但是这玩意由于 list 寻址不连续，常数堪称巨大，比纯暴力还慢（这题纯暴力可过），考场上算复杂度一定记得算上 list 的常数。

## code

线段树合并主体代码已经上了，然后其他部分可以看其他题解，这里将 list 分块做法上上来。
```cpp
const int MAXN=2e5+10;
const int B=400;
inline int get(int x){return (x-1)/B+1;}
inline int L(int x){return (x-1)*B+1;}
inline int R(int x){return x*B;}
list<int> a[MAXN/B+20][110];
int ans[MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;cin>>n;
	int x;
	for(int i=1;i<=n;i++)
	{
		int x;cin>>x;
		a[get(i)][x].push_back(i);
	}
	int T;cin>>T;
	auto update=[&](list<int>& a,list<int>& b,int l,int r)
	{
		auto ii=a.begin();
		while(ii!=a.end())
		{
			auto nxt=next(ii);
			if(l<=*ii&&*ii<=r) b.splice(b.begin(),a,ii);
			ii=nxt;
		}
	};
	while(T--)
	{
		int l,r,x,y;cin>>l>>r>>x>>y;
		if(x==y)continue;
		int p=get(l),q=get(r);
		update(a[p][x],a[p][y],l,r),update(a[q][x],a[q][y],l,r);
		for(int i=p+1;i<q;i++) a[i][y].splice(a[i][y].begin(),move(a[i][x]));
	}
	for(int i=1;i<=get(n);i++)
	{
		for(int j=1;j<=100;j++)
			for(auto& p:a[i][j])ans[p]=j;
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	return 0;
}
```



---

## 作者：小木虫 (赞：0)

### Problem  
给你一个长度为 $n$ 的序列 $a$，每次执行一个操作，使得一个区间内为 $x$ 的数都变成 $y$。  
问你这个序列最后会变成什么。  

### Solution  
你首先发现，你可以对每个权值建一个线段树，然后区域变值的操作就是把一颗线段树的若干子树（代表这个区间）移植（合并）到另外一颗线段树上。  

然后我们发现些线段树的节点个数是 $O(n \log n)$，所以合并的复杂度是正确的。  

然后我们依次合并线段树，这个题就做完了。  

code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,a[N],b[N],L,R,x,y,root[110],cnt,l[N*80],r[N*80],tree[N*80];
void update(int &rt,int left,int right,int x){
	if(!rt)rt=++cnt;
	if(left==right){tree[rt]++;return;}
	int mid=(left+right)/2;
	if(x<=mid)update(l[rt],left,mid,x);
	else update(r[rt],mid+1,right,x);
}
int merge(int rt1,int rt2,int left,int right){
	if(!rt1)return rt2;if(!rt2)return rt1;
	tree[rt1]+=tree[rt2];tree[rt2]=0;
	if(left==right)return rt1;
	int mid=(left+right)/2;
	l[rt1]=merge(l[rt1],l[rt2],left,mid);
	r[rt1]=merge(r[rt1],r[rt2],mid+1,right);
	l[rt2]=r[rt2]=0;return rt1;
}
void query(int &rt1,int &rt2,int left,int right,int L,int R){
	if(!rt2)rt2=++cnt;
	if(left>=L&&right<=R){
		rt2=merge(rt2,rt1,left,right);rt1=0;
		return;
	}int mid=(left+right)/2;
	if(L<=mid)query(l[rt1],l[rt2],left,mid,L,R);
	if(mid+1<=R)query(r[rt1],r[rt2],mid+1,right,L,R);
}
void dfs(int rt,int left,int right,int x){
	if(!rt)return;
	if(left==right&&tree[rt]==0)return;
	if(left==right){b[left]=x;return;}
	int mid=(left+right)/2;
	dfs(l[rt],left,mid,x);
	dfs(r[rt],mid+1,right,x);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],update(root[a[i]],1,n,i);
	cin>>m;
	while(m--){
		cin>>L>>R>>x>>y;
		if(x==y)continue;
		query(root[x],root[y],1,n,L,R);
	}
	for(int i=1;i<=100;i++)
		dfs(root[i],1,n,i);
	for(int i=1;i<=n;i++)
		cout<<b[i]<<" ";
	return 0;
}
```


---

## 作者：king_xbz (赞：0)

这是一道区间内部分点修改，最终状态查询的题目，是一道不错的数据结构题目。

所以我们考虑用分块来艹，虽然动态开点线段树好像更能跑一点，但是毕竟我太菜了 不会写。

这道题的数据范围是$2e5$，分块根号复杂度应该还是可以艹过去的。

由于数据的值域只有$100$，所以我们可以考虑在每个节点维护一个大小为$100$的桶即可，然后记录这个点的变化情况。

我们考虑使用分块，暴力修改，用一个大小为$n×100$的$mp$桶数组标记$1\to 100$每个数的映射情况作为懒标记，在每次修改的时候下传标记，然后最后把标记全部下传，输出最后的$a$数组即可

代码：

```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 1001
#define N 500001
using namespace std;
struct node
{
	int siz;
	int tot;
}
block;
int a[N],L[N],R[N],mp[N][105],bel[N],n,vis[N];
inline int read();
void pushdown(int x);
inline void build(int l,int r,int now);
void modify(int l,int r,int x,int y);
int main()
{
	n=read();
	for(fint i=1;i<=n;i++)
	a[i]=read();
	block.siz=2000;//听说这样跑的快
	block.tot=n/block.siz;
	if(n%block.siz)
	block.tot++;
	for(fint i=1;i<=n;i++)
	bel[i]=(i-1)/block.siz+1;
	build(1,block.siz,1);
	for(fint i=1;i<=block.tot;i++)
	for(fint j=1;j<=100;j++)
	mp[i][j]=j;
	int m;
	m=read();
	for(fint i=1;i<=m;i++)
	{
		int ll,rr,x,y;
		ll=read(),rr=read(),x=read(),y=read();
		modify(ll,rr,x,y);
	}
	for(fint i=1;i<=n;i++)
	if(!vis[bel[i]])
	pushdown(i),vis[bel[i]]=1;
	for(fint i=1;i<=n;i++)
	cout<<a[i]<<" ";
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

void build(int l,int r,int now)
{
	if(now==block.tot)
	{
		L[now]=l,R[now]=n;
		return ;
	}
	L[now]=l,R[now]=r;
	build(r+1,r+block.siz,now+1);
	return ;
}

void modify(int l,int r,int x,int y)
{
	if(bel[l]==bel[r])
	{
		pushdown(l);
		for(fint i=l;i<=r;i++)
		if(a[i]==x)
		a[i]=y;
		return ;
	}
	pushdown(l),pushdown(r);
	for(fint i=l;i<=R[bel[l]];i++)
	if(a[i]==x)
	a[i]=y;
	for(fint i=L[bel[r]];i<=r;i++)
	if(a[i]==x)
	a[i]=y;
	for(fint i=bel[l]+1;i<=bel[r]-1;i++)
	for(fint j=1;j<=100;j++)
	if(mp[i][j]==x)
	mp[i][j]=y;
	return ;
}

inline void pushdown(int x)
{
	for(fint i=L[bel[x]];i<=R[bel[x]];i++)
	a[i]=mp[bel[x]][a[i]];
	for(fint i=1;i<=100;i++)
	mp[bel[x]][i]=i;
	return ;
}

---

