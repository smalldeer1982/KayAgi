# 题目信息

# The Butcher

## 题目描述

Anton plays his favorite game "Defense of The Ancients 2" for his favorite hero — The Butcher. Now he wants to make his own dinner. To do this he will take a rectangle of height $ h $ and width $ w $ , then make a vertical or horizontal cut so that both resulting parts have integer sides. After that, he will put one of the parts in the box and cut the other again, and so on.

More formally, a rectangle of size $ h \times w $ can be cut into two parts of sizes $ x \times w $ and $ (h - x) \times w $ , where $ x $ is an integer from $ 1 $ to $ (h - 1) $ , or into two parts of sizes $ h \times y $ and $ h \times (w - y) $ , where $ y $ is an integer from $ 1 $ to $ (w - 1) $ .

He will repeat this operation $ n - 1 $ times, and then put the remaining rectangle into the box too. Thus, the box will contain $ n $ rectangles, of which $ n - 1 $ rectangles were put in the box as a result of the cuts, and the $ n $ -th rectangle is the one that the Butcher has left after all $ n - 1 $ cuts.

Unfortunately, Butcher forgot the numbers $ h $ and $ w $ , but he still has $ n $ rectangles mixed in random order. Note that Butcher didn't rotate the rectangles, but only shuffled them. Now he wants to know all possible pairs $ (h, w) $ from which this set of rectangles can be obtained. And you have to help him do it!

It is guaranteed that there exists at least one pair $ (h, w) $ from which this set of rectangles can be obtained.

## 说明/提示

In the first test case, Butcher could only have a rectangle of size $ 4 \times 5 $ . Then the cuts could look like this (first the green cut was made, then the red one):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1819B/4604742f19434dbb2dfafc53d3bccc8f9c76c341.png)In the second test case, Butcher could have either a rectangle of $ 1 \times 3 $ or $ 3 \times 1 $ . The cuts would have looked like this (first the green cut was made, then the red cut):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1819B/a32b9e64b715c3348f2ec2b70f2c902cbff97240.png)In the third test case, Butcher did not make any cuts, so the rectangle is $ 10 \times 10 $ .

## 样例 #1

### 输入

```
4
3
1 2
3 5
1 3
3
1 1
1 1
1 1
1
10 10
4
3 2
5 5
2 2
8 7```

### 输出

```
1
4 5
2
1 3
3 1
1
10 10
1
13 7```

# AI分析结果

---
# 💡 Kay的C++算法解析：The Butcher 深入学习指南 💡

<introduction>
今天我们来一起分析“THE BUTCHER”这道C++编程题。这道题需要我们根据切割后的小矩形反推原始大矩形的可能尺寸。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟算法与验证逻辑

🗣️ **初步分析**：
解决这道题的关键在于理解切割过程的逆推逻辑。简单来说，每次切割会保留一个子矩形继续切割，另一个放入盒子。因此，初始矩形的长或宽必然是所有小矩形中长或宽的最大值（因为第一次切割会产生一个与原始长或宽相等的子矩形）。

- **题解思路**：所有题解的核心思路是：计算所有小矩形的总面积 \( S \)，找到长的最大值 \( mxh \) 和宽的最大值 \( mxw \)，然后验证两种可能的初始矩形 \( (mxh, S/mxh) \) 和 \( (S/mxw, mxw) \)（需满足 \( S \) 能被 \( mxh \) 或 \( mxw \) 整除）。验证时，模拟逆切割过程，检查小矩形能否按规则拼合出初始矩形。
- **核心难点**：如何高效验证候选初始矩形的合法性（即模拟逆切割过程）。
- **可视化设计**：采用8位像素风格，用不同颜色的像素块表示小矩形，动态展示逆切割过程中长和宽的变化。例如，初始时所有小矩形随机分布，每次选中与当前长/宽匹配的小矩形（高亮），将其拼合到初始矩形中，同时更新当前剩余的长/宽，伴随“叮”的音效提示关键操作。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面筛选了以下优质题解：
</eval_intro>

