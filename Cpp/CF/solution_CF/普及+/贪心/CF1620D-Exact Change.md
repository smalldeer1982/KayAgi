# Exact Change

## 题目描述

One day, early in the morning, you decided to buy yourself a bag of chips in the nearby store. The store has chips of $ n $ different flavors. A bag of the $ i $ -th flavor costs $ a_i $ burles.

The store may run out of some flavors, so you'll decide which one to buy after arriving there. But there are two major flaws in this plan:

1. you have only coins of $ 1 $ , $ 2 $ and $ 3 $ burles;
2. since it's morning, the store will ask you to pay in exact change, i. e. if you choose the $ i $ -th flavor, you'll have to pay exactly $ a_i $ burles.

Coins are heavy, so you'd like to take the least possible number of coins in total. That's why you are wondering: what is the minimum total number of coins you should take with you, so you can buy a bag of chips of any flavor in exact change?

## 说明/提示

In the first test case, you should, for example, take with you $ 445 $ coins of value $ 3 $ and $ 1 $ coin of value $ 2 $ . So, $ 1337 = 445 \cdot 3 + 1 \cdot 2 $ .

In the second test case, you should, for example, take $ 2 $ coins of value $ 3 $ and $ 2 $ coins of value $ 2 $ . So you can pay either exactly $ 8 = 2 \cdot 3 + 1 \cdot 2 $ or $ 10 = 2 \cdot 3 + 2 \cdot 2 $ .

In the third test case, it's enough to take $ 1 $ coin of value $ 3 $ and $ 2 $ coins of value $ 1 $ .

## 样例 #1

### 输入

```
4
1
1337
3
10 8 10
5
1 2 3 4 5
3
7 77 777```

### 输出

```
446
4
3
260```

# 题解

## 作者：Presentation_Emitter (赞：13)

结论题。

对于每一种方案，面值为 $1$ 和 $2$ 的硬币各不超过两个。三个面值为 $1$ 的硬币显然可以替换为一个面值为 $3$ 的硬币。$2$ 同理。

枚举面值 $1$ 和 $2$ 的硬币个数，然后直接算出面值为 $3$ 的硬币个数即可。时间复杂度 $\Theta(3^2Tn)$。

核心代码：

```cpp
ll slv(ll t1,ll t2)
{
	ll res=-1;
	for(int i=1;i<=n;++i)
	{
		ll u=inf;
		for(int j=0;j<=t1;++j)
		{
			for(int k=0;k<=t2;++k)
			{
				ll r=a[i]-j-k-k;
				if(r<0)continue;
				if(!(r%3))tomin(u,r/3);
			}
		}
		tomax(res,u);
	}
	ret res+t1+t2;
}
```

个人觉得比 `C` 水多了。

---

## 作者：World_Creater (赞：5)

一道分类讨论 + 贪心的题目  
首先显然答案不会超过 $\Big\lfloor \dfrac{\max}{3} \Big\rfloor +2$（$\max$ 为原输入最大值，这种取法是先取到足够的 $3$，再取两个 $1$ 补齐余数）。且不会小于 $\Big\lceil\dfrac{\max}{3}\Big\rceil$。因此我们要做的就是如何优化掉朴素的取法。  
首先如果 $\max$ 是 $3$ 的倍数。  
1. 如果其他数也都是 $3$ 的倍数，直接输出  $\dfrac{\max}{3}$ 即可。
2. 否则将其中的一个 $3$ 拆成 $1+2$ ，这样所有小于 $\max$ 的数一定可以被取到，输出 $\dfrac {\max}{3}+1$。

如果 $\max \bmod 3=1$
1. 正常的取法是取 $\Big\lfloor\dfrac{\max}{3}\Big\rfloor$ 个 $3$ 并且再多取一个 $1$ ，如果有除以 $3$ 余 $2$ 的数就多取一个 $1$ 补足。
2. 但是手推样例即可以发现这种做法不是最优的，我们可以将其中的一个 $3$ 改成 $2$ ，将多取的那个 $1$ 也改成 $2$，变成取 $\Big\lfloor\dfrac{\max}{3}\Big\rfloor-1$ 个 $3$ 和两个 $2$ 的形式。
3. 这样的做法只有两个数取不到：$1$ 和 $\max-1$ ，仅当出现这两个数时特判，否则输出 $\Big\lfloor\dfrac{\max}{3}\Big\rfloor+1$  。

