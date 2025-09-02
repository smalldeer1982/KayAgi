# 题目信息

# [USACO06FEB] Cellphones G

## 题目描述

The cows have started using cellphones to cowmunicate with each other, but have found that the button layout doesn't suit their hooves very well. They are designing a special cellphone with fewer but larger buttons.


One feature they liked on the standard cellphones was predictive text. Each button has a few letters associated with it, and one types a word by pushing the associated buttons. Because there is more than one letter for each button, this can be ambiguous for some words.  However, most of the time the ambiguity can be resolved by using a dictionary to determine what word the user wanted.


Since the cows are designing a custom cellphone, they are also going to replace the English alphabet with the Cow alphabet. By an amazing coincidence, the cow alphabet is simply the first L (1 <= L <= 26) letters of the English alphabet, in the same order. They want to find out how to assign the letters of the Cow alphabet to the B buttons (1 <= B <= L) in such a way that the maximum number of words in their dictionary are unambiguous when entered with predictive text. Like normal cellphones, they want the letters on each button to be a contiguous section (one or more consecutive letters) of the alphabet.

奶牛的名字都是由英文字母表的前1(1 < K 26)个字母构成的.现在想设计一种手机， 有个按键.请你把这L个字母按顺序分配给B个按键，使能够通过按这些键而唯一确 定的奶牛数尽量多.


## 说明/提示

Explanation of the sample:




Button 1 contains AB, button two contains C-K, and button 3 contains LM. The words CELL, DILL, FILL and FILM are all entered as 2233, while the remaining 7 words are all entered uniquely.


## 样例 #1

### 输入

```
3 13
11
ALL
BALL
BELL
CALK
CALL
CELL
DILL
FILL
FILM
ILL
MILK```

### 输出

```
7
AB
CDEFGHIJK
LM```

# AI分析结果



### 综合分析与结论
本题需要将字母按序分配到B个按键，使得字典中的唯一可识别单词最多。核心难点在于高效枚举所有合法分配方式，并快速计算每种分配的唯一单词数。最优解法需结合DFS剪枝与哈希技巧。

---

### 精选题解分析

#### 题解作者：HPXXZYY（★★★★☆）
**关键亮点**：
1. **DFS剪枝枚举**：通过深度优先搜索生成连续字母区间的分配方案，利用`color+L-sub >= B`剪枝保证剩余字母足够分配。
2. **进制哈希判重**：将单词转化为B+1进制数，通过排序快速统计唯一哈希值。
3. **字典序处理**：在DFS顺序枚举中，优先保留字典序更优的方案。

**代码核心思想**：
```cpp
void dfs(int sub, int color) {
    if (sub > L) {
        if (color >= B) updata_answer();
        return;
    }
    // 尝试新开按键
    if (sub > 1 && color < B) {
        ch[sub] = color + 1;
        dfs(sub + 1, color + 1);
    }
    // 延续当前按键
    if (color + L - sub >= B) {
        ch[sub] = color;
        dfs(sub + 1, color);
    }
}
```

---

### 最优思路总结
1. **连续块划分**：按键必须包含连续字母，DFS时通过维护当前块编号自然生成合法分配。
2. **剪枝优化**：通过剩余字母数判断是否满足后续按键需求，避免无效递归。
3. **哈希快速统计**：B+1进制哈希保证不同按键组合的哈希值唯一，排序后线性遍历统计唯一项。

---

### 相似题目推荐
1. **P1092 [NOIP2004 提高组] 虫食算**（搜索剪枝与进制处理）
2. **P2322 [HNOI2006] 最短母串问题**（状态压缩与BFS优化）
3. **P5017 [NOIP2018 普及组] 摆渡车**（动态规划与时间离散化）

---
处理用时：59.44秒