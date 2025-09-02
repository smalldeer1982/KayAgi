# [ABC277D] Takahashi's Solitaire

## 题目描述

【题面翻译】

给定 $n$ 张牌，每张牌上有一个数字 $a_i$。

你要先选一张牌放在桌子上。假设当前最后一张放置的牌为 $x$，接下来，你每次只能放写着 $x$ 或 $(x + 1) \bmod m$ 的牌。

一直操作下去。你需要让你手上剩下的牌的总和**最小**。

translated by @[liangbowen](https://www.luogu.com.cn/user/367488).

## 说明/提示

$1 \le n \le 2 \times 10^5$

$2 \le m \le 10^9$

保证 $0 \le a_i < m$。

## 样例 #1

### 输入

```
9 7
3 0 2 5 5 3 0 6 3```

### 输出

```
11```

## 样例 #2

### 输入

```
1 10
4```

### 输出

```
0```

## 样例 #3

### 输入

```
20 20
18 16 15 9 8 8 17 1 3 17 11 9 12 11 7 3 2 14 3 12```

### 输出

```
99```

# 题解

## 作者：liangbowen (赞：17)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc277_d)

[或许更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16885477.html)

比较简单的模拟。

## 思路

首先把 $a_i$ 排序。每次往后一直跑，如果不能再取了，就停下。

但是这样做是 $O(n^2)$ 的。我们需要优化。

优化也很容易想到：假设我们跑完了区间 $[l, r]$，下一个开始的地方其实是 $r + 1$。

有了这个优化，时间复杂度就是 $O(n)$ 了。

实现方面，有一个细节：由于可以取 $(x + 1) \bmod m$，所以我们跑到末尾时，可能会跳回 $a_1$。

为了以防死循环，我们要做两件事：

1. 如果当前回合把全部牌都取光了，要立刻终止。
2. 如果程序已经跳回过 $1$ 了，取完这一回合后也要立刻终止。

## 代码

省去了大量的缺省源。

赛时打的，乱糟糟的。

```cpp
const int N = 2e5 + 5;
int a[N];
void solve()
{
	int n, m;
	scanf("%d%d", &n, &m);
	ll sum = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
	sort(a + 1, a + n + 1);
	int pos = 1; ll ans = sum;
	bool calc = false; //是否跳回去过
	for (;;)
	{
		int p = pos; ll tsum = sum;
		for (int nxt; sum != 0;) //nxt 是下一个点
		{
			if (p == n) calc = true; //即将跳回去
			nxt = (p == n ? 1 : p + 1);
			sum -= a[p];
			if (a[p] != a[nxt] && (a[p] + 1) % m != a[nxt]) break;
			p = nxt;
		}
		ans = min(ans, sum);
		if (calc) break;
 
		if (p == n) calc = true; //即将跳回去
		pos = (p == n ? 1 : p + 1);
		sum = tsum;
	}
	cout << ans << '\n';
}
```

希望能帮助到大家！

---

## 作者：WaterSun (赞：7)

# 思路

本题的操作只与 $a_i$ 有关，与 $i$ 的顺序无关，因此，我们可以对它进行排序。

我们将序列 $a$ 变为两个 $a$ 拼接起来的结果。

我们可以枚举起点 $i$，一步步往后推，直到不满足条件。

最后求每一次的最小值即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10,inf = 1e18 + 10;
int ln,m,n,sum,ans = inf;
int a[N],arr[N];
map<int,int> mp;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	ln = read();
	m = read();
	for (re int i = 1;i <= ln;i++){
		a[i] = read();
		mp[a[i]]++;
		sum += a[i];
	}
	sort(arr + 1,arr + 1 + ln);
	for (auto it = mp.begin();it != mp.end();it++) arr[++n] = (it -> first);//因为枚举过程中有重复元素较为麻烦，所以可以用离散化搞一下 
	for (re int i = 1;i <= n;i++) arr[i + n] = arr[i]; 
	for (re int i = 1;i <= n;){
		int res = mp[arr[i]] * arr[i];
		int j = i + 1;
		for (;j < i + n;j++){//最多走 n 步 
			if (arr[j] >= m) j = n;//超出 m，x 跳到 0 
			else if (j == n + 1){ 
				if (arr[j]) break;//第一个元素不满足：a[1] = 0 
			}
			else if (arr[j] - arr[j - 1] == 1) res += mp[arr[j]] * arr[j];//满足条件，累加答案 
			else break;
		}
		ans = min(ans,sum - res);//取最小值 
		if (j > n) break;//优化 
		i = j;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：liaoxingrui (赞：3)

## Content

给你 $n$ 张牌，每张牌有一个权值 $a_i$，最开始你可以选择一张牌 $x$ 删除，后面你就只能选值为 $x$ 或 $( x + 1 ) \bmod m$ 的牌删除。

问你最后剩下的牌的和最小为多少？

## Solution

问你和最少，就需要删除的和最大，贪心明显不可能。

我们可以发现被删除的数一定是连续的一段（除了 $m - 1$ 和 $0$ 之外），那么这一段从里面最小的数开始删除一定是最优的，所以就不用搜这一段的其他数，时间复杂度 $O(n)$。

要注意需要将以 $0$ 开始的一段的和记录下来，如果有以 $m - 1$ 结尾的一段，则将两段的和加在一起计算。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,tot;
int a[N],b[N];
long long cnt,ans=LONG_LONG_MAX,sum2;
long long sum[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt+=a[i];
	}
	sort(a+1,a+n+1);
	a[0]=-1;
	for(int i=1;i<=n;i++)
		if(a[i]!=a[i-1]){
			tot++;
			b[tot]=a[i];
			sum[tot]=1;
		}
		else
			sum[tot]++;
	for(int i=1;i<=tot;i++){
		long long sum1=sum[i]*b[i];
		for(int j=i;j<tot;j++)
			if(b[j]+1==b[j+1]){
				sum1+=sum[j+1]*b[j+1];
				if(j==tot-1)
					i=tot; 
			}
			else{
				if(b[i]==0)
					sum2=sum1;
				i=j;
				break;
			}
		if(b[i]==m-1)
			sum1+=sum2;
		ans=min(ans,cnt-sum1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：快乐的大童 (赞：3)

我们钦定“取数”为题目中所说的“将一个数放置在桌子上”。

由于对于某一个数 $x$，它只能取 $x$ 和 $(x+1)\bmod m$ 两种数，所以我们发现，只要 $(x+1)\bmod m$ 能取到的数，$x$ 就一定能取到。


那么我们可以先对原数列排序，记录下来每个数出现的次数，然后去重，方便处理。

拿样例举个例子（$n=9,m=7$）：

`3 0 2 5 5 3 0 6 3`

排序之后：

`0 0 2 3 3 3 5 5 6`

去重：

`0 2 3 5 6`

则我们可以知道：

- 数字 `0`、`3` 只能取到本身；
- 数字 `2` 可以取到 `2` 和 `3`；
- 数字 `5` 可以取到 `5`、`6` 和 `0`。
- 数字 `6` 可以取到 `6` 和 `0`；

------------

**以下 $a$ 表示对原数组进行排序去重处理后的数组，$M$ 表示去重后数组的长度。注意题目给出的 $m$ 和这个钦定的 $M$ 的区别。**

$cnt_i$ 表示数 $a_i$ 在**原数组**中出现的次数。

然后从后往前枚举每一个数，令 $ans_i$ 表示若最开始先取 $a_i$，能取到的数的总和。

这样我们可以得到：

- $ans_M=cnt_M\times a_M$。
- 若 $a_{i+1}=(ai+1)\bmod m$，则 $ans_i=ans_{i+1}+cnt_i\times a_i$。
- 反之 $ans_i=cnt_i\times a_i$。

由于对于数 $m-1$，它既可以取它本身，也可以取 $0$。

所以我们需要特判一下当 $a_1=0,a_M=m-1$（因为我们已经排序过了）的时候，对于所有能取到 $m-1$ 的数（包括它本身），将其的答案加上 $ans_M$。

不要忘记特判一下所有数都可以取到 $m-1$ 的情况。

例如（$n=m=5$）：

`0 1 2 3 4`

正确答案显然为 `0`，标准错误答案为 `-10`。


------------

最后对所有 $ans_i$ 取 $\max$，答案即为 $sum-\max\{ans_i\}$，其中 $sum$ 为原数列的数的总和。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int R(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;
}
inline void write(int x){
	if(x<0){x=-x;putchar('-');}
	int y=0;char z[70];
	while(x||!y){z[y++]=x%10+48;x/=10;}
	while(y--)putchar(z[y]);
}
const int N=2e5+5;
int n,mod,a[N],sum;
map<int,int>cnt;
int tmp;
int ans[N];
signed main(){
	n=R(),mod=R();
	for(int i=1;i<=n;i++) a[i]=R(),cnt[a[i]]++,sum+=a[i];
	sort(a+1,a+n+1);
	int m=unique(a+1,a+n+1)-(a+1);
	bool flag=1;
	for(int i=2;i<=m;i++){
		if(a[i]!=a[i-1]+1) flag=0;
	}
	if(flag){
		puts("0");
		return 0;
	}
	ans[m]=cnt[a[m]]*a[m];
	for(int i=m-1;i>=1;i--){
		if(a[i+1]-a[i]==1) ans[i]=ans[i+1]+cnt[a[i]]*a[i];
		else ans[i]=cnt[a[i]]*a[i];
	}
	if(a[m]==mod-1&&a[1]==0){
		ans[m]+=ans[1];
		for(int i=m-1;i>=1;i--){
			if(a[i+1]-a[i]==1) ans[i]+=ans[1];
			else break;
		}
	}
	int res=0x7fffffffffffffff;
	for(int i=1;i<=m;i++){
		res=min(res,sum-ans[i]);
	}
	write(res);
}

```


---

## 作者：kczw (赞：2)

# 题意
给定一个长度为 $n$ 的并且元素大小小于 $m$ 的数列，选择其中一个类似于 $1,2,3,……$ 或者 $m-3,m-2,m-1,0,1,……$ 的值域，当然值域范围内的所有数都必须要在给定的数列中出现过。我们在数列中删去所有在此值域内的数，使得数列的和最小。

# 思路
首先 $m\leq10^9$ 并且 $n\leq2\times10^5$，所以很容易能知道要离散处理，理所应当想到用 map。

然后，易知将数列存于 map 中并且遍历，枚举出值最大的连续段。

最后用数列总和减去求得的连续段的值，即为答案。

# 实现

```cpp
#include<iostream>
#include<map> 
#define int long long
using namespace std;
map<int,int> mp;
int n,m,ans,sum,res,lst=-1,bres=-1;
//res存储连续段的值，bres是为了处理类似于从m-1到0的段不直接相连时的变量
//bres存储的值时第一个连续段的值，最后处理时，如果没有m-1到0的连续段，bres并不会被使用（详见代码）
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1,a;i<=n;i++)scanf("%lld",&a),mp[a]++,sum+=a;
	for(auto t:mp){
		if(t.first-lst!=1&&lst!=-1){
			ans=max(ans,res);
			if(bres==-1)bres=res;
			res=0;
		}res+=t.second*t.first;
		lst=t.first;
		if(t.first==m-1&&mp.find(0)!=mp.end())ans=max(ans,res+bres);
	}ans=max(ans,res);
	printf("%lld",sum-ans);
	return 0;
}
```


---

## 作者：ImposterAnYu (赞：2)

~~RMJ是废了吗，几乎每次交都是UKE~~

~~别问为什么标题这样写，问就是写成Takahashi's Solitaire会炸~~

题目意思翻译里已经讲得很清楚了。既然是要手中的牌总和最小，自然是要让桌上的牌总和最大。

首先，因为我们不一定要按照题目中给的顺序来放牌，所以我们可以考虑将所有的牌按从小到大的顺序排序。这样会方便我们进行取牌的操作。

接下来怎么做呢？很显然，因为我们需要让取出来放到桌面上的牌的总和最大，所以我们需要采取贪心的策略，能取就取。所以，我们需要从第一张牌开始，判断后面的牌可不可以取。能取就取出来，不能取就算答案，然后从下一张开始重新取。为什么不用从头开始取呢？因为从刚才取过的开头那一张的后面开始取答案只会更小，没有必要。毕竟每张牌上面的数都是非负整数。

最后一个问题：取到最后一张之后还能取怎么办？一般我们的思路都是回到开头继续取，但是显然没有这个必要。当我们的数组的最后一个元素需要连接第一个元素时，我们可以索性把整个数组接在最后一个元素后面（相当于是把牌复制了一份），并且把接上的数组的每个元素都加上 $m$。因为 $a \equiv (a + m)\pmod{m}$，所以我们在计算答案的时候让 $a_i$ 对 $m$ 取模，这样子既可以保证牌上数字的单调性（因为 $0 \leq a_i < m$），又可以方便计算答案。

但是这样会带来一个新问题：如果无论从哪个地方开始取牌都可以取完，那么我们的算法会取双倍的牌出来。

比如下面这组数据：

```
5 5
0 1 2 3 4
```

正确答案显而易见是 $0$，但是我们的算法因为会多取一倍的牌出来，导致答案变成了 $-10$。~~手上还剩负数张牌，这不扯淡吗~~

怎么办呢？其实很简单，给取的牌加一个张数限制，当取出的牌达到 $n$ 张之后，你能取也不能再取了，必须出来统计答案。

这么一套操作下来，题目也就解决啦~

贴个代码：

```cpp
#include<bits/stdc++.h>
#define N 400000
#define int1 long long
using namespace std;
int1 n,nn,m,a[N + 5],ans,i,j,sum,s,len;//sum表示取出的牌的和，ans表示桌上的牌总和的最大值，len表示取出的牌的张数（偷懒写成了长度length）。 
void C(){//关同步（加速读入输出用的）。 
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	return ;
}
int main(){
	C();
	cin >> n >> m;
	nn = (n << 1);//总牌数（因为复制了一遍牌）。 
	for(i = 1; i <= n; i++){
		cin >> a[i];
		s += a[i];//牌的总和。 
	}
	sort(a + 1,a + n + 1);//排序。 
	for(i = 1,j = n + 1; i <= n; i++,j++){
		a[j] = a[i] + m;//复制牌。 
	}
	for(i = 1,j = 0; i <= nn; i++,j++){
		if(a[i] - a[j] <= 1 && len < n){//如果还能取就取牌。 
			sum += a[i] % m,ans = max(ans,sum),len++;
		}else{//不能取就滚（bushi）。 
			sum = a[i] % m,ans = max(ans,sum),len = 1;//其实是重新取。
		}
	}
	cout<< s - ans << endl;//拿总和减去拿出去的最大值，得到的就是拿在手里的最小值。 
	return 0;
}
```


---

## 作者：VitrelosTia (赞：1)

完全想复杂的一道题，不过每一步都是典 trick。

首先考虑对于 $a_i$，把 $a_i$ 和 $a_i + 1 \bmod m$ 合并，用并查集维护每次更新大小，最后找最大的并查集就行了。然后发现值域非常大，直接离散化会破环数量关系，考虑到只关心 $a_i$ 和 $a_i + 1 \bmod m$ 并且 $a_i < m$，只离散化 $a_i$ 和 $a_i + 1$ 即可。最后有一些边界仔细实现一下就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define test cerr << "test\n"
#define print(x) cout << #x << " = " << x << endl
#define file(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

const int N = 1e6 + 5;
int n, k, m, a[N], b[N];
int f[N], siz[N];
void init(int n) { for (int i = 0; i <= n; i++) f[i] = i; }
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
void merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return;
	f[x] = y; siz[y] += siz[x];
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> k; int sum = 0, mx = 0; bool h0 = false;
	for (int i = 1; i <= n; i++) {
		cin >> a[i]; if (a[i] == 0) h0 = true;
		sum += a[i], mx = max(mx, a[i]);
		b[++m] = a[i], b[++m] = a[i] + 1;
	}
	sort(b + 1, b + m + 1); m = unique(b + 1, b + m + 1) - (b + 1); 
	init(m); if (mx == k - 1) k = b[m];
	for (int i = 1; i <= n; i++) {
		a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b - (h0);
		siz[find(a[i])] += b[a[i] + h0];
		merge(a[i], (a[i] + 1) % k);
	} int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, siz[find(a[i])]);
	cout << sum - ans;
	return 0;
}
```

---

## 作者：cczzss (赞：1)

## 思路
首先我们可以发现，如果取了一个整数 $X$，就应当取完所有的整数 $X$。这样我们只需要考虑取 $(X+1)\bmod M$ 的情况。
将原数组去重、从大到小排序后，对于任意的 $X$ ，都可以通过二分查找 $(X+1)\bmod M$。

不同于其他题解，我是通过图论完成的。那么这时候，我们就应考虑建边。建立一条从 $X$ 指向 $(X+1)\bmod M$ 的有向边。

接下来考虑答案。要求的是剩下的最小值，即取出放在桌上的最大值。那么很简单，**bfs** 跑最长路即可。这里注意点权要乘上这个数出现的次数。

来看特殊情况，如果一个整数找不到 $(X+1)\bmod M$，答案就应与这个数乘上它的出现次数的乘积取最大值。

还有一种情况，建好的图恰好是一个环，特判一下，输出 $0$ 即可。

最后记得开 **long long**。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,a[N],in[N],dis[N],sum,rt[N],cnt,ans,vis[N],out[N];
map<int,int>mp;
struct edge{
    int to,next;
}e[N];
void add(int x,int y){
    e[++cnt]={y,rt[x]},rt[x]=cnt;
}
queue<int>q;
void bfs(int x){
    memset(dis,0,sizeof dis);
    q.push(x);dis[x]=a[x]*mp[a[x]];
    while(q.size()){
        int p=q.front();q.pop();
        for(int i=rt[p];i;i=e[i].next){
            int v=e[i].to;
            if(dis[p]+a[v]*mp[a[v]]>dis[v]){
                dis[v]=dis[p]+a[v]*mp[a[v]];
                q.push(v);
            }
        }
    }
    for(int i=1;i<=n;i++) if(dis[i])ans=max(ans,dis[i]);
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        ++mp[a[i]];sum+=a[i];
        if(mp[a[i]]>1) a[i]=-1;
    }
    sort(a+1,a+n+1,greater<int>());
    bool b=0;
    for(int i=1;i<=n&&a[i]!=-1;i++){
        int p=(a[i]+1)%m;
        if(p==a[i]) continue;
        int l=1,r=n,mid,q=0;
        while(l<=r){
            mid=l+r>>1;
            if(a[mid]>=p) q=mid,l=mid+1;
            else r=mid-1;
        }
        if(a[q]==p){
        	add(i,q);in[q]++;out[i]++;
        	vis[i]=1;
        	if(vis[q]) b=1;
        }
    }
    bool f=0;
    for(int i=1;i<=n&&a[i]!=-1;i++)
        if(!in[i]){
        	f=1;
        	if(out[i]) bfs(i);
        	else ans=max(ans,a[i]*mp[a[i]]);
        }
    if(!f&&b) cout<<0;
    else cout<<sum-ans;
}
```

---

## 作者：lyt_awa (赞：1)

## 思路
由于$a_i$ 的顺序与取那个数无关。所以可以先对 $a$ 数组进行排序。

又因为保证 $0 \le a_i < m$，所以对于一张牌 $a_i$ 被拿走那么只要满足 $a_{i+1}=a_i$ 或者 $a_{i+1}=a_i+1$ 那么牌 $a_{i+1}$ 也会被拿走（在 $i=n$ 时，要同时满足 $a_n=m-1$ 和 $a_1=0$，那么在 $a_1$ 被拿走后，牌 $a_n$ 也会被拿走）。

于是可以用**并查集**来维护能同时被拿走的牌，最后再枚举拿走哪个并查集里的所有牌能使剩下来的牌数字之和最小就行了。
## $code$
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

int n, m, a[N], p[N], fa[N], sum1[N];
int ans = 0x3f3f3f3f3f3f3f3f, sum = 0;

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

signed main() {
	n = read();
	m = read();
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
		fa[i] = i;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i) sum1[i] = a[i];
	for (int i = 1; i <= n; ++i) {
		sum += a[i];
		p[i] = p[i - 1] + a[i];
		if (i == n) {
			if (a[i] == m - 1 && !a[1]) {
				int f1 = find(i), f2 = find(1);
				if (f1 != f2) {//一定要判
					sum1[f2] += sum1[f1];
					fa[f1] = f2;
				}
			}
		}
		else if (a[i] == a[i + 1] || a[i] + 1 == a[i + 1]) {
			int f1 = find(i), f2 = find(i + 1);
			if (f1 != f2) {
				sum1[f2] += sum1[f1];
				fa[f1] = f2;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		int fd = find(i);
//		printf("%lld\n", sum1[fd]);
		ans = min(ans, sum - sum1[fd]);
	}
	printf("%lld\n", ans);
	return 0;
}
```
时间复杂度大约 $O(n \log n)$（用了**路径压缩**时间复杂度比较玄学）。

---

## 作者：4041nofoundGeoge (赞：0)

## 思路

我们首先要找出每个整数在初始手牌中出现的次数。即序列 $\{(v_0,f_0),(v_1,f_1),(v_2,f_2),\dots,(v_{k-1},f_{k-1})\}$ 表示上面写着 $v_i$ 的卡片出现了 $f_i$ 次（我们设 $f_0,f_1,\dots,f_{k-1}∈\mathbb{N^+}$，且 $v_0<v_1<\dots<v_{k-1}$）。我们需要 $O(N\log N)$ 的时间复杂度找到此序列。

> 你需要让你手上剩下的牌的总和最小

根据这句话，我们假设 Takahashi 总是放我们上一次放的牌。**所以，我们总是可以唯一确定第二张及以后要放的牌，那么留给他的唯一选择就是第一张牌要放。**

接下来我们分情况讨论：

1. 如果 $k=M$，我们什么都不需要做，直接输出 $0$。
2. 如果 $k<M-1$，我们设 $s_i$ 表示的是当我们第一张牌为 $v_i$，最后剩下的牌的总和。我们的目的就是找到 $s_0,s_1,\dots,s_{k-1}$。当第一张牌为 $v_i$ 时，我们又可以继续分情况讨论（~~分情况套分情况~~）：
   - 当 $v_{(i+1)\pmod k} \not\equiv (v_i+1)\pmod M$ 时，最开始的牌总和为 $\sum\limits_{j=0}^{k} v_jf_j$，他可以扔掉 $v_if_i$ 张牌，所以 $s_i=\sum\limits_{j=0}^{k} v_jf_j$。
   - 当 $v_{(i+1)\pmod k} \equiv (v_i+1)\pmod M$ 时，同理 $s_i=s_{(i+1)\pmod k}-v_if_i$。

因此，从某些 $p$ 开始，我们计算 $s_i$，总时间复杂度为 $O(N)$，输出 $\min\limits^{k-1}_{i=0}s_i$。

综上总时间复杂度为 $O(N\log N)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define wrote return
#define by 0
using namespace std;
ll s[200005];
int main()
{
    ll n, M, a, sum = 0;
    map<ll, ll> m;
    cin >> n >> M;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        m[a]++;
        sum += a;
    }
    vector<pair<ll, ll>> v;
    for (auto p : m)
        v.push_back(p);
    int k = v.size();
    if (k == M) {
        cout << 0 << endl;
        return 0;
    }
    int p;
    for (int i = 0; i < k; i++) {
        if (v[(i + 1) % k].first != (v[i].first + 1) % M) {
            p = i;
            break;
        }
    }
    for (int i = 0; i < k; i++) {
        int j = (p - i + k) % k;
        s[j] = sum;
        if (v[(j + 1) % k].first == (v[j].first + 1) % M)
            s[j] = s[(j + 1) % k];
        s[j] -= v[j].first * v[j].second;
    }
    ll ans = INT_MAX - 5;
    for (int i = 0; i < k; i++)
        ans = min(ans, s[i]);
    cout << ans;
    puts("");
    wrote by;
}
```

---

## 作者：wfc284 (赞：0)

小炮打蚊子……  
因为我没有看到 $0 \leqslant a_i < m$ 的条件，同时误以为大力模拟非常复杂，于是采用了更复杂的方法。  
先进行**图论建模**。对于一个值 $a_i$，能向 $(a_i+1) \bmod m$ 连一条边（如果存在），扫一遍连边即可。值域很大，注意离散化。点权为值乘出现次数（取一个点必定可以取完相同权值的）。  
然后注意到图可能有环（实际上也就 $0 \leqslant val < m$ 那一块有环），于是跑一遍 Tarjan 缩点。  
最后拓扑排序求最长链即可。
### Code
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define int long long
using namespace std;
const int N = 2e5+2;

int n, m, a[N], sum;
vector<int> va;
int val[N];

int func(int x) { return lower_bound(va.begin(), va.end(), x) - va.begin(); }

struct node {
	int u, v;
	node(int u = 0, int v = 0) : u(u), v(v) { }
} e[N];
int tot;

vector<int> g[N];
int ind[N];
void build() {
	for(int i = 1; i <= tot; ++i)
		g[e[i].u].push_back(e[i].v);
}

int dfn[N], low[N], num, exist[N];
int colour[N], knum, newval[N];
stack<int> st;
void Tarjan(int u) {
	dfn[u] = low[u] = ++num;
	st.push(u), exist[u] = 1;
	for(auto v : g[u]) {
		if(!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
		else if(exist[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		++knum;
		while(!st.empty()) {
			int x = st.top();
			st.pop();
			colour[x] = knum;
			newval[knum] += val[x];
			exist[x] = 0;
		}
	}
}

vector<int> newg[N];
void rebuild() {
	for(int i = 1; i <= n; ++i) 
		for(auto j : g[i]) {
			int x = colour[i], y = colour[j];
			if(x != y) newg[x].push_back(y), ++ind[y];
		}
}

int f[N], ans;
queue<int> q;
void Topsort() {
	for(int i = 1; i <= knum; ++i) 
		if(ind[i] == 0) q.push(i), f[i] = newval[i];
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		ans = max(ans, f[u]);
		for(auto v ; newg[u]) {
			f[v] = max(f[v], f[u] + newval[v]);
			if(--ind[v] == 0) q.push(v);
		}
	}
}

signed main() {
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		sum += a[i];
		va.push_back(a[i]);
	}
	va.push_back(-1);
	sort(va.begin(), va.end());
	va.erase(unique(va.begin(), va.end()), va.end());
	
	for(int i = 1; i <= n; ++i) val[func(a[i])] += a[i];
	
	for(int i = 1; i <= n; ++i) {
		int u = func(a[i]), v = func((a[i]+1) % m);
		if(v < (int) va.size() && va[v] == (a[i]+1) % m)	// a[i]+1 mod m 存在
			e[++tot] = node(u, v);
	}
	
	n = va.size() - 1;
	build();
	for(int i = 1; i <= n; ++i)
		if(!dfn[i]) Tarjan(i);
	rebuild();
	Topsort();
	cout << sum - ans;
	return 0;
}
```

