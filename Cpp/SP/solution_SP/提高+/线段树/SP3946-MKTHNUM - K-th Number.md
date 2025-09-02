# MKTHNUM - K-th Number

## 题目描述

题目大意：

给你 $n$ 个数，多次询问某段区间中第 $k$ 小的数。

## 说明/提示

$1\le n \le 100000$ , $1 \le m \le 5000$ , $-10^9 \le a_i \le 10^9$。

~~注意：简单的做法可是过不了的。~~

 感谢 @gjc1124646822  提供的翻译。
 
 Fixed by @AnEasySong

# 题解

## 作者：Acestar (赞：15)

题意应该都知道吧，就是查询区间第 $k$ 小。

这里介绍一下**整体二分**：

- 所谓整体二分，需要数据结构题满足以下性质:

  1.询问的答案具有可二分性。

  2.修改对判定答案的贡献相对独立，修改之间互不影响效果。

  3.修改如果对判定答案有贡献，则贡献为一确定的与判定标准无关的值。

  4.贡献满足交换律，结合律，具有可加性。

  5.题目允许离线操作。
- 询问的答案有可二分性质显然是前提，我们发现，因为修改对判定标准的贡献相对独立，且贡献的值(如果有的话)与判定标准无关，所以如果我们已经计算过某一个些修改对询问的贡献，那么这个贡献永远不会改变，我们没有必要当判定标准改变时再次计算这部分修改的贡献，只要记录下当前的总贡献，再进一步二分时，直接加上新的贡献即可。
- 这样的话，我们发现，处理的复杂度可以不再与序列总长度直接相关了，而可能只与当前待处理序列的长度相关。




接下来考虑本题。

对于单个查询而言，我们可以采用预处理+二分答案的方法解决，但现在我们要回答的是一系列的查询，对于查询而言我们都要重新预处理然后二分，时间复杂度无法承受，但是我们仍然希望通过二分答案的思想来解决，整体二分就是基于这样一种想法，我们将所有操作(包括修改和查询)一起二分，进行分治。

我们时刻维护一个操作序列和对应的可能答案区间 $[L,R]$，我们先求的一个判定答案 $mid=(L+R)>>1$，然后我们考虑操作序列的修改操作，将其中符合条件的修改对各个询问的贡献统计出来，然后我们对操作序列进行划分。


先用一个结构体数组存下所有输入。

```cpp
struct node
{
	int x,y,k,type,id;
	//修改中 x:数值, type:操作类型(1), id:在数组中的位置
	//查询中 x,y,k:输入, type:操作类型(2), id:询问编号 
};

node q[N+M],q1[N+M],q2[N+M];	//q:当前二分区间的操作, q1:当前二分区间的左区间的操作, q2:右区间的操作

int t1,t2;	//t1:q1长度, t2:q2长度
```

$[ql,qr]$ 表示操作区间，$[L,R]$表示答案区间。

如果 $L=R$ 就说明找到答案了，将 $[ql,qr]$ 中所有查询操作的答案赋为 $L$。

```cpp
if(L==R)	//找到答案了 
{
	for(int i=ql; i<=qr; i++)
		if(q[i].type==2)
			ans[q[i].id]=L;
	return;
}
```



第一类操作是修改，也就是输入的 $n$ 个数。

这里用**树状数组**维护，最普通的吧，维护比一个数小的数的个数。


```cpp
int c[N];

int lowbit(int t)
{
	return t&(-t);
}

void add(int x,int y)
{
	for(int i=x; i<=n; i+=lowbit(i))
		c[i]+=y;
}

int getsum(int x)
{
	int res=0;
	for(int i=x; i>0; i-=lowbit(i))
		res+=c[i];
	return res;
}
```

但是并不是直接全都 $add$ 进去。在二分的时候，如果 $q[i].x<=mid$，也就是会影响第 $k$ 小的值，就 $add(q[i].id,1)$，并将这个操作存进 $q1$，因为在左区间也会用到，否则直接存进 $q2$，因为在右区间可能会用到。

```cpp
if(q[i].type==1)
{
	if(q[i].x<=mid)
	{
		add(q[i].id,1);
		q1[++t1]=q[i];
	}
	else
	{
		q2[++t2]=q[i];
	}
}
```


第二类操作是查询。

如果当前累计贡献 $cnt$ 比要求贡献大，也就是数的个数大于 $k$，说明 $mid$ 过大，满足标准的修改过多，我们需要给这个查询设置更小的答案区间，于是二分到答案区间 $[L,mid]$，否则二分到区间 $[mid+1,R]$，并将查询第 $k$ 小改为查询第 $k-cnt$ 小。

```cpp
else	//if(q[i].type==2) 
{
	int cnt=getsum(q[i].y)-getsum(q[i].x-1);
	if(cnt>=q[i].k)
	{
		q1[++t1]=q[i];
	}
	else
	{
		q[i].k-=cnt;
		q2[++t2]=q[i];
	}
}
```

最后把 $q1$ 和 $q2$ 再存回 $q$，进行二分就可以了。注意要把树状数组清空。

```cpp
for(int i=1; i<=t1; i++)
	if(q1[i].type==1) add(q1[i].id,-1);
for(int i=1; i<=t1; i++)
	q[ql+i-1]=q1[i];
for(int i=1; i<=t2; i++)
	q[ql+t1+i-1]=q2[i];
solve(ql,ql+t1-1,L,mid);
solve(ql+t1,qr,mid+1,R);
```

## Code

