# Empty Graph

## 题目描述

— Do you have a wish?



 — I want people to stop gifting each other arrays.

O_o and Another Young Boy



An array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ fell down on you from the skies, along with a positive integer $ k \le n $ .

You can apply the following operation at most $ k $ times:

- Choose an index $ 1 \le i \le n $ and an integer $ 1 \le x \le 10^9 $ . Then do $ a_i := x $ (assign $ x $ to $ a_i $ ).

Then build a [complete](https://en.wikipedia.org/wiki/Complete_graph) undirected weighted graph with $ n $ vertices numbered with integers from $ 1 $ to $ n $ , where edge $ (l, r) $ ( $ 1 \le l < r \le n $ ) has weight $ \min(a_{l},a_{l+1},\ldots,a_{r}) $ .

You have to find the maximum possible diameter of the resulting graph after performing at most $ k $ operations.

The diameter of a graph is equal to $ \max\limits_{1 \le u < v \le n}{\operatorname{d}(u, v)} $ , where $ \operatorname{d}(u, v) $ is the length of the shortest path between vertex $ u $ and vertex $ v $ .

## 说明/提示

In the first test case, one of the optimal arrays is $ [2,4,5] $ .

The graph built on this array:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1712D/6f5937a14546fd0344ab2a7ad56768b75a98a230.png) $ \operatorname{d}(1, 2) = \operatorname{d}(1, 3) = 2 $ and $ \operatorname{d}(2, 3) = 4 $ , so the diameter is equal to $ \max(2,2,4) = 4 $ .

## 样例 #1

### 输入

```
6
3 1
2 4 1
3 2
1 9 84
3 1
10 2 6
3 2
179 17 1000000000
2 1
5 9
2 2
4 2```

### 输出

```
4
168
10
1000000000
9
1000000000```

# 题解

## 作者：Gokix (赞：14)

