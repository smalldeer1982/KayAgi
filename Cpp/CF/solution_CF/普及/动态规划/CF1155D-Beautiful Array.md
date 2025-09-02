# Beautiful Array

## 题目描述

NaCly_Fish 给了你一个长度为 $n$ 的序列。

她想知道这个序列最大的美丽程度。

同时，她给了你一次操作的机会，你需要选择序列的一个子串，将其中所有数乘上 NaCly_Fish 给定的一个常数 $x$。

我们定义一个序列的美丽程度为其所有子串的和的最大值，而子串则是序列的一个连续子序列，在本题中，子串可以是空的。

## 样例 #1

### 输入

```
5 -2
-3 8 -2 1 -6
```

### 输出

```
22
```

## 样例 #2

### 输入

```
12 -3
1 3 3 7 1 3 3 7 1 3 3 7
```

### 输出

```
42
```

## 样例 #3

### 输入

```
5 10
-1 -2 -3 -4 -5
```

### 输出

```
0
```

# 题解

## 作者：Yizhixiaoyun (赞：9)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/16731966.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1155D)

## 题目分析

说实话，第一眼这题以为是贪心...~~（事实上我看所有动态规划都像贪心）~~。

然后接着发现贪心明显做不了，又看见最大子段和，很容易联想到 $\text{dp}$。

在设计状态的时候，我们考虑有哪些状态影响结果：

- 当前处于序列的哪一位

- 是否使用了魔法

开始以为只用设计用和不用两种状态，结果后来发现实际上有三种状态：

1. 不用魔法

记状态为 $dp_{i,0}$，直接从上一个状态转移过来即可。

$$dp_{i,0} = \max(dp_{i-1,0} + a_i,0)$$

2. 正在用魔法

先从 $dp_{i,0}$ 转移过来，然后再与使用魔法后的结果比较。

$$dp_{i,1} = \max(dp_{i,0},dp_{i-1,1} + a_i \times x)$$

3. 已经使用完魔法

还是从 $dp_{i,1}$ 转移过来，然后另一边从 $dp_{i-1,2}$ 转移过来，加上题中所给的 $a_i$。

$$dp_{i,2} = \max(dp_{i,1},dp_{i-1,2} + a_i)$$

最后 $ans$ 直接求三者最大值即可。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=3e5+5;
int n,x;
int ans;
int a[maxn],dp[maxn][4];
inline void init(){
	cin>>n>>x;
	for(register int i=1;i<=n;++i) cin>>a[i];
}
signed main(){
	init();
	for(register int i=1;i<=n;++i){
		dp[i][0]=max(dp[i-1][0]+a[i],0LL);
		dp[i][1]=max(dp[i][0],dp[i-1][1]+a[i]*x);
		dp[i][2]=max(dp[i][1],dp[i-1][2]+a[i]);
		ans=max(ans,dp[i][2]);
	}
	cout<<ans;
}
```

---

## 作者：Rainy_chen (赞：5)

赛后AC选手前来水一发题解  
很显然的我们知道不带修的最大子段和问题是可以用dp解决的  
那么我们把dp的思路同样套到这一道题上  
我们可以观察发现 每一个状态只包含了两个信息
- 推到哪一位了
- 乘法的区间是否过了  

那么我们设计一个dp  

$dp_{i,j}$表示末尾为$i$的子序列的最大值  
$j=1$表示没使用乘法 $j=2$表示正在使用 $j=3$表示使用过了  
然后三个方程就可以顺手推出来  
$dp_{i,1} = max(dp_{i-1,1}+A_i,0)$  
$dp_{i,2} = max(dp_{i-1,1}+A_i\times x,dp_{i-1,2}+A_i\times x,0)$  
$dp_{i,3} = max(dp_{i-1,3}+A_i,dp_{i-1,2}+A_i,0)$  

然后随便做一下dp就好了

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long int_t;

int_t read(){
    int_t ans = 0,w = 1;char ch=0;
    while(!isdigit(ch)){ch=getchar();if(ch=='-')w=-1;}
    while(isdigit(ch)){ans=ans*10+ch-'0';ch=getchar();}
    return ans*w;
}

int main (){
    int_t n = read(),x = read();
    int_t a = 0,b = 0,c = 0,na,nb,nc,ans=0;
    for(int i=1;i<=n;i++){
        int_t now = read();
        na = max(a+now,0ll);
        nb = max(max(a+now*x,b+now*x),0ll);
        nc = max(max(c+now,b+now),0ll);
        a = na,b = nb,c = nc;
        ans = max(max(ans,a),max(b,c));
    }
    cout<<ans;
}
```


---

## 作者：activeO (赞：3)

