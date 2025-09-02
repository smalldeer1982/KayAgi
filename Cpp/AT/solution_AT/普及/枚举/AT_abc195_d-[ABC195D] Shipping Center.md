# [ABC195D] Shipping Center

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc195/tasks/abc195_d

$ 1 $ から $ N $ の番号がついた $ N $ 個の荷物と、$ 1 $ から $ M $ の番号がついた $ M $ 個の箱があります。

荷物 $ i $ の大きさは $ W_i $ で、価値は $ V_i $ です。

箱 $ i $ には大きさが $ X_i $ 以下の荷物を入れることができます。$ 1 $ つの箱に $ 2 $ つ以上の荷物を入れることはできません。

$ Q $ 個のクエリが与えられます。各クエリでは $ 2 $ つの整数 $ L,R $ が与えられるので、次の問題を解いてください。

- 問題：$ M $ 個の箱のうち、箱 $ L,L+1,\ldots,R $ の $ R-L+1 $ 個の箱が使えなくなってしまいました。 残りの箱の中に同時に入れることができる荷物の価値の合計の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ M\ \leq\ 50 $
- $ 1\ \leq\ Q\ \leq\ 50 $
- $ 1\ \leq\ W_i\ \leq\ 10^6 $
- $ 1\ \leq\ V_i\ \leq\ 10^6 $
- $ 1\ \leq\ X_i\ \leq\ 10^6 $
- $ 1\ \leq\ L\ \leq\ R\ \leq\ M $
- 入力は全て整数

### Sample Explanation 1

$ 1 $ 番目のクエリでは箱 $ 4 $ が使えません。 箱 $ 1 $ に荷物 $ 1 $ を、箱 $ 2 $ に荷物 $ 3 $ を、箱 $ 3 $ に荷物 $ 2 $ を入れることで、 全ての荷物を箱の中に入れることができ、箱の中の荷物の価値の合計を $ 20 $ にすることができます。 $ 2 $ 番目のクエリでは全ての箱が使えません。したがって、答えは $ 0 $ です。 $ 3 $ 番目のクエリでは、箱 $ 4 $ だけが使えます。箱 $ 4 $ に荷物 $ 1 $ を入れることで、箱の中の荷物の価値の合計は $ 9 $ となり、これが最大です。

## 样例 #1

### 输入

```
3 4 3
1 9
5 3
7 8
1 8 6 9
4 4
1 4
1 3```

### 输出

```
20
0
9```

# 题解

## 作者：PDAST (赞：2)

## 题目分析
题目的意思很明确。

有 $N$（$1 \le N \le 50$）件货物和 $M$（$1 \le M \le 50$）个箱子。

每个箱子的容积是 $Xi$（$1 \le Xi \le 10^6$）。

每件货物体积是 $Wi$（$1 \le Wi \le 10^6$）。

价值是 $Vi$（$1 \le Vi \le 10^6$）。

每个盒子只能装体积不大于它的容积的一个货物，装后可以获得该货物的价值。

现在有 $Q$（$1 \le Q \le 50$）次询问。

每次给出 $L$ 和 $R$，表示 $L$ 到 $R$（$1 ≤ L ≤ R ≤  M$）的箱子不可用，求每次询问可获得的最大价值。

保证所有数据都是整数。

因为 $N$ 和 $M$ 不大于 $50$，所以可以用贪心三重循环暴力解。
## 解题准备
用一个结构体存盒子的容积及序号（就是输入的顺序）。

两个数组存货物体积和价值。

然后给盒子排序，按盒子容积升序排，后面有用。
## 贪心算法
由于 $N$ 和 $M$ 很小，所以找最优方案的可以套在接收询问的循环里。

每次询问得到 $L$ 和 $R$，循环枚举箱子，如果箱子序号在 $L$ 到 $R$ 之间，则跳过该次循环。

接着再套一层循环，枚举货物。

当货物的体积 **小于等于**（注意，是小于等于）箱子的容积且没有被标记过时。

将货物价值与原来存的货物最大价值比较，求得该箱子可获得的最大价值，并标记所选货物。

