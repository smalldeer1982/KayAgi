# 题目信息

# Advertising Agency

## 题目描述

Masha works in an advertising agency. In order to promote the new brand, she wants to conclude contracts with some bloggers. In total, Masha has connections of $ n $ different bloggers. Blogger numbered $ i $ has $ a_i $ followers.

Since Masha has a limited budget, she can only sign a contract with $ k $ different bloggers. Of course, Masha wants her ad to be seen by as many people as possible. Therefore, she must hire bloggers with the maximum total number of followers.

Help her, find the number of ways to select $ k $ bloggers so that the total number of their followers is maximum possible. Two ways are considered different if there is at least one blogger in the first way, which is not in the second way. Masha believes that all bloggers have different followers (that is, there is no follower who would follow two different bloggers).

For example, if $ n=4 $ , $ k=3 $ , $ a=[1, 3, 1, 2] $ , then Masha has two ways to select $ 3 $ bloggers with the maximum total number of followers:

- conclude contracts with bloggers with numbers $ 1 $ , $ 2 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_1 + a_2 + a_4 = 6 $ .
- conclude contracts with bloggers with numbers $ 2 $ , $ 3 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_2 + a_3 + a_4 = 6 $ .

Since the answer can be quite large, output it modulo $ 10^9+7 $ .

## 说明/提示

The test case is explained in the statements.

In the second test case, the following ways are valid:

- conclude contracts with bloggers with numbers $ 1 $ and $ 2 $ . In this case, the number of followers will be equal to $ a_1 + a_2 = 2 $ ;
- conclude contracts with bloggers with numbers $ 1 $ and $ 3 $ . In this case, the number of followers will be equal to $ a_1 + a_3 = 2 $ ;
- conclude contracts with bloggers with numbers $ 1 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_1 + a_4 = 2 $ ;
- conclude contracts with bloggers with numbers $ 2 $ and $ 3 $ . In this case, the number of followers will be equal to $ a_2 + a_3 = 2 $ ;
- conclude contracts with bloggers with numbers $ 2 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_2 + a_4 = 2 $ ;
- conclude contracts with bloggers with numbers $ 3 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_3 + a_4 = 2 $ .

In the third test case, the following ways are valid:

- concludes a contract with a blogger with the number $ 2 $ . In this case, the number of followers will be equal to $ a_2 = 2 $ .

## 样例 #1

### 输入

```
3
4 3
1 3 1 2
4 2
1 1 1 1
2 1
1 2```

### 输出

```
2
6
1```

# AI分析结果


# 💡 Kay的C++算法解析：Advertising Agency 深入学习指南 💡

<introduction>
今天我们来分析"Advertising Agency"这道C++编程题。这道题要求我们在给定博主粉丝数的情况下，选择k个博主使粉丝总数最大，并计算方案数。本指南将带你深入理解解题思路、核心算法和实现技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`组合数学`与`贪心策略`

🗣️ **初步分析**：
> 解决这道题的关键在于**贪心选择+组合计数**。想象你在果园挑选最大的k个苹果，但有些苹果大小相同 - 这时挑选哪些相同大小的苹果就会产生不同方案！算法流程如下：
> 1. 按粉丝数从大到小排序（或使用桶计数）
> 2. 累加粉丝数，直到覆盖k个选择位置
> 3. 当遇到"临界值"（第k大的数）时，计算需从中选多少个数
> 4. 用组合数公式C(cnt, need)计算方案数
>
> **可视化设计思路**：采用8位像素风格展示博主粉丝数（不同高度的像素柱），高亮显示被选中的博主。当遇到多个相同粉丝数时，展示组合选择过程（像素方块闪烁+选择音效）。控制面板支持单步执行观察选择过程。

---

## 2. 精选优质题解参考

<eval_intro>
我基于思路清晰度、代码规范性和算法效率，精选了以下高质量题解：

**题解一（来源：Carotrl）**
* **点评**：思路清晰直击核心（贪心+组合计数），代码规范易读（桶计数+杨辉三角预处理组合数）。亮点在于高效处理临界值逻辑：从大到小遍历桶，当累计博主数≥k时计算组合数。边界处理严谨（k=0等特殊情况），可直接用于竞赛。

**题解二（来源：冰糖鸽子）**
* **点评**：解法简洁高效，直接排序后定位第k大的值。亮点在于巧妙计算：统计≥第k大值总数(cnt)和前k个中该值出现次数(cnt2)，用C(cnt, cnt-cnt2)得解。变量命名清晰(a,cnt,cnt2)，组合数预处理规范，实践参考价值高。

