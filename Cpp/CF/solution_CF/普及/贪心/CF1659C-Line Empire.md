# Line Empire

## 题目描述

You are an ambitious king who wants to be the Emperor of The Reals. But to do that, you must first become Emperor of The Integers.

Consider a number axis. The capital of your empire is initially at $ 0 $ . There are $ n $ unconquered kingdoms at positions $ 0<x_1<x_2<\ldots<x_n $ . You want to conquer all other kingdoms.

There are two actions available to you:

- You can change the location of your capital (let its current position be $ c_1 $ ) to any other conquered kingdom (let its position be $ c_2 $ ) at a cost of $ a\cdot |c_1-c_2| $ .
- From the current capital (let its current position be $ c_1 $ ) you can conquer an unconquered kingdom (let its position be $ c_2 $ ) at a cost of $ b\cdot |c_1-c_2| $ . You cannot conquer a kingdom if there is an unconquered kingdom between the target and your capital.

Note that you cannot place the capital at a point without a kingdom. In other words, at any point, your capital can only be at $ 0 $ or one of $ x_1,x_2,\ldots,x_n $ . Also note that conquering a kingdom does not change the position of your capital.

Find the minimum total cost to conquer all kingdoms. Your capital can be anywhere at the end.

## 说明/提示

Here is an optimal sequence of moves for the second test case:

1. Conquer the kingdom at position $ 1 $ with cost $ 3\cdot(1-0)=3 $ .
2. Move the capital to the kingdom at position $ 1 $ with cost $ 6\cdot(1-0)=6 $ .
3. Conquer the kingdom at position $ 5 $ with cost $ 3\cdot(5-1)=12 $ .
4. Move the capital to the kingdom at position $ 5 $ with cost $ 6\cdot(5-1)=24 $ .
5. Conquer the kingdom at position $ 6 $ with cost $ 3\cdot(6-5)=3 $ .
6. Conquer the kingdom at position $ 21 $ with cost $ 3\cdot(21-5)=48 $ .
7. Conquer the kingdom at position $ 30 $ with cost $ 3\cdot(30-5)=75 $ .

The total cost is $ 3+6+12+24+3+48+75=171 $ . You cannot get a lower cost than this.

## 样例 #1

### 输入

```
4
5 2 7
3 5 12 13 21
5 6 3
1 5 6 21 30
2 9 3
10 15
11 27182 31415
16 18 33 98 874 989 4848 20458 34365 38117 72030```

### 输出

```
173
171
75
3298918744```

# 题解

## 作者：Engulf (赞：4)

容易发现我们只能从原点开始往右一个一个王国攻占，那么我们对于当前的王国 $x_i$，选择只有两种：

1. 直接攻占。
2. 占领并迁都。

显然我们计算两种操作的贡献取个最小值即可。

不管怎么操作，都必须攻占 $x_i$，所以操作变成了决定 **是否迁都**。

假设现在已经攻占了 $x_i$，当前首都为 $cap$：

- 不迁都的贡献：$b \cdot \sum\limits_{j = i + 1} ^ {n} x_j - cap$。
- 迁都的贡献：$a \cdot (x_i - cap) + b \cdot \sum\limits_{j = i + 1} ^ {n} x_j - x_i$。

若迁都造成的贡献更小，就迁移首都。

因为这个更新没有后效性，当前的状态过了就不会再算，所以上面的贪心是正确的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5 + 5;
int n, a, b;
int x[N], sum[N];

inline int query(int l, int r) {return sum[r] - sum[l - 1];}

int so1ve()
{
	for (int i = 1; i <= n; i ++ ) sum[i] = 0;
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i ++ ) cin >> x[i], sum[i] = sum[i - 1] + x[i];
	int cap = 0, ans = 0;
	for (int i = 1; i <= n; i ++ )
	{
		ans += b * (x[i] - cap);
		int t1 = b * (query(i + 1, n) - cap * (n - i));
		int t2 = a * (x[i] - cap) + b * (query(i + 1, n) - x[i] * (n - i));
		if (t2 < t1) ans += a * (x[i] - cap), cap = x[i];
	}
	return ans;
}

