---
title: "Help General"
layout: "post"
diff: 普及+/提高
pid: CF142B
tag: ['构造']
---

# Help General

## 题目描述

Once upon a time in the Kingdom of Far Far Away lived Sir Lancelot, the chief Royal General. He was very proud of his men and he liked to invite the King to come and watch drill exercises which demonstrated the fighting techniques and tactics of the squad he was in charge of. But time went by and one day Sir Lancelot had a major argument with the Fairy Godmother (there were rumors that the argument occurred after the general spoke badly of the Godmother's flying techniques. That seemed to hurt the Fairy Godmother very deeply).

As the result of the argument, the Godmother put a rather strange curse upon the general. It sounded all complicated and quite harmless: "If the squared distance between some two soldiers equals to $ 5 $ , then those soldiers will conflict with each other!"

The drill exercises are held on a rectangular $ n×m $ field, split into $ nm $ square $ 1×1 $ segments for each soldier. Thus, the square of the distance between the soldiers that stand on squares $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equals exactly $ (x_{1}-x_{2})^{2}+(y_{1}-y_{2})^{2} $ . Now not all $ nm $ squad soldiers can participate in the drill exercises as it was before the Fairy Godmother's curse. Unless, of course, the general wants the soldiers to fight with each other or even worse... For example, if he puts a soldier in the square $ (2,2) $ , then he cannot put soldiers in the squares $ (1,4) $ , $ (3,4) $ , $ (4,1) $ and $ (4,3) $ — each of them will conflict with the soldier in the square $ (2,2) $ .

Your task is to help the general. You are given the size of the drill exercise field. You are asked to calculate the maximum number of soldiers that can be simultaneously positioned on this field, so that no two soldiers fall under the Fairy Godmother's curse.

## 输入格式

The single line contains space-separated integers $ n $ and $ m $ ( $ 1<=n,m<=1000 $ ) that represent the size of the drill exercise field.

## 输出格式

Print the desired maximum number of warriors.

## 说明/提示

In the first sample test Sir Lancelot can place his 4 soldiers on the $ 2×4 $ court as follows (the soldiers' locations are marked with gray circles on the scheme):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/0d23ce3839b0ce156cddd9663617e134809111ae.png)In the second sample test he can place 6 soldiers on the $ 3×4 $ site in the following manner:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF142B/57bf2bd762016d87a2641e15975b3acd653786ad.png)

## 样例 #1

### 输入

```
2 4

```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4

```

### 输出

```
6
```

