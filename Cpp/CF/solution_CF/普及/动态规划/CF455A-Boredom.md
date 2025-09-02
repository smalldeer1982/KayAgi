# Boredom

## 题目描述

亚力克斯不喜欢无聊。

所以每当他感到无聊他就会想出一些游戏。一个冬天的晚上他想出了一个游戏并且决定开始玩这个游戏。

给定一个有 $n$ 个元素的序列 $\{a_n\}$。你可以做若干次操作。在一次操作中我们可以取出一个数（假设他为 $x$）并删除它，同时删除所有的序列中值为 $x+1$ 和 $x-1$ 的数。这一步操作会给玩家加上 $x$ 分。

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
9
1 2 1 3 2 2 2 2 3
```

### 输出

```
10
```

# 题解

## 作者：人间凡人 (赞：17)

####  题意:
 
有 $n$ 个数,每一次取一个 $x$ ,将其删除，并将所有值为 $x+1$ 与 $x-1$ 的数都删除,$ans$ 加上 $x$ ,求最后最大的 $ans$ 的值.

#### 思路：

因为我们可以注意到取一个 $x$ 后要将所有的值为 $x+1$ 与 $x-1$的数都给删除了,所以我们不妨统计出每一个数出现的次数，$num[i]$ 表示 $i$ 这个数出现的次数，因为 $1<=a[i]<=100000$ ,所以不会超空间，接下来就可以引出我们今天的主角—— $Dp$ 了 $!$

$Dp[i]$ 表示算到 $i$ 这个数时的最大分数为多少。

那么该如何转移呢，我们知道取一个 $x$ 后，这些 $num[x+1]$ 与 $num[x-1]$ 会被删除,所以就可以很容易的得到 $dp[i]=max(dp[i-1],dp[i-2]+num[i]*i);$

初始值：$dp[1]=num[1];$

答案：$dp[max(a[i])]$

$Code:$
```cpp
#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,x,N;
long long dp[M],num[M];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		num[x]++;
		N=max(N,x);
	}
	dp[1]=num[1];
	for(int i=2;i<=N;i++)
		dp[i]=max(dp[i-2]+num[i]*i,dp[i-1]);
	printf("%lld\n",dp[N]);
	return 0;
} 
```




---

## 作者：Cult_style (赞：10)

# 算法：DP
我看了看题解，用的都是一个方法，可是讲的好像不那么容易懂，我就写一篇题解吧。

先上递推式吧：

$dp[i]=max(dp[i-1],dp[i-2]+vis[i]*i)$

$vis[i]$表示第$i$个数出现的次数，$dp[i]$表示前$i$个数中，可以得到的最大得分

- $dp[i-1]$没什么好讲的，就是我们不取第$i$个物品

- $dp[i-2]+vis[i]*i$其实就是我们选第$i$个物品，$i-2$是因为$i-1$是题目上的$"x-1"$,我们要把它删掉，所以取$i-2$,然后$vis[i]*i$就是我们的分值，把$vis[i]$个$i$全取了，得到$vis[i]*i$

代码如下：

```
#include<bits/stdc++.h>
#define inf 0x7fffffff
#define MN 100005
#define ll long long
using namespace std;
ll n;
ll a[MN];
ll vis[MN],ma=-inf;
ll dp[MN];
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		ma=max(a[i],ma);
		++vis[a[i]];
	}
	dp[1]=vis[1];
	for(int i=2;i<=ma;++i){
		dp[i]=max(dp[i-1],dp[i-2]+vis[i]*i);
	}
	printf("%lld",dp[ma]);
	
	return 0;
}
```


---

## 作者：Allanljx (赞：4)

## 题意
有 $n$ 个数,每一次取一个 $x$，并将所有值为 $x+1$ 和 $x-1$ 的数都删除，每取一个数，就要加上被取的数，问最后被取的数的和最大时是多少。

## 思路
用 $a$ 数组统计每个数出现的次数， $a[i]$ 表示第 $i$ 个数出现的次数。

然后就该开始 $dp$ 了， $dp[i][0]$ 表示不取当前这个数， $dp[i][1]$ 表示取这个数。 $dp[i][0]=max(dp[i-1][0],dp[i-1][1])$ ，因为如果不取当前这个数，那么前一个数可以取也可以不取。
 $dp[i][1]=dp[i-1][0]+a[i]*i$ ，因为，如果取当前这个数，上一个数就不能取，但要加上这个数的个数乘这个数。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int m,a[100005],dp[100005][5];
signed main()
{
	int n,d=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>m;
		if(m>d) d=m;//记录最大的数 
		a[m]++;//每个数出现的个数
	}
	dp[1][1]=a[1];//初始化 
	for(int i=1;i<=d;i++)
	{
		dp[i][0]=max(dp[i-1][0],dp[i-1][1]);//不取 
		dp[i][1]=dp[i-1][0]+a[i]*i;//取 
	}
	cout<<max(dp[d][0],dp[d][1]);//最大值 
    return 0;
}
```


