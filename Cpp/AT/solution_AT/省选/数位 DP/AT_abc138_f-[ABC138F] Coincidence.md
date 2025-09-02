# [ABC138F] Coincidence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc138/tasks/abc138_f

整数 $ L,\ R $ が与えられます。整数の組 $ (x,\ y) $ $ (L\ \leq\ x\ \leq\ y\ \leq\ R) $ であって、$ y $ を $ x $ で割った余りが $ y\ \text{\ XOR\ }\ x $ に等しいものの個数を $ 10^9\ +\ 7 $ で割ったあまりを求めてください。

 $ \text{\ XOR\ } $ とは 整数 $ A,\ B $ のビットごとの排他的論理和 $ a\ \text{\ XOR\ }\ b $ は、以下のように定義されます。

- $ a\ \text{\ XOR\ }\ b $ を二進数表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進数表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \text{\ XOR\ }\ 5\ =\ 6 $ となります (二進数表記すると: $ 011\ \text{\ XOR\ }\ 101\ =\ 110 $)。

## 说明/提示

### 制約

- $ 1\ \leq\ L\ \leq\ R\ \leq\ 10^{18} $

### Sample Explanation 1

条件を満たす組は $ (2,\ 2),\ (2,\ 3),\ (3,\ 3) $ の $ 3 $ 通りです。

### Sample Explanation 3

個数を $ 10^9\ +\ 7 $ で割ったあまりを計算することを忘れないでください。

## 样例 #1

### 输入

```
2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
10 100```

### 输出

```
604```

## 样例 #3

### 输入

```
1 1000000000000000000```

### 输出

```
68038601```

# 题解

## 作者：ycyaw (赞：16)

[传送门](https://atcoder.jp/contests/abc138/tasks/abc138_f)

题意：求$L\leq x\leq y\leq R$且满足$y\% x=y\oplus x$的$(x,y)$的对数。$(1\leq L\leq R\leq 10^{18})$

$y\% x$显然很不好做，我们需要转化一下。

我们发现：

$1.$ 当$2x\leq y$，有$y-x>y\% x$；

$2.$ 当$2x>y$，有$y-x=y\%x$。

$3.$ $y\oplus x\geq y-x$。

于是：

$2x\leq y$时，不存在$y\oplus x=y\% x$。

所以$2x>y$，即$x$和$y$的位数相同，最高位同时为$1$。

那么问题就转化成，求$y-x=y\oplus x$的$(x,y)$的对数。

满足$y-x=y\oplus x$，那么$y$二进制下为$1$，$x$为$0$或$1$，$y$二进制下为$0$，$x$必为$0$。

考虑数位$dp$，这种类型的数位$dp$不像常规的数位$dp$，用$0\sim r$的答案减去$0\sim l-1$的答案。

我们考虑枚举哪一位为最高位，然后$dp[i][x1][x2]$表示前$i$位，数的大小有没有达到下界$L$，有没有达到上界$R$的方案数，转移时先枚举$y$，再枚举$x$。

还有一道[类似的题](https://www.luogu.org/problem/CF1245F)，做法是相同的。

$Code\ Below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define int long long
#define hh puts("")
#define pc putchar
#define mo 1000000007
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
const int N=65;
int l,r,lenl,lenr,pl[N],pr[N],dp[N][2][2],ans;
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-1;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+(ch^48);ch=getchar();}
    return ret*ff;
}
void write(int x){if(x<0){x=-x,pc('-');}if(x>9) write(x/10);pc(x%10+48);}
void writeln(int x){write(x),hh;}
void writesp(int x){write(x),pc(' ');}
int dfs(int pos,int x1,int x2){
    if(!pos) return 1;
    if(dp[pos][x1][x2]!=-1) return dp[pos][x1][x2];
    int &res=dp[pos][x1][x2];res=0;
    int t1=x1?pl[pos]:0,t2=x2?pr[pos]:1;
    for(int y=t1;y<=t2;y++)
        for(int x=t1;x<=y;x++)
            res=(res+dfs(pos-1,x1&(x==t1),x2&(y==t2)))%mo;
    return res;
}
signed main(){
    memset(dp,-1,sizeof(dp));
    l=read(),r=read();
    while(l){
        pl[++lenl]=l&1;
        l>>=1;
    }
    while(r){
        pr[++lenr]=r&1;
        r>>=1;
    }
    for(int i=lenl;i<=lenr;i++) ans=(ans+dfs(i-1,i==lenl,i==lenr))%mo;//枚举哪个最高位为1 
    write(ans);
    return 0;
}
```


---

## 作者：Otue (赞：6)

挖掘取模性质：

* 当 $\lfloor \frac{y}{x} \rfloor=1$，有 $y\bmod x=y-x$。

* 当 $\lfloor \frac{y}{x} \rfloor>1$，有 $y\bmod x<y-x$。

挖掘异或性质：$y⊕x\geq y-x$。

把两个东西合在一起可以知道：

* 当 $\lfloor \frac{y}{x} \rfloor=1$，有 $y⊕x\geq y\bmod x$。

* 当 $\lfloor \frac{y}{x} \rfloor>1$，有 $y⊕x> y\bmod x$。

所以当且仅当 $\lfloor \frac{y}{x} \rfloor=1$ 时才会有 $y\bmod x=x⊕y$，则有 $y-x=x⊕y$。

对每一位进行考虑，$y=0$ 时 $x=0$，$y=1$ 时 $x=0$ 或 $1$。数位 dp 即可。

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 64, mod = 1e9 + 7;
int l, r, dp[N][2][2][2];

int dfs(int k, int f1, int f2, int w) { // f1表示是否为下限l，f2表示是否为上限r
	if (k == -1) return 1;
	if (dp[k][f1][f2][w] != -1) return dp[k][f1][f2][w];
	int st = f1 ? (l >> k & 1) : 0;
	int ed = f2 ? (r >> k & 1) : 1;
	int ans = 0;
	for (int i = st; i <= 1; i++) {
		for (int j = i; j <= ed; j++) {
			if (w && i != j) continue;
			ans += dfs(k - 1, f1 & (i == st), f2 & (j == ed), w & (!j));
			ans %= mod;
		}
	}
	return dp[k][f1][f2][w] = ans;
} 

signed main() {
	memset(dp, -1, sizeof dp);
	cin >> l >> r;
	cout << dfs(60, 1, 1, 1) % mod << endl;
} 
```

