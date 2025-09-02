# Serge and Dining Room

## 题目描述

Serge 来到学校食堂，发现这里排着一条长队。队伍中有 $m$ 个学生。他现在还不确定是否要等到队伍散去，所以他想知道如果他等到最后，他会拿到哪道菜。由于 Serge 非常疲惫，他让你帮他计算这个问题。

最初有 $n$ 道菜，每道菜的价格分别为 $a_1, a_2, \ldots, a_n$。如你所知，队伍中有 $m$ 个学生，他们分别拥有 $b_1, \ldots, b_m$ 个托格罗（学生按排队顺序编号，即第一个学生拥有 $b_1$ 个托格罗，最后一个学生拥有 $b_m$ 个托格罗）。

学生们认为最贵的菜就是最美味的，所以每个学生都会购买他能买得起的最贵的菜（每道菜只有一份，被买走后其他人就不能再买了）。如果某个学生买不起任何一道菜，他就会离开队伍（真是残酷的资本主义……）

但对 Serge 来说，钱根本不是问题，所以只要还有剩下的菜，他就会买下最贵的那一道。

此外，Serge 的学校经济形势非常不稳定，有些菜的价格或某些学生的托格罗数量可能会发生变化。更正式地说，你需要处理 $q$ 个操作：

- 将 $a_i$ 改为 $x$，即第 $i$ 道菜的价格变为 $x$ 个托格罗。
- 将 $b_i$ 改为 $x$，即队伍中第 $i$ 个学生现在拥有 $x$ 个托格罗。

在这些操作期间，没有学生会离开队伍，因为售货员迟到了。

每次操作后，你都需要告诉 Serge，如果他等到队伍散去，他最终会买到哪道菜的价格；如果此时没有剩下的菜，则输出 $-1$。

## 说明/提示

在第一个样例中，第一次操作后，有一道价格为 $100$ 托格罗的菜和一个只有 $1$ 托格罗的学生，所以 Serge 会买到价格为 $100$ 的菜。

在第二个样例中，第一次操作后，有一道价格为 $1$ 托格罗的菜和一个拥有 $100$ 托格罗的学生，所以 Serge 什么也得不到。

