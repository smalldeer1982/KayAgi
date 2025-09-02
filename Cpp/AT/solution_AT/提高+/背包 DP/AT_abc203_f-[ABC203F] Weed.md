# [ABC203F] Weed

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc203/tasks/abc203_f

高橋君と青木君の家の庭には草 $ 1 $, 草 $ 2 $, $ \ldots $, 草 $ N $ の $ N $ 本の草が生えており、草 $ i $ の高さは $ A_i $ です。 高橋君と青木君は次の方法で庭の草抜きを行う事にしました。

- まず、青木君が高々 $ K $ 本の草を選んで抜く。
- その後、高橋君が次の操作を庭の草がすべて抜けるまで繰り返す。
  
  
  - 残っている草のうち高さが最大のものの高さを $ H $ とする。残っている草のうち、高さが $ \frac{H}{2} $ より高いものを一斉に抜く。

青木君は、高橋君の操作回数が最小となるようにした上で、自分の抜く本数を最小にしたいと考えています。 このときの高橋君の操作回数と青木君の抜く草の本数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ K\ \leq\ N $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力は全て整数である。

### Sample Explanation 1

例えば青木君が草 $ 4 $ (高さ $ 9 $) を選んで抜いたとき、残りの草の中で最も高いものは草 $ 3 $ であり、その高さは $ 4 $ です。 $ \frac{4}{2}=2 $ であり、$ 2\ <\ 3 $, $ 2\ <\ 4 $ より $ 1 $ 回目の操作で高橋君は草 $ 2 $ と草 $ 3 $ のみを抜くことができます。その後、 $ 2 $ 回目の操作で草 $ 1 $ を抜き、高橋君は $ 2 $ 回で操作を終えることができます。 一方で、青木君がどの草を $ 1 $ 本選んだとしても高橋君は $ 1 $ 回で操作を終えることはできません。 また、もし青木君が $ 1 $ 本も抜かなかったとすると高橋君は $ 3 $ 回操作する必要があるため、青木君は高橋君の操作回数を最小にするために最低 $ 1 $ 本は抜かなくてはなりません。

### Sample Explanation 2

青木君が全ての草を抜いたとき高橋君は操作を行う必要がなく、明らかにこのときが最小です。

## 样例 #1

### 输入

```
4 1
2 3 4 9```

### 输出

```
2 1```

## 样例 #2

### 输入

```
3 3
2 3 5```

### 输出

```
0 3```

## 样例 #3

### 输入

```
9 8
137 55 56 60 27 28 133 56 55```

### 输出

```
1 4```

# 题解

## 作者：nxd_oxm (赞：7)

首先肯定要从小到大排序。我们可以设计一个最脑残的 dp：$dp_{i,j}$ 表示在前 $i$ 个草中拔掉 $j$ 个最小的操作次数。转移：

$$dp_{i,j}=\min(dp_{i-1,j-1},dp_{low_i,j}+1)$$

其中 $low_i$ 表示拔掉第 $i$ 个草的最小能影响到的编号减一，可以双指针或者二分维护。转移的意思是要不然就拔掉第 $i$ 个草，要不然就在第 $i$ 个草这里操作一次。

注意到状态数 $\mathcal{O}(nk)$。观察题面，其实我们是按两个关键字来排序答案：先是按操作次数排序，再按拔掉的草的个数排序。发现操作次数的最大值是 $\mathcal{O}(\log_2W)$ 级别的（$W=10^9$），而拔掉的草的个数是 $\mathcal{O}(k)$ 级别的，对于这种不对称的式子我们就可以将状态与值反过来。定义 $dp_{i,j}$ 表示在前 $i$ 个草中操作 $j$ 次时最小拔掉的草的个数。转移：

$$dp_{i,j}=\min(dp_{i-1,j}+1,dp_{low_i,j-1})$$

