# Naughty Stone Piles

## 题目描述

There are $ n $ piles of stones of sizes $ a_{1},a_{2},...,a_{n} $ lying on the table in front of you.

During one move you can take one pile and add it to the other. As you add pile $ i $ to pile $ j $ , the size of pile $ j $ increases by the current size of pile $ i $ , and pile $ i $ stops existing. The cost of the adding operation equals the size of the added pile.

Your task is to determine the minimum cost at which you can gather all stones in one pile.

To add some challenge, the stone piles built up conspiracy and decided that each pile will let you add to it not more than $ k $ times (after that it can only be added to another pile).

Moreover, the piles decided to puzzle you completely and told you $ q $ variants (not necessarily distinct) of what $ k $ might equal.

Your task is to find the minimum cost for each of $ q $ variants.

## 说明/提示

In the first sample one way to get the optimal answer goes like this: we add in turns the $ 4 $ -th and the $ 5 $ -th piles to the $ 2 $ -nd one; then we add the $ 1 $ -st pile to the $ 3 $ -rd one; we add the $ 2 $ -nd pile to the $ 3 $ -rd one. The first two operations cost $ 1 $ each; the third one costs $ 2 $ , the fourth one costs $ 5 $ (the size of the $ 2 $ -nd pile after the first two operations is not $ 3 $ , it already is $ 5 $ ).

In the second sample you can add the $ 2 $ -nd pile to the $ 3 $ -rd one (the operations costs $ 3 $ ); then the $ 1 $ -st one to the $ 3 $ -th one (the cost is $ 2 $ ); then the $ 5 $ -th one to the $ 4 $ -th one (the costs is $ 1 $ ); and at last, the $ 4 $ -th one to the $ 3 $ -rd one (the cost is $ 2 $ ).

## 样例 #1

### 输入

```
5
2 3 4 1 1
2
2 3
```

### 输出

```
9 8 ```

# 题解

## 作者：Feyn (赞：3)

[link](https://www.luogu.com.cn/problem/CF226B)

假如不限制每个点的合并次数，显然最优解应该是把所有点往最大点上合并。于是我们找到了这道题的一个结论，即一个点对答案的贡献次数是它以及它所在集合被合并的次数。而合并的过程又非常像一个树形结构（儿子们向父亲合并，然后被父亲带着去合并祖先），于是我们可以转化一下题意：有一些点，希望用这些点组成一棵树，限制每个点儿子数量的最大值，希望最小化所有点的点权乘深度之和（毕竟深度就是它被合并，也就是贡献的次数）。

这棵树是完全（套用完全二叉树的概念）的时候显然是最优的，然后考虑如何安排点权，由于每个点的贡献只和深度有关，而且一个点往上走只会单纯的导致一个点落下来，所以问题就可以贪心的来做了，即把权值大的点尽量往上安排即可。

实现上其实没必要建树，把数组排序之后考虑有哪些点在同一层即可。复杂度是 $O(N\log N)$。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
const int N=100010;
using namespace std;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}
inline int min(int s1,int s2){return s1<s2?s1:s2;}

int m,n,a[N];
inline bool cmp(int s1,int s2){return s1>s2;}

