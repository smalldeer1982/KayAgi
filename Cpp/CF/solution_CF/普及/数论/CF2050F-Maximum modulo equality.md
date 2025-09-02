# Maximum modulo equality

## 题目描述

给你一个长度为 $n$ 的数组 $a$ 和 $q$ 次查询。  
每次查询给定两个数 $l$ 和 $r$，求出最大的 $m$ 使得 $a_l \bmod m = a_{l + 1} \bmod m = \dots = a_r \bmod m$，其中 $a \bmod b$ 是 $a$ 除以 $b$ 的余数。  
**特别的，当 $m$ 可能是无限大时，请输出 $0$。**

## 样例 #1

### 输入

```
3
5 5
5 14 2 6 3
4 5
1 4
2 4
3 5
1 1
1 1
7
1 1
3 2
1 7 8
2 3
1 2```

### 输出

```
3 1 4 1 0 
0 
1 6```

# 题解

## 作者：Determination_Y (赞：9)

[Cnblogs](https://www.cnblogs.com/Sundar-2022/p/18591483)

### 【题意简述】

你有一个长度为 $n$ 的数组 $a$。

每一次询问给定 $l,r$，寻找最大的 $m$ 使得 $a_l$ 到 $a_r$ 的所有数对 $m$ 同余，

### 【前置数学芝士】

首先是一个非常 Naive 的结论，请自行感性证明：设 $a>b$，$a$ 和 $b$ 对 $a-b$ 同余。

> 理性证明：
>
> 设 $p=a-b$，$a=kp+q$
>
> 那么 $b=a-(a-b)=a-p=(k-1)p+q$
>
> 他们对 $p$ 同余（都是 $q$）

然后另一个非常 Naive 的结论，请自行感性证明：设 $a>b$，$a$ 和 $b$ 对 $a-b$ 的所有因数同余。

> 理性证明：
>
> 设 $p=a-b$，$a=kp+q$，$b=(k-1)p+q$
>
> 设 $p$ 的这个因数为 $p_0$
>
> 因为 $kp$ 和 $(k-1)p$ 可以被 $p$ 整除，所以这两个数也可以被 $p_0$ 整除，同余于 $p_0$
>
> 而且 $q$ 和 $q$ 同余于 $p_0$
>
> 所以 $a$ 和 $b$ 的两部分分别同余于 $p_0$
>
> 所以 $a$ 和 $b$ 同余于 $p_0$

### 【思路】

首先 $a_l$ 到 $a_r$ 同余可拆分成：

| 限制 | 结论 |
| ---- | ---- |
| $a_l,a_{l+1}$ 同余     | $m$ 是 $\vert a_l-a_{l+1} \vert$ 的因数     |
| $a_{l+1},a_{l+2}$ 同余 | $m$ 是 $\vert a_{l+1}-a_{l+2}\vert$ 的因数 |
| $…$                    | $…$                               |
| $a_{r-2},a_{r-1}$ 同余 | $m$ 是 $\vert a_{r-2}-a_{r-1}\vert$ 的因数 |
| $a_{r-1},a_r$ 同余     | $m$ 是 $\vert a_{r-1}-a_r\vert$ 的因数     |

然后就出结论了，$m=\gcd(\vert a_l-a_{l+1}\vert ,\vert a_{l+1}-a_{l+2}\vert ,…,\vert a_{r-2}-a_{r-1}\vert ,\vert a_{r-1}-a_r\vert )$。

用 ST 表搞一搞，特判一下区间长度为 $1$。

### 【Code】

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,q,a[200005],s[200005];
int l,r,Log[200005];

struct ST_map{
	int Gcd[200005][21];
	void Init(){
		for(int i=1;i<=n-1;i++) Gcd[i][0]=s[i];
		for(int i=1;i<=20;i++){
			for(int j=1;j<=n-1;j++){
				Gcd[j][i]=__gcd(Gcd[j][i-1],Gcd[min(j+(1<<(i-1)),n)][i-1]);
			}
		}
	}
	int Query(int l,int r){
		int logx=Log[r-l+1];
		return __gcd(Gcd[l][logx],Gcd[r-(1<<logx)+1][logx]);
	}
}ST;

void Main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++)  s[i]=abs(a[i+1]-a[i]);
	ST.Init();
	while(q--){
		scanf("%d%d",&l,&r);
		if(l==r) printf("0 ");
		else     printf("%d ",ST.Query(l,r-1));
	}puts("");
} 

