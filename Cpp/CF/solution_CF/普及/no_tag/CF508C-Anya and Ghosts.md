# Anya and Ghosts

## 题目描述

Anya loves to watch horror movies. In the best traditions of horror, she will be visited by $ m $ ghosts tonight. Anya has lots of candles prepared for the visits, each candle can produce light for exactly $ t $ seconds. It takes the girl one second to light one candle. More formally, Anya can spend one second to light one candle, then this candle burns for exactly $ t $ seconds and then goes out and can no longer be used.

For each of the $ m $ ghosts Anya knows the time at which it comes: the $ i $ -th visit will happen $ w_{i} $ seconds after midnight, all $ w_{i} $ 's are distinct. Each visit lasts exactly one second.

What is the minimum number of candles Anya should use so that during each visit, at least $ r $ candles are burning? Anya can start to light a candle at any time that is integer number of seconds from midnight, possibly, at the time before midnight. That means, she can start to light a candle integer number of seconds before midnight or integer number of seconds after a midnight, or in other words in any integer moment of time.

## 说明/提示

Anya can start lighting a candle in the same second with ghost visit. But this candle isn't counted as burning at this visit.

It takes exactly one second to light up a candle and only after that second this candle is considered burning; it means that if Anya starts lighting candle at moment x, candle is buring from second x + 1 to second x + t inclusively.

In the first sample test three candles are enough. For example, Anya can start lighting them at the $ 3 $ -rd, $ 5 $ -th and $ 7 $ -th seconds after the midnight.

In the second sample test one candle is enough. For example, Anya can start lighting it one second before the midnight.

In the third sample test the answer is $ -1 $ , since during each second at most one candle can burn but Anya needs three candles to light up the room at the moment when the ghost comes.

## 样例 #1

### 输入

```
1 8 3
10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 10 1
5 8
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1 1 3
10
```

### 输出

```
-1
```

# 题解

## 作者：liuzhongrui (赞：2)

## 思路

我们先来判断输出 ```-1``` 的情况，题目中说到每根蜡烛可以燃烧 $t$ 秒，鬼魂来时最少要有 $r$ 跟蜡烛被点燃，而每根蜡烛被点燃需要 $1$ 秒钟的时间，很容易发现，当 $t<r$ 时，即每根蜡烛燃烧时间小于最少要被点燃的蜡烛数时，不可能存在最少要有 $r$ 跟蜡烛被点燃这个条件，证明也很简单，由于每根蜡烛被点燃需要 $1$ 秒钟的时间，因此点燃 $r$ 根蜡烛至少需要 $r$ 秒，当 $t<r$ 时总会存在有蜡烛撑不到 $r$ 秒。这种情况输出 ```-1``` 即可。

接下来的情况都是合法的了。我们逐个读入每个鬼魂的到达时间 $w_i$。在每次读入一个到达时间后，检查之前点燃的蜡烛是否可以覆盖当前鬼魂的到达时间。如果无法覆盖，则点燃足够的新蜡烛以覆盖到达时间。在这个过程中，记录了点燃的蜡烛总数，最后输出点燃蜡烛的总数即可。

## Code

