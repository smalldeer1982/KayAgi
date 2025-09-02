# Facer和教官

## 题目背景

Facer和教官关系很好，被教官任命为副教官。

## 题目描述

Facer 要训练一个 $N$ 个人的队伍。

每个人有一个智力值 $a_i$ 和一个体力值 $b_i$。

Facer 希望两个人组队，组队的两个人要尽量相似。

具体来说，编号为 $i$ 和 $j$ 的人的相似度为 $| a_i - a_j + b_j - b_i | + | a_i - a_j |$。相似度越小，表示越相似。

现在队伍里有 $N$ 个人，但是 Facer 想要进行 $M$ 次操作。有以下两种操作：

- 在队伍里加入一个人。
- 给出一个**不在队伍里**的人的数据，输出他和队伍里所有人的相似度中最低的相似度。注意，操作结束后，**不要将这个人加入队伍，也不要将找到的人移出队伍**。

## 说明/提示

对于 $40\%$ 的数据，$1 \le N,M \le 1000$。

对于 $100\%$ 的数据，$1 \le N,M \le {10}^5$。

## 样例 #1

### 输入

```
3 3
1 7
2 -1
6 6
1 1 5
2 4 5
2 3 0```

### 输出

```
3
1
```

# 题解

## 作者：zhengrunzhe (赞：5)

首先观察公式

$$cmp(i,j) =| ai - aj + bj - bi | + | ai - aj | $$

看到两个绝对值，左边一个绝对值加右边一个绝对值，是不是很像曼哈顿距离？

由于动态加点，这时候我们选择强上K-D Tree

普通的平面最近曼哈顿点对的估价函数我们是这样写的

$$max(minx-x,0)+max(x-maxx,0)+max(miny-y,0)+max(y-maxy,0)$$

同理，我们也需要对cmp函数进行正确的估价

一开始我是这么想的：

绝对值不等式：

$$|x|+|y|>=|x-y|$$

令

$$x=ai-aj+bj-bi,y=ai-aj$$

代入得

$$cmp(i,j)=|ai-aj+bj-bi|+|ai-aj|=|x|+|y|>=|x-y|$$

即

$$cmp(i,j)>=|ai-aj+bj-bi-(ai-aj)|$$

   $$cmp(i,j)>=|bj-bi|$$
       
然后估价函数可以这么写：

$$max(minb-b,0)+max(b-maxb,0)$$

然后提交一波

