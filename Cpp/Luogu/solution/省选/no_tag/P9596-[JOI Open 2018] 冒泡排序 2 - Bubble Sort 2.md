# [JOI Open 2018] 冒泡排序 2 / Bubble Sort 2

## 题目描述

冒泡排序是一个对序列排序的算法。现在我们要将一个长度为 $N$ 的序列 $A_0,A_1,\ldots ,A_{N-1}$​ 按不降顺序排序。当两个相邻的数没有按正确顺序排列时，冒泡排序会交换这两个数的位置。每次扫描这个序列就进行这种交换。更确切地说，在一趟**扫描**中，对于 $i=0,1,\ldots ,N-2$，并按这个顺序，如果 $A_i>A_{i+1}$​，那么我们就交换这两个数的位置。众所周知任何序列经过有限趟扫描后一定可以按非降顺序排好序。对于一个序列 $A$，我们定义**用冒泡排序的扫描趟数**为使用如上算法使得 $A$ 排好序的情况下所扫描的趟数。

JOI 君有一个长度为 $N$ 的序列 $A$。他打算处理 $Q$ 次修改 $A$ 的值的询问。更明确地说，在第 $(j+1)\ (0\le j\le Q-1)$ 次询问，$A_{X_j}$ 的值会变为 $V_j$。

JOI 君想知道处理每次修改之后，用冒泡排序的扫描趟数。

## 说明/提示

**【样例解释】**

给定一个长度为 $N=4$ 的序列 $A=\{1,2,3,4\}$ 和 $Q=2$ 次询问：$X=\{0,2\},V=\{3,1\}$。

1. 对于第一次询问，$A_0$ 的值变为 $3$。我们得到 $A=\{3,2,3,4\}$。
2. 对于第一次询问，$A_2$ 的值变为 $1$。我们得到 $A=\{3,2,1,4\}$。

对 $A=\{3,2,3,4\}$ 做冒泡排序：

- $A$ 并未排好序，所以第一趟扫描开始。因为 $A_0>A_1$，所以我们交换它们，序列变为 $A=\{2,3,3,4\}$。因为 $A_1\le A_2$，所以我们不交换它们。因为 $A_2\le A_3$，所以我们也不交换它们。
- 现在 $A$ 已经排好序了，所以冒泡排序过程结束。

因此对于 $A=\{3,2,3,4\}$，冒泡排序的扫描趟数为 $1$。

对 $A=\{3,2,1,4\}$ 做冒泡排序：

- $A$ 并未排好序，所以第一趟扫描开始。因为 $A_0>A_1$，所以我们交换它们，序列变为 $A=\{2,3,1,4\}$。因为 $A_1> A_2$，所以我们交换它们，序列变为 $A=\{2,1,3,4\}$。因为 $A_2\le A_3$，所以我们也不交换它们。
- $A$ 并未排好序，所以第二趟扫描开始。因为 $A_0>A_1$，所以我们交换它们，序列变为 $A=\{1,2,3,4\}$。因为 $A_1\le A_2$，所以我们不交换它们。因为 $A_2\le A_3$，所以我们也不交换它们。
- 现在 $A$ 已经排好序了，所以冒泡排序过程结束。

因此对于 $A=\{3,2,1,4\}$，冒泡排序的扫描趟数为 $2$。

**【数据范围】**

共有四个子任务。每个子任务的分值及附加限制如下：

| 子任务编号 | 分值 |         $N$          |         $Q$          |              $A,V$               |
| :--------: | :--: | :------------------: | :------------------: | :------------------------------: |
|    $1$     | $17$ |  $1\le N\le 2\ 000$  |  $1\le Q\le 2\ 000$  |      $1\le A_i,V_j\le 10^9$      |
|    $2$     | $21$ |  $1\le N\le 8\ 000$  |  $1\le Q\le 8\ 000$  | $1\le A_i,V_j\le 10^9$ |
|    $3$     | $22$ | $1\le N\le 50\ 000$  | $1\le Q\le 50\ 000$  |      $1\le A_i,V_j\le 100$       |
|    $4$     | $40$ | $1\le N\le 500\ 000$ | $1\le Q\le 500\ 000$ |      $1\le A_i,V_j\le 10^9$      |



## 样例 #1

### 输入

```
4 2
1 2 3 4
0 3
2 1```

### 输出

```
1
2```

## 样例 #2

### 输入

```
11 12
11 4 13 6 7 3 5 12 4 10 11
8 11
4 4
6 20
0 2
7 2
3 18
5 9
0 6
8 8
9 4
0 8
6 18
```

### 输出

```
5
5
5
4
6
6
6
7
7
7
7
7```

# 题解

## 作者：liuhangxin (赞：21)

## P9596 [JOI Open 2018] 冒泡排序 2

一个序列 $A$ 的扫描次数为 $\max_{i=1}^n \sum_{j=1}^i[a_j>a_i]$。

证明：

发现一次操作必定将恰好一个 $p$ 前面大于他的数换到他后面(排除没有的)。原式子相当于对于每个位置 $p$ ，把其前面大于他的换到他后面需要的扫描次数取 $\max$ ，即操作后对于每个位置其前面没有大于他的，序列 $A$ 就是拍好序列。

发现同样的值只有最后一个位置 $p$ 有用，一种值的答案为 $\sum [A_i>v]-(n-p)$，其中可以把 $n-p$ 看作后面比他大的值，因为如果后面有比他小的值 $v2$ ，他的最后一个位置 $p2>p$，一定有 $\sum [A_i>v2]-(n-p2)>\sum [A_i>v]-(n-p)$ ，即值 $v$ 一定不优。

开棵权值线段树直接维护这个式子的最值，用 set 维护每种颜色的位置集合即可。

