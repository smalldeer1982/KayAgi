# Array Craft

## 题目描述

For an array $ b $ of size $ m $ , we define:

- the maximum prefix position of $ b $ is the smallest index $ i $ that satisfies $ b_1+\ldots+b_i=\max_{j=1}^{m}(b_1+\ldots+b_j) $ ;
- the maximum suffix position of $ b $ is the largest index $ i $ that satisfies $ b_i+\ldots+b_m=\max_{j=1}^{m}(b_j+\ldots+b_m) $ .

You are given three integers $ n $ , $ x $ , and $ y $ ( $ x > y $ ). Construct an array $ a $ of size $ n $ satisfying:

- $ a_i $ is either $ 1 $ or $ -1 $ for all $ 1 \le i \le n $ ;
- the maximum prefix position of $ a $ is $ x $ ;
- the maximum suffix position of $ a $ is $ y $ .

If there are multiple arrays that meet the conditions, print any. It can be proven that such an array always exists under the given conditions.

## 说明/提示

In the second test case,

- $ i=x=4 $ is the smallest index that satisfies $ a_1+\ldots +a_i=\max_{j=1}^{n}(a_1+\ldots+a_j)=2 $ ;
- $ i=y=3 $ is the greatest index that satisfies $ a_i+\ldots +a_n=\max_{j=1}^{n}(a_j+\ldots+a_n)=2 $ .

Thus, the array $ a=[1,-1,1,1] $ is considered correct.

## 样例 #1

### 输入

```
3
2 2 1
4 4 3
6 5 1```

### 输出

```
1 1
1 -1 1 1
1 1 -1 1 1 -1```

# 题解

## 作者：Linge_Zzzz (赞：5)

题意不再赘述。

# Sol

注意到关键条件 $x>y$。

要想使 $x$ 成为前缀最大值，那么必然有 $a_{x+1}=-1$，同理有 $a_{y-1}=-1$。

不妨先把 $y$ 到 $x$ 先填上 $1$，这样肯定不劣。

现在考虑 $1$ 到 $y-1$ 以及 $x+1$ 到 $n$ 怎么填。一开始我把这些全填了 $-1$，吃了一发罚时。

为什么呢，考虑 $n=8,x=5,y=4$，那么根据上面的构造有 $a=-1,-1,-1,1,1,-1,-1,-1$。其前缀最大在 $1$ 而不是 $5$。

现在我们有了一个新方向。让 $1$ 到 $y-1$ 以及 $x+1$ 到 $n$ 的和的绝对值尽可能小，那么直接从 $x+1$ 到 $n$ 交替填 $-1,1$ 即可，$y$ 同理。

对于刚才那个例子，我们有 $a=-1,1,-1,1,1,-1,1,-1$。满足要求。

为什么是对的呢，在后文我们只考虑前缀最大值，后缀最大值同理。

首先 $x>y$，那么 $x-y+1\geq 2$，只要我们保证了 $\sum_{i=1}^{y-1}a_i\geq -1$，那么最大值一定是正数，就不会出现刚才的情况。

考虑 $y-1$ 的奇偶性，如果奇数，和为 $-1$，否则和为 $0$。满足要求。

# Code

