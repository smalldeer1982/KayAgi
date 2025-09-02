# 题目信息

# Inflation

## 题目描述

You have a statistic of price changes for one product represented as an array of $ n $ positive integers $ p_0, p_1, \dots, p_{n - 1} $ , where $ p_0 $ is the initial price of the product and $ p_i $ is how the price was increased during the $ i $ -th month.

Using these price changes you are asked to calculate the inflation coefficients for each month as the ratio of current price increase $ p_i $ to the price at the start of this month $ (p_0 + p_1 + \dots + p_{i - 1}) $ .

Your boss said you clearly that the inflation coefficients must not exceed $ k $ %, so you decided to increase some values $ p_i $ in such a way, that all $ p_i $ remain integers and the inflation coefficients for each month don't exceed $ k $ %.

You know, that the bigger changes — the more obvious cheating. That's why you need to minimize the total sum of changes.

What's the minimum total sum of changes you need to make all inflation coefficients not more than $ k $ %?

## 说明/提示

In the first test case, you can, for example, increase $ p_0 $ by $ 50 $ and $ p_1 $ by $ 49 $ and get array $ [20150, 50, 202, 202] $ . Then you get the next inflation coefficients:

1. $ \frac{50}{20150} \le \frac{1}{100} $ ;
2. $ \frac{202}{20150 + 50} \le \frac{1}{100} $ ;
3. $ \frac{202}{20200 + 202} \le \frac{1}{100} $ ;

In the second test case, you don't need to modify array $ p $ , since the inflation coefficients are already good:

1. $ \frac{1}{1} \le \frac{100}{100} $ ;
2. $ \frac{1}{1 + 1} \le \frac{100}{100} $ ;

## 样例 #1

### 输入

```
2
4 1
20100 1 202 202
3 100
1 1 1```

### 输出

```
99
0```

# AI分析结果


### 💡 Kay的C++算法解析：Inflation 深入学习指南 💡  
**引言**  
今天我们一起分析"通货膨胀系数调整"这道贪心算法题。本指南将帮助你理解如何通过最小修改满足价格约束条件，掌握贪心策略的核心思想与应用技巧。

---

## 1. 题目解读与核心算法识别  
✨ **本题主要考察**：`贪心算法`  
🗣️ **初步分析**：  
> 解决本题的关键在于运用**贪心算法**。想象你在玩塔防游戏：当多个防御点同时告急时，优先升级能覆盖最多路径的炮塔。本题中，我们发现**只修改初始价格`p₀`是最优策略**——因为`p₀`出现在所有月份的分母中，修改它可同时解决多个月份的超标问题，且不会引发新问题（不会成为分子）。  
> - **题解思路**：遍历每个月份，若`100*pᵢ > k*前缀和`，计算需为`p₀`增加的最小值`max(0, ceil(100pᵢ/k)-当前前缀和)`，最终取所有月份需求的最大值  
> - **可视化设计**：像素方块表示每月价格，超标月份闪烁红色，`p₀`增加时显示绿色上升箭头与数值，前缀和进度条同步增长。复古音效：超标时"警告音"，解决后"金币音效"，背景为8-bit芯片音乐  

---

## 2. 精选优质题解参考  
**题解一（作者：henrytb）**  
* **点评**：直击贪心本质，代码简洁高效（O(n)时间复杂度）。亮点在于：  
  - **思路**：逆向遍历精妙避开前缀和更新问题，用`(p[i]*100 - sum[i-1]*k + k-1)/k`实现整数向上取整  
  - **代码**：变量名`ned`（need缩写）清晰，边界处理严谨（`per(i,n,2)`避免越界）  
  - **实践**：竞赛标准实现，无浮点运算避免精度问题  

**题解二（作者：Иɔlɔ）**  
* **点评**：正向遍历的典范实现。亮点在于：  
  - **思路**：实时维护前缀和，用`To_max(mx, need)`累积需求  
  - **代码**：`ceill(100.0*w[i]/k)`显式向上取整，逻辑一目了然  
  - **调试**：注释强调"增加其他`pⱼ`会引发连锁反应"，点明贪心选择`p₀`的核心原因  

**题解三（作者：云浅知处）**  
* **点评**：树状数组的创新应用（虽非最优但具教学意义）。亮点：  
  - **结构**：封装BIT类展示前缀和动态更新过程  
  - **健壮性**：单独实现`ceill()`处理整除边界  
  - **启发**：演示数据结构如何支持多次修改场景  

---

## 3. 核心难点辨析与解题策略  
1. **难点1：如何选择修改位置？**  
   * **分析**：修改`pⱼ`(j≥1)会同时影响其作为分子的后续月份。贪心选择`p₀`因它只出现在分母，如henrytb所述"`p₀`增大可贡献最多不满足点"  
   * 💡 **学习笔记**：优先修改影响范围最大的"杠杆变量"  

2. **难点2：避免浮点数精度陷阱**  
   * **分析**：条件`100*pᵢ ≤ k*S`需整数运算。Иɔlɔ用`ceil(100.0*w[i]/k)`，henrytb用`(x+k-1)/k`技巧避免浮点比较  
   * 💡 **学习笔记**：竞赛中优先使用整数运算+取整技巧  

