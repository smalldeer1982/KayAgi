# MEX Queries

## 题目描述

You are given a set of integer numbers, initially it is empty. You should perform $ n $ queries.

There are three different types of queries:

- 1 $ l $ $ r $ — Add all missing numbers from the interval $ [l,r] $
- 2 $ l $ $ r $ — Remove all present numbers from the interval $ [l,r] $
- 3 $ l $ $ r $ — Invert the interval $ [l,r] $ — add all missing and remove all present numbers from the interval $ [l,r] $

After each query you should output MEX of the set — the smallest positive (MEX $ >=1 $ ) integer number which is not presented in the set.

## 说明/提示

Here are contents of the set after each query in the first example:

1. $ {3,4} $ — the interval $ [3,4] $ is added
2. $ {1,2,5,6} $ — numbers $ {3,4} $ from the interval $ [1,6] $ got deleted and all the others are added
3. $ {5,6} $ — numbers $ {1,2} $ got deleted

## 样例 #1

### 输入

```
3
1 3 4
3 1 6
2 1 3
```

### 输出

```
1
3
1
```

## 样例 #2

### 输入

```
4
1 1 3
3 5 6
2 4 4
3 1 6
```

### 输出

```
4
4
4
1
```

# 题解

## 作者：Unnamed114514 (赞：20)

### 前置知识 
[珂朵莉树](https://pzj.blog.luogu.org/ke-duo-li-shu)，是一种支持区间覆盖，区间取反，区间加，区间乘等操作，在**随机数据**下，复杂度接近线性。对于本题，虽然不是随机数据，但是 CF 放过了，时间在最优解的大约 3 倍。

首先，$1$、$2$、$3$ 操作都是珂朵莉树的板子：区间覆盖，区间取反，重点是查询：

首先，我们有了一个 `set` 它里面存储了各个区间的权值，若为 0，则表示它未加入或已删除，输出它的左端点即可，即一次暴力查找。因为有解，所以 $10^{18}+1$ 永远为 $0$。具体细节见代码：
```cpp
#include<bits/stdc++.h>
#define int long long//不开 long long 见祖宗
#define se set<node>::iterator//宏定义迭代器
using namespace std;
inline int read(){
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return res;
}//快读
struct node{
    int l,r;
	mutable int val;//区间端点、权值
    bool operator<(const node &t) const{
		return l<t.l;
	}

};
int n;
set<node> s;
se it,itl,itr;
inline se split(int pos){
    it=s.lower_bound(node({pos}));
    if(it!=s.end()&&it->l==pos)
		return it;
    --it;
    int l=it->l,r=it->r,v=it->val;
    s.erase(it);
    s.insert(node({l,pos-1,v}));
    return s.insert(node({pos,r,v})).first;
}//分裂成 2 个区间
inline void assign(int l,int r,int val){
    itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node({l,r,val}));
}//区间覆盖
inline void rever(int l,int r){
    itr=split(r+1),itl=split(l);
    for(se it=itl;it!=itr;++it)
        it->val=!it->val;
}//区间取反
signed main(){
    n=read();
    s.insert(node({1,(int)1e18+1,0}));//初始化为 0，且 1e18+1 一定是一个接
    while(n--){
        int flag=read(),l=read(),r=read();
        if(flag==1)
			assign(l,r,1);//覆盖
        else if(flag==2)
			assign(l,r,0);//覆盖
        else if(flag==3)
			rever(l,r);//翻转
        for(it=s.begin();it!=s.end();++it)
            if(!it->val){
                printf("%lld\n",it->l);
                break;
            }//暴力查询
    }
    return 0;
}
```

---

## 作者：Acestar (赞：18)

本题要支持区间修改和区间查询，于是可以用**线段树**，由于 $l,r≤10^{18}$ 并且只需要查找位置，于是就能很容易地想到**离散化**。

用 $sum$ 数组存区间和，$tag$ 数组存区间赋值，$rev$ 数组存区间翻转。

再开一个 $q$ 数组，用来离散化。因为要离散化，所以是离线的。把每次操作的 $l$ 和 $r$ 存进 $q$ ，并把 $r+1$ 存进 $q$ ,然后将 $q$ 数组进行 排序+去重，就得到了原操作的大小关系，并且映射到了 $1-n$。

其实也可以用 $map$，下角标为 $1-n$，值为 $l,r,r+1$，但是我这里用的是第一种。

对于每次询问，先从根开始，如果 $sum<$区间长度，说明存在 $0$， 只需要再继续往下查找左子树和右子树（**注意顺序**，要**先查找左子树**），直到叶节点，最后将查找到的位置对应值的值输出即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long

using namespace std;

const int N = 12e5+10;	//因为询问个数最大是1e5，每次询问都会加三个值，而线段树要开4倍，所以是12e5
const int M = 1e5+10;

int n,m;
int t[M],l[M],r[M],q[M<<2];	//q[]:离散化数组
int sum[N],tag[N],rev[N];
//sum[]:区间和，tag[]:区间赋值，rev[]:区间翻转 

inline int read()	//快读 
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}

inline void pushup(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

inline void build(int l,int r,int rt)
{
	//初始全为0，tag为-1
	sum[rt]=0;
	rev[rt]=0;
	tag[rt]=-1;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	pushup(rt);
}

inline void pushdown(int l,int r,int rt)
{
	int mid=(l+r)>>1;
	if(tag[rt]!=-1)		//如果有tag，那么就清空rev 
	{
		tag[rt<<1]=tag[rt];
		tag[rt<<1|1]=tag[rt];
		rev[rt<<1]=0;
		rev[rt<<1|1]=0;
		if(tag[rt])
		{
			sum[rt<<1]=mid-l+1;
			sum[rt<<1|1]=r-mid;
		}
		else
		{
			sum[rt<<1]=0;
			sum[rt<<1|1]=0;
		}
		tag[rt]=-1;
	}
	if(rev[rt])		//如果有rev，那么如果有tag，就将tag^1,否则将rev^1 
	{
		if(tag[rt<<1]!=-1) tag[rt<<1]^=1;
		else rev[rt<<1]^=1;
		if(tag[rt<<1|1]!=-1) tag[rt<<1|1]^=1;
		else rev[rt<<1|1]^=1;
		sum[rt<<1]=mid-l+1-sum[rt<<1];
		sum[rt<<1|1]=r-mid-sum[rt<<1|1];
		rev[rt]=0; 
	}
}

inline void update(int t,int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R)
	{
		if(l==r)
		{
			if(t==1) sum[rt]=1;
			else if(t==2) sum[rt]=0;
			else sum[rt]^=1;
		}
		else
		{
			if(t==1)	//区间赋值为1
			{
				tag[rt]=1;
				rev[rt]=0;
				sum[rt]=r-l+1;
			}
			if(t==2)	//区间赋值为0
			{
				tag[rt]=0;
				rev[rt]=0;
				sum[rt]=0;
			}
			if(t==3)	//区间翻转
			{
				if(tag[rt]!=-1) tag[rt]^=1;
				else rev[rt]^=1;
				sum[rt]=r-l+1-sum[rt];
			}
		}
		return;
	}
	pushdown(l,r,rt);
	int mid=(l+r)>>1;
	if(L<=mid) update(t,L,R,l,mid,rt<<1);
	if(mid<R) update(t,L,R,mid+1,r,rt<<1|1);
	pushup(rt);
}

inline int query(int l,int r,int rt)
{
	if(l==r) return l;
	pushdown(l,r,rt);
	int mid=(l+r)>>1;
	//如果sum<区间长度，说明存在0
	if(sum[rt<<1]<mid-l+1) return query(l,mid,rt<<1);
	else return query(mid+1,r,rt<<1|1);
}

signed main()
{
	m=read();
	q[++n]=1;
	for(int i=1; i<=m; i++)
	{
		t[i]=read(),l[i]=read(),r[i]=read();
		q[++n]=l[i],q[++n]=r[i],q[++n]=r[i]+1;	//离散化初始数组 
	}
	//离散化 
	sort(q+1,q+1+n);			//排序
	n=unique(q+1,q+1+n)-(q+1);	//去重
	build(1,n,1);
	for(int i=1; i<=m; i++)
	{
		l[i]=lower_bound(q+1,q+1+n,l[i])-q;
		r[i]=lower_bound(q+1,q+1+n,r[i])-q;
		update(t[i],l[i],r[i],1,n,1);
		printf("%lld\n",q[query(1,n,1)]);
	}
	return 0;
}
```

---

## 作者：Grisses (赞：18)

[题面](https://www.luogu.com.cn/problem/CF817F)

本题看完后我们发现它应该需要维护 3 种操作：

> - 将 l 到 r 的区间用 1 覆盖
>
> - 将 l 到 r 的区间用 0 覆盖
>
> - 将 l 到 r 的区间取反
>
> 区间的初始值都为 0。
>
> 在每次操作后输出第一个 0 的下标。

对于区间修改的问题，很明显是线段树。

只不过。。。~~细节多得让人疯~~

## 1. 对于懒惰标记，我们有 4 种情况：

- 0：表示没有标记

- 1：表示要用 0 覆盖

- 2：表示要用 1 覆盖

- 3：表示要取反

所以，下降懒惰标记也。。。

```cpp
  void down(int q){
      if(c[q].p&&c[q].l!=c[q].r){//有标记
          int l=q<<1,r=q<<1|1;
          if(c[q].p!=3){//这个懒惰标记是覆盖
              c[l].p=c[q].p;c[l].v=(c[q].p-1)*(c[l].r-c[l].l+1);
              c[r].p=c[q].p;c[r].v=(c[q].p-1)*(c[r].r-c[r].l+1);//那就直接覆盖
          }
          else{//这个标记是反转
              if(c[l].p==0)c[l].v=c[l].r-c[l].l+1-c[l].v,c[l].p=3;//没有就直接修改
              else if(c[l].p==1)c[l].v=c[l].r-c[l].l+1,c[l].p=2;//如果用0覆盖，就换成用1覆盖
              else if(c[l].p==2)c[l].v=0,c[l].p=1;//如果用1覆盖，就换成用0覆盖
              else c[l].v=c[l].r-c[l].l+1-c[l].v,c[l].p=0;//如果标记了反转，直接改
              if(c[r].p==0)c[r].v=c[r].r-c[r].l+1-c[r].v,c[r].p=3;
              else if(c[r].p==1)c[r].v=c[r].r-c[r].l+1,c[r].p=2;
              else if(c[r].p==2)c[r].v=0,c[r].p=1;
              else c[r].v=c[r].r-c[r].l+1-c[r].v,c[r].p=0;//同理
          }
      }
      c[q].p=0;
  }
```

## 2.对于区间修改，我们有两种：

#### 1.覆盖

```cpp
  void Add(int q,int l,int r,int x){
          if(l<=c[q].l&&c[q].r<=r){c[q].p=x;c[q].v=(x-1)*(c[q].r-c[q].l+1);return;}//修改整个区间，直接改懒惰标记
          down(q);
          int mid=c[q].l+c[q].r>>1;
          if(l<=mid)Add(q<<1,l,r,x);
          if(mid<r)Add(q<<1|1,l,r,x);
          c[q].v=c[q<<1].v+c[q<<1|1].v;
   }
```

#### 2.反转
```cpp
  void Swap(int q,int l,int r){
      if(l<=c[q].l&&c[q].r<=r){//反转整个区间
          if(c[q].p==1||c[q].p==2){//原本是覆盖，那就反着覆盖
              c[q].v=c[q].r-c[q].l+1-c[q].v;
              c[q].p=(c[q].p==1?2:1);
          }
          else{//原本是反转或没有，直接改
              c[q].v=c[q].r-c[q].l+1-c[q].v;
              c[q].p=(c[q].p==0?3:0);
          }
          return;
      }
      down(q);
      int mid=c[q].l+c[q].r>>1;
      if(l<=mid)Swap(q<<1,l,r);
      if(mid<r)Swap(q<<1|1,l,r);
      c[q].v=c[q<<1].v+c[q<<1|1].v;
  }
```

## 3.查询
```cpp
  int Gets(int q){
      if(c[q].v==0)return c[q].l;//如果这个区间都是0，返回左端点
      if(c[q].v==c[q].r-c[q].l+1)return 0;//如果都是1，无解
      down(q);//下传
      int sum=Gets(q<<1);//先左后右
      if(sum!=0)return sum;
      sum=Gets(q<<1|1);
      return sum;
  }
