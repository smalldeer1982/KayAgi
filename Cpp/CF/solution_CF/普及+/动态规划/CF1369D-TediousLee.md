# TediousLee

## 题目描述

首先，我们定义 `RDB` 为一棵具有特殊性质的树，它有一个级别 $level$。  
一个级别为 $1$ 的 `RDB` 是一个单独的节点。
接着，对于所有 $i>1$，级别为 $i$ 的 `RDB` 的构成方法如下。  
先求出级别为 $i-1$ 的 `RDB`，然后对于该 `RDB` 中的每个节点 $x$。  

- 如果 $x$ 没有孩子，那么给他加上一个孩子。  
- 如果 $x$ 只有一个孩子，那么给他加上两个孩子。  
- 如果 $x$ 已经有了超过一个孩子，那么我们跳过节点 $x$。  

以下是 $1\le n \le 3$ 的所有 `RDB`

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGMTM2OUQvNjRjNjY3Zjg4YjBiYTNiNThhNDU4MWU4ZjcyNmQ0ODQ3ZDk3N2E2Yy5wbmc?x-oss-process=image/format,png)

接下来，我们定义一个 `claw`  （见下图），它也是一棵具有特殊性质的树，并且将节点 $1$ 称为这个 `claw` 的中心，其他的称为底部节点。

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGMTM2OUQvNDE0MmRhNTE0NDVmNGNmY2UxNmVhNjhkOTY4MzJjYWFiZjE3YWNjZS5wbmc?x-oss-process=image/format,png)

现在，给出一个级别为 $n$ 的 `RDB`，初始时他上面的所有节点都为绿色，你可以进行一些操作。  
对于每次操作，你需要在给出的 `RDB` 中找到一个 `claw`，满足所有底部节点在 `RDB` 中都是中心节点的儿子，且这四个节点在 `RDB` 中都是绿色。然后将这四个节点染为黄色。  
问最多可以将多少个节点染成黄色。

## 说明/提示

$1\le T\le 10^4$  
$1\le n \le 2\cdot 10^6$

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
7
1
2
3
4
5
100
2000000```

### 输出

```
0
0
4
4
12
990998587
804665184```

# 题解

## 作者：wflengxuenong (赞：9)

这个题目画图思考后当然是递归或者递推啦！
对于层数为n的树，根节点的三个子节点中，左右子树为n-2，中间子树为n-1;
所以初步递推为f(n)=f(n-1)+2*f(n-2);
这个代码写完后发现是错的，错在哪里呢？当根节点为3的倍数时候，根节点与其三个子节点可以染色形成一组claw。
![](https://img-blog.csdnimg.cn/2020070516342794.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xlbmd4dWVub25n,size_16,color_FFFFFF,t_70)
递推的初值为：
f[0]=f[1]=f[2]=0

因此递推的式子为：

f(n)=f(n-1)+2*f(n-2) n%3!=0

f(n)=f(n-1)+2*f(n-2)+4 n%3==0

参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+9 ;
typedef long long ll;
const ll mod=1e9+7;
ll a[N],f[N],t,x,n;

int main() {
	cin>>t;
	for(int i=1;i<=t;i++){
		scanf("%lld",&a[i]) ;
		n=max(n,a[i]);
	}
	f[0]=f[1]=f[2]=0,f[3]=4;
	for(int i=4;i<=n;i++){
		f[i]=(f[i-1]+2*f[i-2]%mod)%mod;
		if(i%3==0)f[i]=(f[i]+4)%!mod;
	}
		
	for(int i=1;i<=t;i++)printf("%lld\n",f[a[i]]);

}
```


---

## 作者：vectorwyx (赞：9)

蒟蒻第一次A掉div2的D题呢，赶紧发篇题解纪念一下qwq

------------

很明显，对于$n(n \ge3)$阶的`RBD树`，它的根结点一定有且仅有三个子树。

这三个子树中，有两个是$n-2$阶的`RBD树`，还有一个是$n-1$阶的`RBD树`。

得出这个结论后，递推式$f_{n}=f_{n-1}+f_{n-2} \times2$似乎是理所当然的。但是这个式子默认了答案只由子树决定，而显然根结点和它的三个子树的根结点也会形成一个满足条件的`claw形`，这会对答案产生影响。


------------


故而，我们需要分成两种情况：根结点染色或是不染色，分别用$f_{n,1}$或$f_{n,0}$表示。


* 根结点染色，那么它的三个子树的根结点就不能再成为`claw形`的根结点了。故递推式为$f_{n,1}=f_{n-1,0}+f_{n-2,0}\times 2+4$

* 根结点不染色，那么它的三个子树的根结点没有任何限制。故递推式为$f_{n,0}=f_{n-1}+f_{n-2}\times 2(f_{k}=\max{f_{k,0},f_{k,1}})$

这题就这样做完了。


------------
代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int syk=1e9+7,maxn=2e6+5;//stO syk Orz 
ll dp[maxn][2];//dp[i][0/1]表示i阶的树根结点不染/染黄色所能达到的最大黄色点数 