---

## 作者：Arghariza (赞：3)

先开个桶 $mp_i$ 把 $s_i$ 值出现的个数统计下来（题目说 $a_i≤10^5$，所以不用担心空间爆掉），把最大的数 $m$ 记录下来。

如果是暴力的话时间肯定会炸掉，所以考虑 $dp$ 。

定义 $dp$ 数组， $dp_i$ 表示取到 $i$ 时的最大值（或者你可以理解为在一个数列上覆盖长度为 $3$ 的线段，表示取到中间的值）。如果这里不选的话那么 $dp_{i-1}$ 和 $dp_{i-2}$ 肯定被选（因为此时如果 $dp_{i-2}$ 不选的话就肯定不能得出最大值），又因为这个数列一定是**递增**的，所以可以转移为 $dp_{i-1}$ ；如果这里被选了的话，我们实际上只能保证 $dp_{i-2}$ 被选了，而 $dp_{i-1}$ 并不能保证，所以转移为 $dp_{i-2}+mp_i\cdot i$ 。

所以 $dp$ 数组的状态转移方程为 $dp_i=max\{dp_{i-1},\ dp_{i-2}+mp_i\cdot i\}$ 。同时 $dp_1$ 为 $1$ 的个数 $mp_1$，最后输出 $dp_m$ 即可.

然后就是细节问题了，首先要记得开 $long\ long$ 。

```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 100001
using namespace std;

int n, m, s[maxn], mp[maxn], dp[maxn];

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &s[i]);
		m = max(m, s[i]);
		mp[s[i]]++;
	}
	dp[1] = mp[1];
	for (int i = 2; i <= m; i++) {
		dp[i] = max(dp[i - 1], dp[i - 2] + mp[i] * i);
	}
	printf("%lld", dp[m]);
	return 0;
}
```

---

## 作者：Fearliciz (赞：1)

~~这题是恶评吗？~~

其实这道题就是一道很普通的 $\texttt{dp}$ 题。 用 $\texttt{vn[i]}$ 来存储序列里 $\texttt{i}$ 出现的次数。开始错了好多次，最后才发现是忘了开 $\texttt{long long}$，溢出了。

所以就有了以下信息：

初值：$\texttt{f[1] = vn[1]}$。

转移：$\texttt{f[i]=max(f[i-1],f[i-2]+vn[i]*i)}$。

答案：$\texttt{f[max(x)]}$。

显然，$\texttt{f[i-1]}$ 表示不选，$\texttt{f[i-2]+vn[i]*i}$ 中的 $\texttt{vn[i]*i}$ 表示把 $\texttt{vn[i]}$ 个 $\texttt{i}$ 全选了。

以下为代码：

```cpp
#include<bits/stdc++.h>
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
#define ll long long
using namespace std;
const int NR=100005;
ll n,x,X;
ll f[NR],vn[NR];
int main()
{
	scanf("%d",&n);
	for(ll i=1;i<=n;i++){
		scanf("%d",&x);
		vn[x]++;
		X=max(X,x);
	}
	f[1]=vn[1];
	for(ll i=2;i<=X;i++)
		f[i]=max(f[i-1],f[i-2]+vn[i]*i);
	printf("%d\n",f[X]);
	return 0;
} 
```


