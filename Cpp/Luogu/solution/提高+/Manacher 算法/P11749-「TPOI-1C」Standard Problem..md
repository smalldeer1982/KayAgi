# 「TPOI-1C」Standard Problem.

## 题目描述

你是某知名 CP 网站的比赛审核员，经常收到一些 standard 的投稿。

你已经使用了太多次「quite standard」和「somewhat standard」作为回复了，因此这次你决定换一些。

首先你写下了你对这道题的评价 $s$，这里 $s$ 是一个仅包含英文小写字母的字符串。为了让投稿者知道自己的题目有多 standard，你又将这个字符串 $s$ 粘贴了 $k-1$ 次。最终，你的评价形成了一个字符串 $t = s^k$。

投稿者定义一个回复的 _怪异度_ 是这个字符串里的回文子串数量。请你求出你写下的回复 $t$ 的怪异度。由于这个值可能很大，你只需要输出它对 $998244353$ 取模的结果。

**形式化的**，给定字符串 $s$ 和整数 $k$，求 $s^k$（字符串 $s$ 拼接 $k$ 次）有多少回文子串（位置不同即算作不同），模 $998244353$。

## 说明/提示

### 样例解释

对于第一组数据，$t = s^2 = \texttt{abababab}$，共有 $20$ 个回文子串。

对于第三组数据，输入的字符串是 $(\texttt{abaab})^6$。

### 数据范围

子任务 $1$ 为样例，不计分。

| 子任务 | 分数 | $n \le$ | $k \le$ |
| :----------: | :----------: | :----------: | :----------: |
| $2$ | $5$ | $2$ | $10^9$ |
| $3$ | $30$ | $3 \cdot 10^6$ | $3 \cdot 10^6$ |
| $4$ | $30$ | $2000$ | $10^9$ |
| $5$ | $35$ | $3 \cdot 10^6$ | $10^9$ |

- 子任务 $3$ 保证 $\sum k \le 3 \cdot 10^6$。
- 子任务 $4$ 保证 $\sum n^2 \le 2.5 \cdot 10^7$。

## 样例 #1

### 输入

```
3
4 2
abab
1 1
a
30 1
abaababaababaababaababaababaab
```

### 输出

```
20
1
128```

# 题解

## 作者：sunkuangzheng (赞：6)

> 观察：在 $s^k$ 中任意一个长度大于等于 $n$ 的回文串都可以向两侧无限延伸。
> 
> 证明：设 $s_{1\sim n}$ 是回文串，记 $t = s^k$，此时应有 $t_0 = t_n = s_n,t_{n+1} = t_1 = s_1$。因此 $t[0,n+1]$ 也是回文串，以此类推即可。

考虑对 $s+s+s$ 求出每个中心的回文半径，如果回文半径大于等于 $\lceil \frac{n}{2} \rceil$，那么这个回文串就可以无限延伸，贡献容易计算；否则这个回文中心在所有位置的贡献都是一样的（特判边界情况），贡献也不难计算。

