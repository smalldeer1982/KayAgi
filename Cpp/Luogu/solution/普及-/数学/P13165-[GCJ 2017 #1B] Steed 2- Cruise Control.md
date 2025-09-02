# [GCJ 2017 #1B] Steed 2: Cruise Control

## 题目描述

Annie 是一名公交车司机，工作压力很大。她曾尝试通过加勒比海邮轮来放松自己，但那次旅行同样让她感到压力重重，于是她最近开始学习骑马。

今天，Annie 正骑着她的马沿着一条狭长的单向公路向东行进。她现在位于公路的 $0$ 公里处，目的地在 $D$ 公里处；公路上的公里数从西到东依次编号。

在这条路上，还有 $N$ 匹其他马同样向东行进；它们都会一直前进下去，并且目前都位于 Annie 的马和她的目的地之间。第 $i$ 匹马当前位于 $K_i$ 公里处，并以其最大速度 $S_i$ 公里每小时行进。

马非常有礼貌，一匹马 $H_1$ 不会超过（即不会跑到前面去）另一匹起始位置在 $H_1$ 前面的马 $H_2$。（多匹马可以在任意时刻处于同一位置；你可以将马视为一个点。）除 Annie 的马以外，其他马都以最大速度行进，除非某匹马 $H_1$ 追上了另一匹更慢的马 $H_2$，此时 $H_1$ 会减速至 $H_2$ 的速度。

而 Annie 的马没有最大速度限制，她可以选择任意速度，只要不超过其他马。为了让自己和马都能顺利前行，Annie 想为她的马选择一个全程恒定的“巡航速度”，使得她的马在从当前位置到目的地的整个过程中都不会超过其他马。请问她能选择的最大速度是多少？

## 说明/提示

**样例解释**

在样例 1 中，只有一匹（非常慢的）马在路上；它到达 Annie 目的地需要 $25$ 小时。Annie 选择的速度只要不超过 $101$ 公里每小时，就不会在到达目的地前超过这匹马。

在样例 2 中，有两匹马在路上。较快的马会在 $2$ 小时后于 $240$ 公里处追上较慢的马。此后，两匹马会以较慢马的速度再行进 $1$ 小时，直到到达 $300$ 公里处的目的地。Annie 能选择的最大速度是 $100$ 公里每小时。

**数据范围**

- $1 \leq T \leq 100$。
- $0 < K_i < D \leq 10^9$，对所有 $i$。
- $K_i \neq K_j$，对所有 $i \neq j$。（没有两匹马起始位置相同。）
- $1 \leq S_i \leq 10000$。

**小数据范围（11 分，测试点 1 - 可见）**

- $1 \leq N \leq 2$。

**大数据范围（14 分，测试点 2 - 隐藏）**

- $1 \leq N \leq 1000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2525 1
2400 5
300 2
120 60
60 90
100 2
80 100
70 10```

### 输出

```
Case #1: 101.000000
Case #2: 100.000000
Case #3: 33.333333```

# 题解

## 作者：__F__ (赞：6)

## 题目大意  
一共有 $T$ 组数据，每组数据有两个整数 $D$ 和 $N$。$N$ 代表马的数量。之后给出 $N$ 条马目前所处的位置和它的速度，问 Annie 的马在不超过其他马的前提下，最大速度是多少。  
## 思路分析  
题目中说 Annie 和其他 $N$ 匹马都沿着一条单向公路向东行进。我们可以把这条单项公路看作一个数轴，Annie 最开始时位于数轴的起点，也就是 $0$ 位置。输入的 $D$ 表示所有马的目的地，也就是 Annie 的终点。题目中说所有马都不会超过它前面那条马，如果追上了就会将自己的速度减至更慢的那匹马的速度。所以 Annie 既然不想超过其他的马，就一定会受最慢的那匹马的限制，那我们就需要找出最慢的那匹马的速度。这匹马既然速度最慢，那如果没有不能超过其他马的限制，它所花费的时间肯定是最多的。所以我们可以求出本来每匹马所需要花费的时间，找到最大值，最后用总路程除以时间即可。  
## 代码实现  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
double T,d,n,k[N],s[N],t[N], maxn;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	std::cin>>T;
	for(int i=1;i<=T;i++){
		std::cin>>d>>n;
		maxn=-100;
		memset(t,0,sizeof(t));//多测不清空，爆零两行泪 
		for(int j=1;j<=n;j++){
			std::cin>>k[j]>>s[j];
			t[j]=(d-k[j])/s[j];//求出花费的时间 
			maxn=max(maxn,t[j]);//找最大值 
		}
		std::cout<<"Case #"<<i<<": ";
		std::cout << fixed <<setprecision(6) << double(d)/maxn <<"\n";//求出速度 
	}
		return 0;
} 
```

---

## 作者：Hkb150429 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13165)

## 题意

Annie 的马位于公路的 $0$ 公里处，目的地在 $D$ 公里处；

在这条路上，还有 $N$ 匹其他马同样向东行进；它们都会一直前进下去，并且目前都位于 Annie 的马和她的目的地之间。第 $i$ 匹马当前位于离 Annie 的马的起点 $K_i$ 公里处，并以 $S_i$ 公里每小时行进。

并且，一匹马 $H_1$ 不会超过另一匹起始位置在 $H_1$ 前面的马 $H_2$。除 Annie 的马以外，其他马都以最大速度行进，除非某匹马 $H_1$ 追上了另一匹更慢的马 $H_2$，此时 $H_1$ 会减速至 $H_2$ 的速度，所以 $H_1$ 的时间就是时间是 $H_2$ 的时间。

## 思路

我们可以求出每匹马 $H_i$ 从它们的起点至终点所用的时间 $T_i$，把它们与 Annie 的马的时间取最大值 $mt$，就可以算出来 Annie 的马最短行走时间。因为我们知道**路程除以速度等于时间**，所以我们就可以知道 Annie 的马的最大恒定速度，输出 $mt$ 就可以了。

## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
long long d;
int n;
long long k[1005];
long long s[1005];
int main(){
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        scanf("%lld%d",&d,&n);
        for(int j=1;j<=n;j++){
            scanf("%lld%lld",&k[j],&s[j]);
        }
        double mt=0;
        for(int j=1;j<=n;j++){
            double t=double(d-k[j])/s[j]*1.000000;
            if(t>mt) mt=t;
        }
        double v=1.000000*d/mt;
        printf("Case #%d: %.6f\n",i,v);
    }
    return 0;
}

```

