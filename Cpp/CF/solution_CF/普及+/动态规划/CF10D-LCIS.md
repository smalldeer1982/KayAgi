# LCIS

## 题目描述

This problem differs from one which was on the online contest.

The sequence $ a_{1},a_{2},...,a_{n} $ is called increasing, if $ a_{i}<a_{i+1} $ for $ i<n $ .

The sequence $ s_{1},s_{2},...,s_{k} $ is called the subsequence of the sequence $ a_{1},a_{2},...,a_{n} $ , if there exist such a set of indexes $ 1<=i_{1}<i_{2}<...<i_{k}<=n $ that $ a_{ij}=s_{j} $ . In other words, the sequence $ s $ can be derived from the sequence $ a $ by crossing out some elements.

You are given two sequences of integer numbers. You are to find their longest common increasing subsequence, i.e. an increasing sequence of maximum length that is the subsequence of both sequences.

## 样例 #1

### 输入

```
7
2 3 1 6 5 4 6
4
1 3 5 6
```

### 输出

```
3
3 5 6 
```

## 样例 #2

### 输入

```
5
1 2 0 2 1
3
1 0 1
```

### 输出

```
2
0 1 
```

# 题解

## 作者：Nishikino_Curtis (赞：13)

对于这类问题我们通常有两种转移方式，一种是以i结尾的数列，另一种是前i个数中选择一些组成的数列。
 
此题中我们选用a数组前i个元素，b数组以j结尾来转移，空间为O(n^2)，时间为O(n^3).

再来说方案：维护一个LICS[i][]，代表以j结尾的LICS方案，每更新一次答案，则将方案也迁移过来。这将额外带来一个O(n)的复杂度，但是对于本题来说足够了，而且转移也相当简明直白。

Code：

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 505
using namespace std;
int n,m,a[maxn],b[maxn],f[maxn][maxn],lics[maxn][maxn],tot[maxn];
int ans,pos;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    cin>>m;
    for(int i=1;i<=m;++i)cin>>b[i];
    f[0][0]=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            if(a[i]!=b[j])f[i][j]=f[i-1][j];
            else {
                f[i][j]=1;tot[j]=1;
                for(int k=1;k<j;++k){
                    if(b[k]<b[j])
                    {
                        if(f[i-1][k]+1>f[i][j]){
                            f[i][j]=f[i-1][k]+1;
                            tot[j]=tot[k]+1;
                            for(int p=1;p<=tot[k];++p)lics[j][p]=lics[k][p];
                        }
                    }
                }
                lics[j][tot[j]]=b[j];
            }
        }
    for(int i=1;i<=m;++i){
        if(f[n][i]>ans)ans=f[n][i],pos=i;
    }
    printf("%d\n",ans);
    for(int i=1;i<=tot[pos];++i)printf("%d ",lics[pos][i]);
    return 0;
}
```

---

## 作者：李若谷 (赞：9)

## O($n^2$)算法

首先本题是最长上升子序列和最长公共子序列的结合。

我们可以设 $f(i,j)$表示前以$b[j]$结尾的，与a数组前i个数匹配的最长公共上升子序列。

先不考虑路劲输出

那么，如果 $a[i] \neq b[j]$，则$f(i,j) = f(i-1,j)$

如果$a[i] = b[j]$，则$f(i,j) = \max(f(i-1,k) + 1 )$

然后我们就可以写出 $O(n^3)$ 做法：
```cpp
for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		if(a[i]==b[j])
		{
			for(int k=0;k<j;k++)
				if(b[k]<a[i])
					f[i][j] = max(f[i][j],f[i-1][k]+1);
		}
		else f[i][j] = f[i-1][j];
