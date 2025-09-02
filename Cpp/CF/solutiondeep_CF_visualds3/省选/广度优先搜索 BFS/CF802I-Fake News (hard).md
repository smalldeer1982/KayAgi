# 题目信息

# Fake News (hard)

## 题目描述

Now that you have proposed a fake post for the HC $ ^{2} $ Facebook page, Heidi wants to measure the quality of the post before actually posting it. She recently came across a (possibly fake) article about the impact of fractal structure on multimedia messages and she is now trying to measure the self-similarity of the message, which is defined as

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802I/cdbfdfc02921b55d94f8e9715364be36292f81c3.png)where the sum is over all nonempty strings $ p $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802I/aea1d5f3b9f7520d94fcc0daea05a447b5429c82.png) is the number of occurences of $ p $ in $ s $ as a substring. (Note that the sum is infinite, but it only has a finite number of nonzero summands.)

Heidi refuses to do anything else until she knows how to calculate this self-similarity. Could you please help her? (If you would like to instead convince Heidi that a finite string cannot be a fractal anyway – do not bother, we have already tried.)

## 说明/提示

A string $ s $ contains another string $ p $ as a substring if $ p $ is a contiguous subsequence of $ s $ . For example, ab is a substring of cab but not of acb.

## 样例 #1

### 输入

```
4
aa
abcd
ccc
abcc
```

### 输出

```
5
10
14
12
```

# AI分析结果

# 💡 Kay的C++算法解析：Fake News (hard) 深入学习指南 💡

## 引言
今天我们要解决的问题是**计算字符串所有子串出现次数的平方和**——听起来有点抽象？别担心，我们会用「后缀数组（SA）」和「后缀自动机（SAM）」这两个字符串处理的“神器”，把复杂问题变得清晰！


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：字符串处理（后缀数组/后缀自动机）

🗣️ **初步分析**：  
问题要求计算所有子串`p`的`cnt(p)²`之和（`cnt(p)`是`p`在原串中的出现次数）。直接枚举所有子串显然不现实（子串数量是`O(n²)`的，n是字符串长度），所以需要**高效的字符串压缩或排序技术**。

### 核心算法的比喻
- **后缀数组（SA）**：把字符串的所有后缀（比如`"abc"`的后缀是`"abc"`、`"bc"`、`"c"`）排成一队，相似的后缀会挨在一起。比如`"aaa"`的后缀排序后是`"aaa"`、`"aa"`、`"a"`，它们的共同前缀很长——这能帮我们快速统计相同子串的数量。  
- **后缀自动机（SAM）**：把所有子串“压缩”成一个自动机，每个节点代表一组**结尾位置相同**的子串（称为`endpos`集合）。比如`"abab"`中的`"ab"`和`"bab"`的结尾位置不同，但`"ab"`和`"b"`的结尾位置可能有重叠——SAM能高效管理这些子串的关系。

### 题解思路对比
- **SA派**：通过后缀排序得到`height`数组（相邻后缀的最长公共前缀），再用**单调栈**计算所有公共前缀的贡献（因为每对相邻后缀的公共前缀对应一组重复子串）。  
- **SAM派**：直接构建SAM，每个节点的贡献是`endpos大小² × 该节点代表的子串数量`（子串数量=节点最长长度-父节点最长长度）。

### 可视化设计思路
我们会设计一个**8位像素风的SAM演示动画**：  
- 用彩色方块代表SAM的节点（比如红色是初始节点，蓝色是新插入的节点）；  
- 插入字符时，动态展示节点的分裂、父节点的连接（比如用黄色线条表示父指针）；  
- 用“叮”的音效提示节点创建，“嗡”的音效提示节点分裂；  
- 最终用绿色高亮所有节点的`endpos`大小，直观展示每个子串的出现次数。


## 2. 精选优质题解参考

