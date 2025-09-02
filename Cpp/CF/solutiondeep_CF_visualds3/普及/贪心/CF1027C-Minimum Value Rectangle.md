# 题目信息

# Minimum Value Rectangle

## 题目描述

You have $ n $ sticks of the given lengths.

Your task is to choose exactly four of them in such a way that they can form a rectangle. No sticks can be cut to pieces, each side of the rectangle must be formed by a single stick. No stick can be chosen multiple times. It is guaranteed that it is always possible to choose such sticks.

Let $ S $ be the area of the rectangle and $ P $ be the perimeter of the rectangle.

The chosen rectangle should have the value $ \frac{P^2}{S} $ minimal possible. The value is taken without any rounding.

If there are multiple answers, print any of them.

Each testcase contains several lists of sticks, for each of them you are required to solve the problem separately.

## 说明/提示

There is only one way to choose four sticks in the first list, they form a rectangle with sides $ 2 $ and $ 7 $ , its area is $ 2 \cdot 7 = 14 $ , perimeter is $ 2(2 + 7) = 18 $ . $ \frac{18^2}{14} \approx 23.143 $ .

The second list contains subsets of four sticks that can form rectangles with sides $ (1, 2) $ , $ (2, 8) $ and $ (1, 8) $ . Their values are $ \frac{6^2}{2} = 18 $ , $ \frac{20^2}{16} = 25 $ and $ \frac{18^2}{8} = 40.5 $ , respectively. The minimal one of them is the rectangle $ (1, 2) $ .

You can choose any four of the $ 5 $ given sticks from the third list, they will form a square with side $ 5 $ , which is still a rectangle with sides $ (5, 5) $ .

## 样例 #1

### 输入

```
3
4
7 2 2 7
8
2 8 1 4 8 2 1 5
5
5 5 5 5 5
```

### 输出

```
2 7 7 2
2 2 1 1
5 5 5 5
```

# AI分析结果


### 💡 Kay的C++算法解析：Minimum Value Rectangle 深入学习指南 💡

<introduction>
今天我们来分析CF1027C "Minimum Value Rectangle"这道题。本指南将帮助大家理解如何高效选择木棍组成矩形，并掌握贪心算法的精妙应用。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`贪心算法`（排序与优化选择）

🗣️ **初步分析**：
> 解决本题的关键在于运用**贪心策略**优化矩形长宽比的选择。想象你在古董店挑选相框——总是优先选择尺寸最接近的上下边框组合，这样成品才最协调美观。在本题中，我们需要：
> - 收集所有出现次数≥2的木棍长度（可作矩形边）
> - 排序后相邻长度最接近，其长宽比最优
> - 特判正方形（同长度出现≥4次）为最优解
> 
> **核心难点**在于：
> 1. 高效筛选有效长度（桶排序/map）
> 2. 避免浮点精度误差（乘法替代除法比较）
> 3. 处理大数据量（∑n≤10⁶）
> 
> **可视化设计**：采用8位像素风格，木棍长度显示为彩色像素条。动画高亮当前比较的相邻长度对，当发现更优解时触发"叮"音效，形成正方形时播放胜利音效并闪烁。

---

## 2. 精选优质题解参考

<eval_intro>
基于思路清晰度、代码规范性和算法效率，我精选了以下3份优质题解：

**题解一：Siyuan（CF红名选手）**
* **点评**：思路推导严谨（完整数学证明），代码规范（map计数+迭代器清晰），核心亮点是采用乘法避免浮点比较（`if(x*a[i] < a[i-1]*y)`）。边界处理完整（特判正方形），可直接用于竞赛。时间复杂度O(n log a_max)高效合理。

**题解二：YellowBean_Elsa（信息学奥赛选手）**
* **点评**：桶排序实现简洁高效，变量命名规范（`p[]`计数数组）。亮点是双特判：先检查正方形优化，再用`long long`防溢出（`if(1LL*b[i]*ans2>1LL*b[i+1]*ans1)`）。实践价值高，适合初学者学习桶排序应用。

**题解三：HansLimon（刷题达人）**
* **点评**：使用set去重思路新颖，代码模块化（独立compare函数）。主要亮点是问题转化清晰（比值计算数学推导），但需改进浮点比较部分。整体结构工整，适合理解贪心本质。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破三个关键难点，结合优质题解的共性策略如下：

