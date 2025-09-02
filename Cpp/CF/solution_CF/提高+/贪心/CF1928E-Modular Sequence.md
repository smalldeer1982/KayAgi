# Modular Sequence

## 题目描述

You are given two integers $ x $ and $ y $ . A sequence $ a $ of length $ n $ is called modular if $ a_1=x $ , and for all $ 1 < i \le n $ the value of $ a_{i} $ is either $ a_{i-1} + y $ or $ a_{i-1} \bmod y $ . Here $ x \bmod y $ denotes the remainder from dividing $ x $ by $ y $ .

Determine if there exists a modular sequence of length $ n $ with the sum of its elements equal to $ S $ , and if it exists, find any such sequence.

## 说明/提示

In the first example, the sequence $ [8, 11, 2, 5, 2] $ satisfies the conditions. Thus, $ a_1 = 8 = x $ , $ a_2 = 11 = a_1 + 3 $ , $ a_3 = 2 = a_2 \bmod 3 $ , $ a_4 = 5 = a_3 + 3 $ , $ a_5 = 2 = a_4 \bmod 3 $ .

In the second example, the first element of the sequence should be equal to $ 5 $ , so the sequence $ [2, 2, 2] $ is not suitable.

## 样例 #1

### 输入

```
3
5 8 3 28
3 5 3 6
9 1 5 79```

### 输出

```
YES
8 11 2 2 5 
NO
NO```

# 题解

## 作者：Galex (赞：13)

