---
title: "Champions' League"
layout: "post"
diff: 普及/提高-
pid: CF234E
tag: ['模拟', '排序']
---

# Champions' League

## 题目描述

In the autumn of this year, two Russian teams came into the group stage of the most prestigious football club competition in the world — the UEFA Champions League. Now, these teams have already started to play in the group stage and are fighting for advancing to the playoffs. In this problem we are interested in the draw stage, the process of sorting teams into groups.

The process of the draw goes as follows (the rules that are described in this problem, are somehow simplified compared to the real life). Suppose $ n $ teams will take part in the group stage ( $ n $ is divisible by four). The teams should be divided into groups of four. Let's denote the number of groups as $ m $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65e4300bd0cdae46f7d260b1389d3b214f9ce521.png)). Each team has a rating — an integer characterizing the team's previous achievements. The teams are sorted by the rating's decreasing (no two teams have the same rating).

After that four "baskets" are formed, each of which will contain $ m $ teams: the first $ m $ teams with the highest rating go to the first basket, the following $ m $ teams go to the second one, and so on.

Then the following procedure repeats $ m-1 $ times. A team is randomly taken from each basket, first from the first basket, then from the second, then from the third, and at last, from the fourth. The taken teams form another group. After that, they are removed from their baskets.

The four teams remaining in the baskets after $ (m-1) $ such procedures are performed, form the last group.

In the real draw the random selection of teams from the basket is performed by people — as a rule, the well-known players of the past. As we have none, we will use a random number generator, which is constructed as follows. Its parameters are four positive integers $ x,a,b,c $ . Every time there is a call to the random number generator, it produces the following actions:

- calculates ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/2fe2894178b5b7478ae2269aae243e7c851b6173.png);
- replaces parameter $ x $ by value $ y $ (assigns ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/72e8070934423a6837039e7a1e2f312765ec26ab.png));
- returns $ x $ as another random number.

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) means taking the remainder after division: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/c19545677f47a50d181dd7b00e822282597427db.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/770f8dc8f9b95dc42d2401b09019f707ad7418fc.png).

A random number generator will be used in the draw as follows: each time we need to randomly choose a team from the basket, it will generate a random number $ k $ . The teams that yet remain in the basket are considered numbered with consecutive integers from $ 0 $ to $ s-1 $ , in the order of decreasing rating, where $ s $ is the current size of the basket. Then a team number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65912cf5ed5c94787700c166a6eeb79e0114a14b.png) is taken from the basket.

Given a list of teams and the parameters of the random number generator, determine the result of the draw.

## 输入格式

The first input line contains integer $ n $ ( $ 4<=n<=64 $ , $ n $ is divisible by four) — the number of teams that take part in the sorting. The second line contains four space-separated integers $ x,a,b,c $ ( $ 1<=x,a,b,c<=1000 $ ) — the parameters of the random number generator. Each of the following $ n $ lines describes one team. The description consists of the name of the team and its rating, separated by a single space. The name of a team consists of uppercase and lowercase English letters and has length from 1 to 20 characters. A team's rating is an integer from 0 to 1000. All teams' names are distinct. All team's ratings are also distinct.

## 输出格式

Print the way the teams must be sorted into groups. Print the groups in the order, in which they are formed in the sorting. Number the groups by consecutive uppercase English letters, starting from letter 'A'. Inside each group print the teams' names one per line, in the order of decreasing of the teams' rating. See samples for a better understanding of the output format.

## 说明/提示

In the given sample the random number generator will be executed four times:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/fe99c797dbb307d601e0f59e424f6250c45a7d38.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/baa288fe7b8d960b815b5367ff1126e08e6c706b.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/81b191782fc61308d51cf88ac0aba6c561fc0212.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/549ef2ab2cbb05e99d689f6ca803b6fab657873d.png).

## 样例 #1

### 输入

```
8
1 3 1 7
Barcelona 158
Milan 90
Spartak 46
Anderlecht 48
Celtic 32
Benfica 87
Zenit 79
Malaga 16

```

### 输出

```
Group A:
Barcelona
Benfica
Spartak
Celtic
Group B:
Milan
Zenit
Anderlecht
Malaga

```

