# 题目信息

# Little Robber Girl's Zoo

## 题目描述

Little Robber Girl likes to scare animals in her zoo for fun. She decided to arrange the animals in a row in the order of non-decreasing height. However, the animals were so scared that they couldn't stay in the right places.

The robber girl was angry at first, but then she decided to arrange the animals herself. She repeatedly names numbers $ l $ and $ r $ such that $ r-l+1 $ is even. After that animals that occupy positions between $ l $ and $ r $ inclusively are rearranged as follows: the animal at position $ l $ swaps places with the animal at position $ l+1 $ , the animal $ l+2 $ swaps with the animal $ l+3 $ , ..., finally, the animal at position $ r-1 $ swaps with the animal $ r $ .

Help the robber girl to arrange the animals in the order of non-decreasing height. You should name at most $ 20000 $ segments, since otherwise the robber girl will become bored and will start scaring the animals again.

## 说明/提示

Note that you don't have to minimize the number of operations. Any solution that performs at most $ 20000 $ operations is allowed.

## 样例 #1

### 输入

```
4
2 1 4 3
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
7
36 28 57 39 66 69 68
```

### 输出

```
1 4
6 7
```

## 样例 #3

### 输入

```
5
1 2 1 2 1
```

### 输出

```
2 5
3 4
1 4
1 4
```

# AI分析结果

### 题目翻译
# 小女劫匪的动物园

## 题目描述
小女劫匪喜欢在她的动物园里吓唬动物取乐。她决定将动物按身高非递减的顺序排成一排。然而，动物们被吓得无法待在正确的位置上。

起初，劫匪女孩很生气，但随后她决定亲自来安排动物的位置。她会反复说出数字 $l$ 和 $r$，使得 $r - l + 1$ 为偶数。之后，位于 $l$ 到 $r$（包含 $l$ 和 $r$）位置的动物会进行如下重新排列：位置 $l$ 的动物与位置 $l + 1$ 的动物交换位置，位置 $l + 2$ 的动物与位置 $l + 3$ 的动物交换，以此类推，最后，位置 $r - 1$ 的动物与位置 $r$ 的动物交换。

帮助劫匪女孩将动物按身高非递减的顺序排列。你最多只能说出 $20000$ 个区间，否则劫匪女孩会感到厌烦，然后又开始吓唬动物了。

## 说明/提示
注意，你不必使操作次数最少。任何执行次数不超过 $20000$ 次操作的解决方案都是允许的。

## 样例 #1
### 输入
```
4
2 1 4 3
```
### 输出
```
1 4
```

## 样例 #2
### 输入
```
7
36 28 57 39 66 69 68
```
### 输出
```
1 4
6 7
```

## 样例 #3
### 输入
```
5
1 2 1 2 1
```
### 输出
```
2 5
3 4
1 4
1 4
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是利用冒泡排序对数组进行排序，并在交换元素时输出交换的区间。由于 $n$ 最大为 $100$，冒泡排序的交换次数在 $O(n^2)$ 左右，最多 $4950$ 次，远小于题目限制的 $20000$ 次，所以能满足要求。各题解的主要区别在于代码实现细节和输出方式。

### 通用建议与扩展思路
对于此类排序并输出操作过程的题目，冒泡排序是一种简单且有效的方法。在实现时，要注意数组下标和输出格式。扩展思路方面，可以考虑其他排序算法，如插入排序、选择排序等，看是否能在满足条件的情况下减少操作次数。还可以尝试优化冒泡排序，如设置标志位提前结束排序过程。

### 重点代码
以下是一个典型的冒泡排序并输出交换区间的代码：
```cpp
#include<iostream>
using namespace std;
const int N = 110;
int a[N];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++) {
        for (int j = n; j > i; j--) {
            if (a[j] < a[j - 1]) {
                cout << j - 1 << " " << j << endl;
                swap(a[j - 1], a[j]);
            }
        }
    }
    return 0;
}
```
核心实现思想：使用两层循环，外层循环控制排序的轮数，内层循环从后往前遍历，比较相邻元素，如果顺序错误则交换，并输出交换的区间。

### 推荐题目
1. [P1177 【模板】排序](https://www.luogu.com.cn/problem/P1177)
2. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
3. [P1923 【深基9.例4】求第 k 小的数](https://www.luogu.com.cn/problem/P1923)

### 个人心得
题解中未包含个人心得。

---
处理用时：22.42秒