# Neko and Aki's Prank

## 题目描述

Neko 正在 Aki 家的后院玩他的玩具。Aki 决定恶作剧一下，偷偷地在 Neko 的玩具里放了猫薄荷。不幸的是，他下手太重，把整袋猫薄荷都倒进了玩具里……

Neko 花了一整天才恢复正常。他向 Aki 报告说，他看到了很多奇怪的东西，包括一个包含所有长度为 $2n$ 的合法括号序列的 [trie](https://en.wikipedia.org/wiki/Trie)。

合法括号序列的定义如下：

- 空序列是合法括号序列；
- 如果 $s$ 是合法括号序列，那么 $(\,s\,)$ 也是合法括号序列；
- 如果 $s$ 和 $t$ 都是合法括号序列，那么 $st$ 也是合法括号序列。

例如，字符串 "(())"、"()()" 是合法括号序列，而 ")(" 和 "((" 不是。

Aki 随后想出了一个有趣的问题：这个 trie 的最大匹配（即没有两个边有公共顶点的最大边集）的大小是多少？由于答案可能很大，请输出答案对 $10^9+7$ 取模后的结果。

## 说明/提示

下图展示了前两个样例的 trie（为清晰起见，圆括号被替换为尖括号）。最大匹配用蓝色高亮显示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1152D/364c839d3a5d6c2987f41486d9a1c09bc9880efd.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1152D/a47292c3f5348a0f5d679fa952fd06c1a21a7fc0.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
```

### 输出

```
9
```

# 题解

## 作者：a2956331800 (赞：16)

先放代码（因为代码太简单了）

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define md 1000000007
using namespace std;

int n,f[2005][2005],ans,i,j;

int main()
{
	cin>>n;
	f[1][1]=1;
	for(i=2;i<=n+1;i++)
		for(j=1;j<=i;j++)
			f[i][j]=(f[i-1][j]+f[i][j-1])%md,(i+j)%2==1?ans=(ans+f[i][j])%md:0;
	cout<<ans;
	return 0;
}
```

就是求

$$f_{i,j}=f_{i-1,j}+f_{i,j-1}$$

$$ans=\sum_{(i+j)\bmod 2=1}f_{i,j}$$

所以这为什么是对的呢？

先来看这样一种**构造选中的边集**的方法：

- 选$trie$树上所有深度为**偶数**的点和其**父节点**的连边（如果有多条边冲突就保留一条）

（把$trie$的根深度视为$0$）

括号序列的长度是$2n$，**偶数**，也就是说$trie$树的**叶子**深度为偶数，按这种方法我们覆盖了所有深度为**奇数**的点，而所有边都连接两个深度奇偶不同的点，所以这样选就得到了最大的边集

- 答案就是$trie$树上深度为**奇数**的点的**个数**

上面那个构造方法的解释顺便解释了这一点

所以只需要求$trie$上深度为奇数的点有几个就行了

- 求上面的那个$f$显然是递推求卡特兰数的一种方法

根据卡特兰数与括号序列的关系（或者把左括号看成$i+=1$，右括号看成$j+=1$）显然可以知道$f_{i,j}$就是有$i$个左括号,$j$个右括号，且是**合法括号序列的前缀**的括号序列的个数。对应到$trie$上就是$f_{i,j}$个点

所以把$i+j\bmod 2=1$的$f_{i,j}$加起来就得到$trie$上深度为奇数的点的个数，也就是答案





---

## 作者：NaCly_Fish (赞：3)


此题有一个推导过程稍微麻烦的 $\Theta(n)$ 做法，个人感觉过程可能有些绕弯路了，也欢迎大家提出更巧妙的方法。

首先我们有一个递推 $f_{i,j}=f_{i-1,j}+f_{i,j-1} \  (j \leq i)$，可惜这个递推式不是对任意位置成立的，这让我们很难受。于是我们可以考虑根据原本的 $f$，在其留空的位置按递推式推出 $g$，看看它长什么样（通常都很好用！）：

```
1   0   -1  -2  -3  -4  -5  
1   1   0   -2  -5  -9  -14 
1   2   2   0   -5  -14 -28 
1   3   5   5   0   -14 -42 
1   4   9   14  14  0   -42 
1   5   14  28  42  42  0   
1   6   20  48  90  132 132 
```
现在得到的这个矩阵，除第一行以外，所有位置都满足 $g_{i,j}=g_{i-1,j}+g_{i,j-1}$ 了，也就是说每一行都可以直接用上一行的前缀和表示。规律也很明显：

$$f_{n,m}=[x^m] \left( \frac{1-2x}{(1-x)^{n+2}} \bmod  x^{n+1}\right)$$
而最终答案是
$$\sum_{i=0}^n \sum_{j=0}^i f_{i,j}[i+j \bmod 2 = 1]$$

其中第 $i$ 行所有数的和很简单，它就是 Catalan 数 $C_{i+1}$。
***
现在重点在于对 $i \in [0,n]$ 求出
$$s_i=\sum_{j=0}^i (-1)^j f_{i,j}=\sum_{j=0}^i[t^j] \frac{1+2t}{(1+t)^{i+2}}= [t^i] \frac{1+2t}{(1+t)^{i+2}(1-t)}$$
写成二元 GF 就是
$$[t^ix^i] \frac{1+2t}{(1-t^2)(1+t-x)}=[u^0] \frac{u+2u^2}{(1-u^2)(-x+u+u^2)}$$
尝试分式分解，原式可以分解为这么一大坨：
$$[u^0]\frac{1}{2-x}\left( \frac{ -1+2x+(1+x)u}{x(1-u^2)}+\frac{x(-1+2x)+(1+x)u}{x(u^2+u-x)}\right)$$
由于左边这部分显然是没有 $u$ 的负次项的，故化简为
$$ \frac{-1+2x}{x(2-x)}+\frac{1}{x(2-x)} \red{[u^0]\frac{x(-1+2x)+(1+x)u}{u^2+u-x}}$$
后面那部分继续大力分解：
$$[u^0]\left( \frac{\alpha + x \beta}{u+\alpha}+\frac{\beta + x \alpha}{u+\beta}\right) $$
$$\alpha = \frac{1-\sqrt{1+4x}}{2} \ , \ \beta = \frac{1+\sqrt{1+4x}}{2}$$
接下来一步很关键，仅凭直觉乱搞很可能会得出错误的结果。我们需要考察分解出的每个分式，是否真的包含 $u^0$ 的项（在先按 $x$ 展开，再按 $u$ 展开的情况下）。

稍加思索我们可以断定 $\frac{1}{u+\alpha}$ 是不包含 $u^0$ 项的（乘上一个只含 $x$ 的幂级数，显然不影响这一性质），直接扔掉即可。这是因为 $\alpha$ 常数项为零，导致：
$$\frac{1}{u+\alpha}=\frac{u^{-1}}{1+\alpha/u}=\sum_{i \geq 0} (-1)^i \alpha^i u^{-i-1}$$
同理也可以验证 $\frac{1}{u+\beta}$ 是包含 $u^0$ 项的，故原本红色的那部分就可以直接写为 $1+x\alpha/\beta$，然后可以化简得到
$$s_i=[x^i] \frac{\alpha / \beta+2}{2-x}=[x^i]\frac{-1+2x+\sqrt{1+4x}}{2x(2-x)}$$
****
于是，答案就可以写为
$$\frac 12\sum_{i=0}^n C_{i+1}-(-1)^is_i$$
到这里就能以 $\Theta(n)$ 的时间复杂度算出答案啦～ 

ps：答案的生成函数显然为代数幂级数，二元的常系数递推得到这样的结果，也是意料之中的。

---

## 作者：2017gangbazi (赞：3)

第二次遇到这个题了,第一次是在字节跳动的一场比赛

~~然后我爆零了~~

没有想到题解里大佬的递推方法555，个人感觉其实是一道不错的记搜题.

![](https://cdn.luogu.com.cn/upload/image_hosting/b6kuhg8a.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图,画出整个$Trie$树之后，发现当 $n=3$ 时问题中有两个 $n=2$ 时的子问题，考虑动态规划。

对于每个节点，以它为根的子树的答案只与
**当前点的左括号比右括号多的个数**和**当前点与它的父节点是否连边**有关。

考虑据此涉及状态。

$ f(n,delta,k)  $   表示“  $ n $ 对括号，此时左括号比右括号多 $ delta $  个，
且与父节点连边情况为 $ k $ (1表示连边，0表示不连）” 时的方案总数。

考虑转移.

$ n==delta $ 时，

$ f(n,delta,0) =max(f(n-1,delta-1,1)+1,f(n-1,delta-1,0)) $ 

$ f(n,delta,1) =f(n-1,delta-1,0) $

$ n>delta $ 时，

$ f(n,delta,1) =f(n,delta+1,0)+f(n-1,delta-1,0)$

$
f(n,delta,0) =\begin{cases}
f(n,delta,1)\\
1+f(n,delta+1,1)+f(n-1,delta-1,0)\\
1+f(n-1,delta-1,1)+f(n,delta+1,0)\\
\end{cases}
$

采用**记忆化搜索**即可。

```cpp
int f(int n,int delta,bool is) {
	if(!n)return 0;
	
	if(dp[n][delta][is]!=-1)return dp[n][delta][is];
	
	int &p=dp[n][delta][is];
	
	if(n==delta) {
		if(is)return p=(f(n-1,delta-1,0));
		else return p=max(f(n-1,delta-1,1)+1,f(n-1,delta-1,0));
	} else {
		if(!delta) {
			p=max(f(n,delta+1,0),is?0:(f(n,delta+1,1)+1));
			return p;
		} else {
			p=f(n,delta+1,0)+f(n-1,delta-1,0);
			if(!is) {
				p=max(p,1+f(n,delta+1,1)+f(n-1,delta-1,0));
				p=max(p,f(n,delta+1,0)+f(n-1,delta-1,1)+1);
			}
			return p;
		}
	}
}
```
最终答案即为 $ max(f(n,0,0),f(n,0,1)) $。



---

## 作者：shiroi (赞：3)



### Description

有一个由所有长为 $2n$ 的合法括号序列组成的 $\text{Trie}$ ，求 $\text{Trie}$ 树上最大匹配的大小。




### Solution

观察题目可以发现，题目中的最大匹配即为所有深度为奇数的点的数量。

定义 $\text{Trie}$ 树上根节点的深度为 $0$ 。 $\text{Trie}$ 树在构造时，对每个深度为奇数的点任选其下方的一条边。

求解时对所有前缀进行dp。设 $f(i, j)$ 表示有 $i$ 个左括号，$j$ 个右括号的前缀数量。转移方程为 $f(i, j) = f(i - 1, j) + f(i, j - 1)$ 。之后可以直接求解。

代码实现相对简单，需要注意取模。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0,f=1,c=getchar();
	while(c<48) c=='-'&&(f=-1),c=getchar();
	while(c>47) x=x*10+c-'0',c=getchar();
	return x*f;
}

const int MOD = 1e9+7;
const int MAXN = 1005;
int f[MAXN][MAXN],n,ans;

int main(int argc, char const *argv[])
{
	n=read(); f[0][0]=1;
	for(int i=1; i<=n; i++)
	{
		for(int j=0; j<=i; j++)
		{
			f[i][j]=(f[i-1][j]+f[i][j-1])%MOD;
			if((i+j)&1) (ans+=f[i][j])%=MOD;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```





---

## 作者：hpbl (赞：3)

这题看起来好难啊qvq

细看一看样例解释，你会发现其实应该是从第一层边开始，每层尽量选多一点边。结果就是这样了。

证明：

我们设我们第$i$层选了$a_i$条边，深度为$i$的节点有$b_i$个（根深为$0$)。

那么一定有$a_{i-1}+a_i \le b_i$

即$\begin{cases} a_1+a_2\le b_1 \\ a_2+a_3 \le b_2 \\ \cdots \\ a_{2n-1}+a_{2n}\le b_{2n-1}  \end{cases}$

相加得$\sum_{i=1}^{2n}a_i \le \frac{\sum_{i=1}^{2n-1}b_i+a_1+a_{2n}}{2} $

很明显我们要尽量让这些等号取等，因此我们先让所有数取最大值$(a_1 \le 1)$

如果我们让$a_1$变小$1$，这样我们可以改变$a_1,a_2,\cdots,a_k$的值

此时$a_2$会变大$1$，$a_3$会减小$1$，以此类推，最后$a_{k}$会变大$(-1)^k$

然后$\sum_{i=1}^{k}a_i$就会变小$[k \ mod \ 2==0]$

因此它不会变大

所以不如让$a_1$取最大值

然后后面的也取最大值

即$\begin{cases} a_1=1 \\ a_2=b_1-a_2 \\ a_3=b_2-a_2 \\ \cdots \\ a_{2n}=b_{2n-1}-a_{2n-1} \end{cases}$

剩下来就是怎么求$b_i$

一遍dp就行了

我们把括号序列中的$($当成$1$,$)$当成$-1$

那么这个序列的每个前缀和$s_i$满足:

$0 \le s_i \le min(i,2n-i),i \equiv s_i(mod \ 2) $

设前$i$个数的前缀和为$j$的情况数为$f_{i,j}$

若$j > 0$，你这一步可能是$($，因此$f_{i,j}+=f_{i-1,j-1}$

若$j < min(i-1,2n-i+1)$，你这一步可能是$)$，因此$f_{i,j}+=f_{i-1,j+1}$

因此$b_i=\sum_{j=0}^{min(i,2n-i)}f_{i,j}$

剩下的就不成问题了吧

代码中我是下标倒过来dp的，问题不大

记得取模~~（我忘了取模结果调了35min才发现这里挂了）

Code:
```cpp
#include<cstdio>
#include<cstdlib>
using namespace std;
const int mod=1e9+7; 
int n,f[2001][1001],ans,t,lst;
int main()
{
    scanf("%d",&n);
    f[2*n][0]=1;
    for(int i=2*n-1;i>=0;i--)
        for(int j=i&1;j<=i&&j<=2*n-i;j+=2)
            f[i][j]=((j<2*n-i-1?f[i+1][j+1]:0)+(j!=0?f[i+1][j-1]:0))%mod;
    for(int i=2*n;i;i--)
    {
        t=0;
        for(int j=0;j<=i&&j<=2*n-i;j++) t=(t+f[i][j])%mod;
        lst=(t-lst+mod)%mod;
        ans=(ans+lst)%mod;
    }
    printf("%d",ans);
}
```



---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1152D)

&nbsp;

### 题目大意：
有一个由所有长为 $2n$ 的合法括号序列组成的`trie`，求最多能从树上选取多少条边，使得任意两条边都没有公共端点。输出这个数模 $10^9+7$ 的值。

&nbsp;

### 解题思路：
首先考虑如何选边最优，不难发现对于每一次选边，必然连接一个深度为奇数的点和深度为偶数的点，设深度为奇数的点的个数为 $odd$，偶数深度的点为 $even$，则在最佳理想状况下，遍数必然为 $\min(odd,even)$，而由于合法括号序列长度为偶数，则奇数深度点个数必然小于偶数深度点个数（ 我们定义根的深度为 $0$ ）。

于是问题便转化为了求 $trie$ 数上深度为奇数的点的个数。尝试用 `dp` 求解，我们定义 $dp[i][j]$ 为有 $i$ 个左括号， $j$ 个右括号的括号序列个数，同时保证 $i\ge j$，这样一来这个括号序列便一定是 `trie` 树上的某一点，然后对于 $i+j$ 为奇数的状态，统计它们的和即可，显然的，这些状态中所包含的括号序列显然都是树上深度为 $i$ 的点。

转移方程比较好想，为 $dp[i][j]=(dp[i-1][j]+dp[i][j-1])\bmod$ $10^9+7$。

最后输出统计的和即可。

代码如下：
```cpp
int main(){
	scanf("%d",&n);
	
	ll ans=0;
	dp[1][1]=1;
	for(int i=2;i<=n+1;i++){
		for(int j=1;j<=i;j++){
			dp[i][j]=(dp[i-1][j]+dp[i][j-1])%mod;
			if((i+j)%2==1) ans=(ans+dp[i][j])%mod;
		}
	} 
	printf("%lld",ans);
	return 0;
}
```

显然的，转移方程只和 $i$ 与 $i-1$ 有关，所以可以滚动数组，省掉第一维，代码与上面的类似，这里不再赘述。

完结撒花 OvO！！！

---

## 作者：End1essSummer (赞：0)

通过手模第三个样例，可以发现能选到的最多的边数等于在字典树上奇数层（根节点不算）的点的数量总和。

接下来尝试证明。在树上，每层的点的数量一定都小于等于下一层点的数量。那么现在考虑从中抽出来相邻两层（除了根节点）的话，那么能选到最大边数就是其中点数最小的层（被抽出来的第一层）。

如果是四层的话，那么能选到的最大边数就应当是其中的第一层与第三层点的个数。

以此类推，有 $n$ 层时就会是其中奇数层点的个数。

所以只需要递推求出每层点的个数，并把奇数层的点数加起来。

关于如何递推：

假设现在我们有状态 $dp_{i,j}$ 定义为由 $i$ 个左括号与 $j$ 个右括号组成的合法序列个数，容易发现：

  1. $j \leq i$

  2. $dp_{i,j}$ 只可以从 $dp_{i-1,j}$，$dp_{i,j-1}$ 转移过来，意义就是在它们右边新插上一个左括号或者右括号。
  
  在题目建出来的字典树中，以第 $i$ 层结尾的括号序列长度为 $i$，也就是说第 $i$ 层点的个数就是：
  
  $$sum_i=∑_{j=0}^{j\leq \frac{i}{2}} dp_{i-j,j}$$


代码简单的令人害怕。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,dp[1010][1010],sum[2010],ans=0;
const int mod=1e9+7;
signed main(){
    cin>>n;
    dp[0][0]=1;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=i;j++){
            if(j<i){
                dp[i][j+1]=(dp[i][j+1]+dp[i][j])%mod;
            }dp[i+1][j]=(dp[i+1][j]+dp[i][j])%mod;
        }
    }for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            sum[i+j]=(dp[i][j]+sum[i+j])%mod;
        }
    }for(int i=1;i<=n*2;i++){
        if(i&1){
            ans=(ans+sum[i])%mod;
        }//cout<<sum[i]<<'\n';
    }cout<<ans<<'\n';
}
```

---

## 作者：james1BadCreeper (赞：0)

我们来看 $n=3$ 时候的 Trie 树：

![](https://pic.imgdb.cn/item/63b82f20be43e0d30e5926ec.png)

实际上我们只需要贪心地选择边即可选到最大值，原因很简单，不选择这一条而选择下一条并不会使贡献变大。

可以发现，所有深度为偶数的节点都会连接一条边，所以现在的问题成了求深度为偶数的节点的个数。

设 $f(i,j)$ 代表有 $i$ 个左括号，$j$ 个右括号在 Trie 上能形成的括号序列个数。初始 $f(0,0)$，转移时，可以选择添加一个左括号或者右括号，只需要满足 $j\le i$，因此 $f(i,j)=f(i-1,j)+f(i,j-1)$。当 $i+j$ 为偶数时，这个节点在 Trie 上的深度也是偶数，加起来就是答案。


```cpp
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 1000000007;

int n, ans;
int f[1005][1005];

int main(void) {
    scanf("%d", &n);
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        f[i][0] = 1;
        for (int j = 1; j <= i; ++j) 
            f[i][j] = (f[i - 1][j] + f[i][j - 1]) % MOD;
    }
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= i; ++j)
            if ((i + j) & 1) ans = (ans + f[i][j]) % MOD;
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Digital_Sunrise (赞：0)

[link](https://www.luogu.com.cn/problem/CF1152D)

## 题意简述
给你一个 $n$ ，求出**所有**长度为 $2n$ 的合法左右括号序列组成的 Trie 树中的最大匹配的大小。

其中 $1\le n \le 1000$

## 思路

[//]:拿样例下手

对于一个叶子节点等深的 Trie 树，有一种比较简单的最大匹配选法：

将每一个深度为**偶数**的节点与其父亲的连边选上，如果有冲突那么只留一个。

![](https://cdn.luogu.com.cn/upload/image_hosting/x40th4ei.png)

按照上述说法可构造如上图的最大匹配，

其中 dep:1 的节点的两个子节点造成了冲突，最终红色边被删掉。

这么选完之后，我们发现所有深度为**奇数**的点都各有一条对应边。

那么答案就是树中深度为**奇数**的点的数量。

如何求？

我们发现在长为 $2n$ 的序列中左括号和右括号的地位时**不对等的**，

因为在每一个右括号出现之前，已有左括号的数量总是要大于已有右括号的数量。

这个情景非常符合**卡特兰树**，尝试用其进行求解。

设 $f_{i,j}$ 表示已经有 $i$ 个左括号,$j$ 个右括号的合法序列的数量，其中 $i \ge j$ 。

也表示树上所有**所含信息长度为 $i + j$ ,包含 $i$ 个左括号以及 $j$ 个右括号**的节点数量。

显然 $f_{i,j}=f_{i-1,j} + f_{i,j-1}$ ，

那么答案即为所有的 $i,j$ 的和为奇数（深度为奇数）的 $f_{i,j}$ 之和

也就是：

$$ans=\sum\limits_{i=1}^n\sum\limits_{j=1}^i f_{i,j}\times[(i+j)\bmod2]$$

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;

int n,ans;
int f[1010][1010];

inline int read()
{
	int w = 1,f = 0;
	char c = getchar();
	while(c < '0' or c > '9')
	{
		if(c == '-') w = -1;
		c = getchar();
	}
	while(c >= '0' and c <= '9')
	{
		f = f * 10 + c - '0';
		c = getchar();
	}
	return w * f;
}

signed main()
{
	n = read();
	f[1][1] = 1;
	for(int i = 2;i <= n + 1;i++)
	{
		for(int j = 1;j <= i;j++)
		{
			f[i][j] = f[i - 1][j] + f[i][j - 1];
			f[i][j] %= mod;
			if((i + j) % 2 == 1)
				ans = (ans + f[i][j]) % mod;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：ljc20020730 (赞：0)

[CF 1152 Solution ](https://www.cnblogs.com/ljc20020730/p/10766001.html)

考虑一个长度为2n ($n \leq 1000$)的括号序列所在的字典树，一组合法的选边是任取一条边两端的两个点都不在边集中其他边中出现。

最大化选边集合的边数。 由于答案较大，对$10^9 + 7 $取模.

Solution : 

考虑到括号序列所在的trie树，若两个括号序列前缀平衡数一定的时候，那么为了保证最后得到合法的括号序列，那么显然，其子树必然相等。

显然，我们不需要重复计算这些冗余的量。

考虑维护这个状态 ， 考虑到确定一个等价的状态只需要确定当前序列总长度和当前平衡值即可。

我们这里对于当前括号序列平衡值的定义是：当前左括号数-右括号数。

显然，通过这两种状态就可以确定一些相互等价的点。这些状态的数目是$n^2$

考虑一个简单的dp，设$f[i][j]$表示当前括号序列长度为$i$（深度），左括号数-右括号数（平衡值）

考虑转移：

$ f[i][j] += f[i-1][j-1] $新增1个右括号

$ f[i][j] += f[i-1][j+1] $新增1个左括号

我们需要知道转移是否合法，即能否组成新的边，这取决于父亲节点$(i-1)$的合法性。

不妨设$g[i][j]$为$f[i][j]$意义下对于$(i,j)$的合法性 ，

转移也非常显然 $g[i][j] = !(g[i-1][j-1]||g[i-1][j+1])$

所以若$ g[i][j] = 1$ 时 生成(i,j) 的方案会额外多1种。

所以转移方程可以写成

$ f[i][j] = f[i-1][j-1] + f[i-1][j+1] + g[i-1][j-1]||g[i-1][j+1]$

$ g[i][j] = !(g[i-1][j-1]||g[i-1][j+1])$

边界 $f[0][0]=0, g[0][0] = 1$

细节方面直接对于一个$ f[i][j] $显然需要满足$j \leq i$。

Code : 

```cpp
# include <bits/stdc++.h>
# define int long long
const int N=2e3+10;
const int mo=1e9+7;
int f[N][N]; bool g[N][N];
using namespace std;
signed main()
{
	int n; scanf("%lld",&n); n<<=1;
	f[0][0]=0,g[0][0]=true;
	for (int i=1;i<=n;i++)
	 for (int j=0;j<=n;j++)
	  {
	  	int ret=0,flag=0;
	  	if (j!=0) ret=(ret+f[i-1][j-1])%mo,flag|=g[i-1][j-1];
	  	if (j+1<=i-1) ret=(ret+f[i-1][j+1])%mo,flag|=g[i-1][j+1];
	  	if (flag) f[i][j]=(ret+1)%mo,g[i][j]=false;
	  	else f[i][j]=ret%mo,g[i][j]=true;
	  }
	printf("%lld\n",f[n][0]);  
	return 0;
}
```


---