时间复杂度线性。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 01.09.2024 16:17:57
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5,mod = 998244353;
using namespace std;
int T,n,m; string s;
vector<int> manachar(string t){
    string s; s = ".#";
    for(char c : t) s += c,s += '#';
    int n = s.size(),r = 0,mid = 0; vector<int> p(n);
    for(int i = 1;i < n;i ++){
        if(i <= r) p[i] = min(r - i + 1,p[2 * mid - i]);
        while(s[i - p[i]] == s[i + p[i]]) p[i] ++;
        if(i + p[i] - 1 > r) r = i + p[i] - 1,mid = i; 
    }for(int &i : p) i = i / 2;
    return p;
}void los(){
    cin >> n >> m >> s; ll ans = 0;
    auto p = manachar(s + s + s); s = " " + s;
    p.erase(p.begin()); 
    for(int k = 2 * n;;k ++){
        int i = (k + 1) / 2 - n,j = k / 2 + 1 - n;
        if(j > n) break;
        if(p[k] >= n + (i == j)){
            int l = m / 2;
            ans = (ans + 1ll * l * (l - 1) % mod * n % mod + 1ll * (i + n - j + 1) * l) % mod;
            if(m & 1) ans = (ans + min(i,n - j + 1) + 1ll * l * n) % mod; 
        }else ans = (ans + 1ll * p[k] * (m - 2) + min(i,p[k]) + min(n - j + 1,p[k])) % mod; 
    }cout << ans << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

## 作者：wxzzzz (赞：3)

感觉官方题解证明有点抽象，来补个简洁易懂的证明。

> 结论：若 $s^k$ 中某个回文串的长度 $>n$，那么它可以向两边无限延伸。

> 证明：在相邻字符中插入 $\tt\#$，则仅需考虑奇回文串。令 $p,len(len\ge n)$ 分别为回文中心、回文半径，则相当于证明 $s^k_{p-len}=s^k_{p+len}$。显然 $s^k_{[p-len+1+n,p+len-1+n]}=s^k_{[p-len+1,p+len-1]}$，因此 $s^k_{[p-len+1+n,p+len-1+n]}$ 也是回文串。又因为 $len\ge n$，所以这两个相同回文串连成一个大回文串 $s^k_{[p-len+1,p+len-1+n]}$，回文中心 $p'=\frac{(p-len+1)+(p+len-1+n)}{2}=p+\frac{n}{2}$。所以 $s^k_{p-len}=s^k_{p-len+n}=s^k_{2p'-(p-len+n)}=s^k_{p+len}$，原命题得证。

---

## 作者：I_will_AKIOI (赞：3)

因 whk 原因成为场外选手，然后最后半小时看题发现 C 很简单，简单场我咋没打，输麻了。

首先考虑 $k=1$。答案就是字符串 $s$ 中回文子串个数 $cnt$。然后考虑把 $k$ 增加 $1$，假设 $t=s^k$，$t_i$ 表示组成 $t$ 的第 $i$ 个 $s$。

那么此时 $t$ 的长度为 $2n$，$t$ 回文子串个数一共分为三部分。第一部分和第二部分是 $t_1$ 和 $t_2$ 单独的贡献 $cnt$，第三部分是 $t_1+t_2$。

当 $k$ 继续增大，到达 $3$ 时，$t$ 的回文子串个数就是原来 $s^2$ 的回文子串个数加上 $t_3$ 的贡献加上 $t_2+t_3$ 的贡献加上 $t_1+t_2+t_3$ 的贡献。以此类推，由于 $t_1=t_2\dots =t_k$，所以包含 $s$ 个数相同的 $t$ 的子串的贡献相同，因此每个相邻的 $k$ 的答案之差是一个等差数列，或者通过打表发现，答案呈现一个二阶等差数列，也就是前后两项的差是等差数列。根据通项公式，$a_n=a_1+(a_2-a_1)(n-1)+\frac{1}{2}(a_3-2a_2+a_1)(n-1)(n-2)$，因此只需要求出 $s^1,s^2,s^3$ 的回文子串个数，就可以求出答案。

回文子串个数需要用 Manacher 求，用 hash 和二分会 TLE。个数就是每个字符回文半径之和。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define N 3000005
using namespace std;
int n,m,k,x,y,z,p[N*6];
char c,s1[N],s2[N];
int Manacher(char s[])//Manacher 算法
{
	int l=0,r=-1,ans=0;
	for(int i=0;i<=m;i++) p[i]=0;
	for(int i=1;i<=m;i++)
	{
		if(i<=r) p[i]=min(p[l+r-i],r-i+1);
		while(s[i-p[i]]==s[i+p[i]]) p[i]++;
		if(i+p[i]>r) l=i-p[i]+1,r=i+p[i]-1;
	}
	for(int i=1;i<=m;i++) ans+=p[i]/2;
	return ans;
}
void build(int len,char s1[],char s2[])//通过 s1 构建一个 s2，便于执行 Manacher 算法
{
	s2[0]='~';
	s2[1]='|';
	m=1;
	for(int i=1;i<=len;i++) s2[++m]=s1[(i-1)%n+1],s2[++m]='|';
	s2[m+1]='\0';
	return;
}
void solve()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>s1[i];
	build(n,s1,s2);
	x=Manacher(s2);
	build(n+n,s1,s2);
	y=Manacher(s2);
	build(n+n+n,s1,s2);
	z=Manacher(s2);
	//求出二阶等差数列前三项
	int res=(x+(y-x)%mod*(k-1)%mod+(z-y-y+x)%mod*(k-1)%mod*(k-2)%mod*499122177%mod)%mod;
	//通项公式
	cout<<res<<"\n";
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：zyn_ (赞：2)

题意：给定长为 $n$ 的字符串 $s$ 与正整数 $k$，设 $f(s)$ 表示 $s$ 的回文子串个数，求 $f(s^k)$。要求 $O(n)$。

$k=1$ 就是 Manacher 模板。

注意到：$k\ge 2$ 时，固定 $s$，$f(s^k)$ 是关于 $k$ 的**二次函数**。

证明：

$g(k)=f(s^{k+1})-f(s^k)$ 就是 $s^{k+1}$ 中右端点在末 $n$ 位的回文子串个数。这里 $k\ge 2$。

$h(k)=g(k+1)-g(k)$ 就是 $s^{k+2}$ 中右端点在末 $n$ 位的回文子串个数减去 $s^{k+1}$ 中右端点在末 $n$ 位的回文子串个数，也即 $s^{k+2}$ 中左端点在前 $n$ 位且右端点在末 $n$ 位的回文子串个数。这里 $k\ge 2$。

设左端点是从左往右第 $l$ 位，右端点是从右往左第 $n-r+1$ 位。则这个回文子串是 $S(l,r,k)=s[l\dots n]+s^k+s[1\dots r]$。我们希望 $h(k)$ 是常值函数，因此只需证，固定 $(l,r)$，若 $\exist k\ge 2$ 使 $S(l,r,k)$ 回文，则 $\forall k\ge 2$ 使 $S(l,r,k)$ 回文。

设 $|S(l,r,k)|=t$。考虑 $S(l,r,k)$ 回文，等价于 $\forall i=1,2,\dots,\lfloor\dfrac{t}{2}\rfloor$，有 $s_{l+i}=s_{r-i}$（下标 $\bmod n$ 理解）。由于 $k\ge 2$，$t\ge 2n$，$\lfloor\dfrac{t}{2}\rfloor\ge n$，因此这又等价于 $\forall i=1,2,\dots,n$，有 $s_{l+i}=s_{r-i}$。注意这个条件与 $k$ 无关，从而对所有 $k\ge 2$，$S(l,r,k)$ 回文等价。

证毕。

于是用 Manacher 计算出 $k=2,3,4$ 的答案，插值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 64000009
#define int long long
#define ll long long
#define mod 998244353
ll T,n,k,x[N];
char c[N],s[N];
int _init_manacher(int n,char *s,char *t){
    for(int i=1;i<=n;++i)t[i<<1]='#',t[i<<1|1]=s[i];
    t[(n+1)<<1]='#',t[1]='~',t[(n+1)<<1|1]='$';
    return (n<<1)+3;
}
void manacher(int n,char *s,int *res){
    static char c[N];
    static int len,p,maxr;
    len=_init_manacher(n,s,c);
    p=maxr=0;
    for(int i=2;i<len;++i){
        res[i]=i>maxr?0:min(res[(p<<1)-i],maxr-i);
        while(c[i-res[i]]==c[i+res[i]])++res[i];
        --res[i];
        if(i+res[i]>maxr)maxr=i+res[i],p=i;
    }
}
ll f,g,h,d,e;
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld%s",&n,&k,c+1);
        if(k==1){
            f=g=h=0;
            for(int i=1;i<=n;++i)s[i]=c[i];
            manacher(n,s,x);
        	for(int i=2;i<=(n+1)<<1;++i)f+=((x[i]+1)>>1),f%=mod;
            printf("%lld\n",f);
            continue;
        }
        f=g=h=0;
        for(int i=1;i<=n;++i)s[i+n+n+n]=s[i+n+n]=s[i+n]=s[i]=c[i];
        manacher(4*n,s,x);
    	for(int i=2;i<=(4*n+1)<<1;++i)f+=((x[i]+1)>>1),f%=mod;
        for(int i=1;i<=n;++i)s[i+n]=s[i]=c[i];
        manacher(2*n,s,x);
    	for(int i=2;i<=(2*n+1)<<1;++i)g+=((x[i]+1)>>1),g%=mod;
        for(int i=1;i<=n;++i)s[i+n+n]=s[i+n]=s[i]=c[i];
        manacher(3*n,s,x);
    	for(int i=2;i<=(3*n+1)<<1;++i)h+=((x[i]+1)>>1),h%=mod;
        ll tmp=f;f=g,g=h,h=tmp;
        e=(h-g)-(g-f);--k;
        d=g-f;e%=mod,d%=mod,f%=mod;
        printf("%lld\n",((f+d*(k-1)%mod+(k-2)*(k-1)/2%mod*e%mod)%mod+mod)%mod);
    }
	return 0;
}
```

---

## 作者：Clare613 (赞：1)

## **思路：**
这道题我们可以发现如果字符串本身不是一个回文串，那么答案一定是 $0$。我们知道这个后就可以发现，从连着三个起，不管是连几个，他们的答案都是一样的。也就是首尾两个字符串，中间加个回文串。\
接着我们就能把公式算出来，设一个为 $A$，两个为 $B$，三及以上为 $C$，可得：
$$(B-A)\times(k-1)+(C-2\times B+A)\times\dfrac{(k-1)\times(k-2)}{2}+A$$

算后好对于答案取模输出即可。
## **code：**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s,str,w;
int n,m,p[50000005];
int k;
const int mod=998244353;
void add(){
	str=" ";
	int len=w.size();
	for(int i=0;i<w.size();i++){
		str+="#";
		str+=w[i];
	}
	str+="#";
	str+="@";
	m=len*2+1;
}
int manacher(){
//	memset(p,0,sizeof(p));
	int r=0;
	int mid=0;
	int ans=0,last=0;
	for(int i=1;i<=m;i++){
		p[i]=((i<r)?min(p[2*mid-i],r-i):1);
		while(str[i+p[i]]==str[i-p[i]]){
			p[i]++;
		}
		if(i+p[i]>r){
			r=p[i]+i;
			mid=i;
		}
		ans+=p[i]/2;
		ans%=mod;
	}
	return ans;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0)->sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		cin>>s;
		w=s;
		add();
		int A=manacher();
		w=s+s;
		add();
		int B=manacher();
		w=s+s+s;
		add();
		int C=manacher();
		cout<<((((B-A+mod)%mod)*((k-1+mod)%mod))%mod+(C-2*B+A+mod*2)%mod*(((k-1)*(k-2)/2)%mod)+A)%mod<<"\n";
	}
	return 0;
}
/*
abaaba
*/
```

