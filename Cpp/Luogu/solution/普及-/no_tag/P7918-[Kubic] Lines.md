# [Kubic] Lines

## 题目背景

建议先看 C 题题目背景。

## 题目描述

平面直角坐标系中有 $n$ 条直线，**任意三条直线不交于一点且没有两条直线重合**。显然这些直线形成了不超过 $\dfrac{n(n-1)}{2}$ 个**交点**。你可以从这些直线中选出一部分，一个点被**覆盖**当且仅当有**至少一条**被选中的直线经过了它。求最少选出多少条直线才能**覆盖**所有**交点**。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^5,|a|,|b|,|c|\le 10^9,a,b$ 不全为 $0$。

||分值|$n$|特殊性质|
|:-:|:-:|:-:|:-:|
|$\operatorname{Subtask}1$|$10$|$\le 20$|无|
|$\operatorname{Subtask}2$|$30$|$\le 100$|无|
|$\operatorname{Subtask}3$|$10$|无特殊限制|$ab=0$|
|$\operatorname{Subtask}4$|$50$|无特殊限制|无|

### 样例解释

一种方法是选出 $x+2y+3=0$ 和 $4x+5y+6=0$ 两条线。

可以证明没有更优的方案。

## 样例 #1

### 输入

```
3
1 2 3
4 5 6
7 8 10```

### 输出

```
2
```

# 题解

## 作者：Origin0107 (赞：9)

update on 11.12:将 double 换为 long double 减小精度造成的误差，感谢 @[yzy1](https://www.luogu.com.cn/user/207996) 指出错误。

# Problem

给定 $n$ 条直线，选取一些直线，覆盖所有点，并输出最小值。

# Solution

1. 易证 $n$ 条直线两两相交时，需要 $n-1$ 条直线去覆盖。
1. 当有 $i$ 条直线相互平行时，这 $i$ 条直线可以视作 $1$ 条直线

记 $x$ 为斜率相等直线数（即同一条直线的平行直线数）的最大值，答案为 $n-x$

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

map<long double,int> m;
long double a,b,c;
int x,n;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b>>c;
		m[b/a]++;
		x=max(x,m[b/a]);
	}
	cout<<n-x<<endl;
	return 0;
}
```

---

## 作者：银杉水杉秃杉 (赞：6)

这道题跟平行线有关，将平行的直线划为一组进行讨论，相当于把平行线合并成一条直线。

合并后所有直线互不平行，任意去掉一组平行线也能满组覆盖到所有交点。要使得剩下的直线数量最小，所以答案为 $ans=$ 直线总数量 $n$ $-$ 数量最多的一组平行线的数量。

用直线的斜率来区分不平行的直线，斜率相同的两条直线互为平行线。

注意：由于用斜率记录直线，double 的精度可能会不够，所以要用上 long double。

很多人用的是 map 来记录平行线。事实上也可以不用 map，将斜率进行排序，数一数重复的数量，找出最大值即可。

两种写法我都放出来给大家看看：

有 map 版：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, inf = 0x3f3f3f3f;
int n, m, mx;
map<long double, int> s;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        long double f = (a == 0) ? inf : (long double)b / a; //当a=0时，斜率为正无穷
        if (++s[f] > mx)
            mx = s[f];
    }
    printf("%d\n", n - mx);
    return 0;
}
```

