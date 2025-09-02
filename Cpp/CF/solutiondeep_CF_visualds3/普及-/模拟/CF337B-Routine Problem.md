# 题目信息

# Routine Problem

## 题目描述

Manao has a monitor. The screen of the monitor has horizontal to vertical length ratio $ a $ : $ b $ . Now he is going to watch a movie. The movie's frame has horizontal to vertical length ratio $ c $ : $ d $ . Manao adjusts the view in such a way that the movie preserves the original frame ratio, but also occupies as much space on the screen as possible and fits within it completely. Thus, he may have to zoom the movie in or out, but Manao will always change the frame proportionally in both dimensions.

Calculate the ratio of empty screen (the part of the screen not occupied by the movie) to the total screen size. Print the answer as an irreducible fraction $ p/q $ .

## 说明/提示

Sample 1. Manao's monitor has a square screen. The movie has 3:2 horizontal to vertical length ratio. Obviously, the movie occupies most of the screen if the width of the picture coincides with the width of the screen. In this case, only 2/3 of the monitor will project the movie in the horizontal dimension: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337B/429cc762b90fac9b9969eeb0bd54bb3278635967.png)

Sample 2. This time the monitor's width is 4/3 times larger than its height and the movie's frame is square. In this case, the picture must take up the whole monitor in the vertical dimension and only 3/4 in the horizontal dimension: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337B/9da098e1ff076f33756d107ad7616fb9b6b441f1.png)

## 样例 #1

### 输入

```
1 1 3 2
```

### 输出

```
1/3
```

## 样例 #2

### 输入

```
4 3 2 2
```

### 输出

```
1/4
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Routine Problem 深入学习指南 💡

<introduction>
今天我们来一起分析“Routine Problem”这道C++编程题。这道题围绕屏幕与电影的长宽比例展开，需要计算屏幕空余部分的最小面积比。本指南将帮你梳理核心思路、解析优质题解，并通过生动的像素动画直观理解算法！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学（比例计算与分数化简）`

🗣️ **初步分析**：
解决这道题的关键是理解“如何让电影在屏幕上等比缩放后，空余部分最小”。简单来说，就像给照片调整尺寸——要么让照片的长边和屏幕长边对齐，要么让宽边对齐，选择其中空余更少的情况。

在本题中，数学的核心应用是：
1. **比例统一**：将屏幕和电影的比例统一到同一维度（长或宽），计算对应的另一维度长度。
2. **分数化简**：用最大公约数（GCD）将结果约分为最简分数。

### 核心思路与难点：
- **两种对齐方式**：电影的长与屏幕长对齐（情况1），或宽与屏幕宽对齐（情况2）。需比较两种情况下的空余比例，取更小的那个。
- **比例统一方法**：例如，长对齐时，将屏幕比例 $a:b$ 与电影比例 $c:d$ 统一前项（长），得到屏幕实际宽为 $b \times c$，电影实际宽为 $a \times d$。若 $b \times c \geq a \times d$，则电影宽不会超过屏幕宽，此时空余比例为 $(b \times c - a \times d)/(b \times c)$；否则需考虑宽对齐。
- **可视化设计**：用像素矩形模拟屏幕和电影，动态展示两种对齐方式下的尺寸变化，高亮空余部分，并用颜色区分不同情况（如红色表示长对齐，蓝色表示宽对齐）。

### 复古像素动画设计：
动画将采用8位像素风格，屏幕和电影用彩色方块表示。点击“单步执行”时，会先展示长对齐的计算过程（屏幕长方块与电影长方块重合，宽部分用虚线表示），再切换到宽对齐。关键步骤（如计算比例、比较大小）会伴随“叮”的音效，最终结果用金色高亮显示。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和算法有效性，以下3道题解因逻辑简洁、实现准确被选为优质参考：
</eval_intro>

**题解一：作者Vidoliga（赞：5）**
* **点评**：此题解思路直接，通过两种情况的数学推导明确了空余比例的计算方法。代码中使用`gcd`函数处理分数化简，变量名虽简单但逻辑清晰（如用`e`表示最大公约数）。亮点在于通过几何直观（图示）辅助理解，适合新手快速掌握核心逻辑。

**题解二：作者Yzmddsw（赞：1）**
* **点评**：此题解代码极其简洁，直接比较两种情况的条件（`b*c >= a*d`），并利用C++内置的`__gcd`函数完成分数化简。代码结构工整，边界条件处理（如避免负数）隐含在逻辑判断中，是竞赛风格的典型实现。

**题解三：封禁用户（赞：0）**
* **点评**：此题解对思路的解释非常详细（如统一前项/后项的步骤），代码注释清晰，适合对数学推导不太熟悉的学习者。虽然变量名较基础（如`Gcd`），但逻辑完整，且明确指出了约分的必要性，是理解问题的好材料。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题时，主要会遇到以下核心难点，我们逐一分析：
</difficulty_intro>