```cpp
//50分代码 请勿模仿
#include<cstdio>
#include<algorithm>
using namespace std;
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool fh=0;
	while (ch<48||ch>57)fh=ch=='-'?1:fh,ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (fh)in=-in;
}
const int K=2,N=1e5+10,M=1e5+10,INF=2147483647;
int n,m,f;
struct point
{
	int d[K];
	inline const bool operator<(const point &p)const
	{
		return d[f]<p.d[f];
	}
	inline const friend int cmp(const point &a,const point &b)
	{
		return abs(a.d[0]-b.d[0]+b.d[1]-a.d[1])+abs(a.d[0]-b.d[0]);
	}
}w[N+M];
template<int K>class KD_Tree
{
	static const double alpha=0.75;
	private:
		struct tree
		{
			int size;
			tree *son[2];
			point range,mx,mn;
			inline const void pushup()
			{
				size=son[0]->size+1+son[1]->size;
				for (int i=0;i<K;i++)
					mx.d[i]=max(range.d[i],max(son[0]->mx.d[i],son[1]->mx.d[i])),
					mn.d[i]=min(range.d[i],min(son[0]->mn.d[i],son[1]->mn.d[i]));
			}
			inline const bool unbalanced()
			{
				return son[0]->size>size*alpha||son[1]->size>size*alpha;
			}
			inline const int evalue(const point &x)
			{
				return max(mn.d[1]-x.d[1],0)+max(x.d[1]-mx.d[1],0);
			}
		}memory_pool[N+M],*recycle[N+M],*null,*tail,*root;
		int top,rnk,mn;
		inline const void init()
		{
			tail=memory_pool;
			null=tail++;
			root=null->son[0]=null->son[1]=null;
			for (int i=0;i<K;i++)
				null->range.d[i]=0,
				null->mx.d[i]=-INF,
				null->mn.d[i]=INF;
			null->size=top=0;
		}
		inline tree *spawn(const point &x)
		{
			tree *p=top?recycle[--top]:tail++;
			p->size=1;
			p->mn=p->mx=p->range=x;
			p->son[0]=p->son[1]=null;
			return p;
		}
		inline const void travel(tree *p)
		{
			if (p==null)return;
			travel(p->son[0]);
			w[++rnk]=p->range;
			recycle[top++]=p;
			travel(p->son[1]);
		}
		inline tree *build(int l,int r,int d)
		{
			if (l>r)return null;
			int mid=l+r>>1;f=d;
			nth_element(w+l,w+mid,w+r+1);
			tree *p=spawn(w[mid]);
			if (l==r)return p;
			p->son[0]=build(l,mid-1,(d+1)%K);
			p->son[1]=build(mid+1,r,(d+1)%K);
			p->pushup();
			return p;
		}
		inline const void rebuild(tree *&p)
		{
			rnk=0;
			travel(p);
			p=build(1,rnk,0);
		}
		inline tree **add(tree *&p,const point &x,int d)
		{
			if (p==null)return p=spawn(x),&null;
			tree **bad=add(p->son[p->range.d[d]<x.d[d]],x,(d+1)%K);
			p->pushup();
			if (p->unbalanced())bad=&p;
			return bad;
		}
		inline const void query(tree *p,const point &x)
		{
			if (p==null)return;//printf("(%d,%d)\n",p->range.d[0],p->range.d[1]);
			mn=min(mn,cmp(p->range,x));
			int f[2]={INF,INF};
			if (p->son[0]!=null)f[0]=p->son[0]->evalue(x);
			if (p->son[1]!=null)f[1]=p->son[1]->evalue(x);//printf("%d %d %d\n",mn,f[0],f[1]);
			bool t=f[0]>=f[1];
			if (f[t]<mn)query(p->son[t],x);t^=1;
			if (f[t]<mn)query(p->son[t],x);
		}
	public:
		inline KD_Tree(){init();}
		inline const void insert(const point &x)
		{
			tree **bad=add(root,x,0);
			if (*bad!=null)rebuild(*bad);
		}
		inline const int query(const point &x)
		{
			mn=INF;
			query(root,x);
			return mn;
		}
		inline const void build()
		{
			root=build(1,n,0);
		}
};
KD_Tree<K>kdt;
int main()
{
	read(n);read(m);
	for (int i=1;i<=n;i++)for (int j=0;j<K;j++)read(w[i].d[j]);
	kdt.build();
	while (m--)
	{
		int opt;point c;
		read(opt);
		for (int i=0;i<K;i++)read(c.d[i]);
		if (opt==1)kdt.insert(c);
		else printf("%d\n",kdt.query(c));
	}
	return 0;
}
```

就愉快的tle拿50分了

原因在于：这个估价函数太low了，正确性有保证但是无法获得合理高效的时效

然后我们再看一眼式子

$$cmp(i,j) =| ai - aj + bj - bi | + | ai - aj | $$

$$cmp(i,j)=|(bj-ai)-(bi-ai)|+|ai-aj|$$

我*，这不就是裸的平面最近点对吗

**把(b-a)当做第一维，a当做第二维,cmp(i,j)就是点i,j的曼哈顿距离**

于是愉快地K-D Tree通过了此题

