# Array Without Local Maximums

## 题目描述

$Ivan$偶然发现一个旧的生日礼物。礼物是一个含有$n$个元素的数组，每个元素都介于$1$和$200$之间。但是现在数组已经很旧了，有的数字难以看清。他记得对于所有元素，它的相邻元素中至少有一个不小于它。也就是说：

$a_1\le a_2,a_n\le a_{n-1}$且$a_i\le \max \left( a_{i-1},a_{i+1} \right) $对于任意$i\in \left[ 2,n-1 \right] $都成立。

$Ivan$想知道有多少种方案能够还原这个数组。当然，还原后要保证每个元素仍然介于$1$和$200$之间。输出方案数对$998244353$取模的结果。

## 说明/提示

第一个样例，$a_2$只能为$2$。

第二个样例，$a_1=a_2$，所以有$200$中可能。

## 样例 #1

### 输入

```
3
1 -1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
-1 -1
```

### 输出

```
200
```

# 题解

## 作者：quantum11 (赞：15)

$f_{ijk}$ 第$i$个数为$j$时，$k={0,1,2}$分别表示它左边的数小于，等于，大于它的方案数。

小于的情况，与大于类似，$0,1,2$都可以加

等于的情况：只要把前面那个数的$0,1,2$都加上。

大于的情况：加上大于这个数的数字方案数的前缀和，可以加上$1,2$的情况。

空间开不下用滚动数组。

```
#include<bits/stdc++.h>
using namespace std;
const int mo=998244353;
long long n,k,a[100005],f[2][205][3],ans,s;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",a+i);
	if(a[1]==-1) for(int i=1;i<=200;++i) f[k][i][0]=1;else f[k][a[1]][0]=1;
	for(int i=2;i<=n;k^=1,++i){
		s=0;
		for(int j=1;j<=200;++j){
			f[k^1][j][0]=(a[i]==-1||a[i]==j)?s:0;
			(s+=f[k][j][0]+f[k][j][1]+f[k][j][2])%=mo;
		}
		for(int j=1;j<=200;++j)
		f[k^1][j][1]=(a[i]==-1||a[i]==j)?(f[k][j][0]+f[k][j][1]+f[k][j][2])%mo:0;
		s=0;
		for(int j=200;j;--j){
			f[k^1][j][2]=(a[i]==-1||a[i]==j)?s:0;
			(s+=f[k][j][1]+f[k][j][2])%=mo;
		}
	}
	for(int i=1;i<=200;++i) (ans+=f[k][i][1]+f[k][i][2])%=mo;
	return !printf("%lld",ans);
}
```

---

## 作者：K8He (赞：13)

大佬们的题解都~~太深奥了，~~直接把转移方程放出来让其他大佬们感性理解，蒟蒻们很难理解，所以我就写了一篇让像我一样的蒟蒻能看懂的题解