```

## 4.主函数
```cpp
  scanf("%lld",&n);
  for(int i=1;i<=n;i++){
      scanf("%lld%lld%lld",&a[i].t,&a[i].l,&a[i].r);
      p[(i-1)*4+1]=a[i].l;
      p[(i-1)*4+2]=a[i].l-1;//加入l-1（加入更优的答案）
      p[(i-1)*4+3]=a[i].r;
      p[i*4]=a[i].r+1;//加入r+1保证有答案
  }
  p[n*4+1]=1;//一定要有1！！！
  sort(p+1,p+n*4+2);
  for(int i=1;i<=n*4+1;i++){if(p[i]!=p[i-1])M_A[p[i]]=++tot,M_B[tot]=p[i];}//离散化
  T.Build(1,1,tot);
  for(int i=1;i<=n;i++){
      if(a[i].t!=3)T.Add(1,M_A[a[i].l],M_A[a[i].r],(a[i].t==1?2:1));
      else T.Swap(1,M_A[a[i].l],M_A[a[i].r]);//按要求操作
      printf("%lld\n",M_B[T.Gets(1)]);//输出
  }
```
这是[总代码](https://www.luogu.com.cn/paste/v3f629h8)（无注释）

---

## 作者：Froggy (赞：11)

动态开点平衡树,她不香么?

---

我看见清一色的离散化+线段树,为毛我第一想法是动态开点?

用 $\operatorname{FHQ\ Treap}$ 更好处理一些

动态开点会使pushdown极其简短

安利另一道动态开点平衡树的题[P3968](https://www.luogu.com.cn/problem/P3968) + [题解](https://www.luogu.com.cn/blog/1445353309froggy/solution-p3968) ,P3968显然比这道题要复杂一些..(但其实只要思路清晰也不难)

看题解之前,首先要保证会写 $\operatorname{FHQ\ Treap}$

对于平衡树中的每个节点记录所代表的区间 $[l,r]$ ,以及区间里的数的值`num` ,反转标记`rev`,最左侧的0/1: `mn[0/1]` (如果不存在0/1就设置为inf) 和以它为根的子树所代表的区间长度 `siz` (别忘开**long long**哦)

同时用一个map记录右端点为r的节点编号,方便之后的动态开点

这里重点讲如何开点:

比如搞要在 $[L,R]$ 这个区间进行操作,那么就分别在 $L$,$R$ 的位置新开点

假设开点的位置为 $pos$

首先要找到 $pos$ 在平衡树的哪个节点的区间之中,即在平衡树中找到一个节点的区间 $[l,r]$ 满足: $l \leq pos \leq r$

这个好办,直接在map里面lower_bound即可

然后就可以拆成 $[l,pos-1],[pos,pos],[pos+1,r]$ 三个区间,新建三个节点然后再合并回去即可(具体见代码)

当然要先判断一下 $pos>l$ 和 $r>pos$

别忘了**删除原来的节点,更新map**!!!

开点讲完了,还有一些细节:

区间反转的时候还要 `swap(mn[0],mn[1]);`

update的时候很套路就不详细说了,更新mn[0/1]时直接在左右子树里取min即可

*code:*

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<map>
using namespace std;
#define N 200010
typedef long long ll;
const ll inf=1LL<<61;
map<ll,int> mp;//开个map记录平衡树中右端点为r的节点编号
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int m,root,cnt=0;
struct node{
	int key,num,ch[2],rev;
	ll mn[2],l,r,siz;
	bool Rev(){//弄个成员函数进行区间反转
		num^=1;
		rev^=1;
		swap(mn[0],mn[1]);
	}
}t[N<<4];
int NewNode(int num,ll l,ll r){//建新节点
	int k=++cnt; 
	t[k].num=num;
	t[k].l=l,t[k].r=r;
	t[k].siz=r-l+1;
	t[k].key=rand();
	t[k].ch[0]=t[k].ch[1]=0;
	if(num==0){
		t[k].mn[0]=l;
		t[k].mn[1]=inf;
	}
	else{
		t[k].mn[0]=inf;
		t[k].mn[1]=l;
	}
	mp[r]=k;
	return k;
}
void pushdown(int k){//下放标记
	if(t[k].rev){
		t[t[k].ch[0]].Rev();
		t[t[k].ch[1]].Rev();
		t[k].rev=0;
	}
}
void update(int k){//更新节点信息
	t[k].mn[0]=t[k].mn[1]=inf;
	t[k].siz=t[t[k].ch[0]].siz+t[t[k].ch[1]].siz+t[k].r-t[k].l+1;
	if(t[k].num==0){
		t[k].mn[0]=t[k].l;
	}
	else{
		t[k].mn[1]=t[k].l;
	}
	if(t[k].ch[0]){
		for(int i=0;i<=1;i++)
		t[k].mn[i]=min(t[k].mn[i],t[t[k].ch[0]].mn[i]);
	}
	if(t[k].ch[1]){
		for(int i=0;i<=1;i++)
		t[k].mn[i]=min(t[k].mn[i],t[t[k].ch[1]].mn[i]);
	}
}
void Split(int k,ll data,int &l,int &r){
	if(!k){
		l=r=0;
		return;
	}
	pushdown(k);
	if(t[k].r<=data){
		l=k;
		Split(t[k].ch[1],data,t[k].ch[1],r);
	}
	else{
		r=k;
		Split(t[k].ch[0],data,l,t[k].ch[0]);
	}
	update(k);
}
int Merge(int l,int r){
	if(!l||!r)return l+r;
	pushdown(l),pushdown(r);
	if(t[l].key<t[r].key){
		t[l].ch[1]=Merge(t[l].ch[1],r);
		update(l);
		return l;
	}
	else{
		t[r].ch[0]=Merge(l,t[r].ch[0]);
		update(r);
		return r;
	}
}
void del(int k){;
	mp.erase(mp.lower_bound(t[k].r));
	if(t[k].ch[0])del(t[k].ch[0]);
	if(t[k].ch[1])del(t[k].ch[1]);
}
void New(ll pos){//开点
	int k=mp.lower_bound(pos)->second;
	int l=0,r=0,p=0;
	int num=t[k].num;
	ll x=t[k].l,y=t[k].r;
	if(x==y&&x==pos)return;
	Split(root,y,l,r);
	Split(l,x-1,l,p);
	del(p);
	if(pos>x){
		l=Merge(l,NewNode(t[k].num,x,pos-1));
	}
	if(y>pos){
		r=Merge(NewNode(t[k].num,pos+1,y),r);
	}
	root=Merge(l,Merge(NewNode(t[k].num,pos,pos),r));
}
void Change(ll x,ll y,int num){
	int l=0,p=0,r=0;
	New(x),New(y);//先开点
	Split(root,y,l,r);
	Split(l,x-1,l,p);
	del(p);
	root=Merge(l,Merge(NewNode(num,x,y),r));
}
void Rev(ll x,ll y){
	int l=0,p=0,r=0;
	New(x),New(y);//先开点
	Split(root,y,l,r);
	Split(l,x-1,l,p);
	t[p].Rev();
	root=Merge(l,Merge(p,r));
}
int main(){
	srand(time(0));
	m=read();
	root=Merge(root,NewNode(0,1,2000000000000000000LL));//一开始开一个大区间
	for(int i=1;i<=m;i++){
		int opt=read();
		ll l=read(),r=read();
		if(opt==1){
			Change(l,r,1);
		}
		else if(opt==2){
			Change(l,r,0);
		}
		else{
			Rev(l,r);//1<->0
		}
		printf("%lld\n",t[root].mn[0]);//直接从根查询即可
	}
	return 0;
}
```

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!


---

## 作者：Rui_R (赞：8)

在看到题解清一色的线段树后，我决定为题解区带来一些新鲜的血液

**分块**

题目大意：维护一个初始全为0的数组，并处理三种操作：

将区间$l~r$改为1，将区间$l~r$改为0，将区间$l~r$取反

操作次数为$n$，且要你在每次操作后输出最小的，在数组中为0的正整数

数据范围：$1\leqslant n \leqslant 1e5,1\leqslant l,r \leqslant 1e18$

