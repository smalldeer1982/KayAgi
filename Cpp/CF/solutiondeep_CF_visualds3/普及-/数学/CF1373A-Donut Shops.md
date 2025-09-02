# 题目信息

# Donut Shops

## 题目描述

There are two rival donut shops.

The first shop sells donuts at retail: each donut costs $ a $ dollars.

The second shop sells donuts only in bulk: box of $ b $ donuts costs $ c $ dollars. So if you want to buy $ x $ donuts from this shop, then you have to buy the smallest number of boxes such that the total number of donuts in them is greater or equal to $ x $ .

You want to determine two positive integer values:

1. how many donuts can you buy so that they are strictly cheaper in the first shop than in the second shop?
2. how many donuts can you buy so that they are strictly cheaper in the second shop than in the first shop?

If any of these values doesn't exist then that value should be equal to $ -1 $ . If there are multiple possible answers, then print any of them.

 The printed values should be less or equal to $ 10^9 $ . It can be shown that under the given constraints such values always exist if any values exist at all.

## 说明/提示

In the first testcase buying any number of donuts will be cheaper in the second shop. For example, for $ 3 $ or $ 5 $ donuts you'll have to buy a box of $ 10 $ donuts for $ 4 $ dollars. $ 3 $ or $ 5 $ donuts in the first shop would cost you $ 15 $ or $ 25 $ dollars, respectively, however. For $ 20 $ donuts you'll have to buy two boxes for $ 8 $ dollars total. Note that $ 3 $ and $ 5 $ are also valid answers for the second shop, along with many other answers.

In the second testcase buying any number of donuts will be either cheaper in the first shop or the same price. $ 8 $ donuts cost $ 32 $ dollars in the first shop and $ 40 $ dollars in the second shop (because you have to buy two boxes). $ 10 $ donuts will cost $ 40 $ dollars in both shops, so $ 10 $ is not a valid answer for any of the shops.

In the third testcase $ 1 $ donut costs $ 2 $ and $ 3 $ dollars, respectively. $ 2 $ donuts cost $ 4 $ and $ 3 $ dollars. Thus, $ 1 $ is a valid answer for the first shop and $ 2 $ is a valid answer for the second shop.

In the fourth testcase $ 10^9 $ donuts cost $ 10^{18} $ dollars in the first shop and $ 10^9 $ dollars in the second shop.

## 样例 #1

### 输入

```
4
5 10 4
4 5 20
2 2 3
1000000000 1000000000 1000000000```

### 输出

```
-1 20
8 -1
1 2
-1 1000000000```

# AI分析结果


### 💡 Kay的C++算法解析：Donut Shops 深入学习指南 💡

<introduction>
  今天我们分析CF1373A「Donut Shops」。这道题考察数学推导和贪心思维，通过极端值分析解决。本指南将帮助你理解核心算法、掌握解题技巧，并通过像素动画直观感受决策过程。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用`（数学推导与贪心思维）

🗣️ **初步分析**：
> 这道题就像在两家超市买糖果：一家散卖（单价a），一家整盒卖（b个/盒，c元/盒）。解题关键是采用**贪心思想**——通过极端情况（买1个或1盒）快速决策，避免复杂计算。
>
>   - **核心思路**：第一家店最优情况是买1个（最小单位），第二家店最优是买1盒（b个）。比较这两种情况即可得到答案。
>   - **难点**：避免浮点数精度风险（用乘法代替除法）和超时（不循环枚举）。
>   - **可视化设计**：像素动画将展示两家店铺的价格比较过程，用不同颜色高亮关键决策点（如1个甜甜圈vs1盒），并添加8-bit音效增强记忆点。

---

## 2. 精选优质题解参考

<eval_intro>
  基于思路清晰度、代码规范性和算法效率，我精选了3份优质题解。它们均用整数运算避免精度问题，逻辑直击核心。

**题解一：zct_sky**  
* **亮点**：  
  最简洁的贪心实现。问题1直接比较`a`和`c`（买1个），问题2比较`a*b`和`c`（买1盒）。代码用`long long`防溢出，变量名清晰（`a,b,c`），边界处理严谨（如`a>=c`时无解）。实践价值高，可直接用于竞赛。

**题解四：Colorful_Unicorn**  
* **亮点**：  
  逻辑与题解一一致，但突出`#define int long long`的防溢出技巧。代码结构工整，主循环用`for`替代`while`，增强可读性。特别规范了输出格式（换行符`\n`），减少竞赛提交错误。

