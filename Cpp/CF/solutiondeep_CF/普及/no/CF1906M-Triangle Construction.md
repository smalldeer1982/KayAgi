# 题目信息

# Triangle Construction

## 题目描述

You are given a regular $ N $ -sided polygon. Label one arbitrary side as side $ 1 $ , then label the next sides in clockwise order as side $ 2 $ , $ 3 $ , $ \dots $ , $ N $ . There are $ A_i $ special points on side $ i $ . These points are positioned such that side $ i $ is divided into $ A_i + 1 $ segments with equal length.

For instance, suppose that you have a regular $ 4 $ -sided polygon, i.e., a square. The following illustration shows how the special points are located within each side when $ A = [3, 1, 4, 6] $ . The uppermost side is labelled as side $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906M/e59a9e9dcf5329e7eff8711f30517212fd26fdbd.png)You want to create as many non-degenerate triangles as possible while satisfying the following requirements. Each triangle consists of $ 3 $ distinct special points (not necessarily from different sides) as its corners. Each special point can only become the corner of at most $ 1 $ triangle. All triangles must not intersect with each other.

Determine the maximum number of non-degenerate triangles that you can create.

A triangle is non-degenerate if it has a positive area.

## 说明/提示

Explanation for the sample input/output #1

One possible construction which achieves maximum number of non-degenerate triangles can be seen in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906M/42eede39a9359517d4b7c742aaa8551dfcdfbb8c.png)Explanation for the sample input/output #2

One possible construction which achieves maximum number of non-degenerate triangles can be seen in the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906M/fc47dcb22d8f025c4d1e0997698a6023ed22d7f5.png)

## 样例 #1

### 输入

```
4
3 1 4 6```

### 输出

```
4```

## 样例 #2

### 输入

```
6
1 2 1 2 1 2```

### 输出

```
3```

## 样例 #3

### 输入

```
3
1 1 1```

### 输出

```
1```

# AI分析结果



【中文题目重写】

# 三角形构造

## 题目描述

给定一个正 $N$ 边形。任选一边标记为第 $1$ 边，然后按顺时针顺序标记第 $2$、$3$，……，第 $N$ 边。第 $i$ 边上有 $A_i$ 个特殊点，这些点将该边均分为 $A_i + 1$ 段。

例如一个正四边形（正方形），当 $A = [3, 1, 4, 6]$ 时特殊点分布如示例图所示。

要求构造尽可能多的非退化三角形，满足：
1. 每个三角形由 3 个不同特殊点构成
2. 每个点最多属于一个三角形
3. 所有三角形互不相交

求可构造的最大三角形数量（非退化三角形即面积大于零的三角形）。

## 样例 #1

### 输入
```
4
3 1 4 6
```

### 输出
```
4
```

---

**算法分类**：数学

---

### 题解分析与结论

各题解核心思路均围绕两点展开：
1. 总点数 $\text{sum} = \sum A_i$ 的 $\frac{1}{3}$ 是基础答案
2. **极值限制条件**：当最大边点数 $A_{\max} > 2 \times (\text{sum} - A_{\max})$ 时，答案受限于其他边点数之和 $\text{sum} - A_{\max}$

**解决难点**在于发现当某边点数过多时，其超出部分的点数无法与其他边形成有效三角形组合。此时最优策略是使用该边的点两两与其他边的点组合，最多形成 $\text{sum} - A_{\max}$ 个三角形。

---

### 精选题解

#### 1. _Violet_Evergarden 的题解（★★★★★）
**关键亮点**：
- 精确提炼数学条件式：`maxx > 2*(sum - maxx)`
- 代码简洁高效，变量类型处理严谨

**核心代码**：
```cpp
long long sum = 0;
int maxx = 0;
for (int i = 1; i <= n; i++) {
    int a; cin >> a;
    sum += a;
    maxx = max(maxx, a);
}
if ((sum - maxx) * 2 < maxx) 
    cout << sum - maxx;
else 
    cout << sum / 3;
```

#### 2. lichenzhen 的题解（★★★★☆）
**关键亮点**：
- 用比例解释临界条件 $\frac{2}{3}\text{sum}$
- 采用三元表达式简化输出逻辑

**核心代码**：
```cpp
printf("%lld", (maxn*3 > sum*2) ? sum - maxn : sum/3);
```

#### 3. L_shadow 的题解（★★★★☆）
**调试心得**：
- 初期未考虑极值情况导致 WA，通过分析三点共线问题找到突破口
- 使用更直观的条件表达式 `maxx*3 > sum*2`

---

### 最优思路总结
1. **数学极值判断**：优先检查最大边点数是否超过其他边总和的2倍
2. **贪心分配策略**：当存在支配性边时，采用两两组合策略；否则按总点数分配
3. **数据类型处理**：总和可能超过 int 范围，必须使用 long long

---

### 拓展练习
1. [P1223 贪心的小偷](https://www.luogu.com.cn/problem/P1223)（极值条件下的最优分配）
2. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803)（贪心策略中的区间选择）
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（两两组合的最优化问题）

---

### 调试心得摘录
> "初期直接 sum/3 提交 WA，发现当一条边点数过多时，其点无法有效配对。通过构造极值测试用例，才意识到需要引入两倍条件的特判。" —— L_shadow

> "最大的坑在于三点共线的隐蔽限制，这类几何约束在纯数学题中容易忽视，需特别注意边界条件。" —— liuzhongrui

---
处理用时：94.46秒