# A Simple Task

## 题目描述

This task is very simple. Given a string $ S $ of length $ n $ and $ q $ queries each query is on the format $ i $ $ j $ $ k $ which means sort the substring consisting of the characters from $ i $ to $ j $ in non-decreasing order if $ k=1 $ or in non-increasing order if $ k=0 $ .

Output the final string after applying the queries.

## 说明/提示

First sample test explanation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/39812d297b72578842edac4711612bcaf8f08f55.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/6cf00260e704a305c81e1f57b87405efa2610fa7.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/8d72452272093b12cc5f5081cf07220bba9298d5.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/51ddb7e0620c1f3452d956f281c3537d11d07fb3.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558E/47cfdfe8b8cb10e651ce3dbdd53d8f068aca3e79.png)

## 样例 #1

### 输入

```
10 5
abacdabcda
7 10 0
5 8 1
1 4 0
3 6 0
7 10 1
```

### 输出

```
cbcaaaabdd```

## 样例 #2

### 输入

```
10 1
agjucbvdfk
1 10 1
```

### 输出

```
abcdfgjkuv```

# 题解

## 作者：leozhang (赞：25)

非常好的一道题，是线段树的常见玩法

将字符串转化为1~26个数

对区间开一棵线段树，用两个数组分别维护区间中1~26每个数的个数以及一个区间覆盖标记，表示这个区间是否被某一个值覆盖了

在每次排序时，首先查出这个区间中1~26每个数出现的次数，然后因为是排过序的，所以相等的数排完序之后一定是连续的一段区间，这样如果升序，我们就对整个区间从小到大进行覆盖，否则从大到小覆盖

最后遍历整棵线段树输出即可

一句话总结：每次排序只需做一次区间查询，26次区间覆盖，这样时间复杂度O（26nlogn）

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#define ls tree[rt].lson
#define rs tree[rt].rson
#define rt1 rt<<1
#define rt2 (rt<<1)|1
using namespace std;
struct Tree
{
	bool tag[30];
	int s[30];
	int lson;
	int rson;
}tree[400005];
struct node
{
	int v[30];
}zero;
int n,q;
int a[100005];
char s[100005];
void pushdown(int rt)
{
	if(ls==rs)
	{
		return;
	}
	for(int i=1;i<=26;i++)
	{
		if(tree[rt].tag[i])
		{
			for(int j=1;j<=26;j++)
			{
				tree[rt1].tag[j]=0;
				tree[rt1].s[j]=0;
				tree[rt2].tag[j]=0;
				tree[rt2].s[j]=0;
			}
			tree[rt1].tag[i]=1;
			tree[rt2].tag[i]=1;
			tree[rt1].s[i]=tree[rt1].rson-tree[rt1].lson+1;
			tree[rt2].s[i]=tree[rt2].rson-tree[rt2].lson+1;
			tree[rt].tag[i]=0;
			break;
		}
	}
}
void buildtree(int rt,int l,int r)
{
	tree[rt].lson=l;
	tree[rt].rson=r;
	if(l==r)
	{
		tree[rt].s[a[l]]=1;
		return;
	}
	int mid=(l+r)>>1;
	buildtree(rt1,l,mid);
	buildtree(rt2,mid+1,r);
	for(int i=1;i<=26;i++)
	{
		tree[rt].s[i]=tree[rt1].s[i]+tree[rt2].s[i];
	}
}
node add(node x,node y)
{
	node ret=zero;
	for(int i=1;i<=26;i++)
	{
		ret.v[i]=x.v[i]+y.v[i];
	}
	return ret;
}
node query(int rt,int l,int r)
{
	if(ls>r||rs<l)
	{
		return zero;
	}else if(ls>=l&&rs<=r)
	{
		node ret=zero;
		for(int i=1;i<=26;i++)
		{
			ret.v[i]=tree[rt].s[i];
		}
		return ret;
	}
	pushdown(rt);
	int mid=(ls+rs)>>1;
	return add(query(rt1,l,r),query(rt2,l,r));
}
void update(int rt,int l,int r,int val)
{
	if(ls>r||rs<l)
	{
		return;
	}
	if(ls>=l&&rs<=r)
	{
		for(int i=1;i<=26;i++)
		{
			tree[rt].s[i]=0;
			tree[rt].tag[i]=0;
		}
		tree[rt].tag[val]=1;
		tree[rt].s[val]=rs-ls+1;
		return;
	}
	pushdown(rt);
	int mid=(ls+rs)>>1;
	if(l<=mid)
	{
		update(rt1,l,r,val);
	}
	if(r>mid)
	{
		update(rt2,l,r,val);
	}
	for(int i=1;i<=26;i++)
	{
		tree[rt].s[i]=tree[rt1].s[i]+tree[rt2].s[i];
	}
}
void pushit(int rt)
{
	pushdown(rt);
	if(ls==rs)
	{
		return;
	}
	pushit(rt1);
	pushit(rt2);
}
void print(int rt)
{
	if(ls==rs)
	{
		for(int i=1;i<=26;i++)
		{
			if(tree[rt].s[i])
			{
				printf("%c",i-1+'a');
				return;
			}
		}
	}
	print(rt1);
	print(rt2);
}
inline int read()
{
	int f=1,x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
//	freopen("third.in","r",stdin);
//	freopen("third.out","w",stdout);
	n=read(),q=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=s[i]-'a'+1;
	}
	buildtree(1,1,n);
	for(int i=1;i<=q;i++)
	{
		int l=read(),r=read(),typ=read();
		node temp=query(1,l,r);
		if(typ==1)
		{
			for(int j=1;j<=26;j++)
			{
				update(1,l,l+temp.v[j]-1,j);
				l+=temp.v[j];
			}
		}else
		{
			for(int j=26;j>=1;j--)
			{
				update(1,l,l+temp.v[j]-1,j);
				l+=temp.v[j];
			}
		}
	}
	pushit(1);
	print(1);
	printf("\n");
	return 0;
}
```

---

## 作者：LJC00753 (赞：19)

珂朵莉真可爱

所以我们要用珂朵莉树

每次统计一下区间里每个字母出现多少次，然后往set里insert 26个节点接行了

因为最多产生n+26m个节点，且每个节点被遍历到后一定会被删除

所以时间复杂度是 n + 26m + nlogn

```#include<bits/stdc++.h>
using namespace std;

