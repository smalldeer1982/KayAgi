# [ABC017D] サプリメント

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc017/tasks/abc017_4

健康志向の高橋君は通販で購入したサプリメントを摂取することにした。

サプリメントは $ N $ 個あり、$ 1 $ から $ N $ まで番号が付けられている。

また、サプリメントの味は $ M $ 種類あり、$ 1 $ から $ M $ まで番号が付けられている。サプリメント $ i\ (1\ ≦\ i\ ≦\ N) $ の味は $ f_i\ (1\ ≦\ f_i\ ≦\ M) $ である。

高橋君はサプリメントを番号順に複数日かけて摂取する予定である。高橋君はサボらないように、サプリメントが $ 1 $ つ以上残っている場合はその日中に必ず $ 1 $ つ以上サプリメントを摂取しなければならないという規則を定めた。

高橋君は強靭な肉体を持っているため、$ 1 $ 日にどれだけサプリメントを摂取しても大丈夫だが、同じ味には飽きてしまうので、同じ日に同じ味のサプリメントを $ 2 $ つ以上摂取することはできない。

高橋君は、サプリメントの摂取方法の是非について吟味するため、このような条件下で全部で何通りの摂取方法があるかを知りたい。

ここで $ 2 $ つの摂取方法についてそれらが違うというのは、ある日について摂取したサプリメントの番号の組み合わせが異なることを定義する。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ N\ ≦\ 5,000 $ かつ $ M\ ≦\ 5,000 $ を満たすデータセット $ 1 $ に正解した場合は、上記とは別に $ 30 $ 点が与えられる。
- 追加制約のないデータセット $ 2 $ に正解した場合は、上記とは別に $ 70 $ 点が与えられる。

### Sample Explanation 1

以下の $ 5 $ 通りが考えられます。 $ 1 $ 日目 $ 2 $ 日目 $ 3 $ 日目 $ 4 $ 日目 $ 5 $ 日目 サプリメント $ 1 $ サプリメント $ 2 $ サプリメント $ 3 $ サプリメント $ 4 $ サプリメント $ 5 $ サプリメント $ 1 $ サプリメント $ 2 $ サプリメント $ 3,4 $ サプリメント $ 5 $ なし サプリメント $ 1 $ サプリメント $ 2,3 $ サプリメント $ 4 $ サプリメント $ 5 $ なし サプリメント $ 1,2 $ サプリメント $ 3 $ サプリメント $ 4 $ サプリメント $ 5 $ なし サプリメント $ 1,2 $ サプリメント $ 3,4 $ サプリメント $ 5 $ なし なし

### Sample Explanation 2

どのように食べても飽きません。

## 样例 #1

### 输入

```
5 2
1
2
1
2
2```

### 输出

```
5```

## 样例 #2

### 输入

```
6 6
1
2
3
4
5
6```

### 输出

```
32```

# 题解

## 作者：lottle1212 (赞：13)

# [原题传送们](https://www.luogu.com.cn/problem/AT_abc017_4)

## Part 0

- 给定一个长度为 $N(1 \leq N \leq 10^{5})$ 的序列 $a$。
- 其中 $a_i(1 \leq i \leq N) \in 1 \sim M (1 \leq M \leq 10^{5})$。
- 求出将 $a$ 划分成若干个子串的方案数，其中子串内任意元素互不相同。注意，答案要对 $10^9 + 7$ 取模。

## Part 1

容易看出，此题可以由递推 $\text{DP}$ 解决。我们用 $dp_i$ 表示选择前 $i$ 个数的方案数。

首先，我们确定边界值 $dp_0 = dp_1 = 1$。

然后，我们用 $l$ 表示满足从 $l \sim i$ 间所有元素各不相同的最小值。当 $l - 1 \leq j < i$ 时，我们可以把序列 $a$ 分成 $1 \sim j$ 和 $j + 1 \sim i$ 这两部分，$dp_j$ 表示划分 $a_{1 \sim j}$ 的方案数，$a_{j + 1 \sim i}$ 是这一次选的数。根据 $l$ 的定义可得，$a_k (j \leq k \leq i)$ 各不相同。

接下来就很容易地得出动态转移方程：

$$dp_i = \sum_{j = l - 1}^{i - 1}{dp_j}$$

此时，单点转移的时间复杂度为 $O(N)$，总复杂度为 $O(N^2)$。

