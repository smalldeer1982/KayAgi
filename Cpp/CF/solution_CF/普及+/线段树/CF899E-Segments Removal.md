# Segments Removal

## 题目描述

Vasya has an array of integers of length $ n $ .

Vasya performs the following operations on the array: on each step he finds the longest segment of consecutive equal integers (the leftmost, if there are several such segments) and removes it. For example, if Vasya's array is $ [13,13,7,7,7,2,2,2] $ , then after one operation it becomes $ [13,13,2,2,2] $ .

Compute the number of operations Vasya should make until the array becomes empty, i.e. Vasya removes all elements from it.

## 说明/提示

In the first example, at first Vasya removes two fives at the second and third positions. The array becomes $ [2,2] $ . In the second operation Vasya removes two twos at the first and second positions. After that the array becomes empty.

In the second example Vasya has to perform five operations to make the array empty. In each of them he removes the first element from the array.

In the third example Vasya needs three operations. In the first operation he removes all integers $ 4 $ , in the second — all integers $ 100 $ , in the third — all integers $ 2 $ .

In the fourth example in the first operation Vasya removes the first two integers $ 10 $ . After that the array becomes $ [50,10,50,50] $ . Then in the second operation Vasya removes the two rightmost integers $ 50 $ , so that the array becomes $ [50,10] $ . In the third operation he removes the remaining $ 50 $ , and the array becomes $ [10] $ after that. In the last, fourth operation he removes the only remaining $ 10 $ . The array is empty after that.

## 样例 #1

### 输入

```
4
2 5 5 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
6 3 4 1 5
```

### 输出

```
5
```

## 样例 #3

### 输入

```
8
4 4 4 2 2 100 100 100
```

### 输出

```
3
```

## 样例 #4

### 输入

```
6
10 10 50 10 50 50
```

### 输出

```
4
```

# 题解

## 作者：emptysetvvvv (赞：9)

## 双向链表 堆

### 背景 

神犇们都道是 $\mathtt{Splay}$ 模板题，可是小萌新 $\varnothing$ 实在是太菜了，他只会使用优先队列。

## 思路

>很明显，数列 $a$ 是由若干段区间组成，每一段区间数字相同，以下均用“颜色”表示每一段区间的数字（属性）。

- 本题唯一值得关注的地方是 **删除一个区间后，左右两边的区间如果颜色相同，就会合并成一个大区间**。

先不考虑如何实现，我们先考虑思路：

1. 从当前所有区间中找出长度最大的（相同长度找最左边的），记为区间 $cur$，删除，计数器$+1$；

2. 判断 $cur$ 的左右区间颜色是否相同，若相同，将两个小区间的信息删除，插入合并后的大区间的信息；

3. 检查是否全部删除完了，没删完则重复步骤1，否则结束。

不考虑步骤2，这个过程显然可以用优先队列维护，步骤1即取出堆顶，步骤3检查堆是否为空。

- 现在问题转化为，如何实现步骤2.

直接从堆中找出左右两个元素是十分麻烦的，删除更是没法做。

删除区间 $cur$，查找区间 $cur$ 当前的左右区间，显然可以用双向链表维护。

对于删除堆中的元素，我们可以用 $vis$ 标记这个元素在堆中已经被删除了，若堆顶元素被标记过，直接```continue```掉即可。

- 梳理一下思路，

**维护一个双向链表，链表中每个节点储存【该区间是初始情况中从左往右第 $i$ 个区间】，$pre[i]$ 表示 $i$ 左边的区间编号，$nxt[i]$ 表示 $i$ 右边的区间编号**。

**维护一个优先队列，堆中每节点储存【区间长度，区间编号】，先按照第一维由大到小排序，第一维相同时第二维从小到大排序（左边优先）。**

1. **设当前堆顶区间的编号是 $cur$，我们需要在链表中删除 $cur$，并标记 $vis$；**

2. **若 $pre[cur]$ 与 $nxt[cur]$ 颜色相同，则标记 $vis$ 表示删除了右区间，将【左右区间长度之和，左区间编号】加入优先队列中；**

>加入后，堆中会有两个节点编号都为左区间编号，不过不要紧，因为新加入那个区间长度更大，会被更早取出，取出时标记 $vis$。

3. 计数器$+1$，这回合删除了一个区间。

### 代码

实现时，由于先按第一维升序，再按第二维降序比较麻烦，我们不妨直接将数列 $a$ 翻转过来（倒序输入），这样两维都是升序了。


```cpp
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 200005;
int n, a[maxn], tot, col[maxn], sum[maxn], pre[maxn], nxt[maxn], ans;
bool vis[maxn];
priority_queue<pair<int, int> > q;
int main() {
	ios :: sync_with_stdio(false);
	cin >> n;
	for(int i = n; i; --i) cin >> a[i];
	for(int i = 1; i <= n; ++i)
		if(a[i] == a[i-1]) ++sum[tot];
		else col[++tot] = a[i], sum[tot] = 1;
	for(int i = 1; i <= tot; ++i) pre[i] = i-1, nxt[i] = i+1, q.push(make_pair(sum[i], i));
	while(!q.empty()) {
		int cur = q.top().second; q.pop();
		if(vis[cur]) continue;
		int l = pre[cur], r = nxt[cur];
		pre[r] = l, nxt[l] = r, vis[cur] = true;
		if(l and col[l] == col[r])
			pre[nxt[r]] = l, nxt[l] = nxt[r], vis[r] = true, q.push(make_pair(sum[l]+=sum[r], l));
		++ans;
	}
	cout << ans << endl;
}
```

### p.s

小萌新yy的做法，有hack数据叫我嗷。

---

## 作者：Wen_kr (赞：4)

暴力做法：
每次找出最长的区间并删去，反复模拟。

首先这样肯定会超时，因此我们应该想办法在暴力的某些环节优化。

