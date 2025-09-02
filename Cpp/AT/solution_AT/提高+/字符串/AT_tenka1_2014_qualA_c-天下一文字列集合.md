# 天下一文字列集合

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2014-quala/tasks/tenka1_2014_qualA_c

 英小文字 (`a`～`z`) と、英小文字 $ 1 $ 文字と一致するワイルドカード (`*`) からなる $ m $ 文字の文字列のパターンが $ n $ 個与えられる。  
 この文字列のパターンは、 $ m $ 文字の英小文字からなる文字列の集合 $ X $ のいずれかの要素に一致するようにように作られたものである。

 集合 $ X $ の要素数の最小値を求めよ、ダイキ君。

## 说明/提示

### 部分点

- $ 1\ ≦\ n\ ≦\ 4 $, $ 1\ ≦\ m\ ≦\ 4 $ の全てのテストケースに正解した場合、部分点として20点が与えられる
- $ 1\ ≦\ n\ ≦\ 14 $, $ 1\ ≦\ m\ ≦\ 10 $ の全てのテストケースに正解した場合、部分点としてさらに30点が与えられる

### Sample Explanation 1

集合 $ X $ の例としては、 ``` axxb oocb ``` がありうる。

## 样例 #1

### 输入

```
5 4
a*x*
*xx*
*x*b
**cb
****```

### 输出

```
2```

# 题解

## 作者：xie_lzh (赞：4)

### 简要题意

给定 $n$ 个长度为 $m$ 的字符串。

字符串中仅包含小写字母和 `∗` 号。

现在你需要求出一个最小的字符串集合满足

1. 该集合中字符串仅由小写字母构成且长度为 $m$。
1. 原来的 $n$ 个字符串都可以与该集合中至少一个字符串匹配，其中 `∗` 号可以匹配任何字符。

输出最小集合的大小并且**输出一个换行符**。

### 简要分析

容易发现 $n$ 十分小，仅有 $14$ 则容易想到 $\Theta(n^2(2^n+m))$ 的状态压缩做法。

具体分析我们发现，集合中的一个字符串能匹配原来的多个字符串当且仅当匹配的这些字符串两两不冲突，实现方面可以简单地预处理任意两个字符串之间是否冲突。

在预处理完之后，直接枚举原来 $n$ 个字符串可以形成的所有集合，再枚举集合内的字符串之间是否冲突，若不冲突则这一个集合可以由一个字符串匹配。

处理完可以由一个字符串匹配的所有集合后，枚举那些不能由一个字符串匹配的集合，尝试拆成两个子集来扩展，这里的复杂度可以做到 $\Theta(3^n)$，即枚举一个集合和他的所有子集，但是其实直接枚举 $2^{2n}$ 个集合也可以过。

下面是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,cnt,ans[1<<15];
bool mat[15][15];
char c[15][N];
bool check(int i,int j)
{
    for(int l=1;l<=m;l++)
        if(c[i][l]!='*'&&c[j][l]!='*'&&c[i][l]!=c[j][l])
            return false;
    return true;
}
bool check2(int st)
{
    for(int i=st;i;i-=1<<__lg(i))
    {
        for(int j=st;j;j-=1<<__lg(j))
        {
            if(__lg(i)!=__lg(j)&&!mat[__lg(i)+1][__lg(j)+1]) return false;
        }
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>c[i]+1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            if(check(i,j)) mat[i][j]=mat[j][i]=1;
        }
    }
    for(int i=1;i<(1<<n);i++)
    {
        if(check2(i)) ans[i]=1;
        else ans[i]=10000;
    }
    for(int i=1;i<(1<<n);i++)
    {
        if(ans[i]==1) continue;
        for(int j=i;j;j=(j-1)&i)
        {
            ans[i]=min(ans[i],ans[j]+ans[i^j]);
        }
    }
    cout<<ans[(1<<n)-1]<<'\n'; //一定要记得换行啊！！！
    return 0;
}
	
```

---

## 作者：AC_love (赞：2)

发现 $n$ 非常小，考虑状压 DP。

容易想到：新字符串集合一定是由原来的字符串集合内部经过一些字符串的合并得到的。

设 $f(i)$ 表示只考虑 $i$ 的二进制位的字符串时，最小集合的大小。

如果 $i$ 的所有字符串可以合并成一个字符串，那么 $f(i) = 1$。

否则我们枚举子集，设 $j \land k = \varnothing, j \lor k = i$，则有：

$$f(i) = \min(f(j) + f(k))$$

现在考虑怎么判断 $i$ 代表的字符串能否合并成一个字符串。

我们可以预处理出字符串两两之间的关系，如果 $i$ 对应的所有字符串都可以两两合并，那么就能，否则不能。

[code](https://atcoder.jp/contests/tenka1-2014-quala/submissions/59634611)

---

