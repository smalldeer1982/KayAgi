---
title: "T-shirt"
layout: "post"
diff: 省选/NOI-
pid: CF183D
tag: ['贪心', '背包 DP', '期望']
---

# T-shirt

## 题目描述

你将在CodeForces的一个$n$人团队实习，n个工程师由1到$n$编号。你决定给每个工程师一个纪念品：一件来自你的国家的T恤（T恤在CodeForces很受欢迎）。不幸的是，你不知道$n$个工程师各自衣服的尺寸。一共有1到m共m种不同的尺寸，并且每个工程师只适合一个尺寸。

你不知道每个工程师的尺寸，所以你询问你的朋友Gerald。很遗憾，他也不知道每个工程师的尺寸，但他知道对于第$i$个工程师，适合第j种T恤的概率。

最后你带来了$n$件T恤（这$n$件T恤可以是任意组合，你也可以带多件同样尺寸的衣服），在你准备T恤的时候并不知道每个工程师的尺寸，所以你只能根据Gerald提供的概率决定你所带的T恤。

你的任务是最大化收到适合自己的衣服的工程师数量的期望值。

当你到达办公室后，你会询问每个工程师他适合的T恤的尺寸，如果你有那个尺寸的衣服，你就会给他一件，否则就不给他T恤。你会从$1$号问起，一直问到$n$号

---

## 输入格式

第一行为两个用空格分开的整数n和m（$1<=n<=3000$,$1<=m<=300$)，分别代表工程师数量和衣服尺寸数量

接下来有$n$行，每行$m$个空格分开的整数，第$i$行第$j$个数字代表第$i$个工程师适合第$j$种T恤的概率。每个整数在$1$到$1000$之间。实际上的概率应为每个整数除以1000。

保证对于每个工程师适合每种T恤的概率之和为$1$。

## 输出格式

输出一行，一个实数代表收到T恤的工程师数量的最大期望值。允许最大误差为$10^{-9}$。

感谢@LJZ_C 提供的翻译

## 样例 #1

### 输入

```
2 2
500 500
500 500

```

### 输出

```
1.500000000000

```

## 样例 #2

### 输入

```
3 3
1000 0 0
1000 0 0
0 1000 0

```

### 输出

```
3.000000000000

```

## 样例 #3

### 输入

```
1 4
100 200 300 400

```

### 输出

```
0.400000000000

```



---

---
title: "Thief in a Shop"
layout: "post"
diff: 省选/NOI-
pid: CF632E
tag: ['枚举', '排序', '背包 DP']
---

# Thief in a Shop

## 题目描述

A thief made his way to a shop.

As usual he has his lucky knapsack with him. The knapsack can contain $ k $ objects. There are $ n $ kinds of products in the shop and an infinite number of products of each kind. The cost of one product of kind $ i $ is $ a_{i} $ .

The thief is greedy, so he will take exactly $ k $ products (it's possible for some kinds to take several products of that kind).

Find all the possible total costs of products the thief can nick into his knapsack.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n,k<=1000 $ ) — the number of kinds of products and the number of products the thief will take.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=1000 $ ) — the costs of products for kinds from $ 1 $ to $ n $ .

## 输出格式

Print the only line with all the possible total costs of stolen products, separated by a space. The numbers should be printed in the ascending order.

## 样例 #1

### 输入

```
3 2
1 2 3

```

### 输出

```
2 3 4 5 6

```

## 样例 #2

### 输入

```
5 5
1 1 1 1 1

```

### 输出

```
5

```

## 样例 #3

### 输入

```
3 3
3 5 11

```

### 输出

```
9 11 13 15 17 19 21 25 27 33

```



---

---
title: "PolandBall and Gifts"
layout: "post"
diff: 省选/NOI-
pid: CF755F
tag: ['贪心', '背包 DP', '进制']
---

# PolandBall and Gifts

## 题目描述

It's Christmas time! PolandBall and his friends will be giving themselves gifts. There are $ n $ Balls overall. Each Ball has someone for whom he should bring a present according to some permutation $ p $ , $ p_{i}≠i $ for all $ i $ .

Unfortunately, Balls are quite clumsy. We know earlier that exactly $ k $ of them will forget to bring their gift. A Ball number $ i $ will get his present if the following two constraints will hold:

1. Ball number $ i $ will bring the present he should give.
2. Ball $ x $ such that $ p_{x}=i $ will bring his present.

What is minimum and maximum possible number of kids who will not get their present if exactly $ k $ Balls will forget theirs?

## 输入格式

The first line of input contains two integers $ n $ and $ k $ ( $ 2<=n<=10^{6} $ , $ 0<=k<=n $ ), representing the number of Balls and the number of Balls who will forget to bring their presents.

The second line contains the permutation $ p $ of integers from $ 1 $ to $ n $ , where $ p_{i} $ is the index of Ball who should get a gift from the $ i $ -th Ball. For all $ i $ , $ p_{i}≠i $ holds.

## 输出格式

You should output two values — minimum and maximum possible number of Balls who will not get their presents, in that order.

## 说明/提示

In the first sample, if the third and the first balls will forget to bring their presents, they will be th only balls not getting a present. Thus the minimum answer is $ 2 $ . However, if the first ans the second balls will forget to bring their presents, then only the fifth ball will get a present. So, the maximum answer is $ 4 $ .

## 样例 #1

### 输入

```
5 2
3 4 1 5 2

```

### 输出

```
2 4
```

## 样例 #2

### 输入

```
10 1
2 3 4 5 6 7 8 9 10 1

```

### 输出

```
2 2
```



---

---
title: "Winning Strategy"
layout: "post"
diff: 省选/NOI-
pid: CF97C
tag: ['倍增', '背包 DP', '图论建模']
---

# Winning Strategy

## 题目描述

One university has just found out about a sport programming contest called ACM ICPC v2.0. This contest doesn't differ much from the well-known ACM ICPC, for example, the participants are not allowed to take part in the finals more than two times. However, there is one notable difference: the teams in the contest should consist of exactly $ n $ participants.

Having taken part in several ACM ICPC v2.0 finals and having not won any medals, the students and the university governors realized that it's high time they changed something about the preparation process. Specifically, as the first innovation it was decided to change the teams' formation process. Having spent considerable amount of time on studying the statistics of other universities' performance, they managed to receive some interesting information: the dependence between the probability of winning a medal and the number of team members that participated in the finals in the past. More formally, we know $ n+1 $ real numbers $ p_{0}<=p_{1}<=...<=p_{n} $ , where $ p_{i} $ is the probability of getting a medal on the finals if the team has $ i $ participants of previous finals, and other $ n-i $ participants arrived to the finals for the first time.

Despite such useful data, the university governors are unable to determine such team forming tactics that would provide the maximum probability of winning a medal at ACM ICPC v2.0 finals on average (we are supposed to want to provide such result to the far future and we are also supposed to have an endless supply of students). And how about you, can you offer such optimal tactic? At the first stage the university governors want to know the value of maximum average probability.

More formally, suppose that the university sends a team to the $ k $ -th world finals. The team has $ a_{k} $ participants of previous finals ( $ 0<=a_{k}<=n $ ). Since each person can participate in the finals no more than twice, the following condition must be true: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/b04e8ade7d007ad0702101fe8e64b638ac1fbbe2.png). Your task is to choose sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) so that the limit $ Ψ $ exists and it's value is maximal:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/cb2ffabcf620f29ef29bcdc17d35b1562b965de1.png)As ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) is an infinite sequence, you should only print the maximum value of the $ Ψ $ limit.

## 输入格式

The first line contains an integer $ n $ ( $ 3<=n<=100 $ ), $ n $ is the number of team participants. The second line contains $ n+1 $ real numbers with no more than 6 digits after decimal point $ p_{i} $ ( $ 0<=i<=n,0<=p_{i}<=1 $ ) — the probability of that the team will win a medal if it contains $ i $ participants who has already been on the finals. Also the condition $ p_{i}<=p_{i+1} $ should be fulfilled for all $ 0<=i<=n-1 $ .

## 输出格式

Print the only real number — the expected average number of medals won per year if the optimal strategy is used. The result may have absolute or relative error $ 10^{-6} $ .

## 说明/提示

In the second test, no matter what participants the team contains, it is doomed to be successful.

## 样例 #1

### 输入

```
3
0.115590 0.384031 0.443128 0.562356

```

### 输出

```
0.4286122500

```

## 样例 #2

### 输入

```
3
1 1 1 1

```

### 输出

```
0.9999999999

```



---