signed main()
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	while (T -- ) cout << so1ve() << '\n';
	return 0;
}
```

---

## 作者：rmzls (赞：2)

### 思路
观察题目，我们能获得两个信息点：

1.你可以选择一个已经被征服的王国，然后把首都迁到那个王国。  
2.你可以选择一个没有被征服的王国，满足你的首都与其之间没有其他未被征服的王国，然后征服那个王国。

考虑到我们的首都一开始在最左边，而去攻占其他国家的时候中间不能有其他国家,那么显然我们的攻占顺序是从左到右。既然攻占顺序已经确定，那么不考虑换首都，以首都 $k$ 去攻占从 $m$ 开始的其他国家的代价为（其中 $c_i$ 表示第 $i$ 个国家的坐标）

$b\times(c_m-c_k+c_{m+1}-c_k+c_{m+2}-c_k+…+c_n-c_k)=b\times(\sum_{i=m}^nc_i-c_k\times(n-m+1))$

而当我们将首都 $k$ 换到一个新地点 $j$ 的时候，后面所需要的代价为

$b\times(c_m-c_j+c_{m+1}-c_j+c_{m+2}-c_j+…+c_n-c_j)+a\times(c_j-c_k)=a\times(c_j-c_k)+b\times(\sum_{i=m}^nc_i-c_j\times(n-m+1))$

显然对于一个已经攻占的位置 $j$ ，若满足

$a\times(c_j-c_k)+b\times(\sum_{i=m}^nc_i-c_j\times(n-m+1))<b\times(\sum_{i=m}^nc_i-c_k\times(n-m+1))$

那么我们便可以进行转移。但是这个式子看上去是不是复杂了点？

我们通过化简，可以得到一个简单的式子(相信大家都会化简的啦）：

$a<b\times(n-m+1)$

那么只要满足这个条件就可以换首都了。我们发现这个式子只和 $m$ 有关，所以每次个新地点被攻占下来的时候只用考虑一次需不需要换首都就行了。
所以每针对一个新攻下的地点考虑一次是否需要转移便可以求解。记录一个 $cap$ 表示当前首都的坐标。

------------
### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a,n,b,dis;//并不需要开数组，因为每个点的距离只会计算一次，用一个dis存下来就行了
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld%lld",&n,&a,&b);
		int ans=0,cap=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&dis);
			ans+=b*(abs(dis-cap));
			if(b*(n-i)>a){//判断是否转移，公式见上文
				ans+=a*(abs(dis-cap));
				cap=dis;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
} 
```


---

## 作者：happy_dengziyue (赞：2)

### 1 思路

很明显的，国王的最优方案一定是这样的：

依次攻占下一个国家，然后每次攻占都要立即迁移首都。直到，攻占完第 $k$ 个国家之后，不迁移首都，而是一鼓作气攻占完所有国家。打完后，首都在第 $k-1$ 个国家。

当然了，首都也可以在 $0$ 点。

那么，我们就设 $s[i]$ 为第 $i$ 个国家和第 $n$ 个国家之间的距离，设 $s2[i]$ 为 $\sum_{j=i+1}^nx[j]-x[i]$。

可以发现，设首都位于 $i$，那么，迁移首都的花费就是 $(s[0]-s[i])\times a$，而攻占国家的花费就是 $(s[0]-s[i]+s2[i])\times b$。

