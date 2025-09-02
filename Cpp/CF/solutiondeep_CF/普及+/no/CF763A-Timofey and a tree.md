# 题目信息

# Timofey and a tree

## 题目描述

Each New Year Timofey and his friends cut down a tree of $ n $ vertices and bring it home. After that they paint all the $ n $ its vertices, so that the $ i $ -th vertex gets color $ c_{i} $ .

Now it's time for Timofey birthday, and his mother asked him to remove the tree. Timofey removes the tree in the following way: he takes some vertex in hands, while all the other vertices move down so that the tree becomes rooted at the chosen vertex. After that Timofey brings the tree to a trash can.

Timofey doesn't like it when many colors are mixing together. A subtree annoys him if there are vertices of different color in it. Timofey wants to find a vertex which he should take in hands so that there are no subtrees that annoy him. He doesn't consider the whole tree as a subtree since he can't see the color of the root vertex.

A subtree of some vertex is a subgraph containing that vertex and all its descendants.

Your task is to determine if there is a vertex, taking which in hands Timofey wouldn't be annoyed.

## 样例 #1

### 输入

```
4
1 2
2 3
3 4
1 2 1 1
```

### 输出

```
YES
2```

## 样例 #2

### 输入

```
3
1 2
2 3
1 2 3
```

### 输出

```
YES
2```

## 样例 #3

### 输入

```
4
1 2
2 3
3 4
1 2 1 2
```

### 输出

```
NO```

# AI分析结果

### 题目内容
#### Timofey和一棵树
1. **题目描述**：每年新年，Timofey和他的朋友们都会砍倒一棵有$n$个顶点的树并带回家。之后，他们给这$n$个顶点都涂上颜色，使得第$i$个顶点被涂成颜色$c_{i}$。
现在到了Timofey的生日，他的妈妈让他把树拿走。Timofey按如下方式移除这棵树：他先拿起某个顶点，然后其他所有顶点向下移动，使这棵树以他拿起的顶点为根。之后Timofey把树拿到垃圾桶。
Timofey不喜欢多种颜色混合在一起。如果一个子树中有不同颜色的顶点，这个子树就会让他烦恼。Timofey想找到一个顶点，当他拿起这个顶点时，不存在让他烦恼的子树。他不把整棵树看作一个子树，因为他看不到根顶点的颜色。
某个顶点的子树是指包含该顶点及其所有后代的子图。
你的任务是判断是否存在这样一个顶点，使得Timofey拿起它时不会烦恼。
2. **样例 #1**
    - **输入**
```
4
1 2
2 3
3 4
1 2 1 1
```
    - **输出**
```
YES
2
```
3. **样例 #2**
    - **输入**
```
3
1 2
2 3
1 2 3
```
    - **输出**
```
YES
2
```
4. **样例 #3**
    - **输入**
```
4
1 2
2 3
3 4
1 2 1 2
```
    - **输出**
```
NO
```

### 算法分类
无算法分类

### 题解综合分析与结论
这些题解主要围绕寻找一个能使子树内颜色统一的根节点展开。不同题解思路各有特点：
 - **lixiao189与Erica_N_Contina思路相近**：通过统计边两端颜色不同的情况，若某个节点连接颜色不同节点的数量等于总的颜色不同边的数量，该节点即为所求。此方法巧妙利用了子树颜色合法的特性，避免了复杂的树形结构遍历。
 - **zhangqiuyanAFOon2024与Bai_R_X思路相似**：先找出与邻接节点颜色不同数量最多的节点，再通过深搜判断以此节点为根时子树颜色是否统一。这种方法直观，但深搜部分增加了代码复杂度。
 - **CQ_Bob采用DP结合换根操作**：定义状态函数表示子树颜色是否相同，通过DFS序和分块处理换根后的情况，复杂度较高。
 - **huangrenheluogu同样利用换根操作**：通过$f_x$表示子树与$x$颜色是否相同，判断根节点所有儿子情况并进行转移。

整体来看，lixiao189和Erica_N_Contina的方法思路简洁，代码实现清晰，相对更优。

### 所选的题解
#### 作者：lixiao189 (5星)
 - **关键亮点**：思路清晰，通过统计颜色不同的边的数量来判断符合条件的节点，无需复杂的树形结构处理，代码简洁高效。
 - **核心代码片段**：
```cpp
for (int i=1;i<=n-1;i++){
    if (col[a[i]]!= col[b[i]]){
        sum1++;
        sum[a[i]]++;sum[b[i]]++;
    }
}

for (int i=1;i<=n;i++){
    if (sum[i]==sum1){
        printf ("YES\n%d\n",i);
        return 0;
    }
}
```
核心实现思想：遍历所有边，若边两端顶点颜色不同，统计总数`sum1`，并对两端顶点的不同颜色连接数`sum`加1。最后遍历所有顶点，若某个顶点的`sum`值等于`sum1`，则该顶点为所求。

#### 作者：Erica_N_Contina (5星)
 - **关键亮点**：与lixiao189思路类似，表述清晰，通过边权设置和统计来判断符合条件的根节点，代码简洁明了。
 - **核心代码片段**：
```cpp
for(int i=1;i<n;i++){
    if(c[a[i]]!=c[b[i]])cnt[a[i]]++,cnt[b[i]]++,sum++;
}

for(int i=1;i<=n;i++){
    if(cnt[i]==sum){
        cout<<"YES\n"<<i;
        return 0;
    }
}
```
核心实现思想：遍历所有边，若边两端顶点颜色不同，对应顶点的出边边权和`cnt`加1，同时统计所有边权和`sum`。遍历所有顶点，若某个顶点的`cnt`值等于`sum`，则该顶点为所求。

### 最优关键思路或技巧
通过统计边两端颜色不同的情况来确定符合条件的根节点，避免对树形结构进行复杂的遍历和处理，简化了问题的求解过程。

### 可拓展之处
同类型题可围绕树形结构和节点颜色条件展开，类似算法套路为通过统计一些关键信息（如颜色不同的边数、节点连接情况等）来简化对树形结构的判断，避免直接对每个子树进行复杂的递归遍历。

### 洛谷相似题目
 - [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及对图中节点的分类处理，与本题对节点颜色的判断有相似之处。
 - [P2016 战略游戏](https://www.luogu.com.cn/problem/P2016)：在树形结构上进行策略选择，与本题在树形结构上找符合条件节点思路类似。
 - [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：同样基于树形结构进行决策，可类比本题在树上寻找合适节点的过程。 

---
处理用时：44.03秒