```cpp
#include <iostream>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int a[N];
void solve(){
	int n,x,y;
	cin>>n>>x>>y;
	fill(a,a+1+n,0);
	for(int i=x+1;i<=n;i++)a[i]=-1;
	for(int i=1;i<y;i++)a[i]=-1;
	for(int i=1;i<=n;i++){
		if(a[i]==-1)cout<<-1<<' ';
		else cout<<1<<' ';
	}
	cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：CoderMeow (赞：1)

# CF1990B 题解

## 题意简述

构造一个给定长度的由 $-1,1$ 组成的数列，满足其最大前缀和的结束位置（若有多个取最小结束位置）和其最大后缀和的起始位置（若有多个取最大起始位置）分别为给定位置 $x,y$，其中保证 $y>x$。

## 构造思路

赛时感觉还是容易想到的。

先从局部开始：关注 $x,y$ 位置及其周边。首先，$x,y$ 位置必然为 $1$，否则不包含该位置的前/后缀和是更大的。其次，$x+1,y-1$ 位置必然为 $-1$，否则包含该位置的前/后缀和是更大的。最后，$y+1,y+2,\dots,x-2,x-1$ 等位置填充 $1$ 是可行的。这样保证在 $x$ 到 $y$ 间的前/后缀和都小于终于 $x$/始于 $y$ 的前/后缀和.

然后还剩下 $x+1$ 位置后方的和 $y-1$ 位置前方的部分。如果这两部分全部填上 $-1$，那么可能在 $y$ 到 $x$ 段的前/后缀和得到的补偿小于到 $y$/$x$ 前/后缀和付出的代价。如果全填充 $1$，则有很大可能前/后缀和经过 $x+1$/$y-1$ 位置后继续延伸可以得到更大的和。那么不难想到一种维持平衡的方法：$1$ 与 $-1$ 间隔填充上。如此，有且仅有 $y$ 至 $x$ 段会有连续的 $1$ 出现，其余部分的前缀和的绝对值小于等于 $1$。在连续加上至少 $2$ 个 $1$ 后，前/后缀和必然大于上述两个剩余的部分。

## Code

根据上述构造思路不难实现。

赛时记录：[Code](https://codeforces.com/contest/1990/submission/271553329)

---

## 作者：MrJC_Pandingding (赞：0)

### [题](https://codeforces.com/contest/1990/problem/B)[目](https://www.luogu.com.cn/problem/CF1990B)
### 解题思路
$a$ 的最大前缀位置为 $x$，则 $\sum_{x+1}^i\le0(x+1\le i\le n)$；$a$ 的最大后缀位置为 $y$，则 $\sum_i^{y-1}\le0(1\le i\le y-1)$。因此，令 $a_y\sim a_x$ 为 $1$，其余的数 $-1$ 和 $1$ 交替即可。
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,x,y;
int main()
{
	int i;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&n,&x,&y);
		if(!(y&1))
			printf("-1 ");
		for(i=1;i<=(y-1>>1);++i)
			printf("1 -1 ");
		for(i=y;i<=x;++i)
			printf("1 ");
		for(i=1;i<=(n-x>>1);++i)
			printf("-1 1 ");
		if((n^x)&1)
			printf("-1 ");
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Cyx20110930 (赞：0)

# 简要题意

给定 $n,x,y$，问是否可以构造一序列 $a$，使：
$$
\forall 1 \le i \le n,a_i \in \set{1,-1}
$$
$$
\sum_{
\begin{subarray}{l}
   1\le i \le x
\end{subarray}}a_i=max_{1 \le j \le n}{\sum_{
\begin{subarray}{l}
   1\le k \le j
\end{subarray}}a_k}
$$
$$
\sum_{
\begin{subarray}{l}
   y\le i \le n
\end{subarray}}a_i=max_{1 \le j \le n}{\sum_{
\begin{subarray}{l}
   j\le k \le n
\end{subarray}}a_k}
$$

# Solution

分析易得：

$x$ 是最大前缀和的下标是因为：

+ 当我选中第 $i(1\le i < x)$ 个下标时，有：
$
\sum_{
\begin{subarray}{l}
   i\le j \le x
\end{subarray}}a_j>0
$

+ 当我选中第 $i(x < i \le n)$ 个下标时，有：
$
\sum_{
\begin{subarray}{l}
   i\le j \le x
\end{subarray}}a_j<0
$

同理，$y$ 是最大后缀和的下标是因为：

+ 当我选中第 $i(1\le i < y)$ 个下标时，有：
$
\sum_{
\begin{subarray}{l}
   i\le j \le y
\end{subarray}}a_j<0
$

+ 当我选中第 $i(y < i \le n)$ 个下标时，有：
$
\sum_{
\begin{subarray}{l}
   y\le j \le i
\end{subarray}}a_j>0
$

首先易得 $x,y$ 处应填 $1$。

注意到 $x>y$，那么在 $(x,y)$ 处也应填 $1$。

那么 $[1,y)$ 呢？

为了满足 $
\sum_{
\begin{subarray}{l}
   i\le j \le x
\end{subarray}}a_j>0
$

一种简单易想的方法是填 $-1,1,-1,1,-1,...,-1$，注意 $y-1$ 处要填 $-1$，再交替往前填。

这样可以保证从头开始的和最大 $0$，最小 $-1$，而 $[x,y]$ 至少有两个 $1$ 可以让 $y$ 拿到最大值地位。

由对称性得，$(x,n]$ 同理，只需填 $-1,1,-1,1,-1,...,-1$，注意 $x+1$ 处要填 $-1$，再交替往前填。

综上，我们用 $O(\sum n)$ 的时间复杂度做出了这题。

# Code

马蜂丑见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
          int n,x,y;
          cin>>n>>x>>y;
          int i=1;
          for(;i<y;i++)cout<<((y-i)%2?-1:1)<<' ';
          for(;i<=x;i++)cout<<"1 ";
          for(;i<=n;i++)cout<<((i-x)%2?-1:1)<<' ';
          cout<<'\n';
	}
        return 0;
}
```

---

## 作者：liugh_ (赞：0)

## [Array Craft](https://www.luogu.com.cn/problem/CF1990B)

