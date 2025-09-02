# New Year and Rainbow Roads

## 题目描述

Roy and Biv have a set of $ n $ points on the infinite number line.

Each point has one of 3 colors: red, green, or blue.

Roy and Biv would like to connect all the points with some edges. Edges can be drawn between any of the two of the given points. The cost of an edge is equal to the distance between the two points it connects.

They want to do this in such a way that they will both see that all the points are connected (either directly or indirectly).

However, there is a catch: Roy cannot see the color red and Biv cannot see the color blue.

Therefore, they have to choose the edges in such a way that if all the red points are removed, the remaining blue and green points are connected (and similarly, if all the blue points are removed, the remaining red and green points are connected).

Help them compute the minimum cost way to choose edges to satisfy the above constraints.

## 说明/提示

In the first sample, it is optimal to draw edges between the points (1,2), (1,4), (3,4). These have costs 4, 14, 5, respectively.

## 样例 #1

### 输入

```
4
1 G
5 R
10 B
15 G
```

### 输出

```
23
```

## 样例 #2

### 输入

```
4
1 G
2 R
3 B
10 G
```

### 输出

```
12
```

# 题解

## 作者：E_huan (赞：7)

吐槽：省选计划的某些作业实在是太难太难了~（尤其是本周的黑色Ynoi们）。放弃了，写点 CF 题换换脑子。如果神犇们发现本篇题解的错误的话请评论或私信指出，感激不尽！

------------
### 贪心+分类讨论

只有绿点不会被删除，所以肯定从绿点下手。

发现任何红点或蓝点不会跨过一个绿点连边。因为当  $x<y<z$ 且 $y$ 为绿点时，$x$ 与 $z$ 连边的花费与 $x$ 与 $y$ 连边且 $y$ 与 $z$ 连边的费用相同，但是 $y$ 不会被去掉，而 $x$ 和 $z$ 可能被去掉，所以跨过绿点连边一定不会更优。

所以只需要考虑两个绿点之间的点怎么连。
红点和蓝点之间的边没有任何意义，根本不用连。

因此每个绿色与绿色之间的段内只有两种情况：

$1$. 

$绿-蓝-蓝-...-蓝-绿$ 

$绿-红-红-...-红-绿$


$2$.

$绿------------绿$

$绿-蓝-...-蓝 （断） 蓝-...-蓝-绿$

$绿-红-...-红 （断） 红-...-红-绿$

贪心地想，断开的一条边必定是蓝蓝之间的最长边和红红之间的最长边。只需要把两种情况的答案去最大值就可以了。
    
但是有特殊情况：

$1$. 全局没有出现绿色点（即一段首尾都不是绿色的情况）：所有红色点连起来，所有蓝色点连起来即可。其实就是两端的红色点的坐标差+两端的蓝色点的坐标差。

$2$. 开头不是绿色（即一段开头不是绿色，结尾是绿色的情况），只能把红色点和蓝色点都连到右边绿色点上。

$3$. 结尾不是绿色，和 $2$. 同理。

此外注意一下一段内不存在红色或蓝色的情况，具体细节可以看代码。

#### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300010,inf=1e9+10;
int n,x[N];
char c[N][2];
ll ans=0;
inline void work(int l,int r)
{
    int lred=inf,rred=-inf,lblue=inf,rblue=-inf;
    for(int i=l;i<=r;i++)
        if(c[i][0]=='R') lred=min(lred,x[i]),rred=max(rred,x[i]);
        else if(c[i][0]=='B') lblue=min(lblue,x[i]),rblue=max(rblue,x[i]);
    if(c[l][0]!='G'&&c[r][0]!='G') { ans+=((lred<rred)?rred-lred:0)+((lblue<rblue)?rblue-lblue:0); return;}
    if(c[l][0]!='G')
    {
        if(lred!=inf) ans+=x[r]-lred;
        if(lblue!=inf) ans+=x[r]-lblue;
        return;
    }
    if(c[r][0]!='G')
    {
        if(rred!=-inf) ans+=rred-x[l];
        if(rblue!=-inf) ans+=rblue-x[l];
        return;
    }
    int mx1=0,mx2=0,last1=x[l],last2=x[l];
    for(int i=l;i<=r;i++)
        if(c[i][0]=='R') mx1=max(mx1,x[i]-last1),last1=x[i];
        else if(c[i][0]=='B') mx2=max(mx2,x[i]-last2),last2=x[i];
    mx1=max(mx1,x[r]-last1);
    mx2=max(mx2,x[r]-last2);
    ans+=min((x[r]-x[l])*3-mx1-mx2,(x[r]-x[l])*2);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x[i]);
        scanf("%s",c[i]);
    }
    int last=1;
    for(int i=1;i<=n;i++)
        if(c[i][0]=='G') 
            work(last,i),last=i;
    work(last,n);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：liubai (赞：5)

