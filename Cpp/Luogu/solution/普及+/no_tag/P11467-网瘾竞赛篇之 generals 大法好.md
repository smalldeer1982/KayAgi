# 网瘾竞赛篇之 generals 大法好

## 题目描述

t1e 同学沉迷于打 generals 的 1v1 模式，他将游戏简化为以下内容：

初始时 t1e 有一座城堡，每回合结束时会生产 $x$ 单位的兵力，他的对手也有一座城堡，每回合结束时会生产 $y$ 单位的兵力，初始时（第 $0$ 回合）双方的兵力都为 $0$。

有 $n$ 座其他城堡可以被 t1e 占领，t1e 每个回合开始时可以攻占**最多** $1$ 个城堡，占领第 $i$ 个城堡需要消耗 $a_i$ 单位的兵力，从占领后的下一个回合开始，该城堡每回合结束时为 t1e 生产 $1$ 个单位的兵力。

t1e 同学想知道最早在第多少个回合，他的兵力能超过对手的兵力。

如果永远无法超过，输出 $-1$。

## 说明/提示

对于第一组数据，t1e 的最优操作过程如下：
| 回合 | 回合结束时 t1e 的兵力      | 回合结束时对手的兵力 |
| :----: | :----------------------------:| :--------------------: |
| 0    | 0                     | 0                    |
| 1    | 1                     | 1                    |
| 2    | 1                     | 2                    |
| 3    | 3                     | 3                    |
| 4    | 5                     | 4                    |

注意：t1e 在第 $2$ 回合开始时占领了 $1$ 号城堡。

$1\le T\le 100$，$1 \le n, \sum n \le 2\times 10^{5}$，$1 \le x, y, a_i \le 10^5$。

## 样例 #1

### 输入

```
4
1 1 1
1
6 1 2
1 1 4 5 1 4
2 1 3
1 1
1 3 2
1```

### 输出

```
4
7
-1
1```

# 题解

## 作者：封禁用户 (赞：5)

神奇模拟。

把城堡需要的兵力排个序，当 t1e 的兵力能买消耗最小的城堡时，判断一下不买该城堡的答案，与全局答案取 $\min$，然后直接默认买掉（如果不买更优那么后面就不会再更新全局答案），循环模拟一下就行。

大概就是这样：

```cpp
il void mian(){
	read(n, x, y), readArr(a + 1, n);
	if (x + n <= y) return cout << "-1", void();
	if (x > y) return cout << "1", void();
	sort(a + 1, a + n + 1);
	int b1 = 0, b2 = 0, ans = 0, ret = inf / 2;//b1 是 t1e 的兵力，b2 是对手的兵力
	L(i, 1, n){
		int tim = (a[i] - b1 - 1) / x + 1, t = inf / 3;
		if (b1 >= a[i]) tim = 0;
		if (x > y) t = (b2 + 1 - b1 - 1) / (x - y) + 1;
		ckmin(ret, ans + t), ans += tim + 1, b1 += tim * x, b2 += tim * y;
		b1 -= a[i], b1 += x, x++, b2 += y;
	}
	write(min(ret, ans + (b2 + 1 - b1 - 1) / (x - y) + 1));
}
```

---

## 作者：TLE_Automat (赞：4)

**这里是官方题解。**

因为占领每个城堡所产生的收益是相同的，所以最优情况下一定是按照 $a_i$ 从小到大的顺序占领城堡。

假设最终兵力超过对方时，t1e 已经额外占领了 $p$ 座城堡，那么这 $p$ 座城堡一定是越早占领，产生的收益越多。

有了以上两个结论，我们可以先将 $a_i$ 从小到大排序，设 $f_i$ 代表额外占领 $i$ 座城堡所需要的最小回合数，$g_i$ 代表额外占领第 $i$ 座城堡时剩余的总兵力，那么可以推出如下的状态转移方程：
$$
\begin{aligned}

f_{i} &= f_{i - 1} + \max\left(0, \left\lceil\frac{a_{i} - g_{i - 1}}{x + i - 1}\right\rceil\right) + 1 \\

g_{i} &= g_{i - 1} + (x + i - 1) \times \left\lceil\frac{a_{i} - g_{i - 1}}{x + i - 1}\right\rceil - a_i