---

## 作者：hyxgg (赞：3)

[题目](https://www.luogu.com.cn/problem/AT_abc138_f)
## 前言
看到题解区都是数位 dp ，然而这题其实只需要稍稍分类讨论一下就行了。
# 思路
（以下提到的位、位数等描述都是在二进制下）。
## 一些显而易见的结论
### 关于位数
易发现，$x$ 和 $y$ 必定是位数相同的，（否则异或的结果位数必定等于其较大值，模的结果必定小于等于其较小值）。

### 关于每一位
#### 结论
再然后，观察到对于每一位必定只有三种情况：

- $y$ 中为 $1$，$x$ 中为 $0$。
- $y$ 和 $x$ 中都为 $1$。
- $y$ 中为 $0$，$x$ 中为 $0$。

#### 为什么？
以上三种在当前位上合法是显而易见的，而全部都是这三种情况则全部也就合法了。

但 $y$ 中为 $0$，$x$ 中为 $1$ 为什么不行呢？

假设第 $i$ 位是第一个 $y$ 中为 $0$，$x$ 中为 $1$ 的位，则此时异或的结果必然会比模的结果多 $2^{i-1}$ 而这在后面的 $i-1$ 位是不可能补回来的。 

## 做法
设 $r$ 的位数为 $rd$，$l$ 的位数为 $ld$。

枚举 $x$ 和 $y$ 的位数，设位数为 $i$。

### $ld < i < rd$ 时

因为此时不会有上下界的问题，所以除了最高位之外所有位都有上面提到的三种情况，也就是说此时的答案为：
$$3^{i-1}$$

### $i = ld$ 时

从高位往地位遍历，设当前遍历到第 $j$ 位。

#### $l$ 的第 $j$ 位为 $1$

此时只有 $x$，$y$ 的第 $j$ 位都为 $1$ 的情况不会超出范围，即只有一种情况，直接跳过看后面。

#### $l$ 的第 $j$ 位为 $0$ 

此时三种情况都是不会超出范围的，我们分开讨论：

##### $y$ 和，$x$ 中都为 $1$

这意味着之后 $j-1$ 位无论怎么搞都是不会超出范围的，于是我们直接加上 $3^{j-1}$ 。

其实并不行，这里需要在乘上一个系数，而这个系数是由其他的两种情况带来的。

##### 其他情况

可以发现这两种情况对于后面的取值是没有影响的，但是却有两种不同的取值，于是我们将后面的答案乘上一个二，也即将上面提到的系数（初始化为一）乘上一个二。

### $i = rd$ 时
和 $i = ld$ 的情况类似，只是当前位为一和为零的做法对调而已。

### 特判
当 $ld = rd$ 时，以上的做法正确性是有问题的，于是需要特判。

一样是从高位往低位遍历，设当前到 $j$ 位。

#### $j$ 位上 $l$ 为 $0$,$r$ 为 $1$
显然，这时无论什么情况都不会超。

如果这位 $x$，$y$ 都为 $0$，则之后无论如何都不会比 $r$ 大，此时的答案即为之后 $j-1$ 位上只考虑 $l$ 的方案数，参见 $i = ld$ 时的做法。

$x$，$y$ 都为 $1$ 时同理。

$y$ 上为 $1$，$x$ 上为 $0$ 时对后面没有影响，直接往后面遍历就行了。

#### $j$ 位上 $l$ 为 $1$,$r$ 为 $0$
可以发现这里没有一种情况不超界，直接跳出就行了。

#### 其他情况
其他情况都只有一种取值，且对后面没有影响，直接跳过即可。

#### 最后的特判
判一下 $x=l,y=r$ 的情况是否合法，如是则答案加一。

# 代码
代码如下，有问题评论区见。
```
#include<iostream>
#include<cstdio>
#define ll long long
#define mod 1000000007
using namespace std;
ll l,r;
int main(){
	scanf("%lld%lld",&l,&r);
	if(r==1){
		printf("1");
		return 0;
	}
	ll cr=0,tr=r,cl=0,tl=l;
	while(tr)
		cr++,tr>>=1;
	while(tl)
		cl++,tl>>=1;
	ll da=0,dda=1,qx=1,ddaa;
	ll ans=0;
	if(cl==cr){
		for(ll i=cr-1;i>=1;i--){
			if((r>>(i-1)&1)==(l>>(i-1)&1)){
				if(i==1)ans++;
				continue;
			}
			else if((r>>(i-1)&1)&&(l>>(i-1)&1)==0){
				da=0,qx=1;
				for(ll j=i-1;j>=1;j--){
					if((l>>(j-1)&1)==0){
						dda=1;
						for(ll k=1;k<j;k++){
							dda*=3;
							dda%=mod;
						}
						da+=qx*dda%mod;
						da%=mod;
						qx*=2,qx%=mod; 
					}
				}
				da+=qx;
				da%=mod;
				ans+=da;
				ans%=mod;
				da=0,qx=1;
				for(ll j=i-1;j>=1;j--){
					if((r>>(j-1)&1)){
						dda=1;
						for(ll k=1;k<j;k++){
							dda*=3;
							dda%=mod;
						}
						da+=qx*dda%mod;
						da%=mod;
						qx*=2,qx%=mod; 
					}
				}
				da+=qx;
				da%=mod;
				ans+=da;
				ans%=mod;
				if(i==1)ans++;
			}
			else break;
		}
		printf("%lld",ans); 
		return 0;
	} 
	for(ll i=cr-1;i>=1;i--){
		if(r>>(i-1)&1){
			dda=1,ddaa=1;
			for(ll j=1;j<i;j++){
				 
				dda*=3;
				dda%=mod;
			}
			da+=qx*dda%mod;
			da%=mod;
			qx*=2;
			qx%=mod;
		}
	}
	da+=qx;
	da%=mod;
	ans+=da;
	ans%=mod;
	for(ll i=cl+1;i<cr;i++){
		da=1;
		for(ll j=1;j<i;j++){
			da*=3;
			da%=mod;
		}
		ans+=da;
		ans%=mod;
	}
	da=0,qx=1;
	for(ll i=cl-1;i>=1;i--){
		if((l>>(i-1)&1)==0){
			dda=1;
			for(ll j=1;j<i;j++){
				dda*=3;
				dda%=mod;
			}
			da+=qx*dda%mod;
			da%=mod;
			qx*=2,qx%=mod;  
		}
	} 
	da+=qx;
	da%=mod; 
	ans+=da;
	ans%=mod;
	
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：hhhqx (赞：2)

对于 $x \le y$：
- 若 $2x \le y$，则 $y - x > y \bmod x$。
- 若 $2x > y$，则 $y - x = y \bmod x$。
- 有 $x \oplus y \ge y - x$。

当 $2x \le y$ 时，不可能存在 $y \bmod x = x \oplus y$ 了。

现在只需要考虑满足 $x \le y < 2x$ 且 $y - x = y \oplus x$ 的 $(x,y)$。

很多题解说只用统计二进制位数相同的 $(x,y)$，为什么？

首先 $x$ 要么和 $y$ 位数相同，要么 $x$ 比 $y$ 的位数少一。

$x \le y < 2x$ 就是 $0 \le y-x < x$。如果 $x$ 比 $y$ 的位数少一，那 $y \oplus x$ 一定是大于 $x$ 的。所以 $x$ 比 $y$ 的位数少一的情况也可以忽略了。


---

问题转化为统计多少对 $(x,y)$ 满足：

- $L \le x \le y \le R$ 且 $x$ 和 $y$ 的二进制位数相同。
- $y - x = x \oplus y$。

第二个限制等价于：对于每个二进制位，$y=1$ 则 $x=0/1$，$y=0$ 则 $x=0$。

然后就是一个比较明显的数位 dp 了。

为什么要写递推？世界属于记忆化搜索！！！

实现参考了 https://www.luogu.com.cn/article/xrraivbn 。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const LL mod = 1e9 + 7;

LL L, R;
LL f[100][2][2][2];

LL Solve(int d, int o1, int o2, int o3){
	if(d == -1) return 1;
	if(f[d][o1][o2][o3] != -1) return f[d][o1][o2][o3];
	LL ret = 0;
	int O1 = (L >> d) & 1, O2 = (R >> d) & 1;
	for(int i = (o1 ? 0 : O1); i < 2; i++){
		for(int j = i; j <= (o2 ? 1 : O2); j++){
			if(!o3 && i != j) continue;
			ret += Solve(d - 1, o1 | (i != O1), o2 | (j != O2), o3 | (j != 0));
			ret %= mod;
		}
	}
	return f[d][o1][o2][o3] = ret;
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	memset(f, -1, sizeof(f));
	cin >> L >> R;
	cout << Solve(60, 0, 0, 0);
	return 0;
}
```

---

## 作者：rnf5114 (赞：2)

观察题目可以发现对于 $y \bmod x$ 这个形式比较难受，所以我们可以把它转成 $y - r\times x$，但如果 $r \ge 2$，那么 $x \oplus y$ 则一定会在 $x$ 二进制表示下的最高位的 $1$ 再左边出现一个 $1$，又因为 $y - r\times x$ 一定小于 $x$，所以 $r$ 的取值只能为 $1$，再根据异或也可以看作不退位减法的性质，所以这时题目就转变成了值在 $l$ 到 $r$ 之间的任意数对 $(x,y)$ 满足 $x<y<2\times x$ 同时 $x$ 二进制表示下为 $1$ 的位置 $y$ 的也一定为 $1$。

这个时候就变成了一个简单数位动规了，只是因为数对的限制导致差分法不太好写所以我们的状态涉及则要有所更改。

枚举哪一位为它们共有的最高位的 $1$ 然后状态设计再新增一个判断下界的状态即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int Mod=1e9+7;
int lenl,lenr,pl[100],pr[100],dp[100][2][2],l,r,ans;
int dfs(int id,int flagl,int flagr){
	if(id==0)
		return 1;
	if(~dp[id][flagl][flagr])
		return dp[id][flagl][flagr];
	dp[id][flagl][flagr]=0;
	int di=flagl?pl[id]:0;
	int ding=flagr?pr[id]:1;
	for(int i=di;i<=ding;i++)
		for(int j=di;j<=i;j++)
			dp[id][flagl][flagr]=(dp[id][flagl][flagr]+dfs(id-1,flagl&(j==di),flagr&(i==ding)))%Mod;
	return dp[id][flagl][flagr];
}
signed main(){
	memset(dp,-1,sizeof dp);
	cin>>l>>r;
	while(l){
		pl[++lenl]=l&1;
		l>>=1;
	}
	while(r){
		pr[++lenr]=r&1;
		r>>=1;
	}
	for(int i=lenl;i<=lenr;i++)
		ans=(ans+dfs(i-1,i==lenl,i==lenr))%Mod;
	cout<<ans;
	return 0;
}

/*
       ┏┓　　　┏┓
     ┏┛┻━━━┛┻┓
     ┃　　　　　　　┃
     ┃　　　━　　　┃
     ┃　┳┛　┗┳　┃
     ┃　　　　　　　┃
     ┃　　　┻　　　┃
     ┃　　　　　　　┃
     ┗━┓　　　┏━┛
         ┃　　　┃
         ┃　　　┃
         ┃　　　┗━━━┓
         ┃　　　　　 ┣┓
         ┃　　　　 ┏┛
         ┗┓┓┏━┳┓┏┛
           ┃┫┫　┃┫┫
           ┗┻┛　┗┻┛



*/


```

---

## 作者：_Yonder_ (赞：1)

遇到这种题，首先要狠狠地♡推性质。

模运算其实就是多次的减运算，则有：

当 $y<2x$ 时，$y\bmod x=y-x$。

当 $y\ge2x$ 时，$y\bmod x<y-x$。

因为 $y-x\le x\oplus y$，所以只有 $y<2x$ 的情况下可能有解。

因为 $y-x=x\oplus y,y<2x$，所以 $x,y$ 二进制下位数相同。

手推不难发现：

当 $y$ 的第 $i$ 位为 $1$，$x$ 的第 $i$ 位为 $0/1$。

当 $y$ 的第 $i$ 位为 $0$，$x$ 的第 $i$ 位为 $0$。

数位 dp 即可，状态设计：$f_{i,l,r,w}$，$i$ 表示二进制的第 $i$ 位，$l$ 表示是否需要大于 $L$ 的第 $i$ 位，$r$ 表示是否需要小于 $R$ 的第 $i$ 位，$w$ 表示 $i\sim 64$ 位是否都为 $0$。

---

## 作者：ZnPdCo (赞：1)

这题其实是一道思维题。首先推断是一个数位 DP，由于模操作的麻烦性，所以我们得要进行一定的转换。

发现模操作其实是有以下规律：
$$
\begin{cases}
y - x = y \bmod x & \lfloor\frac{y}{x}\rfloor=1 \\
y - x > y \bmod x & \lfloor\frac{y}{x}\rfloor>1
\end{cases}
$$

> 证明：因为 $y \bmod x = y - \lfloor\frac{y}{x}\rfloor \times x$，所以当 $\lfloor\frac{y}{x}\rfloor=1$ 时，$y - x = y \bmod x$。

另外有：
$$
y \oplus x \ge y - x
$$

> 证明：有下表
>
> |  | $y=0$                  | $y=1$                  |
> | -------------------- | -------------------- | -------------------- |
> | $x=0$                  | $0 \oplus 0 = 0 - 0$ | $1 \oplus 0 = 1 - 0$ |
> | $x=1$                  | $0 \oplus 1 > 0 - 1$ | $1 \oplus 1 = 1 - 1$ |

所以有：

$$
\begin{cases}
y \oplus x \ge y \bmod x & \lfloor\frac{y}{x}\rfloor=1 \\
y \oplus x > y \bmod x & \lfloor\frac{y}{x}\rfloor>1
\end{cases}
$$

所以只有当 $\lfloor\frac{y}{x}\rfloor=1$ 时才有可能 $y \bmod x=y\oplus x$，所以有 $y - x=y\oplus x$。

现在就方便了，我们发现当 $y=0$ 时，$x$ 只能为 $0$，当 $y=1$ 时，$x$ 可以为 $0$ 或 $1$。即 $x<y$。

那么现在就可以设计 $f_i$ 表示二进制下的数位长度为 $i$，有以下代码：

```c++
for(ll y = 0; y <= 1; y++) {
	for(ll x = 0; x <= y; x++) {
		(res += f[p-1]) %= P;
	}
}
```

---

但是我们又会发现，题目要求 $L\le x\le y\le R$，也就是 $x$，$y$ 不能超出我们已有的范围。设想可以带上当前前面的数位，每次转移前判断是否越界。

但这样我们的复杂度回到了 $O(n)$，于是考虑其他做法。

---

又发现判断越界只有两种情况，一种是前面都是 $L$ 或 $R$ 的前缀，那么这一位就有越界的风险，要么前面不是前缀，那么这一位取什么都可以。

设计 $f_{i,f1,f2}$ 表示二进制下的数位长度为 $i$，$f_1$ 为前面是不是 $L$ 的前缀，这一位可能会越界，$f_2$ 为前面是不是 $R$ 的前缀，这一位可能会越界。

由于状态比较复杂，这里采用记忆化搜索：

```c++
#include <cstdio>
#include <bitset>
#include <iostream>
#include <cmath>
#define ll long long
#define N 100
#define P 1000000007
using namespace std;
bitset<N> l, r;
ll llen, rlen;
ll ans;
ll read() {
	ll x = 0; char c = '.';
	while(c < '0' || c > '9') c = getchar();
	while(c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = getchar();
	}
	return x;
} 
ll f[N][2][2];
ll v[N][2][2];
ll fun(ll p, ll f1, ll f2) {
	if(p == -1) return 1;
	if(v[p][f1][f2]) return f[p][f1][f2];
	v[p][f1][f2] = 1;
	ll res = 0;
	ll st = f1 ? l[p] : 0;				// 如果前面是前缀，这一位要从 l[p] 开始枚举 
	ll ed = f2 ? r[p] : 1;
	for(ll y = st; y <= ed; y++) {
		for(ll x = st; x <= y; x++) {
			(res += fun(p-1, f1 /*如果前面是L的前缀*/ & (x==st) /*而且这一位也取了临界值*/, f2 & (y==ed))) %= P;
		}
	}
	return f[p][f1][f2] = res;
}
ll msb(bitset<N> x) {
	for(ll i = x.size() - 1; i >= 0; i--) {
		if(x[i] == 1) return i;
	}
	return 0;
}
int main() {
	l = read(), r = read();
	llen = msb(l);
	rlen = msb(r);
	
	for(ll i = llen; i <= rlen; i++) {
		(ans += fun(i - 1, i == llen /*采用临界值*/, i == rlen)) %= P;
	}
	
	printf("%lld", ans);
}
```



---

## 作者：AC_love (赞：0)

因为有 $x \le y$，则 $y \bmod x \ge y - x$。

同时我们知道 $y - x \ge x \oplus y$，因此显然有 $y \bmod x = y - x = x \oplus y$。

考虑如何满足 $y - x = x \oplus y$。先拆位，对于任意一位，一定有 $y - x \le x \oplus y$。只要任意一位没有取等，最后也一定取不到等。

所以对于任何一个二进制位，一定有 $y - x = x \oplus y$。那么如果 $y$ 的这一位是 $0$，$x$ 这一位也只能是 $0$。如果 $y$ 的这一位是 $1$，则 $x$ 这一位可以是 $0$ 也可以是 $1$。

在此基础上，我们还要满足 $y \bmod x = y - x$。这个怎么实现？考虑 $y$ 的二进制下的最高位，若 $x$ 这一位也为 $1$，则一定满足。若 $x$ 这一位为 $0$，此时必须有 $y < 2x$，那么 $x$ 的下一位必定是 $1$。而根据刚才我们的结论，$x$ 某一位是 $1$ 时 $y$ 必须也是 $1$，则 $y$ 的这一位是 $1$，则 $x$ 再下一位也是 $1$……以此类推。推到最后我们发现无法满足条件，所以 $x$ 这一位不可能是 $0$。

剩下的实现很简单，数位 DP 即可。

需要注意的是这个数位 DP 不能像常规数位 DP 那样拆成 $[1, L - 1]$ 和 $[1, R]$ 分开计算，因为这样无法统计 $x$ 在 $[1, L - 1]$ 而 $y$ 不在时的贡献。所以必须在 DP 时同时记录上下界。

[code](https://atcoder.jp/contests/abc138/submissions/65558565)

---

## 作者：Shiota_Nagisa (赞：0)

为什么大家写的都是记忆化搜索，没人写正向递推（）

[原题传送门](https://atcoder.jp/contests/abc138/tasks/abc138_f)

看到数据范围，考虑 $O(1)$ 算法，然而并不可行，所以我们考虑 $O(\log n)$ 算法，就是数位 dp。

考虑将 $y \bmod x$ 这一坨东西转换，我们注意到，$x \oplus y \ge y-x$ ，所以为了满足条件 $y-x \le x \bmod y$ , 接着，我们又注意到 $x \bmod y = x-\lfloor x/y \rfloor \times y$，易得，当且仅当 $ \lfloor x/y \rfloor=1$ ，即 $2 \times y>x$ 时，有 $y-x \le x \bmod y$ ，且当 $2 \times y>x$ 时，$x \bmod y = x-y$ ，所以我们可以将问题转化为$y-x=x \oplus y$。

可以发现，对于一位的二进制，当 $x_{i}=1$ ，$y_{i}=1$ 或 $0$ ，当 $x_{i}=0$ ，$y_{i}$ 只能等于 $0$ ，$x$ 与 $y$ 二进制位数一样，特殊的，为了保证 $2 \times y>x$ ，对于 $x$ 与 $y$ 的第一位，必须都取 $1$。

我们可以利用数位 dp 解决该问题。


```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long
const int mod=1e9+7;
int dp[66][2][2][2];//dp[i][j][k][l]为，当前处理第i位，x取顶的状态是i，y取顶的状态是j，x，y是否都已取值的状态为l 
int l,r;
int cal(int x,int y){
	for(int i=0;i<=60;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++) for(int l=0;l<2;l++) dp[i][j][k][l]=0;
	dp[60][1][1][0]=1; 
	for(int i=59;i>=0;i--){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				for(int l=0;l<2;l++){
					bool nowj,nowk;
					if(j==1&&!((x>>i)&1)){
						nowj=1;
					}
					else nowj=0;
					if(k==1&&!((y>>i)&1)){
						nowk=1;
					}
					else nowk=0;
					dp[i][nowj][nowk][l]=(dp[i][nowj][nowk][l]+dp[i+1][j][k][l])%mod;
					if(nowj==0&&nowk==0) dp[i][j][k][1]=(dp[i][j][k][1]+dp[i+1][j][k][l])%mod;
					if(nowj==0&&l==1) dp[i][j][nowk][l]=(dp[i][j][nowk][l]+dp[i+1][j][k][l])%mod;
				}
			}
		}
	}
	return dp[0][0][0][1]+dp[0][0][1][1]+dp[0][1][0][1]+dp[0][1][1][1];
}
signed main(){
	cin>>l>>r;
	int add=cal(r,r)%mod,add2=cal(l-1,r)%mod,add3=cal(l-1,l-1)%mod,add4=cal(r,l-1)%mod;
	cout<<(add-add2+add3-add4+mod)%mod<<endl;//做二维差分，得出答案 
}
```

---

## 作者：KMYC (赞：0)

课上老师讲的题。

数位 dp，选择采用递归+记忆化搜索，每次记录当前 $X$ 的二进制位和 $Y$ 的二进制位,然后枚举接下来的 $X$ 和 $Y$ 的二进制位，根据取模与异或性质可得：

$Y=0$ 时 $X=0$，$Y=1$ 时 $X=0或1$。

一部分思路在注释里。（代码不是我写的，所以马蜂与我以前的题解不同）

```c++
#include<iostream>


