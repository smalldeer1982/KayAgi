# [ARC126B] Cross-free Matching

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc126/tasks/arc126_b

座標平面上に、$ x $ 座標が $ 1,\ 2,\ \ldots,\ N $、$ y $ 座標が $ 0 $ または $ 1 $ であるような合計 $ 2N $ 個の頂点 $ (1,\ 0),\ldots,\ (N,0),\ (1,1),\ \ldots,\ (N,1) $ があります。 これらのうちの $ 2 $ 頂点を結ぶ線分が $ M $ 個あり、$ i $ 番目の線分は $ (a_i,\ 0) $ と $ (b_i,\ 1) $ を結んでいます。

これら $ M $ 個の線分から $ K $ 個の線分を選び、選んだ線分のうちどの $ 2 $ 個の線分も同一の点を含まないようにすることを考えます。ただし、線分の両端点も線分に含まれる点として扱います。可能な $ K $ の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N,\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ a_i,\ b_i\leq\ N $
- $ i\neq\ j $ ならば、$ a_i\neq\ a_j $ または $ b_i\neq\ b_j $

### Sample Explanation 1

$ 1,\ 2 $ 番目の線分を選ぶことが、最適解のひとつです。 例えば $ 1 $ 番目の線分と $ 3 $ 番目の線分は同一の点 $ \left(\frac53,\ \frac23\right) $ を含むため、同時に選ぶことはできません。 !\[\](https://img.atcoder.jp/arc126/3e4cb12392855ea49b7ed0b643ebd370.png)

### Sample Explanation 2

$ 1,\ 3,\ 5 $ 番目の線分を選ぶことが、最適解のひとつです。 例えば $ 1 $ 番目の線分と $ 2 $ 番目の線分は同一の点 $ (1,\ 1) $ を含むため、同時に選ぶことはできません。 !\[\](https://img.atcoder.jp/arc126/416681cace776c87fac353e0acb9c4a1.png)

### Sample Explanation 3

!\[\](https://img.atcoder.jp/arc126/2436c39ccc0fa35fc57d35647bce9f08.png)

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3 5
1 1
2 1
2 2
3 2
3 3```

### 输出

```
3```

## 样例 #3

### 输入

```
7 5
1 7
7 1
3 4
2 6
5 2```

### 输出

```
1```

# 题解

## 作者：fush (赞：3)

## 题意
有两行，一行 $n$ 个点，和 $m$ 条线（从第一行的节点连向第二行的节点）。
现在问你最多留下多少线，能使任意两条线均不相交。
## 思路
为了方便描述，第 $a$ 条线的第一行节点是 $a_x$，第二行节点是 $a_y$。

显然，两条相交的线 $a, b$ 必然满足，$a_x < b_x \land a_y > b_y$ 或是 $a_x = a_x \lor a_y = b_y$。

那么我们对 $a_x$ 做升序，相等时 $a_y$ 做降序（规避第二种情况）。

这样我们只需要对 $a_y$ 求最长上升子序列即可。
## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
constexpr int N = 1e6 + 10;
struct A{int x, y;}a[N];
int f[N], tot, n, m;
int find(int x){
	int l = 0, r = tot;
	while(l < r){
		int mid = (l + r) >> 1;
		if(f[mid] < x)l = mid + 1;
		else r = mid;
	}
	return l;
}
int32_t main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
		cin >> a[i].x >> a[i].y;
	sort(a + 1, a + 1 + m, [](A&i, A&j){return (i.x ^ j.x) ? (i.x < j.x) : (i.y > j.y);});
	f[tot = 1] = a[1].y;
	for(int i = 1; i <= m; i++){
		if(a[i].y > f[tot])f[++tot] = a[i].y;
		else f[find(a[i].y)] = a[i].y;
	}
	cout << tot << endl;
	return 0;
}
```

---

## 作者：SlyCharlotte (赞：0)

# 题意
$n$ 个点，$m$ 个匹配。

$m$ 行数，每行两个数，表示 $(a_i, 0)$ 和 $(1, b_i)$ 有一条边。

现在问你，左边的一个点最多匹配右边的一个点，注意：任意两个边不能有交点，最多匹配多少个边。

# 分析
题目让保证不能存在逆序对，同时一个点只能匹配一个点，所以我们求的是序列的最长上升子序。

相对于城市匹配，每个点在给的时候可以有多个匹配的，我们可以对第一维升序，第二维降序，通过单调栈来维护上升子序就保证每个 $x$ 只会向栈中添加一个元素。
# 代码
```cpp

struct Node{
  int x, y;
  bool operator< (const Node &W) const{
    if (x == W.x) return y > W.y;
    return x < W.x;
  }
}a[N];
int stk[N], top;//求最长上升子序列
int main()
{
  cin >> n >> m;
  for (int i = 0; i < m; i ++ )
  {
    int x, y; scanf("%d%d", &x, &y);
    a[i] = {x, y};
  }
  sort(a, a + m);
  for (int i = 0; i < m; i ++ )
  {
    if (!top || a[i].y > stk[top]) stk[++ top] = a[i].y;
    else *lower_bound(stk + 1, stk + 1 + top, a[i].y) = a[i].y;
    // printf("top = %d, stk[top] = %d, a[i].x = %d, a[i].y = %d\n", top, stk[top], a[i].x, a[i].y);
  }
  // for (int i = 1; i <= top; i ++ ) cout << stk[i] << " ";
  // cout << endl;
  cout << top << endl;
  return 0;
}
```

---

