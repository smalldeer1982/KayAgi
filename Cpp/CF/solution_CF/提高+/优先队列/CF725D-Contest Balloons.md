# Contest Balloons

## 题目描述

ACM比赛，大家都知道。AC一题会有一个气球。
现在有$n(2<=n<=300000)$ 支队伍，每支队伍的重量是$w_i$ ，拥有$t_i$ 个气球$(w_i,t_i<=10^{18})$ ，当一支队伍的气球个数比它的重量都要大时，这个队伍就会飘起来，从而被取消比赛资格。
现在你带领的是1号队，你希望你队伍的名次尽可能靠前，你是个有原则的人，不会偷气球，但你可以把气球送给别的队伍，让他们飞起来。
求最终你的队伍所获得的最好名次

## 样例 #1

### 输入

```
8
20 1000
32 37
40 1000
45 50
16 16
16 16
14 1000
2 1000
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
4 4
4 4
4 4
4 4
4 4
4 4
5 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
14000000003 1000000000000000000
81000000000 88000000000
5000000000 7000000000
15000000000 39000000000
46000000000 51000000000
0 1000000000
0 0
```

### 输出

```
2
```

# 题解

## 作者：ahawzlc (赞：6)

这道题可以用排序 + 堆的方式解答。

可以想到一种贪心策略：每次放飞一个花费气球最少的队伍，即 $\min{w-t+1}$ 。

这个我们用小根堆来实现。

然后因为排名是按照气球数量 t 来决定的，所以要先排名，把气球多的队伍放前面，然后逐一放飞直到再也无力放飞为止。

因为有可能存在放飞一个队伍之后自己排名反而被后面的队伍 KO ，所以必须在**处理的时候**更新答案。

``` cpp
#include<bits/stdc++.h>
#define int long long
#define pi pair<int,int>//懒得用结构体了
#define F first
#define S second
using namespace std;
priority_queue<int,vector<int>,greater<int> > q;//STL大法好
pi te[300005];
signed main() {
	int n,t,w;
	cin>>n>>t>>w;
	for(int i=2; i<=n; i++) {
		int x,y;
		cin>>x>>y;
		te[i]=make_pair(x,y);
	}
	sort(te+2,te+n+1);//排序（此处是从小到大）
    //第一个输入的本队，所以不用排序
	int i=n,rank=0x3f3f3f3f;//所以i要从n开始到2
	while(1) {
		for(; i>=2&&te[i].F>t; i--)//把比自己优秀的入堆
			q.push(te[i].S-te[i].F+1);
		rank=min(rank,(long long)q.size()+1);
		if(q.size()&&t>=q.top()) {
			t-=q.top();//付出代价
			q.pop();//拜拜您内
		} else {//当无力迫害或已经rk1的时候退出
			cout<<rank;
			break;
		}
	}
	return 0;
}
```


---

## 作者：allqpsi (赞：3)

#### 这道题并不是很难，用堆就可过。

### 思路：

我们首先想到的就是：我们想要让一个队飘起来这个队必须在我们前面，不然让它飘起来也无益。

所以我们就得出一个思路，将在我们前面的人按照他们飘起来所需气球塞入堆，每次取最小的。

那我们就遇到一个问题，若在给他人气球时有人超过了我们怎么办？其实很简单，我们只需将它也塞入堆就行了。

