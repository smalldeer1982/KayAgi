# Minimal Coverage

## 题目描述

**本题有多组测试数据。**

给你 $n$ 条线段，告诉你每条线段的长度。
    
你需要把它们**依次**放在一条无限长的数轴上。
    
放置需满足当前线段的起点是前一个线段的终点。特别地，第一个线段的起点为 $0$。

也就是说，若前一个线段的终点是 $x$,当前长度为 $d$, 那么这个线段必须放在 $[x−d,x]$ 终点变为 $x−d$，或 $[x,x+d]$ 终点变为 $x+d$。

请问放置完后所有线段的最小覆盖长度是多少？

## 说明/提示

$1\le t\le 1000$，$1\le\sum n\le10^4$，$1\le a_i\le 1000$。

## 样例 #1

### 输入

```
6
2
1 3
3
1 2 3
4
6 2 3 9
4
6 8 4 5
7
1 2 4 6 7 7 3
8
8 6 5 1 2 2 3 6```

### 输出

```
3
3
9
9
7
8```

# 题解

## 作者：HDWR (赞：13)

分享一个非常智慧的做法，从 tutorial 评论区看到的

发现答案长度越大，留给这堆线段施展的空间就越大，也就是答案更容易合法。于是考虑二分答案 $t$。

如何 `check`？

当时想了半天如何贪心，总是想不出正确的策略，遂放弃。

但是贪心 `check` 的本质还是逐条插入线段，验证每条线段的结尾端点能否落到这个长度为 $t$ 的区间里。

**于是我们考虑直接维护这个东西！！**

设 $01$ 数组 $b_{j, i}$ 表示考虑前 $j$ 条线段，第 $i$ 个位置能（$1$）否（$0$）成为第 $j$ 条线段结尾位置；换句话说，第 $i$ 个位置能否成为第 $j + 1$ 条线段开始位置。

> Tips: `b[j][i]` 表示第 i 位能否成为第 j + 1 条线段的起始点。注意这里实际上并没有考虑第 j + 1 条线段的能否“成功地”放在这里（因为定义 1 只“考虑了前 j 条线段”能否“成功”放下），只是考虑了第 i 位“有没有可能”成为它的起始点，所以第 1 条线段是“可能”可以放在任何起始点的。接下来转移的时候，才开始考虑这条将要放下的线段的长度，也就是能否“成功地”放在这里。

考虑新加入一条线段长度为 $d$，对所有（答案不会越界的）位置 $i$，它能成为结尾当且仅当位置 $i \pm d$ 至少有一个能成为开头，也就是：

$$b_{j, i} = b_{j - 1, i - d} \text{ or } b_{j - 1, i + d}$$

当前的答案满足条件意味着 $b_{n}$ 至少有一个位置为 $1$。

快速维护这个 $01$ 数组可以通过 `std::bitset` 实现。可以直接滚动数组把第一维优化掉。

## 代码实现

注释写的英文是因为我同时在用 Dev-C++ 和 VSCode，为了防止编码混乱才写成英文的。

关于那个神奇的式子可以参考下图（线是 1，实心块是 0）：

