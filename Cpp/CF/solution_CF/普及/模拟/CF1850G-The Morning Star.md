# The Morning Star

## 题目描述

### 题意简述
本题有多组数据。

给定 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，$y_i$。

现需要将星星和指南针放在任意两个点上，使得星星在指南针的正北、正东、正西、正南、正东南、正东北、正西南或正西北方向，求一共几种放法。（如果对此不太理解结合样例解释）

## 说明/提示

$2\leq n \leq 2 \cdot 10^5$

$-10^9\leq x_i,y_i \leq 10^9$
在第一组数据中：

指南针在 $(0,0)$，星星在 $(-1,-1)$，在指南针的正西南方向。

指南针在 $(0,0)$，星星在 $(1,1)$，在指南针的正东北方向。

指南针在 $(-1,-1)$，星星在 $(0,0)$，在指南针的正东北方向。

指南针在$(-1,-1)$，星星在$(1,1)$，在指南针的正东北方向。

指南针在$(1,1)$，星星在$(0,0)$，在指南针的正西南方向。

指南针在$(1,1)$，星星在$(-1,-1)$，在指南针的正西南方向。

所以答案为6。

在第二组数据中：
 
指南针在$(6,9)$，星星在$(10,13)$，在指南针的正东北方向。

指南针在$(10,13)$，星星在$(6,9)$，在指南针的正西南方向。

所以答案是 2。

## 样例 #1

### 输入

```
5
3
0 0
-1 -1
1 1
4
4 5
5 7
6 9
10 13
3
-1000000000 1000000000
0 0
1000000000 -1000000000
5
0 0
2 2
-1 5
-1 10
2 11
3
0 0
-1 2
1 -2```

### 输出

```
6
2
6
8
0```

# 题解

## 作者：lwx20211103 (赞：5)

## 题目翻译

![](https://espresso.codeforces.com/d4bc950948a1049d2c81071966d4259748cb892a.png)

这是一个指南针，给你 $n$ 个点，每次可以放两个点，一个在中心，一个在八个方向的任意一个方向。求有多少种放置方法。

## 题目分析

首先，我们注意到：每当有两个点满足条件，那么答案就会加 $2$。如果有 $x$ 个点互相满足条件，那么方案数，就是 $x$ 排 $2$。即:

$$\frac{x!}{(x - 2)!}$$

这是代码：

```cpp
ll pailie(int n, int m)
{
	ll ans = 1;
	for (int i = n - m + 1; i <= n; i++)
		ans *= i;
	return ans;
}
```

我们下一步，怎么求能满足的点呢。

对于上下方向只要判断 $x$ 坐标是否相同。

对于左右方向只要判断 $y$ 坐标是否相同。

对于剩下四个，我们可以把问题转化成判断两个点之间的直线的**斜率**是否是 $\pm 1$ 即可。运用斜率公式：

$$k = \frac{y1 - y2}{x1-x2}$$

当然，我们可以进一步转化。如果 $k = 1$，那么式子化简为 $x1 - y1 = x2 - y2$，只要判断这两个数的差是否相等。如果 $k = -1$， 那么式子又可以化简为为 $x1 + x2 = y1 + y2$，只要判断两个数的和是否相等。

我们只要开四个映射表，分别映射 $x$ 坐标相等的个数，$y$ 坐标相等的个数，和相等的个数，差相相等的个数，然后分别把这几个映射表每个的答案都去计算它们排列 $2$ 的值，累加起来就是结果。

时间复杂度 $\Theta(n)$，足够通过此题，代码简短明了，一道难度 1500 的题目就被我们解决了。

## 代码区

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll pailie(int n, int m) n排m的代码
{
	ll ans = 1;
	for (int i = n - m + 1; i <= n; i++)
		ans *= i;
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		ll ans = 0;//注意long long
		cin >> n;
		map<int, int> mp, mp2, mp3, mp4;
		for (int i = 1; i <= n; i++)
		{
			int x, y;
			cin >> x >> y;
			mp3[x]++;
			mp4[y]++;
			mp[x + y]++;
			mp2[x - y]++;//如题解所示
		}
		for (auto &&i : mp) if (i.second >= 2) ans += pailie(i.second, 2);
		for (auto &&i : mp2) if (i.second >= 2) ans += pailie(i.second, 2);
		for (auto &&i : mp3) if (i.second >= 2) ans += pailie(i.second, 2);
		for (auto &&i : mp4) if (i.second >= 2) ans += pailie(i.second, 2);
		cout << ans << "\n";//完结撒花
	}	
	return 0;
}

