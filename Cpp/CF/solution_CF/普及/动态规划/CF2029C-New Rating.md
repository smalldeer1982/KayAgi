# New Rating

## 题目描述

Hello, Codeforces Forcescode!





Kevin used to be a participant of Codeforces. Recently, the KDOI Team has developed a new Online Judge called Forcescode.

Kevin has participated in $ n $ contests on Forcescode. In the $ i $ -th contest, his performance rating is $ a_i $ .

Now he has hacked into the backend of Forcescode and will select an interval $ [l,r] $ ( $ 1\le l\le r\le n $ ), then skip all of the contests in this interval. After that, his rating will be recalculated in the following way:

- Initially, his rating is $ x=0 $ ;
- For each $ 1\le i\le n $ , after the $ i $ -th contest, 
  - If $ l\le i\le r $ , this contest will be skipped, and the rating will remain unchanged;
  - Otherwise, his rating will be updated according to the following rules: 
      - If $ a_i>x $ , his rating $ x $ will increase by $ 1 $ ;
      - If $ a_i=x $ , his rating $ x $ will remain unchanged;
      - If $ a_i<x $ , his rating $ x $ will decrease by $ 1 $ .

You have to help Kevin to find his maximum possible rating after the recalculation if he chooses the interval $ [l,r] $ optimally. Note that Kevin has to skip at least one contest.

## 说明/提示

In the first test case, Kevin must skip at least one contest. If he chooses any interval of length $ 1 $ , his rating after the recalculation will be equal to $ 5 $ .

In the second test case, Kevin's optimal choice is to select the interval $ [3,5] $ . During the recalculation, his rating changes as follows:

 $ $$$ 0 \xrightarrow{a_1=1} 1 \xrightarrow{a_2=2} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{a_6=3} 3 \xrightarrow{a_7=4} 4  $ $ </p><p>In the third test case, Kevin must skip the only contest, so his rating will remain at the initial value of  $ 0 $ .</p><p>In the fourth test case, Kevin's optimal choice is to select the interval  $ \[7,9\] $ . During the recalculation, his rating changes as follows:</p><p> $ $  0 \xrightarrow{a_1=9} 1 \xrightarrow{a_2=9} 2 \xrightarrow{a_3=8} 3 \xrightarrow{a_4=2} 2 \xrightarrow{a_5=4} 3 \xrightarrow{a_6=4} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4  $ $ </p><p>In the fifth test case, Kevin's optimal choice is to select the interval  $ \[5,9\]$$$.

## 样例 #1

### 输入

```
5
6
1 2 3 4 5 6
7
1 2 1 1 1 3 4
1
1
9
9 9 8 2 4 4 3 5 3
10
1 2 3 4 1 3 2 1 1 10```

### 输出

```
5
4
0
4
5```

# 题解

## 作者：chen_z (赞：3)

考虑 dp。

设 $dp_{i,0}$ 表示到第 $i$ 位还未 skip 过的最大答案，明显可以直接从上一位转移。

设 $dp_{i,1}$ 表示已经 skip 过并且第 $i$ 位强制不 skip 的最大答案。

$dp_{i,1}$ 可以直接从 $dp_{i-1,1}$ 转移，也可以从前面所有的 $dp_{j,0}$ 转移，最优的转移来自前面所有 $dp_{j,0}$ 的最大值，可以顺手维护一下。

时间复杂度线性。

AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
using namespace std;
const int N=300010;
int T,n,a[N],dp[N][3];
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f; 
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i]; 
		dp[0][0]=0,dp[0][1]=-inf;
		int maxn=-inf;
		for(int i=1;i<=n;i++){
			if(i>1)maxn=max(maxn,dp[i-2][0]);
			if(a[i]>dp[i-1][0])dp[i][0]=dp[i-1][0]+1;
			else if(a[i]==dp[i-1][0])dp[i][0]=dp[i-1][0];
			else dp[i][0]=dp[i-1][0]-1;
			if(a[i]>dp[i-1][1])dp[i][1]=dp[i-1][1]+1;
			else if(a[i]==dp[i-1][1])dp[i][1]=dp[i-1][1];
			else dp[i][1]=dp[i-1][1]-1;
			if(a[i]>maxn)dp[i][1]=max(dp[i][1],maxn+1);
			else if(a[i]==maxn)dp[i][1]=max(dp[i][1],maxn);
			else dp[i][1]=max(dp[i][1],maxn-1);
		}
		for(int i=1;i<n;i++)dp[n][1]=max(dp[n][1],dp[i][0]);
		cout<<max(0ll,dp[n][1])<<'\n';
	} 
	return 0;
}
```

---

## 作者：TianTianChaoFang (赞：2)

# 思路

大致题意为：一个值 $x$ 初始为 $0$，然后有一个数组 $a$，遍历一次数组。  
如果 $a_i > x$，则 $x + 1$。  
如果 $a_i < x$，则 $x - 1$。  
如果 $a_i = x$，则 $x$ 不变。  
必须且只能跨越一段连续区间，求 $x$ 的最大可能值。  

后面的由前面的计算得到，并且前面的不受后面的影响，并且必须跳跃一段，很容易想到 DP。  

首先是 **DP 状态**。  
最优解是开三个状态来 DP，这个官方题解讲得很清楚，因此这里提供一个我赛时写的两个状态的思路。  
根据题目描述，可以连续也可以跳跃。  
因此我选择给每个点 $i$ 设两个状态：$i$ 由前一个转移得到和由更前面的跳跃得到。  
以下用 $dp_{i, 0}$ 表示第 $i$ 个点是由前面跳跃得到的，用 $dp_{i, 1}$ 表示第 $i$ 个点是由前一个点转移得到。  

首先我们可以预处理一下一次也不跳的时候，每一个点的答案是多少，把它存入 $dp_{i, 1}$ 中。这个很简单，按照题意从前往后模拟一遍即可。  

然后我们考虑要跳跃的，也就是 $dp_{i, 0}$ 的值。  
因为题目要我们只能跳一次，所以，跳跃后的值只能通过没有跳过的值来转移，也就是 $dp_{j, 1}$ 的值。  

那么问题来了，只要和 $i$ 有间隔的前面的点都可以作为转移的前置状态，选哪一个呢？  
题目要我们求的是最后结果的最大值，不难发现，贪心地想，最后结果要最大，每一个局部的结果也要尽可能大。  
因为这样的话，在 $i$ 之后，经历相同的增增减减，在最后的答案一定会更大。  
于是我们只有在这个点是增的时候才会更优，也就是在前面选择一个 $dp_{i, 0}$ 的值比 $a_i$ 小的点来转移。  
（**简单证明**：如果 $dp_{j, 1} \geq a_i$，因为是从0增上来的，那么一定可以在 $j$ 之前找到一个 $k$，满足 $dp_{k, 1} < a_i$，证毕。）  
又因为结果要尽可能的大，所以要在更小的点中选一个最大的。  
那么转移方程就出来了：$dp_{i, 0} = \max(dp_{j, 1} + 1)$，$j$ 满足 $j < i - 1$ 并且 $dp_{j, 1} < a_i$。  

不难发现，如果暴搜的话，这样的复杂度是 $O(n ^ 2)$ 的。  
那再细品一下这句话：“比 $a_i$ 更小的点中挑一个最大的。”那不就可以二分了吗。  
我们可以把 $j \in [1, i - 2]$ 的 $dp_{j, 1}$ 的值以及 $0$ 压入一个便于二分数据结构中，比如 **map** 或 **set**。  
我赛时使用的树状数组（赛后发现 **set** 或者 **map** 就可以了而且复杂度更优）。  
每次转移时，二分找到小于 $a_i$ 中最大的一个值，用来转移得到 $dp_{i, 0}$。  
这个过程可以在循环的过程中同时进行，每次处理完一个 $i$ 的 $dp_{i, 0}$ 后将 $dp_{i - 1, 0}$ 压入数据结构即可。  

到这里，我们就处理出了每一个点不跳跃到达和只跳跃一次到达能够得到的最大值。  
要得到最后答案，我们还需要从前往后来一轮 DP。  

这里我们再开一个 DP 数组 $ans$。  
$ans_{i, 1}$ 表示到 $i$ 为止没有跳跃过得到的最大值。  
$ans_{i, 0}$ 表示到 $i$ 为止跳跃过了到的最大值。  

那么转移也很明显。  
因为 $dp_{i, 1}$ 预处理的就是到 $i$ 为止没有跳跃过，所以 $ans_{i, 1} = dp_{i, 1}$。 
而 $ans_{i, 0}$ 因为表示的是到 $i$ 为止跳跃过，所以我们只需要把在跳跃到 $i$ 前面的位置和刚好跳跃得到 $i$ 这个位置的结果取个最大值。  
也就是假设跳跃到前面再不跳跃到 $i$ 的答案设为 $now$。   
如果 $ans_{i - 1, 0} < a_i$，$now = ans_{i - 1, 0} + 1$。  
如果 $ans_{i - 1, 0} > a_i$，$now = ans_{i - 1, 0} - 1$。  
如果 $ans_{i - 1, 0} = a_i$，$now = ans_{i - 1, 0}$。  
所以 $ans_{i, 0} = \max(now, dp_{i, 0})$。  
这里要特别**注意一下**，如果 $i = 1$，$ans_{1, 0}$ 应设置为一个极小值，因为 $1$ 这个点是不能通过跳跃得到的，这个状态不存在。  

最后取答案的时候，其实就是 $i \in [1, n - 1]$ 时，和 $ans_{i, 1}$ 取最小，表示前面都不跳，后面全跳。$i = n$ 时，和 $ans_{n, 0}$ 取最小，表示在前面已经跳跃过了并且到达了 $n$ 这个点。  

时间复杂度 $O(n \times \log{n})$。  
写题解的时候又想了一下，其实数据结构也可以不用，只需要记录到 $i - 1$ 这个点时 $dp_{j, 1}$ 的最大值就行了，因为是从 $0$ 增长上来的，那么从 $0$ 到 $\max(dp_{j, 1})$ 之间的数一定都出现过，这样的话 $O(n)$ 就可以了。

# AC CODE

```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 2e18
#define ull unsigned long long
#define ls o << 1
#define rs o << 1 | 1