无 map 版：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, inf = 0x3f3f3f3f;
int n, m, mx, s[N];
long double f[N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        f[i] = (a == 0) ? inf : (long double)b / a; //当a=0时，斜率为无穷
    }
    sort(f + 1, f + n + 1);
    s[++m] = 1;
    for (int i = 2; i <= n; i++) //数重复的
        if (f[i] == f[i - 1])
            s[m]++;
        else
            s[++m] = 1;
    for (int i = 1; i <= m; i++) //找最大值
        if (s[i] > mx)
            mx = s[i];
    printf("%d\n", n - mx);
    return 0;
}
```

感谢 @y1z1 大佬提供的 hack 数据。（原先写的 double，后来改成 long double 了）

---

## 作者：Tzs_yousa (赞：5)

# 核心
合成线：即把相平行的线合成一条。

为什么可以这样，是因为如果这几条线平行，它们与另外一条线相交，实际上只需要一条线即可遍布他们的全部交点，就相当于两条不平行的直线相交。

那如果是这几条线平行，与另外两条平行的线相交是怎么回事呢，实际上只需要那两条平行的线就可以，另外的那组平行的合成一条，实际上我们要找的就是哪一组平行线个数最多，然后把它合成一条。
### AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
const int MAXN = 100001;
using namespace std;
int n, a[MAXN], b[MAXN], c[MAXN], vis[MAXN], sum, p, maxn;
int gcd(int x, int y)
{
	if(y == 0) return x;
	return gcd(y, x % y);
}//写了然而并没有甚么卵用的gcd,我为啥不用是因为我用了gcd然后T了 
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i] >> b[i] >> c[i];
	for (int i = 1; i <= n ; i++)
	{
		if(vis[i] == 1) continue;
		int sum = 0;//x = gcd(a[i], b[i]); 
		for (int j = i + 1; j <= n; j++)
		{
			if(vis[j] == 1) continue;
			//int y = gcd(a[j],b[j]);
			if(a[i] == 0 && a[j] == 0)
			{
				sum++;
				vis[j] = 1;
			}
			else if(double(b[i])/double(a[i]) == double(b[j])/double(a[j])) 
			{
				sum++;
				vis[j] = 1;
			}
		}
		p = p + sum + 1;
		maxn = max(sum + 1, maxn);//找出来最多的那一条 
	}
	cout << p - maxn; 
	return 0;
}
```
完结撒花！

---

## 作者：Buried_Dream (赞：5)

## 题意：
给定 $n$ 个一次函数，选出最少的一次函数去覆盖所有点。

## 思路：

用一个结构体来存这个函数的信息，存 $a, b,c,k$,最后的 $k$ 是一次函数的斜率。
```cpp
struct node{
	int a, b, c;
	double k;
}P[maxn << 1];
```
统计斜率的目的就是为了找出斜率出现次数最多的一条直线，用所有的边数 $n$ 去减去斜率出现次数最多的一条边，因为斜率出现次数最多的一条边会重复经过最多的点，所以这样是最优的。

这样做完交上回发现只有90分，第三个subtask会被卡。

数据范围显示是 $a,b=0$ 也就是$a 和 b$ 至少有一个为零，因为题目中说道 $a，b$ 不会同时为 $0$, 所以说只要统计 $0$ 出现的次数就可以了。

如果出现的次数比边的数量多，就直接输出边减去其中的最大值。

## AC code：


```cpp

#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<queue>
#include<stack>
#include<cmath>
#include<cstring>
#define LL long long
#define il inline
#define re register
#define inf 0x3f3f3f3f
#define FJH 1314
using namespace std;
const int maxn = 5e6 + FJH;
const int MAXN = 2e3 + 32;
inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-'){w = -1;}ch = getchar();}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s * w;}
il void print(int x){
	if(x < 0) putchar( '-' ),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
struct node{
	int a, b, c;
	double k;
}P[maxn << 1];
int falg_1 = 0, falg_2 = 0;
bool cmp(node a, node b) {return a.k < b.k;}
int main(){
	long long n = read();
	for(int i = 1 ; i <= n; i++) {
		P[i].a = read(), P[i].b = read(), P[i].c = read();
		if(P[i].a != 0 && P[i].b != 0) {
		P[i].k = double(P[i].a ) * -1.0 / double(P[i].b);
		}
		if(P[i].a == 0) falg_1++;
		if(P[i].b == 0) falg_2++;
	}
	int ans_2 = max(falg_1, falg_2);
	if(falg_1 + falg_2 >= n) {
		cout << n - ans_2;
		return 0;
	}
	sort(P + 1, P + n + 1, cmp);
	long long ans = 0;
	long long js = 1;
	for(int i = 2; i <= n; i++) {
		if(P[i].k == P[i - 1].k) js++;
		else ans = max(ans, js), js = 1;
		}
	ans = max(ans , js);
	cout << n - ans;
	return 0;
}

```


---

## 作者：VinstaG173 (赞：5)

由于良心出题人给的条件，我们有一些结论。

显然若两条不平行直线均未选，则它们的交点未被覆盖。故未选的所有直线互相平行。

显然与某直线 $l$ 平行的所有直线（包括 $l$）均未选时所有交点均被覆盖。

