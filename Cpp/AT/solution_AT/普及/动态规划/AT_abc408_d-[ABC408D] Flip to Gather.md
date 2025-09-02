# [ABC408D] Flip to Gather

## 题目描述

给你一个长度为 $N$ 的、由 $0$ 和 $1$ 构成的字符串 $S$。

你可以执行以下操作若干次：
- 选择一个整数 $1\le i\le N$，$S_i\leftarrow 1-S_i$。

你的目标是让 $S$ 中的 $1$ 连续或 $S$ 中不存在 $1$。请找出需要的最小的操作次数。

多组数据。

## 说明/提示

**样例 1 解释**

对于第一组数据，我们选择 $i=1$ 进行一次操作即可。

第二、三组数据不需要执行任何操作。

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
3
5
10011
10
1111111111
7
0000000```

### 输出

```
1
0
0```

## 样例 #2

### 输入

```
5
2
01
10
1000010011
12
111100010011
3
111
8
00010101```

### 输出

```
0
2
3
0
2```

# 题解

## 作者：chenxi2009 (赞：13)

## 思路
我们考虑保留一段区间 $[l,r]$ 的所有 $1$，那么需要操作的次数就是 $[1,l)$ 和 $(r,n]$ 中的 $1$ 的个数加上 $[l,r]$ 中的 $0$ 的个数。

求个前缀和，令 $s_i$ 表示 $[1,i]$ 中的 $1$ 的个数，$[l,r]$ 的答案就是：
$$
s[l-1]+(s[n]-s[r])+((r-l+1)-(s[r]-s[l-1]))\\
=s[n]+(r-2s[r])+(2s[l-1]-(l-1))
$$
考虑枚举每一个 $r$，由于我们要让答案最小，$l-1=x$ 就取 $[0,r]$ 中使得 $2s[x]-x$ 最小的那个（$l-1=r$ 表示删掉所有 $1$），其实就是 $2s[x]-x$ 的前缀最小值。直接算即可，时间复杂度 $O(\sum N)$。

笑点解析：这是我前六道题里花时间最长的一道。
## 代码
```cpp
#include<bits/stdc++.h>
#define gc getchar
#ifndef DEBUG
#define debug
#endif
using namespace std;
template<typename T>void read(T &x){x = 0;int f = 1;char c = gc();while(!isdigit(c)){if(c == '-') f = -1;c = gc();}while(isdigit(c)) x = x * 10 + c - '0',c = gc();x *= f;}
const int N = 300000;
int T,n,p[N],r,l,ans,x[N];
char s[N];
int main(){
  read(T);
  while(T --){
    ans = 2e9;
    read(n);scanf("%s",s + 1);
    for(int i = 1;i <= n;i ++) p[i] = p[i - 1] + s[i] - '0';//前缀和
    for(int i = 0;i <= n;i ++) x[i] = 2 * p[i] - i;//取 l-1=x 时对答案造成的影响
    for(int i = 1;i <= n;i ++) x[i] = min(x[i],x[i - 1]);//取 x 的前缀最小值
    for(int i = 1;i <= n;i ++) ans = min(ans,p[n] + (i - 2 * p[i]) + x[i]);
    printf("%d\n",ans);
  }
  return 0;
}
```

---

## 作者：Clover_Lin (赞：6)

## 博客
请点击[这里](https://blog.csdn.net/ArmeriaLeap/article/details/148356352)阅读。
## 题目大意
给定一个长度为 $N$ 的字符串 $S$，只由 `0` 和 `1` 组成。现在，反转其中的一些位置，使字符串中要么没有 `1`，要么所有的 `1` 都在一个连续的子段内，求最少操作次数。
## 思路
这是一个决策的问题，我们考虑字符串 `10011`，有如下几种选择：
- 把最左侧的一段 `1` 变成 `0`。
- 把中间的 `0` 变成 `1`。
- 把最右侧的一段 `1` 变成 `0`。

这是本题动态规划的雏形，我们来仔细考虑一下如何去做。

**前置操作**：把第 $i$ 个连续的 `1` 的子段的**左端点**记为 $p_i$，将这个子段的长度记为 $l_i$。把这样的子段个数记为 $cnt$。

**状态定义**：令 $f_i$ 表示在完全不改变第 $i$ 个子段的情况下，最小答案是多少。

**状态转移**：显然左右都得考虑。左边：$f_i=\min\lbrace f_{i-1}+p_i-(p_{i-1}+l_{i-1}-1)-1,\sum_{j=1}^{i-1}l_j\rbrace$；右边：$f_i=\min\lbrace f_{i+1}+p_{i+1}-(p_i+l_i-1)-1,\sum_{j=i+1}^{cnt}l_i\rbrace$。左边与右边之和即为 $f_i$ 的最终值。

**答案**：所有 $f_i$ 的最小值。
## 代码
AC 记录：[Submission #66340268](https://atcoder.jp/contests/abc408/submissions/66340268)。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int t, n, cnt;
string s;
int p[200010];
int l[200010];
int f[200010];

int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n >> s;
		s = " " + s + " ";
		cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			if (s[i] == '1' && s[i - 1] != '1')
			{
				p[++cnt] = i;
				l[cnt] = 1;
				f[cnt] = 1e9;
			}
			else if (s[i] == '1')
				l[cnt]++;
		}
		if (cnt == 0 || cnt == 1)
		{
			cout << "0" << endl;
			continue;
		}
		f[1] = 0;
		int s = l[1];
		for (int i = 2; i <= cnt; i++)
		{
			f[i] = f[i - 1] + p[i] - (p[i - 1] + l[i - 1] - 1) - 1;
			f[i] = min(f[i], s);
			s += l[i];
		}
		int ans = f[cnt];
		s = l[cnt];
		for (int i = cnt - 1; i >= 1; i--)
		{
			int v = f[i + 1] + p[i + 1] - (p[i] + l[i] - 1) - 1;
			f[i] += min(v, s);
			ans = min(ans, f[i]);
			s += l[i];
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Alex866 (赞：5)

## 题意分析

题目给定一个 01 序列，每次可以将该序列的每一位翻转，让我们求该序列仅包含一段连续的 1 的最小操作次数。

## 算法选取

观察得知最后留下的一段不是越长越好，也不是越短越好，我们又注意到每个 1 离最后留下的一段越远，将他们连起来的代价就越高，这启示我们这可能是区间问题。\
又观察样例可知，当一段连续的 1 的个数大于和它和最长的一段 1 中间的 0 的个数时，显然填 0 一定比连上更好，我们注意到可能它有最大子段和的性质，我们考虑构造最大子段和：

- 连续的 $k$ 个 1 和连续的 $k$ 个 0 在一起时，将 0 变成 1 和将 1 变成 0 的代价一样，这说明我们构造 0 和 1 对应的数要是相反数。
- 连续的 $k$ 个 1 和连续的不足 $k$ 个 0 在一起时，将 0 变成 1 要比将 1 变成 0 的代价少，反之亦然，这说明我们构造的 0 对应的数是负数，1 是正数，这里可以构造 1 和 -1。

这启示我们可以打一个最大子段和来解决，注意这里 0 要变成 -1。

## code

```cpp
#include<bits/extc++.h>
using namespace std;
using namespace chrono;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
#define _FF(_Name,_Begin,_End) for(auto _Name=_Begin;_Name<_End;_Name++)
int t,n,sum,ans;
string s;
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>s;
		sum=ans=0;
		_FF(i,0,n){
			sum=max(0,sum+((s[i]^'0')<<1)-1);
			ans=max(ans,sum);
		}
		cout<<count(s.begin(),s.end(),'1')-ans<<'\n';
	}
	return 0;
}
```

---

观察。注意。启示。

---

## 作者：xy_mc (赞：4)

### 题目描述：

(可能是我翻译的事，很长时间没看懂 QWQ)。

给定一个长度为 $N$ 的字符串 $S$，每次操作可以翻转一个字符（$0$ 变 $1$ 或 $1$ 变 $0$）。目标是使字符串中的 $1$ 形成一个连续的区间（最多一个区间），求最小操作次数。


### 解题思路：

细想一下，我们要的最终状态中，$1$ 的连续区间为 $[l, r]$（可能为空）。操作次数 $=$ 区间内 $0$ 的个数 $+$ 区间外 $1$ 的个数。那么我们设区间长度为 $L$，区间内 $1$ 的个数为 $c$，则操作次数 $= \text{cnt} + L - 2c$，因为 $L-c$ 是区间内 $0$ 的个数，$cnt-c$ 是区间外 $1$ 的个数，其中 $\text{cnt}$ 是整个字符串中 $1$ 的总数。

这样的话就显而易见了，遍历每个可能的右端点 $r$，维护 $2p - r$ 的最小值，其中 $p$ 是前 $r$ 个字符中 $1$ 的个数。通过更新前缀和和最小值，可以在 $O(N)$ 时间内求解。

### 核心代码:

```cpp
#define rep(i,x,y) for(int i=x;i<=(y);++i)

