# 题目信息

# Restorer Distance

## 题目描述

You have to restore the wall. The wall consists of $ N $ pillars of bricks, the height of the $ i $ -th pillar is initially equal to $ h_{i} $ , the height is measured in number of bricks. After the restoration all the $ N $ pillars should have equal heights.

You are allowed the following operations:

- put a brick on top of one pillar, the cost of this operation is $ A $ ;
- remove a brick from the top of one non-empty pillar, the cost of this operation is $ R $ ;
- move a brick from the top of one non-empty pillar to the top of another pillar, the cost of this operation is $ M $ .

You cannot create additional pillars or ignore some of pre-existing pillars even if their height becomes $ 0 $ .

What is the minimal total cost of restoration, in other words, what is the minimal total cost to make all the pillars of equal height?

## 样例 #1

### 输入

```
3 1 100 100
1 3 8```

### 输出

```
12```

## 样例 #2

### 输入

```
3 100 1 100
1 3 8```

### 输出

```
9```

## 样例 #3

### 输入

```
3 100 100 1
1 3 8```

### 输出

```
4```

## 样例 #4

### 输入

```
5 1 2 4
5 5 3 6 5```

### 输出

```
4```

## 样例 #5

### 输入

```
5 1 2 2
5 5 3 6 5```

### 输出

```
3```

# AI分析结果

# 💡 Kay的C++算法解析：Restorer Distance 深入学习指南 💡

<introduction>
  今天我们来一起分析「Restorer Distance」这道C++编程题。题目要求我们把不同高度的柱子变成一样高，通过加砖、减砖或移动砖三种操作，找到最小成本。这道题的核心是**用三分法找单谷函数的最小值**，跟着Kay一步步拆解，你会发现它其实很有趣！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：三分法（单谷函数最小值查找） + 前缀和优化

🗣️ **初步分析**：
解决这道题的关键，是找到一个「最终高度H」，让总操作成本最小。那成本和H的关系是什么呢？想象一下：如果H太小，需要加很多砖（成本A）；如果H太大，需要减很多砖（成本R）；而中间某个H会让成本最低——这就像一个「山谷」，成本先降后升，形成**单谷函数**（下凸函数）。

三分法就是专门找这种「山谷最低点」的算法！它的核心思想像「缩小包围圈」：每次在区间里选两个点（lmid和rmid），比较它们的成本——哪边成本高，就把哪边的边界往中间缩，直到找到最小值。

在本题中，我们需要：
1. **预处理**：排序柱子高度，计算前缀和（快速求「需要加的总砖数」和「需要减的总砖数」）；
2. **三分查找**：在可能的H区间（比如从最小高度到最大高度）里，用三分法找成本最低的H；
3. **成本计算**：对每个H，先算需要加的总高度X和减的总高度Y，优先用移动操作（M，因为M≤A+R），剩下的用加或减操作。

**可视化设计思路**：我们用8位像素风模拟三分过程——
- 屏幕左侧是「H轴」（像素柱子，高度代表H），右侧是「成本柱」（高度代表该H的成本）；
- 用红色框标记当前区间[l, r]，黄色高亮lmid和rmid，绿色闪烁最终找到的最优H；
- 每次比较lmid和rmid的成本时，播放「叮」的音效：如果lmid成本高，左边边界往右缩（红色框右移）；反之右边边界往左缩。


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和算法有效性三个维度，筛选了3份优质题解，帮你快速掌握核心方法！
</eval_intro>

**题解一：wsyhb（证明+三分+前缀和）**
* **点评**：这份题解最棒的地方是**严谨证明了成本函数是单谷的**！作者详细分析了H变化时成本的变化率，证明变化率单调递增（函数下凸），让三分法的使用有了理论依据。代码里用排序+前缀和快速计算X和Y，三分的边界处理也很规范（当l<r时循环，取三等分点），逻辑清晰到像说明书！

**题解二：b6e0_（三分+贪心）**
* **点评**：作者不仅讲了三分的两种实现方式（三等分点/缩小到100后枚举），还补充了**贪心思路**——当M较小时，最优H在平均数附近。代码里的`getans`函数很聪明：先算X和Y，再比较「移动+剩余操作」和「直接加+减」的成本，取最小值，考虑得很全面！

**题解三：7KByte（二分替代三分）**
* **点评**：这份题解很有创意！作者把「三分找最小值」转化为「二分找斜率变号的点」——通过`check(x)`判断x处的成本是否比x+1小，从而找到最优H。代码超级简洁，时间复杂度和三分一样，但思路更巧妙，适合想拓展思维的同学！


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题时，大家常遇到三个「卡点」，Kay帮你拆解清楚！
</difficulty_intro>

1. **难点1：怎么证明成本函数是单谷的？**
   * **分析**：成本函数的「变化率」（H增加1时成本的变化量）是单调递增的。比如当H很小时，增加H会减少成本（变化率负）；当H超过最优值后，增加H会增加成本（变化率正）。变化率从负变正，说明函数先降后升，是单谷的！
   * 💡 **学习笔记**：单谷函数的关键是「变化率单调」，证明这一点就能放心用三分！

