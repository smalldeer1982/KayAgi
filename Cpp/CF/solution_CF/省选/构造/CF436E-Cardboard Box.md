# Cardboard Box

## 题目描述

Everyone who has played Cut the Rope knows full well how the gameplay is organized. All levels in the game are divided into boxes. Initially only one box with some levels is available. Player should complete levels to earn stars, collecting stars opens new box with levels.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF436E/17b1896a1f51431c95d9715d9bee7717c44e7cec.png)Imagine that you are playing Cut the Rope for the first time. Currently you have only the levels of the first box (by the way, it is called "Cardboard Box"). Each level is characterized by two integers: $ a_{i} $ — how long it takes to complete the level for one star, $ b_{i} $ — how long it takes to complete the level for two stars $ (a_{i}<b_{i}) $ .

You want to open the next box as quickly as possible. So, you need to earn at least $ w $ stars. How do make it happen? Note that the level can be passed only once: either for one star or for two. You do not necessarily need to pass all the levels.

## 说明/提示

In the first test sample, answer 21 is also assumed correct.

## 样例 #1

### 输入

```
2 3
1 2
1 2
```

### 输出

```
3
12
```

## 样例 #2

### 输入

```
5 3
10 20
5 10
10 20
6 9
25 30
```

### 输出

```
14
01020
```

# 题解

## 作者：George1123 (赞：45)


