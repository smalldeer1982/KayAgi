# 题目信息

# Forever Winter

## 题目描述

A snowflake graph is generated from two integers $ x $ and $ y $ , both greater than $ 1 $ , as follows:

- Start with one central vertex.
- Connect $ x $ new vertices to this central vertex.
- Connect $ y $ new vertices to each of these $ x $ vertices.

 For example, below is a snowflake graph for $ x=5 $ and $ y=3 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829F/8093abf53ab9afd4293f2937f4849e3ca604a47a.png)The snowflake graph above has a central vertex $ 15 $ , then $ x=5 $ vertices attached to it ( $ 3 $ , $ 6 $ , $ 7 $ , $ 8 $ , and $ 20 $ ), and then $ y=3 $ vertices attached to each of those.

 Given a snowflake graph, determine the values of $ x $ and $ y $ .

## 说明/提示

The first test case is pictured in the statement. Note that the output 3 5 is incorrect, since $ x $ should be output before $ y $ .

## 样例 #1

### 输入

```
3
21 20
21 20
5 20
13 20
1 3
11 3
10 3
4 8
19 8
14 8
9 7
12 7
17 7
18 6
16 6
2 6
6 15
7 15
8 15
20 15
3 15
7 6
1 2
1 3
2 4
2 5
3 6
3 7
9 8
9 3
3 6
6 2
2 1
5 2
2 7
4 3
3 8```

### 输出

```
5 3
2 2
2 3```

# AI分析结果

### 题目翻译
# Forever Winter

## 题目描述

一个雪花图由两个大于1的整数$x$和$y$生成，具体步骤如下：

- 从一个中心顶点开始。
- 将$x$个新的顶点连接到这个中心顶点。
- 将$y$个新的顶点分别连接到这$x$个顶点中的每一个。

例如，下图是$x=5$和$y=3$的雪花图。![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829F/8093abf53ab9afd4293f2937f4849e3ca604a47a.png)图中的中心顶点是$15$，然后有$x=5$个顶点连接到它（$3$、$6$、$7$、$8$和$20$），接着每个这些顶点又连接了$y=3$个顶点。

给定一个雪花图，确定$x$和$y$的值。

## 说明/提示

第一个测试用例如题目描述所示。注意输出3 5是错误的，因为$x$应该在$y$之前输出。

## 样例 #1

### 输入

```
3
21 20
21 20
5 20
13 20
1 3
11 3
10 3
4 8
19 8
14 8
9 7
12 7
17 7
18 6
16 6
2 6
6 15
7 15
8 15
20 15
3 15
7 6
1 2
1 3
2 4
2 5
3 6
3 7
9 8
9 3
3 6
6 2
2 1
5 2
2 7
4 3
3 8
```

### 输出

```
5 3
2 2
2 3
```

### 算法分类
图论

### 题解分析与结论
本题的核心是通过图的度数信息来确定雪花图的$x$和$y$。雪花图的结构决定了中心顶点的度数为$x$，第二层顶点的度数为$y+1$，第三层顶点的度数为1。通过统计各层顶点的度数，可以推导出$x$和$y$的值。

### 精选题解

#### 题解1：zhlzt (★★★★★)
**关键亮点**：
- 通过统计度数为1的顶点数量来确定第三层顶点的数量。
- 使用STL set来存储第二层顶点，确保不重复，从而确定$x$。
- 通过第三层顶点数量除以$x$来确定$y$。

**核心代码**：
```cpp
set<int>st;int ans=0;
for(int i=1;i<=n;i++) if(cnt[i]==1){
    ans++,st.insert(edge[i][0]);
} 
printf("%d %d\n",st.size(),ans/st.size());
```

#### 题解2：cjh20090318 (★★★★)
**关键亮点**：
- 通过求树的重心来确定中心顶点。
- 重心的出度即为$x$，其子节点的出度减一即为$y$。

**核心代码**：
```cpp
dfs(1,0,n);
printf("%d %d\n",(int)G[rt].size(),(int)G[G[rt][0]].size()-1);
```

#### 题解3：luqyou (★★★★)
**关键亮点**：
- 通过枚举每个顶点作为根节点，计算深度来确定中心顶点。
- 深度为1的顶点数量为$x$，深度为2的顶点数量除以$x$为$y$。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){//确定根
    dfs(i,0,0);
    bool f=1;
    sum1=0;
    sum2=0;
    for(int j=1;j<=n;j++){
        if(depth[j]==1) sum1++;
        if(depth[j]==2) sum2++;
        if(depth[j]>2){
            f=0;
            break;
        }
    }
    if(f){
        break;
    }
}
cout<<sum1<<" "<<sum2/sum1<<endl;
```

### 最优关键思路
通过统计图中各层顶点的度数，结合雪花图的结构特点，可以高效地推导出$x$和$y$的值。使用STL set来去重和统计第二层顶点数量是一个巧妙的优化。

### 拓展思路
类似的问题可以扩展到其他类型的图结构，如星型图、环形图等，通过分析图的度数分布来确定其结构参数。

### 推荐题目
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)
2. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

---
处理用时：34.95秒