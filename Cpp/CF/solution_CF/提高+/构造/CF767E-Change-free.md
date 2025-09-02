# Change-free

## 题目描述

Student Arseny likes to plan his life for $ n $ days ahead. He visits a canteen every day and he has already decided what he will order in each of the following $ n $ days. Prices in the canteen do not change and that means Arseny will spend $ c_{i} $ rubles during the $ i $ -th day.

There are $ 1 $ -ruble coins and $ 100 $ -ruble notes in circulation. At this moment, Arseny has $ m $ coins and a sufficiently large amount of notes (you can assume that he has an infinite amount of them). Arseny loves modern technologies, so he uses his credit card everywhere except the canteen, but he has to pay in cash in the canteen because it does not accept cards.

Cashier always asks the student to pay change-free. However, it's not always possible, but Arseny tries to minimize the dissatisfaction of the cashier. Cashier's dissatisfaction for each of the days is determined by the total amount of notes and coins in the change. To be precise, if the cashier gives Arseny $ x $ notes and coins on the $ i $ -th day, his dissatisfaction for this day equals $ x·w_{i} $ . Cashier always gives change using as little coins and notes as possible, he always has enough of them to be able to do this.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF767E/64d62fb5157d1985972f5b10ec8077c5e6d11b1c.png)"Caution! Angry cashier"Arseny wants to pay in such a way that the total dissatisfaction of the cashier for $ n $ days would be as small as possible. Help him to find out how he needs to pay in each of the $ n $ days!

Note that Arseny always has enough money to pay, because he has an infinite amount of notes. Arseny can use notes and coins he received in change during any of the following days.

## 样例 #1

### 输入

```
5 42
117 71 150 243 200
1 1 1 1 1
```

### 输出

```
79
1 17
1 0
2 0
2 43
2 0
```

## 样例 #2

### 输入

```
3 0
100 50 50
1 3 2
```

### 输出

```
150
1 0
1 0
0 50
```

## 样例 #3

### 输入

```
5 42
117 71 150 243 200
5 4 3 2 1
```

### 输出

```
230
1 17
1 0
1 50
3 0
2 0
```

# 题解

## 作者：hsfzLZH1 (赞：5)

## 题目大意

你初始时有无数张 $100$ 元纸币和 $m$ 张 $1$ 元纸币（假设货币系统中只有这两种纸币）。有 $n$ 天，第 $i$ 天你需要购买价值为 $c_i$ 的物品。你在这一天每让售货员找一张 $1$ 元的纸币，就会让售货员的不满意系数增加 $w_i$ ，但你在之后的天数内可以使用售货员找你的这些 $1$ 元纸币。

输出最小可能的售货员的不满意系数和，并输出每一天付钱的方案。如果有多种方案，输出任意一种。

$1\le n,c_i,w_i\le 10^5,0\le m\le 10^9$

## 解题思路

对于每天都有两种付钱方案：

1. 正好付给售货员 $c_i$ 元钱，不用找零。需要满足此时的 $m\ge c_i~mod~100$ 。 $c_i$ 为 $100$ 的倍数时默认使用此方案。选择这种方式会令你的 $m$ 值减少 $c_i~mod~100$ 。

2. 付给售货员 $\lceil \frac {c_i} {100} \rceil$ 张 $100$ 元纸币，找零 $100-c_i~mod~100$ 元。因为如果你此时多给售货员 $1$ 元纸币，售货员的找零就更多，不满意系数越大。 **注意** ：选择这种方式会令你此时的 $m$ 增加 $100-c_i~mod~100$ 。

所以我们可以预处理出每天按照方案二付款的代价（即售货员的不满意程度） $v_i=w_i\times (100-c_i~mod~100)$ 。

我们使用 **贪心** 策略。按天数处理，如果需要支付的钱数满足方案一的条件，则使用方案一付款。如果不满足条件， **从之前的某一天（包括今天）中选择一天把方案一换成方案二** 。假设选择的这一天是第 $i$ 天， 由于原来的方案一消耗了 $c_i~mod~100$ 张一元纸币，而换成方案二后又会找零 $100-c_i~mod~100$ 张一元纸币，所以把方案一换成方案二后你的一元纸币会多出 $100$ 张，一定足够你支付今天的方案一。这个操作会使售货员的不满意程度增加 $v_i$ 。