在第三个样例中，没有人能买价格为 $8$ 的菜，所以 Serge 会拿走它。第二次操作后，所有菜都被买走了。第三次操作后，第三和第五个学生分别买走了第一和第二道菜，第四道菜没人买。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 1
1
1
1
1 1 100
```

### 输出

```
100
```

## 样例 #2

### 输入

```
1 1
1
1
1
2 1 100
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 6
1 8 2 4
3 3 6 1 5 2
3
1 1 1
2 5 10
1 1 6
```

### 输出

```
8
-1
4
```

# 题解

## 作者：Mr_HY43205 (赞：7)

[CF1179C Serge and Dining Room](https://www.luogu.com.cn/problem/CF1179C)
### 题意
食堂有 $n$ 种菜品，第 $i$ 种菜品价格 $a_i$ 元。有 $m$ 个学生排队吃饭，第 $i$ 个学生带了 $b_i$ 元。学生依次挑选菜品，每个人都会选择之前没人买过的，自己能买得起的最贵的菜。现在给定菜品价格序列 $a$ ，以及学生身上所带金额的序列 $b$，并进行 $q$ 次修改，每次修改可以让一种菜品的价格变为 $x$ 元，或者让一个学生带的钱变成 $x$ 元。问每次修改完，学生买完之后剩下菜品中最贵的菜值多少钱？

###### 数据范围：
$1 \leq n,m \leq 3\times10^5, 1\leq a,b \leq 10^6,1 \leq q \leq 3\times 10^5$。
###### 关键词：线段树

------------
### 解题思路
题意很长，刚开始可以多举一些例子帮助理解。经过一些例子的计算和模拟，我们可以发现，每次询问，需要找到一个最大的菜品价格 $a_i$，使得能买得起这盘菜的学生人数小于价格大于等于 $a_i$ 的菜品的数量。

形式化地说，我们要求的是 $(a_i)_ {max}$，使得集合 $\{x|x\geq a_i \ \wedge\ x\in \{a\}\}$ 中的元素多于集合 $\{y|y\geq a_i \ \wedge\ y\in \{b\}\}$。

既然我们要统计的是集合大小，那每个元素之间的相对位置应该对答案没有影响。也就是说，不管学生怎么排队，菜品按什么顺序排列，最后剩下菜品的最高价格一定是唯一的。

这个结论对吗？可以简单地证明一下，如果我们只交换相邻两个学生之间的顺序，那最多只可能让两个人吃到的菜交换一下，对答案是没有影响的。由此，无论我们怎么交换学生之间的顺序，最终答案都不变。

于是，我们只需要考虑每种价格所对应的菜品和学生的数量就可以了。为了方便，我们可以记 $f(i)$ 为价格大于等于 $i$ 的菜的数量， $g(i)$ 为钱数大于等于 $i$ 的学生的数量。由于我们关心的是菜品数和学生数之间的差，所以我们只需要维护好每一个价格对应的 $g(i) - f(i)$，并且找到最大的 $i$ 使得 $g(i) - f(i) < 0$ 就行了。

如何维护每一个价格对应的 $g(i) - f(i)$？首先，一盘价格为 $a_i$ 的菜会让每一个小于等于 $a_i$ 的价格的 $g(i) - f(i)$ 减一，而一个带了 $b_j$ 元钱的学生会让每一个小于等于 $a_i$ 的价格的 $g(i) - f(i)$ 加一。修改菜价和学生钱数也可以看成是同样的操作。所以我们需要一个数据结构来进行区间修改的操作。直接使用普通的线段树进行维护就可以了。

本题线段树使用价格作为区间。在线段树维护的过程中，我们使用 $mn$ 数组来表示每一个区间内最小的 $g-f$ 的值。在查询的过程中，找到位置最靠右的，$mn$ 值小于 $0$ 且长度为一的区间，并返回其区间位置（即对应价格）。如果整个定义域内都没有 $mn$ 小于 $0$ 的区间，说明无解，返回 $-1$。每一次询问都在线段树上进行一次区间修改操作，并输出答案。每次询问操作的时间复杂度为 $O(\log(10^6))$，经过 $q$ 次操作，总时间复杂度为 $O(q\cdot \log(10^6))$。

本题代码如下：

```cpp
#include <iostream>
using namespace std;

#define ls i << 1
#define rs (i << 1) + 1
const int maxN = 300005;
const int maxA = 1000005;
int n, m, q;
int a[maxN], b[maxN];
int cnt[maxA];		//在输入初始数组时记录每个价格对应的数量
int l[maxA * 4], r[maxA * 4], mn[maxA * 4], tag[maxA * 4];		//线段树区间信息，tag为区间操作时的懒标记

