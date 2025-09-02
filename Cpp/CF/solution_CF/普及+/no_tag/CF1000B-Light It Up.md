# Light It Up

## 题目描述

**题目大意：**

有一台灯，这个灯在时间为$0$时打开，$m$时关闭，在$0$到$m$这段时间内有$n$个时间点灯的状态会改变（即开变关，关变开），现在可以在**剩余**的时间点选一个让灯的状态改变一次，求这个灯最大亮着的时间

## 样例 #1

### 输入

```
3 10
4 6 7
```

### 输出

```
8
```

## 样例 #2

### 输入

```
2 12
1 10
```

### 输出

```
9
```

## 样例 #3

### 输入

```
2 7
3 4
```

### 输出

```
6
```

# 题解

## 作者：VenusM1nT (赞：4)

模拟。  
转换一下模型：若干条线段，只能取其中编号为奇数的，而我们可以切掉其中一条改变编号。  
再转换一下：若干条线段，我们可以不操作，也可以钦定其中的一条，这条前面的取奇数编号，后面的取偶数编号，然后对钦定的这一条，取它的 $\text{len}-1$，至此只需要枚举一下就可以了。
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
using namespace std;
int n,m,a[MAXN],b[MAXN],len[MAXN],sum1[MAXN],sum2[MAXN],ans;
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(reg int i=1;i<=n;i++) cin>>a[i];
	a[0]=0,a[n+1]=m;
	sort(a,a+n+2);
	for(reg int i=1;i<=n+1;i++)
	{
		len[i]=a[i]-a[i-1];
		if(i%2) ans+=len[i];
	}
	for(reg int i=1;i<=n+1;i++)
	{
		sum1[i]=sum1[i-1]+((i%2)?len[i]:0);
		sum2[i]=sum2[i-1]+((!(i%2))?len[i]:0);
	}
	for(reg int i=1;i<=n+1;i++)
	{
		if(len[i]==1) continue;
		reg int cnt=sum1[i-1]+len[i]-1+sum2[n+1]-sum2[i];
		ans=max(ans,cnt);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lsr1409111459 (赞：2)

#### 1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1000B)）

#### 2 解题思路

题目通俗一点理解就是有一条 $0\sim M$ 的线段，用 $n$ 个点分成 $n+1$ 条线段。从左到右编号，取其中所有编号为奇数的线段长度。操作就是插入一个点使后面线段的奇偶性改变。

考虑插入一个点，会将一个线段分成两部分，取其中一部分。那么，一定是将线段分为 $1$ 和 $a_i-1$ ，然后取 $a_i-1$ 的收益最大。

因此，我们的思路就是，枚举每一段线段，取该线段前的所有编号为奇数的线段，该线段后的所有编号为偶数的线段，和该线段的长度减一，三者加和。最后取所有枚举出的和的最大值（注意还可以不插点）。

可以用前缀和维护奇数线段和和偶数线段和， $O(1)$ 调用即可。

#### 3 解题代码

```cpp
#include <iostream>
using namespace std;
int n,m;
int a[100100],len[100100];
int ans=0;
int sum1[100100],sum2[100100];
//sum1[i]表示线段i前所有编号为奇数的线段的长度和，sum2[i]表示线段i前所有编号为偶数的线段的长度和
int main()
{
    scanf("%d%d",&n,&m);
    a[0]=0;a[n+1]=m;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n+1;i++)
    {
        len[i]=a[i]-a[i-1];
        if(i%2)
        {
            ans+=len[i];
            sum1[i]=sum1[i-1]+len[i];
            sum2[i]=sum2[i-1];
        }
        else
        {
            sum1[i]=sum1[i-1];
            sum2[i]=sum2[i-1]+len[i];
        }
    }
    for(int i=1;i<=n+1;i++)
        ans=max(ans,sum1[i-1]+len[i]-1+sum2[n+1]-sum2[i]);
    printf("%d\n",ans);
    return 0;
}
```

#### 4 解题心得

本题最开始理解错题意，导致毫无头绪。先去做了后面的中文题再回来阅读，豁然开朗。

前缀和维护/差分维护可以 $O(1)$ 查询/修改，还是很有用的优化方法。

---

## 作者：lowAltitudeFlyer (赞：2)

## Solution
模拟。

显然最优方案一定是在某次已有操作的时刻加$1$或减$1$的时刻改变状态（感性理解即可）。所以我们枚举每个已有操作，如果在该时刻加$1$或减$1$的时刻改变状态总亮灯时间更长，则修改答案。

使用前缀和可以做到$O(1)$计算在某个时刻改变状态的总亮灯时间。
## Tips
- 可以不改变状态

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 5;
int n, m, a[MAXN], sum[MAXN], ans; //sum[i]表示0到a[i]时刻的总亮灯时间 
int calc(int x, int y) { //a[x]到a[y]时刻的总亮灯时间 
	return sum[y] - sum[x];
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		if(i % 2 == 1) sum[i] = sum[i-2] + a[i] - a[i-1];
		else sum[i] = sum[i-1];
	}
	a[n+1] = m;
	if(n % 2 == 1) sum[n+1] = sum[n];
	else sum[n+1] = sum[n] + m - a[n];
	for(int i = 0; i <= n + 1; i++) {
		if(a[i] - 1 >= 0 && a[i] - 1 != a[i-1]) {
			ans = max(ans, sum[i] + (m - a[i] - calc(i, n+1)) + (i % 2 == 0 ? 1 : -1)); //在a[i]-1时刻改变状态 
		}
		if(a[i] + 1 <= m && a[i] + 1 != a[i+1]) {
			ans = max(ans, sum[i] + (m - a[i] - calc(i, n+1)) + (i % 2 == 0 ? 1 : -1)); //在a[i]+1时刻改变状态 
		}
	}
	ans = max(ans, sum[n+1]); //可以不改变状态 
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：Lee666666 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1000B)

