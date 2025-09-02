# Coffee Varieties (easy version)

## 题目描述

This is the easy version of the problem. You can find the hard version in the Div. 1 contest. Both versions only differ in the number of times you can ask your friend to taste coffee.

This is an interactive problem.

You're considering moving to another city, where one of your friends already lives. There are $ n $ cafés in this city, where $ n $ is a power of two. The $ i $ -th café produces a single variety of coffee $ a_i $ .

As you're a coffee-lover, before deciding to move or not, you want to know the number $ d $ of distinct varieties of coffees produced in this city.

You don't know the values $ a_1, \ldots, a_n $ . Fortunately, your friend has a memory of size $ k $ , where $ k $ is a power of two.

Once per day, you can ask him to taste a cup of coffee produced by the café $ c $ , and he will tell you if he tasted a similar coffee during the last $ k $ days.

You can also ask him to take a medication that will reset his memory. He will forget all previous cups of coffee tasted. You can reset his memory at most $ 30\ 000 $ times.

More formally, the memory of your friend is a queue $ S $ . Doing a query on café $ c $ will:

- Tell you if $ a_c $ is in $ S $ ;
- Add $ a_c $ at the back of $ S $ ;
- If $ |S| > k $ , pop the front element of $ S $ .

Doing a reset request will pop all elements out of $ S $ .

Your friend can taste at most $ \dfrac{2n^2}{k} $ cups of coffee in total. Find the diversity $ d $ (number of distinct values in the array $ a $ ).

Note that asking your friend to reset his memory does not count towards the number of times you ask your friend to taste a cup of coffee.

In some test cases the behavior of the interactor is adaptive. It means that the array $ a $ may be not fixed before the start of the interaction and may depend on your queries. It is guaranteed that at any moment of the interaction, there is at least one array $ a $ consistent with all the answers given so far.

## 说明/提示

In the first example, the array is $ a = [1, 4, 1, 3] $ . The city produces $ 3 $ different varieties of coffee ( $ 1 $ , $ 3 $ and $ 4 $ ).

The successive varieties of coffee tasted by your friend are $ 1, 4, \textbf{1}, 3, 3, 1, 4 $ (bold answers correspond to Y answers). Note that between the two ? 4 asks, there is a reset memory request R, so the answer to the second ? 4 ask is N. Had there been no reset memory request, the answer to the second ? 4 ask is Y.

In the second example, the array is $ a = [1, 2, 3, 4, 5, 6, 6, 6] $ . The city produces $ 6 $ different varieties of coffee.

The successive varieties of coffee tasted by your friend are $ 2, 6, 4, 5, \textbf{2}, \textbf{5} $ .

## 样例 #1

### 输入

```
4 2
N
N
Y
N
N
N
N```

### 输出

```
? 1
? 2
? 3
? 4
R
? 4
? 1
? 2
! 3```

## 样例 #2

### 输入

```
8 8
N
N
N
N
Y
Y```

### 输出

```
? 2
? 6
? 4
? 5
? 2
? 5
! 6```

