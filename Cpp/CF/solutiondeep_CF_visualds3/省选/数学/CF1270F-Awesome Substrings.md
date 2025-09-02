# 题目信息

# Awesome Substrings

## 题目描述

Let's call a binary string $ s $ awesome, if it has at least $ 1 $ symbol 1 and length of the string is divisible by the number of 1 in it. In particular, 1, 1010, 111 are awesome, but 0, 110, 01010 aren't.

You are given a binary string $ s $ . Count the number of its awesome substrings.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

In the first sample, all substrings of $ s $ are awesome.

In the second sample, we have the following awesome substrings of $ s $ : 1 ( $ 2 $ times), 01 ( $ 2 $ times), 10 ( $ 2 $ times), 010 ( $ 2 $ times), 1010, 0101

In the third sample, no substring is awesome.

## 样例 #1

### 输入

```
111
```

### 输出

```
6
```

## 样例 #2

### 输入

```
01010
```

### 输出

```
10
```

## 样例 #3

### 输入

```
0000
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1111100000
```

### 输出

```
25
```

# AI分析结果


### 💡 Kay的C++算法解析：Awesome Substrings 深入学习指南 💡

#### **引言**
今天我们分析一道有趣的字符串计数问题：Awesome Substrings。题目要求统计二进制字符串中所有满足长度能被其中1的个数整除的子串数量。本指南将带你理解核心算法，掌握解题技巧，并通过像素动画直观感受算法执行过程。

---

### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`根号分治` + `前缀和技巧`

🗣️ **初步分析**：
> 解决本题的关键在于运用**根号分治**策略。想象你是一名仓库管理员：当货物量少时（k≤√n），直接分类统计（桶计数）；当货物量大但内容少时（k>√n），采用高效分区扫描（枚举1的个数）。这种策略完美平衡了效率！
> 
> **核心流程**：
> 1. **小k处理**：枚举k=1到√n，计算`f(i)=k*s_i-i`，用桶统计相同值的对数
> 2. **大k处理**：枚举左端点i和1的个数k，计算右端点区间，统计满足`长度>k*√n`的倍数
> 
> **可视化设计**：
> - 像素动画将展示两个场景：小k部分的"桶分类"（闪烁像素块入桶）和大k部分的"探险家扫描"（像素小人移动+区间高亮）
> - 关键步骤高亮：桶计数时相同值闪烁黄光，区间计算时倍数位置亮绿光
> - 复古音效：入桶"叮"声，匹配成功"噔"声，过关"胜利"旋律

---

### 2. 精选优质题解参考
从思路清晰度、代码规范性、算法优化度等维度，精选3份≥4星的优质题解：

**题解一（crashed）**
* **点评**：推导严谨完整，代码结构清晰（预处理nxt数组高效定位1的位置），桶计数边界处理规范（动态分配大数组防溢出）。亮点在于双指针维护区间时的边界处理技巧，实践参考价值高，可直接用于竞赛。

**题解二（xht）**
* **点评**：代码简洁高效（仅30行），使用vector智能清理非零桶提升性能。亮点在于用`vi p`动态记录非空桶位置避免全清空，算法优化巧妙。虽变量命名较简略，但核心逻辑突出。

**题解三（OIer_Eternity）**
* **点评**：创新赋值策略（1→k-1，0→-1）实现充要条件判断，题解描述详细易懂。亮点在于预处理pos数组快速定位1的位置，学习笔记部分对记忆化搜索的解释尤为清晰。

---

### 3. 核心难点辨析与解题策略
<difficulty_intro>
解决本题需突破三大核心难点：
</difficulty_intro>

1. **状态转换技巧**
   * **难点**：如何将子串条件转化为可计算形式？
   * **分析**：优质题解通过前缀和+等式变形（`k·s_i - i = k·s_j - j`），将问题转化为统计相同特征值对数
   * 💡 **学习笔记**：前缀和是子串计数问题的万能钥匙

2. **根号分治设计**
   * **难点**：如何选择阈值？为何分治策略有效？
   * **分析**：取T=√n使两阶段均衡：小k部分O(n√n)桶计数，大k部分O(n²/T)区间扫描
   * 💡 **学习笔记**：阈值选择是根号分治的灵魂

