# 题目信息

# Maximum Submatrix 2

## 题目描述

You are given a matrix consisting of digits zero and one, its size is $ n×m $ . You are allowed to rearrange its rows. What is the maximum area of the submatrix that only consists of ones and can be obtained in the given problem by the described operations?

Let's assume that the rows of matrix $ a $ are numbered from 1 to $ n $ from top to bottom and the columns are numbered from 1 to $ m $ from left to right. A matrix cell on the intersection of the $ i $ -th row and the $ j $ -th column can be represented as $ (i,j) $ . Formally, a submatrix of matrix $ a $ is a group of four integers $ d,u,l,r $ $ (1<=d<=u<=n; 1<=l<=r<=m) $ . We will assume that the submatrix contains cells $ (i,j) $ $ (d<=i<=u; l<=j<=r) $ . The area of the submatrix is the number of cells it contains.

## 样例 #1

### 输入

```
1 1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2
10
11
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 3
100
011
000
101
```

### 输出

```
2
```

# AI分析结果

### 题目重写
# 最大子矩阵2

## 题目描述
给定一个由数字0和1组成的矩阵，其大小为 $n×m$ 。允许重新排列矩阵的行。通过上述操作，能得到的仅由1组成的子矩阵的最大面积是多少？

假设矩阵 $a$ 的行从上到下从1到 $n$ 编号，列从左到右从1到 $m$ 编号。矩阵中第 $i$ 行和第 $j$ 列交叉处的单元格可以表示为 $(i,j)$ 。形式上，矩阵 $a$ 的子矩阵是一组四个整数 $d,u,l,r$  $(1\leq d\leq u\leq n; 1\leq l\leq r\leq m)$ 。我们认为该子矩阵包含单元格 $(i,j)$  $(d\leq i\leq u; l\leq j\leq r)$ 。子矩阵的面积是它包含的单元格数量。

## 样例 #1
### 输入
```
1 1
1
```
### 输出
```
1
```
## 样例 #2
### 输入
```
2 2
10
11
```
### 输出
```
2
```
## 样例 #3
### 输入
```
4 3
100
011
000
101
```
### 输出
```
2
```

### 算法分类
排序

### 综合分析与结论
所有题解思路核心均是通过预处理每行连续1的数量，利用行可交换的特性，对某列的连续1数量进行排序后计算可能的最大子矩阵面积。不同点在于预处理方式及排序后计算面积的细节。有的题解从右往左预处理，有的从左往右；计算面积时有的正向遍历，有的反向遍历。在优化方面，部分题解提到可优化排序过程以降低时间复杂度。

### 所选的题解
- **作者：localhost (4星)**
  - **关键亮点**：思路清晰，代码简洁，利用预处理数组 `f[i][j]` 记录向右连续1的个数，通过对每列的 `f` 值排序并枚举计算最大子矩阵面积。
  - **重点代码**：
```cpp
int main(){
    in>>n>>m;
    Fur(i,1,n)in>>(a[i]+1);
    Fur(i,1,n)
        Fdr(j,m,1)
        if(a[i][j]==49)f[i][j]=f[i][j+1]+1;

    int ans=0;
    Fur(j,1,m){
        Fur(i,1,n)t[i]=f[i][j];
        sort(t+1,t+n+1);
        Fur(i,1,n)ans=MAX(ans,t[i]*(n-i+1));
    }
    out<<ans<<ln;
}
```
  - **核心实现思想**：先预处理出每个位置向右连续1的个数，然后对每列数据排序，通过遍历排序后的数据计算以该列为边界的最大子矩阵面积。
- **作者：hsy8116 (4星)**
  - **关键亮点**：图文并茂，详细解释思路，从确定矩形一边出发，预处理 `c[i,j]` 表示左侧连续1个数，对每列 `c` 值从小到大排序，通过遍历计算最大子矩阵面积。
  - **重点代码**：
```cpp
int main()
{
    int n, m;
    scanf("%d%d", &n, m);
    for (int i = 1; i <= n; i ++)
    {
        scanf("%s", a[i] + 1);
    }
    for (int i = 1; i <= n; i ++)
    {
        for (int j = 1; j <= m; j ++)
        {
            if (a[i][j] == '1') c[j][i] = c[j - 1][i] + 1;
            else c[j][i] = 0;
        }
    }
    int ans = 0;
    for (int j = 1; j <= m; j ++)
    {
        sort(c[j] + 1, c[j] + n + 1);
        for (int i = 1; i <= n; i ++)
        {
            ans = max(ans, c[j][i] * (n - i + 1));
        }
    }
    cout << ans << endl;
    return 0;
}
```
  - **核心实现思想**：预处理每个位置左侧连续1的个数，对每列的该值排序，遍历排序后的值计算最大子矩阵面积。
- **作者：Erica_N_Contina (4星)**
  - **关键亮点**：思路清晰，通过预处理数组 `f[i,j]` 表示从 `a[i,j]` 开始往后连续1的个数，对每列 `f` 值排序后通过遍历尝试更新答案。
  - **重点代码**：
```cpp
signed main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
        if(a[i][j]=='1')f[i][j]=f[i][j+1]+1;

    int ans=0;
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++)t[i]=f[i][j];
        sort(t+1,t+n+1);
        for(int i=1;i<=n;i++)ans=max(ans,t[i]*(n-i+1));
    }
    printf("%d",ans);
}
```
  - **核心实现思想**：与localhost题解类似，预处理每个位置向后连续1的个数，对每列数据排序后遍历计算最大子矩阵面积。

### 最优关键思路或技巧
通过预处理每个位置连续1的数量，利用行可交换的性质，对某列的连续1数量进行排序，通过遍历排序后的数据计算可能的最大子矩阵面积。这种思路巧妙利用了行交换的条件，简化了问题求解。

### 可拓展之处
同类型题可考虑拓展到三维矩阵，或限制交换次数等情况。类似算法套路可应用于其他需要利用行列特性，通过排序优化计算的矩阵问题。

### 洛谷推荐题目
- [P1169 棋盘制作](https://www.luogu.com.cn/problem/P1169)
- [P2701 小B的询问](https://www.luogu.com.cn/problem/P2701)
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)

### 个人心得摘录与总结
作者SkyRainWind感慨做过类似原题，回忆青春。此类心得体现做题积累的重要性，多做相似类型题目有助于在新题中快速找到思路。 

---
处理用时：61.25秒