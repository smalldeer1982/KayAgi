# 题目信息

# New Year and North Pole

## 题目描述

In this problem we assume the Earth to be a completely round ball and its surface a perfect sphere. The length of the equator and any meridian is considered to be exactly $ 40000 $ kilometers. Thus, travelling from North Pole to South Pole or vice versa takes exactly $ 20000 $ kilometers.

Limak, a polar bear, lives on the North Pole. Close to the New Year, he helps somebody with delivering packages all around the world. Instead of coordinates of places to visit, Limak got a description how he should move, assuming that he starts from the North Pole. The description consists of $ n $ parts. In the $ i $ -th part of his journey, Limak should move $ t_{i} $ kilometers in the direction represented by a string $ dir_{i} $ that is one of: "North", "South", "West", "East".

Limak isn’t sure whether the description is valid. You must help him to check the following conditions:

- If at any moment of time (before any of the instructions or while performing one of them) Limak is on the North Pole, he can move only to the South.
- If at any moment of time (before any of the instructions or while performing one of them) Limak is on the South Pole, he can move only to the North.
- The journey must end on the North Pole.

Check if the above conditions are satisfied and print "YES" or "NO" on a single line.

## 说明/提示

Drawings below show how Limak's journey would look like in first two samples. In the second sample the answer is "NO" because he doesn't end on the North Pole.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750B/9bb594fe352848bbba36035935a49c02ad65109a.png)

## 样例 #1

### 输入

```
5
7500 South
10000 East
3500 North
4444 West
4000 North
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
15000 South
4000 East
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
20000 South
1000 North
1000000 West
9000 North
10000 North
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
3
20000 South
10 East
20000 North
```

### 输出

```
NO
```

## 样例 #5

### 输入

```
2
1000 North
1000 South
```

### 输出

```
NO
```

## 样例 #6

### 输入

```
4
50 South
50 North
15000 South
15000 North
```

### 输出

```
YES
```

# AI分析结果



---
# 💡 Kay的C++算法解析：New Year and North Pole 深入学习指南 💡

<introduction>
今天我们来一起分析“New Year and North Pole”这道C++编程题。这道题主要考察我们对移动规则的模拟和边界条件的判断，通过分析可以帮助我们掌握如何将实际问题转化为代码逻辑。让我们一步步拆解，轻松掌握解题关键！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟应用

🗣️ **初步分析**：
解决这道题的关键在于“模拟”Limak的移动过程，并严格检查每一步是否符合规则。简单来说，“模拟”就像我们玩游戏时一步步操作角色，每一步都要检查是否触发了游戏规则中的限制。在本题中，规则限制包括：北极点只能向南走、南极点只能向北走、最终必须回到北极点。

- **题解思路**：所有优质题解都抓住了核心——忽略东西方向（因为不影响纬度），只关注南北移动的纬度变化。通过一个变量（如`s`、`sum`、`road`）记录当前纬度（离北极的距离），逐步骤检查每一步是否违反规则。
- **核心难点**：如何正确判断“在北极/南极时的方向限制”以及“移动后是否越界”。例如，在北极点（纬度0）时，若方向不是“South”则直接失败；移动后纬度若超过20000（南极点）或小于0（北极点以北）也失败。
- **可视化设计**：我们可以用一个像素化的地球仪，中间用竖条表示纬度（0是北极，20000是南极）。每一步移动时，用箭头指示方向（南/北），竖条长度动态变化。当触发规则错误时（如北极点向北走），屏幕闪烁红色并播放提示音效；最终回到北极时，播放胜利音效并显示“YES”。

---

## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰度、代码规范性、算法有效性等维度评估，以下3道题解因逻辑简洁、代码规范、关键判断准确，被选为优质参考：
</eval_intro>

