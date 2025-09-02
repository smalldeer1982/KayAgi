# Fenwick Tree

## 题目描述

设 $\operatorname{lowbit}(x)$ 表示 $x$ 的二进制最低位的值，例如 $\operatorname{lowbit}(12)=4$，$\operatorname{lowbit}(8)=8$。

对于长度为 $n$ 的数组 $a$，若长度为 $n$ 的数组 $s$ 满足对于所有 $k$ 均有 $s_k=\left(\sum\limits_{i=k-\operatorname{lowbit}(k)+1}^{k}a_i\right)\bmod 998\,244\,353$，则称 $s$ 为 $a$ 的 *树状数组* ，记为 $s=f(a)$。

对于正整数 $k$ 和数组 $a$，定义 $f^k(a)$ 如下：

$$
f^k(a)=
\begin{cases}
f(a)&\text{若 }k=1\\
f(f^{k-1}(a))&\text{否则}\\
\end{cases}
$$

给定长度为 $n$ 的数组 $b$ 和正整数 $k$，请求出一个数组 $a$，满足 $0\le a_i < 998\,244\,353$ 且 $f^k(a)=b$。可以证明答案一定存在，若有多个解，输出任意一个即可。

## 说明/提示

第一组测试数据中，可以验证 $f^1([1,1,1,1,1,1,1,1])=[1,2,1,4,1,2,1,8]$。

第二组测试数据中，可以验证 $f^2([1,2,3,4,5,6])=f^1([1,3,3,10,5,11])=[1,4,3,17,5,16]$。

## 样例 #1

### 输入

```
2
8 1
1 2 1 4 1 2 1 8
6 2
1 4 3 17 5 16```

### 输出

```
1 1 1 1 1 1 1 1
1 2 3 4 5 6```

# 题解

## 作者：luoguhandongheng (赞：10)

~~只有我一个人没看懂 dalao 题解的插板法是怎么来的吗~~，这篇题解只是提供一种对 $C_{\Delta d+k-1}^{k-1}$ 的理解方式，肯定不是最简单的方式，~~但是是我这种 jvruo 能看懂的方式~~。
## 前置知识
定义： $k$ 阶等差数列

对于一个给定的数列 $\{a_n\}$，把它的连续两项 $a_{n+1}$ 与 $a_n$ 的差 $a_{n+1}-a_n$ 记为 $\{b_n\}$，得到一个新数列，把数列 $\{b_n\}$ 称为原数列的一阶差数列。如果将 $\{b_n\}$ 的一阶差数列记为 $\{c_n\}$，则数列 $\{c_n\}$ 是 $\{a_n\}$ 的二阶差数列。依此类推，可得出数列 $\{a_n\}$ 的 $p$ 阶差数列，其中 $p \in \mathbb N^{*}$。

若 $\{a_n\}$ 的 $k-1$ 阶差数列是公差为 $d$ 的等差数列，且 $\{a_n\}$ 的 $k$ 阶差数列为常数列，则称 $\{a_n\}$ 为 $k$ 阶等差数列。

假设有常数列（零阶等差数列）$\{a_k=1,\forall k \in \N^{*}\}$，那么它的一重求和 $S_{1,n}=\sum_{k=1}^{n}a_k$ 确定的 $N$ 项的数列 $\{S_{1,n}\}_{n=1}^{N}$ 是一个一阶等差数列。进一步地，我们可以定义该常数列的 $m$ 重求和 $S_{m,n}=\sum_{k=1}^{n}S_{m-1,k}$ 确定的 $N$ 项 $m$ 阶等差数列 $\{S_{m,n}\}_{n=1}^{N}$。具体地 $\{S_{1,n}\}=\{1,2,3,\dots \}$，$\{S_{2,n}\}=\{1,3,6,\dots \}$，$\{S_{3,n}\}=\{1,4,10,\dots \}$。