**题解一：作者FFTotoro（赞：7）**
* **点评**：此题解逻辑清晰，关键结论明确（初始矩形只有两种可能），代码规范且高效。作者使用`map`维护小矩形的长和宽，通过交替检查长和宽的最大值来验证候选矩形，边界处理严谨（如去重相同候选）。算法复杂度为 \( O(n \log n) \)，适合竞赛场景。亮点在于对逆切割过程的模拟：通过`map`动态删除已使用的小矩形，确保每一步操作的正确性。

**题解二：作者Zi_Gao（赞：1）**
* **点评**：此题解提出反向思考（从切割逆过程入手），思路新颖。使用`set`维护小矩形的长和宽，代码简洁。验证时通过不断匹配当前长/宽的最大值来拼合，逻辑直接。亮点在于用`set`的`rbegin()`快速获取最大值，简化了代码实现，适合初学者理解。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题的核心难点在于如何验证候选初始矩形的合法性。结合优质题解，我们提炼以下关键点：
</difficulty_intro>

1.  **关键点1：确定初始矩形的候选**  
    * **分析**：初始矩形的长或宽必然是所有小矩形长或宽的最大值（第一次切割产生的子矩形保留了原始长或宽）。因此，候选为 \( (mxh, S/mxh) \) 和 \( (S/mxw, mxw) \)（需满足 \( S \) 能被对应值整除）。  
    * 💡 **学习笔记**：利用“第一次切割保留原始长/宽”的性质，快速缩小候选范围。

2.  **关键点2：验证候选矩形的合法性**  
    * **分析**：模拟逆切割过程，交替匹配当前长/宽的最大值。例如，若候选长为 \( mxh \)，则先匹配所有长为 \( mxh \) 的小矩形，减去它们的宽，再匹配宽为新宽的小矩形，依此类推，直到所有小矩形被使用。  
    * 💡 **学习笔记**：逆过程需严格按照“先长后宽”或“先宽后长”的交替顺序，确保每一步匹配当前最大值。

3.  **关键点3：处理重复候选**  
    * **分析**：两种候选可能相同（如 \( mxh = S/mxw \) 且 \( mxw = S/mxh \)），需去重。  
    * 💡 **学习笔记**：验证后检查候选是否相同，避免重复输出。

