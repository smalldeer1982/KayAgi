# [Aboi Round 1] I なんです

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/r38iwta6.png)

## 题目描述

有一个长度为 $n$ 的序列 $\{a\}$，$q$ 次询问，每次给你一个区间 $[l,r]$，求该区间内所有长度为奇数的子序列的 $\gcd$ 的平方之积，答案对 $998244353$ 取模。

## 说明/提示

对于 $100\%$ 的数据，$1\leq n,q,a_i\leq10^5$。

本题采用捆绑测试，你需要通过一个子任务的所有测试点才能得到该子任务的分数。

| 子任务编号 | $n$ | $q$ | $a_i$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $\le20$ | $\le20$ | $\le10^5$ | / | $10$ |
| $2$ | $\le10^3$ | $\le10^3$ | $\le10^5$ | / | $10$ |
| $3$ | $\le3\times10^4$ | $\le3\times10^4$ | $\le10^5$ | / | $10$ |
| $4$ | $\le10^5$ | $\le10^5$ | $\le10^5$ | $\text{A}$ | $5$ | 
| $5$ | $\le10^5$ | $\le10^5$ | $\le300$ | / | $10$ |
| $6$ | $\le10^5$ | $\le10^5$ | $\le10^5$ | / | $55$ |

特殊性质 $\text{A}$：所有 $a_i$ 均相同。

## 样例 #1

### 输入

```
10 5
1 3 5 2 4 6 8 8 8 10
1 3
5 7
3 6
8 10
7 10```

### 输出

```
225
147456
230400
1638400
562036629```

## 样例 #2

### 输入

```
10 5
2 2 2 2 2 2 2 2 2 2
1 2
1 4
1 5
1 6
1 7```

### 输出

```
16
65536
301989884
932051910
299560064```

# 题解

## 作者：WorldMachine (赞：5)

有这样一个好想法：回滚莫队，维护奇数和偶数长度的答案，区间变长的时候奇数从偶数处转移，偶数从奇数处转移。不幸的是我不会转移，于是我想了一种更恶心的做法。

---

$\text{lcm}$ 就是对每个素因子的次数取 $\max$，$\gcd$ 就是对每个素因子的次数取 $\min$。

类比 min-max 反演，有：
$$
\text{lcm}(T)=\prod_{S\subseteq T,S\not=\varnothing}(\gcd(S))^{(-1)^{|S|-1}}
$$
要求所有长度为奇数的子序列的 $\gcd$ 的平方之积，即：
$$
\text{lcm}([l,r])\cdot\prod_{S\subseteq [l,r],S\not=\varnothing}\gcd(S)
$$
于是问题变成两部分：求区间 $\text{lcm}$，以及求区间内所有子序列的 $\gcd$ 之积。

---

第二部分，考虑根号分治。

对于 $p\le\sqrt V$，设区间 $[l,r]$ 内 $p$ 次数为 $k$ 的数个数为 $\text{cnt}_k$，那么 $p$ 的贡献（次数）为：
$$
\sum_{i=1}^{\lfloor\log_pV\rfloor}i\left(2^{\text{cnt}_i}-1\right)2^{\sum\limits_{j=i+1}^{\lfloor\log_pV\rfloor}\text{cnt}_j}
$$
预处理 $2$ 的次幂，注意到次数会很大所以记得对 $998244352$ 取模。对于每个 $p$ 可以花 $\mathcal O(\log V)$ 的时间获得这部分的答案，这部分时间复杂度为 $\mathcal O\left((n+q)\cdot\dfrac{\sqrt V}{\log V}\cdot\log V\right)=\mathcal O((n+q)\sqrt V)$。

对于 $p>\sqrt V$，性质是每一个 $a_i$ 至多会有一个这样的 $p$。莫队，设当前 $p$ 的出现次数为 $\text{cnt}_p$，那么 $p$ 的贡献为 $p^{2^{\text{cnt}_p}-1}$，那么当前的答案为：
$$
\prod_{p>\sqrt V}p^{2^{\text{cnt}_p}-1}=\dfrac{\prod\limits_{p>\sqrt V}p^{2^{\text{cnt}_p}}}{\prod\limits_{p>\sqrt V}p}
$$
考虑如何计算分子。

正常的做法是，维护 $\text{pow}_p=p^{2^{\text{cnt}_p}}$，区间扩大时直接将 $\text{pow}_p$ 平方顺便更新答案（所以还要维护一个 $\text{pow}^{-1}_p$），缩小时就寄了，所以要使用回滚莫队。

其实不用回滚莫队，设 $\text{pow}_{p,k}=p^{2^k}$，这个可以把 $2^k\bmod 998244352$ 预处理出来，再预处理每个素数的光速幂，当然 $\text{pow}_{p,k}^{-1}$ 也一样地搞，这样就可以使用普通莫队了，但不好说哪个更快。

