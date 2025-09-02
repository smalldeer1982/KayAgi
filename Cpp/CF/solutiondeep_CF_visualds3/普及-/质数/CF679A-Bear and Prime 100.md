# 题目信息

# Bear and Prime 100

## 题目描述

This is an interactive problem. In the output section below you will see the information about flushing the output.

Bear Limak thinks of some hidden number — an integer from interval $ [2,100] $ . Your task is to say if the hidden number is prime or composite.

Integer $ x>1 $ is called prime if it has exactly two distinct divisors, $ 1 $ and $ x $ . If integer $ x>1 $ is not prime, it's called composite.

You can ask up to $ 20 $ queries about divisors of the hidden number. In each query you should print an integer from interval $ [2,100] $ . The system will answer "yes" if your integer is a divisor of the hidden number. Otherwise, the answer will be "no".

For example, if the hidden number is $ 14 $ then the system will answer "yes" only if you print $ 2 $ , $ 7 $ or $ 14 $ .

When you are done asking queries, print "prime" or "composite" and terminate your program.

You will get the Wrong Answer verdict if you ask more than $ 20 $ queries, or if you print an integer not from the range $ [2,100] $ . Also, you will get the Wrong Answer verdict if the printed answer isn't correct.

You will get the Idleness Limit Exceeded verdict if you don't print anything (but you should) or if you forget about flushing the output (more info below).

## 说明/提示

The hidden number in the first query is $ 30 $ . In a table below you can see a better form of the provided example of the communication process.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/b5d048578748c4adde3d49c36a749660a61701b4.png)

The hidden number is divisible by both $ 2 $ and $ 5 $ . Thus, it must be composite. Note that it isn't necessary to know the exact value of the hidden number. In this test, the hidden number is $ 30 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/f54f8d5adb5e9403a147185e0d841ee7fbfd7d7b.png)

 $ 59 $ is a divisor of the hidden number. In the interval $ [2,100] $ there is only one number with this divisor. The hidden number must be $ 59 $ , which is prime. Note that the answer is known even after the second query and you could print it then and terminate. Though, it isn't forbidden to ask unnecessary queries (unless you exceed the limit of $ 20 $ queries).

## 样例 #1

### 输入

```
yes
no
yes
```

### 输出

```
2
80
5
composite
```

## 样例 #2

### 输入

```
no
yes
no
no
no
```

### 输出

```
58
59
78
78
2
prime
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Bear and Prime 100 深入学习指南 💡

<introduction>
今天我们来一起分析“Bear and Prime 100”这道交互题。这道题需要通过最多20次询问，判断一个隐藏在[2,100]之间的数是质数还是合数。本指南将帮助大家梳理核心思路，理解关键步骤，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学（质数判断）与枚举应用`

🗣️ **初步分析**：
解决这道题的关键在于利用质数的性质，通过有限的询问覆盖所有可能的合数情况。简单来说，质数的定义是“只有1和自身两个因数”，而合数至少有三个因数（包括两个不同的质数或一个质数的平方）。在本题中，我们需要设计一组询问数，通过系统的“yes/no”反馈，快速判断隐藏数的性质。

- **核心思路**：  
  100以内的合数可分为两类：一类是能被至少两个不同质数整除的数（如30=2×3×5）；另一类是质数的平方（如4=2²、9=3²）。因此，我们需要询问两类数：  
  - **50以内的质数**（共15个：2,3,5,7,11,13,17,19,23,29,31,37,41,43,47）：若隐藏数能被其中两个或以上整除，必为合数。  
  - **质数的平方（≤100）**（共4个：4,9,25,49）：这些数是合数但只能被一个质数整除（如4只能被2整除），需单独询问。  

- **核心难点**：如何用不超过20次询问覆盖所有合数情况，尤其是平方数的特殊情况。  
- **解决方案**：将两类数合并为一个询问列表（共19个：15个质数+4个平方数），统计“yes”次数。若≥2次“yes”，则为合数；否则为质数。  

- **可视化设计思路**：采用8位像素风格动画，用网格表示可能的数（2-100），被询问的数用闪烁的像素方块标记，“yes”反馈时方块变绿色，“no”变红色。最终根据“yes”次数判断结果，伴随“胜利”或“提示”音效。


## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰度、代码规范性、算法有效性等方面的评估，以下3道题解因逻辑清晰、代码简洁且覆盖核心问题，被选为优质参考（评分≥4星）：
</eval_intro>

**题解一：作者PC_DOS（赞：7）**
* **点评**：此题解直接列出了关键的询问列表（15个质数+4个平方数），通过统计“yes”次数快速判断结果。代码结构简洁，变量命名清晰（如`arrAsk`存储询问数，`nCount`统计“yes”次数），边界处理严谨（提前终止循环）。亮点在于将平方数直接加入询问列表，避免了复杂的二次判断，降低了代码复杂度。

**题解二：作者lukelin（赞：7）**
* **点评**：此题解分两步询问：先询问质数，若得到“yes”则进一步询问其平方（如询问2后，再询问4）。这种分步策略更灵活，能减少不必要的询问次数（例如若某个质数的平方超过100则跳过）。代码中`cnt`变量明确统计有效“yes”次数，逻辑清晰，适合理解质数与平方数的关系。

