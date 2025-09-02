# 题目信息

# Rudolf and Snowflakes (simple version)

## 题目描述

This is a simple version of the problem. The only difference is that in this version $ n \le 10^6 $ .

One winter morning, Rudolf was looking thoughtfully out the window, watching the falling snowflakes. He quickly noticed a certain symmetry in the configuration of the snowflakes. And like a true mathematician, Rudolf came up with a mathematical model of a snowflake.

He defined a snowflake as an undirected graph constructed according to the following rules:

- Initially, the graph has only one vertex.
- Then, more vertices are added to the graph. The initial vertex is connected by edges to $ k $ new vertices ( $ k > 1 $ ).
- Each vertex that is connected to only one other vertex is connected by edges to $ k $ more new vertices. This step should be done at least once.

The smallest possible snowflake for $ k = 4 $ is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1846E1/2fc3f5caf761ddee75c017a3deae10ee696f63d1.png)After some mathematical research, Rudolf realized that such snowflakes may not have any number of vertices. Help Rudolf check if a snowflake with $ n $ vertices can exist.

## 样例 #1

### 输入

```
9
1
2
3
6
13
15
255
10101
1000000```

### 输出

```
NO
NO
NO
NO
YES
YES
YES
YES
NO```

# AI分析结果

### 题目重写
# Rudolf and Snowflakes (简单版)

## 题目描述

这是该问题的简单版本，唯一区别在于此版本中 $ n \le 10^6 $。

一个冬天的早晨，Rudolf 若有所思地望着窗外，看着飘落的雪花。他很快注意到雪花构造中的某种对称性。作为一个真正的数学家，Rudolf 提出了一个雪花的数学模型。

他将雪花定义为一个按照以下规则构建的无向图：

- 初始时，图中只有一个顶点。
- 然后，向图中添加更多顶点。初始顶点通过边连接到 $ k $ 个新顶点（$ k > 1 $）。
- 每个只连接到一个其他顶点的顶点通过边连接到 $ k $ 个更多的新顶点。此步骤至少执行一次。

$ k = 4 $ 时最小的雪花如图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1846E1/2fc3f5caf761ddee75c017a3deae10ee696f63d1.png)

经过一些数学研究，Rudolf 意识到这样的雪花可能不具有任意数量的顶点。帮助 Rudolf 检查是否存在具有 $ n $ 个顶点的雪花。

## 样例 #1

### 输入

```
9
1
2
3
6
13
15
255
10101
1000000```

### 输出

```
NO
NO
NO
NO
YES
YES
YES
YES
NO```

### 算法分类
数学、枚举

### 题解分析与结论
题目要求判断一个数 $n$ 是否可以表示为 $1 + k + k^2 + \cdots + k^q$ 的形式，其中 $k \ge 2$ 且 $q \ge 2$。由于 $n \le 10^6$，可以通过枚举 $k$ 和 $q$ 来预处理所有可能的 $n$，然后直接查询。

### 高星题解
1. **作者：xiazha (4星)**
   - **关键亮点**：通过枚举 $k$ 和延伸次数 $x$，预处理所有可能的 $n$，使用桶标记合法 $n$，查询时直接判断。
   - **代码核心**：
     ```cpp
     for(int i=2;i<=1000;i++) {
         sum=1;
         for(int j=1;j<=20;j++) {
             kk=1;
             for(int k=1;k<=j;k++) kk*=i;
             sum+=kk;
             if(sum>=1000000) break;
             if(j>=2) t[sum]=1;
         }
     }
     ```

2. **作者：sgl654321 (4星)**
   - **关键亮点**：使用等比数列求和公式，枚举 $k$ 和 $q$，预处理合法 $n$，查询时直接判断。
   - **代码核心**：
     ```cpp
     for(int k=2;k<=1010;k++) {
         for(int q=2;;q++) {
             if((ksm(k,q+1)-1)/(k-1)>1000000) break;
             else f[(ksm(k,q+1)-1)/(k-1)]=1;
         }
     }
     ```

3. **作者：Nwayy (4星)**
   - **关键亮点**：枚举 $k$ 和 $m$，预处理合法 $n$，使用 `map` 存储，查询时直接判断。
   - **代码核心**：
     ```cpp
     for(i=2;i<=1000000;i++) {
         P[i]=get(1000000000000000000,i);
         check(i);
     }
     ```

### 最优关键思路
通过枚举 $k$ 和 $q$，预处理所有可能的 $n$，使用桶或 `map` 存储合法 $n$，查询时直接判断。这种方法利用了数学公式和枚举技巧，适合处理 $n \le 10^6$ 的情况。

### 可拓展之处
类似的问题可以扩展到更大的 $n$，或者考虑更复杂的雪花构造规则。例如，可以研究 $k$ 和 $q$ 的关系，或者引入更多的图论概念。

### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---
处理用时：26.37秒