---

## 作者：Ivan422 (赞：0)

题目大意：给出长度 $n$ 的正整数数组 $a_i$ 和大小范围 $m$，保证 $0\leq a_i<m$，可以随意选择一张牌开始，并且只能打相同或编号是下一号的牌，其中 $m-1$ 的下一号是 $0$。要能打出的牌编号之和最大，求出剩下的牌的编号和。

可以把牌全部计入一个 `map` 里，再为了方便处理再计入数组 $b$ 中，可以发现出牌操作其实类似环形，可以复制一遍 $b$ 数组。但是这样做会有一个问题：有可能两边都被算了。可以发现这种情况仅限于 $0$ 到 $m-1$ 的牌全部都出现，直接特判即可。

打不同编号的牌比较特殊，由于 `map` 是有序的，直接判断有没有可以打的下一号牌。

每一次当能够成功打牌，就在 $l$ 中记录牌编号和。每一次对和求最大值，最后输出总和减去最大值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=2e5+10,M=1010,P=998244353,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,m,a[N],b[2*N][2],cur,su,ans,l;
map<int,int>mp;
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){mp[a[i]]++;su+=a[i];}
    if(mp.size()==m){cout<<"0\n";return 0;}
    for(auto v:mp)b[++cur][0]=v.first,b[cur][1]=v.second;
    for(auto v:mp)b[++cur][0]=v.first,b[cur][1]=v.second;
    for(int i=1;i<=cur;i++){
        if(i==1||(b[i-1][0]+1)%m!=b[i][0])l=0;
        l+=b[i][0]*b[i][1];
        ans=max(ans,l);
    }
    cout<<su-ans;
    return 0;
}
```

---

## 作者：tsh_qwq (赞：0)

在题解区暂时没有看到类似的做法，发一下，考试时喜提 17 分，考完才发现 sort 范围忘了 $\times 2$，吐血。

[提交记录](https://atcoder.jp/contests/abc277/submissions/64665950)

## 思路

其他题解基本都是搜完了跳回 $a_1$，不难发现这个序列是一个类似于环的结构，遇到环怎么办呢？**破环为列**啊。

我们令 $a_{i+n} = a_i + m$，排序之后用贪心找出和最大的连续子序列，再用数列元素总和去减这个子序列之和即可得出答案。

**但是**，因为 $a_{i+n}>m$，所以计算总和时要模 $m$。还有子序列元素数一定不能大于 $n$，~~考试时因为这个调了 20min~~。

## 代码：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("3","Ofast","inline")
#define int long long
#define endl "\n"
using namespace std;
int n,m,to=1;
int ans;
int a[400005];
int su,la[400005],sum[400005],fst[400005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		a[i+n]=a[i]+m;
		su+=a[i];
	}
	sort(a+1,a+2*n+1);
	la[1]=a[1];
	sum[1]+=a[1];
	fst[1]=1;
	for(int i=2;i<=2*n;i++)
	{
		if((a[i]==la[to]||a[i]==la[to]+1)&&i<fst[to]+n)
		{
			la[to]=a[i];
			sum[to]+=a[i]%m;
		}
		else
		{
			ans=max(ans,sum[to]);
			to++;
			la[to]=a[i];
			sum[to]+=a[i]%m;
			fst[to]=i;
		}
	}
	ans=max(ans,sum[to]);
	cout<<max((int)0,su-ans);
	return 0;
}
```

