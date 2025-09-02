# [POI 2003] Chocolate

## 题目描述

有一块 $n\times m$ 的矩形巧克力，准备将它切成 $n\times m$ 块。

巧克力上共有 $n-1$ 条横线和 $m-1$ 条竖线，你每次可以沿着其中的一条横线或竖线将巧克力切开，无论切割的长短，沿着每条横线切一次的代价依次为 $y_1,y_2,…,y_{n-1}$，而沿竖线切割的代价依次为 $x_1,x_2,…,x_{m-1}$。

例如，对于下图 $6\times4$的巧克力：

![](https://cdn.luogu.com.cn/upload/image_hosting/s0j2oloj.png)


我们先沿着三条横线切割，需要 $3$ 刀，得到 $4$ 条巧克力，然后再将这 $4$ 条巧克力沿竖线切割，每条都需要 $5$ 刀，则最终所花费的代价为 $y_1+y_2+y_3+4\times (x_1+x_2+x_3+x_4+x_5)$。

当然，上述简单切法不见得是最优切法，那么怎样切割该块巧克力，花费的代价最少呢？

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10000$，$1\le m\le 10000$。

## 样例 #1

### 输入

```
6 4
2
1
3
1
4
4
1
2```

### 输出

```
42
```

# 题解

## 作者：xieyuhao2022 (赞：2)

## Solution

我们将题目简化为：现有集合 $X,Y$，里面有已有一些数字。

我们观察题目，不难得出每次切割的代价为，其数值与前面不属于同个集合的数字个数 $+1$ 的乘积。

例如，若横向切下一刀，此时巧克力变为两块，那么竖向切割时就需要切两次，即做两倍代价。以此类推，即可得出上述结论。

进一步分析，我们不难得出应优先选择数值大的进行切割。

对于同个集合，显然数值大的排序靠前更优。

对于不同集合，即不同方向上切割，后切的自然需要在原基础上多切一刀，那么数值大的会越来越大。反之，我们则需要优先选择数值大的。

因此，我们可以将两个集合合并、排序后进行操作。

时间复杂度为 $O(N \log{N})$，可以通过本题。

## Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=2e4+5;	//注意开两倍大小
int n,m,tot,x_,y_;
long long ans;
struct qwq{
	int val,id;
}a[N];
bool cmp(qwq x,qwq y){
	return x.val>y.val;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		cin>>a[i].val;
		a[i].id=1;
	}
	for(int i=n;i<n+m-1;i++){
		cin>>a[i].val;
		a[i].id=2;
	}
	tot=n-1+m-1;
	sort(a+1,a+1+tot,cmp);
	for(int i=1;i<=tot;i++){	//记录出现过的不同元素
		if(a[i].id==1) ans+=(y_+1)*a[i].val,x_++;
		else ans+=(x_+1)*a[i].val,y_++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：lidundun (赞：2)

# Chocolate
看到这道题，我们第一时间想到贪心。

我们发现题目等价于有两个集合 $x y$ 里面有一些数字，现在将两个集合进行排序。

每个数字的代价为其数值与前面不属于同个集合的数字个数 $+\mathtt{1}$ 的乘积，求最小代价。

我们发现对于同个集合，显然数值大的排序靠前更优。

对于不同集合的数, 我们考虑当他们相邻时，交换位置相当于总代价改变他们之间的差值, 显然也是大的数字靠前代价更小一些。

所以，我们将 $x y$ 丢到一起按照从大到小进行排序，同时计算答案即可。

# 防作弊代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,a,shuzt=1,hengzt=1,ans=1;
struct s{
	int nm,xy;
}l[2000001];
bool cmp(s x,s y)
{
	return x.nm>y.nm;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<n;i++)
	{
		scanf("%d",&l[i].nm);
		l[i].xy=1;
	}
	for(int i=n;i<=m+n-2;i++)
	{
		scanf("%d",&l[i].nm);
	}
	sort(l+1,l+n+m-1,cmp);
	for(int i=1;i<=n+m-2;i++)
	{
		if(l[i].xy==1)
		{
			ans+=l[i].nm*hengzt;
			shuzt++;
		}
		else
		{
			ans+=l[i].nm*shuzt;
			hengzt++;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

检查一下你的变量初值吧

---

## 作者：Great_Influence (赞：2)

发现数据范围是 $10^4$ ，显然是 $O(nm)$ 卡一卡能过的。

注意到我们每一维肯定都是从大到小一刀刀切， 排完序后就只需要考虑横着切和竖着切的相对顺序了。

写个 $O(nm)$ 的 $dp$ 就可以了。注意最好将第一维滚动节省访问数组的时间。

按照题意模拟会 TLE ?

我们先分析一下原来的 $dp$ 方程:

$$dp[i][j] = \min(dp[i-1][j]+a[i]*j,dp[i][j-1]+b[j]*i)$$

容易发现瓶颈在于 $O(nm)$ 次的乘法。我们考虑利用后缀和将乘法优化成加法:

$$dp[i][j] = \min(dp[i-1][j]+B[j+1],dp[i][j-1]+A[i+1])$$

这个式子是怎么来得呢? 我们考虑横着切完这一刀后，后面竖着的没切的每一刀的相对顺序都会向后移动一格，每一个所乘的系数都会 $+1$ 。我们将初值设置为 $dp[0][0]=A[1]+B[1]$ ，那么所要的答案就是 $dp[n][m]$ 。

这样会比直接使用乘法快大概10倍左右。~~(当然你要是用 $O2$ 乘法也许也能跑过去。。。)~~

核心代码:
```cpp
	#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
	#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)

	sort(a + 1, a + n + 1, greater<int>());
	sort(b + 1, b + m + 1, greater<int>());
	Repe(i, n - 1, 1) a[i] += a[i + 1];
	Repe(i, m - 1, 1) b[i] += b[i + 1];
	dp[0][0] = a[1] + b[1];
	Rep(i, 1, m) dp[0][i] = dp[0][i - 1] + a[1];
	cr = dp[0];
	Rep(i, 1, n)
	{
		ls = cr, cr = dp[i & 1];
		cr[0] = ls[0] + b[1];
		Rep(j, 1, m) cr[j] = min(ls[j] + b[j + 1], cr[j - 1] + a[i + 1]);
	}

```

---

## 作者：_EternalRegrets_ (赞：1)

#### update on 24.06.29：修改复杂度

[传送门](https://www.luogu.com.cn/problem/P5948)

本题贪心。

将 $x$ 数组和 $y$ 数组放到集合 $a$ 里。

通过尝试可以证明，当 $x_i$ 等于 $y_j$ 时，先切割 $x_i$ 处，再切割 $y_j$ 处，与先切割 $y_j$ 处，再切割 $x_i$ 处的代价是相同的。(题解末尾附证明)

同时，不难发现应该优先切割数值大的线。（贪心）

于是直接对集合从小到大 $a$ 排序，通过 $id$ 区分竖切或横切。

遍历 $a$ 数组即可。复杂度 $O(N \log N)$。 （感谢 UID:728079 指正）

#### code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct node{
    int x;
    int id;
};

node a[20004];

int ans=1e18;
int n; int m;
bool cmp(node x,node y){
    return x.x>y.x;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    //freopen("choco.in","r",stdin);
    //freopen("choco.out","w",stdout);

    cin>>n;
    cin>>m;

    for(int i=1;i<=n+m-2;i++){
        cin>>a[i].x;
        if(i>=n){
            a[i].id=1;
        }
        else{
            a[i].id=0;
        }
    }

    ans=0;
    sort(a+1,a+1+n+m-2,cmp);

    int u; int l; u=l=0;
    for(int i=1;i<=n+m-2;i++){
        if(a[i].id==0){
            u++;
            ans+=(l+1)*a[i].x;
        }
        else{
            l++;
            ans+=(u+1)*a[i].x;
        }
    }

    cout<<ans;
    return 0;
}
```

#### 所提命题证明：

设 $x_i = y_j = t$ , $u$ 是横向已切个数，$l$ 是竖向已切个数。

先切割 $x_i$ 处，再切割 $y_j$ 处：

$t\times(l+1)+t\times(u+2)$

先切割 $y_j$ 处，再切割 $x_i$ 处：

$t\times(u+1)+t\times(l+2)$

化简两式，得两式都等于 $(u+l)\times t+3\times t$。

得证，证毕。

---

## 作者：Adolfo_North (赞：1)

提供一种比较清新的做法。

思路：贪心。

思考：如果在巧克力上横向切一刀，那么纵向要切的刀数就会加一。如果在巧克力上纵向切一刀，那么横向要切的刀数就会加一。

结论：要先切代价大的，再切代价小的。

做法：横切代价与纵切代价放到一起排序，依次计算需要的代价即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int xy;
	bool flag;//flag区分是纵切代价还是横切代价。 
}a[20010];
int cnt[2];//cnt[i]代表在某个方向上已经有多少块巧克力。 
bool cmp(node a,node b){
	return a.xy>b.xy;
}
int main()
{
    int n,m;
    long long ans=0;
    cin>>n>>m;
	n--;
	m--;
    for(int i=1;i<=n;i++)cin>>a[i].xy;
	for(int i=1;i<=m;i++){
		cin>>a[i+n].xy;
		a[i+n].flag=1;
	}
	sort(a+1,a+n+m+1,cmp);
	for(int i=1;i<=n+m;i++) {
		ans+=(long long)a[i].xy*(cnt[!a[i].flag]+1);//用当前方向的代价去乘以另一个方向上的块数。 
		cnt[a[i].flag]++;//切了一刀，块数加一。 
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：qiuweilin666 (赞：1)



#### 思路：贪心
我们发现题目等价于有两个集合 $X ,Y$，里面有一些数字，现在将两
个集合进行排序。每个数字的代价为其数值与（前面不属于同个集合的数字个数 +1）
的乘积，求最小代价。
我们发现对于同个集合，显然数值大的排序靠前更优。
对于不同集合的数, 我们考虑当他们相邻时，交换位置相当于总代
价改变他们之间的差值, 显然也是大的数字靠前代价更小一些。
所以我们将 $X, Y$ 丢到一起按照从大到小进行排序，同时计算答案
即可。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a,shu=1,heng=1,ans;
struct abc{
	int num,xy;
}l[2000001];
bool cmp(abc x,abc y){
	return x.num>y.num;
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d",&l[i].num);
		l[i].xy=1;
	}
	for(int i=n;i<=m+n-2;i++){
		scanf("%d",&l[i].num);
	}
	sort(l+1,l+n+m-1,cmp);
	for(int i=1;i<=n+m-2;i++){
		if(l[i].xy==1){
			ans+=l[i].num*heng;
			shu++;
		}
		else{
			ans+=l[i].num*shu;
			heng++;
		}
	}
	printf("%lld",ans);
	return 0;
}
```
不喜勿喷

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P5948)

### $\texttt{Description}$

给定一个 $n \times m$ 的巧克力，问把巧克力切成 $1 \times 1$ 的小块的最小代价，切的地方对应的代价已在输入中给出。

### $\texttt{Solution}$

考虑贪心的做法，一点都不难。

思路如下：

- 首先我们得知道两块木板切开之后不能够叠在一起切。如果不考虑任何情况，这时我们就需要把每条线都切一次，这肯定不是最小代价。
- 那么我们现在考虑横向切完以后，变成了两块木板，且木板不能叠在一起切。如果横向切了一刀，那么就有两个木板，剩下没有切的竖线就必须多切一次。所以就有如下规律：
- 对于每一条横线要切多少次，就是前面切的竖线数量 $+1$。
- 对于每一条竖线要切多少次，就是前面切的横线数量 $+1$。

### $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e4 + 5;

struct node {
	int val, op;
	// val 代表代价
	// op 代表是横线还是竖线
} a[N * N];

bool cmp(node x, node y) {
	return x.val > y.val;
	// 按代价从大到小排序
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i < n; i ++) {
		cin >> a[i].val;
		a[i].op = 0; // 0代表是横线
	}
	
	for (int i = n; i < n + m - 1; i ++) {
		cin >> a[i].val;
		a[i].op = 1; // 1代表竖线
	}
	
	sort(a + 1, a + n + m, cmp);
	int h = 0, s = 0;
	int ans = 0;
	
	for (int i = 1; i < n + m; i ++) {
		if (a[i].op == 1) { // 竖线
			ans += (h + 1) * 1ll * a[i].val;
			s ++;
		} else { // 横线
			ans += (s + 1) * 1ll * a[i].val;
			h ++;
		}
	}
	
	cout << ans;
	return 0;
}
```

完结。

---

## 作者：George222 (赞：0)

一眼贪心，为什么呢？

从题面中我们可以看见纵向切一刀横向就多一刀的代价，所以我们把所有代价混一起排序从大到小切割即可。

（结尾附证明）

注：要开 `long long`，最坏情况约为：$10000 \times \max(y) + 10000 \times 10000 \times \max(x)$，肯定炸 $10^9$。

代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n, m;
struct Choco
{
    int x;
	int flag;
} a[20005];
int cnt[2];
bool cmp(Choco a, Choco b)
{
	return a.x > b.x;
}
ll ans;

int main()
{
    cin >> n >> m;
	n--, m--;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].x;
        a[i].flag = 0;
    }
	for (int i = 1; i <= m; i++)
    {
		cin >> a[i + n].x;
		a[i + n].flag = 1;
	}
	sort(a + 1, a + n + m + 1, cmp);
	for (int i = 1; i <= n + m; i++)
    {
		ans += a[i].x * (cnt[!(a[i].flag)] + 1); 
		cnt[a[i].flag]++;
	}
	cout << ans << "\n";
    return 0;
}
```

---

附：证明

通过题面我们可以看出，如果我们纵向切了 $1$ 刀，此时想去切横向就要增加 $2 \times x$ 的代价而不是 $x$ 的代价。

推导出：对于切一次的代价，下一次以不同方向切的必然会增加一倍的代价。

所以我们最好的解决方法就是将代价从大到小排序来避免较大的代价变得更大。

以此，证明结束。

---

## 作者：lqsy002 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P5948)。

## 解题思路

由于每条线被切至少一次，所以一条线每被切一次就增加一份代价。

因此每个交叉点上用代价较大的线切代价较小的线比较优，所以先切代价大的后切代价小的。

总体思路如下：

1. 将两种切法的代价分别从大到小排序。

2. 选择当前交叉点上代价较大的切法进行切割。

3. 将指针指向下一个交叉点。

4. 重复二三步骤，遍历每一个交叉点。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 10010
using namespace std;
int n,m,ans;
int x[maxn],y[maxn];
bool cmp(int a,int b){
    return a>b;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;++i)
		cin>>x[i];
	for(int i=1;i<m;++i)
		cin>>y[i];
	sort(x+1,x+n,cmp);
	sort(y+1,y+m,cmp);
	for(int i=1,px=1,py=1;i<(n+m-1);++i)
		if(py>=m||x[px]>y[py])
            ans+=x[px++]*py;
		else
            ans+=y[py++]*px;
	cout<<ans;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

[双倍经验](https://www.luogu.com.cn/problem/P1324)。

显然我们应该尽可能地先选择代价大的，否则到后面它就会以几倍代价出现，所以先将 $x,y$ 排序，维护一下横着切了几刀，竖着切了几刀，计算答案即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
struct node
{
	int sx,v;
}c[N<<1];
int cmp(node a,node b)
{
	return a.v>b.v;
}
signed main()
{
	int n,m,hcut=0,wcut=0;
	cin>>n>>m;
	for(int i=1;i<n;i++) cin>>c[i].v,c[i].sx=0;
	for(int i=1;i<m;i++) cin>>c[n+i-1].v,c[n+i-1].sx=1;
	sort(c+1,c+n+m-1,cmp);
	int ans=0;
	for(int i=1;i<n+m-1;i++)
	{
		if(c[i].sx)
		{
			wcut++;
			ans+=(hcut+1)*c[i].v;
		}
		else
		{
			hcut++;
			ans+=(wcut+1)*c[i].v;
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：__log__ (赞：0)

### P5948 [POI2003] Chocolate
[题面折跃门](https://www.luogu.com.cn/problem/P5948) [双倍经验](https://www.luogu.com.cn/problem/P1324)

#### $\text{Part0}$ 先补上一个样例解释：
依次切下 $x_5$ $y_1$ $x_3$ $x_1$ $y_3$ $x_4$ $x_2$ $y_2$（当然顺序不唯一），

代价总和为 

$4\times1+4\times2+3\times2+2\times2+2\times4+1\times3+1\times3+1\times6=42$。

#### $\text{Part1}$ 所以这道题到底是什么？？？

考虑代价大小和切下顺序是否有关系。

不难得知代价越大的一刀应该越早切下。

下面感性理解一下这个贪心策略的正确性：

* 只考虑其中两刀的关系：
* 如果两刀同为横着切或同为竖着切，那么这两刀的先后顺序没有区别。
* 如果两刀一刀横着一刀竖着：
 	
    * 两刀的代价均为 $x$，那这两刀先切哪一刀也没有区别。
    * 两刀代价不同，设竖着的一刀代价为 $a$，横着的一刀代价为 $b(a>b)$。
    	
        1. 先横着切：横切为 $b$，竖切为 $a\times2$，所以总代价为 $2a+b$。
        2. 先竖着切：竖切为 $a$，横切为 $b\times2$，所以总代价为 $a+2b$。
        
        因为 $a>b$，所以先切竖的那一刀代价更小，也就是说如果有横竖各一刀，先切代价大的那一刀总代价最小。

然后按照这个东东写代码就 ok 了。
#### $\text{Part2}$ Code
~~不开 long long 见祖宗~~
```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;

int n, m, ans;
int a[10100], b[10100];

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i < n; ++i) cin >> a[i];
    for(int j = 1; j < m; ++j) cin >> b[j];
    sort(a + 1, a + n), sort(b + 1, b + m);
    int i = n - 1, j = m - 1;
    while(i && j) {
        if(a[i] > b[j]) ans += (a[i--] * (m - j)); // 如果竖着切的代价更大，就先切竖的
        else ans += (b[j--] * (n - i)); // 否则先写横的
    }
    while(i) ans += a[i--] * m; // 如果横的先切完了，剩下的全切竖的
    while(j) ans += b[j--] * n; // 同理
    cout << ans;
    return 0;
}

```

---

## 作者：Leowang2009 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P5948)
# 思路
容易想到贪心。显然切的次数是一定的。因为每切一刀就多增加一块，总次数一定是 $n\times m - 1$。所以为了让总代价更小，就应当让代价更高的少切，而代价低的尽量多切。
## 证明
对于两次切割 $a$ 和 $b$ 分两种情况讨论：

1.$a$ 与 $b$ 同向：显然，后切的次数肯定大于等于先切的次数，故应当让代价更高的先切，代价低的后切。

2.$a$ 与 $b$ 异向：不妨设 $a$ 为纵向，$b$ 为横向，且 $a\leq b$。设切之前共 $row$ 行 $col$ 列，若先切 $a$，则总代价为：
$$a\times row + b\times (col + 1) = a\times row + b\times col + b$$
若先切 $b$,则总代价为：
$$a\times (row + 1) + b\times col = a\times row + b\times col + a$$
又 $a\leq b$，故：
$$a\times row + b\times col + a\leq a\times row + b\times col + b$$
故先切 $b$ 代价更低，即代价更高的应当先切。

证毕！
# 代码
代码实现上应当先对两个数组分别排序，然后用类似于归并排序的方式，整合起来的同时计算出答案，还有一定记得开 ```long long``` ~~血的教训~~，总体时间复杂度 $O(N\log N)$
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
long long n,m,x[N],y[N],row=1,col=1,res;
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<n;i++) scanf("%lld",&x[i]);
	for(int i=1;i<m;i++) scanf("%lld",&y[i]);//输入
	sort(x+1,x+n,greater<int>()),sort(y+1,y+m,greater<int>());//从大到小排序
	for(int i=1;i<n+m-1;i++){//计算答案
		if(row>=n||x[col]>y[row]) res+=x[col]*row,col++;
		else res+=y[row]*col,row++;
	}printf("%lld",res);
	return 0;
}
```
完结撒花！

---

## 作者：Infiltrator (赞：0)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://www.luogu.com.cn/problem/P5948)

------------

# Solution

每次选择花费最大的地方切，然后按照题意$O(n)$模拟即可。

证明如下：

>$1.$若两次切割都是横向或竖向，且花费小的比花费大的先切割。    
>设花费小的切割的时候需要切割$a$次，花费大的切割的时候需要切割$b$次，因为中间可能切割了任意次另外一个方向，所以$a <= b$。    
>那么将它们交换，则花费大的对答案的贡献一定小于等于原先的贡献，所以同一方向将花费大的放在花费小的前面一定最优。    
>$2.$若两次切割不是同一方向，且话费晓得比花费大的先切割。    
>设切割前若切花费小的方向花费小的方向需要切$a$刀，切花费大的方向需要切$b$刀。    
>那么先切花费小的，花费大的就需要切$b + 1$刀，反之亦然。    
>因为花费大的$\times (b + 1) + $花费小的$\times a >=$花费大的$\times b + $花费小的$\times (a + 1)$，所以先切花费大的一定最优。  
>$$Q.E.D.$$  

所以最后复杂度就是排序的复杂度。

------------

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define ll long long

const int N = 20000;

int n, m, num, sum[2];

struct Node
{
    int cost, type;
} cut[N + 50];

void Read(int &x)
{
    x = 0; int p = 0; char st = getchar();
    while (st < '0' || st > '9') p = (st == '-'), st = getchar();
    while (st >= '0' && st <= '9') x = (x << 1) + (x << 3) + st - '0', st = getchar();
    x = p ? -x : x;
    return;
}

bool Cmp(Node a, Node b)
{
    return a.cost > b.cost;
}

int main()
{
    ll ans = 0;
    Read(n); Read(m);
    for (int i = 1, x; i <= n - 1; i++) Read(x), cut[++num] = (Node){x, 1};
    for (int i = 1, x; i <= m - 1; i++) Read(x), cut[++num] = (Node){x, 0};
    sort(cut + 1, cut + num + 1, Cmp);
    for (int i = 1; i <= num; i++)
    {
        ans = ans + 1LL * (sum[cut[i].type ^ 1] + 1) * cut[i].cost;
        sum[cut[i].type]++;
    }
    printf("%lld", ans);
    return 0;
}
```

---