> 给定三个整数 $n,x,y$（$x>y$），构造一个长度为 $n$ 的序列 $a$ 满足：
> 
> - $\forall 1\le i\le n,a_i\in \{-1,1\}$。
> - 满足 $\sum_{j=1}^i a_j=\max_{j=1}^{n}\sum_{k=1}^j a_k$ 的最小索引 $i=x$。
> - 满足 $\sum_{j=i}^n a_j=\max_{j=1}^{n}\sum_{k=j}^n a_k$ 的最大索引 $i=y$。
>
> $n\le 10^5$。

我们记 $pre_i=\sum_{j=1}^i a_j,suf_i=\sum_{j=i}^n a_j$。首先，显然必须有 $a_x=a_y=1$。**条件 $x>y$ 非常关键**，由此可知 $[y,x]$ 内全填 $1$ 是最优的，因为 $[y,x]$ 内 $-1$ 越多 $suf_y$ 和 $pre_x$ 就会越小。

接下来，$[1,y)$ 填什么更优？自然地想到全填 $-1$，但会发现当 $y-1>x-y+1$ 即 $y>x/2+1$ 时，全填 $-1$ 是不可行的，$[y,x]$ 中的 $1$ 不够补回来。那么可不可以只把 $-1$ 用到恰到好处呢？答案是肯定的。不论 $y$ 是偶数还是奇数，都可以控制 $[1,y)$ 内 $-1$ 和 $1$ 的数量之差的绝对值小于 $1$，**条件 $x>y$ 非常关键**，由此可知 $[y,x]$ 内至少有两个 $1$，是一定够补回来的。

最后，$-1$ 和 $1$ 按什么顺序填？为了保住 $y$ 的后缀最大值地位，从 $y-1$ 向前开始一定要先填 $-1$ 再填 $1$，因此有一种好写的做法就是 $a_{y-1}=-1,a_{y-2}=1,a_{y-3}=-1,\ldots$，交替进行。$(x,n]$ 同理。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<algorithm>
#include<cassert>
#include<bitset>
#include<list>
#include<iomanip>
#ifdef ONLINE_JUDGE
#define getchar() (_p==_q&&(_q=(_p=_b)+fread(_b,1,_s,stdin),_p==_q)?-1:*_p++)
#define putchar(x) ((_r-_o<_s)?(*_r++=x):(flush(),_r=_o,*_r++=x))
#endif
#define inline inline __attribute__((__always_inline__))
#define flush() fwrite(_o,_r-_o,1,stdout),fflush(stdout)
using namespace std;const int _s=1<<20;char _b[_s],_o[_s],*_p=_b,*_q=_b,*_r=_o;template<class T>inline bool fr(T&x){x=0;char c=0;bool f=0;do{if((c=getchar())==-1)return 0;if(c=='-')f=1;}while(c<48||c>57);do {x=x*10+c-48;if((c=getchar())==-1)break;}while(c>47&&c<58);if(f)x=-x;return 1;}template<class T>inline void fw(T x){char _d[40],_l=-1;if(x<0)x=-x,putchar('-');do _d[++_l]=x%10+48;while(x/=10);do putchar(_d[_l]);while(~--_l);}

#define int long long
const int maxn=2e5+3;

int n,x,y,a[maxn];