由于我们要最小化售货员每天的不满意程度之和，所以我们每次要选择最小可能的 $v_i$ 。我们使用 **优先队列** 来维护这一决策。在处理一天的方案之前，我们将今天的 $v_i$ 插入优先队列，因为在决策时也可能会选择今天把方案一换成方案二。需要换成方案二时，取出优先队列中最小的值，计算不满意程度之和。注意每天，都要将 $m$ 的值减小 $c_i~mod~100$ ，因为你总是假设一开始选择方案一。

时间复杂度 $O(n\log_2 n)$ ，空间复杂度 $O(n)$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=100010;
typedef long long ll;
ll ans;
int n,m,c[maxn],w[maxn],v[maxn];
bool tf[maxn];//tf=1 pay 100*x
struct node
{
	int id;
	bool operator<(node x)const{return v[id]>v[x.id];}
};
priority_queue<node>q;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",c+i);
	for(int i=1;i<=n;i++)scanf("%d",w+i);
	for(int i=1;i<=n;i++)if(c[i]%100)v[i]=(100-(c[i]%100))*w[i];
	for(int i=1;i<=n;i++)
	{
		if(c[i]%100==0){tf[i]=true;continue;}
		q.push({i});
		if(m>=c[i]%100)m-=c[i]%100;
		else
		{
			if(m<c[i]%100)m+=100,ans+=v[q.top().id],tf[q.top().id]=true,q.pop();
			m-=c[i]%100;
		}
	}
	printf("%I64d\n",ans);
	for(int i=1;i<=n;i++)
	{
		if(tf[i])printf("%d %d\n",(c[i]+99)/100,0);
		else printf("%d %d\n",c[i]/100,c[i]%100);
	}
	return 0;
} 
```

---

## 作者：Naganorhara_Yoimiya (赞：4)

# CF767E Change-free 题解

## 题目大意：

我有无数张百元大钞以及有限的  1 元硬币，每天收银员找  1  元零钱就会让他的愤怒值增加一点，求这个愤怒值的最小值。

## 思路分析

一眼贪心，付钱方式分两种：第一种是应该付多少就是多少；第二种是全部使用百元大钞并且让可怜的收银员找零。

先假设全部使用第一种方式，能用第一种就第一种，然后当发现零钱不够时，使用第二种方式。

很容易发现，第一种方式会消耗 $c_i \bmod  100$  元零钱，第二种方式会增加  $100$  $ -$   $c_i$    $\bmod  $  $100$   元零钱，所以把第一种方式改为第二种方式，会增加刚好  $100$  元零钱（也就是不存在改了一天发现零钱还不够用）。

那么，我们只需要选择怒气值增加最小的一天去由方式一改为方式二即可,在这里我使用了堆去维护这一性质。

##  AC  Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;//这个东东让我调了一个小时
int n,m,c[maxn],w[maxn],v[maxn],id[maxn]; 
long long ans; //不开long long见祖宗！！！！ 
bool fs[maxn]; //fs表示付款方式 若tf = true，使用100元 

struct node{
	int id;
//结构体内部的重载运算符，效率相对更高
	bool operator<(node x)const{return v[id]>v[x.id];}
};

//我们每次要选择最小可能的vi，我们使用堆维护这一决策
priority_queue<node> q;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> c[i];
	for(int i = 1;i <= n;i++) cin >> w[i];
	for(int i = 1;i <= n;i++) {
		//把第一种方案改成第二种方案 售货员的不满意程度增加vi 
		if(c[i] % 100 != 0) v[i] = (100 - (c[i] % 100)) * w[i];
	} 
	for(int i = 1;i <= n;i++){
		//如果可以直接付百元大钞，那么直接付，皆大欢喜 
		if(c[i] % 100 == 0){fs[i] = 1;continue;}
		//在处理一天的方案之前，我们将今天的vi插入优先队列，因为在决策时也可能会选择今天把方案一换成方案二。 
		q.push({i});
		//能付百元大钞就先付了 
		if(m >= c[i] % 100) m -= c[i] % 100;
		else{
			//零钱不够了 
			if(m < c[i] % 100){
				m += 100; //零钱会增加100 
				ans += v[q.top().id];
				//将这一天设置为找零的方案 
				fs[q.top().id] = 1;
				//把这一天弹出 
				q.pop();
			}
			//零钱数量减少 
			m -= c[i] % 100; 
		}
	}
	cout << ans << "\n"; 
	for(int i = 1;i <= n;i++){
		if(fs[i]) cout << (c[i] + 99) / 100 << " " << 0;
		else cout << c[i] / 100 << " " << c[i] % 100;
		cout << "\n";
	} 
    return 0;
}

---

## 作者：_Scaley (赞：1)


# 首先，这是一道贪心题

## 我的大致方法：pair+堆优

### 题目分析：

从第一天开始，到最后一天，每天可以选择找钱或者不找钱。

如果不找钱，则零钱数m减去多出的零钱；

如果找钱，则收银员的怒气值上升找钱数乘每天心情值w（下文称ann值）。

### 贪心策略：

我们就可以利用贪心思想：

#### 两种情况：


------------


##### 情况一：

如果手中的零钱数是足够的，就选择用手中的零钱支付所需要的零钱；

##### 情况二：

如果手中的零钱数不够，就找出之前用零钱支付多余钱数的一天，在那一天选择用100元支付多出钱数，让收银员找钱。

这样就多出了100元的零钱，足以支付当前所需支付的零钱，但收银员的怒气值会上升，需要专门记录下来。


------------


Q: 选哪一天呢？

A： 使收银员怒气值上升最小的那一天，也就是在之前经过的天数中选择ann值的最小值。

# 贪心正确证明：

### 反证法：

如果在需要零钱时（也就是手中零钱不足以支付多余钱数），选择非最小的ann值，那我们将在可以支付当前多余钱数的情况下，收银员的怒气值上升比最小ann值所上升的怒气值要高，不符合最优方案，故错误。

（同样结果却使收银员怒气值更高，非最优方案）

### 结论：

不能选用非最小ann值

结论成立，贪心方案正确

------------

------------
# 优化：

题目时间限制1s，若选取在每一次零钱不够时从第一天开始枚举找ann最小值

### 时间复杂度：O（n2）

**天数的取值范围是1<=n<=100000，如果遇到最坏情况，可能会T掉**

看来得优化

既然是求动态最小值，那就用堆优找最小ann值

可以用**pair类型**把之前经过的天的ann值和第几天存下



------------



## 注意：

### 1、记得开long long

（m的最大值为一的九次方，若叠加几次可能会爆int（~~也可能不会爆~~））

~~我不会算~~

### 2、用100元能够正好支付时不加入堆中

题目中不允许多给钱，如果用100元正好支付完就无法来换零钱，故不加入堆中

### 3、若用pair类型存储数据，要将ann值放在pair中的first

pair类型排序时默认用first来排序

### PS：

堆中存的是可能需要让收银员找钱的天数

一开始经过的天数（没有让收银员找零）都可能是需要让收银员找钱的天数，故放进堆中

若出现情况二，就利用堆找到ann最小值，完成找钱操作并使已找过钱的天数被pop，避免题目中多给钱的情况


------------


## **完整AC代码**

```c
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 100001
#define LL long long
#define M(i, j) make_pair(i, j)
using namespace std;

