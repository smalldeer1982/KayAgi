# [POI 2013] TAK-Taxis

## 题目描述

Byteasar wants to take a taxi from the town Bytehole to the town Bytepit,    which is $m$ kilometres away from Bytehole.

Exactly $d$ kilometres along the way from Bytehole to Bytepit, there is    a base of $n$ taxis, numbered from $1$ to $n$.

The taxi no. $i$ has enough fuel to drive exactly $x_i$ kilometres.

Byteasar can change taxis at any point.

All the taxis start at their base but need not return there.

Your task is to determine whether Byteasar can be driven from Bytehole to    Bytepit, and if so, what it the minimum number of taxis required for such    a journey.

Translation 1:

一条线段有三个点，0为初始位置，d为出租车总部位置，m为家的位置，人要叫车，有n辆车可以提供，每辆车有一个路程上限，并且都从车站出发，叫的车行驶之后不必须回到车站，问最少叫几辆车

.Translation 2:

Byteasar想坐出租车从Bytehole镇到Bytepit镇,恰好有d千米从Bytehole镇到Bytepit镇,这有n个出租车,编号从1到n.第i个出租车有足够的燃料行驶xi千米.Byteasar可以在任意点改变出租车.所有的出租车从他们的总部出发但没必要返回总部.你的任务是判断Byteasar是否能从Bytehole镇到Bytepit镇,如果可以,求出路途需要出租车的最小数量.


## 说明/提示

提示:此题需开long long


## 样例 #1

### 输入

```
42 23 6
20 25 14 27 30 7
```

### 输出

```
4
```

# 题解

## 作者：Yizhixiaoyun (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P3550)

## 题目分析

本题是一道比较有意思的贪心。

首先我们一看题目，不难发现，在过总部之前，使用距离越小的车越浪费，因此我们将距离数组从大到小排序，然后从前往后使用车即可。

但是仔细一想，如果我们把大车都用了，最后剩下的小车是没有办法带我们回家的。所以我们得留一辆可以从总部直接回家的车，然后使用刚刚的贪心策略就可以了。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pf push_front
#define ass assign
#define fst first
#define sec second
#define lb lower_bound
#define ub upper_bound
#define zlt using
#define AK namespace
#define IOI std
zlt AK IOI;
const int maxn=500010;
long long m,d,n,a[maxn];
long long tot1,tot2,ans=1;
bool cmp(long long x,long long y){return x>y;}
void init(){
	cin>>m>>d>>n;
	for(register long long i=1;i<=n;++i) cin>>a[i];
	sort(a+1,a+n+1,cmp);
}
void duel(){
	for(register long long i=n;i>=1;--i){
		if(a[i]>=m-d){
			tot1=i;break;
		}
	}
	if(tot1==0) cout<<"0",exit(0);
	for(register long long i=1;i<=n;++i){
		if(tot1==i) continue;
		if(tot2>=d||m+d-2*tot2<=a[tot1]) break;
		else if(a[i]<=d-tot2) cout<<"0",exit(0);
		ans++;
		tot2+=(a[i]-d+tot2);
		if(tot2>=m){
			ans--;
			cout<<ans;
			exit(0);
		}
	}
}
void print(){
	if(m+d-2*tot2>a[tot1]) cout<<"0";
	else cout<<ans;
}
int main(){
	init();
	duel();
	print();
}
```

---

## 作者：karma (赞：6)

收到@远航之曲  思路的启发,顺便将题目进行了翻译(翻译的不好不要打我).

此题贪心很是巧妙,介于楼下题解中注释不多,故进行补充.

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long now,num,last,ans=1;
//now为现在人的位置 ans=1初始化为1表示最终要用一辆车直接从总部到终点 
long long N,M,a[500005];
//此题需开long long 
bool cmp(long long a,long long b){return a>b;}
int main(){
    scanf("%lld %lld %lld",&N,&M,&num);//输入路程总距离,从起点到总部距离,出租车数量 
    for(int i=1;i<=num;++i)scanf("%lld",&a[i]);//输入每个出租车的;路程限制 
    sort(a+1,a+1+num,cmp);//从大到小排序 
    for(int i=1;i<=num;++i)if(a[i]<N-M){last=i;break;}//找到第一个限制距离小于从总部到终点距离的车 
    last--;//上一个车的限制距离一定大于等于从总部到终点的距离 
    //要将这个车留下来(最后到总部时直接用这辆车) 
    //贪心:之前从起点到总部时会浪费车的汽油,且不能将汽油多的全部用尽,否则虽然用的车少,但是最后剩下的车
    //汽油都很少,从总部不能到达终点 
    if(!last){printf("0");return 0;}//如果没有一个车满足条件,则一定不能到达终点 
    for(int i=1;i<=num;++i){//枚举每个车 
        if(i==last)continue;//将此车留下来 
        if(now>=M || N-now+M-now<=a[last]) break;//到达总部或此距离小于留下的车就跳出循环
        //解释此距离:因为此时人在总部左侧,留下的车先要行驶M-now到达人的位置
        //再行驶N-now的距离到达终点,如果留下的车可以做到这点就跳出循环 
        else if(a[i]<=M-now){printf("0");return 0;}//这个车不能使人向前移动(人在总部左边时,车需要先过来) 
        ans++;//使用车的数量加一 
        now+=a[i]-(M-now);//人的位置移动 
        if(now>=N){printf("%lld",ans-1);return 0;}//直接到达(没有用留的车)所以ans-1 
    }
    if(N-now+M-now>a[last])printf("0");//剩下的车也到不了 
    else printf("%lld",ans);//可以到 
    return 0;
}
```