[![47LOb9.png](https://z3.ax1x.com/2021/10/01/47LOb9.png)](https://imgtu.com/i/47LOb9)

```cpp
const int MAXN = 10000 + 10;

int n, aa[MAXN];

std::bitset<MAXN> s, t; 
// (after j loops) s[i] means (after considering the first j segs) 
// whether the jth seg's end can be placed on pos i
// in other words, (before the (j + 1)th loop) s[i] means (after considering the first j segs)
// whether it's possible to place the (j + 1)th seg's start on pos i

// jth seg's end can be placed on pos i if and only if its start can be placed on pos (i - len) or (i + len)
// that is, forall i, new_s[i] = s[i - len] | s[i + len]


bool check(int mid) {
    s = 0; t = 0;
    for (int i = 0; i <= std::min(mid, MAXN - 1); ++i) t.set(i);
    s = t;
    for (int i = 1; i <= n; ++i) {
        s = ((s >> aa[i]) | (s << aa[i])) & t;
        // this magic thing equals to:
        // for (int j = 1; j <= n; ++j) {
        //     new_s[j] = s[j - aa[i]] | s[j + aa[i]];
        // }
    } return s.count();
}

int main() {
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T --> 0) {
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> aa[i];
        int l = 1, r = 2e7, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid - 1, ans = mid;
            else l = mid + 1;
        } cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：似嫩 (赞：12)

## 题意简析
有多组数据
- 给你 $n$ 条线段，告诉你每条线段的**长度**。
- 你需要把它们放在一条**无限长的数轴**上。
- 放置需满足**当前线段的起点**是**前一个线段的终点**，特别的第一个线段的起点为 $0$。

也就是说，若前一个线段的终点是 $x$,当前长度为 $d$, 那么这个线段必须放在 $[x-d,x]$ 终点变为 $x-d$，或 $[x, x + d]$ 终点变为 $x + d$。
- 请问放置完后所有线段的最小覆盖长度是多少？
- $1\le t\le 10^4, 1\le n\le 10^4$

## 分析
~~好耶，居然是DP题~~

我们把覆盖看成跳跃，一条条跳进行决策显然不现实~~贪心写挂了~~。通过观察可以证明，最后的答案肯定不超过 $2\times l_{\max}$。因为所有的线段都可以在里面左右跳，而不出去（也可参见下面的解释）。

由于数轴是无限长的，从哪里开始没有影响。我们可以规定所有线段在 $[-l_{\max},l_{\max}]$ 之间，如果当前上一个结束位置大于 $0$，就向左跳，否则，就向右跳，这样就不会跳出边界。

解决了如何操作的问题，接下来首先是dp的状态：$dp_{i,l}$ 用来表示当前 $i$ 的结束点到最左边的距离是 $l$ 时，到最右边的距离最小值。于是当前覆盖的长度即为 $l+dp_{i,l}$。最后的答案即为 $\min(l+dp_{n,l})(0\le l\le 2\times l_{\max})$

然后是转移：
- 预处理：$dp_{i,j}=inf,dp_{0,0}=0$ 如果等于 $inf$，说明无法跳到，直接跳出。
- 对于每个线段考虑向左放还是向右放：
	- 其中 $0\le l\le 2\times l_{\max},0\le i< n$
	- 对于 $a_{i+1}$, 如果考虑向左放，那么到左边界的距离变为 $\max(l-a_{i+1},0)$（如果没有超过范围，就减一下，否则它就是现在的最左边），到右边界的距离为 $dp_{i,l}+a_{i+1}$（因为向左跳了那么多）。所以有
    $$dp_{i+1,\max(0,l-a_{i+1})} = min(dp_{i+1,\max(0,l-a_{i+1})},dp_{i,l}+a_{i+1})$$
   - 如果考虑向右放，那么到右边界的距离变为 $\max(dp_{i,l}-a_{i+1},0)$，到左边界的距离为 $l+a_{i+1}$，所以有
   $$dp_{i+1,l+a_{i+1}}=min(dp_{i+1,l+a_{i+1}},\max(dp_{i,l}-a_{i+1},0))$$
然后我们就愉快地解决了， 复杂度 $O(n\times l_{\max})$

## 总结
想对状态还是。。嗯不难想的
~~总之也是道神仙题~~

```cpp
const int INF = 1000000000;

int main() {
    int T = read();
    while (T --) {
        int n = read();
        int maxx = 0;
        for (int i = 0; i < n; i++) {
            a[i] = read();
            maxx = max(maxx, a[i]);
        }
        vector<vector<int>> dp(n + 1, vector<int>(2 * maxx + 1, INF));
        dp[0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int left = 0; left <= 2 * maxx; left++) {
                if (dp[i][left] == INF)
                    continue;
                dp[i + 1][max(left - a[i], 0)] = min(dp[i + 1][max(left - a[i], 0)], dp[i][left] + a[i]);
                if (left + a[i] < dp[i + 1].size()) {
                    dp[i + 1][left + a[i]] = min(dp[i + 1][left + a[i]], max(dp[i][left] - a[i], 0));
                }
            }
        }
        int ans = 2 * maxx + 1;
        for (int left = 0; left <= 2 * maxx; left++)
            ans = min(ans, left + dp[n][left]);
        write(ans), puts("");
    }
}
```


---

## 作者：hgzxwzf (赞：8)

### [CF1579G](https://codeforces.com/contest/1579/problem/G)

首先肯定可以二分长度 $len$。

设 $dp_{i,j}$ 表示考虑了前 $i$ 条线段，终点可不可能在 $j$。

因为坐标可能为负数，所以不方便处理，所以 $j$ 不是坐标位置。

实际上我们并不需要在意 $j$ 表示什么，我们只需要控制 $j\in[0,len]$，这样就保证了从起点到任意一个转移到的终点的距离都不超过 $len$。

初始对于 $j\in[0,len]$，$dp_{0,j}=1$。

转移：对于 $j$ 满足 $dp_{i-1,j}=1$，如果 $j+a_i\le len$，$dp_{i,j+a_i}=1$；如果 $j-a_i\ge 0$，$dp_{i,j-a_i}=1$。

如果 $\exists\space i\le len$ 满足 $dp_{n,i}=1$，则 $len$ 可以取得到。

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define LL long long

using namespace std;
const int N=1e4+10;

int a[N],n;
bool dp[2][N];

inline bool pd(int len)
{
	int cur=0;
	rep(i,0,len) dp[0][i]=1;
	rep(i,1,n)
	{
		cur^=1;
		rep(j,0,len) dp[cur][j]=0;
		rep(j,0,len)
			if(dp[cur^1][j])
			{
				if(j+a[i]<=len) dp[cur][j+a[i]]=1;
				if(j-a[i]>=0) dp[cur][j-a[i]]=1;
			}
	}
	rep(i,0,len) if(dp[cur][i]) return 1;
	return 0;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		rep(i,1,n) scanf("%d",&a[i]);
		int l=0,r=2000,ans;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(pd(mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：Otomachi_Una_ (赞：4)

喵喵的 dp 题。

## 题目简述

- 给你 $n$ 条线段，每个线段有长度 $a_i$。
- 要求把这 $n$ 条线段连在一条数轴上。
- 这些线段的最短覆盖长度。
- $\sum n\leq 10^4,a_i\leq10^3$。

## 解题思路

首先有个显然错误的贪心：

> 对于每个线段，如果固定端点在左边那就往右边放；反之往左边放。

这个贪心是显然错误的。从数据的范围就可以看出。但是这个贪心还是给我们一点提示，那就是：答案不会超过 $a_{\max}$。

我们猜这个题的时间复杂度是 $O(na_{\max})$。然后我们想想怎么做？

考虑 $\text{dp}$。这个 $\text{dp}$ 既要描述当前的长度又要描述当前顶点的位置。那么就有了这样的描述：$f_{i,j}$ 表示第 $i$ 个线段到达当前的极右端点的值为 $j$ 时到极左端点的**最小值**为 $f_{i,j}$。那么最终的答案是 $\min(f_{n,i}+i)$。

状态转移方程是很好想的，但是比较复杂：

```cpp
f[i+1][max(0,j-a[i+1])]=min(f[i+1][max(0,j-a[i+1])],f[i][j]+a[i+1]); 
f[i+1][j+a[i+1]]=min(f[i+1][j+a[i+1]],max(f[i][j]-a[i+1],0));
```

## 参考代码

```cpp
#include<iostream>
using namespace std;
const int MAXN=1e4+5;
const int MR=1e3+5;
int f[MAXN][2*MR];int n;
int a[MAXN];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=0;i<=n;i++)
		for(int j=0;j<2*MR;j++)
			f[i][j]=1e9;
	f[0][0]=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<2*MR;j++)
			if(f[i][j]<114514){//如果合法 
				f[i+1][max(0,j-a[i+1])]=min(f[i+1][max(0,j-a[i+1])],f[i][j]+a[i+1]); 
				if(j+a[i+1]<2*MR) f[i+1][j+a[i+1]]=min(f[i+1][j+a[i+1]],max(f[i][j]-a[i+1],0));
			}
	int ans=114514;
	for(int i=0;i<2*MR;i++)
		ans=min(ans,f[n][i]+i);
	cout<<ans<<endl;
}
int main(){
	int _;cin>>_;
	while(_--) solve();
}
```

---

## 作者：0_lan_0 (赞：3)

一道十分巧妙的 dp 题
# 题目大意

有 $n$ 条线段，长度为 $d_i$，其实也可以看成是跳格子，每次可以向左或向右跳 $d_i$ 格，问跳到的极左格子与极右格子的距离的最小值。

# 思路

第一眼以为是贪心：

如果固定端点在左边那就往右边放，否则往左边放。

in
```
4
6 2 3 9
```
out
```
9
```

此时用这个贪心思路明显会错，但我们会在贪心中发现答案 $ans$ 一定满足：
$$
d_{max} \le ans \le 2 \times d_{max}
$$
此时我们考虑使用 dp，dp 的状态有点难想出来，$dp_{i,j}$ 表示第 $i$ 次放完后的结束点离极左端点的距离为 $j$，离极右端点的距离为 $dp_{i,j}$，所以此时覆盖的端点数为 $j+dp_{i,j}$，那么最终的答案就是 $\min(dp_{n,j}+j)$。

接下来看如何转移状态，把当前放完结束的点设为 $s$，极左端点设为 $l$，极右端点设为 $r$，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/olziswrd.png)

每条线段可以在上条线段的终点选择向左或向右放，我们把当前线段长度看为 $a$。

向左放：所以当前的位置为 $s-a$，因为距离没有负数，所以当 $a \ge j$ 时，$j = 0$，简单来说就是 $j=\min(j-a,0)$ 。因为覆盖距离尽可能要小，所以当 $j$ 一定时，要求最小的 $dp_{i,j}$，所以 $dp_{i+1,j} =\min(dp_{i+1,j},dp_{i,k}+a)$。

所以向左放的状态转移为
```cpp
dp[i+1][max(j-a[i+1],0ll)]=min(dp[i+1][max(j-a[i+1],0ll)],dp[i][j]+a[i+1]);
```

理解完向左放后那么向右放就不展开说了，代码：
```cpp
dp[i+1][j+a[i+1]]=min(dp[i+1][j+a[i+1]],max(dp[i][j]-a[i+1],0ll));
```
dp 部分就结束了，最后贴上代码。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e4+10,M=1e3+10,inf=1e10;
int t,n,a[N],Max,dp[N][M<<1],ans; 
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		Max=0,ans=inf;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			Max=max(Max,a[i]);
		}
		for(int i=0;i<=n;i++){
			for(int j=0;j<=Max*2;j++)
				dp[i][j]=inf;
		}
		dp[0][0]=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<Max*2;j++){
				if(dp[i][j]==inf) continue;
				dp[i+1][max(j-a[i+1],0ll)]=min(dp[i+1][max(j-a[i+1],0ll)],dp[i][j]+a[i+1]); 
				if(j+a[i+1]<Max*2)
					dp[i+1][j+a[i+1]]=min(dp[i+1][j+a[i+1]],max(dp[i][j]-a[i+1],0ll));
			}
		}
		for(int i=0;i<Max*2;i++)
			ans=min(ans,i+dp[n][i]);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：ltdj (赞：3)

~~给一个自认为妙好写的dp做法~~

显然我们可以考虑dp，容易想到最长距离可能达到1e7, 这是无法接受的。

先给一个结论吧，我们假设线段的最长长度为M，那么最长覆盖不超过$2M$（向左M，向右M）。

![image](https://cdn.luogu.com.cn/upload/image_hosting/qnqypuuc.png)。

可以按照如下贪心策略：如果单前结束位置离L的距离比R要远，那么下一条线段向左，反之向右。证明：如果要超过R，那么起点至少要在原点右边，此时一定向左，反之亦然。

此时容易想到的一个状态是设 $f_{i,j,k}$ 前i条线段表示以j为左端点(向左覆盖的最远点)，k为结束位置的最短覆盖距离， 显然贪心来说这个距离越短越优。 

此时对于 $f_i$ 的每个状态，结束位置确定，考虑加入第i+1条线段，可能的结束位置和左端点只有两个， 所以转移是O(1)的。

我们发现这种方法的左右端点位置可能为负数，不好处理，而且复杂度过大，这启发我们优化状态设计。

仔细思考，我们记录左端点和结束位置，又知道覆盖长度来求出右端点，这些这的有用吗？

我们其实只是想知道结束位置与左右端点的距离即可，他们的位置具体在哪里并不重要，您把他平移一下还是一样的。所以我们考虑设 $f_{i, j}$，前i线段，结束位置离左端点的距离为j时的最短覆盖，知道最短覆盖即可算出右端点距离。

转移很好写， 具体参考代码。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
 
int read(){
	int num=0, flag=1; char c=getchar();
	while(!isdigit(c) && c!='-') c=getchar();
	if(c=='-') flag=-1, c=getchar();
	while(isdigit(c)) num=num*10+c-'0', c=getchar();
	return num; 
}
 
const int N = 1050;
const int inf = 0x3f3f3f3f;
int T, n;
int a[N*10];
int f[N*10][N*4];
 
void clear(int x){
	for(int i=0; i<N*2+10; i++) f[x][i] = inf;
}
 
int main(){
	T = read();
	while(T--){
		n = read();
		for(int i=1; i<=n; i++) a[i] = read();
		
		clear(1); f[1][a[1]] = a[1];
		for(int i=2; i<=n; i++){ 
			clear(i);
			
			for(int j=0; j<=N*2; j++){
				f[i][j+a[i]] = min(f[i][j+a[i]], j+max(f[i-1][j]-j, a[i]));
				f[i][max(j-a[i], 0)] = min(f[i][max(j-a[i], 0)], f[i-1][j]-j+max(j, a[i]));
			}
		}
		int ans = inf;
		for(int i=0; i<=N*2; i++) ans = min(f[n][i], ans);
		cout << ans << endl;
 	}
	return 0;
}
```