---

## 作者：Natural_Selection (赞：1)

# 题解：[P13165](https://www.luogu.com.cn/problem/P13165)

## 思路

题面看似很长，但实际上最关键的就一句话：

**某匹马 $H_1$ 追上了另一匹更慢的马 $H_2$，此时 $H_1$ 会减速至 $H_2$ 的速度。**

那我们找最慢的马就行了呀。

## [AC](https://www.luogu.com.cn/record/223381802) Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int o;
struct horse{ //马
    int k,s;
};
int main(){
    int t;
    cin>>t;
    while(t--){
        int d,n;
        cin>>d>>n;
        horse a[n+2];
        double max_s=0.00;
        for(int i=0;i<n;i++){//找最慢的马跑完时所用的时间
            cin>>a[i].k>>a[i].s;
            max_s=max(max_s,(d-a[i].k)/double(a[i].s));
        }
        //以最慢的马跑完时所用的时间为基准设定速度。
        printf("Case #%d: %.6lf\n",++o,double(d/max_s));
    }
    return 0;  //完成！(～￣▽￣)～ 
}
```

---

## 作者：kobebraint (赞：1)

## 看题

A 一串字母这人要骑马从 $0$ 公里跑到 $D$ 公里，她前面还有很多速度不一的马，A 一串字母必须匀速到达终点，不能超过任何一匹前方的马。

怎么保证不会超过呢？**我们要让 A 一串字母到达终点的时间 ≥ 前面的所有马到达终点的时间中的最大值**。

如果 A 一串字母比其它马提前到了终点，那就说明她在中途超过了某匹更慢的马。

## 怎么做？

A 一串字母前面的每匹马从自己当前位置 $K_i$ 以最大速度 $S_i$ 跑到终点 $D$，需要的时间是 $(D - K_i) / S_i$。

这些马都会按自己的速度走，谁追上别人就降速，但是不用考虑减速的情况，你可以理解为追上前面的马和被追的马是一只马，会同时到达终点，所以只要知道每匹马自己单独跑到终点要多久就够了。设 $t_i$ 为其他马到达终点的时间，那么 A 一串字母的最大合法速度为 $D \div \max_{t_i}$，能保证她在最长的那个时间内刚好到达终点，不超过任何马。

## 上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define dot(x) fixed<<setprecision(x)
#define foru(a,b,c) for(ll a=b;a<=c;a++)

ll t,n,m,T,d;

int main(){
    cin>>t;
    T=t;
    while(t--){
        cin>>d>>n;
        ld maxx=0;
        foru(i,0,n-1){
            ld k,s;
            cin>>k>>s;
            maxx=max(maxx,(d-k)/s);
        }
        cout<<dot(6)<<"Case #"<<T-t<<": "<<d/maxx<<endl;
    }
    return 0;
}
```

