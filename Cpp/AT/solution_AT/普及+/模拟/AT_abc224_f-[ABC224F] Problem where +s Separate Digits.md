# [ABC224F] Problem where +s Separate Digits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc224/tasks/abc224_f

$ 1 $ から $ 9 $ までの数字のみで構成された文字列 $ S $ が与えられます。  
 この文字列 $ S $ から、以下の操作によって式 $ T $ を作ります。

- はじめ、 $ T=S $ であるとする。
- 各要素が $ 1 $ 以上 $ |S|-1 $ 以下の整数である、値に重複のない集合 $ A $ を選ぶ。なお、 $ A $ が空集合であってもよい。
- $ A $ の全ての要素 $ x $ について、 $ x $ の降順に以下の操作を行う。
  - $ T $ の $ x $ 文字目と $ x+1 $ 文字目の間に、 `+` を挿入する。

例えば、 $ S= $ `1234`、 $ A=\ \lbrace\ 2,3\ \rbrace $ であるとき、 $ T $= `12+3+4` となります。

この操作によって得られる $ T $ としてあり得る全ての式に対して、式を計算したときの値の総和を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ |S|\ \le\ 2\ \times\ 10^5 $
- $ S $ は `1`, `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9` のみからなる。

### Sample Explanation 1

式 $ T $ としてあり得るものは `1234`, `123+4`, `12+34`, `12+3+4`, `1+234`, `1+23+4`, `1+2+34`, `1+2+3+4` の $ 8 $ つです。 これらを計算した値の総和は $ 1736 $ です。

### Sample Explanation 2

$ S $ の長さが $ 1 $ であることもあります。この場合、 $ A $ として指定可能なのは空集合のみです。

### Sample Explanation 3

答えを $ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
1234```

### 输出

```
1736```

## 样例 #2

### 输入

```
1```

### 输出

```
1```

## 样例 #3

### 输入

```
31415926535897932384626433832795```

### 输出

```
85607943```

# 题解

## 作者：SunburstFan (赞：2)

### F - Problem where +s Separate Digits

#### 题目大意 

有一个只含 $1 \ldots 9$ 的长度为 $N$ 数字串。

在这个串中加最少 $0$ 个，最多 $N-1$ 个加号，使得其变成一个加法算式，求所有可能的算式的结果的总和模 $998244353$。

#### 解题思路

考虑 dp。

- 设 $f_i$ 表示 $1 \ldots i$ 中，第 $i$ 位与第 $i-1$ 位之间没有加号的方案数。

- 设 $g_i$ 表示 $1 \ldots i$ 中，第 $i$ 位与第 $i-1$ 位之间有加号的方案数。

容易得到状态转移：

- **$f_i = s_i \times 2^{i-1} + f_{i-1} \times 10$**。

解释：第 $i$ 位与第 $i-1$ 位之间没有加号，即它们是连着的一个数，因此需要先将 $f_{i-1}\times 10$，再将第 $i$ 位的数字加上去，共有 $2^{i-1}$ 种可能，因此就要加上 $s_i \times 2^{i-1}$。

- **$g_i = g_{i-1} \times 2 + f_{i-1}$**。

解释：第 $i$ 位将第 $i-1$ 位没有分离的分离开来了，因此要加上 $f_{i-1}$，同时之前就已经分离的会出现两个分支因此还要加上 $g_{i-1} \times 2$。

最终答案为 $f_n + g_n$，时间复杂度 $O(N)$，$1 \leq N \leq 2 \times 10^5$，轻松通过。

```cpp
n=s.length();
pow_2[0]=1ll;
for(int i=1;i<=n;i++){
    pow_2[i]=(pow_2[i-1]*2ll)%mod;
}