[CF1712D](https://www.luogu.com.cn/problem/CF1712D)

在题解区是清一色的二分，而唯一一篇贪心题解的讨论还略显复杂的情况下，我希望提供一种比较简洁的贪心思路。

**在复杂度允许的情况下，尽可能把东西丢给机子去做。 ——秋语橙**

------------

方便起见，以下记 $MD=10^9$.

贪心做法需要一些结论，我这里直接给出。前 2 个结论证明不再赘述，可参考[ 0htoAi 的题解](https://www.luogu.com.cn/blog/hanhan-zz/cf1712d-ti-xie)。

1. 两点间的最短路要么为 两点间直连的边长，要么为 两倍全局最小 $a$ 的值；

2. 图的直径必然可在相邻两点的最短路处取得；

3. 最优策略必然将前 $k-1$ 小的 $a$ 赋值成 $MD$。

以下给出结论 3 的证明：

对于 $k=1$ 的情况，显然成立。对于 $k>1$ 的情况，根据结论 1，每一次赋值点的选取要么是当前全局最大 $a$ 的相邻点（记为**操作 1**），要么为当前全局最小 $a$（记为**操作 2**）。注意到，一旦出现 2 个连续的 $MD$，我们就没有必要再执行**操作 1** 了，称为**盈满状态**。达到**盈满状态**后只需执行**操作 2**.无论怎样执行哪个操作，在第 $k$ 次赋值之前，必然存在至少一个 $a=MD$，这时全局最大 $a=MD$，必然执行一次**操作 1** 后就达到了**盈满状态**，之后执行的**操作 2** 无非就是被提前了。

所以，我们发现，在把前 $k-1$ 小的 $a$ 赋值成 $MD$ 后，所有问题就被转化到 $k=1$ 的问题上了。接下来考虑 $k=1$ 的解法：

先约定一些变量：$ans1$ 表示 $\max\limits_{i=1}^{n-1}(\min(a_i,a_{i+1}))$，$ans2$ 表示全局最小 $a$ 的两倍，$ans3$ 表示全局非严格次小 $a$ 的两倍。

当然你可以讨论，但是太麻烦了，而且极易出错。（我不知道有没有人用 $O(1)$ 的讨论过了，如果有的话请与我交流一下，我先表示我的敬意Orz)

我们来考虑一下前言中的那句话，发现现在甚至允许 $O(n)$ 的复杂度。

所以不妨枚举每一个 $a_i$，尝试把 $a_i$ 赋值成 $MD$ 后更新答案，再把 $a_i$ 变回来。

注意到赋值当前 $a_i$ 时，无非就是变了 $ans1$ 或是 $ans2$，接下来就这两种情况进行分别维护：

1. ans1:很暴力，因为改变 $a_i$ 只会影响 $\min(a_{i-1},a_i),\min(a_{i},a_{i+1})$，所以重新算一下这两个值，和原来全局 $ans1$ 取个 $\max$，作为当前的 $ans1$。

2. ans2:直接讨论，如果当前改变的是全局最小 $a$，那当前 $ans2=ans3$，否则不变。

把 $ans1$ 和 $ans2$ 取个 $\min$ 就是当前改变 $a_i$ 后的答案，更新 $ans$ 即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long rd(){char ch=getchar();long long x=0,f=1;while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
                        while('0'<=ch && ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void wr(long long x){if(x<0){putchar('-');x=-x;}if(x>9) wr(x/10);putchar(x%10+'0');}

const long long N=1e5+10,MD=1000000000;
long long t,n,k,a[N+10],ans,ans1,ans2,ans3,mx,mx1,mx2;
struct node{long long w,id;}b[N+10];
bool cmp(node u,node v){return u.w<v.w;}

int main(){
	long long i,j,u,v,x,y;
	t=rd();
	while(t--){
		n=rd();k=rd();
		for(i=1;i<=n;i++){
			a[i]=rd();
			b[i].w=a[i];b[i].id=i;
		}
		a[n+1]=0;//为下面(1)处理更简洁
		sort(b+1,b+n+1,cmp);
		for(i=1;i<k;i++) a[b[i].id]=MD;//把前k-1小的赋值成MD，转化为k=1问题
		ans=0;ans1=0;
		for(i=1;i<n;i++)//统计全局最大相邻更小a
			ans1=max(ans1,min(a[i],a[i+1]));
		ans2=MD;ans3=MD;
		for(i=1;i<=n;i++){//统计2倍全局最小a和2倍全局次小a
			if(a[i]<ans2){
				ans3=ans2; ans2=a[i];
			}
			else if(a[i]<ans3) ans3=a[i];
		}
		ans2*=2;ans3*=2;
		for(i=1;i<=n;i++){
			u=a[i];a[i]=MD;
			mx1=a[i-1];mx2=a[i+1];//改变相邻更小a的2种情况(1)
			mx=max(ans1,max(mx1,mx2));
			if(u*2==ans2) ans=max(ans,min(mx,ans3));//当前改的a等于全局最小a
			else ans=max(ans,min(mx,ans2));//当前改的a不是全局最小a
			a[i]=u;
		}
		wr(ans),putchar('\n');
	}
	return 0;
} 
```

---

## 作者：0htoAi (赞：6)

这题有个显然的二分做法，可是我考场没想到，所以直接贪心的。虽然考场上没有 AC，但是做法跟补题的时候的做法也差不多。

考虑原图中任意两个点 $(l,r)$，$1 \leq l < r \leq n$，它们之间的最短路只有可能是这两种情况之一：

* 从 $l$ 直接走到 $r$，长度为 $\min_{i=l}^{r}(a_i)$。

* 从 $l$ 走到全局最小点 $a_{\min}$，再从 $a_{\min}$ 走到 $r$，长度为 $2a_{\min}$。

其实可能出现 $a_{\min}=\min_{i=l}^{r}(a_i)$ 的情况，不过由于最短路是以上两种情况取较小值，所以可以忽略这个问题。

首先明确只要改变一个点的值，一定把其改成最大值，即 $10^9$。

然后分类讨论：

* $k=n$ 时：

	所有点都能染成 $10^9$，答案即为 $10^9$。  
    
* $n>k>1$ 时：
	
    将前 $k-1$ 小的点变成 $10^9$，此时对于任何一个点到其相邻点，把小的一个变成 $10^9$，由于前面至少将 $1$ 个点变成过 $10^9$，所以一定能找到这个 $10^9$，把其相邻点也变成 $10^9$。设第 $k$ 小的点为 $a_k$，则此时最长的两点最短路长度就为 $\min(10^9,2a_k)$。
    
    即可以得出结论：当 $k>1$ 时，答案不会小于 $\min(10^9,2a_k)$。
    
    然后考虑常规情况，根据最上面的，最短路只有可能是 $2$ 种情况之一，于是模拟。要使得全局最小点尽可能大，于是把前 $k$ 小的 $a$ 都变成 $10^9$，然后对于一对相邻的点 $(i,i+1)$，其最短路长度为 $\min(a_i,a_{i+1})$。找出最大的这个值，即找出 $\max_{i=1}^{n-1}(\min(a_i,a_{i+1}))$。综上可得全局最长的最短路为 $\max(\min(10^9,2a_k),\min(\max_{i=1}^{n-1}(\min(a_i,a_{i+1})),2a_{k+1}))$。其中 $a_k$ 和 $a_{k+1}$ 表示第 $k$ 和第 $k+1$ 小的 $a$，而 $a_i$ 表示原数组 $a$ 的第 $i$ 个值。
    
    为什么要选相邻的点？因为两点中间的 $\min$ 随着两点的距离单调不上升，两个点离得越远越不优。
    
* $k=1$ 时：
	
    第一种情况同 $n>k>1$ 时的第一段。但是由于 $k=1$，所以不保证找得到 $10^9$，找 $a_{\max}$ 就行了。即答案不会小于 $\min(a_{\max},2a_{\min})$。
    第二种情况同 $n>k>1$ 时的“常规情况”。
    则此时全局最长最短路为 $\max(\min(a_{\max},2a_{\min}),\min(\max_{i=1}^{n-1}(\min(a_i,a_{i+1})),2a_2))$。其中 $a_{\min}$ 表示 $a$ 的最小值， $a_2$ 表示 $a$ 的次小值，$a_{\max}$ 表示 $a$ 的最大值。注意 $\min(a_i,a_{i+1})$ 里的这个 $a$ 是把 $a_{\min}$ 变成 $10^9$ 之后来找的， $1<k<n$ 时同样也是先赋值再算。
    
如果题解看糊涂了可以看代码：

```
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+50;
int N,K;
struct Dot
{
	int Val,id;
}d[MAXN];
bool cmp(Dot a,Dot b)
{
	return a.Val<b.Val;
}
int a[MAXN];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&K);
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&d[i].Val);
			d[i].id=i;
			a[i]=d[i].Val;
		}
		if(K==N)
		{
			puts("1000000000");
			continue;
		}
		sort(d+1,d+N+1,cmp);
		int ans1,ans2,ans3,ans4;
		if(K==1)
		{
			ans1=d[1].Val*2;
			ans2=0;
			for(int i=1;i<=N;i++)
			{
				ans2=max(ans2,a[i]);
			}
			ans3=d[2].Val*2,ans4=0;
			a[d[1].id]=1000000000;
			for(int i=1;i<N;i++)
			{
				ans4=max(ans4,min(a[i],a[i+1]));
			}
			printf("%d\n",max(min(ans1,ans2),min(ans3,ans4)));
			continue;
		}
		ans1=min(1000000000,d[K+1].Val*2),ans2=0;
		for(int i=1;i<=K;i++)
		{
			a[d[i].id]=1000000000;
		}
		for(int i=1;i<N;i++)
		{
			ans2=max(ans2,min(a[i],a[i+1]));
		}
		ans1=min(ans1,ans2);
		printf("%d\n",max(min(1000000000,d[K].Val*2),min(ans1,ans2)));
	}
}
```


---

## 作者：Dregen_Yor (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1712D)。

[博客食用效果更佳](https://www.cnblogs.com/Dregen-Yor/p/16588729.html)。

# 题目大意

- 给定一个序列 $ a_1,a_2,\ldots,a_n $。

- 你可以进行最多 $k$ 次操作，每次操作选定一个数字 $i$（$ 1 \le i \le n $）和一个整数 $x$（$1 \le x \le 10^9 $），使 $a_i=x$。

- 建立一张有 $n$ 个点的图，对每个点从 $1$ 到 $n$ 进行编号，其中点 $l$ 和点 $r$ 之间连有一条边权为 $\min(a_{l},a_{l+1},\ldots,a_{r})$ 的边。

- 找出两点之间的最短路径的最大值。

# 思路

首先看到求最短路径的最大值，最小值最大，妥妥的二分答案。

根据题目中两个点之间连边的边权的性质，不难推断出最大值一定出现在相邻的两个点之间，不相邻的两个点之间可能存在更小的值，即使是有更大的值也不会成为边权。

两个点之间的最短路要么是两个点之间的边直达，要么是找一个最小的点，以最小的点作为中转站在两个点之间折跃，即点 $l$ 和点 $r$ 之间的最短路为 $\min( \min(1,n)\times2,\min(l,r))$。

在二分枚举答案时，假设当前枚举的答案为 $pos$ ，可以考虑设一个**前缀和**和一个**后缀和**，统计 $a_i\times2\le pos$ 的 $i$ 的数量，因为每个 $a_i\times2\le pos$ 的 $i$ 即是我们需要修改的点。

我们从 $1$ 到 $n-1$ 枚举，统计最小的 $pre_{i-1}+sub_{i+2}+ord(a_i<pos)+ord(a_{i+1}<pos)$，判断是否成立即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, k, a[100010], pre[100010], sub[100010];

bool check(int pos) {
	for (int i = 1; i <= n; i++) {

		pre[i] = pre[i - 1] + (int)((a[i] << 1) < pos);
	}

	for (int i = n; i; --i) {

		sub[i] = sub[i + 1] + (int)((a[i] << 1) < pos);
	}

	int minx = 0x7fffffff;

	for (int i = 1; i < n; i++) {

		minx = min(minx, pre[i - 1] + sub[i + 2] + (int)(a[i] < pos) + (int)(a[i + 1] < pos));;
	}

	return minx <= k;
}

signed main() {
	scanf("%lld", &t);

	while (t--) {
		scanf("%lld%lld", &n, &k);
		memset(pre, 0, sizeof(pre));
		memset(sub, 0, sizeof(sub));

		for (int i = 1; i <= n; i++) {

			scanf("%lld", &a[i]);
		}

		int l = 0, r = 1e9, ans = 0;

		while (l <= r) {
			int mid = l + r >> 1;

			if (check(mid)) {
				l = mid + 1;
				ans = mid;
			} else {
				r = mid - 1;
			}
		}

		printf("%lld\n", ans);
	}

	return 0;
}

```


