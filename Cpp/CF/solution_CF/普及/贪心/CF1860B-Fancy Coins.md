# Fancy Coins

## 题目描述

Monocarp is going to make a purchase with cost of exactly $ m $ burles.

He has two types of coins, in the following quantities:

- coins worth $ 1 $ burle: $ a_1 $ regular coins and infinitely many fancy coins;
- coins worth $ k $ burles: $ a_k $ regular coins and infinitely many fancy coins.

Monocarp wants to make his purchase in such a way that there's no change — the total worth of provided coins is exactly $ m $ . He can use both regular and fancy coins. However, he wants to spend as little fancy coins as possible.

What's the smallest total number of fancy coins he can use to make a purchase?

## 说明/提示

In the first testcase, there are no regular coins of either type. Monocarp can use $ 2 $ fancy coins worth $ 1 $ burle and $ 3 $ fancy coins worth $ 3 $ (since $ k=3 $ ) burles to get $ 11 $ total burles with $ 5 $ total fancy coins.

In the second testcase, Monocarp has a lot of regular coins of both types. He can use $ 11 $ regular coins worth $ 1 $ burle, for example. Notice that Monocarp doesn't have to minimize the total number of used coins. That way he uses $ 0 $ fancy coins.

In the third testcase, Monocarp can use $ 5 $ regular coins worth $ 1 $ burle and $ 1 $ regular coin worth $ 3 $ burles. That will get him to $ 8 $ total burles when he needs $ 11 $ . So, $ 1 $ fancy coin worth $ 3 $ burles is enough.

## 样例 #1

### 输入

```
4
11 3 0 0
11 3 20 20
11 3 6 1
100000000 2 0 0```

### 输出

```
5
0
1
50000000```

# 题解

## 作者：I_am_kunzi (赞：8)

# CF1860B 题解

### 题目翻译

你想凑出 $ m $ 元。现在有一个 $ k$，你有 $ a_1 $ 个普通 $ 1 $ 面值的硬币和无限的花色 $ 1 $ 面值硬币；你还有 $ a_k $ 个普通 $ k $ 面值的硬币和无限的花色 $ k $ 面值硬币，求需要的最少花色硬币数。

### 题目思路

一看到这题我的思路就是把两种普通硬币先拿上，再想办法用花色硬币，但是观察样例第三组数据会发现这种贪心不一定是最优解（全部用上则需要 $ 2 $ 个 $ 1 $ 面值花色硬币；劣于只用 $ 5 $ 个普通 $ 1 $ 面值硬币和 $ 1 $ 个 $ 3 $ 面值硬币时只需 $ 1 $ 个 $ 3 $ 面值花色硬币）。

我们可以先计算出不用普通硬币时所需的两种花色硬币数，再在不用 $ 1 $ 面值普通硬币替代 $ k $ 面值普通硬币的情况下用它们分别替代同面值的花色硬币。此外如果仍有多余，再用 $ 1 $ 面值普通硬币替代 $ k $ 面值普通硬币以减少花色硬币需求数。

### 题目代码

```cpp
#include<iostream>
using namespace std;
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		long long m , k , a1 , ak;
		cin >> m >> k >> a1 >> ak;
		long long take_1 = m % k; // 不替代情况下所需 1 面值花色硬币
		long long take_k = m / k; // 不替代情况下所需 k 面值花色硬币
		long long fancy_1 = max((long long) 0 , take_1 - a1); // 替代后所需 1 面值花色硬币
		long long drop_1 = max((long long) 0 , a1 - take_1); // 没有用到的 1 面值花色硬币数
		long long fancy_k = max((long long) 0 , take_k - ak); // 用 k 面值普通硬币替代后所需 k 面值花色硬币
		long long replace = min(drop_1 / k , fancy_k); // 用 1 面值普通硬币替代 k 面值普通硬币数
		cout << fancy_1 + fancy_k - replace << endl; // 答案即为计算后两种花色硬币所需数量与替代硬币数作差
	}
    return 0;
}
```

---

## 作者：Wf_yjqd (赞：3)

题面又是很难读懂。

我甚至过了以后还不知道为啥特殊硬币都要使用无限个了还有计算最小花费。

所以就是按自己理解的题意写的。