依次枚举首都位置，取答案最小值即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
#define inf 200000000000000000
int t;
int n;
long long a,b;
long long x[max_n+2];
long long s[max_n+2];
long long s2[max_n+2];
long long ans;
long long mi(long long a,long long b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1659C_1.in","r",stdin);
	freopen("CF1659C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%lld%lld",&n,&a,&b);
		x[0]=0;
		for(int i=1;i<=n;++i)scanf("%lld",x+i);
		s[n]=0;
		s2[n]=0;
		for(int i=n-1;i>=0;--i){
			s[i]=x[i+1]-x[i]+s[i+1];
			s2[i]=(x[i+1]-x[i])*(n-i)+s2[i+1];
		}
		ans=inf;
		for(int i=n-1;i>=0;--i)ans=mi(ans,(s[0]-s[i])*(a+b)+s2[i]*b);
		printf("%lld\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/74293761)

By **dengziyue**

---

## 作者：Erotate (赞：0)

### Solution

在占领了一个王国后，有迁都和不迁都两种选择，那么：

- 不迁都的代价为 $b \times \sum\limits_{j = i + 1} ^ {n} x_j - C$。

- 迁都的代价为 $b \times \sum\limits_{j = i + 1} ^ {n} x_j + a \times (x_i - C) - x_i$。

其中 $i$ 为当前攻占的王国，$C$ 为首都的位置，其余的变量与题目意义相同。

所以如果迁都的代价更少，那就迁都，否则直接攻占即可。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int t,n,a,b,x[N],sum[N],ans;
signed main(){
    scanf("%lld",&t);
    while(t--){
        memset(x,0,sizeof(x));
        memset(sum,0,sizeof(0));
        ans=1e18;
        scanf("%lld%lld%lld",&n,&a,&b);
        for(int i=1;i<=n;++i){
            scanf("%lld",&x[i]);
            sum[i]=sum[i-1]+x[i];
        }
        for(int i=0;i<=n;++i) ans=min(ans,x[i]*b+x[i]*a+(sum[n]-sum[i]-x[i]*(n-i))*b);
        printf("%lld\n",ans);
    }
    system("pause");
    return 0;
}
```


---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1659C)

*1500 都不会了，这水平。

首先考虑一种简单情况就是 $a \le b$，显然这时候迁移肯定比不迁移好，所以每次都迁，最后迁到 $x_{n-1}$，所以答案就是 $ax_{n-1}+bx_n$。

然后考虑 $a>b$ 怎么做。发现当前如果不迁移，以后迁移的收益会更低（早迁移的话，迁移费少了，而且攻打的费用也少了），所以如果当前不迁那以后更不会迁了。

于是最佳策略一定是不断迁移到 $x_k$，然后从 $x_{k+1} \sim x_n$ 只攻打不迁移。这样答案就是 $ax_k+bx_k+b[\sum\limits_{i=k+1}^nx_i-(n-k)x_k]$，这个式子处理一下前缀和可以直接 $O(1)$ 求。

所以暴力枚举 $k$ 算贡献取最小值，复杂度 $O(n)$。

可以看出 $a \le b$ 的情况就是 $a>b$ 时，$k=n-1$ 的特殊情况。

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1659C)
一开始看到这道题，我的思路是将每一个王国的上一个王国记录下来，如果直接征服该王国的代价比先迁都到上一个王国再征服该王国的代价小，就直接征服，否则先迁都到上一个王国再征服该王国。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	scanf("%d",&t);
	while(t--){
		long long n,a,b,sd=0,la=0;
		long long ans=0;
		scanf("%d%d%d",&n,&a,&b);
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			if((x-sd)*b>=(la-sd)*a+(x-la)*b){
				ans+=(la-sd)*a+(x-la)*b;
				sd=la;
			}
			else ans+=(x-sd)*b;
			la=x;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
结果可想而知，连样例都没过。

原因也很简单，迁都之后不仅对下一个王国有影响，还对之后所有的王国都有影响。

那正确的思路也很容易想到了，那就是遇到一个王国先征服，再根据一次迁都的代价和以后所有节省的距离判断是否要迁都。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	scanf("%d",&t);
	while(t--){
		long long n,a,b,sd=0;
		long long ans=0;
		scanf("%lld%lld%lld",&n,&a,&b);
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			ans+=(x-sd)*b;//先征服
			if((n-i)*b*(x-sd)/*该王国以后所有节省的代价*/>a*(x-sd)/*迁都的代价*/){
				ans+=(x-sd)*a;
				sd=x;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF1659C](https://www.luogu.com.cn/problem/CF1659C)

# 思路

这题思路是暴力。

对于当前位置来说，我们要么攻占和迁都，要么只攻占。

那么我们比较不迁都省下来的总费用与迁都哪个小，然后直接输出。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int t,n,a,b;
void solve(){
	int sum=0,p=0;
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		sum+=b*(x-p);
		if((n-i)*b>a){
			sum+=a*(x-p);
			p=x;
		}
	}
	cout<<sum<<endl;
}
signed main(){
	cin>>t;
	while(t--){
		solve();
	}
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/141029914)

---