int ans[N];
void solve(int len){
	int l=2,now=len,op=1;
	for(;l<=m;l=l+now,op++,now*=len)ans[len]+=(a[min(l+now-1,m)]-a[l-1])*op;
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);for(int i=1;i<=m;i++)read(a[i]);
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++)a[i]+=a[i-1];
	for(int i=1;i<=m;i++)solve(i);
	read(n);int s1;
	while(n--){read(s1);if(s1>m)s1=m;printf("%I64d\n",ans[s1]);}
	
	return 0;
}
```

---

## 作者：ncwzdlsd (赞：2)

为什么现在的题解都要建树啊，不懂诶，哭哭。

所以就有了这样一篇浅显易懂的题解 qwq。

初见这道题，想过用 DP 搞一搞，但是后来发现，可以用贪心诶！要求在对于每一对石子有一定的合并次数限制下，合并若干堆石子的最小花费。

考虑对于每一组石子 的大小 $a_i$，在满足移动次数不超过 $k$ 次的前提下，我们应该尽量让石子堆大小小小的移动次数更多，让石子堆大小大的移动次数更少；还有一个比较好想的贪心策略，对于其中的一个石子堆，我们应该尽量让当前状态下，石子堆大小比较大的尽量不移动，而是让石子堆大小更小的石子堆向大石子堆移动。

模拟一下移动的过程，我们先从一种最简单的情况入手：$k=1$，显然每一堆石子都只能合并一次，于是显然我们只需要让第一堆石子不断按序向后合并，这样我们就可以得到一个最优解了。

对于 $k$ 次移动，我们先对石子堆排序，由于前面提到的贪心策略，肯定是要让所有石子堆都合并到最后一大堆最优。我们考虑先把排好序的第 $n-1$ 堆到第 $n-k$ 堆进行进行移动，因为越往后移动的石子堆合并所需要的移动次数显然更多，所以让大小大的先移动，可以知道每一堆需要移动 $1$ 次，第 $n-k-1$ 堆到第 $n-k^2-1$ 堆移动 $2$ 次，不断进行这个过程直到合并成一堆即可。为什么？考虑对于石子堆，它可以合并的次数增加了，那么每一次被合并的堆数显然也在增加。试一试 $k=2$ 和 $k=3$ 的情况，发现 $k=2$ 时每一次可以合并两堆，即两堆、四堆、八堆……；$k=3$ 同理。以此类推，对于 $k$ 的情况，每次合并产生的贡献就是 $k$，对于某一堆石子上面我们可以合并 $k$ 个，而这 $k$ 个又可以由 $k$ 次合并推来。

对于计算每一次合并的代价，我们可以考虑用前缀和维护。为了防止超时，我们可以先预处理一下 $k=1$ 的解。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1e5+5;
int a[maxn],sum[maxn];

signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n;cin>>n;
	int ans1=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	sum[0]=0;
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i];
		if(i!=n) ans1+=sum[i];
	}
	int q;cin>>q;
	while(q--)
	{
		int k;cin>>k;
		if(k==1) {cout<<ans1<<' ';continue;}
		int ans=0,kk=k,nn=n-1,cnt=1;
		while(nn>=kk)
		{
			ans+=(sum[nn]-sum[nn-kk])*cnt;
			nn-=kk,kk*=k,cnt++;
		}
		ans+=sum[nn]*cnt;
		cout<<ans<<' ';
	}
	return 0;
}
```