故我们用除去最大公约数的方法求出一组平行线条数最大值，即为可以不选的直线数最大值，进而求出选择的最小可能条数。

Code:
```cpp
#include<map>
#include<cstdio>
#define rg register
using std::map;
using std::pair;
using std::make_pair;
inline int GCD(int a,int b)
{
	while(b^=a^=b^=a%=b);return a;
}
int n,a,b,c,d,mx;
map<pair<int,int>,int>ap;
int main()
{
	n=read();
	for(rg int i=0;i<n;++i)
	{
		a=read(),b=read(),c=read(),d=(a&&b)?GCD(a,b):a+b;
		if((++ap[make_pair(a/d,b/d)])>mx)mx=ap[make_pair(a/d,b/d)];
	}
	printf("%d\n",n-mx);
	return 0;
}
```

---

## 作者：断清秋 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P7918)

赛时第一次没过 Div2 B 祭……被这题给诈骗了/fn

考虑两两直线均不平行的情况，显然答案是 $n-1$。

考虑有平行的情况，发现选择的直线必然都是两两不平行的。

所以统计一下每条直线的斜率，出现次数最多的就是最多的一组平行线，用 $n$ 减去这个数目即可。

---

## 作者：FuriousC (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P7918)

这里给出一种 $O(n^2)$ 卡过的做法（

思路：

![](https://cdn.luogu.com.cn/upload/image_hosting/me39bjeq.png)

像上图这两条平行的线，只需要取一条绿色的线就可以覆盖所有交点，换句话说就是可以不用取这两条平行的线。

如果没有互相平行的线答案就是 $n-1$；有平行的线再减掉平行的线的数量即可。

若 $a_i/\gcd(a_i,b_i)=a_j/\gcd(a_j,b_j)$ 且 $b_i/\gcd(a_i,b_i)=b_j/\gcd(a_j,b_j)$，那么两条线平行。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct lines{
	int a,b,c;
}l[100005];
bool vis[100005];
int main(){
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&l[i].a,&l[i].b,&l[i].c);
		int gcd1=__gcd(l[i].a,l[i].b);
		l[i].a=l[i].a/gcd1;l[i].b=l[i].b/gcd1;//先预处理好
	}
	for(int i=1;i<=n;i++){
		int tmp=1;
		if(vis[i]){
			continue;
		}
		for(int j=i+1;j<=n;j++){
			if(vis[j]){
				continue;
			}
			if(l[i].a==l[j].a&&l[i].b==l[j].b&&i!=j){//判断平行
				tmp++;
				vis[j]=1;
			}
		}
		ans=max(ans,tmp);
	}
	printf("%d",n-ans);
	return 0;
}
```


---

## 作者：Iam1789 (赞：4)

首先可以看到，`任意三条直线不交于一点且没有两条直线重合`，说明对于任意一个交点它有且仅有两条直线经过。

先考虑没有直线平行的情况。在没有直线平行的情况下，每条直线两两都有一个交点。假如你删了两条直线，则这两条直线唯一的交点是没有直线经过的，不合法。而如果你只删一条直线，则这条直线与其它直线的交点一定在其它直线上，合法。所以你最多只能删一条直线，答案是 $n-1$。

再考虑有平行的直线。对于一对平行的直线，如果你要删其中一条直线，另一条直线也是可以删去的，因为这两条直线之间并没有交点。

接下来就好办了。找出最大的一个平行直线集 $A$，删去里面的直线，答案即为 $n-\text{card}(A)$。

对于判断直线平行，初中数学告诉我们，直线 $a//b$ 当且仅当 $a$ 与 $b$ 的斜率相等。于是我们按照斜率排序，统计斜率相同直线数的最大值就可以了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
struct dian{
	int x,y;
}a[100007];
inline int read()
{
	int s=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*f;
}
int fad;
int gcd(int x,int y)
{
	if(!y)
	return x;
	return gcd(y,x%y);
}
bool cmp2(dian x,dian y)
{
	if(x.x==y.x)
	return x.y<y.y;
	return x.x<y.x;
}
long long ans=0;
int main()
{
	n=read();
	int Gcd;
	for(int i=1;i<=n;++i)
	a[i].x=read(),a[i].y=read(),Gcd=gcd(a[i].x,a[i].y),a[i].x/=Gcd,a[i].y/=Gcd,fad=read();
	sort(a+1,a+n+1,cmp2);
	int anss=0;
	int jl=1;
	for(int i=2;i<=n;++i)
	{
		if(a[i].x!=a[i-1].x||a[i].y!=a[i-1].y)
		{
			anss=max(anss,i-jl);
			jl=i;
		}
	}
	anss=max(anss,n+1-jl);
	printf("%lld",n-anss);
	return 0;
}
```