long long l, r;

bool mem[64][2][2][2];
long long cache[64][2][2][2];
long long solve(int len, bool z, bool ex, bool ey) {
  //考虑前 len 位 ex:x 的二进制当下的值 ey:y 的二进制当下的值
	if (len < 0) {
		return 1;
	}
	else {
		
		if (mem[len][z][ex][ey]) return cache[len][z][ex][ey];
		//记忆化
		int bl = (l >> len) % 2;
		int br = (r >> len) % 2;
		long long sum = 0;
		for (int bx = 0; bx <= 1; bx++)
			for (int by = 0; by <= 1; by++) {
         //枚举 x , y 的二进制值
				if (z and bx == 0 and by == 1) continue;
				if (bx == 1 and by == 0) continue;
				if (ex and bx < bl) continue;
				if (ey and by > br) continue;
        //判断是否满足条件y=0 时 x=0，y=1时 x=0或 1
1

				sum += solve(len-1, z and bx == 0 and by == 0, ex and bx == bl, ey and by == br);
			}
		mem[len][z][ex][ey] = true;
		return cache[len][z][ex][ey] = sum % 1000000007;
        //记忆化
	}
}
int main(){
	int n; st::cin>>n;
	while(n--){
		std::cin>>l>>r;
		std::cout<<solve(62,true,true,true)<<"\n";
	}
}
```

---

## 作者：cyq32ent (赞：0)

显然 $y-x\leq y\operatorname{xor} x$，$y\bmod x\leq y-x$，故 $y\operatorname{xor} x=y-x$。

考虑数位 $dp$，设 $dp_{L,z,I,J}$ 为考虑前 $L$ 位，当前数字是否为`0`，$x$ 是否到达边界，$y$ 是否到达边界。那么可以枚举 $x$，$y$ 的当前位并转移。比如，若当前状态为 $(L,z,I,J)$，$x$、$y$ 的当前位分别为 $i,j$，设$l$、$r$在当前位的边界为 $A$、$B $，则 $f_{L,z,I,J}\leftarrow f_{L,z,I,J}+f_{L-1,z\land ij=0,I\land i=A,J\land j=B}$。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r,mem[64][2][2][2],f[64][2][2][2];
int solve(int L,int z,int I,int J){
	if(!~L)return 1;
	int s=0,A=(l>>L)&1,B=(r>>L)&1;
	if(mem[L][z][I][J])return f[L][z][I][J];
	for(int i=0;i<2;i++)for(int j=i;j<2;j++){
		if(z&&(!i)&&j)continue;
		if((I&&i<A)||(J&&j>B))continue;
		s+=solve(L-1,z&&!(i||j),I&&i==A,J&&j==B);
	}
	mem[L][z][I][J]=1;
	return f[L][z][I][J]=s%1000000007;
}
signed main(){
	cin>>l>>r;
	cout<<solve(62,1,1,1);
	return 0;
}
```

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc138_f)

