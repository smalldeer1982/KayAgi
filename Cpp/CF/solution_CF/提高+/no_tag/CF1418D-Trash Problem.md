# Trash Problem

## 题目描述

Vova decided to clean his room. The room can be represented as the coordinate axis $ OX $ . There are $ n $ piles of trash in the room, coordinate of the $ i $ -th pile is the integer $ p_i $ . All piles have different coordinates.

Let's define a total cleanup as the following process. The goal of this process is to collect all the piles in no more than two different $ x $ coordinates. To achieve this goal, Vova can do several (possibly, zero) moves. During one move, he can choose some $ x $ and move all piles from $ x $ to $ x+1 $ or $ x-1 $ using his broom. Note that he can't choose how many piles he will move.

Also, there are two types of queries:

- $ 0 $ $ x $ — remove a pile of trash from the coordinate $ x $ . It is guaranteed that there is a pile in the coordinate $ x $ at this moment.
- $ 1 $ $ x $ — add a pile of trash to the coordinate $ x $ . It is guaranteed that there is no pile in the coordinate $ x $ at this moment.

Note that it is possible that there are zero piles of trash in the room at some moment.

Vova wants to know the minimum number of moves he can spend if he wants to do a total cleanup before any queries. He also wants to know this number of moves after applying each query. Queries are applied in the given order. Note that the total cleanup doesn't actually happen and doesn't change the state of piles. It is only used to calculate the number of moves.

For better understanding, please read the Notes section below to see an explanation for the first example.

## 说明/提示

Consider the first example.

Initially, the set of piles is $ [1, 2, 6, 8, 10] $ . The answer before the first query is $ 5 $ because you can move all piles from $ 1 $ to $ 2 $ with one move, all piles from $ 10 $ to $ 8 $ with $ 2 $ moves and all piles from $ 6 $ to $ 8 $ with $ 2 $ moves.

After the first query, the set becomes $ [1, 2, 4, 6, 8, 10] $ . Then the answer is $ 7 $ because you can move all piles from $ 6 $ to $ 4 $ with $ 2 $ moves, all piles from $ 4 $ to $ 2 $ with $ 2 $ moves, all piles from $ 2 $ to $ 1 $ with $ 1 $ move and all piles from $ 10 $ to $ 8 $ with $ 2 $ moves.

After the second query, the set of piles becomes $ [1, 2, 4, 6, 8, 9, 10] $ and the answer is the same (and the previous sequence of moves can be applied to the current set of piles).

After the third query, the set of piles becomes $ [1, 2, 4, 8, 9, 10] $ and the answer is $ 5 $ because you can move all piles from $ 1 $ to $ 2 $ with $ 1 $ move, all piles from $ 2 $ to $ 4 $ with $ 2 $ moves, all piles from $ 10 $ to $ 9 $ with $ 1 $ move and all piles from $ 9 $ to $ 8 $ with $ 1 $ move.

After the fourth query, the set becomes $ [1, 2, 4, 8, 9] $ and the answer is almost the same (the previous sequence of moves can be applied without moving piles from $ 10 $ ).

After the fifth query, the set becomes $ [1, 2, 4, 8, 9, 100] $ . You can move all piles from $ 1 $ and further to $ 9 $ and keep $ 100 $ at its place. So the answer is $ 8 $ .

After the sixth query, the set becomes $ [1, 2, 4, 8, 9, 50, 100] $ . The answer is $ 49 $ and can be obtained with almost the same sequence of moves as after the previous query. The only difference is that you need to move all piles from $ 50 $ to $ 9 $ too.

## 样例 #1

### 输入

```
5 6
1 2 6 8 10
1 4
1 9
0 6
0 10
1 100
1 50```

### 输出

```
5
7
7
5
4
8
49```

## 样例 #2

### 输入

```
5 8
5 1 2 4 3
0 1
0 2
0 3
0 4
0 5
1 1000000000
1 1
1 500000000```

### 输出

```
3
2
1
0
0
0
0
0
499999999```

# 题解

## 作者：Karry5307 (赞：4)

### 题意

数轴上有 $n$ 个点，每一次你可以将**所有**位置在 $x$ 的点移动到 $x-1$ 或者是移动到 $x+1$，花费为 $1$。

有 $q$ 次操作，每一次会在数轴上添加一个原来没有的点或者是删除一个原来已经有的点。在所有操作前和每一次操作后你需要回答将所有点集中到不超过两个点的最小花费。

$\texttt{Data Range:}1\leq n,q\leq 10^5$

