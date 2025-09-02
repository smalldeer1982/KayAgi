# 题目信息

# Facetook Priority Wall

## 题目描述

Facetook 是一个知名的社交网站，它将推出一个名为 Facetook Priority Wall 的新功能。这一功能将根据优先级因子对你朋友的所有帖子进行排序。

优先级因子将受到三种行为的影响：
1. ```"X posted on Y's wall"``` (15 分), 
2. ```"X commented on Y's post"``` (10 分), 
3. ```"X likes Y's post"``` (5 分).

$X$ 和 $Y$ 是两个不同的名字。每一种行为都会使 $X$ 和 $Y$ 之间的优先级因子增加对应分数 ($X$ 和 $Y$ 之间的优先级因子与 $Y$ 和 $X$ 之间的优先级因子相同) 。

给定 $n$ 个上述格式的行为（没有行为序号和行为分数），你要将所有除自己名字以外的名字按照优先级因子打印出来。

## 样例 #1

### 输入

```
ahmed
3
ahmed posted on fatma's wall
fatma commented on ahmed's post
mona likes ahmed's post
```

### 输出

```
fatma
mona
```

## 样例 #2

### 输入

```
aba
1
likes likes posted's post
```

### 输出

```
likes
posted
```

# AI分析结果



---

# 💡 Kay的C++算法解析：Facetook Priority Wall 深入学习指南 💡

<introduction>
今天我们来一起分析“Facetook Priority Wall”这道C++编程题。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟` (模拟输入解析、数据统计与排序)

🗣️ **初步分析**：
解决“Facetook Priority Wall”这道题，关键在于**模拟社交行为的解析、分数统计及排序过程**。简单来说，“模拟”就像按照规则一步步“复制”题目中的操作——就像你按照菜谱做饭，每一步都严格对照步骤执行。在本题中，模拟主要用于：解析输入的行为语句，提取涉及的用户X和Y；根据行为类型（发帖、评论、点赞）计算优先级分数；记录所有出现的用户（即使不加分）；最后按分数和字典序排序输出（排除自己）。

- **题解思路**：所有题解核心思路一致：用`map`或`unordered_map`统计用户分数，解析输入提取用户，根据行为类型加分，最后排序输出。差异主要在输入解析的细节处理（如如何提取Y的名字）和数据结构的选择（如用`vector`还是结构体数组存储用户）。
- **核心难点**：正确提取用户名字（特别是处理Y的`'s`后缀）、记录所有出现的用户（包括不加分的）、实现多关键字排序（分数降序，字典序升序）。
- **可视化设计**：采用8位像素风格动画，模拟行为解析过程：每个行为作为一帧，用不同颜色的像素块表示X和Y，分数变化时数字跳动；排序时像素块按规则排列，伴随“叮”的音效，直观展示分数统计和排序逻辑。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码可读性、算法有效性与优化程度、实践价值等几个方面，筛选了以下评分较高（≥4星）的题解。
</eval_intro>

**题解一：作者xyx404**
* **点评**：此题解思路清晰，代码结构工整。通过`unordered_set`记录出现的用户，`unordered_map`统计分数，结构体存储用户信息以便排序。输入解析部分通过判断行为类型（`posted`/`commented`/`likes`）提取X和Y，并正确删除Y的`'s`后缀。变量命名虽有小瑕疵（如`soccer`应为`score`），但整体规范。处理边界条件（如用户不加分时仍记录）严谨，适合竞赛参考。

**题解二：作者Mzh2012**
* **点评**：此题解逻辑简洁，直接使用`map`统计分数，结构体数组存储用户。输入解析部分通过判断行为类型分情况处理，代码可读性高。排序函数明确（分数降序，字典序升序），实践价值高。美中不足是输入处理细节（如`cin`顺序）需注意，但整体是优秀的参考。

