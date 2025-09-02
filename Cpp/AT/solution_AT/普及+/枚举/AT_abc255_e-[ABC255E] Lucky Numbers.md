# [ABC255E] Lucky Numbers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc255/tasks/abc255_e

長さ $ N-1 $ の整数列 $ S\ =\ (S_1,\ S_2,\ \ldots,\ S_{N-1}) $ および、「ラッキーナンバー」として $ M $ 個の相異なる整数 $ X_1,\ X_2,\ \ldots,\ X_M $ が与えられます。

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ であって、次の条件を満たすものを「良い数列」と呼びます。

> すべての $ i\ =\ 1,\ 2,\ \ldots,\ N-1 $ について、$ A_i\ +\ A_{i+1}\ =\ S_i $ が成り立つ。

良い数列 $ A $ を $ 1 $ つ選ぶときの、$ A $ の要素のうちラッキーナンバーであるものの個数（すなわち、$ A_i\ \in\ \lbrace\ X_1,\ X_2,\ \ldots,\ X_M\ \rbrace $ となる $ 1 $ 以上 $ N $ 以下の整数 $ i $ の個数）としてあり得る最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10 $
- $ -10^9\ \leq\ S_i\ \leq\ 10^9 $
- $ -10^9\ \leq\ X_i\ \leq\ 10^9 $
- $ X_1\ \lt\ X_2\ \lt\ \cdots\ \lt\ X_M $
- 入力はすべて整数

### Sample Explanation 1

良い数列 $ A $ として $ A\ =\ (3,\ -1,\ 4,\ -1,\ 5,\ -9,\ 2,\ -6,\ 5) $ を選ぶと、$ A $ の要素のうちラッキーナンバーであるものは $ A_2,\ A_4,\ A_5,\ A_9 $ の $ 4 $ 個となり、これが考えられる中で最大です。

## 样例 #1

### 输入

```
9 2
2 3 3 4 -4 -7 -4 -1
-1 5```

### 输出

```
4```

## 样例 #2

### 输入

```
20 10
-183260318 206417795 409343217 238245886 138964265 -415224774 -499400499 -313180261 283784093 498751662 668946791 965735441 382033304 177367159 31017484 27914238 757966050 878978971 73210901
-470019195 -379631053 -287722161 -231146414 -84796739 328710269 355719851 416979387 431167199 498905398```

### 输出

```
8```

# 题解

## 作者：HyB_Capricornus (赞：7)

本人第一篇题解。

$2022/12/27/10:08$ 修改汉字与数学公式应该空格的错误，重新提交审核。

$2022/12/27/11:16$ 审核通过。

### 题目大意：

题目给出 $N-1$ 个数的一个数列 $S=(S_1,S_2,\ldots ,S_{N-1})$。另外给出 $M$ 个互不相同的整数 $X_1,X_2,X_3,\ldots,X_M$
。这 $M$ 个数是 “幸运数”。
我们假定有一个 “原序列” ，使得对于任意一个 $i\in[1,N-1]$ ，有 $S_i=A_i+A_{i+1}$
。
我们希望构造一个 “原序列” ，使原序列中存在尽可能多的 “幸运数”。请问这个原序列中最多有多少个
“幸运数”。当原序列中存在某个幸运数多次的时候，幸运数个数按多次计算。

### TLE 做法：

~~我不相信这题只有绿~~

我们可以很容易发现一个入手点，就是**若我们能推出 $a_i$，可以使用若干次推导知道 $a$ 数组** (由 $s_{i-1}-a_i$ 求出 $a_{i-1}$，由 $s_{i}-a_i$ 求出 $a_{i+1}$，然后递推下去)。

不难发现，若 $a_i$ 可以推出 $a_1$，$a_1$ 也可以推出 $a_i$，设 $a_i$ 推出的 $a_1=v$，并且 $a_i$ 推出的 $a_1$ 与 $a_j$ 推出的 $a_1$ 相同，则通过 $v$ 可以推出 $a_i$，也可以推出 $a_j$，**则说明 $a_i$ 与 $a_j$ 可以在一个合法的序列中同时存在**。

可以想到，**我们希望有多个幸运数同时存在**，我们可以把一个幸运数所推出来的 $a_1$ 当做这个幸运数的标识，若出现重复则**说明可以构造一个原序列使得这两个幸运数可以同时出现**，重复几次就代表有几个幸运数可以同时出现。

但是复杂度应该不太能通过本题。

### 大优化：
我们发现可以优化的部分就是知道 $a_i$ 求得 $a_1$ 的部分，我们要想办法通过预处理 $O(1)$ 解决。