---

## 作者：ran_qwq (赞：0)

恶臭回文串题，赛时被 corner case 送走了……

赛时不想写马拉车，写了哈希+二分，所以出题人真放了单 log 过？

首先特判 $n=1$ 及 $k=1$ 的情况，前者输出 $\binom k2$，后者枚举回文中心二分。

我们仍然沿用 $k=1$ 的做法，枚举回文中心 $x$，为了方便我们假设它是字符。手玩一下回文串拓展的过程：首先会顶到一端，然后因为重复可以继续匹配。我们把原串复制一份看看会发生什么事情。

假如说先顶到的是原串的**右端**，即回文中心在原串的右半部分。下面的讨论都是基于这个大前提的。然后右端点会进入复制串。如果左端点**能**顶到原串的左端。这时候你会发现以后就不受回文的限制，可以顶到重复 $k$ 次的 $S^k$ 的左端或右端。为什么呢？此时原串 $S$ 可以表示为 $A+B$，当前匹配的串可以表示为 $A+B+A'$，这里 $A'$ 表示 $A$ 的反串，$B$ 是一个回文串。不难发现 $A$ 的左边是 $B$，$A'$ 的右边也是 $B$，但 $B=B'$！所以可以归纳证明到这里已经不受回文的限制了。

此时对于第 $i$ 个 $S$ 的这个回文中心 $x$，不妨设最后顶到的是 $S^k$ 的左端。则前面长度为 $(i-1)n+x$。考虑所有顶到 $S^k$ **左端**的 $x$ 的总贡献。我们把 $k$ 为奇数时最中间的串单独算，那么前 $t=\lfloor\dfrac k2\rfloor$ 个 $x$ 会顶到左端。即和为 $\sum\limits_{j=1}^t(j-1)n+x=xt+n\binom{t-1}2$。顶到右端同理。中间的贡献就是 $n(t+1)-x+1$。