```cpp
//100分代码
#include<cstdio>
#include<algorithm>
using std::abs;
using std::max;
using std::min;
using std::nth_element;
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
const int K=2,N=1e5+10,M=1e5+10,INF=2147483647;
int n,m,f;
struct point
{
	int d[K];
	inline point(int x=0,int y=0){d[0]=x;d[1]=y;}
	inline const bool operator<( const point &p)const
	{
		return d[f]<p.d[f];
	}
	inline const friend int manhattan( const point &a, const point &b)
	{
		int dis=0;
		for (int i=0;i<K;i++)dis+=abs(a.d[i]-b.d[i]);
		return dis;
	}
}w[N+M];
template<int K>class KD_Tree
{
	static const double alpha=0.75;
	private:
		struct tree
		{
			int size;
			tree *son[2];
			point range,mx,mn;
			inline const void pushup()
			{
				size=son[0]->size+1+son[1]->size;
				for (int i=0;i<K;i++)
					mx.d[i]=max(range.d[i],max(son[0]->mx.d[i],son[1]->mx.d[i])),
					mn.d[i]=min(range.d[i],min(son[0]->mn.d[i],son[1]->mn.d[i]));
			}
			inline const bool unbalanced()
			{
				return son[0]->size>size*alpha||son[1]->size>size*alpha;
			}
			inline const int evalue(const point &x)
			{
				int f=0;
				for (int i=0;i<K;i++)f+=max(mn.d[i]-x.d[i],0)+max(x.d[i]-mx.d[i],0);
				return f;
			}
		}memory_pool[N+M],*recycle[N+M],*null,*tail,*root;
		int top,rnk,flag,mn;
		inline const void init()
		{
			tail=memory_pool;
			null=tail++;
			root=null->son[0]=null->son[1]=null;
			for (int i=0;i<K;i++)null->mx.d[i]=-INF,null->mn.d[i]=INF;
		}
		inline tree *spawn(const point &x)
		{
			tree *p=top?recycle[--top]:tail++;
			p->size=1;
			p->mn=p->mx=p->range=x;
			p->son[0]=p->son[1]=null;
			return p;
		}
		inline const void travel(tree *p)
		{
			if (p==null)return;
			travel(p->son[0]);
			w[++rnk]=p->range;
			recycle[top++]=p;
			travel(p->son[1]);
		}
		inline tree *build(int l,int r,int d)
		{
			if (l>r)return null;
			int mid=l+r>>1;f=d;
			nth_element(w+l,w+mid,w+r+1);
			tree *p=spawn(w[mid]);
			if (l==r)return p;
			p->son[0]=build(l,mid-1,d^1);
			p->son[1]=build(mid+1,r,d^1);
			p->pushup();
			return p;
		}
		inline const void rebuild(tree *&p,int d)
		{
			rnk=0;
			travel(p);
			p=build(1,rnk,d);
		}
		inline tree **insert(tree *&p,const point &x,int d)
		{
			if (p==null)return p=spawn(x),&null;
			tree **bad=insert(p->son[p->range.d[d]<x.d[d]],x,d^1);
			p->pushup();
			if (p->unbalanced())bad=&p,flag=d;
			return bad;
		}
		inline const void query(tree *p,const point &x)
		{
			mn=min(mn,manhattan(p->range,x));
			int f[2]={INF,INF};
			if (p->son[0]!=null)f[0]=p->son[0]->evalue(x);
			if (p->son[1]!=null)f[1]=p->son[1]->evalue(x);
			bool t=f[0]>=f[1];
			if (f[t]<mn)query(p->son[t],x);t^=1;
			if (f[t]<mn)query(p->son[t],x);
		}
	public:
		inline KD_Tree(){init();}
		inline const void insert(int x,int y)
		{
			tree **bad=insert(root,point(y-x,x),flag=0);
			if (*bad==null)return;
			rebuild(*bad,flag);
		}
		inline const int query(int x,int y)
		{
			mn=INF;
			query(root,point(y-x,x));
			return mn;
		}
};
KD_Tree<K>kdt;
int main()
{
	read(n);read(m);
	for (int x,y,i=1;i<=n;i++)read(x),read(y),kdt.insert(x,y);
	for (int opt,x,y;m--;)
		if (read(opt),read(x),read(y),opt==1)kdt.insert(x,y);
		else printf("%d\n",kdt.query(x,y));
	return 0;
}
```

---

## 作者：Jian_Yu (赞：3)

我不会写 K-D Tree，所以有了这篇题解。

首先我们会发现：

$$
|a_i-a_j+b_j-b_i|+|a_i-a_j|=|(a_i-b_i)-(a_j-b_j)|+|a_i-a_j|
$$

因此把每个人当做平面上位于 $(a_i-b_i,a_i)$ 的点，题目就变成在平面上了动态插入点和查询距离一个点曼哈顿距离最小的点。

