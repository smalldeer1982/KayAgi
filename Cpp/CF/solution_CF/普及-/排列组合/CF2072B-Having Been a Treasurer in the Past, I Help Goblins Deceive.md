# Having Been a Treasurer in the Past, I Help Goblins Deceive

## 题目描述

完成第一个任务后，章人（Akito）离开了初始洞穴。不久后，他偶然发现了一个哥布林村落。

由于章人无处可居，他想了解房屋的价格。众所周知，哥布林将数字写作由字符 '-' 和 '\_' 组成的字符串，字符串 $ s $ 所表示的数值等于其所有等于字符串 "-\_-" 的不同子序列 $ ^{\text{∗}} $ 的数量（这与哥布林的面部特征非常相似）。

例如，字符串 $ s = $ "-\_--\_-" 表示的数值为 $ 6$，因为它包含 $ 6 $ 个 "-\_-" 子序列：

1. $ s_1 + s_2 + s_3 $
2. $ s_1 + s_2 + s_4 $
3. $ s_1 + s_2 + s_6 $
4. $ s_1 + s_5 + s_6 $
5. $ s_3 + s_5 + s_6 $
6. $ s_4 + s_5 + s_6 $

最初，哥布林在回答章人的问题时随机写了一个字符串数值 $ s$，但随后他们意识到想要从旅行者身上获取尽可能多的黄金。为此，他们要求你重新排列字符串 $ s $ 中的字符，使得该字符串所表示的数值最大化。

$ ^{\text{∗}} $ 字符串 $ a $ 的子序列是指通过删除 $ a $ 中若干（可能为 $ 0 $）个字符后得到的字符串 $ b$。若两个子序列是通过删除不同位置的字符得到的，则它们被视为不同的子序列。

## 说明/提示

第一个测试用例中，最优方案是将字符重排为 "-\_-"。这是唯一一个长度为 $ 3 $ 且至少包含一个 "-\_-" 子序列的字符串。

第二个测试用例中，只有一个字符 "-"，而构成子序列 "-\_-" 至少需要两个 "-"。这意味着无论如何重排，答案都是 $ 0$。

第七和第八个测试用例中，字符串长度 $ n < 3$，这意味着长度为 $ 3 $ 的子序列不存在。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
3
--_
5
__-__
9
--__-_---
4
_--_
10
_-_-_-_-_-
7
_------
1
-
2
_-```

### 输出

```
1
0
27
2
30
9
0
0```

# 题解

## 作者：_0_px (赞：4)

### 题意简述
重新排列字符串 $s$，使得 $s$ 中子序列 `-_-` 的个数最多，并输出最多的个数。
### AC思路
考虑贪心，把 $s$ 变成形如
$$\texttt{--} \dots \texttt{--\_\_} \dots \texttt{\_\_--} \dots \texttt{--}$$
的形式（先是若干个 `-`，再是若干个 `_`，最后是若干个 `-`）。

那么这个字符串的 `-_-` 子序列个数为：第一段 `-` 个数 $\times$ 中间               `_` 的个数 $\times$ 第二段 `-` 个数。  
其中 `_` 的个数是确定的，就得让第一段 `-` 个数 $\times$ 第二段 `-` 个数最大，那就让两段的个数尽量接近。设 `-` 的个数为 $cnt$，那么两段长度分别为 $\lfloor \frac{cnt}{2} \rfloor$ 和 $cnt - \lfloor \frac{cnt}{2} \rfloor$。
### AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, cnt;
string s;
int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t --){
        cin >> n >> s;
        cnt = 0; // 统计`-`的个数。
        for (int i = 0; i < n; ++ i){
            cnt += (s[i] == '-');
        }
        cout << (cnt / 2) * 1ll * (cnt - cnt / 2) * (n - cnt) << '\n';
    }
    return 0;
}
```
最后再说一句：**不开 `long long` 见祖宗！**

---

## 作者：Bai_R_X (赞：1)

