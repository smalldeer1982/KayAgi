# Game with Marbles (Hard Version)

## 题目描述

本题的简单版与困难版的区别仅在于测试用例数量和 $n$ 的限制。在困难版中，测试用例数量不超过 $10^4$，所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。此外，单个测试用例中的 $n$ 没有额外限制。

最近，Alice 和 Bob 的父母给了他们 $n$ 种不同颜色的弹珠。Alice 拥有第 $1$ 种颜色的 $a_1$ 个弹珠，第 $2$ 种颜色的 $a_2$ 个弹珠，……，第 $n$ 种颜色的 $a_n$ 个弹珠。Bob 拥有第 $1$ 种颜色的 $b_1$ 个弹珠，第 $2$ 种颜色的 $b_2$ 个弹珠，……，第 $n$ 种颜色的 $b_n$ 个弹珠。所有 $a_i$ 和 $b_i$ 的取值范围为 $1$ 到 $10^9$。

经过一番讨论，Alice 和 Bob 想出了如下的游戏规则：两人轮流操作，Alice 先手。在每一回合，当前玩家选择一种颜色 $i$，要求两人手中该颜色的弹珠都至少有一个。然后，该玩家丢弃自己手中一种该颜色的弹珠 $1$ 个，对手则丢弃所有该颜色的弹珠。游戏结束的条件是不存在某种颜色 $i$，使得两人手中该颜色的弹珠都至少有一个。

游戏的得分为游戏结束时 Alice 剩余弹珠数减去 Bob 剩余弹珠数，即 $A-B$，其中 $A$ 为 Alice 剩余弹珠数，$B$ 为 Bob 剩余弹珠数。Alice 希望最大化得分，Bob 希望最小化得分。

请计算当双方都采取最优策略时，游戏结束时的得分。

## 说明/提示

在第一个样例中，一种得到得分 $1$ 的方案如下：

1. Alice 选择颜色 $1$，丢弃 $1$ 个弹珠，Bob 也丢弃 $1$ 个弹珠；
2. Bob 选择颜色 $3$，丢弃 $1$ 个弹珠，Alice 也丢弃 $1$ 个弹珠；
3. Alice 选择颜色 $2$，丢弃 $1$ 个弹珠，Bob 丢弃 $2$ 个弹珠。

最终，Alice 剩余 $a = [3, 1, 0]$，Bob 剩余 $b = [0, 0, 3]$。得分为 $3 + 1 - 3 = 1$。

可以证明，如果双方都采取最优策略，得分无法更优。

在第二个样例中，Alice 可以先选择颜色 $1$，然后 Bob 选择颜色 $4$，之后 Alice 选择颜色 $2$，Bob 选择颜色 $3$。可以证明这是最优策略。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5```

### 输出

```
1
-9
2999999997
8
-6```

# 题解

## 作者：abensyl (赞：2)

不知道 easy version 什么做法，上来之间照着 hard version 做的。

- [CF1914E1 Game with Marbles (Easy Version)](https://www.luogu.com.cn/problem/CF1914E1)；  
- [CF1914E2 Game with Marbles (Hard Version)](https://www.luogu.com.cn/problem/CF1914E2)。

两人肯定是按照一种贪心策略来进行，对于每种颜色的珠子，如果 A 得到先选择它，那么 B 这种颜色的珠子会变为 $1$，而 A 的这种颜色的珠子全部保住，就会对答案产生 $a_i-1$ 的影响，如果 B 拿到，那么就会产生 $b_i-1$ 的影响，而两者的差值就可以理解为这种珠子所带来的价值，就是 $a_i-1+b_i-1$，化简就是 $a_i+b_i-2$，显然，贪心时按照 $a_i+b_i-2$ 和按照 $a_i+b_i$ 排序效果是相同的，所以考虑把 $a_i+b_i$ 压入大根堆或者优先队列，每次取出堆顶即可。

时间复杂度 $O(n\log n)$。

大致代码如下：

```cpp
const int N = 1e5+5, M = 5e5+5;
ll a[M],b[M];
void solve() {
	ll n,sc=0;
	cin>>n;
	rep(i,1,n) cin>>a[i];
	rep(i,1,n) cin>>b[i];
	priority_queue<pii> pq;
	rep(i,1,n)
		pq.push({a[i]+b[i],i});
	rep(i,1,n) {
		if(i%2) sc+=a[pq.top().second]-1;
		else sc-=b[pq.top().second]-1;
		pq.pop();
	} cout<<sc<<'\n';
}
```

---

## 作者：ST_AS_IS_ZHY (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1914E2)

## 题意

给定两个人每种颜色弹珠的数量，在每一轮游戏中当前回合的玩家可以在自己拥有该颜色弹珠的情况下通过减少一枚该颜色弹珠来让对方该颜色弹珠清零，在无法进行下一回合时游戏结束。游戏的胜负由双方剩余弹珠数量决定。

## 思路

可以理解为对于每一个颜色的弹珠，当你让对方的弹珠数量清零时，也就间接的保护了自己的弹珠，所以这一次操作的贡献是自己的弹珠数量加上对方的弹珠数量减一。所以只需要求出对于每一种颜色双方的弹珠总数，排序将大的放在前面，再通过回合数的奇偶性贪心就行。

## 代码

```c++
// Problem: Game with Marbles (Easy Version)
//   弹珠游戏（简易版）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1914E1
// Memory Limit: 250 MB
// Time Limit: 3500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long 

