# 右折

## 题目描述

[problemUrl]: https://atcoder.jp/contests/mujin-pc-2018/tasks/mujin_pc_2018_c

$ N $ 行 $ M $ 列のマス目があります。上から $ i $ 行目、左から $ j $ 列目にあるマスを $ (i,j) $ で表します。 特に、左上のマスは $ (1,1) $ であり、右下のマスは $ (N,M) $ です。 マス目の状態は 二次元配列 $ s $ で表され、$ s_{ij} $ が `#` のときマス $ (i,j) $ には障害物があり、`.` のとき障害物がないことを表します。

高橋君は、このマス目のいずれかのマスに、上下左右いずれかの方向を向けたロボットを置きました。 ロボットは向いている方向に $ 1 $ マス以上まっすぐ進んだ後、向きを右に $ 90 $ 度変え、再びまっすぐに $ 1 $ マス以上進んで停止しました。 この過程でロボットが通ったマス(置かれたマスおよび停止したマスを含む)のいずれにも障害物はなく、またロボットがマス目の外に出ることはありませんでした。

ロボットが置かれたマスと停止したマスの順序対としてありうるものの個数を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N,M\ \leq\ 2\times\ 10^3 $
- $ s_{ij} $ は `#` または `.` である

### Sample Explanation 1

$ ((1,1),(2,2)),((1,1),(3,2)),((1,2),(2,1)),((2,1),(1,2)),((2,1),(3,2)),((2,2),(1,1)),((2,3),(1,2)),((2,3),(1,1)),((3,2),(2,3)) $ の $ 9 $ 個が条件を満たします。

## 样例 #1

### 输入

```
3 3
..#
...
#.#```

### 输出

```
9```

## 样例 #2

### 输入

```
2 5
.#.#.
..#..```

### 输出

```
2```

## 样例 #3

### 输入

```
6 8
#......#
##....##
#.#..#.#
#..##..#
#......#
#......#```

### 输出

```
182```

# 题解

## 作者：SuyctidohanQ (赞：0)

### 思路分析

这是一道简单的模拟题，建议评  ${\color{yellow} {普及/提高-}}$。

如果能求出在某个方格中将方向改变 $90$ 度的起点和终点组的个数，就能解决这个问题。

如果该方格的上下左右（不包括该方格）有 $a, b, c, d$ 块没有东西阻挡的方格，则有 $(a + b) \times (c + d)$ 就变成了该方格。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN = 2000 + 10;
ll n, m, shu1[MAXN][MAXN], shu2[MAXN][MAXN], ans = 0;
char s[MAXN][MAXN];
int main() {
	cin >> n >> m;
	for (ll i = 0; i <= (n - 1); i ++) cin >> s[i];
	for (ll i = 0; i <= (n - 1); i ++) {
		ll cun = 0;
		for (ll j = 0; j <= m; j ++) {
			if (s[i][j] != '.') {
				for (ll k = cun; k <= (j - 1); k ++) shu1[i][k] = (j - cun - 1);
				cun = j + 1;
			}
		}
	}
	for (ll i = 0; i <= (m - 1); i ++) {
		ll cun = 0;
		for (ll j = 0; j <= n; j ++) {
			if (s[j][i] != '.') {
				for (ll k = cun; k <= (j - 1); k ++) shu2[k][i] = (j - cun - 1);
				cun = j + 1;
			}			
		}
	}
	for (ll i = 0; i < n; i ++)
		for (ll j = 0; j < m; j ++) ans += (shu1[i][j] * shu2[i][j]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：banglee (赞：0)

## AT_mujin_pc_2018_c 右折 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_mujin_pc_2018_c)

## 正文
这是一道简单的模拟题。

~~在你的脑海里~~想象一个能旋转 $90$ 度的方格。如果能快速求出在某个方格中将方向改变 $90$ 度的起点和终点组的个数，就能解决这个问题。

这意味着，如果该方格的上下左右（不包括该方格）有 $u,d,l,r$ 块没有东西阻挡的方格，则有 $(u + d) \times (l + r)$ 就变成了该方格。由于从上、下、左、右依次查看正方形，所以可以在 $O(NM)$ 时间内找到 $u,d,l,r$。

## Code
```
#include<bits/stdc++.h>
using namespace std;
int n,m,w[2005][2005],h[2005][2005];
char a[2005][2005];
long long ans;
signed main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		int t=0;
		for(int j=0;j<=m;j++)
			if(a[i][j]!='.')
			{
				for(int k=t;k<j;k++)
					w[i][k]=j-t-1;
				t=j+1;
			}
	}
	for(int j=0;j<m;j++)
	{
		int t=0;
		for(int i=0;i<=n;i++)
			if(a[i][j]!='.')
			{
				for(int k=t;k<i;k++)
					h[k][j]=i-t-1;
				t=i+1;
			}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			ans+=w[i][j]*h[i][j];
	cout<<ans;
	return 0;
}
```

---

