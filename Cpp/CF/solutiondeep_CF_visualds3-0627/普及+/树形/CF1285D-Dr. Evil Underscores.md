# 题目信息

# Dr. Evil Underscores

## 题目描述

Today, as a friendship gift, Bakry gave Badawy $ n $ integers $ a_1, a_2, \dots, a_n $ and challenged him to choose an integer $ X $ such that the value $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ is minimum possible, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

As always, Badawy is too lazy, so you decided to help him and find the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 说明/提示

In the first sample, we can choose $ X = 3 $ .

In the second sample, we can choose $ X = 5 $ .

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 5```

### 输出

```
4```

# AI分析结果



# 算法分类
**位运算分治**

# 综合分析与结论
## 核心思路
题目要求找到一个整数 X，使得所有 a_i 异或 X 后的最大值最小。采用**高位优先的贪心策略**，按位从高到低处理：

1. **按位分组**：将数组按当前处理位（如第k位）分割为0组和1组
2. **决策逻辑**：
   - 若两组都存在 → 该位必然贡献 2^k，递归取两组最小值相加
   - 若只有一组 → 该位可消去为0，递归处理剩余位
3. **递归终止**：处理到最低位时返回0

## 解决难点
- **高位优先处理**：高位的权值远大于低位，必须优先处理高位
- **分治策略**：通过递归将大问题分解为子问题，避免暴力枚举X
- **空间优化**：无需显式建立Trie树，通过动态分组降低空间消耗

## 可视化设计
1. **动画演示**：
   - 用不同颜色标记当前处理位（如红色高亮）
   - 将数组动态分割为左右两组（0组蓝色，1组绿色）
   - 递归时显示新的分组与当前位贡献值

2. **复古风格**：
   - 8位像素风格界面，使用16色调色板
   - 音效设计：
     - 分组时播放短促"滴"声
     - 递归返回时播放"嗒"声
     - 找到最优解时播放胜利音效

3. **交互功能**：
   - 步进控制：空格键单步执行
   - 速度调节：方向键控制动画速度
   - 自动演示：按A键自动运行

# 题解评分 (≥4星)
1. **基地A_I（5星）**  
   - 核心代码仅20行，递归逻辑清晰
   - 时间复杂度O(n logC)，空间优化到位
   - 代码结构易于移植到其他语言

2. **EternalHeart1314（4.5星）**  
   - 注释详细，变量命名规范
   - 使用vector动态分组，内存效率高
   - 包含样例推导说明，便于理解

3. **Pengzt（4星）**  
   - 结合排序预处理优化分组效率
   - 使用位掩码替代实际分割，节省内存
   - 代码包含性能优化思路说明

# 核心代码实现
```cpp
int dfs(vector<int>& nums, int bit) {
    if (bit < 0) return 0;
    vector<int> zero, one;
    for (int num : nums) {
        if (num & (1 << bit)) one.push_back(num);
        else zero.push_back(num);
    }
    if (zero.empty()) return dfs(one, bit-1);
    if (one.empty()) return dfs(zero, bit-1);
    return (1 << bit) + min(dfs(zero, bit-1), dfs(one, bit-1));
}

int main() {
    vector<int> nums = {1,2,3}; // 示例输入
    cout << dfs(nums, 30); // 从最高位30开始处理
}
```

# 同类型题目
1. **CF817E** - 寻找最大异或对（Trie树应用）
2. **AT_abc281f** - 双倍经验题
3. **LeetCode 421** - 数组中两个数的最大异或值

# 可视化代码片段
```javascript
// 伪代码演示递归过程
function visualizeDFS(bit, zeroArr, oneArr) {
    highlightBit(bit); // 高亮当前bit位
    drawSplitAnimation(zeroArr, oneArr); // 绘制分组动画
    if (zeroArr.length && oneArr.length) {
        playSound('split'); // 播放分割音效
        let left = recursiveCall(zeroArr, bit-1);
        let right = recursiveCall(oneArr, bit-1);
        showMinResult(left, right); // 显示取min过程
    }
    // ...其他情况处理
}
```

# 个人心得
- **调试技巧**：用二进制打印中间分组结果，如`cout << bitset<4>(num)`
- **性能优化**：预排序后通过指针范围传递分组，减少vector拷贝
- **思维突破**：认识到当某位存在两种值时，该位必然贡献2^k，这是解题的关键

---
处理用时：74.97秒