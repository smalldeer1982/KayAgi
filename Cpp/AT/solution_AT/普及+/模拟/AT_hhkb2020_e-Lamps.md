# Lamps

## 题目描述

[problemUrl]: https://atcoder.jp/contests/hhkb2020/tasks/hhkb2020_e

縦 $ H $ 行、横 $ W $ 列からなるマス目があり、それぞれのマスは散らかっているか散らかっていないかのどちらかです。

今からあなたはこのマス目のうち $ 0 $ 個以上の散らかっていないマスに照明を置きます。

照明は置かれたマスの上下左右の $ 4 $ 方向に、マス目の端もしくは最初に散らかっているマスにぶつかる直前まで照らします (散らかっているマスは照らされません)。照明は、置かれたマス自身も照らします。

整数 $ H,\ W $ と $ H $ 個の長さ $ W $ の文字列 $ S_i $ が与えられます。 $ S_i $ の $ j $ 文字目が `.` のとき、上から $ i $ 行目、左から $ j $ 列目のマスは散らかっていません。$ S_i $ の $ j $ 文字目が `#` のとき、上から $ i $ 行目、左から $ j $ 列目のマスは散らかっています。

散らかっていないマスの個数を $ K $ 個だとすると、照明の置き方は全部で $ 2^K $ 通りあります。 この $ 2^K $ 通りそれぞれについて、$ 1 $ 個以上の照明によって照らされるマスの個数を計算したときの総和を $ 1,000,000,007 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H\ \leq\ 2000 $
- $ 1\ \leq\ W\ \leq\ 2000 $
- $ S_i $ は `.` と `#` のみからなる長さ $ W $ の文字列

### Sample Explanation 1

全部で照明の置き方は $ 16 $ 通りあります。 - このうち $ 9 $ 通り (左から $ 1 $ 番目か $ 2 $ 番目の少なくとも一方に照明が置かれている、かつ左から $ 4 $ 番目か $ 5 $ 番目の少なくとも一方に照明が置かれている) では、$ 4 $ マスが照らされます。 - このうち $ 3 $ 通り (左から $ 1 $ 番目か $ 2 $ 番目の少なくとも一方に照明が置かれている、かつ左から $ 4 $ 番目と $ 5 $ 番目のどちらにも照明が置かれていない) では、$ 2 $ マスが照らされます。 - このうち $ 3 $ 通り (左から $ 4 $ 番目か $ 5 $ 番目の少なくとも一方に照明が置かれている、かつ左から $ 1 $ 番目と $ 2 $ 番目のどちらにも照明が置かれていない) では、$ 2 $ マスが照らされます。 - このうち $ 1 $ 通り (照明が $ 1 $ つも置かれていない) では、$ 0 $ マスが照らされます。 求める総和は $ 4\ \times\ 9\ +\ 2\ \times\ 3\ +\ 2\ \times\ 3\ +\ 0\ \times\ 1\ =\ 48 $ となります。

## 样例 #1

### 输入

```
1 5
..#..```

### 输出

```
48```

## 样例 #2

### 输入

```
2 3
..#
#..```

### 输出

```
52```

# 题解

## 作者：robinyqc (赞：1)

又被绿题爆杀了。完全不会计数啊。

枚举所有射灯摆放情况显然是不行的。并且每个射灯可能会有重复贡献，这就非常不好算。这种要去掉重复贡献而且计算所有方案的价值和的问题，考虑对每个格子单独算贡献。

对于一个格子 $(i, j)$ 它在任意一种情况下有贡献，当且仅当它所在的行列中有至少一盏射灯。至少一盏也不好求，容斥一下，求一盏射灯都没有的情况数。显然就是 $(i, j)$ 摆一盏灯能照射到的格子，不允许摆灯。剩下的随便放。所以设总的空格子数为 $a$，$(i, j)$ 能照到的格子数为 $p_{i, j}$，那么其贡献为 $2^a - 2^{a - p_{i, j}}$。

至于 $(i, j)$ 能够照到的格子数，可以递推地求。总复杂度 $O(nm)$。



