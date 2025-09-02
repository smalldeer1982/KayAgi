# 题目信息

# Peterson Polyglot

## 题目描述

Peterson loves to learn new languages, but his favorite hobby is making new ones. Language is a set of words, and word is a sequence of lowercase Latin letters.

Peterson makes new language every morning. It is difficult task to store the whole language, so Peterson have invented new data structure for storing his languages which is called broom. Broom is rooted tree with edges marked with letters. Initially broom is represented by the only vertex — the root of the broom. When Peterson wants to add new word to the language he stands at the root and processes the letters of new word one by one. Consider that Peterson stands at the vertex $ u $ . If there is an edge from $ u $ marked with current letter, Peterson goes through this edge. Otherwise Peterson adds new edge from $ u $ to the new vertex $ v $ , marks it with the current letter and goes through the new edge. Size of broom is the number of vertices in it.

In the evening after working day Peterson can't understand the language he made this morning. It is too difficult for bored Peterson and he tries to make it simpler. Simplification of the language is the process of erasing some letters from some words of this language. Formally, Peterson takes some positive integer $ p $ and erases $ p $ -th letter from all the words of this language having length at least $ p $ . Letters in words are indexed starting by 1. Peterson considers that simplification should change at least one word, i.e. there has to be at least one word of length at least $ p $ . Peterson tries to make his language as simple as possible, so he wants to choose $ p $ such that the size of the broom for his simplified language is as small as possible.

Peterson is pretty annoyed with this task so he asks you for help. Write a program to find the smallest possible size of the broom and integer $ p $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778C/f15fa0cc8758e6866285fb29653e592b9e8e324d.png)

Broom from the second sample test can be built using language "piece", "of", "pie", "pretty", "prefix". Its simplification with $ p=2 $ obtains the language of words "pece", "o", "pe", "petty", "pefix". This language gives us the broom with minimum possible size.

## 样例 #1

### 输入

```
5
1 2 c
2 3 a
3 4 t
2 5 t
```

### 输出

```
3
2
```

## 样例 #2

### 输入

```
16
1 2 o
2 3 f
1 4 p
4 5 i
5 6 e
6 7 c
7 8 e
4 9 r
9 10 e
10 11 t
11 12 t
12 13 y
10 14 f
14 15 i
15 16 x
```

### 输出

