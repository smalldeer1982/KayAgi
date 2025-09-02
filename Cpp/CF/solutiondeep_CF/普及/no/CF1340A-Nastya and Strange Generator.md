# 题目信息

# Nastya and Strange Generator

## 题目描述

Denis was very sad after Nastya rejected him. So he decided to walk through the gateways to have some fun. And luck smiled at him! When he entered the first courtyard, he met a strange man who was selling something.

Denis bought a mysterious item and it was... Random permutation generator! Denis could not believed his luck.

When he arrived home, he began to study how his generator works and learned the algorithm. The process of generating a permutation consists of $ n $ steps. At the $ i $ -th step, a place is chosen for the number $ i $ $ (1 \leq i \leq n) $ . The position for the number $ i $ is defined as follows:

- For all $ j $ from $ 1 $ to $ n $ , we calculate $ r_j $ — the minimum index such that $ j \leq r_j \leq         n $ , and the position $ r_j $ is not yet occupied in the permutation. If there are no such positions, then we assume that the value of $ r_j $ is not defined.
- For all $ t $ from $ 1 $ to $ n $ , we calculate $ count_t $ — the number of positions $ 1 \leq j \leq n $ such that $ r_j $ is defined and $ r_j = t $ .
- Consider the positions that are still not occupied by permutation and among those we consider the positions for which the value in the $ count $ array is maximum.
- The generator selects one of these positions for the number $ i $ . The generator can choose any position.

Let's have a look at the operation of the algorithm in the following example:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1340A/b046e416b9d8c9ca15a404e7bc85fa278badc8c3.png)Let $ n = 5 $ and the algorithm has already arranged the numbers $ 1, 2, 3 $ in the permutation. Consider how the generator will choose a position for the number $ 4 $ :

- The values of $ r $ will be $ r = [3, 3, 3, 4,         \times] $ , where $ \times $ means an indefinite value.
- Then the $ count $ values will be $ count = [0, 0, 3, 1,         0] $ .
- There are only two unoccupied positions in the permutation: $ 3 $ and $ 4 $ . The value in the $ count $ array for position $ 3 $ is $ 3 $ , for position $ 4 $ it is $ 1 $ .
- The maximum value is reached only for position $ 3 $ , so the algorithm will uniquely select this position for number $ 4 $ .

Satisfied with his purchase, Denis went home. For several days without a break, he generated permutations. He believes that he can come up with random permutations no worse than a generator. After that, he wrote out the first permutation that came to mind $ p_1, p_2, \ldots, p_n $ and decided to find out if it could be obtained as a result of the generator.

Unfortunately, this task was too difficult for him, and he asked you for help. It is necessary to define whether the written permutation could be obtained using the described algorithm if the generator always selects the position Denis needs.

## 说明/提示

Let's simulate the operation of the generator in the first test.

At the $ 1 $ step, $ r = [1, 2, 3, 4, 5], count = [1, 1, 1, 1,       1] $ . The maximum value is reached in any free position, so the generator can choose a random position from $ 1 $ to $ 5 $ . In our example, it chose $ 5 $ .

At the $ 2 $ step, $ r = [1, 2, 3, 4, \times], count = [1, 1,       1, 1, 0] $ . The maximum value is reached in positions from $ 1 $ to $ 4 $ , so the generator can choose a random position among them. In our example, it chose $ 1 $ .

At the $ 3 $ step, $ r = [2, 2, 3, 4, \times], count = [0, 2,       1, 1, 0] $ . The maximum value is $ 2 $ and is reached only at the $ 2 $ position, so the generator will choose this position.

At the $ 4 $ step, $ r = [3, 3, 3, 4, \times], count = [0, 0,       3, 1, 0] $ . The maximum value is $ 3 $ and is reached only at the $ 3 $ position, so the generator will choose this position.

At the $ 5 $ step, $ r = [4, 4, 4, 4, \times], count = [0, 0,       0, 4, 0] $ . The maximum value is $ 4 $ and is reached only at the $ 4 $ position, so the generator will choose this position.

In total, we got a permutation of $ 2, 3, 4, 5, 1 $ , that is, a generator could generate it.

## 样例 #1

### 输入

```
5
5
2 3 4 5 1
1
1
3
1 3 2
4
4 2 3 1
5
1 5 2 4 3```

### 输出

```
Yes
Yes
No
Yes
No```

# AI分析结果

### 题目内容重写

#### 题目描述

Denis 在 Nastya 拒绝他后非常伤心。于是他决定通过传送门来寻找一些乐趣。幸运的是，当他进入第一个庭院时，他遇到了一个奇怪的人，正在卖一些东西。

Denis 买了一个神秘的物品，结果发现是一个随机排列生成器！Denis 不敢相信自己的运气。

回到家后，他开始研究这个生成器的工作原理，并了解了它的算法。生成排列的过程由 $n$ 步组成。在第 $i$ 步，选择一个位置来放置数字 $i$ $(1 \leq i \leq n)$。选择位置的规则如下：

- 对于所有 $j$ 从 $1$ 到 $n$，计算 $r_j$ —— 最小的索引，使得 $j \leq r_j \leq n$，并且位置 $r_j$ 在排列中尚未被占用。如果没有这样的位置，则 $r_j$ 的值未定义。
- 对于所有 $t$ 从 $1$ 到 $n$，计算 $count_t$ —— 满足 $r_j$ 已定义且 $r_j = t$ 的位置 $1 \leq j \leq n$ 的数量。
- 考虑所有尚未被占用的位置，并选择其中 $count$ 值最大的位置。
- 生成器选择其中一个位置来放置数字 $i$。生成器可以任意选择一个位置。

