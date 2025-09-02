# [USACO18DEC] Convention S

## 题目描述

一场别开生面的牛吃草大会就要在 Farmer John 的农场举办了！

世界各地的奶牛将会到达当地的机场，前来参会并且吃草。具体地说，有 $N$ 头奶牛到达了机场（$1\le N\le 10^5$），其中奶牛 $i$ 在时间 $t_i$（$0\le t_i\le 10^9$）到达。Farmer John 安排了 $M$（$1\le M\le 10^5$）辆大巴来机场接这些奶牛。每辆大巴可以乘坐 $C$ 头奶牛（$1\le C\le N$）。Farmer John 正在机场等待奶牛们到来，并且准备安排到达的奶牛们乘坐大巴。当最后一头乘坐某辆大巴的奶牛到达的时候，这辆大巴就可以发车了。Farmer John 想要做一个优秀的主办者，所以并不想让奶牛们在机场等待过长的时间。如果 Farmer John 合理地协调这些大巴，等待时间最长的奶牛等待的时间的最小值是多少？一头奶牛的等待时间等于她的到达时间与她乘坐的大巴的发车时间之差。

输入保证 $MC\ge N$。

## 说明/提示

如果两头时间 $1$ 到达的奶牛乘坐一辆巴士，时间 $3$ 和时间 $4$ 到达的奶牛乘坐乘坐第二辆，时间 $10$ 和时间 $14$ 到达的奶牛乘坐第三辆，那么等待时间最长的奶牛等待了 $4$ 个单位时间（时间 $10$ 到达的奶牛从时间 $10$ 等到了时间 $14$）。

## 样例 #1

### 输入

```
6 3 2
1 1 10 14 4 3```

### 输出

```
4```

# 题解

## 作者：StudyingFather (赞：20)

本题可以采用二分答案的方法解决。

先将牛到达的时间排序，然后二分最长等待时间即可。

