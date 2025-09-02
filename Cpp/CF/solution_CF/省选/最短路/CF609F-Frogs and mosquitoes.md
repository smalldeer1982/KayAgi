# Frogs and mosquitoes

## 题目描述

There are $ n $ frogs sitting on the coordinate axis $ Ox $ . For each frog two values $ x_{i},t_{i} $ are known — the position and the initial length of the tongue of the $ i $ -th frog (it is guaranteed that all positions $ x_{i} $ are different). $ m $ mosquitoes one by one are landing to the coordinate axis. For each mosquito two values are known $ p_{j} $ — the coordinate of the position where the $ j $ -th mosquito lands and $ b_{j} $ — the size of the $ j $ -th mosquito. Frogs and mosquitoes are represented as points on the coordinate axis.

The frog can eat mosquito if mosquito is in the same position with the frog or to the right, and the distance between them is not greater than the length of the tongue of the frog.

If at some moment several frogs can eat a mosquito the leftmost frog will eat it (with minimal $ x_{i} $ ). After eating a mosquito the length of the tongue of a frog increases with the value of the size of eaten mosquito. It's possible that after it the frog will be able to eat some other mosquitoes (the frog should eat them in this case).

For each frog print two values — the number of eaten mosquitoes and the length of the tongue after landing all mosquitoes and after eating all possible mosquitoes by frogs.

Each mosquito is landing to the coordinate axis only after frogs eat all possible mosquitoes landed before. Mosquitoes are given in order of their landing to the coordinate axis.

## 样例 #1

### 输入

```
4 6
10 2
15 0
6 1
0 1
110 10
1 1
6 0
15 10
14 100
12 2
```

### 输出

```
3 114
1 10
1 1
1 2
```

## 样例 #2

### 输入

```
1 2
10 2
20 2
12 1
```

### 输出

```
1 3
```

# 题解

## 作者：hxhhxh (赞：8)

upd on 2024.4.17：原来的代码复杂度是错的，现在已经改正了。增加了对青蛙的维护的说明。

## 大意

在坐标轴上有 $ n $ 个青蛙，每一只青蛙都有一个可以吃蚊子的区间 $[x_i,x_i+t_i]$($x_i$ 互不相同)，有 $m$ 只蚊子，每一只蚊子依次降落在 $p_i$，最靠左的能吃到它的青蛙会吃了它，并使其 $t_i$ 增加蚊子的参数 $b_i$ 。蚊子不被吃掉时会停留在原位。

求每一只青蛙最终的 $t_i$ 和吃到蚊子的数量。

## 思路

如果 $x_i<x_j$ ，并且 $ x_i+t_i\geq x_j+t_j $，那么青蛙 $j$ 就永远无论如何都吃不到蚊子了。

我们可以按 $x_i+t_i$ 排序，去掉这些吃不到蚊子的青蛙，那么这些青蛙的 $x_i$ 就是单调递增的。

有一只蚊子降落下来了。这时候我们可以在青蛙中二分最左的右端大于蚊子位置的青蛙，如果这只青蛙可以吃到，那么这只青蛙就会吃到这只蚊子，否则这只蚊子将停留在这里。

如果这只蚊子停留在原地，我们可以用一个 `multiset` 存起来，方便以后的查找。

如果找到了吃到这只蚊子的青蛙（设它的编号为 $i$）， $t_i$ 就会增加，**就有可能吃到更多的蚊子**，所以还需要单独对这只青蛙查找能吃到的蚊子，注意要一个个地找，找完之后增加 $t_i$ 然后重复过程。查找的方法是用 `multiset` 自带的 `lower_bound`，找在左端点右的最左蚊子。

当找完之后没有剩下的蚊子可以吃后，要清除吃不到蚊子的青蛙，不然可能对二分产生影响。这样的青蛙（设为 $j$）有 $x_j+t_j\leq x_i+y_i$，$x_j\geq x_i$。由于我们是按照 $x_j+t_j$ 排序的，所以这样的青蛙只可能在 $i$ 的前面。

注意，使用 `vector` 存青蛙并每次 `erase` 掉吃不到蚊子的青蛙的时间复杂度是错误的。这是因为，`vector` 的 `erase` 函数的时间复杂度是 $O(size)$ 的，而 $size$ 可以轻松达到 $O(n)$，从而时间复杂度为 $O(n^2)$。应该使用 `multiset` 维护每个青蛙。

## 代码