void solve(int n){//通过递推先把答案预处理出来 
	dp[1][1]=dp[1][0]=dp[2][1]=dp[2][0]=0;
	dp[3][0]=0;dp[3][1]=4;
	fo(i,4,n){
		//分类讨论进行递推 
		dp[i][0]=(1ll*max(dp[i-2][1],dp[i-2][0])*2+max(dp[i-1][1],dp[i-1][0]))%syk;
		dp[i][1]=(4+1ll*dp[i-2][0]*2+dp[i-1][0])%syk;
	}
}

void work(){
	int n=read();
	printf("%d\n",max(dp[n][0],dp[n][1]));
	//puts("");
}
int main(){
	int T=read();
	solve(maxn-5);
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：Priori_Incantatem (赞：6)

[题目链接](https://www.luogu.com.cn/problem/CF1369D)

#### 由于本题的取模会影响最大值的判断，本题解并非正解，仅在不取模的情况下才能保证答案正确。  
#### 但因为数据太水，本方法还是可以AC。仅供参考

个人认为是一道非常有意思的题，题意就不赘述了

首先，要发现这题的做法，必须要先打表找规律。可以自己在纸上用手捏出 $n\le 6$ 的数据

经过打表后，我们可以发现下面这个规律：

![image.png](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pLmxvbGkubmV0LzIwMjAvMDYvMjkvaVZXbUZzWlhVeTlNVFBPLnBuZw?x-oss-process=image/format,png)

图稍微有点丑，见谅

这里其实很像树的最大独立集，我们可以用树形DP实现  
设 $f[x][0]$ 为以 $x$ 为根的子树中，不选 $x$ 的情况下可以得到的最多的 `claw` 的数量。**注意这里是 `claw` 的数量，不是染成黄色的节点数**  
同理，设 $f[x][1]$ 为选 $x$ 的情况下可以得到的最多的 `claw` 的数量。那么，转移方程就是：  
$f[x][1]=\sum f[y][0]$，$f[x][0]=\sum \max(f[y][1],f[y][0])$，其中 $y$ 是 $x$ 的儿子

但是，$T\le 10^4,n\le 2 \cdot 10^6$ 的数据范围并不允许。

根据上面的打表，相信你们一定会发现每一个级别对应着一个唯一的 `RDB`，又因为 $n\le 2 \cdot 10^6$，所以我们可以用递推或者记忆化搜索实现（下面的 $f$ 跟上面的没有关系）  

设 $f[i][1]$ 为在级别为 $i$ `RGB` 中，如果选上根节点时最多可以选出多少个 `claw`  
同理 $f[i][0]$ 表示不选根节点时最多可以选出的  `claw` 的个数  
转移方程：$f[i][1]=2 \times f[i-2][0]+f[i-1][0]+1$  
$f[i][0]=2 \times \max(f[i-2][0],f[i-2][1])+\max(f[i-1][0],f[i-1][1])$

时间复杂度 $\operatorname{O}(n)$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int Maxn=2000000+10,mod=1000000007;
int f[Maxn][2];
int n,m;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int T=read();
	m=2;
	while(T--)
	{
		n=read();
		if(m<n)
		for(int i=m+1;i<=n;++i)
		{
			f[i][1]=((f[i-2][0]<<1)%mod+f[i-1][0]+1)%mod;
			int tmp=(max(f[i-2][0],f[i-2][1])<<1)%mod;
			f[i][0]=(tmp+max(f[i-1][0],f[i-1][1]))%mod;
		}
		m=max(n,m);
		int ans=max(f[n][0],f[n][1]);
		ans=(ans<<1)%mod;
		ans=(ans<<1)%mod; // 输出的时候记得乘以4！
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：2)

# 思路
不难发现，对于一个 $lv>2$ 的树而言，左右儿子是 $lv-2$ 的，中间儿子是 $lv-1$ 的，这里就放一个 $lv=4$ 的图（手绘，不喜勿喷 qwq）：

![](https://cdn.luogu.com.cn/upload/image_hosting/za6i51t1.png)

然后每隔三层，就会在根节点形成一个与子树的爪不重合的爪，所以状态转移方程如下：

$$
dp_i=\left\{\begin{matrix}
 dp_{i-1}+2\times dp_{i-2} & i\bmod3\ne0\\
 dp_{i-1}+2\times dp_{i-2}+4 & i\bmod3=0
\end{matrix}\right.
$$

另外注意一个爪子有四个点。

# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const int mod = 1e9 + 7;
int n = 2000003, t, dp[2000005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	for (int i = 3; i < n; ++ i)
		dp[i] = (dp[i - 1] + dp[i - 2] * 2 % mod + (! (i % 3)) * 4) % mod;
	cin >> t;
	while (t --)
		cin >> n, cout << dp[n] << '\n';
	return 0;
}
```

---

## 作者：AC_love (赞：0)

可以画一个图找一找规律。

不难发现，在一棵级别为 $n$ 的树中，对于根节点而言，它有中间一棵级别为 $n - 1$ 的子树，两边有两棵级别为 $n - 2$ 的子树。

因此，我们可以直接写出 DP 转移方程：$f_i = f_{i - 1} + 2f_{i - 2}$。

但是这么做显然是错的，如果直接这样转移的话，我们会发现：所有的 $f$ 都是 $0$，这就寄了。

寄在哪了呢？我们发现：每个 $n$ 级别的树中，除了一棵 $n - 1$ 级别的树和两棵 $n - 2$ 级别的树之外，还有一个根节点，这个根节点刚才一直被我们忽略了。

我们可以把一些根节点拼在一起，形成更多的 `claw`。

不难发现，每次 $n$ 是 $3$ 的倍数的时候，就可以形成一个更多的 `claw`，可以染色的节点数增加 $4$。

因此转移方程为 $f_i =\begin{cases} f_{i - 1} + 2f_{i - 2}&{\mathrm{if}}(i \not \equiv 0 \pmod 3) \\ f_{i - 1} + 2f_{i - 2} + 4 &{\mathrm{if}}(i \equiv 0 \pmod 3) \end{cases}$

可以 DP 预处理 $f$ 数组，然后 $O(1)$ 询问即可，非常容易。

---

## 作者：kimi0705 (赞：0)

# CF1369D TediousLee 题解
考虑 dp。

设 $dp_{i,0}$ 表示节点 $i$ 染色的答案，$dp_{i,1}$表示节点 $i$ 染色的答案。 

特殊的，$dp_{1,0}=dp_{2,0}=0$ 和 $dp_{1,1}=dp_{2,1}=-\infty$

考虑转移：$dp_{i,0}=\max(dp_{i-2,0},dp_{i-2,1})\times2+\max(dp_{i-1,0}, dp_{i-1,1})$、$dp_{i,1}=dp_{i-2,0}\times2+dp_{i-1,0}+4$。

注意加 $4$。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6;
const int Mod = 1e9 + 7;
int dp[N + 10][2], q, x;
int main() {
    dp[1][0] = 0, dp[1][1] = -10000000;
    dp[2][0] = 0, dp[2][1] = -10000000;
    for (int i = 3; i <= N; i++) {
        dp[i][0] = (max(dp[i - 2][0], dp[i - 2][1]) * 2 % Mod + max(dp[i - 1][0], dp[i - 1][1])) % Mod;
        dp[i][1] = (dp[i - 2][0] * 2 % Mod + dp[i - 1][0] + 4) % Mod;
    }
    cin >> q;
    while(q--) {
        cin >> x;
        cout << max(dp[x][0], dp[x][1]) << '\n';
    }
}
```

---

## 作者：cmll02 (赞：0)

这里有个稍微不同的做法。

首先很显然这个数据范围就是 $O(T+\max(n))$ 也就是预处理出答案。

那么这玩意怎么预处理呢？

dp 式子是 $f_i=\max(f_{i-1}+2f_{i-2},4(f_{i-4}+f_{i-3})+f_{i-2}+1)$，但是这样会挂。

原因就是取模后你不知道哪个更大（比如 $2$ 和 $10^9+8$ 取模后 $2$ 大）。

但是不取模就是对的。

我们试试把没有溢出的部分打表：

```cpp
0
0
1
1
3
6
12
24
49
97
195
390
780
1560
3121
6241
12483
```

这样就明显了。


$f_i = f_{i-1}+1$ 或 $f_i = f_{i-1}-1$ 或 $f_i = f_{i-1}$。

至于具体如何，很好算吧。。。显然按照 $6$ 为循环节周期变。

```
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#define int long long
inline int read()
{
	int num=0;char c=getchar();int f=1;
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47&&c<58)num=num*10+(c^48),c=getchar();
	return num*f;
}
int w0[2000005],w1[2000005],a[2000005];
inline int re1d()
{
    char c=getchar();
    while((c^48)>1)c=getchar();
    return c&1;
}
const int mod=1000000007;
inline int max(int a,int b){return a<b?b:a;}
signed main()
{
    int T=read();
    w0[1]=1;
    /*for(int i=2;i<=200000;i++)
    {
        int tmp=w0[i-1];
        w0[i]=w0[i-1]+2*w1[i-1];
        w0[i]%=mod;
        w1[i]=tmp;
        if(i==3)a[i]=1;
        else if(i==2)a[i]=0;
        else a[i]=a[i-1]+w1[i-1]-1;
    }*/
    a[3]=a[4]=1,a[5]=3;
    
    for(int i=6;i<=2000000;i++)//a[i]=a[i-1]*2%mod;
    {
        a[i]=a[i-1]*2%mod;
        if(i%6==3||i%6==5)a[i]=(a[i]+1)%mod;
        else if(i%6==4)a[i]=(a[i]+mod-1)%mod;
    }
    while(T--)
    //for(int i=1;i<=100;i++)
    {
        int n=read();
        printf("%lld\n",(a[n]*4)%mod);
    }
    //printf("%lld\n",n+n-ans);
}
//0 0 0 1 -1 1
```

---