int T;
int main()
{
	int cnt=0,last=2;
	for(int i=2;i<=200000;i++){
		if(i==last){
			cnt++;
			last*=2;
		}Log[i]=cnt;
	}
	scanf("%d",&T);
	while(T--) Main();
	return 0;
}
```

### 【后记】

祝贺我自己，在上蓝前的最后一场 Div.3 AK。

两发罚时全是数组开小，乐。

以后就打不了了。

---

## 作者：chenxi2009 (赞：3)

# 思路
有趣的类 RMQ 题。

$a_i\equiv a_{i+1}\pmod{m}$ 和 $m\mid(a_{i+1}-a_i)$ 互为充要条件，那么可以发现题目要求等价于使 $m\mid(a_{l+1}-a_l),m\mid(a_{l+2}-a_{l+1}),m\mid(a_{l+3}-a_{l+2}),\cdots,m\mid(a_r-a_{r-1})$。特别地，若 $a\mid b$ 中 $b$ 为负数，认为其等价于 $a\mid -b$。

题目要求 $m$ 是这些数的因数，又要求 $m$ 最大，那这不就是求**最大公因数**吗？每次求相邻两项差序列中的连续区间的最大公因数，可以用 ST 表存储连续一段区间的最大公因数，处理方法同普通的 RMQ 问题。

时间复杂度 $O(\sum (n\log n+q)\log\max a)$，其中单次辗转相除求最大公因数的时间复杂度为 $O(\log \max a)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,q,a[200001],l,r,st[200001][19],lg[200001];
inline int log(int x){
	return lg[x];
} 
inline int pow(int x){
	return 1 << x;
}
inline void pre(){//对数预处理 
	lg[1] = 0;
	for(int i = 2;i <= 200000;i ++) lg[i] = lg[i >> 1] + 1;
}
inline void stpre(){
	for(int i = 1;i < n;i ++) st[i][0] = abs(a[i + 1] - a[i]);//底层单个差分为自身的 gcd 
	for(int i = 1;i <= 18;i ++) for(int j = 1;j <= n - pow(i) + 1;j ++) st[j][i] = __gcd(st[j][i - 1],st[j + pow(i - 1)][i - 1]);//ST 表倍增 gcd 
}
inline int ask(int l,int r){//ST 表询问，左右两半侧的 gcd  
	int len = r - l + 1;
	return __gcd(st[l][log(len)],st[r - pow(log(len)) + 1][log(len)]);
}
int main(){
	pre();
	scanf("%d",&T);
	while(T --){
		scanf("%d%d",&n,&q);
		for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
		stpre();
		for(int i = 1;i <= q;i ++){
			scanf("%d%d",&l,&r);
			printf("%d ",(l != r) * ask(l,r - 1));//特判 l=r，根据样例得出应该输出 0 
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：AK_400 (赞：1)

注意到对于

$$\forall x,y,m\in \mathbb Z^+$$

若

$$x\equiv y\pmod m$$

有

$$x-y\equiv 0\pmod m$$

于是对于

$$\forall x,y,z,m\in \mathbb Z^+$$

若

$$x-y\equiv y-z\equiv 0\pmod m$$

有

$$x-z\equiv 0\pmod m$$

于是我们把这个数组作差分，得到数组 $d(d_i=a_i-a_{i-1})$，对于区间 $[l,r]$，$\gcd(d_{l+1},d_{l+2},\cdots,d_r)$ 即为所求。特别的，若 $l=r$ 则输出 `0`。区间 $\gcd$ 可以用 st 表来做。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
int a[200005],d[200005],st[200005][18],lg[200005];
int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}
void init(){
    for(int i=1;i<18;i++){
        for(int j=2;j+(1<<i)-1<=n;j++){
            st[j][i]=gcd(st[j][i-1],st[j+(1<<i-1)][i-1]);
        }
    }

}
int qu(int l,int r){
    return gcd(st[l][lg[r-l+1]],st[r-(1<<lg[r-l+1])+1][lg[r-l+1]]);
}
void slv(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i],d[i]=abs(a[i]-a[i-1]),st[i][0]=d[i];
    init();
    while(q--){
        int l,r;
        cin>>l>>r;
        if(l==r)cout<<0<<" ";
        else cout<<qu(l+1,r)<<" ";
    }
    cout<<endl;
    return;
}   
signed main(){
    for(int i=2;i<=2e5+1;i++)lg[i]=lg[i>>1]+1;
    int t;cin>>t;while(t--)
    slv();
    return 0;
}
```

