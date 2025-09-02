# [NEERC 2014] Knockout Racing

## 题目描述

在 Pandora 星球上，比赛比以往任何时候都更受欢迎。但这些比赛相当不寻常。有 $n$ 辆车在一条长直赛道上参加比赛。每辆车以每秒 1 米的速度移动。赛道的坐标以米为单位。

第 $i$ 号车在赛道上两个坐标为 $a_{i}$ 和 $b_{i}$ 的点之间移动，起始于第 0 秒在点 $a_{i}$。车从 $a_{i}$ 移动到 $b_{i}$，然后从 $b_{i}$ 移动到 $a_{i}$，然后再从 $a_{i}$ 移动到 $b_{i}$，如此往复。

英俊的 Mike 想用炸药将一些车淘汰出比赛。因此他有 $m$ 个问题。第 $j$ 个问题是：从开始到 $t_{j}$ 秒后，坐标在 $x_{j}$ 到 $y_{j}$ 之间（包括边界）的车的数量是多少？

你的任务是回答 Mike 的问题。

## 说明/提示

时间限制：1 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 5
0 1
0 2
2 3
3 5
4 5
0 5 0
0 1 2
0 2 1
2 5 2
2 5 3
```

### 输出

```
5
1
2
4
3
```

# 题解

## 作者：mycbxzd (赞：3)

# 题目翻译
## 背景
在潘多拉星球，赛车比以往任何时候都更受欢迎。但这些比赛相当不寻常。有 $n$ 辆汽车参加在直线赛道上的比赛。每辆汽车以每秒 $1$ 米的速度移动。赛道上的坐标以米为单位。

第 $i$ 辆汽车在坐标为 $a_{i}$ 和 $b_{i}$ 的两点之间移动，从第二秒开始从点 $a_{i}$ 出发。汽车从 $a_{i}$ 移动到 $b_{i}$，然后从 $b_{i}$ 移动到 $a_{i}$，再从 $a_{i}$ 移动到 $b_{i}$，依此类推。

英俊的迈克想要用炸药淘汰一些汽车。因此，他有 $m$ 个问题。第 $j$ 个问题是：从开始后 $t_{j}$ 秒后，坐标在 $x_{j}$ 和 $y_{j}$ 之间的汽车数量是多少（包括边界）？

你的任务是回答迈克的问题。
## 输入格式

输入文件的第一行包含两个整数 $n$ 和 $m (1 \le n , m \le 1000)$ -- 比赛中汽车的数量和问题的数量。

接下来的 $n$ 行中，每行包含一辆汽车的描述：两个整数 $a_{i}$ 和 $b_{i} (0 \le a_{i}, b_{i} \le 10^{9}, a_{i} ≠ b_{i})$ -- 汽车 $i$ 移动的两个点的坐标。

接下来的 $m$ 行中，每行包含一个问题的描述：三个整数 $x_{j} , y_{j}$ , 和 $t_{j} (0 \le x_{j} \le y_{j} \le 10^{9}, 0 \le t_{j} \le 10^{9})$ -- 问题 $j$ 的坐标范围和时间。

## 输出格式

写入输出文件 $m$ 行。每行必须包含一个整数 -- 对应输入文件中给定的问题的答案。


# 解题

## 思路:
其实整个题目的核心就是三行代码解决

```cpp
if ((t / (b[j] - a[j])) % 2 == 1) {l = b[j] - t % (b[j] - a[j]);
else l = a[j] + t % (b[j] - a[j]);
if (l >= x && l <= y)ans++;
```

- 计算在给定时间 `t` 后，位于坐标范围 `[x, y]` 内的车辆数量，并将结果存储在 `ans` 中。
- 首先，声明了一个名为 `l` 的 `long long` 类型变量，用于存储每辆车在给定时间 `t` 后的位置。
- 然后，通过 `if-else` 条件语句，根据每辆车在奇数或偶数往返周期内的不同，计算每辆车在给定时间 `t` 后的位置 `l`。如果车辆在奇数往返周期内，则 `l` 被赋值为 `b[j] - t % (b[j] - a[j])`，否则 `l` 被赋值为 `a[j] + t % (b[j] - a[j])`。
- 接着，通过条件判断 `if (l >= x && l <= y)`，检查每辆车在给定时间 `t` 后的位置 `l` 是否在指定的坐标范围 `[x, y]` 内。若在范围内，则将 `ans` 加一，表示有一辆车在该时间范围内位于指定的坐标范围内。



### 式子解释(不知道叫啥了就叫式子吧):

```cpp
b[j] - t % (b[j] - a[j])
```

它计算了在给定时间 `t` 后，位于奇数往返周期内的车辆的位置。具体来说，`b[j] - a[j]` 表示车辆从起始坐标 `a[j]` 到结束坐标 `b[j]` 的距离，而 `t % (b[j] - a[j])` 则表示当前往返周期内已经行驶的时间。因为车辆是以每秒 1 米的速度行驶的，所以 `(b[j] - t % (b[j] - a[j]))` 表示从结束坐标 `b[j]` 开始倒退，倒退的距离为当前往返周期内已行驶的时间，从而得到了车辆在奇数往返周期内的位置。

```cpp
a[j] + t % (b[j] - a[j])
```

它计算了在给定时间 `t` 后，位于偶数往返周期内的车辆的位置。同样，`a[j]` 表示车辆的起始坐标，而 `t % (b[j] - a[j])` 则表示当前往返周期内已经行驶的时间。因为车辆是以每秒 1 米的速度行驶的，所以 `(a[j] + t % (b[j] - a[j]))` 表示从起始坐标 `a[j]` 开始继续向前行驶，行驶的距离为当前往返周期内已行驶的时间，从而得到了车辆在偶数往返周期内的位置。

### 判断原因解释:

```cpp
if (l >= x && l <= y)
```

它用于判断每辆车在给定时间 `t` 后的位置 `l` 是否在指定的坐标范围 `[x, y]` 内。如果车辆的位置 `l` 大于等于 `x` 并且小于等于 `y`，则说明该车辆在指定的坐标范围内，条件成立。

------------
## 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n, m, a[100010], b[1000010], x, y, t,ans,l;
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)cin >> a[i] >> b[i];
    // 对于每个问题，计算解决方案
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> t;
        ans = 0; 
        for (int j = 1; j <= n; j++) {
            if ((t / (b[j] - a[j])) % 2 == 1) {
    			// 如果车辆在奇数往返周期内
    			l = b[j] - t % (b[j] - a[j]);
			} else {
    			// 如果车辆在偶数往返周期内
    			l = a[j] + t % (b[j] - a[j]);
			}
            if (l >= x && l <= y)ans++;
        }
        cout << ans << endl;
    }
}
```

---

## 作者：iloveziwei (赞：2)

# 题目链接

[题 目 链 接](https://www.luogu.com.cn/problem/P6995)

# 分析

纯暴力 $O(n^2)$ 就可以过，对于每次询问，先计算每辆车在 $t$ 秒后的所在位置，如果车是从 $a$ 点过去（即 $\displaystyle\frac{t}{b-a}$ 为偶数），所在位置就应是 $t\bmod(b-a)$，如是从 $b$ 点回来（即 $\displaystyle\frac{t}{b-a}$ 为奇数），所在位置就为 $t-t\bmod(b-a)$。再判断所在位置是否在询问的区间内即可。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1010,M=1010;
struct node{
	ll a,b;
}e[N];
struct qu{
	ll x,y,t;
}ques[M];
ll n,m; 
int main(){
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		cin>>e[i].a>>e[i].b;
	}
	for(ll i=1;i<=m;i++){
		cin>>ques[i].x>>ques[i].y>>ques[i].t;
		ll ans=0;
		for(ll j=1;j<=n;j++){
			ll difference=e[j].b-e[j].a;//a,b两端点距离 
			ll to_back=ques[i].t/difference;//往返次数 
			ll meter=e[j].a+(to_back%2==0?ques[i].t%difference:difference-ques[i].t%difference);//所在位置
			if(meter>=ques[i].x&&ques[i].y>=meter) {
				ans++;
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：run_away (赞：1)

## 题意

给 $N(1\le N\le 1000)$ 辆在一条直线上跑的车，每辆车在区间 $[A_i,B_i](0\le A_i,B_i\le 10^9,A_i\ne B_i)$ 中行驶，可以把速度都看作一个单位速度。

然后给 $M(1\le M\le 1000)$ 个询问，每个询问都有一组 $X_i,Y_i,T_i(1\le X_i,Y_i,T_i\le 10^9)$ ，表示问在 $T_i$ 时，区间 $[X_i,Y_i]$ 内有几辆车。

## 分析

我们注意到，题目里的 $N$ 和 $M$ 都不大，所以 $O(NM)$ 的算法也可以过。

所以我们可以在每一组询问时，都直接暴力求解每辆车的位置，然后统计一遍就可以了。

经过观察，可以发现：因为车是来回往返的，时间为 $T_j$ ，单次距离为 $B_i-A_i$ ，所以当 $T_j\bmod (B_i-A_i)$ 为偶数时，是从 $A_i$ 往 $B_i$，此时该车距离 $A_i$ 点为 $T_j\bmod (B_i-A_i)$ ；为奇数时，是从 $B_i$ 往 $A_i$  ，此时该车距离 $A_i$ 点为 $T_j-T_j\bmod (B_i-A_i)$ 。

**我们此时求的距离是到 $A_i$ 的，而不是真实的位置，所以还要再加上 $A_i$ 。**

## Code

```c++
#include<bits/stdc++.h>
typedef long long ll;//个人习惯，没必要加long long
char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<21],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
ll n,m,x,y,t,space[1005],ans;
struct car{
    ll a,b;
}c[1005];//每辆车
signed main(){
    n=read(),m=read();
    for(int i=0;i<n;++i){
        c[i].a=read(),c[i].b=read();
    }//输入A，B
    for(int j=0;j<m;++j){
        x=read(),y=read(),t=read(),ans=0;
        memset(space,0,sizeof space);
        for(int i=0;i<n;++i){
            if((t/(c[i].b-c[i].a))%2==1){
                space[i]=(c[i].b-c[i].a)-t%(c[i].b-c[i].a);
            }
            else{
                space[i]=t%(c[i].b-c[i].a);
            }
            space[i]+=c[i].a;//求车的位置，记住要在c[i].a的基础上加
            if(space[i]>=x&&space[i]<=y)++ans;//统计
        }
        printf("%lld\n",ans);//输出
    }
    return 0;
}
```

---

## 作者：koukilee (赞：1)

题目：[[NEERC2014\] Knockout Racing](https://www.luogu.com.cn/problem/P6995)

****

## 题意

有 $n$ 辆车在 $[l_i,\ r_i]$ 之间往返行驶，速度为 $1$ 个单位每秒，初始时向右行驶。

有 $m$ 个询问，表示第 $t$ 秒在 $[x_i,\ y_i]$ 中有几辆车。

****

## 思路

根据范围 $1\ ≤\ n\ ,\ m\ ≤1000$，我们不难想到 $O(nm)$ 的暴力做法：

每次询问时，遍历所有车，判断当前时间这个车是否在规定范围内即可。

这里需要注意的是：**当这辆车走完了奇数次区间后，它现在是向左的。反之，它现在是向右的**。

分类讨论即可。

****

## 参考代码

```c++
/* The code is from koukilee*/
#include<cstdio>

using ll = long long;
const ll MAXN = 1010100, mod = 1e9 + 7; 

//char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<21],*O=obuf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template <typename T>
inline void read(T &sum) {
    ll tf = 0; char ch = getchar(); sum = 0;
    while(ch < '0' || ch > '9') tf = ch == '-' ? 1 : 0, ch = getchar();
    while(ch >= '0' && ch <= '9') sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
    (tf) && (sum =- sum);
}template <typename T,typename ...Args>
inline void read(T &tmp, Args &...tmps){read(tmp); read(tmps...);}

void printt(ll x){if(x >= 10) printt(x / 10); putchar(x % 10 + '0');} 
inline void print(ll x){x < 0 ? putchar('-'), printt(-x) : printt(x);}
template <typename T>
inline void put(T x){print(x), putchar('\n');}
template <typename T, typename ...Args>
inline void put(T &tmp, Args &...tmps){put(tmp); put(tmps...);} /*无所谓的头文件*/

ll n, m, l[MAXN], r[MAXN];

int main(){
	read(n, m);
	for(int i = 1; i <= n; i++) read(l[i], r[i]); /*读入，不讲。。。*/
	while(m--){
		ll x, y, t, ans = 0; read(x, y, t);
		for(int i = 1; i <= n; i++){
			ll len = r[i] - l[i];
            /*计算这个区间长度，这里需要注意的是 len 不是r[i] - l[i] + 1，因为它本身就占了一个点，相当于它只需要走r[i] - l[i]个点*/
			if((t / len) & 1){ /*分类讨论*/
				ll time = t % len/*剩下的步数*/, now = r[i] - time; /*奇数，从右向左*/
				if(now >= x && now <= y) ans++; 
			}
			else{
				ll time = t % len, now = l[i] + time; /*从左向右*/
				if(now >= x && now <= y) ans++; 
			}
		}
		put(ans); /*输出*/
	}
    return 0;
}
```

~~`Last`，本题解如果有问题，请联系我修改! awa~~

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/P6995)
# 分析
按照题意模拟即可。

我们只需要依次找到第 $i$（$1\le i\le N$）辆车在 $t_j$ 时刻时所在的位置，看这个位置是不是在区间 $[x_j,y_j]$ 之中，如果是，答案加 $1$，反之则什么也不变。

那怎么找到第 $i$（$1\le i\le N$）辆车在 $t_j$ 时刻时所在的位置呢？很简单。我们设每辆车一个时刻可以开 $1$ 个单位长度，一直到 $t_j$ 时刻时则会开 $t_j$ 个单位长度。但是，由于每辆车实在一个固定的区间内往返，所以还需要判断这辆车是在朝哪个方向开。我们可以发现，当车子开了偶数个全程时，此时继续开的话则是从起点往终点开，需要用终点的位置减去多开的单位距离，反之则是从终点往起点开，需要用起点的位置加上多开的单位距离。所以我们只需要知道这辆车此时开了几个全程，很好计算，只需要用 $b_i-a_i$ 的结果去除以 $t_j$（向下取整）即可。计算一辆车当前位置的代码如下：
```cpp
loction=(t/(b[j]-a[j]))%2==1?b[j]-t%(b[j]-a[j]):a[j]+t%(b[j]-a[j]);
```

**注意：考虑到数据范围，要开 `long long`。**
# code
```cpp
#include<iostream>
#define ll long long
using namespace std;
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	ll n,m,x,y,t,a[1000],b[1000],ans=0,loction;
	cin>>n>>m;
	for(int i=0;i<n;++i) cin>>a[i]>>b[i];
	for(int i=0;i<m;++i,ans=0) {
		cin>>x>>y>>t;
		for(int j=0;j<n;++j) {
			loction=(t/(b[j]-a[j]))%2==1?b[j]-t%(b[j]-a[j]):a[j]+t%(b[j]-a[j]);
			if(loction>=x&&loction<=y) ++ans;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Daniel_xu (赞：0)

# P6995 Knockout Racing——模拟算法基础
## 思路分析
由于数据范围 $ 1≤n,m≤1000 $ 我们使用暴力算法 $ O( N ^ 2 )$ 即可通过。
## 具体实现
对于每一个询问，声明变量 $ sum $ 表示有多少辆车在区间内，我们可以枚举每一辆车所处的位置，判断是否在区间内，如果是，则 $ sum \gets sum+1 $。
### 如何计算车辆的位置呢？
假设车辆在区间 $ [l,r] $ 之间行驶，要查询 $ T $ 时刻车辆所在的位置，$ len = r - l $ 则：
- 如果 $ \lfloor \frac {T}{len} \rfloor $ 为偶数，说明车辆在 $ T $ 时刻正在从 $ l $ 开往 $ r $，当前位置为 $ l + t \bmod len $。
- 否则，说明车辆在 $ T $ 时刻正在从 $ r $ 开往 $ l $，当前位置为 $ r - t \bmod len $。
# AC 代码
```cpp
#include<iostream>
using namespace std;
const int N=1005;
int a[N][2];//存储每辆车移动的区间 
int get_pos(int i,int t){//获取编号为 i 的车辆在 T 时刻的位置 
	int len=a[i][1]-a[i][0];
	if(t/len&1){//车正在从 R 开往 L 
		return a[i][1]-t%len;
	}else{//车正在从 L 开往 R 
		return a[i][0]+t%len;
	}
}
int main(){
	//输入 
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i][0]>>a[i][1];
	}
	while(m--){
		int l,r,t;
		cin>>l>>r>>t;
		int sum=0;
		//依次枚举每辆车所在的位置 
		for(int i=1;i<=n;i++){
			int pos=get_pos(i,t);//获取位置 
			if(l<=pos && pos<=r){//如果在区间内，sum 加 1 
				sum++;
			}
		}
		//输出结果 
		cout<<sum<<'\n';
	}
	return 0;
}

```

---

## 作者：danb123 (赞：0)

## 题目大意

本题的意思很明白，就是给定一个区间与时刻，判断有多少辆赛车在那个时刻属于这个区间中，计算数量。赛车会在指定区间来回行驶，每一秒行驶一个单位。

## 题目分析

这是一道很明显的模拟题目，本身这道题并没有很难的思路与算法，不过大家要注意他的数据范围，一定要开到长整型。

首先，对于每一次询问，遍历一遍每一辆赛车。并确定每一辆赛车的位置。那怎么确定位置呢？通过询问的时刻来判定。每一辆赛车在一个区间来回跑，为了确定是从起点跑回终点，还是从终点跑回起点。用这个区间的终点坐标减去它的起点坐标算出整个区间的长度。再用时间去除这个长度，算出赛车已经跑的趟数。如果为奇数代表从终点跑到起点，否则为从起点跑到终点。如果为从终点跑到起点，用终点坐标减去时刻取余区间长度的值。否则用起点坐标加上时刻取余区间长度的值。再判断是否在询问的区间中。

```cpp
long long l; 
(t/(b[j]-a[j]))%2==1? l=b[j]-t%(b[j]-a[j]):l=a[j]+t%(b[j]-a[j]); 
if(l>=x&&l<=y) cnt++;
```
下面是完整代码，时间复杂度为赛车数乘上询问数。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[100001],b[100001],cnt,x,y,t;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	for(int i=1;i<=m;i++){
		cin>>x>>y>>t;
		cnt=0;
		for(int j=1;j<=n;j++){
			long long l; 
			(t/(b[j]-a[j]))%2==1? l=b[j]-t%(b[j]-a[j]):l=a[j]+t%(b[j]-a[j]); 
			if(l>=x&&l<=y) cnt++;
		}
		cout<<cnt<<endl;
	}
}
```
审核员辛苦了！



---

## 作者：KyleShen1213 (赞：0)

## 题意
$N$ 辆车分别在不同的两端间来回跑，求在某一时刻某一段路上的车的数量。
## 思路
这道题暴力可以通过，每一次询问时，分别计算每辆车的位置，再判断是否在这个区间中，是的话，$ans$ 就加 $1$。
## 注意要点
计算车的位置是，要注意它的方向，如果跑的单程数量是偶数，那么是从 $a$ 到 $b$，否则就是从 $b$ 到 $a$。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct yy{
	ll a,b;
}y[1005];//定义车跑的区间的结构体 
struct qq{
	ll x,y,t;
}q[1005];//定义每次询问的结构体 
ll m,n; 
int main()
{
	cin>>n>>m;//输入 
	for(ll i=1;i<=n;i++)  cin>>y[i].a>>y[i].b;//输入 
	for(ll i=1;i<=m;i++)//循环m次询问 
	{
		cin>>q[i].x>>q[i].y>>q[i].t;ll ans=0;
		for(ll j=1;j<=n;j++)//循环n辆车 
		{
			ll d=y[j].b-y[j].a; ll jl=q[i].t/d;//计算单程路程和单程数量 
			ll wz=y[j].a+(jl%2==0?q[i].t%d : d-q[i].t%d);//计算车辆所在位置 
			if(wz>=q[i].x&&q[i].y>=wz)  ans++;//如果在规定区间内，ans++ 
		}
		cout<<ans<<endl;//每一次询问输出答案 
	}
	return 0;//结束程序 
}
```

---

## 作者：KevinHu0402 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6995)

#### 思路分析

拿到这道题，我首先翻了一下题目标签，发现没有，所以只能自己分析了……
  
  初步分析，题目告诉我们有**许多**车（不知道数量），每辆车都会在一个区间（闭区间）内运动，求的是一个区间在T时刻有多少车。拿到题目，我直接写了一个 struct 记录询问的区间，然后 while 循环，每次循环都要刷新车的位置，然后在 $Ti$ 时刻记录 struct 区间内车的数量，即可得出结果。

~~码风不好，这里道个歉。~~
#### 代码如下：
```
#include <bits/stdc++.h>
using namespace std;
struct node{
    int x,y;
}a[1001];
int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 0;i < n;i++){
        cin >> a[i].x >> a[i].y;
    }
    while(m > 0){
    	m--;
        int xx,yy,t;
        cin >> xx >> yy >> t;
        int ans = 0;
        for(int i = 0;i < n;i++){
            int tx = 0;
            if(t < (a[i].y - a[i].x)){
                tx = a[i].x + t;
            } 
            else{
                 int p = t % (a[i].y - a[i].x);
                 int q = t / (a[i].y - a[i].x); 
                 if(q & 1) tx = a[i].y - p; 
                 else tx = a[i].x + p; 
              } 
              if(tx >= xx && tx <= yy){
                  ans++;
              } 
        }
        cout << ans << endl;
    }
    return 0;
} 
```
最后不要忘了算一下题目的数据范围，这道题很明显只用int就够了。

~~求管理员通过！！~~

---

## 作者：VIOLET__FOREVER (赞：0)

[传送门](https://www.luogu.com.cn/problem/P6995)

## 题目分析
题目的数据范围很小，只有 $1000$ ，所以平方级的算法可以过去，所以我们考虑每一次询问都将全部的赛车的情况遍历一遍，而每一个赛车有两种情况：
1. 从左边开往右边
1. 从右边开往左边

这个我们可以通过 $t$ 取模 $r_i-l_i$ 得到，之后只需要判断是否在规定区域内就行。

## code
```cpp
#include<bits/stdc++.h>
#define int long long

const int N=1005;

using namespace std;

int n,m;
int l[N],r[N];

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];	
	}
	while(m--){
		int x,y,t;
		cin>>x>>y>>t;
		int ans=0;
		for(int i=1;i<=n;i++){
			if((t/(r[i]-l[i]))%2==0){//两种情况的判断
				int xx=l[i]+(t%(r[i]-l[i]));
				if(xx>=x && xx<=y) ans++;
			}
			else{
				int xx=r[i]-(t%(r[i]-l[i]));
				if(xx>=x && xx<=y) ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

