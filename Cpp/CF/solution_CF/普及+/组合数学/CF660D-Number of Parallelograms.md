# Number of Parallelograms

## 题目描述

给定平面上$n$个点，问用这些点能组成多少平行四边形（多个平行四边形可以共用点，保证任意三点不共线）

## 说明/提示

$1 \leq n \leq 2000$ , $0\leq x_i,y_i \leq 10^{9}$

## 样例 #1

### 输入

```
4
0 1
1 0
1 1
2 0
```

### 输出

```
1
```

# 题解

## 作者：世末OIer (赞：6)

题目大意:

有n个点。问你在平面直角坐标系上，从中任选4个点，能组成多少个平行四边形

题解:

根据平行四边形的特点:它的两条对角线互相平分

线段ij的中点:((x[i]+x[j])/2,(y[i]+y[j])/2)

线段pq的中点:((x[p]+x[q])/2,(y[p]+y[q])/2)

同时乘上2:(x[i]+x[j],y[i]+y[j]) , (x[p]+x[q],y[p]+y[q])

得:如果x[i]+x[j]=x[p]+x[q],y[i]+y[j]=y[p]+y[q]，那么四边形ijpq为平行四边形。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
map<pair<int,int>,int>cnt;
int n,x[2002],y[2002];
int main(){
	int i,j;
	scanf("%d",&n);
	for(i=0;i<n;++i) scanf("%d%d",x+i,y+i);
	for(i=0;i<n;++i) for(j=0;j<i;++j) ++cnt[mp(x[i]+x[j],y[i]+y[j])];
	ll ans=0;
	for(map<pair<int,int>,int>::iterator it=cnt.begin();it!=cnt.end();it++){
		int t=it->second;
		ans+=t*(t-1)/2;
	}
	printf("%I64d\n",ans);
	return 0;
}
```

---

## 作者：jianhe (赞：4)

我们考虑平行四边形的性质，根据初二数学知识：

1. 对边平行且相等。
2. 对角线互相平分。

如果采用第一种，就枚举两个点，算两个点直接的距离以及所在直线的斜率即可。但细节稍微复杂，我选择了第二种。

如果采取第二种，我们枚举两个点并计算中点，最后枚举中点并计算答案即可。

在实际实现时，为了避免小数，我们可以给中点乘二，具体可见代码。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2010;
ll n,x[N],y[N],ans;
map<pair<ll,ll>,ll> p;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			p[{x[i]+x[j],y[i]+y[j]}]++;
	for(auto t:p) ans+=t.second*(t.second-1)/2;	
	cout<<ans;
	return 0;
}
```

---

## 作者：xunhuanyihao (赞：3)

### CF660D Number of Parallelograms
平行四边形判定定理之一：对角线互相平分的四边形是平行四边形。所以我们可以枚举两个顶点，两点 $x$ 坐标，$y$ 坐标分别相加除以 $2$ 就是中点所在位置，如果枚举四个点 $A,B,C,D$，若线段 $AC$ 的中点坐标等于线段 $BD$ 的中点坐标，则四边形 $ABCD$ 是平行四边形。那么我们只要判断有多少个可能的线段中点坐标相同即可，由于只要判是否相同，可以将所有中点的 $x,y$ 坐标同时 $\times 2$，最后统计坐标相同的中点的个数即可。时间复杂度 $O(n^2)$。