维护名次的话，我们只需边操作边取 max 就行了。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int v,c;
	bool operator<(node l)const{
		return c-v>l.c-l.v;
	}
};
priority_queue<node>qi;
int n,vv,cc,l,cnt,ans=1e9;
node vi[350005];
bool cmp(node a,node b){
	return a.v>b.v;
}
signed main(){///freopen("a.in","r",stdin);
	cin>>n>>vv>>cc;
	for(int i=1;i<n;i++){
		cin>>vi[i].v>>vi[i].c;
	}
	sort(vi+1,vi+n,cmp);
	cnt=0;
	l=n;
	for(int i=1;i<n;i++){
		if(vi[i].v>vi[i].c){
			cnt++;
			continue;
		}
		if(vi[i].v<=min(vv,cc)){
			l=i;
			break;
		}
		qi.push(vi[i]);
	}
	ans=min(ans,l-cnt);
	while(!qi.empty()&&vv>0){
		node a=qi.top();
		qi.pop();
		if(a.c-a.v+1>vv){
			break;
		}
		vv-=a.c-a.v+1;
		cnt++;
		while(l<n&&vi[l].v>vv){
			if(vi[l].v>vi[l].c){
				cnt++;
				continue;
			}
			qi.push(vi[l]);
			l++;
		}
		ans=min(ans,l-cnt);
	}
	cout<<ans;
} 
```

---

## 作者：tangyigeng (赞：3)

## 简要题意
给出两个整数表示气球数和最大能承受的气球数，我们可以将自己的气球给别人一个。当一个人气球数严格大于最大能承受的气球数时，这个人就被淘汰了并且也算在最终排名里面，求最终按气球降序排列中我们能拿到最高的排名。
## 分析
为了让我们能更靠前，我们得尽可能的多淘汰目前排在我们前面的人，而淘汰第 $i$ 个人只需要将我们的气球给对方 $w_i-t_i+1$ 个，所以我们可以把排在我们前面的人的 $w_i-t_i+1$ 用一个小根堆保存。

但是把我们的气球给别人后我们的排名也有可能会降低，之前气球比我们少的人这时候可能就比我们多了，所以可以先把所有人按 $t_i$ 排个序，然后用记个 $top$ 表示一到 $top$ 的人是排在我们前面的，当我们的气球减少时就从 $top$ 挨个往后找该派在我们前面的，然后将这些人的 $w_i-t_i+1$ 扔进堆里。

最后在实时用一个变量记录每一次送气球操作前后的答案的最小值。
## 代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
namespace AKIOI{
	const int N = 3e5;
	struct node{
		ll t, w;
	} a[N + 10];
	int n;
	priority_queue<pair<ll, int> > q;
	bool cmp(node x, node y){
		if(x.t != y.t)
			return x.t > y.t;
		return x.w < y.w;
	}
	int main(){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%lld%lld", &a[i].t, &a[i].w);
		sort(a + 2, a + n + 1, cmp);
		int top = 2, ans;
		while(a[top].t > a[1].t)
			q.push({a[top].t - a[top].w, top++});
		ans = q.size();
		while(q.size()){
			if(a[1].t + q.top().first - 1 >= 0){
				a[1].t += q.top().first - 1;
				q.pop();
			}
			else
				break;
			while(a[top].t > a[1].t)
				q.push({a[top].t - a[top].w, top++});
			ans = min(ans, (int)q.size());
		}
		printf("%d", min(ans, (int)q.size()) + 1);
		return 0;
	}
}
int main(){
	return AKIOI::main();
}
```

---

## 作者：Suiseiseki (赞：3)

这一道题不难发现，就是一道贪心。

我们不可能把排名比自己低的队伍送上天，这没有意义。

可以很容易地发现，当前的名次等于得分比我大的名次的人的总个数+1

当我们在某种状态下已经拿到第一名时，可以不必再继续了

每次肯定让我们前面最容易飞的队伍上天，然后更新当前名次、最优答案，把飞走的队伍挪开

相信大部分同学看到这里马上就会想到优先队列，没错，这题就是优先队列。

思路也理顺了，下面就来看代码吧：
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
struct P{
    long long t;
    long long w;
    friend bool operator <(P p,P q){//重载运算符，不会的同学可以用cmp代替
        if(p.t==q.t){
            return p.w<q.w;
        }
        return p.t>q.t;
    }
}a[300005];
priority_queue<long long,vector<long long>,greater<long long> >q;//标准的优先队列
int mn(int a,int b){
    return a<b?a:b;
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%I64d%I64d",&a[i].t,&a[i].w);//CF的评测机是Windows系统，所以long long要用%I64d
    }
    sort(a+2,a+1+n);//排序，但一号队伍不参与排序
    int id=2;
    int ans=1<<30;//排名设为最大值
    while(1){
        while(id<=n&&a[id].t>a[1].t){
            q.push(a[id].w-a[id].t+1);
            id++;
        }//将比当前大的队伍入堆
        ans=mn(ans,q.size()+1);//更新最优答案
        if(q.empty()||a[1].t<q.top()){//退出条件，1、堆内没有元素了（我是第一）；2、当前气球个数不能送任意一支队伍上天
            break;
        }
        a[1].t-=q.top();//送它上天
        q.pop();//把它踢掉
    }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：zhyh (赞：2)

~~STL真是太好用了~~

模拟一下决策，不妨把当前在场的队伍分成两部分：比自己得分高和比自己得分低的。（对题目的补充说明：得分相同时算自己赢，见样例#2）

暂时不管低的那部分，我们先送高的上天~~（雾~~。那么当然要选最小代价，即 $(w-t+1)$最小的啦。对此我们可以用个小根堆维护。

送走一个队伍后，我们的得分就降了一些，可能就打不过原来比我们得分低的那部分中的某些队伍了，于是此时把那些翻盘的队压到堆里。得分小的那部分事先排序一下就可以了。

当前我们打败的队伍数就是飞走的队伍数和比我们得分低的队伍数之和，需要不断模拟并更新答案，直到堆为空或送不动为止。

