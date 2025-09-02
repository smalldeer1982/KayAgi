# [GCJ 2008 AMER SemiFinal] Mixing Bowls

## 题目描述

你正在按照一道食谱制作午餐。

该食谱是一种通过将多种配料混合在一起制成的混合物。每种配料可以是以下两种之一：

- 另一种你必须先在单独碗中制作的混合物；或者
- 你厨房里已有的基础配料，可以直接加入。

要制作一种混合物，你需要准备好它的所有配料，取一个空碗将这些配料混合在一起。不能通过向已经存在的混合物中继续添加配料来制作新的混合物。

例如，如果你想用 CAKEMIX（混合物）和 lies（基础配料）来制作 CAKE（混合物），那么你必须先在一个碗中制作好 CAKEMIX，然后再将 CAKEMIX 和 lies 加入第二个碗中混合，制成 CAKE。

一旦你将某个混合物作为配料使用，并且其所在的碗已经清空，你可以将这个碗用于制作其他混合物。因此，你需要准备的碗的数量取决于你选择制作混合物的顺序。

请你计算制作整个食谱所需的最少碗数。

## 说明/提示

**样例解释**

在第一个样例中，为了满足你对 SOUP 的渴望，你可以按以下步骤操作：

1. 用一个碗将 celery 和 onions 混合，制作 VEGETABLES。
2. 用第二个碗将 chicken 和第一个碗中的 VEGETABLES 混合，制作 STOCK。此时第一个碗已空。
3. 用第一个碗将 STOCK、salt 和 water 混合，制作 SOUP。

在第二个样例中，你可以选择先制作 FLAVOR 或 FRUIT，再与 milk 和 icecream 一起混合制作 MILKSHAKE。

如果你先制作 FRUIT，则需要四个碗：

1. 用一个碗将 banana 和 berries 混合，制作 FRUIT。
2. 用第二个碗将 nutmeg 和 cinnamon 混合制作 SPICES，用第三个碗将 cocoa 和 syrup 混合制作 CHOCOLATE。（顺序可交换）
3. 用第四个碗将 SPICES 和 CHOCOLATE 混合制作 FLAVOR。
4. 用第二或第三个碗将 FRUIT、FLAVOR、milk 和 icecream 混合制作 MILKSHAKE。

但如果你在 FLAVOR 之后再制作 FRUIT，则只需三个碗：

1. 用一个碗将 nutmeg 和 cinnamon 混合制作 SPICES，用第二个碗将 cocoa 和 syrup 混合制作 CHOCOLATE。（顺序可交换）
2. 用第三个碗将 SPICES 和 CHOCOLATE 混合制作 FLAVOR。
3. 用第一个碗将 banana 和 berries 混合制作 FRUIT。
4. 用第二个碗将 FRUIT、FLAVOR、milk 和 icecream 混合制作 MILKSHAKE。

**数据范围**

- $1 \leq C \leq 10$
- $2 \leq M \leq 10$

**小数据范围（5 分，测试点 1 - 可见）**

- $1 \leq N \leq 10$

**大数据范围（9 分，测试点 2 - 隐藏）**

- $1 \leq N \leq 1000$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3
SOUP 3 STOCK salt water
STOCK 2 chicken VEGETABLES
VEGETABLES 2 celery onions
5
MILKSHAKE 4 milk icecream FLAVOR FRUIT
FRUIT 2 banana berries
FLAVOR 2 SPICES CHOCOLATE
SPICES 2 nutmeg cinnamon
CHOCOLATE 2 cocoa syrup```

### 输出

```
Case #1: 2
Case #2: 3```

