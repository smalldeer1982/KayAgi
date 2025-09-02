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
今天我们要一起攻克的是交互题“Bear and Prime 100”。这道题的关键在于通过最多20次询问，判断一个隐藏在[2,100]之间的数是质数还是合数。跟着Kay的分析，我们会一步步理解核心思路、关键技巧，并通过可视化动画直观感受算法过程！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学判断与交互模拟` 

🗣️ **初步分析**：
解决这道题的核心是利用“合数的因数特性”。简单来说，一个合数（非质数）至少有两个不同的质因数（如15=3×5），或者是一个质数的平方（如4=2×2）。我们的任务是通过询问特定的数，根据“是否是隐藏数的因数”的回答，判断隐藏数的性质。

- **题解思路**：主流解法是先询问50以内的质数（共15个，如2,3,5...47），因为合数至少有一个这样的质因数；再补充询问这些质数的平方（如4=2²、9=3²等，共4个），避免漏掉仅含单个质因数但平方后仍≤100的合数（如49=7²）。若“yes”回答≥2次，直接判定为合数；否则为质数。
- **核心难点**：如何设计询问列表覆盖所有合数情况（普通合数和平方数），同时控制询问次数≤20次。
- **可视化设计**：采用8位像素风动画，用“询问框”显示当前询问的数，“回答灯”（绿色为yes，红色为no）反馈结果，动态统计“yes”次数。关键步骤高亮：当“yes”次数达到2次时，弹出“合数”标志；若遍历所有询问仍不足2次，弹出“质数”标志。动画中会有像素音效（“叮”表示yes，“咚”表示no）增强交互感。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等维度，以下3道题解因逻辑严谨、代码简洁被选为优质参考：
</eval_intro>

**题解一：作者lukelin（赞8）**
* **点评**：此题解思路清晰，精准抓住了“质数平方数”这一关键点。代码中先遍历50以内的质数，若某次询问得到“yes”，立即检查该质数的平方是否≤100（如2²=4≤100），并再次询问其平方是否为因数。若两次“yes”或累计“yes”≥2次，直接判定为合数。代码变量命名直观（如`p_num`、`prime`数组），边界处理严谨（平方数≤100的判断），实践价值高（可直接用于竞赛）。

**题解二：作者PC_DOS（赞7）**
* **点评**：此题解通过预定义包含质数和平方数的询问列表（如{2,3,4,5,9...49}），直接遍历列表统计“yes”次数。思路简洁直白，代码结构工整（单循环处理所有询问），适合新手理解。虽然未显式区分质数和平方数的逻辑，但通过预设计的列表巧妙覆盖了所有情况，是“打表法”的典型应用。

**题解三：作者stdout（赞3）**
* **点评**：此题解详细解释了“为何需要补充平方数”的逻辑（普通质数列表会漏掉4、9等情况），并给出了完整的询问列表（19个数）。代码中使用`register`优化循环变量，提升效率；`cnt`变量清晰统计“yes”次数，逻辑流畅。特别适合学习如何从问题分析到代码实现的完整推导过程。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的关键在于处理两类合数：多质因数合数和单质因数平方合数。以下是核心难点及应对策略：
</difficulty_intro>

1.  **关键点1：如何选择询问的数，覆盖所有合数？**
    * **分析**：普通合数（如15=3×5）至少有2个不同的质因数，因此询问50以内的质数（共15个）即可覆盖这类情况。但平方合数（如4=2×2）只有1个质因数，需额外询问这些质数的平方（如4、9、25、49）。
    * 💡 **学习笔记**：合数的因数特性是解题的“钥匙”，既要覆盖多质因数情况，也要处理平方数特例。

2.  **关键点2：如何控制询问次数不超过20次？**
    * **分析**：50以内的质数有15个，其平方数有4个（2²=4,3²=9,5²=25,7²=49），总共有15+4=19次询问，满足≤20次的限制。若某次询问后“yes”≥2次，可提前终止，节省次数。
    * 💡 **学习笔记**：提前终止是优化交互题的常用技巧，能有效减少不必要的询问。

3.  **关键点3：如何处理边界情况（如隐藏数是质数本身）？**
    * **分析**：若隐藏数是质数（如59），则只有它本身是其因数（在[2,100]范围内）。因此，若所有询问的质数和平方数均得到“no”，则判定为质数。
    * 💡 **学习笔记**：质数的因数唯一性是判定的最终依据。

### ✨ 解题技巧总结
- **打表法**：预定义关键数（质数+平方数）的列表，避免动态计算，减少出错。
- **提前终止**：一旦“yes”次数≥2次，立即输出结果，节省询问次数。
- **边界检查**：对质数的平方数需额外判断是否≤100（如11²=121>100，无需询问）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，覆盖了质数和平方数的询问，逻辑简洁且高效。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了lukelin和PC_DOS的思路，预定义质数列表和平方数列表，遍历询问并统计“yes”次数，提前终止判定。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;

    // 50以内的质数（15个）
    const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    // 质数的平方（≤100的，共4个）
    const int square_primes[] = {4, 9, 25, 49};

    int main() {
        string res;
        int cnt = 0;

        // 先询问质数列表
        for (int p : primes) {
            cout << p << endl;
            fflush(stdout); // 交互题必须刷新输出
            cin >> res;
            if (res == "yes") {
                cnt++;
                // 检查该质数的平方是否≤100，若是则追加询问
                if (p * p <= 100) {
                    cout << p * p << endl;
                    fflush(stdout);
                    cin >> res;
                    if (res == "yes") cnt++;
                }
                if (cnt >= 2) {
                    cout << "composite" << endl;
                    return 0;
                }
            }
        }

        // 再询问平方数列表（若前面未提前终止）
        for (int sq : square_primes) {
            cout << sq << endl;
            fflush(stdout);
            cin >> res;
            if (res == "yes") {
                cout << "composite" << endl;
                return 0;
            }
        }

        // 所有询问后仍未满足条件，判定为质数
        cout << "prime" << endl;
        return 0;
    }
    ```