这道题是道**模拟**题，但穿插着一点点**贪心**。

我们先计算总时间：$n$ 次改变灯的开关，将从 0 到 $m$ 这一大段时间分成了 $n + 1$ 小段，有些小段的时间由于灯是关着的所以不计算在总时间内。

而我们能够新添加的让灯改变一次的机会，无非就是在这 $n + 1$ 段中选择**长度大于 1** 的一段并插入，我们需要找出所有插入的方案中选择**最优**的一个。

设 $len_i$ 表示第 $i$ 小段的长度。

我们先讨论这个机会应该插入在每个小段中的什么位置：

第一种情况：如果这一小段灯是**开**着的，那么在这个机会插入的位置一直到这一小段结束这段时间，灯是关着的，我们当然希望关灯的这一段尽可能**短**，所以这个位置应该尽可能靠**后**，就在结束前的一时，对答案的贡献为 -1。

第二种情况：如果这一小段灯是**关**着的，那么在这一小段开始一直到这个机会插入的位置这段时间，灯是开着的，我们当然希望开灯的这一段尽可能**长**，所以这个位置应该尽可能靠**前**，就在开始后的一时，对答案的贡献为 $len_i - 1$。

显然，在一个小段中插入的位置不同并不会产生除上述讨论外的**额外影响**，所以贪心成立。

接着我们讨论这个小段插入机会后对其他小段的影响：

设这个小段是第 $i$ 个小段，第 $i + 1$ 小段到第 $n$ 小段的开关都会**颠倒**，需要重新计算。

如果我们每一小段都要重新计算，那么时间复杂度是 $O(n^2)$，而数据范围是 $n \leq 10^5$，不能通过。这是我们需要声明一个**后缀**数组 $suf$，$suf_i$ 表示第 $i$ 段到第 $n + 1$ 段开关颠倒后的贡献，这样就可以在 $O(1)$ 的时间内重新计算颠倒后的贡献。

上代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100015;

inline int simple_read() {
	int s = 0;
	char ch = getchar();
	while (ch < 48 || ch > 57) {
		ch = getchar();
	}
	while (ch > 47 && ch < 58) {
		s = (s << 3) + (s << 1) + ch - 48;
		ch = getchar();
	}
	return s;
}

int n, m, sum, chan, arr1[maxn], arr2[maxn], suf[maxn];