时间复杂度 $\mathcal{O}(n\log_2W)$。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(long long i=j;i<=n;i++)
#define updmax(a,b) a=max(a,b)
#define updmin(a,b) a=min(a,b)
#define pb push_back
using namespace std;
int n,k,a[200010],dp[200010][40],low[200010];
void gs(){
	cin>>n>>k;
	f(i,1,n)cin>>a[i];
	sort(a+1,a+1+n);
	f(i,1,n){
		int u=lower_bound(a+1,a+1+n,(a[i]/2)+1)-a;
		low[i]=u-1;
	}
	f(i,1,n){
		f(j,0,31){
			dp[i][j]=dp[i-1][j]+1;
			if(j)updmin(dp[i][j],dp[low[i]][j-1]);
		}
	}
	int ans=LLONG_MAX/2,o=0;
	f(j,0,30){
		if(ans>j&&dp[n][j]<=k){ans=j;o=dp[n][j];}
	}
	cout<<ans<<" "<<o<<endl;
}
signed main(){gs();return 0;}
```

---

## 作者：tyr_04 (赞：7)

[传送门](https://www.luogu.com.cn/problem/AT_abc203_f)

## 题意

给你 $n$ 个数 $a_{1...n}$，定义一次操作为：每次选择最大的数 $a_i$，并将所有大于 $\lfloor \frac{a_i}{2} \rfloor$ 的数删除。

在进行操作前可以提前删除任意 $k$ 个数，问你在删完所有数时保证操作数尽量小的最低提前删数次数。

## 思路

一眼动态规划。

定义 $dp_{i,j}$ 表示还剩前 $i$ 小的数时操作数为 $j$ 的最小删数次数。

注意到每次删数后会使大于最大值的 $\frac{1}{2}$ 个数全部删除，所以最多操作 $\log_2(A)$ 次就可以把所有数删完，其中 $A$ 是 $a_{1...n}$ 的最大值，所以 $j$ 最大为 $30$ 左右。

接下来的思路就显而易见了，将 $a$ 数组排序从小到大，再从大往小转移，找到 $a$ 的值小于等于 $\lfloor \frac{a_i}{2} \rfloor$ 的最大位置 $r$（可以使用二分），每次转移有两种情况：

+ 在操作开始前删除这个数：$dp_{i-1,j}=\min(dp_{i,j}+1,dp_{i-1,j});$

+ 在操作时删除这个数：$dp_{r,j+1}=\min(dp_{i,j},dp_{r,j+1});$

答案就是 $p$ 和 $dp_{0,p}$ 了，其中 $p$ 表示满足 $dp_{0,p} \le k$ 的最小值。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[200005],dp[200005][35];
bool cmp(int x,int y)
{
	return x<y;
}
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=30;j++)
		{
			dp[i][j]=INT_MAX;
		}
	}
	dp[n][0]=0;
	for(int i=n;i>=1;i--)
	{
		int p=a[i]/2,l=1,r=i;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(a[mid]<=p)
			{
				l=mid+1;
			}
			else if(a[mid]>p)
			{
				r=mid-1;
			}
		}
		for(int k=0;k<=30;k++)
		{
			dp[i-1][k]=min(dp[i][k]+1,dp[i-1][k]);
			dp[r][k+1]=min(dp[i][k],dp[r][k+1]);
		}
	}
	int ans1=INT_MAX,ans2=INT_MAX;
	for(int i=0;i<=30;i++)
	{
		if(dp[0][i]!=INT_MAX&dp[0][i]<=k)
		{
			ans1=i;
			ans2=dp[0][i];
			break;
		}
	}
	cout<<ans1<<' '<<ans2;
	return 0;
}
```

---

## 作者：_Deer_Peach_ (赞：6)

题意：

~~你重生了，成为了一个除草机。~~

有 $n$ 处草，你可以提前除掉不超过 $k$ 株草，然后先找到剩余草中最高的草，高度为 $a_i$，然后除掉高度小于 $\lfloor\frac{a_i}{2}\rfloor$ 的草，求在除完所有草时并保证操作数尽量小的最低提前除草次数。

思路：

动态规划。

状态定义：

$dp_{i,j}$ 表示除去前 $i$ 株草操作 $j$ 次的最小提前除草次数。

每次操作除去比最高草的高度的一半低的草，最坏情况就是只能除一株草，也就是次高的草是最高草的高度的一半，设最高草的高度为 $h$，那么最多操作次数为 $\log_2(h)$ 次，约为 $30$。

越高的草能使除去的草更多，所以优先除低的草。所以先将草的高度排序。

状态转移：

