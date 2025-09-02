# [JRKSJ R6] 第七学区

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/jswrnw5w.png)

这个题本来是要拿到 Tree Diagram 上算的，但是 Tree Diagram 被某组织的宇宙射线射爆了，所以这个问题交给了你。

不过你不需要计算出可能出现的最坏情况，只需要解决原问题就可以了。

## 题目描述

给你一个长度为 $n$ 的序列 $a$，求其所有子区间的按位或和的和。

## 说明/提示

保证读入模板消耗的时间少于 200ms，空间少于 1MB。

### 数据规模

本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | $\text{Score}$ |
| :----------: | :----------: | :----------: | 
| $1$ | $10^4$ | $10$ |
| $2$ | $3\times 10^6$ | $20$ |
| $3$ | $4\times 10^7$ | $30$ |
| $4$ | $5\times 10^7$ | $40$ |

对于 $100\%$ 的数据，$1\le n\le 5\times 10^7$，$0\le a_i <2^{64}$。

## 样例 #1

### 输入

```
10 10
2 8 9 1 9 2 7 1 2 10
1 10 1 1```

### 输出

```
544```

# 题解

## 作者：Rainbow_qwq (赞：22)

来写一下 $n\log n$ 做法。

首先要有一个 $n\log V$ 的 simple 做法。考虑对于每个位，数 0 段的个数，然后用全部的减去这些。对每个位维护一个 $lst_i$ 表示当前结尾有多少个 0，那么这个位下一次是 $0$ 就是操作 $lst_i\to lst_i+1,sum\to sum+2^i$，否则是 $lst_i\to 0,sum\to sum-lst_i2^i$。可以写出如下代码。

```cpp
int n;
ull res,lst[66];
inline ull C2(int x){return 1ull*x*(x-1)/2;}

signed main()
{
	READ::init(n);
	ull sum=0;
	int lim=0;
	For(i,0,n-1){
		ull x=READ::read();
		sum+=(~x);
		For(j,0,63)
			if(x>>j&1)sum-=lst[j]<<j,lst[j]=0;
			else ++lst[j];
		res-=sum;
	}
	res-=C2(n+1);
	cout<<res;
	return 0;
}
```

用一个 trick，考虑原本我们维护的是 64 个 $lst_j$，且 $lst_j$ 是 $\le n$ 的，把二进制数位画出来，这是一个 01 矩阵，并且只有 $64\times \log n$ 个位置可能有值。于是考虑转置这个矩阵，维护 $w_i$ 表示哪些 $lst_j$ 的第 $i$ 位为 1，这样只需要维护 $\log n$ 个 $w_i$。

对于 $lst_i\to 0$ 的操作就是把 $w_i$ 的那些位变为 0；对于 $lst_i\to lst_i+1$ 的操作就手动模拟二进制加法器。代码如下。

小常数 $n\log n$，1.6s。

```cpp
int n;
ull res;

inline ull C2(int x){return 1ull*x*(x-1)/2;}
ull w[30];

signed main()
{
	READ::init(n);
	ull sum=0;
	int lim=0;
	For(i,0,n-1){
		ull x=READ::read();
		sum+=(~x);
//		For(j,0,63)
//			if(x>>j&1)sum-=lst[j]<<j,lst[j]=0;
//			else ++lst[j];
		ull up=(~x),nup;
		for(int j=0;j<=lim;++j){
			sum-=(w[j]&x)<<j;
			w[j]&=(~x); // 上两行是变为 0 的操作
			nup=up&w[j];
			w[j]^=up;
			up=nup; // 上三行是模拟 +1 的二进制加法器
		}
		if((i&-i)==i)++lim;
		res-=sum;
	}
	res-=C2(n+1);
	cout<<res;
	return 0;
}
```

---

## 作者：critnos (赞：10)

没有人写解法 2 啊（悲），甚至写解法 1 的也不多。大部分是暴力，我记得我卡了，居然还跑过去了吗，谢罪谢罪谢罪。

## 解法 1

来自 JohnVictor，时间复杂度为 $O(n\sqrt w)$，但是吊打了 std orz。

对于每一位组成的 $01$ 序列，如果能够每 $\sqrt w$ 压进一个 word，就可以 $O(n\sqrt w)$ 计算出答案。因为显然求全 $0$ 区间，维护信息 $L$ 左端极长段，$R$ 右端极长段，$f$ 该区间是否全 $0$ 和 $ans$，这部分可以 $O(2^{\sqrt w})$ 预处理。

考虑对序列分块，每块大小 $\sqrt w$。预处理出 $[0,2^{\sqrt w})$ 中每个数将数位分散到 $[0,w)$ 上。这样对于每一块，实质上是做一个 $01$ 矩阵转置。利用前面的预处理和位运算，可以很轻易地 $O(w)$ 做到。

