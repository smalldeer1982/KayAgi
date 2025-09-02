# [GCJ 2011 #1A] The Killer Word

## 题目描述

你正在和你的朋友 Sean 玩“Hangman”（猜单词）游戏。虽然你听说 Sean 很擅长“从婴儿手里夺糖”，但他在这个游戏上并不那么厉害。你能否利用 Sean 不完美的策略，让他输得尽可能惨？

```
 +--+
 |  O
 | /|\       Mystery word: _ a _ a _ a _
 | / \
 |
+-+---+
```

游戏规则如下：

- 有一个所有有效单词组成的字典 $D$，你和 Sean 都知道。每个单词只包含小写字母 a-z，且没有空格。
- 你先从 $D$ 中任选一个单词，并把它写在黑板上，每个字母用下划线 _ 替代。
- Sean 每回合可以选择一个字母，问你这个字母是否在单词中。如果在，你需要揭示所有该字母出现的位置；否则，Sean 失去 1 分。
- 当单词的所有字母都被揭示后，本轮结束。
- 无论 Sean 输掉多少分，本轮都不会提前结束。

Sean 使用一种非常简单的策略。他会列出 26 个字母，按某种顺序组成列表 $L$，然后依次尝试每个字母。如果在 $D$ 中至少有一个单词（a）包含他当前考虑的字母，且（b）与黑板上已揭示的信息和他之前所有猜测的结果一致，那么 Sean 就会猜这个字母。否则，他会跳过这个字母。不管怎样，Sean 都会继续按顺序尝试下一个字母。

给定 Sean 的字母列表，你应该选择哪个单词，才能让 Sean 输掉尽可能多的分数？如果有多个选择让 Sean 输掉同样多的分数，你应选择字典中最靠前的那个单词。

**示例**

假设 Sean 按字母表顺序猜字母（即 $L = $ "abcdefghijklmnopqrstuvwxyz"），且 $D$ 包含 banana、caravan 和 pajamas。如果你选择 pajamas，游戏过程如下：

- 你先在黑板上写下 7 个下划线 _ _ _ _ _ _ _。根据下划线数量，Sean 立刻知道单词只能是 caravan 或 pajamas。
- Sean 首先猜 a，因为它在 $L$ 的首位，你需要揭示所有 a 的位置：_ a _ a _ a _。
- Sean 跳过 b，尽管 banana 里有 b，但他已经知道这不是你的单词。
- 接着他猜 c，因为 caravan 里有 c。但你选的单词没有 c，所以 Sean 失去 1 分，且没有新信息被揭示。
- 通过排除法，Sean 现在知道你的单词只能是 pajamas，于是他依次猜 j、m、p、s，且不再失分。

所以，如果你选择 pajamas，Sean 会失去 1 分。选其他单词他不会失分。

## 说明/提示

**数据范围**

- $1 \leq T \leq 10$。
- 每个单词长度为 $1$ 到 $10$ 个字符。
- 每组测试数据中不会有重复单词。

**小数据范围（10 分，测试点 1 - 可见）**

- $1 \leq N \leq 100$。
- $1 \leq M \leq 10$。
- 时间限制：3 秒。

**大数据范围（20 分，测试点 2 - 隐藏）**

- $1 \leq N \leq 10000$。
- $1 \leq M \leq 100$。
- 时间限制：6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3 2
banana
caravan
pajamas
abcdefghijklmnopqrstuvwxyz
etaoisnhrdlcumwfgypbvkjxqz
4 1
potato
tomato
garlic
pepper
zyxwvutsrqponmlkjihgfedcba```

### 输出

```
Case #1: pajamas caravan
Case #2: garlic```