## 思路
我们可以将中间设为下划线，左右两边减号平分，方案数为 $\lceil\frac{cnt1}{2}\rceil\times\lfloor\frac{cnt1}{2}\rfloor\times cnt2$（$cnt1$ 为减号的数量，$cnt2$ 为下划线的数量）。

明显的，根据基本不等式（当 $x+y=n$ 时，$x\times y$ 最大的解为 $x=y=\frac{n}{2}$），这个方案最优。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,i,cnt1,cnt2;
string s;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		cnt1=cnt2=0;
		for(i=0;i<s.size();i++)
		{
			if(s[i]=='-')cnt1++;
			else cnt2++;
		}
		cout<<((cnt1+1)/2)*(cnt1/2)*cnt2<<endl;
	}
	return 0;
}
```
建议评橙

---

## 作者：Lyw_and_Segment_Tree (赞：1)

## 题意简述

**本题多测**

有一个字符串 $s$，只有 `-` 和 `_` 两种字符，你需要重排 $s$，使得该字符串的子序列 `-_-` 的数量最大。

## 开始解题！

因为是仅仅只是要求子序列的数量最大，我们考虑贪心。

因为 `-_-` 中只有一个 `_`，所以我们考虑把所有 `_` 放在一起，然后把 `-` 放在两边。

那么我们假设原本的 $s$ 中有 $cnt$ 个 `-`，由于放在两边的 `-` 的数量之和为 $cnt$，不妨假设在最左边放 $a$ 个 `-`，那么就要在右边放 $cnt - a$ 个 `-`。

而在和一定（$a + cnt - a = cnt$） 的情况下，要使得 $a \times (cnt - a)$ 最大，这里用到一个结论，就是在和一定的情况下，两个数越接近结果越大。即要使得 $a$ 与 $cnt - a$ 尽量接近，两个数所以 $a$ 取 $\lfloor \dfrac{cnt}{2} \rfloor$ 即可。

那么总的匹配数即为 $a \times (cnt - a) \times (n - cnt) = \lfloor \dfrac{cnt}{2} \rfloor \times (cnt - \lfloor \dfrac{cnt}{2} \rfloor) \times (n - cnt)$，直接输出答案即可。

而计算 $cnt$ 直接扫一遍即可，是 $O(n)$ 的，算上多测的时间复杂度，则总的复杂度即为 $O(Tn)$。

最后注意一下多测的问题即可，上代码，缺省源较长，主要看主函数即可：

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

const ll maxn = 3;

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

namespace math {
    vector<ll> fac, inv;
    
    void init(ll sz) {
        fac.resize(sz + 5), inv.resize(sz + 5);
        
        fac[0] = fac[1] = inv[0] = inv[1] = 1;
        
        for (ll i = 2; i <= sz; i++) {
            fac[i] = fac[i - 1] % mod * i % mod;
            
            inv[i] = (mod - inv[mod % i] * (mod / i) % mod) % mod; 
        }
        
        for (ll i = 2; i <= sz; i++) {
            inv[i] *= inv[i - 1] % mod, inv[i] %= mod;
        }
    }
    
    ll A(ll n, ll m) {
        return fac[n] % mod * inv[n - m] % mod;
    }
    
    ll C(ll n, ll m) {
        return fac[n] % mod * inv[m] % mod * inv[n - m] % mod;
    }
}

ll qpow(ll a, ll b, ll m = 1) {
    if (b == 0) return 1 % m;
    
    ll ans = 1;
    
	while (b) {
        if (b & 1) ans = ans * a % m;
        
        a = a * a % m;
        
        b >>= 1;
    }
    
    return ans;
}

ll gcd(ll a, ll b) {
	return a == 0 || b == 0 ? max(a,b) : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a,b) * b;
}

ll lowbit(ll x) {
    return x & (-x);
}

ll popcount(ll x){
    ll res = 0;
    
    while (x) {
        x -= lowbit(x);
        
        res ++;
    }
    
    return res;
}

struct BIT {
	ll n = 0; std::vector<ll> c;
	
	BIT (ll sz) {
		n = sz, c.resize(sz + 5);
	};
	
	void add(ll x, ll y) {
		if (n == 0) {
			return ;
		} else {
			for (ll i = x; i <= n; i += lowbit(i)) {
				c[i] += y;
			}
		}
		
		return ;
	}
	
	ll sum(ll x) {
		ll res = 0;
		
		for (ll i = x; i; i -= lowbit(i)) {
			res += c[i];
		}
		
		return res;
	}
};

struct DSU { // 并查集
    ll n = 0; vector<ll> fa;
    
    DSU (ll sz) {
        n = sz, fa.resize(sz + 5);
    };
    
    void init() {
        if (n == 0) {
            return ;
        }
        
        for (ll i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }
    
    ll find(ll x) {
        return x == fa[x] ? x : find(fa[x]);
    }
    
    void merge(ll x, ll y) {
        x = find(x), y = find(y);
        
        if (x != y) {
            fa[x] = y;
        }
    }
};

// template<typename tp1,typename tp2,int N>
// struct Htb{
    // static constexpr int M=1e7+19;
    // int hd[M+3],to[N],ct;
    // tp1 ed[N];tp2 w[N];
    // static int hc(ul v){
        // v^=v<<13,v^=v>>7;
        // return (v^(v<<17))%M;
    // }
    // void ins(tp1 x,tp2 y){
        // int &p=hd[hc(x)];
        // ed[++ct]=x,to[ct]=p;
        // w[p=ct]=y;
    // }
    // int count(tp1 x){
        // for(int i=hd[hc(x)];i;i=to[i])
            // if(ed[i]==x)return 1;
        // return 0;
    // }
    // pair<tp2,bool>find(tp1 x){
        // for(int i=hd[hc(x)];i;i=to[i])
            // if(ed[i]==x)return mkp(w[i],true);
        // return mkp(0,false);
    // }
    // int operator[](tp1 x){
        // int &p=hd[hc(x)];
        // for(int i=p;i;i=to[i])
            // if(ed[i]==x)return i;
        // ed[++ct]=x,to[ct]=p;
        // return p=ct;
    // }
    // void clear(){while(ct)hd[hc(ed[ct--])]=0;}
// };

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, a[200005]; string s;

ll opt, l, r, ans = 0;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;
    
    ll T; cin >> T;
    
    while (T--) {
        cin >> n >> s; ll cnt = 0;
        
        for (i = 0; i < n; i++) cnt += (s[i] == '-');
        
        cout << (cnt / 2) * (cnt - cnt / 2) * (n - cnt) << endl;
    }
    
	return 0;
}
```

