# Mixing Invitations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2257

[PDF](https://uva.onlinejudge.org/external/112/p11282.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11282/110870a90869e55e6ec3515fe755ec5b158955d7.png)

## 样例 #1

### 输入

```
3 2
4 1
4 4```

### 输出

```
5
17
24```

# 题解

## 作者：云雷心柠檬听 (赞：1)

## [博客食用更佳](https://www.cnblogs.com/lemon-cyy/p/17830206.html)

### 题意简述
Kelly 寄出去 $n$ 封邀请函，但她希望只有小于等于 $m$ 个人收到他们自己的邀请函（即有至少 $n-m$ 个人收到了别人的邀请函）。

### 思路形成
容易发现，这道题是一个典型的错排题，我们只需要分别求出 $n-m$ 个元素到 $n$ 个元素的错排即可。

接下来为错排的推导，我们令 $f[x]$ 表示 $x$ 个元素的错排。

这时候第 $x$ 号元素不能在第 $x$ 个位置上，它排在了另一个位置上，令这个位置为 $y$，则 第 $y$ 号元素出现了两种可能性。
1. $y$ 号元素恰好排在了第 $x$ 个位置上，此时相当于剩下的元素错排的情况，共 $f[x-2]$ 种。
2. $y$ 号元素并没有排在第 $x$ 个位置上，此时如果我们把 $y$ 就看作 $x$，这个问题就变成了除了 $x$ 以外所有元素的错排，共 $f[n-1]$ 种

由于 $y$ 号元素的选取共有 $x-1$ 种，可以得到最后的递推公式。
$$
f[x]=(x-1)\times(f[x-1]+f[x-2])
$$

### 代码细节
由于每一个人都是不一样的，因此计算答案时还要乘上选出人的方案数，即当有 $a$ 个人没有收到自己的邀请函时，答案应该为 $C^{a}_{n} \times f[a]$。

### AC 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=29;
ll C[N][N],cuo[N];
ll n,m;

void init(){
	for(ll i=1;i<=20;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++){
			C[i][j]=C[i][j-1]*(i-j+1)/j;
		}
	}
	cuo[0]=1;
	cuo[2]=1;
	for(ll i=3;i<=20;i++){
		cuo[i]=(i-1)*(cuo[i-1]+cuo[i-2]);
	}
}

void solve(){
	while(cin>>n>>m){
		ll ans=0;
		for(ll i=m;i>=0;i--){
			ans+=C[n][i]*cuo[n-i];
		}
		cout<<ans<<endl;
	}
}

int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：Rainbow_Sky (赞：0)

## 大致题意：

Kelly 今天过生日，发了 $n$ 张邀请函，可是他的家只能容纳 $m$ 人，于是 Alex 决定如果某人收到的邀请函是他自己的，就会来，反之不会。求有几种让来的人少于 $m$ 的方案数。

## 思路

首先，我们都可以想到的是，在 $n$ 个人中选出 $i$ 人的方案数为 $C_n^i$，但是剩下的人怎么处理呢？这时，我们需要引入一种知识，叫错排，因为需要让若干人都不收到自己的邀请函，所以需要错排。

错排即为错开的排序，令数字不再原来的地方：$D_n=(n-1)\times(D_{n-1}+D_{n-2})$ 其中 $D_1=0,D_2=1$。
### 证明

其实证明也不难。我们可以假设共有 $n$ 个元素，先随意选出一个，设之为 $a$，那么不在自己位子上，共有 $n-1$ 种选择方式。之后选择一个 $b$，这时有了两种情况。

1. $b$ 恰好在 $a$ 的位置上，那么就对剩下的 $(n-2)$ 个元素进行错排，方案数为 $D_{n-2}$.

2. $b$ 不在 $a$ 的位置上，那么就还有 $n-1$ 个位置，可供选择，为 $D_{n-1}$。

最后，根据加法原理与乘法原理，可得 $D_n=(n-1)\times(D_{n-1}+D_{n-2})$。

------------


从而在我们取了 $i$ 人的时候，还剩 $n-i$ 人，则有 $D_{n-i}$ 种情况。

这样，$i$ 从 $0$ 枚举到 $m$，对于每一个 $i$ 进行计算：$C_n^iD_{n-i}$ 即可。

这样我们就可以非常轻易地得出，总方案数为：
$$S=\sum_{i=0}^mC_n^iD_{n-i}$$

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=30,MAXN=30;
int n,m; ll c[MAXN][MAXN],d[MAXN]; 
void yuchuli(){
	for(int i=0;i<=N;i++){		
		c[i][0]=1;
		for(int j=1;j<=i;j++)
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
	d[0]=1; d[1]=0;
	for(int i=2;i<=N;i++)		
		d[i]=(i-1)*(d[i-1]+d[i-2]);
}
int main(){
	yuchuli();
	while(scanf("%d%d",&n,&m)!=EOF){
		ll sum=0;
		for(int i=0;i<=m;i++)	
			sum+=c[n][i]*d[n-i];
		printf("%lld\n",sum);
	}
	return 0; 
}
```

---