for(int i=1;i<=n;i++){
    ll u=s[i-1]-'0';
    f[i]=((f[i-1]*10)%mod+(u*pow_2[i-1])%mod)%mod;
    g[i]=((g[i-1]*2)%mod+f[i-1])%mod;
}
cout<<(f[n]+g[n])%mod<<"\n";
```

---

## 作者：I_LOVE_MATH (赞：1)

### 题目大意

给出一个大整数，可以往其中任意添加加号（可以不加），变成一个加法算式，问所有这种加法算式结果之和。

### 解题思路

考虑**拆贡献**。

设长度为 $n$，现在枚举到第 $i$ 位。

- 考虑后面的加号影响：  
  设此时第 $i$ 位是 $x$ 位数，那么一种情况会有 $10^{x-1}$ 的贡献，后面最左的加号在第 $i+x-1$ 位，后面有 $n-i-x$ 位可以随便填，那么有 $2^{n-i-x}$种情况，特别地，如果后面没有加号，有 $1$ 种情况。  
  那么求和就能得到以下式子：
  $$f[i]=2^0\cdot10^{x-i}+2^0\cdot10^{x-i-1}+2^1\cdot10^{x-i-2}+2^2\cdot10^{x-i-3}+\cdot\cdot\cdot+2^{x-i-1}\cdot10^0$$
  不难得到递推式：
  $$
  f[x] = \begin{cases}
  1 & x=n\\
  10\cdot f[i + 1] + 2 ^ {x - i - 1} & 1<x<n
  \end{cases}
  $$
- 考虑前面的加号影响：  
  只需考虑情况数即可，为 $2^{i-1}$。

最后只要拿当前位的数乘上两个影响即可得到当前位贡献，最后求和。

代码实现可以预处理 $2$ 的幂次，即可做到 $O(n)$

### 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
#define ll long long
using namespace std;

const int N = 2e5 + 10, P = 998244353;

ll n, ans;
ll f[N], g[N];
string s;

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> s;
	n = s.length();
	s = " " + s;
	g[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		g[i] = (2 * g[i - 1]) % P;
	}
	f[n] = 1;
	for (int i = n - 1; i >= 1; i--)
	{
		(f[i] = f[i + 1] * 10 + g[n - 1 - i]) %= P;
	}
	for (int i = 1; i <= n; i++)
	{
		(ans += (s[i] - '0') * g[i - 1] * f[i]) %= P; 
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：gxp123 (赞：1)

# abc224 F - Problem where +s Separate Digits

## 题意

给你一个数字串 $S$（只包含 $1\sim 9$），你可以在其中插入小于 $|S|$ 个加号（可以是 $0$ 个，结果即为 $S$），使得 $S$ 变成一个算式。计算所有可能的算式结果的和模 $998244353$ 的值。

数据范围：$1\le |S|\le 2\times10^5$

## 题解

我们设 $f_i$ 表示以 $i$ 结尾当前还没有分离（指还没有加上 `+`） 的贡献。

则
$$
f_i = f_{i-1}\times10 + s_i\times2^{i-1}
$$
理解一下这句话的意思就是：我们在最后的数字上加上 $x$，则前面的数字的值就乘上 $10$。

情况数有 $2^{i-1}$ 种，所以就乘上 $2^{i-1}$。

有了没有分离的，我们还需要加上分离的。

我们设 $g_i$ 表示以 $i$ 结尾当前已经分离（指加上 `+` 与后面的隔开了，贡献就这么多了） 的贡献。

则
$$
g_i=g_{i-1}\times2+f_{i-1}
$$
理解一下这句话的意思就是：我们把前面没分离的分离了，之前已经分离的迭代一次会有两个分支（相对应的式子后面分离或不分离）。

总的时间复杂度就是 $O(n)$。

## code

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;
const int maxN = 2e5 + 10;
const int mod = 998244353;
ll f[maxN],g[maxN];
char s[maxN];
int n;

int main(){
    scanf("%s",s + 1);
    n = strlen(s + 1);
    ll t2 = 1;
    for(int i = 1,x ; i <= n ; ++i){
        x = s[i] - '0';
        f[i] = ((x * t2) % mod + (f[i - 1] * 10) % mod) % mod;
        g[i] = (g[i - 1] * 2 % mod + f[i - 1]) % mod;
        t2 = (t2 * 2) % mod;
    }
    cout << (f[n] + g[n]) % mod;
    return 0;
}
```

---

## 作者：appear_hope (赞：1)

考虑设计状态，$dp_i$ 表示以 $i$ 结尾的数字的贡献（还没有放加号），转移 

$$dp_i = \sum _{j \le i - 1} ^ {j = 0} dp_j + f{_{j + 1}, _i} \times 2 ^ {j - 1}$$

其中 $f{_i, _j}$ 表示 $i$ 到 $j$ 所连起来的数字。

那为什么后面还要乘 $2^{j - 1}$ 次方呢？