---

## 作者：A_Đark_Horcrux (赞：3)

更新于 2021 年 11 月 14 日：增加了正确的代码。

对于 Subtask 3，观察发现只要输出水平直线和竖直直线中较少的那一组即可。这启示我们从平行线的角度分析问题：

我们把倾斜角相同的直线都归为一组，也就是说每一组里所有的直线互相平行。（如果某一条直线没有与之倾斜角相同的直线则单独记为一组）

考虑如果要取到所有交点，可以对于某一组平行线，选出这组线以外的直线。因为平行线间没有交点，所以这种选法已经覆盖了所有的交点，不需要在这一组平行线内选。

因此分组，记录平行线数量最大的那一组，选剩下的即可。

但是有两种比较特殊的情况：

$1.\gcd(a,b)\neq1$

$2.b=0$

对于情况一可以约分，也可以像我这样屑一个 double 关键字的 map：

```cpp
map<double,int> m;
m[(double)a[i]/b[i]]++;
```

__由于原数据太水。double 做法没有被卡精度。__

对于情况二特别记录即可。

这是现场的 __错误的__ 屑代码，它非常的屑，很容易看出问题：

```cpp
#include<cstdio>
#include<map> 
using namespace std;
int read()
{
	int s=0,b=1; char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') b=-1; c=getchar();}
	while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
	return s*b;
}
map<double,int> m;
int n,maxx,s,t,a[100010],b[100010],c[100010];
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),b[i]=read(),c[i]=read(),a[i]&&b[i]?m[(double)a[i]/b[i]]++:(!a[i]?s++:t++);//a,b都不为0，则记录水平或竖直
	for(int i=1;i<=n;i++) if(a[i]&&b[i]) maxx=max(maxx,m[(double)a[i]/b[i]]);//找最大的平行线组
	printf("%d\n",s+t==n?min(s,t):n-maxx);//判断输出
	return 0;
 } 
```

是的，它记录了 $b=0$ 的直线数，但没有单独拿出来判断，这是我拿了 90 分后看到了 Subtask 3 写的特判。说明一下这道题的数据很水 qaq

附一组简单的 hack

```
4
1 0 1
1 0 2
1 0 3
1 1 1
```

应输出：```1```

---

正确的代码应使用约分的方法，如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<map> 
using namespace std;
int read()
{
	int s=0,b=1; char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') b=-1; c=getchar();}
	while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
	return s*b;
}
map<pair<int,int>,int> m;//索引改为分子和分母！
pair<int,int> f(int x,int y) {return make_pair(x/__gcd(x,y),y/(__gcd(x,y)));} //约分
int n,maxx,s,t,a[100010],b[100010],c[100010];
int main()
{
	n=read();
	for(int i=1;i<=n;i++)//以下操作相同。
		a[i]=read(),b[i]=read(),c[i]=read(),a[i]&&b[i]?m[f(a[i],b[i])]++:(!a[i]?s++:t++);
	for(int i=1;i<=n;i++) if(a[i]&&b[i]) maxx=max(maxx,m[f(a[i],b[i])]);
	printf("%d\n",s+t==n?min(s,t):n-maxx);
	return 0;
 } 
