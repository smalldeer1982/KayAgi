# [ARC160C] Power Up

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc160/tasks/arc160_c

正整数からなる $ N $ 要素の多重集合 $ A=\lbrace\ A_1,A_2,\dots,A_N\ \rbrace $ が与えられます。

あなたは、以下の操作を好きな回数 ( $ 0 $ 回でもよい) 繰り返すことが出来ます。

- $ A $ に $ 2 $ 個以上含まれる正整数 $ x $ を選ぶ。$ A $ から $ x $ を $ 2 $ 個削除し、$ A $ に $ x+1 $ を $ 1 $ 個加える。
 
最終的な $ A $ としてあり得るものの個数を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 2\ \times\ 10^5 $
 
### Sample Explanation 1

最終的な $ A $ としてあり得るものは、$ \lbrace\ 1,1,2,4\ \rbrace,\lbrace\ 2,2,4\ \rbrace,\lbrace\ 3,4\ \rbrace $ の $ 3 $ 個があります。 $ \lbrace\ 3,4\ \rbrace $ は以下のようにして作ることが出来ます。 - $ x $ として $ 1 $ を選ぶ。$ A $ から $ 1 $ を $ 2 $ 個削除し、$ 2 $ を $ 1 $ 個加える。$ A=\lbrace\ 2,2,4\ \rbrace $ となる。 - $ x $ として $ 2 $ を選ぶ。$ A $ から $ 2 $ を $ 2 $ 個削除し、$ 3 $ を $ 1 $ 個加える。$ A=\lbrace\ 3,4\ \rbrace $ となる。

## 样例 #1

### 输入

```
4
1 1 2 4```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
1```

## 样例 #3

### 输入

```
13
3 1 4 1 5 9 2 6 5 3 5 8 9```

### 输出

```
66```

# 题解

## 作者：541forever (赞：3)

因为我们只关心最后集合的状态个数，因此我们可以钦定合并顺序是从小到大的，因为如果从大往小可能会有后效性。

注意到，值域较小，考虑暴力 dp，记 $dp_{i,j}$ 表示合并到 $i$ 这个值，现有 $j$ 个 $i$ 的方案数。转移可以考虑到 $dp_{i,j}$ 可以转移到 $dp_{i+1,cnt_{i+1}+k}$ 其中 $k \le \lfloor{ j\over2}\rfloor$。

这个状态看上去有 $O(n^2)$ 个，考虑将第二维记作第 $i$ 位增加了 $j$ 个，记 $cnt_i$ 表示 $i$ 这个值在 $a_i$ 中出现的次数，$A$ 为 $a$ 中最大的数，则状态数变为 $\sum_{i=1} ^{A+\log N} {{\sum_{j=1}^i 2^j\times cnt_j}\over 2^i}\le 2N$。转移可以考虑差分每次用后缀和算出 $dp_i$。

[Code](https://atcoder.jp/contests/arc160/submissions/41647792)

---

## 作者：Mars_Dingdang (赞：3)

## 题目描述
给出一个大小为 $N$ 的可重集 $ A=\lbrace\ A_1,A_2,\dots,A_N\ \rbrace $。

你可以执行若干次如下操作（也可以不执行）。

- 将两个 $x$ 合并成一个 $x+1$。

输出最终可能的集合个数对 $998244353$ 取模的结果。

## 大体思路
计数题，一眼 DP。

令 $f(i,j)$ 表示当前对数 $i$ 进行操作，$i$ 可以对下一位贡献 $j$ 个数的集合个数。记 $num_i$ 表示数 $i$ 的出现次数，很显然有
$$f(i,\dfrac {num_i+j}{2})=\sum_{k=j}f(i-1,k)$$

这样转移需要 $O(n)$，一个简单的后缀和优化即可做到 $O(1)$ 转移。

然后就是 DP 状态的精细实现，大概类似 IOI2022 鲶鱼塘那题，用一个 `vector` 存状态，这样由于每次能贡献的数的个数都是加上一个不大的数除以 $2$，又由于最大的数不超过 $O(\max+\log)$，因此记 $N=\max+\log$，则状态数不超过 $\sum_{i=1}^N num_i(1+\dfrac 1 2 +\dfrac 1 4+\cdots)=2N$，即线性。

注意取模。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 3e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int n, a[maxn], num[maxn];
vector<int> f[maxn];
const ll mod = 998244353;
int main () {
	read(n);
	rep(i, 1, n) {
		read(a[i]);
		num[a[i]] ++;
	}
	f[0].push_back(1);
	rep(i, 1, 200050) {
		f[i].resize((num[i] + f[i - 1].size()) / 2 + 1);
		for(int j = 0; j < f[i - 1].size(); ++ j)
			(f[i][(j + num[i]) / 2] += f[i - 1][j]) %= mod;
		for(int j = f[i].size() - 2; j >= 0; -- j)
			(f[i][j] += f[i][j + 1]) %= mod;
	}
	writeln(f[200049][0]);
	
	return 0;
}
```