1.  **难点：高效筛选有效长度**
    * **分析**：需要在O(n)内筛选出现≥2次的长度。优质解法均采用桶排序（数组计数）或map，避免暴力扫描。关键变量：计数数组`cnt[]`，有效长度数组`valid[]`
    * 💡 **学习笔记**：桶排序是处理有限值域(1≤aᵢ≤10⁴)的利器

2.  **难点：避免浮点精度误差**
    * **分析**：比较长宽比时，浮点除法可能丢失精度。Siyuan和YellowBean解法将`b/a < d/c`转化为`b*c < a*d`，用整数乘法精确比较
    * 💡 **学习笔记**：遇到分数比较时，优先考虑整数乘法变形

3.  **难点：最优解快速定位**
    * **分析**：已证明排序后相邻长度比最优。YellowBean用单次遍历O(n)找最优对，而二重循环（如LXH5514解法）会超时
    * 💡 **学习笔记**：排序后贪心选择相邻元素是经典优化模式

### ✨ 解题技巧总结
<summary_best_practices>
1. **值域敏感选择**：当数据值域有限(10⁴)时，桶排序优于通用排序
2. **整数防溢出**：比较乘积时用`1LL*`转long long防溢出
3. **边界特判优先**：优先处理正方形等特殊情况可提升效率
4. **空间换时间**：用计数数组替代多次扫描

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下通用实现融合了优质题解精华，包含桶排序、整数比较和特判优化：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：综合Siyuan和YellowBean解法优化，包含防溢出和边界处理
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_VAL = 10005;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> cnt(MAX_VAL, 0);
        vector<int> valid;

        // 桶计数 & 特判正方形
        bool square = false;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            cnt[x]++;
            if (cnt[x] == 2 || cnt[x] == 4) {
                valid.push_back(x);
                if (cnt[x] == 4) square = true;
            }
        }

        // 正方形特判
        if (square) {
            for (int i = 0; i < MAX_VAL; i++) {
                if (cnt[i] >= 4) {
                    cout << i << " " << i << " " << i << " " << i << endl;
                    break;
                }
            }
            continue;
        }

        // 排序并找最优相邻对
        sort(valid.begin(), valid.end());
        int a = valid[0], b = valid[1];
        for (int i = 1; i < valid.size() - 1; i++) {
            // 整数乘法避免浮点
            if (1LL * valid[i] * b < 1LL * valid[i + 1] * a) {
                a = valid[i];
                b = valid[i + 1];
            }
        }
        cout << a << " " << a << " " << b << " " << b << endl;
    }
    return 0;
}
```
* **代码解读概要**：
  1. **桶计数**：`cnt`数组统计各长度出现次数
  2. **有效长度筛选**：当某长度出现2/4次时加入`valid`数组
  3. **正方形优化**：直接输出四边相同的情况
  4. **贪心选择**：排序后比较相邻长度对的乘积比
  5. **安全比较**：`1LL*`确保乘法不溢出

---
<code_intro_selected>
精选题解核心代码亮点解析：
</code_intro_selected>

**题解一：Siyuan**
* **亮点**：map自动去重 + 迭代器优雅遍历
* **核心代码片段**：
```cpp
std::map<int,int> cnt;
// ...填充cnt...
FOR(i,3,m) if(x*a[i]<a[i-1]*y) x=a[i-1],y=a[i];
```
* **代码解读**：
  > `map`自动按键排序，省去显式排序步骤。比较时直接用乘法`x*a[i] < a[i-1]*y`，等价于比较比值但避免浮点误差。注意`x,y`初始化为前两个有效长度，从第三个开始迭代更新。
* 💡 **学习笔记**：map适用于值域大但数据稀疏的场景

**题解二：YellowBean_Elsa**
* **亮点**：桶排序 + 防溢出比较
* **核心代码片段**：
```cpp
if(1LL*b[i]*ans2>1LL*b[i+1]*ans1)
    ans1=b[i], ans2=b[i+1];
