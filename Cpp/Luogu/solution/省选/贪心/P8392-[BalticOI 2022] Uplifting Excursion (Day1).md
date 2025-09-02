# [BalticOI 2022] Uplifting Excursion (Day1)

## 题目描述

有 $2m+1$ 种物品，重量分别为 $-m,-m+1,\ldots, m-1,m$。重量为 $i$ 的物品有 $a_i$ 个。

你需要拿走若干物品，使得这些物品重量之和恰好为 $l$。在此基础上，你需要拿尽可能多的物品。

问在物品重量之和恰好为 $l$ 的基础上，你最多能拿多少物品。

## 说明/提示

子任务 $1$ ($5$ 分)：$m , a_i≤50$

子任务 $2$ ($15$ 分)：$m , a_i≤100$。

子任务 $3$ ($20$ 分)：$m≤30$。

子任务 $4$ ($20$ 分)：$m ≤50$。

子任务 $5$ ($20$ 分)：$m ≤ 100$。

子任务 $6$ ($20$ 分)：没有特殊限制。

对于子任务 $3$ 到子任务 $6$，如果通过 $\forall i<0,a_i=0$ 的测试点，可以获得一半的得分。

对于所有数据，满足 $1\leq m \leq 300$，$-10^{18}\le l \le 10^{18}$，$0\le a_i\le 10^{12}$。

## 样例 #1

### 输入

```
2 5
2 3 1 1 4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
3 5
3 1 0 2 0 0 2```

### 输出

```
impossible```

# 题解

## 作者：7KByte (赞：13)

首先我们发现这题不弱于背包，只不过这题多了一个限制，每件物品的价值为 $1$，体积很小。

考虑到总的容量很大而单件物品体积很小，所以我们先贪心的尽量多选物品，这样背包的容量最多还剩 $m$，此时我们再使用背包考虑填满这最后这点体积。由于 $i$ 和 $-i$ 在跑背包是不会同时存在，所以最多再塞 $2m$ 个数，背包值域开 $[-m^2,m^2]$ 即可。

需要注意的细节是对于已经贪心选择的物品，要对应考虑体积为相反数的物品表示反悔操作。对于原体积 $<0$ 的物品，可以先强制选择然后删除，这样将物品体积统一变成正数。多重背包可以直接跑二进制优化，时间复杂度 $\mathcal{O}(m^3\log m)$。

```cpp
#define N 605
int n, m, k, f[N * N]; LL ans, l, a[N], b[N], c[N], d[N];
void ins(LL s,int v,int w){
	if(!s)return;
	cmn(s, n + n + 1LL);
	if(v > 0){
		int c = 1;
		for(; c + c < s; c <<= 1, w <<= 1, v <<= 1);
		while(true){
			pre(x, k - v, 0)cmx(f[x + v], f[x] + w);
			s -= c;
			if(1 == c)break;
			c >>= 1, w >>= 1, v >>= 1;
		}
		if(s > 0){
			v *= s, w *= s;
			pre(x, k - v, 0)cmx(f[x + v], f[x] + w);
		}
	}
	else{
		v = -v;
		int c = 1;
		for(; c + c < s; c <<= 1, w <<= 1, v <<= 1);
		while(true){
			rep(x, v, k)cmx(f[x - v], f[x] + w);
			s -= c;
			if(1 == c)break;
			c >>= 1, w >>= 1, v >>= 1;
		}
		if(s > 0){
			v *= s, w *= s;
			rep(x, v, k)cmx(f[x - v], f[x] + w);
		}
	}
}
int main() {
	read(n, l);
	pr(i, n)read(a[i]), ans += a[i], l += i * a[i];
	LL x; read(x); ans += x;
	rp(i, n)read(b[i]);
	if(l < 0){puts("impossible"); return 0;}
	rp(x, n){
		if(b[x] * x <= l)l -= b[x] * x, ans += (c[x] = b[x]);
		else {c[x] = l / x, ans += c[x], l -= c[x] * x; break;}
	}
	pr(x, n){
		if(a[x] * x <= l)l -= a[x] * x, ans -= (d[x] = a[x]);
		else {d[x] = l / x, ans -= d[x], l -= d[x] * x; break;}
	}
	m = n * n, k = m * 2;
	memset(f, 0xcf, sizeof(f));
	f[m] = 0;
	rp(x, n){
		if(c[x])ins(c[x], -x, -1);
		if(b[x] - c[x])ins(b[x] - c[x], x, 1);
		if(d[x])ins(d[x], -x, 1);
		if(a[x] - d[x])ins(a[x] - d[x], x, -1);
	}
	if(l > m || f[m + l] < -m)puts("impossible");
	else printf("%lld\n", ans + f[m + l]);
	return 0;
}
```

