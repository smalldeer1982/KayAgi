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
今天我们来一起分析“Bear and Prime 100”这道交互题。这道题需要通过最多20次询问，判断一个2-100之间的隐藏数是质数还是合数。本指南将帮你梳理核心思路，解析优质题解，并通过像素动画直观理解算法过程！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`枚举与数学判断` 

🗣️ **初步分析**：
解决这道题的关键在于通过有限次询问，快速判断隐藏数的因数特征。简单来说，我们需要枚举可能的因数（质数及其平方），并根据回答的“yes”次数判断结果。  
- **核心思路**：质数的因数只有1和自身，而合数至少有两个不同的因数（或一个因数的平方）。因此，我们需要询问所有50以内的质数（共15个，如2、3、5等），以及这些质数的平方（如4=2²、9=3²等，共4个）。若“yes”回答≥2次，说明隐藏数有至少两个不同因数（或一个平方因数），必为合数；否则为质数。  
- **核心难点**：如何覆盖所有可能的合数情况（尤其是平方数，如4、9等，它们只有一个质因数但本身是合数）。优质题解通过额外询问质数的平方数解决了这一问题。  
- **可视化设计**：我们将设计一个8位像素风格的“因数侦探”动画，用像素方块代表询问的数（质数标绿色，平方数标黄色），隐藏数用问号方块表示。每次询问时，对应方块闪烁，回答“yes”则变亮，“no”则变暗。当“yes”≥2次时，触发“合数”提示音效；否则触发“质数”提示。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度筛选了以下优质题解（≥4星）：
</eval_intro>

**题解一：作者lukelin**  
* **点评**：此题解逻辑严谨，首先枚举50以内的质数，若得到“yes”则进一步检查该质数的平方是否≤100（如2²=4≤100，而11²=121>100无需检查）。若平方数也是因数，则直接判定为合数。代码中变量`cnt`统计“yes”次数，逻辑简洁。亮点在于对平方数的精准处理（仅检查≤100的平方），避免多余询问。

**题解二：作者PC_DOS**  
* **点评**：此题解将质数和平方数合并为一个询问列表（共19个数），直接遍历询问。若“yes”≥2次则判定合数。代码通过`arrAsk`数组明确列出所有需要询问的数（如2、3、4、5、9等），结构清晰。亮点在于将质数与平方数统一处理，减少分支判断，代码更易读。

**题解三：作者stdout**  
* **点评**：此题解详细解释了“平方数陷阱”（如4=2²仅能被2整除），并通过添加4、9、25、49到询问列表解决。代码中`q`数组包含19个关键数，循环询问并统计“yes”次数。亮点在于对错误原因的反思（如最初未考虑平方数导致WA），对学习者有启发意义。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的关键在于覆盖所有可能的合数情况。以下是三个核心难点及应对策略：
</difficulty_intro>

1.  **关键点1：如何选择需要询问的数？**  
    * **分析**：50以内的质数（如2、3、5等）是判断合数的基础，因为任何合数至少能被一个质数整除。但像4（2²）、9（3²）等平方数，虽然只能被一个质数整除，但本身是合数，需额外询问这些平方数。  
    * 💡 **学习笔记**：质数的平方（≤100）是特殊合数，需单独加入询问列表。

2.  **关键点2：如何根据回答次数判断结果？**  
    * **分析**：若“yes”回答≥2次，说明隐藏数有至少两个不同因数（或一个平方因数），必为合数；若“yes”≤1次，则为质数（或仅被一个质数整除且其平方不是因数）。  
    * 💡 **学习笔记**：“yes”次数≥2是判断合数的充分条件。

3.  **关键点3：如何控制询问次数不超过20次？**  
    * **分析**：50以内的质数有15个，加上4个平方数（4、9、25、49），共19次询问，符合20次限制。优质题解通过合并质数与平方数列表，确保次数合规。  
    * 💡 **学习笔记**：合理设计询问列表是控制次数的关键。