时间复杂度 $O(n\sqrt w)$，不过跑的很快。

## 解法 2

博客第一页就有这个分治的思想，不知道有没有选手翻了我的博客（捂脸

考虑求出每一位的答案。即保留这一位后形成的 $01$ 序列有多少个区间中至少有一个 $1$。思路同上。

一个经典的思想是分治。

然而对每位都维护的话时间复杂度不可接受。$O(nw)$ 的。

我们把 $w$ 个数都拆成二进制。然后把二进制的每一位的 $w$ 个 $01$ 压到一个 word 里。称这个为计数器。

说人话，举个栗子：

$w=2$，两个二进制分别是 $11$ 和 $01$。压完之后就变成两个 word，第 $0$ 位的 word 是 $10$，第 $1$ 位的 word 是 $11$。

所以计数器维护了 $O(\log n)$ 个 word。

考虑这里合并的本质：并行计算 $w$ 个二进制加法/乘法。

考虑加法，设两计数器为 $a,b$：

从低到高枚举每一位。维护进位。

每一位是否进位可以压进一个 word 里，因为这里至多进位一次，设其为 $t$。

计算该位答案：显然为 $t \oplus a_i \oplus b_i$。

计算 $t$：即判断两次加法的过程中是否有任何一个进位了。即 $(a_i \land b_i)|((a_i \oplus b_i)\land t)$。

时间复杂度 $O(\log n)$。

考虑乘法：

暴力乘法即可。本质上是做 $O(\log n)$ 次加法。

时间复杂度 $O(\log ^2 n)$。

每次合并调用 $O(1)$ 次加法和乘法。

时间复杂度即 $T(n)=2T(\dfrac n 2)+O(\log ^2 n)$。

因为 $\log ^2 n=o(n^{eps})$，$eps<1$ 所以时间复杂度 $O(n)$。

具体实现的时候不要朴素分治，要二进制分组，这样空间复杂度能做到 $O(\log n)$。

很神奇有没有。让我们一起膜拜 hqztrue 和上琴桥。

%%%

---

## 作者：enucai (赞：4)

## Description

给你一个长度为 $n$ 的序列 $\{a\}$，求其所有子区间的按位或的和。

其中，$1\le n\le 5\times 10^7$，$0\le a_i<2^{64}$。答案对 $2^{64}$ 取模。

## Analysis

第一眼：什么傻逼题。第二眼：$5\times 10^7$ 啊，没事了。

**约定：本题较卡常，故把常数带在复杂度内。**

考虑 $O(n\log V)$ 如何做。看到或，考虑按位计算贡献。我们先枚举每一位，看有多少个子区间的或这一位是 $1$。根据或运算的性质，我们发现只有这一位全 $0$ 的区间才是 $0$。于是对于每一位，将原序列转换为一个 01 序列，求出所有全 $0$ 的连续段，某一位 $i$ 的贡献就是 $2^i\times(\binom{n}{2}-\sum\binom{len_i}{2})$。$\{len\}$ 是所有全 $0$ 连续段的长度。

但是发现 $O(n\log V)$ 的复杂度是无法接受的，同时 $O(n)$ 的空间也是无法接受的。接下来的思路来自 cxy，膜拜。

考率对原序列进行分块，每个块的大小是 $B$。将原序列的答案拆成两部分：块内贡献 与 块间贡献。采取不同方式计算。

块内贡献用暴力枚举的方式计算，每个块内的复杂度 $O(B^2)$，块个数 $O(\frac{n}{B})$，于是这部分就在 $O(nB)$ 的复杂度内轻松解决。

块间的贡献较为麻烦，接下来分步解决。

首先考虑在较低复杂度内算出每一个二进制位在块内的第一个与最后一个 $1$ 的出现位置。暴力是单个块 $O(B\log V)$ 的，不够优秀。

考虑对块内的元素 $\{a\}$ 求前缀或运算和，称为序列 $\{s\}$。对于一个数 $a_i$，块内第一个出现在 $i$ 位置的二进制位就是 $s_i-s_{i-1}$ 的所有二进制为 $1$ 的位，不断取 $\text{lowbit}$ 即可。由于每一个二进制位只会在一个位置被算到，所以处理第一次出现位置的复杂度是 $O(\log V)$ 的，非常优秀。最后一个同理。因此单个块内处理该信息的复杂度是 $O(2\log V)$，即 $O(128)$，所有块复杂度 $O(\frac{128n}{B})$。下称 $i$ 二进制位在块内的第一次出现位置为 $f_i$，最后一个位置为 $g_i$。