---

## 作者：Drifty (赞：1)

### Solution

注意到性质：合法的模数 $m$ 一定能够整除区间中任意两个数的差。由于我们期望 $m$ 尽可能大，那么 $m$ 就是区间差分的 $\gcd$。[Code。](https://mirror.codeforces.com/contest/2050/submission/295888393)

---

## 作者：Kendieer (赞：1)

[**\[传送门\]**](/problem/CF2050F)

## 题意

> 给定一个长度为 $n$ 序列 $a$，要求将其查询 $q$ 次，对于每次查询，求最大化 $m$，使得 $a_l\bmod m=a_{l+1}\bmod m = a_{l+2}\bmod m = \cdots = a_{r}\bmod m$。

## 思路构建

对于任意两数 $x,y$，若对同一模数 $m$ 取模，则满足 $x=k_1 m+b_1,y=k_2 m+b_2,k_1,k_2\in N$。若两数相等，即 $b_1 = b_2$，则满足 $x-y = (k_1-k_2)m,k_1-k_2\in N$，联立可得 $\max_m = |x-y|$。

对于三个数 $x,y,z$ 的情况下，则需满足 $m=\gcd {(|x-y|,|y-z|,|x-z|)}$。

由此我们可以延伸到 $n$ 个数。

又因为 $\gcd(a,b,c)=\gcd(\gcd(a,b),c)$，所以，对于每次查询，我们只需每次查询 $\gcd{_{i=l+1}^r{|a_i-a_{i-1}|}}$。

区间查询可以用 **ST 表** 或者 **线段树** 维护即可。

记得特判 $l=r$ 的情况。

## 参考代码

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i,a,b) for(ll i = (a);i < (b);i++)
#define repr(i,a,b) for(ll i = (b) - 1;i>= (a);i--)
#define elif else if
#define reflush cout.flush()
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
const ll inf = 0x3f7f7f7f7f7f7f7f;

template <typename T>
void to_max(T &x,T y){ x = max(x,y); }
template <typename T>
void to_min(T &x,T y){ x = min(x,y); }

ll qread(){
    ll r = 0,s = 1,ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    if (ch == '-') ch = getchar(),s = -1;
    while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0',ch = getchar();
    return r * s;
}

char readChar(){
    int ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
    return ch;
}

const string QWrite = "0123456789ABCDEF";
void qwrite(ll x,int t = 10){
    if (x>=t) qwrite(x/t,t);
    putchar(QWrite[x%t]);
}

const int maxn = 2e5 + 7;
const int mod = 998244353;
struct Node {};

ll sgt[maxn << 2],arr[maxn];

inline int lst(int idx){return idx << 1;}
inline int rst(int idx){return idx << 1 | 1;}