```cpp
#include<iostream>
#include<cstdio>
#define INF 1e9
using namespace std;

const int N=1e5+10;
const int M=5e3+10;

struct node
{
	int x,y,k,type,id;
	//修改中 x:数值, type:操作类型(1), id:在数组中的位置
	//查询中 x,y,k:输入, type:操作类型(2), id:询问编号 
};
int n,m,tot;	//tot:操作个数 
int ans[N],c[N];
node q[N+M],q1[N+M],q2[N+M];	//q:当前二分区间的操作, q1:当前二分区间的左区间的操作, q2:右区间的操作 

int lowbit(int t)
{
	return t&(-t);
}

void add(int x,int y)
{
	for(int i=x; i<=n; i+=lowbit(i))
		c[i]+=y;
}

int getsum(int x)
{
	int res=0;
	for(int i=x; i>0; i-=lowbit(i))
		res+=c[i];
	return res;
}

void solve(int ql,int qr,int L,int R)	//ql,qr:操作区间; L,R:答案区间 
{
	if(ql>qr) return;
	if(L==R)	//找到答案了 
	{
		for(int i=ql; i<=qr; i++)
			if(q[i].type==2)
				ans[q[i].id]=L;
		return;
	}
	int mid=(L+R)>>1,t1=0,t2=0;
	for(int i=ql; i<=qr; i++)
	{
		if(q[i].type==1)
		{
			if(q[i].x<=mid)
			{
				add(q[i].id,1);
				q1[++t1]=q[i];
			}
			else
			{
				q2[++t2]=q[i];
			}
		}
		else	//if(q[i].type==2) 
		{
			int cnt=getsum(q[i].y)-getsum(q[i].x-1);
			if(cnt>=q[i].k)
			{
				q1[++t1]=q[i];
			}
			else
			{
				q[i].k-=cnt;
				q2[++t2]=q[i];
			}
		}
	}
	for(int i=1; i<=t1; i++)
		if(q1[i].type==1) add(q1[i].id,-1);
	for(int i=1; i<=t1; i++)
		q[ql+i-1]=q1[i];
	for(int i=1; i<=t2; i++)
		q[ql+t1+i-1]=q2[i];
	solve(ql,ql+t1-1,L,mid);
	solve(ql+t1,qr,mid+1,R);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)
	{
		int x;
		scanf("%d",&x);
		tot++;
		q[tot].x=x,q[tot].type=1,q[tot].id=i;
	}
	for(int i=1; i<=m; i++)
	{
		int x,y,k;
		scanf("%d%d%d",&x,&y,&k);
		tot++;
		q[tot].x=x,q[tot].y=y,q[tot].k=k,q[tot].type=2,q[tot].id=i;
	}
	solve(1,tot,-INF,INF);
	for(int i=1; i<=m; i++)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：Gary818 (赞：14)

# [「SP3946」K-th Number](https://www.luogu.org/problem/SP3946)    
从线段树基础一路肝到主席树  
### **主席树**（以下部分摘自《算法竞赛》）    
又称**可持久化线段树** ，**函数式线段树** 由于创造者名字缩写是HJT，与我们敬爱的前国家主席名字缩写相同，于是我们尊称它为**主席树** ，是最重要的可持久化数据结构之一。   
主要思想就是保存多个历史版本的线段树，但是我们没有那么多的空间去保存每一次修改，所以我们采用只合并、添加一条链的方式来保存每个版本。因此，主席树不再是一棵完全二叉树，所以我们就不能再用层次序编号（k<<1和k<<1|1）而是直接改用记录每个节点的左右儿子。因为每次修改都会创建$ O(logN) $个新节点，所以我们主席树的**空间复杂度** 是$ O(N+M logN) $，为了节省空间，我们不再记录每个节点带表的区间[l,r]，而是作为递归参数传递。  

上面没看懂没关系，直接看题吧   
**问题概述** ：给定序列，查询l～r区间第k小值    
**思路** ：因为考虑到a[i]值域很大，所以首先就要离散化。假设离散化之后a[i]的值$ b[a[i]] \in[1,T] $ 线段树上的每个节点上保存一个变量sum，用来保存[L,R]区间中一共插入过多少个数，初始值为0。  
**细节** ：对于每个a[i]，在对b[a[i]]进行单点修改时，sum+=1，线段树每个每个内部节点sum值等于左右子树sum之和。因此，以“root[i]为根的线段树”的值域区间[L,R]就保存了A的前i个数有多少个落在值域[L,R]内。（这段话好好理解一下）    
接下来考虑每次询问的[l,r,k]，有一条重要的性质：**以root[l]和root[r]为根的两棵线段树对值域划分是完全相同的。**（没看懂不要紧）换句话说，**除了sum值不同，两棵线段树的内部结构和每个节点代表的值域区间完全对应**。由此，~~我们得到一句大家能看懂的话~~,root[r]的值域区间[L,R]的sum值减去root[l-1]的值域区间[L,R]的sum值，就是a[l~r]有多少个数落在值域[L,R]中。  
那似乎这个题就讲完了QwQ  
看看代码，我的代码是借鉴的题解区某为dalao的（里面有注释  
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn=200010;

int tot,n,m;
int sum[maxn<<5],rt[maxn<<5],ls[maxn<<5],rs[maxn<<5];//题解sum，根，左节点，右节点
int a[maxn],b[maxn];//a是原数组，b是离散化数组
int p;//修改点

inline void build(int &k,int l,int r){//建树
    k=++tot;//动态开点
    if(l==r) return;
    int mid=(l+r)>>1;
    build(ls[k],l,mid);
    build(rs[k],mid+1,r);
}

inline int change(int k,int l,int r){//确定左儿子、右儿子，更新sum值
    int oo=++tot;
    ls[oo]=ls[k];
    rs[oo]=rs[k];
    sum[oo]=sum[k]+1;
    if(l==r) return oo;
    int mid=(l+r)>>1;
    if(p<=mid) ls[oo]=change(ls[oo],l,mid);
    else rs[oo]=change(rs[oo],mid+1,r);
    return oo;
}

inline int query(int u,int v,int l,int r,int k){
    int ans,mid=((l+r)>>1),x=sum[ls[v]]-sum[ls[u]];
    if(l==r) return l;
    if(x>=k) ans=query(ls[u],ls[v],l,mid,k);
    else ans=query(rs[u],rs[v],mid+1,r,k-x);
    return ans;
}

signed main(){
    int l,r,k,q,ans;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
    sort(b+1,b+1+n);//排序
    q=unique(b+1,b+1+n)-b-1;//去重
    build(rt[0],1,q);
    for(int i=1;i<=n;i++){
        p=lower_bound(b+1,b+1+q,a[i])-b;//可以视为查找最小下标的匹配值
        rt[i]=change(rt[i-1],1,q);
    }
    while(m--){
        cin>>l>>r>>k;
        ans=query(rt[l-1],rt[r],1,q,k);
        cout<<b[ans]<<endl;
    }
    return 0;
}
```  
结束了～～～

---

## 作者：_WMD (赞：5)