using namespace std;

const int N = 3e5 + 9;
int a[N];
int dp[N][2];
int ans[N][2];
int t[N];
int n;

int lowbit(int x){return x & -x;}

void add(int v, int x)
{
	for(int i = v;i <= n;i += lowbit(i))t[i] += x;
}

int query(int v)
{
	int res = 0;
	for(int i = v;i;i -= lowbit(i))res += t[i];
	return res;
}

void init()
{
	for(int i = 1;i <= n;i ++)t[i] = 0;
	for(int i = 1;i <= n;i ++)
	{
		dp[i][0] = dp[i][1] = 0;
		ans[i][0] = ans[i][1] = 0;
	}
}

void solve()
{
	cin >> n;
	
	init();
	
	for(int i = 1;i <= n;i ++)cin >> a[i];
	
	int now = 0;
	for(int i = 1;i <= n;i ++)//预处理不跳跃的情况
	{
		if(a[i] > now)dp[i][1] = ++ now;
		else if(a[i] == now)dp[i][1] = now;
		else if(a[i] < now)dp[i][1] = -- now;
	}
	
	add(0 + 1, 1);
	for(int i = 2;i <= n;i ++)//得到跳到i这个位置的dp值
	{
		int pre = query(a[i]);
		int l = 0, r = a[i] + 1;
		while(l + 1 != r)//二分找最优（用set或map更优）
		{
			int mid = (l + r) >> 1;
			if(query(mid) < pre)l = mid;
			else r = mid;
		}
		dp[i][0] = r;
		add(dp[i - 1][1] + 1, 1);//将i - 1的没跳跃的dp值压入数据结构
	}
	
	for(int i = 1;i <= n;i ++)//处理到每个点为止的最优答案
	{
		ans[i][1] = dp[i][1];
		
		if(i == 1)ans[i][0] = -inf;
		else
		{
			int now = ans[i - 1][0];
			if(now > a[i])now --;
			else if(now < a[i])now ++;
			
			ans[i][0] = max(now, dp[i][0]);
		}
	}
	
	int res = 0;
	for(int i = 1;i < n;i ++)res = max(res, ans[i][1]);//跳最后一段
	res = max(res, ans[n][0]);//跳前面的
	
	cout << res << '\n';
}

signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    int t = 1;cin >> t;
    while(t --)solve();

    return 0;
}

```

---

## 作者：Super_Cube (赞：2)

# Solution

设 $dp_{i,0/1/2}$ 表示到第 $i$ 次比赛时还没进行过跳过操作，正在进行跳过操作，已经进行过跳过操作的最高 rating。设 $f(x,y)$ 为题目中的 rating 变化函数。枚举 $a_i$ 可能的状态，转移为：$dp_{i,0}=f(dp_{i-1,0},a_i),dp_{i,1}=\max(dp_{i-1,0},dp_{i-1,1}),dp_{i,2}=\max(f(dp_{i-1,1},a_i),f(dp_{i-1,2},a_i))$。初始化 $dp_{0,1}=dp_{0,2}=-\infty$，答案为 $\max(dp_{n,1},dp_{n,2})$。

# Code

```cpp
#include<bits/stdc++.h>
inline int calc(int x,int y){
	return x+(x<y?1:x==y?0:-1);
}
int dp[300005][3];
int a[300005];
int T,n;
int main(){
	dp[0][1]=dp[0][2]=0xc0c0c0c0;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;scanf("%d",&a[i++]));
		for(int i=1;i<=n;++i){
			dp[i][0]=calc(dp[i-1][0],a[i]);
			dp[i][1]=std::max(dp[i-1][0],dp[i-1][1]);
			dp[i][2]=std::max(calc(dp[i-1][1],a[i]),calc(dp[i-1][2],a[i]));
		}
		printf("%d\n",std::max(dp[n][1],dp[n][2]));
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：1)

赛时卡一年害我喜提 (-7)，然后因为这个卡一年导致没有写出 F，愤怒了。

以及这题为什么不是绿。愤怒了。

给一种 $O(n)$ 的做法，比另外一个题解少一只 $\log$。

## 解题思路

考虑动规。

记 $f_{i}$ 表示先前至少用过一次 skip 操作，仅考虑第 $i$ 场比赛时的最大 rating。

记记号：

$$\operatorname{mov}(x,l)=\begin{cases}
x-1 &\ x>l \\
x &\ x=l \\
x+1 &\ x<l \\
\end{cases}$$

可以理解为 $\operatorname{mov}(x,l)$ 表示 rating 为 $x$ 的时候打了一场 $l$ 分的比赛。

记 $pre_i$ 表示从 $x=0$ 开始连续打完前 $i$ 场比赛的最终 rating。

转移是好写的：

$$f_i=\max{(\operatorname{mov}(f_{i-1},a_i),\max\limits_{1\leq j \leq i-1} pre_j)}$$

边界为 $f_1=0$

其中 $\operatorname{mov}(f_{i-1},a_i)$ 表示之前已经 skip 过一次的情况，而 $\max\limits_{1\leq j \leq i-1} pre_j$ 表示这一次使用了 skip 的情况。

注意到使用 skip 时一定会 skip 到先前分数最大的位置，所以最优性显然。