```



---

## 作者：_fairytale_ (赞：5)

我们考虑对于一个指南针，其他的哪些点有贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/aj5duyji.png)

显然，只有当其他点在直线 $1-4$ 时，才会对答案有贡献。

因此，我们分析一下这些直线上点的特点（记指南针坐标为 $(x_0,y_0)$，直线 $i$ 上的点坐标为 $(x_i,y_i)$）。

- 直线 $1$ ：$x_1=x_0$

- 直线 $2$ ：$x_2-x_0=y_2-y_0$，即 $x_0-y_0=x_2-y_2$

- 直线 $3$ ：$y_3=y_0$

- 直线 $4$ ：$x_4-x_0=y_0-y_4$，即 $x_0+y_0=x_4+y_4$

因此，我们只需要开 $4$ 个 map 维护这些点的 $x,x-y,y,x+y$ 的出现次数即可。

```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
#define maxn 200010
using namespace std;
int T;
int n,m;
int x[maxn],y[maxn];
ll ans;
map<int,int>mp1,mp2,mp3,mp4;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
    cin>>T;
    while(T--){
    	mp1.clear(),mp2.clear(),mp3.clear(),mp4.clear();
    	cin>>n;
    	ans=0;
		for(re int i=1;i<=n;++i){
			cin>>x[i]>>y[i];
			mp1[x[i]]++;
			mp2[x[i]-y[i]]++;
			mp3[y[i]]++;
			mp4[x[i]+y[i]]++;
		}
		for(re int i=1;i<=n;++i){
			ans+=mp1[x[i]]+mp2[x[i]-y[i]]+mp3[y[i]]+mp4[x[i]+y[i]]-4;//去掉自己的贡献 
		}
		cout<<ans<<'\n';
	}
	return 0;
}


```

---

## 作者：_sunkuangzheng_ (赞：3)

**【题目大意】**

平面上有 $n$ 个互不相同的点，问至少满足下述条件之一的**有序**点对 $(i,j)$ 个数：

1. $|x_i - x_j| \times |y_i-y_j| = 0$，即两点横纵坐标任一相等。

1. 将坐标轴旋转 $45^\circ$ 后满足条件 $1$。

$1 \le n \le 2 \times 10^5,|x_i|,|y_i|\le 10^9$。

**【题目分析】**

显然满足条件 $1$ 的点对数量计数是简单的，我们只需要分别给横、纵坐标排序，统计连续的相等的坐标段，根据组合意义求解即可。

考虑条件 $2$ 的处理。我们发现点 $(x_i,y_i)$ 在坐标轴旋转 $45^\circ$ 后变为 $(x_i+y_i,x_i-y_i)$。处理方式和条件 $1$ 完全相同，根据组合意义求解。

具体的，设连续相等的值有 $x$ 个，它们对答案的贡献是 $2\dbinom{x}{2} = x(x-1)$。

**【代码】**

代码略长，但四段基本相似，逻辑非常清晰。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
struct p{int x,y;}a[500005];
bool cmp1(p a,p b){return (a.x - a.y) < (b.x - b.y);}
bool cmp4(p a,p b){return (a.x + a.y) < (b.x + b.y);}
bool cmp2(p a,p b){return a.x < b.x;}
bool cmp3(p a,p b){return a.y < b.y;}
signed main(){
    cin >> t;
    while(t --){
        cin >> n;int ans = 0,cnt = 1;
        for(int i = 1;i <= n;i ++) cin >> a[i].x >> a[i].y;
        sort(a+1,a+n+1,cmp1);
        for(int i = 2;i <= n;i ++){
            if((a[i].x - a[i].y) == (a[i-1].x - a[i-1].y)) cnt ++;
            else ans += cnt * (cnt-1),cnt = 1;
        }
        ans += cnt * (cnt - 1),cnt = 1;
        sort(a+1,a+n+1,cmp2);
        for(int i = 2;i <= n;i ++){
            if(a[i].x == a[i-1].x) cnt ++;
            else ans += cnt * (cnt-1),cnt = 1;
        }
        ans += cnt * (cnt - 1),cnt = 1;
        sort(a+1,a+n+1,cmp3);
        for(int i = 2;i <= n;i ++){
            if(a[i].y == a[i-1].y) cnt ++;
            else ans += cnt * (cnt-1),cnt = 1;
        }
        ans += cnt * (cnt - 1),cnt = 1;
        sort(a+1,a+n+1,cmp4);
        for(int i = 2;i <= n;i ++){
            if((a[i].x + a[i].y) == (a[i-1].x + a[i-1].y)) cnt ++;
            else ans += cnt * (cnt-1),cnt = 1;
        }
        ans += cnt * (cnt - 1),cnt = 1;
        cout << ans << "\n";
    }
}
```

---

## 作者：cjh20090318 (赞：3)

## 题意

给你 $n$ 个点的坐标，你需要找出有多少组不重合的点满足一个点在另一个点的正北、正南、正东、正西、西北、东北、西南、东南方向。

## 分析

只需要记录每一行、每一列、每一条斜线上有多少个点即可。

设当前行、列、斜线上有 $x$ 个点，那么答案就为 $x(x-1)$。