## Part 2

接下来考虑优化。

观察转移方程易知，$l$ 具有递增性。因此，我们可以利用尺取法来找到满足要求的 $l$。而求和的部分，我们可以用前缀来优化。设：

$$sum_i = \sum_{j = 0}^{i} {dp_j}$$

则：

$$dp_i = sum_{i - 1} - sum_{l - 2}$$

时间复杂度 $O(n)$。

然后，我们就可以愉快地开始写代码啦！

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;
const int mxn = 1e5;
const int N = mxn + 10;
ll n, m, dp[N], sum[N], a[N], vis[N], cnt, l;
void add(int x) { if(vis[x] == 1) ++ cnt; ++ vis[x]; }//插入
void del(int x) { if(vis[x] == 2) -- cnt; -- vis[x]; }//删除
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; ++ i) cin >> a[i];
	dp[0] = dp[1] = sum[0] = 1, sum[1] = 2, l = 1, vis[a[1]] = 1;//vis[i] 表示数字 i 出现的次数
	for(int i = 2; i <= n; ++ i) {
		add(a[i]); while(cnt && l <= i) del(a[l ++]); //尺取
		dp[i] = ((sum[i - 1] - sum[l - 2]) % mod + mod) % mod;//动态转移
		sum[i] = ((sum[i - 1] + dp[i]) % mod + mod) % mod;//更新前缀
	}
	cout << dp[n] << '\n';
	return 0;
}
```


---

## 作者：elonzhang (赞：2)

# [题目传送门](https://atcoder.jp/contests/abc017/tasks/abc017_4)

## 题意
对于一串由数字构成的序列，将其分割成若干段，且每一段内的每个数字最多只有一个。求其方案数对 $10^9+7$ 取模后的结果。

## 思路
考虑使用 DP 进行求解。设 $dp_i$ 为只使用前 $i$ 个数字的方案数。那么怎么求呢？我们发现只要从左端点 $l \sim i$ 内没有重复的数字，就可以加上 $dp_{last-1}$ 的方案数，每次循环都向前搜索的暴力时间复杂度就是 $O(n^2)$。

## 优化
简单观察一下就会发现，左端点 $l$ 是单调递增且易求的。那我们就可以考虑用一个变量 $last$ 来存储左端点。每次循环都用 $f$ 数组记录一下 $last \sim i$ 这段区间内是否有重复的数字，如果有就使 $last$ 加一。最后我们再用前缀和数组 $sum$ 来优化，就可以让整体时间复杂度仅为 $O(n)$。

---

### 初始化
`dp[0]=dp[1]=sum[0]=f[a[1]]=1,sum[1]=2`

## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
#pragma G++ optimize(2,3,"Ofast","inline")
#define int long long
#define double long double
#define endl '\n'
const int N=114514,mod=1e9+7;
int n,m,ans,cnt,sum[N]={1,2},last=1,a[N],dp[N]={1,1},f[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i<=n;i++) cin >> a[i];
	f[a[1]]++;
	for(int i = 2;i<=n;i++){
		cnt+=(++f[a[i]]==2);
		while(cnt&&last<=i) cnt-=(--f[a[last++]]==1);//尺取
		dp[i]=sum[i-1]-sum[last-2];dp[i]=(dp[i]%mod+mod)%mod;//每一步都取模防止爆 long long
		sum[i]=sum[i-1]+dp[i];sum[i]=(sum[i]%mod+mod)%mod;//每一步都取模防止爆 long long
	}
	cout << dp[n] << endl;
	return 0;
}
```

---

## 作者：SalN (赞：2)

