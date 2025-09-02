# Rating System

## 题目描述

You are developing a rating system for an online game. Every time a player participates in a match, the player's rating changes depending on the results.

Initially, the player's rating is $ 0 $ . There are $ n $ matches; after the $ i $ -th match, the rating change is equal to $ a_i $ (the rating increases by $ a_i $ if $ a_i $ is positive, or decreases by $ |a_i| $ if it's negative. There are no zeros in the sequence $ a $ ).

The system has an additional rule: for a fixed integer $ k $ , if a player's rating has reached the value $ k $ , it will never fall below it. Formally, if a player's rating at least $ k $ , and a rating change would make it less than $ k $ , then the rating will decrease to exactly $ k $ .

Your task is to determine the value $ k $ in such a way that the player's rating after all $ n $ matches is the maximum possible (among all integer values of $ k $ ). If there are multiple possible answers, you can print any of them.

## 说明/提示

In the first example, if $ k=3 $ , then the rating changes as follows: $ 0 \rightarrow 3 \rightarrow 3 \rightarrow 4 \rightarrow 6 $ .

In the second example, if $ k=0 $ , then the rating changes as follows: $ 0 \rightarrow 0 \rightarrow 0 \rightarrow 0 $ .

In the third example, if $ k=25 $ , then the rating changes as follows: $ 0 \rightarrow 4 \rightarrow 6 $ .

In the fourth example, if $ k=6 $ , then the rating changes as follows: $ 0 \rightarrow 5 \rightarrow 6 \rightarrow 6 \rightarrow 8 \rightarrow 7 \rightarrow 6 \rightarrow 8 $ .

## 样例 #1

### 输入

```
4
4
3 -2 1 2
3
-1 -2 -1
2
4 2
7
5 1 -3 2 -1 -2 2```

### 输出

```
3
0
25
6```

# 题解

## 作者：Sumikura (赞：24)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1845D)  
[CF传送门](codeforces.com/problemset/problem/1845/D)

我们发现在这个题中一个人的 Rating 总是分为三段：（每一段长度可能为零）

1. 上升到 $k$；
1. 下降时回到 $k$；
1. 上升，下降时不再回到 $k$。

举个栗子：

```
n = 10
a = 5 8 -3 5 -7 3 -4 8 -7 9
k = 15
```

在这个例子中：

$a[1] = 5$，$a[2] = 8$，$a[3] = -3$，$a[4] = 5$ 就是第一段，Rating 上升到 $k$；

$a[5] = -7$，$a[6] = 3$，$a[7] = -4$ 就是第二段，虽然会上分，但是最终都会回到 $k$；

$a[8] = 8$，$a[9] = -7$，$a[10] = 9$ 就是第三段，虽然会下分，但是不再会回到 $k$ 了。

我们是要最大化这个人**最后**的 Rating，所以我们要尽可能的排除下分所带来的影响。第二段如果没有 $k$ 的限制的话，那么 Rating 就会往下掉。我们要进行的操作，其实等价于选一个和为负的区间，把区间的贡献改为零，使得最后总和最大。假设第二段所对应区间的和为 $sum$，所有数的总和为 $num$，那么我们操作完后新 Rating 就会变为 $num - sum + 0$。

通过观察这个式子，我们发现 $sum$ 越小新 Rating 就会越大，这不就是求最小子段和吗？$k$ 就等于第一段的和。