[AC record](https://codeforces.com/contest/2072/submission/307920976)

---

## 作者：wmrqwq (赞：1)

这是一篇视频题解。

![](bilibili:BV1FHP3eAEWj?t=144)

[代码链接](https://codeforces.com/contest/2072/submission/307829124)

---

## 作者：_second_coming_ (赞：1)

### 我的思路：

在每次输入循环中，定义一个字符串 `s`，用于存储输入的字符序列。再定义两个变量，`d` 和 `u`，分别用来统计字符串中 `-` 和 `_` 的数量，初始值都设为 0。

接着，遍历字符串 `s`，统计 `-` 和 `_` 的数量。如果 `-` 的数量少于 2 或 `_` 的数量少于 1，那么直接输出 0，因为无法形成 `-_-` 子序列。

如果满足条件，计算最大子序列数量。根据公式，最大子序列数量等于 `-` 的数量乘以 `_` 的数量，再乘以 `-` 的数量减 1 的一半，即 $d \times u \times \frac{d - 1}{2}$。

最后，输出结果。

### 证明上面的公式

首先，子序列 `-_-` 由三个部分组成：一个 `-`，一个 `_`，和另一个 `-`。为了形成这样的子序列，我们需要在字符串中找到至少两个 `-` 和一个 `_`。

假设字符串中有 $d$ 个 `-` 和 $u$ 个 `_`。我们需要从 $d$ 个 `-` 中选择 2 个，从 $u$ 个 `_` 中选择 1 个来形成 `-_-` 子序列。

从 $d$ 个 `-` 中选择 2 个的方式数为组合数 $C^d_2$，计算公式为：

$$
C^d_2 = \frac{d(d - 1)}{2}
$$

从 $u$ 个 `_` 中选择 1 个的方式数为 $u$。

---

由乘法原理，
将选择 `-` 的方式数和选择 `_` 的方式数相乘，得到形成 `-_-` 子序列的总方式数：

$$
\text{总方式数} = C^d_2 \times u = \frac{d(d - 1)}{2} \times u
$$

---

简化上述公式，得到：

$$
\text{总方式数} = d \times u \times \frac{d - 1}{2}
$$

### 代码！

```cpp
#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		string s;
		cin >> s;

		int d = 0, u = 0;  // 分别统计“-”和“_”的数量
		for (int i = 0; i < n; i++) {
			if (s[i] == '-')
				d++;
			else
				u++;
		}

		if (d < 2 || u < 1) {
			cout << 0 << endl;	// 如果“-”少于 2 或“_”少于 1，输出 0
		} else {
			cout << d * u * (d - 1) / 2 << endl;  // 计算并输出最大子序列数量
		}
	}
	return 0;
}
```

---

## 作者：X1RAY (赞：1)

非常简单的一道数学题哈，我们知道最大就是找下划线左右两边的乘积，把下划线都放在中间就可以了
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
       int n;
       cin>>n;
       string c;
       cin>>c;
       int a=0,b=0;
       for(int i=0;i<n;i++)
       {
	   	  if(c[i]=='-')
	   	  {
		      a++;	 	
		  }
		  else b++;
	   }
	   int x=a/2,y=a-x;
	   cout<<(long long)x*y*b<<endl;
    }
    return 0;
}
```

---

## 作者：Getaway_Car_follower (赞：0)

我们注意到我们最后的字符串肯定是形如 $\texttt{---}\cdots \texttt{-\_\_}\cdots\texttt{\_-}\cdots\texttt{---}$ 的，设三部分数量分别为 $a,b,c$，那么贡献为 $a\times b\times c$，设 $s$ 中有 $x$ 个 $\texttt{-}$ 和 $y$ 个 $\texttt{\_}$，那么很显然最大贡献为 $\lfloor\frac x2\rfloor\times \lceil \frac x2\rceil\times y$。

code：<https://codeforces.com/contest/2072/submission/309453360>

---

## 作者：RyanLi (赞：0)

传送门：洛谷 [CF2072B Having Been a Treasurer in the Past, I Help Goblins Deceive](https://www.luogu.com.cn/problem/CF2072B) | Codeforces [B. Having Been a Treasurer in the Past, I Help Goblins Deceive](https://codeforces.com/contest/2072/problem/B)

更佳的阅读体验：[CF2072B 题解](https://blog.ryanli.top/index.php/archives/252/)

---

**简要题意**：给定字符串只包含减号 `-` 和下划线 `_` 的字符串 $s$，重新排列 $s$ 中的所有字符，使得 $s$ 中组成字符串 `-_-` 的子序列数量最大，并输出这个数量。

`-_-` 只有中间有一个下划线 `_`。为了保证这样的子序列一定存在，下划线 `_` _一定是位于重新排列的字符串的中间位置的，即下划线 `_`_ 左右两端一定都有减号 `-`。

根据[均值不等式](https://baike.baidu.com/item/%E5%9D%87%E5%80%BC%E4%B8%8D%E7%AD%89%E5%BC%8F)，我们知道当左右两侧的减号 `-` 数量尽可能相等时，他们的乘积最大。

又根据[乘法原理](https://oi.wiki/math/combinatorics/combination/#%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86)，我们知道最终的子序列数量为左侧减号 `-` 的数量、右侧减号 `-` 的数量与下划线 `_` 数量的乘积。

因此，我们只需要统计减号 `-` 和下划线 `_` 的乘积，即可求出答案。

```cpp
#include <iostream>
using namespace std;

