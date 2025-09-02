# [ABC393E] GCD of Subset

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc393/tasks/abc393_e

给定一个长度为 $ N $ 的数列 $ A=(A_1,A_2,\dots,A_N) $ 和一个不超过 $ N $ 的正整数 $ K $。  
对于每个 $ i=1,2,\dots,N $，请解决以下问题：

- 从 $ A $ 中选出包含 $ A_i $ 的 $ K $ 个元素时，求这些元素的最大公约数 (GCD) 可能达到的最大值。

## 说明/提示

### 约束条件

- $ 1 \leq K \leq N \leq 1.2 \times 10^6 $
- $ 1 \leq A_i \leq 10^6 $
- 输入中所有值均为整数

### 样例解释 1

- 当 $ i=1 $ 时，选择 $ A_1 $ 和 $ A_3 $，最大公约数为 $\gcd(\{3, 6\}) = 3$，这是最大值。
- 当 $ i=2 $ 时，选择 $ A_2 $ 和 $ A_5 $，最大公约数为 $\gcd(\{4, 12\}) = 4$，这是最大值。
- 当 $ i=3 $ 时，选择 $ A_3 $ 和 $ A_5 $，最大公约数为 $\gcd(\{6, 12\}) = 6$，这是最大值。
- 当 $ i=4 $ 时，选择 $ A_4 $ 和 $ A_2 $，最大公约数为 $\gcd(\{7, 4\}) = 1$，这是最大值。
- 当 $ i=5 $ 时，选择 $ A_5 $ 和 $ A_3 $，最大公约数为 $\gcd(\{12, 6\}) = 6$，这是最大值。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5 2
3 4 6 7 12```

### 输出

```
3
4
6
1
6```

## 样例 #2

### 输入

```
3 3
6 10 15```

### 输出

```
1
1
1```

## 样例 #3

### 输入

```
10 3
414003 854320 485570 52740 833292 625990 909680 885153 435420 221663```

### 输出

```
59
590
590
879
879
590
20
879
590
59```

# 题解

## 作者：gesong (赞：12)

题目传送门：[[ABC393E] GCD of Subset](https://www.luogu.com.cn/problem/AT_abc393_e)。
# 思路

我们发现值域的大小仅为 $10^6$ 我们考虑枚举答案，对于答案 $x$ 我们只会影响到 $x$ 的倍数的位置，我们记录一下这些位置的 $a$ 数组个数，如果个数不小于 $k$ 那么这个点的位置就可以被 $x$ 更新。

最后输出 $a_i$ 的对应的值域位置的答案即可，具体的细节可以查看代码。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,M=1.2e6+10;
int anss[N],a[M],vis[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	int n=read(),k=read();
	for (int i=1;i<=n;i++) a[i]=read(),vis[a[i]]++;//用桶记录每个位置的数组出现次数
	for (int i=1;i<N;i++){
		int sum=0;
		for (int j=i;j<N;j+=i) sum+=vis[j];//记录个数
		if (sum>=k){
			for (int j=i;j<N;j+=i) anss[j]=max(anss[j],i);//如果满足，更新答案
		}
	}//调和级数枚举
	for (int i=1;i<=n;i++) printf("%lld\n",anss[a[i]]);
    return 0;
}
//AtCoder Beginner Contest 393 RP++
//AtCoder Beginner Contest 393 RP++
//AtCoder Beginner Contest 393 RP++
//AtCoder Beginner Contest 393 RP++
//AtCoder Beginner Contest 393 RP++

```

---

## 作者：Lovely_yhb (赞：6)

### 题意

给定一个长度为 $n$ 的序列 $a$ 和一个整数 $k$，对于每个 $i$，求出必须选 $a_i$ 的情况下选 $k$ 的数的最大 $\gcd$。

### 思路

首先思考原始问题，在长度为 $n$ 的序列中选 $k$ 个数的最大 $\gcd$。这是有原题的。[P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)。

做法是：枚举每个数的因子，把它加到桶里。从大到小枚举所有因子，如果某个数出现次数大于等于 $k$ 就是答案。

但这个题不能枚举因子，因为 $10^6$ 的数据随便把 $O(n\sqrt n)$ 的复杂度卡掉。

这个题是这样统计因子的：设 $t_i$ 表示 $i$ 在 $a$ 中出现的次数，$m$ 表示 $\max(a_1,a_2,\dots,a_n)$，$f_x$ 表示 $x$ 是 $a$ 中 $f_x$ 个数的因子。枚举每个 $x$，$\displaystyle f_x=\sum^{K\times x\le m}_{K=1}t_K$。

答案这样统计：设 $ans_{i}$ 表示必须选 $i$ 这个数的答案。从大到小枚举每个数 $x$，如果它作为因子的次数大于 $k$，那么 $x,x\times2,x\times3,\dots$ 的答案就都是 $x$。

