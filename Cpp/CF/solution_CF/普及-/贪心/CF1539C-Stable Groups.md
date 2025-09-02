# Stable Groups

## 题目描述

There are $ n $ students numerated from $ 1 $ to $ n $ . The level of the $ i $ -th student is $ a_i $ . You need to split the students into stable groups. A group of students is called stable, if in the sorted array of their levels no two neighboring elements differ by more than $ x $ .

For example, if $ x = 4 $ , then the group with levels $ [1, 10, 8, 4, 4] $ is stable (because $ 4 - 1 \le x $ , $ 4 - 4 \le x $ , $ 8 - 4 \le x $ , $ 10 - 8 \le x $ ), while the group with levels $ [2, 10, 10, 7] $ is not stable ( $ 7 - 2 = 5 > x $ ).

Apart from the $ n $ given students, teachers can invite at most $ k $ additional students with arbitrary levels (at teachers' choice). Find the minimum number of stable groups teachers can form from all students (including the newly invited).

For example, if there are two students with levels $ 1 $ and $ 5 $ ; $ x = 2 $ ; and $ k \ge 1 $ , then you can invite a new student with level $ 3 $ and put all the students in one stable group.

## 说明/提示

In the first example you can invite two students with levels $ 2 $ and $ 11 $ . Then you can split the students into two stable groups:

1. $ [1, 1, 2, 5, 8, 11, 12, 13] $ ,
2. $ [20, 22] $ .

In the second example you are not allowed to invite new students, so you need $ 3 $ groups:

1. $ [1, 1, 5, 5, 20, 20] $
2. $ [60, 70, 70, 70, 80, 90] $
3. $ [420] $

## 样例 #1

### 输入

```
8 2 3
1 1 5 8 12 13 20 22```

### 输出

```
2```

## 样例 #2

### 输入

```
13 0 37
20 20 80 70 70 70 420 5 1 5 1 60 90```

### 输出

```
3```

# 题解

## 作者：Shunpower (赞：4)

## 题目大意

现在有 $n$ 个学生，每个学生的水平为 $a_i$，允许你往其中添加 $k$ 个任意水平的学生。现在要求你把这 $n$ 个学生分成几组，使得每一组中的**水平大小相邻**的学生的水平绝对差小于等于 $x$。

## 思路分析
### 考虑贪心

可以先对学生的水平排一下序，算绝对差，把绝对差存储到一个数组里，接着对这个绝对差数组做贪心。

### 如何贪心
**因为绝对差小的情况更容易满足**，所以我们要先对绝对差数组排序，使得绝对差小的情况先考虑，绝对差大的情况后考虑。

如果绝对差大于 $x$，可以用两种办法解决：
- 能用加学生解决的，就用加学生解决。（并且要使得加的学生尽量少）
- 不能用加学生解决的，可以直接分成两组，避免两个人在同一组内。

## 代码剖析

### 3.1：差分
```cpp
sort(a+1,a+n+1);
	for(int i=2;i<=n;i++){
		b[i-1]=a[i]-a[i-1];
	}
sort(b+1,b+n);
```
$b$ 数组存储了两个水平相邻学生的绝对差，这里可以不带绝对值，因为 $sort$ 的结果是从小到大的。

最后对 $b$ 数组排序，以便后面做贪心。

### 3.2：贪心
```cpp
for(int i=1;i<n;i++){
	if(b[i]>x){//如果需要操作
		if(k>=(b[i]-1)/x){//看一看可不可以通过加学生解决
			k-=(b[i]-1)/x;//可以就让可用学生减掉需要学生
		}
		else{
			cnt++;//否则就分组，分组的次数加1。
		}
	}
}
```
首先判断这个差是否需要操作，如果不需要，就不管了。

如果需要，先尝试用加学生的办法去做。

- WARNING：这里减掉 $1$ 是非常重要的。我们可以把学生看成隔板，把一段水平差分成几段，而段数比点数少 $1$。

如果学生够用，把可用学生数量减去需要的学生数量。

否则就分一次组，让分组次数的计数器加 $1$。

最后直接输出。

- WARNING：输出 $cnt+1$！因为 $cnt$ 记录的是分组的次数，分了 $cnt$ 次，就会有 $cnt+1$ 组。

## AC Code

代码已分段给出，不给出完整代码

[CF AC记录](https://codeforces.com/contest/1539/submission/120286639)

[洛谷AC记录](https://www.luogu.com.cn/record/52051072)

---

## 作者：ZolaWatle (赞：2)

#### 题目大意

给定 $n$ 个数 $a_i$，你可以将这 $n$ 个数分成若干组。每一组的元素需要满足按升序排列后，任意两个香菱的元素值之差不超过 $x$。另外地，在分组前，你可以向这 $n$ 个数中加入至多 $k$ 个元素值任意的数。你需要求出最少可以将这些数分为几个组。

#### 解题思路

由于分组并不要求按照给定的顺序，我们可以考虑贪心。我们将 $a_i$ 由小到大排序，然后扫一遍，记录下每个间隙的值。对于“间隙”，我们这样定义：对于位置 $i$，若排序后的 $a_i-a_{i-1}>x$，则称 $i$ 是一个“间隙”，它的值为 $w=a_i-a_{i-1}$。考虑最劣情况。设“间隙”的个数为 $tot$，如果无论如何加入新元素都无法减少间隙的个数，答案显然为 $ans=tot+1$。

接下来对所有的“间隙”从小到大排序，这样就能保证用最少的新元素“填满”最多的“间隙”。对于每一个“间隙”，我们考虑最少需要多少个新元素才能将其“填满”。我们设在这个间隙中添入 $nd$ 个新元素，则此时它的值为 $w'=\dfrac{a_i-a_{i-1}}{nd+1}=\dfrac{w}{nd+1}$。为了满足 $\leq x$ 的条件，我们得到关系如下：

$$\dfrac{w}{nd+1} \leq x$$

$$w \leq x\cdot (nd+1)$$

$$nd \geq \dfrac{w}{x}-1$$

即 $nd_{min}=\lceil \dfrac{w}{x} \rceil-1$。

对于每一个“间隙”，若当前剩余的 $k\geq nd_{min}$，将 $ans$ 自减，然后将 $k$ 减去这个 $nd_{min}$ 即可。重复这个操作，直到无“间隙”剩余或某一时刻的 $k<nd_{min}$。最后剩下来的这个 $ans$ 即为答案。

记得开 ll。

#### 完整代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define re register int
#define rl register ll
#define rep(i,a,b) for(re i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(re i=(a),i##end=(b);i>=i##end;--i)
#define mem(arr,val) memset(arr,val,sizeof(arr))
#define cpy(a1,a2) memcpy(a1,a2,sizeof(a2))
using namespace std;

const int N=2e5+10;
int n,tot,ans;
ll k,x,a[N],lj[N];

inline int rint()
{
    re x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}
inline ll rll()
{
    rl x=0ll,f=1ll; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1ll; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}

signed main()
{
	n=rint(),k=rll(),x=rll();
	rep(i,1,n) a[i]=rll();
	sort(a+1,a+n+1);
	
	rep(i,2,n)
		if(a[i]-a[i-1]>x)
			lj[++tot]=a[i]-a[i-1];
	ans=tot+1;
	
	sort(lj+1,lj+tot+1);
	rep(i,1,tot)
	{
		rl nd=lj[i]/x+1ll*(lj[i]%x!=0)-1ll;
		if(k-nd<0) break;
		k-=nd;
		--ans;
	}
	
	printf("%d",ans);
    return 0;
}
```

感谢阅读！

---

## 作者：zMinYu (赞：1)

## 题面

给定 $n$ 个数 $a_i$，你可以将这 $n$ 个数分成若干组。每一组的元素需要满足按升序排列后，任意两个相邻的元素值之差不超过 $x$。另外地，在分组前，你可以向这 $n$ 个数中加入至多 $k$ 个元素值任意的数。你需要求出最少可以将这些数分为几个组。

## 思路

这是一道贪心题。

先考虑 $k=0$ 时，会被分成几个组。很显然，如果有两个相邻的元素值之差超过 $x$ 的，那么这两个元素之间就要分开，使它们处于不同的组中。我们设有 $m$ 个如上述要分开的地方，那么答案为 $m+1$。但是这仅限于 $k=0$ 时，对于 $k>0$ 的情况，我们就要拿这 $k$ 个数去填 $m$ 个断开的地方，于是，我们就要考虑如何填这 $k$ 个数，能使填好的地方尽可能多。随后，我们进一步考虑怎么填才能使填一处所用的数尽可能少。于是，对于任意 $1 < i \le n$ 且 $a_i-a_{i-1}>x$，当 $a_i-a_{i-1}$ 能整除 $x$ 时，填一处所用的数的最小数量为 $\frac{a_i-a_{i-1}}{x}-1$，否则为 $\lfloor\frac{a_i-a_{i-1}}{x}\rfloor$。

那么到这里，思路就结束了。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 7;
int n;
long long k, x, a[N];
vector<long long> vec;
signed main() {
	cin >> n >> k >> x;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n);
	for (int i = 2; i <= n; i++) {
		if (a[i] - a[i - 1] > x) {
			int t = (a[i] - a[i - 1]) / x;
			if ((a[i] - a[i - 1]) % x == 0) t--;
			vec.push_back(t);
		}
	}
	sort(vec.begin(), vec.end());
	int ans = 0;
	for (int i = 0; i < (int) vec.size(); i++) {
		if (k < vec[i]) break;
		k -= vec[i], ans++; 
	}
	cout << vec.size() - ans + 1;
	return 0;
}
```

---

## 作者：lostxxx (赞：0)

# 题目分析

我们发现，如果能插入一个数字，那么必定插入一个数字，但是频繁的使用 $a_i-a_{i-1}$ 不是很方便，于是我们使用一个差分数组 $dif_i$ 表示第 $i$ 个空的差，由 $a_i-a_{i-1}$ 得到，但是为了保证尽量有序，所以我们先将 $a$ 数组排序，然后求出差分数组 $dif$ 后再将 $dif$ 从小到大排序。至于为什么从小到大排序，我们可以思考下面一组样例。

```
5 3 2
1 5 9 13 21 23 25
```

正确输出应该为 $2$ ，如果我们花费三个代价全部放在数字 $13$ 和 $21$ 之间的话，那么答案会变为 $4$ ，明显不优。所以我们从小到大处理 $dif$ 数组。

至于如何快速加数，我们可以直接求得加数的数量 $\frac{dif_i-1}{x}$ 然后 $k$ 减去数量即可，直到 $k$ 不够或者小于等于 $0$ 。

然后再遍历一遍 $dif$ 数组寻找，如果 $dif_i > x$ ，则 $ans$ 加 $1$ 。

代码如下

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,x;
ll a[200100];
ll dif[200100];
ll ans=1;
int main(){
	cin>>n>>k>>x;
	for (int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for (int i=2;i<=n;i++)
		dif[i]=a[i]-a[i-1];
	for (int i=2;i<=n;i++){
		if (dif[i]<=x)
			continue;
		else if (k>0 && dif[i]>x){
			ll cost=(dif[i]-1)/x;
			if (cost<=k){
				k-=cost;
				dif[i]=0;
			}else
				break;
		}else if (k==0)
			break;
	}
	for (int i=2;i<=n;i++){
		if (dif[i]>x)
			ans++;
	}
	cout<<ans;
}
```

---

## 作者：liangkairui (赞：0)

# [Stable Groups](https://www.luogu.com.cn/problem/CF1539C) 题解
## 题意简述
现有 $n$ 个数，每个数为 $a_i$，你可以在其中任意的位置插入 $k$ 个数，然后将它们分成若干组，使得每组中相邻的数的绝对值的差小于等于 $x$。
## 思路方法
~~标签里面有贪心，所以~~我们考虑贪心。

可以看出绝对值差越小就越好处理。所以我们先将数组 $a$ 进行排序，然后算相邻两位的差，将这个差进行排序。

当我们发现绝对值的差大于 $x$，就考虑两种操作：**插入一个或多个数**或者**将这两个数分开存在两组中**。

如果要插入数，当 $a_i-a_{i-1}$ 能整除 $x$ 时，可插入 $\frac{a_i-a_{i-1}}{x}-1$ 个数，否则可插入 $\frac{a_i-a_{i-1}}{x}$ 个数。

## 注意
本题数据范围要求使用 `long long`。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N=2*1e5+7;
inline ll read(ll &x){		//快读 
	char c=getchar();
	int f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	x=0;
	while(c>='0'&&c<='9'){x=x*10+int(c-'0');c=getchar();}
	return x*f;
}
ll a[N],c[N],cnt=0;
int main()
{
	ll n,k,x;
	read(n);
	read(k);
	read(x);
	for(ll i=1;i<=n;i++)read(a[i]);
	sort(a+1,a+n+1);	//sort默认从小到大排 
	for(ll i=2;i<=n;i++){
		if(a[i]-a[i-1]>x){		//判断差值是否超过x 
			c[++cnt]=(a[i]-a[i-1])/x;
			if((a[i]-a[i-1])%x==0){	//如果差值刚好可以被x整除，则需要插入的数-1 
				c[cnt]--; 
			}
		}
	}
	sort(c+1,c+cnt+1);
	ll sum=0,ans=0;
	for(ll i=1;i<=cnt;i++){
		if(c[i]+sum>k)break;
		sum+=c[i];
		ans++;
	}
	cout<<cnt-ans+1;
	return 0;
}
```
求管理大大过审，请各位 dalao 指点。

---

## 作者：Rookie_t (赞：0)

这道题可以使用贪心策略。

1. 根据题目要求输入变量。 

2. 把输入的 $n$ 个整数从小到大排序。 

3. 存储相邻两数的差，把这些差值排序，然后初始化 $ans$ 变量。

4. 根据题意，对于某一个数，插入一个数，就可以减少一个分组。 

5. 在插入时，我们就使用输入给出的 $k$ 个数，把两数之差变得尽量大，然后输出初始组数减去减小组数即可。 

我们可以在中间加入 $\left \lfloor a_i-a_{i-1} \over  x  \right \rfloor-1$ 或 $\left \lfloor a_i-a_{i-1} \over  x  \right \rfloor$ 个元素。 
 
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200010],n,k,x,ans;
vector<int> v;
signed main(){
	cin>>n>>k>>x;
	for(int i = 1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	for(int i = 1;i<=n;i++){
		if(a[i+1]-a[i]>x){
			v.push_back(a[i+1]-a[i]);
		}
	}
	ans = v.size();	
	ans++;
	sort(v.begin(),v.end());
	int len = v.size();
	for(int i = 0;i<len;i++){
		int t = v[i]/x;
		if(!(v[i]%x)){
			t--;
		}	
		if(k>=t){
			k -= t;
			ans--;
		}
		else{
			break;
		}			
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路
我们可以采取贪心的策略。

题目要求我们尽可能让相邻两数之间差最小。所以我们可以对原数组排序，这样就是不进行任何操作的情况下，使得相邻两数之间差最小的最佳情况。

接下来，我们对排序后的数组进行遍历。如果我们发现 $a_i - a_{i-1} (1 < i \le n)$ 比 $x$ 大，那么我们就考虑往中间加数。

这里，我们先暂时不管“至多加入 $k$ 个元素”这个条件。很显然，我们需要在这两个数中间加入 $\left\lfloor \frac{a_i - a_{i-1}}{x} \right\rfloor -1$ 个元素。

那么怎么满足“至多加入 $k$ 个元素”这个条件呢？只需要记录每次添加的元素数量，优先满足数量小的操作即可。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,x,cnt = 0,tot = 0,ans = 0;
long long num[200005],add[200005];
int main(){
	scanf("%lld%lld%lld",&n,&k,&x);
	for(long long i = 1; i <= n; i++){
		scanf("%lld",&num[i]);
	}
	sort(num+1,num+1+n);
	for(long long i = 1; i < n; i++){
		if(num[i+1]-num[i] > x){
			tot++;
			add[tot] = (num[i+1]-num[i])/x;
			if((num[i+1]-num[i])%x == 0){
				add[tot]--;
			}
		}
	}
	sort(add+1,add+1+tot);
	for(long long i = 1; i <= tot; i++){
		if(cnt+add[i] > k){
			break;
		}
		cnt += add[i];
		ans++;
	}
	printf("%lld",tot-ans+1);
	return 0;
}
```

---

## 作者：hubin1 (赞：0)

# Stable Groups

## 题目大意

题目翻译清晰，可以自己看题。[题面](https://www.luogu.com.cn/problem/CF1539C)

## 思路

1. 首先我们会想到贪心。
2. 一开始对这 $n$ 个数进行排序，然后预处理它们两两之间的差值。
3. 对于这些差值进行排序，并计算出在不加入任意元素前的答案。
4. 对于某一个位置，插入一定的数，可以减少一个分组，从而符合题意。
5. 在插入时，我们要合理使用这 $k$ 个数，所以要把数之间的差变得尽量大，从而节约数。
6. 最后答案即：不加入之前的组数减去可以减小组数。

## Code

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define debug(x) cerr<<#x<<"="<<x<<"\n"

const int MAX=2e5+10;
int a[MAX];
// int b[MAX];
vector<int>b;

signed main()
{
	int n,k,x;
	scanf("%lld%lld%lld",&n,&k,&x);
	
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	
	sort(a+1,a+1+n);//升序排序
	
	for(int i=1;i<=n;i++)
		if(a[i+1]-a[i]>x)
			b.push_back(a[i+1]-a[i]);//预处理差值并存入 b
	
	int ans=b.size()+1;
	
	sort(b.begin(),b.end());
	
	for(int i=0;i<(int)b.size();i++)
	{
		int t=b[i]/x;
		if(b[i]%x==0)//对于倍数进行特判，因为可以节约一个数
			t--;
		if(k>=t)//剩余数量足够插入
		{
			k=k-t;
			ans--;
		}
		else
			break;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Engulf (赞：0)

我们先对 $a$ 排序，这样能保证相邻两个数的差值尽可能小。

然后对 $a$ 进行分组，把不合题意的分开来。

又因为我们有 $k$ 个插入的机会，为了合并尽可能多的组，我们可以以差值按照小到大排序，然后逐一满足。

注意一下如果差值 $d$ 被 $x$ 整除，需要插入的数 $k$ 应当减一。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;

const int N = 2e5 + 5;
int n;
LL k, x;
LL a[N];

int main()
{
	scanf("%d%lld%lld", &n, &k, &x);
	for (int i = 1; i <= n; i ++ ) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	vector<PII> groups;
	int l = 1;
	for (int i = 2; i <= n; i ++ )
	{
		if (a[i] - a[i - 1] > x)
		{
			groups.push_back({l, i - 1});
			l = i;
		}
	}
	groups.push_back({l, n});
	vector<LL> gap;
	for (int i = 1; i < groups.size(); i ++ )
	{
		auto cur = groups[i], pre = groups[i - 1];
		LL gp = a[cur.first] - a[pre.second];
		LL d = gp / x;
		if (gp % x == 0) d -- ;
		gap.push_back(d);
	}
	int res = groups.size();
	sort(begin(gap), end(gap));
	for (int i = 0; i < gap.size(); i ++ )
	{
		if (gap[i] <= k)
		{
			k -= gap[i];
			res -- ;
		}
		else break;
	}
	cout << res << endl;
	return 0;
}
```

---

## 作者：Booksnow (赞：0)

# Stable Groups

## 题目大意

给定 $n$ 个数 $a_i$ ，你可以将这些数分成若干组，但每一组的元素满足按升序排列后，相邻两个元素值的差不超过 $x$ 。在分组前，你可以向这些数中插入至多 $k$ 个为可以试任意值的元素。

问最少能够分成几组满足要求的数？

## 分析

其实这道题应该是一个比较明显的**贪心**吧。

考虑先直接将这 $n$ 个数尽量分组，实在不能连在一起的就先断开，求出**不插入元素**最少分出的组。

怎么分？先排个序，然后从头到尾遍历，能够放一起就放，不能也就是差超过 $x$ 了，断开就完了。

不难发现这样我们分出来的组存在**严格的大小关系**，于是我们能够很轻松的求出每个组之间的差值。即用元素相对较大组中的最小元素减去元素相对较小组中的最大元素，将其存在数组内。

求出这些差值后我们排个序，然后就可以开始填了，很显然**先合并差值小的两个组一定不劣**。

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w*=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int n,k,x,ans;
int tot,a[N],com[N];
inline bool cmp(int x,int y) { return x>y; }
signed main()
{
	n=read(),k=read(),x=read();
	for(register int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1,cmp);
	for(register int i=1;i<n;i++) //不加学生，分组
		if(a[i]-a[i+1]>x) com[++tot]=a[i]-a[i+1];
	ans=tot+1;
	sort(com+1,com+tot+1);
	for(register int i=1;i<=tot;i++){
		int need=com[i]/x;
		if(com[i]%x==0) need-=1;
		if(need>k) break;
		else k-=need,ans-=1;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Goodrage (赞：0)

这里提供一种暴力贪心做法。

**题目大意**

有一个排序后的含有 $n$ 个元素的数组，现在要把它分成小组。如果一个小组中每两个相邻数值之差都不大于 $x$，那么这个小组就是稳定的。

现在，除了这 $n$ 个元素之外，我们还可以加入自己选择的 $k$ 个元素。求出加入 $k$ 个元素后形成稳定小组的最小数量。

**思路解析**

明显是个贪心。先考虑 $k$ = $0$ 的情况。

如果 $k$ = $0$， 那么就不会有别的数值加入，最小的小组数量必定是它原有的小组数量。下面开始分组。

数组 $begend$ 标记每一小组的开头和结尾  - 1表示开头，2表示结尾。
```cpp
	sort(a+1,a+n+1);
	int beg,ende;//每组开头，每组结尾
	beg=1;
	top=1;//小组数
	for(int i=2;i<=n;i++)
	{
		if((a[i]-a[i-1]<=x)) continue;//差距小于x，不能分
		if((a[i]-a[i-1])>x)//分
		{
			ende=i-1;//这个元素是新一组的开头，它的上一个必定是上一组的结尾
			begend[top][1]=beg;//标记开头
			begend[top][2]=ende;//标记结尾
			top++;//多了一组
			beg=i;//新的一组从这里开始
		}
	}
	begend[top][1]=beg;//最后一组不会被在循环中标记，所以要把它也带上
	begend[top][2]=n;//最后一组的最后一个元素肯定是整个数组最后一个元素
	if(k==0)//判k是否等于0
	{
		printf("%d\n",top);//直接输出组数
		return 0;//结束了？
	}
```
但问题来了 - 如果需要添加元素，添加到哪里呢？

下面引入贪心思路 - 可少的补，多的不补，直到补完为止。

我们要算出每两组之间的空隙至少要插入多少个元素，才能将他们连上。因此，我们认为新加入的元素到两边相邻的元素距离相等。

$diff$ 数组即为每两组元素之间至少需要补充几个元素才能合并为一组。
```
	for(int i=1;i<top;i++)//枚举组数。
	{
		int curdif=a[begend[i+1][1]]-a[begend[i][2]];//这组的头，上组的尾
		diff[i]=curdif/x; //假定每两个新增元素之间差为x，求加入几个元素
		if(curdif%x==0) diff[i]--; //注意！！如果距离正好是x的倍数，要减去1.假如距离是2x，则只需要在x的位置上放一个就足够了，不要多放！
	}
```
贪心来了
```
	sort(diff+1,diff+top);//按需要元素少的排序
	int anstop=top;
	for(int i=1;i<top;i++)
	{
		if(k<=0) break;//全补完了
		if(k>=diff[i])//可以补上
		{
			k-=diff[i];//补
			anstop--;//两组合并为一组，组数减少
		}
		else break;//补不上了，直接退出
	}
	printf("%lld\n",anstop);//输出答案
   return 0;//真正结束了
}

```
Q： 如果补完后 $k$ 有剩余，但是后面的 $diff_i$ 都比 $k$ 大，会影响结果吗？

A： 不会。剩下的元素你塞哪里都不会影响组数。

**比赛代码**
```
#include<bits/stdc++.h>
using namespace std;
#define int long long //十年CF一场空，不开longlong见祖宗!
string s;
int a[201010];
int begend[200100][2],top;
int diff[201100];
int ans=0;
signed main()
{
	int n,k,x;
	scanf("%lld%lld%lld",&n,&k,&x);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	int beg,ende;
	beg=1;
	top=1;
	for(int i=2;i<=n;i++)//先分一波组
	{
		if((a[i]-a[i-1]<=x)) continue;
		if((a[i]-a[i-1])>x)
		{
		//\	printf("%lld aaa %lld\n",a[i]-a[i-1],x);
			ende=i-1;
			begend[top][1]=beg;
			begend[top][2]=ende;
			top++;
			beg=i;
		}
	}
	begend[top][1]=beg;
	begend[top][2]=n;
	if(k==0)//其实没啥用的特判
	{
		printf("%d\n",top);
		return 0;
	}
	for(int i=1;i<top;i++)//算两组之间需要补几个
	{
		int curdif=a[begend[i+1][1]]-a[begend[i][2]];
		diff[i]=curdif/x;
		if(curdif%x==0) diff[i]--;
	}
//	for(int i=1;i<top;i++)
//		printf("%d ",diff[i]);
	sort(diff+1,diff+top);
	int anstop=top;
	for(int i=1;i<top;i++)//可少的补
	{
		if(k<=0) break;
		if(k>=diff[i])
		{
			k-=diff[i];
			anstop--;
		}
		else break;
	}
	printf("%lld\n",anstop);
	return 0;
}
```
希望各位CF不掉分。

---

