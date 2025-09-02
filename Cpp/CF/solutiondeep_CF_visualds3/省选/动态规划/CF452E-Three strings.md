# 题目信息

# Three strings

## 题目描述

You are given three strings $ (s_{1},s_{2},s_{3}) $ . For each integer $ l $ $ (1<=l<=min(|s_{1}|,|s_{2}|,|s_{3}|) $ you need to find how many triples ( $ i_{1},i_{2},i_{3} $ ) exist such that three strings $ s_{k}[i_{k}...\ i_{k}+l-1] $ $ (k=1,2,3) $ are pairwise equal. Print all found numbers modulo $ 1000000007 (10^{9}+7) $ .

See notes if you are not sure about some of the denotions used in the statement.

## 说明/提示

Consider a string $ t=t_{1}t_{2}...\ t_{|t|} $ , where $ t_{i} $ denotes the $ i $ -th character of the string, and $ |t| $ denotes the length of the string.

Then $ t[i...\ j] $ $ (1<=i<=j<=|t|) $ represents the string $ t_{i}t_{i+1}...\ t_{j} $ (substring of $ t $ from position $ i $ to position $ j $ inclusive).

## 样例 #1

### 输入

```
abc
bc
cbc
```

### 输出

```
3 1 
```

## 样例 #2

### 输入

```
abacaba
abac
abcd
```

### 输出

```
11 2 0 0 
```

# AI分析结果

# 💡 Kay的C++算法解析：Three Strings 深入学习指南 💡

<introduction>
  今天我们来一起攻克「Three Strings」这道字符串难题！题目要求我们找出三个字符串中所有长度相同且内容一致的子串组合数量。本指南会用**广义后缀自动机（广义SAM）**这个“字符串神器”帮你理清思路，还会通过像素动画让算法“动起来”，让学习更有趣～
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：字符串（广义后缀自动机+差分）

🗣️ **初步分析**：
解决这道题的关键是**广义后缀自动机（广义SAM）**——它就像一个“超级字符串字典”，能把多个字符串的所有子串高效地“压缩”存储，每个节点代表一群“长得一样、出现规律也一样”的子串。我们的目标是：
1. 用广义SAM把三个字符串的子串统一管理；
2. 统计每个子串在三个串中分别出现的次数；
3. 把每个子串的贡献（次数相乘）分配到对应的长度区间，最后用**差分**快速计算每个长度的总答案。

### 核心算法流程与可视化设计思路
- **广义SAM构建**：逐个字符扩展三个字符串，每个节点记录子串的长度范围（比如节点`x`的子串长度是`[link[x].len+1, x.len]`）。
- **次数统计**：通过DFS从叶子节点向上合并，统计每个子串在三个串中的出现次数（子节点的子串是父节点的后缀，所以次数要累加）。
- **差分贡献**：每个节点的贡献是`次数1×次数2×次数3`，对应长度区间`[link[x].len+1, x.len]`，用差分数组标记区间加减。
- **可视化设计**：用8位像素风格展示SAM的构建过程（节点像“积木”一样拼接），次数用数字像素块显示，差分用“进度条”动态更新，最后前缀和生成答案时会有“胜利音效”～

---

## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度、代码可读性、算法有效性**三个维度筛选了3份优质题解，帮你快速掌握核心逻辑～
</eval_intro>

**题解一：Memory_of_winter（赞3）**
* **点评**：这份题解是广义SAM的“标准模板级实现”！思路非常直白：先建广义SAM，用DFS统计每个节点在三个串中的出现次数，再通过差分将节点贡献映射到长度区间。代码结构工整（比如`SAM`命名空间封装核心逻辑），变量名`sz[i][tg]`清晰表示节点`i`在第`tg`个串中的次数。尤其值得学习的是**差分处理**——用`ans[R[fail[i]]+1] += tmp`和`ans[R[i]+1] -= tmp`快速标记区间，最后前缀和得到答案，效率极高！

**题解二：2018LZY（赞1）**
* **点评**：这是一份“极简版广义SAM”！代码去掉了冗余的封装，直接用结构体`tr`表示SAM节点，`add`函数简洁实现了SAM的扩展逻辑。亮点在于**排序合并次数**——用`Sort`函数按节点长度从大到小排序，保证父节点的次数是子节点的累加。差分部分的`upd`函数（用位运算处理模运算）很巧妙，值得借鉴！

**题解三：foreverlasting（赞0）**
* **点评**：这份题解的注释非常详细（比如`dfs`函数里的`sz[x][0]+=sz[tox][0]`明确说明合并子节点次数），适合新手理解SAM的“树状结构”。代码中`addedge`函数构建了SAM的后缀树（父节点是`link`），`dfs`遍历后缀树合并次数的逻辑非常直观，能帮你快速掌握“子串次数累加”的原理～

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的“坑”主要集中在**广义SAM的理解**和**贡献的区间处理**上。结合优质题解，我帮你提炼了3个核心难点和解决策略：
</difficulty_intro>

1. **难点1：广义SAM的节点到底代表什么？**
    * **分析**：SAM的每个节点代表一组“endpos相同”的子串（endpos是子串在原串中所有结束位置的集合）。比如节点`x`的子串长度范围是`[link[x].len+1, x.len]`——`link[x]`是`x`的父节点，代表更短的后缀子串。
    * 💡 **学习笔记**：节点的长度范围是SAM的“核心属性”，所有贡献都要基于这个范围计算！

2. **难点2：如何统计子串在三个串中的出现次数？**
    * **分析**：每个字符串的前缀对应SAM中的一条路径，我们先标记路径上的节点（比如第`tg`个串的前缀对应节点`p`，则`sz[p][tg]++`）。然后通过DFS从叶子节点向上合并——因为子节点的子串是父节点的后缀，所以父节点的次数是所有子节点次数的和。
    * 💡 **学习笔记**：DFS合并是“自底向上”的，这样能保证父节点的次数包含所有子串的出现情况！

3. **难点3：如何把节点贡献映射到长度区间？**
    * **分析**：节点`x`的贡献是`sz[x][0]×sz[x][1]×sz[x][2]`（三个串中出现次数的乘积），对应长度区间`[link[x].len+1, x.len]`。用差分数组`d`标记：`d[L] += 贡献`，`d[R+1] -= 贡献`，最后前缀和`d`数组就能得到每个长度`l`的答案。
    * 💡 **学习笔记**：差分是处理“区间加、单点查”的神器，能把`O(n)`的区间操作变成`O(1)`！

### ✨ 解题技巧总结
- **技巧1：用广义SAM统一管理多字符串的子串**：避免重复处理每个字符串，效率更高。
- **技巧2：DFS合并子节点次数**：利用SAM的树状结构（后缀树），快速统计每个子串的出现次数。
- **技巧3：差分处理区间贡献**：把节点的长度范围转化为差分操作，最后前缀和得到答案，时间复杂度`O(n)`。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**通用核心实现**——综合了优质题解的精华，结构清晰，适合新手模仿～
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码基于Memory_of_winter和foreverlasting的题解，封装了广义SAM的构建、次数统计和差分处理，逻辑完整且易读。
* **完整核心代码**：
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 3e5 + 10;
const int MAX_NODE = 6e5 + 10; // 广义SAM节点数是原串长度的2倍

// 广义SAM结构
struct SAM {
    int len[MAX_NODE], link[MAX_NODE]; // len: 节点最长子串长度; link: 后缀链接
    int nxt[MAX_NODE][26]; // 转移边
    int cnt, last; // cnt: 节点数; last: 最后一个节点
    long long sz[MAX_NODE][3]; // sz[i][j]: 节点i在第j个串中的出现次数

    SAM() {
        cnt = last = 1;
        memset(len, 0, sizeof(len));
        memset(link, 0, sizeof(link));
        memset(nxt, 0, sizeof(nxt));
        memset(sz, 0, sizeof(sz));
    }

    // 扩展字符c（0~25），属于第tg个串（0~2）
    void extend(int c, int tg) {
        int p = last;
        int np = ++cnt;
        last = np;
        len[np] = len[p] + 1;
        sz[np][tg] = 1; // 当前节点对应第tg个串的一个前缀

        // 沿着后缀链接更新转移边
        while (p && !nxt[p][c]) {
            nxt[p][c] = np;
            p = link[p];
        }

        if (!p) {
            link[np] = 1; // 没有后缀，链接到根节点
        } else {
            int q = nxt[p][c];
            if (len[p] + 1 == len[q]) {
                link[np] = q; // q是p的直接后缀
            } else {
                // 分裂q为nq，复制q的转移边和链接
                int nq = ++cnt;
                len[nq] = len[p] + 1;
                link[nq] = link[q];
                memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
                // 更新p及其祖先的转移边到nq
                while (p && nxt[p][c] == q) {
                    nxt[p][c] = nq;
                    p = link[p];
                }
                link[q] = link[np] = nq; // q和np的链接指向nq
            }
        }
    }
} sam;

// 后缀树的邻接表（用于DFS合并次数）
int head[MAX_NODE], edge_cnt;
struct Edge { int to, next; } edges[MAX_NODE];

void add_edge(int u, int v) {
    edges[++edge_cnt] = {v, head[u]};
    head[u] = edge_cnt;
}

// DFS合并子节点的次数到父节点
void dfs(int u) {
    for (int i = head[u]; i; i = edges[i].next) {
        int v = edges[i].to;
        dfs(v);
        // 合并v的次数到u
        for (int tg = 0; tg < 3; tg++) {
            sam.sz[u][tg] += sam.sz[v][tg];
        }
    }
}

int ans[MAXN]; // 差分数组
char s[MAXN];

int main() {
    int min_len = MAXN;
    // 处理三个字符串，构建广义SAM
    for (int tg = 0; tg < 3; tg++) {
        cin >> s;
        int len = strlen(s);
        min_len = min(min_len, len);
        sam.last = 1; // 每个字符串重新从根节点开始扩展
        for (int i = 0; i < len; i++) {
            sam.extend(s[i] - 'a', tg);
        }
    }

    // 构建后缀树的邻接表（link指向父节点）
    for (int i = 2; i <= sam.cnt; i++) {
        add_edge(sam.link[i], i);
    }

    // DFS合并次数
    dfs(1);

    // 差分处理每个节点的贡献
    for (int i = 2; i <= sam.cnt; i++) {
        long long贡献 = sam.sz[i][0] * sam.sz[i][1] % MOD;
        贡献 = 贡献 * sam.sz[i][2] % MOD;
        int L = sam.len[sam.link[i]] + 1;
        int R = sam.len[i];
        ans[L] = (ans[L] + 贡献) % MOD;
        ans[R + 1] = (ans[R + 1] - 贡献 + MOD) % MOD;
    }

    // 前缀和计算最终答案
    long long current = 0;
    for (int l = 1; l <= min_len; l++) {
        current = (current + ans[l]) % MOD;
        cout << current << " ";
    }
    cout << endl;

    return 0;
}
```
* **代码解读概要**：
  1. **SAM构建**：`extend`函数逐个字符扩展三个字符串，每个字符对应SAM的一个节点，记录子串长度和转移边。
  2. **后缀树构建**：用`add_edge`函数把每个节点的`link`（后缀链接）转化为树的边，形成后缀树。
  3. **次数合并**：`dfs`函数从根节点遍历后缀树，把子节点的次数累加到父节点。
  4. **差分与前缀和**：计算每个节点的贡献，用差分标记区间，最后前缀和得到每个长度`l`的答案。

---

<code_intro_selected>
接下来看**优质题解的核心片段**，学习它们的“巧妙细节”～
</code_intro_selected>

**题解一：Memory_of_winter的差分处理**
* **亮点**：用`reduce`函数简化模运算，避免负数！
* **核心代码片段**：
```cpp
inline void reduce(int &x) { x += x >> 31 & MOD; } // 处理负数模运算
// ...
for (int i = 2; i <= idx; i++) {
    int tmp = 1LL * sz[i][0] * sz[i][1] % MOD * sz[i][2] % MOD;
    reduce(ans[R[fail[i]] + 1] += tmp - MOD); // ans[L] += tmp
    reduce(ans[R[i] + 1] -= tmp); // ans[R+1] -= tmp
}
```
* **代码解读**：
  - `reduce`函数用位运算处理负数：如果`x`是负数（`x >> 31`为`-1`），则加`MOD`；否则加`0`。
  - 差分操作`ans[L] += tmp`和`ans[R+1] -= tmp`，`reduce`确保结果在`0~MOD-1`之间。
* 💡 **学习笔记**：模运算中处理负数的小技巧，能避免`if`判断，代码更简洁！

**题解二：2018LZY的排序合并**
* **亮点**：按节点长度从大到小排序，保证父节点在子节点之后处理！
* **核心代码片段**：
```cpp
void Sort() {
    for (int i = 0; i <= mx; i++) c[i] = 0;
    for (int i = 1; i <= tot; i++) c[tr[i].len]++;
    for (int i = 1; i <= mx; i++) c[i] += c[i-1];
    for (int i = tot; i; i--) b[c[tr[i].len]--] = i;
}
// ...
Sort();
for (int i = tot; i > 1; i--) {
    int j = b[i], fa = tr[j].fa;
    for (int k = 0; k < 3; k++) f[fa][k] += f[j][k];
}
```
* **代码解读**：
  - `Sort`函数用计数排序按`tr[i].len`从大到小排序（`b`数组是排序后的节点顺序）。
  - 遍历`b`数组，把每个节点的次数累加到父节点——因为父节点的长度比子节点小，所以子节点先处理，父节点后处理，保证次数正确。
* 💡 **学习笔记**：计数排序是处理SAM节点排序的“黄金搭档”，时间复杂度`O(n)`！

**题解三：foreverlasting的DFS合并**
* **亮点**：用邻接表构建后缀树，DFS逻辑直观！
* **核心代码片段**：
```cpp
void dfs(const int &x) {
    for (res i = head[x]; ~i; i = edge[i].next) {
        res tox = edge[i].to;
        dfs(tox);
        sz[x][0] += sz[tox][0], sz[x][1] += sz[tox][1], sz[x][2] += sz[tox][2];
    }
    add(ans[A.sam[A.sam[x].par].len+1], 1LL*sz[x][0]*sz[x][1]%kcz*sz[x][2]%kcz);
    add(ans[A.sam[x].len+1], kcz-1LL*sz[x][0]*sz[x][1]%kcz*sz[x][2]%kcz);
}
```
* **代码解读**：
  - `head`数组用`-1`初始化（`memset(head, -1, sizeof(head))`），遍历邻接表时`i != -1`表示还有边。
  - 递归处理子节点`tox`，然后把`tox`的次数累加到`x`——这就是“自底向上”的合并！
* 💡 **学习笔记**：邻接表是处理树结构的常用方式，DFS能清晰遍历树的所有节点～

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地“看到”广义SAM的工作过程，我设计了一个**8位像素风格的动画**——《像素字符串工厂》！像玩FC游戏一样，看着算法一步步运行～
</visualization_intro>

### **动画设计方案**
#### 1. 整体风格与场景
- **8位像素风**：仿照《超级马里奥》的配色（红、蓝、黄为主），节点用“彩色方块”表示（根节点是黄色，其他节点是蓝色），字符串用“彩色小珠子”表示（第一个串红，第二个串绿，第三个串蓝）。
- **场景布局**：
  - 左侧：三个输入字符串的“原料传送带”（红、绿、蓝珠子依次滚动）；
  - 中间：广义SAM的“工厂车间”（节点像积木一样拼接，转移边用虚线连接）；
  - 右侧：差分“进度条”和答案“显示板”（进度条用绿色填充，答案用数字像素块显示）。

#### 2. 核心动画步骤
1. **初始化**：
   - 传送带开始滚动，三个字符串的珠子依次出现；
   - 车间里只有一个黄色根节点（节点1）；
   - 进度条和显示板为空。
2. **SAM扩展（Extend操作）**：
   - 每个字符珠子“落入”车间，触发节点扩展：
     - 新节点（蓝色方块）从根节点延伸出来，显示长度`len`（比如“len=3”）；
     - 转移边（虚线）连接父节点和新节点，闪烁一次表示“建立转移”；
     - 播放“叮”的音效（8位音色）。
   - 节点上显示`sz`值（比如“红:2，绿:1，蓝:3”），表示该节点在三个串中的出现次数。
3. **DFS合并次数**：
   - 后缀树的边（实线）亮起，从叶子节点（最深的蓝色方块）向上“流动”黄色光；
   - 父节点的`sz`值逐渐增加（比如子节点`sz=2`，父节点`sz`从`1`变成`3`）；
   - 播放“嗒”的音效，表示次数合并完成。
4. **差分与前缀和**：
   - 右侧进度条的`L`位置亮起绿色（表示`ans[L] += 贡献`），`R+1`位置亮起红色（表示`ans[R+1] -= 贡献`）；
   - 前缀和计算时，进度条从左到右填充绿色，显示板的数字依次更新（比如“l=1:3，l=2:1”）；
   - 全部计算完成后，播放“叮~”的胜利音效，显示板闪烁庆祝。

#### 3. 交互与控制
- **控制面板**：
  - 按钮：「开始」（启动动画）、「单步」（一步步看）、「重置」（重新开始）；
  - 滑块：「速度」（调节动画快慢，从“龟速”到“火箭”）；
  - 开关：「音效」（开启/关闭8位音乐）。
- **AI自动演示**：点击「AI模式」，动画会自动运行，像“贪吃蛇AI”一样展示完整流程，适合快速浏览。

#### 4. 设计理念
- **像素风格**：复古游戏感能降低学习压力，让算法更“亲切”；
- **动态展示**：节点扩展、次数合并、差分更新都用动画呈现，避免“死记硬背”；
- **音效反馈**：关键操作有音效，强化记忆（比如“叮”对应节点扩展，“嗒”对应次数合并）。

<visualization_conclusion>
通过这个动画，你能清晰看到“字符串→SAM节点→次数统计→差分→答案”的完整流程，就像看着工厂把“原料”（字符串）变成“产品”（答案）一样！
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
广义SAM是处理多字符串子串问题的“瑞士军刀”，学会它能解决很多类似题目！
</similar_problems_intro>

### **通用思路迁移**
广义SAM的核心是**统一管理多字符串的子串**，适用于：
1. 统计多个字符串的公共子串数量；
2. 找出多个字符串的最长公共子串；
3. 计算多个字符串中每个子串的出现次数。

### **洛谷练习推荐**
1. **洛谷 P3804** - 后缀自动机
   - 🗣️ **推荐理由**：SAM的基础模板题，帮你熟悉SAM的构建和基本操作（比如统计不同子串数量）。
2. **洛谷 P3181** - [HAOI2016] 找相同字符
   - 🗣️ **推荐理由**：两个字符串的相同子串数量统计，是本题的“简化版”，能巩固SAM的次数统计技巧。
3. **洛谷 P4070** - [SDOI2016] 生成魔咒
   - 🗣️ **推荐理由**：广义SAM的经典应用，处理动态添加字符的字符串，要求统计不同子串数量，能锻炼你的SAM扩展能力。
4. **洛谷 P5231** - [JSOI2012] 玄武密码
   - 🗣️ **推荐理由**：用SAM处理多个模式串的匹配问题，要求快速判断每个模式串是否是原串的子串，能加深你对SAM转移边的理解。

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中的“经验之谈”能帮你少走弯路，我摘录了2条关键心得：
</insights_intro>

> **经验1（来自Memory_of_winter）**：“SAM的节点贡献是区间的，所以一定要用差分！”
> **点评**：很多新手会直接遍历每个节点的长度范围，逐个累加贡献，这样时间复杂度是`O(n^2)`，会超时。差分能把时间复杂度降到`O(n)`，是本题的“关键优化”！

> **经验2（来自2018LZY）**：“统计次数时，一定要按节点长度从大到小排序！”
> **点评**：因为父节点的长度比子节点小，子节点的次数要先累加给父节点。如果顺序反了，父节点的次数会少算，导致答案错误。

---

<conclusion>
本次关于「Three Strings」的分析就到这里！广义SAM是字符串算法中的“高端武器”，但只要理解了“节点代表子串”“后缀链接是父节点”“差分处理区间贡献”这三个核心点，就能轻松掌握。记得多做练习，把算法变成你的“本能”～下次我们再一起挑战更难的字符串问题！💪
</conclusion>

---
处理用时：142.80秒