---

## 作者：cachejtt (赞：4)

## 题意
给你一个序列，你可以修改任意次，每次把序列中任意 $k$ 个数修改为一个你自己选择的 $x$（$x\le 10^9$）。

构造一个完全图，若一条边连接 $(i,j)$，则边权为$\min(a_i,a_{i+1},\dots,a_j)$。请让图的直径最大。

图的直径定义为：任意两点间最短路的最大值。

## 思路

我们约定:

- 用 $\operatorname{d}(u,v)$ 表示 $u$ 与 $v$ 的最短路。
- 用 $\operatorname{e}(u,v)$ 表示连接 $u$ 与 $v$ 的边的边权。
- 用 $diameter$ 表示图的直径。
- 用 $minn$ 表示 $\min(a_1,a_2,\dots,a_n)$。

考虑以下事实。

显然对于这题，两点间最短路，最多经过两条边。
则

$$\operatorname{d}(u,v)=\min(\operatorname{e}(u,v),2\times minn)$$

这是因为，两点间最短路，或直接到达，或走两条边。若直接到达，则值为 

$$\operatorname{e}(u,v)=\min(a_u,\dots,a_v)$$

若走两条边，则一定是**走两次**边权最小的那种边，也就是说，假设 $i_{min}$ 为 $a_i$ 最小值的下标，则最短路大小为 

$$\operatorname{e}(u,i_{min})+\operatorname{e}(i_{min},v)=2\times a_{i_{min}}$$

故得上式。

再看有关 $\operatorname{e}(u,v)$ 的性质。

由于 $\operatorname{e}(u,v)=\min(a_u,\dots,a_v)$，故选择任意一个 $p\ge v$，有 $\operatorname{e}(u,v)\ge \operatorname{e}(u,p)$

故

$$\begin{aligned}
\operatorname{e}(u,v) & = \min(\operatorname{e}(u,u+1),,\dots,\operatorname{e}(v-1,v)) \\
     & = \min\limits_{u\le i\le v-1}(\operatorname{e}(a_i,a_{i+1}))
\end{aligned}$$

可得

$$\begin{aligned}
diameter & = \max({d(u,v)}) \\
     & = \max{(\min(\operatorname{e}(u,v),2\times minn)}) \\
     & = \min(2\times minn,\max(\operatorname{e}(u,v))) \\
     & = \min(2\times minn,\max(\min\limits_{1\le i\le n-1}(a_i,a_{i+1})))
\end{aligned}$$

## 做法
我们已经推导过，

$$diameter= \min(2\times minn,\max(\min\limits_{1\le i\le n-1}(a_i,a_{i+1})))$$

接下来只需二分答案。

设当前答案为 $ans$，则将所有 $\le \dfrac{ans}{2}$ 的点赋值成 $10^9$。为什么是 $\dfrac{ans}{2}$ 呢？因为这条边若作为 $minn$ 的话，会被走两次，也就是上面式子中的 $2\times minn$。

现在记录一下我们修改了几次，设为 $cnt$。

