# 题目信息

# [USACO11NOV] Above the Median G

## 题目描述

Farmer John has lined up his N (1 <= N <= 100,000) cows in a row to measure their heights; cow i has height H\_i (1 <= H\_i <= 1,000,000,000) nanometers--FJ believes in precise measurements! He wants to take a picture of some contiguous subsequence of the cows to submit to a bovine photography contest at the county fair.

The fair has a very strange rule about all submitted photos: a photograph is only valid to submit if it depicts a group of cows whose median height is at least a certain threshold X (1 <= X <= 1,000,000,000).

For purposes of this problem, we define the median of an array A[0...K] to be A[ceiling(K/2)] after A is sorted, where ceiling(K/2) gives K/2 rounded up to the nearest integer (or K/2 itself, it K/2 is an integer to begin with). For example the median of {7, 3, 2, 6} is 6, and the median of {5, 4, 8} is 5.

Please help FJ count the number of different contiguous subsequences of his cows that he could potentially submit to the photography contest.

给出一串数字，问中位数大于等于X的连续子串有几个。（这里如果有偶数个数，定义为偏大的那一个而非中间取平均）


## 说明/提示

FJ's four cows have heights 10, 5, 6, 2. We want to know how many contiguous subsequences have median at least 6.


There are 10 possible contiguous subsequences to consider. Of these, only 7 have median at least 6. They are {10}, {6}, {10, 5}, {5, 6}, {6, 2}, {10, 5, 6}, {10, 5, 6, 2}.


## 样例 #1

### 输入

```
4 6 
10 
5 
6 
2 
```

### 输出

```
7 
```

# AI分析结果


### 💡 Kay的C++算法解析：Above the Median G 深入学习指南 💡

#### 题目解读与核心算法识别
✨ **本题主要考察**：`前缀和与逆序对技巧应用`  
🗣️ **初步分析**：
> 解决中位数问题就像在迷宫中寻找宝藏——需要将复杂条件转化为可计算的路径。核心思路：  
> - 将≥X的值映射为1，<X的值映射为-1，使中位数条件转化为**子段和非负**  
> - 通过前缀和数组记录路径高度（`sum[i] = sum[i-1] + (a[i]≥X ? 1 : -1)`）  
> - 问题最终转化为：统计满足`0≤l<r≤n`且`sum[r]≥sum[l]`的区间数量（正序对计数）  

**可视化设计思路**：  
- **像素迷宫探险**：用绿色像素块(■)表示1，红色(□)表示-1，上方显示前缀和折线图  
- **关键动画**：当前元素高亮黄色闪烁；`sum[i]`变化时播放"叮"音效；正序对匹配时触发蓝色闪光  
- **复古UI**：FC风格控制面板，含速度滑块/单步按钮，胜利时播放8-bit胜利音乐

---

#### 精选优质题解参考
**题解一（封禁用户）**  
* **点评**：  
  创新性地利用`|sum[i]-sum[i-1]|=1`的性质，用计数数组`b[]`代替树状数组，实现**O(n)时间复杂度**。代码简洁高效（仅15行），核心变量`t`动态维护正序对增量，边界处理严谨（`a[0]=n`避免负下标）。空间优化到200kB内，竞赛适用性强。

**题解二（关怀他人）**  
* **点评**：  
  树状数组解法典范，通过`2*dp[i]-i`构造新序列解决离散化问题。代码模块化优秀：  
  - `lowbit()/add()/sum()`函数封装清晰  
  - 偏移量`n+1`巧妙处理负值（`pre[i]+n+1`）  
  - 输入/处理/输出逻辑分离，易扩展性高

**题解三（BlueRose73）**  
* **点评**：  
  对O(n)方法给出**最详细推导注释**，揭示`pre`变量的动态维护本质：  
  ```math
  pre_i = pre_{i-1} + 
  \begin{cases} 
    num[sum_i] + 1 & \text{if } sum_i > sum_{i-1} \\
    -(num[sum_{i-1}] - 1) & \text{otherwise}
  \end{cases}
  ```
  学习价值突出，特别适合理解递推关系本质。

---

#### 核心难点辨析与解题策略
1. **难点：中位数条件转化**  
   *分析*：传统排序法O(n² log n)超时。优质解通过`1/-1`映射将中位数≥X ⇨ 子段和≥0 ⇨ `sum[r]≥sum[l]`，建立问题等价关系  
   💡 **学习笔记**：复杂条件可转化为可计算代数关系

2. **难点：高效统计区间关系**  
   *分析*：正序对计数需O(n²)。两种优化方案：  
   - **树状数组**：离散化`sum`值，`add(sum_l)`后`query(sum_r)`（关怀他人/ycyaw解法）  
   - **线性计数**：利用相邻`sum`差±1特性，动态维护`num[]`数组（封禁用户/BlueRose73解法）  
   💡 **学习笔记**：相邻状态变化为常数时，可优化空间

