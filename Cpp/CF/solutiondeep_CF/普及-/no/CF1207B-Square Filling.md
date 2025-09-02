# 题目信息

# Square Filling

## 题目描述

You are given two matrices $ A $ and $ B $ . Each matrix contains exactly $ n $ rows and $ m $ columns. Each element of $ A $ is either $ 0 $ or $ 1 $ ; each element of $ B $ is initially $ 0 $ .

You may perform some operations with matrix $ B $ . During each operation, you choose any submatrix of $ B $ having size $ 2 \times 2 $ , and replace every element in the chosen submatrix with $ 1 $ . In other words, you choose two integers $ x $ and $ y $ such that $ 1 \le x < n $ and $ 1 \le y < m $ , and then set $ B_{x, y} $ , $ B_{x, y + 1} $ , $ B_{x + 1, y} $ and $ B_{x + 1, y + 1} $ to $ 1 $ .

Your goal is to make matrix $ B $ equal to matrix $ A $ . Two matrices $ A $ and $ B $ are equal if and only if every element of matrix $ A $ is equal to the corresponding element of matrix $ B $ .

Is it possible to make these matrices equal? If it is, you have to come up with a sequence of operations that makes $ B $ equal to $ A $ . Note that you don't have to minimize the number of operations.

## 说明/提示

The sequence of operations in the first example:

 $ \begin{matrix} 0 & 0 & 0 & & 1 & 1 & 0 & & 1 & 1 & 1 & & 1 & 1 & 1 \\ 0 & 0 & 0 & \rightarrow & 1 & 1 & 0 & \rightarrow & 1 & 1 & 1 & \rightarrow & 1 & 1 & 1 \\ 0 & 0 & 0 & & 0 & 0 & 0 & & 0 & 0 & 0 & & 0 & 1 & 1 \end{matrix} $

## 样例 #1

### 输入

```
3 3
1 1 1
1 1 1
0 1 1
```

### 输出

```
3
1 1
1 2
2 2
```

## 样例 #2

### 输入

```
3 3
1 0 1
1 0 1
0 0 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 2
0 0
0 0
0 0
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 填充正方形

## 题目描述
给定两个矩阵$A$和$B$。每个矩阵都恰好有$n$行和$m$列。矩阵$A$的每个元素要么是$0$，要么是$1$；矩阵$B$的每个元素初始时为$0$。

你可以对矩阵$B$执行一些操作。在每次操作中，你选择$B$的任意一个大小为$2×2$的子矩阵，并将所选子矩阵中的每个元素替换为$1$。换句话说，你选择两个整数$x$和$y$，使得$1≤x < n$且$1≤y < m$，然后将$B_{x,y}$、$B_{x,y + 1}$、$B_{x + 1,y}$和$B_{x + 1,y + 1}$设置为$1$。

你的目标是使矩阵$B$等于矩阵$A$。当且仅当矩阵$A$的每个元素都等于矩阵$B$的对应元素时，两个矩阵$A$和$B$相等。

是否有可能使这两个矩阵相等？如果可以，你必须想出一系列操作，使$B$等于$A$。注意，你不必最小化操作次数。

## 说明/提示
第一个示例中的操作序列：

$\begin{matrix} 0 & 0 & 0 & & 1 & 1 & 0 & & 1 & 1 & 1 & & 1 & 1 & 1 \\ 0 & 0 & 0 & \rightarrow & 1 & 1 & 0 & \rightarrow & 1 & 1 & 1 & \rightarrow & 1 & 1 & 1 \\ 0 & 0 & 0 & & 0 & 0 & 0 & & 0 & 0 & 0 & & 0 & 1 & 1 \end{matrix}$

## 样例 #1
### 输入
```
3 3
1 1 1
1 1 1
0 1 1
```
### 输出
```
3
1 1
1 2
2 2
```
## 样例 #2
### 输入
```
3 3
1 0 1
1 0 1
0 0 0
```
### 输出
```
-1
```
## 样例 #3
### 输入
```
3 2
0 0
0 0
0 0
```
### 输出
```
0
```

### 算法分类
模拟

### 综合分析与结论
所有题解的核心思路均为利用题目不要求操作次数最少这一条件，对矩阵$A$中所有能进行$2×2$子矩阵操作（即该$2×2$子矩阵内元素全为$1$）的位置进行操作，操作后对比操作结果矩阵与目标矩阵$A$是否一致，一致则输出操作次数与操作位置，不一致则输出$-1$。各题解的主要区别在于代码实现细节，如记录操作位置的方式、判断无解的时机等。

### 所选的题解
- **作者：引领天下 (5星)**
    - **关键亮点**：思路清晰简洁，代码实现直接明了，利用`vector`存储操作位置，整体结构紧凑。
    - **个人心得**：提到自己做题时WA了3次，其中一次是样例WA，暗示做题过程中细节处理的重要性。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int n,m;
    bool a[55][55],b[55][55];
    vector<pair<int,int> > ans;
    int main(){
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)scanf("%d",&a[i][j]);
        for (int i=1;i<n;i++)
        for (int j=1;j<m;j++)if(a[i][j]&&a[i+1][j]&&a[i][j+1]&&a[i+1][j+1])ans.push_back(make_pair(i,j)),b[i][j]=b[i+1][j]=b[i][j+1]=b[i+1][j+1]=1;
        for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)if(b[i][j]^a[i][j])return!printf("-1");
        printf("%d\n",ans.size());
        for (vector<pair<int,int> >::iterator it=ans.begin();it!=ans.end();it++)printf("%d %d\n",it->first,it->second);
    }
    ```
    - **核心代码说明**：读入矩阵$A$后，遍历矩阵$A$中可操作位置进行操作并记录，最后检查操作后的矩阵$B$与$A$是否一致，输出结果。