详细过程已经在代码里注释说明，这里不再赘述。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[100005];
int main()
{
 //freopen("convention.in","r",stdin);
 //freopen("convention.out","w",stdout);
 int n,m,c;
 scanf("%d%d%d",&n,&m,&c);
 for(int i=1;i<=n;i++)
  scanf("%d",&a[i]);
 sort(a+1,a+n+1);
 int l=0,r=a[n]-a[1];
 while(l<r)
 {
  int mid=(l+r)>>1,cnt=1,sta=1;
  for(int i=1;i<=n;i++)
   if(a[i]-a[sta]>mid||i-sta+1>c)
   //如果等待时间超过了二分中点mid或当前车辆已经满载，就重新发一辆车
   {
   	cnt++;
   	sta=i;
   }
  if(cnt<=m)r=mid;//该时间下车辆数充足，等待时间可以更小
  else l=mid+1;//车辆不足，等待时间要更长
 }
 printf("%d\n",l);
 fclose(stdin);
 fclose(stdout);
 return 0;
}
```

---

## 作者：Polarnova (赞：18)

考虑二分奶牛中的最大等待时间的最小值。  
通过判定 按此时间划分奶牛所需要的车辆数是否大于$M$ 来检查这种方案是否合法
```cpp
#include<cstdio>
#include<algorithm>
int n,m,c,a[100010];
bool aval(int x) {
    int car=1,fir=a[1],peo=0;
    for(int i=1;i<=n;i++) {
        if(++peo>c)car++,fir=a[i],peo=1;
        if(a[i]-fir>x)car++,fir=a[i],peo=1;
    }
    return car<=m;
}
int main() {
    scanf("%d%d%d",&n,&m,&c);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    std::sort(a+1,a+n+1);
    int l=0,r=a[n]-a[1];
    while(l<r) {
        int mid=(l+r)>>1;
        if(aval(mid))r=mid;
        else l=mid+1;
    }
    printf("%d",l);
    return 0;
}
```

---

## 作者：PersistentLife (赞：9)

乍一看，这题好像和 [P5017摆渡车](https://www.luogu.com.cn/problem/P5017) 差不多，但不同在哪里呢？

答案是这题是求等车时间最长的奶牛的最小值，而 P5017 是求等车之和的最小值。

那我们怎么办呢？

我们假设答案为 $X$，那么按照下面的方法安排是最优的。

- 为了节省车，我们尽可能让每一辆车上更多的牛，只要不超载即可。

- 如果此时等下一头牛上车会导致最先上车的奶牛等车时间超过 $X$，那么就让这辆车出发，并立即换下一辆车来等候。

所以，我们就可以写出下面的代码。

```cpp
bool check(int x)
{
	int cnt=1,lst=a[1],cntcow=1;//车的数量，第一只上车的奶牛到站的时间，目前车上奶牛只数
	for(int i=2;i<=n;i++)//因为我们默认装在第一头奶牛，所以i从2开始
	{
		cntcow++;//加一头
		if(a[i]-lst>x||cntcow>c)//如果时间超过或超载
		{
			cnt++;//发车
			cntcow=1;
			lst=a[i];//调下一辆车来
			if(cnt>m) return 0;//如果超过车数，就返回0
		}
	}
	return 1;//方法可行
}
```

但，我们怎么去确定 $X$ 呢？$\Theta(N^2)$ 暴力？

当然不是，因为 $N \le 10^5$。

那，二分？貌似可以。

```cpp
while(l<=r)
{
	int mid=(l+r)>>1;
	if(check(mid)) l=mid+1;
	else r=mid-1;
}
```

可是，这里是求最小值，不是最大值，我们不妨变形一下。

```cpp
while(l<=r)
{
	int mid=(l+r)>>1;
	if(check(mid)) r=mid-1;
	else l=mid+1;
}
```

记得读入后将到站时间排序哦！

```cpp
cin>>n>>m>>c;
for(int i=1;i<=n;i++) cin>>a[i];
sort(a+1,a+1+n);
l=0;r=a[n]-a[1];
```

告 辞 ！

---

## 作者：小小小朋友 (赞：5)

#### 题目描述

这是我们模拟赛题目……结果我就这道题满分……我还是太菜了。

有很多奶牛要坐车，但他们出来的时间不同，FJ有很多车去接，求**等待时间最长的奶牛等待的时间的最小值**。

#### 思路简述

看到要求**时间的最大值的最小值**，明显，这是一道二分答案题目，唯一需要思考的是其`check`函数的写法。

`check`函数运用贪心的思路，将奶牛上车时间进行排序，直接进行模拟，看是否可在每辆车都不超载，每个奶牛等待时间都不超标的情况下将所有奶牛接走。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,c,m,t[100005],l,r;
bool ok(ll x){
	int r_n=0;
	//printf("test%lld:\n",x);
	ll u_c=1,c_h=1,t_n=t[0];//u_c指用掉的车辆数，c_h指这辆车已有的奶牛数，t_n指这辆车到达时间
	for(r_n=1;r_n<n;r_n++){//遍历每个奶牛
		if((t[r_n]-t_n)>x||c_h>=c){//如果奶牛等候时间过长或车满载了，就换下一辆车
			t_n=t[r_n];//更新车的出发时间
			c_h=0;
			u_c++;
		}
		if(u_c>m){//如果车不够了，则不能满足条件
			return 0;
		}
		c_h++;//增加车上的奶牛数
	}
	return 1;
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&c);
	for(ll i=0;i<n;i++) scanf("%lld",&t[i]);//输入
	sort(t,t+n);//按时间排序
	r=1e9+1;//注意二分的边界并不小
	while(l<=r){//二分答案模板
		ll mid=(r+l)/2;
		if(ok(mid)){
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%lld",l);//输出即可
	return 0;
}
```


---

## 作者：EuphoricStar (赞：2)

## 思路：二分答案
二分奶牛最小的最大等待时间。判断过程用贪心实现。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, c, l, r = INT_MIN, mid;
vector<int> cows;

bool check(int time)
{
    int mm = 0, now = cows[0], nowi = 0;
    for (int i = 1; i < cows.size(); i++)
    {
        // 挨个奶牛遍历，如果时间超过了 time 或者车满了就发车，发前面 i 个牛
        if ((cows[i] - now) > time || (i + 1 - nowi) > c)
            mm++, nowi = i, now = cows[i];
    }
    return mm < m;
}

