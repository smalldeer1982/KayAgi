# 题目信息

# Berpizza

## 题目描述

Monocarp and Polycarp are working as waiters in Berpizza, a pizzeria located near the center of Bertown. Since they are waiters, their job is to serve the customers, but they choose whom they serve first differently.

At the start of the working day, there are no customers at the Berpizza. They come there one by one. When a customer comes into the pizzeria, she sits and waits for Monocarp or Polycarp to serve her. Monocarp has been working in Berpizza for just two weeks, so whenever he serves a customer, he simply chooses the one who came to Berpizza first, and serves that customer.

On the other hand, Polycarp is an experienced waiter at Berpizza, and he knows which customers are going to spend a lot of money at the pizzeria (and which aren't) as soon as he sees them. For each customer, Polycarp estimates the amount of money this customer can spend, and when he serves a customer, he chooses the one that is expected to leave the most money at Berpizza (in case there are several such customers, he chooses the one who came first among them).

Obviously, no customer can be served twice, so Monocarp and Polycarp choose which customer to serve only among those who haven't been served yet.

When the number of customers gets really high, it becomes difficult for both Monocarp and Polycarp to choose the customer they are going to serve. Your task is to write a program that makes these choices for them. Formally, your program should be able to process three types of queries:

- $ 1 $ $ m $ — a customer comes to Berpizza, and Polycarp estimates the amount of money that they will spend as $ m $ ;
- $ 2 $ — Monocarp serves a customer which came to the pizzeria first;
- $ 3 $ — Polycarp serves a customer which is expected to spend the largest amount of money at the pizzeria (if there are several such customers, the one that came to the pizzeria first is chosen).

For each query of types $ 2 $ and $ 3 $ , report the number of the customer who was served (the customers are numbered in the order they come to the pizzeria, starting from $ 1 $ ).

## 样例 #1

### 输入

```
8
1 8
1 10
1 6
3
2
1 9
2
3```

### 输出

```
2 1 3 4```

## 样例 #2

### 输入

```
6
1 8
1 10
1 8
3
3
3```

### 输出

```
2 1 3```

## 样例 #3

### 输入

```
8
1 103913
3
1 103913
1 103913
3
1 103913
1 103913
2```

### 输出

```
1 2 3```

# AI分析结果

### 题目重写
Monocarp 和 Polycarp 是位于 Bertown 中心的 Berpizza 披萨店的两位服务员。他们的工作是为顾客服务，但他们的服务顺序选择方式不同。

在工作开始时，Berpizza 没有顾客。顾客们一个接一个地来到店里。当顾客来到披萨店时，她会坐下等待 Monocarp 或 Polycarp 为她服务。Monocarp 刚在 Berpizza 工作了两周，因此每当他服务顾客时，他会选择最早来到 Berpizza 的顾客进行服务。

另一方面，Polycarp 是 Berpizza 的一位经验丰富的服务员，他能够一眼看出哪些顾客会在披萨店花费大量金钱（哪些不会）。对于每个顾客，Polycarp 会估计该顾客在披萨店的花费金额，当他服务顾客时，他会选择预计花费最多的顾客（如果有多个这样的顾客，他会选择最早来到店里的那个）。

显然，每个顾客只能被服务一次，因此 Monocarp 和 Polycarp 只能从尚未被服务的顾客中选择。

当顾客数量非常多时，Monocarp 和 Polycarp 很难选择要服务的顾客。你的任务是编写一个程序来为他们做出选择。具体来说，你的程序需要能够处理以下三种类型的查询：

- `1 m` — 一个顾客来到 Berpizza，Polycarp 估计该顾客的花费金额为 `m`；
- `2` — Monocarp 服务最早来到披萨店的顾客；
- `3` — Polycarp 服务预计花费最多的顾客（如果有多个这样的顾客，选择最早来到店里的那个）。

对于每个类型为 `2` 和 `3` 的查询，输出被服务的顾客的编号（顾客按来到披萨店的顺序编号，从 `1` 开始）。

### 算法分类
模拟、队列、优先队列

### 题解分析与结论
该题的核心在于如何处理三种不同类型的查询，特别是如何在高效的时间内找到最早来到的顾客或花费最多的顾客。大多数题解采用了队列和优先队列的结合，利用队列处理 `2` 类型查询，优先队列处理 `3` 类型查询，并通过标记数组来避免重复服务。

### 精选题解

#### 题解1：作者：lzy120406 (赞：1)
**星级：4**
**关键亮点：**
- 使用队列和优先队列分别处理 `2` 和 `3` 类型查询。
- 通过标记数组 `served` 来记录顾客是否已被服务，避免重复服务。
- 代码结构清晰，逻辑简单易懂。

**核心代码：**
```cpp
queue<int> monoQueue; // Monocarp 的队列
priority_queue<Customer> polyQueue; // Polycarp 的优先队列
bool served[500005]; // 标记顾客是否被服务

void solve() {
    int id = 0;
    while (n--) {
        int op;
        cin >> op;
        if (op == 1) {
            int m;
            cin >> m;
            customerId++;
            monoQueue.push(customerId);
            polyQueue.push({customerId, m});
        } else if (op == 2) {
            while (!monoQueue.empty() && served[monoQueue.front()]) {
                monoQueue.pop(); // 跳过已服务的顾客
            }
            if (!monoQueue.empty()) {
                int id = monoQueue.front();
                monoQueue.pop();
                served[id] = true;
                cout << id << " ";
            }
        } else if (op == 3) {
            while (!polyQueue.empty() && served[polyQueue.top().id]) {
                polyQueue.pop(); // 跳过已服务的顾客
            }
            if (!polyQueue.empty()) {
                int id = polyQueue.top().id;
                polyQueue.pop();
                served[id] = true;
                cout << id << " ";
            }
        }
    }
}
```

#### 题解2：作者：wangkelin123 (赞：1)
**星级：4**
**关键亮点：**
- 使用优先队列和全局变量 `t` 来处理 `2` 类型查询，优化了查找未服务顾客的效率。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码：**
```cpp
int t=0;//全局

while(vis[++t]);
cout<<t<<' ';
vis[t]=true;
```

#### 题解3：作者：KSToki (赞：1)
**星级：4**
**关键亮点：**
- 使用优先队列和标记数组 `vis` 来处理 `3` 类型查询，确保每次找到的顾客都是未被服务的。
- 代码结构清晰，逻辑简单易懂。

**核心代码：**
```cpp
while(vis[q.top().id]) q.pop();
cout<<q.top().id<<' ';
vis[q.top().id]=true;
q.pop();
```

### 最优关键思路
- **数据结构选择**：使用队列处理 `2` 类型查询，优先队列处理 `3` 类型查询，确保每次查询都能在高效时间内完成。
- **标记数组**：通过标记数组记录顾客是否已被服务，避免重复服务。
- **全局变量优化**：使用全局变量 `t` 来优化查找未服务顾客的效率，减少不必要的遍历。

### 拓展思路
- **同类型题**：类似的问题可以出现在其他需要处理多种查询的场景中，如处理不同类型的任务调度、资源分配等。
- **算法优化**：可以进一步优化优先队列的实现，如使用更高效的数据结构或算法来减少查询时间。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3378 堆](https://www.luogu.com.cn/problem/P3378)
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

---
处理用时：41.94秒