upd：我好像学了个假的数据结构……上面的东西直接用指针数组搞出每个数要用到的值即可，总数是 $n$ 的。

第二部分时间复杂度为 $\mathcal O((n+q)\sqrt V+n\sqrt q)$。

---

尝试解决第一部分。有了第二部分的基础其实是简单的。

对于 $p\le\sqrt V$ 就是一个区间最大值，可以简单地做到 $\mathcal O((n+q)\sqrt V)$。

如果 $p>\sqrt V$，每个 $p$ 的次数至多为 $1$，大力做莫队即可。

第一部分时间复杂度为 $\mathcal O((n+q)\sqrt V+n\sqrt q)$。

---

结算：$n,m,V$ 均同级，时间复杂度为 $\mathcal O(n\sqrt n)$，常数不小，但别写太劣就能过。

代码应该不会很短，慢慢写。

---

## 作者：hyman00 (赞：2)

出题人对离散对数有什么执念吗，连续两个题都要用。

平方最后算，先拆贡献，容易发现

$$
\gcd(a_1,\dots,a_n)=\prod_{p^k|a_1,\dots,a_n}p
$$

因此统计所有素数幂在多少个子序列出现了即可。

考虑莫队，如何插入一个数，枚举他的所有素数幂的因子，假设它已经在区间内出现了 $k$ 次，则贡献是答案乘上 $p^{2^{\max(k-1,0)}}$，其中 $2^{\max(k-1,0)}$ 是 $k$ 个数中长度偶数的子序列个数。可以做到 $O(n^{1.5}\log^2n)$。

尝试去掉一个 log，上面的 2 的幂可以预处理，下面的可以用离散对数转成乘法计算，做到 $O(n^{1.5}\log n)$。

代码粘了一堆板子。

```c++
const int P=MOD,g=3;
namespace Math{
	unordered_map<int,int>pm(5000000);
	int ff[32000];
	vi pr;
	int b,c,n,tc;
	il int qp(int x,int y){
		int z=1;
		for(;y;(x*=x)%=P,y>>=1)if(y&1)(z*=x)%=P;
		re z;
	}
	il int _Log(int x){
		x=qp(x,P-2);
		for(int i=b;;i+=b){
			(x*=c)%=P;
			if(pm.count(x))re i-pm[x];
		}
	}
	void init(){
		b=500000;c=1;
		rept(i,1,b+1){
			(c*=g)%=P;
			pm[c]=i;
		}
		n=min((int)sqrt(P)+2,P);
		rept(i,2,n){
			if(!ff[i]){
				ff[i]=_Log(i);
				pr.pb(i);
			}
			for(int j:pr){
				if(i*j>=n)break;
				ff[i*j]=(ff[i]+ff[j])%(P-1);
				if(i%j==0)break;
			}
		}
		tc=_Log(P-1);
	}
	il int Log(int x){
		if(x<n)re ff[x];
		int y=P/x,z=P%x;
		if(z*2<=x)re (tc+Log(z)-ff[y]+P-1)%(P-1);
		re (Log(x-z)-ff[y+1]+P-1)%(P-1);
	}
}
const int N=100005,B=330;
int n,q;
int a[N],c[N],pw[N],ans[N],cx[N],icx[N];
vector<array<int,4>>qy;
vi tp[N],pr;
int isp[N];
il int qp(int x,int y){
	int z=1;
	for(;y;(x*=x)%=MOD,y>>=1)if(y&1)(z*=x)%=MOD;
	re z;
}
int tmp;
il void ins(int x){
	for(int i:tp[x]){
		(tmp+=cx[i]*pw[c[i]])%=(MOD-1);
		c[i]++;
	}
}
il void era(int x){
	for(int i:tp[x]){
		c[i]--;
		(tmp-=cx[i]*pw[c[i]])%=(MOD-1);
	}
}
void run(){
	Math::init();
	rept(i,2,N){
		if(!isp[i]){
			pr.pb(i);
			int ri=Math::Log(i);
			for(int j=i;j<N;j*=i){
				cx[j]=ri;
				for(int k=j;k<N;k+=j)tp[k].pb(j);
			}
		}
		for(int j:pr){
			if(i*j>=N)break;
			isp[i*j]=1;
			if(i%j==0)break;
		}
	}
	pw[0]=pw[1]=1;
	rept(i,2,N)pw[i]=pw[i-1]*2%(MOD-1);
	cin>>n>>q;
	rep(i,n)cin>>a[i];
	rep(i,q){
		int l,r;
		cin>>l>>r;
		l--;
		qy.pb({l/B,r,l,i});
	}
	sort(all(qy));
	tmp=1;
	int l=0,r=0;
	for(auto it:qy){
		while(l>it[2])ins(a[--l]);
		while(r<it[1])ins(a[r++]);
		while(l<it[2])era(a[l++]);
		while(r>it[1])era(a[--r]);
		ans[it[3]]=tmp;
	}
	rep(i,q)cout<<qp(g,MOD*2-4+ans[i]*2)<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--)
		run();
	re 0;
}

```

