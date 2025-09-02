# Meaning Mean

## 题目描述

Pak Chanek has an array $ a $ of $ n $ positive integers. Since he is currently learning how to calculate the floored average of two numbers, he wants to practice it on his array $ a $ .

While the array $ a $ has at least two elements, Pak Chanek will perform the following three-step operation:

1. Pick two different indices $ i $ and $ j $ ( $ 1 \leq i, j \leq |a| $ ; $ i \neq j $ ), note that $ |a| $ denotes the current size of the array $ a $ .
2. Append $ \lfloor \frac{a_i+a_j}{2} \rfloor $ $ ^{\text{∗}} $ to the end of the array.
3. Remove elements $ a_i $ and $ a_j $ from the array and concatenate the remaining parts of the array.

For example, suppose that $ a=[5,4,3,2,1,1] $ . If we choose $ i=1 $ and $ j=5 $ , the resulting array will be $ a=[4,3,2,1,3] $ . If we choose $ i=4 $ and $ j=3 $ , the resulting array will be $ a=[5,4,1,1,2] $ .

After all operations, the array will consist of a single element $ x $ . Find the maximum possible value of $ x $ if Pak Chanek performs the operations optimally.

 $ ^{\text{∗}} $ $ \lfloor x \rfloor $ denotes the floor function of $ x $ , which is the greatest integer that is less than or equal to $ x $ . For example, $ \lfloor 6 \rfloor = 6 $ , $ \lfloor 2.5 \rfloor=2 $ , $ \lfloor -3.6 \rfloor=-4 $ and $ \lfloor \pi \rfloor=3 $

## 说明/提示

In the first test case, the array is initially $ a=[1,7,8,4,5] $ . Pak Chanek will perform the following operations:

1. Pick $ i=1 $ and $ j=2 $ , then $ a=[8,4,5,4] $ .
2. Pick $ i=3 $ and $ j=2 $ , then $ a=[8,4,4] $ .
3. Pick $ i=2 $ and $ j=3 $ , then $ a=[8,4] $ .
4. Pick $ i=1 $ and $ j=2 $ , then $ a=[6] $ .

After all the operations, the array consists of a single element $ x=6 $ . It can be proven that there is no series of operations that results in $ x $ greater than $ 6 $ in the end.

## 样例 #1

### 输入

```
3
5
1 7 8 4 5
3
2 6 5
5
5 5 5 5 5```

### 输出

```
6
4
5```