定理：$m$ 阶等差数列 $\{S_{m,n}\}$ 的第 $x$ 项（即 $S_{m,x}$）为 $C^{m}_{m+x-1}$。（证明的话可以通过杨辉三角感性理解一下）~~很丑的两张图~~可以对照理解。
![](https://cdn.luogu.com.cn/upload/image_hosting/y5ixlcsp.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/lfg2q8ez.png)

## 题意
 $\operatorname{f}(a)$ 表示求数组 $a$ 在求和意义下的树状数组，已知 $a$ 经过 $\operatorname{f}$ 的 $k$ 次迭代后的结果为 $b=\operatorname{f}^{k}(a)$，求 $a$ 数组。
## 思路
![](https://cdn.luogu.com.cn/upload/image_hosting/5ah9sig1.png)
为书写方便，接下来我们记 $s^{t}= \operatorname{f}^{t}(a)$。（特别地 $s^0=a$ )

首先，我们发现，在进行 $\operatorname{f}$ 的变换时，树状数组叶子结点的值始终是不变的。比如 $s[1]=a[1],s^{2}[1]=s[1]=a[1]$，同理也可以证明 3、5、7 等叶子节点的值不变。所以 $a[叶子节点]=b[叶子节点]$。因此我们可以考虑从这些点入手，一层一层向上递归来求出每一个 $a[i]$ 的值。（比如：将 $b[2]$ 中 $a[1]$ 的贡献减掉得到 $a[2]$ 的值，$b[4]$ 中 $a[1]$、$a[2]$、$a[3]$ 的贡献减掉得到 $a[4]$ 的值。）

由题意可知，$s^{k}[u]=\sum s^{k}[v]+s^{k-1}[u]$，其中 $v$ 是 $u$ 在树状数组的结构中的直接儿子。比如，图中 $s^{k}[4]=s^{k}[2]+s^{k}[3]+s^{k-1}[4]$。特别地，取 $k=1$ 时 $s[4]=s[2]+s[3]+a[4]$ 即为普通的树状数组。

接下来，我们考虑 $a[i]$ 对 $s^k$ 的贡献。

先取具体的例子，我们考虑 $a[1]$ 对 $s^k$ 的贡献。首先，$a[1]$ 显然只会对它的祖先产生贡献。那么我们先考虑只有8个点（即图中）的情况。

考虑 1 的所有祖先 2、4、8。因为只有 $s[1]$，$s[2]$，$s[4]$，$s[8]$ 中含有 $a[1]$，以下的所有式子又只计算 $a[1]$ 的贡献，（你可以认为是 $a[2]=a[3]=a[4]\dots=0$，那么接下来的书写将省去其他的项。

$s^{k}[1]=a[1],\forall k\in \N^{*}$

$s[2]=s[1]\ \ \\ 
s^{2}[2]=s^{2}[1]+s[2]=2a[1]\\
s^{3}[2]=s^{3}[1]+s^{2}[2]=3a[1]$

$s[4]=s[2]=a[1]\\
s^{2}[4]=s^{2}[2]+s[4]=3a[1]\\
s^{3}[4]=s^{3}[2]+s^{2}[4]=6a[1]
$

$s[8]=s[4]=a[1]\\
s^{2}[8]=s^{2}[4]+s[8]=4a[1]\\
s^{3}[8]=s^{3}[4]+s^{2}[8]=10a[1]
$

将 $a[1]$ 的系数分别列出：\
$s[2]:{1,2,3,4\dots}\\
s[4]:{1,3,6,10\dots}\\
s[8]:{1,4,10,20,\dots}$ \
可以发现他们都是一组 $n$ 阶等差数列，具体来说，$a[1]$ 在其 $x$ 级父亲 $u$ 的 $s^{k}[u]$ 中的系数为 $x$ 阶等差数列的第 $k$ 项(有点拗口，感性理解即可)。

那么问题转化为求 $x$ 阶等差数列的第 $k$ 项。

观察到题中的 $x$ 阶等差数列就是上文提到的 $\{S_{x,n}\}$,则其第 $k$ 项带入上文提到的公式为 $C_{x+k-1}^{x}$。

下面对以上的发现结论做一个简单的证明（即证明 $a[u]$ 在其 $x$ 级父亲 $v$ 的 $s^{k}[v]$ 中的系数为数列 $\{S_{x,n}\}$ 的第 $k$ 项）,~~不想看证明的同学可以跳过。~~

利用归纳法：对 $u$ 的 1 级父亲（直接父亲）\
$$ s^{k}[u_1]  \\=s^{k}[u] + s^{k-1}[u_1]+other \\= s^{k}[u]+(s^{k-1}[u] + s^{k-2}[u_1])+other\\ =s^{k}[u]+[s^{k-1}[u] + (s^{k-2}[u]+s^{k-3}[u_1])]+other\\=\sum_{i=1}^{k}s^i[u] + other $$   \
关注到 $s^i[u]=a[u]+other(\forall i \in \N^{*})$ 且 $other$ 中显然不含有 $a[u]$，那么原式等于 $\sum_{i=1}^{k}a[u] + other$，故 $s^{k}[u_1]$ 中含有 $\sum_{i=1}^{k} 1$ 个 $a[u]$。而$\sum_{i=1}^{k} 1$ 恰好就是一重求和 $\{S_{1,n}\}_{n=1}^N$ 的第 $k$ 项。 

同理，对于 $u$ 的 $x$ 级父亲 $u_x$ 和 $x+1$ 级父亲 $u_{x+1}$，我们也有 $s^{k}[u_{x+1}]=\sum_{i=1}^{k}s^i[u_x] + other$。假设当 $x$ 时命题成立，那么我们有 $s^i[u_x]$ 中应含有 $\{S_{x,n}\}$ 的第 $i$ 项即 $S_{x,i}$ 个 $a[u]$。那么对于 $u_{x+1}$,$s^{k}[u_{x+1}]=\sum_{i=1}^{k}s^i[u_x] + other=a[u]\times\sum_{i=1}^{k}S_{x,i}+other$，根据定义，$S_{x+1,k}=\sum_{i=1}^{k}S_{x,i}$,所以原式等于 $a[u] \times S_{x+1,k}+other$,这样我们就证明了 $s^{k}[u_{x+1}]$ 也含有 $S_{x+1,k}$（即 $\{S_{x+1,n}\}$ 的第 $k$ 项）个 $a[u]$。

由上面的推导可以知道，对于**点$u$和他的祖先$v$**，**如果** $x=dep[u]-dep[v]$（即上文提到的 $x$ 级父亲），那么 $s^{k}[v]$ 中将含有 **$C_{x+k-1}^{x}$** 个 $a[u]$，将 $v$ 的子树中所有节点的贡献减掉，即可求出 $a[v]$ 的值。
## 实现
通过一个 ```bitset``` 模拟树状数组中每个节点的二进制编码，注意到 ```lowbit(i)``` 小的节点一定比 ```lowbit(i)``` 大的节点深度更深，因此先将 ```lowbit(i)``` 小的节点处理完后再去处理 ```lowbit(i)``` 大的节点(因为父亲节点的更新一定要求已经求出了每个 ```a[儿子节点]```)，在回溯时更新。

这里没看懂直接看代码吧。
## 编码

```cpp
#include <bits/stdc++.h>
#define bs bitset 
#define int long long
using namespace std;
int lowbit(int i){
	return i&(-i);
} 
const int N=2e5+10,mod=998244353;
int n,s,b[N],D,a[N],inv[50];
bs <60> t;
void init(){
	inv[1]=1;
	for(int i=2;i<=D;++i)
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
}
void solve(int u){
	if(u==0){//到了叶子节点 
		t[u]=1;//叶子节点的lowbit(i)都是最后一位，把最后一位标记为1 
		int k=t.to_ullong(),fa=k+lowbit(k);//求十进制下的节点编号
        //叶子节点的b[k]就等于a[k]
		if(k<n){//减掉它对它祖先的贡献 
			int cnt=1;//cnt求组合数 
			for(int i=fa,x=1/*x=dep[i]-dep[k]*/;i<=n;i+=lowbit(i),++x){
				cnt=(cnt*inv[x]%mod)*(s+x-1)%mod;
				b[i]=((b[i]-cnt*b[k]%mod)%mod)%mod;//把x级父亲中a[k]的部分减掉
				b[i]=(b[i]%mod+mod)%mod;//保证是非负的 
			}
		}
		t[u]=0;
		return;
	}
	//枚举所有的情况 
	t[u]=1;solve(u-1);
	t[u]=0;solve(u-1);
	//更新 
	t[u]=1;
	int k=t.to_ullong(),fa=k+lowbit(k);
    //回溯到u的时候，b[k]中所有它儿子的贡献已经被减掉，因此b[k]=a[k],可以直接用b[k]更新它的祖先
	if(k<n){ 
		int cnt=1;
		for(int i=fa,x=1;i<=n;i+=lowbit(i),++x){
			cnt=(cnt*inv[x]%mod)*(s+x-1)%mod;
			b[i]=((b[i]-cnt*b[k]%mod)%mod)%mod;
			b[i]=(b[i]%mod+mod)%mod;
		}
	}
	t[u]=0;//把u这一位调成零，因为回溯到上一位时，必须保证lowbit是上一位
	//比如这时的二进制编码是1101 回溯到上一位时就变成1100 保证先更新lowbit小的在更新lowbit大的 
} 
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int m;cin>>m;
    while(m--){
    	cin>>n>>s;
    	for(int i=1;i<=n;++i)	cin>>b[i];
    	D=ceil(log2(n));
    	init();//求逆元（求组合数的时候要用） 
    	t.reset();//初始化 
		solve(D);
		for(int i=1;i<=n;++i)
			cout<<b[i]<<' ';
		cout<<endl;	
	}
	return 0;
}

```
时间复杂度 $O(n\log n)$。

---

## 作者：Creeper_l (赞：10)

> 题意：定义 $f(a)$ 表示将 $a$ 序列变为其所对应的树状数组。已知 $f^k(a)=b$，给定长度为 $n$ 的序列 $b$，求 $a$ 序列。

很神奇的一道组合题。

首先我们考虑树状数组的结构。会发现 $a_i$ 最终一定只会对 $a_i$ 以及 $a_i$ 的祖先节点产生贡献。那么假设有两点 $u,v$，且 $u$ 在 $v$ 的上面 $d$ 层，考虑 $v$ 对 $u$ 会贡献多少次。**其实这等价于从 $v$ 开始走 $k$ 步（每一步可以选择不动）走到 $u$ 的路径总数**，因为每走一步都相当于是做了一次 $f$ 操作。而求这种路径数可以直接用插板法解决，答案为 $C_{d+k-1}^{k-1}$。

于是我们知道了每一个点对其祖先的贡献。又因为我们已知最终的 $b$ 序列，所以我们可以枚举每一个点以及它的所有祖先，将它祖先的值减去它对祖先的贡献即可。这样最终得到的就是原序列 $a$ 了。注意枚举点一定要从叶子往上枚举，因为需要保证当前点的儿子对它的贡献已经被减掉了，这样它对它祖先的贡献才是正确的。

因为每个点在树状数组上的祖先最多有 $\log(n)$ 个，所以总时间复杂度 $O(n \log n)$

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5 + 10;
const int mod = 998244353; 
int T,n,a[MAXN],inv[MAXN],k;	
inline int Lowbit(int x) {return (x & -x);}
signed main() {
	inv[0] = inv[1] = 1;
	for(int i = 2;i < MAXN;i++)
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;
 	for(cin >> T;T;T--,puts("")) {
		cin >> n >> k;
		for(int i = 1;i <= n;i++) cin >> a[i];
		for(int v = 1;v <= n;v++) {
			int C = 1;
			for(int d = 1,u = v + Lowbit(v);u <= n;u += Lowbit(u),d++) {
				C = C * ((d + k - 1) * inv[d] % mod) % mod;
				a[u] = (a[u] - C * a[v] % mod + mod) % mod;
			}
		}
		for(int i = 1;i <= n;i++) cout << a[i] << " ";
	} return 0;
} 
```

---

## 作者：鲤鱼江 (赞：2)

尺子好强，拜谢尺子。

题意：
定义映射 $f(a)$ 的作用为将数列 $a$ 映射到其对应的树状数组，给出 $f^k(a)$ 求 $a$。

~~啥？你说你不会树状数组？不可能吧？~~

比较小清新的好玩题，难度不大。

你考虑将树状数组的图画出来（树状数组当然是树状的），平时高度压缩的代码并不对我们的解题有什么帮助。

![](https://cdn.luogu.com.cn/upload/image_hosting/dmu6ermw.png)

我们每次树状数组求和都等价于子树求和，对吧？至于平时的树状数组单点加法，可以理解为一直爬链。

现在有了清晰的图，我们可以将问题具体一下：给出 $k$ 次子树和后的树，求原来的权值。一下子就明了可做了。

后面我就算不说大家也应该知道怎么做了吧？对于每一个节点，暴力向上跳，从它的父亲中去除它自己的贡献（注意每次从叶子开始跳）。

贡献系数是什么呢？好问题。

我们只考虑当前节点带来的贡献，并且把祖先都拿出来当作数列，则每次子树求和都相当求了一遍前缀和，这是不必说的，你可以手模几遍来找一下。

不过 $k$ 很大，需要 $O(1)$ 转移组合数，太套路所以自己想（也可以看我的代码）。

具体实现的话，我为了偷懒，是暴力找叶子跳的。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();
        	while(c<'0'||c>'9')c=getchar();x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer& operator << (char* str) {int cur=0;while(str[cur])putchar(str[cur++]);return *this;}
    	Writer& operator << (const char* str){int cur=0;while(str[cur])putchar(str[cur++]);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n' 
#define cin Fastio :: cin
#define cout Fastio :: cout

const int mod=998244353;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
    friend std::ostream& operator<<(std::ostream& os, const modint& a) { return os << a.val; }
};

const int N=4e5+10;
modint frac[N],inv[N],b[N],a[N];
int n,T,K;

void init(const int len){
	frac[0]=inv[0]=1;
	for(int i=1;i<=len;++i) frac[i]=frac[i-1]*i;
	inv[len]=frac[len].inv();
	for(int i=len-1;i;--i) inv[i]=inv[i+1]*(i+1);
	for(int i=1;i<=len;++i) inv[i]*=frac[i-1];
}
inline int lowbit(const int x){return x&(-x);}

int main(){
	cin>>T;init(400000);
	while(T--){
		cin>>n>>K;
		for(int i=1;i<=n;++i) cin>>b[i];
		for(int j=0;j<=20;++j){//枚举lowbit 
			for(int i=1;i<=n;++i){
				if((lowbit(i)>>j)&1){
					int ct=1;a[i]=b[i];modint tmp=1;
					for(int k=i;k<=n;k+=lowbit(k)){
						b[k]-=tmp*a[i];
						tmp*=inv[ct]*(K+ct-1);++ct;
					}
				}
			}
		}
		for(int i=1;i<=n;++i) cout<<a[i].val<<' ';cout<<endl;
	}
	return 0;
}
```

---

## 作者：FerventTemp0 (赞：1)

给的式子是一个 $\log$ 阶前缀和状物，所以最后每个位置必定是一个对 $k$ 的 $O(\log)$ 阶多项式，所以直接暴力跑前 $\log$ 次，然后对每个位置都插一遍就做完了。

复杂度 $O(n\log n)$，没什么细节，写完直接交就行。

[code](https://codeforces.com/contest/1967/submission/262263584)

这题衒技用组合做法，真要过题还得看插值，不用脑子还不容易写错，很适合我这样的猪。

update：改了一下代码，让它看起来更好看了。

---

## 作者：OtterZ (赞：1)

~~我们充分发扬人类智慧~~
# 题意
我们定义操作为：

$$
a_i = (\sum _ {j = \operatorname{lowbit}(i)}^i a_j) \bmod 998244353
$$
给出 $k$ 此操作后的结果 $b_i$，求原先数组 $a_i \bmod 998244353$ 的结果。
# 更改关系
由于 $k$ 非常大，且部分下标下的数不变，如 $a_1,a_3$，考虑先推更改关系，再用于推原数组。  
我们列举一下影响关系，易于知道这些关系简化成祖先到子孙的关系可以得到一棵树状数组。
# 贡献
对于祖先关系的两点，我们发现同层的两个点对共同祖先的更改可以按同类处理，我们可以考虑操作时 $a_1$ 对 $a_2,a_4$ 的影响：

1. 操作一次，$a_2$ 共加上一次 $a_1$，$a_4$ 加上一次 $a_1$。
1. 操作两次，$a_2$ 共加上 $2$ 次 $a_1$，$a_4$ 加上 $3$ 次 $a_1$。
1. 操作三次，$a_2$ 共加上 $3$ 次 $a_1$，$a_4$ 加上 $6$ 次 $a_1$。

由此我们猜测当 $j$ 节点为比 $i$ 节点高 $t$ 层的祖先，操作 $k$ 次后，$b_j$ 共加过 $\frac{(k + t - 1)!}{t! \cdot (k - 1)!}$ 次 $a_i$。

接下来证明：

1. 当 $t = 1$ 时，$b_j$ 加了 $k = \frac{(k +1 - 1)!}{1! \cdot (k - 1)!}$ 次 $a_i$，符合条件；
2. 若 $t = r$ 时成立，当 $t = r + 1$ 时，加上的倍数为：

$$
\sum _{o = 1}^ {k} \frac{(o + r - 1)!}{r! \cdot (o - 1)!}
$$

因为

$$
\frac{(o + r - 1)!}{r! \cdot (o - 1)!} = \frac{1}{r + 1}\cdot (\frac{(o + r)!}{r! \cdot (o - 1)!} - \frac{(o + r - 1)!}{r! \cdot (o - 2)!})
$$

故

$$
\begin{aligned}
\sum _{o = 1}^ {k} \frac{(o + r - 1)!}{r! \cdot (o - 1)!}
&=  \frac{1}{r + 1}\cdot (\frac{(k + r)!}{r! \cdot (k - 1)!} - 0)\\
&= \frac{(k + (r + 1) - 1) !}{(r + 1) ! \cdot (k - 1) !} \\ &= \frac{(k + t - 1)!}{t! \cdot (k - 1)!}
\end{aligned}
$$

证毕。
# 3. 反推
我们易得可以从前往后遍历，遍历到 $i$ 时，我们减去 $a_i$ 因操作对相应的 $b_j$ 的贡献，就会得到答案。

通过类似树状数组的修改方法，可以得到一个 $\operatorname{O}(n\log n)$ 的方法。
# 4. 上代码

```cpp
#include<cstdio>
using namespace std;
int n,m,k,b[200009],dt[29],inv[29];
const int mod = 998244353;
int main(){
	scanf("%d",&m);
	while(m--){
		scanf("%d %d",&n,&k);
		dt[0] = 1;
		for(int i = 1; i <= 20; i ++){
			inv[i] = (i == 1) ? 1 : 1ll * (mod - mod / i) * inv[mod % i] % mod;
			dt[i] = 1ll * dt[i - 1] * (k + i - 1) % mod;
			dt[i] = 1ll * dt[i] * inv[i] % mod;
		}
		for(int i = 1; i <= n; i ++){
			scanf("%d",&b[i]);
		}
		for(int i = 1; i <= n; i ++){
			int o = i;
			for(int j = 1; o + (o & (-o)) <= n; j ++){
				o += o & (-o);
				b[o] = (b[o] - 1ll * b[i] * dt[j] % mod + mod) % mod;
				//printf("%d %d %d\n",i,o,b[o]);
			}
		}
		for(int i = 1; i <= n; i ++){
			printf("%d ",b[i]);
		}
		puts("");
		//return 0;
	}
	return 0;
}
```

---

## 作者：OE_AiHAn (赞：0)

## [CF1967C](https://codeforces.com/problemset/problem/1967/C)

### 题意
对于数组 $a$，有函数 $f(a)$，设数组 $s = f(a)$，则对于每一个 $s_i$，都有：

$$s_i = \left(\sum^{i}_{j = (i \operatorname{\& } (i - 1)) + 1}{a_j}\right)$$

其中 $\&$ 表示按位与运算。

对于一个正整数 $k$，函数 $f^k(a)$ 定义如下：

$$ f^k(a)=
\begin{cases}
    f(a)&k=1\\\\
    f(f^{k-1}(a))&k > 1
\end{cases}$$

给你正整数 $n, k$ 和一个长度为 $n$ 的数组 $b$ 表示 $f^k(a)$，求一个符合题意的数组 $a$，可以证明答案总是存在的。

### 解析
理解题意便可以看出，各个下标数值之间的关系形成一片森林，下标 $\operatorname{lowbit}$ 值（二进制形式下数字为 1 的最低数位对应值，如 $\operatorname{lowbit}(12) = 4$）越小，其对应节点在树上深度越大。明显每个 $a_i$ 仅对其自身和在该树上的祖先有贡献，且对自身的贡献为 1，对其有贡献的仅有自身及其后代。

![](https://cdn.luogu.com.cn/upload/image_hosting/3fvthsa2.png)

打表可看出对于下标 $i$ 和其祖先 $j$，贡献 $c_{i, j}$ 的大小仅与下标 $i, j$ 在树上的节点深度差有关，我们可以预处理在 $k$ 次函数计算后不同深度差下后代节点对祖先节点的贡献。设 $dp_{i, j}$ 表示深度差为 $i$ 时进行在 $f^j(a)$ 中后代节点对祖先节点的贡献。初始时除了 $dp_{1, 0} = 1$，其余 $dp_{i, j} = 0$，有转移方程：

$$dp_{i, j} = \sum_{l = 1}^{i}{dp_{l, j - 1}}$$

由于 $k$ 较大但 $i$ 的范围较小，我们可以考虑通过矩阵加速优化计算 $dp_{i, k}$ 的过程。

预处理完贡献值后，自底向上倒推，在祖先节点中减去当前节点的贡献，最后该祖先节点 $i$ 保留的值就是原本 $a_i$ 的值。复杂度大概为 $O({\log}^3{n} \log{k} + n\log{n})$。

### 代码
```c++
#include <bits/stdc++.h>
#include <unordered_map>
#define LL long long
#define ll long long
#define double long double
#define pii pair<int, int>
#define pll pair<LL, LL>
#define pdd pair<double, double>

using namespace std;

//nxt数组用于记录下标的父节点下标，N为矩阵大小
LL a[200005], b[200005], pre[25][25], nxt[200005], N, mod = 998244353;

//矩阵加速
void mqpow(int n)
{
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            pre[i][j] = (i == j);

    LL M[25][25], cur[25][25];
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            M[i][j] = (i >= j);

    while (n)
    {
        if (n & 1)
        {
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    cur[i][j] = 0;
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    for (int k = 1; k <= N; k++)
                        cur[i][j] = (cur[i][j] + pre[i][k] * M[k][j] % mod) % mod;
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    pre[i][j] = cur[i][j];
        }
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                cur[i][j] = 0;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                for (int k = 1; k <= N; k++)
                    cur[i][j] = (cur[i][j] + M[i][k] * M[k][j] % mod) % mod;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                M[i][j] = cur[i][j];

        n >>= 1;
    }
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    //预处理nxt数组
    for (int i = 1; i <= 200000; i++)
    {
        int idx = 0, cur = i;
        while (!(cur & (1 << idx)))
            cur |= 1 << idx++;
        while (cur & (1 << idx))
            idx++;
        nxt[i] = cur ^ ((1 << (idx + 1)) - 1);
    }

    int T, n;
    LL k;
    cin >> T;
    while (T--)
    {
        cin >> n >> k;
        N = log2(n) + 1;
        for (int i = 1; i <= n; i++)
            cin >> b[i];

        mqpow(k); //预处理深度差产生的贡献系数
        for (int i = 1; i <= N; i++)
            for (int j = 1; j * (1 << (i - 1)) <= n; j += 2) //从叶子节点（lowbit值为1下标）开始倒推
            {
                int cur = j * (1 << (i - 1));
                a[cur] = b[cur]; //节点保留值即为答案
                for (int l = nxt[cur], m = 2; l <= n; l = nxt[l], m++)
                    b[l] = (b[l] + mod - a[cur] * pre[m][1] % mod) % mod; //从祖先节点中减去当前节点的贡献
            }

        for (int i = 1; i <= n; i++)
            cout << a[i] << " ";
        cout << "\n";
    }
}
```

最后祝各位顺利AC。>w<

---

## 作者：N1K_J (赞：0)

虽然看起来很困难，但其实也就看起来很吓人。

题目大意：称对一个长度为 $n$ 的序列 $a_1,a_2,a_3,\cdots,a_n$ 进行一次操作 $f$ 为对该序列建立一颗树状数组，令 $\{a_n\}$ 中的每一项为这个树状数组上对应位置。

例：$[1,2,3,4]$ 的树状数组为 $[1,3,3,10]$，故 $f([1,2,3,4]) = [1,3,3,10]$。

先给定一个序列 $k$ 次操作后的结果，求原序列。

注意到一个事实：不妨设结果为 $\{c_n\}$，初始序列为 $\{a_n\}$，$\forall i = 1,2,3,\cdots n,\exists p_1,p_2,p_3,\cdots,p_n \in N \; s.t. \; c_i = \sum p_ia_i$。

我们不妨考虑每个数对他后面的数的贡献。

如图，计算了 $a_1$ 对 $c_1,c_2,c_4,c_8$ 在 $k=1,2,3,4$ 下的贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/kbbuf4sg.png)

我们注意到，在树状数组上，$2$ 是 $1$ 的父亲，$4$ 是 $2$ 的父亲，$8$ 是 $4$ 的父亲。

我们不妨设 $x$ 是 $y$ 的 $d$ 级祖先，在 $k = k_0$ 时，$a_x$ 对 $c_y$ 的贡献应当为 $\dfrac{k_0 \cdot (k_0+1) \cdots (k_0+d-1)}{d!}$。

由此，我们用树状数组的方式从每个点往后跳，容易得到每个点的初始值，具体参考代码。

[Code](https://codeforces.com/contest/1972/submission/258911831)

---

## 作者：Priestess_SLG (赞：0)

为什么大家都会做这题啊呜呜呜/dk/dk/dk

题目名叫 Fenwick Tree 那就提示我们这题和 Fenwick Tree 有关。可以发现题目中给出的 $s_i$ 和 $a$ 中的关系正好就是树状数组中根节点和子树内结点的关系。而每一次操作，就是对于每一个结点，将其子树内所有结点的权值添加到她身上。

直接计算每一个点的贡献是困难的，考虑计算每一个点对其他结点产生的贡献。显然一个点 $x$ 对另一个点 $y$ 产生了至少 $1$ 的贡献，当且仅当 $x$ 在 $y$ 的子树内，同 $y$ 为 $x$ 的直属祖先结点。又因为 Fenwick Tree 中时间复杂度为 $O(\log n)$，所以树中所有结点 $x$ 都只有 $O(\log n)$ 个会因其产生贡献的结点。

现在问题变为：一个结点 $x$ 会对其直属祖先结点 $y$ 产生多少的贡献。这里设 $\text{depth}(x)$ 表示 $x$ 点在树中的深度，那么 $x,y$ 之间会有 $\text{depth}(x)-\text{depth}(y)$ 个结点来帮助传递 $x$ 到 $y$ 两个结点的贡献。可以发现路径上每一次产生贡献都是从 $x$ 向 $y$ 做一次链上前缀和，而题目中给定了 $k$ 则说明要做 $k$ 次链上前缀和。考虑将其移出链中，转移到数组上，并取出原有权值对答案的影响，那么问题变为：

+ 现在有一个长度为 $d$ 的数组 $a$，初始只有 $a_1=1$。对其做 $k$ 次前缀和，问 $a_d$ 的值是多少。

这个问题是十分经典的组合问题，容易证明答案为：$\binom{d+k-1}{d}$。又因为 Fenwick Tree 优秀的性质，树高为 $\log$ 级别，所以每一个点 $x$ 直接暴力往上跳祖先更新答案即可，无需使用各种高级 ds。另一个问题是虽然 $d\sim O(\log n)$，但是 $k\to10^9$。考虑计算组合数 $\binom{a}{b}$ 中，若 $a\to 10^9$ 而 $b\to 20$，则完全可以直接暴力的根据组合数展开 $O(\log n)$ 计算答案。因此问题得以解决，时间复杂度为 $O(n\log^2n)$。

有一种可爱的优化方法是每一组数据的 $k$ 均为常数，因此直接暴力打出 $d\sim O(\log n)$ 以内的所有组合数表，可以优化到 $O(n\log n)$ 求解，感觉真的不太能再优化了。

写的奇奇怪怪的代码：

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200010;
const int mod = 998244353;
int a[N], depth[N], up[N];
vector<int> adj[N], radj[N];
void dfs(int u, int fa) {
    up[u] = fa;
    depth[u] = depth[fa] + 1;
    for (int &v : radj[u])
        if (v != fa) dfs(v, u);
}
int power(int a, int b, int c) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % c;
        a = a * a % c, b >>= 1;
    }
    return ans;
}
int inversion(int x, int mod) {
    return power(x, mod - 2, mod);
}
int binom(int x, int y) {
    int sum = 1;
    for (int i = 1; i <= y; ++i) sum = sum * (x - i + 1) % mod;
    for (int i = 1; i <= y; ++i) sum = sum * inversion(i, mod) % mod;
    return sum;
}
int table[50], res[N];
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; ++i) cin >> a[i], depth[i] = up[i] = 0;
        for (int i = 1; i <= n; ++i) adj[i].clear(), radj[i].clear();
        for (int i = 1; i <= n; ++i) res[i] = a[i];
        for (int i = 1; i <= n; ++i) {
            int x = i + (i &- i);
            if (x <= n) {
                adj[i].emplace_back(x);
                radj[x].emplace_back(i);
            }
        }
        for (int i = 1; i <= n; ++i)
            if (!depth[i]) dfs(i, 0);
        for (int i = 1; i < 50; ++i) table[i] = binom(i + k - 1, i);
        for (int i = 1; i <= n; ++i) {
            vector<int> parent;
            int j = i;
            while (j) {
                j = up[j];
                if (j) parent.emplace_back(j);
            }
            for (int j = 0; j < parent.size(); ++j) {
                res[parent[j]] = (res[parent[j]] + mod - res[i] * table[j + 1] % mod) % mod;
                // cout << i << ' ' << parent[j] << ' ' << res[parent[j]] << ' ' << a[i] << ' ' << table[j + 1] << '\n';
            }
        }
        for (int i = 1; i <= n; ++i) cout << res[i] << ' ';
        cout << '\n';
    }
    return 0;
}
```

---