---

## 作者：goIdie (赞：0)

## 思路

一个比较考察思维的题吧。

因为 Annie 的马不能超过其他的马，所以 Annie 的马必须在最后到达终点。那么为了让 Annie 的马速度最快，就要让 Annie 的马和除 Annie 的马以外的马中到达终点最慢的马同时到达终点。这样就能在保证不超过其他的马的同时使马的速度最快。

代码实现较为简单，第 $i$ 匹马到达终点的时间为 $\frac{D-K_i}{S_i}$，我们找出最大的到达时间 $maxn$，那么答案即为 $\frac{D}{maxn}$，保留六位小数输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,d,n,k[1001],s[1001];
double maxn;
int main() {
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>d>>n;
        maxn=0.0;
        for(int i=1;i<=n;i++){
            cin>>k[i]>>s[i];
            maxn=max(double(d-k[i])/s[i],maxn);
        }
        cout<<"Case #"<<t<<": "<<fixed<<setprecision(6)<<d/maxn<<endl;
    }
    return 0;
}
```

---

## 作者：_ByTT_ (赞：0)

# 题解：P13165 [GCJ 2017 #1B] Steed 2: Cruise Control
### 题意
Annie 从公路的起点出发，它前面有 $N$ 匹马，所有马，包括 Annie 的马，都要去往距公路 $D$ 公里的地方。马不会超过任何起点比他们远的马，如果速度比前面的马快，它们就会和他们前面的马重合。

求 Annie 的马最快的巡航速度是多少。巡航速度指到达终点前全程不会变化的速度。
### 思路
刚开始可能会想到用 Annie 的马去对比每一个马，然后求最大巡航速度。但是 $O(T \times N^2)$ 的时间复杂度是一亿左右，常数大一点就会被卡掉。

但是巡航速度是不会变的，所以我们只需要找到花费时间最长的那匹马，并和它同时到达终点即可。因为每一匹马的起点都比 Annie 的马远，所以无需害怕会出现答案错误的情况。

代码很好写。请注意输出格式。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct Node{
	int s,k;
	double sj;
}a[10005];
bool bmp(Node a,Node b){
	return a.k<b.k;
}
signed main(){
	int T;cin>>T;
	for(int x=1;x<=T;x++){
		memset(a,0,sizeof(a));
		int n,d;cin>>d>>n;
		double ans,mx=-1;
		for(int i=1;i<=n;i++){
			cin>>a[i].k>>a[i].s;
			a[i].sj=(d-a[i].k)*1.0/(a[i].s*1.0);
			mx=max(mx,a[i].sj);
		}
		ans=d*1.0/mx;
		cout<<"Case #"<<x<<": ";
		cout<<fixed<<setprecision(10)<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：_fallen_leaves_ (赞：0)

[P13165 [GCJ 2017 #1B] Steed 2: Cruise Control](https://www.luogu.com.cn/problem/P13165)

## 题意
Annie 骑着马沿着一条单向公路行进。她位于公路的 $0$ 处，目的地在 $D$ 处，还有 $N$ 匹其他马同样行进，它们都会一直前进下去，目前都位于 Annie 的马和她的目的地之间。Annie 不想追上其他的马，请问她能选择的最大速度是多少？

## 思路
我们不需要考虑一条马追上另一条马，速度可能会改变这一条件，因为追上另一匹马的马，所用的时间肯定与追上的那匹马是时间相等，我们只要统计出所有马到 $D$ 点的距离，从中取出一个最大值，就是 Annie 的马行驶的最快时间，此时间内 Annie 的马总共行驶了 $D$ 公里，用 $D$ 除以最快时间就是答案。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,op=0;
signed main()
{
	cin>>t;
	while(t--)
	{
		op++;
		double d;
		int n;
		cin>>d>>n;
		double ans=0;
		for(int i=1;i<=n;i++)
		{
			double x,y;
			cin>>x>>y;
			double tim=(d-x)/y;
			ans=max(ans,tim);
		}
		printf("Case #%d: %10lf\n",op,d/ans); 
	}
	return 0;
}

```

---