$\max\limits_{1\leq j \leq i-1} pre_j$ 可以预处理做到 $O(1)$ 转移，$\operatorname{mov}(f_{i-1},a_i)$ 可以 $O(1)$ 计算，故时间复杂度是 $O(n)$ 的。

---

## 作者：徐晨轩✅ (赞：0)

一个不用 DP 的做法。

记 $f(x,l,r)$ 表示以初始 rating $x$，连续参加第 $l$ 场至第 $r$ 场比赛之后的 rating。

显然，若 $w_1 < w_2$，则 $\forall 1 \le l \le r \le n, f(w_1,l,r)\le f(w_2,l,r)$。

考虑枚举 skip 之后的第一场，根据上面的结论，skip 之前的 rating 越高越优。维护 $val_i$ 表示 $\max_{j=1}^i f(0,1,i)$ 即可找到最优的 skip 之前的 rating。答案即为 $\max\{\max_{i=2}^n f(val_{i-2}, i, n),val_{n-1}\}$。至于如何计算 $f(val_{i-2}, i, n)$，可以维护一个 $mx$，表示到当前为止最优的 rating（已经 skip 过后的，但不一定是刚 skip 之后的第一场），按题意模拟即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int f(int x, int y) {
    if (y > x) return x + 1;
    if (y == x) return x;
    if (y < x) return x - 1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }
        int x = 0;
        vector<int> val(n);
        for (int i = 0; i < n; i++) {
            x = f(x, a[i]);
            val[i] = x;
        }
        for (int i = 1; i < n; i++)
            val[i] = max(val[i], val[i - 1]);
        int mx = 0;
        for (int i = 1; i < n; i++) {
            mx = max(mx, (i > 1 ? val[i - 2] : 0));
            mx = f(mx, a[i]);
        }
        cout << max(mx, val[n - 2]) << endl;
    }
    return 0;
}
```

---

## 作者：Dangerise (赞：0)

~为什么我只写了 A , C 但是上青了~

注意到，如果我们不考虑 skip 这一操作，很明显当我们进行一连串的比赛的时候，我们初始的 rating 越高，那么打完一系列比赛之后的 rating 只增不减。

那么做法就是，对于一场比赛，寻找之前的一场比赛，从那一场比赛直接跳到这场比赛，使得在开始这场比赛前的初始 rating 最高。

```cpp
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

#define int long long
// #define double long double
#define il inline
#define siz(x) ((int)x.size())
#define me(a, v) memset(a, v, sizeof(a))
#define cp(a, b) memcpy(b, a, (assert(sizeof(a) == sizeof(b)), sizeof(a)))
#define L(i, l, r) for (int i = l; i <= r; i++)
#define R(i, r, l) for (int i = r; i >= l; i--)

il char gc() { return getchar(); }
il void pc(char c) { putchar(c); }
il int qread() {
    int ans = 0;
    char c = gc();
    bool f = 0;
    while (c < '0' || c > '9') {
        if (c == '-') {
            f = 1;
        }
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        ans = ans * 10 + c - '0';
        c = gc();
    }
    if (f) {
        return -ans;
    } else {
        return ans;
    }
}

constexpr int N = 3 * 114514, inf = LONG_LONG_MAX / 2 - 100;