------------
[更好的阅读体验](https://www.cnblogs.com/Keven-He/p/TJ-CF1067A.html)

[原题传送门](https://www.luogu.com.cn/problem/CF1067A)

> 动态规划三部曲：确定状态，转移方程，初始状态和答案。
> 
> ——神仙 @[akicc](https://www.luogu.com.cn/user/333773)

# 第一步 确定状态
$f_{i,j,k}(k\in\{0,1,2\})$表示第 $i$ 个数选为 $j$ 且和前一个数是小于/等于/大于（$k=0$ 是大于，$k=1$ 是等于，$k=2$ 是小于）的关系时的方案数。
# 第二步 转移方程
把三种关系分开讨论：
- $k=0$，比上一个大，它的方案数就是上一个数选的比它小的数的方案数和；
- $k=1$，由于和上一个数相同，它的方案数就是上一个数的方案数和；
- $k=2$，比上一个小，它的方案数就是上一个数选的比它大的数的方案数和，但是为了防止上一个数比相邻的数都大，我们要去掉上一个数比上上个数大的方案数。

那么我们的转移方程就是：

$f_{i,j,0}=\sum^{j-1}_{l=1}f_{i-1,l,0}+f_{i-1,l,1}+f_{i-1,l,2}$

$f_{i,j,1}=f_{i-1,j,0}+f_{i-1,j,1}+f_{i-1,j,2}$

$f_{i,j,2}=\sum^{200}_{l=j+1}f_{i-1,l,1}+f_{i-1,l,2}$

如果 $a_i=-1$ 则 $1\le j\le 200$，否则 $j=a_i$	。

直接求和会超时，我们可以使用前缀和优化。
# 第三步 初始状态和答案
如果第二个数取得比第一个数小就不符合题目要求了，而第一个数只有一种取法，所以我们让 $f_{1,j,0}=1$，就可以让 $f_{2,j,2}$ 取不到方案数了！

如果最后一个数比倒数第二个数大，也不符合题意，所以我们在取答案的时候不能取 $f_{n-1,j,0}$ 。

[可以不用滚动数组，但是空间不要开太大](https://www.luogu.com.cn/record/57151523)
# 代码
```cpp
#include <bits/stdc++.h>
#define _for(i,a,b) for(int i=a;i<=b;++i)
#define for_(i,a,b) for(int i=a;i>=b;--i)
#define ll long long
using namespace std;
const int N=1e5+10,M=998244353;
ll n,a[N],f[N][205][3],ans;
void pre(){
	if(a[1]==-1)_for(i,1,200)f[1][i][0]=1;
	else f[1][a[1]][0]=1;
}void dp(){
	_for(i,2,n){
		int s=0;
		_for(j,1,200){
			if(a[i]==-1||a[i]==j)f[i][j][0]=s%M,f[i][j][1]=(f[i-1][j][0]+f[i-1][j][1]+f[i-1][j][2])%M;
			s=(s+f[i-1][j][0]+f[i-1][j][1]+f[i-1][j][2])%M;
		}s=0;
		for_(j,200,1){
			if(a[i]==-1||a[i]==j)f[i][j][2]=s%M;
			s=(s+f[i-1][j][1]+f[i-1][j][2])%M;
		}
	}
}int main(){
	scanf("%lld",&n);
	_for(i,1,n)scanf("%lld",&a[i]);
	pre(),dp();
	_for(i,1,200)ans=(ans+f[n][i][1]+f[n][i][2])%M;
	printf("%lld",ans);
	//system("pause");
	return 0;
}
```

---

## 作者：Fido_Puppy (赞：5)

$$\texttt{Description}$$

[CF1067A Array Without Local Maximums](https://www.luogu.com.cn/problem/CF1067A)

$$\texttt{Solution}$$

明显是计数类 $\text{DP}$。

观察到 $1 \leq a_i \leq 200$，所以我们可以把 $a_i$ 加入到状态中。

设 $f_{i, j}$ 表示前 $i$ 个数，第 $i$ 个位置填 $j$ 的方案数，满足 $a_i > a_{i - 1}$ 的方案数。

设 $g_{i, j}$ 表示前 $i$ 个数，第 $i$ 个位置填 $j$ 的方案数，满足 $a_i < a_{i - 1}$ 的方案数。

设 $h_{i, j}$ 表示前 $i$ 个数，第 $i$ 个位置填 $j$ 的方案数，满足 $a_i = a_{i - 1}$ 的方案数。

转移方程也很好推：

当满足 $a_i > a_{i - 1}$ 时，由于 $a_{i - 1} < a_i$，所以 $i - 1$ 号位置上已经满足条件，三种情况都可以。

$$f_{i, j} = \sum_{k = 1}^{k < j} f_{i - 1, k} + g_{i - 1, k} + h_{i - 1, k}$$

当 $a_i < a_{i - 1}$ 时，由于 $a_{i - 1} > a_i$，所以 $i - 1$ 号位置为了满足条件，必须满足 $a_{i - 1} \leq a_{i - 2}$。

$$g_{i, j} = \sum_{k = j + 1}^{200} g_{i - 1, k} + h_{i - 1, k}$$

当 $a_i = a_{i - 1}$ 时与 $a_i > a_{i - 1}$ 的情况类似。

$$h_{i, j} = f_{i - 1, j} + g_{i - 1, j} + h_{i - 1, j}$$

当 $a_i \neq -1$ 时，只需转移 $j = a_i$ 的情况即可。

这个就可以用前缀和优化转移。

$\text{DP}$ 的边界条件我们可以假设无论如何 $a_1 > a_0$，也就是 $1$ 号位置想要满足条件，必须满足 $a_1 \leq a_2$。

所以可得：

若 $a_1 = -1$

$$\forall 1 \leq i \leq 200, f_{1, i} = 1$$

若 $a_1 \neq -1$

$$f_{1, a_1} = 1$$

最终结果就是

$$\sum_{i = 1}^{200} h_{n, i} + g_{n, i}$$

$$\texttt{Code}$$

[代码链接](https://www.luogu.com.cn/paste/gcwgaroc)

$$\texttt{Thanks for watching!}$$

---

## 作者：ycyaw (赞：4)

记$f[i][j][0/1]$表示前$i$个数，第$i$个数取$j$，左边一个数是否大于等于这个数（满足条件为$1$，否则为$0$）的方案数。

转移时，如果这一位为$-1$，枚举这一位的数字$1\sim200$，枚举上一位的数字$1\sim 200$转移。

代码如下：
```cpp
for(int j=1;j<=200;j++){//当前位
    for(int k=1;k<=200;k++){//上一位 
        if(k==j) f[i][j][1]=(f[i][j][1]+f[i-1][k][0]+f[i-1][k][1])%mo;
        if(k>j) f[i][j][1]=(f[i][j][1]+f[i-1][k][1])%mo;
        if(k<j) f[i][j][0]=(f[i][j][0]+f[i-1][k][0]+f[i-1][k][1])%mo;
    } 
}
```
如果这一位不为$-1$，省去当前位的枚举。

可以发现这样转移是$O(40000\times n)$的，无法通过。

观察到从上一位转移过来的$f[i-1][k][0/1]$是连续的一段，那么前缀和优化即可。

复杂度$O(200\times n)$。

~~我为什么要写这么水的题的题解？？既然写了那就交吧。~~

$Code\ Below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define int long long
#define hh puts("")
#define pc putchar
#define mo 998244353
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
const int N=100005,M=205;
int n,a[N],f[N][M][2],ans,pre[M][2],suf[M][2];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-1;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+(ch^48);ch=getchar();}
    return ret*ff;
}
void write(int x){if(x<0){x=-x,pc('-');}if(x>9) write(x/10);pc(x%10+48);}
void writeln(int x){write(x),hh;}
void writesp(int x){write(x),pc(' ');}
signed main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    if(a[1]==-1) for(int i=1;i<=200;i++) f[1][i][0]=1;
    else f[1][a[1]][0]=1;
    for(int j=1;j<=200;j++){
        pre[j][0]=(pre[j-1][0]+f[1][j][0])%mo;
        pre[j][1]=(pre[j-1][1]+f[1][j][1])%mo;
    }
    for(int j=200;j>=1;j--){
        suf[j][0]=(suf[j+1][0]+f[1][j][0])%mo;
        suf[j][1]=(suf[j+1][1]+f[1][j][1])%mo;
    }
    for(int i=2;i<=n;i++){
        if(a[i]==-1){
            for(int j=1;j<=200;j++){
                f[i][j][1]=(f[i][j][1]+f[i-1][j][0]+f[i-1][j][1])%mo;
                f[i][j][1]=(f[i][j][1]+suf[j+1][1])%mo;
                f[i][j][0]=(f[i][j][0]+pre[j-1][0]+pre[j-1][1])%mo;
            }
        }
        else{
            f[i][a[i]][1]=(f[i][a[i]][1]+f[i-1][a[i]][0]+f[i-1][a[i]][1])%mo;
            f[i][a[i]][1]=(f[i][a[i]][1]+suf[a[i]+1][1])%mo;
            f[i][a[i]][0]=(f[i][a[i]][0]+pre[a[i]-1][0]+pre[a[i]-1][1])%mo;
        }
        for(int j=1;j<=200;j++){
            pre[j][0]=(pre[j-1][0]+f[i][j][0])%mo;
            pre[j][1]=(pre[j-1][1]+f[i][j][1])%mo;
        }
        for(int j=200;j>=1;j--){
            suf[j][0]=(suf[j+1][0]+f[i][j][0])%mo;
            suf[j][1]=(suf[j+1][1]+f[i][j][1])%mo;
        }
    }
    for(int i=1;i<=200;i++) ans=(ans+f[n][i][1])%mo;
    write(ans);
    return 0;
}
```


---

## 作者：TainityAnle (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1067A)

### 题目大意：

给你 $n$ 个数的数组 $a$，每个数在 $1$ 到 $200$ 之间，让你求有多少种满足 $a_1\le a_2,a_n\le a_{n-1}$ 且 $a_i\le \operatorname{max}(a_{i-1},a_{i+1})$ 对于任意 $i\in[2,n-1]$ 都成立。

看看这条件，这么复杂，谁看得懂啊，那就翻译一下吧。

中文 $\to$ 人话： **DP，三维的那种**，设 $dp_{i,j,st}$，$i$ 表示枚举到了第 $i$ 个，$j$ 表示第 $i$ 位选的是 $j$，而 $st$ 表示前一个数（$a_{i-1}$）与当前数（$a_i$）的关系，$st$ 有三种情况，$0$，$1$，$2$。$st=0$ 的情况，表示 $a_{i}>a_{i-1}$，$st=1$ 的情况，表示 $a_{i}=a_{i-1}$，$st=2$ 的情况，表示 $a_{i}<a_{i-1}$。

分析到此结束，可能有些乱，仔细看，其实不难，那就直接上状态转移方程吧。

---
### 状态转移

状态转移方程有 $3$ 个，需要分类讨论。

以下情况要求在满足 $a_i=-1$ 或 $a_i=j$ 情况下：

---
$a_{i}>a_{i-1}$ 的情况：

$$ f_{i,j,0}=\sum_{i = 1}^{200} sum$$

对于 $sum$，
$$ sum=\sum_{i=1}^{200} f_{i-1,j,0}+f_{i-1,j,1}+f_{i-1,j,2}$$

注意，不同的， $sum$ 要在任何时候更新，即使不满足 $a_i=-1$ 或 $a_i=j$，先更新完 $f_{i,j,0}$ 后，再更新 $sum$。

---
$a_{i}=a_{i-1}$ 的情况：

$$ sum=\sum_{i=1}^{200} f_{i-1,j,0}+f_{i-1,j,1}+f_{i-1,j,2}$$

---
$a_{i}<a_{i-1}$ 的情况：

$$f_{i,j,2}=\sum_{i = 200}^{1} sum$$

对于 $sum$，
$$ sum=\sum_{i=200}^{1} f_{i-1,j,1}+f_{i-1,j,2}$$

注意，不同的， $sum$ 要在任何时候更新，即使不满足 $a_i=-1$ 或 $a_i=j$，先更新完 $f_{i,j,2}$ 后，再更新 $sum$。

---
### 整体框架

剩下的也就剩初始化了，初始化有两种情况，如果第一个位置为 $-1$，那么这里一定有一种填法，如果不是，则把所有的 $f_{1,i,0}$ 赋值为 $1$。

**很重要的一点，空间节约着开！！！**

有的人喜欢把数组大小开到 $N+10$，$N+5$，但这道题千万不要，$f$ 数组开到 $100002\times202\times3$ 就已经很极限了，本蒟蒻喜欢开 $N+5$，所以一开始我开了 $100005\times205\times5$，然后就 MLE，0 分。

### AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,f[100002][202][3],sum,a[100005];
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	if(~a[1]) f[1][a[1]][0]=1;
	else for(int i=1; i<=200; i++) f[1][i][0]=1;
	for(int i=2; i<=n; i++) {
		sum=0;
		for(int j=1; j<=200; j++) {
			if(!~a[i]||a[i]==j) {
				f[i][j][0]=sum;
				f[i][j][1]=(f[i-1][j][0]+f[i-1][j][1]+f[i-1][j][2])%998244353;
				if(a[i]==j) break;
			}
			sum=(sum+f[i-1][j][0]+f[i-1][j][1]+f[i-1][j][2])%998244353;
		}			 f[i-1][j][0]+f[i-1][j][1]+f[i-1][j][2]
		sum=0;
		for(int j=200; j>=1; j--) {
			if(!~a[i]||a[i]==j) {
				f[i][j][2]=sum;
				if(a[i]==j) break;
			}
			sum=(sum+f[i-1][j][1]+f[i-1][j][2])%998244353;
		}
	}
	sum=0;
	for(int i=1; i<=200; i++) sum=(sum+f[n][i][1]+f[n][i][2])%998244353;
	cout<<sum%998244353;
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
~~人类智慧题~~，看到取模一眼 Dp。
# 思路
这道题的主要智慧之处就在于定义状态，我们定义 $f_{i,j,0/1/2}$ 为现在枚举到第 $i$ 位且第 $i$ 位填 $j$ 并且 $a_i$ 大于等于小于 $a_{i-1}$ 的方案数我们可以发现这样的话需要分类讨论。

- $f_{i,j,0}$ 时那么我们的 $a_{i}$ 已经大于 $a_{i-1}$ 了所以我们对于 $i-1$ 位已经满足条件了所以 $a_{i-2}$ 与 $a_{i-1}$ 之间的关系无论怎么取都没影响。
- $f_{i,j,1}$ 其实也和上面同理。
- $f_{i,j,2}$ 因为我们的 $a_{i}$ 无法对 $a_{i-1}$ 进行贡献所以贡献必须是 $a_{i-2}$ 给来了，那么就要加上 $f_{i-1,k,1}+f_{i-1,k,2}$。

但是这样我们发现时间复杂度过不去所以需要用一个前缀和优化，这里只用存最后一位为 $0$ 的和所有的加起来，然后整体时间复杂度 $O(n^2)$，稳稳通过。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n;
const int mod=998244353;
const int N=1e5+10;
int a[N];
int f[N][210][3];
int ze[210];
int sum[210];
/*
0 a[i-1]<a[i]
1 a[i-1]=a[i]
2 a[i-1]>a[i]
*/
fire main() {
//	freopen("s.out","r",stdin);
	in(n);
	rep(i,1,n) in(a[i]);
	if(a[1]!=-1) f[1][a[1]][0]=1ll;
	else rep(i,1,200) f[1][i][0]=1;
	rep(i,1,200) sum[i]=(sum[i-1]+f[1][i][1]+f[1][i][2]+f[1][i][0])%mod;
	rep(i,1,200) ze[i]=(ze[i-1]+f[1][i][0])%mod;
	rep(i,2,n) {
		if(a[i]!=-1) {
			if(a[i-1]!=-1) {
				if(a[i]>a[i-1]) f[i][a[i]][0]=(f[i][a[i]][0]+((f[i-1][a[i-1]][1]+f[i-1][a[i-1]][2])%mod+f[i-1][a[i-1]][0])%mod)%mod;
				else if(a[i]==a[i-1]) f[i][a[i]][1]=(f[i][a[i]][1]+((f[i-1][a[i-1]][1]+f[i-1][a[i-1]][2])%mod+f[i-1][a[i-1]][0])%mod)%mod;
				else f[i][a[i]][2]=(f[i][a[i]][2]+(f[i-1][a[i-1]][1]+f[i-1][a[i-1]][2])%mod)%mod;
			} else {
				f[i][a[i]][0]=(f[i][a[i]][0]+sum[a[i]-1])%mod;
				f[i][a[i]][1]=(f[i][a[i]][1]+((f[i-1][a[i]][1]+f[i-1][a[i]][0])%mod+f[i-1][a[i]][2])%mod)%mod;
				f[i][a[i]][2]=(f[i][a[i]][2]+((sum[200]-sum[a[i]])%mod+mod)%mod-((ze[200]-ze[a[i]])%mod+mod)%mod+mod)%mod;
			}
		} else {
			if(a[i-1]!=-1) {
				rep(j,1,200) {
					if(j>a[i-1]) f[i][j][0]=(f[i][j][0]+((f[i-1][a[i-1]][0]+f[i-1][a[i-1]][1])%mod+f[i-1][a[i-1]][2])%mod)%mod;
					else if(j==a[i-1]) f[i][j][1]=(f[i][j][1]+((f[i-1][a[i-1]][0]+f[i-1][a[i-1]][1])%mod+f[i-1][a[i-1]][2])%mod)%mod;
					else f[i][j][2]=(f[i][j][2]+(f[i-1][a[i-1]][1]+f[i-1][a[i-1]][2])%mod)%mod;
				}
			} else {
				rep(j,1,200) {
					f[i][j][0]=(f[i][j][0]+sum[j-1])%mod;
					f[i][j][1]=(f[i][j][1]+(f[i-1][j][1]+f[i-1][j][0])%mod+f[i-1][j][2])%mod;
					f[i][j][2]=(f[i][j][2]+(((sum[200]-sum[j])%mod+mod)%mod-((ze[200]-ze[j])%mod+mod)%mod)+mod)%mod;
				}
			}
		}
		rep(j,1,200) sum[j]=(sum[j-1]+((f[i][j][1]+f[i][j][0])%mod+f[i][j][2])%mod)%mod,ze[j]=(ze[j-1]+f[i][j][0])%mod;
	}
	int res=false;
	rep(i,1,200) res=(res+(f[n][i][1]+f[n][i][2])%mod)%mod;
	print(res);
	return false;
}

```

---

## 作者：Singularity0909 (赞：1)

蒟蒻第一次发题解，纪念第一次AC紫题 /捂脸

dp[i][j][k]表示当第i个数为j，第i-1个数与第i个数之间的大小关系为k时的方案数目

(k = 0: a[i - 1] < a[i], k = 1: a[i - 1] = a[i], k = 2: a[i - 1] > a[i])

**状态转移方程**

dp[i][j][0] = $\sum_{x=1}^{j-1}$(dp[i - 1][x][0] + dp[i - 1][x][1] + dp[i - 1][x][2])

dp[i][j][1] = dp[i - 1][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2]

dp[i][j][2] = $\sum_{x=j+1}^{200}$(dp[i - 1][x][1] + dp[i - 1][x][2])

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
const int mod = 998244353;
int n,  a[maxn];
ll sum, dp[maxn][201][3];

inline const int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + ch - '0'; ch = getchar(); }
    return x * f;
}

int main()
{
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    if (~a[1]) dp[1][a[1]][0] = 1;
    else for (int j = 1; j <= 200; j++) dp[1][j][0] = 1;
    for (int i = 2; i <= n; i++)
    {
        sum = 0;
        for (int j = 1; j <= 200; j++)
        {
            if (a[i] == -1 || a[i] == j)
            {
                dp[i][j][0] = sum;
                dp[i][j][1] = (dp[i - 1][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2]) % mod;
            }
            sum = (sum + dp[i - 1][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2]) % mod;
        }
        sum = 0;
        for (int j = 200; j >= 1; j--)
        {
            if (a[i] == -1 || a[i] == j) dp[i][j][2] = sum;
            sum = (sum + dp[i - 1][j][1] + dp[i - 1][j][2]) % mod;
        }
    }
    sum = 0;
    for (int j = 1; j <= 200; j++) sum = (sum + dp[n][j][1] + dp[n][j][2]) % mod;
    printf("%lld\n", sum);
    return 0;
}

```

---

## 作者：封禁用户 (赞：1)

$update \ 2020.1.19:$ 草草草，发现公式全炸了，到[我的博客](https://www.luogu.com.cn/blog/orz-froggod/solution-cf1067a)里看吧...


------------


这题是个dp题

本来有点做不来，和神froggy聊了一会儿天后就做得来了，在此感谢神froggy的金光加身，拯救了我那同浆糊一样的大脑

设$dp[i][j][0/1/2]$表示当i取值为j时,i大于/等于/小于左边的数的方案数


状态转移方程显然就是

$$
dp[i][j][0]=\sum_{k=1}^{j-1} (dp[i-1][k][0]+dp[i-1][k][1]+dp[i-1][k][2]) 
$$
$$
dp[i][j][1]=dp[i-1][j][0]+dp[i-1][j][1]+dp[i-1][j][2]
$$
$$
dp[i][j][2]=\sum_{k=j+1}^{200} (dp[i-1][k][1]+dp[i-1][k][2])
$$


这坨东西前缀和维护一下，我们就能用$O(n)$阿了这题（实际做的时候常数大概是400,略大）


初值问题：我们发现这个方程在赋初值的时候并不好搞...我们可以设第0个数是0，根据题意，dp[1][j][0]肯定就是1

然后就没了


------------

放代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long dp[205][3],sum[205][3];
int main(){
	int n,x,st,ed;
	scanf("%d%d",&n,&x);
	if(x==-1){
		for(int i=1;i<=200;++i)
			dp[i][0]=1;
	}
	else dp[x][0]=1;
	for(int j=1;j<=200;++j)
		sum[j][0]=sum[j-1][0]+dp[j][0],sum[j][1]=sum[j-1][1]+dp[j][1],sum[j][2]=sum[j-1][2]+dp[j][2];
	for(int i=2;i<=n;++i){
		scanf("%d",&x);
		if(x!=-1) st=ed=x;
		else st=1,ed=200;
		for(int j=1;j<st;++j) dp[j][0]=0,dp[j][1]=0,dp[j][2]=0;
		for(int j=ed+1;j<=200;++j) dp[j][0]=0,dp[j][1]=0,dp[j][2]=0;
		for(int j=st;j<=ed;++j)
		{
			dp[j][0]=(sum[j-1][0]+sum[j-1][1]+sum[j-1][2])%mod;
			dp[j][1]=((sum[j][0]-sum[j-1][0]+sum[j][1]-sum[j-1][1]+sum[j][2]-sum[j-1][2])%mod+mod)%mod;
			dp[j][2]=((sum[200][1]-sum[j][1]+sum[200][2]-sum[j][2])%mod+mod)%mod;
		}
		for(int j=1;j<=200;++j)
			sum[j][0]=(sum[j-1][0]+dp[j][0])%mod,sum[j][1]=(sum[j-1][1]+dp[j][1])%mod,sum[j][2]=(sum[j-1][2]+dp[j][2])%mod;
	}
	long long ans=0;
	for(int j=1;j<=200;++j)
		ans=(ans+dp[j][1]+dp[j][2])%mod;
	cout<<ans;
    //%%% 神froggy
}
```


---

## 作者：xuantianhao (赞：0)

## [Array Without Local Maximums](https://www.luogu.com.cn/problem/CF1067A)

很容易想到，设 $f[i][j][0/1]$ 表示：

到第 $i$ 位时，位置 $i$ 填入了 $j$，且 $j\geq$ 位置 $i-1$ 上的数的状态是 0 或 1 的种数。

但这就会有问题：大于等于反过来是小于等于，而不是小于。

因此我们还要记录一下是否相等。即设 $f[i][j][0/1/2]$ 表示：

到第 $i$ 位时，位置 $i$ 填入了 $j$，且 $j$ 相较于上一位是小于，等于，大于。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
const int lim=200;
int n,num[100100],f[2][210][3],res;
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&num[i]);
    if(num[1]==-1)for(int i=1;i<=lim;i++)f[1][i][0]=1;
    else f[1][num[1]][0]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=lim;j++)f[i&1][j][0]=f[i&1][j][1]=f[i&1][j][2]=0;
        int s;
        s=0;
        for(int j=1;j<=lim;j++){
            if(num[i]==-1||j==num[i])f[i&1][j][0]=s;
            (s+=f[!(i&1)][j][0]+f[!(i&1)][j][1]+f[!(i&1)][j][2])%=mod;
        }
        for(int j=1;j<=lim;j++)if(num[i]==-1||j==num[i])f[i&1][j][1]=(f[!(i&1)][j][0]+f[!(i&1)][j][1]+f[!(i&1)][j][2])%mod;
        s=0;
        for(int j=lim;j>=1;j--){
            if(num[i]==-1||j==num[i])f[i&1][j][2]=s;
            (s+=f[!(i&1)][j][1]+f[!(i&1)][j][2])%=mod;
        }
