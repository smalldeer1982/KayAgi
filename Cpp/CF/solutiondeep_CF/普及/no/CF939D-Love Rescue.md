# 题目信息

# Love Rescue

## 题目描述

Valya and Tolya are an ideal pair, but they quarrel sometimes. Recently, Valya took offense at her boyfriend because he came to her in t-shirt with lettering that differs from lettering on her pullover. Now she doesn't want to see him and Tolya is seating at his room and crying at her photos all day long.

This story could be very sad but fairy godmother (Tolya's grandmother) decided to help them and restore their relationship. She secretly took Tolya's t-shirt and Valya's pullover and wants to make the letterings on them same. In order to do this, for one unit of mana she can buy a spell that can change some letters on the clothes. Your task is calculate the minimum amount of mana that Tolya's grandmother should spend to rescue love of Tolya and Valya.

More formally, letterings on Tolya's t-shirt and Valya's pullover are two strings with same length $ n $ consisting only of lowercase English letters. Using one unit of mana, grandmother can buy a spell of form $ (c_{1},c_{2}) $ (where $ c_{1} $ and $ c_{2} $ are some lowercase English letters), which can arbitrary number of times transform a single letter $ c_{1} $ to $ c_{2} $ and vise-versa on both Tolya's t-shirt and Valya's pullover. You should find the minimum amount of mana that grandmother should spend to buy a set of spells that can make the letterings equal. In addition you should output the required set of spells.

## 说明/提示

In first example it's enough to buy two spells: ('a','d') and ('b','a'). Then first letters will coincide when we will replace letter 'a' with 'd'. Second letters will coincide when we will replace 'b' with 'a'. Third letters will coincide when we will at first replace 'b' with 'a' and then 'a' with 'd'.

## 样例 #1

### 输入

```
3
abb
dad
```

### 输出

```
2
a d
b a```

## 样例 #2

### 输入

```
8
drpepper
cocacola
```

### 输出

```
7
l e
e d
d c
c p
p o
o r
r a
```

# AI分析结果

### 题目内容重写

**题目描述**

Valya 和 Tolya 是一对理想的情侣，但有时也会吵架。最近，Valya 因为 Tolya 穿着印有不同字母的 T 恤而生气，现在她不想见他，Tolya 整天坐在房间里看着她的照片哭泣。

这个故事本可以非常悲伤，但仙女教母（Tolya 的祖母）决定帮助他们恢复关系。她偷偷拿走了 Tolya 的 T 恤和 Valya 的毛衣，并希望通过魔法使它们上的字母相同。为此，她可以花费一点魔力购买一个咒语，该咒语可以改变衣服上的某些字母。你的任务是计算 Tolya 的祖母需要花费的最少魔力来拯救 Tolya 和 Valya 的爱情。

更正式地说，Tolya 的 T 恤和 Valya 的毛衣上的字母是两个长度相同的字符串，由小写英文字母组成。使用一点魔力，祖母可以购买一个形式为 $(c_1, c_2)$ 的咒语（其中 $c_1$ 和 $c_2$ 是一些小写英文字母），该咒语可以任意次数地将字母 $c_1$ 转换为 $c_2$，反之亦然。你需要找到祖母应该花费的最少魔力来购买一组咒语，使得两个字符串的字母相同。此外，你还需要输出所需的咒语集合。

**说明/提示**

在第一个示例中，购买两个咒语就足够了：('a','d') 和 ('b','a')。然后，当我们用 'd' 替换 'a' 时，第一个字母将匹配。第二个字母将在我们用 'a' 替换 'b' 时匹配。第三个字母将在我们先用 'a' 替换 'b'，然后用 'd' 替换 'a' 时匹配。

**样例 #1**

**输入**

```
3
abb
dad
```

**输出**

```
2
a d
b a
```

**样例 #2**

**输入**

```
8
drpepper
cocacola
```

**输出**

```
7
l e
e d
d c
c p
p o
o r
r a
```

### 算法分类
并查集

### 题解分析与结论

#### 题解对比
1. **chufuzhe** 和 **ahawzlc** 的题解都使用了并查集来解决这个问题，思路相似，都是通过并查集来判断两个字符是否在同一个集合中，如果不在，则合并它们，并记录操作次数和操作步骤。
2. **Horadrim** 的题解采用了图的深度优先搜索（DFS）来解决问题，通过建边和遍历来处理字符的转换，思路较为新颖，但实现复杂度较高。
3. **pipiispig** 的题解同样使用了并查集，代码简洁，思路清晰，但与其他并查集题解相比，没有明显的优化或创新。

#### 最优思路
并查集是解决该问题的最佳选择，因为它能够高效地判断两个字符是否可以通过一系列转换变为相同字符，并且能够记录转换的路径。通过并查集，我们可以将字符的转换关系表示为集合的合并操作，最终得到最小转换次数和具体的转换步骤。

#### 关键代码
```cpp
int find(int x) {
    if(fa[x]==x) return x;
    fa[x]=find(fa[x]);
    return fa[x];
}

void merge(char x, char y) {
    fa[find(x)] = fa[y];
}
```

#### 拓展思路
类似的问题可以通过并查集来解决，特别是在需要判断元素之间是否可以通过某种操作相互转换的场景。例如，字符转换、图的连通性问题等。

### 推荐题目
1. [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)
2. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
3. [P1197 [JSOI2008]星球大战](https://www.luogu.com.cn/problem/P1197)

### 个人心得
在使用并查集时，路径压缩是非常重要的优化手段，可以显著提高查询效率。此外，在处理字符转换问题时，将字符映射到整数范围（如ASCII码）可以简化操作。

---
处理用时：29.32秒