---

## 作者：xzCyanBrad (赞：2)

人类智慧分析复杂度题，会不了半点。鉴定为脑子退化了。

设 $c_x$ 为 $A$ 中 $x$ 的个数。首先我们有 $\Theta(n^3)$ dp：令 $F(i,j)$ 表示数字 $i$ 给数字 $i+1$“进位”$j$ 个的方案数，那么有 $F(i,j)=\sum_{k\ge\max(0,2j-a_i)}F(i-1,k)$。进一步地可以把它优化成 $\Theta(n^2)$：设 $G(i)$ 为 $F(i)$ 的后缀和，则 $F(i,j)=G(i-1,\max(0,2j-a_i))$。

于是我花了两天想怎么把它优化成小于平方的状态，甚至真想出了一个分块做法……因为看起来现在的状态是平方的。/fn

转念一想，考虑计算状态数。显然到 $i$ 的状态数 $q_i=\left\lfloor\frac{q_{i-1}+c_i}{2}\right\rfloor$。计算每个 $c_x$ 对状态数的贡献，发现它在 $x$ 会被贡献 $c_x$ 次，在 $x+1$ 会被贡献 $\left\lfloor\frac{c_x}2\right\rfloor$ 次……最后就是 $c_x(1+\frac12+\frac14+\cdots+\frac1{2^t})\le 2c_x$ 是线性的！又根据 $\sum c=n$，我们发现总状态数是线性的！

于是记录每个 $q_i$，dp 只到 $q_i$ 即可。数组开不下可以滚动。

没了。

---

## 作者：Lucyna_Kushinada (赞：1)

我们可以钦定一个从小到大合并的顺序，以更方便地 dp。

对于数字 $i$，能影响到其出现次数的只有 $i-1$，于是我们设 $dp_{i,j}$ 表示合并到**数字** $i$ 时，其出现次数为 $j$ 的集合数，同时令 $cnt_i$ 为原始时 $i$ 的出现次数，还有 $lst_{i-1}$ 为 $i-1$ 的最大出现次数（能合并就合并）。

所以 $dp_{i,j+cnt_i}=\displaystyle\sum_{k=2\times j}^{lst_{i}}dp_{i-1,k}$，$lst_i=cnt_i+\lfloor\frac{lst_{i-1}}{2}\rfloor$，答案就是 $\displaystyle\sum_{i=cnt_v}^{lst_{v}}dp_{v,i}$，其中 $v$ 为可以理论合并出的最大值（可以看作 $n+\log_2 n$），$dp_{v,cnt_v}$ 是不去主动合并出 $v$ 的方案数。

不过这个会超时，我们考虑优化一下。

首先把 $j+cnt_i$ 都换元为 $j$，得到 $dp_{i,j}=\displaystyle\sum_{k=2\times (j-cnt_i)}^{lst_{i}}dp_{i-1,k}$。

这显然可以方便地使用后缀和优化，又因为 $lst_i$ 对 $lst_{i+1}$ 贡献最多只有其一半，而且 $\sum cnt_i$ 不超过 $2 \times 10^5$，所以我们可以把复杂度看作 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back

#define N 202502
#define int long long