除去第 $i$ 株草有两种方法：
1. 提前除草：$dp_{i,j} \gets dp_{x,j-1}$；
2. 操作除草：$dp_{i,j} \gets dp_{i-1,j}+1$。

所以最后的转移方程就是 $dp_{i,j} \gets \min(dp_{i-1,j-1},dp_{x,j}+1)$。其中 $x$ 是低于第 $i$ 株草高度一半的草中最高的草最大的下标（可以用二分求）。

最后答案只要遍历操作次数，遇到一个有答案的 $i$ 就直接输出 $i$ 和 $dp_{n,i}$。
代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int N=2e5+5;
const int Max=0x3f3f3f3f3f3f3f3f,Min=-Max;
int n,k,a[N],dp[N][35];//dp[i][j]表示除前i株草操作j次需要提前除多少草
signed main(){
    IOS;cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n==k){cout<<0<<" "<<k;return 0;}//如果n=k可以全部提前除去，操作次数为0
	sort(a+1,a+n+1);
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=k;i++)dp[i][0]=i;//初始化
	for(int i=1;i<=n;i++){
		int l=1,r=i,mid;
		while(l<r){//二分
			mid=l+r>>1;
			a[mid]>a[i]/2?r=mid:l=mid+1;
		}for(int j=1;j<=30;j++)
			dp[i][j]=min(dp[i-1][j]+1,dp[r-1][j-1]);//状态转移
	}for(int i=0;i<=30;i++)
		if(dp[n][i]<=k){cout<<i<<" "<<dp[n][i];return 0;}
	return 0;
}
```

---

## 作者：KAxdd (赞：3)

## 题意
一共 $n$ 个数字，你可以选择提前拿走一些，接着每次可以选择一个未被删除的数  $a_i$ 进行删除，删除所有序列中大于 $\left \lfloor \frac{a_i}{2} \right \rfloor $ 的数，至多拿走 $k$ 个，求删除数最少的前提下拿走的数量最少。

## 解答

很明显我们先要按照大小排序，我们考虑暴力dp，设 $f_{i,j}$ 为做到了第 $i$个数字,一共提前拿掉了 $j$ 个数的最小转移次数，其中我们设 $to_i$ 为选择了第 $i$ 个数字所不能能的第一个数字的位置，显然能得到以下式子。

$$f_{i,j}=\min (f_{i+1,j})$$

$$f_{to_i,j}=\min (f_{i,j}+1)$$

这个题目最明显可以发现 $\left \lfloor \frac{a_i}{2} \right \rfloor $ 这样的操作最多会执行 $\log n$ 次，也就是说我们dp数组内最大值也只有 $\log n$ 所以我们直接考虑把状态互换，式子不变。接着从最小的选起，看提前选择的数字是否满足要求即可。

时间复杂度 $O(n \log n)$

PS：感觉这道题并没有过多的思维空间，建议评绿。

### ACcode
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[200005][55],a[200005],to[200005];
signed main() {
    int n,k;
    scanf("%lld %lld",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    int now=0;
    for(int i=1;i<=n;i++) {
        while(a[now+1]<=a[i]/2) now++;
        to[i]=now;
    }   
    memset(f,0x3f,sizeof f);
    f[n][0]=0;
    for(int i=n;i>=1;i--) {
        for(int j=0;j<=30;j++) {
            f[i-1][j]=min(f[i-1][j],f[i][j]+1);
            f[to[i]][j+1]=min(f[to[i]][j+1],f[i][j]);
        }
    }
    for(int i=0;i<=30;i++) {
        if(f[0][i]<=k) {
            printf("%lld %lld\n",i,f[0][i]);
            return 0;
        }
    }
    return 0;
}
```



---

## 作者：dulinfan2023 (赞：3)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc203_f)

## 思路讲解

- 首先使 $x=\max^n_{i=1}a_i $，易得至多进行 $\log_2 x$ 次，则使用 $dp$。

- 先对 $a$ 数组进行升序排序，用 $dp_{i,j}$ 表示用 $j$ 次操作拔掉前 $i$ 株草的最少预处理的草数。

