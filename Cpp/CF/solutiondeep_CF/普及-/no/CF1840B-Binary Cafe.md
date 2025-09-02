# 题目信息

# Binary Cafe

## 题目描述

Once upon a time, Toma found himself in a binary cafe. It is a very popular and unusual place.

The cafe offers visitors $ k $ different delicious desserts. The desserts are numbered from $ 0 $ to $ k-1 $ . The cost of the $ i $ -th dessert is $ 2^i $ coins, because it is a binary cafe! Toma is willing to spend no more than $ n $ coins on tasting desserts. At the same time, he is not interested in buying any dessert more than once, because one is enough to evaluate the taste.

In how many different ways can he buy several desserts (possibly zero) for tasting?

## 说明/提示

Variants for 1st sample: {}, {1}

Variants for 2nd sample: {}, {1}

Variants for 3rd sample: {}, {1}, {2}

Variants for 4th sample: {}, {1}, {2}, {1, 2}

## 样例 #1

### 输入

```
5
1 2
2 1
2 2
10 2
179 100```

### 输出

```
2
2
3
4
180```

# AI分析结果

### 题目翻译
从前，托马发现自己身处一家二进制咖啡馆。这是一个非常受欢迎且不同寻常的地方。

咖啡馆为顾客提供 $k$ 种不同的美味甜点。甜点编号从 $0$ 到 $k - 1$。由于这是一家二进制咖啡馆，第 $i$ 种甜点的价格是 $2^i$ 枚硬币！托马愿意花费不超过 $n$ 枚硬币来品尝甜点。同时，他对购买同一种甜点超过一次不感兴趣，因为尝一次就足以评估其味道。

他有多少种不同的方式来购买（可能为零种）甜点进行品尝？

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是将问题转化为求有多少个 $k$ 位二进制数（可以有前导零）小于等于 $n$。通过比较 $n$ 和 $2^k - 1$ 的大小关系分情况讨论：
 - 当 $n \leq 2^k - 1$ 时，$0$ 到 $n$ 的所有数都可以用 $k$ 位二进制数表示，答案为 $n + 1$。
 - 当 $n > 2^k - 1$ 时，只能表示 $0$ 到 $2^k - 1$ 的数，答案为 $2^k$。

同时，为了防止 $2^k$ 溢出，当 $k \geq 30$ 时，直接判定答案为 $n + 1$。各题解在思路上基本一致，只是在代码实现和细节处理上略有不同。

### 所选的题解
- **MornStar（5星）**
    - 关键亮点：思路清晰，代码简洁，直接利用 `pow` 函数进行计算，并且对 $k \geq 30$ 的情况进行了特判，避免溢出。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        long long n,k;
        cin>>n>>k;
        if(k>=30||n<pow(2,k))	cout<<n+1<<endl;
        else	cout<<(int)pow(2,k)<<endl;
    }
}
```
- **Vct14（4星）**
    - 关键亮点：对思路的解释详细，不仅从组合数的角度分析了 $n \geq 2^k - 1$ 时的情况，还提到了每个甜点有买和不买两种状态，共有 $2^k$ 种买法，有助于理解问题的本质。
- **_zzzzzzy_（4星）**
    - 关键亮点：代码规范，使用 `i64` 定义长整型，并且对输入输出进行了优化，提高了效率。
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        if (k >= 30 || n <= (1 << k) - 1) {
            cout << n + 1 << "\n";
        }
        else {
            cout << (1 << k) << "\n";
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
- **思维方式**：将购买甜点的问题转化为二进制数的表示问题，利用二进制数的特性进行分析，简化了问题。
- **细节处理**：对 $k \geq 30$ 的情况进行特判，避免 $2^k$ 溢出。

### 可拓展之处
同类型题或类似算法套路：
 - 涉及二进制表示和组合计数的问题，例如求满足某些条件的二进制数的个数。
 - 利用数学公式和性质进行分类讨论的问题，通过比较不同情况的边界值来确定答案。

### 推荐洛谷题目
- P1010 幂次方：本题与本题类似，都涉及到数的二进制表示和幂次方的计算。
- P1464 Function：需要根据输入的不同情况进行分类讨论，与本题的分情况讨论思路相似。
- P1045 麦森数：涉及到高精度计算和幂次方的问题，对本题的幂次方计算有一定的拓展。

### 个人心得
部分题解提到了要注意 $2^k$ 可能会溢出的问题，通过特判 $k \geq 30$ 的情况来避免，这是在处理幂次方计算时需要注意的一个重要细节。 

---
处理用时：29.85秒