1.  **关键点1：如何确定对齐方式（长对齐还是宽对齐）**  
    * **分析**：需要比较两种对齐方式下电影的另一维度是否超出屏幕。例如，长对齐时，若电影的宽（计算为 $a \times d$）不超过屏幕的宽（计算为 $b \times c$），则长对齐可行；否则需选择宽对齐。  
    * 💡 **学习笔记**：判断条件是 `b*c >= a*d`，若成立则长对齐，否则宽对齐。

2.  **关键点2：如何计算空余比例**  
    * **分析**：长对齐时，空余比例为 $(b \times c - a \times d)/(b \times c)$；宽对齐时为 $(a \times d - b \times c)/(a \times d)$。这两个比例的分子是屏幕宽（或长）减去电影宽（或长），分母是屏幕的宽（或长）。  
    * 💡 **学习笔记**：比例的本质是“未被覆盖的部分”与“屏幕对应维度”的比值。

3.  **关键点3：如何将分数约分为最简形式**  
    * **分析**：需要计算分子和分母的最大公约数（GCD），然后将分子分母同时除以GCD。C++中可使用`__gcd`函数（需包含头文件`<algorithm>`）。  
    * 💡 **学习笔记**：约分是数学题的常见需求，GCD是解决这类问题的关键工具。

