# 花火

## 题目描述

## 0.前言

前来贡献翻译（改了题目主人公，管理如果不喜那就改回来吧）……

LSY最可爱，逃:)。

---

## 【题目背景】

烟花升起而后绽放犹如浮生沉浮，一个人孤寂地徘徊……

所以可爱的LSY很喜欢看烟花。（然而貌似没什么关联）

---


现在LSY在烟花长廊的起点，起点位置为$0$，终点位置为$L$。烟花长廊内总共有$n$束烟花要发射，其中第$i$束烟花要在$t[i]$时在$p[i]$发射。由于LSY十分喜欢烟花，所以LSY在烟花长廊中有非凡的速度使得LSY在$1$秒钟内可以前进任意距离（前进的长度不能为负数但是可以为$0$）。因为LSY视力不是很好，所以某一束烟花在绽放时离她越远的话她的不满值会升高，具体计算方法如下：

如果$t$时刻有一束烟花在$Pf$位置绽放并且LSY在$Pl$位置，那么LSY的不满值会上升$|Pf-Pl|$。

举个栗子：在1时刻，LSY在位置3，有一束烟花在位置4绽放，那么LSY的不满值将会上升1。

现在LSY找到了你，希望你能设计出一个程序使得她看完所有烟花后不满值最小。

---

## 样例 #1

### 输入

```
5 10
1 2
1 4
3 8
4 7
5 1```

### 输出

```
9```

## 样例 #2

### 输入

```
4 10
1 4
1 4
2 1
3 9```

### 输出

```
3```

## 样例 #3

### 输入

```
10 20
2 15
3 4
3 14
4 11
6 0
7 7
8 8
8 8
8 12
9 10```

### 输出

```
33```

# 题解

## 作者：珅肐 (赞：7)

弃了好久的题，时隔良久又翻出来，终于像是有了思路

我们贪心的想

如果没有不能向后走的限制的话

我们每次都到烟花的释放点，有多个释放点就取中间点

这是非常好想的

但是如果加上这个限制呢？

局部贪心就不是最优解了

考虑不加限制时的过程，当ニワンゴくん向后走时，

如果这并不是实际最优解，即ニワンゴくん当前这步走的比最优解多

我们就将这步拉回来，并重新计算贡献

具体怎么实现呢？代码可能写的有点奇怪

就拿样例说吧，
```cpp
5 10
1 2
1 4
3 8
4 7
5 1
```
我们按时间倒着排序，来避免对后面造成的影响

首先，站在原点不动的代价是$\sum_{i=1}^np_i=22$

第一个是 $5$ $1$

当前在零位置，到$1$位置，代价是$1$，但是我们可以挪到$1$位置，这样代价就是$1-1=0$

第二个是 $4$ $7$

当前在$1$位置,本来只可以向前挪，这里回溯到$7$位置，代价是$7-1=6$，


第三个是 $3$ $8$

当前在$7$位置向前，到$8$位置需要回溯，代价最少是$8-7=1$，

第四个是 $1$ $4$

当前在$8$位置向前，回到$4$不需要代价

第五个是 $1$ $2$

因为时间与第四个是一致的，代价一定是$2$，可以写作$4-2$

总代价为$0+6+1+0+2=9$

思考我们的过程，回到之前的不需要代价，向后需要的代价为其坐标的绝对值

所以可以直接把当前的$p_i$压入优先队列，取出最小的$p$做就好了，

