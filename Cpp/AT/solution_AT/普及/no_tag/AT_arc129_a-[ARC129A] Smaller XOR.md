# [ARC129A] Smaller XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc129/tasks/arc129_a

整数 $ N,L,R $ が与えられます． 以下の条件を両方満たす整数 $ x $ の個数を数えてください．

- $ L\ \leq\ x\ \leq\ R $
- $ (x\ \oplus\ N)\ <\ N $ （ここで $ \oplus $ はビット単位 $ \mathrm{XOR} $ 演算を表す）
 
 ビット単位 $ \mathrm{XOR} $ 演算とは  整数 $ A,\ B $ のビット単位 $ \mathrm{XOR} $ 、$ A\ \oplus\ B $ は、以下のように定義されます。

- $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 1\ \leq\ L\ \leq\ R\ \leq\ 10^{18} $
- 入力される値はすべて整数である

### Sample Explanation 1

$ x=1 $ の場合，$ L\ \leq\ x\ \leq\ R $ は満たしますが，$ (x\ \oplus\ N)\ <\ N $ は満たしません． $ x=2 $ の場合，両方の条件を満たします． 他に条件を満たす $ x $ は存在しません．

## 样例 #1

### 输入

```
2 1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
10 2 19```

### 输出

```
10```

## 样例 #3

### 输入

```
1000000000000000000 1 1000000000000000000```

### 输出

```
847078495393153025```

# 题解

## 作者：NightmareAlita (赞：3)

## 简要题意

给你三个数 $N, L, R$，询问满足 $x \in [L, R]$ 且 $(x \oplus N) < N$ 的整数 $x$ 的个数。

## 策略分析

我们考虑异或运算的性质，当某一位为 $0$ 时，它异或一个值可能增大或者不变，当某一位为 $1$ 时，它异或一个值可能减小或不变，也就是说一个数 $k$ 想要满足异或一个 $x$ 要比自己原来小，那么 $x$ 最高位的数值要是 $1$，且刚好要能对的上 $k$ 最高位那个 $1$。只要这一位变成 $0$ 了，后面 $x$ 的其它位想怎么取就怎么取，总之不管怎么取都一定比原来的数小。那么假设 $k$ 的第 $p$ 位为最高位，根据前面的分析，$x \in [2^p,2^{p+1}-1]$ 就可以满足条件，又因为 $x \in [L,R]$，二者取个交集即可。

上面我们讨论了能够得到 $x$ 的个数的性质，下面就把它套用在本题上。我们从 $N$ 的最低位开始扫，每当扫到一个 $1$ 就对以这一位为最高位的数计算一下 $x$ 的个数，然后累加起来就是本题的答案。

## 参考代码

``` cpp
#include <iostream>
#include <cstdio>
#define LL long long
using namespace std;

namespace SHAWN {
    LL n, l, r, ans; 
    int work()
    {
        cin >> n >> l >> r;
        for (int i = 0; (1ll << i) <= n; ++i) {
            LL xl = 1ll << i, xr = (xl << 1) - 1;
            if (!(xl & n)) { continue; }
            LL edgel = max(l, xl), edger = min(r, xr);
            ans = max(ans, ans + edger - edgel + 1);
        }
        cout << ans << '\n';
        return 0;
    }
}

signed main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```



---

## 作者：PineappleSummer (赞：2)

