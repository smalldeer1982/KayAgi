# Elections

## 题目描述

You are running for a governor in a small city in Russia. You ran some polls and did some research, and for every person in the city you know whom he will vote for, and how much it will cost to bribe that person to vote for you instead of whomever he wants to vote for right now. You are curious, what is the smallest amount of money you need to spend on bribing to win the elections. To win elections you need to have strictly more votes than any other candidate.

## 样例 #1

### 输入

```
5
1 2
1 2
1 2
2 1
0 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 2
1 2
2 1
0 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
100000 0
```

### 输出

```
0
```

# 题解

## 作者：Computer1828 (赞：5)

一血。

------------

考虑贪心、二分，我们可以二分需要多少张票，然后问题就会转化成已知要多少张票，然后求花费的最小值。不难发现买多少票和花费成正比，所以可以二分。

然后考虑怎么买票超过自己的对手：假设我需要 $x$ 张票，那么，所有票数大于等于 $x$ 的人的票都得买走，要不然他们就会阻止我当州长；其次，我肯定要尽量买便宜的，所以需要在读入后对票价排序；最后，如果我买了这些票数大于等于 $x$ 的人的票后还不够 $x$ 张，那我就不得不从剩下的票池里买了，而且也一定会去买便宜的。

代码：

```cpp
#include<bits/stdc++.h>
#define N 100000
using namespace std;
int n;
vector<int> a[N+5];
inline int check(int u){//返回需要u张票要花多少钱
	int ans = 0,tot = a[0].size();
	vector<int> nti;//剩下的票池
	for(int i = 1;i<=N;++i){
		int j = 0,k = a[i].size();
		while(k>=u) ans += a[i][j++],--k,++tot;//把票数大于等于u的人的票买掉
		while(j<a[i].size()) nti.push_back(a[i][j++]);
	}
	sort(nti.begin(),nti.end());
	for(int i = 0;i<nti.size();++i){
		if(tot>=u) break;//如果够票了，就退出
		ans += nti[i],++tot;//不够票就继续买
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	int u,v;
	for(int i = 1;i<=n;++i) scanf("%d%d",&u,&v),a[u].push_back(v);
	for(int i = 1;i<=N;++i) sort(a[i].begin(),a[i].end());
	int l = 1,r = n;
	while(l<=r){
		int mid = (l+r)/2;
		if(check(mid) < check(mid+1)) r = mid-1;
		else l = mid+1;
	}
	printf("%d",check(l));
	return 0;
}
```

---

## 作者：AladV (赞：2)

## 题意分析
~~就，我们教练说题目翻译三观不正，就这样......~~

## 做法分析
其实如果一味的选择需要的钱最少的人去获取的话，不一定是最优的，因为你的目标是削弱你的敌人，而不是让你自己变得更强。

我们二分一个 $x$ 表示最后你赢的时候有 $x$ 张选票，这样一来问题就转化成了：花最少的钱，使得所有对手的票数量小于 $x$。这样一来，对于每一个敌对党派，我们找出耗费最少的把他买通，然后把这个人加入到自己的党派即可。
细节代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
struct Seven_favor_Seven_against_Cast_and_recast_Seven_times
{
    int tar;
    int val;
}a[N];
int n;
int l,r;
int cnt[N];
bool alli[N];
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
bool cmp(Seven_favor_Seven_against_Cast_and_recast_Seven_times x,Seven_favor_Seven_against_Cast_and_recast_Seven_times y)
{
    return x.val<y.val;
}
int check(int x)
{
    memset(cnt,0,sizeof(cnt));
    int mine=0;
    int res=0;
    for(int i=1;i<=n;i++)
    {
        if(!a[i].tar) mine++,alli[i]=true;
        else alli[i]=false,cnt[a[i].tar]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(!alli[i] && cnt[a[i].tar]>=x) 
        {
            cnt[a[i].tar]--;
            mine++;
            res+=a[i].val;
            alli[i]=true;
        }
    }
    if(mine<x)
    {
        for(int i=1;i<=n;i++)
        {
            if(!alli[i]) 
            {
                mine++;
                res+=a[i].val;
            }
            if(mine==x) return res;
        }
    }
    else return res;
    return 1e18;
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i].tar=read(),a[i].val=read();
    sort(a+1,a+n+1,cmp);
    l=1,r=0x3f3f3f3f;
    int ans=0x3f3f3f3f;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        int curans=check(mid);
        if(check(mid+1)>=curans) r=mid-1,ans=curans;
        else l=mid+1;
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：傅思维666 (赞：2)

