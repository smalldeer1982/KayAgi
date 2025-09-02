# 题目信息

# Brand New Easy Problem

## 题目描述

A widely known among some people Belarusian sport programmer Lesha decided to make some money to buy a one square meter larger flat. To do this, he wants to make and carry out a Super Rated Match (SRM) on the site Torcoder.com. But there's a problem — a severe torcoder coordinator Ivan does not accept any Lesha's problem, calling each of them an offensive word "duped" (that is, duplicated). And one day they nearely quarrelled over yet another problem Ivan wouldn't accept.

You are invited to act as a fair judge and determine whether the problem is indeed brand new, or Ivan is right and the problem bears some resemblance to those used in the previous SRMs.

You are given the descriptions of Lesha's problem and each of Torcoder.com archive problems. The description of each problem is a sequence of words. Besides, it is guaranteed that Lesha's problem has no repeated words, while the description of an archive problem may contain any number of repeated words.

The "similarity" between Lesha's problem and some archive problem can be found as follows. Among all permutations of words in Lesha's problem we choose the one that occurs in the archive problem as a subsequence. If there are multiple such permutations, we choose the one with the smallest number of inversions. Then the "similarity" of a problem can be written as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF202B/7915a415961b72b48e6cd878bc6adf37cd6bd951.png), where $ n $ is the number of words in Lesha's problem and $ x $ is the number of inversions in the chosen permutation. Note that the "similarity" $ p $ is always a positive integer.

The problem is called brand new if there is not a single problem in Ivan's archive which contains a permutation of words from Lesha's problem as a subsequence.

Help the boys and determine whether the proposed problem is new, or specify the problem from the archive which resembles Lesha's problem the most, otherwise.

## 说明/提示

Let us remind you that the number of inversions is the number of pairs of words that follow in the permutation not in their original order. Thus, for example, if the original problem is "add two numbers", then permutation "numbers add two" contains two inversions — pairs of words "numbers" and "add", "numbers" and "two".

Sequence $ b_{1},b_{2},...,b_{k} $ is a subsequence of sequence $ a_{1},a_{2},...,a_{n} $ if there exists such a set of indices $ 1<=i_{1}&lt;i_{2}&lt;...\ &lt;i_{k}<=n $ that $ a_{ij}=b_{j} $ (in other words, if sequence $ b $ can be obtained from $ a $ by deleting some of its elements).

In the first test case the first problem contains the "find the palindrome next" permutation as a subsequence, in which the number of inversions equals 1 (words "palindrome" and "next").

In the second test case there is no problem that contains a permutation of words from Lesha's problem as a subsequence.

## 样例 #1

### 输入

```
4
find the next palindrome
1
10 find the previous palindrome or print better luck next time
```

### 输出

```
1
[:||||||:]
```

## 样例 #2

### 输入

```
3
add two numbers
3
1 add
2 two two
3 numbers numbers numbers
```

### 输出

```
Brand new problem!
```

## 样例 #3

### 输入

```
4
these papers are formulas
3
6 what are these formulas and papers
5 papers are driving me crazy
4 crazy into the night
```

### 输出

```
1
[:||||:]
```

## 样例 #4

### 输入

```
3
add two decimals
5
4 please two decimals add
5 decimals want to be added
4 two add decimals add
4 add one two three
7 one plus two plus three equals six
```

### 输出

```
3
[:|||:]
```

# AI分析结果

# 💡 Kay的C++算法解析：Brand New Easy Problem 深入学习指南 💡

## 引言
今天我们要分析的问题是「Brand New Easy Problem」——判断Lesha的问题是否是全新的，或者找到 archive 中最相似的问题。这个问题看似复杂，但只要拆解成**子序列判断**和**最小反转数计算**两个核心部分，就能逐步解决。让我们一起深入探究吧！


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：状态压缩动态规划（DP） + 子序列处理

### 🗣️ 初步分析
解决这个问题的关键在于两点：  
1. **判断archive问题是否包含Lesha问题的排列作为子序列**：只需检查archive问题是否包含Lesha问题的所有单词（因为排列的子序列等价于选择每个单词的一个位置并按顺序排列）。  
2. **计算最小反转数**：若包含，需找到反转数最少的排列（反转数越小，相似度越高）。这里要用到**状态压缩DP**——用二进制mask表示已选单词的集合，记录最小反转数和最后位置，确保子序列的顺序性。

### 核心算法流程
- **步骤1**：过滤archive问题，保留Lesha问题中的单词，形成序列T'。  
- **步骤2**：预处理每个单词在T'中的出现位置（按递增排序）。  
- **步骤3**：状态压缩DP：  
  - `dp[mask][j]` 表示已选`mask`对应的单词、最后选的是第`j`个单词时的**最小反转数**和**最后位置**。  
  - 转移时，尝试添加未选单词`k`，找到其在T'中大于当前最后位置的最小位置，计算新增反转数（已选单词中rank大于`k`的数量），更新状态。

