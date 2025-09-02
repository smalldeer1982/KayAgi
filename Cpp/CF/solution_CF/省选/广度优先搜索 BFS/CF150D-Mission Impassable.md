# Mission Impassable

## 题目描述

Market stalls now have the long-awaited game The Colder Scrools V: Nvodsk. The game turned out to be difficult as hell and most students can't complete the last quest ("We don't go to Nvodsk..."). That threatened winter exams. The rector already started to wonder whether he should postpone the winter exams till April (in fact, he wanted to complete the quest himself). But all of a sudden a stranger appeared at the door of his office. "Good afternoon. My name is Chuck and I solve any problems" — he said.

And here they are sitting side by side but still they can't complete the mission. The thing is, to kill the final boss one should prove one's perfect skills in the art of managing letters. One should be a real magician to do that. And can you imagine what happens when magicians start competing...

But let's put it more formally: you are given a string and a set of integers $ a_{i} $ . You are allowed to choose any substring that is a palindrome and delete it. At that we receive some number of points equal to $ a_{k} $ , where $ k $ is the length of the deleted palindrome. For some $ k $ , $ a_{k}= $ -1, which means that deleting palindrome strings of such length is forbidden. After a substring is deleted, the remaining part "shifts together", that is, at no moment of time the string has gaps. The process is repeated while the string has at least one palindrome substring that can be deleted. All gained points are summed up.

Determine what maximum number of points can be earned.

"Oh" — said Chuck, raising from the chair, — "I used to love deleting palindromes, just like you, but one day I took an arrow in the Knee".

## 说明/提示

In the first sample we cannot delete any substring, so the best result is $ 0 $ . In the second sample we are allowed to delete only those palindromes whose length equals $ 1 $ , thus, if we delete the whole string, we get $ 7 $ points. In the third sample the optimal strategy is: first we delete character c, then string aa, then bb, and the last one aa. At that we get $ 1+3*5=16 $ points.

## 样例 #1

### 输入

```
7
-1 -1 -1 -1 -1 -1 -1
abacaba
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7
1 -1 -1 -1 -1 -1 -1
abacaba
```

### 输出

```
7
```

## 样例 #3

### 输入

```
7
1 5 -1 -1 -1 -1 10
abacaba
```

### 输出

```
16
```

# 题解

## 作者：max67 (赞：5)

## 前言

前几天看的 ducati 大佬的题解不知道为什么突然没掉了。本着人人为我，我为人人（让其他人更好的 he 题），特意写篇题解。

## 题解
首先注意到题目中不能取的长度的权值为 $-1$，为了方便考虑，我们把“不能取”这个条件转化为"取了一定最劣"，即把权值赋为 $- \inf$。

对于这种带区间删除的题目，一般用区间 dp 来考虑。套路的，我们设 $f[l][r]$ 表示区间 $[l,r]$ 内操作的最大贡献。

对于转移，我们考虑这个区间取的最后一个回文串。注意两个字符必须满足他们之间的字符全部被删掉才能选入同一个回文串中。即我们选出的回文串满足以下性质：取回文串中序号最小 $mn$ 和最大的位置 $mx$，满足删掉这个回文串后，区间 $[mn,mx]$ 内的字符全部被删除。

这启示我们再考虑设两个数组辅助转移： $h[l][r]$ 表示删掉区间 $[l,r]$ 的最大贡献，$g[i][j][k]$ 表示在区间 $[l,r]$ 中，已经选出了长度为 $k$ 的回文串，回文串的两端在 $i,j$ 的最大贡献。

注意 $g[i][j][k]$ 的转移大体过程：

* 对于一个回文串，从两边向中间转移。

由于起始条件与枚举的区间 $[l,r]$ 有关，注意到光是每次计算 $f$ 时都须清空 $g$ 数组，复杂度就至少为 $O(n^5)$。

既然如此，那么考虑反其道而行之：对于一个回文串，我们从中间向两边转移。微调一下 $g$ 数组的定义：$g[l][r][k]$ 表示在区间 $[l,r]$ 中，选出长度为 $k$ 的回文串，满足回文串的两个端点在 $l,r$ 的最大贡献。

考虑转移，枚举下面两个相同的字符：

* $g[l][r][k]= \max_{i<j,i,j \in (l,r)}(g[i][j][k]+h[l][i-1]+h[j+1][r])$

但是这个转移是 $n^5$ 的，原因在于一次性同时枚举了两个字符。一个比较 naive 的优化想法是记录当前回文串的未匹配字符在 $l/r$ 上，然后枚举另一个匹配字符。