如果 $\max \bmod 3=1$  
1. 这种情况下取到 $\max$ 并保证数量最小的方案是唯一的： $\Big\lfloor\dfrac{\max}{3}\Big\rfloor$ 个 $3$ 和一个 $2$。
2. 因此除非其他数均只有除以 $3$ 余 $2$ 和被 $3$ 整除的情况时输出 $\Big\lfloor\dfrac{\max}{3}\Big\rfloor+1$ 否则输出$ \Big\lfloor\dfrac{\max}{3}\Big\rfloor +2$。

最后的情况是只有 $\max$ 不被 $3$ 整除而其他数都被 $3$ 整除时，只需输出 $\Big\lfloor\dfrac{\max}{3}\Big\rfloor+1$ 即可。 

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005],mod1,mod2,mmod,maxn;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		mod1=mod2=mmod=maxn=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		sort(a+1,a+1+n);
		mmod=a[n]%3;
		for(int i=1;i<n;i++)
		{
			if(a[i]==a[n]) break;
			maxn=max(a[i],maxn);
			if(a[i]%3==1) mod1=1;
			if(a[i]%3==2) mod2=1;
		}
		if(mmod==0)
		{
			if(mod1||mod2) cout<<a[n]/3+1;
			else cout<<a[n]/3;
		}
		else 
		{
			if(!mod1&&!mod2) cout<<a[n]/3+1;
			else 
			if(mmod==1)
			{
				if(mod2==1&&a[1]!=1&&a[n]-maxn!=1) cout<<a[n]/3+1;
				else if(mod2==0&&mod1==1) cout<<a[n]/3+1;
				else cout<<a[n]/3+2;
			}
			else if(mmod==2)
			{
				if(mod2==1&&mod1==0) cout<<a[n]/3+1;
				else cout<<a[n]/3+2;
			}
		}
		puts("");
	}
}
```


---

## 作者：Tyyyyyy (赞：5)

# CF1620D
#### 题意简述
- 有 $n$ 个物品，第 $i$ 个物品价格为 $a_i$。
- 有三种货币，面值分别为 $1,2,3$。
- 求最小需要多少张货币，才能表出所有的 $a_i$。
- 多组测试数据。
- $1 \leq t \leq 1000,1 \leq n \leq 100,1 \leq a_i \leq 10^9$。

#### 题目分析
首先，可以证明我们最多带 $1$ 张 $1$ 元和 $2$ 张 $2$ 元。

因为如果带 $2$ 张（或更多）$1$ 元，则用更少张数的 $2$ 元或 $3$ 元可以表出。$2$ 元同理。

因此，我们可以枚举带的 $1$ 元和 $2$ 元的张数，再计算需要多少张 $3$ 元。

具体来说，设带了 $i$ 张 $1$ 元，$j$ 张 $2$ 元，当前考虑到第 $k$ 件物品，则这一件物品需要的 $3$ 元的张数 $x_k$ 为：

$$x_k=\begin{cases}
\frac{a_k}{3}-1 & a_k \bmod 3 =0 , i \times j \ne 0 \\
\frac{a_k}{3} & a_k \bmod 3 =0 , i \times j=0 \\
\frac{a_k-4}{3} & a_k\bmod 3=1,a_k\geq 4,j =2\\
\frac{a_k-1}{3} & a_k \bmod 3=1,i \ne 0\\
\frac{a_k-5}{3} & a_k \bmod 3=2,a_k \geq 5,i \ne 0,j=2\\
\frac{a_k-2}{3} & a_k \bmod 3=2,j\ne 0 \\
\infty & \text{otherwise}
\end{cases}$$

当前情况需要的 $3$ 元张数即 $\max_{i=1}^n x_i$。最后在所有情况中取总张数最小的即可。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[110];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		int ans=1e9;
		for(int num1=0;num1<=1;num1++)
		{
			for(int num2=0;num2<=2;num2++)
			{
				int res=0;
				for(int i=1;i<=n;i++)
				{
					if(a[i]%3==0)
					{
						if(num1&&num2)res=max(res,a[i]/3-1);
						else res=max(res,a[i]/3);
					}
					else if(a[i]%3==1)
					{
						if(num2==2&&a[i]>=4)res=max(res,(a[i]-4)/3);
						else if(num1)res=max(res,(a[i]-1)/3);
						else res=1e9;
					}
					else
					{
						if(num2==2&&num1&&a[i]>=5)res=max(res,(a[i]-5)/3);
						else if(num2)res=max(res,(a[i]-2)/3);
						else res=1e9;
					}
				}
				ans=min(ans,res+num1+num2);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：jianhe (赞：4)

注意到货币的面值只能是 $1,2,3$，就从这一点特殊性质入手。

可以发现，面值为 $1$ 的纸币不会超过 $2$ 张，因为 $2$ 张 $1$ 元纸币相当于 $1$ 张 $2$ 元纸币，显然后者更优。

同理，面值为 $2$ 的纸币不会超过 $3$ 张，因为 $3$ 张 $2$ 元纸币相当于 $2$ 张 $3$ 元纸币，显然后者更优。

然后暴力枚举即可~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+10,inf=1e9;
ll T,n,a[N],res;
ll solve(ll t,ll t1,ll t2){
	ll ct=inf; 
	for(int i=0;i<=t1;i++)//面值为 1 的纸币数量
		for(int j=0;j<=t2;j++){//面值为 2 的纸币数量
			ll tmp=t-i-j*2;//剩余钱数
			if(tmp<0) continue;
			if(!(tmp%3)) ct=min(ct,tmp/3);//面值为 3 的纸币数量
		}
	return ct;
}
ll work(ll t1,ll t2){
	ll ans=-1;//面值为 3 的纸币数量最大值
	for(int i=1;i<=n;i++) ans=max(ans,solve(a[i],t1,t2));
	return ans+t1+t2;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;res=inf;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=0;i<=1;i++)
			for(int j=0;j<=2;j++) res=min(res,work(i,j));
		cout<<res<<"\n";
	}
	return 0;
}

```