### 可视化设计思路
我们会用**8位像素风格**演示DP的状态转移：  
- 用不同颜色的像素块代表`mask`（二进制位亮灯表示已选单词）。  
- 用箭头表示状态转移（从`mask`到`new_mask`），高亮新增的单词和反转数变化。  
- 加入「单步执行」和「自动播放」，配合「叮」的音效提示关键操作，让你直观看到`mask`的增长和反转数的计算过程。


## 2. 精选优质题解参考
本次分析的题解中未找到完整的优质题解。不过，Kay给大家提供**通用学习建议**：  
- 先掌握**子序列的判断**（检查所有单词是否存在）。  
- 再学习**状态压缩DP**（用mask表示集合，适合小n的问题）。  
- 重点理解**反转数的计算**：新增反转数等于已选单词中rank更大的数量（用位运算快速统计）。


## 3. 核心难点辨析与解题策略

### 🧩 核心难点与解决策略
1. **难点1：如何高效判断archive问题是否包含Lesha的所有单词？**  
   - **分析**：只需用哈希集合（如`unordered_set`）存储Lesha的单词，遍历archive问题的单词，统计是否覆盖所有单词。  
   - 💡 学习笔记：哈希集合是快速判断元素存在的利器。

2. **难点2：如何设计状态压缩DP的状态？**  
   - **分析**：用`mask`（二进制数）表示已选单词的集合，`dp[mask][j]`记录最后选的是第`j`个单词时的最小反转数和最后位置。这样既能保证子序列的顺序（最后位置递增），又能跟踪反转数。  
   - 💡 学习笔记：状态压缩DP适合**集合选择类问题**，mask的每一位代表一个元素是否被选。

3. **难点3：如何快速计算新增的反转数？**  
   - **分析**：反转数是「已选单词中rank大于当前单词`k`的数量」。用位运算`mask & ((1<<n) - (1<<k))`提取这些位，再统计1的个数（用`__builtin_popcount`函数）。  
   - 💡 学习笔记：位运算能高效处理集合的统计问题。


### ✨ 解题技巧总结
- **问题拆解**：把复杂问题拆成「包含性检查」和「最小反转数计算」两个子问题，逐个解决。  
- **预处理优化**：提前存储每个单词的出现位置，避免重复查找。  
- **状态压缩**：用mask表示集合，将指数级的状态转化为可处理的二进制数。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
* **说明**：本代码综合了状态压缩DP的核心逻辑，实现了最小反转数的计算。

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

struct State {
    int min_inv;  // 最小反转数
    int last_pos; // 最后一个单词的位置
    State() : min_inv(INT_MAX), last_pos(-1) {}
    State(int inv, int pos) : min_inv(inv), last_pos(pos) {}
};

