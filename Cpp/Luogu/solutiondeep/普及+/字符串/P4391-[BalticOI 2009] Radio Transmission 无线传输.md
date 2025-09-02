# 题目信息

# [BalticOI 2009] Radio Transmission 无线传输

## 题目描述

给你一个字符串 $s_1$，它是由某个字符串 $s_2$ 不断自我连接形成的（保证至少重复 $2$ 次）。但是字符串 $s_2$ 是不确定的，现在只想知道它的最短长度是多少。

## 说明/提示

#### 样例输入输出 1 解释
对于样例，我们可以利用 $\texttt{abc}$ 不断自我连接得到 $\texttt{abcabcabcabc}$，读入的 $\texttt{cabcabca}$，是它的子串。

#### 规模与约定
对于全部的测试点，保证 $1\le L \le 10^6$。

## 样例 #1

### 输入

```
8
cabcabca```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
这些题解主要围绕两种算法来解决问题：KMP算法和字符串哈希算法。
 - **KMP算法思路**：通过求解字符串的next数组（最长公共前后缀数组），发现字符串长度n减去next[n]即为最小循环子串的长度。不同题解在阐述此原理时角度略有不同，但核心都是利用最长公共前后缀与最小循环子串之间的关系。
 - **字符串哈希算法思路**：通过枚举前缀长度，利用哈希值判断前缀和后缀是否相等，从而找到最小循环子串长度。此方法相对直观，但需要注意哈希值冲突问题。

在解决难点上，KMP算法题解主要聚焦于理解next数组与最小循环子串的联系，而哈希算法题解则着重于如何优化枚举过程以避免暴力比较带来的高时间复杂度。

综合质量来看，LYYY、lei_yu、功在不舍的题解思路清晰、阐述详细、代码简洁且可读性高，可评为4星及以上。

### 所选4星及以上题解
1. **LYYY（4星）**
    - **关键亮点**：通过详细的图文解释，清晰地阐述了为什么答案是n - next[n]，对next数组的含义和运用讲解透彻，代码简洁明了。
    - **个人心得**：“刚学了KMP算法见到这道题，完全没有思路，但是真的想出来了之后，真的对KMP算法中的next数组有了更深的认识。”
    - **核心代码**：
```cpp
#include<cstdio>
using namespace std;
const int maxn=1111111;
int n,kmp[maxn];//kmp数组即next数组
char ss[maxn];
int main()
{
    scanf("%d%s",&n,ss+1);
    int j=0;
    for(int i=2;i<=n;++i)
    {
        while(j&&ss[i]!=ss[j+1]) j=kmp[j];
        if(ss[i]==ss[j+1]) ++j;
        kmp[i]=j;
    }
    printf("%d",n-kmp[n]);
    return 0;
}
```
    - **核心实现思想**：先通过KMP算法求出next数组，然后直接输出n - kmp[n]作为最小循环子串的长度。
2. **lei_yu（4星）**
    - **关键亮点**：通过具体例子，从整周期和非整周期两种情况，详细且生动地解释了公式N - next[N]的原理，易于理解。
    - **个人心得**：“刚学KMP，理解之后感觉对整个人都升华了。”
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int size1,nex[1000001],j;
char s1[1000001];
int main()
{
    cin>>size1;
    cin>>s1+1;
    j=0;
    for(int i=1;i<=size1;i++)
    {
        if(s1[j+1]!=s1[i+1]&&j>0)j=nex[j];
        if(s1[i+1]==s1[j+1])
            nex[i+1]=++j;
    }
    cout<<size1-nex[size1]<<endl;
}
```
    - **核心实现思想**：同样是利用KMP算法求出next数组，进而得出最小循环子串长度为size1 - nex[size1]。
3. **功在不舍（4星）**
    - **关键亮点**：从理论层面深入剖析了KMP算法，包括Border与周期的关系、Border的传递性、next数组的定义及匹配过程等，最后得出求最小周期等价于求最大Border长度（即next[n]），使读者对KMP算法有更深入的理解。
    - **核心代码**：
```cpp
next[0]=-1;next[1]=0;
for(int i=2;i<=n;i++)
{
    k=next[i-1];
    while(k!=-1&&s[k+1]!=s[i])k=next[k];
    next[i]=k+1;
}
```
```cpp
k=0;
for(int i=1;i<=m;i++)
{
    while(k!=-1&&s[k+1]!=t[i])k=next[k];
    k=k+1;
    if(k==n)js++,printf("%d\n",i-n+1);
}
```
    - **核心实现思想**：前一段代码是求next数组，后一段是利用next数组进行匹配，通过理论分析得出答案为n - next[n]。

### 最优关键思路或技巧
利用KMP算法中next数组与最小循环子串长度的关系是解决本题的关键思路。通过理解next数组代表的最长公共前后缀，能够巧妙地将问题转化为简单的计算，避免了暴力枚举带来的高时间复杂度。

### 同类型题或类似算法套路拓展
同类型题目通常围绕字符串的循环节、最长公共前后缀等问题展开。类似算法套路包括利用KMP算法解决字符串匹配问题，以及通过字符串哈希快速判断字符串的相等关系。

### 洛谷相似知识点题目推荐
 - [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
 - [UVA10298 Power Strings](https://www.luogu.com.cn/problem/UVA10298)
 - [P2445 [SDOI2010]魔法猪学院](https://www.luogu.com.cn/problem/P2445)

### 个人心得摘录与总结
多位作者提到在学习KMP算法后做本题，对KMP算法尤其是next数组有了更深的理解。做题过程是对知识深入理解和掌握的有效途径，通过思考和解决问题，能挖掘算法的本质和应用场景。 

---
处理用时：35.42秒