- 若 $cnt>k$，显然不可能
- 若 $cnt=k$，只需计算当前直径是否可行。若 $diameter\le ans$ 则可行。
- 若 $cnt<k$，若 $k>1$，则一定可以有更多修改空间，即一定可以；若 $k=1$，否则因为只能修改一个，只需寻找 $a_i$ 最大值并与 $ans$ 比较即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
using namespace std;
int t=1,n,k,a[100005],aa[100005],l,r,mid;
int calc(){
  int m1=min(aa[1],aa[2]);
  rep(i,1,n-1){
    m1=max(m1,min(aa[i],aa[i+1]));
  }
  int m2=aa[1];
  rep(i,1,n){
    m2=min(m2,aa[i]);
  }
  return min(m1,2*m2);
}
bool check(int ans){
  int sum=0;
  rep(i,1,n)aa[i]=a[i];
  rep(i,1,n){
    if(aa[i]<(ans+1)/2)sum++,aa[i]=1e9;
  }
  if(sum>k)return false;
  else if(sum==k){
    int d=calc();
    if(d>=ans)return true;
    else return false;
  }
  else{
    if(k==1){
      int mm=aa[1];
      rep(i,1,n)mm=max(mm,aa[i]);
      if(mm>=ans)return true;
      else return false;
    }
    else return true;
  }
}
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>k;
    rep(i,1,n)cin>>a[i];
  	l=1;
    r=1e9;
    while(l<r){
      mid=(l+r)>>1;
      if(check(mid))l=mid+1;
      else r=mid;
    }
    while(check(l) && l<n)l++;
    while(check(l)==0 && l>1)l--;
    cout<<l<<endl;
  }
  return 0;
}
```

---

## 作者：Jr_Zlw (赞：4)

# 二分

首先有一个比较明显的性质，直径最多经过两条边。

设全局最小值为  $m$。考虑从任意一点  $u$  出发，经过全局最小值所在的点，然后再到任意点，花费是  $2\times m$  的。而任意边权  $\geq m$，走两条后的权值必定  $\geq 2\times m$。所以最多就是花费  $2\times m$  走两条边，不然只走一条。

然后考虑  $l,r$  相距越远，它们之间的那条边越小，所以考虑最远点的时候只需考虑相邻两点就行了。

而相邻两点  $i-1,i$  的最短距离为  $\min\{a_{i-1},a_{i},2\times m\}$。

所以直径  $D=\max\limits_{i\in[2,n]}\{\min\{a_{i-1},a_{i},2\times m\}\}$。

考虑这是一个最大值套最小值这种形式，上二分答案。

设当前判断使用  $\leq k$  次操作是否能使答案为  $mid$。

首先如果  $2\times m<mid$,那么无论如何都可以通过全局最小走到任意点，所以先把  $2\times a_i< mid$  的位置全部置为  $10^9$。

然后现在只需考虑  $\max\limits_{i\in [2,n]} \{\min\{a_{i-1},a_i\}\}$  了。

发现只需要有一个  $\min\{a_{i-1},a_{i}\}\geq mid$  即可。

所以如果已经满足无需操作，否则如果存在  $a_i\geq mid$，改掉与他相邻的其中一个即可，否则需要改两个。

判一下操作次数是否  $\leq k$  返回即可。

复杂度  $O(n\log W)$，$W$  是值域。

代码：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define rep(a,b,c) for(int c(a);c<=(b);++c)
#define drep(a,b,c) for(int c(a);c>=(b);--c)
#define grep(b,c) for(int c(head[b]);c;c=nxt[c])
#define Clear(a,n) memset(a,0,((n)+3)*sizeof(a[0]))
typedef long long LL;
typedef std::pair<int,int> pii;
using namespace std;
inline int read()
{
	int res=0;char ch=getchar();bool flag=0;while(ch<'0'||ch>'9')flag^=(ch=='-'),ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();return flag ? -res : res ;
}
inline void rd(bool &x){char c;do c=getchar();while(c!='0'&&c!='1');x=c=='1';}
inline void print(LL x){if(x>9)print(x/10);putchar(x%10+'0');}
//template<typename T> inline T min(const T&x,const T&y){return x<y?x:y;}
//template<typename T> inline T max(const T&x,const T&y){return x<y?y:x;}
template<typename T> inline T Swap(T&x,T&y){T tmp=x;x=y;y=tmp;}
template<typename T> inline T Abs(T&x){return x<0?-x:x;}
const int N=1e5+10,INF=1e9;int a[N],n,K,A[N];
inline bool check(int lm)
{
	
	memcpy(A,a,(n+3)*sizeof(int));
	int cc=0;rep(1,n,i){if(2*A[i]<lm)++cc,A[i]=INF;}
	bool f1=0,f2=0;rep(2,n,i)if(min(A[i],A[i-1])>=lm){f1=1;break;}
	rep(1,n,i)if(A[i]>=lm){f2=1;break;}
	if(!f1)++cc;if(!f2)++cc;
	return cc<=K;
}
inline void Solve()
{
	n=read();K=read();rep(1,n,i)a[i]=read();
	int l=1,r=1e9,res=1e9,mid;
	while(l<=r)check(mid=(l+r)>>1)?l=mid+1,res=mid:r=mid-1;
	printf("%d\n",res);
}

signed main()
{
	int T=read();
	while(T--)Solve();
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：3)

### 1 视频题解

![](bilibili:BV1DS4y1s7yL)

### 2 思路

我们可以发现，$dis(u,v)$ 是以下 $3$ 种之一：

+ $\min(a_u,...,a_v)$

+ $\min(a_1,...,a_u)+\min(a_1,...,a_v)$

+ $\min(a_u,...,a_n)+\min(a_v,...,a_n)$

我们可以发现，如果是第 $2$ 种可能的话，$\min(a_1,...,a_u)+\min(a_1,...,a_v)<\min(a_u,...,a_v)$ ~~这不废话吗~~，由此我们发现，$\min(a_1,...,a_u)=\min(a_1,...,a_v)=\min(a_1,...,a_{u-1})$。

同理，如果是第 $3$ 种可能，$\min(a_u,...,a_n)=\min(a_v,...,a_n)=\min(a_{v+1},...,a_n)$

并且我们可以发现，直径一定是相邻的两个点的最短路。

我们可以设 $u,v$ 其中 $v-u>1$。可以发现，前 $2$ 种最短路可能中，相邻的确实更优：

$\min(a_{u},...,a_{v})\le\min(a_{u},a_{u+1})$

$\min(a_1,...,a_{u-1})\times2=\min(a_1,...,a_{u-1})\times2$ ~~这不废话吗。~~

但是第 $3$ 种可能有不一样的情况：

$\min(a_{v+1},...,a_n)\times2\ge\min(a_{u+2},...,a_n)\times2$

可以发现，当这个不等式不能取等时，$\min(a_{u},...,a_{v})$ 会更小。

我们可以考虑二分，看看可不可能直径为 $x$。

如果这样，我们枚举 $i(1\le i<n)$，看看 $dis(i,i+1)\ge x$ 是否可能成立。

可以发现，我们要把 $a_1,...,a_{i-1}$ 和 $a_{i+2},...,a_{n}$ 之中所有满足 $a_j\times2<x$ 的全部填上，$a_i$ 和 $a_{i+1}$ 也要检查。

如果操作次数足以全部填上，那么就可以以 $x$ 为直径。如果检查一遍都不可以，那就是不可以。

最后输出答案即可。

具体细节看代码。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 100000
#define inf (1ll<<52)
int t;
int n;
int k;
long long a[max_n+2];
long long b[max_n+2];
long long cntl[max_n+2];
long long cntr[max_n+2];
long long ans;
bool check(long long x){
	cntl[0]=0;
	for(int i=1;i<=n;++i){
		if(a[i]*2<x)cntl[i]=cntl[i-1]+1;
		else cntl[i]=cntl[i-1];
	}
	cntr[n+1]=0;
	for(int i=n;i>=1;--i){
		if(a[i]*2<x)cntr[i]=cntr[i+1]+1;
		else cntr[i]=cntr[i+1];
	}
	for(int i=1;i<n;++i){
		if(cntl[i-1]+cntr[i+2]+(a[i]<x)+(a[i+1]<x)<=k)return true;
	}
	return false;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1712D_1.in","r",stdin);
	freopen("CF1712D_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i)scanf("%lld",a+i);
		if(k>=n){
			printf("1000000000\n");
			continue;
		}
		ans=0;
		for(long long l=0,r=1000000000,mid;l<=r;){
			mid=(l+r)>>1;
			if(check(mid)){
				l=mid+1;
				ans=mid;
			}
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/83727169)

By **dengziyue**

---

## 作者：EnofTaiPeople (赞：3)

### 题意：
给定 $n,k,a_i,1\le i\le n$。
有一个图，点 $l$ 和点 $r$ 之间有一条边权为 $\min\limits_{i=l}^ra_i$ 的边，记 $d(u,v)$ 为点 $u$ 到点 $v$ 的最短路径长度，你可以将 $k$ 个 $a_i$ 修改为 $[1,10^9]$ 之间的任意正整数，最大化 $\max\limits_{u\ne v}d(u,v)$，输出最大值。

本题多测，先输入一行一个数 $t\le10^4$，接下来每组数据，先输入两个数 $n,k$，$1\le k\le n\le10^5$，下一行 $n$ 个数，表示 $a_i$。

输出 $t$ 行，表示每一组数据的答案。

$\sum n\le10^5,1\le a_i\le 10^9$.

### 题解：
这是一篇一堆特判的题解。

1. 首先特判 $n=k$ 的情况，直接输出 $10^9$；
2. 再特判 $n=2$ 的情况，因为 $n\ne k$，所以 $k=1$，将较小值改为 $10^9$，输出较大值。

设答案为 $ans$。

考虑 $n>2$ 时，设 $a_i$ 为最小值，对于所有 $x,y,x\ne i,y\ne i,x\ne y$，都有 $d(x,y)\le 2a_i$，而若 $x=i$ 或 $y=i$，都有 $d(x,y)=a_i$，于是 $ans\le 2a_i$。

发现答案具有单调性，可以二分答案 $md$，将所有 $2a_i<md$ 的 $a_i$ 全部改成 $10^9$，接下来，我们还需要找到一个 $i<n$ 使 $md\le\min\{a_i,a_{i+1}\}$，扫一遍记下最少需要修改几个数字（最多为 $2$）。

好像不需要二分，也不需要特判 $n=k$，我太菜了。

贴上不到 1k 的 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
using ll=long long;
ll A,B,C;
int n,k,T,p[N],ml,mr,a[N],b[N];
bitset<N>vs;
inline bool ck(int P){
	int x,d=0,R=2;
	for(x=1;x<=n;++x)
		if(p[x]<<1<P)p[x]=1e9,++d;
	for(x=1;x<n;++x)
		R=min(R,(p[x]<P)+(p[x+1]<P));
	for(x=1;x<=n;++x)p[x]=b[x];
	return d+R<=k;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int i,j,x,y,z,l,r,md;
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(i=1;i<=n;++i)cin>>p[i],b[i]=p[i],a[i]=i;
		if(n==k){
			printf("%d\n",1000000000);continue;
		}else if(n==2){
			printf("%d\n",max(p[1],p[2]));continue;
		}
		sort(a+1,a+n+1,[&](int x,int y){return b[x]<b[y];});
		l=0,r=1e9,A=0;
		while(l<=r){
			md=l+r>>1;
			if(ck(md))A=md,l=md+1;
			else r=md-1;
		}printf("%lld\n",A);
	}
	return 0;
}
```

