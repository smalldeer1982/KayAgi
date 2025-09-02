# 题目信息

# Mocha and Hiking

## 题目描述

The city where Mocha lives in is called Zhijiang. There are $ n+1 $ villages and $ 2n-1 $ directed roads in this city.

There are two kinds of roads:

- $ n-1 $ roads are from village $ i $ to village $ i+1 $ , for all $ 1\leq i \leq n-1 $ .
- $ n $ roads can be described by a sequence $ a_1,\ldots,a_n $ . If $ a_i=0 $ , the $ i $ -th of these roads goes from village $ i $ to village $ n+1 $ , otherwise it goes from village $ n+1 $ to village $ i $ , for all $ 1\leq i\leq n $ .

Mocha plans to go hiking with Taki this weekend. To avoid the trip being boring, they plan to go through every village exactly once. They can start and finish at any villages. Can you help them to draw up a plan?

## 说明/提示

In the first test case, the city looks like the following graph:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1559C/c2e581af2a9a8a7c84fbcdcb044c393f08812267.png)

So all possible answers are $ (1 \to 4 \to 2 \to 3) $ , $ (1 \to 2 \to 3 \to 4) $ .

In the second test case, the city looks like the following graph:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1559C/50cae05bb483d2eef22f0fe8c5bad7425f443436.png)

So all possible answers are $ (4 \to 1 \to 2 \to 3) $ , $ (1 \to 2 \to 3 \to 4) $ , $ (3 \to 4 \to 1 \to 2) $ , $ (2 \to 3 \to 4 \to 1) $ .

## 样例 #1

### 输入

```
2
3
0 1 0
3
1 1 0```

### 输出

```
1 4 2 3 
4 1 2 3```

# AI分析结果

### 题目内容重写

**题目描述**

Mocha 居住的城市叫做 Zhijiang。这个城市有 $n+1$ 个村庄和 $2n-1$ 条有向道路。

道路分为两种：

- $n-1$ 条道路是从村庄 $i$ 到村庄 $i+1$，其中 $1\leq i \leq n-1$。
- $n$ 条道路可以由一个序列 $a_1,\ldots,a_n$ 描述。如果 $a_i=0$，则第 $i$ 条道路是从村庄 $i$ 到村庄 $n+1$；否则，这条道路是从村庄 $n+1$ 到村庄 $i$，其中 $1\leq i\leq n$。

Mocha 计划本周末和 Taki 一起去远足。为了避免旅途无聊，他们计划经过每个村庄恰好一次。他们可以从任意村庄开始和结束。你能帮他们制定一个计划吗？

**说明/提示**

在第一个测试用例中，城市的结构如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1559C/c2e581af2a9a8a7c84fbcdcb044c393f08812267.png)

所以所有可能的答案是 $ (1 \to 4 \to 2 \to 3) $ 和 $ (1 \to 2 \to 3 \to 4) $。

在第二个测试用例中，城市的结构如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1559C/50cae05bb483d2eef22f0fe8c5bad7425f443436.png)

所以所有可能的答案是 $ (4 \to 1 \to 2 \to 3) $、$ (1 \to 2 \to 3 \to 4) $、$ (3 \to 4 \to 1 \to 2) $ 和 $ (2 \to 3 \to 4 \to 1) $。

**样例 #1**

### 输入

```
2
3
0 1 0
3
1 1 0```

### 输出

```
1 4 2 3 
4 1 2 3```

### 算法分类
构造

### 题解分析与结论

本题的核心在于如何构造一条经过所有村庄且每个村庄只经过一次的路径。通过对题目的分析，可以发现路径的构造主要依赖于三种情况：

1. 如果 $a_1=1$，即从村庄 $n+1$ 可以到达村庄 $1$，则可以直接从 $n+1$ 开始遍历所有村庄。
2. 如果 $a_n=0$，即从村庄 $n$ 可以到达村庄 $n+1$，则可以直接从村庄 $1$ 开始遍历到村庄 $n+1$。
3. 如果存在一个村庄 $i$，使得 $a_i=0$ 且 $a_{i+1}=1$，则可以从村庄 $i$ 跳到村庄 $n+1$，然后再回到村庄 $i+1$。