问题在于如何记录，对于行列，我使用了 `std::map`，斜线就可以用一个 `std::pair<int,int>` 记录函数解析式。

时间复杂度 $O(n \log n)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<map>
#include<utility>
typedef long long LL;
typedef std::pair<int,int> PII;
int n;
std::map<int,int> H,L;
std::map<PII,int> M;
void solve(){
	scanf("%d",&n);
	H.clear(),L.clear();
	M.clear();
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&x,&y);
		++H[x],++L[y];//记录行、列。
		++M[{1,-x+y}],++M[{-1,x+y}];//上升的函数（k=1）和下降的函数（k=-1）。
	}
	LL ans=0;
	for(PII x:H) ans+=(LL)x.second*(x.second-1);//依次统计答案。
	for(PII x:L) ans+=(LL)x.second*(x.second-1);
	for(std::pair<PII,int> x:M) ans+=(LL)x.second*(x.second-1);
	printf("%lld\n",ans);
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：Light_az (赞：1)

显然四种合法情况的特点如下：

- 横坐标相同。

- 竖坐标相同。

- 横竖坐标差值相同。

- 横竖坐标和值相同。

对于后两种情况是因为：

- 在一条左低右高的斜线上时，点的横纵坐标差值一定相同。

- 在一条左高右低的斜线上时，点的横纵坐标和值一定相同。

因此先使用映射法将每个点坐标对应四种合法情况的值存入容器，然后考虑方案数量。

将问题转化为：现在有一条直线，线上有 $n $ 个点，选择两个点作为一组，考虑顺序，问有多少种方案。

显然首先枚举 $n$ 个点，剩下 $n-1$ 种选择，因此方案数为 $n \times (n-1)$。

那么最后将每条直线和斜线的点的数量枚举，再加上答案贡献即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10;
ll n,m,k,x[N],y[N],u,v,w,cnt,ans,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
map<ll,ll> a1,a2,a3,a4;
int main(){
	cin>>T;
	while(T--){
		a1.clear();//多组数据清空
		a2.clear();
		a3.clear();
		a4.clear();
		ans=0;
		cin>>n;
		F(i,1,n){
			cin>>x[i]>>y[i];
			a1[x[i]]++;//将四种合法情况的值放入容器
			a2[y[i]]++;
			a3[x[i]-y[i]]++;
			a4[x[i]+y[i]]++;
		}
		for(auto it:a1) ans+=it.second*(it.second-1);//迭代器枚举每条直线上的点的数量，并加上答案贡献
		for(auto it:a2) ans+=it.second*(it.second-1);
		for(auto it:a3) ans+=it.second*(it.second-1);
		for(auto it:a4) ans+=it.second*(it.second-1);
		cout<<ans<<"\n";
	}

	return 0;
}


```


---

## 作者：Wf_yjqd (赞：1)

赛时怕清空 map 被卡，写了个毫无正确性的东西。。

Div.4 都没进前一千，我到底多菜啊。

------------

考虑用桶记录相同行，列和斜排的个数。

观察发现，可以用四个桶，分别为 $x$，$y$，$x-y$，$x+y$ 来表示南北方向，东西方向，东北—西南方向，西北—东南方向。

由于可能存在负数，考虑用 map 维护桶，同一个桶内任意俩个可以互相连接。

若桶内个数为 $x$，方案数为 $x\times(x-1)$，求和即可。

复杂度 $\operatorname{O}(n\times\log{n})$（$\log{n}$ 为 map 自带复杂度）。

注意 unordered_map 会被卡啊。

------------

丑陋的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
inline void write(register ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return ;
}
ll T,n,x,y,ans;
map<ll,ll> mp[4];
inline void Count(ll id){
    for(auto it:mp[id])
        ans+=it.second*(it.second-1);
    return ;
}
int main(){
    T=read();
    while(T--){
        n=read();
        for(ll i=1;i<=n;i++){
            x=read();
            y=read();
            mp[0][x]++;//南北方向
            mp[1][y]++;//东西方向
            mp[2][x+y]++;//东北—西南方向
            mp[3][x-y]++;//西北—东南方向
        }
        ans=0;
        for(int i=0;i<4;i++){
            Count(i);
            mp[i].clear();
        }
        write(ans);
        putchar('Sherry');
    }
    return 0;
}
```


---

## 作者：Night_sea_64 (赞：0)

显然，有下列四个结论：

- 当两个不同的点 $a,b$ 的 $x$ 坐标相同时，$b$ 在 $a$ 的西或东。
- 当两个不同的点 $a,b$ 的 $y$ 坐标相同时，$b$ 在 $a$ 的北或南。
- 当两个不同的点 $a,b$ 的 $x,y$ 坐标之和相同时，$b$ 在 $a$ 的西北或东南。
- 当两个不同的点 $a,b$ 的 $x,y$ 坐标之差相同时，$b$ 在 $a$ 的东北或西南。

