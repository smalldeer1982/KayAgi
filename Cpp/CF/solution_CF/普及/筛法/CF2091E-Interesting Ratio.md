# Interesting Ratio

## 题目描述

最近，Misha 在 IT Campus "NEIMARK" 的夏令营中学习了新课题 —— 欧几里得算法。

当发现 $a \cdot b = \text{lcm}(a, b) \cdot \text{gcd}(a, b)$ 时，他有些惊讶。其中 $\text{gcd}(a, b)$ 是 $a$ 和 $b$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)，而 $\text{lcm}(a, b)$ 是[最小公倍数 (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple)。Misha 想到既然 LCM 和 GCD 的乘积存在，或许它们的商也值得研究：$F(a, b) = \frac{\text{lcm}(a, b)}{\text{gcd}(a, b)}$。

例如，他取 $a = 2$ 和 $b = 4$，计算得到 $F(2, 4) = \frac{4}{2} = 2$，结果是一个质数（一个数如果恰好有两个因数则为质数）！现在他认为当 $a < b$ 且 $F(a, b)$ 是质数时，这个比值 $F(a, b)$ 是"有趣的比值"。

由于 Misha 刚接触数论，他需要你帮忙计算 —— 满足 $F(a, b)$ 是"有趣的比值"且 $1 \leq a < b \leq n$ 的不同数对 $(a, b)$ 有多少个？

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
5
10
34
10007```

### 输出

```
4
11
49
24317```

# 题解

## 作者：Collapsarr (赞：5)

# CF2091E Interesting Ratio 题解

### 解一：

题目中已经给了我们提示：$a\times b=\operatorname{lcm}(a,b)\times \gcd(a,b)$，那我们首先考虑将 $\operatorname{F}$ 函数进行变化：
$$
\operatorname{F}(a,b) = \frac{\operatorname{lcm}(a,b)}{\gcd(a,b)} = \frac{\frac{a\times b}{\gcd(a,b)}}{\gcd(a,b)} = \frac{a\times b}{\gcd(a,b)^2}
$$
题目中要求我们使得函数 $\operatorname{F}$ 的值是一个质数，因为质数有且仅有 $1$ 和他自己两个因数，所以我们考虑将 $\operatorname{F}$ 函数拆开：
$$
\operatorname{F}(a,b) = \frac{a}{\gcd(a,b)} \times \frac{b}{\gcd(a,b)}
$$
不妨令 $a\lt b$，又因为 $\operatorname{F}(a,b)$ 必须有一个因子为 $1$，则得 $\frac{a}{\gcd(a,b)}=1,\frac{b}{\gcd(a,b)} = p$，其中 $p$ 为某一个质数。

因为 $\gcd(a,b)$ 的值可以任取，所以满足条件的 $(a,b)$ 的个数仅和 $p$ 的大小有关系，考虑枚举每一个小于等于 $n$ 的质数 $p$，则可取的 $(a,b)$ 的个数为 $\lfloor \frac{p}{n} \rfloor$，所以我们可以预处理出来所有小于等于 $10^7$ 的质数，每一次询问即可做到 $O(n)$ 的复杂度处理。

### 解二：

考虑打表（最近 CF 打表打糊涂了，看什么都是打表……）：

对样例中的 $10\ 5$ 数据打表后我们可以发现满足条件的 $(a,b)$ 分别为：

$(1,2)$ $(1,3)$ $(1,5)$ $(1,7)$ 

$(2,4)$ $(2,6)$ $(2,10)$ 

$(3,6)$ $(3,9)$

$(4,8)$ 

$(5,10)$ 

可以发现满足条件的 $(a,b)$ 在除掉自己的 $\gcd(a,b)$ 后一定为 $(1,p)$ 的形式（$p$ 为某一个质数），所以可取的 $(a,b)$ 的个数为 $\lfloor \frac{p}{n} \rfloor$，剩余同上。

### CODE

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define intt __int128

int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while(ch<'0'||'9'<ch)
	{
		if(ch=='-')
		{
			f = -1;
		}
		ch = getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		x = (x<<3) + (x<<1) + ch - '0';
		ch = getchar();
	}
	return x * f;
}

const int N = 1e7 + 10,M = N - 10,inf = 1e18;

int prime[N],n,ans;
bool falg[N];

void primes()//欧拉筛板
{
	for(int i = 2;i<=M;i++)
	{
		if(!falg[i])
		{
			prime[++prime[0]] = i;
		}
		for(int j = 1;j<=prime[0]&&i*prime[j]<=M;j++)
		{
			falg[i*prime[j]] = 1;
			if(i%prime[j]==0)
			{
				break;
			}
		}
	}
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	primes();
    int T = read();
    while(T--)
	{
    	n = read();
    	ans = 0;
    	for(int i = 1;i<=prime[0]&&prime[i]<=n;i++)
		{
			ans += n / prime[i];
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：Error_Eric (赞：3)

### Statement

求小于等于 $n$ 的所有自然数组成的数对 $(a,b)$ 中，$\mathrm{lcm}(a,b)\over\gcd(a,b)$ 是质数的无序对的个数。

### Solution

注意到 $a=b$ 肯定不行，那么不妨令 $a<b$。

${\mathrm{lcm}(a,b)\over\gcd(a,b)} = {\mathrm{lcm}(a,b)\gcd(a,b)\over\gcd(a,b)\gcd(a,b)}={ab\over\gcd(a,b)\gcd(a,b)} = {a\over \gcd(a,b)}\times {b\over\gcd(a,b)}$。

两个整数的乘积是质数只有一种情况：小的那个是 $1$。因此 ${a\over\gcd(a,b)} = 1$，也就是说 $a = \gcd(a, b), b= \mathrm{lcm}(a, b)$。

换言之 $(a,b)$ 合法当且仅当 $b\over a$ 是个质数。那么对于每个 $b$，合法的 $a$ 的和 $b$ 的质因数一一对应。

枚举 $b$ 可以得到答案就是 $d(i)$ 的前缀和，其中 $d(i)$ 表示 $i$ 的不同质因数个数。

$d$ 能够有很多方法处理。一个比较简单的做法是做个线性筛。每次用质数 $p$ 筛合数的时候，若合数的另外一个乘数 $q$ 不是 $p$ 的倍数，则 $d(pq) = d(q)+1$。否则 $d(pq) = d(q)$。答案输出 $d$ 的前缀和即可。

### Code

[Link](https://vjudge.net/solution/59511618)

---

## 作者：ZMQ_Ink6556 (赞：2)

## 题解：CF2091E Interesting Ratio

### 题意简述

找出所有数对 $(a , b)$，使得 $1 \le a < b \le n$ 且 $\frac{\operatorname{lcm}(a , b)}{\gcd(a , b)}$ 为质数。

### 解题思路

#### 结论：

若 $\frac{\operatorname{lcm}(a , b)}{\gcd(a , b)}$ 为质数，则 $\frac{b}{a}$ 是质数。

#### 证明：

- 首先假设 $a , b$ 互质，则 $\frac{\operatorname{lcm}(a , b)}{\gcd(a , b)} = ab$，不成立。
- 其次，若 $b$ 不是 $a$ 的倍数，则 $a$ 可以表示为 $p_1 \times p_2$，$b$ 可以表示为 $p_1 \times p_3$，其中 $p_1 , p_2 , p_3$ 均为整数。
- 此时 $\frac{\operatorname{lcm}(a , b)}{\gcd(a , b)} = \frac{p_1 \times p_2 \times p_3}{p_1} = p_2 \times p_3$，不是质数。
- 最后只剩下 $b$ 是 $a$ 的倍数。此时 $\frac{\operatorname{lcm}(a , b)}{\gcd(a , b)} = \frac{b}{a}$。
- 证毕。

#### 做法：

首先**预处理出数据范围（$10^7$）内所有质数**，欧拉筛或埃氏筛均可。

对于每个测试点，从 $1$ 到 $\frac{n}{2}$ 枚举 $a$。使用一个指针表示现在能取到的最大的质数。可以发现，**随着 $a$ 的增大，指针不会上升**。这保证了复杂度是 $O(n)$。

最终复杂度：$O(n + V \log V)$（埃氏筛）或 $O(n + V)$（欧拉筛）。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;
long long t , n , cnt , prime[20000005] , tmp , ans;
bitset<20000005> vis; 
inline void ycl() 
{
	for(int i = 1 ; i <= 20000000 ; i++)
	{
		vis[i] = 1;
	}
	vis[1] = 0;
	for(long long i = 2 ; i <= 20000000 ; i++)
	{
		if(vis[i])
		{
			cnt++;
			prime[cnt] = i;
			for(long long j = 1 ; i * j <= 20000000 ; j++)
			{
				vis[i * j] = 0;
			}
		}
	}
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ycl(); 
	cin >> t;
	while(t--)
	{
		cin >> n;
		ans = tmp = 0;
		while(prime[tmp + 1] <= n)
		{
			tmp++;
		}
		for(long long i = 1 ; i <= n ; i++)
		{
			while(i * prime[tmp] > n)
			{
				tmp--;
			}
			ans += tmp;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：zhangli828 (赞：1)

## 题目大意
给你一个整数 $n$，让你求出有多少组 $(a,b)$ 满足 $1\le a<b\le n$ 且 $\frac{\text{lcm}(a,b)}{\text{gcd}(a,b)}$ 为质数。
## 题目解法
我们发现 $\text{lcm}(a,b)=a\times b\div\text{gcd}(a,b)$，所以可以得到 $\frac{\text{lcm}(a,b)}{\text{gcd}(a,b)}=\frac{a\times b}{2\times\text{gcd}(a,b)}$，所以 $b\div\text{gcd}(a,b)$ 一定为质数，所以我们可以枚举质数 $p$，然后 $ans$ 每次加上 $\lfloor\frac{n}{p}\rfloor$ 即可。对于那些质数，我们可以提前用埃氏筛把所有小于 $10^7$ 的质数处理出来，这样后面可以 $O(\text{质数数量})$ 处理出答案。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 1e7 + 10;

int vis[kMaxN], t, n, ans;
vector<int> p;

void P() {  // 用埃氏筛提前预处理质数
  for (int i = 2; i < kMaxN; i++) {
    if (!vis[i]) {
      p.push_back(i);
    }
    for (int j = 0; j < p.size() && i * p[j] < kMaxN; j++) {
      vis[i * p[j]] = 1;
      if (!(i % p[j])) {
        break;
      }
    }
  }
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t, P(); t--; ans = 0) {
    cin >> n;
    for (int i = 0; i < p.size() && p[i] <= n; i++) {  // 枚举质数
      ans += n / p[i];  // 计算每个质数可以满足的对数数量
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：Aegleseeker_ (赞：1)

随机 VP Div3，随机写题解。

$\frac{\operatorname{lcm}(a,b)}{\gcd(a,b)}=\prod\limits_{p\in \operatorname{Prime}}p^{cnt_{b,p}-cnt_{a,p}}$

其中钦定 $a<b$，$cnt_{x,y}$ 代表 $x$ 中能分解出几个质数 $y$。

看不懂的去学 $\gcd$ 和 $\operatorname{lcm}$ 的那个本质质因数表示。

要令上面那个东西为质数，根据质数定义可以发现条件是：

当且仅当只能存在一个 $p$ 满足 $cnt_{b,p}-cnt_{a,p}=1$，其它 $p$ 满足 $cnt_{b,p}-cnt_{a,p}=0$。

也就是说我们要统计 $\sum\limits_{1\le a<b\le n} [b=p\times a,p\in \operatorname{Prime}]$ 这个东西，不难发现其实就是每个数的质因子个数的前缀和。

下面给出一种基于素数密度的思维难度低的 $O(n+q)$ 做法。

考虑线性筛出所有质数 $p_i$，枚举每个 $p_i$ 和其倍数 $p_i\times j$，直接对答案加一。最后求前缀和即可。

复杂度为 $O(\frac{n}{\ln}\times \ln)=O(n)$。

（第一个是素数密度，第二个是调和级数）

---

## 作者：c_legg (赞：1)

## 题意

给你一个 $n$，要求整数对 $(a, b)$ 使得 $1\le a\lt b\le n$ 且 $\frac{\text{lcm}(a, b)}{\gcd(a, b)}$ 为质数的数量。

## 思路

根据唯一分解定理，令 $a=\sum p_i^{x_i}$ 同时 $a=\sum p_i^{y_i}$，则 $\text{lcm}(a, b)=\sum p_i^{\max(x_i,y_i)}$ 且 $\gcd(a, b)=\sum p_i^{\min(x_i,y_i)}$。

可得 $\frac{\text{lcm}(a, b)}{\gcd(a, b)}=\sum p_i^{\max(x_i,y_i)-\min(x_i,y_i)}$。

又可以发现，$\frac{\text{lcm}(a, b)}{\gcd(a, b)}$ 为质数的冲要条件是只有一个 $\max(x_i,y_i)-\min(x_i,y_i)=1$ 且其他 $\max(x_i,y_i)-\min(x_i,y_i)=0$。

那就是说，因为 $a\lt b$，所以 $b=a\rho$，其中 $\rho$ 是一个质数。

那先跑个埃氏筛好了！

然后又发现对于每个 $\rho$，$a$ 和 $b$ 的个数为 $\lfloor\frac{n}{\rho}\rfloor$，所以枚举 $\rho$ 即可。

## 代码

埃氏筛复杂度 $\Theta(\text{Max}\log\log\text{Max})$，计算 $\text{ans}$ 复杂度 $\Theta(n)$，所以总复杂度为 $\Theta(\text{Max}\log\log\text{Max}+nt)$。

``` cpp
#include <bits/stdc++.h>
#define Max 10000000
#define ll long long
using namespace std;
 
int t, n;
 
int pris[Max], cnt;
 
bitset<Max+100> ispri;
 
void slove() {
    cin>>n;
    ll ans(0);
    for(int i(0); i<cnt && pris[i]<=n; i++) {
        ans+=n/pris[i];
    }
    cout<<ans<<"\n";
}
 
int main() {
    for(int i(2); i<=Max; i++) ispri[i]=1;
    for(int i(2); i<=Max; i++) {
        if(!ispri[i]) continue;
        pris[cnt++]=i;
        if((ll)i*i>Max) continue;
        for(int j(i*i); j<=Max; j+=i) ispri[j]=0;
    }
 
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    
    cin>>t;
    
    while(t--) slove();
    return 0;
}
```

---

## 作者：__O_v_O__ (赞：1)

套路地，我们设 $\gcd(a,b)=g$，那么 $a=gx,b=gy$，其中 $(x,y)=1$。

考虑 $F(a,b)=\frac{gxy}{g}=xy$，因为它是质数，所以 $x=1$，且 $y$ 也为质数（如果 $x,y$ 均大于 $1$，那么 $F(a,b)$ 至少有 $4$ 个因数，矛盾）。

也就是说，满足条件的 $(a,b)$ 可以表示为 $(i,ki)$ 的形式，其中 $k$ 是一个质数。现在加上 $1\le a,b\le n$ 的条件，我们考虑枚举 $i$，计算此时 $k$ 的上界 $\left\lfloor\frac{n}{i}\right\rfloor$，然后答案加上 $1\sim\left\lfloor\frac{n}{i}\right\rfloor$ 中的质数个数即可。线性筛+前缀和可以简单处理。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e7+1;
int t,n,p[N],pn,su[N];
bool fl[N];
void pre(){
	for(int i=2;i<N;i++){
		if(!fl[i])p[++pn]=i;
		for(int j=1;j<=pn&&i*p[j]<N;j++){
			fl[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	for(int i=2;i<N;i++)
		su[i]=su[i-1]+(!fl[i]);
}
signed main(){
	ios::sync_with_stdio(0);
	pre();
	cin>>t;
	while(t--){
		cin>>n;
		int an=0;
		for(int i=1;i<=n;i++){
			int li=n/i;
			an+=su[li];
		}
		cout<<an<<'\n';
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

显然，$\frac{\operatorname{lcm}(a,b)}{\gcd(a,b)}=\frac{a}{\gcd(a,b)}\times\frac{b}{\gcd(a,b)}$。

要想这个数为质数，那必定有一者为 $1$，另一者为质数。也就是说，如果令 $a<b$，那么 $a\mid b,\frac{b}{a}\in\mathbb{P}$。显然满足条件的 $a$ 的个数为 $b$ 的质因数个数，可以线性筛。

总复杂度 $O(n+V)$，$V=10^7$，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, cnt[10000005];
int p[10000005], c; bool isp[10000005];
inline void prep() {
	for (int i = 2;i <= 1e7;++i) {
		if (!isp[i]) p[++c] = i, cnt[i] = 1;
		for (int j = 1;j <= c && i * p[j] <= 1e7;++j) {
			isp[i * p[j]] = 1;
			if (i % p[j] == 0) {
				cnt[i * p[j]] = cnt[i];
				break;
			}
			cnt[i * p[j]] = cnt[i] + 1;
		}
	}
}
signed main() {
	ios::sync_with_stdio(0); prep();
	for (int i = 1;i <= 1e7;++i) cnt[i] += cnt[i - 1];
	for (cin >> t;t;t--) cin >> n, cout << cnt[n] << endl;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 开始解题！

相当基础的数论，很好想的一个东西。

不妨设 $d = \gcd(a, b)$，则 $a = dx, b = dy$，其中 $\gcd(x, y) = 1$。

那么此时 $\text{lcm}(a, b) = dxy$，即可得出 $F(a, b) = xy$，又 $a < b$，则 $x < y$，要使 $xy$ 为质数，则结合 $x < y$，可以发现 $x = 1$ 且 $y$ 为质数。

那么我们可以得到表达式 $1 \le b \le n$，即 $1 \le dy \le n$，就有 $1 \le d \le \lfloor \dfrac{n}{y} \rfloor$，即对于每个素数 $y$ 会产生 $\lfloor \dfrac{n}{y} \rfloor$ 个答案。

所以我们可以线性筛预处理一下素数，然后枚举 $y$，统计答案即可。

做完了。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define vec vector
#define pll pair<ll, ll>
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

namespace fastio {
    char buf[1 << 21], *p1 = buf, *p2 = buf;
	
    const ll getc() {
        return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
    }
	
    const ll read() {
        ll x = 0, f = 1;
		
        char ch = getc();
		
        while (ch < '0' || ch > '9') {
            if (ch == '-') f = -1; ch = getc();
        }
		
        while (ch >= '0' && ch <= '9') {
            x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
        }
		
        return x * f;
    }
	
    const void write(ll x) {
        if (x < 0) {
            putchar('-'), x = -x;
        }
		
        ll sta[35], top = 0;
	    
        do {
            sta[top++] = x % 10, x /= 10;
        } while (x);
	    
        while (top) putchar(sta[--top] + 48);
    }
}

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, a[200005]; string s;

ll opt, l, r, ans = 0;

ll p[10000005], tot = 0; bitset<10000005> vis;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;

    // vis[1] = 1;   

    for (i = 2; i <= 10000000; i++) {
        if (!vis[i]) p[++tot] = i;

        for (j = 1; j <= tot && i * p[j] <= 10000000; j++) {
            vis[i * p[j]] = 1;

            if (i % p[j] == 0) {
                break;
            }
        }
    }

    ll T = rd();

    while (T--) {
        n = rd(), ans = 0;

        for (i = 2; i <= n; i++) {
            if (!vis[i]) ans += n / i;
        }

        wt(ans), puts("");
    }

    return 0;
}
```

[AC record](https://codeforces.com/contest/2091/submission/312805677)

---

## 作者：lw393 (赞：0)

对于这道题，我们发现可以直接使用 OEIS 大法。本题答案为 A013939。

对于每个 $n$ 有 $ans = \sum_{i=1}^n \omega(i) = \sum_{i=1}^n \pi(\lfloor \frac{n}{i}\rfloor)$。

证明：($P$ 为全体质数集)

$$\sum_{i=1}^n \omega(i) = \sum_{p\in P,p\le n}\lfloor\frac{n}{p}\rfloor$$

$$\sum_{i=1}^n \pi(\lfloor\frac{n}{i}\rfloor) = \sum_{i=1}^n\sum_{p\in P,p\le \lfloor \frac{n}{i} \rfloor}1=\sum_{p\in P,p\le n}\lfloor\frac{n}{p}\rfloor$$

$$\therefore \sum_{i=1}^n \omega(i) = \sum_{i=1}^n \pi(\lfloor\frac{n}{i}\rfloor)$$

所以直接做一遍筛法即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e7 + 5;

int prime[N], is_prime[N], cnt;

void euler(int n){
    for(int i = 2; i <= n; i++){
        is_prime[i] ^= 1;
        if(is_prime[i] == 1) { prime[++cnt] = i; }
        for(int j = 1; j <= cnt && i * prime[j] <= n; j++){
            is_prime[i * prime[j]] = 1;
            if(i % prime[j] == 0) break; 
        }
    }
    for(int i = 1; i <= n; i++) is_prime[i] += is_prime[i - 1];
}

void solve(){
    int n;
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n; i++) ans += is_prime[n / i];
    cout << ans << '\n';
}

int main(){
    euler(N - 1);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：_299817_ (赞：0)

## Part 0：前言

感觉 E 和 F 的 gap 很大啊。

## Part 1：思路

观察题目给的式子 $F(a, b) = \frac{\operatorname{lcm}(a, b)}{\gcd(a, b)}$，因为 $\operatorname{lcm}(a,b)=\frac{a\times b}{\gcd(a,b)}$，故可以推导出：$F(a, b)=\frac{a}{\gcd(a, b)}\times\frac{b}{\gcd(a, b)}$。

我们要让上面的那个式子是一个质数，我们又知道它由两个数相乘而得，所以两个乘数就一定一个是质数一个是 $1$，而且题目中又给了 $a<b$，所以 $\frac{a}{\gcd(a,b)} = 1$，也就是 $a = \gcd(a, b)$，那么 $\frac{b}{a}$ 一定是一个质数，于是我们枚举质数 $p$，那么看有多少个 $a$ 满足 $p\times a \le n$ 即可。

这里求质数用的是埃筛。

## Part 2：代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#include<list>
#include<cstdint>
using namespace std;
#define rep(i, l, r) for(i32 i = (i32)(l); i <= (i32)(r); i++)
#define per(i, l, r) for(i32 i = (i32)(l); i >= (i32)(r); i--)
#define FILEIO(INNAME, OUTNAME) freopen(INNAME".in", "r", stdin), freopen(OUTNAME".out", "w", stdout)
#define sort stable_sort
#define map unordered_map
#ifdef QwQ_ATM
    #define Debug(x) cout << "---------- #Debug " << x << " ----------" << endl
    #define DDebug(s, x) cout << s << x
    #define Output(x) cout << x
#else
    #define Debug(x) 1
    #define DDebug(s, x) 1
    #define Output(x) 1
    #define endl '\n'
    #include<bits/stdc++.h>
#endif
#define int long long
typedef pair<int, int> pii;
using i32 = int32_t;
using i64 = int64_t;
const int MAXN = 10000000;

bitset <10000010> vis;
int prime[5000010];
int cnt;

void primes(){
    vis.set();
    vis[0] = 0, vis[1] = 0;
    for(int i = 2; i * i <= MAXN; i++){ if(vis[i]){ for(int j = i << 1; j <= MAXN; j += i) vis[j] = 0; } }
}

void solve(){
    int n;
    cin >> n;
    int aans = 0;
    for(int i = 1; prime[i] <= n && i <= cnt; i++){
        aans += n / prime[i];
    }
    cout << aans << endl;
}

i32 main(){
    #ifdef QwQ_ATM
        FILEIO("input", "output");
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    primes();
    rep(i, 1, MAXN){
        if(vis[i] == 1){
            prime[++cnt] = i;
        }
    }
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
```

---

