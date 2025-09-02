# k-substrings

## 题目描述

给定一个长度为 $n$ 的字符串 $T$ 。

定义 $k$ 子串表示 $S_k , S_{k+1} ~ \cdots S_{n - k +1}$ 。显然的， $1$子串= $T$，并且有  $\lceil \frac n 2 \rceil$ 个 $k$ 子串。

对于每一个 $k$ 子串  $k=1,2,3...\lceil \frac n 2 \rceil$ ，试找出最大长度的字符串 $t$，使得 $t$ 是 $T$ 的前缀和后缀且 $t$ 的 长度为奇数。

## 样例 #1

### 输入

```
15
bcabcabcabcabca
```

### 输出

```
9 7 5 3 1 -1 -1 -1
```

## 样例 #2

### 输入

```
24
abaaabaaaabaaabaaaabaaab
```

### 输出

```
15 13 11 9 7 5 3 1 1 -1 -1 1
```

## 样例 #3

### 输入

```
19
cabcabbcabcabbcabca
```

### 输出

```
5 3 1 -1 -1 1 1 -1 -1 -1
```

# 题解

## 作者：Miraik (赞：14)

### 简要题意

给一个长度为 $n$ 的字符串 $s$，对于 $1 \le k \le   \lceil \frac{n}{2} \rceil$ 求 $s[k,n-k+1]$
 的 **最长且长度为奇数** 的 $\text{border}$ 的长度。
 
### 题解 
 
注意到一个惊人的事实：对于所有 $k$，我们要求解的子串的中心位置相同。

因此我们发现，如果我们从中间向两边扩展，即 $k$ 从大到小做，必然有 $ans_i \le ans_{i+1}+2$。

证明很简单，就相当于你往两边各插入一个字符，那么 $\text{border}$ 长度最多增加 $2$（也就是当前的 $\text{border}$ 继续匹配掉这两个字符）。

那我们只需要在 $k$ 从大往小做的时候先将当前 $\text{border}$ 长度加 $2$，然后直接用字符串哈希判断一下 $\text{border}$ 是否合法，不合法就不停减 $2$ 就好了。

由于每次 $\text{border}$ 长度最多增加 $2$，那么我们整个流程中 $\text{border}$ 长度减小的次数也最多为 $n$，因此时间复杂度就是线性的了。

代码非常简短。

```cpp
#include<cstdio>
const int N=1000005;
const int mod=1000000007;
int n,m,pw[N],hsh[N],f[N],ans; char s[N];
inline int gethash(int l,int r){
	int k=r-l+1;
	return (hsh[r]+mod-1ll*pw[k]*hsh[l-1]%mod)%mod;
}
main(){
	scanf("%d%s",&n,s+1); m=(n-1)/2;
	pw[0]=1; for(int i=1;i<=n;i++) pw[i]=pw[i-1]*131ll%mod;
	for(int i=1;i<=n;i++) hsh[i]=(hsh[i-1]*131ll+s[i]-'a')%mod;
	f[m+1]=-1;
	for(int i=m;~i;i--){
		f[i]=f[i+1]+2;
		while(~f[i] && i*2+f[i]>=n) f[i]-=2;
		while(~f[i] && gethash(i+1,i+f[i]) != gethash(n-i-f[i]+1,n-i) ) f[i]-=2;
	}
	for(int i=0;i<=m;i++) printf("%d%c",f[i],i==(n-1)/2?'\n':' ');
}
```


---

## 作者：YellowBean_Elsa (赞：10)

## 我来造福世界啦

虽然我就是个菜鸡

### 题目描述

给定一个长度为$n$的字符串$T$

定义$k$子串表示$S_kS_{k+1}...S_{n - k +1}$，显然的$1$子串=$T$，并且有$\lceil \frac n 2 \rceil$个$k$子串

对于每一个$k$子串 $k=1,2,3...\lceil \frac n 2 \rceil$试找出最大长度的字符串$t$，使得$t$是$T$的前缀和后缀

### 输入输出格式

#### 输入格式：
输入的第一行是一个整数$n$，表示字符串的长度。

输入的第二行是一个长度为$n$的字符串$s$。

#### 输出格式：

输出$\lceil \frac n 2 \rceil$个数，其中第$i$个数为 满足$t$是$i$子串的前缀和后缀的字符串 $t$ 的最大长度

（感谢@maoxiangui的翻译）

### 分析

首先，每一个目标子串都关于 $s$ 中心对称

所以我们考虑从最中间开始算

注意，算最中间要根据 $len(s)$ 奇偶性