接下来延续第一种算法的思想，枚举每一个二进制位，保存该二进制位上一个 $1$ 出现的位置，为 $lst_i$。那么这一位的跨块且或为 $0$ 的且右端点在该块内的区间个数是 $(f_i-l)\times (l-lst_i-1)$。又容易算出所有跨块的区间个数，用其减去所有不合法的区间个数就是这一位或为 $1$ 且跨块的区间个数，乘上二进制值即为这一位贡献。块内计算该信息复杂度为 $O(\log V)$ 即 $O(64)$。所有块复杂度为 $O(\frac{64n}{B})$。

因此最终时间复杂度 $O(nB+\frac{128n+64n}{B})=O(nB+\frac{192n}{B})$，取 $B=14$ 左右时复杂度较为优秀，约为 $O(14n)$。空间上只需要存当前块的 $B$ 个值与每一位的上一次出现位置，与该块内每个二进制位出现的第一个与最后一个位置，即 $O(B+\log V)$，约 $250$ 个 `long long` 变量，绰绰有余。于是解决了此题。

## Code

```cpp
int n,lst[64],f[64],g[64];
ll a[15],p[15],ban[64],vov;
ull ans;
signed main(){
  READ::init(n);
  for(int pos=1;pos<=n;pos+=14){
    int l=pos,r=min(n,pos+13),len=r-l+1;
    rep(i,l,r) a[i-l+1]=READ::read();
    rep(i,1,len){
      ll tmp=0;
      rep(j,i,len) tmp|=a[j],ans+=tmp;
    }
    rep(i,0,63) f[i]=g[i]=0;
    p[0]=0; rep(i,1,len) p[i]=p[i-1]|a[i];
    rep(i,1,len){
      ll qwq=p[i]-p[i-1];
      while(qwq) f[__lg(qwq&(-qwq))]=i+l-1,qwq-=qwq&(-qwq);
    }
    p[len+1]=0; per(i,len,1) p[i]=p[i+1]|a[i];
    rep(i,1,len){
      ll qwq=p[i]-p[i+1];
      while(qwq) g[__lg(qwq&(-qwq))]=i+l-1,qwq-=qwq&(-qwq);
    }
    rep(i,0,63){
      if(f[i]){
        ban[i]+=1ll*(f[i]-l)*(l-1-(lst[i]+1)+1);
        lst[i]=g[i];
      }else{
        ban[i]+=1ll*(r-l+1)*(l-1-(lst[i]+1)+1);
      }
    }
    vov+=1ll*(r-l+1)*(r-l+2)/2;
  }
  rep(i,0,63){
    ll tim=1ll*n*(n+1)/2-vov-ban[i];
    ans+=(ull)(1ull<<i)*tim;
  }
  cout<<ans;
}
```

---

## 作者：FxorG (赞：2)

感觉我这种做法的难点就是加个循环展开啊！

直接做是平凡的，可以做到 $O(64n)$，即先所有位钦定所有区间都有贡献，然后斥去贡献为 $0$ 的区间即可。

然后你发现似乎很难优化了！考虑本质上是在找两个连续 $1$ 段间的 $0$ 段的长度，你考虑上了分块应该是很好维护的。显然你块内的贡献有 $2$ 种方式，$O(64B) \ / \ O(B^2)$，块与块之间的考虑维护每个块首个和尾个 $1$ 的位置，这一部分可以直接倍增做，即记录前后缀或和。然后对于每个位就可以 $O(1)$ 计算贡献了。这样做的复杂度是 $O(\dfrac{64n\log_2B}{B})$ 的。

然后 $B$ 取 $64$ 就过了。


