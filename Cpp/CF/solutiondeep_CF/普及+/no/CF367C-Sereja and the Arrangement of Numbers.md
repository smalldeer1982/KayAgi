# 题目信息

# Sereja and the Arrangement of Numbers

## 题目描述

Let's call an array consisting of $ n $ integer numbers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ , beautiful if it has the following property:

- consider all pairs of numbers $ x,y $ $ (x≠y) $ , such that number $ x $ occurs in the array $ a $ and number $ y $ occurs in the array $ a $ ;
- for each pair $ x,y $ must exist some position $ j $ $ (1<=j&lt;n) $ , such that at least one of the two conditions are met, either $ a_{j}=x,a_{j+1}=y $ , or $ a_{j}=y,a_{j+1}=x $ .

Sereja wants to build a beautiful array $ a $ , consisting of $ n $ integers. But not everything is so easy, Sereja's friend Dima has $ m $ coupons, each contains two integers $ q_{i},w_{i} $ . Coupon $ i $ costs $ w_{i} $ and allows you to use as many numbers $ q_{i} $ as you want when constructing the array $ a $ . Values $ q_{i} $ are distinct. Sereja has no coupons, so Dima and Sereja have made the following deal. Dima builds some beautiful array $ a $ of $ n $ elements. After that he takes $ w_{i} $ rubles from Sereja for each $ q_{i} $ , which occurs in the array $ a $ . Sereja believed his friend and agreed to the contract, and now he is wondering, what is the maximum amount of money he can pay.

Help Sereja, find the maximum amount of money he can pay to Dima.

## 说明/提示

In the first sample Sereja can pay $ 5 $ rubles, for example, if Dima constructs the following array: $ [1,2,1,2,2] $ . There are another optimal arrays for this test.

In the third sample Sereja can pay $ 100 $ rubles, if Dima constructs the following array: $ [2] $ .

## 样例 #1

### 输入

```
5 2
1 2
2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
100 3
1 2
2 1
3 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1 2
1 1
2 100
```

### 输出

```
100
```

# AI分析结果

### 题目内容
# Sereja和数字排列

## 题目描述
我们称一个由 $n$ 个整数 $a_{1}, a_{2}, \cdots, a_{n}$ 组成的数组是“美丽的”，如果它具有以下性质：
- 考虑所有数对 $x,y$ （$x \neq y$），使得数 $x$ 和数 $y$ 都出现在数组 $a$ 中；
- 对于每对数 $x,y$ ，必须存在某个位置 $j$（$1 \leq j \lt n$），使得以下两个条件至少满足其一：要么 $a_{j}=x, a_{j + 1}=y$，要么 $a_{j}=y, a_{j + 1}=x$ 。

Sereja 想构建一个由 $n$ 个整数组成的美丽数组 $a$ 。但事情并非那么简单，Sereja 的朋友 Dima 有 $m$ 张优惠券，每张优惠券包含两个整数 $q_{i}, w_{i}$ 。优惠券 $i$ 的成本为 $w_{i}$ ，并且允许在构建数组 $a$ 时使用任意多个数字 $q_{i}$ 。$q_{i}$ 的值各不相同。Sereja 没有优惠券，所以 Dima 和 Sereja 达成了如下交易。Dima 构建一个由 $n$ 个元素组成的美丽数组 $a$ 。之后，对于数组 $a$ 中出现的每个 $q_{i}$ ，他从 Sereja 那里拿走 $w_{i}$ 卢布。Sereja 相信了他的朋友并同意了这份合同，现在他想知道，他最多可以支付多少钱。

帮助 Sereja 找到他最多可以支付给 Dima 的金额。

## 说明/提示
在第一个样例中，Sereja 可以支付 5 卢布，例如，如果 Dima 构建以下数组：$[1,2,1,2,2]$ 。对于这个测试用例还有其他最优数组。

在第三个样例中，Sereja 可以支付 100 卢布，如果 Dima 构建以下数组：$[2]$ 。