------------

考虑贪心，因为每次花费普通 $k$ 元硬币不会增加最后使用特殊硬币次数，所以尽量全花光。

而剩下的就得考虑要用多少次普通 $1$ 元硬币了。

显然，我们要让剩下的钱除以 $k$ 的商和余数的和尽可能小。

考虑尽量让余数为 $0$ 的同时商尽量小，因为商如果是最小的一个，余数就会 $\ge1$，至少不可能更优。

如果余数无法为 $0$，就把普通 $1$ 元全用完好了。

按以上贪心策略模拟即可，复杂度 $\operatorname{O}(1)$。

------------

没啥好说的水题。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,m,k,a1,ak;
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld%lld%lld",&m,&k,&a1,&ak);
        m-=min(m/k,ak)*k;
        if(m<=a1)
            puts("0");
        else{
            if((m-a1)%k!=0&&((m-a1)/k+1)*k<=m)
                m=((m-a1)/k+1)*k;
            else
                m-=a1;
            printf("%lld\n",m/k+m%k);
        }
    }
    return 0;
}
```


---

## 作者：Zaku (赞：3)

题意已经翻译地很好了。没见过这么水的 T2。

### $\rm{Solve:}$

容易想到尽量使用 $k$ 面值。于是使用两个变量 $t_1$ 和 $t_k$ 分别记录 $m \bmod k$ 和 $\Large \frac{m}{k}$ 的两种面值硬币个数。

本着上面的原则，我们在 $a_1 > t_1$ 时把多的 $1$ 面值转化成 $k$ 面值，即 `ak += (a1 - t1) / k`，然后 $a1 \gets t1$。这样的情况下就不需要 $1$ 面值的花硬币了。

为了便于求出答案，在 $a_k > t_k$ 时，$a_k\gets t_k$。

这样，答案即为 $t_1 - a_1 + t_k - a_k$。

代码：
```cpp
void solve(){
    int m, k, a1, ak;
    cin >> m >> k >> a1 >> ak;
    int t1 = m % k, tk = m / k;
    if (a1 > t1)
        ak += (a1 - t1) / k, a1 = t1;
    if (ak > tk) ak = tk;
    cout << t1 - a1 + tk - ak << endl;
}
```

---

## 作者：tbdsh (赞：3)

# 题意简述
[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf1860b)

[洛谷题面传送门](/problem/cf1860b)

[CF 题面传送门](https://codeforces.com/contest/1860/problem/B)

有两种硬币 A 和 B。硬币 A 价值 $1$ 元，有 $a_1$ 个，硬币 B 价值 $k$ 元，有 $a_k$ 个。同时，你还有很多个任意硬币。每个任意硬币价值 $1$ 元或 $k$ 元。现在请你用这些硬币凑出正好 $m$ 元。请你最小化任意硬币的使用数量。输出这个最小数量。

# 分析
首先，如果 $a_1=a_k=0$，那么就只能用任意硬币。不难发现，此时答案为 $\left\lfloor\dfrac{m}{k}\right\rfloor + m\bmod k$。

同时，如果 $a_1>m$，那么答案为 $0$。

判断完这两种情况后，我们考虑一般情况。

按照以下几步操作即可（下面默认每次操作完 $m$ 的值都进行更新）。

- 用硬币 A 让 $m\bmod k$ 的值变小。

- 用硬币 B 让 $m$ 的值尽可能小。

- 在硬币 A 现在的数量 $\ge k$ 的情况下，不断地用 $k$ 枚硬币 A。

不难发现，现在的情况再使用硬币 A、B 只会让答案更劣。所以现在还需要使用的任意硬币数量就是 $\left\lfloor\dfrac{m}{k}\right\rfloor + m\bmod k$。

直接输出即可。

单组数据时间复杂度：$O(1)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
void Solve(){
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  if (!c && !d){
    cout << a / b + a % b << '\n';
    return ;
  }
  if (c >= a){
    cout << "0\n";
    return ;
  }
  int x = a / b, ans = 0;
  if (x <= d){
    a %= b;
  }else {
    a -= b * d;
  }//操作 2。
  if (a % b <= c){//操作 1。
    c -= a % b;
    a -= a % b;
  }else {
    a = max(0, a - c);
  }
  a -= (c / b) * b;//操作 3。
  cout << max(0, a / b + a % b) << '\n';//比较懒，没有处理 c>a 的情况了。所以答案和 0 取 max。
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：bingo888 (赞：2)

#### 题目回顾：   
$t$ 组数据：对于每组数据，你有 $a_1$ 枚 $1$ 元的普通硬币和 $a_k$ 枚 $k$ 元的普通硬币，同时你还有无限的花硬币（面值 $1$ 元和 $k$ 元均有），你需要用最少的花硬币组成**恰为** $m$ 元的面值，输出花硬币使用的最小值（来自本人的翻译）。  
#### 正解：  
考虑贪心，记录 $c=\lfloor\frac{m}{k}\rfloor$。  
若 $c\le a_k$，则表示我们可以不用 $k$ 面值的花硬币，记录 $d=m-c$，此时我们的答案就是 $\max(d-a_1,0)$。  
若 $c>a_k$，则首先将 $a_k$ 枚普通硬币用出，记录 $m'=m-a_k\times k$ 和 $d'=m'-\lfloor\frac{m'}{k}\rfloor$，如果 $a_1\ge d'$，则表示 $1$ 面值的普通硬币可以将余数填满，剩下的就用 $k$ 面值花硬币，此时答案为 $\frac{m'-d'}{k}-\lfloor\frac{a_1-d'}{k}\rfloor$，否则表示 $1$ 面值的普通硬币填不满余数，答案就是 $\frac{m'-d'}{k}+d'-a_1$。  
***  
我认为答案都说的很清楚，就不贴代码了。（个人认为这道题难度最多为普及-）

---

## 作者：Iniaugoty (赞：1)

Update on 10.13：改了一点代码。

大意：见翻译。

$1$ 个 $k$ 元相当于 $k$ 个 $1$ 元，所以 $k$ 元尽可能多的使用。但是 $a _ 1$ 以下 $1$ 元是免费的，可以在 $[0, a _ 1]$ 中最大化 $1$ 元个数，减少 $k$ 元个数，即令 $1$ 元个数为 $m \bmod k + k \times \lfloor \dfrac {a _ 1 - m \bmod k} {k} \rfloor$。

注意特判 $a _ 1 < m \bmod k$ 的情况，直接 $0$ 个 $1$ 元。

```cpp
std::cin >> m >> k >> a1 >> ak;
if (a1 < m % k) std::cout << (m % k - a1) + std::max(m / k, ak) - ak << "\n";
else std::cout << std::max((m - (m % k + (a1 - m % k) / k * k)) / k, ak) - ak << "\n";
```

---

## 作者：aCssen (赞：1)

### Solution

容易想到一种构造，即用 $\lfloor \frac{m}{k} \rfloor $ 个价值为 $k$ 的硬币，再用 $m \bmod k$ 个价值为 $1$ 的硬币。

这样，答案为 $\max\lbrace0,\lfloor \frac{m}{k} \rfloor-b\rbrace+\max\lbrace0,m \bmod k-a\rbrace$，取 $\max$ 是因为所需硬币数量可能比现有普通硬币数量小。

但这样可能不是最优的，原因是价值为 $k$ 的普通硬币可能很少，但价值为 $1$ 的硬币却剩下了很多，此时我们考虑调整：用 $k$ 个价值为 $1$ 的普通硬币替换一个价值为 $k$ 的硬币。

这样显然是正确的，因为价值为 $k$ 的硬币无法凑出 $m \bmod k$ ，但价值为 $1$ 的硬币却能凑出 $k$。

具体的，我们将本题的解答分为几个部分：

+ 计算出消去 $m \bmod k$ 所需的花硬币数，同时正确维护剩余的价值为 $1$ 的普通硬币数 $a'$。

+ 得到价值为 $k$ 的硬币需要的个数：$c=\max\lbrace \lfloor \frac{m}{k} \rfloor -\lfloor \frac{a'}{k}\rfloor,0 \rbrace$。

+ 如果 $c>b$，答案加上 $(c-b)$。
### Code
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
void solve(){
	int m,k,a,b,cnt1,cnt2,ans=0;
	scanf("%d%d%d%d",&m,&k,&a,&b);
	cnt1=m%k,cnt2=m/k;
	if(cnt1>a){
		ans+=(cnt1-a);
		a=0;
	}
	else a-=cnt1;
	cnt2=max(cnt2-(a/k),0);
	if(cnt2>b) ans+=(cnt2-b);
	printf("%d\n",ans);
}
int main(){
	int t;
	scanf("%lld",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：XSean (赞：1)

# B: Fancy Coins 题解

[Problem - B - Codeforces](https://codeforces.com/contest/1860/problem/B)

## 基本思路：

思路：

- 先拿价值为 $k$ 的金币，然后再拿价值为 $1$ 的金币，然后先拿普通版的，再拿有花色版的（将无穷多的花色视为每次一个），自然算出所有类型的金币数量。

- 考虑**剩下**的价值为 $1$ 的普通版金币**尽可能多**的和价值为 $k$ 的花色版金币交换。一定是等价（相等的价值）交换，直到价值为 $1$ 的普通版金币没了或者价值为 $k$ 的花色版金币没了。

**时间复杂度：$O(T)$**。

## 代码实现：

核心代码：

```cpp
int T; rd(T);
while(T--){
    int tot, k, a1, ak; rd(tot, k, a1, ak);
    int use1 = tot % k, usek = tot / k;
    int fancy1 = max(0, use1 - a1), fancyk = max(0, usek - ak);
    int rest1 = max(0, a1 - use1);
    int replace = min(fancyk, rest1 / k);
    prf("%d\n", fancy1 + fancyk - replace);
}
```

**[完整代码](https://codeforces.com/contest/1860/submission/219517146)**

---

## 作者：xiaomuyun (赞：0)

本题解将会以纯朴暴力但容易理解的思路带着大家通过这题，适合 OI 萌新阅读。

- [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1860B)
- [CodeForces 题目传送门](https://codeforces.com/problemset/problem/1860/B)

## 理解题意

我有 $a_1$ 枚 $1$ 元普通硬币和 $a_k$ 枚 $k$ 元普通硬币。另外，我还有面值为 $1$ 元 **和** $k$ 元的特殊硬币，且这些硬币的数量是无限多的。我可以用这两种硬币去凑面值，请问凑出 $m$ 元至少需要几枚特殊硬币？

## 思路分析

可以看出来是一个简单的分类讨论题。那就开始分讨吧。

### 1. 所有普通硬币的面值之和大于等于 $m$

注意这种情况的答案不一定为 $0$，随便出一个数据都可以 hack 掉，比如 `15 4 0 4` 的答案为 $3$，这种情况需要 $3$ 枚 $1$ 元特殊硬币。

对于这种情况，我们在保证凑出来的和小于等于 $m$ 前先尽可能地用 $k$ 元普通硬币凑。然后等 $m$ 减当前凑出来的和小于 $k$ 时，也就是再用 $k$ 元普通硬币的话凑出来的总和就超过 $m$ 时，这时候就可以用 $1$ 元硬币了。注意这里的 $1$ 元硬币可以是普通硬币也可以是特殊硬币，$1$ 元普通硬币在这个情况可能会被用完，参考数据 `10 4 1 100`，答案为 $1$，即使用一枚 $1$ 元特殊硬币。

### 2. 所有普通硬币的面值之和小于 $m$

首先定义变量 $need$ 的值为 $m-s$，其中 $s$ 为所有普通硬币的面值之和，即 $a_k\times k+a_1\times1$。

- 如果 $need\ge k$，则尽可能地塞面值为 $k$ 元的特殊硬币是一定的。不过我觉得我讲不明白，请看代码中的解释。
- 如果 $need<k$，就用面值为 $1$ 元的特殊硬币填上即可。或者是少用一些 $1$ 元普通硬币来凑一个 $k$ 元特殊硬币。

## 代码实现

```cpp
#include<cstdio>
#define int long long// 10^6 * 10^6 > 2^31-1
using namespace std;
int _,m,k,a1,ak;
signed main(){
	scanf("%lld",&_);
	while(_--){
		scanf("%lld%lld%lld%lld",&m,&k,&a1,&ak);
		if(k*ak+a1<m){//对应分类讨论里的第二种情况。
			int need=m-(k*ak+a1);
			if(need>=k){
				if(need%k==0) printf("%lld\n",need/k);//如果能只丢一枚 k 元特殊硬币就能凑到 m 元就好啦。
				else if(a1>=k-need%k) printf("%lld\n",need/k+1);//少用一些 1 元普通硬币来凑一个 k 元特殊硬币，这样一定会比用一堆 1 元特殊硬币来凑更优。
				//有了上面这一行判断语句就得在前面特判 need%k==0 的情况，不然样例都过不了哦。
				else printf("%lld\n",need/k+need%k);//能用 k 元特殊硬币就用 k 元特殊硬币，否则就用 1 元特殊硬币。
			}
			else {//下面两部分分别对应思路分析中 need<k 的两种方案。
				if(a1>=k-need) printf("1\n");
				else printf("%lld\n",need);
			}
		}
		else {//对应分类讨论里的第一种情况。
			if(k*ak<=m){//似乎不用这里的判断，因为在这个 else 里面 k*ak+a1 是大于等于 m 的。如果需要判断请在评论区指出。
				int need=m-k*ak;
				if(need<=a1) printf("0\n");
				else printf("%lld\n",need-a1);
			}
			else {
				int need=m%k;
				if(need<=a1) printf("0\n");
				else printf("%lld\n",need-a1);//ak 就算很大，1 元普通硬币数量也有可能很少。
			}
		}
	}
	return 0;
}
```
## hack 数据

输入：

```plain
1
3 3 1 0
```

输出：

```plain
1
```

解释：使用一枚 $k$ 元特殊硬币。

## 最后

祝早日 AC。

---

## 作者：Mix66 (赞：0)

### 思路

容易想到尽量使用 $k$ 面值。于是使用两个变量 $t_1$ 和 $t_k$ 分别记录 $m \bmod k$ 和 $\frac{m}{k}$ 的两种面值硬币个数。

这样，答案即为 $t_1 - a_1 + t_k - a_k$。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
    int m , k , a, a_k;
    cin >> m >> k >> a >> a_k;
    int t = m % k;
    int t_k = m / k;
    if ( a > t )
    {
        a_k += ( a - t ) / k;
        a = t;
    }
    if( a_k > t_k ) 
    {
        a_k = t_k;
    }
    cout << t - a + t_k - a_k << endl;
}
int main()
{
    int T;
    cin >> T;
    while( T-- )
    {
        solve();
    }
    return 0;
}

```