\end{aligned}
$$
对于所有 $i$，求出额外占领 $i$ 座城堡后，总兵力超过对方所需要的最小总回合数，求最小值即为答案。

需要额外判断，如果将所有城堡全部占领后，兵力增长速度仍然不比对手快，即 $x + n \le y$ 时，兵力永远不会超过对方。

---

## 作者：_std_O2 (赞：3)

# P11467题解
考虑贪心，每次开所耗兵力最小的塔，当 $x>y$ 时判断是否再开新的塔。
## 证明
假设每次不是开所耗兵力最小的塔，又因为只能当 $x>y$ 时 t1e 同学的兵力才能超过对面。则所让 $x>y$ 时所需的回合数一定大于每次开所耗兵力最小的塔所需的回合数，故假设不成立。
## 判断有无解
显然只有当 $x+n>y$ 时 t1e 同学的兵力才能超过对面。当 $x+n \le y$ 时 t1e 同学的兵力永远无法超过对面。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,x,y,T,a[300005];
signed main(){
	cin>>T;
	while(T--){
		int ans=1e18;
		cin>>n>>x>>y;
		int army=0,num=0,add=x;//army 为现有兵力，num为回合数，add 为每回合的产兵数
		for(int i=1;i<=n;i++) cin>>a[i];
		if(x>y) {
			cout<<1<<endl;
			continue;
		}
		if(x+n<=y){
			cout<<-1<<endl;
			continue;
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			num=max(num+1,(int)ceill((a[i]-army)*1.0/add)+1);
			int cnt=add*num+army;
		    add++,army=cnt-a[i]-add*num;
			if(add>y)ans=min(ans,army/(y-add)+1);//判断是否再多开塔
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：fish_love_cat (赞：3)

我超，Gen！

---

推式子即可，半个小时就推完了。

贪心的策略是优先占好占的堡。

注意堡不用全占就可以开始追了。答案取最小值。

~~然后被细节卡了一个小时 /qd~~

所以来说说实现。

先判掉一招秒和无解的情况。

然后模拟每一个堡占掉后的情况，用推出来的柿子算即可。

注意最好不要出现负数，要特判。注意到出现负数以后要考虑的多上天了，容易锅。

每个变量所代表的一定要闹清楚，不然很容易挂。注释的重要性充分体现。

算了一下应该需要 `long long`，也开着。

还有，反复手玩样例极有助于调题。

警惕题面要求的是超对手而追平不被允许。还有就是占堡要一个回合，且与此同时所拥有的堡都可以生产。太好了没注意到挂疯了。

应该没了。

代码贴一下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
int fish(int times,int xnow,int y,int x){
    int ynow=y*times;
    int flc=ynow-xnow;
    int cat=x-y;
    return 1+flc/cat+times;
}
void solve(){
    int n,x,y;
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+1+n);
    if(x+n<=y){
        puts("-1");
        return;
    }else if(x>y){
        puts("1");
        return;
    }
    int ans=0,sum=0,ret=1e18;
    for(int i=1;i<=n;i++){
        if(a[i]>sum){
            a[i]-=sum;
            int flc=ceil(a[i]*1.0/(x+i-1))+1;
            ans+=flc;
            sum=flc*(x+i-1)-a[i];
        }else{
            sum-=a[i];
            ans++;
            sum+=x+i-1;
        }
        if(i+x>y)
        ret=min(ret,fish(ans,sum,y,i+x));
    }
    cout<<ret<<endl;
    return;
}
signed main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：3)

这个问题可以被抽象成一次函数。什么时候 t1e 兵力随时间变化的一次函数的斜率比对手大了，他就能超过对手。

显然可以证明，t1e 一定会先攻占 $a_i$ 较小的城堡，因为这些城堡的生产速度都一样是 $1$。

于是从小到大看每个城堡，维护 t1e 兵力的最后一段一次函数的解析式（斜率一定 $>0$）。攻占下这个城堡时，算出什么整数时刻第一次得到 $\ge a_i$ 的兵力，然后在下一个回合攻占。也就是将当前时刻的兵力值减去 $a_i$，并且斜率增加 $1$，得到新一段的函数解析式。

每次算什么时候超过对手，就是算这个一次函数和 $y=Yx$（$Y$ 为题目中的 $y$）的交点 $x$ 坐标再上取整即可。当然如果斜率没有超过 $Y$ 就不要算了。

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
int t,n,x,y,a[200010];
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>x>>y;
        for(int i=1;i<=n;i++)cin>>a[i];
        if(x>y)
        {
            cout<<1<<endl;
            continue;
        }
        sort(a+1,a+n+1);
        int k=x,b=0,l=0,ans=9e18;
        for(int i=1;i<=n;i++)
        {
            l=max(l+1,(int)ceill((a[i]-b)*1.0/k)+1);
            int cnt=k*l+b;
            k++,b=cnt-a[i]-k*l;
            if(k>y)ans=min(ans,b/(y-k)+1);
        }
        if(ans<9e18)cout<<ans<<endl;
        else cout<<-1<<endl;
    }
    return 0;
}
```

---

## 作者：wzy0 (赞：1)

阅读题目，发现对于任一其他城堡，每回合都只能生产 $1$ 个单位的兵力。 \
如果 $x + n \le y$，则永远无法超过对手的兵力，所以输出 $-1$。 \
如果 $x > y$，则第一回合就超过对手的兵力，所以输出 $1$。 \
否则，我们肯定是按 $a_i$ 从小到大攻占城堡。

我们假设答案为 $an$。 \
然后，我们枚举攻占到第 $i$ 座城堡,其中 $i \in [ 0 , n ]$。 \
设达成要求需要 $u_i$ 个回合，剩余 $b_i$ 单位兵力，以及还需要 $v_i$ 个回合才能超过对方。

初始状态显然是 $i = 0$，这时 $u_0 = 0 , b_0 = 0$ 且不可能超过对方。 \
然后，对于 $i \in [ 1 , n ]$，我们计算：
$$l = \max \{ 1 , \lceil \frac{a_i - b_i}{x + i-1} \rceil \}$$
$$u_i = u_{i-1} + l , b_i = b_{i-1} + l \cdot (x + i-1) - a_i$$
此时，如果 $x + i > y$，我们再计算：
$$v_i = \lceil \frac{u_i \cdot y - b_i}{x + i - y} \rceil$$
$$an \gets \min \{ an , v_i \}$$

最后输出 $an$ 即可，时间复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

long long t,n,x,y,a[200005],l,r,s,k,in;

bool com(long long i,long long j){
	return i<j;
}

int main(){
	ios::sync_with_stdio(0);cin.tie();cout.tie();
	cin>>t;
	while(t--){
		cin>>n>>x>>y;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		if(x+n<=y){
			cout<<-1;
		}else if(x>y){
			cout<<1;
		}else{
			in=1000000000000000018;
			l=r=s=k=0;
			sort(a+1,a+n+1,com);
			for(int i=1;i<=n;i++){
				k=max((a[i]-l+(x-1))/x+1,1ll);
				s+=k;
				l+=k*x;l-=a[i];
				r+=k*y;x++;
				if(x>y){
					if(r>=l){
						in=min(in,s+(r-l)/(x-y)+1);
					}else{
						in=min(in,s);
						break;
					}
				}
			}
			cout<<in;
		}
		cout<<'\n';
	}
	return 0;
}

```

