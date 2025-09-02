# Nezzar and Binary String

## 题目描述

Nezzar has a binary string $ s $ of length $ n $ that he wants to share with his best friend, Nanako. Nanako will spend $ q $ days inspecting the binary string. At the same time, Nezzar wants to change the string $ s $ into string $ f $ during these $ q $ days, because it looks better.

It is known that Nanako loves consistency so much. On the $ i $ -th day, Nanako will inspect a segment of string $ s $ from position $ l_i $ to position $ r_i $ inclusive. If the segment contains both characters '0' and '1', Nanako becomes unhappy and throws away the string.

After this inspection, at the $ i $ -th night, Nezzar can secretly change strictly less than half of the characters in the segment from $ l_i $ to $ r_i $ inclusive, otherwise the change will be too obvious.

Now Nezzar wonders, if it is possible to avoid Nanako being unhappy and at the same time have the string become equal to the string $ f $ at the end of these $ q $ days and nights.

## 说明/提示

In the first test case, $ \underline{00000} \rightarrow \underline{000}11 \rightarrow 00111 $ is one of the possible sequences of string changes.

In the second test case, it can be shown that it is impossible to have the string $ f $ at the end.

## 样例 #1

### 输入

```
4
5 2
00000
00111
1 5
1 3
2 1
00
01
1 2
10 6
1111111111
0110001110
1 10
5 9
7 10
1 7
3 5
6 10
5 2
10000
11000
2 5
1 3```

### 输出

```
YES
NO
YES
NO```

# 题解

## 作者：fanfansann (赞：12)

## E - Nezzar and Binary String


A 有一个长度为 $n$ 的二进制串 S，他想让自己最好的朋友 B 看，B将会用 $q$ 天的时间来检查这个二进制串。
第 $i$ 天， B会在这一天早上检查这个二进制串的一个区间 $[l_i,r_i]$ ，如果这个区间内的数字全部都是一致的，也就是全部都为 $1$ 或者全部都为 $0$ ，B就会很开心，否则她就会不开心。
A为了使 B 每次检查都能变得开心，所以 A 会在每天 B 检查之后的当天晚上偷偷地去修改这个二进制串，使得 B 第二天检查的时候能够开心。为了不被 B 发现，A 每次只能修改今天早上 B 检查过的那个区间 $[l_i,r_i]$，并且修改的字符的个数必须**小于**这个区间字符总数的一半，

与此同时，A还有一个任务，就是他希望可以通过这 $q$ 天的修改，将二进制串 $s$ 变成 $f$ 。请问 A 能够在每天都保证 B 开心的同时，将二进制串 $s$ 修改为 $f$ 呢吗？

$T$ 组数据，每组输入两个整数 $n$ 和 $q$ ，然后输入两个二进制串 $s$ 和 $f$，接着输入 $q$ 个区间。若 A 能在保证 B 每次都开心的前提下，完成这个任务，则输出 `YES` 否则输出 `NO`。

$1 \le t \le 2 \cdot 10^5,1 \le n \le 2 \cdot 10^5,0 \le q \le 2 \cdot 10^5$

```cpp
4
5 2
00000
00111
1 5
1 3
2 1
00
01
1 2
10 6
1111111111
0110001110
1 10
5 9
7 10
1 7
3 5
6 10
5 2
10000
11000
2 5
1 3
```

```cpp
YES
NO
YES
NO
```
**Solution**

我们本来按照题意的顺序，是她先查看，我们再修改，但是每次改都要受到之后她查看的区间的影响。

比如样例一：

> 第一天，她要看 $[1,5]$ ，很开心走了 ~ 
> 
> ------
> 第一天晚上，我可以改 $[1,5]$ ，**但是**她明天要看 $[1,3]$ ，所以我要**先保证** $[1,3]$ 是没有 $0,1$ 同时存在的，再看能不能改 $[1,5]$ 的其他元素使得$s\to f$，就很怪，当前的操作需要考虑之后的影响，我们还需要提前知道下一次的操作区间，就很奇怪。
> 
> ------
> 第二天，她要看 $[1,3]$，因为前一天晚上我的努力，她很开心的走了 ~
> 
> ------
> 第二天晚上，我可以改 $[1,3]$，明天她不看了，我就尽量改
> $[1,3]$ 使得$s\to f$

但是如果我们反过来，变成我们先改，她再看，也就是我们早上先改，晚上她再看，就很舒服。

>第一天早上，我可以改 $[1,3]$ ，**因为**她晚上要看 $[1,3]$ ，所以我们只需要保证 $[1,3]$ 是没有 $0,1$ 同时存在的，再尽量朝着 $f\to s$ 的方向改 $[1,3]$ 。
> 
> ------
>第一天晚上，她看完 $[1,3]$ ，开心地走了 ~
> 
> ------
>第二天早上，我可以改 $[1,5]$，因为她晚上要看 $[1,5]$，我们就保证 $[1,5]$ 是没有 $0,1$ 同时存在的，再尽量朝着 $f\to s$ 的方向改 $[1,5]$ ，因为这是最后一天了，我发现可以直接把 $f$ 变成 $s$ ，并且 $s$ 串全是 $0$，她看了一定很开心 (●ˇ∀ˇ●) ，我就这么做了
> 
> ------
>第二天，她要看 $[1,5]$，因为早上我的努力，她开心地蹦蹦跳跳的走了 ~

其实正序做不只是很做起来，而且最关键的是，我们需要自己考虑最优解，这是非常困难的，而我们交换顺序对题目的答案不会造成任何影响，但是却会给我们的实现带来很大的方便，并且稍微分析一下就会发现，逆序做，不需要我们有任何操作空间。

使用逆向思维，可以帮助我们简化这个问题。然后我们来考虑怎么解决这个问题。

我们将会从 $f$ 出发，满足每次区间的一致性，致力于得到 $s$ 。

由于我们只有一个操作：修改定区间内的二进制串，并且每次最多只能修改个数**小于**区间长度的**一半**。

实际上这就代表着我们只能有一种修改方式：将 $0,1$ 中数量少的那一方修改为另一方，因为只有这样修改，我们才既能保证区间内的字符完全相同，又能保证修改的数量不超过区间长度的一半。

但是如果区间内 $0,1$ 的**数量相同**，那就没办法修改了，无论偏袒哪一方都不能在修改小于区间长度的一半的条件下修改成同一个数字，直接输出 `NO` 即可。