using namespace std;
int T , n , sum1 , sum2;
struct node
{
    int a , b;
    int sum;
}s[400001];

bool cmp(node x , node y)
{
    return x.sum > y.sum;
}

signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T --)
    {
	sum1 = sum2 = 0;
	cin >> n;
	for(int i = 1 ; i <= n ; i ++) 
	{
	    cin >> s[i].a;
	    sum1 += s[i].a;
	}
	for(int i = 1 ; i <= n ; i ++) 
	{
	    cin >> s[i].b;
	    sum2 += s[i].b;
	    s[i].sum = s[i].a + s[i].b;
	    //cout << "sum = " << s[i].sum << '\n';
	}
	//cout << sum1 << ' ' << sum2 << '\n';
	sort(s + 1 , s + n + 1 , cmp);
	//for(int i = 1 ; i <= n ; i ++) cout << "sum = " << s[i].sum << '\n';
	for(int i = 1 ; i <= n ; i ++)
	{
	    if(!s[i].a || !s[i].b) continue;
	    if(i % 2)
	    {
		sum2 -= s[i].b;
		s[i].b = 0;
		sum1 --;
		s[i].a --;
	    }
	    else
	    {
		sum1 -= s[i].a;
		s[i].a = 0;
		sum2 --;
		s[i].b --;
	    }
	}
	cout << sum1 - sum2 << '\n';
    }
	return 0;
}
```



---

## 作者：qingyun111 (赞：1)

[洛谷CF1914E2 Game with Marbles (Hard Version)](https://www.luogu.com.cn/problem/CF1914E2)

[CF1914E2 Game with Marbles (Hard Version)](https://codeforces.com/problemset/problem/1914/E2)


### 主要是要理解题目：

题目的意思是 $a_{i}$ 和 $b_{i}$ 同样的位置，一边减一，另一边全部舍弃，而两边都会进行最优解操作。从 $a_{i}$ 开始。而我们需要求的则是最后的总分。

那么最大的问题：因为都是最优解操作，难以进行判断。

### 那我们换个思路：什么是最优解操作？

**当前序列位置为最大的，先把对面的全部扔掉，自己减一保大。**

当两个序列同位置的总和为最大的时候就是最优解。这相当于，把两个序列相加到一个数组里面（数值和序号都要记入），在以数值进行降序排序。

那总分呢？每一次加上当前操作的序列最优解数值（记得要减一）。


## 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define yes cout<<"Yes"<<endl;
#define no cout<<"No"<<endl;
#define N 1000000

ll num[N];

void solve() {
    ll  n,m,q,boll,tem,o,r,a,b,c,d,x,y,z,ans,sum,val,k;
    ans=sum=val=tem=0;
    a=b=0;
    cin>>n;
    vector<ll>v1(n),v2(n);
    vector<pair<ll,ll>>v3(n);
    for(int i=0;i<n;i++) {
        cin>>v1[i];
    }
    for(int i=0;i<n;i++) {
        cin>>v2[i];
        v3[i].first=v1[i]+v2[i]-1;//每一次操作要减1
        v3[i].second=i;
    }
    
    sort(v3.rbegin(),v3.rend());
    for(int i=0;i<n;i++){
        if(i%2==0){
            sum+=v1[v3[i].second]-1;
        }else{
            sum-=v2[v3[i].second]-1;
        }
    }
    cout<<sum<<endl;
    return;
}
int main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int t=1;
    cin>>t;
    while(t--) {
        solve();
    }
    return 0;
}
```


