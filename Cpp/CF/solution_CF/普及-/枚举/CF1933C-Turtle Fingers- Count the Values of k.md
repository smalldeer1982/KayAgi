# Turtle Fingers: Count the Values of k

## 题目描述

You are given three positive integers $ a $ , $ b $ and $ l $ ( $ a,b,l>0 $ ).

It can be shown that there always exists a way to choose non-negative (i.e. $ \ge 0 $ ) integers $ k $ , $ x $ , and $ y $ such that $ l = k \cdot a^x \cdot b^y $ .

Your task is to find the number of distinct possible values of $ k $ across all such ways.

## 说明/提示

In the first test case, $ a=2, b=5, l=20 $ . The possible values of $ k $ (and corresponding $ x,y $ ) are as follows:

- Choose $ k = 1, x = 2, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 1 \cdot 2^2 \cdot 5^1 = 20 = l $ .
- Choose $ k = 2, x = 1, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 2 \cdot 2^1 \cdot 5^1 = 20 = l $ .
- Choose $ k = 4, x = 0, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 4 \cdot 2^0 \cdot 5^1 = 20 = l $ .
- Choose $ k = 5, x = 2, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 5 \cdot 2^2 \cdot 5^0 = 20 = l $ .
- Choose $ k = 10, x = 1, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 10 \cdot 2^1 \cdot 5^0 = 20 = l $ .
- Choose $ k = 20, x = 0, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 20 \cdot 2^0 \cdot 5^0 = 20 = l $ .

In the second test case, $ a=2, b=5, l=21 $ . Note that $ l = 21 $ is not divisible by either $ a = 2 $ or $ b = 5 $ . Therefore, we can only set $ x = 0, y = 0 $ , which corresponds to $ k = 21 $ .

In the third test case, $ a=4, b=6, l=48 $ . The possible values of $ k $ (and corresponding $ x,y $ ) are as follows:

- Choose $ k = 2, x = 1, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 2 \cdot 4^1 \cdot 6^1 = 48 = l $ .
- Choose $ k = 3, x = 2, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 3 \cdot 4^2 \cdot 6^0 = 48 = l $ .
- Choose $ k = 8, x = 0, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 8 \cdot 4^0 \cdot 6^1 = 48 = l $ .
- Choose $ k = 12, x = 1, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 12 \cdot 4^1 \cdot 6^0 = 48 = l $ .
- Choose $ k = 48, x = 0, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 48 \cdot 4^0 \cdot 6^0 = 48 = l $ .

## 样例 #1

### 输入

```
11
2 5 20
2 5 21
4 6 48
2 3 72
3 5 75
2 2 1024
3 7 83349
100 100 1000000
7 3 2
2 6 6
17 3 632043```

### 输出

```
6
1
5
12
6
11
24
4
1
3
24```

# 题解

## 作者：OPEC (赞：5)

# [Turtle Fingers: Count the Values of k](https://www.luogu.com.cn/problem/CF1933C)
这道题 $a$ 和 $b$ 都很小，而 $l$ 却很大。

所以枚举 $x$ 和 $y$，计算 $k$ 就可以了。

这里是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
signed main()
{
	//不要抄题解 QAQ
	fst
	cin>>t;
	while(t--)
	{
		int a,b,l;
		cin>>a>>b>>l;
		set<int> ans;
		for(int x=0,ax=1;ax<=l;x++,ax*=a)
		{
			for(int y=0,by=1;by<=l;y++,by*=b)
			{
				int k=l/(ax*by);
				if(k*ax*by==l)
				{
					ans.insert(k);
				}
			}
		}
		cout<<ans.size()<<'/n';
	}
	return 0;
}
```

---

## 作者：szhqwq (赞：2)

## 思路

考虑枚举。

因为 $a,b$ 最小为 $2$，$l$ 最大为 $10^6$，所以可以枚举 $x,y$ 统计答案。那么我们需要考虑一下 $x,y$ 枚举的上界，为了使答案能够全部统计到，我们需要找到一个最小的 $n$，使得 $a^n \ge l$，以及一个最小的 $m$，使得 $b^m \ge l$。很显然，$n = \lceil\log_{a}l\rceil,m = \lceil\log_{b}l\rceil$。

那么每次我们算出 $a^x \cdot b^y$ 的值，看其能否整除 $l$ 即可。注意我们需要标记每次算出的 $k$ 的值，可能会算出重复的 $k$。

[Link](https://codeforces.com/contest/1933/submission/249037547)

---

## 作者：appear_hope (赞：1)

观察数据范围发现 $\log_{a} l \times \log_{b} l$ 并不会超时。

所以故而可以直接枚举 $a$ 和 $b$ 的不超过 $l$ 的幂次，但会出现一个细节，可以发现当 $a=b$ 时会出现相等的 $k$，那么想办法去个重就行了，为了方便我使用 `set`。

时间复杂度：$O(T \times \log_{a} l \times \log_{b} l)$。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

int T, a, b, l;

void Solve(){
  set<int> s;
  cin >> a >> b >> l;
  int x = 0, y = 0;
  long long tmpx = 1, tmpy = 1;
  for(; tmpx * a <= l; x++, tmpx *= a){
  }
  for(; tmpy * b <= l; y++, tmpy *= b){
  }
  tmpx = 1;
  for(int i = 0; i <= x; i++){
    tmpy = 1;
    for(int j = 0; j <= y; j++){
      if(l % (tmpx * tmpy) == 0){
        s.insert(l / (tmpx * tmpy));
      }
      tmpy *= b;
    }
    tmpx *= a;
  }
  cout << s.size() << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  for(cin >> T; T--; Solve()){
  }
  return 0;
}

```