**题解三（来源：sochiji）**
* **点评**：结构严谨，解释详尽。亮点在于分步演示贪心策略（如"苹果选择"比喻），桶计数+杨辉三角实现。控制流清晰（for循环遍历桶），边界处理完整，适合初学者理解。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破以下关键点：

1.  **确定选择策略**
    * **分析**：必须选择前k大值，但相同值可能产生多方案。优质解法都先排序/桶排序，确保从大到小选择。
    * 💡 **学习笔记**：贪心策略是基础，排序保证正确性。

2.  **定位临界值**
    * **分析**：当累计博主数≥k时，最后一个加入的值（第k大值）就是临界点。需计算：该值的总数(total)和还需选择数(need = k-已选数)。
    * 💡 **学习笔记**：`need = k - (已选博主数 - 该值总数)`是核心计算。

3.  **高效计算组合数**
    * **分析**：C(total, need)需模10^9+7。常用两种方案：①预处理杨辉三角（O(n²)）②阶乘+逆元（O(n log p)）。题解多采用杨辉三角因n≤1000。
    * 💡 **学习笔记**：组合数计算要预判边界（如total=0或need=0时返回1）。

### ✨ 解题技巧总结
<summary_best_practices>
- **技巧1（桶计数优化）**：当值域小（aᵢ≤n）时，用桶代替全排序，复杂度从O(n log n)降至O(n)
- **技巧2（组合数预处理）**：多测试用例时，在main()外预计算杨辉三角表避免重复
- **技巧3（边界鲁棒性）**：特判k=0（方案数为1）和k>n（无解）的情况
- **技巧4（调试验证）**：用样例[1,3,1,2]k=3验证，应得组合数C(2,1)=2
---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是整合优质题解思路的通用实现：

```cpp
#include <iostream>
#include <cstring>
#define MOD 1000000007
using namespace std;

// 预处理组合数表（全局只计算一次）
long long C[1005][1005];
void init() {
    for (int i = 0; i <= 1000; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) 
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }
}

int main() {
    init(); // 初始化组合数表
    int T; cin >> T;
    while (T--) {
        int n, k, x, cnt[1001] = {0};
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> x;
            cnt[x]++; // 桶计数
        }
        
        int selected = 0;
        for (int val = 1000; val >= 1; val--) {
            if (!cnt[val]) continue;
            if (selected + cnt[val] < k) {
                selected += cnt[val]; // 全选当前值
            } else {
                int need = k - selected; // 还需选择的数量
                cout << C[cnt[val]][need] << endl;
                break;
            }
        }
    }
    return 0;
}
```

**代码解读概要**：
1. **预处理**：`init()`用杨辉三角计算所有C(n,k)组合数
2. **桶计数**：`cnt[x]`统计粉丝数为x的博主数量
3. **贪心选择**：从大到小遍历值（1000→1）
4. **临界处理**：当累计选择数≥k时，计算组合数C(cnt[val], need)

---

<code_intro_selected>
### 精选题解核心片段赏析

**题解一（Carotrl）**
* **亮点**：桶计数+组合数表高效实现
* **核心片段**：
```cpp
for (int i = n; i >= 1; i--) {
    if (sum + b[i] < k) sum += b[i];
    else {
        int need = k - sum;
        ans = C[b[i]][need]; 
        break;
    }
}
```
* **代码解读**：
> 循环从最大粉丝数向下遍历。`b[i]`是粉丝数i的博主数量。若累计`sum + b[i]`仍小于k，则全选当前值；否则计算还需选的数量`need`，用组合数C(b[i], need)得解。
> **关键变量**：`sum`（已选博主数），`b[i]`（桶计数数组）
* 💡 **学习笔记**：桶计数避免排序，O(n)复杂度

**题解二（冰糖鸽子）**
* **亮点**：直接定位第k大值
* **核心片段**：
```cpp
sort(a+1, a+1+n, greater<int>());
int target = a[k]; // 第k大的值
int total = count(a+1, a+n+1, target);
int selected_in_topk = count(a+1, a+k+1, target);
cout << C[total][selected_in_topk] << endl;
```
* **代码解读**：
> 先对数组降序排序。`target`即第k大的值，`total`是该值总出现次数，`selected_in_topk`是前k个中该值出现次数。组合数计算C(total, selected_in_topk)。
> **注意**：实际应为C(total, need)，其中need = selected_in_topk - (k - total)？原代码逻辑需验证
* 💡 **学习笔记**：排序后可直接定位临界值

