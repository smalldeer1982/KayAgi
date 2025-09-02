# Jeff and Removing Periods

## 题目描述

Cosider a sequence, consisting of $ n $ integers: $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ . Jeff can perform the following operation on sequence $ a $ :

- take three integers $ v $ , $ t $ , $ k $ $ (1<=v,t<=n; 0<=k; v+tk<=n) $ , such that $ a_{v} $ = $ a_{v+t} $ , $ a_{v+t} $ = $ a_{v+2t} $ , $ ... $ , $ a_{v+t(k-1)} $ = $ a_{v+tk} $ ;
- remove elements $ a_{v} $ , $ a_{v+t} $ , $ ... $ , $ a_{v+t·k} $ from the sequence $ a $ , the remaining elements should be reindexed $ a_{1},a_{2},...,a_{n-k-1} $ .
- permute in some order the remaining elements of sequence $ a $ .

A beauty of a sequence $ a $ is the minimum number of operations that is needed to delete all elements from sequence $ a $ .

Jeff's written down a sequence of $ m $ integers $ b_{1} $ , $ b_{2} $ , $ ... $ , $ b_{m} $ . Now he wants to ask $ q $ questions. Each question can be described with two integers $ l_{i},r_{i} $ . The answer to the question is the beauty of sequence $ b_{li} $ , $ b_{li}+1 $ , $ ... $ , $ b_{ri} $ . You are given the sequence $ b $ and all questions. Help Jeff, answer all his questions.

## 样例 #1

### 输入

```
5
2 2 1 1 2
5
1 5
1 1
2 2
1 3
2 3
```

### 输出

```
2
1
1
2
2
```

## 样例 #2

### 输入

```
10
2 1 3 3 3 3 1 3 1 1
10
4 8
2 10
1 10
4 4
1 3
2 4
6 7
1 9
2 5
1 1
```

### 输出

```
2
3
3
1
3
2
2
3
2
1
```

# 题解

## 作者：沉石鱼惊旋 (赞：18)

