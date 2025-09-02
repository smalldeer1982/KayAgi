# [AGC066A] Adjacent Difference

## 题目描述

#### 题目大意

给定一个大小为 $n*n$ 的数组 $A$ 和数字 $d$ ， 和数组中的每个数字 $A_{i,j}$ ， 你可以对每个数字进行加上一个数或减去一个数的操作 ， 使得每个数字与其相邻数字的差的绝对值大于等于 $d$ 。 并且对于每个操作值的绝对值之和不超过 $\frac{1}{2}dn^2$ 。

## 样例 #1

### 输入

```
3 5
-2 1 3
3 -4 -4
0 1 3```

### 输出

```
-2 8 3
3 -9 -4
-2 8 3```

## 样例 #2

### 输入

```
5 2
1 5 5 0 3
2 0 2 5 1
5 2 0 5 5
3 7 2 0 1
6 0 4 3 6```

### 输出

```
0 4 6 1 3
3 1 3 6 1
5 3 0 3 5
2 6 3 1 3
4 0 5 3 6```

# 题解

## 作者：快斗游鹿 (赞：9)

## 思路

先考虑一个特殊情况，当 $a_{i,j}=0$，且 $d=1$ 时，怎么构造？显然，我们可以把 $i+j$ 为偶数的格子都置成 $1$，或把 $i+j$ 为奇数的格子都置成 $1$，两种方法中总有一种能满足条件。这启发我们可以对 $i+j$ 的奇偶性分类讨论。

可以想到一种最简单的构造方法：

当 $i+j$ 是偶数时，$a_{i,j}=k$。

当 $i+j$ 是奇数时，$a_{i,j}=k+d$。

这样一定可以满足条件，但代价并不优。不过我们注意到，这时对于每个 $a_{i,j}$，将它加上 $x\times 2d$ 后，它一定也能满足条件，因此考虑如下构造：

当 $i+j$ 是偶数时，$a_{i,j}\equiv k\pmod {2d}$。

当 $i+j$ 是奇数时，$a_{i,j}\equiv k+d\pmod {2d}$。

尝试枚举每个可能的 $k$，总时间复杂度 $O(dn^2)$，已经可以通过。

但我们还有更好的解法，注意到 $k=0$ 时或 $k=d$ 时，总有一种情况可以满足条件。如何证明？设 $x=a_{i,j}\bmod 2d$。

当 $0\le x\le d$ 时，$k=0$ 时需要花费的代价为 $x$，$k=d$ 时需要花费的代价为 $d-x$。

当 $d<x<2d$ 时，$k=0$ 时需要花费的代价为 $2d-x$，$k=d$ 时需要花费的代价为 $x-d$。

可以发现，$k=0$ 和 $k=d$ 时两种情况加起来的总代价为 $dn^2$，故必有一种的代价小于 $\dfrac{1}{2}dn^2$。分别讨论两种情况即可。总时间复杂度 $O(n^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <math.h>
#include <cstdio>
#define int long long
using namespace std;
const int inf=1e18;
const int N=505;
int n,d,a[N][N],b[N][N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	//freopen("std.in","r",stdin);
	//ios::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	n=read();d=read();int mod=2*d;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read(),b[i][j]=a[i][j];
	}
	int cost=0;
	//(i+j)%2=0,a(i,j)mod 2d=k
	//(i+j)%2=1,a(i,j)mid 2d=k+d;
	//k=0,k=d
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int x=abs(a[i][j])%mod;
			if((i+j)%2==0){
				if(x<=d){
					cost+=x;
					if(a[i][j]<0)a[i][j]+=x;
					else a[i][j]-=x;
				}
				else{
					cost+=(2*d-x);
					if(a[i][j]<0)a[i][j]-=(2*d-x);
					else a[i][j]+=(2*d-x);
				}
				if(x<=d){
					if(b[i][j]<0)b[i][j]-=(d-x);
					else b[i][j]+=(d-x);
				}
				else{
					if(b[i][j]<0)b[i][j]+=(x-d);
					else b[i][j]-=(x-d);
				}
			}
			else{
				if(x<=d){
					cost+=(d-x);
					if(a[i][j]<0)a[i][j]-=(d-x);
					else a[i][j]+=(d-x);
				}
				else{
					cost+=(x-d);
					if(a[i][j]<0)a[i][j]+=(x-d);
					else a[i][j]-=(x-d);
				}
				if(x<=d){
					if(a[i][j]<0)b[i][j]+=x;
					else b[i][j]-=x;
				}
				else{
					if(b[i][j]<0)b[i][j]-=(2*d-x);
					else b[i][j]+=(2*d-x);
				}
			}
		}
	}
	int lim=d*n*n;lim/=2;
	if(cost<=lim){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)cout<<a[i][j]<<" ";
			cout<<endl;
		}
		return 0;
	}
	else{
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)cout<<b[i][j]<<" ";
			cout<<endl;
		}
	}
	return 0;
}