---

## 作者：SilverLi (赞：2)

> [Minimal Coverage の 传送门](https://www.luogu.com.cn/problem/CF1579G)
>
> [按一按](https://www.cnblogs.com/Silver-Wolf/p/18690075/CF1579G)

怎么这个题想不到啊，~~所以我选择了看题解~~。

~~不容易~~发现，如果覆盖长度为 $x$ 可以，那长度更多的一定可以（这里**不盖满**整个长度为 $x$ 的段也可以）。

二分试一试，令当前二分的覆盖长度为 $len$。

DP 一下，$f_{i, j}$ 表示放完 $1 \sim i$ 的线段，结尾能否位置 $j$。

$f_{i, j}$ 的转移如下：

1. $f_{i-1, j-a_i} \left ( j-a_i \ge 0 \right )$。

2. $f_{i-1, j+a_i} \left ( j+a_i \le len \right )$。

时间复杂度：$O(\sum n \max a \log_2 n)$。

朴素实现：

```cpp
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define N 10005
#define mid (l + r >> 1)
int n, a[N];
bool F[N], G[N];
bool *f = F, *g = G;
void swap()
{
    bool *t = f;
    f = g, g = t;
}
bool check(int lim)
{
    memset(f, 1, sizeof F);
    for (int i = 1; i <= n; ++i)
    {
        swap();
        memset(f, 0, sizeof F);
        for (int j = 0; j <= lim; ++j)
        {
            if (j - a[i] >= 0)
                f[j] |= g[j - a[i]];
            if (j + a[i] <= lim)
                f[j] |= g[j + a[i]];
        }
    }
    for (int i = 0; i <= lim; ++i)
        if (f[i])
            return 1;
    return 0;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        int l = 1, r = 2000, it = -1;
        while (l <= r)
            check(mid)
                ? (it = mid, r = mid - 1)
                : (l = mid + 1);
        printf("%d\n", it);
    }
    return 0;
}
```

这个复杂度看起来有点不稳，可以试试 `std::bitset`（[详见](https://oi-wiki.org/lang/csl/bitset/)）。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid (l + r >> 1)
using namespace std;
inline int read()
{
    int f = 0, ans = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();
    return f ? -ans : ans;
}
void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
const int N = 1e4 + 5, M = 2e3 + 5;
int n, a[N];
bitset<M> f, base;
inline bool check(int lim)
{
    base.reset();
    for (int i = 0; i <= lim; ++i)
        base[i] = 1;
    f = base;
    for (int i = 1; i <= n; ++i)
        f = f >> a[i] | f << a[i] & base;
    return f.any();
}
signed main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T = read();
    while (T--)
    {
        n = read();
        for (int i = 1; i <= n; ++i)
            a[i] = read();
        int l = 1, r = 2000, it = -1;
        while (l <= r)
            check(mid)
                ? (it = mid, r = mid - 1)
                : (l = mid + 1);
        write(it), putchar('\n');
    }
    return 0;
}
```

---

## 作者：StayAlone (赞：1)

题意可以转化成，初始有一个点位于原点。给定一个序列 $a$，顺次将 $x$ 变为 $x+a_i$ 或 $x-a_i$，使得途径点中，最远点对的距离最近。

容易发现答案最多为 $2V$，其中 $V$ 为值域。证明很简单，考虑如果 $x+a_i>V$，那么 $x>0$，那么 $x-a_i > -V$。反之亦然。

考虑二分答案 $t$。第一想法是，对于包含原点的 $t$ 个区间依次检查能否满足条件。但是区间动来动去很烦，可以转化成钦定区间为 $[0, t]$，起点在 $[0, t]$ 中选择，判断是否有一种方法能使点不曾离开区间。

考虑用 bitset 维护第 $i$ 个位置上是否可能有点。初始均可作为起点，所以全是 $1$。操作 $a_k$ 时，若 $i-a_k$ 与 $i+a_k$ 中任意一个是 $1$，那么 $i$ 就可以为 $1$。其本质也可理解为 dp。

最终的 bitset 只要有任何位置为 $1$，就证明存在一个起点，使其始终不离开区间 $[0, t]$。

时间复杂度 $\mathcal O(\frac{nV\log V}{w})$。

[AC record](https://www.luogu.com.cn/record/156813242)
```cpp
int n, a[MAXN]; bitset <2010> f, org;

il bool check(int x) {
	f.reset(); org.reset();
	rep1(i, 0, x) org[i] = f[i] = 1;
	rep1(i, 1, n) f = ((f << a[i]) | (f >> a[i])) & org;
	return f.count();
}

int main() {
	for (int T = read(); T--; ) {
		read(n); rer(i, 1, n, a);
		int l = 1, r = 2e3;
		while (l ^ r) {
			int mid = l + r >> 1;
			if (check(mid)) r = mid;
			else l = mid + 1;
		} printf("%d\n", l);
	}
	rout;
}
```

---

## 作者：900102bj (赞：1)

### [CF1579G Minimal Coverage](https://www.luogu.com.cn/problem/CF1579G "CF1579G Minimal Coverage")
设最长线段长度为 $l_{max}$。可以证明，最后的答案一定在 $l_{max}$ 和 $2\times l_{max}$ 之间。

我们发现这道题并没有一个保证正确性的一个贪心策略，对于每一条线段它向左或向右放置都是有可能的，当然前提是答案不能超过 $2\times l_{max}$，题中线段的长度并没有很大，考虑 dp。

dp 状态：$dp_{i,l}$ 表示当前第 $i$ 条线段的终点到最左边的距离为 $l$ 时，到最右边的距离。最后的答案即为 $\min(l+dp_{n,l})$。
具体地，对于第 $i$ 条线段，长度为 $a_{i}$，如果向左放，转移就是

$$dp_{i,\max(j-a_{i},0)}=\min(dp_{i,\max(j-a_{i},0)},dp_{i-1,j}+a_{i})$$

向右放时注意判断到左边界的距离不能超过 $2\times l_{max}$

$$dp_{i,j+a_{i}}=\min(dp_{i,j+a_{i}},\max(dp_{i-1,j}-a_{i},0))$$

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
const int maxn=1e4+10;
const int maxm=1e3+10;
const int inf=0x3f3f3f3f;
int a[maxn];
int dp[maxn][maxm*2];
int main(){
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        int mx=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            mx=max(mx,a[i]);
        }
        for(int i=0;i<=n;i++){
            for(int j=0;j<=2*mx;j++){
                dp[i][j]=inf;
            }
        }
        dp[0][0]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=2*mx;j++){
                if(dp[i-1][j]==inf){
                    continue;
                }
                dp[i][max(j-a[i],0)]=min(dp[i][max(j-a[i],0)],dp[i-1][j]+a[i]);
                if(j+a[i]<=2*mx){
                    dp[i][j+a[i]]=min(dp[i][j+a[i]],max(dp[i-1][j]-a[i],0));
                }
            }
        }
        int ans=inf;
        for(int i=0;i<=2*mx;i++){
            ans=min(ans,dp[n][i]+i);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：BreakPlus (赞：1)

好久没静下心来做题，手感越来越差。今天还是静下心来好好想了这道题，觉得作为 *2200 难度略逊，但是这个思维还是有点深度的。

-----

看到这题，我们不难想到 dp，但是不知道维护啥。维护当前端点坐标？这里我们确定一下答案的范围，以保证 dp 的复杂度。

答案的范围：$[\max\{a\} , 2\max\{a\}]$

下限易证，关于上限，我们构造一个长度为 $2\max\{a\}$ 的线段。发现无论当前的线段翻折到了这个线段上的哪个点，左右两边必然有一段长度 $\le \max\{a\}$。这样归纳一下，每一步都可行。证毕。

接下来，不难发现直接 dp 也不好维护这个覆盖长度。但是如果我们**确定了覆盖长度**，岂不是可以直接维护端点坐标进行 dp？这是一个很好地思路。

**考虑二分**，由于刚才的证明，仅仅二分的复杂度是 $\log_2 \max\{a\}$ 的。关于 $\text{check}(\texttt{mid})$，设计一个 $f(i,j)=0/1$ 表示第 $i$ 条线段翻折后是否能落到点 $j$ 上。初始我们限制的端点范围是 $0 \sim \texttt{mid}$ 的，起点在哪里不限。那么这个 dp 的复杂度是 $\mathcal O (n \max\{a\}) $ 的。事实上由于 CF 机子较快，可以通过本题。

总复杂度：设 $t = \max\{a\}$，则为 $\mathcal O (n t \log t ) $ （有点勉强）。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
typedef short ll;

inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
/*--------------head------------------*/

ll n,d[10005];
bool f[2][2001];
inline bool check(ll mid){
	for(ll i=0;i<=mid;i++) f[0][i]=1;
	for(ll i=0;i<n;i++){
		ll lft=i&1; ll rht=lft^1;
		memset(f[rht], 0, sizeof(f[rht]));
		for(ll j=0;j<=mid;j++){
			if(f[lft][j]){
				if(j>=d[i+1]) f[rht][j-d[i+1]]=1;
				if(j+d[i+1]<=mid) f[rht][j+d[i+1]]=1;// cout<<"from "<<j<<" to "<<j+d[i+1]<<endl;
			}
		}
	}
	for(ll j=0;j<=mid;j++)
		if(f[n&1][j]) return 1;
	return 0;
}
void solve(){
	n=read();
	ll mx = 0;
	for(ll i=1;i<=n;i++) d[i]=read(), mx = (d[i]>mx?d[i]:mx);
	ll lft=mx, rht=2*mx, ans=0;
	while(lft<=rht){
		ll mid=lft+rht>>1;
		if(check(mid)) ans=mid, rht=mid-1;
		else lft=mid+1;
	}
	cout<<ans<<endl;
}
int main(){
    ll T=read();
    while(T--) solve();
    return 0;
}

```

---

## 作者：lfxxx (赞：0)

好题。

考虑设计一个最暴力的 dp，$dp_{i,l,r,p}$ 表示考虑到第 $i$ 条线段，终点是 $p$，最左边和最右边分别是 $l,r$。由于可以构造出不超过 $O(V)$ 的答案，所以 dp 数组后面三维一定不超过 $O(V)$。

考虑优化，你发现最后计算答案的方式是 $r-l$，和 $p$ 关系不大，于是考虑优化答案计算方式，不妨记 $L=p-l,R=r-p$，最后可以用 $L+R$ 计算答案，于是状态变为 $dp_{i,L,R}$，又注意到这是一个具有单调性的 0/1 状态，于是记录 $dp_{i,L}$ 表示 $R$ 的最小值即可做到 $O(n \times V)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxv = 2114;
const int maxn = 1e4+114;
int f[maxn][maxv];
int a[maxn],n;
void work(){
    cin>>n;
    for(int i=0;i<=n;i++){
        for(int j=0;j<maxv;j++) f[i][j]=maxv;
    }
    for(int i=1;i<=n;i++) cin>>a[i];
    f[0][0]=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<maxv;j++){
            f[i+1][max(0,j-a[i+1])]=min(f[i+1][max(0,j-a[i+1])],f[i][j]+a[i+1]);
            if(j+a[i+1]<maxv) f[i+1][j+a[i+1]]=min(f[i+1][j+a[i+1]],max(0,f[i][j]-a[i+1]));
        }
    }
    int ans=maxv;
    for(int j=0;j<maxv;j++) ans=min(ans,j+f[n][j]);
    cout<<ans<<'\n';
} 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