第一，暴力的查找是 $O(n)$ 的，这是不能接受的，考虑使用线段树优化，合并各个区间，最后取所有区间的结果，这样的查找时间复杂度只有 $O(1)$

具体的合并方法为：

首先对于线段树的每个节点，我们定义一个 $lsum$ 表示左端点的数字，再定义一个 $rsum$ 表示右端点的数字，以及一个 $sum$ 表示区间的长度。

因为每个区间的数字是一样的，我们使用线段树维护的不是每个节点的数字，而是原序列中的每个区间。

所以，线段树上的每个节点还要维护三个值：从左端点开始的最长区间，从右端点开始的最长区间以及全局最长区间。

我们设这三个区间分别为 $lbest,rbest,best$

最后，因为我们需要删除某些节点，因此定义一个 $bool$ 型变量表示这个节点是否删除。

考虑左儿子与右儿子的合并。

若两个儿子都已经被删除，那么这个节点也已经被删除。

若有一个儿子被删除，那么返回那个没删除的儿子。

否则，当前节点的 $lbest$ 就等于左儿子的 $lbest$，当前节点的 $rbest$ 就等于右儿子的 $rbest$，而当前节点的 $best$ 就等于左右儿子 $best$ 长度大的那个 $best$。

再考虑若左儿子的右端点数字等于右儿子左端点的数字，那么这两个区间就能合并：

若左儿子的 $lbest$ 的长度等于左儿子的 $sum$，则说明左儿子单独成一个区间，因此当前节点的 $lbest$ 就等于左儿子的 $lbest$ 加上右儿子的 $lbest$

右儿子的 $rbest$ 长度等于右儿子的 $sum$ 同理。

当前节点的 $best = max(best,lson.rbest + rson.lbest)$

这样合并操作就做完啦~

第二，考虑删除。

由于我们先前的工作，删除是很简单的，只要取出顶部节点 $best$ 的 $l$ 端点与 $r$ 端点，删除这个区间即可，具体请看代码。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 200005;

int a[N];
pair<int,int> b[N];
int n,tot,sum;

struct range
{
	int l,r,len;
	bool operator < (const range &a) const
	{
		if(len != a.len) return len < a.len;
		return l > a.l;
	}
	range operator + (const range &a) const
	{
		return (range){l,a.r,len + a.len};
	}
};

struct node
{
	range lbest,rbest,best;
	int lv,rv,sum;
	bool is_clear;
	void clear()
	{
		is_clear = 1;
		lv = -1,rv = -1;
		best.len = 0,lbest.len = 0,rbest.len = 0;
	}
	void init(int l,int x,int y)
	{
		best = (range){l,l,y};
		lbest = rbest = best;
		sum = y,lv = rv = x,is_clear = 0;
	}
	friend node operator + (const node &a,const node &b)
	{
		static node c;
		if(a.is_clear && b.is_clear)
		{
			c.is_clear = 1;
			c.clear();
			return c;
		}
		if(b.is_clear) return a;
		if(a.is_clear) return b;
		c.is_clear = 0;
		c.sum = a.sum + b.sum;
		c.lv = a.lv,c.rv = b.rv;
		c.lbest = a.lbest;
		c.rbest = b.rbest;
		c.best = max(a.best,b.best);
		if(a.rv == b.lv)
		{
			if(a.lbest.len == a.sum) c.lbest = max(c.lbest,a.lbest + b.lbest);
			if(b.rbest.len == b.sum) c.rbest = max(c.rbest,a.rbest + b.rbest);
			c.best = max(c.best,a.rbest + b.lbest);
		}
		return c;
	}
}tree[N << 2];

void Push_Down(int rt)
{
	if(tree[rt].is_clear == 1)
	{
		tree[rt << 1].clear();
		tree[rt << 1 | 1].clear();
	}
}

void Build(int l,int r,int rt)
{
	if(l == r)
	{
		tree[rt].init(l,b[l].first,b[l].second);
		return ;
	}
	int mid = (l + r) >> 1;
	Build(l,mid,rt << 1);
	Build(mid + 1,r,rt << 1 | 1);
	tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
	//printf("%d %d %d\n",rt,tree[rt].best.l,tree[rt].best.r);
}

void clear(int rt,int l,int r,int l1,int r1)
{
	if(l == l1 && r == r1)
	{
		tree[rt].clear();
		return ;
	}
	//printf("%d %d %d %d WENG\n",l,r,l1,r1);
	Push_Down(rt);
	int mid = (l + r) >> 1;
	if(r1 <= mid) clear(rt << 1,l,mid,l1,r1);
	else if(l1 > mid) clear(rt << 1 | 1,mid + 1,r,l1,r1);
	else
		clear(rt << 1,l,mid,l1,mid),clear(rt << 1 | 1,mid + 1,r,mid + 1,r1);
	tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n; ++ i)
		scanf("%d",&a[i]);
	int s = 1;
	for(int i = 2;i <= n; ++ i)
		if(a[i] != a[i - 1])
			b[++tot] = make_pair(a[i - 1],s),s = 1;
		else
			s ++;
	b[++tot] = make_pair(a[n],s);
	n = tot;
	Build(1,tot,1);
	int sum = 0;
	while(!tree[1].is_clear)
	{
		int l = tree[1].best.l;
		int r = tree[1].best.r;
		clear(1,1,tot,l,r);
		sum ++;
	}
	printf("%d\n",sum);
}

