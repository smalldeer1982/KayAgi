# Segment Covering

## 题目描述

ChthollyNotaSeniorious 给了 DataStructures 一条数轴，上面有 $m$ 个互不相同的线段。设 $f(l,r)$ 表示选择偶数个线段，使得它们的并恰好为 $[l,r]$ 的方案数，$g(l,r)$ 表示选择奇数个线段，使得它们的并恰好为 $[l,r]$ 的方案数。

ChthollyNotaSeniorious 向 DataStructures 提出了 $q$ 个问题。在每个询问中，ChthollyNotaSeniorious 会给出两个数 $l, r$，现在他希望你能帮他计算 $f(l,r)-g(l,r)$ 模 $998\,244\,353$ 的值，这样他就不会让她失望了。

## 说明/提示

在第一个询问中，我们需要计算 $f(1, 4) - g(1, 4)$。唯一一个线段子集的并为 $[1, 4]$，即 $\{[1, 3], [2, 4]\}$，所以 $f(1, 4) = 1, g(1, 4) = 0$。

在第二个询问中，我们需要计算 $f(1, 5) - g(1, 5)$。唯一的线段子集的并为 $[1, 5]$ 的有 $\{[1, 3], [2, 4], [3, 5]\}$ 和 $\{[1, 3], [3, 5]\}$，所以 $f(1, 5) = 1, g(1, 5) = 1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
1 3
4 6
2 4
3 5
1 4
1 5```

### 输出

```
1
0```

# 题解

## 作者：Little09 (赞：16)

先膜拜出题人 @[1kri](https://www.luogu.com.cn/user/235926)，贡献了一道质量很高的题目。这道题也告诉了我们：看到奇偶相减不止想到 LGV，还可以去挖掘性质，有了性质问题会简化许多。

首先假设有两条线段 $X,Y$ 满足 $X$ 包含了 $Y$，那么 $X$ 是可以被删除的。原因是：如果选择了 $X$，那么 $Y$ 是否选择，可以给奇偶分别产生相等的贡献，所以我们可以删除 $X$。

对于一组 $[l,r]$，我们考虑所有完全被包 $[l,r]$ 含的线段。对于这些线段，我们按照左端点排序。由于现在没有线段有包含关系了，所以右端点其实也排好了序。考虑三条按序的线段，如果满足 $l_1<l_2<l_3<r_1$，那么会发现如果同时选择了 $1$ 和 $3$，那么 $2$ 是否选择都会给奇偶产生相等的贡献，所以 $3$ 也可以被删除（因为此时 $1$ 是必须选择的）。这样又可以推出 $2$ 必须选择，就可以按此递推下去。

按照上面的方式删除线段后，剩下的所有线段都必须选择。所以如果剩下 $k$ 条线段，且满足 $[l_1, r_1] \cup [l_2, r_2] \cup \cdots \cup [l_k, r_k] = [l, r]$，那么答案是 $(-1)^k$；否则答案是 $0$。线段如下图所示：

![](https://s2.loli.net/2022/04/28/q3ypMouNFBawil4.png)

按上图的答案就是 $0$，因为并集不是 $[l,r]$。

再想一下每组询问我们做了什么：询问前先扔掉所有包含其他线段的线段，每次询问我们先找到左端点就是 $l$ 的线段和左端点大于 $l$ 且最小的两条线段作为起始线段。从他们开始，设他们编号 $1,2$，我们先从 $1$ 找到一个左端点大于 $r$ 且最小的线段 $3$，再对 $2$ 做，一直这么做下去，直到右端点到达 $r$。

接下来我们考虑 $q$ 组询问。我们按照上面这个步骤进行一个预处理：对于线段 $i$，我们找到最小的 $j$ 满足 $l_j>r_i$，建一棵树（森林），我们令 $fa_i=j$。事实上不用把树显式建出来，只要 $fa$ 数组就行。

这样我们每次先找到两条初始线段，只要线段范围没有超过 $r$，就一直倍增向后面跳 $fa$ ，如果最终两条线段的右端点还没到 $r$，或者最终两条线段是相同的，那么答案就是 $0$ 了。

最终跳到的线段相同的时候，表明中间存在一段空隙，没有被任何线段覆盖。比如上图的情况，从 $1,2$ 开始跳都会到达 $5$，$r_4$ 和 $l_5$ 之间存在了空隙，所以答案是 $0$。

否则我们可以通过倍增的次数算出总共有奇数还是偶数条线段，从而确定答案是 $1$ 还是 $998244352$。

```cpp
const int N=200005;
int n,m,cnt; 
struct point
{
	int x,y;
}a[N],b[N];
bool operator < (const point &x,const point &y)
{
	if (x.x==y.x) return x.y>y.y;
	return x.x<y.x;
}
int f[N][21];
int ask(int x)
{
	return lower_bound(b+1,b+cnt+1,(point){x,inf})-b;
}

