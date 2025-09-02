# DNA Evolution

## 题目描述

Everyone knows that DNA strands consist of nucleotides. There are four types of nucleotides: "A", "T", "G", "C". A DNA strand is a sequence of nucleotides. Scientists decided to track evolution of a rare species, which DNA strand was string $ s $ initially.

Evolution of the species is described as a sequence of changes in the DNA. Every change is a change of some nucleotide, for example, the following change can happen in DNA strand "AAGC": the second nucleotide can change to "T" so that the resulting DNA strand is "ATGC".

Scientists know that some segments of the DNA strand can be affected by some unknown infections. They can represent an infection as a sequence of nucleotides. Scientists are interested if there are any changes caused by some infections. Thus they sometimes want to know the value of impact of some infection to some segment of the DNA. This value is computed as follows:

- Let the infection be represented as a string $ e $ , and let scientists be interested in DNA strand segment starting from position $ l $ to position $ r $ , inclusive.
- Prefix of the string $ eee... $ (i.e. the string that consists of infinitely many repeats of string $ e $ ) is written under the string $ s $ from position $ l $ to position $ r $ , inclusive.
- The value of impact is the number of positions where letter of string $ s $ coincided with the letter written under it.

Being a developer, Innokenty is interested in bioinformatics also, so the scientists asked him for help. Innokenty is busy preparing VK Cup, so he decided to delegate the problem to the competitors. Help the scientists!

## 说明/提示

Consider the first example. In the first query of second type all characters coincide, so the answer is $ 8 $ . In the second query we compare string "TTTTT..." and the substring "TGCAT". There are two matches. In the third query, after the DNA change, we compare string "TATAT..."' with substring "TGTAT". There are $ 4 $ matches.

## 样例 #1

### 输入

```
ATGCATGC
4
2 1 8 ATGC
2 2 6 TTT
1 4 T
2 2 6 TA
```

### 输出

```
8
2
4
```

## 样例 #2

### 输入

```
GAGTTGTTAA
6
2 3 4 TATGGTG
1 1 T
1 6 G
2 5 9 AGTAATA
1 10 G
2 2 6 TTGT
```

### 输出

```
0
3
1
```

# 题解

## 作者：封禁用户 (赞：7)

小蒟蒻又来水题解啦 QωQ

# 题目
将字符串 $e$ 重复多次，问与 $s$ 中的一个给定子串的重合字符数量。

显然就是对 $e$ 的每一个字符询问

$$\sum_{i=0}^{\lfloor\frac{r-l-x}{|e|}\rfloor}[s_{l+x+i|e|}=e_x]$$

# 思路
突破口在 $|e|\le 10$ 和 字符数量为 $4$ 这两点。

不难发现，对于一个 $e_x$ ，能够贡献的 $s$ 字符为 $l+x+i|e|$ ，**在模** $|e|$ **意义下相等**。所以，我们可以试着去求 $s$ 的一段区间中，下标模 $|e|$ 为一个特定值时，四种元素各有多少个。肯定是用前缀和啊！

用 $f(m,c,x)$ 存储

$$\sum_{i=0}^{+\infty}[s_{x-im}=c]$$

也就是，对于前 $x$ 个格子，若其下标在模 $m$ 意义下与 $x$ 同余，则分成四种字符存数量。

我们存前缀和，怎么修改？只好改成树状数组。树状数组可以考虑用 $\lfloor\frac{x}{m}\rfloor+1$ 作为关键字。

时间复杂度 $\mathcal O\big[|e|\cdot(n+q)\log n\big]$ ，大家都差不多。空间复杂度 $\mathcal O(|e|\cdot cn)$ ，比一些题解中的四维数组要好。

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef long long int_;
inline int readint(){
	int a = 0; char c = getchar(), f = 1;
	for(; c<'0'||c>'9'; c=getchar())
		if(c == '-') f = -f;
	for(; '0'<=c&&c<='9'; c=getchar())
		a = (a<<3)+(a<<1)+(c^48);
	return a*f;
}
inline void writeint(int x){
	if(x > 9) writeint(x/10);
	putchar((x%10)^48);
}

const int MaxN = 100005;
int n; // 文本串长度
/** @return 字符 @p c 的哈希值 */
inline int has(char c){
	switch(c){
		case 'A': return 0;
		case 'T': return 1;
		case 'G': return 2;
		case 'C': return 3;
	}
	return -1; // It's nothing
}