为了方便，代码里有 $l_i=x_i,r_i=x_i+t_i$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ansc[200005],ansv[200005];
struct st{
	int l,r,id;
	bool operator<(const st&re)const{
		return r==re.r?l<re.l:r<re.r;
	}
}a[200005];
multiset<pair<int,int> >p;
multiset<st>s;
void upd(st v){
	s.insert(v);
	auto x=s.lower_bound(v);
	while(x!=s.begin()){
		auto o=prev(x);
		if(o->l>=v.l&&o->r<=v.r) s.erase(o);
		else break;
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%lld %lld",&a[i].l,&a[i].r),ansv[i]=a[i].r,a[i].r+=a[i].l,a[i].id=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) upd(a[i]);
	for(int i=1,x,v;i<=m;i++){
		scanf("%lld %lld",&x,&v);
		auto t=s.lower_bound((st){0,x,0});
		if(t==s.end()) p.insert({x,v});
		else if(t->l>x) p.insert({x,v});
		else{
			int px=t->id,pl=t->l,pr=t->r;
			pr+=v,ansc[px]++,ansv[px]+=v;
			while(1){
				auto to=p.lower_bound({pl,0});
				if(to==p.end()) break;
				if(to->first>pr) break;
				pr+=to->second,ansc[px]++,ansv[px]+=to->second;
				p.erase(to);
			}
			s.erase(t);
			upd((st){pl,pr,px});
		}
	}
	for(int i=1;i<=n;i++) printf("%lld %lld\n",ansc[i],ansv[i]);
}
```

---

## 作者：StayAlone (赞：5)

作为一道一遍过的紫题，写篇题解纪念一下。

### 题意

有 $n$ 只青蛙，第 $i$ 只青蛙可以吃到 $[x_i, x_i + l_i]$ 区间内的所有蚊子。每个蚊子会被所有能吃掉它的青蛙中 $x_i$ 最小的那只青蛙吃掉。每个蚊子还带有一个属性 $t_i$，表示如果这只蚊子被吃掉，吃掉它的青蛙的 $l_i$ 会加上 $t_i$。每一时刻，当且仅当没有蚊子能被吃掉或所有蚊子都被吃掉时，下一只蚊子才会出现。问每一只青蛙吃了几只蚊子，最后的 $l_i$ 为多少。  

$x_i$ 互不相同。

### 思路  

首先离散化 $x_i$，维护一棵线段树，维护离散化后的 $\max\limits_{i = l}^{r}\{x_i + l_i\}$。查找 $p$ 能被哪只青蛙吃掉时，使用类似线段树二分的做法：

- 若左边维护的值大于等于 $p$，往左走
- 反之，往右走。  

其实这里也是一个贪心：如果往左边走只能走到一个 $x_i > p$ 的点，表示往右边走一定不会出现 $x_i \leqslant p$ 的情况。如果走到了一个叶子节点但是不和条件，说明这只蚊子暂时不能被吃。

接下来就是处理暂时不能被吃的蚊子。把它们放在一个可重集内，每一次如果有青蛙吃了蚊子，就去看看它能不能吃掉某些集合里的旧蚊子。直接 while 循环 lower_bound 查找，能吃就吃即可。  

排序有一次，每只蚊子只会进入集合一次，所有青蛙最多一共更改 $m$ 次，所以时间复杂度是 $O(n\log n + m\log m + m\log n)$。$n, m$ 是同一级别的，所以近似看成 $O(n\log n)$。  

[AC code 记录](https://www.luogu.com.cn/record/70050929)
```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define ......
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 2e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc
{
	template <typename T>
	il void read(T &x)

    il int read()
    
	template <typename T, typename ...L>
	il void read(T &x, L &...y)

	template <typename T>
	il void write(T x)


	template <typename T>
	il T my_max(const T &x, const T &y)
}
using namespace stupid_lrc;
// 奇妙缺省源
int n, m, pre[MAXN], x[MAXN], p[MAXN], b[MAXN], ate[MAXN], uni[MAXN];
ll len[MAXN]; pii nuf[MAXN];
multiset <pii> mt;

struct setr
{
	ll mx;
} t[MAXN << 2];

il void pushup(int x)
{
	t[x].mx = my_max(t[ls(x)].mx, t[rs(x)].mx);
}

il void build(int rt, int l, int r)
{
	if (l == r) return t[rt].mx = x[pre[l]] + len[pre[l]], void();
	int mid = l + r >> 1;
	build(ls(rt), l, mid); build(rs(rt), mid + 1, r);
	pushup(rt);
}

il void upd(int rt, int l, int r, int k, int del) // 第 k 只青蛙的 t 增加 del
{
	if (r < k || l > k) return;
	if (l == r && r == k) return len[pre[l]] += del, t[rt].mx += del, void();
	int mid = l + r >> 1;
	upd(ls(rt), l, mid, k, del); upd(rs(rt), mid + 1, r, k, del);
	pushup(rt);
}

il int wc(int rt, int l, int r, int pos) // 找到最左侧的能吃位置在 pos 的蚊子的青蛙
{
	if (l == r) return x[pre[l]] <= pos && x[pre[l]] + len[pre[l]] >= pos ? pre[l] : -1;
	int mid = l + r >> 1;
	if (pos <= t[ls(rt)].mx) return wc(ls(rt), l, mid, pos);
	return wc(rs(rt), mid + 1, r, pos);
}

il int get(int x)
{
	return lower_bound(nuf + 1, nuf + 1 + n, mp(x, -1)) - nuf;
}

int main()
{
	read(n, m);
	rep1(i, 1, n) read(x[i], len[i]), nuf[i] = mp(x[i], i);
	sort(nuf + 1, nuf + 1 + n);
	rep1(i, 1, n) pre[i] = nuf[i].snd;
	build(1, 1, n);
	rep1(i, 1, m)
	{
		read(p[i], b[i]); int eat = wc(1, 1, n, p[i]);
		if (!~eat)
		{
			mt.insert(mp(p[i], b[i]));
			continue;
		}
		upd(1, 1, n, get(x[eat]), b[i]); ate[eat]++;
		
		auto it = mt.lower_bound(mp(x[eat], -1));
		while (it != mt.end() && (*it).fst <= x[eat] + len[eat])
		{
			upd(1, 1, n, get(x[eat]), (*it).snd);
			ate[eat]++; mt.erase(it);
			it = mt.lower_bound(mp(x[eat], -1));
		}
	}
	rep1(i, 1, n) write(ate[i], ' '), write(len[i], '\n');
	rout;
}
```

---

## 作者：Dilute (赞：5)

[$$\huge\texttt{在本人blog食用更佳}$$](https://dilute.xyz/2019/04/22/Solutions/Solution-CF609F/)

## set​瞎搞

#### 预处理

我们考虑一下，一只青蛙能够影响的区间是什么

我们发现，如果将每只青蛙能够吃到的文字区间$[l, r]$按照左端点$l$排序，然后把后面的区间和前面的区间的重复部分去掉，那么就可以得到一个青蛙真正可以吃到的蚊子的范围区间

我觉得下面这张图讲的很清楚w

![](http://dilute.xyz/images/2.png)

好，那么我们的预处理就这么完了。

#### 加入蚊子

我们采用$set$维护所有青蛙能够真正吃到的蚊子的范围区间，那么在加入一只蚊子的时候，可以lower\_bound快速求出这只蚊子会不会被吃掉，如果它被吃掉了，是被哪只青蛙吃掉了。

显然，如果一只蚊子被吃掉了，那么吃掉它的哪只青蛙和其他青蛙可以吃到的蚊子的范围区间都会变化，那么我们只要从当前更新过的哪只青蛙的范围向后找，把所有被当前区间所包含的区间全都删除，最后再调整一下没有被完全覆盖的区间的左端点。

#### 还有一点

这道题有一个非常恶心的设定：蚊子如果没有被吃掉，它会待在原地，直到被某只青蛙吃掉为止。

这让我们再用一个$set$维护当前没有被吃掉的蚊子，然后在前面吃掉一只蚊子，区间变长的时候，在储存蚊子的那个$set$里面lower_bound一下判断是否能够再吃掉其他的蚊子，等确定没有蚊子可吃的时候再去判断后面的区间是否被更新。

#### 代码

我实现的丑的要命，反正跑得过去就行，轻喷...

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

struct Node{
    int l;
    int r;
    int id;
    bool operator < (const Node &b) const {
        if(l == b.l)
            return r > b.r;
        return l < b.l;
    }
};
std::set<Node> s;
std::multiset<std::pair<int, int> > s2;
int ans[200010], x[200010], t[200010], p[200010], b[200010];

std::set<Node>::iterator operator + (std::set<Node>::iterator it, const int &b){
    it++;
    return it;
}

std::set<Node>::iterator operator - (std::set<Node>::iterator it, const int &b){
    it--;
    return it;
}
int id[200010];

bool cmp(int a, int b){
    return x[a] < x[b];
}

int main(){
    int n = inp();
    int m = inp();
    for(int i = 1; i <= n; i++){
        x[i] = inp();
        t[i] = inp();
        id[i] = i;
    }
    std::sort(id + 1, id + n + 1, cmp);
    s.insert((Node){x[id[1]], x[id[1]] + t[id[1]], id[1]});
    for(int i = 2; i <= n; i++)
        if(std::max(s.rbegin()->r + 1, x[id[i]]) <= x[id[i]] + t[id[i]])
            s.insert((Node){std::max(s.rbegin()->r + 1, x[id[i]]), x[id[i]] + t[id[i]], id[i]});
    for(int i = 1; i <= m; i++){
        p[i] = inp();
        b[i] = inp();
        std::set<Node>::iterator it = s.upper_bound((Node){p[i], p[i]});
        it--;
        if(it->r >= p[i] && it->l <= p[i]){
            t[it->id] += b[i];
            ans[it->id]++;
            Node nxt = *it;
            s.erase(it);
            s.insert((Node){nxt.l, nxt.r + b[i], nxt.id});
            it = s.find((Node){nxt.l, nxt.r + b[i], nxt.id});
            std::multiset<std::pair<int, int> >::iterator it2 = s2.lower_bound(std::make_pair(it->l, 1));
            while(it2 != s2.end() && it2->first <= it->r){
                t[it->id] += it2->second;
                ans[it->id]++;
                Node nxt = *it;
                s.erase(it);
                s.insert((Node){nxt.l, nxt.r + it2->second, nxt.id});
                it = s.find((Node){nxt.l, nxt.r + it2->second, nxt.id});
                s2.erase(it2);
                it2 = s2.lower_bound(std::make_pair(it->l, 1));
            }
            while((it + 1) != s.end() && it->r >= (it + 1)->r)
                s.erase(it + 1);
            if((it + 1) != s.end()){
                Node nxt = *(it + 1);
                s.erase(it + 1);
                s.insert((Node){std::max(nxt.l, it->r + 1), nxt.r, nxt.id});
            }
        } else
            s2.insert(std::make_pair(p[i], b[i]));
    }
    for(int i = 1; i <= n; i++)
        printf("%d %d\n", ans[i], t[i]);
}
```



---

## 作者：幻影星坚强 (赞：3)

对于每只青蛙离散化后扔线段树上，权值为能到达的最远处。然后我们发现max（$a_1$~$a_i$）是单调递增的，所以可以二分，然后就可以找到每个蚊子能被吃到的最左边的青蛙。

不会被吃到的扔set里，然后当某只青蛙舌头变长了再将set里能被吃掉的全吃掉（重复进行找到能被吃掉的最小的p将它吃掉的操作）。

因为我set属于普及-水平（甚至清空变量填的是权值还调了半天）所以选择了降维，可以被hack，但比较幸运没被hack，不会set的大概可以参考一下。或者改成二维

```
#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
const int N = 2e5 + 10;
int n, m;
int tree[N << 2], maxs[N << 2];
int x[N], t[N], p[N], b[N], num[N];
multiset<long long>s;
void opt1(int o, int l, int r, int i, int x)
{
	if(l == r)
	{
		maxs[o] = x;
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= i)opt1(o << 1, l, mid, i, x);
	else opt1(o << 1 | 1, mid + 1, r, i, x);
	maxs[o] = max(maxs[o << 1], maxs[o << 1 | 1]);
}
bool opt2(int o, int l, int r, int L, int R, int x)
{
	//printf("%d\n", o);
	if(l >= L && r <= R)
	{
		return maxs[o] >= x;
	}
	int mid = (l + r) >> 1, ans = 0;
	if(mid >= L) ans |= opt2(o << 1, l, mid, L, R, x);
	if(mid < R)  ans |= opt2(o << 1 | 1, mid + 1, r, L, R, x);
	return ans;
}
bool pd(int i, int j)
{
	return x[i] < x[j];
}
int ans[N], dy[N];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i)
	{
		scanf("%d%d", &x[i], &t[i]);
		num[i] = i;
	}
	for (int i = 1; i <= m; ++ i)
	{
		scanf("%d%d", &p[i], &b[i]);
	}
	sort(num + 1, num + 1 + n, pd);
	for (int i = 1; i <= n; ++ i)
	{
		opt1(1, 1, n, i, x[num[i]] + t[num[i]]);
	}
	long long y;
	y = 9223372036854775800;
	s.insert(y);
	for (int i = 1; i <= m; ++ i)
	{
		int l = 1, r = n;
		for(; l < r;)
		{
			int mid = (l + r) >> 1;
			if(x[num[mid]] > p[i]) r = mid;
			else l = mid + 1;
		}
		while(x[num[r]] > p[i]) -- r;
		l = 1;
		if(r < 1 || !opt2(1, 1, n, 1, r, p[i]))
		{
			s.insert((long long)p[i] * 1000000000LL + (long long)b[i]);
			continue;
		}
		for(; l < r;)
		{
			int mid = (l + r) >> 1;
			if(opt2(1, 1, n, 1, mid, p[i]))r = mid;
			else l = mid + 1;
		}
		while(l <= n && !opt2(1, 1, n, 1, l, p[i])) ++ l;
		while(l > 1 && opt2(1, 1, n, l - 1, l - 1, p[i])) -- l;
		++ ans[num[l]];
		t[num[l]] += b[i];
		opt1(1, 1, n, l, x[num[l]] + t[num[l]]);
		while(!s.empty())
		{
			long long y;
			y = (long long)x[num[l]] * 1000000000LL;
			__typeof(s.begin()) i = s.lower_bound(y);
			y = *i;
			if(y / 1000000000LL <= (long long)(x[num[l]] + t[num[l]]))
			{
				++ ans[num[l]];
				s.erase(i);
				t[num[l]] += (int)(y % 1000000000LL);
			}
			else
			break;
		}
		opt1(1, 1, n, l, x[num[l]] + t[num[l]]);
	}
	for (int i = 1; i <= n; ++ i)
	{
		printf("%d %d\n", ans[i], t[i]);
	}
}
```


---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]CF609F%20Frogs%20and%20mosquitoes)

