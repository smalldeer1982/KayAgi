# 题目信息

# One Occurrence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and $ q $ queries to it. $ i $ -th query is denoted by two integers $ l_i $ and $ r_i $ . For each query, you have to find any integer that occurs exactly once in the subarray of $ a $ from index $ l_i $ to index $ r_i $ (a subarray is a contiguous subsegment of an array). For example, if $ a = [1, 1, 2, 3, 2, 4] $ , then for query $ (l_i = 2, r_i = 6) $ the subarray we are interested in is $ [1, 2, 3, 2, 4] $ , and possible answers are $ 1 $ , $ 3 $ and $ 4 $ ; for query $ (l_i = 1, r_i = 2) $ the subarray we are interested in is $ [1, 1] $ , and there is no such element that occurs exactly once.

Can you answer all of the queries?

## 样例 #1

### 输入

```
6
1 1 2 3 2 4
2
2 6
1 2
```

### 输出

```
4
0
```

# AI分析结果



---
处理用时：93.25秒