这些题解的思路基本一致，主要区别在于代码的实现细节和可读性。以下是对部分题解的评分和关键亮点的总结。

### 所选高分题解

#### 题解作者：thhxxx (赞：3)
**星级：4星**
**关键亮点：**
- 思路清晰，代码简洁，直接处理了三种情况。
- 时间复杂度为 $O(n)$，效率较高。

**核心代码：**
```cpp
if (rd[1] == 1) {
    cout << n + 1 << ' ';
    for (int i = 1; i < n; i++) cout << i << ' ';
    cout << n << '\n';
}
else if (rd[n] == 0) {
    for (int i = 1; i <= n; i++) cout << i << ' ';
    cout << n + 1 << '\n';
}
else {
    int pos = 0;
    for (int i = 1; i < n; i ++) {
        if (rd[i] == 0 && rd[i + 1] == 1) {
            pos = i;
            break;
        }
    }
    for (int i = 1; i <= pos; i++) cout << i << ' ';
    cout << n + 1 << ' ';
    for (int i = pos + 1; i < n; i++) cout << i << ' ';
    cout << n << '\n';
}
```

#### 题解作者：sunzz3183 (赞：1)
**星级：4星**
**关键亮点：**
- 代码结构清晰，逻辑明确。
- 使用了 `bool` 变量 `qwq` 来标记是否找到符合条件的路径，增加了代码的可读性。

**核心代码：**
```cpp
if(a[1]==1){
    cout<<n+1<<" ";
    for(int i=1;i<=n;i++)
        cout<<i<<" ";
    cout<<"\n";
    continue;
}
if(a[n]==0){
    for(int i=1;i<=n;i++)
        cout<<i<<" ";
    cout<<n+1<<"\n";
    continue;
}
for(int i=1;i<n;i++){
    if(a[i]==0&&a[i+1]==1){
        for(int j=1;j<=i;j++)
            cout<<j<<" ";
        cout<<n+1<<" ";
        for(int j=i+1;j<=n;j++)
            cout<<j<<" ";
        qwq=0;
        break;
    }
}
```

#### 题解作者：江户川·萝卜 (赞：1)
**星级：4星**
**关键亮点：**
- 代码简洁，逻辑清晰，直接处理了三种情况。
- 使用了 `bool` 变量 `win` 来标记是否找到符合条件的路径，增加了代码的可读性。

**核心代码：**
```cpp
if(!a[1]){
    bool win=0;int d;
    for(int i=1;i<n;i++)if(!a[i]&&a[i+1]) win=1,d=i;
    if(!win&&a[n]) puts("-1");
    else{
        if(!win) d=n;
        for(int i=1;i<=d;i++) printf("%d ",i);
        printf("%d ",n+1);
        for(int i=d+1;i<=n;i++) printf("%d ",i);
        puts("");
    }
}
else{
    printf("%d ",n+1);
    for(int i=1;i<=n;i++) printf("%d ",i);
    puts(""); 
}
```

### 最优关键思路或技巧
1. **分类讨论**：通过分析题目中的三种情况，分别处理不同的路径构造方式。
2. **标记变量**：使用 `bool` 变量来标记是否找到符合条件的路径，增加代码的可读性和逻辑清晰度。
3. **时间复杂度优化**：通过一次遍历找到符合条件的路径，时间复杂度为 $O(n)$，保证了代码的效率。

### 可拓展之处
本题的构造思路可以推广到其他类似的图论问题中，特别是涉及到路径构造和遍历的问题。类似的题目可能涉及到更复杂的图结构或更多的约束条件，但基本的分类讨论和标记变量的思路仍然适用。

### 推荐题目
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)
2. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
3. [P1353 跑步](https://www.luogu.com.cn/problem/P1353)

### 个人心得摘录
- **thhxxx**：通过分类讨论，直接处理了三种情况，代码简洁高效。
- **sunzz3183**：使用 `bool` 变量 `qwq` 来标记是否找到符合条件的路径，增加了代码的可读性。
- **江户川·萝卜**：代码简洁，逻辑清晰，直接处理了三种情况，使用 `bool` 变量 `win` 来标记是否找到符合条件的路径。

---
处理用时：58.52秒