---

## 作者：Genius_Star (赞：1)

### 题意：

有面值为 $1$，$2$，$3$ 的三种硬币，你希望准备总量最少的硬币，能够买 $n$ 个商品的任意一种。

### 思路：

发现到 $1$ 和 $2$ 的面值最多只有 $2$ 个，因为拿 $3$ 个或者以上直接拿硬币 $3$ 了。

所以，我们考虑暴力做法，首先枚举面值 $1,2,3$ 的个数 $i,j,k$，其中硬币 $3$  的个数，我们考虑对于 $\max\limits_{i=1}^n(a_i)$，我们以此定 $3$ 的数量的上界和下界，下界为：$\frac{\max\limits_{i=1}^n(a_i)}{3}-5$，因为这 $6$ 是我们可以用 $1$ 和 $2$ 硬币最多凑出来的钱，而上界即为：$\lceil\frac{\max\limits_{i=1}^n(a_i)}{3}\rceil$。

然后，我们可以直接暴力计算该面值选中方案是否满足条件，以此枚举 $x,y,z$，其中 $x$ 是第 $x$ 件物品，$y \le i$ 表示我们选择 $y$ 枚 $1$ 硬币，$z \le j$ 表示我们选择 $z$ 枚 $2$ 硬币。

然后，得到剩下的加价钱 $a_x-y-z \times 2$，我们判断这个值能否被 $3$ 整除，并且判断需要的钞票是否大于了 $k$。