最后的答案，输出 $ans_{a_i}$ 即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,k,a[1200005],t[N],f[N],ans[N],m;
signed main() {
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>k;
	for(int i=1; i<=n; i++) cin>>a[i],t[a[i]]++,m=max(m,a[i]);
	for(int i=1; i<=m; i++) for(int j=i; j<=m; j+=i) f[i]+=t[j];
	for(int i=m; i>=1; i--)
		if(f[i]>=k)
			for(int j=i; j<=m; j+=i)
				if(!ans[j]) ans[j]=i;
	for(int i=1; i<=n; i++) cout<<ans[a[i]]<<'\n';
	return 0;
}
```

---

## 作者：zengziqvan (赞：4)

注意到值域很小。

于是考虑预处理出值域内所有数字能够被原序列中多少个数字整除。

这个东西可以方便的用桶统计。

具体的，记 $f_i$ 表示原序列中有多少个 $i$ 的倍数。

有转移：

$$
f_i\gets \sum_{k\in \mathbb{N+},k\times i\le V} f_{k\times i} 
$$

初值是 $f_i\gets\sum_{j=1}^n [a_j=i]$.

同时可以预处理所有数字的约数。

上述两者复杂度均为 $O(V\log V)$，其中 $V$ 为值域。

对于第 $i$ 个数字，自大而小的枚举其所有的约数，并判断是否有 $f_i\ge k$ 即可。

总复杂度 $O(n\times d(V)+V\log V)$，其中 $d(i)$ 表示 $1\sim i$ 中约数最多的数字的约数个数。本题大概是 $240$。

[submissions](https://atcoder.jp/contests/abc393/submissions/62790726)

---

## 作者：Drifty (赞：4)

### Solution

下文记 $M$ 为 $\max\{A_i\}$。

注意到值域很小，因此我们不妨将 $x\in [1, M]$ 的倍数的个数预处理出来，记录为 $\text{cnt}_x$。

然后统计答案时枚举这个公约数 $d\in [1, M]$ 如果这个公约数的 $\text{cnt}_x\ge K$，那么说明对于这个 $d$ 的所有倍数，随便从当中选 $K$ 个，最终得到的最大公约数至少为 $d$，这也就意味着对于所有 $d$ 的倍数，答案至少为 $d$。

我们如何保证答案最大？很简单，倒序枚举 $d$ 即可。

时间复杂度为 $\mathcal{O}(M\ln M + n)$，可以通过。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int N = 1.2e6 + 7;
int n, k, a[N];

int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < n; i ++) cin >> a[i];

    int m = *max_element(a, a + n);

    vector <int> pre (m + 1, 0), cnt (m + 1, 0), ans (m + 1, 0);

    for (int i = 0; i < n; i ++) pre[a[i]] ++;

    for (int i = 1; i <= m; i ++) {
        for (int j = i; j <= m; j += i) cnt[i] += pre[j];
    }
    for (int d = m; d; d --) {
        if (cnt[d] >= k) for (int x = d; x <= m; x += d) {
            if (ans[x] == 0) ans[x] = d;
        }
    }

    for (int i = 0; i < n; i ++) cout << ans[a[i]] << '\n';
    return 0;
}
```

---

## 作者：chenxi2009 (赞：2)

## 思路
注意到 $A_i\le10^6$，$A_i$ 的因子也不会超过 $10^6$，如果我们预先知道每个 $A_i$ 的因子序列，我们就可以统计每个数是多少个 $A_i$ 的因子。\
显然 $A_i$ 对应的答案一定是它的因子，寻找答案就可以从大到小遍历 $A_i$ 的因数，遇到的第一个被标记达到 $K$ 次的因数就是答案。

怎么得到 $A_i$ 的因数？当你发现 $O(N\sqrt{\max A_i})$ 的算法过不去的时候，~~我的超级智慧告诉我~~你就应该想起调和级数预处理了。

对于每一个数 $1\le i\le10^6$，把它推入它的 $10^6$ 以内的倍数的因数序列里。令 $M\leftarrow\max A_i$，这样的操作每一个数分别被推入了 $M,\left\lfloor\frac{M}{2}\right\rfloor,\left\lfloor\frac{M}{3}\right\rfloor,\cdots,\frac{M}{M}$ 次，我们知道 $\sum_{i=1}^N\frac{N}{i}\approx N\log N$，因此这一步的复杂度为 $O(M\log M)$。

那后面依次遍历标记每一个数的因子然后再次遍历找答案会不会超时？这和因子序列的长度有关。打表发现 $10^6$ 以内的数最多拥有 $240$ 个因数，这个数是 $720720$。令 $f(x)$ 表示 $x$ 以内的数最多拥有的因数个数，则总时间复杂度为 $O(A_i\log A_i+Nf(A_i))$。

