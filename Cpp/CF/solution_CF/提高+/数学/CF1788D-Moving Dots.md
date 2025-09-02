# Moving Dots

## 题目描述

We play a game with $ n $ dots on a number line.

The initial coordinate of the $ i $ -th dot is $ x_i $ . These coordinates are distinct. Every dot starts moving simultaneously with the same constant speed.

Each dot moves in the direction of the closest dot (different from itself) until it meets another dot. In the case of a tie, it goes to the left. Two dots meet if they are in the same coordinate, after that, they stop moving.

After enough time, every dot stops moving. The result of a game is the number of distinct coordinates where the dots stop.

Because this game is too easy, calculate the sum of results when we play the game for every subset of the given $ n $ dots that has at least two dots. As the result can be very large, print the sum modulo $ 10^9+7 $ .

## 说明/提示

In the first example, for a subset of size $ 2 $ , two dots move toward each other, so there is $ 1 $ coordinate where the dots stop.

For a subset of size $ 3 $ , the first dot and third dot move toward the second dot, so there is $ 1 $ coordinate where the dots stop no matter the direction where the second dot moves.

For $ [1, 2, 4, 6] $ , the first and second dots move toward each other. For the third dot, initially, the second dot and the fourth dot are the closest dots. Since it is a tie, the third dot moves left. The fourth dot also moves left. So there is $ 1 $ coordinate where the dots stop, which is $ 1.5 $ .

Because there are $ 6 $ subsets of size $ 2 $ , $ 4 $ subsets of size $ 3 $ and one subset of size $ 4 $ , the answer is $ 6 \cdot 1 + 4 \cdot 1 + 1 = 11 $ .

In the second example, for a subset of size $ 5 $ (when there are dots at $ 1 $ , $ 3 $ , $ 5 $ , $ 11 $ , $ 15 $ ), dots at $ 1 $ and $ 11 $ will move right and dots at $ 3 $ , $ 5 $ , $ 15 $ will move left. Dots at $ 1 $ , $ 3 $ , $ 5 $ will eventually meet at $ 2 $ , and dots at $ 11 $ and $ 15 $ will meet at $ 13 $ , so there are $ 2 $ coordinates where the dots stop.

## 样例 #1

### 输入

```
4
1 2 4 6```

### 输出

```
11```

## 样例 #2

### 输入

```
5
1 3 5 11 15```

### 输出

```
30```

# 题解

## 作者：thostever (赞：16)

如果一些连续的点最终汇聚成一个点，那么它们运动方向一定形如：$\{\rightarrow,\cdots,\rightarrow,{\color{Red}\rightarrow},{\color{Red}\leftarrow},\leftarrow,\cdots,\leftarrow\}$。

我们考虑最中间的向右和向左的两个点（已标红），统计它们的贡献。

选定 $i$ 和 $j$ 为中间的两个点（$i < j$）。那么它们有贡献当且仅当：

1. $i$ 和 $j$ 之间所有的点都不能选。

2. $i$ 左边距离 $i$ 小于等于 $(x_j-x_i)$ 的点都不能选，$j$ 右边距离 $j$ 小于 $(x_j-x_i)$ 的点都不能选。

第一条是因为若 $i$ 和 $j$ 之间有点，那么 $i$ 和 $j$ 就不是最中间的两个点了。

第二条是因为如果不满足条件，那么 $i$ 就会往左边走或者 $j$ 就会往右边走。

至于剩下的 $k$ 个点，选和不选都可以，一共有 $2^k$ 的贡献。

若要找到第二条中的分界点，可以在左边和右边分别进行二分查找。时间 $O(n^2\log n)$。