### 题解一：SA+单调栈（作者：hsfzLZH1，赞6）
* **点评**：  
  这道题的“经典SA解法”！思路非常清晰：先通过后缀排序将相似后缀排在一起，再用`height`数组记录相邻后缀的公共前缀长度。最巧妙的是**用单调栈优化贡献计算**——单调栈能快速统计所有“连续的最小公共前缀”，避免了暴力枚举的`O(n²)`复杂度。代码规范（变量名如`sa`、`height`含义明确），边界处理严谨（比如开`long long`防止溢出），是SA应用的“教科书级”范例。


### 题解二：SAM（作者：Alex_Wei，赞4）
* **点评**：  
  SAM的“极简实现”！利用SAM的核心性质：每个节点代表的子串数量是`len[p]-len[link(p)]`，出现次数是`endpos`大小（通过拓扑排序累加子树大小）。代码非常简洁，没有冗余逻辑，完美体现了SAM“压缩子串”的优势。对于想学习SAM的同学来说，这是一份“拿来就能用”的模板。


### 题解三：SA+并查集（作者：MoonPie，赞4）
* **点评**：  
  另一种有趣的SA思路！通过**并查集合并相似后缀**：按`height`从大到小排序，每次合并相邻的后缀（因为它们的公共前缀长），用`sum`维护当前长度子串的平方和。这种方法把“统计重复子串”转化为“合并集合”，逻辑更直观，适合刚学并查集的同学理解。


## 3. 核心难点辨析与解题策略

### 1. 问题转化：如何将平方和拆分为可计算的贡献？
- **分析**：直接计算`cnt(p)²`很难，但我们可以把它拆成“每个子串每次出现的贡献”——比如一个子串第k次出现时，贡献是`2(k-1)+1`（因为`k² - (k-1)² = 2k-1`）。这样总贡献等于“所有子串的出现次数之和”加上“两倍的重复出现次数之和”。  
- 💡 **学习笔记**：**转化问题**是解决复杂题的关键——把“平方和”拆成“增量贡献”，就能用算法高效统计。


### 2. 选择算法：SA还是SAM？
- **分析**：  
  - SA适合处理“前缀相似性”问题（比如统计公共前缀），但需要额外的单调栈/并查集优化；  
  - SAM更直接，因为它天生管理子串的`endpos`集合，能直接计算每个子串的出现次数。  
  对于本题，SAM的代码更简洁，但SA的思路更直观——根据自己的掌握程度选择。  
- 💡 **学习笔记**：**工具匹配问题**——不同的字符串算法有不同的擅长领域，要学会根据问题特征选择。


### 3. 处理关键数据结构：单调栈/并查集/SAM的parent树
- **分析**：  
  - SA的单调栈：维护“连续的最小公共前缀”，避免重复计算；  
  - SA的并查集：合并相似后缀，用集合大小统计出现次数；  
  - SAM的parent树：通过拓扑排序累加子树的`endpos`大小，得到每个节点的出现次数。  
- 💡 **学习笔记**：**数据结构是算法的“手脚”**——选择合适的数据结构能让算法事半功倍。


