# 题目信息

# Kind Anton

## 题目描述

Once again, Boris needs the help of Anton in creating a task. This time Anton needs to solve the following problem:

There are two arrays of integers $ a $ and $ b $ of length $ n $ . It turned out that array $ a $ contains only elements from the set $ \{-1, 0, 1\} $ .

Anton can perform the following sequence of operations any number of times:

1. Choose any pair of indexes $ (i, j) $ such that $ 1 \le i < j \le n $ . It is possible to choose the same pair $ (i, j) $ more than once.
2. Add $ a_i $ to $ a_j $ . In other words, $ j $ -th element of the array becomes equal to $ a_i + a_j $ .

For example, if you are given array $ [1, -1, 0] $ , you can transform it only to $ [1, -1, -1] $ , $ [1, 0, 0] $ and $ [1, -1, 1] $ by one operation.

Anton wants to predict if it is possible to apply some number (zero or more) of these operations to the array $ a $ so that it becomes equal to array $ b $ . Can you help him?

## 说明/提示

In the first test-case we can choose $ (i, j)=(2, 3) $ twice and after that choose $ (i, j)=(1, 2) $ twice too. These operations will transform $ [1, -1, 0] \to [1, -1, -2] \to [1, 1, -2] $

In the second test case we can't make equal numbers on the second position.

In the third test case we can choose $ (i, j)=(1, 2) $ $ 41 $ times. The same about the fourth test case.

In the last lest case, it is impossible to make array $ a $ equal to the array $ b $ .

## 样例 #1

### 输入

```
5
3
1 -1 0
1 1 -2
3
0 1 1
0 2 2
2
1 0
1 41
2
-1 0
-1 -41
5
0 1 -1 1 -1
1 1 -1 1 -1```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容
# Kind Anton

## 题目描述
鲍里斯又一次需要安东帮忙出一道题。这次安东需要解决以下问题：

有两个长度为 $n$ 的整数数组 $a$ 和 $b$。已知数组 $a$ 仅包含集合 $\{-1, 0, 1\}$ 中的元素。

安东可以执行以下一系列操作任意次数：
1. 选择任意一对索引 $(i, j)$，使得 $1 \leq i < j \leq n$。同一对 $(i, j)$ 可以选择多次。
2. 将 $a_i$ 加到 $a_j$ 上。换句话说，数组的第 $j$ 个元素变为 $a_i + a_j$。

例如，给定数组 $[1, -1, 0]$，通过一次操作，它只能变为 $[1, -1, -1]$、$[1, 0, 0]$ 和 $[1, -1, 1]$。

安东想知道是否可以对数组 $a$ 应用若干次（零次或多次）这些操作，使其变为数组 $b$。你能帮助他吗？

## 说明/提示
在第一个测试用例中，我们可以先选择 $(i, j) = (2, 3)$ 两次，然后再选择 $(i, j) = (1, 2)$ 两次。这些操作将把 $[1, -1, 0]$ 变为 $[1, -1, -2] \to [1, 1, -2]$。

在第二个测试用例中，我们无法使第二个位置的数字相等。

在第三个测试用例中，我们可以选择 $(i, j) = (1, 2)$ $41$ 次。第四个测试用例同理。

在最后一个测试用例中，不可能使数组 $a$ 等于数组 $b$。