代码如下~~（我好像对小根堆做了些多余的事）~~：
```cpp
#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

struct node {
    ll t, w;
    bool operator > (const node &o) const {
        return w-t > o.w-o.t;
    }
} a[300005];
priority_queue<node,vector<node>,greater<node> > Q;
    ll N, ans;

bool cmp(node x, node y)
{
    return x.t > y.t;
}
int main()
{
    scanf("%lld", &N);
    for (int i=1; i<=N; i++) scanf("%lld%lld", &a[i].t, &a[i].w);
    sort(a+2,a+N+1,cmp);
    
    for(int k=2, tot=0;;) {
        while (a[k].t > a[1].t && k<=N) Q.push(a[k++]);
        ans = max(ans, N-k+1+tot);
        if (!Q.empty() && Q.top().w-Q.top().t+1 <= a[1].t) {
            a[1].t -= Q.top().w-Q.top().t+1, Q.pop(), tot++;
        } else break;
    }
    
    printf("%lld\n", N-ans);
    return 0;
}
```

---

## 作者：No21 (赞：1)

## 细节！！！
- 一开始不会有任何队伍被放飞。

- 当一个队伍的气球数量大于其重量的时候才会被放飞（等于则不会）。

- 若你的队伍和其他队伍同分，你的队伍在所有同分队伍中排名第一。

## 解题思路

首先，目前比我们名次低的队伍不值得坑害，所以我们要坑害名次比我们高的队伍。

其次，对于每个名次比我们高的队伍，坑害他们的代价也不同，显然，坑害第 $i$ 个队伍的代价为 $w_i-t_i+1$。

我们考虑，对于一个队伍，我们并不关心他的气球数比我们多多少，我们只关心他的气球数是否比我们多，因此不难得到，每次坑害一个名次比我们高且坑害代价尽量低的队伍是最优的。我们使用一个优先队列维护坑害每一个名次比我们高的队伍的代价，每次坑害队首的队伍。

由于一次坑害有可能使我们的排名降低（坑害了名次高的,但是我们的气球也会变少），因此我们需要不断更新比我们名次高的队伍，同时判断是否需要更新答案（变优则更新，否则不更新）。

