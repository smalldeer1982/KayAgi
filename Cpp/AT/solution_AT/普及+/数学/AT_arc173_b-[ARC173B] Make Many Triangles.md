# [ARC173B] Make Many Triangles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc173/tasks/arc173_b

二次元平面上に相異なる $ N $ 個の点があります。 $ i $ 番目の点の座標は $ (x_i,y_i) $ です。

これらの点のいずれかを頂点とする（非退化な）三角形をたくさん作りたいです。ただし、同じ点を複数の三角形の頂点として用いることはできません。

最大で何個の三角形が作れるか求めてください。

   非退化な三角形とは 非退化な三角形とは、 $ 3 $ つの頂点が同一直線上に並ばない三角形のことを指します。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 300 $
- $ -10^9\ \leq\ x_i,y_i\ \leq\ 10^9 $
- $ i\ \neq\ j $ ならば $ (x_i,y_i)\ \neq\ (x_j,y_j) $
- 入力される値はすべて整数
 
### Sample Explanation 1

例えば $ 1,3,6 $ 番目の点からなる三角形と $ 2,4,5 $ 番目の点からなる三角形を考えると、三角形を $ 2 $ つ作ることができます。 同じ点を複数の三角形の頂点として用いることはできませんが、三角形が共通部分を持っても構いません。

## 样例 #1

### 输入

```
7
0 0
1 1
0 3
5 2
3 4
2 0
2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
3
0 0
0 1000000000
0 -1000000000```

### 输出

```
0```

# 题解

## 作者：Redamancy_Lydic (赞：6)

## 背景

前几天打了比赛，崩麻了，所以来水一篇题解。~~LC真睿智~~

## 题意

给你 $n$ 个点，问最多能组成几个三角形。

## 分析

~~听说可以随机化~~。这道题就是一个简单贪心。

我们考虑，如果没有共线的点，那么答案显然就是 $\frac{n}{3}$ 了。

如果有共线，我们容易想到一个贪心思路：既然同一直线上的点不能组成三角形，那么应该尽可能让多的不在这条直线上的点消耗这条直线上的点，即设直线上点的集合为 $C$，那么对于任意 $\{x,y\}\notin C$，让它和 $C$ 中的两个元素组成三角形即可。这种情况下答案显然是 $n-card(C)$，限制条件是直线上的点能够消耗完其余点，即 $\frac{card(C)}{2}> n-card(C) $。

由于 $1\leq n \leq 300 $ 的奇妙范围，直线的寻找可以直接暴力三重循环。对于是否共线的判断，可以用相似来证，具体在代码里面。

然后就可以上代码了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
} 
const int maxn=1e6+10;
int n;
struct no
{
	int x,y;
}a[500]; 
int ans=-maxn;//记录最长直线 
bool ch(no x,no y)//判断是否共线 
{
    return x.x*y.y==x.y*y.x;
}
no operator -(no x,no y)
{
    return (no){x.x-y.x,x.y-y.y};
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x=read(),y=read();
		a[i]={x,y};
	}
	for(int i=1;i<n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			int sum=2;
			for(int k=1;k<=n;k++)
			{
				if(k==i||k==j)continue;
				if(ch(a[k]-a[i],a[k]-a[j]))sum++;
			}
			ans=max(ans,sum);//更新最大值 
		}
	}
	if(ans/2>n-ans)cout<<n-ans;//直线可以消耗所有点 
	else cout<<n/3;//不能 
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：3)

有一个显然的错误贪心：对于能够取的点我们尽量先取。

