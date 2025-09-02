# Nice Shopping

## 题目描述

[problemUrl]: https://atcoder.jp/contests/hitachi2020/tasks/hitachi2020_b

あなたは、冷蔵庫と電子レンジを買うために、とある家電量販店に来ました。

この家電量販店では、 $ A $ 種類の冷蔵庫と $ B $ 種類の電子レンジが販売されています。 $ i $ 番目( $ 1\ \le\ i\ \le\ A $ )の冷蔵庫の値段は $ a_i $ 円であり、 $ j $ 番目( $ 1\ \le\ j\ \le\ B $ )の電子レンジの値段は $ b_j $ 円です。

また、あなたは $ M $ 種類の割引券を所持しており、 $ i $ 番目 ( $ 1\ \le\ i\ \le\ M $ )の割引券では、 $ x_i $ 番目の冷蔵庫 と $ y_i $ 番目の電子レンジを同時に買うと、 支払総額が $ c_i $ 円安くなります。ただし、複数の割引券を同時に使うことはできません。

さて、あなたは冷蔵庫と電子レンジをちょうど $ 1 $ 台ずつ買おうと思っています。かかる金額の最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ A\ \le\ 10^5 $
- $ 1\ \le\ B\ \le\ 10^5 $
- $ 1\ \le\ M\ \le\ 10^5 $
- $ 1\ \le\ a_i\ ,\ b_i\ ,\ c_i\ \le\ 10^5 $
- $ 1\ \le\ x_i\ \le\ A $
- $ 1\ \le\ y_i\ \le\ B $
- $ c_i\ \le\ a_{x_i}\ +\ b_{y_i} $

### Sample Explanation 1

$ 1 $ 番目の冷蔵庫と $ 2 $ 番目の電子レンジを買うと、割引券の効果により $ 3+3-1=5 $ 円になります。

### Sample Explanation 2

複数の割引券を同時に使うことはできないことに注意してください。

### Sample Explanation 3

この場合は $ 1 $ 番目の冷蔵庫と $ 1 $ 番目の電子レンジを買うと $ 6 $ 円になり、これが最小です。 割引券は使わなくてもよいことに注意してください。

## 样例 #1

### 输入

```
2 3 1
3 3
3 3 3
1 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
1 1 2
10
10
1 1 5
1 1 10```

### 输出

```
10```

## 样例 #3

### 输入

```
2 2 1
3 5
3 5
2 2 2```

### 输出

```
6```

# 题解

## 作者：w33z8kqrqk8zzzx33 (赞：1)

首先，答案上限是 $\min a + \min b$。 可以 $O(n)$ 的处理这两个值。

第二，如果可以得到比以上上限更优的答案，那肯定是从应用一个优惠券得到的。

来证明，可以使用反证法：假设没有应用一个优惠券，然后选了 $i$，$j$ 使得 $a_i + b_j < \min a + \min b$。显然不可能，应为 $\min a$ 是 $a$ 的最小值和 $\min b$ 是 $b$ 的最小值。

这样，就枚举所有优惠券，并且更新答案如果一个或者多个优惠券会降低答案。

去掉长板子的代码：

```cpp
int A[100005], B[100005];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int a, b, m; gi(a); gi(b); gi(m);
	int oa = 100005, ob = 100005;
	rep1(i, a) {
		gi(A[i]);
		oa = min(oa, A[i]);
	}
	rep1(i, b) {
		gi(B[i]);
		ob = min(ob, B[i]);
	}
	int opt = oa + ob;
	rep(i, m) {
		int x, y, c; 
		gi(x); gi(y); gi(c);
		opt = min(opt, A[x] + B[y] - c);
	}
	cout << opt << endl;
}
```

---

## 作者：SpeedStar (赞：1)

## 算法
先分别求一下冰箱和微波炉的最小值，再将二者相加作为答案，然后将这个答案在用过打折券的情况下每次和用过打折券的结果取$min$更新答案。