# 思路

发现 $x$ 对题目的限制较大，因此考虑先将 $x$ 排序并离散化后再来考虑。

不难用线段树维护 $\max_{i = l}^{r}\{x_i + len_i\}$，这样我们就可以利用类似线段树上二分的技巧得出是哪一只青蛙吃掉的蚊子。

但是有可能有一只蚊子无法吃掉，我们先把它丢进一个集合里面。

每有一次青蛙能吃掉新蚊子，意味着有一个青蛙舌头的长度会增加，便有了能吃掉原本无法吃掉的蚊子的可能，在此时将那些蚊子单独拎出来判断即可。

考虑到对于每一只蚊子最多进集合一次，出集合一次，所以复杂度是正确的。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10;
int n,m;
int x[N],nx[N],len[N],id[N],vis[N];
pii tmp[N];
multiset<pii> st;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r,Max;
    }tr[N << 2];

    inline void pushup(int u){
        tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r};
        if (l == r) return tr[u].Max = x[id[l]] + len[id[l]],void();
        int mid = l + r >> 1;
        build(ls(u),l,mid),build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline void modify(int u,int x,int k){
        if (tr[u].l == x && tr[u].r == x){
            vis[id[x]]++,len[id[x]] += k,tr[u].Max += k;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(ls(u),x,k);
        else modify(rs(u),x,k);
        pushup(u);
    }

    inline int query(int u,int k){
        if (tr[u].l == tr[u].r){
            int t = id[tr[u].l];
            if (x[t] <= k && x[t] + len[t] >= k) return t;
            else return -1;
        }
        if (tr[ls(u)].Max >= k) return query(ls(u),k);
        else return query(rs(u),k);
    }

    #undef ls
    #undef rs
}T;

