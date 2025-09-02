---
title: "Hyperspace Jump (easy)"
layout: "post"
diff: 普及/提高-
pid: CF958D1
tag: []
---

# Hyperspace Jump (easy)

## 题目描述

The Rebel fleet is on the run. It consists of $ m $ ships currently gathered around a single planet. Just a few seconds ago, the vastly more powerful Empire fleet has appeared in the same solar system, and the Rebels will need to escape into hyperspace. In order to spread the fleet, the captain of each ship has independently come up with the coordinate to which that ship will jump. In the obsolete navigation system used by the Rebels, this coordinate is given as the value of an arithmetic expression of the form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958D1/d69a7d7c3c678bb5c53aa5b1c81de4c6ffbba379.png).

To plan the future of the resistance movement, Princess Heidi needs to know, for each ship, how many ships are going to end up at the same coordinate after the jump. You are her only hope!

## 输入格式

The first line of the input contains a single integer $ m $ ( $ 1<=m<=200000 $ ) – the number of ships. The next $ m $ lines describe one jump coordinate each, given as an arithmetic expression. An expression has the form (a+b)/c. Namely, it consists of: an opening parenthesis (, a positive integer $ a $ of up to two decimal digits, a plus sign +, a positive integer $ b $ of up to two decimal digits, a closing parenthesis ), a slash /, and a positive integer $ c $ of up to two decimal digits.

## 输出格式

Print a single line consisting of $ m $ space-separated integers. The $ i $ -th integer should be equal to the number of ships whose coordinate is equal to that of the $ i $ -th ship (including the $ i $ -th ship itself).

## 说明/提示

In the sample testcase, the second and the third ship will both end up at the coordinate $ 3 $ .

Note that this problem has only two versions – easy and hard.

## 样例 #1

### 输入

```
4
(99+98)/97
(26+4)/10
(12+33)/15
(5+1)/7

```

### 输出

```
1 2 2 1 
```

