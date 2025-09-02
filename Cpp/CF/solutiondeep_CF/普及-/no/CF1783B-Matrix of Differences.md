# 题目信息

# Matrix of Differences

## 题目描述

For a square matrix of integers of size $ n \times n $ , let's define its beauty as follows: for each pair of side-adjacent elements $ x $ and $ y $ , write out the number $ |x-y| $ , and then find the number of different numbers among them.

For example, for the matrix $ \begin{pmatrix} 1 & 3\\ 4 & 2 \end{pmatrix} $ the numbers we consider are $ |1-3|=2 $ , $ |1-4|=3 $ , $ |3-2|=1 $ and $ |4-2|=2 $ ; there are $ 3 $ different numbers among them ( $ 2 $ , $ 3 $ and $ 1 $ ), which means that its beauty is equal to $ 3 $ .

You are given an integer $ n $ . You have to find a matrix of size $ n \times n $ , where each integer from $ 1 $ to $ n^2 $ occurs exactly once, such that its beauty is the maximum possible among all such matrices.

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
1 3
4 2
1 3 4
9 2 7
5 8 6```

# AI分析结果

### 题目内容
# 差值矩阵

## 题目描述
对于一个 $n \times n$ 的整数方阵，我们按如下方式定义其美丽度：对于每一对相邻（有公共边）的元素 $x$ 和 $y$，写出 $|x - y|$ 的值，然后统计这些值中不同数字的数量。

例如，对于矩阵 $\begin{pmatrix} 1 & 3\\ 4 & 2 \end{pmatrix}$，我们考虑的数字为 $|1 - 3| = 2$，$|1 - 4| = 3$，$|3 - 2| = 1$ 和 $|4 - 2| = 2$；其中有 $3$ 个不同的数字（$2$，$3$ 和 $1$），这意味着它的美丽度等于 $3$。

给定一个整数 $n$。你需要找到一个 $n \times n$ 的矩阵，其中从 $1$ 到 $n^2$ 的每个整数恰好出现一次，使得在所有这样的矩阵中，它的美丽度最大。

## 样例 #1
### 输入
```
2
2
3
```
### 输出
```
1 3
4 2
1 3 4
9 2 7
5 8 6
```

### 算法分类
构造

### 综合分析与结论
各题解核心思路均为构造出能使相邻元素差值种类达到最大（即 $n^2 - 1$ 种）的矩阵。主要差异在于构造矩阵的具体方式。有的题解先构造出 $n^2 - n$ 种差值的矩阵，再通过翻转偶数行来补齐剩下的差值；有的通过“反复横跳”“之”字形、螺旋形、蛇形等不同方式直接构造出满足要求的矩阵；还有使用 dfs 来放置序列到矩阵中。

### 所选的题解
- **作者：_299817_（5星）**
    - **关键亮点**：思路清晰，先分析简单构造得到 $n^2 - n$ 种差值的情况，再通过翻转偶数行巧妙补齐剩下的 $n$ 种差值，代码实现简洁明了。
    ```cpp
    int main(){
        ios::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        cin >> T; 
        while(T--){
            cin >> n;
            int i1 = 1; 
            int i2 = n * n; 
            int flag = 0; 
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= n; j++){
                    if(flag == 0){ 
                        a[i][j] = i1;
                        i1++;
                        flag = 1;
                    }else{ 
                        a[i][j] = i2;
                        i2--;
                        flag = 0;
                    }
                }
            }
            for(int i = 1; i <= n; i++){
                if(i % 2 == 0){ 
                    for(int j = 1; j <= n / 2; j++){ 
                        swap(a[i][j], a[i][n - j + 1]);
                    }
                }
            }
            for(int i = 1; i <= n; i++){ 
                for(int j = 1; j <= n; j++){
                    cout << a[i][j] << " ";
                }
                cout << "\n";
            }
        }
        return 0;
    }
    ```
    - **核心实现思想**：首先通过交替放置最小数和最大数构造出有 $n^2 - n$ 种差值的矩阵，然后对偶数行进行翻转，使得相邻元素差值能覆盖 $1$ 到 $n^2 - 1$ 所有值。
- **作者：cyrxdzj（4星）**
    - **关键亮点**：提出“反复横跳”的排列思路，直接构造出满足最大美丽度的矩阵，代码实现基于这种思路，逻辑连贯。
    ```cpp
    int main()
    {
        scanf("%d",&t);
        while(t--)
        {
            scanf("%d",&n);
            int now=1,cnt=1;
            for(int i=1;i<=n;i++)
            {
                if(i&1)
                {
                    for(int j=1;j<=n;j++)
                    {
                        a[i][j]=now;
                        if(cnt&1)
                        {
                            now=n*n-now+1;
                        }
                        else
                        {
                            now=n*n-now+2;
                        }
                        cnt++;
                    }
                }
                else
                {
                    for(int j=n;j>=1;j--)
                    {
                        a[i][j]=now;
                        if(cnt&1)
                        {
                            now=n*n-now+1;
                        }
                        else
                        {
                            now=n*n-now+2;
                        }
                        cnt++;
                    }
                }
            }
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                {
                    printf("%d ",a[i][j]);
                }
                printf("\n");
            }
        }
        return 0;
    }
    ```
    - **核心实现思想**：按照“反复横跳”思路，根据行的奇偶性，交替改变数字放置规律，使得相邻元素差值能达到 $n^2 - 1$ 种。
- **作者：Night_sea_64（4星）**
    - **关键亮点**：先分析出差值范围，提出通过最大最小数交替相邻构造出差值序列，再以“之”字形填入矩阵，思路易懂，代码简洁。
    ```cpp
    int main()
    {
        int t;
        cin>>t;
        while(t--)
        {
            int n;
            cin>>n;
            a[1][1]=1;
            int last=1,now=n*n-1,p=1;
            for(int i=1;i<=n;i++)
            {
                if(i%2)
                    for(int j=(i==1?2:1);j<=n;j++)
                    {
                        a[i][j]=last=last+now*p;
                        p=0-p,now--;
                    }
                else for(int j=n;j>=1;j--)
                    {
                        a[i][j]=last=last+now*p;
                        p=0-p,now--;
                    }
            }
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                    cout<<a[i][j]<<" ";
                cout<<endl;
            }
        }
        return 0;
    }
    ```
    - **核心实现思想**：先确定第一个数为 $1$，根据最大最小数交替相邻构造出差值序列，按行的奇偶性以“之”字形将数字填入矩阵，保证相邻元素差值覆盖 $1$ 到 $n^2 - 1$。

### 最优关键思路或技巧
构造矩阵时，利用最大最小数交替相邻的方式构造出差值序列，然后通过特定的矩阵填充方式（如翻转偶数行、“之”字形、蛇形等），使矩阵相邻元素差值能覆盖从 $1$ 到 $n^2 - 1$ 的所有值，从而达到最大美丽度。

### 可拓展之处
同类型题通常围绕特定规则下的矩阵或序列构造，类似算法套路为先分析目标结果（如最大差值种类），再寻找合适的构造方式。例如一些构造满足特定条件的幻方、数独变体等题目。

### 洛谷相似题目推荐
- [P1156 垃圾陷阱](https://www.luogu.com.cn/problem/P1156)：涉及到对不同条件的分析与构造策略。
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)：通过特定规则对矩阵进行遍历和状态更新，与本题构造矩阵有相似思考过程。
- [P1990 覆盖墙壁](https://www.luogu.com.cn/problem/P1990)：同样是在一定限制条件下的构造问题，锻炼构造思路。 

---
处理用时：57.49秒