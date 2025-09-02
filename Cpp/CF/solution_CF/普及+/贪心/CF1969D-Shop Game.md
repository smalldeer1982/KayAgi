# Shop Game

## 题目描述

Alice 和 Bob 正在商店里玩游戏。商店里有 $n$ 件商品；每件商品有两个参数： $a_i$（Alice 买进的物品价格）和 $b_i$（愿意出的物品价格）。

Alice 希望选择一个商品子集（可能是空）并购买它们。之后，Bob 会执行以下操作：

- 如果 Alice 购买的物品少于 $k$，Bob 可以免费拿走所有物品；
- 否则，他会免费拿走 Alice 购买的 $k$ 个物品（由 Bob 选择是哪些 $k$ 个物品），至于其他被选中的物品，Bob 会从 Alice 那里购买，并为 $i$ 号物品支付 $b_i$。

Alice 的利润等于 $\sum\limits_{i\in S}b_i-\sum\limits_{j \in T}a_j$，其中 $S$ 是 Bob 从 Alice 处购买的物品集，$T$ 是 Alice 从商店购买的物品集。换句话说，Alice 的利润就是 Bob 支付给她的金额和她购买商品所花费的金额之间的差额。

Alice 希望自己的利润最大化，而 Bob 希望 Alice 的利润最小化。您的任务是计算在 Alice 和 Bob 都采取最优行动的情况下 Alice 的利润。

## 说明/提示

在第一个测试用例中，Alice应该购买 $ 2 $ 然后把它卖给鲍勃，那么她的利润是 $ 2 - 1 = 1 $ 。

在第二个测试用例中，Alice应该购买 $ 1 $，$ 2 $ 和 $ 3 $ 项；然后鲍勃可以接受 $ 1 $ 免费，并支付 $ 2 $ 和 $ 3 $ 。Alice的利润是 $ (3+2) - (1+2+1) = 1 $ 。鲍勃也可以接受 $ 2 $ 为免费的物品，这不会改变Alice的利润。鲍勃不会接受 $ 3 $ 为免费的物品，因为这样 Alice 的利润为 $ 2 $。

## 样例 #1

### 输入

```
4
2 0
2 1
1 2
4 1
1 2 1 4
3 3 2 3
4 2
2 1 1 1
4 2 3 2
6 2
1 3 4 9 1 3
7 6 8 10 6 8```

### 输出

```
1
1
0
7```

# 题解

## 作者：GY程袁浩 (赞：6)

## 思路
### 考虑 Bob 的策略：

如果 Alice 选了物品 $i$，那么 Bob 如果选了物品 $i$ 会使得 Alice 对于这个物品亏多少钱。

原来赚的钱：$b_{i}-a_{i}$。

Bob 选后本金的亏损：$-a_{i}$。

那么 Bob 如果选了物品 $i$ 会就使得 Alice 对于这个物品亏：
$-(b_{i}-a_{i})-a_{i}=-b_{i}$。

所以我们知道 Bob 应该选前 $k$ 大 $b_{i}$ 的 $i$ 才能使在目前 Alice 选出的物品中让他亏损最多。

### 考虑 Alice 的策略：

首先 Alice 选出的前 $k$ 大的物品一定不赚钱。

那么如果选的物品不多于 $k$ 且至少选了一个物品，就一定是亏的，在最坏的情况下，我们可以什么都不选来保证不亏钱。

所以可以选 $k$ 个物品来献祭，来让其它选的物品赚钱，但也不是选哪个献祭都可以，那 $k$ 个献祭的物品的 $b_{i}$ 必须在所有选出的物品的 $b$ 里是前 $k$ 大。

那么如何才能让献祭的物品由我们选择呢？可以选择将 $b$ 由大到小排序，这样最左边的我们选择的 $k$ 个物品就一定是献祭的，又由于我们需要献祭的钱最少，所以选 $a_{i}$ 前 $k$ 小的 $i$ 就可以了。那么选的第 $k$ 个物品往后怎么选？只需要挑 $b_{i}>a_{i}$ 的选就行了，因为如果选其它的必然不赚钱。