更狼牙棒的体验 $\to$ [`George1123`](https://www.cnblogs.com/George1123/p/13970224.html)

---

## 题面

> [CF436E Cardboard Box](https://www.luogu.com.cn/problem/CF436E)

> $n$ 个关卡，对每个关卡可以花 $a_i$ 时间得到 $1$ 颗星，或花 $b_i$ 时间得到 $2$ 颗星，或不玩。问获得 $m$ 颗星最少需要多少时间。

> 数据范围：$1\le n\le 3\cdot 10^5$，$1\le m\le 2n$，$a_i<b_i$。

---

## 题解

> 蒟蒻做这题时已经知道是反悔贪心了，但是做了 $4$ 个小时做不出来。于是去看题解，感觉这个 $5$ 堆做法太非人类了，于是去看 `CF` 题解和代码后总结出了蒟蒻的不用反悔贪心的做法和题解。

如果不反悔贪心，那么每一步必须保证没有后效性地最优。

很明显如果只有 $a_i$，排序可以满足这个条件。

这题最朴素的错误做法是用一个小顶堆，刚开始把所有 $a_i$ 丢进去，然后 $m$ 次每次取堆顶，如果选了 $a_i$ 把 $b_i-a_i$ 也丢进去。 

如果 $a_i$ 都很大，$b_i-a_i$ 都很小这样显然是亏的。

假如某个 $i$ 打出 $2$ 星是当前最优，如果 $a_i$ 已经取了按照上面的办法肯定没有问题；但是如果 $a_i$ 都没取，$a_i$ 不一定是单个中的最优。

所以这篇题解最重要的骚操作就来了：选之前权衡，选两个的最优还是一个的最优：哪个更优？

可以用一个 `vis` 数组记录打了那些关卡，每次把打了的从堆中扔掉，这样就可以假定堆中的都是没有打过的了。

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define x first
#define y second
#define bg begin()
#define ed end()
#define pb push_back
#define mp make_pair
#define sz(a) int((a).size())
#define R(i,n) for(int i(0);i<(n);++i)
#define L(i,n) for(int i((n)-1);~i;--i)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=3e5,sN=N<<1;
int n,m,star[N];
ll a[sN],ns; bool vis[sN];
priority_queue<pair<ll,int>> o,t;
void ref(priority_queue<pair<ll,int>> &q){
    while(sz(q)&&vis[q.top().y]) q.pop();
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    R(i,n) cin>>a[i]>>a[i+n],a[i+n]-=a[i],
        o.push(mp(-a[i],i)),t.push(mp(-a[i]-a[i+n],i));
    while(m--){
        ref(o),ref(t);
        int i=o.top().y; o.pop(),ref(o);
        if(m&&sz(t)&&a[i]-o.top().x>=-t.top().x)
            o.push(mp(-a[i],i)),i=t.top().y,t.pop();
        i<n&&(o.push(mp(-a[i+n],i+n)),true);
        ns+=a[i],star[i%n]++,vis[i]=true;
    }
    cout<<ns<<'\n';
    R(i,n) cout<<star[i],i==n-1&&(cout<<'\n');
    return 0;
}

/*

可以考虑不反悔：权衡一个两个哪个优！

*/
```

---

**祝大家学习愉快！**

---

## 作者：lyyi2003 (赞：39)

这里有一种基于**反悔堆贪心**的做法

建议大家先做一下两道类似的题（也可以搞懂这道题后用类似的方法做这两道）：

[P1484	种树](https://www.luogu.com.cn/problem/P1484)

[ [NOI2019]序列](https://www.luogu.com.cn/problem/P5470)
    
这个题也可以用类似的做法来做

我们考虑怎么从选$i$颗星的方案拓展得到选$i+1$颗星的方案，有以下四种方式：

1. 选择一个没有选星星的位置$i$，付出$a_i$的代价选一颗星

2. 选择一个已经选了一颗星的位置$i$，然后付出$(b_i-a_i)$的代价选上第二颗星
3. 选择一个已经选了一颗星的位置$i$，再选一个没有选星星的位置$j$，将原来$i$位置上选的那颗星星反悔不选，然后在位置$j$上选上两颗星，代价$b_j-a_i$
4. 选择一个已经选了两颗星的位置$i$，再选一个没有选星星的位置$j$，将原来$i$位置上的第二颗星星反悔不选，再在$j$位置上选两颗星星，代价$b_j-(b_i-a_i)$

用堆每次从四种情况中选一种代价最小的拓展即可。

复杂度$O(nlogn)$

详细细节可以看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300007
#define LL long long
int a[N],b[N];
struct node{
	int x,i;
};
bool operator <(node a,node b){
	return a.x>b.x;
}
int ty[N];
struct queue  //可删除堆
{
	int op;
	priority_queue<node> q;
	void up(){while(!q.empty()&&ty[q.top().i]!=op)q.pop();}
	bool empty(){up();return q.empty();}
	node top(){up(); return q.top();}
	void push(node x){q.push(x);}
}q1,q2,q3,q4,q5;

void push1(int p){
	ty[p]=1;
	q2.push({b[p]-a[p],p}),q3.push({-a[p],p});
}
void push2(int p){
	ty[p]=2;
	q5.push({-(b[p]-a[p]),p});
}
void push0(int p){
	ty[p]=0; q1.push({a[p],p}),q4.push({b[p],p});
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	q1.op=q4.op=0,q2.op=q3.op=1; q5.op=2;
	for(int i=1;i<=n;i++)
		q1.push({a[i],i}),q4.push({b[i],i});
	LL ans=0;
	for(int i=1;i<=m;i++){
		int x,mi=1e9+7,op=0,p,q;
		if(!q1.empty()&&(x=q1.top().x)<mi)mi=x,p=q1.top().i,op=1;  //情况1
		if(!q2.empty()&&(x=q2.top().x)<mi)mi=x,p=q2.top().i,op=2;  //情况2
		if(!q3.empty()&&!q4.empty()&&(x=q3.top().x+q4.top().x)<mi)mi=x,p=q3.top().i,q=q4.top().i,op=3;  //情况3
		if(!q5.empty()&&!q4.empty()&&(x=q5.top().x+q4.top().x)<mi)mi=x,p=q5.top().i,q=q4.top().i,op=4;  //情况4
		ans+=mi;
		if(op==1)push1(p);
		else if(op==2)push2(p);
		else if(op==3)push0(p),push2(q);
		else push1(p),push2(q);
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++)printf("%d",ty[i]); //因为每一次拓展都会把当前位置的状态记录下来，所以最后直接输出即可
	return 0;
}

```


---

## 作者：lndjy (赞：21)

反悔贪心神仙题。我也看了题解才明白。

[反悔贪心精选题单](https://www.luogu.com.cn/training/8793)

这题难就难在，它有4种决策。简单的反悔贪心只有两种决策，直接选择和反悔。

这题的直接选择有两种：

1. 花费 $a_i$ 加 1 星。
2. 花费 $b_i-a_i$ 由 1 星变为 2 星。

反悔也有两种：

1. 把一个一星反悔成不选，再找一个选两星,花费 $b_j-a_i$。
2. 把一个两星反悔成一星，再找一个选两星，花费 $b_j+a_i-b_i$。

这个东西一个堆是没有办法维护的，需要 5 个堆。

一个维护 $a_i$ ，一个维护 $b_i-a_i$，一个维护 $-a_i$，一个维护 $b_i$ ，一个维护 $a_i-b_i$ 。

然后按照反悔贪心的常规，4 种情况选择最小值即可。

代码：
```cpp
#include<iostream>
#include<queue>
#define int long long
using namespace std;
struct node
{
	int id,num;
	bool operator <(const node &p)
	const{
		return num>p.num;
	}
};
priority_queue<node> q1,q2,q3,q4,q5;
int op1,op2=1,op3=1,op4,op5=2;
int n,w;
int a[300005],b[300005];
int ans[300005],sum;
signed main()
{
	cin>>n>>w;
	for(int i=1;i<=n;i++)
	cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++)
	{
		q1.push((node){i,a[i]});
		q4.push((node){i,b[i]});
	}
	for(int i=1;i<=w;i++)
	{
		int minn=1e10,op,p,q;
		while(!q1.empty()&&ans[q1.top().id]!=op1) q1.pop();
		if(!q1.empty()&&q1.top().num<minn)
		{
			minn=q1.top().num;
			p=q1.top().id;
			op=1;
		}
		while(!q2.empty()&&ans[q2.top().id]!=op2) q2.pop();
		if(!q2.empty()&&q2.top().num<minn)
		{
			minn=q2.top().num;
			p=q2.top().id;
			op=2;
		}
		while(!q3.empty()&&ans[q3.top().id]!=op3) q3.pop();
		while(!q4.empty()&&ans[q4.top().id]!=op4) q4.pop();
		if(!q3.empty()&&!q4.empty()&&q3.top().num+q4.top().num<minn)
		{
			minn=q3.top().num+q4.top().num;
			p=q3.top().id;q=q4.top().id;
			op=3;
		}
		while(!q4.empty()&&ans[q4.top().id]!=op4) q4.pop();
		while(!q5.empty()&&ans[q5.top().id]!=op5) q5.pop();
		if(!q5.empty()&&!q4.empty()&&q5.top().num+q4.top().num<minn)
		{
			minn=q5.top().num+q4.top().num;
			p=q5.top().id;q=q4.top().id;
			op=4;
		}
		sum+=minn;
		if(op==1)
		{
			ans[p]=1;
			q2.push({p,b[p]-a[p]});
			q3.push({p,-a[p]});
		}
		if(op==2)
		{
			ans[p]=2;
			q5.push({p,a[p]-b[p]});
		}
		if(op==3)
		{
			ans[p]=0;ans[q]=2;
			q1.push({p,a[p]});
			q4.push({p,b[p]});
			q5.push({q,a[q]-b[q]});
		}
		if(op==4)
		{
			ans[p]=1;ans[q]=2;
			q2.push({p,b[p]-a[p]});
			q3.push({p,-a[p]});	
			q5.push({q,a[q]-b[q]});		
		}
	}
	cout<<sum<<endl;
	for(int i=1;i<=n;i++)
	cout<<ans[i];
	return 0;
}
```


---

## 作者：xyf007 (赞：20)

这道题有很多的贪心方法，这里讲一种其他人没写的方法。

先将各关卡按照 $b_i$ 排序，这时我们来考虑一组最优解会满足哪些条件。  
假设选择的两星关卡中用时最长的为第 $k$ 个，那么所有 $k$ 之前的关卡都至少完成了一颗星，否则我们把 $k$ 换成前面没选的那个，答案不会变劣。  
那么我们可以枚举前 $L$ 个关卡都至少完成了一颗星，剩下的情况中，前 $L$ 个关卡可以变成两颗星，后 $n-L$ 个关卡可以变成一颗星，从中选出最小的 $m-L$ 个求和就可以了。  
这里使用了权值线段树来维护答案。

P.S 参考了 CF 的官方题解。
```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
struct level
{
    int a, b, id;
} a[300001];
struct node
{
    int cnt, ls, rs;
    long long sum;
} t[10000001];
int n, m, tot = 1, b[300001];
void pushup(int x)
{
    t[x].cnt = t[t[x].ls].cnt + t[t[x].rs].cnt;
    t[x].sum = t[t[x].ls].sum + t[t[x].rs].sum;
}
void modify(int l, int r, int p, int val, int x)
{
    if (l == r)
    {
        t[x].cnt += val;
        t[x].sum += val * l;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
    {
        if (!t[x].ls)
        {
            t[x].ls = ++tot;
        }
        modify(l, mid, p, val, t[x].ls);
    }
    else
    {
        if (!t[x].rs)
        {
            t[x].rs = ++tot;
        }
        modify(mid + 1, r, p, val, t[x].rs);
    }
    pushup(x);
}
long long query(int l, int r, int k, int x)
{
    if (l == r)
    {
        return static_cast<long long>(k) * l;
    }
    int mid = (l + r) >> 1;
    if (k <= t[t[x].ls].cnt)
    {
        return query(l, mid, k, t[x].ls);
    }
    else
    {
        return t[t[x].ls].sum + query(mid + 1, r, k - t[t[x].ls].cnt, t[x].rs);
    }
}
int main(int argc, char const *argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i].a >> a[i].b;
        a[i].id = i;
    }
    std::sort(a + 1, a + n + 1, [](const level &x, const level &y) -> bool {
        return x.b < y.b;
    });
    for (int i = 1; i <= n; i++)
    {
        modify(1, 1000000000, a[i].a, 1, 1);
    }
    long long ans = 1e18, tmp = 0;
    int pos = -1;
    for (int i = 1; i <= n && i <= m; i++)
    {
        if (m - i + 1 <= n)
        {
            if (long long t = tmp + query(1, 1000000000, m - i + 1, 1); ans > t)
            {
                ans = t;
                pos = i - 1;
            }
        }
        tmp += a[i].a;
        modify(1, 1000000000, a[i].a, -1, 1);
        modify(1, 1000000000, a[i].b - a[i].a, 1, 1);
    }
    if (m - n >= 0)
    {
        if (long long t = tmp + query(1, 1000000000, m - n, 1); ans > t)
        {
            ans = t;
            pos = n;
        }
    }
    std::cout << ans << '\n';
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    for (int i = 1; i <= pos; i++)
    {
        b[a[i].id] = 1;
        q.emplace(a[i].b - a[i].a, i);
    }
    for (int i = pos + 1; i <= n; i++)
    {
        q.emplace(a[i].a, i);
    }
    for (int i = 1; i <= m - pos; i++)
    {
        b[a[q.top().second].id]++;
        q.pop();
    }
    for (int i = 1; i <= n; i++)
    {
        std::cout << b[i];
    }
    return 0;
}
```

---

## 作者：xuanxuan001 (赞：15)

第 $2^{2^2}$ 篇题解了。

提供一个不用带反悔贪心的新解法，我是在打一次月赛的[一道题](https://www.luogu.com.cn/problem/P8439)时想出来的这个做法~~的雏形~~。

首先将 $n$ 个关卡分成两部分：$a_i \le b_i - a_i$ 和 $a_i > b_i - a_i$，然后分别求出在这两部分中获得 $i$ 颗星的代价 $dp_{0/1,i}$，如果得不到这么多就设为 INF，那么答案就是 $\min\limits_{i=0}^kdp_{0,i} + dp_{1,k - i}$。

对于第一类，把 $a_i$ 和 $b_i - a_i$ 分别放入一个堆中，由于保证 $a_i < b_i - a_i$，所以一个关卡的一星一定会在第二个星之前被计算，所以这个堆中前 $i$ 小的数的和就是 $dp_{0,i}$。

重点在于求第二类。首先有个结论：这一类中最多只会有一个关卡拿且只拿一星。下(gan)面(xing)证(li)明(jie)一下，就是设有两个关卡 $i$，$j$ 都是拿且只拿一星。不妨设 $a_i \le a_j$，那么就可以选择在第 $i$ 关拿两星而不拿第 $j$ 关的那一颗，因为有
$$
b_i = a_i + b_i - a_i < a_i + a_i \le a_i + a_j
$$
那么有了上面那个结论，就可以开始求 $dp_1$ 了。首先将这类关卡按 $b_i$ 从小到大排序，那么前 $i$ 个 $b$ 值的和就是 $dp_{1,2i}$。

然后对于 $dp_{1,2i + 1}$，选择将前 $i$ 个关卡玩到两星，然后在剩下的关卡中选择一个 $a$ 值最小的玩一星。所以只需要再处理一个后缀 $\min$ 就可以求了。

我就这么切了那道月赛题，于是我找到了那个 AC 代码一通改（顺便吐槽一下输出方案是真的烦。。。），一通 WA 之后发现 WA on #71。这次不是我写错了，而是个 hack：
```
2 3
3 5
5 6
```
这个里面的两个关卡都属于第二类。那么按照我的算法我会选择给第一关打两星，因为它的 $b_i$ 更小，但其实选择给第二关打两星更优，因为第一关的 $a_i$ 比第二关的 $a_i$ 小的量更大。

月赛没有卡我，所以我过了。

我原本以为我假了，所以已经准备写带反悔贪心了。但四天后我又想起了这道题。

前面的解法其实每步都是可以证明的，只有那个在第二类中获得 $2i+1$ 个星的部分是错的，这里已经确定要选一个关卡只打一星了，然后剩下的 $2i$ 也肯定是选除前面选的那一关以外 $b_i$ 最大的。

设打一星的那一关是第 $x$ 关，那么我前面其实是考虑了 $x > i$ 的情况下的最优解。所以……把 $x \le i$ 的情况再考虑一下不就行了吗！

那么上面那个情况可以认为是前 $i+1$ 个关卡的 $b$ 值和再减去其中的一个 $b_i - a_i$。那么对第二类的那些关卡求一个 $b_i - a_i$ 的前缀 $\max$，然后更新答案即可。

好的，这个解法死灰复燃了。

需要注意一个细节，就是在排序的时候如果 $b$ 值相同需要将 $a$ 值小的放在后面以保证后缀 $\min$ 的值正确。同理求前缀 $\max$ 时也要重新排序，将 $b-a$ 值大的放在前面。

代码（可读性比较差，见谅~~月赛写的那个更不可读~~）：
```cpp
#include<cstdio>
#include<algorithm>
#define TY ll
#define MAXN 300002
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);++i)
#define fOR(i,a,b) for(TY i=(a);i<(b);++i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);--i)
#define rOF(i,a,b) for(TY i=(a);i>(b);--i)
using namespace std;
typedef long long ll;
const TY M=998244353,INF=4e14;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(b&1)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10,0);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY n,k,dp[2][MAXN<<1],u,v,sz,db,tmp,ans=INF,num[MAXN<<1];
struct node{TY a,b,sm,id;}a[MAXN<<1],b[MAXN];bool fl[MAXN];
bool cmp1(node a,node b){if(a.sm!=b.sm)return a.sm<b.sm;else return a.a>b.a;}
bool cmp2(node a,node b){if(a.sm!=b.sm)return a.sm<b.sm;else return a.a>b.a;}
int main(){
	n=qr();k=qr();
	FOR(i,1,n){
		u=qr();v=qr()-u;
		if(v>=u){
			a[++sz]=(node){.a=0,.b=0,.sm=u,.id=i};
			a[++sz]=(node){.a=0,.b=0,.sm=v,.id=i};
		}else b[++db]=(node){.a=u,.b=v,.sm=u+v,.id=i};
	}sort(a+1,a+sz+1,cmp1);sort(b+1,b+db+1,cmp1);
	FOR(i,1,sz)dp[0][i]=dp[0][i-1]+a[i].sm;FOR(i,sz+1,k)dp[0][i]=INF;//第一类比较容易
	FOR(i,1,db)dp[1][i<<1]=(tmp+=b[i].sm);//第二类先处理2i的答案
	FOR(i,db<<1|1,k)dp[1][i]=INF;tmp=b[db].a;
	ROF(i,db-1,0){//2i+1讨论的第一种情况
		dp[1][i<<1|1]=dp[1][i<<1]+tmp;
		tmp=minn(tmp,b[i].a);
	}sort(b+1,b+db+1,cmp2);tmp=0;//重新排序后处理第二种
	FOR(i,1,db){
		tmp=maxn(tmp,b[i].b);
		if(dp[1][i*2-1]>dp[1][i<<1]-tmp){
			dp[1][i*2-1]=dp[1][i<<1]-tmp;fl[i]=true;
		}
	}FOR(i,0,k)if(ans>dp[0][i]+dp[1][k-i]){ans=dp[0][i]+dp[1][k-i];u=i;}
	tmp=ans-dp[0][u];FOR(i,1,u)++num[a[i].id];u=k-u;
	if(u&1){
		if(!fl[u=u+1>>1])sort(b+1,b+db+1,cmp1);
		fOR(i,1,u)num[b[i].id]=2;//num记录每关拿几星
		if(fl[u]){
			v=dp[1][u<<1]-tmp;num[b[u].id]=2;
			FOR(i,1,u)if(b[i].b==v){k=i;break;}
		}else{
			v=tmp-dp[1][u-1<<1];
			FOR(i,u,db)if(b[i].a==v){k=i;break;}
		}num[b[k].id]=1;
	}else ROF(i,u>>1,1)num[b[i].id]=2;
	qw(ans,'\n');FOR(i,1,n)putchar(48|num[i]);
	return 0;
}
```

---

## 作者：tzc_wk (赞：11)

[题面传送门](https://www.luogu.com.cn/problem/CF436E)

题意：

有 $n$ 个关卡，第 $i$ 个关卡玩到 $1$ 颗星需要花 $a_i$ 的时间，玩到 $2$ 颗星需要 $b_i$ 的时间。（$a_i<b_i$）

求玩到 $w$ 颗星最少需要多少时间。

$1 \leq n \leq 3 \times 10^5$

糅合一下楼下几位神仙的解法吧

首先有一个显然的错误解法：初始将所有 $a_i$ 压入优先队列，然后每次弹出优先队列中最小的值，如果它是一星的话就将 $b_i-a_i$ 压入优先队列。

hack：

```
2 2
3 4
2 5
```

下面介绍三种解法：

1. 直接对着上面的贪心进行魔改

   上面的贪心错误的原因是因为没有权衡好选择两星还是选择一星。

   我们可以再建立一个优先队列保存当前零星的关卡中，$b_i$ 的最小值。

   如果我们发现，当前零星的关卡中 $b_i$ 的最小值 $<$ 一星的最小的两个值之和。

   那么我们就把 $i$ 关卡玩到一星，并将 $b_i-a_i$ 压入一星的队列当中。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
const int MAXN=3e5+5;
int n,m,a[MAXN<<1],vis[MAXN<<1],star[MAXN];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > o,t;
void clear(priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > &q){
	while(!q.empty()&&vis[q.top().se]) q.pop();
}
int main(){
	scanf("%d%d",&n,&m);for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&a[i+n]),a[i+n]-=a[i];
	for(int i=1;i<=n;i++) o.push(mp(a[i],i)),t.push(mp(a[i]+a[i+n],i));
	ll ans=0;
	while(m--){
        clear(o);clear(t);
        int i=o.top().se;o.pop();clear(o);
        if(m&&t.size()&&a[i]+o.top().fi>=t.top().fi)
            o.push(mp(a[i],i)),i=t.top().se,t.pop();
        if(i<=n) o.push(mp(a[i+n],i+n));
        ans+=a[i];star[(i>n)?(i-n):i]++;vis[i]=true;
    } printf("%lld\n",ans);
    for(int i=1;i<=n;i++) printf("%d",star[i]);
	return 0;
}
```

2. 反悔贪心

   考虑每次增加一颗星星，取最小的增加方式。

   按照最朴素的贪心有两种增加方式：

   I. 将一个零星的关卡 $i$ 改为一星，代价为 $a_i$

   II. 将一个一星的关卡 $i$ 改为两星，代价为 $b_i-a_i$

   我们利用返回贪心的思想，还有两种反悔方式：

   III. 将一个一星关卡 $i$ 改为零星关卡，并将一个零星关卡 $j$ 改为两星关卡，代价为 $b_j-a_i$

   IV. 将一个两星关卡 $i$ 改为一星关卡，并将一个零星关卡 $j$ 改为两星关卡，代价为 $b_j-(b_i-a_i)$

   考虑怎样维护这个最小值，我们建立五个小根堆：

   $q_1:\min\{a_i|star_i=0\}$

   $q_2:\min\{b_i-a_i|star_i=1\}$

   $q_3:\min\{b_i|star_i=0\}$

   $q_4:\min\{-a_i|star_i=1\}$

   $q_5:\min\{-b_i+a_i|star_i=2\}$

   对于方式 I，取出 $q_1$ 的队首。

   对于方式 II，取出 $q_2$ 的队首。

   对于方式 III，取出 $q_3$ 和 $q_4$ 的队首并将它们相加。

   对于方式 III，取出 $q_3$ 和 $q_5$ 的队首并将它们相加。

   还有个注意点：有些关卡星值的修改会牵扯到两个堆，我们要在每一次取状态时判断状态是否满足，不满足就 pop 掉。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
const ll INF=1e18;
const int MAXN=3e5+5;
int n,m,a[MAXN],b[MAXN],star[MAXN];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > q1,q2,q3,q4,q5;
//q1: min{a[i]} star[i]=0
//q2: min{b[i]-a[i]} star[i]=1
//q3: min{b[i]} star[i]=0
//q4: min{-a[i]} star[i]=1
//q5: min{-b[i]+a[i]} star[i]=2
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	q1.push(mp(INF,n+1));q2.push(mp(INF,n+1));q3.push(mp(INF,n+1));
	q4.push(mp(INF,n+1));q5.push(mp(INF,n+1));star[n+1]=-1;
	for(int i=1;i<=n;i++) q1.push(mp(a[i],i)),q3.push(mp(b[i],i));
	ll ans=0;
	for(int i=1;i<=m;i++){
		while(q1.size()>1&&star[q1.top().se]!=0) q1.pop();
		while(q2.size()>1&&star[q2.top().se]!=1) q2.pop();
		while(q3.size()>1&&star[q3.top().se]!=0) q3.pop();
		while(q4.size()>1&&star[q4.top().se]!=1) q4.pop();
		while(q5.size()>1&&star[q5.top().se]!=2) q5.pop();
		ll x1=q1.top().fi,x2=q2.top().fi,x3=q3.top().fi+q4.top().fi,x4=q3.top().fi+q5.top().fi;
		ll mn=min(min(x1,x2),min(x3,x4));ans+=mn;
//		printf("%lld\n",mn);
		if(x1==mn){
			int j=q1.top().se;star[j]=1;q1.pop();
			q2.push(mp(b[j]-a[j],j));q4.push(mp(-a[j],j));
		} else if(x2==mn){
			int j=q2.top().se;star[j]=2;q2.pop();
			q5.push(mp(-b[j]+a[j],j));
		} else if(x3==mn){
			int j1=q3.top().se,j2=q4.top().se;
			star[j1]=2;star[j2]=0;q3.pop();q4.pop();
			q5.push(mp(-b[j1]+a[j1],j1));
			q1.push(mp(a[j2],j2));q3.push(mp(b[j2],j2));
		} else{
			int j1=q3.top().se,j2=q5.top().se;
			star[j1]=2;star[j2]=1;q3.pop();q5.pop();
			q5.push(mp(-b[j1]+a[j1],j1));
			q2.push(mp(b[j2]-a[j2],j2));q4.push(mp(-a[j2],j2));
		}
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++) printf("%d",star[i]);
	return 0;
}
```

   

3. 数据结构

   我们将这 $n$ 个关卡按 $b_i$ 从小到大排序。

   假设我们选择的**两星**的关卡中 $b_i$ 最大的为关卡 $l$，那么在关卡 $l$ 前面的所有关卡都至少选择了一颗星（注意我们已经按 $b_i$ 从小到大排好序了）。

   为什么呢？很简单，如果有一个关卡 $j$ 一颗星都没选，那么把 $b_l$ 改为零星，$b_j$ 改为两星肯定更优。

   又因为关卡 $l$ 是选择的两星的关卡中 $b_i$ 最大的一个，所以在 $l$ 后面的关卡至多选了一星。

   维护 $c_i=\begin{cases}b_i-a_i&(i\leq l)\\a_i&(i>l)\end{cases}$

   然后取 $c_i$ 最小的 $w-l$ 个就行了。

   实现方式很多，我使用的是将 $b_i-a_i$ 与 $a_i$ 揉在一起离散化，然后线段树上二分。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
bool chkmin(ll &x,ll y){return ((x>y)?(x=y,1):0);}
bool chkmax(ll &x,ll y){return ((x<y)?(x=y,1):0);}
const int MAXN=3e5+5;
int n,w,a[MAXN],b[MAXN],key[MAXN<<1],hs[MAXN<<1],cnt=0,num=0,ord[MAXN];
int get(int x){return lower_bound(hs+1,hs+num+1,x)-hs;}
struct node{
	int l,r,c;ll v;
} s[MAXN<<3];
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r) return;
	int mid=(l+r)>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
void modify(int k,int x,int addv,int addc){
	if(s[k].l==s[k].r){s[k].c+=addc;s[k].v+=addv;return;}
	int mid=(s[k].l+s[k].r)>>1;
	if(x<=mid) modify(k<<1,x,addv,addc);
	else modify(k<<1|1,x,addv,addc);
	s[k].c=s[k<<1].c+s[k<<1|1].c;
	s[k].v=s[k<<1].v+s[k<<1|1].v;
}
ll query(int k,int c){
	if(s[k].l==s[k].r) return 1ll*c*hs[s[k].l];
	if(c>=s[k<<1].c) return s[k<<1].v+query(k<<1|1,c-s[k<<1].c);
	else return query(k<<1,c);
}
bool cmp(int x,int y){return b[x]<b[y];}
int star[MAXN];pii p[MAXN];
int main(){
	scanf("%d%d",&n,&w);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;i++) ord[i]=i;sort(ord+1,ord+n+1,cmp);
//	for(int i=1;i<=n;i++) printf("%d\n",ord[i]);
	for(int i=1;i<=n;i++) key[++cnt]=a[i],key[++cnt]=b[i]-a[i];
	sort(key+1,key+cnt+1);
	for(int i=1;i<=cnt;i++) if(key[i]!=key[i-1]) hs[++num]=key[i];
	build(1,1,num);
	for(int i=1;i<=n;i++) modify(1,get(a[i]),a[i],1);
	ll ans=1e18,sum=0;if(w<=n) ans=min(ans,query(1,w));
	int pos=0;
	for(int i=1;i<=n;i++){
		modify(1,get(a[ord[i]]),-a[ord[i]],-1);
		modify(1,get(b[ord[i]]-a[ord[i]]),b[ord[i]]-a[ord[i]],1);
		sum+=a[ord[i]];//printf("%lld\n",sum);
//		printf("%lld\n",query(1,w-i));
		if(w-i<=n&&w-i>=0) if(chkmin(ans,query(1,w-i)+sum)) pos=i;
	} printf("%lld\n",ans);
	for(int i=1;i<=pos;i++) star[ord[i]]++;
	for(int i=1;i<=pos;i++) p[i]=mp(b[ord[i]]-a[ord[i]],ord[i]);
	for(int i=pos+1;i<=n;i++) p[i]=mp(a[ord[i]],ord[i]);
	sort(p+1,p+n+1);for(int i=1;i<=w-pos;i++) star[p[i].se]++;
	for(int i=1;i<=n;i++) printf("%d",star[i]);
	return 0;
}
```

---

## 作者：0htoAi (赞：11)

前言：借鉴了 @George1123 的做法，在此基础上改良，另外变得好理解了。经过改良，我的做法比他的做法快了 $4$ 倍，目前是最优解。

#### 大体思路：

需要权衡的是直接花 $b_i$ 得 $2$ 个星星还是花 $2$ 个不同的 $a_i$ 得 $2$ 个星星，如何对比这两种情况哪个更优是最大的问题。

开 $2$ 个小根堆维护 $a_i$ 和 $b_i$ 的最小值，然后开始贪心。

#### 贪心过程：

目的是要选当前最优，设当前 $q_a$ 堆的最小值为 $a_{min}$，$q_b$ 堆的最小值为 $b_{min}$，可以假设它们不是同一个 $i$。

显然直接比较 $\frac{b_{min}}{2}$ 和 $a_{min}$ 的大小是不对的，因为可能 $a_{min}$ 所对应的 $b$ 的值比 $a_{min}$ 大不了多少。

于是又取出 $q_a$ 堆除去 $a_{min}$ 的最小值 $a_{min2}$，也可以假设 $a_{min2}$ 与 $b_{min}$ 不是同一个 $i$。

现在可以直接比较 $a_{min}+a_{min2}$ 和 $b_{min}$ 的大小了。因为现在要选 $2$ 个星星出来，这两种必定有一种是最优情况。

考虑分类讨论：

* $a_{min}+a_{min2} \leq b_{min}$ 时：

  （注：取等时无论怎么处理结果一样）

  连取 $2$ 个 $1$ 星更优，答案加上 $a_{min}+a_{min2}$，用到 $a_{min}$ 和 $a_{min2}$ 所对应的 $i$ 的次数各增加 $1$。

  对于 $a_{min}$ 和 $a_{min2}$ 所对应的 $2$ 个 $i$，如果 $i$ 是第一次被用到，那么 $q_a$ 堆中还要新加进一个权值为 $b_i-a_i$ 的星星，表示可以增加 $b_i-a_i$ 的代价多得到 $1$ 个星星，跟普通星星无差异。

  此时注意，要在 $q_b$ 堆中删除 $i$ 这个点，因为它已经不能一次取 $2$ 个星星了，可以用堆的常用操作懒删除，等 $i$ 到堆顶的时候再删。 

* $a_{min}+a_{min2} > b_{min}$ 时：

  直接取 $1$ 个 $2$ 星最优，答案加上 $b_{min}$，用到 $b_{min}$ 所对应的 $i$ 的次数为 $2$。

  将 $a_{min}$ 和 $a_{min2}$ 重新入 $q_a$ 堆，在 $q_a$ 中删除 $b_{min}$ 所对应的点，同理也可以使用懒删除。

#### 小细节：

* 因为每次贪心都是取 $2$ 个星星，如果 $w$ 为奇数该怎么办？

  如果 $w$ 为奇数则在最开始向 $q_a$ 增加一个编号为 $0$，权值为 $0$ 的点，相当于白送一个星星，并将 $w$ 变成 $w+1$。注意这个 $0$ 号点要标记为使用过一次，以免再次入堆。

* $w=2 \times n$ 时会出现 ```RE```，具体原因是因为 $q_a$ 最后会只有 $1$ 个元素，怎么处理？

  特判掉这种情况，如果遇到了直接全选 $b_i$ 就好。

---

## 作者：whiteqwq (赞：10)

[CF436E Cardboard Box](https://www.luogu.com.cn/problem/CF436E)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1746671)
## 题意
- $n$个关卡，每个关卡可以获得$0$星，$1$星和$2$星；
- 获得$1$星的代价为$a_i$，获得$2$星的代价为$b_i$；
- 求获得**恰好**$k$个星星的最小代价
- $1\leqslant n\leqslant 3\cdot 10^5,1\leqslant k\leqslant 2\cdot n$

## 分析
第一眼，很显然可以看出一个$O(n\cdot k)$的dp做法（设$f_{i,j}$代表前$i$个关卡获得$j$个星星的最小代价），但是这个复杂度无法通过本题。

首先，可以使用一个贪心思想：每一次增加**一颗**星星，取**最小的增加方式**。

我们考虑一个贪心策略：不断选最小$a_i$的零星关卡改成一星关卡，或者把一个一星关卡改成二星关卡（贪心地选已经有一星且$b_i-a_i$最小的关卡），但是这个贪心很显然是错误的。

hack：
```
2 3
4 1
1 9
```

普通贪心不行，我们可以进行**反悔贪心**，建议先做一道题了解一下反悔贪心：[CF865D Buy Low Sell High](https://www.luogu.com.cn/problem/CF865D)。

重申一下贪心的思想：每一次增加**一颗**星星，取**最小的增加方式**。

此时贪心策略有两种：
1. 零星关卡$i$改一星关卡$i$；
2. 一星关卡$i$改二星关卡$i$。

想一想怎么通过反悔之前的操作来增加一颗星星（即反悔策略）：
1. 一星关卡$i$改零星关卡$i$，并将一个零星关卡$j$改成二星关卡；
2. 二星关卡$i$改一星关卡$i$，并将一个零星关卡$j$改成二星关卡。

注意，普通贪心二**并不能**归入反悔贪心一，因为反悔策略一本质是把一个零星关卡改成二星关卡，而贪心策略二本质是把一个一星关卡改成二星关卡，在维护时会有差别。

现在考虑如何维护这四个策略：
（注意，代码中**小根堆是用大根堆权值取负来实现的**）
1. 贪心策略1：对答案的贡献为$a_i$，用小根堆$q1$来维护零星关卡的$a$；
2. 贪心策略2：对答案的贡献为$b_i-a_i$，用小根堆$q5$来维护一星关卡的$b-a$；
3. 反悔策略1：对答案的贡献为$b_j-a_i$，我们可以把式子拆成$b_j$和$-a_i$，用小根堆$q3$维护零星关卡$b$的最小值，用大根堆$q2$维护一星关卡$a$的最大值；
4. 反悔策略2：对答案的贡献为$b_j+a_i-b_i$，我们可以把式子拆成$b_j$和$-(b_i-a_i)$，用小根堆$q3$维护零星关卡$b$的最小值，用大根堆$q4$维护二星关卡$b_i-a_i$的最大值。

还要注意一个细节：有些关卡星值的修改会**牵扯到两个堆**，此时我们就不能单纯只$\text{pop}$当前的状态了，还要在每一次取状态时判断状态是否满足，不满足就**直接**$\text{pop}$掉。

注意这里可以直接$\text{pop}$的原因是**反悔之后的关卡一定不会再次进行反悔**。（否则就一定不优了）

时间复杂度：因为每个点最多进行一次贪心选出，一次反悔，加上优先队列，故复杂度为：$O(n\log n)$。

## 代码
需要注意的地方：

- long long，inf要开大
- 优先队列塞入边界值

```
#include<stdio.h>
#include<queue>
#define int long long
#define inf 100000000000000000
using namespace std;
const int maxn=300005;
int n,m,anss;
int a[maxn],b[maxn],ans[maxn];
priority_queue< pair<int,int> >q1,q2,q3,q4,q5;
//q1 min{a|a选0}
//q2 max{a|a选1}
//q3 min{b|b选0}
//q4 max{b-a|b选2}
//q5 min{b-a|a选1}
inline void add_0(int x){//加入0
	ans[x]=0;
	q1.push(make_pair(-a[x],x));
	q3.push(make_pair(-b[x],x));
}
inline void add_1(int x){//加入1
	ans[x]=1;
	q2.push(make_pair(a[x],x));
	q5.push(make_pair(-(b[x]-a[x]),x));
}
inline void add_2(int x){//加入2
	ans[x]=2;
	q4.push(make_pair(b[x]-a[x],x));
}
signed main(){
	scanf("%lld%lld",&n,&m);
	//优先队列插入初值
	q1.push(make_pair(-inf,n+1));
	q2.push(make_pair(-inf,n+1));
	q3.push(make_pair(-inf,n+1));
	q4.push(make_pair(-inf,n+1));
	q5.push(make_pair(-inf,n+1));
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		add_0(i);//初始星值是0
	}
	for(int k=1;k<=m;k++){//不断增加一个星星
		int p1=q1.top().second,p2=q2.top().second,p3=q3.top().second,p4=q4.top().second,p5=q5.top().second;
		while(q1.size()>1&&ans[p1]!=0)
			q1.pop(),p1=q1.top().second;
		while(q2.size()>1&&ans[p2]!=1)
			q2.pop(),p2=q2.top().second;
		while(q3.size()>1&&ans[p3]!=0)
			q3.pop(),p3=q3.top().second;
		while(q4.size()>1&&ans[p4]!=2)
			q4.pop(),p4=q4.top().second;
		while(q5.size()>1&&ans[p5]!=1)
			q5.pop(),p5=q5.top().second;
		int k1=-q1.top().first,k2=q2.top().first,k3=-q3.top().first,k4=q4.top().first,k5=-q5.top().first;
		int t1=k1,t2=k5,t3=k3-k2,t4=k3-k4;
		int minn=min(min(t1,t2),min(t3,t4));
		//注:这里i指已选的点，j指未选的点
		if(t1==minn){
			//贪心策略1:选一星(0->a[i])
			anss+=t1;
			q1.pop();
			add_1(p1);
		}
		else if(t2==minn){
			//贪心策略2:一星改成二星(a[i]->b[i])
			anss+=t2;
			q5.pop();
			add_2(p5);
		}
		else if(t3==minn){
			//反悔策略1:一个一星改零星，选另一个二星(a[i]->b[j])
			anss+=t3;
			q2.pop(),q3.pop();
			add_0(p2),add_2(p3);
		}
		else{
			//反悔策略2:一个二星改一星，选另一个二星(b[i]->a[i]+b[j])
			anss+=t4;
			q3.pop(),q4.pop();
			add_1(p4),add_2(p3);
		}
	}
	printf("%lld\n",anss);
	for(int i=1;i<=n;i++)
		printf("%lld",ans[i]);
	puts("");
	return 0;
}
```

---

## 作者：feecle6418 (赞：8)

如果已经决定了要玩哪些关卡，一定是把这些关卡中 $b-a$ 较小的那一些玩到二星。

把所有关卡按照 $b-a$ 排序，一定存在一个分界线，分界线前（只要玩了）全玩到二星，分界线后（只要玩了）全玩到一星，显然界前和界后都选最小的那些。

假设有 $p$ 个关卡玩到二星，这时界线前要选前 $p$ 小的 $b$，界线后要选前 $w-2p$ 小的 $a$，这个代价显然关于 $p$ 凸。

使用权值线段树等维护前 $k$ 小值，配上二分 / 三分，复杂度 $O(n \log^2 n)$。

事实上上面的做法常数很大而且很难写。

经过观察可以发现，对于给定界线 $i$ 而言代价 $f_i(p)$ 凸，但是对于整个问题的答案而言，$\min_{i}f_i(p)$ 对于 $p$ 也是凸的（这我不会证）。对 $p$ 二分 / 三分，对顶堆维护前 $p$ 小值即可。

复杂度不变，常数很小。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Heap{
 
priority_queue<int> s1;
priority_queue<int,vector<int>,greater<int> > s2;
int K;
ll sum=0;
void Do(){
	while(s1.size()>K){
		int u=s1.top();
		s1.pop(),s2.push(u),sum-=u;
	}
	while(s1.size()<K&&s2.size()){
		int u=s2.top();
		s2.pop(),s1.push(u),sum+=u;
	}
}
void Ins(int x){
	s1.push(x),sum+=x,Do();
}
void Makek(int k){
	K=k,Do();
}
ll Query(){
	if(s1.size()<K)return 1e18;
	return sum;
}
void Clear(){
	priority_queue<int> t1;
	priority_queue<int,vector<int>,greater<int> > t2;
	swap(s1,t1),swap(s2,t2),sum=0;
}
 
}a1,a2;
int n,w,ans[300005];
ll f[300005];
struct Thing{
	int a,b,id;
}a[300005];
ll Get(int i,bool is=0){
	int j=w-2*i;
	a1.Clear(),a2.Clear();
	a1.Makek(i),a2.Makek(j);
	ll mn=1e18;
	int pos=0;
	for(int k=n+1;k>=1;k--){
		if(k<=n)a2.Ins(a[k].a);
		f[k]=a2.Query();
	}
	for(int k=0;k<=n;k++){
		if(k)a1.Ins(a[k].b);
		ll w=a1.Query()+f[k+1];
		if(w<mn)mn=w,pos=k;
	}
	if(is){
		cout<<mn<<'\n';
		vector<Thing> tmp;
		for(int k=1;k<=pos;k++)tmp.push_back(a[k]);
		sort(tmp.begin(),tmp.end(),[](Thing x,Thing y){return x.b<y.b;});
		for(int k=0;k<i;k++)ans[tmp[k].id]=2;
		tmp.clear();
		for(int k=pos+1;k<=n;k++)tmp.push_back(a[k]);
		sort(tmp.begin(),tmp.end(),[](Thing x,Thing y){return x.a<y.a;});
		for(int k=0;k<j;k++)ans[tmp[k].id]=1;
		for(int k=1;k<=n;k++)cout<<ans[k];
	}
	return mn;
}
int main(){
	scanf("%d%d",&n,&w);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].a,&a[i].b),a[i].id=i;
	sort(a+1,a+n+1,[](Thing x,Thing y){return x.b-x.a<y.b-y.a;});
	int L=-1,R;
	for(int i=0;i<=n;i++){
		int j=w-2*i;
		if(j<0||i+j>n)continue;
		if(L==-1)L=i;
		R=i;
	}
	while(L<R){
		int mid=(L+R)/2;
		if(Get(mid)<Get(mid+1))R=mid;
		else L=mid+1;
	}
	Get(L,1);
}
```

---

## 作者：mazihang2022 (赞：7)

提供一种不一样的思路？

容易发现一个结论：一般来讲，若关卡 $i$ 满足 $b_i\le 2\cdot a_i$，则该关要么 $0$ 星，要么 $2$ 星。更进一步地，所有关卡中最多只有一关不满足该结论。

等价结论：若存在两个关卡 $i$ 和 $j$（假设 $a_i\le a_j$）满足上述条件并且两个关卡都是 $1$ 星，则将第 $i$ 关调整为 $2$ 星，将第 $j$ 关调整为 $0$ 星不会使答案更劣。因为 $b_i\le 2\cdot a_i\le a_i+a_j$ 所以该结论成立。

考虑对两种不同关卡分开处理。

对于 $b_i\le2\cdot a_i$ 的关卡，直接扔进堆中，代价为 $b_i$，选一次得两颗星。

对于 $b_i\gt2\cdot a_i$ 的关卡，我们直接将该关拆成代价分别为 $a_i$ 和 $b_i-a_i$ 的两颗星，将拆分出来的每颗星扔进堆中即可。因为 $b_i-a_i\gt a_i$，所以选取时肯定是依次选出某关的两颗星的。

每次取出两个堆中代价最小的比较单价（代价除以星数），选取小的即可。经过一些选取后 $w=1$ 时需要特判（具体可见代码）。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fir first
#define sec second
using namespace std;

const int maxn=300005;
const int inf=0x7fffffff;

int n,m;
int a[maxn];
int b[maxn];
int vis[maxn];

pair<int,int> getmin() {
	int ans=inf,id=-1;
	for(int i=1;i<=n;i++) {
		if(!vis[i]&&a[i]<ans) { 
			ans=a[i],id=i;
		} else if(vis[i]==1&&b[i]-a[i]<ans) { 
			ans=b[i]-a[i],id=i;
		}
	}
	return {ans,id};
}

pair<int,int> getmax() {
	int ans=0,id=-1;
	for(int i=1;i<=n;i++) {
		if(vis[i]==1&&a[i]>ans) {
			ans=a[i],id=i;
		} else if(vis[i]==2&&b[i]-a[i]>ans) {
			ans=b[i]-a[i],id=i;
		}
	}
	return {ans,id};
}

signed main() {
	n=read(),m=read();
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q1,q2;
	for(int i=1;i<=n;i++) {
		a[i]=read(),b[i]=read();
		if(b[i]<=2*a[i]) {
			q1.push({b[i],i});
		} else {
			q2.push({a[i],i}),q2.push({b[i]-a[i],i});
		}
	}
	ll ans=0;
	while(true) {
		int x=q1.size()?q1.top().fir:inf,y=q2.size()?q2.top().fir:inf;
		if(m==1) {
			auto a=getmax(),b=getmin();
			int p=x-a.fir,q=b.fir;
			if(p<=q) {
				vis[q1.top().sec]=2,vis[a.sec]--;
			} else {
				vis[b.sec]++;
			}
			ans+=min(p,q);
			break;
		}
		if(y==inf||y*2>=x) {
			vis[q1.top().sec]=2;
			q1.pop(),ans+=x,m-=2;
		} else {
			vis[q2.top().sec]++;
			q2.pop(),ans+=y,m--;
		}
		if(!m) {
			break;
		}
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++) {
		putchar('0'+vis[i]);
	}
	putchar('\n');
}
```

---

## 作者：ListenSnow (赞：3)


## 题意

$n$ 个关卡，对每个关卡，你可以花 $a_i$ 代价得到一颗星，也可以花 $b_i$
代价得到两颗星，也可以不玩。问获得 $w$ 颗星最少需要多少时间。

#### 数据范围

$1 \leq n \leq 300000,1 \leq w \leq 2n$。

### 思路

对于本题有一个很直接的想法，把花费 $b_i$ 看成是花费 $a_i$ 得到一颗星以后再花费 $b_i-a_i$ 的代价再得到一颗星。

如果直接用小根堆 $q1$ 维护最小代价，每次选第一颗星后把第二颗星插入堆中，得到的答案不一定是最优的。因为假设现在还需 $2$ 颗星，贪心的选了 $i$ 的第二颗星，再选 $j$ 大一点的第一颗星，可能并不比直接选 $j$ 的二颗星的代价小（也就是没有考虑选第一颗星后再插入的第二颗星的代价）。

可以再开一个小根堆 $q2$ 来维护同时取两颗星的代价。每次取出时判断一下是零散地选两颗星代价小还是一次性取两颗星代价小。但是需要注意，如果一次性选两颗星代价更小，不能直接把两颗都取走，这是因为取了第一颗星后，并不保证取第二颗星和另一颗星的代价就比 $q2$ 此时的最小值更优（如 $2,2,6,10,8,11$ 这组数据，如果直接取完，得到的答案是 $18$，但最优解是 $17$）。只能说这种选法比零散的选法一定更优或者等价，但取出一个后就不一定是最优的了（如果取第二颗星的代价实在太小了，那么也会被再次取出）。

同时由于 $q1$ 和 $q2$ 中维护的是相同元素，于是需要用一个数组记录该星是否被选过（也方便最后输出答案），如果当前堆顶的元素已经被使用过了就弹出，直到没有被使用过。


### code：
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=6e5+10;
#define LL long long
int n,m,a[N];LL ans;bool vis[N];
struct node{int id;LL val;bool operator <(const node &t)const{return val>t.val;};};
priority_queue<node> q1,q2;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&a[i+n]),a[i+n]-=a[i],q1.push(node{i,a[i]}),q2.push(node{i,a[i+n]+a[i]});
	while(m--)
	{
		while(q1.size()&&vis[q1.top().id]) q1.pop();
		while(q2.size()&&vis[q2.top().id]) q2.pop();
		int now=q1.top().id;q1.pop();
		while(q1.size()&&vis[q1.top().id]) q1.pop();
		if(m&&q2.size()&&a[now]+q1.top().val>=q2.top().val){q1.push(node{now,a[now]});now=q2.top().id;q2.pop();}
		if(now<=n) q1.push(node{now+n,a[now+n]});ans+=a[now];vis[now]=true;
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++) printf("%d",vis[i]+vis[n+i]);puts("");
	return 0;
}
```


---

## 作者：xzy090626 (赞：2)

声明：这篇题解的做法是乱搞。

反悔贪心过于难做了，我们考虑乱搞。

先想暴力怎么做。显然是 $O(nw)$ 做一遍 dp。但是我们发现大部分状态没啥用，考虑怎么砍掉这些无用的状态。

首先 shuffle 一遍序列，我们发现如果 $n$ 个位置的总和是 $w$，那么平均每个位置就是 $w\over n$，前 $i$ 个位置就是 $wi\over n$，即前 $i$ 个位置期望的背包空间是 $k={wi\over n}$。那我们考虑设一个长度 $m$，只对 $[k-m,k+m]$ 的状态进行 dp 的转移，其它的照搬之前的状态。这个通过滚动数组可以容易地实现。

然后考虑 $m$ 取多少比较合适。由于还要记录方案，可以直接开到空间极限，这里我取的是 $\sqrt w$。然后注意记录方案的时候为了避免被卡空间，要用一些小技巧，另外要用 bitset 记录一下选了哪个方案，详见代码中。

复杂度就是 $O(n\sqrt n)$，虽然这个具体的出错概率我不太会算，但是的确在 CF 数据上可以通过。因此，在 OI 赛制中在充分了解正确率的情况下，使用这个是有利而无弊的。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cmath>
#include<string>
#include<set>
#include<map>
#include<unordered_map>
#include<queue>
#include<time.h>
#include<bitset>
#include<random>
#include<iomanip>
#include<assert.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define pb push_back
using namespace std;
const int N = 6e5 + 7;
int n,w,dp[2][N];
pair<pii,int>s[N];
int l[N],r[N];
bitset<1500>f[2][N];
char ans[N];
signed main(){
	srand(time(0));
	memset(dp,0x3f,sizeof dp);
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>w;
	int m = sqrt(n*2);
	for(int i=1;i<=n;++i) cin>>s[i].x.x>>s[i].x.y,s[i].y = i;
	random_shuffle(s+1,s+n+1);
	dp[0][0] = 0;
	for(int i=1;i<=n;++i){
		int pos = w * i / n;
		l[i] = max(0ll,pos-m);
		r[i] = min({i*2,w,pos+m});
		for(int j=l[i];j<=r[i];++j){
			dp[i%2][j] = dp[1^i%2][j]; f[0][i][j-l[i]] = 1;
			if(j && dp[1^i%2][j-1]+s[i].x.x<dp[i%2][j]) dp[i%2][j] = dp[1^i%2][j-1]+s[i].x.x, f[1][i][j-l[i]] = 1,f[0][i][j-l[i]] = 0;
			if(j>=2 && dp[1^i%2][j-2]+s[i].x.y<dp[i%2][j]) dp[i%2][j] = dp[1^i%2][j-2]+s[i].x.y,f[0][i][j-l[i]] = f[1][i][j-l[i]] = 0;
		}
	}
	cout<<dp[n%2][w]<<'\n';
	int x = n,y = w;
	while(x>=1){
		bool ff = 0;
		for(int i=1;i>=0;--i){
			if(f[i][x][y-l[x]]){
				ans[s[x].y] = '0' + i;
				x--,y -= i;
				ff = 1;
				break;
			}
		}
		if(!ff) ans[s[x--].y] = '2',y-=2;
	}
	cout<<(ans+1);
	return 0;
}
```
注意这份代码要在 C++ 17 下提交。实际时间和空间都不算特别极限。

---

## 作者：Farkas_W (赞：2)

$$\texttt{前言}$$

$\quad$都是本机房 [@lyyi2003](https://www.luogu.com.cn/user/100806#practice) $dalao$ 教的，请各位先膜 [@lyyi2003](https://www.luogu.com.cn/user/100806#practice)。

$$\texttt{关于本题}$$

$\quad$此题一看就是反悔贪心，没有学过的请出门左转[浅谈反悔贪心](https://www.luogu.com.cn/blog/Farkas/qian-tan-fan-hui-tan-xin)或[Farkas_W的反悔贪心题单](https://www.luogu.com.cn/training/38261#problems)。

$\quad$考虑此题每次加一颗星星有几种状态需要考虑：
1. 从未选星星的关卡中选一个代价最小的星星。
2. 从已选一颗星星的关卡中选一个关卡使它再加一颗星星。
3. 从已选一颗的关卡中选一个代价最大的，再从未选星星的关卡中选一个两颗星星的和最小的，将已选的一颗反悔，加上两颗星星。
4. 从已选两颗星星的关卡中选一个第二颗星星代价最大的，再从未选星星的关卡选上两颗星星。

发现每次多选一个星星只有这四种情况，开五个堆同时维护五个序列(用 $a_i$，$b_i$ 分别表示选一颗星星或两颗星星的代价)：

1. 在一颗星星也没有选的关卡中按 $a_i$ 从小到大排序
2. 在选了一颗星星的关卡中按 $a_i$ 从大到小排序
3. 在选了一颗星星的关卡中按 $b_i-a_i$ 从小到大排序
4. 在选了两颗星星的关卡中按 $b_i-a_i$ 从大到小排序
1. 在一颗星星也没有选的关卡中按 $b_i$ 从小到大排序

$\quad$建 $5$ 个堆，分别算出四种答案的代价，每次选最小的，修改它的星星数量，然后将改变了的放入新的堆里(根据改变后的星星的数量来放)即可。

```cpp
//马蜂有点丑，还请见谅
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define re register int
#define il inline
#define inf 1e9+5
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(long long x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=3e5+5;
int n,m,b[N];
long long ans;
struct node{
  int x,y,id;
}a[N];
struct node1{
  int x,y,id;
  il bool operator<(const node1 &hh)const
  {return x>hh.x;}//x xiao->da  b[i]=0;
};
priority_queue<node1>q1;
struct node2{
  int x,y,id;
  il bool operator<(const node2 &hh)const
  {return x<hh.x;}//x da->xiao  b[i]=1;
};
priority_queue<node2>q2;
struct node3{
  int x,y,id;
  il bool operator<(const node3 &hh)const
  {return (y-x)>(hh.y-hh.x);}//y-x  xiao->da   b[i]=1;
};
priority_queue<node3>q3;
struct node4{
  int x,y,id;
  il bool operator<(const node4 &hh)const
  {return (y-x)<(hh.y-hh.x);}//y-x  da->xiao    b[i]=2;
};
priority_queue<node4>q4;
struct node5{
  int x,y,id;
  il bool operator<(const node5 &hh)const
  {return y>hh.y;}//y xiao->da   b[i]=0;
};
priority_queue<node5>q5;
signed main()
{
  n=read();m=read();
  for(re i=1;i<=n;i++)
    {
      a[i].x=read();a[i].y=read();a[i].id=i;
      q1.push((node1){a[i].x,a[i].y,i});
      q5.push((node5){a[i].x,a[i].y,i});
    }
  for(re i=1;i<=m;i++)
    {
      int t1,t2,t3,t4;t1=t2=t3=t4=inf;//初始为inf极大值
      while(!q1.empty()&&b[q1.top().id]!=0)q1.pop();//保证堆顶符合条件，因为它有可能已经被改变了
      while(!q2.empty()&&b[q2.top().id]!=1)q2.pop();
      while(!q3.empty()&&b[q3.top().id]!=1)q3.pop();
      while(!q4.empty()&&b[q4.top().id]!=2)q4.pop();
      while(!q5.empty()&&b[q5.top().id]!=0)q5.pop();
      if(!q1.empty())t1=q1.top().x;//分别计算四种选择的代价
      if(!q3.empty())t2=q3.top().y-q3.top().x;
      if(!q5.empty()&&!q2.empty())t3=q5.top().y-q2.top().x;
      if(!q5.empty()&&!q4.empty())t4=q5.top().y-(q4.top().y-q4.top().x);
      if(t1<=t2&&t1<=t3&&t1<=t4){//若第一种选择最优
	    node1 tmp=q1.top();q1.pop();//弹出
	    ans+=(long long)t1;b[tmp.id]=1;//更新答案
	    q2.push((node2){tmp.x,tmp.y,tmp.id});//放入一颗星星的堆里
	    q3.push((node3){tmp.x,tmp.y,tmp.id});//放入一颗星星的堆里
	    continue;
      }if(t2<=t1&&t2<=t3&&t2<=t4){//若第二种选择最优
	    node3 tmp=q3.top();q3.pop();//弹出
	    ans+=(long long)t2;b[tmp.id]=2;//更新答案
	    q4.push((node4){tmp.x,tmp.y,tmp.id});//放入一颗星星的堆里
	    continue;
      }if(t3<=t1&&t3<=t2&&t3<=t4){//若第三种选择最优
	    node5 tmp1=q5.top();q5.pop();//弹出
	    node2 tmp2=q2.top();q2.pop();//弹出
	    ans+=(long long)t3;b[tmp1.id]=2;b[tmp2.id]=0;//更新答案
	    q4.push((node4){tmp1.x,tmp1.y,tmp1.id});//放入两颗星星的堆里
	    q1.push((node1){tmp2.x,tmp2.y,tmp2.id});//放入零颗星星的堆里
        q5.push((node5){tmp2.x,tmp2.y,tmp2.id});//放入零颗星星的堆里
	    continue;
      }if(t4<=t1&&t4<=t2&&t4<=t3){//若第四种选择最优
	    node5 tmp1=q5.top();q5.pop();//弹出
	    node4 tmp2=q4.top();q4.pop();//弹出
	    ans+=(long long)t4;b[tmp1.id]=2;b[tmp2.id]=1;//更新答案
	    q4.push((node4){tmp1.x,tmp1.y,tmp1.id});//放入两颗星星的堆里
	    q2.push((node2){tmp2.x,tmp2.y,tmp2.id});//放入一颗星星的堆里
	    q3.push((node3){tmp2.x,tmp2.y,tmp2.id});//放入一颗星星的堆里
      }
    }print(ans);putchar('\n');
  for(re i=1;i<=n;i++)print(b[i]);
  return 0;
}
```

---

## 作者：尹昱钦 (赞：2)

# 做法：反悔贪心
**枚举星星数**，每加一颗星星，
## 有以下情况：
1. 零星关卡变成一星
1. 一星关卡变成两星
1. 一个零星关卡变成两星，一个一星关卡变成零星
1. 一个零星关卡变成两星，一个两星关卡变成一星

## 转化为优先队列即为：
- q1：零星关卡到一星的代价
- q2：零星关卡到二星的代价
- q3：一星关卡从二星变成一星的代价
- q4：一星关卡的到一星的代价
- q5：二星关卡从二星到一星的代价

## 四种情况为：
1. 小根堆q1堆顶
1. 小根堆q3堆顶
1. 小根堆q2堆顶 - 大根堆q4堆顶
1. 小根堆q2堆顶 - 大根堆q5堆顶

然后分别维护这五个队列即可。
## 注意：
- 取堆顶前要先判断堆是否为空
- 每种情况的初始值一定要初始化一个很大的longlong（不能用初始化int的值）

## AC代码:

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=300005;
int n,w,vis[maxn][3];
long long minw;
long long ans,ans1,ans2,ans3,ans4;
struct node{
	long long t1,t2;
}a[maxn];
priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > q1,q2,q3;
priority_queue<pair<long long,int> > q4,q5;
int main(){
	cin>>n>>w;
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].t1,&a[i].t2);
		q1.push(make_pair(a[i].t1,i));
		q2.push(make_pair(a[i].t2,i));
		vis[i][0]=1;
	}
	for(int i=1;i<=w;i++){
		ans1=ans2=ans3=ans4=0x3f3f3f3f3f3f;
		while(!q1.empty()&&!vis[q1.top().second][0]) q1.pop();
		while(!q2.empty()&&!vis[q2.top().second][0]) q2.pop();
		while(!q3.empty()&&!vis[q3.top().second][1]) q3.pop();
		while(!q4.empty()&&!vis[q4.top().second][1]) q4.pop();
		while(!q5.empty()&&!vis[q5.top().second][2]) q5.pop();
		if(!q1.empty()) ans1=q1.top().first;
		if(!q3.empty()) ans2=q3.top().first;
		if(!q2.empty()&&!q4.empty()) ans3=q2.top().first-q4.top().first;
		if(!q5.empty()&&!q2.empty()) ans4=q2.top().first-q5.top().first;
		minw=min(min(ans1,ans2),min(ans3,ans4));
		ans+=minw;
		if(minw==ans1){
			int id=q1.top().second;
			q1.pop();
			vis[id][0]=0;
			vis[id][1]=1;
			q3.push(make_pair(a[id].t2-a[id].t1,id));
			q4.push(make_pair(a[id].t1,id));
			continue;
		}
		if(minw==ans2){
			int id=q3.top().second;
			q3.pop();
			vis[id][1]=0;
			vis[id][2]=1;
			q5.push(make_pair(a[id].t2-a[id].t1,id));
			continue;
		}
		if(minw==ans3){
			int id1=q2.top().second;
			int id2=q4.top().second;
			q2.pop();
			q4.pop();
			vis[id1][0]=0;
			vis[id1][2]=1;
			vis[id2][1]=0;
			vis[id2][0]=1;
			q5.push(make_pair(a[id1].t2-a[id1].t1,id1));
			q1.push(make_pair(a[id2].t1,id2));
			q2.push(make_pair(a[id2].t2,id2));
			continue;
		}
		if(minw==ans4){
			int id1=q2.top().second;
			int id2=q5.top().second;
			q2.pop();
			q5.pop();
			vis[id1][0]=0;
			vis[id1][2]=1;
			vis[id2][2]=0;
			vis[id2][1]=1;
			q5.push(make_pair(a[id1].t2-a[id1].t1,id1));
			q3.push(make_pair(a[id2].t2-a[id2].t1,id2));
			q4.push(make_pair(a[id2].t1,id2));
			continue;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(vis[i][0]) printf("0");
		else if(vis[i][1]) printf("1");
		else if(vis[i][2]) printf("2"); 
	}
	return 0;
}
```
~~**是不是又臭又长**~~

**于是你就这样A了一道黑题了**

---

## 作者：BigSmall_En (赞：1)

# [CF436E](https://codeforces.com/problemset/problem/436/E) Cardboard Box

> $n$ 个关卡，对每个关卡，你可以花 $a_i$ 代价得到一颗星，也可以花 $b_i$ 代价得到两颗星，也可以不玩。问获得 $m$ 颗星最少需要多少时间。

给一种题解区还没有具体写但是是官方题解的做法。

### 思路

将关卡按 $b_i$ 排序，发现如果我们对于关卡 $x$，如果花 $b_x$ 的代价得到了两颗星星，那么如果答案要优秀，就必须在 $1\sim x$ 的关卡中至少得到一颗星星。

> 证明：如果在 $y(1\leq y< x)$ 位置没有得到一颗星星，那么我们可以花费 $b_y$ 的代价在 $y$ 处获得星星，同时取消掉 $x$ 处取得的两颗星星，由于 $b_y<b_x$，所以在得到同样星星数量的情况下花费更小。

所以假设在前 $L$ 个中都已经选了一颗星星，满足 $\max(0,m-n)\leq L\leq \min(n,m)$。那么可以认为只能在 $1\sim L$ 的范围内考虑取两颗星星的情况，此时不会更劣。

此时的答案的一部分为 $\sum_{i=1}^{L}a_i$。

另一部分则是在 $1\sim L$ 区间内多取一颗星星或在 $L\sim n$ 的区间内取一颗星星的情况。

即可重集合 $\{b_i-a_i|i\leq L\}\cup\{a_i|L<i\}$ 的前 $m-L$ 小的元素的和。

### 实现

先将所有的 $a_i$ 加入到一个数据结构中，从小到大枚举 $L$ 时候，将 $a_i$ 从数据结构中移除，$b_i-a_i$ 加入。然后查询数据结构中前 $m-L$ 小的元素和。

可以将 $b_i-a_i,a_i$ 离散化。维护一颗线段树，线段树的每个区间上记录当前数据结构中该区间的数的个数 $siz$ 和他们的和 $sum$。修改即为线段树单点修改。查询线段树上二分即可，注意一个叶子节点的 $siz$ 可能大于要查询的数的个数，此时需要返回 $siz\times val$，其中 $val$ 是该节点所对应的离散化数组的值的大小。

询问方案数我没有比较好的实现方法。我的方法是记录下答案最小时 $L$ 的取值。然后将此时的 $b_i-a_i$ 或 $a_i$ 的值以及他们所对应的编号直接存下来排序，选前 $m-L$ 个。

时间复杂度 $O(n\log n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll>ttfa;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=300005;
int n,m,lis[N<<1],tot,bel[N];
ttfa arr[N];
inline int Loc(int x){return lower_bound(lis+1,lis+1+tot,x)-lis;}
struct node{ll a,b,d;int id;}a[N];
bool cmp(node x,node y){return x.b<y.b;}
int siz[N<<3];ll sum[N<<3];
#define ls p<<1
#define rs p<<1|1
#define mid ((l+r)>>1)
inline void pushup(int p){
	siz[p]=siz[ls]+siz[rs];
	sum[p]=sum[ls]+sum[rs];
}
void update(int p,int l,int r,int L,ll v,int f){
	if(l==r){siz[p]+=f;sum[p]+=f*v;return;}
	if(L<=mid)update(ls,l,mid,L,v,f);
	else update(rs,mid+1,r,L,v,f);
	pushup(p);
}
ll query(int p,int l,int r,ll k){
	if(l==r)return (ll)lis[l]*k;
	if(k<=siz[ls])return query(ls,l,mid,k);
	return sum[ls]+query(rs,mid+1,r,k-siz[ls]);
}

int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		a[i].a=read(),a[i].b=read();a[i].id=i;
		a[i].d=a[i].b-a[i].a;
		lis[++tot]=a[i].a,lis[++tot]=a[i].d;
	}
	sort(lis+1,lis+1+tot);
	tot=unique(lis+1,lis+1+tot)-lis-1;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;++i)
		update(1,1,tot,Loc(a[i].a),a[i].a,1);
	ll pre=0,ans=0x3f3f3f3f3f3f3f3f;int lim=0;
	if(m<=n)ans=query(1,1,tot,m);
	//printf("%lld\n",ans);
	for(int i=1;i<=max(m-n,1)-1;++i){
		pre+=a[i].a;
		update(1,1,tot,Loc(a[i].a),a[i].a,-1);
		update(1,1,tot,Loc(a[i].d),a[i].d,1);
	}
	for(int i=max(m-n,1);i<=min(n,m);++i){
		pre+=a[i].a;
		update(1,1,tot,Loc(a[i].a),a[i].a,-1);
		update(1,1,tot,Loc(a[i].d),a[i].d,1);
		ll tmp=pre+query(1,1,tot,m-i);
		if(tmp<ans)ans=tmp,lim=i;
		//printf("%lld %lld\n",ans,lim);
	}
	printf("%lld\n",ans);
	//if(m==300000)printf("%d\n",lim);
	for(int i=1;i<=lim;++i)arr[i]={a[i].d,i},bel[a[i].id]=1;
	for(int i=lim+1;i<=n;++i)arr[i]={a[i].a,i};
	sort(arr+1,arr+1+n);
	for(int i=1;i<=m-lim;++i){
		if(arr[i].second<=lim)bel[a[arr[i].second].id]=2;
		else bel[a[arr[i].second].id]=1;
	}
	for(int i=1;i<=n;++i)
		printf("%d",bel[i]);
	putchar('\n');
	return 0;
}
/*
10 8
2 22
5 12
5 16
10 26
13 16
1 23
1 18
8 30
13 21
6 14
//上面是CF的一个数据点
*/
```

### 后记

特别感谢 [recollector](https://www.luogu.com.cn/user/177893) 大佬对本篇题解完成提供的帮助。

---

## 作者：Gmt丶FFF (赞：0)

一道经典的反悔贪心题。

考虑每次选择使总星数加一，那么总共有四种情况。

一、对于一关没有星，选一颗星，代价为 $a_i$。

二、对于一关有一颗星，再选一颗星，代价为 $b_i-a_i$。

三、对于一关有一颗星，选择退回这颗星，并再另一个没星的关卡选两颗星，代价为 $-a_i+b_j$。

四、对于一关有两颗星，退回一颗星，并再另一个没星的关卡选两颗星，代价为 $-b_i+a_i+b_j$

那么维护五个优先队列，分别为 $a_i,b_i-a_i,-a_i,b_j,-b_i+a_i$，每次取四种情况的最小值来选即可。

```
#include<iostream>
#include<cstdio>
#include<queue>
#define int long long
using namespace std;
const int N=3e5+5;
int n,w,a[N],b[N],vis[N];
long long ans=0;
struct node
{
	int name;
	int data;
};
bool operator <(node fi,node se)
{
	return fi.data>se.data;
}
priority_queue<node>q1,q2,q3,q4,q5;
signed main()
{
	scanf("%lld%lld",&n,&w);
	q1.push({0,10000000000ll});
	q2.push({0,10000000000ll});
	q3.push({0,10000000000ll});
	q4.push({0,10000000000ll});
	q5.push({0,10000000000ll});
	for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i],&b[i]),q1.push({i,a[i]}),q5.push({i,b[i]});
	for(int i=1;i<=w;i++)
	{
		int num1=q1.top().data,num2=q2.top().data,num3=q5.top().data+q3.top().data,num4=q5.top().data+q4.top().data;
		if(num1<=num2&&num1<=num3&&num1<=num4)
		{
			ans+=num1;
			int id=q1.top().name;
			vis[id]=1;
			q3.push({id,-a[id]});
			q2.push({id,b[id]-a[id]});
		}
		else if(num2<=num1&&num2<=num3&&num2<=num4)
		{
			ans+=num2;
			int id=q2.top().name;
			vis[id]=2;
			q4.push({id,a[id]-b[id]});
		}
		else if(num3<=num2&&num3<=num1&&num3<=num4)
		{
			ans+=num3;
			int id=q5.top().name,id2=q3.top().name;
			q4.push({id,a[id]-b[id]});
			q1.push({id2,a[id2]});
			q5.push({id2,b[id2]});
			vis[id]=2;
			vis[id2]=0;
		}
		else
		{
			ans+=num4;
			int id=q5.top().name,id2=q4.top().name;
			q4.push({id,a[id]-b[id]});
			q3.push({id2,-a[id2]});
			q2.push({id2,b[id2]-a[id2]});
			vis[id]=2;
			vis[id2]=1;
		}
		while(q1.top().name!=0&&vis[q1.top().name]!=0)q1.pop();
		while(q2.top().name!=0&&vis[q2.top().name]!=1)q2.pop();
		while(q3.top().name!=0&&vis[q3.top().name]!=1)q3.pop();
		while(q4.top().name!=0&&vis[q4.top().name]!=2)q4.pop();
		while(q5.top().name!=0&&vis[q5.top().name]!=0)q5.pop();
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++)printf("%lld",vis[i]);
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

