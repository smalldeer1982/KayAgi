# 题目信息

# Yet Another Problem

## 题目描述

You are given an array $ a $ of $ n $ integers $ a_1, a_2, a_3, \ldots, a_n $ .

You have to answer $ q $ independent queries, each consisting of two integers $ l $ and $ r $ .

- Consider the subarray $ a[l:r] $ $ = $ $ [a_l, a_{l+1}, \ldots, a_r] $ . You can apply the following operation to the subarray any number of times (possibly zero)- 
  1. Choose two integers $ L $ , $ R $ such that $ l \le L \le R \le r $ and $ R - L + 1 $ is odd.
  2. Replace each element in the subarray from $ L $ to $ R $ with the XOR of the elements in the subarray $ [L, R] $ .
- The answer to the query is the minimum number of operations required to make all elements of the subarray $ a[l:r] $ equal to $ 0 $ or $ -1 $ if it is impossible to make all of them equal to $ 0 $ .

You can find more details about XOR operation [here](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 说明/提示

In the first query, $ l = 3, r = 4 $ , subarray = $ [3, 3] $ . We can apply operation only to the subarrays of length $ 1 $ , which won't change the array; hence it is impossible to make all elements equal to $ 0 $ .

In the second query, $ l = 4, r = 6 $ , subarray = $ [3, 1, 2] $ . We can choose the whole subarray $ (L = 4, R = 6) $ and replace all elements by their XOR $ (3 \oplus 1 \oplus 2) = 0 $ , making the subarray $ [0, 0, 0] $ .

In the fifth query, $ l = 1, r = 6 $ , subarray = $ [3, 0, 3, 3, 1, 2] $ . We can make the operations as follows:

1. Choose $ L = 4, R = 6 $ , making the subarray $ [3, 0, 3, 0, 0, 0] $ .
2. Choose $ L = 1, R = 5 $ , making the subarray $ [0, 0, 0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
7 6
3 0 3 3 1 2 3
3 4
4 6
3 7
5 6
1 6
2 2```

### 输出

```
-1
1
1
-1
2
0```

# AI分析结果



## 唯一算法分类  
前缀异或和、哈希表应用  

## 综合分析与结论  
### 核心思路与难点  
所有题解均基于以下核心性质：  
1. **异或和不变性**：每次操作后整个区间的异或和不变  
2. **必要条件**：当且仅当区间异或和为0时可能有解  
3. **奇偶分割特性**：偶数长度区间必须存在奇数长度的异或和为0的子区间才能拆解  

**关键实现步骤**：  
- 预处理前缀异或数组 `xsum`  
- 跳过首尾连续的0以简化问题  
- 哈希表记录每个前缀异或值在不同奇偶位置的最晚出现位置  
- 快速判断是否存在满足奇偶性的分割点  

### 可视化设计思路  
**动画方案**：  
1. **前缀异和预处理**：  
   - 数组元素用像素块表示，背景色表示数值，异或和流动线动态连接  
   - 左侧展示哈希表结构，不同颜色区分奇偶位置存储情况  
2. **查询处理流程**：  
   - 高亮当前查询区间，自动跳过首尾0（用闪烁效果标记跳过的0）  
   - 若区间全0则触发绿色闪光，播放成功音效  
   - 判断分割点时，在哈希表中检索对应奇偶性的坐标，触发检索动画  
3. **复古风格实现**：  
   - 使用16色调色板，异或和流动线用8位风格波纹效果  
   - 音效：成功用NES过关音效，失败用FC炸弹爆炸音效  

## 题解清单 (≥4星)  
1. **luo_shen（4星）**  
   - 亮点：完整推导操作次数上限，提出跳0优化，处理预处理顺序问题  
   - 心得：调试时发现必须从后往前预处理哈希表  

2. **Semorius（4星）**  
   - 亮点：简洁的奇偶哈希表设计，直接判断分割点存在性  
   - 代码：仅30行实现核心逻辑，预处理与查询分离清晰  

3. **XenonWZH（4星）**  
   - 亮点：二分查找优化分割点判断，代码可读性强  
   - 创新：使用`map<vector>`存储坐标集合，逻辑直观  

## 核心代码实现  
```cpp
// 预处理部分（Semorius版）
unordered_map<int, int> mp[2];
for (int i = n; i >= 0; i--) {
    nx[i] = mp[(i % 2) ^ 1][xsum[i]]; // 记录奇偶相反的位置
    mp[i % 2][xsum[i]] = i;
}

// 查询逻辑核心判断
if ((r - l + 1) % 2) ans = 1;
else if (a[l] == 0 || a[r == 0) ans = 1; 
else if (nx[l-1] <= r) ans = 2; // 存在合法分割点
```

## 相似题目推荐  
1. CF1775E - 前缀和与哈希表应用  
2. P1469 找筷子 - 异或性质应用  
3. CF1423J 异或构造问题  

## 个人心得摘录  
luo_shen题解中提到的调试经历：  
> "预处理顺序错误导致WA多次，最终发现必须从后往前扫描才能正确记录最近出现位置"  
> "暴力跳0会遗漏非连续0的情况，改为预处理每个位置的前后非0位置才通过"  

## 复古游戏化演示设计  
**核心动画步骤**：  
1. **初始化阶段**：  
   - 数组元素以16x16像素块呈现，下方显示前缀异或值  
   - 哈希表区域分奇偶两列，动态更新存储状态  

2. **查询阶段**：  
   - 当前查询区间边框闪烁红色，自动收缩跳过首尾0（伴随8位滑动音效）  
   - 分割点检索时，在哈希表对应奇偶列触发扫描光束  

3. **结果反馈**：  
   - 成功时整个区间变为绿色方块雨，播放《超级马里奥》金币音效  
   - 失败时区间爆炸为像素碎片，播放《魂斗罗》中弹音效  

**AI自动演示模式**：  
- 随机生成测试用例，自动展示不同情况处理流程  
- 右下角显示当前操作计数，达成最优解时触发连击加分特效

---
处理用时：72.13秒