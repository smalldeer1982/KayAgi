# Daniel and Spring Cleaning

## 题目描述

给定$l,r$，求
$$\sum_{a=l}^r\sum_{b=l}^r[a+b=a\oplus b]$$

## 样例 #1

### 输入

```
3
1 4
323 323
1 1000000
```

### 输出

```
8
0
3439863766
```

# 题解

## 作者：skydogli (赞：7)

~~好不容易发现一道本蒟蒻都会的数位DP题~~

首先，我们可以知道这题本质上就是求满足各个二进制位与运算后都不为1的数对个数，那么对于每个二进制位就有$(0,0),(0,1),(1,0)$这3种情况，就可以进行DP了。

然后根据数位DP的套路我们考虑差分，设$calc(l,r)=\sum\limits_{x=0}^{l}\sum\limits_{y=0}^{r}[x \ \ and\ \ y=0] $的数量，这样就能只考虑是否顶上界而无须考虑下界问题了。那么题目要求的答案其实就是$calc(r,r)-calc(l-1,r)\times 2 + calc(l-1,l-1)$,具体的DP方程见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define N 35
LL f[N+5][2][2];
int T,l,r;
LL calc(LL a,LL b){//x为从0到a，y为从0到b
	if(a<0||b<0)return 0;
    //差分后有小于0的情况注意特判
	memset(f,0,sizeof(f));
	f[N][1][1]=1;//一开始都顶上界
	for(int i=N-1;i>=0;--i){//按位依次选取
		for(int j=0;j<2;++j)
			for(int k=0;k<2;++k){//j，k分别表示x和y是否顶上界的情况
				bool nexj=(j&&!((a>>i)&1ll)),nexk=(k&&!((b>>i)&1ll));
				f[i][nexj][nexk]+=f[i+1][j][k];
				//考虑这一位x和y都取0的情况，可以手动模拟一下，只有顶当前上界且限制的这一位为0才会继续顶上界
				if(((a>>i)&1)||!j) f[i][j][nexk]+=f[i+1][j][k];
                //如果当前不顶a的上界或a这一位为1，那么x可以在这一位取1
				if(((b>>i)&1)||!k) f[i][nexj][k]+=f[i+1][j][k];
                //同理，如果当前不顶b的上界或b的这一位为1，那么y可以在这一位取1
			}
	}
	return f[0][0][0]+f[0][1][0]+f[0][0][1]+f[0][1][1];
}
signed main()
{
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&l,&r);
		printf("%lld\n",calc(r,r)-calc(l-1,r)*2ll+calc(l-1,l-1));
        //差分
	}
	return 0;
}
```

---

## 作者：Saliеri (赞：3)

一个不用容斥的做法。

做完之后右转 [ABC138F](https://www.luogu.com.cn/problem/AT4840)，做法几乎一模一样。

___

同时搞两个数的上下界不太方便，考虑强制钦定 $x<y$，最后答案 $ \times2$。

$x=y$时不会有贡献，所以不会算重。但是$x=y=0$满足条件，记得特判。

对于同时有上下界的数位 DP，有一个新姿势：设 $dp_{d,lim1,lim2}$ ，表示正在从高位到低位决策第 d 位，下界是否顶满，上界是否顶满的答案。

转移时枚举每一位 $x,y$ 的决策即可。

但我们发现一个问题：若只设这两个维度，无法有效区分高位相等与否的情况，而转移与 $x,y$ 高位是否相等有关，于是就有大锅。

随便补补，多设一维变成 $dp_{d,lim1,lim2,eq}$ 表示高位是否相等。

转移是数位DP的套路，显然，不赘述。

时间复杂度 $O(T\log r)$ 。

___

代码：其实可以用这种记搜的写法，会好写很多。

```cpp
#include <cstdio>
#include <cstring>
typedef long long ll;
ll dp[35][2][2][2];
int T,l,r,lb[35],ub[35],digl,digr;
ll dfs(int d,bool flagl,bool flagr,bool eq){
	if(!d)return 1;
	ll &res = dp[d][flagl][flagr][eq];
	if(~res)return res;
	res = 0;
	int lbound = flagl?lb[d]:0,rbound = flagr?ub[d]:1;
	for(int y=0;y<=rbound;++y)
		for(int x=lbound;x<=(eq?y:1);++x)
			if(!(x&y))
				res += dfs(d-1,flagl&(x==lbound),flagr&(y==rbound),eq&(x==y));
	return res;
}
int main(){
	scanf("%d",&T);
	while(T--){
		memset(dp,-1,sizeof(dp)),memset(lb,0,sizeof(lb)),memset(ub,0,sizeof(ub));
		scanf("%d %d",&l,&r);
		int flag = !l;
		digl = digr = 0;
		while(l)lb[++digl] = l&1,l >>= 1;
		while(r)ub[++digr] = r&1,r >>= 1;
		printf("%lld\n",dfs(digr,1,1,1)*2-flag);
	}
	return 0;
}
```

---

## 作者：Kelin (赞：2)

## [题意](https://blog.csdn.net/BeNoble_/article/details/102886240)

求$[l,r]$之间有多少对$(x,y)$满足$x+y=x\oplus y$

$0\le l\le r\le10^9$

---
## 题解

注意到$l,r$的范围，又涉及到二进制位上运算，所以考虑按二进制来数位$dp$

设$f(l,r)$表示满足以下条件的$(x,y)$有多少对

>$x+y=x\oplus y$
>
>$0\le x\le l$
>
>$0\le y\le r$

根据容斥可以得到$Ans=f(r,r)-2f(l-1,r)+f(l-1,l-1)$

根据数位$dp$的基本思路

$dp(p,Lim_x,Lim_y)$表示在二进制第$p$位，$x,y$是否有限制的答案

有限制表示已经选的填的数的高位是否与$l,r$相同

如果有限制这一位填的数就不能超过$l,r$在当前位的值

时间复杂度$O(\log r)$

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int L,R;ll f[33][2][2];
ll dp(int p,bool Lim_x,bool Lim_y){
	if(p==-1)return 1;
	ll&g=f[p][Lim_x][Lim_y];
	if(g!=-1)return g;
	g=0;
	int Up_x=Lim_x?(L>>p)&1:1,
		Up_y=Lim_y?(R>>p)&1:1;
	for(int i=0;i<=Up_x;++i)
		for(int j=0;j<=Up_y;++j)
			if(!(i&j))
				g+=dp(p-1,Lim_x&&i==Up_x,Lim_y&&j==Up_y);
	return g;
}
inline ll Sol(int l,int r){
	if(l<0)return 0;
	memset(f,-1,sizeof f);
	L=l,R=r;
	return dp(log2(R+1)+1,1,1);
}
int main(){
	int t,l,r;
	scanf("%d",&t);
	while(t--)
		scanf("%d%d",&l,&r),
		printf("%lld\n",Sol(r,r)-2*Sol(l-1,r)+Sol(l-1,l-1));
return 0;
}
```

