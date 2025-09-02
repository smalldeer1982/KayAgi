# [GCJ 2008 #1B] Number Sets

## 题目描述

你有一个连续整数序列。你希望将它们分组为若干集合。

给定一个区间和一个整数 $P$。最初，区间内的每个整数各自属于一个集合。

然后，你会考虑区间内的每一对整数。如果这两个整数有一个不小于 $P$ 的质因数，则将这两个整数所在的集合合并。

最终，这个过程中会剩下多少个不同的集合？

## 说明/提示

**小数据集（10 分，测试集 1 - 可见）**

- $1 \leq C \leq 10$
- $1 \leq A \leq B \leq 1000$
- $2 \leq P \leq B$

**大数据集（25 分，测试集 2 - 隐藏）**

- $1 \leq C \leq 100$
- $1 \leq A \leq B \leq 10^{12}$
- $B \leq A + 1000000$
- $2 \leq P \leq B$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
10 20 5
10 20 3```

### 输出

```
Case #1: 9
Case #2: 7```

# 题解

## 作者：bssmessi (赞：0)

注意到 $B-A\le 10^{6}$，所以区间内任意两数的最大质因数一定小于 $10^6$。所以我们考虑先把质数筛出来然后枚举每个大于 $P$ 的质数，合并集合考虑用并查集维护。

注意：做合并操作时一定要注意枚举同一个质因数一定要向一个方向合并，我最先就因为这个 T 掉了。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int T,a,b,p,ans,tot,fa[N],isp[N],pri[N];
int find(int x){
	if(fa[x]==x) return fa[x];
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fy]=fx;
}
signed main(){
	cin>>T;
	for(int i=2;i<N;i++){
		if(!isp[i]) pri[++tot]=i;
		for(int j=1;j<=tot&&i*pri[j]<N;j++){
			isp[i*pri[j]]=1;
			if(i%pri[j]==0) break;
		}
	}
	for(int o=1;o<=T;o++){
		cin>>a>>b>>p;ans=0;
		for(int i=0;i<=b-a;i++) fa[i]=i;
		for(int i=1;i<=tot;i++){
			if(pri[i]<p) continue;
			int k=ceil(a*1.0/pri[i]);
			for(int j=k*pri[i];j<=b;j+=pri[i]) merge(k*pri[i]-a,j-a);
		}
		for(int i=0;i<=b-a;i++) if(fa[i]==i) ans++;
		cout<<"Case #"<<o<<": "<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：xy_mc (赞：0)

一道非常简单的并查集模板（恕我提交了 $6$ 次，dalao 勿喷

首先我们很容易想到两个两个枚举去合并，但是这样的时间复杂度太大了，超过了 $O(TL^2)$（$L$ 是区间长度），直接 $T$ 飞了 QwQ。

再仔细想一下，$A,B \le 10^{12}$ 虽然很大，但是它们的质因数显然不超过 $\sqrt{B} \le 10^{6}$，所以我们可以利用线性筛筛出 $[2,10^6]$ 之间的质数，再把符合条件的质数的倍数合并即可，至于有些数可能多次被合并这种问题，强大的并查集可以帮我们处理。

注意：十年 OI 一场空，不开 long long 见祖宗。

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=(y);++i)
#define per(i,x,y) for(int i=x;i>=(y);--i)
typedef long long ll;
using namespace std;
const int N=1e6+1000;

ll l,r,op;
bool vis[N];
int p[N],cnt;
int f[N],ct;

void init(){   //线性筛
	rep(i,2,N-10){
		if(!vis[i]) p[++cnt]=i;
		for(int j=1;j<=cnt&&p[j]*i<=N-10;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}

int find(int x){   //寻找祖先
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}

void merge(int x,int y){  //合并
	int fx=find(x),fy=find(y);
	if(fx!=fy) f[fy]=fx;
}

void solve(){
	ct++;
	cin>>l>>r>>op;
	rep(i,1,r-l+1) f[i]=i;  //由于目标数字过大，会超内存，所以用第几个数来代替那个数。
	rep(i,1,cnt){
		if(p[i]<op) continue;  //不符合要求。
		ll tot,cs; //一定要开 long long，不然下面乘的时候会超int，就会出现负数下表，从而 RE。
		tot=cs=ceil(l*1.0/p[i]); //算出从 p[i] 的第几个倍数开始再区间范围内。
		while(p[i]*tot<=r){
			merge(p[i]*cs-(l-1),p[i]*tot-(l-1)); //合并
			tot++;
		}
	}
	int ans=0;
	rep(i,1,r-l+1){   //判断还剩几个集合
		if(f[i]==i){ 
			ans++;
		}
	}
	printf("Case #%d: %d\n",ct,ans);
}

int main(){
	int t;
    cin>>t;
	init();
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：chen_zhe (赞：0)

本题解来自于[《挑战程序设计竞赛》](https://www.luogu.com.cn/training/813583)。

---

首先因为这是一个集合合并的问题，所以貌似可以使用并查集求解。如果对区间内的任意两个数查询是否包含不小于 $P$ 的公共质因数，每一次查询由于需要分解质因数所以需要花费 $O(\sqrt{B})$ 的时间。因此，整个算法的时间复杂度就是 $O((B - A)^2 \sqrt{B})$ 。虽然可以通过 Small 数据，但是无法通过 Large 数据。

我们注意到 Large 有一个限制条件是 $B - A \leq 1000000$ 。如果满足 $A \leq a \leq b \leq B$ 的整数 $a$ ， $b$ 有公共质因数 $p$ ，那么 $p$ 一定能整除 $b - a$ 。由于 $B - A \leq 1000000$ ，因此 $p$ 也不会超过 $1000000$ 。

当 $a$ 和 $b$ 有公共质因数 $p$ 时， $a$ 和 $b$ 都是 $p$ 的倍数。因此，不需要尝试 $[A, B]$ 中所有的数对，只需要遍历所有可能的质因数 $p$ ，对每一个 $p$ 合并其所有倍数，就可以更加高效地求得答案。在合并时，从不小于 $A$ 的最小的 $p$ 的倍数 $((A + p - 1) / p \times p)$ 开始，不断枚举 $p$ 的倍数直到不超过 $B$ 的最大的 $p$ 的倍数 $(B / p \times p)$ ，并把这些数所在的集合合并起来。结合之前对区间筛法和并查集复杂度的分析，可以得出的整个算法的复杂度是 $O(B - A)$ 。

```cpp
typedef long long ll;

int prime[1000000]; // 不超过1000000的第i个的素数
int p;              // 素数的个数

// 输入
ll A, B, P;

void solve() {
    int len = B - A + 1;
    init_union_find(len); // 初始化并查集

    for (int i = 0; i < p; i++) {
        // 对不小于P的素数进行处理
        if (prime[i] >= P) {
            // 不小于A的最小的prime[i]的倍数
            ll start = (A + prime[i] - 1) / prime[i] * prime[i];
            // 不大于B的最大的prime[i]的倍数
            ll end = B / prime[i] * prime[i];

            for (ll j = start; j <= end; j += prime[i]) {
                // start和j属于同一个集合
                unite(start - A, j - A);
            }
        }
    }

    int res = 0;
    for (ll i = A; i <= B; i++) {
        // find(i) == i时，i就是并查集的根
        // 集合的个数等于根的个数
        if (find(i - A) == i - A) res++;
    }
    printf("%d\n", res);
}
```

---