## 作者：allqpsi (赞：0)

首先，发现答案具有明显的单调性，即：若一个数 $a$ 可行，比 $a$ 大的数也可行。由此想到二分答案。

一个答案的性质便是一定不超过数组中最大的数乘二。可证明在一个区间长度为数组中最大的数乘二内，若此时位置小于中间便向右放，否则向左放。因此我们将二分的左边界取数组中最大的数乘二。

然后就是如何判断是否可行，可动态规划解决。我们设数组 $f_{i,j}$ 指到第 $i$ 条线段，结尾为 $j$ 是否可行。转移为 $f_{i,j}| =f_{i-1,j-a_{i}}$ 和 $f_{i,j}| =f_{i-1,j+a_{i}}$ 便做完了。

**注意，此处要用滚动数组，否则会炸时限。**

#### 代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define set(ai) memset(ai,0,sizeof(ai));
#define fset(ai) memset(ai,127,sizeof(ai));
#define hset(ai) memset(ai,63,sizeof(ai));
#define rep(i,s,t) for(int i=s;i<=t;i++)
#define frep(i,s,t) for(int i=s;i>=t;i--)
#define rep1(i,s,t) for(int i=s;i<t;i++)
#define frep1(i,s,t) for(int i=s;i>t;i--)
#define srt(ai,n) sort(ai+1,ai+n+1)
#define csrt(ai,n,cmp) sort(ai+1,ai+n+1,cmp)
#define pb push_back
#define ppb pop_back
#define cr i%2
#define ls !(i%2)
using namespace std;
const int N=1e4+5,M=2e3+5;
int t,n,ans,l=0,r,mx,ai[N],mid;
bool f[2][M],sm;
bool chk(int x){
	set(f);sm=0;
	rep(i,0,x)f[0][i]=1;
	rep(i,1,n){
		bool isit=0;
		rep(j,0,x-ai[i])f[cr][j]|=f[ls][j+ai[i]];
		rep(j,ai[i],x)f[cr][j]|=f[ls][j-ai[i]];
		rep(j,0,x)f[ls][j]=0;
	}
	rep(i,0,x)sm|=f[n%2][i],f[n%2][i]=0;
	return sm;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n,mx=-M,l=0;
		rep(i,1,n)cin>>ai[i],mx=max(mx,ai[i]);
		ans=r=2*mx;
		while(l<=r)mid=(l+r)>>1,(chk(mid))?(ans=mid,r=mid-1):(l=mid+1);
		cout<<ans<<endl;
	}
}
```

---

## 作者：ZBHRuaRua (赞：0)

观察发现，对于第 $i$ 步操作，比较"你走到了 $3$ 并且此时已经触碰的区间 $[0,5]$ "和"你走到了 $1$ 并且此时已经触碰的区间为 $[-2,3]$ "两者，你会发现其实对后续影响是相同的，也就是两者其实是等价的。

这提示了我们，我们关注的其实只有

1.走到哪( $pos$ )

2.左右边界

但显然直接维护这些信息是不现实的，复杂度炸飞了。

于是可以想到使用差值 DP ，设 $R$ 为右边界到 $pos$ 的距离， $L$ 为左边界到pos的距离，则我们可以维护 $R-L$ 这一个信息就能得到左右边界。

但此时我们还是需要维护 $pos$ 和 $R-L$ 这两个信息，还是会炸。

但实际上通过我们上面的第一段话，我们能够知道其实在同一步结束后，我们并不关心到底 $pos$ 在哪，只需要知道在 $R-L$ 的限制下的最短区间长度即可。

这部分的转移还算蛮简单的。

由于左右是差不多的，我们这里就列出向右放线段的转移。

 $f[i]$ 表示 $R-L$ 为 $i$ 时的最短区间长度

 $g$ 数组是每一步的临时数组

当 $R>=a[i]$ 时，显然区间长度不会变

因此 $g[j-2*a[i]]=min(g[j-2*a[i]],f[j])$ 

当 $R<a[i]$ 时，区间长度变化

 $g[j-2*R-(a[i]-R)]=min(g[j-2*R-(a[i]-R)],f[j]+(a[i]-R))$

怎么知道 $L$ 和 $R$ 的值？

 $f[i]$ 不就是 $L+R$ 嘛

所以 $L*2=f[i]-i$

$R*2=f[i]+i$

但是 $f$ 数组开多大呢（换句话说，复杂度多少）

容易发现显然不可能冲出 $max_{a_i}$
因此开 $2*2000$ 即可（因为有负数域）

具体看代码：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
const int len=2000;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+(c-'0');
		c=getchar();
	}
	return x*f;
}
int t;
int a[10050];
int f[4050],g[4050];
int main()
{
	t=read();
	while(t--)
	{
		int n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		memset(f,63,sizeof(f));
		f[len+a[1]]=f[len-a[1]]=a[1];
		for(int i=2;i<=n;i++)
		{
			memset(g,63,sizeof(g));
			for(int j=0;j<=2*len;j++)
			{
				if(f[j]<=1e7)
				{
					int k=j-len;
					int L=(f[j]-k)/2,R=(f[j]+k)/2;
					if(R>=a[i]&&(j-2*a[i])>=0) g[j-2*a[i]]=min(g[j-2*a[i]],f[j]);
					if(L>=a[i]&&(j+2CF1579G Minimal Coverage*a[i]<=2*len)) g[j+2*a[i]]=min(g[j+2*a[i]],f[j]);
					if(R<a[i]&&(j-2*R-(a[i]-R))>=0) g[j-2*R-(a[i]-R)]=min(g[j-2*R-(a[i]-R)],f[j]+(a[i]-R));
					if(L<a[i]&&(j+2*L+(a[i]-L)<=2*len)) g[j+2*L+(a[i]-L)]=min(g[j+2*L+(a[i]-L)],f[j]+(a[i]-L));
				}
			}
			for(int j=0;j<=2*len;j++) f[j]=g[j];
		}
		int minn=1e9;
		for(int i=0;i<=2*len;i++) minn=min(minn,f[i]);
		cout<<minn<<endl; 
	}
}
```

