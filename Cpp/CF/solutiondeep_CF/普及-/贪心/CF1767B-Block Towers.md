# 题目信息

# Block Towers

## 题目描述

There are $ n $ block towers, numbered from $ 1 $ to $ n $ . The $ i $ -th tower consists of $ a_i $ blocks.

In one move, you can move one block from tower $ i $ to tower $ j $ , but only if $ a_i > a_j $ . That move increases $ a_j $ by $ 1 $ and decreases $ a_i $ by $ 1 $ . You can perform as many moves as you would like (possibly, zero).

What's the largest amount of blocks you can have on the tower $ 1 $ after the moves?

## 说明/提示

In the first testcase, you can move a block from tower $ 2 $ to tower $ 1 $ , making the block counts $ [2, 1, 3] $ . Then move a block from tower $ 3 $ to tower $ 1 $ , making the block counts $ [3, 1, 2] $ . Tower $ 1 $ has $ 3 $ blocks in it, and you can't obtain a larger amount.

In the second testcase, you can move a block from any of towers $ 2 $ or $ 3 $ to tower $ 1 $ , so that it has $ 2 $ blocks in it.

In the third testcase, you can $ 500000000 $ times move a block from tower $ 2 $ to tower $ 1 $ . After that the block countes will be $ [500000001, 500000000] $ .

## 样例 #1

### 输入

```
4
3
1 2 3
3
1 2 2
2
1 1000000000
10
3 8 6 7 4 1 2 4 10 1```

### 输出

```
3
2
500000001
9```

# AI分析结果



# Block Towers 题解中文翻译

## 题目描述

有 $n$ 个方块塔，编号从 $1$ 到 $n$。第 $i$ 个塔包含 $a_i$ 个方块。

每次操作中，若塔 $i$ 的方块数大于塔 $j$，可以将一个方块从塔 $i$ 移到塔 $j$（此时 $a_i$ 减 1，$a_j$ 加 1）。求经过任意次操作后，塔 1 的最大方块数量。

## 说明/提示

样例 1 中，通过两次操作使塔 1 达到最大值 3。样例 3 中通过大量操作使塔 1 达到 500000001。

---

## 题解综合分析与结论

### 核心算法思路
所有题解均基于以下关键观察：
1. **操作后总和不变**：每次移动不影响总方块数，最终结果仅与分配方式相关。
2. **贪心策略**：要使塔 1 最大化，需优先处理较小的较大值，每次将塔 1 与比它大的最小元素合并。
3. **数学公式**：两个数 $a_1$ 和 $a_i$ 多次操作后，塔 1 的值变为 $\lceil \frac{a_1+a_i}{2} \rceil$。

### 最优解关键技巧
1. **排序预处理**：将其他塔按升序排序，确保每次处理最小的较大值。
2. **迭代更新**：依次将塔 1 与每个大于它的元素合并，使用公式 `a1 = (a1 + a_i + 1) / 2` 更新。

---

## 精选题解（评分≥4星）

### 1. 作者：hyfzelda（★★★★☆）
**亮点**：代码简洁，直接处理输入后排序，用整数运算避免浮点误差。
```cpp
sort(a+1,a+n);  // 对除塔1外的元素排序
for(int i=1;i<n;i++)
    if(x < a[i]) x = (x + a[i] + 1)/2;  // 关键更新公式
```

### 2. 作者：ImNot6Dora（★★★★☆）
**亮点**：使用标准库函数 `ceil` 明确表达向上取整逻辑，代码结构清晰。
```cpp
sort(a+2, a+n+1);
for(int i=2; i<=n; i++)
    if(a[1]<a[i])
        a[1] = ceil((a[1]+a[i])/2.0);  // 显式向上取整
```

### 3. 作者：0zhouyq（★★★★★）
**亮点**：采用优先队列动态维护较大值，避免完整排序，时空效率更优。
```cpp
priority_queue<ll, vector<ll>, greater<ll>> q;
while(!q.empty()) {
    a = (a + q.top() + 1)/2;  // 位运算加速
    q.pop();
}
```

---

## 关键代码实现
以最优的优先队列解法为例：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int T; cin >> T;
    while(T--) {
        int n; ll a, x;
        cin >> n >> a;
        priority_queue<ll, vector<ll>, greater<ll>> q;
        for(int i=1; i<n; i++) {
            cin >> x;
            if(x > a) q.push(x);
        }
        while(!q.empty()) {
            a = (a + q.top() + 1) >> 1;  // 位运算优化
            q.pop();
        }
        cout << a << endl;
    }
    return 0;
}
```

---

## 拓展与举一反三

### 相似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 优先队列贪心
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 排序贪心
3. [P5019 铺设道路](https://www.luogu.com.cn/problem/P5019) - 贪心分配策略

### 个人心得摘录
"操作顺序影响最终结果，必须从小到大处理才能最大化塔1" —— 多题解强调贪心顺序的重要性。调试时需注意输入数据范围（如 1e9 需用 long long）。

---
处理用时：75.30秒