# 题目信息

# Farmer John's Challenge

## 题目描述

[Trade Winds - Patrick Deng](https://soundcloud.com/patrick-deng-392681004/trade-winds-ft-alex-zhu)

⠀



Let's call an array $ a $ sorted if $ a_1 \leq a_2 \leq \ldots \leq a_{n - 1} \leq a_{n} $ .

You are given two of Farmer John's favorite integers, $ n $ and $ k $ . He challenges you to find any array $ a_1, a_2, \ldots, a_{n} $ satisfying the following requirements:

- $ 1 \leq a_i \leq 10^9 $ for each $ 1 \leq i \leq n $ ;
- Out of the $ n $ total cyclic shifts of $ a $ , exactly $ k $ of them are sorted. $ ^\dagger $

If there is no such array $ a $ , output $ -1 $ .

 $ ^\dagger $ The $ x $ -th ( $ 1 \leq x \leq n $ ) cyclic shift of the array $ a $ is $ a_x, a_{x+1} \ldots a_n, a_1, a_2 \ldots a_{x - 1} $ . If $ c_{x, i} $ denotes the $ i $ 'th element of the $ x $ 'th cyclic shift of $ a $ , exactly $ k $ such $ x $ should satisfy $ c_{x,1} \leq c_{x,2} \leq \ldots \leq c_{x, n - 1} \leq c_{x, n} $ .

For example, the cyclic shifts for $ a = [1, 2, 3, 3] $ are the following:

- $ x = 1 $ : $ [1, 2, 3, 3] $ (sorted);
- $ x = 2 $ : $ [2, 3, 3, 1] $ (not sorted);
- $ x = 3 $ : $ [3, 3, 1, 2] $ (not sorted);
- $ x = 4 $ : $ [3, 1, 2, 3] $ (not sorted).

## 说明/提示

In the first testcase, $ a = [1, 1] $ satisfies $ n = 2, k = 2 $ :

The two cyclic shifts of $ a $ are $ [a_1, a_2] $ and $ [a_2, a_1] $ , which are both $ [1, 1] $ and are sorted.

In the second testcase, $ a = [69\,420, 69, 420] $ satisfies $ n = 3, k = 1 $ :

The three cyclic shifts of $ a $ are $ [a_1, a_2, a_3] $ , $ [a_2, a_3, a_1] $ , $ [a_3, a_1, a_2] $ , which are $ [69\,420, 69, 420] $ , $ [69, 420, 69\,420] $ , and $ [420, 69\,420, 69] $ , respectively.

Only $ [69, 420, 69\,420] $ is sorted.

## 样例 #1

### 输入

```
3
2 2
3 1
3 2```

### 输出

```
1 1
69420 69 420
-1```

# AI分析结果



**唯一算法分类**: 组合数学

---

### 题解思路与核心难点

#### **核心思路**
问题要求构造数组满足恰好 `k` 个循环移位有序。通过数学分析发现：
1. **k=1**：构造严格递增数组（如 `1,2,...,n`），仅原数组有序。
2. **k=n**：构造全等数组（如全 `1`），所有循环移位均有序。
3. **其他k值**：无解，因无法满足非全等数组的多次有序循环移位。

#### **关键证明**
- 若存在两个不同循环移位均有序，则数组元素必须全等（推导见下文）。
- 非全等数组最多只有一个有序循环移位（原数组本身）。

#### **数学推导**
假设存在两个不同的循环移位 `x` 和 `y` 均有序：
```
a_x ≤ a_{x+1} ≤ ... ≤ a_n ≤ a_1 ≤ ... ≤ a_{x-1}  
a_y ≤ a_{y+1} ≤ ... ≤ a_n ≤ a_1 ≤ ... ≤ a_{y-1}
```
结合原数组递增条件 `a_1 ≤ a_2 ≤ ... ≤ a_n`，可得 `a_1 = a_2 = ... = a_n`，即全等数组。

---

### 最优题解评分（≥4星）

1. **luobotianle (5星)**
   - 思路清晰，直接给出构造条件。
   - 代码简洁，覆盖所有情况。
   - 实践性强，无需复杂运算。

2. **I_will_AKNOI (4星)**
   - 明确数学推理，解释全等数组的必要性。
   - 代码简单易懂，输出灵活。

3. **Alexxu2024 (4星)**
   - 通过打表验证，增强结论可信度。
   - 代码结构清晰，附带详细注释。

---

### 关键代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int main(){
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(k==1) for(int i=1;i<=n;i++) cout<<i<<" ";
        else if(k==n) for(int i=1;i<=n;i++) cout<<"1 ";
        else cout<<-1;
        cout<<"\n";
    }
    return 0;
}
```
**核心逻辑**：直接判断 `k` 的值，分别构造递增或全等数组。

---

### 同类问题与推荐题目
1. **构造全等数组**：如 [CF12B Correct Solution?](https://www.luogu.com.cn/problem/CF12B)。
2. **循环移位性质**：如 [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)。
3. **数学构造题**：如 [CF1360B Honest Coach](https://www.luogu.com.cn/problem/CF1360B)。

---

### 可视化设计思路（8位像素风）
1. **动画流程**：
   - **步骤1**：绘制网格，每个格子代表数组元素。
   - **步骤2**：高亮当前构造的数组（如递增时，颜色渐变）。
   - **步骤3**：模拟循环移位，红色标记无序的位置。
   - **步骤4**：统计有效移位数，显示是否匹配 `k`。

2. **音效与交互**：
   - 成功构造时播放8-bit胜利音效。
   - 无解时播放低沉音效，屏幕闪烁提示。

3. **Canvas示例**：
   ```javascript
   // 伪代码：绘制递增数组
   function drawSortedArray(ctx, n) {
       for(let i=0; i<n; i++) {
           ctx.fillStyle = `hsl(${i*30}, 70%, 50%)`; // 渐变颜色
           ctx.fillRect(i*30, 0, 25, 25);
       }
   }
   ```

---

**个人心得**：构造题的难点常在于发现隐藏的数学约束，需通过反证法或极端案例验证猜想。本题通过分析循环移位的序关系，快速锁定全等数组的必要性，是此类问题的典型解法。

---
处理用时：64.97秒