int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m >> c;
    if (n <= m)
    {
        cout << 0;
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        cows.push_back(a);
        r = max(r, a);
    }
    sort(cows.begin(), cows.end());
    // 二分法尝试最小的最大等待时间
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << l;
    return 0;
}
```


---

## 作者：WRuperD (赞：2)

## [更好的阅读体验](https://www.luogu.com.cn/blog/WRuperD/solution-p5119)

#### 1.题意：
	有n头奶牛在不同时间到达了机场，你有m辆车，每车做c头奶牛，问所有到达的奶牛中的等待时间最长的那只至少等待多少时间。

#### 2.1 用什么算法？
	首先，暴力枚举明显不行，但又没有其他较为高深的算法，所以考虑效率较高的二分答案。
    
#### 2.2 怎么用？
	二分的原理再次不多阐述，这里只用二分每头牛的最大等待时间，如果所有牛都可以在这个时间内（<=）等到车，r = mid - 1， 否则l = mid + 1。
    
#### 3.1 代码实现：
```c
#include<iostream>
#include<algorithm>
using namespace std;
int n, m, c;//如题,不解释 
long long a[100000 + 10];//a数组记录每只奶牛到达时间 
int check(int x) //二分基操 
{
	int num = 1;//目前用车数量 
	int cnt = 0;//目前车上牛 
	int temp = a[1]; //记录目前等待目前仍在等的最早来的奶牛的到达时间 
	for (int i = 1; i <= n; i++)
	{
		if (a[i] - temp > x or cnt == c)//满牛车走或牛等待时间超限 
		{
			num++;//车数++ 
			cnt = 1;//更新目前车上牛数 
			temp = a[i];//更新目前等待目前仍在等的最早来的奶牛的到达时间 
		} 
		else
		{
			cnt++;//车上牛数++ 
		}
	}//判断要用车数最小值是否小于FJ有的车 
	if (num <= m)
	{
		return 1;//满足条件, r = mid - 1;
	}
	else
	{
		return 0;//不满足, l = mid + 1;
	}
}
int main()
{
	cin >> n >> m >> c;
	long long l = 0, r;//二分基操 
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];//输入 
	}
	sort(a + 1, a + n + 1);//为二分保证单调不减排序 
	r = a[n] - a[1];//显然最长等到时间=最晚来的-最早来的 
	while (r >= l)//二分基操 
	{
		int mid = (l + r) / 2, q = check(mid);
		if (q)//以下上面解释过 
		{
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	cout << l << endl;//完美输出结束!!! 
	return 0;
}
```
#### 4.1 总结
	这是一道十分好的二分题目，但完全没到蓝题难度，顶多黄。


---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/P5119)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到题目要求，我们不难想到二分答案。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;并且我们还可以发现一个贪心性质，即所有的大巴的出发时刻一定对应着一头牛的到达时刻。这个性质很显然。如果将出发时刻前移，那么也可以满足要求，但是装载牛的数量减少会导致答案不会优于当前方案；如果后移，就有可能使得最大值增长，答案不会更优。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是就可以用贪心性质来检查答案，每次选取最长的一段区间的牛作为一辆车的乘客，最后检查是否可以装得下。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;时间$O(n\log_2(\max t))$  
# 代码
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 1 ) + ( x << 3 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) write( x / 10 );
	putchar( x % 10 + '0' );
}

int t[MAXN];
int N, M, C;

bool chk( const int len )
{
	int need = 0;
	for( int i = 1, rig = 0 ; i <= N ; )
	{
		for( rig = i ; rig <= N && t[rig] - t[i] <= len && rig - i + 1 <= C ; rig ++ );
		need ++, i = rig;
	}
	return need <= M;
}

int main()
{
	int l = 0, r, mid;
	read( N ), read( M ), read( C );
	for( int i = 1 ; i <= N ; i ++ ) read( t[i] );
	sort( t + 1, t + 1 + N );
	r = t[N];
	while( r - l > 1 )
	{
		if( chk( mid = l + r >> 1 ) ) r = mid;
		else l = mid + 1;
	}
	if( chk( l ) ) write( l ); 
	else write( r );
	putchar( '\n' );
	return 0;
}
```

---

## 作者：NKL丶 (赞：1)

## 主要思路：二分答案。  
要二分的东西也十分简单明了：即等待时间最长的奶牛等待的时间的最小值。  
附上代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int l,r,mid,n,m,c,a[100005],now,sum,ans;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);//先进行排序，以便后面操作
	l=0;r=a[n];//最小值即每头奶牛一来就上车（即0），最大值即所有奶牛都要上同一台车（即a[n]）
	while(l<=r)//进行二分
	{
		mid=(l+r)>>1;
		now=1;//now表示现在一开始等待的奶牛的下标
		sum=1;//sum即等待时间为mid的话所需要的车数
		for(int i=1;i<=n;i++)
		{
			if(i-now+1>c||a[i]-a[now]>mid)//如果已经超载或者等待的时间已经超过了mid
			{
				now=i;//用第i只奶牛作头（有点不准）
				sum++;//车数++
			}
		}
        //缩小范围
		if(sum<=m)ans=mid,r=mid-1;//如果合法，更新答案
		else l=mid+1;
	}
	cout<<ans;//输出
	return 0;
}
```


---

## 作者：BreakPlus (赞：1)

第一眼看到这题，相信很多人都像我一样没有头绪。

首先我们来想想，假设我们得到了问题的答案，该如何去验证？

假设从第一个奶牛开始都做第一班车，定义 $cnt=1$。

枚举整个 $t$ 数组，一旦发现超载了，或是等待时间满了怎么办？

那么从当前开始，奶牛们都去承载第二版车，将 $cnt$ 调整为当前坐标值，如此循环下去。

最后，要用的飞机数量小于 $m$ 且答案最小即为答案。

这只是判断部分，我们如何寻找答案呢？暴力枚举吗？显然会超时。

我们假设问题的答案为 $x$ 则 $x$ 越大要用的飞机数量就越少。由这个你想到了啥？**二分**。

使用二分答案即可求出。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

int n,m,c,t[100010];
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x;
}
int main()
{
    n=read();m=read();c=read();
    for(int i=1;i<=n;i++) 
        t[i]=read();
    sort(t+1,t+1+n);
    int l=1,r=t[n]-t[1];//二分边界
    while(l<r)
    {
        int middle=(l+r)/2;
        int cnt=1,now=1;
        for(int i=1;i<=n;i++)
        {
            if(i-now+1>c||t[i]-t[now]>middle)
            {
                cnt++;
                now=i;
            }
        }
        if(cnt<=m) r=middle;//如果飞机数小于等于 m 那么尝试更小
        else l=middle+1;//不够只能往大的答案想了qaq
    }
    printf("%d\n",l);
    return 0;
}
```

