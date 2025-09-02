# Banknotes

## 题目描述

### 题意简述

有 $n$ 中面额的钞票，第 $i$ 种钞票面额为 $10^{a_i}$ 勃朗。（保证 $a_1=0$）

定义 $f(s)$ 为组成 $s$ 勃朗最少需要多少张钞票。

给定 $k$，问使得 $f(s)>k$ 的最小 $s$ 是多少。

## 样例 #1

### 输入

```
4
3 13
0 1 2
2 777
0 4
3 255
0 1 3
10 1000000000
0 1 2 3 4 5 6 7 8 9```

### 输出

```
59
778
148999
999999920999999999```

# 题解

## 作者：Cht_master (赞：4)

- 题意简述：有 $n$ 种面额的钞票，第 $i$ 种钞票面额为 $10^{a_i}$ 勃朗。定义 $f(s)$ 为组成 $s$ 勃朗最少需要多少张钞票。给定 $k$，问使得 $f(s)>k$ 的最小 $s$ 是多少。多组数据，$1\leq t\leq 10^4$，$1\leq n\leq 10$，$1\leq k\leq 10^9$，$a_1=0,\forall i\in(1,n],a(i-1)<a(i),a_n\leq 9$。 

- 题目简析： 

  - 性质 $\texttt1$：对于形如 $10^c-1$ 的数，恒有：若 $c_1>c_2$，则 $f(10^{c_1}-1)>f(10^{c_2}-1)$，易证。
    - 例如对于 $9999$ 和 $99$，有 $9999>99$，则 $f(9999)>f(99)$。
  - 性质 $\texttt2$：对于位数确定的不含前导 $0$ 的数 $x$，它从高到低的每一位越小，则 $f(x)$ 越小。
    - 例如对于 $22345$ 和 $21345$，有 $f(22345)>f(21345)$。
    - 简单证明：
      1. 若有 $10^4$ 这种面值，那么显然 $f(22345)>f(21345)$;
      2. 若没有 $10^4$ 这种面值，则需要更多的 $10^c,c<4$ 的面值的钞票，故仍有 $f(22345)>f(21345)$。
  - 根据性质 $\texttt 1$，考虑枚举或二分满足 $f(x)>k,x=10^c-1$ 的最小的 $x$。
  - 根据性质 $\texttt 2$，把 $x$ 从高到低逐位尽量的减少；这是因为要求最小的 $x$，所以显然高位越小越好（这里也可以二分）。
    - 例如对于样例 `2 777 0 4`，首先根据性质 $\texttt 1$ 求得 $x=999$；然后将 $x$ 最高位依次减少，得到 $x=799$；继续将次高位减小，得到 $x=779$；最后减小个位，得到 $x=778$。
  - 单次询问复杂度 $O(\lg^3ans)$ ，用上二分可能快一点。

- ```cpp
  #include<bits/stdc++.h>
  #define ll long long
  using namespace std;
  const int mxN(20);
  int n,a[mxN+5];ll K,p[mxN+5];
  int dig[mxN+5],tdig[mxN+5];
  ll Qpow(ll x){ll s(1);while(x--)s*=10;return s;}
  ll f(ll x){
  	ll s(0);
  	for(int i(n);i>=1;--i){
  		s+=(x/p[i]),x-=(x/p[i])*p[i];
  		if(!x)return s;
  	}
  	return s;
  }
  int main(){
  	int T;scanf("%d",&T);
  	while(T--){
  		scanf("%d%lld",&n,&K);
  		for(int i(1);i<=n;++i)scanf("%d",&a[i]),p[i]=Qpow(a[i]);
  		ll ans(0),digs(0),t;
  		while(f(ans)<=K)ans=ans*10+9;
  		t=ans;while(t)dig[++digs]=t%10,t/=10;
  		for(int i(1);i<=digs;++i){
  			for(int j(dig[i]);j>=0;--j){
  				for(int k(1);k<=digs;++k)tdig[k]=dig[k];
  				tdig[i]=j,t=0;
  				for(int k(1);k<=digs;++k)t=t*10+tdig[k];
  				if(f(t)<=K){tdig[i]=j+1;break;}
  			}
  			for(int j(1);j<=digs;++j)dig[j]=tdig[j];
  		}
  		for(int i(1);i<=digs;++i)printf("%d",dig[i]);putchar('\n');
  	}
  	return 0;
  }
  ```

  

