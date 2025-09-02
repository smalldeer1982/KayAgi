# [GCJ 2011 #2] Airport Walkways

## 题目描述

你现在在机场，站在 $0$ 点。通往登机口的走廊长度为 $X$ 米，你的飞机即将起飞。走廊上有若干条自动步道，每条步道的速度为 $w_i$。当你在步道上行走或奔跑时，你的速度为（你的速度 $+$ $w_i$）。步道不会移动它们的位置，只是让你移动得更快。步道之间不会重叠：在走廊的任意一点，至多只有一条步道，但一条步道可以在另一条步道结束的地方开始。

你的正常步行速度为 $S$。你担心可能赶不上飞机，因此你可以选择奔跑一段时间——你最多可以以速度 $R$ 奔跑 $t$ 秒。你不需要连续奔跑 $t$ 秒：你可以将这 $t$ 秒分成任意多个时间段，甚至可以不用完全部时间。

请问，在你合理安排步行和奔跑的情况下，最短需要多少时间才能到达登机口 $X$ 点？

## 说明/提示

**样例解释**

在第一个样例中，最优的做法是立即开始奔跑，并奔跑 1 秒。

**数据范围**

- $1 \leq T \leq 40$。
- $1 \leq S < R \leq 100$。
- $1 \leq w_i \leq 100$。
- $0 \leq B_i < E_i \leq X$。
- $E_i \leq B_{i+1}$。

**小数据集（8 分，测试集 1 - 可见）**

- $1 \leq t \leq 100$。
- $1 \leq X \leq 100$。
- $1 \leq N \leq 20$。
- 时间限制：3 秒。

**大数据集（10 分，测试集 2 - 隐藏）**

- $1 \leq t \leq 10^6$。
- $1 \leq X \leq 10^6$。
- $1 \leq N \leq 1000$。
- 时间限制：6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
10 1 4 1 2
4 6 1
6 9 2
12 1 2 4 1
6 12 1
20 1 3 20 5
0 4 5
4 8 4
8 12 3
12 16 2
16 20 1```

### 输出

```
Case #1: 4.000000
Case #2: 5.500000
Case #3: 3.538095238```

# 题解

## 作者：yytmcjs (赞：1)

# P13374 [GCJ 2011 #2] Airport Walkways
### 题目概括
有一个长廊，里面设有不重叠的加速步道，给出在地面行走和奔跑的速度，以及每个步道的起止点和在上面的增益速度。可以选择奔跑或行走，但奔跑有时限，问时间最小值。
### 思路
可以很轻松的看出来这是一道贪心题。

那么，**如何贪**？

我们可以设两段路程 $s$ 相等但基础速度分别为 $v1$ 和 $v2$，且 $v1 < v2$。此时，如果奔跑带来的额外速度为 $v3$，那么两个路段可以减少的时间分别为 $\frac{v3 \times s}{( v1 + v3 ) \times v1}$ 和 $\frac{v3 \times s}{( v2 + v3 ) \times v2}$，显而易见的，前者带来的收益更大，也就是说我们贪心的策略是**速度小的优先**。

我们只需要一个排序便可解决这个问题，接下来就是对于每个排在前面的步道尽量多地使用奔跑并用总时间减去节省的时间以得出答案。

这里还有个小细节：为了方便计算，我们可以将没有步道的部分看作一个整体，其速度就是行走的速度。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

double T;
pair<double,double> a[100005];		//这里用pair数组存储{速度，长度} 

int main(){
	cin >> T;
	for (int j=1;j<=T;j++){
		double x,s,r,t,cnt=0,sum=0;
		int n;
		cin >> x >> s >> r >> t >> n;
		for (int i=1;i<=n;i++){		//读入 
			int b,e,w;
			cin >> b >> e >> w;
			a[i].first=w+s;
			a[i].second=e-b;
			cnt+=a[i].second;		//计算叠加行走速度后的速度和每段长度 
		}
		if (cnt<x){
			n++;
			a[n].first=s;
			a[n].second=x-cnt;		//剩下的没有步道的部分 
		}
		for (int i=1;i<=n;i++) sum+=a[i].second/a[i].first;		//总的时间 
		sort(a+1,a+n+1);		//排序 
		for (int i=1;i<=n;i++){
			if (t<=0) break;		//奔跑时间用完就停 
			double ti=a[i].second/(a[i].first+(r-s));		//如果使用奔跑，全程省下的时间 
			double tt=min(ti,t);		//有可能剩余的奔跑时间不够 
			sum-=tt*(r-s)/a[i].first;		//这里是一个整理完的算省出时间的公式 
			t-=tt;		//用了 
		}
		cout << "Case #" << j << ": ";
		printf("%.6lf\n", sum);		//保留精度 
	}
	return 0;
}