void solve(){
	int l,cnt=0,ans,v=0,p=0;
	string s;
	cin>>l>>s;
	rep(i,0,l-1) cnt+=(s[i]=='1');
	ans=cnt;
	rep(i,0,l-1){
		v=min(v,2*p-i);
		ans=min(ans,cnt+(i+1)-2*(p+(s[i]=='1'))+v);
		p+=(s[i]=='1');
	}
	printf("%d\n",ans);
}
```

---

## 作者：Liyanxi1028 (赞：3)

### 思路

读完题，$\sum N \le 2 \times 10^5$，复杂度应该是线性，考虑 dp。

先对输入做一定处理：这个 $01$ 串肯定由连续的 $0$（下称 $0$ 串）和连续的 $1$（下称 $1$ 串）交替组成，（若有）最开头的 $0$ 串显然与答案无关，舍去。我们不妨设第 $i$ 段 $1$ 串长度为 $a_i$，第 $i$ 段 $0$ 串长度为 $b_i$，**$dp_i$ 为第 $i$ 段 $1$ 串及以前均被处理完毕且第 $i$ 段 $1$ 串未被置 $0$ 的最小代价**。那么枚举断点，该点以前的 $1$ 置 $0$，以后的 $0$ 置 $1$，得到：

$$
dp_i=\min_{j=1}^{i}(\sum_{k=1}^{j}a_k+\sum_{k=j}^{i-1}b_k)
$$

如果直接这样转移，每组数据时间复杂度 $O(N^2)$，过不了。考虑优化，由上式得：

$$
\begin{aligned}

dp_i&=\min(\min_{j=1}^{i-1}(\sum_{k=1}^{j}a_k+\sum_{k=j}^{i-1}b_k),\sum_{k=1}^{i}a_k+\sum_{k=i}^{i-1}b_k)\\

&=\min(\min_{j=1}^{i-1}(\sum_{k=1}^{j}a_k+\sum_{k=j}^{i-1}b_k),\sum_{k=1}^{i}a_k)\\

&=\min(\min_{j=1}^{i-1}(\sum_{k=1}^{j}a_k+\sum_{k=j}^{i-2}b_k)+b_{i-1},\sum_{k=1}^{i}a_k)\\

\end{aligned}
$$

注意到上式 $\min(,)$ 的左部恰好为 $dp_{i-1}$。所以，我们得到：

$$
dp_i=\min(dp_{i-1}+b_{i-1},\sum_{k=1}^{i}a_k)
$$

对于 $dp_i$ 计算答案时，以之后的 $1$ 串都被我们置 $0$ 来算即可。$a$ 数组做前缀和完事，时间复杂度 $O(\sum N)$。

### 代码

[link](https://atcoder.jp/contests/abc408/submissions/66338993)。

```cpp
#include<bits/stdc++.h>
#define int long long
#define db long double
#define Pii pair<int,int>
#define fi first
#define se second
#define inline
#define swap(x,y) x^=y^=x^=y
#define f(x,y) fixed<<setprecision(y)<<x
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,rp,stdin),p1==p2)?EOF:*p1++)