void setup(int i) {		//建树
    if (l[i] == r[i]) return;
    int m = (l[i] + r[i]) >> 1;
    l[ls] = l[i];
    r[ls] = m;
    l[rs] = m + 1;
    r[rs] = r[i];
    setup(ls);
    setup(rs);
}
void push_down(int i) {		//标记下放
    if (tag[i] == 0) return;
    mn[ls] += tag[i];
    mn[rs] += tag[i];
    tag[ls] += tag[i];
    tag[rs] += tag[i];
    tag[i] = 0;
}
void update(int ql, int qr, int i, int d) {	//线段树区间修改操作，进行增量式维护
    if (qr < l[i] || r[i] < ql) return;
    else if (l[i] < ql || qr < r[i]) {
        push_down(i);
        update(ql, qr, ls, d);
        update(ql, qr, rs, d);
        mn[i] = min(mn[ls], mn[rs]);
    }
    else {
        mn[i] += d;
        tag[i] += d;
    }
}
int query(int i) {		//线段树查询，返回对应价格最高的合法位置
    if (mn[i] > 0) return -1;
    else if (l[i] == r[i]) return l[i];
    else {
        push_down(i);
        if (mn[rs] < 0) return query(rs);
        else if (mn[ls] < 0) return query(ls);
        else return -1;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]--;
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        cnt[b[i]]++;
    }
    l[1] = 1;
    r[1] = 1000000;
    setup(1);
    for (int i = 1; i <= 1000000; i++) {
        update(1, i, 1, cnt[i]);
    }			//线段树初始化
    cin >> q;
    for (int t = 1; t <= q; t++) {
        int c, i, x;
        cin >> c >> i >> x;
        if (c == 1) {
            if (x > a[i]) update(a[i] + 1, x, 1, -1);
            else update(x + 1, a[i], 1, 1);
            a[i] = x;
        }
        else {
            if (x > b[i]) update(b[i] + 1, x, 1, 1);
            else update(x + 1, b[i], 1, -1);
            b[i] = x;
        }
        cout << query(1) << endl;		//对每次更新进行维护，并输出答案
    }
    return 0;
}
```



---

## 作者：wucstdio (赞：4)

这是一道十分巧妙的贪心题。

### 题意

有$n$盘菜和$m$个人，每一个人都会选择他能买的价值最高的菜，问最后剩下的价值最高的菜的价值，带修改。

### 转化

首先我们考虑我们可以怎么求。

如果有两个人$i<j$，且$b_i<b_j$，那么如果$i$选择的菜比$j$选择的菜贵（因为他排在前面），那么我们就可以把这两个人选择的菜交换一下，这样并不会影响判定是否有解。

经过若干次交换，我们就发现人的标号已经没有关系了，因为我们把$b_i$排序之后，会发现他们选择的菜也已经按照价格排序了。

这样我们就可以得到另一个暴力：将所有人和所有菜从大到小排序，每次比较开头的两个，如果能买就删掉他们后继续，否则这个菜就是答案。

### 再转化

然而我们发现这仍然是一个暴力……

我们需要将这个再转化成可以用数据结构维护的东西。

我们考虑最后的答案$i$应该满足什么条件。容易发现条件就是能买下它的有$i-1$个人，并且这些人都买了比它贵的那些菜。

经过一番思考，条件可以进一步转化为：**排序后，第$i$道菜可能成为答案，当且仅当能够买下这道菜的人数小于$i$**，我们只需要对所有这样的菜价格取个max即可

所以我们就可以用平衡树维护能买下这道菜的人数减去每一道菜的排名，记为$val[i]$，这样答案就是第一个$val[i]<0$的元素。可以直接在平衡树上二分实现。

然后我们发现值域范围只有$10^6$，所以其实不需要平衡树，用权值线段树就可以解决。注意一开始权值线段树中的数应该都设为正无穷，当一个值变成合法的时候再减回来。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define lson o<<1
#define rson o<<1|1
#define mid (l+r)/2
using namespace std;
struct Tree
{
	int minv;
	int addv;
}tree[4000005];
int n,m,q,a[300005],b[300005],cnt[1000005];
void pushup(int o)
{
	tree[o].minv=min(tree[lson].minv,tree[rson].minv);
}
void build(int o,int l,int r)
{
	if(l==r)
	{
		tree[o].minv=1000000000;
		return;
	}
	build(lson,l,mid);
	build(rson,mid+1,r);
	pushup(o);
}
void pushdown(int o)
{
	if(tree[o].addv)
	{
		tree[lson].addv+=tree[o].addv;
		tree[rson].addv+=tree[o].addv;
		tree[lson].minv+=tree[o].addv;
		tree[rson].minv+=tree[o].addv;
		tree[o].addv=0;
	}
}
void add(int o,int l,int r,int from,int to,int v)
{
	if(l>=from&&r<=to)
	{
		tree[o].addv+=v;
		tree[o].minv+=v;
		return;
	}
	pushdown(o);
	if(from<=mid)add(lson,l,mid,from,to,v);
	if(to>mid)add(rson,mid+1,r,from,to,v);
	pushup(o);
}
int ask(int o,int l,int r)
{
	if(tree[o].minv>=0)return -1;
	if(l==r)return l;
	pushdown(o);
	if(tree[rson].minv<0)return ask(rson,mid+1,r);
	else return ask(lson,l,mid);
}
void debug(int o,int l,int r)
{
	if(l>10)return;
	if(l==r)
	{
		printf("%d ",tree[o].minv);
		return;
	}
	pushdown(o);
	debug(lson,l,mid);
	debug(rson,mid+1,r);
}
int main()
{
	scanf("%d%d",&n,&m);
	build(1,1,1000000);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		cnt[a[i]]++;
		if(cnt[a[i]]==1)add(1,1,1000000,a[i],a[i],-1000000000);
		add(1,1,1000000,1,a[i],-1);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		add(1,1,1000000,1,b[i],1);
	}
	scanf("%d",&q);
	while(q--)
	{
		int opt,i,x;
		scanf("%d%d%d",&opt,&i,&x);
		if(opt==1)
		{
			add(1,1,1000000,1,a[i],1);
			cnt[a[i]]--;
			if(cnt[a[i]]==0)add(1,1,1000000,a[i],a[i],1000000000);
			a[i]=x;
			add(1,1,1000000,1,a[i],-1);
			cnt[a[i]]++;
			if(cnt[a[i]]==1)add(1,1,1000000,a[i],a[i],-1000000000);
		}
		else
		{
			add(1,1,1000000,1,b[i],-1);
			b[i]=x;
			add(1,1,1000000,1,b[i],1);
		}
		printf("%d\n",ask(1,1,1000000));
	}
	return 0;
}
```

