# 题目信息

# Misha and Forest

## 题目描述

Let's define a forest as a non-directed acyclic graph (also without loops and parallel edges). One day Misha played with the forest consisting of $ n $ vertices. For each vertex $ v $ from $ 0 $ to $ n-1 $ he wrote down two integers, $ degree_{v} $ and $ s_{v} $ , were the first integer is the number of vertices adjacent to vertex $ v $ , and the second integer is the XOR sum of the numbers of vertices adjacent to $ v $ (if there were no adjacent vertices, he wrote down $ 0 $ ).

Next day Misha couldn't remember what graph he initially had. Misha has values $ degree_{v} $ and $ s_{v} $ left, though. Help him find the number of edges and the edges of the initial graph. It is guaranteed that there exists a forest that corresponds to the numbers written by Misha.

## 说明/提示

The XOR sum of numbers is the result of bitwise adding numbers modulo $ 2 $ . This operation exists in many modern programming languages. For example, in languages C++, Java and Python it is represented as "^", and in Pascal — as "xor".

## 样例 #1

### 输入

```
3
2 3
1 0
1 0
```

### 输出

```
2
1 0
2 0
```

## 样例 #2

### 输入

```
2
1 1
1 0
```

### 输出

```
1
0 1
```

# AI分析结果



【中文重写题目】
# Misha和森林

## 题目描述

定义森林为无向无环图（不含自环和平行边）。Misha有一个包含n个顶点的森林，对于每个顶点v（0到n-1），他记录了度数degree_v（相邻顶点数）和s_v（相邻顶点编号的异或和，若无相邻顶点则为0）。现在请你根据这些信息还原原始森林的边。

## 输入格式
第一行输入n，随后n行每行给出degree_v和s_v。

## 输出格式
第一行输出边数，随后每行输出一条边的两个顶点（任意顺序）。

## 样例
见原题样例

---

**算法分类**：拓扑排序（BFS）、构造

---

### 题解分析与结论

各题解均采用类似拓扑排序的思路，利用叶子节点（度=1）的异或和唯一确定相邻顶点，通过逐步消减叶子节点还原边。关键差异在于数据结构的选用：

1. **优先队列法**（_H17_，4星）
   - 亮点：使用优先队列处理度数变化，理论上支持更复杂的度数处理
   - 缺点：优先队列的logN复杂度在本题中不必要

2. **标准队列法**（World_Creater，5星）
   - 亮点：直接使用普通队列维护度为1的节点，时间复杂度O(N)
   - 代码简洁，逻辑清晰，维护度数和异或值的操作高效

3. **拓扑推演法**（lichenxi111，4星）
   - 亮点：详细说明拓扑排序的树结构应用场景
   - 实现与队列法相同，理论解释更充分

---

### 最优题解代码（World_Creater）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d[100005],a[100005];
vector<pair<int,int> > ans;
queue<int> q;

int main() {
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>d[i]>>a[i];
        if(d[i]==1) q.push(i);
    }
    while(!q.empty()) {
        int x=q.front(); q.pop();
        if(d[x]==0) continue;
        int y=a[x];
        ans.push_back({x,y});
        a[y] ^= x;
        if(--d[y]==1) q.push(y);
        d[x]--;
    }
    cout<<ans.size()<<"\n";
    for(auto p:ans) 
        cout<<p.first<<" "<<p.second<<"\n";
}
```

**核心思想**：
1. 初始化时将所有度=1的节点入队
2. 每次取出队列头部节点x，其异或值y即为唯一的相邻节点
3. 将边(x,y)加入答案，并更新y的异或值和度数
4. 若y的度数变为1则入队，继续处理

---

### 关键技巧总结

1. **拓扑排序应用**：将森林的叶子节点视为拓扑起点，逐步消减得到边信息
2. **异或性质利用**：a ^ b ^ a = b，通过异或操作逆向消去已处理的节点
3. **队列维护**：仅需处理度=1的节点，保证线性时间复杂度

---

### 类似题目推荐

1. P1144 最短路计数（BFS应用）
2. P1038 神经网络（拓扑排序经典题）
3. P2661 信息传递（环检测与拓扑结合）

---

### 题解心得摘录

> "很像交互题" —— lichenxi111  
> 指出本题逆向推导特性与交互题的相似性，强调思维转换的重要性

> "堆顶肯定是度数为1，直接就是下一个点" —— _H17_  
> 强调优先队列的取数特性，但实际测试发现普通队列更优，体现数据结构选择的重要性

---
处理用时：74.76秒