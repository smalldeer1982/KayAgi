# 题目信息

# Seating of Students

## 题目描述

Students went into a class to write a test and sat in some way. The teacher thought: "Probably they sat in this order to copy works of each other. I need to rearrange them in such a way that students that were neighbors are not neighbors in a new seating."

The class can be represented as a matrix with $ n $ rows and $ m $ columns with a student in each cell. Two students are neighbors if cells in which they sit have a common side.

Let's enumerate students from $ 1 $ to $ n·m $ in order of rows. So a student who initially sits in the cell in row $ i $ and column $ j $ has a number $ (i-1)·m+j $ . You have to find a matrix with $ n $ rows and $ m $ columns in which all numbers from $ 1 $ to $ n·m $ appear exactly once and adjacent numbers in the original matrix are not adjacent in it, or determine that there is no such matrix.

## 说明/提示

In the first test case the matrix initially looks like this:

`<br></br>1 2 3 4<br></br>5 6 7 8<br></br>`It's easy to see that there are no two students that are adjacent in both matrices.

In the second test case there are only two possible seatings and in both of them students with numbers 1 and 2 are neighbors.

## 样例 #1

### 输入

```
2 4
```

### 输出

```
YES
5 4 7 2 
3 6 1 8 
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 学生座位安排

## 题目描述
学生们进入教室参加考试，并以某种方式就座。老师心想：“他们可能是为了互相抄袭才这样坐的。我需要重新安排他们的座位，使得原本相邻的学生在新座位中不再相邻。”

教室可以表示为一个有 $n$ 行和 $m$ 列的矩阵，每个单元格中有一名学生。如果两个学生所在的单元格有一条公共边，那么这两个学生就是相邻的。

让我们按行的顺序将学生从 $1$ 到 $n·m$ 编号。因此，最初坐在第 $i$ 行第 $j$ 列单元格中的学生编号为 $(i - 1)·m + j$ 。你必须找到一个有 $n$ 行和 $m$ 列的矩阵，其中从 $1$ 到 $n·m$ 的所有数字都恰好出现一次，并且原始矩阵中相邻的数字在新矩阵中不相邻，或者确定不存在这样的矩阵。

## 说明/提示
在第一个测试用例中，矩阵最初如下所示：

`<br></br>1 2 3 4<br></br>5 6 7 8<br></br>`很容易看出，在这两个矩阵中没有两个学生是相邻的。

在第二个测试用例中，只有两种可能的座位安排，并且在这两种安排中，编号为 1 和 2 的学生都是相邻的。

## 样例 #1
### 输入
```
2 4
```
### 输出
```
YES
5 4 7 2 
3 6 1 8 
```
## 样例 #2
### 输入
```
2 1
```
### 输出
```
NO
```

### 算法分类
搜索（深度优先搜索 DFS）、构造

### 题解综合分析与结论
1. **L7_56题解**：
    - **思路**：采用深度优先搜索（DFS）来枚举每个位置放置的数字。由于 $n,m \leq 10^5$ 开二维数组会内存超限，利用 $n*m \leq 10^5$ 的条件，将二维数组转化为一维数组存储。
    - **算法要点**：定义 `dfs` 函数递归搜索每个位置，`beside` 函数判断两个数在原矩阵是否相邻，通过交换一维数组元素模拟放置数字过程。
    - **难点解决**：用一维数组代替二维数组存储数据，巧妙解决内存问题。
2. **cmll02题解**：
    - **思路**：采用构造法。对图黑白格染色后白格平移解决 $n\geq 8$ 或 $m\geq 8$ 的情况；对 $n\geq4$ 且 $m\geq 4$ 的情况，先打乱每行（奇偶分开倒序排序）再打乱每列；剩下小数据情况手算答案。
    - **算法要点**：分情况构造不同的座位排列方式，利用黑白格染色和平移以及行列打乱的策略。
    - **难点解决**：针对不同规模的数据，设计不同的构造方法，避免了复杂的搜索过程。
3. **流绪题解**：
    - **思路**：与L7_56类似，使用深度优先搜索，从第一个位置开始向后搜索，对每个位置枚举后面所有位置，判断交换后是否符合题意。同样因为内存问题使用一维数组存储并计算坐标。
    - **算法要点**：`dfs` 函数递归搜索，`check` 函数判断交换后是否符合相邻条件。
    - **难点解决**：和L7_56一样，通过一维数组解决内存问题。

综合来看，L7_56和流绪的DFS思路较为常规直接，cmll02的构造法相对巧妙，针对不同规模数据有不同策略，减少了搜索的复杂度。

### 所选的题解
- **cmll02题解**：★★★★
    - **关键亮点**：采用构造法，针对不同规模的数据设计不同构造策略，避免复杂搜索，有效降低时间复杂度。
    - **重点代码**：
```cpp
// 解决 n≥8 或 m≥8 的情况
namespace subtask1{
    void solve(int n,int m)
    {
        puts("YES");
        int cnt=0;
        int **b=new int*[n];
        for(int i=0;i<n;i++)b[i]=new int[m];
        int u=n&2147483646;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                cnt++;
                if((i+j+1)&1)b[i][j]=cnt;
                else
                {
                    int q=i+4;
                    if(q>=n)
                    {
                        if(n&1)
                            if(q&1)q=q-n+1;
                            else q=q-n-1;
                        else q=q-n;
                    }
                    b[q][j]=cnt;
                }
            }
        }
        for(int i=0;i<n;i++,puts(""))
            for(int j=0;j<m;j++)printf("%d ",b[i][j]);
        delete[] b;
    }
}
// 解决 n≥4 且 m≥4 的情况
namespace subtask3{
    void fill(int*a,int n,int d)
    {
        int cnt=1;
        for(int i=(n+1)>>1;i>0;i--)a[i-1]=d+cnt,cnt+=2;
        cnt=n;
        for(int i=2;i<=n;i+=2)a[--cnt]=d+i;
    }
    void solve(int n,int m)
    {
        // 小数据情况直接输出答案
        if(n==1&&m==1)puts("YES\n1");
        else if(n==1&&m==2)puts("NO");
        else if(n==2&&m==1)puts("NO");
        else if(n==2&&m==2)puts("NO");
        else if(n==2&&m==3)puts("NO");
        else if(n==3&&m==2)puts("NO");
        else if(n+m==4)puts("NO");
        else if(n==3&&m==3)puts("YES\n5 1 6\n3 9 4\n7 2 8");
        else
        {
            puts("YES");
            if(n<m)
            {
                int **b=new int*[m];
                for(int i=0;i<m;i++)b[i]=new int[n];
                int cnt=2;
                for(int i=m/2+1;i<=m;i++)fill(b[i-1],m,cnt*n),cnt+=2;
                cnt=1;
                for(int i=1;i<=m/2;i++)fill(b[i-1],m,cnt*n),cnt+=2;
                for(int j=0;j<n;j++,puts(""))
                    for(int i=0;i<m;i++)printf("%d ",b[i][j]);
                delete[] b;
            }
            else
            {
                int **b=new int*[n];
                int cnt=0;
                for(int i=n/2+1;i<=n;i++)fill(b[i-1],m,cnt*m),cnt+=2;
                cnt=1;
                for(int i=1;i<=n/2;i++)fill(b[i-1],m,cnt*m),cnt+=2;
                for(int i=0;i<n;i++,puts(""))
                    for(int j=0;j<m;j++)printf("%d ",b[i][j]);
                delete[] b;
            }
        }
    }
}
```
    - **核心实现思想**：`subtask1` 函数处理 $n\geq 8$ 或 $m\geq 8$ 的情况，通过黑白格染色，白格向下平移四格（处理边界情况）构造座位排列；`subtask3` 函数处理 $n\geq4$ 且 $m\geq 4$ 的情况，通过 `fill` 函数对每行或每列奇偶分开倒序排序构造座位排列，小数据情况直接输出答案。

### 最优关键思路或技巧
cmll02题解的构造法是一种很巧妙的技巧，针对不同规模数据采用不同构造策略，避免了DFS在大规模数据下的高时间复杂度，提高了算法效率。同时，将二维数组问题转化为一维数组存储以解决内存问题也是通用的技巧。

### 拓展思路
同类型题可考虑一些涉及图的重新布局且有相邻限制的题目，类似算法套路可以是根据数据规模分情况讨论，对于大数据采用构造法，小数据可以暴力搜索或直接给出结果。

### 洛谷题目推荐
1. **P1118 数字三角形**：通过递推和搜索解决数字三角形路径问题，涉及类似的搜索与构造思路。
2. **P1433 吃奶酪**：需要搜索不同路径，判断是否符合条件，和本题DFS思路类似。
3. **P1036 [NOIP2002 普及组] 选数**：利用搜索解决组合问题，和本题搜索思路有相通之处。 

---
处理用时：64.44秒