时间复杂度$O((n+q)\log v)$

---

## 作者：封禁用户 (赞：3)

小蒟蒻又来水题解啦 QωQ

# 题目
…… 没法简化题意了。

# 思路
我们机房里的另一位同学很快就给出了解法：

__如果第 $i$ 大的 $a$ 满足，不小于它的 $b$ 有至多 $i-1$ 个，则 $i$ 可以作为答案！__

“从来如此，便对吗？”虽然 $\tt LLB$ 经常虐场，但是我 ~~怀着杠精的傲骨~~ 决定反驳！

然后找到了一组数据。$a=\{1,4,5\},b=\{2,3\}$ ，显然第 $3$ 大的 $a$ 是不能作为答案的。

~~话说另一篇题解好像也有这个小失误？~~

我只好自己 $\tt yy$ 了一个算法。我说，我把 $a$ 和 $b$ 都从大到小排序，然后依次扫过去。设定变元 $x=0$ 。如果遇到 $b$ ，将 $x$ 加上 $1$ ；遇到 $a$ ，将 $x$ 减 $1$ ，若 $x<0$ ，立刻返回当前 $a$ 值作为答案。

我是怎么想的呢？$x$ 相当于记录了没匹配的 $b$ 的数量。如果有一个 $a$ 出现，肯定会与一个 $b$ 匹配，因为它们之间没别人。而 $x<0$ 说明没有 $b$ 与之匹配，所以就直接作为答案了——毕竟是从大到小考虑的。

结果这两种算法走到了同一条路上：将 $b$ 视为 $+1$ ，将 $a$ 视为 $-1$ ，求后缀和为负的第一个位置。

可是为啥前面那种论述有反例？问题就是这个“立刻返回当前 $a$ 值作为答案”。最终的答案是满足这个条件的，但是其他的 $a$ 却说不准了。

反正大家觉得前面那个也有道理、也能 $\tt AC$ ，就不用看我的想法了。

# 代码
后缀和咋整？当成对 $(-\infty,a]$ 进行区间修改。于是用权值线段树，查询靠二分，二分可以放在线段树上。复杂度 $\mathcal O[(n+m+q)\log a]$ 。

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long int_;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0'||c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c&&c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
inline void writeint(int x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) writeint(x/10);
	putchar((x%10)^48);
}

const int MaxN = 1000000;

int v[MaxN<<1|1]; // 线段树区间内最小值
int lazy[MaxN<<1|1]; // 懒标记

void pushDown(int l,int r){
	int t = (l+r)|(l!=r), mid = (l+r)>>1;
	int lson = (l+mid)|(l!=mid);
	int rson = (mid+1+r)|(mid+1!=r);
	v[lson] += lazy[t];
	lazy[lson] += lazy[t];
	v[rson] += lazy[t];
	lazy[rson] += lazy[t];
	lazy[t] = 0;
}