# 上课讲到这个题，看到没有题解，索性写一发
## 直接上思路：
### 显然，红点只能与红点相连或与绿点相连，蓝点也是如此；
### 对于绿点有两种连的方法!
#### 1.两个绿点相连；
#### 2.两个绿点通过两条路径（必须同时拥有）
##### 一.绿->红->红->.....->红->绿相连
##### 二.绿->蓝->蓝->.....->蓝->绿相连;
#### 对于1的连法，我们可以通过删除之前连的最大红边和蓝边使结果更优
详细请看我蒟蒻的代码
```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int maxm=300005;
int n;
char c;
ll p[maxm];//p记录位置
ll ans,lastR,lastG,lastB,maxR,maxB;//lastR为当前红点的位置，其余同理。maxR记录当前红边的最大值，maxB为绿边
int main()
{
 scanf("%d",&n);
 for(int i=1;i<=n;i++)
 {
   scanf("%lld",p+i);
   cin>>c;
   if(c=='R'||c=='G')//注意到绿边时也要连边
   {
   	  if(lastR)//如果之前连接了红边
   	  {	
   	  ans+=p[i]-p[lastR];
   	  maxR=max(maxR,p[i]-p[lastR]);
   	  }
   	  lastR=i;
   }
   if(c=='B'||c=='G')
   {
   	   if(lastB)//如果之前连接了蓝边
   	   {
   	   	  ans+=p[i]-p[lastB];
   	   	  maxB=max(maxB,p[i]-p[lastB]);
   	   }
   	   lastB=i;
   }
   if(c=='G')
   {
   	  if(lastG)
   	  ans+=min((ll)0,p[i]-p[lastG]-maxB-maxR);/*0是连法1消耗的结果
                                                  后面为连法2消耗的结果，两者取min
   	  lastG=i;
   	  maxB=maxR=0;//每次都要清零，因为绿点相当于图的分割点，之前连的红边（举例）对于后面没有影响
   }
 }
 printf("%lld\n",ans);
 return ling;//你们懂的
}
```
#### 希望本蒟蒻的思路能给各位dalao一些帮助



---

## 作者：intel_core (赞：1)

首先，蓝点不可能和红点连边。

如果 $x,y$ 同色，且 $z$ 为绿色，还满足 $x<z<y$，那么一定不会出现 $(x,y)$ 这条边（因为可以被 $(x,z)$ 和 $(z,y)$ 平替）。

（实际上，如果 $x,y,z$ 都同色也有类似的结论）

如果没有绿色顶点，直接输出蓝点和红点的坐标极差之和就可以。

如果有绿色顶点，随便取出两个相邻的 $x_1,x_2$ 。

那么 $x_1,x_2$ 之间有两种连接方式：

* 处于这两个顶点之间的蓝点/红点间接都连到 $x_1,x_2$ 上。

* 所有蓝点连成一条链，所有红点连成一条链。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=3e5+10;
#define int long long
int n,ans,v1[NR],v2[NR],v3[NR];
int len1,len2,len3,now1,now3,last1,last3;

