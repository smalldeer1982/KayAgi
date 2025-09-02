# [USACO05OPEN] Expedition G

## 题目描述

一群奶牛抢了一辆卡车决定前往树林里探险，但是由于它们的驾驶技术太糟，油箱在路上给弄破了，所以它们每前进一个单位的路程就会漏掉一个单位的油。

为了修好油箱，奶牛们必须前往最近的城市（不会超过 $10^6$ 单位路程）。  
在当前位置和城市之间有 $n$ 个加油站．奶牛可以在加油站加 $1$ 到 $100$ 单位的油。  

对于人来说，树林是个危险的地方；对奶牛来说，更是这样。  所以，奶牛要尽可能的少停站加油，幸运的是，这辆卡车的油箱非常大，你可以认为它的容量是无穷大的。  
卡车在离城 $l$ 个单位时还有 $p$ 个单位的油，你要算出奶牛们至少要停几站才能到城市，或者奶牛们根本到不了城市。

## 说明/提示

对于 $100\%$ 的数据，$1\leq n\leq 10^4$，$1\leq p\leq 1000000$。

## 样例 #1

### 输入

```
4
4 4
5 2
11 5
15 10
25 10
```

### 输出

```
2```

# 题解

## 作者：Glass_S (赞：7)

## [[USACO05OPEN]Expedition G（题目传送门）](https://www.luogu.com.cn/problem/P9833)

## 详细思路

 **贪心的模拟**

首先审题，我们可以很容易得知车在它一次性耗完 **初始油量** 这段路程中经过的加油站里才能停下来加油 (每个加油站只能加一次油) 。

此时此刻，作为一个贪心的人我们不免贪心了起来 —— 既然要加油了，那为什么不去加那个能加 **最多油** 的加油站呢 ~~(反正油是免费的)~~ 。

既然都要去加最大油了，我们就可以去开一个 **优先队列** 去存一下它能加的最大油呢。

在加上油以后，我们只需要继续耗完这些油去重复上方的加油操作 OK 了。

如果他把它油箱里的油和路过的能加油的加油站用完了，但是到达不了下一个加油站或城市，那就 over 了。

于是乎，基于此等方法的思想便诞生了。


------------

## 粗略思路

1. 从初始开始，每一次都将油箱里边的油耗完，~~然后进行时光倒流大法~~，回头再去一个加油站去加最大的油；

2. 如果某个加油站在它每次耗完油经过的这段路之间，将这个加油站放入优先队列里边，加一次油后 `sum++`；

3. 输出 -1 的操作：如果他把它手里的油和加油站用完了，但是到达不了下一个加油站或城市，那就永远到不了了。

------------

##  my AC 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<algorithm>
#define lp (p*2)
#define rp (p*2+1)
#define mid ((l+r)/2)
#define int long long
#define N 10010
using namespace std;
int n,l,p,sum,tim=1;
int vis[N];
struct oil
{
	int local,hav;//local是加油站距城市的距离,hav就是它能提供的油量
}a[N];
priority_queue<int>q;//利用优先队列去存它的最大能加的油量 
bool cmpx(const oil a,const oil b)//定义sort让a[]从大到小排列 
{
	return a.local>b.local;
}
int re() 
{
	int x=0,p=1;
	char y=getchar();
	for(;y<'0'||y>'9';y=getchar())
	    if(y=='-')
	        p=-p;
	for(;y>='0'&&y<='9';y=getchar())
	    x=x*10+y-'0';
	return x*p;
}
void wr(int x) 
{
	if(x<0)
	    x=-x,putchar('-');
	if(x>9)
	    wr(x/10);
	putchar(x%10+'0');
}
signed main()
{
	n=re();
	for(int i=1;i<=n;i++)
	    a[i].local=re(),a[i].hav=re();
	l=re(),p=re();//l为到城市的距离，p为目前油量
	sort(a+1,a+n+1,cmpx);
	while(1)
	{
		l-=p;
		if(l<=0)//当到城市的距离小于等于0，结束循环 
		    break;
		    
		for(int i=tim;i<=n;i++)
		    if(a[i].local>=l&&a[i].local<=l+p)
		    	    q.push(a[i].hav);//只有他能到达的加油站，才能给他加油 
			else {
			    tim=i;//为了方便判断下边输出-1的情况，和优化一下此for循环 
				break;
			}	
		p=q.top();//优先队列第一个就是他最大能加的油量 
		q.pop();
		sum++;
		if(q.empty()&&a[tim].local<(l-p))//如果她走过的站已经没有再能给他加油的，并且他还到达不了下一个站 
		    wr(-1),exit(0);//输出-1且结束程序 
	}
	wr(sum);
}
```

---

## 作者：zdoef (赞：3)

## 1.总体思想
最少加多少次油可以从起点到终点。
## 2.实现
- 当前点的油量加上能加的所有油看能到哪个点。
- 当油量不够到下一个点时加油。

------------
```cpp
#include <bits/stdc++.h>
using namespace std;
int read()//快读 
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}