---

## 作者：zhm080507 (赞：12)

#### 题意描述

要在权值为 $[-m,m]$ 中选若干个物品，使它们的**权值之和**为 $L$，并使它们的**个数之和**尽可能大。

#### 算法分析

- 首先我们可以发现选取物品的最优一定是小的多选，那我们可以先将全部都选进来，然后再从大到小删除；

  最后的结果 $sum$ 一定是属于 $[L-m,L+m]$ 的。

```c++
if(sum>L){//如果大了，从m开始删 
		for(int i=2*m;i>m;i--){
			tmp=sum-L;
			b[i]-=min(tmp/(i-m),a[i]);//注意上限 
			sum-=(i-m)*(a[i]-b[i]);
		}
	}else{//如果小了，从-m删 
		for(int i=0;i<m;i++){
			tmp=L-sum;
			b[i]-=min(tmp/(m-i),a[i]);
			sum-=(i-m)*(a[i]-b[i]);
		}
	}
	//a为总数，b为用了的个数 
```

- 现在我们的目标就变成了在当前基础上进行调整，使最后的合并结果变为 $L$。

  我们容易发现对于每一次跳动的最大限度是 $m$，所以一定存在策略能使 $sum$ 维持在 $[L-m,L+m]$ 中；
  而一个当前的 $sum$，在第二次出现时经过调整，结果一定不优；

  由此，对于每个物品，因为其每次使用造成的影响至少为 $1$，所以至多有 $m$ 个变化是有效的，所以得出 $sum$ 的有效值域为 $[L-m^2,L+m^2]$，所以在这里面进行**多重背包**时，物品个数最多为 $m^2$ 个。

  ```c++
  siz=m*m*2;
  	memset(f,-0x3f,sizeof(f));
  	/*
  	接下来在(L-m^2,L+m^2)的值域中跑多重背包 
  	对于物品个数：
  		因为对于一个在(L-m^2,L+m^2)中的值，我们最多只能到达一次， 
  	因为多次变化后答案更劣。而每一个物品加入或删除至少变化一，所
  	以对于每种物品最多考虑m^2个 
  	*/ 
  	tmp=m*m-L+sum;f[tmp]=0;//背包边界 
  	for(int i=0;i<=2*m;i++)
  		f[tmp]+=b[i];//初始化，当前情况用了多少 
  	for(int i=0;i<=2*m;i++){
  		if(i==m) continue;//价值为0的物品显然全选 
  		if(b[i])//如果有用了的，考虑删除 
  			add(-(i-m),-1,min(b[i],(ll)siz)) ;
  		if(a[i]-b[i])//如果有没用的，考虑添加 
  			add(i-m,1,min(a[i]-b[i],(ll)siz)) ;
  	}
  ```

  另外，对于多重背包因为复杂度为 $O(m*(m^2)^2)=O(m^5)$，所以用二进制优化为$O(m^3log(m^2))$。

  ```c++
  void add(ll w,ll v,int c){
  	//w表示当前操作一次对sum的影响，v表示对结果的影响，c表示物品个数
  	if(w>0){
  		for(int s=1;c>0;c-=s,s<<=1){
      	int k=min(s,c);//二进制优化多重背包 
  		for(int i=siz;i>=k*w;i--)
      		f[i]=max(f[i],f[i-k*w]+k*v);
      	//倒序跑01背包
      }
  	}else{
  		for(int s=1;c>0;c-=s,s<<=1) {
  			int k=min(s,c);
  		for (int i=0; i-k*w<=siz;++i)
  			f[i]=max(f[i],f[i-k*w]+k * v);
  		}
  	}
  }
  ```

- 特别的，对于超过值域范围的 $L$ 需要特判掉。

  ```c++
  cin>>m>>L;
  	for(int i=0;i<=2*m;i++){
  		cin>>a[i];b[i]=a[i];
  		//a为总数，b为用了的个数 
  		if(i<m) dm+=a[i]*(i-m);
  		else um+=a[i]*(i-m);
  	}//记录上下边界 
  	if(L<dm||L>um){
  		printf("impossible\n");
  		return 0;
  	}//如果超出，直接结束 
  ```