然后我们发现我们会跟着这个区间的设定，一步一步**没有任何操作空间**地从头修改到最后，所以如果最后我们得到的字符串，如果就是 $s$，那么恭喜你，成功完成了这个任务，你会很开心，她会很开心，我们都获得了快乐，直接输出 `YES` 即可。

同理，如果最后得到的不是 $s$，那么抱歉，输出 `NO` 。

最后一个问题，如果快速地实现区间修改呢？

我们发现我们只需要有两个操作即可：区间全部修改（区间染色），区间查询（查询 $0,1$ 的个数）

而数据很大：$1 \le t \le 2 \cdot 10^5,1 \le n \le 2 \cdot 10^5,0 \le q \le 2 \cdot 10^5$，需要 $O(Tqlogn)$ 的时间复杂度以及高超的卡常技巧，这一切无不指引着一个神奇的数据结构：线段树 ~ 

我们只需要维护区间和就行了，因为区间和就是1的个数。

由于需要区间查询，所以我们需要加上lazytag，就是我们修改的时候，区间是 $0$ 还是 $1$。由于不能初始化为 $0$ ，重复了，所以我们记得初始化为 `-1` 就好。

然后就是很简单的代码了：

**Code**

注意：毒瘤出题人把数据开到了 $2\times 10^5$，而线段树需要开四倍空间。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;
typedef long long ll;
typedef int itn;
const int N = 3e5 + 7, mod = 1e9 + 7;
const ll INF = 1e18 + 7;

int n, m, q;
int L[N], R[N];
char s[N], f[N];

struct Tree
{
    int l, r;
    int sum;//维护 1 的个数, 因为 0 求和还是 0 和就是 1 的个数
    int lz;//1 / 0
}tr[N << 2];

void push_up(int p)
{
    tr[p].sum = tr[p << 1].sum +  tr[p << 1 | 1].sum;
}

void push_down(int p)
{
     if(tr[p].lz == -1) return ;
     tr[p << 1].lz = tr[p].lz;
     tr[p << 1 | 1].lz = tr[p].lz;
     tr[p << 1].sum = (tr[p << 1].r - tr[p << 1].l + 1) * tr[p].lz;//都是等于而不是加
     tr[p << 1 | 1].sum = (tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1) * tr[p].lz;
     tr[p].lz = -1;
}