这里给出一个更简单的方法：观察到我们求的是最大贡献，因此若枚举到的不合法状态的贡献小于等于最大贡献，转移依然是正确的。

我们注意到 $h[l][r]\ge \max_{i\in (l,r]}(h[l][i]+h[i+1][r])$。即对于回文串的相邻两个字符（位置设为 $i,j$），我们把 $h[i][j]$ 拆成 $h[i][k]+h[k+1][j]$ 。因此我们考虑新的状态中可以在原来的回文串的基础上往外删除一些字符。

我们设 $g[l][r][k]$ 表示在区间 $[l,r]$ 中，选出长度为 $k$ 的回文串，满足在 $[l,r]$ 内，除了回文串以外的其他字符都被删除的最大贡献。

那么有：

* $g[l][r][k]=[s[l]=s[r]]\times g[l+1][r-1][k-2]$
* $g[l][r][k]=\max_{i\in [l,r)}(g[l][i][k]+g[i+1][r][0],g[l][i][0]+g[i+1][r][k])$

* $g[l][r][0]=\max_{k>0}(g[l][r][k]+a[k])$

注意到在计算回文串的相邻两个字符的区间贡献时，上面的转移体现为：对于这个区间，枚举划分方案的最大贡献。这与 $h[l][r]$($g[l][r][0]$) 的转移等价，因此是对的。

最后注意到答案是若干个被删除的区间的组合，因此 $f$ 的计算可以搬到最后来进行。且只用计算 $f[1][n]$ 即可。

## 代码

* 实现的时候用 $f$ 表示上文中的 $g$ 数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=155,inf=0x3f3f3f3f;
int n,ans;
int a[N];
char s[N];
int f[N][N][N],dp[N];
signed main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),a[i]=a[i]<0?-inf:a[i];
    memset(f,0xcf,sizeof(f));
    scanf("%s",s+1);
    for(int len=1;len<=n;len++)
        for(int l=1,r=l+len-1;r<=n;l++,r++)
        {
            if(len==1)
            {
                f[l][r][0]=a[1];f[l][r][1]=0;
                f[l+1][l][0]=0;
                continue;
            }
            if(s[l]==s[r])
                for(int k=2;k<=len;k++)
                    f[l][r][k]=max(f[l][r][k],f[l+1][r-1][k-2]);
            for(int k=0;k<=len;k++)
                for(int i=l;i<r;i++)
                    f[l][r][k]=max({f[l][r][k],f[l][i][k]+f[i+1][r][0],f[l][i][0]+f[i+1][r][k]});
            for(int k=1;k<=len;k++)
                f[l][r][0]=max(f[l][r][0],f[l][r][k]+a[k]);
        }
    for(int i=1;i<=n;i++)
    {
        dp[i]=max(dp[i],dp[i-1]);
        for(int j=0;j<i;j++)
            dp[i]=max(dp[i],dp[j]+f[j+1][i][0]);
    }
    printf("%d\n",dp[n]);
    return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：4)

### 题意

> 给定一个字符串，你可以删掉长度为 $i$ 的回文子串，获得 $v_i$ 的积分，$v_i=-1$ 表示不能删除长度为 $i$ 回文子串。删掉之后前后会拼接起来。
> 
> 求最多能得到多少积分。$n\le 150$。

### 题解

删除回文子串，我们想到区间 DP。不妨设 $f_{i,j}$ 表示将区间 $[i,j]$ 全部删完的最大积分。

发现因为删掉之后前后会拼接起来，难以设计转移。我们再设 $g_{i,j,k}$ 表示将区间 $[i,j]$ 删到剩下一个长度为 $k$ 的回文串的最大积分。那么我们有：

$$f_{i,j}=\max_k\{g_{i,j,k}+a_k\}$$
$$g_{i,j,k}=\max([s_i=s_j]g_{i+1,j-1,k-2},\max_{i\le p<j}\{g_{i,p,k}+f_{p+1,j},f_{i,p}+g_{p+1,j,k}\})$$
$$g_{i,j,0}=f_{i,j}$$

显然这样转移包括了所有情况。

那么我们暴力 $O(n^4)$ DP 即可。

