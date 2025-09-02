# Best Price

## 题目描述

伯兰德最大的商店收到了一批圣诞树，并已有 $n$ 位顾客前来欲购这些树。在销售启动前，商店需要统一为每棵树定价。为了合理制定价格，商店掌握了关于每位顾客的一些信息。

对于第 $i$ 位顾客，有两个已知整数 $a_i$ 和 $b_i$，它们定义了顾客的购物行为：

- 如果价格不超过 $a_i$，顾客将购买一棵树并给出正面评价；
- 如果价格超过 $a_i$ 但不超过 $b_i$，顾客仍会购买，但会留下负面评价；
- 如果价格高于 $b_i$，则顾客将不会购买。

在负面评价不超过 $k$ 条的前提下，你的任务是帮助商店计算出最大的可能收益。

## 说明/提示

考虑以下例子：

- 在第一个测试用例中，如果价格设为 $1$，两位顾客都会各买一棵树且没有负面评价。
- 在第二个测试用例中，如果价格设为 $5$，顾客会购买一棵树且给出一条负面评价。
- 在第三个测试用例中，如果价格定为 $3$，所有顾客会购买且将收到两条负面评价。
- 在第四个测试用例中，价格定为 $7$ 时，有两位顾客购买，一条负面评价。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2 0
2 1
3 4
1 1
2
5
3 3
1 5 2
3 6 4
4 3
2 3 2 8
3 7 3 9
3 1
2 9 5
12 14 9```

### 输出

```
2
5
9
14
15```

# 题解

## 作者：ohjun (赞：4)

## 思路分析
通过贪心不难发现我们的定价一定等于某一个 $a_i$ 或 $b_i$，否则如果选一个中间值一定可以通过提高定价到一个离它最近的 $a_i$ 或 $b_i$ 从而提高赚的钱并且没有任何负收益。 所以直接枚举所有 $a_i$ 和 $b_i$，不难通过二分算出在当前价格下的总销量（二分 $b$）和不给差评的人的数量（二分 $a$），如果差评的人的数量小于等于 $k$ 则统计答案。时间复杂度 $O(n\log{n})$。
## Code

```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int maxn = 2e5 + 5;
    int t, n, k;
    ll ans;
    int A[maxn], B[maxn];
     
    void cal(int x)
    {
    	int tot = n - (lower_bound(B, B + n, x) - B);
    	int val = n - (lower_bound(A, A + n, x) - A);
    	if(tot - val > k) return;
    	ans = max(ans, ll(tot) * ll(x));
    }
     
    int main()
    {
    	ios::sync_with_stdio(0);
    	cin.tie(0);
    	cin >> t;
    	while(t--)
    	{
    		cin >> n >> k;
    		for(int i = 0; i < n; i++)
    			cin >> A[i];
    		for(int i = 0; i < n; i++)
    			cin >> B[i];
    		sort(A, A + n);
    		sort(B, B + n);
    		ans = 0LL;
    		for(int i = 0; i < n; i++)
    		{
    			cal(A[i]);
    			cal(B[i]);
    		}
    		cout << ans << '\n';
    	}
    	return 0;
    }
```

---

## 作者：BpbjsGreen (赞：4)

对于每一个 $a_i$，对答案的影响为：增加一个差评。

对于每一个 $b_i$，对答案的影响为：减少一个购买人数，减少一个差评（因为在处理 $a_i$ 时增加了一个差评）。

我们发现，$a_i$ 对答案的影响与它所配对的 $b_i$ 无关，对于 $b_i$ 也是如此。也就是说，**我们可以任意交换 $\bm{a,b}$ 数组各个数的顺序**。

对 $a,b$ 数组排序后，价格从小到大扫一遍即可。

时间复杂度 $O(n\log n)$。

```cpp
// ID: @BpbjsGreen

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int n, k, a[N], b[N];

