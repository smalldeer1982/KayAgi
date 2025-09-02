---
title: "Letter"
layout: "post"
diff: 入门
pid: CF43B
tag: ['模拟', '字符串', '概率论']
---

# Letter

## 题目描述

### 题面描述

Vasya 决定利用报纸上的一段文字写一封匿名信。他可以从报纸上剪下一段文字（或字母），把他们粘贴到匿名信上去。已经剪下的文字不可重复使用。当然，匿名信中的空格不需要剪——他只要在空格处作出标记即可。现在，他知道报纸上的文字 $s1$ 和他即将写下的匿名信的内容 $s2$，请你帮他看看，他能否完成匿名信的书写。

## 输入格式

两行，分别是 $s1$ 和 $s2$（无空行），长度不超过 $200$，英文字母区分大小写，信中空格不作处理。

## 输出格式

写的出来就输出`YES`，否则输出`NO`。

## 样例 #1

### 输入

```
Instead of dogging Your footsteps it disappears but you dont notice anything
where is your dog

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
Instead of dogging Your footsteps it disappears but you dont notice anything
Your dog is upstears

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
Instead of dogging your footsteps it disappears but you dont notice anything
Your dog is upstears

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
abcdefg hijk
k j i h g f e d c b a

```

### 输出

```
YES

```