CODE

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize(3)
using namespace std;
const int N = 5e5 + 5;
int n, m, a[N];
inline int read()
{
    int x(0), f(1); char ch(getchar());
    while(!isdigit(ch))f = (ch == '-'? -1: f), ch = getchar();
    while( isdigit(ch))x = x * 10 + ch - '0' , ch = getchar();
    return x * f;
}
signed main()
{
    for(int t(read()); t; t--)
    {
        n = read();
        for(int i(1); i <= n; i++)a[i] = read();
        int num(0), sum(0), ans(0), st(0), ans1(0);
        for(int i(1); i <= n; i++)
        {
            sum += a[i];
            if(sum > 0)sum = 0, ed = i;
            if(sum < ans)ans = sum, ans1 = ed;
        }
        //ans1和ed是用来记第一段的末尾。
        for(int i(1); i <= ans1; i++)num += a[i];
        cout << num << "\n";
    }
    return 0;
}
```

---

## 作者：formkiller (赞：13)

### Problem:
给出一个长度为 $n$ 的序列 $\{a\}$。

有一个数 $s$，第 $i$ 次操作会使 $s$ 加上 $a_i$。

设立一个下限值 $k$，使得当 $s \ge k$ 后，$s$ 不再低于 $k$。

求 $n$ 次操作后使得 $s$ 最大的整数 $k$，若有多种可能输出其中一种即可。


------------
### Solution:
不妨记 $S_i$ 为前 $i$ 个数的前缀和。那么有一个显然的结论是：最优情况下， $k$ 的一种取值为 $S_m$，其中 $1 \le m \le n$。

我们考虑进行了前 $i$ 次操作且 $s \ge k$ 成立后，进行第 $i+1$ 到 $n$ 次操作对 $s$ 产生的影响。那么在不考虑 $k$ 的保底作用下，$s + S_n-S_i$ 即为最终答案，也即这个数会小于等于真实答案。

然后我们在考虑真实答案到底怎么出现呢：$s$ 达到了某个极大值时刚好达到 $k$，后面的若干次操作使它在保底作用下不小于 $k$，最后可能有若干次操作使其增长，其中 $s$ 一直不小于 $k$。

既然最后的若干次操作摆脱了 $k$ 的限制，我们就枚举这个摆脱限制的起始位置。那么第 $i$ 次操作后面的这段操作对答案的影响即为 $S_n-S_i$。考虑前 $i$ 次操作使 $s$ 最大，即为前 $i$ 次操作中 $S_i$ 的最大值，这个最大值即为 $k$。此时在 $s$ 达到最大值 $k$ 后，经历第 $i$ 次操作后， $s = k$。


------------
### Code:
```cpp
//good luck
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <string>
# include <algorithm>
# include <vector>
# include <queue>
# include <ctime>
# include <map>

#define LL long long
#define maxn int(1e6+5)
#define is(a) (a>='0'&&a<='9')
#define iabs(a) ((a)>0?(a):(-a))
#define imax(a,b) ((a)>(b)?(a):(b))
#define imin(a,b) ((a)<(b)?(a):(b))

using namespace std;

int T,N,a[maxn];
LL sum[maxn],ma,ans,anss;