LL c[MAXN], w[MAXN], zheng[MAXN], ling[MAXN];//zheng[i]是第i天100元花费的个数，ling[i]是第i天零钱花费的元数
LL n, m, h, k, ans=0;
priority_queue<pair<LL, LL>, vector< pair<LL, LL> >, greater< pair<LL, LL> > > q;//小头堆（STL万岁！）

int main(){

　　scanf("%lld %lld", &n, &m);
　　for (int i = 1; i <= n; i++){
　　scanf("%lld", &c[i]);
　　zheng[i] = c[i] / 100;//算出每天至少花费多少100元
　　c[i] %= 100;//预处理，c[i]只存需花费零钱
　　}
　　for (int i = 1; i <= n; i++) scanf("%lld", &w[i]);
　　for (int i = 1; i <= n; i++){
　　　　ling[i] += c[i];
　　　　if (c[i]) q.push(M(w[i]*(100 - c[i]), i));
　　　　if (c[i] > m){
　　　　　　h = q.top().first;//取出最小怒气值
　　　　　　k = q.top().second;//取出是哪一天
　　　　　　q.pop();
　　　　　　ans += h;//积累怒气值
　　　　　　ling[k] -= c[k];//那一天不用找零了
　　　　　　zheng[k]++;//那一天100元整数+1
　　　　　　m += 100;//多出100元零钱
　　　　}
　　　　m -= c[i];
　　}
　　printf("%lld\n", ans);
　　for (int i = 1; i <= n; i++){
　　　　printf("%lld %lld\n", zheng[i], ling[i]);
　　}
　　return 0;
}
```
希望能帮到您⁄(⁄ ⁄•⁄ω⁄•⁄ ⁄)⁄.

---

## 作者：Thaumaturge (赞：1)

抱着打蓝题的心态来打这题，打得我要哭死了$QAQ$摧残自尊心

用的是数据结构冗杂堆砌的法子维护的

但是这种方法不用脑子，确实好啊$qwq$

观察题目，直接构造方案很麻烦，可以先将所有情况全部用1方式（全部付100元）支付，再考虑如何用2方式替换1方式。

容易发现，如果将找零的钱看作一个差分数组，收获为正，支付为负则在$i$点上替换相当于在差分数组的原数组上的i～n项减去100。我们要时刻保证这个差分数组的每一项都大于0。

咋们做呢？

由一般套路可以知道，1个2方式一定无法替换2个2方式，2个2方式替换1个2方式也是没有必要的。因此，2方式只能替换自己的1方式，或其他的1个2方式。考虑从后往前扫，如果无法直接使用2方式，可以从可行的替换区间中取出对答案贡献最大的去掉，使得当前2方式可以替换1方式。

如何判断哪些2方式可以被当前2方式替换呢？

~~数据结构堆砌啊~~

在该点后的2方式可替换该点，当且仅当他们之间的（差分数组形成的原数组）的值大于等于100。因为替换后，会造成这段区间的值全部减去100。

这些点的集合在数组上显然连续，上队列！快速查询一个最值，并将其删除，上multiset（为什么会忘记懒惰删除的优先队列，明明队列就用了懒惰删除的）！区间减，在某个无界的，但是稍有特殊的平面内寻找最靠左的点，不想也不敢打树套树！上二分套线段树！

~~整个过程脑子都是蒙的，也可以说是没带脑子~~

~~考试时要是敢这么淦就凉了呀~~

```cpp
/*************************************************************************
	> File Name: CF767E.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2020年01月12日 星期日 19时00分35秒
 ************************************************************************/
 