这个数字在 $3\times10^8$ 左右，在 AtCoder 的机子下并不会超时。
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,k,a[2000000],cnt[2000000],ans;
vector<int>v[2000000];//v_i 升序保存了 i 的所有因数 
int main(){
	for(int i = 1;i <= 1000000;i ++) for(int j = 1;i * j <= 1000000;j ++) v[i * j].push_back(i);//调和级数预处理因数 
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
	for(int i = 1;i <= n;i ++) for(auto j : v[a[i]]) cnt[j] ++;//标记 A_i 的因数 
	for(int i = 1;i <= n;i ++){
		for(auto j : v[a[i]]) if(cnt[j] >= k) ans = j;
		printf("%d\n",ans);//A_i 最大的标记次数达到 K 的因数 
	}
	return 0;
}
```
## 闲话
vector 常数大，在本地不开 O2 预处理超过时限是正常的，不敢交你就输了。

---

## 作者：Aegleseeker_ (赞：1)

## 题意

给你一个长度为 $1\le n\le 1.2\times 10^6$ 的序列和一个 $k$。对于每个 $1\le i\le n$，你需要求出「从序列中选 $k$ 数并强制选 $i$，最大的 $\gcd$」。

值域：$1\le a_i\le 10^6$。

## 题解

~~很像同学出的某道题。~~

~~（同学从某种意义上押中了 ABC393 的题目，膜拜）~~

$\gcd$ 这个东西没啥好的性质所以直接做做不了，这种时候一般考虑从答案入手，判断是否合法。

我们枚举答案 $1\le i\le 10^6$，再判断这个答案能对哪些 $1\le j\le n$ 造成贡献。不难发现所有 $a_j=ki$ 的 $j$ **可能** 造成贡献。于是我们接着枚举 $ki$，然后提前开个桶记录所有的 $a_j$，统计 $a_j=ki$ 的那些数和个数，不难发现当个数 $\ge k$ 时可以造成贡献，于是我们对这些数的答案取 $\max$ 即可。（建议参考代码理解）

submission：https://atcoder.jp/contests/abc393/submissions/62794977

复杂度是什么？不考虑重复的数，是 $O(n\ln n)$ 的，考虑重复的数，是 $O(n\times d(n))$ 的，而 $d(n)$ 的量级很小，可以通过。

---

## 作者：DrAlfred (赞：1)

摘要：数学，枚举，桶

[传送门：https://www.luogu.com.cn/problem/AT_abc393_e](https://www.luogu.com.cn/problem/AT_abc393_e)

## 题意

给定一个长度为 $n$ 的数组 $a$，现在对于每个 $i = 1, 2, \dots, n$，求出在数组中包含 $a_i$ 的长度为 $k$ 的子序列的 $\gcd$ 的最大值。

## 分析思路

首先观察到对于相同的值答案应该是一样的，同时原问题也等价于我们选出长度大于等于 $k$ 的子序列的 $\gcd$ 的最大值，考虑把所有相同的值放到一起来看。

抛开优秀的常数，时间复杂度为 $O(n\times \max \mathrm{d}(V))$ 甚至 $O(n \sqrt V)$ 的做法是不可取的，也就是说我们没法对每个数分解质因数。那么可以考虑枚举答案。设当前的答案为 $g$，如果 $\sum_{g \mid x} cnt_x \ge k$，那么 $g$ 对于所有 $g \mid x$ 的值 $x$ 都是合法的答案，对这些值更新答案即可。

总复杂度为 $O(\frac{V}{\sum_{i=1}^V i} + n) = O(V \log V + n)$，可以通过本题。使用 Dirichlet 前缀和可以做到 $O(V \log \log V + n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1200010;
const int V = 1000010;
int n, k, a[N], cnt[V], ans[V];
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i], cnt[a[i]]++;
    }
    for (int g = 1; g < V; g++) {
        int tot = 0;
        for (int i = g; i < V; i += g) {
            tot += cnt[i];
        }
        if (tot < k) continue;
        for (int i = g; i < V; i += g) {
            ans[i] = g;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[a[i]] << '\n';
    }
    return 0;
}

```

---

## 作者：SunburstFan (赞：1)

### E - GCD of Subset

#### 题目大意

给定一个长度为 $N$ 的序列 $A=(A_1,A_2,…,A_N)$ 和一个正整数 $K$。对于每个元素 $A_i$，解决如下问题：

- 选择 K 个包含 $A_i$ 的元素，求出这些元素的最大公约数。

#### 解题思路

1. 使用一个数组 `freq` 来记录每个元素出现的次数。

2. 对于每个可能的数 $d$，我们要计算出它所有倍数的出现频率。即，$d$ 的倍数是 $d,2d,3d,\dots$ ，累加这些数的出现次数。

