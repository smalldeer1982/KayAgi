# 题目信息

# Palindromic characteristics

## 题目描述

Palindromic characteristics of string $ s $ with length $ |s| $ is a sequence of $ |s| $ integers, where $ k $ -th number is the total number of non-empty substrings of $ s $ which are $ k $ -palindromes.

A string is $ 1 $ -palindrome if and only if it reads the same backward as forward.

A string is $ k $ -palindrome ( $ k&gt;1 $ ) if and only if:

1. Its left half equals to its right half.
2. Its left and right halfs are non-empty ( $ k-1 $ )-palindromes.

The left half of string $ t $ is its prefix of length $ ⌊|t|/2⌋ $ , and right half — the suffix of the same length. $ ⌊|t|/2⌋ $ denotes the length of string $ t $ divided by $ 2 $ , rounded down.

Note that each substring is counted as many times as it appears in the string. For example, in the string "aaa" the substring "a" appears 3 times.

## 说明/提示

In the first example 1-palindromes are substring «a», «b», «b», «a», «bb», «abba», the substring «bb» is 2-palindrome. There are no 3- and 4-palindromes here.

## 样例 #1

### 输入

```
abba
```

### 输出

```
6 1 0 0 
```

## 样例 #2

### 输入

```
abacaba
```

### 输出

```
12 4 1 0 0 0 0 
```

# AI分析结果

### 题目内容
# 回文特征
## 题目描述
字符串 $s$ 长度为 $|s|$，其回文特征是一个由 $|s|$ 个整数组成的序列，其中第 $k$ 个数是 $s$ 中为 $k$ 阶回文的非空子串的总数。

一个字符串是1阶回文，当且仅当它从前往后读和从后往前读是一样的。

一个字符串是 $k$ 阶回文（$k > 1$），当且仅当：
1. 它的左半部分等于它的右半部分。
2. 它的左半部分和右半部分是非空的 $(k - 1)$ 阶回文。

字符串 $t$ 的左半部分是其长度为 $\lfloor|t|/2\rfloor$ 的前缀，右半部分是相同长度的后缀。$\lfloor|t|/2\rfloor$ 表示字符串 $t$ 的长度除以 2 并向下取整。

注意，每个子串在字符串中出现几次就计算几次。例如，在字符串 "aaa" 中，子串 "a" 出现 3 次。
## 说明/提示
在第一个例子中，1阶回文子串是 "a", "b", "b", "a", "bb", "abba"，子串 "bb" 是2阶回文。这里没有3阶和4阶回文。
## 样例 #1
### 输入
```
abba
```
### 输出
```
6 1 0 0 
```
## 样例 #2
### 输入
```
abacaba
```
### 输出
```
12 4 1 0 0 0 0 
```

### 算法分类
字符串

### 题解综合分析与结论
这些题解主要围绕三种思路展开：
1. **字符串哈希**：暴力枚举子串，通过哈希判断子串两边是否符合回文条件，时间复杂度为 $O(n^2 \log n)$，此方法简单直接，但效率较低，适用于数据范围较小的情况。
2. **动态规划**：定义 $dp[i][j]$ 表示 $s[i...j]$ 的回文阶数，通过判断 $s[i]$ 与 $s[j]$ 以及 $dp[i + 1][j - 1]$ 的值来进行状态转移，最后通过前缀和得到结果，时间复杂度为 $O(n^2)$，能处理 $n \leq 5000$ 的数据规模。
3. **回文自动机（PAM）**：构建回文自动机，计算每个节点的出现次数 $cnt[p]$、长度小于 $len[p]/2$ 的最长回文后缀 $g[p]$ 以及回文串 $p$ 的阶数 $f[p]$，通过特定转移方程得到 $f[p]$，最后对结果数组求后缀和得到答案，时间复杂度为 $O(n)$，适用于较大数据范围如 $|s| \leq 5000000$ 的情况。

不同题解的难点主要在于如何高效地判断回文以及处理不同阶回文之间的关系。字符串哈希难点在于哈希函数的设计与运用；动态规划难点在于状态转移方程的推导；回文自动机难点在于其原理理解与实现，包括节点信息计算与转移方程运用。

