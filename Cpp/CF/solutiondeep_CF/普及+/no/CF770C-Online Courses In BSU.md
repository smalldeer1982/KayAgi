# 题目信息

# Online Courses In BSU

## 题目描述

Now you can take online courses in the Berland State University! Polycarp needs to pass $ k $ main online courses of his specialty to get a diploma. In total $ n $ courses are availiable for the passage.

The situation is complicated by the dependence of online courses, for each course there is a list of those that must be passed before starting this online course (the list can be empty, it means that there is no limitation).

Help Polycarp to pass the least number of courses in total to get the specialty (it means to pass all main and necessary courses). Write a program which prints the order of courses.

Polycarp passes courses consistently, he starts the next course when he finishes the previous one. Each course can't be passed more than once.

## 说明/提示

In the first test firstly you can take courses number $ 1 $ and $ 2 $ , after that you can take the course number $ 4 $ , then you can take the course number $ 5 $ , which is the main. After that you have to take only the course number $ 3 $ , which is the last not passed main course.

## 样例 #1

### 输入

```
6 2
5 3
0
0
0
2 2 1
1 4
1 5
```

### 输出

```
5
1 2 3 4 5 
```

## 样例 #2

### 输入

```
9 3
3 9 5
0
0
3 9 4 5
0
0
1 8
1 6
1 2
2 1 2
```

### 输出

```
6
1 2 9 4 5 3 
```

## 样例 #3

### 输入

```
3 3
1 2 3
1 2
1 3
1 1
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 鲍里斯州立大学的在线课程

## 题目描述
现在你可以在鲍里斯州立大学参加在线课程！波利卡普需要通过他专业的 $k$ 门主要在线课程才能获得文凭。总共有 $n$ 门课程可供选择。

由于在线课程之间存在依赖关系，情况变得复杂起来。对于每一门课程，都有一个必须在开始学习该课程之前通过的课程列表（该列表可能为空，这意味着没有限制）。

帮助波利卡普通过最少数量的课程来获得该专业的文凭（即通过所有主要课程和必要的前置课程）。编写一个程序，输出课程的学习顺序。

波利卡普按顺序学习课程，他完成前一门课程后才开始下一门课程。每门课程不能学习超过一次。

## 说明/提示
在第一个测试用例中，首先可以学习课程1和2，之后可以学习课程4，然后可以学习课程5，这是一门主要课程。之后，只需要学习课程3，这是最后一门尚未通过的主要课程。

## 样例 #1
### 输入
```
6 2
5 3
0
0
0
2 2 1
1 4
1 5
```
### 输出
```
5
1 2 3 4 5 
```

## 样例 #2
### 输入
```
9 3
3 9 5
0
0
3 9 4 5
0
0
1 8
1 6
1 2
2 1 2
```
### 输出
```
6
1 2 9 4 5 3 
```

## 样例 #3
### 输入
```
3 3
1 2 3
1 2
1 3
1 1
```
### 输出
```
-1
```

### 算法分类
深度优先搜索 DFS

### 综合分析与结论
这些题解主要围绕通过深度优先搜索（DFS）或结合拓扑排序来解决课程依赖问题。思路上，大多从主要课程出发，通过递归方式处理前置课程。算法要点在于如何标记已访问和已通过的课程，避免重复学习。难点主要是判环，不同题解采用了不同的判环方式。部分题解直接从主要课程进行 DFS 并在过程中判环，部分题解先通过拓扑排序判环再进行后续操作。

### 所选的题解
- **作者：WsW_ (5星)**
    - **关键亮点**：思路清晰，代码简洁。采用 DFS 对每个需要通过的科目进行处理，通过两个标记数组分别记录是否通过和是否递归，在递归过程中巧妙判环，最后使用队列存储答案方便输出。
    - **重点代码**：
```cpp
void pass(int t){
    if(vst[t]){//重复递归，有环
        cout<<-1;
        exit(0);
    }
    vst[t]=1;
    for(int i=0;i<edg[t].size();i++){
        if(!vis[edg[t][i]])pass(edg[t][i]);//先通过前置科目
    }
    vis[t]=1;//再通过这个科目
    ans.push(t);//按顺序存入答案
}
```
核心实现思想：在 `pass` 函数中，先判断是否重复递归（即是否有环），然后递归处理前置课程，最后标记当前课程已通过并加入答案队列。
- **作者：dlzlj_2010 (4星)**
    - **关键亮点**：利用拓扑排序思想，从主要科目开始搜索，通过两个标记数组分别记录是否被访问和是否通过，在搜索过程中判环，逻辑清晰。
    - **重点代码**：
```cpp
bool dfs(int u){//拓扑排序
    if(vis[u])return 0;//有环
    vis[u]=1;//标记为已访问
    for(auto v:e[u]){//遍历前置科目
        if(!passed[v]){//未通过
            bool f=dfs(v);//通过前置科目
            if(!f)//有环就一路返回0
                return 0;
        }
    }
    passed[u]=1,ans.push_back(u);//加入答案
    return 1;
}
```
核心实现思想：在 `dfs` 函数中，先判断是否有环（若已访问则有环），然后遍历前置科目，递归处理未通过的前置科目，若过程中有环则返回0，最后标记当前科目已通过并加入答案数组。
- **作者：OldVagrant (4星)**
    - **关键亮点**：采用贪心思路，从主修课出发，只关注主修课及其前置课程，通过递归函数模拟学习过程，代码简洁明了。
    - **重点代码**：
```cpp
void work(int x){
    if(ok[x]) return;//如果x已经被学完了，就可以直接return掉。
    if(vis[x]) cout<<-1,exit(0);//访问同一个点两次，意味着出现了环，而如果在work函数里遇到环的话就代表着某门主修课永远无法学习，于是无解。
    vis[x]=1;//标记一下
    for(auto j:pre[x]) work(j);//学习x之前，要先去学x的所有前置课程
    ans[++tot]=x,ok[x]=1;//学完了x的所有前置课程，现在可以学x了。
    return;
}
```
核心实现思想：在 `work` 函数中，先判断课程是否已学完，再判断是否有环，然后递归处理前置课程，最后标记当前课程已学并加入答案数组。

### 最优关键思路或技巧
通过DFS处理课程依赖关系时，利用标记数组记录课程状态，有效避免重复访问和处理，同时在递归过程中巧妙判环。如WsW_ 的题解，使用两个标记数组，一个记录课程是否已通过，另一个记录是否正在递归中，以此判断是否存在环。

### 可拓展之处
同类型题目通常围绕有向图的拓扑结构，处理任务依赖、工序安排等问题。类似算法套路是在处理有依赖关系的任务时，合理利用DFS或拓扑排序，并注意判环问题。

### 推荐题目
- [P1983 车站分级](https://www.luogu.com.cn/problem/P1983)：通过对车站等级关系构建有向图，利用拓扑排序求解车站最少分级数。
- [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)：涉及有向图的强连通分量及缩点操作，与本题判环及处理图结构有相似之处。
- [P2051 [AHOI2009]中国象棋](https://www.luogu.com.cn/problem/P2051)：虽然主要是动态规划，但在处理棋盘状态依赖关系时，可类比本题处理课程依赖关系的思想。 

---
处理用时：70.17秒