int main(){
    n = read(),m = read();
    for (re int i = 1;i <= n;i++){
        x[i] = read(),len[i] = read();
        tmp[i] = {x[i],i};
    }
    sort(tmp + 1,tmp + n + 1);
    for (re int i = 1;i <= n;i++){
        id[i] = tmp[i].snd;
        nx[tmp[i].snd] = i;
    }
    T.build(1,1,n);
    while (m--){
        int p,del;
        p = read(),del = read();
        int t = T.query(1,p);
        if (!~t) st.insert({p,del});
        else{
            T.modify(1,nx[t],del);
            auto it = st.lower_bound(make_pair(x[t],-1));
            while (it != st.end() && x[t] + len[t] >= (*it).fst){
                T.modify(1,nx[t],(*it).snd);
                st.erase(it),it = st.lower_bound(make_pair(x[t],-1));
            }
        }
    }
    for (re int i = 1;i <= n;i++) printf("%d %d\n",vis[i],len[i]);
    return 0;
}
```

---

## 作者：Purslane (赞：2)

# Solution

两年前把这题扔进了任务计划——当时以为是超级难题。

假设我们要加入一只新的蚊子。这时候，所有现存的蚊子都是稳定的，不会被任何一只青蛙。

如果这只蚊子不能被任何一只青蛙吃掉，对于青蛙而言无法发生任何变化，直接跳过。否则，可以使用线段树上二分找到第一只能吃掉它的青蛙。

这只青蛙的舌头会增长——因此它会不断吃掉之前稳定的蚊子（这些蚊子，不可能被除了这只幸运青蛙以外的其他青蛙吃掉——他们的舌头都没变长）

复杂度为 $O(n \log n)$，因为吃蚊子这一步可以势能分析。

```cpp
#include<bits/stdc++.h>
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,m,p[MAXN],len[MAXN],id[MAXN],rev[MAXN],mx[MAXN<<2],cnt[MAXN],ans1[MAXN],ans2[MAXN];
struct INFO {int p,len,id;};
multiset<pair<int,int>> st;
void update(int k,int l,int r,int pos,int v) {
	if(l==r) return mx[k]=v,void();
	if(pos<=mid) update(lson,l,mid,pos,v);
	else update(rson,mid+1,r,pos,v);
	return mx[k]=max(mx[lson],mx[rson]),void();	
}
int bfind(int k,int l,int r,int v) {
	if(mx[k]<v) return -1;
	if(l==r) return l;
	int ans=bfind(lson,l,mid,v);
	if(ans!=-1) return ans;
	return bfind(rson,mid+1,r,v);	
}
void insert(int x,int b) {
	int id=bfind(1,1,n,x);
	if(id==-1||p[id]>x) return st.insert({x,b}),void();
	cnt[id]++,len[id]+=b;
	while(1) {
		auto it=st.lower_bound({p[id],0});
		if(it==st.end()) break ;
		if(it->first>p[id]+len[id]) break ;
		cnt[id]++,len[id]+=it->second;
		st.erase(it);
	}
	update(1,1,n,id,p[id]+len[id]);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	vector<INFO> vc;
	ffor(i,1,n) cin>>p[i]>>len[i],vc.push_back({p[i],len[i],i});
	sort(vc.begin(),vc.end(),[](INFO A,INFO B){return A.p<B.p;});
	ffor(i,1,n) p[i]=vc[i-1].p,len[i]=vc[i-1].len,id[i]=vc[i-1].id,update(1,1,n,i,p[i]+len[i]);
	ffor(i,1,m) {
		int p,b;
		cin>>p>>b;
		insert(p,b);	
	}
	ffor(i,1,n) ans1[id[i]]=cnt[i],ans2[id[i]]=len[i];
	ffor(i,1,n) cout<<ans1[i]<<' '<<ans2[i]<<'\n';
	return 0;
}
```

---

## 作者：Code_星云 (赞：2)

这题最直观的做法是把数轴拍到线段树上进行维护，但这样由于数值不定，离散化后点仍会非常多，因此该方法并不优。

又观察到青蛙的数量是正常线段树可以处理的范围，因此考虑将青蛙按位置离散化后放到线段树上，其权值为舌头能伸到的最大位置。那么此时处理蚊子时，就可以用线段树二分的方式求出能吃到某只蚊子的最左边的青蛙。

需要注意的是，蚊子落地后不一定立马就会被吃掉，因此我们再开一个 multiset 来存放，每次再用 lower_bound 寻找可吃掉它的青蛙（具体实现见代码）。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<utility>
#include<queue>
#include<map>
#include<set>
using namespace std;
#define int long long
#define mp make_pair
#define ls (x << 1)
#define rs (x << 1 | 1)
#define px first
#define py second
#define il inline
typedef pair<int, int> pii;
 
const int N = 400005;
int n, m, ret[N], len[N], bg[N], ate[N], to[N];
pii init[N];
multiset<pii> s;
 
namespace sgtree{
	struct segtree{
		int l, r, maxn;
		#define l(x) tree[x].l
		#define r(x) tree[x].r
		#define maxn(x) tree[x].maxn
	};
	segtree tree[2 * N];
	il void pushup(int x){
		maxn(x) = max(maxn(ls), maxn(rs));
	}
	il void build(int x, int l, int r){
		l(x) = l; r(x) = r;
		if(l == r){
			maxn(x) = bg[ret[l]] + len[ret[l]];
			return;
		}
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
		pushup(x);
	}
	il void modify(int x, int p, int val){
		if(! l(x) || ! r(x)) return;
		if(l(x) == r(x) && l(x) == p){
			maxn(x) += val;
			len[ret[l(x)]] += val;
			return;
		}
		int mid = (l(x) + r(x)) >> 1;
		if(p <= mid) modify(ls, p, val);
		else modify(rs, p, val);
		pushup(x);
	}
	il int query(int x, int p){
		if(l(x) == r(x)){
			if(bg[ret[l(x)]] <= p && bg[ret[l(x)]] + len[ret[l(x)]] >= p) return ret[l(x)];
			else return -1;
		}
		if(maxn(ls) >= p) return query(ls, p);
		else return query(rs, p);
	}
};
using namespace sgtree;
 
signed main(){
	scanf("%lld %lld", &n, &m);
	for(int i = 1; i <= n; i ++){
		scanf("%lld %lld", &bg[i], &len[i]);
		init[i] = mp(bg[i], i);
	}
	sort(init + 1, init + n + 1);
	for(int i = 1; i <= n; i ++){
		ret[i] = init[i].py;
		to[ret[i]] = i;
	}
	build(1, 1, n);
	for(int i = 1; i <= m; i ++){
		int p, b;
		scanf("%lld %lld", &p, &b);
		int eater = query(1, p);
		if(! (~ eater)){
			s.insert(mp(p, b));
			continue;
		}
		ate[eater] ++;
		modify(1, to[eater], b);
		set<pii>:: iterator ip = s.lower_bound(mp(bg[eater], -1));
		while(ip != s.end() && (*ip).px <= bg[eater] + len[eater]){
			int tp = (*ip).px, tb = (*ip).py;
			ate[eater] ++; s.erase(ip);
			modify(1, to[eater], tb);
			ip = s.lower_bound(mp(bg[eater], -1));
		}
	}
	for(int i = 1; i <= n; i ++) printf("%lld %lld\n", ate[i], len[i]);
	return 0;
}
```