#### 完整代码

```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int M=310;
ll m,L,dm,um,tmp,sum;
ll a[M*2], b[M*2];
ll siz;
ll f[M*M*2];

void add(ll w,ll v,int c){
	//w表示当前操作一次对sum的影响，v表示对结果的影响，c表示物品个数
	if(w>0){
		for(int s=1;c>0;c-=s,s<<=1){
    	int k=min(s,c);//二进制优化多重背包 
		for(int i=siz;i>=k*w;i--)
    		f[i]=max(f[i],f[i-k*w]+k*v);
    	//倒序跑01背包
    }
	}else{
		for(int s=1;c>0;c-=s,s<<=1) {
			int k=min(s,c);
		for (int i=0; i-k*w<=siz;++i)
			f[i]=max(f[i],f[i-k*w]+k * v);
		}
	}
}

int main(){
//	freopen("greedy.in", "r", stdin);
//	freopen("greedy.out", "w", stdout);
	cin>>m>>L;
	for(int i=0;i<=2*m;i++){
		cin>>a[i];b[i]=a[i];
		//a为总数，b为用了的个数 
		if(i<m) dm+=a[i]*(i-m);
		else um+=a[i]*(i-m);
	}//记录上下边界 
	if(L<dm||L>um){
		printf("impossible\n");
		return 0;
	}//如果超出，直接结束 
	sum=dm+um;
	if(sum>L){//如果大了，从m开始删 
		for(int i=2*m;i>m;i--){
			tmp=sum-L;
			b[i]-=min(tmp/(i-m),a[i]);//注意上限 
			sum-=(i-m)*(a[i]-b[i]);
		}
	}else{//如果小了，从-m删 
		for(int i=0;i<m;i++){
			tmp=L-sum;
			b[i]-=min(tmp/(m-i),a[i]);
			sum-=(i-m)*(a[i]-b[i]);
		}
	}
	siz=m*m*2;
	memset(f,-0x3f,sizeof(f));
	/*
	接下来在(L-m^2,L+m^2)的值域中跑多重背包 
	对于物品个数：
		因为对于一个在(L-m^2,L+m^2)中的值，我们最多只能到达一次， 
	因为多次变化后答案更劣。而每一个物品加入或删除至少变化一，所
	以对于每种物品最多考虑m^2个 
	*/ 
	tmp=m*m-L+sum;f[tmp]=0;//背包边界 
	for(int i=0;i<=2*m;i++)
		f[tmp]+=b[i];//初始化，当前情况用了多少 
	for(int i=0;i<=2*m;i++){
		if(i==m) continue;//价值为0的物品显然全选 
		if(b[i])//如果有用了的，考虑删除 
			add(-(i-m),-1,min(b[i],(ll)siz)) ;
		if(a[i]-b[i])//如果有没用的，考虑添加 
			add(i-m,1,min(a[i]-b[i],(ll)siz)) ;
	} 
	if(f[m*m]<0) cout<<"impossible"<<endl;
	else cout<<f[m*m]<<endl;
	return 0;
}
```

---

## 作者：tzc_wk (赞：12)

首先讲一些错误的方向，刚看到这道题你会发现背包必然是逃不掉的，因此你可能会尝试各种方法乱搞背包，包括但不限于定义域值域交换、猜测答案在 $[m^2,sum-m^2]$ 之内必然有解等等错误的尝试，但是都不太行得通。

正确的方向：**发现一些性质，从而将背包容量限制在 $\text{poly}(m)$ 的规模内**。

我们先考虑一个贪心：先假设所有数全选，求出所有数之和 $s$，如果 $s > L$ 就每次删去最大的数直到 $\le L$ 位置，这个可以直接扫一遍求得，对于 $s<L$ 的情况也同理。此时所有数之和必然在 $[L-m,L]$ 中，但是这不一定是最优方案，我们还需进一步调整。假设此时 $i$ 的数量为 $c_i$，最优解中 $i$ 的数量为 $b_i$，那么有结论 $\sum |b_i - c_i|\le 2m$。证明大概就，在调整过程中，所有物品重量总和肯定不会走出区间 $[L-m,L+m]$，否则我们可以调整删物品/加物品的顺序，并且我们肯定不会重复经过同一个状态两次，因此我们最多加/删物品 $2m$ 次。于是直接多重背包即可。背包容量上界是 $\mathcal O(m^2)$，使用单调队列可以优化到 $\mathcal O(m^3)$。