int main() {
    int n;
    cin >> n;
    vector<string> lesha(n);
    unordered_set<string> lesha_set;
    for (int i = 0; i < n; ++i) {
        cin >> lesha[i];
        lesha_set.insert(lesha[i]);
    }

    int m;
    cin >> m;
    int best_p = -1;
    int best_idx = -1;

    for (int idx = 1; idx <= m; ++idx) {
        int len;
        cin >> len;
        vector<string> archive(len);
        unordered_set<string> archive_set;
        for (int i = 0; i < len; ++i) {
            cin >> archive[i];
            archive_set.insert(archive[i]);
        }

        // 步骤1：检查是否包含所有单词
        bool contains_all = true;
        for (const string& word : lesha) {
            if (!archive_set.count(word)) {
                contains_all = false;
                break;
            }
        }
        if (!contains_all) continue;

        // 步骤2：构建过滤序列T'
        vector<string> T_prime;
        for (const string& word : archive) {
            if (lesha_set.count(word)) {
                T_prime.push_back(word);
            }
        }

        // 步骤3：预处理每个单词的位置列表
        unordered_map<string, int> word_to_rank;
        for (int i = 0; i < n; ++i) {
            word_to_rank[lesha[i]] = i;
        }
        vector<vector<int>> pos_list(n);
        for (int i = 0; i < T_prime.size(); ++i) {
            string word = T_prime[i];
            int rank = word_to_rank[word];
            pos_list[rank].push_back(i);
        }

        // 步骤4：状态压缩DP
        vector<vector<State>> dp(1 << n, vector<State>(n));
        // 初始化
        for (int j = 0; j < n; ++j) {
            if (!pos_list[j].empty()) {
                int mask = 1 << j;
                dp[mask][j] = State(0, pos_list[j][0]);
            }
        }

        // 转移
        for (int mask = 1; mask < (1 << n); ++mask) {
            for (int j = 0; j < n; ++j) {
                if (!(mask & (1 << j))) continue;
                State curr = dp[mask][j];
                if (curr.min_inv == INT_MAX) continue;

                for (int k = 0; k < n; ++k) {
                    if (mask & (1 << k)) continue;
                    // 找pos_list[k]中第一个大于curr.last_pos的位置
                    auto& pos = pos_list[k];
                    auto it = upper_bound(pos.begin(), pos.end(), curr.last_pos);
                    if (it == pos.end()) continue;
                    int p = *it;

                    // 计算新增反转数：mask中rank>k的数量
                    int added_inv = __builtin_popcount(mask & ((1 << n) - (1 << (k + 1))));
                    int new_inv = curr.min_inv + added_inv;
                    int new_mask = mask | (1 << k);

                    // 更新dp[new_mask][k]
                    if (new_inv < dp[new_mask][k].min_inv || 
                        (new_inv == dp[new_mask][k].min_inv && p < dp[new_mask][k].last_pos)) {
                        dp[new_mask][k] = State(new_inv, p);
                    }
                }
            }
        }

        // 找最小x
        int min_x = INT_MAX;
        for (int j = 0; j < n; ++j) {
            if (dp[(1 << n) - 1][j].min_inv < min_x) {
                min_x = dp[(1 << n) - 1][j].min_inv;
            }
        }
        if (min_x == INT_MAX) continue;

        // 计算p=2^(n - min_x)
        int p = 1 << (n - min_x);
        if (p > best_p || (p == best_p && idx < best_idx)) {
            best_p = p;
            best_idx = idx;
        }
    }

    if (best_idx == -1) {
        cout << "Brand new problem!" << endl;
    } else {
        cout << best_idx << endl;
        cout << "[: ";
        for (int i = 0; i < best_p - 1; ++i) {
            cout << "|";
        }
        cout << ":]" << endl;
    }

    return 0;
}
```

### 代码解读概要
- **输入处理**：读取Lesha的问题和archive问题。  
- **包含性检查**：用哈希集合快速判断archive是否包含所有单词。  
- **过滤序列T'**：保留archive中属于Lesha的单词，形成子序列。  
- **位置预处理**：记录每个单词在T'中的所有位置（按递增排序）。  
- **状态压缩DP**：初始化每个单词的初始状态，然后遍历所有mask，转移状态计算最小反转数。  
- **结果计算**：找到相似度最高的archive问题，输出结果。


## 5. 算法可视化：像素动画演示 (核心部分)

### 🎮 动画设计方案
**主题**：像素版「单词探险队」——帮助Lesha的单词找到一条「反转数最少」的路径穿过archive的单词森林。

### 核心演示内容
1. **场景初始化**：  
   - 屏幕左侧是「单词森林」（T'的像素化展示，每个单词用不同颜色的方块表示）。  
   - 屏幕右侧是「DP状态面板」：用8位像素的二进制灯表示`mask`（亮灯=已选单词），下方显示当前最小反转数和最后位置。  
   - 底部有「单步」「自动」「重置」按钮，以及速度滑块。

2. **算法执行演示**：  
   - **初始化**：每个单词的初始状态（mask=1<<j）用绿色灯点亮，显示反转数0和第一个位置。  
   - **转移过程**：  
     - 选中一个`mask`（例如`0001`），用黄色高亮。  
     - 尝试添加未选单词（例如`k=2`），找到其在森林中的位置（用红色箭头指向）。  
     - 计算新增反转数（用数字气泡显示），更新`new_mask`（`0011`）的灯为绿色，显示新的反转数和位置。  
   - **完成状态**：当`mask=1111`（所有灯亮），播放「胜利音效」，高亮最小反转数的状态。

3. **游戏化元素**：  
   - **音效**：选中`mask`时播放「叮」，转移成功播放「咔嗒」，完成播放「胜利旋律」。  
   - **关卡**：将DP的不同阶段设为「小关卡」（如「初始化关」「转移关」「完成关」），完成关卡获得像素星星奖励。

### 设计亮点
- 用**像素方块**直观展示单词和位置，用**二进制灯**展示`mask`，让抽象的状态变得可见。  
- 音效和关卡设计增加趣味性，帮助你记住关键步骤。


## 6. 拓展练习与相似问题思考

### 通用思路迁移
状态压缩DP常用于**小集合选择问题**，例如：  
- 旅行商问题（TSP）：用mask表示已访问的城市。  
- 子集和问题：用mask表示已选的元素。  
- 单词拼写问题：用mask表示已选的字母。

### 洛谷练习推荐
1. **洛谷 P1171** - 售货员的难题  
   🗣️ 推荐理由：经典TSP问题，用状态压缩DP解决，锻炼mask的使用。  
2. **洛谷 P1433** - 吃奶酪  
   🗣️ 推荐理由：类似TSP，需要记录最后位置，与本题的DP状态设计一致。  
3. **洛谷 P2622** - 关灯问题II  
   🗣️ 推荐理由：用mask表示灯的状态，练习状态转移的设计。


## 7. 学习心得与经验分享 (若有)
本次分析的题解中未发现明确的作者个人心得分享部分。


## 结语
通过这个问题，我们学习了**状态压缩DP**在子序列和反转数问题中的应用。关键是要将复杂的问题拆解成可处理的子问题，并用二进制mask高效表示集合状态。记得多做练习，熟练掌握位运算和DP状态设计——你会发现很多问题都能迎刃而解！💪

下次我们再一起探索新的编程挑战！✨

---
处理用时：479.51秒