### ✨ 解题技巧总结
- **问题分解**：将问题拆解为“判断是否有多个质因数”和“判断是否为平方数”两部分，分别处理。  
- **列表预定义**：预定义需要询问的质数和平方数列表，避免动态计算，减少错误。  
- **及时终止**：一旦“yes”次数≥2，立即输出“composite”并终止，节省次数。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合多个优质题解，提炼出一个逻辑清晰、覆盖所有情况的核心实现。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合lukelin和PC_DOS的思路，预定义质数和平方数列表，遍历询问并统计“yes”次数，确保覆盖所有合数情况。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;

    // 50以内的质数（15个）和它们的平方（≤100，共4个）
    const int ask_list[] = {2, 3, 4, 5, 7, 9, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};

    int main() {
        string res;
        int cnt = 0;
        for (int num : ask_list) {
            cout << num << endl;
            fflush(stdout); // 交互题必须刷新输出
            cin >> res;
            if (res == "yes") {
                cnt++;
                if (cnt >= 2) { // 出现2次及以上yes，必为合数
                    cout << "composite" << endl;
                    return 0;
                }
            }
        }
        // 所有询问后cnt≤1，为质数
        cout << "prime" << endl;
        return 0;
    }
    ```
* **代码解读概要**：  
  代码首先定义了需要询问的数列表（包含质数和平方数），然后遍历每个数进行询问。每次询问后检查回答，若“yes”次数≥2则立即输出“composite”并终止；否则遍历结束后输出“prime”。

---
<code_intro_selected>
接下来，我们分析优质题解的核心代码片段，学习其亮点：
</code_intro_selected>

**题解一：作者lukelin**  
* **亮点**：动态检查质数的平方是否≤100，避免多余询问（如11²=121>100无需询问）。
* **核心代码片段**：
    ```cpp
    const int p_num = 15;
    int prime[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

    for (int i = 0; i < p_num; ++i) {
        cout << prime[i] << endl;
        fflush(stdout);
        cin >> s;
        if (s[0] == 'y') {
            if ((prime[i] * prime[i]) <= 100) { // 仅检查平方≤100的质数
                cout << (prime[i] * prime[i]) << endl;
                fflush(stdout);
                cin >> s;
                if (s[0] == 'y') { // 平方数是因数，直接判定合数
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
  这段代码遍历质数列表，每次询问后若得到“yes”，则进一步询问该质数的平方（仅当平方≤100时）。若平方数也是因数，直接判定合数；否则统计“yes”次数。这种动态检查避免了对大质数平方的无效询问（如11²=121>100无需询问），节省次数。  
* 💡 **学习笔记**：动态判断条件（如平方是否≤100）可减少不必要的操作，提升效率。

**题解二：作者PC_DOS**  
* **亮点**：将质数和平方数合并为一个列表，代码简洁，逻辑直接。
* **核心代码片段**：
    ```cpp
    int arrAsk[19] = {2, 3, 4, 5, 9, 7, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};

    for (int i = 0; i <= 18; ++i) {
        cout << arrAsk[i] << endl;
        fflush(stdout);
        cin >> sAns;
        if (sAns[0] == 'y') {
            ++nCount;
        }
        if (nCount >= 2) {
            cout << "composite";
            goto endapp;
        }
    }
    ```
* **代码解读**：  
  这段代码通过预定义的`arrAsk`数组（包含质数和平方数），直接遍历询问。每次询问后统计“yes”次数，若≥2次则立即判定合数。这种“预列表”方法避免了复杂的条件判断，代码更易维护。  
* 💡 **学习笔记**：预定义关键数据列表（如质数、平方数）可简化逻辑，减少错误。

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解询问过程，我们设计了“因数侦探”8位像素动画，用复古风格展示每一步询问和判断！
</visualization_intro>

  * **动画演示主题**：`像素因数侦探：寻找隐藏数的秘密`  
  * **核心演示内容**：模拟与隐藏数的交互过程，展示每次询问的数（质数标绿色，平方数标黄色）、系统回答（“yes”时方块变亮，“no”变暗），以及最终“质数”或“合数”的判定。  
  * **设计思路简述**：8位像素风格（如FC游戏画面）营造轻松氛围；颜色区分质数与平方数，帮助学习者识别关键数；音效（“叮”提示询问，“胜利”音效提示判定）强化操作记忆。  

  * **动画帧步骤与交互关键点**：
    1.  **场景初始化**：  
        - 背景为像素风格的“侦探事务所”，顶部显示“剩余询问次数：20”（随询问减少）。  
        - 左侧排列19个询问数（质数绿方块，平方数黄方块），右侧为隐藏数的“？”方块（灰色）。  
        - 控制面板：单步/自动播放按钮、速度滑块（调节动画快慢）。  

    2.  **算法启动**：  
        - 第一个询问数（如2）从列表弹出，移动到隐藏数方块前，伴随“叮”的音效。  
        - 隐藏数方块闪烁，显示“yes”或“no”文字，对应询问数方块变亮（yes）或变暗（no）。  

    3.  **核心步骤演示**：  
        - 每次询问后，“剩余次数”减1。若“yes”次数≥2，隐藏数方块变为红色，弹出“composite”文字，播放上扬的胜利音效。  
        - 若遍历完所有询问且“yes”≤1次，隐藏数方块变为蓝色，弹出“prime”文字，播放轻快音效。  

    4.  **交互控制**：  
        - 单步模式：点击“下一步”逐次执行询问；自动模式：按设定速度自动播放。  
        - 重置按钮：回到初始状态，重新开始演示。  

    5.  **旁白提示**：  
        - （询问2时）“现在询问2是否是隐藏数的因数，注意看回答！”  
        - （“yes”次数≥2时）“发现两个因数，隐藏数是合数！”  

<visualization_conclusion>
通过这个动画，你可以直观看到每次询问的影响，理解为什么“yes”≥2次就能判定合数，轻松掌握核心逻辑！
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
本题的关键在于通过枚举关键数判断因数特征，这种思路可迁移到其他需要“有限次询问”或“因数判断”的问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - 判断数的性质（如质数、平方数）时，可通过枚举关键因数（如小质数）快速缩小范围。  
    - 交互题中需注意输出刷新（如`fflush(stdout)`），避免因缓冲导致错误。  

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1959** - `遗址`  
        * 🗣️ **推荐理由**：同样涉及因数判断，需通过有限次操作确定结果，可巩固“枚举关键数”的思路。  
    2.  **洛谷 P1125** - `笨小猴`  
        * 🗣️ **推荐理由**：需判断字符串中字母出现次数是否为质数，练习质数判断的基础逻辑。  
    3.  **洛谷 P2014** - `选课`  
        * 🗣️ **推荐理由**：虽然是树形DP，但需枚举关键节点，培养“分解问题”的思维。  

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，对我们很有启发：
</insights_intro>

> **参考经验 (来自作者stdout)**：“最初没考虑平方数（如4、9），直接询问质数列表导致WA。后来意识到这些数只能被一个质数整除但本身是合数，于是添加平方数到询问列表，最终通过。”  
> **点评**：这位作者的经验提醒我们，特殊情况（如平方数）容易被忽略。在解题时，需多举反例验证思路，确保覆盖所有可能情况。遇到错误时，通过分析测试用例（如4、9）定位问题，是有效的调试方法。

---

<conclusion>
通过今天的分析，相信你已经掌握了“Bear and Prime 100”的核心解法！记住，遇到交互题要注意输出刷新，遇到质数判断要考虑平方数等特殊情况。多练习、多思考，你会越来越熟练！下次见~ 💪
</conclusion>

---
处理用时：120.05秒