### ✨ 解题技巧总结
- **问题分解**：将问题拆分为“找候选”和“验证候选”两部分，降低复杂度。
- **数据结构选择**：用`map`或`set`维护小矩形的长/宽，快速获取最大值（`begin()`或`rbegin()`）。
- **边界处理**：验证时检查长/宽是否变为非正数，避免无效操作。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合优质题解的通用核心实现，逻辑清晰且高效。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合FFTotoro和Zi_Gao的题解思路，采用`map`维护小矩形的长和宽，交替验证候选矩形。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    #define int long long
    using namespace std;

    bool check(int x, int y, vector<pair<int, int>>& a) {
        map<pair<int, int>, int, greater<>> m1, m2;
        for (auto& [h, w] : a) {
            m1[{h, w}]++;
            m2[{w, h}]++;
        }
        int cnt = 0;
        bool flag = true; // true表示当前检查长，false表示检查宽
        while (cnt < a.size()) {
            if (flag) {
                if (m1.empty() || m1.begin()->first.first != x) return false;
                auto [h, w] = m1.begin()->first;
                int num = m1[{h, w}];
                y -= w * num;
                cnt += num;
                m2[{w, h}] -= num;
                if (m2[{w, h}] == 0) m2.erase({w, h});
                m1.erase({h, w});
            } else {
                if (m2.empty() || m2.begin()->first.first != y) return false;
                auto [w, h] = m2.begin()->first;
                int num = m2[{w, h}];
                x -= h * num;
                cnt += num;
                m1[{h, w}] -= num;
                if (m1[{h, w}] == 0) m1.erase({h, w});
                m2.erase({w, h});
            }
            flag = !flag;
        }
        return x == 0 && y == 0;
    }

    main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int t;
        cin >> t;
        while (t--) {
            int n;
            cin >> n;
            vector<pair<int, int>> a(n);
            int S = 0, mxh = 0, mxw = 0;
            for (auto& [h, w] : a) {
                cin >> h >> w;
                S += h * w;
                mxh = max(mxh, h);
                mxw = max(mxw, w);
            }
            vector<pair<int, int>> ans;
            if (S % mxh == 0 && check(mxh, S / mxh, a)) {
                ans.emplace_back(mxh, S / mxh);
            }
            if (S % mxw == 0 && check(S / mxw, mxw, a)) {
                pair<int, int> p(S / mxw, mxw);
                if (ans.empty() || ans.back() != p) {
                    ans.push_back(p);
                }
            }
            cout << ans.size() << "\n";
            for (auto& [h, w] : ans) {
                cout << h << " " << w << "\n";
            }
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先计算总面积 \( S \)、最大长 \( mxh \) 和最大宽 \( mxw \)。然后验证两种候选矩形：若 \( S \) 能被 \( mxh \) 整除，验证 \( (mxh, S/mxh) \)；同理验证 \( (S/mxw, mxw) \)。验证函数`check`使用`map`维护小矩形的长和宽，交替检查当前长/宽的最大值，确保所有小矩形被正确使用。

---
<code_intro_selected>
以下是优质题解的核心代码片段赏析：
</code_intro_selected>

**题解一：FFTotoro**
* **亮点**：使用`map`动态维护小矩形的长和宽，交替检查最大值，逻辑严谨。
* **核心代码片段**：
    ```cpp
    bool check(int x, int y, vector<pair<int, int> > a, bool f){
        map<pair<int, int>, int, greater<> > m1, m2;
        for(auto [x,y]:a)m1[make_pair(x,y)]++,m2[make_pair(y,x)]++;
        for(int c=0;c<a.size();f^=1){
            if(f){
                if(m1.begin()->first.first!=x)return false;
                // 处理长匹配的小矩形
            } else {
                if(m2.begin()->first.first!=y)return false;
                // 处理宽匹配的小矩形
            }
        }
        return true;
    }
    ```
* **代码解读**：`m1`按长降序存储小矩形（长, 宽），`m2`按宽降序存储（宽, 长）。`f`标记当前检查长或宽：若检查长，取`m1`的第一个元素（最长），减去其宽；若检查宽，取`m2`的第一个元素（最宽），减去其长。交替进行直到所有小矩形被使用。
* 💡 **学习笔记**：`map`的`greater<>`排序方便快速获取最大值，动态删除已使用的小矩形确保每一步操作正确。

**题解二：Zi_Gao**
* **亮点**：使用`set`维护小矩形的长和宽，代码简洁。
* **核心代码片段**：
    ```cpp
    bool check(register long long nowx,register long long nowy){
        stx.clear(),sty.clear();
        for(i=0;i<n;++i) stx.insert((NODE){ps[i].x,i}),sty.insert((NODE){ps[i].y,i});
        while(!(stx.empty()&&sty.empty())){
            if(!stx.empty()&&stx.rbegin()->val==nowx){
                // 处理长匹配的小矩形
            }else if(!sty.empty()&&sty.rbegin()->val==nowy){
                // 处理宽匹配的小矩形
            }else return false;
        }
        return true;
    }
    ```
* **代码解读**：`stx`和`sty`分别按长、宽降序存储小矩形。每次取长或宽的最大值，若匹配当前长/宽则删除该小矩形，更新剩余长/宽。若无法匹配则返回失败。
* 💡 **学习笔记**：`set`的`rbegin()`直接获取最大值，简化了最大值的查找逻辑。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解逆切割过程，我们设计一个“像素拼合大师”动画，用8位像素风格展示小矩形如何拼合出初始大矩形。
</visualization_intro>

  * **动画演示主题**：像素拼合大师——逆切割之旅

  * **核心演示内容**：展示候选初始矩形的验证过程，动态显示小矩形如何按长/宽最大值匹配，逐步拼合出初始矩形。

  * **设计思路简述**：8位像素风格（如FC游戏画面）营造轻松氛围，用不同颜色区分小矩形（如蓝色表示长匹配，绿色表示宽匹配）。每匹配一个小矩形，播放“叮”的音效；拼合完成时播放“胜利”音效，增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为左右两部分：左侧为像素网格（初始为空白，最终显示初始矩形），右侧为控制面板（开始/暂停、单步、速度滑块）。
          * 小矩形以随机位置排列在网格下方，用像素块表示（颜色随机，尺寸为小矩形的长宽）。

    2.  **算法启动**：
          * 输入候选初始矩形的长 \( h \) 和宽 \( w \)，网格左上角显示当前目标：“目标：\( h \times w \)”。
          * 播放轻快的8位背景音乐。

    3.  **核心步骤演示**：
          * **长匹配阶段**：高亮所有长为 \( h \) 的小矩形（蓝色闪烁），将它们逐个移动到网格左侧（从下到上堆叠），每移动一个，网格右侧显示“当前宽剩余：\( w - 小矩形宽 \)”，播放“叮”音效。
          * **宽匹配阶段**：更新 \( w \) 为剩余宽，高亮所有宽为 \( w \) 的小矩形（绿色闪烁），将它们逐个移动到网格左侧（从左到右排列），更新 \( h \) 为剩余长，播放“叮”音效。
          * **错误提示**：若无法匹配当前长/宽，高亮错误位置（红色闪烁），播放“错误”音效，动画暂停。

    4.  **目标达成**：
          * 所有小矩形拼合完成且 \( h \) 和 \( w \) 均为0时，网格显示完整初始矩形（金色边框），播放“胜利”音效，显示“验证成功！”。

  * **旁白提示**：
      * （长匹配前）“现在需要匹配长为 \( h \) 的小矩形，注意看它们的宽如何影响剩余宽度！”
      * （宽匹配时）“宽匹配完成，剩余长度更新，继续匹配新的宽度！”
      * （错误时）“无法匹配当前宽，此候选不合法哦！”

<visualization_conclusion>
通过这个动画，我们能清晰看到逆切割过程中每一步的匹配逻辑，理解小矩形如何拼合出初始大矩形。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心是逆推和验证，这类思路在其他切割/组合问题中也常见。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 逆推法：从结果反推初始状态（如拼图问题、路径回溯）。
      * 验证逻辑：通过模拟过程检查候选解的合法性（如数独验证、排列组合验证）。
      * 最大值性质：利用最大值缩小候选范围（如数组分割、区间覆盖）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1182 数列分段Section II**  
          * 🗣️ **推荐理由**：考察最大值的性质和验证逻辑，需判断最小最大值是否满足条件，与本题思路类似。
    2.  **洛谷 P1044 栈**  
          * 🗣️ **推荐理由**：逆推合法出栈序列，训练逆过程思维。
    3.  **洛谷 P1314 聪明的质监员**  
          * 🗣️ **推荐理由**：涉及验证候选值的合法性，需通过二分法缩小范围，强化验证逻辑。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
FFTotoro在题解中提到：“赛时没切出来，下大分，麻了。赛后不敢相信这玩意只有*1900。” 这提醒我们：
</insights_intro>

> **参考经验**：遇到难题时，赛后复盘关键结论（如本题中“初始矩形只有两种可能”）能快速提升。即使赛时未解决，理清思路后往往发现问题并不复杂。

> **点评**：这位作者的经验告诉我们，竞赛中遇到困难时，赛后的总结和关键结论的提炼至关重要。本题的关键在于抓住“第一次切割保留原始长/宽”的性质，这需要对问题深入分析。

-----

<conclusion>
本次关于“THE BUTCHER”的C++解题分析就到这里。希望这份指南能帮助大家理解逆推和验证的核心思路，掌握用数据结构高效模拟过程的技巧。记住，多动手模拟、总结关键结论，是提升算法能力的关键！下次挑战新题见！💪
</conclusion>

-----

---
处理用时：473.08秒