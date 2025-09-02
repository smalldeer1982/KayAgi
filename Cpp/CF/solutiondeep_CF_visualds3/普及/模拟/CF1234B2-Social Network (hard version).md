# 题目信息

# Social Network (hard version)

## 题目描述

The only difference between easy and hard versions are constraints on $ n $ and $ k $ .

You are messaging in one of the popular social networks via your smartphone. Your smartphone can show at most $ k $ most recent conversations with your friends. Initially, the screen is empty (i.e. the number of displayed conversations equals $ 0 $ ).

Each conversation is between you and some of your friends. There is at most one conversation with any of your friends. So each conversation is uniquely defined by your friend.

You (suddenly!) have the ability to see the future. You know that during the day you will receive $ n $ messages, the $ i $ -th message will be received from the friend with ID $ id_i $ ( $ 1 \le id_i \le 10^9 $ ).

If you receive a message from $ id_i $ in the conversation which is currently displayed on the smartphone then nothing happens: the conversations of the screen do not change and do not change their order, you read the message and continue waiting for new messages.

Otherwise (i.e. if there is no conversation with $ id_i $ on the screen):

- Firstly, if the number of conversations displayed on the screen is $ k $ , the last conversation (which has the position $ k $ ) is removed from the screen.
- Now the number of conversations on the screen is guaranteed to be less than $ k $ and the conversation with the friend $ id_i $ is not displayed on the screen.
- The conversation with the friend $ id_i $ appears on the first (the topmost) position on the screen and all the other displayed conversations are shifted one position down.

Your task is to find the list of conversations (in the order they are displayed on the screen) after processing all $ n $ messages.

## 说明/提示

In the first example the list of conversations will change in the following way (in order from the first to last message):

- $ [] $ ;
- $ [1] $ ;
- $ [2, 1] $ ;
- $ [3, 2] $ ;
- $ [3, 2] $ ;
- $ [1, 3] $ ;
- $ [1, 3] $ ;
- $ [2, 1] $ .

In the second example the list of conversations will change in the following way:

- $ [] $ ;
- $ [2] $ ;
- $ [3, 2] $ ;
- $ [3, 2] $ ;
- $ [1, 3, 2] $ ;
- and then the list will not change till the end.

## 样例 #1

### 输入

```
7 2
1 2 3 2 1 3 2
```

### 输出

```
2
2 1 
```

## 样例 #2

### 输入

```
10 4
2 3 3 1 1 2 1 2 3 3
```

### 输出

```
3
1 3 2 
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Social Network (hard version) 深入学习指南 💡

<introduction>
今天我们来一起分析“Social Network (hard version)”这道模拟类编程题。通过这道题，我们可以学会如何用数据结构高效模拟“最近对话列表”的动态更新过程。让我们一步步拆解问题，掌握核心技巧吧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟` (结合哈希表与双端队列的高效操作)

🗣️ **初步分析**：
> 解决这道题的关键在于模拟手机屏幕对话列表的动态更新过程。简单来说，“模拟”就是严格按照题目描述的规则，用代码复现每一步操作。就像玩“像素版消息管理器”——每次收到新消息，我们需要快速判断它是否已在屏幕上：如果在，就像没看到一样；如果不在，就把它“顶”到列表最前面，挤掉最后一个（如果超容量）。

- **题解思路对比**：大部分题解都采用“双端队列（deque）+哈希表（map/set）”的组合。双端队列维护对话的顺序（队首是最新的，队尾是最早的），哈希表快速判断对话是否存在。少数题解用队列（queue）或数组模拟，但双端队列更直观。
- **核心算法流程**：遍历所有消息，对每个消息：
  1. 用哈希表检查是否已存在，存在则跳过；
  2. 不存在则插入队首，更新哈希表；
  3. 若队列长度超过k，删除队尾元素并更新哈希表。
- **可视化设计**：计划用8位像素风格的“消息板”展示队列变化：队首插入时用“向上弹出”动画，队尾删除时用“向下消失”动画；哈希表状态用像素灯（绿色亮表示存在，灰色灭表示不存在）；关键操作（插入/删除）伴随“叮”/“噗”的像素音效。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性的综合评估，以下题解因逻辑简洁、实现高效被选为优质参考（评分≥4星）：
</eval_intro>

**题解一：作者 jiangXxin**
* **点评**：此题解思路直白，直接抓住“双端队列+哈希表”的核心。代码中使用`deque`维护顺序，`map`标记存在性，变量名（如`que`、`mp`）简洁易懂。特别值得学习的是，当队列长度超过k时，直接弹出队尾并更新哈希表，逻辑严谨。从实践角度看，代码可直接用于竞赛，边界处理（如初始空队列）非常到位。

**题解二：作者 FiraCode**
* **点评**：此题解同样使用`deque`和`map`，但代码结构更紧凑。核心逻辑（判断存在→插入队首→检查长度）清晰明了，循环内操作无冗余。亮点在于将“插入”和“删除”操作合并在一个条件判断中，减少代码复杂度，适合快速编写。