### 前言

你打开了本题。

你发现是已经写过了 $998244353$ 遍的维护最大的邻项之差。

你熟练的写出了代码，但是发现需要分类讨论，很头疼。

你翻开了题解，发现题解也是分类讨论。

相信经历了这么多的你心中满满的“我太难了”。

那么这篇题解将拯救你于水火之中（？）

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13726170.html)

注意到肯定是左边一段的点放在一起右边一段的点放在一起。

假设当前一共有 $n$ 个点，从小到大依次为 $p_1,\cdots,p_n$，考虑让 $p_1,\cdots,p_k$ 放在一起，$p_{k+1},\cdots,p_n$ 放在一起，那么花费为 $p_k-p_1+p_n-p_{k+1}=(p_n-p_1)-(p_{k+1}-p_k)$。

注意到对于每一个加点删点的操作来说 $p_n-p_1$ 很容易维护，然后 $p_{k+1}-p_k$ 就是开个 `multiset` 维护最大差值就完了。

但是这东西需要分类讨论很麻烦，所以我们想个办法让维护这东西变得很轻松不需要分类讨论。

考虑 Splay 预处理的时候往里面加 $\infty$ 和 $-\infty$，所以我们也可以往里面加 $\infty$ 和 $-\infty$。

然后询问的时候最大的两个绝对是 $p_1-(-\infty)$ 和 $\infty-p_n$，于是只需要查询第三大的那个就好了，没有第三大的答案就是 $0$。