**题解七：b6e0_**  
* **亮点**：  
  用`signed main()`解决`#define int long long`的编译警告问题。注释强调“过于简单”体现对算法本质的洞察——复杂问题往往有简洁数学解。代码去冗余，`if-else`链高度优化，是高效编码的典范。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
  解决本题需突破三个关键难点，结合优质题解的策略如下：

1.  **难点一：如何避免浮点数精度风险？**
    * **分析**：比较单价时（如第二家店单价比`c/b`），用乘法`a*b > c`替代除法`c/b > a`。因`b≥2`，整数乘法不会溢出且无精度损失（题解1/4/7均采用）。
    * 💡 **学习笔记**：整数运算 > 浮点数——竞赛编程黄金准则。

2.  **难点二：为什么选择极端值（1个和1盒）？**
    * **分析**：贪心思想的本质——极值点往往是最优解候选。买1个是零售最小单位，买1盒是批发最小单位。数学证明：其他数量不会比这两个决策更优（题解13给出完整推导）。
    * 💡 **学习笔记**：当问题存在"最小单位"时，优先测试极端情况。

3.  **难点三：如何处理"严格小于"的边界条件？**
    * **分析**：`a>=c`时买1个不满足严格便宜（第一家花费≥第二家）；`a*b<=c`时买1盒不满足（第二家花费≥第一家）。所有题解统一用`if-else`处理，未引入复杂逻辑。
    * 💡 **学习笔记**：边界条件决定算法正确性——先列全数学不等式，再编码。

### ✨ 解题技巧总结
- **技巧一（极值分析法）**：将复杂购买策略简化为两个极值点（1和b）的决策。
- **技巧二（整数防溢）**：用`long long`存储`a*b`（最大`1e18`），避免`int`溢出。
- **技巧三（条件合并）**：用`if-else`链取代嵌套判断，提升代码可读性（如题解7）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
  以下通用代码融合优质题解精华，用整数运算实现贪心策略，完美处理边界：