[原题](https://www.luogu.com.cn/problem/CF817F)

进入正文。

首先我们看到数据范围：$1e18$  于是倒吸一口凉气。离散化无疑。

那么要怎么离散化呢?

我~~感性~~觉得，这个答案应该只与每次操作的端点有关

于是深入思考得到，真正有意义的，只有每次操作的$l,r,r+1$

诶，$r+1$?为什么？

因为，若一次操作后$1~r$全部为1，答案将为$r+1$而不是下一个点。因此索性将$r+1$也作为一个点加入到离散化后的结果中

还有一个臭名昭著的坑点：$1$也要被扔到离散化的结果中

毕竟若每次操作的端点不涉及$1$答案就是$1$啊

那么，对于离散化的结果，就可以用分块去维护了

对于每个块维护一个tag，表示这个块中有几个值为$1$,再维护一个c，表示这个块是否被取反过

对每个点设置一个v，表示它看起来的值

而其实际上的值还要考虑其所属块的tag和c(若tag取满则其值为1，tag为0则其值为0，且要考虑其是否被取反过)

时间复杂度为$O(n* \sqrt{n})$,对于本题的数据能够搞定

那么，基本就这样了。一些奇奇怪怪的细节可以参考一下代码。加了注释，希望您能看懂。

$Code:$
```cpp
#include <cstdio>
#include <map>
#include <cmath>
#include <algorithm>

#define int long long

const int maxn=4e5+50;//一次操作加三个点，这里求稳开了四倍

struct question{
	int opt,l,r;
}q[maxn];

int n,a[maxn],cnt,to[maxn];std::map<int,int> after;//离散化用

int tag[maxn],belong[maxn],key,v[maxn],c[maxn],size[maxn];

inline void assign(int id,int k){//将第id块全部改为k
	int begin=(id-1)*key+1;
	for(int i=begin;belong[i]==belong[begin];i++) v[i]=c[belong[i]]?!k:k;
}

inline void modify(int l,int r,int k){
	if(k==-1){//区间取反
		if(belong[l]==belong[r]){
			if(tag[belong[l]]==size[belong[l]]||!tag[belong[l]]){
				int pos=tag[belong[l]]>0;//1 or 0
				assign(belong[l],pos);
			}
			//需要assign函数是因为有时tag会不再有意义
			//不能再用tag是否取满或tag是否为0来判断这一整块
			//因为这里我们修改了这一块的一部分
			for(int i=l;i<=r;i++){
				if((c[belong[i]]?!v[i]:v[i])==1) tag[belong[i]]--;
				if((c[belong[i]]?!v[i]:v[i])==0) tag[belong[i]]++;
				v[i]=!v[i];
			}//暴力修改
			return;
		}
		if(tag[belong[l]]==size[belong[l]])
		assign(belong[l],1);
		if(!tag[belong[l]]) assign(belong[l],0);
		//观察tag是否对其块内的值有意义
		//若有意义则其意义应被暴力下传来体现
		//因为tag要变了
		for(int i=l;belong[i]==belong[l];i++){
			if((c[belong[i]]?!v[i]:v[i])==1) tag[belong[i]]--;
			if((c[belong[i]]?!v[i]:v[i])==0) tag[belong[i]]++;
			v[i]=!v[i];
		}
		if(tag[belong[r]]==size[belong[r]])
		assign(belong[r],1);
		if(!tag[belong[r]]) assign(belong[r],0);
		for(int i=r;belong[i]==belong[r];i--){
			if((c[belong[i]]?!v[i]:v[i])==1) tag[belong[i]]--;
			if((c[belong[i]]?!v[i]:v[i])==0) tag[belong[i]]++;
			v[i]=!v[i];
		}
		for(int i=belong[l]+1;i<belong[r];i++){
			c[i]=!c[i];
			tag[i]=size[i]-tag[i];//令人舒爽的部分
			//不用管什么乱七八糟的，反过来就好
		}
	}else{
		//区间赋值
		//其实思想根上面很像，代码也基本一致
		//所以看着代码百来行的，其实没多少
		if(belong[l]==belong[r]){
			if(tag[belong[l]]==size[belong[l]]) assign(belong[l],1);
			if(!tag[belong[l]]) assign(belong[l],0);
			for(int i=l;i<=r;i++){
				//若值变了，更新tag
				if((c[belong[i]]?!v[i]:v[i])==1&&k==0) tag[belong[l]]--;
				if((c[belong[i]]?!v[i]:v[i])==0&&k==1) tag[belong[l]]++; 
				v[i]=c[belong[i]]?!k:k;
			}
			return;
		}
		if(tag[belong[l]]==size[belong[l]]) assign(belong[l],1);
		if(!tag[belong[l]]) assign(belong[l],0);
		for(int i=l;belong[i]==belong[l];i++){
			if((c[belong[i]]?!v[i]:v[i])==1&&k==0) tag[belong[i]]--;
			if((c[belong[i]]?!v[i]:v[i])==0&&k==1) tag[belong[i]]++;
			v[i]=c[belong[i]]?!k:k;
		}
		if(tag[belong[r]]==size[belong[r]]) assign(belong[r],1);
		if(!tag[belong[r]]) assign(belong[r],0);
		for(int i=r;belong[i]==belong[r];i--){
			if((c[belong[i]]?!v[i]:v[i])==1&&k==0) tag[belong[i]]--;
			if((c[belong[i]]?!v[i]:v[i])==0&&k==1) tag[belong[i]]++;
			v[i]=c[belong[i]]?!k:k;
		}
		for(int i=belong[l]+1;i<belong[r];i++){
			c[i]=0;//大手一挥把c划掉不管
			if(k==0) tag[i]=0;
			else tag[i]=size[i];//令人舒爽，直接赋值
		}
	}
}

inline int query(){
	// printf("cnt:%d\n",cnt);
	// for(int i=1;i<=cnt;i++) printf("i:%d v[i]:%d val:%d\n",i,tag[belong[i]]==size[belong[i]]?1:!tag[belong[i]]?0:c[belong[i]]?!v[i]:v[i],to[i]);
	for(int i=1;i<=belong[cnt];i++){
		// printf("i:%d tag:%d\n",i,tag[i]);
		if(tag[i]!=size[i]){//若不满，那肯定是在里面了
			int begin=(i-1)*key+1;
			if(!tag[i]) return begin;
			for(int j=begin;belong[j]==belong[begin];j++){
				if((c[i]?!v[j]:v[j])==0) return j;//枚举就好
			}
		}
	}
	// return cnt;
}

signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&q[i].opt,&q[i].l,&q[i].r);
		a[++cnt]=q[i].l,a[++cnt]=q[i].r,a[++cnt]=q[i].r+1;
	}
	a[++cnt]=1;
	std::sort(a+1,a+cnt+1);
	cnt=std::unique(a+1,a+cnt+1)-a-1;//离散化
	// for(int i=1;i<=cnt;i++) printf("%d ",a[i]);putchar('\n');
	key=std::sqrt(cnt);
	for(int i=1;i<=cnt;i++){after[a[i]]=i,to[i]=a[i],belong[i]=(i-1)/key+1;size[belong[i]]++;}//分块
	// for(int i=1;i<=cnt;i++) printf("%d ",belong[i]);putchar('\n');
	// to[cnt+1]=to[cnt]+1;
	// for(int i=1;i<=n;i++) printf("l:%d after_l:%d r:%d after_r:%d\n",q[i].l,after[q[i].l],q[i].r,after[q[i].r]);
	for(int i=1;i<=n;i++){
		if(q[i].opt==1){
			modify(after[q[i].l],after[q[i].r],1);
		}
		if(q[i].opt==2){
			modify(after[q[i].l],after[q[i].r],0);
		}
		if(q[i].opt==3){
			modify(after[q[i].l],after[q[i].r],-1);
		}
		// printf("%lld\n",query());
		printf("%lld\n",to[query()]);//输出
		//to[after[x]]=x,to用来将离散化后的结果转回其真正的值
	}
	return 0;
}
```


---

## 作者：傅思维666 (赞：7)

## 题解：

发一篇更详细的题解。

线段树+离散化。

但是并不是裸的叠加。

从头开始思考，展现一下思路过程：首先要维护三种操作，区间置零，区间置1，区间反转，并输出从左到右第一个0的位置。

区间操作必然考虑线段树，但是这个值域维护令人望而却步，但是这么大的值域需要离散化已经是套路的东西了。所以直接把其排序去重映射到一个有限值域中，在这个有限值域建线段树，最后返回的值再映射回去就好了。

然后思考如何维护这几种操作。区间赋值可以打lazy标记，区间反转同样可以打反转标记。打多重lazy标记的时候一定要考虑好标记间的相互影响，换言之，就是两种标记下传的先后问题。那么我们考虑：

区间赋值，之前的反转标记就会失效。区间反转，之前的赋值标记就会取反。它们之间没有先后的顺序，只是每次打新标记的时候直接重新赋值另一种标记就好。

至于求MEX值，很多大佬用了线段树+二分。但是没有必要，只需要先查左子树后查右子树，就可以找到最左的节点。有人说这是贪心，勉强算吧，小贪心？

之后是本题坑点：离散化要把r+1也离散进去。为什么呢？着重讲一讲：因为我们本来想维护值域，但是因为值域太宽广了，所以要离散化。但是并不是所有的都可以离散化。仔细思考：这道题，我们把$[l,r]$进行离散操作，这个$[l,r]$就有可能连成一起。那么假如我们要查询$l,r$中间的数，就查不到。这个时候就不能离散化。

但是为什么这道题可以用离散化呢？就是因为我们是整个区间赋值、反转，所以，可以保证答案肯定不会出现在这些区间内部，因为我们本来就是按块操作的。

但是$r+1$不一样，显然，$r+1$是有可能被算成答案的。所以$r+1$也要离散进去。

就大功告成了。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
#define lson pos<<1
#define rson pos<<1|1
using namespace std;
char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0,f=1;
	char ch=nc();
	while(ch<48||ch>57)
		if(ch=='-')
			f=-1,ch=nc();
	while(ch>=48&&ch<=57)
		x=x*10+ch-48,ch=nc();
	return x*f;
}
const int maxn=1e5+5;
int n;
int opt[maxn],l[maxn],r[maxn];
int a[maxn<<2],cnt;
int sum[maxn<<4],lazy[maxn<<4],rev[maxn<<4];
//sum求和，lazy赋值，rev反转
void pushup(int pos)
{
	sum[pos]=sum[lson]+sum[rson];
}
void build(int pos,int l,int r)
{
	int mid=(l+r)>>1;
	lazy[pos]=-1;
	if(l==r)
		return;
	build(lson,l,mid);
	build(rson,mid+1,r);
}
void mark(int pos,int l,int r,int k)
{
	if(k==1)
	{
		sum[pos]=(r-l+1);   
		lazy[pos]=1;
		rev[pos]=0;
	}
	else if(k==2)
	{
		lazy[pos]=0;
		sum[pos]=0;
		rev[pos]=0;
	}
	else
	{
		if(lazy[pos]!=-1)
			lazy[pos]^=1;
		else
			rev[pos]^=1;
		sum[pos]=(r-l+1)-sum[pos];
	}
}
void pushdown(int pos,int l,int r)
{
	int mid=(l+r)>>1;
	if(lazy[pos]==1)
	{
		mark(lson,l,mid,1);
		mark(rson,mid+1,r,1);
		lazy[pos]=-1;
	}
	else if(lazy[pos]==0)
	{
		mark(lson,l,mid,2);
		mark(rson,mid+1,r,2);
		lazy[pos]=-1;
	}
	if(rev[pos])
	{
		mark(lson,l,mid,3);
		mark(rson,mid+1,r,3);
		rev[pos]=0;
	}
}
void update(int pos,int l,int r,int x,int y,int k)
{
	int mid=(l+r)>>1;
	if(l==r)
	{
		if(k==1)
			sum[pos]=1;
		else if(k==2)
			sum[pos]=0;
		else
			sum[pos]^=1;
		return;
	}
	if(x<=l && r<=y)
	{
		mark(pos,l,r,k);
		return;
	}
	pushdown(pos,l,r);
	if(x<=mid)
		update(lson,l,mid,x,y,k);
	if(y>mid)
		update(rson,mid+1,r,x,y,k);
	pushup(pos);
}
int query(int pos,int l,int r)
{
	int mid=(l+r)>>1;
	if(l==r)
		return l;
	pushdown(pos,l,r);
	if(sum[lson]<(mid-l+1))
		return query(lson,l,mid);
	else
		return query(rson,mid+1,r);
}
signed main()
{
	n=read();
	a[++cnt]=1;
	for(int i=1;i<=n;i++)
	{
		opt[i]=read();l[i]=read();r[i]=read();
		a[++cnt]=l[i];a[++cnt]=r[i];a[++cnt]=r[i]+1;
	}
	sort(a+1,a+cnt+1);
	cnt=unique(a+1,a+cnt+1)-(a+1);
	build(1,1,cnt);
	for(int i=1;i<=n;i++)
	{
		l[i]=lower_bound(a+1,a+cnt+1,l[i])-a;
		r[i]=lower_bound(a+1,a+cnt+1,r[i])-a;
		update(1,1,cnt,l[i],r[i],opt[i]);
		printf("%lld\n",a[query(1,1,cnt)]);
	}
	return 0;
}
```



---

## 作者：LRL52 (赞：3)

> 前言：本蒟蒻的第一篇题解，更好的阅读体验戳这里:https://www.luogu.org/blog/lrl/

- 本题讲师讲的~~巨水~~，但容易错的细节却提醒了的，听的时候不是很懂，中午回去想了一下，好像懂了，下午就开始做，本题令我想的最久的就是多标记问题（$XOR$标记和$Add$染色标记），最终决定**同一节点只保留1个标记**（由于本题的特殊性），简而言之，就是$XOR$和区间暴力覆盖成$1$或$0$不能同时存在，如果存在，那就一定可以合并，存在$Add$数组上，所以在$Pushdown$的时候：

1. 假如传$Add$标记，就把左右儿子区间的$Add$直接覆盖成当前的$Add$，并把它们的$XOR$标记赋为0（有可能存在，但存在没有用了，染色成$0/1$是暴力的,无条件的）；
2. 假如传$XOR$标记，以左儿子为例，如果左儿子$Add!=-1$，就让$Add\ xor\ 1$，否则就把左儿子的$XOR$和$1$进行异或操作，右儿子传递是一样的；
3. 假如同时传$Add$标记和$XOR$标记，那是不能的，前文已经说过，上两步在传递的时候也**保证了两个标记同一节点最多只存在一个**。

#### 本题需要注意的就是首先要离散化（~~这个应该都知道不讲了~~），并且在离散化后的数组里同时加上每个操作的（右端点$+1$），因为它是很可能产生答案的地方，还有也别忘记离散化数组里一定得有$1$  

另外在代码里异或数组是$yh$（直接取的拼音首字母，别见怪），$1$表示该区间需要$XOR$，0表示该区间不需要$XOR$，初始值为$0$。

$Code:$
```cpp
#define ri register int
#define ll long long
#define ci const int&
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define dwn(i,a,b) for(register int i=(a);i>=(b);--i)
#define ee(i,a) for(register int i=head[a];i;i=e[i].nxt)
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define pre int m=(l+r)>>1
#define pushup sum[rt]=sum[rt<<1]+sum[rt<<1|1]
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+55;
const int M=2055;
const int inf=0x3f3f3f3f;
char ss[1<<21],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<21,stdin),A==B)?EOF:*A++;}
template<class T>void rd(T&x){
    ri f=1;char c=gc();x=0;while(c<48||c>57){if(c=='-')f=-1;c=gc();};
    while(c>47&&c<58){x=(x<<3)+(x<<1)+(c^48);c=gc();}x*=f;
}
int n,sum[(N*3)<<2],add[(N*3)<<2],yh[(N*3)<<2],op[N],cnt=0;
ll v[N<<2],ql[N],qr[N];
struct cmp{
	inline bool operator()(const ll&T1,const ll&T2){
		return T1<T2; 
	}
};

void buildtree(int l,int r,int rt){
	if(l==r){
		sum[rt]=0;add[rt]=-1;yh[rt]=0;
		return;
	}
	pre;
	sum[rt]=0;add[rt]=-1;yh[rt]=0;
	buildtree(lson);
	buildtree(rson);
	pushup;
}

inline void pushdown(int l,int r,int rt){
	pre;
	if(add[rt]!=-1){
		add[rt<<1]=add[rt];
		add[rt<<1|1]=add[rt];
		yh[rt<<1]=0;
		yh[rt<<1|1]=0;
		if(add[rt]==1){
			sum[rt<<1]=m-l+1;
			sum[rt<<1|1]=r-m;
		}
		else{
			sum[rt<<1]=0;
			sum[rt<<1|1]=0;
		}
		add[rt]=-1;
	}
	if(yh[rt]){
		if(add[rt<<1]!=-1)add[rt<<1]^=1;
		else yh[rt<<1]^=1;
		if(add[rt<<1|1]!=-1)add[rt<<1|1]^=1;
		else yh[rt<<1|1]^=1;
		sum[rt<<1]=m-l+1-sum[rt<<1];
		sum[rt<<1|1]=r-m-sum[rt<<1|1];
		yh[rt]=0;
	}
}

int query(int l,int r,int rt){
	if(l==r)return l;
	pushdown(l,r,rt);
	pre;
	if(sum[rt<<1]<m-l+1)return query(lson);
	else return query(rson);
} 

