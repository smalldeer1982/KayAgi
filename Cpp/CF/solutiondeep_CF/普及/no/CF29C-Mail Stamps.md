# 题目信息

# Mail Stamps

## 题目描述

One day Bob got a letter in an envelope. Bob knows that when Berland's post officers send a letter directly from city «A» to city «B», they stamp it with «A B», or «B A». Unfortunately, often it is impossible to send a letter directly from the city of the sender to the city of the receiver, that's why the letter is sent via some intermediate cities. Post officers never send a letter in such a way that the route of this letter contains some city more than once. Bob is sure that the post officers stamp the letters accurately.

There are $ n $ stamps on the envelope of Bob's letter. He understands that the possible routes of this letter are only two. But the stamps are numerous, and Bob can't determine himself none of these routes. That's why he asks you to help him. Find one of the possible routes of the letter.

## 样例 #1

### 输入

```
2
1 100
100 2
```

### 输出

```
2 100 1 ```

## 样例 #2

### 输入

```
3
3 1
100 2
3 2
```

### 输出

```
100 2 3 1 ```

# AI分析结果



# Mail Stamps

## 题目描述

有一天 Bob 收到了一封带有邮票的信。Bob 知道当 Berland 的邮局将信件从城市 A 直接寄往城市 B 时，会在信件上盖「A B」或「B A」的邮戳。由于经常无法直接将信件从发件人城市直接寄到收件人城市，信件会通过一些中间城市转寄。邮局绝不会让信件经过重复的城市。Bob 确信邮局准确地盖上了所有邮戳。

信封上有 $n$ 个邮戳，Bob 意识到可能的信件路线只有两种。但由于邮票数量太多，Bob 无法自行确定其中任意一条路线。因此他请求你帮助找出其中一种可能的信件路线。

## 样例 #1

### 输入
```
2
1 100
100 2
```

### 输出
```
2 100 1
```

## 样例 #2

### 输入
```
3
3 1
100 2
3 2
```

### 输出
```
100 2 3 1
```

---

**算法分类**：图论 / 深度优先搜索 (DFS)

---

### 题解分析与结论

#### 核心思路
所有题解均基于以下两个关键点：
1. **链式结构特性**：路径必然是一条链，起点和终点的度为1，中间节点的度为2
2. **离散化处理**：使用 `map` 处理高达 $10^9$ 的稀疏节点编号，避免传统数组越界

#### 最优思路提炼
1. **度数统计法**：通过统计每个节点的邻接数量（度数），度数为1的节点即为路径端点
2. **链式DFS遍历**：从任意端点出发，DFS遍历时记录前驱节点防止回溯，保证线性时间复杂度
3. **动态邻接表**：使用 `map<int, vector<int>>` 直接存储原始节点编号，省去离散化映射步骤

---

### 精选题解

#### 1. Empty_Dream（5星）
**亮点**：代码简洁高效，直接利用 STL 特性
```cpp
map<int, vector<int>> g;
void dfs(int x, int fa) {
    cout << x << " ";
    for (int v : g[x]) 
        if (v != fa) dfs(v, x);
}
```
- 直接使用 `map` 存储邻接表，省去离散化步骤
- 仅需一次遍历即可找到起点，DFS 直接输出路径

#### 2. Jerrywang09（4星）
**亮点**：迭代法实现，内存占用更低
```cpp
int prev = -1;
while (true) {
    cout << v << " ";
    for (int to : a[v]) 
        if (to != prev) { 
            prev = v; 
            v = to; 
            break; 
        }
    if (a[v].size() == 1 && prev != -1) break;
}
```
- 通过 `prev` 变量记录前驱节点，避免递归栈开销
- 线性遍历时间复杂度 $O(n)$

#### 3. Ag2WO4（4星）
**亮点**：Python实现展现算法本质
```python
while len(a[e[-1]])-1:
    for j in a[e[-1]]:
        if j != e[-2]: e.append(j); break
```
- 利用列表直接记录路径，每次仅需比较前驱节点
- 无需复杂数据结构，适合理解算法核心逻辑

---

### 拓展训练
1. **链式结构检测**：[P2661 信息传递](https://www.luogu.com.cn/problem/P2661)（最小环检测）
2. **离散化应用**：[P1955 程序自动分析](https://www.luogu.com.cn/problem/P1955)（大规模离散数据并查集）
3. **图遍历变式**：[P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)（二分图染色）

---

### 心得摘录
> "发现度数为1的节点必定是端点后，问题瞬间从图遍历简化为链式遍历" —— Empty_Dream  
> "双向映射的离散化虽然增加了代码量，但能避免处理原始编号的混乱" —— Minecraft万岁  
> "Python的动态列表在处理链式结构时意外地简洁" —— Ag2WO4

这些心得体现了从图论特性到实现细节的深刻理解，特别是在处理大规模稀疏数据时，选择合适的数据结构直接影响代码复杂度。

---
处理用时：55.59秒