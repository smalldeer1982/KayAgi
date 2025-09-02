# Three Colors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2019/tasks/tenka1_2019_d

$ N $ 個の整数が与えられます。$ i $ 個目の整数は $ a_i $ です。 与えられたすべての整数を赤、緑、青の $ 3 $ 色のいずれかで塗り、以下の条件を満たすようにする方法の個数を $ 998244353 $ で割ったあまりを求めてください。

- 赤、緑、青で塗られた整数の総和をそれぞれ $ R,G,B $ とする。三辺の長さがそれぞれ $ R,G,B $ であるような正の面積の三角形が存在する。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 300 $
- $ 1\ \leq\ a_i\ \leq\ 300(1\leq\ i\leq\ N) $
- 入力はすべて整数である

### Sample Explanation 1

三角形の三辺の長さがそれぞれ $ 1,2,2 $ となるように整数を塗り分けるしかなく、そのような塗り分け方は $ 18 $ 通り存在します。

## 样例 #1

### 输入

```
4
1
1
1
2```

### 输出

```
18```

## 样例 #2

### 输入

```
6
1
3
2
3
5
2```

### 输出

```
150```

## 样例 #3

### 输入

```
20
3
1
4
1
5
9
2
6
5
3
5
8
9
7
9
3
2
3
8
4```

### 输出

```
563038556```

# 题解

## 作者：灵茶山艾府 (赞：10)

### 提示 1

正难则反，计算不满足条件的方案数。用 $3^n$ 减去不满足条件的方案数，就得到了满足条件的方案数。

### 提示 2

设 $s$ 为 $a$ 中元素之和。

如果某种颜色的元素和至少为 $\left\lceil\dfrac{s}{2}\right\rceil$，则无法满足要求（否则可以满足）。

