# AmShZ and G.O.A.T.

## 题目描述

Let's call an array of $ k $ integers $ c_1, c_2, \ldots, c_k $ terrible, if the following condition holds:

- Let $ AVG $ be the $ \frac{c_1 + c_2 + \ldots + c_k}{k} $ (the average of all the elements of the array, it doesn't have to be integer). Then the number of elements of the array which are bigger than $ AVG $ should be strictly larger than the number of elements of the array which are smaller than $ AVG $ . Note that elements equal to $ AVG $ don't count.
  
  For example $ c = \{1, 4, 4, 5, 6\} $ is terrible because $ AVG = 4.0 $ and $ 5 $ -th and $ 4 $ -th elements are greater than $ AVG $ and $ 1 $ -st element is smaller than $ AVG $ .

Let's call an array of $ m $ integers $ b_1, b_2, \ldots, b_m $ bad, if at least one of its non-empty subsequences is terrible, and good otherwise.

You are given an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ . Find the minimum number of elements that you have to delete from it to obtain a good array.

An array is a subsequence of another array if it can be obtained from it by deletion of several (possibly, zero or all) elements.

## 说明/提示

In the first sample, the array $ a $ is already good.

In the second sample, it's enough to delete $ 1 $ , obtaining array $ [4, 4, 5, 6] $ , which is good.

## 样例 #1

### 输入

```
4
3
1 2 3
5
1 4 4 5 6
6
7 8 197860736 212611869 360417095 837913434
8
6 10 56026534 405137099 550504063 784959015 802926648 967281024```

### 输出

```
0
1
2
3```

# 题解

## 作者：DeaphetS (赞：27)

[为自己的博客引流](https://www.cnblogs.com/DeaphetS/p/16502035.html)

既然要求的是最大的好序列，就需要考虑排除所有的不安定因素，即先思考什么样的子序列是非法的。

$k=1,2$ 的时候可以发现都是合法情况，那么看一下 $k=3$ 的情况，可以得出非法的情况只可能是 $c_1<\frac{c_1+c_2+c_3}{3}<c_2\le c_3$，分析一下可以得出，对应的充要条件实际上是 $\frac{c_1+c_2+c_3}{3}<c_2$，可以化成 $c_1+c_3<2c_2$。

另外可以证明，一个非法序列 $c$ 里一定存在一个长度为 $3$ 的非法子序列，证明方式采用反证法。

令 $m=\lceil \frac{k}{2}\rceil$，考虑 $c_m$ 的大小，既然 $c$ 是一个非法序列，那么 $c_m$ 就一定要严格大于序列的平均值。然而由于 $c$ 中不存在一个长度为 $3$ 的非法子序列，据此得出对任意的 $i$，$c_i,c_m,c_{k-i+1}$ 一定是一个合法序列，那么就有 $c_i+c_{k-i+1}\ge 2c_m$（这一结论在 $i=m$ 或 $k-i+1=m$ 时也显然成立）。把 $\sum c_i$ 乘以二后首尾配对就能得到：

$$2\sum_{i=1}^k c_i=\sum_{i=1}^{k} {c_i+c_{k-i+1}}\ge2k\cdot c_m$$

把上面的这个式子两边同除 $2k$ 就能得出，$c_m\le \frac{\sum_{i=1}^k c_i}{k}$ ，与之前的 $c_m$ 要严格大于序列的平均值发生矛盾，于是得出 $c$ 里一定存在一个长度为 $3$ 的非法子序列，**证毕**。

于是一个好的序列就必须保证：序列中不存在三个数 $a\le b\le c$，使得 $2b>a+c$。必要性显然，充分性在刚刚得到了证明。

那么我们在构造一个尽可能大的子序列时，就需要时刻保证对任意的 $a\le b\le c$，有 $b\le \frac{a+c}{2}$。我们来考虑一下往答案序列里面一直加数的过程，假设一开始序列里有两个数 $x,y$，不妨设 $x,y$ 就分别是最终答案中的最小值和最大值，那么下一个被加进来的数就必须满足 $x\le z\le \frac{x+y}{2}$。不难通过想象（或在数轴上画图）得出，这一操作相当于让前两个数之间的间隔减半。于是这个加数的操作不会超过 $O(\log n)$ 次，当然除了最后可能会把所有与 $x$ 相同的数字全部加进去。

回顾这个构造序列的过程，本着贪心的原则可以得出，当确定了序列中的最小值 $a$ 之后，一定是先把所有数字中的最大值加进去来提高初始两个数之间的间隔。接下来就是不断加入最大的满足 $x\le z\le \frac{x+y}{2}$ 的数字 $z$，这样就能构造出一个以 $a$ 为最小值的最大序列。这里要注意，由于在序列中，只有最小值是可以重复出现的（若不然，则会有 $\{x,y,y\},x<y$ 使得序列变坏），所以序列的最小值是需要枚举的。那么我们枚举序列中的最小值，然后再模拟生成序列的过程，每次二分找到最大的满足条件的数，就能得到最终的答案，时间复杂度为 $O(n\log n\log W)$。

当然作为一篇严谨的题解，我们还需要补充说明一下，按照此法生成的序列一定是一个好序列。实际上只要说明任意一个大小为 $3$ 的子序列都是合法序列就好了，以下为证明过程：

对这个生成的序列 $b$，可以根据生成序列的过程得出，$b_{i}\le \frac{b_{i+1}+b_1}{2}$，从而有 $b_{i+1}-b_1\ge 2(b_i-b_1)$。那么对任意的 $j>i$，也能得出 $b_j-b_1\ge 2(b_i-b_1)$，移项得到 $b_j-b_i\ge b_i-b_1$。

于是对任意的 $i<j<k$，必然有 $b_k-b_j\ge b_j-b_1\ge b_j-b_i$，从而推出 $2b_j\le b_i+b_k$，得到 $b_i,b_j,b_k$ 是一个合法序列，**证毕**。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200010
int T,n,a[N];
int main()
{
	scanf("%d",&T);
	while(T--){
		int ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1,nxt=1;i<=n;i=nxt){
			while(nxt<=n && a[nxt]==a[i])nxt++;
			if(nxt>n){
				ans=max(ans,nxt-i);
				break;
			}
			int j=n,cnt=1;
			while(nxt<=j){
				j=upper_bound(a+nxt,a+j,(a[i]+a[j])/2)-a-1;
				if(j<nxt)break;
				cnt++;
			}
			ans=max(ans,cnt+nxt-i);
		}
		printf("%d\n",n-ans);
	}
}
```


---

## 作者：Cry_For_theMoon (赞：5)

[传送门](https://codeforces.com/contest/1610/problem/E)

写出 $O(n^2)$ 贪心以后还以为是 DS 题，看了好久才发现直接暴力...

#### 分析：

首先，对一个序列 $a=\{a_1,a_2,...,a_n\}$，我们研究它合法的充要条件。（花了 30min 才看出来 555）

**结论：若 $x<y\in a$，且 $x$ 为最小值，$y$ 为最大值，则不存在第三个元素 $z\in a$，且 $2z\gt x+y$**。

证明：首先这是一个必要条件，否则 $\{x,y,z\}$ 三个数就不合法了。再来证明充分性：注意到一个事实，就是若一堆数的平均数为 $ave$，然后你加入一个 $ave\gt x$，那么新的 $ave$ 依旧大于 $x$。

发现你只要证明对于一个 $a$，$a$ 本身合法就行了，因为它的子序列也是符合结论的条件的。那显然你加入 $\min$ 和 $\max$，再按降序加入剩余的数，过程中大于 $ave$ 的数永远不超过 $1$ 个。证毕。

现在，考虑钦定最终序列的最小值 $a_l$，不难通过反证得出，每次我们会加入，在满足上述条件下，最小的能加入的数 $a_r$，重复这个过程即可，整个过程只关注当前选的最大的数 $maxn$，可以 $O(n^2)$ 贪心解决。

考虑优化这个过程。设 $maxn=a_l+v$，那么要新加入一个数 $x$ 必须满足 $x\ge a_l+2v$，惊奇的发现这只会执行 $O(\log n)$ 次。每次暴力二分即可。

然后你会 TLE on 5.... 原因是开始 $v=0$ 时你会爆，只要把这些都选了就行。

复杂度 $O(n \log n\log w)$。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const ll MAXN=2e5+10,INF=1e18;
ll T,n,a[MAXN],ans=INF;
void solve(){
	scanf("%lld",&n);
	rep(i,1,n)scanf("%lld",&a[i]);
	if(n<=2){
		printf("0\n");return;
	}
	ans=n-2;
	rep(i,1,n-1){
		if(a[n]==a[i]){
			ans=min(ans,(ll)(i-1));
			break;
		}
		int u=upper_bound(a+1,a+1+n,a[i])-a;
		ll cnt=u-i+1,maxn=a[u];
		while(1){
			if(u==n)break;
			ll val=maxn*2-a[i];
			if(a[n]<val)break;
			cnt++;
			u=lower_bound(a+u+1,a+1+n,val)-a;
			maxn=a[u];
		}
		ans=min(ans,n-cnt);
	}
	printf("%lld\n",ans);
}
int main(){
	scanf("%lld",&T);
	while(T--){
		solve();
	}

	return 0;
}

```



---

## 作者：Milmon (赞：3)

## 题目大意

定义：设一个单调不降的序列 $a$ 的所有数的平均数为 $x$，则 $a$ 是**糟糕的** $\Leftrightarrow a$ 中大于 $x$ 的数的个数 $>a$ 中小于 $x$ 的数的个数。

定义：一个单调不降的序列不存在它的一个子序列是糟糕的，则称这个子序列是**好的**；否则，称这个子序列是**坏的**。

给定长度为 $n$ 的单调不降的序列 $a$，求 $a$ 的好的子序列的最大长度。

测试数据组数 $T\leq 10^4$，$2\leq n\leq 2\times 10^5$，$2\leq\sum n\leq 2\times 10^5$，$1\leq a_i\leq 10^9$

## 解题思路

对于一个序列 $a$，我们尝试分析 $a$ 的长度较短的子序列是否是糟糕的。

对于 $a$ 的一个长度为 $m$ 的子序列 $b$：

- 若 $m\leq 2$，易得 $b$ 不为糟糕的序列。

- 若 $m=3$，设 $b=\{b_0,\ b_1,\ b_2\}$，其中 $b_0\leq b_1\leq b_2$，则 $b$ 是糟糕的 $\Leftrightarrow b_0<\dfrac{b_0+b_1+b_2}3<b_1\leq b_2\Leftrightarrow b_0+b_2<2b_1$。

观察发现，对于一个好的序列 $a$，其长度为 $3$ 的子序列就必须有较多的性质。猜想：是否只需要考虑长度为 $3$ 的子序列？

设长度为 $m$ 的糟糕的序列 $b$ 的中位数为 $b_i$，其中 $i=\left\lceil\dfrac m2\right\rceil$。若 $b$ 的任意一个长度为 $3$ 的子序列都不是糟糕的序列，则由糟糕的序列的定义，且 $2b_i\leq b_j+b_{n-j+1}$，则

$$
2\sum_{j=1}^mb_j=\sum_{j=1}^m\left(b_j+b_{n-j+1}\right)\geq 2mb_i
\Rightarrow
b_i\leq\frac 1m\sum_{j=1}^mb_j.
$$

又由 $b$ 为一个糟糕的序列，易得 $b_i>\dfrac 1m\sum\limits_{j=1}^mb_j$，与上式矛盾。所以我们得出了——

**引理 1：** 对于任意一个糟糕的序列 $a$，都存在它的一个长度为 $3$ 的糟糕的子序列。

对于一个坏的序列 $a$，必定存在 $a$ 的一个子序列是糟糕的，又由引理 1 得必定存在这个糟糕子序列的一个糟糕的子序列长度为 $3$，而这个长度为 $3$ 的序列也是 $a$ 的子序列，于是我们就得出了——

**引理 2：** 对于一个序列 $a$，若不存在它的一个长度为 $3$ 的子序列是糟糕的，则 $a$ 必定是好的序列。

枚举要取出的子序列的最小值 $\alpha$，此时取数上界 $\beta=n$。则下一个选择的数 $x$ 必须满足 $2x\leq a_\alpha+a_\beta$，那么只需每次考虑贪心选择序列中属于区间 $(\alpha,\ \beta)$ 的数中满足 $2x\leq a_\alpha+a_\beta$ 的最大数 $x$，并将取数上界更新为 $x$ 即可。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;

namespace solve{
	int n,a[200001];
	void main(){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",a+i);
		int now=1,answer=0;
		for(int i=1;i<=n;i++){
			while(now<=n&&a[now]==a[i])now++;
			if(now==n+1){
				answer=max(answer,now-i);
				break;
			}
			int pre=n,tot=1;
			while(now<=pre){
				int l=now-1,r=pre-1;
				while(l<r){
					int mid=l+r+1>>1;
					if(a[mid]*2<=(a[i]+a[pre]))l=mid;
					else r=mid-1;
				}
				pre=l;
				if(pre<now)break;
				tot++;
			}
			answer=max(answer,tot+now-i);
		}
		printf("%d\n",n-answer);
	}
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--)
		solve::main();
	return 0;
}
```

---