using namespace std;
const int N=1e6+10;
const int rp=1e6+10;

int t,n,m,ans,dp[N],a[N],b[N]; string s;
char buf[rp],*p1=buf,*p2=buf;

inline int read() 
{
	int x=0,f=1; char c=0;
    while(!isdigit(c)){if(c=='-') f=-1; c=gc();}
    while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=gc();
    return x*f;
}//好像没用快读？

inline char read_ch()
{
	char c=0;
	while((!isalpha(c))||(c>='0'&&c<='9')) c=gc();
	return c;
}

signed main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>s; m=0; ans=1e9;
		for(int i=0;i<n;++i)
			if(s[i]=='0'&&m==0) ;//舍开头 0
			else if(i==0||s[i]!=s[i-1]) dp[++m]=1;
			else ++dp[m];//预处理成串长
		if(!m) {cout<<"0\n"; continue;}//判全是 0
		m=(m+1)/2;
		for(int i=1;i<=m;++i) 
			a[i]=a[i-1]+dp[(i<<1)-1],b[i]=dp[i<<1];//存到 a,b 上，并对 a 做前缀和
		for(int i=0;i<=2*m;++i) dp[i]=0;//重复利用
		for(int i=1;i<=m;++i)
			dp[i]=min(dp[i-1]+b[i-1],a[i-1]),//推的式子
			ans=min(ans,dp[i]+a[m]-a[i]);//将该处往后均置 0
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：2)

## 分析

设最终我们要把区间 $[l,r]$ 变为 $1$，其余都是 $0$，那么操作代价是区间内的 $0$ 的数量 $c_0$ 加上区间外的 $1$。设区间内的 $1$ 数量为 $c_1$，总 $1$ 数量为 $tot$，则代价是 $c_0-c_1+tot$，由此，我们的目标是找到最小的 $c_0-c_1$，那就是最大的 $c_1-c_0$。