代码提供一种双指针 $O(n^2)$ 时间的做法：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+7;
int n,m;
int a[3010];
int l[3010][3010],r[3010][3010];
ll pw[3010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		int p=i-1;
		for(int j=i+1;j<=n;j++)
		{
			while(p>=1&&a[i]-a[p]<=a[j]-a[i]) p--;
			l[i][j]=p;//求 i 前面的最靠后的可以选的点 
		}
		//下面为 j 在 i 前面 
		p=i+1;
		for(int j=i-1;j>=1;j--)
		{
			while(p<=n&&a[p]-a[i]<a[i]-a[j]) p++;
			r[j][i]=p;//求 i 后面最靠前的可以选的点 
		}
	}
	pw[0]=1; for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;// 2 的 i 次方 
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			ans+=pw[l[i][j]+n-r[i][j]+1]; ans%=mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：liujy_ (赞：5)

 直接枚举子集显然复杂度会炸掉。   
 每一轮结束时每个点肯定都会停留在一个坐标上，且一个坐标上可能有多个点。我们考虑枚举每个有点停留的坐标出现在在多少个子集里面。考虑一个坐标是如何产生的，肯定只有一个相邻的点对 $(i,j)$ 且它们互相是对方距离最近的点，这样 $(i,j)$ 就会产生一个新坐标。   
 接下来问题就剩下对于一个点对，当它们两个能产生贡献的时候会出现在多少个子集里。注意这个地方是强制要求这个点对会产生一个新的坐标。显然 $(i,j)$ 之间没有其它点，并且它们另一侧的点和它们的距离大于它们之间的距离。我们可以在一开始给坐标排个序，然后每次二分一个最右边且可以与 $i$ 相邻的点，显然这个点以及它左边的点都是可以存在的，$j$ 右边同理。这样我们就得到除去 $(i,j)$ 的所有选了不会影响的点，假设点数为 $s$，那么答案即为 $2^s$。枚举点对把答案加起来即可。   
 ```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=2e5+5,mod=1e9+7; 
int t,n,a[N],s[N];long long ans;
int solve1(int l,int r,int x){
	int res=0;//cout<<x<<endl; 
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid]<=x)res=mid,l=mid+1;
		else r=mid-1;
	}
	return res;
}
int solve2(int l,int r,int x){
	int res=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid]>=x)res=mid,r=mid-1;
		else l=mid+1;
	}
	return res;
} 
int ksm(int a,int b){
	int s=1;
	while(b){
		if(b&1)s=1ll*a*s%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return s;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			int x=a[j]-a[i];
			int zb1=solve1(1,i-1,a[i]-x-1);
			int zb2=solve2(j+1,n,a[j]+x);
			if(zb2==0)zb2=n+1;
			ans+=1ll*ksm(2,zb1)%mod*ksm(2,(n-zb2+1))%mod;
			if(ans>=mod)ans-=mod; 
		}
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：CQ_Bab (赞：4)

# 前言
这道题场切了，居然是蓝的。
# 思路
我们可以发现不能暴力，然后我们可以枚举一个左右端点然后我们来算它们都往中间走能产生的贡献，我们可以发现能起到贡献的就是不跟着 $i$ 和 $j$ 的方案数，那么我们可以给出一个区间 $l\sim r$ 表示在这个区间内的都会跟着 $i$ 和 $j$ 走到中间，那么我们就可以发现若在这个区间之外的有 $cnt$ 个那么就会有 $2^{cnt}$ 个贡献，所以我们就可以用二分来算出这个区间然后用总的减一下即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define il inline
#define in(x) scanf("%lld",&x)
#define w(x) while(x--)
int t;
int n;
const int mod=1e9+7,N=100010;
int a[N],res;
int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
signed main() {
	in(n);
	rep(i,1,n) in(a[i]);
	rep(i,1,n) {
		rep(j,i+1,n) {
			int l=a[j]-a[i]+1;
			int x=a[i]-l+1,y=a[j]+l-1;
			int tx=lower_bound(a+1,a+1+n,x)-a-1;
			int ty=lower_bound(a+1,a+1+n,y)-a-1;
			res=(res+qmi(2,n-ty+tx))%mod;
		}
	}
	cout<<res<<endl;
	return false;
}

```