---

## 作者：Clever_Jimmy (赞：2)

## **题意简述**

给定数轴非负半轴上的 $n$ 只青蛙的位置 $x_i$ 以及舌头长度 $l_i$，还有依次落下来的 $m$ 只蚊子的位置 $p_i$ 以及大小 $b_i$。

每只蚊子 $j$ 仅会被满足 $x_i \le p_j \land x_i + l_i \ge p_j$，且 $i$ 最小的青蛙吃掉，吃之后 $l_i \gets l_i + b_j$。

问最后每只青蛙吃掉的蚊子的数量以及最后每只青蛙舌头的长度[^1]。

数据范围：$1 \le n, m \le 2\cdot 10^5$，$1 \le x_i, l_i, p_i, b_i \le 10^9$。

## **解题思路**

我们实际上要解决的问题，是每只蚊子落下来了之后，被哪只青蛙吃掉。

首先离散化，然后维护区间中 $x_i + l_i$ 的最大值 $\textrm{dat}(p)$。

注意到一只蚊子可能落下来的时候没有青蛙能吃到，但是之后某只青蛙的舌头变长了，能吃到它了；因此我们需要一个 `multiset` 来维护没吃掉的蚊子。

当在线段树上位于一个 $\textrm{dat}(p) < p_i$ 的节点时，肯定这只蚊子是吃不掉的了，把它丢进一个 `multiset` 里存着以后吃。

