# 题目信息

# Balanced Substring

## 题目描述

You are given a string $ s $ consisting only of characters 0 and 1. A substring $ [l,r] $ of $ s $ is a string $ s_{l}s_{l+1}s_{l+2}...\ s_{r} $ , and its length equals to $ r-l+1 $ . A substring is called balanced if the number of zeroes (0) equals to the number of ones in this substring.

You have to determine the length of the longest balanced substring of $ s $ .

## 说明/提示

In the first example you can choose the substring $ [3,6] $ . It is balanced, and its length is $ 4 $ . Choosing the substring $ [2,5] $ is also possible.

In the second example it's impossible to find a non-empty balanced substring.

## 样例 #1

### 输入

```
8
11010111
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
111
```

### 输出

```
0
```

# AI分析结果



---

## 唯一算法分类  
**前缀和 + 哈希优化**

---

## 综合分析与结论  
### 核心思路  
所有题解均采用以下核心逻辑：  
1. **权值转换**：将字符 '0' 视为 -1，'1' 视为 1  
2. **前缀和数组**：计算每个位置的前缀和 $sum[i]$  
3. **哈希映射**：记录每个前缀和值第一次出现的位置  
4. **最大跨度**：遍历时若 $sum[r] = sum[l-1]$，则区间 $[l,r]$ 为平衡子串  

### 关键难点与解决方案  
| 难点                | 解决方案                                      |
|---------------------|---------------------------------------------|
| 负数索引处理        | 前缀和整体偏移 +n 或大常数（如 1e5）         |
| 首次位置记录        | 用数组替代 STL map，时间优化至 O(1)           |
| 前缀和为0的特殊情况 | 初始位置 sum[0]=0，并记录其位置为0           |

### 可视化设计  
**动画方案**：  
1. **网格绘制**：横向展示字符串，每个字符下方动态更新前缀和  
2. **颜色标记**：  
   - 红色：当前处理的字符  
   - 蓝色：前缀和首次出现的位置  
   - 绿色：当前最长平衡子串  
3. **步进控制**：单步展示前缀和计算、哈希表更新、答案比较过程  
4. **复古像素风格**：  
   - 用 8-bit 像素块表示字符和前缀和值  
   - 音效设计：计算前缀和时播放 "beep"，找到更长解时播放 "coin" 音效  

---

## 题解清单 (≥4星)  
### 1. zhengrunzhe (★★★★★)  
**关键亮点**：  
- 用数组替代哈希表，时间空间双重优化  
- 循环中合并前缀和计算与答案更新，代码极简  
- 偏移处理巧妙（sum[i]+n），避免负数  

### 2. ynxynx (★★★★☆)  
**关键亮点**：  
- 代码结构与 zhengrunzhe 类似，但注释更详细  
- 明确强调「加n是为了避免负数」的偏移原理  

### 3. yeshubo_qwq (★★★★☆)  
**关键亮点**：  
- 压缩循环至单层，变量命名更简洁  
- 特殊处理 sum=0 的情况（i-a[0] = i+1）  

---

## 最优思路提炼  
### 核心代码片段  
```cpp
int sum[N], first[2*N]; // 前缀和与首次位置记录数组
for(int i=1; i<=n; i++){
    sum[i] = sum[i-1] + (s[i]=='1' ? 1 : -1);
    if(first[sum[i]+n]) 
        ans = max(ans, i - first[sum[i]+n]);
    else 
        first[sum[i]+n] = i;
}
```

### 技巧总结  
1. **偏移量选择**：前缀和范围 [-n, n]，偏移量取 n 保证非负  
2. **滚动更新**：在计算前缀和的同时更新首次出现位置，单次遍历完成  
3. **空间换时间**：用固定大小数组代替动态哈希表，访问速度更快  

---

## 同类题目推荐  
1. **洛谷 P1115** - 最大子段和（前缀和基础应用）  
2. **洛谷 P3406** - 海底高铁（差分与前缀和结合）  
3. **LeetCode 560** - 和为K的子数组（哈希表优化前缀和）  

---

## 个人心得摘录  
> "为什么要用map啊，还带个log。前缀和范围在[-n,n]之间，桶开成数组+n就好了" —— zhengrunzhe  
> 调试中发现哈希表访问速度成为瓶颈，改用数组后效率显著提升  

---

## 可视化实现片段（复古像素风格）  
```javascript
// Canvas 绘制前缀和网格
function drawGrid(ctx, sumArray) {
  const colors = ["#FF6B6B", "#4ECDC4", "#45B7D1"];
  sumArray.forEach((sum, idx) => {
    ctx.fillStyle = colors[(sum + 10) % 3]; // 8-bit 三色调色板
    ctx.fillRect(idx * 30, 100, 25, 25);   // 绘制前缀和方块
  });
}

// 音效触发
function playSound(type) {
  const sounds = {
    update: new Audio('data:audio/wav;base64,UklGRl...'), // 短促哔声
    found: new Audio('data:audio/wav;base64,UklGRl...')  // 上扬音效
  };
  sounds[type].play();
}
```

---
处理用时：64.79秒