[更好的阅读体验](http://blog.cyx2009.top/archives/250/)

# 闲话

和等差数列过不去了。碰上等差数列就要调 1h。

# 题目翻译

为了方便描述，我们约定数值相同的数为同一颜色的数。

有 $n$ 个数，我们定义一次操作为：选择若干个同颜色数，使得他们在序列中的位置为一个等差数列。删除它们。

操作完之后可以重排整个序列。

有 $q$ 个询问，每次询问给定 $[l,r]$，求至少几次操作能全部删除 $[l,r]$。

询问互不影响。

$1\leq n,q,a_i\leq 10^5$

# 题目思路

与翻译类似，约定数值相同的数为同一颜色的数。

看起来就长了一眼莫队样子。

分析一下，发现操作一次之后，通过重排是可以调整使得之后每次都能删除某一种相同数。

但是，如果我们第一次操作就可以删除某一种相同数，换言之，**如果原区间本身就包含一个颜色使得位置为等差数列**，答案即为区间颜色数。反之，答案为区间颜色数 $+1$。

区间颜色数是很好维护的，我们用一个桶记录每个数出现几次即可。

另外介绍一种小常数写法，我们记录 $pre_i$ 与 $nxt_i$ 表示与 $a_i$ 颜色相同的数上一次或下一次出现在什么位置，这能做到访址连续跑得更快。

```cpp
// while(L>Query[i].L)ANS+=(++h[a[--L]]==1);
// while(R<Query[i].R)ANS+=(++h[a[++R]]==1);	  
// while(L<Query[i].L)ANS-=(--h[a[L++]]==0);
// while(R>Query[i].R)ANS-=(--h[a[R--]]==0);
while(L>Query[i].L)ANS+=(nxt[--L]>R);
while(R<Query[i].R)ANS+=(pre[++R]<L);	  
while(L<Query[i].L)ANS-=(nxt[L++]>R);
while(R>Query[i].R)ANS-=(pre[R--]<L);
```

注释即为正常桶记录写法，非注释即为这种访址连续的写法。

然后我们考虑如何判断『原区间本身就包含一个颜色使得位置为等差数列』，为了莫队方便把信息传递到下个区间，我们改成『维护区间内有多少颜色使得位置为等差数列』。

这个有一个很显然的单次修改查询 $\mathcal O(\log n)$ 的做法为，维护若干 multiset，每次暴力插入删除当前点的贡献，然后判断最大值与最小值是否相等。附一个到此步 TLE on 23 的码：[CF submission 243942020](https://codeforces.com/contest/351/submission/243942020)。

然后考虑优化，我们现在把要维护的问题转化为：

> 有 $n$ 个类别，每次操作在一个类别里加入或删除一个数，每次判断这个类别是否只有 $1$ 种数。

然后，我们考虑一个人类智慧做法：

维护 $3$ 个信息，类别中数的个数 $cnt_i$，类别中数的和 $sum_{0,i}$，类别中数的平方和 $sum_{1,i}$。

有这三个信息我们就可以判断是否类别中均为一个数了。

~~你怎么知道这是我深夜在 U 群问怎么做这个问题然后 skip2004 告诉我的解法。~~

然后我们把之前 TLE on 23 的码改一改就可以了！

# 完整代码

[CF submission 243951477](https://codeforces.com/contest/351/submission/243951477)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
int fa[100020];
int a[100020];
int ans[100020];
int pre[100020];
int nxt[100020];
int p[100020];
ll sum[2][100020];
int cnt[100020];
multiset<int> s[100020];
int n, len, ANS, q, tot;
struct node
{
    int L, R, id;
} Query[1000020];
bool cmp(node a, node b)
{
    if (fa[a.L] != fa[b.L])
        return a.L < b.L;
    if (fa[a.L] & 1)
        return a.R > b.R;
    return a.R < b.R;
}
ll sq(int x) { return 1LL * x * x; }
bool same(int x) { return !cnt[x] ? 1 : !(sum[0][x] % cnt[x]) && !(sum[1][x] % cnt[x]) && sq(sum[0][x] / cnt[x]) * cnt[x] == sum[1][x]; }
void add(int x, bool ff)
{
    bool f = 0;
    if (ff & 1)
    {
        if (same(a[x]))
            f = 1;
        cnt[a[x]]++;
        sum[0][a[x]] += x - pre[x];
        sum[1][a[x]] += sq(x - pre[x]);
        if (!same(a[x]) && f)
            tot--;
    }
    else
    {
        if (same(a[x]))
            f = 1;
        cnt[a[x]]++;
        sum[0][a[x]] += nxt[x] - x;
        sum[1][a[x]] += sq(nxt[x] - x);
        if (!same(a[x]) && f)
            tot--;
    }
}
void del(int x, bool ff)
{
    bool f = 0;
    if (ff & 1)
    {
        if (!same(a[x]))
            f = 1;
        cnt[a[x]]--;
        sum[0][a[x]] -= x - pre[x];
        sum[1][a[x]] -= sq(x - pre[x]);
        if (same(a[x]) && f)
            tot++;
    }
    else
    {
        if (!same(a[x]))
            f = 1;
        cnt[a[x]]--;
        sum[0][a[x]] -= nxt[x] - x;
        sum[1][a[x]] -= sq(nxt[x] - x);
        if (same(a[x]) && f)
            tot++;
    }
}
int main()
{
    read(n);
    len = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
        fa[i] = (i + len - 1) / len;
        nxt[i] = n + 1;
        pre[i] = p[a[i]];
        nxt[pre[i]] = i;
        p[a[i]] = i;
    }
    read(q);
    for (int i = 1; i <= q; i++)
    {
        int L, R;
        read(L, R);
        Query[i] = {L, R, i};
    }
    sort(Query + 1, Query + q + 1, cmp);
    int L = 1, R = 0;
    for (int i = 1; i <= q; i++)
    {
        while (L > Query[i].L)
        {
            L--;
            if (nxt[L] > R)
                ANS++, tot++;
            else
                add(L, 0);
        }
        while (R < Query[i].R)
        {
            R++;
            if (pre[R] < L)
                ANS++, tot++;
            else
                add(R, 1);
        }
        while (L < Query[i].L)
        {
            if (nxt[L] > R)
                ANS--, tot--;
            else
                del(L, 0);
            L++;
        }
        while (R > Query[i].R)
        {
            if (pre[R] < L)
                ANS--, tot--;
            else
                del(R, 1);
            R--;
        }
        ans[Query[i].id] = ANS + 1 - (tot > 0);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：KaisuoShutong (赞：9)

# CF351D Jeff and Removing Periods

[题目链接](https://www.luogu.com.cn/problem/CF351D)。

## 转化

首先，一次操作后可以重排的含义是：**任意重排**。  
那么因为一次等差数列的取出条件是 $a$ 数组相等，故我们直接 sort 后每种元素取一次即可，答案为区间不同颜色个数。这是一个经典的莫队问题，可以在 $O(n^{\frac{3}{2}})$ 的时间复杂度内轻易实现。

等等，第一次操作怎么办？  
故问题转化为：如何求出区间内是否有某个数的出现位置构成等差数列？

## 解决

考虑同样使用莫队算法解决这个问题。

不妨对于每个位置 $i$，我们都处理出其后面距其远位置 $j$ 满足 $a_j=a_i$，且对于 $i$ 与 $j$ 中间的所有 $a$ 值等于 $a_i$ 的点，相邻两个距离都相同。  
具体地，在实现时，定义一个 $w$ 数组，表示若 $i$ 与 $j$ 的 $a$ 值相同，且满足中间 $a$ 值等于 $a_i$ 的相邻两个距离相同，则 $w$ 的值相同。也就是相同 $w$ 的两个点需满足：  
![satisfied](https://cdn.luogu.com.cn/upload/image_hosting/tuxv4kyn.png)

因为实现的问题，所以我要求 $w_i=w_j$ 还需满足 $i$ 和 $lst_{a_i}$ 的距离也等差。

举个例子：  
![](https://cdn.luogu.com.cn/upload/image_hosting/trtkbdwu.png)

那么现在只需要维护一个颜色的位置最小值和位置最大值即可。  
好像没法不带 log 完成啊……等等？

位置最小/大值？注意到其有个性质：每次加入都会成为 最小值/最大值 之一。  
那么开一个 `STL::deque`，即可完成此题。

时间复杂度 $O(n^{\frac{3}{2}})$。

点个赞吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
struct info{int l,r,n;}Q[maxn];
int n,q,bl,B[maxn],a[maxn],pr[maxn],C[maxn];
bool cmp(info x,info y) {return B[x.l]==B[y.l]?B[x.l]&1?x.r<y.r:x.r>y.r:x.l<y.l;}
int ls[maxn],lt[maxn],tot,nxt[maxn],W[maxn];deque<int>D[maxn];
int ASK(int x) {
	if(C[x]==1) return 1;
	else if(C[x]>1&&W[nxt[*D[x].begin()]]==W[*--D[x].end()]) return 1;
	return 0;
}
signed main() {
	memset(ls,-1,sizeof(ls)),memset(lt,-1,sizeof(lt));
	n=read(),bl=sqrt(n);
	for(int i=1;i<=n;i++) a[i]=read(),
		(~ls[a[i]])&&(!~lt[a[i]]||i-ls[a[i]]==lt[a[i]])?W[i]=W[ls[a[i]]]:W[i]=++tot,
		~ls[a[i]]?(nxt[ls[a[i]]]=i,lt[a[i]]=i-ls[a[i]]):0,ls[a[i]]=i,B[i]=(i-1)/bl+1;
	q=read();
	for(int i=1;i<=q;i++) Q[i]=(info){read(),read(),i};
	sort(Q+1,Q+1+q,cmp);
	int L=1,R=0,NUM=0,ans=0;
	for(int i=1;i<=q;i++) {
		while(R<Q[i].r) NUM-=ASK(a[++R]),ans+=(++C[a[R]]==1),D[a[R]].push_back(R),NUM+=ASK(a[R]);
		while(Q[i].l<L) NUM-=ASK(a[--L]),ans+=(++C[a[L]]==1),D[a[L]].push_front(L),NUM+=ASK(a[L]);
		while(Q[i].r<R) NUM-=ASK(a[R]),ans-=(--C[a[R]]==0),D[a[R]].pop_back(),NUM+=ASK(a[R--]);
		while(L<Q[i].l) NUM-=ASK(a[L]),ans-=(--C[a[L]]==0),D[a[L]].pop_front(),NUM+=ASK(a[L++]);
		pr[Q[i].n]=ans+(NUM==0);
	}
	for(int i=1;i<=q;i++) cout<<pr[i]<<'\n';
	return 0;
}
```

---

## 作者：幻影星坚强 (赞：5)

介绍一种更无脑的解法。

首先我们发现答案就是区间颜色数+区间是否存在间隔相同的颜色，前面可以用莫队解决，后面我们可以通过扫一遍，每次将当前颜色到上面一个颜色的距离与该颜色原先的间隔长度比较即可，在过程中我们可以记录有多少个颜色间隔长度依然相等来判断是否存在。

而我们发现后面这个东西如果每次只在最前面或最后面加入颜色的话，就只要记录一个颜色的最前面最后面的位置和间隔长度即可，而删除没有这么无脑，所以我们直接用回滚莫队避免删除，时间复杂度 $O(n\sqrt{n})$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 2e5 + 10;
int block;
int n, m;
struct Q
{
	int l, r, ids;
	
}que[N];
int LL[N], RR[N], ids[N];
bool pd(Q i, Q j)
{
	return (ids[i.l] == ids[j.l] ? i.r < j.r : i.l < j.l);
}
int col[N], ans[N];
int len[N], tot[N], L[N], R[N], _L[N], _len[N], _tot[N];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i)
	scanf("%d", &col[i]);
	scanf("%d", &m);
	block = m / sqrt(n);
	if(block > n)block = n;
	if(block <= 0)block = 1;
	ids[0] = -1;
	for (int i = 1; i <= n; ++ i)
	{
		ids[i] = i / block;
		if(LL[ids[i]] == 0)
		LL[ids[i]] = i;
		RR[ids[i]] = i;
	}
	int q = 0;
	for (int i = 1; i <= m; ++ i)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		if(ids[l] == ids[r])
		{
			for (int j = l; j <= r; ++ j)
				tot[col[j]]	= 0, len[col[j]] = 0;
			int zong = 0;
			for (int j = l; j <= r; ++ j)
			{
				ans[i] += (tot[col[j]] == 0);
				zong += (tot[col[j]] == 0);
				if(tot[col[j]] == 0)
				L[col[j]] = R[col[j]] = j;
				else
				{
					if(len[col[j]] == 0)
					{
						len[col[j]] = j - R[col[j]];
					}
					else
					if(len[col[j]] > 0)
					{
						if(len[col[j]] != j - R[col[j]])
						-- zong, len[col[j]] = -1;
					}
					R[col[j]] = j;
				}
				++ tot[col[j]];
			}
			ans[i] += (zong == 0);
		}
		else
		{
			que[++ q] = (Q){l, r, i};
		}
	}
	sort(que + 1, que + 1 + q, pd);
	memset(tot, 0, sizeof(tot));
	memset(len, 0, sizeof(len));
	int pos = 1, col_tot = 0, num = 0, zong = 0;
	for (int i = 1; i <= q; ++ i)
	{
		if(ids[que[i].l] != ids[que[i - 1].l])
		{
			memset(tot, 0, sizeof(tot));
			memset(len, 0, sizeof(len));
			++ num, pos = RR[ids[que[i].l]], col_tot = zong = 0;
		}
		while(pos < que[i].r)
		{
			++ pos;
			col_tot += (tot[col[pos]] == 0);
			zong += (tot[col[pos]] == 0);
			if(tot[col[pos]] == 0)
			L[col[pos]] = R[col[pos]] = pos;
			else
			{
				if(len[col[pos]] == 0)
				{
					len[col[pos]] = pos - R[col[pos]];
				}
				else
				if(len[col[pos]] > 0)
				{
					if(len[col[pos]] != pos - R[col[pos]])
					-- zong, len[col[pos]] = -1;
				}
				R[col[pos]] = pos;
			}
			++ tot[col[pos]];
		}
		int _zong = zong, _col_tot = col_tot;
		for (int j = RR[ids[que[i].l]]; j >= que[i].l; -- j)
		{
			_len[col[j]] = len[col[j]];
			_L[col[j]] = L[col[j]];
			_tot[col[j]] = tot[col[j]];
		}
		for (int j = RR[ids[que[i].l]]; j >= que[i].l; -- j)
		{
			_col_tot += (_tot[col[j]] == 0);
			_zong += (_tot[col[j]] == 0);
			if(_tot[col[j]] == 0)
			_L[col[j]] = j;
			else
			{
				if(_len[col[j]] == 0)
				{
					_len[col[j]] = _L[col[j]] - j;
				}
				else
				if(_len[col[j]] > 0)
				{
					if(_len[col[j]] != _L[col[j]] - j)
					-- _zong, _len[col[j]] = -1;
				}
				_L[col[j]] = j;
			}
			++ _tot[col[j]];
		}
		ans[que[i].ids] = _col_tot + (_zong == 0);
	}
	for (int i = 1; i <= m; ++ i)
	printf("%d\n", ans[i]);
}
```


---

## 作者：_Anchor (赞：4)

# Problem

[CF351D Jeff and Removing Periods](https://www.luogu.com.cn/problem/CF351D)


# Solution

首先需要想到的是一个结论：

对于一个区间，如果其存在某一个值的位置集合构成等差数列，那么这个区间的答案就是区间颜色个数，如果不存在（也就是说所有值的位置集合都不能构成等差数列），那么这个区间的答案就是区间颜色个数+1，原因显然。

正确性显然，因为我们相当于把第一次删除的机会拿来对区间所有元素“排序”了，排序过后，答案显然就是区间颜色个数了，因为都构成了差为 1 的等差数列。

而如果我们第一次可以不浪费地再删掉一个元素，那么我们何乐而不为呢？于是就有了这个加一和不加一的区别。

而这个问题当中，区间数颜色是一个经典问题，不再赘述，具体可以看[P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)，这里我们使用莫队来维护。

那么我们现在的问题就是：对于所有值，维护其位置集合当前是否是等差数列。

我们可以考虑这样来做：对于每一个值维护一个双端队列，然后每次插入和删除相当于都是在队首和队尾操作。

然后思考怎么快速判断当前的双端队列是否是一个等差数列。

我们发现可以对每一个值维护一个并查集，也就是说，我们可以在原序列中维护每一个点可以形成的等差数列的最左端，也就是说，我们每次到一个值，就询问这个值的上一个位置以及上一个位置结尾的等差数列对应的公差。

然后我们检查一下当前点可不可以接上去，可以就把当前点父亲设为上一个位置，不可以就是其本身，再更新公差和位置即可。

判断的话就是取出当前的第 2 项，然后在并查集里查看和最后一项是否在同一个集合中即可。

可能这里大家会有一个问题：为什么中间的位置就不用判断了呢？

这是因为我们这里的并查集一定是“连续”的，也就是说，因为每一个点要么和自己连，要么可以去最接近的上一个点，所以如果右端点和左端点在同一个集合，那么右端点肯定是通过中间一一相连在到了左端点，于是这里相当于自动判断了中间点。

最后，时间复杂度是 $O(n\times\alpha(n)\times\sqrt{n})$。（这里偷懒没有写按秩合并就当作是 $O(nlogn\sqrt{n})$ 吧）

# Code

跑的很慢。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
const int N=1e5+5;
#define ll long long
int n,m,k;
int bl[N],fa[N];
int a[N],Ans[N],cnt[N],pos[N],d[N];
struct Query{int l,r,id;}Q[N];
int Now,Num;
deque<int> q[N];
int Getfa(int x){return x==fa[x]?x:fa[x]=Getfa(fa[x]);}
inline bool Check(int val){
    if(q[val].empty()) return false;
    int l=q[val].front(),r=q[val].back();
    if(l==r) return true;
    q[val].pop_front();
    int g=q[val].front();
    bool ret=(Getfa(g)==Getfa(r));
    q[val].push_front(l);
    return ret;
}
inline void Add(int x,bool f){
	if(Check(a[x])) Num--;
	if(f==false) q[a[x]].push_front(x);
	else q[a[x]].push_back(x);
	cnt[a[x]]++;
	if(cnt[a[x]]==1) Now++;
	if(Check(a[x])) Num++;
	return ;
}
inline void Del(int x,bool f){
	if(Check(a[x])) Num--;
	if(f==false) q[a[x]].pop_front();
	else q[a[x]].pop_back();
	cnt[a[x]]--;
	if(cnt[a[x]]==0) Now--;
	if(Check(a[x])) Num++;
	return ;
}
inline bool Cmp(Query x,Query y){return bl[x.l]^bl[y.l]?bl[x.l]<bl[y.l]:bl[x.l]&1?x.r<y.r:x.r>y.r;}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		if(!pos[a[i]]) fa[i]=-1,d[i]=0;
		else{
			if(i-pos[a[i]]==d[pos[a[i]]]) fa[i]=pos[a[i]];
			else fa[i]=i;
			d[i]=i-pos[a[i]];
		}
		pos[a[i]]=i;
	}
	read(m);
	const int t=sqrt(m);
	for(int i=1;i<=m;i++) read(Q[i].l),read(Q[i].r),Q[i].id=i;
	for(int i=1;i<=n;i++) bl[i]=(i-1)/t+1;
	sort(Q+1,Q+m+1,Cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l>Q[i].l) Add(--l,false);
		while(r<Q[i].r) Add(++r,true);
		while(l<Q[i].l) Del(l++,false);
		while(r>Q[i].r) Del(r--,true);
		Ans[Q[i].id]=Now+(Num==0?1:0);
	}
	for(int i=1;i<=m;i++) write(Ans[i]),putchar('\n');
	
	return 0;
} 
```


---

## 作者：abruce (赞：3)

先简化题意，如果我们可以将这个区间内一个数在一次内删完，我们剩下的就可以把颜色相同的排在一起，答案即为不同颜色数。  
如果没有一个数可以一次删完，答案为不同颜色数加一。  
对于区间不同颜色数，我们显然可以用莫队维护，此处不在赘述。  
对于有没有数可以一次删完，问题转化为有没有数在区间内出现下标为一个等差数列。我们可以每种颜色开一个 vector，如果这种颜色出现数量少于 $2$，则一定合法。否则我们从这种颜色的第三个出现位置开始枚举，如果它到上一个位置的距离等于上一个到上上个的距离，那么仍然是等差数列。否则我们需要分裂。我们可以记一个第二颜色来表示需不需要分裂。  
查询的时候，每个颜色记一个 deque，加入删除很好搞定，判断第二位置和末位置的第二颜色是否是一样的，即可。  
代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
struct node {
	int l,r,blk,id;
	friend bool operator<(node a,node b) {
		return a.blk==b.blk?a.r<b.r:a.l<b.l;
	}
} p[maxn];
int a[maxn],cnt[maxn],ans1,ans2,n,m,mn[maxn],mx[maxn],l=1,r,sn=256,bel[maxn],sum[maxn];//bel是其第二颜色
vector<int> v[maxn];
deque<int> q[maxn];
bool check(int c) {
	if(q[c].size()<=2)return 1;
	return bel[*++q[c].begin()]==bel[q[c].back()];//第二位置和末位置的第二颜色是否是一样的
}
void revise(int x,bool p,bool v) {
	int c=a[x];
	v?ans1+=!cnt[c]++:ans1-=!--cnt[c];
	if(!q[c].empty())ans2-=check(c);
	if(v)p?q[c].push_back(x):q[c].push_front(x);
	else p?q[c].pop_back():q[c].pop_front();
	if(!q[c].empty())ans2+=check(c);
}
void md(int i) {
	while(l>p[i].l)revise(--l,0,1);
	while(r<p[i].r)revise(++r,1,1);
	while(l<p[i].l)revise(l++,0,0);
	while(r>p[i].r)revise(r--,1,0);
	sum[p[i].id]=ans1+(ans2==0);
}
int main() {
	scanf("%d",&n);
	for(register int i=1; i<=n; i++)scanf("%d",&a[i]),v[a[i]].push_back(i);
	for(register int i=1; i<=n; i++) {
		if(v[i].size()<=2)continue;
		for(register int j=2; j<v[i].size(); j++)bel[v[i][j]]=bel[v[i][j-1]]+(v[i][j]-v[i][j-1]!=v[i][j-1]-v[i][j-2]);//预处理第二颜色
	}
	scanf("%d",&m);
	for(register int i=1; i<=m; i++)scanf("%d%d",&p[i].l,&p[i].r),p[i].blk=p[i].l/sn,p[i].id=i;
	sort(p+1,p+m+1);
	for(register int i=1; i<=m; i++)md(i);
	for(register int i=1; i<=m; i++)printf("%d\n",sum[i]);
	return 0;
}
```

---

## 作者：Southern_Dynasty (赞：2)

首先做一点显然的转化：在进行第一次操作之后，可以将相同的数排在一起，这样一次就能删掉一种数。如果一开始就能删光一种数的话，那么次数就是区间颜色数，否则就是区间颜色数 $+1$。


所以现在原问题变成了两个问题：求区间内不同颜色数，判断区间内是否有某种颜色满足其出现位置构成等差数列。

第一问是经典问题，可以离线后 BIT 做到 $O(n\log n)$。

考虑第二问，设 $pre_i$ 表示 $a_i$ 上一次出现的位置，$nxt_i$ 表示 $a_i$ 下一次出现的位置。$pos_i$ 表示最小的左端点 $l$，使得 $[l,i]$ 中 $a_i$ 出现的位置成等差数列，**$a_l$ 不一定等于 $a_r$**。显然前两项易求，$pos$ 可以递推求出。

那么原问题相当于是检验 $\max_{i=l}^{r}[pos_i\le l][nxt_i>r]$ 是否为 $1$。考虑离线扫描线，用线段树维护所有 $nxt_i>r$ 的位置的 $pos_i$ 最小值。扫到 $r$ 的时候直接把 $pre_r$ 位置的值设为 $+\infty$，再更新 $r$ 位置的值，最后判断 $[l,r]$ 的最小值是否 $\le l$ 即可。

时间复杂度 $O(n\log n)$。

卡常：不难发现 $nxt$ 数组是没用的，而且由于值域小，算 $pre$ 的时候可以直接开桶。

这样就可以拿到最优解了。

Code：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define gt getchar
#define pt putchar
#define fst first
#define scd second
#define SZ(s) ((int)s.size())
#define all(s) s.begin(),s.end()
#define pb push_back
#define eb emplace_back
#define re register
typedef long long ll;
typedef double db;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;
const int N=1e5+5;
const int inf=1e9;
const int SIZE=(1<<14);
using namespace std;
using namespace __gnu_pbds;
typedef pair<int,int> pii;
template<class T,class I> inline void chkmax(T &a,I b){a=max(a,(T)b);}
template<class T,class I> inline void chkmin(T &a,I b){a=min(a,(T)b);}
inline bool __(char ch){return ch>=48&&ch<=57;}
inline char gc(){
	static char buf[SIZE],*begin=buf,*end=buf;
	return begin==end&&(end=(begin=buf)+fread(buf,1,SIZE,stdin),begin==end)?EOF:*begin++;
}
template<class T> inline void read(T &x){
	x=0;bool sgn=0;static char ch=gc();
	while(!__(ch)&&ch!=EOF) sgn|=(ch=='-'),ch=gc();
	while(__(ch)) x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	if(sgn) x=-x;
}
template<class T,class ...I> inline void read(T &x,I &...x1){
	read(x);
	read(x1...);
}
template<class T> inline void print(T x){
	static char stk[70];short top=0;
	if(x<0) pt('-');
	do{stk[++top]=x>=0?(x%10+48):(-(x%10)+48),x/=10;}while(x);
    while(top) pt(stk[top--]);
}
template<class T> inline void printsp(T x){
	print(x);
	putchar(' ');
}
template<class T> inline void println(T x){
	print(x);
	putchar('\n');
}
int n,m,a[N],pre[N],pos[N],ans[N],mp[N];
vector<pair<pii,int> > vec[N];
vector<pii> qry[N];
int c[N];
inline int lowbit(int x){
	return x&(-x);
}
inline void add(int x,int w){
	while(x<=n){
		c[x]+=w;
		x+=lowbit(x);
	} 
}
inline int query(int x){
	int ans=0;
	while(x){
		ans+=c[x];
		x-=lowbit(x); 
	}
	return ans;
}
struct Node{
	int l,r;
	int mn;
}node[N<<2];
inline int lson(int x){
	return x<<1;
}
inline int rson(int x){
	return x<<1|1;
}
inline void push_up(int p){
	node[p].mn=min(node[lson(p)].mn,node[rson(p)].mn);
}
void build(int p,int l,int r){
	node[p].l=l,node[p].r=r;
	node[p].mn=inf;
	if(l==r) return;
	int mid=l+((r-l)>>1);
	build(lson(p),l,mid);
	build(rson(p),mid+1,r);
}
void update(int p,int x,int w){
	int l=node[p].l,r=node[p].r;
	if(l==r) return node[p].mn=w,void();
	int mid=l+((r-l)>>1);
	if(x<=mid) update(lson(p),x,w);
	else update(rson(p),x,w);
	push_up(p);
}
int query(int p,int ql,int qr){
	int l=node[p].l,r=node[p].r;
	if(ql<=l&&r<=qr) return node[p].mn;
	int mid=l+((r-l)>>1),ans=inf;
	if(ql<=mid) chkmin(ans,query(lson(p),ql,qr));
	if(qr>mid) chkmin(ans,query(rson(p),ql,qr));
	return ans; 
}
signed main(){
	read(n);
	for(re int i=1;i<=n;++i){
		read(a[i]);
		pre[i]=mp[a[i]];
		mp[a[i]]=i;
	}
	for(re int i=1;i<=n;++i){
		if(!pre[i]) pos[i]=1;
		else if(i-pre[i]==pre[i]-pre[pre[i]]) pos[i]=pos[pre[i]];
		else pos[i]=pre[pre[i]]+1;
	}
	read(m);
	for(re int l,r,i=1;i<=m;++i){
		read(l,r);
		vec[l-1].eb(make_pair(pii(l,i),-1));
		vec[r].eb(make_pair(pii(l,i),1));
		qry[r].eb(l,i); 
	}
	for(re int r=1;r<=n;++r){
		add(pre[r]+1,1);
		for(auto qwq:vec[r]){
			int l=qwq.fst.fst,id=qwq.fst.scd,w=qwq.scd;
			ans[id]+=query(l)*w;
		}
	}
	build(1,1,n);
	for(re int r=1;r<=n;++r){
		update(1,r,pos[r]);
		if(pre[r]) update(1,pre[r],inf);
		for(auto qwq:qry[r]){
			int l=qwq.fst,id=qwq.scd; 
			ans[id]+=(query(1,l,r)>l);
		}
	}
	for(re int i=1;i<=m;++i) println(ans[i]);
	return 0;
}
```


---

## 作者：快乐的大童 (赞：0)

[https://www.luogu.com.cn/problem/CF351D](https://www.luogu.com.cn/problem/CF351D)

由于每次操作后存在重排操作，我们可以让序列（询问的区间）中的相同值放在一块，这样以后每次操作就能删掉一整个值相同的位置了。那么第二次操作后所需操作数就是当前序列中不同数的个数。经典数颜色问题，离线线段树/莫队/主席树都能做。

数颜色问题：[https://www.luogu.com.cn/problem/P1972](https://www.luogu.com.cn/problem/P1972)

设原序列不同数个数为 $c$，现在考虑第一次操作该怎么做，如果第一次操作能删掉一整个颜色，那么第二次操作以后会使用 $c-1$ 次操作，总操作次数就是 $c$；否则不能删掉一整个颜色，第二次操作以后会使用 $c$ 次操作，总操作次数就是 $c+1$。

序列能删掉一整个颜色当且仅当存在某个颜色使得该颜色出现的位置构成等差数列。

考虑对每个位置求出最远的 $j$ 使得区间 $[j,i]$ 中颜色 $a_i$ 出现的位置无法构成等差数列，这个显然是可以递推求的，令 $pos_i=j$。

那么如果一个区间存在某个颜色使得该颜色构成等差数列，就说明对于区间中每种颜色**最后一次**出现的位置 $j$ 的 $pos_j$ 的最小值 $<l$。注意不能是区间任意位置，否则会出现该区间某种颜色出现位置的某个前缀是等差数列而整个序列不是等差数列的情况，我们很难判掉。

强制让区间中颜色最后一次出现的位置有贡献，我们发现这又是经典数颜色问题（的一种变形），仍然可以使用离线线段树/莫队/主席树解决，时间复杂度 $O(n\log n)$ 或 $O(n\sqrt n)$。

代码采用的方法是主席树。

[https://codeforces.com/contest/351/submission/244017885](https://codeforces.com/contest/351/submission/244017885)

---

