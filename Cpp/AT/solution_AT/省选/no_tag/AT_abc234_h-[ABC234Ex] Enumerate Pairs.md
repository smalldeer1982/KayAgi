# [ABC234Ex] Enumerate Pairs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc234/tasks/abc234_h

$ 1 $ から $ N $ までの番号のついた $ N $ 個の整数の組 $ (x_i,y_i) $ と、整数 $ K $ が与えられます。  
 以下の条件を満たす整数の組 $ (p,q) $ を「出力」で指定する形式に従ってすべて列挙してください。

- $ 1\ \le\ p\ <\ q\ \le\ N $
- $ \sqrt{(x_p-x_q)^2+(y_p-y_q)^2}\ \le\ K $

ただし、そのような整数の組が $ 4\ \times\ 10^5 $ 組以下であることは保証されます。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ K\ \le\ 1.5\ \times\ 10^9 $
- $ 0\ \le\ x_i,y_i\ \le\ 10^9 $
- 列挙すべき整数の組は $ 4\ \times\ 10^5 $ 組以下である

### Sample Explanation 1

条件を満たす整数の組は以下の $ 9 $ 個なので、これを出力形式に従って出力して下さい。 $ (1,2),(1,3),(1,4),(2,3),(2,4),(2,5),(3,4),(3,5),(5,6) $

### Sample Explanation 2

条件を満たす整数の組が $ 0 $ 組である場合もあります。

### Sample Explanation 3

$ x_i=x_j $ かつ $ y_i=y_j $ であるような整数の組 $ (i,j) $ ($ i\ <\ j $) が存在する場合もあります。

## 样例 #1

### 输入

```
6 5
2 0
2 2
3 4
0 0
5 5
8 3```

### 输出

```
9
1 2
1 3
1 4
2 3
2 4
2 5
3 4
3 5
5 6```

## 样例 #2

### 输入

```
2 1414213562
0 0
1000000000 1000000000```

### 输出

```
0```

## 样例 #3

### 输入

```
10 150
300 300
300 400
300 500
400 300
400 400
400 400
400 500
500 300
500 400
500 500```

### 输出

```
29
1 2
1 4
1 5
1 6
2 3
2 4
2 5
2 6
2 7
3 5
3 6
3 7
4 5
4 6
4 8
4 9
5 6
5 7
5 8
5 9
5 10
6 7
6 8
6 9
6 10
7 9
7 10
8 9
9 10```

# 题解

## 作者：MatrixGroup (赞：15)

## 题意

给你平面上 $N$ 个点的坐标，问你有多少对点的欧几里得距离 $\leqslant K$，按字典序从小到大输出它们。

$N\le 2\times10^5$。保证答案点对数不超过 $4\times10^5$。

## 分析

平面最近点对类型的题可以考虑随机旋转。

随机旋转一个角度，把点按照横坐标排序，枚举其之后的 $18\ 000$ 个点，判断距离是否小于等于 $K$ 即可。

## 代码

```cpp
vector<pair<int,int> > ans;
int n;ll k,x[200005],y[200005];
ll q[200005],r[200005];
int p[200005];
bool cmp(int u,int v)
{
	return (x[u]-x[v])*361425<(y[u]-y[v])*130113;
}
inline ll sq(ll x)
{
	return x*x;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin>>n>>k;
	rep1(i,n)
	{
		p[i]=i;
		cin>>x[i]>>y[i];
	}
	sort(p+1,p+n+1,cmp);
	rep1(i,n)
	{
		q[i]=x[p[i]];r[i]=y[p[i]];
	}
	k*=k;
	rep1(i,n)
	{
		for(int j=min(i+18000,n);j>i;--j)
		{
			if(sq(q[i]-q[j])+sq(r[i]-r[j])<=k)
			ans.pb(mp(min(p[i],p[j]),max(p[i],p[j])));
		}
	}
	cout<<ans.size()<<endl;
	sort(ans.begin(),ans.end());
	for(pair<int,int>P:ans)cout<<P.fi<<" "<<P.se<<endl;
	return 0;
}
```

---

## 作者：altgo (赞：8)

## 题目大意