---

## 作者：N1tr0us_Acid (赞：1)

非常好的贪心，使我的大脑旋转。

# $\texttt{Solution}$
因为不论每个城堡的耗费兵力多少，它们每回合对总兵力的贡献都是 $1$，所以我们肯定要按兵力从小到大攻占城堡。  

其次，如果在某一回合我们的总兵力已经可以攻占某一座城堡，那么立刻攻占该城堡一定优于在若干回合后再攻占该城堡，因为城堡消耗兵力不变，越早攻占，这座城堡就会提供越多的贡献。

那么就很好写了，我们预处理出 $tim$ 和 $les$ 两个数组，$tim_i$ 表示最早在第几回合可以攻下 $i$ 座城堡，$les_i$ 表示攻下之后还剩多少兵力，然后对于每种情况进行模拟即可。

注意两个特判：
1. 如果攻占了所有城堡仍不能超过对手，就是 $-1$。
2. 如果一个城堡都不用攻占，即 $x > y$，就只用 $1$ 回合。

# $\texttt{Code}$
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int x, y, n;

const int N = 2e5 + 10, inf = 0x3f3f3f3f;

int tt;

int a[N], tim[N], les[N];

signed main(void) {
    cin >> tt;

    while (tt --) {
        cin >> n >> x >> y;

        for (int i = 1; i <= n; i ++) cin >> a[i];

        sort(a + 1, a + n + 1); // 一定要记得排序！

        if(x + n <= y) { // 特判1
            puts("-1");

            continue;
        }

        if(x > y) { // 特判2
            puts("1");

            continue;
        }

        int nowx = 0, kx = x;

        for (int i = 1; i <= n; i ++) {
            if(a[i] <= nowx) {
                tim[i] = tim[i - 1] + 1;

                nowx -= a[i];
                nowx += kx;

                les[i] = nowx;

                kx ++;

                continue;
            }

            int del = (a[i] - nowx) / kx + ((a[i] - nowx) % kx != 0);

            nowx += del * kx + kx;
            nowx -= a[i];
            kx ++;

            tim[i] = tim[i - 1] + del + 1;
            les[i] = nowx;
        }

        int ans = inf;

        for (int i = y - x + 1; i <= n; i ++) { // 只有当 x + i > y 时，才有可能超过对手，所以 i 从 y - x + 1 开始。
            int nowy = y * tim[i];

            int del = nowy - les[i];

            int wil = del / (x + i - y) + 1;

            ans = min(ans, tim[i] + wil);
        }

        cout << ans << endl;
    }
}