void update(int o,int x,int y,int l,int r,int rt){
	if(x<=l&&r<=y){
		if(l==r){
			if(o==1)sum[rt]=1;
			else if(o==2)sum[rt]=0;
			else sum[rt]^=1;
		}
		else{
			if(o==1){
				add[rt]=1;yh[rt]=0;
				sum[rt]=r-l+1;
			}
			else if(o==2){
				add[rt]=0;yh[rt]=0;
				sum[rt]=0;
			}
			else{
				if(add[rt]==-1)yh[rt]^=1;
				else add[rt]^=1;
				sum[rt]=r-l+1-sum[rt];
			}
		}
		return;
	}
	pushdown(l,r,rt);
	pre;
	if(x<=m)update(o,x,y,lson);
	if(y>m)update(o,x,y,rson);
	pushup;
}

int main()
{
    //freopen("read.txt","r",stdin);
    rd(n);
    v[++cnt]=1;
    rep(i,1,n){
    	rd(op[i]);rd(ql[i]);rd(qr[i]);
    	v[++cnt]=ql[i];v[++cnt]=qr[i];v[++cnt]=qr[i]+1;
	}
	sort(v+1,v+cnt+1,cmp());
	cnt=unique(v+1,v+cnt+1)-v-1;
	buildtree(1,cnt,1);
	rep(i,1,n){
	    ql[i]=lower_bound(v+1,v+cnt+1,ql[i])-v;
		qr[i]=lower_bound(v+1,v+cnt+1,qr[i])-v;	
		update(op[i],ql[i],qr[i],1,cnt,1);  
		printf("%lld\n",v[query(1,cnt,1)]);
    }
    return 0;
}
```

---

## 作者：一只书虫仔 (赞：3)

#### Description

> 维护一个集合，初始为空。有 $3$ 种操作：
> - 把 $[l,r]$ 中在集合中没有出现过的数添加到集合中。
> - 把 $[l,r]$ 中在集合中出现过的数从集合中删掉。
> - 把 $[l,r]$ 中在集合中没有出现过的数添加到集合中，并把 $[l,r]$ 中在集合中出现过的数从集合中删掉。
>
> 每次操作后输出在集合中没有出现过的最小正整数。

#### Solution

ODT 裸题，本篇题解就当做 ODT 入门讲解吧（

ODT 的初步思想使用 `set` 维护一些区间，首先我们建立一个区间的结构体，注意 `set` 能够引用的变量名是要有序的：

```cpp
struct range {
	long long l; // 左界 
	long long r; // 右界 
	mutable long long v; // 性质 区间中的数是否已在集合中 0 / 1 
	bool operator < (const range& a) const {
		if (l != a.l) return l < a.l;
		else return r < a.r;
	}
};
```

里面的四样东西分别是：

- $l,r$：区间的左右界；
- $v$：区间的性质，在本题中就是区间内的所有数是否已在集合中，注意要在前面加一个 `mutable`，具体原因在下方会说明；
- `<` 的特殊声明：使得结构体 `range` 是有序的。
 
首先我们就把 $[1,10^{18}]$ 这个区间插入 `set` 里，性质 $v=0$。

然后我们对本题的三个操作分别考虑。

**第一个操作**

我们运行到第一个操作时，假设我们要将区间 $[l,r]$ 插入，假设 $[l,r]=[3,15]$，然后 `set` 中原有三个区间的 $v=1$，分别是 $[1,4]$，$[6,8]$，$[10,17]$，我们可以将这三个区间分裂为五个 $v=1$ 的区间 $[1,2]$，$\bf[3,4]$，$\bf[6,8]$，$\bf[10,15]$，$[16,17]$，然后将上面加粗的三个区间删掉，插入 $[3,15]$，然后这个区间的 $v=1$，就可以了。具体也就是我们要实现在 $p$ 处分割一下，如果 $p$ 刚好在一个区间 $[L,R]$ 内那么就将区间 $[L,R]$ 分割成 $[L,p-1]$ 和 $[p,R]$，$v$ 继承 $[L,R]$ 的 $v$，再将这两个区间插入即可。

问题来了，set 不能直接调用下标，我们怎么找到满足要求的 $[L,R]$ 呢？可以使用 `lower_bound` 查找。为了方便，我们可以将分割函数 `split` 返回一个迭代器，迭代器指向 $[p,R]$，在之后的代码里有大用处：

```cpp
set <range>::iterator split (long long p) {
	range tmp;
	tmp.l = p, tmp.r = p, tmp.v = 0;
	set <range>::iterator it = s.lower_bound(tmp); // 二分查找
	if (it != s.end() && (*it).l == p) return it; // 特殊情况
	it--;
	long long l = (*it).l, r = (*it).r, v = (*it).v;
	s.erase(it); // 删掉 [l,r]
	range L, R;
	L.l = l, L.r = p - 1, L.v = v;
	R.l = p, R.r = r, R.v = v;
	s.insert(L); // 插入 [l, p - 1]
	return s.insert(R).first; // 插入 [p, r] 并返回迭代器
}
// [l, r] -> [l, p - 1], [p, r]
```

注意一些特殊情况要特殊考虑，比如说右界是 `set` 的右界等，在上方代码里有明确标注。

然后我们调用 `split(r + 1)` 和 `split(l)`（要先调用 $r+1$ 再调用 $l$，具体原因我不清楚，其他巨佬可能有讲解？），分割后返回了分别以 $l$ 和 $r+1$ 为左界的区间的迭代器 $p,q$。

```cpp
set <range>::iterator q = split(r + 1);
set <range>::iterator p = split(l);
```

要删除区间 $[l,r]$ 内的所有子区间，可以直接调用 `erase(p, q)`，因为 `erase` 函数是左闭右开的，和我们的目的相符。删除后，再将 $[l,r]$ 插入即可，插入时 $v=1$，因为将要将这些数加入集合。

```cpp
s.erase(p, q);
range now;
now.l = l, now.r = r, now.v = 1;
s.insert(now);
```

**第二个操作**

与第一个操作类似，只不过最后插入 $[l,r]$ 时 $v=0$。

```cpp
s.erase(p, q);
range now;
now.l = l, now.r = r, now.v = 0;
s.insert(now);
```

**第三个操作**

类似于区间翻转，可以考虑分割之后枚举迭代器 $[p,q)$，直接暴力让 $v=1-v$ 即可。

```cpp
for (set <range>::iterator it = p; it != q; it++)
	(*it).v = 1 - (*it).v;
```

**输出 MEX**

也不难，枚举整个 `set`，然后找到最靠左的不在集合内的区间的左界即可。

```cpp
long long ans = 0;
for (set <range>::iterator it = s.begin(); it != s.end(); it++)
	if ((*it).v == 0) {
		ans = (*it).l;
		break;
	}
```

于是我们就用 `set` 维护的方式解决了这道题目。

---

## 作者：RedreamMer (赞：3)

[$\Large{\texttt{CF817F}}$](https://www.luogu.com.cn/problem/CF817F)

题目调了好久，发片题解纪念下QwQ

算法：线段树+离散化

---

$\Large\texttt{Meaning}$

（题意略有改动）

共有 $n$ 个操作，一个区间（初始全为 $0$ ），共三种操作如下：

$1.$ 将 $[l,r]$ 区间赋值为 $1$ 。

$2.$ 将 $[l,r]$ 区间赋值为 $0$ 。

$3.$ 将 $[l,r]$ 区间的数取反。

每次操作后问最小的正整数 $x$ 且 $a_x$ 为 $0$ 。

$1\le l,r\le 10^{18}$

---

$\Large\texttt{Solution}$

区间修改，查询，首先想到线段树，但是建一个 $10^{18}$ 量级的线段树，时间和空间显然不合理。

但是发现 $n$ 的范围很小，每次修改的区间的左右端点顶多也只有$2*10^{5}$，所以~~套路~~将数据离线下来进行离散化处理，将每个端点排序再依次标号，用数组储存。

然后的操作和普通的线段树没有什么不同，在线段数中对每一段区间存储两个变量( $p_0$ ：区间中是否有 $0$ ， $p_1$ ：区间中是否有 $1$ )。

操作一：$p_0$ 赋值为 $0$ ， $p_1$ 赋值为 $1$ 。

操作二：$p_0$ 赋值为 $0$ ， $p_1$ 赋值为 $1$ 。

操作三：交换 $p_0$ 和 $p_1$ 。

但是需要注意的是（这里我卡了好久）， $\texttt{push\_down}$ 的操作中，对于要下传的标记为3时，若儿子节点的懒标记还没有下传，是不可以直接覆盖的，原因显然。

可是懒标记的特点就是 “懒” ，不可能让操作一直递归下去吧。

所以对此需要进行分类讨论：

若下传的操作是 $1$ 或 $2$ ：可以直接覆盖懒标记，因为这次操作会将整个区间都赋值为 $0$ 或 $1$ ，和之前的操作无关。

若下传的操作是 $3$ ：那么如果懒标记为 $3$ ，可以直接消除懒标记，取反 $+$ 取反 $=$ 不变。

若下传的操作是 $3$ ：如果懒标记为 $1$ ，则就改懒标记为 $2$ ，如果懒标记为 $2$ ，则就改懒标记为 $1$ ，覆盖( $1/0$ )+取反=覆盖( $0/1$ ) （这个操作代码中未体现 ~~其实是我懒的写~~）。

---

$\Large\texttt{Code}$

代码细节还是挺多的，请细细看（码风应该可以令人接受QwQ）

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize(1)
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <immintrin.h>
#include <emmintrin.h>
//qqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzkqqzk
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

// #define PB push_back
// #define MP make_pair
#define ls now << 1
#define rs now << 1 | 1
// #define int long long
// #define us unsigned
#define LL long long
const int N = 1e5;
// const int N = 4e5;
// #define re register
// const int mod = 1e9 + 7;
// const int inf = 0x7fffffff;
// char buf[(int)1e8], *ss = buf;
// inline int INIT()
// {
//     buf[fread(buf, 1, (int)1e8 - 1, stdin)] = '\n';
//     fclose(stdin);
//     return 0;
// }
// const int __START__ = INIT();

inline char nc()
{
    static const int BS = 1 << 22;
    static unsigned char buf[BS], *st, *ed;
    if (st == ed)
        ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? EOF : *st++;
}
//#define nc getchar
inline LL read()
{
    char ch;
    LL res = 0;
    bool flag = 0;
    while (!isdigit(ch = nc()))
        ;
    while (ch >= '0' and ch <= '9')
    {
        res = (res << 1) + (res << 3) + (ch - '0');
        ch = nc();
    }
    return res;
}

int a, top, id;
LL p[(N << 5) + 10];
map<LL, int> st;
struct node
{
    int opt;
    LL l, r;
} s[(N << 5) + 10];
struct S
{
    int l, r, lazy;
    bool p0, p1, qq;
} m[(N << 5) + 10];

inline void up(int now)
{
    m[now].p0 = m[ls].p0 | m[rs].p0;
    m[now].p1 = m[ls].p1 | m[rs].p1;
}

inline void down(int now)
{
    if (!m[now].lazy || m[now].qq)
        return;
    if (m[now].lazy == 1)
    {
        m[ls].p0 = m[rs].p0 = 0;
        m[ls].p1 = m[rs].p1 = 1;
    }
    else if (m[now].lazy == 2)
    {
        m[ls].p0 = m[rs].p0 = 1;
        m[ls].p1 = m[rs].p1 = 0;
    }
    else
    {
        if (m[ls].lazy)
            down(ls);
        if (m[rs].lazy)
            down(rs);
        swap(m[ls].p0, m[ls].p1);
        swap(m[rs].p0, m[rs].p1);
    }
    m[ls].lazy = m[rs].lazy = m[now].lazy;
    m[now].lazy = 0;
}

inline void build(int now, int l, int r)
{
    m[now].l = l;
    m[now].r = r;
    if (l == r)
    {
        m[now].p0 = 1;
        m[now].p1 = 0;
        m[now].qq = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    up(now);
    return;
}

inline void add(int now, int l, int r, int k)
{
    if (m[now].l >= l && m[now].r <= r)
    {
        if (k == 1)
        {
            m[now].p0 = 0;
            m[now].p1 = 1;
        }
        else if (k == 2)
        {
            m[now].p0 = 1;
            m[now].p1 = 0;
        }
        else
        {
            swap(m[now].p0, m[now].p1);
        }
        if (k == 1 || k == 2)
            m[now].lazy = k;
        else if (k == 3 && m[now].lazy == 3)
            m[now].lazy = 0;
        else
        {
            down(now);
            m[now].lazy = k;
        }
        return;
    }
    down(now);
    int mid = (m[now].l + m[now].r) >> 1;
    if (l <= mid)
        add(ls, l, r, k);
    if (mid < r)
        add(rs, l, r, k);
    up(now);
}

inline int query(int now, int l, int r)
{
    if (m[now].r < l || m[now].l > r || m[now].p0 == 0)
        return -1;
    if (m[now].p0 == 1 && m[now].p1 == 0)
        return m[now].l;
    down(now);
    int mid = (m[now].l + m[now].r) >> 1;
    int k = query(ls, l, r);
    if (k != -1)
        return k;
    return query(rs, l, r);
}

signed main()
{
    a = read();
    for (int i = 1; i <= a; i++)
    {
        s[i].opt = read();
        s[i].l = read();
        s[i].r = read();
        if (s[i].l != 1)
            p[++top] = s[i].l - 1;
        p[++top] = s[i].l;
        p[++top] = s[i].l + 1;
        if (s[i].r != 1)
            p[++top] = s[i].r - 1;
        p[++top] = s[i].r;
        p[++top] = s[i].r + 1;
    }
    p[++top] = 1;
    sort(p + 1, p + top + 1);
    int k = unique(p + 1, p + top + 1) - p - 1;
    build(1, 1, k);
    for (int i = 1; i <= k; i++)
        st[p[i]] = i;
    // cout << st[2] << ' ' << st[10];
    for (int i = 1; i <= a; i++)
    {
        add(1, st[s[i].l], st[s[i].r], s[i].opt);
        // for (int i = 1; m[i].l; i++)
        //     cout << i << ' ' << m[i].l << ' ' << m[i].r << ' ' << m[i].p0 << ' ' << m[i].p1 << ' ' << m[i].lazy << endl;
        printf("%lld\n", p[query(1, 1, k)]);
    }
    return 0;
}
```

