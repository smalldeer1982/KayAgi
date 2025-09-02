# 题目信息

# Say No to Palindromes

## 题目描述

Let's call the string beautiful if it does not contain a substring of length at least $ 2 $ , which is a palindrome. Recall that a palindrome is a string that reads the same way from the first character to the last and from the last character to the first. For example, the strings a, bab, acca, bcabcbacb are palindromes, but the strings ab, abbbaa, cccb are not.

Let's define cost of a string as the minimum number of operations so that the string becomes beautiful, if in one operation it is allowed to change any character of the string to one of the first $ 3 $ letters of the Latin alphabet (in lowercase).

You are given a string $ s $ of length $ n $ , each character of the string is one of the first $ 3 $ letters of the Latin alphabet (in lowercase).

You have to answer $ m $ queries — calculate the cost of the substring of the string $ s $ from $ l_i $ -th to $ r_i $ -th position, inclusive.

## 说明/提示

Consider the queries of the example test.

- in the first query, the substring is baa, which can be changed to bac in one operation;
- in the second query, the substring is baacb, which can be changed to cbacb in two operations;
- in the third query, the substring is cb, which can be left unchanged;
- in the fourth query, the substring is aa, which can be changed to ba in one operation.

## 样例 #1

### 输入

```
5 4
baacb
1 3
1 5
4 5
2 3```

### 输出

```
1
2
0
1```

# AI分析结果

### 题目内容（中文重写）
# 对回文串说不

## 题目描述
如果一个字符串不包含长度至少为 2 的回文子串，我们就称这个字符串是“美丽的”。回顾一下，回文串是指从第一个字符到最后一个字符和从最后一个字符到第一个字符读取方式相同的字符串。例如，字符串 "a"、"bab"、"acca"、"bcabcbacb" 是回文串，但字符串 "ab"、"abbbaa"、"cccb" 不是。

我们将一个字符串的“代价”定义为使该字符串变为“美丽的”所需的最少操作次数，在一次操作中，允许将字符串的任何一个字符修改为前 3 个拉丁字母（小写）中的一个。

给定一个长度为 $n$ 的字符串 $s$，该字符串中的每个字符都是前 3 个拉丁字母（小写）中的一个。

你需要回答 $m$ 个查询，计算字符串 $s$ 从第 $l_i$ 个到第 $r_i$ 个位置（包含两端）的子串的“代价”。

## 说明/提示
考虑样例测试中的查询：
- 在第一个查询中，子串是 "baa"，可以通过一次操作将其修改为 "bac"；
- 在第二个查询中，子串是 "baacb"，可以通过两次操作将其修改为 "cbacb"；
- 在第三个查询中，子串是 "cb"，可以保持不变；
- 在第四个查询中，子串是 "aa"，可以通过一次操作将其修改为 "ba"。

## 样例 #1
### 输入
```
5 4
baacb
1 3
1 5
4 5
2 3
```
### 输出
```
1
2
0
1
```

### 算法分类
前缀和

### 综合分析与结论
这些题解的核心思路都是先分析出满足条件（不包含长度至少为 2 的回文子串）的字符串只能是由 `abc` 的 6 种排列循环构成，然后通过枚举这 6 种排列，利用前缀和来快速计算每个子区间修改为对应排列所需的操作次数，最后取最小值得到答案。

各题解的主要区别在于代码实现细节和变量命名，但整体思路和算法要点一致。难点在于发现满足条件的字符串的规律以及如何利用前缀和优化查询操作。

### 评分较高的题解
- **作者：NXYorz（4星）**
    - **关键亮点**：思路清晰，代码结构简洁，通过自定义 `work` 函数处理每种排列的前缀和计算，易于理解。
    - **核心代码**：
```cpp
void work(char x , char y , char z , int t)
{
    for(int i = 0; i < n; i++)
    {
        sum[t][i + 1] += sum[t][i];
        if(i % 3 == 0 && s[i] != x) sum[t][i + 1]++;
        if(i % 3 == 1 && s[i] != y) sum[t][i + 1]++;
        if(i % 3 == 2 && s[i] != z) sum[t][i + 1]++;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    cin >> s;

    work('a' , 'b' , 'c' , 1);
    work('b' , 'a' , 'c' , 2);
    work('c' , 'a' , 'b' , 3);
    work('c' , 'b' , 'a' , 4);
    work('a' , 'c' , 'b' , 5);
    work('b' , 'c' , 'a' , 6);

    for(int i = 1; i <= m; i++)
    {
        int l , r; scanf("%d%d",&l,&r);
        int ans = 1e9 + 10;
        for(int j = 1; j <= 6; j++)
            ans = min(ans , sum[j][r] - sum[j][l - 1]);
        printf("%d\n",ans);
    }
}
```
核心实现思想：`work` 函数用于计算将原字符串修改为以 `x, y, z` 为循环节的字符串所需的操作次数的前缀和。在 `main` 函数中，调用 `work` 函数 6 次处理 6 种排列，对于每个查询，枚举 6 种排列的前缀和，取最小值作为答案。

- **作者：iMya_nlgau（4星）**
    - **关键亮点**：详细解释了思路，通过预处理模 3 等于 0、1、2 的位置上的不为 `a`、`b`、`c` 的位置的前缀和，实现快速计算答案。
    - **核心代码**：
```cpp
const int maxn=2e5+10;
char str[maxn];
int n,m,a[maxn],s[3][3][maxn];
int c[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
int main(){
    n=read(),m=read();
    scanf("%s",str+1);
    for(int i=1;i<=n;i++) a[i]=str[i]-'a';
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            for(int k=i+1;k<=n;k+=3)
                s[i][j][k]=s[i][j][k+1]=s[i][j][k+2]=s[i][j][k-1]+(a[k]!=j);
    while(m--){
        int l=read(),r=read(),ans=0x3f3f3f3f;
        for(int i=0;i<6;i++){
            int res=0;
            for(int j=0;j<3;j++) res+=s[j][c[i][j]][r]-s[j][c[i][j]][l-1];
            ans=min(ans,res);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
核心实现思想：通过三重循环预处理前缀和数组 `s`，对于每个查询，枚举 6 种排列，计算每种排列下的操作次数，取最小值作为答案。

### 最优关键思路或技巧
- **发现规律**：通过分析不包含回文子串的字符串的性质，发现其只能由 `abc` 的 6 种排列循环构成，从而将问题转化为枚举这 6 种排列并计算操作次数。
- **前缀和优化**：利用前缀和数组记录将原字符串修改为每种排列所需的操作次数，在查询时可以快速计算任意子区间的操作次数，将时间复杂度从 $O(nm)$ 降低到 $O(n + m)$。

### 拓展思路
同类型题或类似算法套路：
- 其他字符串修改问题，如给定一个字符串和一些修改规则，求将其转换为另一种形式的最小操作次数。
- 区间查询问题，通过预处理前缀和或其他数据结构，实现快速查询区间信息。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察前缀和与动态规划思想，求最大子段和。
- [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)：二维前缀和的应用，求最大加权矩形的和。
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)：涉及前缀和与数学计算，通过前缀和优化计算过程。

### 个人心得摘录与总结
- **xujingyu**：最初使用暴力对比字符串与每种排列的方法，在第五个点超时，后来发现重复计算很耗时间，于是加上前缀和优化，解决了超时问题。总结：在处理区间查询问题时，要注意避免重复计算，可考虑使用前缀和等优化方法。 

---
处理用时：109.56秒