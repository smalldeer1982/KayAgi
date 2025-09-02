# [ARC052D] 9

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc052/tasks/arc052_d

整数の $ 9 $ には面白い性質があります。 どのような非負整数 $ N $ を選んでも $ N $ を $ 9 $ で割った余りと、 $ N $ を $ 10 $ 進法で表記した時の各桁の数字の和を $ 9 $ で割った余りが一致するのです。

高橋君はこのような性質を持つ整数が他にないか気になりました。しかし、残念なことにこのような性質をもつ整数は $ 9 $ と $ 3 $ と $ 1 $ くらいしか見つかりませんでした。 そこで、「どのような非負整数 $ N $ を選んでも・・・」ではなくて「できるだけ多くの非負整数 $ N $ に対して・・・」というふうに性質の条件を落として探してみることにしてみました。

高橋君は非負整数 $ K $ がどれくらい多くの非負整数 $ N $ に対して上のような条件をみたすのかが知りたいです。

高橋君を手伝うために以下の問いに答えてください。

- $ 1\ ≦\ N\ ≦\ M $ となる整数 $ N $ のうち $ K $ で割った余りと、$ N $ を $ 10 $ 進法表記した時の各桁の数字の和を $ K $ で割った余りが一致するような $ N $ の個数を求めてください。

## 说明/提示

### 制約

- 与えられる数字はすべて整数
- $ 1\ ≦\ K\ ≦\ M\ ≦\ 10^{10} $

### 部分点

この問題には部分点が設定されている。

- $ 1\ ≦\ M\ ≦\ 10^5 $ を満たすデータセットに正解した場合は $ 10 $ 点が与えられる。
- $ 1\ ≦\ M\ ≦\ 10^{10} $を満たすデータセットに正解した場合はさらに $ 90 $ 点が与えられる。合計で$ 100 $点となる。

### Sample Explanation 1

$ 1 $桁の整数はかならず条件を満たします。 そのほかに $ 50\ ≦\ N\ ≦\ 59 $ を満たす整数は全て条件を満たします。 これら以外に条件を満たす整数は $ 100 $ 以下の範囲にはありません。 よって $ 19 $ を出力します。

## 样例 #1

### 输入

```
5 100```

### 输出

```
19```

## 样例 #2

### 输入

```
112 32279```

### 输出

```
309```

## 样例 #3

### 输入

```
108 3141592653```

### 输出

```
261799999```

## 样例 #4

### 输入

```
9 10000000000```

### 输出

```
10000000000```

# 题解

## 作者：_sunkuangzheng_ (赞：9)