3. 对于每个 $d$，如果它的倍数的出现次数大于或等于 $K$，说明我们可以选出至少 $K$ 个元素，且它们的 $\operatorname{GCD}$ 至少是 $d$。然后，遍历它的倍数，并更新这些倍数对应的最大 $\operatorname{GCD}$。

   时间复杂度：$O(N \log N)$。

#### 核心代码

```cpp
int n, k;
cin >> n >> k;

vector<int> a(n+5);
for(int i = 0; i < n; i++)
    cin >> a[i];

vector<int> freq(N+5, 0);
for(int i = 0; i < n; i++){
    freq[a[i]]++;
}

vector<int> f(N+5, 0);
for(int d = 1; d <= N; d++){
    for(int m = d; m <= N; m += d){
        f[d] += freq[m];
    }
}

vector<int> ans(N+5, 0);
for(int d = 1; d <= N; d++){
    if(f[d] >= k){
        for(int m = d; m <= N; m += d){
            ans[m] = max(ans[m], d);
        }
    }
}

for(int i = 0; i < n; i++){
    cout << ans[a[i]] << "\n";
}
```

---

## 作者：szh_AK_all (赞：1)

可以先考虑每个因子对于最终答案的贡献。对于一个因子 $i$，如果输入序列 $a$ 中有不小于 $k$ 个数是 $i$ 的倍数，那么最终答案就可能是 $i$，也就是此时对于每个满足 $a_j$ 是 $i$ 的倍数的位置 $j$，其答案至少为 $i$。

于是枚举每个因子 $i$，枚举 $i$ 的倍数并统计其答案即可，容易计算该做法时间复杂度正确。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[2000005], q[1000005], da[2000005];

signed main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i], q[a[i]]++;
	for (int i = 1; i <= 1000000; i++) {
		int ans = 0;
		for (int j = 1; i * j <= 1000000; j++)
			ans += q[i * j];
		if (ans >= k)
			for (int j = 1; i * j <= 1000000; j++)
				da[i * j] = i;
	}
	for (int i = 1; i <= n; i++)
		cout << max(1, da[a[i]]) << "\n";
}
```

---

## 作者：時空 (赞：0)

[In Luogu](https://www.luogu.com.cn/problem/AT_abc393_e)

这种题都不会？这种题都不会？这种题都不会？这种题都不会？这种题都不会？这种题都不会？这种题都不会？

赛时过了 F 没过 E。我的评价是 E > F。

注意到对于一个数 $x$，如果一定要选这个数的话，最终得到的 $\gcd$ 肯定是 $\le x$ 的。

考虑对于每个 $x$，记录在序列 $a$ 中有多少个数是 $x$ 的倍数。不妨令其为 $cnt_x$。这个东西很好求。

那么当 $cnt_x \ge K$ 时，对于 $x$ 的所有倍数，必须选上它们后最终的 $\gcd$ 至少可以得到 $x$。那么对于这些倍数更新一遍，取最值即可。这样就做完了。

[AC Link](https://atcoder.jp/contests/abc393/submissions/62822351)

---

## 作者：Yuexingfei_qwq (赞：0)

差点 AC。
## 思路  
用 $cnt_i$ 表示能被 $i$ 整除的所有数的个数，$e_i$ 表示 $i$ 的所有因数。素数筛处理出 $cnt$ 和 $e$，最后计算最小值即可。  

## AC CODE  
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a / __gcd(a, b) * b
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned long long;

int n, k;
int a[1300000], cnt[1100000];
std::vector<int> e[1300000];

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> n >> k;
	F(i, 1, n, 1) {
		cin >> a[i];
		cnt[a[i]]++;
	}
	F(i, 1, 1000000, 1) {
		e[i].push_back(i);
		F(j, i * 2, 1000000, i) {
			cnt[i] += cnt[j];
			e[j].push_back(i);
		}
	}
	F(i, 1, n, 1) {
		int ans = 0;
		for (auto j : e[a[i]]) {
			if (cnt[j] >= k) {
				ans = std::max(ans, j);
			}
		}
		cout << ans << el;
	}
	r0;
}
```