令 $sum_i=sum_{i-1}+[s_i=1]-[s_i=0]$，特别地，$sum_0=0$，这样我们相当于找最大的 $sum_i-sum_j(j<i)$，维护一下即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int sum[200010];
void solve()
{
	int n,cnt=0;
	cin>>n;
	string s;
	cin>>s;
	s=' '+s;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='1'?1:-1),cnt+=s[i]=='1';
	int mn=0,ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,sum[i]-mn);
		mn=min(mn,sum[i]);
	}
	cout<<cnt-ans<<'\n';
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
}

---

## 作者：P2441M (赞：2)

## 题意
给定一个长度为 $n$ 的 $0/1$ 串 $s$，你可以进行多次操作，每次操作可以选择 $1\leq i\leq n$ 并反转 $s_i$。求最少操作次数使得 $s$ 中**最多**有一个 $1$ 的极长连续段。多测，$1\leq T\leq 2\times 10^4$，$1\leq n\leq\sum{n}\leq 2\times 10^5$。

## 题解

神秘 D 题，害我交了两发贪心，吃了两发罚时。

预处理出 $pre_i=\sum_{j=1}^i[s_j=\texttt{1}]$，枚举操作后 $s$ 中 $1$ 的极长连续段 $[l,r]$，则其对应的操作次数为

$$
\begin{align*}
&pre_{l-1}+(pre_n-pre_r)+(r-l+1-(pre_r-pre_{l-1}))\\
=&pre_n+2pre_{l-1}-2pre_r+r-(l-1)\\
=&pre_n+(r-2pre_r)-(l-1-2pre_{l-1})
\end{align*}
$$

令 $a_i=i-2pre_i$，则上式变为

$$
pre_n+a_r-a_{l-1}
$$

于是答案即为

$$
\min_{l=1}^n\min_{r=l}^n\{pre_n+a_r-a_{l-1}\}=pre_n+\min_{r=l}^n\left\{a_r-\max_{l=0}^{r-1}a_l\right\}
$$

预处理 $a$ 的前缀最大值即可 $\mathcal{O}(n)$ 计算上式。注意还要特判 $s$ 操作后全 $0$ 的情况，对应操作次数就是 $pre_n$。

时间复杂度 $\mathcal{O}(n)$。

## 代码
```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 5, INF = 1e9;

int t, n, pre[N], a[N], mx[N];
char s[N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while (t--) {
    	cin >> n >> s + 1;
    	for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + (s[i] == '1');
        mx[0] = 0;
    	for (int i = 1; i <= n; ++i) a[i] = i - pre[i] * 2, mx[i] = max(mx[i - 1], a[i]);
    	int ans = pre[n];
    	for (int i = 1; i <= n; ++i) chk_min(ans, a[i] - mx[i - 1] + pre[n]);
    	cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：zzhbpyy (赞：1)

记 $S$ 中 $1$ 的个数为 $cnt$。

对于每个左端点 $l$ 满足 $1\le l \le N$，当右端点 $r$ 由 $k$ 变为 $k+1$ 时，若 $S_{k-1}=1$ 则操作次数减一，否则操作次数加一。

考虑把 $S_i=1$ 视为 $-1$，$S_{i-1}=0$ 视为 $1$，计算前缀和 $a_i$。

在枚举左端点 $l$ 时，最优操作次数为 $\min\{a_{l-1},a_l,\dots,a_n\}-a_{l-1}+cnt$。但直接这样做的复杂度是 $O(n^2)$，可以预处理 $a_i$ 的后缀最小值，优化至 $O(n)$。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a[200005],b[200005],n;
string s;
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
    cin>>t;
    while(t--){
        cin>>n>>s;s=' '+s;int cnt=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='1')a[i]=a[i-1]-1,cnt++;
            else a[i]=a[i-1]+1;
        }b[n]=a[n];
        for(int i=n-1;i>=0;i--){
            b[i]=min(a[i],b[i+1]);
        }int ans=INT_MAX;
        for(int i=0;i<n;i++){
            ans=min(ans,b[i]-a[i]);
        }
        for(int i=0;i<=n;i++)a[i]=b[i]=0;
        cout<<ans+cnt<<'\n';
    }
}
```

---

## 作者：bryce (赞：1)

## 思路
考虑一个区间 $l, r$ 的代价为需要多少次使得区间内的所有数变为 $1$，其它变为 $0$，于是答案就相当于找一个区间使得代价最少。