**题解一：作者Hanghang**
* **点评**：这份题解思路非常清晰，直接抓住“纬度变化”这一核心，用变量`s`记录当前纬度。代码注释详细（如“万能头大法好”“别忘了return 0的好习惯”），变量名简洁易懂。关键判断（北极点/南极点方向限制、越界检查）一步到位，没有冗余操作。从实践角度看，代码可以直接用于竞赛，边界处理严谨（如`if(s<0||s>20000)`检查越界），是初学者学习模拟类问题的优秀模板。

**题解二：作者流绪**
* **点评**：此题解结构紧凑，用`flag`变量标记是否合法，逻辑一目了然。变量名`sum`直观表示“累计纬度”，符合直觉。代码中对方向的判断（如`s[0]=='S'`）通过首字母简化输入处理，减少了不必要的字符串比较，提升了效率。最终检查`sum`是否为0的逻辑直接对应题目“回到北极”的要求，是典型的“问题-代码”直接映射。

**题解三：作者Node_Edge**
* **点评**：此题解代码简洁，变量名`l`（latitude，纬度）含义明确。通过`ios::sync_with_stdio(false)`优化输入速度，适合竞赛场景。关键判断（北极点/南极点方向限制、越界检查）顺序合理，一旦发现不合法立即输出“NO”并退出，避免无效计算。代码风格工整，是“短平快”解决模拟问题的典范。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们需要重点关注以下3个核心难点，并掌握对应的解决策略：
</difficulty_intro>

1.  **关键点1：如何处理北极点/南极点的方向限制？**
    * **分析**：北极点（纬度0）只能向南走，南极点（纬度20000）只能向北走。在代码中，需要在每一步移动前检查当前纬度是否为0或20000，并判断方向是否符合要求。例如，若当前纬度是0但方向不是“South”，则直接输出“NO”。
    * 💡 **学习笔记**：北极和南极是“方向禁区”，必须优先检查方向是否合法。

2.  **关键点2：如何判断移动后是否越界？**
    * **分析**：纬度的合法范围是0到20000（包含边界）。向南移动会增加纬度（`s += t_i`），向北移动会减少纬度（`s -= t_i`）。移动后若纬度超出0-20000范围（如向南走超过20000到南极以南），则直接失败。
    * 💡 **学习笔记**：纬度是“一维坐标”，越界判断只需检查上下限。

3.  **关键点3：如何确保最终回到北极？**
    * **分析**：所有移动结束后，必须检查纬度是否为0。即使过程都合法，若最终纬度不为0（如停在南极或中间某点），仍需输出“NO”。
    * 💡 **学习笔记**：最终状态是问题的“终点条件”，必须最后验证。

### ✨ 解题技巧总结
<summary_best_practices>
- **忽略无关操作**：东西方向不影响纬度，直接跳过处理，减少代码复杂度。
- **提前终止**：一旦发现不合法操作（如北极点向北走），立即输出“NO”并退出，避免无效计算。
- **变量命名直观**：用`latitude`、`sum`等变量名明确表示纬度，提升代码可读性。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路后提炼的通用核心代码，逻辑清晰、结构简洁，适合直接学习和应用。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Hanghang、流绪等优质题解的思路，重点突出纬度变化的模拟和边界条件检查，是解决本题的典型实现。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;

    int main() {
        int n, latitude = 0; // latitude表示当前离北极的距离（0为北极，20000为南极）
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int t;
            string dir;
            cin >> t >> dir;

            // 检查北极点/南极点的方向限制
            if (latitude == 0 && dir != "South") {
                cout << "NO" << endl;
                return 0;
            }
            if (latitude == 20000 && dir != "North") {
                cout << "NO" << endl;
                return 0;
            }

            // 更新纬度（东西方向不影响，直接跳过）
            if (dir == "South") {
                latitude += t;
            } else if (dir == "North") {
                latitude -= t;
            }

            // 检查是否越界（超过北极或南极）
            if (latitude < 0 || latitude > 20000) {
                cout << "NO" << endl;
                return 0;
            }
        }

        // 最终必须回到北极
        cout << (latitude == 0 ? "YES" : "NO") << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取移动次数`n`，用`latitude`变量记录当前纬度（初始为0，北极）。通过循环处理每一步移动：先检查当前是否在北极/南极并方向是否合法；然后根据方向更新纬度（南北方向改变纬度，东西方向无影响）；最后检查纬度是否越界。所有步骤完成后，检查是否回到北极，输出结果。