int a[N], n, maxn[N];
signed main() {
    int t = qread();
    while (t--) {
        n = qread();
        L(i, 1, n) { a[i] = qread(); }
        int x = 0;
        L(i, 1, n) {
            maxn[i] = max(maxn[i - 1], x); 
            if (a[i] > x) {
                x++;
            } else if (a[i] < x) {
                x--;
            }
        }
        x = 0;
        L(i, 1, n) {
            x = max(x, maxn[i]);
            if (a[i] > x) {
                x++;
            } else if (a[i] < x) {
                x--;
            }
        }
        x = max(x, maxn[n]);
        if (x == n) {
            x--;
        }
        printf("%lld\n", x);
    }
    return 0;
}
```

---

## 作者：gcx12012 (赞：0)

### 前言
一个抽象的 $1\log$ 二分做法，但是适合 ds 爱好者。
### Solution
首先我们考虑 $O(n^2 \log n)$ 怎么做，显然，我们枚举可能得到的每一个答案 $k$，然后我们倒着推，初始时取值区间为 $[k,k]$。

手推发现，每碰到一个数 $a_i$ 时，如果 $l\le a_i \le r$，取值范围 $[l,r]$ 变为 $[l-1,r+1]$；如果 $a_i < l$，取值范围 $[l,r]$ 变为 $[l+1,r+1]$；否则，取值范围 $[l,r]$ 变为 $[l-1,r-1]$。

我们一直从后往前推，并预处理每个前缀经过操作后所得的 $x$，然后判断它后面的区间是否包含它即可，这个用树状数组做即可。

我们考虑怎么优化，显然我们可以把当前可能成为答案的区间 $[L,R]$ 二分，然后对右半区间进行处理，如果右半区间有答案就递归右区间，反之同理。

这样的时间复杂度就是 $O(n \log^2 n)$ 的，可以通过。

实际上也可以不写树状数组，但是我场上懒得优化了。

然后稍微注意一下细节即可。
### Code

```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 1200010
#define For(i,a,b) for(int i=a;i<=b;++i)
#define Rof(i,a,b) for(int i=a;i>=b;--i)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r 
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int>

using namespace std;
bool st;
int a[N],b[N];
int T,n;

bool ed;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int pl[N],pr[N];
int c[N];
void add(int x,int k){
	while(x<=4*n+1){
		c[x]+=k;
		x+=(x&(-x));
	}
}
int qry(int x){
	int p=0;
	while(x){
		p+=c[x];
		x-=(x&(-x));
	}
	return p;
}
bool chk(int nowl,int nowr){
	For(i,1,n) add(b[i]+n+1,1);
	pl[n+1]=nowl,pr[n+1]=nowr;
	//cout<<nowl<<' '<<nowr<<endl;
	int l=nowl,r=nowr;
	Rof(i,n,1){
		if(a[i]>=l && a[i]<=r) l--,r++;
		else if(a[i]<l) l++,r++;
		else l--,r--;
		pl[i]=l,pr[i]=r;
	}
	//For(i,1,n+1) cout<<pl[i]<<' '<<pr[i]<<endl;
	int is=0;
	Rof(i,n+1,2){
		add(b[i-1]+n+1,-1);
		nowl=min(nowl,pl[i]);
		nowr=max(nowr,pr[i]);
		if(qry(nowr+n+1)-qry(nowl+n)) is=1;
	}
	//cout<<endl;
	return is;
}
void sol(){
	n=read();
	For(i,1,n) a[i]=read();
	For(i,1,n){
		if(a[i]>b[i-1]) b[i]=b[i-1]+1;
		else if(a[i]==b[i-1]) b[i]=b[i-1];
		else b[i]=b[i-1]-1;
	}
	int l=0,r=n;
	while(l<r){
		int mid=(l+r)>>1;
		if(chk(mid+1,r)) l=mid+1;
		else r=mid; 
	}
	cout<<l<<endl;
}