我们可以知道：

$$
\left\{
\begin{aligned}
A_2 & = S_1-A_1 \\
A_3 & = S_2-A_2 \\
A_4 & = S_3-A_3 \\
& \ldots\ldots \\
A_n & = S_{n-1}-A_{n-1}
\end{aligned}
\right.
$$

因为 $A_3=S_2-A_2$，且 $A_2=S_1-A_1$，可以将 $A_2$ 换为 $S_1-A_1$ 推出 $A_3=S_2-(S_1-A_1)=S_2-S_1+A_1$。

以此种规律递推可以知道：

$$
\left\{
\begin{aligned}
A_2 & = S_1-A_1 \\
A_3 & = S_2-S_1+A_1 \\
A_4 & = S_3-S_2+S_1-A_1 \\
A_5 & = S_4-S_3+S_2-S_1+A_1\\
& \ldots\ldots \\
A_n & = S_{n-1}-S_{n-2}+S_{n-3}-S_{n-4}+\ldots+(-1)^{n} \times A_1
\end{aligned}
\right.
$$

既然我们已经知道了知道 $A_1$ 求 $A_n$ 的求法，不难反推知道 $A_n$ 求 $A_1$ 的求法。

$$A_n = S_{n-1}-S_{n-2}+S_{n-3}-S_{n-4}+\ldots+(-1)^{n} \times A_1$$
$$-((-1)^{n} \times A_1) = (S_{n-1}-S_{n-2}+S_{n-3}-S_{n-4}+\ldots-A_n)$$
$$(-1)^{n+1} \times A_1 = (S_{n-1}-S_{n-2}+S_{n-3}-S_{n-4}+\ldots)-A_n$$
$$A_1 = \frac{S_{n-1}-S_{n-2}+S_{n-3}-S_{n-4}+\ldots-A_n}{ (-1)^{n+1}}$$

很显然，$S_{n-1}-S_{n-2}+S_{n-3}-S_{n-4}+\ldots$ 一部分可以用预处理 $O(1)$ 解决。

这里本人思路将 $S_{n-1}-S_{n-2}+S_{n-3}-S_{n-4}+\ldots$ 定义为 $B_n$，递推公式可以有上述所推：

$$B_i=S_{n-1}-S_{n-2}+S_{n-3}-S_{n-4}+\ldots$$
$$B_i=S_{i-1}-(S_{n-2}-S_{n-3}+S_{n-4}-\ldots)$$
$$B_i=S_{i-1}-B_{i-1}$$

则 $O(1)$ 求知道 $A_n$ 求 $A_1$ 的方法为：

$$A_1=\frac{B_n-A_n}{ (-1)^{n+1}}$$

由于本人为了看起来更方便，并且由于 $\frac{X}{1}$ 或$\frac{X}{-1}$ 均等于 $X \times 1$ 与 $X \times (-1)$，所以可将其换成：

$$A_1=(B_n-A_n)\times(-1)^{n+1}$$

下面给出 $\color{green}AC$ 代码：

```c++
#include <iostream>
#include <map>
#define MAXN 100010
#define MAXM 15
#define ll long long
using namespace std;
ll n,m;
ll s[MAXN],luky[MAXM];
ll a[MAXN],b[MAXN];
map<ll,ll> mp;
ll k;
int main(void) {
    cin>>n>>m;
    for (ll i=1;i<n;i++)
        cin>>s[i];
    for (ll i=1;i<=m;i++)
        cin>>luky[i];
    for (ll i=2;i<=n;i++)
        b[i]=s[i-1]-b[i-1]; //递推公式，上文已做推导
    for (ll i=1;i<=n;i++)
        for (ll j=1;j<=m;j++)
            mp[(b[i]-luky[j])*(i%2?-1:1)]++; //luky[i] 对应文中 a[n]
    for (map<ll,ll>::iterator it=mp.begin();it!=mp.end();it++)
        k=max(k,it->second); //查找最多相同的 a[1]
    cout<<k;
    return 0;
}
```

---

## 作者：xuan_gong_dong (赞：3)

很想[这个题](https://www.luogu.com.cn/problem/P5847)。
## 题面
[[ABC255E] Lucky Numbers](https://www.luogu.com.cn/problem/AT_abc255_e)
## 分析
一看是以为 $n$ 和 $m$ 同阶，想了好久，觉得好难，放到一边摆了一会继续看，才发现 $m \le 10$。

首先很容易发现从 $a_2$ 一直到 $a_n$ 都是可以直接被 $a_1$ 递推而来，而这个递推又是很容易去预处理的，那么我们不就可以直接存储当 $X_i$ 是 $a_j$ 时的 $a_1$ 最多出现的 $a_1$ 就是答案，可以用一个 哈希表或者其他映射方式就好了。

时间复杂度 $O(n \times m \log n)$，可以通过。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int s[100010],x[100];
int Max=0;
map < int , int > mp;
int c[100010];
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<n;i++)
	{
		scanf("%lld",&s[i]);
		c[i]=s[i]-c[i-1];
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&x[i]);
		for(int j=1;j<=n;j++)
		{
			int a=x[i]-c[j-1];
			if(j%2==0)a=-a;
			mp[a]++;
			if(mp[a]>Max)Max=mp[a];
		}
	}
	printf("%lld",Max);
	return 0;
}
```


---

## 作者：Ryan_Adam (赞：2)

## 题解：AT_abc255_e [ABC255E] Lucky Numbers
### 算法
枚举，思维
### 分析
根据题意，我们很容易发现，只要确定了 $a$ 序列中的任意一个数，我们就可以通过 $S$ 序列来推出整个 $a$ 序列。

发现 $m$ 的范围是很小的，所以我们可以假设 $a_i$ 是幸运数，将其构成的序列都标记一下，最终获得标记最多的那个序列就是幸运数最多的序列。因为序列 $a$ 可以由任意一个 $a_i$ 推演出来，所以我们可以用 $a_1$ 来代表序列 $a$。（当然其他表示方法如 $a_n$ 也可以）

目前我们需要枚举 $a_i（1\le i\le n）$，每个 $a_i$ 枚举 $x_j（1\le j\le m）$，此时复杂度已经是 $\mathcal{O(nm)}$ 了，所以我们需要 $\mathcal{O(1)}$ 由 $a_i$ 推出 $a_1$。

由题可知 $S_1=a_1+a_2,S_2=a_2+a_3,\cdots$，所以可知： 
$$a_1=S_1-a_2=S_1-S_2+a_3=\cdots=S_1-S_2+S_3-\cdots+(-1)^{i-2}S_{i-1}+(-1)^{i-1}a_i$$
我们把 $S_1-S_2+S_3-\cdots+(-1)^{i-2}S_{i-1}$ 预处理一下就可以 $\mathcal{O(1)}$ 推出 $a_1$ 了。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int s[N],x[N],ss[N];
int n,m;
vector<vector<int> > v;
map<int,int> mp;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n-1;i++)
        cin>>s[i];
    for(int i=1;i<=m;i++)
        cin>>x[i];
    ss[1]=s[1];
    for(int i=2;i<=n;i++)
        ss[i]=ss[i-1]+(i&1?1:-1)*s[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            mp[ss[i-1]+(i&1?1:-1)*x[j]]++;
    int ans=-1;
    for(auto it:mp)
        ans=max(ans,it.second);
    cout<<ans<<endl;
    return 0;
}
/*
9 2
2 3 3 4 -4 -7 -4 -1
-1 5
*/
```

---

## 作者：灵茶山艾府 (赞：2)

根据题意，确定序列 $A$ 中的任意一个数，就能确定整个序列 $A$。

一种暴力的做法是，枚举每个 $A_i=X_j$，去看生成的序列 $A$ 能有多少个幸运数，但这种做法是 $O(N^2M)$ 的，需要优化。

根据题意，$A_1$ 与 $A_i$ 的关系为：

$$
A_1 = S_1 - S_2 + S_3 - \cdots + (-1)^{i-1}A_i
$$

不妨以 $A_1$ 为「参照物」，在枚举 $A_i=X_j$ 时，算出对应的 $A_1$，同时用一个哈希表统计 $A_1$ 的出现次数，最后取哈希表中所有出现次数的最大值，即为答案。

AC 代码（Golang）：

```go
package main
import ("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, m, sum, ans int
	Fscan(in, &n, &m)
	s := make([]int, n-1)
	for i := range s {
		Fscan(in, &s[i])
	}
	cnt := make(map[int]int, n*m)
	x := make([]int, m)
	for i := range x {
		Fscan(in, &x[i])
		cnt[x[i]]++
	}
	for i, v := range s {
		if i&1 > 0 {
			sum -= v
			for _, w := range x {
				cnt[sum+w]++
			}
		} else {
			sum += v
			for _, w := range x {
				cnt[sum-w]++
			}
		}
	}
	for _, c := range cnt {
		if c > ans {
			ans = c
		}
	}
	Print(ans)
}
```


---

## 作者：TSY48 (赞：1)

**解题思路**

不难发现，知道 $A_1$，即可知道 $A_2,\dots,A_n$。

令 $t_i=S_i-t_{i-1}$，则递推式如下：
$$
A_i=t_i+(-1)^{i+1}\times A_1
$$


知道这个后，就可以直接枚举 $A_i=X_j$ 算出对应的 $A_1$ 用个 map 记录 $A_1$ 出现的次数，答案便是 $A_1$ 出现的最大数。

部分代码如下：

```c++
for(int i=2;i<=n;i++){
    int s;
    scanf("%lld",&s);
    t[i]=s-t[i-1]; 
}
for(int i=1;i<=m;i++) scanf("%lld",&x[i]);
int ans=-1;
for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
       	int now=x[j]-t[i];
        if(!(i&1)) now*=(-1ll);
        rec[now]++;
        ans=max(ans,rec[now]);
    }
}
```

---

## 作者：lovely_codingcow (赞：1)

## 思路

### 朴素做法

首先我们考虑一定可以有一个点是幸运数，于是我们可以考虑遍历每一个 $S_i$，钦定 $a_i$ 是一个幸运数，然后我们就可以反推出 $a_1$ 的值。然后我们统计 $a_1$ 重复被计算出的次数。因为只要有一个 $a_i$ 被确定了，整个序列就确定了。也就是说，$a_1$ 的重复次数就是我们要求的最多的幸运数个数，因为他们都是同一个序列。如果我们这样做，时间复杂度是 $\mathcal{O}(n^2m)$，很显然无法通过本题。

### 优化做法

我们考虑如何优化这个算法。我们回顾一下计算 $a_1$ 值的过程。我们假设已经确定了 $a_x$ 的值：

- 如果 $x$ 是**奇数**，那么很显然式子是
	$$
	S_{x - 1}-S_{x-2}+S_{x-3}-\cdots+S_{1}-a_1
	$$
- 如果 $x$ 是**偶数**，那么仍然很显然的是式子是
	$$
	S_{x-1}-S_{x-2}+S_{x-3}-\cdots-S_1+a_1
	$$

很显然，由于 $S_i$ 不会改变，$\pm a_1$ 之前的一长串式子也不会改变，因此我们可以考虑预处理 $\pm a_1$ 前面的式子，然后 $\mathcal{O}(1)$ 求值。

让我们设 $f_{i,\,0}$ 为此时 $S_i$ 系数为负的情况，$f_{i,\,1}$ 为此时 $S_{i}$ 系数为正的情况。聪明的你可能发现了，$f_{i,\,0}$ 在最终计算时不需要的，但是在预处理的过程中，这是必要的。很容易推出状态转移方程

$$
\begin{array}{l}
f_{i,\,0}=f_{i-1,\,1}-S_i \\
f_{i,\,1}=f_{i-1,\,0}+S_i
\end{array}
$$

我们可以 $\mathcal{O}(n)$ 预处理，然后采用朴素做法的思路统计答案，总复杂度为 $\mathcal{O}(nm)$，可以通过。

## 代码

```cpp
#include <iostream>
#include <map>

#define int long long

using namespace std;

int n, m, s[100009], x[20], f[100009][2];
map<int, int> mp;

signed main() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++) {
        f[i][0] = f[i - 1][1] + s[i];
        f[i][1] = f[i - 1][0] - s[i];
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            mp[(j & 1 ? 1 : -1) * (x[i] - f[j - 1][0])] += 1;
        }
    }
    int ans = 0;
    for (auto &[i, j]: mp) {
        ans = max(ans, j);
    }
    cout << ans;
}
```

---

## 作者：appear_hope (赞：1)

如果知道了 $A_i$ 中的任意一个元素，我们就能还原 $A$ 序列。

那么通过这个思路往下走可以想到答案至少为 $1$。

首先第一个思路：

枚举 $A_i = X_j$，然后还原原序列。

时空复杂度：

时间复杂度：$O(N^2 \times M)$。

空间复杂度：$O(N + M)$。

我们继续思考，如何优化。

我们与其还原 $A$ 序列，不如到 $A$ 中序列中选择一个位置 $x$，并在 $A_i = X_j$ 时计算 $A_x$，那么 $A_x$ 的最大出现数量就是答案，显然这个位置是 $1$。

推式子得以下结论：

$$A_1 = (\sum _{j = 1}^{j = i - 1} S_{j} \times (-1)^{j + 1}) + A_i \times (-1)^i$$

思路出来了：

枚举 $A_i = X_j$，然后计算 $A_1$，提示 $(\sum _{j = 1}^{j = i - 1} S_{j} \times (-1)^{j + 1})$ 是可以预处理的。

时空复杂度：

时间复杂度：$O(N \times M \log_{2} (N \times M))$。

空间复杂度：$O(N \times M \log_{2} (N \times M))$。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 5;

ll s[N];
int n, m, ans;
map<ll, int> mp;
pair<int, int> a[N];

int main(){
  cin >> n >> m;
  for(int i = 1; i < n; i++){
    cin >> a[i].first;
    s[i + 1] = s[i] + (i % 2 == 1 ? 1 : -1) * a[i].first;
  }
  for(int i = 1; i <= m; i++){
    cin >> a[i].second;
  }
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      mp[s[i] + (i % 2 == 0 ? -1 : 1) * a[j].second]++;
      ans = max(ans, mp[s[i] + (i % 2 == 0 ? -1 : 1) * a[j].second]);
    }
  }
  cout << ans;
  return 0;
}