void build(int l,int r,int idx,ll val,int goal){
    if (l == r && l == goal){
        sgt[idx] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (goal <= mid) {
        build(l,mid,lst(idx),val,goal);
    } else {
        build(mid +1,r,rst(idx),val,goal);
    }
    sgt[idx] = gcd(sgt[lst(idx)],sgt[rst(idx)]);
}

ll query(int l,int r,int idx,int rl,int rr){
    if (l == rl && r == rr){
        return sgt[idx];
    }
    int mid = (l+r)/ 2;
    ll ans = 0;
    if (rl <= mid){
        ans = gcd(ans,query(l,mid,lst(idx),rl,min(rr,mid)));
    }
    if (rr > mid){
        ans = gcd(ans,query(mid+1,r,rst(idx),max(rl,mid+1),rr));
    }
    return ans;
}

void solve(){
    int n = qread(), q = qread();
    rep(i,0,n << 2 | 1){
        sgt[i] = 0;
    }
    rep(i,1,n+1){
        arr[i] = qread();
        build(1,n,1,arr[i] - arr[i-1],i);
    }
    
    rep(i,0,q){
        int l = qread(),r = qread();
        if (l == r){
            cout << 0 << " ";
        } else {
            cout << query(1,n,1,l+1,r) << " ";
        }
    }
    cout << endl;
}

int main(){
    int n = qread();
    while(n--)
    solve();
    return 0;
}
```

---

## 作者：Meickol (赞：0)

首先，当区间长度为 $1$ 时，答案显然为 $0$。

当区间长度为 $2$ 时：由 $a_l \bmod m = a_{l+1} \bmod m$，可得 $(a_l-a_{l+1}) \bmod m =0$，即 $km=(a_l-a_{l+1})$，即 $a_l-a_{l+1}$ 的因子都可以作为答案，但是显然当 $k$ 取 $1$ 时 $m$ 最大，同时我们要避免 $m$ 为负数，即最大的 $m$ 取值为 $|a_l-a_{l+1}|$。

当区间为 $[l,r]$ 时，可以考虑合并区间长度为 $2$ 的区间，要保证同时满足，即答案为：
$$
(|a_l-a_{l+1}|,|a_{l+1}-a_{l+2}|,\cdots ,|a_{r-1}-a_{r}|)
$$
静态区间查询，可以使用 ST 表维护。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
const int N=2e5+5;
int n,q;
int a[N],f[N][25];
void init(){
	rep(i,1,n-1) f[i][0]=abs(a[i]-a[i+1]);
	rep(j,1,20){
		for(int i=1;i+(1<<j)-1<=n-1;i++){
			f[i][j]=__gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
}
int query(int l,int r){
	int k=log2(r-l+1);
	return __gcd(f[l][k],f[r-(1<<k)+1][k]);
}
void solve(){
	cin>>n>>q;
	rep(i,1,n) cin>>a[i];
	init();
	while(q--){
		int l,r;
		cin>>l>>r;
		if(l==r) cout<<0<<" ";
		else cout<<query(l,r-1)<<" ";
	}
}
```

---

## 作者：HHC883 (赞：0)

# 题目分析
题目要求我们找到最大的 $m$，使得

$$a_l \equiv a_{l+1} \equiv \cdots \equiv a_r \pmod m$$

由同余的性质，上式的充要条件是 $\forall l \le i < r , m \mid a_i - a_{i+1}$。这便要求 $m$ 是 $a_l-a_{l+1} , a_{l+1} - a_{l+2} , \cdots , a_{r-1} - a_r$ 的公因数，于是 $m$ 的最大值就是 $(a_l - a_{l+1} , a_{l+1} - a_{l+2} , \cdots , a_{r-1} - a_r)$，即求出区间最大公因数。由于是静态查询，用 ST 表维护即可。
# 参考代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int t;
int n,q,a[(int)2e5+5];
int st[(int)2e5+5][25];
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
void init(){
	for(int i=1;i<=n-1;i++) st[i][0]=abs(a[i]-a[i+1]);
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)-1<=n-1;i++){
			st[i][j]=gcd(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
}
int query(int l,int r){
	int maxlog=log(r-l+1)/log(2);
	return gcd(st[l][maxlog],st[r-(1<<maxlog)+1][maxlog]);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>q;
		for(int i=1;i<=n;i++) cin>>a[i];
		init();
		int l,r;
		while(q--){
			cin>>l>>r;
			if(l==r) cout<<"0 ";
			else cout<<query(l,r-1)<<' ';
		}
		cout<<'\n';
	}
	return 0;
}