3. **重复计数规避**
   * **难点**：如何避免k≤T和k>T部分的重叠统计？
   * **分析**：在大k计算中限定`长度>k*T`（如`max(T+1, ceil(L_len/k))`）
   * 💡 **学习笔记**：边界处理是竞赛代码的生死线

#### ✨ 解题技巧总结
<summary_best_practices>
通用解题心法：
</summary_best_practices>
- **问题分解术**：将复杂条件拆解为`前缀和`+`整除关系`的数学模型
- **时空平衡术**：根号分治在O(n√n)复杂度下完美平衡时空
- **桶计数三诀**：①偏移防负 ②动态清空 ③vector记非零位
- **边界四必查**：全0串、n=1、偏移量、整数除法取整方向

---

### 4. C++核心代码实现赏析
<code_intro_overall>
通用实现融合多题解优点，完整解决框架：
</code_intro_overall>

**本题通用核心C++实现**
```cpp
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;
const int MAXN = 2e5+5, MAXT = 450; // T=√n

int s[MAXN], nxt[MAXN]; // s:前缀和, nxt:下一个1的位置
char S[MAXN];

int main() {
    scanf("%s", S+1);
    int N = strlen(S+1), T = sqrt(N);
    
    // 前缀和 & 特判全0
    for (int i=1; i<=N; i++) 
        s[i] = s[i-1] + (S[i]=='1');
    if (s[N] == 0) { puts("0"); return 0; }

    // 预处理nxt数组（核心优化点）
    nxt[N+1] = N+1;
    for (int i=N; i>=0; i--)
        nxt[i] = (S[i]=='1') ? i : nxt[i+1];

    LL ans = 0;
    // ===== 第一阶段：小k桶计数 =====
    int *buc = new int[MAXN*MAXT + 2*MAXN](); // 动态大数组防溢出
    for (int k=1; k<=T; k++) {
        for (int i=0; i<=N; i++) {
            int idx = k*s[i] - i + N; // 偏移防负
            buc[idx]++;
        }
        for (int i=0; i<=N; i++) {
            int idx = k*s[i] - i + N;
            if (buc[idx]) {
                ans += (LL)buc[idx] * (buc[idx]-1) / 2;
                buc[idx] = 0; // 手动清空桶
            }
        }
    }
    delete[] buc;

    // ===== 第二阶段：大k区间扫描 =====
    for (int i=0; i<N; i++) { // 枚举左端点
        int cur = nxt[i]; // 当前位置
        for (int k=1; k<=N/T && cur<=N; k++) {
            int nxt_pos = nxt[cur+1]; // 下一个1位置
            int L_len = cur - i;     // 最小长度
            int R_len = nxt_pos-1 - i; // 最大长度
            
            if (L_len <= R_len) {
                int t_min = max(T+1, (L_len+k-1)/k); // 关键去重！
                int t_max = R_len / k;
                if (t_min <= t_max) 
                    ans += t_max - t_min + 1;
            }
            cur = nxt_pos; // 跳至下一个1
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

**代码解读概要**：
> 1. **预处理**：`nxt`数组实现O(1)跳转1的位置，是性能关键
> 2. **第一阶段**：桶计数时采用`动态分配+偏移`处理负值，统计公式为组合数C(n,2)
> 3. **第二阶段**：`cur`指针高效扫描区间，`t_min=max(T+1,...)`确保不重复统计
> 4. **边界防护**：全0串特判、内存精确释放、整数除法取整

---
<code_intro_selected>
精选题解片段赏析：
</code_intro_selected>

**题解一（crashed）片段**
```cpp
nxt[N+1] = N+1;
for (int i=N; i>=0; i--)  // 逆向预处理技巧
    nxt[i] = (s[i]^s[i+1]) ? i+1 : nxt[i+1];
```
* **亮点**：位运算判断1的位置变化，减少分支预测
* **学习笔记**：逆向预处理是链式结构的常见优化

**题解二（xht）片段**
```cpp
vi p; // 动态记录非空桶位置
for (int i=0; i<=n; i++) 
    if (buc[x]) p.pb(x);
while (p.size()) 
    buc[p.back()]=0, p.pop_back();
