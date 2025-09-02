# Level K Palindrome

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jsc2021/tasks/jsc2021_e

高橋くんは、すぬけくんに日頃の感謝を込めてレベル $ K $ の回文を送ることにしました。レベル $ L $ の回文 ( $ L $ は $ 0 $ 以上の整数 ) は以下のように定義されます。

- 文字列 $ s $ の左右を反転させたものを $ \mathrm{rev}(s) $ と表す。
- 文字列 $ s $ は $ s\ =\ \mathrm{rev}(s) $ であるとき、回文という。
- 空文字列と回文でない文字列はレベル $ 0 $ の回文である。
- 任意の**空でない**レベル $ L\ -\ 1 $ の回文 $ t $ に対して、$ t,\ \mathrm{rev}(t) $ をこの順に繋げた文字列はレベル $ L $ の回文である。
- 任意のレベル $ L\ -\ 1 $ の回文 $ t $ と任意の文字 $ c $ に対して、$ t,\ c,\ \mathrm{rev}(t) $ をこの順に繋げた文字列はレベル $ L $ の回文である。

いま、高橋くんは文字列 $ S $ を持っています。  
 $ S $ から $ 1 $ 文字選んで別の英小文字に書き換えるということを $ 0 $ 回以上繰り返すことで、$ S $ をちょうどレベル $ K $ の回文にすることができるか判定してください。また、できる場合は、$ S $ がちょうどレベル $ K $ の回文になるまでに必要な最小の書き換え回数を求めてください。

## 说明/提示

### 制約

- $ K $ は整数
- $ 0\ <\ = K\ <\ = 5\ \times\ 10^5 $
- $ S $ は英小文字からなる
- $ 1\ <\ =\ |S|\ <\ = 5\ \times\ 10^5 $

### Sample Explanation 1

`aabaaaabaa` のレベルは以下のように計算できます。 - 空文字列はレベル $ 0 $ の回文である。 - `a` は (空文字列), `a`, (空文字列) を順に繋げた文字列だから、レベル $ 1 $ の回文である。 - `aa` は `a`, `a` を順に繋げた文字列だから、レベル $ 2 $ の回文である。 - `aabaa` は `aa`, `b`, `aa` を順に繋げた文字列だから、レベル $ 3 $ の回文である。 - `aabaaaabaa` は `aabaa`, `aabaa` を順に繋げた文字列だから、レベル $ 4 $ の回文である。 よって、`aabaaaabaa` は初めからレベル $ 4 $ の回文であるので、書き換える必要はありません。

### Sample Explanation 2

例えば、`aabaaaabaa` を `acbcaacbca` に書き換えると、ちょうどレベル $ 2 $ の回文を作ることができます。 `aabaaaabaa` はレベル $ 2 $ の回文ではないことに注意してください。

## 样例 #1

### 输入

```
4
aabaaaabaa```

### 输出

```
0```

## 样例 #2

### 输入

```
2
aabaaaabaa```

### 输出

```
4```

## 样例 #3

### 输入

```
3
aabaaaabaa```

### 输出

```
impossible```

## 样例 #4

### 输入

```
5
aabaaaabaa```

### 输出

```
impossible```

## 样例 #5

### 输入

```
2
acaabcbababaaac```

### 输出

```
6```

# 题解

## 作者：Y204335 (赞：1)

# Level K Palindrome

## 题目大意

给出 $k$ 级回文串的定义，给定 $k$ 以及字符串 $S$，问将 $S$ 变为 $k$ 级回文串最少要改变的字符数。

## 题目分析

首先，由于 $0$ 级回文串长度一定不为 $1$（为 $1$ 则一定回文），$x(x>0)$ 级回文串一定不为空，所以可以直接判掉无解的情况。

然后考虑怎样处理，显然如果几个位置需要填同种字母，选择这几个位置中出现次数最多的字母一定最优，由于 $k$ 级回文串的性质，$S$ 一定可以不断被分为左右两个对称的 $k-1$ 级回文串，所以可以每次将字符串折叠（长度除 $2$），记录每个位置折叠前每种字母出现的次数，当当前字符串长度为奇数时，处理中间位置（$\left\lfloor\frac{n}{2}\right\rfloor+1$）的字符。

$S$ 最后会被变为 $0$ 级回文串，由于 $0$ 级回文串本身不能是回文串，所以当该 $0$ 级回文串的最优选择是回文串时，需要选择次优情况，具体实现不难。

时间复杂度 $O(\left|S\right|)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, k, ans, cnt[N][27], res = 0x3fffffff;
string s;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> k >> s;
    n = s.size();
    s = '#' + s;
    if (k > 20 || (n >> k) == 1 || (k && (n >> (k - 1)) == 0)) {
        cout << "impossible";
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        cnt[i][s[i] - 'a']++;
    }
    for (int i = k; i >= 1; i--) {
        for (int j = 1; j <= n / 2; j++) {
            for (int p = 0; p < 26; p++) {
                cnt[j][p] += cnt[n - j + 1][p];
            }
        }
        if (n & 1) {
            ans += (1 << (k - i)) - *max_element(cnt[n / 2 + 1], cnt[n / 2 + 1] + 26);
        }
        n /= 2;
    }
    if (!n) {
        cout << ans;
        return 0;
    }
    for (int i = 1; i <= n / 2; i++) {
        int id1[2] = { 26, 26 }, id2[2] = { 26, 26 };
        for (int j = 0; j < 26; j++) {
            if (cnt[i][j] > cnt[i][id1[1]]) {
                id1[1] = j;
                if (cnt[i][id1[0]] < cnt[i][id1[1]]) {
                    swap(id1[0], id1[1]);
                }
            }
            if (cnt[n - i + 1][j] > cnt[n - i + 1][id2[1]]) {
                id2[1] = j;
                if (cnt[n - i + 1][id2[0]] < cnt[n - i + 1][id2[1]]) {
                    swap(id2[0], id2[1]);
                }
            }
        }
        if (id1[0] != id2[0])
            res = 0;
        ans += (1 << (k + 1)) - cnt[i][id1[0]] - cnt[n - i + 1][id2[0]];
        res = min({ res, cnt[i][id1[0]] - cnt[i][id1[1]], cnt[n - i + 1][id2[0]] - cnt[n - i + 1][id2[1]] });
    }
    ans += res;
    if (n & 1) {
        ans += (1 << k) - *max_element(cnt[n / 2 + 1], cnt[n / 2 + 1] + 26);
    }
    cout << ans;
    return 0;
}
```

---