## 题解：

一眼看出来贪心。

是CF1019A的加强版。

CF1019A是N^2贪心就能过，这个必须加二分枚举。

当然，贪心策略都是一样的。

咋贪呢？发现如果正向考虑买票，并不是买价格最小的选民就最优，因为其他党派比你票多，如果你在削弱大党的同时给自己买票，有可能会更优。

所以考虑逆向贪心。

直接枚举自己最终胜选的票数是多少票，假设是$x$张。然后显然，高于这些票数的党派都需要被砍成$x-1$张才能保证让联合党胜出。在砍这些党派的过程中，肯定要从小到大买。

在砍完这些党派之后，如果1党还是没有等于x，那只好从剩下的所有党派中从小到大买。

然后发现这整个算法流程就是一二分判断。

代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=3003;
int n,m;
vector<int> v[maxn];
ll check(int x)//买x张选票能否更优
{
	ll ret=0;
	int tot=0;
	vector<int> tmp;
	for(int i=1;i<=m;++i)
	{
		int j=0,k=v[i].size();
		while(k>=x) 
			ret+=v[i][j++],--k,++tot;
		while(j<v[i].size()) 
			tmp.push_back(v[i][j++]);
	}
	sort(tmp.begin(),tmp.end());
	for(int i=0;i<tmp.size();++i)
	{
		if(tot>=x) 
			break;
		ret+=tmp[i],++tot;
	}
	return ret;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int p,c;
		scanf("%d%d",&p,&c);
		v[p].push_back(c);
	}
	for(int i=1;i<=m;i++)
		sort(v[i].begin(),v[i].end());
	for(int i=0;i<v[1].size();i++)
		v[1][i]=0;
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)<check(mid+1))
			r=mid-1;
		else
			l=mid+1;
	}
	printf("%lld\n",check(l));
	return 0;
}
```


---

## 作者：ka_da_Duck (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF457C)

思路： 
-

只能让敌对党派的支持这边少，设我方党派最后有 $x$ 名支持者，则敌对党派的支持者的最大值应 $<x$。

首先答案是一个凸的函数，所以三分 $x$ 的取值。

所以我们要按金额从小到大一直买通每一个敌对党派的支持者，直到它的支持者个数 $<x$。

如果执行完上述操作后我方党派支持者还不足 $x$ 名，那么剩下的按金额从小到大收买即可。

代码
-

```cp
#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10;

int n, m;
// m 表示党派数量 
vector<int> e[maxn];