```rust
use proconio::input;
use ac_library::ModInt1000000007 as Mint;

fn main()
{
    input! {
        h: usize,
        w: usize,
    }
    let mut a = Vec::<Vec<u8>>::new();
    for _ in 0..h {
        input! {
            s: String
        }
        a.push(s.as_bytes().to_vec());
    }
    let mut p = vec![vec![0; w]; h];
    let mut k = 0;
    for i in 0..h {
        let mut l = (a[i][0] == b'.') as i32;
        p[i][0] += l;
        k += l as usize;
        for j in 1..w {
            if a[i][j] == b'.' {
                l += 1;
                k += 1;
            }
            else {
                l = 0;
            }
            p[i][j] += l;
        }
    }
    for i in 0..h {
        let mut l = (a[i][w - 1] == b'.') as i32;
        p[i][w - 1] += l;
        for j in (0..w - 1).rev() {
            if a[i][j] == b'.' {
                l += 1;
            }
            else {
                l = 0;
            }
            p[i][j] += l;
        }
    }
    for i in 0..w {
        let mut l = (a[0][i] == b'.') as i32;
        p[0][i] += l;
        for j in 1..h {
            if a[j][i] == b'.' {
                l += 1;
            }
            else {
                l = 0;
            }
            p[j][i] += l;
        }
    }
    for i in 0..w {
        let mut l = (a[h - 1][i] == b'.') as i32;
        p[h - 1][i] += l;
        for j in (0..h - 1).rev() {
            if a[j][i] == b'.' {
                l += 1;
            }
            else {
                l = 0;
            }
            p[j][i] += l;
        }
    }
    let mut pw2 = Vec::<Mint>::new();
    let mut v = Mint::new(1);
    for _ in 0..=k {
        pw2.push(v);
        v += v;
    }
    let mut ans = Mint::new(0);
    let pwk = pw2[k];
    for i in &p {
        for j in i {
            if *j != 0 {
                ans += pwk - pw2[k + 3 - *j as usize];
            }
        }
    }
    println!("{}", ans);
}
```

---

## 作者：_RainCappuccino_ (赞：0)

> $\mathtt{TAG}$：计数、数学

# 变量说明
下文中 $k$ 指整洁方块个数。

# First. 如何计数？

一个方案一个方案地数肯定是不现实的，不妨反过来想：每个方块在多少个方案中被照亮。

# Second. 如何求多少个方案

首先预处理出有多少位置可以将 $s_{i,j}$ 照亮。记为 $x$。这个很简单，不再赘述。

那么只需要这 $x$ 个方块中任意一个被点亮，$s_{i,j}$ 就可以被照亮。

排除掉全关的情况，只对于这 $x$ 个方块的方案数为 $2^x - 1$（因为总方案为 $2^x$）。

其余方块不影响，所以可以任意排列，即 $2^{k - x}$ 种方案。

根据乘法原理，$x$ 个方块的选取每种都要对应其余方块的 $2^{k - x}$ 种选取，所以 $s_{i,j}$ 被选中的情况即为 $(2^x - 1) \times 2^{k - x}$。

然后该方块的贡献即为被选中的方案数。

最后答案即为每个整洁方块的贡献之和。

# 时间复杂度

预处理：$\text{O}(nm)$

计数：$\text{O}(nm)$

总时间复杂度：$\text{O}(nm)$

# 提示