[link](https://www.luogu.com.cn/problem/AT_abc017_4)

----

### 题目大意

给定长度为 $n$ 的序列 $a_1,a_2,...,a_n$，种类数 $m$，其中 $a_i\in[1,m]$

现在我们要把 $a$ 分成若干段，要求每段中 $a_i$ 的值各不相同且每段不为空

求总的方案数对 $1000000007$ 取模的结果

其中 $1\leq n,m \leq 10^5$

----

###  解题思路

计数类问题，考虑 DP

设计状态，$f[i]$ 表示在 $a1,a2,...,a_i$ 中的方案数

我们考虑从 $j$ 到 $i$ 做成子段，于是乎

$f[i]=\sum{f[j-1]}$，其中 $a_j,...,a_i$ 不重复

然后呢，我们发现，这个 $j$ 的取值肯定是一个区间

因为假设 $j'$ 不行，那么 $j'-1$ 肯定不行

于是乎我们前缀和，转移就是 $O(1)$ 的了

令 $sum$ 为 $f$ 的前缀和，$a_j$ 为最后一个不符合的

那么 $f[i]=sum[i-1]-sum[j-2]$



那么 $j$ 怎么取呢，我们不断加颜色 $j$ 定是单调的，所以我们可以尺取

而想一下，会发现，每一次都是上一个跟 $a_x$ 相等的 $a_y$ 中的 $y$ 去更新了 $j$，因为 $j$ 单调，我们也可以记录上一个跟 $a_i$ 相等的位置不断取 $\max$ 来求 $j$

----

### code

尺取做法

```cpp
#include<bits/stdc++.h>
#define MN 100100
#define P 1000000007

using namespace std;

int n, m, a[MN];
int f[MN], sum[MN];
int zs[MN], cnt, pos;

signed main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i)
		scanf("%d", a+i);
	f[0]=f[1]=sum[0]=pos=1;
	zs[a[1]]=1, sum[1]=2;
	for(int i=2; i<=n; ++i) {
		if(++zs[a[i]]==2) cnt++; 
		while(pos<=i&&cnt)
			cnt-=(--zs[a[pos++]]==1);
		f[i]=sum[i-1]-sum[pos-2];
		f[i]=(f[i]%P+P)%P;
		sum[i]=sum[i-1]+f[i];
		sum[i]=(sum[i]%P+P)%P;
	}
	printf("%d\n", f[n]);
	return 0;
}
```
另一种做法

```cpp
#include<bits/stdc++.h>
#define MN 100100
#define P 1000000007

using namespace std;

int n, m, a[MN], lst[MN];
int f[MN], sum[MN], p;

signed main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; ++i)
		scanf("%d", a+i);
	sum[0]=1;
	for(int i=1; i<=n; ++i) {
		p=max(p,lst[a[i]]), lst[a[i]]=i;
		int qwq=(p==0)?0:sum[p-1];
		f[i]=(sum[i-1]-qwq+P)%P;
		sum[i]=(sum[i-1]+f[i])%P;
	}
	printf("%d\n", f[n]);
	return 0;
}
```


---

## 作者：myster1ous (赞：1)

## Statement

**注意：题面中的 $1$ 个以上是指 $\geqslant 1$ 个。**

形式化题意：给定一个长度为 $n$，值域为 $[1, m]$ 的序列 $a_1, \dots, a_n$。

求问，有多少种把 $a_1, \dots, a_n$ 划分为若干其中不存在重复元素的子串的方案。

数据范围：$1 \leqslant n \leqslant 10^5$。

## Solution

$1 \leqslant n \leqslant 10^5$ 不难想到线性 $\text{dp}$。

我们定义：$\text{dp}_i$ 就是划分完 $1 \sim i$ 的方案数。

边界条件：$\text{dp}_0 = 1$。\
答案：$\text{dp}_n$。\
转移方式：算出 $\text{dp}_i$ 后，枚举下一个子串 $[i, j]$，如果 $[i, j]$ 中没有重复元素，那么 $\text{dp}_j \gets \text{dp}_j + \text{dp}_i$。

不难发现，上面这个算法转移是 $\mathcal{O}(n^2)$ 的，对于本题 $1 \leq n \leq 10^5$ 的数据无法通过，因此考虑优化。

首先，如果 $[i, k]$ 中已经有重复元素，那么 $[i, k'](k' > k)$ 已经没有必要考虑了，所以我们只需要找到第一个有重复元素的 $[i, k]$，然后我们记录 $\text{right}_i = k$。

原先的转移方式变成了：$\text{dp}_j \gets \text{dp}_i + \text{dp}_j (j \in [i, \text{right}_i])$。

然后，$\text{dp}_j$ 的区间修改可以用差分来解决，然后 $\text{right}_i$ 不难发现一定大于 $\text{right}_{i - 1}$，双指针即可，这样这个算法就成功被我们优化成了 $\mathcal{O}(n)$，代码如下：

## Code

```cpp
// LUOGU_RID: 194824250
#include <bits/stdc++.h>
#define int long long

const int maxn = 100010;
const int mod = 1000000007LL;

int n, m, a[maxn], f[maxn];

signed main() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	f[0] = 1;
	f[1] = mod - 1;
	int prefixsum = 0, right = 0;
	std::unordered_set<int> set;
	set.insert(0);
	for (int i = 0; i <= n; i++) {
		set.erase(a[i]);
		while (!set.count(a[right + 1])) {
			set.insert(a[right + 1]);
			right += 1;
		} 
		prefixsum = (prefixsum + f[i]) % mod;
		f[i + 1] = (f[i + 1] + prefixsum) % mod;
		f[right + 1] = ((f[right + 1] - prefixsum) % mod + mod) % mod;
	} std::cout << std::accumulate(f, f + n + 1, 0LL) % mod << "\n";
	return 0;
}
```

---

## 作者：_Kenma_ (赞：1)

## 前言

简单题。但是我假了一回。

## 思路分析

设 $f_i$ 表示考虑到第 $i$ 个位置的方案数，则有转移：

$$f_i=\sum_{j=l-1}^{i-1} f_j$$

其中 $l$ 是满足 $[l,i]$ 区间没有重复颜色的最小值。

不难发现 $l$ 可以在 DP 的过程中用双指针求出。

然后再前缀和优化一下，可以做到 $O(n)$。

感觉还没开始就结束了……

## 代码实现

```cpp

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,tot,l,lst[100005],a[100005],cnt[100005],f[100005],sum[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	f[0]=1;
	sum[0]=1;
	f[1]=1;
	sum[1]=2;
	l=1;
	cnt[a[1]]=1;
	for(int i=2;i<=n;i++){
	    cnt[a[i]]++;
		if(cnt[a[i]]==2) tot++;
		while(l<=i && tot){
			cnt[a[l]]--;
			if(cnt[a[l]]==1) tot--;
			l++;
		}
		f[i]=((sum[i-1]-(l>=2?sum[l-2]:0))%mod+mod)%mod;
		sum[i]=(sum[i-1]+f[i])%mod;
	}
	cout<<f[n]<<'\n';
	return 0;
}

```

---

## 作者：porse114514 (赞：0)

# AT_abc017_4 [ABC017D] サプリメント 题解
## 题目大意
给定长度为 $n\,(1\le n\le 10^5)$ 的数组，要从位置 $1$ 跳若干次到位置 $n + 1$。每次至少跳一格，而且每次跳的区间（包含起终点）不能有重复数字。求方案数。（**请理解此段，否则后面可能比较难懂**）

## 思路
这种只往一个方向跳，求方案数的题 $90\%$ 都是 dp。
令 $endd_i$ 为区间 $[i,j]$ 满足没有重复数字的 $j$ 的最大值，$dp_i$ 为从 $i$ 跳到 $n + 1$ 的方案数。

则：
$$
dp[i] = \sum_{j = i + 1}^{endd_i+1}dp_j
$$

这个东西使用前缀和很好维护，那么我们的问题就是如何求 $endd_i$。

~~欸，我会，线段树！~~

我们其实可以直接用双指针 $O(n)$ 维护，具体地，我么先预处理表示 $a_i$ 上一次出现的下标 $lastt_i$，然后开始双指针：
1. 将 $r$ 往后移
2. 当当前的 $lastt_r\ge l$ 时， 将 $endd_l$ 到 $endd_{lastt_r}$ 都赋值为 $r - 1$，将 $l$ 赋值为 $lastt_r + 1$

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100010, modd = 1e9 + 7; // 不要忘记取模！

int n, m, a[maxn];
int dp[maxn], endd[maxn];
int las[maxn], lastt[maxn]; // las[i] 表示 i 上次出现的位置，laastt[i] 表示 a[i] 上次出现的位置
int l, r; // 双指针
int sum[maxn]; // 前缀和

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i], lastt[i] = las[a[i]], las[a[i]] = i; // 求 lastt
	l = r = 1;
	while (1) {
		r++;
		if (lastt[t] >= l) { // 如果当前有重复
			while (1) {
				endd[l] = r - 1;
				l++;
				if (l == lastt[r] + 1) break;
			}
		}
		if (r == n) break;
	}
	while (1) {
		endd[l++] = n;
		if (l == n + 1) break;
	} // 别忘了把后面无重复的设为 n
	dp[n] = 1;
	dp[n + 1] = 1;
	sum[n + 1] = 1;
	sum[n + 2] = 0;
	sum[n] = dp[n] + 1;
	for (int i = n - 1; i > 0; i--) {
		dp[i] = (sum[i + 1] - sum[endd[i] + 2]) % modd;
		sum[i] = (sum[i + 1] + dp[i]) % modd;
	} // dp 转移
	cout << (dp[1] + modd) % modd << '\n';
	
	return 0;
}
```

---

## 作者：codwarm (赞：0)

[题目传送门~](https://www.luogu.com.cn/problem/AT_abc017_4)

一道 DP 前缀和优化好题。

## 题目分析

首先，朴素 DP 非常好想。可以从后向前考虑，设 $f_i$ 表示从第 $i$ 个补品开始的摄取方法数。

摄取一个补品：$f_i = f_{i+1}$

摄取两个补品：$f_i = f_{i+2}$

以此类推。

则转移方程为：
$$f_i = f_{i+1} + f_{i+2} + \dots + f_{j}$$

这里的 $j$ 指 $i$ 向后**最远能取到的保证不重复的数**，这一步可以用 unordered_map 判重。

## 朴素 DP 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005,mod = 1e9+7;
int n,m,a[N],dp[N];
int main()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++) cin >> a[i];
	dp[n+1] = 1;
	for (int i = n;i >= 1;i--)
	{
		dp[i] = dp[i+1];
		unordered_map<int,bool> mp;//map判重
		mp[a[i]] = 1;
		for (int j = i+1;j <= n;j++)
		{
			if (mp[a[j]]) break;
			dp[i] += dp[j+1] % mod,dp[i] %= mod;
			mp[a[j]] = 1;
		}
	}
	cout << dp[1] << endl;
	return 0;
} 
```

