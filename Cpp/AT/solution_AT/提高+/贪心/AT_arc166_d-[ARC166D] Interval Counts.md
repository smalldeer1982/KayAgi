# [ARC166D] Interval Counts

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc166/tasks/arc166_d

$ x_1\ <\ \cdots\ <\ x_N $ を満たす正整数 $ x_1,\ \ldots,\ x_N $ および，正整数 $ y_1,\ \ldots,\ y_N $ が与えられます．

組 $ (M,\ L_1,\ R_1,\ \ldots,\ L_M,\ R_M) $ であって，以下の条件を全て満たすものを考えます：

- $ M $ は正整数である．
- 各 $ j\ (1\leq\ j\leq\ M) $ に対して，$ L_j,\ R_j $ は $ L_j\leq\ R_j $ を満たす整数である．
- 各 $ i\ (1\leq\ i\leq\ N) $ に対して，$ L_j\leq\ x_i\leq\ R_j $ を満たす $ j\ (1\leq\ j\leq\ M) $ がちょうど $ y_i $ 個存在する．
 
このような組は必ず存在することが証明できます．そのような組に対する $ \min\ \lbrace\ R_j-L_j\mid\ 1\leq\ j\leq\ M\rbrace $ としてありうる最大値を求めてください．ただし，最大値が存在しない場合には `-1` を出力してください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ x_1\ <\ \cdots\ <\ x_N\ \leq\ 10^9 $
- $ 1\leq\ y_i\ \leq\ 10^9 $
 
### Sample Explanation 1

例えば組 $ (3,\ 1,\ 4,\ 2,\ 4,\ 3,\ 5) $ に対して $ \min\ \lbrace\ R_j-L_j\mid\ 1\leq\ j\leq\ M\rbrace\ =\ 2 $ が成り立ちます．

### Sample Explanation 2

例えば組 $ (3,\ -1000,\ 10,\ -1000,\ 1000,\ 10,\ 1000) $ に対して $ \min\ \lbrace\ R_j-L_j\mid\ 1\leq\ j\leq\ M\rbrace\ =\ 990 $ が成り立ちます．$ \min\ \lbrace\ R_j-L_j\mid\ 1\leq\ j\leq\ M\rbrace $ の最大値は存在しません．

## 样例 #1

### 输入

```
3
1 3 5
1 3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3
1 10 100
2 3 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
7
10 31 47 55 68 73 90
3 7 4 6 3 4 4```

### 输出

```
56```

# 题解

## 作者：樱雪喵 (赞：9)

这不比 C 简单。

## Description

给定正整数 $n$ 和长度为 $n$ 的序列 $x_i,y_i$，保证 $x_i$ 单调递增。你要构造 $m$ 个区间 $[L_i,R_i]$（$m$ 由你指定），使每个 $x_i$ 恰好被 $y_i$ 个区间包含。

最大化 $\min_{i=1}^m \{R_i-L_i\}$，并求该值。

$N\le 2\times 10^5,\ 1\le x_i,y_i\le 10^9$。

## Solution

看到最小值最大试图进行二分，然而不太可做。因此考虑直接贪心构造。

按 $x_i$ 从小到大的顺序依次构造区间。  
假设当前构造的区间已经满足 $x_1,\dots,x_{i-1}$ 的限制。那么根据当前 $y_i$ 和 $y_{i-1}$ 的大小关系分为三种情况。

- $y_i=y_{i-1}$ 是容易处理的，因为我们什么也不用做，把上一次的区间都延长过来就可以。

- 若 $y_i<y_{i-1}$，我们不能把所有未确定右端点的区间都接过来，必须要断掉恰好 $d=y_{i-1}-y_i$ 条边。根据想让最短区间最长的目标，断掉左端点前 $d$ 小的线段是最优的。所以把左端点前 $d$ 小的线段右端点设为 $x_i-1$，把它们移出未确定右端点的区间集合并更新答案。

- 若 $y_i>y_{i-1}$，那么缺 $d=y_i-y_{i-1}$ 个区间。令它们左端点最小，则新增 $d$ 个左端点为 $x_{i-1}+1$，右端点未确定的区间，加入集合。

由于 $y\le 10^9$，$m$ 很大，暴力维护所有左端点不可行。但发现每次我们加入集合的左端点都单调递增，用一个队列存储二元组 $(x,y)$ 表示插入了 $y$ 条左端点为 $x$ 的区间。删除的时候弹队首即可，时间复杂度 $O(n)$。