```

---

## 作者：_bruh_ (赞：1)

## P11467 题解

[题目传送门](https://www.luogu.com.cn/problem/P11467)

### 解题思路

首先注意两个特殊情况：

1. 当 $ x > y $ 时，显然在回合一时胜利。
2. 当 $ x + n > y $ 时，显然此时无论如何都无法获胜。

然后，~~经常玩 generals 的同学都知道~~，每次占领塔时应尽量选择**消耗少**的塔，所以可以对于塔以**占领其所需兵力**为第一关键词进行升序排序。这是一种典型的贪心思维。

接着，不难发现，想要占领一座塔所需的回合数为：

$$ \lceil{\frac{N-R}{x}}\rceil $$

其中 $ N $ 表示所需兵力，$ R $ 表示当前剩余兵力，$ x $ 表示每回合生产兵力。

其次，由于我们不确定占领多少座塔时可以达到题目要求，即在最快时间内超过敌方兵力，因此，每次占领塔时都需要判断此时不再占领塔超过敌方兵力的耗时，显然为：

$$ \lceil{\frac{N-R}{x-x'}}\rceil \quad (x'< x) $$

其中 $ N $ 表示敌方兵力，$ R $ 表示当前剩余兵力，$ x $ 表示每回合生产兵力，$ x' $ 表示敌方每回合生产兵力。

完毕。

### 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
inline void write(ll x)
{
	if(x<0)x=-x,putchar(45);
	if(x>9)write(x/10);
	putchar(x%10^48);
}
inline ll read()
{
	ll x=0;bool c=false;char a=getchar();
	for(;a<'0'||a>'9';a=getchar())c|=a==45;
	for(;a>='0'&&a<='9';a=getchar())x=(x<<3)+(x<<1)+(a^48);
	return c?-x:x;
}
#define R read()
using namespace std;

ll n,x,y,ans,sum,a[200002];

int main()
{
	ll T=R;
	while(T--)
	{
		n=R,x=R,y=R;sum=0;ans=11451919810;
		for(ll i=1;i<=n;++i)a[i]=R;
		if(x>y){write(1);putchar(10);continue;}
		if(x+n<=y){write(-1);putchar(10);continue;}
		sort(a+1,a+1+n);
		ll en=0,ar=0;
		for(ll i=1;i<=n;++i)
		{
			ll tick=max(0ll,(a[i]-ar-1)/x)+2;
			if(ar>=a[i])tick=1;
			en+=tick*y;
			ar+=tick*x-a[i];
			sum+=tick;
			cout<<sum<<": "<<ar<<"  "<<en<<endl;
			++x;
			if(x>y)
			{
				ll tick=max(0ll,(en-ar-1)/(x-y))+1;
				if(tick*(x-y)+ar==en)++tick;
				ans=min(tick+sum,ans);
			}
		}
		write(ans);
		putchar(10);
	}
	return 0;
}
```