于是很容易想出这样的思路：枚举每个点，查找有多少个其它的点跟它的 $x$ 坐标相同、$y$ 坐标相同、$x,y$ 坐标之和相同、$x,y$ 坐标之差相同。

为了做到快速，我们需要把所有点的这四个值都存下来并排序，每次查找时**二分查找**某个值出现的次数。用这个值减掉自己一个。

**温馨提示：十年 OI 一场空，不开 long long 见祖宗！**

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t,n;
int a[5][200010],b[5][200010];
//a[1] 记录 x 坐标
//a[2] 记录 y 坐标
//a[3] 记录 x+y
//a[4] 记录 x-y
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            int x,y;
            cin>>x>>y;
            a[1][i]=b[1][i]=x,a[2][i]=b[2][i]=y;
            a[3][i]=b[3][i]=x+y,a[4][i]=b[4][i]=x-y;
        }
        for(int i=1;i<=4;i++)sort(a[i]+1,a[i]+n+1);
        long long ans=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=4;j++)
                ans+=upper_bound(a[j]+1,a[j]+n+1,b[j][i])-lower_bound(a[j]+1,a[j]+n+1,b[j][i])-1;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Leaper_lyc (赞：0)

如果两个坐标合法，则一定满足下面三种情况中的一种：
1. 横坐标相同：即满足 $x[i] = x[j]$。
2. 纵坐标相同：即满足 $y[i] = y[j]$。
3. 在同一个对角线上 ：
即满足 $x[i]+y[i]=x[j]+y[j]$（可以认为是“\\”）或者 $x[i]-y[i]=x[j]-x[j]$（可以认为是“/”）。

那我们就对这几种情况分别开几个 map 来记录这每种情况的次数，最后累加起来就行，注意要开 `long long`。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

#define int long long
#define maxn 200005

int x[maxn], y[maxn];