---

## 作者：QWQ_123 (赞：1)

众所周知，异或是不进位加法。

所以显然 $a+b$ 不能进位，也就是 `a & b = 0`。

所以 $a,b$ 的每一位都只能是 $(0,0),(1,0),(0,1)$。

然后设 $f_{i,j,k}$ 表示第 $i$ 位 $a$ 是 $j$，$b$ 是 $k$。

然后记搜，然后记录 $a$ 和 $b$ 是否顶到上界即可。

然后对于询问直接二维差分。

---

## 作者：2huk (赞：1)

> - 给定 $l, r$，求 $\sum_{i=l}^r \sum_{j=l}^r [i+j = i \operatorname{xor} j]$。
> - $r \le 10^9$。

因为异或是不进位加法，所以只要 $i, j$ 进行加法时不进位，就一定有 $i+j = i \operatorname{xor} j$。换言之，$i \operatorname{and} j = 0$ 和 $i+j = i \operatorname{xor} j$ 是等价的。

所以所求即 $\sum_{i=l}^r \sum_{j=l}^r [i \operatorname{and} j = 0]$。

设 $f(x, y) = \sum_{i=\color{red}1}^x \sum_{j=\color{red}1}^y [i \operatorname{and} j = 0]$。那么所求即 $f(r, r) - f(r, l - 1) - f(l - 1, r) + f(l - 1, l - 1)$。$f(x, y)$ 的求解是简单数位 DP。