然后根据
$$ ans_i \le ans_{i+1}+2$$
可知对于每个目标子串都把它的答案从 $ans_{i+1}+2$ 到 $-1$ 间的奇数都枚举一遍就行了

判断答案是否可行就用字符串哈希（但不知为何自然溢出就会挂qwq）

### 代码

```cpp
//coder: Feliks Hacker of IOI == YB an AKer of IMO
//acknowledgements: https://www.cnblogs.com/five20/p/9353217.html,
//https://blog.csdn.net/b121382291/article/details/102357461
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+5;
const int P=131;
const ll mod=998244353;//自然溢出竟然会挂！！！ 
int n;
char s[N];
int ans[N];
int cnt,l,r;
ll x,y;
ll p[N],sum[N];
inline ll mo(ll x){//龟速模，别理它 
	while(x>=mod)x-=mod;
	return x;
}
//the preparation of string hashing  
inline void Hash(){
	p[0]=1;
	for(int i=1;i<=n;i++){
		p[i]=p[i-1]*P%mod;
		sum[i]=mo(sum[i-1]*P%mod+s[i]-'a'+1);
	}
}
//finding the hash of a substring from s[l] to s[r]
inline ll hs(int l,int r){
	return mo(sum[r]-sum[l-1]*p[r-l+1]%mod+mod);
}
int main(){
	scanf("%d%s",&n,s+1);
	Hash();
	cnt=n+1>>1;
	//处理最中间那个 
	if(n&1)ans[cnt]=-1,l=r=cnt;
	else{
		l=n>>1,r=l+1;
		if(s[l]==s[r])ans[cnt]=1;
		else ans[cnt]=-1;
	}
	//从中间向两边扩散 
	for(int i=cnt-1;i>=1;i--){
		l--,r++;//扩大substring
        	//枚举从比上一个大2到-1的奇数
		for(int j=ans[i+1]+2;j>=-1;j-=2){
        		//hash判断是否同时是前后缀
			x=hs(l,l+j-1),y=hs(r-j+1,r);
			if(x==y || j==-1){
				ans[i]=j;
				break;
			}
		}
	}
	for(int i=1;i<=cnt;i++)
		printf("%d ",ans[i]);
	return 0;
}
```
### 关于复杂度

有人可能会问：这不是 $n ^ 2$ 的吗？

我们来看 $j$ 的变化情况：

每轮循环之初从 $ans_{i+1}$ 变成 $ans_{i+1}+2$, 一共 $\frac{n}{2}$ 次

而j从 $ans_{cnt}$ 变成 $ans_1$ 差不多是有增无减

所以 
$$ j \gets j - 2 $$ 

这一步最多也进行了 $\frac{n}{2}$ 次

于是总复杂度 $O ( N )$

目前谷排速度第四 2333……

## See you next time!


---

## 作者：QueenSi (赞：9)

提供一种思路  
对于一个串，将其反转后相互差开一格插入原串，那么前后缀相同的部分是回文串   
如串为: $A B C A B,$  
反转后为 $B A C B A,$  
插入为: $ABBACCABBA$  
其回文串 $ABBA$ 实际为 $AB$ 的前后缀反转插入而成  
我们可以利用此性质进行 $manacher$  
那么目前字串变为: $@ $ # $ A $ # $ B $ # $ B $ # $ A $ # $ C $ # $  C $ # $ A $ # $ B $ # $ B $ # $ A $ #  
我们记$b$数组为回文半径  
有以下结论:  
1.前后缀相同的长度为 $b[i]/2$  
2.原串的第i个字串在目前串的位置为位置 $4*i-1$（算 $@$ 符号）  
3.由于前后缀插入，导致回文串只可能是偶数长度的回文串，所以只有 $#$ 为中心的回文串是有用的  
4.原串需要统计的位置只有 $n/2+n$ % $2$ 个  
记当前统计到 $k$ 的位置为 $i$ ，显然 $i=4*k-1$ ，记回文中心为 $j$ ,若 $j<i$ 那么无相同前后缀，不然原串的最长前后缀为 $\lfloor (j-i)/2 \rfloor +1$  
因为我们希望答案尽可能大，所以前做预处理，把回文中心的位置存入他的左边界，在正式处理时，从左到右扫，取最大的中心与当前的$k$进行计算即可。  
因为要找奇数前后缀，$\lfloor (j-i)/2 \rfloor+1=2*v+1$,$v$为自然数,  
由于 $i=4*k-1$ ,所以 $\lfloor (j-4*k+1)/2 \rfloor+1=2*v+1$ , $j=4*(v-k)+1$ 或 $(v-k)$ 注意原式是向下取整 
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
inline bool Isdigit(char &c){if(c>='0'&&c<='9') return true;return false;}
inline int read(){int x=0,f=1;char c=getchar();for(;!Isdigit(c);c=getchar()){if(c=='-') f=-1;}
	for(;Isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^48);return x*f;}