---

## 作者：Resolute_Faith (赞：0)

现在假定我们有一串序列长得像这样的：

$$
x,x+1,x+1,x+2,x+1,x,x+3,x+2
$$

那么怎么取可以把它们全部取完呢，答案是从小往大取。也就是说对于 $[l,r]$ 中连续的一大段数，排序取后更优。

所以我们用并查集维护一下，如果 $a_i$ 跟 $a_{i+1}$ 可以一下取完，那么把他扔到一个并查集里，最后查询一下所有的集合，看一下哪一个总和最大，就做完了。

时间复杂度好像是 $\mathcal{O}(n\alpha)$。代码很短。

核心代码：

```cpp
sort(a+1,a+n+1);
for(register int i=2;i<=n;i++){
    if(abs(a[i]-a[i-1])<=1){
        int x=find(i);
        int y=find(i-1);
        if(x==y) continue;
        f[x]=y;
    }
    if(a[i]==m-1&&a[1]==0){
        int x=find(1);
        int y=find(i);
        if(x==y) continue;
        f[x]=y;
    }
}
```

---

## 作者：Y2y7m (赞：0)

~~我这场ABC属于是梦幻开局了，第二题读错题，第三题忘了需要离散化~~

这道题也就是个黄题吧。

由于他有可能到达 $m-1$ 又回到 $0$，相当于是一个环，所以我们把这个数组排序去重后复制一遍接在后面，然后 $dp$。