```

在上面的代码中，关键的一部分是k这个循环。

这个循环要找的是k从0到j-1中，最大的 $f[i][k]$

但是在循环j的时候，i其实已经是一个定值了。

我们考虑j和j+1时,k循环的变化。

如果j+1的话，k循环会从0-j+1。

并且循环内的状态转移不会变。

所以从j到j+1事实上只是多运行了一个 
```cpp
f[i][j] = max(f[i][j],f[i-1][k]+1);
```
然而，上面的代码中j+1把j循环中的全部都重复循环了一遍，然后再循环了k=j+1的这个。

明显重复了。

我们事实上可以用一个变量来存储前j个最大的$f[i][j]$。

这样直接省去了k这一层循环。

然后我们考虑路劲。

DP问题的路劲其实很简单，只需要记录一下每一个状态是怎么转移过来的就行了。

代码：
```cpp

#include <iostream>
#include <cstdio>
using namespace std;
const int N = 501;
int a[N],b[N];
int f[N][N];
int pre[N][N];
inline int read()
{
	char ch;
	int ans = 0,f = 1;
	ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ans = ans*10 + ch - '0';
		ch = getchar();
	}
	return ans*f;
}
inline void write(int x)
{
	if(x>9) write(x/10);
	putchar(x%10+48);
}
int main()
{
	int n,m;
	int ans = 0;
	n = read();
	for(register int i=1;i<=n;i++) a[i] = read();
	m = read();
	for(register int j=1;j<=m;j++) b[j] = read();
	a[0] = b[0] = -1;
	for(register int i=1;i<=n;i++)
	{
		int val = 0;
		int pos = 0;
		for(register int j=1;j<=m;j++)
		{
			f[i][j] = f[i-1][j];
			pre[i][j] = j;
			if(a[i] == b[j])
			{
				if(f[i][j] < val+1)
				{
					f[i][j] = val + 1;
					pre[i][j] = pos;
				}
			}
			if(b[j] < a[i])
			{
				if(f[i-1][j] > val) 
				{
					val = f[i-1][j];
					pos = j;
				}
			}
		}
	}
	int final;
	for(register int i=1;i<=m;i++)
	{
		if(f[n][i] > ans)
		{
			ans = f[n][i];
			final = i;
		}
	}
	int i = n,j = final;
	write(ans),putchar('\n');
	if(!ans) return 0;
	int path[N],cnt = 0;
	while(i||j)
	{
		// printf("%d ",j);
		if(pre[i][j]!=j)
			path[cnt++] = b[j];
		j = pre[i][j];
		i--;
	}
	for(register int i=cnt-1;i>=0;i--) write(path[i]),putchar(' ');
	return 0;
}
```


---

## 作者：Xx_queue (赞：2)

[博客食用更佳](https://www.cnblogs.com/Xx-queue/p/11712428.html)

题目链接:[https://www.luogu.org/problem/CF10D](https://www.luogu.org/problem/CF10D)

题目大意:本题是LCS和LIS的综合.给出两个序列,长度n,m(n,m<=500),求两个序列的最长公共上升子序列.

分析:先回顾一下LIS,与LCS的状态与方程表示方法,不知道的小伙伴先百度一下;

考虑涉及状态,$F[i][j]$表示两个序列能构成的以$B_j$结尾的LCIS的长度;

方程不难想出(~~其实对我来说还是有难度的~~):

$ F[i][j]= F[i-1][j]\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ if({A_i != B_j})$
$F[i][j]= max \{F[i-1][k] \}+1,0 \leq k < j,b_k < A_i\ \ \ \ if({A_i == B_j})$

这里解释一下这两个方程:

$if(A_i!=B_j)$: $i$之前的以$B_j$结尾的最长公共上升子序列还是原来的那个(因为现在的$A_i$与$B_j$不相等嘛,加入了$A_i$也不能构成新的序列(不公共))，所以长度还是 $F[i-1][j]$ ;

$if(A_i==B_j)$:这时候两者相等了,出现了一个新的公共元素$A_i$,将$A_i$放到原最长公共上升子序列的尾部,看看能不能继续满足上升这一条件,所以我们可以枚举一个$k$,如果$B_k<A_i$,就放进去并加上1。

这里有一个地方要注意:先要初始化$A_0=B_0=-inf$,思考为什么?

如果不初始化一下,你最开始的第一个元素就有可能检测不到而漏掉,所以这里$k$也要从0开始枚举;

不信你可以去试试$k$从1枚举,第二个样例就会WA;

所以剩下的就很容易了!直接$O(n^3)$枚举i,j,k,按照方程来写就over;

最后输出序列时递归地按照转移方程输出,注意一下边界条件;


AC代码:(请理解上述文字后再看代码,请勿直接抄袭)
```cpp
#include <bits/stdc++.h>
#define N (500+5)
using namespace std;
int n,m,Max,x,y;
int a[N],b[N],dp[N][N];
void print_ans(int x,int y){
	if(dp[x][y]==1){
		printf("%d ",b[y]);
		return;
	}
	if(!x||!y) return;
	if(dp[x][y]==dp[x-1][y]){
		print_ans(x-1,y);
		return;
	}
	for(int i=y-1;i>=1;i--){
		if(b[i]<b[y]&&dp[x][y]==dp[x-1][i]+1){
			print_ans(x,i);
			printf("%d ",b[y]);
			return;
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&b[i]);
	}
	a[0]=b[0]=INT_MIN;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]){
				for(int k=0;k<j;k++){
					if(b[k]<a[i]){
						dp[i][j]=max(dp[i][j],dp[i-1][k]+1);
					}
				}
				if(Max<dp[i][j]) Max=dp[i][j],x=i,y=j;
			}
			else{
				dp[i][j]=dp[i-1][j];
			}
		}
	}
	printf("%d\n",Max);
	print_ans(x,y);
	return 0;
}