---

## 作者：远航之曲 (赞：3)

感觉是一道很不错的贪心


第一眼的感觉肯定是贪心，因为人在还没过车站的时候离车站越远越不划算，浪费的路程也就越多，所以要尽量先叫行驶路程远的车


但是这样只能得50分。


比如说这组数据：


12 4 5
2 3 4 5 8


如果贪心的话显然是回不去的，为什么呢？


我们观察，当人过了车站之后，只需要一辆能从车站到家的车就够了，你有再多其他的车路程短也没用


所以贪心之前需要给自己留一个路程最小的能从车站回家的车，这个车之前不能用


````cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
long long inline read()
{
    long long x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
long long m,d,n,a[500010];
bool comp(long long a,long long b)
{
    return a>b;
}
void cut(){puts("0");exit(0);}
main()
{
    m=read(),d=read(),n=read();
    for (int i=1;i<=n;i++)
        a[i]=read();
    sort(a+1,a+1+n,comp);
    long long res;
    for (res=1;res<=n;res++)
        if (a[res]<m-d)
            break;
    res--;if (!res) cut();
    long long now=0,ans=1;
    for (int i=1;i<=n;i++)
    {
        if(i==res) 
            continue;
        if(now>=d || m-now+d-now<=a[res]) 
            break;
        if(a[i]<=d-now) 
            cut();
        ans++;
        now+=a[i]-(d-now);
        if(now>=m) 
        {
            ans--;break;
        }
    }
    if (m-now+d-now>a[res])
        puts("0");
    else
        printf("%d\n",ans);
}
```

---

## 作者：HHYQ_07 (赞：0)

# 题解

## 思路

这道题考虑贪心策略，我们发现在 $0$ 到 $d$ 这个区间里，用的车的数量越多越不利，所以先尽量叫路程远的车。但再我们又想到如果让开的远的车都花在这个区间里了，那么回家时可能没有合适的车，所以在执行之前要先预留出一辆能回家的车，选一辆能满足回家的路程且能走的路程最小的车，其余按车能行驶路程从大到小排序。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int m,d,n,a[500010],sum,now,ans=1;
bool cmp(int a,int b)
{
    return a>b;
}
signed main()
{
    cin>>m>>d>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n,cmp);
    for(sum=1;sum<=n;sum++)
        if(a[sum]<m-d)break;
    sum--;
	if(sum==0)
	{
		cout<<"0";
		return 0;
	}
    for (int i=1;i<=n;i++)
    {
        if(i==sum)continue;
        if(now>=d||m+d-2*now<=a[sum])break;
        if(a[i]<=d-now)
        {
        	cout<<"0";
        	return 0;
		}
        ans++;
        now+=a[i]-d+now;
        if(now>=m) 
        {
            ans--;
			break;
        }
    }
    if(m+d-2*now>a[sum])cout<<"0";
    else cout<<ans;
    return 0;
}
```

---

## 作者：IcyFoxer_XZY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3550)

这题可以考虑贪心思路，当发现人在 $[0,d)$ 时，车越多就越浪费，所以尽可能用距离远的车。但这样可能导致没有车从 $d$ 去 $m$，所以在最开始留一辆可以的车。

注意判断只需要最后一辆车可以带到 $m$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000005;
int n,ans,m,d,x,a;
vector<int> s;
signed main(){
    scanf("%lld%lld%lld",&m,&d,&n);
    for(int i=0;i<n;++i){
    	scanf("%lld",&x);
    	s.push_back(x);
	}
	sort(s.begin(),s.end());
    if(m-d){
    	int p=lower_bound(s.begin(),s.end(),m-d)-s.begin();
    	if(p>=n){
    		puts("0");
    		return 0;
		}
		a=s[p];
		s.erase(s.begin()+p);
	}
    reverse(s.begin(),s.end());
    int pos=0,td=d-(a-m+d>>1);
    for(int i:s){
    	int t=i-d+pos;
    	if(t<=0){
    		puts("0");
    		return 0;
		}
		pos+=t;++ans;
		if(pos>=td)break;
	}
    printf("%d",ans+(pos<m));
    return 0;
}
```
Bye！

---