**题解三：作者Jerrlee**
* **点评**：此题解思路巧妙，通过交换X和Y简化加分逻辑（若Y是自己则交换为X是自己），减少重复代码。使用`map`和`vector`组合，代码简洁高效。输入解析部分用`erase`删除`'s`后缀，处理得当。特别适合学习如何简化条件判断。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下一些关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1：正确提取用户名字（处理`'s`后缀）**
    * **分析**：输入中的Y名字常以`Y's`形式出现（如`fatma's`），需要删除最后两个字符得到`Y`。例如，`Y = "fatma's"`时，`erase(Y.size()-2)`得到`"fatma"`。优质题解通常使用`erase`或`substr`方法处理，确保名字正确。
    * 💡 **学习笔记**：字符串处理时，注意检查边界（如`size()`是否足够），避免越界错误。

2.  **关键点2：记录所有出现的用户（包括不加分的）**
    * **分析**：即使行为中没有自己参与（X和Y都不是自己），这两个用户仍需被记录（分数为0）。例如，样例2中输入`"likes likes posted's post"`，两个用户`likes`和`posted`都需输出。优质题解通过`map`的自动去重特性（插入即记录）解决此问题。
    * 💡 **学习笔记**：`map`或`unordered_map`的`insert`操作可确保用户被记录，即使分数为0。

3.  **关键点3：多关键字排序（分数降序，字典序升序）**
    * **分析**：排序需先按分数从高到低，分数相同则按姓名字典序从小到大。优质题解通常自定义排序函数（如`cmp`），在结构体或`vector`排序时应用此规则。
    * 💡 **学习笔记**：自定义排序函数时，用`return a.score > b.score`实现降序，`return a.name < b.name`实现字典序升序。