这里之所以压入两次是为了去掉之前$\sum_{i=1}^np_i$的影响
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<set>
#include<queue>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
typedef pair<int,int> pairs;
priority_queue<int> q;
multiset<pairs> v;
signed main(){
	int n=read(),sum=0,ans=0;read();
	while(n--){
		int t=read(),p=read();
		v.insert(make_pair(-t,p));
		sum+=p;
	}
	for(multiset<pairs>::iterator it=v.begin();it!=v.end();it++){
		q.push(-(*it).second),q.push(-(*it).second);
		ans+=q.top(),q.pop();
	}
	printf("%lld\n",ans+sum);
	return 0;
}
```


---

## 作者：xlpg0713 (赞：5)

花火可爱，虽然日语里的花火指烟花。翻译写得很清楚，不再说一遍了。

slope trick 板子题，大概到不了黑。

设 $f_{i,x}$ 表示第 $i$ 个时刻在 $x$ 的最小代价，易于写出 dp 方程：

$f_{i,x}=\sum\limits_j\left[t_j=x\right]|p_j-x|+\min\limits_{i=1}^{x}f_{i-1,x}$

易于发现这个函数一定是下凸的。于是用 slope trick 的话说：维护下凸函数，每次将斜率大于 $0$ 的部分推平，并加上若干个绝对值函数，维护最小值。

会了 slope trick 就会写代码了。

```cpp
#include<iostream>
#include<queue>
int n, l, t[100005], p[100005]; using ll = long long;
ll k, b; std::priority_queue<ll> q;
int main(){
    std::ios::sync_with_stdio(false);
    std::cin >> n >> l;
    for(int i = 1; i <= n; i++){
        std::cin >> t[i] >> p[i];
        if(t[i]>t[i-1]) while(k) b+=q.top(), q.pop(), k--;
        k++, b -= p[i], q.push(p[i]), q.push(p[i]);
    } while(k) b+=q.top(),q.pop(),k--; std::cout << b << '\n';
}
```

---

## 作者：roger_yrj (赞：3)

## AT_dwango2016qual_e 花火

### 题解

看到绝对值，这题大概能猜它是个 Slope Trick。

这题有一点像 [AT_abc217_h](https://www.luogu.com.cn/problem/AT_abc217_h)。

设 $f_{i,j}$ 为 $i$ 时刻时位置在 $j$ 收到伤害的最小值。

首先根据归纳法，我们可以发现 $f_i$ 是个下凸函数。我们使用两个优先队列来维护斜率为 $0$ 的段的左右部分的拐点。（**常见套路**）

让我们看看从 $i-1$ 这个时刻到 $i$ 时刻发生了什么变化。

“前进任意距离”的意思就是 $f_{i,j}=\min\limits_{k\le j}{f_{i-1,k}}$，这实质上就是把右边的拐点清空。

然后算伤害的部分分类讨论 $Pf$ 的位置在左边/中间/右边即可，注意维护斜率为 $0$ 的段和答案。

**注意输出答案时加换行**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
ll n,tagl,tagr,t[N],d[N],l;
ll ans;
priority_queue<ll>L;
priority_queue<ll,vector<ll>,greater<ll> >R;
int main(){
	cin>>n>>l;
	for(int i=1;i<=n;i++)L.push(0);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&t[i],&d[i]);
	for(int i=1;i<=n;i++){
		while(!R.empty())R.pop();
		int j=i;
		while(i<n&&t[i+1]==t[i])i++;
		for(int k=j;k<=i;k++)R.push(l);
		for(;j<=i;j++){
			if(L.top()<=d[j]&&d[j]<=R.top())L.push(d[j]),R.push(d[j]);
			else if(L.top()>d[j]){
				ans+=L.top()-d[j];
				R.push(L.top());
				L.pop();
				L.push(d[j]);
				L.push(d[j]);
			}else{
				ans+=d[j]-R.top();
				L.push(R.top());
				R.pop();
				R.push(d[j]);
				R.push(d[j]);
			}
		}
	}
	cout<<ans<<"\n";
}
```

---

## 作者：hejianxing (赞：3)

