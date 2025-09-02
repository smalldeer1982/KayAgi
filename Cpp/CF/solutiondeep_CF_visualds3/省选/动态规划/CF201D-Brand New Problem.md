# 题目信息

# Brand New Problem

## 题目描述

A widely known among some people Belarusian sport programmer Lesha decided to make some money to buy a one square meter larger flat. To do this, he wants to make and carry out a Super Rated Match (SRM) on the site Torcoder.com. But there's a problem — a severe torcoder coordinator Ivan does not accept any Lesha's problem, calling each of them an offensive word "duped" (that is, duplicated). And one day they nearely quarrelled over yet another problem Ivan wouldn't accept.

You are invited to act as a fair judge and determine whether the problem is indeed brand new, or Ivan is right and the problem bears some resemblance to those used in the previous SRMs.

You are given the descriptions of Lesha's problem and each of Torcoder.com archive problems. The description of each problem is a sequence of words. Besides, it is guaranteed that Lesha's problem has no repeated words, while the description of an archive problem may contain any number of repeated words.

The "similarity" between Lesha's problem and some archive problem can be found as follows. Among all permutations of words in Lesha's problem we choose the one that occurs in the archive problem as a subsequence. If there are multiple such permutations, we choose the one with the smallest number of inversions. Then the "similarity" of a problem can be written as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF201D/7915a415961b72b48e6cd878bc6adf37cd6bd951.png), where $ n $ is the number of words in Lesha's problem and $ x $ is the number of inversions in the chosen permutation. Note that the "similarity" $ p $ is always a positive integer.

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

# 💡 Kay的C++算法解析：Brand New Problem 深入学习指南 💡

## 引言
今天我们来分析一道来自Codeforces的经典问题——**Brand New Problem**。这道题的核心是**状压动态规划（DP）的维度优化**，非常适合锻炼我们对状态设计和复杂度分析的能力。让我们一起拆解问题，理解算法的巧妙之处吧！


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：状压DP + 维度优化（针对小值域状态的巧妙转换）

### 🗣️ 初步分析
解决这道题的关键，在于理解两个核心问题：
1. **如何判断archive问题是否包含Lesha问题的排列作为子序列？**  
2. **如何找到该排列中逆序对最少的（即顺序对最多的）？**

#### 核心算法思想：状压DP的“维度反转”
Lesha的问题有**n个无重复单词**（n≤15），这意味着我们可以用**二进制掩码（mask）**表示“已选单词的集合”（比如mask=0b101表示选了第0和第2个单词）。

直接的状压DP思路是：`dp[i][mask]`表示“遍历到archive序列的第i位时，选了mask中的单词的最小逆序对数量”。但archive序列的长度k可以达到5e5，这样的复杂度（O(k*2ⁿ)）会直接超时！

**优化的关键**：逆序对的数量最多是`n*(n-1)/2=105`（当n=15时），这个值域非常小。于是我们**反转DP的维度**——将“逆序对数量”作为状态的一部分，将“所需的最短前缀长度”作为DP的值。具体来说：
- `dp[mask][s]`表示“选了mask中的单词，顺序对数量为s时，所需的archive序列最短前缀长度”。
- 我们的目标是找到**最大的s**（顺序对最多→逆序对最少），使得`dp[full_mask][s] ≤ 序列长度`（full_mask是选了所有单词的掩码）。

#### 核心流程与可视化设计
1. **预处理next数组**：记录archive序列中每个位置之后第一个出现某单词的位置（用于快速查找下一个单词）。
2. **DP初始化**：`dp[0][0] = 0`（选0个单词，顺序对0，用0长度前缀）。
3. **状态转移**：对于每个mask和s，如果`dp[mask][s]`有效，遍历所有未选单词i，计算增加的顺序对数量（mask中比i小的单词数），更新新的mask和s对应的最短前缀长度。
4. **结果计算**：找full_mask下最大的s，计算相似度p=s+1。

**可视化设计思路**：用8位像素风格展示：
- 左侧是archive序列的单词（用编号0~n-1的像素块表示）；
- 中间是**掩码灯板**（15个像素灯，亮表示已选单词）；
- 右侧是**状态显示区**（当前顺序对s、最短前缀长度）；
- 转移时，用箭头指向next位置的单词，高亮新选的灯，弹出“+cnt”的动画（cnt是增加的顺序对），并播放“叮”的像素音效。


## 2. 精选优质题解参考

