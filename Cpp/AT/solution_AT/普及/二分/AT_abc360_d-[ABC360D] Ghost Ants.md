# [ABC360D] Ghost Ants

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc360/tasks/abc360_d

数直線上に $ 1 $ から $ N $ の番号がつけられた $ N $ 匹の蟻がいます。 蟻 $ i $ $ (1\ \leq\ i\ \leq\ N) $ ははじめ座標 $ X_i $ にいて、正負どちらかの方向を向いています。はじめに全ての蟻は相異なる座標にいます。各蟻が向いている方向は長さ $ N $ の $ 01 $ 文字列 $ S $ で表され、$ S_i $ が `0` のとき蟻 $ i $ は負の方向を向いており、 `1` のとき蟻 $ i $ は正の方向を向いています。

現在を時刻 $ 0 $ とし、時刻 $ (T+0.1) $ までの $ (T+0.1) $ 単位時間にわたって、$ N $ 匹の蟻がそれぞれの向いている方向に向かって単位時間あたり $ 1 $ の速さで移動します。 複数の蟻が同じ座標に到達すると、それらの蟻はすれ違い、方向や速度を変えずに通り過ぎます。 $ (T+0.1) $ 単位時間が経過したとき、すべての蟻は停止します。

$ 1\ \leq\ i\ <\ j\ \leq\ N $ を満たし、今から時刻 $ (T+0.1) $ までに蟻 $ i $ と蟻 $ j $ がすれ違う整数の組 $ (i,j) $ の個数を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ T\ \leq\ 10^{9} $
- $ S $ は `0` と `1` からなる長さ $ N $ の文字列
- $ -10^{9}\ \leq\ X_i\ \leq\ 10^{9} $ $ (1\ \leq\ i\ \leq\ N) $
- $ X_i\ \neq\ X_j $ $ (1\ \leq\ i\ <\ j\ \leq\ N) $
- $ N,T,X_i $ $ (1\ \leq\ i\ \leq\ N) $ は整数

### Sample Explanation 1

以下の $ 5 $ つの蟻の組み合わせがすれ違います。 - 蟻 $ 3 $ と蟻 $ 4 $ が時刻 $ 0.5 $ にすれ違う。 - 蟻 $ 5 $ と蟻 $ 6 $ が時刻 $ 1 $ にすれ違う。 - 蟻 $ 1 $ と蟻 $ 2 $ が時刻 $ 2 $ にすれ違う。 - 蟻 $ 3 $ と蟻 $ 6 $ が時刻 $ 2 $ にすれ違う。 - 蟻 $ 1 $ と蟻 $ 4 $ が時刻 $ 3 $ にすれ違う。 これ以外の蟻の組み合わせはすれ違うことはないため、$ 5 $ を出力します。

## 样例 #1

### 输入

```
6 3
101010
-5 -1 0 1 2 4```

### 输出

```
5```

## 样例 #2

### 输入

```
13 656320850
0100110011101
-900549713 -713494784 -713078652 -687818593 -517374932 -498415009 -472742091 -390030458 -379340552 -237481538 -44636942 352721061 695864366```

### 输出

```
14```

# 题解

## 作者：Size_OIer (赞：7)

