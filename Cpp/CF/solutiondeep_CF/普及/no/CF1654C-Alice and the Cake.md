# 题目信息

# Alice and the Cake

## 题目描述

Alice has a cake, and she is going to cut it. She will perform the following operation $ n-1 $ times: choose a piece of the cake (initially, the cake is all one piece) with weight $ w\ge 2 $ and cut it into two smaller pieces of weight $ \lfloor\frac{w}{2}\rfloor $ and $ \lceil\frac{w}{2}\rceil $ ( $ \lfloor x \rfloor $ and $ \lceil x \rceil $ denote [floor and ceiling functions](https://en.wikipedia.org/wiki/Floor_and_ceiling_functions), respectively).

After cutting the cake in $ n $ pieces, she will line up these $ n $ pieces on a table in an arbitrary order. Let $ a_i $ be the weight of the $ i $ -th piece in the line.

You are given the array $ a $ . Determine whether there exists an initial weight and sequence of operations which results in $ a $ .

## 说明/提示

In the first test case, it's possible to get the array $ a $ by performing $ 0 $ operations on a cake with weight $ 327 $ .

In the second test case, it's not possible to get the array $ a $ .

In the third test case, it's possible to get the array $ a $ by performing $ 1 $ operation on a cake with weight $ 1\,970\,429\,473 $ :

- Cut it in half, so that the weights are $ [985\,214\,736, 985\,214\,737] $ .

 Note that the starting weight can be greater than $ 10^9 $ .In the fourth test case, it's possible to get the array $ a $ by performing $ 2 $ operations on a cake with weight $ 6 $ :

- Cut it in half, so that the weights are $ [3,3] $ .
- Cut one of the two pieces with weight $ 3 $ , so that the new weights are $ [1, 2, 3] $ which is equivalent to $ [2, 3, 1] $ up to reordering.

## 样例 #1

### 输入

```
14
1
327
2
869 541
2
985214736 985214737
3
2 3 1
3
2 3 3
6
1 1 1 1 1 1
6
100 100 100 100 100 100
8
100 100 100 100 100 100 100 100
8
2 16 1 8 64 1 4 32
10
1 2 4 7 1 1 1 1 7 2
10
7 1 1 1 3 1 3 3 2 3
10
1 4 4 1 1 1 3 3 3 1
10
2 3 2 2 1 2 2 2 2 2
4
999999999 999999999 999999999 999999999```

### 输出

```
YES
NO
YES
YES
NO
YES
NO
YES
YES
YES
YES
NO
NO
YES```

# AI分析结果

### 题目内容重写
Alice 有一块蛋糕，她将进行 $n-1$ 次切割操作。每次操作会选择一块重量 $w \geq 2$ 的蛋糕，将其切成两块，重量分别为 $\lfloor \frac{w}{2} \rfloor$ 和 $\lceil \frac{w}{2} \rceil$。切割完成后，她会将这些蛋糕按任意顺序排列。给定一个数组 $a$，其中 $a_i$ 表示第 $i$ 块蛋糕的重量，判断是否存在一个初始重量的蛋糕，经过上述操作后可以得到数组 $a$。

### 算法分类
**搜索**（广度优先搜索 BFS）

### 题解分析与结论
该题的核心思路是通过逆向思维，从给定的蛋糕序列出发，尝试将其合并为一个初始蛋糕。由于每次切割操作都是将蛋糕分成两个部分，因此可以通过模拟切割的逆过程来判断是否能够合并成功。大多数题解采用了 BFS 或优先队列来模拟这一过程，并通过 `map` 或 `multiset` 来记录蛋糕的出现次数。

### 所选高星题解
#### 1. 作者：_Fatalis_ (赞：7)
**星级：5星**
**关键亮点：**
- 使用 BFS 和 `map` 来模拟切割的逆过程，思路清晰且高效。
- 通过限制 BFS 的深度（`q.size() > 2*n`）来避免不必要的计算，优化了时间和空间复杂度。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
bool bfs() {
    while (!q.empty()) {
        int lst = q.front(); q.pop();
        if (fk[lst]) fk[lst]--;
        else {
            if (lst == 1 || q.size() > 2 * n) return false;
            int hl = lst / 2, hr = lst / 2 + (lst % 2);
            q.push(hl), q.push(hr);
        }
    }
    return true;
}
```

#### 2. 作者：RocksonLee (赞：3)
**星级：4星**
**关键亮点：**
- 使用优先队列来维护蛋糕的切割过程，确保每次处理最大的蛋糕。
- 通过比较当前最大蛋糕与目标序列的最大值来判断是否继续切割，逻辑严谨。
- 代码结构清晰，易于扩展。

**核心代码：**
```cpp
while (!q.empty() && !p.empty() && flag) {
    if (q.top() == p.top()) q.pop(), p.pop();
    if (q.top() > p.top()) flag = false;
    if (q.top() < p.top()) {
        p.push(p.top() % 2 == 0 ? p.top() / 2 : p.top() / 2);
        p.push(p.top() % 2 == 0 ? p.top() / 2 : p.top() / 2 + 1);
        p.pop();
    }
}
```

#### 3. 作者：0xFF (赞：2)
**星级：4星**
**关键亮点：**
- 使用优先队列和排序来模拟切割过程，确保每次处理最大的蛋糕。
- 通过判断当前最大蛋糕与目标序列的最大值是否匹配来决定是否继续切割，逻辑清晰。
- 代码简洁，易于理解。

**核心代码：**
```cpp
while (n > 0) {
    int k = q.top();
    if (k == a[n]) n--;
    else if (k < a[n]) break;
    else {
        q.push(k / 2);
        q.push((k + 1) / 2);
    }
    q.pop();
}
```

### 最优关键思路
- **逆向思维**：从给定的蛋糕序列出发，模拟切割的逆过程，判断是否能够合并为一个初始蛋糕。
- **优先队列**：通过优先队列或 `map` 来维护蛋糕的切割过程，确保每次处理最大的蛋糕。
- **剪枝优化**：通过限制 BFS 的深度或提前终止条件来优化时间和空间复杂度。

### 可拓展之处
- **类似题目**：可以扩展到其他需要逆向思维的题目，如拼图问题、分解问题等。
- **数据结构**：可以尝试使用其他数据结构如 `multiset` 或 `unordered_map` 来进一步优化。

### 推荐题目
1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1064 [NOIP2006 提高组] 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

### 个人心得
- **调试经历**：在处理 BFS 时，需要注意剪枝条件，否则容易导致超时。
- **踩坑教训**：在模拟切割过程时，确保每次处理的是最大的蛋糕，否则可能导致逻辑错误。
- **顿悟感想**：逆向思维在解决某些问题时非常有效，尤其是在处理分解或合并问题时。

---
处理用时：34.66秒