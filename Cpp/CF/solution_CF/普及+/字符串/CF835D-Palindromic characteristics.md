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

# 题解

## 作者：xzggzh1 (赞：8)

和已有的一篇回文自动机的解法不同，这里给出的是简单的 $n\leq 5000 $ 的解法，做法是 dp。

题意：

给你一个串，让你求出 $k$ 阶回文子串有多少个。其中：

1. 如果一个字串是 $k$ 阶回文，那他一定还是 $k-1$ 阶回文。
2. 如果一个串是 $k$ 阶回文，那么这个串需要满足：它本是是回文的且他的左半部分是 $k-1$ 回文的（如果长度是奇数，则左半部分长度向下取整）。

---

题目中 $n\leq 5000$，直接考虑二维 $dp$ 。

设 $dp[i][j]$ 表示 $s[i...j]$ 的回文阶数，若为 $0$ 则不是回文串。

考虑从 $dp[i+1][j-1]$ 到 $dp[i][j]$ 的转移：

若 $s[i] \not = s[j] $ 或者 $dp[i+1][j-1]=0$ 那么 $dp[i][j]=0$ 。

否则 $dp[i][j]=dp[i][i+(i-j+1)/2-1]+1$ 。（等于左半部分的阶数 $+1$ ）。

知道转移，最后记得搞个前缀和就好了，这里是核心代码。

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

---

## 作者：Ebola (赞：5)

这题的数据范围非常小，因此是可以字符串hash乱搞一波的，但我觉得这样的话，这题就出的一点意义都没有了，为了发挥这题的价值，我们把它当做|s|≤5000000的题目来做

把它开到了这个范围，那肯定就是要线性的做法了，我们考虑使用回文自动机

对于回文自动机上每个结点p，计算其出现的次数cnt[p]，以及长度小于len[p]/2的最长回文后缀g[p]

可以在每次插入完之后对cnt[last]+1，全部插入完了再沿fail树上传，这样可以O(n)求出cnt数组

设f[p]表示回文串p是几阶的，那么我们可以得到如下转移方程：

- f[p]=1  ,  len[p]/2≠len[g[p]]

- f[p]=f[g[p]]+1  ,  len[p]/2=len[g[p]]

转移顺序应该按照点编号递增，因为p总是出现在g[p]后面

那么我们枚举p，让ans[f[p]]+=cnt[p]，由于k阶回文串必定是1~k-1阶回文串，所以我们对ans数组求一遍后缀和就得到了最终答案

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

---

## 作者：Steven_lzx (赞：3)