/** @brief c[i][j][x]: 求 @p x-ki 有多少个 @p j 类字符 */
int c[11][4][MaxN];
/**
 * @param m 选择的元素之间的间距
 * @param t 字符的种类
 **/
void modify(int m,int i,int t,int v){
	int p = i/m+1, q = i%m;
	for(; (p-1)*m+q<=n; p+=(p&-p))
		c[m][t][(p-1)*m+q] += v;
}
int query(int m,int i,int t){
	int res = 0, p = i/m+1, q = i%m;
	for(; p; p-=(p&-p))
		res += c[m][t][(p-1)*m+q];
	return res;
}

char s[MaxN], tmp[MaxN];
int main(){
	scanf("%s",s+1), n = strlen(s+1);
	for(int i=1; i<=n; ++i){
		s[i] = has(s[i]);
		for(int r=1; r<=10; ++r)
			modify(r,i,s[i],1);
	}
	int q = readint();
	while(q --){
		int opt = readint();
		if(opt == 1){
			int x = readint();
			scanf("%s",tmp);
			int nv = has(*tmp);
			for(int r=1; r<=10; ++r){
				modify(r,x,nv,1);
				modify(r,x,s[x],-1);
			}
			s[x] = nv; // 接过接力棒
		}
		if(opt == 2){
			int l = readint(), r = readint();
			scanf("%s",tmp);
			int m = strlen(tmp), ans = 0;
			for(int i=0; i<m; ++i){
				tmp[i] = has(tmp[i]);
				int id = l+i-m;
				if(0 < id) // 有用的查询
					ans -= query(m,id,tmp[i]);
				id = r/m*m+(l+i)%m;
				if(id > r) id -= m;
				if(0 < id) // 有用的查询
					ans += query(m,id,tmp[i]);
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：Crosser (赞：2)

BIT 入门题。

我们需要在字符串上维护两种操作：

- 单点修改。
- 给定模板串 $e$，区间查询有多少个位置下标模 $|e|$ 同余并且字符相同。

考虑到字符集只有 `ATCG`，$|e|\leq 10$，我们对每个字符，每个模数，每个余数分别开一个 BIT，加起来是 $400$ 个 BIT，执行单点修改区间查询即可。复杂度 $\mathcal O(|\Sigma||e|^2n\log(|\Sigma||e|^2n))=\mathcal O(n\log n)$。

一些处理上的问题：

- $x\bmod |e|$ 显然使用 $0$ 开始下标更方便，但是 BIT 内的下标依旧可以从 $1$ 开始，BIT 本身的下标 $x\bmod |e|$ 不影响 BIT 内修改操作的下标。只要指向正确的 BIT，BIT 内下标从啥开始都行。
- 没试过线段树，但是 BIT 常数小完全能过。题解区没有线段树，可能不卡常过不去。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct bit {
	int b[100005];
 	int lbit(int x) { return x & (-x); }
	void add(int x, int w = 1) { for(; x <= n; x += lbit(x)) b[x] += w; }
	int ask(int x) { int res = 0; for(; x; x -= lbit(x)) res += b[x]; return res; }
    int ask(int l, int r) { return ask(r) - ask(l - 1); }
} a[11][11], t[11][11], c[11][11], g[11][11];
void add(int x, char ch, int mod, int w) {
    if(ch == 'A') a[mod][x % mod].add(x + 1, w);
    if(ch == 'T') t[mod][x % mod].add(x + 1, w);
    if(ch == 'C') c[mod][x % mod].add(x + 1, w);
    if(ch == 'G') g[mod][x % mod].add(x + 1, w);
}
signed main() {
    string str; cin >> str; n = str.size(); int q; cin >> q;
    for(int i = 0; i < n; i++) {
        for(int mod = 1; mod <= 10; mod++) add(i, str[i], mod, 1);
    }
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            int x; cin >> x; x--; char ch; cin >> ch;
            for(int mod = 1; mod <= 10; mod++) add(x, ch, mod, 1), add(x, str[x], mod, -1);
            str[x] = ch;
        } else if(op == 2) {
            int l, r; string e; cin >> l >> r >> e; int mod = e.size();
            int res = 0;
            for(int i = 0; i < mod; i++) {
                if(e[i] == 'A') res += a[mod][(i + l - 1) % mod].ask(l, r);
                if(e[i] == 'T') res += t[mod][(i + l - 1) % mod].ask(l, r);
                if(e[i] == 'C') res += c[mod][(i + l - 1) % mod].ask(l, r);
                if(e[i] == 'G') res += g[mod][(i + l - 1) % mod].ask(l, r);
            }
            cout << res << endl;
        }
    }
    system("pause");
    return 0;
}
```

---

## 作者：Hagasei (赞：0)

看题发现 $|e|\le10$，于是想到分别维护整段，间隔 $1$，间隔 $2$，...间隔 $9$ 的各数出现次数，即使用 $55\times4=220$ 棵树状数组。然后就是板板了。

注，虽然只需要 $220$ 棵，但为了实现方便，代码中有四五百棵树状数组，一些无用。

`bit[x][i][j][k]` 维护下标 `%i==j` 的元素，核苷酸对应 `k` 。 

code:

```cpp
#include<bits/stdc++.h>
inline void wr(int ans){if(ans>9)wr(ans/10);putchar((ans%10)^48);}
inline void qr(int&ret){int x=0;char ch=getchar();while(ch<'0'||ch>'9')ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();ret=f?-x:x;}
using namespace std;
int bit[100005][11][10][4];//四维分别为
int n;
inline int lowbit(int x){return x&-x;}
inline void add(int w,int v,int x,int y,int z){
	while(w<=n){
		bit[w][x][y][z]+=v;
		w+=lowbit(w);
	}
}
inline int sum(int w,int x,int y,int z){
	int s=0;
	while(w){
		s+=bit[w][x][y][z];
		w-=lowbit(w);
	}
	return s;
}
char a[100005],e[15];
int tr[130];
int main(){
	freopen("virus.in","r",stdin);
	freopen("virus.out","w",stdout);
	tr['T']=1,tr['G']=2,tr['C']=3;
	cin>>a+1;
	n=strlen(a+1);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=10;++j){
			add(i,1,j,i%j,tr[a[i]]);
		}
	} 
	int m;
	qr(m);
	int op,x,y;
	while(m--){
		qr(op),qr(x);
		if(op==2){
			qr(y);
			cin>>e;
			int l=strlen(e),ans=0;
			for(int i=0;i<l;++i){
				ans+=sum(y,l,(x+i)%l,tr[e[i]])-sum(x-1,l,(x+i)%l,tr[e[i]]);
			}
			wr(ans);
			putchar('\n');
		}
		else{
			char p;
			cin>>p;
			for(int j=1;j<=10;++j){
				add(x,-1,j,x%j,tr[a[x]]);
			}
			a[x]=p;
			for(int j=1;j<=10;++j){
				add(x,1,j,x%j,tr[a[x]]);
			}
		}
	}
}
```

---

## 作者：Others (赞：0)

这题较为简单，考试的时候第一个想到的是~~分块均摊复杂度~~，甚至在没看到 $e$ 的长度前以为这题要~~根号分治~~。

这题的查询的 $e$ 对应的每个位置他模 $e$ 的长度是一样的而且 $e$ 的长度只有 $10$，所以可以开 $10*10*4$ 个树状数组就完了，这里的 cache 要好好的卡，不然就 $MLE$ 了。

**Code**

```cpp
#include <bits/stdc++.h>
#define ll long long
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define lowbit(x) (x&-x)
using namespace std;
int m,n,l,r,opt,bit[100005][11][10][5],a[100005],base[100005],len,ans,tmp;
char s[100005];
void add(int a,int b,int c,int d,int e){
	while(a<=n){
		bit[a][b][c][d]+=e;
		a+=lowbit(a);
	}
}
int getsum(int a,int b,int c,int d){
	int tot=0;
	while(a){
		tot+=bit[a][b][c][d];
		a-=lowbit(a);
	}
	return tot;
}
int main() {
	freopen("virus.in","r",stdin);
	freopen("virus.out","w",stdout);
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	base['A']=1,base['T']=2,base['C']=3,base['G']=4;
	for(int i=1;i<=n;i++) {
		a[i]=base[s[i]];
		for(int j=1;j<=10;j++){
			add(i,j,i%j,a[i],1);
		}
	}
	while(m--){
		scanf("%d",&opt);
		if(opt^2){
			scanf("%d%s",&l,s+1);
			for(int i=1;i<=10;i++){
				add(l,i,l%i,a[l],-1);
			}
			a[l]=base[s[1]];
			for(int i=1;i<=10;i++){
				add(l,i,l%i,a[l],1);
			}
		}else{
			scanf("%d%d%s",&l,&r,s+1);
			len=strlen(s+1);
			ans=0,tmp=(l%len==0?len:l%len)-1;
			for(int i=1;i<=len;i++){
				ans+=(getsum(r,len,((i+tmp)%len+len)%len,base[s[i]])-getsum(l-1,len,((i+tmp)%len+len)%len,base[s[i]]));
			}
			cout << ans << endl;
		}
	}
	return 0;
}
```

---

## 作者：_acat_ (赞：0)

## 题目大意：

给一个长度只包含 $A$,$T$,$C$,$G$ 的字符串，$q$ 次操作，每次有两种：

1. 修改某个位置的字母。
2. 给定一个字符串 $s(|s|\le 10)$，生成一个重复的新串 $sssss \cdots$。询问 $[L,R]$ 中有几个字母跟新字符串对应。

## Sol
设母串为 $T$，询问字符串为 $s$。

注意到每次询问中的字符串 $s$ 长度不超过 $10$，记 $len = |s|$。

假设每次询问的区间都是 $[1,n]$。

我们只对 $T$ 中前 $len$ 个字符考虑。

对于 $s_i$，我们要判断的是 $T_i$，$T_{i+len}$，$T_{i+2len}$ $\cdots$ $T_{i+klen}$ $(i+klen\le n)$ 是否等于 $s_i$ 即可。

分析对于每种可能的 $len$ (最多 $10$ 种情况）

1. 对于每个 $i$。
2. 对于每个可能的 $s_i$。

我们都建立一个长度为 $n$ 的树状数组，其中第 $j$ 位表示 $T_j$ 是否和 $s_i$ 相等。

且其中 $j$ 只需要取 $\{i,i+len,i+2len,\cdots,i+klen\}$。

总共需预处理 $4 \times (1+2+3+\cdots+10)=220$ 个长度为 $n$ 的树状数组。

再分析对于一般询问 $[L,R]$，长度为 $len$ 的 $s$

只需要对 $T_{L,\cdots,R}$ 的前 $len$ 个字符考虑即可。

对于 $T_L$，我们先找到 $i$。

然后在 $(len,i,s_i)$ 对应的树状数组上查询 $[L,R]$ 上有几个 $1$ 即可。

## 核心代码

```cpp
#define N 100010
int n,m, sum[4][11][11][N],has[128];
char t[N],s[20];
int lowbit(int x){
    return x&(-x);
}
void change(int c,int p,int v){
    for(int x=p;x<=n;x+=lowbit(x)){
        for(int j=1;j<=10;j++){
            sum[c][j][p%j][x]+=v;
        }
    }
}
int query(int c,int len,int p,int x){
    int ret=0;
    while(x){
        ret+=sum[c][1en][p][x];
        x-=lowbit(x);
    }
    return ret;
}
int main() {
    has['A']=0,has['T']=1,has['C']=2,has['G']=3;
    scanf("%s" ,t+1);
    n=strlen(t+1); 
    for(int i=1;i<=n;i++)
        change(has[t[i]],i,1);
    int op,1,r,x;
    char c;
    m=read();
    while(m--){
        op=read();
        if(op==1){
            scanf("%d %c",&x,&c); 
            change(has[t[x]],x,-1);
            change(has[c],x,1);
            t[x]=c;
        }else{
            scanf("%d %d %s",&1,&r,&s);
            int len=strlen(s), ans=0;
            for(int i=0;i<len;i++){
                ans+=query(has[s[i]],len, (i+1)%len,r);
                query(has[s[i]],len,(i+l)%len,1-1);
                printf( "%d\n",ans);
            }
        }
    }
    return 0;
}
```

---

## 作者：lluoguu (赞：0)

# 思路

设子串为 $T$，询问字符串为 $s$。

注意到每次询问中的字符串 $s$ 长度不超过 $10$,记 $Len = |s|$。
假设每次询问的区间都是 $[1,n]$。
我们只对 $T$ 中前 $Len$ 个字符考虑。
对于 $s[i]$，我们要判断的是 $T[i]$，$T[i+Len],T[i+2Len]\ldots T[i+kLen] (i+kLen\leq n)$是否等于 s[i] 即可。

然后我们分析对于每种可能的 $Len$。

对于每个可能的 s[i]，我们都建立一个长度为 $n$ 的树状数组，其中第 $j$ 为表示 $T[j]$ 是否和 $s[i]$ 相等。

且其中 $j$ 只需要取 $(i,i+Len,i+2len,\ldots i+kLen)$ 总共需预处理 $4\times(1+2+3+\ldots 10)=220$ 个长度为 $n$ 的树状数组。

不会时间超限，去打代码吧！

---

