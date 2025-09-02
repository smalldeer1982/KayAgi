# Lunar New Year and Food Ordering

## 题目描述

Lunar New Year is approaching, and Bob is planning to go for a famous restaurant — "Alice's".

The restaurant "Alice's" serves $ n $ kinds of food. The cost for the $ i $ -th kind is always $ c_i $ . Initially, the restaurant has enough ingredients for serving exactly $ a_i $ dishes of the $ i $ -th kind. In the New Year's Eve, $ m $ customers will visit Alice's one after another and the $ j $ -th customer will order $ d_j $ dishes of the $ t_j $ -th kind of food. The $ (i + 1) $ -st customer will only come after the $ i $ -th customer is completely served.

Suppose there are $ r_i $ dishes of the $ i $ -th kind remaining (initially $ r_i = a_i $ ). When a customer orders $ 1 $ dish of the $ i $ -th kind, the following principles will be processed.

1. If $ r_i > 0 $ , the customer will be served exactly $ 1 $ dish of the $ i $ -th kind. The cost for the dish is $ c_i $ . Meanwhile, $ r_i $ will be reduced by $ 1 $ .
2. Otherwise, the customer will be served $ 1 $ dish of the cheapest available kind of food if there are any. If there are multiple cheapest kinds of food, the one with the smallest index among the cheapest will be served. The cost will be the cost for the dish served and the remain for the corresponding dish will be reduced by $ 1 $ .
3. If there are no more dishes at all, the customer will leave angrily. Therefore, no matter how many dishes are served previously, the cost for the customer is $ 0 $ .

If the customer doesn't leave after the $ d_j $ dishes are served, the cost for the customer will be the sum of the cost for these $ d_j $ dishes.

Please determine the total cost for each of the $ m $ customers.

## 说明/提示

In the first sample, $ 5 $ customers will be served as follows.

1. Customer $ 1 $ will be served $ 6 $ dishes of the $ 2 $ -nd kind, $ 1 $ dish of the $ 4 $ -th kind, and $ 1 $ dish of the $ 6 $ -th kind. The cost is $ 6 \cdot 3 + 1 \cdot 2 + 1 \cdot 2 = 22 $ . The remain of the $ 8 $ kinds of food will be $ \{8, 0, 2, 0, 4, 4, 7, 5\} $ .
2. Customer $ 2 $ will be served $ 4 $ dishes of the $ 1 $ -st kind. The cost is $ 4 \cdot 6 = 24 $ . The remain will be $ \{4, 0, 2, 0, 4, 4, 7, 5\} $ .
3. Customer $ 3 $ will be served $ 4 $ dishes of the $ 6 $ -th kind, $ 3 $ dishes of the $ 8 $ -th kind. The cost is $ 4 \cdot 2 + 3 \cdot 2 = 14 $ . The remain will be $ \{4, 0, 2, 0, 4, 0, 7, 2\} $ .
4. Customer $ 4 $ will be served $ 2 $ dishes of the $ 3 $ -rd kind, $ 2 $ dishes of the $ 8 $ -th kind. The cost is $ 2 \cdot 3 + 2 \cdot 2 = 10 $ . The remain will be $ \{4, 0, 0, 0, 4, 0, 7, 0\} $ .
5. Customer $ 5 $ will be served $ 7 $ dishes of the $ 7 $ -th kind, $ 3 $ dishes of the $ 1 $ -st kind. The cost is $ 7 \cdot 3 + 3 \cdot 6 = 39 $ . The remain will be $ \{1, 0, 0, 0, 4, 0, 0, 0\} $ .

In the second sample, each customer is served what they order except the last one, who leaves angrily without paying. For example, the second customer is served $ 6 $ dishes of the second kind, so the cost is $ 66 \cdot 6 = 396 $ .

In the third sample, some customers may not be served what they order. For example, the second customer is served $ 6 $ dishes of the second kind, $ 6 $ of the third and $ 1 $ of the fourth, so the cost is $ 66 \cdot 6 + 666 \cdot 6 + 6666 \cdot 1 = 11058 $ .

## 样例 #1

### 输入

```
8 5
8 6 2 1 4 5 7 5
6 3 3 2 6 2 3 2
2 8
1 4
4 7
3 4
6 10
```

### 输出

```
22
24
14
10
39
```

## 样例 #2

### 输入

```
6 6
6 6 6 6 6 6
6 66 666 6666 66666 666666
1 6
2 6
3 6
4 6
5 6
6 66
```

### 输出

```
36
396
3996
39996
399996
0
```

## 样例 #3

### 输入