map <int, int> d1, d2, d3, d4;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t, n, ans;
    cin >> t;
    while (t--) {
        cin >> n;
        ans = 0;
        d1.clear(); d2.clear();
        d3.clear(); d4.clear();
        for (int i = 1; i <= n; i++) {
            cin >> x[i] >> y[i];
            d1[x[i]]++;
            d2[y[i]]++;
            d3[x[i] + y[i]]++;
            d4[x[i] - y[i]]++;
        }
        for (int i = 1; i <= n; i++) {
            ans = ans + d1[x[i]] - 1;
            ans = ans + d2[y[i]] - 1;
            ans = ans + d3[x[i] + y[i]] - 1;
            ans = ans + d4[x[i] - y[i]] - 1;
        }
        cout << ans << '\n';
    }
}
```

---

## 作者：I_am_kunzi (赞：0)

# CF1850G 题解

### 题目翻译

有 $ t $ 组测试数据，每组给定一个 $ n$，代表有 $ n $ 个点，已知指南针只能指向八个方向（见原题插图），求这些点中可以一个点为指南针并且指向另一个点的点对数。

### 题目思路

其实题目中的八个方向可以大致归为四个方向（左 - 右，上 - 下，左上 - 右下，右上 - 左下）。这四个方向分别特征为：

+ 左 - 右：横坐标（$ x $）相等；

+ 上 - 下：纵坐标（$ y $）相等；

+ 左上 - 右下：横坐标 - 纵坐标（$ x - y $）相等；

+ 右上 - 左下：横坐标 + 纵坐标（$ x + y $）相等。

所以针对这四个数组排序，每次遍历一遍，假设有 $ k (k > 1) $ 个相等的数，则这一段可以选出的点对有 $ k \times (k - 1) $ 个。

### 题目代码

```cpp
long long h[200005] , w[200005]; // 左 - 右；上 - 下；
long long dx[200005] ,dy[200005]; // 左上 - 右下；右上 - 左下
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		// memset 可加可不加，但最好在不爆时限的情况下加上
		//memset(dy , 0 , sizeof(dy));
		//memset(dx , 0 , sizeof(dx));
		//memset(h , 0 , sizeof(h));
		//memset(w , 0 , sizeof(w));
		int n;
		cin >> n;
		for(int i = 1 ; i <= n ; i++) // 预处理出四个数组
		{
			cin >> h[i] >> w[i];
			dx[i] = h[i] - w[i];
			dy[i] = h[i] + w[i];
		}
		// 对这四个数组进行排序，为了方便后面遍历
		sort(h + 1 , h + n + 1);
		sort(w + 1 , w + n + 1);
		sort(dx + 1 , dx + n + 1);
		sort(dy + 1 , dy + n + 1);
		long long now = 2147483647 , combo = 0; // 给 now 初始一个该题数据不可能达到的数，防止出现事故；combo 为目前这个数的出现次数
		long long ans = 0; // 答案变量
		for(int i = 1 ; i <= n ; i++) // 左 - 右
		{
			if(h[i] != now)
			{
				now = h[i];
				if(combo > 1) // 因为只有一个点无法构成点对
				{
					ans += combo * (combo - 1);
				}
				combo = 1;
			}
			else
			{
				combo++;
			}
		}
		if(combo > 1) // 同上
		{
			ans += combo * (combo - 1);
		}
		now = 2147483647; // 初始化
		combo = 0;
		for(int i = 1 ; i <= n ; i++) // 上 - 下
		{
			if(w[i] != now)
			{
				now = w[i];
				if(combo > 1)
				{
					ans += combo * (combo - 1);
				}
				combo = 1;
			}
			else
			{
				combo++;
			}
		}
		if(combo > 1)
		{
			ans += combo * (combo - 1);
		}
		now = 2147483647;
		combo = 0;
		for(int i = 1 ; i <= n ; i++) // 同上 
		{
			if(dx[i] != now)
			{
				now = dx[i];
				if(combo > 1)
				{
					ans += combo * (combo - 1);
				}
				combo = 1;
			}
			else
			{
				combo++;
			}
		}
		if(combo > 1)
		{
			ans += combo * (combo - 1);
		}
		now = 2147483647;
		combo = 0;
		for(int i = 1 ; i <= n ; i++) // 同上
		{
			if(dy[i] != now)
			{
				now = dy[i];
				if(combo > 1)
				{
					ans += combo * (combo - 1);
				}
				combo = 1;
			}
			else
			{
				combo++;
			}
		}
		if(combo > 1)
		{
			ans += combo * (combo - 1);
		}
		cout << ans << endl;
	}
    return 0;
}
```


---

## 作者：aCssen (赞：0)

### Solution
我们可以枚举指南针的位置，然后分别计算与指南针同行，同列，同对角线的星星数量即可。

设指南针的坐标为 $(x,y)$。

对于同行，其坐标的形式是 $(x,k)$，开桶记录满足 $a=x$ 的数对 $(a,b)$ 即可。

对于同列，其坐标的形式是 $(k,y)$，开桶记录满足 $b=y$ 的数对 $(a,b)$ 即可。

对于同对角线，其坐标的形式有两种。

一种是 $(x+k,y+k)$，此时 $x+k-y+k$ 是定值 $x-y$，开桶记录满足 $a-b=x-y$ 的数对 $(a,b)$ 即可。

一种是 $(x+k,y-k)$，此时 $x+k+y-k$ 是定值 $x+y$，开桶记录满足 $a+b=x+y$ 的数对 $(a,b)$ 即可。

坐标很大且不能离散化，所以用 `map`。

时间复杂度 $\mathcal{O}(\sum n \log V)$，$V$ 是值域。

记得多测清空。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int x[maxn],y[maxn],n;
map<int,int>f1,f2,f3,f4;
void solve(){
	cin>>n;
	long long ans=0;
	f1.clear();
	f2.clear();
	f3.clear();
	f4.clear();
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		f1[x[i]]++;
		f2[y[i]]++;
		f3[x[i]-y[i]]++;
		f4[x[i]+y[i]]++;
	}
	for(int i=1;i<=n;i++){
		int posx=x[i],posy=y[i];
		ans+=(f1[posx]-1);
		ans+=(f2[posy]-1);
		ans+=(f3[posx-posy]-1);
		ans+=(f4[posx+posy]-1);
	}
	cout<<ans<<'\n';
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：sto_5k_orz (赞：0)

# G

考虑两个点的罗盘 $(x_1,y_1)$ 和 $(x_2,y_2)$ 不会报废，需要满足一下四个条件之一：

1. $x_1=x_2$

2. $y_1=y_2$

3. $x_1-y_1=x_2-y_2$

4. $x_1+y_1=x_2+y_2$

不难发现当 $(x_1,y_1)\not = (x_2,y_2)$ 时，下面四个条件至多满足一条。

所以维护下每个点的 $x,y,x-y,x+y$，然后存起来排序，双指针扫出重复的次数 $x$，答案即为 $\sum x(x-1)$。

复杂度瓶颈在于排序的 $\mathcal{O(n\log n)}$，可以通过。

本人赛时脑抽写了个 unordered_map，被卡 TLE 了，警钟敲烂。

---

## 作者：__Allen_123__ (赞：0)

### 题意简述

给定 $n$ 个点 $(x_i, y_i)$，请求出从中选出 $2$ 个点的方法数，使得这两个点在同一行，同一列或同一对角线上。注意如果选出的两个点相同但顺序不同，那么算不同的情况。

本题有多测，共 $t$ 组数据，题目保证 $1\le t \le 10^4, n\ge 2, \sum_{i=1}^{t} n_i\le 2\times 10^5, -10^9\le x_i, y_i\le 10^9$。

### 题目分析

前置知识：[排列组合](https://oi-wiki.org/math/combinatorics/combination/)。

我们很容易想到这样一种方法：用 $4$ 个数组分别标记在同一行，同一列和同一对角线上的点的数量（储存 $x_i, y_i, x_i+y_i, x_i-y_i$），因为只有这样才满足题目条件。

对于每一个相同的行，列或对角线，如果在这个对角线上的点的数量有 $x$ 个，那么我们可以在其中任意选取两个点进行排列，即此时它对答案的贡献为 $A_{x}^{2}=x(x-1)$。当 $x=1$ 时，无法选出两个点，此时答案仍然为 $x(x-1)=0$。最终把答案全部加起来即可。

思路很明确，但我们看到数据范围，$-10^9\le x_i, y_i\le 10^9$，直接用普通数组来储存显然不可行。所以我们应该使用 `map` 来储存同一行、列、对角线的数量，最后计算每种情况的答案，全部加起来就可以得出结果。

注意有多测，每次测试之后应清空所有 `map`，并且答案可能超出 `int` 范围。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
struct node{
	int x, y;
}a[MAXN];
int t, n;
map<int, int> mp1, mp2, mp3, mp4;
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1;i <= n;i++){
			scanf("%d%d", &a[i].x, &a[i].y);
			mp1[a[i].x]++;
			mp2[a[i].y]++;
			mp3[a[i].x + a[i].y]++;
			mp4[a[i].x - a[i].y]++; // 记录每行、列、对角线的点的数量
		}
		unsigned long long ans = 0;
		for(map<int, int>::iterator it = mp1.begin();it != mp1.end();it++){
			ans += 1LL * it->second * (it->second - 1);
		}
		for(map<int, int>::iterator it = mp2.begin();it != mp2.end();it++){
			ans += 1LL * it->second * (it->second - 1);
		}
		for(map<int, int>::iterator it = mp3.begin();it != mp3.end();it++){
			ans += 1LL * it->second * (it->second - 1);
		}
		for(map<int, int>::iterator it = mp4.begin();it != mp4.end();it++){
			ans += 1LL * it->second * (it->second - 1);
		} // 计算答案
		printf("%llu\n", ans);
		mp1.clear();
		mp2.clear();
		mp3.clear();
		mp4.clear(); // 清空 map
	}
	return 0;
}


```