int main()
{
    //fprintf(stderr,"%d",(&ed-&st)/1024/1024);
    //freopen("detect.in","r",stdin);
    //freopen("detect.out","w",stdout);
    T=read();
    while(T--) sol();
	return 0;
}
/*

*/
```

---

## 作者：daitangchen2008 (赞：0)

## 思路    
令 $f(x,y)$ 为表现为 $y$ 时遇到等级分为 $x$ 后的等级分。则：
$$f(x,y)=

\begin{cases}

x+1& \text{x>y}\\

x&  \text{x=y}\\ 

x-1& \text{x<y}\\

\end{cases}$$
设 $dp_{i,0}$ 为到第 $i$ 个时还没有取过段时的等级分最大值。显然有:  
$$dp_{i,0}=f(dp_{i-1,0},a_i)$$  
设 $dp_{i,1}$ 为到第 $i$ 个时已经去过一段时的等级分最大值。
则：
$$dp_{i,1}=\max(f(dp_{i-1,1},a_i),f(dp_{j,0},a_i)),    0<j<i-1$$    
这个过程可以使用优先队列优化，时间复杂度 $O(n \log n)$。  
答案：$\min(dp_{n,1},dp_{j,0}), 0<j<n$。
## 代码  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+10;
int a[N];
int dp[N][3];
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		priority_queue<int>q;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			dp[i][0]=dp[i][1]=0;
		dp[1][0]=1;
		dp[1][1]=0;
		if(a[2]>=2)
		dp[2][0]=2;
		else
		dp[2][0]=1;
		dp[2][1]=1;
		q.push(dp[1][0]);
		for(int i=3;i<=n;i++)
		{
			if(a[i]<dp[i-1][0])
				dp[i][0]=dp[i-1][0]-1;
			else
			if(a[i]==dp[i-1][0])
				dp[i][0]=dp[i-1][0];
			else
				dp[i][0]=dp[i-1][0]+1;
			if(a[i]<dp[i-1][1])
				dp[i][1]=dp[i-1][1]-1;
			else
			if(a[i]==dp[i-1][1])
				dp[i][1]=dp[i-1][1];
			else
				dp[i][1]=dp[i-1][1]+1;
			int x=q.top();
			if(a[i]<x)
				x=x-1;
			else
				if(a[i]==x)
					x=x;
			else
				x=x+1;
				dp[i][1]=max(dp[i][1],x);
			q.push(dp[i-1][0]);
		}
		int ans=0;
		for(int i=1;i<=n-1;i++)
			ans=max(ans,dp[i][0]);
		cout<<max(ans,dp[n][1])<<endl;
		while(q.size())
			q.pop();
	}
	return 0;
} 
```

---

## 作者：tai_chi (赞：0)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18538159) 中阅读。

#### 题意

Kevin 在打 CF 比赛，他的 rating 初始为 $0$。给出他 $n$ 场比赛每场的表现分，若当前 rating 低于本场表现分则 rating 增加一，高于则减少一，等于则不变。Kevin 可以屏蔽一段区间的比赛（区间长度至少为 $1$），问最优情况下 Kevin 的最终 rating。

#### 分析

我们可以通过模拟得到只考虑前 $i$ 场的 rating。然后考虑用一段后缀拼上一段前缀。

然后发现后缀不是很好递推处理，于是我们可以二分一个答案即最终位置的 rating，然后往前递推。由于是倒着推，遇到更小的表现分 rating 加一，遇到更大的表现分 rating 减一。相等的情况我们可以考虑一个贪心：我们希望前缀某个位置出现与当前 rating 相等直接屏蔽中间的区间，而由于 rating 更低的位置一定出现得更早，那我们一定会选择将 rating 减一。

rating 接近 $0$ 的时候有一些细节要特判。

```cpp
void solve()
{
	int n; cin>>n;
	vector<int> a(n+5),p(n+5,0),pos(n*3+5,n*5+5);
	int ans=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(p[i-1]>a[i]) p[i]=p[i-1]-1;
		else if(p[i-1]==a[i]) p[i]=p[i-1];
		else if(p[i-1]<a[i]) p[i]=p[i-1]+1;
		pos[p[i]]=min(pos[p[i]],i);
		if(i!=n) ans=max(ans,p[i]);
	}
	auto check=[&](int x)
	{
		if(pos[x]<=n-1) return 1;
		for(int i=n;i>=1;i--)
		{
			if(x>a[i]) x=x+1;
			else if(x<a[i]) x=x-1;
			else if(x==a[i])
			{
				if(x==1) x=1;
				else x=x-1;
			}
			if(x<0) return 0;
			if(pos[x]<=i-2) return 1;
		}
		return 0;
	};
	int l=0,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) ans=max(ans,mid), l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<"\n";
}
```

---

