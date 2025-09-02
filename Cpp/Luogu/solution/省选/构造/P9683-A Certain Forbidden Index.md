# A Certain Forbidden Index

## 题目背景

**这是一道函数式交互题。本题仅支持 C++ 提交。（出于某些原因，请不要使用 GCC 9 提交）**

**本地编译、提交时请在程序里加入以下函数声明语句：**

```cpp
int query(int, int);
```

**任何在赛时攻击交互库而得分的行为均视为作弊。**


## 题目描述

有一个长为 $n=2^k$ 的序列，基于这个序列建立了一棵[线段树](https://oi-wiki.org/ds/seg/)。现在线段树上有恰好一个节点被标记了。

你可以进行若干次询问，每次询问给定一个区间 $[l,r]$，交互库会在被修改的线段树上进行一次区间查询，你可以得知在被修改的线段树上这个区间对应的所有节点中，是否有节点被标记。

你需要在尽可能少的询问内找到这个节点。具体而言，若最优策略在最坏情况下需要 $Q$ 次询问，则你最多可以使用 $Q$ 次询问。

### 交互流程

你不需要，也不应该实现主函数，你只需要实现如下函数：

```cpp
std::pair<int, int> solve(int k);
```

该函数需要在得到答案后返回一个数对 $(x,y)$，表示被标记的线段树节点所对应的区间为 $[x,y]$。

你可以调用交互库提供的方法：

```cpp
int query(int l, int r);
```

传入的 `l` 和 `r` 代表询问的区间为 $[l,r]$。交互库会返回对应的结果。你需要保证 $1\le l\le r\le n$。具体而言：

- 当没有节点被标记时，交互库返回 $0$；
- 当有节点被标记时，交互库返回 $1$；
- 当询问的区间不合法时，交互库会返回 $-1$，此时你需要立即结束这组数据的交互（不是整个测试点），否则可能导致不可预知的错误。

本题无询问次数限制，但过多的询问会导致时间超限，详细信息请看“数据规模与约定”。

## 说明/提示

#### 样例 1 解释

下面是一种可能的交互流程：

| 交互库 | 选手程序 | 备注 |
| :----------: | :----------: | :----------: |
| 调用 `solve(2)` |  | 开始测试 |
| 返回 $1$ | 调用 `query(1,1)` | $[1,1]$ 就是答案节点 |
|  | 返回 $(1,1)$ | 答案正确 |
| 调用 `solve(2)` |  | 开始下一组数据的评测 |
| 返回 $1$ | 调用 `query(2,4)` | $[2,4]$ 对应的节点是 $[2,2]$ 和 $[3,4]$，包括了答案节点 |
| 返回 $0$ | 调用 `query(1,4)` | $[1,4]$ 对应的节点只有 $[1,4]$，不包括答案节点 |
|  | 返回 $(3,4)$ | 答案正确，评测结束 |


### 计分方式

本题首先会受到和传统题相同的限制。例如编译错误会导致整道题目得 $0$ 分，运行时错误、超过时间限制、超过空间限制等会导致相应测试点得 $0$ 分等。

如果你找到的节点是错误的，或者你给出的询问不合法，在该测试点将会得到 $0$ 分。

否则，设在一组数据中，答案最坏需要 $x$ 次询问，而你使用了 $y$ 次询问，满分为 $t$，则这组数据的分数是 $t\times \min\left(1,\mathrm{e}^{-\frac{y}{x}+1}\right)$。

每个测试点取所有数据组中得分的最小值，向下保留两位小数。你的得分是所有测试点得分之和。

### 数据规模与约定

对于所有数据，保证 $1\le k\le 14$，$1\le T\le 300$。

本题共 $14$ 个测试点，对于第 $i$ 个测试点，保证 $k=i$。对于 $1\le k\le 4$ 的测试点，满分 $10$ 分。对于 $5\le k\le 14$ 的测试点，满分 $6$ 分。

保证在每组数据进行 $2n$ 次询问时，单个测试点内，交互库使用的时间不超过 0.6s，空间不超过 8MiB。

### 下发文件说明

下发文件中有一个可以通过样例的程序示例 `sample.cpp`，以及一个样例交互库 `grader.cpp`。假设你的答案文件为 `answer.cpp`，则可以使用如下命令将其编译成可执行文件 `answer`：

```shell
g++ grader.cpp answer.cpp -o answer -O2
```

实际评测时的交互库可能是自适应的，即被修改的节点可能不会在交互一开始时确定。

## 样例 #1

### 输入

```
2
2 1 1
2 3 4```

### 输出

```
1
2```

# 题解

## 作者：FFTotoro (赞：19)

题目链接：[$\color{Purple}\texttt{P9683 A Certain Forbidden Index}$](https://www.luogu.com.cn/problem/P9683)。

填坑。提供一个相对好写的做法。

考虑把一堆不交的区间绑在一起问（即先询问这些区间的并，判断答案是否在里面）：对于一个区间，能与它绑在一起的区间最多只有 $1$ 个是与它同一层的。

于是我们想到一个比较原始的做法：因为 $[1,2^k]$ 没有任何区间可以合并，所以放最后作为单独一块问；从线段树的顶端按照 BFS 序往下询问，如果该区间 $[l,r]$ 没有进行过标记（记这种区间为“**初始区间**”），按以下方式处理：标记它，如果它是作为左儿子被问到的（反之同理），那么就不断往右找下一层且它们的**并集是一个区间**的区间 $[l_1,r_1]$（即满足 $l_1=r+1$），然后 $[l,r]\leftarrow[l_1,r_1]$，对 $[l_1,r_1]$ 进行标记；这样能获得不少的块并且答案已经很优。加上对 $k=1$ 的特判可以做到 $63\mathrm{pts}$：笔者考场上使用的是该做法，已经得到了一个非常可观的分数。

注：对于这种做法，如果对块内相邻元素连边，在整棵线段树上这些边就可以构成很多交叉的 X 型（读者可以自行理解一下）。

但是此时答案还不是最优的。考虑是否可以合并一些区间：我们观察到，对于一些左 / 右端点在正中间的作为右 / 左儿子进行处理的区间，是可以将它所在的块和同一层那个唯一可以合并的区间所在的块合并的。例如，$k=4$ 时，区间 $[7,8]$ 与区间 $[9,10]$ 所在的块可以合并。处理的过程中考虑一下这种情况。

事实上我们可以观察到，对于合并同一层的这种情况，我们只需处理 $[l,r]$ 满足 $r<2^k$ 且**作为右儿子**询问到的“**初始区间**”所在的块和它右边那个同层的且可合并的区间所在的块即可。证明显然。

询问块内元素的过程可以不用像其他题解一样用二分，因为我们观察到如果一个块的大小如果不超过 $2$，那么二分跟朴素做法的没有区别——实际上块越小两种做法的区别越小。又因为是按照 BFS 序从上往下问，感性理解一下就可以得知越往下问块越小而且数量越多。实测可以获得 $100\mathrm{pts}$。

如果不放心可以把所有块全部预处理出来然后按照块的大小降序排序询问。但是这个做法会在 $k=14$ 的时候超时，所以选用前者。

示例代码（$100\mathrm{pts}$）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int query(int,int);
pii solve(int k){
  vector<tuple<int,int,int,int> > q;
  function<void(int,int,int)> dfs=[&](int l,int r,int w){
    if(l==r)return;
    q.emplace_back(l,l+r>>1,w-1,0);
    q.emplace_back(l+r+1>>1,r,w-1,1);
    dfs(l,l+r>>1,w-1);
    dfs(l+r+1>>1,r,w-1);
  }; // 按照 BFS 序处理出所有区间遍历顺序，0/1 表示左 / 右儿子
  dfs(1,1<<k,k);
  set<pii> t; t.emplace(1,1<<k);
  vector<tuple<vector<pii>,int,int,int,int> > s;
  for(auto [l,r,w,b]:q){
    if(t.find(make_pair(l,r))==t.end()){
      vector<pii> v; int p=(b?l:r);
      for(int i=w-1;i>=0;i--){
        v.emplace_back(b?p-(1<<i):p+1,b?p-1:p+(1<<i));
        b?p-=(1<<i):p+=(1<<i);
      } // 处理块
      if(b){
        bool b2=false;
        if(r<(1<<k)){
          b2=true,p=r;
          for(int i=w;i>=0;i--){
            v.emplace_back(p+1,p+(1<<i));
            p+=(1<<i);
          }
        } // 可以与同一层的合并
        if(query(l-(1<<w)+1,b2?(r<<1)-l+(1<<w):r)){
          // 询问是否在整个区间，下同
          for(auto [l1,r1]:v)
            if(query(l1,r1))return make_pair(l1,r1);
          // 询问单个区间，下同
          return make_pair(l,r);
          // 不在上述区间就是最后一个，下同
        }
      }
      else if(query(l,r+(1<<w)-1)){
        for(auto [l1,r1]:v)
          if(query(l1,r1))return make_pair(l1,r1);
        return make_pair(l,r);
      }
      for(auto [l1,r1]:v)t.emplace(l1,r1);
      t.emplace(l,r); // 使用 std::set 打标记
    }
  }
  return make_pair(1,1<<k); // 都不是上述区间
}
```

---

## 作者：5ab_juruo (赞：8)

由于交互库自适应，所以先考虑如何覆盖线段树上所有节点。

性质 1：每一次线段树询问最多问到两个同一层的点；

性质 2：当询问有点在最左侧/最右侧时，该次询问最多只能问到一个同一层的点。

考虑最下面一层，共有 $2^k$ 个节点，除去根节点左边和右边共有 $2k$ 个节点，所以至少需要进行 $(2^k-2k)/2+2k+1=2^{k-1}+k+1$ 次询问，来覆盖所有线段树上的节点。

考虑递归构造，当 $k=1$ 时，只能每个节点问一次。假设我们找到了 $k-1$ 的询问集合，将两个这样的集合合并成 $k$ 时，要将中间的询问尽可能合并，可以省掉 $k$ 次询问。这样使用的区间数满足 $c_1=3,c_n=2c_{n-1}-n$，解得 $c_n=2^{n-1}+n+1$ 即为下界，满足要求。

然后注意几个事情：

1. 合并的时候最上面两个要交换，否则会让两边的根节点的询问连起来，这是不合法的；
2. 要注意询问的顺序，如果一次询问异常了需要定位到具体的节点。可以证明，按照覆盖节点个数倒序排序，直接枚举就是对的；
3. 注意汇报答案不算询问，所以只剩下一个点时可以直接汇报，少一次询问。

```cpp
const int max_k = 14, max_n = (1 << max_k);

struct rg
{
	int l, r, cnt;
	rg() { }
	rg(int _l, int _r, int _c) : l(_l), r(_r), cnt(_c) { }
};
int pl, pr;

void grc(int l, int r, vector<rg>& ls, vector<rg>& ms, vector<rg>& rs)
{
	if (l == r)
		return;
	if (r - l == 1)
	{
		ls.emplace_back(l, l, 1);
		rs.emplace_back(r, r, 1);
		return;
	}
	int mid = (l + r) >> 1;
	
	vector<rg> tl, tr;
	grc(l, mid, ls, ms, tl);
	grc(mid + 1, r, tr, ms, rs);
	
	ls.emplace_back(l, tr.rbegin()->r, tr.rbegin()->cnt + 1);
	rs.emplace_back(tl.rbegin()->l, r, tl.rbegin()->cnt + 1);
	
	for (int i = 0; i < tl.size() - 1; i++)
		ms.emplace_back(tl[i].l, tr[i].r, tl[i].cnt + tr[i].cnt);
}

bool qrd(int L, int R, int l, int r)
{
	if (L <= l && r <= R)
	{
		if (query(l, r))
		{
			pl = l, pr = r;
			return true;
		}
		return false;
	}
	int mid = (l + r) >> 1;
	
	if (L <= mid && qrd(L, R, l, mid))
		return true;
	return mid < R && qrd(L, R, mid + 1, r);
}

bool isinit = false;
vector<rg> m;
void init(int n)
{
	vector<rg> l, r;
	grc(1, n, l, m, r);
	m.insert(m.end(), l.begin(), l.end());
	m.insert(m.end(), r.begin(), r.end());
	
	sort(m.begin(), m.end(), [](const rg& a, const rg& b) {
		return a.cnt > b.cnt;
	});
}

pair<int, int> solve(int k)
{
	int n = 1 << k;
	
	if (!isinit)
	{
		init(n);
		isinit = true;
	}
	
	for (auto& q : m)
		if (query(q.l, q.r))
		{
			if (q.cnt == 1)
				pl = q.l, pr = q.r;
			else
				qrd(q.l, q.r, 1, n);
			return make_pair(pl, pr);
		}
	pl = 1, pr = n;
	return make_pair(pl, pr);
}
```

---

## 作者：_i_i_ (赞：3)

这是一篇感性理解的文章，仅作为考场思路。

令 $n=2^k$。

考虑画图，会发现 $[1,n]$ 这个区间询问一次只能得到这一个信息，非常的亏，于是考虑放到最后，如果下面没有 tag 就直接范围 $[1,n]$。

然后是 $\left[1,\dfrac n2\right]$ 和 $\left[\dfrac n2+1,n\right]$，询问操作少代表每一次询问的区间尽可能多，因此判断 $\left[1,\dfrac n2\right]$ 时可以向交互库询问 $[1,n-1]$，这样可以一次询问到 $k$ 个区间，非常划算，同理询问 $[2,n]$。

如果此时查询到了 tag，则使用二分在 $k$ 个区间中找到区间的具体位置然后范围，操作数为 $\lceil\log_2k\rceil$。

我们要尽可能在一次询问里询问多个区间，考虑按照下图蓝色区间来询问，区间覆盖了一个中线的两边尽可能多的点，感性理解这样子是非常优的，我们称这些区间为附加区间。

![](https://cdn.luogu.com.cn/upload/image_hosting/eec9c5uy.png)

接下来考虑 $\left[1,\dfrac n{2^d}\right]$、$\left[n-\dfrac n{2^d}+1,n\right]$ 这些区间（上图中紫色和粉色和棕色），由于这些区间靠边，因此我们只能取尽可能靠近中心的询问区间。

如果一个区间他不靠边，则可以证明他一定是被上方某个单方向区间包括或者是附加区间，~~证明我不会，但是看起来很对~~。

总之我们就这样枚举完了所有的区间，注意不要将二分的次数放到后面，防止二分查询次数超过了普通查询限制，也就是小的询问区间要尽可能后面询问。

~~不会考虑询问次数，但看起来确实是对的~~。

具体实现（分治，二分）可以看代码（其实不难实现）。

```cpp
#include <utility>
#include <cstdio>
int query(int, int);
std::pair<int, int> getl(int l, int r) {
	int dep = 0, L = r - l + 1; while (L != 1) dep++, L >>= 1;
	int ll = 0, rr = dep;  while (ll < rr) {
		int mid = (ll + rr + 1) >> 1; if (query(l - (r - l + 1) + (1 << mid), r)) ll = mid; else rr = mid - 1;
	}
	return {l - (r - l + 1) + (1 << ll), l - (r - l + 1) + (1 << (ll + 1)) - 1};
}
std::pair<int, int> getr(int l, int r) {
	int dep = 0, L = r - l + 1; while (L != 1) dep++, L >>= 1;
	int ll = 0, rr = dep; while (ll < rr) {
		int mid = (ll + rr + 1) >> 1; if (query(l, r + (r - l + 1) - (1 << mid))) ll = mid; else rr = mid - 1;
	}
	return {r + (r - l + 1) - (1 << (ll + 1)) + 1, r + (r - l + 1) - (1 << ll)};
}
std::pair<int, int> svl(int l, int r) {
	int len = r - l + 1;
	int p = query(l - len + 1, r); if (p) return getl(l, r);
	else return {-1, -1};
}
std::pair<int, int> svr(int l, int r) {
	int len = r - l + 1;
	int p = query(l, r + len - 1); if (p) return getr(l, r);
	else return {-1, -1};
}
int NN;
std::pair<int, int> sv(int l, int r, int op1, int op2) {
//	printf("sv %d %d %d %d\n", l, r, op1, op2);
	int mid = (l + r) >> 1; std::pair<int, int> ans; 
	if (op1) {
		ans = svr(l, mid); if (ans.first != -1) return ans;
	}
	if (op2) {
		ans = svl(mid + 1, r); if (ans.first != -1) return ans;
	}
	if (l == r - 1) return {-1, -1};
	// X from here
	int dep = 0, L = r - l + 1; while (L != 1) dep++, L >>= 1;
	for (int i = dep - 3; ~i; i--) {
//		printf("mid i %d\n", i);
		if (query(mid - (1 << (i + 1)) + 2, mid + (1 << (i + 1)) - 1)) {
			if (query(mid - (1 << (i + 1)) + 2, mid)) return getl(mid - (1 << i) + 1, mid);
			else return getr(mid + 1, mid + (1 << i));
		}
	}
	ans = sv(l, mid, l == 1, 0); if (ans.first != -1) return ans;
	ans = sv(mid + 1, r, 0, r == NN); return ans;
}
std::pair<int, int> solve(int k) {
	NN = 1 << k; std::pair<int, int> ans= sv(1, NN, 1, 1);
	if (ans.first == -1) return {1, NN}; else return ans;
}
```

---

## 作者：sunzz3183 (赞：2)

# P9683 A Certain Forbidden Index 题解

## 题意

交互题

给定一个 $k$，对于一个长度为 $2^k$ 的序列建立一棵线段树。

有一个节点被标记了，现在你需要通过区间询问找到这个节点。

询问方法：像线段树一样，询问的是有返回值的的节点，返回有没有被标记的节点，比如：

当 $k=2$ 时，$[1,1]$ 被标记，询问 $[1,3]$ 即询问节点 $[1,2],[3,3]$ 返回值为 $0$，询问 $[1,1]$ 返回值为 $0$。

## 分析

首先 $[1,2^k]$ 不用询问，把下面的都询问完答案如果没有标记，答案显然是 $[1,2^k]$。

显然一次询问能询问的节点个数最多，且每次询问不重复是最优的。

假设一次询问返回 $1$ ，那么可以通过二分来 $\log$ 次找到答案，如下：

```cpp
inline pair<int,int> Getans(){
    int l=0,r=vt.size()-1;
    while(l<r){
        int mid=(l+r)>>1;
        if(query(vt[l].first,vt[mid].second))r=mid;
        else l=mid+1;
    }
    return vt[l];
}
```

然后考虑如何使节点个数最多，容易想到是找到一段区间节点长度构成为这样：

$$2^i,2^{i-1},2^{i-2},\dots,1$$

然后对着 $2^4$ 手模一下，可以得到这样一张图（每种颜色代表一种询问）：

![](https://cdn.jsdelivr.net/gh/sunzz3183/szzphoto@img/img/202312011550269.png)

注意，图中一些相邻询问可以连接起来，比如图中粉色，灰色等部分。

然后观察规律，发现每一段的特点是：

1. 若不是连接起来的询问，最大的点一定是最左或最右，可以通过递推求得每一个节点的左右端点，且最大点的层数如果是 $i$，那么询问遍历到的点的个数一定是 $k+1-i$。

2. 若是连接起来的，可以分别考虑两个相邻的最大点，转化为特点 $1$，点个数为 $2(k+1-i)$。

但是还有个问题。

发现找到区间进行二分的时候，节点个数少的区间二分次数一定会更少（废话。

那么会产生什么影响呢？假设我们把所有区间都询问，最后的询问是节点个数最多的，那么就会比最后的询问是节点个数最少的多出近一个 $\log$，所以我们要将每次询问的节点个数从大到小排序后排序（也可以通过特定的顺序询问）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int query(int, int);
int nnn,kkk;
pair<int,int>ans;
vector<pair<int,int> >vt;
inline void lft(int l,int r,int len){
    vt.push_back({l,r});
    if(len==1)return;
    r=l-1;len>>=1;l=r-len+1;
    lft(l,r,len);
    return;
}
inline void rght(int l,int r,int len){
    vt.push_back({l,r});
    if(len==1)return;
    l=r+1;len>>=1;r=l+len-1;
    rght(l,r,len);
    return;
}
inline pair<int,int> Getans(){
    int l=0,r=vt.size()-1;
    while(l<r){
        int mid=(l+r)>>1;
        if(query(vt[l].first,vt[mid].second))r=mid;
        else l=mid+1;
    }
    return vt[l];
}
struct node{
    int l,r,d,cnt,id;
};
vector<node>num;
inline void Main(){
    for(int d=1ll<<(kkk-1),i=kkk;d;i--,d>>=1){
        num.push_back({1,d,d,i,1});
        num.push_back({nnn-d+1,nnn,d,i,2});
        for(int l=d*3+1,r=5*d;r<=nnn;l+=d*4,r+=d*4)
            num.push_back({l,r,d,i<<1,3});
    }
    sort(num.begin(),num.end(),[](node x,node y){return x.cnt>y.cnt;});
    return;
}
pair<int,int> solve(int k){
    num.clear();
    kkk=k;
    nnn=1ll<<k;
    Main();
    for(node i:num){
        if(i.id==3){
            int mid=(i.l+i.r)>>1;
            vt.clear();
            lft(i.l,mid,i.d);reverse(vt.begin(),vt.end());
            rght(mid+1,i.r,i.d);
            if(query(vt[0].first,vt.back().second))return Getans();
        }
        else if(i.id==1){
            vt.clear();
            rght(i.l,i.r,i.d);
            if(query(vt[0].first,vt.back().second))return Getans();
        }
        else if(i.id==2){
            vt.clear();
            lft(i.l,i.r,i.d);reverse(vt.begin(),vt.end());
            if(query(vt[0].first,vt.back().second))return Getans();
        }
    }
    return {1,nnn};
}
```


---

