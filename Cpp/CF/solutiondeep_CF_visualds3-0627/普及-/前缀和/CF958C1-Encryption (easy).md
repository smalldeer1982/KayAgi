# 题目信息

# Encryption (easy)

## 题目描述

Rebel spy Heidi has just obtained the plans for the Death Star from the Empire and, now on her way to safety, she is trying to break the encryption of the plans (of course they are encrypted – the Empire may be evil, but it is not stupid!). The encryption has several levels of security, and here is how the first one looks.

Heidi is presented with a screen that shows her a sequence of integers $ A $ and a positive integer $ p $ . She knows that the encryption code is a single number $ S $ , which is defined as follows:

Define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given an integer $ p $ . She needs to split $ A $ into $ 2 $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- The two parts do not overlap.
- The total sum $ S $ of the scores of those two parts is maximized. This is the encryption code.

Output the sum $ S $ , which is the encryption code.

## 说明/提示

In the first example, the score is maximized if the input sequence is split into two parts as $ (3,4) $ , $ (7,2) $ . It gives the total score of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/39bbc2e047bed6ad62ef40401430a139534974d3.png).

In the second example, the score is maximized if the first part consists of the first three elements, and the second part consists of the rest. Then, the score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/d991bcec92c9c10d8e1b00b096112e99ba9e2d35.png).

## 样例 #1

### 输入

```
4 10
3 4 7 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
10 12
16 3 24 13 9 8 7 5 12 12
```

### 输出

```
13
```

# AI分析结果



---

### 算法分类
前缀和

---

### 题解思路与核心分析

#### 核心思路
所有题解均采用**前缀和预处理 + 枚举分割点**的核心思路：
1. 预处理前缀和数组 `s`，其中 `s[i] = a[1] + a[2] + ... + a[i]`
2. 枚举分割点 `i`（1 ≤ i < n），计算两部分的和：
   - 前段：`s[i] % p`
   - 后段：`(s[n] - s[i]) % p`
3. 遍历所有分割点，取最大值

#### 解决难点
- **时间复杂度优化**：暴力枚举分割点+每次求和是 O(n²)，而前缀和将每次计算优化至 O(1)
- **取模特性理解**：必须分别对两段取模后相加，而非总和取模后再分割
- **边界条件处理**：分割点不能为 n，否则后段为空

---

### 题解评分（≥4星）

1. **chlchl（5星）**
   - 代码清晰简洁，用 `long long` 避免溢出
   - 注释明确解释「不能分割到 n」的边界条件
   - 变量命名直观（`s` 为前缀和，`ans` 存最大值）

2. **Coros_Trusds（4星）**
   - 同时计算前缀和与后缀和，展示不同实现视角
   - 代码模块化分离预处理与计算逻辑
   - 使用 `std::max` 替代手动条件判断

3. **智子（4星）**
   - 双数组分别存前缀和后缀，增强可读性
   - 代码结构完整，包含输入输出处理
   - 变量命名规范（`pre`, `suf`）

---

### 最优代码实现（关键逻辑）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5 + 10;
ll s[N], ans;
int n, p;

int main() {
    scanf("%d%d", &n, &p);
    for(int i=1; i<=n; i++) {
        scanf("%lld", &s[i]);
        s[i] += s[i-1]; // 前缀和直接原地计算
    }
    for(int i=1; i<n; i++) { // 关键循环：i不能等于n
        ans = max(ans, s[i]%p + (s[n]-s[i])%p);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

### 同类型题拓展
1. **最大子段和**（P1115）：利用前缀和快速计算区间和极值
2. **环形子数组和**（LeetCode 918）：结合前缀和与环形数组特性
3. **分割数组使差值最小**（LeetCode 1043）：动态规划+前缀和优化

---

### 可视化算法设计

#### 动画流程
1. **构建前缀和**：像素方块从左到右依次累加，每个方块显示当前前缀和值
2. **扫描分割点**：高亮当前分割点（如红色箭头），左右半区分别用不同颜色（绿/蓝）
3. **动态计算模值**：两半区上方实时显示 `sum%p` 的计算过程
4. **最大值追踪**：右侧独立区域记录历史最大值，更新时闪烁提示

#### 复古游戏化要素
- **8-bit 音效**：分割点移动（电子滴答声），新最大值出现（上升音阶）
- **像素风格**：用 16 色块表示数组元素，前缀和数字以 8-bit 字体显示
- **AI 自动演示**：分割点自动移动，速度可调（快/中/慢三档）

---

### 举一反三题目推荐
1. [洛谷 P1115] 最大子段和
2. [洛谷 P3396] 哈希冲突（前缀和变形）
3. [洛谷 P2671] 求和（前缀和+奇偶性）

---

### 关键心得摘录
> "**前缀和原地计算**可减少内存占用，但要注意数据溢出" —— chlchl  
> "分割点遍历范围必须明确 **i < n**，否则后段为空" —— Milthm  
> "取模运算的分配律不成立，必须分开计算" —— CrazyWisdom

---
处理用时：73.50秒