**题解三：作者 Katsura_Hinagiku**
* **点评**：此题解用数组模拟栈（`stck`），思路巧妙。通过维护栈顶指针`top`，插入时直接`stck[++top]`，删除时通过`top-k`定位队尾，避免了STL的额外开销。虽然离散化用`map`实现，但代码简洁，适合理解基础数据结构的模拟过程。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们可能会遇到以下几个关键问题。结合优质题解的共性，我们一起梳理解决策略：
</difficulty_intro>

1.  **关键点1：如何高效判断对话是否已存在？**
    * **分析**：由于`id_i`范围很大（1e9），不能用数组直接标记，需用哈希表（`map`或`unordered_map`）。哈希表的查询时间是O(1)，能快速判断是否存在。例如，题解中`mp[x]`为`true`表示`x`在屏幕上。
    * 💡 **学习笔记**：当数据范围大时，哈希表是高效判重的首选工具。

2.  **关键点2：如何维护对话的顺序？**
    * **分析**：每次新对话插入队首，旧对话后移。双端队列（`deque`）的`push_front`和`pop_back`操作正好对应“插入队首”和“删除队尾”，时间复杂度均为O(1)。若用普通队列（`queue`），插入队首需反转队列，效率低。
    * 💡 **学习笔记**：双端队列是处理“两端操作”场景的利器。

3.  **关键点3：如何处理超容量时的删除？**
    * **分析**：当队列长度超过k时，需删除队尾元素（最早进入的）。此时需同步更新哈希表（标记该元素为不存在），否则后续相同`id`会被误判为存在。例如，题解中`mp[que.back()] = false`后再`pop_back`。
    * 💡 **学习笔记**：删除操作需同时维护数据结构和辅助标记，避免状态不一致。