---

## 作者：Symbolize (赞：2)

# 思路
二份答案。

显然我们可以二分直径的最大值，在判断是否合法。

我们很容易发现，对于 $l$ 到 $r$ 的最短路径要么是直接到，要么是过一个中转点，那显然如果过中转点，那中转点定是 $\min\limits_{l \le i \le r}a_i$。又因我们的中转点连接两边，所以路径权值要翻倍，那我们就推出了 $l,r$ 的最短路径通式：$\min(\min\limits_{1 \le i \le n},\min\limits_{l \le i \le r}a_i \times 2)$。

那我们就可以开始写判断函数了！

我们的判断原理是改变的值不能大于 $k$。我们传入 $x$，表示假设的直径。那因为我们前面推出的通式，所以如果 $\min\limits_{l \le i \le r}a_i \times 2 < x$，那么这个点必须修改。所以我们可以用一个前缀和 $sum1$ 与后缀和 $sum2$ 记录截止 $i$ 要更改的数的数量。

最后从 $1$ 到 $n-1$ 循环。单独判断枚举的 $i$ 是否满足 $a_i < x$ 或 $a_{i+1} < x$，满足一个让一个变量 $sum_i \gets 1$ 两个就 $sum_i \gets 2$ 最小修改次数就是 $\min\limits_{sum1_{i-1}+sum2_{i+2}+sum_i}$。