2. **难点2：怎么快速计算X和Y？**
   * **分析**：X是「所有比H矮的柱子需要加的总高度」，Y是「所有比H高的柱子需要减的总高度」。排序后用前缀和，可以通过二分找到H的位置，快速算出X=H*p - sum[p]（p是比H小的柱子数量），Y=sum[n]-sum[p] - H*(n-p)。
   * 💡 **学习笔记**：排序+前缀和是处理「区间和」问题的神器！

3. **难点3：三分的边界怎么处理？**
   * **分析**：三分的循环条件通常是`l < r`，但当区间很小时（比如长度<100），直接枚举所有H计算成本更安全（避免边界错误）。比如b6e0_的代码里，当ri-le>100时用三分，否则枚举。
   * 💡 **学习笔记**：处理边界的小技巧——「大区间用三分，小区间枚举」！


### ✨ 解题技巧总结
- **技巧A：预处理优化**：排序+前缀和，把计算X和Y的时间从O(n)降到O(log n)；
- **技巧B：操作等价转换**：先把M更新为min(M, A+R)，因为移动砖的成本不可能比「减+加」更高；
- **技巧C：三分边界处理**：当区间足够小时，直接枚举所有可能的H，避免三分的边界错误。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**通用核心代码**，综合了优质题解的思路，清晰展示「排序→前缀和→三分→计算成本」的完整流程！
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码来自wsyhb的题解，逻辑最清晰，覆盖了所有核心步骤。
* **完整核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,A,R,M;
const int max_N=1e5+5;
int h[max_N];
long long sum[max_N];

inline long long calc(int H) {
    int p=upper_bound(h+1,h+N+1,H)-h-1;
    long long X=1ll*p*H - sum[p];     // 需要加的总高度
    long long Y=(sum[N]-sum[p]) - 1ll*(N-p)*H; // 需要减的总高度
    long long c=min(X,Y);
    return A*(X-c) + R*(Y-c) + M*c;   // 移动c次，剩下的加或减
}

int main() {
    scanf("%d%d%d%d",&N,&A,&R,&M);
    M=min(M,A+R); // 优化移动成本
    for(int i=1;i<=N;++i) scanf("%d",h+i);
    sort(h+1,h+N+1);
    for(int i=1;i<=N;++i) sum[i]=sum[i-1]+h[i]; // 前缀和
    
    int l=h[1],r=h[N];
    while(l<r) {
        int lmid=l+(r-l)/3,rmid=r-(r-l)/3;
        if(calc(lmid)<calc(rmid)) r=rmid-1;
        else l=lmid+1;
    }
    printf("%lld\n",calc(l));
    return 0;
}
```
* **代码解读概要**：
  1. **输入与预处理**：读入数据，更新M为min(M,A+R)，排序h数组，计算前缀和sum；
  2. **三分查找**：初始化区间为[最小高度, 最大高度]，每次取lmid和rmid，比较成本后收缩区间；
  3. **计算成本**：`calc`函数用upper_bound找H的位置，计算X和Y，优先用移动操作，返回总成本。


<code_intro_selected>
接下来看三个优质题解的核心片段，学习它们的「亮点」！
</code_intro_selected>

**题解一：wsyhb的calc函数**
* **亮点**：用upper_bound快速找p，前缀和计算X和Y，逻辑简洁。
* **核心代码片段**：
```cpp
inline long long calc(int H) {
    int p=upper_bound(h+1,h+N+1,H)-h-1;
    long long X=1ll*p*H - sum[p];
    long long Y=(sum[N]-sum[p]) - 1ll*(N-p)*H;
    long long c=min(X,Y);
    return A*(X-c) + R*(Y-c) + M*c;
}
```
* **代码解读**：
  - `upper_bound`找的是「第一个比H大的元素位置」，所以p是比H小的元素数量；
  - X是「所有比H小的元素需要加的总高度」（H*p是目标总高度，减去原总高度sum[p]）；
  - Y是「所有比H大的元素需要减的总高度」（原总高度sum[N]-sum[p]减去目标总高度H*(N-p)）；
  - c是X和Y的较小值，用移动操作（M*c），剩下的X-c用加操作（A*(X-c)），Y-c用减操作（R*(Y-c)）。
* 💡 **学习笔记**：upper_bound+前缀和是计算区间和的黄金组合！

**题解二：b6e0_的getans函数**
* **亮点**：考虑了「移动+剩余操作」和「直接加+减」的成本，取最小值，更严谨。
* **核心代码片段**：
```cpp
long long getans(long long mid) {
    long long sum1=0,sum2=0;
    for(int i=0;i<n;i++) {
        if(h[i]<mid) sum1+=mid-h[i];
        else sum2+=h[i]-mid;
    }
    if(sum1>sum2) 
        return min(sum2*m+(sum1-sum2)*a, sum1*a+sum2*r);
    return min(sum1*m+(sum2-sum1)*r, sum1*a+sum2*r);
}
```
* **代码解读**：
  - sum1是需要加的总高度，sum2是需要减的总高度；
  - 当sum1>sum2时，比较「移动sum2次+加sum1-sum2次」和「直接加sum1次+减sum2次」的成本，取小的；
  - 这样做是因为有时候移动操作不一定更优（比如M=A+R时，两种方式成本一样）。
* 💡 **学习笔记**：永远要考虑「特殊情况」，比如M等于A+R时，移动和直接加+减一样贵！

**题解三：7KByte的check函数**
* **亮点**：用二分替代三分，思路新颖，代码更简洁。
* **核心代码片段**：
```cpp
bool check(int x) {
    return calc(x) < calc(x+1);
}