十年 OI 一场空，不开 long long 见祖宗。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
const int N = 2000 + 10;
const int mod = 1e9 + 7;
#define endl '\n'
int n;
int h, w, k;
char mp[N][N];
int l[N][N], r[N][N], u[N][N], d[N][N];
int fac[N *N];
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> h >> w;
	for (int i = 1; i <= h; i ++) {
		for (int j = 1; j <= w; j ++) {
			mp[0][j] = mp[h + 1][j] = '#';
			cin >> mp[i][j];
			if(mp[i][j] != '#') k ++;
		}
		mp[i][0] = mp[i][w + 1] = '#';
	}
	fac[0] = 1;
	for (int i = 1; i <= k; i ++) fac[i] = fac[i - 1] * 2 % mod; // 预处理 2 ^ i
	for (int i = 1; i <= h; i ++) {
		for (int j = 1; j <= w; j ++) {
			if(mp[i][j - 1] != '#') l[i][j] = l[i][j - 1] + 1;
			else l[i][j] = 0;
		}
		for (int j = w; j >= 1; j --) {
			if(mp[i][j + 1] != '#') r[i][j] = r[i][j + 1] + 1;
			else r[i][j] = 0;
		}
	}
	for (int j = 1; j <= w; j ++) {
		for (int i = 1; i <= h; i ++) {
			if(mp[i - 1][j] != '#') u[i][j] = u[i - 1][j] + 1;
			else u[i][j] = 0;
		}
		for (int i = h; i >= 1; i --) {
			if(mp[i + 1][j] != '#') d[i][j] = d[i + 1][j] + 1;
			else d[i][j] = 0;
		}
	}
	int ans = 0;
	for (int i = 1; i <= h; i ++) {
		for (int j = 1; j <= w; j ++) {
			if(mp[i][j] == '#') continue;
			int cnt = l[i][j] + r[i][j] + d[i][j] + u[i][j] + 1;
			ans += (fac[cnt] - 1 + mod) % mod * fac[k - cnt] % mod;
			ans %= mod;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_hhkb2020_e)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/11/05/AT-HHKB2020-E%20Lamps/)

## 前言

暑假集训的一个题，现在看来非常一眼当时竟然不会做，我太菜了。

### 前置芝士

根本没有。


## 分析

枚举所有 $2^k$ 种方案显然是困难的，所以我们考虑每个位置 $(i, j)$ 对答案的贡献。

根据题意，$(i, j)$ 这个位置在某种摆放方案下能对答案造成贡献当且仅当 $(i, j)$ 被至少一盏灯照到，这是我们就可以想到一个经典的容斥模型，就是 **至少一个 = 全集 - 一个都没有**，在这题中，我们设 $f(i, j)$ 为 $(i, j)$ 对答案的贡献，根据容斥，我们有
$$
f(i, j) = 2^k - g(i, j)
$$
其中 $g(i, j)$ 为 $(i, j)$ 不能被照到的方案数，然后我们转而求 $g(i, j)$。

我们预处理 $l_{i, j}, r_{i, j}, u_{i, j}, d_{i, j}$，分别表示左侧离 $(i, j)$ 的最近墙的纵坐标，右侧离 $(i, j)$ 的最近墙的纵坐标，上方离 $(i, j)$ 最近墙的横坐标，下方离 $(i, j)$ 最近墙的横坐标，不难发现四个东西我们都可以 $O(nm)$ 预处理，处理完后，我们得到能把 $(i, j)$ 的照亮的格子数量为
$$
p_{i, j} = (j - l_{i, j} - 1) + (r_{i, j} - j - 1) + (i - u_{i, j} - 1) + (d_{i, j} - i - 1) + 1
$$
然后我们就可以得到 $g(i, j) = 2^{k - p_{i, j}}$，那么最终我们就可以求出 $f(i, j)$ 了，最后对所有合法的 $f(i, j)$ 求和即可。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 2010, mod = 1e9 + 7;
char a[N][N];
int l[N][N], r[N][N], u[N][N], d[N][N];

inline int read()
{
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline int qpow(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

inline int get_mod(int x)
{
    return (x % mod + mod) % mod;
}

int main()
{
    int n = read(), m = read();
    int k = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)    
            cin >> a[i][j], k += a[i][j] == '.';
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            l[i][j] = a[i][j] == '#' ? j : l[i][j - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            u[i][j] = a[i][j] == '#' ? i : u[i - 1][j];
    for (int i = 1; i <= n; i++) r[i][m + 1] = m + 1;
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
            r[i][j] = a[i][j] == '#' ? j : r[i][j + 1];
    for (int i = 1; i <= m; i++) d[n + 1][i] = n + 1;
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
            d[i][j] = a[i][j] == '#' ? i : d[i + 1][j];
    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (a[i][j] == '#') continue;
            int p = (j - l[i][j] - 1) + (r[i][j] - j - 1) + (i - u[i][j] - 1) + (d[i][j] - i - 1) + 1;
            res = (res + get_mod(qpow(2, k) - qpow(2, k - p))) % mod;
        }
    printf("%d\n", res);
    return 0;
}
```







---

