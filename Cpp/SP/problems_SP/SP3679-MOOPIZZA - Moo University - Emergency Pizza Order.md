---
title: "MOOPIZZA - Moo University - Emergency Pizza Order"
layout: "post"
diff: 难度0
pid: SP3679
tag: []
---

# MOOPIZZA - Moo University - Emergency Pizza Order

## 题目描述

 Moo U's cafeteria has run out of hay and so must order pizzas for the C (1 <= C <= 1,000) calves attending Moo U. Conveniently, a large pizza from the local pizzeria, Pizza Farm, serves exactly one calf.

 Pizza Farm is willing to make a pizza for each calf, but, due to the size of the order, has three constraints on the order:

 \* Although Pizza Farm has long list of T (1 <= T <= 30) vegetarian toppings, each of the pizzas must have exactly K (1 <= K <= T) toppings  
  
 \* No topping on a pizza can be duplicated (a pizza cannot have onions and onions, for example).  
  
 \* No two pizzas in the order can have the same set of toppings.  
  
 For example, if pizza 1 has onions, green peppers, pineapples, and wheat grass, then it can be the only pizza with that exact set of toppings, although pizza 2 might have onions, green peppers, pineapples, and also olives.

 For ordering purposes, the toppings are numbered 1..T.

 The calves at Moo U are very picky when it comes to their pizza toppings. Some calves might not like all of the toppings available. A calf will eat a pizza only she likes every single one of the toppings on that pizza. Determine the maximum number of calves that can be fed.

## 输入格式

 \* Line 1: Three integers: C, T, and K. \* Lines 2..C+1: Each line of space-separated integers describes which toppings one of the calves likes. The first integer on a line is the number of topping the calf likes. The remaining integers on the line are the toppings that the calf likes.

## 输出格式

 \* Line 1: A single integer, the maximum number of calves that can be fed.

## 样例 #1

### 输入

```
3 2 1
2 2 1
1 1
1 2



Input details:

There are three calves.  Pizza Farm has two toppings and each pizza
must have exactly one topping.  The first calf likes both of the
toppings, the second calf likes only the first topping, and the
third calf likes only the second topping.
```

### 输出

```
2
```

