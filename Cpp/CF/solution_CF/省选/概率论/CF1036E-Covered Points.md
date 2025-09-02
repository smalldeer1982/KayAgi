# Covered Points

## 题目描述

You are given $ n $ segments on a Cartesian plane. Each segment's endpoints have integer coordinates. Segments can intersect with each other. No two segments lie on the same line.

Count the number of distinct points with integer coordinates, which are covered by at least one segment.

## 说明/提示

The image for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036E/328bc786470ca0c6c881c66bf4ab063a98d10f53.png)Several key points are marked blue, the answer contains some non-marked points as well.

The image for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1036E/eec87126bd479256c1ebc7932fb835380371e1c1.png)

## 样例 #1

### 输入

```
9
0 0 4 4
-1 5 4 0
4 0 4 4
5 2 11 2
6 1 6 7
5 6 11 6
10 1 10 7
7 0 9 8
10 -1 11 -1
```

### 输出

```
42
```

## 样例 #2

### 输入

```
4
-1 2 1 2
-1 0 1 0
-1 0 0 3
0 3 1 0
```

### 输出

```
7
```

# 题解

## 作者：nekko (赞：5)

发现$n$只有$1000$，不妨直接两两线段求交，然后去重复，然后统计一下就行了

---

关于求交：

对于一条线段（这里是整数意义上的线段，也就是一个等差数列)，可以将它写成

$$\begin{cases} x_i=k_i u_i+x_0 \\ y_i=k_iv_i+y_0 \end{cases}$$

的形式，当然这是一条“射线”，与另一条“射线”联立后如果有解还需要判断是否在合法

---

关于统计：

对于每一条线段，首先算出来它上面有多少个整点，也就是$p_i=\gcd(abs(x_1-x_0), abs(y_1-y_0))+1$

然后计算这条线段上面有多少个整点，满足这个整点还在其它线段上（也就是求一下和其它线段的交点然后去一下重），设个值为$q_i$

那么把$p_i-q_i$累加到答案里

最后把所有的交点去重后的个数加到答案里

然后就做完了

---

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;
int cnt[N];

struct P {
	int x, y;
};
bool operator < (P a, P b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
P operator - (P a, P b) { return (P) { a.x - b.x, a.y - b.y}; }
ll operator * (P a, P b) { return (ll) a.x * b.y - (ll) b.x * a.y; }

struct LINE {
	P a, b;
	ll d;
} ln[N];

ll ans;

set<P> s[N], glo;

ll x, y;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
void exgcd(ll a, ll b, ll &x, ll &y) {
	if(!b) {
		x = 1, y = 0;
	} else {
		exgcd(b, a % b, y, x);
		y -= x * (a / b);
	}
}

const P fl = (P) { (int) 1e7, (int) 1e7 };

bool in(ll x, ll l, ll r) {
	if(l > r) swap(l, r);
	return l <= x && x <= r;
}

P get(LINE a, LINE b) {
	ll x0 = a.a.x, y0 = a.a.y;
	ll u0 = (a.b.x - a.a.x) / a.d;
	ll v0 = (a.b.y - a.a.y) / a.d;
	
	ll x1 = b.a.x, y1 = b.a.y;
	ll u1 = (b.b.x - b.a.x) / b.d;
	ll v1 = (b.b.y - b.a.y) / b.d;
	
//	cout << "x0 = " << x0 << " y0 = " << y0 << endl;
//	cout << "u0 = " << u0 << " v0 = " << v0 << endl;
//	cout << "x1 = " << x1 << " y1 = " << y1 << endl;
//	cout << "u1 = " << u1 << " v1 = " << v1 << endl;
	
	ll up1 = (y1 - y0) * u0 - (x1 - x0) * v0;
	ll dw1 = u1 * v0 - v1 * u0;
	if(!dw1 || up1 % dw1) return fl;
	ll k1 = up1 / dw1;
	
	ll x = x1 + k1 * u1, y = y1 + k1 * v1;
	
//	cout << x << ' ' << y << endl;
	
	if(
	
	in(x, a.a.x, a.b.x) &&
	in(y, a.a.y, a.b.y) &&
	in(x, b.a.x, b.b.x) &&
	in(y, b.a.y, b.b.y)
	
	) {
		return (P) { x, y };
	} else {
		return fl;
	}
}

int main() {
//	freopen("data.in", "r", stdin);
	ios :: sync_with_stdio(0);
	int n; cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> ln[i].a.x >> ln[i].a.y >> ln[i].b.x >> ln[i].b.y;
		ln[i].d = gcd(abs(ln[i].a.x - ln[i].b.x), abs(ln[i].a.y - ln[i].b.y));
	}
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= n ; ++ j) {
			
//			if(i == 1 && j == 2)
			
			if(i != j) {
				P p = get(ln[i], ln[j]);
//				if(i == 1 && j == 2) {
//					cout << "( " << p.x << ", " << p.y << " )" << endl;
//				}
				if(p.x != 1e7) {
					s[i].insert(p);
					glo.insert(p);
				}
			}
		}
		ans += ln[i].d + 1 - s[i].size();
	}
	ans += glo.size();
//	cout << "glo.size() == " << glo.size() << endl;
//	for(auto v: glo) {
//		cout << "(" << v.x << ", " << v.y << ")" << endl;
//	}
	cout << ans << endl;
}
```

---

## 作者：紊莫 (赞：0)

我们把线段看作是动态的加入。

对于一条线段上的整点数量是好算的，然后枚举之前已经加入的线段，减去交点数量就是新增加的整点数量。

**切忌使用浮点运算**，否则会被卡精度，判断方法可以将其看作两个等差数列后求解二元一次方程，具体可以看其他题解。

[代码实现。](https://codeforces.com/contest/1036/submission/275882815)

---

