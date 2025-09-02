# Robot on Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/keyence2021/tasks/keyence2021_c

$ H $ 行 $ W $ 列のマス目があります。上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ と書くことにします。 それぞれのマスには `R`, `D`, `X` のいずれかの文字を書き込むことができます。はじめ、どのマスにも文字は書き込まれていません。

すぬけ君は $ K $ 個のマスを選んで文字を書き込みました。 $ i $ 番目に文字を書き込んだマスは $ (h_i,w_i) $ で、書き込んだ文字は $ c_i $ でした。

残りのマスへの文字の書き込み方は $ 3^{HW-K} $ 通りあります。それぞれの場合について以下の問題の答えを計算し、その総和を $ 998244353 $ で割ったあまりを求めてください。

> 上記のマス目上を移動可能なロボットがあります。 ロボットは $ (i,j) $ にいるとき、$ (i+1,j),(i,j+1) $ のいずれかに移動することができます。 ただし、$ (i,j) $ に `R` と書かれていた場合は $ (i,j+1) $ にのみ、`D` と書かれていた場合は $ (i+1,j) $ にのみ移動することができます。`X` と書かれていた場合はどちらにも移動可能です。
> 
> ロボットを $ (1,1) $ に設置したとき、ロボットがマス目の外に出ずに $ (H,W) $ に到達するようなロボットの移動経路は何通りありますか？ただし、ロボットは $ (H,W) $ に到達した時点で停止するものとします。
> 
> ここで、$ 2 $ つの移動経路が異なるとはロボットが通ったマスの集合が異なることをいいます。

## 说明/提示

### 制約

- $ 2\ \leq\ H,W\ \leq\ 5000 $
- $ 0\ \leq\ K\ \leq\ \min(HW,2\ \times\ 10^5) $
- $ 1\ \leq\ h_i\ \leq\ H $
- $ 1\ \leq\ w_i\ \leq\ W $
- $ i\ \neq\ j $ ならば $ (h_i,w_i)\ \neq\ (h_j,w_j) $
- $ c_i $ は `R`, `D`, `X` のいずれか

### Sample Explanation 1

\- $ (1,2) $ のみまだ文字が書き込まれていません。 - `R` を書いたとき、ロボットが $ (H,W) $ に到達するようなロボットの移動経路は $ 1 $ 通りです。 - `D` を書いたとき、ロボットが $ (H,W) $ に到達するようなロボットの移動経路は $ 2 $ 通りです。 - `X` を書いたとき、ロボットが $ (H,W) $ に到達するようなロボットの移動経路は $ 2 $ 通りです。 - これらの総和である $ 5 $ を出力してください。

### Sample Explanation 3

\- $ 998244353 $ で割ったあまりを求めるのを忘れずに。

## 样例 #1

### 输入

```
2 2 3
1 1 X
2 1 R
2 2 R```

### 输出

```
5```

## 样例 #2

### 输入

```
3 3 5
2 3 D
1 3 D
2 1 D
1 2 X
3 1 R```

### 输出

```
150```

## 样例 #3

### 输入

```
5000 5000 10
585 1323 R
2633 3788 X
1222 4989 D
1456 4841 X
2115 3191 R
2120 4450 X
4325 2864 X
222 3205 D
2134 2388 X
2262 3565 R```

### 输出

```
139923295```

# 题解

## 作者：Crazyouth (赞：1)

## 分析

翻译难评。

注意到这题很像一个 dp，于是考虑 $dp_{i,j}$ 表示从 $(1,1)$ 走到 $(i,j)$ 的方案数，如果 $(i,j)$ 有写好的字符，那么这和正常 dp 无异；如果这里没有字符，注意到不管这个 dp 值将来被哪个 dp 值转移过去，这个地方都只能填 `X` 或者往转移处的方向，也就是说这个格子只能选两种字符，即 $dp_{i,j}$ 应当乘上 $\frac{2}{3}$。

因此 dp 式子是

$$dp_{i,j}=\begin{cases}
(f_{i,j}+g_{i,j})\times h_{i,j} & i>1 且 j>1\\
f_{i,j}\times h_{i,j} & i>1 且 j=1\\
g_{i,j}\times h_{i,j} & j>1 且 i=1\\
3^{HW-k} & i=1 且 j=1
\end{cases}$$