---
<code_intro_selected>
接下来，我们分析优质题解中的核心代码片段，学习其中的巧妙思路。
</code_intro_selected>

**题解一：作者Hanghang**
* **亮点**：代码注释详细，关键判断逻辑清晰，直接处理纬度变化和边界条件。
* **核心代码片段**：
    ```cpp
    if(s==0&&y!="South") {
        cout<<"NO"<<endl;return 0;
    }
    if(s==20000&&y!="North") {
        cout<<"NO"<<endl;return 0;
    }
    if(y=="South")s+=x;
    if(y=="North")s-=x;
    if(s<0||s>20000) {
        cout<<"NO"<<endl;return 0;
    }
    ```
* **代码解读**：
    > 这段代码是模拟的核心。首先检查当前是否在北极（`s==0`）且方向不是南，或在南极（`s==20000`）且方向不是北，若违反则直接输出“NO”。然后根据方向更新纬度（南加北减）。最后检查纬度是否越界（小于0或大于20000），越界则输出“NO”。每一步都紧扣题目规则，逻辑直白。
* 💡 **学习笔记**：模拟问题的关键是“按规则逐条检查”，每一步都不能遗漏条件。

**题解二：作者流绪**
* **亮点**：用`flag`标记是否合法，代码结构紧凑，适合快速实现。
* **核心代码片段**：
    ```cpp
    if(!sum && s[0]!='S') flag = 0;
    if(sum==20000&&s[0]!='N') flag = 0;
    if(s[0]=='N') sum-=x;
    if(s[0]=='S') sum+=x;
    if(sum<0||sum>20000) flag = 0;
    ```
* **代码解读**：
    > 这段代码通过`sum`记录纬度，`flag`初始为1（合法）。若在北极（`sum==0`）且方向首字母不是'S'（南），或在南极（`sum==20000`）且方向首字母不是'N'（北），则`flag`置0（不合法）。然后根据方向更新`sum`，并检查是否越界。最后通过`flag`和`sum`是否为0判断结果。
* 💡 **学习笔记**：用标记变量统一管理合法性，避免多次输出“NO”，代码更简洁。

**题解三：作者Node_Edge**
* **亮点**：代码简洁高效，通过`ios::sync_with_stdio(false)`优化输入速度。
* **核心代码片段**：
    ```cpp
    if(l==0&&s!="South") {
        cout<<"NO"<<endl;return 0;
    }
    if(l==20000&&s!="North") {
        cout<<"NO"<<endl;return 0;
    }
    if(s=="South") l+=m;
    if(s=="North") l-=m;
    if(l<0||l>20000) {
        cout<<"NO"<<endl;return 0;
    }
    ```
* **代码解读**：
    > 这段代码用`l`表示纬度，每一步先检查北极/南极的方向限制，再更新纬度，最后检查越界。逻辑与题目规则一一对应，没有冗余操作，适合竞赛场景。
