# ゲーム

## 题目描述

Alice 和 Bob 在玩游戏。初始时有两座山，左边的山上有 $A$ 个物品，从上到下的第 $i$ 个价值为 $a_i$；右边的山上有 $B$ 个物品，从上到下的第 $i$ 个价值为 $b_i$。Alice 先手，Alice 和 Bob 交替进行操作，可行的操作如下：

- 如果两座山都空了，游戏结束。
- 如果只有某一座山空了，取走另一座山上的最上面的物品。
- 如果两座山都没有空，选择任意一座山，并取走其最上面的物品。

假设两人都采取最优策略，请求出 Alice 能取得的物品的价值总和。

## 说明/提示

- $1 \le A, B \le 1000$
- $1 \le a_i, b_i \le 1000$

# 题解

## 作者：Proxima_Centauri (赞：3)

[雅虎曰：原题传送门](https://www.luogu.com.cn/problem/AT_tdpc_game)

## 题目大意
两堆东西，每个东西都有一个价值，Alice 和 Bob 轮流取，都以最优策略，最大化 Alice 获得的价值。
## 分析
~~胡说八道部分~~

发现很多大佬都使用了区间 DP，蒟蒻不会写，只能搞线性的。

**状态**

设 $f[i][j]$ 表示：第一堆东西取到第 $i$ 个之前，第二堆取到第 $j$ 个之前的时候，Alice 获得的最大价值。

**转移**

我们采用逆推的方式进行 DP。~~才不是因为我正推挂了呢~~

那么我们很容易得到，在 Alice 取的时候的转移方程：
$$f[i][j] = \max(f[i + 1][j] + a[i], f[i][j + 1] + b[j])$$ 
其中，$a[i]$ 和 $b[j]$ 分别表示两堆东西的第 $i$ 个和第 $j$ 个的价值。

但是，这毕竟是个双人游戏，Bob 取的时候又该怎么办呢？

$Bob$ 天天玩各种游戏，脑子肯定非常聪明，所以肯定会采取最优策略——最小化 Alice 获得的价值，才能让自己获得的更多。~~（废话~~

所以根据这个思想，我们能得到在 Bob 取的时候的方程：
$$f[i][j] = \min(f[i + 1][j], f[i][j + 1])$$ 
还有一个小问题——怎么判断该谁取了？

非常简单。如果 $i + j$ 是偶数，说明两个人总共取过了偶数次，所以下一次应该 Alice 取！反之，如果是奇数就应该 Bob 取。

**初值**

这个东西比较麻烦。
我们推 $i$ 的时候会利用 $i + 1$，所以我们需要初始化 $n + 1$ 的项。同理，$m + 1$ 也要初始化。

具体初始化过程放在下面了。如下代码和转移过程一样，也是讨论了该谁取的情况。
```
for (int i = n; i >= 1; i--) 
	if ((i + m) % 2) f[i][m + 1] = f[i + 1][m + 1] + a[i];
	else f[i][m + 1] = f[i + 1][m + 1];
for (int i = m; i >= 1; i--) 
	if ((i + n) % 2) f[n + 1][i] = f[n + 1][i + 1] + b[i];
	else f[n + 1][i] = f[n + 1][i + 1];
```
**答案**

这个不用多说，就是 $f[1][1]$。
## AC code
话不多说，上代码！
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
int f[1010][1010];
int a[1010], b[1010];
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= m; i++) scanf("%d", b + i);
	for (int i = n; i >= 1; i--) 
		if ((i + m) % 2) f[i][m + 1] = f[i + 1][m + 1] + a[i];
		else f[i][m + 1] = f[i + 1][m + 1];
	for (int i = m; i >= 1; i--) 
		if ((i + n) % 2) f[n + 1][i] = f[n + 1][i + 1] + b[i];
		else f[n + 1][i] = f[n + 1][i + 1];
	for (int i = n; i >= 1; i--)
		for (int j = m; j >= 1; j--)
			if ((i + j + 1) % 2) 
				f[i][j] = max(f[i + 1][j] + a[i], f[i][j + 1] + b[j]);
			else f[i][j] = min(f[i + 1][j], f[i][j + 1]);
	printf("%d\n", f[1][1]);
	return 0;
}
```
为了纪念伟大的退役的 $27$ 老师，代码总共有 $27$ 行。
## 总结
挺好的一道动态规划题，放在黄题比较难了，思维难度还是可以的，尤其是逆推这里。~~我就没想到（不是~~

---

## 作者：Obviathy (赞：3)

考虑把两个序列头尾拼接，然后跑区间DP。

我们设计 $f_{i,j}$ 为区间 $i$ 到 $j$ 的答案，显然先手希望它最大，后手希望它最小（很经典的套路了）。这个思路可以参考[这个题](https://www.luogu.com.cn/problem/AT_dp_l)。

当你完全理解了刚才那个题后，我们可以发现，将两个序列拼起来，那不就是从头尾取石子求最优值吗！

这道题我们只需判断一下中间的断点。我们知道如果区间在断点左边或右边都是没意义的，因为区间与断点中间的石子是不可能先于区间取到的，而且区间的一个端点如果刚好在区间上，那么就只能在左边或右边去了。在这里特判一下。

### AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e3+10;
int n,mid,m;
long long a[N],b[N];
long long f[N][N];
int main(){
	cin >> n >> m;
	mid = n;
	for(int i = 1;i <= n;i ++)cin >> a[i];
	for(int i = n+m;i >= n + 1;i --)cin >> a[i];
	n += m;
//	for(int i = 1;i <= n;i ++)cout << a[i] <<' ';
//	cout << endl;
//	f[mid][mid] = a[mid];
//	f[mid+1][mid+1]=a[mid+1];
	for(int len = 1;len <= n;len ++){
		for(int i = 1;i+len-1 <= n;i ++){
			int j = i + len - 1;
			if(i <= mid && j >= mid+1)
				if((n-len)&1)f[i][j] = min(f[i+1][j],f[i][j-1]);
				else f[i][j] = max(f[i+1][j]+a[i],f[i][j-1]+a[j]);
			if(i == mid + 1)
				if((n-len)&1) f[i][j] = f[i][j-1];
				else f[i][j] = f[i][j-1] + a[j];
			if(j == mid)
				if((n-len)&1) f[i][j] = f[i+1][j];
				else f[i][j] = f[i+1][j] + a[i];
		}
	}
//	for(int i = 1;i <= n;i ++)for(int j = i;j <= n;j ++)cout << i <<'~'<<j<<':'<<f[i][j]<<endl;
	cout << f[1][n] << endl;
	return 0;
}
```