## DP 优化
朴素 DP 时间复杂度 $O(n^2)$，于是考虑优化。

朴素 DP 是 $O(n)$ 枚举查找 $j$ 的位置，那么可以预处理每个 $i$ 对应 $j$ 的位置，再通过前缀和求出 $f_{i+1} + f_{i+2} + \dots + f_{j}$ 的值，就可以优化状态转移时间复杂度为 $O(1)$。

最终复杂度为 $O(n)$。

## 预处理的方法

怎么求出每个 $i$ 对应的 $j$ 的位置呢？我们发现 $j$ 的位置是随着 $i$ 单调递增的，因为 $i-1$ 对应的 $j$ 对于 $i$ 来说肯定也是可行的。

所以很容易能想到使用双指针算法，时间复杂度 $O(n)$。

具体实现见代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100005,mod = 1e9+7;
int n,m,a[N];
int dp[N],bk[N],sum[N];
unordered_map<int,int > mp;	
int main()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++) cin >> a[i];
	for (int i = 1,j = i;i <= n;i++) //双指针算法
	{
		while (j <= n && !mp[a[j]]) mp[a[j]]++,j++;
		bk[i] = j-1; //存储每个i最远能走到的数
		mp[a[i]]--;
	} 
	dp[n+1] = sum[n+1] = 1;
	for (int i = n;i >= 1;i--)
	{
		//dp[i] = dp[i+1] + dp[i+2] + ... + dp[bk[i] + 1]
		dp[i] =( sum[i+1]-sum[bk[i] + 2] + mod) % mod;
		sum[i] = (sum[i+1] + dp[i]) % mod;
	}
	cout << dp[1] << endl;
	return 0;
} 
```



---

## 作者：_lyx111 (赞：0)

# [ABC017D] サプリメント

[link](https://atcoder.jp/contests/abc017/tasks/abc017_4?lang=en)

## 题意

给定一个长度为 $n$ 的序列 $f_1,f_2,\dots,f_n$，种类数为 $m$，满足 $\forall\ 1\le i\le n,1\le f_i\le m$。

将序列 $\{f_n\}$ 分成若干段，满足每段内的 $f_i$ 互不相同，问分割方案总数，对 $10^9+7$ 取模。

数据范围：$1\le n,m\le 10^5$。

时间限制：$3\ \text{s}$，空间限制：$256\ \text{MB}$。

## 分析

考虑 dp，设 $dp_i$ 为 $f_1,f_2,\dots,f_i$ 的答案。

那么显然有转移：

$$dp_i=\sum_{j=l}^{i-1} dp_{j-1}$$

其中，$l$ 是满足 $f_l,\dots,f_i$ 互不相同的 $l$ 中的最小值。

考虑前缀和，设 $sum_i=\sum_{j=1}^i dp_j$，则转移转化为：

$$dp_i=sum_{i-1}-sum_{l-2}$$

考虑如何快速求出 $l$，显然的，当 $i$ 单调递增时，$l$ 也会单调递增，考虑指针法（好像叫什么尺取法？忘记了）。

设 $pre_i$ 为满足 $f_i=f_j$ 和 $1\le j\le i$ 的最大的 $j$，如果不存在这样的 $j$，则钦定 $pre_i=0$，这个可以用桶来计算。

那么每次只需 $\max(l,pre_i+1)\to l$ 即可（想想为什么，挺显然的），那么我们得到了 $l$ 之后就可以直接转移了。

## 细节

1. 注意指针 $l=1$ 的情况，要特殊判断，否则会出现访问 $sum_{-1}$ 的情况；

2. 输出答案的时候一定要再输出一个换行，蒟蒻就因为这个瞪了好久。

3. 要初始化 $dp_0=sum_0=dp_1=1,sum_1=2$。

## 代码

~~~cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10,mod=1e9+7;
int n,m;
int f[MAXN];
int bar[MAXN],pre[MAXN]; //bar 是桶 
int dp[MAXN],sum[MAXN];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&f[i]);
	for(int i=1;i<=n;i++)
	{
		pre[i]=bar[f[i]];
		bar[f[i]]=i;
	}
	dp[0]=sum[0]=dp[1]=1;
	sum[1]=2;
	int l=1;
	for(int i=2;i<=n;i++)
	{
		l=max(l,pre[i]+1);
		if(l==1)
			dp[i]=sum[i-1];
		else
			dp[i]=(sum[i-1]-sum[l-2]+mod)%mod;
		sum[i]=(sum[i-1]+dp[i])%mod;
	}
	printf("%d\n",dp[n]);
	return 0;
}
~~~

[AC记录](https://atcoder.jp/contests/abc017/submissions/37898099)

## 写在最后

蒟蒻很菜，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正。

---

## 作者：Ming_dao (赞：0)

题目的意思是，给定这 $N$ 个物品的顺序，但可以将部分物品在一天内吃完，同一天吃的东西内不考虑顺序。求满足同一天不吃同种物品的情况下，可以有多少种吃法（每天至少吃一个）。

本题貌似找不到什么性质规律，不妨大胆假设DP。

设 $f_i$ 表示前 $i$ 个食物的所有划分情况。发现，我们把问题分成了两部分，一部分是已知的前 $i$ 个食物，另一部分就是现在这天该吃的食物，最多能吃多少呢——吃到当天恰好多吃一个，就会多出一种同种口味的食物。

**注意**，同种口味的食物不一定是最后吃的食物的上一个同类食物。例如：$3~1~2~1~2~1$。

于是我们就列出了状态转移方程：
$$
f_i=\sum_{j=l}^{i-1}dp_j
$$
此处的 $l$ 为出现的上一个同种食物所在序列中的位置。

显然的前缀和优化。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int Mod=1e9+7;
const int maxn=1e5+10;
int a[maxn],nw[maxn],pre[maxn],vis[maxn];

int f[maxn],sum[maxn];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];pre[i]=nw[a[i]];nw[a[i]]=i;
	}
	f[0]=f[1]=sum[0]=1;sum[1]=2;
	vis[a[1]]=1;
	for(int i=2,l=0;i<=n;i++){
		if(vis[a[i]]){
			for(int j=l;j<=pre[i];j++)vis[a[j]]--;
			l=pre[i]+1;
		}
		vis[a[i]]++;
		if(l==0)f[i]=sum[i-1]%Mod;
		else f[i]=(sum[i-1]-sum[l-2]+Mod)%Mod;
		sum[i]=(sum[i-1]+f[i])%Mod;
	}
	cout<<f[n]<<'\n';
	return 0;
}
```

需注意一个点，$l$ 在移动的时候需要多移动一格，是为了防止再次移动时把 vis 数组多减去一遍。

---