其中

$$f_{i,j}=\begin{cases}
dp_{i-1,j} & (i-1,j) 上的字符不是 R\\
0 & otherwise
\end{cases}$$

$$g_{i,j}=\begin{cases}
dp_{i,j-1} & (i,j-1) 上的字符不是 D\\
0 & otherwise
\end{cases}$$

$$h_{i,j}=\begin{cases}
\frac{2}{3} & (i,j) 上没有字符\\
1 & otherwise
\end{cases}$$

最后输出 $dp_{H,K}$ 即可。

**注意：十年 OI 一场空，long long 开多见祖宗。**

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int qpow(int b,int p)
{
	int ret=1;
	while(p)
	{
		if(p&1) ret=ret*b%mod;
		b=b*b%mod;
		p>>=1;
	}
	return ret;
}
short a[5010][5010];int dp[5010][5010];
signed main()
{
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)
	{
		int x,y;
		char c;
		cin>>x>>y>>c;
		a[x][y]=(int)c; 
	}
	dp[1][1]=qpow(3,n*m-k);
	//int inv3=qpow(3,mod-2);
	//cout<<"!:"<<inv3<<'\n';
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		if(i+j==2) continue;
		dp[i][j]=(a[i-1][j]!=(int)('R'))*dp[i-1][j]+(a[i][j-1]!=(int)('D'))*dp[i][j-1];
		dp[i][j]%=mod;
		if(!a[i][j]) dp[i][j]*=665496236;
		dp[i][j]%=mod;
	} 
	cout<<dp[n][m];
}

---

## 作者：11400F (赞：0)

这种情况只能 dp。

首先考虑每一个格子都写了字母的情况（也就是普通情况）。

设这个格子坐标为 $(i,j)$，那么他的转移就为：

- 如果这个格子的字母为 $R$，那么 $dp_{i,j+1}$ 加上 $dp_{i,j}$，就是向右移动。

- 如果这个格子的字母为 $D$，那么 $dp_{i+1,j}$ 加上 $dp_{i,j}$，就是向下移动。
- 如果这个格子的字母为 $X$，那么 $dp_{i+1,j}$ 和 $dp_{i,j+1}$ 都加上 $dp_{i,j}$，就是既可以向下走也可以向右走。

初始值设置 $dp_{1,1} = 1$，就可以算出结果，为 $dp_{H, W}$。

---

现在再考虑空格子。我们给初始值 $dp_{1,1}$ 设置为 $3^{HW-K}$，就是所有情况的总数。

分析一下，发现每一个空格子的情况就是上面列举的那 $3$ 种。

所以在转移时，转移向每一个方向的值就应该为 $\frac{dp_{i,j}}{3}$。

然后把上面的 $3$ 种情况综合一下，就变为了：

- 如果这个格子的字母为空，那么 $dp_{i+1,j}$ 和 $dp_{i,j+1}$ 都加上 $2 \times \frac{dp_{i,j}}{3}$。

最后求出 $dp_{H,W}$ 即可。

---

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define add(x,y) ((x+y>=mod)?x+y-mod:x+y)
typedef long long ll;
const ll mod = 998244353;

