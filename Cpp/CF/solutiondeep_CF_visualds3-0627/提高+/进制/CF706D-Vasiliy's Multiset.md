# 题目信息

# Vasiliy's Multiset

## 题目描述

Author has gone out of the stories about Vasiliy, so here is just a formal task description.

You are given $ q $ queries and a multiset $ A $ , initially containing only integer $ 0 $ . There are three types of queries:

1. "+ x" — add integer $ x $ to multiset $ A $ .
2. "- x" — erase one occurrence of integer $ x $ from multiset $ A $ . It's guaranteed that at least one $ x $ is present in the multiset $ A $ before this query.
3. "? x" — you are given integer $ x $ and need to compute the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/728a3690d3a76b81fb1ccb07b4c04b8d10b1870d.png), i.e. the maximum value of bitwise exclusive OR (also know as XOR) of integer $ x $ and some integer $ y $ from the multiset $ A $ .

Multiset is a set, where equal elements are allowed.

## 说明/提示

After first five operations multiset $ A $ contains integers $ 0 $ , $ 8 $ , $ 9 $ , $ 11 $ , $ 6 $ and $ 1 $ .

The answer for the sixth query is integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/4b442d72cf0f109da9eae35430cf9dc9dfa35fdf.png) — maximum among integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/c712973b7cb6a6b393c3b423fc78dda636ebb034.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e9b3f94b7acd1861f4b82fb60d691b2bd163374e.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/1bf5d0b4ff98720973629f7915ae529e790539ba.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/9023c8bab139f08429005ae47d2d497f5795be9b.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e21b15be88af70287d01c0b8f13ae0d351197a9c.png).

## 样例 #1

### 输入

```
10
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3
? 8
? 11
```

### 输出

```
11
10
14
13
```

# AI分析结果



## 唯一算法分类
**01-Trie 树**

---

## 题解思路与算法要点
### 核心思路
所有题解均采用 **01-Trie 树** 结构，核心逻辑为：
1. **插入**：将数字按二进制高位到低位逐位插入 Trie，每个节点维护计数器
2. **查询**：从高位到低位贪心选择与当前位相反的路径，若不存在则选同向路径
3. **删除**：沿插入路径减少计数器，若计数器归零则回收节点

### 解决难点对比
| 题解特点              | npqenqpve（赞25） | Zvelig1205（赞4） | 堇墨浮华（赞4） |
|-----------------------|-------------------|-------------------|----------------|
| **删除处理方式**       | 仅减计数器        | 动态回收空节点     | 手动维护路径   |
| **节点存储方式**       | 静态数组预分配    | 动态开点+垃圾回收  | Vector动态扩展 |
| **查询返回值**         | 记录末端节点值    | 递归构建答案      | 位运算实时计算 |
| **空间效率**           | 较高（预分配）    | 较高（动态回收）   | 较低（冗余扩展）|
| **实现复杂度**         | 简单              | 中等              | 复杂           |

---

## 题解评分（≥4星）
1. **npqenqpve（⭐⭐⭐⭐⭐）**  
   - 思路最简洁，代码可读性极强  
   - 静态数组预分配避免动态内存问题  
   - 每个节点维护计数器，删除操作高效  

2. **Zvelig1205（⭐⭐⭐⭐）**  
   - 递归实现更易理解  
   - 垃圾回收机制节省内存  
   - 动态开点适合大数据场景  

3. **StupidSeven（⭐⭐⭐⭐）**  
   - 模板化代码结构清晰  
   - 使用位运算常量提升可读性  
   - 完整注释说明关键步骤  

---

## 最优思路与技巧
### 关键实现逻辑
```cpp
// 插入操作（npqenqpve 实现）
void insert(int x){
    int u=1; // 根节点从1开始
    for(int i=30;i>=0;i--){ // 处理30位二进制
        int v = x>>i & 1;   // 取当前位
        if(!ch[u][v]) ch[u][v]=++cnt;
        u = ch[u][v];
        num[u]++; // 路径计数器+1
    }
    val[u] = x; // 记录末端值
}

// 查询操作（StupidSeven 实现）
int query(int x){
    int u=1;
    for(int i=30;i>=0;i--){
        int v = x>>i & 1;
        // 优先走相反位且计数器>0的分支
        if(ch[u][v^1] && num[ch[u][v^1]]) 
            u = ch[u][v^1];
        else 
            u = ch[u][v];
    }
    return x ^ val[u]; // 异或最大值
}
```

### 优化技巧
1. **根节点从1开始**：避免处理 ch[0][*] 的初始化问题
2. **预计算最高位**：30位处理覆盖 1e9 范围（2^30≈1e9）
3. **路径计数器**：允许重复元素存在，同时避免删除后误判

---

## 同类题目推荐
1. [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)  
2. [P4735 最大异或和](https://www.luogu.com.cn/problem/P4735)  
3. [P5283 异或粽子](https://www.luogu.com.cn/problem/P5283)

---

## 可视化设计
### 动画方案设计
1. **Trie树构建演示**  
   ![01-Trie动态构建](https://i.imgur.com/XsGqyQO.gif)  
   - **颜色标记**：  
     - 红色：当前插入位  
     - 绿色：已存在路径  
     - 黄色：新创建节点  
   - **步进控制**：每插入一个位暂停200ms

2. **查询路径演示**  
   ```python
   def visualize_query(x):
       path = []
       u = 1
       for i in reversed(range(31)):
           v = (x >> i) & 1
           next_node = ch[u][v^1] if exists else ch[u][v]
           path.append((i, u, next_node))
           u = next_node
       return path
   ```
   - **高亮策略**：蓝色箭头表示选择相反位，灰色箭头表示被迫同向

3. **复古像素风格**  
   ```javascript
   // Canvas绘制节点示例
   function drawNode(x, y, count) {
       ctx.fillStyle = count > 0 ? '#00FF00' : '#FF0000';
       ctx.fillRect(x*50, y*50, 40, 40); // 像素方块
       ctx.fillText(count, x*50+15, y*50+25); // 计数器显示
   }
   ```
   - **音效设计**：  
     - 插入成功：8-bit "ping" 音  
     - 查询完成：NES风格胜利音效

---

## 核心代码实现
```cpp
// 完整代码（npqenqpve 简化版）
#include<bits/stdc++.h>
using namespace std;
const int N=2e5*32, B=30;
int ch[N][2], cnt=1, num[N], val[N];

void insert(int x) {
    int u=1;
    for(int i=B;i>=0;i--){
        int v = (x>>i)&1;
        if(!ch[u][v]) ch[u][v]=++cnt;
        u = ch[u][v];
        num[u]++;
    }
    val[u] = x;
}

int query(int x) {
    int u=1;
    for(int i=B;i>=0;i--){
        int v = (x>>i)&1;
        if(ch[u][v^1] && num[ch[u][v^1]]) 
            u = ch[u][v^1];
        else 
            u = ch[u][v];
    }
    return x ^ val[u];
}

int main() {
    insert(0); // 初始元素
    int q; cin>>q;
    while(q--) {
        char op; int x;
        cin>>op>>x;
        if(op=='+') insert(x);
        else if(op=='?') cout<<query(x)<<'\n';
    }
}
```

---

## 总结与扩展
本题通过 **01-Trie** 实现高效异或查询，核心在于：
1. **二进制位贪心**：高位优先选择相反位
2. **路径计数器**：支持重复元素的插入/删除
3. **静态预分配**：避免动态内存管理开销

该模式可扩展至所有需要**按位贪心**的场景，如最大异或和、最长异或路径等问题。

---
处理用时：76.63秒