* **代码解读概要**：代码首先遍历50以内的质数，对每个质数询问是否为隐藏数的因数。若得到“yes”，进一步询问其平方（若平方≤100）。若“yes”次数≥2，直接判定为合数。若质数列表遍历完仍不足2次“yes”，再检查平方数列表，若有“yes”则判定为合数，否则为质数。

---
<code_intro_selected>
接下来分析优质题解的核心代码片段，学习其中的巧妙思路：
</code_intro_selected>

**题解一：作者lukelin**
* **亮点**：动态检查质数的平方是否≤100，避免无效询问（如11²=121无需询问），节省次数。
* **核心代码片段**：
    ```cpp
    for (int i = 0; i < p_num; ++i) {
        cout << prime[i] << endl;
        fflush(stdout);
        cin >> s;
        if (s[0] == 'y') {
            if ((prime[i] * prime[i]) <= 100) {
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
* **代码解读**：这段代码遍历质数列表，每次询问后若得到“yes”，立即检查该质数的平方是否≤100。若是，再次询问平方数是否为因数。若两次“yes”或累计“yes”≥2次，直接输出合数。这种动态追加询问的方式，精准覆盖了平方数的情况。
* 💡 **学习笔记**：动态判断平方数是否需要询问，避免冗余操作，是优化交互题的关键技巧。

**题解二：作者PC_DOS**
* **亮点**：预定义包含质数和平方数的完整列表（19个数），通过单循环遍历，逻辑极简。
* **核心代码片段**：
    ```cpp
    int arrAsk[19] = { 2, 3, 4, 5, 9, 7, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49 };
    for (i = 0; i <= 18; ++i) { 
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
* **代码解读**：通过预定义的`arrAsk`数组（包含15个质数+4个平方数），遍历每个数并询问。若“yes”次数≥2次，直接输出合数。这种“打表法”代码简洁，适合新手理解。
* 💡 **学习笔记**：预定义关键数列表是解决交互题的常用方法，能简化逻辑并减少出错。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“如何通过询问判断质数/合数”，我们设计了一个8位像素风动画——《质数侦探社》！让我们化身小侦探，通过询问线索（因数）揭开隐藏数的真面目！
</visualization_intro>

  * **动画演示主题**：`质数侦探社——寻找隐藏数的秘密`

  * **核心演示内容**：屏幕左侧是“询问机器”（像素风格控制台），右侧是“隐藏数小屋”（一个带问号的像素房）。侦探（像素小人）每次向机器输入一个数（如2、3等），机器会弹出“yes”或“no”的灯牌（绿色/红色）。统计“yes”次数，当次数≥2时，小屋显示“合数”；否则显示“质数”。

  * **设计思路简述**：8位像素风格（类似FC游戏）降低学习门槛，通过“灯牌反馈”和“次数统计”直观展示算法逻辑。音效（“叮”表示yes，“咚”表示no）增强记忆点，“提前终止”的动画（侦探欢呼）强化成就感。

  * **动画帧步骤与交互关键点**：

    1.  **初始化场景**：
          - 背景：复古像素街道，“质数侦探社”招牌闪烁。
          - 界面：左侧控制台显示“询问次数：0/20”，右侧小屋显示“？”。
          - 音效：8位风格BGM（轻快的电子音乐）。

    2.  **开始询问**：
          - 侦探输入第一个数（如2），控制台弹出“询问2？”，小屋上方出现“2”的像素气泡。
          - 机器反馈“yes”（绿色灯牌亮起），控制台“询问次数”+1，音效“叮～”。

    3.  **关键步骤演示**：
          - 当“yes”次数达到2次时，小屋的问号变成“合数”（金色字体闪烁），侦探举手欢呼，音效“胜利！”（上扬音调）。
          - 若遍历所有询问后“yes”<2次，小屋显示“质数”（蓝色字体），侦探推眼镜点头，音效“正确～”。

    4.  **交互控制**：
          - 控制面板：单步按钮（逐次询问）、自动播放（加速演示）、重置（重新开始）。
          - 调速滑块：可调节动画速度（慢/中/快），适合不同学习节奏。

    5.  **游戏化元素**：
          - 关卡模式：每成功判断一个隐藏数（如30、59），解锁下一个“侦探等级”（见习→初级→高级）。
          - 积分系统：正确判断得10分，提前终止（次数少）额外加5分，激励高效思考。

  * **旁白提示**：
      - （询问质数时）“注意！如果隐藏数能被这个质数整除，可能是合数的线索哦～”
      - （询问平方数时）“这个数是某个质数的平方！如果隐藏数能被它整除，那肯定是合数～”
      - （“yes”≥2次时）“找到两个因数！隐藏数一定是合数，侦探任务完成！”

<visualization_conclusion>
通过这样的像素动画，我们能直观看到每次询问如何积累线索，最终锁定隐藏数的性质。动画中的交互和游戏化设计，让学习算法变得像玩游戏一样有趣！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题的“因数判断”思路后，我们可以尝试解决更多类似问题，巩固数学判断和交互题的处理技巧。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 本题的“因数特性分析”可迁移到其他数论问题（如判断完全平方数、分解质因数）。
      - 交互题的“提前终止”技巧适用于需要动态决策的场景（如二分查找、猜数字游戏）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1918 保龄球**  
        * 🗣️ **推荐理由**：交互题，需要通过输入输出动态调整策略，与本题的“询问-反馈”模式类似。
    2.  **洛谷 P1072 Hankson的趣味题**  
        * 🗣️ **推荐理由**：考察因数与倍数的关系，需结合数学分析和枚举，与本题的“因数判断”核心相关。
    3.  **洛谷 P2014 选课**  
        * 🗣️ **推荐理由**：动态规划与树形结构结合，锻炼问题分解能力，适合提升综合解题技巧。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些“踩坑”经历对我们很有启发：
</insights_intro>

> **参考经验 (来自作者stdout)**：“我最初只询问了质数列表，结果被4、9等平方数坑了。后来意识到需要补充质数的平方数，才通过了测试。”
>
> **点评**：这位作者的经验提醒我们，在设计算法时要考虑特殊情况（如平方数）。遇到错误时，通过分析反例（如4=2×2）可以快速定位问题。这对我们调试代码、完善逻辑非常有帮助！

-----

<conclusion>
通过今天的分析，我们掌握了“Bear and Prime 100”的核心思路：通过询问质数和平方数，统计“yes”次数判断质数或合数。记住，交互题的关键是设计高效的询问策略，同时覆盖所有可能情况。下一次遇到类似问题，你也能轻松解决啦！加油，未来的算法小达人～ 💪
</conclusion>

---
处理用时：143.17秒