inline void read(int &x)
{
  x=0;bool f=0;char ch=getchar();
  for (;!is(ch);ch=getchar()) f|=ch=='-';
  for (;is(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
  x=f?-x:x;
}

int main()
{
//	freopen("a.in","r",stdin);
	read(T);
	while (T--) {
		ma = 0; ans = 0; anss = 0;
		read(N);
		for (int i = 1; i <= N; ++i) read(a[i]), sum[i] = sum[i-1] + a[i];
		for (int i = 1; i <= N; ++i) {
			ma = max(ma,sum[i]);
			if (ans < ma + sum[N] - sum[i]) {
				ans = ma + sum[N] - sum[i];
				anss = ma;
			}
		}
		printf("%lld\n",anss);
	}
    return 0;
}
 

```


---

## 作者：Sanyueyetu (赞：8)

# 题目传送门
[洛谷翻译](https://www.luogu.com.cn/problem/CF1845D)
# 思路
首先，很容易想到 $k$ 一定是截至某一位的前缀和。那么，应该找哪一段的前缀和呢？

注意，自从排名到达第 $k$ 位的那一刻起，排名就不会低于第 $k$ 名了。也就是说，从到达第 $k$ 位开始，直到最后一次前缀和低于 $k$ 这中间等同于完全没有任何贡献。

比较抽象，举个例子。

```cpp
7
5 1 -3 2 -1 -2 2
```
样例的最后一组数据。
最后的输出应该是 $6$。那么，排名变化应该如下：

```
第1次 5
第2次 6
第3次 6
第4次 8
第5次 7
第6次 6
第7次 8
```
我们可以看到，第 $2$ 次排名第一次到达 $6$，之后第 $6$ 次排名最后一次低于 $6$，但是因为 $k$ 的存在又回到 $6$。所以这之间是不是可以看作没有任何贡献？

所以我们唯一要做的就是确定一段后缀，以及一段前缀，这两段之间可以像上面的例子中第 $2$ 次到第 $6$ 次之间一样忽略，然后最大化这一段前缀和后缀的和。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t, n, ans, a[300010];
long long sum[300010],qian[300010],maxsum,hou[300010];
//qian代表前缀和，hou代表后缀和，sum[i]代表截至第i位的最大前缀和
int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		maxsum=0;
		ans = 0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			qian[i]=qian[i-1]+a[i];
			sum[i]=maxsum=max(maxsum,qian[i]);
		}
		maxsum=-1e9;
		for(int i=n;i>=0;i--){
			hou[i]=hou[i+1]+a[i];
			if(maxsum<sum[i]+hou[i+1]){//最大化前缀和+后缀和
				maxsum=sum[i]+hou[i+1];
				ans=sum[i];
			}
		}
		cout << ans << endl;
	}
}
```


---

## 作者：Louis_lxy (赞：4)

我们先令 $k=sum_i$，此时我们发现，原先可能降到 $k$ 一下的地方，现在最多降到 $k$，显然我们就要最大化 $sum_i-\min_{j=i+1}^n sum_j$ 的值。我们只需要从后往前遍历前缀和数组，然后用个变量统计已经遍历到的最小值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 1;
int _, n, a[N];
long long sum[N], mn, mx, res;

int main()
{
	scanf("%d", &_);
	while (_--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
		res = sum[n], mn = sum[n], mx = 0;
		for (int i = n - 1; i >= 0; --i)
		{
			if (sum[i] - mn > mx) mx = sum[i] - mn, res = sum[i];
			mn = min(mn, sum[i]);
		}
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：Register_int (赞：2)

首先一个结论，答案必为 $\sum^m_ia_i$ 的形式。我们可以把设 $k$ 转化为从某一个位置起“截断”，即贡献清 $0$，这一位以后以 $k=0$ 的情况计算，再将前段的贡献加回。如果设的 $k$ 导致它在前面就被“截断”怎么办？由于“截断”只会增大当前和，所以后面计算的部分反而比第一次“截断”小，不必判断。

接下来，问题就变成了对每一个后缀计算这个值。每次在前面添加一个数时，我们记录当前因“截断”而应该少扣的部分，以及当前的后缀和。由于添加负数没有影响，添加整数会让整段抬高，因此直接与少扣的部分抵消即可。

总时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;
int t, n;

ll a[MAXN], s[MAXN], sum, res, mp, ans;

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n), sum = res = ans = mp = 0, s[n + 1] = 0;
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for (int i = n; i; i--) sum = max(0ll, sum - a[i]), res += a[i], s[i] = res + sum;
		sum = res = 0;
		for (int i = 1; i <= n; i++) {
			res = max(res, sum += a[i]);
			if (mp < res + s[i + 1]) mp = res + s[i + 1], ans = res;
		}
		printf("%lld\n", ans);
	}
}
```

---

## 作者：User_Unauthorized (赞：1)

## 题面
给定一个长度为 $n$ 数列 $a$，保证每项都不为 $0$。初始时 $x=0$，然后对于 $1\le i\le n$，按顺序进行如下操作：

- 如果 $x\ge k$，则 $x\rightarrow \max(k, x+a_i)$，否则 $x\rightarrow x+a_i$。

你需要求出 $k$，使得 $x$ 的值尽量大。

## 题解
如果我们不考虑 $k$ 的影响，将 $x$ 的变化曲线画出来，可以发现为一段折线。下面考虑 $k$ 的影响：可以使一段趋势为向下的折线变化量为 $0$，那么 $k$ 对总答案的贡献即为改变的这一段折线的变化量。考虑最大化该变化量，即在原数列中寻找最小区间和。

考虑处理出原数列的前缀和 $sum$，计算时枚举右端点 $r$，以 $r$ 为右端点的区间最小区间和为 $sum_r - \max\limits_{1 \le l < r} sum_l$，开一个变量维护即可。总复杂度 $\mathcal{O}(n)$。

## Code
```cpp
//CodeForces - 1845D
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::pair<valueType, valueType> ValuePair;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        ValueVector source(N);

        for (auto &iter: source)
            std::cin >> iter;

        std::partial_sum(source.begin(), source.end(), source.begin());

        ValuePair ans(0, 0);

        valueType maxSum = 0;

        for (auto const &iter: source) {
            ans = std::min(ans, std::make_pair(iter - maxSum, maxSum));

            maxSum = std::max(maxSum, iter);
        }

        std::cout << ans.second << '\n';
    }
}
```

---

## 作者：Wf_yjqd (赞：1)

太颓了，这么晚才来补题。

------------

考虑形式一定为，前若干个后 $x$ 增加到超过 $k$，然后抵挡一段本应下降的区间使得 $x$ 不变，最后 $x$ 可能会再增加。

考虑枚举后两种情况中间的断点，用前缀和维护最后增加的数。

如何贪心地选择 $k$ 呢？

可以将 $k$ 设为前缀和的最大值，然后让 $x$ 到达 $k$ 后不在下降，这样一定最优。

复杂度 $\operatorname{O}(n)$。

------------

放个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=3e5+84;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
inline void write(register ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return ;
}
ll T,n,a[maxn],mx,ans,anss;
int main(){
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++)
            a[i]=read()+a[i-1];
        ans=anss=mx=0;
        for(int i=1;i<=n;i++){
            if(mx+a[n]-a[i]>ans){
                ans=mx+a[n]-a[i];
                anss=mx;
            }
            mx=max(mx,a[i]);
        }
        write(anss);
        putchar('Sherry');
    }
    return 0;
}
```