[通过记录](https://codeforces.com/contest/226/submission/197060491)

---

## 作者：TH911 (赞：1)

> [洛谷 RMJ 226B 题目传送门](https://www.luogu.com.cn/problem/CF226B)
>
> 双倍经验：[CF 226B 传送门](https://codeforces.com/problemset/problem/226/B) [CF 227D 传送门](https://codeforces.com/problemset/problem/227/D)
>
> ~~为什么这么近就重题了。~~

# 题意分析

如果不考虑合并 $k$ 次的限制，就是一个普通的合并石子问题，思路即将小堆合并到大堆上，这样小堆的计算次数会更多，大堆的计算次数会更少，进而使得总代价最小。

考虑加入 $k$ 次限制之后总代价的形式：

* 存在 **$1$ 个** $a_i$ 满足 $a_i$ 不在总代价中。
* 存在 **$k$ 个** $a_i$ 满足 $a_i$ 被计算了 $1$ 次。
* 存在 **$k^2$ 个** $a_i$ 满足 $a_i$ 被计算了 $2$ 次。
* ……
* 存在 $n$ 个 $a_i$ 满足 $a_i$ 被计算了 $\left\lceil\log_k n\right\rceil$ 次。

具体可以参考此图：

![](https://cdn.luogu.com.cn/upload/image_hosting/chb8vn9i.png)

我们可以以 $a_i$ 为节点建一棵树（代码中不需要，仅仅为了便于分析），那么一个节点与父节点的连边代表合并到父节点上。

则可以解释上文的结论，根节点的 $x$ 级子节点有 $k^x$ 个，而这些子节点的答案被统计了 $x$ 次（合并一次就会被统计一次）。

则一个节点对总代价的贡献为其值乘深度，这也是建树的做法。

然而，我们可以考虑令较大的 $a_i$ 被统计的次数尽可能少，直接排序后贪心统计即可。

同时又考虑到 $k$ 可能相同，可以预处理出 $k=1,2,3,\cdots,n$ 的情况的答案 $ans_k$，询问时直接输出即可。注意当 $k>n$ 时，答案同 $k=n$ 的情况。

时间复杂度：$\mathcal O(n\log n)$。

# AC 代码

```cpp
//#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<string>
#include<vector>
#include<cmath>
#include<ctime>
#include<deque>
#include<queue>
#include<stack>
#include<list>
using namespace std;
//#define int long long
typedef long long ll;
constexpr const int N=1e5;
int n,a[N+1];
ll sum[N+1],ans[N+1]; 
int main(){
	/*freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);*/
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];
	}
	for(int k=1;k<=n;k++){
		//p=n-1:a[n]不统计 
		int p=n-1,pl=1;
		ll kk=k;//kk=k^pl
		while(p>=kk){
			ans[k]+=(sum[p]-sum[p-kk])*pl;//这一层的kk个元素统计答案
			p-=kk;kk*=k;
			pl++;
		}
		ans[k]+=sum[p]*pl;
	} 
	int q;
	scanf("%d",&q);
	while(q--){
		int k;
		scanf("%d",&k);
		k=min(k,n);
		printf("%lld ",ans[k]);
	}putchar(10);
	
	/*fclose(stdin);
	fclose(stdout);*/
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[更好的阅读体验](https://doittomorrow.xyz/post/cf226b-naughty-stone-piles-ti-jie/)
## 题目大意
就是普通的石子合并，但是添加了限制条件：每一堆石子合并的次数不能超过 $k$ 次。

## 思路
对于普通的石子合并，将除了最大的石子外的所有的石子全部合并到最大的石子上肯定是最优的。

> 证明：  
> 假设石子的重量为 $a_1,a_2,a_3,\cdots ,a_{n+1},a_n$，且满足对于 $i\in [1,n-1]$，$a_i\le a_{i+1}$。假设我们要将 $x,y,z$ 三堆石子合并，那么有以下几种可能出现合并的代价：
> - $a_x+a_y$，代表将 $x$ 和 $y$ 依次合并到 $z$。
>- $a_x+a_z$，代表将 $x$ 和 $z$ 依次合并到 $y$。
>- $a_y+a_z$，代表将 $y$ 和 $z$ 依次合并到 $z$。

> 因为 $a_x\le a_y\le a_z$，所以 $a_x+a_y\le a_x+a_z,a_y+a_z$。可见，在全部依次合并的情况下将除了最大的石子外的所有的石子全部合并到最大的石子上肯定是最优的。  
对于现将一堆石子合并到另外一堆再进行合并肯定是更劣的，因为同样的两项的和依然会存在，而且因为一堆被合并了两次，所以还还要多重复一次。

我们可以将这个情况抽象成为一棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/80v59fag.png)

将 $x$ 合并到 $y$ 就相于从 $x$ 到 $y$ 连一条边，这张图的代价为每个点的点权乘以这个点的度 $-1$（即合并次数）的和。因为题目有限制每一堆石子合并的次数不能超过 $k$ 次，所以这个题目求的就是每个节点至多有 $k$ 个孩子的树的代价的最小值。显然，我们可以将 $a$ 数组排序，贪心的从小到大尽可能将每一层都放满。

对于样例首先将输入排序得到 $4,3,2,1,1$。

对于 $k=3$ 时，我们得到了这样的一棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/vn6z4ke8.png)

其代价为 $4\times 0+2\times 1+3\times 1+1\times 2+1\times 3=9$。

通过观察可以得到第 $i$ 层有 $k^{i-1}$ 个节点，所以在实际的计算中我们并不需要真正将树建出来，而是直接统计就可以了。

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,a[N],m,k;
map<int,int> mp;
bool cmp(int a,int b){
	return a>b;
}
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*a;
		}
		b>>=1;
		a=a*a;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		a[i]+=a[i-1];
	}
	cin>>m;
	while(m--){
		int ans=0;
		cin>>k;
		if(mp[k]){
			cout<<mp[k]<<' ';
			continue;
		}
		int i=1,cnt;
		for(i=1,cnt=0;i<=n;i+=ksm(k,cnt+1),cnt++){
			ans+=(a[i]-a[i-ksm(k,cnt)])*cnt;
		}
		i-=ksm(k,cnt);
		ans+=(a[n]-a[i])*(cnt);
		mp[k]=ans;
		cout<<ans<<' ';
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

合并石子题，如果没有位置限制，通常考虑建树，这题也是如此。

但是和经典石子合并不同的是这里合并的代价是较小的一个石子，所以建树不能是两个石子堆连向新堆，而是小堆连向大堆，然后这题就和原来的合并石子一样了——总代价为每个树节点权值乘上层数。

所以首先我们希望把大的堆尽可能放在前面，所以考虑对原数组从大到小排序，然后我们希望整体层数较小，所以我们会尽可能安排所有的小层数，所以我们一定会尽可能连成满 $k$ 叉树，然后最后树的形态就是：

- 第一层是最大值。
- 第二层是排名 $2\sim k+1$ 的数字。
- 第二层是排名 $k+2\sim k^2+k+1$ 的数字。
- 如此类推。

知道了规律之后就没必要建树了，对于每一层乘上的数字是一样的，所以我们直接暴力预处理 $1\sim n$ 的所有询问，一次算一整层，时间复杂度显然是调和级数的 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=1e5+5;
//const LL M;
//const LL mod;
//const LF eps;
//const LL P;
LL n,q,x,a[N],sum[N],ans[N];
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+n+1,[](LL a,LL b){return a>b;});
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(LL j=1,t=0,k=1;j<=n;j+=k,t++,k*=i)
		{
			ans[i]+=(sum[min(n,j+k-1ll)]-sum[j-1])*t;
		}
	}
	scanf("%lld",&q);
	while(q--)
	{
		scanf("%lld",&x);
		if(x>n)x=n;
		printf("%lld ",ans[x]);
	}
	return 0;
}
//RP++
```

---