---

## 作者：漠寒 (赞：2)

## 分析

因为每一个面额都是前面面额的整数倍，所以最终得到的答案减一的合成方案里每一张钞票的张数，一定没有达到后一种面额和该种面额的比值，否则就能用更少的张数来替换，例如现在有 $1$ 和 $10$,你 $1$ 最多用 $9$ 张，要不然只用一张 $10$ 就替代了，所以从小到大考虑每一张钞票在答案中的张数，就是后一种面额除以该种面额的值减一，将这些求和，张数不足时便停止，若还有剩余，全加给最后一种。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline void read(int &res){
	char c;
	int f=1;
	res=0;
	c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
int T;
int n,k;
int a[15];
int cf[15];
signed main()
{
	read(T);
	cf[0]=1;
	for(int i=1;i<=10;i++)cf[i]=cf[i-1]*10;
	while(T--){//代码中求的是答案减一，所以最后要加一
		read(n);read(k);
		for(int i=1;i<=n;i++)read(a[i]);
		int ans=0,sum=0,cnt;
		cnt=cf[a[2]-a[1]]-2;
		if(cnt>k){
			printf("%lld\n",k+1);
			continue;
		}
		else ans=cnt,sum=cnt;
		for(int i=2;i<n;i++){
			cnt=cf[a[i+1]-a[i]]-1;
			if(cnt+sum>k){
				ans+=(k-sum)*cf[a[i]];
				sum=k;
			}
			else {
				ans+=cnt*cf[a[i]];
				sum+=cnt;
			}
		}
		if(sum<k)ans+=(k-sum)*cf[a[n]];
		printf("%lld\n",ans+1);
	}
	return 0;
}


```


---

## 作者：vvauted (赞：2)

## Description

有 $n$ 种面值的货币，第 $i$ 种的面值为 $10^{a_i}$，求用 $k$ 种货币不能凑出的最小价值

## Solution

显然，第 $i(i<n)$ 种只能选 $10^{a_{i+1}-a_i}-1(i<n)$ 个，如果多选则可以用第 $i+1$ 张代替，特别的，第 $n$ 张可以无限选。

我们尽量把面值较小的选完即可

## Code 

```cpp
#include <stdio.h>
#define ll long long
 
ll n, k, a[11], d[11];
ll pow[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 1000000000};//打个猥琐的表
 
int main() {
	int T, w, n, k;
	scanf("%d", &T);
	while(T --) {
		scanf("%d%d", &n, &k); w = 1; ll ans = 0; ++ k; // k 张最小选不出来的就是 k+1 张选出来最小的
		for(int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
		for(int i = 1; i < n; ++ i) d[i] = a[i + 1] - a[i], d[i] = pow[d[i]] - 1;//预处理选择数
		while(k && w < n) { // 第 n 个没有限制，单独算
			if(d[w] <= k) ans += d[w] * pow[a[w]], k -= d[w];
			else ans += k * pow[a[w]], k = 0;
			w ++; 
		} if(k) ans += k * pow[a[n]];//如果要选第 n 张，加上
		printf("%lld\n", ans);
	}
}

```


---

## 作者：XL4453 (赞：1)

### 解题思路：

考虑贪心。

优先使用小的币值去构造价值，如果能放就尽量在每一位上放 $9$，否则按照剩下的需要纸币数量去构造。

这个贪心的证明是比较显然的，如果在允许的条件下，把一个小的币值换成大的币值只能使得在价值不变的前提下增加代价。

本题的特殊性在于每一个币值都是 $10^n$ 的形式，这个特殊性使得其与其他的币值表示相比相对简单。

---
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,k,a[105],now,ans[105],cnt,len;
int main(){
	scanf("%lld",&T);
	while(T--){
		memset(a,0,sizeof(a));
		memset(ans,0,sizeof(ans));
		now=cnt=len=0;
		
		scanf("%lld%lld",&n,&k);
		
		for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
		
		for(int i=1;i<=n;i++){
			if(pow(10,(a[i]-a[i-1]))-1+now<=k){
				now+=pow(10,a[i]-a[i-1])-1;
				for(int j=a[i-1];j<=a[i]-1;j++)
				ans[j]=9;
			}
			else{
				cnt=k-now+1;
				if(cnt*pow(10,a[i-1])>=pow(10,a[i]))continue;
				now=k+1;
				len=a[i-1];
				while(cnt){
					ans[len]=cnt%10;
					cnt/=10;
					len++;
				}
			}
		}
		cnt=k-now+1;
		len=a[n];
		while(cnt){
			ans[len]=cnt%10;
			cnt/=10;
			len++;
		}
		for(int i=100;i>=0;i--)
		if(ans[i]!=0){
			len=i;
			break;
		}
		for(int i=len;i>=0;i--){
			printf("%d",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：智子 (赞：1)

## 题意

给出 $n$ 种面值为 $10^{a_i}$ 的纸币，求最少的金额使其无法用 $k$ 张纸币表示出来。

## 思路

可以转换为找到最小的必须用 $k + 1$ 种纸币表示出的金额，定义 $s = k + 1$。对于第 $i$ 种纸币，令 $s$ 减去 $10^{a_{i + 1} - a_i} - 1$，如果不能减去或者已经到了面值最大的纸币，就直接输出当前的数，并在后面用 $a_i$ 个 $9$ 填充。

## 代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN = 10;
const int base[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int a[MAXN], ans[MAXN];

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        int n, k;

        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        int s = k + 1, p = n;
        for(int i = 1; i <= n; i++) {
            if(i == n) {
                ans[i] = s;
                break;
            }
            if(s > base[a[i + 1] - a[i]] - 1) {
                ans[i] = base[a[i + 1] - a[i]] - 1;
                s -= base[a[i + 1] - a[i]] - 1;
            } else {
                ans[i] = s;
                p = i;
                break;
            }
        }
        printf("%d", ans[p]);
        for(int i = 1; i <= a[p]; i++) {
            printf("9");
        }
        printf("\n");
    }

    return 0;
}
```

---

## 作者：fls233666 (赞：0)

既然要让使用的钞票数量大于 $k$，我们可以先找到使用钞票数量为 $k$ 的**最大的**金额 $s$，在 $s$ 的基础上增加一张钞票得到答案。

如何凑出这个 $s$？考虑**贪心**。从小面值到大面值依次尽可能使用钞票。对于第 $i$ 种钞票，它能使用的最多次数就是 $\frac{10^{a_{i+1}}-10^{a_i}}{10^{a_i}}$。计算出最多的使用次数后与 $k$ 比较，在 $k$ 中扣去相应的数值。如果能使用的最大次数比 $k$ 大，则只使用 $k+1$ 次，并在这之后结束循环。如果把前 $n-1$ 种钞票都用完后，如果还存在 $k \ge 0$，则直接把最大面值的第 $n$ 种钞票使用 $k+1$ 次即可。

最后就是主要一些实现时的细节问题即可。下面放上代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

int n,na[12];
ll ans,w[12],nk,cnt;

int main(){
  
	w[0]=1;
	for(rgt i=1;i<=10;i++)
		w[i]=w[i-1]*10;  //预处理钞票面值
                          
	int test;
	scanf("%d",&test);
	while(test--){
		ans=0;
		scanf("%d%lld",&n,&nk);
		for(rgt i=1;i<=n;i++)
			scanf("%d",&na[i]);
  
		for(rgt i=1;i<n&&nk>=0;i++){
			cnt=(w[na[i+1]]-w[na[i]])/w[na[i]]; //计算当前钞票最多能使用几次
			if(cnt>nk)
				cnt=nk+1;
			ans+=cnt*w[na[i]];  //计算最终面值
			nk-=cnt;  //扣除相应的使用次数
		}
  
		if(nk>=0)
			ans+=(nk+1)*w[na[n]];  //剩下的使用次数用最大面值的钞票补完
  
		printf("%lld\n",ans);
	}
	return 0;
}

/*
1
5 10008
0 4 5 6 8
*/
```


---

