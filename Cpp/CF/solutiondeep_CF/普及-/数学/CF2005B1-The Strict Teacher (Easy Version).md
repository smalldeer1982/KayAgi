# 题目信息

# The Strict Teacher (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions are the constraints on $ m $ and $ q $ . In this version, $ m=2 $ and $ q=1 $ . You can make hacks only if both versions of the problem are solved.

Narek and Tsovak were busy preparing this round, so they have not managed to do their homework and decided to steal David's homework. Their strict teacher noticed that David has no homework and now wants to punish him. She hires other teachers to help her catch David. And now $ m $ teachers together are chasing him. Luckily, the classroom is big, so David has many places to hide.

The classroom can be represented as a one-dimensional line with cells from $ 1 $ to $ n $ , inclusive.

At the start, all $ m $ teachers and David are in distinct cells. Then they make moves. During each move

- David goes to an adjacent cell or stays at the current one.
- Then, each of the $ m $ teachers simultaneously goes to an adjacent cell or stays at the current one.

This continues until David is caught. David is caught if any of the teachers (possibly more than one) is located in the same cell as David. Everyone sees others' moves, so they all act optimally.

Your task is to find how many moves it will take for the teachers to catch David if they all act optimally.

Acting optimally means the student makes his moves in a way that maximizes the number of moves the teachers need to catch him; and the teachers coordinate with each other to make their moves in a way that minimizes the number of moves they need to catch the student.

Also, as Narek and Tsovak think this task is easy, they decided to give you $ q $ queries on David's position. Note: this is the easy version, and you are given only one query.

## 说明/提示

In the first example, the student can just stay at cell $ 2 $ . The teacher, initially located in cell $ 1 $ , can reach cell $ 2 $ in one move. Therefore, the answer is $ 1 $ .

In the second example, the student should just stay at cell $ 1 $ . The teacher, initially located in cell $ 3 $ , can reach cell $ 1 $ in two moves. Therefore, the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
10 2 1
1 4
2
8 2 1
3 6
1
8 2 1
3 6
8```

### 输出

```
1
2
2```

# AI分析结果

### 题目内容重写

#### 严格的老师（简单版）

**题目描述**

这是问题的简单版本。两个版本之间的唯一区别在于对 $m$ 和 $q$ 的限制。在这个版本中，$m=2$ 且 $q=1$。只有在两个版本的问题都解决的情况下，你才能进行 hack。

Narek 和 Tsovak 忙于准备这次比赛，因此他们没有完成作业，决定偷 David 的作业。他们的严格老师注意到 David 没有作业，现在想要惩罚他。她雇佣了其他老师来帮助她抓住 David。现在共有 $m$ 个老师一起追捕他。幸运的是，教室很大，David 有很多地方可以躲藏。

教室可以表示为一个从 $1$ 到 $n$ 的一维直线。

开始时，所有 $m$ 个老师和 David 都在不同的单元格中。然后他们开始移动。在每一步中：

- David 可以移动到相邻的单元格或留在当前单元格。
- 然后，每个老师同时移动到相邻的单元格或留在当前单元格。

这个过程一直持续到 David 被抓住。David 被抓住的条件是任何一个老师（可能不止一个）与 David 位于同一个单元格。每个人都能看到其他人的移动，因此他们都会采取最优策略。

你的任务是找出老师们需要多少步才能抓住 David，假设他们都采取最优策略。

采取最优策略意味着学生会采取行动以最大化老师们抓住他所需的步数；而老师们会协调彼此的行动以最小化抓住学生所需的步数。

此外，由于 Narek 和 Tsovak 认为这个任务很简单，他们决定给你 $q$ 次关于 David 位置的查询。注意：这是简单版本，你只会收到一次查询。

**说明/提示**

在第一个例子中，学生可以留在单元格 $2$。老师最初位于单元格 $1$，可以在一步内到达单元格 $2$。因此，答案是 $1$。

在第二个例子中，学生应该留在单元格 $1$。老师最初位于单元格 $3$，可以在两步内到达单元格 $1$。因此，答案是 $2$。

**样例 #1**

**输入**

```
3
10 2 1
1 4
2
8 2 1
3 6
1
8 2 1
3 6
8
```

**输出**

```
1
2
2
```

### 题解综合分析与结论

这道题的核心在于通过分类讨论来确定老师们抓住 David 所需的最少步数。所有题解都采用了类似的思路，即将 David 的位置与两个老师的位置进行比较，分为三种情况：

1. **David 在所有老师的左边**：David 会尽可能向左移动，老师们也会向左移动，最终 David 会被最左边的老师抓住。所需步数为 $b_1 - 1$。
2. **David 在两个老师之间**：David 会停留在两个老师的中间，老师们会向中间移动，最终 David 会被两个老师同时抓住。所需步数为 $\frac{b_2 - b_1}{2}$。
3. **David 在所有老师的右边**：David 会尽可能向右移动，老师们也会向右移动，最终 David 会被最右边的老师抓住。所需步数为 $n - b_2$。

所有题解都正确地实现了这一思路，并且代码简洁明了。不同题解的区别主要在于代码的实现细节和优化程度。

### 所选高分题解

#### 题解作者：masonxiong (5星)

**关键亮点**：
- 思路清晰，分类讨论全面。
- 代码简洁，使用了 `sort` 函数对老师的位置进行排序，确保 $b_1 < b_2$。
- 代码可读性强，使用了 `ios::sync_with_stdio(false)` 和 `cin.tie(nullptr)` 来优化输入输出。

**代码核心实现**：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t, n, m, q, a, b[2];
    for (cin >> t; t--; ) {
        cin >> n >> m >> q >> b[0] >> b[1] >> a;
        sort(b, b + 2);
        if (a < b[0])
            cout << b[0] - 1 << '\n';
        else if (a > b[1])
            cout << n - b[1] << '\n';
        else
            cout << (b[1] - b[0]) / 2 << '\n';
    }
    return 0;
}
```