- **作者：pzc2004 (4星)**
    - **关键亮点**：用变量$s$记录原始矩阵应变为$1$但还没变为$1$的元素数量，在操作过程中实时更新$s$，通过$s$判断是否还有需要操作的位置，逻辑较为严谨。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int n,m,a[55][55],b[55][55],c[55][55],k,x[2505],y[2505],s;
    int main()
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){scanf("%d",&a[i][j]);if(a[i][j]==1){s++;}}
        while(s)
        {
            k++;
            bool bb=0;
            for(int i=1;i<n;i++)
            {
                for(int j=1;j<m;j++)
                {
                    if(a[i][j] && a[i+1][j] && a[i][j+1] && a[i+1][j+1] && b[i][j]==0)
                    {
                        x[k]=i;
                        y[k]=j;
                        b[i][j]=1;
                        if(c[i][j]==0)s--;
                        if(c[i+1][j]==0)s--;
                        if(c[i][j+1]==0)s--;
                        if(c[i+1][j+1]==0)s--;
                        c[i][j]=c[i+1][j]=c[i][j+1]=c[i+1][j+1]=1;
                        bb=1;
                        break;
                    }
                }
                if(bb)break;
            }
            if(!bb){printf("-1");return 0;}
        }
        printf("%d\n",k);
        for(int i=1;i<=k;i++)printf("%d %d\n",x[i],y[i]);
    }
    ```
    - **核心代码说明**：读入矩阵$A$并初始化$s$，通过`while(s)`循环不断寻找可操作位置进行操作并更新$s$，若找不到可操作位置则输出$-1$，最后输出操作次数和操作位置。
- **作者：Stars_visitor_tyw (4星)**
    - **关键亮点**：代码结构清晰，先进行操作记录，再统一判断是否能达到目标矩阵，逻辑连贯。
    ```cpp
    #include<assert.h> 
    #include<ctype.h> 
    #include<errno.h> 
    #include<float.h> 
    #include<math.h> 
    #include<stdio.h> 
    #include<stdlib.h> 
    #include<string.h> 
    #include<time.h> 
    #include<wchar.h> 
    #include<wctype.h>
    #include<algorithm> 
    #include<bitset> 
    #include<cctype> 
    #include<cerrno> 
    #include<clocale> 
    #include<cmath> 
    #include<complex> 
    #include<cstdio> 
    #include<cstdlib> 
    #include<cstring> 
    #include<ctime> 
    #include<deque> 
    #include<exception> 
    #include<fstream> 
    #include<functional> 
    #include<limits> 
    #include<list> 
    #include<map> 
    #include<iomanip> 
    #include<ios> 
    #include<iosfwd>
    #include<iostream> 
    #include<istream> 
    #include<ostream> 
    #include<queue> 
    #include<set> 
    #include<sstream> 
    #include<stack> 
    #include<stdexcept> 
    #include<streambuf> 
    #include<string> 
    #include<utility> 
    #include<vector> 
    #include<cwchar> 
    #include<cwctype>
    using namespace std;
    inline int read()
    {
        int x=0,f=1;
        char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
        while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
        return x*f;
    }
    int a[55][55],b[55][55];
    int ans=0,x[3005],y[3005];
    int n, m;
    int main()
    {
        memset(a,0,sizeof a);
        n=read();
        m=read();
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                b[i][j]=read();
            }
        }
        for(int i=1;i<n;i++)
        {
            for(int j=1;j<m;j++)
            {
                if(b[i][j]&&b[i+1][j]&&b[i][j+1]&&b[i+1][j+1])
                {
                    x[++ans]=i;
                    y[ans]=j;
                    a[i][j]=a[i+1][j]=a[i][j+1]=a[i+1][j+1]=1;
                }
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(a[i][j]!=b[i][j])
                {
                    cout<<-1;
                    return 0; 
                }
            }
        }
        cout<<ans<<endl;
        for(int i=1;i<=ans;i++)
        {
            cout<<x[i]<<' '<<y[i]<<endl;
        }
        return 0;
    }
    ```
    - **核心代码说明**：读入矩阵$B$，遍历可操作位置记录操作并更新矩阵$A$，最后检查矩阵$A$与$B$是否一致，输出结果。

### 最优关键思路或技巧
利用题目不要求操作次数最少这一特性，直接对所有可操作的$2×2$子矩阵进行操作，简化问题求解过程，避免复杂的优化策略。操作过程中合理使用数组或容器记录操作位置，操作完成后通过一次遍历检查结果矩阵与目标矩阵是否一致来判断是否有解。

### 可拓展思路
此类题目可拓展到对不同形状子矩阵的操作，或者对操作次数有更严格限制的情况。对于不同形状子矩阵操作，需重新分析可操作条件和判断无解的条件；对于操作次数限制，可能需要结合动态规划等算法寻找最优解。

### 洛谷相似题目推荐
- [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)：通过给定的变换规则将一个字符串变换成另一个字符串，同样需要考虑操作的可行性与结果判断，与本题判断矩阵能否通过特定操作变换到目标矩阵思路类似。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：对给定的图形进行填充操作，与本题对矩阵进行填充操作有相似之处，都涉及到对区域的操作与判断。
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：在字符串中查找特定单词并统计其出现次数，虽然操作对象是字符串，但在字符串中寻找符合条件的子串与在矩阵中寻找符合条件的子矩阵在思维方式上有一定相似性，都需要遍历并判断条件。

### 个人心得摘录与总结
引领天下提到做题时WA了3次，其中一次是样例WA，反映出即使是看似简单的暴力模拟题，在实现过程中也需注意细节，不能掉以轻心，要认真处理边界条件、逻辑判断等，通过多测试样例来发现问题。 

---
处理用时：122.92秒