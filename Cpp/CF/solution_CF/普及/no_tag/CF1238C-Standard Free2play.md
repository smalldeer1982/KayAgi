# Standard Free2play

## 题目描述

您现在正在玩一个游戏，您初始在一个高度 $h$ 的悬崖

悬崖沿壁高度为 $1-h$ 的这些位置均有平台，平台有两种状态，被选中/不被选中，您可以认为只有被选中的平台才出现在这个悬崖上且你可以站在上面。

初始时有 $n$ 个平台为被选中，保证平台 $h$ 被选中，您每次可以进行一个操作，不妨假设您当前站在平台 $x$ 处（此时平台 $x$ 一定被选中），即让平台 $x$ 变成未被选中，而平台 $x - 1$ 变成相反的状态。

您非常的脆弱，所以不能跌落超过$2$的高度，比如您可以从高度为$3$的平台跌落到高度为$1$的平台，但不能从高度为$3$的平台跌落到地面$($高度：$0)$

现在您想要回到地面，即高度为$0$

您可以使用一种魔力水晶，即其可以将任意一个平台修改成指定的状态。

现在希望您求出回到地面最少需要使用多少颗魔力水晶？

## 样例 #1

### 输入

```
4
3 2
3 1
8 6
8 7 6 5 3 2
9 6
9 8 5 4 3 1
1 1
1
```

### 输出

```
0
1
2
0
```

# 题解

## 作者：jiayixuan1205 (赞：5)

# CF1238C Standard Free2play
## 算法
题目中求解使用最少的数量，故考虑贪心。
## 分析
题目中给出的是“向下掉落”，为方便考虑，我们可以将其等价逆向考虑为“从下向上蹦”。

首先，根据题意，我们有两种操作：
- **普通操作**，即将当前所在平台收回，同时使下一个平台变为相反状态。
- **特殊操作**，直接指定改变某平台的状态。

为使使用的水晶最少，容易想到使用水晶的时候只能是用于使未露出的平台露出以让其不被摔死。因此从下向上枚举初始露出的平台，若相邻两平台距离差值大于 $1$（用 $1$ 而不用 $2$ 是因为普通操作要改变与之相邻平台的状态），则需使用魔力水晶；反之普通操作跳过该平台即可。
## 实例代码
```cpp
#include<bits/stdc++.h>
#define N 200200

using namespace std;

int a[N],n,h,T;

int main()
{
	cin>>T;
	while(T--)
	{
		int ans=0;
		cin>>h>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		n++;
		a[n]=0;
		for(int i=2;i<=n;i++)
		{
			if(a[i]-a[i+1]>1) ans++;
			else i++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Soulist (赞：4)

考虑两个落差比较大的点，比如$100$到$5$

会发现$100$到$5$的情况等同于$6$到$5$的情况

而$100$是可以直接到$6$的，这个性质可以简单分类讨论一下得到

考虑一种依赖于值域的$dp$

考虑魔法水晶的使用对于答案的影响

分类讨论得到有一下用法：

在$x$时如果$x-1$被选中，那么可以修改$x-1$的状态，然后到达$x-1$

在$x$时如果$x-1$未被选中且$x-2$被选中，那么可以修改$x-1$的状态然后到达$x-2$，可以发现这一步时无用的，因为它等同于达到$x-1$后前往$x-2$

在$x$时如果$x-1$被选中且$x-2$被选中，则可以修改$x-2$后直接达到$x-2$，然而实际上这一步与修改$x-1$后前往$x-2$等效

所以可以发现魔法水晶修改的唯一用途是修改$x-1$的状态

所以就可以直接$dp$，根据当前位置$i$的状态和$i-1$的初始状态以及$i-2$的初始状态就可以转移了

然而这样复杂度是$O(h)$

但是一开始摆出来的性质告诉你相邻两点的$dp$没必要值域的去计算，可以直接将$100$当做$6$去做即可

于是复杂度$O(n)$

如果你写了这个$dp$就会发现只要贪心一下就行了$($大雾$...$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2e5 + 5 ; 
int n, H, a[N], dp[N] ; 
int solve() {
	int ans = 0, r = 1 ; 
	for( re int i = 2; i <= n; ++ i ) {
		if( a[i - 1] != a[i - 2] + 1 ) dp[i] = dp[i - 1] + 1 ;
		else dp[i] = dp[i - 2] ;  
	}
	return dp[n] ; 
}
signed main()
{
	int T = gi() ;  
	while( T-- ) {
		H = gi(), n = gi() ; 
		rep( i, 1, n ) a[n - i + 1] = gi() ; 
		printf("%d\n", solve() ) ;
	}
	return 0 ;
}
```

---

## 作者：Rex01 (赞：2)

## [CF1238C 题目传送门](https://www.luogu.com.cn/problem/CF1238C)