```cpp
int dp(int u, bool sb, bool bs) {
	if (!u) return 1;
	
	int& res = f[u][sb][bs];
	if (~res) return res;
	res = 0;
	
	int t1 = sb ? a[u] : 1;
	int t2 = bs ? b[u] : 1;
	
	for (int i = 0; i <= t1; ++ i )
		for (int j = 0; j <= t2; ++ j )
			if (!i || !j) res += dp(u - 1, sb && (i == t1), bs && (j == t2));
	
	return res;
}

int calc(int x, int y) {
	if (x < 0 || y < 0) return 0;
	
	memset(f, -1, sizeof f);
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	
	int l = 0;
	while (x) {
		a[ ++ l] = x & 1;
		x >>= 1;
	}
	len = l, l = 0;
	while (y) {
		b[ ++ l] = y & 1;
		y >>= 1;
	}
	len = max(len, l);
	
	int res = dp(len, 1, 1);
	
	return dp(len, 1, 1);
}

void Luogu_UID_748509() {
	int l, r;
	fin >> l >> r;
	fout << (calc(l - 1, l - 1) + calc(r, r)) - (calc(l - 1, r) + calc(r, l - 1)) << '\n';
}
```

---

## 作者：Piwry (赞：1)

有点意思的数位题（指调试调了 1h+ \fad）...之前还没见到过同时有两个上界的数位题目...

这里仅讲下我的思路；当然直接 dp 的做法也不是不可以 \kk

## 解析

首先显然有当且仅当 $a\& b=0$ 时才有 $a+b=a⊕b$

接着发现这个枚举同时有上界和下界要求非常麻烦，于是推一波式子：$\sum\limits_{a=l}^r\sum\limits_{b=l}^r{[a\& b=0]}=\sum\limits_{a=0}^r\sum\limits_{b=0}^r{[a\& b=0]}-2\sum\limits_{a=0}^{l-1}\sum\limits_{b=0}^r{[a\& b=0]}+\sum\limits_{a=0}^{l-1}\sum\limits_{b=0}^{l-1}{[a\& b=0]}$

对于计算 $\sum\limits_{a=0}^{lim1}\sum\limits_{b=0}^{lim2}{[a\& b=0]}$，我们考虑枚举 $a$ 从高位到低位确定了几位和 $b$ 从高位到低位确定了几位（确定成 $lim1, lim2$ 的数位值）

若 $a$ 从高位到低位确定了 $i-1$ 位，$b$ 从高位到低位确定了 $j-1$ 位，且 $lim1_i=1, lim2_j=1$；如果我们将 $a_i, b_j$ 设为 $0$，显然后面位无论怎么放 $a, b$ 都不会超过 $lim1$ 和 $lim2$

先考虑 $i<j$；设最大数位长度为 $m$。为了使 $[i+1, j-1]$ 部分的 $\&$ 值为 $0$，在 $b$ 为 $1$ 的下标处，$a$ 只能放 $0$，但其余部分可以随意放；设随意放的位数为 $k$（其实就是 $b$（$lim2$） 的 $[i+1, j-1]$ 数位的 “$0$” 个数），那么这部分贡献就为 $2^k$。而对于 $[j+1, m]$ 的部分，方案数显然就是 “确定一个数，另一个数枚举它的子集”，即 $3^{|[j+1, m]|}$。此外还有 $[j, j]$ 部分的贡献；由于 $b_j$ 确定为 $0$，因此 $a_j$ 可以随意放，贡献就为 $2$

可以自己做个图理解，类似这样：

