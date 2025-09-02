# [RC-02] yltx 数对

## 题目背景

yltx 又双叒叕出自己不会做的题了……

## 题目描述

yltx 定义若一个**素数**数对 $(x,y)$ 满足 $x\times y-3\times (x-y)$ 是素数，则称其为一个 yltx 数对。

他给了你 $T$ 对 $(x,y)$，请你检查他们是否为 yltx 数对。

数据以种子$(x_0,y_0)$的形式给出。

执行 $T$ 次 $x_0\leftarrow (7x_0+13)\ \mathrm{xor}\ (x_0\div 13-7)$，第 $i$ 次执行得到的数先取模 $10^4$、加上 $10^4$、取模 $10^4$，再加 $1$，就得到了第 $i$ 组数据的 $x$。这里的除法就是整除，把 $x_0$ 视作 32 位有符号整数。

用同样的方法得到 $y$。

数据生成模板：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,x_0,y_0;
int main() {
	scanf("%d%d%d",&T,&x_0,&y_0);
	while(T--){
		x_0=((7*x_0+13)^(x_0/13-7));
		y_0=((7*y_0+13)^(y_0/13-7));
		int x=(x_0%10000+10000)%10000+1,y=(y_0%10000+10000)%10000+1;
		//x,y即为一组(x,y)。
	}
	return 0;
}
```

## 说明/提示

各测试点数据范围如下：

| 测试点 | T | Subtask |
| :---: | :---: | :---: |
| 1 | $\le10$ | 1 |
| 2 | $\le20$ | 1 |
| 3 | $\le50$ | 1 |
| 4 | $\le100$ | 1 |
| 5 | $\le500$ | 1 |
| 6 | $\le1000$ | 1 |
| 7 | $\le5000$ | 2 |
| 8 | $\le10^4$ | 2 |
| 9 | $\le5\times10^4$ | 2 |
| 10 | $\le4\times10^5$ | 2 |
| 11 | $\le10^6$ | 2 |
| 12 | $\le5\times10^6$ | 2 |
| 13 | $\le4\times10^7$ | 3 |
| 14 | $\le4\times10^7$ | 3 |
| 15 | $\le4\times10^7$ | 3 |
| 16 | $\le4\times10^7$ | 3 |
| 17 | $\le4\times10^7$ | 3 |
| 18 | $\le4\times10^7$ | 3 |
| 19 | $\le4\times10^7$ | 3 |
| 20 | $\le4\times10^7$ | 3 |

各Subtask捆绑测试。

本题开放数据下载，但希望您能用数据做正确的事。

## 样例 #1

### 输入

```
100000 1 2```

### 输出

```
321```

# 题解

## 作者：feecle6418 (赞：4)

### Update on 2020.5.11

bitset 优化筛法。

首先 $10^7$ 组询问，肯定要预处理出范围内的所有素数然后 $O(1)$ 判断。

线性筛会爆空间（似乎也能过？），只能用埃氏筛。

先筛掉 $2,3$ 的倍数，然后在 $6$ 个里面只用筛 $2$ 个：$i(6i+1)$，$i(6i+5)$。

用 bitset 压一下位就行了。注意不需要筛偶数，可大大减少时间和空间。

std：

```
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
int k=1,s[10005],prime[10005];
bitset<50110005>vst;
inline bool Prime(register int n){
	return n<2?0:(n==2?1:(n%2&&!vst[n>>1]));
}
int main() {
//	freopen("5.in","r",stdin);
//	freopen("5.out","w",stdout);
	for(int i=9; i<=100030000; i+=6)vst[i>>1]=1;
	for(int i=15; i<=100030000; i+=10)vst[i>>1]=1;
	for(register int i=7; i<=20000; i+=2){
		if(vst[i>>1])continue;
		for(register int j=i*(i/6*6+1); j<=100030000; j+=i*6){
			vst[j>>1]=1;
            vst[(j>>1)+(i<<1)]=1;
		}
	}
	int T,x0,y0,s=0;
	scanf("%d%d%d",&T,&x0,&y0);
	while(T--){
		x0=((7*x0+13)^(x0/13-7));
		y0=((7*y0+13)^(y0/13-7));
		int x=(x0%10000+10000)%10000+1,y=(y0%10000+10000)%10000+1;
		if(Prime(x)&&Prime(y)&&Prime(x*y-3*(x-y)))s++;
	}
	cout<<s;
	return 0;
}
```

---

## 作者：CloudyKai (赞：3)

第一次拿最优解，思路比较清奇。

首先根据题意，$x$ 和 $y$ 都是 $[1,10000]$ 以内的质数，打表发现大约有不到 $1300$ 个数。

因此可能合法的数对个数有大约 $2\times 10^6$ 个。设 $z=x\cdot y-3(x-y)$，则只需要对这么多可能出现的 $z$ 判断是否为质数即可。

判断是否为质数时，直接使用 $O(\sqrt{z})$ 的朴素算法，用求得的 $[1,10000]$ 中的 $1300$ 个质数去检验一遍。由于只有 $2\times 10^6$ 个数对，我们可以将结果记忆化。

设值域内的质数个数为 $cntp$，则理论时间复杂度为 $O(cntp^3)$，在本题中为 $10^9$ 级别的；空间复杂度为 $O(cntp^2)$。

而实际上，由于输入数据随机，需要检验的 $(x,y)$ 对数并没有跑满；并且 $x$ 和 $y$ 的期望值较小，相乘得到的 $z$ 也会较小，检验素数很快。

最终以 237ms 的速度通过了本题。

水一篇代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 10004, NN = 1300;
int T;
int x_0, y_0;
int np[N], id[N], p[N], cnt;
bool ck[NN][NN], res[NN][NN];

int main()
{
	np[1] = 1;
	for (int i = 2; i < N; i++)
	{
		if (!np[i])
		{
			p[++cnt] = i;
			id[i] = cnt;
		}
		int k;
		for (int j = 1; j <= cnt; j++)
		{
			if ((k = p[j] * i) >= N) break;
			np[k] = 1;
			if (i % p[j] == 0) break;
		}
	}
	int ans = 0;
	scanf("%d%d%d",&T,&x_0,&y_0);
	while (T--)
	{
		x_0=((7*x_0+13)^(x_0/13-7));
		y_0=((7*y_0+13)^(y_0/13-7));
		int x=(x_0%10000+10000)%10000+1,y=(y_0%10000+10000)%10000+1;
		if (!np[x] && !np[y])
		{
			int xx = id[x], yy = id[y];
			int z = x * y - 3 * (x - y);
			if (z <= 1) continue;
			if (!ck[xx][yy])
			{
				ck[xx][yy] = res[xx][yy] = true;
				for (int i = 1; i <= cnt && p[i] * p[i] <= z; i++)
				{
					if (z % p[i] == 0)
					{
						res[xx][yy] = false;
						break;
					}
				}
			}
			if (res[xx][yy]) ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：greater_than (赞：0)

## 题目大意

>给你 $ T $ 组对 $ ( x , y ) $，求满足 $ x , y , x \times y − 3 \times ( x − y ) $ 都是质数的有多少对。


## 思路

>由于 $ T $ 有那么亿点点大，也只有 $ 4 \times 10^7 $ 而已。so，线性筛可能会爆空间，所以考虑预处理，程序每一次开始先计算出最大的 $ x \times y $ 即 $ 10^8 $ 以内的所有素数，然后对于每次询问 $ O(1) $ 解决即可。

### 注意：

因为 $ 6i + 2 , 6i + 4 , 6i $ 都是 $ 2 $ 的倍数，且 $ 6i + 3 $ 是三的倍数，所以在 $ 1 \le i $ 的时候，质数只有可能是 $ 6i + 1 $ 和 $ 6i + 5 $ 两种可能，可以以此加速。

[提交记录](https://www.luogu.com.cn/record/174062869)

要压位！！！

[AC Link](https://www.luogu.com.cn/record/196743274)

---

## 作者：aCssen (赞：0)

### Solution
提供一种乱搞做法。

首先注意到，给出的 $x,y$ 都不超过 $10^4$，然后合法的条件要求 $x,y$ 均为质数，那么我们可以先判掉 $x$ 或 $y$ 不为质数的情况，在本题的生成器下，经测试，剩下的 $(x,y)$ 约为 $10^5$ 级别。

那就可以乱做了，首先令 $V$ 为剩下的 $x \times y-3(x-y)$ 的最大值。若 $V\le 2 \times 10^7$ 可以乱做，否则使用费马小定理反过来判断即可。

注意这并不是充分条件，所以要多选几个来判，代码中进行了 $10$ 次判断。

有个小东西，要将剩下的数用 `map` 记录个数，再排序，去重，不然好像最后那个包一个点都过不去。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e7+5;
bitset<maxn>vis;
void prime(int n){
	vis[1]=true;
	for(int i=2;i<=n;i++){
		if(vis[i]) continue;
		for(int j=i;j<=n/i;j++)
			vis[i*j]=true;
	}
}
ll power(ll a,int b,int p){
	ll ans=1;
	for(;b;b>>=1){
		if(b&1) ans=(ans*a)%p;
		a=(a*a)%p;
	}
	return ans;
}
int random(int N){
	return 1ll*rand()*rand()%N+1;
}
bool isprime(int n){
   	if(n<=1) return false;
	if(n<=100) return !vis[n];
	for(int i=2;i<=100;i++)
		if(n%i==0) return false;
    for(int i=1;i<=10;i++){
        int a=random(n-2)+1;
        ll val=power(a,n-1,n);
        if(val!=1) return false;
    }
    return true;
}
bool check(int x){
	if(x<=1) return false;
	if(x==2||x==3) return true;
	if(x%2==0||x%3==0) return false;
	return !vis[x];
}
int T,x_0,y_0,ans;
vector<int>v;
map<int,int>cnt;
int main(){
	srand(time(NULL));
	scanf("%d%d%d",&T,&x_0,&y_0);
	prime(1e4);
	while(T--){
		x_0=((7*x_0+13)^(x_0/13-7));
		y_0=((7*y_0+13)^(y_0/13-7));
		int x=(x_0%10000+10000)%10000+1,y=(y_0%10000+10000)%10000+1;
		if(check(x)&&check(y)) v.push_back(x*y-3*(x-y));
	}
	int Max=0;
	for(auto x:v) Max=max(Max,x);
	if(Max<=20000000){
		prime(Max);
		for(auto x:v) if(x>1&&x%2!=0) ans+=(!vis[x]);
		printf("%d",ans);
		return 0;
	}
	for(auto x:v) cnt[x]++;
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(auto x:v) if(isprime(x)) ans+=cnt[x];
	printf("%d",ans);
	return 0;
}
```