```
12
2
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Peterson Polyglot 深入学习指南 💡

<introduction>
  今天我们要拆解的问题是「Peterson Polyglot」——一个关于**Trie树合并优化**的趣味题目。想象一下：你有一个由字母组成的“单词迷宫”（Trie树），现在要拆掉某一层的所有分叉口，让它们的子分叉直接连到上一层，相同字母的分叉还要合并成一个。我们的目标是找到拆哪一层能让迷宫变得最小！这个问题能帮我们深入理解Trie树的结构和合并技巧，一起开始吧～
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（Trie树合并与层优化）

🗣️ **初步分析**：
> 解决这道题的关键，是把题目中的“Broom”（扫帚树）转化为我们熟悉的**Trie树**（字典树）——每个节点代表单词中的一个位置，边代表字母。题目中的“删除第p层”，其实就是**把Trie树中所有深度为p的节点“拆掉”**：让这些节点的子节点直接连接到它们的父节点（深度p-1的节点），并且如果多个子节点有相同的字母，就合并成一个节点（这样能减少总节点数）。我们的任务就是找到这样的p，让合并后的Trie树节点数最少。

- **核心思路**：对于每个可能的p（深度），计算“删除第p层”能减少多少节点（减少得越多，合并后的树越小）。最终选减少量最大的p。
- **关键算法**：通过**Trie树合并**计算每个深度的减少量——对于每个深度p-1的节点，合并它的所有子节点（原本在深度p），合并过程中每合并两个节点就会减少一个节点（比如两个“a”子节点合并成一个，就少了一个节点）。
- **可视化设计思路**：用**8位像素风格**展示Trie树（节点是彩色方块，边是像素线，根节点在左，深度向右延伸）。演示时，先高亮当前要删除的深度p的节点，再动画展示子节点合并到父节点的过程（相同字母的方块“吸”在一起，伴随“叮”的合并音效），最后显示该深度的减少量。控制面板支持单步执行、自动播放（像“贪吃蛇AI”一样逐个深度演示）和速度调节。


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和算法有效性三个维度筛选了3份优质题解，它们分别用不同的方式实现了Trie合并，能帮我们从多个角度理解问题～
</eval_intro>

**题解一：(来源：Aonynation)**
* **点评**：这份题解的思路最“直白好懂”！作者直接把问题转化为“计算每个深度的合并减少量”，用**DFS遍历Trie树**，对每个节点的子节点调用`merge`函数合并，计算合并后的节点数变化。代码中的`merge`函数是标准的Trie合并模板（递归合并每个子节点，空节点直接返回非空的那个），变量名（比如`sum[deep]`记录深度`deep`的减少量）也很直观。最棒的是，它用“总节点数 - 最大减少量”直接得到答案，逻辑闭环非常严谨，适合新手快速入门。

**题解二：(来源：dead_X)**
* **点评**：这份题解用了**dsu on tree（启发式合并）**优化！作者发现，合并子树时可以“重用重儿子的子树”，避免重复计算，把时间复杂度从O(n²)降到了O(n log n)。虽然代码稍长，但思路很有启发性——当子树很大时，启发式合并能大幅减少合并次数。比如，合并时先处理重儿子的子树，再把其他子树合并到重儿子上，这样总合并次数会少很多。对于想优化算法效率的同学，这是很好的参考。

**题解三：(来源：localhost)**
* **点评**：这份题解的代码**最简洁**！作者用最少的代码实现了核心逻辑：`mg`函数递归合并Trie节点，`dfs`函数遍历每个深度计算减少量。虽然解释较少，但代码结构清晰，适合想“抓重点”的同学。比如，`cnt`变量记录合并后的新节点数，`a[d]`记录深度`d`的减少量，最后直接找`a[d]`的最大值，逻辑非常直接。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这个问题时，大家常遇到“读不懂题”“不会算减少量”“合并函数写错”这三个难点。结合优质题解，我帮大家拆解了应对策略～
</difficulty_intro>

1.  **关键点1：把题目转化为Trie合并问题**
    * **分析**：题目中的“删除第p层”其实是“合并所有深度p的节点的子节点到父节点”。比如，假设父节点U有两个子节点V1（字母a）和V2（字母a），删除V1和V2所在的层后，U会直接连接一个合并后的“a”节点——这样就少了1个节点（V1或V2）。理解这一点，题目就变成了“找哪个层的合并能减少最多节点”。
    * 💡 **学习笔记**：复杂问题先“建模”——把题目中的“扫帚树”翻译成Trie树，问题就变得熟悉了！

2.  **关键点2：计算每个深度的减少量**
    * **分析**：减少量 = 原节点数 - 合并后的节点数。对于每个深度p，我们需要计算“所有深度p-1的节点合并子节点后，总共少了多少节点”。比如，题解一用`sum[deep]`记录深度`deep`的减少量：`cnt - n - 1`（`cnt`是合并后的总节点数，`n`是原节点数，差值就是减少的节点数）。
    * 💡 **学习笔记**：用“差值法”算减少量——合并后的节点数越少，减少量越大！

3.  **关键点3：正确实现Trie合并函数**
    * **分析**：合并两个Trie节点x和y的核心逻辑是：如果x或y为空，直接返回非空的那个；否则，新建一个节点，递归合并x和y的所有子节点。比如题解一的`merge`函数：
      ```cpp
      inline int merge(int x, int y) {
        if (x == 0 || y == 0) return x + y;
        int now = ++cnt;
        for (int i = 0; i < 26; i++)
          son[now][i] = merge(son[x][i], son[y][i]);
        return now;
      }
      ```
      这个函数确保了合并后的节点包含x和y的所有子节点，且相同字母的子节点会被合并。
    * 💡 **学习笔记**：递归是实现Trie合并的“神器”——它能自动处理所有子节点的合并！


### ✨ 解题技巧总结
- **技巧1：问题建模**：把“扫帚树”转化为Trie树，将“删除层”转化为“合并子节点”，问题就变得可解。
- **技巧2：差值计算**：通过“合并后的节点数 - 原节点数”计算减少量，避免直接统计合并后的树大小。
- **技巧3：递归合并**：用递归实现Trie合并，逻辑清晰且不易出错。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合了题解一和题解三的通用核心代码**——它保留了最简洁的逻辑，适合快速理解整体流程～
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了题解一的DFS逻辑和题解三的简洁风格，核心是“遍历每个节点→合并子节点→计算减少量”。
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <cstring>
  using namespace std;

  const int N = 600005;
  int n, son[N][26], sum[N], cnt; // sum[deep]记录深度deep的减少量

  // 合并两个Trie节点x和y，返回合并后的根节点
  inline int merge(int x, int y) {
    if (x == 0 || y == 0) return x + y;
    int now = ++cnt;
    for (int i = 0; i < 26; i++)
      son[now][i] = merge(son[x][i], son[y][i]);
    return now;
  }

  // DFS遍历Trie，计算每个深度的减少量
  void dfs(int now, int deep) {
    cnt = n + 1; // 重置合并后的节点计数器（从原节点数+1开始）
    int merged = n + 1; // 初始合并后的根节点（空节点）
    for (int i = 0; i < 26; i++)
      if (son[now][i]) merged = merge(merged, son[now][i]);
    // 减少量 = 合并后的节点数 - (n + 1) （因为cnt从n+1开始，差值就是新增的节点数，原节点数是n，所以减少量是 cnt - (n+1)）
    sum[deep] += cnt - (n + 1);
    // 递归处理子节点
    for (int i = 0; i < 26; i++)
      if (son[now][i]) dfs(son[now][i], deep + 1);
  }

  int main() {
    cin >> n;
    memset(son, 0, sizeof(son));
    for (int i = 1, x, y; i < n; i++) {
      char c;
      cin >> x >> y >> c;
      son[x][c - 'a'] = y;
    }
    dfs(1, 1); // 根节点深度为1
    // 找最大减少量对应的深度p
    int max_decrease = 0, best_p = 1;
    for (int i = 1; i <= n; i++) {
      if (sum[i] > max_decrease) {
        max_decrease = sum[i];
        best_p = i;
      }
    }
    // 合并后的节点数 = 原节点数 - 最大减少量
    cout << n - max_decrease << endl << best_p << endl;
    return 0;
  }
  ```