如果左端点**不能**顶到原串的左端，即不能顶到 $S^k$ 的左端。那么不能拓展到整个串，设回文半径为 $r$，此时又有两种情况。一是它不处于两个 $S$ 中间，直接贡献是 $kr$。二是它处于两个 $S$ 中间，由于只有 $k-1$ 个中间，剩下 $1$ 个是 $S^k$ 最后的那个 $S$ 里面的，因为顶到右端而不能继续拓展，它的贡献是 $n-x+1$。所以情况二的贡献是 $kn-x+1$。

先顶到原串的左端的情况同理，只是在 $S$ 的左半部分。回文中心不是字符也同理。

时间复杂度 $O(n\log n)$ 或 $O(n)$。

赛时的 corner case 是这种写法，回文中心不是字符时，左半部分和右半部分的划分问题。

```cpp
ull pw[N],hl[N],hr[N];
il ull gtl(int l,int r) {return hl[r]-hl[l-1]*pw[r-l+1];}
il ull gtr(int l,int r) {return hr[l]-hr[r+1]*pw[r-l+1];}
void QwQ() {
	string s; int n=rd(),k=rd(),as=0; cin>>s,s=" "+s+s;
	for(int i=1;i<=n*2;i++) hl[i]=hl[i-1]*B+s[i];
	hr[n*2+1]=0; for(int i=n*2;i;i--) hr[i]=hr[i+1]*B+s[i];
	if(n==1) return wr(1ll*k*(k+1)/2%MOD,"\n");
	if(k==1) {
		for(int i=1;i<=n;i++) {
			int l=1,r=min(i,n-i+1),rs=0;
			for(int md;l<=r;) md=l+r>>1,gtl(i-md+1,i)==gtr(i,i+md-1)?l=(rs=md)+1:r=md-1;
			cadd(as,rs);
		}
		for(int i=2;i<=n;i++) if(s[i]==s[i-1]) {
			int l=1,r=min(i-1,n-i+1),rs=0;
			for(int md;l<=r;) md=l+r>>1,gtl(i-md,i-1)==gtr(i,i+md-1)?l=(rs=md)+1:r=md-1;
			cadd(as,rs);
		}
		return wr(as,"\n");
	}
	for(int i=n/2+1;i<=n;i++) {
		int l=1,r=min(i,n*2-i+1),rr=r,rs=0;
		for(int md;l<=r;) md=l+r>>1,gtl(i-md+1,i)==gtr(i,i+md-1)?l=(rs=md)+1:r=md-1;
		if(rs==rr) {
			cadd(as,vadd(vmul(rr,k/2),vmul(1ll*(k/2)*(k/2-1)/2%MOD,n)));
			if(k&1) cadd(as,vadd(n-i+1,vmul(k/2,n)));
			cadd(as,vadd(vmul(n-i+1,k/2),vmul(1ll*(k/2)*(k/2-1)/2%MOD,n)));
		} else if(i+rs-1<=n) cadd(as,vmul(rs,k));
		else cadd(as,vadd(vmul(rs,k-1),n-i+1));
	}
	for(int i=(n+1)/2+1;i<=n;i++) if(s[i-1]==s[i]) {
		int l=1,r=min(i-1,n*2-i+1),rr=r,rs=0;
		for(int md;l<=r;) md=l+r>>1,gtl(i-md,i-1)==gtr(i,i+md-1)?l=(rs=md)+1:r=md-1;
		if(rs==rr) {
			cadd(as,vadd(vmul(rr,k/2),vmul(1ll*(k/2)*(k/2-1)/2%MOD,n)));
			if(k&1) cadd(as,vadd(n-i+1,vmul(k/2,n)));
			cadd(as,vadd(vmul(n-i+1,k/2),vmul(1ll*(k/2)*(k/2-1)/2%MOD,n)));
		} else if(i+rs-1<=n) cadd(as,vmul(rs,k));
		else cadd(as,vadd(vmul(rs,k-1),n-i+1));
	}
	for(int i=n+1;i<=n+n/2;i++) {
		int l=1,r=min(i,n*2-i+1),rr=r,rs=0;
		for(int md;l<=r;) md=l+r>>1,gtl(i-md+1,i)==gtr(i,i+md-1)?l=(rs=md)+1:r=md-1;
		if(rs==rr) {
			cadd(as,vadd(vmul(rr,k/2),vmul(1ll*(k/2)*(k/2-1)/2%MOD,n)));
			if(k&1) cadd(as,vadd(i-n,vmul(k/2,n)));
			cadd(as,vadd(vmul(i-n,k/2),vmul(1ll*(k/2)*(k/2-1)/2%MOD,n)));
		} else if(i-rs+1>n) cadd(as,vmul(rs,k));
		else cadd(as,vadd(vmul(rs,k-1),i-n));
	}
	for(int i=n+1;i<=n+(n+1)/2;i++) if(s[i-1]==s[i]) {
		int l=1,r=min(i-1,n*2-i+1),rr=r,rs=0;
		for(int md;l<=r;) md=l+r>>1,gtl(i-md,i-1)==gtr(i,i+md-1)?l=(rs=md)+1:r=md-1;
		if(rs==rr) {
			cadd(as,vadd(vmul(rr,k/2),vmul(1ll*(k/2)*(k/2-1)/2%MOD,n)));
			if(k&1) cadd(as,vadd(i-n-1,vmul(k/2,n)));
			cadd(as,vadd(vmul(i-n-1,k/2),vmul(1ll*(k/2)*(k/2-1)/2%MOD,n)));
		} else if(i-rs>n) cadd(as,vmul(rs,k));
		else cadd(as,vadd(vmul(rs,k-1),i-n-1));
	}
	wr(as,"\n");
}
signed main() {
//	freopen("in.in","r",stdin),freopen("out.out","w",stdout);
	pw[0]=1; for(int i=1;i<=N-10;i++) pw[i]=pw[i-1]*B;
	int T=rd(); while(T--) QwQ();
}
```

---