### ✨ 解题技巧总结
- **数据结构搭配**：哈希表（判重）+双端队列（维护顺序）是此类“最近使用”问题的经典组合。
- **边界处理**：初始队列为空时，直接插入；插入后立即检查长度，避免遗漏删除操作。
- **代码简洁性**：用`deque`的`size()`直接判断长度，避免手动计数（除非需优化复杂度）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，选择最简洁的“双端队列+哈希表”实现作为通用核心代码。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了jiangXxin和FiraCode的题解思路，使用`deque`维护顺序，`map`判重，逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <deque>
    #include <map>
    using namespace std;

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n, k;
        cin >> n >> k;

        deque<int> que;
        map<int, bool> exists;

        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (exists[x]) continue; // 已存在，跳过

            // 插入队首并标记
            exists[x] = true;
            que.push_front(x);

            // 超容量则删除队尾
            if (que.size() > k) {
                exists[que.back()] = false;
                que.pop_back();
            }
        }

        // 输出结果
        cout << que.size() << "\n";
        while (!que.empty()) {
            cout << que.front() << " ";
            que.pop_front();
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入，初始化双端队列`que`和哈希表`exists`。遍历每条消息时，若消息不存在则插入队首并标记；若队列超容则删除队尾并取消标记。最后输出队列长度和内容。核心逻辑集中在循环内，通过`push_front`和`pop_back`维护顺序，`map`快速判重。

---
<code_intro_selected>
接下来，我们剖析优质题解的核心代码片段，学习其中的巧妙思路。
</code_intro_selected>

**题解一：作者 jiangXxin**
* **亮点**：代码简洁，直接使用`deque`和`map`，变量名清晰。
* **核心代码片段**：
    ```cpp
    deque<int> que;
    map<int,bool> mp;
    // ...
    if(mp[x]==true)continue;
    mp[x]=true;
    que.push_front(x);
    if(que.size()>=k+1){
        m=que.back();
        mp[m]=false;
        que.pop_back();
    }
    ```
* **代码解读**：
    > 这段代码是核心逻辑：若`x`不存在（`mp[x]`为`false`），则标记为存在（`mp[x]=true`），插入队首（`push_front`）。若队列长度超过`k`（`>=k+1`），则取出队尾元素`m`，取消标记（`mp[m]=false`）并弹出队尾（`pop_back`）。这里用`>=k+1`是因为插入后可能刚好超过`k`，确保队列长度不超过`k`。
* 💡 **学习笔记**：插入后立即检查长度，避免队列“膨胀”。

**题解二：作者 FiraCode**
* **亮点**：代码紧凑，将插入和删除合并处理。
* **核心代码片段**：
    ```cpp
    if (ma[a[i]]) continue;
    if (q.size () == k) ma[q.back()] = false , q.pop_back();
    if (!ma[a[i]]) q.push_front (a[i]) , ma[a[i]] = true;
    ```
* **代码解读**：
    > 这段代码逻辑非常简洁：若存在则跳过；若队列已满（`size==k`），先删除队尾并取消标记；最后插入新元素并标记。注意第二个`if`确保在删除后再插入，避免队列长度超过`k`。
* 💡 **学习笔记**：条件判断顺序很重要，先处理删除再插入，确保队列长度正确。

**题解三：作者 Katsura_Hinagiku**
* **亮点**：用数组模拟栈，减少STL依赖。
* **核心代码片段**：
    ```cpp
    int stck[200005],top=0;
    // ...
    stck[++top]=ccc;
    if(top>k){
        mp[stck[top-k]]=0;
    }
    ```
* **代码解读**：
    > 用数组`stck`模拟栈，`top`是栈顶指针。插入时`stck[++top]`，超容时（`top>k`），标记`stck[top-k]`（即最早的元素）为不存在。输出时从`top`往前取`k`个元素。这种方法避免了STL的开销，适合理解底层逻辑。
* 💡 **学习笔记**：数组模拟是理解数据结构的好方法，但需注意索引计算。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地看到对话列表的动态变化，我们设计一个“像素消息板”动画，用8位复古风格展示每一步操作！
</visualization_intro>

  * **动画演示主题**：`像素消息管理器——帮手机整理对话列表`
  * **核心演示内容**：展示消息的插入（顶到队首）、删除（挤掉队尾）过程，以及哈希表的状态变化。
  * **设计思路简述**：8位像素风让界面更亲切；消息块的“弹出”和“消失”动画强化操作记忆；音效提示关键步骤（插入“叮”，删除“噗”），增加互动感。

  * **动画帧步骤与交互关键点**：

    1.  **初始化场景**：
          * 屏幕分为两部分：上方是“消息板”（像素网格，最多k个位置），下方是“哈希灯板”（每个消息对应一个小灯，绿色亮表示存在，灰色灭表示不存在）。
          * 控制面板：单步/自动按钮、速度滑块（1x-5x）、重置按钮。

    2.  **处理消息**：
          * 新消息`x`从屏幕右侧飞入，指向消息板：
            - 若哈希灯板中`x`的灯是绿色（已存在），消息爆炸成像素点，无其他变化；
            - 若灯是灰色（不存在），消息板队首位置弹出空位，消息`x`“跳”入队首，后面的消息依次下移一格；同时哈希灯板`x`的灯变绿。
          * 若消息板已满（k个位置），队尾消息“滑落”消失，对应哈希灯板灯变灰。

    3.  **音效与反馈**：
          * 插入消息：“叮~”（高音效）；
          * 删除消息：“噗~”（低音效）；
          * 全部处理完成：“啦~”（胜利音效），消息板高亮。

    4.  **交互控制**：
          * 单步执行：点击“下一步”，逐消息处理；
          * 自动播放：选择速度，动画自动推进；
          * 重置：清空消息板和哈希灯板，回到初始状态。

  * **旁白提示**：
      * （插入时）“看！新消息`x`不在列表里，所以它被放到最前面~”；
      * （删除时）“列表满啦，最后一个消息`y`被挤出去了~”；
      * （存在时）“消息`x`已经在列表里，不用动~”。

<visualization_conclusion>
通过这样的动画，我们能直观看到每一步操作如何影响消息列表和哈希表，理解“插入-删除”的动态平衡过程。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
这道题的核心是“最近使用”场景的模拟，类似的问题在编程中很常见。掌握这种思路后，我们可以解决更多类似问题：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * **浏览器历史记录**：新页面插入队首，超容量删除最早页面；
      * **缓存淘汰（LRU）**：最近最少使用的缓存被删除，可用类似方法模拟；
      * **游戏道具栏**：新道具插入栏位，满了则替换最旧的。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1056** - `排座椅`
          * 🗣️ **推荐理由**：模拟座位调整过程，需要维护座位的占用状态，锻炼逻辑清晰的模拟能力。
    2.  **洛谷 P1067** - `多项式输出`
          * 🗣️ **推荐理由**：模拟多项式的格式化输出，需处理多种边界情况（如系数为0、符号等），提升细节处理能力。
    3.  **洛谷 P1160** - `队列安排`
          * 🗣️ **推荐理由**：用双向链表模拟队列的插入和删除，与本题双端队列思路类似，适合进一步巩固。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试中的小技巧，这些经验能帮助我们少走弯路：
</insights_intro>

> **参考经验 (来自 作者 jiangXxin)**：“一开始没注意哈希表和队列的同步，导致删除队尾后哈希表没更新，后面相同的id被误判为存在。后来通过打印中间状态，发现了这个问题。”
>
> **点评**：这位作者的经验很实用！在模拟类问题中，数据结构（如队列）和辅助标记（如哈希表）的状态必须同步。调试时，打印关键变量（如队列内容、哈希表标记）能快速定位问题。

-----

<conclusion>
通过今天的分析，我们掌握了如何用双端队列和哈希表模拟“最近对话列表”的动态更新。关键是理解“判重”和“维护顺序”的核心逻辑，以及数据结构的高效搭配。接下来，动手写代码并调试，你会更深刻地理解其中的细节！下次见~ 💪
</conclusion>

---
处理用时：139.16秒