如果当前节点满足 $\textrm{dat}(p) \ge p_i$：

- 如果 $\textrm{dat}(2p) \ge p_i$，即左儿子节点有青蛙可以吃掉这只蚊子，那肯定是优先选更靠左的青蛙吃掉，向左儿子递归；
- 否则如果 $\textrm{dat}(2p + 1) \ge p_i$，即右儿子节点有青蛙可以吃掉这只蚊子，那就往右儿子递归。
- 如果到了一个叶子节点，说明这个节点表示的青蛙要吃掉当前蚊子了，更新 $l_i$，$\textrm{eat}(p)$（表示这只青蛙吃了多少只蚊子）以及 $\textrm{dat}(p)$。

在更新 $l_i$ 的时候，看当前的青蛙在 `multiset` 里能不能吃更多的蚊子；实现上就是在 `multiset` 里 `lower_bound`，找 $p_j$ 大于等于 $x_i$ 的第一只蚊子 $j$ 能否被 $i$ 吃掉，顺着吃。

## **代码实现**

``` cpp
#include <bits/stdc++.h>
#define LL long long

namespace io {
	template <typename T> inline void read(T & _x) {
        int f = 0, ch; _x = 0;
        while(!isdigit(ch = getchar())) f |= ch == '-';
        while(isdigit(ch)) _x = _x * 10 + ch - '0', ch = getchar();
	        if(f) _x = -_x;
	    }
	    template <typename T, typename ... Args> inline void read(T &_f, Args& ... args) {
	        read(_f), read(args ...);
	    }
	    inline void _deal(char ch) { putchar(ch); }
	    template <typename T> inline void _deal(T _x) {
	        if (_x < 0) putchar('-'), _x = -_x;
	        if (_x > 9) _deal(_x / 10);
	        putchar(_x % 10 + '0');
	    }
	    inline void write() {}
	    template <typename T, typename ... Args> inline void write(T _f, Args ... args) {
	        _deal(_f), write(args...);
	    }
	}

const int N = 2e5 + 5;
const int M = 2e5 + 5;

int n, m, x[N], t[N], rk[N];

std::multiset<std::pair<int, int> > ms;
std::pair<int, LL> ans[M];

bool cmp(int aa, int bb) {
	return x[aa] < x[bb];
}

struct SEGTREE {
	static const int MS = N * 4;
	LL dat[MS];
	int eat[MS], frm[MS];
	void pushup(int p) {
		dat[p] = std::max(dat[p << 1], dat[p << 1 | 1]);
	}
	void build(int p, int L, int R) {
		if(L == R) {
			dat[p] = x[rk[L]] + t[rk[L]];
			eat[p] = 0;
			frm[p] = x[rk[L]];
			return;
		}
		int MID = L + R >> 1;
		build(p << 1, L, MID), build(p << 1 | 1, MID + 1, R);
		pushup(p);
	}
	void solve(int p, int L, int R, int pos, int siz) {
		if(dat[p] < pos) {
			ms.insert(std::make_pair(pos, siz));
			return;
		}
		if(L == R) {
			if(frm[p] > pos)
				ms.insert(std::make_pair(pos, siz));
			else {
				dat[p] += siz, ++eat[p];
				for(std::multiset<std::pair<int, int> >::iterator it = ms.lower_bound(std::make_pair(frm[p], -1)); it != ms.end();) {
					if(it->first > dat[p])
						break;
					else {
						dat[p] += it->second;
						++eat[p];
						std::multiset<std::pair<int, int> >::iterator tmp = it;
						++it;
						ms.erase(tmp);
					}
				}
			}
			return;
		}
		int MID = L + R >> 1;
		if(dat[p << 1] >= pos)
			solve(p << 1, L, MID, pos, siz);
		else if(dat[p << 1 | 1] >= pos)
			solve(p << 1 | 1, MID + 1, R, pos, siz);
		pushup(p);
	}
	std::pair<int, LL> query(int p, int L, int R, int x) {
		if(L == R)
			return std::make_pair(eat[p], dat[p] - frm[p]);
		int MID = L + R >> 1;
		if(x <= MID)
			return query(p << 1, L, MID, x);
		else
			return query(p << 1 | 1, MID + 1, R, x);
	}
} tr;

int32_t main() {
	io::read(n, m);
	for(int i = 1; i <= n; ++i) {
		io::read(x[i], t[i]);
		rk[i] = i;
	}
	std::sort(rk + 1, rk + n + 1, cmp);
	tr.build(1, 1, n);
	for(int i = 1; i <= m; ++i) {
		int ttp, ttb;
		io::read(ttp, ttb);
		tr.solve(1, 1, n, ttp, ttb);
	}
	for(int i = 1; i <= n; ++i)
		ans[rk[i]] = tr.query(1, 1, n, i);
	for(int i = 1; i <= n; ++i)
		printf("%d %lld\n", ans[i].first, ans[i].second);
	return 0;
}
```

