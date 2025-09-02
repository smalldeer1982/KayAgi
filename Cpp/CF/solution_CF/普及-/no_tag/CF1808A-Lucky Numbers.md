# Lucky Numbers

## 题目描述

Olympus City recently launched the production of personal starships. Now everyone on Mars can buy one and fly to other planets inexpensively.

Each starship has a number —some positive integer $ x $ . Let's define the luckiness of a number $ x $ as the difference between the largest and smallest digits of that number. For example, $ 142857 $ has $ 8 $ as its largest digit and $ 1 $ as its smallest digit, so its luckiness is $ 8-1=7 $ . And the number $ 111 $ has all digits equal to $ 1 $ , so its luckiness is zero.

Hateehc is a famous Martian blogger who often flies to different corners of the solar system. To release interesting videos even faster, he decided to buy himself a starship. When he came to the store, he saw starships with numbers from $ l $ to $ r $ inclusively. While in the store, Hateehc wanted to find a starship with the luckiest number.

Since there are a lot of starships in the store, and Hateehc can't program, you have to help the blogger and write a program that answers his question.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1808A/e10cd9aa8c24a123d5e125320e42ed0d55b601c6.png)

## 说明/提示

Let's look at two test examples:

- the luckiness of the number $ 59 $ is $ 9 - 5 = 4 $ ;
- the luckiness of $ 60 $ equals $ 6 - 0 = 6 $ ;
- the luckiness of $ 61 $ equals $ 6 - 1 = 5 $ ;
- the luckiness of $ 62 $ equals $ 6 - 2 = 4 $ ;
- the luckiness of $ 63 $ is $ 6 - 3 = 3 $ .

 Thus, the luckiest number is $ 60 $ .In the fifth test example, the luckiest number is $ 90 $ .

## 样例 #1

### 输入

```
5
59 63
42 49
15 15
53 57
1 100```

### 输出

```
60
49
15
57
90```