inline bool Ischar(char &c){if(c>='a'&&c<='z') return true;return false;}
inline int Cread(char ch[]){int s=0;char c=getchar();for(;!Ischar(c);c=getchar());
	for(;Ischar(c);c=getchar()) ch[++s]=c;return s;}


const int N = 1e6+10;
int n,lenP,lenT,b[N<<2],L[N<<2],ans=-1;
char P[N],buf[N<<1],T[N<<2];

inline void Trans(){
	for(int i=1;i<=lenP;++i) buf[i*2-1]=P[i],buf[i*2]=P[n-i+1];
	T[++lenT]='@';
	for(int i=1;i<=2*lenP;++i) T[++lenT]='#',T[++lenT]=buf[i];
	T[++lenT]='#';
}

inline void Manacher(char ch[],int len){
	for(int i=1,r=1,mid=1;i<=len;++i){
		if(i<=r) b[i]=min(r-i+1,b[mid*2-i]);
		while(ch[i+b[i]]==ch[i-b[i]]) ++b[i];
		if(i+b[i]-1>r) r=i+b[i]-1,mid=i;
	}
}

int main(){
	n=read();
	lenP=Cread(P);
	Trans();
	Manacher(T,lenT);
	int Mi=n/2+n%2;
	for(int i=1;i<=lenT/2;++i) if(b[i]>1&&T[i]=='#'&&(i%4==0||i%4==1)) L[i-b[i]+1]=i;
	for(int i=1;i<=Mi*4-1;++i){
		ans=max(ans,L[i]);
		if(!((i+1)%4)){
			int res=(ans-i)/2+1;
			if(i>ans)  printf("-1");
			else printf("%d",res);
			if(i^(Mi*4-1)) putchar(' ');
		}
	}
	return 0;
}
```


---

## 作者：George1123 (赞：9)


拯救退役小锰锌 $\to$ [`George1123`](https://www.cnblogs.com/George1123/p/14334397.html)

---

## 题面

> [CF961F k-substrings](https://www.luogu.com.cn/problem/CF961F)

> 给定字符串 $s$，求每个左右端删除长度相等的子串的最长奇 `border` 长度。

> 数据范围：$2\le |S|\le 10^6$。

---

## 题解

其实是水题，`vp` 的时候比较懒散，写了个 `z-function` 发现不行就睡大觉去了，补题的时候画了幅图不能丢了只好写篇题解（完美的理由）。

注意到一段长为 $n$ 的字符串掐头去尾后黄色的这段仍然是新字符串的 `border`。

![](https://i.loli.net/2021/01/27/s69I4ehjHWb8V3P.jpg)

并且新字符串的 `border` 可以更大，所以两次答案满足 $a_0-2\le a_1$。

如果从中间最小的子串往两边算，那么答案 $a$ 每次最多增加 $2$，可能减少。

所以可以每次先给答案 $+2$，再一直减到是 `border` 为止。

判断 `border` 可以用 `hash`，时间复杂度 $\Theta(n)$。

---

## 代码

```cpp
//George1123
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef vector<int> vi;
typedef pair<int,int> pii;

#define x first
#define y second
#define sz(a) (int)((a).size())
#define all(a) (a).begin(),(a).end()
#define R(i,n) for(int i=0;i<(n);++i)
#define L(i,n) for(int i=(n)-1;i>=0;--i)

constexpr int inf32=0x3f3f3f3f;
constexpr i64 inf64=0x3f3f3f3f3f3f3f3f;

constexpr int mod=1000000007;

struct mint{
    int x;
    mint(int x=0):x(x){}
    friend mint operator+
    (const mint a,const mint &b){
        int x=a.x+b.x;
        return mint(x>=mod?x-mod:x);
    }
    friend mint operator-
    (const mint a,const mint &b){
        int x=a.x-b.x;
        return mint(x<0?x+mod:x);
    }
    friend mint operator*
    (const mint a,const mint &b){
        return mint(1ll*a.x*b.x%mod);
    }
};