#define MAXN 100005 
#define se set<aa>
#define it iterator

struct aa {
	int l,r;
	char v;
};

bool operator <(aa a,aa b) {
	return a.r < b.r;
}

char a[MAXN];
int n,m;
se s;

void rd() {
	scanf("%d%d",&n,&m);
	scanf("%s",a+1);
	for(int i = 1; i <= n; i ++) {
		s.insert((aa){i,i,a[i]});
	}
}

void split(se::it x,int i) {
	int l = x->l,r = x->r;
	char v = x->v;
	if(i < l || i >= r) return;
	s.erase(x);
	s.insert((aa){l,i,v});
	s.insert((aa){i+1,r,v});
}

int c[30];

void paix(int l,int r,bool p) {
	se::it x = s.lower_bound((aa){0,l-1,0});
	split(x,l-1);
	se::it y = s.lower_bound((aa){0,r,0});
	split(y,r);
	x = s.lower_bound((aa){0,l,0});
	y = s.lower_bound((aa){0,r,0});
	y ++;
	for(se::it i = x; i != y; i ++) 
		c[(i->v)-'a'] += (i->r) - (i->l) + 1;
	s.erase(x,y);
	if(p) {
		int x = l;
		for(int i = 0; i <= 26; i ++)
		if(c[i] > 0){
			s.insert((aa){x,x+c[i]-1,i+'a'});
			x += c[i];
		}
	} else {
		int x = l;
		for(int i = 26; i >= 0; i --)
		if(c[i] > 0){
			s.insert((aa){x,x+c[i]-1,i+'a'});
			x += c[i];
		}		
	}
	memset(c,0,sizeof(c)); 
}

int main()
{
	rd();
	for(int i = 1; i <= m; i ++)
	{
		int l,r,p;
		scanf("%d%d%d",&l,&r,&p);
		paix(l,r,p);
	}
	for(se::it i = s.begin(); i != s.end(); i ++)
		for(int j = i->l; j <= i->r; j ++)
			putchar(i->v);
	cout<<"\n";

	return 0;
 } 
```

珂朵莉真可爱

---

## 作者：奇米 (赞：11)

# 题解 - $\mathrm{CF558E \ A \ Simple \ Task}$
## 吐槽一下：
* 这道题目足足做了我$3$个小时，我$stm$真的要吐血了。

## 题目意思
就是给你一长为$n(\leq 10^5)$个小写字母序列，支持两种操作：
* $(l,r,0)$：将$[l,r]$升序
* $(l,r,1)$：将$[l,r]$倒序

求出$m(\leq 10^5)$次操作后的序列。

## $\mathrm{Sol}$
* 可以说是一道经典套路题吧
* 我们首先建$26$棵线段树维护每一个字母，相当于对于升序我们只要对于这段区间里的字母按$\mathrm{a-z}$的顺序依次加入，不停更新加入左端点即可，右端点即为左端点加这个字母的数量。倒序也同理，只要$\mathrm{z-a}$的顺序即可。
* 然后就是线段树的基本操作了（嘻嘻嘻，我调了半年。
* 说句实话：对于大多数题目，套路就是硬道理。。。

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
 
inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}
 
const int N=1e5+5;
 
int n,m,ans;
char ch[100001],res[100001];
 
struct seg
{
	int tr[31][400001],laz[31][400001];
	inline void init()
	{
		for ( int i=1;i<=26;i++ )  
			memset(laz[i],-1,sizeof(laz[i]));
	}
	inline void build(int rt,int l,int r)
	{
		if(l==r)
		{
			tr[ch[l]-'a'+1][rt]=1;
			return;
		}
		int mid=(l+r)/2;
		build(rt<<1,l,mid);
		build(rt<<1|1,mid+1,r);
		for ( int i=1;i<=26;i++ ) 
			tr[i][rt]=(tr[i][rt<<1]+tr[i][rt<<1|1]);
	}
	inline void push_down(int rt,int l,int r,int col)
	{
		if(laz[col][rt]!=-1)
		{
			tr[col][rt]=laz[col][rt]*(r-l+1);
			int mid=(l+r)/2;
			tr[col][rt<<1]=laz[col][rt]*(mid-l+1);
			tr[col][rt<<1|1]=laz[col][rt]*(r-mid);
			laz[col][rt<<1]=laz[col][rt];
			laz[col][rt<<1|1]=laz[col][rt];
			laz[col][rt]=-1;
		}
	}
	inline void update(int rt,int l,int r,int ll,int rr,int col,int v)
	{
		if(ll<=l&&r<=rr)
		{
			tr[col][rt]=v*(r-l+1);
			laz[col][rt]=v;
			return;
		}
		push_down(rt,l,r,col);
		int mid=(l+r)/2;
		if(ll<=mid) update(rt<<1,l,mid,ll,rr,col,v);
		if(rr>mid) update(rt<<1|1,mid+1,r,ll,rr,col,v);
		tr[col][rt]=tr[col][rt<<1]+tr[col][rt<<1|1];
	}
	inline int query(int rt,int l,int r,int ll,int rr,int col)
	{
		if(ll<=l&&r<=rr) return tr[col][rt];
		push_down(rt,l,r,col);
		int mid=(l+r)/2;
		int sum=0;
		if(ll<=mid) sum+=query(rt<<1,l,mid,ll,rr,col);
		if(rr>mid) sum+=query(rt<<1|1,mid+1,r,ll,rr,col);
		return sum;
	}
	inline void print(int rt,int l,int r)
	{
		if(l==r)
		{
			for ( int i=1;i<=26;i++ ) 
				if(tr[i][rt]) 
				{
					res[l]='a'+i-1;
					break;
				}
			return;
		}
		for ( int i=1;i<=26;i++ ) push_down(rt,l,r,i);
		int mid=(l+r)/2;
		print(rt<<1,l,mid);
		print(rt<<1|1,mid+1,r);
	}				
};
seg T;
 
int main()
{
	n=read();
	m=read();
	scanf("%s",ch+1);
	T.init();
	T.build(1,1,n);
	for (;m--;)
	{
		int op,x,y;
		x=read(),y=read(),op=read();
		if(op==1)
		{
			int tmp=x-1;
            for ( int j=1;j<=26;j++ )
			{
                int cas=T.query(1,1,n,x,y,j);
                if(!cas)continue;
                T.update(1,1,n,x,y,j,0);
                T.update(1,1,n,tmp+1,tmp+cas,j,1);
				tmp=tmp+cas;
            }
		}
		else
		{
			int lp=x-1;
			for ( int j=26;j>=1;j-- )
			{
				int sum=T.query(1,1,n,x,y,j);
				if(!sum) continue;
				T.update(1,1,n,x,y,j,0);
				T.update(1,1,n,lp+1,lp+sum,j,1);
				lp+=sum;

			}
		}
	}
	T.print(1,1,n);
	for ( int i=1;i<=n;i++ ) putchar(res[i]);
	return 0;
}
/*
10 5
abacdabcda
7 10 0
5 8 1
1 4 0
3 6 0
7 10 1
*/
```