思路类似的一道题 $\to$ [link](https://www.luogu.com.cn/problem/P6371)。

**【题目分析】**

这类问题很像数位 dp，面对“数字的和是 $k$ 的倍数”我们通常采取把 $x \bmod k$ 作为一维放在 dp 状态里。可惜这题数据范围是 $1 \le k \le m \le 10^{10}$，空间爆炸力！

也许你想了很久也没能想出怎么用一个算法解决 $1 \le k \le 10^{10}$ 的情况。那么我们考虑骗分。你已经知道可以用数位 dp 计算出大约 $k \le 10^4$ 时的答案，那我们只需要解决 $10^4 \le k \le 10^{10}$ 的测试点。

数字多了下界有什么性质？有个好的性质是 $\lfloor \dfrac{m}{k} \rfloor \le 10^6$。所以我们考虑枚举倍数。首先枚举数字数位和的值，容易发现这个值不会超过 $90$。然后枚举每个倍数，暴力判断即可。这部分的时间复杂度是 $\mathcal O(S \log m\dfrac{m}{k} )$，其中 $S = 90$。算一下极限数据会跑 $90 \times 10 \times 10^6 = 9 \times 10^8$，看起来就过不了，但是因为常数很小就过了（

数位 dp 部分，设 $f_{p,s,w,l}$ 表示第 $p$ 位，数字和模 $k$ 为 $s$，数字和为 $w$，是否顶住上界为 $l$ 的方案数，直接记忆化搜索即可。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e4+5;
int k,m,f[15][maxn][91][2],num[15],n,ans;
int dfs(int p,int s,int w,int l){
    if(!p) return s == w % k && w;
    if(f[p][s][w][l] != -1) return f[p][s][w][l];
    int up = (l ? num[p] : 9),ans = 0;
    for(int i = 0;i <= up;i ++) ans += dfs(p-1,(s*10+i)%k,w+i,l && (i == up));
    return f[p][s][w][l] = ans;
}int wk(int x){while(x) num[++n] = x % 10,x /= 10;return dfs(n,0,0,1);}
signed main(){
    cin >> k >> m;memset(f,-1,sizeof(f));
    if(k <= 10000) return cout << wk(m),0;
    for(int i = 0;i <= 90;i ++)
        for(int j = i;j <= m;j += k){
            int ct = 0,x = j;
            while(x) ct += x % 10,x /= 10;
            if(ct % k == i) ans ++;
        }
    cout << ans - 1;//注意 0 不算答案
}
```

---

## 作者：Daniel2020 (赞：7)

~~本来是奔着练根号分治来的，结果做着做着就做成折半搜索了，逛了一遍题解区还没发现相同做法，逆天。~~
 
发现 $\sqrt{10^{10}} = 10^5$，考虑将 $N$ 分割为“前五位”和“后五位”。形式化地讲，令 $p = 10^5,N = ap+b$。

显然有 $a,b \leqslant 10^5$。假设 $a$ 的各位数字之和为 $f_a$，$b$ 的各位数字之和为 $f_b$，则合法的数应满足：

$$ap+b \equiv f_a+f_b \pmod{k}$$

移项得：

$$ap-f_a \equiv f_b-b \pmod{k}$$

于是可以预处理 $(f_b-b) \bmod k$ 计入桶中，再枚举 $a$，求出 $(ap-f_a) \bmod k$ 后在桶中查询即可。注意 $a$ 取到上界时可能不能匹配所有的 $b$，但是此时至多只剩下 $10^5$ 个数没有被判断，暴力计算即可。也可以优先处理 $a$ 取到上界时 $b$ 的上界避免暴力计算。

计算一个数的各位数字之和可以用 DP 处理，消除暴力计算的常数，最终时空复杂度 $O(\sqrt{M})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+7;
typedef long long LL;
LL k,m,p = 100000,w,n,ans,a[N],b[N];
int main()
{
	scanf("%lld%lld",&k,&m);
	if(m == 10000000000)
		ans += (m%k == 1),m--;
	n = (-p%k+k)%k;
	for(int i = 1;i < 10;i++)
		b[i] = i;
	for(int i = 0;i < 10000;i++)
		for(int j = 0;j < 10;j++)
			b[(i<<3)+(i<<1)+j] = b[i]+j;
	LL lim = m/p,rem = m%p;
	for(LL i = 0;i <= rem;i++)
		a[(i-b[i])%k]++;
	w = (n*lim+b[lim])%k;
	if(w < p) ans += a[w];
	for(LL i = rem+1;i < p;i++)
		a[(i-b[i])%k]++;
	for(LL i = 0,j = 0;i < lim;i++,j += n)
	{
		w = (j+b[i])%k;
		if(w < p) ans += a[w];
	}
	printf("%lld",ans-1);
 	return 0;
}
```


---

## 作者：yiming564 (赞：5)

# [AT_arc052_d [ARC052D] 9](https://www.luogu.com.cn/problem/AT_arc052_d)

## $\text{Description}$

给定两个正整数 $k, m$，满足 $1 \leq k, m \leq 10 ^ {10}$。

求有多少个 $1 \leq x \leq m$，满足 $x$ 的各位之和 $\equiv x \pmod{k}$

## $\text{Solution}$

### 类似题目

- [P3773 [CTSC2017] 吉夫特](https://www.luogu.com.cn/problem/P3773)

### 约定与记法

- 定义 $\operatorname{popcnt}_k(x)$ 为 $x$ 在 $k$ 进制意义下的各位数之和。
  特别的，$k = 10$ 时，该函数也就等价于 $x$ 在 $10$ 进制下的各位之和。
- 定义 $\operatorname{MSB}_k(x)$ 为 $x$ 在 $k$ 进制意义下的最高位。
  特别的，$k = 10$ 时，该函数也就等价于 $x$ 在 $10$ 进制下的第一位数。

### 问题分析

#### 朴素算法

首先，我们容易发现一个显然的事实：

$$
\forall 1 \leq x \leq m, \operatorname{popcnt}_{10}(x) < 9 \times \log_{10}(m) + \operatorname{MSB}_{10}(m + 1)
$$

用通俗易懂的语言来说，就是 $\operatorname{popcnt}_{10}(x)$ 的上界只和 $m$ 的位数成正比，而当 $m = 10 ^ {10}$ 时，该函数的最大值也只有 $90$。

因此我们有一个显然的暴力，对于每一种满足上述不等式的 $d = \operatorname{popcnt}_{10}(x)$，枚举 $d + nk \leq m$，并检验 $\operatorname{popcnt}_{10}(d + nk)$ 是否等于 $d$，统计个数即为答案。

该算法的时间复杂度为 $O(\frac{m \log ^ 2 m}{k})$，且带有一个 $9$ 的常数，当 $k$ 较大时尚可接受，但如果 $k$ 较小则不行，考虑优化。

#### 优化

如果你做过 [P3773 [CTSC2017] 吉夫特](https://www.luogu.com.cn/problem/P3773)，你就会知道一个折半处理的 $\text{trick}$。

考虑将 $x$ 拆分为 $up + v$，则有如下的转化：

$$
\begin{aligned}
	\operatorname{popcnt}_{10}(x) &= x \\
	\operatorname{popcnt}_{10}(up + v) &= up + v \\
	\operatorname{popcnt}_{10}(u) + \operatorname{popcnt}_{10}(v) &= up + v \\
	\operatorname{popcnt}_{10}(v) - v &= up - \operatorname{popcnt}_{10}(u)
\end{aligned}
$$

则可以考虑先处理每个可能的 $v$，将 $\operatorname{popcnt}_{10}(v) - v$ 放入一个哈希表中。

对于每个可能的 $u$，直接在哈希表中查询 $up - \operatorname{popcnt}_{10}(u)$ 的出现次数即可。

时间复杂度为 $O(p + \frac{m}{p})$*，当 $p = \sqrt{m}$ 时理论最优。

（当然，为了图方便我写了 $p = 10 ^ 5$）

### $\text{Tricks and Corner Cases}$

- 细心的读者可能发现了，优化的时间复杂度甚至不带 $\log$，因为 $p$ 的值域较小，我们可以递推预处理 $\operatorname{popcnt}_{10}$。
- 粗心的作者可能火急火燎地打完代码，发现样例 $3$ 挂了，这是因为当 $u$ 取到最大值 $31415$ 时，$v \leq p \rightarrow v \leq 92653$，因此要注意在计算 $v$ 的时候提前把答案加上。
- 贪心的作者可能在调试时发现哈希表的下标溢出了，以为自己发现了 GDB 的 bug，但实际上是他自己把哈希表的类型设为了 $\texttt{int}$。

## $\text{Code}$

代码相当短小精悍，这是我写过最短的紫题之一。

```cpp
#include <bits/extc++.h>
const int64_t p = 1e5;
int64_t k, m; int cnt[p + 1];
__gnu_pbds::cc_hash_table<int64_t, int> sum;
int main()
{
	scanf("%ld %ld", &k, &m);
	int64_t ans = 0; int ll = std::min(p, m + 1), lh = m / p;
	for (int i = 0; i <= p; i++) cnt[i] = (cnt[i / 10] + i % 10) % k;
	for (int i = 0; i < ll; i++)
	{
		sum[(cnt[i] - i % k + k) % k]++;
		if (i == m % p) ans += sum[(lh * p - cnt[lh] + k) % k];
	}
	for (int i = 0; i < lh; i++) ans += sum[(i * p - cnt[i] + k) % k];
	printf("%ld", ans - 1);
	return 0;
}
```

---

## 作者：RedLycoris (赞：3)

题目翻译是错误的，正确的如下：

给定两个正整数 $K,M (1\le K,M \le 10^{10})$，你需要求出有多少个正整数 $N$ 满足 $1 \le N \le M$ 且 $N \equiv S_N (\bmod K) $，其中 $S_N$ 是 $N$ 的各位数字之和。

题解：

这个 $10^{10}$ 的数据范围并不常见，但是可以发现大概是根号的复杂度。

显然无法分块，考虑怎么做到根号分治。我们先对 $K$ 设定一个阈值 $T$，其中 $T$ 是 $\sqrt{M}$ 级别。


+ $K \ge T$ 

当 $1 \le N \le 10^{10}$ 时，最大的 $S_N$ 不过 $9\times 10=90$，所以我们可以去先枚举数字和 $S$，然后就可以发现，$\bmod K= S$ 的 $N$ 的个数不会超过 $\lfloor\frac{M}{K}\rfloor +1$ 个。直接枚举这些数就可以了。复杂度 $O(S_N\times \frac{M}{K})$。

+ $K \le T$

我们可以考虑把 $K$ 做为一维压到数位 dp 里了。令 $dp_{i,j,sm,0/1}$ 表示考虑到从高到低第 $i$ 位，此时的数 $\bmod K = j$，数字和为 $sm$，是否已经小于 $m$ 的数的个数。这样就可以 dp 了，复杂度 $O(\log k \times S_N\times K)$。

均衡一下取 $K=10000$ 最优。

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
using namespace std;
ll k,m,n;
int ee[13];
ll dp[13][10000][91][2];
inline void add(ll&x,ll y){x+=y;}
signed main(){
	cin>>k>>m;
	ll ans=0;ll tm=m;
	for(int i=1;;++i){
		ee[i]=tm%10;
		tm/=10;
		if(tm==0){
			n=i;
			break;
		}
	}
	reverse(ee+1,ee+n+1);
	if(k>=10000){
		for(int i=0;i<=90;++i){
			for(ll ee=i;ee<=m;ee+=k){
				ll t=ee,cnt=0;
				while(t){
					cnt+=t%10;
					t/=10;
				}
				if(cnt%k==i)++ans;
			}
		}
		cout<<ans-1<<'\n';
		return 0;
	}
	dp[1][0][0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<k;++j){
			for(int sm=0;sm<=90;++sm){
				{//f=0
					for(int t=0;t<ee[i];++t){
						if(sm+t<=90){
							add(dp[i+1][(j*10+t)%k][sm+t][1],dp[i][j][sm][0]);
						}
					}
					if(sm+ee[i]<=90)add(dp[i+1][(j*10+ee[i])%k][sm+ee[i]][0],dp[i][j][sm][0]);
				}
				{//f=1
					for(int t=0;t<10;++t)if(sm+t<=90)add(dp[i+1][(j*10+t)%k][sm+t][1],dp[i][j][sm][1]);
				}
			}
		}
	}
	for(int ee=0;ee<=90;++ee)add(ans,dp[n+1][ee%k][ee][0]),add(ans,dp[n+1][ee%k][ee][1]);
	cout<<ans-1<<'\n';
}
```

---

## 作者：Cx114514 (赞：2)

## 前置知识：根号分治、数位DP

考虑设一个阈值 $p$。

当 $k \le p$ 时，考虑数位DP。

定义 $f_{i,j,0/1}$ 表示满足“考虑最低的 $i$ 位，数字和模 $k$ 与其本身模 $k$ 的差为 $j$，是否考虑数字限制”的数字个数。

令数字 $m$ 最低的第 $i$ 位为 $dig_{i}$，则易得转移如下：

$f_{i,j,0} = \sum_{l=0}^{9} f_{i-1,j+l^{i-1}-l,0}$

$f_{i,j,1} = f_{i-1,j+dig_{i}^{i-1}-dig_{i},1}+\sum_{l=0}^{dig_{i}-1} f_{i-1,j+l^{i-1}-l,0}$

时间复杂度：$O\left (S p \log m  \right )$，其中 $S=10$。

当 $k>p$ 时，我们考虑任意一个的数字和都不超过 $90$。那么，我们便没有必要考虑模 $k$ 大于 $90$ 的数字，只需枚举其他数字直接判断即可。

时间复杂度：$O\left (S \frac{m}{p}  \log m  \right )$，其中 $S=90$。

$p$ 取 $5 \times 10^{5} $ 即可通过此题。

最终贴上代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int k, m, M, ans, cnt, dig[15], zhi_yin[15], f[15][500005][5];

int sum(int x)
{
	int res = 0;
	while (x)
	{
		res += (x % 10);
		x /= 10;
	}
	return res;
}

signed main()
{
	zhi_yin[0] = 1;
	for (int i = 1; i <= 10; i++)
		zhi_yin[i] = zhi_yin[i - 1] * 10;
	cin >> k >> m;
	M = m;
	while (M)
	{
		dig[++cnt] = M % 10;
		M /= 10;
	}
	if (k <= 500000)
	{
		f[0][0][0] = f[0][0][1] = 1;
		for (int i = 1; i <= cnt; i++)
		{
			for (int j = 0; j < k; j++)
			{
				for (int l = 0; l <= 9; l++)
					f[i][j][0] += f[i - 1][(j + (zhi_yin[i - 1] * l) - l) % k][0];
				for (int l = 0; l < dig[i]; l++)
					f[i][j][1] += f[i - 1][(j + (zhi_yin[i - 1] * l) - l) % k][0];
				f[i][j][1] += f[i - 1][(j + (zhi_yin[i - 1] * dig[i]) - dig[i]) % k][1];
			} 
		}
		cout << f[cnt][0][1] - 1 << endl;
	}
	else
	{
		for (int i = 0; i <= m / k; i++)
		{
			for (int j = 1; j <= 90; j++)
				if ((i * k + j) <= m)
				{
					int x = i * k + j;
					if (sum(x) == j) ans++;
				}
		}
		cout << ans << endl;
	}
	return 0;
} 
```

---

## 作者：Soh_paramEEMS (赞：0)

## 题目
给定两个正整数 $k,m$，满足 $1≤k,m≤10^{10}$。

求有多少个 $1≤x≤m$，满足 $x$ 的各位之和 $a \equiv x \pmod k$
## 思路
这是一道数位 dp 题目

其实两题的思路差不多，注意到**当 $k$ 很大**时，枚举各位数字和 $s_x \in [0,90]$、再枚举 $x$、然后记录余数相等的情况，是不会超时的。

于是考虑对 $k$ 分段：
### $k > 10^4$
可以做到 $\Theta \left ( 91 \left \lfloor \frac{m}{k} \right \rfloor \right )$ 比较无脑，不过最后记得答案减去 $1$，因为要求 $1≤x≤m$。

```cpp
ll ans=0;
for(ll s=0;s<=90;s++)
{
	for(ll i=s;i<=m;i+=k)
	{
		ll t=i,ss=0;
		while(t)
		{
			ss+=t%10;
			t/=10;
		}
		ans+=(ss%k==s%k);
	}
}
ans--;
```
### $k \leq 10^4$
考虑拆解 $m$ 的各位数字，然后搜索枚举。

考虑高位往低位枚举。

定义 $f_{len,ys,sum,op}$，表示数字长度为 $len$，余数为 $ys$，各位数字和为 $sum$，是否有数字达到 $m$ 的对应位（以防所枚举的数大于 $m$ ）的方案数。

记忆化搜索即可。

拆数：

```cpp
ll sol(ll x)
{
	ll tot=0,t=x;
	while(t)
	{
		sw[++tot]=t%10;
		t/=10;
	}
	memset(f,-1,sizeof(f));
	return dp(tot,1,0,0);
}
```
记忆化搜索：

```cpp
ll dp(ll len,bool op,ll sum,ll ys)
{
	if(len<=0)return (sum&&ys==sum%k);//余数相同产生 1 次贡献
	if(f[len][ys][sum][op]!=-1)return f[len][ys][sum][op];
	ll ret=0,t=(op?sw[len]:9ll);
	//如果前面的数位没有到达 m 的对应位 (op==0)，说明后面的数位无论填什么数，所枚举的数都小于 m
	//否则该数位最大值限制为 m 的对应位数值
	for(int i=0;i<=t;i++)
	ret+=dp(len-1,op&(i==t),sum+i,(ys*10+i)%k);
	f[len][ys][sum][op]=ret;
	return ret;
}
```
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=13,S=92,X=1e4;//1e10/1e6
ll k,m;
ll sw[N],f[N][X+2][S][2];
ll dp(ll len,bool op,ll sum,ll ys)
{
	if(len<=0)return (sum&&ys==sum%k);
	if(f[len][ys][sum][op]!=-1)return f[len][ys][sum][op];
	ll ret=0,t=(op?sw[len]:9ll);
	for(int i=0;i<=t;i++)
	ret+=dp(len-1,op&(i==t),sum+i,(ys*10+i)%k);
	f[len][ys][sum][op]=ret;
	return ret;
}
ll sol(ll x)
{
	ll tot=0,t=x;
	while(t)
	{
		sw[++tot]=t%10;
		t/=10;
	}
	memset(f,-1,sizeof(f));
	return dp(tot,1,0,0);
}
int main()
{
	scanf("%lld%lld",&k,&m);
	if(k<=X)
	{
		printf("%lld",sol(m));
		return 0;
	}
	ll ans=0;
	for(ll s=0;s<=90;s++)
	{
		for(ll i=s;i<=m;i+=k)
		{
			ll t=i,ss=0;
			while(t)
			{
				ss+=t%10;
				t/=10;
			}
			ans+=(ss%k==s%k);
		}
	}
	ans--;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

## [AT_arc052_d [ARC052D] 9](https://www.luogu.com.cn/problem/AT_arc052_d)

> 给定两个正整数 $k,m$，记 $s(x)$ 为 $x$ 在十进制下各数位之和，求 $\sum_{i=1}^{m} [i\equiv s(i)\pmod k]$。
>
> $1\le k,m\le 10^{10}$。

一种朴素的方法是枚举余数，暴力判断，时间复杂度 $O(\frac{mt}{k})$，其中 $t=90$ 为 $10^{10}$ 内各位之和的最大值。容易发现当 $k$ 较大，超过约 $10^4$ 时，这么做是可以通过的。

对于 $k$ 较小的情况，考虑数位 dp。设 $f(d,cur,sum,lead,full)$ 为从高位至低位考虑到第 $d$ 位，当前数为 $cur$，$s(cur)=sum$，当前是否有前导 $0$，当前是否取到上界，的满足条件的数的个数，其中称 $x$ 满足条件当且仅当 $x\equiv s(x)\pmod k$。注意到 $cur$ 的上界会取到 $10^{10}$，而满足条件只需要同余，并不需要具体的数，考虑将 $cur$ 和 $sum$ 都模 $k$ 并判断二者是否相等即可。时间复杂度 $O(ktw)$，其中 $t=90,w=10$。

```cpp
#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#define getchar() (_p==_q&&(_q=(_p=_b)+fread(_b,1,_s,stdin),_p==_q)?-1:*_p++)
#define putchar(x) ((_r-_o<_s)?(*_r++=x):(flush(),_r=_o,*_r++=x))
#endif
#define flush() fwrite(_o,_r-_o,1,stdout),fflush(stdout)
#define inline inline __attribute__((always_inline))
using namespace std;const int _s=1<<20;char _b[_s],_o[_s],*_p=_b,*_q=_b,*_r=_o;template<class T>inline bool fr(T&x){x=0;char c=0;bool f=0;do{if((c=getchar())==-1)return 0;if(c=='-')f=1;}while(c<48||c>57);do {x=x*10+c-48;if((c=getchar())==-1)break;}while(c>47&&c<58);if(f)x=-x;return 1;}template<class T>inline void fw(T x){char _d[40],_l=-1;if(x<0)x=-x,putchar('-');do _d[++_l]=x%10+48;while(x/=10);do putchar(_d[_l]);while(~--_l);}

#define int long long
const int Maxl = 11, Maxk = 1e4 + 3;

int K, M;

int dig[Maxl], len;
int f[Maxl][Maxk][Maxl * 9];
int dfs(int d, int cur, int sum, bool lead, bool full) {
	if (d == 0) return !lead && cur == sum;
	if (!lead && !full && ~f[d][cur][sum]) return f[d][cur][sum];
	int res = 0, top = full ? dig[d] : 9;
	for (int i = 0; i <= top; ++i) 
		res += dfs(d - 1, (cur * 10 + i) % K, (sum + i) % K, i == 0 && lead, full && i == top);
	if (!lead && !full) f[d][cur][sum] = res;
	return res;
}

inline int calc(int x) {
	len = 0; do dig[++len] = x % 10; while (x /= 10);
	fill(**begin(f), **end(f), -1);
	return dfs(len, 0, 0, 1, 1);
}

inline int sum(int x) {
	int sum = 0;
	do sum += x % 10; while (x /= 10);
	return sum;
}

inline int solve() {
	int cnt = 0;
	for (int s = 0; s <= 90; ++s)  // 各位之和最多为90，枚举余数并暴力判断
		for (int i = s; i <= M; i += K) 
			if (sum(i) == s) cnt++;
	return cnt - 1; // 0不算
}

signed main() {
	fr(K), fr(M);
	fw(K <= 1e4 ? calc(M) : solve());
	return flush(), 0;
}
```

---

## 作者：tuget (赞：0)

第一反应是数位 dp。

先不管它数据范围单考虑 dp 的设计，显然令 $f_{i,j,p,l}$ 表示第 $i$ 位，各个数位的数字之和模 $k$ 为 $j$，数字本身模 $k$ 为 $p$，最高位为 $l$ 的数字个数，时间复杂度是 $O(10k^2\log_{10}m)$，肯定要优化。

观察一下我们实际要用到的信息实际上是“各个数位的数字之和模 $k$”和“数字本身模 $k$”这两者之间的数量关系，最终求方案时也只需要两者相等，所以考虑作差，令 $f_{i,j,l}$ 表示第 $i$ 位，数字本身 $-$ 各个数位的数字之和的差模 $k$ 为 $j$，最高位为 $l$ 的数字个数，这样时间复杂度就是 $O(10k\log_{10}m)$ 的，可以过掉 $k \le 10^5$ 的数据。

剩下的怎么办？容易想到这时 $\lfloor \frac{m}{k} \rfloor \le 10^5$，同时数位和最大就只有 $90$，即只有 $\le 90$ 的余数是有用的，所以先枚举余数 $i$，然后枚举 $m$ 以内模 $k$ 为 $i$ 的数，验证枚举出的数的数位和是否等于 $i$ 即可，时间复杂度 $O(90 \times \lfloor \frac{m}{k} \rfloor\log_{10}m)$。

代码中变量和原题有所出入。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define DEBUG
#define db double
#define ll long long
#define usd unsigned
#define ull usd ll
#define i128 __int128
#define frp(in,m,st) freopen(in,m,st)
#define fio(in,out) frp(in,"r",stdin),frp(out,"w",stdout)
#ifndef DEBUG
char B[1<<20 | 5],*P,*G;
#define gc() ((P==G && (G=(P=B)+fread(B,1,1<<20,stdin)),P==G)?EOF:*P++)
#else
#define gc() getchar()
inline void bug(){cout<<endl;}
template<typename TS,typename ... T>
inline void bug(TS p,T ... x){cout<<p<<" ";bug(x...);}
#endif
template<class T>
inline T Read()
{
	T res=0,f=1;char c;
	for(;(c=gc())<'0' || c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9')res=(res<<3)+(res<<1)+(c^48),c=gc();
	return res*f;
}
#define read() Read<int>()
ll n,mod,mul=10,f[12][maxn][10],g[12][maxn],ans,num[12],tot;
inline int solve()
{
	int i;ll j,x,res;
	for(i=0;i<=90;++i)for(j=i;j<=n;j+=mod)
	{
		x=j,res=0;
		while(x)res+=x%10,x/=10;
		if(res%mod==i)++ans;
	}
	printf("%lld",ans-1);
	return 0;
}
int main()
{
	int i,j,k,s;
	s=mod=Read<ll>(),n=Read<ll>();
	if(mod>=1e5)return solve();
	while(n)num[tot++]=n%10,n/=10;
	for(i=0;i<=9;++i)f[0][0][i]=1;g[0][0]=10;
	for(i=1;i<tot;++i,mul*=10)
	{
		for(j=0;j<=mod;++j)for(k=0;k<=9;++k)
			f[i][(j+(mul*k-k))%mod][k]+=g[i-1][j];
		for(j=0;j<=mod;++j)for(k=0;k<=9;++k)g[i][j]+=f[i][j][k];
	}
	for(i=tot-1;~i;--i)
	{
		if(!i)ans+=f[i][mod-s][num[i]];
		for(j=0;j<num[i];++j)ans+=f[i][mod-s][j];
		s=(num[i]*(mul/=10)-num[i]+s)%mod,s==0&&(s=mod);
	}
	printf("%lld",ans-1);
	return 0;
}
```

---

## 作者：白简 (赞：0)

题意翻译是假的，骗了我十分钟（恼）。
### 题目大意
给定两个正整数 $k$ 和 $m$，需要求出有多少个正整数 $n$ 满足 $1 \leq n \leq m$ 且 $n \equiv S_n \pmod k$。

（$1 \leq m \leq 10^{10}$）
### 思路
范围 $10^{10}$，考虑根号复杂度。

考虑根号分治，设 $T$ 在 $\sqrt{m}$ 级别。

- $K \geq T$

容易发现，$S_n$ 的值很小，最大也不会超过 $90$。

那我们可以枚举数字和 $S_n$。

那么与 $S_n$ 关于 $k$ 同余的 $n$ 的个数不会超过 $\left\lfloor \frac{m}{k} \right\rfloor + 1$ 个。

直接枚举这些 $n$ 就可以了，复杂度达标。

- $K < T$

考虑把 $n \bmod k$ 的值作为一维放状态里，直接数位 DP 即可。
### Code
```cpp
// ARC052D
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 10500;

int n,m,k;

int dp[15][N][95][2];
// dp[i][j][k][l] : 
// 第 i 位,Sn % k = j,Sn = k,是否为上界 

int num[15],tot;

int dfs(int cnt,int mod,int sum,int lim) {
    if(cnt == 0) {
        if(mod == sum % k && sum != 0)
            return 1;
        
        return 0;
    }

    if(dp[cnt][mod][sum][lim] != -1) 
        return dp[cnt][mod][sum][lim];

    int Max = 9,ans = 0;

    if(lim)
        Max = num[cnt];
    
    for(int i = 0;i <= Max; i++)
        ans += dfs(cnt - 1,(mod * 10 + i) % k,sum + i,lim && i == Max);

    return dp[cnt][mod][sum][lim] = ans;
}

int Work(int x) {
    while(x) {
        tot ++;
        num[tot] = x % 10;
        x /= 10;
    }

    return dfs(tot,0,0,1);
}

signed main() {
    cin >> k >> m;

    memset(dp,255,sizeof(dp));

    if(k <= 1e4) 
        cout << Work(m) << "\n";
    else {
        int ans = 0;

        for(int i = 0;i <= 90; i++) {
            for(int j = i;j <= m; j += k) {
                int x = j,Sn = 0;

                while(x) {
                    Sn += x % 10;
                    x /= 10;
                }

                if(Sn % k == i)
                    ans ++;
            }
        }

        cout << ans - 1 << "\n";
        // 去掉 0 
    }
    return 0;
}
```

---