int mypow(int a,int x=mod-2,int res=1){
    for(;x;x>>=1,a=(mint(a)*a).x)
        if(x&1) res=(mint(res)*a).x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n;
    string s;
    cin>>n>>s;

    constexpr int B=3917;
    vi p(n+1),pw(n+1);
    pw[0]=1;
    R(i,n) pw[i+1]=(mint(pw[i])*B).x;
    R(i,n) p[i+1]=(mint(p[i])*B+s[i]).x;
    auto sec=[&](int l,int r){
        int res=(mint(p[r])-mint(p[l])*pw[r-l]).x;
        return res;
    };

    vi res(n+1>>1);
    if((~n&1)&&(s[n-1>>1]==s[
    n>>1])) res[n-1>>1]=1;
    else res[n-1>>1]=-1;
    L(i,n-1>>1){
        res[i]=res[i+1]+2;
        for(;res[i]>-1;res[i]-=2)
            if(sec(i,i+res[i])==sec(n-i-res[i],n-i))
                break;
    }
    R(i,n+1>>1) cout<<res[i]<<' ';
    cout<<'\n';

    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
```

---

**沉舟侧畔千帆过，病树前头万木春，退役了！**

---

## 作者：Presentation_Emitter (赞：8)

~~本题难度显然虚高。~~

设 $S_{[1,n]}$ 的 `border` 为 $t_{[1,k]}(k \ge 3)$，那么显然 $t_{[2,k-1]}$ 是 $S_{[2,n-1]}$ 的 `border`。

要求 $t$ 为奇数，所以我们可以对于每一个 $i \in [1,n]$ 求出以 $i$ 为中心**可能成为 `border`** 的最长子串长度 $l_i$。这显然可以哈希求解。

对于一个左端点 $i$，该点的答案显然是 $2d-1$。其中 $d$ 代表 $i$ 右边中心最远的 `border` 的距离。然后我们可以用一个指针，从每一个 `border` 中心向左更新答案。

Code:

```cpp
#define maxn 1000000
#define bas 131
#define p1 998244353
#define p2 1019260817
ll n,ans[maxn+5],len[maxn+5],pw1[maxn+5],pw2[maxn+5],hs1[maxn+5],hs2[maxn+5];char s[maxn+5];
il ll hash1(ll l,ll r){ret (hs1[r]-hs1[l-1]*pw1[r-l+1]%p1+p1)%p1;}
il ll hash2(ll l,ll r){ret (hs2[r]-hs2[l-1]*pw2[r-l+1]%p2+p2)%p2;}
il ll hash0(ll l,ll r){ret hash1(l,r)*p2+hash2(l,r);}
int main()
{
	n=rd();scanf("%s",s+1);pw1[0]=pw2[0]=1;
	memset(len,0xff,sizeof(len));memset(ans,0xff,sizeof(ans));
	for(int i=1;i<=n;++i)
	{
		pw1[i]=pw1[i-1]*bas%p1;
		pw2[i]=pw2[i-1]*bas%p2;
		hs1[i]=(hs1[i-1]*bas+s[i])%p1;
		hs2[i]=(hs2[i-1]*bas+s[i])%p2;
	}
	for(int i=1;i<=n-i;++i)
	{
		reg ll l=0,r=i-1,mid;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(hash0(i-mid,i+mid)==hash0(n+1-i-mid,n+1-i+mid))
				l=mid+1,len[i]=len[n+1-i]=mid;
			else r=mid-1;
		}
	}
	ll p=(n+1)/2;
	for(int i=(n+1)/2;i>=1;--i)
	{
		if(p>i)p=i;
		if(~len[i])while(i-p<=len[i])ans[p]=((i-p)<<1)|1,--p;
	}
	for(int i=1;i<=(n+1)/2;++i)prt(ans[i]," \n"[i==n]);
	ret 0;
}
```

---

## 作者：2huk (赞：3)

> - 给定一个长度为 $n$ 的字符串 $T$。定义 $k$ 子串表示 $S_k , S_{k+1}  \cdots S_{n - k +1}$。求每个 $k$ 子串 $k=1,2,3...\lceil \frac n 2 \rceil$ 的 border 长度。这里要求 border 的长度为奇数。
> - $n \le 10^6$。

考虑：

![](https://cdn.luogu.com.cn/upload/image_hosting/m8v60bjy.png)

其中蓝色部分为 $k$ 子串，绿色的是这个 $k$ 子串 border，红线是原串中线，橙线分别是这两个 border 的中线。因为题目要求 border 长度为奇数，所以橙线坐标一定为整数。

第一条橙线的下标为 $i$，那么根据 $k$ 子串在下标上的对称性，另一条橙线的下标为 $n - i + 1$。我们考虑枚举第一条橙线的下标 $i = 1, 2, \dots, \lfloor \frac n2 \rfloor$。

接下来显然可以二分最大的 border 的半径 $r$，并计算这个 border 可能会对哪些 $k$ 子串的答案构成影响。

具体地，二分出最大的 $r$ 使得 $s[i-r+1, i+r-1] = s[n-i-r+2, n-i+r]$，这一步可以用字符串 Hash 判断。

然后考虑对于 $(i-r+1)$ 子串，此时可以用 $2r - 1$ 更新它的答案，表示当前这个子串的长度。同理，对于 $(i-r+2)$ 子串，此时我们可以用 $2r-3$ 更新它的答案，因为这个子串不能包含 $i - r + 1$ 这个位置，因此长度减了 $2$。以此类推，贡献的形式呈一个公差为 $-2$ 的等差数列。

于是问题就转化成了：

> - 若干次操作，将连续若干数与一个公差为 $-2$ 的等差数列取 $\max$。

做法见 [线段树做题笔记 (7)](https://www.cnblogs.com/2huk/p/18099771#-%E5%8C%BA%E9%97%B4-chkmax-%E5%85%AC%E5%B7%AE%E4%B8%80%E5%AE%9A%E7%9A%84%E7%AD%89%E5%B7%AE%E6%95%B0%E5%88%97)。

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1000010, P = 1145147117, c = 1451;

int n;
char s[N];
int hs[N], hs2[N], C[N];
int a[N];

int calc(int l, int r) {
	return ((hs[r] - hs[l - 1] * C[r - l + 1] % P) % P + P) % P;
}

struct Tree {
	struct Node {
		int l, r, v;
	}tr[N << 2];
	
	void pushup(int u) {
		tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
	}
	
	void calc(int u, int d) {
		tr[u].v = max(tr[u].v, d);
	}
	
	void pushdown(int u) {
		calc(u << 1, tr[u].v);
		calc(u << 1 | 1, tr[u].v);
	}
	
	void build(int u, int l, int r) {
		tr[u] = {l, r, -114514};
		if (l != r) {
			int mid = l + r >> 1;
			build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
		}
	}
	
	void modify(int u, int l, int r, int v) {
		if (tr[u].l >= l && tr[u].r <= r) {
			calc(u, v);
		}
		else {
			int mid = tr[u].l + tr[u].r >> 1;
			pushdown(u);
			if (l <= mid) modify(u << 1, l, r, v);
			if (r > mid) modify(u << 1 | 1, l, r, v);
		}
	}
	
	int query(int u, int x) {
		if (tr[u].l == tr[u].r) return tr[u].v;
		int mid = tr[u].l + tr[u].r >> 1;
		pushdown(u);
		if (x <= mid) return query(u << 1, x);
		return query(u << 1 | 1, x);
	}
}T;

void solve(int l, int x) {
	int r = x / 2 + l;
	if (r > n) r = n;
	if (l <= r) T.modify(1, l, n, x + 2 * l);
}

void lst() {
	for (int i = 1; i <= (n + 1) / 2; ++ i ) {
		a[i] = T.query(1, i) - 2 * i;
	}
}

signed main() {
	scanf("%lld%s", &n, s + 1);
	
	C[0] = 1;
	for (int i = 1; i < N; ++ i ) {
		C[i] = C[i - 1] * c % P;
	}
	
	for (int i = 1; i <= n; ++ i ) {
		hs[i] = (hs[i - 1] * c % P + s[i] - 'a') % P;
	}
	
	T.build(1, 1,  n);
	
	memset(a, -1, sizeof a);
	for (int i = 1; i <= n / 2; ++ i ) {
		int mid1 = i, mid2 = n - i + 1;
		if (s[mid1] != s[mid2]) continue;
		
		int l = 1, r = min(mid1, n - mid2 + 1), R;
		
		while (l <= r) {
			int mid = l + r >> 1;
			if (calc(mid1 - mid + 1, mid1 + mid - 1) == calc(mid2 - mid + 1, mid2 + mid - 1)) {
				R = mid;
				l = mid + 1;
			}
			else {
				r = mid - 1;
			}
		}
		
		solve(mid1 - R + 1, R * 2 - 1);
	}
	
	lst();
	
	for (int i = 1; i <= (n + 1) / 2; ++ i ) {
		cout << max(-1ll, a[i]) << ' ';
	}
	
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

由 k-substring 的定义，子串是从两边往中心靠拢的。倒过来看就是子串从中心开始，每次会左右各多一个字符。设 $i$ 的答案为 $f_i$，有 $f_i\le f_{i+1}+2$，因为最优情况也就是多出来的两个字符恰好能成为答案的一部分。于是每次将 $f_i$ 置为其上界 $f_{i+1}+2$，然后用字符串哈希判断 $f_i$ 是否合法，若合法就停止，否则减二并重复这一过程。

时间复杂度：$O(n)$。因为一共 $O(n)$ 次加二，带来最多 $O(n)$ 次减二。

自然溢出会 WA on test 34。

# Code

```cpp
#include<bits/stdc++.h>
const int mod=998244259,P=193;
int hash[1000005],base[1000005];
int ans[1000005];
char s[1000005];
int n,m;
int main(){
	scanf("%d%s",&n,s+1);
	base[0]=1;
	for(int i=1;i<=n;++i)
		hash[i]=(1ll*hash[i-1]*P+s[i])%mod,base[i]=1ll*base[i-1]*P%mod;
	ans[(m=n-1>>1)+1]=-1;
	for(int i=m;~i;--i){
		for(ans[i]=ans[i+1]+2;(i<<1)+ans[i]>=n;ans[i]-=2);
		while(~ans[i]&&(hash[i+ans[i]]-1ll*hash[i]*base[ans[i]]%mod+mod)%mod!=(hash[n-i]-1ll*hash[n-i-ans[i]]*base[ans[i]]%mod+mod)%mod)ans[i]-=2;
	}
	for(int i=0;i<=m;++i)
		printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Kelvin2009 (赞：1)

这是一道性质分析加字符串匹配。

首先，设 $i$ 子串满足的条件的 $t$ 最大长度为 $nxt_i$。

考虑 $i$ 子串与其它 $j$ 子串的关系。可以发现：子串长度每增加 $2$，最大匹配长度至多增加 $2$。

即：
$$nxt_{i}-nxt_{i+1}\leqslant2$$ 

移项：
$$nxt_{i}\leqslant nxt_{i+1}+2$$ 

考虑反着推。对于边界显然有 $nxt_{\lfloor\frac{n}{2}\rfloor}=0$。

再逐个向下枚举过去，每次 $nxt_{i}$ 的上界确定，至多为 $nxt_{i+1}+2$。由于前后缀 $t$ 的长度为奇数，每次 $nxt_{i}$ 减 $2$ 看前后缀是否相同。

可以发现 $nxt$ 的总变化量与复杂度的数量级相同，因此复杂度正确。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int range=1e6+5;
const long long base=29;
const long long mod1=1e9+7;
const long long mod2=1e9+9;
char c[range];
int n,pos,nxt[range];
long long pai1[range],pai2[range];
long long hush1[range],hush2[range];
inline long long get_hush1(int l,int r){return (hush1[r]-hush1[l-1]*pai1[r-l+1]%mod1+mod1)%mod1;}
inline long long get_hush2(int l,int r){return (hush2[r]-hush2[l-1]*pai2[r-l+1]%mod2+mod2)%mod2;}
inline bool check(int l1,int r1,int l2,int r2){return (get_hush1(l1,r1)==get_hush1(l2,r2) && get_hush2(l1,r1)==get_hush2(l2,r2));}
int main()
{
	pai1[0]=1ll;
	pai2[0]=1ll;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin >> c[i];
		c[i]=c[i]-'a'+1;
		pai1[i]=pai1[i-1]*base,pai1[i]%=mod1;
		pai2[i]=pai2[i-1]*base,pai2[i]%=mod2;
		hush1[i]=(hush1[i-1]*base%mod1+c[i])%mod1;
		hush2[i]=(hush2[i-1]*base%mod2+c[i])%mod2;
	}
	int ran=(n-1)/2;
	nxt[ran+1]=-1;
	for(int i=ran;i>=0;i--)
	{
		pos=nxt[i+1]+2;
		while(pos!=-1 && (i+pos>=n-i || !check(i+1,i+pos,n-i-pos+1,n-i))) pos-=2;
		nxt[i]=pos;
	}
	for(int i=0;i<=ran;i++) printf("%d ",nxt[i]);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

一个比较重要的模型？

考虑如果 $S[i \cdots n+1-i]$ 有一个长度为奇数的公共前后缀 $T = S[i \cdots i+len-1] = S[n+2-len-i \cdots n+1-i]$，那么考虑 $T[2 \cdots len-1]$ 实际上是 $S[i+1 \cdots n-i]$ 的一个公共前后缀。

即 $len_i - 2 \le len_{i+1}$，$len_i \le 2 + len_{i+1}$。

因此倒叙扫描 $i$，使用势能分析法，得到复杂度为 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10,MOD=998244353;
int n,pw[MAXN],pre[MAXN],len[MAXN];
string S;
int calc_hash(int l,int r) {return ((pre[r]-pre[l-1]*pw[r-l+1])%MOD+MOD)%MOD;}
int check(int pos,int len) {return calc_hash(pos,pos+len-1)==calc_hash(n+1-pos-len+1,n+1-pos);}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>S,S="&"+S;
	pw[0]=1; ffor(i,1,n) pw[i]=pw[i-1]*26%MOD,pre[i]=(pre[i-1]*26+S[i]-'a')%MOD;
	if(n%2==0) len[n/2]=(S[n/2]==S[n/2+1])?1:-1;
	else len[n/2+1]=-1;
	roff(i,n/2+n%2-1,1) {
		len[i]=min(n-2*(i-1),len[i+1]+2);
		while(len[i]>=0&&check(i,len[i])==0||len[i]%2==0) len[i]--;
	}
	ffor(i,1,n/2+n%2) cout<<len[i]<<' ';
	return 0;
}
```

---

## 作者：drowsylve (赞：1)

### 简化题意
我们定义一个字符串 $s[1…n]$ 的 k-substring 是 $s[k…n-k+1]$。
给定字符串 $s$，对于每个 $k$，求最大的奇数 $t$，满足 $s$ 的 k-substring 的长度为 $t$ 的前缀同时也是它的后缀。
### 题解
我们记 k-substrings 的答案为 $res_k$，考虑从中间开始计算答案，不断向左右两端扩展。此处需要注意讨论原串长度对中间点的影响。

注意到 $res_k≤res_{k+1}+2$，因为每次向左右各扩展一位，答案最多增加 $2$。

因此答案存在一定的单调性，每次暴力的枚举 $t$ 的长度，直接哈希判断前后缀。

由于每次答案范围最多比上次增加 $2$，因此总时间复杂度为 $O(n)$，可以通过此题。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000005;
const int base=131;
const int mod=1000000009;
int n,res[N];
string s;
int h[N],b[N];
bool check(int l1,int r1,int l2,int r2){
	int h1=(h[r1]-(h[l1-1]*b[r1-l1+1])%mod+mod)%mod;
	int h2=(h[r2]-(h[l2-1]*b[r2-l2+1])%mod+mod)%mod;
	return h1==h2;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>s;
	s='$'+s;
	b[0]=1;
	for(int i=1;i<=n;i++){
		h[i]=(h[i-1]*base+s[i]-'a'+1)%mod;
		b[i]=b[i-1]*base%mod;
	}
	int mid=(n+1)/2;
	for(int i=mid;i>=1;i--){
		if(i==mid){
			if(n&1==1) res[i]=-1;
			else res[i]=(s[i]==s[i+1])?1:-1;
			continue;
		}
		res[i]=res[i+1]+2;
		while(res[i]>=1){
			if(check(i,i+res[i]-1,n-i+1-res[i]+1,n-i+1)) break;
			res[i]-=2;
		}
	}
	for(int i=1;i<=mid;i++) cout<<res[i]<<' ';
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

考虑一个 $k$ 子串 $l\sim r$。他的一个奇数长度 border 为 $l\sim l'$ 和 $r'\sim r$。我们容易发现 $\frac{l+l'}{2}$ 和 $\frac{r'+r}{2}$ 关于中间点对称且一定是整点。

于是我们会发现中间点有且仅有 $O(n)$ 对。

显然我们可以对于每对中间点找到最长往左右扩展多少，这个是可以二分的。

对于每对中间点，子串往里收会导致 $len$ 减去 $2$。故打 $tag$ 然后 $O(n)$ 计算即可。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=998244353,mul=131;
int pw[1000005],hsh[1000005],maxv[1000005];
int find(int l,int r){
	return (hsh[r]-hsh[l-1]+mod)*pw[1000000-l]%mod;
}
signed main(){
	pw[0]=1; for(int i=1;i<=1000000;i++) pw[i]=pw[i-1]*mul%mod;
	memset(maxv,-1,sizeof(maxv));
	int n; cin>>n;
	string s; cin>>s; s=" "+s;
	for(int i=1;i<=n;i++) hsh[i]=(hsh[i-1]+s[i]*pw[i])%mod;
	for(int l=n/2,r=(n+3)/2;r<=n;l--,r++){
		if(s[l]==s[r]){
			int L=1,R=l;
			while(L<R){
				int mid=(L+R+1)>>1;
				if(find(l-mid+1,l+mid-1)==find(r-mid+1,r+mid-1)) L=mid;
				else R=mid-1;
			}
			maxv[l-L+1]=max(maxv[l-L+1],L*2-1);
		}
	}
	for(int i=1;i<=(n+1)/2;i++) maxv[i]=max(maxv[i-1]-2,maxv[i]),cout<<maxv[i]<<" ";
	return 0;
}
```

