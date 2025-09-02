# [ARC069E] Frequency

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc069/tasks/arc069_c

すぬけくんは数列を作るのが好きです。

$ 1 $ から $ N $ までの番号がついた石の山があります。 $ i $ 番の石の山は $ a_i $ 個の石からなります。

すぬけくんは以下の手順により長さ $ Σa_i $ の数列 $ s $ を構成することにしました。

1. 石の数が最大である山のうち、最も番号が小さい山の番号を $ x $ として、$ s $ の末尾に $ x $ を追加する
2. 石が $ 1 $ 個以上存在する山を $ 1 $ つ選んで、選んだ山から石を $ 1 $ つ取り除く
3. 石が $ 1 $ 個以上存在する山が存在するなら $ 1. $ へ、そうでなければ数列の構成を終了する

$ s $ が辞書順で最小の数列となるようにしたとき、$ s $ に $ 1,2,3,...,N $ という数がそれぞれいくつ含まれるか求めなさい。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^{5} $
- $ 1\ ≦\ a_i\ ≦\ 10^{9} $

### Sample Explanation 1

以下の手順で辞書順最小であるような数列が構成できます。 - 石の数が最大であるような山は $ 2 $ 番なので $ 2 $ を $ s $ に追加する。その後、番号 $ 2 $ の山から石を $ 1 $ つ取り除く。 - 石の数が最大であるような山は $ 1 $ 番と $ 2 $ 番なので、最も番号が小さい $ 1 $ を $ s $ に追加する。その後、番号 $ 2 $ の山から石を $ 1 $ つ取り除く。 - 石の数が最大であるような山は $ 1 $ 番なので $ 1 $ を $ s $ に追加する。その後、番号 $ 1 $ の山から石を $ 1 $ つ取り除く。 このときできる数列は $ (2,1,1) $ となります。$ 1 $ は $ 2 $ つ含まれ、$ 2 $ は $ 1 $ つ含まれます。

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
2
1```

## 样例 #2

### 输入

```
10
1 2 1 3 2 4 2 5 8 1```

### 输出

```
10
7
0
4
0
3
0
2
3
0```

# 题解

## 作者：water_tomato (赞：6)

本文同步发表于个人博客：[Link](https://www.watertomato.com/at2335-arc069c-frequency-%e9%a2%98%e8%a7%a3/)。

[题目链接](https://www.luogu.com.cn/problem/AT2335)。

题意不多赘述。

## 解析

由于每次会将石子最多的那堆的序号加入 $S$ 中，我们考虑将原始的石子堆从大到小排序。首先我们发现如果有一堆比其他都要高，我们可以将他取到与第二高的一样高，这样的话结果只可能会更优（因为相同时优先取小的）。

依照这个思路，我们考虑按照高度一层一层取下来，这样答案会越来越优（若存在多个高度相同的，你只需要认为在取的过程中先取序号大的即可）。由于高的不取完矮的一定无法加入 $S$，因此这样一定是最优结果。

也就是说，我们只需要记录从开始（从最高的开始）到当前所有堆中序号最小的那个，然后每次变层时，将当前最小的答案加上高度差乘以大于等于该层的所有堆数量的结果即可（相当于削掉这层以上的部分），详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,maxx,ans[N];
struct node{
	int p,a;
}a[N];
inline bool cmp(node i,node j){
	if(i.a!=j.a) return i.a>j.a;
	return i.p>j.p;//同层的直接让序号小的在后面，后续方便一些
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i].a);
		a[i].p=i;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1,now=1e9+7;i<=n;i++){
		if(i!=n&&a[i].a==a[i+1].a) continue;//同层的跳过
		now=min(now,a[i].p);//更新当前最小值
		ans[now]+=i*(a[i].a-a[i+1].a);//加入削掉这层以上部分所需的次数
	}
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Tjqq (赞：0)

注意到 S 序列单调递减，否则一定不优。

于是从大到小选择模拟
### code:

```cpp
//created by fqr & cyx in 2025
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
#define ll long long
#define pb emplace_back
int ff,Ch;
template <typename T> inline void rd(T &x) {
    x=0,ff=1,Ch=getchar();
    while((Ch<'0'||Ch>'9') && Ch!='-') Ch=getchar();
    if(Ch=='-')Ch=getchar(),ff=-1;
    while(Ch>='0' && Ch<='9') {
        x=(x<<1)+(x<<3)+Ch-'0';
        Ch=getchar();
    }
    x*=ff;
}
template <typename T,typename ...Args> inline void rd(T &x,Args &...args) {
    rd(x), rd(args...);
}
using namespace std;
const int N=1e5+5;
int n; 
int a[N],p[N];
ll ans[N];
signed main() {
#ifdef LOCAL
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
#endif
	rd(n);
	for(int i=1; i<=n; i++)
		rd(a[i]),p[i]=i;
	sort(p+1,p+1+n,[&](const int &x,const int &y) {
		return a[x]>a[y];
	});
	ll sum=a[p[1]];
	for(int i=2,lst=1; i<=n+1; i++) {
		if(p[i]<p[lst]) {
			ans[p[lst]]=sum-1ll*(i-1)*a[p[i]];
			sum=(i-1)*a[p[i]];
			lst=i;
		}
		sum+=a[p[i]];
	}
	for(int i=1; i<=n; i++)
		printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：NATO (赞：0)

纸张题。

### 思路浅析：

显然我们可以通过拿后面的石子保证字典序单调不增，这肯定是比有增更优秀的。

如果我们想要减小最大值的最小位置，那么我们必然需要从当前所有最大值的位置上拿走至少 $maxn-maxn_{next}$ 块石头，为了字典序最小，这样必然是最优秀的，其中 $maxn$ 为当前最大值，$maxn_{next}$ 为当前次大值，那么显然，在拿这一些石子时，最大值的最小位置始终是原来最大值的最小位置是字典序最小的，即给最大值的最小位置的出现次数加上 $maxn_{sum}(maxn-maxn_{next})$ 次，其中 $maxn_{sum}$ 是当前最大值的个数，再更新最大值的最小位置即可，当最小位置为 $1$ 时将剩下石子数加到 $1$ 的出现次数即可。

线段树简单维护一下最大值和最大值的最小位置即可。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
ll n,a[100005];
ll sum[100005];
struct tree
{
	ll maxn,uid;
	#define ls(id) id*2
	#define rs(id) id*2+1
}tr[400005];
void pushup(ll id)
{
	if(tr[ls(id)].maxn>=tr[rs(id)].maxn)tr[id]=tr[ls(id)];
	else tr[id]=tr[rs(id)];
}
void build(ll id,ll l,ll r)
{
	if(l==r)
	{
		tr[id].maxn=a[l];tr[id].uid=l;return;
	}
	ll mid=l+r>>1;
	build(ls(id),l,mid);
	build(rs(id),1+mid,r);
	pushup(id);
}
void update(ll id,ll l,ll r,ll ml)
{
	if(l==r)
	{
		tr[id].maxn=0;return;
	}
	ll mid=l+r>>1;
	if(ml<=mid)update(ls(id),l,mid,ml);
	else update(rs(id),1+mid,r,ml);
	pushup(id);
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;++i)cin>>a[i];
	build(1,1,n);
	ll ss=1,nw=tr[1].uid,val=tr[1].maxn;
	update(1,1,n,nw);
	while(nw!=1)
	{
		ll fw=tr[1].uid;
		sum[nw]+=(val-tr[1].maxn)*ss;
		++ss;val=tr[1].maxn;
		update(1,1,n,fw);
		if(fw<nw)nw=fw;
	}
	for(ll i=1;i<=n;++i)
	if(a[i]<=a[1])sum[1]+=a[i];
	else sum[1]+=a[1];
	for(ll i=1;i<=n;++i)
	cout<<sum[i]<<'\n';
}
```

---

## 作者：_Flame_ (赞：0)

## 思路

贪心的想每次要取哪堆石子。

由于题目说如果最高的石子有多堆，取最小的序号加入 $S$ 中，而不是最高的石子的序号无论再小，在最高的石子被取到高度与其相同前都取不到，所以策略就很明显了。

先取最高的石子，若最高的石子有多堆，将编号最小的最后取，这样对于每一种高度，能取到的都是这一高度中编号的最小值，毫无疑问，这肯定是最优的。

具体实现方面，按照高度为第一关键字，序号为第二关键字由大到小排序，高度相同的就取序号最小的，对于每一种高度计算将其全部变为下一种高度的贡献即可。

## Code
[Code](https://atcoder.jp/contests/arc069/submissions/43509912)


---

## 作者：TankYu (赞：0)

根据贪心，我们一定会拿**当前最大的，更靠后的**石子。优先拿当前最大的正确性显然。在有等大的情况下，如果拿更靠前的，那么等大靠后的这一堆一定会在 $S$ 中**多出现一次**，字典序会变劣。

那么我们一次拿会造成多少贡献呢？注意到以上的贪心策略，我们以大小为第一关键字，并以下标为第二关键字排序。从前向后扫，同时记录下标最小值，对于每一个 $A_i \ne A_{i + 1}$，我们会将 $i + 1$ 前面的拿成 $i + 1$ 的大小。这部分将当前对最小值的答案造成 $i \times (A_i - A_{i + 1})$ 的贡献。

如果 $A_i = A_{i + 1}$，跳过。注意开 `long long`。

```cpp
#include <map>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define D double
#define LD long double
#define LL long long
#define ULL unsigned long long
#define S string
#define fi first
#define se second
#define mp make_pair
using namespace std;

struct sum
{
	int num;
	int id;
} a[100010];

bool cmp(sum x, sum y)
{
	if (x.num != y.num)
	{
		return x.num > y.num;
	}
	return x.id > y.id;
}
LL ans[100010];

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].num;
		a[i].id = i;
	}
	sort(a + 1, a + n + 1, cmp);
	int minn = 1000000000;
	for (int i = 1; i <= n; i++)
	{
		if (a[i].num == a[i + 1].num)
		{
			continue;
		}
		minn = min(minn, a[i].id);
		ans[minn] += 1ll * (a[i].num - a[i + 1].num) * i;
	}
	for (int i = 1; i <= n; i++)
	{
		cout << ans[i] << '\n';
	}
	return 0;
}

```

---