```cpp
const int N=2e5+5,inf=1e9;
int n,x[N],y[N];
pii q[N];
int st=1,ed=0,ans=inf;
int main()
{
    n=read();
    for(int i=1;i<=n;i++) x[i]=read();
    for(int i=1;i<=n;i++) y[i]=read();
    x[0]=-inf;
    for(int i=1;i<=n;i++)
    {
        if(y[i]==y[i-1]) continue;
        if(y[i]>y[i-1]) q[++ed]=pii(x[i-1],y[i]-y[i-1]);
        else
        {
            int now=y[i-1]-y[i];
            while(st<=ed&&q[st].se<=now)
            {
                ans=min(ans,x[i]-q[st].fi-1);
                now-=q[st].se,st++;
            }
            if(st<=ed&&now&&q[st].se>now) q[st].se-=now,ans=min(ans,x[i]-q[st].fi-1);
        }
    }
    if(ans==inf) printf("-1\n");
    else printf("%d\n",ans-1);
    return 0;
}
```

---

## 作者：Rosabel (赞：2)

是不是有点太简单了？

贪心地考虑，从左到右扫（这很显然是这类题的策略）。假定 $S_i$ 为经过 $i$ 的区间 $[L,R]$ 所组成的集合，显然有 $\mid S_i\mid=y_i$。

发现从 $i-1$ 过渡到 $i$ 的时候，最好是能把 $S_{i-1}$ 的元素继承到 $S_i$ 继续使用（可以理解为原来的区间为 $[L,i-1]$，那么将右端点拓展至 $i$ 使区间变为 $[L,i]$ 显然不劣，相当于将原来可能成为最小值的量增大了）。这就是本题贪心的核心思想。

当 $y_i=y_{i-1}$ 时，直接全部继承即可。

当 $y_i\lt y_{i-1}$ 时，这时只能继承 $S_{i-1}$ 的一部分，另外一部分需要扔掉。这里肯定是扔掉左端点最靠左的更优。反证法证明，若存在两个 $S_{i-1}$ 的元素区间使得大致形态为 $A+B$（即 $A$ 段和 $B$ 段拼接而成） 和 $B$，二选一继承到 $S_i$（假设接的下一段为 $C$）。那么若抛掉 $A+B$ 这两个区间最终对答案的贡献为 $\min(\mid A+B\mid,\mid B+C\mid)$。抛掉 $B$ 这两个区间最终对答案的贡献为 $\min(\mid B\mid,\mid A+B+C\mid)=\mid B\mid$。显然前者更优。

当 $y_i\gt y_{i-1}$ 时，集合中不得不在继承 $S_{i-1}$ 所有元素的基础上增加 $y_i-y_{i-1}$ 个元素区间 $[i,R]$。

为了在 $y_i\lt y_{i-1}$ 情况下正确处理，集合内的元素区间显然根据左端点升序排序（右端点在扫描线未确定）。由于维护 $\Theta(\sum y)$ 个元素不太现实，考虑到最多只会有 $n$ 个本质不同的元素区间（左端点不同），那么只需将本质相同的元素区间合并到一个记录元素区间信息和相同元素个数的二元组即可。单调队列维护集合。时间复杂度线性 $\Theta(n)$。