```
* **亮点**：vector智能清理非零桶，避免O(n√n)全清
* **学习笔记**：容器记录有效位置是稀疏数据处理利器

**题解三（OIer_Eternity）片段**
```cpp
// 创新赋值法：1->k-1, 0->-1
sum[i] = sum[i-1] + (s[i]=='1' ? k-1 : -1);
if (sum[i]==0) ans++;  // 满足充要条件
```
* **亮点**：通过赋值转换，将整除条件转化为和为0
* **学习笔记**：问题等价转换可开辟新思路

---

### 5. 算法可视化：像素动画演示
<visualization_intro>
**像素探险家**带你直击根号分治核心！设计采用8位FC红白机风格，通过双场景演示算法本质：
</visualization_intro>

* **主题**：根号分治大冒险（小k桶分类 + 大k区间扫描）
* **核心演示**：
  ```mermaid
  graph LR
    A[初始化] --> B{ k≤√n ? }
    B -->|是| C[桶计数场景]
    B -->|否| D[区间扫描场景]
    C --> E[像素块入桶]
    D --> F[小人移动+高亮区间]
  ```

* **动画帧详解**：
  1. **初始化界面**  
     ![界面](https://fakeimg.pl/600x200/00ff00/000/?text=Binary+String&font_size=20)  
     *网格化二进制串*：1=黄色方块，0=灰色方块；控制面板含速度滑块/暂停键

  2. **小k阶段（桶计数）**  
     ![桶计数](https://fakeimg.pl/600x200/ff00ff/000/?text=Bucket+Counting&font_size=20)  
     - 顶部显示当前k值，左侧像素桶旋转入场  
     - 扫描位置i：计算`k*s_i-i`，对应桶亮蓝光+播放"叮"声  
     - **相同值匹配**：当桶计数≥2时，相关i位置闪烁红光，显示`ans += C(count,2)`

  3. **大k阶段（区间扫描）**  
     ![区间扫描](https://fakeimg.pl/600x200/00ffff/000/?text=Interval+Scanning&font_size=20)  
     - 像素小人从左端出发，脚印显示当前位置i  
     - 按k=1,2,3...显示1的位置：黄色方块脉冲发光  
     - 计算右端点区间：[L,R]显示绿色半透明覆盖  
     - **有效位置**：满足`len>k*√n`的倍数位置亮绿光，播放"噔"声

  4. **胜利结算**  
     所有k处理完成后，全屏闪烁+播放胜利旋律，显示最终答案

* **交互设计**：
  - **AI演示模式**：自动按最优速度运行（可调速）
  - **关键音效**：入桶(8bit水滴声)，匹配成功(金币声)，区间计算(激光声)
  - **教学提示**：右下角显示Kay的实时解析（如："k=3时，相同特征值匹配成功！"）

---

### 6. 拓展练习与相似问题思考
<similar_problems_intro>
根号分治是处理大规模数据的利器，以下问题可用相似思路：
</similar_problems_intro>

1. **哈希冲突（洛谷 P3396）**  
   * 当模数p≤√n时预处理，否则暴力查询  
   * **Kay提示**：巩固分治阈值选择能力

2. **Rmq Problem/mex（洛谷 P4137）**  
   * mex值≤√n时用桶扫描，否则用主席树  
   * **Kay提示**：学习不同数据结构的协同使用

3. **由乃打扑克（洛谷 P5356）**  
   * 分块+根号分治处理区间排序  
   * **Kay提示**：进阶训练分块思想与分治结合

---

### 7. 学习心得与经验分享
<insights_intro>
题解中的调试经验尤其珍贵：
</insights_intro>

> **crashed的踩坑记录**：  
> *"最初未考虑桶的负偏移，RE后通过`idx=k*s_i-i+N`解决"*  
>  
> **Kay点评**：  
> 偏移量处理是桶计数的核心技巧，类似问题可考虑`双倍空间+中间偏移`

> **OIer_Eternity的顿悟**：  
> *"发现k≤√n和k>√n的统计独立性后，才写出正确去重逻辑"*  
>  
> **Kay点评**：  
> 分治策略的数学证明是代码正确性的基石，建议用小数据验证覆盖性

---

### 结语
通过本指南，相信大家已掌握根号分治解决子串计数的精髓。记住：好算法=数学洞察+工程优化+可视化验证！下次算法冒险再见！🚀

> Kay's signature: 在代码的宇宙中，每个问题都是等待征服的星球。保持好奇，持续探索！

---
处理用时：236.42秒