题目不难，但是一定要注意细节，上代码。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace TO
{
    const int N=3e5+21;
    int n,ans=1e9,res=1;
    struct st
    {
        int t,w;
    }a[N];
    int myt,myw,last=1;//这里使用myt表示我们的气球量，myw表示我们的重量
    priority_queue <int,vector <int>,greater <int> > q;
    bool cmp(st a,st b)
    {
        return a.t>b.t;
    }
    int mian()
    {
        cin>>n;
        cin>>myt>>myw;
        for(int i=1;i<n;i++)
            cin>>a[i].t>>a[i].w;
        sort(a+1,a+n,cmp);
        while(myt>=0)
        {
            for(int i=last;i<n;i++)//用last表示我们上一次停止进队的位置，避免重复进队
            {
                if(a[i].t<=myt)
                {
                    last=i;
                    break;
                }
                q.push(a[i].w-a[i].t+1);
                res++;
                if(i==n-1)
                    last=n;
            }
            ans=min(ans,res);
            if(q.empty())
            {
                ans=1;
                break;
            }//一定要判，不然下面的if会RE
            if(myt>=q.top())
            {
                myt-=q.top();
                res--;
                q.pop();
            }
            else
                break;
        }
        cout<<ans;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：RioFutaba (赞：0)

## 题意
有 $n$ 个队伍，每个队伍有 $t_i$ 和 $w_i$，$t_i$ 越大排名越前。当 $t_i$ 大于 $w_i$ 时，第 $i$ 个队伍被淘汰。现在 $1$ 号队可以减少自己的 $t$ 送给别的队伍，问能达到的最前的排名。
## 思路
可以进行贪心。容易想到，每次淘汰当前 $t$ 比自己大的且耗费 $t$ 最少的队伍，直到没有队伍存在或 $t$ 不足以进行操作。中途要不断把 $t$ 比自己大的队伍入队，并记录当前排名，取最大值。

可以先按 $t$ 排序，然后用优先队列找到最小的花费。

具体实现看代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long//t,w很大，需要开long long
const int maxn=3e5+5;
struct node{
	int t,w;
	bool operator<(node &o){return t>o.t;}//按 w 从小到大排序
}a[maxn];
int n,r=maxn;//r 为排名，默认为极大值
priority_queue<int,vector<int>,greater<int>> q;//小顶堆
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].t,&a[i].w);
	int x=a[1].t;//记录 1 号队伍的 t 值
	sort(a+2,a+n+2);//1号队伍不需要排序
	int tot=2;//tot 之前的队伍已经入队过
	while(1){
		for(;tot<=n && a[tot].t>x;tot++) q.push(a[tot].w-a[tot].t+1);//t 减小后需要入队 t 比自己大的队伍淘汰的花费
		r=min(r,(int)q.size()+1);//记录排名，排名为比自己大的 t 值个数加一
		if(r==1) break;//排名为一，之后无需再进行操作
		if(x>=q.top()){//可以淘汰
			x-=q.top();
			q.pop();
		}else{//t 值不够，跳出循环
			break;
		}
	}
	printf("%lld\n",r);//输出
	return 0;
}
```

---

## 作者：sjhnb (赞：0)

## 做法：贪心+优先队列


### 具体分析：

先按气球的初始个数从大到小排序求出初始名次，并把名次排在第一队前面的队放入优先队列。

接着，按 $ (w-t-1) $ 值从小到大优先，然后依次把气球给排名在前面的的队，给完气球后记得把自己的数量减少，然后继续跟之前排在第一队后面的队伍进行比较，考虑是否被后面的队伍反超，并且记录最好的名次。

最后输出最好的名次即可。

### 代码：
```cpp
#include<bits/stdc++.h>
#define maxn 400005
#define int long long
using namespace std;
int n;
int ans,sum;
int ii;
struct node{
	int t,w,need;
	bool operator < (const node &x) const{
		return x.need<need;
	}
}a[maxn];
inline bool cmp(node x, node y)
{
	return x.t>y.t;
}
priority_queue<node> q;
signed main()
{
	cin>>n;
	for (int i=0; i<n; i++)
		cin>>a[i].t>>a[i].w;
	sort(a+1,a+n,cmp);	//比较时注意第一队要单独提出来，不与其他队伍比较
	for (int i=1; i<n; i++)
		if (a[i].t>a[0].t)
		{
			int tp=a[i].w-a[i].t+1;
			node jl;
			jl.t = a[i].t;
			jl.w = a[i].w;
			jl.need = tp;
			q.push(jl);
		}
		else
		{
			ans = i;
			ii = i;
			break;
		}
	if (ans==0)
		ans = n;
	sum = ans;
	while (!q.empty())
	{
		node tp=q.top();
		q.pop();
		a[0].t -= tp.need;
		if (a[0].t<0)
			break;
		else
		{
			int j=ii;
			for (; j<n; j++)
				if (a[j].t>a[0].t)
				{
					int qwe=a[j].w-a[j].t+1;
					node jl;
					jl.t = a[j].t;
					jl.w = a[j].w;
					jl.need = qwe;
					q.push(jl);
				}
				else
					break;
			sum += j-ii-1;
			ii = j;
			ans = min(ans,sum);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：破忆 (赞：0)

## 【题意】
每个人又$t$个气球和$w$的重量，当$t>w$时会失去比赛资格，气球数多排名靠前，你可以赠送气球放飞他人，使得自己的排名最高
## 【分析】
首先按照气球数从大到小排序

放飞前面的人能够使自己的排名变高，气球一定是送给前面

**贪心**地考虑，要选择代价最小的人放飞，即$w-t$最小

动态维护这个最小值可以用**堆**

放飞掉一个人之后，自己可能会因为气球数变少排名下降，需要与后面的人比较并及时处理

若后面的人超越自己，则需要放入堆中等待下一步处理

不断重复以上操作，期间维护当前排名，取最小
## 【算法】
贪心+堆
## 【代码】
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn=3e5+5,INF=1<<30;
int n;
LL T,W;
LL read(){
	LL ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
struct data{
	LL t,w;
	data (const LL _t=0,const LL _w=0){t=_t,w=_w;}
	bool operator <(data b)const{return w-t<b.w-b.t;}
}a[maxn],hep[maxn];
int len;
bool cmp(data x,data y){
	return x.t>y.t;
}
void put(LL t,LL w){
	hep[++len]=data(t,w);
	int son=len;
	while(son>1&&hep[son]<hep[son>>1]){
		swap(hep[son],hep[son>>1]);
		son>>=1;
	}
}
void get(LL &t,LL &w){
	#define ls (fa<<1)
	#define rs (fa<<1|1)
	t=hep[1].t,w=hep[1].w;
	hep[1]=hep[len--];
	int fa=1,son;
	while(ls<=len){
		if(rs>len||hep[ls]<hep[rs]) son=ls;else son=rs;
		if(hep[son]<hep[fa]) swap(hep[fa],hep[son]),fa=son;else return;
	}
}
int ans=INF,now=1;
int main(){
	freopen("CF725D.in","r",stdin);
	freopen("CF725D.out","w",stdout);
	n=read()-1,T=read(),W=read();
	for(int i=1;i<=n;i++) a[i].t=read(),a[i].w=read();
	sort(a+1,a+1+n,cmp);
	int i=1;
	while(1){
		if(ans==1) break;
		while(i<=n&&T<a[i].t) put(a[i].t,a[i].w),i++,now++;
		ans=min(ans,now);
		if(len){
			LL t,w;
			get(t,w);
			T-=w-t+1;
			if(T<0) break;
			now--;
		}else break;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