* **代码解读概要**：
  > 1. **输入处理**：读取n个节点，构建Trie树（`son[x][c-'a'] = y`表示节点x有一个字母c的子节点y）。
  > 2. **DFS计算减少量**：从根节点（深度1）开始遍历，对每个节点的子节点调用`merge`合并，计算该深度的减少量并存入`sum[deep]`。
  > 3. **找最优解**：遍历`sum`数组，找到减少量最大的深度`best_p`，输出合并后的节点数（`n - max_decrease`）和`best_p`。


<code_intro_selected>
接下来赏析3份优质题解的核心片段，看看它们的“亮点”在哪里～
</code_intro_selected>

**题解一：(来源：Aonynation)**
* **亮点**：用`sum[deep]`直接记录每个深度的减少量，逻辑直观。
* **核心代码片段**：
  ```cpp
  inline void dfs(int now, int deep) {
    int num;
    num = cnt = n + 1;
    for (int i = 0; i < 26; i++)
      if (son[now][i]) num = merge(num, son[now][i]);
    sum[deep] += cnt - n - 1; // 减少量 = 合并后的节点数 - 初始值（n+1）
    for (int i = 0; i < 26; i++)
      if (son[now][i]) dfs(son[now][i], deep + 1);
  }
  ```
* **代码解读**：
  > 这段代码是计算减少量的核心。`cnt`从`n+1`开始（因为原Trie有n个节点，合并后的节点数从n+1开始计数），`merge`后`cnt`是合并后的总节点数。`cnt - n - 1`就是合并过程中**新增的节点数**——但等一下，减少量不是“原节点数 - 合并后的节点数”吗？其实这里的`sum[deep]`记录的是“合并该深度的节点后，总共减少了多少节点”。比如，原节点数是n，合并后的节点数是`cnt`，所以减少量是`n - (cnt - (n+1) - 1)`？不对，再仔细想：原节点数是n，合并后的节点数是`cnt`吗？不，题解一的`cnt`是合并后的新节点数（从n+1开始），所以合并后的总节点数是`n + (cnt - (n+1))`？不对，其实题解一的`sum[deep]`记录的是“合并该深度的节点后，减少的节点数”——比如，合并两个子节点x和y，原本需要x和y两个节点，合并后只需要一个，所以减少了1个节点。`cnt - n - 1`就是合并过程中减少的节点数总和（因为每合并一次，`cnt`加1，而原节点数是n，所以`cnt - n - 1`就是减少的数量）。