[AC 记录](https://atcoder.jp/contests/abc393/submissions/62850866)

--- 
完结~~不~~散花。

---

## 作者：heyx0201 (赞：0)

## 题意
给定 $N$ 个正整数 $A_1, A_2, \dots, A_N$，对于每个 $A_i$，求：所有包含 $A_i$ 的大小为 $K$ 的 $A$ 的子集中元素 $\gcd$ 最大值。
## 思路
这题思路还挺显然的，$1 \le A_i \le 10^6$ 可以得到启发去枚举 $\gcd$ 作为答案，并将答案用值作下标记录。

令 $F(x)$ 表示 $A$ 中可以被 $x$ 整除的数的个数，发现若 $x$ 可以作为答案，则必然满足 $F(x) \ge k$。又有 $A_i \le 10^6$，令当前枚举的答案为 $x$，考虑统计每个数出现次数，再采用类似于埃氏筛的思想统计 $F(x)$，即 $A$ 中元素在序列 $S = \{x, 2x, 3x, \dots qx\}, q \in \text{N*}$ 出现次数。此时若满足条件，即可更新 $S$ 中元素的答案。
## 核心代码
```cpp
for (int i = 1; i <= n; i++) {
  cnt[a[i]]++; // 统计元素出现次数
}
for (int i = 1; i < MAXV; i++) {
  int cntk = 0;
  for (int j = i; j < MAXV; j += i) { // 埃氏筛思想，下同
    cntk += cnt[j]; // 统计 F(x)
  }
  if (cntk >= k) { // 满足条件
    for (int j = i; j < MAXV; j += i) {
      ans[j] = i; // 更新答案
    }
  }
}
```

---

## 作者：ztd___ (赞：0)

### 致敬传奇 ABC393 赛时仅一人 AK。

你发现 A，B，C，D 都是一眼题，花 15min 切掉后，认为自己一定能 AK 这一场 ABC，于是转来思考 E。


你发现自己做过一道相似的题目。
> 给定长度为 $N$ 的序列 $A$ 和整数 $K$，要求从 $A$ 中任选 $K$ 个数字，使得这些数的 $\gcd$ 最大。其中 $N \le 10^5$，$K \le 10^5$，$A_i \le 10^5$。

你回想起老师讲这道题时的思路。
> 设答案为 $X$，那么选出来的 $K$ 个数字必然都有一个因数 $X$。那么将每一个数分解因数后，把因数们放在一个桶 $b$ 里，找出最大的满足 $b_i \ge K$ 的 $i$ 即可，也就是让拥有 $i$ 这个因子的数字数量比 $K$ 多或等于 $K$。

你仿佛发现了解题的线索，这意味着，**你距离 AK ABC393 更近了一步！**

你决定把这些因数存在桶里面，然后到 $A_i$ 的时候，因为 $A_i$ 必选，所以 $K$ 个数里肯定有 $A_i$。

所以你把 $A_i$ 的因数分解出来。对于每一个因数 $j$，如果 $b_j \ge K$，就说明除了 $A_i$ 以外，还有至少 $K - 1$ 个数字有 $j$ 这个因子，那么 $j$ 就可以作为答案。你只要统计满足 $b_j \ge k$ 的 $j$ 的最大值就好了。

你心中很是兴奋，你想象着 AK ABC393 后的辉煌。  
“唉唉，怎么 [TLE](https://atcoder.jp/contests/abc393/submissions/62789452) 了啊！”

你仔细想了想，分解因数的复杂度是根号，总体的复杂度就是 $O(N\sqrt{V})$，其中 $V$ 为值域。

“唉唉，这个数据范围怎么这么大啊！那岂不是连因数都分解不了了吗！唉唉，什么不可做题啊！什么司马 ABC。”

你突然认为 AK ABC393 似乎不是那么简单。

你冥思苦想，终于在仅剩 10min 时思考出了新的方法。

“既然不能直接分解，那为什么不间接分解呢？”

唉唉，间接分解是什么东西。

哦哦哦，好像有一种东西。一个一个往前推。比如到 $2$ 的时候，就把剩下所有 $2$ 的倍数的**因子集**中塞进去一个 $2$。

“埃氏筛好像就是这个原理啊！那埃氏筛 $10^6$ 随便跑，这个是不是也能 $10^6$ 随便跑啊！”

你发现可以用 `vector` 来维护**因子集**。于是你高兴地写出了代码。

哦哦哦，[AC](https://atcoder.jp/contests/abc393/submissions/62812922) 了。**你距离 AK ABC393 更近了一步！**

“唉唉，比赛怎么结束了啊。”

“唉唉，怎么**只有一个人**过了 G 啊！”

你忽然发现，AK ABC 似乎没有那么简单。

---

## 作者：3_14 (赞：0)

[**题目传送门**](https://www.luogu.com.cn/problem/AT_abc393_e)

# 思路

* 预处理因数。

对于每个数，我们可以预处理出它的所有因数。因为题目中数的范围是 $1\le A_i \le 10^6$，所以可以预先计算出 $1$ 到 $10^6$ 每个数的因数，以便后续快速查找。

* 统计因数出现次数

遍历数组 $A$，对于每个数 $A_i$，将其所有因数的出现次数加一。这样我们就得到了每个因数在数组中出现的总次数。

* 寻找最大公约数

对于数组中的每一个元素 $A_i$，从它的最大因数开始遍历其所有因数，找到第一个出现次数大于等于 $k$ 的因数，这个因数就是包含 $A_i$ 的 $k$ 个元素子集中能达到的最大公约数。

# 代码

```cpp
#include<bits/stdc++.h>
#define Freopen(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
#define lcm(x,y) x/__gcd(x,y)*y
#define lb(x) (x&-x)
#define str to_string
using namespace std;
using ll=long long;
const double EPS=1e-6,PAI=acos(-1.0);
const int MAX=1.2*1e6+5,mod=1e9+7,MOD=998244353;
// 函数用于预处理每个数的所有因数
vector<vector<int>> jc(int x) {
    vector<vector<int>> ans(x + 1);
    // 遍历所有可能的因数
    for (int i = 1; i <= x; i++)
        // 对于每个数 j，如果 i 是 j 的因数，则将 i 加入 j 的因数列表中
        for (int j = i; j <= x; j += i)
            ans[j].push_back(i);
    return ans;
}
int n, k, A[MAX];
int main() {
    // 关闭同步流
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++)cin >> A[i];
    // 预处理 1 到 1e6 + 5 每个数的因数
    auto div = jc(1e6 + 5);
    // 用于统计每个因数出现的次数
    vector<int> cnt(1e6 + 11, 0);
    // 遍历数列 A，统计每个数的因数出现次数
    for (int a : A)
        for (int d : div[a])cnt[d]++;
    // 对于数列中的每个元素 A[i]
    for (int i = 0; i < n; i++) {
        int ans = 1;
        // 从 A[i] 的最大因数开始遍历
        for (int j = div[A[i]].size() - 1; j >= 0; j--) {
            int d = div[A[i]][j];
            // 如果该因数出现次数大于等于 K，则找到了最大公约数
            if (cnt[d] >= k) {
                ans = d;
                break;
            }
        }
        // 输出结果
        cout << ans << '\n';
    }
    return 0;
}
```

[**AC 记录**](https://atcoder.jp/contests/abc393/submissions/62991875)

---

## 作者：linjinkun (赞：0)

> 大概评级：绿。

拿到题目，寻找突破口，发现 $A_i \le 10^6$，一般的数据都是 $A_i \le 10^9$，所以必有蹊跷。

数学，权值，最大公约数，联想到了因子……懂了，原来是这么做！

首先一个数 $x$ 如果能做最大公约数，那么 $A_i$ 一定是 $x$ 的倍数，并且总共有至少 $K$ 个数是 $x$ 的倍数（包含 $A_i$），那么我们肯定是需要一个数组来处理对于一个数在 $A$ 中有多少个数是它的倍数，但根据我们的直觉，在这个数组之前应该还需要设置一个数组处理对于一个数它在 $A$ 中出现了多少次，我们设处理对于一个数它在 $A$ 中出现了多少次的数组为 $num$，处理对于一个数在 $A$ 中有多少个数是它的倍数的数组为 $s$，那么显然 $f_d = \sum_{d|n} s_n$，于是直接使用类似埃氏筛法的东西求出 $f$ 数组，如果设 $M = \max_{i = 1}^n A_i$，那么求出 $f$ 数组的时间复杂度为 $O(M \log M)$，求出 $s$ 数组就不用说了，$O(N)$ 地一边读入一边统计就行了，最后有了 $f$ 数组的辅助，是很好求出答案的，我们设 $A_i$ 的答案为 $ans_i$，$ans_i = \max_{d|n,t_d \ge K}d$，很好理解吧，于是我们发现这玩意也可以使用一种类似埃氏筛的方法求，于是这道题就结束了。

总时间复杂度：$O(N+M \log M+M \log M+N) = O(N+M \log M)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1.2e6+5;
int num[N],t[N],ans[N],a[N];
int main()
{
	int n,k;
	scanf("%d %d",&n,&k);
	int maxx = 0;
	for(int i = 1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		maxx = max(maxx,a[i]);
		num[a[i]]++;
	}
	for(int i = 1;i<=maxx;i++)
	{
		for(int j = i;j<=maxx;j+=i)
		{
			t[i]+=num[j];	
		}
	}
	for(int i = 1;i<=maxx;i++)
	{
		if(t[i]<k)
		{
			continue;
		}
		for(int j = i;j<=maxx;j+=i)
		{
			ans[j] = max(ans[j],i);
		}
	}
	for(int i = 1;i<=n;i++)
	{
		printf("%d\n",ans[a[i]]);
	}
    return 0;
}
```

---

## 作者：Magus (赞：0)

第一次赛时 ABCDE。

注意到 $A_i$ 最大 $10^6$。

这个数据范围，我们可以记录原数组中每个数出现了多少次，然后从 $1$ 到 $10^6$ 枚举最大公约数 $i$，如果数组中有超过 $K$ 个数能被 $i$ 整除，说明一定可以从原数组中选取 $K$ 个数保证这些数的最大公约数至少为 $i$，那么答案数组更新，然后就做完了。

[AC 记录。](https://atcoder.jp/contests/abc393/submissions/62813108)

```cpp
#include<bits/stdc++.h>
#define int long long
#define I using
#define AK namespace
#define NOIP2024 std
I AK NOIP2024;
const int maxn=1e7+10,maxm=1e3+10,mod=998244353,inf=1000000;
int n,m,x,y,u,v,arr[maxn],res[maxn];
unordered_map<int,int>mp;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>arr[i];
		mp[arr[i]]++; 
	}
	for(int i=1;i<=inf;i++)
	{
		x=0;
		for(int j=i;j<=inf;j+=i)
		{
			x+=mp[j];
		}
		if(x>=m)
		{
			for(int j=i;j<=inf;j+=i)
			{
				res[j]=i;
			}			
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<res[arr[i]]<<'\n';
	}
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

首先题意转化求 $a_i$ 最大的约数 $x$ 满足在 $a_{1,2,\cdots n}$ 中存在 $k$ 个数被 $x$ 整除。考虑一个预处理值域内所有数约数的方法：枚举约数 $x$，把 $2x,3x,\cdots$ 标记约数 $x$，再顺便记一下约数出现的次数。这样的复杂度是调和级数的，可以接受。然后你就直接枚举约数即可。记 $d(n)$ 为 $n$ 的约数个数，时间复杂度 $O(V\log V+nd(V))$ 可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define test cerr << "test\n"
#define print(x) cout << #x << " = " << x << endl
#define file(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

const int N = 1.2e6 + 5;
int n, k, m, a[N], cnt[N], c[N];
vector <int> p[N];
int solve(int x) {
    vector <int> qwq = p[x]; reverse(qwq.begin(), qwq.end());
    for (int y : qwq) if (c[y] >= k) return y;
    return 1;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++, m = max(m, a[i]);
    for (int i = 2; i <= m; i++) for (int j = i; j <= m; j += i)
        p[j].push_back(i), c[i] += cnt[j];
    for (int i = 1; i <= n; i++) cout << solve(a[i]) << '\n';
    return 0;
}

```

---

## 作者：ANDER_ (赞：0)

#### 考察：数学、筛法。
## E - GCD of Subset
Time Limit: 2 sec / Memory Limit: 1024 MB
### 题意

给你一个长度为 $N$ 的序列 $A$ 和一个正整数 $K$。  

针对每个 $i = 1, 2, \dots, N$ 求解下面的问题：

- 从 $A$ 中选出包含 $A_i$ 的 $K$ 个元素，求所选元素的最大公约数的最大值。
### 数据范围

- $1 \leq K \leq N \leq 1.2 \times 10^6$
- $1 \leq A_i \leq 10^6$
- 所有输入值均为整数。

### 思路

记 $frq_x$ 为 $A$ 中 $x$ 的出现次数，预处理时间复杂度 $\Theta(N)$，形式化地：
$$frq_x = \displaystyle\sum_{i=1}^N [A_i = x]$$

记 $cnt_x$ 为 $A$ 中所有 $A_i$ 满足 $x \mid A_i$ 的个数，预处理时间复杂度 $\Theta(N)$ 但常数较大，计算方式：
$$cnt_d = \displaystyle\sum_{m=1}^{\lfloor \frac{A_{\max}}{d} \rfloor} frq_{d \times m}$$


记 $fcm_x$ 为满足 $cnt_d \ge K \land d \mid x$ 的最大因数 $d$。可以从大到小遍历所有可能的因数 $d$，若 $cnt_d \ge K$，则用 $d$ 更新答案，以确保每个元素取到最大可能的 $d$。预处理时间复杂度 $\Theta(N)$ 但常数较大。计算方式：

$$\forall x = k \cdot d \ (k \in \mathbb{N}^+),fcm_x = \max(fcm_x, d)$$

对于每个 $A_i$，最终答案即为 $fcm_{A_i}$。时间复杂度 $\mathcal{O}(M \log_2 M)$，其中 $M = \underset{x \isin A}{\max}\text{ }x$，[赛时代码](https://atcoder.jp/contests/abc393/submissions/62807822)。

---

## 作者：lilong (赞：0)

由于 $a_i \le 10^6$，故可以一遍求出 $[1,10^6]$ 内每个数的因数以及这个数的倍数在 $a$ 中的出现次数。求完后对每个 $a_i$ 暴力枚举因数，判断其倍数出现次数是否超过 $k$ 并更新答案即可。

总时间复杂度 $O(N\log N+nd(a_i))$，其中 $N=10^6$，又由于 $a_i\le 10^6$，故 $\max \{ d(a_i) \} \le 240$，可以通过本题。如果后半部分预处理完 $[1,10^6]$ 内所有答案再输出，则复杂度 $O(N\log N+n)$，但实际运行稍慢。以下代码为第一种写法。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define N 1000000

using namespace std;

vector<int> p[N + 10];
int n,k,a[N * 2 + 10],f[N + 10],g[N + 10];

int main()
{
    cin >> n >> k;
    for( int i = 1 ; i <= n ; i ++ )
        cin >> a[i],f[a[i]] ++;
    for( int i = 1 ; i <= N ; i ++ )
        for( int j = i ; j <= N ; j += i )
            p[j].push_back( i ),g[i] += f[j];
    for( int i = 1 ; i <= n ; i ++ )
    {
        for( int j = p[a[i]].size() - 1 ; j >= 0 ; j -- )
            if( g[p[a[i]][j]] >= k )
            {
                cout << p[a[i]][j] << '\n';
                break;
            }
    }
    return 0;
}
```

---

## 作者：Dream_poetry (赞：0)

### 思路：

我们发现 $A_i \le 10^6$，所以我们思考每个元素的权值和答案的关系。

我们首先拿一个桶，记录每个元素出现了多少次。

我们设 $b_i$ 表示 $i$ 最多可以是多少个元素的公因数，通过暴力枚举来获得对应答案即可。

如果 $b_i$ 不小于 $k$，我们就考虑枚举 $i$ 的倍数，尝试用 $i$ 来更新 $x \times i$ 的答案。

最后直接输出每个元素对应的答案即可。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k;
int a[1200005];
int maxn;

int cnt[1200005];
int b[1200005];
int ans[1200005];



signed main(){
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		cnt[a[i]]++;
		maxn=max(maxn,a[i]);
	}	
	for (int i=1;i<=maxn;i++){
		for (int j=i;j<=maxn;j+=i){
			b[i]+=cnt[j];
		}
	}
	for (int i=1;i<=maxn;i++){
		if (b[i]<k){
			continue;
		}
		for (int j=i;j<=maxn;j+=i){
			ans[j]=max(ans[j],i);
		}
	}
	for (int i=1;i<=n;i++){
		cout<<ans[a[i]]<<'\n';
	}
	return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## [ABC393E] GCD of Subset

一开始的时候，我看到这个题目，想到的是暴力枚举组合（但是根据数据范围显然不能做到）。

$A_i$ 的值域是 $10^6$，这个范围下，我们考虑统计每个数出现的次数，然后枚举每个约数，对于每个约数，通过枚举这个约数的倍数的方式，统计数组中能被这个数整除的数的个数。然后我们枚举约数，如果数组中有超过 $K$ 个数能被这个约数整除，我们就可以通过枚举这个约数的倍数的方式，更新该数字的答案值。

最后从前往后，通过数组中的值调用前面预处理的答案数组，输出答案即可。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,a[1200010],frq[1000010],d[1000010],ans[1000010];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		frq[a[i]]++;
	}
	for(int i=1;i<=1000000;i++)
		for(int j=i;j<=1000000;j+=i)
			d[i]+=frq[j];
	for(ll i=1000000;i>=0;i--){
		if(d[i]<k) continue;
		for(int j=i;j<=1000000;j+=i)
			ans[j]=max(ans[j],i);
	}
	for(int i=1;i<=n;i++)
		cout<<ans[a[i]]<<endl;
	return 0;
}
```

---

## 作者：ljy05 (赞：0)

首先，我们要确定每个数 $x$ 是否能作为答案。如果在 $A$ 中，有至少 $K$ 个数是 $x$ 的倍数，那么 $x$ 就可能是答案。一个桶可以用来快速的统计在 $A$ 中有多少个数是 $x$ 的倍数。

然后，我们要确定每个数 $y$ 的答案是多少。如果 $y$ 是某个 $x$ 的倍数，并且 $x$ 能作为答案，那么 $y$ 的答案就可能是 $x$。在枚举 $x$ 的时候，更新它所有倍数的答案就可以高效的完成这一步。

最后，对于每个 $A_i$，取出它的答案即可。

代码：https://atcoder.jp/contests/abc393/submissions/62799854

---

## 作者：lfxxx_ (赞：0)

我们对于每个数 $i$，记录一下他是 $A$ 中多少个数的因数，记为 $cntd_i$。

然后对于所有 $cntd_i \ge K$ 的数，我们再次扫一遍，让 $A$ 中所有他的倍数的最大因数修改成 $i$。

时间复杂度 $O(N+V \log V)$，其中 $V = \max(A_i)$。

```cpp
//zhouyoyo巨佬保佑我AK
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int a[N],cnt[N],ans[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,K,maxn=0;
    cin>>n>>K;
    for(int i=1;i<=n;++i)
        cin>>a[i],++cnt[a[i]],maxn=max(maxn,a[i]);
    for(int i=1;i<=maxn;++i)
    {
        int cntd=0;
        for(int j=1;j*i<=maxn;++j)
            cntd+=cnt[i*j];
        if(cntd>=K)
        {
            for(int j=1;j*i<=maxn;++j)
                ans[i*j]=max(ans[i*j],i);
        }
    }
    for(int i=1;i<=n;++i)
        cout<<ans[a[i]]<<'\n';
}
```

---