const int lim=2e5+20;
const int mod=998244353;
int n,a[N],cnt[N],dp[N],s[N];

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n;

    rep(i,1,n){
        cin>>a[i];
        cnt[a[i]]++;
    }

    s[0]=1;

    int lst=0;
    rep(i,0,lim){
        lst=cnt[i]+lst/2;

        rep(j,0,cnt[i]-1){
            dp[j]=0;
        }

        rep(j,cnt[i],lst){
            dp[j]=s[(j-cnt[i])*2];
        }

        s[lst]=dp[lst];
        per(j,0,lst-1){
            s[j]=(s[j+1]+dp[j])%mod;
        }
    }

    cout<<s[0];

    return 0;
}
```

---

## 作者：TernaryTree (赞：1)

期末结束力，做点水题唤醒思维。

一眼 dp，注意到是两两合并类问题，大胆猜测设计一个暴力 dp 的状态数量是对的。于是有了 $f_{i,j}$ 表示只考虑值域 $1\sim i$ 的数，最终合出来 $i$ 有 $j$ 个的方案数。

注意到只考虑 $1\sim i$ 的情况下，$i$ 的个数一定会比初始时候多，因为不考虑 $i$ 合成 $i+1$ 的情况。

则有

$$f_{i,cnt_i+j}=\sum_{k=2j} f_{i-1,k}$$

令 $g_{i,j}=f_{i,cnt_i+j}$，化上式为

$$g_{i,j}=\sum_{k=\max(2j-cnt_{i-1},0)}f_{i-1,k}$$

后面的用后缀和优化一下可以 $\Theta(1)$ 转移。我们考虑这样的 dp 实际有值的状态数有多少：设 $v_i$ 表示 $g_i$ 底下有多少个 $j$ 有值。则有

$$
\begin{aligned}
2j-cnt_{i-1}&\le v_{i-1}\\
j&\le\dfrac{ v_{i-1}+cnt_{i-1}}2\\
v_i&=\dfrac{ v_{i-1}+cnt_{i-1}}2
\end{aligned}
$$

那么就有

$$

\begin{aligned}
\sum v_i&=\dfrac12\sum v_{i-1}+cnt_{i-1}\\

\sum v_i&=\dfrac12\sum v_i+\dfrac12 \sum cnt_i\\
\dfrac12\sum v_i&=\dfrac12 \sum cnt_i\\

\sum v_i&= \sum cnt_i=n\\
\end{aligned}
$$

综上我们证明了所有有用的状态只有线性种，所以总 $\Theta(n)$ 做完了。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 5e5 + 10;
const int mod = 998244353;

int n, m = 4e5;
int a[maxn];
int cnt[maxn]; 
vector<int> f[maxn], g[maxn];

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
	}
	f[1].resize(1), g[1].resize(1);
	f[1][0] = g[1][0] = 1;
	for (int i = 2; i <= m; i++) {
		for (int j = 0; ; j++) {
			int l = max(j * 2 - cnt[i - 1], 0ll);
			if (l < f[i - 1].size()) {
				f[i].push_back(g[i - 1][l]);
				continue;
			}
			break;
		}
		g[i] = f[i];
		for (int j = (int) g[i].size() - 2; ~j; j--) (g[i][j] += g[i][j + 1]) %= mod;
	}
	cout << f[m][0] << endl;
	return 0;
}

```

---

## 作者：zhangjiahe__ (赞：0)

# 题意简述：

$n$ 个数组成集合，可以将两个 $x$ 合并成 $x+1$，求最终能变成多少种集合。

# 思路：

设 $dp_{i,j}$ 为已经合并到了 $i$，最多合 $j$ 个 $i+1$ 的方案数。

则转移方程为 $dp_{i,\frac{num_i+j}{2} } = \sum_{k=j}^{} dp_{i-1,k}$，正常转移复杂度不够优，用后缀和优化到均摊 $\Theta (1)$。

# 代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, a[300005], cnt[300005];
vector<int> dp[300005];
signed main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        cnt[a[i]]++; //统计每个数的数量
    }
    dp[0].push_back(1);
    for(int i = 1; i <= 200000+25; i++) //200000+25可以换成n+__lg(n)+1
    {
        dp[i].resize((cnt[i]+dp[i-1].size())/2+1); //先把dp[i]的空间定义好，否则会访问溢出
        for(int j = 0; j < dp[i-1].size(); j++)
        {
            dp[i][(j+cnt[i])/2] += dp[i-1][j]; //转移 
            dp[i][(j+cnt[i])/2] %= 998244353;
        }
        for(int j = dp[i].size()-2; j >= 0; j--)
        {
            dp[i][j] += dp[i][j+1]; //后缀和
            dp[i][j] %= 998244353;
        }
    }
    cout << dp[200024][0];
}
```

---

## 作者：newwzl (赞：0)

## 题意
给你一个自动排序的可重集，每次操作可以取出可重集内相同的两个 $x$ 并插入一个 $x+1$ ，问在任意多次操作后有多少种不同的可重集。
## 思路
这种类型的题因为输入过大无法搜索，那么一般就是贪心或者动态规划。而且这个题是求个数的，基本可以确定是动态规划了。

首先可以想到最简单的 $N^2$ 动态规划：

定义 $f_{i,j}$ 表示当可重集内仅仅存在大于 $i$ 的数并且一共有 $j$ 个 $i$ 时，最终不同的可重集数量。

转移式子也很好想（注：按照我的习惯，我定义 `tong` 表示数字的出现次数）：

 $$f_{i,j}=\sum_{k=tong[i+1]}^{tong[i+1]+\lfloor \frac{j}{2}\rfloor}f_{i+1,k}$$
 
 一个显然的优化是前缀和。另外我们发现，枚举到每一个 $i$ 时，其 $j$ 的上限是比 $N$ 小很多的。计算发现，其上限的总和是 $O(N)$ 级别的。至此，时间优化到了 $O(N)$ 级别的。
 
空间滚动数组即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353,N=4e5+10;;
int n,tong[N],m=4e5,num[N];
int f[5][N],fs[5][N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		scanf("%lld",&x);
		tong[x]++;
	}
	f[m&1][0]=f[m&1][1]=1;
	for(int i=1;i<=m;i++){
		num[i]=max(0ll,num[i-1]/2)+tong[i]+1;
	}
	for(int i=m-1;i>=1;i--){
		f[i&1][0]=f[i&1^1][tong[i+1]];
		for(int j=1;j<=num[i];j++)f[i&1][j]=((fs[i&1^1][tong[i+1]+j/2]-fs[i&1^1][tong[i+1]-1])%mod+mod)%mod;
		fs[i&1][0]=f[i&1][0];
		for(int j=1;j<=num[i];j++){
			fs[i&1][j]=(f[i&1][j]+fs[i&1][j-1])%mod;
		}
	}
	cout<<(f[1&1][tong[1]]+mod)%mod<<"\n";
	return 0;
}
```