ll ksm(ll bas, ll x){
    ll ans = 1;
    while(x){
        if(x&1) ans = ans * bas % mod;
        bas = bas * bas % mod;
        x >>= 1;
    }
    return ans;
}
int n, m, k;
const int N = 5004;
char s[N][N];
ll ans[N][N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n>>m>>k;
    int x, y;
    for(int i=1;i<=k;i++){
        cin>>x>>y;
        cin>>s[x][y];
    }
    ll bas = ksm(3, n*m-k); //初始值
    ll inv3mul2 = ksm(3, mod-2)*2%mod; //这里把他综合到了一起。其实就是÷3×2。
    ans[1][1] = bas;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j] == 'D'){
                ans[i+1][j] = add(ans[i+1][j], ans[i][j]);
            }else if(s[i][j] == 'R'){
                ans[i][j+1] = add(ans[i][j+1], ans[i][j]);
            }else if(s[i][j] == 'X'){
                ans[i+1][j] = add(ans[i+1][j], ans[i][j]);
                ans[i][j+1] = add(ans[i][j+1], ans[i][j]);
            }else{
                ans[i][j+1] = add(ans[i][j+1], ans[i][j]*inv3mul2%mod);
                ans[i+1][j] = add(ans[i+1][j], ans[i][j]*inv3mul2%mod);
            }
        }
    }
    cout<<ans[n][m];
    return 0;
}
```

以上。

---

## 作者：_determination_ (赞：0)

简单 dp。

我们考虑一下一条路径的贡献。设路径上的空点数量为 $x$，路径外的空点数量为 $y$。那么贡献就是 $2^x3^y$。

那么我们就可以开始 dp。设 $f_{x,y}$ 表示到达 $(x,y)$ 时的贡献。

$f_{x,y}=f_{x-1,y}\times 2+f_{x,y-1}\times 2$。

然而这个 2 有的时候不能乘，因为这个 2 是路径上空点的数量。在来的点不是空点的时候就不能乘这个 2。

然后考虑怎样搞路径外的空点数量，显然往下走就统计左侧的空点数量，往右走就统计上面的空点数量就可以不重不漏了。记得最后判一下终点是否为空。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define endl '\n'
using namespace std;
const int mod=998244353,inf=0x3f3f3f3f3f3f3f3f;
const int N=5010,M=2e5+10;
long long f[N][N];
int s[N][N];
int op[N][N],n,m,k;
int calc(int x1,int y1,int x2,int y2)
{
	int ans=s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
	return ans;
}
int pw[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	freopen("bot.in","r",stdin);
	freopen("bot.out","w",stdout);
	cin >> n >> m >> k;
	while(k--)
	{
		int x,y;
		char ch;
		cin >> x >> y >> ch;
		if(ch=='D')op[x][y]=1;
		if(ch=='R')op[x][y]=2;
		if(ch=='X')op[x][y]=3;
	}
	for ( int i = 1 ; i <= n ; i++ )
	{
		for ( int j = 1 ; j <= m ; j++ )
		{
			s[i][j]=op[i][j]==0;
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+s[i][j];
		}
	}
	pw[0]=1;
	for ( int i = 1 ; i < N ; i++ )pw[i]=1ll*pw[i-1]*3%mod;
	f[1][1]=1;
	for ( int i = 1 ; i <= n ; i++ )
	{
		for ( int j = 1 ; j <= m ; j++ )
		{
			if(i!=1&&op[i-1][j]!=2)
				f[i][j]+=1ll*f[i-1][j]*(op[i-1][j]==0?2:1)*pw[calc(i,1,i,j-1)]%mod;
			if(j!=1&&op[i][j-1]!=1)
				f[i][j]+=1ll*f[i][j-1]*(op[i][j-1]==0?2:1)*pw[calc(1,j,i-1,j)]%mod;
			f[i][j]%=mod;
//			cout << f[i][j] << " ";
		}
//		cout << endl;
	}
	cout << (1ll*f[n][m]*(op[n][m]==0?3:1))%mod;
	return 0;
}
/*
n=5000我是人机
完蛋还是不会
对于每一条路径，他的贡献是
2^路径上空节点数 * 3^路径外空节点数
终点不算入路径内 
so?
f[x][y]为路径到了(x,y)的方案数
f[x][y]=f[x-1][y]*(op[x-1][y]==0?2:1)*(3^ept[x-1][y+1~m])+
		f[x][y-1]*(op[x][y-1]==0?2:1)*(3^ept[x+1~n][y-1])
当然要限制一下转移，至少你填空之后不能往反方向走 
好好好，大样例挂了 
我是弱智 
f[x][y]=f[x-1][y]*(op[x-1][y]==0?2:1)*(3^ept[x][1~y-1])+
		f[x][y-1]*(op[x][y-1]==0?2:1)*(3^ept[1~x-1][y])
?还是过不去
哦哦这两种是等价的 
我靠没模啊 
哈哈了。 
*/
```

---

## 作者：Mu_leaf (赞：0)

# [洛谷题面](https://www.luogu.com.cn/problem/AT_keyence2021_c)

## [Atcoder题面](https://atcoder.jp/contests/keyence2021/tasks/keyence2021_c)