---

## 作者：Feyn (赞：4)

一道比较板的题。

首先如果每个子点集的答案都是 $1$ 的话，那么答案应该就算 $2^n-n-1$。但是事实并不是这样的，这是因为有些子点集的点最后会停留在超过一个点的位置。观察这些情况，会发现如果一个点集会停留在多个位置当且仅当存在两个相邻的点，左边那个向左移动，右边那个向右移动。这样这两个点显然不会停留在同一个点，所以最后会停在多个位置上。更进一步发现，每产生一对上述的相邻点，最后点集的答案就会加一，所以问题就转变成了求这样的点对数。

枚举上述的点 $x,y(x<y)$，根据上面的定义，这两个点在选出的点集中是相邻的，也就是说中间的点都不会被选择。然后为了满足条件，说明 $x$ 左边有一个比 $y$ 更近的点，$y$ 右边有一个比 $x$ 更近的点。考虑前者，那些更近的点可以二分查找找出，假设数量是 $a$ 个，也就是说 $x$ 要往左走当且仅当这些点中选出至少一个，方案数是 $2^a-1$。右边同理，加起来就可以了。

复杂度 $O(N^2\log N)$。

感谢 @liaoyichen 指出笔误！


```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=3010;
const int mod=1e9+7;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,del,ans,a[N],e[N]={1};
inline int get(int val){
	int l=1,r=m+1,mid;
	while(l<r){
		if(a[(mid=(l+r)>>1)]>=val)r=mid;
		else l=mid+1;
	}
	return l;
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	
	read(m);
	for(int i=1;i<=m;i++)e[i]=e[i-1]*2%mod;
	for(int i=1;i<=m;i++)read(a[i]);
	for(int x=1;x<=m;x++){
		for(int y=x+1;y<=m;y++){
			int len=a[y]-a[x];
			int p=get(a[x]-len),q=get(a[y]+len)-1;
			int now=(e[x-p]-1)*e[p-1]%mod;
			now=now*(e[q-y]-1)%mod*e[m-q]%mod;
			del=(del+now)%mod;
		}
	}
	ans=e[m]-m-1;
	ans+=del;
	printf("%lld\n",(ans%mod+mod)%mod);
	
	return 0;
}
```

---

## 作者：liangbob (赞：2)

## $\mathtt{Problem\ Definition}$

题目讲得很抽象，这里直接上图说话：