### ✨ 解题技巧总结
- **技巧1**：问题转化——将“平方和”拆成“增量贡献”，降低计算难度；  
- **技巧2**：算法选择——根据问题特征选SA（前缀相似）或SAM（子串压缩）；  
- **技巧3**：数据结构辅助——用单调栈/并查集/SAM的parent树优化统计。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考（SAM版）
* **说明**：综合多个SAM题解的思路，提炼出的简洁实现，适合快速上手。
* **完整核心代码**：
```cpp
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int N = 2e5 + 10;
struct SAM {
    int tot, last;
    int ch[N][26], len[N], fa[N], cnt[N];
    vector<int> G[N];
    SAM() { tot = last = 1; }
    void add(int c) {
        int p = last, np = ++tot;
        len[np] = len[p] + 1, cnt[np] = 1;
        last = np;
        while (p && !ch[p][c]) ch[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else {
            int q = ch[p][c];
            if (len[q] == len[p] + 1) fa[np] = q;
            else {
                int nq = ++tot;
                len[nq] = len[p] + 1;
                memcpy(ch[nq], ch[q], sizeof(ch[q]));
                fa[nq] = fa[q], fa[q] = fa[np] = nq;
                while (p && ch[p][c] == q) ch[p][c] = nq, p = fa[p];
            }
        }
    }
    long long calc() {
        long long ans = 0;
        for (int i = 2; i <= tot; i++) G[fa[i]].push_back(i);
        dfs(1);
        for (int i = 2; i <= tot; i++)
            ans += 1LL * cnt[i] * cnt[i] * (len[i] - len[fa[i]]);
        return ans;
    }
    void dfs(int u) {
        for (int v : G[u]) {
            dfs(v);
            cnt[u] += cnt[v];
        }
    }
    void clear() {
        memset(ch, 0, sizeof(ch));
        memset(len, 0, sizeof(len));
        memset(fa, 0, sizeof(fa));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i <= tot; i++) G[i].clear();
        tot = last = 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    SAM sam;
    while (T--) {
        string s; cin >> s;
        sam.clear();
        for (char c : s) sam.add(c - 'a');
        cout << sam.calc() << '\n';
    }
    return 0;
}
```
* **代码解读概要**：  
  1. **SAM初始化**：`tot`是节点总数，`last`是最后一个节点；  
  2. **插入字符**：`add`函数处理每个字符，创建新节点并维护父指针；  
  3. **计算贡献**：`calc`函数通过DFS统计每个节点的`endpos`大小（`cnt`数组），然后计算每个节点的贡献总和。


### 题解一：SA+单调栈核心片段
* **亮点**：用单调栈快速统计`height`数组的贡献。
* **核心代码片段**：
```cpp
ans = n * (n + 1) / 2; // 所有子串的基础贡献（出现1次）
stack<pair<int, int>> st;
st.push({0, 0});
for (int i = 1; i <= n; ++i) {
    while (height[i] < height[st.top().first]) st.pop();
    st.push({i, st.top().second + (i - st.top().first) * height[i]});
    ans += 2 * st.top().second; // 两倍的重复贡献
}
```
* **代码解读**：  
  - `ans`初始化为所有子串的数量（每个子串出现1次的贡献）；  
  - 单调栈维护“连续的最小`height`值”，栈中的`second`是当前所有公共前缀的总长度；  
  - 每次将当前`height`加入栈，然后把重复贡献（两倍的总长度）加到`ans`中。  
* 💡 **学习笔记**：单调栈是处理“连续区间最小值”的神器，能把`O(n²)`的计算优化到`O(n)`。


### 题解二：SAM核心片段
* **亮点**：用拓扑排序统计`endpos`大小。
* **核心代码片段**：
```cpp
// 拓扑排序（按len从大到小）
for (int i = 1; i <= cnt; i++) buc[len[i]]++;
for (int i = 1; i <= n; i++) buc[i] += buc[i-1];
for (int i = cnt; i >= 1; i--) id[buc[len[i]]--] = i;
// 累加endpos大小
for (int i = cnt; i >= 1; i--) ed[fa[id[i]]] += ed[id[i]];
```
* **代码解读**：  
  - 先按节点的`len`（最长子串长度）排序（拓扑序）；  
  - 然后从下往上累加每个节点的`ed`（`endpos`大小）到父节点——因为父节点的`endpos`包含所有子节点的`endpos`。  
* 💡 **学习笔记**：SAM的`parent`树是“后缀链接树”，子节点的`endpos`是父节点的子集，所以可以用拓扑排序快速统计。


## 5. 算法可视化：像素动画演示 (SAM版)

### 动画演示主题：像素SAM的“字符插入之旅”
**设计思路**：用8位像素风模拟SAM的构建过程，让你“看得到”子串的压缩！