十分简短。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010];
int m,t,r;
int main() {
	scanf("%d%d%d",&m,&t,&r);
	if(t<r) {
		puts("-1");
		return 0;
	}
	int st=0,ed=0,ans=0;;
	while(m--) {
		int w;
		scanf("%d",&w);
		while(st<ed&&a[st]<w) st++;
		for(int i=w-r+ed-st; i<w; i++){
			a[ed++]=i+t;
			ans++;
		} 
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：wxw_zl (赞：1)

## 题意简述：

数轴上有 $m$ 个点，每个点的坐标各不相同，需要用线段覆盖上面的所有点，每条线段的长度为 $t$, 每条线段的左端点前面需要空出长度为 $1$ 的距离，线段的左端点的横坐标可以在  $x$ 轴负半轴上。

## 思路：

第一反应是二分答案，在想 check 的时候发现，二分是不必要的，可以直接按照需求点燃蜡烛。需要注意的是，如果按照鬼魂出现的时间顺序，从前往后贪心地点蜡烛会假，因为点燃的蜡烛的位置会影响到后面的蜡烛，所以我们可以从后往前处理。贪心时，我们尽量往前点蜡烛，因为这样可以对前面的鬼魂提供最大的贡献（应该很容易懂），代码中有解释。

## 细节：

题意是可以在午夜之前点燃蜡烛的，为了处理负数的情况，把数组开两倍即可，然后加 $300$ 的偏移量。

## 代码：

```cpp
#include<bits/stdc++.h>
#define rise(i,l,r) for(int (i)=(l);(i)<=(r);(i)++)
#define fall(i,r,l) for(int (i)=(r);(i)>=(l);(i)--)
using namespace std;
const int maxn=305;
int m,t,r,w[maxn],tim[maxn<<1];
void in() {
	cin>>m>>t>>r;
	rise(i,1,m) {
		cin>>w[i];
		w[i]+=300;
	}
	sort(w+1,w+1+m);
}
int solve() {
	fall(i,m,1) {
		int k=max(w[i]-t,0),burning=0;
//		k表示对当前鬼魂有贡献的最早点燃时间，burning表示在[k,w[i])区间内已经点燃的蜡烛数量 
		fall(j,w[i]-1,k)burning+=tim[j];//统计在处理后面的蜡烛时已经点燃的蜡烛数量 
		rise(j,k,w[i]-1) {//贪心点燃蜡烛，在[k,w[i])这个区间中，任意一蜡烛均可对i号鬼魂做出贡献，易证明，越早点燃蜡烛是越有利于前面的 
			if(burning>=r)break;
			if(tim[j])continue;
			tim[j]=1;
			burning++;
		}
		if(burning<r)return -1;
	}
	int res=0;
	rise(i,1,w[m])res+=tim[i];
	return res;
}
int main() {
	ios::sync_with_stdio(false);
	in();
	cout<<solve();
	return 0;
}
```

---

## 作者：Rex01 (赞：0)

## [CF508C 题目传送门](/problem/CF508C)

## 题目大意
夜市中管理方会在午夜后进行 $m$ 次检查，第 $i$ 次检查在午夜后的第 $w_i$ 秒进行，每次检查持续 $1$ 秒钟，要求每次检查夜市里至少有 $r$ 根蜡烛在燃烧。已知每根蜡烛能燃烧 $t$ 秒，点燃一根蜡烛需要 $1$ 秒。你的任务是要使每次检查都合格，最少需要多少根蜡烛。

## 解决思路
首先考虑特殊情况，即输出 $-1$。如果每根蜡烛燃烧的时间小于最小的蜡烛根数（$t < r$），即不满足要求，则直接输出 $-1$。每次鬼魂到达时，检查之前点燃的蜡烛是否还能覆盖当前时间。如果不能，就点燃新蜡烛。最后输出总共点燃的蜡烛数量。

## 代码展示
```cpp
#include <iostream>
using namespace std;
 
int m, t, r, w, a[1010];
//a[]表示燃烧的蜡烛的结束时间 
int x, y, ans;
//x表示燃烧的蜡烛的起始下标 
//y表示下一个要被点燃的蜡烛下标

int main() 
{
	cin >> m >> t >> r;
	if(t < r) 
	{//如果每根蜡烛燃烧的时间小于最小的蜡烛根数，
		puts("-1");//即不满足情况，则直接输出-1
		return 0;
	}
	for(int i = 1; i <= m; i++)
	{
		cin >> w;
		while(x < y && a[x] < w) x++;
		for(int j = w - r + y - x; j < w;j++)
		{
			a[y++] = j + t;
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：L_shadow (赞：0)

## 思路：
挨个尝试在每一个时间点不点蜡烛，如果不点蜡烛仍然合法，那么这个时间点就不点蜡烛。否则点蜡烛。

细节：遍历每一个时间点时，应从后往前遍历。因为后面的决策影响不到前面是否合法，但是前面的决策会影响后面的决策。

## code：
```
#include<bits/stdc++.h>
using namespace std;
int m,t,r,a[305],ans=605;
bool vis[610];
bool check() {
	for(int i=1; i<=m; i++) {
		int cnt=0;
		for(int j=a[i]-t; j<a[i]; j++) cnt+=vis[j];
		if(cnt<r) return 0;
	}
	return 1;
}
int main() {
	scanf("%d%d%d",&m,&t,&r);
	for(int i=1; i<=m; i++) {
		scanf("%d",&a[i]);
		a[i]+=300;
	}
	for(int i=0; i<=605; i++) vis[i]=1;//全点上蜡烛 
	if(!check()) {//即便全点上蜡烛也不合法 
		printf("-1");
		return 0;
	}
	for(int i=604; i>=0; i--) {
		vis[i]=0;//决策 
		if(!check()) vis[i]=1;
		ans-=(1-vis[i]);
	}
	printf("%d",ans);
}
```

---