![如果看到这行字，请私信我。](https://cdn.luogu.com.cn/upload/image_hosting/8334nz76.png)

## $\mathtt{Solution}$

核心思想很简单，但是最难想到的就是核心思想，这个核心思想就是“正难则反”。

一些点移动停下来后不同坐标的个数本身就是一个非常抽象的数，如果直接进行统计并没有什么很好的方法，只能模拟。

那是否意味着这道题是不可做题呢？显然不是的，“正难则反”，我们可以从反面进行考虑。

我们发现，每个不同坐标肯定是两个点走到一起形成的（这很显然，因为与其它点重合就停止），那么我们可以考虑枚举点对 $(i,j)$，然后看看 $(i,j)$ 会在再选其它哪些点的情况之下能走到一起，那么这种选的情况的 $f$ 值就加一。最后所有点统计完之后，每个子集的 $f$ 都自然确定了，之后一加就完事。我们像这样，通过不同坐标反向计算 $f$。

这里还要注意一点：不用统计每个子集的 $f$，而是对于所有点对 $(i,j)$，把答案加上 $(i,j)$ 的“再选其它点的情况之下能走到一起”的选择方案数 $t$ 就行。原因的话就是因为有 $t$ 种选择其它点的方案，对于这 $t$ 种的每一个 $f$ 值都要加上 $1$，每次统计相当于给答案加上 $t$ 个 $1$，因此，就是给答案加上 $t$。

接着我们就来考虑求 $t$ 的值。

怎么求？“正难则反”，我们考虑不能选的点。

先来证明一个定理：

如果距 $x$ 最近的点是 $t$，那么若干时刻过后，距 $x$ 最近的点还是 $t$。

证明：不妨设距 $t$ 最近的点是 $y$，且 $x$ 在 $t$ 右侧。

- 若 $y$ 在 $t$ 左侧，则 $x,t$ 都往左走，由于速度相同，两者距离不变。

  设有其他点 $v$，如果 $v$ 往左走，同理距离不变，$t$ 距离最小。如果如果 $v$ 往左右走，距离则会增大，$t$ 距离依然最小。

- 若 $y$ 在 $t$ 右侧，$x$ 往左走，$t$ 往右走，两者距离缩短，依然最小。

  设有其他点 $v$，如果 $v$ 往左走，距离不变，$t$ 距离最小。如果如果 $v$ 往左右走，距离则会增大，$t$ 距离依然最小。

那么也就是说，一个点一旦出发，它的方向就是定的。

接着看图说话：

![如果看到这行字，请私信我。](https://cdn.luogu.com.cn/upload/image_hosting/gz1ewgpl.png)

在左边黄色区域内，随便选一个点在里面都会把 $i$ “勾引”过去（因为它的距离比 $j$ 要小），根据上面的定理，而一旦勾引过去，就回不来了，因此左边黄色区域不能选点，为“危险区域”，右边黄色同理。那么自然而然，在粉色区域中，无论怎么选都不会勾引到任何一个点（因为距离都比 $j$ 要大），因此，$t$ 的值就是在粉色区域内乱选的方案数，为 $2^{t_1+t_2}$，其中 $t_1$ 为左边粉色区域点的个数，$t_2$ 为右边粉色区域点的个数。

问题又随之而来：$t_1$ 和 $t_2$ 又怎么算呢？这个就很简单了。我们给所有点排个序，然后二分找到最后一个（即下标最大的）小于 $i-c$ 的点，下标为 $p$；并同时二分找到第一个（下标最小的）大于等于 $j+c$ 的点，下标为 $q$。那么 $t_1=p$，$t_2=n-q+1$。

为什么 $t_1$ 是小于呢？因为由题意，当相邻两个距离都相同时，点总是会往左边走，那么你放在 $i-c$ 照样还是会被勾引，因此只能放在坐标比 $i-c$ 小的点。

## $\mathtt{Code}$

详见 <https://codeforces.com/contest/1788/submission/195932993>。

---

## 作者：masonpop (赞：1)

经典题。

首先发现一个性质：所有点的移动方向不会发生变化，始终为最开始的方向。这是因为点的移动速度相同，容易得到。

如果所有子集答案都是 $1$，那么总答案为 $2^n-(n+1)$。考虑什么情况会汇聚到多个点。可以发现，如果相邻两个点是形如 $\leftarrow \rightarrow$ 的运动情况的话，会额外产生一个点。容易发现总额外贡献就是这种相邻点对的数量。

枚举点对 $(x,y)$，考虑其贡献。显然，它们中间的点不能再取，而 $x$ 左边必须至少选出一个点离 $x$ 的距离相对于 $y$ 更近。$y$ 同理。显然二分查找。采用 `lower_bound` 和 `upper_bound` 函数。简单用乘法原理统计即可。

复杂度 $O(n^2\log n)$。如果用快速幂会增大常数，会被卡掉。需要预处理 $2$ 的幂次。[代码](https://codeforces.com/contest/1788/submission/210821519)。

---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/17212916.html)

[题目传送门](https://codeforces.com/problemset/problem/1788/D)  
[题目翻译](https://www.luogu.com.cn/problem/CF1788D)
### 题目解析
考虑怎样才能产生贡献，显然对于留下的相邻的 $l,r$，需要让 $l$ 向右，$r$ 向左即可产生 $1$ 的贡献。  
接下来就是考虑如何计算 $l$ 向右 $r$ 向左的方案数，其实就是计算左右两边最多可以留下的个数 $x$，方案数就是 $2^x$。  
考虑把左右两边的分开计算。  

我们发现，如果我们要让 $l$ 向右，枚举右边的 $l+1$ 到 $n$ 作为 $l$ 右边相邻的数，那么最左边可以留下的个数是单调不增的，所以枚举每一个 $l$，我们用双指针扫一次就好了。  
另一边同理。时间复杂度就是 $\Theta(n^2)$。

```cpp
int n,a[maxn],le[maxn][maxn],ri[maxn][maxn]; ll ans,pw[maxn];
int main(){
#ifdef LOCAL
	freopen("1.in","r",stdin);
#endif
	n=read(); int i,j,k; pw[0]=1;
	for(i=1;i<=n;i++) a[i]=read(),pw[i]=pw[i-1]*2%MOD;
	for(i=1;i<n;i++){
		k=i-1;
		for(j=i+1;j<=n;j++){
			while(a[i]-a[k]<=a[j]-a[i]&&k) k--;
			ri[i][j]=k;
		}
	}
	for(i=2;i<=n;i++){
		k=i+1;
		for(j=i-1;j>=1;j--){
			while(a[i]-a[j]>a[k]-a[i]&&k<=n) k++;
			le[i][j]=n-k+1;
		}
	}
	for(i=1;i<n;i++) for(j=i+1;j<=n;j++)
		ans+=pw[ri[i][j]+le[j][i]],ans%=MOD;
	print(ans); return 0;
}
```

---

## 作者：zhlzt (赞：0)

### 题解
让我们回想一下加强前的问题，在这个问题中，我们不考虑子集。

我们不难发现，每个点在移动过程中都不会改变方向。

假设点聚集在坐标 $x$ 处。坐标小于 $x$ 的最右边的点应该向右移动，坐标大于 $x$ 的最左边的点应该向左移动。我们可以观察到，相邻点相互移动的个数就是答案。

现在我们来解决子集问题。我们不计算每个子集的相邻点相互移动的个数，而是计算每个可能的 $1 \leq i < j \leq n$ 子集的个数，其中点 $i$ 向右移动，点 $j$ 向左移动，且 $i$ 和 $j$ 之间没有点。

设子集中点的坐标为 $k$ 。我们将尝试找出以点 $i$ 和点 $j$ 为聚集中心（即让旁边的点停留的位置）时对答案的贡献。

由于在 $i$ 和 $j$ 之间没有点，因此满足 $x_i <k< x_j$ 的点不应该出现在子集中。由于点 $i$ 应该向右移动，因此子集中不应该有满足 $k<x_i $ 和 $x_i-k \leq x_j-x_i$ 的点。同理，满足 $k>x_j$ 和 $k-x_j < x_j-x_i$ 的点也不应该出现在子集中。综上所述并移项，可得满足 $2x_i - x_j \leq k < 2x_j + x_i$ 的点不应该出现在子集中。

除此之外，其余的点选或不选不选均可，预处理 $2$ 的幂即可。由于 $(i, j)$ 有 $O(n^2)$ 对，我们可以在 $O(n^2)$ 的复杂度中解决问题。

代码中利用单调性而使用双指针预处理满足条件的 $k$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3010;
const int mod=1e9+7;
int d[maxn],dpow[maxn];
int dpl[maxn][maxn],dpr[maxn][maxn];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",d+i);
	for(int i=1;i<=n;i++){
		int pl=i-1,pr=i+1;
		for(int j=i+1;j<=n;j++){
			while(pl>=1 and 2*d[i]-d[j]<=d[pl]) pl--;
			dpl[i][j]=pl;
		}
		for(int j=i-1;j>=1;j--){
			while(pr<=n and d[pr]<2*d[i]-d[j]) pr++;
			dpr[j][i]=pr;
		}
	}
	int ans=0; dpow[0]=1;
	for(int i=1;i<=n;i++) dpow[i]=dpow[i-1]*2%mod;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			ans=(ans+dpow[dpl[i][j]+(n-dpr[i][j]+1)])%mod;
		}
	}
	printf("%d\n",ans); return 0;
}
```

---

## 作者：MSavannah (赞：0)

不难发现每个点的移动方向是一直不变的。

考虑一个点集，它的答案就是相邻的相对运动的点的对数。

进一步的一个点集的所有子集的答案是什么呢？枚举子集复杂度一定会炸，不可取。正难则反，我们计算每个满足条件的点对 $(i,j)$ 会出现在多少个点集中。

而这些点集需要满足的条件为：

1. $(i,j)$ 之间没有点，即点集中不存在点 $k$ 满足 $x_i<k<x_j$。

2. 为了保证 $i$ 向右动，$j$ 向左动。点集中不存在 $k$ 满足 $k<x_i$ 并且 $x_i-k\leq x_j-x_i$，同理也不应存在 $k>x_j$ 并且 $k-x_j\leq x_j-x_i$。

二分一下可选的最右和最左边的点就可以了。如果可以选的点有 $p$ 个，那么这个 $(i,j)$ 就会有 $2^p$ 的贡献。统计一下即可，时间复杂度 $O(n^2\log n)$。

[code](https://www.luogu.com.cn/record/156886027)

---

## 作者：Hisaishi_Kanade (赞：0)

你发现某种方案中每个最后留下的点可以说是相互独立的。

你钦定 $i,j$ 作为两个点要选，然后最后走到了一起会怎么样？

那么也就是所有 $x\in[1, x_i-(x_j-x_i)-1]$ 和 $x\in[x_j+(x_j-x_i),V]$ 随便选了。他们怎么选不影响 $i,j$ 走一起。他们产生的点在别的枚举算过了。

为什么是这个范围呢？因为如果选了 $i, j$ 之外的这个范围内的点，$i,j$ 就不是产生新点的那组了，和枚举不符啊。

如何统计？动态开点线段树。做完了。

```cpp
// LUOGU_RID: 124848885
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
#define mid (l+r>>1)
using namespace std;
int n, m, tot;
const int N=3005, M=1000000;
const int V=1e9, p=1e9+7;
int a[N], pw[N]; int i, j;
int tr[M];
int lc[M], rc[M];
inline void push_up(int id){tr[id]=tr[lc[id]]+tr[rc[id]];}
inline void add(int &id, int pos, int l, int r)
{
//	printf("%d %d %d %d\n", id, pos, l, r);
	if(pos<l || r<pos) return ;
	if(id==0) id=++tot;
	if(l==pos && r==pos) {++tr[id]; return ;}
	add(lc[id], pos, l, mid);
	add(rc[id], pos, mid+1, r);
	push_up(id);
	return ;
}
inline int query(int id, int ql, int qr, int l, int r)
{
	if(!id) return 0;
	if(r<ql || qr<l) return 0;
	if(ql<=l && r<=qr) return tr[id];
	return query(lc[id], ql, qr, l, mid)+query(rc[id], ql, qr, mid+1, r);
}
int main()
{
	scanf("%d", &n); rep(i, 1, n) scanf("%d", a+i);
	int rt=0; rep(i, 1, n) add(rt, a[i], 1, V);
//	puts("ok");
	pw[0]=1; rep(i, 1, n) pw[i]=(pw[i-1]<<1)%p;
	long long res=0; rep(i, 1, n) rep(j, i+1, n)
	{
//		printf("%d %d %d %d\n", i, j, query(1, 1, a[i]-(a[j]-a[i]-1), 1, V), query(1, a[j]+(a[j]-a[i]), V, 1, V));
		(res+=pw[query(1, 1, a[i]-(a[j]-a[i])-1, 1, V)+query(1, a[j]+(a[j]-a[i]), V, 1, V)])%=p;
	}
	printf("%lld\n", res);
	return 0;
}
```

---

