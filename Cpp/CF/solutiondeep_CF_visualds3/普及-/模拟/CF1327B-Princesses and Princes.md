# 题目信息

# Princesses and Princes

## 题目描述

The King of Berland Polycarp LXXXIV has $ n $ daughters. To establish his power to the neighbouring kingdoms he wants to marry his daughters to the princes of these kingdoms. As a lucky coincidence there are $ n $ other kingdoms as well.

So Polycarp LXXXIV has enumerated his daughters from $ 1 $ to $ n $ and the kingdoms from $ 1 $ to $ n $ . For each daughter he has compiled a list of kingdoms princes of which she wanted to marry.

Polycarp LXXXIV is very busy, so he finds a couple for his daughters greedily one after another.

For the first daughter he takes the kingdom with the lowest number from her list and marries the daughter to their prince. For the second daughter he takes the kingdom with the lowest number from her list, prince of which hasn't been taken already. If there are no free princes in the list then the daughter marries nobody and Polycarp LXXXIV proceeds to the next daughter. The process ends after the $ n $ -th daughter.

For example, let there be $ 4 $ daughters and kingdoms, the lists daughters have are $ [2, 3] $ , $ [1, 2] $ , $ [3, 4] $ , $ [3] $ , respectively.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1327B/50ce2d8ac0f6b682008f6274aa8cfbc6afc16be3.png)In that case daughter $ 1 $ marries the prince of kingdom $ 2 $ , daughter $ 2 $ marries the prince of kingdom $ 1 $ , daughter $ 3 $ marries the prince of kingdom $ 3 $ , leaving daughter $ 4 $ nobody to marry to.

Actually, before starting the marriage process Polycarp LXXXIV has the time to convince one of his daughters that some prince is also worth marrying to. Effectively, that means that he can add exactly one kingdom to exactly one of his daughter's list. Note that this kingdom should not be present in the daughter's list.

Polycarp LXXXIV wants to increase the number of married couples.

Unfortunately, what he doesn't have the time for is determining what entry to add. If there is no way to increase the total number of married couples then output that the marriages are already optimal. Otherwise, find such an entry that the total number of married couples increases if Polycarp LXXXIV adds it.

If there are multiple ways to add an entry so that the total number of married couples increases then print any of them.

For your and our convenience you are asked to answer $ t $ independent test cases.

## 说明/提示

The first test case is depicted in the statement. Adding the fourth kingdom to the list of the fourth daughter makes her marry the prince of the fourth kingdom.

In the second test case any new entry will increase the number of marriages from $ 0 $ to $ 1 $ .

In the third and the fourth test cases there is no way to add an entry.

In the fifth test case there is no way to change the marriages by adding any entry.

## 样例 #1

### 输入

```
5
4
2 2 3
2 1 2
2 3 4
1 3
2
0
0
3
3 1 2 3
3 1 2 3
3 1 2 3
1
1 1
4
1 1
1 2
1 3
1 4```

### 输出

```
IMPROVE
4 4
IMPROVE
1 1
OPTIMAL
OPTIMAL
OPTIMAL```

# AI分析结果



---
# 💡 Kay的C++算法解析：Princesses and Princes 深入学习指南 💡

<introduction>
今天我们来一起分析“Princesses and Princes”这道贪心匹配问题。通过这篇指南，你将学会如何用贪心策略解决公主与王子的匹配问题，掌握关键代码实现，并通过像素动画直观理解算法过程。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：贪心算法

🗣️ **初步分析**：
解决这道题的关键在于理解“贪心匹配”的核心思想。贪心算法就像分糖果时，先给第一个小朋友最小的糖果，再给第二个小朋友剩下最小的——每一步都选择当前最优的选项，从而可能达到全局最优。在本题中，每个公主按顺序选择自己列表里编号最小的未被选中的王子，正是贪心策略的典型应用。