int add(int ql,int qr,int adv,int l=1,int r=MaxN){
	int t = (l+r)|(l!=r); // 存储位置
	if(r < ql || qr < l) return v[t];
	if(ql <= l && r <= qr){
		lazy[t] += adv;
		return v[t] += adv;
	}
	pushDown(l,r); // 一定记得先下传懒标记
	int lson = add(ql,qr,adv,l,(l+r)>>1);
	int rson = add(ql,qr,adv,(l+r)/2+1,r);
	return v[t] = min(lson,rson); // pushUp
}

int query(int l=1,int r=MaxN){
	int t = (l+r)|(l!=r);
	if(v[t] >= 0) return -1;
	if(l == r) return l;
	pushDown(l,r);
	int res = query((l+r)/2+1,r);
	if(res != -1) return res;
	return query(l,(l+r)>>1);
}

int a[2][MaxN];
int main(){
	int n = readint(), m = readint();
	for(int i=1; i<=n; ++i)
		add(1,a[0][i] = readint(),-1);
	for(int i=1; i<=m; ++i)
		add(1,a[1][i] = readint(),1);
	int q = readint();
	while(q --){
		int opt = readint()-1;
		int x = readint();
		int v = readint();
		add(1,a[opt][x],1-2*opt);
		add(1,a[opt][x] = v,2*opt-1);
		writeint(query());
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
很早之前 duel 到的，当时没做出来，今早 $10$ 分钟瞪出来了。

感觉和 [CF756C](https://www.luogu.com.cn/problem/CF756C) 挺像。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
考虑逐步拆解这个问题。

首先看到学生有顺序，这个就很难办了。

当我加入修改的时候，就要把修改后学生都跑一遍，$n^2$ 降不下去了。

考虑先从这里下手，不难发现，顺序是没有影响的。

因为菜是没有顺序的，所以我们把菜按金额排序放到数轴上。

接着把学生的钱数也抽象成点扔到数轴上，那他能买的菜就是在这个点左边的任何点。

考虑下这个点贡献什么时候会产生变化。

即为当他一直加直到又越过一个菜的金额的点的时候嘛。

也就是，被两个菜的金额夹在中间的钱数的学生都是等价的。

接着因为等价类中的学生买的菜品金额是单减的，一定是把更大的先选走。

所以并不存在一个钱多的学生只买了个金额很小的菜导致答案变大的情况。

这样我们就可以按照任意顺序处理学生了。

接着考虑，对于一个有 $x$ 块钱的学生，他能买的菜的金额区间，即为 $[1,x]$。

而一个价格为 $x$ 的菜，不能买这个菜的金额区间便为 $[1,x]$。

那么对于学生的区间 $+1$，菜的区间 $-1$，点 $x$ 的值便表示能买金额为 $x$ 的菜的人数。

那什么时候是菜没法被人买呢？

能买人数 $<0$ 的时候，即是存在金额为 $x$ 且没人能买的时候了。

考虑用线段树维护这个过程，找的时候因为要找最大的 $x$，所以先遍历右儿子再遍历左儿子。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=3e5+10,V=1e6,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,q,a[N],b[N],t[(V+10)<<2],lz[(V+10)<<2];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s) { for(char c:s) put(c); }
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void pushdown(int p){lz[ls]+=lz[p],lz[rs]+=lz[p],t[ls]+=lz[p],t[rs]+=lz[p],lz[p]=0;}
inline void modify(int p,int l,int r,int x,int w)
{
    if(r<=x) return lz[p]+=w,t[p]+=w,void();
    pushdown(p);modify(ls,l,mid,x,w);
    if(mid<x) modify(rs,mid+1,r,x,w);
    t[p]=min(t[ls],t[rs]);
}
inline int query(int p,int l,int r)
{
    if(l==r) return l;pushdown(p);
    if(t[rs]<0) return query(rs,mid+1,r);
    if(t[ls]<0) return query(ls,l,mid);
    return -1;
}
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read(),modify(1,1,V,a[i],-1);
    for(int i=1;i<=m;i++) b[i]=read(),modify(1,1,V,b[i],1);
    q=read();
    for(int i=1,op,x,y;i<=q;i++)
    {
        op=read(),x=read(),y=read();
        if(op==1) modify(1,1,V,a[x],1),modify(1,1,V,a[x]=y,-1);
        else modify(1,1,V,b[x],-1),modify(1,1,V,b[x]=y,1);
        print(query(1,1,V));put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：kouylan (赞：2)

这题题意就是有 $n$ 盘菜，每盘菜有价格 $a_i$；有 $m$ 个人，每个人有 $b_i$ 的钱。每个人会买自己能买并且还有的最贵的。问最后剩下的最贵的菜是多少钱？带修改。

我们先来想一个问题，什么时候一盘菜会剩下来？显然是能买这盘菜的人都去买更贵的菜了，而不能买的人什么都做不了。

这样，我们就可以定义 $rank_i$ 表示能买第 $i$ 道菜的人减去这道菜从大到小的排名。如果 $rank_i<0$，就代表这盘菜会剩下。

这样我们就想到了一个暴力的做法：每一次修改，我们都把 $rank_i$ 算出来，就能求出答案了。

我们来想办法优化这个做法。因为每一次 $a_i$ 改变或 $b_i$ 改变，受影响的都是从 $1$ 到 $a_i/b_i$ 的 $rank_i$ 值，所以我们可以用一颗线段树维护，下标就是菜的价格，即 $a_i$，只需要记录对应区间内 $rank_i$ 的最小值，记为 $mn$ 即可。查询时，若 $mn>=0$，则代表无解，否则返回最大的下标即可。

下面是 AC 代码。
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define lson o<<1
#define rson o<<1|1
#define mid (l+r>>1)

const int N = 1e6;
const int INF = 0x7f7f7f7f;

int n,m,q,a[300005],b[300005],apr[1000005];
struct segtree{
	int mn,laz;
}t[1000005<<2];

void update(int o)
{
	t[o].mn = min(t[lson].mn,t[rson].mn);
}

void build(int o,int l,int r)
{
	t[o].laz = 0;
	if(l==r)
	{
		t[o].mn = INF;
		return;
	}
	build(lson,l,mid);
	build(rson,mid+1,r);
	update(o);
}

void pushdown(int o)
{
	if(t[o].laz)
	{
		t[lson].mn += t[o].laz, t[lson].laz += t[o].laz;
		t[rson].mn += t[o].laz, t[rson].laz += t[o].laz;
	}
	t[o].laz = 0;
}

void modify(int o,int l,int r,int ql,int qr,int v)
{
	if(l>=ql && r<=qr)
	{
		t[o].mn += v;
		t[o].laz += v;
		return;
	}
	pushdown(o);
	if(ql<=mid)
		modify(lson,l,mid,ql,qr,v);
	if(qr>mid)
		modify(rson,mid+1,r,ql,qr,v);
	update(o);
}

int query(int o,int l,int r)
{
	if(t[o].mn>=0)
		return -1;
	if(l==r)
		return l;
	pushdown(o);
	if(t[rson].mn<0)
		return query(rson,mid+1,r);
	else
		return query(lson,l,mid);
}

signed main()
{
	cin>>n>>m;
	build(1,1,N);
	for(int i=1;i<=n&&scanf("%lld",a+i);i++)
	{
		modify(1,1,N,1,a[i],-1);
		apr[a[i]]++;
		if(apr[a[i]]==1)
			modify(1,1,N,a[i],a[i],-INF);
	}
	for(int i=1;i<=m&&scanf("%lld",b+i);i++)
		modify(1,1,N,1,b[i],1);
	cin>>q;
	while(q--)
	{
		int op,x,y;
		scanf("%lld%lld%lld",&op,&x,&y);
		if(op==1)
		{
			modify(1,1,N,1,a[x],1);
			apr[a[x]]--;
			if(apr[a[x]]==0)
				modify(1,1,N,a[x],a[x],INF);
			a[x] = y;
			apr[a[x]]++;
			modify(1,1,N,1,a[x],-1);
			if(apr[a[x]]==1)
				modify(1,1,N,a[x],a[x],-INF);
		}
		else if(op==2)
		{
			modify(1,1,N,1,b[x],-1);
			b[x] = y;
			modify(1,1,N,1,b[x],1);
		}
		printf("%lld\n",query(1,1,N));
	}
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：冷却心 (赞：0)

我是夏亚·阿兹纳布尔。

简单 ds。考虑答案的充分条件：对于一个 $x$，如果大于 $a_i\ge x$ 的菜数量大于 $b_i \ge x$ 的人数量，那么答案 $\ge x$。但是这个不具有单调性，所以不能直接二分。但是能发现答案是最大的满足这个条件的 $x$。所以我们对权值开一棵线段树对每个 $x$ 维护 $a_i\ge x$ 的个数减去 $b_i \ge x$ 的个数，那么修改就是前缀加减，查询就是查询全局最后一个 $\ge 0$ 的位置，可以直接线段树上二分。时间复杂度 $O((n+m+q)\log V)$。

https://codeforces.com/problemset/submission/1179/326589856。

---

## 作者：Pink_Dove (赞：0)

[更美味的食用体验](https://yumomeow.github.io/2025/02/28/solution-CF1179_c/)
## 题意
有 $n$ 道菜和 $m$ 个学生，每个菜有价格 $a_i$，每个学生有 $b_i$ 元。学生按顺序买菜，每个人会买能买得起的最贵的菜，买不起就离开队伍。

每次修改某道菜的价格或者某个学生的钱数，求所有学生买完菜后剩下最贵的菜，如果不剩就输出 $-1$。
## 题解
学生的顺序并不会影响答案。考虑两个学生 $i,j$，$b_i<b_j$，不管是 $i$ 先买还是 $j$ 先买都不会影响到他们买到的菜，最终答案也不会被影响。

实际上我们要求的就是一个最大的 $a_i$，使得买得起这盘菜的学生人数小于价格大于等于 $a_i$ 的菜的数量，这样大于等于 $a_i$ 的菜（除了这一个）都会被买走，剩下最大的就是 $a_i$。对于那些被买走的价格比 $a_i$ 小的菜，我们并不关心。

形式化地说，对于每个 $i$，设 $\ge i$ 的 $b_j$ 数量为 $f_i$， $\ge i$ 的 $a_j$ 数量为 $g_i$，那么我们要求的就是最大的满足 $f_i-g_i<0$ 的 $i$。

考虑加入一个 $a_i$ 对于 $f-g$ 会有什么影响。显然所有 $\le i$ 的 $g_i$ 会 $+1$，$(f_i-g_i)$ 相应减一。加入一个 $b_i$ 时，所有 $\le i$ 的 $f_i$ 会 $+1$，$f_i-g_i$ 相应加一。

建立一个线段树，对每个价格 $i$ 维护 $(f_i-g_i)$。加入$a_i,b_i$ 时就是前缀加减操作，修改时就是区间加减。查询时，只需要查最大的 $\le 0$ 的下标就可以。

## 代码
```cpp
#include<iostream>
#define ls (u<<1)
#define rs (u<<1|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=1e6+10;
int n,m,a[N],b[N],q,mi[N<<2],tag[N<<2];
void pushdown(int u){
	mi[ls]+=tag[u];mi[rs]+=tag[u];
	tag[ls]+=tag[u];tag[rs]+=tag[u];
	tag[u]=0;
}
void insert(int u,int l,int r,int L,int R,int k){
	if(L<=l&&r<=R){
		mi[u]+=k;tag[u]+=k;
		return;
	}
	pushdown(u);
	if(L<=mid) insert(ls,l,mid,L,R,k);
	if(R>mid) insert(rs,mid+1,r,L,R,k);
	mi[u]=min(mi[ls],mi[rs]);
}
int query(int u,int l,int r){
	if(mi[u]>0) return -1;
	if(l==r) return l;
	pushdown(u);
	if(mi[rs]<0) return query(rs,mid+1,r);
	if(mi[ls]<0) return query(ls,l,mid);
	return -1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		insert(1,1,N-1,1,a[i],-1);
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		insert(1,1,N-1,1,b[i],1);
	}
	cin>>q;
	while(q--){
		int op,i,x;
		cin>>op>>i>>x;
		if(op==1){
			if(x>a[i]) insert(1,1,N-1,a[i]+1,x,-1);
			else insert(1,1,N-1,x+1,a[i],1);
            // 这里可以画图理解一下
            // 就是减去原本 a_i 的贡献，加上 x_i 的贡献，影响的就是不重叠的那段区间
			a[i]=x;
		}
		else{
			if(x>b[i]) insert(1,1,N-1,b[i]+1,x,1);
			else insert(1,1,N-1,x+1,b[i],-1);
			b[i]=x;			
		}
		cout<<query(1,1,N-1)<<'\n';
	}
	return 0;
}
```

---

## 作者：Purslane (赞：0)

## Solution

紫题当然要写题解喽 .

考虑答案是 $x$ . 那么有 $A=\sum[a_i \ge x]$ 个盘子可供选择 , 有 $B=\sum [b_i \ge x]$ 个阔气的小朋友可以买得起价格不少于 $x$ 的盘子 .

其实我们不用关心这些小朋友买的具体是哪一个 , 只需要知道有 $B$ 个人就可以了 .

显然当 $A > B$ 的时候 Serge 是可以买到价格不少于 $x$ 的盘子 .

$A > B$ 这种条件的解法比较经典 : $\pm 1$ 序列 , 子段和为正 .

由于带修 , 我们开一个权值线段树 , 表示价格 . 我们要进行以下操作 :

- `update(1,1,N,a[i],1)` 表示一个盘子
- `update(1,1,N,b[i],-1)` 表示一个小朋友

这样我们求正的后缀和即可 .

这种显然的东西可以线段树上二分 .

> 怎样二分 ? 我们应择优取大的 , 所以先往右儿子走 . 看看有儿子的最大后缀和加上后面的是否 $> 0$ , 如果是 , 那么答案肯定在右儿子 ; 否则往左儿子走 . 复杂度 $\text{O(log n)}$ .

注意判 `-1` .

code : 

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
#define mid (l+r>>1)
using namespace std;
const int MAXN=1e6+10;
int n,m,q,a[MAXN],b[MAXN];
struct Segment_Tree {
	int l,r,sum,suf;
}tr[MAXN<<2];
Segment_Tree operator +(Segment_Tree A,Segment_Tree B) {
	return {A.l,B.r,A.sum+B.sum,max(B.suf,B.sum+A.suf)};
}
void build(int k,int l,int r) {
	if(l==r) return tr[k]={l,r,0,0},void();
	build(k<<1,l,mid),build(k<<1|1,mid+1,r);
	tr[k]=tr[k<<1]+tr[k<<1|1];
	return ;
}
void update(int k,int l,int r,int pos,int add) {
	if(l==r) return tr[k]={l,r,tr[k].sum+add,tr[k].suf+add},void();
	if(pos<=mid) update(k<<1,l,mid,pos,add);
	else update(k<<1|1,mid+1,r,pos,add);
	tr[k]=tr[k<<1]+tr[k<<1|1];
	return ;
}
int N=1000000;
void init(void) {
	build(1,1,N);
 	ffor(i,1,n) update(1,1,N,a[i],1);
 	ffor(i,1,m) update(1,1,N,b[i],-1);
	return ;
}
int query(int k,int l,int r,int tot) {
	if(l==r&&tot+tr[k].sum>0) return l;
	if(l==r) return -1;
	if(tot+tr[k<<1|1].suf>0) return query(k<<1|1,mid+1,r,tot);
	return query(k<<1,l,mid,tot+tr[k<<1|1].sum);
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,m) cin>>b[i];
	init();
	cin>>q;
	ffor(i,1,q) {
		int op,pos,val;
		cin>>op>>pos>>val;
		if(op==1) update(1,1,N,a[pos],-1),update(1,1,N,val,1),a[pos]=val;
		else update(1,1,N,b[pos],1),update(1,1,N,val,-1),b[pos]=val;
		cout<<query(1,1,N,0)<<'\n';
	}
	return 0;
}
```

写得太丑啦 ......

---

