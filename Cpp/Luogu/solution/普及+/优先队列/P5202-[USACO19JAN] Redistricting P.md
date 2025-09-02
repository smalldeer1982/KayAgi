# [USACO19JAN] Redistricting P

## 题目背景

USACO 19 年一月月赛铂金组第一题。

## 题目描述

奶牛们的特大城市，牛都，要进行重新分区了！——这总是一个在居住在这里的两大主要种族（荷斯坦牛和更赛牛）之间富有争议的政治事件，因为两大种族都想要在牛都政府中保持足够的影响力。

牛都的大都市圈由一列 $n$ 块牧草地组成，每块里有一头奶牛，均为荷斯坦牛 (Holstein) 和更赛牛 (Guernsey) 之一。

牛都政府想要将大都市圈划分为若干个连续的区，使得每个区至少包含一块牧草地且至多包含 $k$ 块牧草地，并且每块牧草地恰好属于一个区。由于政府当前由荷斯坦牛控制，她们想要找到一种分区方式能够最小化更赛牛较多或者均势的区的数量（如果更赛牛的数量与荷斯坦牛的数量相等那么这个区就是均势的）。

有一个关心政治的更赛牛团体想要知道政府的分区计划可能会对她们造成多少损害。帮助她们求出最坏情况，也就是更赛牛较多或是均势的区的最小可能的数量。

## 说明/提示

### 样例解释

一种可能的划分方式是 $[1],~[2, 3],~[4, 5],~[6, 7]$。第二、四个区是均势的区，第三个区是更赛牛优势的区。

### 数据范围

对于 $100\%$ 的数据，保证 $1 \leq k \leq n \leq 3 \times 10^5$，$s$ 的长度为 $n$，且只含字符 `H` 和 `G`。

## 样例 #1

### 输入

```
7 2
HGHGGHG```

### 输出

```
3```

# 题解

## 作者：梧桐灯 (赞：15)

这里用单调队列实现，~~吊打堆~~，时间复杂度只需O(n)

首先看到此题想到DP。容易得出下面的式子：

记$sum[i]$为$1$ ~ $i$ 中$H$的个数减去$G$的个数

$$f[i] = min \left\{f[j] + (sum[i] - sum[j] <= 0)\right\}$$

$$(i - j <= k)$$

由于枚举j肯定要超时，我们想到用数据结构来维护DP

如果没有$(sum[i] - sum[j] <= 0)$这个东西，我们很容易想到用单调队列来维护，但加上后面这个呢？由于它不是1就是0，而且$sum[i]$值固定，那我们可以分类讨论：

对于$ \forall p, q $ ($p, q$满足转移条件)：

若$f[p] \neq f[q]$，则我们肯定把小的放队首，因为即使它要加1也一定不会劣于另一个

若$f[p] = f[q]$, 则我们把$sum$小的放队首，这样拿$sum[i]$减后才更可能不小于0

有了以上推论&细节~~&卡常~~，你就不仅能AC，~~RP好还能进入最优解第一面（女装有益减小常数QwQ）~~

以下是代码（131ms）

```cpp
#pragma GCC optimize ("Ofast")
#include <cstdio>
using namespace std;

inline void read (int& s) {
	s = 0;
	static char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c & 15), c = getchar ();
	return ;
}

const int N = 300007;
int n, k, f[N], sum[N];
int Q[N], H, T;

int main () {
	read (n), read (k);
	register int i; for (i = 1; i <= n; ++i) sum[i] = sum[i - 1] + (getchar () == 'H' ? 1 : -1);
	Q[T++] = 0; //刚开始前0头牛答案为0
	for (i = 1; i <= n; ++i) {
		while (H < T && i - Q[H] > k) ++H; //单调队列的出队操作
		f[i] = f[Q[H]] + (sum[i] - sum[Q[H]] <= 0);
		while (H < T) {
			if (f[i] < f[Q[T - 1]] || (f[i] == f[Q[T - 1]] && sum[i] < sum[Q[T - 1]])) --T;
			else break;
		} //入队操作，注意一下细节
		Q[T++] = i;
	}
	printf ("%d\n", f[n]);
	return 0;
}

```

~~个人觉得单调队列好写，好记，好快，为什么还用堆来维护呢~~

---

## 作者：荣耀火影 (赞：7)