在 [博客园](https://www.cnblogs.com/2020gyk080/p/16130111.html) 阅读以获得更好的体验。

## 做法一：字符串哈希

暴力枚举子串，Hash 判断两边是否可行，时间复杂度 $O(n^2 \log n)$。

## 做法二：DP

[这篇文章](https://www.luogu.com.cn/blog/xzggzh/solution-cf835d) 写的很清楚。

## 做法三：PAM

当数据范围 $1 \leq |s| \leq 5000000$ 时，前两种方法是过不去的，~~能过去也可以被 Hack~~。所以我们考虑线性的做法，而 PAM 在插入之后上传 $fail$ 树，使 $cnt$ 数组可以 $O(n)$ 求出。

设 $g_p$ 表示长度小于 $\dfrac{len_p}{2}$ 的最长回文后缀，$f_p$ 表示回文串 $\text{p}$ 的阶数，易得以下结论：

$$
\begin{cases}
 f_p=1 & \text{ if } \dfrac{len_p}{2} \neq len_{g_{p}} \\
 f_p=f_{g_{p}}+1 & \text{ otherwise } 
\end{cases}
$$

统计答案时，枚举 $p$，令 $ans_{f_p}+=cnt_p$，最终答案就是对 $ans$ 数组求出后缀和。

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

---

## 作者：我和鱼过不去 (赞：2)

一道很适合练手的回文自动机（PAM）练习题。  
&nbsp;

### 思路 
由回文串的性质得出，若一个回文串 $S$ 有一个长度为 $\left\lfloor\dfrac{|S|}{2}\right\rfloor$ 的回文后缀 $T$ ，则 $S$ 拥有一个的与后缀一致的回文前缀，即 $T$。设 $T$ 的阶数为 $x$，则 $S$ 的阶数为 $x+1$ 。  
根据回文自动机的性质，可以通过 $fail$ 指针找到长度恰好为当前回文串长度一半的回文后缀，则可以得到当前回文串的阶数。  
&nbsp;  
&nbsp;
 
还有几个需要注意的地方：  
1. 有些回文串在母串中多次出现，需要重复计算。处理时可以利用 $fail$ 指针指向当前回文串最长非自身回文后缀的特点，叠加该回文后缀的出现次数（当前回文串出现时，该回文后缀也跟着出现），以计算每个回文串出现的次数；
```cpp
inline void insert(int c,int id)
{
    ......;
    sum[last]++;   //当前回文串出现次数+1
}	
inline void sort()
{
    for(int i=cnt;i>=2;i--)   //利用fail指针往回计算，防止遗漏 
    {
        sum[p[i].fail] += sum[i];
    }
    ......;
}
```  
2. 若当前回文串没有长度恰好为自身一半的回文后缀，则当前回文串的阶数为 $1$ 。
```cpp
for(int i=2;i<=cnt;i++)
{
    int tmp = i;
    while(p[tmp].len*2>p[i].len)  //如果当前回文后缀的长度大于回文串的一半 
    {
        tmp = p[tmp].fail;
    }
    if(p[tmp].len==p[i].len/2)    //回文串长度有奇有偶 
    {
        tot[i] = tot[tmp]+1;      //累加阶数 
    }
    else tot[i] = 1;              //左半部分不为回文串，则阶数为1 
    ans[tot[i]] += sum[i];        //回文串可能多次出现
}
```
3.  
> 一个串如果是 $k$ 阶回文串，它也是 $k-1$ 阶回文串。  

注意用后缀和的方法累加答案。
```cpp
for(int i=len;i>=1;i--)
{
    ans[i] += ans[i+1];
}
```  
&nbsp;  
&nbsp;

## $Code$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=5e4+5;
const int maxm=30;
int n;
int tot[maxn],sum[maxn],ans[maxn];
char str[maxn];
struct node
{
    int fail,len,e[maxm];
};
struct PAM
{
    int cnt = 1,last = 0;
    int s[maxn];
    node p[maxn];
    inline PAM()
    {
        s[0] = '#';
        p[0].fail = 1;
        p[1].len = -1;
    }
    
    inline void insert(int c,int id)
    {
        s[id] = c;
        while(s[id-p[last].len-1]!=s[id]) last = p[last].fail;
        if(!p[last].e[c])
        {
            p[++cnt].len = p[last].len+2;
            int tmp = p[last].fail;
            while(s[id-p[tmp].len-1]!=s[id]) tmp = p[tmp].fail;
            p[cnt].fail = p[tmp].e[c];
            p[last].e[c] = cnt;
        }
        last = p[last].e[c];
        sum[last]++;   //当前回文串出现次数+1
    }
    
    inline void sort()
    {
        for(int i=cnt;i>=2;i--)   //利用fail指针往回计算，防止遗漏 
        {
            sum[p[i].fail] += sum[i];
        }
        for(int i=2;i<=cnt;i++)
        {
            int tmp = i;
            while(p[tmp].len*2>p[i].len)  //如果当前回文后缀的长度大于回文串的一半 
            {
                tmp = p[tmp].fail;
            }
            if(p[tmp].len==p[i].len/2)    //回文串长度有奇有偶 
            {
                tot[i] = tot[tmp]+1;      //累加阶数 
            }
            else tot[i] = 1;              //左半部分不为回文串，则阶数为1 
            ans[tot[i]] += sum[i];        //回文串可能多次出现
        }
    }
} pam;
int main()
{
    scanf("%s",str+1);
    int len = strlen(str+1);
    for(int i=1;i<=len;i++)
    {
        pam.insert(str[i]-'a',i);
    }
    pam.sort();
    for(int i=len;i>=1;i--)
    {
        ans[i] += ans[i+1];   //注意用后缀和的方法累加答案 
    }
    for(int i=1;i<=len;i++)
    {
        printf("%d ",ans[i]);
    } 
    printf("\n");
    return 0;
}
```




---

## 作者：唐一文 (赞：2)

~~因为随机跳题跳到这题发现以前做过[类似的题](https://www.luogu.com.cn/problem/CF7D)就来发题解了~~

## Description

[传送门](https://www.luogu.com.cn/problem/CF835D)

## Solution

这题和 CF7D 基本一样，但是这题是求所有子串的阶级。

因为这题数据范围只有 $5000$，所以枚举从每个位置开始就行了。

接下来就和 CF7D 一样了。

用 $f_{j,i}$ 表示子串 $j\sim i$ 的阶级。

~~读题后~~可以知道：

- 若 $j\sim i$ 不是回文串，那么 $f_{j,i}=0$。

- 若 $j\sim i$ 是回文串，那么 $f_{j,i}=f_{j,\left\lfloor\frac{i}{2}\right\rfloor}+1$。

可以开个桶统计答案，然后就是怎么判断回文串了。

可以用 manacher 或者 哈希 解决，这里用的是 哈希。

注意到每个 $k$ 阶级子串都是 $0\sim k-1$ 阶级子串，所以要做一遍后缀和。

## Code
```cpp
#include<bits/stdc++.h>
#define re register
#define ull unsigned long long
using namespace std;
char c[5005];
ull fac,fro,bac;
/*
fac计算base的幂
fro计算从前往后的哈希值
bac计算从后往前的哈希值
这里是直接推过去的，也可以预处理一遍
*/
int n,dp[5005],ans[5005];
int main(){
  scanf("%s",c),n=strlen(c);
  //注意要把可能影响后面答案的dp清零（也可直接把dp开两维）
  for(re int j=0;j<n;dp[j++]=0){
    fro=bac=0,fac=1;
    for(re int i=j;i<n;++i){
      dp[i]=0,fro=fro*131+c[i],bac=bac+fac*c[i],fac=fac*131;
      fro^bac?0:++ans[dp[i]=dp[(i-j-1>>1)+j]+1];
    }
  }
  for(re int i=n;i;--i)ans[i]+=ans[i+1];//后缀和
  for(re int i=1;i<=n;++i)printf("%d ",ans[i]);
}
```

---

## 作者：向日葵小班 (赞：0)

### 题目大意：

所有串都是“$0$ 阶回文串”。
	
&emsp;&emsp;对 $k≥1$，若串 $S$ 是回文串，且 $S[1:\left\lfloor\|S|/2 \right\rfloor]$（左半边）是 $k-1$ 阶回文串，则称为“$k$ 阶回文串”。

&emsp;&emsp;给出长度为 $n$ 的串 $S$ ,对于 $k=1∼n$求 $S$ 的 $k$ 阶回文子串个数“位置不同的子串视为不同子串”。

$n\le 5\times 10^6$。


------------

### 这题要先学会一种算法：PAM

&emsp;&emsp;PAM，也叫回文自动机。

&emsp;&emsp;回文自动机的每个节点表示原串的一个（本质不同）回文子串。

&emsp;&emsp;转移边表示给当前串左右同时加上某个字符。

&emsp;&emsp;显然，通过这种方法，偶回文串只能到达偶回文串，奇回文串只能到达奇回文串，故有一奇一偶两个根。（奇根指向单字符字符串，为了方便，可将奇根的 $len$ 约定为 $-1$）。

&emsp;&emsp;$fail$ 边指向自己的最长回文后缀。（约定偶根的 $fail$ 指向奇根）


&emsp;&emsp;称从结尾在原串末尾的最长回文子串开始向上跳 $fail$ 得到的链为终止链，其在原串中对应着这样的一系列回文子串。如图

![](https://cdn.luogu.com.cn/upload/image_hosting/e1h1lp4e.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

即原串的所有回文后缀。


### 构造方法：

&emsp;&emsp;采用增量法，每次向串末尾添加一个字符。记为 $x$，考虑加入 $x$ 后的新回文后缀。

#### 引理：
每添加一个字符，至多新增一个新的本质不同的回文串，且是所有回后缀中最长的。

#### 证明：
如图，红色串为最长回文后缀，绿色串为某个较短的回文后缀。

![](https://cdn.luogu.com.cn/upload/image_hosting/go1r2tt9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

根据回文，绿色串必然在之前已经出现过了。

#### 推论：

&emsp;&emsp;本质不同的回文子串(回文自动机的点数)不超过 $|S|$。

&emsp;&emsp;考虑如何找到这个最长的新回文后缀。对于每个新回文后缀，在其两侧去掉一个 $x$，就对应一个旧的回文后缀。

&emsp;&emsp;可以暴力跳旧终止链，并检查对应回文串左侧是否恰好有一个 $x$。

&emsp;&emsp;由于终止链上长度随深度递增，一旦找到一个符合要求的点 $v$，即找到了最长的新回文后缀。

&emsp;&emsp;维护转移边。若 $v$ 已经有 $x$ 出边，则表示该最长回文后缀已经在前面出现过，找出 $v\xrightarrow{x}d$，本次终止链末尾即为 $d$。

&emsp;&emsp;否则，最长回文后缀是全新的，新建点 $u$ 装这个后缀，连一条 $v\xrightarrow{x}u$，且 ```cpp
u.len=v.len+2```。




&emsp;&emsp;维护 $fail$ 边。可以顺着终止链继续找下一个旧的回文后缀 $v^\prime$ 满足左边有一个 $x$。



&emsp;&emsp;新次长回文后缀必然在前面出现过，所以此时 $v^\prime$ 有 $\xrightarrow{x}$ 出边。找出 $x^\prime\xrightarrow{x}y^\prime$,则 ```u.fail=u′```。（若找不到这样的 $v^\prime$则 ```u.fail``` 置为偶根）



&emsp;&emsp;跳终止链的过程中，终止链长度的消长相当于蜗牛爬杆，复杂度均摊 $O(n)$。

#### 回文自动机的经典应用：
	

&emsp;&emsp;求本质不同回文串数。
    
&emsp;&emsp;求在各个位置结尾的回文串数。

&emsp;&emsp;求公共回文串数。


------------
#### 回到这题上，我们来讲讲这个题目的解法：

&emsp;&emsp;建立 PAM。记节点 $u$ 长度不超过 ```u.len/2``` 的最长回文后缀为 ```u.half```。

&emsp;&emsp;构造回文自动机的时，记新产生的点为 $np$，且 $p\xrightarrow{x}np$，那么先找到 ```p.half```，然后向祖先跳直到能产生对应回文后缀为止。此时出边指向的那个点就是 ```u.half```，复杂度证明类似前面对终止链长度变化的分析。

&emsp;&emsp;记 $f[u]$ 表示回文串 $u$ 的阶数，有如下 DP：


```cpp
f[u]=f[u.half]+1 (u.half.len=⌊u.len/2⌋)
f[u]=1           (u.half.len<⌊u.len/2⌋)
     
```


&emsp;&emsp;求出各个回文串的阶数后，乘以出现次数再后缀和即可。




---

## 作者：FutaRimeWoawaSete (赞：0)

准备把这个玩意儿当成回文自动机的模板做，先水一发 $O(n ^ 2 \log n)$ 的解法。          

暴力枚举子串，然后分治使用 $Hash$ 判断左右两边可不可以走，时间复杂度 $O(n ^ 2 \log n)$ 。        

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int Len = 5e3 + 5 , K = 131;
int n,ans[Len];
unsigned long long a[Len][2],b[Len];
unsigned long long Hash_1(int l,int r){return a[r][0] - a[l - 1][0] * (b[r - l + 1]);}
unsigned long long Hash_2(int l,int r){return a[l][1] - a[r + 1][1] * (b[r - l + 1]);}
int Calc(int l,int r)
{
	if(l == r) return 1;
	int len = (r - l + 1);
	if(len % 2 == 1) 
	{
		int mid = (l + r) >> 1;
		if(Hash_1(l , mid - 1) == Hash_2(mid + 1 , r)) return 1 + Calc(l , mid - 1);
		return 0;
	}
	else
	{
		int mid = (l + r) >> 1;
		if(Hash_1(l , mid) == Hash_2(mid + 1 , r)) return 1 + Calc(l , mid);
		return 0;
	}
}
char s[Len];
int main()
{
	scanf("%s",s + 1);
	n = strlen(s + 1);
	b[0] = 1;
	for(int i = 1 ; i <= n ; i ++) 
	{
		a[i][0] = a[i - 1][0] * K + (s[i] - '0');
		b[i] = b[i - 1] * K;
	}
	for(int i = n ; i >= 1 ; i --) a[i][1] = a[i + 1][1] * K + (s[i] - '0');
	for(int i = 1 ; i <= n ; i ++) 
		for(int j = i ; j <= n ; j ++)
		{
			int num = Calc(i , j);if(num < 0) continue;
			ans[num] ++;
		}
	for(int i = n ; i >= 1 ; i --) ans[i] += ans[i + 1]; 
	for(int i = 1 ; i <= n ; i ++) printf("%d ",ans[i]);
	return 0;
}
```

---

