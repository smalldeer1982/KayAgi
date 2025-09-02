# 题目信息

# ABBB

## 题目描述

Zookeeper is playing a game. In this game, Zookeeper must use bombs to bomb a string that consists of letters 'A' and 'B'. He can use bombs to bomb a substring which is either "AB" or "BB". When he bombs such a substring, the substring gets deleted from the string and the remaining parts of the string get concatenated.

For example, Zookeeper can use two such operations: AABABBA $ \to $ AABBA $ \to $ AAA.

Zookeeper wonders what the shortest string he can make is. Can you help him find the length of the shortest string?

## 说明/提示

For the first test case, you can't make any moves, so the answer is $ 3 $ .

For the second test case, one optimal sequence of moves is BABA $ \to $ BA. So, the answer is $ 2 $ .

For the third test case, one optimal sequence of moves is AABBBABBBB $ \to $ AABBBABB $ \to $ AABBBB $ \to $ ABBB $ \to $ AB $ \to $ (empty string). So, the answer is $ 0 $ .

## 样例 #1

### 输入

```
3
AAA
BABA
AABBBABBBB```

### 输出

```
3
2
0```

# AI分析结果

### 题目内容重写

Zookeeper 正在玩一个游戏。在这个游戏中，Zookeeper 必须使用炸弹来轰炸一个由字母 'A' 和 'B' 组成的字符串。他可以使用炸弹来轰炸一个子串，该子串要么是 "AB"，要么是 "BB"。当他轰炸这样的子串时，该子串会从字符串中删除，剩下的部分会拼接在一起。

例如，Zookeeper 可以进行两次操作：AABABBA → AABBA → AAA。

Zookeeper 想知道他能得到的最短字符串的长度是多少。你能帮助他找到这个最短字符串的长度吗？

### 算法分类
贪心

### 题解分析与结论

本题的核心是通过贪心策略，尽可能多地删除 "AB" 和 "BB" 子串，以得到最短的字符串。大多数题解都采用了栈或队列的数据结构来实现这一目标。以下是各题解的要点对比：

1. **栈的使用**：大多数题解使用栈来维护字符，遇到 'B' 时检查栈顶是否为 'A' 或 'B'，如果是则弹出栈顶，表示删除一个子串。这种方法的优点是简单直观，且时间复杂度为 O(n)。

2. **贪心策略**：部分题解强调了优先删除 "AB" 子串，因为 'A' 只能通过 "AB" 被删除，而 'B' 可以通过 "AB" 或 "BB" 被删除。这种策略确保了 'A' 被尽可能多地删除，从而得到更短的字符串。

3. **链表实现**：少数题解使用了双向链表来维护字符的删除操作，虽然实现较为复杂，但在某些情况下可能更高效。

### 高星题解推荐

#### 题解作者：_Scaley (赞：2)
- **星级**：4星
- **关键亮点**：使用栈来维护字符，优先删除 "AB" 子串，再删除 "BB" 子串，思路清晰，代码可读性强。
- **核心代码**：
  ```cpp
  for (int i = 1; i < l; ++i) {
      if (s[i] == 'A') sta[++top] = s[i];
      else if (sta[top] == 'A') top--;
      else sta[++top] = s[i];
  }
  ```

#### 题解作者：KEBrantily (赞：1)
- **星级**：4星
- **关键亮点**：使用 STL 的栈，代码简洁，逻辑清晰，强调了优先删除 "AB" 子串的正确性。
- **核心代码**：
  ```cpp
  for(int j=1;j<tot;j++){
      if(st.size() && a[j]=='B' && (st.top()=='A' || st.top()=='B')){
          st.pop();
          continue;
      }
      st.push(a[j]);
  }
  ```

#### 题解作者：jun头吉吉 (赞：1)
- **星级**：4星
- **关键亮点**：使用栈处理字符，逻辑简洁，代码实现高效，强调了贪心策略的正确性。
- **核心代码**：
  ```cpp
  for(int i=1;i<=n;i++)
      if(s.size() && c[i]=='B') s.pop();
      else s.push(c[i]);
  ```

### 最优关键思路
使用栈来维护字符，优先删除 "AB" 子串，再删除 "BB" 子串。这种贪心策略确保了 'A' 被尽可能多地删除，从而得到最短的字符串。

### 拓展思路
类似的问题可以通过贪心策略和栈或队列的数据结构来解决，例如删除特定模式的子串以得到最短字符串。这类问题通常需要优先处理某些特定字符或子串，以确保最优解。

### 推荐题目
1. [P1045 删除子串](https://www.luogu.com.cn/problem/P1045)
2. [P1046 最短字符串](https://www.luogu.com.cn/problem/P1046)
3. [P1047 字符串压缩](https://www.luogu.com.cn/problem/P1047)

---
处理用时：26.62秒