我们充分发扬人类智慧，将所有点随机赋权并暗权值从小到大排序，只要 $i,j,k$ 能构成三角形，即这三点不共线，就直接加入答案。多随几次即可通过。

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N=305;
const double eps=1e-11;
struct Node{
	int x,y,w;
}a[N],c[N];
int n,flag[N],ans,sum;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
bool cmp(Node xxx,Node yyy){
	return xxx.w<yyy.w;
}
bool check(int x,int y,int z){
	c[1].x=a[x].x;c[1].y=a[x].y;
	c[2].x=a[y].x;c[2].y=a[y].y;
	c[3].x=a[z].x;c[3].y=a[z].y;
	sort(c+1,c+4,cmp);
	if(c[2].x==c[1].x&&c[3].x==c[2].x)return 1;
	if(c[2].y==c[1].y&&c[3].y==c[2].y)return 1;
	if(c[2].x==c[1].x||c[3].x==c[2].x)return 0;
	if(c[2].y==c[1].y||c[3].y==c[2].y)return 0;
	double k1=(1.0*c[2].y-1.0*c[1].y)/(1.0*c[2].x-1.0*c[1].x);
	double k2=(1.0*c[3].y-1.0*c[2].y)/(1.0*c[3].x-1.0*c[2].x);
	//printf("%.5Lf %.5Lf\n",k1,k2);
	if(abs(k1-k2)<=eps)return 1;
	return 0;
}
signed main(){
	clock_t st=clock();
	srand(time(0));
	n=read();
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read();
	while(1){
		if(clock()-st>1.95*CLOCKS_PER_SEC)break;
		for(int i=1;i<=n;i++)a[i].w=rand();//cout<<a[i].w<<" ";
		//cout<<endl;
		memset(flag,0,sizeof(flag));
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				for(int k=j+1;k<=n;k++){
					if(flag[i]||flag[j]||flag[k])continue;
					if(check(i,j,k))continue;
					sum++;flag[i]=1;flag[j]=1;flag[k]=1;
				}
			}
		}
		//cout<<sum<<endl;
		ans=max(ans,sum);sum=0;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Starrykiller (赞：2)

这里提供一种随机化做法。

考虑每次对于第 $i$ 个点，若其未被使用，则找到其后面的第一组 $(j,k)$ 使得 $\triangle A_iA_jA_k$ 面积不为 $0$（这个可以用叉积非常容易地判定，具体见 [ABC340F] S=1）。然后令 $i\gets i+1$，重复以下过程。

发现这个过程如果只做一次的话，会 [WA*32](https://atcoder.jp/contests/arc173/submissions/51132034)。但是我们可以对序列 shuffle 100 次（$100n^3\le 2\times 10^8$），就可以通过了。

[Submission](https://atcoder.jp/contests/arc173/submissions/51132782)。

---

## 作者：Phartial (赞：1)

你谷题解区没有任何一篇非随机化题解提到了正确性证明，我觉得这玩意显然不了一点吧。。。

首先你拉一条直线 $l$，设这条直线穿过了 $c$ 个题目给的整点，那么因为每个三角形都至少要有一个点不在 $l$ 上，就可以得到一个上界是 $n-c$，而且这个上界在某些条件下也是可以得到的：选 $l$ 上的两个点和 $l$ 外的一个点配对，如果可以把 $l$ 外的点用完就可以得到 $n-c$ 个三角形，有限制 $2(n-c)\le c$，即 $c\ge \frac{2}{3}n$。

找到穿过点最多的直线，然后看一下它经过的点数量 $c$ 和 $\frac{2}{3}n$ 的大小关系，如果 $c\ge\frac{2}{3}n$ 则答案为 $n-c$，否则以上的构造过程无法成立。

然后大胆猜一下，如果 $c<\frac{2}{3}n$，那么一定能得到上界 $\lfloor\frac{n}{3}\rfloor$。

考虑证明，先做一个放缩，让 $c<\frac{2}{3}n$ 变成 $c\le\lceil\frac{2}{3}n\rceil$，这种形式会更好处理。

使用数学归纳法，$n=3,4,5$ 的情况是显然的，对于某个 $n\ge 6$，因为 $c\le\lceil\frac{2}{3}n\rceil$，我们总是可以找到一个非退化的三角形。把它删掉，如果剩下的 $n-3$ 个点中还是不存在经过超过 $\lceil\frac{2}{3}(n-3)\rceil$ 个点的直线，归纳即证；否则，设这条直线为 $l$。

设 $l$ 经过了 $c$ 个点，那么应当有 $\lceil\frac{2}{3}(n-3)\rceil<c\le\lceil\frac{2}{3}n\rceil$，所以 $c$ 只能是 $\lceil\frac{2}{3}n\rceil-1$ 或 $\lceil\frac{2}{3}n\rceil$。

若 $c=\lceil\frac{2}{3}n\rceil$，就有 $n-c=\lfloor\frac{n}{3}\rfloor$，我们可以通过选 $l$ 上的 $2$ 个点与不在 $l$ 上的一个点的构造方式得到 $\lfloor\frac{n}{3}\rfloor$ 个三角形。

若 $c=\lceil\frac{2}{3}n\rceil-1$，我们就用两个在 $l$ 上的点和一个不在 $l$ 上的点组一个三角形，那么 $l$ 上就只剩下 $\lceil\frac{2}{3}n\rceil-3$ 个点，$l$ 外只剩下 $\lfloor\frac{n}{3}\rfloor$ 个点，如果有一条直线穿过了 $l$ 外的所有点和 $l$ 中的一个点，要使归纳假设不成立，就要有 $\lfloor\frac{n}{3}\rfloor+1>\lceil\frac{2}{3}n\rceil-2$，在 $n\ge 6$ 的范围里只有 $n=6$ 满足这个式子，手玩一下不难发现此时仍然可以构造出 $\lfloor\frac{n}{3}\rfloor$ 个三角形。

于是我们就完成了证明。找直线 $\Theta(n^3)$ 暴力找就行。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 301;

int n, ans;
LL x[kN], y[kN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> x[i] >> y[i];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      int c = 0;
      for (int k = 1; k <= n; ++k) {
        c += (y[j] - y[i]) * (x[k] - x[i]) == (y[k] - y[i]) * (x[j] - x[i]);
      }
      ans = max(ans, c);
    }
  }
  cout << min(n / 3, n - ans);
  return 0;
}
```

---

## 作者：coderJerry (赞：1)

$\operatorname{Update } 2024/04/29$：已经修改好格式，烦请管理员再次审核。
### 题目描述
给定 $n$ 个点，每个点只能选一次，问最多能组成多少三角形。
### 题目分析
显然最好情况下能组成 $\lfloor\frac{n}{3}\rfloor$ 个三角形。如果这些点大多都共线，我们还要计算出来这 $n$ 个点里最多有多少个共线，设为 $s$。当 $s≥\lfloor\frac{2n}{3}\rfloor$，我们可以在这 $s$ 个点中选两个并在剩下 $n-s$ 个点中选一个组成三角形。于是最后答案即为 $\min(\lfloor\frac{n}{3}\rfloor,n-s)$。

至于判定共线，那就记结论。若 $i,j,k$ 共线，则：$|(x_i-x_j)\times (y_i-y_k)|=|(x_i-x_k)\times(y_i-y_j)|$。
### AC 代码
注意上文判定共线的乘法处可能会爆 ```int```，要开 ```long long```。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,x[310],y[310],ans=0;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int cnt=0;
            for(int k=1;k<=n;k++){
                int x1=x[i]-x[j],y1=y[i]-y[j];
                int x2=x[i]-x[k],y2=y[i]-y[k];
                if(abs(x1*y2)==abs(x2*y1)) cnt++;
            }
            ans=max(ans,cnt);
        }
    }
    cout<<min(n/3,n-ans)<<endl;
    return 0;
}
```