---

## 作者：UniGravity (赞：1)

首先 gcd 的平方是骗人的，因为求的是积，平方最后乘上即可。

有一个 gcd 的转化：

$$\gcd(S)=\prod_{p\in\mathbb{P}}\prod_{k\ge 1,\forall x\in S,p_i^k|x}p_i$$

验证一下可以发现这是对的。

考虑对每个质数 $p$ 统计答案。考虑枚举 $p,k$，判断区间 $[l,r]$ 内有多少个数是 $p^k$ 倍数（记为 $c$），根据组合数知识可得 $c$ 中选奇数或偶数个的方案数是相等的。因此可行的 $S$ 共 $2^{c-1}$ 个（$c=0$ 时特判一下）。

但若对所有质数都扫一遍整个数组枚举答案不太牛。考虑经典 trick：记 $V$ 表示值域上界，显然所有数都可以表示成若干个小于 $\sqrt V$ 的质数和最多一个大于 $\sqrt V$ 的质数的乘积。因此考虑根号分治。

大质数出现次数总和最多为 $n$，且对应的 $k$ 一定为 $1$，这个随便拿个莫队维护区间内的 $p^{(2^{cnt_p-1})}$ 就可以了。如果直接做可能是 $O(n\sqrt q\log V)$ 的，因为要快速幂。可以套个[离散对数板子](https://www.luogu.com.cn/problem/P11175)做到 $O(n\sqrt q)$。

小质数共有 $O(\frac{\sqrt V}{\log V})$ 个。枚举每个小质数，然后 $O(\log V)$ 枚举 $k$，先扫一遍数组做前缀和，然后每个询问就可以 $O(1)$ 查了。$\log V$ 消掉了，总的时间复杂度是 $O(q\sqrt V)$ 的。

设 $n,q,V$ 同阶，时间复杂度 $O(n\sqrt n)$。

```cpp
const int N=100005,B=320,P=998244353;
vector<int>pr;
bool np[N];
int n,q,a[N],mxp[N],pw2[N],lg[N];
int id[N],cnt[N],ans[N],res=0;
il void add(int x){
    x=mxp[x];if(!x)return;
    if(cnt[x])res=(res-1ll*lg[x]*pw2[cnt[x]-1]%(P-1)+P-1)%(P-1);
    cnt[x]++;
    res=(res+1ll*lg[x]*pw2[cnt[x]-1])%(P-1);
}
il void del(int x){
    x=mxp[x];if(!x)return;
    res=(res-1ll*lg[x]*pw2[cnt[x]-1]%(P-1)+P-1)%(P-1);
    cnt[x]--;
    if(cnt[x])res=(res+1ll*lg[x]*pw2[cnt[x]-1])%(P-1);
}

struct Q{
    int l,r,i;
    il friend bool operator<(Q &x,Q &y){
        if(id[x.l]!=id[y.l])return x.l<y.l;
        else return (id[x.l]&1)?(x.r<y.r):(x.r>y.r);
    }
}qr[N];

signed main(){
    BSGS::init(3,P);
    forto(i,2,B){
        if(!np[i])pr.eb(i);
        for(int j:pr){
            if(i*j>B)break;
            np[i*j]=1;
            if(i%j==0)break;
        }
    }
    n=read(),q=read();
    pw2[0]=1;forto(i,1,n)pw2[i]=pw2[i-1]*2%(P-1);
    int x,mx=0;
    forto(i,1,n){
        x=a[i]=read(),id[i]=i/B,mx=max(mx,a[i]);
        for(int j:pr)while(x%j==0)x/=j;
        if(x>1){
            if(!lg[x])lg[x]=BSGS::qry(x);
            mxp[i]=x;
        }
    }
    forto(i,1,q)qr[i].l=read(),qr[i].r=read(),qr[i].i=i;
    sort(qr+1,qr+q+1);
    int l=1,r=0;
    forto(i,1,q){
        while(l>qr[i].l)add(--l);
        while(r<qr[i].r)add(++r);
        while(l<qr[i].l)del(l++);
        while(r>qr[i].r)del(r--);
        ans[qr[i].i]=res;
    }
    int k;
    for(int p:pr){
        k=BSGS::qry(p);
        for(int pk=p;;pk*=p){
            cnt[0]=0;
            forto(i,1,n)cnt[i]=cnt[i-1]+(a[i]%pk==0);
            forto(i,1,q){
                x=cnt[qr[i].r]-cnt[qr[i].l-1];
                if(x)ans[qr[i].i]=(ans[qr[i].i]+1ll*k*pw2[x-1])%(P-1);
            }
            if(1ll*pk*p>mx)break;
        }
    }
    forto(i,1,q)printf("%lld\n",fpow(3,ans[i]*2%(P-1),P));
    return 0;
}
```

---

