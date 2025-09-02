# New Passenger Trams

## 题目描述

There are many freight trains departing from Kirnes planet every day. One day on that planet consists of $ h $ hours, and each hour consists of $ m $ minutes, where $ m $ is an even number. Currently, there are $ n $ freight trains, and they depart every day at the same time: $ i $ -th train departs at $ h_i $ hours and $ m_i $ minutes.

The government decided to add passenger trams as well: they plan to add a regular tram service with half-hour intervals. It means that the first tram of the day must depart at $ 0 $ hours and $ t $ minutes, where $ 0 \le t < {m \over 2} $ , the second tram departs $ m \over 2 $ minutes after the first one and so on. This schedule allows exactly two passenger trams per hour, which is a great improvement.

To allow passengers to board the tram safely, the tram must arrive $ k $ minutes before. During the time when passengers are boarding the tram, no freight train can depart from the planet. However, freight trains are allowed to depart at the very moment when the boarding starts, as well as at the moment when the passenger tram departs. Note that, if the first passenger tram departs at $ 0 $ hours and $ t $ minutes, where $ t <       k $ , then the freight trains can not depart during the last $ k       - t $ minutes of the day.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1379D/918cbdf79c8069ded989062dcac2b7f9f1eca401.png)A schematic picture of the correct way to run passenger trams. Here $ h=2 $ (therefore, the number of passenger trams is $ 2h=4 $ ), the number of freight trains is $ n=6 $ . The passenger trams are marked in red (note that the spaces between them are the same). The freight trains are marked in blue. Time segments of length $ k $ before each passenger tram are highlighted in red. Note that there are no freight trains inside these segments. Unfortunately, it might not be possible to satisfy the requirements of the government without canceling some of the freight trains. Please help the government find the optimal value of $ t $ to minimize the number of canceled freight trains in case all passenger trams depart according to schedule.

## 说明/提示

In the first test case of the example the first tram can depart at 0 hours and 0 minutes. Then the freight train at 16 hours and 0 minutes can depart at the same time as the passenger tram, and the freight train at 17 hours and 15 minutes can depart at the same time as the boarding starts for the upcoming passenger tram.

In the second test case of the example it is not possible to design the passenger tram schedule without cancelling any of the freight trains: if $ t \in [1, 15] $ , then the freight train at 16 hours and 0 minutes is not able to depart (since boarding time is 16 minutes). If $ t = 0 $ or $ t \in [16, 29] $ , then the freight train departing at 17 hours 15 minutes is not able to depart. However, if the second freight train is canceled, one can choose $ t = 0 $ . Another possible option is to cancel the first train and choose $ t = 13 $ .

## 样例 #1

### 输入

```
2 24 60 15
16 0
17 15```

### 输出

```
0 0```

## 样例 #2

### 输入

```
2 24 60 16
16 0
17 15```

### 输出

```
1 0
2```

# 题解

## 作者：zhimao (赞：8)

其实此题很简单，完全不需要动态开点线段树这种东西。

显然输入的与 $h$ 有关的东西都没用，我们只需要知道所有 train 的 $m_i$ 对 $\tfrac{m}{2}$ 取模的结果即可。则问题变为在时间 $0$ 到 $\tfrac{m}2-1$ 间（注意是个环）取一段长度为 m-k+1 的区间使区间内发车的 train 数量最多。 排序以后双指针即可，具体详见代码。

目前 codeforces 最快且最短(^_^)。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
struct arr
{
	int x,y;
	bool operator<(arr a) const
	{
		return x<a.x;
	}
}a[1000000];
int main()
{
	scanf("%d%*d%d%d",&n,&m,&k);
	m>>=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%*d%d",&a[i].x);
		a[i].x%=m;
		a[i].y=i;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) a[i+n]={a[i].x+m,a[i].y};
	for(int i=1;i<=n;i++) a[i+n+n]={a[i+n].x+m,a[i+n].y};
	int ans=0,l;
	for(int i=1,j=1;j<(n<<1);i++)
	{
		while(a[j+1].x<a[i].x+(m-k+1)&&j<(n<<1)) ++j;
		if(j-i+1>ans) l=i,ans=j-i+1;
	}
	printf("%d %d\n",n-ans,a[l].x);
	int i=l;
	for(;a[i].x<a[l].x+(m-k+1);i++);
	for(;i<l+n;i++) printf("%d ",a[i].y);
	return 0;
}
```


---

## 作者：feecle6418 (赞：6)

首先你要知道题目在说什么，因为它非常绕。具体来讲，train 随便发车，tram 隔半小时发一辆，给了 train，让你决定 tram 的发车时间。

我们看，每辆 train 会影响到哪些时候发车的 tram。首先，所有的时间都可以先对 $\dfrac{m}{2}$ 取模。然后再来看：在 $i$ 时刻发车，会影响 $(i,i+k)$ 即，$[i+1,i+k-1]$ 发车的 tram。假如它跨越了半小时，我们就拆成两段 $[i+1,\dfrac{m}{2}],[1,i+k-1-\dfrac{m}{2}]$。然后，用动态开点线段树处理每个点发车会影响多少次。

最后在线段树上 DFS 一次，找被影响次数最小的节点就是答案。

时间复杂度、空间复杂度是 $O(n\log m)$。

```cpp