最后将可选箱子的最大价值相加，即为本次询问的最大价值，~~是不是挺简单的~~。

最后附上本蒟蒻的AC代码
[AC 记录](https://www.luogu.com.cn/record/143333928)
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int wight,num;
}x[1001];
int w[1001],v[1001],vis[1001];
long long sum[10001];
bool cmp(Node a,Node b)
{
	return a.wight<b.wight;
}
int main()
{
	int n,m,q,l,r,xbox;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i]>>v[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>x[i].wight;
		x[i].num=i;
	}
	sort(x+1,x+m+1,cmp);
	for(int i=1;i<=q;i++)
	{
		int sum=0;
		memset(vis,0,sizeof(vis));
		cin>>l>>r;
		for(int j=1;j<=m;j++)
		{
			if(x[j].num>=l&&x[j].num<=r)continue;
			int maxn=0,pos=0;
			for(int k=1;k<=n;k++)
			{
				if(x[j].wight>=w[k]&&v[k]>maxn&&vis[k]==0)
				{
					maxn=v[k];
					pos=k;
				 } 
			}
			sum+=maxn;
			vis[pos]=1;
		}
		cout<<sum<<endl;
	}
	return 0;
}
```
PS：希望这次能通过please︿(￣︶￣)︿

---

## 作者：Fkxxx (赞：2)

### 思路

这是一道比较有意思的题，显而易见的，本题数据范围仅为 $1 \leq N , M , Q \leq 50$，所以我们可以用很多种方法完成它。您可以在这篇题解中看到本题的贪心解法。

我们先来分析每一个询问操作。

询问操作是让我们在不使用 $[l,r]$ 内的箱子的情况下求出最大价值。

对于一个箱子，它的最优解就是把体积小于等于它，价值最大的物品塞进去。

对于多个箱子，可能会有多个箱子公用一个最优解，此时就要有所取舍了。

![图1](https://picdl.sunbangyan.cn/2023/11/02/a0d8b7809048b458edf351856ac199ca.png)

上图中，①箱子和②箱子公用一个最优解——②物品。

①箱子可选 $4$ 个物品，而②箱子可选 $5$ 个物品，感性地想，我们应该优先满足选择更少（体积更小）的①箱子。

根据以上思路，我们只需对于每一个问题，从小到大遍历所有符合问题要求的箱子，对于每个箱子，循环找到**没有使用过**的箱子中的最优解计入总价值并标记已使用。

### AC 记录

[Submission #47152977](https://atcoder.jp/contests/abc195/submissions/47152977)

---

## 作者：Luo_gu_ykc (赞：2)

# ABC195D

## 题目大意

你有 $n$ 个行李，$m$ 个盒子。

第 $i$ 个行李所需装进的容量为 $w_i$，价值为 $v_i$。

第 $i$ 个盒子容量为 $x_i$（注意每个盒子最多只能装一个）。

给定 $q$ 个询问，每次询问告诉你从第 $l_i$ 到 $r_i$ 的盒子不能使用，请求出可以获得的最高价值。

## 思路

数据范围可以明显看出，此题多解法，本题解用的是贪心。

如果想要使得价值最大，就可以发现每个盒子都要**最大化**自己的价值。

通俗来说，就是在可以装进盒子的情况下，尽量选择价值更高的。

但对于两个不同容量的盒子而言，他们可能会都选择同一个行李。

那面对这种情况，应该怎么办？

可以发现，容量小一点的箱子可装的行李，容量大一点的箱子也都可以装。

那么可以换一种讲法，就是容量大的箱子可选择的行李，一定比容量小一点箱子可选择的行李要多。

这样，我们就一定会让容量小一点箱子选择这个行李。

所以，容量越小的箱子，越要优先选择。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, m, q;

struct node {
	int w, v;
}a[N];

struct Node {
	int x, cnt;
	bool operator < (const Node & i) {
		return x < i.x; // 按箱子容量从小到大排序（同样你也可以使用 cmp 自定义函数）
	}
}b[N];

int main(){
	cin >> n >> m >> q;
	for(int i = 1; i <= n; i++){
		cin >> a[i].w >> a[i].v;
	}
	for(int i = 1; i <= m; i++){
		cin >> b[i].x;
		b[i].cnt = i;
	}
	sort(b + 1, b + 1 + m);
	while(q--){
		int sum = 0;
		bool v[N] = {0};
		int l, r;
		cin >> l >> r;
		for(int i = 1; i <= m; i++){ // 枚举箱子
			int ans = 0, pos = 0;
			if(l <= b[i].cnt && b[i].cnt <= r){ // l ~ r 中的箱子不可选
				continue;
			}
			for(int j = 1; j <= n; ++j){
				if(a[j].w <= b[i].x && !v[j]){ // 如果当前行李可以装进盒子，且不被选过
					if(a[j].v > ans){ // 价值最大化
						ans = a[j].v;
						pos = j;
					}
				}
			}
			v[pos] = 1;// 标记所选择的行李
			sum += ans;
		}
		cout << sum << "\n";
	} 
	return 0;
}

```