设 $a_i$ 表示 $[1, i]$ 中有多少个 $1$，区间 $l, r$ 的代价为 $w_{l, r}$，那么 $w_{l, r} = r - l + 1 - (a_r - a_{l - 1}) + a_{l - 1} + (a_n - a_r)$，变形得到 $w_{l, r} = 2a_{l - 1} + a_n - l + 1 + r - 2a_r$。

考虑枚举 $l$，则需要快速找到一个 $r$，使得 $w_{l, r}$ 是以 $l$ 为开头的最小的代价的区间。由上面的式子可得，需要找最小的 $r - 2a_r (r\ge l)$，于是可以预处理出 $r\in [l, n]$ 中最小的 $r - 2a_r$，最后对每个以 $l$ 开头的区间的最小代价取最小值即为答案。

## 代码
```cpp
#include<iostream>

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 2e5 + 10;
int T, n, ans;
char c[N];
int a[N], sum[N];
void solve(){
    n = read(), sum[n + 1] = 0x7fffffff;
    cin >> c;
    for (int i = n; i >= 1; i--) c[i] = c[i - 1], sum[i] = 0x7fffffff;
    for (int i = 1; i <= n; i++) a[i] = a[i - 1] + (c[i] == '1');
    ans = a[n];
    for (int i = n; i >= 1; i--)
        sum[i] = min(sum[i + 1], i - 2 * a[i]);
    for (int i = 1; i <= n; i++)
        ans = min(ans, sum[i] + 2 * a[i - 1] + a[n] - i + 1);
    cout << ans << '\n';
}

int main(){
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：lyx128 (赞：1)

本题目考虑使用线段树实现。

视频题解：

![](bilibili:BV1N77kzXEaE)

我们发现我们需要选出两个数$1 \leq l \leq r \leq n$，并将在 $l$ 左边的数全部改为 $0$，将 $l$ 到 $r$ 之间的数全部改为 $1$，将 $r$ 右边的数字全部改为 $0$。

即分别统计 $l$ 左边 $1$ 的个数，$l$ 到 $r$ 之间 $0$ 的个数，$r$ 右边的 $1$ 的个数。

我们考虑将 $r$ 使用扫描线的思想向右滑动，使用线段树求最小值操作求出当前最佳 $l$ 的位置。

以下为先段数的操作过程：

- 当 $S_i$ 为 $0$ 时，$i-1$ 及前面的所有权值均需要增加 $1$，因为右区间（需统计 $0$ 的区间）受到此操作的影响。

- 当滑动到 $i$ 时，我们需要将线段树 $i$ 位置的权值加上 $1$ 到 $i$ 之间 $1$ 的个数，作为 $1$ 到 $l$ 左侧需要统计的 $1$ 的贡献。

最后，当前位置 $i$ 的答案便是线段树中 $1$ 到 $i$ 之间的最小值加上 $i+1$ 到 $n$ 之间 $1$ 的个数。

代码实现如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5;
const int oo=2e9;
int T;
int n;
char s[N+5];
int cnt1,fcnt1;
int ans;

#define ls (id<<1)
#define rs (id<<1|1)
#define push_up(id) (st[id].val=min(st[ls].val,st[rs].val))

struct ST{
	int l,r;
	int val;
	int tag;
}st[(N<<2)+5];

void push_down(int id){
	if(!st[id].tag)
		return ;
	st[ls].val+=st[id].tag;
	st[rs].val+=st[id].tag;
	st[ls].tag+=st[id].tag;
	st[rs].tag+=st[id].tag;
	st[id].tag=0;
	return ;
}

void build(int id,int l,int r){
	st[id].l=l;
	st[id].r=r;
	st[id].val=0;
	st[id].tag=0;
	if(l==r)
		return ;
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(id);
	return ;
}

void update(int id,int l,int r,int x){
	if(l>r)
		return ;
	if(st[id].l>r||st[id].r<l)
		return ;
	if(st[id].l>=l&&st[id].r<=r){
		st[id].val+=x;
		st[id].tag+=x;
		return ;
	}
	push_down(id);
	update(ls,l,r,x);
	update(rs,l,r,x);
	push_up(id);
	return ;
}

int ask(int id,int l,int r){
	if(l>r)
		return oo;
	if(st[id].l>r||st[id].r<l)
		return oo;
	if(st[id].l>=l&&st[id].r<=r)
		return st[id].val;
	push_down(id);
	return min(ask(ls,l,r),ask(rs,l,r));
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		cin>>s+1;
		build(1,1,n);
		cnt1=0;
		fcnt1=0;
		ans=oo;
		for(int i=1;i<=n;i++)
			fcnt1+=(s[i]=='1');
		for(int i=1;i<=n;i++){
			if(s[i]=='0')
				update(1,1,i-1,1);
			update(1,i,i,cnt1);
			cnt1+=(s[i]=='1');
			fcnt1-=(s[i]=='1');
			ans=min(ans,ask(1,1,i)+fcnt1);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Wddie (赞：1)

#### 题意简述  
给定若干串仅由 $0$ 和 $1$ 组成长度为 $n$ 的数组 $s$，可以修改其中的一些数字，使所有的 $1$ 变为连续的一段，问最少要修改几次。  
#### 分析
一个十分暴力的做法是，将这个区间的左、右端点枚举出来，并计算出最少要修改几次即可。   
如何计算？我们定义 $sum_0(i,j)$ 表示 $[i,j]$ 中 $0$ 的个数，$sum_1(i,j)$ 表示 $[i,j]$ 中 $1$ 的个数。$l$ 为枚举区间的左端点，$r$ 为枚举区间的右端点。那么答案可以表示为：
$$
\min{(\sum_{i=1}^{l-1}s_i+r-l+1+\sum_{i=l}^rs_i+\sum_{i=r+1}^ns_i)}
$$  
接下来，我们考虑如何优化这个暴力。

先将去掉 $\min$ 后的式子中包含 $l$ 的部分、包含 $r$ 的部分与同时包含 $l$、$r$的部分分离出，得到：
$$
(\sum_{i=1}^{l-1}s_i)-l+(\sum_{i=l}^rs_i)+(\sum_{i=r+1}^{n}s_i)+r+1
$$ 
我们可以选择枚举右端点、考虑左端点，因为 
$
(\sum_{i=r+1}^ns_i)+r+1
$
仅与 $r$ 有关，所以可以直接放在 $\min$ 外处理。现在问题就变成了求：
$$ 
\min {(\sum_{i=1}^{l-1}s_i)-l+(\sum_{i=l}^rs_i)}
$$   
将 $\sum_{i=l}^rs_i$ 转化为 $(\sum_{i=r+1}^ns_i)-(\sum_{i=1}^{l-1}s_i)$，进一步去除与 $r$ 有关的项 $\sum_{i=r+1}^ns_i$，进一步把任务转换为求如下结果：
$$
\min(\sum_{i=1}^{l-1}s_i+\sum_{i=1}^{l-1}s_i)-l
$$
把去掉 $\min$ 后的式子去掉后变为：
$$
\sum_{i=1}^{l-1}s_i-(l-\sum_{i=1}^{l-1}s_i)
$$
分析后可以发现，上述式子实质上是在求 $[1,l-1]$ 范围内 $1$ 的个数与 $0$ 的个数之差。  
那么我们也可以直接通过两个前缀和数组维护 $[1,l-1]$ 中 $0$ 和 $1$ 分别的个数，然后相减、取 $\min$、求最小值即可。  

_code:_
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n;
char a[N];int pre[N][2];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			pre[i][0]=pre[i-1][0]+(a[i]=='0');
			pre[i][1]=pre[i-1][1]+(a[i]=='1');
//			cerr<<i<<' '<<pre[i][0]<<' '<<pre[i][1]<<'\n';
		}
		int  ans=0x3f3f3f3f,mn=0;
		for(int i=1;i<=n;i++){
//			for(int j=1;j<=i;j++){
//				ans=min(ans,pre[i-1][0]-pre[j-1][0]+pre[j-1][1]+pre[n][1]-pre[i][1]);
//			}
			ans=min(ans,pre[i-1][0]+mn+pre[n][1]-pre[i][1]);
			mn=min(mn,pre[i][1]-pre[i][0]);
		}
		cout<<ans<<'\n';
	}
	return 0;
} 


```