![pic_dig](https://cdn.luogu.com.cn/upload/image_hosting/1o379dr1.png)

（~~别吐槽画风~~）

而对于 $i>j$ 或 $i=j$ 的情况，处理也类似

于是我们只需枚举 $i, j$，然后将每次的方案数求和即可。对每次询问，总的枚举复杂度是 $O(\log n^2)$ 的（快速幂的复杂度不计入）

## CODE

讲得可能有点不太清楚；可参考代码实现理解qaq

```cpp
#include <cstdio>
#define ll long long

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

ll Pow(ll x, int k){
	ll ret =1;
	for(; k; x =x*x, k >>=1)
		if(k&1)
			ret =ret*x;
	return ret;
}

const int MAXDig =(31+1) +10;

int L[MAXDig], R[MAXDig];
int sum_l[MAXDig], sum_r[MAXDig];/*两个上界从高位到低位的数位 "0" 个数的前缀和*/
int pre_l[MAXDig], pre_r[MAXDig];/*两个上界从高位到低位的数位的前缀 ( 可参考实现理解 )*/

ll work(int l, int r){
	if(l < 0 || r < 0)
		return 0;
	int beg1 =31, beg2 =31;
	for(int k =1<<29, i =1; k; k >>=1, ++i){/*高位补 0，均拓展到 30 位 (INT_MAX)*/
		L[i] =((l&k) != 0);
		R[i] =((r&k) != 0);
		if((l&k) != 0 && beg1 == 31)
			beg1 =i;
		if((r&k) != 0 && beg2 == 31)
			beg2 =i;
		sum_l[i] =sum_l[i-1]+((l&k) == 0);
		sum_r[i] =sum_r[i-1]+((r&k) == 0);
		pre_l[i] =(pre_l[i-1]<<1)+((l&k) != 0);
		pre_r[i] =(pre_r[i-1]<<1)+((r&k) != 0);
	}
	ll ret =0;
	for(int i =beg1; i <= 30; ++i)/*枚举 a < lim1, b < lim2 的情况，从高位逐步确定数位*/
		for(int j =beg2; j <= 30; ++j)
			if(L[i] == 1 && R[j] == 1){
				if(i == j){
					if((pre_l[i-1]&pre_r[j-1]) != 0)/*确定的数位不再满足 & 为 0*/
						break;
					ret +=Pow(3, 30-i);
				}
				else if(i > j){
					if((pre_l[i-1]&(pre_r[j-1]<<(i-j))) != 0)
						break;
					ret +=Pow(3, 30-i)*(1ll<<(sum_l[i-1]-sum_l[j] +1));
					// 由于 L[j]=1，所以 sum_l[j] 实际上就是 sum_l[j+1]，^- 这里这么写是为了避免边界问题 //
					// 后面还有个 "+1"，是 [i, i] 部分的贡献 ( 即 2 ) //
				}
				else{
					if((pre_r[j-1]&(pre_l[i-1]<<(j-i))) != 0)
						break;
					ret +=Pow(3, 30-j)*(1ll<<(sum_r[j-1]-sum_r[i] +1));
				}
			}
	for(int i =beg1; i <= 30; ++i)/*b 等于 lim2*/
		if(L[i] == 1){
			if((r&(pre_l[i-1]<<(30-(i-1)))) != 0)
				break;
			ret +=1ll<<(sum_r[30]-sum_r[i]);
		}
	for(int i =beg2; i <= 30; ++i)/*a 等于 lim1*/
		if(R[i] == 1){
			if((l&(pre_r[i-1]<<(30-(i-1)))) != 0)
				break;
			ret +=1ll<<(sum_l[30]-sum_l[i]);
		}
	if((l&r) == 0)/*a, b 均等于 lim1, lim2*/
		++ret;
	return ret;
}

int main(){
	for(int t =0, T =read(); t < T; ++t){
		int l =read(), r =read();
		printf("%lld\n", work(r, r)+work(l-1, l-1)-2*work(l-1, r));
	}
}
```

## 其它

话说计算 $\sum\limits_{a=0}^{lim}\sum\limits_{b=0}^{lim}{[a\& b=0]}$ 其实是有一个 $\log$ 的做法的...主要是一开始我没想到枚举 $a$ **也枚举** $b$，于是就捣鼓半天弄出了这个东西...

这里仅放下代码和简略注释，就不展开了 \fad（要展开说其实也就是一堆分类讨论）

```cpp
#include <cstdio>
#define ll long long

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

ll Pow(ll x, int k){
	ll ret =1;
	for(; k; x =x*x, k >>=1)
		if(k&1)
			ret =ret*x;
	return ret;
}

int L[32], R[32];
int sum[32];/*lim 从高位到低位的数位 "0" 个数的前缀和*/

void work(int l, int r){
	if(r == 0){
		puts("1");
		return;
	}
	for(int k =1<<29, i =1; k; k >>=1, ++i){
	//	L[i] =((l&k) != 0);
		R[i] =((r&k) != 0);
		sum[i] =sum[i-1]+((r&k) == 0);
	}
	long long ret =0;
	int fst =0;
	for(int i =1; i <= 30; ++i){
		if(R[i] == 1){
			if(fst == 0){/*a "首位" 为 0 的情况，需要枚举 b*/
				ret +=Pow(3, 30-i);
				for(int j =i+1; j <= 30; ++j){/*从高位逐步确定数位，避免 b 超过上界*/
					if(R[j] == 1){
						ret +=(1ll<<(sum[j]-sum[i]))*2*Pow(3, 30-j);
					}
				}
				ret +=1ll<<(sum[30]-sum[i]); //
				fst =i;
			}
			else/*否则的话 b 一定达不到上界，做图讨论下就能发现怎么计算贡献*/
				ret +=(1ll<<(sum[i]-sum[fst]))*2*Pow(3, 30-i);
		}
	}
	ret +=1ll<<(sum[30]-sum[fst]);/*a 等于 lim 时的贡献*/
	printf("%lld\n", ret);
}

int main(){
	// 代码其实来自于某场模拟赛... //
//	freopen("lambda.in", "r", stdin);
//	freopen("lambda.out", "w", stdout);
	for(int t =0, T =read(); t < T; ++t){
		int l =read(), r =read();
		if(l == 0)
			work(l, r);
		else{
			long long cnt =0;/*这里是暴力计算 \fad*/
			for(int i =l; i <= r; ++i){
				for(int j =l; j <= r; ++j)
					if((i&j) == 0)
						++cnt;
			}
			printf("%lld\n", cnt);
		}
	}
}
```

---

## 作者：ziyistudy (赞：0)

其实，异或相当于没有进位的加法，所以 $a+b$ 没有进位，即对于同位置 $a,b$ 的二进制位 $i,j$，有 $i \& j=0$（其中，$\&$ 表示按位与）。则 $(i,j)$ 可以取值为 $(0,0)$，$(0,1)$ 和 $(1,0)$。

再看到这题求解有上下界，不难想到数位 dp。设 
$$work(x,y)=\sum_{a=1}^x\sum_{b=1}^y [x\&y=0]$$

则数位 dp 记录 $dp_{pos,lim,lim1}$ 表示当前考虑第 $pos$ 位，$x,y$ 是否到达上界。

最后利用差分，答案为 $work(r,r)-work(l-1,r)-work(l,r-1)-work(l-1,l-1)$。其中 $work(l-1,r)=work(l,r-1)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=998244353;
// head
const int N=35;
int dp[N][2][2];
int num[N],num1[N];
int dfs(int pos,int lim,int lim1)
{
    if(pos==0) return 1;
    if(dp[pos][lim][lim1]!=-1) return dp[pos][lim][lim1];
    int ans=0;
    ans+=dfs(pos-1,lim&&(!num[pos]),lim1&&(!num1[pos]));
    if(num[pos]||!lim) ans+=dfs(pos-1,lim&&num[pos],lim1&&(!num1[pos]));
    if(num1[pos]||!lim1) ans+=dfs(pos-1,lim&&(!num[pos]),lim1&&num1[pos]);
    dp[pos][lim][lim1]=ans;
    return ans;
}
int work(int x,int y)
{
    if(x<0||y<0) return 0; //important
    memset(num,0,sizeof(num));
    memset(num1,0,sizeof(num1));
    memset(dp,-1,sizeof(dp));
    int len=0,len1=0;
    while(x) num[++len]=x%2,x/=2;
    while(y) num1[++len1]=y%2,y/=2;
    return dfs(max(len,len1),1,1);
}
signed main() 
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    int q;cin>>q;
    while(q--)
    {
        int l,r;cin>>l>>r;
        cout<<work(r,r)-work(l-1,r)*2+work(l-1,l-1)<<endl;
    }
}
```

---

## 作者：wflhx2011 (赞：0)

## Solution

首先，对于位运算熟悉的话，就会发现题目其实是要求 $\sum_{a=l}^{r}\sum_{b=l}^{r} [a \operatorname{and}b=0] $ 的数量。

所以，每一位上二进制组合可能有 $(0,1)$，$(1,0)$ 或 $(0,0)$ 这三种情况。

考虑使用记忆化搜索，设 $f_{i,j,k}$ 表示当前枚举到第 $i$ 位，两个数分别有无限制，随后分别枚举上述三种情况。

最后，设 $solve(u,v)$ 表示 $\sum_{a=0}^{u}\sum_{b=0}^{v} [a \operatorname{and}b=0] $ 的结果，由类似二位前缀和的方法（其实就是容斥）可得答案为 $ solve(r,r)-solve(l-1,r)-solve(l,r-1)+solve(l-1,l-1)=solve(r,r)-2\times solve(l-1,r)+solve(l-1,l-1) $。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[37][2][2];
long long l,r,a[45],b[45];
long long dfs(long long k,long long f1,long long f2)
{
	if(!k)	
		return 1;
	if(f[k][f1][f2]>=0)
		return f[k][f1][f2];
	long long ans=0;
	ans+=dfs(k-1,f1&&!a[k],f2&&!b[k]);
	if((!f1)||(a[k]))
		ans+=dfs(k-1,f1,f2&&!b[k]);
	if((!f2)||(b[k]))
		ans+=dfs(k-1,f1&&!a[k],f2);
	f[k][f1][f2]=ans;
	return ans;
}
long long solve(long long u,long long v)
{
	if(u<0||v<0)
		return 0;
	memset(f,-114514,sizeof(f));
	long long len1=0,len2=0;
	for(int i=1;i<=40;i++)
		a[i]=b[i]=0;
	while(u)
	{
		a[++len1]=u%2;
		u/=2;
	}
	while(v)
	{
		b[++len2]=v%2;
		v/=2;
	}
	return dfs(max(len1,len2),1,1);
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>l>>r;
		cout<<solve(r,r)-2ll*solve(l-1,r)+solve(l-1,l-1)<<endl;	
	} 
	return 0;
}

```