signed main(){
    // ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cerr.tie(0);
    // freopen("2.in","r",stdin);
    // freopen("2.out","w",stdout);
    
    int cse;fr(cse);while(cse--){
        fr(n),fr(x),fr(y);
        for(int i=y;i<=x;i++)a[i]=1;
        for(int i=y-1;i>=1;i--)a[i]=a[i+1]*-1;
        for(int i=x+1;i<=n;i++)a[i]=a[i-1]*-1;
        for(int i=1;i<=n;i++)fw(a[i]),putchar(32);
        putchar(10);
    }
    flush(),exit(0);
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
$y<x$？第一反应：$a_1\sim a_{y-1}=-1,a_y\sim a_x=1,a_{x+1}\sim a_n=-1$。然后你会开心地发现你 WA Pretest #2 了。这里给出一组 Hack：`6 2 1`。

终于明白为什么是 $y<x$ 而不是 $y\le x$ 了。我们只要 $a_y\sim a_x=1$，前后两端都是 $-1,1$ 交替就行辣。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, x, y;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> x >> y;
		for (int i = y - 1; i; -- i)
			cout << (i & 1 ? "-1 " : "1 ");
		for (int i = y; i <= x; ++ i)
			cout << "1 ";
		for (int i = 1, tmp = n - x; i <= tmp; ++ i)
			cout << (i & 1 ? "-1 " : "1 ");
		cout << '\n';
	}
	I AK IOI
}
```

---

## 作者：tder (赞：0)

考虑构造 $a=\{\cdots,1,-1,1,1,\cdots,1,1,-1,1,\cdots\}$，其中：

- $a_y$ 至 $a_x$ 均为 $1$；
- $a_y$ 以前和 $a_x$ 以后均为 $\pm1$ 交替；
- $a_{y-1}$ 和 $a_{x+1}$ 为 $-1$。

容易发现 $x$ 一定为最大前缀，且 $y$ 为最大后缀。

下面给出简单证明。

令 $f(l,r)=\sum\limits_{i=l}^r a_i$。特别的，$g(r)=f(1,r)$。

> 结论 1：对于 $y\le k<x$，$g(k)<g(x)$。
> 
> 证明 1：显然的。$a_y$ 至 $a_x$ 均为 $1$，往后多加 $1$ 必定更大。

> 结论 2：对于 $k<y$，$g(k)<g(x)$。
>
> 证明 2：若 $a_1=1$，则当 $k<y$ 时 $g(k)\in\{0,1\}$，而 $g(y)=1$，故此 $g(k)\le g(y)$。由结论 1，$g(y)<g(x)$，故 $g(k)<g(x)$。反之 $a_1=-1$ 同理。

> 结论 3：对于 $k>x$，$g(k)\le g(x)$。
> 
> 证明 3：此时 $f(x+1,k)\in\{-1,0\}$，故 $g(k)=g(x)+f(x+1,k)\le g(x)$。

综合上述结论，我们知道：

- $g(x)$ 是所有 $g(i)$ 中最大的；
- 对于所有满足 $g(k)=g(x)$ 的 $k$ 都有 $k\ge x$。

故 $x$ 是最大前缀，$y$ 是最大后缀相当于是 reverse 一下，同理可证。

---

## 作者：EricWan (赞：0)

我们发现题目数据范围有 $x>y$，观察发现，把 $y$ 和 $x$ 中间的部分全部填 $1$ 肯定是最优的（证明就不放了，证明比较简单）。

之后我们需要考虑两边都填什么，发现 $a_{x+1}$ 和 $a_{y-1}$ 都不得不填 $-1$，否则就不能满足题目要求了。毕竟有 $y$ 到 $x$ 这一段为答案的正确性做贡献了，我们只需要让两边尽量稳定就可以。想要让他们的前缀和和后缀和尽量稳定，我们可以交叉地填 $1$ 和 $-1$，因为 $a_{x+1}$ 和 $a_{y-1}$ 已经确定了，我们模拟一遍就可以，这样构造是可以证明是对的。

代码主体：

```cpp
for (int i = y; i <= x; i++) b[i] = 1;
for (int i = y - 1; i >= 1; i--) b[i] = b[i + 1] * -1;
for (int i = x + 1; i <= n; i++) b[i] = b[i - 1] * -1;
```

---

## 作者：tzzl3035 (赞：0)

# CF1990B 题解
### 题目大意
有 $t$ 组数据，每组给出三个正整数 $n$，$x$ 和 $y$。定义**最大前缀位置**为在长为 $m$ 的数组 $b$ 中满足 $b_1+\dots+b_i = \max_{j=1}^{m} (b_1+\dots+b_j)$ 的**最小索引** $i$，**最大后缀位置**为在长为 $m$ 的数组 $b$ 中满足 $b_i+\dots+b_m = \max_{j=1}^{m} (b_j+\dots+b_m)$ 的**最大索引** $i$。请构造一个长度为 $n$，由 $1$ 和 $-1$ 组成，以 $x$ 为最大前缀位置，以 $y$ 为最大后缀位置的数组。保证 $2 \le n \le 10^5$ 且 $1 \le y < x \le n$。
### 思路
既然 $y < x$，我们就可以在数组从 $y$ 到 $x$ 的地方全部填充 $1$，而在其余位置使 $1$ 和 $-1$ 交错排列，使总和尽量为 $0$。且要注意的是，数组下标为 $y-1$ 和 $x+1$ 的地方一定为 $-1$。
### 代码
``` c++
#include <bits/stdc++.h> // 万能头
using i64 = long long;

void solve() {
	// 输入
	int n, x, y;
	std::cin >> n >> x >> y;
	// 在下标比 y 小的地方交错填充 1 和 -1
	int _out;
	if(y & 1) _out = 1;
	else _out = -1;
	for(int i = 1; i < y; ++i) {
		std::cout << _out << ' ';
		_out = 0 - _out;
	}
	// 在下标由 y 至 x 的地方填充 1
	for(int i = y; i <= x; ++i) 
		std::cout << 1 << ' ';
	// 在下标比 x 大的地方交错填充 -1 和 1
	_out = -1;
	for(int i = x; i < n; ++i) {
		std::cout << _out << ' ';
		_out = 0 - _out;
	}
	std::cout << '\n'; // 多组数据记得换行

}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(nullptr);

	int t; std::cin >> t;
	// 挨组处理
	while(t--) {
		solve();
	}
	
	return 0;
}

```
### [RESULT](https://codeforces.com/contest/1990/submission/271585825)

---