### 所选的题解
#### 作者：xzggzh1 (5星)
- **关键亮点**：采用简单的二维动态规划解法，针对题目给定的较小数据范围 $n \leq 5000$，思路清晰，代码简洁明了，直接体现核心算法思想。
```cpp
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;++i) dp[i][i]=1,ans[1]++;
    for(int len=2;len<=n;++len)
    for(int i=1,j=i+len-1;i+len-1<=n;++i,ans[dp[i][j]]+=(bool)dp[i][j],j=i+len-1)
    if(s[i]!=s[j]||i+1<=j-1&&dp[i+1][j-1]==0) dp[i][j]=0;
    else dp[i][j]=dp[i][i+len/2-1]+1;
    for(int i=n;i>=1;--i) ans[i]+=ans[i+1];
    for(int i=1;i<=n;++i) printf("%d ",ans[i]);
}
```
核心实现思想：先初始化单个字符子串为1阶回文。然后按子串长度遍历，对于每个子串，根据两端字符是否相等以及子串去掉两端字符后的回文阶数判断当前子串回文阶数，若两端字符相等且去掉两端后的子串是回文，则当前子串回文阶数为左半部分子串回文阶数加1。最后通过前缀和统计不同阶回文子串数量。

#### 作者：Ebola (4星)
- **关键亮点**：考虑到数据范围扩大到 $|s| \leq 5000000$ 的情况，使用回文自动机解决问题，详细阐述了回文自动机每个节点信息的计算方法以及状态转移方程，代码完整且注释清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=50010;
char ss[MAXN];
int s[MAXN],n;
int ch[MAXN][26],sz;
int fail[MAXN],lst;
int len[MAXN],cnt[MAXN];
int g[MAXN],f[MAXN];
long long ans[MAXN];

int newnode(int l){len[++sz]=l;return sz;}

void init()
{
    sz=-1;
    n=lst=0;
    newnode(0);
    newnode(-1);
    fail[0]=1;
    s[0]=-1;
}

int find(int p)
{
    while(s[n]!=s[n-len[p]-1]) p=fail[p];
    return p;
}

void insert(int c)
{
    s[++n]=c;
    int cur=find(lst);
    if(!ch[cur][c])
    {
        int now=newnode(len[cur]+2);
        fail[now]=ch[find(fail[cur])][c];
        if(len[now]<=2)
            g[now]=fail[now];
        else
        {
            int p=g[cur];
            while(s[n]!=s[n-len[p]-1]||(len[p]+2)*2>len[now]) p=fail[p];
            g[now]=ch[p][c];
        }
        ch[cur][c]=now;
    }
    lst=ch[cur][c];
    cnt[lst]++;
}