给你平面上 $N$ 个点的坐标，问你有多少对点的欧几里得距离 $\leqslant K$，按字典序从小到大输出它们。

保证答案点对数不超过 $4\times10^5$。

## 题解

诡题。

平面分块，划分成 $K\times K$ 的正方形。

然后点 $(x,y)$ 属于正方形 $([x/K],[y/K])$。

假如一个点在的正方形为 $(a,b)$，则和这个点距离小于等于 $K$ 的点必然只会在 $(a+c,b+d),-1\le c,d\le 1$。

然后我们暴力枚举每个点以及以其正方形为中心的九宫格中的每个点判断是否合法。

输出即可。

接下来证明复杂度的正确性。

观察到一个正方形内的点是很容易满足条件的。我们设正方形内有 $x$ 个点，我们证明其有 $O(n^2)$ 个满足条件的点对。

我们将这个正方形划分成四个 $(K/2)\times(K/2)$ 的小正方形，观察到小正方形内的点对必然满足条件。我们设四个小正方形分别有 $a,b,c,d$ 个点。

我们有 $a+b+c+d=x$，不妨设 $a\ge b\ge c\ge d$，因此 $a\ge \frac{x}{4}$，所以至少有一个小正方形内有 $\frac{a(a-1)}{2}$。

所以是 $O(x^2)$ 的，带小常数。

设 $B_{i,j}$ 表示 $(i,j)$ 内的点数。那么我们有 $\sum_{i,j}B_{i,j}^2\le 400000\times C$。

我们匹配相邻九宫格的复杂度是 $B_pB_q$，显然其 $\le \max^2(B_p,B_q)$，因此总复杂度还是 $C\sum_{i,j}B_{i,j}^2$，也就是 $\le 400000C$。

重新考虑这个过程，发现只需要随便设一个比较合适的正方形大小，比如说 $\sqrt 2 K\times \sqrt 2K$ 之类的正方形大小，复杂度也是对的。

---

## 作者：yhylivedream (赞：6)

根号很不好维护，先给式子左右平方，$(x_p-x_q)^2+(y_p-y_q)^2\le k^2$。

考虑计算满足 $(x_p-x_q)^2\le k^2$ 的二元组，再在剩下的二元组中计算 $(y_p-y_q)^2\le k^2$ 的二元组，再在经过两次筛选的二元组中判断答案。

筛选 $(x_p-x_q)^2\le k^2$ 的二元组时可以左右开方变成 $x_p-x_q\le k$，纵坐标同理。

## 代码

```cpp
//author : yhy
#include <bits/stdc++.h> 

using namespace std;
using LL = long long;
using Pii = pair<LL, LL>;
using Ppiii = pair<Pii, LL>;

const LL kMaxN = 2e5 + 5, kInf = 1e18;

LL n, k;
set<Pii> st;
Ppiii a[kMaxN];
vector<Pii> ans;

signed main() {
  cin.tie(0)->ios::sync_with_stdio(0), cin >> n >> k;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i].first.first >> a[i].first.second;
    a[i].second = i;
  }
  sort(a + 1, a + n + 1), st.insert({kInf, 0});
  for (LL i = 1, j = 1; i <= n; i++) {
    for (; a[i].first.first - a[j].first.first > k; j++) {
      st.erase({a[j].first.second, j});
    }
    auto it = st.lower_bound({a[i].first.second - k, 0});
    for (; (*it).first <= a[i].first.second + k; it++) {
      if ((a[(*it).second].first.first - a[i].first.first) * (a[(*it).second].first.first - a[i].first.first)
      + (a[(*it).second].first.second - a[i].first.second) * (a[(*it).second].first.second - a[i].first.second) <= k * k) {
        LL tx = a[(*it).second].second, ty = a[i].second;
        tx > ty && (swap(tx, ty), 0), ans.push_back({tx, ty});
      }
    }
    st.insert({a[i].first.second, i});
  }
  cout << ans.size() << '\n', sort(ans.begin(), ans.end());
  for (Pii x : ans) {
    cout << x.first << ' ' << x.second << '\n';
  }
}
```

这不比分治好写 $114$ 倍。

---