最后判断最小修改次数是否小于 $k$ 次即可。

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e5+10;
using namespace std;
int t,n,k,a[N],sum1[N],sum2[N];
bool check(int x)
{
	//虽说中间断开一段有点烦，但有前后缀就不怕了 
	rep1(i,1,n)//从前到后需要改的条数 
	{
		sum1[i]=sum1[i-1];//附上前一个的值 
		if((a[i]<<1)<x) ++sum1[i];//判断目前这个 
	}
	rep2(i,n,1)
	{
		sum2[i]=sum2[i+1];//附上前一个的值 
		if((a[i]<<1)<x) ++sum2[i];//判断目前这个 
	}
	int minn=LONG_LONG_MAX;
	rep1(i,1,n-1) 
	{
		int sum=sum1[i-1]+sum2[i+2];//除a[i]和a[i+1]外需要改的 
		if(a[i]<x) ++sum;//判断 
		if(a[i+1]<x) ++sum;//判断 
		minn=min(minn,sum);//最小的 
	}
	if(minn<=k) return 1;//是否在限制内 
	return 0;
}
void getans()
{
	memset(sum1,0,sizeof sum1);//记得清空 
	memset(sum2,0,sizeof sum2);//因为模考时没清空挂了 
	cin>>n>>k;
	rep1(i,1,n) cin>>a[i];
	int l=0,r=1e9;//二分直径的值
	while(l<=r)//二分 
	{
		int mid=l+r>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	cout<<l-1<<endl;//l=mid+1所以要-1 
	return;
}
signed main()
{
// 	freopen("D.in","r",stdin);
// 	freopen("D.out","w",stdout); 
	cin>>t;
	while(t--) getans();//循环要答案 
	return 0;//收场 
}
/*
思路：
吐血了呀！
想了半天贪心，结果贪心快推出结论时才发现这两点之间的到达方式要么直接过去，要么过其他两条路（多了还不是要重复）
那还不如数学推一推试试
如果要中转，我们每次找的一定是最小的点作为中转
显然l到r的最短路径就是min(min(l,r)a[i],(min(1,n)a[i])>>1)
好像又有点像二分啊
那假设我们的直径最大值为x
那每个a[i]<<1 <= x的点就必须修改，因为它会使l到r的路径小于x
因此，除了a[i]<->a[i+1]这条路以外，其余都得判断。可以用前后缀和来标记，减小复杂度和工作量。
单独判断一下a[i]与a[i+1]是否小于x就完工了。 

样例：
6
3 1
2 4 1
3 2
1 9 84
3 1
10 2 6
3 2
179 17 1000000000
2 1
5 9
2 2
4 2
*/
```

---

## 作者：sunkuangzheng (赞：1)

$\textbf{1.1 Describtion}$

给定长度为 $n$ 的序列 $a$ 和一张无向完全图，边 $u,v(u \le v)$ 的权值是 $\min\limits_{i=u}^v\{a_i\}$。你可以进行 $k$ 次操作，让 $a_i \gets x,x \in [1,10^9]$ 且 $x$ 的值由你选定，问操作完后图的直径的最大值。图的直径即最大的两点之间的最短距离。

$1 \le n \le 10^5$。

$\textbf{1.2 Hints}$

- $\textbf{1.2.1 Hint 1}$

设 $d(u,v)$ 表示 $u$ 到 $v$ 的最短路，尝试确定 $d(u,v)$ 的上界。

- $\textbf{1.2.2 Hint 2}$

尝试证明 $d(u,v) = \min(\min\limits_{i=u}^v\{a_i\},2\min\limits_{i=1}^n\{a_i\})$。

- $\textbf{1.2.3 Hint 3}$

根据 $\text{Hint 2}$ 中的结论，为了让 $d(u,v)$ 最大，选取的 $u,v$ 应该满足什么关系？

- $\textbf{1.2.4 Hint 4}$

二分答案。

$\textbf{1.3 Solution}$

我们先对 $\text{Hint 2}$ 中的结论做简要证明。

设 $1 \sim n$ 中 $a_i$ 取最小值的地方是 $i = p$，那么由于完全图，显然存在路径 $u \to p \to v$，路径长度是 $2a_p$，又因为可以直接走边 $u,v$，所以$d(u,v) = \min(\min\limits_{i=u}^v\{a_i\},2\min\limits_{i=1}^n\{a_i\})$。

$2\min\limits_{i=1}^n\{a_i\}$ 不变的情况下，我们希望 $d(u,v)$ 最大，就等价于让 $\min\limits_{i=u}^v\{a_i\}$ 最大，也显然子区间最短，即 $v = u + 1$ 时最优。

我们二分答案 $x$，贪心的检验答案。很容易发现每次都让 $a_i \gets 10^9$ 一定不劣。首先如果不能在 $k$ 次操作内让最小值的 $2$ 倍 $\ge x$，肯定不合法。设 $k_1$ 是已经操作过的次数，$k_2$ 是剩余的次数，那么如果 $k_2 \ge 2$ 肯定合法。如果存在一个 $i \in [1,n-1]$ 满足 $\min(a_i,a_{i+1}) \ge x$，或者 $\max(a_i,a_{i+1}) \ge x$ 并且 $k_2 \ge 1$，也是合法情况。

上面的检验是线性的，所以时间复杂度 $\mathcal O(n \log V)$。

**【代码】**

```cpp
/**
 *    author: sunkuangzheng
 *    created: 03.10.2023 09:41:34
**/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int t,n,k,a[maxn],b[maxn],c[maxn],d[maxn];
bool cmp(int x,int y){return a[x] < a[y];}
bool ck(int x){
    int lk = 0;
    for(int i = 1;i <= n;i ++) a[i] = b[i];
    for(int i = 1;i <= n;i ++) if(a[i] * 2 < x) lk ++,a[i] = 1e9;
    if(lk > k) return 0;if(k - lk >= 2) return 1;
    for(int i = 1;i < n;i ++) if(min(a[i],a[i+1]) >= x) return 1;
    else if(max(a[i],a[i+1]) >= x && lk != k) return 1;
    return 0;
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t --){
        cin >> n >> k;
        for(int i = 1;i <= n;i ++) cin >> a[i],b[i] = a[i],c[i] = i;
        int l = 1,r = 1e9;
        while(l <= r){
            int mid = (l + r) / 2;
            if(ck(mid)) l = mid + 1; else r = mid - 1;
        }cout << l - 1 << "\n";
    }
}
```



---

## 作者：WaterSun (赞：1)

# 思路

因为我们枚举的直径是具备单调性的，所以可以使用二分答案。

我们可以想一个事情，如果有两个点 $u$ 和 $v$，它们两点之间的最短路径要么是直接从 $u \to v$；要么是经过一个中转点 $t$，即：$u \to t \to v$。

然后，我们可以发现一个显然的规律，就是 $t$ 一定是区间 $a$ 中最小值的下标。

知道了这些，我们便可以得出一个结论：任意两点 $u,v$ 的最短路径为 $\min(\min_{l \leq i \leq r}a_i,2 \times \min_{1 \leq i \leq n}a_i)$。

接着，我们的 $\operatorname{check}$ 函数就很好想了。

我们根据上面的公式，可以推断出对于一个 $i(l \leq i \leq r)$，如果 $2 \times a_i < x$ 那么这个点是一定要修改的。

我们这些数是可以用前缀和维护的，于是我们可以用两个数组 $s1,s2$ 分别维护 $1 \sim i$ 和 $i \sim n$ 区间中的修改的数量。

随后，我们枚举一下 $1 \sim n - 1$，判断一下 $a_i < x$ 和 $a_{i + 1} < x$。

最终我们的修改次数就是 $\min(s1_{i - 1} + s2_{i + 2} + (a_i < x) + (a_{i + 1} < x))$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10,inf = 1e9 + 10;
int T,n,k;
int arr[N],s1[N],s2[N];

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

inline bool check(int x){
	int res = inf;
	for (re int i = 1;i <= n;i++) s1[i] = s1[i - 1] + ((arr[i] << 1) < x);//前缀和 
	for (re int i = n;i;i--) s2[i] = s2[i + 1] + ((arr[i] << 1) < x);
	for (re int i = 1;i < n;i++){//枚举 1 ~ n - 1 
		int cnt = s1[i - 1] + s2[i + 2];//记录当前答案 
		if (arr[i] < x) cnt++;
		if (arr[i + 1] < x) cnt++;
		res = min(res,cnt);//取 min 
	}
	return (res <= k);//判断是否合法 
}

int main(){
	T = read();
	while (T--){
		int l = 0,r = 1e9;
		n = read();
		k = read();
		s2[n + 1] = 0;//记得把这一位清零 
		for (re int i = 1;i <= n;i++) arr[i] = read();
		while (l <= r){//二分板子 
			int mid = l + r >> 1;
			if (check(mid)) l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n",l - 1);//记得减 1 
	}
	return 0;
}
```