代码如下:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=1e6+10,inf=1e9;
int n,q;
int a[N],stk[N],cnt;
int p[N],v[N];
set<int>s[N];
int Max[4*N],tag[4*N];
#define mid (l+r)/2
#define L 2*u
#define R 2*u+1
void change(int u,int l,int r,int lp,int rp,int v)
{
    if(lp>rp)return;
    if(lp<=l&&r<=rp)
    {
        Max[u]+=v;
        tag[u]+=v;
        return;
    }
    if(lp<=mid)change(L,l,mid,lp,rp,v);
    if(rp>mid)change(R,mid+1,r,lp,rp,v);
    Max[u]=max(Max[L],Max[R])+tag[u];
}
void Add(int c,int p){
    change(1,1,cnt,1,c-1,1);
    if(!s[c].size())change(1,1,cnt,c,c,inf-n);
    else change(1,1,cnt,c,c,-*prev(s[c].end()));
    s[c].insert(p);
    change(1,1,cnt,c,c,*prev(s[c].end()));
}
void Del(int c,int p)
{
    change(1,1,cnt,1,c-1,-1);
    change(1,1,cnt,c,c,-*prev(s[c].end()));
    s[c].erase(p);
    if(!s[c].size())change(1,1,cnt,c,c,-(inf-n));
    else change(1,1,cnt,c,c,*prev(s[c].end()));
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),stk[++cnt]=a[i];
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&p[i],&v[i]);p[i]++;
        stk[++cnt]=v[i];
    }
    sort(stk+1,stk+cnt+1);
    cnt=unique(stk+1,stk+cnt+1)-stk-1;
    for(int i=1;i<=cnt;i++)change(1,1,cnt,i,i,-inf);
    for(int i=1;i<=n;i++)a[i]=lower_bound(stk+1,stk+cnt+1,a[i])-stk;
    for(int i=1;i<=q;i++)v[i]=lower_bound(stk+1,stk+cnt+1,v[i])-stk;
    for(int i=1;i<=n;i++)
        Add(a[i],i);
    for(int i=1;i<=q;i++)
    {
        Del(a[p[i]],p[i]);
        a[p[i]]=v[i];
        Add(a[p[i]],p[i]);
        printf("%d\n",Max[1]);
    }
    return 0;
}
```

---

## 作者：wujingfey (赞：17)

题目传送门：[冒泡排序](https://www.luogu.com.cn/problem/P9596)

## 写在前面
学完线段树后的练习题，听了老师评讲才做出来，于是写一篇题解报告巩固温习。本题解报告会详细的写出推导过程乃至部分分的获得办法，但依旧需要认真梳理逻辑。

# 题意描述
给定一个序列，进行 $q$ 次修改，每次修改后从前往后冒泡，求把序列排序成升序的次数（冒泡完成后要还原数组）。

# 题解
## 算法一
暴力模拟，复杂度拉满了是 $O(n^3)$，如果写点优化应该能过子任务一。反正我没过，T 了两个点。
## 算法二
我们模拟一下冒泡的过程，比如这里有个数列 $a:4,2,3,5,1$，一次冒泡后变成了：$2,3,4,1,5$。我们发现 $2,3,1$ 前面比它们小的数都减少了一个。进行一次冒泡，数列变成了 $2,3,1,4,5$。$1$ 前面比它小的数减少了一个。我们一直冒泡下去，直到每个数前面的数都严格不大于它。

所以我们可以得到规律，设 $f_i$ 为 $a_i$ 前面比 $a_i$ 小的数的个数，其实一次冒泡就是让所有 $f_i-1$，因为一次冒泡我们只会把一个大于 $a_i$ 的数移到 $a_i$ 后面。那很显然，$ans=\max_{i=1}^{n}f_i$。

于是我们可以树套树来维护，用权值线段树维护 $f_i$，用普通线段树维护 $\max f_i$。

复杂度 $O(n\log_2^2n)$，可以通过子任务 $1\sim3$。

~~但因为我太弱了，没学过树套树，所以不会这个部分分。~~

## 算法三，正解
设 $g_i$ 为第 $1\sim i$ 内 $\le a_i$ 的数，显然存在 $f_i=i-g_i$。然而，如果存在两个数使得 $i<j,a_i\geq a_j$，则一定有 $f_i<f_j$。为什么呢？因为 $i<j$ 所以 $a_i$ 在 $a_j$ 后面，被减去的数更少。又因为 $a_i\geq a_j$，**所以比 $a_i$ 小的数一定严格不小于比 $a_j$ 小的数**，也就是 $g_i\geq g_j$，减去的数更多。综上，**如果存在两个数使得 $i<j,a_i\geq a_j$，则一定有 $f_i<f_j$。**

**所以如果我们把 $g_i$ 的定义改成整个数组内 $\le a_i$ 的数，其实答案是不变的。这又是为什么呢？** 考虑这样改变定义后对 $f_i$ 的影响：这样更改后，如果 $a_i$ 后面有比 $a_i$ 小的数 $a_j$，那么 $g_i$ 会增大，$f_i$ 会变小。但又因为 $i<j,a_i\geq a_j$，根据上面的证明可知，$f_i\le f_j$，所以本来 $f_i$ 就不会变成答案了，现在变小了肯定还是不可能。反之，如果没有 $a_i\geq a_j$，那么 $a_i$ 可能成为答案，但这样定义修改后是不会对这个 $f_i$ 产生影响的。如此证明完毕。于是我们可以用权值线段树实现，同时维护至于内数的个数，以及 $\max f_i$。复杂度降低到 $O(n\log_2n)$。

~~救命究竟是怎样的大佬能想出这样的解法啊！~~

# 代码实现
说实话我觉得此题代码写起来还是很有难度的，~~当然不排除是因为我太弱了的问题~~。这里详细解释一下代码的一些实现问题。

## 离散化
首先值域是从 $1\sim 10^9$，所以要建立权值线段树需要离散化。$a$ 是原数组，$q$ 是询问数组（我把询问离线下来了）。$b$ 是离散化数组。不过要注意一下，如果两个元素值相同，相对位置关系不会改变。所以离散化的时候就要同是记录 $val$ 和 $id$，然后 sort 的时候也注意一下。

```cpp
cin>>n>>m;
for(int i=1;i<=n;i++){
	cin>>a[i].val;
	a[i].id=i;
	b[++cnt]=a[i];
}
for(int i=1;i<=m;i++){
	cin>>q[i].id>>q[i].val;//把id号元素修改为val
	q[i].id++;//原编号从0开始，我把它们修改成从1开始，所以id++
	b[++cnt]=q[i];//离线询问 
}
build(1,1,cnt);//建立空树
sort(b+1,b+1+cnt,cmp);//离散化 
```
## 维护线段树
### update_change & update_add
线段树维护两个元素：$maxx,sum$，$maxx$ 表示 $l\sim r$ 内的 $\max f_i$，$sum$ 表示 $l\sim r$ 内有多少个数。于是我们需要分别写两个函数维护：update_change 是插入、删除元素后进行修改，update_add 则修改 $maxx$。

```cpp
void update_change(int p,int x,int d){//对应题目的修改操作 
	if(tr[p].l==tr[p].r){
		if(d!=-INF) tr[p].sum=1;//对应加入 
		else tr[p].sum=0;//对应删除 
		tr[p].maxx=d;
		return;
	}
	push_down(p);
	int mid=(tr[p].l+tr[p].r)>>1;
	if(x<=mid) update_change(p<<1,x,d);
	else update_change(p<<1|1,x,d);
	push_up(p);
}
```
```cpp
void update_add(int p,int l,int r,int d){//对应修改后对maxx的更新 
	if(l>r) return;
	if(l<=tr[p].l&&tr[p].r<=r){
		f(p,d);//修改 
		return;
	}
	push_down(p);
	int mid=(tr[p].l+tr[p].r)>>1;
	if(l<=mid) update_add(p<<1,l,r,d);
	if(mid<r) update_add(p<<1|1,l,r,d);
	push_up(p);
}
```
### query

首先建一棵空树，然后把 $a$ 离散化后的映射值插入树内。假设第 $i$ 个元素的映射值为 $x$，插入之后，我们首先在对应位置的 $sum\gets sum+1$。然后考虑维护 $maxx$：跟上文一样，$g_i$ 表示 $\le x$ 的数，我们还需要函数 $query$ 查询一个元素的排名。
```cpp
int query(int p,int x){//查询一个数的排名 
	if(tr[p].l==tr[p].r) return tr[p].sum;
	push_down(p);
	int mid=(tr[p].l+tr[p].r)>>1;
	if(x<=mid) return query(p<<1,x);
	else return tr[p<<1].sum+query(p<<1|1,x);
}
```
### 插入 $a$ 中元素

**值得注意的是，因为元素有重复的，所以我们在求 $g_i$ 的时候，应该求 $x-1$ 的排名，然后 $+1$，而不是直接 $query(x)$**。

然后根据 $f_i=i-g_i=i-query(x-1)-1$ 修改对应位置的 $maxx$。接着我们又发现，如果在 $x$ 的位置插入了一个数，那么后面所有数的 $g_i$ 都会加一，$f_i$ 则减一。

```cpp
for(int i=1;i<=n;i++){//插入a中元素
	int x=lower_bound(b+1,b+1+cnt,a[i])-b;//查找映射值 
	int y=query(1,x-1);//查找映射值前一位的排名，因为有重复的值	 
	update_change(1,x,i-y-1);//在x的位置加上1，g(x)=i-y-1
	update_add(1,x+1,cnt,-1);//x上的数多了一个，表明g(x+1)~g(cnt)都+1，于是f对应-1 
	c[a[i].id]=x;//把a映射值复制给c 
}
```

此外我们用 $c$ 数组存一下映射值，方便以后的修改操作。
## 修改
主要分为两步：删除原来的数与插入新的数。具体操作看代码吧，注释写的超详细了。
```cpp
for(int i=1;i<=m;i++){//查询 
	update_change(1,c[q[i].id],-INF);//把要更改的元素移除，利用c找到映射值，然后在值域线段树上修改为0 
	update_add(1,c[q[i].id]+1,cnt,1);//从该映射值往后到cnt的fi+1，因为这个值被移除了 
	int x=lower_bound(b+1,b+1+cnt,q[i])-b;//要修改成为哪个映射值
	c[q[i].id]=x;//把对应id的数修改为新的映射值 
	int y=query(1,x-1);//查找映射值前一位的排名
	update_change(1,x,q[i].id-y-1);//同上
	update_add(1,x+1,cnt,-1);//同上 
	cout<<tr[1].maxx<<'\n';
}
```
# AC code
```cpp
#include<bits/stdc++.h>
#define INF 0x7fffffff 
using namespace std;
const int N=5e5+5;
struct NODE{
	int id,val;
	bool operator < (const NODE &a) const{
		if(a.val!=val) return val<a.val;//权值为第一关键字 
		return id<a.id;//顺序为第二关键字 
	}
}a[N],q[N],b[N<<1];
struct TREE{
	int maxx,sum,lz;
	//maxx是f也就是答案，sum记录值域内的数的个数，lz懒标记 
	int l,r;
}tr[N<<3];
int n,m,cnt,c[N<<1];
void push_up(int p){
	tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
	tr[p].maxx=max(tr[p<<1].maxx,tr[p<<1|1].maxx);
}
void f(int p,int d){//给f_max打懒标记 
	if(tr[p].maxx==-INF) return;
	tr[p].lz+=d;
	tr[p].maxx+=d;
}
void push_down(int p){
	if(tr[p].lz){
		f(p<<1,tr[p].lz);
		f(p<<1|1,tr[p].lz);
		tr[p].lz=0;
	}
}
void build(int p,int l,int r){//建空的权值线段树 
	tr[p].l=l; tr[p].r=r;
	if(l==r){
		tr[p].maxx=-INF;
		tr[p].sum=0;
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p);
}
void update_change(int p,int x,int d){//对应题目的修改操作 
	if(tr[p].l==tr[p].r){
		if(d!=-INF) tr[p].sum=1;//对应加入 
		else tr[p].sum=0;//对应删除 
		tr[p].maxx=d;
		return;
	}
	push_down(p);
	int mid=(tr[p].l+tr[p].r)>>1;
	if(x<=mid) update_change(p<<1,x,d);
	else update_change(p<<1|1,x,d);
	push_up(p);
}
void update_add(int p,int l,int r,int d){//对应修改后对maxx的更新 
	if(l>r) return;
	if(l<=tr[p].l&&tr[p].r<=r){
		f(p,d);//修改 
		return;
	}
	push_down(p);
	int mid=(tr[p].l+tr[p].r)>>1;
	if(l<=mid) update_add(p<<1,l,r,d);
	if(mid<r) update_add(p<<1|1,l,r,d);
	push_up(p);
}
int query(int p,int x){//查询一个数的排名 
	if(tr[p].l==tr[p].r) return tr[p].sum;
	push_down(p);
	int mid=(tr[p].l+tr[p].r)>>1;
	if(x<=mid) return query(p<<1,x);
	else return tr[p<<1].sum+query(p<<1|1,x);
}
bool cmp(NODE a1,NODE a2){ 
	if(a1.val!=a2.val) return a1.val<a2.val;
	return a1.id<a2.id;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].val;
		a[i].id=i;
		b[++cnt]=a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].id>>q[i].val;//把id号元素修改为val
		q[i].id++;
		b[++cnt]=q[i];//离线询问 
	}
	build(1,1,cnt);
	sort(b+1,b+1+cnt,cmp);//离散化 
	for(int i=1;i<=n;i++){//建树 
		int x=lower_bound(b+1,b+1+cnt,a[i])-b;//查找映射值 
		int y=query(1,x-1);//查找映射值前一位的排名，因为有重复的值	 
		update_change(1,x,i-y-1);//在x的位置加上1，g(x)=i-y-1
		update_add(1,x+1,cnt,-1);//x上的数多了一个，表明g(x+1)~g(cnt)都+1，于是f对应-1 
		c[a[i].id]=x;//把a映射值复制给c 
	}
	for(int i=1;i<=m;i++){//查询 
		update_change(1,c[q[i].id],-INF);//把要更改的元素移除，利用c找到映射值，然后在值域线段树上修改为0 
		update_add(1,c[q[i].id]+1,cnt,1);//从该映射值往后到cnt的fi+1，因为这个值被移除了 
		int x=lower_bound(b+1,b+1+cnt,q[i])-b;//要修改成为哪个映射值
		c[q[i].id]=x;//把对应id的数修改为新的映射值 
		int y=query(1,x-1);//查找映射值前一位的排名
		update_change(1,x,q[i].id-y-1);//同上
		update_add(1,x+1,cnt,-1);//同上 
		cout<<tr[1].maxx<<'\n';
	}
	return 0;
}
```
# 写在后面
此题就我而言还是觉得是比较难的紫题了，主要难点是对 $f_i=i-g_i$ 的推导与推广，正如另一篇题解所说，**“对于这种求极值的题，我们可以不用盯着最优决策考虑，适当放宽条件，既可以保证取极值的正确性，又可以保证代码的码量较小，有点类似于不等式放缩。还是需要灵活地思维。”**

此外也需要对线段树的一定理解，推一手我线段树的复习总结博客：[线段树复习小结](https://www.luogu.com.cn/blog/wujingfey/xian-duan-shu-fu-xi-xiao-jie)。

码字不易，求过审，求点赞！

---

## 作者：_•́へ•́╬_ (赞：10)

## 思路

维护每个数之前的比他大的数的个数，全局最大值就是答案。

为啥呢？这些比他大的数都要到他右边去，一趟最多带一个过去，所以个数就是趟数。

考虑如何维护。

朴素维护是树套树。

使用性质：如果一个数，在他的右边有比他小的数，那么这个数之前的比他大的数的个数一定不是最大值。这样的数，我们就不必维护他的真实值，只要实际值比真实值小就行了。

然后大概有好几种做法。我参考了 loj 的[最短解](https://loj.ac/s/1358034)，他去掉了“之前”的限制，直接维护比每个数大的数的个数。如何维护呢？他用这个数的下标减去比这个数小的数的个数。

有个要注意的就是数字相同的时候，要认为左边的比右边小，离散化时可以做到。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#define N 500009
#define lc ((i)<<1|1)
#define rc ((i)+1<<1)
using namespace std;
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
int n,q,a[N],x[N],v[N],maxn[N<<3],lazy[N<<3];
long long lsh[N<<1],lsz;
inline void upd(int i,int l,int r,int ql,int qr,int x)
{
	if(qr<l||r<ql)return;
	if(ql<=l&&r<=qr){maxn[i]+=x;lazy[i]+=x;return;}
	int mid=l+r>>1;upd(lc,l,mid,ql,qr,x);upd(rc,mid+1,r,ql,qr,x);
	maxn[i]=max(maxn[lc],maxn[rc])+lazy[i];
}
main()
{
	read(n);read(q);
	for(int i=0;i<n;read(a[i]),lsh[lsz++]=a[i]*(long long)(n)+i,++i);
	for(int i=0;i<q;read(x[i]),read(v[i]),
		lsh[lsz++]=v[i]*(long long)(n)+x[i],++i);
	sort(lsh,lsh+lsz);lsz=unique(lsh,lsh+lsz)-lsh;
	for(int i=0;i<n;++i)
		a[i]=lower_bound(lsh,lsh+lsz,a[i]*(long long)(n)+i)-lsh;
	for(int i=0;i<q;++i)
		v[i]=lower_bound(lsh,lsh+lsz,v[i]*(long long)(n)+x[i])-lsh;
	for(int i=0;i<n;++i)
		upd(0,0,lsz-1,a[i],a[i],i),
		upd(0,0,lsz-1,a[i]+1,lsz-1,-1);
	for(int i=0;i<q;++i)
	{
		upd(0,0,lsz-1,a[x[i]],a[x[i]],-x[i]),
		upd(0,0,lsz-1,a[x[i]]+1,lsz-1,1);
		a[x[i]]=v[i];
		upd(0,0,lsz-1,v[i],v[i],x[i]),
		upd(0,0,lsz-1,v[i]+1,lsz-1,-1);
		printf("%d\n",maxn[0]);
	}
}
```

