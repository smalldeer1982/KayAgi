# 题目信息

# Robin Hood in Town

## 题目描述

In Sherwood, we judge a man not by his wealth, but by his merit.



Look around, the rich are getting richer, and the poor are getting poorer. We need to take from the rich and give to the poor. We need Robin Hood!

There are $ n $ people living in the town. Just now, the wealth of the $ i $ -th person was $ a_i $ gold. But guess what? The richest person has found an extra pot of gold!

More formally, find an $ a_j=max(a_1, a_2, \dots, a_n) $ , change $ a_j $ to $ a_j+x $ , where $ x $ is a non-negative integer number of gold found in the pot. If there are multiple maxima, it can be any one of them.

A person is unhappy if their wealth is strictly less than half of the average wealth $ ^{\text{∗}} $ .

If strictly more than half of the total population $ n $ are unhappy, Robin Hood will appear by popular demand.

Determine the minimum value of $ x $ for Robin Hood to appear, or output $ -1 $ if it is impossible.

 $ ^{\text{∗}} $ The average wealth is defined as the total wealth divided by the total population $ n $ , that is, $ \frac{\sum a_i}{n} $ , the result is a real number.

## 说明/提示

In the first test case, it is impossible for a single person to be unhappy.

In the second test case, there is always $ 1 $ happy person (the richest).

In the third test case, no additional gold are required, so the answer is $ 0 $ .

In the fourth test case, after adding $ 15 $ gold, the average wealth becomes $ \frac{25}{4} $ , and half of this average is $ \frac{25}{8} $ , resulting in $ 3 $ people being unhappy.

In the fifth test case, after adding $ 16 $ gold, the average wealth becomes $ \frac{31}{5} $ , resulting in $ 3 $ people being unhappy.

## 样例 #1

### 输入

```
6
1
2
2
2 19
3
1 3 20
4
1 2 3 4
5
1 2 3 4 5
6
1 2 1 1 1 25```

### 输出

```
-1
-1
0
15
16
0```

# AI分析结果


### 💡 Kay的C++算法解析：Robin Hood in Town 深入学习指南 💡

**引言**  
今天我们一起分析"Robin Hood in Town"这道有趣的C++编程题。本指南将帮助你理解如何通过数学推导或二分查找高效解决金币分配问题，并通过像素动画直观展示算法过程。

---

### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`数学推导`与`二分查找`  

🗣️ **初步分析**：  
> 解决这道题的关键在于发现金币分配的**临界点规律**。想象小镇居民按财富排成队伍，当中间位置居民的财富值被"平均线"越过时，就会触发罗宾汉的出现（超过半数人不满）。  
> - **数学推导法**：通过排序找到中位数位置（第n/2+1个居民），直接计算最小x值（公式：`x = max(0, 2*n*aₖ - sum + 1)`）  
> - **二分查找法**：利用x的单调性（x越大不满人数越多），二分搜索满足条件的最小x  
> - **可视化设计**：像素动画将展示居民财富柱状图排序过程，用红色标记不满居民。当增加x时，金色"最大值"柱升高，灰色"平均线"上移，红线跨越中位数位置时触发胜利音效  

---

### 2. 精选优质题解参考
**题解一：Karieciation（公式推导法）**  
* **点评**：此解法精妙地发现了中位数位置与临界值的关系，用`2*n*aₖ - sum + 1`直接计算x。代码简洁高效（O(n log n)），变量命名清晰（sum, p），边界处理严谨（n≤2特判）。亮点在于完整的公式推导，帮助理解数学本质。

**题解二：Temp113（二分查找法）**  
* **点评**：通过二分搜索验证x的单调性，思路通用性强。代码结构规范（check函数分离），变量作用明确（tmp备份原数组）。虽然比公式法稍慢（O(n log max_x)），但展示了二分思想的典型应用，调试技巧值得学习（临时修改数组后恢复）。

**题解三：Super_Cube（二分优化版）**  
* **点评**：在二分框架中巧妙使用`lower_bound`优化不满人数统计。代码简洁有力（一行核心判断），利用STL提升效率。亮点在于结合排序位置快速计数，避免完整遍历，实践价值高。

---

### 3. 核心难点辨析与解题策略
1. **关键点：发现中位数临界规律**  
   * **分析**：要使超过半数人不满，排序后第n/2+1个居民必须低于平均线（其前方所有人自然满足条件）。优质题解都通过排序后取a[n/2+1]定位此关键点
   * 💡 **学习笔记**：排序后中位数位置是群体不满的"多米诺骨牌触发点"

2. **关键点：严格不等式处理**  
   * **分析**：题目要求"严格小于"平均值一半，公式法中需`+1`（x > 2np-sum ⇒ x ≥ 2np-sum+1），二分法则需精确浮点数比较
   * 💡 **学习笔记**：临界值计算时，严格不等式需要额外+1偏移

3. **关键点：特判无解情况**  
   * **分析**：当n≤2时，无论如何分配都无法满足超过半数不满（1人时0不满，2人时最多1不满）。所有优质题解优先处理此特例
   * 💡 **学习笔记**：小规模数据常需特殊处理，避免公式失效

✨ **解题技巧总结**  
- **中位数定位法**：排序后取n/2+1位置可快速确定群体临界点  
- **二分答案套路**：当答案单调且验证简单时优先考虑二分框架  
- **防御性编程**：对公式计算结果做max(0, ...)处理防止负值  