![](https://cdn.luogu.com.cn/upload/image_hosting/w0rqjgob.png)

全球首杀，取之！

经过一些简单的转化可以变成求一个序列 $a$，满足 $a_1$ 是某个给定的值 $x$，总和也是某个给定的值 $s$，且对于每个 $i>1$，$a_i$ 要么为 $0$ 要么为 $a_{i-1}+1$。注意这里的 $x,s$ 和题面里的不一定相同。

我们先考虑 $a_1=0$ 的情况。显然 $a$ 是由若干个以 $0$ 开始，公差为 $1$ 的等差数列构成的。如果我们之考虑那些长度 $\ge 2$ 的等差数列（即不考虑只由一个 $0$ 组成的，因为可以无脑放在最后且不影响总和），则这些等差数列的长度之和需要 $\le n$。

考虑算出 $f_i$ 表示为了让总和为 $i$，需要的等差数列的长度之和的最小值。转移直接枚举最后一个等差数列的长度。显然每个等差数列的长度不超过 $O(\sqrt s)$ 级别，故递推 $f_i$ 的复杂度是 $O(s\sqrt s)$ 的。那么有解的充要条件就是 $f_s \le n$，构造解根据转移的决策点构造即可。

$a_1\ne 0$ 类似，只需枚举第一个 $0$ 的位置就和 $a_1=0$ 的情况相同了。

总复杂度 $O(s\sqrt s)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
bool Med;

LL read() {
	LL s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

const int lim = 700;

int tri(int x) {
	return x * (x + 1) / 2;
}

int f[200005];

void work() {
	int n = read(), x = read(), y = read(), s = read(), t = x % y;
	if ((LL)t * n % y != s % y || (LL)t * n > s) {
		printf("No\n");
		return ;
	}
	s = (s - t * n) / y;
	int st = (x - t) / y;
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for (int i = 1; i <= s; i++)
		for (int j = 1; tri(j) <= i; j++)
			f[i] = min(f[i], f[i - tri(j)] + j + 1);
	for (int i = 1, sum = st; i <= n && sum <= s; sum += st + i, i++) {
		if (f[s - sum] <= n - i) {
			printf("Yes\n");
			for (int j = 1; j <= i; j++)
				printf("%d ", (st + j - 1) * y + t);
			int cnt = n - i;
			s -= sum;
			while (s) {
				for (int j = 1; tri(j) <= s; j++)
					if (f[s - tri(j)] + j + 1 == f[s]) {
						cnt -= j + 1;
						for (int k = 0; k <= j; k++)
							printf("%d ", k * y + t);
						s -= tri(j);
						break;
					}
			}
			for (int j = 1; j <= cnt; j++)
				printf("%d ", t);
			putchar('\n');
			return ;
		}
	}
	printf("No\n");
}

bool Mst;
signed main() {
	int T = read();
	while (T--)
		work();
	return 0;
}
```

---

## 作者：Eraine (赞：4)

编号：CF1928E

tag：动态规划

写在前面的话：

笔者在同一个套路上栽倒的两次，前一次是某场 ARC 比赛，后一次即这题。由于考试的时候过于着急以及实力问题，导致考试实力，虽然上分，但是没理想发挥。警钟长鸣！！！

这里发现 $x$ 和 $y$ 与正解无关。只要将每一个 $a_i$ 表示成 $a_i=b_ix+y$ 的形式即可。具体地，在预处理的时候将 $s$ 减去 $n$ 个 $x\mod y$，再将 $s$ 除以 $y$ 即可。问题即变为构造一个长度为 $n$ 的序列使得 $a_1=\lfloor\frac{x}{y}\rfloor$，$i\in(1,n],a_i=0\ \text{or}\ a_i=a_{i-1}+1$ 且 $\sum a_i=s$。注意在将 $s$ 除以 $y$ 之前，若 $s$ 不能整除 $y$ 或 $s\lt 0$ 则为无解，直接退出。

以下默认 $n,s$ 同阶。

构造出来的 $a$ 序列一定为 $\lfloor\frac{x}{y}\rfloor,\lfloor\frac{x}{y}\rfloor+1,\lfloor\frac{x}{y}\rfloor+2,\dots,\lfloor\frac{x}{y}\rfloor+k_0,0,1,2,\dots,k_1,0,1,2,\dots,k_2,\dots,k_m$。即划分为若干段，除了第一段以 $\lfloor\frac{x}{y}\rfloor$ 开头，其余都以 $0$ 开头的长度总和为 $n$ 的公差为 $1$ 的等差数列。

然后是 DP。首先一个很显然的性质，即每段长度是 $\Theta(\sqrt n)$ 级别的，由于等差数列和是 $\Theta(n^2)$ 级别的。否则该段等差数列和就超过 $n$ 了。

DP 的约束条件有两个。数列和必须为 $s$，数列长度必须为 $n$，这样就发现这个 DP 方程状态数就已经是 $\Theta(n^2)$ 的，不可行。观察这两个约束条件，前者不太好变动，发现后者可以转换为在前者条件下求出最小长度。只要判断最小长度 $f_i$ 与 $n$ 的大小关系即可。所以动态规划转移就推出来了。设 $f_i$ 为数列和为 $i$ 数列的最小长度，方程转移如下：

$$f_i=f_{i-\sum_{k=0}^{j}k}+j+1$$

$j$ 是 $\Theta(\sqrt n)$ 级别的，内层关于 $k$ 的和式可以 $\Theta(1)$ 求得。至于要列出方案，迭代求解即可。对第一段的处理，只需枚举长度然后可以 $\Theta(1)$ 类似转移。

$\Theta(n\sqrt n)$。

赛后代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
const int inf=1e9;
int f[N];
void solve(){
	int n,x,y,s;
	scanf("%d%d%d%d",&n,&x,&y,&s);
	if((ll)(x%y)*n>(ll)(s)){
		printf("NO\n");
		return;
	}
	s=s-n*(x%y);
	if(s%y){
		printf("NO\n");
		return;
	}
	s/=y;
	if(x/y>s){
		printf("NO\n");
		return;
	}
	for(int i=1;i<=s;i++){
		f[i]=inf;
	}
	for(int i=1;i<=s;i++){
		int sum=0;
		for(int j=0;j<=s;j++){
			sum=sum+j;
			if(sum>i){
				break;
			}
			f[i]=min(f[i],f[i-sum]+j+1);
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		sum=sum+x/y+i-1;
		if(sum>s){
			break;
		}
		if(f[s-sum]<=n-i){
			printf("YES\n");
			for(int j=1;j<=i;j++){
				printf("%d ",(x/y+j-1)*y+x%y);
			}
			for(int p=s-sum;p;){
				int val=0;
				for(int j=0;j<=p;j++){
					val=val+j;
					if(val>p){
						break;
					}
					if(f[p]==f[p-val]+j+1){
						for(int k=0;k<=j;k++){
							printf("%d ",k*y+x%y);
						}
						p=p-val;
						break;
					}
				}
			}
			for(int j=1;j<=n-i-f[s-sum];j++){
				printf("%d ",x%y);
			}
			printf("\n");
			return;
		}
	}
	printf("NO\n");
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}
```
警钟长鸣！

---

## 作者：operator_ (赞：3)

# Modular Sequence

[题目传送门](https://www.luogu.com.cn/problem/CF1928E)

## 题解

发现 $a_i+y$ 与 $a_i\bmod y$ 均不改变 $a_i$ 模 $y$ 的余数，所以答案序列的每个元素均可表示为 $x\bmod y+ky$ 的形式，先让 $s$ 减去 $n\times (x\bmod y)$，再除以 $y$，这样原序列可以被划分为一个从 $\lfloor\dfrac{x}{y}
\rfloor$ 开始的等差数列和若干个从 $0$ 开始的等差数列。

第一个等差数列可以直接枚举项数，后面的考虑预处理 dp，设 $f_i$ 表示和为 $i$ 的合法数列至少需要几项，转移枚举最后一个等差数列的项数，容易发现复杂度是 $O(\sqrt n)$ 级别的。

最后还要输出方案，记录一下转移时最后一项的项数即可，是容易的。

代码：

```cpp
/*
 * @Author: operator_ 
 * @Date: 2024-02-15 11:02:31 
 * @Last Modified by: operator_
 * @Last Modified time: 2024-02-15 12:36:34
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
int t,n,x,y,s,f[200005],g[200005];
signed main(){
    cin>>t;
    memset(f,0x3f,sizeof(f));f[0]=0;
    for(int i=1;i<=200000;i++)
        for(int j=1;(j-1)*j/2<=i;j++)
            if(f[i-(j-1)*j/2]+j<f[i]) 
                g[i]=j,f[i]=f[i-(j-1)*j/2]+j;
    while(t--) {
        n=rd(),x=rd(),y=rd(),s=rd();
        s-=n*(x%y);int xx=x/y,fl=0;
        if(s<0||s%y!=0) {puts("NO");continue;}
        s/=y;
        for(int i=1;i<=n&&(2*xx+i-1)*i/2<=s;i++) {
            int now=s-(2*xx+i-1)*i/2;
            if(f[now]+i<=n) {
                puts("YES");
                for(int j=1;j<=i;j++) printf("%lld ",x+j*y-y);
                for(int j=1;j<=n-f[now]-i;j++) printf("%lld ",x%y);
                while(now!=0) {
                    for(int j=1;j<=g[now];j++) printf("%lld ",x%y+j*y-y);
                    now-=(g[now]-1)*g[now]/2;
                }
                puts("");fl=1;break;
            }
        }
        if(!fl) puts("NO");
    }
    return 0;
}
```

---

## 作者：honglan0301 (赞：3)

## 题意

给出 $n,x,y,s$，需要构造长为 $n$ 的序列 $a$，满足 $a_1=x$，$\sum a_i=s$，且对于 $\forall i>1$ 均有 $[a_i=a_{i-1}+y]\bigvee[a_i=a_{i-1}\bmod y]$。

## 分析

首先 $a_i\bmod y$ 全部相同，因此判掉 $s\bmod y\neq (n\times x)\bmod y$ 的情况。不妨设 $a_i=k_i{y}+(x\bmod y)$，于是我们只需要构造序列 $k_i$，即转化为了 $n'=n,x'=\lfloor \frac{x}{y}\rfloor,y'=1,s'=s-n\times(x\bmod y)$ 的问题。

此时注意到可以对 $n$ 根分：

- 当 $n>O(\sqrt s)$ 时，从前往后贪心地让每个 $k_i$ 尽量大就能保证有解，因为满足 $\sum\limits_{i=1}^p \leq s-x< \sum\limits_{i=1}^{p+1}$ 的 $p$ 是 $O(\sqrt s)$ 级别的，我们可以用一段 $1,2,\dots,p$ 和 $O(\sqrt s)$ 个 $1$ 拼出 $s$。

- 否则考虑 dp，枚举序列中第一个 $0$ 的位置 $i$，之后只需要知道能否用总长为 $n-i+1$ 的 $0,0\ 1,0\ 1\ 2,\dots$ 等连续段拼起来，使得总和为 $s-\frac{(2x+i-2)\times (i-1)}{2}$。而这可以提前预处理，令 $f_{i,j}$ 表示能否用长为 $i$ 的段拼出 $j$，转移需要枚举下一段的长度，那么 $\text{bitset}$ 优化即可做到 $O(\frac{s\times \sqrt s^2}{w})=O(\frac{s^2}{w})$。

## 代码

有趣的事情。赛时代码通过了 main tests 全部数据，但是多测不清空被 @6f21 叉了。

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <bitset>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long

int T,n,x,y,s,a[200005];
int b[200005];
bitset <200005> dp[1005];

void solve1()
{
	for(int i=2;i<=n;i++)
	{
		if(b[i-1]+1<=s)
		{
			b[i]=b[i-1]+1; s-=b[i];
		}
		else b[i]=0;
	}
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++) cout<<b[i]*y+x%y<<" "; cout<<endl;
}
int calc(int l,int r)
{
	return (l+r)*(r-l+1)/2;
}
void init()
{
	dp[0][0]=1;
	for(int i=1;i<=500;i++)
	{
		for(int j=1;j<=i;j++)
		{
			dp[i]|=(dp[i-j]<<calc(1,j-1));
		}
	}
}
void solve(int bh,int nx,int ns)
{
	if(!nx) return;
	for(int i=1;i<=nx;i++)
	{
		if(dp[nx-i][ns-calc(1,i-1)])
		{
			b[bh+1]=0;
			for(int j=bh+2;j<=bh+i;j++) b[j]=j-(bh+1);
			solve(bh+i,nx-i,ns-calc(1,i-1)); return;
		}
	}
}
void solve2()
{
	for(int i=1;i<=n;i++)
	{
		if(calc(b[1],b[1]+i-1)-b[1]>s) break;
		if(dp[n-i][s-(calc(b[1],b[1]+i-1)-b[1])])
		{
			cout<<"YES"<<endl;
			for(int j=2;j<=i;j++) b[j]=b[j-1]+1;
			solve(i,n-i,s-(calc(b[1],b[1]+i-1)-b[1]));
			for(int i=1;i<=n;i++) cout<<b[i]*y+x%y<<" "; cout<<endl;
			return;
		} 
	}
	cout<<"NO"<<endl;
}

signed main()
{
	init();
	cin>>T;
	while(T--)
	{
		cin>>n>>x>>y>>s;
		a[1]=x;
		if(s<x+(n-1)*(x%y)) {cout<<"NO"<<endl; continue;}
		s-=x+(n-1)*(x%y);
		if(s%y!=0) {cout<<"NO"<<endl; continue;}
		s/=y;
		b[1]=x/y;
		//cout<<s<<" "<<b[1]<<" "<<n<<endl;
		if(n>=1000) solve1(); else solve2();
	}
}
```


---

## 作者：LCat90 (赞：2)

【化繁为简】

先观察序列可能的形式，不好统计。于是全部减去**公共部分** $x\bmod y$。然后发现还可以除以 $y$。后面变成：$\lfloor\frac{x}{y}\rfloor$ 为首项的一段公差为 $1$ 的等差数列，还有一堆首项为 $0$ 的。

前面比较特殊，直接枚举；后面就是凑 $sum$ 的预处理问题。

【可行性问题】

于是 dp 的转移就可以通过枚举最后一项个数来（定义 $dp_{i,j}$ 表示能否用 $n$ 个位置构造使得和为 $j$），但是这样的话还是 $O(n^2)$。

又是 dp 的一个转化：发现假设 $n$ 个可行，那我们可以在最后**填一堆的** $0$，使得 $\forall m>n$ 都合法。所以 dp 状态变成：$dp_i$ 表示和为 $i$ 的**最小**的长度，简单贪心一下后发现转移是 $O(s\sqrt s)$ 的。 

最后构造的时候注意还原，自认为清晰的代码：

```cpp
#include <bits/stdc++.h>
#define pii pair <int, int> 
#define int long long
using namespace std;
const int N = 2e5 + 5, inf = 0x3f3f3f3f3f3f3f3f; int read();
int n, x, y, s, dp[N], rec[N];
void dfs(int xx) {
	if(!xx) return ;
	int yy = rec[xx]; 
	for(int i = 0;i <= yy; ++i) printf("%lld ", x % y + i * y);
	dfs(xx - yy * (yy + 1) / 2);
}
void solve() {
	cin >> n >> x >> y >> s;
	s = s - n * (x % y);
	if(s < 0 or s % y) return puts("NO"), void(); 
	s /= y; // 化成一般式
	for(int i = 1;i <= n; ++i) { // 项数，公差 = 1 
		int End = x / y + i - 1, sum = (x / y + End) * i / 2;
		if(sum > s) break ;
		int S = s - sum;
		if(dp[S] <= n - i) { 
			puts("YES"); // 可以，那么构造方案开始！ 
			for(int j = 1;j <= i; ++j) printf("%lld ", x + (j - 1) * y); // 后续：dfs 
			dfs(S); 
			int num = n - i - dp[S]; for(int j = 1;j <= num; ++j) printf("%lld ", x % y); // 用 0 来凑！ 
			return puts(""), void();
		}
	}  puts("NO");
}
void init() {
	memset(dp, 0x3f, sizeof dp); dp[0] = 0;
	for(int i = 1;i <= 200000; ++i) {// 和为 i
		for(int j = 1;j <= 700; ++j) { // 项数 = j + 1，首 = 0，末 = j 
			int x = j * (j + 1) / 2; if(x > i) break ;
			if(dp[i - x] != inf and dp[i - x] + j + 1 < dp[i]) dp[i] = dp[i - x] + j + 1, rec[i] = j; // 状态 i 是选择了序列 j 转移而来 
		} 
	}
}
signed main() {
	int T; cin >> T; init();
	while(T--) solve();
	return 0;
}

int read() {
	char c; int sum = 0; while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') sum = (sum << 3) + (sum << 1) + (c ^ 48), c = getchar();
	return sum;	
}
```

---

## 作者：xieziheng (赞：2)

很好玩的题。

然额我没开 long long WA 了，赛后加了两个 1ll* 就过了！！！

一个显然的事实是数列中所有数模 $y$ 值相同。所以记 $w=x \bmod y$，可以先将所有数减掉 $w$ 再除以 $y$，特判掉一些情况后，可以转化成这个问题：

称数列中形如 $a,a+1,\cdots,a+t$ 称为一个连续段，则转化后的数列形如以 $\frac {x-w} y$ 为开头的连续段和一些以 $0$ 为开头的连续段。所以只需要构造这样的数列 $a$，使得 $\sum_{i=1}^{n} a_i=\frac {s-n \times w} {v}$，就行。

注意到我们可以随意添加 $0$，且把开头连续段去掉后所有连续段都以 $0$ 为开头。然后我赛时就想到了一个抽象的做法，就是预处理 $f_s$ 表示若干以 $0$ 为开头的连续段使得其和为 $s$ 所花的最短长度，然后再记录一下转移方案，预处理复杂度是 $\mathcal{O}(s \sqrt s)$ 的。然后直接枚举开头的连续段长度，如果方案合法就做完了，否则显然一定不合法。

细节挺多。

赛时死因在于，第 $32$ 行 $n \times w$ 爆 int 了。

```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
typedef long long ll;
il int read(){
	int x=0,c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return x;
}
const int N=2e5+5,inf=1e9;
int T,n,u,v,w,s,sum,a[N],f[N],pre[N],ck;
il void init(){
	int x,y,z;for(int i=1;i<N;++i) f[i]=inf;
	f[0]=0;
	for(int i=1;i<=800;++i){
		x=i*(i+1)/2;
		for(int j=x;j<N;++j)
			if(f[j]>f[j-x]+i+1) f[j]=f[j-x]+i+1,pre[j]=i;
	}
}
ll x;int y,z;
int main(){
	scanf("%d",&T);init();
	while(T--){
		scanf("%d%d%d%d",&n,&u,&v,&s);w=u%v;
		if(!s){
			if(!u){puts("YES");for(int i=1;i<=n;++i) printf("0 ");puts("");}
			else puts("NO");
			continue;
		}
		if(s<1ll*n*w || (s-1ll*n*w)%v!=0) {puts("NO");continue;}
		a[1]=(u-w)/v,sum=(s-n*w)/v;
		if(sum<a[1] || sum*2ll>1ll*(2ll*a[1]+n-1ll)*n){puts("NO");continue;}
		ck=0;
		if(a[1]){
			for(int i=1;i<=n;++i){
				x=((2ll*a[1]+i-1ll)*i)/2ll;if(x>sum) break;
				if(f[sum-x]<=n-i){
					ck=1;
					for(int j=2;j<=i;++j) a[j]=a[j-1]+1;
					y=int(sum-x),z=i+1;
					while(y){
						for(int j=z;j<=z+pre[y];++j) a[j]=j-z;
						z+=pre[y]+1,y-=(pre[y]*(pre[y]+1))/2;
					}
					for(int j=z;j<=n;++j) a[j]=0;
					break;
				}
			}
		}
		else{
			if(f[sum]<=n){
				ck=1,y=sum,z=1;
				while(y){
					for(int j=z;j<=z+pre[y];++j) a[j]=j-z;
					z+=pre[y]+1,y-=(pre[y]*(pre[y]+1))/2;
				}
				for(int j=z;j<=n;++j) a[j]=0;
			}
		}
		if(!ck) puts("NO");
		else{
			puts("YES");x=0;
			for(int i=1;i<=n;++i) printf("%d ",w+a[i]*v),x+=a[i];puts("");
		}
	}
	return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：2)

说实话，这场 E 真比 D 简单吧！

* observation1：序列所有数 $\bmod\ y$ 相同，记为 $r$；

* observation2：将序列的每个数写作 $p_iy+r$ 的形式，原要求等价于 $\displaystyle\left(\sum_{i=1}^np_i\right)y+nr=S$；

* observation3：$p_i=p_{i-1}+1$ 或 $p_i=0$。

问题转化成给定 $n,S',p_1$（其中 $S'$ 是所有 $p$ 的和），求是否存在满足上述条件的数列 $p$。

再转化一下，把所有取 $p_i=p_{i-1}+1$ 的部分封装成一段，那么我们有 $O(\sqrt V)$ 种本质不同的段，我们发现这是个背包！

但这个背包是做不了的！它的 $n,V$ 都是 $2\times 10^5$ 级别，空间也炸，`bitset` 都救不了！

这个时候稍微转化一下思路，我们发现如果某个序列能拼出总和 $S$，可以在后面加任意多个 $0$。于是转化成求解拼出总和 $S$ 的最短长度 $dis$，又因为 $dis$ 的转移方向有单调性，$O(V\sqrt V)$ 扫一遍即可。

最后枚举 $p_1$ 所在段的长度直接构造即可。

复杂度 $O(V\sqrt V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005

int n,x,y,S,pre[MAXN],dis[MAXN],p[MAXN];

inline int jS( int x ){ return x * ( x - 1 ) / 2; }

inline void solve(){
	scanf("%lld%lld%lld%lld",&n,&x,&y,&S);
	int r = x % y,R = S - n * r; if( R % y || R < 0 ){ puts("NO"); return; } R /= y;
	vector<int> V( n + 1 ); bool flag = 0;
	for( int prelen = 1 ; prelen <= n ; prelen ++ ){
		int rem = R - ( jS( x / y + prelen ) - ( x / y > 0 ? jS( x / y ) : 0 ) );
		if( rem < 0 ) continue;
		if( dis[rem] <= n - prelen ){
			flag = 1;
			vector<int> Lens; int now = rem;
			while( now ) Lens.emplace_back( pre[now] ),now -= p[pre[now]];
			int len = 0;
			for( int i = 1 ; i <= prelen ; i ++ ) V[++len] = x / y + i - 1;
			for( int ele : Lens ) for( int j = 0 ; j < ele ; j ++ ) V[++len] = j;
			while( len < n ) V[++len] = 0;
			break;
		}
	}
	if( !flag ){ puts("NO"); return; }
	puts("YES");
	for( int i = 1 ; i <= n ; i ++ ) printf("%lld ",V[i] * y + r); puts("");
}

signed main(){
	for( int i = 1 ; i <= MAXN - 5 ; i ++ ) p[i] = i * ( i - 1 ) / 2;
	for( int i = 1 ; i <= MAXN - 5 ; i ++ ) dis[i] = 1e9;
	dis[0] = 0;
	for( int i = 0 ; i <= MAXN - 5 ; i ++ )
		for( int j = 2 ; i + p[j] <= MAXN - 5 ; j ++ )
			if( dis[i] + j < dis[i + p[j]] ) dis[i + p[j]] = dis[i] + j,pre[i + p[j]] = j;
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：2)

[更好的阅读体验](https://www.cnblogs.com/sunkuangzheng/p/18013450)

2300？1300！

## $\textbf{Problem Statement}$

给定 $n,x,y,s$，构造长度为 $n$ 的序列 $a$，满足：

- $a_1 = x$。

- $\forall i \in [2,n],a_i = a_{i-1} + y$ 或者 $a_i = a_{i-1} \bmod y$。

- $\sum \limits_{i=1}^n a_i = s$。

给出构造或报告无解。$\sum n,\sum s \le 2 \cdot 10^5$。

## $\textbf{Hints}$

### $\textbf{Hint 1}$

令 $p = s - n \cdot (x \bmod y)$，如果 $p \bmod y \ne 0$，这个问题可能有解吗？

### $\textbf{Hint 2}$

令 $s = \dfrac{p}{y}$，问题等价于构造序列 $a$，使得 $a_1 = x$，$\forall i \in [2,n],a_i = a_{i-1}+1$ 或 $a_i = 0$，且 $\sum \limits_{i=1}^n a_i = s$。

### $\textbf{Hint 3}$

解决 $x < y$ 的情况。$x \ge y$ 的情况可以简单转化。

### $\textbf{Hint 4}$

当 $x < y$ 时，鉴于你可以填 $0$，你只需要关心拼出一个整数 $q$ 最小需要几个数字。

#### $\textbf{Hint 5}$

可以用 DP 解决。

## $\textbf{Solution}$

先阅读完所有提示。

我们来解决 $x < y$ 的情况，此时我们关心拼出整数 $q$ 最少需要几个数字。考虑图论建模，对于数字 $i$，向 $x = i+\sum\limits_{j=1}^k j$ 连边权为 $k+1$ 的边，表示从 $i$ 到 $x$ 需要 $k+1$ 个新的数字，容易发现边数为 $\mathcal O(n \sqrt n)$ 级别。跑一边 dij 即可得到拼出每个整数的最少代价，复杂度 $\mathcal O(n \sqrt n \log n)$。

你发现这个图是个 DAG，边即为 dp 的转移方程，那么直接 dp 就好，复杂度 $\mathcal O(n\sqrt n )$。

然后我们就 $\mathcal O(1)$ 解决了 $x < y$ 的情况，对于 $x \ge y$ 的情况，我们只需要枚举第一部分填几个数字，然后就转化成了 $x < y$ 的情况。

构造答案只需要记录 dp 方案，这也是容易完成的。回答每组询问的时间复杂度是 $\mathcal O(n)$，可以通过。

[赛时代码](https://codeforces.com/contest/1928/submission/245823419)。因为脑抽了所以写了 dij。





---

## 作者：解方橙 (赞：1)

## 简要题意
给出四个数 $n,a_1,y,S$，构造一个长度为 $n$ 的序列 $a$ 使得 $\forall 1\leq i\leq n, a_i=a_{i-1}+y$ 或 $a_{i-1}\operatorname{mod} y$，或报告无解。

## 题目解法

提供一个不用根号分治的做法。暴力大法好。

首先对题目进行转化。注意到可以执行的两个操作都不会改变 $a_i\operatorname{mod}y$ 的值，不妨记 $m=a_1\operatorname{mod} y$，那么每个 $a_i$ 都会对总和产生 $m$ 的贡献。因此，不妨将 $S$ 减去 $n\times m$，$a_i$ 都减去 $m$。

每个 $a_i$ 在减去 $m$ 之后就变成了 $y$ 的倍数，因此不妨将 $a_i$ 都除以 $y$，$S$ 也除以 $y$。

于是：问题变成了以下的简化版本：

- 有三个数 $n,a_1,S$，构造一个长度为 $n$ 的序列 $a$ 使得 $\forall 1\leq i\leq n,a_i=a_{i-1}+1$ 或 $0$。

看着舒服多了。

可以发现，最后的 $a$ 序列一定是这样的：
- 开始有一段递增的序列，然后之后是一堆 $0,1,2,\dots$。

举个例子，$3,4,0,1,2,3,0,1,2,\dots$。

我们的任务也就是构造一个这样的序列使得：
- 长度 $=n$；
- 和为 $S$。

此时可能会想到贪心，即能增就一直增，不行了就开始下一段 $0,1,2,\dots$。

但这是错的，反例：$n=6,a_1=4,S=14$，按照贪心是造不出来的，但正确答案为 $4,0,1,2,3,4$。

于是我们考虑和 DP 有关的东西。

由于 $a$ 序列是由一段 $a_1$ 开始的递增序列和若干段 $0$ 开始的递增序列拼接而成的，我们分开处理。

注意到一个事情：和不超过 $S$ 的一段递增序列的长度是 $\mathcal{O}(\sqrt{S})$ 级别的。这很好理解：比如说 $0,1,2,3,\dots$，那在 $\sqrt{S}$ 个数后和就变成了 $\sqrt{S}\times (\sqrt{S}-1)/2$，这就达到 $S$ 的数量级了。

于是我们可以暴力枚举 $a_1$ 开始的那一段的长度，对于剩下的部分，进行 DP。

记 $f_i$ 表示从 $0$ 开始，和为 $i$ 的序列最小长度。我们可以枚举最后一段选了多少个数进行暴力转移。

即如果我们最后一段选了 $j$ 个数，则 $f_i\gets \min(f_i,f_{i-j(j-1)/2}+j)$。

暴力转移的复杂度也是 $\mathcal{O}(\sqrt{L})$ 的（其中 $L$ 指题目中的 $2e5$），原理同上。

注意到 $f$ 的转移与 $n,a_1,S$ 都无关，于是可以放到开头预处理，这部分复杂度 $\mathcal{O}(L\sqrt{L})$。

题目要求我们输出答案，那再开一个数组 $g_i$ 记录转移即可。

回到主程序，枚举开头一段的复杂度为 $\mathcal{O}(\sqrt{S})$，找到答案后输出时，由于至多转移 $n$ 次，于是这部分复杂度为 $\mathcal{O}(n)$。

于是这道题就做完了。 [submission](https://codeforces.com/contest/1928/submission/246063614)

后记：这是我打的最好的一场 CF 了，但是是 VP …… /fn

---

## 作者：int_R (赞：1)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18014004/CF1928E)

[原题链接](https://www.luogu.com.cn/problem/CF1928E)

设 $p=x\bmod y$。思考发现本质是 $x,x+y,x+2y,\cdots,x+k_1y,p,p+y,p+2y,\cdots,p+k_2y,p,p+y,p+2y,\cdots,p+k_3y\cdots$，即每次二操作会使 $y$ 的系数变为 $0$。

枚举第 $i$ 次操作是第一次二操作，记 $s_1=s-(i\times x+y\times\dfrac{i(i-1)}{2}+(n-i)\times p)$，也就是第一次二操作后通过若干个 $y$ 凑出来的数，当 $s1<0$ 或者 $y\nmid s1$ 时不合法。

那么我们现在要使系数和为 $\dfrac{s1}{y}$ 且操作次数不大于 $n-i$ 次，所以可以用一个背包来找出凑出系数 $j$ 的最小操作数。连续的 $1$ 次二操作和 $i-1$ 次一操作可以获得 $\dfrac{i*(i-1)}{2}$ 的贡献，可知有用的 $i$ 是根号级别的，直接背包，然后记录一下 DP 路径，最后就可以输出方案了。注意如果最少操作数小于 $n-i$，那么要多进行几次二操作来补满。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int MAXN=2e5+10,INF=1e9+7;
int T,n,x,y,s,f[MAXN],d[MAXN];
inline bool B(int k,int s)
{
    if(s<0||s%y) return false;
    if(f[s/y]>k) return false;
    s/=y;cout<<"Yes\n";
    for(int i=1;i<=n-k;++i) cout<<x+(i-1)*y<<' ';
    for(int i=1;i<=k-f[s];++i) cout<<x%y<<' ';
    while(s)
    {
        for(int i=1;i<=d[s];++i)
            cout<<x%y+(i-1)*y<<' ';
        s-=d[s]*(d[s]-1)/2;
    }
    cout<<'\n';return true;
}
inline void work()
{
    cin>>n>>x>>y>>s;bool flag=false;
    for(int i=1;i<=n;++i)
        if(B(n-i,s-(x*i+i*(i-1)/2*y+(n-i)*(x%y))))
            {flag=true;break;}
    if(!flag) cout<<"No\n";return ;
}
signed main()
{
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    for(int i=1;i<=200000;++i) f[i]=INF;
    for(int i=1;;++i)
    {
        int cur=i*(i-1)/2;if(cur>200000) break;
        for(int j=cur;j<=200000;++j)
        {
            if(f[j-cur]+i<f[j])
                f[j]=f[j-cur]+i,d[j]=i;
        }
    }
    cin>>T;while(T--) work();
    return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[CF1928E](https://www.luogu.com.cn/problem/CF1928E)

### 思路

令 $r=x \bmod y$。每个 $a_i$ 形如 $r+k\times y$。把 $n$ 个 $r$ 提出来，除掉 $y$，枚举第 $1$ 个取模操作在 $i$ 位置。这样可以确定 a 数组形如 $\frac{x}{y},\dots,\frac{x}{y}+i,0,1,2,\dots,k_1,\dots,0,1,2,\dots,k_x,0,\dots,0$。 

问题转换为在 $i$ 个位置内凑出若干个 $0,1,2,\dots,k$ 使和为 $s$，多余位置不停取模用 $r$ 补上希望在可行的复杂度内预处理。

考虑 dp。因为 $s\leq 2\times 10^5$ 而 $\sum_{i=0}^k i=\frac{k\times (k-1)}{2}$ 是根号级别的，可以 $O(\sqrt n)$ 枚举加上哪个 $0,1,2,\dots,k$。设 $dp_s$ 表示最少用几个位置凑出 $s$。

$$dp_s=\min dp_{s-\frac{k\times (k-1)}{2}}+k+1$$

### code 

```cpp
int n,x,y,s,r,k;
int dp[maxn],pre[maxn][2];
void sovle(){
	n=read(),x=read(),y=read(),s=read();
	r=x%y;s-=r*n;k=x/y;
	if(s<0||s%y!=0){
		printf("NO\n");
		return ;
	}
	s/=y;
	for(int i=k;i<=k+n-1;i++){
		if(s<(k+i)*(i-k+1)/2)break;
		if(dp[s-(k+i)*(i-k+1)/2]>n-(i-k+1))continue;
		s-=(k+i)*(i-k+1)/2; 
		// cout<<s<<" "<<i<<" "<<dp[s]<<"\n";
		printf("YES\n");
		for(int j=1;j<=i-k+1;j++)printf("%lld ",x),x+=y,n--;
		while(s){
			x=r,printf("%lld ",x),n--;
			int l=pre[s][1];s=pre[s][0];
			for(int j=1;j<=l;j++)x+=y,printf("%lld ",x),n--;
		}
		while(n)printf("%lld ",r),n--;
		printf("\n");
		return ;
	}
	printf("NO\n");
}

int T;
signed main(){
	memset(dp,0x3f,sizeof(dp));dp[0]=0;
	for(int i=1;i<=maxn-10;i++){
		for(int j=1;j*(j+1)/2<=i;j++){
			if(dp[i]>dp[i-j*(j+1)/2]+j+1){
				dp[i]=dp[i-j*(j+1)/2]+j+1;
				pre[i][0]=i-j*(j+1)/2,pre[i][1]=j;
			}
		}
	}
	T=read();
	while(T--)sovle();
}
```

---

## 作者：w9095 (赞：0)

[CF1928E Modular Sequence](https://www.luogu.com.cn/problem/CF1928E)

考虑合法的答案的构成为一个 $x,x+y,\dots x+ky$ 的块加上若干个 $x\bmod y,x\bmod y+y,\dots x\bmod y+ky$ 的块。因为无论加多少次 $y$，对 $y$ 进行一次取模就都被消去了。

我们考虑枚举 $x,x+y,\dots x+ky$ 的块的长度，然后判断剩余的数的总和能否被剩余的位置拼出。这里不判断剩余位置能否拼出剩余的数的总和，因为这个很难预处理，也很难快速计算。

我们把除了第一个块的元素，每一个都减去 $x\bmod y$，再除以 $y$，就变成了若干个 $0,1,\dots k$ 的块。这样的好处是，如果拼出剩余的数的总和的序列长度小于剩余的位置，就可以补入 $0$ 来占位。

我们记 $dp[i]$ 为拼出总和为 $i$ 的序列的最小长度。我们枚举 $j$，表示新增一个长度为 $j-1$ 的块，可以使用等差数列求和公式得到这个块的和，容易得到如下转移方程：

$$dp[i]=\min(dp[i],dp[i-\frac{j\times(j-1)}{2}]+j)(\frac{j\times(j-1)}{2}\le i)$$

由于题目需要输出方案，所以还需要记录每次转移的前驱与新增块的长度，方便输出方案。

时间复杂度为 $O(s\sqrt{s}+n)$，可以通过。

需要注意，有很多种情况会导致当前枚举的长度不可行，具体可以看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,x,y,s,f[300000],pr[300000],pz[300000],a[300000];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	bool flag=1;
	   	scanf("%lld%lld%lld%lld",&n,&x,&y,&s);
	   	for(int i=0;i<=s;i++)f[i]=1e10,pr[i]=0,pz[i]=0;
	   	f[0]=0;
	   	for(int i=1;i<=s;i++)
	   	    for(int j=2;j*(j-1)/2<=i;j++)
	   	        if(f[i-j*(j-1)/2]+j<f[i])f[i]=f[i-j*(j-1)/2]+j,pr[i]=i-j*(j-1)/2,pz[i]=j;
		for(int i=1;i<=n;i++)
	   	    {
	   	    long long ns=s-i*x-i*(i-1)*y/2;
			if(ns<0)break;
			a[1]=x;
			for(int j=2;j<=i;j++)a[j]=a[j-1]+y;
			ns-=(n-i)*(x%y);
			if(ns<0||ns%y!=0)continue;
			ns/=y;
			if(f[ns]>n-i)continue;
			flag=0;
			for(int j=i+1;j<=n-f[ns];j++)a[j]=x%y;
			long long now=n-f[ns]+1;
			while(ns)
			   {
			   	for(long long j=0;j<pz[ns];j++)a[now+j]=x%y+j*y;
			   	now+=pz[ns];
			   	ns=pr[ns];
			   }
			break;	
			}
		if(flag)printf("NO\n");
		else
		   {
		   	printf("YES\n");
		   	for(int i=1;i<=n;i++)printf("%lld ",a[i]);
		   	printf("\n");
		   }
	   }
	return 0;
}
```

---

## 作者：Register_int (赞：0)

显然最后的序列中每个数都是 $(x\bmod y)+py$ 的形式。我们直接构造 $p$，问题转化为：构造一个长度为 $n$ 的序列 $p$，满足 $(x\bmod y)\times n+y\sum _ip_i=s$，并且 $p_i=p_{i-1}+1$ 或 $0$。

设 $dp_i$ 为满足 $p_1=0$，且 $\sum p=i$ 的序列的最小长度。考虑每次加进新的 $0,1,2,\cdots,j-1$ 的一段，那么得到转移：

$$dp_i=\min_j(dp_{i-\binom j2}+j)$$

显然 $j$ 最多只会有 $O(\sqrt n)$ 个，这部分的时间复杂度为 $O(n\sqrt n)$。

考虑如何从这个 dp 数组得出答案。由于给定了 $p_1=\left\lfloor\frac xy\right\rfloor$，不妨枚举第一段为 $\left\lfloor\frac xy\right\rfloor,\left\lfloor\frac xy\right\rfloor+1,\left\lfloor\frac xy\right\rfloor+2,\cdots, \left\lfloor\frac xy\right\rfloor+i-1$。此时计算剩余的和 $s'$，只要 $s'$ 能用长度 $n-i$ 及以下的序列凑出来，就一定能满足条件，因为我们可以在空位补 $0$。此时相当于判断 $dp_{s'}$ 是否为 $\le n-i$。输出方案直接在 dp 数组上回溯即可，时间复杂度 $O(n\sqrt n)$。

若 $s\not\equiv nx\pmod y$ 或者 $s<(x\bmod y)\times n$，就可以直接判无解。枚举了第一段的所有可能长度后仍不可行，也为无解。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int dp[MAXN];

inline 
void init(int n) {
	for (int i = 1; i <= n; i++) {
		dp[i] = 1e9;
		for (int j = 1; j * (j - 1) / 2 <= i; j++) {
			dp[i] = min(dp[i], dp[i - j * (j - 1) / 2] + j);
		}
	}
}

void print(int i, int x, int y) {
	if (!i) return ;
	for (int j = 1; j * (j - 1) / 2 <= i; j++) {
		if (dp[i] != dp[i - j * (j - 1) / 2] + j) continue;
		for (int k = 0; k < j; k++) printf("%d ", x + k * y);
		return print(i - j * (j - 1) / 2, x, y);
	}
}

int t, n, m, x, y, tx; bool f;

int main() {
	scanf("%d", &t), init(2e5);
    for (int i = 1; i <= t; i++) {
    	scanf("%d%d%d%d", &n, &x, &y, &m), f = 0, tx = x;
    	if (m % y != (ll)n * x % y || (ll)x % y * n > m) { puts("NO"); continue; }
    	m = (m - x % y * n) / y, x /= y;
    	for (int i = 1; i <= n; i++) {
    		m -= x + i - 1; if (m < 0) break;
			if (dp[m] > n - i) continue; f = 1, puts("YES");
    		for (int j = 0; j < i; j++) printf("%d ", tx + y * j);
    		print(m, tx % y, y);
    		for (int j = i + dp[m]; j < n; j++) printf("%d ", tx % y);
			puts(""); break;
		}
		if (!f) puts("NO");
	}
}
```

---

## 作者：Rain_chr (赞：0)

本来不想写题解的，但发现题解区唯一一篇太过复杂，加上本题比较有趣，所以还是记录一下思考过程吧。

首先可以发现，数列中所有数字都可以拆成 $ay+(x\bmod y)$ 的形式，那么我们可以先将和减去 $n(x\bmod y)$，如果此时和为负数或不能被 $y$ 整除，那么一定无解。

接着我们可以发现，整个数列可以被分成若干连续上升段，除第一段外，每一段的都是从零开始的连续上升段。之所以连续，是因为每次加上 $y$；从零开始，则对应取模操作。

显然，和相同的情况下，序列长度越短越优，那么我们可以直接做完全背包，把每个上升段当作物品进行 DP。设当前连续段长度为 $i$，物品代价即 $\frac{i(i-1)y}{2}$，权值即 $i$。

可以发现，这样的物品只会有 $O(\sqrt s)$ 个，那么背包的复杂度就是 $O(s\sqrt s)$。

那么剩下的就是最开始的那一段，这一段由 $\lfloor \frac{x}{y} \rfloor$ 开头。我们可以枚举除第一段外所有段的和，再二分找到一个端点，使得第一段的权值加上其他段的和恰好为 $s$。如果长度不到 $n$，就在最后面补零。最后每个位置记得加上一开始减去的 $x\bmod y$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e5+10;
int dp[N],pre[N],from[N];
int f(int x)
{
	return x*(x-1)/2;
}
int ans[N];
int sum(int l,int r)
{
	return (l+r)*(r-l+1)/2;
}
int n,x,y,s;
int pos=0;
void print(int x)
{
	if(x==0) return ;
	print(pre[x]);
	for(int i=0;i<from[x];i++)
		ans[++pos]+=y*i;
}
void run()
{
	cin>>n>>x>>y>>s;
	for(int i=1;i<=s;i++) dp[i]=1e9,pre[i]=from[i]=0;
	int k=x%y;
	s-=k*n;
	if(s<0||s%y)
	{
		cout<<"NO\n";
		return ;
	}
	for(int i=1;i<=n;i++) ans[i]=k;
	for(int i=2;y*f(i)<=s;i++)
	{
		int now=y*f(i);
		for(int j=now;j<=s;j++)
		{
			if(dp[j]>dp[j-now]+i)
			{
				pre[j]=j-now;
				dp[j]=dp[j-now]+i;
				from[j]=i;
			}
		}
	}
	for(int i=0;i<=s;i++)
	{
		int l=x/y,r=x/y+n-1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(y*sum(x/y,mid)==s-i)
			{
				if(mid-x/y+1+dp[i]<=n)
				{
					for(int j=x/y;j<=mid;j++)
						ans[j-x/y+1]+=j*y;
					pos=mid-x/y+1;
					print(i);
					cout<<"YES\n";
					for(int j=1;j<=n;j++)
						cout<<ans[j]<<' ';
					cout<<endl;
					return ;
				}
				break;
			}
			else if(y*sum(x/y,mid)>s-i) r=mid-1;
			else l=mid+1;
		}
	}
	cout<<"NO\n";
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    	run();
    return 0;
} 

```


---

## 作者：DerrickLo (赞：0)

我们注意到 $a_i \bmod y=x \bmod y$，那么我们可以假设 $b_i=\displaystyle{\frac{a_i-x\bmod y}{y}}$，那么 

$$\sum b_i=\displaystyle{\frac{\sum(a_i-x\bmod y)}{y}}=\frac{\sum a_i-(x\bmod y)\times n}{y}=\frac{s-(x\bmod y)\times n}{y}$$

这样我们就能把原问题转化为一个新问题：$b_1=\lfloor\frac{x}{y}\rfloor$，$b_i=b_{i-1}+1$ 或 $0$，问和能否为一个给定的数。

这个问题就很好做了。先预处理一下每个数分成若干个形为 $0,1,2,\ldots,n$ 的序列的和，这些序列长度的和的最小值是多少，这可以用 `dp` 求解，然后枚举第一个变成 $0$ 的位置，看看符不符合条件即可，输出可以把 `dp` 的顺序逆过来做。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,y,s,dp[200005];
signed main(){
	cin>>t;
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	for(int i=1;i<=200000;i++){
		for(int j=1;j*(j-1)/2<=i;j++)dp[i]=min(dp[i],dp[i-j*(j-1)/2]+j);
	}
	while(t--){
		cin>>n>>x>>y>>s;
		if(x*n%y!=s%y){
			cout<<"NO\n";
			continue;
		}
		s=(s-(x%y)*n)/y;
		if(s<0){
			cout<<"NO\n";
			continue;
		}
		int now=x/y,cnt=0,flag=-1,sum=x/y;
		while(sum<=s){//枚举第一个变成0的位置
			cnt++;
			if(dp[s-sum]<=n-cnt){
				flag=cnt;
				break;
			}
			now++,sum+=now;
		}
		if(flag==-1){
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		for(int i=x/y;i<x/y+flag;i++)cout<<i*y+(x%y)<<' ';
		int maxx=dp[s-sum],noww=s-sum;
		while(noww){
			for(int j=1;j*(j-1)/2<=noww;j++)if(dp[noww]==dp[noww-j*(j-1)/2]+j){
				for(int k=0;k<j;k++)cout<<k*y+(x%y)<<' ';
				noww-=j*(j-1)/2;
				break;
			}
		}
		for(int i=1;i<=n-cnt-maxx;i++)cout<<x%y<<" ";
		cout<<"\n";
	}
}
```

---

