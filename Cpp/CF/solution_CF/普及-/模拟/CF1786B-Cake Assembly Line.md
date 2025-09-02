# Cake Assembly Line

## 题目描述

A cake assembly line in a bakery was once again optimized, and now $ n $ cakes are made at a time! In the last step, each of the $ n $ cakes should be covered with chocolate.

Consider a side view on the conveyor belt, let it be a number line. The $ i $ -th cake occupies the segment $ [a_i - w, a_i + w] $ on this line, each pair of these segments does not have common points. Above the conveyor, there are $ n $ dispensers, and when a common button is pressed, chocolate from the $ i $ -th dispenser will cover the conveyor segment $ [b_i - h, b_i + h] $ . Each pair of these segments also does not have common points.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1786B/346ba483d975827d12cf4a1c8655bc16066dc283.png) Cakes and dispensers corresponding to the first example.The calibration of this conveyor belt part has not yet been performed, so you are to make it. Determine if it's possible to shift the conveyor so that each cake has some chocolate on it, and there is no chocolate outside the cakes. You can assume that the conveyour is long enough, so the cakes never fall. Also note that the button can only be pressed once.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1786B/9d91448781ebe899dcbaa2a5c7ae76c17064ee03.png) In the first example we can shift the cakes as shown in the picture.

## 说明/提示

The first example is shown in the figures in the statement.

In the second example, we can move the conveyor, for example, so that the centers of the cakes are at $ 4, 9, 14, 19, 24 $ .

In the third example, we can't move the conveyor accordingly.

## 样例 #1

### 输入

```
4
3 10 5
65 95 165
40 65 145
5 2 1
1 6 11 16 21
4 9 14 19 24
3 3 2
13 22 29
5 16 25
4 4 1
27 36 127 136
35 50 141 144```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：c20231020 (赞：4)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1786B)