3. **难点3：最小化总修改量**  
   * **分析**：所有月份共享`p₀`的修改量，故取各点需求最大值即全局最优解  
   * 💡 **学习笔记**：当修改可被复用时，局部最值即全局解  

### ✨ 解题技巧总结  
- **技巧1：问题特征识别** - 发现`p₀`的特殊地位（仅分母出现）  
- **技巧2：数学等价转换** - 将分式约束转为整式`100pᵢ ≤ k·S`  
- **技巧3：边界鲁棒性** - 用`(x+k-1)/k`或`ceil()`处理整除边界  

---

## 4. C++核心代码实现赏析  
**通用核心实现（综合优质题解）**  
```cpp
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    int t; cin >> t;
    while(t--) {
        ll n, k, need = 0, sum = 0;
        cin >> n >> k;
        ll p; cin >> p;  // p0
        sum = p;
        for(int i=1; i<n; ++i) {
            cin >> p;
            if(100*p > k*sum) 
                need = max(need, (100*p - k*sum + k-1)/k);
            sum += p;
        }
        cout << need << endl;
    }
}
```
**代码解读概要**：  
> 1. 读入测试次数`t`  
> 2. 对每组数据：  
>    - 初始化前缀和`sum=p₀`  
>    - 遍历后续价格：若超标则计算需为`p₀`增加的量`(100pᵢ - k*sum + k-1)/k`（向上取整）  
>    - 实时更新前缀和  

**题解一片段（henrytb）**  
```cpp
per(i,n,2) {  // 逆向遍历
    if(p[i]*100 > sum[i-1]*k) 
        ned = max(ned, (p[i]*100 - sum[i-1]*k + k-1)/k);
}
```
> **解读**：  
> - `per(i,n,2)`：从最后月份倒序遍历，避免修改`p₀`后重复检查  
> - `(x+k-1)/k`：经典整数向上取整技巧，等价于`ceil(x/k)`  
> - **学习笔记**：逆向遍历是处理"修改历史数据"的常用手段  

**题解二片段（Иɔlɔ）**  
```cpp
rep(i,2,n) {
    ll need_val = ceil(100.0*w[i]/k);
    To_max(mx, need_val - pre[i-1]); 
}
```
> **解读**：  
> - `ceil(100.0*w[i]/k)`：显式浮点取整确保精度  
> - `To_max(mx, x)`：宏定义实现`mx = max(mx, x)`，代码简洁  
> - **学习笔记**：宏可提升代码可读性，但需避免副作用  

---

## 5. 算法可视化：像素动画演示  
### 🎮 像素通胀大作战（8-bit风格）  
**设计思路**  
> 用FC游戏《大富翁》风格呈现：每月价格为像素金币堆，前缀和为进度条。超标月份闪烁红光时触发"央行干预"（修改`p₀`），强化贪心策略的直观理解。  

**关键帧流程**  
1. **初始化**：  
   - 屏幕顶部显示`p₀`金币堆（金色像素块）  
   - 垂直排列后续月份金币堆（银色像素块）  
   - 底部进度条标示当前前缀和，右侧显示`k%`阈值线  

2. **逐月检查**：  
   ``` 
   [Month 2] 检测中... 
   ██ 当前比例: 50/100 = 50% > k=1% → 超标!
   ```  
   - 超标月份闪烁红光，播放"警报音效"  
   - 显示计算过程：`需总前缀和 ≥ ceil(100*50/1)=5000`  

3. **修改`p₀`**：  
   - `p₀`金币堆上方弹出绿色`+4950`箭头  
   - 进度条从50扩展到5000（填充动画）  
   - 播放"金币叮当"音效  

4. **过关验证**：  
   - 所有月份变绿色，播放胜利音效  
   - 显示最终修改量：`4950`  

**交互控制**  
- 🎛️ 面板：步进/播放/重置按钮 + 速度滑块  
- 🎮 游戏化：每解决1个月份得100分，全部解决解锁"通胀克星"奖杯  

---

## 6. 拓展练习  
**相似问题场景**  
1. 水库水位调节：修改初始水位使每日流量不超过阈值  
2. 游戏资源平衡：调整初始资源产出率满足各关卡需求  
3. 温度控制系统：修改基础温度使各区域不超温  

**洛谷题目推荐**  
1. **P1090 合并果子**  
   → 贪心策略经典应用，巩固优先队列使用  
2. **P3817 小A的糖果**  
   → 变形：修改相邻元素满足差值约束，对比本题全局修改  
3. **P5019 铺设道路**  
   → 贪心+差分思想，强化前缀和应用  

---

## 7. 学习心得  
> **经验分享（综合题解）**：  
> *"避免修改中间元素是关键——这就像修补漏水管道，从源头处理比逐个修补裂缝更高效"*  
> **点评**：多篇题解强调`p₀`的特殊性，提醒我们解题时先分析变量间的数学关系，再设计策略  

---

通过本次分析，我们深入掌握了贪心策略在约束优化问题中的应用。记住：**识别关键变量+数学转化**是破解此类题目的核心！下次遇到类似问题，不妨先问自己："是否存在一个影响全局的杠杆变量？"

---
处理用时：206.72秒