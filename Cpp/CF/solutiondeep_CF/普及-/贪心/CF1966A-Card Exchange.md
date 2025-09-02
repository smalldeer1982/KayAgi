# 题目信息

# Card Exchange

## 题目描述

You have a hand of $ n $ cards, where each card has a number written on it, and a fixed integer $ k $ . You can perform the following operation any number of times:

- Choose any $ k $ cards from your hand that all have the same number.
- Exchange these cards for $ k-1 $ cards, each of which can have any number you choose (including the number written on the cards you just exchanged).

Here is one possible sequence of operations for the first example case, which has $ k=3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1966A/25cf30b9964a74e1022f2c7cdd313093587901b5.png)What is the minimum number of cards you can have in your hand at the end of this process?

## 说明/提示

The first example case corresponds to the picture above. The sequence of operations displayed there is optimal, so the answer is $ 2 $ .

In the second example case, no operations can be performed, so the answer is $ 1 $ .

In the fourth example case, you can repeatedly select $ 4 $ cards numbered with $ 1 $ and replace them with $ 3 $ cards numbered with $ 1 $ , until there are $ 3 $ cards left.

## 样例 #1

### 输入

```
7
5 3
4 1 1 4 4
1 10
7
7 2
4 2 1 100 5 2 3
10 4
1 1 1 1 1 1 1 1 1 1
5 2
3 8 1 48 7
6 2
10 20 30 10 20 40
6 3
10 20 30 10 20 40```

### 输出

```
2
1
1
3
5
1
6```

# AI分析结果



# Card Exchange

## 题目描述

你手中有 $n$ 张卡牌，每张卡牌上有一个数字，给定一个固定整数 $k$。你可以执行以下操作任意次：

- 从手中选出任意 $k$ 张数字相同的卡牌。
- 将这些卡牌替换为 $k-1$ 张任意数字的卡牌（包括原数字）。

求最终手中卡牌的最小可能数量。

## 样例

输入：
```
7
5 3
4 1 1 4 4
1 10
7
7 2
4 2 1 100 5 2 3
10 4
1 1 1 1 1 1 1 1 1 1
5 2
3 8 1 48 7
6 2
10 20 30 10 20 40
6 3
10 20 30 10 20 40
```

输出：
```
2
1
1
3
5
1
6
```

---

## 题解分析与结论

### 核心思路
1. **关键观察**：若存在某个数字的出现次数 $\geq k$，则可以通过不断将其余卡牌转换为该数字，并持续进行操作，最终卡牌数可降至 $k-1$。
2. **贪心策略**：只需检查所有数字的出现次数，若存在至少一个数字出现次数 $\geq k$，则答案必为 $k-1$；否则无法操作，答案为原卡牌数 $n$。

### 解决难点
- **操作链的构造**：通过将其他卡牌转换为同一高频率数字，形成连续操作，确保每次操作减少卡牌数。
- **数学归纳**：当存在足够多的同一数字时，每次操作减少 $1$ 张卡牌，最终稳定在 $k-1$ 张。

### 最优解代码
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        unordered_map<int, int> cnt;
        int max_cnt = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            max_cnt = max(max_cnt, ++cnt[x]);
        }
        if (max_cnt >= k) {
            cout << k - 1 << endl;
        } else {
            cout << n << endl;
        }
    }
    return 0;
}
```

### 关键技巧
- **哈希表统计频率**：快速找到最高频数字。
- **直接比较阈值**：仅需判断最大频率是否 $\geq k$，避免复杂计算。

---

## 相似题目推荐
1. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102)  
   - 考察哈希表统计频率及差值匹配。
2. [P1618 三连击（升级版）](https://www.luogu.com.cn/problem/P1618)  
   - 通过枚举和数学分析优化组合。
3. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)  
   - 利用异或性质找唯一出现奇数次数的元素，类似频率处理。

---
处理用时：537.65秒