---

## 作者：xqh07 (赞：0)

计数题，无关排列组合，需要状态转移，一眼 dp。

先不考虑空间限制，设 $dp_{i,j} $ 表示**值为 $i$ 的数在合并前有 $j$ 个**的方案数，记 $a_i$ 为初始时 $i$ 的数量，设 $y$ 为 $i-1$ 在可重集中的最大出现次数，则有转移方程：

$dp_{i,a_{i}+j} = \sum_{k = j \times 2}^{y} dp_{i-1,k}$

通过简单的后缀和优化，可做到 $O(1)$ 转移。通过简单的滚动数组优化，可将状态数压为 $O(n)$。

又因为最大的数不超过 $mx + \log n$，所以总状态数不超过 $ n \times 2$，时间复杂度为线性。 

# Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int n, x, mx, y, a[300005], dp[300005], res, s[300005], mn = 1e9;
signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &x);
		++a[x];
		mx = max(mx, x);
		mn = min(mn, x);
	}
	y = a[mn];
	for(int j = y; j >= 0; j--) s[j] = 1;
	for(int i = mn + 1; i <= mx + 50; i++)
	{
		y = a[i] + (y / 2);
		for(int j = 0; j < a[i]; j++) dp[j] = 0;
		for(int j = a[i]; j <= y; j++) dp[j] = s[(j - a[i]) * 2];
		s[y] = dp[y];
		for(int j = y - 1; j >= 0; j--) s[j] = (s[j + 1] + dp[j]) % mod;
	}
	printf("%lld\n", s[0]);
	return 0;
}

```


---

## 作者：Starry_Ocean (赞：0)

- 参考文章：Mars_Dingdang 的《[ARC160C](https://www.luogu.com.cn/article/k4m9gi40)》。

#### 算法考察：动态规划。

### 思路

记 $f(i,j)$ 表示操作到第 $i$ 个数可以对 $i+1$ 贡献 $j$ 个数字的方案数。稍加思考，可以得到：

$$
f(i,\frac{cnt_i+j}{2} )= \sum_{k=j}f(i-1,k)
$$

其中 $cnt_i$ 表示数 $i$ 出现的次数。

希望大家能好好推导这个等式，这是学习动态规划很重要的一部分。

好，这样的转移时间复杂度是 $O(n)$ ，显然，无法满足 $n \le 2\times10^5$，因为还要套一层循环，总的时间复杂度为 $O(n^2)$。为了解决这个问题，我们可以使用前缀和优化。这样总的时间复杂度就变成了 $O(n)$。可以通过本题。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 2e5+50;//开大一点，否则会 WA
const ll mod = 998244353;
ll n,a[N],cnt[N];
vector<ll> dp[N];
int main(){
	cin>>n;
	for(ll i = 1;i <= n;++i){
		cin>>a[i];
		cnt[a[i]]++;//桶排序 
	}
	dp[0].push_back(1);
	for(ll i = 1;i <= N;++i){
		dp[i].resize((cnt[i]+dp[i-1].size())/2+1);//开设数组，类似滚动
		for(ll j = 0;j < dp[i-1].size();++j){
			(dp[i][(j+cnt[i])/2]+=dp[i-1][j])%=mod;
		} 
		for(ll j = dp[i].size()-2;j >= 0;--j){
			(dp[i][j]+=dp[i][j+1])%=mod;
		}
	}
	cout << dp[N-1][0];
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/175971021)。

---