---

## 作者：Leeb (赞：0)

### 题意简述

给出 $l$，$r$，要求 $(a,b)$ 的对数且满足：
- $l\le a,b\le r$。
- $a+b=a\oplus b$。
### 解题思路

如果将问题转化为前缀问题我们在二进制上面就会比较好分析问题。

记 $calc(l,r)$ 为 $0\le a\le l$，$0\le b\le r$ 时满足条件的对数，那么我们根据容斥的思想即可知道答案为：$calc(r,r)-calc(l-1,r)-calc(r,l-1)+calc(l-1,l-1)$。

那么我们现在只需考虑求 $calc(l,r)$。

**数位 dp**。

注意到 $a+b=a\oplus b$ 的条件为 $a\&b=0$。

所以我们直接从高到低枚举每一位数位 dp 计算答案即可。
### 参考代码

```cpp
// Code by Leeb
// Powered by Visual Studio Code
// -- More and More vegetables, what should I do?
// -- AFO! AFO YYDS!
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 35
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
#define int long long 
#define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define pii pair<int, int>
#define fir first
#define sec second
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, l, r, dp[N][2][2];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = 1; ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline int dfs(int, int, int, bool, bool);
inline int calc(int l, int r);
inline void init() {
    l = in(), r = in();
}
inline void work() {
    int ans = calc(r, r) - calc(l - 1, r) - calc(r, l - 1) + calc(l - 1, l - 1);
    out(ans, endl);
}
inline int calc(int l, int r) {
    if (l < 0 || r < 0) return 0;
    mem(dp, -1);
    int ans = dfs(l, r, 30, 1, 1);
    return ans;
}
inline int dfs(int l, int r, int k, bool f1, bool f2) {
    if (k == -1) return 1;
    if (dp[k][f1][f2] != -1) return dp[k][f1][f2];
    int ans = 0, a = 1, b = 1;
    if (f1) a = (l >> k & 1);
    if (f2) b = (r >> k & 1);
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) 
            if (!(i & j)) ans += dfs(l, r, k - 1, f1 & (i == a), f2 & (j == b));
    }
    return dp[k][f1][f2] = ans;
}
signed main() {
    // freopen("example.in", "r", stdin);
    // freopen("example.ans", "w", stdout);
    // freopen("equal.in", "r", stdin);
    // freopen("equal.out", "w", stdout);
    int t = in();
    while (t--) {
        init();
        work();
    }
    return 0;
}
```