- **题解思路**：所有题解的核心思路一致：先模拟贪心匹配过程（为每个公主选择列表中最小的可用王子），记录哪些王子和公主未匹配。若存在未匹配的公主和王子，输出其中一对即可；否则说明已最优。
- **核心难点**：正确模拟贪心匹配过程，避免遗漏未匹配的公主或王子；确保添加的王子不在公主原列表中（但根据题目性质，未匹配的王子必然不在公主原列表中，因此无需额外检查）。
- **可视化设计**：我们将用8位像素风动画演示匹配过程：公主（像素小人）依次走到王子（像素方块）前，选择最小的未被标记的王子（标记为粉色），未匹配的公主和王子用灰色高亮。添加操作时，公主的列表弹出新王子（蓝色闪光），最终匹配成功时播放“叮”的音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过对题解的思路清晰度、代码规范性和算法有效性评估，以下3道题解因逻辑简洁、实现高效被选为优质参考：
</eval_intro>

**题解一：Andrewzdm的实现（来源：用户分享）**
* **点评**：此题解代码结构清晰，变量名`used`（记录王子是否被选）和`choosed`（记录公主是否匹配）直观易懂。代码通过两次遍历分别处理匹配和查找未匹配对象，逻辑简洁。特别值得学习的是，利用`fill`函数初始化数组，避免了手动循环的冗余，体现了良好的代码规范。

**题解二：Happy_Dream的实现（来源：用户分享）**
* **点评**：此题解直接模拟贪心过程，用`b`数组记录王子是否被选，`ans`记录未匹配的公主。代码逻辑直白，边界处理（如`fla`标记是否匹配成功）严谨。输出部分通过遍历找到未匹配的王子，确保了方案的正确性。

**题解三：gyh20的实现（来源：用户分享）**
* **点评**：此题解代码极为简洁，用`c`数组记录王子状态，`lst`变量直接记录最后一个未匹配的公主。通过一次遍历完成匹配，第二次遍历查找未匹配的王子，时间复杂度为O(n)，效率很高。变量命名虽简短但含义明确，适合竞赛场景。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题时，我们需要重点关注以下三个关键点，掌握它们能帮你快速理清思路：
</difficulty_intro>

1.  **关键点1：如何正确模拟贪心匹配过程？**
    * **分析**：每个公主按顺序选择自己列表中编号最小的未被选中的王子。实现时，需要为每个公主遍历其列表，一旦找到未被选的王子（用数组标记），立即标记并跳过后续选项。例如，用`used[x]`表示王子x是否被选，公主i遍历列表时，遇到第一个`used[x]==false`的x，就标记`used[x]=true`并标记自己已匹配。
    * 💡 **学习笔记**：贪心匹配的关键是“按顺序、选最小”，用数组标记状态能高效实现这一逻辑。

2.  **关键点2：如何判断是否存在可改进的配对？**
    * **分析**：若所有公主都匹配成功（即`choosed`数组全为true），则输出`OPTIMAL`；否则，必然存在至少一个未匹配的公主和一个未匹配的王子（因为总共有n个公主和n个王子，未匹配的公主数等于未匹配的王子数）。此时，任选一对未匹配的公主和王子即可。
    * 💡 **学习笔记**：未匹配的公主和王子数量相等，因此只需找到第一个未匹配的公主和第一个未匹配的王子即可。

3.  **关键点3：如何确保添加的王子不在原列表中？**
    * **分析**：题目要求添加的王子不能在公主原列表中。但根据贪心匹配的性质，若公主未匹配，说明其列表中所有王子都被选过了。因此，未匹配的王子必然不在该公主的原列表中（否则她会选择这个王子）。因此无需额外检查。
    * 💡 **学习笔记**：贪心匹配的结果隐含了“未匹配的王子不在未匹配公主的原列表中”这一条件，简化了问题。