signed main()
{
    int T;
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld", &n, &k);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &a[i]);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &b[i]);

        sort(a + 1, a + n + 1);
        sort(b + 1, b + n + 1);
        a[n + 1] = b[n + 1] = 1e18; // 为了下文方便处理

        int nega = 0; // 差评数量
        int pri = 0; // 价格
        int num = n; // 购买人数
        int ans = 0; 

        int pa = 0, pb = 0;
        while (pa < n || pb < n)
        {
            pri = min(a[pa + 1], b[pb + 1]); // 目前移动到的价格

            if (nega <= k) // 差评条件
                ans = max(ans, pri * num); // 更新答案

            while (a[pa + 1] == pri) // 移动指针
                pa++, nega++;
            while (b[pb + 1] == pri)
                pb++, num--, nega--;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：3)

# E. Best Price

一个发现是，**单价只可能在 $a_i$ 和 $b_i$ 这 $2n$ 个数中产生**。

因为 $a_i$ 和 $b_i$ 是一个能接受的最大程度，我们要尽可能多地压榨（？）顾客。

将 $a,b$ 分别**排序**。设目前枚举的单价是 $c$，通过**二分**找到 $\geq c$ 的 $b_i$ 的个数 $B$。那么这些人就是**可能**会给出差评但是一定会买的人数。

剩下的人不可能买了，考虑这些**可能**给出差评的人是否会给出好评。好评同理，$\geq c$ 的 $a_i$ 的个数 $A$ 就是**一定**给出好评并且购买的人。如果 $B-A\leq k$ 说明这个单价是合理的。$c\times B$ 即为这个单价会购买的人产生的总花费。**枚举**所有的 $c$ 依次算出 $A,B$，如果 $B-A\leq k$ 则对 $c\times B$ 取 $\max$ 即可。

<https://codeforces.com/contest/2051/submission/297848639>

---

## 作者：wuzebang2009 (赞：2)

## 题目意思：
有 $n$ 个顾客，第 $i$ 个顾客有两个数值 $a_i$ , $b_i$ 。分别表示价格最大为 $a_i$ 时顾客会购买树并留下好评，价格最大为 $b_i$ 时顾客会购买并留下坏评，其他情况顾客不会购买。
## 思路：
我们的定价只需要关注这两个数值即可，因为只有节点值会印象购买数量和坏评数。那我们先要对每个 $a_i$ 和 $b_i$ 排序铺在一个统一的价格轴上，我们从小到大枚举，计算轴上一个节点的价格，再通过这个节点更新下个节点的信息，如果这个节点是 $a_i$ ，那么坏评数加一，因为我们下一个价格将超过 $a_i$，如果是 $b_i$ 那么坏评数建议，购买数量减一，因为第 $i$ 下一个价格将使这个人不会购买东西，最后取最大价格即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int a[200010],b[200010];

int main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        vector<pair<int,int>> ev;
        ev.clear();
        for(int i=1;i<=n;i++){
            ev.push_back(make_pair(a[i],1));
            ev.push_back(make_pair(b[i],2));
        }
        sort(ev.begin(),ev.end());
        long long ans=0;
        int cnt=n,bad=0;
        for(int i=0;i<2*n;){
            auto[x,y]=ev[i];
            if(bad<=k) ans=max(ans,x*1LL*cnt);
            while(i<2*n && ev[i].first==x){
                bad+=(ev[i].second==1);
                bad-=(ev[i].second==2);
                cnt-=(ev[i].second==2);
                i++;
            }
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：Autumn_Rain (赞：2)

一篇清晰的题解不一定要很长的文字说明。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define pb push_back
int n,k;
void solve(){
	
	cin>>n>>k;
	vector<ll>a(n),b(n);
	vector<pair<int,int> >c;
	
	for(int i=0;i<n;i++){
		cin>>a[i];
		c.pb(mp(a[i],0));
		//第二维的 0/1 判断类别 (是 a 还是 b)
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
		c.pb(mp(b[i],1));
		//第二维的 0/1 判断类别 (是 a 还是 b)
	}
	
	
	sort(c.begin(),c.end());
	
	/*默认按第一关键字大小对所有 a[i],b[i] 排序
	为什么可以排序？
	买或不买的状态在 x 决定好的那一刻就定了
	我们算的变化也都是分开算的, 所以可以排序*/ 
	
	ll ans=0;
	
	/*随着 x 的增大,cnt 必定不会增 
	(卖的贵了买的人就不会更多，此处可以查看一下原题面来理解， 
	也可以根据简化题面中 cnt 的定义自行理解)
	
	不难发现，x 只取 c 中第一关键字的值，依次枚举一定可以得出最大贡献
	为什么它总是可以取到最大值？
	假设 c 中不存在的某个整数价格 x 是最优的。
	如果我们使用 x+1,x+2...(不超过下一个大的 c) 而不是 x，客户买不买的状态都是一样的，
	但我们卖出的每棵树都会得到更多的钱。
	因此，检查 c 的元素作为可能的价格就足够了。
	*/
	
	int cnt=n; //b[i]<=x 的数量 
	int bad=0; //差评数 
	for(int i=0;i<2*n;){ 
		ll x=c[i].first;
		//边界情况：当 x 为所有 c 中的最小值时，每个数都可以算到贡献
		if(bad<=k){//保证差评不超过 k 时才计算贡献 
			ans=max(ans,x*cnt);//计算贡献最大值 
		}
		
		while(i<2*n&&c[i].first==x){
		//找到第一个和选定 x 相等的 c 
		
			if(c[i].second==0){//属于 a[i],此时会受到差评 
				bad++;//差评变多 
			}
			
			else{ //属于 b[i],此时不买 
				bad--;//差评变少 
				cnt--;//但也不买了 
			}
			
			i++;//一直找下去直到 c[i]!=x, 这样就考虑完了所有 x=c 的边界情况 
		}
		
	}
	
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}
//时间复杂度: O(Tnlogn)
/*由于sum n<=2*10^5, 
所以: 2*(10^5)*log(2*10^5)≈40*(10^5)=4*(10^6),
足以通过 */ 

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define pb push_back
int n,k;
void solve(){
	cin>>n>>k;
	vector<ll>a(n),b(n);
	vector<pair<int,int> >c;
	for(int i=0;i<n;i++){
		cin>>a[i];
		c.pb(mp(a[i],0));
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
		c.pb(mp(b[i],1));
	}
	sort(c.begin(),c.end());
	ll ans=0;
	int cnt=n;
	int bad=0;
	for(int i=0;i<2*n;){
		ll x=c[i].first;
		if(bad<=k){
			ans=max(ans,x*cnt);
		}
		while(i<2*n&&c[i].first==x){
			if(c[i].second==0){
				bad++;
			}
			else{
				bad--;
				cnt--;
			}
			i++;
		}
	}
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--)solve();
	return 0；
}
```


圣诞快乐！

---

## 作者：K_yuxiang_rose (赞：1)

不难看出答案一定是 $a$ 数组或 $b$ 数组中的一个数，因为如果答案不在这 $2n$ 个数中，一定可以抬高价格并且使差评数不变，所以枚举这 $2n$ 个数即可。

先将两个数组排序，枚举每一个数时，设这个数为 $x$，通过二分寻找 $a$ 数组中最后一个严格小于 $x$ 的数的下标（如果都不小于就是 $0$），设这个下标为 $num1$，所以会买树并且给好评的人数为 $n-num1$。再寻找 $b$ 数组中最后一个严格小于 $x$ 的数的下标（如果都不小于就是 $0$），设这个下标为 $num2$，所以会不会买树的人数为 $num2$。

因为给差评的人数为总人数减去给好评的人数再减去不买的人数，即 $n-(n-num1)-num2$，如果这个数大于 $k$，说明不满足条件，直接退出。如果满足条件，返回买树的人数乘上价格，即 $(n-num2)\times x$。

总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int a[200005],b[200005];
int sum(int x)
{
	int l=1,r=n,num1=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(a[mid]<x) l=mid+1,num1=mid;
		else r=mid-1;
	}
	l=1,r=n;
	int num2=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(b[mid]<x) l=mid+1,num2=mid;
		else r=mid-1;
	}
	if(n-(n-num1)-num2>k) return 0;
	return (n-num2)*x;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			ans=max(ans,sum(a[i]));
			ans=max(ans,sum(b[i]));
		}
		cout<<ans<<"\n";
	}
    return 0;
}

```

https://codeforces.com/problemset/submission/2051/302170459

---

## 作者：cqbzhzf (赞：1)

[vjudge中文翻译](https://vjudge.net/problem/CodeForces-2051E#author=GPT_zh)
### 思路
- 把计算 $i$ 对最终答案的贡献分为两部分：$a_i$ 的贡献和 $b_i$ 的贡献。
- 对于 $a_i$，差评人数增加。
- 对于 $b_i$，购买人数增加，差评人数减少。
- 遍历**统计贡献**的数组并记录最大值。
- 注：使用 map 统计（方便遍历）的总时间复杂度为 $O_{n \log_n}$,实现细节看代码注释。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long//记得开long long
using namespace std;
int t,n,k,ans,sum1,sum2;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		map<int,int> cnt1,cnt2;//cnt1为差评人数，cnt2为购买人数
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			cnt1[x]++;
		}
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			cnt1[x]--;
			cnt2[x]--;
		}
		ans=sum1=0;//ans为答案，sum1为差评人数
		sum2=n;//购买人数
		for(auto [i,j]:cnt1)//i为价格
		{
			if(sum1<=k)
				ans=max(ans,sum2*i);
			sum2+=cnt2[i],sum1+=j;//分别更新购买人数和差评人数
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：imljw (赞：1)

闲话，比赛最后 $2$ 分钟极限改过的，似乎就我这个蒟蒻用了主席树。

首先，最优价格是 $a$ 数组和 $b$ 数组中的一个，那就枚举好了，先把每个顾客按 $b_i$ 排序，对于一个价格 $p$，我们可以用二分查找找到第一个比 $p$ 大的 $b_i$，那么就会有 $i - 1$ 人购买，离散化后通过[主席树](https://oi-wiki.org/ds/persistent-seg/)统计 $\sum_{j = 1}^{i - 1} a_j < p$，就可以算出负面评价的数量了，如果不超过 $k$，就把当前收益与答案取个最大值，最后输出就好了。

~~你们最想看的东西来了~~，仅供参考。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,k,c[200005],g,b[400005],an,f,rt[200005],cnt,mi;
struct ode{
    long long l,r,sum;
}t[8000005];
void change(long long &k,long long l,long long r,long long p){
    t[++cnt]=t[k];
    k=cnt;
    t[k].sum++;
    if (l==r)return;
    long long mid=(l+r)>>1;
    if (mid>=p)change(t[k].l,l,mid,p);
    else change(t[k].r,mid+1,r,p);
}
long long query(long long k, long long k2, long long p, long long l, long long r){
    if(l>=p)return t[k2].sum-t[k].sum;
    long long mid=(l+r)>>1,res=0;
    if(mid>=p)res=query(t[k].l,t[k2].l,p,l,mid);
    res+=query(t[k].r,t[k2].r,p,mid+1,r);
    return res;
}
struct node{
	long long a,b;
}a[200005];
bool cmp(node a,node b){
	return a.b<b.b;
}
int main() {
	std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
    	cin>>n>>k;
    	mi=1e16;
    	for(int i=1;i<=n;i++)cin>>a[i].a,b[i]=a[i].a,mi=min(mi,a[i].a);
    	for(int i=1;i<=n;i++)cin>>a[i].b,b[i+n]=a[i].b,c[i]=a[i].b;
    	sort(a+1,a+n+1,cmp);//顾客按照b排序
    	sort(c+1,c+n+1);
    	sort(b+1,b+2*n+1);
    	int u=0;
    	rt[0]=t[0].l=t[0].r=t[0].sum=0;
    	for(int i=1;i<=2*n;i++){
    		if(b[i]!=b[u])b[++u]=b[i];//去掉重复的，也可以不加
		}
		for(int i=1;i<=n;i++){
			a[i].a=lower_bound(b+1,b+u+1,a[i].a)-b;
			change(rt[i]=rt[i-1],1,u,a[i].a);
		}
    	g=f=0;
		an=n*mi;
		for(int i=2;i<=u;i++){
			int d=lower_bound(c+1,c+n+1,b[i])-c;
			long long g=(n-d+1)*b[i],f=query(rt[d-1],rt[n],1,1,u)-query(rt[d-1],rt[n],i,1,u);//能赚的钱和负面评价数量
			if(f<=k)an=max(an,g);
		}
		cout<<an<<'\n';
	}
	return 0;
}
```

---

## 作者：postpone (赞：1)

挺好的关于线段的维护问题。

将每个人的 $[a_i, b_i]$ 看作一条线段。考虑以一种方式遍历这些线段：当新加进来一条线段，表示买但是给差评的人多了一个；退出一条线段，则表示买的人和给差评的人都减少了一个，因为不买的人也不会给差评。对于每次加入或退出线段，都更新一次答案。

一种做法是：给每个端点打上标记，分辨是不是起点。然后将端点从小到大排序之后遍历。

设 $c$ 为买的人数，$x$ 为买且给差评的人数。初始时价格最低，所有人都会买而且不会给差评，当遍历到起点，有 $x\leftarrow x+1$；遍历到终点则有 $c\leftarrow c-1$ 和 $x\leftarrow x - 1$。每遍历一个新的值时，若 $x \leq k$，更新一次答案。

代码如下。
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<array<int, 2>> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> a[i][0];
        a[i][1] = (i >= n);
    }
    ranges::sort(a);

    ll ans{};
    int c{n};
    int x{};

    for (int i = 0; i < n * 2; i++) {
        if (i == 0 or a[i - 1][0] != a[i][0]) {
            if (x <= k) {
                ans = max(ans, 1ll * a[i][0] * c);
            }
        }
        if (a[i][1] == 0) {
            x++;
        } else {
            x--;
            c--;
        }
    }

    cout << ans << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    for (cin >> T; T--;) {
        solve();
    }

    return 0;
}
```

---

## 作者：c_legg (赞：0)

## 题意

卖一种圣诞树给 $n$ 个顾客，对于每个整数 $i\in[0,n)$，第 $i$ 个顾客当且仅当单价不大于 $b_i$ 时才会买一棵树，且当单价大于 $a_i$ 时会给出一个差评。现在要找到一个单价 $p$，使得盈利最大，且差评数不大于 $k$，并输出盈利。

## 思路

可以发现，$p\in a\cap b$。因为 $a_i\lt b_i$，所以 $\min\{a\}\lt\min\{b\},\max\{a\}\lt\max\{b\}$，证明略，当 $p\lt\min\{a\}$ 时，所有人都会买且没有差评，但显然 $p=\min\{a\}$ 时更赚。按这个道理，在差评、购买量相同的情况下，若对于原本单价 $p$ 有 $a_i\lt p\lt a_{i+1}$，那 $p=a_{i+1}$ 就更优；同理，$b_j$ 也比 $(b_i,b_j)$ 中的任何单价更优。所以，最优的单价一定存在于 $a$ 或 $b$ 数组中。

那问题就变得简单起来了，只要对 $a$ 和 $b$ 分别进行排序，分别遍历 $a$ 和 $b$ 中的每个元素，求出购买人数和差评数。

其中，对于每个购买者 $i$，$b_i\ge p$，因为 $b$ 现在是升序的，所以可以用二分来找到第一个 $i$ 使 $b_i\ge p$，购买数为 $n-i$。差评数也同理。

## 代码

想出来之后，代码就很简单了，这题的数据范围也还是很友好的：

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll t, n, k, ans;
ll a[1145141], b[1145141];

int main() {
    cin>>t;
    while(t--) {
        cin>>n>>k;
        ans=-1;
        for(ll i=0; i<n; i++) cin>>a[i];
        for(ll i=0; i<n; i++) cin>>b[i];
        sort(a, a+n);
        sort(b, b+n);

        for(ll i=0; i<n; i++) { // 遍历 a
            ll buy=lower_bound(b, b+n, a[i])-b;
            buy=n-buy;
            ll bad=n-(lower_bound(a, a+n, a[i])-a);
            bad=buy-bad;
            if(bad<=k) ans=max(ans, buy*a[i]);
        }
        for(ll i=0; i<n; i++) { // 遍历 b
            ll buy=lower_bound(b, b+n, b[i])-b;
            buy=n-buy;
            ll bad=n-(lower_bound(a, a+n, b[i])-a);
            bad=buy-bad;
            if(bad<=k) ans=max(ans, buy*b[i]);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Kendieer (赞：0)

**传送门：** [**\[洛谷\]**](/problem/CF2051E)、[**\[CodeForces\]**](https://codeforces.com/contest/2051/problem/E)

---

## 前言

这是一道非常好的离散化题目，能够充分发挥离散化的优点。（听说这题有二分做法，但是本蒟蒻不会 T\_T，期待其他 dalao 的二分题解。）

如果你还没有学过离散化，不妨先做做这题 $\rarr$ [**P1496**](/problem/P1496)。

## 思路构建

不难发现，最优价格一定在某一个 $a_i$ 或者 $b_i$ 的值。

我们不妨将每名顾客的价格范围看作一个区间，则他们对应的好评区间和差评区间分别是 $[0,a_i]$ 和 $(a_i,b_i]$。

这样我们就可以转化成了区间覆盖问题，于是我们就可以用离散化将所有顾客的区间进行排序了。

因为我们只需要保证处于 $b$ 区间的数量不多于 $k$ 即可，于是我们可以使用离散化来记录当前价格差评的数量和剩余顾客数量即可。

记住初始顾客数量为 $n$。

**PS：处理 $a_i,b_i$ 一定要计算出收益后再修改对应的差评数量和剩余顾客数量。**

时间复杂度为 $O(n\log n)$。

## 参考代码

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i,a,b) for(ll i = (a);i < (b);i++)
#define repr(i,a,b) for(ll i = (b) - 1;i>= (a);i--)
#define elif else if
#define Code_by_Kendieer return 0
typedef long long ll;
typedef unsigned long long ull;
const ll inf = 0x3f7f7f7f7f7f7f7f;

ll qread();
char readChar();
void qwrite(ll x,int t = 10);

const int maxn = 2e5 + 7;
const int mod = 998244353;
struct Node {
    ll pos = 0,type = 0;// 价格线，类型:1->a,-1 ->b
    Node (ll pos = 0,ll type = 0):pos(pos),type(type){}
};
vector<Node> nodes;

void solve(){
    nodes.clear(); // 多测记得清空
    ll n = qread(),k = qread(),ans = 0;
    rep(i,1,n+1){
        ll a = qread();
        nodes.push_back(Node(a,1));
    }
    rep(i,1,n+1){
        ll b = qread();
        nodes.push_back(Node(b,-1));
    }
    sort(nodes.begin(),nodes.end(),[](Node a,Node b)->bool{
        return a.pos == b.pos ? a.type < b.type : a.pos < b.pos;// 根据价格排序
    });
    ll cnt = n,tmpA = 0,tmpB = 0,worst = 0;
    rep(i,0,nodes.size()){
        if (nodes[i].type == 1 ) tmpA ++; // 记录当前a价格线的人数
        if (nodes[i].type == -1 ) tmpB ++;// 记录当前b价格线的人数
        if (nodes.size() - 1 > i && nodes[i].pos == nodes[i+1].pos) continue;// 处理完所有当前价格的顾客再计算。
        ll rst = cnt * nodes[i].pos;
        if (worst > k) rst = 0;
        ans = max(ans,rst);
        worst += tmpA;// 更新差评
        worst -= tmpB;
        cnt -= tmpB; // 更新购买的顾客数量
        tmpA = tmpB = 0; // 清空记录
    }
    cout << ans << endl;
}

int main(){
    // cin.tie(0),cout.tie(0);
    // ios::sync_with_stdio(0);
    int n = 1;
    n = qread();
    while(n--) solve();
    Code_by_Kendieer;
}

// =====================================================
ll qread(){
    ll r = 0,s = 1,ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    if (ch == '-') ch = getchar(),s = -1;
    while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0',ch = getchar();
    return r * s;
}
char readChar(){
    int ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    return ch;
}
void qwrite(ll x,int t){
    if (x<0) putchar('-'),x=-x;
    if (x>=t) qwrite(x/t,t);
    putchar(x%t<10?'0'+x%t:'A'-10+x%t);
}
// =====================================================
```

---