而我们将坐标系旋转 $45$ 度，曼哈顿距离就可以被转化为切比雪夫距离，不会的可以先去做做[这题](https://www.luogu.com.cn/problem/AT_code_festival_2017_quala_d)。

而距离点 $(x,y)$ 切比雪夫距离 $\le k$ 的点就是位于以 $(x-k,y-k)$ 与 $(x+k,y+k)$ 为顶点的矩形中的所有点。

因此我们可以二分套二维线段树来解决这道题，时间复杂度 $O(n\log^3n)$，~~略微卡常~~。

如果你卡不过去：

- 数据中的数都不大于 $5 \times 10^4$，但是题面中没有说（

- 可以尝试用一个 `set` 来维护 $x$ 在节点的对应区间上中的点所有 $y$ 值，这样可以避免树套树的巨大常数和动态开点的开销。

- 由于线段树上接近根部的点几乎每次都会被插入，而这些点几乎不会在查询的时候被用到，而且对点数多的 `set` 进行插入操作的常数很大，所以可以在遇到与根节点距离小于一定值的点时跳过关于他们的操作，直接往他们的儿子递归。

- 如果当前节点上没有数，直接返回。

- 坐标映射完之后一个维度上的值域会比另一个维度上的值域大，我们可以选择值域小的维度作为下标来维护。

- 在线段树上查询时如果一个点的两个儿子都需要递归查询，可以优先查询内部节点更多的儿子，这样有更大的概率直接返回（~~虽然感觉不是很有用的样子~~

- 大部分的询问答案都很小，所以我们可以在二分前判定几个比较小的值，如果已经判定失败了就直接把二分的右端点设为他们。（或者在对数轴上二分？

- 发现插入的次数相对于查询的次数比较少，所以可以把 `set` 换成 `vector` 来规避 `set` 的大常数，然后插入的时候就暴力插入。

加上以上的优化~~和一些神秘调参和一些运气加持~~，我们就以 $O(n\log^3n)$ 的优秀时间复杂度通过了这题！

记得点赞 QwQ

```
#include <algorithm>
#include <iostream>
#include <string.h>
#include <random>
#include <set>
using namespace std;
const int N = 5e4;

mt19937 rnd(random_device{}());

struct node {
	int l, r;
	vector<int> dots;
} tr[8*N];

#define self tr[rt]
#define ls (rt<<1)
#define rs (rt<<1|1)

void build(int l, int r, int rt=1) {
	self.l = l, self.r = r; int m = (l + r) >> 1;
	if(l < r) build(l, m, ls), build(m + 1, r, rs);
}

const int T = 8000;

void modify(int x, int y, int rt=1) {
	if(rt > T)
		self.dots.insert(lower_bound(self.dots.begin(), self.dots.end(), y), y);
	if(self.l < self.r) {
		if(x <= tr[ls].r) modify(x, y, ls);
		if(tr[rs].l <= x) modify(x, y, rs);
	}
}

int query(int x, int y, int l, int r, int rt=1) {
	if(self.l > y or x > self.r) return 0;
	if(rt > T && self.dots.empty()) return 0;
	if(rt > T && x <= self.l and self.r <= y) {
		auto p = lower_bound(self.dots.begin(), self.dots.end(), l);
		return p != self.dots.end() && *p <= r;
	}
	if(tr[ls].dots.size() > tr[rs].dots.size())
		return query(x, y, l, r, ls) | query(x, y, l, r, rs);
	else return query(x, y, l, r, rs) | query(x, y, l, r, ls);
}

int n, m;
int o, x, y;

inline int check(int x, int y, int p) {
	return query(x - p, x + p, y - p, y + p);
}

inline int get(int x, int y) {
	int l = -1, r = 8000;
	if(check(x, y, 10)) r = 10;
	else if(check(x, y, 100)) r = 100;
	else if(check(x, y, 500)) r = 500;
	while(r - l > 1) {
		int mid = (l + r) >> 1;
		if(check(x, y, mid))
			r = mid;
		else l = mid;
	}
	return r;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	build(-N, N), cin >> n >> m;
	for(int i = 1; i <= n; ++i)
		cin >> x >> y, modify(y, 2 * x - y);
	for(; m--; ) {
		cin >> o >> x >> y;
		if(o == 1) modify(y, 2 * x - y);
		else cout << get(y, 2 * x - y) << "\n";
	}
}
```

---