---

## 作者：syzf2222 (赞：0)

vp 碰到这题真的是稍微有点蚌埠住。

---

首先，一个序列的直径有上界 $2Mn$，在 $m>1$ 时我们至少可以做到 $2m_{th}$，我们想要超越就必须把前 $m$ 全都填满。

容易注意到序列直径只在相邻间取，所以我们对相邻都为 $10^9$，有一个不为 $10^9$ 和都不为 $10^9$ 分类讨论：

- $a_i,a_{i+1}=10^9$，即 $a_i,a_{i+1}$ 都可能处于前 $m$ 个，则答案为 $2(m+1)_{th}$

- 两个中存在一个前 $m$，不妨设 $a_i=10^9$，则答案为 $\min\{2(m+1)_{th},a_{i+1}\}$

- 两个都不是前 $m$，则答案为 $\min\{2(m+1)_{th},a_i,a_{i+1}\}$

特别的，当 $m=1$ 时，若不取最小值，我们可以做到 $\min\{2Mn,Mx\}$，直接把 $10^9$ 放在最大值旁边即可。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
const int inf=1e9;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int T,n,m,a[maxn],b[maxn];
int main(){
	T=read();
	for(int o=1;o<=T;o++){
		n=read(),m=read();int res=0;
		for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i];
		if(n==m){printf("%d\n",inf);continue;}
		sort(b+1,b+1+n);int ans=0;b[n+1]=inf+1;
		for(int i=1;i<n;i++)
			if(a[i]<=b[m]){
				if(a[i+1]<b[m])ans=2*b[m+1];
				else if(a[i+1]==b[m]){
					if(a[i]<b[m]||(m>1&&b[m]==b[m-1]))ans=2*b[m+1];
					else ans=max(ans,b[m]);
				}else ans=max(ans,min(2*b[m+1],a[i+1]));
			}else{
				if(a[i+1]<=b[m])ans=max(ans,min(2*b[m+1],a[i]));
				else ans=max(ans,min(2*b[m+1],min(a[i],a[i+1])));
			}
		if(m>1)ans=max(ans,2*b[m]);
		if(m==1)ans=max(ans,min(b[n],2*b[1]));
		printf("%d\n",min(inf,ans));
	}
	return 0;
}
```

深深地感到自己的弱小/ll

---

## 作者：Foofish (赞：0)

## 题意

现在有一串数列，你可以进行 $k$ 次操作，使得中间 $a_i$ 变为任意一个数，数列中每一个数都是一个节点，节点之间有边，$a_l$ 和 $a_r$ 之间的边权为 $\text{min}(a_l,a_{l+1},...,a_r)$，定义直径为 $l,r$ 之间的最短距离。求出所有直径中的最大值。

## 思路

很显然是一个很复杂的贪心，如果从这个角度深入的话，要讨论很多东西，比较难处理，这里给出一个较为简单的二分答案法。

首先一个显而易见的贪心，我改，肯定改成可以改成的最大值 ${10}^9$。并且答案肯定不会超过 ${10}^9$ 这也方便了我们进行二分。

对于一个 $T$ 他作为答案，我如何知道这个行不行？

首先，如果其中的最小值的两倍小于他，那么肯定不行。因为我任意两个东西之间的直径，我都可以通过最小的数来**中转**使得**所有**直径 $<T$，所以我要贪心地改最小值，改到不需要改了为止。

这样肯定远远不够，因为我要找到一个满足这个的直径。

我这只是满足了中转不会让答案变得小于 $T$。我们不难想到，如果我改完之后有相邻两个数之间的距离 $>T$，那么是不是说明我找到了一个合法的解？

那么我们就考虑什么时候我能满足相邻两个数之间的距离 $\ge T$，如果相邻两个数都 $\ge T$，那么很好，我们一次修改都不需要操作。如果不是，如果只有一个 $\ge T$，那么我们要改一个，如果都 $<T$ 那么我们肯定要改两个，然后找到一个出现过的要改的最小的，这肯定是最优的策略了。

```cpp
#include <bits/stdc++.h>
template <typename T>inline void read(T& t){t=0; register char ch=getchar(); register int fflag=1;while(!('0'<=ch&&ch<='9')) {if(ch=='-') fflag=-1;ch=getchar();}while(('0'<=ch&&ch<='9')){t=t*10+ch-'0'; ch=getchar();} t*=fflag;}
template <typename T,typename... Args> inline void read(T& t, Args&... args) {read(t);read(args...);}
using namespace std;
const int N=1e5+10, inf=0x3f3f3f3f;