总之，是一道不错的发掘性质题。

```cpp
const int MAXN = 600;
int n; ll L, a[MAXN + 5], b[MAXN + 5], sum, mnV, mxV;
ll dp1[2000000], dp2[2000000];
void ins(ll *dp, int w, int v, ll num, int lim) {
//	printf("ins %d %d %lld %d\n", w, v, num, lim);
    for (int i = (w > 0) ? (-lim) : lim, stp = 0; stp < abs(w); (w > 0) ? (i++) : (i--), stp++) {
        deque<pair<int, ll> > q;
        for (int j = i, k = 0; j <= lim && j >= -lim; j += w, k++) {
            while (!q.empty() && q.back().se < dp[j + lim] - v * k) q.pop_back();
            q.push_back(mp(k, dp[j + lim] - v * k));
            while (!q.empty() && q.front().fi < k - num) q.pop_front();
            if (!q.empty()) dp[j + lim] = v * k + q.front().se;
        }
    }
}
int main() {
	freopen("goods.in", "r", stdin);
	freopen("goods.out", "w", stdout);
	scanf("%d%lld", &n, &L);
	for (int i = -n; i <= n; i++) {
		scanf("%lld", &a[i + n]);
		sum += i * a[i + n], b[i + n] = a[i + n];
		if (i < 0) mnV += i * a[i + n];
		else mxV += i * a[i + n];
	}
	if (L < mnV || L > mxV) return puts("impossible"), 0;
	if (sum == L) {
		ll res = 0;
		for (int i = 0; i <= 2 * n; i++) res += a[i];
		printf("%lld\n", res); return 0;
	}
	int d = (sum > L) ? 1 : -1;
	for (int i = d * n; i != 0; i -= d) {
		ll l = 0, r = a[i + n], p = 0;
		while (l <= r) {
			ll mid = l + r >> 1;
			if ((sum - mid * i >= L) == (d == 1)) p = mid, l = mid + 1;
			else r = mid - 1;
		}
		sum -= p * i; b[i + n] -= p;
	}
	int lim = n * n;
	memset(dp1, 192, sizeof(dp1)); memset(dp2, 192, sizeof(dp2));
	dp1[lim] = dp2[lim] = 0;
	for (int i = -n; i <= n; i++) {
		if (i == 0) continue;
		ll can_del = min(1ll * n, b[i + n]), can_add = min(1ll * n, a[i + n] - b[i + n]);
		ins(dp1, i, 1, can_add, lim); ins(dp2, -i, -1, can_del, lim);
	}
	ll lft = L - sum, res = -1e18;
	for (int i = -lim; i <= lim; i++) if (-lim <= lft - i && lft - i <= lim)
		chkmax(res, dp1[i + lim] + dp2[lft - i + lim]);
	for (int i = -n; i <= n; i++) res += b[i + n];
	if (res < 0) puts("impossible");
	else printf("%lld\n", res);
	return 0;
}
```

---

## 作者：binbin_200811 (赞：7)

# [P8392 BalticOI 2022 Day1 Uplifting Excursion](https://www.luogu.com.cn/problem/P8392)

贪心加动规，好题，这两个甚至完全相反的东西可以融进一道题……

### 思路

物品较少，贡献较小，体积较小，但总体积巨大。

直接上 $dp$ 容易把心态搞炸。

我们可以先考虑贪心，使贡献最多还剩 $m$。然后考虑背包填满剩下的体积，且 $i$ 和 $-i$ （这里的 $-i$ 是撤销）的物品是不会重复出现在背包中的，如果重复出现了那么肯定不优，所以最多再加入 $2m$ 个数，背包值域开 $[-m^2,m^2]$。

为什么这里的贪心加 $dp$​ 是正确的呢？

* 由于贡献相同，贪心选体积最小的物品肯定可以选择最多。

* 我们在贪心之后进行了 $dp$ 调整，这个调整是可以反悔减少物品的，也就是我们的 $f[l]$ 会在体积满足 $l$​ 的情况下尽可能多的增加，尽可能少的减少物品，这也是和普通背包的区别。

那么最后我们得出的答案一方面保证了体积肯定符合规定，一方面保证了贪心和动规选出的或是减少的数都是最多或最少的。

### 实现

