# 题目信息

# Settlement of Guinea Pigs

## 题目描述

Dasha loves guinea pigs very much. In this regard, she decided to settle as many guinea pigs at home as possible and developed a plan for the next $ n $ days. Every day, she will either buy a new guinea pig or call a doctor to examine all her pets.

Unfortunately, the store where she was going to buy guinea pigs does not understand them. Therefore, it cannot determine their gender. Dasha can't do it either. The only one who can help is a doctor.

To keep guinea pigs, aviaries are needed. Dasha plans to buy them in the same store. Unfortunately, only one species is sold there — a double aviary. No more than two guinea pigs can live in it.

Since Dasha does not want to cause moral injury to her pets — she will not settle two guinea pigs of different genders in one aviary.

Help Dasha calculate how many aviaries in the worst case you need to buy so that you can be sure that at no moment of time do two guinea pigs of different genders live in the same aviary.

As part of this task, we believe that guinea pigs have only two genders — male and female.

## 说明/提示

In the first set of input data, Dasha needs to put each guinea pig in a separate enclosure, since she does not know their gender.

In the second set of input data, Dasha will buy $ 0 $ guinea pigs, which means she will need $ 0 $ aviaries.

In the third set of input data, you even need $ 3 $ aviaries to put each guinea pig in a separate aviary before the doctor arrives at the $ 4 $ th day. When she finds out their gender, at least two guinea pigs will be of the same gender and they can be placed in one aviary, and the third in another aviary. Thus, she will have one free aviary in which she can settle a new guinea pig. So answer is $ 3 $ .

In the fourth set of input data, we show that $ 4 $ is the optimal answer.

To begin with, we note that the first four guinea pigs can be placed one at a time in an aviary. Then a doctor will come and determine their gender. Among these four guinea pigs there will be at least one pair of the same gender, because: either male guinea pigs are at least $ 2 $ , or they are not more than $ 1 $ , which means that the female is at least $ 3 $ . Now we can put this couple in one aviary, and the other two in separate ones. We will have one more empty aviary where we can put a new pig.

Now let's show that the answer is at least $ 4 $ . Let's say that among the first $ 4 $ guinea pigs, $ 3 $ are female and $ 1 $ is male. We need at least $ 3 $ aviaries to settle them. Then, when we buy a new guinea pig, we will need another aviary in which we will put it, since we do not know its gender.

## 样例 #1

### 输入

```
6
3
1 1 1
3
2 2 2
5
1 1 1 2 1
10
1 2 1 2 1 2 1 2 1 2
20
1 2 1 1 1 1 1 2 1 2 1 2 2 1 1 1 1 1 1 1
20
2 1 1 2 1 1 2 1 2 2 1 1 1 2 2 1 1 1 1 2```

### 输出

```
3
0
3
4
12
9```

# AI分析结果

### 题目内容
# 豚鼠的安置

## 题目描述
达莎非常喜欢豚鼠。因此，她决定尽可能多地在家里饲养豚鼠，并制定了未来 $n$ 天的计划。每天，她要么购买一只新豚鼠，要么请医生来检查她所有的宠物。

不幸的是，她打算购买豚鼠的商店并不了解豚鼠。因此，它无法确定豚鼠的性别。达莎也做不到。唯一能帮忙的人是医生。

为了饲养豚鼠，需要鸟舍。达莎计划在同一家商店购买它们。不幸的是，那里只出售一种——双人鸟舍。一个鸟舍里最多只能住两只豚鼠。

由于达莎不想给她的宠物造成精神伤害——她不会把两只不同性别的豚鼠安置在同一个鸟舍里。

帮助达莎计算在最坏的情况下需要购买多少个鸟舍，以确保在任何时候都不会有两只不同性别的豚鼠住在同一个鸟舍里。

在这个任务中，我们认为豚鼠只有两种性别——雄性和雌性。

## 说明/提示
在第一组输入数据中，达莎需要将每只豚鼠放在单独的鸟舍里，因为她不知道它们的性别。

在第二组输入数据中，达莎将购买 $0$ 只豚鼠，这意味着她将需要 $0$ 个鸟舍。

在第三组输入数据中，在第 $4$ 天医生到来之前，甚至需要 $3$ 个鸟舍来将每只豚鼠放在单独的鸟舍里。当她知道它们的性别后，至少有两只豚鼠将是同一性别，它们可以被安置在一个鸟舍里，而第三只放在另一个鸟舍里。因此，她将有一个空闲的鸟舍，她可以在里面安置一只新豚鼠。所以答案是 $3$。

在第四组输入数据中，我们表明 $4$ 是最优答案。

首先，我们注意到前四只豚鼠可以一只一只地放在鸟舍里。然后医生会来并确定它们的性别。在这四只豚鼠中，至少会有一对是同一性别，因为：要么雄性豚鼠至少有 $2$ 只，要么它们不超过 $1$ 只，这意味着雌性至少有 $3$ 只。现在我们可以把这一对放在一个鸟舍里，另外两只放在单独的鸟舍里。我们将有一个更多的空鸟舍，我们可以在里面放一只新的豚鼠。

现在让我们表明答案至少是 $4$。假设在前 $4$ 只豚鼠中，有 $3$ 只雌性和 $1$ 只雄性。我们至少需要 $3$ 个鸟舍来安置它们。然后，当我们购买一只新豚鼠时，我们将需要另一个鸟舍来放置它，因为我们不知道它的性别。

## 样例 #1
### 输入
```
6
3
1 1 1
3
2 2 2
5
1 1 1 2 1
10
1 2 1 2 1 2 1 2 1 2
20
1 2 1 1 1 1 1 2 1 2 1 2 2 1 1 1 1 1 1 1
20
2 1 1 2 1 1 2 1 2 2 1 1 1 2 2 1 1 1 1 2
```
### 输出
```
3
0
3
4
12
9
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是围绕如何在最坏情况下确定所需鸟舍数量。关键在于处理已知性别和未知性别豚鼠的放置方式。对于未知性别的豚鼠，普遍认为最坏情况是每只都单独占用一个鸟舍；对于已知性别的豚鼠，不同题解通过不同方式计算所需鸟舍，如根据数量的奇偶性讨论、利用抽屉原理等。难点在于准确模拟整个过程，考虑每次操作对豚鼠性别状态和鸟舍需求的影响。

### 通用建议与扩展思路
解决此类问题，关键在于清晰理解题意，准确把握“最坏情况”的含义。在实现上，要注意对不同操作（购买豚鼠和鉴定性别）的合理处理以及对相关变量（如已知/未知性别豚鼠数量、鸟舍数量等）的正确维护。可拓展的方向包括增加更多限制条件，如不同种类豚鼠的混合安置，或改变鸟舍容量等，以加深对这类贪心策略应用的理解。

### 相似知识点洛谷题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
2. [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
3. [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937) 

---
处理用时：32.06秒