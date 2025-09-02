---
title: "New Year and Three Musketeers"
layout: "post"
diff: 提高+/省选-
pid: CF611E
tag: []
---

# New Year and Three Musketeers

## 题目描述

Do you know the story about the three musketeers? Anyway, you must help them now.

Richelimakieu is a cardinal in the city of Bearis. He found three brave warriors and called them the three musketeers. Athos has strength $ a $ , Borthos strength $ b $ , and Caramis has strength $ c $ .

The year 2015 is almost over and there are still $ n $ criminals to be defeated. The $ i $ -th criminal has strength $ t_{i} $ . It's hard to defeat strong criminals — maybe musketeers will have to fight together to achieve it.

Richelimakieu will coordinate musketeers' actions. In each hour each musketeer can either do nothing or be assigned to one criminal. Two or three musketeers can be assigned to the same criminal and then their strengths are summed up. A criminal can be defeated in exactly one hour (also if two or three musketeers fight him). Richelimakieu can't allow the situation where a criminal has strength bigger than the sum of strengths of musketeers fighting him — a criminal would win then!

In other words, there are three ways to defeat a criminal.

- A musketeer of the strength $ x $ in one hour can defeat a criminal of the strength not greater than $ x $ . So, for example Athos in one hour can defeat criminal $ i $ only if $ t_{i}<=a $ .
- Two musketeers can fight together and in one hour defeat a criminal of the strength not greater than the sum of strengths of these two musketeers. So, for example Athos and Caramis in one hour can defeat criminal $ i $ only if $ t_{i}<=a+c $ . Note that the third remaining musketeer can either do nothing or fight some other criminal.
- Similarly, all three musketeers can fight together and in one hour defeat a criminal of the strength not greater than the sum of musketeers' strengths, i.e. $ t_{i}<=a+b+c $ .

Richelimakieu doesn't want musketeers to fight during the New Year's Eve. Thus, he must coordinate their actions in order to minimize the number of hours till all criminals will be defeated.

Find the minimum number of hours to defeat all criminals. If musketeers can't defeat them all then print "-1" (without the quotes) instead.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the number of criminals.

The second line contains three integers $ a $ , $ b $ and $ c $ ( $ 1<=a,b,c<=10^{8} $ ) — strengths of musketeers.

The third line contains $ n $ integers $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=10^{8} $ ) — strengths of criminals.

## 输出格式

Print one line with the answer.

If it's impossible to defeat all criminals, print "-1" (without the quotes). Otherwise, print the minimum number of hours the three musketeers will spend on defeating all criminals.

## 说明/提示

In the first sample Athos has strength $ 10 $ , Borthos $ 20 $ , and Caramis $ 30 $ . They can defeat all criminals in two hours:

- Borthos and Caramis should together fight a criminal with strength $ 50 $ . In the same hour Athos can fight one of four criminals with strength $ 1 $ .
- There are three criminals left, each with strength $ 1 $ . Each musketeer can fight one criminal in the second hour.

In the second sample all three musketeers must together fight a criminal with strength $ 51 $ . It takes one hour. In the second hour they can fight separately, each with one criminal. In the third hour one criminal is left and any of musketeers can fight him.

## 样例 #1

### 输入

```
5
10 20 30
1 1 1 1 50

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
10 20 30
1 1 1 1 51

```

### 输出

```
3

```

## 样例 #3

### 输入

```
7
30 20 10
34 19 50 33 88 15 20

```

### 输出

```
-1

```

## 样例 #4

### 输入

```
6
10 5 10
10 9 5 25 20 5

```

### 输出

```
3

```