最近做到的最难的一题反悔贪心，参考了题解做法才想明白。

------------

解题思路：

考虑反悔贪心。

由于本题要求恰好取到 $w$ 颗星星，不能超过，也不能少，所以思考方向可以应导向为到底怎样得到额外的一星才代价最小：

最简单的决策是直接选择一个一星关卡打了。然后还有以及反悔贪心的基本套路，撤销一个一星关卡的影响，然后再把它改成当前这一个两星关卡的影响。

接下来两种是较难想到的，也是这道题~~为什么是紫色的~~这道题真正的难点：撤销一个一星关卡，然后找一个其他的两星关卡打了；把一个两星关卡反悔成一个一星和另一个两星关卡。

首先是撤销一星选两星这个操作，可以考虑这样一种情况：有个关卡一星特别难，但是二星代价很小，另一个关卡一星特简单，但是两星耗时极长，如果只有一开始的两种决策，会出现（假设要得总计两星）选了第一、二个关卡的一星或者是第二个关卡的两星，而无法决策到第一个关卡的两星的情况。换句话说，就是可能出现一星耗时长无法进入决策考虑范围的情况。

举个例子就是：

关卡一：一星 1 单位时间，两星 100 单位时间。

关卡二：一星 99 单位时间，两星 10 单位时间。