```

---

## 作者：shicj (赞：0)

## 0x00 题目翻译

有一个长度为 $n$ 的序列 $a$ 和 $q$ 个询问，每个询问给出一个区间 $l,r$ 要求查询最大的 $m$ 使得这个区间里所有数字模 $m$ 的结果相同（如果 $m$ 可以取得无穷大，输出 $0$）。

## 0x01 解题思路

这里要求余数全部相同，这样入手不好分析，那么尝试反向思考：**如果余数已经相同，$m$ 已经确定，那么序列会有什么性质？**

设原序列为 $a_1,a_2,\cdots,a_n$，那么可以表示为 $k_1m+x,k_2m+x,\cdots,k_nm+x$，其中 $x$ 是那个相同的余数。

观察到每一项带有相同的 $x$，尝试将它消掉，可以将相邻两项做差，求出一个差分序列 $b$，即 $0,\vert a_1-a_2\vert ,\vert a_2-a_3\vert ,\cdots,\vert a_{n-1}-a_n\vert $，也就是 $0,\vert k_1-k_2\vert m,\vert k_2-k_3\vert m,\cdots,\vert k_{n-1}-k_n\vert $，这时，就可以用 $b$ 的区间最大公约数求出最大的 $m$（序列 $b$ 开头的 $0$ 只是在写代码时和 $l,r$ 对齐位置，没有意义）。

## 0x02 算法实现

似乎大部分人用的是 ST 表，但这里我用的是线段树（因为不会 ST 表），只有查询，没有修改，是比较好写的。

## 0x03 易错要点

1. 输入的查询区间不是 $b$ 中的区间，应为 $l+1,r$。
2. 注意当 $l=r$ 时要特判，否则你的实际查询会 $l+1>r$ 导致 RE。
3. 建树时可以只用 $2,n$ 的一段数值传入，但同样应注意 $n=1$ 的情况。

## 0x04 程序代码

![](https://cdn.luogu.com.cn/upload/image_hosting/p85jre0h.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/ml9rzquc.png)

---

## 作者：HYdroKomide (赞：0)

### 题意：

给定一个序列，每次询问求区间同余最大模数。

### 思路：

发现一些有趣的性质：考虑一个区间，如果所有数除以某个模数的余数相同，所有数之间的差一定是这个模数的倍数。反之我们有：使得区间内所有数同余的模数是区间差分的最大公约数。

区间 gcd 可以被线段树合并，于是开线段树，每次询问直接查询即可（注意区间内所有数相等时答案是 $0$）。复杂度 $O(n\log n)$。

### 程序如下：

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e5+5;
int T,n,q,a[N];
int bet[N],t[N*4];
int gcd(int a,int b){
	if(a==0&&b==0)return 0;
	return __gcd(a,b);
}
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
void pushup(int x){t[x]=gcd(t[ls(x)],t[rs(x)]);}
void build(int x,int l,int r){
	if(l==r){
		t[x]=bet[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	pushup(x);
}
int query(int x,int l,int r,int L,int R){
	if(L<=l&&R>=r)return t[x];
	int mid=(l+r)>>1;
	if(L<=mid&&R<=mid)return query(ls(x),l,mid,L,R);
	else if(L>mid&&R>mid)return query(rs(x),mid+1,r,L,R);
	else return gcd(query(ls(x),l,mid,L,R),query(rs(x),mid+1,r,L,R));
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(i>1)bet[i-1]=abs(a[i]-a[i-1]);
		}
		if(n>1)build(1,1,n-1);
		while(q--){
			int l,r;
			scanf("%d%d",&l,&r);
			if(l==r)printf("0 ");
			else printf("%d ",query(1,1,n-1,l,r-1));
		}
		puts("");
	}
	return 0;
}
```

### THE END

---

## 作者：The_foolishest_OIer (赞：0)

对数列 $a$ 的相邻两项做差，可得新的 $b$ 数组，每次查询就是 $b_l$ 到 $b_{r-1}$ 的最大公因数。

ST 表维护即可。

时间复杂度 $O(n\log^2 n+q\log n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 10;
int T,n,q;
int a[N],b[N],lg[N];
int st[N][25];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void init(){
	for (int i = 2 ; i <= 200000 ; i++)
		lg[i] = lg[i >> 1] + 1;
}
void st_init(){
	for (int i = 1 ; i < n ; i++)
		st[i][0] = b[i];
	for (int j = 1 ; (1 << j) < n ; j++)
		for (int i = 1 ; i <= n - (1 << j) ; i++)
			st[i][j] = __gcd(st[i][j - 1],st[i + (1 << (j - 1))][j - 1]);
}
int query (int l,int r){
	int x = lg[r - l + 1];
	return __gcd(st[l][x],st[r - (1 << x) + 1][x]);
} ST 表
void solve(){
	cin >> n >> q;
	for (int i = 1 ; i <= n ; i++)
		cin >> a[i];
	for (int i = 1 ; i < n ; i++)
		b[i] = (int)abs(a[i] - a[i + 1]); // 得到 b 数组
	st_init();
	for (int i = 1 ; i <= q ; i++){
		int L,R;
		cin >> L >> R;
		if (L == R) cout << 0; // 特判
		else cout << query(L,R - 1);
		cout << ' ';
	}
	cout << endl;
}
signed main(){
	close();
	init();
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