---

## 作者：Krystallos (赞：11)

这里大概简述一下我的心路历程。

第一眼：`sort`牛逼！

~~TLE警告~~

第二眼：整理出询问区间中各个字母的数量，再根据各个字母的数量按要求平摊在区间内。

举个例子，假设区间需要从小到大排序，那么先从`a`开始，找到`a`的数量，然后把该区间内的原有`a`清空，然后从区间左端开始平铺答案数个`a`。以此类推，找到`b`的数量，清空，平铺在`a`的右边。从大到小同理。

这样的话我们需要一种数据结构，能够区间修改，区间查询。线段树刚好可以满足我们的需要。

稍微涉及一点内层实现，我们需要建立26颗线段树，维护每个字母在每个区间内的数量。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int nn = 1e5 + 5;
struct SegTree {//线段树基本结构体
	int l, r, cnt, lazy;
	#define l(p, i) tree[i][p].l//我很懒，懒得写全变量名
	#define r(p, i) tree[i][p].r
	#define lazy(p, i) tree[i][p].lazy
	#define cnt(p, i) tree[i][p].cnt
}tree[26][nn * 8];//26颗线段树，八倍空间
char a[nn];
int n, q;
#define ls (p << 1)
#define rs (p << 1 | 1)
void build(int p, int l, int r, int id) {//建树
	l(p, id) = l;
	r(p, id) = r;
	lazy(p, id) = -1;
	if (l == r) {
		cnt(p, id) = (a[l] == id + 'a');//如果该位置是正在建立的线段树所代表的位置，该点权值为1
		return;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid, id);
	build(rs, mid + 1, r, id);
	cnt(p, id) = cnt(ls, id) + cnt(rs, id);
	return;
}
inline void spread(int p, int id) {//处理lazy标记的函数
	if (~lazy(p, id)) {//等价于lazy(p, id) != -1
		lazy(ls, id) = lazy(rs, id) = lazy(p, id);
		cnt(ls, id) = lazy(ls, id) * (r(ls, id) - l(ls, id) + 1);
		cnt(rs, id) = lazy(rs, id) * (r(rs, id) - l(rs, id) + 1);
		lazy(p, id) = -1;
	}
}
void change(int p, int l, int r, int d, int id) {
	if (l <= l(p, id) && r(p, id) <= r) {
		lazy(p, id) = d;
		cnt(p, id) = d * (r(p, id) - l(p, id) + 1);
		return;
	}
	spread(p, id);//区间覆盖操作不满足交换律，必须先处理掉才能向下修改
	if (l <= r(ls, id))
		change(ls, l, r, d, id);
	if (l(rs, id) <= r)
		change(rs, l, r, d, id);
	cnt(p, id) = cnt(ls, id) + cnt(rs, id);
	return;
}
int ask(int p, int l, int r, int id) {
	if (l <= l(p, id) && r(p, id) <= r)
		return cnt(p, id);
	spread(p, id);//查询前先下放lazy标记
	int ans = 0;
	if (l <= r(ls, id))
		ans += ask(ls, l, r, id);
	if (l(rs, id) <= r)
		ans += ask(rs, l, r, id);
	return ans;
}
void final(int p, int id) {//用于遍历线段树
	if (l(p, id) == r(p, id)) {
		if (cnt(p, id) == 1)//如果该点权值为1，将答案数组的该位置记为答案
			a[l(p, id)] = id + 'a';
		return;
	}
	spread(p, id);
	final(ls, id);
	final(rs, id);
}
int main() {
	scanf("%d %d", &n, &q);
	scanf("%s", a + 1);
	for (int i = 0; i < 26; i++)//建立26棵线段树
		build(1, 1, n, i);
	int l, r, opt;
	while (q--) {
		scanf("%d %d %d", &l, &r, &opt);
		if (opt == 1) {
			int f = l, len;
			for (int i = 0; i < 26; i++) {
				len = ask(1, l, r, i);
				if (len == 0)//没有该字符直接跳过
					continue;
				change(1, l, r, 0, i);//先全部置零
				change(1, f, f + len - 1, 1, i);//依次向右平摊
				f += len;
			}
		} else {
			int f = r, len;
			for (int i = 0; i < 26; i++) {
				len = ask(1, l, r, i);
				if (len == 0)
					continue;
				change(1, l, r, 0, i);
				change(1, f - len + 1, f, 1, i);//依次向左平摊
				f -= len;
			}
		}
	}
	memset(a, 0, sizeof(a));
	for (int i = 0; i < 26; i++) {//遍历所有线段树
		final(1, i);
	}
	for (int i = 1; i <= n; i++)//输出答案
		putchar(a[i]);
	return 0;
}
```

---

## 作者：a17436223 (赞：8)

题意:
$n$个小写字母,m次操作
$op==1$:对$[l,r]$区间内的元素进行升序排序
$op==0$:对$[l,r]$区间内的元素进行降序排序
打印执行完所有操作后的结果

解法:
用可分裂合并的线段树,即建$n$个动态开点的权值线段树,用$set$维护区间,分裂的时候从$set$中找到对应的区间分裂即可.

顺便说下这玩意时间复杂度为$O((n+m)logn)$,在这题中跑的真是飞快,最慢的点也只要$140ms$

```cpp
#include <bits/stdc++.h>
#define Fi first
#define Se second
using namespace std;
const int N=3e5+10;
int s[N*20],ls[N*20],rs[N*20],rt[N],flag[N],ncnt;
set<int> st;
void update(int l,int r,int &k,int p)
{
    if(!k) k=++ncnt;
    s[k]++;
    if(l==r) return ;
    int m=l+r>>1;
    if(p<=m) update(l,m,ls[k],p);
    else update(m+1,r,rs[k],p);
}
//线段树分裂核心操作
void tear(int &x,int y,int k,int flag)//对y线段树进行分裂,使得y线段树保留下k个元素,剩下的给x线段树
{
    if(s[y]==k) return ;
    x=++ncnt;//新建结点
    s[x]=s[y]-k;//减去当前结点元素数量
    s[y]=k;//保留元素
    if(s[ls[y]]+s[rs[y]]==0) return ;//如果元素有重复就必须加这句,因为一个结点下面元素不一定恰好等于1,反正没有儿子就停止
    //升序:
    //对于先看左儿子结点的数量是否大于等于k,如果满足说明
    //①左边中有部分是,可能同时存在x和y线段树的,递归左儿子.
    //②右边都是x线段树的,x的右儿子直接把y的右儿子拿来用,然后把y右儿子删了
    //如果不满足>=k 接着递归右儿子
    //降序:把x和y的左右儿子互换然后同上
    //
    if(flag) swap(ls[y],rs[y]),swap(ls[x],rs[x]);
    if(k<=s[ls[y]]) tear(ls[x],ls[y],k,flag),rs[x]=rs[y],rs[y]=0;
    else  tear(rs[x],rs[y],k-s[ls[y]],flag);
    if(flag) swap(ls[y],rs[y]),swap(ls[x],rs[x]);
}
//把位置p所在的线段树分裂出去
auto split(int p)
{
    auto it = st.lower_bound(p);
    if(it!=st.end()&&*it==p) return it;
    it--;
    tear(rt[p],rt[*it],p-*it,flag[p]=flag[*it]);
    return st.insert(p).Fi;
}
void merge(int &x,int y)//线段树合并 把y线段树合并到y上
{
    if(!x||!y){x|=y;return ;}
    s[x]+=s[y];
    merge(ls[x],ls[y]);
    merge(rs[x],rs[y]);
}
int cnt[35];
void query(int l,int r,int k)//统计答案
{
    if(l==r||s[k]==0) {cnt[l]+=s[k];return ;}
    int m=l+r>>1;
    if(ls[k]) query(l,m,ls[k]);
    if(rs[k]) query(m+1,r,rs[k]);
}
int main()
{
    int n,m;scanf("%d%d",&n,&m);
    getchar();
    for(int i=1;i<=n;i++)
    {
        int x=getchar()-'a'+1;
        update(1,30,rt[i],x);
        st.insert(i);
    }
    for(int i=1;i<=m;i++)
    {
        int l,r,op;
        scanf("%d%d%d",&l,&r,&op);
        auto it2=split(r+1),it1=split(l);
        for(auto it=++it1;it!=it2;it++) merge(rt[l],rt[*it]);
        flag[l]=(op^1);st.erase(it1,it2);
    }
    for(auto e:st)
    {
        memset(cnt,0,sizeof cnt);
        query(1,30,rt[e]);
        if(flag[e]==0)
        {
            for(int j=0;j<30;j++)
                for(int k=1;k<=cnt[j];k++)
                    printf("%c",j+'a'-1);
        }
        else
        {
            for(int j=30;j>=0;j--)
                for(int k=1;k<=cnt[j];k++)
                    printf("%c",j+'a'-1);
        }
    }
    return 0;
}
/*

*/