- 那么很容易就可以知道转移方程式为：
$$dp_{i,j}= \min(dp_{i-1,j}+1,dp_{i^{'},j})$$
     
- 其中 $i^{'}$ 为使 $a_{i^{'}} \le \lfloor \frac{a_i}{2} \rfloor$ 的最大 $i^{'}$，只需预处理出每个 $i^{'}$ 即可。

- 答案就是满足 $dp_{n,m}\le k$ 的最大的 $m$ 和 $dp_{n,m}$。

- 时间复杂度是 $O(n \log n+n \log x)$。

### AC代码 $:$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
#define debug() cout<<"come on"<<'\n'
int n,k,a[200005],dp[200005][105],can[200005];
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		can[i]=upper_bound(a,a+1+n,a[i]/2)-a-1;
	}
	for(int i=1;i<=n;i++){
		dp[i][0]=i;
		for(int j=1;j<=55;j++){
			dp[i][j]=min(dp[i-1][j]+1,dp[can[i]][j-1]);
		}
	}
	for(int i=0;i<=55;i++){
		if(dp[n][i]<=k){
			cout<<i<<" "<<dp[n][i];
			return 0;
		}
	}
	return 0;
}

```

不可以抄代码哦 $!$

---

## 作者：Ooj_bai (赞：2)

首先看到 $2 \times 10^5$ 的数据范围猜想是贪心，但是手玩了一下样例发现似乎并没有什么特点。但仍考虑到每次选择的草的高度一定单调递减，于是先对数组进行排序。

接下来考虑 dp。我们考察每次拔除草的过程，就是每次将大于原最大值的部分除去。这个过程最多只会进行 $\log_2V$，（$V$ 为值域）次，因为每次操作后的最大值一定小于等于操作前最大值的一半。于是猜测 dp 状态中大概有这一项。

后面的步骤就顺理成章了，定义 $dp_{i,j}$ 为前 $i$ 个数高桥操作 $j$ 次的最小青木操作次数。边界为 $dp_{0,0}=1$，统计答案为找到第一个 $i$,使得 $dp_{n,i}\le k$。同时有转移：

$$dp_{i,j}=\min(dp_{i-1,j}+1,\min_{\frac{a_i}{2}<a_k,k<i}\{dp_{k,j-1}\})$$

这个转移是 $O(n)$ 的，不够快。但是发现由第一个满足条件的 $k$ 之后的状态转移来一定是不优的。可以使用双指针或二分找到第一个可转移点，由它转移即可。  
复杂度 $O(n\log n +n\log V)$，$V$ 为值域。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 200005
using namespace std;
int n,k;
int a[maxn],dp[maxn][50];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	memset(dp,0x3f,sizeof dp);
	sort(a+1,a+n+1);
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=40;j++){
			dp[i][j]=dp[i-1][j]+1;
			int last=upper_bound(a+1,a+i+1,a[i]/2)-a-1;
			if(j>0)dp[i][j]=min(dp[i][j],dp[last][j-1]);
		}
	}
	for(int i=0;i<=40;i++){
		if(dp[n][i]<=k){
			cout<<i<<' '<<dp[n][i];
			break;
		}
	}
	return 0;
} 
```

---

## 作者：Louis_lxy (赞：2)

## 前言

感觉这整场 abc 就这题有难度啊，其他的都很简单啊。

## 思路

难度中等的 dp。

首先对答案排序，原因是根据贪心思想，一定是预先拔掉较小的草，较大的草能一次拔掉的草数更多。然后发现最多拔 $\log n$ 次，因此考虑 dp。记 $f(i,j)$ 表示拔掉前 $i$ 株草，后期拔 $j$ 次，最少需要预先拔掉的数量。

首先考虑初始值，首先初始成极大值，由于上文说的贪心思想，对于 $0\le i\le n$，有 $f(i,0)=i$。

然后考虑 dp 方程，分类讨论。

- 预先拔掉第 $i$ 株草，结果为 $f(i-1,j)+1$。
- 后期拔掉所有高度大于 $\lfloor \frac{h_i}{2}\rfloor$ 的草，记最后一株被拔掉的编号为 $p$，结果为 $f(p,j-1)$。

综上，dp 方程为 $f(i,j)=\min(f(i-1,j)+1,f(p,j-1))$。

最后再从小到大扫一遍，输出最小满足题意的即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;
int n, k, a[N], f[N][32];