我们在一开始可以先加上所有负数状态，后面的正数状态加入时就相当于也选择了负数。

```cpp
    scanf("%lld%lld",&n,&l);
    for(int i=n;i;i--) scanf("%lld",&a[i]),l+=a[i]*i,ans+=a[i];
    int t;
    scanf("%lld",&t);ans+=t;
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
    if(l<0){printf("impossible");return 0;}
    for(int i=1;i<=n;i++)
    {
        if(b[i]*i<=l) l-=b[i]*i,ans+=(b1[i]=b[i]);
        else {b1[i]=l/i;ans+=b1[i];l-=b1[i]*i;break;}
    }
    for(int i=n;i;i--)
    {
        if(a[i]*i<=l) l-=a[i]*i,ans-=(a1[i]=a[i]);
        else {a1[i]=l/i;ans-=a1[i];l-=a1[i]*i;break;}
    }
```

$a1,b1$ 记录了选择了多少。

背包可以写成函数的形式并使用二进制优化。

```cpp
void ins(ll s,ll v,ll w)//s ->数量，v ->体积，w ->贡献
{
    s=min(s,n*2+1);
    if(v>0)
    {
        int c=1;
        for(;c+c<s;c<<=1,v<<=1,w<<=1);
        while(1)
        {
            for(int i=k-v;i>=0;i--) f[i+v]=max(f[i+v],f[i]+w);
            s-=c;
            if(c==1) break;
            c>>=1,v>>=1,w>>=1;
        }
        if(s>0)
        {
            v*=s,w*=s;
            for(int i=k-v;i>=0;i--) f[i+v]=max(f[i+v],f[i]+w);
        }
    }
    else
    {
        v=-v;
        int c=1;
        for(;c+c<s;c<<=1,v<<=1,w<<=1);
        while(1)
        {
            for(int i=v;i<=k;i++) f[i-v]=max(f[i-v],f[i]+w);
            s-=c;
            if(c==1) break;
            c>>=1,v>>=1,w>>=1;
        }
        if(s>0)
        {
            v*=s,w*=s;
            for(int i=v;i<=k;i++) f[i-v]=max(f[i-v],f[i]+w);
        }
    }
}
```

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long

const int maxn=505;

ll l,n,m,k,ans;
ll a[maxn],b[maxn],a1[maxn],b1[maxn];
ll f[maxn*maxn*2];

void ins(ll s,ll v,ll w)
{
    s=min(s,n*2+1);
    if(v>0)
    {
        int c=1;
        for(;c+c<s;c<<=1,v<<=1,w<<=1);
        while(1)
        {
            for(int i=k-v;i>=0;i--) f[i+v]=max(f[i+v],f[i]+w);
            s-=c;
            if(c==1) break;
            c>>=1,v>>=1,w>>=1;
        }
        if(s>0)
        {
            v*=s,w*=s;
            for(int i=k-v;i>=0;i--) f[i+v]=max(f[i+v],f[i]+w);
        }
    }
    else
    {
        v=-v;
        int c=1;
        for(;c+c<s;c<<=1,v<<=1,w<<=1);
        while(1)
        {
            for(int i=v;i<=k;i++) f[i-v]=max(f[i-v],f[i]+w);
            s-=c;
            if(c==1) break;
            c>>=1,v>>=1,w>>=1;
        }
        if(s>0)
        {
            v*=s,w*=s;
            for(int i=v;i<=k;i++) f[i-v]=max(f[i-v],f[i]+w);
        }
    }
}

