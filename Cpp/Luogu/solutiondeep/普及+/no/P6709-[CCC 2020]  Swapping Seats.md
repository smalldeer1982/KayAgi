# 题目信息

# [CCC 2020]  Swapping Seats

## 题目描述

有 $N$ 个人坐在一张**圆**桌旁。

共有三个派别，每一个人属于一个派别。

现在，您想使属于同一派别的人坐到一起。

您可以每次将两个人交换位置，输出最小的交换次数。

## 说明/提示

#### 样例解释
$\texttt{BABCBCACCA}\to\texttt{AABCBCBCCA}\to\texttt{AABBBCCCCA}$。

#### 子任务
**本题采用捆绑测试，且本题的 Subtask 分数有微调。**
- Subtask 1（$26$ 分）：$s_i\in\{$`A`$,$`B`$\}$ 且 $N\le 5\times 10^3$。
- Subtask 2（$27$ 分）：$s_i\in\{$`A`$,$`B`$\}$。
- Subtask 3（$27$ 分）：$N\le 5\times 10^3$。
- Subtask 4（$20$ 分）：无特殊限制。

对于 $100\%$ 的数据，保证 $s_i\in\{$`A`$,$`B`$,$`C`$\}$，$1\le N\le 10^6$。

#### 说明
本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/resources/past-contests?contest_category=29) [2020 Senior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/seniorEF.pdf) T4 Swapping Seats。

## 样例 #1

### 输入

```
BABCBCACCA```

### 输出

```
2```

# AI分析结果



**算法分类**: 贪心、前缀和

**综合分析与结论**  
本题需在环形序列中找到使同派相邻的最小交换次数。各题解核心思路一致：破环成链，枚举所有可能的起始位置及排列顺序（如ABC或ACB），利用前缀和统计各区间的字符数量，通过贪心策略优先交换交叉字符对以减少次数。关键在于处理环形枚举和高效统计错误字符数。

**精选题解**  
1. **题解作者：gznpp**（4星）  
   - **亮点**: 推导交换次数公式，利用前缀和优化统计，代码简洁高效。  
   - **关键思路**: 将环形拆为链，枚举A的起始位置，分两种情况（A后接B或C），计算非目标字符数并优化交换次数。  
   ```cpp
   // 核心代码片段
   for (int i = 1; i <= n; ++i) { 
       int nx1 = i + suma, nx2;
       // B next
       nx2 = nx1 + sumb;
       ans = min(ans, max(sb[nx1-1] - sb[i-1], sa[nx2-1] - sa[nx1-1]) + sumc - sc[i + n -1] + sc[nx2 -1]);
       // C next
       nx2 = nx1 + sumc;
       ans = min(ans, max(sc[nx1-1] - sc[i-1], sa[nx2-1] - sa[nx1-1]) + sumb - sb[i + n -1] + sb[nx2 -1]);
   }
   ```

2. **题解作者：Y_ATM_K**（4星）  
   - **亮点**: 直接枚举排列顺序，利用宏定义简化前缀和计算，代码可读性强。  
   - **关键思路**: 枚举A的起始点，计算每个分区的错误字符数，通过贪心交换减少无效操作。  
   ```cpp
   // 核心代码片段
   #define calc(l,r,x) (sum[r][x]-sum[l-1][x])
   for (int i=1;i<=n;++i) {
       int s1=B(i,i+sa[n]-1), s3=A(i+sa[n],i+sa[n]+sb[n]-1);
       ans=min(ans, s1 + s2 + s4 + (s3>s1 ? s3-s1 :0));
   }
   ```

**最优技巧总结**  
- **破环成链**: 将字符串复制拼接处理循环性。  
- **前缀和优化**: 快速统计区间字符数量。  
- **贪心交换策略**: 优先处理交叉字符对（如A区中的B与B区中的A）以减少交换次数。  

**相似题目推荐**  
1. [P1459 三值的排序](https://www.luogu.com.cn/problem/P1459)  
2. [P1369 矩形](https://www.luogu.com.cn/problem/P1369)（前缀和统计）  
3. [CF1081D Maximum Distance](https://www.luogu.com.cn/problem/CF1081D)（贪心+环处理）

---
处理用时：57.20秒