### ✨ 解题技巧总结
- **比例统一技巧**：将两个比例统一到同一维度（如长或宽），通过乘法消去前项或后项，便于比较。
- **边界条件处理**：通过逻辑判断（如`if (b*c >= a*d)`）避免计算负数比例。
- **分数化简**：利用GCD函数快速约分，确保输出为最简分数。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，提炼出一个简洁、通用的核心实现，帮助大家快速掌握完整解题流程。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Vidoliga和Yzmddsw的题解思路，逻辑清晰且符合竞赛风格，适合直接参考。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <algorithm> // 用于__gcd函数
    using namespace std;

    int main() {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;

        // 计算两种情况的分子和分母
        long long numerator1 = b * c - a * d;
        long long denominator1 = b * c;
        long long numerator2 = a * d - b * c;
        long long denominator2 = a * d;

        // 判断哪种情况更优（分子非负）
        if (numerator1 >= 0) {
            long long gcd = __gcd(numerator1, denominator1);
            cout << numerator1 / gcd << "/" << denominator1 / gcd << endl;
        } else {
            long long gcd = __gcd(numerator2, denominator2);
            cout << numerator2 / gcd << "/" << denominator2 / gcd << endl;
        }

        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取输入的屏幕比例（$a:b$）和电影比例（$c:d$），然后计算两种对齐方式下的分子和分母。通过判断第一种情况的分子是否非负（即长对齐是否可行），选择对应的分数并约分输出。核心逻辑集中在比例计算与条件判断上。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，学习其中的巧妙思路：
</code_intro_selected>

**题解一：作者Vidoliga**
* **亮点**：通过几何图示辅助理解，代码中明确区分两种情况的计算。
* **核心代码片段**：
    ```cpp
    LL a,b,c,d;
    scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
    double x=(double)(b*c-a*d)/(b*c),y=(double)(a*d-b*c)/(a*d);
    if(x>=y){
        int e=gcd((b*c-a*d),(b*c));
        printf("%lld/%lld\n",(b*c-a*d)/e,(b*c)/e);
    }
    else{
        int e=gcd((a*d-b*c),(a*d));
        printf("%lld/%lld\n",(a*d-b*c)/e,(a*d)/e);
    }
    ```
* **代码解读**：
    这段代码用`double`类型比较两种情况的空余比例（`x`和`y`），选择更小的那个。`gcd`函数计算分子分母的最大公约数，完成约分。例如，当`x >= y`时，说明长对齐的空余比例更小，输出对应的分数。
* 💡 **学习笔记**：用浮点数比较比例大小是直观的方法，但需注意精度问题（本题中因比例为整数运算，精度足够）。

**题解二：作者Yzmddsw**
* **亮点**：代码极简，直接通过条件判断选择情况，利用C++内置`__gcd`函数。
* **核心代码片段**：
    ```cpp
    ll a,b,c,d;
    cin>>a>>b>>c>>d;
    if(b*c >= a*d){
        cout<<(b*c-a*d)/__gcd(b*c-a*d,b*c)<<"/"<<b*c/__gcd(b*c-a*d,b*c);
    }
    else {
        cout<<(a*d-b*c)/__gcd(a*d-b*c,b*c)<<"/"<<a*d/__gcd(a*d-b*c,b*c);
    }
    ```
* **代码解读**：
    代码直接比较`b*c`和`a*d`的大小，若`b*c >= a*d`，则长对齐可行，计算并输出对应的分数；否则宽对齐。`__gcd`函数直接对分子分母取最大公约数，完成约分。
* 💡 **学习笔记**：竞赛中常用内置函数简化代码，`__gcd`是处理分数化简的利器。

**题解三：封禁用户**
* **亮点**：思路解释详细，代码注释清晰，适合新手理解。
* **核心代码片段**：
    ```cpp
    if(b*c>=a*d){
        int Gcd=__gcd(b*c-a*d,b*c);
        cout<<(b*c-a*d)/Gcd<<'/'<<(b*c)/Gcd<<endl; 
    } 
    else{
        int Gcd=__gcd(a*d-b*c,a*d);
        cout<<(a*d-b*c)/Gcd<<'/'<<(a*d)/Gcd<<endl; 
    }
    ```
* **代码解读**：
    这段代码与Yzmddsw的思路一致，但通过注释明确了每一步的作用（如“统一前项并约分”）。`Gcd`变量名直观，便于理解。
* 💡 **学习笔记**：清晰的注释能大大提高代码的可读性，尤其在团队协作或复习时。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“长对齐”和“宽对齐”的过程，我们设计了一个8位像素风格的动画，让你“看”到比例变化的每一步！
</visualization_intro>

  * **动画演示主题**：`像素屏幕与电影的适配之旅`

  * **核心演示内容**：展示屏幕（蓝色矩形）和电影（红色矩形）的两种适配方式：长对齐（电影长与屏幕长重合）和宽对齐（电影宽与屏幕宽重合），动态计算空余部分的面积比。

  * **设计思路简述**：采用FC红白机风格的像素画面，用不同颜色区分屏幕和电影，关键步骤（如比例计算、比较大小）用闪烁或音效提示，帮助学习者直观理解“为什么选择这种对齐方式”。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕用蓝色像素矩形表示，尺寸标注为“屏幕比例 $a:b$”。
        - 电影用红色像素矩形表示，尺寸标注为“电影比例 $c:d$”。
        - 控制面板包含“单步”“自动播放”按钮和速度滑块（1x-5x）。

    2.  **长对齐演示**：
        - 点击“单步”，屏幕和电影的长维度（水平方向）被统一（如屏幕长变为$a \times c$，电影长也变为$a \times c$）。
        - 电影的宽（垂直方向）计算为$a \times d$，用虚线表示。若$a \times d \leq b \times c$（屏幕宽），则电影完全在屏幕内，空余部分为$b \times c - a \times d$，用黄色像素填充。
        - 音效：“叮”一声提示计算完成。

    3.  **宽对齐演示**：
        - 切换到宽对齐，屏幕和电影的宽维度（垂直方向）被统一（如屏幕宽变为$b \times d$，电影宽也变为$b \times d$）。
        - 电影的长（水平方向）计算为$b \times c$，用虚线表示。若$b \times c \leq a \times d$（屏幕长），则空余部分为$a \times d - b \times c$，用绿色像素填充。
        - 音效：“叮”一声提示计算完成。

    4.  **结果比较**：
        - 自动比较两种对齐方式的空余比例，用金色箭头指向更小的那个。
        - 胜利音效：“啦~”提示找到最优解。

    5.  **AI自动演示**：
        - 点击“AI自动播放”，动画会自动完成长对齐和宽对齐的计算，并直接展示最优结果，像“小机器人”一样快速解决问题。

  * **旁白提示**：
    - “看！屏幕和电影的长被统一了，现在电影的宽是$a \times d$，屏幕的宽是$b \times c$。”
    - “如果电影的宽没超过屏幕宽，空余部分就是$b \times c - a \times d$哦！”
    - “现在比较两种情况的空余比例，选更小的那个就是答案啦~”

<visualization_conclusion>
通过这个像素动画，你不仅能看到比例计算的过程，还能直观理解“为什么选择这种对齐方式”。下次遇到比例问题，你也能像动画里的小机器人一样快速解决啦！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解了本题的比例计算和分数化简后，我们可以尝试以下拓展练习，巩固数学应用能力：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    本题的核心是“比例统一与比较”，这种思路还适用于：
    - 地图比例尺与实际距离的换算（统一比例尺后计算实际长度）。
    - 混合溶液的浓度计算（统一溶质或溶剂的量后比较浓度）。
    - 图像缩放时的分辨率调整（统一长或宽后计算另一维度的尺寸）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1328** - `生活大爆炸版石头剪刀布`  
        * 🗣️ **推荐理由**：这道题需要计算游戏得分，涉及比例和循环逻辑，能锻炼数学建模能力。
    2.  **洛谷 P1422** - `小玉家的电费`  
        * 🗣️ **推荐理由**：通过分段计算电费，巩固比例与分段函数的应用，适合练习条件判断。
    3.  **洛谷 P2433** - `小学数学 N 合一`  
        * 🗣️ **推荐理由**：综合了多种数学问题（包括比例计算），能全面检验数学应用能力。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了解题时的小经验，这些对我们很有启发：
</insights_intro>

> **参考经验 (来自封禁用户)**：“刚开始我没考虑到两种对齐方式，直接用了一种情况计算，结果样例没通过。后来仔细看题目提示的图示，才明白要比较两种情况。”
>
> **点评**：这位作者的经验提醒我们，遇到比例问题时要多维度思考（如长和宽），通过图示或样例验证思路的正确性。动手画一画、模拟计算，是避免遗漏的好方法！

-----

<conclusion>
本次关于“Routine Problem”的分析就到这里。通过理解比例统一、分数化简和两种对齐方式的比较，相信你已经掌握了这类问题的核心解法。记住，遇到数学问题时，先理清逻辑（如本题的两种情况），再用代码实现，就能轻松解决！下次见~ 💪
</conclusion>

---
处理用时：146.31秒