3. **难点：边界与偏移处理**  
   *分析*：`sum[0]=0`必须计入（徐晨轩解法漏此WA）；负值处理需偏移：  
   ```cpp
   // 树状数组解法偏移示例
   add(sum[i] + MAXN); // MAXN=2*n+1
   ```
   💡 **学习笔记**：前缀和问题始终考虑`sum[0]`，负值用偏移而非绝对值

✨ **解题技巧总结**  
- **问题转化**：中位数→01映射→前缀和→正序对  
- **数据结构选择**：  
  `n≤10⁵`优先树状数组，若`|sum变化|=1`可用线性计数  
- **边界防御**：`sum[0]`显式初始化，测试`n=0/1`边界  
- **空间优化**：滚动变量替代完整前缀和数组

---

#### C++核心代码实现赏析
**通用核心实现（线性计数法）**  
```cpp
#include<cstdio>
const int MAXN=200000;
long long n,x,ans,sum[MAXN],cnt[2*MAXN];

int main(){
    scanf("%lld%lld",&n,&x);
    cnt[n] = 1; // sum[0] = 0 → 对应索引n
    for(int i=1,t; i<=n; i++){
        scanf("%d",&t);
        sum[i] = sum[i-1] + (t>=x ? 1 : -1);
        // 动态维护正序对增量
        if(sum[i] > sum[i-1]) 
            ans += cnt[sum[i]] + cnt[sum[i]-1];
        else 
            ans += cnt[sum[i]] + cnt[sum[i]+1];
        cnt[sum[i] + n]++; // 偏移防负
    }
    printf("%lld",ans);
}
```
* **代码解读概要**：  
  - `cnt[]`数组记录各前缀和出现次数（索引=sum+n）  
  - 当`sum[i]`上升时，可匹配`sum[i]`和`sum[i]-1`的历史值  
  - 下降时匹配`sum[i]`和`sum[i]+1`，避免重复计数  

**题解一（封禁用户）片段**  
```cpp
if(a[i]>a[i-1]) t -= b[a[i]];
else t += b[a[i-1]];
b[a[i]]++;
ans += t;
```
* **亮点**：用`t`动态维护增量，避免全量重算  
* **解读**：  
  > 当`a[i]`上升（当前`sum`变大）：  
  > - 可匹配的`l`减少`b[a[i]]`（因严格大于的历史值不再匹配）  
  > 下降时同理，`b[a[i-1]]`包含需排除的历史值  
* 💡 **学习笔记**：增量法减少重复计算

**题解二（关怀他人）片段**  
```cpp
add(pre[i] + n + 1, 1);
ans += sum(pre[i] + n + 1);
```
* **亮点**：树状数组封装清晰，偏移处理优雅  
* **解读**：  
  > `pre[i]+n+1`将值域映射到[1,2n+1]  
  > `add()`插入当前前缀和，`sum()`查询≤当前值的历史数量  
* 💡 **学习笔记**：树状数组适合动态前缀统计

---

### 算法可视化：像素动画演示  
**主题**：`像素迷宫探险家`  
**核心流程**：  
1. **场景初始化**（8-bit风格）：
   - 顶部：前缀和折线图（Y轴范围[-n,n]）
   - 中部：数值条带（绿■=1，红□=-1）
   - 底部：计数数组`cnt[]`柱状图

2. **动态执行**：  
   ```mermaid
   graph LR
   A[扫描新元素] --> B{≥X？}
   B -->|是| C[绿块闪烁+1音效]
   B -->|否| D[红块闪烁-1音效]
   C/D --> E[更新折线图]
   E --> F[计算增量ans]
   F --> G[更新cnt[]柱状图]
   ```

3. **交互控制**：  
   - 单步模式：按空格逐步执行
   - 自动模式：速度滑块控制（0.5x~5x）
   - 高亮提示：当前匹配的`l`位置显示金色边框

4. **游戏化元素**：  
   - 每完成10%进度解锁新BGM段落
   - 正序对匹配时触发连击特效（Combo!）
   - 最终显示宝藏动画（ans值越大动画越华丽）

---

### 拓展练习与相似问题思考
1. **洛谷 P1908** 逆序对  
   → 巩固归并/树状数组求逆序对基础
2. **洛谷 P1719** 最大加权矩形  
   → 二维前缀和转化为最大子段和
3. **洛谷 P3406** 海底高铁  
   → 差分数组与前缀和的综合应用

---

### 学习心得与经验分享
> **BlueRose73的调试经验**：  
> *“最初未理解`pre`变量的动态维护本质，通过手工模拟n=3的案例才突破瓶颈”*  
> **Kay点评**：手工模拟小规模数据是理解递推关系的利器，建议学习时先测试n≤5的案例

---

本次分析展示了如何将抽象的中位数条件转化为可计算问题，并利用前缀和特性优化。记住：好算法=问题转化+数据结构选择+边界防御！下次见！💪

---
处理用时：133.65秒