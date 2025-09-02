# ロト2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ddcc2016-qual/tasks/ddcc_2016_qual_c

$ N $ 枚のカードが $ 1 $ 列に並べられており、$ i(1\ ≦\ i\ ≦\ N) $ 番目のカードには整数 $ A_i $ が書かれています。

この $ N $ 枚のカードを使ったロト $ 2 $ という宝くじがあります。 ロト $ 2 $ は $ 1 $ 番から $ N $ 番までの番号から異なる $ 2 $ つの番号 $ i,\ \,\ j\ (i\ <\ j) $ を選び、選ばれた $ 2 $ つの番号のカードにそれぞれ書かれた値の積 $ A_i\ A_j $が $ K $ の倍数となるとき当選するというルールで行われます。

$ A_iA_j $ が $ K $ の倍数となるような $ i $ と $ j $ の組合せ $ (i,\ \,\ j) $ を良い組合せと呼ぶことにします。良い組合せは何通りあるか求めなさい。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 200{,}000 $
- $ 1\ ≦\ A_i\ ≦\ 10^{9}\ (1\ ≦\ i\ ≦\ N) $
- $ 1\ ≦\ K\ ≦\ 10^{9} $
- $ A_i,\ \,\ K $ はいずれも整数

### Sample Explanation 1

$ (1,\ \,\ 4),\ \,\ (2,\ \,\ 3),\ \,\ (2,\ \,\ 4),\ \,\ (3,\ \,\ 4) $ の $ 4 $ 通りが良い組合せです。

### Sample Explanation 2

どのように $ 2 $ つの番号を選んでも良い組合せになります。

## 样例 #1

### 输入

```
4 6
1 3 2 6```

### 输出

```
4```

## 样例 #2

### 输入

```
5 1
1 2 3 1 2```

### 输出

```
10```

## 样例 #3

### 输入

```
12 60
38 19 180 222 560 1000 7 99 845 3600 12 90```

### 输出

```
33```

# 题解

## 作者：sto_yyrdxh_orz (赞：2)

## 题目大意：
第一行两个正整数 $n$ 和 $k$，接下来 $n$ 一行，$n$ 个数字，你可以选两个数字 $a_i$ 和 $a_j$ 如果它们的乘积是 $k$ 的倍数，将答案加一，输出答案。

### 分析：
我们利用类似冒泡排序的思想，每次都想后找一个数 $j$ 和当前的 $i$ 相乘，判断是否是 $k$ 的倍数，如果是，就将答案加一。

#### 具体代码：
```cpp
#include <iostream>
using namespace std;
int n, k, a[200001], ans;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		//输入 
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			//每次都向后找，类似冒泡排序 
			int sum=a[i]*a[j];
			//a[i]和a[j]的乘积 
			if(sum%k==0){
				//是k的倍数 
				ans++;
				//方案数加一 
			}
		}
	}
	cout<<ans<<endl;
	//输出 
	return 0;
} 
```

---

## 作者：Nygglatho (赞：1)

一个朴素算法是暴力枚举，但是 $1 \le N \le 2 \times 10^5$，很明显会超时。

接下来我们考虑去重。

显然只要两个数 $A_i, A_j$ 的质因子中有 $K$ 的全部质因子，那么乘积就是 $K$ 的倍数。

而这两个数中其他质因子，都与乘积是否是 $K$ 的倍数**无关**。

那么既有 $A_i$ 的所有质因子又有 $K$ 的所有质因子，明显就是它们的最大公因数，即 $\gcd(A_i, K)$，$A_j$ 也一样，既然只通过 $\gcd(A_i, K)$ 以及 $\gcd(A_j, K)$ 来决定乘积是否是 $K$ 的倍数，那么可以将 $A$ 中与 $K$ 最大公因数的数归到一类。

接下来，每一类中，如果类别 $i, j$ 不相等且 $i < j$，设第 $i$ 类有 $x$ 个，第 $j$ 类有 $y$ 个数字，那么很显然有 $x \times y$ 种方案。如果 $i = j$，这一类中数字 $t$ 选择不了 $t$ 及在 $t$ 后面的数（见下图），那么就有 $\dfrac{x(x - 1)}{2}$ 种选择方案，否则，$i > j$，那么与 $i < j$ 情况重复，所以没有选择方案。

![](https://s2.loli.net/2022/01/15/VcjMrEqS2GbH4aN.jpg)

（当 $i = j$ 时，$i$ 中的数字用 $t_1, t_2, t_3, t_4$ 代替。）

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

map<ll, ll> p;
ll n, k, s;

ll gcd(ll x, ll y) {return y == 0 ? x : gcd(y, x % y);}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll q;
	cin >> n >> k;
	for (ll i = 1; i <= n; ++i) {
		cin >> q;
		++p[gcd(q, k)];
	}
	for (auto i : p) {
		for (auto j : p) {
			if (i.first > j.first || i.first * j.first % k != 0) continue;//i > j 或者不是 k 的倍数
			else if (i.first < j.first) s += i.second * j.second;//i < j
			else s += (i.second * i.second - i.second) / 2;//最后那种情况
		}
	}
	cout << s << endl;
} 
```

---