原题链接: [F. Frogs and mosquitoes](https://codeforces.com/problemset/problem/609/F)


---

## 作者：__stick (赞：1)

## 题意

~~自己看翻译~~。

## 思路
似乎没有人谢我这种 ~~sb~~  做法。

首先发现题目所要求的最左边的青蛙先吃是非常容易实现的，就维护一颗线段树，表示当前区间归哪只青蛙管，按 $x_i$ 大的先执行区间赋值，然后会发现这样正好就满足的题目的要求，然后这样一颗线段树就能支持我们完成题目的所有要求了，由于 $p_i$ 最大值是 $10^9$ 就写一个边界开到 $10^9$ 的动态开点线段树就行了。

对于每一个蚊子，我们先要找到是哪一个青蛙吃了它，这个就是线段树单点询问，直接询问即可，如果没有青蛙能管到当前蚊子，就不管，否则就要扩大这只青蛙的管辖范围了，先在线段树上二分出来当前青蛙所管到的第一个位置，按照更新后的舌头长度重新进行区间赋值（其实根本不需要，直接从蚊子所在的位置开始就行了，这样就可以少写一个函数），然后就做完了。

然后发现第一个样例都过不去，手动模拟一下发现是因为不能被吃的蚊子并没有消失，而后面有青蛙舌头变长了还能来吃这个蚊子，所以还需要维护一下没有被吃蚊子的位置，每次有青蛙更新过后就看看新区间中有没有蚊子，有就接着吃，这个蚊子用一个 muliset 维护一下就行了。

本来可以对的，但是线段树区间赋值的 tag 忘记清空了。。。。。。。。然后就调好久。

写题解的时候发现线段树是不必要的，只有区间复制单点询问，用珂朵莉树就行了。

## 代码
上个珂朵莉树的吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> >vii;
#define X first
#define Y second
const int mod=998244353;
const int  MAXN=2e5+10;
struct node
{
	int l,r, w;
	inline node(int L=-1,int R=0,int val=0):l(L),r(R),w(val){}
	inline bool operator<(const node &b)const
	{
		return l<b.l;
	}
	inline bool operator==(const node &b)const
	{
		return l==b.l;
	}
};
struct Chtholly:set<node>
{
	#define IT set<node>::iterator
	inline IT split(int pos)
	{
		IT ii=lower_bound(node(pos));
		if(ii!=end()&&ii->l==pos)return ii;ii--;
		node w=*ii;
		erase(ii),insert(node(w.l,pos-1,w.w));
		return insert(node(pos,w.r,w.w)).first;
	}
	inline void assign(int l,int r,int k)
	{
		IT rr=split(r+1);
		erase(split(l),rr);
		insert(node(l,r,k));
	}
	inline int at(int x)
	{
		IT ii=lower_bound(node(x));
		if(ii!=end()&&ii->l==x)return ii->w;ii--;
		return ii->w;
	}
	#undef IT
};
Chtholly ss;
const int N=2e9;
signed main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int n,m;cin>>n>>m;
	vector<array<int,3> >a(n+1);
	for(int i=1;i<=n;i++)
	{
		int x,t;cin>>x>>t;
		a[i]=(array<int,3>){x,t,i};
	}
	ss.insert(node(0,N+10,0));
	sort(a.begin()+1,a.end(),[&](const array<int,3>&a,const array<int,3>&b){return a[0]<b[0];});
	int rt=0;vi w(n+1);
	for(int i=n;i>=1;i--)
	{
		int x,t,id;
		x=a[i][0],t=a[i][1],id=a[i][2];
		w[i]=id;
		ss.assign(x,min(N,x+t),i);
	}
	vi cnt(n+1);
	auto eat=[&](int p,int x)->int
	{
		int id=ss.at(p);
		if(id==0)
		{
			return -1;
		}
		int u,v,w;
		a[id][1]+=x;
		if(p<=min(N,a[id][0]+a[id][1]))ss.assign(p,min(N,a[id][0]+a[id][1]),id);
		cnt[id]++;
		return id;
	};
	multiset<pair<int,int> >s;
	while(m--)
	{
		int p,x;cin>>p>>x;
		int id=eat(p,x);
		if(id==-1)
		{
			s.emplace(p,x);
			continue;
		}	
		while(1)
		{
			int w=a[id][0]+a[id][1];
			auto ii=s.lower_bound({a[id][0],-2e9});
			if(ii==s.end()||w<(ii->X))break;
			eat(ii->X,ii->Y);
			s.erase(ii);
		}
	}
	vi ans1(n+1),ans2(n+1);
	for(int i=1;i<=n;i++)ans1[w[i]]=cnt[i];
	for(int i=1;i<=n;i++)ans2[w[i]]=a[i][1];
	for(int i=1;i<=n;i++)
	{
		cout<<ans1[i]<<' '<<ans2[i]<<'\n';
	}
	 return 0;
}
```


---

## 作者：jzh817 (赞：1)

题意：有n只青蛙，m只蚊子，坐标分别为x[i],p[j],第i只青蛙舌头长度t[i],第j只蚊子大小为b[j],青蛙会从左到右吃它够得到的蚊子，吃完后，舌头会增长吃的蚊子的体积的长度，求最终每只青蛙吃到的蚊子数和舌头长度。

此题一看便知是线段树+multiset,先将青蛙从左到右排序，再插入到线段树中，然后对于每一只蚊子，先查询是否有青蛙能直接吃掉它，若不行，压入multiset中，供后续进行lower_bound操作，并将新的青蛙舌头长度再次插入线段树中，循环往复。

具体实现见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read(){
	ll a=0,b=getchar(),c=1;
	while(!isdigit(b))c=b=='-'?-1:1,b=getchar();
	while(isdigit(b))a=a*10+b-'0',b=getchar();
	return a*c;
}
const int N=200005; 
int n,m,x[N],t[N],c[N],d[N],a[N*4];
multiset<pair<int,int> > st;
bool cmp(int u,int v){
	return x[u]<x[v];
}
int add(int p,int v,int w,int l,int r){
	if(p<l or p>=r)return a[w];
	if(l+1==r)return a[w]=x[d[p]]+v;
	int mid=(l+r)>>1;
	return a[w]=max(add(p,v,w*2,l,mid),add(p,v,w*2+1,mid,r));
}
int query(int p,int w,int l,int r){
	if(l+1==r)return (a[w]>=p and x[d[l]]<=p)?l:-1;
	int mid=(l+r)>>1;
	return a[w*2]>=p?query(p,w*2,l,mid):query(p,w*2+1,mid,r);
}
int main(){
	n=read(),m=read();
	for(int i=0;i<n;i++)
		x[i]=read(),t[i]=read(),d[i]=i;
	sort(d,d+n,cmp);
	for(int i=0;i<n;i++)
		add(i,t[d[i]],1,0,n);
	while(m--){
		int p=read(),b=read();
		int i,k=query(p,1,0,n);
		if(k==-1)st.insert({p,b});
		else{
			i=d[k],c[i]++,t[i]+=b;
			while(st.size()){
				multiset<pair<int,int> >::iterator it=st.lower_bound({x[i],-1});
				if(it==st.end() or x[i]+t[i]<it->first)break;
				c[i]++,t[i]+=it->second,st.erase(it);
			}
			add(k,t[i],1,0,n);
		}
	}
	for(int i=0;i<n;i++)
		printf("%d %d\n",c[i],t[i]);
	return 0;
}
```