[code](https://atcoder.jp/contests/arc166/submissions/55875560)

---

## 作者：fish_love_cat (赞：1)

最好笑的一集，写二分写着写着突然发现 check 函数能把答案算出来。

---

首先注意到如果当前点的覆盖能够从上一个点的所用区间顺延过来，那顺延肯定优秀。

如果顺延不够用呢？为了不影响上一个点，只能从上一个点坐标的下一位开始新的区间来覆盖。

那如果顺延过来把我超了怎么办？那只有结束区间了。由于答案是取得最小值，那么可以知道要断的肯定是开始早的区间。

至于怎么找到应该断开的区间，一种想法是优先队列。然后我们注意到本题保证升序的妙妙性质，于是队列就能做了。

注意要判无解，翻译中没有提到，但是如果最短区间是无限长的请输出 `-1`。

那么做完了，复杂度应该是综合 $O(n)$ 带点常数的，能过就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005];
int n;
struct fish{
    int x,sum;
};
int check(){
    int ans=1e9;
    deque<fish>q;
    q.push_back({-1000000000,b[1]});
    for(int i=2;i<=n;i++){
        if(b[i]>b[i-1])q.push_back({a[i-1]+1,b[i]-b[i-1]});
        while(b[i]<b[i-1]){
            if(q.front().sum<=b[i-1]-b[i])
            b[i-1]-=q.front().sum,ans=min(ans,a[i]-1-q.front().x),q.pop_front();
            else{
                fish flc=q.front();
                flc.sum-=b[i-1]-b[i];
                b[i-1]=b[i],ans=min(ans,a[i]-1-q.front().x);
                q.pop_front(),q.push_front(flc);
            }
        }
    }
    if(q.front().x==-1000000000)return -1;
    return ans;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        cin>>b[i];
    // int l=0,r=1e9;
    // while(l<r){
    //     int mid=(l+r+1)/2;
    //     if(check(mid))l=mid;
    //     else r=mid-1;
    // }
    cout<<check();
    return 0;
}
```

---

## 作者：SunsetVoice (赞：1)

挺有意思的题，教练出到了模拟赛里面。

第一次场蓝就切双蓝，非常激动的。

本来这种题是个二分题，想了一下感觉十分不可做，于是考虑贪心直接出最优解。

先设 $x_0=-\inf，x_{n+1}=\inf$，反正区间左右都没有限制的，最大肯定不劣。

注意到我们选一个区间实际上是对 $y_i$ 区间减一所以问题立刻就和差分扯上了关系。

问题转化为：

> 给定一个数组，可以选择一对数 $1\le i < j \le n+1$，使 $a_i$ 减一并把 $a_j$ 加一，每次操作代价为 $x_j-x_{i-1}-2$。最大化将 $a$ 数组前 $n$ 项归零所需操作代价的最小值。

正数不用管，因为你考虑到 $j={n+1}$ 相当于单点减并且代价是 $\inf$ 啥都不影响，考虑负数。因为 $i<j$ 所以**一个负数只能用它之前的正数消**，所以找最远的数消这个贪心是没问题的，略微形式化地证一下的话有一篇题解有但这玩意实在太过显然就不再赘述了。

做完了。

考场上“诶奶龙奶龙有没有无解的情况呢”然后想了十几分钟发现这是个差分数组且 $y_i\ge0$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,x[500001] = {0},y[500001] = {0},dy[500001] = {0};
vector<pair<int,int> >p;
signed main(){
	cin>>n;
	for(int i = 1;i<=n;i++)cin>>x[i];
	for(int i = 1;i<=n;i++)cin>>y[i];
	for(int i = 1;i<=n;i++){
		dy[i] = y[i]-y[i-1];
	}
	int hjx = 1;
	for(int i = 1;i<=n;i++){
		if(dy[i]<0){
			while(dy[hjx]<=-dy[i]){
				dy[i]+=dy[hjx];
				dy[hjx] = 0;
				while(dy[hjx]<=0)hjx++;
			}
			if(dy[i]==0){
				p.push_back(make_pair(i,hjx-1));
			}else{
				dy[hjx]+=dy[i];
				dy[i] = 0;
				p.push_back(make_pair(i,hjx));
			}
		}
	}
	x[0] = -1145141919810;
	int mi = 1145141919810;
	for(pair<int,int> np:p){
		mi = min(x[np.first]-x[np.second-1]-2,mi);
	}
	if(mi>1e11){
		cout<<-1<<endl;
	}else{
		cout<<mi<<endl;
	}
	return 0;
}
```

---

## 作者：lalaouye (赞：1)

我们可以将题转化为选择若干区间，给区间中的每个 $y_i$ 减一，这样我们就可以将问题转化为差分了。

我们枚举区间的左端点，从左到右枚举，当我们枚举到 $i$ 时，显然如果当前差分数组 $d_i>0$，那么我们需要将其减去 $d_i$，这样我们获得了一个向后加总共 $d_i$ 个 $1$ 的机会，此时我们维护数列从左往右第一个 $d_p$ 小于 $0$ 的 $p$，然后我们每次进行不断地加减并将 $p$ 往后挪，到 $n+1$ 即可停止。那么这样为什么是对的？因为如果我们将这个小于 $0$ 的交给一个左端点大于 $i$ 的 $j$ 处理，那么由于 $x_j>x_i$，所以一定不优。

该如何计算答案？我们注意到对于任意在序列中 $l$ 到 $r$ 的区间，$L_i$ 取 $x_{l-1}+1$，$R_i$ 取 $x_{r+1}-1$ 显然最优，为了方便我们将 $x_0$ 赋值为 $-\inf$，将 $x_{n+1}$ 赋值为 $\inf$ 即可。