### 题解一：作者chenxia25（赞：5）
**点评**：这道题的“维度反转”思路是关键，作者准确抓住了“逆序对数量小”的特点，将DP的状态从“前缀位置+掩码”转为“掩码+顺序对”，直接解决了超时问题。文中提到的“调换定义域和值域”的套路（类似809D问题），是状压DP优化的经典技巧，值得牢记。此外，作者对next数组的预处理和转移逻辑的分析非常清晰，为后续代码实现奠定了基础。

### 题解二：作者Tyyyyyy（赞：1）
**点评**：作者进一步简化了题意，将问题转化为“找数字序列中排列子序列的最小逆序对”，并给出了**next数组的具体实现代码**和**转移方程**。转移方程中，通过遍历未选单词i，计算mask中比i小的数量（顺序对增量），并更新新状态的最短前缀长度，逻辑非常直接。这部分代码是核心，帮助我们快速理解如何将思路转化为代码。

### 题解三：作者LastKismet（赞：0）
**点评**：作者给出了**完整的C++代码**，包含了从字符串转编号、next数组预处理、DP初始化与转移、结果计算的全流程。代码中的`chmin`函数（取最小值）、`__builtin_popcount`（统计二进制中1的个数）等技巧，是C++竞赛中的常用操作。特别是最后从大到小遍历顺序对s的部分，直接找到最大的可行s，非常高效。


## 3. 核心难点辨析与解题策略

### 1. 如何优化状压DP的高复杂度？
**难点**：直接状压DP的复杂度是O(k*2ⁿ)，k=5e5时会超时。  
**策略**：利用“顺序对数量小”的特点，反转DP维度——将“顺序对数量”作为状态，“最短前缀长度”作为值。这样复杂度降到O(2ⁿ * n²)（n=15时，2ⁿ=32768，n²=225，总操作约7e6次），完全可行。

💡 **学习笔记**：当状压DP的某一维值域很小时，试试“反转维度”，把小值域的量作为状态的一部分！

### 2. 如何快速找到下一个单词的位置？
**难点**：每次找下一个单词都遍历序列会超时。  
**策略**：预处理`next[pos][i]`数组，从后往前遍历序列，记录每个位置pos之后第一个出现i的位置。这样查询时可以O(1)得到结果。

💡 **学习笔记**：预处理“下一个元素的位置”是处理子序列问题的常用优化！

### 3. 如何计算顺序对的增量？
**难点**：选一个新单词i时，需要知道已选单词中比i小的数量（即增加的顺序对）。  
**策略**：用位运算！mask中比i小的单词对应的位是`mask & ((1<<i)-1)`，统计其中1的个数（用`__builtin_popcount`）就是顺序对的增量。

💡 **学习笔记**：位运算可以快速统计“已选集合中的小元素数量”，避免遍历！


### ✨ 解题技巧总结
- **问题转化**：将字符串问题转为数字问题（用map给单词编号），简化处理。
- **维度反转**：状压DP超时？看看有没有小值域的维度可以反转。
- **预处理优化**：next数组快速找下一个元素，避免重复遍历。
- **位运算技巧**：用`__builtin_popcount`快速统计二进制中1的个数。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
**说明**：综合了三个题解的思路，实现了完整的核心逻辑。

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <climits>
using namespace std;

const int N = 15;
const int MAX_MASK = 1 << N;
const int MAX_S = N * (N - 1) / 2; // 最大顺序对数量