#include <bits/stdc++.h>
 
#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define N 100010
#define fi first
#define se second
#define int long long
 
#define pii pair<int,int>
 
using namespace std;
 
int a[N],b[N],val[N],g[N],T[N],n,C;
 
int fans,ans,lim=n+1;
 
bool bh[N],las[N];
 
multiset < pair <int,int> > s;
 
queue < pair <int,int> > q;
 
const int inf=100005;
 
struct Segment_Tree{
	int T[N<<2],tag[N<<2];
	#define ls (x<<1)
	#define rs (x<<1|1)

	inline void pushdown(int x){
		if(tag[x]){
			T[ls]+=tag[x];
			T[rs]+=tag[x];
			tag[ls]+=tag[x];
			tag[rs]+=tag[x];
			tag[x]=0;
		}
		return;
	}

	inline void pushup(int x){
		T[x]=min(T[ls],T[rs]);
	}

	void add(int x,int l,int r,int lx,int rx,int val){
		if(lx<=l && r<=rx) {T[x]+=val;tag[x]+=val;return;}
		pushdown(x);
		int mid=(l+r)>>1;
		if(lx<=mid) add(ls,l,mid,lx,rx,val);
		if(rx>mid)	add(rs,mid+1,r,lx,rx,val);
		pushup(x);
		return;
	}

	int query(int x,int l,int r,int lx,int rx){
		if(lx<=l && r<=rx) return T[x];
		pushdown(x);
		int mid=(l+r)>>1,ans=0x7f7f7f7f;
		if(lx<=mid) ans=min(ans,query(ls,l,mid,lx,rx));
		if(rx>mid)	ans=min(ans,query(rs,mid+1,r,lx,rx));
		pushup(x);
		return ans;
	}
}tree;
 
inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}
 
inline void Input(){
	n=read();tree.add(1,1,n,1,n,read());
	for(re int i=1;i<=n;++i)	a[i]=read(),val[i]=a[i]/100,a[i]=a[i]%100;
	for(re int i=1;i<=n;++i)	{b[i]=read(),g[i]=b[i]*(100-a[i]);if(!a[i]) g[i]=0;ans+=g[i];}
	for(re int i=1;i<=n;++i)	tree.add(1,1,n,i,n,g[i]/b[i]);
	return;
}

inline int find(int l,int r){
	while(l<r){
		int mid=(l+r)>>1;
		if(tree.query(1,1,n,l,mid)<100)		r=mid;
		else								l=mid+1;
	}
	return l;
}
 
