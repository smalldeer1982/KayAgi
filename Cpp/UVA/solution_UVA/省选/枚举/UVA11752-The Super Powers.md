# The Super Powers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2852

[PDF](https://uva.onlinejudge.org/external/117/p11752.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/caccb369bd9149203faf09eaf595e5873b362929.png)

## 样例 #1

### 输入

```
```

### 输出

```
1
16
64
81
256
512
.
.
.```

# 题解

## 作者：fish_love_cat (赞：3)

题意翻译：

求所有满足 $1\le k \le 2^{64}-1$ 且可同时表示为 $k=a^b=c^d,b\ne d$ 的 $k$。

---

推式子。

$$a^b=c^d$$

$$(x^n)^b=(x^m)^d$$

$$x^{nb}=x^{md}$$

$$nb=md$$

---

于是发现合法情况当且仅当 $k=a^b$ 且 $b$ 是合数。

写个筛子把合数筛出来，然后一个一个去代即可。

时间复杂度 $O(a\log a+ab)$。

由于 $4\le b \le 64$，所以 $a\le n^{\frac{1}{4}}$。

这样要跑的范围就很小了，能过，同时你也可以加一个超出最大值的剪枝。

不用高精，使用 `__int128` 即可。

代码实现不放了。

---

## 作者：Milthm (赞：2)

题目很简单，就是让你求满足 $k=a^b$ 且 $k=c^d$，且 $a \neq b,c \neq d$ 的所有的 $k$。

容易发现如果 $k=x^m$，则 $m$ 一定是合数，因为若 $m=a\times b$，则 $k=(x^a)^b$ 且 $k=(x^b)^a$。

所以我们想到筛合数枚举，但这样不会超时吗？答案是不会，因为合数最小是 $4$，只需要枚举 $\sqrt[4]{2^{64}}=2^{16}$ 个数，不会超时。

注意计算的时候会爆掉 `unsigned long long`，需要开 `__int128`。算完了之后要排序并**去重**。

### AC code

```cpp
#include<iostream>
#include<algorithm>
#define int unsigned long long
using namespace std;
int p[10005],a[10005],t,cnt,ans[1000005]; 
signed main(){
	for(int i=2;i<=100;i++){
		if(a[i]==0)p[++t]=i;
		for(int j=1;j<=t&&p[j]*i<=100;j++){
			a[p[j]*i]=1;
			if(i%p[j]==0)break;
		} 
	}
	for(int i=2;i<=65537;++i){
		__int128 qwq=i;
		for(int j=2;j<=100;++j){
			qwq*=i;
			if(qwq>=((__int128)1)<<64)break;
			if(a[j])ans[++cnt]=qwq;
		}
	}
	sort(ans+1,ans+cnt+1);
	cout<<"1\n";
	for(int i=1;i<=cnt;++i){
		if(ans[i]!=ans[i-1])cout<<ans[i]<<'\n';
	}
	return 0;
}

```




---

## 作者：Jadonyzx (赞：1)

若 $k$ 满足条件，则有：

$k=x_1^{y_1}=x_2^{y_2}$

$x_1\ne x_2$

$y_1\ne y_2$

显然当且仅当 $k=x^y$ 且 $y$ 为合数时一定可行。

线性筛合数后枚举，去重即可。

高精度？

```cpp
unsigned __int128
//just do it.
```


code：


```cpp
#include<bits/stdc++.h>
#define int unsigned __int128
using namespace std;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x;
}
inline void write(int x){
	if(x>=10)write(x/10);
	putchar(x%10+'0');
	return;
}
int ans[100000000],anscnt;
bool isp[114];
int prime[114],prcnt;
int czr=1;
signed main(){
	memset(isp,1,sizeof isp);
	czr<<=64;
	for(int i=2;i<114;++i){
		if(isp[i])prime[++prcnt]=i;
		for(int j=1;j<=prcnt&&i*prime[j]<114;++j){
			isp[i*prime[j]]=0;
			if(i%prime[j]==0)break;
		}
	}
	for(int i=2;i<=114514;++i){
		int base=i;
		for(int j=2;j<114;++j){
			base*=i;
			if(base>=czr)break;
			if(!isp[j])ans[++anscnt]=base;
		}
	}
	ans[++anscnt]=1;
	sort(ans+1,ans+1+anscnt);
	for(int i=1;i<=anscnt;++i)if(ans[i]!=ans[i-1])write(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

# 分析

首先找出写一个暴力判素的函数，用于求64以内的合数，因为合数可以唯一分解，而$k^{nm}=(k^n)^m=(k^m)^n$，这样的就可以满足条件了。

具体来说就是枚举$i\in [2,(2^{64})^{\frac{1}{4}}]$，然后枚举指数$j\in[2,64]$，记录答案为$i^j$，如果那个玩意大于$2^{64}-1$，就可以`break`了，如果那个玩意的$j$是合数且小于$2^{64}-1$，就扔进一个set维护就行了。

但是那个$i^j$可能会爆$unsigned\ long\ long $，所以可以求对数，或者干脆用g++自带的int128，要不写高精233。

# 代码

```cpp
#include<cstdio>
#include<set>
typedef unsigned long long uint64;
typedef __int128 int128;
const uint64 MAX = 65536;
const uint64 INF = -1;
bool hash[MAX + 666];
std::set<uint64> ans;

int128 pow(int k,int p){
    int128 ans = 1;
    for(int i = 1;i <= p;i++) ans *= k;
    return ans;
}

bool isPrime(int n){
    if(n == 0 || n == 1) return false;
    for(int i = 2;i * i <= n;i++) if(n % i == 0) return false;
    return true;
}

int main(){
    //freopen("666.txt","w",stdout);
    int128 delta;
    for(int i = 2;i < MAX;i++){
        if(hash[i]) continue;
        for(int j = 2;j < 64;j++){
            delta = pow(i,j);
            if(delta < MAX) hash[delta] = true;
            if(delta > INF) break;
            if(!isPrime(j)) ans.insert((uint64)pow(i,j));
        }
    }
    ans.insert(1);
    for(std::set<uint64>::iterator it = ans.begin();it != ans.end();it++) printf("%llu\n",*it);

    return 0;
}
```



---

## 作者：dingshengyang (赞：0)

最优解前来水题解。

---

Part 1：它是「The Super Power」吗？

设 $x$ 为要验证的数，如果它是 「The Super Power」，一定可以被整数 $y,z$ 表述出来：$x=y^z$。



然并卵。


（上面的 $x$ 已经失效了）

如果 $a^b$ 是「The Super Power」，这个数一定可以表述为 $(a^x)^y=(a^y)^x$（当然，$x\times y=b$）

* **「The Super Power」必然是某一个数的合数次方！**

1. 合数，显然，欧拉筛一下就好了（甩掉楼上暴力判素）。

1. 合数最小是 $4$，那么前面的「某一个数」一定小于 $2^{16}$，因为 $(2^{16})^4=2^{64}$。

1. 算幂的时候，`unsigned long long` 极有可能溢出，可以使用 `__int_128_t`。在发现超过 `unsigned long long` 上界时，及时退出。

1. 需要注意的是，最后要去重,先 `sort`,再 `unique`。（上 `vector<int>`）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 65536+1;
__int128_t MAXULL = 1;
int st[N+50];
int primes[100005];
int cnt;
void init(){
	st[0] = st[1] = 1;
	for(int i = 0;i < 64;i ++)MAXULL <<= 1;
	MAXULL --; 
	for(int i = 2;i <= N;i ++){
		if(!st[i])primes[cnt++] = i;
		for(int j = 0;primes[j]<=N/i;j ++){
			st[primes[j]*i] = 1;
			if(i%primes[j] == 0)break;
		}
	}
}
int main(){
	init();
	vector<__int128_t> vec;
	vec.push_back(1);
	for(int i = 1;i < 65536;i ++){
		__int128_t t = i;
		__int128_t tmp =t*t*t*t;
		for(int j = 4;j <= 64;j ++){
			if(tmp > MAXULL)break;
			if(st[j]){
				vec.push_back(tmp);
			}
			tmp *= t;
		}	
	}
	sort(vec.begin(),vec.end());
	int m = unique(vec.begin(),vec.end())-vec.begin();
	for(int i = 0;i < m;i ++){
		printf("%llu\n",(unsigned long long)vec[i]);
	}
	return 0;//200
}
```

---

## 作者：MC小萌新 (赞：0)

枚举 $k^m$，使得 $m$ 为合数。则所有这样的数即为答案。

证明：设 $m=a×b$，则 $k^m=k^a×k^b=(k^a)^b=(k^b)^a$。所以只需要找出这样的数就可以了。

考虑两层循环。第一层枚举 $k$，$k^m$ 最大到 $2^{64}-1$，而 $m$ 为合数，最小值为 $4$，所以只需要将 $k$ 枚举到 $2^{16}$ 就可以了。第二层循环枚举 $m$，注意不能用 $k^m<2^{64}-1$ 来判断循环结束条件，因为会爆 ```unsigned long long```。这里可以考虑取 $log_k{(2^{64}-1)}$ 与 $m$ 进行比较。每次循环时判断当前的 $m$ 是否为合数。如果是直接加入答案序列。

答案序列使用优先队列保证顺序。

输出时注意判重。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long 
const ull INF=18446744073709551615,MAXN=65536;
ull now;
double qwq=log(INF);
priority_queue<ull,vector<ull>,greater<ull> > ans;
ull qp(ull a,ull b){
	if(b==1)
		return a;
	ull qwq=qp(a,b/2);
	if(b%2)
		return a*qwq*qwq;
	return qwq*qwq;
}
bool OK(ull a){
	for(ull i=2;i*i<=a;++i)
		if(a%i==0)
			return 1;
	return 0;
}
int main(){
	ans.push(1);
    for(ull i=2;i<MAXN;++i){
    	ull t=qwq/log(i);
       for(ull j=4;j<=t;++j)
       		if(OK(j))
       			ans.push(qp(i,j));
    }
    while(!ans.empty()){
    	if(now!=ans.top())
    		cout<<ans.top()<<endl;
    	now=ans.top();
		ans.pop();
	}
    return 0;
}
```


---