---

## 作者：Reunite (赞：6)

## 一
---
简单找规律可得，答案即为所有的前缀比这个数大的个数的最大值，因为假设 $i$ 之前有 $j$ 个位置的值都大于 $a_i$，那么最后这 $j$ 个值都得到 $i$ 的后面，但是每次只能带一个值跨过 $i$，所以答案是这样的。形式化的说，即求：

$$\max \limits_{i=1}^{n}{(\sum \limits_{j=1}^{i-1}[a_j >a_i])}$$

到了这里可以直接上树套树了，但是不好写，我们继续想一想，发现对于 $i<j,a_i>a_j$ 的任意二元组 $(i,j)$，$i$ 一定是劣于 $j$ 的。那么我们可以只考虑每种值最后出现的位置决策就行，因为这样是完全包含最优决策可能出现的位置的（即后缀最小值序列）。

有了上面的理论，我们可以认为，对于值 $c$ 最后一次在序列中出现的位置 $i$，序列中所有大于 $c$ 的值有 $x$ 个，对答案的贡献为：$x-(n-i)=(x+i)-n$。容易发现这肯定是对的，因为一定能取遍所有最优决策，理由同上。

现在就好做了，我们给值离散化，维护一个值域线段树和一个 $set$。线段树需要维护对于值 $c$，其大于 $c$ 的个数与序列中最后出现 $c$ 的下标和的最大值。只需要简单区间 $\pm1$，单点修改和全局查 $\max$ 的操作。$set$ 动态维护值在序列中出现的下标集合。剩下的看代码吧，没有细节。