不过这里用了 map，时间复杂度变为 $O(n^2 \log n^2)$。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
int n;
pii a[N];
map<pii, int>mp;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    for (int i = 1; i <= n; i++) 
        for (int j = i + 1; j <= n; j++) { 
            mp[{a[i].first + a[j].first, a[i].second + a[j].second}]++;
        }
    ll ans = 0;
    for (auto [x, y] : mp) {
        ans += y * (y - 1) / 2;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Frank08 (赞：2)

## 思路

众所周知，平行四边形是由**两组相连的平行线**组成的，我们可以找到所有**等长**的平行线的组数。可以证明，当一组平行线等长时，这两条线的两个端点可以另外组成一组平行线，既可以满足组成平行四边形。但一个平行四边形中含有两组这样的平行线，所以最后的答案要**除二**。

#### 如何判断两条平行线是否平行切等长？
- 可以证明，当 $x_A - x_B = x_C - x_D$ 且 $y_A - y_B = y_C - y_D$ 时，线段 $AB$ 与线段 $CD$ 平行且等长。

## 完整代码

```cpp
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;

map <pair<int,int>,int> mp;
pair <int,int> x[2002];

int main(){
	int n; scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		scanf("%d%d",&x[i].first,&x[i].second);
	sort(x + 1,x + n + 1);
	for(int i = 1;i < n;i++)
		for(int j = i + 1;j <= n;j++)
			mp[make_pair(x[j].first - x[i].first,x[j].second - x[i].second)]++;
	int ans = 0;
	for(auto i : mp)
		ans += i.second * (i.second - 1) / 2;
	printf("%d",ans / 2);
}
```
[AC记录](https://codeforces.com/contest/660/submission/253481317)

---

## 作者：tZEROちゃん (赞：0)

> 平面上 $n$ 个点能组成多少平行四边形。$1\le n\le 2\times 10^3$。

注意到平行四边形两条对角线的交点是这两条对角线的中点。另外对于两个点 $(x_A, y_A), (x_B, y_B)$，他们的中点是 $(\dfrac{x_A + x_B}{2}, \dfrac{y_A + y_B}{2})$。

因此我们枚举两个点，计算出 $P(\dfrac{x_A + x_B}{2}, \dfrac{y_A + y_B}{2})$ 的值，然后对这个点出现的次数 $cnt_P$ 加上 $1$。

显然答案是 $\sum \dfrac{cnt_P(cnt_P-1)}{2}$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)

const int N = 2010;

int x[N], y[N];

int main() {
  map<pair<int, int>, int> mp;
  int n; cin >> n; rep (i, 1, n) cin >> x[i] >> y[i];
  rep (i, 1, n) rep (j, 1, i - 1) mp[{x[i] + x[j], y[i] + y[j]}]++;
  int ans = 0;
  for (auto i : mp) ans += i.second * (i.second - 1) / 2; 
  cout << ans << endl;
}
```

---

## 作者：shao0320 (赞：0)

#### CF660D Number of Parallelograms

套路题。

两条边能组成平行四边形的充要条件是平行且相等。

那枚举两个点建立一个向量，把这个向量的长度和斜率打成一个$pair$塞进$map$中，然后统计每一种$pair$的出现次数即可。

注意每种平行四边形会被算两次（两组对边分别算一次），因此最后答案要除以$2$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<cmath>
#define mp make_pair
#define N 2005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,x[N],y[N],ans;
map<pair<long long,double>,int>MP;
long long dist(int i,int j){return (long long)(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(long long)(y[i]-y[j]);}
double slope(int i,int j){if(x[i]==x[j])return 1e9;return (y[i]-y[j])*1.0/(x[i]-x[j]);}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		x[i]=read();
		y[i]=read();
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			//cout<<"@@@@@@@@"<<i<<" "<<j<<endl;
			//cout<<dist(i,j)<<" ";
			//cout<<slope(i,j)<<endl;
			MP[mp(dist(i,j),slope(i,j))]++;
			//cout<<"!!!!!!!!!"<<i<<" "<<j<<endl;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			int tmp=MP[mp(dist(i,j),slope(i,j))];
			if(tmp)
			{
				//cout<<i<<" "<<j<<" "<<tmp<<endl;
				ans+=tmp*(tmp-1)/2;
				MP[mp(dist(i,j),slope(i,j))]=0;
			}
		}
	}
	printf("%d\n",ans/2);
	return 0;
}

```



---