---

## 作者：Eltaos_xingyu (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1860B)

这是一道很简单的题，我们的思路也很朴素。

首先，很容易推出当只有花币时，对于任意的 $ m $，计算结果为 $ m / k + m \bmod k $。

我们把面值为k的普通硬币用到 $ m < k $ 或用完，然后把面值为1的硬币用完，如果 $ m \leq 0 $ 那就直接输出 $ 0 $，否则用 $ a_1 $ 判断现在的 $ m $ 能否回溯到上一个能整除 $ k $ 的数，如果不能，直接正常输出现在的 $ m $ 的计算结果，如果可以，那就把回溯后的数的计算结果和回溯前的数的计算结果作比较选最小就行了。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	long long m,k,a1,ak;
	while(t--){
		cin>>m>>k>>a1>>ak;
		int temp=m;
		if(a1==0&&ak==0){
			cout<<m/k+m%k<<endl;
			continue;
		}
		m-=ak*k;
		if(m<0)m=(m+ak*k)%k,ak-=m/k;
		m-=a1;
		if(m<=0)cout<<0<<endl;
		else {
			int mm=m/k*k+k;
			if(a1<temp-temp/k*k&&mm-m>a1){
				cout<<m/k+m%k<<endl;
				continue;
			}
			cout<<max(min(mm/k+mm%k,m/k+m%k),0ll)<<endl;
		}
	}
}
```


---

## 作者：chlchl (赞：0)

## Solution
贪心。

#### 思路 1
首先第一反应是，能拿 $k$ 凑的尽量凑，不够的用 $1$ 凑。

但是很快发现这样是过不去第三个样例的，因为按照我们的思路，第三个样例应该选 $3$ 个 $3$ 和 $2$ 个 $1$，这样不仅出现极大冗余，答案也不优（需要两个额外的 $3$）。

#### 思路 2
能不能优化一下上述思路？

很快想到，如果 regular  $1$ 硬币的数量 $\ge k$，我们可以把它转化成若干个 regular $k$ 硬币。

但是这样还是过不去，因为一共有 $6$ 个 $1$，直接转化成 $2$ 个 $3$，尴尬地发现最后还需要 $2$ 个额外的 $1$。

#### 思路 3
显然思路 $2$ 的优化方向不太正确。

我们应该先用 $1$ 把 $n\bmod k$ 填满（这部分不可能用 $k$ 填，即使不够 $1$ 也要额外加），剩下的全部用 $k$ 填。同时若 $1$ 的数量 $\ge k$，那我们就可以 $k$ 个 $k$ 个地填 $1$。

剩下冗余的 $1$ 就不要管了，一旦加不够 $k$ 就会破坏余数，还要加更多的 $1$ 来填补这个余数。

这样，可以发现，额外添加的 $1$ 硬币的个数不会超过 $k-1$ 个。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N = 2e5 + 10;
int T, m, k, a1, ak;
 
void solve(){
	scanf("%d%d%d%d", &m, &k, &a1, &ak);
	int ans = 0;
	int q = m % k;//尽量凑成 k 能完成的任务 
	ans += max(0, q - a1);
	m -= q, a1 = max(a1 - q, 0);
	m -= (int)(a1 / k) * k;//a1 最多能分担掉多少个 k
	//剩下的全是 k 的任务，并且 m 一定能整除 k
	printf("%d\n", ans + max(m / k - ak, 0)); 
}
 
int main(){
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```