发现当 $y\bmod x=y\oplus x$ 的时候，必然满足 $y\bmod x=y-x$，~~下浅浅乱证一下~~。

- $y=1.....$ 然后 $x=1.....$。于是就显然了吧。

- $y=1.....$ 然后 $x=0.....$。可以发现 $y\oplus x=1.....$，而 $y\bmod x<x=0.....$，所以这种方案显然不合法。

我在做这道题的时候顺便发现，对于一个 $y$，若没有 $x$ 的限制，那么 ${\rm ans}(y)=2^{\rm cnt-1}$，其中 $\rm cnt$ 表示 $y$ 在二进制下 $1$ 的个数，这个东西也是分类讨论一下即可。

一开始我想用这个东西来解决这道题，可是 $x$ 的限制死死缠着我，让我无法有突破口。那么直接数学解决不行就 dp 吧，可是我太久没练数位 dp 了然后没写出来。

类比模板数位 dp 但有所区别，由于 $x,y$ 都有限制，那么我们要同时记录 $x,y$ 是否是上下界。具体看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1e9+7;
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
ll l,r,dp[65][2][2][2];
ll inc(ll x,ll y){return x+y>=mod?x+y-mod:x+y;}
// f1 f2 表示是否是上下界
// w 表示前面是否有数
ll dfs(int k,int f1,int f2,int w)
{
	if(k==-1)return 1;
	if(dp[k][f1][f2][w]!=-1)return dp[k][f1][f2][w];
	int xbit=f1?(l>>k&1):0;
	int ybit=f2?(r>>k&1):1;
	ll ans=0;
	for(int i=xbit;i<=1;i++)
		for(int j=i;j<=ybit;j++)
			if(!w||i==j)ans=inc(ans,dfs(k-1,f1&(i==xbit),f2&(j==ybit),w&(!j)));
	return dp[k][f1][f2][w]=ans;
}
int main(){
	memset(dp,-1,sizeof(dp));
	l=read();r=read();
	printf("%lld",dfs(60,1,1,1));
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

来一个递推 dp。

考虑异或和取模的性质：

 - 若 $x \le y < 2x$，则 $y \bmod x = y - x$，$y \oplus x \ge y - x$。
 
 - 若 $y > 2x$，则 $y \bmod x = y - x$，$y \oplus x > y - x$。
 
由此可见，如果让 $y \bmod x = y \oplus x$，需要满足 $x \le y < 2x$，也就是 $x$ 和 $y$ 在二进制表示下位数相同。

考虑数位 dp。不妨设 $f_{i, j, k}$ 表示当前填完了 $i$ 位（从高往低），是否顶上界，是否顶下界。我们考虑当前这一位的情况：

- 若 $y$ 填 $1$，$x$ 填 $0$，则 $(y - x)_i = 1, (y \oplus x)_i = 1$，合法。

- 若 $y$ 填 $1$，$x$ 填 $1$，则 $(y - x)_i = 0, (y \oplus x)_i = 0$，合法。

- 若 $y$ 填 $0$，$x$ 填 $0$，则 $(y - x)_i = 0, (y \oplus x)_i = 0$，合法。

- 若 $y$ 填 $0$，$x$ 填 $1$，则 $(y - x)_i = 1, (y \oplus x)_i = 1$。但是这种情况要讨论一下。我们再相减的时候从前面借了一位。找到这一位往前第一个 $1$ 的位置，也就是借位的位置。我们发现，无论 $x$ 这一位填的是 $0$ 还是 $1$ 都是不合法的。因此不可能出现借位的情况。

因此确定，$x$ 该位所填的一定 $\le$ $y$ 该位所填的。dp 转移即可。

```cpp
auto Lg = [&](int x) { dep(i, 63, 0) if ((x >> i) & 1ll) return i; };
scanf("%lld%lld", &l, &r); int len1 = Lg(l) + 1, len2 = Lg(r) + 1;
auto solve = [](int l, int r, int n) -> int {
	rep(i, 0, n - 1) R[i] = (r >> i) & 1ll, L[i] = (l >> i) & 1ll;
	memset(f, 0, sizeof f); f[n - 1][1][1] = 1ll;
	dep(i, n - 1, 1) rep(j, 0, 1) rep(k, 0, j) rep(a, 0, 1) rep(b, 0, 1) {
		if ((a and j > R[i - 1]) or (b and k < L[i - 1])) continue;
		(f[i - 1][a & (j == R[i - 1])][b & (k == L[i - 1])] += f[i][a][b]) %= mod;
	} int s = 0; rep(i, 0, 1) rep(j, 0, 1) (s += f[0][i][j]) %= mod; return s;
}; rep(i, len1, len2) ans += solve(max(1ll << i - 1, l), min((1ll << i) - 1, r), i);
printf("%lld\n", ans % mod); return 0;
```

---