**题解三：作者stdout（赞：3）**
* **点评**：此题解明确指出了常见错误（未考虑平方数导致WA），并通过预定义的询问列表（19个数）覆盖所有情况。代码中`q`数组直接存储所有需询问的数，循环遍历处理，简洁易读。亮点在于对错误场景的总结，帮助学习者避免常见陷阱。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题时，我们通常会遇到以下核心难点。结合优质题解的思路，我们逐一分析解决方案：
</difficulty_intro>

1.  **关键点1：如何覆盖所有合数情况？**  
    * **分析**：合数可能由两个不同质数相乘（如6=2×3），或一个质数的平方（如4=2²）。若仅询问质数，会漏掉平方数的情况（如4只能被2整除，无法通过两个“yes”判断）。优质题解通过额外询问平方数（4,9,25,49）解决此问题。  
    * 💡 **学习笔记**：特殊情况（如平方数）需要单独考虑，避免因遗漏导致错误。

2.  **关键点2：如何控制询问次数不超过20次？**  
    * **分析**：50以内的质数有15个，平方数有4个，总计19次询问（≤20次）。优质题解通过预定义列表或分步询问（先质数后平方），确保次数合规。例如，lukelin的题解在询问质数后，仅当质数的平方≤100时才二次询问，进一步优化次数。  
    * 💡 **学习笔记**：合理设计询问顺序和内容，是控制次数的关键。

3.  **关键点3：如何根据反馈快速判断结果？**  
    * **分析**：若“yes”次数≥2，直接判定为合数（因至少有两个因数）；若≤1次，则为质数（因质数只能被1和自身整除，而自身不在询问列表中）。优质题解通过实时统计“yes”次数，提前终止循环，提高效率。  
    * 💡 **学习笔记**：实时统计关键指标（如“yes”次数），可提前得出结论，避免多余操作。

### ✨ 解题技巧总结
- **问题分解**：将合数分为“多质因数”和“平方数”两类，分别设计询问策略。  
- **预定义列表**：将需询问的数预存在数组中，避免动态生成的复杂性。  
- **提前终止**：一旦满足条件（如“yes”次数≥2），立即输出结果并结束程序，节省次数。  


## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，我们先看一个综合优质题解的通用核心实现，帮助大家把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了PC_DOS和lukelin的思路，通过预定义询问列表（质数+平方数），统计“yes”次数判断结果。代码简洁高效，符合题目要求。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;

    int main() {
        // 预定义询问列表：15个质数 + 4个平方数（共19次）
        int askList[] = {2, 3, 4, 5, 7, 9, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};
        int yesCount = 0;
        string response;

        for (int num : askList) {
            cout << num << endl;
            fflush(stdout); // 必须刷新输出，避免交互延迟
            cin >> response;

            if (response == "yes") {
                yesCount++;
                if (yesCount >= 2) { // 至少两个因数，必为合数
                    cout << "composite" << endl;
                    return 0;
                }
            }
        }

        // 少于两个"yes"，为质数
        cout << "prime" << endl;
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先定义了需询问的数的列表（包含质数和平方数），然后遍历列表逐个询问。每次询问后读取反馈，若“yes”次数≥2，直接输出“composite”并结束程序；否则遍历结束后输出“prime”。关键逻辑是通过预定义列表覆盖所有可能的合数情况，确保在20次内完成判断。

---
<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段，学习其亮点和实现思路。
</code_intro_selected>

**题解一：作者PC_DOS**
* **亮点**：直接将质数和平方数合并为一个列表，代码简洁，无需额外判断。
* **核心代码片段**：
    ```cpp
    int arrAsk[19] = {2, 3, 4, 5, 9, 7, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};
    for (int i = 0; i <= 18; ++i) {
        cout << arrAsk[i] << endl;
        fflush(stdout);
        cin >> sAns;
        if (sAns[0] == 'y') {
            ++nCount;
            if (nCount >= 2) {
                cout << "composite";
                goto endapp;
            }
        }
    }
    ```
* **代码解读**：  
  `arrAsk`数组包含所有需询问的数。循环遍历数组，每次询问后统计“yes”次数。若次数≥2，立即输出“composite”并跳转结束。这种设计通过预定义列表简化了逻辑，适合快速实现。  
* 💡 **学习笔记**：预定义关键数据（如询问列表）可减少动态计算，提高代码可读性。

**题解二：作者lukelin**
* **亮点**：分步询问质数及其平方，灵活控制次数（仅当平方≤100时询问）。
* **核心代码片段**：
    ```cpp
    const int p_num = 15;
    int prime[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    for (int i = 0; i < p_num; ++i) {
        cout << prime[i] << endl;
        fflush(stdout);
        cin >> s;
        if (s[0] == 'y') {
            if ((prime[i] * prime[i]) <= 100) { // 仅询问平方≤100的情况
                cout << (prime[i] * prime[i]) << endl;
                fflush(stdout);
                cin >> s;
                if (s[0] == 'y') {
                    cout << "composite" << endl;
                    return 0;
                }
            }
            ++cnt;
            if (cnt >= 2) {
                cout << "composite" << endl;
                return 0;
            }
        }
    }
    ```
* **代码解读**：  
  首先询问质数，若得到“yes”反馈，则进一步询问该质数的平方（仅当平方≤100时）。若平方的反馈也是“yes”，则直接判定为合数；否则统计“yes”次数。这种策略避免了对大质数平方（如11²=121>100）的无效询问，优化了次数。  
* 💡 **学习笔记**：根据问题特性动态调整询问内容（如平方是否≤100），可提高效率。


## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解询问过程，我们设计一个“像素质数探测器”动画，以8位复古风格展示每一步询问和反馈，帮助大家“看”到算法如何判断质数或合数。
</visualization_intro>

  * **动画演示主题**：`像素质数探测器——寻找隐藏的数`  
  * **核心演示内容**：通过网格展示2-100的数，被询问的数闪烁，根据“yes/no”反馈改变颜色，最终根据“yes”次数判断结果。  

  * **设计思路简述**：  
    采用8位像素风格（如FC游戏画面），用不同颜色标记数的状态（未询问：灰色，询问中：黄色，“yes”：绿色，“no”：红色）。关键操作（如输出询问、接收反馈）伴随“叮”的音效，结果判定时播放“胜利”或“提示”音效，增强操作记忆和趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：  
        - 屏幕中央显示10×10的像素网格（对应2-100的数，每行10个），每个数用小方块表示（初始为灰色）。  
        - 下方控制面板包含“开始”“单步”“重置”按钮和速度滑块（1-5倍速）。  
        - 播放8位风格背景音乐（如《超级玛丽》经典旋律）。

    2.  **算法启动**：  
        - 点击“开始”，第一个询问数（如2）的方块开始闪烁（黄色），伴随“叮”的音效。  
        - 模拟系统反馈：若隐藏数是30（样例1），则2的方块变绿色（“yes”）；否则变红色（“no”）。  

    3.  **核心步骤演示**：  
        - 每完成一次询问，下一个数的方块开始闪烁，重复颜色变化逻辑。  
        - “yes”次数实时显示在屏幕上方（如“YES计数：1”）。  
        - 当“YES计数≥2”时，所有绿色方块高亮（闪烁绿色），屏幕中央弹出“COMPOSITE”字样，播放“胜利”音效（如《魂斗罗》胜利音）。  

    4.  **结果判定**：  
        - 若遍历完所有询问数后“YES计数≤1”，则隐藏数的方块（如59）变蓝色，屏幕弹出“PRIME”字样，播放“提示”音效（如短笛声）。  

    5.  **交互控制**：  
        - 支持“单步”模式：点击“单步”按钮，逐次执行询问；  
        - 支持“自动播放”：通过速度滑块调整播放速度（如1倍速为每2秒一步）；  
        - 点击“重置”按钮，清空所有颜色，重置计数，回到初始状态。  

  * **旁白提示**：  
    - （询问时）“现在询问数2，它是隐藏数的因数吗？”  
    - （反馈时）“得到‘yes’，说明2是隐藏数的因数，计数加1！”  
    - （结果时）“计数达到2，隐藏数是合数！”

<visualization_conclusion>
通过这样的像素动画，我们能直观看到每个询问的作用和反馈的影响，更深刻理解如何通过有限的询问判断质数或合数。


## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的质数判断和枚举技巧后，我们可以尝试以下拓展练习，巩固并深化理解：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    本题的核心是“通过有限询问覆盖目标集合的关键特征”，这种思路可迁移到其他交互题或枚举问题中。例如：  
    - 判断一个数是否为完全平方数（询问平方根附近的数）；  
    - 猜数字游戏（通过二分法减少询问次数）；  
    - 检测数组中的重复元素（询问特定区间的元素存在性）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1918 保龄球**  
        * 🗣️ **推荐理由**：交互题，需通过输入输出与系统交互，锻炼对询问策略的设计能力。  
    2.  **洛谷 P2678 跳石头**  
        * 🗣️ **推荐理由**：二分答案的典型应用，与本题“通过有限步骤逼近目标”的思想类似。  
    3.  **洛谷 P1075 质因数分解**  
        * 🗣️ **推荐理由**：直接考察质数与因数分解，帮助巩固质数相关知识。  


## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试中的经验，这些对我们很有参考价值：
</insights_intro>

> **参考经验 (来自作者stdout)**：“最初只询问了质数，结果被平方数（如4）坑了，后来添加了平方数的询问才通过。”  
> **点评**：这位作者的经验提醒我们，特殊情况（如平方数）容易被忽略，需要通过测试用例验证思路。在编程中，遇到错误时可手动模拟小例子（如测试隐藏数为4、9的情况），快速定位问题。


<conclusion>
本次关于“Bear and Prime 100”的分析就到这里。通过理解质数的性质、设计询问策略，以及分析优质题解的代码，我们掌握了如何通过有限询问判断质数或合数。希望大家在练习中多思考、多验证，不断提升编程能力！下次见～💪
</conclusion>

---
处理用时：137.83秒