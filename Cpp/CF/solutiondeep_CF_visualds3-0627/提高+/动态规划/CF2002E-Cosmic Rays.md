# 题目信息

# Cosmic Rays

## 题目描述

Given an array of integers $ s_1, s_2, \ldots, s_l $ , every second, cosmic rays will cause all $ s_i $ such that $ i=1 $ or $ s_i\neq s_{i-1} $ to be deleted simultaneously, and the remaining parts will be concatenated together in order to form the new array $ s_1, s_2, \ldots, s_{l'} $ .

Define the strength of an array as the number of seconds it takes to become empty.

You are given an array of integers compressed in the form of $ n $ pairs that describe the array left to right. Each pair $ (a_i,b_i) $ represents $ a_i $ copies of $ b_i $ , i.e. $ \underbrace{b_i,b_i,\cdots,b_i}_{a_i\textrm{ times}} $ .

For each $ i=1,2,\dots,n $ , please find the strength of the sequence described by the first $ i $ pairs.

## 说明/提示

In the first test case, for the prefix of length $ 4 $ , the changes will be $ [0,0,1,0,0,0,1,1,1,1,1]\rightarrow[0,0,0,1,1,1,1]\rightarrow[0,0,1,1,1]\rightarrow[0,1,1]\rightarrow[1]\rightarrow[] $ , so the array becomes empty after $ 5 $ seconds.

In the second test case, for the prefix of length $ 4 $ , the changes will be $ [6,6,6,6,3,6,6,6,6,0,0,0,0]\rightarrow[6,6,6,6,6,6,0,0,0]\rightarrow[6,6,6,6,6,0,0]\rightarrow[6,6,6,6,0]\rightarrow[6,6,6]\rightarrow[6,6]\rightarrow[6]\rightarrow[] $ , so the array becomes empty after $ 7 $ seconds.

## 样例 #1

### 输入

```
4
4
2 0
1 1
3 0
5 1
6
4 6
1 3
4 6
4 0
7 6
6 3
7
9 0
7 1
5 0
7 1
9 0
1 1
2 0
10
10 7
4 9
2 2
7 9
2 8
8 5
11 7
15 5
12 7
4 0```

### 输出

```
2 2 4 5 
4 4 7 7 10 10 
9 9 9 9 9 9 10 
10 10 10 10 10 10 12 15 15 15```

# AI分析结果



0. **题目翻译**  
# 宇宙射线

## 题目描述

给定整数数组 $ s_1, s_2, \ldots, s_l $ ，每秒会同时删除所有满足 $ i=1 $ 或 $ s_i\neq s_{i-1} $ 的 $ s_i $，剩余部分按序拼接形成新数组 $ s_1, s_2, \ldots, s_{l'} $ 。

定义数组的强度为变为空数组所需的秒数。

现给定按左到右顺序压缩描述的数组，包含 $ n $ 对数。每对 $ (a_i,b_i) $ 表示 $ a_i $ 个 $ b_i $，即 $ \underbrace{b_i,b_i,\cdots,b_i}_{a_i\textrm{ 次}} $ 。

对每个 $ i=1,2,\dots,n $，求由前 $ i $ 对描述的数组的强度。

## 说明/提示

第一个测试样例中，前4对的数组变化为：
$ [0,0,1,0,0,0,1,1,1,1,1]\rightarrow[0,0,0,1,1,1,1]\rightarrow[0,0,1,1,1]\rightarrow[0,1,1]\rightarrow[1]\rightarrow[] $，
故强度为5秒。

第二个测试样例中，前4对的变化为：
$ [6,6,6,6,3,6,6,6,6,0,0,0,0]\rightarrow[6,6,6,6,6,6,0,0,0]\rightarrow[6,6,6,6,6,0,0]\rightarrow[6,6,6,6,0]\rightarrow[6,6,6]\rightarrow[6,6]\rightarrow[6]\rightarrow[] $，
故强度为7秒。

---

1. **唯一算法分类**  
无算法分类

---

2. **综合分析与结论**  
### 核心思路  
通过维护**单调递减栈**处理连续段的合并逻辑：  
1. 新加入段 $(a_i,b_i)$ 时，弹出所有栈顶比它小的段  
2. 若弹出过程中发现**同色相邻段**，合并其有效长度  
3. 最终栈底元素即为当前数组强度  

### 解决难点  
- **同色段合并条件**：当中间段全部被弹出后，前后同色段才能合并  
- **有效长度计算**：合并后的长度需减去中间段的影响  
- **时间复杂度控制**：单调栈保证 $O(n)$ 复杂度  

### 可视化设计  
- **8位像素风格**：用不同颜色方块表示栈中元素，弹出时播放爆炸粒子特效  
- **合并动画**：同色方块合并时显示数值累加过程  
- **音效触发**：  
  - 弹出段时播放短促电子音  
  - 合并段时播放合成器滑音  
- **自动演示**：模拟射线逐秒消减过程，右侧显示当前栈结构  

---

3. **题解清单**  
✅ **int08（5星）**  
- 代码简洁，维护栈时巧妙处理合并逻辑  
- 时间复杂度严格 $O(n)$  
- 核心代码仅需15行  

✅ **chlchl（4星）**  
- 独立推导出合并条件  
- 函数封装清晰，变量命名规范  

---

4. **代码实现**  
```cpp
// int08 题解核心代码
while(pt>0 && sta[pt].first<=a[i]) {
    if(sta[pt-1].second == b[i]) 
        a[i] += sta[pt-1].first - sta[pt].first;
    pt--;
}
sta[++pt] = {a[i], b[i]};
cout << sta[1].first << " ";
```

---

5. **同类型题推荐**  
1. P1901 最大矩形面积（单调栈经典问题）  
2. P7167 [eJOI2020] Fountain（带权值处理的栈操作）  
3. P5788 【模板】单调栈  

---

6. **可视化演示逻辑**  
```javascript
// 伪代码示例：合并动画实现
function mergeAnimation(stack, newBlock) {
    while(stack.top().a <= newBlock.a) {
        let top = stack.pop();
        playSound("pop.wav");
        if(stack.top().color == newBlock.color) {
            let mergeValue = newBlock.a + (stack[stack.length-2].a - top.a);
            animateMerge(stack.top(), newBlock, mergeValue);
            stack.pop();
        }
    }
    stack.push(newBlock);
    highlightBottom(stack);
}
```

---

7. **个人心得**  
> "被 $2300$ 击杀了" —— tzl_Dedicatus545  
> 解题关键点在于发现**中间段必须严格小于两端**才能合并，这个条件需要反复推敲样例才能理解透彻

---
处理用时：75.19秒