int main()
{
    scanf("%s",ss);
    init();
    int l=strlen(ss);
    for(int i=0;i<l;i++)
        insert(ss[i]-'a');
    for(int i=sz;i>=2;i--)
        cnt[fail[i]]+=cnt[i];
    for(int i=2;i<=sz;i++)
    {
        if(len[i]/2==len[g[i]])
            f[i]=f[g[i]]+1;
        else f[i]=1;
        ans[f[i]]+=cnt[i];
    }
    for(int i=l;i>=1;i--)
        ans[i]+=ans[i+1];
    for(int i=1;i<=l;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
```
核心实现思想：通过回文自动机的插入操作构建回文树，在插入过程中计算每个节点的相关信息。插入完成后，通过沿 $fail$ 树上传计算每个回文子串的出现次数 $cnt$。再根据节点 $len$ 与 $g$ 的关系确定回文阶数 $f$，最后通过后缀和统计不同阶回文子串数量。

#### 作者：Steven_lzx (4星)
- **关键亮点**：提供了多种做法，包括字符串哈希、DP 和 PAM，并对每种做法进行了简要说明，在 PAM 做法中，代码结构清晰，详细实现了回文自动机的各个功能，与 Ebola 的回文自动机做法相互补充。
```cpp
namespace LZX
{
    using namespace std;
    const int MAXN=5000005;
    int s[MAXN],n,ch[MAXN][26],idx,fail[MAXN],last,len[MAXN],cnt[MAXN],g[MAXN],f[MAXN];
    long long ans[MAXN];
    char str[MAXN];
    int s_PAM_newnode(int l)
    {
        len[++idx]=l;
        return idx;
    }
    void s_PAM_clear()
    {
        idx=-1;
        n=last=0;
        s_PAM_newnode(0);
        s_PAM_newnode(-1);
        fail[0]=1;
        s[0]=-1;
        return;
    }
    int s_PAM_getfail(int p)
    {
        while(s[n]^s[n-len[p]-1])
        {
            p=fail[p];
        }
        return p;
    }
    void s_PAM_insert(int awa)
    {
        int p,c,now;
        s[++n]=awa;
        p=s_PAM_getfail(last);
        if(!ch[p][awa])
        {
            c=s_PAM_newnode(len[p]+2);
            fail[c]=ch[s_PAM_getfail(fail[p])][awa];
            if(len[c]<=2)
            {
                g[c]=fail[c];
            }
            else
            {
                now=g[p];
                while(s[n]^s[n-len[now]-1]||(len[now]+2)*2>len[c])
                {
                    now=fail[now];
                }
                g[c]=ch[now][awa];
            }
            ch[p][awa]=c;
        }
        last=ch[p][awa];
        cnt[last]++;
        return;
    }
    int _main()
    {
        int l;
        scanf("%s",str);
        l=strlen(str);
        s_PAM_clear();
        for(int i=0;i<l;i++)
        {
            s_PAM_insert(str[i]-'a');
        }
        for(int i=idx;i>=2;i--)
        {
            cnt[fail[i]]+=cnt[i];
        }
        for(int i=2;i<=idx;i++)
        {
            if(len[i]/2==len[g[i]])
            {
                f[i]=f[g[i]]+1;
            }
            else
            {
                f[i]=1;
            }
            ans[f[i]]+=1ll*cnt[i];
        }
        for(int i=l;i;i--)
        {
            ans[i]+=ans[i+1];
        }
        for(int i=1;i<=l;i++)
        {
            printf("%lld ",ans[i]);
        }
        printf("\n");
        return 0;
    }
}
```
核心实现思想：与 Ebola 的回文自动机实现类似，通过增量法插入字符构建回文自动机，在插入过程中计算节点的 $fail$、$g$ 等信息，插入完成后计算每个回文子串出现次数 $cnt$，根据节点信息确定回文阶数 $f$，最后通过后缀和得到不同阶回文子串数量。

### 最优关键思路或技巧
回文自动机是解决本题大数据规模的高效方法。其核心技巧在于巧妙利用回文串的性质，通过维护节点的 $fail$ 指针找到最长回文后缀，从而高效地构建回文树，同时通过特定方法计算每个回文子串的出现次数以及长度小于一半的最长回文后缀，以此确定回文阶数。这种数据结构和算法的结合，大大优化了时间复杂度，使得能够处理大规模数据。

### 可拓展之处
同类型题目通常围绕回文串的各种变体性质展开，类似算法套路包括利用回文自动机解决与回文子串相关的计数、查找等问题，如求本质不同回文子串数、在各个位置结尾的回文串数等。也可拓展到结合其他算法，如哈希、动态规划等，根据不同数据范围选择最优解法。

### 推荐洛谷题目
1. [P3978 [TJOI2015]弦论](https://www.luogu.com.cn/problem/P3978)：同样涉及字符串子串相关计数问题，可使用后缀自动机或回文自动机解决，与本题在利用特定自动机解决字符串问题上思路相似。
2. [P4555 [国家集训队]最长双回文串](https://www.luogu.com.cn/problem/P4555)：需要通过回文自动机找到最长双回文串，与本题对回文串性质的深入挖掘和运用类似。
3. [P5496 [模板]回文自动机（PAM）](https://www.luogu.com.cn/problem/P5496)：模板题，用于巩固回文自动机的理解与应用，与本题使用回文自动机解决问题的知识点直接相关。

### 个人心得摘录与总结
暂无。 

---
处理用时：104.91秒