---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF1914E1 Game with Marbles (Easy Version)](https://www.luogu.com.cn/problem/CF1914E1)

[CF1914E2 Game with Marbles (Hard Version)](https://www.luogu.com.cn/problem/CF1914E2)

# 题意简述

小 $A$ 和小 $B$ 想要玩一个游戏，规则是这样的，每个人手里有 $n$ 种类型的弹珠，每种类型的弹珠数量至少为 $1$，每次操作方可以扔掉己方的一个类型的一个弹珠（前提是你至少要有这种类型的弹珠），扔完后对方要扔掉所有的与你扔掉这一颗弹珠的所有同类型的弹珠，双方都想让自己的弹珠数量最大，你需要求出小 $A$ 和小 $B$ 均使用最优策略的情况下小 $A$ 的弹珠数量减去小 $B$ 的弹珠数量的值。

# 解题思路

觉得不太会 Easy Version 的思路，直接讲 Hard Version 的思路吧。

首先，我们对于每一步策略都考虑一个贡献 $c_i$，那么我们很容易得出贡献计算的方式就为 $a_i + b_i = c_i$，其中 $a_i$ 为小 $A$ 的每种类型的弹珠数量，$b_i$ 为小 $B$ 的每种类型的弹珠数量，然后我们只需要将贡献排一下序，容易得出要使策略最优是必定要优先拿贡献大的地方的，因此直接贪心一下就做完了。

# 参考代码

```cpp
/*
Tips:
你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
*/
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
long long t,n,ans,L,R;
struct node{
	long long a,b,c;
}a[200010];
bool cmp(node x,node y){
	return x.c<y.c;
}
/*
long long t,n,maxn,minn,a[200010],b[200010],vis[200010];
void dfs(bool pd,long long cs,long long sum)
{
	if(cs==n+1)
	{
		maxn=max(maxn,sum);
		minn=min(minn,sum);
		return ;
	}
	if(!pd)
	{
		forl(i,1,n)
			if(!vis[i])
				vis[i]=1,dfs(pd^1,cs+1,sum+a[i]-1),vis[i]=0;
	}
	else
	{
		forl(i,1,n)
			if(!vis[i])
				vis[i]=1,dfs(pd^1,cs+1,sum-b[i]+1),vis[i]=0;
	}
}
void solve()
{
	maxn=-1e18,minn=1e18;
	cin>>n;
	forl(i,1,n)
		cin>>a[i];
	forl(i,1,n)
		cin>>b[i];
	dfs(0,1,0);
	if(n%2)
		cout<<maxn<<endl;
	else
		cout<<minn<<endl;
}*/
int main()
{
	IOS;
	cin>>t;
	while(t--)
	{
		cin>>n;
		forl(i,1,n)
			cin>>a[i].a;
		forl(i,1,n)
			cin>>a[i].b,a[i].c=a[i].a+a[i].b;
		sort(a+1,a+1+n,cmp);
		ans=0,L=1,R=n;
		forl(i,1,n)
		{
			if(i%2)
			{
				if(abs(a[L].c)<=abs(a[R].c))
					ans+=a[R].a-1,R--;
				else
					ans+=a[L].a-1,L++;
			}
			else
			{
				if(abs(a[L].c)<=abs(a[R].c))
					ans-=a[R].b-1,R--;
				else
					ans-=a[L].b-1,L++;				
			}
		}
		cout<<ans<<endl;
	}
    /******************/
	/*while(L<q[i].l) */
	/*    del(a[L++]);*/
	/*while(L>q[i].l) */
	/*    add(a[--L]);*/
	/*while(R<q[i].r) */
	/*	  add(a[++R]);*/
	/*while(R>q[i].r) */
	/*    del(a[R--]);*/
    /******************/
	QwQ;
}
```

---

## 作者：nominater (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1914E2)
### 思路
是贪心罢，悲。  
首先用 ```sum``` 记录同种颜色 $a$ 和 $b$ 的总数，一次操作的贡献就是自己的弹珠数量加上对面的弹珠数量再减一，由于每一个人都会做出最优选择，所以我们对 ```sum``` 的大小进行排序，贡献大的在前。逐个回合贪心即可。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e4+10;
ll t,n,res1,res2;
struct Node
{
    int a,b;
    int res;
}f[N<<2];

inline bool cmp(Node x , Node y)
{
    return x.res > y.res;
}
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+c-'0';
        c=getchar();
    }
    return x;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    t=read();
    while(t--)
    {
        res1 = res2 = 0;
        n=read();
        for(int i=1;i<=n;i++) 
        {
            f[i].a=read();
            res1 += f[i].a;
        }
        for(int i=1;i<=n;i++) 
        {
            f[i].b=read();
            res2 += f[i].b;
            f[i].res=f[i].a+f[i].b;
        }
        sort(f+1,f+n+1,cmp);
        for(int i=1;i<=n;i++)
        {
            if(!f[i].a || !f[i].b) 
                continue;
            if(i % 2)
            {
                res2 -= f[i].b;
                f[i].b = 0;
                res1 --;
                f[i].a --;
            }
            else
            {
                res1-= f[i].a;
                f[i].a=0;
                res2--;
                f[i].b--;
            }
        }
        cout<<res1-res2<<endl;
    }
    return 0;
}
```
你说的对，但写题解是一款由【正体不明】研发的......

---

## 作者：Erica_N_Contina (赞：1)

## 思路

首先明确要求说明，即所谓**甲乙的最优策略**是什么。

很显然，每一个下标 $i$ 只能被操作一次。

如果甲对 $i$ 进行操作，那么对答案（即 $A-B$ 的值）的贡献就是 $b_i-1$，如果是乙对 $j$ 进行操作，那么对答案的贡献就是 $-(a_j-1)$（我们假设答案的初始值为 $0$，并且当一个 $i$ 被操作后才把 $a_i,b_i$ 造成的贡献加入到答案中去）。

我们考虑一次操作。可以发现，一次对 $i$ 的操作相当于**保护了自己的 $i$，并且摧毁了对方的 $i$**。那么最优策略当然就是每次选择一个 $i$ 使得自己被保护的值和摧毁对方的值之和最大咯。

所以我们维护 $a_i+b_i$ 的值，从大到小排序，模拟流程即可。



## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rd read()//快读代码已经省略
const int N=1e6+5;
int ans=0,m;
int n;
struct node{
	int a,b,c;
}t[N];
bool cmp(node x,node y){return x.c>y.c;}
void solve(){
	n=rd;
	for(int i=1;i<=n;i++)t[i].a=rd;
	for(int i=1;i<=n;i++)t[i].b=rd;
	for(int i=1;i<=n;i++)t[i].c=t[i].a+t[i].b;
	int l=1,r=n,ans=0;
	sort(t+1,t+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(i&1) ans+=t[i].a-1;//先手
		else ans-=t[i].b-1;//后手
	}
	cout<<ans<<endl;
}
signed main(){
	int t=rd;
	while(t--)solve();
	return 0;
}

```




