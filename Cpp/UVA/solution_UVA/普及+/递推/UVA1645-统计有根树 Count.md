# 统计有根树 Count

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4520

[PDF](https://uva.onlinejudge.org/external/16/p1645.pdf)

# 题解

## 作者：Hisaishi_Kanade (赞：2)

找递推式。

设 $f_i$ 为 $i$ 个节点的满足要求的树的数量，由于同一深度下每个节点子树相同，那么也就是说，根节点的若干个儿子都要分到同样的节点数。

设总共有 $m$ 个儿子，显然这些儿子要分 $n-1$ 个节点（扣掉根节点），至于这些子树中的分配就交给这些儿子做。

则有递推式 $f_i=\sum f_j$，$j$ 要为 $n-1$ 的因子。

你也可以把他理解成动态规划方程。**注意边界条件** $f_1=1$

接下来直接敲代码。

```cpp
#include <stdio.h>
int f[10005];
const int maxn=10000,mod=1000000007;
int main()
{

	int i,j,n,id(1);
	f[1]=1;
	for(i=2;i<=maxn;++i)
	{
		for(j=1;j<i;++j)
		{
			if((i-1)%j==0)
			{
				(f[i]+=f[j])%=mod;
			}
		}
	}
	while(~scanf("%d",&n))
	{
		printf("Case %d: %d\n",id++,f[n]);
	}
	return 0;
}
```

但是此题 $n\le 1000$，这个 $n^2$ 的代码可以通过。

那如果 $n\le10^5$ 呢？

回顾上面的代码，我们发现分解时的 $O(n)$ 复杂度可以再度优化。

```cpp
#include <stdio.h>
int f[10005];
const int maxn=10000,mod=1000000007;
int main()
{
	int n,i,j,mid,id(1);
	f[1]=1;
	for(i=2;i<=maxn;++i)
	{
		mid=i-1;
		for(j=1;j*j<mid;++j)
		{
			if(mid%j==0)
			{
				(f[i]+=f[j])%=mod;
				(f[i]+=f[mid/j])%=mod;
			}
		}
		if(j*j==mid)
		{
			(f[i]+=f[j])%=mod;
		}
	}
	while(~scanf("%d",&n))
	{
		printf("Case %d: %d\n",id++,f[n]);
	}
	return 0;
}
```

按照如上的写法，复杂度降为 $n\sqrt n$，即使 $n\le 10^5$ 也不虚。

如果预处理 $n$ 以内的质数，复杂度还能再降一点。

---

## 作者：MARSandEARTH (赞：1)

## 1－题意
对于给定的 $n(n\le 10^3)$，求出有多少无标号有根树满足相同深度的节点有相同数量的子节点。

对于每组数据，输出 $\texttt{Case X: Y}$。

$X$ 是这组数据的编号（从 $1$ 开始），$Y$ 是求得的答案。
## 2－分析
首先发现其可以递推，不妨设 $f_i$ 为树有 $i$ 个节点时的方案数。

显然可得：$f_n=\sum\limits_{d\mid n-1}f_d$

于是我们 $O(n)$ 预处理后 $O(1)$ 查询即可。

总时间复杂度 $O(n+T)$。

---

## 作者：昤昽 (赞：1)

# [Count](https://www.luogu.org/problemnew/show/UVA1645)

题目中说"同一深度的结点的字结点个数相同",这其实是在说**"每一个结点的每一棵子树都完全相同"**.  

一共有 $n$个结点,除去根结点还剩$(n-1)$个,则设根结点有$m$棵子树,$m$成立当且仅当$ (n-1)\%m==0 $

因此可以得到递推公式:  
$$ f_n=\sum_m^{n-1}f_{\frac{n-1}{m}},(n-1)\%m==0$$  
递推边界:
$$f_1=1$$ 

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int MAXN=1e4+1,MOD=1e9+7;
int f[MAXN];
int main()
{
    int n,cnt=0;
    f[1]=1;
    for(n=2;n<=1000;n++)
        for(int m=1;m<=n-1;m++)
            if((n-1) % m == 0)
                f[n]=(int)( (long long)(f[n]+f[(n-1)/m]) )%MOD;
    
    while(cin >> n)
    {
        cout << "Case " << ++cnt << ": " << f[n] <<endl;
    }
    return 0;
}

```

**最后,需要注意一下此题的输出格式,经本人亲身实验,正确的输出格式是每行后面都跟着一个换行,包括最后一行.**

~~无力吐槽Uva的输出格式~~

---

## 作者：DerrickLo (赞：0)

设 $dp_{i,j}$ 表示 有 $i$ 个居民，最底层有 $j$ 个居民，那么很容易列出方程

$$dp_{i,j}=\sum_{k|j}dp_{i-j,k}$$

时间复杂度 $O(n^2\sqrt{n})$。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
int n,dp[1005][1005],ans[1005],cnt;
signed main(){
	dp[1][1]=1;
	for(int i=2;i<=1000;i++)for(int j=1;j<i;j++)for(int k=1;k*k<=j;k++){
		if(j%k==0){
			dp[i][j]+=dp[i-j][k],dp[i][j]%=mod;
			if(k*k!=j)dp[i][j]+=dp[i-j][j/k],dp[i][j]%=mod;
		}
	}
	for(int i=1;i<=1000;i++)for(int j=1;j<=i;j++)ans[i]+=dp[i][j],ans[i]%=mod;
	while(cin>>n){
		cout<<"Case "<<++cnt<<": "<<ans[n]<<"\n";
	} 
	return 0;
}
```

---

## 作者：ztytql (赞：0)

## content
输入 $n(n<=1000),$ 统计有多少个 $n$ 个结点的有根树，使得每个深度中所有结点的子结点数相同。

## solution
这道题目我们采用递推~~打表~~的方法来做。

显然除了第一个节点必须被放置为根节点外，还剩 $n-1$ 个节点。那么我们可以将剩下的节点平均分，分完后重复操作，最后求一下和就行了。

$O(n^2)$ 预处理，$O(1)$ 询问，复杂度够了。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007;

int n, db[1010], _case = 1;

void in()
{
    db[1] = 1;
    for (int i = 2 ; i <= 1000 ; i ++)
        for (int j = 1 ; j < i ; j ++)
        {
            if ((i - 1) % j == 0)
				db[i] += db[j];
            db[i] = db[i] % mod;
        }
    return ;
}

int main()
{
    in();
    
    while (scanf("%d", &n) != EOF)
        printf("Case %d: %d\n", _case ++, db[n]);
        
    return 0;
}
```

---