### ✨ 解题技巧总结
- **状态标记法**：用布尔数组标记王子和公主的匹配状态，时间复杂度O(n)，高效且易实现。
- **两次遍历法**：第一次遍历完成贪心匹配，第二次遍历查找未匹配对象，逻辑清晰无冗余。
- **边界处理**：注意数组初始化（如`used`和`choosed`数组），避免因未初始化导致的错误。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解思路的通用核心实现，代码简洁高效，适合直接理解和应用：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Andrewzdm和Happy_Dream的思路，通过两次遍历完成匹配和查找，逻辑清晰且时间复杂度为O(n)。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN = 100010;

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int t;
        cin >> t;
        while (t--) {
            int n;
            cin >> n;
            vector<bool> used(n + 1, false);   // 记录王子是否被选
            vector<bool> choosed(n + 1, false); // 记录公主是否匹配
            for (int i = 1; i <= n; ++i) {
                int k;
                cin >> k;
                for (int j = 0; j < k; ++j) {
                    int x;
                    cin >> x;
                    if (!choosed[i] && !used[x]) { // 公主i未匹配且王子x可用
                        used[x] = true;
                        choosed[i] = true;
                    }
                }
            }
            // 查找未匹配的公主和王子
            int unmarried_princess = -1, unmarried_prince = -1;
            for (int i = 1; i <= n; ++i) {
                if (!choosed[i]) {
                    unmarried_princess = i;
                    break;
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (!used[i]) {
                    unmarried_prince = i;
                    break;
                }
            }
            if (unmarried_princess != -1 && unmarried_prince != -1) {
                cout << "IMPROVE\n" << unmarried_princess << " " << unmarried_prince << "\n";
            } else {
                cout << "OPTIMAL\n";
            }
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先读取输入，用`used`数组标记已选王子，`choosed`数组标记已匹配的公主。通过遍历每个公主的列表，完成贪心匹配。最后两次遍历分别找到未匹配的公主和王子，输出结果。

---
<code_intro_selected>
接下来，我们分析优质题解中的核心代码片段，学习其中的巧妙思路：
</code_intro_selected>

**题解一：Andrewzdm的实现**
* **亮点**：使用`vector<bool>`动态管理状态，代码简洁；利用`fill`初始化数组，避免手动循环。
* **核心代码片段**：
    ```cpp
    fill(used + 1, used + n + 1, false);
    fill(choosed + 1, choosed + n + 1, false);
    for(int i = 1; i <= n; i++) {
        int k; cin >> k;
        bool flag = false;
        for(int j = 1; j <= k; j++) {
            int x; cin >> x;
            if(!flag && !used[x]) {
                used[x] = true;
                choosed[i] = true;
                flag = true;
            }
        }
    }
    ```
* **代码解读**：`fill`函数快速初始化两个布尔数组，确保每次测试用例开始前状态正确。内层循环中，`flag`标记公主是否已匹配，遇到第一个可用王子时立即标记，保证“选最小”的贪心策略。
* 💡 **学习笔记**：用`flag`变量控制只选择第一个可用王子，避免重复匹配，是贪心实现的关键。

**题解二：gyh20的实现**
* **亮点**：代码极简，用`lst`变量直接记录最后一个未匹配的公主，减少遍历次数。
* **核心代码片段**：
    ```cpp
    for(re int i=1;i<=n;++i){
        k=read(); bool pp=0;
        for(re int j=1;j<=k;++j){
            re int x=read();
            if(!pp&&!c[x]){ pp=c[x]=1; }
        }
        if(!pp) lst=i;
    }
    ```
* **代码解读**：`pp`变量标记公主是否匹配成功，`c[x]`标记王子是否被选。若公主未匹配（`pp=0`），则`lst`记录其编号。这种“一次遍历记录未匹配公主”的方式非常高效。
* 💡 **学习笔记**：在遍历过程中直接记录未匹配的公主，避免后续再次遍历所有公主，优化了时间。

**题解三：Happy_Dream的实现**
* **亮点**：用`ans`变量记录未匹配的公主，逻辑直白易理解。
* **核心代码片段**：
    ```cpp
    int ans=0;
    for(int i=1;i<=n;i++){
        cin>>k[i];
        int fla=0;
        for(int j=1;j<=k[i];j++){
            int x; cin>>x;
            if(b[x]==0&&fla==0){ // 王子未被选且公主未匹配
                b[x]++; fla=1;
            }
        }
        if(fla==0) ans=i; // 记录未匹配的公主
    }
    ```
* **代码解读**：`fla`标记公主是否匹配成功，`b[x]`记录王子是否被选。若`fla=0`，说明公主i未匹配，`ans`记录其编号。这种“边匹配边记录”的方式简化了后续查找步骤。
* 💡 **学习笔记**：在匹配过程中同步记录未匹配的公主，避免了额外的遍历，提升效率。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解贪心匹配过程，我们设计了一个“像素婚礼”动画，用8位复古风格展示公主选王子的每一步！
</visualization_intro>

  * **动画演示主题**：像素婚礼——公主的王子选择之旅

  * **核心演示内容**：展示每个公主依次选择列表中最小的未被选王子的过程，高亮未匹配的公主和王子，并演示添加王子后的匹配成功效果。

  * **设计思路简述**：采用8位像素风格（如FC游戏画面），用不同颜色区分已选/未选状态，关键步骤伴随音效，让学习者“看到”贪心策略的执行过程。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕分为左右两部分：左侧是“公主队列”（8个像素小人，编号1-8），右侧是“王子城堡”（8个像素方块，编号1-8）。
        - 控制面板：包含“开始/暂停”“单步”“重置”按钮，速度滑块（1-5倍速）。
        - 播放8位风格的轻快背景音乐（类似《超级马里奥》的主题曲片段）。

    2.  **匹配过程演示**：
        - 公主1（黄色小人）走到王子城堡前，遍历自己的列表（如[2,3]）。
        - 王子2（蓝色方块）未被选，公主1选中他：王子2变为粉色（已选），公主1变为绿色（已匹配），播放“叮”的音效。
        - 公主2（紫色小人）遍历列表[1,2]，王子1（蓝色）未被选，选中他：王子1变粉，公主2变绿，音效“叮”。
        - 未匹配的公主（灰色小人）和王子（灰色方块）会逐渐变暗，突出显示。

    3.  **添加王子演示**：
        - 若存在未匹配的公主（如公主4）和王子（如王子4），点击“添加”按钮，公主4的列表弹出王子4（蓝色闪光）。
        - 公主4重新选择，选中王子4：王子4变粉，公主4变绿，播放“哇哦”的胜利音效，屏幕飘出像素星星。

    4.  **交互控制**：
        - 单步执行：点击“单步”按钮，公主逐个匹配，学习者可观察每一步的选择。
        - 自动播放：选择速度后，动画自动演示完整匹配过程，适合整体观察。

  * **旁白提示**：
    - “公主1选择了最小的可用王子2，王子2现在被标记为已选！”
    - “公主4的列表里没有可用王子，她暂时未匹配，需要添加一个王子。”
    - “添加王子4到公主4的列表后，她成功匹配了！”

<visualization_conclusion>
通过这个像素动画，你可以直观看到贪心匹配的每一步，理解为什么未匹配的公主和王子一定可以配对，以及添加操作如何提升匹配数。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
贪心匹配的思路不仅适用于本题，还能解决许多类似的分配问题。以下是一些拓展练习和相似问题：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 任务分配：多个任务和工人，每个工人只能做特定任务，按顺序分配最小可用资源。
      - 座位安排：观众按顺序选择最小的可用座位。
      - 课程选择：学生按顺序选择最小的未被选课程。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1094 [NOIP2007 普及组] 纪念品分组**
        * 🗣️ **推荐理由**：考察贪心策略的应用，需要将物品分组使每组总价不超过限制，与本题的“选最小”思路类似。
    2.  **洛谷 P1803 凌乱的yyy / 线段覆盖**
        * 🗣️ **推荐理由**：用贪心选择结束时间最早的线段，与本题“选最小”的局部最优策略异曲同工。
    3.  **洛谷 P2240 部分背包问题**
        * 🗣️ **推荐理由**：贪心选择单位价值最高的物品，进一步理解贪心策略的适用场景。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试中的小插曲，这些经验对我们很有启发：
</insights_intro>

> **参考经验 (来自 dead_X)**：“x，y写反WA一发，完美避开小号一场上蓝。”
>
> **点评**：这位作者的经历提醒我们，在输出未匹配的公主和王子时，一定要注意顺序（公主编号在前，王子在后）。代码中变量的顺序容易因疏忽写反，通过测试用例验证或打印中间变量可以有效避免这类错误。

-----

<conclusion>
通过这篇指南，你已经掌握了贪心匹配问题的核心思路、代码实现和可视化过程。记住，贪心算法的关键是找到每一步的“最优选择”，并通过状态标记高效实现。多练习类似题目，你会对贪心策略有更深刻的理解！下次见～ 💪
</conclusion>

-----

---
处理用时：137.47秒