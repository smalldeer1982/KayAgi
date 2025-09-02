# [ARC148D] mod M Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc148/tasks/arc148_d

黒板に $ 2N $ 個の整数 $ A_1,\ A_2,\ ...,\ A_{2N} $ が書かれています。また、$ 2 $ 以上の整数 $ M $ があります。  
 Alice と Bob はゲームをします。 ゲームは Alice を先攻として、黒板の上の数が全てなくなるまで次の操作を交互に行います。

- 数を $ 1 $ 個選び、その数を黒板から消す。

ゲームを終了した時点で、(Alice が消した数の和) $ \text{mod\ }M $ と (Bob が消した数の和) $ \text{mod\ }M $ が一致していれば Bob の勝ち、そうでない場合は Alice の勝ちです。  
 両者が最善を尽くしたとき、どちらが勝ちますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ M\ \leq\ 10^9 $
- $ 0\ \leq\ A_i\ \leq\ M\ -\ 1 $
- 入力される値はすべて整数

### Sample Explanation 1

ゲームの進行例として次のようなものが考えられます。 - Alice が $ 1 $ を消す。 - Bob が $ 4 $ を消す。 - Alice が $ 5 $ を消す。 - Bob が $ 8 $ を消す。 このように進んだ場合、(Alice が消した数の和) $ \text{mod\ }M $ は $ (1\ +\ 5)\ \bmod\ 9\ =\ 6 $, (Bob が消した数の和) $ \text{mod\ }M $ は $ (4\ +\ 8)\ \bmod\ 9\ =\ 3 $ で、$ 6\ \neq\ 3 $ なので Alice の勝ちです。

## 样例 #1

### 输入

```
2 9
1 4 8 5```

### 输出

```
Alice```

## 样例 #2

### 输入

```
3 998244353
1 2 3 1 2 3```

### 输出

```
Bob```

# 题解

## 作者：APJifengc (赞：13)

部分参考了 [xiaolilsq dalao](https://www.cnblogs.com/lsq147/p/16687279.html) 的题解。

感觉 AtCoder 的博弈论都好nb啊，我真的是一个都想不出来。

------------------

首先我们考虑当仅剩下两个数字时，Bob 如何会赢。那么假设现在 Alice 取的数的和为 $x$，Bob 取的数的和为 $y$，剩下的两个数字为 $a$ 和 $b$，那么 Bob 会赢当且仅当 $x + a \equiv y + b \pmod m$ 且 $x + b \equiv y + a \pmod m$，那么可以得到一个 Bob 获胜的必要条件 $2a \equiv 2b \pmod m$。

那么这样的 $a,b$ 仅有可能是 $a=b$ 或者 $a \equiv b + \frac{m}{2} \pmod m$（当 $m$ 为偶数时）。

我们不妨考虑将这样的数看做一对。那么不难想出，如果所有的数都可以匹配成若干 $a=b$ 与偶数对 $a \equiv b + \frac{m}{2} \pmod m$，那么 Bob 就一定有必胜策略。Bob 的必胜策略就是每次 Alice 取一个数，Bob 取与之配对的数，这样最后两个和一定相等。

那么是否这个条件为 Bob 获胜的必要条件呢？考虑如果不满足以上的匹配，我们构造一种 Alice 的必胜策略，即可证明该条件为充要条件。

我们先能匹配的匹配，最后应该会剩下一些互不相等的数，且满足 $a \equiv b + \frac{m}{2} \pmod m$ 的数对只有 $0$ 或 $1$ 对。那么我们先让 Alice 随便选满足 $a \equiv b + \frac{m}{2} \pmod m$ 的其中一个数，如果没有那就随便选一个未匹配的数。

假如 Bob 选择了一个在匹配中的数，那么 Alice 可以直接选择与其向对应的数，如果 Bob 选择了一个不在匹配中的数，那么 Alice 也选不在里面的数。这样当不能匹配的数仅剩下两个时，这两个数一定不满足一开始所述的 $2a \equiv 2b \pmod m$ 条件，那么此时 Bob 一定不会获胜，也就是 Alice 一定能够获胜。

于是就可以证明上面的条件是充要的，于是只需要判断能否构成这样的匹配即可。

[code](https://atcoder.jp/contests/arc148/submissions/36538079)

---

## 作者：HNOIRPplusplus (赞：2)

## 题意

+ 有 $2N$ 个数 $A_1, A_2, \dots, A_n$，Alice 和 Bob 轮流取数。Alice 先取，一次一个。
+ 取完以后，将每人取到的数对 $M$ 取模。余数相等则 Bob 赢，否则 Alice 赢。
+ 问最终谁有必胜策略。

## 思路

又是 Alice 和 Bob 的博弈游戏了。~~他们就这么喜欢博弈吗？~~

显然最后一个数是 Bob 取的，而倒数第二个数是 Alice 取的。假设当前 Alice 一共取到的数取余得到 $a$，Bob 得到 $b$，倒数第一、第二个数分别为 $x$ 和 $y$。如果 Bob 有必胜策略，那么 $x+a\equiv y+b\pmod M$ 且 $x+a\equiv y+b\pmod M$。否则 Alice 就会有一种必胜的选法。  
将这两个式子相减、移项，得到 $2x\equiv 2y \pmod M$。也就是说 Alice 取 $x$ ，Bob 就一定会取 $y$，才能满足最终结果一样。

因此，如果存在 $v$ 满足共有奇数个数的 $A_i$ 满足 $2k \equiv v \pmod M$，则 Alice 必胜。Alice 每次从这奇数个 $A_i$ 中选一个，Bob 也会跟一个。但是最终 Alice 拿走最后一个以后 Bob 没有能跟的了，导致 Alice 可以赢。  
此时 Alice 必胜。否则 Bob 必胜。

当然要注意，$x \equiv y + \dfrac M 2 \pmod M$ 的时候代表 Bob 最终凑出来不一定能是相等的。$x$ 和 $y$ 本身并不相等，所以最终还需要继续检验。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 400005;

int a[N];

int main() {
  map<int, int> mp;
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= 2 * n; i++) {
    cin >> a[i];
    mp[2 * a[i] % m]++;
  }
  for(auto t : mp) {
    if(t.second % 2) {
      cout << "Alice";
      return 0;
    }
  }
  for(int i = 1; i <= 2 * n; i++) {
    if((mp[2 * a[i] % m]--) % 2) {
      s = (s - a[i] + m) % m;
    } else {
      s = (s + a[i]) % m;
    }
  }
  if(s % m == 0) {
    cout << "Bob";
  } else {
    cout << "Alice";
  }
}
```

## 总结

将博弈问题规模最小化，然后再观察整个问题如何归到该最小情况上。

[AC](https://www.luogu.com.cn/record/145334776)

谢谢 戚朗瑞 的冬令营支持。

---

