# Old Peykan

## 题目描述

There are $ n $ cities in the country where the Old Peykan lives. These cities are located on a straight line, we'll denote them from left to right as $ c_{1},c_{2},...,c_{n} $ . The Old Peykan wants to travel from city $ c_{1} $ to $ c_{n} $ using roads. There are $ (n-1) $ one way roads, the $ i $ -th road goes from city $ c_{i} $ to city $ c_{i+1} $ and is $ d_{i} $ kilometers long.

The Old Peykan travels 1 kilometer in 1 hour and consumes 1 liter of fuel during this time.

Each city $ c_{i} $ (except for the last city $ c_{n} $ ) has a supply of $ s_{i} $ liters of fuel which immediately transfers to the Old Peykan if it passes the city or stays in it. This supply refreshes instantly $ k $ hours after it transfers. The Old Peykan can stay in a city for a while and fill its fuel tank many times.

Initially (at time zero) the Old Peykan is at city $ c_{1} $ and $ s_{1} $ liters of fuel is transferred to it's empty tank from $ c_{1} $ 's supply. The Old Peykan's fuel tank capacity is unlimited. Old Peykan can not continue its travel if its tank is emptied strictly between two cities.

Find the minimum time the Old Peykan needs to reach city $ c_{n} $ .

## 说明/提示

In the second sample above, the Old Peykan stays in $ c_{1} $ for 3 hours.

## 样例 #1

### 输入

```
4 6
1 2 5 2
2 3 3 4
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2 3
5 6
5 5
```

### 输出

```
14
```

# 题解

## 作者：Sincerin (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF241A)

## 题意
有 $n$ 个城市，$n-1$ 条单向路 (下文用 $m$ 代替)，第 $i$ 条路连接城市 $i$  和 $i+1$，长度为 $d_i$ 。每个城市 ( 除了第 $n$ 个 ) 都有加油站，每到一个城市就会自动加$s_i$ 升油，每加一次油需要 $k$ 小时。有一辆车，$1$ 小时走 $1$ 千米,要用 $1$ 升油，油箱容量无限，从 $1$ 号城市到 $n$ 号，至少要多长时间？

$1≤m,k≤10^3$ ,
$1≤d_i,s_i≤10^3$

## 思路

- 很水的绿题，可以直接打模拟，但是题目中的 **至少** 二字，说明我们要找的答案一定要为最短，这就涉及到了我们接下来要介绍的贪心思想 （大佬请自行跳过）。

- 首先看看两个样例：

1. 在样例一中，不存在二次加油的情况。

1. 在样例二中，每个加油站提供的油一样多。

在这种情况下，我们没有办法看出贪心的思想体现在哪里，所以可以自己造一下数据：

```c
  4 3
  2 5 7 4
  3 2 1 4

```
- 这时如果在第 $i$ 个城市时油不够了，我们选择在第 $i$ 个加油站加油的话，答案应该为 $39$ 小时。但是很显然，同样花费 $3$ 小时，在第一个城市的加油站，一次就可以加油 $3$ 升。所以我们可以在第一个城市多加一些油，以应对后面油不够的情况，这样时间就可以缩短到 $27$ 小时。

- 在代码实现中，我们只需要在每次选择的时候选择已经经过的加油站中 $s_i$ 值最大的，并多停留一段时间即可，我们就用一个新变量 $max$ 来动态更替这个最大值。~~（当然，我们要假设这辆车上有导航，可以预测接下来的路程）~~。 

-  综上所述，本题的贪心思想实现主要通过在供油量较多的加油站加油，从而让时间尽可能的缩短。


----
(不说废话，贴代码！)

## AC Code
```cpp
#include <cstdio>
#include <iostream> 
#include <algorithm> 
using namespace std;
int n,m,k,s[1005],d[1005],oil;// oil 记录剩余油量 
long long ans;//记录花费时间 
int main()
{
  	scanf("%d",&m); //城市个数 
	scanf("%d",&k); //加油(等待)时间 
	for(int i=1;i<=m;i++) scanf("%d",&d[i]); //路的长度(每公里一升油) 
	for(int i=1;i<=m;i++) scanf("%d",&s[i]); //每个加油站的供油量(升/次) 
	for(int i=1;i<=m;i++)
	{
		oil+=s[i]; //第一次(免费)加油 
		if(oil<d[i])//不够 
		{ 
			while(oil<d[i])//补油 
			{
				oil+=s[i];
				ans+=k;
			}
			oil-=d[i];
			ans+=d[i];
		}
		else//够 
		{
			oil-=d[i];
			ans+=d[i];
		}
	}
	printf("%lld",ans);
	putchar('\n'); 
  	return 0;//完结撒花 
}
```
这份代码最优解第三哦，如果看到这里我也不要脸地求个赞吧。

