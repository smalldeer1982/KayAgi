# Non-coprime Split

## 题目描述

You are given two integers $ l \le r $ . You need to find positive integers $ a $ and $ b $ such that the following conditions are simultaneously satisfied:

- $ l \le a + b \le r $
- $ \gcd(a, b) \neq 1 $

or report that they do not exist.

 $ \gcd(a, b) $ denotes the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of numbers $ a $ and $ b $ . For example, $ \gcd(6, 9) = 3 $ , $ \gcd(8, 9) = 1 $ , $ \gcd(4, 2) = 2 $ .

## 说明/提示

In the first test case, $ 11 \le 6 + 9 \le 15 $ , $ \gcd(6, 9) = 3 $ , and all conditions are satisfied. Note that this is not the only possible answer, for example, $ \{4, 10\}, \{5, 10\}, \{6, 6\} $ are also valid answers for this test case.

In the second test case, the only pairs $ \{a, b\} $ that satisfy the condition $ 1 \le a + b \le 3 $ are $ \{1, 1\}, \{1, 2\}, \{2, 1\} $ , but in each of these pairs $ \gcd(a, b) $ equals $ 1 $ , so there is no answer.

In the third sample test, $ \gcd(14, 4) = 2 $ .

## 样例 #1

### 输入

```
11
11 15
1 3
18 19
41 43
777 777
8000000 10000000
2000 2023
1791791 1791791
1 4
2 3
9840769 9840769```

### 输出

```
6 9
-1
14 4
36 6
111 666
4000000 5000000 
2009 7
-1
2 2
-1
6274 9834495```

# 题解

## 作者：_Mikasa (赞：7)

题意：

给定两个整数 $l, r$，要求找到一组 $a, b$，使得 $a + b\in[l, r]$ 且 $a, b$ 不互质。

一个很暴力的思路就是遍历 $sum\in [l, r]$，对于每一个 $sum$ 找到最小的因数 $p$，答案就是 $p$ 和 $sum - p$。如果是质数的话直接跳到下一个 $sum$。

期望在遍历两个 $sum$ 后找到答案，因为除了 $2, 3$ 外没有间隔为 $1$ 的质数。

Code:

```
int minp(int x)
{
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) return i;
	}
	return 0;
}
 
void solve()
{
	int l, r;
	cin >> l >> r;
	for (int i = l; i <= r; i++) {
		int p = minp(i);
		if (p == 0) continue;
		else {
			cout << p << ' ' << i - p << '\n';
			return;
		}
	}
	cout << "-1\n";
}
```


---

## 作者：One_JuRuo (赞：4)

## 思路

CF 典型的诈骗题。

假设分出来的 $a$ 和 $b$ 都有因子 $k$，那么 $a+b$ 也一定有因子 $k$，并且至少还存在另一个最小为 $2$ 的因子，才能分出 $a$ 和 $b$。

所以可以发现，质数是不满足要求的，考虑一个合数，一定可以拆成 $k\times a$ 的形式，那么就直接构造成 $k$ 和 $k\times (a-1)$ 就满足条件了。

所以我们可以提前线性筛预处理出每个数的最小质因子，然后遍历 $n$ 到 $m$，找到第一个合数，然后直接拆开就好了。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,su[10000005],pri[10000005],cnt,minp[10000005],flag;
inline void init()
{
	for(int i=2;i<=10000000;++i)
	{
		if(!su[i]) pri[++cnt]=i,minp[i]=i;
		for(int j=1;j<=cnt&&i*pri[j]<=10000000;++j)
		{
			su[i*pri[j]]=1,minp[i*pri[j]]=pri[j];
			if(i%pri[j]==0) break;
		}
	}
}
int main()
{
	init();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m),flag=0;
		for(int i=max(2,n);i<=m;++i) if(i/minp[i]>1){flag=1,printf("%d %d\n",minp[i],i-minp[i]);break;}
		if(!flag) printf("-1\n");//记得判无解
	}
}
```

---

## 作者：CheZiHe929 (赞：1)

# CF1872C 题解

### 简要题意

共有 $t$ 组测试数据，每组数据给定两个整数 $l,r$，请构造一组 $a,b$ 使满足以下条件：

- $l \le a+b \le r$
- $\gcd(a,b) \neq 1$

若有多组解，则输出任意一组。

若无解，则输出 `-1`。

### 简要思路

遍历 $l$ 到 $r$ 的这个区间，对于遍历到的数 $i$，记录其最小因子（除 $1$ 和其本身外）的值为 $p$，如果存在一个因子 $p$ 就输出该因子 $p$ 和 $i - p$ 即可。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

int get_min_factor(int x){//计算 x 的最小因子（除 1 外）

	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			return i;
			
	return 0;
}

signed main(){
	int t;
	cin>>t;
	while(t--){
		int l,r;
		cin>>l>>r;
		bool f=0;
		for(int i=l;i<=r;i++){//遍历 l 到 r 的区间
			int p=get_min_factor(i);
			if(p){
				cout<<p<<' '<<i-p<<endl;
				f=1;
				break;
			}
		}
		if(!f)cout<<-1<<endl;
	}

	return 0;
}
```