---

## 作者：XL4453 (赞：1)

### 解题思路：

注意到 $a$ 的取值范围很小，只有不超过 $10^5$（中文翻译里好像没有提到，英文里有说），考虑从 $a$ 入手。

用 $f_{i,0/1}$ 表示当取到数 $i$ 时，$i$ 取（用 $1$ 表示）或不取（用 $0$ 表示） ，所能取到的最大价值。

对于 $f_{i,0}$，他可以从 $f_{i-1,0}$ 和 $f_{i-1,1}$ 转移过来，这一个转移不产生价值。

对于 $f_{i-1,1}$，则只能由 $f_{i-1,0}$ 转移过来，这一转移产生 $i$ 出现的次数与 $i$ 数值本身乘积的价值。

由于每一次的转移仅由之前的一个转移过来，可以用滚动数值压一下空间，不过没必要就是了。

---

### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,num[100005],x,f[100005][2],maxn;
int main(){
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		scanf("%lld",&x);
		maxn=max(maxn,x);
		num[x]++;
	}
	for(long long i=1;i<=maxn;i++){
		f[i][0]=max(f[i-1][1],f[i-1][0]);
		f[i][1]=f[i-1][0]+num[i]*i;
	}
	printf("%lld",max(f[maxn][0],f[maxn][1]));
	return 0;
}
```


---

## 作者：小豆子范德萨 (赞：0)

dp[i]代表从输入序列拿掉i这个数后所能够新获得的点数，定义一个cnt[i]代表i这个数在输入数组中出现的次数。
- 递归边界:dp[1] = cnt[1]。
- 接下来确定递归方向：因为每一次x,都可以在1-1e5范围内任意取值，但是拿出序列最大值以外的数对解决本题没有帮助。所以我们可以令i从2开始遍历到输入序列的最大值，对于dp[i]的递推我们可以有两种决策:
1）不取i这个数，那么状态转移到dp[i-1],(因为不取i，i-1这个数就不会被删除) 
2）把i这个数从序列中全部取出，那么dp[i] = dp[i-2]+i*cnt[i]（i-1被删除，考虑i-2）。取这两者的最大值赋值给dp[i]。

```cpp
#include <bits/stdc++.h>
using namespace std;
__int64 cnt[110000],dp[110000];
int main()
{
	long long n,i,j,k,l,m;
	cin>>n;
	memset(cnt,0,sizeof(cnt));
	memset(dp,0,sizeof(dp));
	int flag=0;
	for(i=0; i<n; i++) {
		scanf("%I64d",&m);
		cnt[m]++;
		if(m>flag)
			flag=m;
	}
	dp[1]=cnt[1];
	for(i=2; i<=flag; i++) {
		dp[i]=max(dp[i-1],cnt[i]*i+dp[i-2]);
	}
	printf("%I64d\n",dp[flag]);
	return 0;
}

```


---

## 作者：Roviky (赞：0)

dp题

但坑很多，细节需要注意

很明显是每隔一个数计算一次贡献

然而每次需要判断这个数该不该选[不选这个数x，选x+1和x-1时答案更大]

需要注意的是dp是内存不要访问超限2333333

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long maxn=711111;
long long n,big=-99999,ans=0,a[maxn],dp[maxn],cnt[maxn];
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
		cnt[a[i]]++;
		big=max(big,a[i]);
	}
	dp[0]=0;
	dp[1]=cnt[1];
	for(long long i=2;i<=max(big,n)+11111;i++){
		dp[i]=max(dp[i-1],dp[i-2]+i*cnt[i]);
		ans=max(ans,dp[i]);   //这个地方让我WA了十几次23333
	}
	cout<<ans<<endl;
	return 0;
} 

```

---