struct node{
	int l,p;
}a[10005];
priority_queue<int> v;
int m, ans, cnt, x, y;

bool solve(int y)
{
	for (int i = 1 ; i <= m ; i++){
		int ll=a[i].l-cnt; //当前点与上一次点的距离 
		while ( y < ll ) //当前的油量不能到下一个点  
		{
			if(v.empty())//如果没有加油站能加油 
			{
				cout<<-1;//结束 
				return 0;
			}
			ans++, y+=v.top();//加上油 
			v.pop();//加油站弹出 
		}
		y-=ll, v.push(a[i].p);//油量减距离,能加的油量入队 
		cnt=a[i].l;//上次距起点距离 
	}
	return 1;
}
bool cmp(node x,node y){return x.l>y.l;}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n;
	n=read();
	m=n+1;//输入为n+1个 
	for (int i = 1 ; i <= m ; i++){
		a[i].l=read(),a[i].p=read();
	} 
	x=a[m].l;//起点终点距离 
	sort(a+1,a+m,cmp);//将l从大到小排序 
	for (int i = 1 ; i < m ; i++){
		a[i].l=x-a[i].l;//将起点终点顺序变换 
	} 
	y=a[m].p;//当前油量 
	
	if (solve(y))
	cout<<ans;
	return 0;
}
```


---

## 作者：ivyjiao (赞：2)

发一个短一点的代码。

我们先考虑每个加油站的位置：

- 如果当前加油站的位置在初始位置后面，就忽略这个加油站。
- 如果当前加油站的位置在当前位置前面，但是现在的油能够开到这个加油站，就把这些油都存起来，需要用的时候再用。
- 否则，考虑加油。

在考虑如何加油：

- 不难发现，每次如果要加油，就一定要把加油站加空，这样一定是不劣的。
- 我们建立一个优先队列存储加油站，油量大的加油站在队列顶部，油量小的加油站在队列底部。每次需要加油时依次取出队列顶部的加油站加空。
- 如果此时所有存储的加油站都被加空了，还不足以让车开到下一站，输出 `-1`。

代码：

```
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
int n,l,p,pp,ans;
pair<int,int>a[100001];
priority_queue<int>q;
bool cmp(pair<int,int>x,pair<int,int>y){
    return x.fi>y.fi;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].fi>>a[i].se;
    cin>>l>>p;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        if(a[i].fi>l&&!pp) continue;
        pp=1;
        while(p<l-a[i].fi&&q.size()) p+=q.top(),q.pop(),ans++;
        if(p<l-a[i].fi) return !puts("-1");
        p-=l-a[i].fi;
        l=a[i].fi;
        q.push(a[i].se);
    }
    while(p<l&&q.size()) p+=q.top(),q.pop(),ans++;
    if(p<l) return !puts("-1");
    cout<<ans;
}
```

---

## 作者：_H17_ (赞：2)

## 题目分析

考虑将起点和终点当做油量为 $p,0$ 的加油站，然后按照**离出发点**距离排序依次编号 $1\sim n$。

从 $1\to n$ 就是 $1\to 2 \to 3\to \cdots\to n$，所以处理 $i\to i+1$ 即可。

如果油够：直接过去；否则：从前面加油。下面讨论不能直接过去的情况。

显然既然要最少停靠必须用优先用油量大的加油站，所以可以用一个堆维护之前未被使用过的加油站油量，然后实施加油操作再弹出堆。

也就是每次先把 $i$ 放进堆中，然后如果油够用直接走，不够用就从之前剩下的加油站中加油。

稍微有点难理解，建议和代码一起阅读。

注意：把起点当加油站会导致答案比原来多 $1$，所以答案应该初始设置为 $-1$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10003;
int n,l,p,ans=-1;//注意起点
struct node{
	int p,v;//距离、油量
	node(int p=0,int v=0):p(p),v(v){}
	void r(){
		cin>>p>>v;
		return;
	}
	bool operator<(node b){
		return p<b.p;
	}
}a[N];//加油站
void add(int a,int b){
	::a[++n]=node(a,b);
	return;
}//加点 
priority_queue<int>q;//表示到现在为止所经过且未用过的加油站油量
//加过油就弹出 
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
    	a[i].r();
	cin>>l>>p;
    for(int i=1;i<=n;i++)
		a[i].p=l-a[i].p;
	add(0,p),add(l,0),sort(a+1,a+n+1);//添加起点、终点，按距离排序 
    for(int i=1,now=0;i<=n-1;i++){//处理从i->i+1 
        q.push(a[i].v);//添加加油站i
		while(!q.empty()&&a[i+1].p-a[i].p>now/*油不够*/){ 
			now+=q.top(),ans++;//从多到少加油直到够 
			q.pop();//用过的加油站不能再用
		}
        if(q.empty()&&a[i+1].p-a[i].p>now){//过不去，没加油站了 
			cout<<"-1";
			return 0;
		}
		now-=a[i+1].p-a[i].p;//开过去，油量减少 
    }
    cout<<ans;
    return 0；
}
```