最后，答案可以看成若干个不相交的 $f_{i,j}$ 的和。用一个简单的 DP 可以 $O(n^2)$ 求出。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll a[155];
char s[155];
ll f[155][155],g[155][155][155];
ll dp[155];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    scanf("%s",s+1);
    memset(f,-0x3f,sizeof(f));
    memset(g,-0x3f,sizeof(g));
    for(int i=1;i<=n;i++){
        g[i][i][1]=0;
        if(a[1]>=0)f[i][i]=a[1];else f[i][i]=-0x3f3f3f3f3f3f3f3f;
        g[i][i][0]=f[i][i];
    }
    for(int i=1;i<n;i++){
        if(a[1]>=0)g[i][i+1][1]=a[1],f[i][i+1]=a[1]*2;
        else g[i][i+1][1]=f[i][i+1]=-0x3f3f3f3f3f3f3f3f;
        if(s[i]==s[i+1]){
            g[i][i+1][2]=0;
            if(a[2]>=0)f[i][i+1]=max(f[i][i+1],a[2]);
        }
        g[i][i+1][0]=f[i][i+1];
    }
    for(int len=3;len<=n;len++)
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            f[i][j]=-0x3f3f3f3f3f3f3f3f;
            for(int k=1;k<=n;k++){
                if(s[i]==s[j])g[i][j][k]=g[i+1][j-1][k-2];
                else g[i][j][k]=-0x3f3f3f3f3f3f3f3f;
                for(int p=i;p<j;p++)g[i][j][k]=max(g[i][j][k],max(g[i][p][k]+f[p+1][j],f[i][p]+g[p+1][j][k]));
                if(a[k]>=0)f[i][j]=max(f[i][j],g[i][j][k]+a[k]);
            }
            g[i][j][0]=f[i][j];
        }
    dp[0]=0;
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        for(int j=1;j<=i;j++)dp[i]=max(dp[i],dp[j-1]+f[j][i]);
    }
    printf("%lld\n",dp[n]);
    return 0;
}
```

---

## 作者：yinianxingkong (赞：2)

十分困难的 dp 题。

首先容易发现删去的回文子串都是原串的子序列。而要删除这个子序列的前提就是删完夹在中间的区间。这启示我们作区间 dp，设 $f_{l,r}$ 表示 $[l,r]$ 内的最大价值。

显然只有这样转移不了。前面说过，删除子序列的前提是删完。所以 $f$ 的转移要么是留了几个空要么是删完了。留了几个空的转移一定可以拆成两个区间，所以考虑设 $g_{l,r}$ 表示删完 $[l,r]$ 内的最大价值。

显然只有这样还是转移不了。因为不同长度的子序列的贡献不一样。如果可以把最外层的回文子序列单独讨论就可以转移了。这启示我们设 $h_{l,r,k}$ 表示删完 $[l,r]$ 留下长为 $k$ 的回文子序列的最大价值。

对 $h$ 的转移容易想到枚举回文子序列最外层的两个字符转换成子问题，复杂度 $O(n^5)$，无法通过。观察到我们有许多冗余转移，事实上如果不是当前的 $l$ 和 $r$ 作为最外层的话一定可以拆成左右区间的答案。于是复杂度优化成 $O(n^4)$。

应该很清楚了，代码有需求私信。

---

## 作者：tribool4_in (赞：1)

看到区间操作，数据范围 $n \le 150$，考虑区间 dp。

首先你设 $f_{i, j}$ 表示将 $[i, j]$ 区间删完的最大收益。考虑转移，发现由于回文串的特性，难以对于当前区间直接找出最后一次操作最优的位置，因此考虑开一个辅助 dp 转移，设 $g_{i,j,k}$ 表示将 $[i,j]$ 操作到剩余一个长度为 $k$ 的回文串，则显然有 $f_{i,j}=\max(g_{i,j,k}+v_k)$。

考虑 $g$ 的转移，发现有 4 种情况：

1. 将 $[i+1,j-1]$ 内剩余的回文串扩充到 $[i,j]$：
$$g_{i,j,k}\gets g_{i+1,j-1,k-2}\ [s_i=s_j]$$
2. 将 $[i+1,j-1]$ 内剩余的回文串删掉并出现长度为 2 的 $s_is_j$ 的回文串：
$$g_{i,j,2}\gets g_{i+1,j-1,k-2}+v_{k-2}\ [s_i=s_j]$$
3. 将 $p$ 右半边删空，保留左半边的回文串：
$$g_{i,j,k}\gets g_{i,p,k}+f_{p+1,j}$$
4. 与 3 同理：
$$g_{i,j,k}\gets f_{i,p}+g_{p+1,j,k}$$

然后你惊讶的发现这个串不一定删完，可能会删去**若干个**子区间后剩下的删不动了。因此统计答案时使用经典做法统计若干个不交区间的最优方案：

$$dp_i=\max(dp_{i-1},dp_{j-1}+f_{j,i})$$

另外实现上可以将 $v_i=-1$ 的直接置为 $-\inf$。

然后做完了。

代码：

```cpp
for (int i = 1; i <= n; i++) g[i][i][1] = 0, f[i][i] = a[1];
for (int i = 1; i < n; i++) g[i + 1][i][0] = 0;
for (int len = 2; len <= n; len++) {
    for (int i = 1, j = i + len - 1; j <= n; i++, j++) {
        for (int k = 1; k <= len; k++) {
            if (k >= 2 && s[i] == s[j]) chkmax(g[i][j][k], g[i + 1][j - 1][k - 2]), chkmax(g[i][j][2], g[i + 1][j - 1][k - 2] + a[k - 2]);
            for (int l = i; l < j; l++) chkmax(g[i][j][k], max(g[i][l][k] + f[l + 1][j], f[i][l] + g[l + 1][j][k]));
        }
        for (int k = 1; k <= len; k++) {
            chkmax(f[i][j], g[i][j][k] + a[k]);
        }
    }
}
dp[0] = 0;
for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1];
    for (int j = 1; j <= i; j++) dp[i] = max(dp[i], dp[j - 1] + f[j][i]);
}
```

---

## 作者：cmk666 (赞：0)

[题目传送门](/problem/CF150D)

简单区间 dp。

设 $f_{i,j}$ 表示删光 $i\sim j$ 的最大权值，$g_{i,j,k}$ 表示把 $i\sim j$ 删到只剩一个长为 $k$ 的回文串的最大权值，那么：
$$f_{i,j}=\max\{g_{i,j,k}+a_k,f_{i,p}+f_{p+1,j}\}$$
$$g_{i,j,k}=\max\{f_{i,p}+g_{p+1,j,k},g_{i,p,k}+f_{p+1,j},[s_i=s_j]g_{i+1,j-1,k-2}\}$$
边界条件是 $f_{i,i}=g_{i,i,1}=0,g_{i,i,0}=v_1$。

这样就可以 $O(n^4)$ 转移了。

但字符串不一定要删光，于是再设 $h_{i,j}$ 表示删 $i\sim j$ 的**任意多个**的最大权值，有：
$$h_{i,j}=\max\{0,f_{i,j},h_{i,p}+h_{q,j}\}$$
答案即为 $h_{1,n}$。同样可以 $O(n^4)$ 计算。

虽然本题的 $n$ 有 $150$，但常数小且跑不满，很轻松就能过。核心代码如下：
```cpp
constexpr int NINF = -1000114514;
int n, r, a[159], f[159][159], g[159][159][159], h[159][159]; char s[159];
int main()
{
	read(n);
	For(i, 1, n) read(a[i]), a[i] = a[i] == -1 ? NINF : a[i];
	scanf("%s", s + 1);
	For(i, 1, n) For(j, 1, n) f[i][j] = NINF;
	For(i, 1, n) For(j, 1, n) For(k, 0, n) g[i][j][k] = NINF;
	For(i, 1, n) h[i][i] = max(0, a[1]), f[i][i] = g[i][i][0] = a[1], g[i][i][1] = 0;
	For(i, 0, n) f[i + 1][i] = g[i + 1][i][0] = h[i + 1][i] = 0;
	For(len, 2, n) For(l, 1, n + 1 - len)
	{
		r = l + len - 1;
		For(k, 0, len)
		{
			if ( k > 1 && s[l] == s[r] ) g[l][r][k] = g[l + 1][r - 1][k - 2];
			For(p, l + 1, r) g[l][r][k] = max(g[l][r][k], f[l][p - 1] + g[p][r][k]);
			For(p, l, r - 1) g[l][r][k] = max(g[l][r][k], f[p + 1][r] + g[l][p][k]);
			f[l][r] = max(f[l][r], g[l][r][k] + a[k]);
		}
		For(k, l + 1, r) f[l][r] = max(f[l][r], f[l][k - 1] + f[k][r]);
		h[l][r] = max(0, f[l][r]), g[l][r][0] = max(g[l][r][0], f[l][r]);
		For(k, l, r) For(p, k + 1, r)
			h[l][r] = max(h[l][r], h[l][k] + h[p][r]);
	}
	return printf("%d\n", h[1][n]), 0;
}
```

---

