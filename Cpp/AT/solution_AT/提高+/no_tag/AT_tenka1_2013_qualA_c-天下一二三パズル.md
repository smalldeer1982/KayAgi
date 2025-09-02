# 天下一二三パズル

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2013-quala/tasks/tenka1_2013_qualA_c

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_tenka1_2013_qualA_c/7e406069f12e803b96ea491d6c13225894258dcf.png)図 $ 2 $

 

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_tenka1_2013_qualA_c/40b9d5d20950b80c3e734ad236cabd4619d6ee60.png)図 $ 3 $

 

 $ 2 $ を配置する場合は $ 2 $ マス以上空いていなければならない。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_tenka1_2013_qualA_c/98e7f7f0b2f0c64325eea43fd27eeee89b778034.png)図 $ 4 $

 

 入力は以下の形式で標準入力から与えられる。

> $ M $ $ N $

- 横方向のマスの数 $ M $ と 縦方向のマスの数 $ N $ ( $ 1\ \leq\ M,\ N\ \leq\ 10^6 $ ) が空白区切りで $ 1 $ 行で与えられる。

- $ M,\ N\ \leq\ 4 $ の入力に正解すると、120 点満点に対して部分点として 40 点が与えられる。
- $ M,\ N\ \leq\ 100 $ の入力に正解すると、120 点満点に対して部分点として、さらに 20 点が与えられる。

 数字の配置の仕方が何通りあるかを標準出力に $ 1 $ 行で出力せよ。  
 なお、行の終端には改行が必要である。

 ```

1 1
```

 ```

3
```

 ```

3 1
```

 ```

8
```

# 题解

## 作者：cosf (赞：0)

看样子这题要么是恶心 dp 要么是打表。

首先先写一个 $O(3^{NM}NM)$ 的打表程序，拿到了 $N, M$ 较小的解：

```
3  6  8  8  8  8  9  10 9  8  9  10 
6  18 20 16 16 18 20 18 16 
8  20 28 16 18 20 
8  16 16 18 20 
8  16 18 20   
8  18 20   
9  20 
10
```

显然，表关于 $N, M$ 对称。下面令 $N \le M$。

令答案为 $A$，则可以观察出以下性质（用英文句号以免与 $0$ 混淆）：

- $N = M = 1 \implies A = 3$.
- $N = 1, M = 2 \implies A = 6$.
- $N = 1, 3 \le M \le 5 \implies A = 8$.
- 令 $x = \{10, 9, 8, 9\}$，则 $N = 1, 6 \le M \implies A = x_{M \bmod 4}$.
- $N = 2, M = 4 \implies A = 16$.
- $N = M = 3 \implies A = 28$.
- 其他情况令 $y = \{18, 20, 18, 16\}$，则 $A = y_{(n + m) \bmod 4}$.

然后可以发现观察出来的结果是对的。

远古题，也懒得废心思证了。

```cpp
#include <iostream>
using namespace std;

int solve(int n, int m)
{
    if (n == 1)
    {
        if (m == 1)
        {
            return 3;
        }
        if (m == 2)
        {
            return 6;
        }
        if (m < 7)
        {
            return 8;
        }
        int x[4] = {10, 9, 8, 9};
        return x[m % 4];
    }
    if (n == 3 && m == 3)
    {
        return 28;
    }
    if (n == 2 && m == 4)
    {
        return 16;
    }
    int y[4] = {18, 20, 18, 16};
    return y[(n + m) % 4];
}

int main()
{
    int n, m;
    cin >> n >> m;
    if (n > m)
    {
        swap(n, m);
    }
    cout << solve(n, m) << endl;
    return 0;
}
```

---