```
6 6
6 6 6 6 6 6
6 66 666 6666 66666 666666
1 6
2 13
3 6
4 11
5 6
6 6
```

### 输出

```
36
11058
99996
4333326
0
0
```

# 题解

## 作者：qnickx (赞：3)

模拟，主要恶心的地方应该在于那个找最便宜的食物的条件。我们开一个优先队列，然后把费用的相反数丢进去，然后每次客人提出要求的时候给他满足一下要求，注意实时针对a数组情况来情况优先队列。如果操作完了还有剩余那说明这个客人的要求我们是满足不了的，花费就为0. 
代码如下：
```cpp
#include<iostream>
#include<queue> 
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
priority_queue< pair<ll,ll> > q;
ll n,m,sum;
ll dn[100005],a[100005],c[100005]; 
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(register int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(register int i=1;i<=n;i++)
	{
		cin>>c[i];
		q.push(make_pair(-c[i],(ll)i));
	}
	register ll tmp,q1,q2;
	for(register int i=1;i<=m;i++)
	{
		cin>>q1>>q2;
		tmp=min(q2,a[q1]);
		dn[i]+=(tmp*c[q1]);
		q2-=tmp;
		a[q1]-=tmp;
		if(q2>0)
		{
			while(!q.empty()&&q2>0)
			{
				if(a[q.top().second]==0)
				{
					q.pop();
					continue;
				}
				tmp=min(q2,a[q.top().second]);
				dn[i]+=tmp*c[q.top().second];
				a[q.top().second]-=tmp;
				q2-=tmp;
			}
		}
		if(q2>0)
			dn[i]=0;
	}
	for(register int i=1;i<=m;i++)
	{
		cout<<dn[i];
		if(i!=m)
			cout<<endl;
	}
	return 0;
}
```

---

## 作者：Anguei (赞：2)

模拟题。题面较长，在打 CF 的时候需要耐心读完题目（这也就是比赛时 C 已有 200 AC 时此题 AC 数为零的原因）。

题目要求先考虑最便宜的饭菜，当价格相同的时候考虑序号小的。然而我排序的时候漏掉了第二个条件竟然没有 FST，可能是数据水吧。

有人使用 `for (int i = 1; i <= m; ++i)` 在其中有些了 `i` 的循环，导致样例全过却奇妙的 Wa on #7。所以还是 `while (m--)` 比较安全。

使用 `map` 保存可以简化一下代码。当然这不是必须的。

剩下的就是根据题目指出的三种情况进行模拟了，不难。

```cpp
const int N = 100000 + 5;
struct Data {
    int id, a, c;
    Data(){}
    Data(int id, int a, int c) : id(id), a(a), c(c) {}
    bool operator<(const Data &rhs) const {
        return c < rhs.c; // 这里严格来讲应该加一个比较条件
    }
} x[N];

int n, m, pos = 1;
std::map<int, int> map;

void solution() {
    n = read(), m = read();
    rep(i, 1, n) x[i].a = read(), x[i].id = i;
    rep(i, 1, n) x[i].c = read();
    std::sort(x + 1, x + n + 1);
    rep(i, 1, n) map[x[i].id] = i;
    while (m--) {
        int t = read(), d = read(), ans = 0; t = map[t];
        // 下面是分三种情况进行模拟。
        if (x[t].a >= d) ans = d * x[t].c, x[t].a -= d, d = 0;
        else {
            ans = x[t].a * x[t].c, d -= x[t].a, x[t].a = 0;
            while (pos <= n && d) {
                int now = std::min(d, x[pos].a);
                d -= now, x[pos].a -= now;
                ans += now * x[pos].c;
                if (!x[pos].a) ++pos;
            }
        }
        println(d ? 0 : ans);
    }
}
```

---

## 作者：DengDuck (赞：0)

水题，它咋说你咋做就行了。

首先你给食物排个序，再记录食物之前的位置对应的排序后的位置，然后你就再加个指针指向当前最便宜的没吃完的食物，那么就可以快速找到最便宜的食物或者指定食物的位置。

然后你就直接按照题目大意给食客安排就行了。

