---
title: "Candy Boxes"
layout: "post"
diff: 普及+/提高
pid: CF488B
tag: []
---

# Candy Boxes

## 题目描述

There is an old tradition of keeping $ 4 $ boxes of candies in the house in Cyberland. The numbers of candies are special if their arithmetic mean, their median and their range are all equal. By definition, for a set $ {x_{1},x_{2},x_{3},x_{4}} $ ( $ x_{1}<=x_{2}<=x_{3}<=x_{4} $ ) arithmetic mean is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/4ced3a9ae4181924c136bcc46ede19844528fdef.png), median is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/2d7e14bfd580007a1d694763c07f2437bb7e66e6.png) and range is $ x_{4}-x_{1} $ . The arithmetic mean and median are not necessary integer. It is well-known that if those three numbers are same, boxes will create a "debugging field" and codes in the field will have no bugs.

For example, $ 1,1,3,3 $ is the example of $ 4 $ numbers meeting the condition because their mean, median and range are all equal to $ 2 $ .

Jeff has $ 4 $ special boxes of candies. However, something bad has happened! Some of the boxes could have been lost and now there are only $ n $ ( $ 0<=n<=4 $ ) boxes remaining. The $ i $ -th remaining box contains $ a_{i} $ candies.

Now Jeff wants to know: is there a possible way to find the number of candies of the $ 4-n $ missing boxes, meeting the condition above (the mean, median and range are equal)?

## 输入格式

There is an old tradition of keeping $ 4 $ boxes of candies in the house in Cyberland. The numbers of candies are special if their arithmetic mean, their median and their range are all equal. By definition, for a set $ {x_{1},x_{2},x_{3},x_{4}} $ ( $ x_{1}<=x_{2}<=x_{3}<=x_{4} $ ) arithmetic mean is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/4ced3a9ae4181924c136bcc46ede19844528fdef.png), median is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/2d7e14bfd580007a1d694763c07f2437bb7e66e6.png) and range is $ x_{4}-x_{1} $ . The arithmetic mean and median are not necessary integer. It is well-known that if those three numbers are same, boxes will create a "debugging field" and codes in the field will have no bugs.

For example, $ 1,1,3,3 $ is the example of $ 4 $ numbers meeting the condition because their mean, median and range are all equal to $ 2 $ .

Jeff has $ 4 $ special boxes of candies. However, something bad has happened! Some of the boxes could have been lost and now there are only $ n $ ( $ 0<=n<=4 $ ) boxes remaining. The $ i $ -th remaining box contains $ a_{i} $ candies.

Now Jeff wants to know: is there a possible way to find the number of candies of the $ 4-n $ missing boxes, meeting the condition above (the mean, median and range are equal)?

## 输出格式

There is an old tradition of keeping $ 4 $ boxes of candies in the house in Cyberland. The numbers of candies are special if their arithmetic mean, their median and their range are all equal. By definition, for a set $ {x_{1},x_{2},x_{3},x_{4}} $ ( $ x_{1}<=x_{2}<=x_{3}<=x_{4} $ ) arithmetic mean is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/4ced3a9ae4181924c136bcc46ede19844528fdef.png), median is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/2d7e14bfd580007a1d694763c07f2437bb7e66e6.png) and range is $ x_{4}-x_{1} $ . The arithmetic mean and median are not necessary integer. It is well-known that if those three numbers are same, boxes will create a "debugging field" and codes in the field will have no bugs.

For example, $ 1,1,3,3 $ is the example of $ 4 $ numbers meeting the condition because their mean, median and range are all equal to $ 2 $ .

Jeff has $ 4 $ special boxes of candies. However, something bad has happened! Some of the boxes could have been lost and now there are only $ n $ ( $ 0<=n<=4 $ ) boxes remaining. The $ i $ -th remaining box contains $ a_{i} $ candies.

Now Jeff wants to know: is there a possible way to find the number of candies of the $ 4-n $ missing boxes, meeting the condition above (the mean, median and range are equal)?

## 说明/提示

For the first sample, the numbers of candies in $ 4 $ boxes can be $ 1,1,3,3 $ . The arithmetic mean, the median and the range of them are all $ 2 $ .

For the second sample, it's impossible to find the missing number of candies.

In the third example no box has been lost and numbers satisfy the condition.

You may output $ b $ in any order.

## 样例 #1

### 输入

```
2
1
1

```

### 输出

```
YES
3
3

```

## 样例 #2

### 输入

```
3
1
1
1

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
4
1
2
2
3

```

### 输出

```
YES

```

