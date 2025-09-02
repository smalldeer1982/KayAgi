# 题目信息

# Moscow Gorillas

## 题目描述

In winter, the inhabitants of the Moscow Zoo are very bored, in particular, it concerns gorillas. You decided to entertain them and brought a permutation $ p $ of length $ n $ to the zoo.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

The gorillas had their own permutation $ q $ of length $ n $ . They suggested that you count the number of pairs of integers $ l, r $ ( $ 1 \le l \le r \le n $ ) such that $ \operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r]) $ .

The $ \operatorname{MEX} $ of the sequence is the minimum integer positive number missing from this sequence. For example, $ \operatorname{MEX}([1, 3]) = 2 $ , $ \operatorname{MEX}([5]) = 1 $ , $ \operatorname{MEX}([3, 1, 2, 6]) = 4 $ .

You do not want to risk your health, so you will not dare to refuse the gorillas.

## 说明/提示

In the first example, two segments are correct – $ [1, 3] $ with $ \operatorname{MEX} $ equal to $ 4 $ in both arrays and $ [3, 3] $ with $ \operatorname{MEX} $ equal to $ 1 $ in both of arrays.

In the second example, for example, the segment $ [1, 4] $ is correct, and the segment $ [6, 7] $ isn't correct, because $ \operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4) $ .

## 样例 #1

### 输入

```
3
1 3 2
2 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4```

### 输出

```
16```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
6 5 4 3 2 1```

### 输出

```
11```

# AI分析结果



# Moscow Gorillas 题解分析

## 算法分类
**组合数学**

---

## 题解思路与难点对比

### 核心思路
**枚举MEX值**：通过枚举MEX值m，统计满足两个排列在区间[l,r]的MEX均为m的区间数量。关键点在于：
1. 区间必须包含1~m-1的所有元素
2. 区间不能包含m元素
3. 同时满足上述条件在两个排列中的镜像条件

### 数学推导要点
1. **区间覆盖条件**：用l和r维护当前必须覆盖的最小左边界和最大右边界（所有1~m-1元素的极值位置）
2. **排斥条件**：计算两个排列中m的位置是否在当前区间外，分三种情况计算可能区间数
3. **组合计数公式**：
   - 左区间范围：max(s_m, t_m) < l
   - 右区间范围：r < min(s_m, t_m)
   - 贡献公式：(n - r + 1) * (l - max(s_m, t_m))

### 解决难点
- **动态维护区间边界**：每次处理m后更新l=min(l, s_m), r=max(r, t_m)
- **对称性处理**：当s_m > t_m时交换两者，统一计算逻辑
- **特判MEX=1**：需要单独处理不包含1的区间组合数

---

## 最优题解评分

### TernaryTree（★★★★☆）
- **思路清晰**：分情况图示说明三种区域划分
- **代码简洁**：仅30行核心逻辑
- **优化点**：通过交换s_m和t_m统一计算流程
- **代码亮点**：
  ```cpp
  if (k1 < l && k2 > r) 
    ans += (l - k1) * (k2 - r);
  ```

### lizhous（★★★★☆）
- **抽象层次高**：提出区间必须覆盖极值区间的思想
- **函数封装**：通过geter函数计算范围交集
- **可读性**：使用中文注释解释关键步骤

### 寻逍遥2006（★★★★☆）
- **公式推导完整**：给出所有情况的组合数公式
- **代码压缩**：仅用1个循环完成所有计算
- **数学美感**：用对称性思想处理区间覆盖

---

## 关键代码实现
```cpp
// 核心逻辑：处理m>=2的情况
int l = min(s[1], t[1]), r = max(s[1], t[1]);
for (int m = 2; m <= n; m++) {
    int k1 = s[m], k2 = t[m];
    if (k1 > k2) swap(k1, k2);
    
    if (k1 < l && k2 < l) // m在左侧
        ans += (n - r + 1) * (l - k2);
    else if (k1 > r && k2 > r) // m在右侧
        ans += (k1 - r) * l;
    else if (k1 < l && k2 > r) // m跨越区间
        ans += (l - k1) * (k2 - r);
    
    l = min(l, k1);
    r = max(r, k2);
}
ans += 1; // mex=n+1的情况
```

---

## 同类型题套路
1. **MEX相关**：统计满足MEX条件的区间/子集数
2. **排列性质**：利用元素唯一性进行极值维护
3. **双指针维护**：动态调整必须覆盖的区间边界

---

## 推荐题目
1. CF 1527D - MEX Tree（树上的MEX路径统计）
2. CF 1567D - Expression Evaluation Error（MEX与数位组合）
3. P4135 - 区间Mex（主席树维护MEX）

---

## 可视化设计

### 像素动画方案
1. **颜色标记**：
   - 红色：当前处理的m值位置
   - 绿色：必须覆盖的区间[l,r]
   - 蓝色：可行区间范围

2. **动画步骤**：
   ```python
   # 伪代码逻辑
   for m in 1..n+1:
       draw_grid() # 显示排列p和q
       highlight(s[m], t[m]) # 标记当前m的位置
       draw_rectangle(l, r) # 显示必须覆盖区间
       show_valid_zones() # 显示可行区间范围
       calculate_contribution() # 显示组合数计算公式
       update_lr() # 动态收缩l和r
   ```

3. **8位音效**：
   - 步骤完成：NES风格"coin"音效
   - 错误操作：经典"error"蜂鸣声
   - 区间收缩：扫频音效

---

## 个人心得
- **区间动态维护**：通过极值更新代替复杂数据结构
- **对称性思维**：交换s_m和t_m统一处理逻辑
- **特判优先**：先处理m=1避免循环中的复杂条件

---

通过这种组合数学的思考方式，将看似复杂的MEX问题转化为动态维护区间边界的可计算问题，是解决此类排列相关统计问题的典型思路。

---
处理用时：80.81秒