---

## 作者：tzc_wk (赞：1)

[Codeforces 题面传送门](https://codeforces.ml/contest/961/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF961F)

介绍一种奇怪的 $\Theta(n\log n)$ 的奇怪做法。

注意到这个“border 的长度必须是奇数”的条件非常奇怪，同时我们待求解的字符串也有一些比较奇妙的性质——它们的左右端点都关于中线轴对称，即 $l+r=n+1$。我们考虑 border 的性质与 $l+r=n+1$ 的条件联系起来。对于一个 $s[l...r]$ 的长度为 $len$ 的 border（$len$ 为奇数），假设 $r'=l+len-1,l'=r-len+1$，那么必然有 $s_l$ 与 $s_{l'}$、$s_{l+1}$ 与 $s_{l'+1}$，……，$s_r$ 与 $s_{r'}$ 均匹配。在下文中，用“左 border”代替 $s[l...r']$，“右 border”代替 $s[l'...r]$。

然后我们惊奇地发现，如果我们记 $m_l=\dfrac{l+r'}{2},m_r=\dfrac{l'+r}{2}$，那么有 $m_l+m_r=n+1$，并且 $m_l$ 与 $m_r$ 也应匹配。画出图来大概是这个样子，其中黑线为中线 $\dfrac{n+1}{2}$，绿线为左 border 的两个端点，褐色的线为右 border 的两个端点：

![](https://cdn.luogu.com.cn/upload/image_hosting/qwu9qtma.png)

因此我们考虑枚举 $m_l$，那么可以发现，由于 $m_l$ 是左 border 的中点，$m_r$ 是右 border 的中点，因此在上图中，两段黄色部分对应的字符串必须相同，两段紫色部分也同理，并且黄色和紫色部分长度也应相同。也就是说 $s[l...m_l],s[l'...m_r]$ 是 $s[1...m_l],s[1...m_r]$ 两段前缀的 LCS，$s[m_l...r'],s[m_r...r]$ 是 $[l...n],s[r...n]$ 的两段后缀的 LCP，也就是说，我们可以通过二分+哈希找到 $s[l...m_l]$ 这段区间的范围，不妨设其为 $[1,mn]$。得到了这些信息之后，又该怎样求解答案呢？对于每个左端点 $l$，我们考虑设 $M_l$ 表示 $[l,n+1-l]$ 的所有长度为奇数的 border 中，左 border 的中点的最大值，显然只要左 border 的中点越靠右，对应的 border 长度也就越大，而不难发现，我们求出 $m_l,m_r$ 可以延伸的范围 $[1,mn]$ 之后，操作等价于令 $M_{m_l-mn+1},M_{m_l-mn+2},\cdots,M_{m_l}$ 均对 $m_l$ 取 $\max$，差分一下用个 `set` 维护即可。

```cpp
const int MAXN=1e6;
const int MOD=1004535809;
const int BS=193;
int n;char s[MAXN+5];
int pw[MAXN+5],hsh[MAXN+5];
vector<int> add[MAXN+5],del[MAXN+5];
int gethsh(int l,int r){return (hsh[r]-1ll*hsh[l-1]*pw[r-l+1]%MOD+MOD)%MOD;}
int main(){
	scanf("%d%s",&n,s+1);
	for(int i=(pw[0]=1);i<=MAXN;i++) pw[i]=1ll*pw[i-1]*BS%MOD;
	for(int i=1;i<=n;i++) hsh[i]=(1ll*hsh[i-1]*BS+s[i])%MOD;
	for(int i=1;i<=n>>1;i++) if(s[i]==s[n+1-i]){
		int l=1,r=i,L=0,R=0;
		while(l<=r){
			int mid=l+r>>1;
			if(gethsh(i-mid+1,i)==gethsh(n+1-i-mid+1,n+1-i)) L=mid,l=mid+1;
			else r=mid-1;
		} l=1,r=i;
		while(l<=r){
			int mid=l+r>>1;
			if(gethsh(i,i+mid-1)==gethsh(n+1-i,n-i+mid)) R=mid,l=mid+1;
			else r=mid-1;
		} int mn=min(L,R);
		add[i-mn+1].pb(i);del[i+1].pb(i);
	} multiset<int> st;
	for(int i=1;i<=(n+1>>1);i++){
		for(int x:add[i]) st.insert(x);
		for(int x:del[i]) st.erase(st.find(x));
		if(st.empty()) printf("-1 ");
		else printf("%d ",((*st.rbegin())-i+1)*2-1);
	}
	return 0;
}
```



---