由题目可知，如果两只蚂蚁的方向相同的话，那它们永远不会相遇。  
那么我们就将蚂蚁分成两组：向右的和向左的。  
显然，当且仅当一只向右的蚂蚁在一只向左的蚂蚁左侧，且两者间距离小于等于 $ 2 \times t $ 时，两者能够相遇。  
二分查找并统计即可。  
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200000+5;
int n,t;
string s;
int a[maxn],b[maxn];
int n1,n2;
int p[maxn];
int ans;
signed main(){
    cin>>n>>t;
    cin>>s;
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=0;i<=n-1;i++) if(s[i]=='1') a[++n1]=p[i+1]; else b[++n2]=p[i+1];
    sort(a+1,a+1+n1);
    sort(b+1,b+1+n2);
    for(int i=1;i<=n1;i++) {
        int x1,x2;
        x1=lower_bound(b+1,b+1+n2,a[i])-b;
        x2=upper_bound(b+1,b+1+n2,a[i]+2*t)-b;
        ans+=x2-x1;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Special_Tony (赞：5)

# 思路
首先，因为所有蚂蚁速度一样，所以同向蚂蚁不会相遇，只有反向的才会相遇。因此，我们只要把蚂蚁按方向分成两队，两只初始方向分别为左、右，初始位置为 $x,y$，则它们相交的条件就是 $x-y\in[0,2t]$。然后利用这一点，对两队蚂蚁分别排序后二分或双指针就行了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, t, x, y, l[200005], r[200005], m1, m2;
ll sum;
string a;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> t >> a;
	for (int i = 0; i < n; ++ i) {
		cin >> x;
		if (a[i] == '0')
			l[m1] = x, ++ m1;
		else
			r[m2] = x, ++ m2;
	}
	x = y = 0, sort (l, l + m1), sort (r, r + m2);
	for (int i = 0; i < m2; ++ i) {
		while (x < m1 && l[x] < r[i])
			++ x;
		while (y < m1 && l[y] - t <= r[i] + t)
			++ y;
		sum += y - x;
	}
	cout << sum;
	return 0;
}
```

---

## 作者：xiaofu15191 (赞：1)

看到题面上的“蚂蚁的速度、方向均不变”，想到 $O(n)$ 枚举每一只蚂蚁，算出对于每一只蚂蚁对答案产生的贡献。

显然地，对于一只面向正方向，坐标为 $x$ 的蚂蚁，能够对其答案产生贡献的只有面向负方向，且坐标在 $(x,x+2t)$ 之间的蚂蚁们。

考虑将面向正方向与负方向的蚂蚁坐标分开储存，使用双指针维护。非常好做，注意细节。

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
long long n,t,x[200010],l[200010],head=1,tail=0,sum;
string facing;
struct ant
{
	long long facing,x;
}ants[200010];
bool cmp(ant a,ant b)
{
	return a.x<b.x;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>t;
	cin>>facing;
	for(long long i=1;i<=n;i++)
	{
		cin>>x[i];
		ants[i].facing=facing[i-1]-'0';
		ants[i].x=x[i];
	}
	sort(ants+1,ants+n+1,cmp);
	for(long long i=1;i<=n;i++)
		if(ants[i].facing==0)
			l[++sum]=ants[i].x;
	long long ans=0;
	for(long long i=1;i<=n;i++)
	{
		if(ants[i].facing==1)
		{
			while(l[head]<ants[i].x&&head<=sum) head++;
			while(tail<sum&&l[tail+1]<=ants[i].x+2*t) tail++;
			ans+=max(0ll,tail-head+1);
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：T_TLucas_Yin (赞：1)

这题让我想到了 P1007 独木桥。但比那题简单很多。

首先应该很容易想到，两只蚂蚁会相遇的条件是左边的蚂蚁向右走，右边的蚂蚁向左走，两只蚂蚁的间距 $\le 2T$（因为在规定的时间里，两只蚂蚁会各走 $T$ 格）。限制时间是 $(T+0.1)$，告诉我们在最后一刻相遇的蚂蚁也要计数。

我们可以开一个队列，从左往右遍历所有的蚂蚁，把每一只向右走的蚂蚁都入队，每遍历到一只向左走的蚂蚁就把队里与它间距超过 $2T$ 的右向蚂蚁出队。最后队里剩下的蚂蚁数量就是所有会与它相遇的蚂蚁数量。由于越往右，蚂蚁与前面蚂蚁的间距就越大，所以无需把已经出队的蚂蚁加回来。累加每一只左向蚂蚁得到的答案即可。

**注意事项：给定的蚂蚁序列并不是有序的，要排序！！！方向数组也要跟着排序！！！**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
char c;
queue<int> q;
struct node{
	int flag,a;
}f[1000005];
bool cmp(node a,node b){
	return a.a<b.a;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='0') f[i].flag=0;
		else f[i].flag=1;
	}
	for(int i=1;i<=n;i++) cin>>f[i].a;
	sort(f+1,f+1+n,cmp);
	int sum=0;
	for(int i=1;i<=n;i++){
		if(f[i].flag) q.push(f[i].a);
		else{
			while(!q.empty()&&f[i].a-q.front()>m*2) q.pop();
			sum+=q.size();
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：Heldivis (赞：1)

# ABC360D

首先可以发现，对于同向的蚂蚁，因为速度相同，一定不会相遇。

所以考虑先维护出某一方向的蚂蚁移动区间 $[l_i,r_i]$，用另一方向的蚂蚁移动区间 $[x_i,y_i]$ 去计算贡献，区间长度为 $T$。

两个反向的蚂蚁相遇，当且仅两个区间交集非空。

考虑如何维护？

发现一个区间内合法区间数量，等于这个区间右端点以左的其他区间左端点数量，减去这个区间左端点以左的其他区间右端点数量，二分查找可以快速计算。注意因为题目说的是 $T+0.1$，所以端点重合也算合法。

代码：

```cpp
int n = read(), t = read();
vector<int> xl, xr;
vector<int> tl, tr;
string str;
cin >> str;
for (int i = 0; i < n; i++) {
  int now = read();
  if (str[i] == '1') {
    tl.push_back(now);
    tr.push_back(now + t);
  } else {
    xr.push_back(now);
    xl.push_back(now - t);
  }
}
sort(tl.begin(), tl.end());
sort(tr.begin(), tr.end());
int res = 0;
for (int i = 0; i < xl.size(); i++) {
  int l = xl[i], r = xr[i];
  res += (upper_bound(tl.begin(), tl.end(), r) - tl.begin()) -
         (upper_bound(tr.begin(), tr.end(), l - 1) - tr.begin());
}
cout << res;
```

---

## 作者：Hughpig (赞：0)

显然方向相同的蚂蚁由于速度相同，不会相撞。所以对于每只蚂蚁，只要考虑和它方向不同的蚂蚁即可。

先把所有蚂蚁按位置排序。然后对于某只向左的蚂蚁，它在 $T$ 单位时间后可以向左走 $T$ 个单位。对于一只向右的蚂蚁同理可以走 $T$ 个单位。

所以对某只位置为 $x$ 的向左的蚂蚁来说，位置在 $[x-2T,x]$ 的向右蚂蚁都会和它相撞。我们记录所有位置在它左边的向右蚂蚁坐标，二分计算贡献。

对于向右蚂蚁同理。

时间复杂度 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int N=2e5+9;

ll n,t,x[N],ans;
string s;
vector<int> pos1,pos2;

struct ant{
	int x;
	char c;
	friend bool operator <(ant x,ant y){
		return x.x<y.x;
	}
}qaq[N];

int main()
{
    cin>>n>>t>>s;
    s=' '+s;
    for(int i=1;i<=n;++i)cin>>x[i],qaq[i]={x[i],s[i]};
    sort(qaq+1,qaq+n+1);
    s.clear();s=" ";
    for(int i=1;i<=n;++i)s+=qaq[i].c,x[i]=qaq[i].x;
    for(int i=1;i<=n;++i){
		if(s[i]=='0'){
    		ans+=upper_bound(pos2.begin(),pos2.end(),x[i])-lower_bound(pos2.begin(),pos2.end(),x[i]-2*t);
    		pos1.emplace_back(x[i]);
		}
		else{
			ans+=upper_bound(pos1.begin(),pos1.end(),x[i]+2*t)-lower_bound(pos1.begin(),pos1.end(),x[i]);
			pos2.emplace_back(x[i]);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
第一步，将 $X$ 数组分成 $a$ 和 $b$ 两个数组。如果 $S_i$ 是 `1`，那么 $X_i$ 分到 $a$ 数组，否则分到 $b$ 数组。

第二步，因为后续要进行二分查找，所以要将 $a$ 和 $b$ 两个数组进行升序排序。

第三步，枚举从 $1 \sim n$。从 $b$ 数组找出第一个大于 $a_i+2 \times t$ 的下标，设这个数为 $l$。再从 $b$ 数组找出第一个大于等于 $a_i$ 的下标，设这个数为 $r$。答案加上 $l-r$。

最后输出答案。第三步需要用二分查找的方式，这样总的时间复杂度就是 $O(n \log n)$。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#define int long long
int read(){
 int x=0,t=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
 return x*t;
}
#define rd read()
#define N 200005
int n,t,x[N],a[N],b[N],ia,ib,ans;
signed main(){
	n=rd,t=rd;
	std::string s;std::cin>>s;
	for(int i=1;i<=n;i++)x[i]=rd;
	for(int i=1;i<=n;i++)
		if(s[i-1]=='1')a[++ia]=x[i];
		else b[++ib]=x[i];
	std::sort(a+1,a+1+ia);
	std::sort(b+1,b+1+ib);
	for(int i=1;i<=ia;i++)
		ans+=std::upper_bound(b+1,b+1+ib,a[i]+2*t)-std::lower_bound(b+1,b+1+ib,a[i]);
	std::cout<<ans;
}
```

