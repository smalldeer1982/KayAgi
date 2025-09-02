# [ABC355G] Baseball

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc355/tasks/abc355_g

長さ $ N $ の数列 $ P=(P_1,P_2,\dots,P_N) $ が与えられます。高橋君と青木君が、数列 $ P $ を使ってゲームを行います。

まず、高橋君が、 $ 1,2,\dots,N $ から $ K $ 個の相異なる整数 $ x_1,x_2,\dots,x_K $ を選びます。

次に、青木君が、 $ 1,2,\dots,N $ から $ 1 $ つの整数 $ y $ を $ P_y $ に比例する確率で選びます。すなわち、整数 $ y $ が選ばれる確率は $ \dfrac{P_y}{\sum_{y'=1}^N\ P_{y'}} $ です。そして、青木君が $ \displaystyle\ \min_{i=1,2,\dots,K}\ |x_i-y| $ のスコアを得ます。

高橋君は、青木君が得るスコアの期待値を**最小化**したいです。高橋君が適切に $ x_1,x_2,\dots,x_K $ を選んだときに、青木君が得るスコアの期待値の最小値を $ \sum_{y'=1}^N\ P_{y'} $ 倍した値を求めてください。なお、出力すべき値は整数になることが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^4 $
- $ 1\ \leq\ K\ \leq\ N $
- $ 0\ \leq\ P_i\ \leq\ 10^5 $
- $ 1\ \leq\ \sum_{y'=1}^N\ P_{y'}\ \leq\ 10^5 $
- 入力はすべて整数
 
### Sample Explanation 1

青木君が $ 1,2,\dots,N $ を選ぶ確率はすべて等しく $ \frac{1}{5} $ です。 高橋君が $ x_1=2,x_2=4 $ と選んだとすると、青木君が得るスコアの期待値は $ 1\ \times\ \frac{1}{5}\ +\ 0\ \times\ \frac{1}{5}\ +\ 1\ \times\ \frac{1}{5}\ +\ 0\ \times\ \frac{1}{5}\ +\ 1\ \times\ \frac{1}{5}\ =\ \frac{3}{5} $ です。 高橋君が $ x_1=2,x_2=3 $ と選んだとすると、青木君が得るスコアの期待値は $ 1\ \times\ \frac{1}{5}\ +\ 0\ \times\ \frac{1}{5}\ +\ 0\ \times\ \frac{1}{5}\ +\ 1\ \times\ \frac{1}{5}\ +\ 2\ \times\ \frac{1}{5}\ =\ \frac{4}{5} $ です。 高橋君が他の選び方をしても、青木君が得るスコアの期待値は $ \frac{3}{5} $ より小さくなりません。よって最小値は $ \frac{3}{5} $ であり、これを $ 5 $ 倍した $ 3 $ を出力します。

## 样例 #1

### 输入

```
5 2
1 1 1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5 1
0 0 1 0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
1 1
100```

### 输出

```
0```

## 样例 #4

### 输入

```
20 7
4262 9522 2426 3823 7364 964 2743 2423 1955 5274 3684 847 363 35 278 3220 203 2904 6304 1928```

### 输出

```
22809```

# 题解

## 作者：larsr (赞：3)

**简化题意**：选择 $k$ 个数 $x_1, \ldots ,x_k$，使总价值最小，总价值为：

$$\sum_{i}^n (\min_{1\leq j\leq k}|x_k - i|) \times p_i$$

可以转化为（此处设 $x_0=-\infty,x_{n+1}=\infty$）：

$$\sum_{i=0}^{n}\sum_{x_i\leq j\leq x_{i+1}} \min(j-x_i, x_{i+1} - j)p_j$$

设 $w(l,r)=\sum_{l\le i\le r} \min(i-l,r-i)p_i$，可以看出 $w$ 满足四边形不等式，这明显是一个限制数量划分的问题，那么就可以用四边形不等式优化到 $O(nk)$。

