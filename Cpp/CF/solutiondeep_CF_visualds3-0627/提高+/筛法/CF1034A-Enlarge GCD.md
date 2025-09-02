# 题目信息

# Enlarge GCD

## 题目描述

Mr. F has $ n $ positive integers, $ a_1, a_2, \ldots, a_n $ .

He thinks the greatest common divisor of these integers is too small. So he wants to enlarge it by removing some of the integers.

But this problem is too simple for him, so he does not want to do it by himself. If you help him, he will give you some scores in reward.

Your task is to calculate the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

## 说明/提示

In the first example, the greatest common divisor is $ 1 $ in the beginning. You can remove $ 1 $ so that the greatest common divisor is enlarged to $ 2 $ . The answer is $ 1 $ .

In the second example, the greatest common divisor is $ 3 $ in the beginning. You can remove $ 6 $ and $ 9 $ so that the greatest common divisor is enlarged to $ 15 $ . There is no solution which removes only one integer. So the answer is $ 2 $ .

In the third example, there is no solution to enlarge the greatest common divisor. So the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
6 9 15 30
```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
-1```

# AI分析结果



**唯一算法分类**：数论-质因数分解与筛法

---

### **题解思路与算法要点**

#### **核心问题转化**
1. 设原数组的GCD为$g$，将所有数除以$g$，转化为求新数组的GCD>1
2. 新问题等价于：找出一个质数$p$，使得最多的数能被$p$整除

#### **关键实现步骤**
1. **预处理质数**：使用埃氏筛/线性筛预处理新数组最大值域内的质数
2. **质数统计**：对每个质数$p$，统计新数组中$p$的倍数数量$cnt_p$
3. **最优解计算**：答案=总数-最大的$cnt_p$（需$cnt_p≠0$）

#### **解决难点对比**
| 方法类型          | 时间复杂度           | 核心优化点                          |
|-------------------|----------------------|-------------------------------------|
| 线性筛+质因数分解 | O(max_a + nlogmax_a) | 预处理最小质因数实现快速质因数分解  |
| 埃氏筛+倍数统计   | O(max_a loglogmax_a) | 直接枚举质数的倍数统计出现次数      |

---

### **题解评分 ≥4星**

1. **Siyuan的优化思路（5星）**  
   ✅ 将原数组全部除以GCD的转化思路巧妙  
   ✅ 埃氏筛同时完成质数筛选和倍数统计  
   ⚡ 代码仅30行，利用筛法的跳跃式统计极大优化效率

2. **Acc_Robin的线性筛实现（4.5星）**  
   ✅ 数学推导严谨，证明最终GCD必为质数的思路清晰  
   ✅ 预处理最小质因数实现O(1)查询质因子  
   🔧 代码中`vis`数组的复用节省内存空间

3. **kimi0705的简洁实现（4星）**  
   ✅ 使用`__gcd`函数简化代码逻辑  
   ✅ 动态维护最大值的思路避免额外遍历  
   💡 关键注释"筛素数"部分直指算法核心

---

### **最优思路提炼**
1. **数学转化**：通过除以原GCD将问题转化为寻找质数因子的统计问题
2. **筛法复用**：在筛质数的过程中同步完成倍数统计（如埃氏筛的第二层循环）
3. **极简统计**：对每个质数$p$，统计$\sum_{k=1}^{∞} cnt[p^k]$的合并技巧

```cpp
// 核心代码片段（Siyuan优化思路）
void sieve(int n) {
    for(int i=2; i<=n; ++i) {
        if(!flg[i]) p[++tot]=i;
        for(int j=1; j<=tot&&i*p[j]<=n; ++j) {
            flg[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
}
for(int i=1; i<=tot; ++i) {
    int x=p[i], num=0;
    for(int j=x; j<=mx; j+=x) // 跳跃式统计倍数
        num += cnt[j];
    ans = min(ans, n-num);
}
```

---

### **同类型题推荐**
1. [CF1350B] Orac and Models（质因数分解+DP）
2. [洛谷P1072] Hankson的趣味题（GCD与LCM的质因子分析）
3. [CF1514B] AND 0, Sum Big（位运算与质因数的结合）

---

### **可视化方案设计**
**像素化筛法演示**  
1. **初始状态**：  
   - 屏幕左侧为原始数组（像素块表示数值大小）  
   - 右侧为质数筛过程（黑色方块表示已筛除）

2. **动态过程**：  
   - 当前筛质数$p$时，其倍数位置闪烁黄光  
   - 统计到新数组中的倍数时，对应位置变绿  
   - 状态栏显示当前最优答案`min_remove`

3. **音效设计**：  
   - 发现更优解时播放`coin.wav`（马里奥金币音效）  
   - 筛完一个质数时播放`blip.wav`（短促电子音）

4. **交互控制**：  
   - 方向键控制筛法速度（←减速，→加速）  
   - 空格键暂停/继续  
   - 按R键重置演示

---

### **关键调试心得**
> 来自题解作者Acc_Robin的注释：  
> "最初直接统计每个质数的出现次数会重复计算，后来意识到需要合并相同质因子的指数，例如对12=2²×3¹，只需要统计质数2和3各一次"

这一调试过程揭示了一个关键点：质因数分解时需要去重处理，避免同一个数的多个相同质因子被重复统计。这直接影响最终结果的正确性。

---
处理用时：67.80秒