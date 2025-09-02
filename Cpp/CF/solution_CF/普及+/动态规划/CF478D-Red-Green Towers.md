# Red-Green Towers

## 题目描述

你有 $r$ 块红色的积木和 $g$ 块绿色的积木，它们用于建造红绿塔。红绿塔按照下面的规则来建造：

- 红绿塔有若干层；
- 如果红绿塔有 $n$ 层，那么塔的第一层应该有 $n$ 块积木，第二层有 $n-1$ 块，第三层有 $n-2$ 块，以此类推，最后一层只有一块。换言之，每一层应该比前面一层少一块；
- 红绿塔的每一层必须使用相同颜色的积木。

令 $h$ 表示用 $r$ 个红积木和 $g$ 个绿积木所能搭建的满足上述规则的塔的最大层数。现在你的任务是确定可以建造出多少不同的有 $h$ 层的红绿塔。

如果两个红绿塔相同的一层使用的是不同的颜色，它们就被认为不同的。

你需要写一个程序来求出有多少种高度为 $h$ 的不同的红绿塔。由于答案很大，你只需要输出答案模 $10^9+7$（也就是$1000000007$）后的值。

## 样例 #1

### 输入

```
4 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
9 7
```

### 输出

```
6
```

## 样例 #3

### 输入

```
1 1
```

### 输出

```
2
```

# 题解

## 作者：灵茶山艾府 (赞：3)

首先求出能堆出的最高层数 $h$，满足 $\dfrac{h(h+1)}{2}\le r+g$。

由于每层需要的积木都是同种颜色的，将每层需要的积木视作一个物品，$r$ 视作背包容量，则问题可以看成是从 $1$ 到 $h$ 各有一个物品，组合成不超过 $r$ 的 0-1 背包的方案数。

若组合的数字过小，可能会导致绿色方块不够用，因此组合的数字有下界 $\max\Big(\dfrac{h(h+1)}{2}-g,0\Big)$。

将上下界内的方案数累加即为答案。

```go
package main
import . "fmt"

func main() {
	const mod int = 1e9 + 7
	var r, g, ans int
	Scan(&r, &g)
	h := 1
	for (h+1)*(h+2)/2 <= r+g { h++ }
	dp := make([]int, r+1)
	dp[0] = 1
	for i := 1; i <= h; i++ {
		for j := r; j >= i; j-- {
			dp[j] = (dp[j] + dp[j-i]) % mod
		}
	}
	// 此时 dp[i] 表示堆完 h 层且用了 i 个红色方块的方案数
	// 为保证用的绿色方块数不超过 g，i 不能小于 max(0, h*(h+1)/2-g)
	for _, v := range dp[max(0, h*(h+1)/2-g):] {
		ans = (ans + v) % mod
	}
	Print(ans)
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
```


---

## 作者：_JF_ (赞：2)