## 题目大意
有一个高度为 $h$ 的悬崖，悬崖沿壁高度从 $1$ 到 $h$，每一个整数高度的位置均有平台，每个平台都有两种状态，即被选中和不被选中，分别用 $1$ 和 $0$ 来标识，只有状态为 $1$ 的平台才能停留。初始时有 $n$ 个平台的状态为 $1$，它们的高度是给出的，保证高度为 $h$ 的平台是初始时是被选中。运动过程中，如果玩家当前站在高度为 $x$ 的平台上，此时平台 $x$ 必须是被选中的，此刻之后高度为 $x$ 的平台马上自动变成未被选中的状态，而高度为 $x − 1$ 的平台同时会变成与其原来相反的状态。玩家任何时候都不能下落超过 $2$ 的高度。为了回到高度为 $0$ 的地面上，玩家可以使用一种魔力水晶助力，一个魔力水晶可将任意一个平台修改成指定的状态，你的任务是确定回到地面最少需要使用魔力水晶的数量。

## 解决思路
因为要求最少，因此想到**贪心**。由题目大意可知一共有两种操作：
- 将第 $i$ 个平台收回，同时使第 $i + 1$ 个平台变为相反状态；
- 直接改变某平台的状态。

因为使用水晶只能让平台露出来保护自己，同时为了让最终结果最小，因此从下向上枚举初始露出的平台，若相邻两平台距离差值大于 $1$，则需使用魔力水晶；否则进行普通操作跳过该平台即可。

## 代码展示
```cpp
#include <iostream>
#include <algorithm>
//不用万能头，从我做起
using namespace std;

const int N = 2e5 + 200;
int q, h, n, p[N], ans;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);//减少输入速度
	cin >> q;
	while(q--)
	{
		ans = 0;
		cin >> h >> n;
		for(int i = 1; i <= n; i++)	
			cin >> p[i];
		p[n] = 0;
		for(int i = 2; i <= n + 1; i++)
			if(p[i] - p[i + 1] > 1) ans++;
			else i++;
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1238C)

## 思路
考虑当你在高度为 $x$ 的平台上，下面最近的一个选中的平台是 $y$（$x > y$）时能否不用魔力水晶到达平台 $y + 1$~~，归纳大法好啊~~：
* 当 $x = y + 1$ 时：已经完成，可以。
* 当 $x - 1$ 可以直接到达到达 $y + 1$ 且 $x - 1$ 未选中时：$x$ 会取消选中，$x - 1$ 会从未选中变为选中，转换为从 $x - 1$ 不用魔力水晶到达 $y + 1$，所以可以。

所以可能会坠落的只有从 $y + 1$ 到 $y$ 的那一步，如果平台 $y + 1$ 距离再下面的平台 $z$ 的距离 $y - z + 1 > 2$ 也就是 $y - z > 1$ 时我们就需要使用魔力水晶更改。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;

int t;
	int n, h;
		int p[2];

	bool flag;
	int ans;

void work_n (int i) {
	scanf("%i", &p[i & 1]);
	
	if (flag && i > 2 && p[!(i & 1)] - p[i & 1] > 1) {++ans;}
	else flag = !flag;
}
void work_t () {
	flag = true;
	ans = 0;

	scanf("%i%i", &h, &n);
	FOR (1, n, i) {work_n(i);}
	if (flag && p[n & 1] > 1) {++ans;}

	printf("%i\n", ans);
}
int main () {
	scanf("%i", &t);
	while (t--) {work_t();}
	return 0;
}
```

---

## 作者：longStone (赞：0)

# CF1238C Standard Free2play 题解

## 题意

要从 $h$ 高的悬崖上选择状态为 $1$ 的平台到达地面，一次最多坠落 $2$ 个高度。当你在第 $x$ 个平台上时，平台 $x$ 会收回去并让第 $x - 1$ 个平台改变状态。

同时可以用一个水晶更改一个位置的状态，求最少需要使用的水晶数量。

你只会落在离你最近的平台上。就是说如果你能落在第 $x - 1$ 个平台上，那么你就不能选择落在第 $x - 2$ 个平台上。 

## 观察

### 情况一：一长串状态为 $0$ 的平台

