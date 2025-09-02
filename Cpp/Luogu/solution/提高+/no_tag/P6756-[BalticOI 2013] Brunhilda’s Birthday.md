# [BalticOI 2013] Brunhilda’s Birthday

## 题目描述

有一个整数 $n$ 以及一个长度为 $m$ 的素数表 $p$。

您可以进行任意多次操作，每一次操作时，您选择一个素数 $p_i$，这会使得 $n\to \lfloor \frac{n}{p_i}\rfloor\times p_i$。

您的目标是求出使得 $n$ 变为 $0$ 的最小操作数，如果不可能变为 $0$，请输出 `oo`。

为了增加难度，您需要回答 $Q$ 组 $n$。 

## 说明/提示

#### 数据范围及限制
- 对于 $20$ 分的数据，保证 $m,n,Q\le 10^4$。
- 对于另外 $20$ 分的数据，保证 $Q=1$。
- 对于 $100\%$ 的数据，保证 $1\le m,Q\le 10^5$，$2\le p_i\le 10^7$ 且 $p_i$ 为素数，$1\le n\le 10^7$。

#### 说明
本题译自 [Baltic Olympiad in Informatics 2013](https://boi.cses.fi/tasks.php) [Day 2](https://boi.cses.fi/files/boi2013_day2.pdf) T1 Brunhilda’s Birthday。

因为译题人找不到合适的设置，所以本题满分 $110$ 分。

## 样例 #1

### 输入

```
2 2
2 3
5
6```

### 输出

```
3
oo```

# 题解

## 作者：HYXLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/P6756)

## 思考

定义数字 $x$ 的最小操作次数为 $f(x)$ 。

通过显然的观察可以得到，当 $x$ 递增时，$f(x)$ 也是递增的，且若某个数 $x$ 无解，则大于 $x$ 的数都是无解。

显然想到二分，对于每种答案，求出是这个答案的 $a$ 的区间是什么，查询时直接二分出 $x$ 属于哪个区间即可。

不难发现 $f(x) \leq x$，所以可以直接使用结构体存储。

如何二分呢？

显然可以记录一个 $lst$ 表示上一种答案的区间的右端点是哪个，然后二分这种答案的右端点 $r$ 。接着枚举每个素数 $p$ ，把操作 $p$ 后的数字求出来，若存在某个素数使得求出来的数小于等于 $lst$ ，则这个 $r$ 是合法的，反之则不合法。

注意刚开始的时候先将数组 $p$ 去重。

时间复杂度作者太菜了不会证明，希望有人能证明一下。





### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=1e5+5,M=1e7+5;
struct node{int l,r;}ans[N*100];
int n,q,pr[N];
inline bool check(int x,int lst){
	int mn=x;
	for(R int i=1;i<=n;++i){
		mn=min(mn,x-x%pr[i]);
		if(mn<lst)return 1;
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(R int i=1;i<=n;++i){
		cin>>pr[i];
	}
	sort(pr+1,pr+n+1);
	n=unique(pr+1,pr+n+1)-pr-1;
	int tot=0;
	for(int l=1,res,r;l<=M-5;l=res+1){
		int ls=l;r=M-5;res=-1;
		while(ls<=r){
			int mid=ls+r>>1;
			if(check(mid,l))ls=mid+1,res=mid;
			else r=mid-1;
		}
		if(res==-1)break;
		ans[++tot]={l,res};
	}
	while(q--){
		int x;cin>>x;
		if(x==0)cout<<0<<'\n';
		else{
			int l=1,r=tot;
			if(ans[r].r<x){
				cout<<"oo\n";continue;
			}
			int res=tot;
			while(l<=r){
				int mid=l+r+1>>1;
				if(ans[mid].l<=x)res=mid,l=mid+1;
				else r=mid-1;
			}
			cout<<res<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：9)

显然，我们每次尽可能使得操作后最小，那么我们有个这样的做法：

我们记录每个 $n$ 开桶，对于每个 $p_i$ 我们让所有 $[kp_i,(k+1)p_i-1]$ 向 $kp_i$ 取 $\min$，可以变成一个前缀的形式，然后打个标在 $(k+1)p_i-1$，最后一个后缀更新就可以了。

最后我们得到了最优的操作，最后再处理一下 $b_i=b_{a_i}+1$。做完了。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum=1;
long long m,q,a[10000005],b[10000005];
int main(){
	for(int i=1;i<=1e7;i++)a[i]=0x3f3f3f3f3f3fll;
	cin>>m>>q;
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		if(sum<1e7)sum*=x;
		for(int j=1;1ll*j*x-1<=1e7;j++){
			a[j*x-1]=min(a[j*x-1],1ll*(j-1)*x);
			
		}
		a[(int)1e7]=min(a[(int)1e7],(long long)((int)1e7/x*x));
	}
	for(int i=(int)1e7-1;i>=0;i--)a[i]=min(a[i+1],a[i]);
	for(int i=1;i<=1e7;i++){
		b[i]=b[a[i]]+1;
	}
	while(q--){
		int x;
		cin>>x;
		if(x>=sum){
			cout<<"oo\n";
			continue;
		}
		cout<<b[x]<<"\n";
	}
	return 0;
}

```

---

## 作者：Larryyu (赞：6)

## _Description_

给定 $m$ 个质数 $p_i$，以及 $q$ 组询问。

每组询问给定一个数 $n$，你可以进行若干次操作，每次操作形如从 $m$ 个质数中选择一个 $p_i$，并使 $\lfloor\frac{n}{p_i}\rfloor\times p_i\to n$。

问最少需要多少次操作才能使 $n$ 变为 $0$，若无解，输出 ```oo```。

## _Solution_

这是一道最优化问题，先想想有没有贪心策略。

对于一个数 $x$，并不是取最大或最小的 $p_i$ 最优，很容易举例得出。

好像并没有什么很好的策略，那就上动态规划。

设 $dp_i$ 表示 $i$ 的最小操作次数，依题意得出转移式：$dp_i=\min\limits_{j=1}^m dp_{\lfloor\frac{i}{p_j}\rfloor\times p_j}+1$。

这个式子是 $O(nm)$ 的，无法通过。

我们考虑将刷表改为填表，得出转移式 $\forall p_j\mid i,dp_{[i,i+p_j-1]}=dp_i+1$。

对于同一个 $i$，$p_j$ 越大它能覆盖到的范围就越广，所以只要用最大的 $p_j$ 去转移。

发现这个式子是单调递增的，浅浅证一下：

> 若 $dp_i\ne dp_{i+1}$，说明它们是由不同的地方转移过来的，设其分别为 $dp_j,dp_k$。
>
> 若 $k<i$，那么 $dp_k$ 转移的覆盖区间包含 $dp_i$，所以 $dp_i\ne dp_{i+1}$ 是因为 $dp_j$ 转移会更优秀，即 $dp_i<dp_{i+1}$。
>
> 若 $k=i$，那么 $dp_{i+1}=dp_i+1$。
>
> 证毕。

所以我们可以设一个阈值 $maxn$。

若当前转移 $dp_i$，但 $i+p_j-1\le maxn$，那就没有转移的必要，因为肯定不优于从前面转移，否则转移到 $dp_{[maxn+1,i+p_j-1]}$ 并更新 $i+p_j-1\to maxn$，转移复杂度是 $O(n)$ 的。

整个做法的复杂度瓶颈在于对 $[1,n]$ 中每一个数求出它的质因数中在 $m$ 个质数里并且最大的数。

线性筛 $O(n\log n)$ 和埃氏筛 $O(n\log\log n)$ 均可通过。

下面给出埃氏筛的实现。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,q;
int a[100010];
int val[10000100],dp[10000100];
void init(){
	for(int i=1;i<=m;i++){
		for(int j=0;j<=1e7;j+=a[i]){
			val[j]=a[i];
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>m>>q;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+m);
	m=unique(a+1,a+1+m)-a-1;
	init();
	dp[1]=1e9;
	for(int i=2;i<=1e7;i++){
		dp[i]=1e9;
	}
	int maxn=0;
	val[0]=a[m],dp[0]=0;
	for(int i=0;i<=1e7;i++){
		if(maxn>1e7) break;
		if(!val[i]||dp[i]==1e9) continue;
		if(i+val[i]-1>maxn){
			for(int j=maxn+1;j<=i+val[i]-1;j++){
				if(j>1e7) break;
				dp[j]=dp[i]+1;
			}
			maxn=i+val[i]-1;
		}
	}
	while(q--){
		int x;
		cin>>x;
		if(dp[x]==1e9) cout<<"oo\n";
		else cout<<dp[x]<<'\n';
	}
	return 0;
}
```

---

## 作者：serene_analysis (赞：6)

和另一篇题解不同的做法，跑得更快一些。

从 Loj 上学到的。

或许逆向思维比较强的选手做这个题会更容易想出这个做法？

---

题意已经很明确了。

因为询问的值域并不大，考虑在值域上做文章。先猜一个结论：$\forall x \lt y,ans_x \leq ans_y$。

证明：考虑从 $0$ 往后扩展。首先设最大素数为 $mp$，则 $0$ 到 $mp-1$ 的数答案均为 $1$，并且这个 $1$ 肯定为最优解。

对于每个素数 $p_i$，在已经被扩展到的数中找到最大的 $p_i$ 的倍数 $q$，用 $q$ 扩展 $q+1$ 到 $q+p_i-1$。注意这里需要等一轮全部照完后统一扩展，否则可能出现被非最优解扩展的情况。那么一轮扩展下来，后面的数答案肯定大于等于前面的数。如此一直扩展到值域，那么结论得证。

用这个证明，还可以得到另一个结论：相同答案的 $n$ 肯定处于同一个连续段。

那么这个问题就简单了，按照证明过程做即可。具体实现时可以用第二个结论，只记录答案变化的分界点，询问时二分在分界点中找。有些细节可以见代码。

无解判断还是直接判大于所有数的最小公倍数 $M$。

设值域为 $lim$，时间复杂度可以简单认为是 $\Theta(\dfrac{\min(lim,M)}{mp} \times n+n+q \log lim)$，因为给出的是素数表，所以 $\dfrac{n}{mp} \leq 1$，前面一堆也就不大于值域。于是就可以跑得飞快。截止发题解时是最优解，并甩开第二名很远。

```cpp
#include<algorithm>
#include<cstdio>
typedef long long ll;
const int maxn=1e5+5;
const int maxa=1e7+5;
int n,q;
int list[maxn];
int lcm;
int apr[maxa],acnt;
signed main(){
	scanf("%d%d",&n,&q);
	int mx=0;
	for(int i=1;i<=n;i++){
		scanf("%d",list+i);
		mx=std::max(mx,list[i]);
	}
	lcm=1;
//	std::sort(list+1,list+n+1);
//	n=std::unique(list+1,list+n+1)-list-1;
	for(int i=1;i<=n&&lcm>0;i++)lcm*=list[i];
	if(lcm<0||lcm>maxa)lcm=maxa;
	apr[++acnt]=0,apr[++acnt]=mx;
	while(apr[acnt]<lcm){
		int nx=apr[acnt];
		for(int i=1;i<=n;i++){
			if(!(apr[acnt]%list[i]))continue;
			nx=std::max(nx,(apr[acnt]/list[i]+1)*list[i]);
		}
		apr[++acnt]=nx;
	}
//	printf("acnt=%d\n",acnt);
	for(int i=1;i<=q;i++){
		int x;
		scanf("%d",&x);
		if(x>=lcm)printf("oo\n");
		else printf("%d\n",std::upper_bound(apr+1,apr+acnt+1,x)-apr-1);
	}
	return 0;
}
/*
8 1
2 3 5 7 11 13 17 19
9000000
ans=762868
*/
```

感谢您的阅读！

---

## 作者：yyyyxh (赞：5)

## P6756 LOJ2685 Brunhilda’s Birthday 题解
询问很多，所以可以考虑预处理出每个数的答案，即dp

转移方程：$f_i=\min\{f_{i\ -\ (i\mod p_j)}\}+1$

按照这个式子暴力转移，会有32pts的好成绩

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=10000003,Q=100003;
const int INF=0x3f3f3f3f;
int f[N],p[N];
int n[Q],m,q,mx;
int main(){
	ios::sync_with_stdio(false);
	cin>>m>>q;
	for (int i=1; i<=m; i++) cin>>p[i];
	for (int i=1; i<=q; i++) {cin>>n[i];if (n[i]>mx) mx=n[i];}
	f[0]=0;
	for (int i=1; i<=mx; i++){
		f[i]=INF;
		for (int j=1; j<=m; j++){
			if (i%p[j]==0) continue;
			if (f[i-i%p[j]]+1<f[i]) f[i]=f[i-i%p[j]]+1;
		}
	}
	for (int i=1; i<=q; i++){
		if (f[n[i]]>=INF) cout<<"oo"<<endl;
		else cout<<f[n[i]]<<endl;
	}
	return 0;
}
```
写完暴力，我发现 $f_i$ 是一个不降序列，仔细想了想，这是因为如果存在 $f_u$ 转移到 $f_v(u<v)$ 使得 $f_v<f_{v-1}$ 话，当前素数应不整除 $f_v$（否则转移无意义），这意味着$f_{v-1}$同样也可被$f_u$转移而来，假设矛盾。

第二个发现是，$f_u$可以转移到的必是 $f_{u+1}$~$f_{u+k-1}$ 的一段区间，其中$k|u$，那么每个$f_i$可以转移到的最大右边界就是给出的素数集中整除 $i$ 的最大数。

预处理过后对于每一个 $f_i$ ，可以用一个指针贪心地维护当前转移右边界包含 $x$ 的最小 $i$ （使得 $f_i$ 最小）进行转移。

优化代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=10000003,Q=100003;
const int INF=0x3f3f3f3f;
int f[N],p[N],r[N];
int n[Q],m,q,mx,cur;
int main(){
	ios::sync_with_stdio(false);
	cin>>m>>q;
	for (int i=1; i<=m; i++) cin>>p[i];
	for (int i=1; i<=q; i++) {cin>>n[i];if (n[i]>mx) mx=n[i];}
	sort(p+1,p+m+1);
	for (int i=1; i<=m; i++){
		for (int j=0; p[i]*j<=mx; j++){
			r[p[i]*j]=p[i];
		}
	}
//	for (int i=0; i<=mx; i++) cout<<r[i]<<" "; cout<<endl;
	f[0]=0; cur=0;
	for (int i=1; i<=mx; i++){
		f[i]=INF;
		while (cur+r[cur]<=i&&cur<i) cur++;
		if (cur!=i) f[i]=f[cur]+1;
	}
	for (int i=1; i<=q; i++){
		if (f[n[i]]>=INF) cout<<"oo"<<endl;
		else cout<<f[n[i]]<<endl;
	}
	return 0;
}
``` 
复杂度瓶颈在于预处理右边界上，暴力转移看起来很慢，似乎是 $O(nm)$ ，但交上去却可以AC，想了想，这是因为还有个条件没用：这些数都是素数！如果每个数都很小的话暴力枚举很容易超时，但素数比较稀疏，稍微计算一下，$10^7$ 以内的素数个数在 $6.6 \times 10^5$ 左右，本题最坏复杂度在 $2.5 \times 10^8$ 以下，勉强能过。

---

## 作者：冷却心 (赞：4)

可发现题目对 $n$ 的操作即为：选择一个质数 $p$，并使 $n \leftarrow n - n\bmod p$。那我们设后面得到的数为 $m$，则这个操作的逆向就是 $m+k\rightarrow n$，其中 $k<p$，而 $p$ 是 $m$ 的一个质因子且 $p$ 属于题目给定的集合。

我们记录一个数组 $d_i$ 表示数 $i$ 的最小操作次数，考虑正推转移。首先显然如果质数集合最大的质数为 $p_0$，则小于 $p_0$ 的正整数都只需要操作 $1$ 次，因为除一遍就好了。然后考虑已知 $d_i$ 怎么推下一个 $d_j$。我们定义 $g_i$ 表示 $i$ 最大的属于题目给定集合的质因子，则有如下转移：

$$\forall j < i + g_i，d_j \leftarrow \min(d_j,d_i+1).$$

这样就可以得到一个总时间复杂度是 $\sum g_i$ 的转移，其中预处理 $g_i$ 的时间复杂度可以吗，枚举集合中的质数然后枚举其倍数，时间复杂度是 $O(\sum g_i+m \ln K)$，$K$ 是值域。

这样时间复杂度的瓶颈在 $\sum g_i$ 上，我们对其进行优化。

首先我们可以发现，我们更新到的范围是一个前缀的区间，因此我们维护一个右端点 $r$ 表示之前最远更新到了哪个数，每次更新从 $r+1$ 开始更新就好了，这样右端点至多会移动 $K$ 次，即转移一共只有 $K$ 次，因此时间复杂度是 $O(m\ln K+K)$，$K=10^7$ 轻松跑过。

证明这样一定不劣：

> 结论：$\forall i\in \mathbb{N},d_i \leq d_{i+1}.$
>
> 证明：根据上面的转移，分讨一下：
> 1. 如果 $d_{i+1}$ 由 $d_i$ 转移而来：显然 $d_{i+1}=d_i+1>d_i$。
> 2. 如果 $d_{i+1}$ 由 $d_j$ 转移而来，其中 $j<i$：显然 $d_{i+1}=d_j +1$，而因为 $i+1<j+g_j$，所以也肯定满足 $i<j+g_j$，则 $d_i$ 也可能由 $d_j$ 转移，有 $d_i\leq d_j + 1\leq d_{i +1}$。

根据这个结论，显然就可以得到对于任意 $i<j$，$d_i\leq d_j$。

然后我们回到本来的问题，设当前对于 $i$ 开始更新，之前最远更新到 $r$，则我们要证明对于之前更新过的 $j$， 即满足 $i<j\leq r$ 的 $j$，不用再次更新，即 $d_j \leq d_i + 1$，显然 $d_j$ 由一个小于 $i$ 的 $k$ 更新了，则 $d_j=d_k + 1$，因为 $k<i$ 则 $d_k\leq d_i$，所以 $d_j \leq d_i + 1$。证毕。

---

## 作者：huangrenheluogu (赞：2)

考虑从 $0\to 10^7$ 转移，$f_x$ 表示 $x$ 到 $0$ 的最小步数。显然这个 $f$ 是满足单调性的，$f_x\ge f_{x-1}$，用归纳法简单证明。

于是，只用考虑 $f_{kp_i}$ 对后面的贡献。对于一个 $x=kp_i$，则其贡献的范围是 $[x,x+p_i)$，取满足 $p_i|x$ 的最大 $p_i$ 即可，这个可以在开始维护。由于素数筛倍数是不超过 $\mathcal{O}(V\log\log V)$ 的，其中 $V=10^7$，可以通过。

在维护 dp 转移的时候，可以使用单调队列做到 $\mathcal{O}(V)$，总复杂度是 $\mathcal{O}(V\log\log V)$。

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 1e7 + 5, maxn = 1e7;
int m, Q, n, f[N], a[N], p[N], h, t;
pii tmp, q[N];
inline void chkmax(int &x, int y){
    if(x < y) x = y;
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);   
    scanf("%d%d", &m, &Q);
    for(int i = 1; i <= m; i++){
        scanf("%d", &a[i]);
        for(int j = 0; j <= maxn; j += a[i]){
            chkmax(p[j], a[i]);
        }
    }
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    h = 1;
    for(int i = 0; i <= maxn; i++){
        while(h <= t && q[h].se < i) h++;
        if(h <= t) f[i] = q[h].fi + 1;
        if(f[i] == inf || !p[i]) continue ;
        tmp = {f[i], i + p[i] - 1};
        while(h <= t && q[t].fi == tmp.fi && q[t].se < tmp.se){
            t--;
        }
        if(h > t || q[t].se < tmp.se) q[++t] = tmp;
    }
    while(Q--){
        scanf("%d", &n);
        if(f[n] == inf) puts("oo");
        else printf("%d\n", f[n]);
    }
    return 0;
}
```

---

## 作者：_Flame_ (赞：1)

### $\text{solution}$

显然 $dp_i$ 为 $i$ 的答案的话，$dp_{i}=\min\limits_{j=1}^{m} dp_{i-(i\bmod p_j)}+1$。

发现一些性质：$dp_i$ 是不降的，且答案相同的成连续段。

打表进一步发现，若 $k\mid i$，则 $dp_{i}$ 可以转移到 $dp_{i+1}$ 到 $dp_{i+k-1}$ 的区间，预处理出每个 $i$ 整除它的素数集中的最大数，这个数即为 $k$ 的右边界。所以对于每一个 $dp_{i}$ 贪心的找到最小的 $x$ 使得 $x$ 的转移的有边界包含 $i$ 转移即可。

具体的，维护指针指向最小的能转移到 $a_i$，即为最小的右边界大于 $i$ 的 $dp_j$，转移时加一就行。

---

## 作者：_7thRC_CB_CRP_ (赞：0)

这是考场水题。。。

我们假设有一个 $p,i,f_i$，分别为某一个质数，这个质数的一个倍数，和它所对应的 dp 值，那么我们就可以让他这样转移：

$$f_{[i+1,i+p-1]}=\max(f_{[i+1,i+p-1]},f_i+1)$$

那么我们发现每个数的转移并不是由很多个 $p$ 构成的，他转移仅仅取决于他最大的选定的了质因数。

那么我们可以先将 $10^7$ 内的数全部打上最大的那个选定质因数的标记，这里复杂度和比欧拉筛小一点点。

接着我们安排一个线段树，它用来记录某个 dp 值可以传到的位置。枚举 $10^7$ 内所有的数，然后在线段树上二分获取这个值，再看能不能转移给其他数。

这里由于是线段树二分，并且记录的是 dp 值，那么相当于可以用无递归，大概复杂度卡的过去。

```cpp
#include<bits/stdc++.h>
using namespace std;
int mx[20000001];
int f[10000001];
int t[10000001];
bool s[10000001];
void add(int x, int s) {
	int i = 1, l = 1, r = 2500000;
	int mid;
	while (l < r) {
		mx[i] = max(mx[i], s);
		mid = (l + r) >> 1;
		if (x > mid)
			l = mid + 1, i = i << 1 | 1;
		else
			r = mid, i = i << 1;
	}
	mx[i] = max(mx[i], s);
}
int ans(int x) {
	int i = 1, l = 1, r = 2500000;
	int mid;
	if (mx[i] < x)
		return -1;
	while (l < r) {
		mid = (l + r) >> 1;
		if (mx[i << 1] >= x)
			r = mid, i = i << 1;
		else
			l = mid + 1, i = i << 1 | 1;
	}
	return l;
}
int m, q, n;
int p[100001];
int main() {
	freopen("memory.in", "r", stdin);
	freopen("memory.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> m >> q;
	for (int i = 1; i <= m; i++)
		cin >> p[i];
	sort(p + 1, p + 1 + m);
	for (int i = 1; i <= m; i++) {
		if (!s[p[i]]) {
			for (int j = 0; j <= 10000000; j += p[i])
				t[j] = p[i];
			s[p[i]] = 1;
		}
	}
	add(1, t[0] - 1);
	for (int i = 1; i <= 10000000; i++) {
		f[i] = ans(i);
		if (t[i] && f[i] != -1)
			add(f[i] + 1, i + t[i] - 1);
	}
	while (q--) {
		cin >> n;
		if (f[n] == -1)
			cout << "oo\n";
		else
			cout << f[n] << '\n';
	}
	return 0;
}
```

---

## 作者：_determination_ (赞：0)

抽象思维题。

显然我们可以直接 dp，$f_i$ 为将 $i$ 变成 0 所需的最小步数。

显然 $f_x=\min _{i=1}^{n} f_{\left \lfloor \frac{x}{a_i} \right \rfloor }+1$，然后状态是 $O(n)$ 的但是转移不是一个区间，优化不下去了。

发现这玩意显然是单调的。设 $p_x$ 为在质数集中最大的能整除 $x$ 的数。

那么我们有 $f_i \to f_{[i+1,i+p_i-1]}$。发现左端点单调递增，直接队列优化一下即可。

```cpp
#include<bits/stdc++.h>
// #define int long long
#define endl '\n'
using namespace std;
const int mod=998244353,inf=0x3f3f3f3f3f3f3f3f;
const int N=1e5+10,M=1e7+10,lim=1e7+1;
int n,m,l=1;
int a[N],f[M],pm[M];
queue<pair<int,pair<int,int>>>q;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for ( int i = 1 ; i <= n ; i++ )cin >> a[i];
	sort(a+1,a+1+n);
	pm[0]=a[n];
	for ( int i = 1 ; i <= n ; i++ )
	{
		for ( int j = a[i] ; j <= lim ; j+=a[i] )
		{
			pm[j]=a[i];
		}
	}
	for ( int i = 1 ; i <= n ; i++ )
	{
		if(1ll*l*a[i]>lim)
		{
		    l=lim;
		    break;
		}
		l*=a[i];
	}
	memset(f,0x3f,sizeof(f));
	q.push({0,{0,0}});
	for ( int i = 0 ; i < l ; i++ )
	{
		while(q.front().second.second<i)q.pop();
		f[i]=q.front().first;
		q.push({f[i]+1,{i+1,i+pm[i]-1}});
	}
	while(m--)
	{
		int x;
		cin >> x;
		if(x>=l)cout << "oo\n";
		else cout << f[x] << endl;
	}
	return 0;
}
/*
n+m
100
>=lcm显然无解
这个好证。
<max显然答案为1，用max进行操作即可
然后答案显然不降
哎呦512M直接dp预处理出1~lcm的全部答案即可
显然每次操作我们要让数尽可能变小
那么我们就有nm做法。 
翻了
这个dp我们考虑被动转移
这样的话转移过去就是一个区间。
这玩意不好用数据结构维护
但是我们发现f数组有单调性并且区间左端点单调上升
用一个队列存储所有转移
到i的时候就弹出所有不合法转移(r<i)
然后取出队头进行转移，因为单调性，这样是正确的
瓶颈在于筛最大质因子的过程
似乎是ln，又似乎是loglogn?
跑得飞快就是了 
*/
```

---

## 作者：takanashi_mifuru (赞：0)

考虑设 $dp_i$ 表示把 $i$ 变成 $0$ 的最小步数。

转移是简单的，$dp_i=\min\{dp_{\lfloor\frac{i}{p_j}\rfloor p_j}\}+1$。

但是这个肯定是过不了的，我们观察这个式子容易发现，$dp$ 一定单调不减，同时相邻两项最多相差 $1$。

我们考虑将他差分一下来研究一下什么地方会使得 $dp$ 变化 $1$，容易发现如果对于所有的质数，他都取不到最后一个 $+1$ 之前的位置，他就会再 $+1$。

换句话说，我们对于当前点枚举所有不是他的因数的数，然后求出他的下一个倍数在哪里，把这个东西求个最大值就是下一个分界点，特别地，如果所有数都是他的因数，那就无解了。

直接这样写就可以通过这个题，为什么呢？

我们考虑最大的质数 $p_{max}$，则在区间 $(up_{max},(u+1)p_{max})$ 之间最多只有一个分界点，因为一旦出现两个分界点，我的第二个分界点就可以操作 $p_{max}$ 直接变成 $up_{max}$，其中 $u$ 为任意正整数。

这也就意味着分界点的总数是 $O(\frac{10^7}{p_{max}})$ 的，我们最多操作这么多次，每操作一次需要 $O(m)$ 来寻找分界点，而显然 $p_{max}>m$，所以最后只会总共只会枚 $10^7$ 次。

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,q;
int stk[100005];
int top,pos;
int Min;
int ans[10000005];
int diff[10000005];
int Max=2e9;
int main(){
    scanf("%d%d",&m,&q);
    for(int i=1;i<=m;i++){
        int x;
        scanf("%d",&x);
        stk[++top]=x;
    }
    sort(stk+1,stk+1+top);
    for(int i=1;i<=top;i++){
        if(stk[i]!=stk[i-1]){
            stk[++pos]=stk[i];
        }
    }
    for(int i=1;i<=10000000;){
        diff[i]++;
        int nxt=i;
        for(int j=1;j<=pos;j++){
            if(i%stk[j]==0)continue;
            nxt=max(nxt,((i)/stk[j]+1)*stk[j]);
        }
        if(nxt==i){//
            Max=i;
            break;
        }
        i=nxt;
    }
    for(int i=1;i<=10000000;i++){
        diff[i]+=diff[i-1];
    }
    while(q--){
        int x;
        scanf("%d",&x);
        if(x>=Max){
            puts("oo");
            continue;
        }
        printf("%d\n",diff[x]);
    }
    return 0;
}
```

---

## 作者：Mrkn_chenyx12 (赞：0)

# 思考

显而易见，观察一次操作的定义 $n\to \lfloor \frac{n}{p_i}\rfloor\times p_i$，不难发现实际上就是将 $n$ 变为最大的 $k$ 使得 $k\le n$ 且 $k\bmod p_i=0$。从而易得当且仅当 $n$ 是 $p_i$ 的倍数时，操作无效。那么对于 $n\ge\operatorname{lcm}p=\prod p_i$，一定无解，反之一定有解。

反向思考这道问题，即尝试从 $0$ 扩展到 $n$，预处理答案并保存到 $ans$ 数组。从而，对于一个 $p_i$ 的倍数 $k$，它可以影响到的范围是 $[k+1,k+p_i-1]$，并且取值均为 $ans_k+1$。那么显而易见，答案是单调不减的。

考虑动态维护利用每个素数 $p_i$ 作为最后一个转移到当前位置 $k$ 的成本，只需要在 $k\bmod p_i=0$ 时更新为无穷大，并在 $k\bmod p_i=1$ 时更新为 $ans_{k-1}+1$ 即可。

通过值域维护有多少个素数 $p_i$ 作为最后一个时答案为 $x$，记录当前位置可行的最小答案，已无法取到时向上更新即可。

# 实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int m, q, n, p[100024], cv[100024];
int ans[10000024], vc[10000024], mz;
int lim;

struct Task {
    int p;
    bool r;
};

Task tsks[100024];
int nex[100024];
int s[10000024];

inline bool hasTask(int tz) {
    return s[tz] != 0;
}

inline Task getTask(int tz) {
    auto res = tsks[s[tz]];
    s[tz] = nex[s[tz]];
    return res;
}

inline void addTask(int tz, Task task) {
    if (tz > lim) return;
    nex[task.p] = s[tz];
    tsks[task.p] = task;
    s[tz] = task.p;
}

int main() {
    scanf("%d %d", &m, &q);
    lim = 10000000;
    bool productOver10M = false;
    long long prod = 1;
    for (int i = 1; i <= m; i++) {
        scanf("%d", p + i);
        if (!productOver10M) {
            prod *= p[i];
            if (prod > 10000000) {
                productOver10M = true;
            }
        }
        addTask(p[i], {i, false});
        cv[i] = 1;
    }
    vc[1] = m;
    mz = 1;
    auto isOver = [productOver10M, prod](int v) {
        return (!productOver10M) && (v >= prod);
    };
    lim = productOver10M ? 10000000 : ((int)prod - 1);
    Task tsk;
    for (int i = 1; i <= lim; i++) {
        while (hasTask(i)) {
            tsk = getTask(i);
            if (tsk.r) {
                cv[tsk.p] = ans[i - 1] + 1;
                vc[cv[tsk.p]]++;
                addTask(i + p[tsk.p] - 1, {tsk.p, false});
            }
            else {
                vc[cv[tsk.p]]--;
                addTask(i + 1, {tsk.p, true});
            }
        }
        while (!vc[mz]) mz++;
        ans[i] = mz;
    }
    while (q--) {
        scanf("%d", &n);
        if (isOver(n)) {
            puts("oo");
        }
        else {
            printf("%d\n", ans[n]);
        }
    }
    return 0;
}
```

---