[$\large\texttt{My Blog}$](https://www.luogu.com.cn/blog/184549/)

---

## 作者：Uniecho1 (赞：3)

我寻思着前排的**sto LRL52 orz**都做了，我也该试着做一下......

然和，嗯，很明显是离散化和线段树

那么问题来了：懒标记好维护，异或标记怎么办？

作为一个大蒟蒻，我一点都不认为我能想思路清奇的LRL一样同时维护两个可能相互冲突的标记啊......

想了一想，我决定，**只维护一个懒标记，异或操作时直接找到存在的懒标记修改**！

好的打出来没过，看了CF的数据一口老血：我忘了特判右区间+1是第一个0的情况了！

思考了一下人生，我跑去嫖了LRL的智慧：**离散化的时候把右区间+1也插进去**

```cpp
for(long long i=1;i<=N;i++){
		cin>>cmd[i]>>l[i]>>r[i];
		lsh[++cnt]=l[i];lsh[++cnt]=r[i];lsh[++cnt]=r[i]+1;
	}
```
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

好了于是就做出来了（唉我太菜了）

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long maxn=400005;
long long N,cnt,sum[maxn<<2],lz[maxn<<2],cmd[maxn],l[maxn>>1],r[maxn>>1],lsh[maxn];

void pushdown(long long L,long long R,long long id){
    if(lz[id]==-1)return;
    long long M=L+R>>1;
    lz[id<<1]=lz[id<<1|1]=lz[id];
    sum[id<<1]=lz[id]*(M-L+1);
    sum[id<<1|1]=lz[id]*(R-M);
    lz[id]=-1;
}

void change(long long x,long long y,long long L,long long R,long long id,long long k){
    if(x<=L&&R<=y){
        lz[id]=k;sum[id]=(R-L+1)*k;return;
    }
    pushdown(L,R,id);
    long long M=(L+R)>>1;
    if(x<=M)change(x,y,L,M,id<<1,k);
    if(y>M)change(x,y,M+1,R,id<<1|1,k);
    sum[id]=sum[id<<1]+sum[id<<1|1];
}

void rotate(long long x,long long y,long long L,long long R,long long id){
    if(x<=L&&R<=y&&lz[id]!=-1){
        lz[id]^=1;sum[id]=R-L+1-sum[id];return;
    }
    pushdown(L,R,id);
    long long M=(L+R)>>1;
    if(x<=M)rotate(x,y,L,M,id<<1);
    if(y>M)rotate(x,y,M+1,R,id<<1|1);
    sum[id]=sum[id<<1]+sum[id<<1|1];
}

long long query(long long L,long long R,long long id){
    if(L==R)return L;
    long long M=L+R>>1;
    pushdown(L,R,id);
    if(sum[id<<1]<M-L+1)return query(L,M,id<<1);
    else return query(M+1,R,id<<1|1);
}

void build(long long L,long long R,long long id){
    if(L==R){
        lz[id]=0;
        return;
    }
    long long M=L+R>>1;
    build(L,M,id<<1);
    build(M+1,R,id<<1|1);
}

int main(){
    //freopen("in.txt","r",stdin);
    memset(lz,-1,sizeof(lz));
    cin>>N;
    lsh[++cnt]=1;
    for(long long i=1;i<=N;i++){
        cin>>cmd[i]>>l[i]>>r[i];
        lsh[++cnt]=l[i];lsh[++cnt]=r[i];lsh[++cnt]=r[i]+1;
    }
    sort(lsh+1,lsh+cnt+1);
    long long len=unique(lsh+1,lsh+cnt+1)-lsh-1;
    build(1,len,1);
    for(long long i=1;i<=N;i++){
        long long x=lower_bound(lsh+1,lsh+len+1,l[i])-lsh;
        long long y=lower_bound(lsh+1,lsh+len+1,r[i])-lsh;
        if(cmd[i]==1)change(x,y,1,len,1,1);
        else if(cmd[i]==2)change(x,y,1,len,1,0);
        else if(cmd[i]==3)rotate(x,y,1,len,1);
        printf("%lld\n",lsh[query(1,len,1)]);
    }
    return 0;
}
```
别问我为啥离散化的方式都一样——毕竟同一个老师教的啊（逃）

时间复杂度可能会大一点，但是好理解啊（笑）

啊，说我luogu上没过？？
unknown error交不过去我也很绝望啊

---

## 作者：liuziwen0224 (赞：2)

# problem
- 维护一个集合，初始为空。
- 有 $3$ 种操作：
    1. 把 $[l,r]$ 中在集合中没有出现过的数添加到集合中。
    2. 把 $[l,r]$ 中在集合中出现过的数从集合中删掉。
    3. 把 $[l,r]$ 中在集合中没有出现过的数添加到集合中，并把 $[l,r]$ 中在集合中出现过的数从集合中删掉。
- 每次操作后输出集合的 $\operatorname{MEX}$ —— 在集合中没有出现过的最小正整数。
- $1\le n\le 10^5$，$1\le l\le r\le 10^{18}$。
# solution
竞赛老师说要学习线段树上二分。所以说我就开始疯狂学习。但是这是个啥啊。

~~试图放弃。~~ ~~gg是神~~

区间操作想到线段树。

第一步肯定是离散化，因为$l,r$非常大。

操作其实很好操作，序列的修改和线段树没什么差别。

然后在查询中二分查询就好了。

代码其实特别好懂。
# thoughts
其实这个$r$加一和减一是看一个博客写的。应该是查询前面全都是1的区间的长度。
# code
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;
const long long N=150020;
map<long long,long long> mp;
long long b[N*4],n,m,cnt;
struct ask{
    long long l,r;
    long long k;
}q[N];
struct tree{
    long long l,r,sum,sev,lazy;
}tr[N*40];
void build(long long l,long long r,long long now){
    tr[now].l=l;
    tr[now].r=r;
    tr[now].lazy=-1;
    if(l==r)return;
    long long mid=(l+r)>>1;
    build(l,mid,now*2);
    build(mid+1,r,now*2+1);
}
void pushdown(long long now){
    long long mid=(tr[now].l+tr[now].r)>>1;
    if(tr[now].lazy!=-1){
        tr[now*2].lazy=tr[now*2+1].lazy=tr[now].lazy;
        tr[now*2].sum=(mid-tr[now].l+1)*tr[now].lazy;
        tr[now*2+1].sum=(tr[now].r-mid)*tr[now].lazy;
        tr[now*2].sev=tr[now*2+1].sev=0;
        tr[now].lazy=-1;
    }
    if(tr[now].sev){
        tr[now*2].sev^=1;
        tr[now*2+1].sev^=1;
        tr[now*2].sum=(mid-tr[now].l+1)-tr[now*2].sum;
        tr[now*2+1].sum=(tr[now].r-mid)-tr[now*2+1].sum;
        tr[now].sev=0;
    }
}
void update(long long l,long long r,long long now,long long k){
    pushdown(now);
    if(tr[now].l==l&&tr[now].r==r){
        tr[now].sum=(tr[now].r-tr[now].l+1)*k;
        tr[now].lazy=k;
        tr[now].sev=0;
        return ;
    }
    long long mid=(tr[now].l+tr[now].r)>>1;
    if(l>mid){
        update(l,r,now*2+1,k);
    }
    else if(r<=mid){
        update(l,r,now*2,k);
    }
    else{
        update(l,mid,now*2,k);
        update(mid+1,r,now*2+1,k);
    }
    tr[now].sum=tr[now*2].sum+tr[now*2+1].sum;
}
void serve(long long l,long long r,long long now){
    pushdown(now);
    if(tr[now].l==l&&tr[now].r==r){
        tr[now].sum=(tr[now].r-tr[now].l+1)-tr[now].sum;
        tr[now].sev^=1;
        return;
    }
    long long mid=(tr[now].l+tr[now].r)>>1;
    if(l>mid)serve(l,r,now*2+1);
    else if(r<=mid)serve(l,r,now*2);
    else{
        serve(l,mid,now*2);
        serve(mid+1,r,now*2+1);
    }
    tr[now].sum=tr[now*2].sum+tr[now*2+1].sum;
}
void check(long long now){
    if(tr[now].l==tr[now].r){
        printf("%lld\n",b[tr[now].l]);
        return ;
    }
    long long mid=(tr[now].l+tr[now].r)>>1;
    pushdown(now);
    if(tr[now*2].sum<mid-tr[now].l+1)check(now*2);
    else return check(now*2+1);
}
int main(){
    scanf("%lld",&m);
    for(long long i=1;i<=m;i++){
        scanf("%lld%lld%lld",&q[i].k,&q[i].l,&q[i].r);
        q[i].r++;
        b[++cnt]=q[i].l;
        b[++cnt]=q[i].r;
    }
    b[++cnt]=1;
    sort(b+1,b+1+cnt);
    n=unique(b+1,b+1+cnt)-(b+1);
    for(long long i=1;i<=n;i++){
        mp[b[i]]=i;
    }
    build(1,n,1);
    for(long long i=1;i<=m;i++){
        if(q[i].k==1){
            update(mp[q[i].l],mp[q[i].r]-1,1,1);
        }
        else if(q[i].k==2){
            update(mp[q[i].l],mp[q[i].r]-1,1,0);
        }
        else{
            serve(mp[q[i].l],mp[q[i].r]-1,1);
        }
        check(1);
    }
    return 0;
}
```


---

## 作者：Kendrick_Z (赞：2)

离散化+线段树维护

考场上A了这道题然而由于内存开大MLE

一眼都能看出来是个数据结构题

我选择线段树！

解决这道题的关键是懒标记的叠加和下传过程

我一开始维护的是区间内最左边1和最左边0的位置

后来发现标记没办法下传更改

所以维护0和1的个数

查询时候小贪心一下优先往左边查询

### 标记处理：

对于要维护的区间 假如传的标记为0或1

那么直接覆盖掉之前的 然后更新

如果传的标记是异或标记

那么我们就考虑如果上个标记是异或

我们再次交换0 1的个数

如果是1 那就相当于全部变成0 所以标记变成0

0也同理

那么我们在更新时候分类讨论

然后pushdown大力分左右儿子讨论

### 关于离散化：

r最大到了1E18

那么我们离散化什么?

操作区间 

我们考虑一次操作无非就是01变化

答案可能是左端点 右端点 左端点-1 右端点+1

以及 1

离散化映射下即可

我喜欢结构体的线段树！！传参少：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int INF =1e15;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct node{
	int l,r,tag,id0,id1,siz;
}tree[N];
struct NODE{
	int l,r,op;
}query[N];
int m,n,L[N];
inline int ls(int x){return x<<1;}
inline int rs(int x){return x<<1|1;}
inline void upd(int p){
	tree[p].id0=tree[ls(p)].id0+tree[rs(p)].id0;
	tree[p].id1=tree[ls(p)].id1+tree[rs(p)].id1;
}
inline void build(int l,int r,int p){
	tree[p].l=l,tree[p].r=r,tree[p].id0=r-l+1,tree[p].id1=0;
	tree[p].tag=-1;
	tree[p].siz=r-l+1;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls(p));
	build(mid+1,r,rs(p));
	upd(p);
}
inline void pushdown(int p){
	if(tree[p].tag==-1){
		return ;
	}
	int tag=tree[p].tag;
	if(tag==1){
		tree[ls(p)].tag=tree[rs(p)].tag=1;
		tree[ls(p)].id0=0;
		tree[ls(p)].id1=tree[ls(p)].siz;
		tree[rs(p)].id0=0;
		tree[rs(p)].id1=tree[rs(p)].siz;
			tree[p].tag=-1;
	}else if(tag==0){
		tree[ls(p)].tag=tree[rs(p)].tag=0;
		tree[ls(p)].id1=0;
		tree[ls(p)].id0=tree[ls(p)].siz;
		tree[rs(p)].id1=0;
		tree[rs(p)].id0=tree[rs(p)].siz;
		tree[p].tag=-1;
	}else {
		if(tree[ls(p)].tag==2){
		swap(tree[ls(p)].id1,tree[ls(p)].id0);
		tree[ls(p)].tag=-1;
		}else {
			if(tree[ls(p)].tag==-1){
				swap(tree[ls(p)].id1,tree[ls(p)].id0);
				tree[ls(p)].tag=2;
			}else if(tree[ls(p)].tag==0){
				tree[ls(p)].tag=1;
				tree[ls(p)].id0=0;
				tree[ls(p)].id1=tree[ls(p)].siz;
			}else if(tree[ls(p)].tag==1){
				tree[ls(p)].tag=0;
				tree[ls(p)].id1=0;
				tree[ls(p)].id0=tree[ls(p)].siz;
			}
		}
		if(tree[rs(p)].tag==2){
		swap(tree[rs(p)].id1,tree[rs(p)].id0);
		tree[rs(p)].tag=-1;
		}else {
			if(tree[rs(p)].tag==-1){
				swap(tree[rs(p)].id1,tree[rs(p)].id0);
				tree[rs(p)].tag=2;
			}else if(tree[rs(p)].tag==0){
				tree[rs(p)].tag=1;
				tree[rs(p)].id0=0;
				tree[rs(p)].id1=tree[rs(p)].siz;
			}else if(tree[rs(p)].tag==1){
				tree[rs(p)].tag=0;
				tree[rs(p)].id1=0;
				tree[rs(p)].id0=tree[rs(p)].siz;
			}
		}
			tree[p].tag=-1;
	}
}
inline void change(int l,int r,int p,int fl){
	if(tree[p].l>=l&&tree[p].r<=r){
		if(fl==0){
			tree[p].id0=tree[p].siz;
			tree[p].id1=0;
			tree[p].tag=0;
			return;
		}	
		if(fl==1){
			tree[p].id0=0;
			tree[p].id1=tree[p].siz;
			tree[p].tag=1;
		}	
		return ;
	}
	pushdown(p);
	int mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid){
		change(l,r,ls(p),fl);
	}
	if(r>mid){
		change(l,r,rs(p),fl);
	}
	upd(p);
}
inline int ask(int l,int r,int p){
	if(l==r){
		return l;
	}
	pushdown(p);
	int mid=(l+r)>>1;
	if(tree[ls(p)].id0){
		return ask(l,mid,ls(p));
	}else return ask(mid+1,r,rs(p));
}
inline void change1(int l,int r,int p){
	if(tree[p].l>=l&&tree[p].r<=r){
		if(tree[p].tag==-1){
			swap(tree[p].id0,tree[p].id1);
			tree[p].tag=2;
		}else if(tree[p].tag==0){
			tree[p].tag=1;
			tree[p].id1=tree[p].siz;
			tree[p].id0=0;
		}else if(tree[p].tag==1){
			tree[p].tag=0;
			tree[p].id1=0;
			tree[p].id0=tree[p].siz;
		}else{
			tree[p].tag=-1;
			swap(tree[p].id0,tree[p].id1);
		}
		return;
	}
	pushdown(p);
	int mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid){
		change1(l,r,ls(p));	
	}
	if(r>mid){
		change1(l,r,rs(p));
	}
	upd(p);
}
signed main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	m=read();
	for(int i=1;i<=m;i++){
		query[i].op=read();
		query[i].l=read(),query[i].r=read();
		L[++n]=query[i].l,L[++n]=query[i].r,L[++n]=max(1ll,query[i].l-1);
		L[++n]=query[i].r+1;
	}
	L[++n]=1;
	sort(L+1,L+n+1);
	n=unique(L+1,L+n+1)-L-1;
	build(1,n,1);
	for(int i=1;i<=m;i++){
		int l=query[i].l,r=query[i].r,op=query[i].op;
		int ans=0;
		int ql=lower_bound(L+1,L+n+1,l)-L;
		int qr=lower_bound(L+1,L+n+1,r)-L;
		if(op==1){
			change(ql,qr,1,1);
			printf("%lld\n",L[ask(1,n,1)]);
		}
		if(op==2){
			change(ql,qr,1,0);
			printf("%lld\n",L[ask(1,n,1)]);
		}
		if(op==3){
			change1(ql,qr,1);
			printf("%lld\n",L[ask(1,n,1)]);
		}
	}
	return 0;
}
```


---

## 作者：Spasmodic (赞：1)

虽然区间范围很大，但是我们观察到有效的只有 $O(n)$ 个，那么可以假设 $l,r$ 的范围只有 $2n$，然后搞一个动态开点或者离散化下就随意了。

那么维护计数器可知 $1,2$ 操作就是区间覆盖，$3$ 操作是区间 $\oplus$，打上两个标记就可以了。

询问操作就是找出 $\min\{x|c_1=\dots =c_x=1\}$，那么在线段树上二分就可以了。

复杂度是 $O(n\log n)$ 的。

---

## 作者：Qing_喵乖乖喵 (赞：1)

离散化+线段树

代码中v0表示0的最左位置 v1表示1的最左位置

事先存下线段树每个节点代表的左右区间[l,r]

操作1:区间改为1 直接将v0赋值为INF v1赋值为l

操作2:同理

操作3:交换v0 v1的值即可

需要注意以下几点:

1.离散化时除了加入询问的Li,Ri外,由于1 Li-1 Ri+1也可能成为答案 也要加入

2.注意操作的先后 先覆盖 再异或 我的做法是开两个laz标记 考虑好先后顺序及操作的影响就行

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f,N=1e5+5;
struct node{
	int laz,v0,v1,l,r,tag;
	node*ch[2];
	node(int a=0,int b=0){
		ch[0]=ch[1]=NULL;
		l=a;r=b;laz=-1;tag=0;
		v0=l;v1=INF;
	}
	void turn0(){v0=l;v1=INF;}
	void turn1(){v0=INF;v1=l;}
	void _xor(){swap(v0,v1);}
	void maintain(){
		v0=min(ch[0]->v0,ch[1]->v0);
		v1=min(ch[0]->v1,ch[1]->v1);
	}
	void pushdown(){
		if(laz==0){
			ch[0]->turn0();
			ch[1]->turn0();
			ch[0]->tag=ch[1]->tag=0;
			ch[0]->laz=ch[1]->laz=0;
		}
		if(laz==1){
			ch[0]->turn1();
			ch[1]->turn1();
			ch[0]->tag=ch[1]->tag=0;
			ch[0]->laz=ch[1]->laz=1;
		}
		if(tag){
			ch[0]->_xor();
			ch[1]->_xor();
			ch[0]->tag^=1;
			ch[1]->tag^=1;
		}
		laz=-1;tag=0;
	}
}*rt,pool[N<<4];
inline node*new_node(int a=0,int b=0){
	static int cc=0;
	pool[cc]=node(a,b);
	return &pool[cc++];
}
int query(){return rt->v0;}
void build(node*&u,int l,int r){
	u=new_node(l,r);
	if(l!=r){
		int mid=(l+r)>>1;
		build(u->ch[0],l,mid);
		build(u->ch[1],mid+1,r);
	}
}
void turn0(node*u,int L,int R){
	const int&l=u->l,&r=u->r;
	if(r<L||l>R) return;
	if(L<=l&&r<=R){
		u->tag=0;
		u->laz=0;
		return u->turn0();
	}
	u->pushdown();
	turn0(u->ch[0],L,R);turn0(u->ch[1],L,R);
	return u->maintain();
}
void turn1(node*u,int L,int R){
	const int&l=u->l,&r=u->r;
	if(r<L||l>R) return;
	if(L<=l&&r<=R){
		u->tag=0;
		u->laz=1;
		return u->turn1();
	}
	u->pushdown();
	turn1(u->ch[0],L,R);turn1(u->ch[1],L,R);
	return u->maintain();
}
void _xor(node*u,int L,int R){
	const int&l=u->l,&r=u->r;
	if(r<L||l>R) return;
	if(L<=l&&r<=R){
		u->tag^=1;
		return u->_xor();
	}
	u->pushdown();
	_xor(u->ch[0],L,R);_xor(u->ch[1],L,R);
	return u->maintain();
}
int n,opt[N],cn;ll le[N],ri[N],B[N<<2];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%lld%lld",opt+i,le+i,ri+i);
		B[++cn]=le[i];
		if(le[i]-1>0) B[++cn]=le[i]-1;
		B[++cn]=ri[i];
		B[++cn]=ri[i]+1;
	}
	B[++cn]=1;
	sort(B+1,B+cn+1);
	cn=unique(B+1,B+cn+1)-B-1;
	build(rt,1,cn);
	for(int i=1;i<=n;i++){
		le[i]=lower_bound(B+1,B+cn+1,le[i])-B;
		ri[i]=lower_bound(B+1,B+cn+1,ri[i])-B;
		if(opt[i]==1) turn1(rt,le[i],ri[i]);
		else if(opt[i]==2) turn0(rt,le[i],ri[i]);
		else _xor(rt,le[i],ri[i]);
		printf("%lld\n",B[query()]);
	}
	return 0;
}
```