int T=1,n,a[N],k,c[N];

struct Info{
    int val,pos;
    bool operator < (const Info &info) const{
        return val<info.val;
    }
}b[N];

bool check(int K){
    c[0]=0;c[n+1]=0;
    for(int i=1;i<=n;++i) c[i]=a[i];
    int r=1;
    while(2*b[r].val<K&&r<=n) ++r;
    --r;
    for(int i=1;i<=r;++i) c[b[i].pos]=1e9;
    int flag=inf;
    for(int i=1;i<n;++i) flag=min(flag,(c[i]<K)+(c[i+1]<K));
    return (r+flag)<=k;
}

int main(){
    read(T);
    while(T--){
        int maxx=0;
        read(n,k);
        for(int i=1;i<=n;++i)
            read(a[i]),maxx=max(maxx,a[i]),b[i].val=a[i],b[i].pos=i;
        sort(b+1,b+n+1);
        int l=1,r=1e9;
        while(l<r){
            int mid=l+r+1>>1;
            //cout<<l<<' '<<r<<endl;
            if(check(mid)) l=mid;
            else r=mid-1;
        }
        cout<<l<<endl;
    }
    return 0;
}
```

---

## 作者：Into_qwq (赞：0)

### [$\to \text{CF1712D Empty Graph}\leftarrow$](https://www.luogu.com.cn/problem/CF1712D)

#### 思路：

先考虑 $x\to y\ (x<y)$ 的最短距离 $d(x,y)$ 怎么更新。

( 我们假定 $mn(l,r)$ 表示 $\min\{a_l,a_{l+1},..., a_r\}$ )

显然 $d(x,y)$ 由三部分取最小值组成：

- $x$ 直接到 $y$，这部分的距离是 $mn(x,y)$

- $x$ 先到 $z$ 再到 $y$，且满足 $z<x$，这部分的距离是 $mn(z,x)+mn(z,y)$

- $x$ 先到 $z$ 再到 $y$，且满足 $z>y$，这部分的距离是 $mn(x,z)+mn(y,z)$

显然，第二部分当 $z=1$ 时有最小值 $mn(1,x)+mn(1,y)$，第三部分当 $z=n$ 时有最小值 $mn(x,n)+mn(y,n)$。

然后可以发现答案满足单调性，于是二分答案 $mid$，并且修改数组 $a$ 下标 $[x, y]$ 中值小于 $mid$ 的，这样对于第二部分和第三部分，由于 $mn(x,y)\ge mid$，实际上我们只用使 $2\cdot mn(1,x-1)\ge mid$ 且 $2\cdot mn(y+1,n)\ge mid$。

也就是我们需要修改 $a$ 数组中下标在 $[1,x-1]$ 或 $[y+1,n]$ 之间且小于等于  $\lceil \frac{mid}{2} \rceil$ 的数，然后判断总修改次数是否大于 $k$ 次即可。

我们可以维护一棵主席树来计算需要修改的数，这样做的时间复杂度是 $O(n^2\log n\log A)$ 的，显然需要一些优化。

大胆猜测，选 $x=y-1$ 是最优的，并证明一下：

如果选 $x,y$ 的话，必然需要使得 $a_{1}\sim a_{x - 1}$ 和 $a_{y + 1}$ 都要大于等于 $\lceil\frac{mid}{2}\rceil$ 且 $a_x\sim a_y$ 均大于等于 $mid$。

显然 $x=y-1$ 时最优，此时可以让大于等于 $mid$ 的 $a_i$ 尽量少，这样限制条件就更少，也就使得修改的次数更少。

这样的时间复杂度是 $O(n\log n\log \max\{a\})$ 的，能够通过此题。

**code**：

```c++
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
const int inf=1e9;

int n,k;
int a[N],rt[N];

namespace CT{
	struct node{
		int v,l,r;
	}t[N*31];
	int cnt;
	inline void insert(int &p,int pre,int l,int r,int x,int k){
		p=++cnt;
		t[p]=t[pre];
		++t[p].v;
		if(l==r) return;
		int mid=l+r>>1;
		if(x<=mid) insert(t[p].l,t[pre].l,l,mid,x,k);
		else insert(t[p].r,t[pre].r,mid+1,r,x,k);
	}
	inline int query(int q,int p,int l,int r,int L,int R){
		if(L<=l&&r<=R) return t[p].v-t[q].v;
		int mid=l+r>>1,res=0;
		if(L<=mid) res+=query(t[q].l,t[p].l,l,mid,L,R);
		if(mid<R) res+=query(t[q].r,t[p].r,mid+1,r,L,R);
		return res;
	}
}

inline bool check(int x,int i){
    int now=0;
    if(a[i]<x) ++now;
    if(a[i-1]<x) ++now;
    int num=x/2+(x%2);
    if(now>k) return 0;
    if(num==1) return 1;
    now+=CT::query(rt[0],rt[i-2],1,inf,1,num-1);
    now+=CT::query(rt[i],rt[n],1,inf,1,num-1);
    //cout<<x<<" "<<i<<" "<<num<<" "<<now<<endl;
    return now<=k;
}

signed main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		int ans=0;
        rt[0]=0;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			CT::insert(rt[i],rt[i-1],1,inf,a[i],1);
		}
		for(int i=2;i<=n;++i){
			int l=1,r=1e9+1;
			while(l<r-1){
				int mid=l+r>>1;
				if(check(mid,i)) l=mid;
				else r=mid;
			}
			ans=max(ans,l);
		}
		cout<<ans<<endl;
	}
}
```

当然还有时间复杂度更加优秀的做法，具体可以去看官方题解。

---