在做这道题之前，建议大家可以先看一下[台阶问题](https://www.luogu.org/problemnew/show/P1192)这道题。            
~~看完之后大家可有什么启发呢?~~  
## DP方程
应该可以看出来这题和台阶问题很像，也是一个动态规划的题，且DP方程也十分相似，但是本题我们需要考虑一下如何存储数据。         
我们可以用一个前缀和来存储，$pre[i]$表示从第$1$个牧草地到第$i$个牧草地哪种牛的占有牧草地的数量多，我是这样的：若$pre[i]>0$，则表示荷斯坦牛比更赛牛数量多；若$pre[i]==0$,则表示均势；若$pre[i]<0$，则表示更赛牛比荷斯坦牛数量多。           
于是我们就可以写出$DP$方程了——                
### $dp[i]=min(dp[i],dp[i-j]+(pre[i]-pre[i-j]<=0));$
（$dp[i]$是$[1,i]$的答案，$1<=j<=k$且$j<=i$）           
## 堆（优先队列）优化
很明显，以上方法的时间复杂的是$O(nk)$的，对于这题来说会超时，只能过$7$个点，可是这题$18$个点。。。。。。            
~~下面我就来考虑一下如何用数据结构来提高本题的程序运行效率。~~       
其实，在用以上的方法时我们每次都取的是$dp[i-j]+(pre[i]-pre[i-j]<=0)$的最小值，于是自然想到可以用一个**双关键字的小根堆**来维护$dp[i-j]+(pre[i]-pre[i-j]<=0)$的最小值，一个关键字维护$dp$的最小值，另一个关键字存储这个$dp$值所在的位置$i$。                       
我们知道$pre[i]-pre[i-j]<=0$的值只有可能是$1$或$0$，所以我们应优先维护$dp$最小值，在$dp$值相同的情况下维护$pre$的最小值（$pre[i-j]$越小，$pre[i]-pre[i-j]$的值越大）。           
于是我们的$DP$方程就变成了——                
### $dp[i]=pre[i]-pre[q.top().y]<=0?q.top().x+1:q.top().x;$    
（各字母代表什么将在以下程序中体现）         
现在时间复杂度就是$O(n⋅logk)$，~~时间上面轻轻松松跑过去呀~~。
#### 最后提醒一下初始化：$dp$数组中的每一个数要赋值成一个很大的数，$pre$数组的每一个数要赋值成$0$，先将下标$0$的值压到堆里去，也就是先压进去一个$(0,0)$。~~（原因不用我说吧）~~    
```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
int n,k,pre[300001],dp[300001];
string s;
struct hhh
{
    int x,y;
    bool operator<(const hhh &t) const
    {
        if(x==t.x) return pre[y]>pre[t.y];
        else return x>t.x;
    }
}p;
priority_queue<hhh>q;//双关键字小根堆。
int main()
{
    cin>>n>>k>>s;
    for(int i=n;i>=1;i--) s[i]=s[i-1];
    //求前缀和。
    for(int i=1;i<=n;i++) 
    pre[i]=s[i]=='H'?pre[i-1]+1:pre[i-1]-1;
    memset(dp,0x3f,sizeof(dp));
    dp[0]=0; 
    p.x=0; p.y=0; q.push(p);
    for(int i=1;i<=n;i++)
    {
     //如果最小值的位置过于靠前，就要把它弹掉。
        while(q.top().y<i-k) q.pop();
        dp[i]=pre[i]-pre[q.top().y]<=0?q.top().x+1:q.top().x;
     //将新出现的值压到堆中。
        p.x=dp[i]; p.y=i;
        q.push(p);
    }
    cout<<dp[n];
    return 0;
}
```


---

## 作者：1saunoya (赞：6)

给个不动脑子的做法，数据结构也不用写。

$f_i = \min\{f_j + s_i \leq s_j \} [i-j+1\leq k]$

考虑和回滚莫队一样，$k \leq B$ 的时候暴力转移复杂度 $nB$。

如果 $k > B$，那么拆成若干段，然后右指针一定是单调增的，左边 $B$ 暴力即可，而且跑不满的样子，因为可以对之前的操作回退，后面部分可以用一个块状的东西，直接整块更新，查询的时候直接查一整块，所以复杂度就是 $\frac{n}{B} \times n + nB$。


补一个单调队列的做法吧，看懂了。

考虑把 $f_i$ 小的放在队首，因为每次的贡献只有 $1$，然后每次 $s_i$ 小的是第二关键字，搞搞就做完了。

---

## 作者：fysbb (赞：6)

首先思考如何存储数据，可以用一个前缀和存储，读到 $ H $ 就 $ +1 $ ， 读到 $ G $ 就 $ -1 $ 。

因为当前位置的答案可由之前的答案扩张得到，所以可以动态规划。

设 $ dp[i] $ 为区间 $ [1,i] $ 的答案，状态转移可以写成：

$ dp[i]=min(dp[i-j]+1,dp[i]) , f[i]-f[i-j]<=0 $

$ dp[i]=min(dp[i-j],dp[i]) , f[i]-f[i-j]>0 $

$ j \in [1,k] $

这样的转移方程时间复杂度为 $ O(n \cdot k) $ 

考虑优化此方程，因为每次转移时都要找最小值，所以可以用一个小根堆维护。但这个小根堆要同时维护两个关键字，分别为 $ dp $ 和 $ f $ 的值，要求：

$ heap[i].dp<heap[j].dp $ 或 $ heap[i].dp=heap[j].dp \ \ \ \ \ and \ \ \ \ \ heap[i].f<heap[j].f $

$ j $ 为 $ i $ 的儿子节点。

之后每次状态转移时，使用堆顶元素转移即可。时间复杂度 $ O(n \cdot \log k) $

```cpp
program redistricting;

type tp=record
  a,loc:longint;
end;

var
   f:array[0..300005]of longint;
   heap:array[0..300005]of tp;
   n,m,tot:longint;

function min(a,b:longint):longint;
begin
  if a<b then exit(a)
    else exit(b);
end;

procedure re;
var i:longint;
    s:ansistring;
begin
  readln(s);
  for i:=1 to n do begin
    if s[i]='H' then inc(f[i])
      else dec(f[i]);
    inc(f[i],f[i-1]);
  end;
end;

procedure push(q,p:longint);
var i,j:longint;
    t:tp;
begin
  inc(tot);
  heap[tot].a:=q;
  heap[tot].loc:=p;
  i:=tot;
  while i shr 1<>0 do begin
    j:=i shr 1;
    if (heap[j].a>heap[i].a) or ((heap[j].a=heap[i].a) and (f[heap[j].loc]>f[heap[i].loc])) then begin
      t:=heap[i];
      heap[i]:=heap[j];
      heap[j]:=t;
    end
      else exit;
    i:=j;
  end;
end;

procedure del;
var i,j:longint;
    t:tp;
begin
  heap[1]:=heap[tot];
  dec(tot);
  i:=1;
  while i shl 1<=tot do begin
    j:=i shl 1;
    if (j+1<=tot) and ((heap[j].a>heap[j+1].a) or ((heap[j].a=heap[j+1].a) and (f[heap[j].loc]>f[heap[j+1].loc]))) then inc(j);
    if (heap[i].a>heap[j].a) or ((heap[i].a=heap[j].a) and (f[heap[i].loc]>f[heap[j].loc])) then begin
      t:=heap[i];
      heap[i]:=heap[j];
      heap[j]:=t;
    end
      else exit;
    i:=j;
  end;
end;

procedure main;
var i,j:longint;
    dp:array[0..300005]of longint;
begin
  fillchar(dp,sizeof(dp),$5f);
  for i:=1 to 300005 do heap[i].a:=maxint;
  dp[0]:=0;
  push(0,0);
  for i:=1 to n do begin
    while heap[1].loc<i-m do del; 
    if f[i]-f[heap[1].loc]<=0 then dp[i]:=min(dp[i],heap[1].a+1)
      else dp[i]:=min(dp[i],heap[1].a);
    push(dp[i],i);
  end;
  writeln(dp[i]);
end;

begin
  readln(n,m);
  re;
  main;
end.

```

---

## 作者：CatFromMars (赞：3)

喜提最劣解，题解区似乎没人写这么臭的做法。。。过来纪念一下（大雾

我们容易写出方程，设 $f(i)$ 为前 $1\sim i$ 中划分出的最少数量，$S_i$ 代表 $1\sim i$ 中 ```G``` 出现次数。那么 $f(i) = \min_{j = \max\{0, i - k\}}^{i - 1}\{f(j) + [S(i) - S(j) \ge \dfrac{i - j}{2}]\}$。这是 $O(n^2)$ 的式子，考虑如何优化。

$[S(i) - S(j)] \ge \dfrac{i - j}{2}$，我们分离一下 $i,j$，变成 $[2S(i) - i \ge 2S(j) - j]$ 的形式。如果我们记 $B(i) = 2S(i) - i$，那么 $f(i) = \min_{j = \max\{0, i - k\}}^{i-1}\{f(j) + [B(i) \ge B(j)]\}$。

进一步抽象出来，我们考虑有 $n$ 个三元组 $(i, f(i), B(i))$。对于 $f(i)$ 的转移，我们可以把 $\forall j\in[\max(0, i - k), i - 1]$ 的 $(j, f(j), B(j))$ 按照 $B(j) \le B(i)$ 划分成两个集合 $A,B$。记 $A$ 集合中的最小 $f(j)$ 为 $a$，$B$ 集合中的最小 $f(j)$ 为 $b$。那么 $f(i) = \min\{a+1, b\}$。

按照 $B(j) \le B(i)$ 划分，容易想到线段树——以 $B(i)$ 为下标，$f(i)$ 为权值。那么这样只需要区间查询即可得到 $A,B$ 的最小值了。插入新元素也很简单。但是怎么保证 $j \in [\max(0, i - k), i - 1]$ 呢？换句话说，怎么样删除元素呢？

于是我们考虑对于每个 $B$ 开一个堆，小根堆里面是这个三元组，以 $f$ 为关键字。当我们删除的时候采用懒惰删除，每次取出堆头。记当前 $0\sim delta$ 都被删除了。如果堆头的 $i$ 小于等于 $delta$，那么就把堆头弹出，否则不变。最后在线段树上更新即可。

由于 $B$ 的值域是 $[-n, n]$ 的，每个三元组只会被删除一次。所以时间复杂度是 $O(n\log_2 n)$的。但是常数非常非常大，所以喜提最劣解，大家看个乐子就好（

代码有点丑，见谅 qwq
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5;
int f[N + 10], qz[N + 10], n, qk;
struct node {
	int ind, val;
	bool operator < (const node &other) const {
		return val > other.val;
	}
};
priority_queue <node> que[N * 2 + 10];
int delta = -1;
int tot = 0, rt;
struct seg {
	int ls, rs;
	int cmin;
} T[N * 23 + 10];
void push_up(int now) {
	T[now].cmin = min(T[T[now].ls].cmin, T[T[now].rs].cmin);
}
int ins(int pos, int s, int t, int now, int ind) {
	if(!now) {
		now = ++tot;
		if(!rt) rt = tot;
		T[now].ls = T[now].rs = 0;
	}
	if(s == t) {
		que[s + N].push((node){ind, f[ind]});

		while(!que[s + N].empty()) {
			node tp = que[s + N].top();
			if(tp.ind <= delta)
				que[s + N].pop();
			else break;
		}
		T[now].cmin = que[s + N].top().val;
		return now;
	}
	int mid = (s + t) >> 1;
	if(pos <= mid) T[now].ls = ins(pos, s, mid, T[now].ls, ind);
	else T[now].rs = ins(pos, mid + 1, t, T[now].rs, ind);
	push_up(now);
	return now;
}
int del(int pos, int s, int t, int now) {
	if(!now) {
		now = ++tot;
		if(!rt) rt = tot;
		T[now].ls = T[now].rs = 0;
		T[now].cmin = 0x3f3f3f3f;
	}
	if(s == t) {
		while(!que[s + N].empty()) {
			node tp = que[s + N].top();
			if(tp.ind <= delta)
				que[s + N].pop();
			else break;
		}
		if(!que[s + N].empty())
			T[now].cmin = que[s + N].top().val;
		else T[now].cmin = 0x3f3f3f3f;
		return now;
	}
	int mid = (s + t) >> 1;
	if(pos <= mid) T[now].ls = del(pos, s, mid, T[now].ls);
	else T[now].rs = del(pos, mid + 1, t, T[now].rs);
	push_up(now);
	return now;
}
int qry(int ql, int qr, int s, int t, int now) {
	if(!now) return 0x3f3f3f3f;
	if(ql <= s && t <= qr) return T[now].cmin;
	int mid = (s + t) >> 1, rest = 0x3f3f3f3f;
	
	if(ql <= mid) rest = min(rest, qry(ql, qr, s, mid, T[now].ls));
	if(qr > mid) rest = min(rest, qry(ql, qr, mid + 1, t, T[now].rs));
	return rest;
}


int main() {
	T[0].ls = T[0].rs = 0;
	T[0].cmin = 0x3f3f3f3f;

	cin >> n >> qk;
	for(int i = 1; i <= n; i++) {
		char x; cin >> x;
		if(x == 'G') qz[i] = qz[i - 1] + 1;
		else qz[i] = qz[i - 1];
	}

	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	ins(0, -N, N, rt, 0);
	for(int i = 1; i <= n; i++) {
		if(i > qk) {
			delta = i - qk - 1;
			del(2 * qz[i - qk - 1] - (i - qk - 1), -N, N, rt);
		}
		int w = 2 * qz[i] - i;

		f[i] = min(qry(-N, w, -N, N, rt) + 1, qry(w + 1, N, -N, N, rt));
		ins(w, -N, N, rt, i);
	}
	cout << f[n] << endl;
}
```

---

## 作者：Martin_MHT (赞：3)

好久没有水题解了，让我来写一波大家都没想到的傻子线段树做法

首先是数据的输入与存储，这个前面的大佬已经讲得很好了，具体就是把一个变成$1$一个变成$-1$，做一个前缀和。
我这里是$G$对应1。

设$f_i$表示解决了$1$~$i$的分组之后的最小答案  
那么就可以写出一个~~是个人都能想到的~~状态转移
$$f_i = min\{f_j+[sum_i>=sum_j]\}$$
其中呢$i-k<=j<i$

胡乱分析一下这个可爱的式子，$j$能够对$i$产生贡献首先要满足上面的范围，其次贡献的值只会是$f_j$或者$f_j+1$  
思考一下，我们通过枚举保证了$j$能够转移，那么怎么维护这个$+1$的波动呢？


发现$sum$数组是不会变的，于是可以把它排个序。  
那么就可以在排序后的$sum$数组里面，二分求出当前$sum$值的分界点，即：在这个分界点左侧（包括分界点）的所有$sum$值都是小于等于当前的$sum$值的，所以在左侧的区间所有的$f$值都是要加上$1$的，右区间同理，不用加上$1$。

然后就可以用可爱的线段树来维护分界点左右两侧的$f$的最小值，以此更新当前的$f$值辣！！别忘记删除和更新哦！

```cpp
#include <cstdio>
#include <algorithm> 
#define N 300010
#define gc getchar
#define int long long
#define INF 0x3f3f3f3f3f3f3f3fll 
#define fo(i, a, b) for(int i = (a); i <= (b); ++i)
using namespace std;
int n, k, a[N], tt[N], tp[N], f[N];
int tree[N << 3];
struct Newnode
{
	int id, a;
	bool operator<(const Newnode b) const
	{
		return a < b.a;
	}
}aa[N];
inline int min(int a, int b){return a < b ? a : b;}
inline int ls(int t){return t << 1;}
inline int rs(int t){return t << 1 | 1;}
inline void pushup(int t){tree[t] = min(tree[ls(t)], tree[rs(t)]);}
void build(int t, int l, int r)
{
	if(l == r)
	{
		tree[t] = INF;
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls(t), l, mid);
	build(rs(t), mid + 1, r);
	pushup(t);
}
int query(int t, int l, int r, int fl, int fr)
{
	if(fl > fr)	return INF;
	if(fl <= l && r <= fr)
		return tree[t];
	int mid = (l + r) >> 1, res = INF;
	if(fl <= mid)	res = min(res, query(ls(t), l, mid, fl, fr));
	if(fr > mid)	res = min(res, query(rs(t), mid + 1, r, fl, fr));
	return res;
}
void update(int t, int l, int r, int w, int v)
{
	if(w < l || w > r)	return ; 
	if(l == r)
	{
		tree[t] = v;
		return ;
	}
	int mid = (l + r) >> 1;
	if(w <= mid)	update(ls(t), l, mid, w, v);
	else update(rs(t), mid + 1, r, w, v);
	pushup(t);
}
signed main()
{
	freopen("redistricting.in", "r", stdin);
	freopen("redistricting.out", "w", stdout);
	scanf("%lld %lld", &n, &k);
	fo(i, 1, n)
	{
		char ch = gc();
		while(ch != 'H' && ch != 'G')	ch = gc();
		a[i] = (ch == 'G' ? 1 : -1) + a[i - 1];
		tp[i] = a[i];
		aa[i].a = a[i]; aa[i].id = i;
	}
	sort(aa + 1, aa + n + 1);
	fo(i, 1, n)	a[i] = aa[i].a, tt[aa[i].id] = i;
	build(1, 1, n);
	fo(i, 1, n)
	{
		if(i > k + 1)
			update(1, 1, n, tt[i - k - 1], INF);
		f[i] = INF;
		int w = upper_bound(a + 1, a + n + 1, tp[i]) - a - 1;
		int lt = query(1, 1, n, 1, w), rt = query(1, 1, n, w + 1, n);
		f[i] = min(lt + 1, rt);
		if(i <= k)
			f[i] = min(f[i], tp[i] >= 0);
		update(1, 1, n, tt[i], f[i]);
	}
	printf("%lld", f[n]);
	return 0;
}
```

---

## 作者：XGTD (赞：2)

# P5202 [USACO19JAN] Redistricting P 题解

## Preface
第一次写 USACO 白金的题解。

这道比起同一场另外两道简单多了，我明明在准备一月份银组，模拟赛非要打白金，~~被虐的只有这一道会。~~

## Problem Statement
[p5202](https://www.luogu.com.cn/problem/P5202) 奶牛也搞杰里蝾螈 gerrymandering。

## Solution
首先一眼 DP，$f_i$ 表示前 $i$ 个位置至少有几个更赛牛或平局的选区。每次枚举上次在哪里分区，进行转移。有方程
$$
f_i = \min\{f_j + (diff_i \leq diff_j)\} (j \geq i - k)
$$
$diff_i$ 为前 $i$ 个位置荷斯坦牛数量总和与更赛牛数量总和之差。

但是！直接转移复杂度 $O(nk)$ 无法接受，~~十八个点我过了十三个~~需要优化。发现如果没有第二项也就是 $diff_j$，可以非常容易地用单调队列或者二叉堆（优先队列）维护。

此时发现其实第二项的影响非常有限，最多造成一的贡献，因此其实还是可以用上述两个数据结构维护的，只需要用 $diff_j$ 做第二关键字就行了，因为他最多让总数少一，别人如果 $f$ 比他小的话，加了一也不会更劣。

这里我选用比较慢~~但比较好写~~的优先队列（二叉堆）维护。

## Code

```cpp
/*
too easy for plats!
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
//good habit
int n, k, f[300005], diff[300005];
string s;
struct node{
	int x, y;
};
bool operator < (const node &a, const node &b){
	if(a.x != b.x)return a.x > b.x;
	else return diff[a.y] > diff[b.y];
	//use diff as second and f as first
}
signed main(){
//	freopen("redistricting.in", "r", stdin);
//	freopen("redistricting.out", "w", stdout);
	cin>>n>>k;
	cin>>s;
	for(int i = 1; i <= n; i++){
		diff[i] = diff[i - 1];
		if(s[i - 1] == 'G')diff[i]--;
		else diff[i]++;
	}
	priority_queue< node > q;
	node fir;
	fir.x = 0;
	fir.y = 0;
	q.push(fir);
	for(int i = 1; i <= n; i++){
		int j = q.top().y;
		while(j < (i - k)){
			//out of range
			q.pop();
			j = q.top().y;
		}
		int val = f[j];
		f[i] = val + (diff[i] <= diff[j]);
		node now;
		now.x = f[i];
		now.y = i;
		q.push(now);
	}
	cout<<f[n]<<endl;
	return 0;
}
```

## Result
[Result](https://www.luogu.com.cn/record/196891255)
近几年 USACO 难度增加太快了，~~要是都向一九年这场一样简单就好了。~~

---

## 作者：lam_dyr (赞：1)

数据结构优化 dp 好题。

## 题意

将一个由 $H$ 和 $G$ 组成的字符串划分成多个连续区间，每个区间长度在 $1$ 到 $k$ 之间。最小化 $G$ 数量大于等于 $H$ 数量的区间个数。

## 思路

本题暴力 dp 很容易想到，在此不过多赘述。~~会 T 到飞。~~

[提交记录](https://www.luogu.com.cn/record/197296535)

考虑优化。

本题的核心思想是将字符串划分成最少的不满意区间，优化的关键就是不满意区间的判断和寻找最优的划分方式。

$dp_i$ 表示前 $i$ 个字符的最小不满意区间数。

优化方式：

- 利用前缀和 $sum_i$ 快速计算任意区间内 $H$ 和 $G$ 的数量差，用于判断区间是否不满意。
- 由于前缀和具有单调性，可以用单调队列存储可能成为最优解的下标 $j$，用于快速计算 $dp_i$，也就是寻找最优的划分方式。

具体步骤：

- 计算 $sum_i$，初始化 $dp$ 数组为 `INF`，$dp_0=0$。
- 维护单调队列
  - 移除队首 `q[head]` 中不满足 `q[head]<i-k` 的元素，因为这些元素已经不在当前窗口 $[i-k,i-1]$ 内。
  - 从队尾移除 $dp_j$ 大于等于 $dp_i$，且 $sum_j$ 大于等于 $sum_i$ 的 $j$。
- 将 $i$ 加入队列。
- 最后 $dp_n$ 就是答案。

单调队列关键：

- 存储下标 $j$，而不是值。
- 保证队列中 $dp_j$ 递增，$sum_j$ 在 $dp_j$ 相等时递减。
- 队头元素是当前窗口内，最有可能得到最小 $dp_j$ 的 $j$。

时间复杂度 $O(n)$。~~比优先队列快。~~

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=300005;
const int INF=1e9;
int sum[N],dp[N];
int q[N];
int head,tail;
int n,k;
string s;
int main() {
    cin>>n>>k;
    cin>>s;
    for(int i=1;i<=n;++i) 
        sum[i]=sum[i-1]+(s[i-1]=='H'?1:-1);
    for(int i=0;i<= n;++i) 
        dp[i]=INF;
    dp[0]=0;
    q[tail++]=0;
    for(int i=1;i<=n;++i){
        while(head<tail && q[head]<i-k){
            head++;
        }
        dp[i]=dp[q[head]]+(sum[i]-sum[q[head]]<=0);
        while(head<tail){
            int j=q[tail-1];
            if (dp[j]>dp[i] || (dp[j]==dp[i] && sum[j]>=sum[i])) 
                tail--;
			else 
                break;
        }
        q[tail++] = i;
    }
    cout<<dp[n];
    return 0;
}

```

---

## 作者：Frozen_Ladybug (赞：1)

求代表更赛牛较多或者优势区的最小可能数量，考虑使用动态规划。令 $dp[v]$ 表示区间 $s[0,1,\dots,v-1]$ 中最优的个数。

当且仅当 $s[i,i+1,\dots,j-1]$ 有至少一半为更赛牛时，让 $c_{ij}=1$，否则为 $0$。

则对于 $dp$ 数组，有如下的递推式：

$$dp[j]=\displaystyle\min_{\max(0,j-K)\le i\le j-1}(dp[i]+c_{ij})$$

当我们让 $p[i]$ 等于在区间 $[0,s-1]$ 上两种牛数量之差时，有

$$c_{ij}=\begin{cases}
1,\text{ if }p[i]\le p[j]\\
0,\text{ if }p[i]>p[j]
\end{cases}$$

这样 $c_{ij}$ 可以通过 $p$ 数组以 $\Omicron(1)$ 的复杂度计算。这种解法的复杂度为 $\Omicron(NK)$。

但对于 $\forall i,j,0\le c_{ij}\le1$，故

$$\displaystyle\min_{\max(0,j-K)\le i\le j-1}(dp[i])+1\ge dp[j]\ge\displaystyle\min_{\max(0,j-K)\le i\le j-1}(dp[i])$$

所以只需检查是否存在某个 $i$，使得这个关系式

$$dp[i]+c_{ij}=\displaystyle\min_{\max(0,j-K)\le i\le j-1}(dp[i])$$

成立即可。

所以考虑用一个 ```multiset``` 数组储存 $dp[i]$ 的所有可能值，再用一个映射将 $dp$ 数组和 $pre$ 数组建立联系即可。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[300001]={0},pre[300001]={0};
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]=='H') pre[i+1]=pre[i]+1;
        else pre[i+1]=pre[i]-1;
    }
    multiset<int> val;
    val.insert(0);
    multiset<int> t[300001]; 
    t[0].insert(0);
    for(int i=1;i<=n;i++){
        int u=*(val.begin());
        if(*t[u].begin()<pre[i]) dp[i]=u;
        else dp[i]=u+1;
        val.insert(dp[i]);
        t[dp[i]].insert(pre[i]);
        if(i>=k){
            val.erase(val.find(dp[i-k]));
            t[dp[i-k]].erase(t[dp[i-k]].find(pre[i-k]));
        }
    }
    printf("%d\n",dp[n]);
    return 0;
}
```

---

## 作者：odt63 (赞：1)

## 思路

首先我们思考朴素的 dp 方程。

### 定义状态

首先定义 $dp_i$，表示当前最后一个分区是以 $i$ 结尾时均势区和更赛牛较多区的和的最小值。

然后我们定义 $cnt_i$ 表示 $[1,i]$ 范围内更赛牛减荷斯坦牛的数量，所以 $[l,r]$ 范围内更赛牛减荷斯坦牛的数量就是 $cnt_r - cnt_{l-1}$，在读入时只需要碰到字符 G 加 $1$，碰到字符 H 减 $1$ 就可以了。

### 转移方程

我们假设倒数第二个区间是以 $j$ 结尾的，则最后一个区间的范围是 $[j+1,i]$。由于一个区间的长度大于 $1$ 小于 $k$，所以 $j$ 的范围是从 $i-k$ 到 $i-1$。枚举每一个 $j$，如果 $sum_i-sum_j\geqslant0$，也就是说 $[j+1,i]$ 这个区间是一个均势区或更赛牛较多区，$dp_i=dp_j+1$，否则这不是均势区或更赛牛较多区，$dp_i=dp_j$，最后对所有的 $j$ 转移来的情况区最小值，方程如下：

$$
dp_i=\min\limits_{j=i-k}^{i-1} \begin{cases}dp_j+1&sum_i-sum_j\geqslant0\\dp_j&sum_i-sum_j <0\end{cases}
$$

时间复杂度 $\mathcal{O}(nk)$。

### 优化

很显然，这样一定会 TLE。

我们从状态转移处下手。由于每次转移的范围 $k$ 是固定的，所以没必要一个一个枚举 $j$，而可以用单调队列维护这段转移区间。队列内部存放决策的下标 $j$。

设 $f$ 为当前队首的值， $b$ 为当前队尾的值，则转移分三步：

如果 $i - f > k$ 且队列不为空，说明它超过了长度限制，不能从这里转移来，从队首弹出。循环弹出所有过期的。

转移 $dp_i$ 时，从 $dp_f$ 转移来，这时是最优的。

循环从队尾弹出过期时间早且不够优秀的。

什么叫“不够优秀”？

第一种情况，如果 $dp_b > dp_i$，那么从 $dp_b$ 转移不如 $dp_i$，弹出；第二种情况，如果 $dp_b = dp_i$，但是 $sum_i - sum_j \geqslant 0$，转移时需要加上 $1$，这样最多和 $dp_i$ 转移答案相同，或不及 $dp_i$，且比 $dp_i$ 过期得早，弹出。

核心代码如下：

```cpp
while(!q.empty()&&i-q.front()>k)q.pop_front();
		int j=q.front();
		if(cnt[i]-cnt[j]>=0)dp[i]=dp[j]+1;
		else dp[i]=dp[j];
		while(!q.empty()&&(dp[q.back()]>dp[i]||(dp[q.back()]==dp[i]&&cnt[i]-cnt[q.back()]>=0)))q.pop_back();
		q.push_back(i);
```

时间复杂度 $\mathcal{O}(n)$ 。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[3*114514];
int cnt[3*114514],dp[3*114514];
deque<int>q;
int main(){
	int n,k;
	cin>>n>>k;
	scanf("%s",s+1);
	q.push_back(0);
	for(int i=1;i<=n;i++){
		if(s[i]=='G')cnt[i]=cnt[i-1]+1;
		else cnt[i]=cnt[i-1]-1;
		while(!q.empty()&&i-q.front()>k)q.pop_front();
		int j=q.front();
		if(cnt[i]-cnt[j]>=0)dp[i]=dp[j]+1;
		else dp[i]=dp[j];
		while(!q.empty()&&(dp[q.back()]>dp[i]||(dp[q.back()]==dp[i]&&cnt[i]-cnt[q.back()]>=0)))q.pop_back();
		q.push_back(i);
	}
	cout<<dp[n]<<endl;
	return 0;
}
```

---

## 作者：Neutralized (赞：1)

给出一种完全不需要脑子的线段树做法，好像和其他题解不太一样。  


显然有
$$f_i=\min_{j=i-k}^{i-1} (f_j+[2(S_i-S_j) \ge i-j])$$  
其中 $S_i=\sum_{j=1}^{i}[s_j=G]$，也就是前缀里的更赛牛数量。  

后面那个判定式里移个项：$2S_i-i \ge 2S_j-j$，这样形式就相同了。这个东西扫到 $i$ 后就确定了，于是不难想到在枚举的同时，维护前 $k$ 个位置的这些值对应的 dp 值。  

考虑如何维护。平衡树是可行的，但权值线段树常数更小。我们每次在 $2S_i-i$ 位置插入 $f_i$，并且（如果可删）删除 $i-k-1$ 的贡献即可。  

于是只需要维护区间最小值。转移时，分别查询 $[-n,2S_i-i]$ 和 $[2S_i-i+1,n]$ 的最小值，前者的答案 $+1$ 与后者取 $\min$ 就是 $f_i$ 的值。  
但是还有一个问题，可能会有不同位置的 $2S_i-i$ 相同，那么我们在叶子节点维护 $2n$ 个 `multiset` 来支持插入和删除即可。由于总点数是 $k$ 个，空间上没有问题。  

时间复杂度 $O(n \log n)$。  

代码其实非常好写，但是需要把细节想清楚。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define ri register int
#define ll long long
#define Tp template<class T>
#define g() getchar()
#define pc(x) putchar(x)
#define isd(x) (x>=48&&x<=57)
namespace SlowIO{
	Tp inline void rd(T &x){ x=0; char i=g(); bool f=1; while(!isd(i)) f&=(i!='-'),i=g(); while(isd(i)) x=(x<<3)+(x<<1)+(i^48),i=g(); x*=((f<<1)-1); }
	const int OUT=1e6; static char outp[OUT]; int out;
	Tp inline void op(T x){ out=0; x<0&&(x=-x,pc('-')); if(!x){ pc(48); return; } while(x) outp[++out]=x%10+48,x/=10; while(out) pc(outp[out--]); }
	Tp inline void writeln(T x){ op(x);pc('\n'); }
	Tp inline void writesp(T x){ op(x); pc(' '); }
	Tp inline void write(T x,char c=0){ op(x); c&&pc(c); }
}; using namespace SlowIO;

#define N 300003
const int oo=2147480000;
int n,k,Val[N<<3],res[N],pos[N]; char s[N]; multiset<int> st[N<<1];
#define lef(u) u<<1
#define rig(u) u<<1|1
inline void push(int u){ Val[u]=min(Val[lef(u)],Val[rig(u)]); }
inline void Bld(int u,int l,int r){
	Val[u]=+oo; if(l==r){ st[l+n].insert(+oo); return; } ri mid=l+r>>1;
	Bld(lef(u),l,mid),Bld(rig(u),mid+1,r);
}
inline void Chg(int u,int l,int r,int x,int val,bool f){
	if(l==r){ if(f){
		auto it=st[l+n].lower_bound(val);
		if(it==st[l+n].end()||*it!=val) return;
		st[l+n].erase(it),Val[u]=*st[l+n].begin(); return;
	} else{
		st[l+n].insert(val),Val[u]=*st[l+n].begin(); return;
	} } ri mid=l+r>>1; if(x<=mid) Chg(lef(u),l,mid,x,val,f);
	else Chg(rig(u),mid+1,r,x,val,f); push(u);
}
inline int Qry(int u,int l,int r,int L,int R){
	if(l>=L&&r<=R) return Val[u]; ri mid=l+r>>1,t=+oo;
	if(L<=mid) t=Qry(lef(u),l,mid,L,R);
	if(R>mid) t=min(t,Qry(rig(u),mid+1,r,L,R)); return t;
}

int main()
{
	rd(n),rd(k),Bld(1,-n,n); int sum=0;
	scanf("%s",s+1),Chg(1,-n,n,0,0,0);
	for(ri i=1;i<=n;++i){
		if(i>=k+1) Chg(1,-n,n,pos[i-k-1],res[i-k-1],1); //delete
		sum+=s[i]=='G',pos[i]=(sum<<1)-i;
		int t1=Qry(1,-n,n,-n,pos[i])+1,t2=Qry(1,-n,n,pos[i]+1,n);
		res[i]=min(t1,t2),Chg(1,-n,n,pos[i],res[i],0); //insert
	} printf("%d",res[n]);
	return 0;
}
```

---

## 作者：小木虫 (赞：1)

### Preface
又是一道有意思的单调队列题目。
### Problem  
给定一个长度为 $n$ 的 01 串，要求把其划分为若干个子段，每个子段长度最大为 $k$，求划分后 0 与 1 数量相等的子段加 0 比 1 多的子段的最少数量。
### Solution  
先看暴力，发现可以 dp 暴力转移：  
$dp_i=dp_j+(sum1_{j+1,i}-sum2_{j+1,i}\leq 0)$  $[i-j \leq k]$  
其中 $dp_i$ 表示到 $i$ 节点后的最优答案，$sum1$ 为 1 的数量，$sum2$ 为 0 的数量。  
看到这题的子段最大限制，眼前一亮：  
**这不是一个滑动窗口的转移吗？**  
这简直是在明摆着可以单调队列优化啊。  
首先按照流程，头部删除离当前 $i$ 距离大于 $k$ 的元素。  
然后我们发现 $(sum1_{j+1,i}-sum2_{j+1,i}\leq 0)$ 这个东西,很显然我们将其拆解变形后可以变为：  
$(sum1_i-sum1_j)-(sum2_i-sum2_j) \leq 0$  
我们发现 $sum1$ 和 $sum2$ 是单调不减的，这显然满足单调队列优化的性质，把他们先提出来：  
$sum1_i-sum2_i\leq sum1_j-sum2_j$  
现在由于 $sum1_i-sum2_i$ 显然也递增，那么 $sum1_j-sum2_j$ 越小的元素越吃香，在之后的转移中它会比其它元素更晚满足上述表达式，发现它满足可以让答案加一，那么在两个元素 $a,b$ 并且 $a$ 的下标大于 $b$ 的情况里：  
如果 $a$ 的 dp 值小于 $b$ 的话，很显然 $a$ 更优，因为 $sum$ 的不同只能加一。  
如果 $a$ 的 dp 值等于 $b$ 的 dp 值并且其 $sum1_a-sum2_a\leq sum1_b-sum2_b$ 的话那么 $a$ 更优。  
其它情况 $b$ 更优，但是由于其下标更小，会更早出队，所以 $a$ 可以留下，上面两种情况 $b$ 就直接扔了。  
接下来直接根据上述结论打出单调队列优化就可以了：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,k;char temp;
bool a[N];int dp[N];
int sum1[N];int sum2[N];
int Stack[N];int head=1;int tail=0;
int main(){
	scanf("%d%d",&n,&k);
	getchar();
	for(int i=1;i<=n;i++){
		temp=getchar();
		if(temp=='H')a[i]=0,sum1[i]++;
		else a[i]=1,sum2[i]++;
		sum1[i]+=sum1[i-1];sum2[i]+=sum2[i-1];
	}
	Stack[++tail]=0;
	for(int i=1;i<=n;i++){
		while(head<=tail&&i-Stack[head]>k)++head;
		dp[i]=dp[Stack[head]]+((sum1[i]-sum2[i])<=(sum1[Stack[head]]-sum2[Stack[head]]));
		while(head<=tail&&((dp[i]<dp[Stack[tail]])||(dp[i]==dp[Stack[tail]]
		&&(sum1[i]-sum2[i])<=(sum1[Stack[tail]]-sum2[Stack[tail]]))))
			tail--;
		Stack[++tail]=i;
	}
	printf("%d",dp[n]);
	return 0;
}
```



---

## 作者：Yang818 (赞：1)

### 题目大意

给定一个长度 $n$，仅由 $-1$ 和 $1$ 构成的数列，将这个数列分为若干段，每段长度不超过 $k$。

求一种划分方案，使得数字之和 $\leq 0$ 的段落最小

------------

### 分析

数据范围是 $3 \times 10^5$，明显需要一个 $O(n)$ 或 $O(\log n)$ 的算法

不难看出，这是典型的一个分段问题，需要满足连续性和独立性。

设  $s_n = a_1 + a_2 + \cdots + a_n$  (前缀和)

设  $f[n]$ 为前 $n$ 个元素分段后的最佳结果。

子问题结构=前缀


------------
本题应该用动规的方法解决，现在只差方程式了
![方程](https://cdn.luogu.com.cn/upload/image_hosting/8crj7jsw.png)


------------
下附有程序可供参考
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=310000;
deque<int> Q;//因为头和尾都要插入，所以选用了deque

int s[maxn];//前缀和
int f[maxn];//前n个元素分段后的最佳结果
int main(){
	int n,k;
	char c;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='G'){
			s[i]=s[i-1]-1;
		}
		else{
			s[i]=s[i-1]+1;
		}
	}
	Q.push_back(0);
	for(int i=1;i<=n;i++){
		while(!Q.empty()){//检查过期元素 
			int j=Q.front();//最大值 
			if(i-j>k)
				Q.pop_front();
			else
				break; 
		}
		int j=Q.front(); 
		f[i]=f[j]+(s[j]>=s[i]);
		while(!Q.empty()){
			int j=Q.back();
			if(f[j]>f[i]||(f[j]==f[i]&&s[j]>=s[i]))
				Q.pop_back();
			else
				break;
		}
		Q.push_back(i); 
	}
	cout<<f[n];
   return 0;
} 
```
第一次提交题解，望通过
谢谢

---

## 作者：ynycoding (赞：1)

#### 大致题意:一直一个序列，有两种颜色，现在要求把这个序列分成若干个连续段，并使得每个连续段的长度不超过K。问最少有多少段第二种颜色的数量不少于第二种的数量。  

#### 为了方便理解，我们把序列第一种颜色当作+1，第二种当作-1，做一下前缀和，转化一下题意：平面上有n个点，每相邻的点坐标相差至多为一，每一步可以跳不超过K个点，问至少有多少次跳之后坐标会下降  
![](https://cdn.luogu.com.cn/upload/pic/50184.png)  
##### (样例的一种跳法)  
  
  
#### 接下来我们考虑DP  
#### 最暴力的DP就是枚举转移点j
		如果j的坐标大于i的坐标，则 dp[j]=min(dp[i],dp[j])
		否则 dp[j]=min(dp[i]+1,dp[j])  
  
#### 这个dp是$O(nk)$  
#### 考虑如何优化:  
#### 注意到每次的最优转移一定是恰好比i的值高1，或者是转移到当前dp的区间的最小值。  
第一种可以可一个数组记录每个值上的最靠右的，再记一下有多少个，方便删掉  
第二种可以拿一个单调队列来维护  
Code:  
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
#define MAXN 300005
using std::deque;
using std::min;
int n, k, sum[MAXN], dp[MAXN], cur, ans, p, q[MAXN];
deque<int> mn;
char s[MAXN];
int main()
{
	freopen("redistricting.in", "r", stdin);
	freopen("redistricting.out", "w", stdout);
	scanf("%d%d%s", &n, &k, s);
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+(s[i-1]=='H'?1:-1), p=std::min(p, sum[i]), dp[i]=0x3f3f3f3f;
	for(int i=1; i<=k&&i<=n; ++i) dp[i]=1;
	p=-p+1;
	for(int i=1; i<=k; ++i)
	{
		while(!mn.empty()&&sum[mn.back()]>=sum[i]) mn.pop_back();
		mn.push_back(i);
		q[sum[i]+p]=i;
	}
	if(q[1+p]) dp[q[1+p]]=0;
	for(int i=1; i<n; ++i)
	{
		if(mn.front()<=i&&!mn.empty()) mn.pop_front();
		if(i+k<=n)
		{
			while(!mn.empty()&&sum[mn.back()]>=sum[i+k]) mn.pop_back();
			mn.push_back(i+k), q[sum[i+k]+p]=i+k;
		}
		if(q[sum[i]+1+p]) dp[q[sum[i]+1+p]]=min(dp[q[sum[i]+1+p]], dp[i]);
		dp[min(n, i+k)]=min(dp[min(n, i+k)], dp[i]+1);
		dp[mn.front()]=min(dp[mn.front()], dp[i]+1);
	}
	printf("%d", dp[n]);
	return 0;
}
```  
注:写题解的时候发现我代码没有清除q数组的值，好像会被hack。~~本人太懒，不想改了，~~要改大家自己改吧。

---

## 作者：huhangqi (赞：0)

首先我们设更赛牛为加一，荷斯坦牛为负一。

这样通过前缀和就可以得到这一组是否需要增加一。

设 $dp_i$ 表示以 $i$ 为末尾，最少的分区。

那么方程式就为：

$$$
dp_i=dp_j+(pre_i-pre_j\le 0)
$$$

然而表达式我们并不好判断。

但是由于表达式只能提供数值为一的贡献，那么我们可以使用优先队列，以 $dp_j$ 的值排序，在 $dp_j$ 相同时按照 $pre_j$ 排序，取出最小值即可。

由于选择的区域有限，第一种处理方式是在结构体内记录下位置，若取出的值不合法则删除后再取一次。

对于第二种方法，可以直接使用带删的优先队列。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,dp[300005],pre[300005];
char a[300005];
struct P{
	int x,y;
	bool friend operator<(P a,P b){
		if(a.x!=b.x)return a.x>b.x;
		return a.y>b.y;
	}
};
struct Q{
	priority_queue<P> q1,q2;
	void push(P x){
		q1.push(x);
	}
	void pop(P x){
		q2.push(x);
	}
	P top(){
		while(!q1.empty()&&!q2.empty()&&q1.top().x==q2.top().x&&q1.top().y==q2.top().y){
			q1.pop();
			q2.pop();
		}
		return q1.top();
	}
}q;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]=='G')pre[i]=-1;
		else pre[i]=1;
	}
	for(int i=1;i<=n;i++)pre[i]+=pre[i-1];
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	q.push({0,0});
	for(int i=1;i<=n;i++){
		if(i-k-1>=0)q.pop({dp[i-k-1],pre[i-k-1]});
		P u=q.top();
		dp[i]=u.x+(pre[i]-u.y<=0);
		q.push({dp[i],pre[i]});
	}
	cout<<dp[n];
	return 0;
}
``````

---

## 作者：qwer6 (赞：0)

大佬们的做法都好巧妙，我太笨了想不到。

所以我直接使用线段树和 set 过掉了这道题。

我们首先把 $G$ 转换为 $1$，$H$ 转换为 $-1$，定义状态 $dp_i$ 为前 $i$ 个区域的最少可能数量。

然后做一遍前缀和，转移方程容易得出。
$$
dp_i=
\begin{cases}
dp_j\ (pre_i<pre_j)\\
dp_j+1\ (pre_i\ge pre_j)
\end{cases}
\ \ i-j+1\le k
$$
所以我们立刻想到建立一个权值线段树，记录每个 $pre$ 对应的最小值。

但是这显然是不可以的，因为还有一个 $i-j+1\le k$ 的限制，所以我们考虑使用一个滑动窗口，利用若干个 set 记录二元组 $(a,b)$，表示 $b$ 这个位置对应的值为 $a$，其中 $pre$ 相同的位置记在同一个 set 中，对于 $i$，如果 $i-k-1\ge 0$ 的话，说明我们删掉 $i-k-1$ 这个位置，那么我们在对应的 set 中去掉这个位置，然后通过 set 找到现在这个 $pre$ 中对应的最小值，直接修改线段树对应的值即可。

注意 $pre$ 可能为负，我们离散化一下就可以了。

```c++
/*by qwer6*/
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define Nxt puts("")
#define Spa putchar(32)
#define Pline puts("------------------------------")
namespace FastIO{
	inline int read(int &a){
		char c=getchar();
		int f=1;
		a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		return a=a*f;
	}
	inline int read(){
		char c=getchar();
		int f=1,a=0;
		while(!isdigit(c)){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(isdigit(c)){
			a=(a<<1)+(a<<3)+(c^48);
			c=getchar();
		}
		return a*f;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		std::stack<int>st;
		do{
		   st.push(x%10);
		   x/=10;
		}while(x);
		while(!st.empty())putchar(st.top()+'0'),st.pop();
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int N=3e5+5;
int n,k,tot;
int dp[N],pre[N],tmp[N],mi[N];
char c[N];
set<pii>st[N];
struct Segment_tree{
	int c[N<<2];
	#define ls p<<1
	#define rs p<<1|1
	#define mid (l+r>>1)
	void pushup(int p){
		c[p]=min(c[ls],c[rs]);
	}
	void build(int p,int l,int r){
		c[p]=0x3f3f3f3f;
		if(l==r)return ;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	void change(int p,int l,int r,int x,int v){
		if(l==r)return void(c[p]=v);
		if(mid>=x)change(ls,l,mid,x,v);
		else change(rs,mid+1,r,x,v);
		pushup(p);
	}
	int query(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return c[p];
		if(mid>=L&&mid<R)return min(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
		if(mid>=L)return query(ls,l,mid,L,R);
		return query(rs,mid+1,r,L,R);
	}
}Set; 
signed main(){
	read(n),read(k);
	scanf("%s",c+1);
	for(int i=1;i<=n;i++)tmp[i]=pre[i]=pre[i-1]+(c[i]=='G'?1:-1);
	tmp[n+1]=pre[0];
	sort(tmp+1,tmp+n+2);
	tot=unique(tmp+1,tmp+n+2)-tmp-1;
	for(int i=0;i<=n;i++)pre[i]=lower_bound(tmp+1,tmp+tot+1,pre[i])-tmp;
	for(int i=1;i<=tot;i++)st[i].insert({0x3f3f3f3f,n+1}),mi[i]=0x3f3f3f3f;
	Set.build(1,1,tot);
	Set.change(1,1,tot,pre[0],0);
	st[pre[0]].insert({0,0});
	mi[pre[0]]=0;
	for(int i=1;i<=n;i++){
		if(i-k-1>=0){
			auto it=st[pre[i-k-1]].lower_bound({dp[i-k-1],i-k-1});
			st[pre[i-k-1]].erase(it);
			if(st[pre[i-k-1]].begin()->fi!=mi[pre[i-k-1]]){
				mi[pre[i-k-1]]=st[pre[i-k-1]].begin()->fi;
				Set.change(1,1,tot,pre[i-k-1],st[pre[i-k-1]].begin()->fi);
			}
		}
		dp[i]=Set.query(1,1,tot,pre[i],tot)+1;
		if(pre[i]>1)
			tomin(dp[i],Set.query(1,1,tot,1,pre[i]-1));
		st[pre[i]].insert({dp[i],i});
		if(mi[pre[i]]>dp[i]){
			mi[pre[i]]=dp[i];
			Set.change(1,1,tot,pre[i],dp[i]);
		}
	}
	write(dp[n]);
}
```

---

## 作者：Mierstan085 (赞：0)

CYEZ 模拟赛做的，唐氏把 deque 写成 queue 了，还没发现。

考虑朴素 dp，定义 $w(i)$ 为 $[1, i]$ 中 `H` 的个数减去 `G` 的个数，不难想出这样的动态转移方程：

$$
f_i = \min \{ f_j + [w(i) - w(j) \le 0] \}, i - j \le k$$

但由于这样显然会超时，考虑使用数据结构维护。

假设没有 $w(i) - w(j) \le 0$，显然可以使用单调队列维护。

为了能够使用单调队列，假设有一组 $p, q$ 满足转移条件，那么考虑分类讨论：

1. 如 $f_p \neq f_q$，可以将小值放在队首。
2. 如 $f_p = f_q$，可以将 $w(f_i)$ 小的放在队首。

容易证明，以上的两种方案在任何情况都是最优的。

当然，如果不想证明的话可以考虑堆优化，（应该）会好证一点。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
int n, k, f[N], sum[N];
int q[N], head, tail;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//freopen("redistrict.in", "r", stdin);
	//freopen("redistrict.out", "w", stdout);
	
	cin >> n >> k;
	int i;
	for (i = 1; i <= n; i ++){
	    char s;
	    cin >> s;
	    sum[i] = sum[i - 1] + (s == 'H' ? 1 : - 1);
    }

    q[tail ++] = 0;
    for (i = 1; i <= n; i ++){
        while (head < tail && i - q[head] > k) head ++;
        f[i] = f[q[head]] + (sum[i] - sum[q[head]] <= 0);
        while (head < tail){
            if (f[i] < f[q[tail - 1]] || (f[i] == f[q[tail - 1]] && sum[i] < sum[q[tail - 1]])) tail --;
            else break;
        }    
        q[tail ++] = i;
    }
    cout << f[n];
}
```

---

## 作者：PineappleSummer (赞：0)

单调队列优化 DP，时间复杂度 $\mathcal O(n)$。

设 $f_i$ 为前 $i$ 头奶牛中更赛牛较多或者均势区的最小数量。记 $s_i$ 为前 $i$ 头奶牛中 `H` 比 `G` 多的数量。易得转移：
$$f_i=\min_{j=i-k}^{i-1}(f_j+[s_i-s_j\le 0])$$

发现转移的 $f_j$ 是一个区间，考虑单调队列维护，这样每次 $f_i$ 只需从队头转移而来。

加入 $f_i$ 时需要与队尾 $q_t$ 比较：
- 若 $f_i<f_{q_t}$，则弹出 $q_t$。
- 若 $f_i=f_{q_t}$ 且 $s_i<s_{q_t}$，则弹出 $q_t$。因为把 $s_j$ 较小的放在队首更容易使 $s_i-s_j>0$。

最后答案即为 $f_n$。

```cpp
signed main () {
	ios::sync_with_stdio (false);
	cin.tie (0); cout.tie (0);
	
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> c, sum[i] = sum[i - 1] + (c == 'H' ? 1 : -1);
	q[++t] = 0;
	for (int i = 1; i <= n; i++) {
		while (h < t && i - q[h] > k) ++h;
		f[i] = f[q[h]] + (sum[i] - sum[q[h]] <= 0);
		while (h < t) {
			if (f[i] < f[q[t]] || (f[i] == f[q[t]] && sum[i] < sum[q[t]])) t--;
			else break;
		}
		q[++t] = i;
	}
	cout << f[n];
	return 0;
}
```

---

## 作者：lqsy002 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P5202)。

## 解题思路

堆优化 DP，单调队列优化 DP。

把荷斯坦牛看成 $1$，把更赛牛看成 $-1$，通过前缀和来判断某一段中谁有优势。

选择的时候，第一关键字是贡献大小，第二关键字是要确保区间 $[j-1,i]$ 产生的贡献尽可能小。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int n,k;
int dp[maxn],sum[maxn];
char s[maxn];
struct node{
    int w;
    int p;
    bool operator<(const node &x)const{
        if(w==x.w) 
            return sum[p]>sum[x.p];
        return w>x.w;
    }
};
priority_queue<node>q;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>k>>(s+1);
    for(int i=1;i<=n;++i)
        if(s[i]=='H') 
            sum[i]=sum[i-1]+1;
        else
            sum[i]=sum[i-1]-1;
    q.push({0,0});
    for(int i=1,flag;i<=n;++i){
        while(!q.empty()&&q.top().p<i-k) 
            q.pop();
        if(sum[i]-sum[q.top().p]<=0) 
            flag=1;
        else
            flag=0;
        dp[i]=q.top().w+flag;
        q.push({dp[i],i});
    }
    cout<<dp[n];
    return 0;
}
```

---

## 作者：紊莫 (赞：0)

这是一篇使用单调队列优化 DP 的题解，还不会的可以参考[我的博客](https://zhuanlan.zhihu.com/p/662407180)。  

首先容易写出原始的方程：  

$$f_i=\min(f_j+cost(i,j)),j\in [i-k,i-1]$$  

发现瓶颈在于求一个定长区间的最值，显然单调队列。
代码没有什么特殊的点，纯纯板子，但是注意一下你需要先更新当前答案，再用这个答案去维护到单调队列里。

[示例代码。](https://www.luogu.com.cn/paste/e4kyfos2)

---

## 作者：jockbutt (赞：0)

# Solution

在看到题目的第一眼，就知道它是一道打牌，第二眼看到 $ k \leq n $，就可以笃定需要单调队列优化。

首先，不难推出下面的式子：

$ f_i=min(f_j+T) $

其中的 $ T $ 表示更牛个数是否大于等于荷牛个数，这样的裸的打牌的时间复杂度是 $ O(n\times k) $ 级别的，因为 $ k $ 很大，这样做效率非常低下。

接着，我们发现并不是需要完全枚举前 $ k $ 个位置，只需要记录一个最优的位置当 $ j $ 进行加就行了。那什么位置最优呢？这时候就要用到我们神奇的单调队列了。

队列需要满足两点：其中的元素离当前位置的距离不能超过 $ k $ 并且队列前面的元素要比后面的元素更优。

我们在计算 $ f_i $ 的时候，先把队列前面不合法的元素给打死，再对于队列末尾没有位置 $ i $ 优秀的也全部打死，最后再把 $ i $给加进去。

因为队列后面的元素要优于前面的元素，我们在选取 $ j $ 更新答案时，只需要选队列最顶端的元素就行了。

代码很简单，可以“三位偏序”地吊打那些线段树、优先队列的代码。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
const int maxn=5e5+10;
int a[maxn],f[maxn];
char ch[maxn];
int q[maxn],head=1,tail;
signed main(){
	scanf("%d%d",&n,&m);
	scanf("%s",ch+1);
	for(int i=1;i<=n;++i)	a[i]=a[i-1]+(ch[i]=='H'?1:-1);
	q[++tail]=0;
	for(int i=1,j;i<=n;++i)
	{
		while(head<=tail&&i-q[head]>m)	head++;
		f[i]=f[q[head]]+(a[i]-a[q[head]]<=0);
		while(head<=tail)
		{
			if(f[i]<f[q[tail]]||(f[i]==f[q[tail]]&&a[i]<a[q[tail]]))	tail--;
			else	break;
		}
		q[++tail]=i;
	}
	printf("%d\n",f[n]);
	return 0;
}
/*
14 4
HGHGGHGHHGGHHG


*/
```


---

## 作者：_ctz (赞：0)

[更好的阅读体验$QwQ$](https://ctz45562.github.io/2019/02/25/%E9%A2%98%E8%A7%A3-%E6%B4%9B%E8%B0%B7-P5202-%E3%80%90-USACO19JAN-Redistricting%E3%80%91/)

[传送门](https://www.luogu.org/problemnew/show/P5202)

正解好像是$O(n)$的单调队列优化贪心？这里提供一种好想点的$O(nlogn)$思路。

首先把 $H$ 看作 $1$ ， $G$ 看作 $-1$ ，处理一下前缀和 $sum$ ，这样就能快速判断一段区间两种牛数量关系了。

用 $f(i)$ 表示把前 $i$ 块牧草地分完最少能有几段更赛牛区域。转移时枚举一下最后一段区域的长度，就有：

$f(i)=min\{f(i-j)+(sum[i]-sum[i-j]\le 0)\}(1\le j\le k)$

初值$f[0]=0$，答案为$f[n]$。

$(sum[i]-sum[i-j]\le 0)$意为区域$[i-j+1,i]$是否为更赛牛区域。

时间复杂度：$O(nk)$，显然过不了。

把$sum[i]-sum[i-j]\le 0$移项得$sum[i]\le sum[i-j]$

这样就可以造一棵存两个值$sum[i]$和$f[i]$的平衡树，以$sum[i]$排序，每个节点取一下子树中的$min(f[i])$。查询时遍历一遍平衡树，大于等于当前$sum[i]$的要$+1$，取一下$min$，就能用$logn$的时间更新，然后再插入。同时为了保证取到前面的$k$个值要及时删除$QwQ$

时间复杂度：$O(nlogn)$

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 300005
#define inf 0x3f3f3f3f
#define pn putchar('\n')
#define px(x) putchar(x)
#define ps putchar(' ')
#define pd puts("======================")
#define pj puts("++++++++++++++++++++++")

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
template<typename T>
inline T read(){
	T x=0;
	int y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}//快读
inline int ran(){
	static int seed=45562;
	return seed=(seed*48271LL%2147483647);
}//rand函数，好像能优化一下常数？
struct Treap{
	int dat[maxn],num[maxn],ls[maxn],rs[maxn],ra[maxn],mi[maxn],cnt,root;
    //dat为用于比较的关键值（sum[i])，num为存起来的f[i]，mi为子树最小f[i]
#define ls(x) ls[x]
#define rs(x) rs[x]
	inline void update(int node){
		mi[node]=min(min(mi[ls(node)],mi[rs(node)]),num[node]);
	}
	void right(int &node){
		int rec=ls(node);
		ls(node)=rs(rec);
		rs(rec)=node;
		node=rec;
		update(rs(node));
		update(node);
	}
	void left(int &node){
		int rec=rs(node);
		rs(node)=ls(rec);
		ls(rec)=node;
		node=rec;
		update(ls(node));
		update(node);
	}
	void insert(int &node,int d1,int d2){
		if(!node){
			node=++cnt;
			dat[node]=d1;
			mi[node]=num[node]=d2;
			ra[node]=ran();
			return;
		}
		if(dat[node]<d1||(dat[node]==d1&&num[node]<d2)){
			insert(rs(node),d1,d2);
			if(ra[rs(node)]>ra[node])left(node);
		}
		else {
			insert(ls(node),d1,d2);
			if(ra[ls(node)]>ra[node])right(node);
		}
		update(node);
	}
	void del(int &node,int d1,int d2){
		if(dat[node]==d1&&num[node]==d2){
			if(ls(node)&&rs(node)){
				if(ra[ls(node)]>ra[rs(node)])right(node),del(rs(node),d1,d2);
				else left(node),del(ls(node),d1,d2);
				update(node);
			}
			else node=ls(node)+rs(node);
			return;
		}
		if(dat[node]<d1||(dat[node]==d1&&num[node]<d2))del(rs(node),d1,d2);
		else del(ls(node),d1,d2);
		update(node);
	}
	int Get(int d){
		int node=root,ans=inf;
		while(node){
			if(d<=dat[node])ans=min(ans,min(num[node],mi[rs(node)])+1),node=ls(node);
            //当前节点大于等于待查询值，则它的右子树都大于等于，答案+1
			else ans=min(ans,min(num[node],mi[ls(node)])),node=rs(node);
            //否则左子树都比它小，不+1
		}
		return ans;
	}//查询函数
	Treap(){
		num[0]=mi[0]=inf;
	}
}tr;
int f[maxn],sum[maxn],n,k;
char a[maxn];
int main(){
	n=read(),k=read();
	scanf("%s",a+1);
	for(register int i=1;i<=n;++i)
		if(a[i]=='H')sum[i]=sum[i-1]+1;
		else sum[i]=sum[i-1]-1;
	tr.insert(tr.root,0,0);//插入初值
	for(register int i=1;i<=n;++i){
		if(i>k)tr.del(tr.root,sum[i-k-1],f[i-k-1]);//删除不在当前区间的值
		f[i]=tr.Get(sum[i]);
		tr.insert(tr.root,sum[i],f[i]);
	}
	printf("%d\n",f[n]);
}
```





---