int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	memset(f, 127, sizeof f);
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (i <= k) f[i][0] = i;
		int p = upper_bound(a + 1, a + i + 1, a[i] / 2) - a - 1;
		for (int j = 1; j < 32; ++j)
			f[i][j] = min(f[i - 1][j] + 1, f[p][j - 1]);
	}
	for (int i = 0; i < 32; ++i)
		if (f[n][i] <= k)
		{
			printf("%d %d", i, f[n][i]);
			return 0;
		}
	return 0;
}
```

---

## 作者：Pyrf_uqcat (赞：1)

简单题意。有 $n$ 个草，你可以在除草之前先任选不超过 $k$ 个草除掉。然后开始操作：找到最高的草，除掉所以高度大于最高草一半的草。求最小操作次数。

状态定义：

用 $dp_{i,j}$ 表示经过 $j$ 次操作剩下前 $i$ 小的草时的最小提前除草数。

注意：考虑到前 $i$ 小的草，输入后先将草的高度排序。

初始化：

求最小，将所有值调最大，并把未开始操作所有草都完好时的提前除草数设为 $0$。


```cpp
memset(dp,0x3f,sizeof(dp));
dp[n][0]=0;
```

转移公式：


```cpp
dp[i-1][k]=min(dp[i][k]+1,dp[i-1][k]);
//提前除掉这个草
dp[r][k+1]=min(dp[i][k],dp[r][k+1]);
//不提前除掉这个草
```

其中 $r$ 表示的是高度大于最高草一半的草的下标，需要用二分寻找。

答案：

找第一个 $dp_{i,0}$ 小于等于 $k$ 的。

```cpp
for(int i=0;i<=30;i++)
{
	if(dp[0][i]<=k)
	{
		mi=i;
		ans=dp[0][i];
		break;
	}
}
cout<<mi<<' '<<ans<<endl;
```

### 代码


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include <bits/stdc++.h>
#define int long long 

#define N 200005

using namespace std;

int n,k,a[N];

int dp[N][55];

bool check(int mid,int x)
{
	return a[mid]<=a[x]/2;
}

signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	memset(dp,0x3f,sizeof(dp));
	dp[n][0]=0;
	for(int i=n;i>=1;i--)
	{
		int l=1,r=i;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check(mid,i)) l=mid+1;
			else r=mid-1;
		}
		for(int k=0;k<=30;k++)
		{
			dp[i-1][k]=min(dp[i][k]+1,dp[i-1][k]);
			dp[r][k+1]=min(dp[i][k],dp[r][k+1]);
		}
	}
	int mi=INT_MAX,ans=INT_MAX;
	for(int i=0;i<=30;i++)
	{
		if(dp[0][i]<=k)
		{
			mi=i;
			ans=dp[0][i];
			break;
		}
	}
	cout<<mi<<' '<<ans<<endl;
	return 0;
}

```

---

## 作者：Swirl (赞：1)

> dp。

每次将大于 $\lfloor\frac{h}{2}\rfloor$ 的数删掉，则最多操作 $\log h$ 次，即最多操作 $30$ 次。

考虑 dp。

先将数组排序。

定义 $dp(i, c)$ 为前 $i$ 个数删完用了 $c$ 步的最小预先删掉数的个数。

显然，$dp(i, c)$ 可以预先删掉，故可以从 $dp(i - 1, c)$ 转移而来。

如果我们在一次操作中删掉 $i$，那么会使得所有 $a_t \in \left (\lfloor\frac{a_i}{2}\rfloor, a_i \right ]$ 的 $t$ 被删掉。

我们只需要二分处理出最大的，且不会被删掉的数的下标 $f$ 并从 $dp(f, c - 1)$ 转移即可。

状态转移方程：

$$
dp(i, c) = \min\{dp(i - 1, c) + 1, dp(f, c - 1)\}
$$

注意一下边界条件。

---

```cpp
namespace zqh {
const int N = 200005, R = 30;

int n, k, a[N], dp[N][R + 5], p;

void init() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
}

void solve() {
    p = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        int f = upper_bound(a, a + n + 1, a[i] / 2) - a - 1;
        for (int c = 0; c <= R; c++) {
            dp[i][c] = min(dp[i - 1][c] + 1, (c ? dp[f][c - 1] : LLONG_MAX));
            if (i == n && dp[i][c] <= k) {
                p = min(p, c);
            }
        }
    }
    cout << p << " " << dp[n][p];
}

void main() {
    init();
    solve();
}
}  // namespace zqh
```