$dp$ 很简单啦，设 $f_i$ 为以第 $i$ 个数为结尾的最大子序列； $cnt_i$ 为数值为 $i$ 的元素个数，转移即为：

- 若 $a_{i-1}\bmod m=(a_i-1)\bmod m$，则 $f_i\gets f_{i-1}+a_i\times cnt_{a_i}$。

- 否则 $f_i\gets cnt_{a_i}$。

设 $a$ 数组之和为 $sum$（在没有排序去重之前）。答案为 $\max(sum-\max{f_i},0)$。

现在来证明他的正确性: 

- 若 $\max{f_i}>sum$，则所有的数均可去到，故答案为 $0$。

- 否则取不到所有数，故答案为 $sum-\max{f_i}$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long
int n,m;
int a[400010];
map<int,int> mp;
int f[400010];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	int sum=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		sum+=a[i];
		mp[a[i]]++;
	}
	sort(a+1,a+1+n);
	int t=unique(a+1,a+1+n)-a-1;
	for(int i=1;i<=t;i++) a[t+i]=a[i];
	t*=2;
	for(int i=1;i<=t;i++)
	{
		if((a[i]-1+m)%m==a[i-1]%m||i==1)
		{
			f[i]=f[i-1]+a[i]*mp[a[i]];
		}
		else f[i]=a[i]*mp[a[i]];
	}
	int ans=0;
	for(int i=1;i<=t;i++) ans=max(ans,f[i]);
	cout<<max(sum-ans,0ll)<<endl;
	return 0;
}