### [题面翻译]
有 $H$ 行 $W$ 列的格点。从上到第 $i$ 行，从左到第 $j$ 列的格写为 ($i$，$j$)。每个格子都可以写入 $R$，$D$，$X$ 中的任意一个字符。首先，每个格子都没有写文字。

你可以选择了 $K$ 个格写了文字。第 $i$ 个写入文字的格（$H_i,W_i$）,写入的文字是 $C_i$。在剩余的格上写文字的方法有 $3^{HW-K}$。

对于每种情况，请计算以下问题的答案：

求出其总和除以 $998244353$ 的余数。

有可在上述网格上移动的机器人。机器人在（$i,j$）时，可以移动到（$i+1,j$），($i,j+1$），（$i+1,j$），（$i,j+1$）中的任意一个。但是，如果（$i,j$）中写着 $R$，则只能在（$i,j+1$）中移动，如果写着 $D$，则只能在（$i+1,j$）中移动。写着 $X$ 的情况下都可以移动。

当机器人在（$1,1$）时，机器人不出网格而到达（$H,W$）的移动路径有几种？

注意：机器人在到达（$H,W$）时停止。

### [思路]


很容易知道：

机器人在所有字母填空方式中从（$1,1$）到（$H,W$）可采用的路径数之和等于以下值：

对于从（$1,1$）到（$H,W$）的所有路径，机器人可采用的字母书写方式数之和。

### （这里有点绕，可以先理解一下，再看后面的）

让我们试着找到后者，而不是处理前者。我们假设，从一个空正方形开始，两种移动都可用：向右和向下。

设 $dp[H][W][K]$ 是机器人可以从（$1,1$）到（$H,W$）穿过 $K$ 个空正方形的路径数，我们需要写下与机器人从该方块走的方向相对应的字母，对应机器人从该方格走过的方向。

#### 在其他方格上，我们可以写任何字母。

因此，答案是
 $$\sum_{1 \leq k \leq H+W} \mathrm{dp}(H,W,k) 2^{k}3^{HW-K-k}$$ 
可以发现是枚举 $3$ 个维度。

所以，一眼就看出发现时间会炸，于是：

考虑将 $3$ 维化为 $2$ 维。

在这里，我们可以在转换中将数字乘以 $\frac{1}{2}$。

而不是将 $k$ 作为状态的一部分最后，我们可以在 $O(H \times W)$ 时间内找到它。

可以发现这对于 $H,W \leq 5000$ 完全足够的。

### 特殊的：

可以尝试使用快速幂优化，再加上一点点组合数，同样可以 AC 这道题哦。

------------
这里只贴了使用快速幂优化的版本哦。

对于前面提到的基础版的二维数组就交给各位去处理了。

## $Code:$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=998244353;
ll n,m,k,f[5010][5010],a[5010][5010];
ll ksm(ll x,ll y){
	ll ans=1;
	for(int i=y;i;i>>=1){
		if(i&1)ans=ans*x%mod;
		x=x*x%mod;
	}
	return ans;
}
int main(){
	ll i,j,x,y,op;
	char s[10];
	scanf("%lld%lld%lld",&n,&m,&k);
	for(i=1;i<=k;i++){
		scanf("%lld%lld%s",&x,&y,s);
		if(s[0]=='R')a[x][y]=1;
		else if(s[0]=='D')a[x][y]=2;
		else a[x][y]=3;
	}
	f[1][1]=ksm(3,n*m-k);
	op=ksm(3,mod-2);
	for(i=1;i<=n;i++){
	 	for(j=1;j<=m;j++){
		 	if(i+j>2){
			 	if(i>1){
			 		if(!a[i-1][j])f[i][j]=(f[i][j]+f[i-1][j]*op%mod*2)%mod;
			 		 else if(a[i-1][j]!=1)f[i][j]=(f[i][j]+f[i-1][j])%mod;
			 	}
			 	if(j>1){
			 		if(!a[i][j-1])f[i][j]=(f[i][j]+f[i][j-1]*op%mod*2)%mod;
			 		 else if(a[i][j-1]!=2)f[i][j]=(f[i][j]+f[i][j-1])%mod;
			 	}
		 	}
		}	 
	}
	
	printf("%lld",f[n][m]);
}
```


---