```

---

## 作者：BigJoker (赞：3)

# 前言

我是 sb，考试的时候没有把元素进队，挂了。。。

# 思路

2021 年 csp 普及有一道叫小熊的果篮的题目，跟这道题还是十分相似，都是维护块，然后删除了过后进行合并。
 
考虑双向链表：

题目规定了需要对每一次最长的连续的进行删除，那么我们可以使用一个优先队列来存储每一块的编号。以块长作为第一关键字，最左边的元素作为第二关键字即可。

然后就十分水了。

每次删去最大的时候。

先看看当前的前一块和当前的下一块是否能拼接在一起，即数字相等。如果相等两块进行合并，**然后记得把合并好的进入优先队列**。（这是陈述句）

否则，直接删除即可。

如果当块被合并或者删除时，一定记得打个标记将其视作删除，避免优先队列一直处理。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,ans,cnt;
int a[N],b[N];
int nxt[N],pre[N];
bool f[N];
struct node{
	int Sz,Bh,St,Len;
	friend bool operator<(node x,node y){
		return x.Len==y.Len?x.St>y.St:x.Len<y.Len;
	}
}q[N];
priority_queue<node>qu;
void sub(int x){
	if(q[pre[x]].Sz==q[nxt[x]].Sz){
		f[nxt[x]]=1;
		q[pre[x]].Len+=q[nxt[x]].Len;
		qu.push(q[pre[x]]);
		nxt[pre[x]]=nxt[nxt[x]];
		pre[nxt[nxt[x]]]=pre[x];
	}
	else{
		nxt[pre[x]]=nxt[x];
		pre[nxt[x]]=pre[x];
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),b[i]=a[i];
	sort(b+1,b+1+n);
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+n,a[i])-b;
	for(int i=1;i<=n;){
		int u=a[i];
		q[++cnt].St=i;
		q[cnt].Sz=a[i];
		while(i<=n && a[i]==u) q[cnt].Len++,i++;
		q[cnt].Bh=cnt;
		qu.push(q[cnt]);
	}
	for(int i=1;i<cnt;i++) nxt[i]=i+1;
	for(int i=2;i<=cnt;i++) pre[i]=i-1;
	while(!qu.empty()){
		ans++;
		node x=qu.top();
		qu.pop();
		if(f[x.Bh]){
			ans--;
			continue;
		}
		f[x.Bh]=1;
		sub(x.Bh);
	}
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：wgyhm (赞：2)

看了眼题解，都是我不会而且比较巧妙的做法的做法。由于我没有脑子（划掉），所以我来发一份FHQ-Treap暴力合并、删除的题解。

### 前置芝士

* FHQ-Treap（splay应该也行，但是窝太菜了不会）

* 一个良好的心态

首先，我们先打好一个 FHQ-Treap 的板子，以区间长度为第一关键字，以左端点为第二关键字，建一棵权值平衡树。

```cpp
struct yyy{
	int ls,rs,val,size,rnd,l,r;
    //val表示区间长度，l,r表示区间的左右端点
}a[maxn];
inline void Pushup(int k){
	a[k].size=a[a[k].ls].size+a[a[k].rs].size+1;
}
inline void split(int k,int x,int y,int &a_,int &b_){
	if (!k) a_=b_=0;
	else{
		if (a[k].val>x||(a[k].val==x&&a[k].l<y)) a_=k,split(a[k].rs,x,y,a[k].rs,b_);
		else b_=k,split(a[k].ls,x,y,a_,a[k].ls);
		Pushup(k);
	}
}
inline int merge(int u,int v){
	if (!u||!v) return u|v;
	if (a[u].rnd<a[v].rnd){
		a[u].rs=merge(a[u].rs,v);
		Pushup(u);return u;
	}
	else{
		a[v].ls=merge(u,a[v].ls);
		Pushup(v);return v;
	}
}
```
然后接下来写一个找到区间最大的函数，也就是查找区间排名第一的区间在平衡树中的下标。（至于为什么是下标，因为有了下标可以查找其他东西，而其他东西（区间长度）不能查找下标）
```cpp
inline int at(int x){
	int k=root;
	while (k){
		if (x<=a[a[k].ls].size) k=a[k].ls;
		else if (x==a[a[k].ls].size+1) return k;
		else x-=a[a[k].ls].size+1,k=a[k].rs;
	}
}
```
好的我们~~预处理~~完毕，接下来看主程序。

因为一开始就要分段，所以我们先预处理出原序列中的数段，然后扔到平衡树中。

```cpp
read(n);
	for (i=1;i<=n;i++) read(f[i]);f[n+1]=3e9;
	for (i=2;i<=n+1;i++)
		if (f[i]==f[i-1]) x++;
		else{
		    a[++cnt].val=x;a[cnt].size=1;
			a[cnt].l=a[cnt].tl=i-x;
			a[cnt].rnd=rand();
			split(root,x,a[cnt].l,tmp1,tmp2);
			root=merge(tmp1,merge(cnt,tmp2));
			pos[a[cnt].l]=pos[a[cnt].r]=cnt;
			x=1;++len;
        //x表示区间的长度，len表示总共有多少个数段
        //pos[i]就是以i为端点的区间的下标，用法之后会详细说明。
		}
```
然后进行模拟：
```cpp
while (len>1){
		tmp=at(1);
		split(root,a[tmp].val,a[tmp].l,tmp1,tmp2);
		split(tmp2,a[tmp].val,a[tmp].l+1,tmp2,tmp3);
		root=merge(tmp1,tmp3);
		len--;++ans;
		if (a[tmp].l>1&&a[tmp].r<n&&f[a[tmp].l-1]==f[a[tmp].r+1]){
        //如果被删除的左右区间可以合并，暴力合并
			tot1=pos[a[tmp].l-1];tot2=pos[a[tmp].r+1];
			split(root,a[tot1].val,a[tot1].l,tmp1,tmp2);
			split(tmp2,a[tot1].val,a[tot1].l+1,tmp2,tmp3);
			root=merge(tmp1,tmp3);
			split(root,a[tot2].val,a[tot2].l,tmp1,tmp2);
			split(root,a[tot2].val,a[tot2].l+1,tmp2,tmp3);
			root=merge(tmp1,tmp3);
			a[++cnt].l=a[tot1].l;a[cnt].r=a[tot2].r;pos[a[tot1].l]=pos[a[tot2].r]=cnt;
			a[cnt].size=1;a[cnt].rnd=rand();a[cnt].val=a[tot1].val+a[tot2].val;
			split(root,a[cnt].val,a[cnt].l,tmp1,tmp2);
			root=merge(tmp1,merge(cnt,tmp2));len--;
            //记得减去
		}
	}
	printf("%d ",ans+1);
