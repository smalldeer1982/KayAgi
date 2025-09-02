# 题目信息

# [USACO23OPEN] Moo Language B

## 题目描述

### 题目背景

FJ 对与奶牛更好地互动感兴趣，所以他决定学习 moo 语言！


moo 语言与英语相似，但更为简单。单词只有四种类型：名词、及物动词、不及物动词和连词，每两个单词之间必须用空格隔开。标点符号仅包含逗号和句号，它会跟在单词后面，若该标点符号后面存在单词，则需要隔一个空格再放单词。

对于每个句子，都需要遵循以下格式中的一条：

1. 名词+不及物动词。
2. 名词+及物动词+名词（可以有多个）。及物动词后面必须有至少一个名词。除及物动词后面的第一个名词外，后面的每个名词前面都必须加一个逗号。

也可以在两个句子之间加一个连词，形成复合句，复合句不能与其他句子用连词连接。每一个句子（包括复合句）都必须以句号结尾。

FJ 的词库中有 $N$ 个单词、$C$ 个逗号和 $P$ 个句号。每个单词的使用次数不能超过这个单词在词库中出现的次数。现在，你要帮他输出几个符合以上要求的句子，使总单词数尽量多。

每个输入文件中共包含 $T$ 组样例。

## 说明/提示

$1 \leq T \leq 100$，$1 \leq P, C \leq N \leq 10^3$。

- 输入 2-6：$N \leq 10$。
- 输入 7-11：$N \leq 100$。
- 输入 12-16：$N \leq 1000$。
- 输入编号除以 5 余 2 的测试点：没有及物动词。
- 输入编号除以 5 余 3 的测试点：没有不及物动词。
- 输入编号除以 5 余 4 的测试点：没有连词。

translated by [liyuanchen2021](https://www.luogu.com.cn/user/557680)

## 样例 #1

### 输入

```
3
1 1 1
bessie noun
10 5 4
bessie noun
taught transitive-verb
flew intransitive-verb
elsie noun
farmer noun
john noun
and conjunction
and conjunction
nhoj noun
mooed intransitive-verb
24 5 4
but conjunction
bessie noun
taught transitive-verb
flew intransitive-verb
elsie noun
farmer noun
john noun
and conjunction
and conjunction
nhoj noun
mooed intransitive-verb
bob noun
impressed transitive-verb
cow noun
impressed transitive-verb
leaped intransitive-verb
elsie noun
bella noun
buttercup noun
pushed transitive-verb
mooed intransitive-verb
envy noun
john noun
nhoj noun
```

### 输出

```
0

9
nhoj mooed. farmer taught elsie, bessie and john flew.
23
nhoj mooed. nhoj impressed john, farmer, elsie, bessie and cow impressed bob. bella pushed elsie and buttercup flew. envy mooed but john leaped.```

# AI分析结果



### 综合分析与结论
该题核心是贪心策略下的语法结构构造，需在复杂语法规则中最大化单词使用。各题解均采用分阶段构造与动态调整的思路，但实现方式略有差异。最优解法聚焦于：优先构造高单词产出句型 → 动态替换低效句型 → 剩余资源补充 → 连词优化连接。

---

### 精选题解

#### 1. 作者：_LRH_（5星）
**关键亮点**：
- **分阶段贪心**：先构造不及物句型，再替换为高收益的及物句型。
- **动态调整**：通过替换操作将原结构升级，实现资源高效利用。
- **代码简洁**：使用向量分组管理单词类型，逻辑清晰。

**核心代码思路**：
```cpp
// 阶段1：构造不及物语句
for (; a[0].size() && a[3].size() && h < p; sum += 2) { ... }

// 阶段2：构造及物语句
for (l = h; a[0].size() >= 2 && a[2].size() && h < p; sum += 3) { ... }

// 阶段3：替换低效结构
for (; l && a[0].size() && a[2].size(); l--, sum++) { ... }

// 阶段4：补充逗号+名词
for (; l != h && a[0].size() && c; c--, sum++) { ... }
```

#### 2. 作者：foryou_（4星）
**关键亮点**：
- **同质优化**：与_LRH_思路一致，代码实现更紧凑。
- **输出细节处理**：精确处理逗号与连词的位置，避免格式错误。

**个人心得**：
> “恶♂趣♂味♂大♂模♂拟♂”——强调对复杂规则处理的耐心与细节把控。

---

### 最优思路总结
1. **贪心阶段构造**：优先用尽不及物动词（句型1），再填充及物动词（句型2），确保基础单词数。
2. **动态替换升级**：将已生成的句型1替换为更高单词产出的句型2，提升资源利用率。
3. **剩余资源榨取**：在及物动词后链式补充名词+逗号，最大化利用剩余名词。
4. **连词增益连接**：通过交替使用连词与句号连接句子，额外增加连词带来的单词数。

---

### 拓展与举一反三
- **同类问题**：资源分配型构造题（如[CF987B](https://codeforces.com/problemset/problem/987/B)）。
- **优化套路**：分阶段贪心 + 后效性调整，常见于背包变种或语法构造问题。

---

### 推荐习题
1. **P1155 [NOIP2008 提高组] 火柴棒等式**（构造与资源分配）
2. **P1055 [NOIP2008 普及组] ISBN 号码**（规则模拟与校验）
3. **P1321 [单词覆盖还原]**（语法模式匹配与贪心覆盖）

---
处理用时：114.38秒