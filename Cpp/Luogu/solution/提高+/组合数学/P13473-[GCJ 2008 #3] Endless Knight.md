# [GCJ 2008 #3] Endless Knight

## 题目描述

在国际象棋游戏中，有一种棋子叫做骑士。骑士很特别——它不像其他棋子那样沿直线移动，而是以“L”形跳跃。具体来说，若 $(r_1, c_1)$ 到 $(r_2, c_2)$ 满足 $(r_1 - r_2)^2 + (c_1 - c_2)^2 = 5$，则骑士可以从 $(r_1, c_1)$ 跳到 $(r_2, c_2)$。

在本题中，我们的骑士将踏上一次骑士之旅，从左上角 $(1, 1)$ 走到右下角 $(H, W)$ 的巨大棋盘上。棋盘的高度为 $H$，宽度为 $W$。

你需要注意以下限制：

- 骑士非常正直且热情，只愿意向右和向下移动。也就是说，每一步只能跳到行号和列号都更大的格子。注意，这意味着有些情况下无法到达目标，例如在 $3 \times 10$ 的棋盘上。
- 棋盘上有 $R$ 个格子上有带有邪恶力量的石头。骑士不能落在这些格子上，但跳跃时可以飞越这些格子。

你的任务是计算骑士从左上角走到右下角的不同方案数，满足上述所有限制。显然，答案有时会非常大。请输出方案数对 $10007$ 取模的结果，$10007$ 是一个质数。

## 说明/提示

**数据范围**

- $1 \leq N \leq 100$
- $0 \leq R \leq 10$

**小数据集（5 分，测试点 1 - 可见）**

- $1 \leq W \leq 100$
- $1 \leq H \leq 100$
- $1 \leq r \leq H$
- $1 \leq c \leq W$

**大数据集（20 分，测试点 2 - 隐藏）**

- $1 \leq W \leq 10^{8}$
- $1 \leq H \leq 10^{8}$
- $1 \leq r \leq H$
- $1 \leq c \leq W$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 1 0
4 4 1
2 1
3 3 0
7 10 2
1 2
7 1
4 4 1
3 2```

### 输出

```
Case #1: 1
Case #2: 2
Case #3: 0
Case #4: 5
Case #5: 1```

# 题解

## 作者：light_searcher (赞：0)

为了方便描述，我们记从 $(x,y)$ 到 $(x+1,y+2)$ 为向右走，从 $(x,y)$ 到 $(x+2,y+1)$ 为向下走。

首先我们思考一下不考虑障碍，从左上角走到右下角的方案数为多少，注意到向右走的次数和向下走的次数是一定的，分别记为 $a,b$，则方案数为 $\binom{a+b}{a}$，$a,b$ 可以通过解二元一次方程组得到。

接下来考虑有障碍的方案数，考虑容斥，求出经过其中一些障碍物的方案数。我们称左上角、右下角和障碍为关键点，根据乘法原理，方案数为所有走过相邻两个关键点的方案数的乘积，从当前关键点走向下一个关键点的方案数可以直接用上面的方法做，奇正偶负加到答案上即可。

由于此题模数很小，所以需要使用 Lucas 定理。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=15,mod=10007,K=10010;
int T,n,m,k,inv[K],fac[K],facinv[K],x[N],y[N];
vector<pair<int,int> >p;
void init(){
	inv[1]=fac[0]=facinv[0]=1;
	for(int i=2;i<mod;i++) inv[i]=(inv[mod%i]*(-mod/i)%mod+mod)%mod;
	for(int i=1;i<mod;i++) fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<mod;i++) facinv[i]=facinv[i-1]*inv[i]%mod;
}
int C(int n,int m){
    if(m>n) return 0;
	return fac[n]*facinv[m]%mod*facinv[n-m]%mod;
}
int Lucas(int n,int m){
	if(!m) return 1;
	return Lucas(n/mod,m/mod)*C(n%mod,m%mod)%mod;
}
int main(){
	scanf("%d",&T);
	init();
	for(int id=1;id<=T;id++){
		int ans=0;
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=k;i++) scanf("%d%d",&x[i],&y[i]);
		for(int i=0;i<(1<<k);i++){
			p.clear();
			p.push_back({1,1});
			p.push_back({n,m});
			for(int j=1;j<=k;j++)
				if(i&(1<<(j-1))) p.push_back({x[j],y[j]});
			sort(p.begin(),p.end());
			int cnt=1; 
			for(int i=0;i<p.size()-1;i++){
				int h=p[i+1].first-p[i].first,w=p[i+1].second-p[i].second;
				if(h<0||w<0||(h+w)%3){
					cnt=0;
					break; 
				}
				int a=h-(h+w)/3,b=w-(h+w)/3;
				if(a<0||b<0){
					cnt=0;
					break;
				}
				cnt=cnt*Lucas(a+b,a)%mod;
			}
			if(__builtin_popcount(i)&1) ans=(ans-cnt+mod)%mod;
			else ans=(ans+cnt)%mod;
		}
		printf("Case #%d: %d\n",id,ans);
	}
	return 0;
}

---