---

## 作者：DaiRuiChen007 (赞：1)

# ABC203F 题解



## 思路分析

记 $w=\max_{i=1}^n \{a_i\}$，即 $a_i$ 的值域。

观察到操作次数不超过 $\log_2 w$ 次，因此考虑 dp。

先对 $a_i$ 升序排序，用 $dp_{i,j}$ 表示进行 $j$ 次操作拔掉前 $i$ 棵的草，最少需要预处理掉多少草。

那么状态转移方程如下：
$$
dp_{i,j}=\min\{dp_{i-1,j}+1,dp_{i',j}\}
$$
其中 $i'$ 是满足 $a_{i'}\le\left\lfloor\dfrac{a_i}2\right\rfloor$ 的最大 $i'$，两个转移分别表示拔掉第 $i$ 棵草和预处理掉第 $i$ 棵草。

显然先预处理出所有 $i'$ 后暴力转移即可。

答案是满足 $dp_{n,j}\le k$ 的最大 $j$ 和对应的 $dp_{n,j}$。

时间复杂度 $\Theta(n\log n+n\log w)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int a[MAXN],lst[MAXN],dp[MAXN][51];
signed main() {
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) lst[i]=upper_bound(a,a+n+1,a[i]/2)-a-1;
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;++i) {
		dp[i][0]=dp[i-1][0]+1;
		for(int j=1;j<=50;++j) {
			dp[i][j]=min(dp[i-1][j]+1,dp[lst[i]][j-1]);
		}
	}
	for(int i=0;i<=50;++i) {
		if(dp[n][i]<=k) {
			printf("%d %d\n",i,dp[n][i]);
			break;
		}
	}
	return 0;
} 
```



---

## 作者：Kawaii_qiuw (赞：0)

题意不再赘述。

### 思路

由于特殊操作 $\lfloor\frac{H}{2}\rfloor$ 在，不难发现，操作次数是 $\log N$ 级别的。

将杂草高度排序，直接枚举操作次数，记 $f_{i,j}$ 为第 $i$ 次操作到 $j$ 杂草为止拔草的最大数目。

$$f_{i-1,k}+\sum_{a_k>\lfloor\frac{a_j}{2}\rfloor,k\le j}1 =  f_{i,j}$$
 

最后滚动掉 $i$ 这一维即可。

### 代码


```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 200005
int f[2][maxn];
int a[maxn];
int n, k;