---

## 作者：__Hacheylight__ (赞：1)

T1 Convention

【题意】

有$n$头奶牛，第$i$头在$a[i]$时刻到达，有$m$量大巴车接他们，每辆最多载$k$人（**注意不需要坐满才能走**），求等候时间最长的奶牛最短时间是多少

【分析】

又是最大值最小的问题，很容易想到二分答案

二分等候时间最长的奶牛等候$mid$分钟

$check$函数也很好想

先按到达时间把奶牛排序

记录第一个上车的时间和已上车的人数

如果当前奶牛和第一个上车的奶牛的间隔时间$>mid$或已上$k$人就换下一辆，最后判断用的车子数量是否少于$m$即可。

还是很裸的二分。

【代码】

```cpp
#include <bits/stdc++.h>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 100010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
    char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
    cout << x << endl ;
    exit(0) ;
}

void PRINT(string x) {
    cout << x << endl ;
    exit(0) ;
}

void douout(double x){
     printf("%lf\n", x + 0.0000000001) ;
}

int n, m, c, ans ;
int a[N] ;

bool check(int x) {
	int now = 1, fitake = a[1], peo = 1 ;
	for (int i = 2; i <= n; i++) {
		if (a[i] - fitake > x) now++, fitake = a[i], peo = 1 ;
		else {
			peo++ ;
			if (peo > c) now++, fitake = a[i], peo = 1 ;
		}
		  
	}
	if (now > m) return false ;
	return true ; 
}

int main() {
	scanf("%d%d%d", &n, &m, &c) ;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]) ;
	sort(a + 1, a + n + 1) ;
	int l = 0, r = iinf / 2  ;
	while (l + 1 < r) {
		int mid = (l + r) >> 1 ;
		if (check(mid)) r = mid ;
		else l = mid ;
	} 
	printf("%d\n", r) ;
}

```

---

## 作者：Unordered_OIer (赞：0)

# P5119 题解
拆题：最长等待时间的最小值。  
→**枚举答案(顺序/二分)**  

$check\_mid(time)$函数的定义：  
按照此时间划分奶牛所需要的车辆数是否$<=M$判断合法。  

$check\_mid$ : 
```cpp
bool check_mid(int wait){ // 判断是否可行 
	int wagons=1;
	int firstArrival=arv_tim[0];
	int firstIndex=0;
	// 注意初始化 
	for(int i=1;i<N;i++) // 注意这里是1~N-1 
		if(arv_tim[i]-firstArrival>wait||i+1-firstIndex>C){
		// 满足序列条件无需增加，不满足则加车 
			wagons+=1; // wagons标记加1 
			firstArrival=arv_tim[i]; // 更新操作 
			firstIndex=i; // 更新操作 
		}
	return (wagons<=M); // 是否<=M 
}
```

二分 : 
```cpp
int erfen(int l_bnd,int u_bnd){
	if(l_bnd==u_bnd)return l_bnd; // l==r 
	if(l_bnd+1==u_bnd){ // l+1=r 
		if(check_mid(l_bnd))return l_bnd; // 如果l可以，return l 
		return u_bnd; // 否则return r 
	}
	int mid=(l_bnd+u_bnd)/2; // 计算mid(>>1也可以) 
	if(check_mid(mid))return erfen(l_bnd,mid); // 递归实现二分操作 
	else return erfen(mid+1,u_bnd); // 递归实现二分操作 
	// 一边向左，一边向右 
}
```