---

### 4. C++核心代码实现赏析
**本题通用核心实现（公式法）**  
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        ll a[N], sum = 0;
        for (int i=1; i<=n; i++) {
            cin >> a[i];
            sum += a[i];
        }
        if (n <= 2) {
            cout << -1 << endl;
            continue;
        }
        sort(a+1, a+n+1);
        ll p = a[n/2+1];          // 关键：取中位数位置
        ll x = 2 * n * p - sum + 1; // 临界值公式
        cout << max(0LL, x) << endl;
    }
    return 0;
}
```
* **代码解读概要**：  
  > 1. 读入多组数据，对每组数据求和  
  > 2. 特判n≤2直接返回-1  
  > 3. 排序数组并取中位数位置a[n/2+1]  
  > 4. 通过公式`2*n*p - sum + 1`计算x，负值取0  

---

**题解片段赏析**  
**题解一：Karieciation（公式法）**  
```cpp
sort(a+1, a+1+n);
ll v = (ll)a[n+2>>1] * n << 1;  // 位运算优化*2
if (sum > v) puts("0");          // 已满足条件
else printf("%lld\n", v - sum + 1);
```
* **亮点**：位运算优化，分支处理优雅  
* **代码解读**：  
  > 1. `n+2>>1`等效于`n/2+1`（位运算加速）  
  > 2. 若原总和sum已大于临界值`2np`，则x=0  
  > 3. 否则计算`x = 2np - sum + 1`（严格不等式）  
* 💡 **学习笔记**：位运算可提升常数效率，但需确保可读性  

**题解二：Temp113（二分法）**  
```cpp
bool check(ll x) {
    ll tmp = a[n], s = 0, cnt = 0;
    a[n] += x;                    // 临时修改最大值
    for (int i=1; i<=n; i++) s += a[i];
    double avg_half = (double)s/n/2;  // 平均线计算
    for (int i=1; i<=n; i++) 
        if (a[i] < avg_half) cnt++;
    a[n] = tmp;                   // 恢复原数组
    return cnt > n/2;             // 检查是否超半数
}
```
* **亮点**：完整封装check函数，安全备份恢复数据  
* **代码解读**：  
  > 1. 备份最大值→增加x→计算新总和→统计不满人数  
  > 2. 用浮点数精确比较`a[i] < avg_half`  
  > 3. 恢复数据避免污染后续操作  
* 💡 **学习笔记**：修改全局数据需备份，避免副作用  

---

### 5. 算法可视化：像素动画演示
**主题**：金币小镇的罗宾汉召唤（8-bit像素风格）  

**核心演示**：  
![](https://assets.luogu.com.cn/upload/image_hosting/9z8p7w0k.png)  
*图中：绿柱=普通居民，金柱=最大值，红线=平均线，红柱=不满居民*

**设计思路**：  
> 采用FC红白机像素风格，用不同高度柱状图表示财富值。当增加x时：  
> 1. 金色柱子（最大值）升高 → 播放"金币叮当"音效  
> 2. 灰色平均线同步上移 → 触发"机械滑动"音效  
> 3. 柱顶低于灰线时变红 → 播放"叹息"音效  
> 4. 红柱超过半数时 → 触发胜利音效+烟花特效  

**动画流程**：  
1. **初始化**：居民随机站队 → 像素化排序动画（冒泡效果+音效）  
2. **关键操作**：  
   - 拖拽滑块调整x值 → 实时更新金柱高度和平均线  
   - 点击"AI演示" → 自动寻优（x从0递增，速度可调）  
3. **状态标记**：  
   - 当前中位数居民：闪烁蓝色边框  
   - 不满居民：红色填充+沮丧表情像素图  
4. **胜利条件**：当红柱数量 > n/2时：  
   - 屏幕闪烁红光  
   - 播放8-bit胜利音乐  
   - 罗宾汉像素角色从天而降  

**技术实现**：  
- 用Canvas绘制动态柱状图和移动平均线  
- Web Audio API触发音效（金币声/叹息声/胜利乐）  
- requestAnimationFrame实现平滑动画  

---

### 6. 拓展练习与相似问题思考
**通用技巧迁移**：  
1. 中位数临界思想 → 群体决策/投票系统问题  
2. 二分答案框架 → 最优解搜索问题（如最小化最大值）  
3. 公式推导法 → 数学敏感的边界条件问题  

**洛谷推荐**：  
1. **P1873 砍树**  
   🗣️ *推荐理由*：巩固二分答案思想，寻找最大砍树高度  
2. **P2678 跳石头**  
   🗣️ *推荐理由*：最小化最大跳跃距离，强化二分验证逻辑  
3. **P2440 木材加工**  
   🗣️ *推荐理由*：数学推导与二分法的对比练习  

---

### 7. 学习心得与经验分享
> **参考经验**：多位作者强调`n≤2`的特判重要性，如Karieciation提到："当n=1时不满人数为0，n=2时最多1人不满，永远无法超半数"  
> **点评**：这种边界意识是竞赛编程的关键！调试时优先验证特殊数据范围，可避免80%的WA  

---

**结语**  
通过本次分析，我们掌握了群体不满度的临界值计算技巧，体验了数学推导与二分法的性能取舍。记住：排序定位中位数是此类问题的金钥匙！下次遇到"超半数满足条件"的问题时，不妨回想金币小镇的像素居民们哦~ 💪🏻

---
处理用时：215.66秒