int main() {
	scanf( "%d %d", &n, &k );
	for( int i = 1;i <= n;i ++ )
		scanf( "%d", &a[i] );
	if( n == k ) return ! printf( "0 %d\n", n );
	sort( a + 1, a + n + 1 );
	int ans = 0;
	for( int i = 1;i <= 31;i ++ ) {
		int ip = 0, maxx = 0;
		for( int j = 1;j <= n;j ++ ) {
			while( ip < n && a[ip + 1] <= a[j] / 2 )
				maxx = max( maxx, f[i & 1 ^ 1][++ ip] );
			f[i & 1][j] = maxx + j - ip;
			ans = max( ans, f[i & 1][j] );
		}
		if( ans >= n - k ) return ! printf( "%d %d\n", i, n - ans );
	}
	return 0;
}
```

完结撒花。

---

## 作者：Kexi_ (赞：0)

朴素的动态规划！

设 $f_{i,j}$ 表示前 $i$ 个草操作 $j$ 次全部拔光所需要的预处理次数。

直接转移即可，想要拔掉一个草有两种方式。一种是在一开始预处理他，另一种是在他的位置进行一次操作，这样他自己一定也会被拔除。

由于这个问题跟顺序没什么关系，所以我们可以直接把原数组排序后操作即可。

操作数一定是小于 $O(\log_2 W)$ 的。原因就是我们可以选择每次都在最高的草处操作，每次把最高的草的一半高度以上的草全拔了，最终一定能拔完。

$\log_2 5 \times 10 ^ 9 = 30$。 


```cpp
#include <bits/stdc++.h>
#define ri register int
#define N 200005
#define int long long
#define inf 0x3f3f3f3f
using namespace std;
int n,k;
int a[N],dp[N][35];
signed main()
{
	cin>>n>>k;
	for(ri i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	memset(dp,inf,sizeof(dp));
	dp[0][0]=0;
	for(ri i=1;i<=n;i++){
		for(ri j=0;j<=30;j++){
			dp[i][j]=dp[i-1][j]+1;//直接预处理掉他
			int lst=upper_bound(a+1,a+i+1,a[i]/2)-a-1;//把h/2以上的草都拔了，那么可以直接从第一个小于h/2的草处转移
			if(j) dp[i][j]=min(dp[i][j],dp[lst][j-1]);
		}
	}
	for(ri i=0;i<=30;i++){
		if(dp[n][i]<=k){
			cout<<i<<' '<<dp[n][i];
			break;
		}
	}
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

模拟赛赛题，假贪心居然取得了 27pts 的高分 /jy

---

贪心很有些问题，我们考虑 dp。

排序显然不影响答案，所以先对原序列排序。

设 $dp_{i,j}$ 表示前 $i$ 个草里操作 $j$ 次以后若要使清空最少需要提前拔草的数量。

操作次数是 $\log$ 级别的，所以空间十分足够。

同时对于每一个 $i$ 将当前 $a_i$ 拔了以后影响不到的草中最靠后的草编号记为 $b_i$。利用二分可以 $O(n \log n)$ 把 $b$ 求出来。

然后转移有对当前位置进行操作或者耗费拔草次数两种可能，取最小即可。

转移式子：

$$dp_{i,j}=\min(dp_{b_i,j-1},dp_{i-1,j}+1)$$

最后找到 $j$ 最小且 $dp_{n,j}<k$ 的就是答案。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],b[200005];
int dp[200005][55];
int ans=100,flc;
signed main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)b[i]=lower_bound(a+1,a+1+n,a[i]/2+1)-a-1;
    for(int i=1;i<=n;i++)
    for(int j=0;j<=31;j++){
        dp[i][j]=dp[i-1][j]+1;
        if(j)dp[i][j]=min(dp[i][j],dp[b[i]][j-1]);
    }
    for(int i=0;i<=31;i++)
    if(ans>i&&dp[n][i]<=k){
        cout<<i<<' '<<dp[n][i];
        return 0;
    }
    return 0;
}
```

---

## 作者：AKPC (赞：0)

首先，由于题目操作定义的特性，我们考虑将 $a_i$ 从小到大排序。

设 $dp_{i,j}$ 表示处理完 $[1,i]$ 下标区间内的草，且预先拔掉了 $j$ 根草之后的操作次数。显然有转移方程：

$$dp_{i,j}=\min(dp_{i-1,j-1},dp_{ls_i,j}+1)$$

前者的决策是预先拔掉第 $i$ 根草，后者则是对第 $i$ 根草进行一次操作。其中 $ls_i$ 表示高度 $\leq\frac{a_i}{2}$ 的草中最高的草的下标，使用双指针预处理。

发现操作的个数是 $\log V\leq30$ 级别，考虑维度与存储的信息互换，即设 $dp_{i,j}$ 表示处理完 $[1,i]$ 下标区间内的草，且操作 $j$ 次需要预先拔掉草的数量。转移方程有略微改动：

$$dp_{i,j}=\min(dp_{i-1,j}+1,dp_{ls_i,j-1})$$

[code](/paste/kf4lrhoa)。

---

## 作者：Fesdrer (赞：0)

首先将 $a$ **从大到小**排序，观察删除的过程，如果当前最大的数是 $x$，则删掉的所有大于 $\lfloor \frac x2\rfloor$ 的数刚好是当前 $a$ 的前缀。换句话说，不考虑预先删掉的数，假设当前删到 $a$ 的第 $i$ 个数，则下一次删掉的就是 $a$ 中下标位于 $[i+1,p(i+1)]$ 中的所有数，其中 $p(i+1)$ 是最大的满足 $a_p>\lfloor\frac x2\rfloor$ 的 $p$。而如果要预先删掉数呢？贪心地考虑，我们在一开始和每一次删掉一个区间的数后都可以继续删掉若干长度的区间的数作为预先删掉的数。举例来说，我们可以预先删掉 $a_1,a_2$，然后正常删掉 $a_3$ 到 $a_{p(3)}$，然后预先删掉 $a_{p(3)+1},a_{p(3)+2},a_{p(3)+3}$，然后正常删掉 $a_{p(3)+4}$ 到 $a_{p(p(3)+4)}$，以此类推，当然在某次正常删除后也可以不预先删除，直接进行下一次的正常删除。

于是我们可以设 $f_{i,j}$ 表示当前删到第 $i$ 个数，正常删除 $j$ 次，最少的预先删除的数的个数。转移则考虑下一步是正常删除还是继续预先删除，即 $f_{i,j}+1\rightarrow f_{i+1,j}$ 和 $f_{i,j}\rightarrow f_{p(i+1),j+1}$。考虑到我们最多正常删除 $\log_2(a_1)$ 次，因此时间复杂度是 $\mathcal O(n(\log(n)+\log(a_1)))$ 的。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,k,a[N],f[N][35];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)	cin>>a[i];
	sort(a+1,a+n+1),reverse(a+1,a+n+1);
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	for(int i=0;i<n;i++){
		int l=i+1,r=n;
		while(l<r){
			int mid=(l+r+1)/2;
			if(a[mid]>a[i+1]/2)	l=mid;
			else	r=mid-1;
		}
		for(int j=0;j<35;j++)	if(f[i][j]!=0x3f3f3f3f){
			f[i+1][j]=min(f[i+1][j],f[i][j]+1);
			f[l][j+1]=min(f[l][j+1],f[i][j]);
		}
	}
	for(int i=0;i<35;i++)	if(f[n][i]<=k){
		cout<<i<<" "<<f[n][i]<<endl;
		break;
	}
	return 0;
}
```