设 $f(k)$ 为划分为 $k$ 个区间的最小费用，可以知道 $f$ 是凸性的，详细证明可以看[这篇文章](https://www.luogu.com.cn/article/574asjsv)。那么就可以用 wqs 二分了，在求值时用二分队列。复杂度 $O(n\log V\log n)$。

代码：
```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
#define N 50010
#define pa pair<ll,int>
using namespace std;
int n, k;
ll p[N], sl[N], ssl[N], sr[N], ssr[N], c;
pa f[N], ans;
int id[N], bg, en, ql[N], qr[N];
ll wl(int l, int r)
{
	if(l > r)return 0;
	return ssr[l] - ssr[r + 1] - sr[r + 1] * (r - l + 1);
}
ll wr(int l, int r)
{
	if(l > r)return 0;
	return ssl[r] - ssl[l - 1] - sl[l - 1] * (r - l + 1);
}
ll w(int l, int r)
{
	if(l + 1 == r)return 0;
	int mid = (l + r) / 2;
	return wl(l + 1, mid) + wr(mid + 1, r - 1);
}
pa get(int l, int r)
{
	return make_pair(f[l].first + w(l, r) + c, f[l].second + 1);
}
void check()
{
	bg = 1;
	en = 0;
	ans = make_pair(1e18, 0);
	for(int i = 1; i <= n; i++)
	{
		f[i] = make_pair(wr(1, i - 1) + c, 1);
		while(bg <= en && qr[bg] < i)bg++;
		if(bg <= en)
		{
			ql[bg] = i + 1;
			f[i] = min(f[i], get(id[bg], i));
		}
		ans = min(ans, make_pair(f[i].first + wl(i + 1, n), f[i].second));
		while(bg <= en && get(i, ql[en]) < get(id[en], ql[en]))en--;
		if(bg > en)
		{
			bg = en = 1;
			id[bg] = i;
			ql[bg] = i + 1;
			qr[bg] = n;
		}
		else if(get(i, qr[en]) > get(id[en], qr[en]))
		{
			if(qr[en] < n)
			{
				en++;
				ql[en] = qr[en - 1] + 1;
				qr[en] = n;
				id[en] = i;
			}
		}
		else
		{
			int ml = ql[en], mr = qr[en];
			while(ml < mr)
			{
				int mid = (ml + mr) / 2;
				if(get(i, mid) < get(id[en], mid))mr = mid;
				else ml = mid + 1;
			}
			qr[en] = ml - 1;
			en++;
			ql[en] = ml;
			qr[en] = n;
			id[en] = i;
		}
	}
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)scanf("%lld", p + i);
	for(int i = 1; i <= n; i++)sl[i] = sl[i - 1] + p[i], ssl[i] = ssl[i - 1] + sl[i];
	for(int i = n; i; i--)sr[i] = sr[i + 1] + p[i], ssr[i] = ssr[i + 1] + sr[i];
	ll ml = 0, mr = 1e10;
	while(ml < mr)
	{
		c = (ml + mr) / 2;
		check();
		if(ans.second <= k)mr = c;
		else ml = c + 1;
	}
	c = ml;
	check();
	printf("%lld\n", ans.first - k * c);
	return 0;
}
```

---

## 作者：王华 (赞：2)

前置知识: wqs 二分,四边形不等式优化 dp。  

首先观察题目，将其从概率问题转化为加权的最优化问题，非常容易得出一个 dp 做法，设计状态 $f(i,j)=k$  表示在序列前 $i$ 个位置上划分了 $j$ 次的最小代价为 $k$，状态复杂度为 $O(nk)$，转移为 $O(n)$，并且这个 dp 是难以继续优化的。

因此我们考虑用 wqs 二分进行降维，将每次区间划分强行赋上一个代价，这样我们就成功消掉记录区间划分数的一维，我们得到了一个新的 dp 状态： $f(i)=j$ 划分前 $i$ 个位置且最后一个被划分的位置是 $i$ 的最小代价为 $j$，朴素的转移是

$$
f(i)=\min_{j=1}^{i-1} f(j)+w(j+1,i-1)
$$


非常显然，成本函数 $w$ 在一维固定的情况下具有凸性，因此可以由四边形不等式推出决策单调性，这里给出两种复杂度不同的实现方法。

#### 法一：分治决策点

这个方法在解决不依赖前面 dp 数组转移时比较方便，但在本题中遇到了一个难以解决的问题，如果对于不加限制的询问区间 $[l,r]$ 和可选区间 $[L,R]$，难以直接算出 $[l,r]$ 中点在 $[L,R]$ 中的决策点，因此考虑对这两个区间加限制，不妨设 $R<l$，那么就可以直接算出，核心代码如下。


```cpp
void solve1(int l,int r,int cl,int cr)
{
	int rem=cl,mid=(l+r)>>1;
	for(int i=cl;i<=cr;i++){
		pli cur=mp(dp[i].F+calc(i+1,mid-1)+cost,dp[i].S+1);
		if(cur<dp[mid])dp[mid]=cur,rem=i;
	}
	if(l<mid)solve1(l,mid-1,cl,rem);
	if(mid<r)solve1(mid+1,r,rem,cr);
	return;
}
void solve2(int l,int r)
{
	if(l==r)return;
	int mid=(l+r)>>1;
	solve2(l,mid);
	solve1(mid+1,r,l,mid);
	solve2(mid+1,r);
	return;
}
```

但同时会有一个新的问题，如果 $[l,r]$ 中有点的最优决策点不在 $[L,R]$ 中会有问题吗？

考虑分情况讨论。

情况一：当 $mid$ 的最优决策点在 $[1,L-1]$ 中，此时对于 $[l,mid]$ ，都会满足这个条件，令 $mid$ 在 $[L,R]$中的决策点为 $L$，可知对 $[mid+1,r]$ 没有影响。

情况二：当 $mid$ 的最优决策点在 $[L,R]$ 中，正常做，略。

情况三：当 $mid$ 的最优决策点在 $[R+1,mid-1]$ 中，现在的等价问题是，是否会有在 $[l,mid-1]$ 的点会被 $mid$ 在 $[L,R]$ 的决策点影响。由于决策单调性在决策点可选的子集中依然成立，答案是不会的，过程类似于一般的四边形不等式证明决策点单调，读者可自证。


#### 法二：二分队列

这个方法算是通法了，完全可以套用 oiwiki 的模板。

核心代码如下。

```cpp
pli solve(ll mid)
{
	q.clear();
	for(int i=1;i<=n;i++)
		dp[i]=mp(calcr(1,i-1)+mid,1);
	q.pb(1);lt[1]=2,rt[1]=n;
	for(int i=2;i<=n;i++)
	{
		dp[i]=min(dp[i],mp(dp[q.front()].F+mid+calc(q.front()+1,i-1),dp[q.front()].S+1));
		lt[q.front()]++;if(lt[q.front()]>rt[q.front()])q.pop_front();
		while(!q.empty()&&mp(dp[q.back()].F+calc(q.back()+1,lt[q.back()]-1),dp[q.back()].S)>=mp(dp[i].F+calc(i+1,lt[q.back()]-1),dp[i].S))q.pop_back();
		if(q.empty())lt[i]=i+1,rt[i]=n,q.pb(i);
		else{
			int l=lt[q.back()],r=rt[q.back()];
			while(l<=r){
				int md=(l+r)>>1;
				if(mp(dp[q.back()].F+calc(q.back()+1,md-1),dp[q.back()].S)>=mp(dp[i].F+calc(i+1,md-1),dp[i].S))
					r=md-1;
				else
					l=md+1;
			}rt[q.back()]=r;
			if(r+1<=n){
				q.pb(i);
				lt[i]=r+1;
				rt[i]=n;
			}
		}
	}
	for(int i=1;i<n;i++)
		dp[n]=min(dp[n],mp(dp[i].F+calcl(i+1,n),dp[i].S));
	return dp[n];
}
```


#### 其他方法
具体可参照官方题解，事实上，在去除最外面的一层二分后，该四边形不等式优化 dp，是一个非常经典的问题，法一的复杂度是 $O(n \log^2 n)$，法二的复杂度是 $O(n\log n)$，如果用 monge 矩阵对该问题进行描述，使用 smawk 算法能做到 $O(n)$。

对于这整个问题，官解还有线性做法，和凸包有关的线性对数做法，大家有兴趣可自行探究，笔者不太会线性代数。

---

## 作者：CCPSDCGK (赞：2)

先列出一个朴素 dp，设 $f_{i,j}$ 为前 $i$ 个数划分成了 $j$ 段的最小代价，状态数 $O(nk)$，转移复杂度 $O(n)$，时间复杂度 $O(n^2k)$。

然而这题并没有什么特殊性质能减少状态数或者是转移复杂度之类的，所以考虑各种套路化的 dp 优化方法。

# wqs 二分 $O(n^2k)\rightarrow O(n^2\log C)$
设 $f(i)$ 为划分成了 $i$ 段的最小代价，如果 $f(i)$ 具有凸性，那么所有点 $(i,f(i))$ 就组成了一个凸壳，斜率单调，我们可以通过二分斜率 $k$ 来得出斜率为 $-k$ 的直线刚好截这个凸包的点，即将每一段的代价额外加上 $k$，然后把划分段数这一维去掉，这样就能得出此时的最小代价以及所对应的段数，根据这个与题目要求的段数比较再进行二分。

这里可能会出现一条斜率刚好截到多个点的情况，即一次 dp 得出的最优解可能对应多个划分段数，如果随便取的话可能会出事，所以我们规定取最小的或最大的，然后根据你怎么取的来设计与题目要求的段数该怎么比较。

至于 $f(i)$ 为什么存在凸性，这里先卖个关子。

# 决策单调性优化 dp $O(n^2\log C)\rightarrow O(n\log n\log C)$
对于 $f_i=\min\limits_{j=0}^{i-1}\{f_j+w(j+1,i)\}$ 类 dp，如果 $w(i,j)$ 存在四边形不等式，那么这个 dp 就具有决策单调性 dp，感性理解一下这个 $w(j,i)$ 确实存在四边形不等式，严谨证明也不难推，读者可以自己去推一下。

决策单调性 dp 有两种优化方法，一种是离线分治，一种是半在线的二分队列，由于这里的 dp 形式是自决策单调性 dp，所以无法离线分治，只能用二分队列的方式。

有一个结论，如果 $w(i,j)$ 满足四边形不等式，且 dp 形式为 $f_{k,i}=\min\limits_{j=0}^{i-1}\{f_{k-1,j}+w(j+1,i)\}$，那么以 $k$ 为自变量的 $f_{k,n}$ 具有凸性，所以碰到这样的问题，我们只需要证明 $w(j,i)$ 具有四边形不等式就可以在时间复杂度上大力砍掉两维了，这是一大胜利！

```cpp
int p[50005],sum1[50005],n;
ll sum2[50005];
pair<ll,int> dp[50005];
inline ll w(int l,int r){
	if(l>r) return 0;
	if(l==1&&r==n) return 1e18;
	if(l==1) return sum1[r]*(r+1ll)-sum2[r];
	if(r==n) return sum2[n]-sum2[l-1]-(l-1ll)*(sum1[n]-sum1[l-1]);
	int mid=l+r>>1;
	return (sum1[r]-sum1[mid])*(r+1ll)-(sum2[r]-sum2[mid])+(sum2[mid]-sum2[l-1])-(sum1[mid]-sum1[l-1])*(l-1ll);
}
ll tmp;
inline pair<ll,int> getf(int x,int y){
	if(y>=x) return {1e18,0};
	return {dp[y].first+w(y+1,x-1)+tmp,dp[y].second+1};
}
inline int bound(int x,int y){
	int l=x+1,r=n+1,p;
	while(l<=r){
		int mid=l+r>>1;
		if(getf(mid,x)<getf(mid,y)) p=mid,l=mid+1;else r=mid-1;
	}
	return p;
}
int q[50005],pos[50005];
inline pair<ll,int> f(ll x){
	tmp=x;
	int l=1,r=1;q[1]=0;
	for(int i=1;i<=n+1;i++){
		while(l<r&&pos[l]<i) l++;
		dp[i]=getf(i,q[l]);
		while(l<r&&pos[r-1]>=bound(q[r],i)) r--;
		pos[r]=bound(q[r],i),q[++r]=i;
	}
	return dp[n+1];
}
int main(){
	int k;cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>p[i],sum1[i]=sum1[i-1]+p[i],sum2[i]=sum2[i-1]+(ll)p[i]*i;
	ll l=0,r=1e10,x;
	while(l<=r){
		ll mid=l+r>>1;
		if(f(mid).second<=k+1) x=mid,r=mid-1;else l=mid+1;
	}
	cout<<f(x).first-(k+1)*x;
	return 0;
}
```

---