### 总结：

对于这种求极值的题，我们可以不用盯着最优决策考虑，适当放宽条件，既可以保证取极值的正确性，又可以保证代码的码量较小。有点类似于不等式放缩，总之还得有较灵活的思维吧。
 
---
## 二
---

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

int n,m;
int a[500005];
int b[1000005];
int opx[500005];
int opy[500005];
int mx[4000005];
int tag[4000005];
set <int> st[1000005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void pushdown(int u){
	if(!tag[u]) return ;
	mx[u<<1]+=tag[u];
	mx[u<<1|1]+=tag[u];
	tag[u<<1]+=tag[u];
	tag[u<<1|1]+=tag[u];
	tag[u]=0;
	return ;
}

void updata(int u,int l,int r,int L,int R,int x){
	if(L>R) return ;
	if(L<=l&&r<=R){
		mx[u]+=x;
		tag[u]+=x;
		return ;
	}
	pushdown(u);
	int mid=(l+r)>>1;
	if(L<=mid) updata(u<<1,l,mid,L,R,x);
	if(R>mid) updata(u<<1|1,mid+1,r,L,R,x);
	mx[u]=max(mx[u<<1],mx[u<<1|1]);
	return ;
}

int main(){
	in(n),in(m);
	for(int i=1;i<=n;i++) in(a[i]),b[i]=a[i];
	int cnt=n;
	for(int i=1;i<=m;i++){
		in(opx[i]),in(opy[i]);
		opx[i]++;
		b[++cnt]=opy[i];
	}
	sort(b+1,b+1+cnt);
	cnt=unique(b+1,b+1+cnt)-b-1;
	for(int i=1;i<=cnt;i++) st[i].insert(0);
	for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+cnt,a[i])-b;
	for(int i=1;i<=m;i++) opy[i]=lower_bound(b+1,b+1+cnt,opy[i])-b;
	for(int i=1;i<=n;i++) updata(1,1,cnt,1,a[i]-1,1),st[a[i]].insert(i);
	set <int> :: iterator it,ti;
	for(int i=1;i<=n;i++){
		it=st[a[i]].find(i);
		it++;
		if(it==st[a[i]].end()) updata(1,1,cnt,a[i],a[i],i);
	}
	for(int i=1;i<=m;i++){
		updata(1,1,cnt,1,a[opx[i]]-1,-1);
		updata(1,1,cnt,1,opy[i]-1,1);
		it=st[a[opx[i]]].find(opx[i]);
		it++;
		if(it==st[a[opx[i]]].end()){
			it--;
			ti=it;
			ti--;
			updata(1,1,cnt,a[opx[i]],a[opx[i]],*ti-*it);
		}
		st[a[opx[i]]].erase(opx[i]);
		a[opx[i]]=opy[i];
		st[a[opx[i]]].insert(opx[i]);
		it=st[a[opx[i]]].find(opx[i]);
		it++;
		if(it==st[a[opx[i]]].end()){
			it--;
			ti=it;
			ti--;
			updata(1,1,cnt,a[opx[i]],a[opx[i]],*it-*ti);
		}
		printf("%d\n",mx[1]-n);
	} 
	
	return 0;
}