```

祝大家下一场ABC不会像我这一场一样脑瘫至极。

---

## 作者：IYSY2009I (赞：0)

我们首先将 $A_i$ 从小到大排序，然后首尾相接连成一个环。于是可以发现放到桌子上的牌在环上一定是连续的。

于是我们就有了一个相对暴力的思路：枚举第一个放到桌子上的是哪张牌，然后按顺序能放就放，最后对所有答案就取个 $\min$ 就完事了。可以发现时间复杂度是 $O(N^2)$ 的。

我们考虑进一步优化：假如我们已经有了一种方案为将 $[x,y]$ 内的卡牌放到桌子上，则对于 $x \le z \le y$，以 $z$ 为第一个放到桌子上的牌时，方案显然是 $[z,y]$，可以看出一定比 $[x,y]$ 不优。所以下一次枚举的时候从 $y+1$ 号卡牌开始枚举就可以了。稍加分析便可以发现时间复杂度降到了排序的 $O(N\log N)$。
 
大体思路如上所示，具体细节请看代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
long long a[200005];
int vis[200005];
int main(){
	int n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	sort(a+1,a+n+1);
	long long sum=0;
	for(int i=1;i<=n;i++)
		sum+=a[i];
	int l=0,r=0;
	long long ans=sum;
	int cnt=0;
	while(!vis[r%n+1]){
		cnt++;
		l=r%n+1;
		r=l;
		long long aans=a[r];
		vis[r]=cnt;
		while(a[r%n+1]==a[r]||a[r%n+1]==(a[r]+1)%m){
			if(vis[r%n+1]==cnt) break;
			vis[r%n+1]=cnt;
			r=r%n+1;
			aans+=a[r];
		}
		ans=min(ans,sum-aans);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：__vector__ (赞：0)

## 题外话  
不知道为啥别人都用的并查集。  
我赛时写的记忆化搜索过去的。  
## 做法  
把题目画出来，就是所有 $x$ 都可以互相到达，并且 $x$ 可以到达 $(x+1) \mod m$。  

然后现在我们要让剩下的值最少，转化一下就是让选择的数字总值最大，其实就是找一条路径，使得路径权值和最大。  

我们进行建边，首先所有相同数字都可以互相到达，到达了一个数，就可以走到其他所有相同的数。  

所以基于尽可能多选的贪心，我们可以把相同的数缩成一个点。  

缩完点之后，将每个数组中出现过的数 $x$ 连向 $(x+1) \mod m$。  

然后依次枚举从 $a_i$ 出发，进行爆搜。  

爆搜的时候把答案记一下就行了，就是记忆化。  

复杂度 $O(n \log n)$。  
那个 log 是 map 的。  
用 unordered_map 可以 $O(n)$。  
## Code  
```cpp  
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
int n,m;
ll a[maxn];
map<ll,ll> cnt;
map<ll,bool> vis;
map<ll,ll> ans;
void dfs(ll num)
{
	if(cnt.find(num)==cnt.end())
	{
		return;
	}
	if(vis.find(num)!=vis.end())
	{
		return;
	}
	vis[num]=1;
	dfs((num+1)%m);
	ans[num]=ans[(num+1)%m]+cnt[num];
//	printf("ans[%d]: %d\n",num,ans[num]);
}
int main()
{
	ll sum=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum+=a[i];
		cnt[a[i]]++;
	}
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=n;i++)
	{
		cnt[a[i]]=cnt[a[i]]*a[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(vis.find(a[i])==vis.end())
		{
			dfs(a[i]);
		}
	}
	ll out=0;
	for(int i=1;i<=n;i++)
	{
		out=max(out,ans[a[i]]);
	}
	printf("%lld",sum-out);
	return 0;
}
```

---