因为前面 $1$ ~ $j$ 中共有 $2^{j - 1}$ 中放加法的方式。

我们可以先把这个转移分成两个部分

$$dp_i = \sum_{j \le i - 1} ^ {j = 0} dp_j +  \sum_{j \le i  - 1} ^ {j = 0} f{_{j + 1}, _i} \times 2 ^ {j - 1}$$

第一个部分可以直接用前缀和优化，而第二个部分本质上是让前面选择的数字多了一位，而把加 $a_i$ 在多的那一位上，其中 $a_i$ 表示第 $i$ 位上的数字。

我们可以令

$$ l_i = \sum_{j \le i - 1}^{j=0} f_{j + 1, i} \times 2 ^ {j - 1}$$

根据上面所说的，可以得到 $l_i$ 的递推式

$$ l_i = l_{i - 1} \times 10 + a_i \times 2 ^ {i - 1}$$

其中 $a_i$ 表示第 $i$ 位上的数字。

为什么要乘上 $2^{i - 1}$, 因为前面共有 $2^{i - 1}$ 种放加号的方式，而每种的数字都要多一位，而那多的一位放 $a_i$，此题结束。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353;

string s;
long long l, sum, now;

long long power(long long x, long long p){
  if(!p){
    return 1;
  }
  long long v = power(x, p / 2);
  return (p % 2 == 0 ? v * v : v * v % mod * x) % mod;
}
这里可以不用快速幂，可以预处理