那么问题变成从 $n$ 个数中选一些数，元素和**至少**为 $\left\lceil\dfrac{s}{2}\right\rceil$ 的方案数，这是「至少装满型」0-1 背包，具体可以看 [这个讲解](https://www.bilibili.com/video/BV16Y411v7Y6/)。

注意在「不选」的情况下，我们可以涂成另外两种颜色，这就是为什么代码中的转移方程有个乘 $2$。

我们可以假设 R 的元素和至少为 $\left\lceil\dfrac{s}{2}\right\rceil$，计算出方案数后，乘以 $3$ 就得到了 G 和 B 的情况。（也可以把 $f[0]$ 初始化成 $3$，这样可以少做一次乘法）

### 提示 3

还有一个特殊情况没有考虑。

如果 $s$ 是偶数，那么我们在计算 R 的时候，会存在 $R=G=\dfrac{s}{2}$ 的情况，而在计算 G 的时候，也会把 $R=G=\dfrac{s}{2}$ 的情况计算进去，这样就算重复了。

所以还需要计算从 $n$ 个数中选一些数，元素和**恰好**为 $\dfrac{s}{2}$ 的方案数，这也是 0-1 背包。

```go
package main
import ."fmt"
func max(a, b int) int { if b > a { return b }; return a }

func main() {
	const mod = 998244353
	var n, v, s, dup int
	var f, g [90001]int
	f[0] = 3
	g[0] = 3
	pow3 := 1
	for Scan(&n); n > 0; n-- {
		Scan(&v)
		s += v
		for j := s; j >= 0; j-- {
			f[j] = (f[j]*2 + f[max(j-v, 0)]) % mod // 至少装满
			if j >= v {
				g[j] = (g[j] + g[j-v]) % mod // 恰好装满
			}
		}
		pow3 = pow3 * 3 % mod
	}
	if s%2 == 0 {
		dup = g[s/2] // 恰好装满 s/2
	}
	ans := pow3 - (f[(s+1)/2] - dup)
	Print((ans%mod + mod) % mod)
}
```


---

## 作者：shinkuu (赞：2)

这题现在的一篇题解复杂度不太对（虽然卡过了），一篇要用斯特林数，那就写一篇和标程一个思路的题解吧。

正难则反，考虑计算有多少个三角形满足 $a\ge b+c$，也就是 $a\ge \left\lceil \dfrac{S}{2}\right\rceil$，其中 $a,b,c$ 为三边长，$S$ 为所有边长度之和。介于值域较小，可以使用背包 dp 解决。设 $f_{i,j}$ 为前 $i$ 条边，$a=j$ 的方案数。则有：

$$f_{i,j}=2\times f_{i-1,j}+f_{i-1,j-a_i}$$

则可以求出不符合题目要求的方案数为 $\sum_{i=\left\lceil \frac{S}{2}\right\rceil}^S f_{n,i}\times 3$。

结束了吗？

还没有。

因为我们会发现，如果存在 $a=b=\dfrac{S}{2},c=0$，则这种情况会被多减去一次。于是再做一个类似的 dp 求出方案数。设 $g_{i,j}$ 为前 $i$ 个数，$a=\dfrac{S}{2}$ 的方案数，则有：

$$g_{i,j}=g_{i-1,j}+g_{i-1,j-a_i}$$

然后将上文方案数减去 $g_{n,\frac{S}{2}}\times 3$ 即可。注意只有 $S$ 为偶数时要减去。

最后再用所有方案数减去不满足方案数即可。

code：

```cpp
int n,m,f[N][M],g[N][M],e[N];
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&e[i]);
		m+=e[i];
	}
	f[0][0]=g[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(j<e[i]){
				f[i][j]=2ll*f[i-1][j]%mod;
				g[i][j]=g[i-1][j];
			}else{
				f[i][j]=(2ll*f[i-1][j]+f[i-1][j-e[i]])%mod;
				g[i][j]=(g[i-1][j]+g[i-1][j-e[i]])%mod;
			}
		}
	}
	int ans=0;
	for(int i=(m+1)/2;i<=m;i++)
		ans=(ans+f[n][i])%mod;
	if(m%2==0)
		ans=(ans-g[n][m/2]+mod)%mod;
	ans=3ll*ans%mod;
	printf("%d\n",(qpow(3,n)-ans+mod)%mod);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：_Weslie_ (赞：0)

时代真的变了。$2019$ 年赛时只有 $4$ 人通过的题，$2025$ 得有一车人赛时过掉吧……

## Solution AT_tenka1_2019_d

### Idea

其实我个人很喜欢这个题的一点：**正难则反**。

我们设 $r$ 为红色的和，$g$ 为绿色的和，$b$ 为蓝色的和。

那么正的做就是要求 $b<r+g$ 的方案数（其中 $r<b$ 且 $g<b$）。由于三种颜色等价，所以求出来答案要乘上 $3$。

但是这样很难，我们考虑反着：即求 $b\ge r+g$ 的方案数。

我们设 $f_{i,j}$ 表示前 $i$ 个数 $b$ 为 $j$ 的方案数。那么有：$f_{i,j}=f_{i-1,j}\times 2+f_{i-1,j-a_i}$。

$f_{i-1,j-a_i}$ 大家都理解（即这个数加到 $b$ 里面去）；$f_{i-1,j}$ 的系数 $2$ 则是因为你把他放进 $r$ 或者 $g$ 是等价的。所以要乘 $2$。

于是$b\ge r+g$ 的方案数就是 $\sum\limits_{i=x}^{sum}f_{n,i}$，其中 $x=\lfloor\dfrac{n+1}{2}\rfloor$ 且 $sum=\sum\limits_{i=1}^na_i$。$x$ 的取值应该挺好理解的，这是利用 C++ 的特性（整除），求出第一个大于等于 $\dfrac{n}{2}$ 的整数。

是吗？

不是。

因为你发现：$b=r=\dfrac{sum}{2}$ 且 $g=0$ 时会被多减掉一次。

为什么？

因为我们算出一种 $b=\dfrac{sum}{2}$（$sum$ 为偶数）的方案，就会对应 $b=r$ 和 $b=g$ 两种情况。所以要补上一次。

那么我们定义 $g_{i,j}$ 为 $b=\dfrac{sum}{2}$ 时，$r=j$ 的方案数。有 $g_{i,j}=g_{i-1,j}+g_{i-1,j-a_i}$（背包 dp 模板）。

方案总数是 $3^n$，所以答案就是 $3^n-3\times \sum\limits_{i=x}^{sum}f_{n,i}+3\times w\times g_{n,\frac{sum}{2}}$，其中 $x=\lfloor\dfrac{n+1}{2}\rfloor$ 且 $sum$ 为偶数时 $w=1$，反之为 $0$。

### Code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=305,mod=998244353;
ll dp1[N][N*N],dp2[N][N*N];
int n,a[N],sum;
ll qpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    dp1[0][0]=1;dp2[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++){
            if(j<a[i]){
                dp1[i][j]=dp1[i-1][j]*2%mod;
                dp2[i][j]=dp2[i-1][j];
            }
            else{
                dp1[i][j]=(dp1[i-1][j]*2+dp1[i-1][j-a[i]])%mod;
                dp2[i][j]=(dp2[i-1][j]+dp2[i-1][j-a[i]])%mod; 
            }
        }
    }
    ll ans=0;
    for(int i=(sum+1)/2;i<=sum;i++)ans=(ans+3*dp1[n][i])%mod;
    if(sum%2==0)ans=(ans-3*dp2[n][sum/2]%mod+mod)%mod;
    printf("%lld",(qpow(3,n)-ans+mod)%mod);
}
```

---

## 作者：Louis_lxy (赞：0)

首先容易发现直接计算答案并不好做，于是考虑反着算，用所有可能减去不合法的就可以了。

记 $f(i,j)$ 表示前 $i$ 个，使得 $R\ge j$ 的方案数，$f(i,j)=f(i-1,j-a_i)+f(i-1,j)\times2$，记 $g(i,j)$ 表示前 $i$ 个，使得 $R=j$ 的方案数，$g(i,j)=g(i-1,j)+g(i-1,j-a_i)$。稍微解释一下，就是这个点涂不涂红色所造成的不同贡献。

然后答案就是 $3^n-3\times f(n,\lceil\frac{\sum a}{2}\rceil)+[(\sum a)\bmod2=0]\times3\times g(\lfloor\frac{\sum a}{2}\rfloor)$，解释一下，$3^n$ 就是所有可能，然后去剪掉大于等于 $\lceil\frac{\sum a}{2}\rceil$ 的方案数，$\times3$ 是因为仅仅计算了红色的，其他颜色一样，加上 $[(\sum a)\bmod2=0]\times3\times g(\lfloor\frac{\sum a}{2}\rfloor)$ 是因为当 $(\sum a)\bmod2=0$ 时刚好一半的会被计算两次（交换颜色顺序本质没变）。

---

## 作者：xukehg (赞：0)

先考虑直接暴力 dp，然后你会发现你至少要存两维状态去记录选出的颜色大小的状态，死的十分彻底。

然后我们考虑反过来，因为总共的情况数是确定的，我们可以把总共的状态减去非法的状态。定义 $dp_{i,j}$ 表示到了第 $i$ 位钦定红色为最大值且和为 $j$ 的情况数，蓝色和绿色同理，显然第一位可以滚掉，我们可以得到式子 $dp_j = dp_j \times 2 + dp_{j - a_i}$。然后你会发现第二个样例过不去。

考虑总和是偶数且最大值为总和的一半，则此时不能直接乘 $3$，会有重复。我们再单独做一次 dp 即可去掉重复部分。

[记录](https://atcoder.jp/contests/tenka1-2019/submissions/59312913)。

---

## 作者：fight_for_humanity (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_tenka1_2019_d)。

[Better experience](https://www.cnblogs.com/fight-for-humanity/p/18374877)。

#### Analysis

模拟赛的一道题。朴素的 dp 就是 $dp_{i,j,k}$ 表示染了前 $i$ 个，红的总和为 $j$，黄的总和为 $k$ 的方案数。

考虑优化。由于合法方案很多，不妨计算不合法的方案数，我们记其为 $ans$。

观察合法的判定式子：$a + b > c,a + b + c = presum_i$，因此可以只记一个 $a+b$。$dp_{i,j}$ 表示前 $i$ 个，小的两个结果之和为 $j$ 的方案数。最后统计时只需要将 $j \le \lfloor \frac{sum}{2} \rfloor$ 的 $f_{n,j}$ 加到 $ans$ 中去。

有转移 $dp_{i,j} \gets dp_{i-1,j} + dp_{i-1,j-a_i} \times 2$。通过限定 $j$ 的上界为 $\lfloor \frac{sum}{2} \rfloor$ 可以实现统计。
这里只统计了三种颜色之间的相对关系，所以最后计算时要乘以 $3$。

但是我们发现当 $sum$ 为偶数时会重复统计，即 $a + 0 = c,a = c = \lfloor \frac{sum}{2} \rfloor$ 的情况。
令 $g_{i,j}$ 表示 $c = \lfloor \frac{sum}{2} \rfloor$ 时，$a = j$ 的方案数，这样转移过程就是模拟只选 $a$ 或 $c$ 的过程。
$g_{i,j} \gets g_{i-1,j-1} + g_{i-1,j-a_i}$。从不合法方案总数 $ans$ 中减去 $g_{\lfloor \frac{sum}{2} \rfloor}$ 即可。

最后用全集 $3^n$ 减去 $ans \times 3$。
对于解决方案中的 $f,g$ 的转移，可以删去一维倒序地类似 01 背包一样转移，空间更优秀。

#### CODE

```cpp
inline int mul(int x,int y){ return 1ll * x * y % mod; }
inline int fpow(int a,int k){
	int res = 1;
	while(k){
		if(k & 1)res = mul(res,a);
		a = mul(a,a);
		k >>= 1;
	}
	return res;
}
inline int add(int x,int y){ return x + y >= mod ? x + y - mod : x + y; }
inline int sub(int x,int y){ return x - y < 0 ? x - y + mod : x - y; }
inline void toadd(int &x,int y){ x = add(x,y); }
int n,a[N],tot,f[N],g[N],ans,mid;
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;++i)scanf("%d",&a[i]),tot += a[i];
	mid = (tot >> 1);
	f[0] = 1;
	for(int i = 1;i<=n;++i)
		for(int j = mid;j >= a[i];--j)
			toadd(f[j],mul(2,f[j-a[i]]));
	for(int i = 0;i<=mid;++i)toadd(ans,f[i]);
	if(!(tot&1)){
		g[0] = 1;
		for(int i = 1;i<=n;++i)
			for(int j = tot;j>=a[i];--j)
				toadd(g[j],g[j-a[i]]);
		ans = sub(ans,g[mid]);
	}
	printf("%d",sub(fpow(3,n),mul(3,ans)));
	return 0;
}
```

---

## 作者：Che_001 (赞：0)

题面传送门：[AT2491](https://www.luogu.com.cn/problem/AT4921)

## 题意

有 $n$ 个数，可以给它们染 Red，Green，Blue 三种颜色，定义一种染色方案为合法方案：

令 $ R,G,B $ 分别为染了 Red，染了Green，染了 Blue 的所有石头的权值和，当且仅当所有石头都染上了一种颜色，且存在一个三角形的三边为 $ R,G,B $ 时方案合法。 

求合法方案数 $ ans \bmod 998244353 $ 。

## 题目分析

考虑总方案数为 $3^n$ 次方，

~~枚举铁定 TLE~~

正难则反，所以我们考虑怎么求出不合法的方案数，发现 $n\leq 300$ 故考虑 dp 求解。

令 $ f_{i,j} $ 为当前考虑到第 $i$ 个数，两条短边和为 $j$ 的方案数，易得转移方程：
$$
f_{i,j}\gets f_{i-1,j-a_i}\times 2
$$
注意到，如果 $a_i$ 的总和 $sum$ 是偶数的话，那么当：

1.  $ \displaystyle R=B= \frac{sum}{2}(R+B=G) $ 

2.  $ \displaystyle R=G= \frac{sum}{2}(R+G=B) $ 

3.  $ \displaystyle B=G= \frac{sum}{2}(B+G=R) $

这三种情况下时，就会计算两次贡献。再 dp 一次多余的部分并剪掉即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
long long ans,n,sum;
long long a[350],dp[100010],g[100010];
const long long mod=998244353;
long long Pow(int k)
{
	long long res=1;
	for(int i=1;i<=k;i++)
		res=((res<<1)+res)%mod;
	return res;
}
int main(int argc,const char *argv[])
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		sum+=a[i];
	}
	dp[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=sum/2;j>=a[i];j--)
			dp[j]=(dp[j]+dp[j-a[i]]*2)%mod;
	for(int i=0;i<=sum/2;i++)
		ans=(ans+dp[i])%mod;
	if(sum%2==0)
	{
		g[0]=1;
		for(int i=1;i<=n;i++)
			for(int j=sum;j>=a[i];j--)
				g[j]=(g[j]+g[j-a[i]])%mod;
		ans=(ans-g[sum/2]+mod)%mod;
	}
	printf("%d",(Pow(n)-ans*3%mod+mod)%mod);
	return 0;
}

```

---

## 作者：Lucky_Glass (赞：0)

## \# 解析

显然要DP……

要求构成三角形，则有最长边小于两短边之和，但是在这个限制下，很难设计出状态能够表示最长边。**正难则反**，求“最长边大于等于两短边之和”的方案数。

因为三边之和 $S$ 固定，两短边之和不超过 $\lfloor\frac S2\rfloor$。于是设计状态 $f_{i,j}$ 表示前 $i$ 个数字中选出一些分为两组（两个较短边）的方案数，转移也比较简单，要么不选（$f_{i-1,j}$）要么分到两组中的一个（$2\times f_{i-1,j-a_i}$）。

但是这样计算有些问题，会分出某一个集合是空集的情况，只要有一种 $sum(C)=j$ 的方案，就会对应两种（$A=C,B=\varnothing$ 和 $A=\varnothing,B=C$）非法情况。于是再做一个DP，$g_{i,j}$ 表示前 $i$ 个数选一些数使得和为 $j$ 的方案数。

$f_{n,i}-2\times g_{n,i}$ 则是两短边之和为 $i$ 的方案数，再从三个集合中选出一个作为最长边，即 $3\times(f_{n,i}-2\times g_{n,i})$；于是可以计算得到**在所有集合非空的方案中**非法方案数的数量 $d$：
$$
d=\sum_{j=1}^{\lfloor\frac S2\rfloor}3\times(f_{n,i}-2\times g_{n,i})
$$
最后就剩求总方案数了。注意到由于“非法方案数”求的是在所有集合非空的前提下的非法方案，总方案也应保证集合非空。

相当于把 $n$ 个有区别的数分到 $3$ 个有区别的集合中使得集合非空的方案数。可以用第二类斯特林数（把 $n$ 个有标号球放入 $m$ 个无标号盒子里且盒子不空）。最后答案为 $3!\times S(n,3)-d$。

---

## \# 源代码

```cpp
/*Lucky_Glass*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define ci const int &
const int N=305,MOD=998244353;
inline int Add(ci a,ci b){return a+b>=MOD? a+b-MOD:a+b;}
inline int Sub(ci a,ci b){return a-b<0? a-b+MOD:a-b;}
inline int Mul(ci a,ci b){return int(1ll*a*b%MOD);}
inline int Pow(ci a,ci b){return b? Mul(Pow(Mul(a,a),b>>1),(b&1)? a:1):1;}
const int INV2=Pow(2,MOD-2);

int n;
int num[N],f[2][N*N],g[2][N*N],w[N][4];

inline int Read(int &r){
	int b=1,c=getchar();r=0;
	while(c<'0' || '9'<c) b=c=='-'? -1:b,c=getchar();
	while('0'<=c && c<='9') r=(r<<1)+(r<<3)+(c^'0'),c=getchar();
	return r*=b;
}
int main(){
	Read(n);
	w[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=3;j++)
			w[i][j]=Add(w[i-1][j-1],Mul(j,w[i-1][j]));
	int S=0;
	for(int i=1;i<=n;i++) S+=Read(num[i]);
	S>>=1;
	f[0][0]=g[0][0]=1;
	for(int i=1;i<=n;i++){
		int I=i&1,J=!I;
		for(int j=0;j<=S;j++) f[I][j]=f[J][j],g[I][j]=g[J][j];
		for(int j=num[i];j<=S;j++){
			f[I][j]=Add(f[I][j],Mul(2,f[J][j-num[i]]));
			g[I][j]=Add(g[I][j],g[J][j-num[i]]);
		}
	}
	int del=0;
	for(int i=1;i<=S;i++){
		int thi=Mul(f[n&1][i],INV2);
		thi=Sub(thi,g[n&1][i]);
		del=Add(del,Mul(thi,6));
	}
	int ans=Mul(w[n][3],6);
	printf("%d\n",Sub(ans,del));
	return 0;
}
```

---

## THE END

### Thanks for reading!

---