**本题通用核心C++实现参考**
* **说明**：综合题解1/4/7的最佳实践，代码简洁且鲁棒性强。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    using namespace std;
    int main() {
        int t;
        cin >> t;
        while (t--) {
            long long a, b, c; // 防溢出
            cin >> a >> b >> c;
            
            // 问题1：买1个是否更便宜？
            if (a >= c) cout << "-1 ";
            else cout << "1 ";
            
            // 问题2：买1盒是否更便宜？
            if (a * b <= c) cout << "-1\n";
            else cout << b << "\n";
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 1. **输入处理**：多组数据循环（`t--`）。
    > 2. **问题1决策**：若散卖单价`a`≥整盒价`c`，则无解（输出`-1`）；否则买1个即满足。
    > 3. **问题2决策**：若散卖总价`a*b`≤整盒价`c`，则无解；否则买1盒（`b`个）即满足。

---
<code_intro_selected>
  下面解析优质题解中的核心代码片段，揭示精妙之处：

**题解一：zct_sky**
* **亮点**：8行代码解决战斗，完美体现"少即是多"。
* **核心代码片段**：
    ```cpp
    if(a>=c) cout<<"-1 ";
    else cout<<"1 ";
    if(a*b<=c) cout<<"-1\n";
    else cout<<b<<"\n";
    ```
* **代码解读**：
    > 前两行处理问题1：`a>=c`时无解，否则买1个。后两行处理问题2：`a*b<=c`时无解（注意`<=`包含相等），否则输出`b`。**为何用`<=`？** 因"严格小于"要求第二家花费必须`<`第一家，相等时不成立。
* 💡 **学习笔记**：条件运算符`<=`比`<`更安全——覆盖边界相等情况。

**题解四：Colorful_Unicorn**
* **亮点**：宏定义`#define int long long`彻底防溢出。
* **核心代码片段**：
    ```cpp
    if (e[i]>=q[i]*w[i]) cout<<"-1\n";
    else cout<<w[i]<<"\n";
    ```
* **代码解读**：
    > `q[i]*w[i]`计算散卖总价。**为何不先除？** 若用`e[i]/w[i]`计算单价会丢失精度（如`c=5, b=2`时单价应为2.5，整数除法得2）。乘法规避此风险。
* 💡 **学习笔记**：乘法代替除法——整数比较的经典技巧。

**题解七：b6e0_**
* **亮点**：`signed main()`解决`long long`宏的编译警告。
* **核心代码片段**：
    ```cpp
    if(c>=a*b) cout<<"-1\n";
    else cout<<b<<endl;
    ```
* **代码解读**：
    > 条件`c>=a*b`与题解1的`a*b<=c`等价，但更符合阅读习惯（"整盒价是否≥散卖总价"）。**为何用`endl`？** 比`"\n"`更易读，虽轻微影响效率（刷新缓冲区），但竞赛中可忽略。
* 💡 **学习笔记**：代码表达应优先考虑可读性，次优才是微观优化。

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
  设计名**「甜甜圈大作战」**的8-bit像素游戏，演示贪心决策过程。你将化身像素小人，通过购买决策收集甜甜圈！

* **主题**：FC红白机风格商店比较，含音效和关卡进度。
* **核心演示**：买1个 vs 买1盒的价格对比动画。
* **设计思路**：像素风格降低理解压力；音效强化关键操作；关卡制激励逐步学习。

**动画帧步骤**：
1. **场景初始化**（像素网格）：
   - 左侧商店：像素招牌"$a/个"，柜台摆单个甜甜圈（绿色像素块）。
   - 右侧商店：招牌"$c/盒"，货架放整盒甜甜圈（蓝色像素块，b个/盒）。
   - 控制面板：开始/暂停、单步执行、速度滑块（调速）。

2. **决策演示**（高亮+音效）：
   ```plaintext
   // 伪代码逻辑
   按[单步]键启动 → 小人走到第一家店
   if (a >= c): 
      显示红色"X" + 播放失败音效(短促"嘟") 
   else: 
      绿色甜甜圈放大闪烁 → 支付a金币 + 播放"叮！"音效
   
   按[单步] → 小人走到第二家店
   if (a*b <= c): 
      整盒变灰色 + 播放失败音效 
   else: 
      整盒旋转高亮 → 支付c金币 + 播放胜利音效(上扬旋律)
   ```

3. **动态数据展示**：
   - 顶部状态栏：实时显示`花费1 = a`，`花费2 = c`（问题1）；`花费1 = a*b`，`花费2 = c`（问题2）。
   - 比较结果：用像素箭头指向便宜选项（如`a < c`时箭头指向第一家店）。

4. **游戏化元素**：
   - **音效设计**：关键操作配8-bit音效（比较声"嘀"，支付声"叮"，胜利"🎵"）。
   - **关卡进度**：完成一个问题解锁一颗星，双解解锁皇冠特效。
   - **AI演示模式**：自动播放完整决策流程，像贪吃蛇AI一样逐步展示。

**技术实现**：Canvas绘制商店场景；Web Audio API播放音效；`requestAnimationFrame`控制帧率。

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
  掌握极值分析法后，可解决更多比较类问题。以下是相似思维模式的题目：

1.  **洛谷 P5717** - 三角形分类  
    * 🗣️ **推荐理由**：通过极端值（最大边）快速判断三角形类型，强化极值思维。

2.  **洛谷 P5719** - 分类平均  
    * 🗣️ **推荐理由**：用整数除法避免浮点数，直接比较两类数的均值，巩固乘法替代技巧。

3.  **洛谷 P1106** - 删数问题  
    * 🗣️ **推荐理由**：贪心策略的进阶应用——通过局部极值（最近高位）实现全局最优。

---

## 7. 学习心得与经验分享

<insights_intro>
  题解中虽无显性心得，但代码折射出宝贵经验：

> **隐含经验**：多组数据问题必须用`while(t--)`而非`for`（题解10曾误用导致超时）。  
> **Kay总结**：输入模式决定代码结构——竞赛中优先确认数据组数处理方式！

---

<conclusion>
  通过本次分析，我们学到：复杂问题可转化为极值决策（买1个/1盒），并用整数运算避免精度陷阱。记住Kay的秘诀："遇比较，想乘法；遇决策，试极端"。下次挑战见！🎮✨
</conclusion>

---
处理用时：229.41秒