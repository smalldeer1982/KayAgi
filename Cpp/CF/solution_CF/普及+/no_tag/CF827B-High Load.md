# High Load

## 题目描述

Arkady needs your help again! This time he decided to build his own high-speed Internet exchange point. It should consist of $ n $ nodes connected with minimum possible number of wires into one network (a wire directly connects two nodes). Exactly $ k $ of the nodes should be exit-nodes, that means that each of them should be connected to exactly one other node of the network, while all other nodes should be connected to at least two nodes in order to increase the system stability.

Arkady wants to make the system as fast as possible, so he wants to minimize the maximum distance between two exit-nodes. The distance between two nodes is the number of wires a package needs to go through between those two nodes.

Help Arkady to find such a way to build the network that the distance between the two most distant exit-nodes is as small as possible.

## 说明/提示

In the first example the only network is shown on the left picture.

In the second example one of optimal networks is shown on the right picture.

Exit-nodes are highlighted.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF827B/0a307dfc178cc97ead8d05d1f345ab6df68055f9.png)

## 样例 #1

### 输入

```
3 2
```

### 输出

```
2
1 2
2 3
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
3
1 2
2 3
3 4
3 5
```

# 题解

## 作者：流绪 (赞：2)

k 个点只能连一条边,其他点可以连至少两条边,还要边尽量少

首先我们找到一个点,让他和 k 个点相连,然后再根据这 k 个点向外扩展

为什么会想到这个呢?

首先我们考虑让边最小,那么 n 个点最小会有 n-1 条边,同时不能有环,有环就多一条边了!所以我们得一个点接着一个点连,那么显然 k 个点会在最外层,那我们就可以让一个点为中心,然后扩展出 k 个点出去,因为其他点要至少连两条边,所以他们要有一条边连这 k 个点的一个,一条边连中心点,所以只能扩展 k 个点出去

已经知道怎么构造出这个图了,那怎么算答案呢?

首先我们取出一个点也就是 n-1,然后要扩展出 k 个点,这 k 个点的到中心的距离就是扩展层数 (n-1)/k 了,再乘 2 就是两个 k 点间的距离了,但是可能会出现样例2那样的情况,所以还要加上特判:

⑴如果刚好多了一个普通点,那么距离就要 +1

⑵如果多了超过一个普通点,那么距离就要 +2(普通点就是 除 k 个点外的其他点)

然后就是输出边了

设 1 为中心点先输出第一层,也就是 1 到另外 k 个点

然后输出其他层,从 k+1 开始,每个点 i 到 i-k,i位置到他前一层的 i 位置

下面是 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k;
	cin >> n >> k;
	int ans = (n-1)/k*2;
	if((n-1)%k==1)
		ans ++;
	else if((n-1)%k)
		ans +=2;
	cout << ans <<endl;
	for(int i=2;i<=k;i++)	//因为下面 k+1 开始, i-k 就是 1
    				//所以这里从2开始而不是1
		cout << "1 " << i <<endl;
	for(int i=k+1;i<=n;i++)
		cout << i << " " << i-k <<endl;
}
```


---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF827B *1800](https://www.luogu.com.cn/problem/CF827B)

# 解题思路

假设树以 $1$ 为根，考虑先将 $k$ 个深度为 $1$ 的节点，然后我们就可以将剩余的节点挂在目前的叶子节点上，但是如果一个叶子节点挂了 $2$ 个叶子节点的话，那么这样叶子节点数目你**一定**不能使叶子节点减少，因此一个叶子节点**最多**只能往下挂一个节点，因此你直接用优先队列维护即可。

时间复杂度 $O(n \log n)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) (1ll*(x)/__gcd(x,y)*(y))
#define Sum(x,y) (1ll*((x)+(y))*((y)-(x)+1)/2)
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<pii,vector<pii>,greater<pii>>
#define bug cout<<"---------------------------------------\n";
//ll pw(ll x,ll y,ll mod){if(y==0)return 1;if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
ll n,m;
minqueue q;
vector<pii>ans;
ll a[200010];
ll k;
void solve()
{
    _clear();
	cin>>n>>m;
	if(m==2)
	{
		cout<<n-1<<endl;
		forl(i,1,n-1)
			cout<<i<<' '<<i+1<<endl;
		return ;
	}
	forl(i,2,m+1)
		q.push({1,i}),ans.pb({1,i}),a[++k]=1;
	forl(i,m+2,n)
	{
		pii now=q.top();
		q.pop();
		ans.pb({now.y,i});
		a[++k]=now.x+1;
		q.push({now.x+1,i});
	}
	sort(a+1,a+1+k);
	cout<<a[k]+a[k-1]<<endl;
	for(auto i:ans)
		cout<<i.x<<' '<<i.y<<endl;
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
  //  cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：Crosser (赞：0)

题意转化：对一个 $k$ 个叶子节点的树，最小化深度最大的两叶子的深度和。

结论是先构建一个 $k$ 叉菊花图，接下来往每个分支分别挂点。显然应该尽量均匀分配。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/w80j395z.png)

那么如何证明此为最优解？如果不是菊花图挂链，那么深度之和显然大于 $n-1$，那么在均匀分布的情况下，深度最大的两叶子一定不会深度变小。所以尽量最小化所有结点的深度和，那么显然应该使用菊花图挂链才能避免根到叶子的路径存在公共点。

模拟即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k;
signed main() {
    cin >> n >> k;
    vector<pair<int, int>> v;
    vector<int> res(k);
    for(int i = 2; i <= k + 1; i++) v.emplace_back(1, i), res[i - 2]++;
    for(int i = k + 2; i <= n; i++) res[i % k]++, v.emplace_back(i - k, i);
    sort(res.begin(), res.end(), greater<int>());
    cout << res[0] + res[1] << endl;
    for(auto x : v) cout << x.first << ' ' << x.second << endl;
    system("pause");
    return 0;
}
```

---