int t, n, cnt[2];
char c;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        cnt[0] = cnt[1] = 0;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> c, ++cnt[c == '-'];
        cout << 1ll * (cnt[1] >> 1) * cnt[0] * ((cnt[1] + 1) >> 1) << '\n';
    } return 0;
}
```

---

## 作者：RoamingDuck (赞：0)

### 思路

不难得到当 $b\gt c$ 时，$(a+b)\times (a-b)\lt (a+c)\times (a-c)$。

也就是说在两数和不变的情况下，两数差越大，乘积越小。

这个东西在后面会用得到。

首先来看，在这个世界中，数字是通过计算字符串的子序列数量得到的。而目标是为了让这个数字变得更大。

不妨先构造一个字符串，首先它有 $a$ 个连续的 `-` 字符，$b$ 个连续的 `_` 字符，之后又有 $c$ 个连续的 `-` 字符。那么它的 `-_-` 子序列数量是多少？

很显然是从 $a$ 个中选一个出来组合，$b$ 个中选一个出来组合，$c$ 个中选一个出来组合，也就是 $a\times b\times c$。

那为什么一定要连续呢？因为如果不连续，如果在第 $i$ 个字符开始匹配时，那么前面几个字符就被浪费了，因此我们追求让每个字符被组合的次数要尽可能多。而连续就恰好满足这个条件。

现在去考虑如何让 $a\times b\times c$ 最大。这就需要用到我们前面的定理了，将 $a$ 和 $c$ 分摊总的 `-` 字符数量即可。

因此得到思路：对于**总共**有 $x$ 个 `-` 字符，可以将 $x$ 平摊到中间的 $b$ 个连续的 `_` 字符的两侧，保证了 $a$ 与 $c$ 的差尽可能地小。

### 代码

[AC 记录](https://codeforces.com/contest/2072/submission/308389505)

不开 `long long` 见祖宗。

```
#include <iostream>
#include <string>
#define int long long
const int N = 2e5 + 5;
int T, n, a, b;
std::string s;
void Solve () {
  a = b = 0; // 多测初始化
  std::cin >> n >> s;
  for ( int i = 0; s[i]; i ++ ) {
    if ( s[i] == '-' ) a ++;
    else b ++;
  }
  std::cout << ( a >> 1 ) * ( a - ( a >> 1 ) ) * b;
  std::cout << '\n';
}
signed main () {
  std::cin.tie ( 0 ) -> sync_with_stdio ( false );
  std::cin >> T;
  while ( T -- ) Solve ();
  return 0;
}
```

---

## 作者：yhl110804 (赞：0)

很显然的贪心思路，将 ```-``` 均匀地放在 ```_``` 的两侧，这样计算出的结果最大。由于 $N \leq 2 \times 10^5$ 所以要开 ```long long```。

### Code :
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
   int x=0,f=1;char ch=getchar();
   while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
   while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
   return x*f;
}
void write(int x)
{
   if(x<0)putchar('-'),x=-x;
   if(x<10)putchar(x+'0');
   else write(x/10),putchar(x%10+'0');
}
const int N=1e1;
const int mod=1e9+7;
int T;
string s;
int n;
int len1,len2;
signed main(){
	T=read();
	while(T--){
		n=read();
		cin>>s;
		int len=s.size();
		for(int i=0;i<len;i++)
		if(s[i]=='-')len1++;
		else len2++;
		int maxn=0;
		for(int i=1;i<=len1-1;++i)
		maxn=max(maxn,i*(len1-i));
		cout<<maxn*len2<<"\n";
		len1=len2=0;
	}
    return 0;
}

```

---