---

## 作者：Night_Bringer (赞：0)

# 前言
[博客园体验更佳](https://www.cnblogs.com/C202202chenkelin/p/15034131.html)

[题目链接：CodeForces](https://codeforces.com/problemset/problem/609/F)
# 题意
有 $n$ 个区间，每个区间为 $[x_i,x_i+t_i]$，有 $m$ 个事件，事件的位置为 $p_j$,每个事件会被 $x_i+t_i\geq p_j$ 的区间中， $x_i$ 最小的区间所处理，处理后 $t_i$ 会增加 $b_j$。事件如果没有处理，则不会消失。下一个事件出现时，当且仅当没有可以处理的事件。

输出每个区间处理的事件，和最终的 $t_i$。
# 思路
首先可以发现，这些区间的左端点都是不变的，因为题目想要最小的 $x_i$，所以对于这些区间按照左端点排序。

可以发现，当前答案这一位为 $k$，则前 $k-1$ 个区间中必没有一个满足条件的，而 $p(p\geq k)$，前 $p$ 个区间至少有一个满足条件，于是可以二分答案。

而找到这个分界点，就可以找到能处理这个事件的区间，只需要找到能够处理区间最大值的数据结构。

这里使用的是线段树。第一个二分，二分出 $x_i$ 大于 $p_j$ 的数字的前驱，设为 $rmax$。然后再 $[1,rmax]$ 中二分当前答案。若 $[1,mid]$ 中，最大的 $x_i+t_i$ 大于 $p_j$ 则代表前 $mid$ 个区间可以处理这个事件。

若没有区间可以处理这个事件，则用一个 multiset 来维护没有被处理的事件，按照 $p_j$ 来进行排序，方便以后的区间增长后来处理。

否则处理完当前的事件，区间变长了，由于只有这一个区间变长，所以只有这个区间可能处理之前没处理过的事件。

因为用了 multiset ，所以按顺序枚举 multiset 中的元素。知道不能处理下一个事件或是没有事件可以处理为止。

每处理一个事件，都放入 $slay$ 这个 multiset 中，所有可处理的事件处理完之后，在进行删除，否则会炸。

每次处理后 $slay$ 数组需要清空。
# Code
时间复杂度为 $O(n\log n)$。
```cpp
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
#define LL long long
const int MAXN = 2e5 + 5;
multiset<pair<int, int> > st, slay;
struct Node {
	int l, r, id;
	friend bool operator < (Node x, Node y) {
		return x.l < y.l;
	}
};
bool cmp(Node x, Node y) {
	return x.id < y.id;
}
Node a[MAXN];
int ans[MAXN], p[MAXN], b[MAXN], n, m;
LL len[MAXN];
struct Segment_Node {
	int l, r;
	LL maxdata;
	#define ls (pos << 1)
	#define rs (pos << 1 | 1)
};
struct Segment_Tree {
	Segment_Node t[MAXN << 2];
	void Push_Up(int pos) {
		t[pos].maxdata = max(t[ls].maxdata, t[rs].maxdata);
	}
	void Build(int pos, int l, int r) {
		t[pos].l = l, t[pos].r = r;
		if (l == r) {
			t[pos].maxdata = a[l].r;
			return;
		}
		int mid = (l + r) >> 1;
		Build(ls, l, mid);
		Build(rs, mid + 1, r);
		Push_Up(pos);
	}
	void Update(int pos, int x, int d) {
		if (t[pos].l == t[pos].r) {
			t[pos].maxdata = d;
			return;
		}
		if (t[ls].r >= x)
			Update(ls, x, d);
		else
			Update(rs, x, d);
		Push_Up(pos);
	}
	int Query_Max(int pos, int l, int r) {
		if (l <= t[pos].l && t[pos].r <= r)
			return t[pos].maxdata;
		int res = 0;
		if (l <= t[ls].r)
			res = max(res, Query_Max(ls, l, r));
		if (r >= t[rs].l)
			res = max(res, Query_Max(rs, l, r));
		return res;
	}
};
Segment_Tree tree;
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1, x, t; i <= n; i++) {
		scanf("%d %d", &x, &t);
		a[i].l = x, a[i].r = x + t, a[i].id = i;
	}
	for (int i = 1; i <= n; i++)
		len[i] = a[i].r;
	sort(a + 1, a + 1 + n);
	tree.Build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &p[i], &b[i]);
		int l = 1, r = n, rmax = -1, res = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (a[mid].l <= p[i])
				l = mid + 1, rmax = mid;
			else
				r = mid - 1;
		}
		l = 1, r = rmax;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (tree.Query_Max(1, 1, mid) >= p[i])
				r = mid - 1, res = mid;
			else
				l = mid + 1;
		}
		if (res == -1)
			st.insert(make_pair(p[i], b[i]));
		else {
			LL maxlen = len[a[res].id] + b[i];
			ans[a[res].id]++;
			for (multiset<pair<int, int> >::iterator it = st.upper_bound(make_pair(a[res].l, 0)); it != st.end(); it++) {
				if (it->first <= maxlen) {
					maxlen += it->second;
					ans[a[res].id]++;
					slay.insert(*it);
				}
				else
					break;
			}
			for (multiset<pair<int, int> >::iterator it = slay.begin(); it != slay.end(); it++) 
				st.erase(*it);
			slay.clear();
			len[a[res].id] = maxlen;
			tree.Update(1, res, maxlen);
		}
	}
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; i++)
		printf("%d %lld\n", ans[i], len[i] - a[i].l);
	return 0;
}
```

---