void solve() {
    // ... 输入与预处理 ...
    int l=1,r=1e9,ans=0;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%lld\n",min(calc(ans),min(calc(ans-1),calc(ans+1))));
}
```
* **代码解读**：
  - `check(x)`判断x处的成本是否比x+1小：如果是，说明最优H在x左边；否则在x右边；
  - 二分找到第一个满足`check(x)`的x，再检查x-1和x+1的成本，确保找到最小值。
* 💡 **学习笔记**：二分和三分可以互相转换，关键是找到「判断条件」！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你直观看到三分法的过程，Kay设计了一个**8位像素风的动画**，像玩红白机游戏一样学算法！
</visualization_intro>

### **动画演示主题**：像素探险家找「成本山谷」
### **核心演示内容**：三分法如何缩小区间，找到成本最低的H。
### **设计思路**：用复古像素风格降低学习压力，用音效和动画强化记忆——比如「叮」的音效提示比较操作，红色框收缩表示区间缩小，绿色闪烁表示找到最优解。

### **动画帧步骤与交互关键点**
1. **场景初始化**：
   - 屏幕左侧是「H轴」：用像素柱子表示H（从l到r），高度对应H值；
   - 屏幕右侧是「成本柱」：每个H对应的成本用蓝色柱子表示，高度越高成本越高；
   - 控制面板有「开始/暂停」「单步执行」「重置」按钮，还有速度滑块。

2. **算法启动**：
   - 初始区间[l=h[1], r=h[N]]用红色框标记，播放轻快的8位BGM；
   - 第一次选lmid=l+(r-l)/3，rmid=r-(r-l)/3，用黄色高亮这两个点。

3. **核心步骤演示**：
   - 比较lmid和rmid的成本：如果lmid的成本柱更高，播放「叮」声，红色框右移（l=lmid+1）；
   - 每次收缩区间时，红色框变小，成本柱的「山谷」越来越明显；
   - 当区间长度<100时，切换到「枚举模式」，逐个H检查成本，绿色闪烁最优H。

4. **目标达成**：
   - 找到最优H后，播放「胜利」音效（上扬的8位音调），最优H的柱子闪烁绿色，成本柱显示最小值。

### **旁白提示**
- 「现在检查lmid和rmid的成本，lmid的成本更高，所以最优H在右边，缩小左边界！」
- 「区间越来越小啦，再走几步就能找到最低点啦！」
- 「找到最优H啦！成本是XXX，就是这个绿色的柱子！」


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
三分法是处理「单谷函数最小值」的神器，学会它可以解决很多类似问题！
</similar_problems_intro>

### **通用思路迁移**
三分法适用于**函数先降后升**（单谷）或**先升后降**（单峰）的问题，比如：
1. 找抛物线的最低点；
2. 找最优切割点（比如切绳子使面积最大）；
3. 找最优参数（比如调整学习率使模型损失最小）。

### **练习推荐 (洛谷)**
1. **洛谷 P3382** - 三分法模板题
   * 🗣️ **推荐理由**：最经典的三分模板题，直接练手三分的边界处理！
2. **洛谷 P1883** - 函数
   * 🗣️ **推荐理由**：需要自己构造单谷函数，练习「问题转化」能力！
3. **洛谷 P2678** - 跳石头
   * 🗣️ **推荐理由**：虽然是二分题，但可以用三分思路尝试，对比两者的区别！


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解里的「踩坑经验」比代码更宝贵，Kay帮你提炼出来！
</insights_intro>

> **参考经验 (来自wsyhb)**：「我最初证明时漏掉了X≤Y和X>Y的交界，导致结论错误。后来仔细分析了H变化时X和Y的变化，才补全了证明。」
> **点评**：证明函数单调性时，一定要考虑「边界情况」（比如X从小于Y变成大于Y的瞬间），否则结论会出错！

> **参考经验 (来自b6e0_)**：「当M较小时，最优H在平均数附近，所以可以枚举平均数附近的几个值，快速找到最小值。」
> **点评**：贪心思路能帮你「缩小范围」，比如平均数附近的H大概率是最优的，不用遍历所有可能！


<conclusion>
本次关于「Restorer Distance」的分析就到这里啦！记住：三分法的关键是**证明函数是单谷的**，预处理的关键是**排序+前缀和**，成本计算的关键是**优先用移动操作**。多练几道类似题，你会越来越熟练！下次我们再一起探索新的算法挑战，加油！💪
</conclusion>

---
处理用时：80.47秒