---

## 作者：xs_siqi (赞：1)

应当采用 dp 解决此题。

首先发现一个性质，当 $x$ 大于等于 $k$ 后再也不会低于 $k$ 了。

然后这道题就转化为了：求最大不下降子序列，但是可以在任意时刻使用一次道具使得串保持在 $k$ 及以上。

记 $f_{i,0}$ 表示不使用这个道具的价值，$f_{i,1}$ 为使用过这个道具后的价值。

不难得出，$f_{i,0}=f_{i-1,0}+a_i$。对于选取这个道具的情况则要分类讨论：

首先根据贪心，必然是在前面一段正数区间，后面一段负数区间中过度的点使用这个道具的，所以对于 $a_{i-1}<0$ 且 $a_i>0$，有 $f_{i,1}=\max{f_{j,0}}$，且 $j\in [1,i-1]$。这里注意不一定从上一个转移过来，因为你可以一直保持前面的一段极大区间一直处于那样的高度。

对于 $a_{i}<0$，有 $f_{i,1}=f_{i-1,0}$，因为使用了道具，负数我无论如何也不取。

对于 $a_{i}>0$，有 $f_{i,1}=f_{i-1,0}+a_i$，即使使用了道具，正数我也要取。

但是答案让我们求的是这个道具 $k$ 值定成什么，所以对于循环枚举中，实时判断是否有 $f_{i,0}$ 大于最大值或 $f_{i,1}$ 大于最大值。

我们发现瓶颈在于求最大值的枚举，前缀最大值优化即可。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e5+5;
int Max,p,cnt,t,n,f[maxn][2],max0;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		Max=max0=cnt=p=0;
		for(int i=1;i<=n;i++)f[i][0]=f[i][1]=0;
		for(int x,l=0,i=1;i<=n;i++){
			scanf("%lld",&x);
			Max+=x,cnt+=x;
			f[i][0]=f[i-1][0]+x;
			max0=max(max0,f[i][0]);
			if(l>=0&&x<0)f[i][1]=max0;
			else if(l<0&&x<0)f[i][1]=f[i-1][1];
			if(x>=0)f[i][1]=f[i-1][1]+x;
			if(f[i][1]>=Max){
				Max=f[i][1];
				if(x<0)p=f[i][1];}
			if(f[i][0]>=Max)Max=f[i][0];
			l=x;}
		printf("%lld\n",Max==cnt?max0:p);}
	return 0;}