---

## 作者：liangjindong0504 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1850G)
### 题目大意
有 $t$ 组数据。

在每组数据中，给出 $n$ 个点，
第 $i$ 个点的坐标为 $x_i,y_i$。要求选出两个点，使得：

一点在另一点的东、南、西、北或东南、东北、西南、西北方向。
### 题目分析
首先，不考虑如何实现，先来考虑思路。

由于题目中给出了 $n \leq 2 \cdot 10^5 $，暴力绝对超时（虽然我没试过），于是我们来找规律。

首先，东南西北这四个方向比较好实现。若一点在另一点的东、南、西、北，他们的横坐标或纵坐标必定相同。（这一点比较好想，读不懂可以自己画一下）

剩下四个方向就比较难想了（对我来说）。

东南和西北可以看作是相同的。因为若一点在另一点的正东南方向，则另一点就在这一点的正西北方向。同理，西南和东北也可以看作是相同的。

假设一点在 $(0,0)$。（比较好推）

若另一点在这一点的正东南或正西北方向，则另一点可以在 $(1,-1)$，$(-1,1)$，$(-2,2)$……

不难发现，**若一点在另一点的正东南或正西北方向，横坐标和纵坐标的和都一样。**

若另一点在这一点的正东北或正西南方向，则另一点可以在 $(1,1)$，$(-1,-1)$，$(2,2)$……

可以发现，**若一点在另一点的正东北或正西南方向，横坐标和纵坐标的差都一样。**
### 实现
已经知道怎么写的可跳过

有必要说一下：**有多组数据，不清零爆零。**

我们可以定义 $4$ 个 ```map``` 来存储横坐标、纵坐标、和、差的出现次数。

