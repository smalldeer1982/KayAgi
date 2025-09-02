# 题目信息

# The Very Beautiful Blanket

## 题目描述

Kirill wants to weave the very beautiful blanket consisting of $ n \times m $ of the same size square patches of some colors. He matched some non-negative integer to each color. Thus, in our problem, the blanket can be considered a $ B $ matrix of size $ n \times m $ consisting of non-negative integers.

Kirill considers that the blanket is very beautiful, if for each submatrix $ A $ of size $ 4 \times 4 $ of the matrix $ B $ is true:

- $ A_{11} \oplus A_{12} \oplus A_{21} \oplus A_{22} = A_{33} \oplus A_{34} \oplus A_{43} \oplus A_{44}, $
- $ A_{13} \oplus A_{14} \oplus A_{23} \oplus A_{24} = A_{31} \oplus A_{32} \oplus A_{41} \oplus A_{42}, $

where $ \oplus $ means [bitwise exclusive OR](https://en.wikipedia.org/wiki/Exclusive_or)

Kirill asks you to help her weave a very beautiful blanket, and as colorful as possible!

He gives you two integers $ n $ and $ m $ .

Your task is to generate a matrix $ B $ of size $ n \times m $ , which corresponds to a very beautiful blanket and in which the number of different numbers maximized.

## 说明/提示

In the first test case, there is only 4 submatrix of size $ 4 \times 4 $ . Consider a submatrix whose upper-left corner coincides with the upper-left corner of the matrix $ B $ :

 $  \left[ {\begin{array}{cccc} 9740 & 1549 & 9744 & 1553 \\ 1550 & 1551 & 1554 & 1555 \\ 10252 & 2061 & 10256 & 2065 \\ 2062 & 2063 & 2066 & 2067 \\ \end{array} } \right]  $

 $ 9740 \oplus 1549 \oplus 1550 \oplus 1551 $ $ = $ $ 10256 \oplus 2065 \oplus 2066 \oplus 2067 $ $ = $ $ 8192 $ ;

 $ 10252 \oplus 2061 \oplus 2062 \oplus 2063 $ $ = $ $ 9744 \oplus 1553 \oplus 1554 \oplus 1555 $ $ = $ $ 8192 $ .

So, chosen submatrix fits the condition. Similarly, you can make sure that the other three submatrices also fit the condition.

## 样例 #1

### 输入

```
4
5 5
4 4
4 6
6 6```

### 输出

```
25
9740 1549 9744 1553 9748
1550 1551 1554 1555 1558
10252 2061 10256 2065 10260
2062 2063 2066 2067 2070
10764 2573 10768 2577 10772
16
3108 3109 3112 3113
3110 3111 3114 3115
3620 3621 3624 3625
3622 3623 3626 3627
24
548 549 552 553 556 557
550 551 554 555 558 559
1060 1061 1064 1065 1068 1069
1062 1063 1066 1067 1070 1071
36
25800 25801 25804 25805 25808 25809
25802 4294993099 25806 4294993103 25810 4294993107
26312 26313 26316 26317 26320 26321
26314 4294993611 26318 4294993615 26322 4294993619
26824 26825 26828 26829 26832 26833
26826 4294994123 26830 4294994127 26834 4294994131```

# AI分析结果

### 题目内容翻译
# 非常漂亮的毯子

## 题目描述
基里尔想编织一条非常漂亮的毯子，它由 $n \times m$ 个相同大小的正方形色块组成，每个色块有一种颜色。他为每种颜色都对应了一个非负整数。因此，在我们的问题中，这条毯子可以看作是一个大小为 $n \times m$ 的矩阵 $B$，矩阵元素为非负整数。

基里尔认为，如果矩阵 $B$ 的每个 $4 \times 4$ 子矩阵 $A$ 都满足以下条件，那么这条毯子就非常漂亮：
- $A_{11} \oplus A_{12} \oplus A_{21} \oplus A_{22} = A_{33} \oplus A_{34} \oplus A_{43} \oplus A_{44}$
- $A_{13} \oplus A_{14} \oplus A_{23} \oplus A_{24} = A_{31} \oplus A_{32} \oplus A_{41} \oplus A_{42}$

其中，$\oplus$ 表示[按位异或](https://en.wikipedia.org/wiki/Exclusive_or)。

基里尔请你帮他编织一条尽可能多彩的漂亮毯子。

他给你两个整数 $n$ 和 $m$。

你的任务是生成一个大小为 $n \times m$ 的矩阵 $B$，它对应一条非常漂亮的毯子，并且矩阵中不同数字的数量要尽可能多。

## 说明/提示
在第一个测试用例中，只有 4 个 $4 \times 4$ 的子矩阵。考虑一个左上角与矩阵 $B$ 左上角重合的子矩阵：
$  \left[ {\begin{array}{cccc} 9740 & 1549 & 9744 & 1553 \\ 1550 & 1551 & 1554 & 1555 \\ 10252 & 2061 & 10256 & 2065 \\ 2062 & 2063 & 2066 & 2067 \\ \end{array} } \right]  $

$9740 \oplus 1549 \oplus 1550 \oplus 1551 = 10256 \oplus 2065 \oplus 2066 \oplus 2067 = 8192$；

$10252 \oplus 2061 \oplus 2062 \oplus 2063 = 9744 \oplus 1553 \oplus 1554 \oplus 1555 = 8192$。

所以，所选的子矩阵满足条件。同样，你可以确保其他三个子矩阵也满足条件。

## 样例 #1
### 输入
```
4
5 5
4 4
4 6
6 6
```

### 输出
```
25
9740 1549 9744 1553 9748
1550 1551 1554 1555 1558
10252 2061 10256 2065 10260
2062 2063 2066 2067 2070
10764 2573 10768 2577 10772
16
3108 3109 3112 3113
3110 3111 3114 3115
3620 3621 3624 3625
3622 3623 3626 3627
24
548 549 552 553 556 557
550 551 554 555 558 559
1060 1061 1064 1065 1068 1069
1062 1063 1066 1067 1070 1071
36
25800 25801 25804 25805 25808 25809
25802 4294993099 25806 4294993103 25810 4294993107
26312 26313 26316 26317 26320 26321
26314 4294993611 26318 4294993615 26322 4294993619
26824 26825 26828 26829 26832 26833
26826 4294994123 26830 4294994127 26834 4294994131
```

### 综合分析与结论
这些题解主要围绕构造满足特定异或条件且不同数字尽可能多的 $n \times m$ 矩阵展开。思路上大致分为直接构造、从简单矩阵拓展构造、随机化构造和分治构造几种。
- **算法要点对比**：
    - 六楼溜刘和 I_am_Tangser 都是通过特定公式 $(i \times k) \oplus j$ 直接构造矩阵，其中 $k$ 分别取 $2^9$ 和 $256$，保证了 $2 \times 2$ 子矩阵异或和为 0 且元素互不相同。
    - olegekei 从 $2 \times 2$ 矩阵开始，逐步拓展到 $4 \times 4$、$4 \times m$ 和 $n \times m$ 矩阵，通过设置合适的基数保证元素不重复。
    - hgckythgcfhk 先构造满足所有 $2 \times 2$ 子矩阵异或和为 0 的矩阵，通过复制前两行并或上不同的大数实现。
    - expecto__patronum 采用随机化方法，随机第一行和第一列以及目标异或和，递推计算矩阵元素，直到满足元素互不相同。
    - LJY_ljy 按二进制位考虑，构造满足条件的 $4 \times 4$ 矩阵，再通过分治构造 $256 \times 256$ 矩阵，取左上角 $n \times m$ 子矩阵。
- **难点解决对比**：
    - 直接构造法关键在于找到合适的系数，避免二进制位相交导致元素重复和异或和不满足条件。
    - 拓展构造法要保证每次拓展后的矩阵仍满足条件且元素不重复，需要合理设置基数。
    - 随机化方法需要处理好随机范围和重复元素的判断。
    - 分治构造法要确定好分治的规则和边界条件。

### 所选题解
- **六楼溜刘（5星）**：
    - **关键亮点**：思路清晰，代码简洁，通过简单的公式 $(i \times 2^9) \oplus j$ 直接构造矩阵，并且给出了详细的正确性证明。
    - **核心代码**：
```cpp
#include<cstdio>
int t,n,m;
signed main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m);
        printf("%d\n",n*m);
        for(int i=1;i<=n;i++,puts(""))
            for(int j=1;j<=m;j++)
                printf("%d ",(i<<9)^(j));
    }
}
```
- **LJY_ljy（4星）**：
    - **关键亮点**：从二进制位角度思考，通过分治构造矩阵，思路独特。
    - **个人心得**：2023 年 3 月开始思考此题未做出，2024 年 3 月在考场上突然开窍，说明题目思考久了可能陷入困境，适当放置后可能会有新思路。
    - **核心代码**：
```cpp
const int MAXN = 310;
int a[MAXN][MAXN];
void dfs(int i, int j, int step) {
    if (step == 0) return;
    for (int u = 0; u <= 3; u++) {
        for (int v = 0; v <= 3; v++) {
            a[i + u * step][j + v * step] = a[i][j] + step * step * (u * 4 + v);
            dfs(i + u * step, j + v * step, step / 4);
        }
    }
}
int main() {
    dfs(1, 1, 64);
    int u; scanf("%d", &u);
    while (u--) {
        int n, m; scanf("%d %d", &n, &m);
        printf("%d\n", n * m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++)
                printf("%d ", a[i][j]);
            printf("\n");
        }
    }
    return 0;
}   
```
- **I_am_Tangser（4星）**：
    - **关键亮点**：思路简洁，通过确定合适的系数 $a$ 和 $b$ 构造矩阵，避免二进制位相交。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;
        cout<<n*m<<"\n";
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)cout<<((i*256)^j)<<" ";
            cout<<"\n";
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
- 从简单情况入手，如先考虑 $2 \times 2$ 或 $4 \times 4$ 矩阵，再逐步拓展到更大的矩阵。
- 利用二进制位的特性，通过合适的系数避免二进制位相交，保证元素不重复和异或和满足条件。
- 采用分治思想，将大问题分解为小问题，逐步构造出满足条件的矩阵。

### 可拓展之处
同类型题可能会改变矩阵大小和异或条件，或者要求满足更多的约束条件。类似算法套路包括从简单情况递推、利用二进制性质构造、随机化求解等。

### 洛谷相似题目推荐
- P1216 [USACO1.5] 数字三角形 Number Triangles
- P1002 [NOIP2002 普及组] 过河卒
- P1044 [NOIP2003 普及组] 栈

---
处理用时：55.82秒