```


---

## 作者：Asedwai (赞：0)

由于太蠢了，提供一种 $O(\sum{n\log{n}})$ 的做法。  
## 思路
  考虑枚举 $k$，我们记 $\displaystyle sum_i=\sum_{j=1}^{i}{a_j}$。通过贪心我们可以知道 $k$ 只能取 $sum_i$ 满足 $\displaystyle sum_i>\max_{j=1}^{i-1}\{sum_j\}$。设 $k=sum_i$，那么它的贡献应该是 $k$ 加上区间 $[i+1,n]$，限制 $k$ 为 $0$（不与前面干扰）的值。这样就转化为一个更小的子问题。  

  如何求对于某个区间 $[l,n]$，初始 $x=0,k=0$ 得到的值呢？我们仍然求出前缀和 $sum$。我们发现：如果存在 $sum_i<0$，那么从区间开始到 $i$ 的贡献都不会计算，这个区间的贡献值变为了区间 $[i+1,n]$，限制 $k=0$ 的贡献值（但是必须满足 $i$ 最小）；否则它的贡献就是 $sum_n-sum_{l-1}$。
  
  现在结合起来，即在区间 $[l+1, n]$ 中询问 $sum_i-sum_l<0$ 的最小 $i$。移项后可以用线段树维护。由于每个小询问不会同时依赖彼此，并且最多只有 $n$ 种不同的询问区间，所以可以用 $O(n\log{n})$ 的时间处理出来。  
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fer(i, a, b) for(int i = (a); i <= (b); i ++)
#define fel(i, a, b) for(int i = (a); i >= (b); i --)
#define LL long long
const int Maxn = 3e5 + 10;
int T; 
int n; 
LL qzh[Maxn]; 
struct tree_Segment {
	struct Tree_node {
		int l, r; 
		LL val; 
	};
	Tree_node s[Maxn * 4]; 
#define Ls(i) (i << 1)
#define Rs(i) ((i << 1) | 1)
	inline void build(int i, int l, int r) {
		s[i].l = l, s[i].r = r; 
		if(l == r) {
			s[i].val = qzh[l]; 
			return ; 
		}
		int mid = l + r >> 1; 
		build(Ls(i), l, mid); 
		build(Rs(i), mid + 1, r); 
		s[i].val = min(s[Ls(i)].val, s[Rs(i)].val); 
	}
	inline int query(int i, int l, int r, LL x) {
		if(l > r) return -1; 
		if(s[i].val >= x) return -1; 
		if(s[i].l == s[i].r) return s[i].l; 
		int ans = -1; 
		if(ans == -1 && s[Ls(i)].r >= l && s[Ls(i)].val < x) ans = query(Ls(i), l, r, x); 
		if(ans == -1 && s[Rs(i)].l <= r && s[Rs(i)].val < x) ans = query(Rs(i), l, r, x); 
		return ans; 
	}
} s; 
int f[Maxn]; 
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr); 
	cin >> T; 
	while(T --) {
		cin >> n; 
		fer(i, 1, n) {
			cin >> qzh[i]; 
			qzh[i] += qzh[i - 1]; 
		}
		s.build(1, 1, n); 
		fel(i, n, 0) {
			int t = s.query(1, i + 1, n, qzh[i]); 
			if(t == -1) f[i] = i; 
			else f[i] = f[t];
		}
		LL mx = -1; 
		LL ansd, ansv = -1; 
		fer(i, 0, n) {
			if(qzh[i] > mx) {
				LL t = qzh[n] - qzh[f[i]] + qzh[i]; 
				if(t > ansv) {
					ansv = t; 
					ansd = qzh[i]; 
				}
				mx = qzh[i]; 
			}
		}
		cout << ansd << endl; 
	}
	return 0; 
}
```

---

## 作者：ka_da_Duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1845D)

观察原题的式子，当 $x$ 上升到 $k$ 时，$x$ 便不会再掉下去，这时候，$k$ 就起到了一个保底的作用。

我们考虑枚举最佳保底点，很显然，要使保底点最优，那么它一定是一个前缀和。上升到 $k$ 是一个必要的过程，其贡献即为最佳保底点前的所有前缀和的最大值。在后面 $x$ 持续上升的过程中，直接计算即可。

```cpp
#include <bits/stdc++.h>
#define int long long
 
using namespace std;
const int maxn = 3e5 + 10;
 
int n, mx, ans, res;
int s[maxn];
 
void solve() {
    cin >> n;
    for (int i = 1, x; i <= n; ++i) cin >> x, s[i] = s[i - 1] + x;
    mx = ans = res = 0;
    for (int i = 1; i <= n; ++i) {
        mx = max(mx, s[i]);
        if (ans < mx + s[n] - s[i]) ans = mx + s[n] - s[i], res = mx;
    } cout << res << '\n';
}
 
signed main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) 
        solve();
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

所以说到了提高、省选这一块的时候，思维的要求就会慢慢变高。

显然，这个人的 $x$ 会经历三段：

1. $x<k$；
2. $x\ge k$，且最终落回 $k$；
3. $x\ge k$，且不再落回 $k$。

当然，我们允许这些段的长度为 $0$。

那么这当中，对这个人有帮助的是哪一段呢？很显然，只有中间那一段。那么我们一定能得到中间这一段原始权值之和应为非正数，且现在等价于没有加权值。

显然，这个操作等价于将整个序列的原始权值之和减去这一段的和。当然，我们也允许这一段的长度为 $0$。显然，我们只需要这一段的和尽量小就可以了。

我并不能证明出对于任意一个区间区间都一定能够有一个 $k$ 对应，但根据我们的定义以及计算方法，最小的部分之后一个位置显然是非负的，因此，我们能够枚举到的区间都是合法的。

就这样，一道看起来让人无从下手的题被转化成了最小区间和。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[300005],ap,ip,sm,mv,k;
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n; ap=ip=sm=mv=k=0;
		for(int i=1;i<=n;++i){
			cin>>a[i],sm+=a[i];
			if(sm>0) sm=0,ip=i;
			else if(sm<mv) ap=ip,mv=sm;
		}
		for(int i=1;i<=ap;++i) k+=a[i];
		cout<<k<<endl;
	}
	return 0;
}
```