时间复杂度为 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e5+5;
struct node
{
	LL a,c,num;
}a[N];
bool cmp(node x,node y)
{
	if(x.c==y.c)return x.num<y.num;
	return x.c<y.c;
}
LL n,m,x,y,b[N];
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i].a);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i].c),a[i].num=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)b[a[i].num]=i;
	LL k=1;
	while(m--)
	{
		scanf("%lld%lld",&x,&y);
		LL t=min(a[b[x]].a,y),ans=0;//吃指定食物
		y-=t,a[b[x]].a-=t;
		ans+=t*a[b[x]].c;
		while(y&&k<=n)//吃便宜食物
		{
			LL t=min(a[k].a,y);
			a[k].a-=t,y-=t;
			ans+=t*a[k].c;
			if(a[k].a==0)k++;
		}
		if(y)ans=0;
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Katsura_Hinagiku (赞：0)

一道模拟题，认真读题，按题意模拟即可。~~主要考的是英文阅读理解~~

最麻烦的事情是确认剩余菜品中最便宜的一项，注释中有思路的阐释。直接上代码吧。

```cpp
#include<bits/stdc++.h>//万能头文件
#define ll long long
using namespace std;
struct node
{
	int id;//菜品在原序列中的编号 
	ll sum,cost;//sum:菜品的数量  cost:菜品的单价 
}q[100005];
bool cmp(node a,node b)
{
	if(a.cost!=b.cost)return a.cost<b.cost;
	return a.id<b.id;
}//以单价为第一关键字升序排序，以编号为第二关键字升序排序 
int t[100005];//用于储存排序后当前元素对应的原序列的菜品编号 
int st=1;//记录客户需求的菜品数量不够时，提供的最便宜的菜品是哪一种 
ll ans=0;
bool p=0;//是否所有菜已售完 
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		q[i].id=i;
		scanf("%lld",&q[i].sum);
	}
	for(int i=1;i<=n;++i)
	{
		scanf("%lld",&q[i].cost);
	}
	sort(q+1,q+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		t[q[i].id]=i;
	}
	for(int i=1;i<=m;++i)
	{
		ans=0;
		int x;
		ll y;
		scanf("%d%lld",&x,&y);
		if(p)
		{
			printf("0\n");
			continue;
		}//如果所有菜品都已售完，后面的顾客直接离开，无收益 
		if(y<=q[t[x]].sum)
		{
			q[t[x]].sum-=y;
			ans+=q[t[x]].cost*y;
			while(q[st].sum==0)++st;//更新st 
		}//如果顾客要求的菜品，其剩余数量多于顾客要求的数量，则直接卖给顾客 
		else
		{
			y-=q[t[x]].sum;
			ans+=q[t[x]].cost*q[t[x]].sum;
			q[t[x]].sum=0;
			while(y)
			{
				ll temp=min(y,q[st].sum);
				ans+=q[st].cost*temp;
				y-=temp;
				q[st].sum-=temp;
				while(q[st].sum==0)
				{
					++st;
					if(st>n)
					{
						p=1;
						if(y)
						{
							printf("0\n");
						}
						else
						{
							printf("%lld\n",ans);
						}
						break;
					}
				}
				if(p)break;
			}
		}//依据题意，把剩余的最便宜的菜品卖给顾客，如果都已经卖完了，顾客直接离开，无收益 
		if(!p)printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Dog_Two (赞：0)

我们考虑用堆模拟。

堆内的元素和优先级判定几乎是显然的。

我们不采取题意给定的“一件一件地”提供菜肴的策略，每次直接判定“够不够”并计算“剩多少”。

给出代码：

```

#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,m;
long long cnt[maxn],c[maxn];
struct cmp{
	int idx;
	bool operator < (const cmp& tmp)const{
		if(c[idx]>c[tmp.idx]) return true;
		else if(c[idx]==c[tmp.idx]) return idx>tmp.idx;
		return false;
	}
};
priority_queue<cmp> q;

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i) scanf("%I64d",cnt+i);
	for(int i=1;i<=n;++i) scanf("%I64d",c+i);
	for(int i=1;i<=n;++i) q.push((cmp){i});
	for(int i=1;i<=m;++i){
		int t,d; scanf("%d%d",&t,&d);
		long long val=0;
		if(cnt[t]>=d) cnt[t]-=d,val+=d*c[t],d=0;
		else if(cnt[t]<d) d-=cnt[t],val+=cnt[t]*c[t],cnt[t]=0;
		while(d){
			if(q.empty()) break;
			int new_t;
			do{
				new_t=q.top().idx;
				q.pop();
			}while(!q.empty() and cnt[new_t]==0);
			if(cnt[new_t]==0) break;
			if(cnt[new_t]>=d){
				val+=d*c[new_t],cnt[new_t]-=d,d=0;
				if(cnt[new_t]) q.push((cmp){new_t});
			}
			else{
				d-=cnt[new_t],val+=cnt[new_t]*c[new_t],cnt[new_t]=0;
			}
		}
		if(d) val=0;
		printf("%I64d\n",val);
	}
	return 0;
}

```

---