---

## 作者：hinin (赞：0)

用若干条直线把不共线所有点串起来，以同一直线上的两点为底，直线外另一点为顶点配对。

令最大的直线上的点数为 $k$，如果 $n - k \geq \frac{k}{2} + k \bmod 2$，那么这条直线上的点一定可以被消除。否则不行。

题目就变成若干集合彼此相消。

``` cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll>

using namespace std;

ll n; 
pii Data[304];

bool check(ll a, ll b, ll c)
{
	ll x1 = Data[a].first - Data[c].first;
	ll y1 = Data[a].second - Data[c].second;
	ll x2 = Data[b].first - Data[c].first;
	ll y2 = Data[b].second - Data[c].second;
	return x1 * y2 - x2 * y1;
}

int main()
{
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 

	cin >> n;
	for(ll i = 1; i <= n; i ++) { cin >> Data[i].first >> Data[i].second; }


	ll Max = 0;
	for(ll i = 1; i < n; i ++) {
		for(ll j = i + 1; j <= n; j ++) {
			ll cnt = 0;
			for(ll k = 1; k <= n; k ++) {
				if(check(i, j, k) == 0) { cnt ++; }
			}

			Max = max(Max, cnt);
		}
	}

	cout << min(n / 3, n - Max) << endl;
	
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## 题目
二维平面内有 $n$ 个不同的点。问可以组成多少个不退化的三角形（每一个节点只可以被使用一次）。

不退化的三角形只三点不共线的三角形。
## 思路
这个问题可以随机化。

考虑随机打乱顺序，然后每一次选择字典序最小且合法的 $(i,j,k)$ 作为三角形确定下来。

将这个算法运算直到时间大于 $0.9$ 秒输出答案最大值。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace fastIO{
	inline int read(){
		int x=0,f=1;char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-f;ch=getchar();}
		while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
		return x*f;
	}
	int buf[20],TOT;
	inline void print(int x,char ch=' '){
		if(x<0) putchar('-'),x=-x;
		else if(x==0) buf[++TOT]=0;
		for(int i=x;i;i/=10) buf[++TOT]=i%10;
		do{putchar(buf[TOT]+'0');}while(--TOT);
		putchar(ch);
	}
}
using namespace fastIO;
const int MAXN=305;
int n,p[MAXN],ans;
bool vis[MAXN];
struct node{
	int x,y;
	bool friend operator<(const node &A,const node &B){
		return A.x==B.x?A.y<B.y:A.x<B.x;
	}
}a[MAXN],b[MAXN];
bool check(){
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		for(int j=i+1;j<=n;j++){
			if(vis[j]) continue;
			for(int k=j+1;k<=n;k++){
				if(vis[k]) continue;
				if((a[i].x-a[j].x)*(a[i].y-a[k].y)!=(a[i].x-a[k].x)*(a[i].y-a[j].y)){
					vis[i]=vis[j]=vis[k]=1;
					return 1;
				}
			}
		}
	}
	return 0;
}
signed main(){
	srand(time(0));
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read();
		b[i]=a[i];
	}
	while(1.0*clock()/CLOCKS_PER_SEC<0.9){
		for(int i=1;i<=n;i++) p[i]=i;
		random_shuffle(p+1,p+n+1);
		for(int i=1;i<=n;i++) a[i]=b[p[i]];
		int sum=0;
		while(check()) sum++;
		ans=max(ans,sum);
		memset(vis,0,sizeof(vis));
	}
	
	print(ans);
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

如果多个点共线，那么它们中的任意三个点无法组成三角形。这其中包含最多点的直线无疑对答案有直接影响，将它单独拿出来分析：用直线外的一个点可以与直线上的两个点组成三角形，若最后剩下了直线上的点，则无法处理；否则通过灵活调配可以使得直线外的点被充分使用。故分类讨论即可。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;
const long double eps = 1e-7;
int n;
long double x[310], y[310];
long long ans, maxn;
inline bool equ(long double x, long double y)
{return abs(x - y) <= eps;}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= n; ++j)
		{
			if(j == i) continue;
			bool flag = false;
			if(x[i] == x[j]) flag = true;
			long long res = 0;
			for(int k = 1; k <= n; ++k)
			{
				if(flag)
				{
					if(x[k] == x[i])
						++res;
				}
				else
				{
					if(k == i) ++res;
					else if(k == j) ++res;
					else if(x[i] != x[k] && x[j] != x[k] && equ((y[i] - y[j]) / (x[i] - x[j]), (y[i] - y[k]) / (x[i] - x[k])))
					{
						++res;
					}
				}
			}
			maxn = max(maxn, res);
		}
	}
//	cout << maxn << '\n';
	cout << min(n - maxn, 1ll * n / 3) << '\n';
	return 0;
}
```

