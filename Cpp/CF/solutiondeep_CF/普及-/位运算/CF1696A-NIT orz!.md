# 题目信息

# NIT orz!

## 题目描述

NIT, the cleaver, is new in town! Thousands of people line up to orz him. To keep his orzers entertained, NIT decided to let them solve the following problem related to $ \operatorname{or} z $ . Can you solve this problem too?

You are given a 1-indexed array of $ n $ integers, $ a $ , and an integer $ z $ . You can do the following operation any number (possibly zero) of times:

- Select a positive integer $ i $ such that $ 1\le i\le n $ . Then, simutaneously set $ a_i $ to $ (a_i\operatorname{or} z) $ and set $ z $ to $ (a_i\operatorname{and} z) $ . In other words, let $ x $ and $ y $ respectively be the current values of $ a_i $ and $ z $ . Then set $ a_i $ to $ (x\operatorname{or}y) $ and set $ z $ to $ (x\operatorname{and}y) $ .

Here $ \operatorname{or} $ and $ \operatorname{and} $ denote the [bitwise operations OR and AND](https://en.wikipedia.org/wiki/Bitwise_operation) respectively.

Find the maximum possible value of the maximum value in $ a $ after any number (possibly zero) of operations.

## 说明/提示

In the first test case of the sample, one optimal sequence of operations is:

- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (3\operatorname{or}3)=3 $ and $ z $ becomes $ (3\operatorname{and}3)=3 $ .
- Do the operation with $ i=2 $ . Now $ a_2 $ becomes $ (4\operatorname{or}3)=7 $ and $ z $ becomes $ (4\operatorname{and}3)=0 $ .
- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (3\operatorname{or}0)=3 $ and $ z $ becomes $ (3\operatorname{and}0)=0 $ .

After these operations, the sequence $ a $ becomes $ [3,7] $ , and the maximum value in it is $ 7 $ . We can prove that the maximum value in $ a $ can never exceed $ 7 $ , so the answer is $ 7 $ .

In the fourth test case of the sample, one optimal sequence of operations is:

- Do the operation with $ i=1 $ . Now $ a_1 $ becomes $ (7\operatorname{or}7)=7 $ and $ z $ becomes $ (7\operatorname{and}7)=7 $ .
- Do the operation with $ i=3 $ . Now $ a_3 $ becomes $ (30\operatorname{or}7)=31 $ and $ z $ becomes $ (30\operatorname{and}7)=6 $ .
- Do the operation with $ i=5 $ . Now $ a_5 $ becomes $ (27\operatorname{or}6)=31 $ and $ z $ becomes $ (27\operatorname{and}6)=2 $ .

## 样例 #1

### 输入

```
5
2 3
3 4
5 5
0 2 4 6 8
1 9
10
5 7
7 15 30 29 27
3 39548743
10293834 10284344 13635445```

### 输出

```
7
13
11
31
48234367```

# AI分析结果

### 题目中文重写
# NIT 太牛啦！

## 题目描述
NIT，这位厉害的人物，初来乍到！成千上万的人排着队向他膜拜。为了让膜拜他的人开心，NIT 决定让他们解决下面这个与“orz”相关的问题。你也能解决这个问题吗？

给定一个从 1 开始索引、包含 $n$ 个整数的数组 $a$ 以及一个整数 $z$。你可以进行任意次数（可能为零）以下操作：

- 选择一个正整数 $i$，满足 $1 \leq i \leq n$。然后，同时将 $a_i$ 设置为 $(a_i \text{ or } z)$，并将 $z$ 设置为 $(a_i \text{ and } z)$。换句话说，设 $x$ 和 $y$ 分别为 $a_i$ 和 $z$ 的当前值。那么将 $a_i$ 设置为 $(x \text{ or } y)$，并将 $z$ 设置为 $(x \text{ and } y)$。

这里的“or”和“and”分别表示[按位或和按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation)。

在进行任意次数（可能为零）的操作后，找出数组 $a$ 中的最大值的最大可能值。

## 说明/提示
在样例的第一个测试用例中，一个最优的操作序列如下：

- 对 $i = 1$ 进行操作。现在 $a_1$ 变为 $(3 \text{ or } 3) = 3$，$z$ 变为 $(3 \text{ and } 3) = 3$。
- 对 $i = 2$ 进行操作。现在 $a_2$ 变为 $(4 \text{ or } 3) = 7$，$z$ 变为 $(4 \text{ and } 3) = 0$。
- 对 $i = 1$ 进行操作。现在 $a_1$ 变为 $(3 \text{ or } 0) = 3$，$z$ 变为 $(3 \text{ and } 0) = 0$。

经过这些操作后，数组 $a$ 变为 $[3, 7]$，其中的最大值为 7。我们可以证明数组 $a$ 中的最大值永远不会超过 7，所以答案是 7。

在样例的第四个测试用例中，一个最优的操作序列如下：

- 对 $i = 1$ 进行操作。现在 $a_1$ 变为 $(7 \text{ or } 7) = 7$，$z$ 变为 $(7 \text{ and } 7) = 7$。
- 对 $i = 3$ 进行操作。现在 $a_3$ 变为 $(30 \text{ or } 7) = 31$，$z$ 变为 $(30 \text{ and } 7) = 6$。
- 对 $i = 5$ 进行操作。现在 $a_5$ 变为 $(27 \text{ or } 6) = 31$，$z$ 变为 $(27 \text{ and } 6) = 2$。

## 样例 #1
### 输入
```
5
2 3
3 4
5 5
0 2 4 6 8
1 9
10
5 7
7 15 30 29 27
3 39548743
10293834 10284344 13635445
```

### 输出
```
7
13
11
31
48234367
```

### 综合分析与结论
这些题解的核心思路一致，都是基于位运算的性质来解题。按位或操作会使数字变大或不变，按位与操作会使数字变小或不变，所以 $z$ 的值只会不增，对每个 $a_i$ 最多进行一次操作就能得到最优解。只需遍历数组 $a$，求出每个 $a_i$ 与 $z$ 按位或的最大值即可。

### 所选题解
- **作者：Prms_Prmt（5星）**
    - **关键亮点**：思路清晰，先阐述位运算的特殊性质，通过集合的概念解释 $z$ 的变化，进而得出仅需操作一次的结论，代码简洁明了。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,a,z;

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        int mx=0;
        scanf("%d%d",&n,&z);
        for(int i=1;i<=n;i++)
            scanf("%d",&a),mx=max(mx,a|z);
        printf("%d\n",mx);
    }
    return 0;
}
```
核心实现思想：先读取测试用例的数量 $t$，对于每个测试用例，读取数组长度 $n$ 和整数 $z$，然后遍历数组，不断更新 $a_i$ 与 $z$ 按位或的最大值，最后输出该最大值。

- **作者：zhicheng（4星）**
    - **关键亮点**：思路直接，从题目要求出发，分析出 $z$ 只会变小，所以第一次操作一定是最大的，代码简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,a,b,p,ans;
    scanf("%d",&n);
    while(n--){
        ans=0;
        scanf("%d%d",&a,&b);
        while(a--){
            scanf("%d",&p);
            ans=max(ans,b|p);
        }
        printf("%d\n",ans);
    }
}
```
核心实现思想：读取测试用例数量 $n$，对于每个测试用例，读取数组长度 $a$ 和整数 $b$，遍历数组，不断更新 $p$ 与 $b$ 按位或的最大值，最后输出该最大值。