signed main()
{
    scanf("%lld%lld",&n,&l);
    for(int i=n;i;i--) scanf("%lld",&a[i]),l+=a[i]*i,ans+=a[i];
    int t;
    scanf("%lld",&t);ans+=t;
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
    if(l<0){printf("impossible");return 0;}
    for(int i=1;i<=n;i++)
    {
        if(b[i]*i<=l) l-=b[i]*i,ans+=(b1[i]=b[i]);
        else {b1[i]=l/i;ans+=b1[i];l-=b1[i]*i;break;}
    }
    for(int i=n;i;i--)
    {
        if(a[i]*i<=l) l-=a[i]*i,ans-=(a1[i]=a[i]);
        else {a1[i]=l/i;ans-=a1[i];l-=a1[i]*i;break;}
    }
    m=n*n,k=m*2;
    memset(f,0xcf,sizeof(f));
    f[m]=0;
    for(int i=1;i<=n;i++)
    {
        if(b1[i]) ins(b1[i],-i,-1);
        if(b[i]-b1[i]) ins(b[i]-b1[i],i,1);
        if(a1[i]) ins(a1[i],-i,1);
        if(a[i]-a1[i]) ins(a[i]-a1[i],i,-1);
    }
    if(l>m||f[m+l]<-m){printf("impossible");return 0;}
    else printf("%lld",ans+f[m+l]);
}
```

记得全开 `long long`。

---

## 作者：_fairytale_ (赞：3)

主要讲一下证明。

首先全拿走，设拿走物品的总重量为 $S$。若 $S>l$ 则不断放回重量最大的；若 $S\le l-m$ 则不断放回重量最小的，最终一定会使 $S$ 落在 $(l-m,l]$ 内，这是因为物品重量的绝对值 $\le m$。

接下来我们通过加入和放回一些物品把 $S$ 调到 $l$。可以通过“ $S>l$ 就减，$S<l$ 就加”的方式重排加入和放回的顺序把 $S$ 始终控制在 $(l-m,l+m)$ 内。

接下来我们证明同一个 $S$ 出现两次一定不优，如果出现两次，那么这两次之间所有加入放回的动作形成一个环，我们可以把这个环平移到最开始，于是只需证 $S$ 第一次落在 $(l-m,l]$ 的数值出现两次一定不优。考虑反证，如果更优，那么这个环中加入的物品比拿出的物品更多，而我们把 $S$ 调回 $l$ 的过程，使用的是拿出物品最少的办法。如果存在这样一个环，那么把 $S$ 调回 $l$ 的过程再接上这个环，拿出的物品会变得更少，矛盾。

因为 $(l-m,l+m)$ 中的每个 $S$ 最多出现一次，所以调整过程中每个物品最多加入/放回 $\mathcal m$ 次（假设是加入，那么只会分别在 $(l-m,l)$ 加入一次，反之亦然），每次对背包大小的影响最多为 $m$，因此背包大小是 $m^2$ 的，接下来跑多重背包即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mid ((l+r)>>1)
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
using namespace std;
template<class _T>
void ckmax(_T &x,_T y) {
	x=max(x,y);
}
int F[180100],*f=F+90050;
int m,L;
int A[800],*a=A+400;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>m>>L;
	rep(i,-m,m)cin>>a[i];
	int S=0,num=0;
	rep(i,-m,m)S+=a[i]*i,num+=a[i];
	vector<pii>V;
	auto add=[&](int w,int num,int op)->void {
		if(num==0)return;
		for(int i=1;i<=num;i<<=1)V.push_back({w*i,op*i}),num-=i;
		if(num)V.push_back({w*num,op*num});
	};
	{
		int d=(S>L?1:-1);
		for(int i=m*d; i!=0; i-=d) {
			int l=0,r=a[i],res=a[i];
			while(l<=r) {
				if(d==1?S-mid*i<=L:S-mid*i>L-m)res=mid,r=mid-1;
				else l=mid+1;
			}
			S-=res*i,num-=res;
			add(i,res,1);
			add(-i,a[i]-res,-1);
		}
		for(int i=-m*d; i!=0; i+=d)add(-i,a[i],-1);
		if(S<=L-m||S>L)return cout<<"impossible\n",0;
	}
	memset(F,-0x3f,sizeof F);
	f[S-L]=num;
	for(pii t:V) {
		int d=(t.fi<0?-1:1);
		for(int i=m*m*d;i!=-m*m*d&&abs(i-t.fi)<=m*m;i-=d)ckmax(f[i],f[i-t.fi]+t.se);
	}
	if(f[0]>=0)cout<<f[0]<<'\n';
	else cout<<"impossible\n";
	return 0;
}
```

---

## 作者：ty_mxzhn (赞：3)

典题。

先把全部选完。根据当前总和和目标总和的大小关系，贪心退掉尽量少的物品使得总和在 $[l-m,l]$ 之间。

考虑此时我们既可以拿没选完的物品，也可也退掉已经选的物品，但是显然单个物品选或退的个数不会很多。具体的，不会超过 $m^2$ 个选或退。

一种方法是二进制分组维护多重背包即可，时间复杂度 $O(m^3\log m)$。但是常数很小，如果值域拉大常数就会更小，近乎无法卡。

也可以单调队列优化，不过码量稍大。

---