---

## 作者：Erusel (赞：1)

$\text{Codeforces}$ 的 $\text{tag}$ 真准确啊，这种题被划分成了 $\text{Trees-tag}$，我也是服了

---

题目要求支持以下三种操作：

$1.$ 把区间 $[l,r]$ 的所有数全部变成 $1$

$2.$ 把区间 $[l,r]$ 的所有数全部变成 $0$

$3.$ 把区间 $[l,r]$ 中的 $0$ 变成 $1$，$1$ 变成 $0$

每次操作后询问最左边的 $0$ 的位置

其中操作次数 $\leq 100000$，$l,r \leq 1e18$

因为 $l,r$ 很大，我们可以考虑把所有操作离线下来然后离散化

$3$ 操作和[这题]( https://www.luogu.org/problem/P2574 )中的操作是一样的，我们可以考虑用线段树维护区间和，

区间异或就相当于 $sum=len-sum$，其中 $sum$ 表示这段区间的和，$len$ 表示这段区间的长度

每次操作询问最左边 $0$ 的位置，有一种非常简单的做法，就是二分这个位置，

然后根据起点到这个点的位置这一段的区间和进行判断：

如果这一段的区间和等于这段区间的长度 ，往大的二分

否则往小的二分，记录答案

贴个部分的 $\text{Code}:$

```cpp
while(l<=r)
{
    int mid=(l+r)>>1;
    if(query(1,1,mid)==mid)l=mid+1;
    else ans=mid,r=mid-1;
}
```

但这样的时间复杂度单次操作是 $log^2{n}$ 的，我们有更优秀的做法

容易想到我们在线段树上从根节点往下跳，

如果左儿子区间和小于当前区间长度，那答案就在左儿子，否则就在右儿子

这样的时间复杂度是 $logn$ 的，总时间复杂度为 $O(nlogn)$

---

## 作者：The_foolishest_OIer (赞：0)

# 题解：MEX Queries

## 前情提要

以下是我的全部提交记录）：

![](https://cdn.luogu.com.cn/upload/image_hosting/1vr2mq5m.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/pfh2hd7f.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/a1b6c8l6.png)

## 做法：

看到题解区全是离线的，我就来一发在线的吧。

因为 $l,r$ 的值域大得离谱，故直接采用动态开点线段树（维护每个数是否存在）。

如果你不会动态开点，可以先做这题：[CF915E](https://www.luogu.com.cn/problem/CF915E)。

本题共有需维护三种标记。

对于第一种标记，因为无论前面有什么操作，都不会影响结果，直接赋值。

第二种同理。

对于第三种，这本质就是区间异或 $1$，如果前一个也是这种操作，那么就抵消了；如果是第一种，实际上就是进行了第二种操作；前面是第二种同理。

所以打标记代码很好写：


```cpp
void maketag (int o,ll l,ll r,char w){
	if (!lzy[o]){ // 没有直接打标记
		lzy[o] = w;
	}else if (w != 3){
		lzy[o] = w;
	}else{
		if (lzy[o] == w) lzy[o] = 0;
		else lzy[o] = (lzy[o] == 2 ? 1 : 2);
	}
	if (w == 1) sum[o] = r - l + 1;
	else if (w == 2) sum[o] = 0;
	else sum[o] = r - l + 1 - sum[o];
}
```

对于查询，可以采用线段树二分做到 $O(\log W)$ 的复杂度，$W$ 指的是值域。

于是就得到了第一版代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair <int,int>
#define pbb pair <bool,bool>
#define fi first
#define se second
#define mp make_pair
#define endl '\n'
const int N = 1.4e7 + 10;
int T,q;
struct Dynamic_SGT{
	ll mx = 1e18;
	ll sum[N];
	int o = 0,tot = 0;
	int ls[N],rs[N];
	char lzy[N];
	void pushup (int o){
		sum[o] = sum[ls[o]] + sum[rs[o]];
	} 
	void maketag (int o,ll l,ll r,char w){
		if (!lzy[o]){
			lzy[o] = w;
		}else if (w != 3){
			lzy[o] = w;
		}else{
			if (lzy[o] == w) lzy[o] = 0;
			else lzy[o] = (lzy[o] == 2 ? 1 : 2);
		}
		if (w == 1) sum[o] = r - l + 1;
		else if (w == 2) sum[o] = 0;
		else sum[o] = r - l + 1 - sum[o];
	}
	void pushdown (int o,ll l,ll r){
		if (!lzy[o]) return;
		if (!ls[o]) ls[o] = ++tot;
		if (!rs[o]) rs[o] = ++tot;
		ll mid = (l + r) >> 1ll;
		maketag(ls[o],l,mid,lzy[o]);
		maketag(rs[o],mid + 1,r,lzy[o]);
		lzy[o] = 0;
	}
	void update (int &o,ll l,ll r,ll ql,ll qr,char w){
		if (!o) o = ++tot;
		if (ql <= l && r <= qr){
			maketag(o,l,r,w);
			return;
		}
		pushdown(o,l,r);
		ll mid = (l + r) >> 1ll;
		if (ql <= mid) update(ls[o],l,mid,ql,qr,w);
		if (qr > mid) update(rs[o],mid + 1,r,ql,qr,w);
		pushup(o);
	}
	ll query (int &o,ll l,ll r){
		if (!o) o = ++tot;
		if (l == r) return l;
		pushdown(o,l,r);
		ll mid = (l + r) >> 1ll;
		if (sum[ls[o]] < mid - l + 1) return query(ls[o],l,mid);
		else return query(rs[o],mid + 1,r);
	}
};
Dynamic_SGT tr;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> q;
	while (q--){
		int op;
		ll l,r;
		cin >> op >> l >> r;
		tr.update(tr.o,1ll,tr.mx,l,r,op);
		cout << tr.query(tr.o,1ll,tr.mx) << endl;
	}
} 
signed main(){
	close();
	T = 1;
	//cin >> T;
	while (T--) solve();
	return 0;
}
```

## 优化

- 注意到上方的代码中的 `lzy` 数组用了 `char` 类型，实际上是为了节省空间。

- 关闭同步流会浪费空间。

- 因为许多点的 `sum` 是没有意义的，且 `sum` 数组必须开 `long long`，故选择调整 `sum` 的大小。

因为这个比较玄学，最后我一通乱搞终于通过了第 $15$ 个点。

实际上我们应该把 `mx` 调大，因为如果 $10^{18}$ 也符合要求，答案实际上是 $10^{18} + 1$。

所以得到了最终版代码。

## Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair <int,int>
#define pbb pair <bool,bool>
#define fi first
#define se second
#define mp make_pair
#define endl '\n'
const int N = 16533671;
const int M = 14855877; // 调参
int T,q;
struct Dynamic_SGT{
	ll mx = 1e18 + 5;
	ll sum[M];
	int o = 0,tot = 0;
	int ls[N],rs[N];
	char lzy[N];
	void pushup (int o){
		if (ls[o] > M - 3 || rs[o] > M - 3) return;
		sum[o] = sum[ls[o]] + sum[rs[o]];
	}
	void maketag (int o,ll l,ll r,char w){
		if (!lzy[o]){
			lzy[o] = w;
		}else if (w != 3){
			lzy[o] = w;
		}else{
			if (lzy[o] == w) lzy[o] = 0;
			else lzy[o] = (lzy[o] == 2 ? 1 : 2);
		}
		if (o > M - 3) return;
		if (w == 1) sum[o] = r - l + 1;
		else if (w == 2) sum[o] = 0;
		else sum[o] = r - l + 1 - sum[o];
	}
	void pushdown (int o,ll l,ll r){
		if (!lzy[o]) return;
		if (!ls[o] && tot < N - 3) ls[o] = ++tot;
		if (!rs[o] && tot < N - 3) rs[o] = ++tot;
		ll mid = (l + r) >> 1ll;
		maketag(ls[o],l,mid,lzy[o]);
		maketag(rs[o],mid + 1,r,lzy[o]);
		lzy[o] = 0;
	}
	void update (int &o,ll l,ll r,ll ql,ll qr,char w){
		if (!o && tot < N - 3) o = ++tot;
		if (ql <= l && r <= qr){
			maketag(o,l,r,w);
			return;
		}
		pushdown(o,l,r);
		ll mid = (l + r) >> 1ll;
		if (ql <= mid) update(ls[o],l,mid,ql,qr,w);
		if (qr > mid) update(rs[o],mid + 1,r,ql,qr,w);
		pushup(o);
	}
	ll query (int &o,ll l,ll r){
		if (!o && tot < N - 3) o = ++tot;
		if (l == r) return l;
		pushdown(o,l,r);
		ll mid = (l + r) >> 1ll;
		if (sum[ls[o]] != mid - l + 1) return query(ls[o],l,mid);
		else return query(rs[o],mid + 1,r);
	}
};
Dynamic_SGT tr;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> q;
	while (q--){
		int op;
		ll l,r;
		cin >> op >> l >> r;
		tr.update(tr.o,1ll,tr.mx + 5,l,r,op);
		cout << tr.query(tr.o,1ll,tr.mx + 5) << endl;
	}
} 
signed main(){
	//close();
	T = 1;
	//cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Others (赞：0)

这题的 $mex$ 先让我想到的是~~值域分块~~。

# Solution

这题用值域分块也可以，但是考场上不想被卡，于是我打了个权值线段树。

一、二操作及等同于在值域上区间赋 $1/0$，第三个操作可以看成区间取反，因为每个叶子节点的之只有可能是 $1/0$，所以取反时可以 $O(1)$ 得到计算后的值，这里就是简单的线段树。

然后讲讲比较关键的一个点：懒惰标记的下传。

这题的赋值显然可以直接覆盖（因为操作很“暴力”），取反时要考虑原有的懒标，如果是区间赋值的懒标就搞成另外一种区间赋值（$1$ 改成 $0$，$0$ 改成 $1$），如果本身是取反的标记的话就改成无标记的状态。

贴一个丑陋至极的代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
template<typename zqw>void qr(zqw &x){
	bool f=x=0;
	char c=getchar();
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x=f?~(x-1):x;
	return ;
}
int n,opt[800005],l[800005],r[800005],flag[800005],top,tot;
struct node{
	int l,r,lc,rc,sum,tag;
}tr[10000005];
void build(int l,int r,int p){
	tr[p].lc=p<<1,tr[p].rc=p<<1|1;
	tr[p].l=l,tr[p].r=r;
	if(l==r){
		tr[p].tag=-1;
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
}
void pushup(int p){
	tr[p].sum=tr[tr[p].lc].sum+tr[tr[p].rc].sum;
}
void pushdown(int p){
	if(tr[p].tag==2){
		tr[tr[p].lc].sum=tr[tr[p].lc].r-tr[tr[p].lc].l+1-tr[tr[p].lc].sum;
		tr[tr[p].rc].sum=tr[tr[p].rc].r-tr[tr[p].rc].l+1-tr[tr[p].rc].sum;
		
		if(tr[tr[p].lc].tag==1||tr[tr[p].lc].tag==0) tr[tr[p].lc].tag^=1;
		else if(tr[tr[p].lc].tag==2) tr[tr[p].lc].tag=-1;
		else tr[tr[p].lc].tag=2;
		
		if(tr[tr[p].rc].tag==1||tr[tr[p].rc].tag==0) tr[tr[p].rc].tag^=1;
		else if(tr[tr[p].rc].tag==2) tr[tr[p].rc].tag=-1;
		else tr[tr[p].rc].tag=2;
	}else if(tr[p].tag==1){
		tr[tr[p].lc].sum=tr[tr[p].lc].r-tr[tr[p].lc].l+1;
		tr[tr[p].rc].sum=tr[tr[p].rc].r-tr[tr[p].rc].l+1;
		tr[tr[p].lc].tag=tr[tr[p].rc].tag=1;
	}else if(tr[p].tag==0){
		tr[tr[p].lc].sum=tr[tr[p].rc].sum=0;
		tr[tr[p].lc].tag=tr[tr[p].rc].tag=0;
	}
	tr[p].tag=-1;
}
void update(int l,int r,int x,int p){
//	cout << tr[p].l << " " << tr[p].r << " " << l << " " << r << " " << p << endl;
	if(l<=tr[p].l&&r>=tr[p].r){
		tr[p].sum=(tr[p].r-tr[p].l+1)*x;
		tr[p].tag=x;
		return ;
	}
	int mid=tr[p].l+tr[p].r>>1;
	pushdown(p);
	if(l<=mid) update(l,r,x,tr[p].lc);
	if(r>mid) update(l,r,x,tr[p].rc);
	pushup(p);
//	cout << p << " " << tr[p].l << " " << tr[p].r << " " << tr[p].lc << " " << tr[p].rc << " " << tr[p].sum << endl;
}
void Flip(int l,int r,int p){
	if(l<=tr[p].l&&r>=tr[p].r){
		tr[p].sum=(tr[p].r-tr[p].l+1)-tr[p].sum;
		if(tr[p].tag==1||tr[p].tag==0) tr[p].tag^=1;
		else if(tr[p].tag==-1) tr[p].tag=2;
		else tr[p].tag=-1;
//		cout << tr[p].sum << endl;
		return;
	}
	int mid=tr[p].l+tr[p].r>>1;
	pushdown(p);
	if(l<=mid) Flip(l,r,tr[p].lc);
	if(r>mid) Flip(l,r,tr[p].rc);
	pushup(p);
}
int getsum(int p){
	if(tr[p].sum==0)return tr[p].l;
	if(tr[p].sum==tr[p].r-tr[p].l+1)return 0;
	pushdown(p);
	int l=getsum(p<<1);
	if(l)return l;
	l=getsum(p<<1|1);
	return l;
}
signed main() {
//	freopen("minimum.in","r",stdin);
//	freopen("minimum.out","w",stdout);
	qr(n);
	for(int i=1;i<=n;i++){
		qr(opt[i]),qr(l[i]),qr(r[i]);
		flag[++top]=l[i],flag[++top]=r[i];
		if(l[i]!=1)flag[++top]=l[i]-1;
		flag[++top]=r[i]+1;
	}
	flag[++top]=1;
 	sort(flag+1,flag+top+1);
 	top=unique(flag+1,flag+top+1)-flag-1;
 	build(1,top,1);
 	for(int i=1;i<=n;i++) {
 		l[i]=lower_bound(flag+1,flag+top+1,l[i])-flag,r[i]=lower_bound(flag+1,flag+top+1,r[i])-flag;
 	}
 	for(int i=1;i<=n;i++) {
 		if(opt[i]==1){
 			update(l[i],r[i],1,1);
 		}else if(opt[i]==2){
 			update(l[i],r[i],0,1);
 		}else{
 			Flip(l[i],r[i],1);
 		}
 		printf("%lld\n",flag[getsum(1)]);
 	}
	return 0;
}

```

---

## 作者：PosVII (赞：0)

**前言**

------------

本题使用权值线段树。

**思路**

------------

显然，数据需要进行离散化操作。把出现的删除和把没有的添加就是全部推平，可以使用懒标记。

第三个操作取反时需要注意，若此时子节点也有懒标记的话需要先下传。

同时，如果在操作赋值的同时也需要考虑该节点是否有懒标记，若有推平操作，取反即可。若有取反操作，负负得正可以抵消。

注意，如果所有操作都没有出现 $1$ 的话 $1$ 还是可以的，所以需要特殊地加一个 $1$。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=10e5+5;
int d[MAXN*4];
int lazy[MAXN*4];
void pushdown(int p,int dl,int dr) {
	if(dl==dr) return;
	int mid=(dl+dr)>>1;
	if(lazy[p]) {
		if(lazy[p]==1) {
			d[(p<<1)]=mid-dl+1;
			d[(p<<1)+1]=dr-mid;
			lazy[(p<<1)]=lazy[(p<<1)+1]=1;
		}
		if(lazy[p]==2) {
			d[(p<<1)]=d[(p<<1)+1]=0;
			lazy[(p<<1)]=lazy[(p<<1)+1]=2;
		}
		if(lazy[p]==3) {
			pushdown((p<<1),dl,mid);
			pushdown((p<<1)+1,mid+1,dr);
			d[(p<<1)]=mid-dl+1-d[(p<<1)];
			d[(p<<1)+1]=dr-mid-d[(p<<1)+1];
			lazy[(p<<1)]=lazy[(p<<1)+1]=3;
		}
		lazy[p]=0;
	}
}
void query(int l,int r,int dl,int dr,int p,int c) {
	if(dl>=l&&dr<=r) {
		if(c==1) d[p]=dr-dl+1;
		if(c==2) d[p]=0;
		if(c==3) d[p]=dr-dl+1-d[p];
		if(c==3) {
			if(lazy[p]==1) lazy[p]=2;
			else if(lazy[p]==2) lazy[p]=1;
			else if(lazy[p]==3) lazy[p]=0;
			else lazy[p]=3;
		}
		else lazy[p]=c;
		return;
	}
	int mid=(dl+dr)>>1;
	pushdown(p,dl,dr);
	if(l<=mid) query(l,r,dl,mid,(p<<1),c);
	if(r>mid) query(l,r,mid+1,dr,(p<<1)+1,c);
	d[p]=d[(p<<1)]+d[(p<<1)+1];
}
int ask(int dl,int dr,int p) {
	if(dl==dr) return dl;
	int mid=(dl+dr)>>1;
	pushdown(p,dl,dr);
	if(d[(p<<1)]!=mid-dl+1) return ask(dl,mid,(p<<1));
	return ask(mid+1,dr,(p<<1)+1);
}
void build(int l,int r,int p) {
	d[p]=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,(p<<1));
	build(mid+1,r,(p<<1)+1);
}
long long l[MAXN],r[MAXN],dir[MAXN];
int op[MAXN];
int n;
signed main() {
//	freopen("minimum.in","r",stdin);
//	freopen("minimum.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d %lld %lld",&op[i],&l[i],&r[i]);
		dir[i*3-1]=l[i],dir[i*3-2]=r[i],dir[i*3]=r[i]+1;
	}
	dir[3*n+1]=1;
	sort(dir+1,dir+2+3*n);
	int cnt=unique(dir+1,dir+2+3*n)-dir-1;
	build(1,cnt,1);
	for(int i=1;i<=n;++i) {
		l[i]=lower_bound(dir+1,dir+1+cnt,l[i])-dir;
		r[i]=lower_bound(dir+1,dir+1+cnt,r[i])-dir;
		query(l[i],r[i],1,cnt,1,op[i]);
		printf("%lld\n",dir[ask(1,cnt,1)]);
	}
	return 0;
}
```


---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF817F)

## 题意

>- 维护一个 $01$ 序列 $a_{1\sim10^{18}+1}$，初始均为 $0$。
>- 有 $n$ 组询问，每组询问输入三个数 $t,l,r$：
>- - $t=1$：把 $a_{l\sim r}$ 赋值为 $1$。
>- - $t=2$：把 $a_{l\sim r}$ 赋值为 $0$。
>- - $t=3$：把 $a_{l\sim r}$ 取反。
>- 每次操作后输出一个数 $x$，满足 $a_x=0$ 且 $x$ 最小。

## 分析

看到区间操作，显然第一时间可以想到线段树，对于 $t=1,2$ 的操作，维护一个标记 $tag1\in\{-1,0,1\}$，表示 $0$ 和 $1$ 表示把该区间复制为 $tag1$，$tag1=-1$ 表示没有标记，对于 $t=3$ 的操作，维护一个标记 $tag2\in\{0,1\}$ 表示是否有翻转。

然而题目求的是总体的 $\text{MEX}$，我们要找到最小的值为 $0$ 的位置，于是就可以维护一个值 $full\in\{0,1\}$ 表示该区间是否全为 $1$，查询答案是从根节点往下找，如果左子树全为 $1$ 那么答案就在右子树，否则在左子树。

然而这样并不好维护，经过翻转操作后无法确定 $full$ 的值，你不知道翻转前该区间是全为 $0$ 还是有一点 $1$，因此我们可以再维护一个值 $any\in\{0,1\}$ 表示区间中是否至少有一个 $1$，这样翻转某个区间的函数就很好写了：

```cpp
void rev(int p){//翻转p节点
	a[p].tag2^=1;//翻转标记
	if(a[p].full)
		a[p].full=a[p].any=0;//之前全是1，翻转后全是0
	else{
		a[p].full=!a[p].any;//之前没有满，翻转后的结果随any取值而定 
		a[p].any=1;//由于翻转前没有满，所以翻转后一定有1 
	}
}
```

赋值时，把 $full$ 和 $any$ 都改成赋的值就好了。

```cpp
void fuz(int p,int v){//赋值 
	a[p].any=a[p].full=a[p].tag1=v;
	a[p].tag2=0;//赋值后无所谓翻转 
}
```

相应的 $\text{pushup}$：

```cpp
void pushup(int p){
    a[p].full=a[pl].full&&a[pr].full;
    a[p].any=a[pl].any||a[pr].any;
}
```

由于 $l,r$ 范围过大，我一开始使用的是动态开点的线段树，然而由于树太深，开点操作太多导致 TLE 了，于是又加上了离散化才过，可动态开点加上离散化后就没太大用处了。

**关于离散化的提示：一定要有 $1$！定要有 $1$！要有 $1$！有 $1$！$1$！！**~~（手动回声~~

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
    long long x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=5e5+10;
#define pl a[p].tl
#define pr a[p].tr
#define DOP_S_T_T bool
struct DOP_Segment_Tree{
    int root,tot;
    struct Tree{
        ll l,r;
        int tl,tr;//左右子树 
        int tag1,tag2;
        DOP_S_T_T full,any;
    }a[N*4];
	void fuz(int p,int v){//赋值 
		a[p].any=a[p].full=a[p].tag1=v;
		a[p].tag2=0;//赋值后无所谓翻转 
	}
	void rev(int p){//翻转p节点
		a[p].tag2^=1;//翻转标记
		if(a[p].full)
			a[p].full=a[p].any=0;//之前全是1，翻转后全是0
		else{
			a[p].full=!a[p].any;//之前没有满，翻转后的结果随any取值而定 
			a[p].any=1;//由于翻转前没有满，所以翻转后一定有1 
		}
	}
	void pushup(int p){
	    a[p].full=a[pl].full&&a[pr].full;
	    a[p].any=a[pl].any||a[pr].any;
	}
    void pushdown(int p){
        if(a[p].tag1!=-1){
        	fuz(pl,a[p].tag1);
        	fuz(pr,a[p].tag1);
        	a[p].tag1=-1;
		}
		else if(a[p].tag2){
			if(a[pl].tag1==-1)
				rev(pl);
			else
				fuz(pl,!a[pl].tag1);
			if(a[pr].tag1==-1)
				rev(pr);
			else
				fuz(pr,!a[pr].tag1);
			a[p].tag2=0;
		}
    }
    void make(int p){//开点 
        if(!pl){
            ll mid=(a[p].l+a[p].r)>>1;
            a[pl=++tot].l=a[p].l;
            a[pl].r=mid;
            fuz(pl,0);
            a[pr=++tot].l=mid+1;
            a[pr].r=a[p].r;
            fuz(pr,0);
        }
    }
    void build(ll l,ll r){//建树 
        root=tot=1;
        a[root].l=l;
        a[root].r=r;
        fuz(root,0);
    }
    void change1(int p,ll l,ll r,DOP_S_T_T v){//赋值 
        if(l<=a[p].l&&a[p].r<=r){
            fuz(p,v);
            return;
        }
        make(p);
        pushdown(p);
        ll mid=(a[p].l+a[p].r)>>1;
        if(l<=mid)
            change1(pl,l,r,v);
        if(r>mid)
            change1(pr,l,r,v);
        pushup(p);
    }
    void change2(int p,ll l,ll r){//翻转 
        if(l<=a[p].l&&a[p].r<=r){
        	if(a[p].tag1!=-1) fuz(p,!a[p].tag1);
        	else rev(p);
            return;
        }
        make(p);
        pushdown(p);
        ll mid=(a[p].l+a[p].r)>>1;
        if(l<=mid)
            change2(pl,l,r);
        if(r>mid)
            change2(pr,l,r);
        pushup(p);
    }
    ll ask(int p){//查询 
        if(a[p].l==a[p].r)
            return a[p].l;
        make(p);
        pushdown(p);
        if(a[pl].full)
        	return ask(pr);
        return ask(pl);
    }
}tree;
int n,m;
ll t[N],l[N],r[N],a[4*N];
int main(){
	n=read();
	a[++m]=1;
	for(int i=1;i<=n;i++){
		t[i]=read();l[i]=read();r[i]=read();
		a[++m]=max(l[i]-1,1ll);a[++m]=l[i];
		a[++m]=r[i];a[++m]=r[i]+1;
	}
	sort(a+1,a+m+1);
	int tot=unique(a+1,a+m+1)-(a+1);
	tree.build(1,tot+10);
	for(int i=1;i<=n;i++){
		l[i]=lower_bound(a+1,a+tot+1,l[i])-a;
		r[i]=lower_bound(a+1,a+tot+1,r[i])-a;
		if(t[i]==1) tree.change1(1,l[i],r[i],1);
		if(t[i]==2) tree.change1(1,l[i],r[i],0);
		if(t[i]==3) tree.change2(1,l[i],r[i]);
		write(a[tree.ask(1)]);
		putchar('\n');
	}
    return 0;
}
```