```
### 公式推导
上面的代码里有一个不太好想的公式，我已经标明，现在来推导一下：

首先，$tt$ 是我们最终决定使用的奔跑时间，$r$ 是奔跑速度，$s$ 是行走速度，$w$ 为步道基础速度。我们在 $tt$ 时间内多走的路程是 $(r + w) \times tt - (s + w) \times tt$，化简便是 $tt \times ( r - s )$ 而这个路程在行走情况下的时间是 $\frac{tt \times ( r - s )}{s + w}$，也就是我们省出来的时间。
### 总结
只要能发现贪心的策略，这道题就基本没问题了，如果上面的公式看不懂可以自己试着推一下。

（如果有问题还请指正，谢谢）

---

## 作者：zhanlinchuan (赞：1)

# 题解
[P13374 [GCJ 2011 #2] Airport Walkways](https://www.luogu.com.cn/problem/P13374)
## 题目分析
在长度为 $X$ 的走廊有 $N$ 个自动步道，每条步道的速度为 $w_i$ 。你的步行速度为 $S$，奔跑速度为 $R$，总共可以跑 $t$ 秒。求到达登机口的最小时间。
## 思路
我们可以用贪心处理这道题。在步道速度小或没有步道的地方跑步会更省时。所以我们可以对步道速度从小到大排序。

最后输出要注意精度。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
struct node{
	double l,w;
}e[100005];
bool cmp(node x,node y){
	return x.w<y.w;
}
int main(){
	cin>>T;
	for(int k=1;k<=T;k++){
		double x,s,r,t,n;
		cin>>x>>s>>r>>t>>n;
		double len0=x;  //记录没有步道的路径长度
		double ans=0;
		for(int i=1;i<=n;i++){
			double a,b,c;
			cin>>a>>b>>c;
			e[i].l=b-a;
			e[i].w=c;
			len0-=e[i].l;
			ans+=e[i].l/(e[i].w+s);
		}
		ans+=len0/s;
		sort(e+1,e+int(n)+1,cmp);
		if(r*t<=len0){
			ans-=len0/s;
			ans+=(t+(len0-t*r)/s);
		}
		else{
			ans-=len0/s;
			ans+=len0/r;
			t-=len0/r; 
			for(int i=1;i<=n;i++){
				if(t<=e[i].l/(e[i].w+r)){
					ans-=e[i].l/(s+e[i].w);
					ans+=(t+(e[i].l-t*(r+e[i].w))/(s+e[i].w));
					break;
				}
				ans-=e[i].l/(s+e[i].w);
				ans+=e[i].l/(r+e[i].w);
				t-=e[i].l/(r+e[i].w);
			}
		}
		cout<<"Case #"<<k<<": ";  //冒号后面有个空格别漏了
		cout<<fixed<<setprecision(6)<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：chenzhuole1 (赞：0)

## 题解：P13374 [GCJ 2011 #2] Airport Walkways

[题目链接](https://www.luogu.com.cn/problem/P13374)

### 思路

首先我们要思考一点，哪些路段使用奔跑能降低总时间？按照常理来说，应该就是在速度最低的时候奔跑，所以我们考虑贪心。

首先计算各路段的基础通行时间，然后考虑在这些路段上分配奔跑时间。

计算无步道路段长度，将其视为速度为 $S$ 的特殊路段，计算所有路段以步行速度通过的总时间，将路段按从小到大排序，然后分配时间，这里就需要贪心。

先计算在该路段上完全奔跑所需时间，再计算实际奔跑时间，算一下它们节省了多少时间，再用剩余奔跑时间减去实际奔跑时间。如果剩余奔跑时间为 $0$，即代表用完了就结束。最后答案就是初始时间减去节省的时间。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct data1{
	double l,v;
}s[1005];
double x,sp,r,t,sum,ans,tot,lst,num,b,e,w;
int n,ta;
bool cmp(data1 a,data1 b){return a.v<b.v;}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout<<fixed<<setprecision(6);//误差在10^6以内 
    cin>>ta;
    for(int k=1;k<=ta;k++)
	{
        cin>>x>>sp>>r>>t>>n;
        sum=0;
        for(int i=1;i<=n;i++)
		{
            cin>>b>>e>>w;
            s[i].l=e-b;
            s[i].v=sp+w;
            sum+=s[i].l;
        }
        if(x>sum)
		{
            s[++n].l=x-sum;
            s[n].v=sp;
        }
        tot=0;
        for(int i=1;i<=n;i++) tot+=s[i].l/s[i].v;
        sort(s+1,s+n+1,cmp);
        lst=t;
        num=0;
        for(int i=1;i<=n;i++)
		{
            if(lst<=0) break;
            double sp1=s[i].v+(r-sp);
            double ma=s[i].l/sp1;
            double use=min(lst,ma);
            num+=use*(r-sp)/s[i].v;
            lst-=use;
        }
        ans=tot-num;
        cout<<"Case #"<<k<<": "<<ans<<'\n';
    }
    return 0;
}
```

---

