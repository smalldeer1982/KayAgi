# 题目信息

# Subsequence Permutation

## 题目描述

A string $ s $ of length $ n $ , consisting of lowercase letters of the English alphabet, is given.

You must choose some number $ k $ between $ 0 $ and $ n $ . Then, you select $ k $ characters of $ s $ and permute them however you want. In this process, the positions of the other $ n-k $ characters remain unchanged. You have to perform this operation exactly once.

For example, if $ s=\texttt{"andrea"} $ , you can choose the $ k=4 $ characters $ \texttt{"a_d_ea"} $ and permute them into $ \texttt{"d_e_aa"} $ so that after the operation the string becomes $ \texttt{"dneraa"} $ .

Determine the minimum $ k $ so that it is possible to sort $ s $ alphabetically (that is, after the operation its characters appear in alphabetical order).

## 说明/提示

In the first test case, we can choose the $ k=2 $ characters $ \texttt{"_ol"} $ and rearrange them as $ \texttt{"_lo"} $ (so the resulting string is $ \texttt{"llo"} $ ). It is not possible to sort the string choosing strictly less than $ 2 $ characters.

In the second test case, one possible way to sort $ s $ is to consider the $ k=6 $ characters $ \texttt{"_o__force_"} $ and rearrange them as $ \texttt{"_c__efoor_"} $ (so the resulting string is $ \texttt{"ccdeefoors"} $ ). One can show that it is not possible to sort the string choosing strictly less than $ 6 $ characters.

In the third test case, string $ s $ is already sorted (so we can choose $ k=0 $ characters).

In the fourth test case, we can choose all $ k=4 $ characters $ \texttt{"dcba"} $ and reverse the whole string (so the resulting string is $ \texttt{"abcd"} $ ).

## 样例 #1

### 输入

```
4
3
lol
10
codeforces
5
aaaaa
4
dcba```

### 输出

```
2
6
0
4```

# AI分析结果

### 题目内容
# 子序列排列

## 题目描述
给定一个长度为 $n$ 的字符串 $s$，由英文字母的小写字母组成。

你必须在 $0$ 到 $n$ 之间选择某个数 $k$。然后，选择 $s$ 中的 $k$ 个字符，并以任意方式对它们进行排列。在此过程中，其他 $n - k$ 个字符的位置保持不变。你必须恰好执行此操作一次。

例如，如果 $s = \texttt{"andrea"}$，你可以选择 $k = 4$ 个字符 $\texttt{"a_d_ea"}$ 并将它们排列为 $\texttt{"d_e_aa"}$，这样操作后字符串变为 $\texttt{"dneraa"}$。

确定最小的 $k$，使得可以按字母顺序对 $s$ 进行排序（即，操作后其字符按字母顺序出现）。

## 说明/提示
在第一个测试用例中，我们可以选择 $k = 2$ 个字符 $\texttt{"_ol"}$ 并将它们重新排列为 $\texttt{"_lo"}$（所以结果字符串是 $\texttt{"llo"}$）。选择严格少于 $2$ 个字符是无法对字符串进行排序的。

在第二个测试用例中，对 $s$ 进行排序的一种可能方法是考虑 $k = 6$ 个字符 $\texttt{"_o__force_"} $ 并将它们重新排列为 $\texttt{"_c__efoor_"} $（所以结果字符串是 $\texttt{"ccdeefoors"} $）。可以证明选择严格少于 $6$ 个字符是无法对字符串进行排序的。

在第三个测试用例中，字符串 $s$ 已经排序（所以我们可以选择 $k = 0$ 个字符）。

在第四个测试用例中，我们可以选择所有 $k = 4$ 个字符 $\texttt{"dcba"} $ 并反转整个字符串（所以结果字符串是 $\texttt{"abcd"} $）。

## 样例 #1
### 输入
```
4
3
lol
10
codeforces
5
aaaaa
4
dcba
```
### 输出
```
2
6
0
4
```

### 算法分类
排序

### 综合分析与结论
这三道题解思路基本一致，核心都是先对原字符串进行排序，然后将排序后的字符串与原字符串逐字符对比，统计位置发生改变的字符个数，该个数即为所求的最小 $k$ 值。时间复杂度均为 $O(tn\log n)$，其中 $t$ 是测试用例的数量，$n$ 是字符串长度，主要时间消耗在对字符串的排序操作上。

### 所选的题解
#### 作者：Dragonbell_exp (4星)
- **关键亮点**：思路清晰，先阐述题目大意，再逐步分析得出“要输出的 $k$ 就是字符串 $s$ 在排序中位置发生改变的个数”这一结论，代码简洁明了，使用 `sort` 函数对字符串排序后直接对比。
```c
#include<iostream>
#include<algorithm>
using namespace std;
char s[10000];
char e[10000];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int ans=0;
        for(int i=1;i<=n;i++){
            cin>>s[i];
            e[i]=s[i];
        }
        sort(s+1,s+n+1);
        for(int i=1;i<=n;i++){
            if(s[i]!=e[i]){
                ans++;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
核心实现思想：读入字符串并存两份，一份排序后与另一份原字符串对比，不同则计数加一。

#### 作者：断清秋 (4星)
- **关键亮点**：代码结构较为完整，使用了自定义的 `read` 函数读取输入，虽然在本题中不是必要优化，但体现了一定的代码实现能力。同样是先排序后对比统计位置改变字符数。
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    back x*f;
}
char a[1000],b[1000];
ll t,n,m,k;
int main()
{
    cin>>t;
    while(t--)
    {
        int sum=0;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        cin>>n;
        for(ri i=1;i<=n;i++)
        {
            cin>>a[i];
            b[i]=a[i];
        }
        sort(b+1,b+n+1);
        for(ri i=1;i<=n;i++)
            if(a[i]!=b[i])
                sum++;
        cout<<sum<<endl;
    }
    back 0;
}
```
核心实现思想：用 `read` 函数读入数据，将字符串复制两份，一份排序后与原字符串逐字符比较，不同则累加计数。

#### 作者：MikeC (4星)
- **关键亮点**：分析部分简洁明了，直接指出判断原字符串与排序后字符串的差异即可得到答案，代码中把字符转为数字方便判断，不过这在本题中并非关键优化。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char a[51];
int c[51],b[51];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)cin>>a[i],c[i]=a[i]-96,b[i]=c[i];
        int ans=0;
        sort(b+1,b+1+n);
        for(int i=1;i<=n;i++)if(c[i]!=b[i])ans++;
        printf("%d\n",ans);
    }
}
```
核心实现思想：将读入的字符转为数字存两份，一份排序后与另一份对比，不同则答案加一。

### 最优关键思路或技巧
核心思路是利用排序后字符串与原字符串对比的方式来确定需要调整位置的字符数量。这种思路简单直接，利用了排序的特性，将复杂的字符串排列问题转化为简单的字符位置对比问题。

### 拓展
同类型题目通常围绕字符串的排序、字符位置调整、最小操作数等方面展开。类似算法套路是先对目标数据进行排序，然后通过对比原数据与排序后的数据来获取需要的结果，在处理字符串、数组等数据结构时经常用到。

### 洛谷推荐题目
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：通过排序去重统计不同数字个数。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：利用归并排序统计逆序对数量。
- [P2155 [SDOI2008]沙拉公主的困惑](https://www.luogu.com.cn/problem/P2155)：结合数论知识与排序思想解决问题。 

---
处理用时：50.64秒