让我们通过一个例子来看算法的运行过程：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1340A/b046e416b9d8c9ca15a404e7bc85fa278badc8c3.png)设 $n = 5$，算法已经将数字 $1, 2, 3$ 放置在排列中。考虑生成器如何选择数字 $4$ 的位置：

- $r$ 的值为 $r = [3, 3, 3, 4, \times]$，其中 $\times$ 表示未定义的值。
- 然后 $count$ 的值为 $count = [0, 0, 3, 1, 0]$。
- 排列中只有两个未占用的位置：$3$ 和 $4$。$count$ 数组中位置 $3$ 的值为 $3$，位置 $4$ 的值为 $1$。
- 最大值仅在位置 $3$ 达到，因此算法将唯一选择这个位置来放置数字 $4$。

Denis 对他的购买感到满意，回家后连续几天不停地生成排列。他认为自己可以像生成器一样生成随机排列。之后，他写下了第一个想到的排列 $p_1, p_2, \ldots, p_n$，并决定判断它是否可以通过生成器生成。

不幸的是，这个任务对他来说太难了，于是他向你求助。你需要判断这个排列是否可以通过上述算法生成，假设生成器总是选择 Denis 需要的位置。

#### 说明/提示

让我们模拟生成器在第一个测试中的运行过程。

在第 $1$ 步，$r = [1, 2, 3, 4, 5], count = [1, 1, 1, 1, 1]$。最大值在任何空闲位置达到，因此生成器可以随机选择 $1$ 到 $5$ 中的任意位置。在我们的例子中，它选择了 $5$。

在第 $2$ 步，$r = [1, 2, 3, 4, \times], count = [1, 1, 1, 1, 0]$。最大值在 $1$ 到 $4$ 的位置达到，因此生成器可以随机选择这些位置中的一个。在我们的例子中，它选择了 $1$。

在第 $3$ 步，$r = [2, 2, 3, 4, \times], count = [0, 2, 1, 1, 0]$。最大值为 $2$，仅在位置 $2$ 达到，因此生成器将选择这个位置。

在第 $4$ 步，$r = [3, 3, 3, 4, \times], count = [0, 0, 3, 1, 0]$。最大值为 $3$，仅在位置 $3$ 达到，因此生成器将选择这个位置。

在第 $5$ 步，$r = [4, 4, 4, 4, \times], count = [0, 0, 0, 4, 0]$。最大值为 $4$，仅在位置 $4$ 达到，因此生成器将选择这个位置。

最终，我们得到了排列 $2, 3, 4, 5, 1$，即生成器可以生成它。

#### 样例 #1

##### 输入

```
5
5
2 3 4 5 1
1
1
3
1 3 2
4
4 2 3 1
5
1 5 2 4 3
```

##### 输出

```
Yes
Yes
No
Yes
No
```

### 算法分类
**构造**

### 题解分析与结论

题目要求判断给定的排列是否可以通过特定的生成器生成。生成器的规则较为复杂，但通过分析可以发现，生成的排列必须满足一定的条件。具体来说，排列必须可以被分割成若干个公差为1的递增等差数列。这一结论可以通过模拟生成器的运行过程得出。

### 所选高星题解

#### 题解1：随情英 (4星)
**关键亮点**：
- 使用线段树优化了查找最大值和未标记位置的过程，将复杂度从 $O(n^2)$ 降低到 $O(n \log n)$。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
void solve() {
    int n = read();
    for (int i = 1; i <= n; ++i) {
        p[read()] = i;
        cnt[i] = 1;
    }
    build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        int w = ask(1, 1, n);
        if (w != cnt[p[i]]) {
            puts("NO");
            return;
        } else {
            if (p[i] + 1 <= n) {
                int k = ask2(1, p[i] + 1, n);
                if (k != 1 << 30) {
                    cnt[k] += cnt[p[i]];
                    change(1, k, cnt[p[i]]);
                }
            }
            change(1, p[i], -cnt[p[i]]);
            cnt[p[i]] = 0;
        }
    }
    puts("YES");
}
```

#### 题解2：KellyFrog (4星)
**关键亮点**：
- 通过数学归纳法证明了排列必须由若干个公差为1的递增等差数列组成。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
void Solve() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i < n; i++) {
        if(a[i + 1] - a[i] > 1) {
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;
}
```

#### 题解3：流绪 (4星)
**关键亮点**：
- 通过模拟生成器的运行过程，得出了排列必须由若干个公差为1的递增等差数列组成的结论。
- 代码逻辑清晰，易于理解。

**核心代码**：
```cpp
void Solve() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if(n <= 2) {
        cout << "Yes\n";
        return;
    }
    for(int i = 1; i <= n; i++) {
        v[i] = 0;
    }
    v[1] = 1;
    a[0] = inf;
    for(int i = 1; i <= n; i++) {
        if(a[i] > a[i - 1]) {
            flag = 0;
        }
        while(a[i + 1] == a[i] + 1 && i + 1 <= n) {
            v[i] = 1;
            i++;
        }
        v[i] = 1;
    }
    for(int i = 1; i <= n; i++) {
        if(!v[i]) {
            flag = 0;
        }
    }
    if(flag) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
```

### 最优关键思路或技巧
- **线段树优化**：通过线段树维护最大值和未标记位置，将复杂度从 $O(n^2)$ 降低到 $O(n \log n)$。
- **数学归纳法**：通过数学归纳法证明排列必须由若干个公差为1的递增等差数列组成。

### 可拓展之处
- 类似的问题可以通过分析生成器的规则，找出排列的特定结构，从而简化问题。
- 使用线段树或其他数据结构优化查找过程，可以应用于其他需要高效查找和更新的问题。

### 推荐题目
1. [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---
处理用时：60.63秒