**题解三（sochiji）**
* **亮点**：完整贪心步骤演示
* **核心片段**：
```cpp
for (int val = max_val; val >= 1; val--) {
    if (cnt[val] == 0) continue;
    if (remaining > cnt[val]) {
        remaining -= cnt[val];
    } else {
        ans = C[cnt[val]][remaining];
        break;
    }
}
```
* **代码解读**：
> `remaining`初始为k，表示还需选择的数量。遍历桶时若当前值数量≤remaining，则全部选择；否则用组合数计算方案。逻辑与其他解法一致。
* 💡 **学习笔记**：`remaining`变量名比`need`更直观

-----

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
让我们通过8位像素游戏动画理解算法执行过程！设计思路：用不同高度像素柱表示博主粉丝数，复古音效增强关键操作反馈。

<center>
![像素动画示意图](https://via.placeholder.com/600x200/36363d/ffffff?text=排序+→+选择+→+组合计算)
</center>
</visualization_intro>

* **动画主题**：像素博主大选择
* **核心演示**：桶计数→从大到小选择→临界值组合计算
* **设计思路**：8位像素风格降低理解压力，音效强化关键操作记忆

* **动画步骤**：
  1. **初始化（像素网格）**：
      - 屏幕显示1000×600像素画布
      - 博主显示为颜色编码的像素柱：高度=粉丝数/10（蓝：1-100，绿：101-300，红：301+）
      - 控制面板：开始/暂停、单步、速度滑块（右下角）
      - 背景音乐：8-bit轻快循环BGM

  2. **桶计数（像素聚合）**：
      - 输入[1,3,1,2] → 像素柱分散出现
      - 桶计数过程：相同高度像素柱合并，底部显示`cnt[1]=2, cnt[2]=1, cnt[3]=1`
      - 音效：计数时"嘀"声，合并时"咔嚓"声

  3. **贪心选择（高亮+音效）**：
      - 从高到低遍历：`val=3`的柱高亮闪烁 → 全选（变金色）→ 播放"选择"音效
      - `val=2`：高亮 → 需选择但数量不足k→全选
      - 当前已选：3(金), 2(金)，还需选1个

  4. **临界值处理（组合动画）**：
      - `val=1`：两个高度相同的像素柱交替闪烁
      - 显示组合公式`C(2,1)=2`
      - 动态演示：先选左柱（路径1），再选右柱（路径2），各伴随"选定"音效

  5. **结果展示**：
      - 成功：显示两条金色路径 + 胜利音效
      - 可切换AI自动演示（速度可调），像贪吃蛇自动选择路径

* **交互设计**：
  - 单步执行：按空格键逐步观察
  - 鼠标悬停：显示博主粉丝数
  - 错误提示：选值错误时像素柱变灰+警告音

<visualization_conclusion>
通过像素动画，你可直观看到：为何相同粉丝数的博主会产生多方案，以及组合数如何计算选择方式！
</visualization_conclusion>

-----

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的贪心+组合思想后，可解决更多变种问题：

* **技巧迁移**：
  1. 资源分配问题（如：从n个物品选k个最大价值）
  2. 带限制的组合计数（如：选数和要求总和%p=0）
  3. 多维约束扩展（如：博主粉丝数+互动率双指标）

* **推荐练习（洛谷）**：
  1. **P2638 安全系统**  
     🗣️ 组合数经典应用，巩固桶计数思想
  2. **P2822 组合数问题**  
     🗣️ 二维前缀和+组合数预处理，提升优化能力
  3. **P3807 卢卡斯定理**  
     🗣️ 大数组合数进阶，学习模数处理技巧

-----

## 7. 学习心得与经验分享

<insights_intro>
题解中的调试经验值得借鉴：

> **参考经验（Cutest_Junior）**：  
> "Virtual participation时把`nth_element(arr+1, arr+k, ...)`错写成`arr+k+1`，导致WA。这提醒我们：调用库函数需仔细核对参数！"

> **点评**：标准库函数参数易错，建议：
> 1. 写代码时查文档确认参数顺序
> 2. 用完后立即写简单测试用例验证
> 3. 封装常用操作（如`nth_element_wrapper`）

---

<conclusion>
本次分析展示了如何用贪心+组合数学解决"Advertising Agency"问题。关键点在于：排序定位临界值 → 组合计算方案数。通过像素动画，我们直观理解了多方案的产生原理。记住：编程能力=基础算法×调试技巧×创造力！下次挑战见！🚀
</conclusion>
```

---
处理用时：145.63秒