这道题可以用主席树或可持久化线段树，但我作为一个蒟蒻肯定是不会的。
我就来个整体分治的题解吧。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MM(a) memset(a,0,sizeof(a))
using namespace std;
const int inf=0x3f3f3f3f;
int n,m,c[100010],ans[5010],t;
struct node
{
	int op,x,y,z; 
}q[160020],lq[160020],rq[160020];
inline int lowbit(int x)
{
	return x&-x;
}
int ask(int x)
{
	int y=0;if(!x)return 0;
	for(;x;x-=lowbit(x))y+=c[x];
	return y;
}
int change(int x,int y)
{
	for(;x<=n;x+=lowbit(x))c[x]+=y;
}
void solve(int l,int r,int lval,int rval)
{
	if(l>r)return;
	if(lval==rval)
	{
		for(int i=l;i<=r;i++)if(q[i].op)ans[q[i].op]=lval;return;
	}
	int mid=(lval+rval)>>1;
	int lt=0,rt=0;
	for(int i=l;i<=r;i++)
	{
		if(q[i].op==0)
		{
			if(q[i].y<=mid)change(q[i].x,1),lq[++lt]=q[i];
			else rq[++rt]=q[i];
		}
		else 
		{
			int cnt=ask(q[i].y)-ask(q[i].x-1);
			if(cnt>=q[i].z)lq[++lt]=q[i];
			else rq[++rt]=q[i],rq[rt].z-=cnt;
		}
	}
	for(int i=l;i<=r;i++)if(q[i].op==0&&q[i].y<=mid)change(q[i].x,-1);
	for(int i=1;i<=lt;i++)q[l+i-1]=lq[i];
	for(int i=1;i<=rt;i++)q[l+i+lt-1]=rq[i];
	solve(l,l+lt-1,lval,mid);solve(l+lt,r,mid+1,rval);
}
int main()
{
//	freopen("in.txt","r",stdin);
	cin>>n>>m;t=n+m;
	for(int i=1;i<=n;i++)scanf("%d",&q[i].y),q[i].op=0,q[i].x=i;
	for(int i=1;i<=m;i++)scanf("%d%d%d",&q[i+n].x,&q[i+n].y,&q[i+n].z),q[i+n].op=i;
	solve(1,t,-inf,inf);
	for(int i=1;i<=m;i++)cout<<ans[i]<<endl;
	return 0;
} 
```

---

## 作者：xixike (赞：4)

# 分块做法

看到题解区里没有分块的题解，我就来补一发qwq。

首先我们把原数组从小到大排序并存到$num$数组里，对$num$数组进行二分查找，每次算出一个$mid$，并找出有多少个小于等于$num[mid]$的数，记为$cnt$，判断如果$cnt>=k$,则$r=mid$,反之则$l=mid$。
```cpp
	int zuo=-1,you=n-1;
	while(you-zuo>1){
		//...计算cnt
		if(cnt>=k) you=mid;
		else zuo=mid;
	}

```
这里，$zuo=-1$是因为我用到了第0位。

那我们如何计算$cnt$呢？

我们考虑对于每一个块进行一次从小到大的排序，暴力计算出两头的（即不在整块内）的小于等于$num[mid]$的数的个数加到$cnt$中，然后对于每一个整块利用upper_bound();函数，求出每一个块中第一个大于$num[mid]$的数的位置为$tmp$，然后用$cnt+tmp-l[b]$即可。
```cpp
	while(you-zuo>1){
		cnt=0;
		int mid=(zuo+you)>>1;
		l=tmpl;
		r=tmpr;
		while(l<r&&l%B!=0)//暴力计算最左边的
			if(a[l++]<=num[mid]) cnt++;
		while(l<r&&r%B!=0)//暴力计算最右边的
			if(a[--r]<=num[mid]) cnt++;
		while(l<r){//b为每一个块，tmp为二分后的结果
			int b=l/B;
			int tmp=upper_bound(bucket[b].begin(),bucket[b].end(),num[mid])-bucket[b].begin();
			cnt+=tmp;
			l+=B;
		}
		if(cnt>=k) you=mid;
		else zuo=mid;
	}

```
**附完整代码**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define N 100010
#define B 1024

using namespace std;

vector <int> bucket[B];
int a[N],num[N];
int n,m,l,r,k,cnt;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		num[i]=a[i];
		bucket[i/B].push_back(a[i]); 
	}
	sort(num,num+n);//第一个二分数组
	for(int i=0;i<n/B;i++)
		sort(bucket[i].begin(),bucket[i].end());//把每一个块都从小到大排序
	while(m--){
		int tmpl,tmpr;
		scanf("%d%d%d",&tmpl,&tmpr,&k);
		tmpl--;//由于输入是从1开始，所以要减一,后面r是先减一所以tmpr不用减
		int zuo=-1,you=n-1;
		while(you-zuo>1){
			cnt=0;
			int mid=(zuo+you)>>1;
			l=tmpl;
			r=tmpr;
			while(l<r&&l%B!=0)
				if(a[l++]<=num[mid]) cnt++;
			while(l<r&&r%B!=0)
				if(a[--r]<=num[mid]) cnt++;
			while(l<r){
				int b=l/B;
				int tmp=upper_bound(bucket[b].begin(),bucket[b].end(),num[mid])-bucket[b].begin();
				cnt+=tmp;
				l+=B;
			}
			if(cnt>=k) you=mid;
			else zuo=mid;
		}
		printf("%d\n",num[you]);//最后输出我们找到的那个数就好啦
	}
	return 0;
}
```


---

## 作者：SymphonyOfEuler (赞：3)

这道题让我们求一个数列的区间$[l,r]$中第K小的数。并且翻译人还很良心，说了 “~~注意：简单的做法可是过不了的。~~”。但是这个不看也知道，应该用可持久化线段树（主席树）。

## **主席树分析：**

**主席树是什么？**

主席树就是利用函数式编程的思想来使线段树支持询问历史（之前所有）版本、同时利用它们之间的共同数据来减少时间和空间消耗的增强版的线段树，复杂度$O(nlogn)$。 

为了展示线段树和主席树的区别，我举一个形象的例子：你今天在线洛谷连着3小时，你一开始有5个粉丝。第一小时，你增加了一个粉丝。第二小时你增加了两个粉丝。第三个小时你掉了一个粉丝。线段树情况下你会直接改掉值。


线段树可以更新你的粉丝数量，但是怎么求出你以前的记录呢？我们设一个$t$，当t=0，是初始状态，t=1的时候，是第一小时粉丝情况，以此类推。这样，每个$t$，都存一个线段树。每当需要操作的时候，我们把改的结果存在这个元素对应的下一个$t$的位置。

总的来说，主席树就是很多个线段树，但是又很快。

这就是主席树的大概思想。

**那么这题怎么做呢？**

我们分析一下普通暴力做法，扫一遍长度为$n$的数列，$O(n)$，太慢了。

我们如果用一个线段树，求解只需$O(logn)$时间。

证明一下：

我们假设有一个数列：

$-2,6,3,12,2,-20$

我们不可以用$-2,-20$，所以先排序一遍。

$-20,-2,2,3,6,12$

这些都从$0\sim5$编号。现在我们画一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/n2ugo1n3.png)

我们设这个树的最底下是数列在$0\sim7$位置上的数更新次数。现在因为sort了一遍，所以这些有数的值都是1。

我们把上面的父亲求下面两个孩子的合。

现在我们询问区间$[0,5]$的第二小的元素。

我们先到根，必须满足$k+1<6$，现在$2+1<6$没问题。所以我们去递归左右孩子，先到左孩子，这是左孩子的值是$4$（$2+2$），判断$k+1<4$？是，递归左右孩子。先走左，判断$k+1<2$，不是，所以你返回上一层，并且k减掉了刚刚点上的值，所以现在是$0$。现在你去有孩子，$k+1<2$？是的，所以递归左右孩子。先去左孩子，$k+1<1$？不，而且k+1还正好等于1，所以数列中第二项2就是你想要的结果。