/*
train随便发车
tram隔半小时发一辆
给了train
决定tram 
*/ 
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,k,h,a[200005],c[14000005][2],sum[14000005],tot,rt,minn=1e9,minp;
void Upd(ll &p,ll l,ll r,ll x,ll y){
	if(!p)p=++tot;
	if(x<=l&&r<=y){
		sum[p]++;
		return ;
	}
	ll mid=(l+r)/2;
	if(x<=mid)Upd(c[p][0],l,mid,x,y);
	if(mid<y)Upd(c[p][1],mid+1,r,x,y);
}
void dfs(ll p,ll l,ll r,ll ns){
	if(!p)return ;
	if(!(c[p][0]||c[p][1])){
		if(ns+sum[p]<minn)minn=ns+sum[p],minp=l;
		return ;
	}
	ll mid=(l+r)/2;
	if(c[p][0])dfs(c[p][0],l,mid,ns+sum[p]);
	else if(ns+sum[p]<minn)minn=ns+sum[p],minp=l;
	if(c[p][1])dfs(c[p][1],mid+1,r,ns+sum[p]);
	else if(ns+sum[p]<minn)minn=ns+sum[p],minp=mid+1;
}
int main(){
	cin>>n>>h>>m>>k;
	if(k==1)return cout<<"0 0"<<endl,0;
	for(int i=1;i<=n;i++){
		ll x,y;
		cin>>x>>y;
		a[i]=(x*m+y)%(m/2)+1;
		ll tmp=a[i]+1,tmp2=a[i]+k-1;
		if(tmp2<=m/2)Upd(rt,1,m/2,tmp,tmp2);
		else Upd(rt,1,m/2,tmp,m/2),Upd(rt,1,m/2,1,tmp2-m/2);
		//if(a[i]<k)a[i]+=h*m;
	}
	dfs(rt,1,m/2,0);
	cout<<minn<<' '<<minp-1<<endl;
	for(int i=1;i<=n;i++){
		ll tmp=minp+m/2-k+1,tmp2=minp-1;
		if(tmp-m/2>=1)tmp-=m/2;
		if(tmp2==0)tmp2=m/2;
	//	cout<<tmp<<' '<<tmp2<<' '<<a[i]<<endl;
		if(tmp<=tmp2){
			if(a[i]>=tmp&&a[i]<=tmp2)cout<<i<<' ';
		}
		else if(a[i]>=tmp||a[i]<=tmp2)cout<<i<<' ';
	}
} 
```

---

## 作者：jasonliujiahua (赞：1)

# [CF1379D](https://www.luogu.com.cn/problem/CF1379D)
## 1. 题目分析
### Step 1：题意转化
首先可以发现 $h$ 是诈骗的，和它没一点关系。因此考虑每个 $m_i$ 对 $t$ 的影响。分以下两种情况讨论：
- $m_i<\frac{M}{2}$，$t\in[m_i+k-\frac{M}{2},m_i]$
- $m_i>=\frac{M}{2}$，$t\in[m_i+k-M,m_i-\frac{M}{2}]$

考虑两个相邻电车之间长为 $\frac{M}{2}$ 的线段去套住 $m_i$ 限制的长为 $k$  的区间，即 $(m_i,m_i+k)\subseteq [t,t+\frac{M}{2}]$ 或 $(m_i,m_i+k)\subseteq [t-\frac{M}{2},t]$ 即可得出上面限制。此处注意如果左端点小于 $0$ 应拆为两个区间。

### Step 2：差分
此时一个 $m_i$ 已经确定了 $1$ 个或 $2$ 个区间，将这些区间在数轴上累加，即区间 $+1$，得到的最大值即为最多留下来的货车数。因为值域非常大，考虑进行离散化。问题变成了：区间加，查询最后整体最大值，差分即可。值得一提的是，一个 $m_i$ 拆成的两个区间一定不会相交，即 $m_i$ 最多会被统计一次，因此上述做法正确。证明如下：

不妨考虑 $m_i<\frac{M}{2}$ 的情况，第二种情况同理。此时两个区间为：$[0,m_i]$ 和 $[m_i+k,M-1]$ 由 $k>0$ 知 $m_i+k>m_i$，即不会相交。

以上过程可以画图理解。

## 2. 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10; 
int n,H,M,k,N,ans,cnt,h[maxn],m[maxn],l[maxn],r[maxn],b[maxn],lb,d[maxn],id[maxn],ok[maxn];
inline void add(int i,int x,int y)
{
	l[++cnt]=x;
	r[cnt]=y;
	id[cnt]=i;
} 
void init()
{
	scanf("%d%d%d%d",&n,&H,&M,&k);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d%d",&h[i],&m[i]);
		if(m[i]<M/2)
		{
			add(i,max(0,m[i]+k-M/2),m[i]);
			if(m[i]+k-M/2<0) add(i,m[i]+k-M/2+M/2,M-1);
		}
		else
		{
			add(i,max(0,m[i]+k-M),m[i]-M/2);
			if(m[i]+k-M<0) add(i,m[i]+k-M+M/2,M-1);
		}
	}
	for(int i=1;i<=cnt;i++) b[++lb]=l[i],b[++lb]=r[i];
	sort(b+1,b+lb+1);
	lb=unique(b+1,b+lb+1)-b-1;
	for(int i=1;i<=cnt;i++)
	{
		l[i]=lower_bound(b+1,b+lb+1,l[i])-b;
		r[i]=lower_bound(b+1,b+lb+1,r[i])-b;
	}
}
void work()
{
	N=cnt*2;
	for(int i=1;i<=cnt;i++) d[l[i]]++,d[r[i]+1]--;
	for(int i=1;i<=N;i++) d[i]+=d[i-1];
	for(int i=1;i<=N;i++)
		if(d[i]>d[ans]) ans=i;
	int tmp=(b[ans]<0)?b[ans]+M/2:b[ans];
	printf("%d %d\n",n-d[ans],tmp);
	for(int i=1;i<=cnt;i++)
		if(l[i]<=ans && ans<=r[i]) ok[id[i]]=1;
	for(int i=1;i<=n;i++) if(!ok[i]) printf("%d ",i);
}
int main()
{
	init();
	work();
	return 0;
}
```

---