---

## 作者：Jerry20231029 (赞：1)

## 题目大意

给出一个长度为 $N$ 的字符串 $S$，$S$ 只含 `0` 和 `1`，每次操作可以修改 $S$ 中的一个字符，求至少修改多少次，可以使 $S$ **最多**只含一个由 `1` 组成的区间。

## 思路

其实题目就是我们需要选择一个区间，要求区间内 `0` 的数量加上区间外 `1` 的数量最小（因为要把区间外的 `1` 改成 `0`，把区间内的 `0` 改成 `1`）。

设 $\operatorname{C}_s(c)$ 为字符串 $s$ 中字符 $c$ 的数量，$s_{[l,r]}$ 为字符串 $s$ 的取区间 $[l,r]$ 的子串。

则选择区间 $[l,r]$  的操作次数为

$$
r-l+1-\operatorname{C}_{S_{[l.r]}}(\texttt{1})+\operatorname{C}_S(\texttt{1})-\operatorname{C}_{S_{[l.r]}}(\texttt{1})
$$

（$r-l+1-\operatorname{C}_{S_{[l.r]}}(\texttt{1})$ 是区间 $[l,r]$ 内 `0` 的数量，$\operatorname{C}_S(\texttt{1})-\operatorname{C}_{S_{[l.r]}}(\texttt{1})$ 是区间外 `1` 的数量）