```

---

## 作者：xfrvq (赞：4)

已经完全不会了。

考虑冒泡排序会扫描一趟，说明有数还没到它该去的位置。那么扫描趟数就应该是 **一个数离它的目标位置的最远距离**。

$$\max_{i=1}^n\left(i-\sum_{j=1}^i[a_j\le a_i]\right)=\max_{i=1}^n\sum_{j=1}^i[a_j\gt a_i]$$

此时维护 $f_i=\sum_{j=1}^i[a_j\gt a_i]$ 的值，单点修改就变成数列区间，值域区间的二维修改，树套树 $O(n\log^2n)$，考虑优化。

设对于 $i$，有 $i\lt k$ 且 $a_i\ge a_k$，那么 $k$ 的答案比 $i$ 不劣，$i$ 没用了。**发现一个 $i$ 还有用，仅当 $\forall k\gt i,a_i\lt a_k$。**

考虑一个聪明的优化：**构造一个新式子，使得 $i$ 有用时，式子的结果就等于 $i$ 的正确值。$i$ 无用时，结果不优于 $i$ 的正确值。求 $\max$ 时这是正确的。**

容易构造：考虑 $\sum_{j}[a_j\gt a_i]$，当 $i$ 有用时等于 $f_i+(n-i)$，原因是 $i$ 有用时，$i+1,\cdots,n$ 都会被多算入答案。我们设 $g_i=\sum_j[a_j\gt a_i]-(n-i)$，在 $i$ 无用时 $g_i\lt f_i$，符合要求。

此时维护 $g_i$ 少了一维区间限制，上值域线段树即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5,S = N * 8;

int n,m,c,a[N],p[N],v[N];
tuple<int,int,int> b[N * 2];
int T[S],C[S],t[S];

#define lc (i << 1)
#define rc (lc | 1)
#define mid ((L + R) >> 1)
#define ls lc,L,mid
#define rs rc,mid + 1,R
#define _ int i = 1,int L = 1,int R = n + m
#define chg(i,x) T[i] += x,t[i] += x
#define psu(i) T[i] = max(T[lc],T[rc]),C[i] = C[lc] + C[rc]
#define psd(i) if(t[i]) chg(lc,t[i]),chg(rc,t[i]),t[i] = 0

void upd(int p,int x,_){
	if(L == R) return x ? (T[i] = x,C[i] = 1) : T[i] = C[i] = 0,void();
	psd(i); p <= mid ? upd(p,x,ls) : upd(p,x,rs); psu(i);
}

void add(int l,int r,int x,_){
	if(l > r) return;
	if(l <= L && R <= r) return chg(i,x),void();
	psd(i);
	if(l <= mid) add(l,r,x,ls);
	if(r > mid) add(l,r,x,rs);
	psu(i);
}

int qry(int l,int r,_,int s = 0){
	if(l > r) return 0;
	if(l <= L && R <= r) return C[i];
	if(l <= mid) s = qry(l,r,ls);
	if(r > mid) s += qry(l,r,rs);
	return s;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i) scanf("%d",a + i),b[i] = make_tuple(a[i],i,0);
	for(int i = 1;i <= m;++i) scanf("%d%d",p + i,v + i),b[i + n] = make_tuple(v[i],++p[i],i);
	sort(b + 1,b + n + m + 1);
	for(int i = 1,c = 0;i <= n + m;++i)
		if(!get<2>(b[i])) upd(i,get<1>(b[i]) + n - ++c),a[get<1>(b[i])] = i;
		else v[get<2>(b[i])] = i;
	for(int i = 1;i <= m;++i){
		if(a[p[i]] != v[i]){
			upd(a[p[i]],0);
			add(1,a[p[i]] - 1,-1);
			upd(v[i],qry(v[i] + 1,n + m) + p[i]);
			add(1,v[i] - 1,1);
			a[p[i]] = v[i];
		}
		printf("%d\n",T[1] - n);
	}
	return 0;
}
```