---

## 作者：harmis_yz (赞：2)

## 分析

贪心，然后没了啊。

对于相邻两个加油站，设当前剩余油量为 $p'$。如果 $l_i-l_{i+1} \le p'$，则直接走过去；否则我们需要在第 $i$ 个加油站之前的某几个没加过油的加油站加油，直到 $l_i-l_{i+1} \le p'$。因为代价都是 $1$，为了使代价最小，我们优先加能加油量多的。这个用大根堆维护就行了。

## 代码

你可以自己写。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=1e4+10;
struct node{
	int l,p;
}a[N];
int n,l,p;
int ans;

il bool cmp(node a,node b){return a.l>b.l;}
il void solve(){
	cin>>n;
	for(re int i=1;i<=n;++i) cin>>a[i].l>>a[i].p;
	cin>>l>>p;
	sort(a+1,a+n+1,cmp);a[0].l=l,a[n+1].l=0;
	priority_queue<int> qu;
	for(re int i=1;i<=n+1;++i){
		if(a[i-1].l-a[i].l>p){
			while(!qu.empty()&&p<a[i-1].l-a[i].l) p+=qu.top(),qu.pop(),++ans;
			if(p<a[i-1].l-a[i].l){cout<<"-1\n";return ;}
		}
		p-=(a[i-1].l-a[i].l),qu.push(a[i].p);
	}
	cout<<ans;
	return ;
}
  