对于每一个出现次数大于等于 $2$ 的横坐标、纵坐标、和、差（若为 $1$ 则达不到两个点），设出现次数为 $n$，则可以给答案增加 $C_{n}^{2}$，意思就是在 $n$ 个点中任取两个不重复的点。不懂排列组合的戳[这里](https://baike.baidu.com/item/%E6%8E%92%E5%88%97%E7%BB%84%E5%90%88/706498)。
### 代码
最后，把代码奉上。

[代码](https://www.luogu.com.cn/paste/1e6xz4zp)

---

## 作者：CQ_Bob (赞：0)

## 分析

对于这道题，我们假设指南针在点 $(x,y)$，则其能匹配的点有：

1. $(x,y+k)$
2. $(x,y-k)$
3. $(x+k,y)$
4. $(x-k,y)$
5. $(x+k,y+k')$
6. $(x+k,y-k')$
7. $(x-k,y+k')$
8. $(x-k,y-k')$

其中 $k,k'$ 是两个正整数。

通过观察，不难发现，这些满足要求的点与 $(x,y)$ 都是有关联的，如下：

1. 当存在点 $(x',y')$，有 $x'=x$ 时，必有 $y'=y \pm k$。
2. 当存在点 $(x',y')$，有 $y'=y$ 时，必有 $x'=x \pm k$。
3. 当存在点 $(x',y')$，有 $x'-y'=x-y$ 时，必有 $x'=x \pm k,y'=y \pm k'$。
4. 当存在点 $(x',y')$，有 $x'+y'=x+y$ 时，必有 $x'=x \pm k,y'=y \pm k'$。

故我们可以开 $4$ 个 map 数组，分别储存对于每个点的每种情况所对应的个数，然后计算出答案。

注：由于这 $4$ 种情况对于每个点的 map 记录的数量都包含的 $(x,y)$ 本身，所以每次的每种情况都需要减一。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int t;
int n,k,a[N];
int x[N],y[N];
map<int,int> cnt1,cnt2,cnt3,cnt4;
void check(){
	cnt1.clear(),cnt2.clear(),cnt3.clear(),cnt4.clear();
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		cnt1[x[i]]++;
		cnt2[y[i]]++;
		cnt3[x[i]-y[i]]++;
		cnt4[x[i]+y[i]]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=cnt1[x[i]]-1;
		ans+=cnt2[y[i]]-1;
		ans+=cnt3[x[i]-y[i]]-1;
		ans+=cnt4[x[i]+y[i]]-1;	
	}
	cout<<ans<<"\n";
}
signed main(){
	cin>>t;
	while(t--){
		check();
	}
	return 0;
}
```


---

## 作者：zct_sky (赞：0)

### Description:
-----
给定 $n$ 个点，其中一个点为晨星，另一点为指南针。

指南针只能指向 $8$ 个方向（$N,NE,E,SE,S,SW,W,NW$），若晨星不在指南针的这 $8$ 个方向上，它就会裂开。

求共有多少种方案使得指南针不会裂开。

本题有多组数据。
### Solution:
-----
我们来分析一下指南针的 $8$ 个方向在坐标上分别代表什么：

- $N,S$：$x$ 坐标相同。

- $E,W$：$y$ 坐标相同。

- $NE,SW$：$x-y$ 相同。

- $NW,SE$：$x+y$ 相同。

根据这四个“相同”，我们可以用 `map`，或进行四次排序。

然后分别遍历 $x,y,x+y,x-y$ 的值，统计答案。

若有 $m$ 个点满足其中一个“相同”，那么它们对答案的贡献为 $A^m_2=m(m-1)$。

最后输出答案即可。

时间复杂度为 $\mathcal{O}(n \log n)$。
### Code 1(排序实现):
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
const int N=2e5+7;
ll n,ans;
#define PLL pair<ll,ll>
PLL a[N];
#define x first 
#define y second
ll t;
bool cmp1(PLL a,PLL b){
	return (a.x==b.x)?a.y<b.y:a.x<b.x;
}
bool cmp2(PLL a,PLL b){
	return (a.y==b.y)?a.x<b.x:a.y<b.y;
}
bool cmp3(PLL a,PLL b){
	return a.x+a.y<b.x+b.y;
}
bool cmp4(PLL a,PLL b){
	return a.x-a.y<b.x-b.y;
}
ll A2(ll a){
	return a*(a-1);
}
ll tmp,len;
int main(){
	t=read();
	while(t--){
		n=read();ans=0;
		for(int i=1;i<=n;i++){
			a[i].x=read();a[i].y=read();
		}
		sort(a+1,a+1+n,cmp1);
		tmp=a[1].x;len=1;
		for(int i=2;i<=n;i++){
			if(a[i].x==tmp){
				len++;
			}else{
				ans+=A2(len);
				len=1;
				tmp=a[i].x; 
			}
		}
		ans+=A2(len);
		sort(a+1,a+1+n,cmp2);
		tmp=a[1].y;len=1;
		for(int i=2;i<=n;i++){
			if(a[i].y==tmp){
				len++;
			}else{
				ans+=A2(len);
				len=1;
				tmp=a[i].y; 
			}
		}
		ans+=A2(len);
		sort(a+1,a+1+n,cmp3);
		tmp=a[1].x+a[1].y;len=1;
		for(int i=2;i<=n;i++){
			if(a[i].x+a[i].y==tmp){
				len++;
			}else{
				ans+=A2(len);
				len=1;
				tmp=a[i].x+a[i].y; 
			}
		}
		ans+=A2(len);
		sort(a+1,a+1+n,cmp4);
		tmp=a[1].x-a[1].y;len=1;
		for(int i=2;i<=n;i++){
			if(a[i].x-a[i].y==tmp){
				len++;
			}else{
				ans+=A2(len);
				len=1;
				tmp=a[i].x-a[i].y; 
			}
		}
		ans+=A2(len);
		printf("%lld\n",ans);
	}
	return 0;
}
```
### Code 2(map 实现):
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
const int N=2e5+7;
ll n,ans;
#define PLL pair<ll,ll>
PLL a[N];
#define x first 
#define y second
ll t;
map<ll,ll>x,y,x_add_y,x_sub_y;
ll A2(ll a){
	return a*(a-1);
}
ll tmp,len;
int main(){
	t=read();
	while(t--){
		n=read();
		ans=0;
	    x.clear();y.clear();x_add_y.clear();x_sub_y.clear();
		for(int i=1;i<=n;i++){
			a[i].x=read();a[i].y=read();
			x[a[i].x]++;y[a[i].y]++;
			x_add_y[a[i].x+a[i].y]++;
			x_sub_y[a[i].x-a[i].y]++;
		}
	    for(auto i:x){
	        ans+=A2(i.y);
	    }
	    for(auto i:y){
	        ans+=A2(i.y);
	    }
	    for(auto i:x_add_y){
	        ans+=A2(i.y);
	    }
	    for(auto i:x_sub_y){
	        ans+=A2(i.y);
	    }
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1850G)    
## 题意
一个指南针只可以指向正东南西北、东北、西北、东南、西南这八个方向。   
现在给定 $n$ 个点，第 $i$ 个点的坐标在 $(x_i,y_i)$，求有多少个二元组 $(i,j)$ 满足指南针在 $(x_i,y_i)$ 的位置并且指南针可以指向 $(x_j,y_j)$ 的位置。      
## 解法  
首先，正东南西北都是 $x$ 或 $y$ 不变，我们只需要开桶记录 $x$ 和 $y$ 即可。   
我们先观察西南和东北，记原来的坐标在 $(x,y)$，那么这两个方向上的点都可以表示成 $(x+w,y+w)$ 的形式。     
它们的差是相等的，所以我们需要再开桶记录 $x-y$。    
如果是东南和西北，那么这两个方向的点可以表示成 $(x+w,y-w)$ 的形式，它们的和是相等的，所以我们要开桶记录下 $x+y$。    
有了这些桶，我们最后扫一遍所有的坐标，每次把四个桶的相应个数相加，减掉本身 $4$ 个就是这一次的答案贡献。     
发现 $x_i$ 和 $y_i$ 范围比较大，所以我们使用 map 实现。     
注：不要使用 unordered_map，会被卡。      
[CODE](https://www.luogu.com.cn/paste/2tnhtstm)

---

## 作者：Dream__Sky (赞：0)

题意简述；

指南针直接指向晨星。它只能指向八个方向中的一个：四个基本方向（北、南、东、西）或某些组合（西北、东北、西南、东南）。否则，它就会坏掉。

平面上有 $n$ 个坐标为整数的不同点。你能用几种方法把指南针放在一个点上，而把晨星放在另一个点上，让指南针不断。

分析：

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kdzzdyri.png)

我们发现，北与南方向的点列数是相同的，西与东方向的点行数是相同的，这点比较显然。我们看西北与东南，发现行与列之差是相等的。再看东北与西南，发现列与行之差是相等的。

那我们就可以用四个桶保存下来，这四种情况各有几个点。

当出现了 $1$ 个，答案是 $0$；当出现了 $2$ 个，答案是 $2$；当出现了 $3$ 个，答案是 $6$；出现 $4$ 个，答案是 $12$。我们发现，当出现了 $n$ 个，答案就是 $n\times(n-1)$。还不懂就自己手推一下，找规律比较好懂。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long//一定要开longlong，赛时吃了2发罚时
using namespace std;
map<int,int> p1,p2,p3,p4;//四个桶
int T,n,a[200001],b[200001];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--)
	{
		cin>>n;
		p1.clear(),p2.clear(),p3.clear(),p4.clear();//多测清空
		for(int i=1;i<=n;i++)
		{
			cin>>a[i]>>b[i];
			p1[a[i]]++;
			p2[b[i]]++;
			p3[a[i]-b[i]]++;
			p4[a[i]+b[i]]++;
		}
		
		int sum=0;
		for(int i=1;i<=n;i++)
		{	
			sum+=(p1[a[i]]-1)*p1[a[i]];
			sum+=(p2[b[i]]-1)*p2[b[i]];
			sum+=(p3[a[i]-b[i]]-1)*p3[a[i]-b[i]];
			sum+=(p4[a[i]+b[i]]-1)*p4[a[i]+b[i]];
			
			p1[a[i]]=p2[b[i]]=p3[a[i]-b[i]]=p4[a[i]+b[i]]=0;
		}//计算答案
		cout<<sum<<"\n";
	}
	return 0;
}


```



---