---

## 作者：Statax (赞：1)

## 前言

~第一次在机房写题解，有点紧张。~

## 题目分析

这个题不算难，看题解都是推式子，这里写了个二分答案。

看题可以发现是一个贪心，因为每个城堡贡献一样，所以我们要按消耗最小及 $a_i$ 从小到大依次占领。

### 无解情况？

可以发现无解当且仅当所有城堡都占领后每天的兵力单位依然不够，及 $x + n \leq y$。

### 最优情况

如果我们 $x$ 本身就大于 $y$，那么只需要一回合就够了。

### 普通情况

这下就是关键部分了。

我们枚举要占领多少个城堡，假设当前将要占领第 $i$ 个城堡，占领前的兵力为 $sum$，初始为 $0$；已经占领 $k$ 个城堡，初始为 $x$。

那么我们要占领第 $i$ 个城堡所需要的回合就是 $\frac{a_i - sum + k - 1}{k}$，记作 $need$。

此时：$sum \gets sum + need \times k - a_i$ 且 $k \gets k + 1$。

由于下一回合开始城堡才能产生贡献，所以我们回合也要加一。那如果我们现在 $k > y$ 了，也就代表在将后某一回合会超过对手了，那我们就枚举具体在哪一天就行了，而这个枚举的过程用二分实现即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
constexpr int MAXN = 1e6 + 5;
constexpr int INF = 0x3f3f3f3f;
constexpr int MOD = 998244353;

int t;
int n, x, y;
int a[MAXN];

int work () {
	sort(a + 1, a + n + 1);
	int ret = INF;
	int sum = 0, cnt = 0, tme = 0;
	for (int i = 1; i <= n; ++i) {
		tme = (x + i - 1);
		int need = max((a[i] - sum + tme - 1) / tme, 0ll) + 1;
		sum += need * tme - a[i], cnt += need;
		if (sum > y * cnt) 
			ret = min(ret, cnt);
		else if (x + i > y) {
			int l = cnt + 1, r = 1e11, ans = INF;
			while (l <= r) {
				int mid = (l + r) / 2; 
				if ((mid - cnt) * (x + i) + sum > y * mid) {
					r = mid - 1,
					ans = mid;
				} else {
					l = mid + 1;
				}
			} ret = min(ret, ans);
		}
	} return ret;
}

int Judge () {
	if (x > y) 
		return 1;
	if (x + n <= y) 
		return -1;
	else 
		return work();
}