![](https://cdn.luogu.com.cn/upload/image_hosting/6h8n0zoy.png)


上主席树模板代码：


```
#include<bits/stdc++.h>

using namespace std;

const int N = 200005;
int n, m, tot;
int root[N << 5], a[N], lc[N << 5], rc[N << 5], s[N << 5], b[N];

int x;

void build_tree(int &p, int l, int r) {//建树
    p = ++tot;//t++，下一个线段树
    s[p] = 0;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(lc[p], l, mid);
    build_tree(rc[p], mid + 1, r);
}

int update(int p, int l, int r) {//更新每个点的初始值
    int q = ++tot;
    lc[q] = lc[p];
    rc[q] = rc[p];
    s[q] = s[p] + 1;
    if (l == r) {
        return q;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        lc[q] = update(lc[q], l, mid);
    } else rc[q] = update(rc[q], mid + 1, r);
    return q;
}

int query(int u, int v, int l, int r, int k){//达到每个点的操作
    int mid = (l + r) >> 1;
    int x = s[lc[v]] - s[lc[u]];
    if (l == r) return l;
    if (x >= k) return query(lc[u], lc[v], l, mid, k);
    else return query(rc[u], rc[v], mid + 1, r, k - x);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);//排序
    int t = unique(b + 1, b + n + 1) - b - 1;
    build_tree(root[0], 1, t);
    for (int i = 1; i <= n; ++i) {
        x = lower_bound(b + 1, b + t + 1, a[i]) - b;
        root[i] = update(root[i - 1], 1, t);
    }
    while (m--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", b[query(root[l - 1], root[r], 1, t, k)]);
    }
    return 0;
}
```

出了这题，主席树还有很多，模板：[P3834 模板](https://www.luogu.com.cn/problem/P3834)。


---

## 作者：六楼溜刘 (赞：1)

## 题意

静态查询区间第 $k$ 小，一眼主席树/整体二分/树套树，但是我要讲另一种做法：**归并树。**

## 题解
#### Q1：什么是归并树？
归并树类似于线段树，但每个节点保存的是两个子节点保存的区间归并排序的结果，容易发现，这样的每个节点管辖的区间都是有序的，叶子节点可以递归求解，其他节点可以利用 `<algorithm>` 库中的 `merge` 函数在回溯时快速求解（当然你也可以自己写个归并函数），每一层总共只要 $O(n)$ ，预处理复杂度 $O(n\log n)$。
#### Q2：归并树有什么用？
由于每个节点都是单调递增的，我们可以二分查找某个数在某个节点所管辖的区间内的排名，利用类似于线段树区间查找的方法，我们可以 $O(\log^2 n)$ 地查找区间排名。结合二分答案，我们可以 $O(\log^3 n)$ 地查找静态区间第 $k$ 大，这个复杂度看起来好像很惊险，实际上由于每次查找的区间肯定远小于 $n$，完全可以 $O(\log^3 n)$ 过十万。另外，由于每一层总共要开 $O(n)$ 的空间，线段树有 $O(\log n)$ 层，空间复杂度为 $O(n\log n)$。

## code（直接套板子）
```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
#define mem(a,b) memset(a,b,sizeof(a))
#include<vector>
#define pbk(a) emplace_back(a)
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=1e5+5,SN=20,inf=0x3f3f3f3f;
int n,m,a[N];
struct MergeTree{
	#define lson l,mid,dpt+1
	#define rson mid+1,r,dpt+1
	private:
		int querymerge[20][N];
		void PushUp(int l,int r,int dpt){//回溯时归并
			int mid=(l+r)>>1;
			merge(querymerge[dpt+1]+l,querymerge[dpt+1]+mid+1,querymerge[dpt+1]+mid+1,querymerge[dpt+1]+r+1,querymerge[dpt]+l);
		}
	public:
		void Build(int* A,int l=1,int r=n,int dpt=0){//建树
			if(l==r){
				querymerge[dpt][l]=A[l];
				return;
			}
			int mid=(l+r)>>1;
			Build(A,lson);
			Build(A,rson);
			PushUp(l,r,dpt);
		}
		int AskCnt(int L,int R,int X,int l=1,int r=n,int dpt=0){
        //查询比它小的数的数量
			if(L<=l&&r<=R){
				return lower_bound(querymerge[dpt]+l,querymerge[dpt]+r+1,X)-querymerge[dpt]-l;
           //二分查询区间内有几个数小于它
			}
			int mid=(l+r)>>1,res=0;
			if(L<=mid) res+=AskCnt(L,R,X,lson);
			if(mid< R) res+=AskCnt(L,R,X,rson);
         //把两个儿子里比它小的数加起来
			return res;
		}
		int AskQuery(int L,int R,int K){
        //二分答案查询区间排名为 K+1 的数
			int ll=1,rr=n,mm;
			while(ll<=rr){
				mm=(ll+rr)>>1;
				int res=AskCnt(L,R,querymerge[0][mm]);
				if(res<=K) ll=mm+1;
				else rr=mm-1;
			}
			return querymerge[0][ll-1];
		}
}mt;
signed main(){
	n=read();m=read();
	forup(i,1,n){
		a[i]=read();
	}
	mt.Build(a);
	forup(i,1,m){
		int l=read(),r=read(),k=read();
		printf("%d\n",mt.AskQuery(l,r,k-1));
        //由于查询的是比它小的数的数量，所以应询问 k-1 
	}
}


```


---

## 作者：fzj2007 (赞：1)

## 第一步 读题

题目我就不放了（~~其实是翻译人的 $\LaTeX$ 有点恶心~~）。

给一个简化版的题目：给定一个长度为 $n$ 的序列，然后有 $m$ 次询问，每次询问在 $\left[l,r\right]$ 区间内第 $k$ 小的数。

## 第二步 思路

要我们求 $\left[l,r\right]$ 中的第 $k$ 小数。我们有一下几点思路：

首先是暴力枚举，对于每一次询问直接枚举 $l,r$，记录。加上预处理，时间复杂度最优是 $O\left(nm\right)$。由于 $n\le10^5$，$m\le5\times 10^3$，所以会超时，舍去。

然后我们要考虑优化。我们发现这道题让我们求区间内第 $k$ 大数，普通线段树显然做不了。。我看了一圈题解，大概有树套树、分块、划分树、归并树等等，但是还是可持久化线段树（主席树）居多。

我这个蒟蒻只会可持久化线段树，那就讲这个吧。初学者可以来看这篇博文，蒟蒻会详细讲解可持久化线段树。

### 第一部分 基础介绍&存储插入

由于可持久化线段树的创造者的名字缩写为 HJT，与我们敬爱的前国家主席的名字相同，故得主席树知名。算法主要思想就是保存多个历史版本的线段树。但是怎么保存呢？每一次修改都保存？空间不就炸了吗......

但是我们仔细想想，发现每次更改的仅仅是叶子节点到根节点这一条链上的结点。也就是只更改了 $\log_2 n$ 个结点，形成了一条链。这样与每改变一次就建一个树相比空间减少了很多。

但是我们要**特别注意主席树不能使用堆式存储法，就是说不能用$x\times2$，$x\times2+1$来表示左右儿子，而是应该动态开点，并保存每个节点的左右儿子编号。** 如果理解了上面的更改以后大家应该都可以理解。

这样我们可以在每次插入的时候进行一次更改存储。

### 第二部分 查找原理

我们已经存好了每一个版本。现在要求出 $\left[1,r\right]$ 区间内的第 $k$ 小值，我们就可以找到插入 $r$ 的版本，然后用普通权值线段树查询答案就可以了。

那我们现在把范围扩展到 $\left[l,r\right]$ 区间内第 $k$ 小的值，我们怎么办呢？

想一下，我们发现可以应用 **前缀和**。我们用 $\left[1,r\right]$ 的信息减去 $\left[1,l-1\right]$ 的信息就可以求出 $\left[l,r\right]$ 的信息。运用前缀和后我们也可以在 $O\left(log_2n\right)$ 的时间内做单次查询。

### 第三部分 空间

这一部分真的要单出来列。。因为你开空间不能吝啬，不然会爆炸。。我们先分析一下：

首先，我们动态开点，线段树会出现 $2\times n-1$ 个结点。然后我们有 $n$ 次修改，每次最多增加 $\lceil log_2n\rceil+1$ 个结点。由于本题 $n \le 10^5$，$\lceil log_2 10^5\rceil+1\approx18$，故总结点数为 $2\times 10^5-1+18\times 10^5=2\times 10^6-1$ 个。那么我们最好还是保守一点，所以我们最好开到 $2^5\times10^5$。或者再大一点（反正别开小，也别开炸。。）

## 第三部分 代码

终于到了代码部分了。。。（**警告：由于快读较长，建议跳过！**）

```
#include<bits/stdc++.h>//万能头
using namespace std; 
using std::cin;
using std::cout;
using std::endl;
namespace IN{//读入优化，建议跳过
    const int MAX_INPUT = 1000000;
    #define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MAX_INPUT),p1==p2)?EOF:*p1++)
    char buf[MAX_INPUT],*p1,*p2;
    template<typename T>inline bool read(T &x) {
        static std::streambuf *inbuf=cin.rdbuf();
        x=0;
        register int f=0,flag=false;
        register char ch=getc();
        while(!isdigit(ch)){
            if (ch=='-') f=1;
        	ch=getc();
        }
        if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
        while(isdigit(ch)) {
            x=x*10+ch-48;
            ch=getc();
        }
        x=f?-x:x;
        return flag;
    }
    template<typename T,typename ...Args>inline bool read(T& a,Args& ...args) {
       return read(a)&&read(args...);
    }
    #undef getc
}

namespace OUT{//输出优化，建议跳过
    template<typename T>inline void put(T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top=0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc('\n');
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc('\n');
    }
    inline void putc(const char ch){
        static std::streambuf *outbuf=cout.rdbuf();
        outbuf->sputc(ch);
    }
    inline void putstr(string s){
    	for(register int i=0;i<s.length();i++) putc(s[i]);
	}
    template<typename T>inline void put(const char ch,T x){
        static std::streambuf *outbuf=cout.rdbuf();
        static char stack[21];
        static int top = 0;
        if(x<0){
            outbuf->sputc('-');
            x=-x;
        }
        if(!x){
            outbuf->sputc('0');
            outbuf->sputc(ch);
            return;
        }
        while(x){
            stack[++top]=x%10+'0';
            x/=10;
        }
        while(top){
            outbuf->sputc(stack[top]);
            --top;
        }
        outbuf->sputc(ch);
    }
    template<typename T,typename ...Args> inline void put(T a,Args ...args){
        put(a);put(args...);
    }
    template<typename T,typename ...Args> inline void put(const char ch,T a,Args ...args){
        put(ch,a);put(ch,args...);
    }
}
using IN::read;
using OUT::put;
using OUT::putc;
using OUT::putstr;
//定义一些
#define N (int)2e5+5 
#define int long long
#define mid ((l+r)>>1)
int cnt,n,m,p,a[N],b[N],q[N];//cnt表示结点数，n，m，a读入，还有离散序列
struct CTnode{//结构体
	int s,l,r;//s表示数，
}t[N<<5];//结构体数组
namespace Chairman_Tree{//如果写好多东西放在一起有可能分不清
	inline int build(int l,int r){//这里建树
		int rt=++cnt;//保存结点编号
		t[rt].s=0;//初始化
		if(l<r) t[rt].l=build(l,mid),t[rt].r=build(mid+1,r);//可以建树就继续建树
		return rt;	//返回结点编号
	}
	inline int update(int k,int l,int r,int rt){//k表示旧结点位置
		int u=++cnt;//保存一下
		t[u].l=t[k].l,t[u].r=t[k].r,t[u].s=t[k].s+1;//复制，更改。点数为上一课加1
		if(l<r)//可以更新
			if(rt<=mid) t[u].l=update(t[k].l,l,mid,rt);//左儿子更新
			else t[u].r=update(t[k].r,mid+1,r,rt);//右儿子更新
		return u;
	}
	inline int query(int x,int y,int l,int r,int k){//查询第k小数
		if(l>=r) return l;
		int u=t[t[y].l].s-t[t[x].l].s;//区间减法得到左儿子信息
		if(u>=k) return query(t[x].l,t[y].l,l,mid,k);//在左儿子中
		else return query(t[x].r,t[y].r,mid+1,r,k-u);//在右儿子中
	}
	inline void init(){
		read(n,m);//读入
		for(int i=1;i<=n;i++) read(a[i]),b[i]=a[i];//读入并赋值
		sort(b+1,b+n+1);//这里先搜索
		p=unique(b+1,b+n+1)-b-1;//不重复数字的个数
		q[0]=build(1,p);//简历一颗空树，并赋值
		for(int i=1;i<=n;i++){
			int k=lower_bound(b+1,b+p+1,a[i])-b;//查找第一个大于等于a[i]的数
			q[i]=update(q[i-1],1,p,k);//更新并赋值
		}	
	}
	inline void solve(){//主函数（话说都变味了）
		init();//读入初始化
		for(int i=1,x,y,z;i<=m;i++)//m次查询
			read(x,y,z),put('\n',b[query(q[x-1],q[y],1,p,z)]);//改成b的输出。由于有影响，所以是q[x-1]
	}
}
signed main(signed argc, char const *argv[]){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Chairman_Tree::solve();//运行solve
    return 0;
}
```

### 第四步 其他

- 撰文不易，大佬勿喷！
- 文章若有`bug`请私信作者，感激不尽！
- 如果有帮助，请帮忙点下赞，感谢！

---

## 作者：doby (赞：1)

静态区间kth

显然也可以使用线段树套平衡树

但是单次查询区间排名就需要log2n，还需要二分求出kth

于是复杂度高达mlog2n*log(2e9)

再加上线段树和平衡树的常数都比较大以及667ms

于是无论怎样都会卡在test16 QwQ

推荐使用主席树

这里给出线段树+treap的代码

```cpp
#include<cstdio>
#include<cstdlib>
using namespace std;
int n,m,l,r,pos,x,out,fh,a[100010],tot,root[400010];
char c,opt;
struct Treap
{
	int l,r,val,dat,cnt,size;
}t[3000010];
int Read()
{
	out=0,fh=1,c=getchar();
	while(c<48||c>57){if(c==45){fh=-1;}c=getchar();}
	while(c>=48&&c<=57){out=(out<<3)+(out<<1)+(c&15),c=getchar();}
	return out*fh;
}
int New(int val)
{
	t[++tot].val=val,
	t[tot].dat=rand()%19260817,
	t[tot].cnt=t[tot].size=1;
	return tot;
}
void Update(int p)
{
	t[p].size=t[t[p].l].size+t[t[p].r].size+t[p].cnt;
}
void Zig(int &p)
{
	int q=t[p].l;
	t[p].l=t[q].r,t[q].r=p,p=q;
	Update(t[q].r);Update(p); 
}
void Zag(int &p)
{
	int q=t[p].r;
	t[p].r=t[q].l,t[q].l=p,p=q;
	Update(t[q].l);Update(p); 
}
void Insert(int &p,int val)
{
	if(!p)
	{
		p=New(val);
		return;
	}
	if(val==t[p].val)
	{
		++t[p].cnt;
		Update(p);
		return;
	}
	if(val<t[p].val)
	{
		Insert(t[p].l,val);
		if(t[p].dat<t[t[p].l].dat){Zig(p);}
	}
	else
	{
		Insert(t[p].r,val);
		if(t[p].dat<t[t[p].r].dat){Zag(p);}
	}
	Update(p);
}
int GRBV(int p,int val)
{
	if(!p){return 0;}
	if(val==t[p].val){return t[t[p].l].size;}
	if(val<t[p].val){return GRBV(t[p].l,val);}
	return GRBV(t[p].r,val)+t[t[p].l].size+t[p].cnt;
}
void Build(int k,int l,int r)
{
	if(l==r)
	{
		Insert(root[k],a[l]);
		return;
	}
	int mid=l+r>>1;
	Build(k<<1,l,mid);
	Build(k<<1|1,mid+1,r);
	for(int i=l;i<=r;++i){Insert(root[k],a[i]);}
}
int QueryR(int k,int l,int r,int ll,int rr,int x)
{
	if(l>rr||r<ll){return 0;}
	if(l>=ll&&r<=rr){return GRBV(root[k],x);}
	int mid=l+r>>1;
	return QueryR(k<<1,l,mid,ll,rr,x)+QueryR(k<<1|1,mid+1,r,ll,rr,x);
}
int QueryV(int l,int r,int rank)
{
	int lef=-1000000010,rig=1000000010;
	while(lef+1<rig)
	{
		int mid=lef+rig>>1;
		if(QueryR(1,1,n,l,r,mid)+1<=rank){lef=mid;}
		else{rig=mid;}
	}
	return lef;
}
int main()
{
	n=Read(),m=Read();
	for(int i=1;i<=n;++i){a[i]=Read();}
	Build(1,1,n);
	while(m--)
	{
		l=Read(),r=Read(),x=Read();
		printf("%d\n",QueryV(l,r,x));
	}
	return 0;
}
```

---

## 作者：da32s1da (赞：1)

竟然没有**划分树**的题解。。

我们考虑把序列按照一定的顺序排序。。

比如样例
```
tre[0] : 1 5 2 6 3 7 4
tre[1] : 1 2 3 4 5 6 7
```
~~Sort~~

换一组吧:$\ 5\ 8\ 4\ 4\ 3\ 2\ 0\ 9$
```
tre[0][] : 5 8 4 4 3 2 0 9
tre[1][] : 4 3 2 0 5 8 4 9
tre[2][] : 2 0 4 3 5 4 8 9
tre[3][] : 0 2 3 4 4 5 8 9
tre[4][] : 0 0 0 0 0 0 0 0
```
发现点什么？

我们把排序后的$1$到$4$按它们**在原序列的顺序**放到**tre[1]**的$1$到$4$里，把排序后的$5$到$8$按它们**在原序列的顺序**放到**tre[1]**的$5$到$8$里。

然后重复上述过程，直到**单个点**返回。

可知，最多进行$\log$次。

另外，我们记$lef[now][i]$为第$now$层，第$i$个点**之前(及自己)**有多少个放到了$tre$的左儿子中。

比如
```
lef[0][] = 0 0 1 1 2 3 4 4
```

那怎么做呢？~~简单的模拟~~

注意一下当**中值**多余一个时，特殊处理。

我们令$gs=siz[ls]-\sum_{i=ls}^{rs}[\ tre[now][i]<b[mid]\ ]$

即计算出应该向左子树放几个中值，顺序防止即可。其他的中值放到右子树中。

代码
```
void mktree(int now,int ls,int rs){
	if(ls==rs)return;
	int nrs=ls+rs>>1,gs=nrs-ls+1;
	for(int i=ls;i<=rs;i++)
	if(tre[now][i]<b[nrs])--gs;
    //计算有几个中值放到左子树中
	int Ls=ls,Rs=nrs+1;
	for(int i=ls;i<=rs;i++){
		lef[now][i]=lef[now][i-1];
        //记一下lef数组
		if(tre[now][i]<b[nrs]||(tre[now][i]==b[nrs]&&gs)){
        	//比中值小或者是 应该往左子树放的中值
			tre[now+1][Ls++]=tre[now][i];//顺序放置
			lef[now][i]++;//lef数组加一下自己
			if(tre[now][i]==b[nrs])--gs;//若为中值，修改
		}else tre[now+1][Rs++]=tre[now][i];//右子树顺序放置
	}
	mktree(now+1,ls,nrs);//左子树
	mktree(now+1,nrs+1,rs);//右子树
}
```
可能有人注意到我们的$lef$数组直接等于上一个,没有特判边界。这是没有关系的，而且还方便查询。

那具体怎么查询呢？

比如我们查询上面序列$\ 5\ 8\ 4\ 4\ 3\ 2\ 0\ 9$中，$2$到$5$第$3$小的数值。

发现$2$到$5$中，在**tre[1][1..4]**中的有$2$个,少于我们查询的$3$。所以应该去**右子树**找。

而且是在$tre[1][]$的$6$到$7$查第$1$小的。

因为第$0$层的$6$到$8$有$2$个放在左子树，所以右边界相应的应该向右$2$个。故应该是$7$。而左边界是因为$2$到$5$有$2$个在右子树。因为是顺序放置，所以左边界是$7-2+1=6$。

下面的自己推推好啦~~。

```
int qans(int now,int ls,int rs,int l,int r,int k){
	if(ls==rs)return tre[now][ls];//叶子直接返回
	int gs=lef[now][r]-lef[now][l-1],nrs=ls+rs>>1,Ls,Rs;
    //gs是l...r有多少放在左子树
	if(gs>=k){//多于k个
		Ls=ls+lef[now][l-1]-lef[now][ls-1];
        //左边界是ls+[ls...l-1]有多少在左子树
		Rs=Ls+gs-1;//右边界加上[l...r]在左子树的
		return qans(now+1,ls,nrs,Ls,Rs,k);
	}else{
		Rs=r+lef[now][rs]-lef[now][r];
        //右边界是r+[r+1...rs]有多少在左子树
		Ls=Rs-(r-l-gs);//左边界是右边界减去[l...r]在左子树的
		return qans(now+1,nrs+1,rs,Ls,Rs,k-gs);
	}
}
```

总程序：
```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+50;
int n,m,x,y,z;
int a[N],b[N];
int tre[20][N],lef[20][N];
void mktree(int now,int ls,int rs){
    if(ls==rs)return;
    int nrs=ls+rs>>1,gs=nrs-ls+1;
    for(int i=ls;i<=rs;i++)
    if(tre[now][i]<b[nrs])--gs;
    int Ls=ls,Rs=nrs+1;
    for(int i=ls;i<=rs;i++){
        lef[now][i]=lef[now][i-1];
        if(tre[now][i]<b[nrs]||(tre[now][i]==b[nrs]&&gs)){
            tre[now+1][Ls++]=tre[now][i];
            lef[now][i]++;
            if(tre[now][i]==b[nrs])--gs;
        }else tre[now+1][Rs++]=tre[now][i];
    }
    mktree(now+1,ls,nrs);
    mktree(now+1,nrs+1,rs);
}
int qans(int now,int ls,int rs,int l,int r,int k){
    if(ls==rs)return tre[now][ls];
    int gs=lef[now][r]-lef[now][l-1],nrs=ls+rs>>1,Ls,Rs;
    if(gs>=k){
        Ls=ls+lef[now][l-1]-lef[now][ls-1];
        Rs=Ls+gs-1;
        return qans(now+1,ls,nrs,Ls,Rs,k);
    }else{
        Rs=r+lef[now][rs]-lef[now][r];
        Ls=Rs-(r-l-gs);
        return qans(now+1,nrs+1,rs,Ls,Rs,k-gs);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        tre[0][i]=b[i]=a[i];
    }
    sort(b+1,b+n+1);
    mktree(0,1,n);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        printf("%d\n",qans(0,1,n,x,y,z));
    }
} 
```

---

## 作者：skydogli (赞：1)

~~隔壁太挤，来这里发一篇题解~~
## 主席树入门题。

### 算法介绍
主席树，原名可持久化线段树，学名函数式线段树（应该是吧），因为发明者黄嘉泰缩写与***主席重名，故得名主席树，其解决的最基础最著名的问题就是静态区间第K大（~~动态没学~~），本题就是入门题。

还是比较喜欢这个数据结构的，因为只增加了空间复杂度（~~我这么菜怎么可能会垃圾回收~~)和一点常数（然而被[这题](https://www.luogu.org/recordnew/lists?uid=7480&pid=1972&status=&sort=undefined)卡了贼久），码量完全没增加，还是肥肠良心的。

其他博客都把查询说得很细，那我主要讲讲建树吧。

主席树之所以可以在较少空间维护历史版本，核心就在于共享儿子，(咳咳。。)因为每一次更新只会更新整棵树中的一颗，举个栗子（圈中的数字代表树上的节点编号而不是范围）：
![](https://cdn.luogu.com.cn/upload/pic/53183.png )
手有点~~十分~~抖，谅解一下哈

由图可知，父亲节点和子节点的关系不再是*2和*2+1了，因为现在要共享字节点，所以要手动存儿子。

### 关于本题
 既然主席树讲完了，那就回归题目，首先为了建树，肯定要先离散化一遍的，**建树要按大小而不是输入的顺序编号**，要求l到r区间第K大，其实就是l到r的历史版本，因为查询是静态的，所以我们可以用差分的思想，用历史版本为r的树-历史版本为l-1的树，这样就能得到l和r的区间了。得到区间后，因为我们建树时按数值大小，就具有二分性了，如果K小于等于左子树区间的数的数量，就往左子树找，否则往右子树找，于是就这么愉快的AC了！
 ### 代码&注释

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mid ((l+r)>>1)
#define MN 200005
int n,m,a[MN],v[MN],id[MN],l,r,k,root[MN],cnt;
//a：输入的数 id：离散化的编号 root：各个历史版本的根
struct tree{
    int Ls,Rs,sum;
}Tree[MN*20];
//Ls、Rs：左右子树 sum：区间中数的数量
void change(int num,int &x,int l,int r){//注意这个'&'
    Tree[cnt]=Tree[x];x=cnt;cnt++;
    //建一个新节点，以便修改
    Tree[x].sum++;
    if(l==r) return;
    if(id[mid]>=num) change(num,Tree[x].Ls,l,mid);
        else change(num,Tree[x].Rs,mid+1,r);
       //改变需要改变的子节点
}
int ask(int i,int j,int num,int l,int r){
    if(l==r) return l;
    int tmp=Tree[Tree[j].Ls].sum-Tree[Tree[i].Ls].sum;
    if(tmp>=num) return ask(Tree[i].Ls,Tree[j].Ls,num,l,mid);
        else return ask(Tree[i].Rs,Tree[j].Rs,num-tmp,mid+1,r);
}//差分后查询
int main(){
    scanf("%d%d",&n,&m);
    cnt=1;
    for(int i=1;i<=n;i++) {scanf("%d",&a[i]);v[i]=a[i];}
    sort(a+1,a+1+n);
    int N=unique(a+1,a+1+n)-a-1;
    for(int i=1;i<=N;i++)
        id[i]=a[i];
    //离散化
    for(int i=1;i<=n;i++){
        root[i]=root[i-1];//要共用上一个版本的节点
        change(v[i],root[i],1,N);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",id[ask(root[l-1],root[r],k,1,N)]);
    }
    return 0;
}


```

真的挺短的^_^


---

## 作者：DennyQi (赞：0)

可持久化权值线段树裸题

先离散化，然后根据给出的数列，依次更新，每次更新一个。这样在询问区间$[l,r]$时就相当于将第$l-1$棵线段树与第$r$棵线段树进行比较（相减），然后像平衡树询问第k小一样从上往下走一遍就好了

```cpp
/*By DennyQi 2018*/
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 100010;
const int INF = 1061109567;
inline int Max(const int a, const int b){ return (a > b) ? a : b; }
inline int Min(const int a, const int b){ return (a < b) ? a : b; }
inline int read(){
    int x = 0; int w = 1; register char c = getchar();
    for(; c ^ '-' && (c < '0' || c > '9'); c = getchar());
    if(c == '-') w = -1, c = getchar();
    for(; c >= '0' && c <= '9'; c = getchar()) x = (x<<3) + (x<<1) + c - '0'; return x * w;
}
struct Num{
	int val,idx,rnk;
}a[MAXN];
int N,M,z,y,x;
int T[MAXN],mp[MAXN];
struct zxs{
	int l[MAXN<<5], r[MAXN<<5], amt[MAXN<<5], numNode;
	int update(int pre, int L, int R, int x){
		int cur = ++numNode;
		l[cur] = l[pre], r[cur] = r[pre], amt[cur] = amt[pre] + 1;
		if(L < R){
			if(x <= (L+R)/2) l[cur] = update(l[pre], L, (L+R)/2, x);
			else r[cur] = update(r[pre], (L+R)/2+1, R, x);
		}
		return cur;
	}
	int query(int pre, int u, int L, int R, int k){
		int sum = amt[l[u]] - amt[l[pre]];
		if(L == R) return mp[L];
		if(sum >= k) return query(l[pre], l[u], L, (L+R)/2, k);
		else return query(r[pre], r[u], (L+R)/2+1, R, k-sum);
	}
}hjt;
inline bool cmp1(const Num& a, const Num& b){ return a.val < b.val; }
inline bool cmp2(const Num& a, const Num& b){ return a.idx < b.idx; }
int main(){
//	freopen(".in","r",stdin);
	N = read(), M = read();
	for(int i = 1; i <= N; ++i){
		a[i].val = read();
		a[i].idx = i;
	}
	sort(a+1, a+N+1, cmp1);
	for(int i = 1; i <= N; ++i){
		if(i != 1 && a[i].val == a[i-1].val) a[i].rnk = a[i-1].rnk;
		else a[i].rnk = i;
	}
	sort(a+1, a+N+1, cmp2);
	for(int i = 1; i <= N; ++i){
		T[i] = hjt.update(T[i-1], 1, N, a[i].rnk);
		mp[a[i].rnk] = a[i].val;
	}
	for(int i = 1; i <= M; ++i){
		x = read(), y = read(), z = read();
		printf("%d\n", hjt.query(T[x-1], T[y], 1, N, z));
	}
	return 0;
}
```

---

## 作者：良月澪二 (赞：0)

这...

看到题目，“简单的做法可是过不了的”，以为会卡掉我的主席树

交个板子就过了呢，明白了简单的做法的含义

来自$P3834$ $AC$代码

相信不会主席树的是不会来看这种题的，写什么注释呢

```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
//#include<inttypes.h>
#define A 5000010

using namespace std;
struct node{
	int l,r,w;
	node()
	{
		w=0;
	}
}tree[A];
struct Node{
	int x,id;
}val[A];
bool cmp(Node a,Node b)
{
	return a.x<b.x;
}
int root[A],rank[A],cnt;

inline void update(int num,int &rt,int l,int r)
{
	tree[cnt++]=tree[rt];
	rt=cnt-1;
	tree[rt].w++;
	if(l==r)
	  return;
	int m=l+r>>1;
	if(num<=m)
	  update(num,tree[rt].l,l,m);
	else update(num,tree[rt].r,m+1,r);
}
inline int query(int i,int j,int k,int l,int r)
{
	int x=tree[tree[j].l].w-tree[tree[i].l].w;
	if(l==r)
	  return l;
	int m=l+r>>1;
	if(k<=x)
	  return query(tree[i].l,tree[j].l,k,l,m);
	else return query(tree[i].r,tree[j].r,k-x,m+1,r);
}
int n,m;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&val[i].x);
		val[i].id=i;
	}
	sort(val+1,val+n+1,cmp);
	for(int i=1;i<=n;i++)
	  rank[val[i].id]=i;
	cnt=1;
	root[0]=0;
	tree[0].l=tree[0].r=tree[0].w=0;
	for(int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		update(rank[i],root[i],1,n);
	}
	int l,r,k;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",val[query(root[l-1],root[r],k,1,n)].x);
	}
}
/*
7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3
*/
```

---

## 作者：dunko (赞：0)

## **题目**
[点这儿](https://www.luogu.org/problemnew/show/SP3946)

## **思路**
主席树大家一定都有所了解吧，这一题就是主席树的模板啊！！  
**静态区间第K小**，不就说明了这题可以用主席树吗？主席树中动态开点就不多说了吧      
还有就是没看这n个数的范围这么大吗？一定要用**离散化**

## **算法**
想必大家都会一点点主席树吧，那蒟蒻我就不再多说了，实在不行可以看看上面大佬的题解，或是找几篇博客看看，还可以找几个视频看看。

## **代码**
不必多说了吧，代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=500001;
struct node{
    int l,r,sum;
}T[maxn*20];//这是保存树的结构体
struct zz{
    int x,id;
}a[maxn];//离散化时要用
int n,m,b[maxn],cnt,root[maxn];
bool cmp(zz a,zz b){return a.x<b.x;}
void update(int x,int &rt,int l,int r){//建树
//注意，这里的rt，也就是这棵树的根是会变的
    T[++cnt]=T[rt]; rt=cnt; T[rt].sum++;//先与上一个树一样，有改变的地方再新建点
    if(l==r) return;
    int mid=(l+r)>>1;//这里就和线段树的操作一样
    if(x<=mid) update(x,T[rt].l,l,mid);
    else update(x,T[rt].r,mid+1,r);
}
int ask(int rt1,int rt2,int x,int l,int r){//查询
    int d=T[T[rt2].l].sum-T[T[rt1].l].sum;
    //前缀和思想，也可以拆开来一颗树一棵树的写，这里我是将它放一起做了
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(x<=d) return ask(T[rt1].l,T[rt2].l,x,l,mid);
    //如果这区间左半边的数的数量比x大，那第x小的数一定在左半边。
    else return ask(T[rt1].r,T[rt2].r,x-d,mid+1,r);
    //不然就在右半边找第x-d大的数
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].x);
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);//先排序一遍，从小到大
    for(int i=1;i<=n;i++) b[a[i].id]=i;//离散化关键点
    for(int i=1;i<=n;i++){
        root[i]=root[i-1];
        update(b[i],root[i],1,n);
    }//建树
    int x,y,z;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        printf("%d\n",a[ask(root[x-1],root[y],z,1,n)].x);//找区间x到y之间第K小的数
        //转化成前缀和，主席树基本操作
    }
    return 0;
}
```

---