---

## 作者：lemondinosaur (赞：0)

这里给出一个 Miller-Rabin 的做法，但是直接套模板会TLE，

考虑搭配线性筛，小范围用线性筛筛出的质数，这道题虽然比较裸，

但是里面的坑点特别多：

> 素数数对 $(x,y)$ 满足 $x\times y-3\times (x-y)$ 是素数

 $x,y$ 和 $x\times y-3\times (x-y)$ 都必须是素数，
 
 所以为了避免三倍的常数导致TLE，那么应该采用预处理小范围的方式；
 
 而且这上面的所有数必须是大于1的正数，所以负数还要特判。
 
 注意单纯的线性筛可能会MLE，所以数组不要开太大。
 
---
# 代码
```cpp
#include <cstdio>
#include <cctype>
#define rr register
using namespace std;
typedef long long lll; int ans,T,x0,y0;
const int P[4]={2,3,5,7},M=1000011;
bool v[M]; int prime[M],Cnt;
inline signed iut(){
	rr int ans=0; rr char c=getchar();
	while (!isdigit(c)) c=getchar();
	while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans;
}
inline signed ksm(int x,int y,int mod){
	rr int ans=1;
	for (;y;y>>=1,x=(lll)x*x%mod)
	    if (y&1) ans=(lll)ans*x%mod;
	return ans;
}
inline void Pro(){
	v[1]=1;
	for (rr int i=2;i<M;++i){
		if (!v[i]) prime[++Cnt]=i;
		for (rr int j=1;j<=Cnt&&prime[j]*i<M;++j){
			v[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
}
inline bool mr(int n){
	if (n<2) return 0;
    if (n==2||n==3||n==5||n==7) return 1;
    if (!(n&1)||!(n%3)||!(n%5)||!(n%7)) return 0;
    rr lll m=n-1; rr int Cnt=0;
    while (!(m&1)) m>>=1,++Cnt;
	for (rr int i=0;i<4&&P[i]<n;++i){
		rr int now=ksm(P[i],m,n),last=now;
		for (rr int j=1;j<=Cnt;++j){
			now=(lll)now*now%n;
			if (now==1&&last!=1&&last!=n-1) return 0;
			last=now;
		}
		if (now!=1) return 0;
	} 
	return 1;
}
signed main(){
	scanf("%d%d%d",&T,&x0,&y0),Pro();
	while(T--){
		x0=((7*x0+13)^(x0/13-7)),y0=((7*y0+13)^(y0/13-7));
		rr int x=(x0%10000+10000)%10000+1,y=(y0%10000+10000)%10000+1;
		if (v[x]||v[y]) continue;
		rr int now=x*y-3*(x-y);
		if (now<2) continue;
		if (now<M&&v[now]) continue;
		if (now>=M) ans+=mr(now);
		    else ++ans;
	}
	return !printf("%d",ans);
} 
```

---