signed main () {
	cin >> t;
	for (; t; --t) {
		cin >> n >> x >> y;
		for (int i = 1; i <= n; ++i) 
			cin >> a[i];
		cout << Judge() << endl;
	}
	return 0;
}
```

---

## 作者：Kendieer (赞：1)

题外话：[**generals**](https://generals.io/)

---

本题传送门：[**P11467**](/problem/P11467)

## 思路构建

设当前 **t1e** 的生产速率为 $k$，对手的速率恒为 $y$，初始情况下 $k=x$。

### 无解情况

若 $k+n \le y$，则兵力永远无法超过对手。

### 有解情况

对于每个城堡，都有其速率 $a_i$，我们不难想到可以贪心选择需求最少的兵力的城堡进行占领。

在占领的时候我们可以枚举每一种速率下超过对手兵力所需的回合。

设生产速率到达 $k$ 最少需要 $c$ 回合，占领后剩余兵力为 $b$，占领城堡后至少还需要 $n$ 回合才能超过对手兵力。

即可以得出以下式子：

$$kn+b\gt (c+n)y$$

移项后得到：

$$n \gt \frac{cy-b}{k-y}$$

由于 $n$ 需要取整，于是可以得出：

$$n \ge \lfloor \frac{cy-b}{k-y} \rfloor + 1$$

**PS：这里的式子必须要满足 $k-y\gt 0$。**

时间复杂度为 $O(n\log n)$。

## Code

[**Record**](/record/195706502)

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i,a,b) for(ll i = (a);i < (b);i++)
#define repr(i,a,b) for(ll i = (b) - 1;i>= (a);i--)
#define elif else if
#define Code_by_Kendieer return 0
typedef long long ll;
typedef unsigned long long ull;
const ll inf = 0x3f7f7f7f7f7f7f7f;

ll qread();
char readChar();
void qwrite(ll x,int t = 10);

const int maxn = 2e5 + 7;
const int mod = 998244353;
struct Node {};
int arr[maxn];
void solve(){
    int n = qread(), x = qread(),y = qread();
    rep(i,0,n){
        arr[i] = qread();
    }
    if (n + x <= y) {
        cout << "-1" << endl;
        return;
    } elif (x > y) {
        cout << 1 << endl;
        return;
    }
    sort(arr,arr+n);
    ll rnd = 0,res = 0,k = x,minStep = inf;
    int ptr = 0;
    rep(i,0,n){
        ll req = max(0LL,(arr[i] - res + k - 1) / k);
        res += req * k - arr[i] + k;
        k++,rnd += req + 1;
        if (k > y){
            ll r = (rnd * y - res) / (k-y) + 1;
            minStep = min(minStep,max(rnd,rnd+r));
        }
    }
    cout << minStep << endl;
    
}

int main(){
    // cin.tie(0),cout.tie(0);
    // ios::sync_with_stdio(0);
    int n = 1;
    n = qread();
    while(n--) solve();
    Code_by_Kendieer;
}

// =====================================================
ll qread(){
    ll r = 0,s = 1,ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    if (ch == '-') ch = getchar(),s = -1;
    while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0',ch = getchar();
    return r * s;
}
char readChar(){
    int ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    return ch;
}
void qwrite(ll x,int t){
    if (x<0) putchar('-'),x=-x;
    if (x>=t) qwrite(x/t,t);
    putchar(x%t<10?'0'+x%t:'A'-10+x%t);
}
// =====================================================
```

---

## 作者：_nothingGG (赞：0)

**一眼贪心题。**

### 注意到：

- 如果 $x>y$ 那么第一个回合就能超过。
  
- 如果 $x+n\le y$ 那么无论如何无法超过。
  
- 否则 $x+n>y$ 也就是说只要等待时间够长就能超过。
  

### 那么该按照什么顺序攻占城堡呢？

城堡（以下简称“塔”）的费用越小越好：从加兵力的角度看，塔的费用越小，那么你花费越小，并且你能更快地攒够兵力，也就更快地能让塔工作。

因此，可以将塔的花费按照从小到大排序，依次占领，只要能占就占。

attention：如果此时的 $x+k>y$ 了，也就是说可以现在就放弃继续开塔，直接蹲兵力，此时是可以直接算出还要多久才能超过对手的，所以要把这些满足 $x+k>y$ 的情况考虑进去，而不是开完所有塔才是最好的！