---

## 作者：ax_by_c (赞：0)

# 题意描述
有 $2$ 种货币，一种价值为 $1$，一种价值为 $k$。

然后你有价值为 $1$ 的普通硬币 $a_1$ 个，以及价值为 $k$ 的普通硬币 $a_k$ 个。

还有价值为 $1$ 的花式硬币无数个，以及价值为 $k$ 的花式硬币无数个。

现在你要凑出 $m$ 元，问最少要用多少花式硬币。
# 解题思路
首先，很容易想到一下方法：

第一步：尽量用价值为 $k$ 的普通硬币。

第二步：尽量用价值为 $1$ 的普通硬币。

第三步：尽量用价值为 $k$ 的花式硬币。

第四步：尽量用价值为 $1$ 的花式硬币。

然后写出来后，你会发现过不了第三个样例。

因为其实能进行这样的操作：

在第二步中少用硬币，第四步中不用硬币，正好还差 $k$，然后在第三步中多用一个硬币。

这样，原来的若干个价值为 $1$ 的普通硬币和价值为 $1$ 的花式硬币就变成了一个价值为 $k$ 的花式硬币。

于是得到更优的解。

但是这样的操作次数会进行几次呢？

显然是一次。

因为如果做了两次，就变成了：

在第二步中少用硬币，第四步中不用硬币，正好还差 $2 \times k$，然后在第三步中多用两个硬币。

那么此时一次肯定更优，因为只做一次的话，第二步就会多用 $k$ 个硬币，而第三步中少用了一个。

但是因为第二步不算进答案，所以实际上就是少用了一次。

证毕。

# 解法
就是先计算不用特殊操作的解，然后如果能用的话就用一次，然后答案为较优解。

核心代码如下：

```cpp
cin>>wt>>k>>a1>>ak;
if(ak*k<=wt)
{
	wt-=ak*k;
	if(a1<=wt)
	{
		wt-=a1;
	}
	else
	{
		wt=0;
	}
	if(wt)
	{
		int res=0;
		res+=wt/k;
		wt-=(wt/k)*k;
		int fks=wt;
		if(a1>=(k-wt))
		{
			fks=min(fks,1LL);
		}
		res+=fks;
		cout<<res<<'\n';
	}
	else
	{
		cout<<wt<<'\n';
	}
}
else
{
	wt-=(wt/k)*k;
	if(a1<=wt)
	{
		wt-=a1;
	}
	else
	{
		wt=0;
	}
	cout<<wt<<'\n';
}
```

---