## 样例 #1
### 输入
```
5
3
1 -1 0
1 1 -2
3
0 1 1
0 2 2
2
1 0
1 41
2
-1 0
-1 -41
5
0 1 -1 1 -1
1 1 -1 1 -1
```
### 输出
```
YES
NO
YES
YES
NO
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，从前往后或从后往前遍历数组，根据当前位置 $a_i$ 和 $b_i$ 的大小关系，判断前面是否存在合适的 $1$ 或 $-1$ 来使 $a_i$ 变为 $b_i$ 。算法要点在于记录数组 $a$ 中 $1$ 和 $-1$ 的出现情况，难点在于理解操作的顺序不影响最终结果以及在处理过程中正确维护 $1$ 和 $-1$ 的状态。不同题解在实现方式上略有差异，如有的使用标记变量，有的使用数组统计数量等。

### 所选的题解
- **作者：AutumnKite (4星)**
    - **关键亮点**：思路清晰简洁，从后往前依次将 $a_i$ 变成 $b_i$ ，通过两个指针分别找到第一个 $1$ 和 $-1$ ，然后根据 $a_i$ 和 $b_i$ 的大小关系进行判断，逻辑明确。
    - **重点代码及核心思想**：
```cpp
const int N = 200005;
int n, a[N], b[N];
void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        read(b[i]);
    }
    int p1 = 1, p2 = 1;
    // 找到第一个1
    while (p1 <= n && a[p1] < 1) {
        if (a[p1] < b[p1]) {
            printStr("NO");
            return;
        }
        ++p1;
    }
    if (p1 <= n && a[p1] < b[p1]) {
        printStr("NO");
        return;
    }
    // 找到第一个 -1
    while (p2 <= n && a[p2] > -1) {
        if (a[p2] > b[p2]) {
            printStr("NO");
            return;
        }
        ++p2;
    }
    if (p2 <= n && a[p2] > b[p2]) {
        printStr("NO");
        return;
    }
    printStr("YES");
}
```
核心思想是通过两个 `while` 循环分别找到数组 $a$ 中从前往后的第一个 $1$ 和 $-1$ ，在寻找过程中就对当前位置 $a_i$ 和 $b_i$ 进行比较判断，如果不符合条件则直接输出 `NO` ，遍历完都符合则输出 `YES` 。
- **作者：banned_xiejiayun (4星)**
    - **关键亮点**：对题意的简化和思路推导详细，分三种情况对 $a$ 数组中的元素与 $b$ 数组对应元素的关系进行讨论，并详细说明了标记 $1$ 和 $-1$ 出现情况的原因，代码注释丰富，可读性强。
    - **重点代码及核心思想**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[100001], b[100001];
bool x, y;
int main() {
    scanf("%d", &t);
    while (t--) {
        x = 0, y = 0;
        bool flag = true;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++)scanf("%d", &b[i]);
        for (int i = 1; i <= n; i++) {
            // 相等情况
            if (a[i] == b[i]) {
                if (a[i] == -1) {
                    if (!x) x = 1;
                } else if (a[i] == 1) {
                    if (!y) y = 1;
                }
                continue;
            }
            // a[i] 大于 b[i] 的情况
            if (a[i] > b[i]) {
                if (x == 0) {
                    printf("NO\n");
                    flag = false;
                    break;
                }
                if (b[i] == -1) {
                    if (!x) x = 1;
                } else if (b[i] == 1) {
                    if (!y) y = 1;
                }
                if (a[i] == -1) {
                    if (!x) x = 1;
                } else if (a[i] == 1) {
                    if (!y) y = 1;
                }
            } else {
                // a[i] 小于 b[i] 的情况
                if (y == 0) {
                    printf("NO\n");
                    flag = false;
                    break;
                }
                if (b[i] == -1) {
                    if (!x) x = 1;
                } else if (b[i] == 1) {
                    if (!y) y = 1;
                }
                if (a[i] == -1) {
                    if (!x) x = 1;
                } else if (a[i] == 1) {
                    if (!y) y = 1;
                }
            }
        }
        if (flag) printf("YES\n");
    }
    return 0;
}
```
核心思想是遍历数组，针对 $a[i]$ 和 $b[i]$ 相等、$a[i] > b[i]$ 、$a[i] < b[i]$ 三种情况分别处理，相等时更新 $1$ 和 $-1$ 的标记，$a[i] > b[i]$ 时检查是否有 $-1$ ，$a[i] < b[i]$ 时检查是否有 $1$ ，若不满足条件则标记为 `NO` ，遍历结束根据标记输出结果。
- **作者：Warriors_Cat (4星)**
    - **关键亮点**：代码简洁明了，从后往前枚举，通过一个数组 `cnt` 记录 $1$ 和 $-1$ 的数量，根据 $a_i$ 与 $b_i$ 的大小关系进行判断，操作直观易懂。
    - **重点代码及核心思想**：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int t, n, a[100010], b[100010], cnt[2];
//cnt[0] 表示 -1 的个数，cnt[1] 表示 1 的个数。
int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i){
            scanf("%d", a + i);
            if(i < n){
                if(a[i] == 1) cnt[1]++;
                if(a[i] == -1) cnt[0]++;
            }
        }
        for(int i = 1; i <= n; ++i) scanf("%d", b + i);
        bool flag = 1;
        for(int i = n; i >= 1; --i){
            if(a[i] == b[i]){
                if(a[i - 1] == 1) cnt[1]--;
                if(a[i - 1] == -1) cnt[0]--;
            }
            else if(a[i] > b[i]){
                if(!cnt[0]){
                    flag = 0;
                    break;
                }
                if(a[i - 1] == 1) cnt[1]--;
                if(a[i - 1] == -1) cnt[0]--;
            }
            else if(a[i] < b[i]){
                if(!cnt[1]){
                    flag = 0;
                    break;
                }
                if(a[i - 1] == 1) cnt[1]--;
                if(a[i - 1] == -1) cnt[0]--;
            }
        }
        if(!flag) puts("NO");
        else puts("YES"); 
        memset(cnt, 0, sizeof(cnt));
    }
    return 0;
} 
```
核心思想是先预处理数组 $a$ 中 $1$ 和 $-1$ 的数量，然后从后往前遍历，当 $a[i]$ 和 $b[i]$ 相等时更新前一个位置的 $1$ 和 $-1$ 的数量，$a[i] > b[i]$ 时检查是否有足够的 $-1$ ，$a[i] < b[i]$ 时检查是否有足够的 $1$ ，根据结果标记并输出。

### 最优关键思路或技巧
采用贪心策略，根据 $a_i$ 和 $b_i$ 的大小关系，利用数组 $a$ 中已出现的 $1$ 和 $-1$ 来判断能否实现转换，通过记录 $1$ 和 $-1$ 的出现情况（如使用标记变量、统计数量等方式）优化判断过程，将时间复杂度控制在 $O(n)$ 。

### 拓展
同类型题通常围绕数组元素的操作与变换，给定特定的操作规则和初始、目标数组状态，判断是否能实现转换或求最少操作次数等。类似算法套路是根据操作规则和数组元素特点，分析操作对数组状态的影响，采用贪心、模拟等策略解决问题。

### 推荐题目
- [P1249 最大乘积](https://www.luogu.com.cn/problem/P1249)
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123) 

---
处理用时：78.63秒