---

## 作者：minVan (赞：1)

**题目大意**

给定三个整数 $a,b,l$，问所有满足 $l=k\cdot a^x\cdot b^y$  的 $(k,x,y)$ 的 $k$ 的种类个数。

**解题思路**

令 $l$ 的唯一分解形式为 $a^p\cdot b^q\cdots$，当 $x=i$ 时（$i\in[1,p]$），$l$ 还剩下 $t=\dfrac{l}{a^i}$，接着从 $1$ 开始枚举 $j$，条件为 $b^j\mid t$，如果此时 $k=t\div b^j$ 没有出现过，那么标记下了并且答案加 $1$。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
bool vis[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    memset(vis, 0, sizeof(vis));
    int l, a, b, cnta = 0, ans = 0;
    cin >> a >> b >> l;
    for(int i = 0, a1 = 1; l % a1 == 0; i++, a1 *= a) {
      int tmp = l / a1, b1 = 1;
      while(tmp % b1 == 0) {
        if(!vis[tmp / b1]) {
          vis[tmp / b1] = 1;
          ++ans;
        }
        b1 *= b;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：__YSC__ (赞：1)

# 题目描述

给定三个正整数 $a,b,l$。求有多少个正整数 $k$ 满足 $\exists x, y使得 l=k\cdot a^x \cdot b^y$。

# 思路

枚举 $l$ 的因数 $k$，然后暴力判断是否存在一对合法的 $x,y$。

时间复杂度 $O(T\sqrt{V} (\log V)^2)$，空间复杂度 $O(1)$。

## 细节

无。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int t;
ll a, b, l, ans;

ll Pow(ll a, ll b) {
  ll res = 1;
  while(b) {
    if(b & 1) {
      res *= a;
    }
    a *= a;
    b >>= 1;
  }
  return res;
}

bool check(ll x) {
  for(ll i = 0; Pow(b, i) <= x; ++i) {
    if(Pow(b, i) == x) {
      return 1;
    }
  }
  return 0;
}

bool C(ll x) {
  for(ll i = 0; Pow(a, i) <= x; ++i) {
    if(x % Pow(a, i) == 0 && check(x / Pow(a, i))) {
      return 1;
    }
  }
  return 0;
}

void Solve() {
  cin >> a >> b >> l;
  ans = 0;
  for(ll i = 1; i * i <= l; ++i) {
    if(l % i == 0) {
      ans += C(l / i) + (l / i != i ? C(i) : 0ll);
    }
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> t;
  while(t--) {
    Solve();
  }
  return 0;
}

```

---

## 作者：Infinite_Loop (赞：1)

# CF1933C
## 思路
本题考虑使用暴力。枚举 $x$ 和 $y$，当 $l \bmod (a ^ {x} \cdot b ^ {y}) = 0$ 时，$ans + 1$。最后输出 $ans$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int t,a,b,l;
bool vis[N];
int main(){
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));
		cin>>a>>b>>l;
		int ans=0;
		for(int x=0;pow(a,x)<=l;x++)
		for(int y=0;pow(a,x)*pow(b,y)<=l;y++){
			if(l%(int)(pow(a,x)*pow(b,y))==0){
				int z=l/(pow(a,x)*pow(b,y));
				if(!vis[z]){
					vis[z]=1;
					ans++;
				}
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：0)

## 题解：CF1933C Turtle Fingers: Count the Values of k

### 分析
暴力枚举。

由于本题数据范围不大，我们可以考虑枚举 $a^x$ 和 $b^y$。判断每次枚举的 $a^x$ 和 $b^y$ 的乘积是否能被 $l$ 整除，如果能，则看看 $l$ 除以 $a^x \times b^y$ 的商是否已经枚举过，若没有枚举，则统计答案。

由于用数组标记答案在多测清零是可能会超时，考虑使用 `map`。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e18;
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
signed main()
{
    int t, a, b, l;
    for(cin>>t;t;t--)
    {
        int ans=0;
        map<int,bool> mp;
        cin>>a>>b>>l;
        for(int ax=1;ax<=l;ax*=a)
        {
            for(int by=1;by<=l;by*=b)
            {
                if(l%(ax*by)==0)
                {
                    if(!mp[l/(ax*by)])
                    {
                        ans++;
                        mp[l/(ax*by)]=1;
                    }
                }
            }
        }
        cout<<ans<<"\n";
    }
}
```

---

## 作者：_QyGyQ_ (赞：0)

我们可以发现，这道题的数据范围很小。所以我们可以暴力枚举每一个 $a$ 与 $b$ 的幂，如果其乘积是 $l$ 的因数，就记录答案。最后结果就是记录的答案去重后的个数。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
signed main(){
	int t;
	cin>>t;
	while(t--){
		map<int,int>mp;
		int a,b,l;
		cin>>a>>b>>l;
		int ans=0;
		for(int i=1;l%i==0;i*=a){
			for(int j=1;l%j==0;j*=b){
				if(l%(i*j)==0){
					if(!mp.count(l/(i*j))){
						ans++;
						mp[l/i/j]=1;
					}
				}
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：Houkiseino_Kokoro (赞：0)

### $\texttt{C. Turtle Fingers: Count the Values of k}$
#### [原题链接](https://codeforces.com/contest/1933/problem/C)
#### 题意简述
给定三个正整数 $a, b, l$，必然存在至少一组非负整数 $k, x, y$，满足 $l = k \times a^x \times b^y$。

求所有满足条件的整数组中 $k$ 所有可能取值的数量。

保证 $2 \le a, b \le 100$，$1 \le l \le 10^6$。
#### 解法
一开始我以为要分解质因数，但写到一半就发现多此一举。

根据数据范围，容易发现 $x$ 或 $y$ 的可能取值最多有 $ \lfloor \log_2 10^6 \rfloor + 1 = 20$ 种。故式子中 $a^x \times b^y$ 的值最多也只有 $20 \times 20 = 400$ 种。直接暴力枚举即可。 由于 $a^x \times b^y$ 的值可能会有重复，需要判重，方法很多就不赘述了。

需要注意的是如果枚举的是 $x$ 与 $y$ 这两个次数的话尽量少用 `pow` 函数，它由于支持浮点运算因此常数极大。建议用[快速幂](https://www.luogu.com.cn/problem/P1226)。如果直接枚举 $a^x$ 与 $b^y$ 的值的话计算乘积注意开 `long long`。

#### 代码
```cpp
void solve()
{
    int a, b, l, ans = 0;
    std::cin >> a >> b >> l;
    std::map<long long, bool> cnt;
    for (int i = 1; i <= l; i *= a)
    {
        for (int j = 1; j <= l; j *= b)
        {
            long long multi = 1ll * i * j;
            if (l % multi == 0 && !cnt[multi])
            {
                cnt[multi] = 1;
                ans++;
            }
        }
    }
    std::cout << ans << std::endl;
}
```

---

## 作者：yhylivedream (赞：0)

## 分析

可以枚举 $a$ 和 $b$ 的幂次，那么 $k$ 即为 $\frac{l}{a^xb^y}$，再计算出 $k$，判断 $k$ 是否为整数，注意 $k$ 有可能重复，开一个集合判重即可。

## 代码

```cpp
# include <bits/stdc++.h> 

using namespace std;
using ll = long long;
using PII = pair <int, int>;

ll T, a, b, l;

signed main () {
	for (cin >> T; T; T --) {
		cin >> a >> b >> l;
		set <int> st;
		for (int i = 0; i <= 20; i ++) {
			for (int j = 0; j <= 20; j ++) {
				int t = pow (a, i) * pow (b, j);
				if (l % t == 0) {
					// cout << l / t << ' ' << i << ' ' << j << '\n';
					st.insert (l / t);
				}
			}
		}
		cout << st.size() << '\n';
	}
	return 0;
}
```

---