---

## 作者：Liyunze123 (赞：0)

对于所有往左走的蚂蚁 $i$ 和往右走的蚂蚁 $j$，答案增加当且仅当 $a_j \ge a_i-2 \times t$ 且 $a_j \le a_i$。我们可以对所有往右走的 $a_j$ 建立 $b$ 数组并排序，对于所有往左走的 $a_i$，二分找出满足条件的 $a_j$ 的范围，即找出第一个大于等于 $a_i-2 \times t$ 的 $b_L$，和最后一个小于等于 $a_i$ 的 $b_R$，答案就加上 $R-L+1$。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],l[200010],r[200010],k[2];
long long ans,t;
char s[200010];
int main(){
	scanf("%d%lld%s",&n,&t,s+1);
	for(int w=1;w<=n;w++){
		scanf("%d",&a[w]),s[w]-='0';
		if(s[w])l[++k[1]]=a[w];
		else r[++k[0]]=a[w];
	}
	sort(l+1,l+k[1]+1);
	for(int w=1;w<=k[0];w++){
		int L=lower_bound(l+1,l+k[1]+1,r[w]-2*t)-l,R=upper_bound(l+1,l+k[1]+1,r[w])-l-1;
		ans+=R-L+1;
	}
	printf("%lld",ans);
	return 0;
}
```
注意 $a_i-2\times t$ 可能会爆 int。

---

