# Curious Array

## 题目描述

You've got an array consisting of $ n $ integers: $ a[1],a[2],...,a[n] $ . Moreover, there are $ m $ queries, each query can be described by three integers $ l_{i},r_{i},k_{i} $ . Query $ l_{i},r_{i},k_{i} $ means that we should add ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF407C/7483b5d05694b4cb36893b9ef3b5ea6eca980e53.png) to each element $ a[j] $ , where $ l_{i}<=j<=r_{i} $ .

Record ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF407C/e80c4b14815086b581d3057ceea9005fcac2476e.png) means the binomial coefficient, or the number of combinations from $ y $ elements into groups of $ x $ elements.

You need to fulfil consecutively all queries and then print the final array.

## 样例 #1

### 输入

```
5 1
0 0 0 0 0
1 5 0
```

### 输出

```
1 1 1 1 1
```

## 样例 #2

### 输入

```
10 2
1 2 3 4 5 0 0 0 0 0
1 6 1
6 10 2
```

### 输出

```
2 4 6 8 10 7 3 6 10 15
```

# 题解

## 作者：MILLOPE (赞：14)

## 写在前面
既然没有人写题解，那么我这个蒟蒻就写一篇水题解好了

[我的博客qwq](https://blog.csdn.net/qq_34493840/article/details/95515653)

## 题目
给出$n$个数，有$m$个操作，每个操作是将$[L,R]$之间的数加上$C(j-L+k,k)$，$L<=j<=R$最后输出这$n$个数的值。

## 题解
- ~~虽然我考场上推出了式子但是我还是打的n^2^暴力（暴力选手qwq~~
- n阶差分可能有点难以理解可以先看一下[三步必杀（二阶差分](https://www.luogu.org/problemnew/show/P4231)
- [三步必杀题解](https://blog.csdn.net/qq_34493840/article/details/94474399)
- 我们要加的序列
$$\dbinom{k}{k},\dbinom{k+1}{k}\cdots\dbinom{r-l+k}{k}$$
- 又可以写成
$$\dbinom{k}{0},\dbinom{k+1}{1}\cdots\dbinom{r-l+k}{r-l}$$
- 结合公式
$$\dbinom{n}{m}=\dbinom{n-1}{m}+\dbinom{n-1}{m-1}$$
- 该序列的一阶差分序列为
$$\dbinom{k-1}{0},\dbinom{k}{1}\cdots\dbinom{r-l+k-1}{r-l}\Leftrightarrow\dbinom{k-1}{k-1},\dbinom{k}{k-1}\cdots\dbinom{r-l+k-1}{k-1}$$
- 二阶差分序列
$$\dbinom{k-2}{0},\dbinom{k-1}{1}\cdots\dbinom{r-l+k-2}{r-l}\Leftrightarrow\dbinom{k-2}{k-2},\dbinom{k-1}{k-2}\cdots\dbinom{r-l+k-2}{k-2}$$
- $j$阶差分序列
$$\dbinom{k-j}{0},\dbinom{k-j+1}{1},\cdots,\dbinom{r-l+k-j}{r-l}\Leftrightarrow\dbinom{k-j}{k-j},\dbinom{k-j+1}{k-j}\cdots\dbinom{r-l+k-j}{k-j}$$
- 我们可以发现这样的组合数序列在进行$k+1$次差分后全部变为$0$，我们可以在$k+1$次差分序列的$l$位置加上$1$，在$r+1$位置减去前面的前缀和即可
- 而$j$阶差分的前$k$位的和等于$j-1$阶差分序列的第$k$个数（~~手推一下吧~~
- 所以第$j$阶序列的前缀和
$$\sum_{j=0}^k\dbinom{r-l+k-j}{r-l}=\dbinom{r-l+k-j+1}{k-j+1}$$
- 每次消除前缀和对后面的影响即可

## $code$ 
```cpp
#include <bits/stdc++.h> 
using namespace std; 
const int maxn = 100000 + 1000;
const int maxm = 100 + 10;
const int mod = 1000000007;
typedef long long LL; 

template <class T> 
inline void read(T &s) {
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w;  
}

int n, m; 
LL a[maxn]; 
LL c[maxn][maxm], ans[maxn][maxm]; 

void init() {
	c[0][0] = 1; 
	for (int i = 1; i < maxn; ++i) {
		c[i][0] = 1; 
		for (int j = 1; j <= i && j < maxm; ++j) {
			c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod; 
		}
	}
}

int main() {
	freopen("data.in", "r", stdin); 
	freopen("bf.out", "w", stdout); 

	init(); 
	scanf("%d%d", &n, &m); 
	for (int i = 1; i <= n; ++i) 
		scanf("%d", &a[i]);  
	int l, r, k; 
	while (m--) { 
		scanf("%d %d %d", &l, &r, &k); 
		for (int i = 0; i <= k; ++i) 
			ans[l][i] = (ans[l][i] + c[k][k-i]) % mod; 
		for (int i = 0; i <= k; ++i)
			ans[r+1][i] = (ans[r+1][i] - c[r-l+k+1][k-i]) % mod; 
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 101; j >= 1; --j) {
			ans[i+1][j-1] = (ans[i+1][j-1] + ans[i][j] + ans[i][j-1]) % mod; 
		}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%lld ", ((ans[i][0] + a[i]) % mod + mod) % mod); 
	}
	return 0; 
}


```


---

## 作者：ChengJY_ (赞：6)

### 前言

优秀的高阶差分/前缀和练习题。

### Solution

**思路**

题意很清晰，不加以赘述。

注意到区间修改，但是我们发现修改的不同，因此设法将其转化为相同的值。

经过打表或手膜等一系列方式，我们发现修改值之间存在一些美妙的关系。

考虑差分。

- $k=1$ 时

一次差分后的差分序列的值均为 1 ，可以配合数据结构修改。

但更好的方法是二次差分，转化为形如 ${1,0,0,0… ,-1}$ 单点修改的形式。

- $k=2$ 时

经过一次差分我们发现其转化为了上述 $k=1$ 的形式。

直接三次差分。

- $k = x$ 时

我们从 $k$ 较小的情况推广，容易发现我们修改的应该是 $k+1$ 阶差分数组。

这也不难通过组合意义证明，另一篇题解已经讲得很清楚了。

**具体实现**

我们发现在具体实现中，难以直接对 $k$ 阶差分数组进行修改。

因为每次差分一次后，修改的序列都会增长。

具体例子如下：

```cpp
修改序列 1  2  3  4  5  0  0  0
一阶差分 1  1  1  1  1  -5 0  0
二阶差分 1  0  0  0  0  -6 5  0
```

我们不难发现，每次为了消除上一阶差分的影响，都需要多伸长一位。

对此，我们可以对于每一阶差分直接消除其影响。

再次以上面的为例：

```cpp
修改序列 1  2  3  4  5  0  0  0
一阶差分 0  0  0  0  0  -5 0  0
二阶差分 1  0  0  0  0  -1 0  0
```

每一阶在 $r+1$ 位置都删去这一阶的前缀，也就是上一阶的最后一个数，即为 $\dbinom{r-l+k-j+1}{r-l}$ 。

这样最终只需要从下向上做前缀和即可。

### [Code](https://codeforces.com/contest/407/submission/164698886)

```cpp
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;

int read(){
    int x=0,w=1;
    char ch=getchar();
    while(ch>'9'||ch<'0') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*w;
}

int mod = 1e9+7;
int n,m;
int fac[N],inv[N];
int a[N],d[100005][105];

int qpow(int x,int k){
	int res=1;
	while(k){
		if(k&1) res=res*x%mod;
		x=x*x%mod;k>>=1;
	}
	return res;
}
void init(){
	fac[0]=inv[0]=1; int maxn = 200000;
	for(int i=1;i<=maxn;++i) fac[i]=fac[i-1]*i%mod;
	inv[maxn]=qpow(fac[maxn],mod-2); 
	for(int i=maxn-1;i>=1;--i) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int x,int y){return fac[x]*inv[y]%mod*inv[x-y]%mod;}

signed main(){	
	init(); //cout<<C(4,2);
	n=read();m=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=m;++i){
		int l=read(),r=read(),k=read();
		d[l][k+1]=(d[l][k+1]+1)%mod;
		for(int j=1;j<=k+1;++j) d[r+1][j]=(d[r+1][j]-C(r-l+k-j+1,r-l)+mod)%mod;
	}
	for(int i=101;i>=1;--i){
		int res=0;
		for(int j=1;j<=n;++j) {
			res=(res+d[j][i])%mod;
			d[j][i-1]=(d[j][i-1]+res)%mod;
		}
	}
	for(int i=1;i<=n;++i) printf("%lld ",(a[i]+d[i][0])%mod);
	return 0;
}
```



---

## 作者：hxuwna (赞：3)

# 题意

给出 $n$ 个数，有 $m$ 个操作。

每个操作是将 $[L,R]$ 之间的数加上 ${j−L+k \choose k}$，$L \le j \le R$。

最后输出这 $n$ 个数的值。

# 题解

这道题的思路感觉比较巧妙。

看到这题我第一反应是线段树，但其实是差分。

## 1. 推导

首先，我们把 $k[i]$ 中的最大值设为 $maxk$，那么根据题意，对于形如

$$ ans[i]=a[i]+\sum_{j=0}^{maxk} cnt[i][j]{j \choose j}
$$

可转移出

$$ 
ans[i+1]=a[i+1]+\sum_{j=0}^{maxk} cnt[i][j]{j+1 \choose j}
$$

而众所周知

$$
{n \choose m} = {n-1 \choose m }+{n-1 \choose m-1 }
$$

于是

$$
{n+m+1 \choose n} = \sum_{i = 0}^{n} \ {i+m \choose i }
$$

所以就有

$$ 
ans[i+1]=a[i+1]+\sum_{j=0}^{maxk} cnt[i][j] \sum_{x=0}^{j} {x \choose x}
$$

那么对于每个 ${j \choose j}$ 来说，原式为

$$ 
ans[i+1]=a[i+1]+\sum_{j=0}^{maxk} {j \choose j} \sum_{x=j}^{maxk} cnt[i][x]
$$

由于 ${j \choose j}=1$，所以把 ${j \choose j}=1$ 代入第 1 个式子和这个式子，再把第 1 个式子的 $i$ 用 $i+1$ 代替。此时，通过比较两式，我们可以发现，原来的 $cnt[i+1][j]$ 变成了 $\sum_{x=j}^{maxk} cnt[i][x]$。

于是，我们便得出一个结论

$$
cnt[i+1][j]=\sum_{x=j}^{maxk} cnt[i][x]
$$

所以我们便可以通过一个类似前缀和的 $O(nk)$ 方法求出每个 $cnt[i][j]$。

## 2. 差分

对于每次操作，我们把 $cnt[l][k]$ 加一，再把每个 $cnt[r][i]$ 减去 ${(k-i)+(r-l) \choose r-l}$。

因为你先把 $cnt$ 的转移列出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/6igwgl7f.png)

再顺时针旋转 $45°$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jmtnd7sb.png)

此时你会发现它其实是个杨辉三角。这是由于 $cnt$ 的转移本质上其实是 C 的转移。

所以根据杨辉三角与 C 的关系，就可以得出 ${(k-i)+(r-l) \choose r-l}$（过程就是把杨辉三角的每一项用组合数学表示，再旋转回去找规律）。

![](https://cdn.luogu.com.cn/upload/image_hosting/ijx63xk4.png)

最后进行一个 $O(nk)$ 的递推推出 $cnt$ 和 $ans$，一道紫题就 AC 了（别忘了加上 $a[i]$）。

# code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int const N=1e5+10,M=1e2+10,mod=1e9+7;
int n,q,a[N],jc[N],inv[N],cnt[N][M],g[N][M];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
void init(int n){
	jc[0]=1;
	for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
	inv[n]=ksm(jc[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){
	if(n<m) return 0;
	return jc[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	init(1e5);//初始化
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(q--){//q次更改
		int l,r,k;cin>>l>>r>>k;
		cnt[l][k]=(cnt[l][k]+1ll)%mod;//差分
		for(int i=k;i>=0;i--) cnt[r+1][i]=(cnt[r+1][i]-C((k-i)+(r-l),(r-l))+mod)%mod;//还是差分
	}
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=100;j>=0;j--){//懒得求maxk就直接默认maxk为100,反正对结果没有影响
			sum=(sum+cnt[i][j])%mod;//求∑
			cnt[i+1][j]=(cnt[i+1][j]+sum)%mod;//前缀和
		}
		cout<<(sum+a[i])%mod<<" ";//输出ans
	}
	return 0;
}
```

---

## 作者：Hilaria (赞：3)

### 多阶差分

[例题link](https://www.luogu.com.cn/problem/CF407C)

+ 多阶差分：字面意思，做很多次差分。

+ #### 例题题意：

	给出 $n$ 个数 $a[1]\dots a[n]$，有 $m$ 个操作。
    
   每个操作是将 $[L,R]$ 之间的数加上 $C(j-L+k,k)$，$L\le j\le R$。

	最后输出这 $n$ 个数。

+ #### 思路

	这个题我们如果直接暴力去做的话时间复杂度 $O(n^2)$，写不了一点！

	那只好另辟蹊径（bushi）。

   首先我们其实可以直接算每个数被加了多少，最后再把原来的 $a[i]$ 加进去。

	考虑一次操作，我们手推一下，易得 $L\dots R$ 加入的数分别是:

	$\dbinom{k}{k},\dbinom{k+1}{k},\dbinom{k+2}{k}\dots \dbinom{k+R-L}{k}$

	然后因为我们有：
    
   $\dbinom {n}{m} = \dbinom {n}{n-m}$

	所以上面的柿子可以变为：

	$\dbinom{k}{0},\dbinom{k+1}{1},\dbinom{k+2}{2}\dots \dbinom{k+R-L}{R-L}$

	这不就是，杨辉三角：![](https://cdn.luogu.com.cn/upload/image_hosting/4p71a282.png)

	举个例子:

```
n=9 k=2 L=2 R=4 
修改序列 0  1  3  6  0  0  0

```

那么在图上就是：![](https://cdn.luogu.com.cn/upload/image_hosting/ej7o7kdq.png)

根据定义：

$\dbinom{i}{j}=\dbinom{i-1}{j}+\dbinom{i-1}{j-1}$

我们果断差分，发现差分一次后的序列整个上移了一行（准确来说差分序列还有个 $R+1$ 处的尾巴，我们下面再讨论）。长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/14z21kw3.png)

辣我们再多做几次差分，我们会发现我们的序列最终总会变为 $1,0,0,0\dots$（手玩可得）。

然后多阶差分就可以了（会的dalao可以跳过下面了）。

```
图1-1
n=9 k=2 L=2 R=4 
原修改序列 0  1  3  6  0  0  0
第一次差分 0  1  2  3 -6  0  0
第二次差分 0  1  1  1 -9  6  0
第三次差分 0  1  0  0 -10 15 -6

```
于是我们开一个数组 $ans[i][j]$ 表示第 $i$ 阶的差分中第 $j$ 个数是多少。
我们可以发现我们一共做了 $k+1$ 次差分，那我们在第 $ans[k+1][1\dots n]$ 的位置做好记录，如下图。

```
图1-2
n=9 k=2 L=2 R=4 
修改序列 0  0  0  0  0  0  0
一阶差分 0  0  0  0  0  0  0
二阶差分 0  0  0  0  0  0  0
三阶差分 0  1  0  0 -10 15 -6

```

我们的数组中「三阶差分」的前缀和就是「第二次差分后」的数，我们把第二次差分后的数赋值到数组中「二阶差分」中去，「二阶差分」的前缀和就是「第一次差分后」的数，以此类推得原序列（结合图 1-1 食用）。

但是我们发现由于我们做了多次差分，为了消除影响我们每次差分都会多一个尾巴（详见图 1-1，就是 **第一次差分后** 多了一个 $-6$，**第二次差分后** 又多了一个 $6$ 且上一次的尾巴变成 $-9$，以此类推）。

那可以让每次差分只有一个尾巴，直接在 **每阶差分** $R+1$ 的位置消除 **这次差分** 的全部影响。

那么还是刚刚辣个例子，我们对于这次操作，我们的数组变为：

```
n=9 k=2 L=2 R=4 
修改序列 0  0  0  0  0  0  0
一阶差分 0  0  0  0 -6  0  0
二阶差分 0  0  0  0 -3  0  0
三阶差分 0  1  0  0 -1  0  0
```

每一阶在 $R+1$ 的位置清除这一阶的影响，也就是 $-1*\dbinom{k+1-i+R-L}{R-L}$，$i$ 为第 $i$ 阶。

说一下这柿子怎么推的吧（大眼观察易得bushi）。

就我们知道第 $i$ 阶的尾巴是这阶的前缀和，然后这阶的前缀和其实就是 $i-1$ 阶的第 $R$ 个数，我们之前不是说了我们每次差分出来的数其实是在杨辉三角上平移吗，我们在杨辉三角上找到 $i-1$ 阶的第 $R$ 个数的位置，然后手推一下就知道了。

最后往上做前缀和就行了。

+ Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;

const int MAXN=2e5+10;
const int MAXK=122;
const int P=1e9+7;

int n,m;
int a[MAXN];
int inv[MAXN],mul[MAXN];
int ans[MAXK][MAXN];

int C(int a,int b) { return inv[a]*mul[a-b]%P*mul[b]%P; }

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	inv[0]=inv[1]=mul[0]=mul[1]=1;
	for(int i=2;i<MAXN;i++) inv[i]=i*inv[i-1]%P;
	for(int i=2;i<MAXN;i++) mul[i]=mul[P%i]*(P-P/i)%P;
	for(int i=2;i<MAXN;i++) mul[i]=mul[i-1]*mul[i]%P;
	for(int i=1;i<=m;i++)
	{
		int l,r,k;
		cin>>l>>r>>k;
		ans[k+1][l]++;
		int sy=k+r-l,kx=r-l;
		for(int j=0;j<=k;j++) ans[j+1][r+1]=(ans[j+1][r+1]-C(sy-j,kx))%P;
	}
	for(int i=101;i>0;i--)
	{
		for(int j=1;j<=n;j++) ans[i][j]=(ans[i][j]+ans[i][j-1])%P;
		for(int j=1;j<=n;j++) ans[i-1][j]=(ans[i-1][j]+ans[i][j])%P;
	}
	for(int i=1;i<=n;i++) cout<<((ans[0][i]+a[i])%P+P)%P<<" ";

	return 0;
}

```

---

## 作者：Union_of_Britain (赞：1)

组合数 $\binom{x+y}{y}$ 的一个意义是 $(0,0)$ 通过走上/右走到 $(x,y)$ 的方案数。

在这道题目中，把所有数排成一行 $(i,100)$，一个操作忽略 $r$ 就相当于在 $(l,100-k)$ 权值加一，之后递推算答案。

对于 $r$ 的限制是容易处理的。每加入一个点，在 $(r+1,100-k+j)$ 权值加上 $\binom{r-l+j}{j}$，代表**第一个**走到横坐标为 $r+1$ 的点需要减去贡献（因此最后一步必然是右；所以组合数不是 $\binom{r-l+1+j}{j}$）。

这样的缺点是修改复杂度变成了 $O(k)$，但是还是可以通过的。总复杂度 $O(nk+mk)$。

---

## 作者：Terac (赞：0)

这个题我觉得还挺有趣的。

推式子发现走不通，如果分开考虑，我甚至对于每个数最后计算都很困难。只能考虑组合数间的递推关系。因为 $\binom{n}{m}=\binom{n}{m-1}+\binom{n-1}{m-1}$，这个题的 $n$ 又是连续递增的，考虑差分试试。

发现每次加的就是 $\binom{k}{k},\binom{k+1}{k},\cdots\binom{k+r-l}{k}$，令 $\Delta^{(1)}_i=\binom{k+i}{k}-\binom{k+i-1}{k}$，发现 $\Delta^{(1)}_i=\Delta^{(1)}_{i-1}+\binom{k+i-1}{k-1}$，令 $\Delta^{(2)}_i=\Delta^{(1)}_i-\Delta^{(1)}_{i-1}$，现在变成了在 $\Delta^{(2)}$ 上区间加 $\binom{k+i-1}{k-1}$ 了，我们通过一次差分，使问题的 $k$ 减小了 $1$。依此类推 $\Delta^{(3)},\Delta^{(4)},\cdots,\Delta^{(k)}$。

因为 $k\le 100$，所以最多 $100$ 次可以使 $k$ 变为 $0$，这时就变成区间 $+1$ 了，再差分一次就结束。

每次要在差分序列上 $r+1$ 位减去 $[l,r]$ 所有新加的值之和，保证差分的正确性，而这个区间和恰是上一个差分序列第 $r$ 位的值，即一个确定的组合数，预处理即可。

时空复杂度 $O(nk+mk)$。

---