[[ARC129A] Smaller XOR](https://atcoder.jp/contests/arc129/tasks/arc129_a)

简单异或题。

为了让  $x\oplus n<n$，$x$ 一定满足以下条件：二进制下，从 $n$ 的高位枚举，如果 $x$ 这一位为 $1$ 且 $n$ 这一位为 $0$，则前面位肯定出现过 $x$ 在该位为 $1$ 且 $n$ 在该位为 $1$ 的情况。

那么考虑一种统计答案的方式：从 $n$ 的高位枚举，如果 $n$ 在当前位上为 $1$，则统计 $x$ 最高位为此位的情况。如果 $[L,R]$ 与 $[2^i,2^{i+1}-1]$ 相交或包含，答案增加 $\min(R,2^{i+1}-1)-\max(2^i,L)+1$。

核心代码如下，时间复杂度 $O(\log n)$。

```cpp
signed main ()
{
	ios::sync_with_stdio (false);
	cin.tie (0); cout.tie (0);
	
	cin >> n >> L >> R;
	for (int i = 61; ~i; i--) {
		if ((n >> i) & 1) {
			if ((1ll << i) > R || ((1ll << (i + 1))) <= L) continue;
			ans += min (R, ((1ll << (i + 1)) - 1)) - max ((1ll << i), L) + 1;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：loser_seele (赞：2)

显然看到异或朴素拆位算贡献。

对于一个二进制位 $ k $，若满足 $ x \oplus n <n $，则 $ n $ 的第 $ k $ 位必须为 $ 1 $。这个是显然的，因为 $ n $ 为 $ 0 $ 的时候 $ n \oplus x $ 显然不会小于 $ n $。

于是 $ x $ 的限定区间即为 $ [2^k,2^{k+1}-1] $，取这个区间与 $ [L,R] $ 的交集，加上区间长度即可。

时间复杂度 $ \mathcal{O}(\log{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
using ll=long long;
int main()
{
  ll N,L,R;
  cin>>N>>L>>R;
  ll ans=0;
  for(int i=0;(1LL<<i)<=N;i++)
  {
    if(((1LL<<i)&N)==0)
    continue;
    ll a=(1LL<<i);
    ll b=2*a-1;
    ll l=max(L,a);
    ll r=min(R,b);
    ans+=max(0LL,r-l+1);
  }
  cout<<ans;
}
```


---

## 作者：yedalong (赞：1)

## 前言

这是一道有关位运算的题目，不会位运算或者异或的同学请看[这里](https://blog.csdn.net/weixin_43736974/article/details/84543970)。\
这里敲一下警钟，不管你是否背熟[运算符的优先级](https://so1.360tres.com/t01ddf06e1ab619f951.jpg)，保险起见，一定要加括号。多加几个括号，就会解决我调了半个多小时的问题。

## 思路

看到数据范围，发现只有时间复杂度为 $O(\log N)$ 或者 $O(1)$ 才能通过此题，读完题目后又发现，$O(1)$ 的时间复杂度是不可能的，因此此题正解的时间复杂度只有可能是 $O(\log N)$，于是就可以往二进制的方向思考。\
首先有一个结论，对于两个数 $x$ 与 $y$ 作异或，如果 $y$ 二进制的最高位高于 $x$ 二进制的最高位，那么异或的结果一定是大于 $x$ 的，大家可以想一想为什么。\
由于我们现在是要让异或的结果小于 $N$ 的，所以这个 $x$ 二进制的最高位是必须低于 $N$ 二进制的最高位的。但这样并不是正解，我们还需要枚举 $N$ 二进制下的每一个 $1$。我们假设当前枚举到的 $1$ 在第 $i$ 位上，那么 $x \in [2^{i-1}, 2^i - 1]$。又因为题目还有要求 $x \in [L,R]$，因此，最后我们只需要求出这两个区间重合的长度，再求和即可，最终时间复杂度 $O(\log N)$。

## AC code:

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,l,r,ans;
int main(){
    cin>>n>>l>>r;
    for(int i = 61;i>=0;i--){
        if((n>>i)&1){
            if((1ll<<i)>r||(1ll<<(i+1))-1<l) continue;//这里与上述x范围不同的原因是上述x的第k位默认是大于0的，而这里是从0开始
            ans+=min(r,(1ll<<(i+1))-1)-max(l,1ll<<i)+1;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：leixinranYY (赞：0)

## 题目简译
给定 $N,L,R$，询问有多少个 $x$ 满足 $L\le x\le R$ 并且 $(x \oplus N)<N$。
## 思路
此题是一道位运算的题目。要想选中的某一位异或值小于等于本身，那这一位必须为 $1$。所以枚举 $N$ 的每一位，如果当前位上为 $1$，就记录一次答案。根据前面的分析，$x$ 的值不仅在 $L$ 和 $R$ 之间，还在 $2^k$ 到 $2^{k+1}-1$，所以二者取个交集即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,l,r,ans,x,y,tl,tr;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>l>>r;
	for(int i=0;(1ll<<i)<=n;i++) 
	{
		int x=(1ll)<<i,y=(x<<1ll)-1;
		if(!(x&n))continue;
		tl=max(l,x),tr=min(r,y);
		ans=max(ans,ans+tr-tl+1);
	}
	cout<<ans;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/197319047)

---

## 作者：__Creeper__ (赞：0)

### 思路

对于一个二进制数第 $k$ 位，若要满足 $x \oplus n < n$，那么则 $n$ 的第 $k$ 位必须为 $1$。我们从 $n$ 的高位枚举，如果当前位上为 $1$，则需要统计以此为最高位的答案。$x$ 的区间为 $[2^k,2^{k+1}-1]$，我们只要取与 $[l,r]$ 的交集，加上区间长度即可。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, l, r, ans;

void solve()
{
	cin >> n >> l >> r;
	for ( int i = 0; ( 1ll << i ) <= n; i++ ) 
	{
		int x = 1ll << i, t = ( x << 1ll ) - 1;
		if ( !( x & n ) ) continue;
		int L = max ( l, x ), R = min ( r, t );
		ans = max ( ans, ans + R - L + 1 );
	}
	cout << ans;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
//	cin >> T;
	while ( T-- ) solve();
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
朴素又简单的思维题。本片题解默认读者了解异或运算。
## 分析。
因为在二进制下，异或的结果无非只有 $1$ 和 $0$ 两个，所以当一个数的最高位 $1$ 与和其同位置的 $1$ 异或后，得到的结果显然小于其本身。所以我们只需要考虑整个区间中的所有数的数位上的 $1$ 然后异或即可。简单来说，我们所要求的区间可以这么计算：我们固定一个二进制数位为 $k$ 则当且仅当存在 $n$ 的第 $k$ 位为 $1$ 时才是一个解。

这样我们就直接遍历 $n$ 的过程中，找到 $1$ 数位的集合，然后同总的题目要求的区间内取一个交集即可。

代码如下，可供参考：
```
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
ll n,l,r;
ll ans;
ll ksm(ll a,ll b){
    int res=1;
    while(b>0){
        if(b&1) res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}
int main(){
    cin>>n>>l>>r;
    for(int i=62;~i;i--){
        if(n>>i&1){
            ll l_2=max(l,1ll<<i);
            ll r_2=min(r,(1ll<<(i+1))-1);
            if(r_2>=l_2){
            	ans+=r_2-l_2+1;
			}
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：yhx0322 (赞：0)

## Description
输入 $N,L,R$，询问满足 $L \le x \le R$，并且 $(x \oplus  N ) < N$ 的正整数 $x$ 的个数。
## Solution
发现一个性质：对于每一位 $t$，如果需要满足上述条件，**二进制下的 $t$ 必须为 $1$。**

于是我们便可以枚举 $t$，每次 $x$ 的区间为 $[2 ^ {t},2 ^ {t + 1})$。又因为 $L \le x \le R$，所以我们取交集即可。

**注意：由于本题的数据范围，记得开 long long，并且使用位运算的时候记得将 `1` 改为 `1LL`，否则会出错。**

## Code
```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int n, l, r, ans;
signed main() {
    cin >> n >> l >> r;
    for (int i = 0; (1LL << i) <= n; i++) {
        int s = 1LL << i, t = (s << 1LL) - 1; // 两个 x 的区间
        if ((s & n) == 0) {
            continue;
        }
        int L = max(l, s), R = min(r, t);
        ans = max(ans, ans + R - L + 1);
    }
    cout << ans;
    
    return 0;
}
```

---