long long ck(int x) {
	long long ans = 0, tot = 0;
	// ans 统计需要的比特币, tot 记录当前我方的人数 
	vector<long long> k;
	for (int i = 1; i <= m; ++i) {
		int nw = 0, sz = e[i].size();
		// nw 记录当前敌对党派的选择人数 
		while (sz >= x) ans += e[i][nw++], --sz, ++tot;
		// 让每一个敌对党派的支持者小于 x 
		while (nw < e[i].size()) k.push_back(e[i][nw++]);
		// 记录剩余的支持者 
	}
	sort(k.begin(), k.end()); 
	for (auto o: k) {
		if (tot >= x) break;
		// 如果我方的支持者依旧不足 x, 那么在剩下的支持者中从小到大选至 x 个 
		ans += o, ++tot;
	}
	return ans; 
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1, u, v; i <= n; ++i) {
		cin >> u >> v;
		if (u == 1) v = 0;
		// 1 是我方党派, 所以不需要收买 
		e[u].push_back(v);
	}
	for (int i = 1; i <= m; ++i) sort(e[i].begin(), e[i].end());
	long long l = 1, r = n;
	//for (int i = 1; i <= n; ++i) cout << ck(i) << '\n';
	while (l <= r) {
		long long mid = l + r >> 1;
		if (ck(mid) < ck(mid + 1)) r = mid - 1;
		else l = mid + 1;
	}
	cout << ck(l);
} 
```

---

## 作者：Piwry (赞：1)

## 解析

首先考虑确定最后获胜时的得票数为 $x$ 时该怎么做

可以考虑先将所有其它队伍的得票 “削减” 直到小于 $x$，“削减” 每个队伍时都贪心选它们最便宜的票；如果此时自己的得票还不到 $x$，就从剩下的票中再选票（也是贪心选最便宜的）补到 $x$

接着不难发现花费随 $x$ 的增大一定是一段前缀下降，之后均上升的。即在到达最优花费的 $x$ 之前都是下降的，因为更小的 $x$ 需要 “削减” 其它队伍更多的票；而到达后再增大 $x$，因为每次在 “削减” 完后还不得不再从剩下的票中选一些，将自己的票数补到 $x$

于是可以考虑直接三分法。复杂度 $\Theta(n\log n)$

另外具体实现时，可能发现某些 $x$ 的取值是不存在的（“削减” 其它队伍的票数时就导致自己的票数超过 $x$ 了）。考虑到每次计算某个 $x$ 时算法的特性（仅可能导致最后的 $x$ 大于预期），我们不妨将某个不存在取值的 $x$ 处的点值规定为右侧第一个有值点的点值（具体实现时不用管 $x$ 是否合法直接返回答案即可）

这样处理后三分法的正确性并不会受到影响

## CODE

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#define ll long long
using std::vector;
using std::sort;
using std::min;
using std::max;

const int MAXN =1e5+20;

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

struct pad{
	int val, id;
	
	pad(){}
	pad(const int &V, const int &I):val(V), id(I){}
	
	bool operator < (const pad &B) const{
		return val > B.val;
	}
};

vector<pad> sup[MAXN], arr;

bool vis[MAXN];

ll check(const int &x, const int &m){
	ll ret =0;
	int nw =sup[1].size();
	memset(vis, 0, sizeof(vis));
	for(int i =2; i <= m; ++i)
		for(int j =sup[i].size()-1; j+1 >= x; --j){
			ret +=sup[i][j].val;
			vis[sup[i][j].id] =1;
			++nw;
		}
	for(int k =0; k < (int)sup[1].size(); ++k)
		vis[sup[1][k].id] =1;
	for(int k =arr.size()-1; k >= 0 && nw < x; --k)
		if(!vis[arr[k].id]){
			ret +=arr[k].val;
			++nw;
		}
	// 貌似函数一些点值处不存在取值 //
	// 我们规定这些点值处的取值为右侧第一个有值点的点值 //
	// 这样拓展下还是能用三分法 //
//	if(nw < x || nw > x)
//		return 0x3f3f3f3f3f3f3f3f;
//	else
		return ret;
}

int main(){
	int n =read(), m =1;
	for(int i =1; i <= n; ++i){
		int p =read()+1, c =read();
		sup[p].push_back(pad(c, i));
		arr.push_back(pad(c, i));
		m =max(m, p);
	}
	sort(arr.begin(), arr.end());
	for(int i =2; i <= m; ++i)
		sort(sup[i].begin(), sup[i].end());
	ll ans =0x3f3f3f3f3f3f3f3f;
	int l =max(1, (int)sup[1].size()), r =n;
	while(1){
		int midl =(l+r)>>1, midr =(midl+r)>>1;
		if(midl == midr){
			for(int i =l; i <= r; ++i)/*实现习惯；枚举次数应当不超过 3*/
				ans =min(ans, check(i, m));
			break;
		}
		ll tmpl =check(midl, m), tmpr =check(midr, m);
		if(tmpl < tmpr){
			ans =min(ans, tmpr);
			r =midr-1;
		}
		else{
			ans =min(ans, tmpl);
			l =midl+1;
		}
	}
	printf("%lld", ans);
}
```

---