int main(){
  cin >> s;
  for(int i = 0; i < s.size(); i++){
    now = (sum + l) % mod;
    sum = (sum + now) % mod;
    l = (10 * l + (s[i] - '0') * power(2, i)) % mod;
    由于每个转移只和上一次得到的答案有关，所以不需要开数组
  }
  cout << now % mod;
  输出什么自己想，这里写的是错的
  return 0;
}
切勿抄袭
```

---

## 作者：harmis_yz (赞：0)

## 分析

考虑对每一位单独考虑。对于第 $i$ 位，其后面第一个加号的位置可能在 $i,i+1,\dots,|s|$ 之后。这时其贡献分别为：$s_i \times 10^0\times 2^{|s|-i-1},s_i \times 10^1\times \times 2^{|s|-i-2} ,\dots,s_i \times 10^{|s|-i}\times \max(1,2^{-1})$。不难发现，在 $i$ 之前的加号一共有 $2^{i-1}$ 种方案。那么 $i$ 这一位的贡献就是 $2^{i-1} \times s_i \times \sum\limits_{j=0}^{|s|-i} 10^j\times \max(1,2^{|s|-i-j-1})$。观察 $\sum\limits_{j=0}^{|s|-i} 10^j\times \max(1,2^{|s|-i-j-1})$ 与 $\sum\limits_{j=0}^{|s|-i-1} 10^j\times \max(1,2^{|s|-i-1-j-1})$ 的差值，发现对于 $0 \le j \le |s|-i-2$，都乘了 $2$。而多了个 $10^{|s|-i}$。记 $g_i=\sum\limits_{j=0}^{|s|-i} 10^j\times \max(1,2^{|s|-i-j-1})$，则有 $g_i=2g_{i+1}-10^{|s|-i-1}+10^{|s|-i}$。时间复杂度 $O(n)$。

---

## 作者：FL_sleake (赞：0)

**本题解的做法与目前题解区所有做法均不同。**

### 题意简述

给你一个数字串 $S$（只包含 $1\sim 9$），你可以在其中插入小于 $|S|$ 个加号（可以是 $0$ 个，结果即为 $S$），使得 $S$ 变成一个算式。计算所有可能的算式结果的和模 $998244353$ 的值。

### 解题思路

分别考虑一位数的贡献，两位数的贡献，三位数的贡献，以此类推。

我们记 $sum_1$ 为所有一位数的和，$sum_2$ 为所有两位数的和，以此类推。

来看一下样例一。

$sum_1=1+2+3+4$

$sum_2=12+23+34=10+20+30+2+3+4=(sum_1-4)\times10+2+3+4$

$sum_3=123+234=120+230+3+4=(sum_2-34)\times10+3+4$

发现规律了吗？$sum_i$ 应该是 $sum_{i-1}$ 减去最后一个 $i-1$ 位数，再乘 $10$，再加上一堆一位数。

其实这个挺好理解的，所有 $i-1$ 位数中，只有最后一个无法扩展为 $i$ 位数，其余都可以通过乘 $10$ 再加它后面一位数扩展为 $i$ 位数。有了这个东西，我们就可以 $\Theta(n)$ 求出所有 $i$ 位数的和了。

然后再来考虑贡献。对于一个 $i$ 位数，为了让它有贡献，应该先在它前后都插入一个加号，保证它出现。然后这个 $i$ 位数中间不能插入加号，也是为了保证它能够出现。其余的位置都可以选择插入加号或者不插入加号，所以总贡献是一个 $2$ 的次幂的形式。

这里需要注意对于头和尾的 $i$ 位数需要单独处理，因为它们前后有一个位置不需要插入加号，所以会多乘一个 $2$。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s;
int mod=998244353,sum[200010],ans=0,lst[200010],pre[200010];
int KSM(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
signed main(){
	cin>>s;
	int n=s.size();
	s=" "+s;
	for(int i=1;i<=n;i++) sum[i]=(sum[i-1]+(s[i]-'0'))%mod;//维护一堆一位数的和
	for(int i=n;i>=1;i--) lst[i]=(lst[i+1]+KSM(10,n-i)*(s[i]-'0')%mod)%mod;//维护后缀，即最后一个 i 位数
	for(int i=1;i<=n;i++) pre[i]=(pre[i-1]*10%mod+(s[i]-'0'))%mod;//维护前缀，即第一个 i 位数
	int num=0;//动态维护所有 i 位数的和
	for(int i=1;i<=n;i++){
		num=(num-lst[n-i+2]+mod)%mod;//减去最后一个 i-1 位数
		num=(num*10%mod+(sum[n]-sum[i-1]+mod)%mod)%mod;//乘10，加上一堆一位数
		num=(num-pre[i]+mod)%mod;//去头
		num=(num-lst[n-i+1]+mod)%mod;//去尾
		ans=(ans+num*KSM(2,max(0ll,n-i-2))%mod)%mod;//算贡献
		ans=(ans+pre[i]*KSM(2,max(0ll,n-i-1))%mod)%mod;//算头尾贡献
		ans=(ans+lst[n-i+1]*KSM(2,max(0ll,n-i-1))%mod)%mod;
		num=(num+pre[i])%mod;//加回来
		num=(num+lst[n-i+1])%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

部分内容参考了官方题解。

首先计算小数据：

$ a=a $

$ ab=11a+2b $

$ abc=112a+22b+4c $

$ abcd=1124a+224b+44c+8d $

所以设第 $ k $ 位上的数为 $ x $，其对答案的贡献即为 $ x \times (10^{k-1}+\sum_{i=0}^{k-2}10^i\times 2^{k-i-2}) $。

证明：实际上一个数的贡献只和之后的第一个加号位置有关，不和之前的有关。

从第一位开始考虑：之后的第一个位置填加号有 $ \frac{1}{2} $ 的概率，于是会对答案造成 $ \frac{1}{2} $ 的贡献，第二个位置是第一个加号的情况为 $ \frac{1}{2^2} $，以此类推，最后一位即为 $ \frac{1}{2^{k-1}} $。

然后所有添加加号的方案一共有 $ 2^{k-1} $ 种，于是直接用方案数与概率相乘即可得到上式。

等式的右边都可以递推计算，时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
int mod=998244353;
string s;int n;
int ten[200005];
int two[200005];
int ar[200005];
signed main()
{
    ten[0]=1;
    two[0]=1;
    for(int i=1;i<200000;i++)
    {
        ten[i]=ten[i-1]*10ll;
        ten[i]%=mod;
        two[i]=two[i-1]*2ll;
        two[i]%=mod;
    }
    cin>>s;
    n=s.size();
    reverse(s.begin(),s.end());
    for(int i=0;i<n;i++)
    ar[i]=s[i]-'0';
    int ans=0;
    int rval=1;
    for(int i=0;i<n;i++)
    {
        ans+=ar[i]*rval*two[n-i-1];
        ans%=mod;
        int trval=rval;
        rval*=10;
        rval%=mod;
        rval+=1*two[i];
        rval%=mod;
    }
    cout<<ans;
}
```


---