```

---

## 作者：ZnPdCo (赞：8)

笑点解析：没有必要将总成本最小化。

---

我们将格子间隔的黑白染色（显然有两种染色方法），对于黑点我们要求它是奇数倍 $d$，对于白点我们要求它是偶数倍 $d$，这样一定满足相邻格子相差至少 $d$。

因为两种染色方法的代价和为 $dN^2$，所以两种方法中至少有一种满足代价小于 $\frac{1}{2}dN^2$，容易实现：

```cpp
ll n, m, ans = 1e15, Case=1;
ll a[N][N], b[N][N], c[N][N];
void solve() {
	input(n, m);
	for(ll i = 1; i <= n; i++) {
		for(ll j = 1; j <= n; j++) {
			input(a[i][j]);
		}
	}
	for(ll x = 0; x <= 1; x ++) {
		ll sum = 0;
		for(ll i = 1; i <= n; i ++) {
			for(ll j = 1; j <= n; j ++) {
				ll k = a[i][j] / m;
				if((i + j + k + x) % 2 == 0) {
					if(a[i][j] < 0) k --;
					else k ++;
				}
				b[i][j] = k * m;
				sum += abs(b[i][j] - a[i][j]);
			}
		}
		if(sum < ans) {
			for(ll i = 1; i <= n; i ++) {
				for(ll j = 1; j <= n; j ++) {
					c[i][j] = b[i][j];
				}
			}
			ans = sum;
		}
	}
	for(ll i = 1; i <= n; i ++) {
		for(ll j = 1; j <= n; j ++) {
			print(c[i][j]);
		}
		putchar('\n');
	}
//	print(ans);
}
```

---

## 作者：Rainbow_qwq (赞：3)

将网格黑白染色，$i+j$ 为奇数/偶数 标为 黑色/白色。

将黑色格变为 $a_{i,j}\bmod 2d = 0$，白色格变为 $a_{i,j}\bmod 2d = d$。这样代价上界为 $n^2d$，即把 $x$ 移向一个 $2d$ 长度的区间的端点。

但是这样的“期望代价”是 $\frac{1}{2}n^2d$ 的。考虑枚举 $x$，将黑色格变为 $a_{i,j}\bmod 2d = x$，白色格变为 $a_{i,j}\bmod 2d = d+x$，根据鸽巢原理，一定有一种方案代价在 $\frac{1}{2}n^2d$ 之内。

题外话：赛时一开始就想到了这个做法，但以为是 $n^2d$ 的就否定了..

---

## 作者：xixihaha2021 (赞：1)

# [[AGC066A] Adjacent Difference](https://www.luogu.com.cn/problem/AT_agc066_a)
## 题意简述
给定一个矩阵，每次操作可以选择一个 $x \in \mathbb{Z}$，将某一项加上 $x$。希望通过若干次操作使得矩阵相邻项的差值不小于 $d$，使得 $\sum |x| \le \frac{1}{2}dn^2$。求一个满足要求的答案矩阵。
## 思路简述
将每个位置 $a_{i,j}$ 按照 $i+j$ 的奇偶性分类，要求其中一类均为 $2kd(k \in \mathbb{Z})$ 形式，另一类均为 $(2k+1)d(k \in \mathbb{Z})$ 形式，则符合题意。如上是容易的，即对每个位置找到最近的相应形式的数并进行修改即可。

显然有 $2$ 种分类，则分类讨论，只需如上两类情况种必存在一种合法即可。显然两种情况的 $\sum |x|$ 的平均值为 $\frac{1}{2}dn^2$，故其中必有一项不大于 $\frac{1}{2}dn^2$。

时间复杂度 $O(dn^2)$，空间复杂度 $O(n^2)$。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,d,sum,a[505][505],b[505][505],tmp;
ll read(){
	ll x = 0;
	bool f = true;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-')f = !f;
		ch = getchar();
	}
	while(isdigit(ch))x = x * 10 + ch - '0',ch = getchar();
	return x * f * 2 - x;
}
ll write(ll x,string ch){
	ll f = 1,L = ch.size(),tmp = x;
	if(tmp < 0){
		putchar('-');
		tmp *= -1;
	}
	while(f <= tmp)f *= 10;
	if(tmp)f /= 10;
	while(f){
		putchar(tmp / f + '0');
		tmp -= (tmp / f * f),f /= 10;
	}
	for(ll i = 0;i <= L - 1;i++)putchar(ch[i]);
	return x;
}
int main(){
	n = read(),d = read();
	for(ll i = 1;i <= n;i++)for(ll j = 1;j <= n;j++)a[i][j] = read();
	for(ll k = 0;k <= d * 2;k++,sum = 0){
		for(ll i = 1;i <= n;i++){
			for(ll j = 1;j <= n;j++){
				tmp = a[i][j] - (a[i][j] % (d * 2) + d * 2) % (d * 2) + k * ((i + j) % 2) + ((k + d) % (d * 2)) * ((i + j + 1) % 2);
				if(tmp > a[i][j])tmp -= d * 2;
				if(a[i][j] - tmp < tmp + d * 2 - a[i][j])sum += a[i][j] - tmp,b[i][j] = tmp;
				else sum += tmp + d * 2 - a[i][j],b[i][j] = tmp + d * 2;
			}
		}
		if(sum <= n * n * d / 2){
			for(ll i = 1;i <= n;i++){
				for(ll j = 1;j <= n;j++)write(b[i][j]," ");
				puts("");
			}
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：_HCl_ (赞：1)

非常好玩的一道题。

# AGC066A Adjacent Difference 题解

**题意简述**

给定方阵 $A$，对 $A$ 中每个数加减一个数，使得相邻两数的差值大于等于 $d$，并且操作数的绝对值之和小于等于 $\frac{1}{2}dn^2$。

**思路引导**

考虑黑白间隔染色。意图通过操作，使得黑色方格的数是 $d$ 的奇数倍，白色方格的数是 $d$ 的偶数倍。容易证明，经过这样的操作，可以使得不同颜色的格子差值大于等于 $d$。

发现这样的染色方式有两种，并且两种染色方式的花费之和等于 $dn^2$。这是因为每个格子在两种染色方式中的操作，一种是向上加到 $d$ 的整数倍，一种是向下减到 $d$ 的整数倍，因此两个操作花费和就是 $d$。

那么就有，两种染色方式中，必定有一种染色方式的操作花费小于等于 $\frac{1}{2}dn^2$。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1001;
int n,d;
int a[N][N],b[2][N][N],sum[2];
int M(int x,int m){
	while(x<0)x+=m;
	return x%m;
}
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j){
			scanf("%d",&a[i][j]);
			int f=(i+j)%2;
			int mod=M(a[i][j],d);
			int tmp=a[i][j]-mod;
			int f2=M(tmp/d,2);
			b[f2^f][i][j]=tmp,sum[f2^f]+=mod;
			b[f2^f^1][i][j]=tmp+d,sum[f2^f^1]+=d-mod;
		}
	int lim=(d*n*n)>>1,f;
	if(sum[0]<=lim)f=0;
	else f=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)cout<<b[f][i][j]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：TLE_Automat (赞：1)

## 题目链接

[https://atcoder.jp/contests/agc066/tasks/agc066_a](https://atcoder.jp/contests/agc066/tasks/agc066_a)

## 题目大意

给定一个 $N \times N$ 的方阵 $A_{i, j}$ 和一个正整数 $d$。每次可以花费 $x$ 的代价将矩阵的某一个位置加上 $x$ 或减去 $x$。请构造一种方案使得方阵中所有相邻位置的差的绝对值大于等于 $d$，且代价之和小于等于 $\frac{1}{2}N^{2}d$。

## 数据范围

- $2\le N \le 500$
- $1\le d \le 1000$
- $-1000 \le A_{i, j} \le 1000$

## 解题思路

先说结论：

1. 将方阵黑白染色，然后将**黑色**的位置变为 $\bmod 2d = 0$ 的最近的数，将**白色**的位置变为 $\bmod 2d = d$ 的最近的数，假设代价此为 $c_0$​。
2. 将方阵黑白染色，然后将**白色**的位置变为 $\bmod 2d = 0$ 的最近的数，将**黑色**的位置变为 $\bmod 2d = d$ 的最近的数，假设代价此为 $c_1$。

则上述两种情况中必有一种满足条件。

证明：

由于上述构造中黑白相邻位置的差的绝对值至少为 $d$，所以满足第一个条件。

考虑第二个条件。假设把一个位置上的数变为 $\bmod 2d = 0$ 的最近数的代价为 $x$，变为 $\bmod 2d = d$ 的最近的数的代价为 $y$，那么一定有 $x + y = d$。这就意味着 $c_0 + c_1 = N ^ {2} d$，则 $c_0$ 和 $c_1$ 中必有一个小于等于 $\frac{1}{2}N^{2}d$。

## 参考代码

[https://atcoder.jp/contests/agc066/submissions/51989697](https://atcoder.jp/contests/agc066/submissions/51989697)

---

## 作者：_Ch1F4N_ (赞：0)

简单题。

对网格图黑白染色，将相邻限制放到黑白之间，由于希望相邻差大于等于 $d$，我们考虑将每个点的值按照黑白错开。

不妨把值域按照 $d$ 分块，一个数可以调整为 $d \times i$ 或者 $d \times (i+1)$，考虑把黑格调为 $d$ 的奇数倍，白格调为 $d$ 的偶数倍，那么相邻项一定至少差 $d$，但是这种方案的操作次数可能有 $d \times n^2$，注意这种调整方案的操作次数和将网格图的颜色翻转后的调整方案的操作次数之和恰好是 $d \times n^2$，所以两个方案中选取合法的就行。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 514;
int a[maxn][maxn],n,d,b[maxn][maxn];
signed main(){
	cin>>n>>d;
	long long res=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			a[i][j]+=1000;
			int z=a[i][j]/d;
			if(((i+j)&1)^(z&1)==1){
				z++;
			}
			b[i][j]=z*d;
			res+=abs(a[i][j]-b[i][j]);
		}
	}
	if(2*res>d*n*n){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int z=a[i][j]/d;
				if(((i+j+1)&1)^(z&1)==1){
					z++;
				}
				b[i][j]=z*d;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cout<<b[i][j]-1000<<" ";
		cout<<"\n";
	}
	return 0;
}

```