![](https://cdn.luogu.com.cn/upload/image_hosting/d6ec3qa7.png)

如图所示，这种情况下可以一直向下移动，不需要消耗任何水晶。

### 情况二：没有地方可以移动

![](https://cdn.luogu.com.cn/upload/image_hosting/cuwoy1vj.png)

如图所示，你不能降落到 $x - 1$ 或 $x - 2$ ，如果不使用水晶将会摔死。

同时，使用水晶后会按情况一的方式下降，下面的 $1$ 仍然会被改变为 $0$。

### 情况三：可以移动到 $x - 2$

如果可以移动到 $x - 2$，说明 $x - 1$ 不能被到达。$x - 1$ 和 $x - 2$ 这两个平台初始状态均为 $1$ 且距离为 $1$。

如果位置 $x - 1$ 不能被到达，那么对应的 $x - 2$  的状态也不会被改变。

## 思路

从第二个初始状态为一的平台开始查找，如果相邻的两个平台高度差大于 $1$ ，则使用一个水晶。如果正好为 $1$ ，那就按情况三跳过下一个平台即可。

## 代码

```c++
#include "bits/stdc++.h"
using namespace std;
int q, h, n, p[200005];
int main()
{
    cin >> q;
    while(q--)
    {
        cin >> h >> n;
        int ans = 0;
        p[n + 1] = 0;//从最后一个平台到地面
        for(int i = 1;i <= n;i++)	cin >> p[i];
        for(int i = 2;i <= n;i++)
        {
            if(p[i] - p[i + 1] > 1)	ans++;//p[i]不能到达
            else i++;
        }
        cout << ans << '\n';
    }
    return 0;
}

```

---

## 作者：Shunpower (赞：0)

简单题。

---------

考虑我们进行普通操作会发生什么。可以发现，我们完全可以直接干到目前位置下方一个被选中的平台上方（因为在此之上都是这层被选中下一层未被选中，操作一次就能掉到下一层），然后我们考虑怎么搞。

假设目前位置为 $x$，则现在我们下方 $x-1$ 处存在一个被选中的平台，我们考虑 $x-2$ 的情况。

如果 $x-2$ 有被选中平台的话，那就可以直接普通操作一次，然后掉到 $x-2$ 上不会被摔死，后面该咋搞咋搞就行了，这样不造成花费，显然是最优的。

如果 $x-2$ 上没有平台，那操作一次就必然会被摔死，并且这个摔死无法避免，所以考虑在 $x-2$ 上强行操作一次，搞一个平台出来，后面就和上一步一样了。

可以发现，对抗 $x-2$ 没有平台只有两种办法：一种是上面讲的方法，另一种就是想办法让人落到 $x-1$ 上。然而想让人自然落到 $x-1$ 上必须要通过强行操作一次来改变不强行操作落到 $x$ 上的事实，所以两种办法都是一样的。

然后模拟就行了。

```cpp
int h,n;
int p[N];
int pos;
void solve(){
    cin>>h>>n;
    fr1(i,1,n) cin>>p[i];
    p[n+1]=0;
    pos=h;
    int cnt=0;
    fr1(i,2,n){
        pos=p[i]+1;
        if(p[i+1]==p[i]-1){
            pos=p[i+1];
            i++;
            continue;
        }
        cnt++;
    }
    cout<<cnt<<'\n';
}
```

---

## 作者：Sandmonth (赞：0)

看到这么多人用贪心只有我用了dp见此发一篇题解，设$dp[i][0/1]$为到第i可移动第平台是否移出该平台，0表示不移除否则反之。dp转移大概就是判断上一个台阶为0 下一个台也为0的差值是否大于2具体实现可代码。
```
#define db long double
#define FOR(x,a,b) for(ll x=a;x<=b;x++)
#define _FOR(x,a,b) for(ll x=a;x>=b;x--)
#define RI(n) scanf("%lld",&n)
#define RLL(n) scanf("%lld",&n)
#define RLL2(a,b) scanf("%lld %lld",&a,&b)
#define RLL3(a,b,c) scanf("%lld %lld %lld",&a,&b,&c)
#define RLL4(a,b,c,d) scanf("%lld %lld %lld %lld",&a,&b,&c,&d)
#define RLF(n) scanf("%lf",&n)
#define RLF2(a,b) scanf("%lf %lf",&a,&b);
#define RLF3(a,b,c) scanf("%lf %lf %lf",&a,&b,&c);
#define RS(n) scanf("%s",n)
#define PLL(n) printf("%lld",n)
#define PLN(n) printf("%lld\n",n)
#define PLN2(a,b) printf("%lld %lld\n",a,b)
#define PLN3(a,b,c) printf("%lld %lld %lld\n",a,b,c)
#define MM(a,x) memset(a,x,sizeof(a));
#define DE(x) cout<<x<<endl;
#define ll long long
#define eps 1e-6
const long long inf=1e17;
const int N=2e5+10+10000;
const int M=1e9+10;
const ll mod=1e9+7;
using namespace std;
ll dp[N][5];
ll a[N];
int main(){
    ll t;
    RLL(t);
    while(t--){
        ll h,n;
        RLL2(h,n);
        FOR(i,1,n)RLL(a[i]);
        dp[1][1]=dp[1][0]=0;
        a[n+1]=0;
        FOR(i,2,n+1){
            if(i==2){
                dp[i][1]=1;
                dp[i][0]=dp[i-1][1];
                continue;
            }
            ll st=a[i-1]-a[i]+1;
            if(st<=2){
                dp[i][1]=min(dp[i-1][0],dp[i-1][1]+1);
                dp[i][0]=dp[i-1][1];
                ll ft=a[i-1]-a[i+1]+1;
                if(ft<=2){
                    dp[i][0]=min(dp[i][0],dp[i-1][0]+1);
                }
            }else{
                dp[i][1]=dp[i-1][1]+1;
                ll ft=(a[i]+1)-a[i+1];
                if(ft<=2){
                    dp[i][0]=dp[i-1][1];
                }else{
                    dp[i][0]=dp[i-1][1]+1;
                }
            }
        }
        PLN(min(dp[n+1][1],dp[n+1][0]));
    }
    return 0;
}
```

---