[Link](https://www.luogu.com.cn/problem/CF478D)

一开始想着去考虑求出这个 $h$，没想到就被误导了。

~~你以为你找到了突破口，那你就全错了！~~

其实问道计数还是考虑 dp，问什么就设什么。

现在想到设 $dp_{i,j,k}$ 表示前 $i$ 层，使用了 $j$ 个红色色块，$k$ 个绿色色块的**方案数**。

注意到如果我们知道 $(i,j)$，可以算出绿色色块的数量为 $\frac{(1+i)\times i}{2}-j$。

发现对于当前的第 $i$ 层填的个数为 $i$，我们直接从红色块/绿色块进行一个转移。

发现到我们的 $dp_{i,j}$ 转移只依赖 $i-1$ 的状态，所以很显然把 $i$ 滚掉。

观察到层数是 $\sqrt n$ 级别的，所以时间复杂度为 $O(n\sqrt n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =200001;
const int mod=1e9+7;
#define int long long
int r,g,ans,dp[N],dp1[N]; 
signed main(){
	cin>>r>>g;
	dp[0]=1;
	for(int i=1;i<=1000;i++){
		int pre=0;
		for(int j=0;j<=r;j++)	dp1[j]=0;
		for(int j=min(r,(1+i)*i/2);j>=0;j--){
			int Red=j,Gre=(1+i)*i/2-j;
			if(Red<=r&&Gre<=g){
				dp1[j]+=dp[j]%mod,dp1[j]%=mod;
				if(j-i>=0)	dp1[j]+=dp[j-i]%mod,dp1[j]%=mod;
			}
			pre+=dp1[j]%mod,pre%=mod;
		}
		for(int j=min(r,(1+i)*i/2);j>=0;j--)	dp[j]=dp1[j];
		if(pre>0)	ans=pre;
		else	break;
	}
//	for(int i=1;i<=5;i++)
//		for(int j=0;j<=(1+i)*i/2;j++)	cout<<i<<" "<<j<<" "<<dp[i][j]<<endl; 
	cout<<ans%mod<<endl;
}
// dp_i,j [1,i] use j red 's ans  
```

---

## 作者：流绪 (赞：2)

砖可能有剩余!

这题应该很容易看出来是 DP 吧

每层的砖块可以看成是等差数列,首项,公差为 1,我们可以根据砖块和求出层数

层数 h*(h+1)/2 = r+g ( 等差数列求和公式 )

但是砖可能是过多的,怎么处理呢?

假设砖是刚好的,我们将砖总和乘以 2 后开根号可以得到一个在 h 到 h+1 间的数,那么砖是过多时,这个数可能达到 h+1 !那么接下来我们的计算就出错了,那么为了避免这个我们不算 h 算 h+1 不就好了.

然后得到层数后我们就可以对层数进行 DP 了

转移方程 dp[i][j] += dp[i-1][j-i]

前i层用j块砖有几种可能,但是题目中砖的数量有 2e5,空间会爆,所以我们滚动掉第一维 dp[j] += dp[j-i] 然后对于每一种红砖个数的用的可能从大到小枚举,若当前红砖加绿砖加起来都不够用退出就好了

一些细节注释在代码里了

下面是 AC代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[200010]={0};
#define mod 1000000007
int main()
{  
	int r,g;
	cin >> r >> g;
	int h = sqrt(r+g+r+g);
	while(h*(h+1)<=r+g+r+g)	 
		h++;
	dp[0]= 1;
	for(int i=1;i<h;i++)		//前 i 层 
		for(int j=r;j>=i;j--)	//用 j 块红砖 
			dp[j] += dp[j-i],dp[j]%=mod;
	int ans = 0;
	int sum=h*(h-1)/2;			//搭塔要用多少块砖 
	for(int i=r;~i;i--)
	{
		if(sum-i>g)				//红的用完了,绿的不够补,接下来需要补的更多,退出 
			break;
		ans+=dp[i];
		ans%=mod;
	}
	cout << ans ;
} 
```


---

## 作者：BugGod (赞：1)

首先，我们发现这个积木塔的每一层连起来是一个等差数列（其实就是 $1\sim n$）。那么这个数列的和，也就是总块数，为 $\frac{n(n+1)}{2}$，而 $n$ 为高度，这个总块数又小于等于 $r+g$。

我们得到这个式子，可得出：$n$ 最大约为 $\sqrt{2(r+g)}$，据此，我们就可以大致求出 $n$ 的最大值，再使用循环，进而求出 $n$ 的最大值。有了层数，我们就可以 DP 了。

$dp_{i,j}$ 代表前 $i$ 层用 $j$ 块红色积木（绿色也可）的方案数。转移方程显然：$dp_{i,j}=(dp_{i,j}+dp_{i-1,j-i})\bmod p$，$p$ 为题目中的模数，即 $10^9+7$。

但是数据范围不允许我们这么做，所以考虑使用滚动数组。类似于 01 背包的，将第一维优化掉，最终得 $dp_j=(dp_j+dp_{j-i})\bmod p$。

统计答案时，我们枚举用多少块红色积木（绿色也可）并累加，答案为 $ \sum^r_{i=\max \lbrace 0,\frac{n(n+1)}{2}-g \rbrace } dp_i $。

---

## 作者：Hisaishi_Kanade (赞：1)

一个非常自然的想法是 $f(i,j,k)$ 表示从上到下前 $i$ 层堆完，红色用了 $j$ 个，绿色用了 $k$ 个的方案数。

不难想到的是，得到了 $i,j$ 完全可以推出 $k$ 而不需要多一维存储。

具体的，设 $g(i)=\sum\limits_{p=1}^i p=\dfrac {i(i+1)} 2$。则有关系 $k=g(i)-j$。

那么现在只需要存 $f(i,j)$。

然后直接考虑目前 $i$ 这一层用哪种颜色。

+ 如果用红色，只需要保证红色个数够即可。即 $f(i,j)\gets f(i,j)+[j\ge i\wedge j\le r]f(i-1,j-i)$。
+ 如果用绿色，也是类似的，上面已经推导过 $k=g(i)-j$，即 $f(i,j)\gets f(i,j)+[g(i)-j\le g]f(i-1,j)$。

这就推完转移了。初始化状态也是简单的。

很显然，若 $r=0$ 或者 $g=0$，答案为 $1$。

接下来，对于第一层，可以用两种颜色搞，则 $f(1,0)=f(1,1)=0$。

你会发现我还没说 $i$ 枚举到啥时候。

上面的转移很显然可以压掉一维，上一次转移好的存在 $f(j)$，我们按照转移再算出一个 $d(j)$。如果 $d(j)$ **取模前**全部为 $0$ 了，则肯定不会再有剩下的转移了，答案就是当前的 $\sum f$。否则还能转移啊，$f\gets d$ 即可。

很显然的发现，$i$ 的枚举量是 $\sqrt n$，总复杂度 $n\sqrt n$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=3e5+5, inf=2e9;
const ll illf=1e18, p=1e9+7;
int a[N], f[N], derta[N];
int qt, n, i, j, k, x, y, lim, res, flag;
#define tot(x) (x*(x+1)/2)
int main()
{
//	freopen("x.in", "r", stdin);
	x=read(); y=read();
	if(x==0 || y==0) {printf("%d\n", 1); return 0;}
	f[0]=f[1]=1;
	int i=1; while(true)
	{
		++i;
		lim=tot(i); rep(j, 0, lim) derta[j]=0; flag=false;
		rep(j, 0, lim) // f[j] 表示 red 用了 j 个
		{
			if(y>=lim-j) derta[j]+=f[j];
			if(j>=i && x>=j) derta[j]+=f[j-i];
			if(derta[j]!=0) flag=true;
			derta[j]%=p;
		} if(!flag) break;
		rep(j, 0, lim) f[j]=derta[j];
//		rep(j, 0, lim) printf("%d ", f[j]); puts("");
	}
	rep(i, 0, lim) (res+=f[i])%=p;
	printf("%d\n", res);
	return 0;
}
```

---

## 作者：ncwzdlsd (赞：1)

### 题意
给定 $r$ 个红块，$g$ 个绿块，要求：

1. 第 $i$ 行放 $i$ 块；

2. 每行同色。

问当堆放成最大高度时，有多少种可能的堆放方式。

### 题解

显然，放置 $h$ 行需要 $\dfrac{(h+1)h}{2}$ 个木块。

于是乎，$r+g\geq\dfrac{(h+1)h}{2}\Rightarrow2(r+g)\geq(h+1)h\Rightarrow2(r+g)>h^2$。

于是就有 $h=\sqrt{2r+2g}$，接着我们找符合条件的 $h$。

设 $dp(i,j)$ 为前 $i$ 行用了 $j$ 个红块的排列个数。

转移方程：（外层循环枚举 $i$ 表示第 $i$ 层，内层循环枚举 $j$ 表示红块数）

1. 如果 $i\leq j$，$dp(i,j)=dp(i-1,j)+dp(i-1,j-i)$，即第 $i$ 层不用红块和全部用红块的两种方案数；

2. 如果 $i>j$，$dp(i,j)=dp(i-1,j)$，即第 $i$ 层只能用绿块。

前 $i$ 层红块最多 $\max(\dfrac{i\times(i+1)}{2}-g,0)$ 个。

然后根据状态转移方程 DP 就可以解决问题啦！

代码就不放了，要自己思考哟！

---

## 作者：lovely_hyzhuo (赞：0)

根据等差数列可得，堆到第 $n$ 层总共需要 $\frac{n(n+1)}{2}$ 个块。转化一下就是 $h \leq \sqrt{2g+2r}$。这是个近似值。

定义 $dp_{i,j}$ 表示第 $i$ 层用 $j$ 块红砖的方案数。

起始状态当然是 $dp_{0,0}=1$。

相当于是一个 01 背包，选红色还是绿色。

那么 $dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-i}$。

但是数据范围只允许我们空间上 $O(n)$。

就像 01 背包一样压掉一维或滚动数组也行。

然后最大只能用 $g$ 块绿砖，这样判，对 $dp$ 数组进行加和，就是答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int r,g;
int dp[200010];
const int mod=1e9+7;
signed main()
{
	cin>>r>>g;
	int n=sqrt(2*(r+g));
	while(n*(n+1)<=2*(r+g))	 
		n++;
	dp[0]=1;
	for(int i=1;i<n;i++)
		for(int j=r;j>=i;j--)
			dp[j]+=dp[j-i],dp[j]%=mod;
	int ans=0;
	for(int i=r;i>=0;i--)
	{
		if(n*(n-1)/2-i>g)
			break;
		ans+=dp[i],ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

