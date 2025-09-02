# [ABC373B] 1D Keyboard

## 题目描述

有一个键盘，键盘上的 $26$ 键排列在一条数字线上。

键盘上的按钮为大写字母表 `ABCDEFGHIJKLMNOPQRSTUVWXYZ` 的排列，我们将这个排列记作 $S$。

你将用这个键盘**依次输入**字符 `ABCDEFGHIJKLMNOPQRSTUVWXYZ`，想要输入字符，需要移到与该字符对应的按键坐标处并按下该键，移动到相邻的键移动距离为 $1$。

起初，你位于字符串 $S$ 中字符 `A` 所处的位置，你想要知道，按下 `A` 键到按下 `Z` 键之间可能移动的最小总距离。

**请注意本题按键并不影响距离，初始时移动的距离为 $0$。**

## 样例 #1

### 输入

```
ABCDEFGHIJKLMNOPQRSTUVWXYZ```

### 输出

```
25```

## 样例 #2

### 输入

```
MGJYIZDKSBHPVENFLQURTCWOAX```

### 输出

```
223```