- **作者：智子（4星）**
    - **关键亮点**：先明确题目大意，再详细分析位运算性质，得出答案是序列 $a$ 中每个 $a_i$ 与 $z$ 进行或运算后的最大值，代码规范。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2000 + 5;

int a[MAXN];
int n, z;

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &z);
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            ans = max(ans, a[i] | z);
        }
        printf("%d\n", ans);
    }

    return 0;
}
```
核心实现思想：读取测试用例数量 $T$，对于每个测试用例，读取数组长度 $n$ 和整数 $z$，将数组元素存入 $a$ 数组，遍历数组，不断更新 $a[i]$ 与 $z$ 按位或的最大值，最后输出该最大值。

### 最优关键思路或技巧
- **思维方式**：从位运算的本质出发，分析按位或和按位与操作对数字的影响，进而得出 $z$ 的变化趋势，从而简化问题。
- **代码实现技巧**：使用 `max` 函数不断更新最大值，使代码简洁高效。

### 可拓展之处
同类型题可能会改变操作规则或增加更多的限制条件，但核心还是围绕位运算的性质。例如，可能会增加其他位运算操作，或者要求在满足某些条件下进行操作，解题时仍需深入分析位运算的特点。

### 洛谷相似题目推荐
1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)：涉及区间动态规划和位运算的结合。
2. [P2196 [NOIP1996 提高组] 挖地雷](https://www.luogu.com.cn/problem/P2196)：需要运用位运算来处理状态。
3. [P1464 Function](https://www.luogu.com.cn/problem/P1464)：其中可能会用到位运算来优化时间复杂度。

### 个人心得摘录与总结
无。

---
处理用时：41.87秒