一开始的一星决策肯定是选择关卡一的一星。然后到二星决策时，如果只有一开始的两种决策就只会选择关卡二的一星，总代价为 $100$，实际上直接打关卡二的二星就只需要 $10$ 的代价。

~~(虽然不太合理，但好像确实没说不能打两星时间比一星短~~

然后是一个两星关卡反悔成当前关卡一星和另一个两星关卡，这种情况和上一种有点类似，都是因为可能出现直接某一个关卡直接二星很容易，而一星很难，导致无考虑不到的情况，而这一种没有上一种极端，而且有了上一个的基础这一个决策也很好理解，所以直接给出例子：

假设你要拿到三星

关卡一：一星 100 单位时间，两星 10 单位时间。

关卡二：一星 5 单位时间，两星 8 单位时间。
        
这样第一次和第二次决策时分别是选择的关卡二一星和两星，没有涉及关卡一，而总共二星时在要取得一颗星按照之前的三种决策只能取关卡一的 $100$ 单位时间，与最优的 $15$ 单位时间相差甚远。

------------
实现上，可以重新列出上面的几种决策（~~其实是我数不过来到底要维护多少堆了~~），并依次分析需要维护的值，当然还是正常反悔贪心的堆维护。

具体的，有：

1. 打一个从来没有打过的一星关卡，需要维护从没有打过的关卡的 $a_i$ 的最小值。

2. 把一个打过的一星关卡变成同关卡二星关卡，需要维护已经打过一星的关卡的 $b_i-a_i$ 的最小值。

3. 把一个打过的一星关卡变成一个其他的二星关卡，需要维护 $b_j-a_i$ 的最小值，实际上就是维护两个值：即已经打了的一星关卡的 $a_i$ 的最大值（或者说是 $-a_i$ 的最小值，两者等价），和从来没有打过的关卡的 $b_j$ 的最小值。

4. 把一个已经打过的二星关卡反悔成当前一星关卡和一个从没有打过的二星关卡，需要维护 $a_i-b_i+b_j$ 的最小值。类似的，拆分下来的就是一个已经打过两星关卡的 $a_i-b_i$ 的最小值和从没有打过的关卡的 $b_i$ 的最小值。

其中决策四 中要维护的从来没有打过的关卡的 $b_i$ 的最小值在决策三 中也用到了，所以你只需要维护五个堆就可以啦。

然后每一次决策根据贪心的原则从所有的决策中选择一个耗时最短的即可，注意需要。

------------
细节上：每一个堆不仅要注意维护取得是哪一个值，还要考虑到维护的是哪一些类型里的值，比如“从没有打过的关卡”“已经拿了两星的关卡”等。

---

## 作者：龙之吻—水货 (赞：0)

# Cardboard Box
## 题目大意
你正在玩一个名为割绳子的游戏，当前单元有 $n$ 关游戏，解锁下一单元需要  $w$ 颗星。对于每一关，得到 $1$ 颗星需要花费 $a_i$ 的时间，得到 $2$ 颗星需要花费 $b_i$ $(b_i > a_i)$，当然不得星不需要花费时间。问解锁下一单元至少需要多少时间，并输出方案。
## 解题报告
这题，可以一眼秒出一个背包做法或者一个比较优秀的DP做法，但由于 $1 \leq a_i \leq 10^9$，而 $1 \leq n \leq 3e5$，显然使用动归并不健康，于是考虑贪心做法。

这题，似乎看起来也可以直接贪心(也就是按照$a_i,b_i$的某种关系进行贪心选取)，但不幸的是，在CF比赛的时候某**t**姓红黑名网友尝试了直接贪心的做法，并且被 $hack$ 掉了，所以我们可能需要更好更稳定的贪心方法。

我们把每一关按照$b_i$从小到大排序，然后我们从$1$扫到$n$。

假设当前我们扫到$pos$，则表示的是 $1$ 到 $pos$ 的关卡中至少要得到一颗星， $pos + 1$ 到 $n$ 的关卡中至多得到一颗星。那么，显然 $1$ 到 $pos$ 的关卡中我们选取了 $pos$ 个 $a_i$，还需要从 $1$ 到 $pos$ 的$b_i - a_i$ 和 $pos + 1$ 到 $n$ 的 $a_i$ 这 $n$ 个数中选取前 $w - pos$ 小的，每次向前推进的时候需要删除一个 $a_i$，加入一个 $b_i - a_i$。显然类似线段树，树状数组，平衡树等数据结构可以很轻松地完成这个任务。(当然，如果出现了不合法的情况跳过即可)

考虑这样贪心的正确性，对于每一个 $pos$，如果 $pos$ 后面有选 $2$ 颗星的情况，显然不会比把其中的 $1$ 颗星转移到前面的关卡完成更优。而从 $1$ 扫到 $n$ ，则将所有可能的情况包含在内。~~感性理解一下这是正确的~~

至于如何输出方案，可以尝试在树上走路的方法，这里就不多说了 QwQ

附上我也不知道为什么写了这么长的代码 QwQ
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<tr1/unordered_map>
#include<vector>

class SegmentTree{
private :
    static const int maxn = 6e5 + 7;
    static const int INF = 1e9 + 7;
    typedef long long ll;
    
    struct Node{
        int val, size;
        ll sum;
        Node *child[2];

        Node() : val(0), size(0), sum(0) {
            child[0] = child[1] = NULL;
        }
    };

    int n;
    Node *root, *tp, pool[maxn << 2];

    Node *newNode() {
        *++tp = Node();
        return tp;
    }

    void update(Node *now) {
        now->size = 0;
        now->sum = 0;
        for (register int i = 0; i < 2; i++) {
            if (now->child[i]) {
                now->size += now->child[i]->size;
                now->sum += now->child[i]->sum;
            }
        }
    }
    
    void addVal(Node *now, int left, int right, int pos, int val) {
        if (left == right) {
            now->val = val;
            now->sum += val;
            now->size++;
            return;
        }
        int mid = (left + right) >> 1;
        if (pos <= mid) {
            if (!now->child[0]) {
                now->child[0] = newNode();
            }
            addVal(now->child[0], left, mid, pos, val);
        } else {
            if (!now->child[1]) {
                now->child[1] = newNode();
            }
            addVal(now->child[1], mid + 1, right, pos, val);
        }
        update(now);
    }

    void delVal(Node *now, int left, int right, int pos, int val) {
        if (left == right) {
            now->sum -= val;
            now->size--;
            return;
        }
        int mid = (left + right) >> 1;
        if (pos <= mid) {
            if (!now->child[0]) {
                now->child[0] = newNode();
            }
            delVal(now->child[0], left, mid, pos, val);
        } else {
            if (!now->child[1]) {
                now->child[1] = newNode();
            }
            delVal(now->child[1], mid + 1, right, pos, val);
        }
        update(now);
    }

    ll query(Node *now, int left, int right, int tot) {
        //printf("tot : %d\n", tot);
        if (left == right) {
            return 1ll * now->val * tot;
        }
        int leftsize = now->child[0] ? now->child[0]->size : 0;
        int mid = (left + right) >> 1;
        ll res = 0;
        if (tot >= leftsize) {
            if (now->child[0]) {
                res += now->child[0]->sum;
            }
            if (tot > leftsize) {
                res += query(now->child[1], mid + 1, right, tot - leftsize);
            }
            return res;
        } else {
            return query(now->child[0], left, mid, tot);
        }
    }

    void search(Node *now, int left, int right, int tot, std::vector<int> &vec) {
        if (!now) {
            return;
        }
        if (left == right) {
            while (tot--) {
                vec.push_back(left);
            }
        }
        int leftsize = now->child[0] ? now->child[0]->size : 0;
        int mid = (left + right) >> 1;
        if (tot >= leftsize) {
            search(now->child[0], left, mid, leftsize, vec);
            if (tot > leftsize) {
                search(now->child[1], mid + 1, right, tot - leftsize, vec);
            }
        } else {
            search(now->child[0], left, mid, tot, vec);
        }
    }
    
public :
    void init(int x) {
        n = x;
        tp = pool;
        root = newNode();
    }

    void addVal(int pos, int val) {
        addVal(root, 1, n, pos, val);
    }

    void delVal(int pos, int val) {
        delVal(root, 1, n, pos, val);
    }

    ll query(int tot) {
        //printf("%d\n", tot);
        //printf("%d : %d\n", root->size, tot);
        return query(root, 1, n, tot);
    }

    void search(int tot, std::vector<int> &vec) {
        search(root, 1, n, tot, vec);
        //printf("%d %d\n", tot, vec.size());
    }
};


class Solution{
private :
    typedef std::pair<std::pair<int, int>, int> par;
    typedef long long ll;
    typedef std::vector<int>::iterator it;
    static const int maxn = 3e5 + 7;
    
    int n, m, p, res[maxn], num[maxn * 3], cnt, pos;
    par val[maxn];
    ll ans, sum, pre;
    std::vector<int> vec, ps[maxn * 3];
    //std::tr1::unordered_map<int, std::vector<int> > ps;
    std::tr1::unordered_map<int, int> id;
    SegmentTree tree;
    
public :
    Solution() {
        get();
        solve();
    }

    void get() {
        scanf("%d %d", &n, &m);
        pos = std::max(m - n + 1, 1);
        for (register int i = 1, x, y; i <= n; i++) {
            scanf("%d %d", &x, &y);
            //num[i] = x, num[i + n] = y;
            num[i] = x, num[i + n] = y - x;
            val[i] = std::make_pair(std::make_pair(y, x), i);
        }
    }

    void solve() {
        std::sort(val + 1, val + 1 + n);
        std::sort(num + 1, num + 1 + (n << 1));
        for (register int i = 1; i <= (n << 1); i++) {
            if (num[i] != num[i - 1]) {
                id[num[i]] = ++cnt;
            }
        }
        tree.init(cnt);
        for (register int i = 1; i < pos; i++) {
            ans += val[i].first.second;
            res[val[i].second]++;
            tree.addVal(id[val[i].first.first - val[i].first.second], val[i].first.first - val[i].first.second);
        }
        for (register int i = pos; i <= n; i++) {
            tree.addVal(id[val[i].first.second], val[i].first.second);
        }
        sum = tree.query(std::min(n, m));
        p = pos - 1;
        for (register int i = pos; i <= n; i++) {
            pre += val[i].first.second;
            tree.delVal(id[val[i].first.second], val[i].first.second);
            tree.addVal(id[val[i].first.first - val[i].first.second], val[i].first.first - val[i].first.second);
            if (std::min(n, m) <= (i - pos + 1)) {
                continue;
            }
            ll q = tree.query(std::min(n, m) - (i - pos + 1));
            if (pre + q < sum) {
                sum = pre + q;
                p = i;
            }
        }
        tree.init(cnt);
        for (register int i = 1; i < pos; i++) {
            tree.addVal(id[val[i].first.first - val[i].first.second], val[i].first.first - val[i].first.second);
        }
        for (register int i = pos; i <= n; i++) {
            tree.addVal(id[val[i].first.second], val[i].first.second);
        }
        printf("%lld\n", ans + sum);
        for (register int i = pos; i <= p; i++) {
            res[val[i].second]++;
            tree.delVal(id[val[i].first.second], val[i].first.second);
            tree.addVal(id[val[i].first.first - val[i].first.second], val[i].first.first - val[i].first.second);
            if (i == p) {
                tree.search(std::min(n, m) - (i - pos + 1), vec);
            }
        }
        if (p == pos - 1) {
            tree.search(std::min(n, m), vec);
        }
        for (register int i = 1; i <= n; i++) {
            if (i <= p) {
                num[i] = val[i].first.first - val[i].first.second;
            } else {
                num[i] = val[i].second;
            }
        }
        for (register int i = 1; i <= n; i++) {
            if (i <= p) {
                ps[id[val[i].first.first - val[i].first.second]].push_back(val[i].second);
            } else {
                ps[id[val[i].first.second]].push_back(val[i].second);
            }
        }
        for (register it i = vec.begin(); i != vec.end(); ++i) {
            int now = *i;
            //printf("%d\n", *i);
            //printf("%d\n", *i);
            //printf("%d\n", now);
            res[ps[now].back()]++;
            ps[now].pop_back();
        }
        for (register int i = 1; i <= n; i++) {
            printf("%d", res[i]);
        }
        putchar('\n');
    }
};
Solution sol;

int main() {}

/*QwQ*/
```

---