---

## 作者：high_sky (赞：0)

### 思路
由于每次选取最大的草后把所有大于它高度一半的都拔除，相当于最高的草的高度至少减半，所以最多操作 $\log a_i$ 次。

所以最小操作数完全可以枚举，我们只需要考虑在每种操作数的情况下最小化预先拔掉的草的数量。

把草按 $a$ 从小到大排序后，我们发现一次操作必定为一个区间，且区间右端点固定则左端点固定，预先拔掉的草就是除了区间覆盖的草以外的其它草，前后显然可转移。

所以设 $dp_{i,j}$ 表示操作 $j$ 次拔完前 $i$ 株草（当然是排序后）的情况下需要预先拔掉的草的数量的最小值，显然有:

$$
dp_{i,j}=\min(dp_{i-1,j}+1,dp_{p_i-1,j-1})
$$

其中 $p_i$ 表示 $i$ 左边的最靠左的高度大于 ⌊$\frac{a_i}{2}$⌋ 的草的下标，这个可以预先用二分或倍增处理出来。总复杂度 $O(n \log a)$。

### Code
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
#define ll long long
#define MAXN 200105
#define uns unsigned
#define MOD 998244353ll
#define INF 0x7f7f7f7f
using namespace std;
inline ll read(){
	ll x=0;bool f=1;char s=getchar();
	while((s<'0'||s>'9')&&s>0){if(s=='-')f^=1;s=getchar();}
	while(s>='0'&&s<='9')x=(x<<1)+(x<<3)+s-'0',s=getchar();
	return f?x:-x;
}
int n,k,a[MAXN],dp[MAXN][35],mn,mk;
signed main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+1+n);
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	mn=INF,mk=INF;
	for(int i=1;i<=n;i++){
		dp[i][0]=i;
		int p=i;
		for(int j=20;j>=0;j--)
			if(p-(1<<j)>0&&a[p-(1<<j)]>(a[i]>>1))p-=(1<<j);
		for(int j=0;j<=31;j++){
			dp[i][j]=min(dp[i][j],dp[i-1][j]+1);
			if(j>0)dp[i][j]=min(dp[i][j],dp[p-1][j-1]);
		}
	}
	for(int j=0;j<=31;j++){
		if(dp[n][j]<=k&&j<mn)mn=j,mk=dp[n][j];
		else if(dp[n][j]<=k&&j==mn)mk=min(mk,dp[n][j]);
	}
	printf("%d %d\n",mn,mk);
	return 0;
}

```

---