int main() {
    int n, m;
    map<string, int> word_id;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        word_id[s] = i;
    }
    cin >> m;
    int best_ans = -1;
    int best_p = 0;
    int best_idx = -1;

    for (int idx = 1; idx <= m; ++idx) {
        int k;
        cin >> k;
        vector<int> seq;
        for (int i = 0; i < k; ++i) {
            string s;
            cin >> s;
            if (word_id.count(s)) {
                seq.push_back(word_id[s]);
            }
        }
        int len = seq.size();
        vector<vector<int>> next(len + 1, vector<int>(n, len + 1));
        // 预处理next数组：从后往前
        for (int i = len - 1; i >= 0; --i) {
            next[i] = next[i + 1];
            next[i][seq[i]] = i + 1; // 下一个位置是i+1（因为seq的索引是0-based）
        }

        // 初始化DP数组：dp[mask][s] = 最小前缀长度
        vector<vector<int>> dp(MAX_MASK, vector<int>(MAX_S + 1, len + 1));
        dp[0][0] = 0;

        for (int mask = 0; mask < MAX_MASK; ++mask) {
            for (int s = 0; s <= MAX_S; ++s) {
                if (dp[mask][s] > len) continue;
                // 遍历所有未选的单词i
                for (int i = 0; i < n; ++i) {
                    if (mask & (1 << i)) continue;
                    // 计算增加的顺序对数量：mask中比i小的单词数
                    int add = __builtin_popcount(mask & ((1 << i) - 1));
                    int new_s = s + add;
                    if (new_s > MAX_S) continue;
                    int new_mask = mask | (1 << i);
                    int new_pos = next[dp[mask][s]][i];
                    if (new_pos <= len) {
                        if (new_pos < dp[new_mask][new_s]) {
                            dp[new_mask][new_s] = new_pos;
                        }
                    }
                }
            }
        }

        // 找最大的s，使得dp[full_mask][s] <= len
        int full_mask = (1 << n) - 1;
        int max_s = -1;
        for (int s = MAX_S; s >= 0; --s) {
            if (dp[full_mask][s] <= len) {
                max_s = s;
                break;
            }
        }
        if (max_s != -1) {
            int p = max_s + 1;
            if (p > best_p || (p == best_p && idx < best_idx)) {
                best_p = p;
                best_idx = idx;
            }
        }
    }

    if (best_idx != -1) {
        cout << best_idx << endl;
        cout << "[:";
        for (int i = 0; i < best_p; ++i) cout << "|";
        cout << ":]" << endl;
    } else {
        cout << "Brand new problem!" << endl;
    }
    return 0;
}
```

**代码解读概要**：
1. **输入处理**：用map将Lesha的单词转为0~n-1的编号。
2. **遍历每个archive问题**：提取有用的单词序列（仅包含Lesha的单词）。
3. **预处理next数组**：从后往前记录每个位置之后第一个出现某单词的位置。
4. **DP初始化**：`dp[0][0] = 0`，其他状态初始化为序列长度+1（表示不可达）。
5. **状态转移**：遍历每个mask和s，尝试选未选的单词i，计算顺序对增量，更新新状态的最短前缀长度。
6. **结果计算**：找full_mask下最大的s，计算p=s+1，记录最优的archive问题。


### 题解三核心代码片段赏析
**来源**：LastKismet的题解  
**亮点**：完整实现了next数组和DP转移，代码简洁高效。

**核心代码片段**：
```cpp
// 预处理next数组
repl(i,0,n)nxt[len][i]=len+1;
per(i,len-1,0){
    repl(j,0,n)nxt[i][j]=nxt[i+1][j];
    nxt[i][v[i]]=i+1;
}
// DP初始化与转移
repl(s,0,1<<n)rep(j,0,n*(n-1)>>1)f[s][j]=len+1;
f[0][0]=0;
repl(s,0,1<<n)rep(j,0,n*(n-1)>>1)if(f[s][j]<=len){
    int ans=0;
    repl(i,0,n){
        if(s&1<<i)++ans;
        else chmin(f[s|1<<i][j+ans],nxt[f[s][j]][i]);
    }
}
```

**代码解读**：
- **next数组**：`nxt[i][j]`表示序列中位置i之后第一个j的位置。从后往前遍历，保证每个位置的next值是最小的。
- **DP初始化**：`f[s][j]`初始化为len+1（不可达），`f[0][0] = 0`（选0个单词，顺序对0）。
- **转移逻辑**：遍历每个mask（s）和顺序对j，如果当前状态可达（`f[s][j] <= len`），则遍历所有单词i：
  - 如果i已选（`s&1<<i`），则ans增加1（统计已选的比i小的单词数？不，等一下，这里的i是遍历顺序0~n-1，所以当i未选时，ans是已选的比i小的单词数（因为前面的i' < i已经被遍历过，如果已选则ans++）。
  - 如果i未选，则更新新状态`f[s|1<<i][j+ans]`为`min(当前值, next[f[s][j]][i])`（即选i后的最短前缀长度）。

**学习笔记**：遍历单词时按0~n-1的顺序，可以自然统计已选的比i小的单词数，不用额外计算！


## 5. 算法可视化：像素动画演示（核心部分）

### 动画演示主题：像素探险家找“顺序对宝藏”
我们用8位像素风格（类似FC游戏），模拟**DP状态转移**的过程，帮助直观理解“掩码变化”“顺序对增加”和“next数组查询”。

### 设计思路
- **风格**：采用FC红白机的配色（比如蓝色背景、黄色文字、红色高亮），用16x16的像素块表示单词编号，用小灯表示掩码状态。
- **交互**：支持“单步执行”“自动播放”（速度可调），关键操作时有像素音效（比如选单词时“叮”，找到full_mask时“咻”）。
- **游戏化元素**：将每个mask的转移视为“小关卡”，完成full_mask时弹出“胜利”动画（像素星星闪烁），增加成就感。

### 动画帧步骤
1. **初始场景**：
   - 左侧：archive序列的单词（比如编号0、1、2、3的像素块，排列成一行）。
   - 中间：掩码灯板（15个小灯，初始全灭）。
   - 右侧：状态显示区（显示当前mask=0、s=0、pos=0）。
   - 底部：控制面板（单步、自动、重置按钮，速度滑块）。

2. **预处理next数组**：
   - 从后往前遍历序列，每个位置的next值用“虚线箭头”指向对应的单词位置（比如pos=0的next[0][1]指向pos=2）。

3. **DP转移演示**：
   - 选中mask=0（全灭）、s=0：遍历未选单词0（第一个单词），计算add=0（mask中无更小的单词），new_s=0，new_pos=next[0][0]（比如pos=1）。
   - 动画：mask灯板的第0个灯亮起（红色），状态显示区的mask变为0b1，s变为0，pos变为1，同时播放“叮”的音效。
   - 接着，处理mask=0b1（选了0）、s=0：遍历未选单词1，add=1（mask中0<1，所以add=1），new_s=1，new_pos=next[1][1]（比如pos=3）。
   - 动画：第1个灯亮起，s变为1，pos变为3，播放“叮”音效。

4. **完成full_mask**：
   - 当mask变为0b1111（n=4）时，状态显示区的s达到最大值（比如3），弹出“胜利”动画（像素星星从mask灯板飞出），播放“咻”的音效，并显示p=s+1=4。

### 旁白提示
- “现在处理mask=0，s=0，选单词0，add=0，pos变1！”
- “mask=0b1，选单词1，add=1（因为0<1），s变1！”
- “full_mask达成！最大s=3，p=4，相似度最高！”


## 6. 拓展练习与相似问题思考

### 通用思路迁移
状压DP的“维度反转”技巧，适用于**n小但另一维度值域小**的问题，比如：
- 求“集合覆盖问题”中覆盖所有元素的最小代价（代价值域小）。
- 求“旅行商问题”中经过所有城市的最短路径（路径长度值域小）。
- 求“子集和问题”中能组成目标和的最小子集大小（子集大小值域小）。

### 洛谷练习推荐
1. **洛谷 P809D** - Hitchhiking in the Baltic States  
   🗣️ **推荐理由**：这道题和本题的“维度反转”思路完全一致，都是将“值域小的量”作为状态，锻炼你对状压DP优化的掌握。

2. **洛谷 P1896** - 互不侵犯  
   🗣️ **推荐理由**：经典的状压DP问题，需要设计状态表示“第i行的状态mask，已放k个国王”，适合巩固状压DP的基础。

3. **洛谷 P2622** - 关灯问题II  
   🗣️ **推荐理由**：n≤10，状压DP的典型应用，需要求“最少按开关次数”，可以用BFS+状压，也可以用DP，适合拓展思路。


## 7. 学习心得与经验分享（若有）
**参考经验（来自chenxia25）**：“我一开始想的是直接状压DP，但空间和时间都不行，后来看题解学到了‘调换定义域和值域’的技巧，才解决了问题。”  
**点评**：这位作者的经历很典型！当常规状压DP超时或超空间时，一定要**观察数据范围中的“小值”**——比如本题的“顺序对数量”，然后尝试反转维度，将小值作为状态的一部分。这是状压DP优化的“黄金法则”！


## 总结
通过这道题，我们学会了**状压DP的维度反转技巧**，掌握了预处理next数组、位运算统计顺序对的方法。记住：**算法的优化往往来自对数据范围的敏锐观察**——找到那个“小值域的维度”，就能打开解题的突破口！

下次遇到状压DP问题时，不妨先问问自己：“有没有哪个维度的取值范围很小？能不能反转？” 相信你会有新的收获！💪

---
处理用时：137.24秒