---

## 作者：registerGen (赞：0)

[更好的阅读体验](https://registergen.github.io/post/ti-jie-cf817f-mex-queries/)

# Solution

首先要想到的是这个题的一个等价题面：

> 维护一个长为 $10^{18}$ 的 $01$ 序列，初始值均为 $0$。
> 三种操作：
> 1. 把 $[l,r]$ 变成 $1$。
> 2. 把 $[l,r]$ 变成 $0$。
> 3. 把 $[l,r]$ 中的 $0$ 变 $1$，$1$ 变 $0$。
> 每次操作后输出序列的最左边的 $0$ 的位置。
> 操作数 $\le 10^5$

然后看到区间赋值，就想到可爱的 Chtholly 啦！

操作 $1$，操作 $2$ 不用多说。

神奇的是，区间反转（操作 $3$）和查询的代码真的可以这样暴力：

```cpp
inline void reverse(ll l,ll r)
{
	Iter itr=split(r+1),itl=split(l);
	for(Iter it=itl;it!=itr;it++)
		it->v^=1;
}

inline ll query()
{
	for(Iter it=s.begin();it!=s.end();it++)
		if(it->v==0)return it->l;
	return -1;
}
```

注意开 `long long`。

# Code

```cpp
#include<cstdio>
#include<algorithm>
#include<set>

#define Iter std::set<Node>::iterator

typedef long long ll;

const int N=1e5;

struct Node
{
	ll l,r;
	mutable bool v;

	Node(ll _l,ll _r=0,bool _v=0):l(_l),r(_r),v(_v){}
};

inline bool operator<(const Node& x,const Node& y)
{
	return x.l<y.l;
}

std::set<Node> s;
ll n;

inline void read(ll& x)
{
	x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-48,c=getchar();
}

inline Iter split(ll pos)
{
	Iter it=s.lower_bound(Node(pos));
	if(it->l==pos&&it!=s.end())return it;
	it--;
	ll l=it->l,r=it->r;
	bool v=it->v;
	s.erase(it);
	s.insert(Node(l,pos-1,v));
	return s.insert(Node(pos,r,v)).first;
}

inline void assign(ll l,ll r,bool v)
{
	Iter itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(Node(l,r,v));
}

inline void reverse(ll l,ll r)
{
	Iter itr=split(r+1),itl=split(l);
	for(Iter it=itl;it!=itr;it++)
		it->v^=1;
}

inline ll query()
{
	for(Iter it=s.begin();it!=s.end();it++)
		if(it->v==0)return it->l;
	return -1;
}

int main()
{
	read(n);
	s.insert(Node(1,1e18,0)); // 先插入一个 1e18 的区间
	while(n--)
	{
		ll opt,l,r;
		read(opt),read(l),read(r);
		if(opt==1)assign(l,r,1);
		if(opt==2)assign(l,r,0);
		if(opt==3)reverse(l,r);
		printf("%lld\n",query());
	}
	return 0;
}
```

---