```

---

## 作者：__YSC__ (赞：1)

# 题目描述

给定长度为 $N-1$ 的序列 $S$，和长度为 $M$ 的序列 $X$。有一个长度为 $N$ 的序列 $A$ 满足：

- 对于每个 $1 \le i < N$ 都满足 $A_i + A_{i+1}=S_i$。

求 $A$ 中最多有多少个 $A_i \in X$。

# 思路

可以先推出这些式子：

$$
\begin{cases}
A_1=S_1-A_2\\
A_2=S_1-A_1\\
A_3=S_2-A_2\\
\vdots\\
A_N=S_{N-1}-A_{N-1}\\
\end{cases}
$$

$$\Downarrow$$

$$
\begin{cases}
A_1=S_1-A_2\\
A_2=S_1-A_1\\
A_3=S_2-S_1+A_1\\
\ \ \ \ \ \ \ \vdots\\
A_N=S_{N-1}-S_{N-2}+S_{N-3}-\dots+(-1)^N\times A_1\\
\end{cases}
$$

$$\Downarrow$$

$$
A_1=S_1-A_2=S_1-S_2+A_3=\dots=S_1-S_2+S_3-\dots+(-1)^N\times A_N
$$

可以发现，当我们知道 $A$ 中的一项时我们就能推出 $A_1$，并且 $A_1$ 相同，则整个 $A$ 相同。所以我们可以用 $A_1$ 表示一种序列 $A$，然后枚举每一个位置 $i$ 上为 $X_j$，并统计答案。其中使用前缀和优化，用 `map` 维护答案。

空间复杂度 $O(N)$，时间复杂度 $O(NM \log (NM))$。

## 细节

无。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const long long MAXN = 100001;

long long n, m, s[MAXN], x[MAXN], sum[MAXN], ans;
map<long long, long long> mp;

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(long long i = 1; i < n; ++i) {
    cin >> s[i];
  }
  for(long long i = 1; i <= m; ++i) {
    cin >> x[i];
  }
  for(long long i = 1; i < n; ++i) {
    sum[i] = sum[i - 1] + (i % 2 ? 1ll : -1ll) * s[i];
  }
  for(long long i = 1; i <= n; ++i) {
    for(long long j = 1; j <= m; ++j) {
      mp[sum[i - 1] + (i % 2 ? 1ll : -1ll) * x[j]]++;
    }
  }
  for(pair<long long, long long> p : mp) {
    ans = max(ans, p.second);
  }
  cout << ans;
  return 0;
}

```