---

## 作者：CmsMartin (赞：0)

[更好的阅读体验](http://cmsblog.top/archives/solution-cf1245f)

## 题目描述

[题目传送门](https://codeforces.com/problemset/problem/1245/F)

简意：给定 $l,r(0 \le l,r \le 10^9)$，求：

$$
\sum_{a=l}^r \sum_{b=l}^r[a+b = a \oplus b]
$$

## 思路

直接做没法做，考虑一下这个式子的意义，也就是什么时候 $a+b = a \oplus b$ 会成立。异或运算表示二进制下不进位加法，他们相等时就说明两个数二进制相加无进位，也就是 $a+b = a \oplus b \Leftrightarrow a\ \&\ b=0$。

原式化为：

$$
\sum_{a=l}^r \sum_{b=l}^r[a\ \&\ b=0]
$$

现在可以做了。转化为前缀相减，设 $f(l,r)=\sum\limits_{a=0}^l \sum\limits_{b=0}^r[a\ \&\ b=0]$，就是 $f(r,r)-f(l - 1, r) - f(l, r - 1) + f(r, r)=f(r,r) - 2f(l - 1, r) + f(l - 1, l - 1)$。然后对于每一个，考虑按位枚举，设 $dp_{i,l_1,l_2}$ 表示从高往低第 $i$ 位，前面对于两个数对于已填的位是否已经是最大（即对于后面做到的上界为 $0$ 的位，我们能不能自己添上 $1$），然后分三种情况对于这一位填就可以了：$(0,0)(0,1)(1,0)$ 。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll T, L, R, Dp[31][2][2];
ll Bit1[31], Bit2[31];

ll DFS(ll pos, bool limit1, bool limit2) {
    if (!pos) return 1ll;
    if (~Dp[pos][limit1][limit2]) return Dp[pos][limit1][limit2];

    ll tmp = DFS(pos - 1, limit1 && (Bit1[pos] == 0), limit2 && (Bit2[pos] == 0));
    if ((!limit1) || Bit1[pos]) tmp += DFS(pos - 1, limit1, limit2 && (Bit2[pos] == 0));
    if ((!limit2) || Bit2[pos]) tmp += DFS(pos - 1, limit1 && (Bit1[pos] == 0), limit2);
    Dp[pos][limit1][limit2] = tmp;
    return tmp;
}

ll Solve(ll x1, ll x2) {
    if (x1 < 0 || x2 < 0) return 0;
    memset(Dp, -1, sizeof Dp);
    memset(Bit1, 0, sizeof Bit1);
    memset(Bit2, 0, sizeof Bit2);
    ll Len1 = 0, Len2 = 0;
    while (x1) {
        Bit1[++Len1] = x1 & 1;
        x1 >>= 1;
    }
    while (x2) {
        Bit2[++Len2] = x2 & 1;
        x2 >>= 1;
    }
    return DFS(max(Len1, Len2), true, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while (T--) {
        cin >> L >> R;
        ll Ans1 = Solve(R, R), Ans2 = Solve(L - 1, R), Ans3 = Solve(L - 1, L - 1);
        cout << Ans1 - 2ll * Ans2 + Ans3 << endl;
    }
    return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1245F)

# 题解

数位 $DP$ 的典型题，记
$$
f(x,y)=\sum_{i=0}^x\sum_{j=0}^y[i+j=i\oplus j]
$$
显然有 $f(x,y)=f(y,x)$，答案为 $f(r,r)-f(l-1,r)-f(r,l-1)+f(l-1,l-1)$，由于前一条件，答案转换为 $f(r,r)-2\times f(l-1,r)+f(l-1,l-1)$.

现在问题为如何计算 $f(x,y)$.

我们考虑在什么情况下 $i+1=i\oplus j$，对于 $i,j$ 的二进制形式 $m,n$，如果 $m_t$ 和 $n_t$ 不同是为 $1$，那么 $m_t+n_t=m_t\oplus n_t$，那么我们只需要统计有多少对 $(i,j)$ 有 $i,j$ 的每一位不同时为 $1$ 即可。

考虑设计函数 `dfs(pos,rl1,rl2)` 表示 $i,j$ 填到第 `pos` 位，$i$ 是否触及上界，$j$ 是否触及上界，首先我们需要保证 $i,j$ 的第 `pos` 位不能同时为 $1$，而下一状态十分简单，不作过多赘述。

此题最需学习的，是 $i,j$ 是同时进行填数这样的数位 $DP$，而之前只以为数位 $DP$ 只能对于单个数进行填数，这是需要注意的。

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13485485.html
```



---

## 作者：C_S_X_ (赞：0)

### 大意
共$T\leq 100$组数据，每组数据给出$l,r\leq 10^9$，问有多少对$(a,b),l\leq a,b\leq r$满足$a+b=a \oplus b$
### 题解
- $a+b=a \oplus b$即二进制下不进位加法的对数
- 考虑数位$DP$，令$f(x,y)$表示$a \leq x,b \leq y$的二进制下不进位加法对数，那么答案就是(简单容斥一下)
$f(r,r)-f(l-1,r)-f(r,l-1)+f(l-1,l-1)$
- 令$dp_{pos,lim1,lim2}$表示考虑到第$pos$位，两个数分别有没有最高位限制的方案，枚举这一位是填$(0,0)/(0,1)/(1,0)$转移即可
### 代码
```cpp
#include<bits/stdc++.h>
namespace csx_std {
	using namespace std;
	typedef long long ll;
	#define FOR(i,a,b) for (register ll i=(a);i<=(b);i++)
	#define For(i,a,b) for (register ll i=(a);i>=(b);i--)
	#define mem(i,j) memset(i,j,sizeof(i))
	#define pii pair<ll,ll>
	#define pb push_back
	#define MP make_pair
	#define fi first
	#define se second
	#define GO(u) for (register ll j=f[u];j!=-1;j=nxt[j])
	const ll N=1e5+5;
	const ll mod=1e9+7;
	inline ll qpow(ll x,ll y) {ll ret=1;for (;y;y>>=1,x=1LL*x*x%mod) if (y&1) ret=1LL*ret*x%mod;return ret;}
	inline ll Inv(ll x) {return qpow(x,mod-2);}
	inline void upd(ll &x,ll y) {x=(1LL*x+y)%mod;return;}
	inline ll chkmax(ll &x,ll y) {return (x<y)?(x=y,1):0;}
	inline ll chkmin(ll &x,ll y) {return (x>y)?(x=y,1):0;}
	inline ll read()
	{
		ll x=0,f=1;
		char c=getchar();
		while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
		while (c>='0'&&c<='9') {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
		return f*x;
	}
	inline void write(ll x)
	{
		if (x<0) x=-x,putchar('-');
		if (x>9) write(x/10);
		putchar(x%10+'0');
		return;
	}
}
using namespace csx_std;
ll T,l,r,dp[101][2][2],ans1,ans2,ans3,ans;
ll bit1[101],bit2[101];
inline ll dfs(ll pos,ll lim1,ll lim2)
{
	if (!pos) return 1;
	if (dp[pos][lim1][lim2]!=-1) return dp[pos][lim1][lim2];
	ll tmp=0;
	tmp+=dfs(pos-1,lim1&&(bit1[pos]==0),lim2&&(bit2[pos]==0));
	if ((!lim1)||bit1[pos]) tmp+=dfs(pos-1,lim1,lim2&&(bit2[pos]==0));
	if ((!lim2)||bit2[pos]) tmp+=dfs(pos-1,lim1&&(bit1[pos]==0),lim2);
	dp[pos][lim1][lim2]=tmp;
	return tmp;
}
inline ll solve(ll m1,ll m2)
{
	if (m1<0||m2<0) return 0;
	mem(dp,-1);
	ll len1=0,len2=0;
	FOR(i,0,40) bit1[i]=bit2[i]=0;
	while (m1)
	{
		bit1[++len1]=m1%2;
		m1>>=1;
	}
	while (m2)
	{
		bit2[++len2]=m2%2;
		m2>>=1;
	}
	return dfs(max(len1,len2),1,1);
}
int main()
{
	T=read();
	while (T--)
	{
		l=read(),r=read();
		ans1=solve(r,r);
		ans2=solve(r,l-1);
		ans3=solve(l-1,l-1);
		ans=ans1-2*ans2+ans3;
		write(ans),putchar('\n');
	}
	return 0;
}
/*
3
1 4
323 323
1 1000000

1
2 2
*/

```


---

## 作者：Expert_Dream (赞：0)

用数位 dp。（显然）

首先 $\oplus$ 表示的是按位异或，$\&$ 表示的是按位与。

首先有一个性质。

对于 $a+b=a \oplus b$。

然而又发现，$\oplus$ 其实是一个不进位的加法，因此，上面同等与 $a \& b = 0$。

我们设 $calc(l,r)$ 代表 $\sum_{x=0}^l \sum_{y=0}^r [x \& y = 0]$。

这样再容斥一下，就可以处理掉一些麻烦的边界问题。

答案就是 $calc(r,r)-calc(l-1,r)\times 2+calc(l-1,l-1)$。

dp 转移的过程就是按位枚举，然后枚举一下 $x$ 和 $y$ 的有没有顶上界，确实是数位 Dp 中一个重要的参数。总的来说，他记录的是有没有贴着最大的那个数，如果这个数选的不是最大的话，那么接下来的数就可以任意选择。否则依然只能最大的选指定的数，就是进位的根据。

```cpp
int dp[N][2][2];
int calc(int x,int y){
	if(x < 0 || y < 0)return 0;
	mem(dp,0);
	dp[35][1][1] = 1;
	For_(i,34,0){
		For(l,0,1){
			For(r,0,1){
				bool tmpl=(l && !((x>>i)&1ll)),tmpr=(r && !((y>>i)&1ll));
				dp[i][tmpl][tmpr]+=dp[i+1][l][r];
				if(((x>>i)&1ll)||!l) dp[i][l][tmpr] += dp[i+1][l][r];
				if(((y>>i)&1ll)||!r) dp[i][tmpl][r] += dp[i+1][l][r];
			}
		}
	}return dp[0][0][0]+dp[0][0][1]+dp[0][1][0]+dp[0][1][1];
}void solve(){
	int x,y;cin >> x >> y;
	cout<<calc(y,y)-2*(calc(x-1,y))+calc(x-1,x-1)<<endl;
}
```

---