---

## 作者：KID2695 (赞：0)

不难发现每个位置只能被一个人选择，我们算一下每张牌被选择时所产生的贡献，甲选择一张牌的时候对自己答案的贡献为 $a_i+b_i-1$，乙选择一张牌的时候对自己答案的贡献也为 $a_i+b_i-1$。所以按这个东西排序，然后贪心选取就行了。

代码
```cpp
struct node{
	int a,b;
}c[N];
bool operator < (const node &a,const node &b){
	return (a.a+a.b-1>b.a+b.b-1);
} 
int t,n;
int main(){
	t=iread();
	while(t--){
		n=iread();
		FOR(i,1,n) c[i].a=iread();
		FOR(i,1,n) c[i].b=iread();
		sort(c+1,c+n+1);
		int op=0;
		ll ans=0;
		FOR(i,1,n){
			if(!op) ans+=c[i].a-1;
			else ans-=c[i].b-1;
			op^=1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

#### 算法
贪心，结构体。
#### 思路
甲想让 $A-B$ 越大越好，乙想让 $A-B$ 越小越好，如果甲乙足够聪明，那么最后 $A-B$ 的值为多少？

- 结构体储存 $a,b$ 数组，$s$ 变量算出 $a,b$ 的总和。
- 对应下标。
- 总体排序（贡献大在前）。
- 逐回合贪心即可。

最终算出答案 $A-B$ 的值。

#### 代码
```c
for(int i=1;i<=n;i++){
	if(i&1) t=t+n[i].a--;
	else t=t-n[i].b--;
}
```

---

## 作者：Elhaithan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1914E2)
### 思路
首先看到题面时就想到是用贪心来做。  
我们可以用结构体来存储 $a$ 数组和 $b$ 数组，$sum$ 存 $a_i$ 与 $b_i$ 的和，使下标相同的 $a_i$ 与 $b_i$ 相对应，然后将其从大到小排序再模拟过程来算出最终 $A-B$ 的值。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+5;
struct node{
	int a, b, sum;
	bool operator < (const node &x)const{
		return x.sum < sum;//从大到小
	}
}num[N];
int t, n;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin >> t;
	while(t --){
		cin >> n;
		memset(num,0,sizeof num);//结构体要清零
		for(int i=1; i<=n; i++) cin >> num[i].a;
		for(int i=1; i<=n; i++) cin >> num[i].b;
		for(int i=1; i<=n; i++) num[i].sum = num[i].a + num[i].b;
		sort(num+1, num+1+n);
		int res = 0;
		for(int i=1; i<=n; i++){
			if(i&1) res += num[i].a - 1;//甲的回合
			else res -= num[i].b - 1;//乙的回合
		}
		cout << res << endl;
	}
	
	return 0;
}
```

