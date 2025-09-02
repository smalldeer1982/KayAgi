# のびたす

## 题目描述

[problemUrl]: https://atcoder.jp/contests/pakencamp-2020-day1/tasks/pakencamp_2020_day1_l

配点 : $ 500 $ 点

 筑駒 71 期の数学の授業では、「のびたす」という演算が登場しました。 $ x $ のびたす $ y $ は、$ x,\ y $ を文字列として見て連結する操作を表します。

 例えば、$ 10 $ のびたす $ 20=1020 $ です。 ある正整数 $ x $ に対して、$ i=1,\ 2,\ldots,\ Q $ について以下の操作のいずれか片方を選んで行うことを考えます。

1. $ x $ を $ x+A_i $ で置き換える
2. $ x $ を $ x $ のびたす $ A_i $ で置き換える
 
 操作の仕方は $ 2^Q $ 通りありますが、それら全てについて最終的な $ x $ を求め、その総和を $ 10^9+7 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
1 3
10```

### 输出

```
323```

## 样例 #2

### 输入

```
4 10
12
21
30
9```

### 输出

```
116122282```

## 样例 #3

### 输入

```
10 102
2109
10329
710923
49832
5437
57432389
78322
572973938
923483
998244353```

### 输出

```
986794595```

# 题解

## 作者：analysis (赞：1)

对于拼接操作，假设 $a$ 的长度（十进制下的位数）为 $s$，则相当于 $x \to x \times 10^s+a$。

于是直接跟加法一起维护就好了。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod=1e9+7;
using namespace std;
int q,x,y,a,b,sz;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>q>>x;
    for(int i=1,num=2;i<=q;i++,num=num*2%mod){
        cin>>a;b=a,sz=1,y=0;
        while(b)b/=10,sz=sz*10%mod;
        y=(x+x*sz%mod)%mod;
        y=(y+num*a%mod)%mod;
        x=y;
    }
    cout<<x<<'\n';
    return 0;
}
```

---

## 作者：dvsfanjo (赞：0)

# 题解：AT_pakencamp_2020_day1_l のびたす

## 思路

观察递推式，要计算以下两个东西：

$\log_{10} a$ 和 $a^b \bmod (10^9+7)$ 。

对于第一个，直接循环除以 $10$ 直到除不了为止.


```cpp
ll lg10(ll x) {
	ll cnt = -1;
	while (x) {
		x /= 10;
		cnt++;
	}
	return cnt;
}
```

对于第二个，只用快速幂就好了，不会的去[ P1226 ](https://www.luogu.com.cn/problem/P1226) 学。

每次递推需要第二个操作套第一个操作，故总复杂度为 $O(n \log n)$ 。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
ll n, f, a;
ll lg10(ll x) {
	ll cnt = -1;
	while (x) {
		x /= 10;
		cnt++;
	}
	return cnt;
}
ll qpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> f;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		f = f * (qpow(10, lg10(a) + 1) + 1) + qpow(2, i) * a;
		f %= mod;
	}
	cout << f << '\n';
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/pakencamp-2020-day1/submissions/59733678)。

看不懂日语，但感觉翻译把题意化简了很多。

---