AC 记录在 [这里](https://www.luogu.com.cn/record/124708509)。

**THE END.**

**THANK YOU.**

---

## 作者：FeiDing (赞：1)

## 题目大意

给出 $l,r$，构造一组 $a,b$ 使满足以下条件：

- $l \le a+b \le r$
- $\gcd(a,b) \neq 1$

## 思路

要使 $\gcd(a,b) \neq 1$，也就是 $a$ 与 $b$ 不互质，最简单的就是 $b \mid a$ 或 $a \mid b$。

## 实现

枚举 $i$ 为 $\gcd(a,b)$ 也就是 $\min(a,b)$，找到一个 $k$ 使 $k \le r$ 且 $i\mid k$，若 $k<l$ 则无解，枚举下一个 $i$。若 $k \ge l$ 则再特判 $\min(i,k-i)$ 是否为 $1$，是则跳过此 $i$，否则输出 $i$ 与 $k-i$。

代码很简单：

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include<iostream>
using namespace std;
int t,l,r,a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>l>>r;
		for(int i=2;i*i<=r;++i){//这里与判质数同理
			int k=r/i;
			k*=i;
			if(k<l)//a+b是否在l与r之间
				continue;
			if(min(i,k-i)!=1){//再特判
				cout<<i<<' '<<k-i<<endl;
				goto end;//跳出循环
			}
		}
		cout<<"-1\n";
		end:
			continue;
	}
}
```


---

## 作者：Larryyu (赞：1)

## _Description_
给定两个数 $l,r$，你需要找到一对正整数 $a,b$，使得 $l\leq a+b\leq r$ 且 $\gcd(a,b)\neq1$。
## _Solution_ 
若 $r\leq3$，无论怎么取都无法满足条件，输出 ```-1``` 即可。

否则我们在 $l\sim r$ 中找到一个合数 $x$，对其质因数分解。若 $y$ 是它的一个质因子，输出  $(x\div y-1)\times y$ 和 $y$ 即可。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
void count(int x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			cout<<i<<" "<<x-i<<endl;
			return ;
		}
	}
	cout<<-1<<endl;
}
void  solve(){

	int l,r;
	cin>>l>>r;

	if(l==r){
		count(l);
	}else if(r<=3) cout<<-1<<endl;
	else{
		for(int i=r;i>=l;i--){
			if(i%2==0) { //偶数是合数中最多的一类数，可以降低复杂度
				count(i);//从r往l遍历，是因为r肯定大于3，而l可能小于3，大于3的偶数一定为合数
				return;
			}
		}
	}
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1872C) & [CF 传送门](//codeforces.com/problemset/problem/1872/C)
# 思路
这道构造题我方法乱想的，分情况考虑：
1. 当 $l<r$ 时，则 $l\sim r$ 之间肯定有一个偶数，只要选一个最大的偶数 $\lfloor\frac r2\rfloor\times2$ 对半分即可。特别需要注意的是，当 $\lfloor\frac r2\rfloor$ 为 $1$ 时，无解；
1. 当 $l=r$ 时，则我们需要枚举 $l$ 每个非 $1$ 因数，枚举到第一个因数 $x$ 后，若 $x\ne l$，则答案就是 $x$ 和 $\frac lx$。不过这样枚举太慢了，我们只要枚举到 $\lfloor\sqrt l\rfloor$ 就够了，因为一个合数一定有只要一个 $\le\lfloor\sqrt l\rfloor$ 的非 $1$ 因数。

# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, l, r;
bool f;
int main () {
	cin >> t;
	while (t --) {
		cin >> l >> r;
		f = 1;
		if (r > 3 && (l < r || ! (l & 1)))
			f = 0, cout << r / 2 << ' ' << r / 2 << '\n';
		else
			for (int i = 3; i * i <= l; ++ i)
				if (! (l % i)) { //第一个因数
					cout << l / i << ' ' << l - l / i << '\n';
					f = 0;
					break ;
				}
		if (f) //无解
			cout << "-1\n";
	}
	return 0;
}
```

---

## 作者：jr_inf (赞：0)

一个很怪的分讨想法。

当 $l \neq r$ 时，区间内一定有一个偶数。设最大的偶数为 $x$ ，那么当 $x > 2$ 时，可以得到一组解 $(2,x-2)$，此时 $\gcd(2,x-2) = 2$。

当 $l = r$ 时，问题转化为找 $a+b=l$ 且 $\gcd(a,b) \neq 1$ 的一组解。当 $l$ 不为质数时，设有 $l$ 的因数 $x$，那么 $(x,l-x)$ 是一组解，此时 $\gcd(x,l-x)$ 一定不为 1。