int query(int l,int r)
{
	int u=ask(l);
	if (u>cnt||b[u].x!=l) return 0;
	if (b[u].y==r) return mod-1;
	int v=ask(l+1);
	if (v>cnt||b[v].x>b[u].y) return 0;
	if (b[v].y>r) return 0;
	int res=0;
	for (int i=20;i>=0;i--)
	{
		if (f[u][i]<=cnt&&b[f[u][i]].y<=r)
		{
			u=f[u][i];
			if (!i) res^=1;
		}
	}
	for (int i=20;i>=0;i--)
	{
		if (f[v][i]<=cnt&&b[f[v][i]].y<=r)
		{
			v=f[v][i];
			if (!i) res^=1;
		}
	}
	if (u==v) return 0;
	if (b[u].y==r||b[v].y==r) 
	{
		if (res) return mod-1;
		return 1;
	}
	return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for (int i=1;i<=n;i++) cin >> a[i].x >> a[i].y;
	sort(a+1,a+n+1);
	int mx=inf;
	for (int i=n;i>=1;i--)
	{
		if (a[i].y>=mx) continue;
		mx=min(mx,a[i].y);
		b[++cnt]=a[i];
	}
	sort(b+1,b+cnt+1);
	int tmp=1;
	for (int i=1;i<=cnt;i++)
	{
		while (tmp<=cnt&&b[tmp].x<=b[i].y) tmp++;
		f[i][0]=tmp;
	}
	for (int i=0;i<=20;i++) f[cnt+1][i]=cnt+1;
	for (int i=1;i<=20;i++)
	{
		for (int j=1;j<=cnt;j++)
		{
			f[j][i]=f[f[j][i-1]][i-1];
		}
	}
	while (m--)
	{
		int l,r;
		cin >> l >> r;
		cout << query(l,r) << "\n";
	}
	return 0;
}
```


---

## 作者：Alex_Wei (赞：11)

非常好的题目！

不在区间上挖一些性质是很难做的，而区间最常见且最有用的一个性质就是 **不包含**。

考虑两个区间 $[x', y']\subset [x, y]$，则对于任意包含 $[x, y]$ 的方案，是否选择 $[x', y']$ 对答案没有影响，总贡献一正一负抵消掉了，相当于钦定不包含 $[x, y]$，即将其删去。最终区间互不包含，满足 $x_i$ 递增且 $y_i$ 递增。

注意是删去较大的区间而不是删去较小的区间，这保证了对于任意区间 $[l, r]$，对所有包含于 $[l, r]$ 的区间做上述操作等价于对所有区间做上述操作后包含于 $[l, r]$ 的区间。

现在考虑一次询问以及所有相关区间 $I_1, I_2, \cdots, I_k$。设 $f_i$ 表示选择 $I_i$ 覆盖 $[x_1, y_i]$ 的区间数为偶数的方案数减去区间数为奇数的方案数，则 $f_i = -\sum_{j = 1} ^ {i - 1} f_j [x_i\leq y_j]$。

分析：

$f_1$ 显然为 $-1$。

如果 $y_1 < x_2$，则 $f_2 = 0$，且根据端点单调的性质，接下来所有 $f$ 也等于 $0$。否则 $f_2 = 1$。

接下来，对于所有 $x_i\leq y_1$ 的 $i$，其 $f_i$ 等于 $\sum_{j = 1} ^ {i - 1} f_j = 0$，可以跳到第一个使得 $y_1 < x_i$ 的 $i$。如果 $y_2 < x_i$，说明 $f_i = 0$，且接下来所有 $f$ 也等于 $0$，否则 $f_i = -f_2 = -1$。进入了形式相同但规模更小的子问题。

我们尝试描述上述过程的核心思想，即维护 $(u, v) = (1, 2)$，每次交替令 $u\gets p_u$ 和 $v \gets p_v$，其中 $p_i$ 表示使得 $y_i < x_j$ 的最小的 $j$。任何时刻，若 $v\gets p_v$ 后出现 $y_u < x_v$，或 $u\gets p_u$ 后 $y_v < x_u$ 则无解。不妨设使得第一次出现无解的情况是 $y_v < x_u$，则接下来令 $v\gets p_v$ 将使得 $v = u$，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4tpfzymu.png)

不断执行操作，直到 $x_{p_u} > r$ 且 $x_{p_v} > r$。若 $u = v$，说明出现了断开的情况，无解。否则，若 $x_u < r$ 且 $x_v < r$，说明 $f_k = 0$。否则若 $x_u = r$ 则 $f_k = -1$，因为 $u$ 维护了过程中所有 $f_u = -1$ 的位置。同理，若 $x_v = r$ 则 $f_k = 1$。

加入多组询问，$i\to p_i$ 连边后树上倍增即可。

注意：

- 若不存在 $i$ 使得 $x_i = l$，无解。
- 若不存在 $i$ 使得 $y_i = r$，无解。
- 注意特判初始情况，$y_u = r$ 时答案为 $-1$，$y_u > r$ 时答案为 $0$。

时间复杂度 $\mathcal{O}((n + q)\log n)$。[代码](https://codeforces.com/contest/1774/submission/185763315)。

---

## 作者：Bring (赞：6)

### [For a better experience please click here.](https://www.cnblogs.com/BrianPeng/p/17006947.html)

Solved the first five questions with brute force. Still 19 points away from reclaiming purple. Hang on!

# Solution: CF1774G Segment Covering

Link to the question: [CF](https://codeforces.com/problemset/problem/1774/G) [Luogu](https://www.luogu.com.cn/problem/CF1774G)

### Preface

A brilliant and tricky question (tricky because modding $998244353$ is 'almost' of no use). This blog is an explanation and extension of the official tutorial.

Notations: We use $[l_i,r_i]$ to denote an interval with index $i$ (or interval $i$) and $[x,y]$ to denote a query interval.

### Analysis

The question asks about the difference between the number of ways of covering $[x,y]$ with even and odd numbers of existing intervals. As the question does not ask the numbers of ways with even and odd intervals separately, but the difference between them, we need to take advantage of it.

#### Property 1

Suppose an interval contains another interval, i.e. there exist indices $i,j$ such that $l_i\leqslant l_j\leqslant r_j\leqslant r_i,$ or $[l_j,r_j]\subseteq [l_i,r_i].$ If we use the interval $[l_i,r_i]$ but not $[l_j,r_j]$ in a covering, then we can always pair it with another covering that is the same as the previous one except that $[l_j,r_j]$ is also used. The two coverings differ by $[l_j,r_j]$ only, so one contributes to $f$ and another contributes to $g.$ In the end, they contribute zero to the final answer.

Therefore, to have a non-zero contribution to the answer, we cannot use the interval $[l_i,r_i].$ In other words, we can remove $[l_i,r_i]$ from our list of intervals.

After removing all 'useless' intervals, if we sort the remaining intervals by their left boundaries, their right boundaries will also be sorted.


#### Property 2

Suppose $[x,y]$ is the query interval and the intervals $[l_i,r_i]$ are trimmed (by Property 1) and sorted in a list. Then, the intervals that might have a chance to be chosen are those contained by $[x,y]$ and are consecutive in the sorted list. We let them be $\{[l_i,r_i],[l_{i+1},r_{i+1}],\cdots,[l_{j},r_{j}]\}.$

If the list is empty or $l_i\ne x$ or $r_i<l_{i+1}$ or $r_j\ne y,$ the answer is obviously $0.$ So, we suppose $l_i=x,r_i\geqslant l_{i+1},r_j=y,$ and we know that the interval $[l_i,r_i]$ must be chosen.

We consider the following case:

![](https://cdn.luogu.com.cn/upload/image_hosting/d4vv0x6m.png)

Here, the black line represents the query interval $[x,y],$ and the colored lines are intervals in our list. We know that the interval $i$ ($[l_i,r_i]$) must be chosen, so we color it green.

Next, we see that in the picture, $l_{i+2}\leqslant r_i,$ which means that the interval $i+2$ intersects with the interval $i.$ Thus, if we choose the interval $i+2$ in a covering, then choosing $i+1$ or not does not affect the covering. Similar to Property 1, this means that if we choose $i+2,$ the net contribution to the answer is $0.$ Therefore, the interval $i+2$ is useless in this case, and we color it red.

In a similar argument, all the intervals that intersect with the interval $i$ (except the interval $i+1$) are useless. We let the interval $k$ be the left-most interval that does not intersect with the interval $i.$

As we need to cover $[x,y]$ and the only interval that intersects with $i$ is $i+1,$ then we must choose $i+1,$ so we color it green. Now, the interval $i+1$ is a must-be-chosen interval and $k$ is a possible interval next to it. In the picture, we may see that $l_{k+1}\leqslant r_{i+1},$ so the interval $k+1$ is useless (Why?). In fact, every interval with an index greater than $k$ that intersects with the interval $i+1$ is useless, and then $k$ must be chosen, being the only 'non-useless' interval that intersects with $i+1$.

To conclude, **a must-be-chosen interval and a possible interval next to it make all the other intervals intersecting with the first interval useless, and the second interval must-be-chosen.**

From the above statement, we may show inductively that **every interval is either must-be-chosen or useless, so there is essentially at most one 'useful' covering.** If an even number of intervals are used, the answer is $1.$ If odd, then $-1.$ If the must-be-chosen intervals cannot cover $[x,y]$, then the answer is $0.$ The covering is like the following:

![](https://cdn.luogu.com.cn/upload/image_hosting/b47sn311.png)

Note that we split the intervals into two "layers," and for every interval, only the intervals next to it intersect with it. In this picture, the interval $j$ is on the same layer as $i+1,$ so there are an even number of intervals and the answer is $1.$ If $j$ is on the layer of $i$, the answer is $-1.$

#### A Hidden Tree Structure

Property 2 already gives us a method of finding the useful covering for a query $[x,y],$ which is recursively seeking the must-be-chosen intervals and deleting useless intervals until an interval has its right boundary equal to $y$ is chosen. However, as there are many queries, optimization is needed.

Let's look closer at the picture above. The intervals are divided into two layers, one starting with $i$ and another starting with $i+1.$ Also, for every interval, if it is not the end, its next interval on the same layer is always **the first interval on its right that is disjoint with it.**

Therefore, if we link each interval to the interval on its right that is disjoint with it, a **tree** is formed. For simplicity, we link all the intervals that have no "parents" to a virtual root node.

Here is our final "theorem" of the question:

$\text{Theorem. }$There is a scheme of choosing the interval if and only if the interval $j$ is the ancestor of exactly one of $i$ and $i+1.$ If it is the ancestor of $i,$ then the answer is $-1.$ If $i+1,$ then the answer is $1.$

p.s. Please prove this theorem independently. There are two points worth noting. Firstly, if $j$ is the common ancestor of both $i$ and $i+1,$ then there is one point where intervals on both layers are disjoint with $j,$ so $[x,y]$ cannot be fully covered. Secondly, the official tutorial calculates the answer $\pm 1$ by counting the number of intervals used, but actually, we only need to check whose ancestor $j$ is.

### Implementation

#### A trick of STL `set`: removing 'useless' intervals by Property 1

If an input interval contains another, we remove the larger one.

This can be done in multiple ways, we may sort the intervals in some manner and label the useless intervals, which is the method in the official tutorial.

Here is another way: we may maintain a `set` of intervals such that no interval is contained by another, through a specifically designed $<$ relation.

We define that the intervals $[l_1,r_1]<[l_2,r_2]$ if $l_1<l_2$ **and** $r_1<r_2.$ We may see that if an interval contains another, they are considered 'equal' by `set` (because neither $<$ nor $>$).

The algorithm is: When we try to add $[l,r]$ into the `set`, we use `find()` method to look for the interval that is 'equal' to $[l,r].$ If it does not exist, then we simply insert $[l,r]$ into the `set`.

Suppose it is $[a,b].$ If $[l,r]$ contains $[a,b],$ then we discard $[l,r].$

Lastly, if $[a,b]$ contains $[l,r],$ then we remove $[a,b]$ from the `set` **and check if there are other intervals in the `set` that contains $[l,r].$** After removing all of them, we insert $[l,r].$

#### `upper_bound`: looking for 'parents'

We may use `vector` to store and index the ordered intervals remaining in the `set`. Now, for an interval $[l_i,r_i]$, its 'parent' is the first interval to its right that is disjoint to it. We may use bisection or two-pointers to achieve this. Here is another way:

We may still use STL and the $<$ relation we have designed. For the interval $[l_i,r_i],$ its 'parent' $[l_k,r_k]$ is exactly the first interval 'greater than' $[r_i,r_i],$ which may be found by `upper_bound`.

Similarly, we may use `upper_bound` to find the left-most interval for the query $[x,y],$ which is the first interval 'greater than' $[x-1,x-1].$

#### Binary lifting: ancestor?

Note that we need to check whether the interval $j$ (the unique interval $[l_j,r_j]$ such that $r_j=y$) exists and is the ancestor of $i$ or $i+1.$ This can be done by binary lifting, the most commonly used method for LCA. Starting from node $i$ (or $i+1$), we 'lift' it to the last interval with its right boundary $\leqslant y.$ Then, if its right boundary $=y,$ then it is interval $j$ and is an ancestor of $i$ (or $i+1$).

### Code

Here is a sample code integrating all the ideas above. The binary-lifting array is `f` and the `vector` `v` stores all `non-useless` intervals in order, with indices from $0$ to `v.size()-1`. We let `v.size()` be the index of the virtual root node.

We use `li` to denote the first interval with its left boundary $\geqslant x,$ which is the interval $i$ in our analysis section. Note that there are many special cases, please read the code and make sure you understand all of the special cases. 

```cpp
//This program is written by Brian Peng.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Rd(a) (a=rd())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int rd(){
	int x;char c(getchar());bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	c^'-'?(k=1,x=c&15):k=x=0;
	while(isdigit(Gc(c)))x=x*10+(c&15);
	return k?x:-x;
}
void wr(int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(int i(a);i<(b);++i)
#define Frn1(i,a,b) for(int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define N (200010)
int m,q,x,y,f[N][20];
struct T{int l,r;
	bool operator<(T b)const{return l<b.l&&r<b.r;}
};//The structure of intervals, with < relation defined.
set<T>st;
signed main(){
	Rd(m),Rd(q);
	while(m--){
		Rd(x),Rd(y);
		auto it(st.find({x,y}));//Find the interval in the set that contains
        //or is contained by the input [x,y]
		if(it==st.end())st.insert({x,y});
		else if(x<=it->l&&it->r<=y)continue;//[x,y] contains a smaller interval
		else{
			st.erase(it);//[x,y] is contained by a larger interval
			while((it=st.find({x,y}))!=st.end())st.erase(it);
            //Remove all the intervals that contain it
			st.insert({x,y});
		}
	}
	vector<T>v(st.begin(),st.end());
	Frn0(i,0,v.size())
        *f[i]=upper_bound(v.begin()+i+1,v.end(),T({v[i].r,v[i].r}))-v.begin();
        //Use upper_bound and < relation to find the parent node
	int lg(log2(v.size()));
	*f[v.size()]=v.size();
	Frn1(j,1,lg)Frn1(i,0,v.size())f[i][j]=f[f[i][j-1]][j-1];//binary lifting
	while(q--){
		Rd(x),Rd(y);
		int li(upper_bound(v.begin(),v.end(),T({x-1,x-1}))-v.begin());
        //li is the index of the first interval with left boundary >= x
		if(li==v.size()||v[li].l!=x||v[li].r>y){wr(0),Pe;continue;}
        //Special cases: li not existing, li not covering x, li exceeding y
		if(v[li].r==y){wr(998244352),Pe;continue;}
        //Special case: li is just [x,y]
		if(li+1==v.size()||v[li+1].r>y||v[li+1].l>v[li].r){wr(0),Pe;continue;}
        //Special cases concerning li+1
		int u(li),u2(li+1);
		Frn_(i,lg,0)if(f[u][i]<v.size()&&v[f[u][i]].r<=y)u=f[u][i];
		Frn_(i,lg,0)if(f[u2][i]<v.size()&&v[f[u2][i]].r<=y)u2=f[u2][i];
        //Binary lifting li and li+1 to the last intervals with right boundary <= y
		if(u==u2||v[u].r!=y&&v[u2].r!=y)wr(0),Pe;
        //Common ancestor or both not reaching y
		else if(v[u].r==y)wr(998244352),Pe;//Ancestor of li
		else wr(1),Pe;//Ancestor of li+1.
	}
	exit(0);
}

```

Time Complexity: $O((m+q)\log m)$

Memory Complexity: $O(m\log m)$

### Extension

STL is a very powerful tool.

In this question, we use STL `set` to maintain a set of intervals that one does not contain another, but a specifically designed $<$ relation.

By designing different $<$ relations, we may maintain a `set` of intervals with different properties conveniently. For example, my blog

[Solution: CF731D 80-th Level Archeology -- Letter, Interval, and Reverse Thinking](https://www.cnblogs.com/BrianPeng/p/16928706.html)

solves another CF problem by maintaining a `set` of mutually disjoint intervals by defining another $<$ relation between intervals.

**Thanks for reading! See you next round!**


---

## 作者：Kubic (赞：6)

验题人报道，一个另类做法。

先考虑 $l=1,r=n$ 怎么做。

考虑容斥，钦定一部分点不被任何线段覆盖。一种钦定方案的贡献为所有未被钦定的点组成的极长连续段的贡献的乘积。

对于一个未被钦定的点组成的极长连续段，设 $k$ 为这个连续段包含的线段个数。

显然如果 $k>0$，那么这个连续段的贡献为 $0$，因为奇偶抵消了。所以我们要求 $k=0$。

设 $p_i$ 表示最大的数满足 $[p_i,i]$ 中至少包含一条线段，如果不存在则为 $-\infty$，$dp_i$ 表示 $[1,i]$ 的答案。

有转移式 $dp_i=-\sum\limits_{j=p_i}^i dp_{j-1}$。

设 $s_i=\sum\limits_{j=0}^i dp_j$。

那么 $s_i-s_{i-1}=-(s_{i-1}-s_{p_i-2})$，$s_i=s_{p_i-2}$。

答案即为 $dp_n=s_n-s_{n-1}$。

考虑如何计算 $s_n$。对于 $s_{n-1}$ 可以类似地处理。

我们从 $i$ 向 $p_i-2$ 连一条边，从 $n$ 开始不断往前跳直到 $<1$。

设跳到的位置为 $x$。显然 $x$ 只有可能是 $0,-1,-\infty$ 三者之一。

分析可得，只有 $x=-1$ 时 $s_n=0$。否则 $s_n=1$。

多组询问只需要用倍增优化往前跳的过程即可。时间复杂度 $O(n\log n)$。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define MOD 998244353
int n,m,ds[N],ps[N],fa[N][18];struct Node {int l,r;}a[N];
int qId(int x) {return lower_bound(ds+1,ds+ds[0]+1,x)-ds;}
int qry(int l,int r)
{
	int t=qId(r);
	for(int i=17;i>=0;--i) if(ps[fa[t][i]]>=l) t=fa[t][i];
	if(ps[t]>=l) t=fa[t][0];return ps[t]!=l-2;
}
int main()
{
	scanf("%d %d",&n,&m);ds[++ds[0]]=1e9;
	for(int i=1,l,r;i<=n;++i)
	{
		scanf("%d %d",&l,&r);++l;
		ds[++ds[0]]=r-1;a[i]=(Node) {l,r};
	}sort(ds+1,ds+ds[0]+1);ds[0]=unique(ds+1,ds+ds[0]+1)-ds-1;
	for(int i=1;i<=ds[0];++i) ps[i]=-1e9;
	for(int i=1,t;i<=n;++i) t=qId(a[i].r),ps[t]=max(ps[t],a[i].l-2);
	for(int i=1;i<=ds[0];++i)
	{
		if(i>1) ps[i]=max(ps[i],ps[i-1]);fa[i][0]=qId(ps[i]);
		for(int j=1;j<=17;++j) fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	for(int i=1,l,r,t;i<=m;++i)
	{
		scanf("%d %d",&l,&r);++l;t=qry(l,r)-qry(l,r-1);
		if(t<0) t+=MOD;printf("%d\n",t);
	}return 0;
}
```

---

## 作者：ღꦿ࿐ (赞：3)

首先直接求 $f,g$ 是不可做的。 考虑这个奇偶差的性质。

若方案唯一，则答案为 1 或 -1。

若方案不唯一：

若存在着一些线段之间有着包含关系，则选择了大线段，是否选择被包含线段都是合法的，这也对应着不同的奇偶性，也就是说着这种情况对奇偶差是没有贡献的，于是我们删掉所有包含其它线段的线段。

则现在的线段排序后的 $r$ 是随着 $l$ 增加而增加的。

还有哪些线段在这种情况下对奇偶差是没有贡献的？ 

![](https://cdn.luogu.com.cn/upload/image_hosting/bk5meblj.png)

像这样，则有唯一的选择方法使得并集合法，答案是 1 或 -1 。

若存在这种下图中红线这样的线段：

![](https://cdn.luogu.com.cn/upload/image_hosting/7poh3o7m.png)

即被相邻两条线段的并包含。

则选蓝色线段后无论是否选取红色线段，都合法，对奇偶差无贡献。

也就是说最终那些有贡献的线段大概是长这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/cu1kxgsg.png)

第一条线段和第三条交集为空，第二条和第四条交集为空 …… 这样下去。

于是现在就有了 $O(nq)$ 做法： 

先删去所有包含关系的线段，再把所有 $[l,r]$ 中的线段拿出来，删去所有上图中红色线段那样的线段，然后判断剩下的线段是否形成一种覆盖以及奇偶性。

考虑优化 ： 我们并不需要考虑“删去”的线段，我们只需要考虑那些保留的线段，而不是哪些线段被删去了。

对于每条线段，我们要找的其实是后面第一条与它不交的线段，从上图可以清晰看出。 

那么我们找到第一条，第二条线段，并分别往后一直找下去就可以找到这些有用的线段，若出现了没有被覆盖的点，则第一条和第二条线段会跳到同一条线段上。

找下一条线段的过程可以使用倍增优化，时间复杂度 $O(q\log n)$。

下面是代码实现，有以下细节需要判断：

没有 $l$ 开头的线段。

没有 $r$ 结尾的线段。

第二条线段和第一条线段不交。

第二条线段超出了 $r$。

[代码  ](https://codeforces.com/contest/1774/submission/186659952)(实现较为复杂，在 CF 最优解第一页。)

---

## 作者：Yansuan_HCl (赞：2)

题解，但是无任何倍增。

有一个朴素的想法是对于任意一组选出的线段，如果这组有线段存在包含关系，或未选出的线段包含选出的线段，或选出的线段包含未选出的线段，则贡献为 $0$。但是这是一眼错的：

```
3 1

1 4
2 5
3 5

1 5
```

答案实际上是 $1$，这时候 `(1,4)(2,5)(3,5)` 这个方案被算重了：`(1,4)(2,5)` 和 `(1,4)(3,5)` 都会因为 `(1,4)(2,5)(3,5)` 存在而贡献变成 $0$。

考虑怎么修一下，我们希望对每种选的方案找出一个**关键线段组**，使这个线段组能覆盖 $[l,r]$ 同时是**唯一**的。考虑以下算法：

- 从 $l$ 到 $r$ 扫描每个点 $i$ ，维护当前已经覆盖满的区间 $[l,j]$。
- 对于所有以 $i$ 为右端点的线段 $[j,i]$：
  - 若 $j\le l$，将 $[j,i]$ 标记为关键的；
  - 否则标记为非关键的。
- 遍历完成后，若有至少一个关键线段，则 $j\gets i$。

此时每种选的方案唯一对应一个关键线段组。若将选的某个非关键线段去掉，关键线段组仍维持不变。

- 若存在某个方案有非关键线段，则这个方案对应的关键线段组贡献为 $0$。

因此就可以 DP 关键线段。考虑暴力，已知一个确定的 $l$，$f_i$ 表示覆盖满 $[l,i]$ 的答案。转移是 $f_i=-\sum f_j$，要求不存在被 $[j+1, i]$ 包含的线段，同时选 $[x,i], i\le j$ 的线段为关键。一个 $i$ 只有一个 $x$ 好办，这个线段必选；否则 $j$ 会受到最大的 $x$ 的限制，但是不一定必选 $[x,i]$，所有以 $i$ 为右端点的线段都可以选，只不能选空集；所以选法有 $2^{cnt}-1$ 种，正负消完贡献保持不变，因此只需当成只有一个最大的 $x$。要求就是 $j\ge x$。

写成前缀和优化，形如 $f_i=-(s_{i-1}-s_{x-1})$，此时 $s_i=s_{i-1}+f_i=s_{x-1}$。这时候发现 $s$ 的取值只有 $0,1$，因而答案只有 $0,1,-1$。

扫描 $i$，用数据结构维护每个 $l$ 对应的 $s_{l,i}$，要支持把一段区间换成之前某个版本的，主席树即可。时空复杂度 $O(n\log n)$。

---

## 作者：UKE_Automation (赞：1)

### CF1774G Segment Covering

[$\text{Link}$](https://codeforces.com/problemset/problem/1774/G)

对于线段问题，有一个经典套路是我们只保留相交或包含中的一种关系，这样前者可以保证左右端点均递增，后者可以构造出树形结构等。对于这道题，显然保留相交关系比较合理，那么考虑如果去掉包含关系。

此时需要用到题目中给出的式子 $f(l,r)-g(l,r)$，考虑讨论贡献，对于两条线段 $s_1,s_2$，如果 $s_1$ 包含 $s_2$，那么若我们选了 $s_1$，则 $s_2$ 选与不选均可，这样的话它一定会分别贡献给 $f,g$ 同样多的方案，贡献就是 $0$。所以我们完全不必考虑选 $s_1$，把 $s_1$ 删掉即可。如此我们保留下来的就只有相交关系了。

进一步的套用这个分析过程会发现，对于三条线段 $s_1,s_2,s_3$，如果满足 $l_1<l_2<l_3<r_1<r_2<r_3$，那么若我们选了 $s_3$，则 $s_2$ 选与不选均可，同理我们可以删除 $s_2$。这样的话我们就不可能有一条线段被两条线段并覆盖了，也就是说线段会形成两排互不相交的线段。

现在剩下的线段就是除了抵消的贡献外多出来的贡献，那么我们只需要算出在这个区间内线段的个数即可。考虑倍增，我们令 $nxt_i$ 表示 $i$ 之后第一条与 $i$ 不相交的线段，那么我们找到 $l$ 对应的线段 $p$，从 $p,p+1$ 分别开始倍增，通过跳的步数计算最后答案即可。注意如果最后两个点跳到了同一个位置，说明中间一定有地方是断开的，那么答案还是 $0$。

这样做的复杂度是 $O(n\log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
const int Mod = 998244353;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b) {int res = 1; for(; b; a = 1ll * a * a % Mod, b >>= 1) if(b & 1) res = 1ll * res * a % Mod; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, m, q;
struct Seg {
	int l, r;
}s[Maxn];
int nxt[Maxn][19];

int solve(int x, int y) {
	int p = lower_bound(s + 1, s + m + 1, (Seg){x, 0}, [](Seg x, Seg y){return y.l > x.l;}) - s;
	int q = lower_bound(s + 1, s + m + 1, (Seg){0, y}, [](Seg x, Seg y){return y.r > x.r;}) - s;
	if(s[p].l != x || s[q].r != y) return 0;
	if(p == q) return Mod - 1;
	int p1 = p, p2 = p + 1, stp = 2;
	for(int i = 18; i >= 0; i--) if(nxt[p1][i] && nxt[p1][i] <= q) p1 = nxt[p1][i], stp += (1 << i);
	for(int i = 18; i >= 0; i--) if(nxt[p2][i] && nxt[p2][i] <= q) p2 = nxt[p2][i], stp += (1 << i);
	if(p1 != q && p2 != q) return 0;
	if(p1 == p2) return 0;
	if(stp & 1) return Mod - 1;
	else return 1;
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n), read(q);
	for(int i = 1; i <= n; i++) {
		read(s[i].l), read(s[i].r);
	}
	sort(s + 1, s + n + 1, [](Seg x, Seg y){return x.r == y.r ? x.l > y.l : x.r < y.r;});
	int mx = 0;
	for(int i = 1; i <= n; i++) {
		if(mx < s[i].l) {
			mx = max(mx, s[i].l); s[++m] = s[i];
		}
	}
	for(int i = 1; i <= m; i++) {
		nxt[i][0] = upper_bound(s + i + 1, s + m + 1, s[i], [](Seg x, Seg y){return y.l > x.r;}) - s;
	}
	for(int i = m; i >= 1; i--) for(int j = 1; j <= 18; j++) nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
	while(q--) {
		int x, y;
		read(x), read(y);
		write(solve(x, y));
	}
    Usd();
	return 0;
}

```

---

## 作者：xcyyyyyy (赞：1)

### [CF1774G] Segment Covering  

先考虑单次询问。

奇偶型问题，考虑到如果不要 $[l,r]$ 的区间都可以覆盖整个区间，那么要了同样可以覆盖，并且奇偶相反直接抵消了。所以我们只统计每个区间是“必要的”的情况。

考虑容斥哪些段没有覆盖到，对于剩下的段可选可不选。这些段一旦包含一个区间，那么这个区间就可选可不选，由于前面的分析，此时的数量为 $0$。（从这里可以看出，我们的容斥是极具目标性的）

那么我们就可以考虑 dp 了，设 $p_i$ 表示以 $i$ 为右端点的所有区间中不包含任何一个给定区间的最小的左端点。每一次转移就钦定 $[j-1,j]$ 这一段不能包含，转移为：$f_i=-\sum \limits_{j=p_i}^{i}f_{j-1}$，同时钦定 $[-1,0]$ 是无意义的，但是每一个状态钦定了这个，故给所有状态乘上 $-1$，即令 $f_{0}=-1$。

考虑写成前缀和的形式：$s_i-s_{i-1}=-(s_{i-1}-s_{p_i-2})$，即 $s_i=s_{p_i-2}$，当然这里的 $s_{p_i-2}$ 可能比 $0$ 小，此时等于 $0$。

考虑处理多次询问，连接 $i \rightarrow p_i-2$ ，若我们从 $r_i $ 能跳到 $l-1$，则其 $s_{r_i}$ 为 $-1$，否则为 $0$，最后要求求解 $s_{r_i}-s_{r_i-1}$，我们分别计算 $r_i$ 和 $r_i-1$ 即可。若能建出树来，直接倍增跳即可。

但是这道题的值域很大。幸运的是，$p_i$ 一定对应了某个区间的 $l+1$，我们树上需要的点只有询问的 $r_i,r_i-1$ 原区间的 $l_i-1$，扫描线求解父亲即可。

（我 tm 离散化错了调了四十分钟）

---

## 作者：lalaouye (赞：0)

是个美难题。

首先这种偶数减计数看着就跟容斥很有关系，总之这种题肯定不太能是分开算。

而这道题一共有两种方法都很有教育意义，一种是容斥，一种是利用一些方法去抵消贡献。

先讲容斥吧。显然我们容斥就是钦定哪些位置一定不选，然后每个区间的贡献就是 $-1$，一种方案的贡献就是它们的积。不难发现，如果对于一种钦定方案存在一个区间可以选，那选与不选的贡献**正负抵消**，我们就只用统计没有满足条件的区间的钦定方案数即可，我们可以设计 dp，设 $f(i)$ 表示前缀 $[1,i]$ 的答案。我们对于一个右端点 $r$，可以求出最大的 $l$ 使得区间中包含一个给定区间，设其为 $p_r$，那么对于 $f(r)$ 我们有转移方程 $f(r)=-\sum_{i=p_r}^r f(i-1)$，我们不妨前缀和，设 $g(i)=\sum_{j=0}^i f(j)$，则 $g(i)-g(i-1)=g(p_i-2)-g(i-1)$，我们惊奇的发现 $g(i)=g(p_i-2)$。

这样对于多组询问我们就可以快速求 $g(i)$ 的值了，$f(i)$ 就是 $g(i)-g(i-1)$。我们不妨将 $i$ 向 $p_i-2$ 连一条边，然后倍增优化去跳，到终点讨论一下答案即可。

通过感受我们可以发现抛开套路不谈最精彩的一步是我们能够发现 $g(i)=g(p_i-2)$，其本质是因为负数的转移系数可以使得很多项互相抵消所制。

接下来再讲讲这题的主流做法，我的代码写的也是这个。

就是考虑正负抵消，首先我们发现这是要求并起来结果为 $[l,r]$，所以我们可以发现对于一个给定区间如果它包含了某个其它的给定区间，它是无意义的，因为只要选了它就会被正负抵消。

然后我们发现最后的区间序列是关于左右端点分别单调的，这很漂亮，但是仍然不够。

我们从头开始考虑，首先第一个区间必选，第二个区间我们不好说，但是我们发现如果第一个区间和第三个区间的并包含了第二个区间，那第三个区间也是无效的！因为第一个必选，第二个则负责抵消。我们将其变得更加形式化，对于 $l_3\le r_1$ 的区间我们可以直接删，我们把所有该删的删完，接下来我们发现第二个区间变成了必选区间，那么我们再把第二个区间作为第一个区间去删，最后我们发现剩下的所有区间都是必选的，那么答案就只需要关心区间总数的奇偶性了。

现在考虑做这道题，我们考虑对于区间 $i$ 往最小的 $j$ 满足 $r_i<l_j$ 连边，查询就是找到第一个区间和第二个区间，然后往后倍增知道卡到 $r$ 位置，我们来分析答案，如果两边倍增完右端点都小于 $r$ 或者倍增完的区间相同就表示无解，对于后者的意义就是中间存在间隙覆盖不到。否则就是根据奇偶性输出答案了。

我们发现这个做法需要我们要么注意力在线，能够感受到必选和包含带来的伟大力量。要么就抓住关键，利用包含关系和式子的特殊性去正负抵消，最后只需要一个倍增的 trick 即可，看到这种往后跳的问题我们可以考虑倍增。

不过怎么想感觉都是容斥是更自然好想的。希望大家能通过我的题解学到东西，如果觉得写得好可以点个赞！

[代码。](https://codeforces.com/contest/1774/submission/333477236)

---

## 作者：takanashi_mifuru (赞：0)

首先有一个性质就是，如果区间 A 包含区间 B，那么可以直接扔掉区间 A，因为如果有一个方案中有区间 A，那么有没有区间 B 做出的奇偶差异可以直接抵掉。

然后考虑做一个 dp，设 $dp_i$ 表示区间 $[lt,i]$ 已经被填满，此时的贡献是多少，那么转移方程是经典的，假设有区间 $[L,i]$ 则 $dp_i$ 可以从 $[L,i)$ 中的每一个 dp 值处转移过来。

容易发现实现这个东西可以用前缀和，于是我们干脆转而维护 dp 的前缀和数组 $pre_i$，则上述式子写出来就是 $pre_i=pre_{i-1}-(pre_{i-1}-pre_{L-1})=pre_{L-1}$，如果询问区间 $[lt,rt]$，则边界条件为 $pre_{lt-1}=0,pre_{lt}=1$。

那么考虑一个点会被赋值为 $0$ 当且仅当他能够一步跳到 $lt-1$，否则他就会被赋值为 $1$，考虑倍增往前跳，跳到 $lt-1$ 的前一步，如果下一步是通过转移直接走到 $lt-1$，那么就会被赋值为 $0$，否则会被赋值为 $1$。

然后考虑这样能求出前缀和，但是我们要求单点，可以直接拿前缀和去减。

```cpp
#include<bits/extc++.h>
const int P=998244353;
using namespace std;
int n,q;
int m;
struct node{
   int lt,rt;
   bool friend operator < (const node &a,const node &b){
      return a.rt<b.rt||a.rt==b.rt&&a.lt>b.lt;
   }
}A[200005];
int nxt[400005][20];
int val[400005],tot,pos;
bool vis[400005];
__gnu_pbds::gp_hash_table<int,int> mp;
bool check(int st,int ed){
   int lt=0,rt=pos+1;
   while(lt+1<rt){
      int mid=lt+rt>>1;
      if(val[mid]<=st)lt=mid;
      else rt=mid;
   }
   st=lt;
   for(int j=19;j>=0;j--){
      if(nxt[st][j]>ed)st=nxt[st][j];
   }
   if(nxt[st][0] xor ed){
      return true;
   }
   if(vis[st]){
      return false;
   }
   return true;
   return !(st==ed);
}
signed main(){
   scanf("%d%d",&n,&q);
   for(int i=1;i<=n;i++){
      scanf("%d%d",&A[i].lt,&A[i].rt);
   }
   sort(A+1,A+1+n);
   for(int i=1;i<=n;i++){
      if(A[i].lt>A[m].lt){
         A[++m]=A[i];
      }
   }
   for(int i=1;i<=m;i++){
      val[++tot]=A[i].lt-1;
      val[++tot]=A[i].rt;
   }
   val[0]=-1;
   sort(val+1,val+1+tot);
   for(int i=1;i<=tot;i++){
      if(val[i] xor val[i-1]){
         val[++pos]=val[i];
      }
   }
   for(int i=1;i<=pos;i++)mp[val[i]]=i;
   for(int i=1;i<=pos;i++){
      nxt[i][0]=i-1;
   }
   for(int i=1;i<=m;i++){
      nxt[mp[A[i].rt]][0]=mp[A[i].lt-1];
      vis[mp[A[i].rt]]=true;
   }
   for(int j=1;j<=19;j++){
      for(int i=1;i<=pos+1;i++){
         nxt[i][j]=nxt[nxt[i][j-1]][j-1];
      }
   }
   while(q--){
      int lt,rt;
      scanf("%d%d",&lt,&rt);
      int st=mp[lt-1];
      if(!st){
         puts("0");
         continue; 
      }
      printf("%d\n",(check(rt,st)-check(rt-1,st)+P)%P);
   }
   return 0;
}
```

---

## 作者：SegTree (赞：0)

首先如果两个区间包含，那么可以把大区间删除。选大区间会导致给 $f$ 和 $g$ 产生相等的贡献，因为求 $f-g$ 所以直接抵消。

![](https://cdn.luogu.com.cn/upload/image_hosting/24r8nid8.png)
我们假设强制选第 $1$ 条线段。

如图所示的三条线段中，若强制选第 $3$ 条，则依据上面没有贡献，所以可以删除第 $3$ 条线段。同理若有 $l_i\le r_1$，则线段 $i$ 可被删去。因此对答案有贡献的线段一定满足第 $1,3,\cdots$ 条区间不交且第 $2,4,\cdots$ 条区间也不交，记当前有 $k$ 条线段，方案显然只有都选，则答案为 $(-1)^k$。使用倍增优化即可。

需要特判无解：没有 $l$ 开头的线段，没有 $r$ 结尾的线段，线段中间断开（$r_i<l_{i+1}$）。

代码：<https://codeforces.com/contest/1774/submission/262129927>。

---

## 作者：tribool4_in (赞：0)

线段并问题加上答案为差值，考虑能否通过抵消来删除一些线段。于是考虑对于两个成包含关系的线段，若外侧线段被选中，内侧线段显然可选可不选，对奇、偶的贡献相同。因此包含其他线段的线段可以删除。

删除这些线段后排序。此时，排序后线段的 $l_i$ 和 $r_i$ 都严格单调递增了，但是这种情况下线段之间的相交状态还有很多种可能。考虑对于连续的三个线段 $A,B,C$，若 $A$ 与 $C$ 有交，容易发现此时 $A$ 与 $C$ 的并将 $B$ 完全包含。因此**若 $A$ 被选中**，$C$ 可以无需考虑（被选中则抵消）。

此时线段的状态已经很清新了，最终有贡献的方案中，选出的线段之间相交的状态必然形如链状，直接暴力做可以实现 $O(qn)$。

考虑如何优化。对于询问 $[L,R]$，考虑描述这个跳的过程，相当于首先找出 $u$ 满足 $l_u=L$，以及其后继 $v$（显然要满足两者有交）。定义某个线段 $u$ 的一次跳跃为找出 $r_u<l_i$ 的最小 $i$，于是相当于 $u,v$ 分别跳跃直到 $\max(r_u,r_v)=R$，且可以发现若 $u=v$ 则相当于中间存在一个位置出现断裂（即无区间覆盖）无解。

发现这个跳跃的过程可以倍增优化，于是做完了。时间复杂度 $O((n+q)\log n)$。注意有若干特判。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, V = 1e9 + 10, mod = 998244353;
int n, q;
struct node {
    int x, y, id;
    bool operator<(const node &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
};
pair<int, int> p[N];
vector<node> ls;
int f[N][20];
pair<int, int> jump(int u, int lim) {
    int cnt = 0;
    for (int i = 19; i >= 0; i--) {
        if (p[f[u][i]].second <= lim) u = f[u][i], cnt += (1 << i);
    }
    return {u, cnt};
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> p[i].first >> p[i].second;
    sort(p + 1, p + n + 1, [](pair<int, int> a, pair<int, int> b) { return a.first < b.first || (a.first == b.first && a.second > b.second); });
    for (int i = 1; i <= n; i++) {
        while (!ls.empty() && ls.back().y >= p[i].second) {
            ls.pop_back();
        }
        ls.push_back((node){p[i].first, p[i].second, i});
    }
    ls.push_back((node){V, V, n + 1});
    p[n + 1] = {V, V};
    for (int i = 0; i < ls.size(); i++) {
        int u = ls[i].id;
        auto it = lower_bound(ls.begin(), ls.end(), (node){ls[i].y + 1, -V, 0});
        if (it == ls.end()) continue;
        f[u][0] = it->id;
    }
    f[n + 1][0] = n + 1;
    for (int j = 1; j < 20; j++)
        for (int i = 1; i <= n + 1; i++) f[i][j] = f[f[i][j - 1]][j - 1];
    for (int i = 1, l, r; i <= q; i++) {
        cin >> l >> r;
        auto iA = lower_bound(ls.begin(), ls.end(), (node){l, -V, 0});
        if (iA == ls.end() || iA->x != l || iA->y > r) {
            cout << 0 << '\n';
            continue;
        }
        if (iA->y == r) {
            cout << mod - 1 << '\n';
            continue;
        }
        int u = iA->id;
        auto iB = iA + 1;
        if (iB == ls.end() || iB->y > r) {
            cout << 0 << '\n';
            continue;
        }
        int v = iB->id;
        auto [U, cU] = jump(u, r);
        auto [V, cV] = jump(v, r);
        if (U == V) {
            cout << 0 << '\n';
            continue;
        }
        if (p[U].second == r || p[V].second == r) cout << ((cU + cV & 1) ? mod - 1 : 1) << '\n';
        else cout << 0 << '\n';
    }
    return 0;
}
```

---