```





---

## 作者：Ebola (赞：8)

### 广告：[我的博客](http://ebola.blogwo.com/)

考虑用权值线段树来解这道题

考虑到给定的字符串仅包含小写字母，因此，我们对每个字母分别先建一棵空树，一共26棵，范围都是1~n

这些线段树的含义是这样的：对于任意一个字母，它所对应的线段树的节点[l,r]，表示在字符串的[l,r]区间中有多少个这个字母

因此，我们初始化这26棵线段树时，对于字符串的第i位，对相应的线段树进行add(i,i,1)操作

接下来考虑排序操作

首先我们开一个桶排数组sum[26+5]，表示每个字母在待操作区间中的出现次数，sum[i]的值就是对相应线段树进行query(l,r)的结果

然后我们需要清空所有线段树的[l,r]区间，这里可以搞一个modify标记，表示将相应节点的add标记以及权值清零，注意pushdown时优先处理modify标记

然后我们按顺序把这些字母加回去，举个升序排序的例子：区间[3,10]中有3个a，4个b，1个c，那我们就对a相应的线段树进行add(3,5,1)，对b相应的线段树进行add(6,9,1)，对c相应的线段树进行add(10,10,1)，降序排序倒过来搞就行了

最后输出就枚举i=1~n，然后对于所有i，对每个线段树都进行query(i,i)，如果query的结果非0，那就输出相应的字母

时间复杂度O(n log n * 26)

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,q;
char s[100010];
struct Node
{
	Node *lson,*rson;
	int v,add,modify;
};
Node *rt[30];
int sum[30];

void pushdown(Node* &o,int l,int r)
{
	int mid=(l+r)/2,k=o->add,tag=o->modify;
	o->add=o->modify=0;
	if(l==r) return;
	if(tag)
	{
		o->lson->modify=1;
		o->rson->modify=1;
		o->lson->add=0;
		o->rson->add=0;
		o->lson->v=0;
		o->rson->v=0;
	}
	o->lson->add+=k;
	o->rson->add+=k;
	o->lson->v+=k*(mid-l+1);
	o->rson->v+=k*(r-mid);
}

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->v=o->add=o->modify=0;
	o->lson=o->rson=NULL;
	if(l==r) return;
	int mid=(l+r)/2;
	build(o->lson,l,mid);
	build(o->rson,mid+1,r);
}

void add(Node* &o,int l,int r,int x,int y,int k)
{
	if(l>=x&&r<=y)
	{
		o->v+=k*(r-l+1);
		o->add+=k;
		return;
	}
	if(o->add||o->modify) pushdown(o,l,r);
	int mid=(l+r)/2;
	if(mid>=x) add(o->lson,l,mid,x,y,k);
	if(mid<y) add(o->rson,mid+1,r,x,y,k);
	o->v=o->lson->v+o->rson->v;
}

void clear(Node* &o,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)
	{
		o->v=0;
		o->modify=1;
		o->add=0;
		return;
	}
	if(o->add||o->modify) pushdown(o,l,r);
	int mid=(l+r)/2;
	if(mid>=x) clear(o->lson,l,mid,x,y);
	if(mid<y) clear(o->rson,mid+1,r,x,y);
	o->v=o->lson->v+o->rson->v;
}

int query(Node* &o,int l,int r,int x,int y)
{
	if(l>=x&&r<=y) return o->v;
	if(o->add||o->modify) pushdown(o,l,r);
	int mid=(l+r)/2,res=0;
	if(mid>=x) res+=query(o->lson,l,mid,x,y);
	if(mid<y) res+=query(o->rson,mid+1,r,x,y);
	return res;
}

int main()
{
	int l,r,k;
	scanf("%d%d%s",&n,&q,s+1);
	for(int i=0;i<26;i++) build(rt[i],1,n);
	for(int i=1;i<=n;i++) add(rt[s[i]-'a'],1,n,i,i,1);
	for(int T=1;T<=q;T++)
	{
		scanf("%d%d%d",&l,&r,&k);
		memset(sum,0,sizeof(sum));
		for(int i=0;i<26;i++)
		{
			sum[i]=query(rt[i],1,n,l,r);
			clear(rt[i],1,n,l,r);
		}
		if(k==1)
		{
			int p=l;
			for(int i=0;i<26;i++)
				if(sum[i])
				{
					add(rt[i],1,n,p,p+sum[i]-1,1);
					p+=sum[i];
				}
		}
		else
		{
			int p=r;
			for(int i=0;i<26;i++)
				if(sum[i])
				{
					add(rt[i],1,n,p-sum[i]+1,p,1);
					p-=sum[i];
				}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<26;j++)
			if(query(rt[j],1,n,i,i)!=0){putchar('a'+j);break;}
	return 0;
}

```