---

## 作者：guoxinda (赞：1)

## 思路
考虑贪心。\
可以发现只要小的箱子能装某个行李那大的箱子一定能装，最好的情况是选小的箱子。\
于是我们可以先将箱子从小到大排序，再将行李价值不相同的按价值从大到小排序，行李价值相同的再按重量从小到大排序。（最优策略）\
然后暴力选择每个能用箱子的最大价值就好了。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,q,x[110],l,r,ans,s,cnt[110];
bool f[110];
struct stu{
	int w,v;
}a[110];
bool cmp(stu&x,stu&y){
	if(x.v!=y.v)return x.v>y.v;
	return x.w>y.w;
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i].w>>a[i].v;
	}
	for(int i=1;i<=m;i++){
		cin>>x[i];
	}
	sort(a+1,a+n+1,cmp);//先按价值排序，再按重量排序
	for(int i=1;i<=q;i++){
		cin>>l>>r;
		ans=0;
		s=0;
		memset(f,0,sizeof(f));
		memset(cnt,0,sizeof(cnt));//初始化
		for(int j=1;j<l;j++){//1~l-1
			s++;
			cnt[s]=x[j];
		}
		for(int j=r+1;j<=m;j++){//r+1~m
			s++;
			cnt[s]=x[j];
		}
		sort(cnt+1,cnt+s+1);//从小到大排序 
		for(int j=1;j<=s;j++){
			for(int k=1;k<=n;k++){
				if(!f[k]&&cnt[j]>=a[k].w){
					f[k]=1;
					ans+=a[k].v;
					break;
				}
			}
		}
		cout<<ans<<endl;
	} 
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 分析
对于每次不能使用的盒子，我们可以新建一个数组，存入可以使用的盒子，这样就相当求于在一些盒子里，放这 $N$ 个物品的最大价值（每个盒子都能用）。

我们可以用贪心完成此题。盒子的空间是一定的，而物品的体积与价值也是一定的。所以我们可以考虑从小的盒子开始放。对于每一个盒子，我们都去枚举每一件物品，若这个物品没有被放进别的盒子，则看它的价值和体积。若价值和这个盒子目前放的物品价值相同，但体积更大且仍能放进去，那么我们选择这个物品一定是最优的。若这个物品的价值更高，优先考虑这个放入物品。注意，在存放新的物品时，上一次的物品是暂时没有放入其他的盒子里的，所以要清除它的标记。最后将每个盒子的价值累加输出即可。