这样，时间复杂度应该为：$O(n \times m)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1010;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,Max,Min;
ll a[N];
int main(){
	T=read();
	while(T--){
		Max=0,Min=1e16;
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			Max=max(Max,a[i]);
		}
		for(int i=0;i<=2;i++){
			for(int j=0;j<=2;j++){
				for(int k=max(0ll,Max/3-6);k<=(ceil)(Max*1.0/3.0);k++){
					ll cnt=i+j+k;
					bool f=1;
					for(int x=1;x<=n;x++){
						bool t=0;
						for(int y=0;y<=i;y++){
							for(int z=0;z<=j;z++){
								ll sum=a[x]-y-z*2;
								if(sum>=0&&sum%3==0&&sum/3<=k){
									t=1;
									break;
								}
							}
						}
						if(!t){
							f=0;
							break;
						}
					}
					if(f)
					  Min=min(Min,cnt);
				}
			}
		}
		write(Min);
		putchar('\n'); 
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# CF1620D 题解



## 思路分析

设 $v=\max_{i=1}^n\{a_i\}$。

有一个显然的策略：选 $\left\lfloor\dfrac v3\right\rfloor$ 个 $3$，然后选 $1$ 和 $2$ 补余数，如果所有 $a_i$ 中没有 $\bmod 3=1$ 的就不选 $1$，同理如果 $a_i$ 中没有 $\bmod 3=2$ 的就不选 $2$。

可以证明当 $1,2$ 中选了 $\le 1$ 个时，答案不会更优，而如果 $1,2$ 都选了。

- 如果 $v\bmod 3=0$，显然可以将一个 $3$ 去掉，用 $1+2$ 取代 $3$。
- 如果 $v\bmod 3=1$，去掉一个 $3$ 和一个 $1$，加入一个 $2$，用 $2+2$ 取代 $1+3$，不过需要特别注意的是如果 $a_i$ 中出现了 $v-1$ 或 $1$ 是不能这么更换的。
- 如果 $v\bmod 3=2$ 没有更优的策略。

因此根据上面的规则简单模拟即可。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int MAXN=101;
int a[MAXN];
inline bool check(int n,int v) {
	for(int i=1;i<=n;++i) if(a[i]==1||a[i]==v-1) return false;
	return true;
}
inline void solve() {
	int n,vis[3]={0,0,0},ans=0,v=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		ans=max(ans,a[i]/3);
		v=max(v,a[i]);
		vis[a[i]%3]=1;
	}
	ans+=vis[1]+vis[2];
	if(v%3==0&&vis[1]&&vis[2]) --ans;
	if(v%3==1&&vis[1]&&vis[2]) if(check(n,v)) --ans;
	printf("%d\n",ans);
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$

---
### 解题思路：

成功地将一个很正常的枚举做成了人工考虑所有情况。

在 $a_i$ 很大的时候，取很多的 $3$，然后如果不够就再加上一个 $1$ 或者 $2$。对于最大的那一个数进行此项操作后，不一定能将之前的所有的数都表示出来，这时候就需要更改一些数或者添加一些数。

如果遇到不能表示的数，也就是减去了最后增加的那一个数时候还是不能被 $3$ 整除的数（或者称在模三意义下和最大的数不同余），则将一个 $3$ 拆成一个 $1$ 和一个 $2$ 就一定能表示出来，而且代价也仅仅比原来大 $1$。当不需要添上数字，或者添上的数字是 $2$ 时，这样的操作一定是最优的，但是添上的数为 $1$ 的时候这样就不一定是最优的了。

添上数且添上的数是 $1$ 时，因为可以将一个 $3$ 和添上的 $1$ 一起变成两个 $2$，所以特别讨论进行这样的转化后是否可以不添加数直接达到表示所有的数的目的。

这里有一些小细节：在去除了一个 $3$ 之后，不一定能表示原来一定能表示的三的倍数，当且仅当这个三的倍数比最大的数小至少 $4$ 的时候能直接用三表示。同时，部分数很小（比如 $1$），在判断的时候，会出现减去 $4$ 变成 $-3$ 而让程序以为是可以用若干个三和两个二表示的数，需要特判。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[10005],ans,MOD;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		ans=(a[n]/3)+(a[n]%3!=0);
		MOD=a[n]%3;
		if(MOD==1){
			int ans1=ans;
			for(int i=1;i<=n;i++){
				if((a[i]-MOD)%3==0)continue;
				if(a[i]%3==0)continue;
				ans++;break;
			}
			MOD=2;
			for(int i=1;i<=n;i++){
				if((a[i]-MOD)%3==0)continue;
				if((a[i]-MOD-MOD)%3==0&&(a[i]-MOD*2>=0))continue;
				if(a[i]%3==0&&a[n]-a[i]>=4)continue;
				if(a[i]==a[n])continue;
				ans1++;break;
			}
			ans=min(ans,ans1);
		}
		else{
			for(int i=1;i<=n;i++){
				if((a[i]-MOD)%3==0)continue;
				if(a[i]%3==0)continue;
				ans++;break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

