# Autocompletion

## 题目描述

Arcady 是一名文案撰稿人。他今天的任务是用自己最喜欢的文本编辑器输入一段已经设计好的故事。

在输入过程中，Arcady 需要逐个输入单词、标点符号和空格。每输入一个字母或符号（包括换行符），都需要按一次键盘。此外，当屏幕上显示了一个单词的部分前缀时，如果已打印的单词中存在唯一匹配此前缀的单词，编辑器会建议补全这个单词。举例来说，当 Arcady 已输入「codeforces」、「coding」和再次输入「codeforces」时，输入「cod」时没有自动补全建议，但输入「code」时，编辑器会建议补全为「codeforces」。

Arcady 只需点击一次就可以接受编辑器的建议，将当前输入的前缀自动补全为完整单词。请注意，自动补全后不会自动输入其他符号（如空格或换行符）。如果 Arcady 不能移动光标或删除已经输入的字符，问他至少需要多少次键盘点击才能完成整个文本的输入？

在这里，单词是指由拉丁字母组成的连续字符序列，并且这些序列被空格、标点符号或行首行尾隔开。Arcady 只使用小写字母。例如，在「it's well-known that tic-tac-toe is a paper-and-pencil game for two players, x and o.」这句话中，有 20 个单词。

## 说明/提示

在第一个样例中，最佳策略是在输入第一次出现的「snowboarding」时，输入「sn」后使用自动补全，并在输入第二次出现的「snowboarding」时，输入「snowb」后使用自动补全，这样可以节省7次点击。

在第二个样例中，是否使用自动补全对总点击次数没有影响。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
snow affects sports such as skiing, snowboarding, and snowmachine travel.
snowboarding is a recreational activity and olympic and paralympic sport.
```

### 输出

```
141
```

## 样例 #2

### 输入

```
'co-co-co, codeforces?!'
```

### 输出

```
25
```

## 样例 #3

### 输入

```
thun-thun-thunder, thunder, thunder
thunder, thun-, thunder
thun-thun-thunder, thunder
thunder, feel the thunder
lightning then the thunder
thunder, feel the thunder
lightning then the thunder
thunder, thunder
```

### 输出

```
183
```

