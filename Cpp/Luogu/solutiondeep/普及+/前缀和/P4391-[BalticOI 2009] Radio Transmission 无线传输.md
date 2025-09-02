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

这道题要求在给定由某个字符串不断自我连接形成的字符串中，找出这个重复子串的最短长度。多数题解使用KMP算法，部分采用哈希算法，还有暴力解法。
1. **KMP算法思路**：通过求字符串的next数组（最长公共前后缀长度数组），发现答案为字符串长度n减去next[n]。如LYYY题解中，利用next数组找到最大公共前后缀，将字符串按此划分，推出剩余部分即循环子串；lei_yu题解通过整周期和非整周期的例子，直观解释了n - next[n]得到循环子串长度的原理；Caicz题解从next数组规律出发，证明最小循环子串长度x满足next[x]==0，进而推出next[n]==n - x，得到答案为n - next[n]。
2. **哈希算法思路**：Timothy题解通过枚举字符串相同长度L的前缀和后缀，用哈希判断是否相等，若相等则(n - L)可能是循环节；leader_one题解枚举子串长度，用哈希判断整段及末位多出来的部分是否满足循环节条件；rainygame题解通过字符串哈希，枚举s3（s1的前缀），判断s1[L - i + 1... n]是否与s3相等，若相等则s1[1... L - i]可作为s2，更新答案。
3. **暴力算法思路**：oneman233题解暴力枚举前缀长度，检查其是否满足循环节条件，即与循环串长度相同的子串需一样，最后剩下长度小于循环串的部分应与循环串的某个前缀匹配，并用map优化防止TLE。

**题解评分**：
1. **LYYY（5星）**：思路清晰，结合图形详细解释了为什么答案是n - next[n]，代码简洁明了，直接给出AC代码，对next数组的运用讲解透彻。
2. **lei_yu（4星）**：通过整周期和非整周期的具体例子，生动形象地阐述了n - next[n]公式的原理，易于理解，代码实现完整。
3. **Caicz（4星）**：从分析错误思路入手，深入探讨next数组规律，给出严谨证明，得出答案，代码实现正确。

**关键思路与技巧**：利用KMP算法中next数组表示最长公共前后缀长度的特性，将求最小循环子串长度问题转化为求n - next[n]。这种思维方式巧妙地利用了字符串的前后缀关系，通过对next数组的深入理解和运用解决问题。

**相似算法套路**：此类题目常涉及字符串的匹配、循环节查找等问题，KMP算法在解决这类问题上较为高效。类似地，在处理字符串中查找特定模式、判断字符串周期性等问题时，都可考虑KMP算法或基于字符串前后缀关系的思路。

**推荐题目**：
1. **P3375 【模板】KMP字符串匹配**：经典的KMP算法模板题，用于熟悉KMP算法的基本实现。
2. **UVA10298 Power Strings**：与本题类似，求字符串的最小循环节长度，可进一步巩固相关知识点。
3. **P2445 [SDOI2010]魔法猪学院**：涉及字符串匹配与最短路算法结合，锻炼综合运用能力。

**个人心得摘录**：
 - LYYY：刚学KMP算法见到这题没思路，想出后对KMP算法中的next数组有了更深认识。
 - lei_yu：刚学KMP，理解之后感觉对自身有升华。
总结：多位作者通过本题对KMP算法有了更深入的理解和感悟，体会到该算法在解决字符串循环节等问题上的巧妙之处。 

**LYYY题解核心代码**：
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
核心思想：先通过KMP算法求出字符串ss的next数组（即kmp数组），最后输出字符串长度n减去next[n]的值，即为最小循环子串长度。

**lei_yu题解核心代码**：
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
核心思想：同样是利用KMP算法求出字符串s1的next数组（即nex数组），最后用字符串长度size1减去next数组最后一个值，得到最小循环子串长度。

**Caicz题解核心代码**：
```cpp
#include<stdio.h>
#include<iostream>
#include<cstring>
using namespace std;
int n,len,next[1000005];
char s[1000005];

int main()
{
    scanf("%d %s",&n,s+1);
    int t1=0,t2;
    next[0]=t2=-1;
    while(t1<=n)
    {
        if(t2==-1||s[t2+1]==s[t1+1])
            next[++t1]=++t2;
        else
            t2=next[t2];
    }
    printf("%d",n-next[n]);
    return 0;
}
```
核心思想：先利用KMP算法求出字符串s的next数组，基于对next数组规律的推导，得出最小循环子串长度为n - next[n]并输出。 

---
处理用时：37.03秒