---

## 作者：bamboo12345 (赞：0)

并不困难的题。

题意：很简单了，不再赘述。

做法：

注意到我们只需要给出来一种构造就行了，不用最小化任何东西，我们可以考虑直接黑白染色，然后考虑让黑色点成为奇数倍的 $d$，白点成为偶数倍的 $d$，或者相反。

因为注意到对于一个点，要不然向上取，要不然向下取，所两种方法总共是 $n^2d$ 的代价的，一定有一种可以达成。

然后一点实现上的细节，当一个数是负数且不满足我们要求的奇偶性时，我们会让他向下取，整数则向上取。

代码：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 505, mod = 998244353, N = 6000;
int n, a[maxn][maxn], k, b[maxn][maxn];
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> a[i][j];
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int t = a[i][j] / k;
			if((i + j + t) % 2)
				t += (a[i][j] >= 0 ? 1 : -1);
			sum += abs(a[i][j] - t * k);
			b[i][j] = t * k;
		}
	}
	if(sum * 2 > n * n * k) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int t = a[i][j] / k;
				if((i + j + t) % 2 == 0)
					t += (a[i][j] >= 0 ? 1 : -1);
				sum += abs(a[i][j] - t * k);
				b[i][j] = t * k;
			}
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cout << b[i][j] << (j == n ? '\n' : ' ');
	return 0;
}
/*
2 
1 3
2 4
*/
```

---

## 作者：WaterM (赞：0)

首先将矩阵黑白染色。目标是将所有的黑色格子变成 $d$ 的奇数倍，白色格子变成 $d$ 的偶数倍。

一种可行的方案是，黑（白）格子都变成**距离自身最近的**奇数（偶数）倍的 $d$。显然这种方案下，每个格子加减的数不会超过 $d$。但是这时总代价最大可能是 $dn^2$。

考虑与之对称的方案，令黑色格子变成 $d$ 的偶数倍，白色格子变成 $d$ 的奇数倍。因为一个数肯定夹在一个【奇数倍的 $d$】和【偶数倍的 $d$】之间。所以每个格子在两种方案种的代价和是 $d$。故两种方案的总代价是 $dn^2$。

根据鸽巢原理，取较小代价的方案符合条件。

---

## 作者：chenhouyuan (赞：0)

~~喜欢这种没有数据结构和算法的题。~~

首先 $d$ 的任意奇数倍和 $d$ 的任意偶数倍之差大于 $d$ 是显然的，所以我们考虑对方阵黑白染色，黑点改为相差最小的 $d$ 的奇数倍，白点改为相差最小的 $d$ 的偶数倍，在反过来做一遍，即黑变偶数倍，白变奇数倍。由于一个数与最近的 $d$ 的奇数倍和偶数倍之差之和为 $d$，所以上述两种更改方案的代价和为 $dn^2$，所以必有一种的代价小于 $\frac{1}{2}dn^2$，输出即可。
##### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=505;
int a[N][N],n,d,ans1,ans2,b[N][N],c[N][N];
int f1(int x){
	int f=1;
	if(x<0){
		f=-1;
		x=-x;
	}
	int tmp=x/d;
	if(tmp%2)return tmp*d*f;
	else return (tmp+1)*d*f;
}
int f0(int x){
	int f=1;
	if(x<0){
		f=-1;
		x=-x;
	}
	int tmp=x/d;
	if(tmp%2==0)return tmp*d*f;
	else return (tmp+1)*d*f;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>d;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if((i+j)%2){
				b[i][j]=f1(a[i][j]);
			}
			else{
				b[i][j]=f0(a[i][j]);
			}
			ans1+=abs(b[i][j]-a[i][j]);
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if((i+j)%2==0){
				c[i][j]=f1(a[i][j]);
			}
			else{
				c[i][j]=f0(a[i][j]);
			}
			ans2+=abs(c[i][j]-a[i][j]);
		}
	}
	if(ans1<=0.5*d*n*n){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<b[i][j]<<' ';
			}
			cout<<'\n';
		}
	}
	else{
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cout<<c[i][j]<<' ';
			}
			cout<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Phartial (赞：0)

幽默构造。

考虑直接钦定 $A_{i,j}-A_{i+1,j}\equiv d\pmod{2d}$，设 $k\equiv A_{1,1}\pmod{2d}$（这里指的是操作后的 $A_{1,1}$），则：

- 对 $i+j\equiv 0\pmod 2$，有 $A_{i,j}\equiv k\pmod{2d}$；
- 对 $i+j\equiv 1\pmod 2$，有 $A_{i,j}\equiv k+d\pmod{2d}$；

容易最小化使 $A$ 满足这两条约束的操作次数，但还有一个问题是最小的操作次数还是可能超过 $\frac{1}{2}dN^2$。

一种想法是考察 $k=0$ 和 $k=d$ 的情况，此时两种情况各对应一种约束：$A_{i,j}\equiv 0\pmod{2d}$ 和 $A_{i,j}\equiv d\pmod{2d}$（对任意 $i,j$ 都是如此）。则任意一个 $A_{i,j}$ 要满足这两个约束需要的操作次数必然是一个 $x$ 一个 $d-x$，于是 $k=0$ 时的操作次数和 $k=d$ 时的操作次数之和是 $dN^2$，由抽屉原理，其中必有一种选择能使得操作次数 $\le\frac{1}{2}dN^2$。

直接嗯写就行。

```cpp
#include <iostream>

using namespace std;

const int kN = 501;

int n, d, a[kN][kN], b[kN][kN];

int F(int d, int m) { return (d - (m - 1) * (d < 0)) / m; }
bool C(int k) {
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int _k = k;
      if (!(i + j & 1)) {
        k = d - k;
      }
      int f = F(a[i][j] - k, 2 * d) * (2 * d) + k;
      int c = F(a[i][j] - k + 2 * d - 1, 2 * d) * (2 * d) + k;
      if (a[i][j] - f < c - a[i][j]) {
        ans += a[i][j] - f, b[i][j] = f;
      } else {
        ans += c - a[i][j], b[i][j] = c;
      }
      k = _k;
    }
  }
  if (ans <= n * n * d / 2) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        cout << b[i][j] << ' ';
      }
      cout << '\n';
    }
    return 0;
  }
  return 1;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> d;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cin >> a[i][j];
    }
  }
  return C(0) && C(d);
}
```

---