### ✨ 解题技巧总结
<summary_best_practices>
- **字符串解析技巧**：按空格分割输入行，提取关键部分（如行为类型、X和Y）。例如，`"X posted on Y's wall"`分割后，第二个单词是行为类型（`posted`），第四个单词是Y的`'s`形式。
- **数据结构选择**：用`map`或`unordered_map`统计分数（自动去重），用结构体数组或`vector`存储用户以便排序（`map`本身无序）。
- **边界处理**：处理`'s`后缀时，确保字符串长度足够（避免`erase`越界）；输出时排除自己的名字。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了多个优质题解的思路（如xyx404的输入解析、Jerrlee的排序逻辑），优化了变量命名，确保代码清晰高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <unordered_map>
    #include <unordered_set>
    #include <vector>
    #include <algorithm>
    using namespace std;

    struct User {
        string name;
        int score;
    };

    bool cmp(const User& a, const User& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.name < b.name;
    }

    int main() {
        string myName;
        int n;
        cin >> myName >> n;

        unordered_map<string, int> scoreMap;
        unordered_set<string> userSet;

        for (int i = 0; i < n; ++i) {
            string x, action, temp, yWithSuffix;
            cin >> x >> action;

            if (action == "likes") {
                cin >> yWithSuffix; // 格式为 "Y's"
                yWithSuffix.erase(yWithSuffix.size() - 2); // 去掉's
                if (x != myName) userSet.insert(x);
                if (yWithSuffix != myName) userSet.insert(yWithSuffix);
                if (x == myName) scoreMap[yWithSuffix] += 5;
                else if (yWithSuffix == myName) scoreMap[x] += 5;
                cin >> temp; // 读取"post"（无用）
            } else {
                cin >> temp; // 读取"on"（无用）
                cin >> yWithSuffix; // 格式为 "Y's"
                yWithSuffix.erase(yWithSuffix.size() - 2); // 去掉's
                if (x != myName) userSet.insert(x);
                if (yWithSuffix != myName) userSet.insert(yWithSuffix);
                int add = (action == "posted") ? 15 : 10;
                if (x == myName) scoreMap[yWithSuffix] += add;
                else if (yWithSuffix == myName) scoreMap[x] += add;
                cin >> temp; // 读取"wall"或"post"（无用）
            }
        }

        vector<User> users;
        for (const string& name : userSet) {
            users.push_back({name, scoreMap[name]});
        }

        sort(users.begin(), users.end(), cmp);

        for (const auto& user : users) {
            cout << user.name << endl;
        }

        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取自己的名字和行为数量，然后遍历每个行为：根据行为类型（`likes`/`posted`/`commented`）解析X和Y（处理`'s`后缀），记录所有出现的用户（排除自己），并根据是否与自己相关加分。最后将用户存入`vector`，按分数和字典序排序后输出。

---
<code_intro_selected>
接下来，我们将逐一剖析筛选出的优质题解中，最能体现核心逻辑的C++实现片段，并点出各自的亮点和关键代码思路。
</code_intro_selected>

**题解一：作者xyx404**
* **亮点**：使用`unordered_set`记录用户，确保无重复；结构体排序逻辑清晰。
* **核心代码片段**：
    ```cpp
    struct node{
        string name;
        int soccer; // 应为score，记录分数
    }ren[110];

    bool cmp(node x,node y){ 
        if(x.soccer==y.soccer) return x.name<y.name;
        return x.soccer>y.soccer;
    }
    ```
* **代码解读**：
    > 这段代码定义了存储用户信息的结构体`node`（包含名字和分数），并自定义排序函数`cmp`。`cmp`函数首先比较分数（降序），分数相同则比较字典序（升序）。这是排序的核心逻辑，确保输出符合题目要求。
* 💡 **学习笔记**：结构体是存储多字段数据的常用方式，自定义排序函数是实现多关键字排序的关键。

**题解二：作者Mzh2012**
* **亮点**：输入解析简洁，直接根据行为类型分情况处理。
* **核心代码片段**：
    ```cpp
    if(b=="posted") m[d]+=15;
    else if(b=="likes") m[d]+=5;
    else m[d]+=10;
    ```
* **代码解读**：
    > 这段代码根据行为类型（`b`）给用户`d`加分。`posted`加15分，`likes`加5分，其余（`commented`）加10分。这是分数统计的核心逻辑，通过简单的条件判断实现。
* 💡 **学习笔记**：条件判断是模拟行为类型的直接方式，需确保覆盖所有情况。

**题解三：作者Jerrlee**
* **亮点**：交换X和Y简化逻辑（若Y是自己则交换为X是自己）。
* **核心代码片段**：
    ```cpp
    if(b==st) swap(a,b); // a 评论/发帖/点赞 b 和 b 评论/发帖/点赞 a 加分一样，换过来便于加分
    if(a==st)
        if(o=="posted") pnts[b]+=15;
        else if(o=="commented") pnts[b]+=10;
        else if(o=="likes") pnts[b]+=5;
    ```
* **代码解读**：
    > 这段代码通过`swap(a,b)`将Y是自己的情况转换为X是自己的情况，减少了重复的条件判断。例如，若原行为是`Y posted on X's wall`且X是自己，交换后统一处理为X是自己的情况，简化逻辑。
* 💡 **学习笔记**：合理交换变量可减少重复代码，提升可读性。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“模拟输入解析与分数统计”的过程，我设计了一个8位像素风格的动画演示方案。让我们一起“看”到算法的每一步！
</visualization_intro>

  * **动画演示主题**：`像素社交墙大冒险`（结合FC红白机风格，模拟社交行为的处理过程）

  * **核心演示内容**：
    - 输入行为的解析过程（提取X、Y，处理`'s`后缀）。
    - 分数统计（根据行为类型加分，数字跳动效果）。
    - 用户排序（像素块按分数和字典序排列）。

  * **设计思路简述**：
    采用8位像素风是为了营造轻松复古的学习氛围；关键操作（如加分、排序）伴随“叮”的音效，强化记忆；每处理一个行为视为“小关卡”，完成后显示“已处理”动画，增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          - 屏幕分为左右两部分：左侧是“行为处理区”（像素风格的社交墙，显示当前处理的行为语句），右侧是“用户分数区”（堆叠的像素块，每个块显示用户名字和分数）。
          - 控制面板：单步/自动播放按钮、调速滑块（1x-5x）、重置按钮。

    2.  **行为解析与用户提取**：
          - 输入行为语句（如`"ahmed posted on fatma's wall"`）逐字符显示，用黄色高亮X（`ahmed`）和行为类型（`posted`），绿色高亮Y（`fatma's`）。
          - 处理`'s`后缀：Y的`'s`部分闪烁后消失，变为`fatma`（绿色像素块）。

    3.  **分数统计**：
          - 若X或Y是自己（假设自己是`ahmed`），则对方（`fatma`）的分数块数字从0变为15（伴随“叮”的音效，数字跳动）。
          - 若行为不涉及自己，X和Y的分数块保持0，但仍以灰色像素块显示（表示已记录）。

    4.  **排序过程**：
          - 所有用户分数块从右侧堆叠区“飞”到排序区，按分数降序排列。分数相同的块按字典序调整位置（如`mona`在`fatma`后，因分数低；若分数相同则`a`开头的在`b`前）。
          - 排序完成后，播放“胜利”音效，排除自己的名字，最终输出列表。

    5.  **交互控制**：
          - 单步执行：点击“单步”按钮，逐帧展示解析、加分、排序。
          - 自动播放：选择速度后，动画自动运行，适合观察整体流程。

  * **旁白提示**：
      - （解析X时）“看！第一个名字是X，用黄色标记啦～”
      - （处理`'s`时）“Y的名字后面有个`'s`，我们把它删掉，变成绿色的Y！”
      - （加分时）“叮～X是自己，所以Y的分数加15分！”

<visualization_conclusion>
通过这样一个融合了像素艺术和复古游戏元素的动画，我们不仅能清晰地看到“模拟”算法的执行流程，还能在一种更轻松有趣的环境中理解输入解析、分数统计和排序的核心逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考该算法/技巧的适用范围和变形应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 本题的“模拟输入解析+数据统计+排序”思路，可用于处理日志分析（如用户登录次数统计）、游戏亲密度计算（如组队次数加分）、社交平台互动统计（如点赞/评论量排序）等场景。关键是识别输入中的关键信息，统计后按规则排序。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1093 奖学金** 
          * 🗣️ **推荐理由**：这道题需要根据多科成绩排序，涉及多关键字排序（总分降序，语文降序，数学降序），能巩固本题的排序技巧。
    2.  **洛谷 P1540 机器翻译** 
          * 🗣️ **推荐理由**：此题模拟内存缓存的替换过程，需要记录已翻译的单词（类似本题记录用户），适合练习模拟和集合的使用。
    3.  **洛谷 P1067 多项式输出** 
          * 🗣️ **推荐理由**：此题需要解析多项式的系数和指数，按规则输出（类似本题解析行为类型和用户），适合练习字符串处理和条件判断。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到调试时遇到的问题，这些经验对我们很有参考价值：
</insights_intro>

> **参考经验 (来自多位题解作者)**：“在处理`'s`后缀时，曾因字符串长度不足导致`erase`越界错误（如输入`"likes likes posted's post"`时，`Y`的字符串长度可能只有5，`erase(5-2)`即`erase(3)`会导致错误）。后来通过检查字符串长度，确保`erase`前长度足够解决了问题。”

> **点评**：这位作者的经验提醒我们，在处理字符串操作（如`erase`、`substr`）时，一定要先检查字符串长度，避免越界错误。例如，本题中`Y`的字符串至少为`"X's"`（长度3），所以`erase(size()-2)`是安全的，但其他场景需谨慎。

-----

<conclusion>
本次关于“Facetook Priority Wall”的C++解题分析就到这里。希望这份学习指南能帮助大家更好地理解模拟算法、字符串处理和排序技巧。记住，编程能力的提升在于持续学习、勤于思考和勇于实践。下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：201.16秒