---

## 作者：CQ_Bab (赞：2)

# 思路
通过观察可以发现答案为每一个数能与之前的数能形成的逆序对数量的最大值，所以考虑维护每一个数逆序对的数量，然后再观察可以发现一个数能组成的逆序对数量为 $val_i=i-\sum_{j=1}^{i}(a_j\leq a_i)$ 并且我们可以发现如果一个数能组成的逆序对数量最多那么它后面一定每一任何一个数小于等于它，因为如果存在 $a_j\leq a_i,j>i$ 那么一定有 $\sum (a_x\leq a_i)\geq \sum(a_x\leq a_j)$ 又由于 $j>i$ 所以 $val_i<val_j$。

有了此结论就可以考虑用一颗权值线段树维护 $a_i=x$ 中 $val_i$ 最大的那一个，我们可以发现柿子为 $\max(id_x)-\sum(a_i\leq x)$ 所以我们考虑用一个 set 来维护每一个数出现的最后的位置，每次加入一个数 $x$ 就将 $x\sim Max$ 都减一然后将当前的最大的下标更新，而删除时就是反过来而已。

但是有人会发现一个问题如果 $x\sim Max$ 中有一个数并未在 $i$ 之后出现过但是也将它减了一不会出问题吗？答案是不会的，因为有了上面的结论可以知道如果 $x\sim Max$ 中有一个数并未在 $i$ 之后出现过就一定不可能是最大值，所以对我们的最大值取值并无影响，知道我们将 $i$ 删除时又会将 $x\sim Max$ 加一便可以抵消掉之前不该减的从而又成为正确答案了。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
const int N=1e6+10;
int n,q;
int a[N];
struct node{
	int l,r;
	int Max,tag;
}tr[N<<2];
void up(int x) {
	tr[x].Max=max(tr[x<<1].Max,tr[x<<1|1].Max);
}
void down(int x) {
	if(tr[x].tag) {
		tr[x<<1].tag+=tr[x].tag;
		tr[x<<1|1].tag+=tr[x].tag;
		tr[x<<1|1].Max+=tr[x].tag;
		tr[x<<1].Max+=tr[x].tag;
		tr[x].tag=false;
	}
}
void build(int u,int l,int r) {
	tr[u]={l,r};
	if(l==r) return ;
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
}
void modify(int u,int l,int r,int k) {
	if(tr[u].l>=l&&tr[u].r<=r) {
		tr[u].Max+=k;
		tr[u].tag+=k;
		return ;
	}
	int mid=tr[u].l+tr[u].r>>1;
	down(u);
	if(mid>=l) modify(u<<1,l,r,k);
	if(mid<r) modify(u<<1|1,l,r,k);
	up(u);
}
int m;
set<int>s[N];
int v[N],idx;
void add(int val,int x) {//加入
	modify(1,x,m,-1);
	if(s[x].size()) modify(1,x,x,-*s[x].rbegin());
	s[x].insert(val);
	modify(1,x,x,*s[x].rbegin());
}
void del(int val,int x) {//删除
	modify(1,x,m,1);
	if(s[x].size()) modify(1,x,x,-*s[x].rbegin());
	s[x].erase(val);
	if(s[x].size()) modify(1,x,x,*s[x].rbegin());
}
vector<pair<int,int>>ss;
void solve() {
	in(n),in(q);
	rep(i,1,n) in(a[i]),v[++idx]=a[i];
	rep(i,1,q) {
		int x,k;
		in(x),in(k);
		x++;
		ss.pb({x,k});
		v[++idx]=k;
	}
	sort(v+1,v+1+idx);
	m=unique(v+1,v+1+idx)-v-1;
	rep(i,1,n) a[i]=lower_bound(v+1,v+1+m,a[i])-v;
	vector<pair<int,int>>kk;
	for(auto to:ss) kk.pb({to.first,lower_bound(v+1,v+1+m,to.second)-v});
	build(1,1,m);
	rep(i,1,n) add(i,a[i]);
	for(auto to:kk) {
		del(to.first,a[to.first]);
		a[to.first]=to.second;
		add(to.first,a[to.first]);
		printf("%lld\n",tr[1].Max);
	}
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：Sky_Maths (赞：2)

# 正文

**首先，我们先要得到一个结论。**

$$ans=\max\limits_{i=1}^{n} (\sum\limits_{j=1}^{i-1}[a_j>a_i])$$

根据冒泡排序，每轮对于每个前面有 $a_j>a_i$ 的 $i$，它都会往前一位，需要往前次数的最大值就是答案。

**考虑如何求这个值。**

可以先将序列映射到一个二维平面上，坐标为 $(i,A_i)$。对于每个 $i,A_i$，往前次数就是它的左上角的点的个数。可以用树套树维护最大值和区间加法。

但是我们换一个做法。

**考虑哪些点可能会贡献答案。**

右下角没有点的点。我们称其为后缀 $\min$ 点，即右边的所有点的 $A_j>A_i$。

现在再考虑将所有的点值都映射到一个 $1\sim n$ 的排列 $p$ 上。

对于后缀 $\min$ 点，左上角的点的个数为 $(n-p_i)-(n-i)=i-p_i$ 即上方的点的个数减去右上方点的个数。

对于非后缀 $\min$ 点，因为其不会贡献答案，我们只需要它的贡献不大于实际贡献即可，而上方点的个数不会变，但右上方，因为右边并不全都在它的上方，所以会偏大，而总的应该偏小。

**再考虑如何维护这个值。**

先将所有出现过的 $A_i$（包括询问和原来）离线下来离散化。

先考虑维护序列中的，可以开一棵线段树，当一个点（从左往右）加入时，它的 $i$ 已知，而 $1\sim p_i-1$ 上存在的个数就是当前序列中小于 $i$ 点的个数，可以线段树查询区间和。

加入当前点就是在 $p_i$ 上插入 $i-p_i$ 的值。

接下来考虑“动态”维护 $i-p_i$，当新加入一个点的时候，它在线段树上所有右边的点 $p_i+=1$，即 $(i-p_i)-=1$，若原本在序列上在该点的左边，一定不是后缀 $\min$ 点，多减不用考虑。

但还有删点，因为改变点值等价于删原来的点并加入一个新点。删点即消去它的贡献，将后面的全部 $-1$ 即可。

我记得**还有一个正确性证明**的，~~容我先咕着~~，作为课后练习（有时间补上，也可私信提醒我）。

## 关于正确性
对于每个点都视为后缀 $\min$ 后，非该类型的点的答案只会偏小不会偏大，该类型的是不会偏大或偏小的，且是求 $\max$，故可以维护，然后贡献相当于每个点刚进入时被前面所有贡献 $-1$，贡献给后面 $-1$，离开时撤回贡献，故贡献是可维护的。

# 代码
借鉴 @IntrepidStrayer 的，但是学校 OJ 上的。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i(l),i##end(r);i<=i##end;++i)
#define per(i,r,l) for(int i(r),i##end(l);i>=i##end;--i)
using namespace std;
namespace IntrepidStrayer {

#define gc getchar
#define mp make_pair
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define pb push_back
#define eb emplace_back
#define ci const int

using ll = long long;
using db = double;
using pii = pair<int,int>;

void read(int &res) {
	res=0; char ch=gc(); bool f=0;
	while((ch<'0'||ch>'9') && ch!='-') ch=gc();
	if(ch=='-') f=1,ch=gc();
	while(ch<='9'&&ch>='0') res=res*10+ch-'0',ch=gc();
	if(f) res=-res;
}

ci N = 1e6 + 9;
ci M = N << 2;
ci inf = 1e9;

struct SGT {
	#define lc u<<1
	#define rc u<<1|1
	int mx[M],cnt[M],tag[M];
	void add(int u,int x) {
		mx[u]+=x;
		tag[u]+=x;
	}
	void pushdown(int u) {
		if(tag[u]) {
			add(lc,tag[u]);
			add(rc,tag[u]);
			tag[u]=0;
		}
	}
	void upd(int u) {
		mx[u]=max(mx[lc],mx[rc]);
		cnt[u]=cnt[lc]+cnt[rc];
	}
	void modify(int u, int l, int r, int a, int b,int x) {
		if(a<=l && r<=b) {
			add(u,x);
			return;
		}
		int mid = l + r >> 1;
		pushdown(u);
		if(a<=mid) modify(lc,l,mid,a,b,x);
		if(mid<b) modify(rc,mid+1,r,a,b,x);
		upd(u);
	}
	int query(int u,int l,int r,int a,int b) {
		if(a>b) return 0;
		if(a<=l&&r<=b) {
			return cnt[u];
		}
		int mid=(l+r)>>1,res=0;
		pushdown(u);
		if(a<=mid) res+=query(lc,l,mid,a,b);
		if(mid<b) res+=query(rc,mid+1,r,a,b);
		return res;
	}
	void insert(int u,int l,int r,int i,int x,int y) {
		if(l==r) {
			mx[u] = x;
			cnt[u] = y;
			return;
		}
		pushdown(u);
		int mid = (l+r)>>1;
		if(i<=mid) insert(lc,l,mid,i,x,y);
		else insert(rc,mid+1,r,i,x,y);
		upd(u);
	}
} tree;

int n,q,m;
int a[N];
pii Q[N],b[N];

int rnk(pii p) {
	return lb(b+1,b+m+1,p) - b;
}

void ins(int i) {
	int t = rnk(mp(a[i],i));
	tree.insert(1,1,m,t,i-(tree.query(1,1,m,1,t-1)+1),1);
	if(t < m) tree.modify(1,1,m,t+1,m,-1);
}

void ers(int i) {
	int t = rnk(mp(a[i],i));
	tree.insert(1,1,m,t,-inf,0);
	if(t<m) tree.modify(1,1,m,t+1,m,1);
}

void solve() {
	read(n); read(q);
	rep(i,1,n) {
		read(a[i]);
		b[i]=mp(a[i],i);
	}
	m=n;
	rep(i,1,q) {
		read(Q[i].fi); ++Q[i].fi; read(Q[i].se);
		b[++m] = mp(Q[i].se,Q[i].fi);
	}
	sort(b+1,b+m+1);
	m=unique(b+1,b+m+1)-b-1;
	tree.modify(1,1,m,1,m,-1e9);
	rep(i,1,n) ins(i);
	rep(i,1,q) {
		ers(Q[i].fi);
		a[Q[i].fi] = Q[i].se;
		ins(Q[i].fi);
		printf("%d\n",tree.mx[1]);
	}
}

}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	IntrepidStrayer::solve();
	return 0;
}