* 💡 **学习笔记**：竞赛中，简洁的代码能减少出错概率，提高编写速度。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解模拟过程，我们设计一个“极地探险家”像素动画，用8位复古风格展示Limak的移动和规则检查！
</visualization_intro>

  * **动画演示主题**：`像素极地探险——Limak的包裹之旅`

  * **核心演示内容**：展示Limak从北极出发，每一步移动的方向和纬度变化，高亮北极/南极的方向限制，以及最终是否回到北极。

  * **设计思路简述**：采用8位像素风格（类似FC游戏），用简单的图形和颜色区分北极（白色）、南极（蓝色）、当前位置（黄色圆点）。每一步移动时，用箭头指示方向（南↓/北↑），纬度条动态变化。音效（如“叮”提示合法移动，“咚”提示违规）增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕左侧显示像素地球仪（圆形，上下分别标“北极”“南极”），右侧显示纬度条（0-20000刻度，黄色滑块表示当前纬度）。
          * 控制面板：单步/自动播放按钮、速度滑块（1x-5x）、重置按钮。
          * 播放8位风格的轻快背景音乐（如《超级玛丽》主题变奏）。

    2.  **移动模拟**：
          * 输入每一步的`t`和`dir`，点击“开始”后，动画逐步骤执行：
            - **方向检查**：若当前在北极且方向不是南，地球仪闪烁红色，播放“咚”音效，显示“NO”并暂停。
            - **纬度更新**：向南移动时，黄色滑块向下滑动（纬度增加）；向北移动时向上滑动（纬度减少）。伴随“唰”的滑动音效。
            - **越界检查**：若滑块超出0-20000范围，地球仪闪烁红色，播放“咚”音效，显示“NO”并暂停。

    3.  **最终检查**：
          * 所有步骤完成后，若滑块停在0刻度（北极），播放“胜利”音效（如《超级玛丽》吃蘑菇音效），显示“YES”；否则播放“失败”音效，显示“NO”。

    4.  **交互功能**：
          * 单步模式：点击“下一步”逐步骤查看移动过程，适合仔细观察。
          * 自动模式：选择速度后自动播放，适合整体流程理解。
          * 重置：点击后回到初始状态（北极，纬度0），可重新输入数据演示。

  * **旁白提示**：
      - （方向检查时）“注意！现在在北极，只能向南走哦～”
      - （纬度更新时）“向南走了t公里，纬度增加到sum！”
      - （越界时）“糟糕！超过南极了，这样不合法～”

<visualization_conclusion>
通过这个像素动画，我们可以直观看到每一步移动是否符合规则，纬度如何变化，以及最终是否回到北极。这种“看得见”的模拟能帮助我们更深刻理解题目逻辑！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是“模拟+边界检查”，这类问题在编程竞赛中很常见。掌握后可以迁移到更多需要逐步骤验证规则的场景！
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 模拟类问题：如游戏角色移动规则检查（如走迷宫时的障碍判断）。
      - 状态跟踪问题：如电梯运行状态（当前楼层、上下方向限制）。
      - 流程验证问题：如自动售货机的操作步骤是否合法（投币、选商品、找零顺序）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1042** - `乒乓球`
          * 🗣️ **推荐理由**：需要模拟乒乓球比赛的得分过程，检查每一局的结束条件（如一方先得11分且领先2分），锻炼规则模拟能力。
    2.  **洛谷 P1067** - `多项式输出`
          * 🗣️ **推荐理由**：根据输入的系数和指数，模拟多项式的输出格式（如符号、系数为0的项省略），培养细节处理能力。
    3.  **洛谷 P1098** - `字符串的展开`
          * 🗣️ **推荐理由**：需要根据给定规则展开字符串（如“a-d”展开为“abcd”），并处理多种边界情况（如数字、大小写），提升模拟的全面性。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中，部分作者提到“弱鸡刚开始写题解，求通过”等，但未包含具体的调试经历或心得。不过从代码中可以看出，作者们都注重“关键条件的提前检查”和“变量的清晰命名”，这是解决模拟问题的重要经验。
</insights_intro>

-----

<conclusion>
本次关于“New Year and North Pole”的解题分析就到这里。通过模拟纬度变化、检查方向限制和最终状态，我们掌握了这类问题的核心解法。记住，模拟问题的关键是“按规则逐条检查，确保每一步都合法”。接下来，快去尝试拓展练习，巩固你的模拟能力吧！💪
</conclusion>

-----

---
处理用时：157.28秒