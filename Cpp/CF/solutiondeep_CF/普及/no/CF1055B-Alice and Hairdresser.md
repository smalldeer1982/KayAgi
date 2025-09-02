# 题目信息

# Alice and Hairdresser

## 题目描述

Alice's hair is growing by leaps and bounds. Maybe the cause of it is the excess of vitamins, or maybe it is some black magic...

To prevent this, Alice decided to go to the hairdresser. She wants for her hair length to be at most $ l $ centimeters after haircut, where $ l $ is her favorite number. Suppose, that the Alice's head is a straight line on which $ n $ hairlines grow. Let's number them from $ 1 $ to $ n $ . With one swing of the scissors the hairdresser can shorten all hairlines on any segment to the length $ l $ , given that all hairlines on that segment had length strictly greater than $ l $ . The hairdresser wants to complete his job as fast as possible, so he will make the least possible number of swings of scissors, since each swing of scissors takes one second.

Alice hasn't decided yet when she would go to the hairdresser, so she asked you to calculate how much time the haircut would take depending on the time she would go to the hairdresser. In particular, you need to process queries of two types:

- $ 0 $ — Alice asks how much time the haircut would take if she would go to the hairdresser now.
- $ 1 $ $ p $ $ d $ — $ p $ -th hairline grows by $ d $ centimeters.

Note, that in the request $ 0 $ Alice is interested in hypothetical scenario of taking a haircut now, so no hairlines change their length.

## 说明/提示

Consider the first example:

- Initially lengths of hairlines are equal to $ 1, 2, 3, 4 $ and only $ 4 $ -th hairline is longer $ l=3 $ , and hairdresser can cut it in $ 1 $ second.
- Then Alice's second hairline grows, the lengths of hairlines are now equal to $ 1, 5, 3, 4 $
- Now haircut takes two seonds: two swings are required: for the $ 4 $ -th hairline and for the $ 2 $ -nd.
- Then Alice's first hairline grows, the lengths of hairlines are now equal to $ 4, 5, 3, 4 $
- The haircut still takes two seconds: with one swing hairdresser can cut $ 4 $ -th hairline and with one more swing cut the segment from $ 1 $ -st to $ 2 $ -nd hairline.
- Then Alice's third hairline grows, the lengths of hairlines are now equal to $ 4, 5, 4, 4 $
- Now haircut takes only one second: with one swing it is possible to cut the segment from $ 1 $ -st hairline to the $ 4 $ -th.

## 样例 #1

### 输入

```
4 7 3
1 2 3 4
0
1 2 3
0
1 1 3
0
1 3 1
0
```

### 输出

```
1
2
2
1
```

# AI分析结果

### 题目内容重写

Alice的头发正在迅速生长。可能是由于维生素过量，或者是一些黑魔法……

为了防止这种情况，Alice决定去理发店。她希望剪发后头发的长度最多为$l$厘米，其中$l$是她最喜欢的数字。假设Alice的头部是一条直线，上面有$n$根头发，编号从$1$到$n$。理发师每挥动一次剪刀，可以将任意一段头发剪短到长度$l$，前提是这段头发中的所有头发长度都严格大于$l$。理发师希望尽快完成工作，因此他会尽可能少地挥动剪刀，因为每次挥动剪刀都需要一秒钟。

Alice还没有决定什么时候去理发店，所以她请你计算一下，根据她什么时候去理发店，剪发需要多长时间。具体来说，你需要处理两种类型的查询：

- $0$ — Alice询问如果她现在去理发店，剪发需要多长时间。
- $1$ $p$ $d$ — 第$p$根头发增长了$d$厘米。

注意，在查询$0$中，Alice关心的是假设现在去理发店的场景，因此头发的长度不会改变。

### 算法分类
模拟

### 题解分析与结论

各题解的核心思路都是通过模拟头发的生长和剪发过程，动态维护需要剪发的次数。关键点在于如何高效地判断新增的头发是否会导致剪发次数的变化，以及如何处理相邻头发的关系。

### 所选高星题解

#### 题解作者：XL4453 (4星)
**关键亮点**：
- 通过数组记录每根头发的长度，动态更新剪发次数。
- 在头发增长时，判断是否会导致剪发次数的变化，特别是当头发从不超过$l$变为超过$l$时，处理相邻头发的关系。

**核心代码**：
```cpp
if(a[x]<=l&&(a[x]+=y)>l){
    ans++;
    if(a[x-1]>l)ans--;
    if(a[x+1]>l)ans--;
}
```
**实现思想**：
当某根头发的长度从不超过$l$变为超过$l$时，检查其左右头发的长度。如果左右头发也超过$l$，则剪发次数减少，因为可以将它们合并为一次剪发。

#### 题解作者：cqbztz2 (4星)
**关键亮点**：
- 详细讨论了头发增长后对剪发次数的影响，特别是当头发从不超过$l$变为超过$l$时，如何处理相邻头发的关系。
- 通过分类讨论，简化了剪发次数的更新逻辑。

**核心代码**：
```cpp
if(a[u-1]>l&&a[u+1]>l){
    ans--;
}
else if(a[u-1]<=l&&a[u+1]<=l){
    ans++;
}
```
**实现思想**：
当某根头发的长度从不超过$l$变为超过$l$时，检查其左右头发的长度。如果左右头发都超过$l$，则剪发次数减少；如果都不超过$l$，则剪发次数增加。

#### 题解作者：ccxswl (4星)
**关键亮点**：
- 通过数组模拟头发的生长和剪发过程，动态维护剪发次数。
- 在头发增长时，判断是否会导致剪发次数的变化，特别是当头发从不超过$l$变为超过$l$时，处理相邻头发的关系。

**核心代码**：
```cpp
if(a[x - 1] > l && a[x + 1] > l) ans--;
if(a[x - 1] <= l && a[x + 1] <= l) ans++;
```
**实现思想**：
当某根头发的长度从不超过$l$变为超过$l$时，检查其左右头发的长度。如果左右头发都超过$l$，则剪发次数减少；如果都不超过$l$，则剪发次数增加。

### 最优关键思路或技巧
- **动态维护剪发次数**：通过数组记录每根头发的长度，动态更新剪发次数。
- **相邻头发关系处理**：当某根头发的长度从不超过$l$变为超过$l$时，检查其左右头发的长度，判断是否需要合并剪发次数。

### 可拓展之处
- **区间合并**：类似的问题可以扩展到区间合并的场景，如合并相邻的区间以减少操作次数。
- **动态更新**：可以应用于需要动态维护某些状态的问题，如动态维护区间的最值或和。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3368)
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

### 个人心得摘录
- **调试经历**：在处理相邻头发关系时，容易忽略边界条件，如第一根和最后一根头发的特殊情况。
- **踩坑教训**：在更新剪发次数时，需要确保头发长度从不超过$l$变为超过$l$时才进行更新，否则会导致重复计数。
- **顿悟感想**：通过分类讨论，可以简化剪发次数的更新逻辑，提高代码的可读性和效率。

---
处理用时：39.93秒