* 💡 **学习笔记**：用“计数器差值”算减少量，是一种巧妙的技巧！

**题解二：(来源：dead_X)**
* **亮点**：用`dsu on tree`优化合并，减少重复计算。
* **核心代码片段**：
  ```cpp
  void dfs(int d,int x) {
    for(int i=0; i<26; i++) 
      if(nxt[x][i]) ++v[d],dfs(d+1,nxt[x][i]);
    qwq=d;CNT=700000;
    // 合并非重儿子到重儿子上
    for(int i=0; i<26; i++) 
      if(nxt[x][i]&&(nxt[x][i]!=hs[x])) merge(nxt[x][i],hs[x]);
    clear(); 
    return ;
  }
  ```
* **代码解读**：
  > 这段代码用了`dsu on tree`的核心思想——**重儿子优先**。`hs[x]`是节点x的重儿子（子树最大的子节点），合并时先处理重儿子的子树，再把其他子节点合并到重儿子上。这样能减少合并的次数，因为重儿子的子树已经处理过了，不需要重新合并。比如，假设x有三个子节点A（重儿子，子树大）、B、C，合并时先处理A，再把B和C合并到A上，这样总合并次数比“合并A→合并B→合并C”少很多。
* 💡 **学习笔记**：启发式合并能优化树的合并效率，适合处理大规模数据！

**题解三：(来源：localhost)**
* **亮点**：代码最简洁，核心逻辑一目了然。
* **核心代码片段**：
  ```cpp
  void dfs(int x,int d){
    int now=n+1;cnt=n+1;
    Fur(i,0,25)if(c[x][i]) now=mg(now,c[x][i]);
    a[d]+=cnt-n-1;
    Fur(i,0,25)if(c[x][i]) dfs(c[x][i],d+1);
  }
  ```
* **代码解读**：
  > 这段代码和题解一的逻辑完全一致，但用了`Fur`宏（遍历0-25）简化代码，`mg`函数是`merge`的简写。`a[d]`记录深度d的减少量，`cnt-n-1`是减少的节点数。代码简洁到“一眼就能看懂”，适合快速理解核心逻辑。
