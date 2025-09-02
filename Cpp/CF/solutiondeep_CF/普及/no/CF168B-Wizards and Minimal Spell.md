# 题目信息

# Wizards and Minimal Spell

## 题目描述

Let's dive into one of the most interesting areas of magic — writing spells. Learning this exciting but challenging science is very troublesome, so now you will not learn the magic words, but only get to know the basic rules of writing spells.

Each spell consists of several lines. The line, whose first non-space character is character "\#" is an amplifying line and it is responsible for spell power. The remaining lines are common, and determine the effect of the spell.

You came across the text of some spell. Spell was too long, so you cannot understand its meaning. So you want to make it as short as possible without changing the meaning.

The only way to shorten a spell that you know is the removal of some spaces and line breaks. We know that when it comes to texts of spells, the spaces carry meaning only in the amplifying lines, so we should remove all spaces in other lines. Newlines also do not matter, unless any of the two separated lines is amplifying. Thus, if two consecutive lines are not amplifying, they need to be joined into one (i.e. we should concatenate the second line to the first one). Removing spaces in amplifying lines and concatenating the amplifying lines to anything is forbidden.

Note that empty lines must be processed just like all the others: they must be joined to the adjacent non-amplifying lines, or preserved in the output, if they are surrounded with amplifying lines on both sides (i.e. the line above it, if there is one, is amplifying, and the line below it, if there is one, is amplifying too).

For now those are the only instructions for removing unnecessary characters that you have to follow (oh yes, a newline is a character, too).

The input contains the text of the spell, which should be reduced. Remove the extra characters and print the result to the output.

## 说明/提示

In the first sample the amplifying lines are lines 1 and 7. So, lines 2 to 6 are concatenated to each other, all spaces are deleted from them.

In the second sample the amplifying lines are lines 1 and 3. So, no lines are concatenated to each other.

## 样例 #1

### 输入

```
   #   include &lt;cstdio&gt;

using namespace std;

int main     (   ){
puts(&quot;Hello # World&quot;); #
#
}
```

### 输出

```
   #   include &lt;cstdio&gt;
usingnamespacestd;intmain(){puts(&quot;Hello#World&quot;);#
#
}
```

## 样例 #2

### 输入

```
#

#
```

### 输出

```
#

#
```

# AI分析结果



# Wizards and Minimal Spell

## 题目描述

让我们深入魔法中最有趣的领域——编写咒语。学习这门令人兴奋但充满挑战的学科非常麻烦，所以现在你将不学习魔法词汇，而是了解编写咒语的基本规则。

每个咒语由若干行组成。第一个非空格字符为"#"的是增幅行，负责咒语的力量。其余为普通行，决定咒语效果。

你获得了一个咒语文本，但它太长难以理解。需要在不改变含义的前提下尽可能缩短它。

缩短规则如下：
1. 非增幅行删除所有空格
2. 连续的非增幅行需合并为一行
3. 空行仅当上下两行都是增幅行时才保留

输入咒语文本，处理后输出。

## 样例 #1

### 输入
```
   #   include &lt;cstdio&gt;

using namespace std;

int main     (   ){
puts(&quot;Hello # World&quot;); #
#
}
```

### 输出
```
   #   include &lt;cstdio&gt;
usingnamespacestd;intmain(){puts(&quot;Hello#World&quot;);#
#
}
```

## 样例 #2

### 输入
```
#

#
```

### 输出
```
#

#
```

---

**算法分类**: 模拟

---

## 题解分析与结论

### 题解对比与评分

1. **Wilderness_（5星）**  
   - **关键亮点**：使用状态标记 `fg` 追踪前一行类型，精准处理换行逻辑。通过分情况处理普通行和增幅行的衔接，正确处理空行保留条件。代码简洁高效。
   - **代码核心**：
     ```cpp
     int fg=0; // 状态标记：0初始，1普通行，2增幅行
     while(getline(cin,s)) {
         // 判断是否为增幅行
         if (是增幅行) {
             if(fg) putchar('\n'); // 前有内容则换行
             cout << s;
             fg = 2;
         } else {
             if(fg==2) putchar('\n'); // 前是增幅行则换行
             // 删空格输出
             fg = 1;
         }
     }
     putchar('\n'); // 最后换行
     ```

2. **玉树临风英俊潇洒（4星）**  
   - **亮点**：逻辑与Wilderness_相似，采用 `flag` 状态变量。通过统一的条件分支处理换行，可读性较好。
   - **优化空间**：变量命名可更明确，缺少对空行的显式处理注释。

3. **Yamchip（3星）**  
   - **思路**：使用 `t` 标记处理行类型，但在空行保留条件处理上不够明确，可能导致中间空行误删。

---

### 最优思路总结

**关键技巧**：  
- **状态跟踪**：维护前一行类型的状态变量，决定当前行起始是否需要换行
- **增量处理**：逐行读取时即时处理空格删除和行合并，避免存储全部数据
- **边界处理**：最后补换行符适配评测系统要求

**代码实现要点**：  
1. 遍历每行判断首个非空字符是否为`#`
2. 增幅行需确保与前一行用换行分隔
3. 普通行删除空格后，若前一行是普通行则直接拼接
4. 空行仅在上下均为增幅行时保留

---

### 拓展与同类题目

1. **调试经验**：  
   - 空行处理需注意：原题样例2中，空行的保留依赖于上下行类型，需用状态变量追踪上下文
   - 最终换行符是易错点，必须显式添加

2. **推荐题目**：  
   - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)（字符串处理）
   - [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)（行处理与格式控制）
   - [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)（字符映射与模拟）

---
处理用时：190.62秒