inline void solve(){
	
	int mn=0x7f7f7f7f;
 
	for(re int i=n;i;--i)
	{
		if(!g[i]) continue;
		mn=tree.query(1,1,n,i,n);
 
		//cout<<"now:"<<fans<<" "<<i<<endl;
 
		if(mn>=100)
		{
			mn-=100;
			fans+=g[i];
			s.insert(make_pair(g[i],i));
			q.push(make_pair(g[i],i));
			tree.add(1,1,n,i,n,-100);
			las[i]=1;
			//printf("choose:%lld\n",i);
		}
 
		else
		{
			pii x;

			lim=find(i,n);

			while(q.size()){
				x=q.front();
				//cout<<query(x.se)-1<<" "<<x.se<<endl;
				if(x.se>lim || bh[x.se]) s.erase(x),q.pop();
				else break;
			}
 
			//cout<<q.size()<<" "<<lim<<endl;
	
			if(!q.size()) break;
 
			pii X=*s.begin();
 
			//cout<<g[i]<<" "<<i<<" "<<lim<<endl;
			if(g[i]<X.fi) continue;
			s.erase(X);
			bh[X.se]=1;
			q.push(make_pair(g[i],i));
			s.insert(make_pair(g[i],i));
			fans+=g[i]-X.fi;
			tree.add(1,1,n,i,X.se-1,-100);
			las[i]=1;
			las[X.se]=0;
		}
	}
	printf("%lld\n",ans-fans);
	for(re int i=1;i<=n;++i)
	{
		if(!a[i])
		printf("%lld 0\n",val[i]);
		else if(las[i])
		printf("%lld %lld\n",val[i],a[i]);
		else
		printf("%lld 0\n",val[i]+1);
	}
	return;
}
 
signed main(){
	Input();
	solve();
	return 0;
}

```


---

## 作者：lskksl (赞：0)

观察发现只会有两种方案：

**使用恰好的钱付款**或**仅使用百元大钞付款**。

不妨采用反悔贪心。

当能使用恰好的钱付款时，则使用。

当零钱不足以付款时，寻求之前某个用恰好钱付款的日子改成百元大钞。

选哪一天呢？

**关键性质：无论选哪一天，零钱数都会增加 $100$。**

~~可以自己找个样例推一下就知道了 qwq。~~

所以**选择店员不满意度增加最少的一天**,而不是 $w_{i}$ 最少的那一天。

代码比较容易实现。

---

## 作者：yyyyxh (赞：0)

## 思路
我们可以这样思考：每一天你选择找零与否获得的价值是固定的，这就意味着我们无论何时修改决策也不会有很大的复杂度。

于是我们开始考虑贪心算法：对于每个决策，我们先贪心地都选择不找零，使店员怒气值最小。万一发现了零钱不够的情况，由于找零带来的怒气是固定的，可以选出之前所造成的怒气值最小的改变决策。

>为什么不用考虑改变之前的决策为我们带来的零钱数量呢？

设 $C$ 为需付款的总数，易知找零钱数固定为 $100-(C\%10)$ ，注意之前也不用付那 $C\%10$ 元零钱，可以知道改变之前的一次决策固定为我们带来 $100$ 元零钱，而且肯定够现在决策需付的零钱。

## 注意事项
- 要用小根堆优化来选取并改变之前的决策

- 需要特判整除时所需零钱为零的情况

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct day
{	ll c,w,pap,coi,i;  //pap表示用的纸币，coi表示应该用的硬币，i为下标
	ll val;  //当选择找零时的代价
	bool sav; //决策标识
	bool operator <(const day x)const
	{	return val>x.val;   //默认大根堆，重载为大于号实现小根堆
	}
}a[100010];  
priority_queue<day> h;
ll ans;  //注意开longlong
int main()
{	ll n,change;
	cin>>n>>change;
	for (ll i=1; i<=n; i++) cin>>a[i].c;
	for (ll i=1; i<=n; i++) cin>>a[i].w;
	for (ll i=1; i<=n; i++)
	{	a[i].pap=a[i].c/100,a[i].coi=a[i].c%100,a[i].i=i;
		a[i].val=(ll)(100-a[i].coi)*a[i].w,a[i].sav=0;
		if (!a[i].coi) continue;   //特判整除的情况，不加入考虑范围
		h.push(a[i]);  //记住可能val值最小的就是本身，要提前入堆
		if (a[i].coi>change)
		{	day j=h.top(); h.pop();
			a[j.i].sav=1,ans+=j.val,change+=100; //固定加100零钱 
		}
		change-=a[i].coi;
	}
	cout<<ans<<endl;
	for (ll i=1; i<=n; i++)
		if (a[i].sav) cout<<a[i].pap+1<<" 0"<<endl;
		else cout<<a[i].pap<<" "<<a[i].coi<<endl;
	return 0;
}
```
***
[原题链接](https://www.luogu.com.cn/problem/CF767E)

---

