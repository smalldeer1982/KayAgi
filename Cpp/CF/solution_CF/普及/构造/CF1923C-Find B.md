# Find B

## 题目描述

An array $ a $ of length $ m $ is considered good if there exists an integer array $ b $ of length $ m $ such that the following conditions hold:

1. $ \sum\limits_{i=1}^{m} a_i = \sum\limits_{i=1}^{m} b_i $ ;
2. $ a_i \neq b_i $ for every index $ i $ from $ 1 $ to $ m $ ;
3. $ b_i > 0 $ for every index $ i $ from $ 1 $ to $ m $ .

You are given an array $ c $ of length $ n $ . Each element of this array is greater than $ 0 $ .

You have to answer $ q $ queries. During the $ i $ -th query, you have to determine whether the subarray $ c_{l_{i}}, c_{l_{i}+1}, \dots, c_{r_{i}} $ is good.

## 样例 #1

### 输入

```
1
5 4
1 2 1 4 5
1 5
4 4
3 4
1 3```

### 输出

```
YES
NO
YES
NO```

# 题解

## 作者：YBaggio (赞：2)

[https://codeforces.com/contest/1923/problem/C](https://codeforces.com/contest/1923/problem/C)

[更好的阅读体验（maybe](https://ybaggio.fun/index.php/archives/79/)
# 题意
如果存在一个长度为 $m$ 的整数数组 $b$ 且以下条件成立，那么长度为 $m$ 的数组 $a$ 就被认为是好数组：
1.  $\sum\limits_{i=1}^{m} a_i = \sum\limits_{i=1}^{m} b_i$;
2. $a_i \neq b_i$；
3. $b_i > 0$。

给你一个长度为 $n$ 的数组 $a$。数组中的每个元素都大于 $0$。

你必须回答 $q$ 个查询。在第 $i$ 个查询中，你必须确定子数组 $a_{l_{i}}, a_{l_{i}+1}, \dots, a_{r_{i}}$ 是否是好数组。
# 题解
判断一个数组 $a$ 好不好，我们可以转化为能否构造出合法的 $b$。

首先，如果 $[l, r]$ 中所有元素 $a_i$ 均大于 $1$, 那么子数组 $a_l, a_{l+1}, \dots, a_r$，必然是好数组，因为我们可以将 $a_{l \dots r - 1}$ 分出 $r - l$ 加在 $a_r$ 上，得到满足条件的 $b$ 数组。

于是我们观察到，影响一个数组 $a$“不好”的原因就是 $a$ 中存在 $1$。因为 $a_i = 1$ 时无法减少自己的值，需要其他元素减少值补给自己，而当其他元素可以补给自己的值不够时，则无法构造出满足条件的 $b$ 数组。

于是我们预处理每个前缀最多有多少值可以补给区间中 $a_i = 1$ 的元素，$f_i = \sum\limits_{j = 1}^{i}{(a_j - 1)}$。和每个前缀有多少值为 $1$ 的元素。
最后对每个询问进行检查即可。
```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int maxn = 300010;
int t, n, m, a[maxn];
ll s[maxn], p[maxn];
int main () {
  ios::sync_with_stdio (false);
  cin.tie (0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      s[i] = s[i - 1] + (a[i] == 1);
      p[i] = p[i - 1] + (a[i] - 1);
    }
    for (int i = 1; i <= m; i++) {
      int l, r; cin >> l >> r;  
      if (l == r) cout << "NO\n";
      else cout << ((s[r] - s[l - 1] <= p[r] - p[l - 1]) ? "YES" : "NO") << '\n';
    }
  }
  return 0;
}
```

---

## 作者：2huk (赞：1)

寒假最后一场 CF 没上 Expert，气死我了。

## Decsription

给定一个长度为 $n$ 的数组 $c$。$q$ 次询问一个区间 $c_l \dots c_r$，判断是否存在一个整数数组 $b$ 使得：

- $\sum_{i=l}^r c_i = \sum_{i = l}^r b_i$；
- $\forall l \le i \le r$，$c_i \ne b_i$；
- $\forall l \le i \le r$，$b_i > 0$。

## Solution

首先我们可以全填 $1$，即所有 $b_i \gets 1$。考虑这样会有什么问题：

- 某些下标 $i$ 会导致 $c_i = b_i$。显然这些位置是原来 $c_i = 1$ 的位置。
- 总和会小。总共小了 $\sum_{i = l}^r c_i - (r - l + 1)$。

我们希望同时解决这两个问题。方法是这样的：

- 对于第一个问题，我们只能让这些 $b_i$ 变大。所以我们希望把那些原来满足 $c_i = 1$ 的 $b_i$ 加上某一个正数。
- 对于第二个问题，我们也希望在某些 $b_i$ 上总共加 $\sum_{i = l}^r c_i - (r - l + 1)$，且这些这些 $b_i$ 也都加上某一个正数。

不难发现这两个问题的解决方案十分相似。

所以同时解决这两个问题的方法就是在原来那些 $c_i = 1$ 的位置上加数，其它位置保持不变。我们需要判断的就是能否加完总共的 $\sum_{i = l}^r c_i - (r - l + 1)$。

假设区间内一共有 $x$ 个位置满足 $c_i = 1$，那么如果方案可行，就代表 $\sum_{i = l}^r c_i - (r - l + 1) \ge x$。反证极易。

所以维护前缀和计算即可。

## Code

```cpp
// Problem: C. Find B
// Contest: Codeforces - Educational Codeforces Round 162 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1923/problem/C
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

#define int long long
typedef long long ll;
typedef unsigned long long LL;
typedef pair<int, int> PII;

struct FASTREAD {
	template <typename T>
	FASTREAD& operator >>(T& x) {
		x = 0; bool flg = false; char c = getchar();
		while (c < '0' || c > '9') flg |= (c == '-'), c = getchar();
		while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
		if (flg) x = -x; return *this;
	}
	template <typename T>
	FASTREAD& operator >>(vector<T>& x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) >> *it;
		return *this;
	}
}fin;

struct FASTWRITE {
	template <typename T>
	FASTWRITE& operator <<(T x) {
		if (x < 0) x = -x, putchar('-');
		static int buf[35]; int top = 0;
		do buf[top ++ ] = x % 10, x /= 10; while (x);
		while (top) putchar(buf[ -- top] + '0');
		return *this;
	}
	FASTWRITE& operator <<(char x) {
		putchar(x); return *this;
	}
	template <typename T>
	FASTWRITE& operator <<(vector<T> x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) << *it, putchar(' ');
		putchar('\n');
		return *this;
	}
}fout;

const int N = 1e6 + 10;
const int P = 998244353;

void Luogu_UID_748509() {
	int n, q;
	fin >> n >> q;
	vector<int> a(n + 1), s1(n + 1), de(n + 1);
	for (int i = 1; i <= n; ++ i ) {
		fin >> a[i];
		s1[i] = s1[i - 1] + (a[i] == 1);
		de[i] = de[i - 1] + a[i] - 1;
	}
	
	while (q -- ) {
		int l, r;
		fin >> l >> r;
		if (l == r) puts("NO");
		else if (de[r] - de[l - 1] >= s1[r] - s1[l - 1]) puts("YES");
		else puts("NO");
	}
	
	return;
}

signed main() {
	int Testcases = 1;
	fin >> Testcases;
	while (Testcases -- ) Luogu_UID_748509();
	return 0;
}
```

---

## 作者：ZZZZZZZF (赞：1)

# 思路

~~新年之后第一场 cf 惨遭 hack。~~

直观上，一个随机的序列很难是不好的。关键在于找出什么情况下一个序列会被认为是不好的。

题目中说 $b$ 中所有数都要是正整数。不难想到 $1$ 的数量是一个限制条件。如果一个序列中没有 $1$，我们总能让其中的数减少或者增加来变得和原序列不同。如果序列中 $1$ 的数量太多，就会出现不好序列的情况，因为 $1$ 只能加不能减，这会阻碍我们将序列进行变化。所以从 $1$ 的数量去考虑。

好序列的定义是序列和相同，我们可以将序列 $a$ 得到序列 $b$ 的过程看作将 $a$ 中某些数大于 $1$ 的部分补到 $a$ 中的 $1$ 上去。如果序列的和足够大，足以让 $a$ 中的 $1$ 全部 $+1$ 从而和原序列错开，那么就可以构成好序列。因为对于非 $1$ 的数，如果被减到了 $1$，那么他就可以和原序列错开，如果没有被减到 $1$，他就可以将自己大于 $1$ 的部分补到原序列中的 $1$ 上，让自己变成 $1$。

总之，只要原序列中的 $1$ 能全被抬升，剩下的数无论如何总能和原序列错开。

# 做法

定义序列长度为 $len$，序列中 $1$ 的数量为 $\operatorname{cnt}(1)$。

如果序列和能将 $1$ 全部抬升，即 $\operatorname{cnt}(1) \le \sum_{i = l}^{r}a_i - len$，那么这个序列就是好的，反之则不是。

注意特判 $l = r$ 的情况，一定不是好序列。

求和用前缀和处理，时间复杂度为 $O(m+n)$。

本题如果在循环中开 ```vector``` 或者使用 ```memset``` 来初始化，很可能会发生 TLE，并且输出使用 ```"\n"``` 的速度远远快于使用 ```endl```。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300005
long long sum1[N],sum[N];//1的数量 前缀和 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,q;
        cin>>n>>q;
        for(int i = 1;i<=n;i++){
            cin>>sum[i];
            sum[i] += sum[i-1];
            sum1[i] = sum1[i-1];
            if(sum[i] - sum[i-1] == 1)
                sum1[i]++;
        }
        while(q--){
            int x,y;
            cin>>x>>y;
            long long len = (y-x+1),s = sum[y]-sum[x-1],n1 = sum1[y]-sum1[x-1];
            if(len == 1){ //特判长度为1
                cout<<"NO\n";
            }
            else if(s-len>=n1) {
                cout<<"YES\n";
            }
            else cout<<"NO\n";
        }
    }
    return 0;
}
```

---

## 作者：AKPC (赞：0)

定义 $p_i=[a_i=1]+1$。

对于查询的区间 $[l,r]$，有以下几种情况：

- $\max\limits_{i=l}^rp_i=1$，说明 $\min\limits_{i=l}^ra_i\geq2$，任取一个位置 $i\in[l,r]$ 把 $b_i$ 设为 $\sum\limits_{i=l}^ra_i-(r-l)$，其余位置的 $b$ 全部设为 $1$ 即可，很好证明 $b_i>a_i$。
- $\min\limits_{i=l}^rp_i=2$，说明 $\max\limits_{i=l}^ra_i=1$，你只能把每个 $b_i$ 设为 $1$，所以这是无解的。
- 反之，把 $p_i=2$ 的位置的 $b_i$ 设为 $1$，把其余位置设为 $2$，如果总和多了，显然就是无解，否则这样就是一个解，如果总和不够可以往 $p_i=1$ 的位置的 $b_i$ 上随便加。

---

## 作者：FeiDing (赞：0)

瞪眼出结论题

# 结论

先考虑只有一次询问的情况。

我们要构造一个序列 $b$。

1. 如果 $c_i$ 是 $1$，那么 $b_i$ 取 $2$。
2. 否则，$b_i$ 取 $1$。

这样就能做到 $\Sigma b$ 尽量小。

如果 $\Sigma b \le \Sigma c$,那么肯定是可以通过一些骚操作满足条件的。否则再怎么样也不行，毕竟 $\Sigma b$ 已经尽量小了。

这样我们就胡出了一个 $\Theta(n)$ 的算法。

---

# 实现

为了实现多次询问，要用前缀和优化。

[代码](https://codeforces.com/contest/1923/submission/247945649)很简单的啦。

不过不知道为什么，有人不开 `long long` 被 Hack，我不开 `long long` 却是没过 pretest。

---

## 作者：I_will_AKIOI (赞：0)

我们注意到规则中的第二条和第三条：所有数互不相等并且大于 $0$。若 $a_i=1$，则 $b_i$ 至少为 $2$。否则的话，$b_i$ 就可以为 $1$ 了。说明这里 $1$ 的花费比其他数多，需要单独考虑。

所以我们使用贪心算法：最小化 $b_i$，若 $\sum\limits_{i=1}^{m} b_i > \sum\limits_{i=1}^{m} a_i$，则是无解的，否则有解。并且还有一种特殊情况：当 $l=r$ 时无解。

这里需要记录区间和及区间 $1$ 的出现个数，就可以使用前缀和啦。

题目比较坑，不开 ```long long``` 赛时能 A，赛后会被 hack。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q,x,y,a[300005],sum[300005],cnt[300005];
void solve()
{
  cin>>n>>q;
  for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i],cnt[i]=cnt[i-1]+(a[i]==1);
  while(q--)
  {
    cin>>x>>y;
    int Sum=sum[y]-sum[x-1];
    int Cnt=cnt[y]-cnt[x-1];
    Sum-=Cnt*2;
    Sum-=y-x+1-Cnt;
    if(Sum<0||x==y) cout<<"NO\n";
    else cout<<"YES\n";
  }
  return;
}
signed main()
{
  ios::sync_with_stdio(false);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：Luzhuoyuan (赞：0)

Links:[[to Codeforces]](https://codeforces.com/contest/1923/problem/C) [[to Luogu]](https://www.luogu.com.cn/problem/CF1923C)

### 题意简述

定义一个长为 $m$ 的正整数序列 $a$ 是好的，当且仅当存在长为 $m$ 的正整数序列 $b$ 满足以下条件：

- $\displaystyle\sum_{i=1}^m a_i=\sum_{i=1}^m b_i;$
- $\forall i\in[1,m],a_i\ne b_i.$

给定一个长为 $n$ 的正整数序列 $c$ 和 $q$ 个询问，每次询问给出 $l_i,r_i$，要求判断 $c_{l_i},c_{l_i+1},\dots,c_{r_i-1},c_{r_i}$ 是否是好的序列。每个测试点 $t$ 组测试用例。

$$1\le t\le 10^4;1\le n,q,\sum n,\sum q\le 3\cdot 10^5;1\le c_i\le 10^9;1\le l_i\le r_i\le n$$

### 思路

考虑根据一个 $a$ 构造一个合法的 $b$。首先若 $m=1$ 必然无解。之后由于 $b_i\ge 1,b_i\ne a_i$，所以对于每个 $a_i=1$，对应的 $b_i$ 相对 $a_i$ 至少要增加 $1$，设 $s1$ 表示 $a_i=1$ 的个数，则总共至少要增加 $s1$。由于总和要相等，我们考虑怎样把 $b$ 的和减回来。

对于每个 $a_i>1$，我们最多能让它在 $b$ 中变成 $1$，设 $s=\displaystyle\sum_{i=1}^m (a_i+1)$，则在这些位置 $b$ 相对 $a$ 至多减少 $s$。

那么如果至少要增加的值比至多能减小的值要大，即 $s1>s$，那么肯定不可能满足总和相等，必然无解。

对于其他情况，我们很容易构造出一种方法。比如，可以令 $b_i=\begin{cases}2 & a_i=1\\1 & a_i>1\end{cases}$，此时必然有 $\sum b\le\sum a$，我们再把 $b$ 中某个值调大一点（或者不变）就行了。

所以只要预处理 $s1$ 和 $s$ 的前缀和就行了。注意特判 $l_i=r_i$ 的情况。复杂度 $O(n+m)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int T,n,m,x,y,s1[N],s[N];
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
signed main(){
	T=read();
	while(T--){
		n=read(),m=read();
		for(int i=1;i<=n;i++)x=read(),s1[i]=s1[i-1]+(x==1),s[i]=s[i-1]+x-1;
		while(m--)x=read(),y=read(),puts(y>x&&s1[y]-s1[x-1]<=s[y]-s[x-1]?"YES":"NO");
	}
	return 0;
}
```
（逃

---

