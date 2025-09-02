# Busy Robot

## 题目描述

### 题意翻译

你有一个机器人，初始位置（$0$ 秒），它在数轴上的位置为 $0$。它的速度是 $1$ 单位每秒。

它会接收 $n$ 个命令：在第 $t_i$ 秒移动到 $x_i$ 。在它移动的时候，会忽视你的所有命令。

定义第 $i$ 个命令是成功的，当且仅当在第 $[t_i,t_{i+1}]$ 秒内机器人到达过 $x_i$ 。（我们定义 $t_{n+1}$ 为正无穷）

你的任务就是求出有多少条命令是成功的。

## 样例 #1

### 输入

```
8
3
1 5
3 0
6 4
3
1 5
2 4
10 -5
5
2 -5
3 1
4 1
5 1
6 1
4
3 3
5 -3
9 2
12 0
8
1 1
2 -6
7 2
8 3
12 -9
14 2
18 -1
23 9
5
1 -4
4 -7
6 -1
7 -3
8 -7
2
1 2
2 -2
6
3 10
5 5
8 0
12 -4
14 -7
19 -5```

### 输出

```
1
2
0
2
1
1
0
2```

# 题解

## 作者：Eibon (赞：6)

这个方法挺好想，但有些笨拙。

考虑按照每个任务进行转移，写一个函数，记录当前是第几个任务，开始这个任务的位置在哪。

然后对接下来的任务跑循环。

如果接下来的任务的开始时间大于等于当前任务的开始时间加上移动到目标点时间之和 $need$ ,那么这个任务就是可以执行的。对于这个任务，需要判断一下，能否在规定时间 $t_{i+1}-t_{i}$ 内移动到目标点 $x_{i}$ 。如果可以那么 $ans$ 加一。

如果这个任务无法执行。对于这个任务，可以分为当前任务向左移、不动和想右移的三种情况。判断在规定时间 $t_{i+1}-t_{i}$ 内是否移动到目标点 $x_{i}$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int T,n,ans;
struct node
{
	int t,x;
};
node a[maxn];
void VIP(int num,int t,int x)//第几个任务，开始时间，初始位置
{
	for(int i=num+1;i<=n;i++){
		int need=abs(a[num].x-x);
		if(a[i].t>=t+need){
			int xx=abs(a[i].x-a[num].x);
			if(xx<=a[i+1].t-a[i].t){
				ans++;
			}
			VIP(i,a[i].t,a[num].x);
			return;
		}
		if(a[num].x<x){//向左移
			if(a[i].x<=x-min(need,(a[i].t-t))&&a[i].x>=x-min(need,(a[i+1].t-t))){
				ans++;
			}
		}
		if(a[num].x==x){//不动
			if(a[i].x==a[num].x&&need>=a[i].t){
				ans++;
			}
		}
		if(a[num].x>x){//向右
			if(a[i].x>=x+(a[i].t-t)&&a[i].x<=x+min(need,(a[i+1].t-t))){
				ans++;
			}
		}
	}
}
signed main()
{
	scanf("%lld",&T);
	while(T--){
		ans=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&a[i].t,&a[i].x);
		}
		a[n+1].t=1e18+5;
		VIP(0,0,0);
		printf("%lld\n",ans);
	}
	return 0;
}
//dyyyyds
```

---

## 作者：wz20201136 (赞：2)

小模拟。

维护当前的目的地，求出每个指令是否被忽略，进而求出每个 $t_i$ 的位置判断即可。

具体详见代码，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int T,n,wz[MAXN]/*ti是所处位置*/,t[MAXN],x[MAXN],g/*当前目标*/;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		g=0;
		for(int i=1;i<=n;i++) 
		{
			scanf("%d%d",&t[i],&x[i]);
			int now=wz[i-1];//上次的位置
			if(now==g||abs(g-now)<=t[i]-t[i-1]) wz[i]=g/*开始时停在上次目标位置*/,g=x[i]/*目标更新*/;//此次指令未被忽略
			else//此次指令被忽略
			{
				if(g>now) wz[i]=now+t[i]-t[i-1];//右移
				else wz[i]=now-t[i]+t[i-1];//左移
			}
		}
		wz[n+1]=g;//因为t_n+1无限大，所以一定能完成当前指令
		int ans=0;
		for(int i=1;i<=n;i++)
			ans+=(min(wz[i],wz[i+1])<=x[i]&&max(wz[i],wz[i+1])>=x[i]);//判断是否有效
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：naroanah (赞：0)

小模拟，动态更新当前正在执行的操作，判断指令是否被忽略。注意到对于 $[t_i, t_{i + 1}]$ 这个区间，执行的操作要么完全包含这个区间，要么在这个区间中结束。所以对于每一个区间，机器人走过的区间是容易计算的。

假设当前在执行的指令开始时间、结束时间、起始位置、方向分别是 $st,ed, from, d$，那么对于 $t \in [st,ed]$，机器人位置为 $from + (t - st) * d$，代入 $t_i, t_{i + 1}$ 计算，检查 $x_i$ 是否在这个区间内即可。注意特判 $t_{i + 1}$ 超过 $ed$ 的情况。

```cpp
int n;
pair<ll, ll> a[N], b[N];
void solve() {
    cin >> n; rep(i, 1, n) cin >> a[i].fi >> a[i].se;
    ll ed = 0, from, to = 0, d, st;
    rep(i, 1, n) {
        if(ed <= a[i].fi) {
            from = to, to = a[i].se; ed = a[i].fi + abs(from - to), st = a[i].fi;
            d = to - from > 0 ? 1 : -1;
        }
        b[i].fi = from + d * (a[i].fi - st);
        if(i < n) b[i].se = a[i + 1].fi > ed ? to : from + d * (a[i + 1].fi - st);
        else b[i].se = to;
        if(b[i].fi > b[i].se) swap(b[i].fi, b[i].se);
    }
    int ans = 0;
    rep(i, 1, n) if(b[i].fi <= a[i].se && a[i].se <= b[i].se) ans++;
    cout << ans << "\n";
}
```

---

