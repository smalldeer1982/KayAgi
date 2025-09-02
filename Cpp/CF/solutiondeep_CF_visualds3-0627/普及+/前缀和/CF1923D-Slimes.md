# 题目信息

# Slimes

## 题目描述

There are $ n $ slimes placed in a line. The slimes are numbered from $ 1 $ to $ n $ in order from left to right. The size of the $ i $ -th slime is $ a_i $ .

Every second, the following happens: exactly one slime eats one of its neighbors and increases its size by the eaten neighbor's size. A slime can eat its neighbor only if it is strictly bigger than this neighbor. If there is no slime which is strictly bigger than one of its neighbors, the process ends.

For example, suppose $ n = 5 $ , $ a = [2, 2, 3, 1, 4] $ . The process can go as follows:

- first, the $ 3 $ -rd slime eats the $ 2 $ -nd slime. The size of the $ 3 $ -rd slime becomes $ 5 $ , the $ 2 $ -nd slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 1 $ -st slime (they are neighbors since the $ 2 $ -nd slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 7 $ , the $ 1 $ -st slime is eaten.
- then, the $ 5 $ -th slime eats the $ 4 $ -th slime. The size of the $ 5 $ -th slime becomes $ 5 $ , the $ 4 $ -th slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 5 $ -th slime (they are neighbors since the $ 4 $ -th slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 12 $ , the $ 5 $ -th slime is eaten.

For each slime, calculate the minimum number of seconds it takes for this slime to be eaten by another slime (among all possible ways the process can go), or report that it is impossible.

## 样例 #1

### 输入

```
4
4
3 2 4 2
3
1 2 3
5
2 2 3 1 1
7
4 2 3 6 1 1 8```

### 输出

```
2 1 2 1 
1 1 -1 
2 1 -1 1 2 
2 1 1 3 1 1 4```

# AI分析结果



## 唯一算法分类
贪心、二分查找、前缀和

---

## 题解思路与算法要点

### 核心思路
1. **预处理连续相同段**：计算每个位置i左边和右边连续相同元素的长度（l[i]、r[i]），用于判断区间是否可合并。
2. **前缀和优化**：通过前缀和快速判断左侧区间总和是否足够大，通过二分查找确定最短有效区间。
3. **双向判断**：对每个史莱姆分别处理左右两个方向的合并可能性，取最小值作为答案。
4. **特判相邻**：若相邻史莱姆直接可吃（a[i-1]>a[i]或a[i+1]>a[i]），直接返回1。

### 解决难点
- **区间有效性判断**：通过预处理l[i]、r[i]快速判断区间是否全相同（若全相同则无法合并）。
- **二分边界处理**：在保证区间总和足够大的前提下，通过单调性二分查找最短有效区间。
- **时间复杂度控制**：通过O(n)预处理和O(n log n)的二分操作，确保算法在3e5数据量下高效运行。

---

## 题解评分（≥4星）

1. **Luzhuoyuan（5星）**  
   - 思路清晰，代码简洁高效  
   - 使用l/r数组预处理连续相同段，结合前缀和二分  
   - 完整处理了左右双向及特判情况  
   - [代码链接](https://codeforces.com/contest/1923/submission/249013194)

2. **AtomAlpaca（4星）**  
   - 使用ST表判断区间是否全相同  
   - 二分思路明确，代码可读性较高  
   - [代码链接](https://codeforces.com/contest/1923/submission/247984795)

3. **kczw（4星）**  
   - 利用相邻差绝对值前缀和判断区间全同  
   - 二分逻辑完整，处理了左右双向情况  
   - [代码链接](https://codeforces.com/contest/1923/submission/249013194)

---

## 最优思路提炼

1. **预处理连续段**  
   计算每个位置i的左边连续相同元素长度l[i]和右边长度r[i]：
   ```cpp
   l[i] = (a[i]==a[i-1] ? l[i-1]+1 : 1)
   r[i] = (a[i]==a[i+1] ? r[i+1]+1 : 1)
   ```

2. **双向二分查找**  
   对每个i分别处理左右两个方向：
   ```cpp
   // 处理左方向
   if (pr[i-1] > a[i] && l[i-1] < i-1) 
      二分查找左边界j，使得sum[j..i-1] > a[i]
      ans = min(ans, i-j)
   // 处理右方向同理
   ```

3. **前缀和优化**  
   预处理前缀和数组pr/su：
   ```cpp
   pr[i] = pr[i-1] + a[i]  // 前缀和
   su[i] = su[i+1] + a[i]  // 后缀和
   ```

4. **特判相邻直接可吃**  
   ```cpp
   if (a[i-1] > a[i] || a[i+1] > a[i]) ans = 1;
   ```

---

## 同类型题推荐

1. **CF1927D**  
   查找区间是否存在不同元素，类似预处理思想  
   [题目链接](https://codeforces.com/contest/1927/problem/D)

2. **P1886 滑动窗口**  
   单调队列维护区间极值，类似区间处理思想  
   [题目链接](https://www.luogu.com.cn/problem/P1886)

3. **P3143 连续子序列**  
   前缀和与二分结合的经典问题  
   [题目链接](https://www.luogu.com.cn/problem/P3143)

---

## 代码片段（核心逻辑）

```cpp
// 预处理连续相同段
for(int i=1;i<=n;i++) 
    l[i] = (a[i]==a[i-1] ? l[i-1]+1 : 1);
for(int i=n;i>=1;i--)
    r[i] = (a[i]==a[i+1] ? r[i+1]+1 : 1);

// 处理每个史莱姆
for(int i=1;i<=n;i++){
    int ans = INF;
    // 特判相邻
    if(a[i-1]>a[i] || a[i+1]>a[i]) ans=1;
    // 处理左方向
    if(pr[i-1] > a[i] && l[i-1] < i-1){
        int j = lower_bound(pr+1, pr+n+1, pr[i]+a[i]) - pr;
        ans = min(ans, i-j);
    }
    // 处理右方向同理
    // ...
    printf("%d ", ans==INF ? -1 : ans);
}
```

---

## 可视化设计

### 动画方案
1. **像素风格布局**  
   - 每个史莱姆用16x16像素方块表示，颜色根据大小渐变  
   - 当前处理史莱姆高亮黄色边框

2. **合并过程演示**  
   - 左侧合并：蓝色箭头从左边界滑向当前史莱姆，合并区域闪烁  
   - 右侧合并：红色箭头从右边界滑向当前史莱姆

3. **二分过程可视化**  
   - 左右指针用绿色/红色竖线标记，随二分过程移动  
   - 有效区间用半透明颜色覆盖

4. **音效设计**  
   - 有效合并：8-bit上升音效（100Hz方波）  
   - 无效区间：低沉提示音（50Hz三角波）  
   - 找到解时播放胜利音效

### 交互功能
- **速度控制**：滑块调节动画速度（0.5x~4x）  
- **单步执行**：空格键逐帧观察二分过程  
- **自动演示**：AI模式自动遍历所有史莱姆处理流程

---

## 个人心得

**调试陷阱**：  
- 必须严格判断区间是否全相同，否则会错误计算有效区间  
- 前缀和数组要使用long long类型防止溢出

**优化技巧**：  
- 预处理连续段比实时计算更高效  
- 反向二分时注意单调性方向（后缀和需降序处理）

**思维突破**：  
- 将合并过程抽象为区间有效性判断，避免模拟具体合并步骤  
- 利用数学性质（区间总和+元素差异）替代物理合并过程

---
处理用时：133.55秒