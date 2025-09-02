# 题目信息

# Cutlet

## 题目描述

Arkady wants to have a dinner. He has just returned from a shop where he has bought a semifinished cutlet. He only needs to fry it. The cutlet should be fried for $ 2n $ seconds, in particular, it should be fried for $ n $ seconds on one side and $ n $ seconds on the other side. Arkady has already got a frying pan and turn on fire, but understood that maybe he won't be able to flip the cutlet exactly after $ n $ seconds after the beginning of cooking.

Arkady is too busy with sorting sticker packs in his favorite messenger and can flip the cutlet only in some periods of time. Namely, there are $ k $ periods of time in which he can do it, the $ i $ -th of them is an interval of time from $ l_{i} $ seconds after he starts cooking till $ r_{i} $ seconds, inclusive. Arkady decided that it's not required to flip the cutlet exactly in the middle of cooking, instead, he will flip it several times in such a way that the cutlet will be fried exactly $ n $ seconds on one side and $ n $ seconds on the other side in total.

Help Arkady and find out if it's possible for him to cook the cutlet, if he is able to flip the cutlet only in given periods of time; and if yes, find the minimum number of flips he needs to cook the cutlet.

## 说明/提示

In the first example Arkady should flip the cutlet in time moment $ 3 $ seconds after he starts cooking and in time moment $ 13 $ seconds after he starts cooking.

In the second example, Arkady can flip the cutlet at $ 10 $ seconds after he starts cooking.

## 样例 #1

### 输入

```
10 2
3 5
11 13
```

### 输出

```
Full
2
```

## 样例 #2

### 输入

```
10 3
3 5
9 10
11 13
```

### 输出

```
Full
1
```

## 样例 #3

### 输入

```
20 1
3 19
```

### 输出

```
Hungry
```

# AI分析结果



## 算法分类
动态规划（DP）结合单调队列优化

---

## 综合分析与结论
### 核心思路与难点
- **问题建模**：将煎牛排过程抽象为动态规划问题，状态定义为处理到第i个区间时，未被烤的那面煎了j秒的最小翻转次数。
- **转移分析**：在每个可翻转区间内，最多翻转两次（奇数次可简化为1次，偶数次可简化为0或2次），需分别处理这两种情况的转移方程。
- **优化关键**：使用单调队列维护转移窗口中的最小值，将单次转移复杂度从O(n)降为O(1)，最终总复杂度为O(nk)。

### 核心算法流程
1. **状态定义**：`dp[i][j]`表示处理完前i个区间后，未被烤的面累计煎了j秒。
2. **翻转0次**：直接继承上一区间的状态。
3. **翻转1次**：倒序遍历j，维护单调队列窗口`[l_i-j, r_i-j]`的最小值。
4. **翻转2次**：正序遍历j，维护单调队列窗口`[j-(r_i-l_i), j]`的最小值。

### 可视化设计
- **像素动画**：用不同颜色块表示DP状态值，红色表示不可达，绿色表示最优值。
- **队列滑动**：动态显示单调队列的入队、出队过程，高亮当前处理的j值。
- **音效提示**：翻转时播放“哔”声，队列操作时添加轻微点击声，找到解时播放胜利音效。
- **复古界面**：采用8-bit风格，用网格展示DP数组，右侧显示当前处理的区间范围和队列状态。

---

## 题解清单（≥4星）
1. **Kelin（5星）**  
   - 关键亮点：清晰的状态转移推导，高效利用滚动数组和双单调队列优化。

2. **yc20170111（4.5星）**  
   - 关键亮点：详细的状态转移图示，代码可读性强，注释明确。

3. **leozhang（4星）**  
   - 关键亮点：深入分析翻转次数对状态的影响，代码结构简洁。

---

## 最优思路提炼
### 核心技巧
1. **状态压缩**：使用滚动数组（`dp[2][N]`）优化空间。
2. **单调队列应用**：正序处理翻转两次的转移，倒序处理翻转一次的转移。
3. **窗口维护**：通过队列头尾指针动态维护区间最小值，避免重复计算。

### 关键代码片段
```cpp
// 处理翻转2次的情况（正序）
for(int j=0; j<=min(n, r); j++){
    while(h<=t && q[h] < j - (r-l)) h++;
    while(h<=t && f_prev[j] <= f_prev[q[t]]) t--;
    q[++t] = j;
    f_current[j] = min(f_current[j], f_prev[q[h]] + 2);
}

// 处理翻转1次的情况（倒序）
for(int j=r; j>=0; j--){
    while(h<=t && q[h] < l - j) h++;
    while(h<=t && f_prev[r-j] <= f_prev[q[t]]) t--;
    q[++t] = r - j;
    f_current[j] = min(f_current[j], f_prev[q[h]] + 1);
}
```

---

## 类似题目推荐
1. **P1725 琪露诺** - 单调队列优化DP  
2. **P3957 跳房子** - 二分答案+单调队列  
3. **CF372C Watching Fireworks is Fun** - 滑动窗口优化DP

---

## 可视化实现方案
### 动画流程
1. **初始化**：绘制N×K的网格表示DP数组，初始化第一列（区间0）的状态。
2. **区间处理**：
   - **步骤1**：显示当前处理的区间`[l_i, r_i]`，高亮黄色边框。
   - **步骤2**：正序遍历j处理翻转两次，用蓝色方块表示当前j，绿色方块表示队列中的候选值。
   - **步骤3**：倒序遍历j处理翻转一次，用红色方块表示当前j，紫色方块表示候选值。
3. **音效触发**：每次队列插入/删除时播放“滴”声，状态更新时播放“嗒”声。

### 复古风格设计
- **调色板**：使用NES经典的8色调色板（黑、白、红、蓝、绿、黄、紫、青）。
- **像素字体**：采用8×8像素字体显示状态数值。
- **背景音乐**：循环播放《超级马里奥》地下关BGM的8-bit改编版。

---

## 完整代码（Kelin题解）
```cpp
#include<bits/stdc++.h>
#define fp(i,a,b) for(int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(int i=a,I=b-1;i>I;--i)
using namespace std;
const int N=2e5+5,inf=1e9;
int n,k,p,l,r,h,t,f[2][N],q[N];
int main(){
    scanf("%d%d",&n,&k);
    memset(f[0],0x3f,sizeof f[0]); f[0][0]=0;
    while(k--){
        scanf("%d%d",&l,&r); p^=1;
        memcpy(f[p],f[p^1],sizeof f[p]);
        h=1,t=0; // 处理翻转两次
        fp(j,0,min(n,r)){
            while(h<=t&&f[p^1][j]<=f[p^1][q[t]])--t;
            while(h<=t&&q[h]<j-(r-l))++h;
            q[++t]=j;
            f[p][j]=min(f[p][j],f[p^1][q[h]]+2);
        }
        h=1,t=0; // 处理翻转一次
        fd(j,r,0){
            while(h<=t&&f[p^1][r-j]<=f[p^1][q[t]])--t;
            while(h<=t&&q[h]<l-j)++h;
            q[++t]=r-j;
            f[p][j]=min(f[p][j],f[p^1][q[h]]+1);
        }
    }
    f[p][n]<inf?printf("Full\n%d",f[p][n]):puts("Hungry");
    return 0;
}
```

---
处理用时：74.35秒