---

## 作者：无名之雾 (赞：0)

~~考场乱搞成功切。~~

## The first method

有一个比较好看出的结论：如果经过最多点的一条线经过了 $k$ 个点，那么答案是 $\min(n-k,n/3)$。

## The second method

下面来讲考场我写的随机化算法。

我们只需要用一个显然错误的贪心优先选取可以取到的点，如果可以组成三角形，每次进行答案更新。并且多次进行操作可过。

[赛时AC记录](https://atcoder.jp/contests/arc173/submissions/51136361)
### 良好码风代码
 
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define ld long double
#define pii pair <int, int>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int x[400], y[400], id[400],n,vis[400],ans,ord[400],tx[400],ty[400];
mt19937 rnd(time(0));
inline bool check(int i,int j,int k){
	if(tx[i]== x[j]&&tx[j]==tx[k])return 1;
	ld k1=(ty[i]-ty[j])*1.00/(tx[i]-tx[j]);
	ld k2=(ty[k]-ty[j])*1.00/(tx[k]-tx[j]);
	ld b1=ty[i]-k1*tx[i];
	ld b2=ty[j]-k2*tx[j];
	if(abs(k1-k2)<0.000001&&abs(b1-b2)<0.000001)return 1;
	return 0;
}
signed main() {
	n=read();
	for(int i=1;i<=n;i++)x[i]=read(),y[i]=read();
	for(int i=1;i<=n;i++)ord[i]=i;
	do{
		memset(vis,0,sizeof vis);
		shuffle(ord+1,ord+n+1,rnd);
		for(int i=1;i<=n;i++)tx[i]=x[ord[i]],ty[i]=y[ord[i]];
		int tans=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				for(int k=j+1;k<=n;k++){
					if(vis[i]||vis[j]||vis[k])continue;
					if(check(i,j,k))continue;
					tans++;
					vis[i]=vis[j]=vis[k]=1;
				}
			}
		}
		ans=max(tans, ans);
	}while(clock()*1.0/CLOCKS_PER_SEC<1.95);
	cout<<ans;
	return 0;
}
```

---