```


---

## 作者：言琢დ (赞：1)

赛后来水一波题解。

考虑相同斜率的直线可以放在一起考虑，假设用来表示斜率的不可重集合是 $S$。

那么对于一个斜率 $k$，除它之外所有的斜率 $k'\in S$ 可以用来“删除”掉这个斜率 $k$ 对应的所有直线。

考虑要保留的直线个数最小，也就是删除的直线个数最大，对于某一个斜率 $k$，如果有一个直线被删除，就意味着其他直线也可以被删除。

而不同斜率的直线同时删除会导致它们俩的交点覆盖不到，所以这样做是最优的。

代码实现：

```cpp
#include<map>
#include<cstdio>
#define int long long
int init(){
	char c = getchar();
	int x = 0, f = 1;
	for (; c < '0' || c > '9'; c = getchar())
		if (c == '-') f = -1;
	for (; c >= '0' && c <= '9'; c = getchar())
		x = (x << 1) + (x << 3) + (c ^ 48);
	return x * f;
}
void print(int x){
	if (x < 0) x = -x, putchar('-');
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
int gcd(int x, int y){
	return y ? gcd(y, x % y) : x;
}
int ab(int x){
	return x < 0 ? -x : x;
}
std::map<std::pair<int, int>, int>map;
int ans;
int mx(int x, int y){
	return x > y ? x : y;
}
void insert(int x, int y){ // 插入一个斜率，并统计该斜率出现次数
	std::pair<int, int> pair = std::make_pair(x, y);
	ans = mx(ans, ++map[pair]);
}
signed main(){
	int n = init();
	for (int i = 1; i <= n; ++i) {
		int a = init(), b = init(), c = init(); // c 的值不影响斜率
		int g = gcd(ab(a), ab(b)); // 不保证 gcd 为 1，就要约分
		a /= g, b /= g;
		if (a < 0)
			insert(a, -b);
		else
			insert(-a, b); // 钦定斜率的分子为正，这样不会出现 -1 / 2 和 1 / -2 被看成两种不同斜率的情况
	}
	print(n - ans), putchar('\n'); // 简单容斥
}
```

---

## 作者：int08 (赞：1)

# 前言
在想到了解法之后，我回来看了看题目中的这句话：

注意：输入数据不保证 $\gcd(a,b)=1$。

然后有了一句劝世良言：

**忽略它！**
# Solution
## 题意理解
我们可以把题目理解为：每选出一条直线，就会将这条直线上的所有交点都去掉，直到将交点数变为 $0$，求出最小要选多少条直线。

但是我们发现，把一条直线上的所有交点都去掉，其实也就相当于去掉了这条直线。

因为题目中说了没有三线共点和两线重合，那么我们就又可以把题目转化为：

在有 $n$ 条直线的平面直角坐标系中，选出最少的直线，使得剩下的直线没有产生交点。

没有产生交点？**那不就是平行线吗！**

于是原来的问题就有了答案：**保留包含最多直线的一组（可能不止两条）平行线，这样就可以在去掉最少直线的情况下，使剩下的部分没有交点。**
## 代码实现
前置知识：**如果两条直线平行，它们的斜率相等。**

于是我们用一个浮点数组来记录每组平行线的斜率，再用另一个整型数组来计算每组平行线的直线数量。

特殊处理： $y$ 可能等于 $0$。此时将斜率记录为 $1000000001$。

在处理完了所有直线之后，查找出所含直线最多的那组平行线就行了。
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,a,b,c,ll[100003],j,g,k,ans=0;double l,p[100003];
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		if(b) l=-double(a)/double(b);
		else l=1000000001;
		k++;p[k]=l;ll[k]=1;
		for(j=1;j<k;j++)
		{
			if(p[j]==l)
			{
				k--;
				ll[j]++;
				break;
			}
		}
	}
	for(j=1;j<=k;j++)
	{
		if(ll[j]>ans) ans=ll[j];
	}
	cout<<n-ans;
	return 0;
} 
```

---

## 作者：orz_z (赞：0)

### 题目大意

给定 $n$ 条解析式为 $ax+by+c=0$ 的直线，选出最少的直线去覆盖所有交点。

### 解题思路

显然，没有删掉的直线一定是互相平行的，否则一定有至少一个交点没有被删掉。

所以其实就是要选出最多的直线使它们两两平行。

对于每一条直线暴力找出有多少条直线与它平行，取最大值即可。

用 `unordered_map` 维护，时间复杂度 $\mathcal O(n \log n)$。

### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

int n;

int a[100007], b[100007], c;

map<pair<int, int>, int> mp;

int ans;

int A, B;

signed main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read(), b[i] = read(), c = read();
        mp[make_pair(a[i], b[i])]++;
        if (a[i] == 0)
            A++;
        if (b[i] == 0)
            B++;
    }
    if (A + B == n)
    {
        cout << min(A, B) << "\n";
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        ans = max(ans, mp[make_pair(a[i], b[i])]);
    cout << n - ans << "\n";
    return 0;
}
```

---