我们可以把式子移项，得：

$$
r-l+1-\operatorname{C}_{S_{[l.r]}}(\texttt{1})-\operatorname{C}_{S_{[l.r]}}(\texttt{1})+\operatorname{C}_S(\texttt{1})
$$

我们发现“区间内 `0` 的数量”是正的，“区间内 `1` 的数量”是负的，所以我们可以把 $S$ 中的 `1` 记为 $-1$，`0` 记为 $1$，新数组记为 $a$，则公式变为：

$$
\operatorname{C}_S(\texttt{1})+\displaystyle\sum_{i=l}^r a_i
$$

由于 $\operatorname{C}_S(\texttt{1})$ 是固定的，所以求出 $\displaystyle\sum_{i=l}^r a_i$ 的最小值即可。

找最小值可以维护 $a$ 的前缀和，每枚举一位，拿这一位的前缀和减去之前最大的前缀和，就得到了结尾为这一位的最小子段和，再取每一位的最小值就是答案。

## 代码

[AC 记录](https://atcoder.jp/contests/abc408/submissions/66372175)

```cpp
#include<iostream>
#include<string>
using  namespace std;

int main(){
	int T,n,c,mx,mn,sum;
	string s;
	for(cin>>T; T--;){
		cin>>n>>s;
		c = mx = mn = sum = 0;
		for(char ch : s){
			c += ch=='1';
			sum += ch=='1' ? -1 : 1;
			mn = min(mn,sum-mx);
			mx = max(mx,sum);
		}
		cout<<c+mn<<'\n';
	}
	return 0;
}
```

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc408_d [ABC408D] 翻转以聚集 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc408_d)

### 题目大意

给出一个 01 字符串。一次操作是把其中一个字符从 `0` 变 `1`、从 `1` 变 `0`。现在通过若干次操作让整个字符串变得最多有一段连续的 `1`，问最小操作次数。

### 思路及实现

容易想到我们对于每段 `1` 变成 `0` 以消除或者 `1` 之间填充 `1` 以连接。但是段数超过二时将变得异常困难。此时可以考虑从相对形式化的结果开始考虑。

显然，最多一段连续 `1` 可能是没有 `1`。这样，操作次数就是初始字符串中 `1` 的数量，记为 $cnt$。

除此之外，就是剩下 $[L, R]$ 的范围是 `1`，其余是 `0` 了，此处 $L \le R$。想要把初始字符串变成这样，操作次数是在 $[L, R]$ 内的 `0` 个数和在 $[L, R]$ 外的 `1` 个数之和。

如果设在 $[L, R]$ 内的 `0` 有 $cnt_{0,L,R}$ 个，`1` 有 $cnt_{1,L,R}$ 个。转化为上述结果花费就是 $cnt_{0,L,R} + (cnt - cnt_{1,L,R}) = cnt - (cnt_{1,L,R} - cnt_{0,L,R})$。

注意到上式 $cnt$ 是常量，另一部分则只与初始字符串中 $[L,R]$ 区间的构成有关。容易想到求某个区间一个数减去零个数的极值来代替求上述答案。

如果我们在 $S_i = 1$ 时赋值 $a_i = 1$，而 $S_i = 0$ 时赋值 $a_i = -1$，就将问题再次变成了求 $a$ 的最大连续子序列和。

这是一个简单的 DP 问题。设它的答案是 $maxx$，答案就是 $cnt - maxx$。但是如果这里存在 $maxx < 0$，虽然这种情况当且仅当整个串都是 `0`，答案就不如 $cnt$。所以可以让 $maxx$ 初值就是 $0$，这样，可以避免上述情况。