但是我们不能只考虑前 $k$ 个物品献祭，所以要枚举考虑献祭的最后一个 $i$ 的分界线。

## 做法
将 $b_{i}$ 排序，预处理 $i$ 到 $n$ 的买入价小于卖入价物品的利润，建立大根堆，存考虑到献祭的前 $k$ 小的 $a_{i}$，维护堆内和。接下来枚举考虑献祭的最后一个 $i$，将 $a_{i}$ 入堆，如果堆的大小大于 $k$ 那么弹出堆顶。左边选前 $k$ 小 $a_{i}$ 的 $i$ 物品，右边选 $b_{i}>a_{i}$ 的 $i$ 物品。用右边利润和减去堆内和来更新 $ans$ 的最大值。

注意 $k$ 为 $0$ 时要特判，因为后面的做法考虑的是   Bob 至少选一个物品。

$ans$ 一开始初值为 $0$，因为 Alice 可以什么都不选。

那么这道题就做完了，代码其实不长。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool cmp(pair<int,int> x,pair<int,int> y)
{
	return x.first>y.first;
}
signed main()
{
    int tt;
    cin>>tt;
    while(tt--)
    {
        int n,k;
        cin>>n>>k;
        vector<pair<int,int> > a(n+1);
		vector<int> pre(n+2);
        for(int i=1;i<=n;i++) cin>>a[i].second;
        for(int i=1;i<=n;i++) cin>>a[i].first;
        sort(a.begin()+1,a.end(),cmp);
		for(int i=n;i>=1;i--) pre[i]=max(a[i].first-a[i].second,(int)0)+pre[i+1];
        priority_queue<int> q;
        int ans=0,sum=0;
        if(k==0)
        {
        	cout<<pre[1]<<endl;
        	continue;
		}
        for(int i=1;i<=n;i++)
        {
            q.push(a[i].second);
            sum+=a[i].second;
            if(q.size()>k&&q.size()) sum-=q.top(),q.pop();
			if(q.size()==k) ans=max(ans,pre[i+1]-sum);
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：AlicX (赞：3)

## Solution 

Alice 的最优策略有两种：要么一个都不选，要么选择 $k$ 个及以上。

那么对于已定集合 $S$，Bob 一定会选择前 $k$ 大的 $b_i$ 不支付，这样一定是最优的。

所以对原数组按 $b_i$ 从小到大排序，枚举第 $k$ 大的 $b_i$ 的下标 $i$，那么 Alice 为了使得自己损失最小一定会在 $i \sim n$ 中选择前 $k$ 小的 $a_i$。

此时 Alice 已经选择了 $k$ 个商品了，那么接下来她可选择也可以不选，在最优策略下，她会选择在 $1 \sim i-1$ 中 $b_i>a_i$ 的商品，这会使她盈利。

所以对于每一个 $i$：维护 $i \sim n$ 前 $k$ 小的 $a_i$ 值，并且维护 $1 \sim i-1$ 中 $b_i-a_i[b_i>a_i]$ 的和。

答案记得与 $0$ 取较大值。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2e5+10; 
int n,k; 
pii a[N]; int f[N]; 
il bool cmp(pii a,pii b){ 
	return a.y<b.y; 
} 
il void solve(){ 
	n=read(),k=read(); 
	for(int i=1;i<=n;i++) a[i].x=read(); 
	for(int i=1;i<=n;i++) a[i].y=read(); 
	sort(a+1,a+n+1,cmp); int ans=0; 
	int num=0; priority_queue<int> q; 
	for(int i=n;i>=n-k+1;i--) q.push(a[i].x),num+=a[i].x; 
	for(int i=n-k+1;i>=1;i--){ 
		f[i]=num; 
		if(q.size()&&q.top()>a[i-1].x) num-=q.top(),q.pop(),q.push(a[i-1].x),num+=a[i-1].x; 
	} for(int i=1,sum=0;i<=n-k+1;i++){ 
		ans=max(ans,sum-f[i]); 
		if(a[i].y>a[i].x) sum+=a[i].y-a[i].x; 
	} printf("%lld\n",ans); 
} 
signed main(){ 
	int T=read(); 
	while(T--) solve(); 
	return 0; 
} 
```

---

## 作者：ilibilib (赞：1)

### 分析：

我们设 $b$ 是 Alice 拿的物品出口价数组，$a$ 是 Alice 拿的物品的进口价数组。

可以得到 Alice 的利润为 $\sum b-\sum a$。

在 Alice 做出决策后，Bob 的操作只能对 $\sum b$ 产生影响，为了使这个值最小，他就一定会拿走出口价最大的 $k$ 的物品。

所以我们先按 $b$ 进行排序。

考虑在前 $i$ 个物品中选出 $k$ 个物品被 Bob 拿，这些物品的 $b$ 不对总利润产生影响了，那么要使利润最大，就要 $-\sum a$ 最大，即选出最小的 $k$ 个 $a_i$，对于后面的物品，不会被 Bob 拿了，那么只要 $b-a$ 大于 $0$ 就拿就行了。

枚举 $i$ 即可，$i\in[k,n]$。

### code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
int a[N],b[N],id[N],s[N];
multiset<int>p;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        int n,k,ans=0,sum=0;
        cin>>n>>k;
        for(int i=1;i<=n;++i) cin>>a[i];
        for(int i=1;i<=n;++i) cin>>b[i];
        for(int i=1;i<=n;++i) id[i]=i;
        sort(id+1,id+n+1,[](const int i,const int j){return b[i]!=b[j]?b[i]>b[j]:a[i]<a[j];});
        s[n+1]=0;
        for(int i=n;i>=1;--i) s[i]=s[i+1]+max(b[id[i]]-a[id[i]],0ll);
        if(k==0) {cout<<s[1]<<'\n';continue;}
        for(int i=1;i<=k;++i)
        {
            sum-=a[id[i]];
            p.insert({-a[id[i]]});
        }
        ans=max(ans,sum+s[k+1]);
        for(int i=k+1;i<=n;++i)
        {
            if(a[id[i]]<-*p.begin())
            {
                sum-=a[id[i]]+*p.begin();
                p.erase(p.begin());
                p.insert(-a[id[i]]);
            }
            ans=max(ans,sum+s[i+1]);
        }
        p.clear();
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：Jerrycyx (赞：1)

#### 对于 Bob

B 的每次零元购相当于吞掉了 A 本应获得的 $b_i$ 元，这些钱就相当于是 A 净亏的。

考虑当 A 选出商品后花的钱 $\sum_{i \in T} a_i$ 已经定了，这时 B 能做的只有让 A 得的钱尽量少，亏得尽量多，它就会按 $b_i$ 从大到小零元购，这样可以让剩下的 $b_i$ 之和最小，A 得的最少，利润也就最少。

#### 对于 Alice

买少于或等于 $k$ 件物品反正都会被 B 零元薅走，一定亏。所以要么一件都不买，不亏不赚；要么买多于 $k$ 件，才有机会赚。

选出的物品中，$b_i$ 值在前 $k$ 大的是一定会被 B 先零元购的，只有其他商品才能带来利润。所以，将所有商品按 $b_i$ 的值从大到小排序，这样可以保证 B 所选的一定是靠左边的 $k$ 个，而右边剩下的就是可以赚钱的。

枚举拿出去投喂 B 的商品和正常赚钱的商品的分界线。

在分界线左侧，当然是希望净亏的越少越好，所以选择的一定是 $a_i$ 最小的 $k$ 个，这部分可以用优先队列维护选出来的 $k$ 个商品的最大 $a_i$ 值，每次分界线右移的时候如果当前的 $a_i$ 比堆顶最大的还大，那么就一定可以顶掉这个堆顶。弹出堆顶并把这个 $a_i$ 压进去即可。

在分界线右侧，凡是 $b_i-a_i>0$ 的都可以选，所以可以另计一个 $sum_i$ 表示从 $i$ 到 $n$ 只取 $b_i-a_i>0$ 的总利润。

得到每次左侧的最小花费和右侧的最大利润之后，两者结合即可计算出此时实际利润。对所有的分界线算出来再取最大值就是 A 在 B 采取最优策略下所能得到的最大利润。

这个最大利润可能仍然是负数。这个时候不如不取，还需处理一下。

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=2e5+5;
int n,k;
pair<int,int> money[N];
long long sum_rev[N];
priority_queue<int> sorry;

bool cmp(pair<int,int> x,pair<int,int> y)
{
	return x.second>y.second;
}
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&money[i].first);
		for(int i=1;i<=n;i++) scanf("%d",&money[i].second);
		sort(money+1,money+n+1,cmp);
		for(int i=n;i>=1;i--)
			sum_rev[i]=sum_rev[i+1]+max(money[i].second-money[i].first,0);
		long long oh_no=0;
		for(int i=1;i<=k;i++)
		{
			sorry.push(money[i].first);
			oh_no+=money[i].first;
		}
		long long ans=0;
		for(int i=k+1;i<=n;i++)
		{
			ans=max(ans,sum_rev[i]-oh_no);
			if(sorry.empty()) continue;
			if(money[i].first<sorry.top())
			{
				oh_no-=sorry.top(); sorry.pop();
				oh_no+=money[i].first; sorry.push(money[i].first);
			}
		}
		printf("%lld\n",ans);
		
		for(int i=1;i<=n;i++) sum_rev[i]=0;
		while(!sorry.empty()) sorry.pop();
	}
	return 0;
}
```

---

## 作者：Msents (赞：1)

先考虑 Bob 的策略。

很明显的，为了使利润最小，他会白嫖 $b_i$ 最大的 $k$ 个被 Alice 选中的物品。

现在再来考虑 Alice 的策略。

此时题意转化为：挑选一些物品，选中了 $i$ 号物品产生的利润为 $b_i-a_i$，但 $b_i$ 前 $k$ 大的物品不会产生利润，还会倒扣 $a_i$，求最大利润。

考虑如果没有后面一条限制，那直接挑选 $b_i-a_i>0$ 的物品即可。

因为前 $k$ 个 $b_i$ 最大的物品会倒扣 $a_i$，考虑将两部分拆开，分别计算。

因为第一部分不要求顺序，可以将数组按 $b_i$ 从大到小排序，从左到右维护左边被选的物品和右边被选的物品。

具体的，左边维护一个大小为 $k$ 的集合，设每次将 $a_i$ 塞进集合，并将最大的值踢出集合，右边挑选 $b_i-a_i>0$ 的物品即可。

答案即为过程中右边的最大利润减去左边的集合的和的最大值。

~~所以优先队列在顶端，为什么还用 set~~

码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MaxN=200000;
int n,k;
struct Pack{
	int a,b;
}arr[MaxN+1];
void Solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>arr[i].a;
	for(int i=1;i<=n;i++)cin>>arr[i].b;
	sort(arr+1,arr+1+n,[](Pack a,Pack b){
		return a.b==b.b?a.a<b.a:a.b>b.b;
	});
	int ans=0,sum=0;
	multiset<int>set;
	for(int i=1;i<=k;i++)set.insert(arr[i].a),sum-=arr[i].a;
	for(int i=k+1;i<=n;i++)
		if(arr[i].b-arr[i].a>0)
			sum+=arr[i].b-arr[i].a;
	for(int i=k+1;i<=n;i++){
		ans=max(ans,sum);
		set.insert(arr[i].a);
		sum-=arr[i].a;
		sum+=*set.rbegin();
		set.erase(--set.end());
		if(arr[i].b-arr[i].a>0)sum-=arr[i].b-arr[i].a;
	}
	cout<<ans<<'\n';

}
#undef int
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--)
		Solve();
	return 0;
}
```

---

## 作者：__Louis__ (赞：0)

## 题解：CF1969D Shop Game

### 题目大意

现在又 $n$ 个商品，Alice 以 $a_i$ 的价格将进货，然后卖给 Bob。Bob 可以选择其中的 $k$ 个免费拿走，剩下的付款 $B_i$ 元。


Alice 可以任意进货，每个货物只有一个，而 Alice 买的东西 Bob 必须拿走。

令 Alice 进货的代价为 $W_1$，Bob 购买东西的代价为 $W_2$，求一种合理的 Alice 的选购方案使得 $W_2-W_1$ 最大。

### 思路

对于 Bob 而言，肯定是免费拿走所有最大 $B_i$，然后付款剩下的。

既然如此，那么 Alice 的策略应该是先以最小的代价把把 $k$ 填满，然后再去找剩下的利益。

怎么实现这个策略？

可以先假定一个权值，这个权值往上的是 Alice 用来填充的，往下的是 Alice 用来最大化利益的。

那么先以 $B_i$ 排序，然后遍历这个权值，然后维护两个代价。

填充那一部分的代价用堆来维护，最大化利益直接维护即可。

复杂度 $O(n\log n)$。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
struct node{
	int x,y;
}arr[maxn];
bool cmp(node a,node b){
	return a.y>b.y;
}
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--){
		int n,k;
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld",&arr[i].x);
		}
		int sum1=0,sum2=0,ans=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&arr[i].y);
			sum2+=max(arr[i].y-arr[i].x,(int)0);
		}
		priority_queue<int,vector<int>,less<int> > q;
		sort(arr+1,arr+1+n,cmp);
		for(int i=1;i<=k;i++){
			sum2-=max(arr[i].y-arr[i].x,(int)0);
			q.push(arr[i].x);
			sum1+=arr[i].x;
		}	
		ans=max(sum2-sum1,ans);
		for(int i=k+1;i<=n;i++){
			q.push(arr[i].x);
			sum1+=arr[i].x;
			sum1-=q.top();
			q.pop();
			sum2-=max(arr[i].y-arr[i].x,(int)0);
			ans=max(sum2-sum1,ans);
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Wyy_w123 (赞：0)

## 题目大意

有 $n$ 件物品，每件物品有价格 $a_i$ 和 $b_i$。小 A 可以花 $a_i$ 元购买一件物品，而小 B **必须** 花 $b_i$ 元购买小 A 的所有物品，但小 B 可以使 $k$ 个小 A 的物品 $b_i$ 变成 $0$。

小 A 想要得到最大的利润（及购买物品中 $b_i-a_i$ 的和），但小 B 希望小 A 的利润尽可能小。你需要求出小 A 最后能赚到的钱。

## 思路

设 $ans$ 为 小 A 最后能赚到的钱。

让我们先来考虑小 B 的策略。原来一件物品能让小 A 得到 $b_i - a_i$ 元；而小 B 将 $b_i$ 变成 $0$ 后， 小 A 则只会得到 $-a_i$ 元，即 $ans$ 减少了 $b_i$ 元。很显然，为了让 $ans$ 尽可能小， 小 B 会免费小A $b_i$ 最大的 $k$ 个。

那我们可以把小 A 选的物品看做成两个部分：
- $b_i$ 最大的 $k$ 个物品
- 其它物品。

对于第一个部分，小 A 会选 $a_i$ 最小的以降低亏损；第二个部分，小 A 会选所有 $b_i > a_i$ 的。将所有物品的 $b_i$ 从小到大排序后，就可以维护一个分界线：左边用前缀和，右边用优先队列维护答案即可。

---

## 作者：__HHX__ (赞：0)

# 思路
因为 Bob 希望 Alice 的利润最小化。

又因为 Bob 免费拿只能影响卖出的价格 $b_i$。

所以 Bob 最优策略为 Alice 选择的前 $k$ 大的 $b_i$。

我们设集合 $T$ 为 Alice 选择的最优集合。

当 $|T| \leq k$ 很明显在此情况 Bob 会免费拿走所有，所以还不如不卖，故在此情况 $0$ 为最优解，所以接下来讨论的情况为 $|T| > k$。

我们记函数 $F(S)$ 为 $S$ 中前 $k$ 大的 $b_i$ 的和。

则答案可以记为 $(\sum_{i \in T} b_i - a_i) - F(T)$。

设 $S = \{x \in [1, n],x \in \mathbb{Z} \mid b_x - a_x > 0 \}$。

很显然当 $T = S$ 时答案并不一定最优。

但可以肯定 $T \subset S$。

我们考虑在 $S$ 中删除元素。

设我们选择删除 $x$ 其中 $x \in S$。

若 $b_x$ 不为 $S$ 前 $k$ 大，则答案变为 $\text{原答案} - (b_x - a_x)$，又因为 $b_x > a_x$ 所以答案一定更劣，故不取。

若 $b_x$ 为 $S$ 前 $k$ 大，则答案变为 $\text{原答案} - (b_x - a_x) + b_x - b_y$ 即 $\text{原答案} + a_x - b_y$ 其中 $y$ 为 $b_y$ 第 $k + 1$ 大，注意此时是将 $x$ 删去，所以大小顺序会变化。

因为我在此情况下选任意值都不能改变 $b_y$ 的值，所以我们要使 $a_x$ 最大，很容易想到优先队列维护此值。

设优先队列 $G$ 为 $b_i(i \in S)$ 为前 $k$ 大，以 $a_i$ 从大到小排序，即大根堆。

我就可以将操作变为：

1. 取出 $G$ 堆顶为 $c$。

2. $\text{答案} = \text{原答案} + c - b_y$

3. 将 $a_y$ 存入 $G$。

其中你可直接对 $b$ 排序以满足快速找到当前第 $k + 1$ 大。

---

## 作者：_LSA_ (赞：0)

注意到 Bob 只会取 Alice 选出的商品中前 $k$ 大的 $b_i$。

考虑贪心，容易想到按照 $b_i$ 从大到小排序，枚举一个分界线，在分界点左边的数选出 $k$ 个让 Bob 免费拿走，在分界点右边的数选出一部分卖给 Bob。

显然左边的数应该取 $a_i$ 前 $k$ 小的，右边的数取所有 $b_i-a_i > 0$ 的。

前 $k$ 小的数开个大根堆维护，堆的大小超过 $k$ 时不断弹出堆顶即可。

时间复杂度 $O(n \log {n})$。

```cpp
const int N = 2e5+10;
int n,k;
struct node{
	int a,b;
}c[N];
bool cmp(node x,node y){
	return x.b != y.b ? x.b > y.b : x.a > y.a;
}
priority_queue<int> q;
int main(){
	int T = read();
	while(T--){
		n = read(); k = read();
		for(int i=1;i<=n;i++) c[i].a = read();
		for(int i=1;i<=n;i++) c[i].b = read();
		sort(c+1,c+1+n,cmp);
		ll ans = 0,sum = 0,res = 0;
		for(int i=1;i<=n;i++) if(c[i].b > c[i].a) res += c[i].b-c[i].a;
		if(!k) ans = res;
		while(!q.empty()) q.pop();
		for(int i=1;i<=n;i++){
			q.push(c[i].a); sum += c[i].a; 
			if(c[i].b-c[i].a > 0) res -= c[i].b-c[i].a;
			while(q.size() > k) sum -= q.top(),q.pop();
			if(q.size() == k) ans = max(ans,res-sum);
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：破壁人罗辑 (赞：0)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF1969D)/[Codeforces](https://codeforces.com/problemset/problem/1969/D)

## 题目大意

给出 $a,b$ 两个数组和一个整数 $k$，Alice 需要选择一个集合 $S$，Bob 需要在 $S$ 中选择一个大小不超过 $k$ 的子集 $T$ 使得 $\sum_{i\in S-T}b_i-\sum_{i\in S}a_i$ 最小化，问在 Bob 选择最优方案的情况下 $\sum_{i\in S-T}b_i-\sum_{i\in S}a_i$ 的最大值是多少。

## 解题思路

若 $S=\empty$，则 $T=\emptyset$，$\sum_{i\in S-T}b_i-\sum_{i\in S}a_i=0$。

若 $S$ 包含了 $m\leq k$ 件物品，则令 $T=S$，得到的 $\sum_{i\in S-T}b_i-\sum_{i\in S}a_i\leq0$，不为最优。

若 $S$ 包含了 $m>k$ 间物品，注意到 $\sum_{i\in S-T}b_i-\sum_{i\in S}a_i=\sum_{i\in S}(b_i-a_i)-\sum_{i\in T}b_i$，则 Bob 的最优方案一定是令 $T$ 包含了在 $S$ 中 $b_i$ 最大的 $k$ 个 $i$。

若 $b_i<a_i$，则选取时一定不优，接下来只考虑 $b_i\geq a_i$ 的情况。

在 $S$ 中删去一个元素时，设此时 $b_t$ 是已选择的 $m$ 个物品中第 $k+1$ 大的 $b$。若 $s\in T$，则删去第 $s$ 个元素时的答案为 $\sum_{i\in S-\{s\}}(b_i-a_i)-\sum_{i\in T-\{s\}+\{t\}}b_i=\sum_{i\in S}(b_i-a_i)-\sum_{i\in T}b_i+(a_s-b_t)$；若 $s\notin T$，则删去第 $s$ 个元素时的答案为 $\sum_{i\in S-\{s\}}(b_i-a_i)-\sum_{s\in T}b_i=\sum_{i\in S}(b_i-a_i)-\sum_{i\in T}b_i-a_s$，由此可得，删去不在 $T$ 中的元素得到的答案一定比原先更劣，删去在 $T$ 中的元素时删去的 $s$ 对应的 $a_s$ 越大答案越优。

所以我们可以先选取 $S$ 为全集，将数组 $a,b$ 依据 $b$ 单调递减的顺序排序，$T$ 为对应 $b$ 最大的 $k$ 个元素，设置一个以 $a$ 为比较依据的大根堆，每次操作时给 $T$ 加上 $S$ 中第 $k+1$ 大的 $b_i$ 对应的 $i$ 且将 $S$ 和 $T$ 减去 $T$ 中最大的 $a_i$ 对应的 $i$，即第 $i$ 次操作将答案减去堆顶的 $a$ 并加上 $b_{k+i}$，令 $ans$ 为所有操作时的答案的最大值，则 $ans$ 即为所求。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> p[200000];
bool cmp(pair<int,int> x,pair<int,int> y){return x.second>y.second;}
struct pLess{
	bool operator()(int x,int y)const{return p[x].first<p[y].first;}
};
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,k;scanf("%d%d",&n,&k);
		for(int i=0;i<n;i++)scanf("%d",&p[i].first);
		for(int i=0;i<n;i++)scanf("%d",&p[i].second);
		for(int i=0;i<n;i++)while(p[i].second<=p[i].first&&i<n)p[i]=p[--n];
		if(n<=k){puts("0");continue;}
		long long ans=0,sum=0;
		for(int i=0;i<n;i++)sum+=p[i].second-p[i].first;
		if(k==0){printf("%lld\n",sum);continue;}
		priority_queue<int,vector<int>,pLess>q;sort(p,p+n,cmp);
		for(int i=0;i<k;i++){sum-=p[i].second;q.push(i);}
		ans=max(0ll,sum);
		for(int i=k;i<n;i++){
			sum+=p[q.top()].first-p[i].second;
			q.pop();q.push(i);ans=max(ans,sum);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