## C++代码
```cpp
#include <iostream>
#define rep(i, n) for (i = 1; i <= n; i++)

using namespace std;

const int N = 1e5 + 10;

int a[N], b[N];
int A, B, M;

int main() {
	cin >> A >> B >> M;
	int i;
	rep(i, A) cin >> a[i];
	rep(i, B) cin >> b[i];
	
    int minA = a[1];
    rep(i, A) minA = min(minA, a[i]);
    
    int minB = b[1];
    rep(i, B) minB = min(minB, b[i]);
	
	int res = minA + minB;
	rep(i, M) {
		int x, y, c;
		cin >> x >> y >> c;
		int hoge = a[x] + b[y] - c;
		if (hoge < 0) hoge = 0;
		res = min(res, hoge);
	}
	
	cout << res << endl;
	
	return 0;
}
```


---

## 作者：Zirnc (赞：0)

[ChungZH's blog](https://chungzh.cn/) · [ChungZH's portfolio](https://chungzh.cc/)

## 题目

您正在逛一家大型电子产品商店，购买冰箱和微波炉。

这家商店出售 $A$ 类冰箱和 $B$ 类微波炉。第 $i$ 台冰箱 $(1 \le i \le)$ 以 $a_i$ 日元出售，第 $j$ 个微波炉 $(1 \le j \le B)$ 售价为 $b_j$ 日元。

您有 $M$ 张优惠票。使用第 $i$ 张票 $(1 \le i \le M)$，当一起购买第 $x_i$ 个冰箱和第 $y_i$ 个微波炉时，您可以从总价格中获得 $c_i$ 日元的折扣。一次只能使用一张票。

您打算购买一台冰箱和一台微波炉。 找到所需的最低金额。

## 题解

模拟模拟模拟。

首先找到最便宜的冰箱和微波炉的总价，然后输入 $M$ 张优惠券的信息，比较哪个便宜，计入变量，最后输出。

```cpp
#include <bits/stdc++.h>
using namespace std;

int A, B, M;
int main() {
  cin >> A >> B >> M;
  int a[A], b[B];
  int minA = 1e9;
  int minB = 1e9;
  for (int i = 0; i < A; i++) {
    cin >> a[i];
    minA = min(minA, a[i]);
  }
  for (int i = 0; i < B; i++) {
    cin >> b[i];
    minB = min(minB, b[i]);
  }
  int ans = minA + minB;

  int x, y, c;
  for (int i = 0; i < M; i++) {
    cin >> x >> y >> c;
    x--;
    y--;
    ans = min(ans, a[x] + b[y] - c);
  }
  cout << ans << endl;
  return 0;
}
```

---

## 作者：leoair (赞：0)

# Nice Shopping

题目大意:给定一个长度为$A$的数列$a$和长度为$B$的数列$b$，并且有$m$个减操作，让$a_x+b_y$的和减去$c$。求$a_i+b_j(1\leq i\leq A,1\leq j\leq B)$的最小值。

这道题其实可以定义一个$ans$记录最小值，然后记录$\min(a_x+b_y-c,ans)$。最后把数列$a$和数列$b$sort一遍，再输出$\min(ans, a_1+b_1)$即可。

接下来看看实现:

### Code:

```cpp
#include <bits/stdc++.h>
#define REP(i, a, b) for (long long i = a; i <= b; ++i)
#define sort(a, b) sort(((a) + 1), ((a) + (b) + 1))
#define ll long long
#define N 100010
using namespace std;

ll m, A, B, ans = INT_MAX, a[N], b[N];

inline ll read(){
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') w *= -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

inline void work(){
	A = read(), B = read(), m = read();			//长度为A的数列a，长度为B的数列B，进行m次减操作 
	REP(i, 1, A) a[i] = read();					//输入序列a 
	REP(i, 1, B) b[i] = read();					//输入序列b 
	REP(i, 1, m){								//依次枚举每个减去的操作 
		ll x = read(), y = read(), c = read();	//a[x]+b[y]-c
		ans = min(ans, a[x] + b[y] - c);		//记录最小值 
	}
	sort(a, A);									//从小到大排序序列a 
	sort(b, B);									//从小到大排序序列b
	printf("%lld\n", min(ans, a[1] + b[1]));	//输出ans和a[1]+b[1]的最小值 
}

int main(){
	work();
	return 0;
}
```



---