---

## 作者：AlicX (赞：0)

## Solution 

不妨先令 $a_1=0$，算出初始数组 $a$。

然后考虑 $a_1$ 增大 $x$ 对后续 $a_i$ 的影响，不难发现 $a_2$ 会减少 $x$，则 $a_3$ 会增加 $x$……

扩展一下就是 $i$ 是奇数会增加 $x$，$i$ 是偶数会减少 $x$。于是算出 $a_i$ 与 $x_j$ 的差值 $p$，如果 $i$ 是奇数就在桶中存入一个 $p$，否则存入 $-p$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2e5+10,M=12; 
int n,m; 
int a[N]; 
int s[N],x[M]; 
map<int,int> mp; 
signed main(){ 
	vector<int> vec; a[1]=0; 
	n=read(),m=read(); int ans=0; 
	for(int i=1;i<n;i++) s[i]=read(),a[i+1]=s[i]-a[i]; 
	for(int i=1;i<=m;i++){ 
		x[i]=read(); 
		for(int j=1;j<=n;j++){ 
			if(j&1) mp[a[j]-x[i]]++;
			else mp[x[i]-a[j]]++; 
		} 
	} for(auto u:mp) ans=max(ans,u.y); 
	printf("%lld\n",ans); return 0; 
} 
```

---