最大连续子序列和可以 $O(N)$ 解决，自然，整个问题也是 $O(N)$ 解决。时间复杂度 $O(TN)$。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, N;
string S; 
int cnt, now, maxx;
int main()
{
	scanf("%d", &T);
    while (T--)
	{
        scanf("%d", &N);
        cin >> S;
        cnt = 0, now = 0, maxx = 0;
        for (int i = 0; i < S.length(); i++)
		{
			cnt += (S[i] == '1');
            now = max(((S[i] == '1') ? 1 : -1), now + ((S[i] == '1') ? 1 : -1));
            maxx = max(maxx, now);
        }
        printf("%d\n", cnt - maxx);
    }
    return 0;
}
```

---

## 作者：littlebug (赞：1)

## Solution

考虑如果把区间 $[l,r]$ 置为 $1$，其余都置为 $0$ 所需要的代价，设 $c_i$ 为 $s_1 \sim s_i$ 中 $0$ 的个数，$d_i$ 为 $s_1 \sim s_i$ 中 $1$ 的个数，则代价为：

$$
c_r - c_{l-1} + d_n - (d_r - d_{l-1})
$$

把与 $r$ 有关的放到一起，与 $l$ 有关的放到一起，就变成了：

$$
d_n + (c_r - d_r) - (c_{l-1} - d_{l-1})
$$

注意到 $d_n$ 是定值，后面两项都是 $c_i - d_i$ 的形式，所以考虑枚举 $r$，在 $1 \sim r$ 之间选一个能让 $c_{l-1} - d_{l-1}$ 最大数，这个直接前缀处理最大值就可以了。

时间复杂度 $O(n)$。

## Code

```cpp
int n,c[N],d[N];
string s;

il void solve()
{
    read(n),read(s),s="$"+s;
    rep(i,1,n) c[i]=c[i-1]+(s[i]=='0'),d[i]=d[i-1]+(s[i]=='1');

    int ans=0,mx=0;
    rep(i,1,n) chmin(ans,c[i]-d[i]-mx),chmax(mx,c[i]-d[i]);
    write(ans+d[n],'\n');
}
```

---

华风夏韵，洛水天依！

---

## 作者：heyx0201 (赞：0)

## 题意 
给定一个长度为 $n$ 的 01 串 $s$，每次操作可以把一个 `0` 变成 `1`，或把 `1` 变成 `0`。求把字符串内的所有 1 变成一个区间的最小操作次数。

## 思路
首先，考虑暴力思路。可以尝试枚举一个区间，然后暴力判断，时间复杂度 $O(n^3)$。

然后发现，实际上判断部分可以前缀后缀和实现，时间复杂度 $O(n^2)$。

由于要求区间信息，考虑枚举一个端点，去查找另一个端点的答案。这里枚举左端点 $l$。需要找到一个右端点 $r$，使得 $[l, r]$ 内的 0 个数与 $[r, n]$ 内 1 的个数之和最小。

考虑预处理。从大到小枚举一个左端点 $l$。设左端点为 $l$ 时的最小答案（即 $[l, r]$ 内的 0 个数与 $[r, n]$ 内 1 的个数之和最小值）为 $res_l$，则可以递推：
$$
res_l = \min \{ res_{l + 1}, cnt_1 \} + [s_l = 0]
$$

其中 $cnt_1$ 表示区间 $(l, n]$ 内 1 的数量。

为什么是这个递推式呢？首先，$res_l$ 当然可以是 $res_{l + 1} + [s_l = 0]$。因为可以在上一个答案的基础上直接在区间内添加 $s_l$。也可以是 $cnt_1 + [s_l = 0]$。因为可以把 $(l, n]$ 全变成 0，然后把 $s_l$ 一个变成 1。最后对这两个取最小值就 ok。

最后求答案。枚举一个左端点 $l$，它的答案就是 $cnt'_1 + res_l$。其中 $cnt'_1$ 表示 $[1, l)$ 内的 1 的个数。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 10;

string s;
int n, res[MAXN];

void Solve() {
  cin >> n >> s;
  s = '#' + s;
  int cnt1 = 0;
  res[n + 1] = 0;
  for (int i = n; i >= 1; i--) {
    res[i] = min(res[i + 1], cnt1) + (s[i] == '0');
    cnt1 += s[i] == '1';
  }
  int ans = n;
  cnt1 = 0;
  for (int i = 0; i <= n; i++) { // 这里是另一种枚举方式，没什么区别。
    cnt1 += s[i] == '1';
    ans = min(ans, cnt1 + res[i + 1]);
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  for (cin >> T; T--; Solve());
  return 0;
}
```

---

## 作者：Toorean (赞：0)

给出 `01` 串 $s$，可以将串中任意字符翻转。求最少翻转次数，使 $s$ 中 `1` 连续。

设 $f(i)$ 表示到 $s_i$ 的最少翻转次数，$sum(i)$ 表示 $[1,i]$ 中 `1` 出现次数。考虑从哪里开始为 `1`，那么有 $f(i)=\min\limits_{j=1}^i \{sum(j-1)+(i-j+1)-[sum(i)-sum(j-1)]+sum(n)-sum(i)\}$。

把与 $j$ 无关项分离出来，那么有 $f(i)=sum(n)+1-i-2\times sum(i)+\min\limits_{j=1}^i\{2\times sum(j-1)+j\}$。

我们只需预处理出后面的 $\min$ 值，即可实现 $\mathcal O(n)$ 总体复杂度。

---