```

当然事情并没有这么简单，看一组数据：

input:
```
7
1 2 2 3 3 3 1
```
这显然输出 $3$，但是程序输出了 $4$。

至于为什么，就是在 $[4,6]$ 删除完毕以后，$[7,7]$ 依然是 $[4,6]$ 右边的区间而不是 $[2,3]$ 的区间，所以我们将删除后的区间而左右区间不能合并的区间向左边的区间（向右也行）合并，改动左右端点，但是相对排名，区间大小，都是不变的。

不过当这个区间的左端点为 $1$ 是就没有必要向左合并了，至于原因也很好想，就不做解释了。（这个情况合并还会WA#7不知道为什么）。

因为有了这个操作，我们还要记录其真实的区间左右端点坐标，比如上面的数据为例，$[2,3]$,$[4,6]$合并以后，真实的区间左右端点坐标应该还是 $2,3,$ 不然左右区间合并的时候，认为右端点是 $6$ 就错了。
   

然后就是亿点细节，当然也有更好的打法，但是我认为的做法根本不需要太多的思考。贴上修改过的主程序：

Code:

```cpp
//a[k].tl,a[k].tr表示这个区间的真实左右端点
int main(){
	srand(time(0));
	rg int i,x=1,n,len=0,tmp,tmp1,tmp2,tmp3,tot1,tot2,ans=0;
	read(n);
	for (i=1;i<=n;i++) read(f[i]);f[n+1]=3e9;
    //不要赋1e9，因为有一个点最后一个数也是1e9然后就误判。。。以后还是要看清数据范围 
	for (i=2;i<=n+1;i++)
		if (f[i]==f[i-1]) x++;
		else{
		    a[++cnt].val=x;a[cnt].size=1;
			a[cnt].l=a[cnt].tl=i-x;
			a[cnt].r=a[cnt].tr=i-1;
            //一开始都是相同的
			a[cnt].rnd=rand();
			split(root,x,a[cnt].l,tmp1,tmp2);
			root=merge(tmp1,merge(cnt,tmp2));
			pos[a[cnt].l]=pos[a[cnt].r]=cnt;
			x=1;++len;
		}
	while (len>1){
		tmp=at(1);
		split(root,a[tmp].val,a[tmp].tl,tmp1,tmp2);
		split(tmp2,a[tmp].val,a[tmp].tl+1,tmp2,tmp3);
		root=merge(tmp1,tmp3);pos[a[tmp].l]=pos[a[tmp].r]=0;
		len--;++ans;
		
		if (a[tmp].l>1&&a[tmp].r<n&&f[a[pos[a[tmp].l-1]].tr]==f[a[pos[a[tmp].r+1]].tl]&&pos[a[tmp].l-1]&&pos[a[tmp].r+1]){
        //这里其实写的有些套，但是想一下也是不难的
			tot1=pos[a[tmp].l-1];tot2=pos[a[tmp].r+1];
			split(root,a[tot1].val,a[tot1].tl,tmp1,tmp2);
			split(tmp2,a[tot1].val,a[tot1].tl+1,tmp2,tmp3);
			root=merge(tmp1,tmp3);
			split(root,a[tot2].val,a[tot2].tl,tmp1,tmp2);
			split(tmp2,a[tot2].val,a[tot2].tl+1,tmp2,tmp3);
			root=merge(tmp1,tmp3);
			
			a[++cnt].l=a[tot1].l;a[cnt].r=a[tot2].r;
			a[cnt].tl=a[tot1].tl;a[cnt].tr=a[tot2].tr;
			pos[a[tot1].r]=pos[a[tot2].l]=0;
			pos[a[tot1].l]=pos[a[tot2].r]=cnt;
            //这里一定要先赋0再赋成cnt,因为有些情况下l=r最后pos[l]=0了。
			a[cnt].size=1;a[cnt].rnd=rand();
			a[cnt].val=a[tot1].val+a[tot2].val;
			split(root,a[cnt].val,a[cnt].tl,tmp1,tmp2);
			root=merge(tmp1,merge(cnt,tmp2));len--;
		}
		else if (a[tmp].l>1){
			tot1=pos[a[tmp].l-1];
			pos[a[tot1].r]=0;
			pos[a[tot1].l]=pos[a[tot1].r=a[tmp].r]=tot1;
	}
    //因为这样排名并不会改变，所以说不需要拿出来合并再放回去。
	printf("%d",ans+1);
	return 0;
}
```

还有问题欢迎私信问我，NOIP2020 之前应该都行。

---

## 作者：万弘 (赞：2)

考虑每次取出最大值,并找到位置.用`std::set`维护,以长度相反数为第一关键字,起始位置为第二关键字,记为$len$.每次取出最小(长度最大)即可.

取出长度最大值后,若左边元素和右边元素相同则需要合并;可以用链表维护,但也可以用`std::set`维护,以起始位置为第一关键字,长度为第二关键字,顺便记录元素的值,记为$seg$.用`set::lower_bound`找到前驱后继即可.  
时间复杂度$\mathcal O(n\log n)$
```cpp
/**********/
#define MAXN 200011
std::set<pll>len;
struct one
{
    ll pos,len,num;
    bool operator <(const one& t)
    const
    {
        return (pos<t.pos||(pos==t.pos&&len<t.len));
    }
};
std::set<one>seg;
int main()
{
    ll n=read(),pre=read(),cnt=1,ans=0;
    if(n==1){puts("1");return 0;}
    for(ll i=2;i<=n;++i)
    {
        ll x=read();
        if(x==pre)++cnt;
        else
        {
            len.insert(pll(-cnt,i-cnt)),seg.insert(one{i-cnt,cnt,pre});
            pre=x,cnt=1;
        } 
    }
    len.insert(pll(-cnt,n+1-cnt)),seg.insert(one{n+1-cnt,cnt,pre});
    while(!len.empty())
    {
        ++ans;
        ll l=len.begin()->first,pos=len.begin()->second;
        auto place=seg.lower_bound(one{pos,0,0});
        if(place!=seg.begin())
        {
        	auto pre=--place,nxt=++(++place);
	        if(pre!=seg.end()&&nxt!=seg.end())
	        {
	            if(pre->num==nxt->num)
	            {
	                len.insert(pll(-pre->len-nxt->len,pre->pos));
	                len.erase(len.lower_bound(pll(-pre->len,pre->pos)));
	                len.erase(len.lower_bound(pll(-nxt->len,nxt->pos)));
	                seg.insert(one{pre->pos,pre->len+nxt->len,pre->num});
	                seg.erase(pre),seg.erase(nxt);
	            }
	        }
		}
        len.erase(len.lower_bound(pll(l,pos)));
        seg.erase(seg.lower_bound(one{pos,0,0}));
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Others (赞：1)

这题我分享一种比较暴力但复杂度没有问题的算法，其他的题解应该都没有而且我这很复杂，我也会讲一下其他的方法 qwq。

# Solution1

看到题就会想到删除一段后两边的可能会合并，然后就是求最大的长度以及最靠前的，处理好这些问题，就淼了一道紫题了。

讲讲怎么实现：

对于原数组，我们可以将他简化成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/7pligfrx.png)

也就是相同的的元素我们将他们整成一坨，每坨有一个 $cnt$ 和 $x$，然后将他们连成链表，为了防止因特判边界而发烧，我将 $0$ 好节点连向两端，使他们构成一个环，这样就好删了（也好合并了）。

然后是找当前要删的，这里我打的是线段树，也就是权值线段树维护 $cnt$ 域上的 $x$，就是因为 $x$ 还要有序，我就把 $x$ 插入其对应的叶子结点的 `set` 里，因为合并时要对应删除（不然我就打 `priority_queue` 了），这样虽然很复杂，但是稳定性个人感觉打出来就不存在不过的情况。

献上一份又臭又长还没人看的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename zqw>void qr(zqw &x){
	bool f=x=0;
	char c=getchar();
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x=f?~(x-1):x;
	return ;
}
int step,lst[200005],nxt[200005],n,a[200005],flag[200005],N,top;
struct node{
	int x,cnt;
}p[200005];
struct Tnode{
	int l,r,sum;
	set<int> pos;
}tr[800005];
void pushup(int p){
	tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
}
void build(int l,int r,int p){
	tr[p].l=l,tr[p].r=r;
	if(l==r){
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
}
void add(int x,int y,int p){
	if(tr[p].l==tr[p].r){
		tr[p].sum++;
		tr[p].pos.insert(y);
		return ;
	}
	int mid=(tr[p].l+tr[p].r)>>1;
	if(x<=mid) add(x,y,p<<1);
	else add(x,y,p<<1|1);
	pushup(p);
}
void del(int x,int y,int p){
	if(tr[p].l==tr[p].r){
		tr[p].sum--;
		tr[p].pos.erase(y);
		return ;
	}
	int mid=(tr[p].l+tr[p].r)>>1;
	if(x<=mid) del(x,y,p<<1);
	else del(x,y,p<<1|1);
	pushup(p);
}
int ask(int p){
	if(tr[p].l==tr[p].r){
		return *tr[p].pos.begin();
	}
	if(tr[p<<1|1].sum) return ask(p<<1|1);
	return ask(p<<1);
}
void Del(int p){
	lst[nxt[p]]=lst[p];
	nxt[lst[p]]=nxt[p];
}
int main() {
	qr(n);
	for(int i=1;i<=n;i++){
		qr(a[i]);
		flag[i]=a[i];
	}
	sort(flag+1,flag+n+1);
	N=unique(flag+1,flag+n+1)-flag-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(flag+1,flag+N+1,a[i])-flag;
	p[++top]=(node){a[1],1};
	for(int i=2;i<=n;i++) {
		if(a[i]==p[top].x) p[top].cnt++;
		else p[++top]=(node){a[i],1};
	}
	build(1,n,1);
	for(int i=1;i<=top;i++) {
		lst[i]=i-1,nxt[i]=(i==top?0:i+1);
		add(p[i].cnt,i,1);
	}
	nxt[0]=1,lst[0]=top;
	p[0]=(node){0,0};
	while(nxt[0]){
		step++;
		int tmp=ask(1),Tmp;
		if(p[nxt[tmp]].x==p[lst[tmp]].x&&nxt[tmp]&&lst[tmp]){
			del(p[lst[tmp]].cnt,lst[tmp],1),del(p[nxt[tmp]].cnt,nxt[tmp],1);
			p[lst[tmp]].cnt+=p[nxt[tmp]].cnt;
			Del(nxt[tmp]);
			add(p[lst[tmp]].cnt,lst[tmp],1);
		}
		Del(tmp);
		del(p[tmp].cnt,tmp,1);
	}
	printf("%d",step);
	return 0;
}
```

# Solution2

这题的线段树其实是非常没有必要的（虽然在考场上我并没有意识到）。直接将结构体（$x,cnt$）塞到一个平衡树（`set`）里，重载一下运算符就轻松过了，并没有上一种算法那么复杂，但看同学们的情况这种做法细节很难调。

因为我没打这种做法，所以就给一个重载运算符的代码：

```cpp
struct node{
	int cnt,x,id;//id 是转化成链表后对应的元素下标。
    bool operator<(const node &p)const{
    	return cnt<p.cnt||(cnt==p.cnt&&id<p.id);
    }
}
```

---

## 作者：Forsaken2020 (赞：1)

**数组链表+优先队列**


突然不想写题了，不如来摸鱼写题解吧— —。这个题是在学校的暑假集训的时候遇到的，题意大概就是说给定一个序列，每次选择这个序列中出现连续数字最长的一段，然后将这段子序列从原序列中删去，如果有多个子序列满足条件，则优先删除子序列中靠近原序列左端的(也就是删遇到的第一个最长子序列)。

这个题的难点在于你删掉一个子序列之后，可能这个子序列两边的两个序列刚好拥有相同的值，那么就能连接在一起，比如1 1 2 2 3 3 3 3 2 2 。

删除3 3 3 3之后得到1 1 2 2 2 2，那么我们就必须要想办法维护可能得到的新序列。一个朴素的想法就是我们在读入的时候将序列压缩，比如2 2 2 2压缩成一个值为2，大小为4的一个数据，然后每次都去找最长的序列，找到之后删除这个序列并且将两端的序列连在一起更新就行了。哦，however，考虑最坏的情况，假如序列中所有数都不相同，那么每次都只能删一个数，复杂度近似O(n^2)，显然，这个复杂度T到不能再T了。

那么我们该怎么办呢。怎么办呢。

考虑以上做法，复杂度最高的地方就是找要删除的序列，那么有什么方法使这个位置的复杂度变成O(logn)呢？显然是存在很多方法完成这个操作，我们这里解决这个地方选择了优先队列的做法，优先队列里面维护序列最长的位置就行了，然后我们将序列压缩，然后用链表连在一起就行了。删除操作显然是O(1)的，而查找操作是O(logn)的。Therefore，我们就成功把整体复杂度降低为O(nlogn)。下面给出代码实现。这个做法可以说是跑的飞快。

```cpp
//author Eterna
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<cmath>
#include<climits>
#include<deque>
#include<functional>
#include<complex>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define INF 0x7fffffff
#define Pi acos(-1.0)
#define maxn 200000
#define eps 1e-15
#define MOD ((ll)1000000007)
#define ABS(x) ((x)>=0?(x):(-(x)))
#define pb(x) push_back(x)
#define lowbit(x) (x&-x)
#define mid (L+R)/2
#define Lson (index*2)
#define Rson (index*2+1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
inline int read_int() {
	char c;
	int ret = 0, sgn = 1;
	do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
	if (c == '-') sgn = -1; else ret = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
	return sgn * ret;
}
inline ll read_ll() {
	char c;
	ll ret = 0, sgn = 1;
	do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
	if (c == '-') sgn = -1; else ret = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
	return sgn * ret;
}
//快读
struct node {
	bool operator<(const node& rhs)const {
		if (number == rhs.number)return pos > rhs.pos;
		return number < rhs.number;
	}
	node() = default;
	node(int n, int p) {
		number = n; pos = p;
	}
	int number = 0, pos = 0;
};
//定义优先队列中的节点
struct seg {
	int value, number;
};//压缩序列
int n, _next[maxn + 5], last[maxn + 5], cnt, x, t, number_seg, ans;
bool cant_visit[maxn + 5];//记录不能再访问的节点
seg arr[maxn + 5];
priority_queue<node> q;
int main(void)
{
	n = read_int(); x = read_int(); cnt = 1;
	for (int i = 1; i != n; i++) {
		t = read_int(); if (t == x)cnt++;
		else {
			arr[++number_seg].number = cnt;
			arr[number_seg].value = x;
			x = t; cnt = 1;
		}
	}
	arr[++number_seg].number = cnt; arr[number_seg].value = x; cnt = 0;
	arr[number_seg + 1].value = -INF; arr[0].value = INF;//防止头尾对链表的影响
	for (int i = 1; i <= number_seg; i++) {
		_next[i] = i + 1; last[i] = i - 1;
		q.push(node(arr[i].number, i));
	}
	while (cnt != n && !q.empty()) {
		node sb = q.top(); q.pop();
		if (cant_visit[sb.pos])continue;
		ans++; cnt += arr[sb.pos].number;
		cant_visit[sb.pos] = true;
		int _Next = _next[sb.pos], _Last = last[sb.pos];
		if (arr[_Next].value == arr[_Last].value) {//处理删掉区间之后连在一起的情况
			arr[_Last].number += arr[_Next].number;
			cant_visit[_Next] = true;
			q.push(node(arr[_Last].number, _Last));
			_Next = _next[_Next];
			last[_Next] = _Last;
			_next[_Last] = _Next;
		}
		else {
			last[_Next] = _Last;
			_next[_Last] = _Next;
		}
	}
	cout << ans << endl;
	//system("pause");
	return 0;
}
```


---

## 作者：Poncirus (赞：0)

看完题后，可以很快想到，类似于 [小熊的果篮](https://www.luogu.com.cn/problem/P7912)，我们可以使用 **优先队列 + 链表** 完成这道题目。

首先我们预处理出序列里的每一个“块”，并使用链表维护每一个“块”的如下信息：

* **长度**，即这一段连续相同数字的个数；
* **数值**，即这一个“块”中全部都是这个数；
* **起始位置**，为了满足题目要求的先删靠前的“块”这个要求。

接下来，我们用一个 **大根堆** 维护每一个块，以 **长度** 为第一关键字，**起始位置** 为第二关键字。

每次取出堆顶的一个“块”并将其从链表中删除。若删除后，原来与该“块”相邻的两个“块” **数值** 相同，则在链表中将后面的那个“块”合并到前面的那个“块”中，并将更新后的前面那个“块”重新入队。

值得注意的是，因为涉及到删除“块”与合并“块”的操作，我们使用一个数组来标记一个“块”是否被删除。

**最后“取出堆顶”操作进行的次数即为答案。**

***


```cpp
#include<bits/stdc++.h>
namespace List{
#define int long long
#define nex(x) link[x][ne]
#define pre(x) link[x][pr]
const int maxn=2e5+5;
template<class T>class list{
	private:
		T a[maxn];
		bool ne,pr;
		int tot,h,t,siz;
		int link[maxn][2];
		inline void swap(T&x,T&y){ T t=y; y=x; x=t; return; }
	public:
		list(void){ link[h=0][ne=0]=1;
			link[t=1][pr=1]=0; tot=1; }
		inline void clear(void){
			link[h=0][ne=0]=1;
			link[t=1][pr=1]=0;
			tot=1; return;
		}
		inline int AddAfter(int k,T x){
			nex(++tot)=nex(k); nex(k)=tot;
			pre(tot)=k; pre(nex(tot))=tot;
			a[tot]=x; ++siz;
			return tot; 
		}
		inline int AddBefore(int k,T x){
			pre(++tot)=pre(k); pre(k)=tot;
			nex(tot)=k; nex(pre(tot))=tot;
			a[tot]=x; ++siz;
			return tot;
		}
		inline int AddatHead(T x){ return AddAfter(h,x); }
		inline int AddatTail(T x){ return AddBefore(t,x); }
		inline void Delete(int k){
			nex(pre(k))=nex(k); pre(nex(k))=pre(k); --siz;
			return;
		}
		inline void DeleteAfter(int k){ Delete(nex(k)); }
		inline void DeleteBefore(int k){ Delete(pre(k)); }
		inline void DeleteatHead(void){ Delete(nex(h)); }
		inline void DeleteatTail(void){ Delete(pre(t)); }
		inline int GetHead(void){
			if(pr) return nex(h);
			return nex(t);
		}
		inline int GetSize(void){ return siz; }
		inline bool Empty(void){ return !siz; }
		inline int GetTail(void){
			if(pr) return t;
			return h;
		}
		inline int GetBack(void){
			if(pr)  return pre(t); 
			return pre(h);
		}
		inline int GetPrev(int k){ return pre(k); }
		inline int GetNext(int k){ return nex(k); }
		inline T& GetValue(int k){ return a[k]; }
		inline void Swap(int x,int y){
			swap(a[x],a[y]); return;
		}
		inline void Reverse(void){ pr^=1; ne^=1; return; }
		inline void MakeLoop(void){
			nex(pre(t))=nex(h);
			pre(nex(h))=pre(t);
			return;
		}
};
#undef int
#undef nex
#undef pre
} // namespace List
namespace XSC062{
#define int long long
using namespace List;
const int inf=1e18;
const int maxn=2e5+5;
struct _{
	int u,d,i; _(){}
	_(int U,int D,int I){ u=U; d=D; i=I; }
};
struct __{
	int u,d,i,m; __(){}
	__(int U,int D,int I,int M){ u=U; d=D; i=I; m=M; }
	bool operator<(const __ q)const{
		return d==q.d?i>q.i:d<q.d;
	}
};
inline void read(int&x){
	x=0; bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	if(f) x=-x; return;
}
list<_>li;
int a[maxn];
bool vis[maxn];
int n,ans,f,l,r;
std::priority_queue<__>q;
int main(){
	read(n); a[0]=inf;
	for(int i=1;i<=n;++i){
		read(a[i]);
		if(a[i]!=a[i-1])
			li.AddatTail(_(0,a[i],i));
		++li.GetValue(li.GetBack()).u;
	}
	for(int i=li.GetHead();i!=li.GetTail();i=li.GetNext(i))
		q.push(__(i,li.GetValue(i).u,li.GetValue(i).i,
		li.GetValue(i).d));
	while(!q.empty()){
		int f=q.top().u, t=q.top().i; q.pop();
		if(vis[f]) continue; vis[f]=1; ++ans;
//		printf("%lld: %lld, %lld\n",f,li.GetValue(f).d,t);
		l=li.GetPrev(f); r=li.GetNext(f);
		if(f==li.GetHead()||f==li.GetBack()){
			li.Delete(f);
			continue;
		}
		li.Delete(f);
		if(li.GetValue(l).d==li.GetValue(r).d){
			li.GetValue(l).u+=li.GetValue(r).u;
			li.Delete(r); vis[r]=1;
			q.push(__(l,li.GetValue(l).u,t,li.GetValue(l).d));
		}
	}
	printf("%lld",ans);
	return 0;
}
#undef int
} // namespace XSC062
int main(){ XSC062::main(); return 0; }
```

---

## 作者：Liynw (赞：0)

这是我们考试题，我做了 $75$ 分，最后才发现是元素入队的时候没有赋值……

***

### Problem

> 有一个长度为 $n$ 的整数数组，对数组执行若干次操作。每一次找到连续相等整数的最长段（如果有多个段长度相同，选择最靠左边的段）并删除它。要求计算经过多少次操作后数组为空。

***

### Solution

因为前两天才调完[小熊的果篮](https://www.luogu.com.cn/problem/P7912)，记忆犹新，所以立刻想到了**队列+链表**的做法。然后再读题，发现需要找长度最长的区间，不能用普通队列，要用**优先队列**。

我们先把所有的区间都找出来，存储每一个区间的左端点，长度（这样就可以算出右端点了）和这个区间数字的值。然后把这些区间全部按照顺序弄到一个双向链表里面，并把需要的值加入优先队列。

详细的讲解在代码注释里。

```cpp
// 定义结构体，需要存区间左端点，区间长度和它在链表里的下标
struct node { int l, len, id; };
std::priority_queue<node> q;
// 定义排序规则：区间长度，一样时左边优先
bool operator<(node x, node y) { return (x.len != y.len) ? (x.len < y.len) : (x.id > y.id); }

// lst 为上一个区间的左端点，因为我们要计算区间长度，所以需要用这个区间和上个区间的左端点算上一个区间的长度，需要存一下
int ans = 0, lst = 0; 
a[0] = a[n + 1] = -1; // 特殊处理头尾端点，以免错误合并
rep(i, 1, n) {
	if(a[i] != a[i - 1]) { // 说明这个数是一个区间的开头
		num[++k] = a[i];
		l[k] = k - 1; // 初始化链表
		r[k] = k + 1;
		if(k != 1) { // 如果这个区间有上一个，即不是第一个
			q.push(node({lst, i - lst, k - 1})); // 元素入队
			L[k - 1] = lst, LEN[k - 1] = i - lst; // 记录区间左端点和长度
		}
		lst = i; // 更新上一个区间的左端点
	}
}
q.push(node({lst, n - lst + 1, k})); // 最后一个区间也需要处理
L[k] = lst, LEN[k] = n - lst + 1;
r[0] = 1, l[k + 1] = k; // 链表的初始化
```

接着就是核心代码了。

我们用一个 `bool` 数组标记一个区间是否被取过，然后从队列里面不停取元素。

- 若此区间已经被标记过了就直接跳过。
- 若此区间没有被取过，就标记一下这个区间，此时又取了一个区间，答案需要 $+1$，然后检查一下它的左右两个区间是否需要被合并；如果需要，就把两个区间合并到它左边那个区间，并标记它右边那个区间。

这句话信息量有点大，是什么意思呢？

说明我们拿到一个没被取过的区间时，需要做这几件事：

1. 把这个区间标记为“已经被取过”。
1. 因为又取了一个区间，所以答案要 $+1$。
1. 把这个区间从链表里删掉。
1. 检查这个被删除的区间的左边的区间（命名为 $l$）和它右边的区间（命名为 $r$）是否需要被合并，也就是说这两个区间的值是不是一样的，如果是一样的，那这个区间被取了之后，$l$ 和 $r$ 就变成了一个区间，所以需要被合并。
1. 合并两个区间的时候，可以把 $l$ 的长度改为两个区间的长度相加，然后把 $r$ 删掉。需要注意 $r$ 也要被标记。
1. 把更新的 $l$ 加入队列。

这个时候就会有小朋友问了：此时队列里还有原来的 $l$，是不是需要删掉？

答案是不需要。因为优先队列的排序规则是按照长度从大到小排的，所以更新后的 $l$ 一定会比原来的 $l$ 先取出，取出之后我们就标记了 $l$，也就不会重复取到了。

给一下代码。

```cpp
inline void remove(int x) {
	id_use[x] = 1; // 实现时可以把标记的代码放在删除的函数里面
	r[l[x]] = r[x];
	l[r[x]] = l[x];
	return;
}

while(!q.empty()) {
	while(!q.empty() && id_use[q.top().id]) // 过滤掉已经被标记过的点
		q.pop();
	if(q.empty()) // 如果队列被取空了就直接跳过
		break;
	node u = q.top();
	q.pop();
	++ans; // 更新答案
	if(num[r[u.id]] == num[l[u.id]]) { // 如果 l 和 r 需要被合并
		LEN[l[u.id]] += LEN[r[u.id]]; // 赋值，注意这里不写只能得 75 分
		q.push(node({L[l[u.id]], LEN[l[u.id]], l[u.id]})); // l 入队
		remove(r[u.id]); // 删除 r
	}
	remove(u.id); // 把这个区间删除
}
write(ans - 1); // 这里 -1 是因为头和尾会被错误合并，所以会多一次
```

大概就是这样了吧。因为核心代码已经给出，所以不再给完整代码了。

~~另外就是祝贺一下 ljt 考试的时候终于没有写挂快读快写了。~~

---

## 作者：bwartist (赞：0)

因为是删除连续的一段，我们不妨就**把信息都放在每一连续段的左端点**。

“删除某一段长度”就可以想成： “删除这一段的左端点”，而删除节点又可联想到**链表**。

在删除某一段的时候，如果左右数字相等，就需要改变左右两边段的长度，可以理解成**“合并”**。具体做法可以 **“删除”右边段（这里不是题目描述中的删除！只是将它的信息给左段），并更新左边段长度**。

在合并过程中，最大值，最小值可能会发生变化，所以可以想到**优先队列**。**更新左段长度**的时候就要往优先队列里添加元素。**删除右段**的时候不用在优先队列里实际操作，只需要用一个数组标记一下这个块是否被删除。每次进行题目里真正的的删除操作时，就去优先队列的队首元素即可。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[200005];
bool flag[200005];//是否被删除
struct h {
	int id, num;
};
struct hh {//链表只存每个块的起始位置 
	int l, r, e;//e:块的长度 
}b[200005];
bool operator<(const h &x, const h &y) {
	if (x.num < y.num)	return true;
	if (x.num > y.num)	return false;
	return x.id > y.id;
}
priority_queue<h> q;
int main () {
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)	scanf ("%d", &a[i]);
	int last = -1;
	for (int i = 1; i <= n; i++) {
		flag[i] = true;
		int j = i;
		while (j <= n && a[j] == a[i])	j++;
		j--;
		h t;
		t.id = i, t.num = j - i + 1;
		q.push(t);
		b[i].e = j - i + 1, b[i].l = last;
		if (last != -1)	b[last].r = i;
		last = i;
		i = j;
	}
	b[last].r = -1;
	int ans = 0;
	while (!q.empty()) {
		h t = q.top();
		q.pop();
		if (!flag[t.id] || t.num != b[t.id].e)	continue;//这个点已经不再是起点或已经被删除或已经被更新 
		ans++;
		int k = t.id;
		b[b[k].l].r = b[k].r;
		b[b[k].r].l = b[k].l;
		flag[k] = false;
		if (a[b[k].l] == a[b[k].r])	{//两个块合并（删除右节点） 
			flag[b[k].r] = false;
			b[b[k].l].e += b[b[k].r].e;
			int L = b[k].r;
			b[b[L].l].r = b[L].r;
			b[b[L].r].l = b[L].l;
			h t2;
			t2.id = b[k].l;
			t2.num = b[b[k].l].e;
			q.push(t2);
		}
	}
	printf ("%d", ans);
	return 0;
}
```


---