```cpp
#include <bits/stdc++.h>
#define pb push_back
#define Misaka namespace  
#define Mikoto std 
#define ull unsigned long long 
using Misaka Mikoto;
using namespace std;
namespace READ
{
	ull Read()
	{
		char ch=getchar();
		ull s=0;
		while(ch<'0'||ch>'9') ch=getchar();
		while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
		return s;
	}
	ull tp[10005];
	int l,r;
	ull g1,g2;
	void init(int &n)
	{
		int i,k;
		n=Read(),k=Read(),l=1;
		for(i=1;i<=k;++i)
			tp[i]=Read();
	}
	ull read()
	{
		if(l>r)
			l=Read(),r=Read(),g1=Read(),g2=Read();
		return tp[l++]*g1+g2;
	}
}
void pr(ull x) {
	static int st[30]; int tp=0;
	if(x==0) {
		putchar('0'); return ;
	}
	if(x<0) putchar('-'),x=-x;
	while(x) st[++tp]=x%10,x/=10;
	for(int i=tp;i>=1;i--) putchar(st[i]+'0');
}
#define cal(x) (1ull*(x)*((x)+1)>>1)
#define L(x) (((x)-1)*B+1)
#define R(x) (min(n,(x)*B))
#define id(x) (((x)-1)/B+1)
#define il inline
const int B=64;
ull ans,ansd;
int las[64];
ull a[B+3],b[B+3];
int n,sz,pos[B+3];
bool ok=0;

//ull cal(int x) {
//	ull res=0;
//	for(int i=1;i<=x;++i) {
//		ull qwq=x-i+1;
//		res+=qwq;
//	}
//	return res;
////	return 
//}

il ull solve(int l,int r) {
	ull res=0;
//	for(int i=l;i<=r;++i) {
//		for(int j=i;j<=r;++j) {
//			if(id(i)!=id(j)) ++res;
//		}
//	}
	if(l>r) return 0;
	if(id(l)==id(r)) return 0;
	res+=cal(r-l+1);
//	cout<<l<<" "<<id(l)<<" "<<R(id(l))<<" "<<r<<" "<<id(r)<<" "<<L(id(r))<<'\n';
	res-=cal(R(id(l))-l+1);
	res-=cal(r-L(id(r))+1);
	ull qwq=id(r)-1-id(l);
	if(qwq) res-=qwq*cal(B);
	return res;
}

il void sol() {
	for(int i=1,j;i<=sz;++i) {
		ull qwq=0;
		for(j=i;j<=sz;j+=4) {
			qwq|=a[j]; ans+=qwq;
			if(j+1<=sz) qwq|=a[j+1],ans+=qwq;
			if(j+2<=sz) qwq|=a[j+2],ans+=qwq;
			if(j+3<=sz) qwq|=a[j+3],ans+=qwq;
		}
	}
	b[0]=0;
	for(int i=1;i<=sz;++i) b[i]=a[i]|b[i-1];
	for(int i=0;i<64;++i) {
		int res=sz;
		if(!((b[sz]>>i)&1)) continue ;
		if(res>32&&((b[res-32]>>i)&1)) res-=32;
		if(res>16&&((b[res-16]>>i)&1)) res-=16;
		if(res>8&&((b[res-8]>>i)&1)) res-=8;
		if(res>4&&((b[res-4]>>i)&1)) res-=4;
		if(res>2&&((b[res-2]>>i)&1)) res-=2;
		if(res>1&&((b[res-1]>>i)&1)) res-=1;
		if(las[i]+1<=pos[res]-1) ans-=1ull*(1ull<<i)*solve(las[i]+1,pos[res]-1);
	}
	b[sz+1]=0;
	for(int i=sz;i>=1;--i) b[i]=a[i]|b[i+1];
	for(int i=0;i<64;++i) {
		if(!((b[1]>>i)&1)) continue ; 
		int res=1;
		if(res+32<=sz&&((b[res+32]>>i)&1)) res+=32;
		if(res+16<=sz&&((b[res+16]>>i)&1)) res+=16;
		if(res+8<=sz&&((b[res+8]>>i)&1)) res+=8;
		if(res+4<=sz&&((b[res+4]>>i)&1)) res+=4;
		if(res+2<=sz&&((b[res+2]>>i)&1)) res+=2;
		if(res+1<=sz&&((b[res+1]>>i)&1)) res+=1;
		if(res) las[i]=pos[res];
	}
}

signed main() {
	READ::init(n);
	sz=0; 
	ull res1=0;
	for(int i=1;i<=n;++i) {
		++sz; a[sz]=READ::read();
		pos[sz]=i;
//		cout<<i<<": "<<a[sz]<<" "<<pos[sz]<<'\n';
		if(sz==B) {
			if(i==n) break ;
			sol();
//			cout<<sz<<" "<<res1<<'\n';
//			ansd+=1ull*sz*res1;
//			res1+=sz;
			sz=0;
//			if(i!=n) sz=0;
		}
	}
	
//	ansd=cal(n);
	if(sz) sol();
	ansd=solve(1,n);
//	cout<<"nw "<<ans<<'\n';
//	cout<<ansd<<'\n';
	for(int i=0;i<64;++i) {
//		if(las[i]+1<pos[1]) {
//			ans-=1ull*(1ull<<i)*(cal(n-las[i])-cal(R(id(las[i]))-las[i])-cal(n-pos[1]+1));
			ans-=1ull*(1ull<<i)*solve(las[i]+1,n);
//			cout<<i<<" "<<las[i]<<" "<<n<<" "<<sz<<" "<<(pos[1]-1-las[i])<<" "<<sz*(pos[1]-1-las[i])<<'\n';
//		}
	}
//	cout<<ansd<<'\n';
	for(int i=0;i<64;++i) ans+=1ull*(1ull<<i)*ansd; 
	pr(ans);
	return 0;
}
```

---