时间复杂度 $\mathcal{O}(n)$。

代码：

```
int n;
int x[N], y[N], d[N];
int l[N], r[N];
signed main ()
{
  n = rd ();
  x[0] = - linf, x[n + 1] = linf;
  rep (i, 1, n) x[i] = rd ();
  rep (i, 1, n) l[i] = x[i - 1] + 1, r[i] = x[i + 1] - 1;
  rep (i, 1, n) y[i] = rd (), d[i] = y[i] - y[i - 1];
  int p = 1;
  while (d[p] >= 0) ++ p;
  int ans = linf;
  rep (i, 1, n)
  {
    int x = d[i];
    if (! x) continue;
    while (x)
    {
      while (d[p] >= 0 && p <= n) ++ p;
      if (p > n) break;
      ans = min (ans, r[p - 1] - l[i]);
      if (- d[p] > x) d[p] += x, x = 0;
      else
      {
        x += d[p], d[p] = 0;
      }
    }
  }
  if (ans >= 1e10) puts ("-1"); else printf ("%lld\n", ans); 
}
```

---

## 作者：Erine (赞：1)

不妨设 $x_0=-\inf$，$y_0=0$。考虑贪心地构造。

我们先构造出满足前 $i$ 项的区间。用一个队列维护右端点可以继续往右扩展的 $y_i$ 个区间左端点。

现在要扩展到 $i+1$。分类讨论：

若 $y_{i+1}\le y_i$，则将队首 $y_i-y_{i+1}$ 个左端点，即贪心选最左的几个左端点弹出，钦定它们的右端点是 $x_{i+1}-1$，并更新答案；

若 $y_{i+1}\gt y_i$，则需要额外加入 $y_{i+1}-y_i$ 个区间，这些区间不能影响前面的覆盖情况，所以左端点都是 $x_i+1$。

注意到 $y_i\le 10^9$，不能直接模拟上述过程。而观察到第二种 case 中加入的数都是相同的，考虑队列维护二元组，即 $(l_i,c_i)$ 表示左端点 $l_i$ 出现了 $c_i$ 次。这样最多加入 $n$ 个二元组，每个二元组最多被弹出一次，总复杂度 $\Theta(n)$。

最后，若答案没有被一个合理的值更新过，则输出 `-1`。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second

using namespace std;
using pii = pair<int, int>;

const int maxn = 1e6 + 10;
const int inf = 1e15;

int n, ans = inf;
int x[maxn], y[maxn];
pii q[maxn];
int hd = 1, tl;

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> x[i];
	for (int i = 1; i <= n; i++) cin >> y[i];
	x[0] = -inf, x[n + 1] = inf;
	for (int i = 1; i <= n; i++) {
		if (y[i] <= y[i - 1]) {
			int k = y[i - 1] - y[i];
			while (hd <= tl) {
				if (q[hd].sc <= k) {
					k -= q[hd].sc;
					ans = min(ans, x[i] - 1 - q[hd].fs);
					++hd;
				} else { 
					if (k) ans = min(ans, x[i] - 1 - q[hd].fs);
					q[hd].sc -= k; 
					break; 
				}
			}
		} else {
			q[++tl] = {x[i - 1] + 1, y[i] - y[i - 1]};
		}
	}
	if (ans > 1e10) cout << -1 << endl;
	else cout << ans << endl;
	return 0;
}