signed main(){
	cin>>n;v2[++len2]=-2e9;
	char c;
	for(int i=1,x;i<=n;i++){
		scanf("%lld %c",&x,&c);
		if(c=='R')v1[++len1]=x;
		if(c=='G')v2[++len2]=x;
		if(c=='B')v3[++len3]=x;
	}
	v2[++len2]=2e9;
	if(len2>2)ans=v2[len2-1]-v2[2];
	else{
		cout<<v1[len1]-v1[1]+v3[len3]-v3[1]<<endl;
		return 0;
	}
	for(int i=1;i<len2;i++){
		int maxn1=0,maxn3=0;
		last1=last3=v2[i];
		while(now1<len1&&v1[now1+1]<=v2[i+1])maxn1=max(maxn1,v1[++now1]-last1),last1=v1[now1];
		while(now3<len3&&v3[now3+1]<=v2[i+1])maxn3=max(maxn3,v3[++now3]-last3),last3=v3[now3];
		maxn1=max(v2[i+1]-last1,maxn1);
		maxn3=max(v2[i+1]-last3,maxn3);
		ans+=min(2*(v2[i+1]-v2[i])-maxn1-maxn3,v2[i+1]-v2[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# Problem
对一条直线上的点连边，使得只有红点和绿点的子图联通且只有蓝点和绿点的子图联通。
# Solution
由于端点均为绿点的边（以下称之为“绿边”）在两个子图中均存在，所以我们考虑这种边。  
可以证明绿边一定只会连相邻两个绿点，所以我们对相邻的两个绿点进行分类讨论。

## 1.绿边相连
我们要保证这两个绿点之间的所有红、蓝点分别连通，便有以下方法：
>将相邻红、蓝点分别连边，删掉最长一条边，如下图。
>![](https://cdn.luogu.com.cn/upload/image_hosting/4uinjglz.png)

我们可以用 st 表来维护区间最值。  

代价为三倍绿边长度减去最长的红、蓝边。
## 2.绿边不连
我们需要保证两个绿点连通，所以不能删掉最长边。

代价为两倍绿边长度。

**注意，我们这样只算了绿边之间的代价，还要加上最左边的绿点的左侧与最右边的绿点右侧的代价**
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5,LG=20;
int n,n1,n2,n3,a[N+5],b[N+5],mp1[N+5],mp2[N+5],lg[N+5],st1[N+5][LG+5],st2[N+5][LG+5];
int query1(int l,int r){
	int len=lg[r-l];
	return max(st1[l][len],st1[r-(1<<len)][len]);
}
int query2(int l,int r){
	int len=lg[r-l];
	return max(st2[l][len],st2[r-(1<<len)][len]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		char opt;
		cin>>x>>opt;
		if(opt=='B')a[++n1]=x;
		if(opt=='R')b[++n2]=x;
		if(opt=='P')a[++n1]=x,b[++n2]=x,n3++,mp1[n3]=n1,mp2[n3]=n2;
	}
	if(!n3){
		cout<<a[n1]-a[1]+b[n2]-b[1];
		return 0;
	}
	for(int i=1;i<n1;i++)st1[i][0]=a[i+1]-a[i];
	for(int i=1;1+(1<<i)<=n1;i++)for(int j=1;j+(1<<i)<=n1;j++)st1[j][i]=max(st1[j][i-1],st1[j+(1<<(i-1))][i-1]);
	for(int i=1;i<n2;i++)st2[i][0]=b[i+1]-b[i];
	for(int i=1;1+(1<<i)<=n2;i++)for(int j=1;j+(1<<i)<=n2;j++)st2[j][i]=max(st2[j][i-1],st2[j+(1<<(i-1))][i-1]);
	for(int i=2;i<=max(n1,n2);i++)lg[i]=lg[i>>1]+1;
	int ans=a[mp1[1]]-a[1]+b[mp2[1]]-b[1]+a[n1]-a[mp1[n3]]+b[n2]-b[mp2[n3]];
	for(int i=2;i<=n3;i++){
		int ans1=3*(a[mp1[i]]-a[mp1[i-1]]),ans2=2*(a[mp1[i]]-a[mp1[i-1]]);
		if(mp1[i]-mp1[i-1]>1)ans1-=query1(mp1[i-1],mp1[i]);
		else ans1-=a[mp1[i]]-a[mp1[i-1]];
		if(mp2[i]-mp2[i-1]>1)ans1-=query2(mp2[i-1],mp2[i]);
		else ans1-=a[mp1[i]]-a[mp1[i-1]];
		ans+=min(ans1,ans2);
	}
	cout<<ans;
}
```

---

## 作者：梦应归于何处 (赞：0)

### 题目大意

数轴上有 $n$ 个点，为红或绿或蓝色，用几条边连接它们，边长为两点距离，使去掉所有红点或蓝点后剩下的点连通，求最小边长和。

### 解法

蓝色和红色都会被删掉，很烦，先不管他们，我们先来看不会被删除的绿点。

在这里我们想一个事情：所有的绿点之间肯定有线连接。为什么呢？如果通过红色或蓝色的点连接那它们一旦被删掉那就不连通了。

我们来考虑两个绿点之间的情况。最后的那一个大区间就可以被分解成多个两个绿点之间的情况的情况。

两个绿点之间的情况有 $4$ 种。

1. 两个绿点之间什么都没有。

2. 两个绿点之间只有蓝点。

3. 两个绿点之间只有红点。

4. 两个绿点之间红点蓝点都有。

一共就只有这 $4$ 种情况。

我们先考虑第一种情况，也是最简单的情况，就直接两个点连一条线就可以了。

第二种情况我们可以直接用两倍的总长减掉红色点的最长间隔。

第三种情况和第二种情况一样。

第四种情况我们需要考虑两种情况，

第一种：两倍长度。

第二种：三倍长度减掉红色点和蓝色点的最大间隔。

把这两种情况取最小值就可以了。

### 细节

别忘了把两头的情况处理一下。

如果没有绿点也要处理一下。

这两种情况很好处理，处理方法请见代码。

### 代码


~~~cpp
#include <bits/stdc++.h>
#define TNTMAX INT_MAX
#define db double
#define ll long long
#define ex exit(0);
#define endl "\n"
#define inl inline
#define null NULL
#define pb(a) push_back(a)
using namespace std;
struct node {
	ll id;
	char col;
} a[4000000];
vector<ll> green;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].id >> a[i].col;
		if (a[i].col == 'G') {
			green.pb(i);
		}
	}
	if (green.empty()) {
		vector<ll> lan, hong;
		for (int i = 1; i <= n; i++) {
			if (a[i].col == 'R') {
				hong.push_back(i);
			} else if (a[i].col == 'B') {
				lan.push_back(i);
			}
		}
		ll len = lan.size();
		ll lenb = hong.size();
		cout << (a[lan[len - 1]].id - a[lan[0]].id) + (a[hong[lenb - 1]].id - a[hong[0]].id);
		return 0;
	}
	ll len = green.size();
	ll ans = 0;
	vector<ll> lan, hong;
	for (int i = 1; i < green[0]; i++) {
		if (a[i].col == 'R') {
			hong.push_back(i);
		} else if (a[i].col == 'B') {
			lan.push_back(i);
		}
	}
	if (!hong.empty()) {
		ans += (a[green[0]].id - a[hong[0]].id);
	}
	if (!lan.empty()) {
		ans += (a[green[0]].id - a[lan[0]].id);
	}
	lan.clear();
	hong.clear();
	for (int i = n; i >= green[len - 1] + 1; i--) {
		if (a[i].col == 'R') {
			hong.push_back(i);
		} else if (a[i].col == 'B') {
			lan.push_back(i);
		}
	}
	if (!hong.empty()) {
		ans += (a[hong[0]].id - a[green[len - 1]].id);
	}
	if (!lan.empty()) {
		ans += (a[lan[0]].id - a[green[len - 1]].id);
	}
	for (int i = 1; i < len; i++) {
		lan.clear();
		hong.clear();
		ll last = green[i - 1], first = green[i], len = a[first].id - a[last].id;
		lan.push_back(last);
		hong.push_back(last);
		for (int j = last + 1; j < first; j++) {
			if (a[j].col == 'R') {
				hong.push_back(j);
			} else if (a[j].col == 'B') {
				lan.push_back(j);
			}
		}
		lan.push_back(first);
		hong.push_back(first);
		ll lenhong = hong.size(), lenlan = lan.size();
		ll longgaphong = 0, longgaplan = 0;
		for (int j = 1; j < lenhong; j++) {
			longgaphong = max(longgaphong, a[hong[j]].id - a[hong[j - 1]].id);
		}
		for (int j = 1; j < lenlan; j++) {
			longgaplan = max(longgaplan, a[lan[j]].id - a[lan[j - 1]].id);
		}
		if (hong.size() == 2 && lan.size() == 2) {
			ans += len;
		} else if (hong.size() > 2 && lan.size() > 2) {
//			cout << longgaphong << " " << longgaplan << endl;
			ans += min(2 * len, 3 * len - longgaphong - longgaplan);
		} else if (hong.size() > 2) {
			ans += 2 * len - longgaphong;
		} else if (lan.size() > 2) {
			ans += 2 * len - longgaplan;
		}
	}
	cout << ans << endl;
	return 0;
}
~~~

---