* 💡 **学习笔记**：简洁的代码往往更易读——避免冗余，抓住核心！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让大家“看得到”Trie合并的过程，我设计了一个**8位像素风格的动画**，像玩FC游戏一样学习算法！
</visualization_intro>

  * **动画演示主题**：像素Trie的“层拆除游戏”——你是一个“Trie建筑师”，要拆掉某一层让Trie最小。
  * **核心演示内容**：展示Trie树的结构→选中某一层→演示子节点合并到父节点→显示减少量→自动找到最优层。
  * **设计思路简述**：用8位像素风格（像《超级玛丽》的画面）让学习更轻松；用“合并音效”和“高亮”强化关键操作；自动播放像“AI闯关”一样，让你直观看到每个层的效果。

  * **动画帧步骤与交互关键点**：
    1.  **场景初始化**：
        * 屏幕左侧显示**像素Trie树**：根节点是红色方块（深度1），子节点是蓝色方块（深度2），孙子节点是绿色方块（深度3）……边是白色像素线，标有字母。
        * 右侧是**控制面板**：有“开始/暂停”“单步”“重置”按钮，速度滑块（从“慢”到“快”），还有“自动找最优”开关。
        * 底部显示**当前减少量**和**最优层**。
        * 播放8位风格的背景音乐（像《坦克大战》的BGM）。
    2.  **选择层演示**：
        * 点击“单步”，首先高亮深度1的节点（红色闪烁），然后动画展示：深度1的节点的子节点（深度2）合并到父节点——相同字母的蓝色方块“吸”在一起，合并成一个蓝色方块，伴随“叮”的音效。底部显示该层的减少量（比如“减少了2个节点”）。
        * 再点击“单步”，高亮深度2的节点（蓝色闪烁），演示它们的子节点（深度3）合并到父节点，同样伴随音效和减少量显示。
    3.  **自动找最优**：
        * 打开“自动找最优”开关，动画会自动遍历所有深度，逐个演示合并过程，最后高亮减少量最大的层（比如深度2），并播放“胜利音效”（像《魂斗罗》的通关音乐），底部显示“最优层是2，合并后的节点数是12”。
    4.  **重置与重来**：
        * 点击“重置”，Trie树恢复原状，可重新演示。

  * **旁白提示**：
    * （高亮深度2时）“现在要拆的是深度2的节点～看！它们的子节点要合并到父节点了！”
    * （合并时）“听到‘叮’的一声吗？这两个‘a’节点合并成一个啦，减少了1个节点！”
    * （找到最优层时）“太棒啦！拆深度2能减少最多节点，合并后的Trie最小！”


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
Trie树的合并技巧不仅能解决本题，还能用于很多“字典类”问题。比如，合并多个字典树、统计共同前缀等。下面推荐几道洛谷题目，帮你巩固Trie的应用～
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    * Trie合并可用于**合并多个单词集合**（比如合并两个字典）；
    * 可用于**统计多个字符串的共同前缀**（合并时统计相同路径的节点数）；
    * 可用于**优化多模式匹配**（比如合并多个AC自动机）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P2580** - 《于是他错误的点名开始了》
        * 🗣️ **推荐理由**：这是Trie树的基础题，帮你熟悉Trie的构建和查询，巩固“节点代表字符”的概念。
    2.  **洛谷 P3879** - 《[TJOI2010]阅读理解》
        * 🗣️ **推荐理由**：这道题需要用Trie统计每个单词出现的文章编号，能帮你练习Trie的“附带信息存储”（比如每个节点记录出现的文章列表）。
    3.  **洛谷 P5357** - 《【模板】AC自动机（加强版）》
        * 🗣️ **推荐理由**：AC自动机是Trie的扩展（带失败指针），这道题需要统计每个模式串的出现次数，能帮你理解Trie的进阶应用。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中的“经验技巧”能帮我们少走弯路，下面分享两个重要的心得～
</insights_intro>

> **参考经验 (来自 Aonynation)**：“合并Trie时，空节点直接返回非空的那个，这样能避免创建多余的节点。”
>
> **点评**：这个技巧太重要了！如果x或y是空节点，直接返回非空的那个，就能跳过无效的合并，减少递归次数。比如，合并一个空节点和一个非空节点，结果就是非空节点，不需要新建任何节点——这能大幅提升合并效率。

> **参考经验 (来自 dead_X)**：“用dsu on tree优化合并，重儿子优先处理，能减少重复计算。”
>
> **点评**：当子树很大时，启发式合并能把时间复杂度从O(n²)降到O(n log n)。比如，合并1000个节点的子树，如果用普通合并需要1000次，而用启发式合并只需要log₂1000≈10次——这对于大规模数据来说，是质的提升！


<conclusion>
本次关于「Peterson Polyglot」的解析就到这里啦～通过这道题，我们学会了把复杂问题转化为Trie树模型，用合并技巧计算减少量，还了解了启发式合并的优化方法。记住：编程的核心是“建模”——把现实问题翻译成代码能理解的结构（比如Trie树），问题就会迎刃而解！下次我们再一起探索更有趣的算法挑战，加油～💪
</conclusion>

---

---
处理用时：169.97秒