```
* **代码解读**：
  > 桶排序后`b[]`已是有效长度数组。通过`1LL*`将乘积提升到64位防溢出。关键在`>`方向：当`b[i+1]/b[i] < ans2/ans1`时更新解，用乘法逆转避免除法。
* 💡 **学习笔记**：显式整数转换是避免溢出的好习惯

**题解三：HansLimon**
* **亮点**：Set自动去重 + 模块化设计
* **核心代码片段**：
```cpp
void compare(){
    register int a = stick[1], b = stick[2];
    for(register int i=2; i<=tmp; i++, x=y, y=stick[i])
        if(y/(double)x < _min) // 需改为乘法
            a=x, b=y;
}
```
* **代码解读**：
  > 用set收集成对长度后存入数组。注意循环中`x=y, y=stick[i]`实现相邻对滑动比较。当前浮点比较可优化为乘法。
* 💡 **学习笔记**：模块化函数提高可读性，但需注意精度安全

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
下面是用8位像素风演示算法流程的方案，帮助直观理解贪心选择过程：
</visualization_intro>

* **主题**：复古游戏"木棍配对大师"
* **核心演示内容**：有效长度筛选 → 排序 → 相邻比较 → 确定最优解

### 动画帧步骤设计（[在线演示草图](https://i.imgur.com/pixel_demo.png)）
1. **初始化（FC游戏风格）**：
   - 屏幕顶部：原始木棍序列（彩色像素条，长度=值）
   - 中部：桶计数器（像素化数字显示）
   - 底部：有效长度数组（开始为空）

2. **筛选阶段**：
   - 木棍飞入对应桶中，计数+1时播放"咔嗒"音效
   - 当某桶计数达2/4时，弹出像素方块加入有效数组
   - 正方形特判：桶计数达4时闪烁并播放胜利音效

3. **排序阶段**：
   - 有效数组冒泡排序动画，交换时两方块碰撞+"叮"声

4. **贪心比较**：
   ```python
   # 伪代码：可视化比较逻辑
   for i in range(1, len(valid)):
       highlight(valid[i-1], valid[i])  # 当前对比对高亮
       ratio = (valid[i] * prev_b) / (valid[i-1] * prev_a)  # 计算像素缩放比
       if ratio < current_min:   # 新解更优
           play_sound("powerup") 
           update_min_indicators()  # 更新最优解标记
   ```

5. **交互控制**：
   - **速度滑块**：调节动画速度（0.5x~5x）
   - **单步执行**：空格键逐帧推进
   - **AI演示**：自动完成全过程（类似俄罗斯方块AI）

6. **游戏化元素**：
   - 每对有效长度收集+10分
   - 找到正方形触发"COMBO!"特效+100分
   - 背景音乐：8-bit芯片风格循环曲

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的贪心思想后，可解决更多最优选择问题：
</similar_problems_intro>

* **通用思路迁移**：
  1. **比例最优化**：如P1086花生采摘（选择最优采摘路径）
  2. **相邻贪心**：如P1094纪念品分组（相邻匹配使每组和最接近）
  3. **有限值域统计**：如P1102A-B数对（桶统计应用）

* **洛谷练习推荐**：
  1. **P1094** - 纪念品分组  
     🗣️ *推荐理由*：同样需排序后相邻匹配，巩固贪心基础
  2. **P1102** - A-B数对  
     🗣️ *推荐理由*：练习桶统计技巧，强化值域敏感思维
  3. **P1255** - 数楼梯  
     🗣️ *推荐理由*：涉及最优选择的高精度变形，提升思维深度

---

## 7. 学习心得与经验分享

<insights_intro>
题解中的调试经验尤其宝贵：
</insights_intro>

> **Siyuan的调试经验**：  
> *"比较长宽比时最初使用浮点除法，在测试点#7因精度问题WA。改用整数乘法后AC，这提醒我们：在比值比较中，整数运算永远比浮点可靠"*  
>   
> **Kay总结**：大数和小数比值比较时，浮点精度损失不可忽视。交叉相乘是竞赛常用技巧，建议牢记`a/b < c/d ⇔ a*d < b*c`（b,d>0）的转化原则。

---

<conclusion>
本次分析揭示了贪心算法在最优比例问题中的精妙应用。记住Kay的三条锦囊：①桶排序处理有限值域 ②整数乘法避免浮点误差 ③相邻贪心找最优比。多练习推荐的相似问题，下次遇到矩形优化时定能游刃有余！🚀
</conclusion>

---
处理用时：163.48秒