void build(int p, int l, int r)//f
{
    tr[p].l = l, tr[p].r = r, tr[p].lz = -1;
    if(l == r) {
        tr[p].sum = f[l] - '0';
        tr[p].lz = -1;
        return ;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

void modify(int p, int l, int r, int val)
{
    if(tr[p].l >= l && tr[p].r <= r) {
        tr[p].sum = (tr[p].r - tr[p].l + 1) * val;//这里全部变成 1 ，sum 等于区间长度，全部变成 0, sum 就是 0
        tr[p].lz = val;
        return ;
    }
    push_down(p);
    int mid = tr[p].l + tr[p].r >> 1;
    if(l <= mid) modify(p << 1, l, r, val);
    if(r > mid) modify(p << 1 | 1, l, r, val);
    push_up(p);
}

int query(int p, int l, int r)
{
    if(tr[p].l >= l && tr[p].r <= r) {
        return tr[p].sum;
    }
    push_down(p);
    int mid = tr[p].l + tr[p].r >> 1;
    int res = 0;
    if(l <= mid) res += query(p << 1, l, r);
    if(r > mid) res += query(p << 1 | 1, l, r);
    return res;
}

bool check()
{
    for(int i = 1; i <= n; ++ i) {
        if(query(1, i, i) != s[i] - '0') {
            return false;
        }
    }
    return true;
}

bool solve()
{
    scanf("%d %d", &n, &q);
    scanf("%s %s", s + 1, f + 1);
    for (int i = 1; i <= q; ++ i) {
        scanf("%d %d", &L[i], &R[i]);
    }
    build (1, 1, n);
    for(int i = q; i >= 1; -- i) {
        int l = L[i], r = R[i];
        int num1 = query(1, l, r);//sum
        int len = r - l + 1;
        if (num1 * 2 == len) return false;// 0 和 1 的长度相等 
        else if(num1 * 2 < len) modify(1, l, r, 0);
        else modify(1, l, r, 1);
    }

    if (!check()) {
        return false;
    }
    return true;
}

itn t;

int main()
{
    scanf("%d", &t);
    while (t -- ) {
        if (solve()) {
            puts("YES");
        }
        else {
            puts("NO");
        }
    }
    return 0;
}
```


---

## 作者：胖头鱼学员 (赞：3)

# CF1478E & CF1477B

## [洛谷传送门](https://www.luogu.com.cn/problem/CF1477B)

## [CF传送门](http://codeforces.com/problemset/problem/1477/B)

## $Question \ Meaning$

有$A$和$B$在玩字符串游戏：

给定字符串$s$，现在有$q$天，每天都要查询一段$l_i \sim r_i$，$B$问是不是全是$0$或$1$，如果不是，$B$就会不爽。但是在这之前，$A$能将其改变不超过一半的字符，不让$B$变得不爽，问能不能在不让$B$变得爽的同时，让$s$在$q$天后变成$t$。

## $Solution$

我们手玩样例得以发现，正着求并不会那么好做，因为当前的每一步关系着以后的每一步。

那么在这种时候我们可以考虑**反着求**

对于每一组$l_i \sim r_i$，分类讨论其中$01$数量：

1. 若其中超过一半是$1$，此时一定有不足一半的$0$，那么我们将所有的$0$改成$1$即可。

2. 若其中不足一半的$1$，那么我们直接将所有的$1$改成$0$即可。

3. 若其中的$01$数量相等，则我们不能改动字符串。

根据上面的分类讨论可知，对于$1st$、$2nd$的情况我们可以回复，但是$3rd$不可以，所以我们只需要对于每一段改它的$0$和$1$，判断区间内$01$数量，改完之后询问两字符串是否相等即可。

## $Code$
```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 2e5 + 10;

int T, n, q;
char s[N], f[N];
int l[N], r[N];

struct segement_tree {
  int l, r;
  int sum, lazy;
} t[N << 2];

void build(int root, int l, int r) {
  t[root].lazy = -1;
  t[root].l = l, t[root].r = r;
  if (l >= r) return;
  int mid = (l + r) >> 1;
  build(root << 1, l, mid);
  build(root << 1 | 1, mid + 1, r);
}

void pushup(int root) {
  t[root].sum = t[root << 1].sum + t[root << 1 | 1].sum;
}

void pushdown(int root) {
  if (t[root].lazy != -1) {
    int& s = t[root].lazy;
    t[root << 1].lazy = t[root << 1 | 1].lazy = s;
    t[root << 1].sum = (t[root << 1].r - t[root << 1].l + 1) * s;
    t[root << 1 | 1].sum = (t[root << 1 | 1].r - t[root << 1 | 1].l + 1) * s;
    t[root].lazy = -1;
  }
}

void update(int root, int l, int r, int v) {
  int L = t[root].l, R = t[root].r;
  if (l <= L && R <= r) {
    t[root].lazy = v;
    t[root].sum = (R - L + 1) * v;
    return;
  }
  pushdown(root);
  int mid = (L + R) >> 1;
  if (l <= mid) update(root << 1, l, r, v);
  if (r > mid) update(root << 1 | 1, l, r, v);
  pushup(root);
}

int query(int root, int l, int r) {
  int L = t[root].l, R = t[root].r;
  if (l <= L && R <= r) {
    return t[root].sum;
  }
  pushdown(root);
  int mid = (L + R) >> 1;
  if (r <= mid) return query(root << 1, l, r);
  if (l > mid) return query(root << 1 | 1, l, r);
  return query(root << 1, l, r) + query(root << 1 | 1, l, r);
}

bool check(bool ok) {
  for (int i = 1; i <= n; i++) {
    if (query(1, i, i) != s[i] - '0') {
      return 0;
    }
  }
  return 1 && ok;
}

void solve() {
  scanf("%d %d", &n, &q);
  scanf("%s %s", s + 1, f + 1);
  for (int i = 0; i < q; i++) {
    scanf("%d %d", &l[i], &r[i]);
  }
  build(1, 1, n);
  for (int i = 1; i <= n; i++) {
    update(1, i, i, f[i] - '0');
  }
  bool ok = 1;
  for (int i = q - 1; i >= 0 && ok; i--) {
    int num = query(1, l[i], r[i]);
    if (num * 2 == r[i] - l[i] + 1) {
      ok = 0;
    } else if (num * 2 < r[i] - l[i] + 1) {
      update(1, l[i], r[i], 0);
    } else {
      update(1, l[i], r[i], 1);
    }
  }
  puts(check(ok) ? "YES" : "NO");
}

int main() {
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
```

## $After \ the \ problem \ is \ solved$

其实对于所有题目来讲，如果正面不好求的话，最好的思路就是从反面入手。

**Update 2021/2/2 增加了代码**

---

## 作者：Epoch_L (赞：1)

题目链接：

[洛谷](https://www.luogu.com.cn/problem/CF1477B "洛谷")

[Codeforces](http://codeforces.com/problemset/problem/1477/B "Codeforces")
## Solution
我一开始以为是道结论题，一直想贪心策略，后来卡了二十多分钟，感觉不行，赶紧换方法。

这题不能正着做，只能反过来，从答案串往原串推，因为正着做有后效性，十分恶心。反过来做以后，顺序就变了，即先改后看，对于每一次检查的区间 $[l,r]$，我们这次修改，一定要改成全为 $0$ 或 $1$，由于我们只能改小于一半的字符，所以只能把数量小的变为数量多的，如果相同，则无法改，直接判为不能。

所以，我们现在需要解决的问题为：
+ 查询区间 $1$ 的个数
+ 将区间全部修改为 $0$ 或 $1$

对于问题 $1$，直接区间求和即可。线段树即可完美解决。

最后，告诫大家，永远不要相信 memset 的复杂度，能不用就不用。这题要把 lazy 标记最开始打成 $-1$，不要 memset，建树时解决就可以了，不然会 T。
## Code
```cpp
#include<bits/stdc++.h>
#define ls p*2
#define rs p*2+1
using namespace std;
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
	x=r*w;
}
const int N=2e5+7;
char c[N],t[N];
int sum[N*4],lazy[N*4],size[N*4],ans;
void update(int p)
{
	size[p]=size[ls]+size[rs];
	sum[p]=sum[ls]+sum[rs];
}
void build(int p,int l,int r)
{
	lazy[p]=-1;
	if(l==r)
	{
		sum[p]=t[l]-'0';
		size[p]=1;
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	update(p);
}
void pushdown(int p)
{
	lazy[ls]=lazy[p];
	sum[ls]=size[ls]*lazy[p];
	lazy[rs]=lazy[p];
	sum[rs]=size[rs]*lazy[p];
	lazy[p]=-1;
}
void change(int p,int l,int r,int x,int y,int k)
{
	if(x<=l&&r<=y)
	{
		lazy[p]=k;
		sum[p]=size[p]*k;
		return;
	}
	if(lazy[p]!=-1)pushdown(p);
	int mid=l+r>>1;
	if(x<=mid)change(ls,l,mid,x,y,k);
	if(y>mid)change(rs,mid+1,r,x,y,k);
	update(p);
}
void query(int p,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
	{
		ans+=sum[p];
		return;
	}
	if(lazy[p]!=-1)pushdown(p);
	int mid=l+r>>1;
	if(x<=mid)query(ls,l,mid,x,y);
	if(y>mid)query(rs,mid+1,r,x,y);
}
int qx[N],qy[N];
void solve()
{
	int n,q;
	read(n);read(q);
	scanf("%s",c+1);scanf("%s",t+1);
	build(1,1,n);
	for(int i=1;i<=q;i++)
		read(qx[i]),read(qy[i]);
	for(int i=q;i>=1;i--)
	{
		ans=0;
		int x=qx[i],y=qy[i];
		int len=y-x+1;
		query(1,1,n,x,y);
		if(ans==len-ans){puts("NO");return;}
		if(ans<len-ans)change(1,1,n,x,y,0);
		else change(1,1,n,x,y,1);
	}
	for(int i=1;i<=n;i++)
	{
		ans=0;
		query(1,1,n,i,i);
		if(ans!=c[i]-'0'){puts("NO");return;}
	}
	puts("YES");
}
int main()
{
	int T;
	read(T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：activeO (赞：1)

## 题目大意

A 和 B 在玩游戏，如果有一天 B 来检查字符串的一段区间不是全是 1 或 全是 0，那么 B 就会不爽，于是每次 B 检查前 A 都可以对一段区间做修改（全改为 1 或 0）。现在要求在 B 每天都开心的情况下，将字符串 S 改为 字符串 T。

## 思路

我们模拟一下样例的过程，发现正着不好做，考虑反过来，即将 T 改为 F。

对于 一段区间 $ [l_i,r_i] $

- 如果 01 数量相同，不能改变字符串。
- 如果 1 的数量超过一半，就只能把所有 0 改为 1。
- 如果 1 的数量没超过一半，就只把所有 1 改为 0。

再看到这个数据范围：
 
$ 1 \leq t \leq 2 \cdot 10^5 $

$ 1 \leq n \leq 2 \cdot 10^5 $

$ 0 \leq q \leq 2 \cdot 10^5 $

~~毒瘤啊~~就用线段树来维护吧，显然只用维护 1 的个数。

然后就是简单的模板过程。不会的跳转至 [P3372](https://www.luogu.com.cn/problem/P3372)

## 代码

```cpp

//祝大家学习愉快!
#include <bits/stdc++.h>

const int maxn=2e5+10;
int a[maxn],b[maxn];
char s[maxn],t[maxn];
int n,m;

struct Tree{
	int l,r;
	int sum,lz;
}tree[maxn<<2];

inline void pushdown(int x){
	if(tree[x].lz==-1) return;
	int l=tree[x].l,r=tree[x].r,mid=(l+r)>>1;
	tree[x<<1].sum=(mid-l+1)*tree[x].lz;
	tree[x<<1|1].sum=(r-mid)*tree[x].lz;
	tree[x<<1].lz=tree[x].lz;
	tree[x<<1|1].lz=tree[x].lz;
	tree[x].lz=-1;
}
inline void pushup(int x){
	tree[x].sum=tree[x<<1].sum+tree[x<<1|1].sum;
}

inline void build(int now,int l,int r){
	tree[now].l=l;
	tree[now].r=r;
	tree[now].lz=-1;
	if(l==r){
		tree[now].sum=t[l]-'0';
		return;
	}
	int mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
	pushup(now);
}
void update(int now,int l,int r,int ql,int qr,int val){
	if(ql<=l&&qr>=r){
		tree[now].sum=(r-l+1)*val;
		tree[now].lz=val;
		return;
	}
	pushdown(now);
	int mid=(l+r)>>1;
	if(ql<=mid) update(now<<1,l,mid,ql,qr,val);
	if(qr>mid) update(now<<1|1,mid+1,r,ql,qr,val);
	pushup(now);
}
int query(int now,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r) return tree[now].sum;
	pushdown(now);
	int mid=(l+r)>>1,sum=0;
	if(ql<=mid) sum+=query(now<<1,l,mid,ql,qr);
	if(qr>mid) sum+=query(now<<1|1,mid+1,r,ql,qr);
	return sum;
}

inline bool check(){
	for(int i=1;i<=n;i++){
		if(query(1,1,n,i,i)!=s[i]-'0') return 0;
	}
	return 1;
}

inline bool solve(){
	for(int i=m;i>=1;i--){
		int l=a[i],r=b[i];
		int num1=query(1,1,n,l,r),len=r-l+1;
		if(num1*2==len) return 0;
		else if(num1*2<len) update(1,1,n,l,r,0);
		else update(1,1,n,l,r,1);
	}
	if(check()) return 1;
	else return 0;
}

int main(){
	
	int q;
	
	scanf("%d",&q);
	
	while(q--){
		scanf("%d %d",&n,&m);
		scanf("%s %s",s+1,t+1);
		for(int i=1;i<=m;i++) scanf("%d %d",&a[i],&b[i]);
		build(1,1,n);
		if(solve()) puts("YES");
		else puts("NO");
	}
	
	return 0;
}

```


---

## 作者：FutaRimeWoawaSete (赞：1)

简单数据结构。              

我们发现原题要求查询一次，修改一次。这样的操作让人很难下手，毕竟我们不知道要改哪些。               

所以先来找性质，我们不难发现如果我们是先修改区间再查询区间的话，就看 1 和 0 谁多就好了然后区间覆盖，最后判断一下是不是还原成了原序列即可。                 

对于这道题，给定了初状态，又给定了末状态，用常见的 trick 倒序处理，我们不难发现这道题变成了上述的问题，直接模拟就好了。                     

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Len = 1e6 + 5;
int n,m,ans[Len << 2],tag[Len << 2];
char s[Len],ss[Len];
struct node
{
	int l,r;
}Sec[Len];
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x){ans[x] = ans[ls(x)] + ans[rs(x)];}
void push_down(int p,int l,int r)
{
	if(tag[p] != -1)
	{
		int mid = (l + r) >> 1;
		ans[ls(p)] = tag[p] * (mid - l + 1) , tag[ls(p)] = tag[p];
		ans[rs(p)] = tag[p] * (r - mid) , tag[rs(p)] = tag[p];
		tag[p] = -1;
	}
}
void build(int p,int l,int r)
{
	tag[p] = -1;
	if(l == r)
	{
		ans[p] = (ss[l] == '1');
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void update(int p,int l,int r,int nl,int nr,int w)
{
	if(nl <= l && nr >= r)
	{
		ans[p] = (r - l + 1) * w;
		tag[p] = w;
		return;
	}
	push_down(p , l , r);
	int mid = (l + r) >> 1;
	if(nl <= mid) update(ls(p) , l , mid , nl , nr , w);
	if(nr > mid) update(rs(p) , mid + 1 , r , nl , nr , w);
	push_up(p);
}
int query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return ans[p];
	push_down(p , l , r);
	int mid = (l + r) >> 1 , res = 0;
	if(nl <= mid) res += query(ls(p) , l , mid , nl , nr);
	if(nr > mid) res += query(rs(p) , mid + 1 , r , nl , nr);
	return res;
}
bool check()
{
	build(1 , 1 , n);
	for(int i = m ; i >= 1 ; i --) 
	{
		int num = query(1 , 1 , n , Sec[i].l , Sec[i].r);
		if(num * 2 == Sec[i].r - Sec[i].l + 1) return 0;
		if(num * 2 > Sec[i].r - Sec[i].l + 1) update(1 , 1 , n , Sec[i].l , Sec[i].r , 1);
		else update(1 , 1 , n , Sec[i].l , Sec[i].r , 0);
	}
	//query(1 , 1 , n , 3 , 3); 
	for(int i = 1 ; i <= n ; i ++) 
	{
		int sim = s[i] - '0';
		if(query(1 , 1 , n , i , i) != sim) return 0;
	}
	return 1;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t --)
	{
		scanf("%d %d",&n,&m);scanf("%s",s + 1);
		scanf("%s",ss + 1);
		for(int i = 1 ; i <= m ; i ++) scanf("%d %d",&Sec[i].l,&Sec[i].r);
		if(check()) puts("YES");
		else puts("NO");
	}
	return 0;
} 
```

---

## 作者：乘湘去 (赞：1)

#### [更好的阅读体验](https://www.cnblogs.com/isonder/p/14348325.html)

#### 中文题意:

$T$ 组数据

给你两个长度为 $n$ 的01串 $s,f,$有 $q$ 次询问。

每次询问有区间 $[\ l,r\ ]$ ,如果 $[\ l,r\ ]$ 同时包含$0$和$1$，则询问终止，否则你可以改变区间$[\ l,r\ ]$ 内严格小于 $len_{lr}$ 的数字。

问是否可以使得询问不终止，且经过 $q$ 次询问后可以将$s$改为$f$。

#### 前置知识:

###### 线段树

~~没了~~

#### 思路:

发现没法正序推过去(~~反正我不会~~)，考虑根据询问逆推。

那么对于 $f$ ,和 $q_{1},q_{2}$···$q_{n}$ ,用 $l_{i},r_{i}$ 来表示 $q_{i}$ , $s_{i}$表示经过前 $i$ 次询问后的字符串 $s$ 。

对于第 $n$ 次询问，当且仅当 $s_{n-1}$中的 $[l_{n},r_{n}]$ 全为 $k$ ( $k$ $\in$ $(0,1)$ ) ,$f$ 在 $[l_{n},r_{n}]$ 内($k\oplus  1$)的数量$num_{k\oplus  1}$ $<$ $len_{lr}$ 时,

$s_{n-1}$ 可转化 $f$ 。

因此，我们可以对于 $f$ 从 $n$ 开始向前遍历询问。对于 $[l_{i},r_{i}]$ , 将  $[l_{i},r_{i}]$  内数量较少的数字改为另一个数字。

~~显然~~，当 $[l_{i},r_{i}]$ 内 $num_{1} = num_{0}$ 时，询问会终止，因为改变量必须严格小于区间长度的一半。

遍历到最后判断 $s$ 和经过转化的 $f$ 是否相同就行了。

#### 做法:

对于区间，查询和改变问题，我们可以用线段树在 $log\ n$ 的复杂度下解决。

首先对于 $f$ 建立线段树，维护区间内 $1$ 的数量。

对于区间修改，建立  $lazy$  标记，$-1$ 表示不变，$0$ 表示  $lazy$  下的区间全为$0$，$1$ 表示  $lazy$  下的区间全为$1$。

$pusdown$ 操作:
```cpp
inline void pushdown(int p,int l,int r)
{
	if(laz[p]==-1)//未被标记跳过
		return ;
	int mid=(l+r)>>1;
	if(laz[p])//标记为1
	{
		tr[p<<1]=(mid-l+1);
		tr[p<<1|1]=(r-mid);
		laz[p<<1]=laz[p<<1|1]=1;
		laz[p]=-1;
		return ;
	}
	tr[p<<1]=tr[p<<1|1]=0;//标记为0
	laz[p<<1]=laz[p<<1|1]=0;
	laz[p]=-1;
}
```
剩下的就是线段树的基本操作了。

#### Code:
```cpp
#include<bits/stdc++.h>
#define N 240000
using namespace std;
 
int t,n,q;
char s[N],f[N];
int ql[N],qr[N],tr[N<<2],laz[N<<2];
 
inline int read()
{
	char a=0;int w=1,x=0;
	while(a<'0'||a>'9'){if(a=='-')w=-1;a=getchar();}
	while(a<='9'&&a>='0'){x=(x<<3)+(x<<1)+(a^48);a=getchar();}
	return x*w;
}
 
inline void pushdown(int p,int l,int r)
{
	if(laz[p]==-1)//未被标记跳过
		return ;
	int mid=(l+r)>>1;
	if(laz[p])//标记为1
	{
		tr[p<<1]=(mid-l+1);
		tr[p<<1|1]=(r-mid);
		laz[p<<1]=laz[p<<1|1]=1;
		laz[p]=-1;
		return ;
	}
	tr[p<<1]=tr[p<<1|1]=0;//标记为0
	laz[p<<1]=laz[p<<1|1]=0;
	laz[p]=-1;
}
 
void build(int p,int l,int r)//建树
{
	laz[p]=-1;
	if(l==r)
	{
		tr[p]=(f[l]^48);
		return ;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	tr[p]=tr[p<<1]+tr[p<<1|1];
}
 
int que(int p,int l,int r,int L,int R)//查询1的数量
{
	if(L<=l&&r<=R)
		return tr[p];
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	int ans=0;
	if(mid>=L)
		ans+=que(p<<1,l,mid,L,R);
	if(mid<R)
		ans+=que(p<<1|1,mid+1,r,L,R);
	return ans;
}
 
void modify(int p,int l,int r,int L,int R,int opt)//区间修改
{
	if(L<=l&&r<=R)
	{
		tr[p]=opt*(r-l+1);
		laz[p]=opt;
		return ;
	}
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(mid>=L)
		modify(p<<1,l,mid,L,R,opt);
	if(mid<R)
		modify(p<<1|1,mid+1,r,L,R,opt);
	tr[p]=tr[p<<1]+tr[p<<1|1];
}
 
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		q=read();
		int flag=1;
		scanf("%s%s",(s+1),(f+1));
		for(register int i=1;i<=q;i++)
		{
			ql[i]=read();
			qr[i]=read();
		}
		build(1,1,n);
		for(register int i=q;i>=1;i--)
		{
			int len=qr[i]-ql[i]+1;//区间长度
			int num=que(1,1,n,ql[i],qr[i]);//查询区间内1的数量
			if( num==len-num )//区间内0的数量为 len-num , 0和1数量相同时不可能成立
			{
				flag=0;
				break;
			}
			modify(1,1,n,ql[i],qr[i],num>(len-num) );//区间修改
		}
		if(!flag)
		{
			printf("NO\n");
			continue;
		}
		for(register int i=1;i<=n;i++)
		{
			int num=que(1,1,n,i,i);//取出经过q次询问后f的第i位
			if(num!=(s[i]^48))//判断f和s是否相等，不相等退出
			{
				flag=0;
				break;
			}
		}
		if(!flag)
		{
			printf("NO\n");
			continue;
		}
		printf("YES\n");
	}
	return 0;
}
```


---

## 作者：_EternalRegrets_ (赞：0)

### 题意描述 
> 有一个二进制字符串，小 B 在第 $i$ 天早上会检查字符串的某一个区间 $[l_i,r_i]$，查看区间内的数字是否全为 $1$ 或 $0$，如果是，他会感到开心，否则他会感到不开心。小 A 可以在当天晚上更改区间 $[l_i,r_i]$ 的个数 **严格小于** 区间长的一半的数字，尽可能使得下一天早上小B感到开心。求小 A 是否可以让小 B 每天都感到开心。

### Solution:
正难则反。

注意到如果把修改和查看操作顺序倒过来，修改方式是唯一的。

所以我们就可以尝试将整个题倒过来做，将已经被检查的区间中的数字全部改为数量更多的那一个。（如果数量相同，则无法完成任务）

可以比较容易地看出只需要执行区间查询与区间覆盖操作，即线段树板子。

### Code：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct tree{
	int val,tag;
};

struct node{
	int l,r;
};

node opt[200005];
tree tr[800005];
int s[200005];
int f[200005];

void build(int id,int L,int R){
	tr[id].tag=-1;
	if(L==R){
		tr[id].val=f[L];
		return;
	}
	
	int mid; mid=(L+R)>>1;
	build(id*2,L,mid);
	build(id*2+1,mid+1,R);
	
	tr[id].val=tr[id*2].val+tr[id*2+1].val;
}

void modify(int id,int L,int R,int l,int r,int delta){
	//cout<<id<<" "<<L<<" "<<R<<" "<<l<<" "<<r<<endl; 
	if(L==l && R==r){
		tr[id].val=(R-L+1)*delta;
		tr[id].tag=delta;
		return;
	}
	int mid; mid=(L+R)>>1; //cout<<L<<" "<<R<<" "<<mid<<endl;
	
	if(tr[id].tag!=-1){
		tr[id*2].tag=tr[id].tag;
		tr[id*2+1].tag=tr[id].tag;
		tr[id*2].val=(mid-L+1)*tr[id].tag;
		tr[id*2+1].val=(R-mid)*tr[id].tag;
		tr[id].tag=-1;
	}
	
	if(mid>=r){
		modify(id*2,L,mid,l,r,delta);
	}
	else if(mid<l){
		modify(id*2+1,mid+1,R,l,r,delta);
	}
	else{
		modify(id*2,L,mid,l,mid,delta);
		modify(id*2+1,mid+1,R,mid+1,r,delta);
	}
	
	tr[id].val=tr[id*2].val+tr[id*2+1].val;
}

int countOne(int id,int L,int R,int l,int r){
	if(L==l && R==r){
		return tr[id].val;
	}
	
	int mid; mid=(L+R)>>1;
	if(tr[id].tag!=-1){
		tr[id*2].tag=tr[id].tag;
		tr[id*2+1].tag=tr[id].tag;
		tr[id*2].val=(mid-L+1)*tr[id].tag;
		tr[id*2+1].val=(R-mid)*tr[id].tag;
		tr[id].tag=-1;
	}
	
	int ret; ret=0;
	if(mid>=r){
		ret+=countOne(id*2,L,mid,l,r);
	}
	else if(mid<l){
		ret+=countOne(id*2+1,mid+1,R,l,r);
	}
	else{
		ret+=countOne(id*2,L,mid,l,mid)+countOne(id*2+1,mid+1,R,mid+1,r);
	}
	
	return ret;
}

void outputTree(int n){
	for(int i=1;i<=n;i++){
		cout<<countOne(1,1,n,i,i);
	}
	cout<<endl;
}

signed main(){
	int T; cin>>T;
	
	while(T--){
		int n,q; cin>>n>>q;
		for(int i=1;i<=n;i++){
			char c; cin>>c;
			s[i]=c-'0';
		}
		
		for(int i=1;i<=n;i++){
			char c; cin>>c;
			f[i]=c-'0';
		}
		
		build(1,1,n);
		//cout<<"build:";
		//outputTree(n);
		 
		for(int i=1;i<=q;i++){
			int l,r; cin>>l>>r;
			opt[i]={l,r};
		}
		
		reverse(opt+1,opt+1+q);
		
        int f; f=0;
		for(int i=1;i<=q;i++){
		//	outputTree(n);
			int l,r; l=opt[i].l,r=opt[i].r;
			int numOne; numOne=countOne(1,1,n,l,r);
			int numZero; numZero=r-l+1-numOne;
			
			if(numOne==numZero){
                f=1;
				break;
			} 
			else if(numOne>numZero){
				modify(1,1,n,l,r,1);
			}
			else{
				modify(1,1,n,l,r,0);
			}
		} 
		
		for(int i=1;i<=n;i++){
		//	cout<<i<<" "<<countOne(1,1,n,i,i)<<" "<<s[i]<<endl; 
			if(countOne(1,1,n,i,i)!=s[i] || f==1){
				f=1;
				break;
			} 
		}
		
		if(f){
			cout<<"NO\n";
		}
		else{
			cout<<"YES\n";
		}
	}
	
	return 0;
} 
```

### 附录：

[AC记录](https://codeforces.com/problemset/submission/1477/307934833)

---

## 作者：DrAlfred (赞：0)

摘要：线段树，时光回溯

[传送门：https://www.luogu.com.cn/problem/CF1477B](https://www.luogu.com.cn/problem/CF1477B)

## 题意

给你两个二进制字符串 $s, t$。$q$ 次操作，每次给定一个区间 $[l, r]$，查询 $s_l, s_{l + 1}, \dots, s_r$ 是否都相等。然后你可以修改这个区间里面 **严格小于区间长度一半个** 字符，来影响下一次操作的检查操作。问若干次操作之后能否从字符串 $s$ 变成 $t$。 

## 分析思路

这题比较符合自觉的做法是试图每次在 $s$ 的基础上修改，尽量往 $t$ 上靠。然而这样做没有办法每次确定给一个明确具体的策略，看似不可做，怎么办？

注意到如果存在一种合法的操作方法能从 $s$ 变成 $t$，那么一定也可以从 $t$ 变成 $s$，只不过我们允许先修改，再查询。

于是策略变得明朗：我们以 $t$ 为初始状态，倒着处理询问。如果当前这段区间 $1$ 多，**由于操作之后我们一定要能通过检查**，事实上我们只能把全部的 $0$ 改成 $1$。如果区间 $0$ 多同理。如果一样多，那就不行。实际上我们是没有任何选择地进行操作。最后检查终止状态是否为 $s$ 即可。

于是我们用线段树维护区间和，区间推平，时间复杂度 $O(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
struct Node {
    int l, r, lazy, sum;
    inline int mid(void) { return (l + r) >> 1; }
    inline void assign(int x) {
        lazy = x, sum = (r - l + 1) * x;
    }
} tr[N << 2];
int t, n, q, l[N], r[N], s[N], f[N];
inline int ls(int p) { return p << 1; }
inline int rs(int p) { return p << 1 | 1; }
inline void pushdown(int p) {
    if (tr[p].lazy != -1) {
        tr[ls(p)].assign(tr[p].lazy);
        tr[rs(p)].assign(tr[p].lazy);
        tr[p].lazy = -1;
    }
}
inline void build(int p, int l, int r) {
    tr[p] = {l, r, -1, 0};
    if (l == r) {
        tr[p].sum = f[l];
    } else {
        const int m = (l + r) >> 1;
        build(ls(p), l, m), build(rs(p), m + 1, r);
        tr[p].sum = tr[ls(p)].sum + tr[rs(p)].sum;
    }
}
inline void modify(int p, int l, int r, int v) {
    if (l <= tr[p].l && tr[p].r <= r) {
        return tr[p].assign(v);
    }
    pushdown(p);
    if (l <= tr[p].mid()) modify(ls(p), l, r, v);
    if (r > tr[p].mid()) modify(rs(p), l, r, v);
    tr[p].sum = tr[ls(p)].sum + tr[rs(p)].sum;
}
inline int query(int p, int l, int r) {
    if (l <= tr[p].l && tr[p].r <= r) {
        return tr[p].sum;
    }
    pushdown(p);
    int m = tr[p].mid(), ans = 0;
    if (l <= m) ans += query(ls(p), l, r);
    if (r > m) ans += query(rs(p), l, r);
    return ans;
}
inline void solve(void) {
    char c;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> c, s[i] = c ^ 48;
    for (int i = 1; i <= n; i++) cin >> c, f[i] = c ^ 48;
    for (int i = 1; i <= q; i++) {
        cin >> l[i] >> r[i];
    }
    build(1, 1, n);
    for (int i = q; i >= 1; i--) {
        int one = query(1, l[i], r[i]);
        int zero = r[i] - l[i] + 1 - one;
        if (zero > one) {
            modify(1, l[i], r[i], 0);
        } else if (zero == one) {
            cout << "NO\n";
            return;
        } else {
            modify(1, l[i], r[i], 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (query(1, i, i) != s[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：AK_400 (赞：0)

题目要求先判断是否一样，再修改，这很困难，但是发现如果把这两个操作倒过来，那么修改是唯一的（只能改不超过一半的数，即将出现次数多的赋值到整段）。于是我们把操作离线下来，从后往前操作，最后判断能否把 $f$ 操作成 $s$ 即可。

区间赋值，区间求和，可以线段树维护。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
string s,f;
#define ls (p<<1)
#define rs (p<<1|1)
#define mid (l+r>>1)
int sum[800005],lz[800005],sz[800005];
void pu(int p){
    sum[p]=sum[ls]+sum[rs];
}
void bd(int l,int r,int p){
    lz[p]=2;
    sz[p]=r-l+1;
    if(l==r){
        sum[p]=f[l]-'0';
        return;
    }
    bd(l,mid,ls),bd(mid+1,r,rs);
    pu(p);
}
void pd(int p){
    if(lz[p]==2)return;
    lz[ls]=lz[rs]=lz[p];
    sum[ls]=lz[p]*sz[ls];
    sum[rs]=lz[p]*sz[rs];
    lz[p]=2;
}
void upd(int l,int r,int ml,int mr,int x,int p){
    if(ml<=l&&r<=mr){
        sum[p]=x*sz[p];
        lz[p]=x;
        return;
    }
    pd(p);
    if(mid>=ml)upd(l,mid,ml,mr,x,ls);
    if(mid<mr)upd(mid+1,r,ml,mr,x,rs);
    pu(p);
}
int qu(int l,int r,int ml,int mr,int p){
    if(ml<=l&&r<=mr)return sum[p];
    pd(p);
    int res=0;
    if(mid>=ml)res+=qu(l,mid,ml,mr,ls);
    if(mid<mr)res+=qu(mid+1,r,ml,mr,rs);
    return res;
}
int l[200005],r[200005];
void slv(){
    cin>>n>>q>>s>>f;
    f=' '+f;
    s=' '+s;
    for(int i=1;i<=q;i++)cin>>l[i]>>r[i];
    bd(1,n,1);
    for(int i=q;i>=1;i--){
        if((r[i]-l[i]+1)%2==0&&qu(1,n,l[i],r[i],1)==(r[i]-l[i]+1)/2){//注意01出现次数一样时无解。
            cout<<"NO"<<endl;
            return;
        }
        if(qu(1,n,l[i],r[i],1)<=(r[i]-l[i]+1)/2){
            upd(1,n,l[i],r[i],0,1);
        }
        else{
            upd(1,n,l[i],r[i],1,1);
        }
    }
    for(int i=1;i<=n;i++){
        if(qu(1,n,i,i,1)!=s[i]-'0'){
            cout<<"NO"<<endl;
            return;
        }
    }
    cout<<"YES"<<endl;
}
signed main(){
    int T;
    cin>>T;
    while(T--)
    slv();
    return 0;
}
```

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

给两个串，对于第一个重复做 $q$ 次查询、修改，使得每次查询区间内元素都一样，问最后是否能改为另一个串。

### 题目分析

我们考虑对于每次修改，都有很多种修改的可能操作，我们不知道哪种最后能改到目标串，所以我们不妨从目标串开始改，改到原始串。

所以我们的操作就变为了先修改一段，然后再查询这一段，最后是否能改为原始串，我们知道为满足查询时元素一样，我们修改时的操作是唯一的，及原来 $0/1$ 个数小于区间长一半的改变，因为严格小于一半，所以是唯一的。然后就变成了线段树板子，区间查询、区间覆盖。

### code
```cpp
#include <iostream>
#include <cstdio>
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls+1)

using namespace std;

const int N = 2e5 + 5, M = 8e5 + 5;
int T, n, q, t[M], tag[M], l[N], r[N];
string a, b;

void push_up(int p){t[p] = t[ls] + t[rs];}
void push_down(int p, int l, int r)
{
    if(tag[p] == -1)    return ;
    t[ls] = tag[p] * (mid - l + 1), tag[ls] = tag[p];
    t[rs] = tag[p] * (r - mid), tag[rs] = tag[p];
    tag[p] = -1;
}

void build(int p, int l, int r)
{
    tag[p] = -1;
    if(l == r)
    {
        t[p] = b[l] - '0';
        return ;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    push_up(p);
}

void update(int p, int l, int r, int ll, int rr, int val)
{
    if(ll <= l && r <= rr)
    {
        tag[p] = val;
        t[p] = val * (r - l + 1);
        return ;
    }
    push_down(p, l, r);
    if(ll <= mid)   update(ls, l, mid, ll, rr, val);
    if(rr > mid)    update(rs, mid + 1, r, ll, rr, val);
    push_up(p);
}

int query(int p, int l, int r, int ll, int rr)
{
    if(ll <= l && r <= rr)
        return t[p];
    int res = 0;push_down(p, l, r);
    if(ll <= mid)   res += query(ls, l, mid, ll, rr);
    if(rr > mid)    res += query(rs, mid + 1, r, ll, rr);
    return res;
}

bool solve()
{
    scanf("%d %d", &n, &q);
    cin >> a >> b;a = "#" + a, b = "#" + b;
    for(int i = 1;i <= q;i++)   scanf("%d %d", &l[i], &r[i]);
    build(1, 1, n);
    for(int i = q;i >= 1;i--)
    {
        int sum = query(1, 1, n, l[i], r[i]);
        if(sum + sum == r[i] - l[i] + 1)    return false;
        if(sum + sum < r[i] - l[i] + 1)
            update(1, 1, n, l[i], r[i], 0);
        else
            update(1, 1, n, l[i], r[i], 1);
    }
    for(int i = 1;i <= n;i++)
        if(query(1, 1, n, i, i) != a[i] - '0')  return false;
    return true;
}

int main()
{
    scanf("%d", &T);
    while(T--)  puts(solve() ? "YES" : "NO");
    return 0;
}

```

---

## 作者：K0stlin (赞：0)

对于每次修改我们发现很头疼，因为可能对后面多个操作都有影响，就好像从决策树的根向下走。于是我们想到从叶子往上走只有一条路，很方便，即**倒着做**。

现在就变成每次检查前修改一次，修改后必须满足条件（全是0或1）。

什么时候无解呢？修改前发现区间里恰好一半是0，一半是1。

有解则将区间内0或1中出现次数较少的改成较多的。

那么我们要支持什么操作？区间查询，区间染色。

线段树就行了。

代码（ $O(nlogn)$ ）：
```cpp
#include <cstdio>
typedef long long ll;
const int N=2e5+5;
int t,n,k,x[N],y[N];
int sum[N<<2][2],tag[N<<2];
char c1[N],c2[N];
struct node {
	int x,y;
	node operator +(const node &w)const {
		return (node){x+w.x,y+w.y};
	}
}now;
inline int read() {
	int x=0,flag=0;char ch=getchar();
	while(ch<'0'||ch>'9'){flag|=(ch=='-');ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return flag?-x:x;
}
inline int mx(int x,int y) {return x>y?x:y;}
inline int mn(int x,int y) {return x<y?x:y;}
 
inline void pu(int ht) {
	sum[ht][0]=sum[ht<<1][0]+sum[ht<<1|1][0];
	sum[ht][1]=sum[ht<<1][1]+sum[ht<<1|1][1];
}
void build(int l,int r,int ht) {
	tag[ht]=-1;
	if(l==r) {
		sum[ht][c2[l]-'0']=1;
		sum[ht][!(c2[l]-'0')]=0;
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,ht<<1);
	build(mid+1,r,ht<<1|1);
	pu(ht);
}
inline void pd(int ht,int ln,int rn) {
	if(tag[ht]!=-1) {
		tag[ht<<1]=tag[ht<<1|1]=tag[ht];
		sum[ht<<1][tag[ht]]=ln;
		sum[ht<<1][!tag[ht]]=0;
		sum[ht<<1|1][tag[ht]]=rn;
		sum[ht<<1|1][!tag[ht]]=0;
		tag[ht]=-1;
	}
}
void update(int l,int r,int ht,int x,int y,int s) {
	if(x<=l&&r<=y) {
		tag[ht]=s;
		sum[ht][s]=r-l+1;
		sum[ht][!s]=0;
		return ;
	}
	int mid=(l+r)>>1;
	pd(ht,mid-l+1,r-mid);
	if(x<=mid) update(l,mid,ht<<1,x,y,s);
	if(y>mid)  update(mid+1,r,ht<<1|1,x,y,s);
	pu(ht);
}
node query(int l,int r,int ht,int x,int y) {
	if(x<=l&&r<=y) return (node){sum[ht][0],sum[ht][1]};
	int mid=(l+r)>>1;
	pd(ht,mid-l+1,r-mid);
	if(x<=mid) {
		if(y>mid) return query(l,mid,ht<<1,x,y)+query(mid+1,r,ht<<1|1,x,y);
		else return query(l,mid,ht<<1,x,y);
	}
	else return query(mid+1,r,ht<<1|1,x,y);
}
bool ch(int l,int r,int ht) {
	if(l==r) {
		if((sum[ht][0]==1&&c1[l]=='0')||(sum[ht][1]==1&&c1[l]=='1')) return 1;
		else return 0;
	}
	int mid=(l+r)>>1;
	pd(ht,mid-l+1,r-mid);
	return ch(l,mid,ht<<1)&ch(mid+1,r,ht<<1|1);
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	t=read();
	while(t--) {
		n=read();k=read();
		scanf("%s\n%s",c1+1,c2+1);
		build(1,n,1);
		for(int i=1;i<=k;++i)
			x[i]=read(),y[i]=read();
		bool flag=1;
		for(int i=k;i>=1;--i) {
			now=query(1,n,1,x[i],y[i]);
			if(now.x==now.y) {
				flag=0;
				break;
			}
			if(now.x<now.y) update(1,n,1,x[i],y[i],1);
			else update(1,n,1,x[i],y[i],0);
		}
		if(flag&&ch(1,n,1)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```
-完-

---