[codeforces](https://codeforc.es/contest/1786/problem/B)

### 题目大意

洛谷链接。

### 思路

> 声明：以下移动以向右为正方向。

对于第 $i$ 个蛋糕，至少需要移动 $(b_i-h)-(a_i-w)$ 个单位（左端点对齐），至多需要移动 $(b_i+h)-(a_i+w)$ 个单位（右端点对齐）。在这个区间内的移动都是合法的。

所以顺序扫一遍蛋糕并记录合法区间的左端点最大值与右端点最小值，如果前者**严格大于**后者，那么输出 `NO`，否则输出 `YES`。

时间复杂度 $O(n)$。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,h,w,a[100010],b[100010];
void solve(){
	cin>>n>>w>>h;int l=-2e9,r=2e9;//合法区间的左右端点
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i)cin>>b[i];
	for(int i=1;i<=n;++i){
		l=max(a[i]-w-b[i]+h,l);r=min(a[i]+w-b[i]-h,r);//求左端点最大值与右端点最小值
		if(l>r){//左端点最大值比右端点最小值还大，那么一定无解
			cout<<"no\n";
			return;
		}
	}
	cout<<"Yes\n";
	return;
}
int main(){
	int t=1;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：qfpjm (赞：2)

# 题解

- 由于第一个蛋糕所处的位置可以确定后面蛋糕的位置，所以考虑通过每一个蛋糕所对喷嘴来限制第一个蛋糕可移动的范围。

- 逐步缩小之后，如果发现左边大于右边，那么就是无解。

- 注意，有可能你算出来的蛋糕位置的范围会左大于右，所以需要比较一下。

- 具体见代码。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, n, w, h, a[100005], b[100005], c[100005];

int main()
{
	cin >> T;
	while (T --)
	{
		cin >> n >> w >> h;
		for (int i = 1 ; i <= n ; i ++)
		{
			cin >> a[i];
		}
		for (int i = 1 ; i <= n ; i ++)
		{
			cin >> b[i];
		}
		for (int i = 2 ; i <= n ; i ++)
		{
			c[i] = a[i] - a[i - 1];
		}
		bool flag = 0;
		int l = min(b[1] - h + w, b[1] + h - w);
		int r = max(b[1] - h + w, b[1] + h - w);
		int L = l, R = r;
		for (int i = 2 ; i <= n ; i ++)
		{
			l = min(b[i] - h + w, b[i] + h - w);
			r = max(b[i] - h + w, b[i] + h - w);
			L = max(L + c[i], l);
			R = min(R + c[i], r);
			if (L > R)
			{
				flag = 1;
				break;
			}
		}
		if (flag)
		{
			puts("NO");
			continue;
		}
		puts("YES");
	}
	return 0;
}
```


---

## 作者：yinhy09 (赞：1)

## 题目分析

这个题我们可以算出来使每一个巧克力酱出口的最左端点比每一个蛋糕的最左端点相等或靠右，最多能移动多少。此时我们不能移动的更多，否则就会有巧克力酱超出左侧。我们假设满足此条件的最大移动距离为 $minn$。（$minn>0$ 表示向右侧移，反之亦然）然后我们将所有的蛋糕都进行 $minn$ 的位移（`a[i]+=minn`），此时再去判断是否右侧能完全覆盖，即 $b_i+h$ 是否小于等于 $a_i+w$，如果任何一个 $i$ 都满足，那么就可以输出 `YES` 了。

$minn$ 的求法也十分简单，把所有蛋糕的最大移动距离取一下最小值，即 `minn=min(minn,(b[i]-h)-(a[i]-w));`

正确性证明：我们肯定希望位移尽可能大，这样 $a_i+w$ 就能更大，更有可能大过 $b_i+h$，但是如果我们的位移比 $minn$ 要大，就会有巧克力酱超出左端点，就卒了。所以 $minn$ 为最优选择。

## AC Code : 

```cpp
/*******************************
| Author:  yinhy09
| Problem: B. Cake Assembly Line
| Contest: Codeforces Round #850 (Div. 2, based on VK Cup 2022 - Final Round)
| URL:     https://codeforces.com/contest/1786/problem/B
| When:    2023-02-05 20:06:05
| 
| Memory:  256 MB
| Time:    1000 ms
*******************************/
 
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define multicase() ll T;scanf("%lld",&T);while(T--)
ll read()
{
	char c;
	ll x=0;
	ll f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll n,w,h;
const int maxn=1e5+10;
ll a[maxn],b[maxn];
ll minn=9e18,f=1;
int main()
{
	multicase()
	{
		minn=9e18;
		n=read(),w=read(),h=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++)b[i]=read();
		for(int i=1;i<=n;i++)minn=min(minn,(b[i]-h)-(a[i]-w));
		for(int i=1;i<=n;i++)a[i]+=minn;
		f=1;
		for(int i=1;i<=n;i++)
		{
			if(a[i]+w<b[i]+h)f=0;
		}
		if(f==0)printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```

谢谢观看

---

## 作者：liaiyang (赞：0)

我们将第一个蛋糕对准到最左边刚好淋到的位置上，检查一遍。

如果后面的蛋糕在左边淋出来了，这个蛋糕如果向左移动，那么最左边对齐的蛋糕肯定会淋出来，直接输出 `NO` 。

如果右边淋出来了，我们就把当前的蛋糕移到最左边，更新位移距离。

为了防止移动完之后从右边流出来，我们将第一个蛋糕对准到最右边刚好淋到的位置上，检查一遍。

如果后面的蛋糕在右边淋出来了，这个蛋糕如果向右移动，那么最右边对齐的蛋糕肯定会淋出来，直接输出 `NO` 。

如果左边淋出来了，我们就把当前的蛋糕移到最右边，更新位移距离。

如果全都满足，说明可行，输出 `YES` 。

对于每组数据，时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
#define cin std::cin
#define cout std::cout
#define endl std::endl
const int N=1e5+10;
int _,n,w,h,l,r,a[N],b[N];
void work(){
	cin>>n>>w>>h;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	l=b[1]-h+w-a[1],r=b[1]+h-w-a[1];//对齐第一个蛋糕
	for(int i=2;i<=n;i++){
		if(b[i]-h<a[i]-w+r){
			cout<<"NO"<<endl;
			return ;
		}
		if(b[i]+h>a[i]+w+r) r=b[i]+h-w-a[i];
		if(b[i]+h>a[i]+w+l){
			cout<<"NO"<<endl;
			return ;
		}
		if(b[i]-h<a[i]-w+l) l=b[i]-h+w-a[i];
	}
	cout<<"YES"<<endl;
}
main(){
	cin>>_;
	while(_--) work();
    return 0;
}

```

---

## 作者：PerssonBrown (赞：0)

## CF1786B 题解

首先可以明确的是，第 $i$ 个喷枪与第 $i$ 个蛋糕一对。

不妨把每一个蛋糕表示成一个区间 $[a_i,b_i]$，对应喷枪的涂抹范围表示为一个区间 $[l_i,r_i]$。

为了让喷枪只涂抹蛋糕，而不会有溢出部分，那么 $a_i+k_i\leq l_i$ 且 $r_i\leq b_i+k_i$（也就是 $[l_i,r_i]\subseteq [a_i+k_i,b_i+k_i]$）。

对于每一个蛋糕都求出使 $[l_i,r_i]\subseteq [a_i+k_i,b_i+k_i]$ 成立的 $k_i$ 的取值范围 $[m_i,n_i]$。由于我们需要满足每一个蛋糕，将所有蛋糕的 $k_i$ 值做并运算，如果最后是 $\emptyset$，那么输出 `NO`，否则输出 `YES`。


---

## 作者：BFSDFS123 (赞：0)

不知道 dispenser 怎么翻译，所以就用原文吧。

容易发现蛋糕移动范围是有限制的，因为蛋糕和 dispenser 都是 $n$ 个的，所以必然是一个 dispenser 对应一个蛋糕。

对于一个 dispenser 和一个蛋糕，我们可以求出这个蛋糕所能移动的距离的区间。区间很容易求，是 $[a_i-b_i-(w-h),a_i-b_i+(w+h)]$。

计算出所有移动距离的区间，之后如果这些区间有交集，那么输出 ``YES``，否则输出 ``NO``。

好像没开 ``long long`` 挂了一发，警钟撅烂。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
#define ull unsigned long long
#define ll long long
using namespace std;
#define int long long
const int Maxn=1e5+10;
int Ar[Maxn];
int b[Maxn];
void work()
{
	int n,w,h;
	scanf("%lld%lld%lld",&n,&w,&h);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&Ar[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
	}
	
	int L=-inf,R=inf;
	for(int i=1;i<=n;i++)
	{
		int nl=Ar[i]-b[i]-(w-h);
		int nr=Ar[i]-b[i]+(w-h);
		if(L>nr)
		{
			puts("NO");
			return ;
		}
		if(nl>R)
		{
			puts("NO");
			return ;
		}
		L=max(L,nl);
		R=min(R,nr);
	}
	if(L>R)
	{
		puts("NO");
		return ;
	}
	puts("YES");
}
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
}

```

---

## 作者：听取MLE声一片 (赞：0)

代码混乱邪恶。

因为蛋糕没有相交点，所以巧克力和蛋糕必定为一一对应。把第一个巧克力和蛋糕分别对齐，然后后面的和第一个取相对位置。

因为巧克力是和蛋糕左对齐，所以是可以右移的。

考虑从 2 到 $n$ 枚举每个蛋糕和巧克力。如果巧克力右端超出的蛋糕范围，那么一定无解。如果巧克力左端超出蛋糕，可以通过右移，记录需要右移的最大值 $mx$。右移也是有限度的，记录能右移的最小值 $mx$。

显然 $mx$ 不超过 $mx$ 和 $2\times(m-k)$ 的，根据这个判断即可。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+10;
int n,m,k,a[N],b[N];
signed main()
{
	int T=read();
	while(T--){
		n=read(),m=read(),k=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			if(i!=1)
			a[i]=a[i]-a[1]+(m-k);
		}
		for(int i=1;i<=n;i++){
			b[i]=read();
			if(i!=1)
			b[i]=b[i]-b[1];
		}
		int flag=1;
		int mx=0,mn=2e9;
		for(int i=2;i<=n;i++){
			if(b[i]+k>a[i]+m){
				flag=0;
				break;
			}
			mx=max(mx,(a[i]-m)-(b[i]-k));
			mn=min(mn,(a[i]+m)-(b[i]+k));
		}
		if(!flag)
			puts("NO");
		else{
			if(mx<=2*m-2*k&&mx<=mn)
				puts("YES");
			else puts("NO");
		}
	}
	return 0;
}

```

---

## 作者：loser_seele (赞：0)

首先可以把第一个对准，然后显然将其右移 $ \leq w-h $ 的距离是合法的。于是后面我们每遇到一个蛋糕都将其移动到巧克力的最左边位置，可以发现这样做每个蛋糕距离其最左端的距离是单调不增的，于是只需要考虑每次移动的位移之和是否超过第一个蛋糕的 $ w-h $ 即可。那么实际上我们可以把每个蛋糕可以摆放的位置表示成区间，然后判一下所有区间是否有交集即可。

时间复杂度 $ \mathcal{O}(n) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
int b[2000020];
signed main()
{
int T;
cin>>T;
while(T--)
{
    int n,w,h;
    cin>>n>>w>>h;
    w-=h;
	for(int i=1;i<=n;i++)
    cin>>a[i];
	for(int i=1;i<=n;i++)
    cin>>b[i];
	int L=-2e9,R=2e9;
	for(int i=1;i<=n;i++)
	{
		int l=a[i]-w-b[i],r=a[i]+w-b[i];
		L=max(l,L);
		R=min(r,R);
	}
	if(L<=R)	
    Y;
	else	
    N;
}
}
```


---