这么写可以规避各种各样的分类讨论，比如说什么新插入的值没有前驱后继啦，什么插入点之前 `multiset` 里元素不够啦什么的，何乐而不为呢？

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=2e5+51,inf=1e15;
multiset<ll>st,gap;
multiset<ll>::iterator it;
ll n,qcnt,op,u,prv,nxt,mx,mn;
ll x[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void erase(ll x)
{
	gap.erase(gap.find(x));
}
inline ll query()
{
	if(*gap.begin()>=1e12)
	{
		return 0;
	}
	it=st.begin(),mn=*(++it),it=st.end(),--it,mx=*(--it);
	return it=gap.end(),--it,--it,mx-mn-*(--it);
}
int main()
{
	n=read(),qcnt=read(),st.insert(inf),st.insert(-inf);
	for(register int i=1;i<=n;i++)
	{
		st.insert(x[i]=read());
	}
	sort(x+1,x+n+1),x[0]=-inf,x[n+1]=inf;
	for(register int i=1;i<=n+1;i++)
	{
		gap.insert(x[i]-x[i-1]);
	}
	printf("%lld\n",query());
	for(register int i=0;i<qcnt;i++)
	{
		op=read(),u=read();
		if(op==0)
		{
			it=st.find(u),prv=u-*(--it),it++,nxt=*(++it)-u;
			st.erase(u),erase(prv),erase(nxt),gap.insert(nxt+prv);
		}
		if(op==1)
		{
			it=st.upper_bound(u),nxt=*(it--),prv=*it,st.insert(u);
			erase(nxt-prv),gap.insert(nxt-u),gap.insert(u-prv);
		}
		if(*gap.begin()>=1e12)
		{
			puts("0");
			continue;
		}
		printf("%lld\n",query());
	}
}
```

---

## 作者：Lily_White (赞：4)

注意到，我们允许弄出两个垃圾堆来，每次扫一下会移动所有的在那个位置的垃圾堆。所以最后的局面应该弄成这样：
```plain
x------------------x            x---------------x
```

其中，`x`代表垃圾堆。

在这种情况下，我们直接推一个到另一个的位置上就行，所以这时答案为
$$ \max_{\forall i }x_i-\min_{\forall i}x_i-\operatorname{len}~gap$$

其中，$gap$ 为两个大线段中间的长度，实现的时候，可以维护所有相邻位置之间的 $gap$，并且通过```std::multiset```动态维护最大的那个。

时间复杂度为 $O(n \log n)$。

代码（C++11）
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, q;
const int N = 200020;
set<int> P;
multiset<int> G;
void add(int pos) {
  auto it = P.insert(pos).first;
  if (next(it) != P.end()) G.insert(*next(it) - pos);
  if (it != P.begin()) {
    G.insert(pos - *prev(it));
    if (next(it) != P.end()) G.erase(G.find(*next(it) - *prev(it)));
  }
}
void erase(int pos) {
  auto it = P.find(pos);
  if (next(it) != P.end()) G.erase(G.find(*next(it) - pos));
  if (it != P.begin()) {
    G.erase(G.find(pos - *prev(it)));
    if (next(it) != P.end()) G.insert(*next(it) - *prev(it));
  }
  P.erase(it);
}
int query(){
  if (P.size() <= 2) return 0;
  return *P.rbegin() - *P.begin() - *G.rbegin();
}
int main() {
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    int p;
    cin >> p;
    add(p);
  }
  cout << query() << endl;
  for (int i = 0; i < q; i++) {
    int type, x;
    cin >> type >> x;
    if (type == 0) erase(x); else add(x);
    cout << query() << endl;
  }
  return 0;
}
```

---

## 作者：ran_qwq (赞：2)

$2100$？$1500$！

将 $a$ 从小到大排序。

题目转化为求一个位置 $p$，使得 $a_p-a_1+a_n-a_{p+1}$ 最小。

这相当于求最大的 $a_{p+1}-a_p$。

用 set 维护当前的点集，用 multiset 维护相邻点的差。

每次加点或删点就相当于把一对相邻点拆开，或将两对相邻点合并，随便分讨一下就行了，注意边界判断。

```cpp
int n,m,a[N];
set<int>P;multiset<int>D;
#define itS set<int>::iterator
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++) P.insert(a[i]);
	for(int i=1;i<n;i++) D.insert(a[i+1]-a[i]);
	wr(P.size()>1?*prev(P.end())-*P.begin()-*prev(D.end()):0,"\n");
	for(int op,x;m--;) {
		op=rd(),x=rd();
		if(op) {
			set<int>::iterator i=P.lb(x);
			if(i!=P.begin()&&i!=P.end()) {
				itS j=prev(i);int s=*i,t=*j;
				P.insert(x),D.erase(D.lb(s-t)),D.insert(x-t),D.insert(s-x);
			} else if(i==P.begin()&&i!=P.end()) {
				int s=*i;
				P.insert(x),D.insert(s-x);
			} else if(i!=P.begin()&&i==P.end()) {
				itS j=prev(i);int s=*j;
				P.insert(x),D.insert(x-s);
			} else P.insert(x);
		} else {
			itS i=P.lb(x);
			if(i!=P.begin()&&i!=prev(P.end())) {
				itS j=prev(i),k=next(i);int s=*j,t=*k;
				P.erase(x),D.erase(D.lb(x-s)),D.erase(D.lb(t-x)),D.insert(t-s);
			} else if(i==P.begin()&&i!=prev(P.end())) {
				itS j=next(i);int s=*j;
				P.erase(x),D.erase(D.lb(s-x));
			} else if(i!=P.begin()&&i==prev(P.end())) {
				itS j=prev(i);int s=*j;
				P.erase(x),D.erase(D.lb(x-s));
			} else P.erase(x);
		}
		wr(P.size()>1?*prev(P.end())-*P.begin()-*prev(D.end()):0,"\n");
	}
}
```

---

## 作者：RedreamMer (赞：2)

[$\Large\texttt{CF1418D}$](https://www.luogu.com.cn/problem/CF1418D)

[$\small\texttt{In my cnblogs}$](https://www.cnblogs.com/RedreamMer/p/13904275.html)

前言：

强烈谴责这套 $\texttt{div.2}$ 的翻译（前面ABC更偏），做这套题目时想崩掉，还是读英文题面好。/cy

## 题意

可以参考参考神 [$\texttt{K\red{arry5307}}$](https://www.luogu.com.cn/user/60990) 的翻译，十分得清晰， 这里不多做赘述。

## 思路

其实思路十分显然，对于两颗木桩坐标为 $x_1$ , $x_2$产生的总花费，分三种情况讨论：

+ 显然左边的木桩左边的点全到左边的木桩，花费为 $x1-min_x$ 。

+ 显然右边的木桩右边的点全到右边的木桩，花费为 $max_x-x_2$ 。

+ 中间的点离哪棵木桩近就去哪，但是有一点十分重要，中间的木桩花费的最优情况肯定是分成两部分，左边到左边的木桩，右边到右边的木桩，令这两部分零界的点分别为 $x_3$ , $x_4$，产生的花费为 $(x_3-x_1)+(x_2-x_4)$ 。

花费全加起来，你会恍然大悟地发现，花费为 $(max_x-min_x)-(x_3-x_2)$ ( $x_2$ 和 $x_3$ 之间没有其它点)。

在每个状态下，$max_x$ 和 $min_x$ 是一定的，要让花费最小，问题就变成了**动态维护区间中任意两点之间最远的距离**。

题解区一群大佬用了蒟蒻我不会的~~科技~~轻松A掉了，于是蒟蒻我只好用大码量的线段树解决（vp时出现了一个小错误导致没有绝杀QwQ） 。

线段树维护三个值，区间内最长的两点间的距离，区间内最左边的点的位置，区间内最右边的点的位置。

~~你会发现顺便把动态维护最大值和最小值给做掉了，但是我原本还弄了个查询操作QwQ~~

具体的 $up$ 操作请见代码

## 代码

$4.99s$ 最优解第一

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ls n << 1
#define rs n << 1 | 1
const int N = 2e5;
inline int read()
{
    register int s = 0;
    register bool neg = 0;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        neg |= (c == '-');
    for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
        ;
    return (neg ? -s : s);
}

int a,b,q[N+10],p[N+10],top;
bool t[N+10];
struct node {
    int l,r,lmx,rmx,sum;
}s[N*4+10];
struct ask {
    int opt,x;
}ask[N+10];

inline void up(int n) {
    s[n].lmx=((s[ls].lmx==-1)?s[rs].lmx:s[ls].lmx);//区间内端点只有一个的时候将左端点和右端点赋值一样，方便操作。
    s[n].rmx=((s[rs].rmx==-1)?s[ls].rmx:s[rs].rmx);
    s[n].sum=max(max(s[ls].sum,s[rs].sum),s[ls].rmx!=-1&&s[rs].lmx!=-1?s[rs].lmx-s[ls].rmx:0);//注意左区间的右端点到有区间的左端点也要被统计在内
}

inline void build(int n,int l,int r) {
    s[n].l=l;
    s[n].r=r;
    s[n].sum=0;
    s[n].lmx=-1;
    s[n].rmx=-1;
    if(l==r) {
        if(t[l]) s[n].lmx=s[n].rmx=p[l];
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    up(n);
}

inline void insert(int n,int k) {
    if(s[n].l==s[n].r) {
        s[n].lmx=s[n].rmx=p[k];
        return;
    }
    int mid=(s[n].l+s[n].r)>>1;
    if(k<=mid) insert(ls,k);
    else insert(rs,k);
    up(n);
}

inline void del(int n,int k) {
    if(s[n].l==s[n].r) {
        s[n].lmx=s[n].rmx=-1;
        return;
    }
    int mid=(s[n].l+s[n].r)>>1;
    if(k<=mid) del(ls,k);
    else del(rs,k);
    up(n);
}

signed main()
{
    // freopen("in1.in","r",stdin);
    a=read();
    b=read();
    top=0;
    for(int i=1;i<=a;i++){
        q[i]=p[++top]=read();
    }
    for(int i=1;i<=b;i++) {
        ask[i].opt=read();
        ask[i].x=p[++top]=read();
    }
    sort(p+1,p+top+1);
    top=unique(p+1,p+top+1)-p-1;
    for(int i=1;i<=a;i++) t[lower_bound(p+1,p+top+1,q[i])-p]=1;
    build(1,1,top);
    printf("%d\n",s[1].rmx-s[1].lmx-s[1].sum);
    for(int i=1;i<=b;i++) {
        if(ask[i].opt==1)
            insert(1,lower_bound(p+1,p+top+1,ask[i].x)-p);
        else
            del(1,lower_bound(p+1,p+top+1,ask[i].x)-p);
        printf("%d\n",s[1].rmx-s[1].lmx-s[1].sum);
    }
    return 0;
}
```

十分遗憾的一题QwQ

---

## 作者：SlyCharlotte (赞：0)

提供一种不同的实现（？）

题目让你求 $\min_{i = 1}^{n-1}{a_i - a_1 + a_n - a_{i+1}}$，观察到 $a_1,a_n$ 都是定值。

实际上让你求 $\min_{i = 1}^{n-1}{a_i - a_{i+1}}$。

考虑使用 `set` 维护 $a_i-a_{i+1}$ 的值，添加元素 $x$ 其实就是找到最大的元素 $y$ 满足 $y < x$ 和第一个大于 $x$ 的元素，将他们的差值从 `set` 中删去，将 两个元素与 $x$ 的差值添加进 set 中。

我们可以再开一个 `set`，记录点集，寻找可以在集合上二分。

这里为了避免返回 `s.end()` 我们可以插入 `-INF,INF`，在找最小值时注意地址需要更改。

注意这里要用 `s.lower_bound(x)` 而不是 `lower_bound(s.begin(), s.end(), x)`，后者常数巨大。

### 实现

```cpp
ll n, q, sz;
ll a[maxn];
multiset<ll> b, st;

signed main()
{
    scanf("%lld%lld", &n, &q);
    b.insert(-INF), b.insert(INF), sz = 2;

    for (ll i = 1; i <= n; i++)
        scanf("%lld", &a[i]), b.insert(a[i]), sz++;
    sort(a + 1, a + 1 + n);
    for (ll i = 2; i <= n; i++)
        st.insert(a[i - 1] - a[i]);
    st.insert(-INF - a[1]), st.insert(a[n] - INF);

    if (sz <= 4)
        printf("0\n");
    else
        printf("%lld\n", *(-- --b.end()) - *(++b.begin()) + *(++ ++st.begin()));

    while (q--)
    {
        ll opt, x;
        scanf("%lld%lld", &opt, &x);
        ll itl = *(--b.lower_bound(x));
        ll itr = *b.upper_bound(x);
        if (opt == 1) // add
        {
            b.insert(x), sz++;
            st.erase(st.find(itl - itr));
            st.insert(itl - x), st.insert(x - itr);
        }
        else // remove
        {
            st.erase(st.find(itl - x));
            st.erase(st.find(x - itr));
            st.insert(itl - itr);
            b.erase(x), sz--;
        }

        if (sz <= 4)
            printf("0\n");
        else
            printf("%lld\n", *(-- --b.end()) - *(++b.begin()) + *(++ ++st.begin()));
    }
    return 0;
}
```



---

## 作者：Mikazuki_Munechika (赞：0)

这道题的思维难度是很低的，这里提供一种好写的方法。

首先我们观察到答案一定是 $ \min_{i} (a_n - a_{i + 1}) + (a_i - a_1) $，其中  $ a $ 已经有序，那么答案只跟 $ \max_i a_{i + 1} - a_i $ 有关了。

然后我们可以在插入和删除的时候维护相邻两个数的差值，注意到如果没有删除操作可以直接优先队列维护，但是谁说有删除就不行了？

于是我们可以搞这么一个东西：

```cpp
struct del_heap
{
	std::priority_queue<int> a,b;
	void push(int x) {a.emplace(x);}
	void erase(int x) {b.emplace(x);}
	void maintain() {for(; a.size() && b.size() && a.top()==b.top(); a.pop(),b.pop());}
	void pop() {maintain(),a.pop();}
	int top() {maintain();return a.top();}
	bool empty(){maintain();return a.empty();}
}Mn;
```

于是优先队列也支持撤销的操作了。

那么实现就是简单的了。

原始 OJ 提交：[link](https://codeforces.com/contest/1418/submission/229851928)

---

## 作者：ademik (赞：0)

#### 分析：

![](https://cdn.luogu.com.cn/upload/image_hosting/708js5ul.png)

具体的，对于上述插入节点的操作，我们有如下代码：

```cpp
set < int > s;  // 维护节点的位置
multiset < int > slen; // 维护间距
void add(int x)
{
    set < int > :: iterator it = s.lower_bound(x); // 找到大于等于 x 的节点。 
    int R = -1, L = -1; // 记录右节点， 左节点的位置
    if(it != s.end()) { // 如果存在右节点
    	R = *it; 
    	slen.insert(R - x); 
	}
	if(it != s.begin()) { // 如果存在左节点
		L = *(-- it);
		slen.insert(x - L);
	}
	if(L != -1 && R != -1) { // 如果左右节点都存在的话
		slen.erase(slen.lower_bound(R - L));
	}
	s.insert(x); // 最后插入 x 节点。 
    return;
}
```

时间复杂度为 $O(q\log n)$。

#### Code :

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
typedef long long i64;
const int N = 1e5 + 50;
int n, m;
set < int > s; 
multiset < int > slen;
void add(int x)
{
    set < int > :: iterator it = s.lower_bound(x);
    int R = -1, L = -1;
    if(it != s.end()) {
    	R = *it; 
    	slen.insert(R - x); 
	}
	if(it != s.begin()) {
		L = *(-- it);
		slen.insert(x - L);
	}
	if(L != -1 && R != -1) {
		slen.erase(slen.lower_bound(R - L));
	}
	s.insert(x);
    return;
}
void del(int x)
{
    s.erase(x);
    set < int > :: iterator it = s.lower_bound(x);
    int R = -1, L = -1;
    if(it != s.end()) {
    	R = *it; 
    	slen.erase(slen.lower_bound(R - x)); 
	}
	if(it != s.begin()) {
		L = *(-- it);
		slen.erase(slen.lower_bound(x - L));
	}
	if(L != -1 && R != -1) {
		slen.insert(R - L);
	}
    return; 
}
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >>n >>m; slen.insert(0);
    for(int i = 1, x; i <= n; i ++) {
        cin >>x; add(x);
    }
    cout <<(*s.rbegin() - *s.begin()) - *slen.rbegin() <<endl;
    while(m --) {
        int op, x; cin >>op >>x;
        if(op == 1) add(x);
        else del(x); 
        if(s.empty()) cout <<"0" <<endl;
        else cout <<(*s.rbegin() - *s.begin()) - *slen.rbegin() <<endl;
    }
    return 0;
} 
```

---

## 作者：Jerrywang09 (赞：0)

### 先说几句

感谢 @feecle6418 提出改进方案！

一道有趣的数据结构题，有一点难想。

### 解题思路

合并很多点，使得最后只剩下 $2$ 个点，最优的策略是什么？

假设现在有 $5$ 个点，下面是一种合并方案：
![](https://cdn.luogu.com.cn/upload/image_hosting/1ama7o3a.png)

左右的向内逼近，一步一步合并，不走中间的最大空隙。也就是，$1$ 先合并给 $2$，$1,2$ 合并完成的合并给 $3$，$5$ 合并给 $4$。

如果按照上述方法操作，最后只剩 $2$ 个点 $3,4$。发现，其实这个过程的代价就是轴的总长度减去不合并的那一段长度。轴的总长度是不变的，为了让代价最小，不合并的那一段长度应尽可能长。因而上图方案就是最优方案的一个例子。

- 对于每个添加操作，只需把一个区间剖成两半；删除操作，只需把两个零碎区间合并起来。过程中我们需要
**查询前驱、后继**
操作。

- 应答询问时需要求出最左右两点距离减去中间的最大空隙。过程中我们需要
**查询最值**
操作。

综上，首选的数据结构是系统自带的 set 和 multiset。set 维护点集，multiset 维护空隙集合。

最后一点注意：在 multiset $S$ 根据键值 **只删除一个** $x$，而不是删除全部的 $x$，我们使用 `S.erase(S.find(x))` 而不是 `S.erase(x)`。

### 奉上代码

```cpp
/*
Title:  Trash Problem
Source: Educational Codeforces Round 95
*/
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, s, t) for(int i=s; i<=t; i++)
#define F first
#define S second
#define ll long long
#define all(x) x.begin(), x.end()
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=200010;
using namespace std;

set<int> S; multiset<int> gap;                              // S是垃圾集合，gap存储最大空隙 
int n, T;

void Insert(int x)
{
    S.insert(x); auto it=S.find(x); 
    int prv=-1, nxt=-1;
    if(it!=S.begin())
    {
        gap.insert(x-*prev(it));                            // 插入前驱到当前点的距离 
        prv=*prev(it);
    }
    it++;
    if(it!=S.end())
    {
        gap.insert(*it-x);                                  // 插入后继到当前点的距离
        nxt=*it;
    }
    if(prv!=-1 && nxt!=-1)
        gap.erase(gap.find(nxt-prv));                       // 原来的一段被剖开 
}

void Delete(int x)
{
    auto it=S.find(x); 
    int prv=-1, nxt=-1;
    if(it!=S.begin())
    {
        gap.erase(gap.find(x-*prev(it)));                   // 删除前驱到当前点的距离 
        prv=*prev(it);
    }
    it++;
    if(it!=S.end())
    {
        gap.erase(gap.find(*it-x));                         // 删除后继到当前点的距离
        nxt=*it;
    }
    S.erase(x);
    if(prv!=-1 && nxt!=-1)
        gap.insert(nxt-prv);                                // 合并原来剖开的整段 
}

signed main()
{
    scanf("%d %d", &n, &T);
    rep(i, 1, n)
    {
        int x; scanf("%d", &x);
        Insert(x);
    }
    int ans=0;
    if(gap.size())
        ans=*prev(S.end())-*S.begin()-*prev(gap.end());
    printf("%d\n", ans);
    while(T--)
    {
        int o, x; scanf("%d %d", &o, &x);
        if(o==0) Delete(x);
        else Insert(x);
        ans=0;
        if(gap.size())
            ans=*prev(S.end())-*S.begin()-*prev(gap.end()); // 距离就是中间最大的空隙不移动 
        printf("%d\n", ans);
    }

    return 0;
}
```

---