### 于是：上代码！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int cal(int x,int y){return (x+y-1)/y;}
signed main(){
	int T;cin>>T;
	while(T--){
        int n,x,y,a[N];
        cin>>n>>x>>y;
    	for(int i=1;i<=n;i++)cin>>a[i];
        if(x+n<=y){puts("-1");continue;}
        if(x>y){puts("1");continue;}
    	sort(a+1,a+n+1);
    	int rlt=0x3f3f3f3f,turns=0;
    	int me=0,other=0;
    	for(int i=1;i<=n;i++){
    		if(x>y)rlt=min(rlt,turns+cal(other-me+1,x-y));
    		int t=max(0ll,cal(a[i]-me,x));
    		turns+=t+1;
    		other+=(t+1)*y;
    		me+=(t+1)*x-a[i];
    		x++;
    	}
        rlt=min(rlt,turns+cal(other-me+1,x-y));
    	cout<<rlt<<endl;
    }
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

模拟题。

发现当我们占领 $n$ 个城堡后，日产士兵不会再变化了。

所以考虑当前有 $i$ 个城堡时，最少所需天数，根据贪心策略，显然先选 $a_i$ 小的城堡打。

剩下的直接模拟即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int N = 2e5 + 10;
const int inf = 1e16;

int n,x,y;
int a[N];

int cal (int x,int y){
	return (x + y - 1) / y;
}
void solve(){
	cin >> n >> x >> y;
	for (int i = 1 ; i <= n ; i++) cin >> a[i];
	sort (a + 1,a + n + 1);
	int ans = inf,now = 0;
	int sx = 0,sy = 0;
	for (int i = 1 ; i <= n ; i++){
		if (x > y){ // 有机会超过
			int day = cal(sy - sx + 1,x - y);
			ans = min(ans,now + day);
		} 
		int day2 = max(0ll,cal(a[i] - sx,x)); // 占领城堡还要多久
		now += day2 + 1;
		sy += (day2 + 1) * y; // 统计兵力
		sx += (day2 + 1) * x - a[i];
		x++;
	}
	if (x <= y) cout << "-1\n"; // 没有机会了
	else{
		ans = min(ans,now + cal(sy - sx + 1,x - y));
		cout << ans << endl;
	} 
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T; T = 1;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：linjunye (赞：0)

### 思路

题意简练，但思维难度却有些大。

先考虑一些分类讨论：

- $x>y$，那么第一回就超过了，答案为 $1$。

- $x+n\le y$，那么无论怎么占领，都超不过，答案为 $-1$。

- $x+n>y$，这个是重点要分析的。

我们根据最后一种情况进行思考。

首先先判断是否永远无法超过。

这个简单，因为无论要花多久，只要占领到了一定量，兵力总会慢慢比对手多，然后超过对手。

然后我们能发现一个贪心。因为每座城堡的贡献都是一样的，所以可以先攻打代价较小的城堡。

然后是重点代码，也是最难的地方，具体如下：

1. 算出满足下一个占领需求所需要的时间，记作 $nxt$，那么在 $t+nxt$ 回合的末尾，就满足了要求。

2. 统计一下在 $nxt$ 回合中的兵力变化。

3. 按照题目所述（或样例解释）来模拟下一个回合的具体购买信息。

4. $x\leftarrow x+1$，表示兵力加 $1$。然后若超过对手生产兵力，先别着急退出循环（可能多买几个更优），对答案产生贡献，然后继续循环。

可能不好理解，放一下核心代码：

```cpp
for(int i=1;i<=n;i++){
	int nxt=max(0ll,up(a[i]-aa,x));//达到下一个目标要在t+nxt回合后，up表示上取整
	t+=nxt;//t+nxt回合后
	aa+=nxt*x;
	bb+=nxt*y;
	t++;//计算下一个回合时的结果
	aa=aa-a[i]+x;//+x是因为还没到产生贡献的时候，详见样例解释
	bb=bb+y;//正常加
	x++;//兵力增加
	if(x>y)ans=min(ans,t+max(0ll,up((bb+1)-aa,x-y)));//超过对手生产兵力，计算还要多久才能超过对少的总兵力。注意是bb+1而不是bb
}
```

### 代码

~~都有核心代码了应该就不需要完整的吧……~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200010;
const int mod=1e9+7;
int n,x,y;
int a[N];
int up(int a,int b){//上取整模板
	return (a+b-1)/b;
}
void solve(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(x>y){//特判1
		cout<<"1\n";
		return;
	}
	if(x+n<=y){//特判2
		cout<<"-1\n";
		return;
	}
	sort(a+1,a+n+1);
	int t=0;
	int aa=0,bb=0;
	int ans=1e18;
	for(int i=1;i<=n;i++){
		int nxt=max(0ll,up(a[i]-aa,x));//达到下一个目标要在t+nxt回合后
		t+=nxt;//t+nxt回合后
		aa+=nxt*x;
		bb+=nxt*y;
		t++;//计算下一个回合时的差值
		aa=aa-a[i]+x;//还没到时候
		bb=bb+y;
		x++;
//		cout<<" "<<t<<" "<<aa<<" "<<bb<<"\n";
		if(x>y)ans=min(ans,t+max(0ll,up((bb+1)-aa,x-y)));
	}
	cout<<ans<<"\n";
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
//	T=1;
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