---

## 作者：ThySecret (赞：0)

## 题目大意

爱丽丝和鲍勃想出了下面这个游戏：玩家轮流玩，从爱丽丝开始。轮到一个玩家时，他选择一种颜色 $i$，这样双方都至少有一个这种颜色的弹珠。然后玩家丢弃一个颜色为 $i$ 的弹珠，而对手则丢弃所有颜色为 $i$ 的弹珠。如果没有颜色 $i$ 使得双方都至少有一颗该颜色的弹珠，游戏就结束了。

游戏的得分是游戏结束时爱丽丝剩余弹珠数与鲍勃剩余弹珠数之差。换句话说，游戏的得分等于 $(A-B)$，其中 $A$ 是爱丽丝拥有的弹珠数，$B$ 是游戏结束时鲍勃拥有的弹珠数。爱丽丝希望得分最大化，而鲍勃希望得分最小化。

求出得分的最大值。

## 解题思路

很明显的贪心题。

双方都想要让对方的弹珠变少，可以想出第一个贪心是让双方优先选择对方弹珠数量最多的颜色减去，可以通过第一个样例，但是第二个就错了，为什么呢？因为对方的弹珠数量可能相同，此时要尽量保护好自己的弹珠数量。

细想后由此可以想出第二个贪心，每一个下标 $i$ 的两个权值 $a_i$ 和 $b_i$ 对于两个人的抉择都十分重要，因此我们可以定义一个结构体分别存储两个数的和与其下标，通过降序排序后便为两个人的依次抉择方案。

## AC Code 

```c++
// Problem: E2. Game with Marbles (Hard Version)
// Contest: Codeforces - Codeforces Round 916 (Div. 3)
// URL: https://codeforces.com/contest/1914/problem/E2
// Memory Limit: 256 MB
// Time Limit: 3500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define int long long

const int N = 2e5 + 9;
const int INF = 0x3f3f3f3f;

int a[N], b[N];
bitset<N> vis;
struct Node
{
    int a, b, idx;
    bool operator < (const Node &u) const
    {
        return a + b > u.a + u.b;
    }
} f[N];


void solve()
{
    int n; cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= n; i ++) cin >> b[i];
    for (int i = 1; i <= n; i ++) f[i] = {a[i], b[i], i};
    sort(f + 1, f + 1 + n);

    for (int i = 1; i <= n; i ++)
    {
        if (i & 1)
            a[f[i].idx] --, b[f[i].idx] = 0;		
        else
            a[f[i].idx] = 0, b[f[i].idx] --;
    }
	
    int suma = 0, sumb = 0;
    for (int i = 1; i <= n; i ++) suma += a[i];
    for (int i = 1; i <= n; i ++) sumb += b[i];
	
    cout << suma - sumb << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T; cin >> T;
    while (T --) solve();
    return 0;
}
```

---