## 样例 #1
### 输入
```
5 2
1 2
2 3
```
### 输出
```
5
```

## 样例 #2
### 输入
```
100 3
1 2
2 1
3 1
```
### 输出
```
4
```

## 样例 #3
### 输入
```
1 2
1 1
2 100
```
### 输出
```
100
```

### 算法分类
数学

### 综合分析与结论
该题解通过将原问题进行两次转化，将其与图论中欧拉图的概念联系起来，通过数学方法计算出不同情况下满足条件的数组最小长度，再结合贪心思想，对价值从大到小排序，在满足数组长度限制下尽可能选取价值大的数，从而得出最大支付金额。思路清晰，逻辑连贯，将复杂的构造问题转化为数学计算问题，有效解决了难点。

### 所选的题解
- **作者**：_cyle_King（5星）
  - **关键亮点**：巧妙地将问题转化为图论中欧拉图相关问题，利用数学方法计算最小数组长度，结合贪心思想解决问题，代码简洁高效。
  - **个人心得**：无

### 重点代码及核心实现思想
```cpp
#include<bits/stdc++.h>

#define rep(i,x,y) for(int i=(x), _=(y); i<=_; i++)
#define per(i,x,y) for(int i=(x), _=(y); i>=_; i--)

using namespace std;
template <class T1, class T2> inline bool cmax(T1 &a, T2 b) {return a < b? a = b, 1 : 0;}
template <class T1, class T2> inline bool cmin(T1 &a, T2 b) {return b < a? a = b, 1 : 0;}
typedef pair<int, int> pii;
typedef pair<int, long long> pil;
typedef pair<long long, int> pli;
typedef pair<long long, long long> pll;
typedef long long LL;

const int N = 1e6 + 10;

int 
main() {
    int n, m;
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    vector<int> a;
    a.reserve(m + 1);
    rep(i, 1, m) {
        int x, y; cin >> x >> y; a.emplace_back(y);
    }
    sort(a.begin(), a.end(), greater<int> ());
    LL ans = 0;
    rep(i, 0, m - 1) {
        LL now;
        if(i & 1) now = 1ll * (i + 1) * (i + 1) / 2;
        else now = 1 + 1ll * i * (i + 1) / 2;
        if(now > n) break;
        else ans += a[i];
    }
    cout << ans << endl;
    return 0;
}
```
核心实现思想：先读入数据并将价值数组 `a` 按从大到小排序。然后通过循环枚举选取数的数量 `i`，根据 `i` 的奇偶性计算出对应所需的最小数组长度 `now`，若 `now` 不超过给定的数组长度 `n`，则将当前价值 `a[i]` 累加到答案 `ans` 中，否则跳出循环，最后输出答案。

### 最优关键思路或技巧
1. **问题转化**：将原数组构造问题转化为图论问题，通过分析图的性质（是否为欧拉图）来计算满足条件的最小数组长度，这是解决问题的关键。
2. **贪心策略**：在计算出最小数组长度后，利用贪心思想，优先选取价值大的数，以达到最大支付金额的目的。

### 可拓展之处
此类问题属于通过巧妙的问题转化，利用数学知识解决构造类问题的类型。类似套路可应用于一些需要构造特定序列或结构，并在一定限制条件下求最值的题目。例如，某些需要构造满足特定相邻关系的序列，并在长度或元素数量限制下求最优解的问题。

### 洛谷相似题目推荐
1. [P1140 相似基因](https://www.luogu.com.cn/problem/P1140)：通过分析基因序列间的关系，利用数学方法计算相似度，与本题通过分析数组元素关系转化为数学计算有相似之处。
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：将实际问题转化为数学模型，通过二分查找解决，与本题转化问题求解思路类似。
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：运用贪心策略解决排队接水时间最优问题，和本题运用贪心思想求最值思路一致。 

---
处理用时：54.44秒