```

---

## 作者：jamesharden666 (赞：1)

观察一下即可发现，每次冒泡排序都会使一个数前面比它大的数的个数减一，那么一个序列的冒泡排序扫描趟数即为 $\max \limits_{i=1}^{n} f_i=\sum \limits_{j=1}^{j=i}[a[j]>a[i]]$ 。

考虑这个式子不好直接维护，于是我们可以去观察一下性质。

观察一下发现： $a_i=a_j$ 且 $i<j$ 时， $f_i \leq f_j$ ； $a_i > a_j$ 且 $i<j$ 时， $f_i \leq f_j$ 。

第一条式子给我们的启发就是：对于同一个 $a_i$ 我们只用维护它最后的出现位置即可。

第二条式子给了我们一个放缩的机会，这里先不解释，往下看你就懂了。

我们设 $g_i=s_i-(n-i)$ ，其中 $s_i$ 为整个序列中比 $a_i$ 大的元素个数。

如果 $i$ 后面没有比 $a_i$ 大的，那么这条式子就与 $f_i$ 等价；那如果有呢？

如果有就满足 $g_i < f_i \leq f_j$ ，也就是说它不影响正确答案的取值。

这就是放缩的精妙之处，利用 $max$ 的性质，将一个难以维护的式子换成一个简单的式子，虽然不保证每个值都是准确的，但保证了最终答案的正确性。

对于 $g_i$ 用值域线段树维护即可，懒标记用标记永久化处理，每个颜色最后的出现位置用 $set$ 维护即可。

最终时间复杂度为 $\mathcal O(n \log n)$ 。

代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m,a[N],b[N],t[N<<2],lz[N<<2],tot=0;
set<int> s[N];
struct node
{
    int pos,val;
}q[N];
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
        s=s*10+(ch-'0'),ch=getchar();
    return s*w;
}
void update(int root,int L,int R,int l,int r,int val)
{
    if(L>=l&&R<=r)
    {
        t[root]+=val;
        lz[root]+=val;
        return ;
    }
    if(R<l||L>r)
        return ;
    int mid=(L+R)>>1;
    update(root<<1,L,mid,l,r,val);
    update(root<<1|1,mid+1,R,l,r,val);
    t[root]=max(t[root<<1],t[root<<1|1])+lz[root];
}
void add(int val,int pos)
{
    if(!s[val].empty())
        update(1,1,tot,val,val,-(*s[val].rbegin()));
    if(val>1)
        update(1,1,tot,1,val-1,1);
    s[val].insert(pos);
    update(1,1,tot,val,val,*s[val].rbegin());
}
void del(int val,int pos)
{
    update(1,1,tot,val,val,-(*s[val].rbegin()));
    if(val>1)
        update(1,1,tot,1,val-1,-1);
    s[val].erase(pos);
    if(!s[val].empty())
        update(1,1,tot,val,val,*s[val].rbegin());
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i)
        a[i]=read(),b[++tot]=a[i];
    for(int i=1;i<=m;++i)
        q[i]=(node){read()+1,read()},b[++tot]=q[i].val;
    sort(b+1,b+tot+1);
    tot=unique(b+1,b+tot+1)-b-1;
    for(int i=1;i<=n;++i)
        a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
    for(int i=1;i<=m;++i)
        q[i].val=lower_bound(b+1,b+tot+1,q[i].val)-b;
    for(int i=1;i<=n;++i)
        add(a[i],i);
    for(int i=1;i<=m;++i)
    {
        del(a[q[i].pos],q[i].pos);
        a[q[i].pos]=q[i].val;
        add(a[q[i].pos],q[i].pos);
        printf("%d\n",t[1]-n);
    }
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

这种题能在模拟赛中被出 $2$ 遍？

考虑一次扫描，就是把一个数前面一个恰好比其大的数弄到它后面。记 $c_i$ 为 $i$ 前面比它大的数，答案就是 $\max c_i$。

如果没有相同的数字，就可以看全局有几个比 $a_i$ 大的。于是可以维护一个二元组 $(a_i,i)$，就变成维护一个位置的贡献是全局有多少个值比他大。这个可以用线段树简单维护。

复杂度是 $\mathcal{O}(n\log n)$。

因为第一次遇到这个题的时候题目名字是 sequence，所以没有删掉 freopen。

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fir first
#define sec second
#define mid (l + r >> 1)
#define ls (p << 1)
#define rs (p << 1 | 1)
using namespace std;
const int N = 5e5 + 5, inf = 0x3f3f3f3f;
bool f1;
int n, q, tot, tag[N << 3], maxn[N << 3], x;
pii aa[N << 1], opt[N], a[N];
bool f2;
inline void addtag(int p, int v){
    tag[p] += v, maxn[p] += v;
}
inline void modify(int p, int l, int r, int x, int y, int v){
    if(x <= l && r <= y){
        addtag(p, v);
        return ;
    }
    if(mid >= x) modify(ls, l, mid, x, y, v);
    if(mid < y) modify(rs, mid + 1, r, x, y, v);
    maxn[p] = max(maxn[ls], maxn[rs]) + tag[p];
}
inline void build(int p, int l, int r){
    maxn[p] = -inf;
    if(l == r){
        return ;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
}
inline void upd(int p, int l, int r, int x, int v){
    if(l == r){
        maxn[p] = v + tag[p];
        return ;
    }
    if(mid >= x) upd(ls, l, mid, x, v);
    else upd(rs, mid + 1, r, x, v);
    maxn[p] = max(maxn[ls], maxn[rs]) + tag[p];
}
inline void gettim(){
    cerr << clock() * 1000 / CLOCKS_PER_SEC << "ms\n";
}
inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while('0' <= c && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
}
int main(){
    // printf("%.2lfMB\n", (&f2 - &f1) / 1024.0 / 1024.0);
    // freopen("sequence.in", "r", stdin);
    // freopen("sequence.out", "w", stdout);
    read(n), read(q);
    for(int i = 1; i <= n; i++){
        read(a[i].fir);
        a[i].sec = i;
        aa[++tot] = a[i];
    }
    for(int i = 1; i <= q; i++){
        read(opt[i].sec), read(opt[i].fir);
        opt[i].sec++;
        aa[++tot] = opt[i];
    }
    sort(aa + 1, aa + tot + 1);
    tot = unique(aa + 1, aa + tot + 1) - aa - 1;
    for(int i = 1; i <= n; i++) a[i].fir = lower_bound(aa + 1, aa + tot + 1, a[i]) - aa;
    for(int i = 1; i <= q; i++) opt[i].fir = lower_bound(aa + 1, aa + tot + 1, opt[i]) - aa;
    build(1, 1, tot);
    for(int i = 1; i <= n; i++){
        upd(1, 1, tot, a[i].fir, i);
        modify(1, 1, tot, a[i].fir, tot, -1);
    }
    for(int i = 1; i <= q; i++){
        x = opt[i].sec;
        if(a[x] == opt[i]){
            printf("%d\n", maxn[1]);
            continue ;
        }
        if(a[x].fir < opt[i].fir) modify(1, 1, tot, a[x].fir, opt[i].fir - 1, 1);
        if(a[x].fir > opt[i].fir) modify(1, 1, tot, opt[i].fir, a[x].fir - 1, -1);
        upd(1, 1, tot, a[x].fir, -inf);
        // modify(1, 1, tot, a[x].fir, tot, 1);
        a[x] = opt[i];
        // modify(1, 1, tot, a[x].fir, tot, -1);
        upd(1, 1, tot, a[x].fir, x);
        printf("%d\n", maxn[1]);
    }
    // gettim();
    return 0;
}
```

---