//      printf("%d:",i);for(int j=1;j<=lim;j++)if(f[i&1][j][0]||f[i&1][j][1])printf("(%d:%d %d)",j,f[i&1][j][0],f[i&1][j][1]);puts("");
    }
    for(int i=1;i<=lim;i++)(res+=f[n&1][i][1]+f[n&1][i][2])%=mod;
    printf("%lld\n",res);
    return 0;
}
```


---

## 作者：MoyunAllgorithm (赞：0)


给出一个包含完整思路历程的新手友好题解。

### 题意

对于数组 $a$，长度 $N$，值小于 $200$，满足

$a_1\le a_2,a_n\le a_{n-1}$ 且 $a_i\le \max \left( a_{i-1},a_{i+1} \right) $ 对于任意 $i\in \left[ 2,n-1 \right] $ 都成立。

给你一个这样的数组，但有一部分数字被去掉了。有多少种填出去掉的数字的办法？

### 分析

容易想到 dp，且可能是 $O(N \max (a_i))$ 的。

试试这个状态：$dp_i$ 表示对前 $i$ 个元素进行修复后，前 $i$ 个元素满足条件，的方案数。

那我们来转移一下：

$dp_i  = ?$

好像不可以，因为我们不知道 $a_{i-1}$ 的值和 $a_{i-2}$ 的值，我们无法判断是否满足条件。

那我们可以把状态改成：$dp_{i,j,k}$ 表示对前 $i$ 个元素进行修复后，$a_i=j,a_{i-1}=k$，前 $i$ 个元素满足条件的方案数。

这样完全可做，但我们光枚举状态就超时了。

发现我们不需要知道 $a_{i-1}$ 是什么，只需要知道 $a_{i-1}$ 和 $a_i$ 的大小关系！

$dp_{i,j,0/1/2}$ 表示对前 $i$ 个元素进行修复后，$a_i=j$，$a_{i-1}$ 和 $a_i$ 的大小关系是小于／等于／大于，前 $i$ 个元素满足条件的方案数。

那我们对于枚举的 $(i,j)$，需要保证 $a_{i-1}$ 满足条件：

- 当 $a_{i-1} < j$，则必然满足，可以从任何 $dp_{i-1,k,p}(k < j,p \in [0,2])$ 向 $dp_{i,j,0}$ 转移，累加即可。

-  当 $a_{i-1}=j$，也满足，$dp_{i-1,j,p}(p \in [0,2])$ 可以向 $dp_{i,j,1}$ 转移。

- 当 $a_{i-1}>j$，需要保证 $a_{i-2} \ge a_{i-1}$。可以从 $dp_{i-1,k,p}(k >j,p \in [1,2])$ 向 $dp_{i,j,2}$ 转移。

转移是 $O( \max(a_i))$ 的。但你使用 **前缀和** 优化，用 $sum_{j,0/1/2}$ 代表 $dp_{i,j,0/1/2}$ 在 $j$ 维的前缀和，即可 $O(1)$ 转移。

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#define LL long long
#define PLI pair<long long,int>
using namespace std;
const int MAXN=1e5+5,MOD=998244353;
int a[MAXN];
int dp[MAXN][205][3],sum[205][3];
//0:i-1<i 1:i-1==i  2:i-1>i
int N;
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++) scanf("%d",&a[i]);
    if(a[1]==-1)
    {
        for(int i=1;i<=200;i++) dp[1][i][0]=1;
    }
    else dp[1][a[1]][0]=1;
    for(int i=2;i<=N;i++)
    {
        for(int j=1;j<=200;j++) sum[j][0]=sum[j][1]=sum[j][2]=0;
        for(int j=1;j<=200;j++)
        {
            sum[j][0]=(sum[j-1][0]+dp[i-1][j][0])%MOD;
            sum[j][1]=(sum[j-1][1]+dp[i-1][j][1])%MOD;
            sum[j][2]=(sum[j-1][2]+dp[i-1][j][2])%MOD;
        }
        if(a[i]==-1)
        {
            for(int j=1;j<=200;j++)
            {
                dp[i][j][0]=(1ll*dp[i][j][0]+sum[j-1][0]+sum[j-1][1]+sum[j-1][2])%MOD;
                dp[i][j][1]=(1ll*dp[i][j][1]+dp[i-1][j][0]+dp[i-1][j][1]+dp[i-1][j][2])%MOD;
                dp[i][j][2]=((1ll*dp[i][j][2]+sum[200][1]-sum[j][1]+sum[200][2]-sum[j][2])%MOD+MOD)%MOD;
            }
        }
        else
        {
            int j=a[i];
            dp[i][j][0]=(1ll*dp[i][j][0]+sum[j-1][0]+sum[j-1][1]+sum[j-1][2])%MOD;
            dp[i][j][1]=(1ll*dp[i][j][1]+dp[i-1][j][0]+dp[i-1][j][1]+dp[i-1][j][2])%MOD;
            dp[i][j][2]=((1ll*dp[i][j][2]+sum[200][1]-sum[j][1]+sum[200][2]-sum[j][2])%MOD+MOD)%MOD;
        }
    }
    LL ans=0;
    for(int i=1;i<=200;i++) ans=(ans+dp[N][i][1]+dp[N][i][2])%MOD;
    printf("%lld\n",ans);
    return 0;
}
```


---