#### 题解作者：封禁用户 (4星)

**关键亮点**：
- 思路清晰，分类讨论全面。
- 代码简洁，使用了 `swap` 函数确保 $b_1 < b_2$。
- 代码可读性强，直接输出结果。

**代码核心实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,q,a,b1,b2;
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m>>q>>b1>>b2>>a;
        if(b1>b2) swap(b1,b2);
        if(a<b1) cout<<b1-1<<endl;
        else if(a<b2) cout<<(b2-b1)/2<<endl;
        else cout<<n-b2<<endl;
    }
}
```

#### 题解作者：xiaokang_suancai (4星)

**关键亮点**：
- 思路清晰，分类讨论全面。
- 代码简洁，使用了 `swap` 函数确保 $b_1 < b_2$。
- 代码可读性强，直接输出结果。

**代码核心实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,q,b1,b2,a;
int main()
{
    ios::sync_with_stdio(0); // 快读
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>q;
        cin>>b1>>b2;
        cin>>a;
        if(b1>b2)
            swap(b1,b2); // 给老师位置排序
        if(a<b1)
            cout<<b1-1<<endl;
        else if(b1<a&&a<b2)
            cout<<(b2-b1)/2<<endl;
        else if(a>b2)
            cout<<n-b2<<endl; // 三种情况上面已经讲了，不再赘述
    }
    return 0;
}
```

### 最优关键思路或技巧

1. **分类讨论**：根据 David 的位置与两个老师的位置关系，分为三种情况进行讨论。
2. **排序优化**：通过排序确保 $b_1 < b_2$，简化后续的判断逻辑。
3. **输入输出优化**：使用 `ios::sync_with_stdio(false)` 和 `cin.tie(nullptr)` 来加速输入输出。

### 可拓展之处

1. **多老师情况**：如果老师数量增加，可以考虑使用贪心或动态规划来确定最优策略。
2. **多维空间**：如果教室是多维空间，可以考虑使用图论中的最短路径算法来确定最优策略。

### 推荐相似题目

1. **P1002 过河卒**：考察分类讨论和动态规划。
2. **P1044 栈**：考察分类讨论和递归。
3. **P1057 传球游戏**：考察分类讨论和动态规划。

---
处理用时：55.92秒