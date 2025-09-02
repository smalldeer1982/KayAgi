# Goats and Wolves

## 题目描述

Once Vasya needed to transport $ m $ goats and $ m $ wolves from riverbank to the other as quickly as possible. The boat can hold $ n $ animals and Vasya, in addition, he is permitted to put less than $ n $ animals in the boat. If in one place (on one of the banks or in the boat) the wolves happen to strictly outnumber the goats, then the wolves eat the goats and Vasya gets upset. When Vasya swims on the boat from one shore to the other, he must take at least one animal to accompany him, otherwise he will get bored and he will, yet again, feel upset. When the boat reaches the bank, first all the animals get off simultaneously, and then the animals chosen by Vasya simultaneously get on the boat. That means that at the moment when the animals that have just arrived have already got off and the animals that are going to leave haven't yet got on, somebody might eat someone. Vasya needs to transport all the animals from one river bank to the other so that nobody eats anyone and Vasya doesn't get upset. What is the minimal number of times he will have to cross the river?

## 说明/提示

The first sample match to well-known problem for children.

## 样例 #1

### 输入

```
3 2
```

### 输出

```
11
```

## 样例 #2

### 输入

```
33 3
```

### 输出

```
-1
```

# 题解

## 作者：Miko35 (赞：8)

upd：修正若干笔误。

翻译是错的，建议看英文题面。

人类小智慧题。

---

题意：河岸一边有 $m$ 只狼和 $m$ 只羊，你有一艘载重为 $n$ 的船初始在动物的一边。船上最多装 $n$ 只动物，你需要把所有动物运送到对岸。在船靠岸的时候，会 **依次** 进行下面的操作：

1. 所有动物下船，转移到停靠的那一侧的河岸。

2. 你可以在河岸上选择若干羊与若干狼，将其转移至船上。

3. 船开向另一侧，且此时船上必须有动物。

如果在一次操作之后，两岸或船上的狼的数量严格大于羊的数量，任务就会失败。你需要求出，在任务不失败的前提下，最少的航行次数。（船一来一回算两次航行）

---

$\textrm{Solution}$：

记 $[x,y](R/L)$ 为“载 $x$ 只羊和 $y$ 只狼去/回”。

---

先考虑 $n>3$ 且 $m$ 足够大的情况。

我们 **希望** 这个过程可以被分成三部分：

1. 开局利用初始右边无动物的性质，可以给右边塞一车狼。
2. 中盘找到一个普遍策略，一直重复使用。
3. 最后利用左边可以无羊的性质完成斩杀。

显然，$1$ 和 $3$ 部分利用特殊性质，效率都应当比 $2$ 高，否则可以用 $2$ 直接代替。我们先考虑这两部分有没有什么可行的策略。

第一部分的最优策略显然是 $[0,n-1](R),[0,1](L),[n-1,1](R),[1,1](L)$。这样通过 $4$ 次航行转移了 $n-2$ 只狼和羊。（为什么不能 $n-1$ 自己思考www）

第三部分，有三个明显的特殊情况：

- $n \geq 2m$ 时，$[m,m]
(R)$，一次。

- $2m > n \geq m+1$ 时，$[m,1](R)$，$[0,1](L)$，$[0,m](R)$，一共三次。

- $n=m$ 时，可以 $[2,2](R),[1,1](L)$ 转化成上面一种情况，一共 $5$ 次。

第二部分，也就是考虑运输过程中间是如何做的。

说的具体一点，“中间”就指的是左右两岸都存在狼和羊（也就不可能出现岸上 $0$ 羊若干狼的特殊情况），我们需要找到一个普遍的策略并证明最优。

既然不存在这种特殊情况，由于右边有动物，所以每次从右边带走动物后，若右边羊的个数严格大于狼的个数，则左边下船之后必然任务失败。所以 **每次从右边带走动物后，右边的狼羊数量一定相等。** 这说明中间的这个策略，周期一定是两次航行（一来一回）。

先说结论：这个策略一来一回的上界是可以将 $\left\lfloor\dfrac{n}{2}\right\rfloor-1$ 只狼与羊转移。

当 $n$ 是偶数的时候，让这个策略重复两次，就达到了在中间转移的理论上界 $n-2$，这个策略显然最优。

当 $n$ 是奇数的时候，这个策略重复两次转移了 $n-3$ 只羊和狼。如果要做到 $n-2$，由于上面的粗体字，一次转移的动物数量一定是 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 羊和 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 狼，这些动物必须在船上。由于回程的时候，船上必须要有动物，也就是把上述的 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 狼排除开外的最后一只。如果这只动物是羊，由于右边一定相等，则左边就会少一只羊导致左边开船后任务失败；如果是狼，则在右边下船后，右边狼就会比羊多一只导致任务失败。故不可能做到 $n-2$。

构造一个这种策略：$\left[\left\lfloor\dfrac{n}{2}\right\rfloor,\left\lfloor\dfrac{n}{2}\right\rfloor\right](R)$，$\left[1,1\right](L)$，一次可以将 $\left\lfloor\dfrac{n}{2}\right\rfloor-1$ 只狼与羊转移。

---

后面就没什么了，注意特判掉 $n=1,2,3$ 的情况，此时 $\left\lfloor\dfrac{n}{2}\right\rfloor-1\leq 0$。

代码没啥难度，是贺的，而且很短，就不贴了（）






---