一开始我尝试一次走一轮，但被卡掉了。所以就屈服于分开写的做法。

感谢 [@ttttalk](https://www.luogu.com.cn/user/538738) debug！

---

## 作者：ttttalk (赞：2)

## [AT_tdpc_game ゲーム](https://www.luogu.com.cn/problem/AT_tdpc_game)

看各位大佬的题解都是线性的，我个人比较喜欢区间，于是将 $a,b$ 两个序列拼起来，每次从两头取就是一道美好的区间 $dp$ 小题。

## Solution

对于一个区间 $i,j$，定义 $f_{i,j}$ 为其中的答案。先手的回合是取的数为偶数次时，先手希望答案尽可能大，于是可以得到方程式：

$$f_{i,j}=\max(f_{i+1,j}+a_i,f_{i,j-1}+a_j)$$

后手回合显然是回合为奇数次时，取的数字对答案没有任何帮助，直接扔掉就好了。但是每次取最小才能使先手取的数尽量大，于是直接取最小值。

$$f_{i,j}=\min(f_{i+1,j},f_{i,j-1})$$

这里有一个很重要的问题，就是本来是两个线性的序列，一个取完了只能固定地取另外一个。如果拼成一个两头取的序列的时候，注意区间必须经过中间的分界点，如果不经过的话答案将会没有意义。

剩下的小点在代码中体现。

## AC Code

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int N=1e3+10;
int n,m,a[2*N],f[2*N][2*N];//合并序列，数组开两倍
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=n+m;i>=n+1;i--) scanf("%d",&a[i]);
	n+=m;
	for (int len=1;len<=n;len++)//斜着填，区间最小为1就可以不用初始化
	{
		for (int i=1;i+len<=n+1;i++)
		{
			int j=i+len-1,d=n-m;//d为断点
			if (i>=d+1)//取完了左边的序列
			{
				if ((n-len)%2==0) f[i][j]=f[i][j-1]+a[j];//模拟，先手按顺序取
				else f[i][j]=f[i][j-1];//后手取得直接扔掉
			}
			else if (j<=d)//取完了右边的序列
			{
				if ((n-len)%2==0) f[i][j]=f[i+1][j]+a[i];
				else f[i][j]=f[i+1][j];
			}
			else//两头取
			{
				if ((n-len)%2==0) f[i][j]=max(f[i+1][j]+a[i],f[i][j-1]+a[j]);
				else f[i][j]=min(f[i+1][j],f[i][j-1]);
			}
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}
```
## Update

更新一种线性写法。

本质是差不多的。定义 $f_{i,j}$ 为 $a$ 数组已经取了 $i$ 到 $n$，$b$ 数组取了 $j$ 到 $m$ 的最优策略。已经取了的个数是 $i-1+j-1$，判断它的奇偶性来决策先手和后手。

易得出先手的策略为：

$$f_{i,j}=\max(f_{i+1,j}+a_i,f_{i,j+1}+b_j)$$

后手同理：

$$f_{i,j}=\min(f_{i+1,j},f_{i,j+1})$$

每一个策略都是由后面的决策推过来的，所以需要倒着求。

接下来就是边界问题。当 $i=n+1$ 或者是 $j=m+1$ 时，其中一方数组被取完。当然也可以判断边界然后在决策，但是这种方法免不了每次都得写一个奇偶性判断先手后手，比较麻烦，写错了容易崩溃。

可以换一个思路想。当一方数组取完了，那么有这个状态的决策都不能选它，也就是找最大最小值的时候它不是最优决策，那么用个三目运算符直接在转移式里面解决了。

## AC Code

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1e3+10,inf=0x3f3f3f3f;
int n,m,a[N],b[N],f[N][N];
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",a+i);
	for (int i=1;i<=m;i++) scanf("%d",b+i);
	for (int i=n+1;i>=1;i--)
	{
		for (int j=m+1;j>=1;j--)
		{
			if (i==n+1&&j==m+1) continue;//两个都取完了，没有意义
			if ((i+j)%2) f[i][j]=min(i==n+1?inf:f[i+1][j],j==m+1?inf:f[i][j+1]);//后手，将一方数组取完的决策赋成正无穷使它不是最优决策
			else f[i][j]=max(i==n+1?0:f[i+1][j]+a[i],j==m+1?0:f[i][j+1]+b[j]);//先手，将一方数组取完的决策赋成负无穷或者是0使它不是最优决策
		}
	}
	printf("%d\n",f[1][1]);//最终答案是从头取到尾
}
```

---

## 作者：fa_555 (赞：1)

**upd：题解界面 LaTeX 渲染又挂了...正确内容请在洛谷博客或个人博客查看**

under 题解 [AT680](https://www.luogu.com.cn/problem/AT680)

同步发布于[个人博客](https://fa555.github.io/2020/某At的dp场/#B-ゲーム)

### problem

Alice 和 Bob 在玩游戏。初始时有两座山，左边的山上有 $A$ 个物品，从上到下的第 $i$ 个价值为 $a_i$；右边的山上有 $B$ 个物品，从上到下的第 $i$ 个价值为 $b_i$。Alice 先手，Alice 和 Bob 交替进行操作，可行的操作如下：

- 如果两座山都空了，游戏结束。
- 如果只有某一座山空了，取走另一座山上的最上面的物品。
- 如果两座山都没有空，选择任意一座山，并取走其最上面的物品。

两人都想取得更大的价值。假设两人都采取最优策略，请求出 Alice 能取得的物品的价值总和。

输入的所有数字都是 $[1, 1000]$ 中的整数。

### solution

考虑从终局向前逆推。设 $f_{i, j}$ 表示 $A$ 被取走第 $i \sim A$ 个物品， $B$ 被取走第 $j \sim B$ 个物品时的价值。

对 $i + j$ 为偶数/奇数，即 Alice/Bob 操作时分类转移：

$$
f_{i, j} = \begin{cases}
\max(f_{i + 1, j} + a_i, f_{i, j + 1} + b_j) & , (i + j) \equiv 0 \pmod 2 \\
\min(f_{i + 1, j}, f_{i, j + 1}) & , (i + j) \equiv 1 \pmod 2
\end{cases}
$$

边界：$f_{i, B + 1} = f_{A + 1, j} = 0$

答案即为 $f_{1, 1}$。总复杂度 $O(AB)$。

### code

实现时要尤其注意边界情况。

``` cpp
int f[1003][1003];

int dp(int A, int* a, int B, int* b) {
  // a, b 下标均从 1 开始
  for (int i = A + 1; i; --i)
    for (int j = B + 1; j; --j) {
      if (i > A && j > B) continue;
      if ((i + j) & 1) {
        if (i > A)
          f[i][j] = f[i][j + 1];
        else if (j > B)
          f[i][j] = f[i + 1][j];
        else
          f[i][j] = std::min(f[i + 1][j], f[i][j + 1]);
      } else {
        if (i > A)
          f[i][j] = f[i][j + 1] + b[j];
        else if (j > B)
          f[i][j] = f[i + 1][j] + a[i];
        else
          f[i][j] = std::max(f[i + 1][j] + a[i], f[i][j + 1] + b[j]);
      }
    }
  return f[1][1];
}

```

---

## 作者：ny_123457 (赞：0)

## Part 1.思路
~~真是应了那句话，标签给啥就做啥。~~  
此题感觉可以算一个不太正常的背包吧，假设这两座山用一个二维数组存，其中一个维度表示一座山能取到的几个物品，另一个维度表示另一座山的。  
状态设定：$f_{i,j}$ 表示 Alice 拿到第 $i,j$ 个物品时获得的价值。  
状态转移：如果 $(i+1) \equiv 1(\mod 2 )$ 那么 $f_{i,j}=min(f_{i+1,j},f_{i,j+1})$，否则 $f_{i,j}=max(f_{i+1,j}+a_i,f_{i,j+1}+b_j)$。
## Part 2.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005],b[1005],f[1005][1005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int i=n+1;i>=1;i--){
		for(int j=m+1;j>=1;j--){
			if((i+j)%2==1){
				if(i<=n&&j<=m)f[i][j]=min(f[i+1][j],f[i][j+1]); 
				else if(i<=n&&j>m)f[i][j]=f[i+1][j];
				else if(j<=m)f[i][j]=f[i][j+1];
			}
			else{
				if(i<=n&&j<=m)f[i][j]=max(f[i+1][j]+a[i],f[i][j+1]+b[j]);
				else if(i<=n&&j>m)f[i][j]=f[i+1][j]+a[i];
				else if(j<=m)f[i][j]=f[i][j+1]+b[j];
			}
		}
	}
	cout<<f[1][1];
	return 0;
}
```

---

## 作者：Lian_zy (赞：0)

## 题目大意
给你两座山 $A,B$，两人轮流操作，每次取走任意一个座山的山顶元素（如果该山非空），两人均采用最优方案，求先手可以取走的最大价值。

## 题目分析

可以把两座山尾接尾的拼起来，像这样：

$$
a_1,a_2 \dots a_{n-1},a_n,b_m,b_{m-1} \dots b_2,b_1
$$

这样少了一个数组，整题会变得容易许多。

接下来我们定义一个数组 $dp_{i,j}$，表示在区间 $\{i,j\}$ 中进行这个过程，产生的最大价值。

对于每一个区间，如果先手：

$dp_{i,j}=\max\{dp_{i+1,j}+a_i,dp_{i,j-1}+a_j\}$

如果是后手，肯定要不得我们好，所以后手一定会给我们留下最差的，即：

$dp_{i,j}=\min\{dp_{i+1,j},dp_{i,j-1}\}$

注意这里不能加上后手取到的数字

最后判断某座山是否为空

我们知道连接点 $d = $ 区间长度 $- m$。

$i = d + 1$ 时第一座山为空，$j = d$ 时第二座山为空。

为空的话 $dp$ 状态只考虑一座山即可。

于是这道题就做完了。

---

## 作者：cosf (赞：0)

## [ゲーム](https://www.luogu.com.cn/problem/AT_tdpc_game)

~~标题是什么意思我不知道。~~

显然，Bob 的策略肯定和 Alice 相同。因为 Bob 的价值高，Alice 的价值就低，这是显然的。

于是，我们可以参考 [Deque](https://www.luogu.com.cn/problem/AT_dp_l)。那道题要求的是分数之差 $X - Y$。

由幼儿园数学知 $X = \frac{(X - Y) + (X + Y)}{2}$，所以我们套那题的思路求出差之后，加上所有的物品的价值之和，除以 $2$ 即可。

具体地，我们令 $dp_{i, j}$ 表示左边的山**剩** $i$ 个，右边的山**剩** $j$ 个时差的最大值，则有

$$
dp_{i, j} = \max\{a_{i + 1} - dp_{i + 1, j}, b_{j + 1} - dp_{i, j + 1}\}
$$

注意判断边界情况。

那么，本题的代码就十分好写了。

```cpp
#include <iostream>
using namespace std;

#define MAXN 1005

int dp[MAXN][MAXN];

int a, b;

int va[MAXN];
int vb[MAXN];

int main()
{
    cin >> a >> b;
    int s = 0;
    for (int i = 1; i <= a; i++)
    {
        cin >> va[i];
        s += va[i];
    }
    for (int i = 1; i <= b; i++)
    {
        cin >> vb[i];
        s += vb[i];
    }
    for (int i = a; ~i; i--)
    {
        for (int j = b; ~j; j--)
        {
            if (i == a)
            {
                if (j == b)
                {
                    continue;
                }
                else
                {
                    dp[i][j] = vb[j + 1] - dp[i][j + 1];
                }
            }
            else if (j == b)
            {
                dp[i][j] = va[i + 1] - dp[i + 1][j];
            }
            else
            {
                dp[i][j] = max(va[i + 1] - dp[i + 1][j], vb[j + 1] - dp[i][j + 1]);
            }
        }
    }
    cout << (s + dp[0][0]) / 2 << endl;
    return 0;
}

```


---

## 作者：expecto__patronum (赞：0)

## 思路：
弱智 DP 题，直接设表示子树内染色的方案数，然后每次合并一个点与它的儿子即可（具体而言，因为儿子间独立，所以方案数就是二项式系数）。

需要注意的是因为第一条边可以在任意位置，所以要以每个点为根各 DP 一次。但是这样每条边会被算两次，所以乘以 $2$ 的逆元即可。

时间复杂度 $O(n^2)$。

## 代码:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int inv2=5e8+4;
const int N=1e3+100;
int n,res;
int f[N],sz[N],fac[N],inv[N];
vector<int>v[N];
void dfs(int x,int fa){
    f[x]=1;
	sz[x]=0;
    for(auto y:v[x]){
        if(y==fa) continue;
        dfs(y,x);
        f[x]=1ll*f[x]*f[y]%mod*inv[sz[x]]%mod*inv[sz[y]]%mod*fac[sz[x]+sz[y]]%mod;
        sz[x]+=sz[y];
    }
    sz[x]++;
}
int ksm(int x,int y=mod-2){
	int z=1;
	for(;y;y>>=1,x=1ll*x*x%mod) if(y&1) z=1ll*z*x%mod;
	return z;
}
signed main(){
    scanf("%lld",&n);
    fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);
	for(int i=n;i;i--) inv[i-1]=1ll*inv[i]*i%mod;
    for(int i=1,x,y;i<n;i++){
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
    for(int i=1;i<=n;i++){
		dfs(i,0);
		(res+=f[i])%=mod;
	}
    printf("%lld\n",1ll*res*inv2%mod);
    return 0;
}

```
[博客](https://www.cnblogs.com/xuantianhao/p/17773998.html)


---

## 作者：Kketchup (赞：0)

## AT-tdpc-game

[传送门](https://atcoder.jp/contests/tdpc/tasks/tdpc_game)

**题意简述**

Alice 和 Bob 在玩游戏。初始时有两座山，左边的山上有 $A$ 个物品，从上到下的第 $i$ 个价值为 $a_i$；右边的山上有 $B$ 个物品，从上到下的第 $i$ 个价值为 $b_i$。Alice 先手，Alice 和 Bob 交替进行操作，可行的操作如下：

- 如果两座山都空了，游戏结束。
- 如果只有某一座山空了，取走另一座山上的最上面的物品。
- 如果两座山都没有空，选择任意一座山，并取走其最上面的物品。

假设两人都采取最优策略，请求出 Alice 能取得的物品的价值总和。

**题目解析**

与 [AT-dp-l](https://atcoder.jp/contests/dp/tasks/dp_l) 类似。

设 $f_{i,j}$表示 $A$ 山（从上到下）取到 $i$，$B$ 山（从上到下）取到 $j$，Alice 的最大价值总和，则答案为 $f_{1,1}$。

转移，若轮到 Alice，即 $(i+j)\bmod2=0$，

$f_{i,j}=\max(f_{i+1,j}+a_i,f_{i,j+1}+b_j)$

否则 $f_{i,j}=\min(f_{i+1,j},f_{i,j+1})$ 

再考虑当 $i=n$ 或者 $j=m$，即一座山已空，此时在两山情况取一种，可用三目运算简化式子。

```cpp
if((i+j)%2==0) 
    f[i][j]=max((i==n+1)?0:(f[i+1][j]+a[i]),(j==m+1)?0:(f[i][j+1]+b[j]));
else 
    f[i][j]=min((i==n+1)?INF:f[i+1][j],(j==m+1)?INF:f[i][j+1]);
```
当然，也可以将两座山拼起来，山顶朝外，注意判断一山取完的情况即可。此处不再详细说明。

**具体实现**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int N=1005;
const int INF=0x3f3f3f3f;
int n,m;
int a[N],b[N];
int f[N][N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=m;++i) scanf("%d",&b[i]);
	for(int i=n+1;i>=1;--i){
		for(int j=m+1;j>=1;--j){
			if(i==n+1&&j==m+1) continue;
			if((i+j)%2==0)
                f[i][j]=max((i==n+1)?0:(f[i+1][j]+a[i]),(j==m+1)?0:(f[i][j+1]+b[j]));
			else
                f[i][j]=min((i==n+1)?INF:f[i+1][j],(j==m+1)?INF:f[i][j+1]);
		}
	}
	printf("%d\n",f[1][1]);
	return 0;
}
```

**完结撒花！请管理通过啦。**

---

## 作者：scp020 (赞：0)

## 本体是一道动态规划题，贪心是不正确的（非常好举反例）

既然是动态规划，那没什么好说的了，这是两座山，所以我们设一个二维数组，第一维表示第一座山取到第几个物品了，第二维同理，$f[i][j]$ 的值表示取到第 $i,j$ 个物品时 Alice 获得的价值。

**动态转移方程如下**：

若 $(i+j)\equiv1\pmod{2}$，则 $f[i][j]=\min(f[i+1][j],f[i][j+1])$。

若 $(i+j)\equiv0\pmod{2}$，则 $f[i][j]=\max(f[i+1][j]+a[i],f[i][j+1]+b[j])$。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int A,B,a[1010],b[1010],f[1010][1010];//f用来dp，第一维记录第一座山（A）取到第几个了，第二维同理 
int main()
{
	cin>>A>>B;
	for(int i=1;i<=A;i++) cin>>a[i];
	for(int i=1;i<=B;i++) cin>>b[i];
	for(int i=A+1;i>=1;i--)//这里开始dp，顺带初始化
	{
		for(int j=B+1;j>=1;j--)
		{
			if((i+j)%2==1)
			{
				if(i<=A && j<=B) f[i][j]=min(f[i+1][j],f[i][j+1]);//在正常的取物范围内，dp，下同 
				else if(i<=A && j>B) f[i][j]=f[i+1][j];//超出范围的是初始化，下同 
				else if(j<=B) f[i][j]=f[i][j+1];
			}
			else
			{
				if(i<=A && j<=B) f[i][j]=max(f[i+1][j]+a[i],f[i][j+1]+b[j]);
				else if(i<=A && j>B) f[i][j]=f[i+1][j]+a[i];
				else if(j<=B) f[i][j]=f[i][j+1]+b[j];
			}
		}
	}
	cout<<f[1][1]<<endl;
	return 0;
}
```


---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT680) & [原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/680)

---

**题意**

有两个人取两个栈的数，每次只能取栈顶，两人都想取得最多数值。问在最优方案下，先手取得的总值是多少？

---

**分析**

**背包！**

问什么设什么。

设 $f_{i,o}$ 为第一个栈取完 $i\sim A$ 个数且第二个栈取完 $o\sim B$ 个数时，先手的获益。

显然，由于栈顶在末尾，所以是逆推。

由于每次只会在两个数中选择，所以只会在两个方案里取最值。
1. 当先手取时，会选最大的方案（注意要加上这一次取的数）
2. 当后手取时，大的方案取了，就剩下小的了，所以就选小的方案（注意这次没有取数）

所以得到转移方程：

$$\boxed{f_{i,o}=\begin{cases}\max(f_{i+1,o}+a_i,f_{i,o+1}+b_o)[i+o\text{为偶数}]\\\min(f_{i+1,o},f_{i,o+1})[i+o\text{为奇数}]\end{cases}}$$

初始化：$f_{A+1,o}=0,f_{i,B+1}$

答案：$f_{1,1}$

时间复杂度：$\Theta(AB)$

---

**代码**

注意边界的初始化和第一个数的处理。

```cpp
#include<bits/stdc++.h>
using namespace std;
int A,B,a[1100],b[1100],f[1100][1100];
int main()
{
	cin>>A>>B;
	for(int i=1;i<=A;i++)
		cin>>a[i];
	for(int i=1;i<=B;i++)
		cin>>b[i];
	for(int i=A+1;i;i--)
		for(int o=B+1;o;o--)
			if((i+o)&1)
				if(i<=A)
					if(o<=B)
						f[i][o]=min(f[i+1][o],f[i][o+1]);
					else 
						f[i][o]=f[i+1][o];
				else
					if(o<=B)
						f[i][o]=f[i][o+1];
					else 
						continue;
			else
				if(i<=A)
					if(o<=B)
						f[i][o]=max(f[i+1][o]+a[i],f[i][o+1]+b[o]);
					else 
						f[i][o]=f[i+1][o]+a[i];
				else
					if(o<=B)
						f[i][o]=f[i][o+1]+b[o];
					else 
						continue;
			
	cout<<f[1][1]<<endl;
	return 0;
}
```

---