int main() {
	n = simple_read();
	m = simple_read();
	int last = 0, tmp;
	for (register int i = 0; i < n; i++) {
		tmp = simple_read();
		if (i & 1) {
			arr1[i] = 0;
			arr2[i] = tmp - last;
		}
		else {
			arr1[i] = tmp - last;
			arr2[i] = 0;
		}
		last = tmp;
		sum += arr1[i];
	}
	if (n & 1) {
		arr1[n] = 0;
		arr2[n] = m - last;
	}
	else {
		arr1[n] = m - last;
		arr2[n] = 0;
	}
	sum += arr1[n];
	for (register int i = n; i > -1; i--) {
		suf[i] = suf[i + 1] + arr2[i] - arr1[i];
	}
	for (register int i = 0; i <= n; i++) {
		if (i & 1) {
			if (arr2[i] > 1) {
				chan = max(chan, arr2[i] - 1 + suf[i + 1]);
			}
		}
		else {
			if (arr1[i] > 1) {
				chan = max(chan, suf[i + 1] - 1);
			}
		}
	}
	printf("%d", sum + chan);
	return 0;
}
```

完结撒花~

---

## 作者：风浔凌 (赞：1)

这道题允许在(a[i]),a[i+1])之内放入一个值，使得其后面所有的开关状态转换，从而达到光亮的时间最长。

经过思考，我们可以知道将转换的位置x移到a[i]或者a[i+1]是最优的。而这时我们不难发现，当灯原本就是亮着的时候在它前面一个转换一次状态比在它后面好；而当灯原本就是灭着的时候在它后面一个放一个转换状态比在他前面放好。

开b，c数组存储亮暗的时间，最后计算一下就可以了。

所以代码如下：
```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
ll n,m,a[100005];
ll b[100005],c[100005];
int main()
{
	cin>>n>>m;
	a[1]=0;
	a[n+2]=m;
	for(int i=2;i<=n+1;i++)
	{
		cin>>a[i];
	}
	ll ans=0,cur=0;
	for(int i=1;i<=n+2;i++)
	{
		b[i]=b[i-1];
		c[i]=c[i-1];
		if(i%2==0)
		{
			ans+=a[i]-a[i-1];
			b[i]+=a[i]-a[i-1];
		}
		else
		{
			c[i]+=a[i]-a[i-1];
		}
	
	for(int i=1;i<n+2;i++)
	{
		if(i%2)
		{
			if(a[i+1]-1>a[i])
			{
				ll cur=b[i]+a[i+1]-1-a[i]+c[n+2]-c[i+1];
                //不要忘了-1
				ans=max(ans,cur);
			}
		}
		else
		{
			if(a[i]+1<a[i+1])
			{
				ll cur=b[i]+a[i+1]-a[i]-1+c[n+2]-c[i+1];
                //不要忘了-1
				ans=max(ans,cur);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：浮光掠影 (赞：0)

### 解题思路：

在 $a_i$ 和 $a_{i+1}$ 之间插入一个数 $x$ 时，$a_i$ 前面的灯亮的时间和是不变的，$x$ 后面每个 $a$ 数组的元素代表的状态反转一次，反转后 $a_{i+1}$ 之后灯亮的时间是固定的（不因为 $x$ 的大小改变）。所以主要看 $a_i$ 和 $a_{i+1}$ 之间的状态。这时分为两种情况：

- $a_i$ 代表开，$a_{i+1}$ 代表关。则插入 $x$ 后，$a_i$ 到$x$ 代表灯亮，$x$ 到 $a_{i+1}$ 代表灯灭，为了使灯亮的时间最长，所以 $x$ 应该是 $a_{i+1}-1$。则现在 $a_{i+1}$ 之前的灯亮的时间是之前的减$1$。

- $a_i$ 代表关，$a_{i+1}$ 代表开。则插入 $x$ 后，$a_i$ 到$x$ 代表灯灭，$x$ 到 $a_{i+1}$ 代表灯亮，为了使灯亮的时间最长，所以 $x$ 应该是 $a_i+1$。则现在 $a_{i+1}$ 之前的灯亮的时间也是之前的减 $1$。

得到这个结论之后，计算插入 $x$ 后的灯亮总时间时，分为两部分；第一部分为 $0$ 到 $a_{i+1}$，灯亮时间为 $sum_i-1$；第二部分为 $a_{i+1}$ 到 $m$，灯亮时间为之前总的灯灭时间减去 $a_{i+1}$ 之前的灯灭时间。即 $(m-sum_{n+1}) - (a_i-sum_i)$。答案取最大值即可，记得和不插入数时的灯亮时间 $sum_{n+1}$ 作比较。

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 100;
 
int n, m, f, a[N], sum[N];
 
int main()
{
	cin>>n>>m;
	for(int i = 1; i <= n; i++) cin>>a[i];
	a[n+1] = m;
	for(int i = 1; i <= n+1; i++)
	{
		f ^= 1;
		sum[i] = sum[i-1] + f*(a[i] - a[i-1]);
	}
	int ans = sum[n+1];
	for(int i = 1; i <= n; i++) ans = max(ans, (sum[i+1]-1) + ((m-sum[n+1]) - (a[i+1]-sum[i+1])));
    cout<<ans;
	return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

让一个灯亮着的时间尽可能大。

~~说了跟说了一样，还是题目翻译又简洁又易懂。~~

## 解法

额就是这有一个坑啊，就是最终答案要和什么都不改的亮着时间比大小啊。

可以用一个前缀和，啊。

先用 $a_i$ 分割 $i$ 个节点。

咱设 $sum_i$ 表示什么都不改的情况下，到第 $i$ 个
节点时亮着的时间；$fsum_i$ 表示当灯的状态全都是反着的情况下（即原本亮着就是暗的，暗的就是亮的）亮的时间（~~那不就是暗着的时间吗？~~）。特别的，$sum_{n+1}$ 是到 $m$ 时间的值，$fsum_{n+1}$ 也是。

然后为了让灯亮着的时间尽可能久，我们要让它亮着的时间更久一点（~~废话~~）。很容易想到在两个节点中间改变状态肯定不是最优的，~~双面不讨好~~，因为早一点可以让它亮着或者暗着更久。所以，在灯下一秒即将变暗时，或刚刚变暗后改变灯的状态，这样它原本变暗就会变亮。

所以枚举 $i$，若 $a_i-1$ 或 $a_i+1$ 中有可以改变状态的时间（即不是 $0$ 且不是 $m$ 且不是 $a$ 中的数），就改变，计算亮着时间，取最大值。

亮着的时间为 $sum_i+(fsum_{n+1}-fsum_{i-1})-1$。

因为改变状态后后面全部都会变，所以前缀和计算 $fsum$。最后减一是因为在它本来是亮着的时候变暗了，下一秒才会重新亮起来。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,m,a[100005],sum[100005],maxn,fsum[100005];
map <int,bool> mp;

signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i = 1;i <= n;i++)
	{
		scanf("%lld",&a[i]);
		mp[a[i]] = 1;//这个时间点无法改变状态
		sum[i] = sum[i - 1];//前缀和
		if(i % 2) sum[i] += a[i] - a[i - 1];//亮着时间
		fsum[i] = fsum[i - 1];
		if(i % 2 == 0) fsum[i] += a[i] - a[i - 1];//暗着时间
	}
	mp[0] = mp[m] = 1;//这两个点也不能改变状态
	fsum[n + 1] = fsum[n];//记得这个
	sum[n + 1] = sum[n];
	if(n % 2 == 0) sum[n + 1] += m - a[n];
	if(n % 2) fsum[n + 1] += m - a[n];
	for(int i = 1;i <= n;i++)
	if(i % 2 && (!mp[a[i] - 1] || !mp[a[i] + 1]))
	maxn = max(maxn,sum[i] + (fsum[n + 1] - fsum[i - 1]) - 1);//取最大值
	printf("%lld",max(maxn,sum[n + 1]));//记得比较,可以不改变!!
	return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路

对每一个区间尝试更改灯的状态。通过**贪心**可以发现两条性质：

1. 如果这段灯在更改之前是开着的，那么一定选择在结束前的时间关掉它。因为如果提前关掉，那么总时间会减少。
2. 如果这段灯在更改之前是关着的，那么一定选择在开始后的第一时间打开它。如果之后再开，那么也浪费了一些时间导致总时间减少。

容易发现每一个区间并不互相影响，故贪心成立。

再维护**前缀和与后缀和**，将整个数组分为三段：未更改前，正在更改的区间，更改区间后面的区间。再分别计算答案即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans,a[100010],s1[100010],s2[100010];
signed main(){
	scanf("%lld%lld",&n,&m);
	a[n+1]=m;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n+1;i++){
		if(i&1){
			ans=ans+a[i]-a[i-1];
			s1[i]=s1[i-1]+a[i]-a[i-1];
			s2[i]=s2[i-1];
		}
		else{
			s1[i]=s1[i-1];
			s2[i]=s2[i-1]+a[i]-a[i-1];
		}
	}
	for(int i=1;i<=n+1;i++){
		if(a[i]-a[i-1]>1) ans=max(ans,s1[i-1]+a[i]-a[i-1]-1+s2[n+1]-s2[i]);
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：cppcppcpp3 (赞：0)

[传送门。](https://www.luogu.com.cn/problem/CF1000B)

## Solution

细节：注意可以不改变任何时刻。

如果要选择某个剩余时刻 $pos$ 让灯的状态改变，那么情况大致如图：

![如图](https://cdn.luogu.com.cn/upload/image_hosting/8divb7cx.png)

其中深绿色的代表灯亮的时间段，上下两行代表选择前后的情况。

不妨设 $a_0=0,a_{n+1}=m$。

我们考虑所有 $pos \in (a_i,a_{i+1})$ 时的最优情况，其实就是让 $(a_i,a_{i+1})$ 中间浅绿色的那段最短，取 $pos=a_i+1$ 即可。

所以对于 $i \in [0,1,\cdots,n]$，若可以，取改变 $a_i+1$ 时的答案 $\max$ 值。设 $pre_i$ 为时刻 $0$ 到 $a_i$ 原来的灯亮时长，这个可以前缀和处理。则改变 $a_i+1$ 的答案 $cnt_i$ 为：

$$pre_i+(a_i-a_{i+1}+1)+(m-a_{i+1})-(pre_{n+1}-pre_{i+1})$$

最终答案为 $\max(\max\limits_{i=0}^{n}cnt_i,pre_{n+1})$。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int N=1e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,m,ans,cnt,a[N],d[N],pre[N];

map<int,bool> vis;

main(){
	n=wrd(),m=wrd(),a[n+1]=m;
	for(int i=1;i<=n;++i) vis[a[i]=wrd()]=1,d[i]=a[i]-a[i-1];
	d[n+1]=m-a[n];
	for(int i=1;i<=n+1;++i) pre[i]=pre[i-1]+(i&1)*d[i];
	ans=pre[n+1];
	
	for(int i=0;i<=n;++i){
		int pos=a[i]+1;
		if(vis[pos] || pos>m) continue;
		cnt=pre[i]+d[i+1]-1+(m-a[i+1])-(pre[n+1]-pre[i+1]);
		ans=max(ans,cnt);
	}
	return printf("%d",ans),0;
}
```

---

## 作者：BLUESKY007 (赞：0)

蒟蒻第二篇题解。。。

比赛的时候写这道题MLE了qwq。。根据CF的赛制我也没敢再交第二次。。

简单讲一下思路好了~~(假装是dalao)~~。。根据题意要加一个或者不加新的点。。如果加一个新的点意味着从这个点往后的时间里状态都会反转(亮->灭&&灭->亮)。。则加入点后的亮灯时间=(点后总时间-点后原本亮灯时间)。。根据三个样例不难发现加的点位置在原有点的两侧并且两侧位置等价~~(这一点感性理解一下就好)~~。。然后就要在加点的时候判断一下已有点两侧是否能加点(一开始没看m最大1e9。。用vis数组判断直接MLE了。。。STL真好用)。。然后每个点默认按照右端加点计算新的亮灯时间(毕竟左右等价)。。和ANS取max更新结果(没错就是这样)。。

看起来没什么问题。。但是新的亮灯时间是(原前+现后)。。而计算原后也要用到原前**(这是重点)** 。。根据题意奇数个点是关闭的偶数点是开启的。。于是一段一段的加就得到总时间(过程中把截至每个点右侧是的亮灯时间都放入vector)。。于是大功告成。。

下面贴代码↓↓
```cpp
#include<cstdio>//CF1000B
#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
#include<queue>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cmath>

using namespace std;

int n,m,ANS,sm,N;

vector<int>a,c;

set<int>s;

int main(){
	int flag=0,re,u,v;
	scanf("%d%d",&n,&m);
	N=n+1;
	a.push_back(0);
	for(int i=1;i<=n;i++){
		scanf("%d",&re);
		a.push_back(re);
		s.insert(re);
	}
	if(n%2==0){
		a.push_back(m);
		N++;
		flag=1;
	}
	for(int i=0,j=i+1;i<N;i+=2,j=i+1){
		u=a[i];
		v=a[j];
		sm-=(u-v);
		c.push_back(sm);
		c.push_back(sm+1);
	}
	ANS=sm;
	for(int i=0;i<n;i++){
		if(s.count(a[i+1]+1)&&s.count(a[i+1]-1)){
			continue;
		}
		int now=c[i],ex=sm-now,et=m-a[i+1]-1;
		ANS=max(ANS,now+et-ex);
	}
	printf("%d\n",ANS);
	return 0;
}
```

---