## CODE
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100;
int n,m,q;
struct aa{
	int v,w;
}a[N];
int V[N];
bool vis[N];//标记数组 
int k[N];
int max_ans[N],max_id[N];//max_ans是每个盒子的最大价值,max_id是每个盒子存的体积最大，价值最优的物品编号 
signed main()
{
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) cin>>a[i].w>>a[i].v;
	for(int i=1;i<=m;i++) cin>>V[i];
	for(int ka=1;ka<=q;ka++)
	{
		memset(vis,0,sizeof(vis));
		memset(max_ans,0,sizeof(max_ans));
		memset(max_id,0,sizeof(max_id));
		int l,r;cin>>l>>r;
		int idx=0;
		for(int i=1;i<l;i++) k[++idx]=V[i];
		for(int i=r+1;i<=m;i++) k[++idx]=V[i];
		sort(k+1,k+idx+1);//从小到大排序 
		for(int i=1;i<=idx;i++)
			for(int j=1;j<=n;j++)
				if(!vis[j]&&max_ans[i]<a[j].v&&a[j].w<=k[i])//价值不同 
				{
					max_ans[i]=a[j].v;
					vis[max_id[i]]=0;
					max_id[i]=j;
					vis[j]=1;
				}
				else 
				{
					if(!vis[j]&&max_ans[i]==a[j].v&&a[j].w<=k[i]&&a[j].w<a[max_id[i]].w)//体积不同 
					{
						vis[max_id[i]]=0;
						max_id[i]=j;
						vis[j]=1;
					}
				}
		int ans=0;
		for(int i=1;i<=idx;i++) ans+=max_ans[i];
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Miracle_1024 (赞：0)

## 解题过程：

很水的一个贪心题好吧，直接结构体一下。

先把 $N$ 个行李的价值的从大到小排一下序。

然后先选取价值最大的行李，往最小的可以塞的箱子里面塞，最后再选择那些价值更小，体积更大的行李。或者也可以先放价值小体积也小的，这种方法也是可行的。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
struct node{
	ll w,v;
}s[N];
bool cmp(node xx,node yy){
    return xx.v>yy.v;
}
ll n,m,q,a[N],l,r,cnt,ans;
bool flag[N];
int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)cin>>s[i].w>>s[i].v;
    for(int i=1;i<=m;i++)cin>>a[i];
    sort(s+1,s+1+n,cmp);
    while(q--){
	    vector<ll>g;
	    memset(flag,0,sizeof flag);
	    cin>>l>>r;
	    for(int i=1;i<=m;i++)if(i<l||i>r)g.push_back(a[i]);
	    sort(g.begin(),g.end());
	    ll k=g.size();
		cnt=1,ans=0;
	    while(k||cnt<=n){
	        for(int i=0;i<g.size();i++){
		        if(!flag[i]&&g[i]>=s[cnt].w){
		            ans+=s[cnt].v;
		            flag[i]=1;
		            k--;
		            break;
		        }
	        }
	        cnt++;
	    }
	    cout<<ans<<endl;
    }
}