---

## 作者：ezoiHY (赞：5)

### 这道题好猥琐啊啊啊啊啊啊
写了一个上午啊啊啊啊
没有在update里写pushup啊啊啊啊

##### 题目大意：
给你一个字符串s，有q个操作
l r 1 :把sl..rsl..r按升序排序 
l r 0 :把sl..rsl..r按降序排序

#### Solution：
我们考虑建26棵线段树，第i棵线段树的[x,y]表示在[x,y]中一共有多少个字母'a'+i-1
至于修改时我们可以以升序为例，从a至z按顺序往前丢，记得要清空区间
同理，降序反过来就是了

#### Code:
~~我们可以用sort啊啊，只不过会TLE~~
```
#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
 
using namespace std;
 
int n,q;
char s[100001];
 
bool cmp(char a,char b){
    return a>b;
}
 
int main(){
    scanf("%d%d%s",&n,&q,s);
    for(int i=1;i<=q;i++){
        int l,r,x;
        scanf("%d%d%d",&l,&r,&x);
        if(x==1)sort(s+l-1,s+r);
        else sort(s+l-1,s+r,cmp);
        printf("%s\n",s);
    }
    printf("\n%s",s);
    return 0;
}
```
这里才是正解代码
```
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

char s[1000001];     
int n,m,sum[27][400001],lazy[27][400001];

inline int rd(){
	register int x=0,y=1;
	register char c=getchar();
	while(c>'9' or c<'0'){
		if(c=='-'){
			y=-1;
		}
		c=getchar();
	}
	while(c>='0' and c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*y;
}

inline void pushup(int o,int rt){
	sum[rt][o]=sum[rt][o<<1]+sum[rt][o<<1|1];
}

inline void pushdown(int o,int l,int r,int rt){
	if(lazy[rt][o]!=-1){
		int mid=(l+r)>>1;
		sum[rt][o]=lazy[rt][o]*(r-l+1);
		sum[rt][o<<1]=lazy[rt][o]*(mid-l+1);
		sum[rt][o<<1|1]=lazy[rt][o]*(r-mid);
		lazy[rt][o<<1]=lazy[rt][o<<1|1]=lazy[rt][o];
		lazy[rt][o]=-1;
	}
}

void build(int o,int l,int r){
	if(l==r){
		sum[s[l]-'a'+1][o]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	for(int i=1;i<=26;i++)pushup(o,i);
}

inline int query(int o,int l,int r,int x,int y,int rt){
	if(x<=l and y>=r){
		return sum[rt][o];
	}
	pushdown(o,l,r,rt);
	int mid=(l+r)>>1,ret=0;
	if(x<=mid)ret+=query(o<<1,l,mid,x,y,rt);
	if(y>mid)ret+=query(o<<1|1,mid+1,r,x,y,rt);
	return ret;
}

inline void update(int o,int l,int r,int x,int y,int rt,int v){
	if(x<=l and y>=r){
		lazy[rt][o]=v;
		sum[rt][o]=v*(r-l+1);
		return;
	}
	pushdown(o,l,r,rt);
	int mid=(l+r)>>1;
	if(x<=mid)update(o<<1,l,mid,x,y,rt,v);
	if(y>mid)update(o<<1|1,mid+1,r,x,y,rt,v);
	pushup(o,rt);
}

void output(int o,int l,int r){
	if(l==r){
		for(int i=1;i<=26;i++){
			if(sum[i][o]){
				s[l]='a'+i-1;
				break;
			}
		}
		return;
	}
	for(int i=1;i<=26;i++)pushdown(o,l,r,i);
	int mid=(l+r)>>1;
	output(o<<1,l,mid);
	output(o<<1|1,mid+1,r);
}

int main(){
	for(int i=1;i<=26;i++)memset(lazy[i],-1,sizeof(lazy[i]));
	n=rd(),m=rd();
	scanf("%s",s+1);
	build(1,1,n);
	while(m--){
		int x=rd(),y=rd();
		if(rd()){
			int tmp=x-1;
			for(int i=1;i<=26;i++){
				int cas=query(1,1,n,x,y,i);
				if(!cas)continue;
				update(1,1,n,x,y,i,0);
				update(1,1,n,tmp+1,tmp+cas,i,1);tmp=tmp+cas;
			}
		}else {
			int tmp=x-1;
			for(int i=26;i>=1;i--){
				int cas=query(1,1,n,x,y,i);
				if(!cas)continue;
				update(1,1,n,x,y,i,0);
				update(1,1,n,tmp+1,tmp+cas,i,1);tmp=tmp+cas;
			}
		}
	}
	output(1,1,n);
	printf("%s\n",s+1);
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：3)

[博客食用效果更佳](https://www.luogu.org/blog/oldherd/solution-CF558E)  
我们考虑建起26棵线段树，每棵维护一种字母，这样子就可以很简单地维护每种字母出现地位置信息。  
对于升序排序，我们从A到Z依次查询所有线段树。统计到目前线段树之前出现的字母与个数p，查询当前字母个数tt，若操作的区间为[t, g]，则当前字母在排序后的区间应当为[t+p, t+p+tt-1]。详情参照代码。降序排序则从Z到A遍历。  
关于输出，我们遍历每一棵线段树，将其字母所占的位置赋值到一个字符数组中，然后统一输出即可。  
附上ac代码：  
```cpp
#include <cstdio>