## Over~~
```cpp
#include<iostream>
#include<algorithm>
// 可以引用"bits/stdc++.h"
using namespace std;
int N,M,C; // 定义变量NMC，意义为题目中的意义 
int arv_tim[100000]; // 记录奶牛的到达时间 
bool check_mid(int wait){ // 判断是否可行 
	int wagons=1;
	int firstArrival=arv_tim[0];
	int firstIndex=0;
	// 注意初始化 
	for(int i=1;i<N;i++) // 注意这里是1~N-1 
		if(arv_tim[i]-firstArrival>wait||i+1-firstIndex>C){
		// 满足序列条件无需增加，不满足则加车 
			wagons+=1; // wagons标记加1 
			firstArrival=arv_tim[i]; // 更新操作 
			firstIndex=i; // 更新操作 
		}
	return (wagons<=M); // 是否<=M 
}
int erfen(int l_bnd,int u_bnd){
	if(l_bnd==u_bnd)return l_bnd; // l==r 
	if(l_bnd+1==u_bnd){ // l+1=r 
		if(check_mid(l_bnd))return l_bnd; // 如果l可以，return l 
		return u_bnd; // 否则return r 
	}
	int mid=(l_bnd+u_bnd)/2; // 计算mid(>>1也可以) 
	if(check_mid(mid))return erfen(l_bnd,mid); // 递归实现二分操作 
	else return erfen(mid+1,u_bnd); // 递归实现二分操作 
	// 一边向左，一边向右 
}
void paixu(int l_bnd,int u_bnd){
	// 排序，纯属调用简单，可以不写 
	sort(arv_tim+l_bnd,arv_tim+u_bnd);
}
int main(){
	cin>>N>>M>>C; // 输入 
	for(int i=0;i<N;i++)cin>>arv_tim[i]; // 输入 
	// 输入不解释 
	paixu(0,N); // 将奶牛到达时间排序 
	cout<<erfen(0,1000000000)<<'\n'; // l=0,r=inf来二分 
	return 0; // 归0 
}
```
# 后记
细节需要注意，否则会掉进坑里没法AC所有点。  
~~为什么这道题是提高+/省选-~~

---

## 作者：Priori_Incantatem (赞：0)

### 题目大意
$n$ 头奶牛，$m$ 辆大巴，每头牛有一个到达时间，求怎样设计坐车方案使得等待时间最久的奶牛的等待时间最少

这题其实没有蓝吧，顶多也就是个绿，二分 + 贪心就好了

我们二分等待最久的时间 $x$，但在对应设计的方案中，不一定有牛的等待时间会达到 $x$，只是保证等待时间不超过 $x$

对于每一次二分的 $x$，我们让每辆大巴尽可能多做人，且满足等待时间最久不超过 $x$，最后输出就好啦

```cpp
#include<cstdio> 
#include<iostream>
#include<algorithm>
using namespace std;
const int Maxn=100000+20,inf=0x3f3f3f3f;
int n,m,k;
int a[Maxn];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
bool check(int x)
{
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		int j=i;
		while(j-i+1<=k && a[j]-a[i]<=x && j<=n)++j;
		--j;
		++cnt,i=j;
		if(cnt>m)return 0;
	}
	return 1;
}
int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;++i) 
	a[i]=read();
	sort(a+1,a+1+n);
	
	int l=0,r=a[n]-a[1],mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}

```

---

## 作者：Zenith_Yeh (赞：0)

“要想知正解，就先看题面。”

一看题面，就知道可以用二分答案来解决。

题面中说：等待时间最长的奶牛等待的时间的最小值，注意 **最长的最小** 。

我们二分最长的等待时间，在通过贪心来 $check$。

**代码：**
```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//优美的快读。
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
int l=0,r=1000000000,n,m,c,t[100005];
inline bool check(int x)//贪心check
{	int liangshu=0,now_min=-1100000000,now=0;
	for(register int i=1;i<=n;++i)
	{	if(now==c||t[i]-now_min>x)//一辆车尽量坐更多的牛。
		{	liangshu++;
			now=0;
			now_min=t[i];
		}
		now++;
	}
	return liangshu<=m;
}
int main()
{	cin>>n>>m>>c;
	for(register int i=1;i<=n;++i)cin>>t[i];
	sort(t+1,t+n+1);
	while(l<r)//二分答案。
	{	int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	cout<<r;
	return 0;
}

```


---