---

## 作者：Leaper_lyc (赞：0)

## 题目描述

给定 $n$ 条线段，第 $i$ 条线段的长度 $a_i$。

要把它们放在一条**无限长的数轴**上。放置需满足**当前线段的起点**是**前一个线段的终点**，特别的第一个线段的起点为 $0$。

也就是说，若前一个线段的终点是 $x$，当前长度为 $d$，那么这个线段必须放在 $[x-d,x]$ 终点变为 $x-d$，或 $[x, x + d]$ 终点变为 $x + d$。

请问放置完后所有线段的最小覆盖长度是多少？

$1\le t\le 1000, 1\le n\le 10^4$。

## 分析

### 性质

考虑一种覆盖策略：若当前坐标大于等于 $0$ 就往左跳，若当前坐标小于 $0$ 就往右跳。

由于我们每次向左跳时，坐标都大于等于 $0$，所以跳到的点的坐标都大于等于 $-1000$。

同理，由于我们每次向右跳时，坐标都小于 $0$，所以跳到的点的坐标都小于 $1000$。

可以粗略的知道坐标的范围在 $[-1000,1000]$ 之间，也就是答案不超过 $2000$。

### 做法

做法一：根据这个性质我们可以二分答案，在 $2000$ 内二分一个长度 $len$ 为答案然后判断。

做法二：DP。

![](https://cdn.luogu.com.cn/upload/image_hosting/jmuw93h1.png)

显然需要考虑这些：当前考虑到第 $i$ 条线段、尾巴到左端距离 $L$ 以及左右端距离 $L'$。于是可以设 $f_{i,L}$ 表示最小的 $L'$ 使得状态 $(i,L,L')$ 可达。

转移显然。

---