[link](https://www.luogu.com.cn/problem/AT_dwango2016qual_e)

水黑。

# 题意

有 $n$ 个烟花，每个烟花在 $t_i$ 时刻、$p_i$ 位置释放。初始位置为 $0$，时刻为 $0$，可以向前移动任意距离（不能向后），但是一个时刻只能在一个位置。烟花释放时，不满值会加上当前位置与烟花的距离。最小化不满值。

$n,V\le 10^5$。

# 题解

Slope trick 的模板题。

Slope trick 将一个整数凸壳（斜率和点都是整数）描述为一个点集 $S$ 和一个一次函数 $y=kx+b$。它的描述方式是这样的：（以下凸壳为例）

这个凸壳由若干一次函数构成。若相邻两个一次函数的交点为 $(x,y)$，其左边的一次函数斜率为 $k_1$，右边的一次函数斜率为 $k_2$，那么向集合中插入 $k_2-k_1$ 个 $x$。同时维护最右边的一次函数的解析式。

这种奇怪的刻画方式有一个显然的性质：对于两个下凸壳 $f(x),g(x)$，$h(x)=f(x)+g(x)$ 可以表示为两个下凸壳的点集相加，同时一次函数的解析式相加。即 $S_h=S_f\cup S_g,y=(k_f+k_g)x+(b_f+b_g)$。

现在考虑这个题目的朴素 dp 做法。设 $f_{i,j}$ 表示时刻 $i$ 在位置 $j$ 的最小代价。假设所有的 $t_i$ 互不相同，那么有转移 $f_{i,j}=\min\limits_{k=1}^{j}\left\{f_{i-1,k}+|p_i-j|\right\}$。

考虑用归纳法证明这个 $f_i$ 是一个下凸壳。因为 $y=f_{i-1,x}$ 是下凸的，$y=|p_i-x|$ 也是下凸的，那么显然有 $y=f_{i-1,x}+|p_i-x|$ 是下凸的。一个凸函数取前缀 $\min$ 之后显然也是凸的，所以 $f_{i}$ 是一个下凸壳。

考虑维护这个凸壳。枚举到第 $i$ 时刻的时候，已维护的凸壳是 $f_{i-1}$，那么将凸壳 $|p_i-j|$ 加上去。由于这个绝对值函数的拐点是 $p_i$，并且左右的斜率差值为 $2$，所以向当前维护的点集中加入两个 $p_i$。原来最右侧的一次函数为 $y=kx+b$，绝对值函数的最右侧为 $y=x-p_i$，所以 $y'=(k+1)x+(b-p_i)$。现在这个凸壳已经变成了 $y=f_{i-1,x}+|p_i-x|$，还要取前缀 $\min$。不难发现取前缀 $\min$ 就是将这个凸壳右侧扯平，斜率大于 $0$ 的部分都变成斜率等于 $0$。具体来讲，将最右侧的一次函数的斜率每次降低 $1$，直到 $k=0$。也就是每次扔掉点集 $S$ 中最大的一个数。那么考虑如何维护这个新的一次函数。

由于最右侧的拐点（被扔掉的数）同时满足降低前的一次函数和现在的一次函数，所以有 $kx+b=(k-1)x+b'$，则 $b'=b+x$。

这样就完成了所有 $t_i$ 互不相同的情况。考虑相同的 $t$，在维护完这个时刻的凸壳后再取前缀 $\min$ 即可。

时间复杂度 $O(n\log n)$。

# 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n, L, t[N], p[N];
priority_queue<int> pq;
int main() {
    scanf("%d%d", &n, &L);
    LL k = 0, b = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &t[i], &p[i]);
        if (t[i] > t[i - 1]) while (k) b += pq.top(), pq.pop(), k--;
        k++, b -= p[i], pq.push(p[i]), pq.push(p[i]);
    }
    while (k) b += pq.top(), pq.pop(), k--;
    printf("%lld\n", b);
    return 0;
}
```

---

## 作者：strcmp (赞：1)

典完了。

设 $f_{i,\,j}$ 代表第 $i$ 个时间在 $j$ 位置的最大贡献，显然有转移：

$$
f_{i,\,j} \gets \min\limits_{k \le j} \{ f_{i - 1,\,k} + \sum\limits_{c}[t_c = i]|k - p_c| \}
$$

每次大概是加一个绝对值函数，而绝对值函数是经典凸性函数，我们猜测 $f_{i,\,j}$ 在 $i$ 固定的时候关于 $j$ 是凸的。发现直接归纳法就容易证明了。折线下凸函数加上绝对值函数仍然是下凸的（事实上这种形式就是经典的 Slope Trick 可优化形式）。

再考虑这个 $\min$ 是个什么东西，发现只是将斜率大于 $0$ 的位置全部推平，仍然不改变凸性。

我们画出 $f_{i,\,j}$ 的图像，每次相当于加上若干个绝对值函数，并把斜率 $ > 0$ 的位置推平。

$f$ 的前缀 $\min$ 的转折点，显然我们只用管斜率 $ < 0$ 的部分。使用 Slope Trick 维护转折点，则每次相当于转折点可重集中加入 $\{ p_i,\,p_i \}$。若 $p_i$ 大于最大的转折点，那么加的第二个 $p_i$ 会因为前缀 $\min$ 直接没掉，因此只需要加一个 $p_i$。否则 $p_i$ 小于最大的转折点，那么前缀 $\min$ 也会把这个转折点删除，所以要一直 `pop`。

直接用个支持插入、查询和删除最小值的数据结构维护斜率的转折点即可。

时间复杂度 $\Theta(n \log n)$，可以通过。使用 vEB 树可以做到 $\Theta(n \log \log L)$。

代码上，首先每次决策点都是堆顶，可以直接加进答案里。然后使用一些费用提前计算的技巧。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define mid (l + r >> 1)
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pq = __gnu_pbds::priority_queue<int>;
constexpr int maxn = 1e5 + 10, mod = 1e9 + 7;
int n, L, t, p, lt, c; pq q; ll ans;
int main() {
	scanf("%d%d", &n, &L);
	rep(i, 1, n) {
		scanf("%d%d", &t, &p);
		if (t > lt) while (c && c--) ans += q.top(), q.pop();
		q.push(p); q.push(p); ans -= p; ++c; lt = t;
	}
	while (c && c--) ans += q.top(), q.pop();
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

另一篇题解从贪心的角度和我得到了相同的代码，说实话我并不是很理解那篇题解的思路正确性......

首先列出 $\mathcal O(nm)$ 的暴力 DP：$dp_{i,j}$ 表示前 $i$ 个时间点，目前在位置 $j$ 的最小不满意度。

转移枚举上一个时间所在的位置 $k\le j$，那么从 $k$ 走过来的最小不满意度是 $dp_{i-1,k}+\sum\limits_{t_p=i}|j-a_p|$，对于所有符合条件的 $k$ 取个 $\min$ 就能转移了，是一个前缀 $\min$ 的形式，因此可以优化到 $\mathcal O(nm)$。

看到绝对值，我们不难想到 Slope Trick。具体而言，考虑设 $F_{i}(x)=dp_{i,x}$，容易发现 $F_{i}$ 是凸的（可以用归纳法证明，在此不表）。而加上的绝对值函数 $|j-a_p|$ 也是凸的，凸函数相加还是凸的（考虑差分数组叠加即可），因此维护这个 dp 可以利用凸函数的性质来完成。

我们再设前缀 $\min$ 函数 $G_{i}(x)=\min\limits_{j=1}^{x}dp_{i,x}$。我们把 $(i,F_{i}(x))$ 和 $(i,G_{i}(x))$ 放在平面上，相邻点连线。发现后者的图像就是把前者斜率为 $1$ 的部分给拉平了，变成一条斜率为 $0$ 的线段。

我们设法维护凸函数。Slope Trick 这个技巧就是运用数据结构维护凸函数的所有斜率变化点，在 $x$ 处斜率变化了 $k$ 那么就插入 $k$ 个 $x$。比如函数 $y=|x-2|$ 的变化点集合就是 $\{2,2\}$。

对于不同的时间点取前缀 $\min$ 有点麻烦，我们不妨让每次加入一个 $|j-a_p|$ 之后立刻取前缀 $\min$，再做之后的操作。  

观察加入了一个函数 $|x-k|$ 之后的变化（其变化点集合为 $\{k,k\}$）。设当前最大变化点为 $k_0$。

我们首先加入一个变化点 $k$。接着，如果 $k>k_0$，那么需要删除 $k_0$，并将整个函数向上平移（在代码中体现为 $ans$ 的变化），再插入另一个变化点 $k$；否则不需要变化。

所有操作全部可以用一个堆解决。时间复杂度 $\mathcal O(n\log n)$。

极简代码：

```cpp
const ll N=5e5+9;
ll n,m,ans;
pii a[N];
priority_queue<ll,vector<ll>,greater<ll> >q;
int main(){
	n=read(),m=read();
	rep(i,1,n)a[i].first=-read(),a[i].second=read();
	sort(a+1,a+n+1);
	rep(i,1,n){
		q.push(a[i].second);
		if(a[i].second>q.top())ans+=a[i].second-q.top(),q.pop(),q.push(a[i].second);
	}
	write(ans);
	return 0;
}
```

---