```

---

## 作者：Phartial (赞：0)

假设我们希望一个区间恰好包含 $[x_l,x_r]$，那么为了最大化这个区间的长度，我们肯定是将其顶到 $[x_{l-1}+1,x_{r+1}-1]$ 为止。由此可知，覆盖一段前缀或后缀的区间长度可以任意大。

注意到一个事情是包含必然不优于交叉（如果有两个区间 $[L_i,R_i]$ 和 $[L_j,R_j]$ 使得 $L_i\le L_j\le R_j\le R_i$，那么调整成 $[L_i,R_j]$ 和 $[L_j,R_i]$ 肯定是不劣的）。

于是你对 $y$ 做一个差分，每个正数找之后最近的负数贪心消就行。

感觉比 C 简单很多啊，是不是不太会数数导致的。

[code](https://atcoder.jp/contests/arc166/submissions/56964886).

---

## 作者：g1ove (赞：0)

线段树做法，拿下你谷最劣解。

题意翻译很形象，就不说了。

## 思路
最大化最小值，我们很容易想到二分答案。很容易发现，答案具有单调性。

我们二分一个答案 $x$，强制每次使用的区间长度都不小于 $x$，然后判断可行性。

现在问题转化为怎么判断一个答案 $x$ 是否可行。

我们发现，如果枚举左端点 $l_i$，右端点的取值是在一个范围内的，即 $r_i\in[p_i,n]$，然后 $p_i$ 我们可以通过二分快速计算出来。不难发现 $p_i$ 也是单调递增的。 

现在问题转化为，可以选若干个区间 $[l,r]$，将区间内的所有数都减 $1$，问最终是否能使所有数变为 $0$。

区间减 $1$ 比较难维护，考虑问题的等价转化，转成差分数组，我们引入 $d$ 数组，令 $d_i=b_i-b_{i-1}$，所有数为 $0$ 等价于 $\forall i\in[1,n],d_i=0$,为了程序写的方便，我们引入点 $x_{n+1}=inf$，并且规定 $d_{n+1}$ 取任意数均可。

然后问题又转化成，可以在 $[1,l_i]$ 中选一个 $d_x$ 将其减一，在 $[p_i+1,n]$ 中选一个 $d_x$ 使其加一。

我们从 $1$ 到 $n$ 遍历 ，如果遇见某一位是负数，那么就是非法的，所以有一个比较明显的贪心策略：
+ 从 $1$ 到 $n$ 遍历 $d_i$ ,如果 $d_i<0$ 返回情况非法，否则，贪心的选择 $j\in[p+1,n]$ 内当前的数和**最左边**的负数 $d_j$，使其变为正数，并在 $d_i\ge 0$ 的条件下。

贪心正确性显然，交换证明即可，读者可自己尝试。

最后，使用线段树动态维护最左边的负数即可。当然，使用 `multiset` 也可，或者一个队列维护，但是不太想写了。

使用线段树和二分，所以时间复杂度 $O(n\log n\log w)$，强势拿下[最劣解](https://www.luogu.com.cn/record/list?pid=AT_arc166_d&orderBy=1&status=&page=3)。

code
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define N 200005
#define ll long long 
#define Pr pair<ll,int>
#define fi first
#define se second
using namespace std;
const ll inf=1e10;
int n;
ll a[N],b[N],t[N];
ll d[N];
struct segtree{
	Pr tr[N*4];
	void Pushup(int x)
	{
		if(tr[x*2].fi>=0) tr[x]=tr[x*2+1];
		else tr[x]=tr[x*2];
	}
	void modify(int l,int r,int P,int x,ll v)
	{
		if(l==r)
		{
			tr[x]=mp(v,l);
			return;
		}
		int mid=(l+r)/2;
		if(P<=mid) modify(l,mid,P,x*2,v);
		else modify(mid+1,r,P,x*2+1,v);
		Pushup(x);
	}
	Pr query(int l,int r,int L,int R,int x)
	{
		if(l>R||r<L) return mp(inf,-1);
		if(l>=L&&r<=R) return tr[x];
		int mid=(l+r)/2;
		Pr lv=query(l,mid,L,R,x*2),rv=query(mid+1,r,L,R,x*2+1);
		if(lv.fi>=0) return rv;
		else return lv;
	}
}tr;
bool check(ll x)
{
	memcpy(b,t,sizeof t);
	for(int i=1;i<=n;i++) tr.modify(1,n,i,1,b[i]); 
	for(int i=1;i<=n;i++)
	{
		if(b[i]<0) return 0;
		int p=upper_bound(a,a+1+n,a[i-1]+1+x)-a;// p->n 
		while(b[i])
		{
			Pr t=tr.query(1,n,p,n,1);
			ll mv=t.first;
			int mp=t.second;
			if(mv>=0) break;
			if(mv+b[i]>0) b[i]+=mv,b[mp]=0,tr.modify(1,n,mp,1,0),tr.modify(1,n,i,1,b[i]);
			else
			{
				b[mp]+=b[i];
				b[i]=0;
				tr.modify(1,n,mp,1,b[mp]); 
				tr.modify(1,n,i,1,0);
				break;
			}
		}
	}
	return 1;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&t[i]);
	for(int i=n;i>=1;i--) t[i]-=t[i-1];
	a[0]=-inf,a[n+1]=inf;
	ll l=1,r=1e9+5;
	while(l<=r)
	{
		ll mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	if(l>1e9) printf("-1");
	else printf("%lld",l-1);
	return 0;
}
```

---

