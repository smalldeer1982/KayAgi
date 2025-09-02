# 题目信息

# Text Messaging

## 题目描述

Fangy the little walrus, as all the modern walruses, loves to communicate via text messaging. One day he faced the following problem: When he sends large texts, they are split into parts each containing $ n $ characters (which is the size of one text message). Thus, whole sentences and words get split!

Fangy did not like it, so he faced the task of breaking the text into minimal messages on his own so that no sentence were broken into pieces when it is sent and the number of text messages to be sent would be minimal. If two consecutive sentences are in different messages, the space between them can be ignored (Fangy does not write this space).

The little walrus's text looks in the following manner:

```
TEXT ::= SENTENCE | SENTENCE SPACE TEXT
SENTENCE ::= WORD SPACE SENTENCE | WORD END
END ::= {'.', '?', '!'}
WORD ::= LETTER | LETTER WORD
LETTER ::= {'a'..'z', 'A'..'Z'}
SPACE ::= ' '
```

SPACE stands for the symbol of a space.

So, how many messages did Fangy send?

## 说明/提示

Let's take a look at the third sample. The text will be split into three messages: "Hello!", "Do you like fish?" and "Why?".

## 样例 #1

### 输入

```
25
Hello. I am a little walrus.
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
How are you?
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
19
Hello! Do you like fish? Why?
```

### 输出

```
3
```

# AI分析结果



# 短信分割 (Text Messaging)

## 题目描述
小海象方伊喜欢用短信交流。当他发送长文本时，消息会被自动分割为最多包含 $n$ 个字符的部分。方伊希望手动将文本分割为最少数量的消息，使得每个消息包含完整的句子（以 `.`、`?`、`!` 结尾的连续字符），且相邻句子在不同消息时中间的空格可省略。

**文本结构定义**：
```
文本 ::= 句子 | 句子 空格 文本
句子 ::= 单词 空格 句子 | 单词 结尾
结尾 ::= {'.', '?', '!'}
单词 ::= 字母 | 字母 单词
字母 ::= {'a'..'z', 'A'..'Z'}
空格 ::= ' '
```

## 算法分类
贪心

---

## 题解分析与结论

### 关键思路总结
1. **句子分割**：遍历字符串，以 `.`、`?`、`!` 为分界符，分割出所有句子并记录长度。
2. **可行性判断**：若有任何句子长度超过 $n$，直接输出 `Impossible`。
3. **贪心合并**：从前往后逐个合并句子，若当前消息剩余容量能容纳下一句子（考虑前导空格），则合并；否则新建消息。

### 优化技巧
- **输入处理**：使用 `getline` 读取完整文本，注意处理首行换行符。
- **空格处理**：合并句子时，相邻句子间添加一个空格（除首句外）。
- **贪心实现**：维护当前消息已用长度，动态判断是否开启新消息。

---

## 精选题解

### 1. Jerrywang09 的题解（⭐⭐⭐⭐）
**亮点**：
- 正确处理输入中的空格和换行符。
- 使用 `vector` 存储句子长度，代码结构清晰。
- 贪心逻辑简洁，处理合并时的空格逻辑明确。

**核心代码**：
```cpp
vector<int> a; // 存储每个句子长度
for (int i = 0; i < s.size(); i++) {
    // 分割句子并计算长度
    if (s[i] == ' ' && i > 0 && isDigit(s[i-1])) continue;
    cnt++;
    if (isDigit(s[i])) {
        a.push_back(cnt);
        cnt = 0;
    }
}

int cnt = a[0], ans = 1;
for (int i = 1; i < a.size(); i++) {
    if (cnt + a[i] + 1 <= n) { // +1为前导空格
        cnt += a[i] + 1;
    } else {
        ans++;
        cnt = a[i];
    }
}
```

### 2. codeLJH114514 的题解（⭐⭐⭐⭐）
**亮点**：
- 边分割边处理无解情况，提前终止无效计算。
- 使用哨兵值简化边界判断。

**核心逻辑**：
```cpp
vector<int> s;
for (遍历字符串) {
    // 分割句子并存入s
    if (句子长度 > n) 输出无解;
}
s.push_back(n+1); // 哨兵元素
for (auto i : s) {
    if (当前容量 + i + 1 > n) { // 新建消息
        ans++;
        now = i;
    } else {
        now += i + 1;
    }
}
```

### 3. Po7ed 的题解（⭐⭐⭐）
**亮点**：
- 动态合并消息时直接处理空格。
- 利用 `vector` 的 `back()` 方法高效合并。

**代码片段**：
```cpp
vector<int> mes;
for (遍历字符串) {
    计算当前句子长度 len;
    if (len > n) 输出无解;
    if (mes非空 && 可合并) {
        mes.back() += len + 1; // 合并并加空格
    } else {
        mes.push_back(len);
    }
}
cout << mes.size();
```

---

## 拓展与总结
### 同类问题套路
- **贪心合并问题**：常见于区间调度、字符串分割等场景，核心是局部最优选择。
- **边界处理**：注意分割符处理、首尾空格、容量溢出等边界情况。

### 推荐习题
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心+优先队列
2. [P1208 混合牛奶](https://www.luogu.com.cn/problem/P1208) - 贪心策略选择
3. [CF1183C Computer Game](https://codeforces.com/problemset/problem/1183/C) - 容量限制下的最优选择

---
处理用时：51.65秒