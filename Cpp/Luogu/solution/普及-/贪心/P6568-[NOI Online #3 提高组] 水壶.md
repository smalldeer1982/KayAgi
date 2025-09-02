# [NOI Online #3 提高组] 水壶

## 题目描述

有 $n$ 个容量无穷大的水壶，它们从 $1\sim n$ 编号，初始时 $i$ 号水壶中装有 $A_i$ 单位的水。

你可以进行不超过 $k$ 次操作，每次操作需要选择一个满足 $1\le x\le n-1$ 的编号 $x$，然后把 $x$ 号水壶中的水全部倒入 $x+1$ 号水壶中。

最后你可以任意选择恰好一个水壶，并喝掉水壶中所有的水。现在请你求出，你最多能喝到多少单位的水。

## 说明/提示

#### 数据规模与约定

- 对于 $10\%$ 的数据，保证 $n \leq 10$。
- 对于 $30\%$ 的数据，保证 $n \leq 100$。
- 对于 $50\%$ 的数据，保证 $n \leq 10^3$。
- 对于 $70\%$ 的数据，保证 $n \leq 10^5$。
- 对于 $100\%$ 的数据，保证 $1\leq n\leq 10^6$，$0\leq k \leq n-1$，$0\le A_i\le 10^3$。

## 样例 #1

### 输入

```
10
5
890 965 256 419 296 987 45 676 976 742
```

### 输出

```
3813```

# 题解

## 作者：chen_zhe (赞：61)

很显然每次倒水之后，水总是单调递增的，那么肯定要把这个更多的水，倒到下一个水壶里面去。也就是说每次倒水的范围是一个区间。

因此问题就很显然地转化为了求一个长度为 $k+1$ 的最大连续子段和，就可以很简单地水过去了。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int n,k,a[1000050];

long long sum,ans;

int main()
{
	freopen("kettle.in","r",stdin);
	freopen("kettle.out","w",stdout);
	n=read(),k=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	int l=1,r=k+1;
	for (int i=l;i<=r;i++)
		sum+=a[i];
	while (r<=n)
	{
		ans=max(ans,sum);
		l++;
		r++;
		sum-=a[l-1];
		sum+=a[r];
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：LinkZelda (赞：41)

- **题意简化：** 给定一个数列与区间长度，求数列中最大的区间和。

- **为什么我们可以这样想呢？**

我们可以贪心地想一下，为了喝掉最多的水，肯定是要把可以倒的水全部倒到自己的杯子里。而且题目说了每杯水只能倒到后一个杯子里面，所以就是一直连续倒到后一个杯子，自己喝最后一杯就是最多的。~~（说了一大堆还不要是求区间加）~~

- **暴力 $O (n^2) $**

我们就直接暴力枚举左端点，左端点加上 $k$ 就得到了右端点，然后再对于这个区间求和。（这么看上去貌似是   $O(nk)$ 的，但是鉴于 $k \leq n-1$ 就夸张点写成 $O(n^2)$ 吧）

但是我们一看数据 ， $n\leq 10^6$ ，肯定会爆 $qwq$



- **前缀和优化 $O (n)$**

看到求区间和，我们很容易可以想到可以 $O(1)$ 搞出区间和的好东西：**前缀和**！！！

我们还是枚举左端点，然后算出右端点 ，再用前缀和求区间加，记录一下区间加的最大值就好啦！

~~其实这个复杂度还有一个不小的常数 ，不过还是能 $AC$ 的就不管了~~ 

- **代码如下**：


```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

int q[1000005],maxx=0;//不用开 long long ，根据题目最大前缀应该是 int 能存下的
int a[1000005];

int main()
{
	//freopen("kettle.in","r",stdin);
	//freopen("kettle.out","w",stdout);
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)//输入数据，初始化前缀和
	{
		scanf("%d",&a[i]);
		q[i]=q[i-1]+a[i];
	}
	for(int i=1;i<=n-k;i++)//前缀和找最大区间加
	{
		maxx=max(maxx,q[i+k]-q[i-1]);
	}
	printf("%d",maxx);//输出
	//fclose(stdin);fclose(stdout);
	return 0;
 } 
```


---

## 作者：锦瑟，华年 (赞：15)

很简单，这题就是最大字段和（前缀和）。

这题为什么是最大字段和呢？很简单，为使能喝的水的数量最大，最终到过的所有水是汇聚在一处的，怎样汇聚在一处呢？很简单，从任意点开始，一直往右（或往左倒）倒即可，所有倒过的水的原来位置连起来就是一个子串了。

那么，最大子串和怎么写呢？这要用到前缀和，那么前缀和又是什么呢？即计算l至r这一段区间的和。先计算从头到每一个数的之间的数的总和，最后输出时，把$a[r]-a[l-1]$即可（为什么呢，$a[r]$是前$r$个数的和，$a[l-1]$是前$l-1$个数的和，两者相减，前$l-1$个数的和被抵消，就是剩下第$l$个数至第$r$个数的和了）。代码：

	for(i=1;i<=n;i++){
    	f[i]+=f[i-1];//计算代码f[r]-f[l-1]
	}
    
好了，只要把每一段的和求出来，剩下的只要判最大就可以了，代码：

	#include<stdio.h>
	using namespace std;
	int a[1000005];
	int main(){
		int n,m,i;
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++){
			scanf("%d",&a[i]);
			a[i]+=a[i-1];//前缀和
		}
		int max=0;
		for(i=1;i+m<=n;i++){
			int k=a[i+m]-a[i-1];//前缀和计算，注意，水壶倒的次数比子段长度小1（自己想想为什么）
			if(k>max)max=k;//判断大小
		}
		printf("%d",max);//输出
		return 0;
	} 
    
好了拜拜~~~

---

## 作者：丨Sky灬丨无惧 (赞：10)

题解
思路：因为每次只能往下一个杯子里倒水，所以等于求一个区间的值，这就令人想到前缀和。
【代码】（考场）：
```
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[3000000],b[3000000],ans=-1;//没事就开longlong
int main() {
//	freopen("kettle.in","r",stdin);
//	freopen("kettle.out","w",stdout);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=b[i-1]+a[i];//计算前缀和。
	}
	for(int i=1;i<=n-k;i++){//区间的循环到n-k就好了，否则就会超出。
		ans=max(ans,b[i+k]-b[i-1]);//求区间内的最大值。
	}
	cout<<ans;//输出答案。
	return 0;
}
```
完结撒花。

---

## 作者：Cripple_Abyss (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P6568)

本题作为提高组的题目，~~太水了吧~~，本蒟蒻这个xxs都能做出来

- ## $50pts$:


暴力枚举

时间复杂度为$O(n^2)$
此代码相信大家都能写出，本蒟蒻不在展出。


- ## $100pts$:

每次求和其实就是删除前一个不要的数字，再加上新增的数


# 注意：每次可以进行$k$次操作,也就是可以将$k+1$个水壶进行合并！！！

# $Code$:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[1000005],ans,s;
int main() {
//	freopen("kettle.in","r",stdin);
//	freopen("kettle.out","w",stdout);
	scanf("%d%d",&n,&k);
	k++;
	for (int i=1; i<=n; i++) {
		scanf("%d",&a[i]);
		if (i<=k)
			s+=a[i];
	}
	ans=s;
	for (int i=1,j=1+k; j<=n; i++,j++) {
		s-=a[i];
		s+=a[j];
		ans=max(ans,s);
	}
	printf("%d\n",ans);
	return 0;
}
```

都看到这了点个赞呗QwQ


---

## 作者：BFqwq (赞：6)

EA nb!EA nb!EA nb!



------------
这个题是一个比较简单的区间求和题。

显然，最优解法是选取一个长度为 $k+1$ 的区间。若不然，则我们将答案区间向前扩充到长度为 $k-1$，一定更优。

于是我们就可以一个前缀和轻松的解决这个题了。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(register int x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=1e6+5;
int n,k,a[maxn],ans;
signed main(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		a[i]+=a[i-1];
		if(i>k) a[i]-=a[i-k-1];
		ans=max(ans,a[i]);
		if(i>k) a[i]+=a[i-k-1];
	}
	print(ans);
	return 0;
}
```


---

## 作者：Wall_breaker (赞：5)

我们来看一看这道题目。
题目大意，是把水从一个壶向后面倒，那么我们考虑下面这张图。

### 原:1 1 1 1 1 1 1 
### 倒:1 0 2 1 1 1 1
### 现:1 2 1 1 1 1

我把2号的水倒进3号,三号加一。

那么，如果我把很多个的水壶合并后，水分散在几个水壶中，那么这是否是最优解呢？

### 如：1 2 2 2 （倒了3次）

可以证明，这一定不是最优解。如果有一次合并没有给最后喝的水壶贡献水，那么这一次合并没有任何价值，我完全可以取消这次合并。**所以，最优解是将水向一个水壶中集中。那么，这就变成了区间和。**

**于是乎，本题就变成了，在原区间中，找一个长度为k+1的区间，使区间和最大。**

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x) {
	x = 0;
	T f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}

template <typename T>
inline void w(T x) {
	if (x > 9) w(x / 10);
	putchar(x % 10 + 48);
}
template <typename T>
inline void write(T x, char c) {
	if (x < 0){
		putchar('-');
		x = -x;
	}
	w(x);
	putchar(c);
}
int a[1000005];
int main(){
	//freopen("kettle.in", "r", stdin);
	//freopen("kettle.out", "w", stdout); 
	int n, k; 
	read(n); read(k);
	for (int i = 1; i <= n; i ++) read(a[i]);
	int ans = 0, s = 0;
	for (int i = 1; i <= k; i ++) {
		s += a[i];
	}
	for (int i = k + 1, j = 0; i <= n; i ++, j ++) {
		s += a[i];
		s -= a[j];
		ans = max(ans, s);
	}
	write(ans, '\n');
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：5)

这道题真的是不能在水了……  
我把题目审了将近三遍都不敢相信这道题居然这么简单  
由于水都是正数，我们能加多少就加多少，故我们必须要用完k次。而且我们要保证我们最后都能把所有水加到一杯水里面去……所以题目就转化成了求一段长度为k + 1的最大子段和对吧……  
前缀和维护一下即可  
直接贴代码了  
# Code
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int Len = 1e6 + 5;
int n,m;
long long a[Len],sum[Len],ans;
int main()
{
	//freopen("kettle.in","r",stdin);
	//freopen("kettle.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= n; i ++)
	{
		scanf("%lld",&a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	m ++;
	for(int i = 0; i <= n - m; i ++) ans = max(ans,sum[i + m] - sum[i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Natsume_Rin (赞：4)

其实只要找长度为 $k+1$ 的子序列的最大值就好了。

这题可以用前缀和 ~~(当然也可以不用)~~

其实也没有什么好讲的。

代码:

```cpp

#include<bits/stdc++.h>
using namespace std;
int a[1000006], f[1000006], ans;
int main(){
    int n, k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		f[i]=f[i-1]+a[i];
	}
	for(int i=k+1;i<=n;++i){
		ans=max(ans,f[i]-f[i-k-1]);
	}
	printf("%d",ans);
    return 0;
}

```

---

## 作者：bovine__kebi (赞：3)

根据题意，因为不可能有负数的水量，所以肯定要倒越多次越好，又因为只能往右边倒，所以题目就变成了，求长度为$k+1$的最大子段，于是我们通过前缀和记录，之后用滑动窗口移动一下就好了，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+5;
int a[maxn];
ll Sum[maxn];
ll maxx=-99999999;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
int main()
{
    int n,k;
    n=read();k=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();  
        Sum[i]=Sum[i-1]+a[i];
    }
    for(register int l=1,r=k+1;r<=n;l++,r++)//滑动窗口的实现
    {
        maxx=max(maxx,Sum[r]-Sum[l-1]);
    }
    printf("%lld\n",maxx);
}
```
~~话说这题为什么在提高考~~

---

## 作者：Chouquet (赞：2)

也不知道怎么证明，~~显然可以用前缀和吧~~，根据题目中倒水的规则只能是在长度为 $k$ 的区间内所有数和的最大值（勿喷），用一个前缀和来处理就行了。

代码：

```cpp
#include <stdio.h>
#define max(a,b) (a)>(b)?(a):(b)
//宏定义max函数
long long s[1000001],ans;//s为前缀和数组，要开long long
int k,n;
main(){
   scanf("%d%d",&n,&k);
   for(int i=1;i<=n;i++)
       scanf("%lld\n",&s[i]),s[i]+=s[i-1]+0ll;//边读入边做前缀和
   for(int i=k+1;i<=n;i++)
       ans=max(ans,s[i]-s[i-k-1]);//求长度为k的区间和的最大值
   return printf("%lld\n",ans),0;
}
```


---

## 作者：Daidly (赞：2)

# STEP1
通过审题，我们可以发现，每一次把$x$号水壶的水倒入$x+1$号水壶中，$x+1$号水壶的水必定比原来多。又因为我们需要求能喝的最多水量，所以每一次的$x+1$必须要用在最多的地方，所以每一次的$x+1$都是连着的。

这样我们就可以把这个问题简单化，只需要求在这个问题中，连续的k+1个元素中，哪个最大，我们就输出哪个。
# STEP2
我们从头开始分析代码。

$1.$输入的格式中，需要输入两个数$n$和$k$，并且输入$n$个小于$1000$的非负整数，这样我们就可以用$for$循环来输入。
```
    cin>>n;
	cin>>k;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
```
$2.$用$for$循环嵌套：
```
for(int i=1;i<=n;i++){//把for循环中的i定义成1是因为需要计算a[0]。
	    a[i]+=a[i-1];//算出每一个及其前面所有数的和
		for(int i=k;i<=n;i++){//把for循环中的i定义成1是因为需要计算a[0]。
		sum=max(sum,a[i]-a[i-k-1]);
	    }
    }
```
# STEP3
$AC$代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,k,sum;
long long a[1000003];
int main(){
	//freopen("kettle.in","r",stdin);
    //freopen("kettle.out","w",stdout);
	ios::sync_with_stdio(false);//加速
    cin.tie(0);cout.tie(0);
	cin>>n;
	cin>>k;
	for( int i=0;i<n;i++){
		cin>>a[i];
	}
	for( int i=1;i<=n;i++){
	    a[i]+=a[i-1];
		for( int i=k;i<=n;i++){
		sum=max(sum,a[i]-a[i-k-1]);
	    }
    }
	cout<<sum<<endl;
	return 0;
}
```


---

## 作者：修罗海神王 (赞：2)

~~说实话，此题作为提高组第一题真的有点太水了~~


| _最后_ 你可以任意选择恰好一个水壶，并喝掉水壶中所有的水。现在请你求出，你最多能喝到多少单位的水。  |
| :----------- |

  注意这一句话，“最后”一词说明了水壶叠加后只能喝一次。那么就意味着水壶的最后一次操作的量要最大。如果第一次操作了 $1$ 和 $2$ ，第二次又操作了 $3$ 和 $4$ ，就无法满足在前4个水壶中找到最大值。
  
  例如，样例：
  
  ```
10
5
890 965 256 419 296 987 45 676 976 742 
```

   $k=5$,说明可以进行 $5$ 次操作，合并 $6$ 个水壶，而这 $6$ 个水壶又必须是连续的，因而可以想到前缀和。
   
   
   很显然，我们要求出 $k+1$ 个水壶的最大连续和。
   
   这样子的话题目就简单多了，但是，还有一点要注意——
   
    十年OI一场空，不开longlong见祖宗
    
   没有错，看见题目 $100%$ 的数据了吗？
   
   $n≤10^6 $,
   $k≤n-1$,
   $A≤10^3$
   
   这样的数据不开 $longlong$ 吗？
   
   好了，说了这么多，贴代码：
   
   ```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,x,mx,s[2000000];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) 
	{
		scanf("%lld",&x);
		s[i]=s[i-1]+x;
	}
	for(int i=1;i<=n;i++) mx=max(s[i+k]-s[i-1],mx);
	cout<<mx<<"\n";
	return 0;
 } 
```
~~祝：下场NOI不要慌，遇到难题细思考~~
   



---

## 作者：infinities (赞：0)

比较显然的一题，直接维护前缀和然后 $O(n)$ 查找长度为 $k+1$ 的最大区间即可。

这么做的原因比较显然，就是我们每次倒水肯定都是有目的的，不能浪费次数，要让倒的水最终被喝掉，所以我们肯定要把尽量多的水用尽量少的次数（即从左往右倒），所以这样我们每次肯定是一个紧挨着一个倒水，这样寻找一段长度为 $k+1$ 的最大区间即可。

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rint register int
const int maxn = 1234567;
const int INF = 1;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

using namespace std;

int sum[maxn], num[maxn], k, n, lla;

signed main(){
	//freopen("kettle.in", "r", stdin);
	//freopen("kettle.out", "w", stdout);
	n = read(), k = read();
	for(int i = 1; i <= n; i++){
		num[i] = read(), sum[i] = sum[i - 1] + num[i];
	}
	for(int i = -1; i <= n - k; i++){
		lla = max(lla, sum[i + k] - sum[i - 1]);
	}
	cout << lla;
	return 0;
}


---

## 作者：cirnovsky (赞：0)

作为提高组的题还是水了点。

题目让我们求一个长度限制为 $k+1$ 的最大子段和，又因为 $A_{i}$ 非负，所以直接前缀和求 $\max(sum_{i+k}-sum_{i-1})$。

（开始没看 $A_{i}$ 的范围还锤了半天单调队列……）

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e6 + 5;
int n, k, a[N];
long long sum[N], dp[N];

signed main() {
	freopen("kettle.in", "r", stdin);
	freopen("kettle.out", "w", stdout);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
	long long ans = 0;
	for (int i = 1; i <= n - k; ++i) ans = max(ans, sum[i + k] - sum[i - 1]);
	return printf("%lld\n", ans), 0;
}
```

---

## 作者：zjrdmd (赞：0)

~~目前是最优解的呢（或许发完题解就不是了~~~

这题其实就是一个简单的贪心，我们可以发现一定是选取连续的$k+1$个数答案最优，所以直接维护前缀和即可。

代码如下

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <stdlib.h>
#include <stack>
#include <queue>
#define N 1000005
#define ri register int

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}

int n,k,ans=-1;
int sum[N];

int main(){
//	freopen("kettle.in","r",stdin) ;
//	freopen("kettle.out","w",stdout);
    n=read();k=read();
	for(ri i=1;i<=n;i++){
		int a=read();
		sum[i]=sum[i-1]+a;
	} 
	for(ri i=k+1;i<=n;i++){
		ans=std::max(ans,sum[i]-sum[i-k-1]);
	}
	printf("%d",ans);
	return 0;
}

```



---

## 作者：huayucaiji (赞：0)

这道题一看可以想出一个贪心的思路，因为我们要倒 $k$ 刺水，所以最优解一定是选择连续的 $k$ 的水壶进行倒水。这样问题就转化为了如何求一个最大的长度为 $k+1$ 的连续字段和。用前缀和维护一下即可。

代码中定义 $sum_i=\sum_{k=1}^{i} A_i$。

```cpp
//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e6+10; 

int n,sum[maxn],k;

signed main() {
	
	n=read();k=read();
	for(int i=1;i<=n;i++) {
		sum[i]=read();
		sum[i]+=sum[i-1];
	}
	
	int maxx=-1;
	for(int i=k+1;i<=n;i++){
		maxx=max(maxx,sum[i]-sum[i-k-1]);
	}
	
	cout<<maxx<<endl;
	return 0;
}

```

---

## 作者：Bosun (赞：0)

很显然 将a倒给b和将b倒给a是等价的，所以在[l,r]内，假定是一直从左往右倒，倒k次，最后一桶的水量就是sum[l,r]

所以就很自然地想到最大子段和了，可以用dp或者前缀和解决！

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int N=1000005;
typedef long long ll;
ll a[N];
int main(){
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++){
    	scanf("%lld",&a[i]);
        a[i]=a[i-1]+a[i];
    }
	ll ans=0;
	for(i=m+1;i<=n;i++)ans=max(ans,a[i]-a[i-m-1]);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：青鸟_Blue_Bird (赞：0)

看到题目的第一眼，DP？
再看一眼数据范围，果断换方法。~~（写出O(N)DP的大佬除外）~~

#### 从题目条件慢慢分析是个好习惯。

首先，肯定是要化简题目的要求啦！

我们有n个水壶，每次可以把第i个水壶的水倒入第i + 1个水壶。

不难想到，如果设f[i]为第i个水壶中的水，很明显有

```cpp
f[i] += f[i - 1]
```

再看看题目要我们所求的。
“选一个水壶，求能喝的水的最大值。”

### 这不就是让某一个f尽可能的大吗！！

那么，如何让某一个f最大呢？   贪心的想，不就是把前K个水壶的水都倒入同一个水壶吗？

### 那么，按照这个想法，我们要求的就是最大连续、且长为K的子段和。

大体思路了解了，正确性还是要证明一下的。

假设我们有5个水壶，初始值分别为

1  、  2、  3、  4、 5

允许我们操作的数量k = 3

按照上面的方法，我们应该依次把2、3、4号水壶的水都倒入5。

如果不这么做呢？（即不求连续最大子段和） 假设我们有一步先将1倒入2， 那么我们的2就变成3。

首先，这违背了我们“尽可能集中在同一个水壶”的原则。其次，大家自己手动摸一下也可以发现，这样之后我们无论怎么倒，都无法获得一个比上文所述方法更大的答案。

证毕。

最后，我们如何求最大连续子段和呢？
考虑应用前缀和方法。

因为我们要求的就是一段连续的和，前缀和十分符合我们的需求。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000100
#define ll long long
#define isdigit(c) ((c)>='0'&&(c)<='9')

ll read(){
	ll x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){
		if(c == '-')s = -1;
		c = getchar();
	} 
	while(isdigit(c)){
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = getchar();
	}
	return x * s;
}

ll n , k;
ll sum[N];

int main(){
//	freopen("kettle.in", "r", stdin);
//	freopen("kettle.out", "w", stdout);
	n = read(), k = read();
	for(int i = 1;i <= n; i++){
		ll x = read();
		sum[i] = sum[i - 1] + x;  /*经典前缀和操作*/
	}
	ll ans = -66666;
	for(int i = k;i <= n; i++){
		ans = max(ans, sum[i] - sum[i - k - 1]); /*记得是i - k - 1*/
	}
	cout << ans << endl; 
	return 0;
}
```



~~(不开long long 好像也能过？）~~

---