## 题目大意

其实就是最大字段和加上一个条件：可以将字串乘上 k。

## 思路

最大字段和可以用 dp 维护，尝试 dp 解决。

显然 dp 状态只包括：

- 推到哪一位
- 用魔法的情况

然后设计出状态：

$ dp_{i,0} $ 表示不用魔法, $ dp_{i,1} $ 表示现在正在用魔法， $ dp_{i,2} $ 表示用完了魔法。容易推出：

$ dp_{i,0}=\max(0ll,dp_{i-1,0}+a_i) $

$ dp_{i,1}=\max(dp_{i,0},dp_{i-1,1}+k*a_i) $

$ dp_{i,2}=\max(dp_{i,1},dp_{i-1,2}+a_i) $ 

## 代码

**注：变量名略有不同，祝大家学习愉快！**

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn=3e5+10;
ll a[maxn],dp[maxn][5];

int main(){
	
	ll n,x,ans=0;
	
	scanf("%lld %lld",&n,&x);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	
	for(int i=1;i<=n;i++){
		dp[i][0]=max(0ll,dp[i-1][0]+a[i]);
		dp[i][1]=max(dp[i][0],dp[i-1][1]+x*a[i]);
		dp[i][2]=max(dp[i][1],dp[i-1][2]+a[i]);
		ans=max(ans,dp[i][2]);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
```


---

## 作者：MatrixCascade (赞：3)

定义 $dp[i][0/1/2]$ 表示当前在第 i 位，0 代表还没用魔法，1 代表正在用魔法，2 代表魔法用完了。

转移思路也很明显

```cpp
		dp[i][0]=max(max(a[i],0ll),dp[i-1][0]+a[i]);
		dp[i][1]=max(max(dp[i-1][0],dp[i-1][1])+a[i]*x,max(a[i]*x,0ll));
		dp[i][2]=max(max(dp[i-1][1],max(dp[i-1][2],dp[i-1][0]))+a[i],max(a[i],0ll));
```

然后每次让 ans 对 $dp[i][0/1/2]$ 取个 max 就可以了。

---

## 作者：冒泡ioa (赞：3)

>[博客链接](http://bubbleioa.top/archives/872)

其实就是最长连续子串的变形。

| 变量名 | 变量作用 |
| ------------ | ------------ |
| $s$ | $s_i$ 表示整个序列乘上 $x$ 后的前缀和 |
| $L$ | $L_i$ 表示 $i$ 位置**往前**的最大连续子串和 |
| $R$ | $R_i$ 表示 $i$ 位置**往后**的最大连续子串和 |

假如我们选择了 $i$ 到 $j$ ($j\le i$) 这一段乘上 $x$ 那么答案就为 
$$s[i]-s[j-1]+R[i+1]+L[j-1]$$

我们可以枚举 $s[i]+R[i+1]$ ，用 $max(L[j-1]-s[j-1])$ 来更新答案

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[300005];
ll s[300005],L[300005],R[300005];

int main() {
	int n;ll x;
	cin>>n>>x;
	ll ans=0;
	for (int i=1; i<=n; i++) {cin>>a[i];ans+=a[i];s[i]=x*a[i];s[i]+=s[i-1];}
	ans=max(ans,0LL);
	for (int i=1; i<=n; i++) L[i]=max(L[i-1]+a[i],0LL);
	for (int i=n; i>=1; i--) R[i]=max(R[i+1]+a[i],0LL);
	ll mx=-1LL<<62;
	for (int i=1; i<=n; i++) {
		mx=max(mx,L[i-1]-s[i-1]);
		ans=max(ans,R[i+1]+s[i]+mx);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：「已注销」 (赞：3)

可以发现答案最多由$3$段组成：乘$x$的一段和左右两段

直接`dp`，甚至不需要开数组

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll k,a,f[3],ans;
int main(){
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;++i){
		scanf("%lld",&a);
		f[0]=max(0LL,f[0]+a);
		f[1]=max(f[0],f[1]+k*a);
		f[2]=max(f[1],f[2]+a);
		ans=max(ans,f[2]);
	}
	printf("%lld",ans);
}
```


---

## 作者：3ksc03_is_sb (赞：1)

## 题目大意
有一个长度为 $n$ 的序列，序列中的字串可以乘一次 $x$，求最大字段和。
## 思路
最开始没看题目，直接求最大字段和，在判断乘不乘 $x$。结果不出意料的 WA 了。  
再次看题目，发现可以用 dp 来做，并划分三个状态。 

首先，我们可以建一个二维数组，用来存当前的最大值。如：   
$dp_{i,0}$ 表示第 $i$ 个数没有用魔法时的最大字段和。  
$dp_{i,1}$ 表示第 $i$ 个数正在使用魔法时的最大字段和。  
$dp_{i,2}$ 表示第 $i$ 个数使用玩魔法之后的最大字段和。  

接着，我们要推状态转移方程，一共三个。它们都可以由[最大字段和](https://www.luogu.com.cn/problem/P1115)里的状态转移方程推出来。这里直接给出，不多做说明。  
1. $dp_{i,0}=\max(dp_{i-1}+a_i,0)$
2. $dp_{i,1}=\max(dp_{i,0},dp_{i-1,1}+a_i\times x)$
3. $dp_{i,2}=\max(dp_{i,1},dp_{i-1,2}+a_i)$

最后在用一个变量去存 $dp_{i,2}$ 中的最大值，并输出就行了。  

附代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x;
long long a[300001];
long long dp[300001][3];
long long maxx;
int main(){
	cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        dp[i][0]=max(dp[i-1][0]+a[i],0+n-n);
		dp[i][1]=max(dp[i][0],dp[i-1][1]+a[i]*x);
		dp[i][2]=max(dp[i][1],dp[i-1][2]+a[i]);
		maxx=max(maxx,dp[i][2]);
    }
    cout<<maxx;
	return 0;
}
```

---

## 作者：gesong (赞：1)

题目传送门：[CF1155D](https://www.luogu.com.cn/problem/CF1155D)
# 思路
这道题一看就是 **dp**。

**状态表示**：$f_{i,0}$ 表示在第 $i$ 位，没有使用魔法 $f_{i,1}$表示在第 $i$ 位，正在使用魔法 $f_{i,3}$ 表示表示在第 $i$ 位，已经使用完魔法。
**状态转移**：

$f_{i,0}$ 转移：

由于没有使用魔法，直接从上一个转移即可，注意要加上现在的数,就是 $f_{i-1,0}+a_{i}$。

所以方程为：  $ f_{i,0}=\max(f_{i-1,0}+a_{i},0) $。

至于为什么要加上 $0$,是因为有可能是负数，比如样例 $3$,取 $0$ 更划算。

$f_{i,1}$ 转移：

从没有使用魔法即 $f_{i,0}$ ,与上一个数进行用正在用魔法的值即 $f_{i-1,1}$ 加上当前值获得魔法的值即 $a_i\times x$ ，最后取最大值即可。

所以方程为： $f_{i,1}=\max(f_{i,0},f_{i-1,1}+a_i\times x)$。

$f_{i,2}$ 转移：

从正在使用魔法即 $f_{i,0}$ ,与上一个数进行用已经用完魔法的值即 $f_{i-1,2}$ 加上当前值获得值即 $a_i$ ，最后取最大值即可。

所以方程为： $f_{i,2}=\max(f_{i.1},f_{i-1,2}+a_i)$。

最后答案就是前三种的最大值即： $ans=\max(ans,f_{i,0},f_{i,1},f_{i,2})$。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[1234567][3],a[1234567]; 
main(){
	int n,x,ans=-1e9;
	cin>>n>>x;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++){//方程转移
		f[i][0]=max(f[i-1][0]+a[i],(int)0);
		f[i][1]=max(f[i][0],f[i-1][1]+a[i]*x);
		f[i][2]=max(f[i][1],f[i-1][2]+a[i]);
		ans=max(ans,max(f[i][0],max(f[i][2],f[i][1])));//计算最大值
	}
	cout <<ans;
    return 0;
}

```

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
给定一个序列 $a$，你可以选择一个子串乘上 $k$，求最大字段和。

首先提醒一下各位，不要认为 $k$ 是负数就一定不优。众所周知，dp 是维护最大子段和的主要方法，所以考虑 dp。这题比较板子。接下来可以发现有三个状态：
- 没有使用魔法的时候。
- 正在使用魔法的时候。
- 使用完了魔法的时候。

不难想到在 $dp_i$ 中加三个子空间存储三种状态的最大字段和，即 $dp_{i,0}$、$dp_{i,1}$、$dp_{i,2}$。然后打擂台即可。

接下来求状态转移方程：
### $dp_{i,0}$
没有乘法操作，只有用上一个加上 $a_i$ 即可，但由于可能有负数，所以和 $0$ 作比较。

> 状态转移方程：$dp_{i,0}=\max(0,dp_{i-1,0}+a_i)$。
### $dp_{i,1}$
相比 $dp_{i,0}$，这一次需要将 $a_i$ 乘 $k$。

> 状态转移方程：$dp_{i,1}=\max(\max(0,dp_{i-1,1}+a_i),dp_{i-1,0}+a_i \times k)$。
> 
由于 $\max(0,dp_{i-1,0}+a_i)$ 已经在 $dp_{i,0}$ 中求出了，可以进一步精简为：
> $dp_{i,1}=\max(dp_{i,0},dp_{i-1,1}+a_i \times k)$。
### $dp_{i,2}$
魔法已经用完了，所以状态转移方程应该是：
> $dp_{i,2}=\max(dp_{i,1},dp_{i-1,2}+a_i)$。
## 代码
[AC记录](https://codeforces.com/problemset/submission/1155/291785777)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=876268;
int n,k,x,dp[N][3];
int maxans=-INT_MAX;
signed main(){
	cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>x;
		int a=dp[i-1][0],b=dp[i-1][1],c=dp[i-1][2];
        dp[i][0]=max(0ll,a+x);
		dp[i][1]=max(dp[i][0],b+x*k);
		dp[i][2]=max(dp[i][1],c+x);
		maxans=max(maxans,dp[i][2]);
    }
    cout<<maxans;
	return 0;
}
```

---

## 作者：luan341502 (赞：0)

典型的子串划分三段式 dp。

将原序列划分成三个子串，第一个和第三个不使用魔法，第二个使用魔法。

设 $f_{i,0/1/2}$ 分别为第一、二、三个子串，进行 dp 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[300005];
long long ans=0,f[300005][3];
void solve(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i][0]=max(f[i-1][0]+1ll*a[i],0ll);
		f[i][1]=max(max(f[i-1][0],f[i-1][1])+1ll*a[i]*x,0ll);
		f[i][2]=max(max(f[i-1][1],f[i-1][2])+1ll*a[i],0ll);
		ans=max(ans,max(max(f[i][0],f[i][1]),f[i][2]));
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	/*int tt;cin>>tt;while(tt--)*/solve();
	return 0;
}
```


---

## 作者：_Flame_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1155D)

## 思路

一道 $\text{dp}$ 题

考虑状态数组 $dp_{i,j}$ 其中 $i$ 表示当前位置的下标编号，第二位 $j$ 表示是否使用魔法。

这里分三种情况，当 $j$ 等于零时，表示还没有使用魔法，此时转移方程为$dp_{i,0}=\max(0,dp_{i-1,0}+a_{i})$，当 $j$ 等于一时，代表正在使用魔法，此时的转移方程为 $dp_{i,1}=\max(dp_{i,0},dp_{i-1,1}+a_{i}\times x)$，当 $j$ 等于二时，代表已经使用过魔法，此时的转移方程为 $dp_{i,2}=\max(dp_{i,1},dp_{i-1,2}+a_{i})$。

最后求最大值输出即可。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=500050;

int n;
int x;
int a[maxn];
int dp[maxn][5];
int ans=0;

signed main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		dp[i][0]=max(0ll,dp[i-1][0]+a[i]);
		dp[i][1]=max(dp[i][0],dp[i-1][1]+x*a[i]);
		dp[i][2]=max(dp[i][1],dp[i-1][2]+a[i]);
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[i][2]);
	}
	cout<<ans<<endl;
}
```



---

## 作者：_xyp (赞：0)

## 解析：
 观察题目我们可以知道
- 问题可以转化为求a数组中最大的子段和，利用动态规划来求解
- 这里我们使用一个sum数组来存储前i项的子段和
#### 根据题目：
- 使用一个minl来不断更新累加到现在的前i项的最小值
- 使用一个max数组来存储更新至当前的最大值 
- 使用ans来记录最终的答案的值（即最大值）
#### 可以得到以下式子

$	  	minl=min(minl,sum[i]*1ll*x-maxl[i])$
$		ans=max(ans,maxr[i+1]+sum[i]*1ll*x-minl)$

#### 由于这里的a[i]的范围，所以我们要在不断更新的过程中转化成longlong型来进行计算,即使用1ll强制类型转换
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int a[301180];
ll sum[301180],maxl[301180],maxr[301180];
int main()
{
    int n,x,y;
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;i++)
    {
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
    }
    for(int i=1;i<=n;i++)
    {
        maxl[i]=maxl[i-1]+a[i];
        if(maxl[i]<0)
            maxl[i]=0;
    }
    for(int i=n;i>=1;i--)
    {
        maxr[i]=maxr[i+1]+a[i];
        if(maxr[i]<0)
            maxr[i]=0;
    }
    ll ans=0,minl=0;
    for(int i=1;i<=n;i++)
    {
        minl=min(minl,sum[i]*1ll*x-maxl[i]); 
        ans=max(ans,maxr[i+1]+sum[i]*1ll*x-minl);
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