```

---

## 作者：leixinranYY (赞：0)

## 题目翻译
有编号为 $1$ 到 $N$ 的 $N$ 个行李和编号为 $1$ 到 $M$ 的 $M$ 个箱子。

每个箱子的容积是 $X_i$。

每件货物的体积是 $W_i$，价值是 $V_i$。

每个盒子只能装体积不大于它的容积的**一个货物**，装后可以获得该货物的价值。

现有 $Q$ 个询问，每次给出 $L$ 到 $R$ 的箱子不可用，求每次询问可获得的最大价值。

## 思路
因为 $N$ 和 $M$ 不大于 $50$，所以直接贪心暴力解。

开始对每个行李的价值**从小到大**排序，并记录每个箱子的编号。接着通过询问得到 $L$ 和 $R$，循环枚举箱子，如果序号在 $L$ 到 $R$ 之间，就跳过。

再套一层循环枚举每个行李，如果已经装进了箱子，就跳过。如果这个行李满足装入箱子的条件，则记录这个行李的价值和这个箱子的编号。最后标记这个行李，将总价值加上新装进箱子的行李的价值。

最后输出总价值即可。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,t,l,r,ans,maxn,ii,w[1010],v[1010];
bool d[1010];
struct node{
    int wi,id;
}a[1010];
bool cmp(node x,node y)
{ return x.wi<y.wi; }
signed main()
{
    scanf("%lld%lld%lld",&n,&m,&t);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld",&w[i],&v[i]);
    for(int i=1;i<=m;i++)
	{
        scanf("%lld",&a[i].wi);
        a[i].id=i;
    }
    sort(a+1,a+m+1,cmp);
    while(t--)
	{
        memset(d,0,sizeof(d));
        ans=0;
        scanf("%lld%lld",&l,&r);
        for(int i=1;i<=m;i++)
		{
            maxn=0,ii=0;
            if(a[i].id>=l && a[i].id<=r)continue;
            for(int j=1;j<=n;j++)
			{
                if(d[j])continue;
                if(v[j]>maxn && w[j]<=a[i].wi)maxn=v[j],ii=j;
            }
            d[ii]=1,ans+=maxn;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/197150469)

---

## 作者：ZH_qaq (赞：0)

## AT_abc195_d [ABC195D] Shipping Center 的题解
#### [洛谷传送门](https://www.luogu.com.cn/problem/AT_abc195_d)
#### [AT 传送门](https://atcoder.jp/contests/abc195/tasks/abc195_d)
### 思路
这道题看似很像背包问题，其实不然。我们只需升序排序数组 $X$ 后，再按顺序贪心地为每个盒子选择它能拿到的价值最高的包裹即可。总时间复杂度为 $\mathcal O(NMQ)$

### 代码
```cpp
#include <bits/stdc++.h>
#define lowbit(x) x & (-x)
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
namespace fastIO {
	inline int read() {
		register int x = 0, f = 1;
		register char c = getchar();
		while (c < '0' || c > '9') {
			if(c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
		return x * f;
	}
	inline void write(int x) {
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
		return;
	}
}
using namespace fastIO;
typedef pair<int, int> pii;
pii bags[55], boxes[55];
bool taken[55];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n, m, q;
	n = read(), m = read(), q = read();
	for(int i = 0; i < n; i ++) {
		bags[i].second = read(), bags[i].first = read();
	}
	sort(bags, bags + n, greater<pii>());
	for(int i = 0; i < m; i ++){
		boxes[i].first = read();
		boxes[i].second = i;
	}	
	sort(boxes, boxes + m);
	while(q --) {
		int l, r, ans = 0;
		l = read(), r = read();
		l --, r --;
		fill(taken, taken + n, false);
		for(int i = 0; i < m; i ++) {
			auto [size, idx] = boxes[i];
			if(idx < l || idx > r) {
				int j = 0;
				for(; j < n; j ++) {
					if(!taken[j] && bags[j].second <= size) {
						break;
					}
				}
				if(j < n) {
					ans += bags[j].first;
					taken[j] = true;
				}
					
			}
		}
		write(ans), putchar('\n');
	}
	return 0;
}
```

---

## 作者：OI_StarGod (赞：0)

~~这题水的一批~~

题意不讲了~~我懒~~

看一眼数据范围：$N \le 50$

稳了，这个数据范围，除非搜索啥的，否则随便搞都不会炸。然后我们发现，大东西小背包不能装，大背包可以，而小东西小背包和大背包都能装。

于是我们就发现，我们可以优先把东西塞进小背包里，如果小背包装不下再用大背包装。因此我们可以按照大小对背包排序。然后基本每次询问就是微型模拟，就是对于每个背包，判断他编号在不在 $l$ 到 $r$，如果不在，枚举所有东西，找到能够装的下且价值最大的物品且没被装进其他背包然后塞进去就完事了。

# ac 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 55;
int n, m, q;
int w[N], v[N];
struct Bag { //背包应当用结构体存，因为要记录编号方便判断他在不再l到r
    int Size; //背包大小
    int id; //编号
}bag[N];
bool vis[N];//有没有被装进其他背包
bool cmp(Bag a, Bag b) { //按照大小从小到大
    return a.Size < b.Size;
}
signed main() {
    scanf("%lld %lld %lld", &n, &m, &q); //热知识：scanf比cin快很多
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld", &w[i], &v[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%lld", &bag[i].Size);
        bag[i].id = i; //记录编号
    }
    sort(bag + 1, bag + m + 1, cmp);//按照大小排序
    while (q--) {
        memset(vis, 0, sizeof(vis));//记得初始化
        int l, r;
        scanf("%lld %lld", &l, &r);
        int ans = 0;//记录最大价值
        for (int i = 1; i <= m; ++i) {//枚举每个背包
            if (bag[i].id >= l && bag[i].id <= r) {//如果在区间l到r
                continue;//跳出
            }
            int maxn = 0, id = 0;//记录可装的下且价值最大的物品
            for (int j = 1; j <= n; ++j) {//枚举物品
                if (vis[j]) {//如果已经被装进其他背包
                    continue;//不管了
                }
                if (v[j] > maxn && w[j] <= bag[i].Size) {//如果装的下且价值比当前最大值大
                    maxn = v[j];//记录
                    id = j;
                }
            }
            vis[id] = 1;//表示该物品已经被选，避免重叠
            ans += maxn;//将总价值加上新塞的物品的价值
        }
        printf("%lld\n", ans);//输出
    }
    return 0;
}
```

---

## 作者：Down_syndrome (赞：0)

## 思路
可以看出是贪心。首先要保证价值最大，我们可以把行李按照价值排序，尽量装排在前面的行李。如果只有一个箱子可以装下，就用这个箱子；如果有多个箱子可以装下，我们就用最小的箱子装，因为更大的箱子更有可能可以装下后面的行李，具体可以看看代码。
## 代码实现
首先 $n,m,q$ 都非常小，我们就可以按上述过程模拟。把行李按照价值排序，把箱子也按照大小排序。每次用二分（当然这么小的数据范围可以直接暴力）找到第一个没用过的能够装下这个行李的箱子，再累加价值。

## [Code](https://www.luogu.com.cn/paste/a0xejz57)

---

## 作者：WaterSun (赞：0)

# 思路

一个简单的贪心，对于每一次操作，我们假设我们能用盒子的大小的数组处理成 $a$。那么，我们可以对 $a$ 进行从小到大排序。

然后，对于我们所有的箱子，我们可以以 $w$ 为关键字，从小到大排序。

接着，我们可以进行暴力枚举，对于 $a_i$，我们要取的必定为 $\max_{w_j \leq a_i}(v_j)$。因为每一个箱子只能被取一次，所以每一次被选过后，需要标记一下。

于是，我们想到用大根堆来维护。我们将所有 $w$ 相同的 $v$ 存入一个大根堆中，然后每一次查找都找一个最大值，然后弹出即可。

注：因为 $w_i \leq 10^6$，所以需要离散化。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 150,M = 1e6 + 10;
int n,m,k,num;
int arr[N],pre[N],w[N],v[N],vis[N];

struct node{
	int w;
	int v;
	bool operator <(const node &t) const{
		return w < t.w;
	}
}box[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	m = read();
	k = read();
	for (re int i = 1;i <= n;i++){
		box[i].w = read();
		box[i].v = read();
	}
	sort(box + 1,box + 1 + n);
	for (re int i = 1;i <= m;i++) pre[i] = read();
	while (k--){
		priority_queue<int> q[N];
		int l,r;
		int idx = 0,qidx = 0,ans = 0;
		l = read();
		r = read();
		for (re int i = 1;i <= n;i++){//离散化 + 存入大根堆 
			if (box[i].w == box[i - 1].w) q[qidx].push(box[i].v);
			else q[++qidx].push(box[i].v);
		}
		for (re int i = 1;i < l;i++) arr[++idx] = pre[i];//处理 a 数组 
		for (re int i = r + 1;i <= m;i++) arr[++idx] = pre[i];
		sort(arr + 1,arr + 1 + idx);
		for (re int i = 1;i <= idx;i++){//查找答案 
			int res = 0,id = -1;
			for (re int j = 1;j <= qidx && box[j].w <= arr[i];j++){
				if (q[j].empty()) continue;
				if (q[j].top() > res){
					res = q[j].top();
					id = j;
				}
			}
			if (~id){//如果有箱子可取才能取 
				ans += res;
				q[id].pop();
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

