# 「YLLOI-R1-T4」枫

## 题目背景

![枫](bilibili:BV1ZP411T7CB)

## 题目描述

有一个 $n$ 行 $m$ 列的网格，你要在该网格上制造一棵树，要求：

- 该树的每个节点对应一个格子。
- 每个格子最多对应一个节点。
- 该树任意节点对应格子所处行数小于其任意儿子节点对应格子所处行数。（行数从上往下严格递增）

节点没有编号，即所有节点是相同的。

定义两棵树相同需满足的所有条件：

- 总节点数相同。
- 对应节点都位于同一格子。形式化地，设两棵树所有节点对应格子的集合分别为 $S_1,S_2$，则 $S_1=S_2$。
- 对应节点所有父子关系均相同。形式化地，使用 $x$ 表示一个格子，则 $\forall x\in S_1,S_2$，设其对应节点的儿子节点对应格子的集合分别为 $S_1{'},S_2{'}$，则 $S_1{'}=S_2{'}$。

问一共能制造出多少种不同的树，答案对 $10^9+7$ 取模。

## 说明/提示

#### 【样例解释#1】

下图为所有不同的树：

![](https://cdn.luogu.com.cn/upload/image_hosting/84kk9yiu.png)

#### 【样例解释#2】

- 共有 $6$ 种不同的 $1$ 个节点的树。
- 共有 $12$ 种不同的 $2$ 个节点的树。
- 共有 $22$ 种不同的 $3$ 个节点的树。
- 共有 $28$ 种不同的 $4$ 个节点的树。
- 共有 $18$ 种不同的 $5$ 个节点的树。
- 共有 $0$ 种不同的 $6$ 个节点的树。

因此共有 $6+12+22+28+18+0=86$ 种不同的树。

#### 【数据范围】

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$n=2$。
- Subtask 2（10 pts）：$m=1$。
- Subtask 3（10 pts）：$n,m \le 3$。
- Subtask 4（20 pts）：$n,m \le 20$。
- Subtask 5（20 pts）：$n,m \le 50$。
- Subtask 6（30 pts）：无特殊限制。

对于全部数据，保证：$1\le n,m\le80$。

## 样例 #1

### 输入

```
2 2```

### 输出

```
10```

## 样例 #2

### 输入

```
3 2```

### 输出

```
86```

# 题解

## 作者：lovelish (赞：18)

看到题目后，很容易想出使用动态规划，那么我们试着用动态规划解决该题。

发现数据范围比较小，于是我们不妨大胆一些定义状态。发现动态规划可以逐行转移，因为确定了前若干行的状态后，便不需要再更改，只需要再考虑后面的，无后效性。那么第一个维度就显然可以使用行数。

因为列与列之间没有明显的区分度，所以我们只能使用节点数定义第二维度。只定义该行的节点数显然是不够的，因为该行每一个节点的父节点选择是之前行的所有节点，因此第二维度定义为当前总节点数。

那么定义 $f_{i,j}$ 表示在 $i$ 行 $m$ 列的网格中，根节点在第一行且总节点数为 $j$ 个的总方案数。

边界很显然，当只有一个根节点时一共有 $m$ 种方案，即 $f_{i,1}=m$。

目标也很显然，所以情况相加即为答案：

$$

\sum_{i=1}^n\sum_{j=1}^{n\times m}f_{i,j}

$$

接下来我们看转移。

对于每一个 $f_{i,j}$，枚举第 $i$ 行的节点数量相加即可。当该行有 $k$ 个节点时，这 $k$ 个节点有不同的位置选择，即从 $m$ 个格子中选择 $k$ 个，即 $\binom{m}{k}$，对于每个节点而言，其可以选择任意一个之前行的节点作为自己的父亲，因为共有 $j-k$ 种选择，一共 $k$ 个节点，一共就是 $(j-k)^k$ 种选择。那么转移式即：

$$
 
f_{i,j}=\sum_{k=0}^{m}f_{i-1,j-k}\times \binom{m}{k}\times (j-k)^k

$$

组合数和乘方参数都比较小，因此可以直接预处理出来。那么总时间复杂度即 $\mathcal O(n^2m^2)$。

于是该题就写完了，不过有一些小细节以及一些小常数优化，这里就不再说明。

---

## 作者：I_will_AKIOI (赞：5)

我们发现每个节点的父亲肯定在这个点的上面，具体在哪一行是无所谓的。因此考虑 dp，设 $f_{i,j}$ 表示当前处理到了第 $i$ 行，前 $i$ 行一共有 $j$ 个节点的树的个数。

接着考虑转移。为了防止越界，这里枚举的 $j$ 是前 $i-1$ 行节点的个数。

枚举第 $i$ 行的节点数 $k$，这 $k$ 个点每个都可以在第 $[1,i-1]$ 行的 $j$ 个节点中选择一个作为父亲，因此选择方案数就是 $j^k$。而第 $i$ 行的 $k$ 个点的排列方案数是 $C_m^k$。最后别忘了乘上原有的方案数 $f_{i-1,j}$，就得到了转移方程，$f_{i,j+k}=\displaystyle\sum_{k=0}^m f_{i-1,j}\cdot C_m^k \cdot j^k$。最后答案就是所有 $f_{i,j}$ 的值相加。

时间复杂度为 $O(n^2m^2\log m)$，可能过不了，瓶颈在于快速幂和取模，因此预处理一下 $j^k$ 这一项就可以优化到 $O(n^2m^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define N 85
using namespace std;
int n,m,ans,f[N][N*N],c[N][N],p[N*N][N];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	f[1][1]=m,c[0][0]=1;
	for(int i=1;i<=m;i++)//预处理组合数
	{
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	for(int i=1;i<=n*m;i++) p[i][0]=1;
	for(int i=1;i<=n*m;i++)	for(int j=1;j<=m;j++) p[i][j]=p[i][j-1]*i%mod;//预处理快速幂
	for(int i=2;i<=n;i++) for(int j=1;j<=(i-1)*m;j++) for(int k=0;k<=m;k++) f[i][j+k]=(f[i][j+k]+f[i-1][j]*c[m][k]%mod*p[j][k])%mod;
	for(int i=1;i<=n;i++) for(int j=0;j<=i*m;j++) ans+=f[i][j];
	cout<<ans%mod;
	return 0;
}
```

---

## 作者：ycy1124 (赞：4)

### 题意
在 $n\times m$ 的矩阵里，现在要求你造出一颗树。一颗合法树需要满足每个节点对应一个格子，一个格子只能对应一个节点，每个节点的父亲必须在他的上面。两个相同的树当且仅当节点对应的格子的集合相等且每个节点的父亲节点相同。要求能构造出多少种不同的树。
### 思路
观察数据范围发现 $n,m$ 很小，考虑 dp。首先肯定是从上往下的 dp，因为想计算下面的方案数时需要用到上面的总点数。我们设 $dp_{i,j}$ 表示在前 $i$ 行，总共有 $j$ 个节点的不同的树的个数。转移时枚举三个变量，$i$ 表是行数，$j$ 表示这一行选 $j$ 个格子做节点，$k$ 表示总点数。转移方程为：
$$
dp_{i,k}=\sum_{i=2}^{n}\sum_{j=0}^{m}\sum_{k=j+1}^{(i-1)\times m+1}dp_{i-1,k-j}\times\dbinom{m}{j}\times (k-j)^j
$$
首先 $dp_{i-1,k-j}$ 是从这个状态转移过来的。$\dbinom{m}{j}$ 表示在 $m$ 个格子里选 $j$ 个的方案数。每个节点可以在上面 $k-j$ 个节点里面选一个做父亲，所以最后还要乘上 $(k-j)^j$。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define md 1000000007
using namespace std;
int n,m,sum[850],inv[850],dp[850][6450];
inline int power(int w){//求逆元
    int qwq=md-2,base=w,Sum=1;
    while(qwq){
        (qwq&1)?Sum*=base,Sum%=md:qwq;
        qwq>>=1;
        base*=base;
        base%=md;
    }
    return Sum;
}
inline int Power(int a,int b){//快速幂
    int qwq=a,base=b,Sum=1;
    while(qwq){
        (qwq&1)?Sum*=base,Sum%=md:qwq;
        qwq>>=1;
        base*=base;
        base%=md;
    }
    return Sum;
}
inline void getsum(int n){//预处理阶乘
	sum[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]*i%md;
    }
}
inline void getinv(int n){//预处理逆元
	for(int i=1;i<=n;i++){
		inv[i]=power(sum[i]);
	}
}
inline int C(int n,int m){//组合数
	return sum[n]*inv[n-m]%md*inv[m]%md;
}
signed main(){
	getsum(80),getinv(80);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		dp[i][1]=m;//赋初值
	}
	for(int i=2;i<=n;i++){//行数 
		for(int j=0;j<=m;j++){//这行选的格子数 
			for(int k=1;k<=(i-2)*m+1;k++){//上面的总点数
				dp[i][k+j]+=C(m,j)*dp[i-1][k]%md*Power(j,k)%md;
				dp[i][k+j]%=md;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=(n-1)*m+1;i++){
		ans+=dp[n][i];//累加答案
		ans%=md;
	}
	cout<<ans%md;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/216006501)。

---

## 作者：zhoujiefu (赞：4)

这里给出一种与其他题解解题路径不太相同的 DP 。

设 $dp_{i,j,k}$ 表示到了第 $i$ 行总共放了 $j$ 个点并在第 $i$ 行放了 $k$ 个点的方案数。得到的暴力 DP 长下面这个样子：

$dp_{i,j,k}=\sum_{x=0}^m dp_{i-1,j-k,x}\times \dbinom{m}{k}\times (j-k)^k$ 。因为 $j$ 的枚举范围大约是 $O(nm)$ 的，所以这个 DP 实际上是 $O(n^2m^3)$ 的，过不了。考虑优化。$\sum$ 在更新当前状态的时候是已知的，所以我们令 $sum_{i,j}=\sum dp_{i-1,j-k,x}$ ，那么我们就可以 $O(1)$ 转移了，时间复杂度 $O(n^2m^2)$ 。具体实现见代码。


```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=88;
const int mod=1e9+7;
inline int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}

int n,m,ans;
int frac[N*N],inv[N*N],dp[N][N*N][N],sum[N][N*N];
inline int C(int n,int m){
	return frac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	frac[0]=1;
	rep(i,1,n*m) frac[i]=frac[i-1]*i%mod;
	inv[n*m]=qpow(frac[n*m],mod-2);
	for(int i=n*m-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	dp[1][1][1]=m,sum[1][1]=m;
	rep(i,2,n){
		rep(j,1,n*m){
			dp[i][j][0]=sum[i-1][j];
			rep(k,1,m){
				dp[i][j][k]=sum[i-1][j-k]*C(m,k)%mod*qpow(j-k,k)%mod;
				dp[i][j][k]%=mod;
			}
			rep(k,0,m){
				sum[i][j]+=dp[i][j][k];
				sum[i][j]%=mod;
			}
		}
	}
	rep(i,1,n){
		rep(j,1,n*m) ans+=sum[i][j],ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Vae_L (赞：3)

~~所以为什么会有【数据删除】出题人 T3 放诈骗啊。~~

时隔一年好不容易报了场 rated，结果被诈骗题创飞了，幽默啊。

更幽默的是 T4 是这种【数据删除】题。

完了再继续说我可能真要将【数据删除】换成一些过不了审的语言了。

所以我们开始这篇题解。

首先注意到 $n$ 和 $m$ 都只有 80，所以可能会想到 $n^4$ 这样的复杂度。

事实也确实是这样的复杂度。

考虑 dp，$dp_{i,j}$ 代表前 $i$ 行，填了 $j$ 个节点的方案数。

答案就是 $dp_{n,j}$ 的和，其中 $j$ 的范围为从 1 到 $n \times m$。

考虑转移。

首先，$dp_{i,j}$ 一定是从 $dp_{i-1,j-k}$ 转移而来，其中 $k$ 为枚举得到，代表含义是当前这一行填的节点个数。

由于该行有 $m$ 个位置，所以其实就是 $m$ 中选 $k$ 个的组合数了。

之后还有这 $k$ 个节点的父节点选择，根据题意，之前的 $j-k$ 个节点都可作为父节点，即 $k$ 个位置，每一个位置有 $j-k$ 个选择方式的方案数，也就是 $(j-k)^k$。

需要注意的是，这里的幂次需要预处理出来，直接在里面快速幂会 T 掉。

~~所以为啥这不是 T3 啊，这【数据删除】比 T2 还水啊。~~

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,dp[8000][8000],c[8000][8000],ans,fast[8000][8000];
const int MOD=1e9+7;
int solve(int a,int n,int p)
{
	int s=1;
	while(n)
	{
		if(n&1) s=(s*a)%p;
		a=(a*a)%p;
		n=n>>1; 
	}
	return s;
}
signed main() 
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) dp[i][1]=m;
    c[0][0]=1;
    for(int i=1;i<=m;i++)
	{
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	}
	for(int i=1;i<=n*m;i++) fast[i][0]=1;
	for(int i=1;i<=n*m;i++)
	{
		for(int j=1;j<=m;j++) fast[i][j]=fast[i][j-1]*i%MOD;
	}
    for(int i=2;i<=n;i++)
    {
		for(int j=1;j<=i*m;j++)
		{
			for(int k=0;k<=min(j,m);k++)
			{
				dp[i][j]=(dp[i][j]+c[m][k]*dp[i-1][j-k]%MOD*fast[j-k][k]%MOD)%MOD;
			}
		}
	}
	for(int i=1;i<=n*m;i++) ans+=dp[n][i],ans%=MOD;
	cout<<ans%MOD;
    return 0;
}

---

## 作者：fish_love_cat (赞：3)

简单 dp，但是赛时数组开挂虚空调试 30min /fad

---

设 $f_{i,j}$ 表示总共填了 $i$ 行，填了 $j$ 个点的方案数。

转移时考虑枚举：当前行 $i$，除去当前行已填点数 $j$，当前行所填点数 $k$。

注意到之前所填的点必须与这行的点有连线关系，于是可以转化为 $j$ 个盒子装 $k$ 个球的问题，这是好做的，易得方案数为 $j^k$。

然后还有这行的点可以乱填，所以方案数又有 $C_m^k$。

于是有转移式：

$$f_{i,j+k}\gets f_{i,j+k}+f_{i-1,j}\times j^k \times C_m^k$$

最后还需要注意不一定从第一行相邻的顺序填下来，只需要保证占用 $i$ 行，所以方案数还要乘上 $C_n^i$。

然后就可以 $O(nmV)$ 做掉了，其中 $V$ 是所用点数。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
int dp[85][6405];
int A[85],inv[85];
#define flc_INF LLONG_MAX
int qpow(int a,int b,int p=flc_INF){
	int ans=1;
	if(b==0)return 1;
	while(b){
		if(b&1)ans*=a,ans%=p;
		a*=a,b>>=1,a%=p;
	}
	return ans;
}
int ni(int a,int p){return qpow(a,p-2,p);}
int C(int n,int m){//组合！
    return (A[n]*inv[m]%mod*inv[n-m]%mod);
}
void init_of_C(int N){//预处理上界
    A[0]=A[1]=1;
    for(int i=2;i<=N;i++)
    A[i]=A[i-1]*i%mod;
    for(int i=0;i<=N;i++)
    inv[i]=ni(A[i],mod);
}
int ans;
signed main(){
    int n,m;
    cin>>n>>m;
    init_of_C(85);
    dp[1][1]=m;
    for(int i=2;i<=n;i++)
    for(int j=1;j<=(i-2)*m+1;j++){
        for(int k=1,qp=j;k<=m;k++,qp*=j,qp%=mod)
        dp[i][j+k]=(dp[i][j+k]+dp[i-1][j]*qp%mod*C(m,k)%mod)%mod;
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n*m;j++)
        ans=(ans+(dp[i][j]*C(n,i))%mod)%mod;
    cout<<ans;
    return 0;
}
```

---

## 作者：xuchuhan (赞：2)

前言：第一次 AK 基础赛，写篇题解纪念。

回到这道题，不难想到 DP。

发现只要一个节点的父亲在它的上面即可，具体哪一层无所谓，所以可以设 $dp_{i,j}$ 表示当前到第 $i$ 层，前 $i$ 层一共有 $j$ 个结点的方案数。考虑转移。枚举当前层的结点个数 $k$，那么前 $i-1$ 层的结点个数就是 $j-k$，第 $i$ 层的 $k$ 个结点都可以任意选前 $i-1$ 层的 $j-k$ 个结点作父亲，那么方案数就是 $(j-k)^k$。同时当前层的 $k$ 个节点可以任意放置在当前层的 $m$ 个空格中，那么方案数就是 $\binom{m}{k}$，最后利用乘法原理，整合成转移：$dp_{i,j}=dp_{i-1,j-k}\times (j-k)^k\times \binom{m}{k}$。

大体架构就是这样，这里讲一下边界处理：因为不一定要从第一行开始放，也不一定要从最后一行结束放，所以要特别注意编辑处理。具体的，可以让 $dp_{i,j}$ 先继承 $dp_{i-1,j}$，即当前行不放，然后进行上文转移的时候将 $k$ 从 $1$ 开始枚举。同时，也存在在当前行开始放的情况，这时总共放 $1$ 个，这一个可以任意放在 $m$ 个空格中的一个，即 $dp_{i,1}=m$。最后统计答案时，直接计算第 $n$ 行的答案之和即可，即 $\sum_{i=1}^{n\times m}dp_{n,i}$。

这样时间复杂度是四次方带一个 $\log$ 的常数，$\log$ 的常数是求组合数和幂次的快速幂导致的。大概率会炸掉（赛时亲测，只有 $50$ 分）。考虑优化这个 $\log$ 的常数，可以暴力的将所有可能的组合数和幂次预处理出来，转移的时候直接用即可。

放一下赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=85,mod=1e9+7;
int n,m,ans,fac[N],dp[N][N*N],invf[N],fp[N*N][N];
int _fpow(int a,int b,int p){int ans=1;while(b){if(b&1)ans=ans*a%p;a=a*a%p,b>>=1;}return ans;}
int _inv(int x,int p){return _fpow(x,p-2,p);}
int C(int a,int b,int p){if(a<b)return 0;return (fac[a]*invf[b]%p*invf[a-b])%p;}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m,fac[0]=1;
	for(int i=1;i<=m;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=0;i<=m;i++)invf[i]=_inv(fac[i],mod);
	for(int i=1;i<=n*m;i++)for(int j=1;j<=m;j++)fp[i][j]=_fpow(i,j,mod);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i*m;j++){
			dp[i][j]=dp[i-1][j];
			if(j==1)dp[i][j]+=m,dp[i][j]%=mod;
			else for(int k=1;k<=min(m,j);k++)
				dp[i][j]+=dp[i-1][j-k]*C(m,k,mod)%mod*fp[j-k][k]%mod,dp[i][j]%=mod;
			if(i==n)ans+=dp[i][j],ans%=mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Amidst (赞：2)

## 思路

考虑 dp。

设计状态，不妨令 $dp_{i,j}$ 表示前 $i$ 行取 $j$ 个点的不同构树的数量。

由于 $n,m\le 80$，不妨令 $n$ 和 $m$ 同阶，考虑 $O(n^4)$ 级别做法。

不妨考虑第 $i$ 行，则枚举 $j$，考虑枚举该行取的节点数量 $k$，每次转移有

$$dp_{i+1,j+k}\gets dp_{i+1,j+k}+dp_{i,j}+\binom{m}{k}+j^k$$

感觉从 $i$ 转移到 $i+1$ 比从 $i-1$ 转移到 $i$ 好写。注意边界情况，$dp_{1,0}=1$，$dp_{1,1}=m$，$j$ 从 $1$ 开始转移，但是要继承上一层的方案。

可以预处理组合数，时间复杂度 $O(n^2m^2)$ 且跑不满。

## 代码

```cpp
#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define int long long
#define mod (int)(1e9+7)
#define __BEGIN_MULTITEST__ \
	signed T; \
	scanf("%d",&T); \
	while(T--) \
	{
#define __END_MULTITEST__ }
using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;
int n,m;
int dp[105][10005];
inline int quick_pow(int a,int b)
{
	if(!a||!b)
		return 1;
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=ret*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ret;
}
int fac[105],inv[105];
int C(int a,int b)
{
	return fac[a]*inv[b]%mod*inv[a-b]%mod;
}
signed main()
{
//	__BEGIN_MULTITEST__
	scanf("%lld%lld",&n,&m);
	fac[0]=1;
	for(int i=1;i<=m;i++)
		fac[i]=fac[i-1]*i%mod;
	inv[m]=quick_pow(fac[m],mod-2);
	for(int i=m-1;i>=0;i--)
		inv[i]=inv[i+1]*(i+1)%mod;
	dp[1][0]=1;
	dp[1][1]=m;
	for(int i=1;i<n;i++)
		for(int j=0;j<=i*m;j++)
		{
			if(!j)
				dp[i+1][1]=m;
			else
				for(int k=0;k<=m;k++)
					(dp[i+1][j+k]+=C(m,k)*dp[i][j]%mod*quick_pow(j,k)%mod)%=mod;
		}
	int ans=0;
	for(int i=1;i<=n*m;i++)
		(ans+=dp[n][i])%=mod;
	printf("%lld\n",ans);
//	__END_MULTITEST__
	return 0;
}
```

---

## 作者：M_CI (赞：1)

### Part0. 前言

好简单的 Div.3 T4。

[赛时 AC 记录](https://www.luogu.com.cn/record/215944967)

---

### Part1. 题意

给定一个 $n\times m$ 的网格图，在其中构建一棵有根树，使得父节点一定在子节点上方，求可构建多少棵不同的有根树。

---

### Part2. 思路

对于点 $A (i,j)$，我们发现只要点 $B (x,y)$ 满足 $x<i$，即可将 $B$ 作为 $A$ 的父节点。根据这一性质，我们发现对于第 $i$ 行的所有点，$1\sim i-1$ 行的所有点均可作为其父节点，而不用管位置关系。

因此，可设 $f_{i,j}$ 表示当前考虑第 $i$ 行、第 $1\sim i$ 行共有 $j$ 个点在树上。因为每一行都能作为根节点所在的行，所以初始时 $f_{i,1}=m$。

考虑转移。对于第 $i$ 行、第 $1\sim i-1$ 行共有 $j$ 个点在树上、第 $i$ 行有 $k$ 个点在树上的情况，$f_{i,j+k}$ 由 $f_{i-1,j}$ 转移而来、第 $i$ 行的 $k$ 个在树上的点可任选、其父节点也可任选，我们得到转移方程：

$$f_{i,j+k}=\sum\limits_{j=0}^{1+(i-2)\times m}\sum\limits_{k=0}^{m} f[i-1][j]\times\binom{m}{k}\times j^k$$

最终答案为 $\sum\limits_{i=1}^{n\times m} f_{n,i}$。

---

### Part3. 解释

枚举时 $1\le j\le 1+(i-2)\times m$ 是因为 $1\sim i-1$ 行必有一行只有一个根节点，其它行不定，所以不用枚举至 $(i-1)\times m$ 。

---

### Part4. 代码

为和思路保持一致，使用赛后修改的代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace rab {
    const int N=81,mod=1e9+7;
    int n,m,ans,c[N][N],f[N][N*N];
    long long g;

    inline int ksm (int x,int y,int z=mod) {
        int rs=1;
        while (y) {
            if (y&1) rs=1ll*rs*x%z;
            x=1ll*x*x%z,y>>=1;
        }
        return rs;
    }

    inline int main () {
        cin>> n>> m;
        for (int i=0;i<=m;i++) {
            c[i][0]=1;
            for (int j=1;j<=i;j++)
                c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
        }
        for (int i=1;i<=n;i++) f[i][1]=m;
        for (int i=2;i<=n;i++) {
            for (int j=0;j<=1+(i-2)*m;j++) {
                for (int k=0;k<=m;k++) {
                    g=1ll*f[i-1][j]*c[m][k];
                    if (g>=mod) g%=mod;
                    g=1ll*g*ksm (j,k);
                    if (g>=mod) g%=mod;
                    f[i][j+k]=(f[i][j+k]+g)%mod;
                }
            }
        }
        for (int i=1;i<=n*m;i++) ans=(ans+f[n][i])%mod;
        cout<< ans;
        return 0;
    }
}

int main () {
    ios::sync_with_stdio (0);
    cin.tie (0);cout.tie (0);
    return rab::main ();
}
```

---

完结撒花！

---

## 作者：WZwangchongming (赞：1)

### 前言

被一路向北硬控 3h，350pts 遗憾离场。


---

### 题意

我们需要在 $n \times m$ 的网格中构造满足以下条件的树：

> - 父节点所在行严格小于子节点所在行。
> - 每个格子最多一个节点。
> - 所有节点构成一棵树（连通且无环）。

求不同结构的树的数量，两棵树相同当且仅当节点位置和父子关系完全相同。答案对 $10^9+7$ 取模。

### 数据范围

对于全部的数据，$1 \le n,m \le 80$。


---

### Solution

考虑到 $n$ 和 $m$ 都很小，爆搜即可获得 30pts。进行一些剪枝就可以再获得 20pts。

但是这题看起来就很能 dp 的样子。

设 $f_{i,j,k}(k \in \set{0,1})$ 表示当前处理到第 $i$ 行，还有 $j$ 个可用父节点，是否已经存在根节点的方案数（$k=0$ 表示未选根，$k=1$ 表示已选根）。

接下来考虑转移。

转移时，对于每一行：

>- 如果 $k=0$，可以选择在该行不选根，或者选一个根。
>- 如果 $k=1$，可以选 $0$ 到 $m$ 个子节点，每个子节点连接到 $k$ 个父节点中的一个。

如果要选根的话，方案数即为 $C(m,1)$。

如果要扩展子树，即选子节点的话，那我们再枚举选择子节点的个数 $s$，因为每个子节点都有 $j$ 种父节点的选择方式，那么方案数就是 $C(m,s) \times j^s$。

那么我们预处理出组合数，再写一个快速幂就好了。

初始状态即未选任何节点。最后统计答案只需要把所有选了根的方案数累加起来即可。

做完了。注意如果三维 dp 数组的话，空间内存有一点点紧，可以替换为两个二维数组。

时间复杂度 $O(n^2m^2\log m)$，跑得很快。

---

Main code：


```cpp
    n = read();
    m = read();
    vector<vector<int> > C(m + 1, vector<int>(m + 1, 0));
    for(int i = 0; i <= m; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
    }
    vector <vector<int> > f(n * m + 1, vector<int>(2, 0));
    f[0][0] = 1;
    for(int i = 0; i < n; i++) {
        vector<vector<int> > g(n * m + 1, vector<int>(2, 0));
        for(int j = 0; j <= n * m; j++) {
            for(int k = 0; k <= 1; k++) {
                if(f[j][k] == 0) continue;
                if(k == 0) {
                    g[j][0] = (g[j][0] + f[j][0]) % P;
                    if(m < 1) continue;
                    if(j + 1 > n * m) continue;
                    g[j + 1][1] = (g[j + 1][1] + f[j][0] * C[m][1]) % P;
                } 
				else {
                    for(int s = 0; s <= m; s++) {
                        int w = C[m][s] * qpow(j, s) % P;
                        if(j + s > n * m) continue;
                        g[j + s][1] = (g[j + s][1] + f[j][1] * w) % P;
                    }
                }
            }
        }
        f = g;
    }
    int ans = 0;
    for(int i = 1; i <= n * m; i++) ans = (ans + f[i][1]) % P;
    printf("%d\n", ans);
```

---

## 作者：Eason_cyx (赞：1)

第 $\bf{104}$ 篇题解。

考虑 $f_{i,j}$ 表示前 $i$ 排放 $j$ 个结点的方案数，容易得转移：

$$f_{i,j}=\displaystyle\sum_{k=1}^{j}f_{i-1,j-k} \times \operatorname{C}_{m}^{k}\times (j-k)^{k}$$

边界条件：$f_{1,1}=1,f_{i,0}=1$。

将组合数用 $O(m \log m)$ 时间预处理，然后直接转移，复杂度是 $O(m \log m+n^3m^2\log nm)$。可以获得 $50$ 分。

然后你会发现 $k$ 其实最大只能取到 $m$。所以把式子改一下，变成：

$$f_{i,j}=\displaystyle\sum_{k=1}^{\min(j,m)}f_{i-1,j-k} \times \operatorname{C}_{m}^{k}\times (j-k)^{k}$$

就可以少一个 $n$。于是可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
ll qpow(ll a, ll b) { if(a == 0) return (b == 1 ? 1 : 0);
    ll c = 1;
    while(b) { if(b & 1) c = (c * a) % mod; a = (a * a) % mod; b >>= 1; } return c;
} ll facinv[805], fac[805], comb[805], f[805][6405];
ll inv(ll x) { return qpow(x, mod-2); }
signed main() {
    int n, m; cin >> n >> m;
    ll x = 1; for(int i = 1;i <= m;i++) {
        x = (x * i) % mod; 
        facinv[i] = inv(x), fac[i] = x;
    } for(int i = 2;i < m;i++) {
        comb[i] = fac[m] * facinv[i] % mod * facinv[m-i] % mod;
    } comb[1] = m; comb[m] = 1; f[1][1] = m; comb[0] = 1;
    for(int i = 1;i <= n;i++) f[i][0] = 1;
    for(int i = 2;i <= n;i++) {
        for(int j = 1;j <= m * (i-1) + 1;j++) {
            for(int k = 0;k <= min(j, m);k++) {
                f[i][j] = (f[i][j] + f[i-1][j-k] * comb[k] % mod * qpow(j-k, k) % mod) % mod;
            }
        }
    } ll ans = 0; for(int i = 1;i <= n * m;i++) ans = (ans + f[n][i]) % mod;
    cout << ans << endl;
    // for(int i = 1;i <= n;i++) {
    //     for(int j = 1;j <= m * (i-1) + 1;j++) {
    //         cout << "f[" << i << "][" << j << "]: " << f[i][j] << endl;
    //     }
    // }
    return 0;
}
```

笑话：赛时本人没有将 $k$ 和 $m$ 取最小，成功被卡。赛后经过 irr74 的嘟嘟嘟指点通过了一道棒棒糖题，再接再厉！！！1

---

## 作者：Hoks (赞：0)

## 前言
比较简单的题。

难度瓶颈应该在组合数上了。
## 思路分析
$n,m$ 这么小，直接暴力 dp 上就行了。

考虑到我们的树是一行一行连下来的，所以我们考虑一行一行的转移。

或者说，你可以发现一行之间的点其实是等价的，可以合并在一起考虑。

为什么呢，因为你考虑到同一行的点无法互相连边，他们连边只和前面几行的点有关。

所以这一行的点从和上面的点连边的角度来考虑，是相同的。

然后是考虑怎么数这个方案数的问题，如果我们直接定义 $f_i$ 表示填到第 $i$ 行的方案数，数不出接下来和前面行的点连边有多少种方案数。

所以再把点数也扔进状态里去，$f_{i,j}$ 表示前 $i$ 行用了 $j$ 个点的方案数。

答案就是 $\sum\limits_{j=1}^{nm} f_{n,j}$。

那么我们有转移：
$$f_{i,j}\leftarrow k^{j-k}\binom{m}{j-k}f_{i-1,k}$$

其中 $\max(0,j-m)\le k\le j$，因为每行最多只能填 $m$ 个点。

这个式子的意思就是前 $i-1$ 行已经填了 $k$ 个点，再在这行填上 $j-k$ 个点变成状态 $j$。

$\binom{m}{j-k}$ 表示我们从第 $i$ 行 $m$ 个点中选出了 $j-k$ 个点连入树中，而这 $j-k$ 个点，每个点认父亲都有 $k$ 种可能，所以总的转移方程就是上式。

当然到这里还没做完，这样写无法通过样例。

为什么呢？

观察发现我们跑出来的 $f_{2,2}=6$，实际为 $4$。

仔细看一下就知道错在哪了。

**当这一行是第一行填入点的行时，只能填入一个点。**

记得特判下转移方程 $k=0$ 的时候改写成赋值为 $[j=1]m$ 就可以了。

详细的可以见代码。
## 代码
复杂度是 $O(n^2m^2\log m)$ 的，瓶颈在快速幂上，实际上是可以先预处理的，不过猫猫懒了能过就行。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=80+10,M=2,V=80,mod=1e9+7,INF=1e10;
int n,m,a[N],f[N][N*N],fac[N],inv[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='?'||c=='<'||c=='='||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int ksm(int x,int y,int mod)
{
    int res=1;if(x==0) return 1;
    while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;}
    return res;
}
inline int C(int n,int m)
{
    if(n<0||m<0||n-m<0) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
inline void prework(int V)
{
    for(int i=fac[0]=1;i<=V;i++) fac[i]=fac[i-1]*i%mod;
    inv[V]=ksm(fac[V],mod-2,mod);
    for(int i=V-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
inline void solve()
{
	n=read(),m=read();int ans=0;f[1][1]=m;
	for(int i=2;i<=n;i++) for(int j=1;j<=i*m;j++)
		for(int k=max(0ll,j-m);k<=j;k++)
			if(k!=0) f[i][j]=(f[i][j]+f[i-1][k]*C(m,j-k)%mod*ksm(k,j-k,mod))%mod;
			else f[i][j]=(j==1)*m;
	for(int i=1;i<=n*m;i++) ans=(ans+f[n][i])%mod;print(ans);
}
signed main()
{
	int T=1;prework(V);
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：ztd___ (赞：0)

**注意：本文的“方案数”一词指代的不是同一个东西的方案数，请谨慎辨别。**

首先可以发现：我们没必要考虑每一行的结点如何排列，只需要知道每行的结点个数即可。

证明：
> 只要某一行上的结点数量确定（假设等于 $x$），那么，通过排列这一行所产生的方案数是固定的，即 $C^x_m$（从 $m$ 个空位中选择 $x$ 个，让它们变成树的结点）。
>
> 然后，每一行的结点的排列方式对于后面和前面的点也是没有影响的。
>
> 对于下面的点：我们计算方案时，只关心下面的点能接在多少个点的后面（即能成为多少个点的儿子），而父节点具体的位置不会对方案数产生影响。
>
> 对于上面的点：感性理解一下。假设上面的点位置已经固定，我们从下面的点开始构树时，只需要考虑下面的点能成为多少个点的儿子，而在哪一个位置成为儿子节点对总方案数是不会有影响的。

于是可以考虑搜索。由于根很特殊，所以我们把根单独算。枚举**根下面的**每一行放多少个点，然后分开计算答案。

然后，对于其中的某一层，我们设上面总共有 $s$ 个点（这意味着这一层的点可以成为多少个点的儿子结点），然后上面那些点构造出来的树总共有 $w$ 种形态，且我们打算在这一行上面放 $i$ 个点。

显然，到下一行的时候 $s$ 会加上 $i$，我们考虑 $w$ 如何变化。

我们发现下一行的 $w$ （即从第一行到这一行这一棵“部分树”的形态数量）被 $3$ 个因素影响着：
1. 上面所有点的排列方案数（即这一行的 $w$）。
2. 这一行所有点的排列方案数（即 $C^i_m$，一开始解释过）。
3. 这一行的每个点分别接到哪一个点下面。

因为上面总共有 $s$ 个点，所以这一行的每一个点有 $s$ 个选择。根据乘法原理，总方案数就是 $i$ 个 $s$ 相乘，即 $s^i$。

所以下一行的 $w$ 就是这一行的 $w$ 乘上 $C^i_m$ 再乘上 $s^i$。

那么，我们的爆搜就可以搜下去了。我们考虑怎么统计整个问题的答案。

显然，我们最终的树形态数，就是搜完以后的 $w$。但是不要把根给忘掉了。我们的根可以随便放，可以放在任意一行、任意一列。

所以，枚举根放在哪一行，然后把 $w$ 的初始值设为 $m$ 即可。

这样我们需要组合数和快速幂。因为 $n$ 和 $m$ 都没那么大，所以组合数可以直接用杨辉三角递推。参见 [P5732](https://www.luogu.com.cn/problem/P5732) & [P1226](https://www.luogu.com.cn/problem/P1226)。

看一下爆搜代码。文中的 $s$ 实际上是 $sum$，$w$ 实际上是 $way$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
const int N = 7000;
int C[N][N];
int cal(int n, int m) {
    if (C[n][m]) return C[n][m];
    if (m == 1) return C[n][m] = n;
    if (n == m || m == 0) return C[n][m] = 1;
    if (m > n) return 0;
    return C[n][m] = (cal(n - 1, m) + cal(n - 1, m - 1)) % MOD;
}
int Pow(int a, int b) {
    int r = 1, x = a, p = b;
    while (p) {
        if (p & 1) r = r * x % MOD;
        x = x * x % MOD, p >>= 1;
    }
    return r;
}
int n, m, ans;
void dfs(int step, int sum, int way) {
    if (step == n + 1) {
        ans = (ans + way) % MOD;
    } else {
        for (int i = 0;i <= m;i++) {
            dfs(step + 1, sum + i, cal(m, i) * Pow(sum, i) % MOD * way % MOD);
        }
    }
}
signed main() {
    cin >> n >> m;
    for (int i = 1;i <= n;i++) {
        dfs(i + 1, 1, m);
    }
    cout << ans;
    return 0;
}
```

通过文章开篇的证明，不难看出，我们的搜索是无后效性的，即不会互相影响。那么我们只要将 $w$ 作为函数的返回值，然后记忆化一下即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
const int N = 7000;
int C[N][N];
int cal(int n, int m) {
    if (C[n][m]) return C[n][m];
    if (m == 1) return C[n][m] = n;
    if (n == m || m == 0) return C[n][m] = 1;
    if (m > n) return 0;
    return C[n][m] = (cal(n - 1, m) + cal(n - 1, m - 1)) % MOD;
}
int Pow(int a, int b) {
    int r = 1, x = a, p = b;
    while (p) {
        if (p & 1) r = r * x % MOD;
        x = x * x % MOD, p >>= 1;
    }
    return r;
}
int dp[85][6500], n, m, ans;
int dfs(int step, int sum) {
    if (dp[step][sum]) return dp[step][sum];
    if (step == n + 1) return dp[step][sum] = 1;
    int all = 0;
    for (int i = 0;i <= m;i++) {
        all = (all + cal(m, i) * Pow(sum, i) % MOD * dfs(step + 1, sum + i)) % MOD;
    }
    return dp[step][sum] = all;
}
signed main() {
    cin >> n >> m;
    for (int i = 1;i <= n;i++)
        ans = (ans + m * dfs(i + 1, 1) % MOD) % MOD;
    cout << ans;
    return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P12415 题解

~~基础赛的题真是越来越简单了。~~

## 思路

考虑动态规划，设 $f_{i,j}$ 为到了第 $i$ 行一共放了 $j$ 个节点的方案数。

$f_{i,j}$ 可以从 $f_{i-1,k}$ 转移得到，其中 $\max(0,j-m) \le k \le j$，也就是第 $i-1$ 行及之前总共填了 $k$ 个节点，第 $i$ 行新增 $j-k$ 个节点，这 $j-k$ 个节点要填进 $m$ 个位置，即有 $\begin{pmatrix} m \\ j-k \end{pmatrix}$ 种方案，然后这 $j-k$ 个节点又要找前面的 $k$ 个点作父亲，所以方案数是 $k^{j-k}$，这两个相乘累加就行了，也就是 $f_{i,j} = \sum\limits_{k=\max(0,j-m)}^j f_{i-1,k} \times \begin{pmatrix} m \\ j-k \end{pmatrix} \times k^{j-k}$，最终答案就是 $\sum\limits_{i=1}^{n \times m} f_{n,i}$。

$\begin{pmatrix} m \\ j-k \end{pmatrix}$ 是组合数，即 $\frac{m!}{(j-k)!(m-j+k)!}$，分数取模用到了逆元。

考虑提高一下运行效率，考虑到需要求逆元的数不多，可以初始化的时候对于每一个 $i!$ 都求一下逆元，然后对于前 $i$ 行，最多只会放入 $(i-1) \times m + 1$ 个节点，枚举的时候可以缩小一点范围。

设 $n,m$ 同阶，时间复杂度 $\mathcal{O}(n^4 \log n)$，实际运行不用跑这么多，可以通过。

## 代码

```cpp
#define int long long
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)

const int N=85;
const int mod=1e9+7;

int n,m;
int f[N][N*N];
int g[N*N],inv[N*N];
int ans;

int exgcd(int a,int b,int& x,int& y) {
    if (!b) {
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

int inverse(int a) {
    int x,y;
    exgcd(a,mod,x,y);
    x=(x%mod+mod)%mod;
    return x;
}

void init() {
    g[0]=1,inv[0]=1;
    _rep(i,1,N*N-1) g[i]=g[i-1]*i%mod,inv[i]=inverse(g[i]);
}

int C(int n,int m) {
    return (g[n]*inv[m]%mod)*inv[n-m]%mod;
}

int ksm(int a,int b) {
    if (!b) return 1;
    if (b==1) return a;
    int k=ksm(a,b>>1);
    if (b&1) return (k*k%mod)*a%mod;
    else return k*k%mod;
}

i32 main() {
    init();
    read(n),read(m);
    _rep(i,1,n) f[i][1]=m;
    _rep(i,1,n) _rep(j,1,(i-1)*m+1) _rep(k,max(0LL,j-m),j) f[i][j]=(f[i][j]+(f[i-1][k]*C(m,j-k)%mod)*ksm(k,j-k))%mod;
    _rep(i,1,n*m) ans=(ans+f[n][i])%mod;
    write(ans);
    return 0;
}
```

---