剩余情况无解，时间复杂度 $O(t\sqrt l)$。

code：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,l,r;
signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&l,&r);
		if(l!=r)
		{
			int cnt=r-r%2;
			if(cnt==2)puts("-1");
			else printf("%d %d\n",2,cnt-2);
		}
		else
		{
			bool f=0;
			for(int i=2;i*i<=l;i++)
			{
				if(l%i)continue;
				f=1;
				printf("%d %d\n",i,l-i);
				break;
			}
			if(!f)puts("-1");
		}
	}
}
```


---

## 作者：Daniel_yao (赞：0)

## Problem
给定 $l,r$，求是否存在满足条件的 $a,b$，使：
- $l \le a+b\le r$；
- $\gcd(a,b)\not= 1$；

若有多组解，任意输出一组。
## Solve
构造题。

要意识到一点，就是 $\gcd(a,a)=a$（笑），然后对着 $a+b\le r,a=b$ 构造就行了：
- 若 $r$ 为偶数， $a=b=\frac{r}{2}$；
- 若 $r$ 为奇数，$l<r$， $a=b=\frac{r-1}{2}$；

若 $r$ 为奇数，$l=r$。这时候就有点麻烦了。相当于已知 $a+b=r,\gcd(a,b)\not=1$，求 $a,b$。

因为 $\gcd(a,b)\not=1$，所以 $\gcd(a,r-a)\not=1$。根据欧几里得算法可知，$\gcd(a,r-a)=\gcd(a,r)\not=1$，所以我们只要知道 $a,r$ 是否有公共质因子即可。

$a$ 是未知量，换个角度想，若 $a$ 可以，则 $a$ 的所有质因子也可以。由于是公共质因子，所以 $\gcd(a,r)$ 的结果其实就是 $r$ 的所有质因子。设 $g$ 为 $r$ 的最小质因子，则 $a=g,b=r-g$。

时间复杂度 $O(T\sqrt n)$。
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007
#define inf 1e9

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 1e7 + 10;

int T, l, r, p[N], len, prime[N], tot, st[N];

vector<int> v[N];

void init() {
  for (int i = 2; i <= 1e7; i++) {
    if(!st[i]) prime[++tot] = i;
    for (int j = 1; j <= tot; j++) {
      if(i * prime[j] > 1e7) break;
      st[i * prime[j]] = 1;
      if(i % prime[j] == 0) break;
    }
  }
}

void solve() {
  read(l, r);
  if(r & 1) r--;
  if(r < l) {
    r++;
    len = 0;
    if(!st[r]) {
      puts("-1");
      return ;
    }
    For(i,2,sqrt(r)) {
      if(st[i]) continue;
      if(r % i == 0) {
        cout << i << ' ' << r - i << '\n';
        return ;
      } 
    }
    return ;
  }
  if(r / 2 == 1) {
    puts("-1"); return ;
  }
  cout << r / 2 << ' ' << r / 2 << '\n'; 
}

signed main() {
  read(T);
  init();
  while(T--) {
    solve();
  }
  return 0;
}
```

---

## 作者：wanghaoran00 (赞：0)

### 题意
给定 $l,r$，构造 $a+b∈[l,r]$ 且 $a,b$ 不互质。 

### 思路
易知 $\gcd(a,a)=a$，若 $l,r$ 及 $l,r$ 之间存在除了 $2$ 的偶数，将其中一个偶数除2即可，获得两个相等的数一定不互质，其他情况输出 $-1$。

AC code
```
using namespace std;
bool isPrime[100000010];
int Prime[6000010], cnt = 0;
void GetPrime(int n){
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[1] = 0;
	for(int i = 2; i <= n; i++){
		if(isPrime[i])
			Prime[++cnt] = i;
		for(int j = 1; j <= cnt && i*Prime[j] <= n; j++) {
			isPrime[i*Prime[j]] = 0;
			if(i % Prime[j] == 0)
				break;
		}
	}
}
int t,l,r;
int main(){
	GetPrime(10000000);
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&l,&r);
		if(l==r){
			if(l==1){//1既不是质数也不是合数
				printf("-1\n");
			}
			for(int i=1;i<=r;i++){
				if(r%Prime[i]==0){
					if(r==Prime[i]){//r本身是质数
						printf("-1\n");
						break;
					}
					else{
						printf("%d %d\n",r-Prime[i],Prime[i]);
						break;
					}
				}
			}
		}
		else{
			if(r>=4){
				if(r%2==0){
					printf("%d %d\n",r/2,r/2);
				}
				else{
					printf("%d %d\n",(r-1)/2,(r-1)/2);
				}
			}
			else{
				printf("-1\n");
			}
		}
		
	}
	return 0;
}
```

---