### 动画帧步骤与交互关键点
1. **初始化场景**（FC红白机风格）：  
   - 屏幕左侧是**字符输入区**（显示当前输入的字符，比如`a`、`b`）；  
   - 中间是**SAM可视化区**（用彩色方块代表节点，红色是初始节点`1`）；  
   - 右侧是**控制面板**（“开始”“单步”“重置”按钮，速度滑块）。  
   - 播放轻松的8位BGM（比如《超级马里奥》的背景音乐）。

2. **插入字符`a`**：  
   - 新建节点`2`（蓝色方块），连接到初始节点`1`（红色→蓝色的线条）；  
   - 节点`2`的`len`显示为`1`（最长子串是`"a"`），`cnt`显示为`1`（出现1次）；  
   - 播放“叮”的音效，表示节点创建成功。

3. **插入字符`b`**：  
   - 新建节点`3`（绿色方块），连接到节点`1`；  
   - 节点`3`的`len`是`2`（最长子串是`"ab"`），`cnt`是`1`；  
   - 音效“叮”再次响起。

4. **插入字符`a`**（触发节点分裂）：  
   - 新建节点`4`（黄色方块），但发现节点`2`的`len`不符合要求；  
   - 分裂节点`2`为`5`（橙色方块），调整父指针（节点`4`和`2`的父节点变为`5`）；  
   - 播放“嗡”的音效，表示节点分裂；  
   - 节点`5`的`len`是`1`（最长子串是`"a"`），`cnt`是`2`（`"a"`出现2次）。

5. **结束状态**：  
   - 所有节点的`cnt`（`endpos`大小）用绿色数字显示；  
   - 每个节点的贡献（`cnt² × (len - parent.len)`）用黄色数字显示；  
   - 总贡献用红色大字显示在屏幕顶部；  
   - 播放“胜利”音效（比如《魂斗罗》的通关音乐）。


### 交互设计
- **单步执行**：点击“单步”按钮，逐个字符插入，观察SAM的变化；  
- **自动播放**：拖动速度滑块调整播放速度，自动演示整个过程；  
- **重置**：点击“重置”按钮，回到初始状态，重新开始。


## 6. 拓展练习与相似问题思考

### 通用思路迁移
SAM和SA不仅能解决本题，还能处理：
1. **统计不同子串的数量**（SAM的节点数减1）；  
2. **求两个字符串的最长公共子串**（SAM合并两个字符串）；  
3. **统计子串的出现次数**（SAM的`endpos`大小）。


### 洛谷练习推荐
1. **洛谷 P4248 [AHOI2013] 差异**  
   🗣️ **推荐理由**：用SA的`height`数组计算所有后缀对的LCP之和，巩固SA的应用。  
2. **洛谷 P3181 [HAOI2016] 找相同字符**  
   🗣️ **推荐理由**：用SAM合并两个字符串，统计公共子串的出现次数，拓展SAM的用法。  
3. **洛谷 P5546 [POI2000] 公共子串**  
   🗣️ **推荐理由**：求多个字符串的最长公共子串，练习SAM的多字符串处理。


## 7. 学习心得与经验分享 (若有)

> **参考经验（来自huayucaiji）**：“对于单调栈的思考，我有一个小技巧，可以通过画柱形图来帮助思考，这样会很直观。”  
> **点评**：这个技巧非常实用！比如SA的`height`数组可以看作柱形图的高度，单调栈维护的是“连续的最小高度”——画个图就能快速理解栈的作用，避免死记硬背。


## 结论
通过SA和SAM，我们把“统计子串出现次数的平方和”这个复杂问题，转化为了**排序+单调栈**或**自动机压缩**的简单问题。记住：**字符串问题的核心是“压缩”或“排序”相似的子串**，找到它们的共同特征，就能高效计算！

下次遇到字符串问题，不妨想想：“SA能排好队吗？SAM能压缩吗？”——你会发现很多问题都能迎刃而解！💪

---
处理用时：87.10秒