using namespace std;

const int sz = 7000010, maxn = 100010;

inline void read(int &x) {
	char ch = getchar();
	x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x<<3)+(x<<1)+(ch&15), ch = getchar();	
}

struct stree{
	int ls, rs, val, laz;
}t[sz];
int root[30], tot = 1;

inline int newnode() {
	t[tot].ls = t[tot].rs = t[tot].val = 0; t[tot].laz = -1;
	return tot++;
}

inline void spread(int p, int ll, int lr) {
	if(!t[p].ls) t[p].ls = newnode();
	if(!t[p].rs) t[p].rs = newnode();
	if(t[p].laz == -1) return;
	t[t[p].ls].val = ll * t[p].laz; t[t[p].ls].laz = t[p].laz;
	t[t[p].rs].val = lr * t[p].laz; t[t[p].rs].laz = t[p].laz;
	t[p].laz = -1;
}

inline void change(int p, int lp, int rp, int l, int r, int v) {
	if(l <= lp && rp <= r) { t[p].val = (rp-lp+1) * v; t[p].laz = v; return; }
	int mid = (lp + rp) >> 1;
	spread(p, mid-lp+1, rp-mid);
	if(l <= mid) change(t[p].ls, lp, mid, l, r, v);
	if(r > mid) change(t[p].rs, mid+1, rp, l, r, v);
	t[p].val = t[t[p].ls].val + t[t[p].rs].val;
}

inline int query(int p, int lp, int rp, int l, int r) {
	if(l <= lp && rp <= r) return t[p].val;
	int mid = (lp + rp) >> 1;
	spread(p, mid-lp+1, rp-mid);
	int ans = 0;
	if(l <= mid) ans += query(t[p].ls, lp, mid, l, r);
	if(r > mid) ans += query(t[p].rs, mid+1, rp, l, r);
	return ans;
}

char s[maxn];