```

---

## 作者：Hanzire76 (赞：1)

## 思路

LCS和LIS的合体，还是挺有难度的。

设$f[i][j]$为以$B_j$为结尾的LCIS的长度，我们可以得出状态转移方程：

$$f[i][j]=f[i-1][j],(A_i\neq B_j)$$

$$f[i][j]=max{f[i-1][k]}+1,0\leq k<j,B_k<A_i,(A_i=B_j)$$

说明一下：

$(A_i\neq B_j)$ ：$i$之前的以$B_j$结尾的LCIS还是之前那个（因为$A_i$和$B_j$不相等，所以不满足公共这个条件，所以长度不变），so，$f[i][j]=f[i-1][j]$

$(A_i==B_j)$：$A_i$与$B_j$相等，出现了新的**公共元素**，这时，考虑是否满足**上升**这个条件。所以循环$k$，从满足上升条件的之前的最优状态转移过来。

但是呢，这个目前这个$dp$的复杂度是$O(n^3)$的，面对这个数据是已经可以过得了的，但我们可以再进一步优化。

在转移过程中，我们把满足$0\leq k <j,B_k<A_i$的$k$的集合称为$F[i][j]$的决策集合，记作$S(i,j)$。注意到在第二层循环中，$A$的下标$i$是不变的，这意味着$B_k<A_i$是固定的。因此，当变量$j$增加1时，$k$的取值范围从$0\leq k<j$变为$0\leq k<j+1$，即$j$有可能进入新的决策集合。所以呢我们只需要$O(1)$地检查$B_j<A_i$是否满足，因为已经在决策集合中的元素不会删除。

最终我们把时间复杂度优化到了$O(N^2)$

## 代码

整体代码就不放了，因为我的输出也是看了各位大佬的QAQ，就只放优化部分的$dp$吧。

```cpp
for(int i=1;i<=n;i++)
{
	int val=0;
	if(b[0]<a[i]) val=dp[i-1][0];
    for(int j=1;j<=m;j++)
	{
    	if(a[i]==b[j])
		{
            dp[i][j]=val+1;
            if(Max<dp[i][j]) Max=dp[i][j],x=i,y=j;
        }
        else dp[i][j]=dp[i-1][j];
        if(b[j]<a[i]) val=max(val,dp[i-1][j]);
    }
}
```



---