---

## 作者：OIer_Hhy (赞：0)

又是切~~水~~题的一天。

这道题，一看到，就知道应该先用一个前缀和。

不难知道，最大值所对应的 $k$ 一定是 前缀和数组 $pre$ 中的一个数。

用一个变量 $mx_i$ 记录 $pre_1,pre_2,\dots,pre_i$ 中的最大值，则 $x_i$ 为 $mx_i+pre_n-pre_i$（即 $pre_1,pre_2,\dots,pre_i$ 中的最大值加上后面的数之和）。

枚举每一个 $i$，不断更新最大值，结果就是使 $x$ 最大的 $mx$ 了。

my code:
```cpp
#include <bits/stdc++.h>
#define int __int128
using namespace std;
namespace FIO{
	#define MP make_pair
	#define F first
	#define S second
	#define R register
	#define I inline
	#define Pii pair<int,int>
	#define D isdigit
	#define A isalpha
	#define MS memset
	#define SO sizeof
	double fpow(double a,int n){
		double ans=1;
		while(n){
			if(n&1) ans*=a;
			a*=a;
			n>>=1;
		}
		return ans;
	}
	void readI(int &x){
		x=0;
		int f=1,c=getchar();
		while(!D(c)){
			if(c=='-') f=-1;
			c=getchar();
		}
		while(D(c)){
			x=(x<<1)+(x<<3)+(c^48);
			c=getchar();
		}
		x=f*x;
	}
	void put(int x){
		if(x<0){
			putchar('-');
			put(-x);
			return ;
		}
		if(x>=10) put(x/10);
		putchar(x%10+48);
	}
	void writeI(int x,char end){
		put(x);
		putchar(end);
	}
	int readS1(char*&s){
		memset(s,0,sizeof s);
		int c=getchar(),len=0;
		while(c==' '||c=='\n') c=getchar();
		while(c!=' '&&c!='\n'){
			s[len++]=c;
			c=getchar();
		}
		return len;
	}
	void writeS1(char*s,char end){
		int len=strlen(s);
		for(int i=0;i<len;i++) putchar(s[i]);
		putchar(end);
	}
	int readS2(string &s){
		s="";
		int c=getchar(),len=0;
		while(c==' '||c=='\n') c=getchar();
		while(c!=' '&&c!='\n'){
			s+=c;
			len++;
			c=getchar();
		}
		return len;
	}
	void writeS2(string s,char end){
		int len=s.size();
		for(int i=0;i<len;i++) putchar(s[i]);
		putchar(end);
	}
	void readC(char &c){
		c=getchar();
	}
	void writeC(char &c){
		putchar(c);
	}
	void readD(double &d){
		int x=0,f=1,c=getchar(),len=-1;
		double y=0;
		while((!D(c))&&(c!='.')){
			if(c=='-') f=-1;
			c=getchar();
		}
		while(D(c)||c=='.'){
			if(c=='.') len=0;
			else{
				if(len==-1) x=(x<<1)+(x<<3)+(c^48);
				else y+=(c^48)*fpow(0.1,++len);
			}
			c=getchar();
		}
		d=(x+y)*f;
	}
	void writeD(double d,int len,char end){
		int x=d;
		double y=d-x;
		put(x);
		if(abs(y)>1e-6) putchar('.');
		while(abs(y)>1e-6&&len--){
			int k=y*10;
			putchar(k+48);
			y=y*10-k;
		}
		while(len>0) len--,putchar('0');
	}
}
using namespace FIO;
const int N=3e5+20;
int t,n,a[N],pre[N],mx,ans,ansk;
I void solve(){
	readI(n);
	for(int i=1;i<=n;i++) readI(a[i]),pre[i]=pre[i-1]+a[i];
	mx=ans=ansk=0;
	for(int i=1;i<=n;i++){
		mx=max(mx,pre[i]);
		if(ans<mx+pre[n]-pre[i]){
			ans=mx+pre[n]-pre[i];
			ansk=mx;
		}
	}
	writeI(ansk,'\n');
}
signed main(){
	readI(t);
	while(t--) solve();
	return 0;
}



```

[彩蛋](https://www.luogu.com.cn/paste/5hml6obj)

---