----



---

## 作者：Stephen_Curry (赞：3)

这道恶评题居然没有题解？赶紧自己发一发……

**评分建议：红**

~~一开始看题面还以为是最短路，琢磨了半天发现是模拟+贪心……~~

我们可以结合样例来分析：（此段可跳过，可直接从下一分割线处开始观赏）

样例一：

![](https://cdn.luogu.com.cn/upload/image_hosting/unkxc3pw.png)

共花费$10$小时。

此时，我们可以手造一组极端数据：

```cpp
m = 2, k = 3

d = {1, 4}

s = {2, 1}
```

此时，常规思路应为：开始$1$号城自动加的$2$升油够到$2$号城了，还剩$2-1=1$升油；自动加$1$升油后$2$升油不够到下一城，即在此地停留$3*2=6$小时后油量够了，到达下一城，共花费$1+6+4=11$小时。

这是最优解吗？不是！正确答案其实是$8$小时！

我们可以在$1$号城时就停留$3$小时，这时到达$2$号城后就有了$2+2-1+1=4$升油，够到终点站了，共花费$3+1+4=8$小时，小于常规思路的$11$小时！

------------

显然，要想时间短，就应该在油量较多的地方加油 ~~（废话）~~，所以，此时我们可以这样想：

假设一路顺风，直接利用到达一地自动加的油就到终点了（样例一），这样当然最好；否则，在路途中必然会出现断油的情况，在这种情况下，我们应当选择所有已经经过的城市中油量最多的地方应当多停一段时间加油（手造数据）。所以，我们应当先进行初始化：

```cpp
for (int i = 1; i <= m; i++) ma[i] = max(ma[i - 1], s[i]);
```

$ma_i$代表第$i$城及之前经过的所有城市中油量最多的城市所储存的油量，显然，它必然为第$i-1$座城市及之前最多的油量与第$i$座城市油量中较大数，也就有了以上代码。

此时，我们完成了初始化，随后便是统计答案的时候了。

显然，之前手造数据时我们发现在断油情况下应当选择已过的城市中油量最多的城市加油，此时可以换一种角度思考：

当走到断油的地方时，我们可以假设这辆老爷车有时光倒流的超能力，能够~~穿越时空，重临过去~~，回到之前油量最多的城市，到那里去加油，直到够到达下一座城市为止。

此时因先前已经初始化过$ma_i$，故直接将当前油量加上$ma_i$，同时答案加上$k$即可。

这时候要注意，由于可能要加多次油才能满足需求，故应重复执行直到$d_i$不大于当前油量时为止。

```cpp
//ans表示至少需要的时间（即答案）
//now表示当前油量
while (d[i] > now) {
    ans += k;
    now += ma[i];
}
```

循环结束后，当前油量还需减去途中消耗的油量（即$d_i$），答案应加上路程（亦为$d_i$）即可。
最后贴上全代码（最优解第二位，欢迎打破~）

```cpp
#include <bits/stdc++.h>
using namespace std;
int m, k, d[1050], s[1050], ans, now, ma[1050];
int main() {
    cin >> m >> k;
    for (int i = 1; i <= m; i++) scanf("%d", &d[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &s[i]);
    for (int i = 1; i <= m; i++) ma[i] = max(ma[i - 1], s[i]);
    for (int i = 1; i <= m; i++) {
        now += s[i];
        while (d[i] > now) ans += k, now += ma[i];
        now -= d[i]; ans += d[i];
    } cout << ans;
}
```


---

## 作者：Kissky (赞：2)

## 分析：

首先我们假设我们走到了第i个城市，加上第i个城市的油之后我们发现我们的油不支持我们到达下一个城市，这时候我们就要额外的进加油了！那么怎么加油是最优的呢？我们根据贪心的策略，在一定的时间内当然是加的油越多越好啊！所以我们要知道在1-i中所有的城市里，在哪里加油可以在一定的时间内加最多。

## My code：
```cpp 
#include<iostream>
#include<algorithm>
using namespace std;
int m,k,d[1000100],s[1000010],ma,ans,v;
int main()
{
	cin>>m>>k; 
   	for(int i=1;i<=m;i++) cin>>d[i]; 
    for(int i=1;i<=m;i++) cin>>s[i];
	for(int i=1;i<=m;i++)
	{
		ma=max(s[i],ma);//求1到i中那个城市加的油量最大 
		v+=s[i];//到达第i个城市自动加油！ 
		if(v>=d[i]) v-=d[i],ans+=d[i];//如果我们的油支持我们到达下一个城市直接走 
		else //不支持就额外加油 
		{
			while(v<d[i]) ans+=k,v+=ma;//开始加油 
			v-=d[i],ans+=d[i];//注意！加油完再走到第i+1个城市！ 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Dreamerly (赞：0)

## 题目：[CF241A](https://www.luogu.com.cn/problem/CF241A)
## 思路：
看完数据规模，可以模拟。因此我们先按照题意来。

当每站自动加的油够的时候就走；但如果油不够，我们就需考虑加油。想到这里，我们就需用到贪心思路。

由于每站加油的时间都是一样的，而加油量不同，**那最优思路肯定是加最多的油**。也就是说，
当我们在第 $i$ 站且油不够时，我们可以看作 $0$ 距离瞬移到 $1$ $-$ $i$ 站，去加最多的油，直到够为止（即我们未卜先知，提前在 $1$ $-$ $i$ 中某一站加好了油）。
## 代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){ 
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar(); 
	}
	return num*sign;
} 
void write(int x){ 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
const int N=1001;
int d[N],s[N],pre[N],ans,now;
signed main(){ 
       int m=read(),k=read();
	for(int i=1;i<=m;i++) d[i]=read();
	for(int i=1;i<=m;i++) s[i]=read(),pre[i]=max(pre[i-1],s[i]);//前缀算出1-i站中能加最多的油的体积
	for(int i=1;i<=m;i++){
		now+=s[i];
		if(now>=d[i]){//如果此时的油够开到下一处 
			now-=d[i];
			ans+=d[i];
		}
		else{
			while(now<d[i]){
				ans+=k; 
				now+=pre[i];//贪心思路，前面的加油站看作是0距离瞬移，只要加到最多的油就行 
			}
			now-=d[i]; 
			ans+=d[i];
		}
	}
	write(ans);
	return 0; 
} 
```


---

## 作者：Creative_sad_yosgic (赞：0)

## CF241Aの题解
### 题意
行到第 $i$ 座城市，耗费 $d(i)$ 升油，同时每个城市有能加 $s(i)$ 升油的加油站，每一次到城市也会加 $s(i)$ 升油。

分析题意模拟可得，在油量充足时，油量减去 $d(i)$ ,时间加上 $d(i)$，但是，如果油量不足怎么办呢？

因为每座城市**所需加油时间**相等，所以你在你**行驶到的任何一个城市加油时间相同**，所以运用**贪心**思路，假设这辆车~~可以时间回溯~~，到当前**油量最多**的城市加油即可。



### 模拟代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,k;
int d[114514],s[114514],linshi[114514];
int ans,bns;//油 时
bool flag;int maxx;
bool cmp(int x,int y)
{
	return x>y;
}//从大到小排序
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);//优化
	cin>>m>>k;
	for(int i=1;i<=m;i++)
		cin>>d[i];
	for(int i=1;i<=m;i++)
		cin>>s[i];
	for(int i=1;i<=m;i++)
	{
		ans+=s[i];//到城市自动加油
		if(ans>=d[i]) ans-=d[i],bns+=d[i];//如果油还够直接耗油并累加时间
		else{
			flag=0;
			maxx=0;
			memset(linshi,0,sizeof(linshi));//毫无用处的初始化（）
			for(int j=1;j<=i;j++) linshi[j]=s[j];
			while(ans<d[i]) {
				if(!flag){sort(linshi+1,linshi+i+1,cmp);flag=1;maxx=linshi[1];}//不够就寻找油最多的城市
			     ans+=maxx;//加油
				 bns+=k;//加时
			}
			bns+=d[i];//减油 时
			ans-=d[i];
		}
	}
	cout<<bns;return 0;
}
```


---

