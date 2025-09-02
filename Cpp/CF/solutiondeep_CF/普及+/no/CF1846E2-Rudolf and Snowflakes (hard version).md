# 题目信息

# Rudolf and Snowflakes (hard version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ n \le 10^{18} $ .

One winter morning, Rudolf was looking thoughtfully out the window, watching the falling snowflakes. He quickly noticed a certain symmetry in the configuration of the snowflakes. And like a true mathematician, Rudolf came up with a mathematical model of a snowflake.

He defined a snowflake as an undirected graph constructed according to the following rules:

- Initially, the graph has only one vertex.
- Then, more vertices are added to the graph. The initial vertex is connected by edges to $ k $ new vertices ( $ k > 1 $ ).
- Each vertex that is connected to only one other vertex is connected by edges to $ k $ more new vertices. This step should be done at least once.

The smallest possible snowflake for $ k = 4 $ is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1846E2/2fc3f5caf761ddee75c017a3deae10ee696f63d1.png)After some mathematical research, Rudolf realized that such snowflakes may not have any number of vertices. Help Rudolf check whether a snowflake with $ n $ vertices can exist.

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
1000000000000000000```

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

【题目翻译】
# Rudolf and Snowflakes (hard version)

## 题目描述

这是该问题的困难版本。唯一的区别是在这个版本中 $ n \le 10^{18} $。

一个冬天的早晨，Rudolf 若有所思地望着窗外，看着飘落的雪花。他很快注意到雪花的某些对称性。作为一个真正的数学家，Rudolf 提出了一个雪花的数学模型。

他将雪花定义为一个无向图，按照以下规则构建：

- 最初，图中只有一个顶点。
- 然后，向图中添加更多顶点。初始顶点通过边连接到 $ k $ 个新顶点（$ k > 1 $）。
- 每个只连接到一个其他顶点的顶点通过边连接到 $ k $ 个更多的新顶点。此步骤至少执行一次。

$ k = 4 $ 时最小的雪花图如图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1846E2/2fc3f5caf761ddee75c017a3deae10ee696f63d1.png)

经过一些数学研究，Rudolf 意识到这样的雪花图可能没有任意数量的顶点。帮助 Rudolf 检查是否存在具有 $ n $ 个顶点的雪花图。

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
1000000000000000000
```

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
NO
```

【算法分类】数学

【题解分析与结论】

该问题的核心是判断一个数 $n$ 是否可以表示为 $1 + k + k^2 + \cdots + k^q$ 的形式，其中 $k \ge 2$，$q \ge 2$。由于 $n$ 的范围非常大（$n \le 10^{18}$），直接枚举 $k$ 和 $q$ 会超时。因此，大多数题解采用了分段处理的方法，将 $k$ 的范围分为两部分：$k \le 10^6$ 和 $k > 10^6$。对于 $k \le 10^6$，直接枚举 $k$ 和 $q$ 并存储合法的 $n$；对于 $k > 10^6$，由于 $q$ 只能为 2，因此可以通过二分或解方程来判断是否存在满足条件的 $k$。

【评分较高的题解】

1. **作者：sgl654321 (赞：9)**  
   - **星级：5**  
   - **关键亮点**：将 $k$ 分为两段处理，第一段使用 `map` 存储合法 $n$，第二段使用二分查找。代码清晰，优化得当，处理大数时使用了 `__int128`。
   - **核心代码**：
     ```cpp
     for(long long k=2;k<=1000000;k++){
         now=k*k;
         for(long long q=2;;q++){
             now=now*k;
             if((now-1)/(k-1)>1e18)break;
             else f[(now-1)/(k-1)]=1;
         }	
     }
     ```

2. **作者：escapist404 (赞：5)**  
   - **星级：4**  
   - **关键亮点**：通过分段处理 $k$，使用 `set` 存储合法 $n$，对于 $k > 10^6$ 的情况使用一元二次方程求解。思路清晰，代码简洁。
   - **核心代码**：
     ```cpp
     for(long long i = 2; i <= 1000000; ++i){
         __int128 j = i + 1;
         __int128 l = i * i;
         while(j + l <= INF){
             j += l;
             l *= i;
             s.insert(j);
         }
     }
     ```

3. **作者：Coffee_zzz (赞：4)**  
   - **星级：4**  
   - **关键亮点**：枚举 $q$ 并使用二分查找 $k$，处理大数时使用了 `__int128`。思路清晰，代码实现较为简洁。
   - **核心代码**：
     ```cpp
     for(int i=2;i<=62;i++){
         l=2,r=P;
         while(l<=r){
             int m=(l+r)/2,p=check(m,i);
             if(p==n){
                 puts("Yes");
                 return;
             }
             else if(p<n) l=m+1;
             else if(p>n) r=m-1;
         }
     }
     ```

【最优关键思路与技巧】
1. **分段处理**：将 $k$ 分为 $k \le 10^6$ 和 $k > 10^6$ 两部分，分别处理，避免超时。
2. **二分查找**：对于 $k > 10^6$ 的情况，使用二分查找或解方程来判断是否存在满足条件的 $k$。
3. **大数处理**：使用 `__int128` 处理大数运算，避免溢出。

【拓展思路】
类似的问题可以通过分段处理和二分查找来优化时间复杂度。例如，判断一个数是否可以表示为某个数列的和，或者判断某个方程是否有整数解。

【推荐题目】
1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
2. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---
处理用时：48.41秒