inline void putree(int p, int lp, int rp, char ch) {
	if(t[p].val == rp-lp+1)	{
		for(int i = lp; i <= rp; i++) s[i] = ch;
		return;	
	}
	if(lp == rp) return;
	int mid = (lp + rp) >> 1;
	spread(p, mid-lp+1, rp-mid);
	if(t[p].ls && t[t[p].ls].val) putree(t[p].ls, lp, mid, ch);
	if(t[p].rs && t[t[p].rs].val) putree(t[p].rs, mid+1, rp, ch);
}

int main() {
	int n, m, t, g, c;
	char ch;
	read(n); read(m);
	for(int i = 0; i < 26; i++) root[i] = newnode();
	for(int i = 1; i <= n; i++) {
		do{
			ch = getchar();
		}while(ch < 'a' || ch > 'z');
		change(root[ch-'a'], 1, n, i, i, 1);
	}
	while(m--) {
		read(t); read(g); read(c);
		int p = 0, tt;
		if(c == 1) {
			for(int i = 0; i < 26; i++) {
				tt = query(root[i], 1, n, t, g);
				if(!tt) continue;
				change(root[i], 1, n, t, g, 0);
				change(root[i], 1, n, t+p, t+p+tt-1, 1);
				p += tt;
			}
		} else {
			for(int i = 25; i > -1; --i) {
				tt = query(root[i], 1, n, t, g);
				if(!tt) continue;
				change(root[i], 1, n, t, g, 0);
				change(root[i], 1, n, t+p, t+p+tt-1, 1);
				p += tt;
			}
		}
	}
	for(int i = 0; i < 26; i++) 
		putree(root[i], 1, n, 'a'+i);
	for(int i = 1; i <= n; i++) putchar(s[i]);
	return 0;	
}
```
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后再次安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)  

---

## 作者：MaxBlazeResFire (赞：2)

**题意**：给定长度为 $n$ 的小写字符序列。你需要维护区间升序或者降序排序，只需在最后输出整个序列。

**解法**：分块。优雅的暴力。

我们考虑将整个序列分为 $\sqrt n$ 块，每块的长度是 $\sqrt n$.

我们维护每个点的具体数值 $a_i$ 与每个块的值域桶 $buc_{i,1\cdots 26}$. 额外地，我们还需要维护一个整块的升/降序标记，以保证复杂度。

首先说明一个子问题：若一个整块有标记，并已知每种字符各有多少个，该如何暴力维护具体的点值？只需维护一个按照字符集顺序，依照标记升/降序扫描的指针即可（其实就是一个裸桶排）。

当修改一个区间 $[l,r]$ 时，有以下两种情况：

1. $[l,r]$ 被一个块完整包含。此时我们暴力修改该块的 $a$ 数组（若有标记，则把标记暴力做掉）。一次复杂度 $O(\sqrt n)$.

2. $[l,r]$ 越过若干个完整的块，并在两侧有零散部分。

对于情况 2 ，首先若零散区间有标记，我们先把标记暴力做了。

然后考虑先把整个区间的桶暴力统计出来。具体来说，散块的 $a$ 零散加，整块就直接将 $buc$ 统计入贡献。这里复杂度 $O(\sqrt n|\Sigma|)$. 然后我们依据询问的升/降序先将离散块和整块桶分布统计出来。 

**具体来说，在这一步我们对于每个块，都可以知道包含于其中的每个字符各有多少。** 

我们知道块的长度，只需要从左到右，按照字符集降/升序，用一个指针扫描字符集，一步步试探性维护即可。即统计一个已加入的字符数量，若按顺序将下一种字符全部加入仍然不够区间长度则加入，否则只加入一部分。这里的复杂度 $O(\sqrt n)$.

然后，我们对于零散的块，用已知的分布暴力修改。复杂度 $O(\sqrt n)$.

对于整块，打上升/降序排列标记。复杂度 $O(\sqrt n)$.

这样下来，我们只需要在最后遍历所有的块，把没有做掉的标记暴力做掉即可。

故整个过程的复杂度为 $O(q\sqrt n|\Sigma|)$. 可以通过此题。而且常数很小，不开 O2 的情况下还能比各种线段树跑得快。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005
#define Sqn 330

char s[MAXN];
int a[MAXN] = {0},laz[Sqn] = {0};
int n,q,num = 0,sqt = 0,st[Sqn] = {0},ed[Sqn] = {0},len[Sqn] = {0},bel[MAXN] = {0};

vector<int> buc[Sqn];

inline vector<int> get_charset( int l , int r ){
	vector<int> buc( 27 );
	for( int i = l ; i <= r ; i ++ ) buc[a[i]] ++;
	return buc;
}

inline void replay( int block , int l , int r , vector<int> bucket , int type , int resize = 0 ){
	if( !resize ) for( int i = l ; i <= r ; i ++ ) buc[block][a[i]] --;
	if( type == 1 ){
		int now = 26;
		for( int i = l ; i <= r ; i ++ ){ while( !bucket[now] ) now --; a[i] = now; bucket[now] --; }
	}
	else if( type == 2 ){
		int now = 1;
		for( int i = l ; i <= r ; i ++ ){ while( !bucket[now] ) now ++; a[i] = now; bucket[now] --; }
	}
	if( !resize ) for( int i = l ; i <= r ; i ++ ) buc[block][a[i]] ++;
}

inline void modify( int l , int r , int k ){
	if( k == 1 ){
		if( bel[l] == bel[r] ){
			int Block = bel[l];
			if( laz[Block] ) replay( Block , st[Block] , ed[Block] , buc[Block] , laz[Block] , 1 ),laz[Block] = 0;
			replay( Block , l , r , get_charset( l , r ) , k );
			return;
		}
		else{
			vector<int> Buc( 27 ),Lbuc( 27 ),Rbuc( 27 );
			int Sblock = bel[l],Eblock = bel[r],now;
			if( laz[Sblock] ) replay( Sblock , st[Sblock] , ed[Sblock] , buc[Sblock] , laz[Sblock] , 1 ),laz[Sblock] = 0;
			if( laz[Eblock] ) replay( Eblock , st[Eblock] , ed[Eblock] , buc[Eblock] , laz[Eblock] , 1 ),laz[Eblock] = 0;
			for( int i = l ; i <= ed[Sblock] ; i ++ ) Buc[a[i]] ++;
			for( int i = st[Eblock] ; i <= r ; i ++ ) Buc[a[i]] ++;
			for( int i = Sblock + 1 ; i <= Eblock - 1 ; i ++ )
				for( int j = 1 ; j <= 26 ; j ++ ) Buc[j] += buc[i][j];
				
			int L = ed[Sblock] - l + 1,S = 0; now = 26;
			while( S + Buc[now] < L ){ Lbuc[now] = Buc[now]; S += Buc[now],Buc[now] = 0,now --; }
			Lbuc[now] = L - S,Buc[now] -= L - S;
			
			int R = r - st[Eblock] + 1; S = 0; now = 1;
			while( S + Buc[now] < R ){ Rbuc[now] = Buc[now]; S += Buc[now],Buc[now] = 0,now ++; }
			Rbuc[now] = R - S,Buc[now] -= R - S;
			
			replay( Sblock , l , ed[Sblock] , Lbuc , k );
			replay( Eblock , st[Eblock] , r , Rbuc , k );
			now = 26;
			for( int i = Sblock + 1 ; i <= Eblock - 1 ; i ++ ){
				fill( buc[i].begin() , buc[i].end() , 0 );
				int Aim = len[i]; S = 0;
				while( S + Buc[now] < Aim ){ S += Buc[now]; buc[i][now] = Buc[now],Buc[now] = 0,now --; }
				buc[i][now] = Aim - S; Buc[now] -= Aim - S;
				laz[i] = k;
			}
		}
	}
	else if( k == 2 ){
		if( bel[l] == bel[r] ){
			int Block = bel[r];
			if( laz[Block] ) replay( Block , st[Block] , ed[Block] , buc[Block] , laz[Block] , 1 ),laz[Block] = 0;
			replay( Block , l , r , get_charset( l , r ) , k );
			return;
		}
		else{
			vector<int> Buc( 27 ),Lbuc( 27 ),Rbuc( 27 );
			int Sblock = bel[l],Eblock = bel[r];
			if( laz[Sblock] ) replay( Sblock , st[Sblock] , ed[Sblock] , buc[Sblock] , laz[Sblock] , 1 ),laz[Sblock] = 0;
			if( laz[Eblock] ) replay( Eblock , st[Eblock] , ed[Eblock] , buc[Eblock] , laz[Eblock] , 1 ),laz[Eblock] = 0;
			for( int i = l ; i <= ed[Sblock] ; i ++ ) Buc[a[i]] ++;
			for( int i = st[Eblock] ; i <= r ; i ++ ) Buc[a[i]] ++;
			for( int i = Sblock + 1 ; i <= Eblock - 1 ; i ++ )
				for( int j = 1 ; j <= 26 ; j ++ ) Buc[j] += buc[i][j];
			
			int L = ed[Sblock] - l + 1,S = 0,now = 1;
			while( S + Buc[now] < L ){ Lbuc[now] = Buc[now]; S += Buc[now],Buc[now] = 0,now ++; }
			Lbuc[now] = L - S,Buc[now] -= L - S;
			
			int R = r - st[Eblock] + 1; S = 0; now = 26;
			while( S + Buc[now] < R ){ Rbuc[now] = Buc[now]; S += Buc[now],Buc[now] = 0,now --; }
			Rbuc[now] = R - S,Buc[now] -= R - S;
			
			replay( Sblock , l , ed[Sblock] , Lbuc , k );
			replay( Eblock , st[Eblock] , r , Rbuc , k );
			now = 1;
			for( int i = Sblock + 1 ; i <= Eblock - 1 ; i ++ ){
				fill( buc[i].begin() , buc[i].end() , 0 );
				int Aim = len[i]; S = 0;
				while( S + Buc[now] < Aim ){ S += Buc[now]; buc[i][now] = Buc[now],Buc[now] = 0,now ++; }
				buc[i][now] = Aim - S; Buc[now] -= Aim - S;
				laz[i] = k;
			}
		}
	}
}

inline void query(){
	for( int i = 1 ; i <= num ; i ++ )
		if( laz[i] ) replay( i , st[i] , ed[i] , buc[i] , laz[i] ),laz[i] = 0;
	for( int i = 1 ; i <= n ; i ++ ) printf("%c",a[i] + 'a' - 1);
}

signed main(){
	scanf("%lld%lld",&n,&q); scanf("%s",s + 1);
	for( int i = 1 ; i <= n ; i ++ ) a[i] = s[i] - 'a' + 1;
	sqt = sqrt( n ) + 1;
	for( int i = 1 ; i <= n ; i ++ ) bel[i] = ( i - 1 ) / sqt + 1;
	for( int i = 1 ; i <= n ; i ++ ) ed[bel[i]] = i;
	for( int i = n ; i >= 1 ; i -- ) st[bel[i]] = i;
	num = bel[n];
	for( int i = 1 ; i <= num ; i ++ ) len[i] = ed[i] - st[i] + 1,buc[i].resize( 27 );
	for( int i = 1 ; i <= n ; i ++ ) buc[bel[i]][a[i]] ++;
	for( int i = 1 ; i <= q ; i ++ ){
		int l,r,k; scanf("%lld%lld%lld",&l,&r,&k);
		modify( l , r , k + 1 );
	}
	query(); puts("");
	return 0;
}
```


---