signed main(){
//	int t;cin>>t;while(t--)
	solve();
	return 0;
}
```


---

## 作者：Mr_Dolphin (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9833)    
感冒发烧，病刚好，在机房做图论做的头晕，随便找道水题写写
## 题目描述 
$p$ 个单位的油，每走一步耗一个单位的油，中途有 $n$ 个加油站，可以在加油站停下来加油，问能否走 $l$ 步，若能则最少停几站。
## 思路
贪心，个人感觉较为直接

1. 显然，既然油箱无限大，那加油时肯定加到最大。

1. 先考虑不再加油时能到哪里，若能到终点，皆大欢喜。若不能，**中途一定要加油**，考虑在哪个站加。因为这些加油站都能经过，所以距离没有影响，那么肯定哪个站油多哪个站加。

1. 再看能到哪里，若不能到终点，再找加油站加油，如此循环，直到能够到达终点。如果循环中发现中途没有加油站能加油，则不能到达终点，输出 $-1$。

数据结构分析：要支持插入，查询和删除最大值的操作，显然堆。
## code
```cpp
#include<bits/stdc++.h>
#define MAXN (int)1e4+10
#define pii pair<int,int>
#define fi first
#define se second
#define mpii make_pair
using namespace std;
int n,l,p,tmp=1,cnt;
pii a[MAXN];
priority_queue<pii> pq;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
bool cmp(pii x,pii y)
{
	return x.se>y.se;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i].se=read();
		a[i].fi=read();
	}
	l=read(),p=read();
	sort(a+1,a+n+1,cmp);
	while(l-p<=a[tmp].se&&tmp<=n)
	{
		pq.push(a[tmp]);
		tmp++;
	}
	while(p<l)
	{
		if(pq.empty())
		{
			printf("-1"); 
			return 0;
		}
		cnt++;
		pii dt=pq.top();
		pq.pop();
		p+=dt.fi;
		while(tmp<=n&&l-p<=a[tmp].se)
		{
			pq.push(a[tmp]);
			tmp++;
		}
	}
	printf("%d",cnt);
	return 0;
}
```

码风轻喷

有问题请私信

---

## 作者：Practice_Account (赞：1)

### 题目大意

[[USACO05OPEN] Expedition G](https://www.luogu.com.cn/problem/P9833)

一辆卡车要行驶 $l$ 单位的距离到达终点，开始时有 $p$ 单位的油。途中有 $n$ 个加油站，给出每个加油站到终点的距离和可以加油的数量。一个卡车的油箱无限，每走 $1$ 单位距离需要消耗 $1$ 单位的油，问卡车要到达终点最少需要加多少次油，如果到达不了终点则输出 `-1`。

### 解题方法

#### 算法：贪心、优先队列

首先，卡车肯定先从距离出发点近的加油站往后开。**每当到达一个加油站，不一定就要加油。如果油够的话尽可能在油量多的加油站加油**。

其次，我们将**到达过的加油站可以加油的数量**看作**加油的权利**。所以当油不够时，尽量用加油权利中的**最大值**。

综上所述，贪心就会包括两个方面：一是**加油站由近及远**，二是**从大到小使用加油权利**。用优先队列进行维护。


------------

### 参考代码

```
#include <bits/stdc++.h>
using namespace std;
const int N = 10000;
struct sta{
    int di, fu;
    bool operator < (const sta& s) const{
        return di > s.di;
    }
}sta[N];
int n, l, p;
int main(){
    while(scanf("%d", &n) != EOF){
        priority_queue<int> fuel;
        for(int i = 0; i < n; i ++){
        	std::cin >> sta[i].di >> sta[i].fu;
        }
        std::sort(sta, sta + n);
        std::cin >> l >> p; 
        fuel.push(p);
        int ans = 0, i = 0;
        while(l > 0 && !fuel.empty()){
            ans ++;
            l -= fuel.top();
            fuel.pop();
            while(i < n && l <= sta[i].di){
                fuel.push(sta[i ++].fu);
            }
        }
        printf("%d\n", l <= 0 ? ans - 1: -1);
    }
    return 0;
}
```


---

## 作者：wangjue1629 (赞：0)

# Solution
[题目传送门](https://www.luogu.com.cn/problem/P9833)

## 题目思路
这个问题可以使用贪心算法来解决。尽量选择能够让卡车行驶更远的加油站，以减少停车次数。

首先，我们将所有加油站按离城市的距离从近到远排序。然后，从卡车当前位置开始，依次检查每个加油站，如果卡车的油量无法到达当前加油站，就从已经检查过的加油站中选择一个油量最多的加油站，将卡车加满油，然后继续前进，直到能够到达当前加油站。如果没有合适的加油站可选，那么代表卡车无法到达城市，返回 $-1$。

如果按我的上述描述去写的话。时间复杂度为 $O(n \log n)$，可以通过本题。

---

## 作者：SSER_ZRQ (赞：0)

首先，不难想到一个粗糙的的贪心做法：将加油站按照距离排序，暴力查询当前的油量是否支持从当前加油站前往下一个加油站，如果可以就直接前往，不行就进入当前加油站。

但是这个算法有一个一眼假的地方：就是在目前看来并不需要进入某个加油站，但是从全局来看必须要进入。

我们考虑加一项新的能力：可以对所有**经过**的加油站进行远程加油。

发现这个结论是对的，在当前进行远程加油，相当于反悔了之前选择不加油的决策，保证了正确性。

当油量不够时，可以选择一个加油站进行加油。选择那个呢？当然是**已经经过并且未加过油**中能加油量最多的加油站啦。

判无解：加了所有能加的油仍到不了下一站，即无解。

维护一种数据结构，能支持插入与删除、查询最大值，堆、线段树均可。

时间复杂度 $O(n \log n)$。

---

