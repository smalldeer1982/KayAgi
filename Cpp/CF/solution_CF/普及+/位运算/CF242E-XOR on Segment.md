# XOR on Segment

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . You are allowed to perform two operations on this array:

1. Calculate the sum of current array elements on the segment $ [l,r] $ , that is, count value $ a_{l}+a_{l+1}+...+a_{r} $ .
2. Apply the xor operation with a given number $ x $ to each array element on the segment $ [l,r] $ , that is, execute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a6ed6800239445c652bf1618450a09b2fce8b86d.png). This operation changes exactly $ r-l+1 $ array elements.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise xor operation to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example in language C++ and Java it is marked as "^", in Pascal — as "xor".

You've got a list of $ m $ operations of the indicated type. Your task is to perform all given operations, for each sum query you should print the result you get.

## 样例 #1

### 输入

```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3
```

### 输出

```
26
22
0
34
11
```

## 样例 #2

### 输入

```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3
```

### 输出

```
38
28
```

# 题解

## 作者：gzw2005 (赞：65)

# 简明题意

给定一长度为 $N$ 的序列，有两种操作： 

- 求区间 $[L,R]$ 的和；
- 将区间 $[L,R]$ 中的每个元素与 $x$ 异或。

---

# 题解

平常的线段树都是动态区间询问和或者最值，但是这一道题将修改操作改成了区间异或，显然，我们无法像普通线段树一样操作。

如果难于思考，不如简化问题：我们假设每个元素 **不是 $0$ 就是 $1$** ，与之异或的数也是 $0$ 或 $1$。找一下规律：

假设这个序列为 $\{0,1,1,0,1\}$。

第一次所有的数和 $0$ 异或：$\{0,1,1,0,1\}$；

第二次所有的数和 $1$ 异或：$\{1,0,0,1,0\}$；

第三次所有的数和 $1$ 异或：$\{0,1,1,0,1\}$。

发现了什么？

- 如果和 $0$ 异或，那么 $1$ 的个数不变；
- 如果和 $1$ 异或，相当于将**区间取反**，那么 $1$ 的个数为原来 $0$ 的个数，即 $1$ 的个数为 $序列长度 - 1的个数$。

---

于是，可以将每个数转成二进制，然后定义线段树中 $f(l,r,i)$ 为在区间 $[l,r]$ 中**第 $i$ 进制位为 $1$ 的个数**。

如果要与 $x$ 异或，那么将 $x$ 拆成二进制，如果第 $i$ 进制位为 $1$ 那么 $f(l,r,i)=(r-l+1)-f(l,r,i)$；如果为 $0$ 则不变。（和之前发现的规律相类似）

如果要求和，那么就是每个 $f(l,r,i)$ 的个数乘以 $2^i$ 求和即可。

因为 $a[i]\leq10^6$，因此只需 $20$ 个进制位，那么时间复杂度要在原先线段树的基础上乘个 $20$ 即 $O(20n\log n)$。

# 参考程序

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int read(){
	char ch=getchar();int num=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while('0'<=ch&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
	return num;
}
const int MAXN=1e5+2;
int N,M,a[MAXN];
int cnt[MAXN<<2][20],tag[MAXN<<2];
#define ls(i) i<<1
#define rs(i) (i<<1)|1
void up(int cur){
	for(int i=0;i<20;i++)
		cnt[cur][i]=cnt[ls(cur)][i]+cnt[rs(cur)][i];
}
void buildTree(int L,int R,int cur){
	if(L==R){
		for(int i=0;i<20;i++)
			if((a[L]>>i)&1)cnt[cur][i]=1;
		return;
	}
	int mid=(L+R)>>1;
	buildTree(L,mid,ls(cur));
	buildTree(mid+1,R,rs(cur));
	up(cur);
}
void down(int L,int R,int cur){
	int mid=(L+R)>>1;
	for(int i=0;i<20;i++)
		if((tag[cur]>>i)&1){//区间取反 
			cnt[ls(cur)][i]=(mid-L+1)-cnt[ls(cur)][i];
			cnt[rs(cur)][i]=(R-mid)-cnt[rs(cur)][i];
		}
	tag[ls(cur)]^=tag[cur];
	tag[rs(cur)]^=tag[cur];
	tag[cur]=0;
}
void update(int L,int R,int cur,int l,int r,int val){
	if(R<l||r<L)return;
	if(l<=L && R<=r){
		for(int i=0;i<20;i++)//区间取反 
			if((val>>i)&1)cnt[cur][i]=(R-L+1)-cnt[cur][i];
		tag[cur]^=val;
		return;
	}
	int mid=(L+R)>>1;
	down(L,R,cur);//下传标记 
	update(L,mid,ls(cur),l,r,val);
	update(mid+1,R,rs(cur),l,r,val);
	up(cur);
}
long long query(int L,int R,int cur,int l,int r){
	if(R<l||r<L)return 0;
	if(l<=L && R<=r){
		long long ret=0,Pow=1;
		for(int i=0;i<20;i++){//求和 
			ret+=Pow*cnt[cur][i];
			Pow<<=1;
		}
		return ret;
	}
	int mid=(L+R)>>1;
	down(L,R,cur);
	return query(L,mid,ls(cur),l,r)+query(mid+1,R,rs(cur),l,r);
}
int main(){
	N=read();
	for(int i=1;i<=N;i++)a[i]=read();
	buildTree(1,N,1);
	M=read();
	for(int i=1,opt,L,R;i<=M;i++){
		opt=read();L=read();R=read();
		if(opt==1)printf("%lld\n",query(1,N,1,L,R));
		else update(1,N,1,L,R,read());
	}
	return 0;
}
```

---

## 作者：若玉 (赞：53)

~~其实并不需要什么神奇的线段树~~  
首先我们来观察n和m的大小  
n<=1e5,m<=5* 1e4  
知道了这个  
我们再观察一下时限  
有4s  
然后我们考虑暴力  
正常的暴力肯定会TLE  
加入快读  
还是会TLE  
##### 所以我们要用到循环展开大法！！！  

我是展到了8次，  
就可以轻松愉快的卡过此题啦！！！  
```.cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,opt,x,y,z,m,a[N],l;
long long ans;
int read()
{
	int sum=0;char ch=getchar();
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch>='0' && ch<='9')
	{
		sum=sum*10+ch-'0';
		ch=getchar();
	}
	return sum;
}
int main()
{
	n=read();
	for (int i=1;i<=n;i++)
	  a[i]=read();
	m=read();
	while (m--)
	{
		opt=read();x=read();y=read();
		if (opt==1)
		{
		  ans=0;
		  for (int i=x;i<=y;i+=7)
		    ans+=a[i]+a[i+1]+a[i+2]+a[i+3]+a[i+4]+a[i+5]+a[i+6],l=i;
		  for (int i=l;i<=l+6;i++)
		    if (i>y) ans-=a[i];
		  printf("%I64d\n",ans);
	    }
	    else
	    {
	    	z=read();
	    	for (int i=x;i<=y;i+=7)
	    	{
	    	  a[i]^=z;
	    	  a[i+1]^=z;
	    	  a[i+2]^=z;
	    	  a[i+3]^=z;
	    	  a[i+4]^=z;
	    	  a[i+5]^=z;
	    	  a[i+6]^=z;
	    	  l=i;
	        }
	        for (int i=l;i<=l+6;i++)
	          if (i>y) a[i]^=z;
		}
	}
	return 0;
}
```

---

## 作者：SymphonyOfEuler (赞：15)

给你一个数列，给你 $l,r$ ，操作两种，第一是区间求和，第二是区间异或 $x$。

异或的法则就是为：0⊕0=0，1⊕0=1，0⊕1=1，1⊕1=0（同为0，异为1）

因为区间查询和异或修改不兼容，所以需要拆位线段树。

用拆位线段树，数组 $cnt$ 来维护每个区间范围内 $1$ 的个数。标签如果是 $1$ 表示需要反转。

把一个数字拆二进制位，异或时，异或每一位。所以就是01互相交换操作。

拆位大概拆到 $20$ 即可。

```
//XOR on segment

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int n, m, a[MAXN], tag[25][MAXN * 4], cnt[25][MAXN * 4], d[MAXN * 4];

inline int lc(int p) { return p << 1; } //left child

inline int rc(int p) { return p << 1 | 1; } //right child

inline int read() {
    register char c = getchar();
    register int x = 0, f = 1;
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    return x * f;
}

inline void write(register int x) {
    if (x == 0) putchar('0');
    else {
        register int st[33], tp = 0;
        while (st[++tp] = x % 10, x /= 10);
        while (putchar(st[tp] ^ 48), --tp);
    }
    putchar('\n');
}

void push_up(int p, int x) {
    cnt[x][p] = cnt[x][lc(p)] + cnt[x][rc(p)];
}

void move_tag(int p, int l, int r, int x) {
    cnt[x][p] = (r - l + 1) - cnt[x][p];
    tag[x][p] ^= 1;
}

void push_down(int p, int l, int r, int x) {
    if (tag[x][p] != 0) {
        int mid = (l + r) >> 1;
        move_tag(lc(p), l, mid, x);
        move_tag(rc(p), mid + 1, r, x);
        tag[x][p] = 0;
    }
}

void build_tree(int p, int l, int r, int x) { //建树
    if (l == r) {
        cnt[x][p] = (a[l] & d[x]) != 0;
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(lc(p), l, mid, x);
    build_tree(rc(p), mid + 1, r, x);
    push_up(p, x);
}

int query(int p, int l, int r, int ql, int qr, int x) { //求和
    if (ql <= l && r <= qr) {
        return cnt[x][p];
    }
    push_down(p, l, r, x);
    int res = 0, mid = (l + r) >> 1;
    if (ql <= mid) {
        res += query(lc(p), l, mid, ql, qr, x);
    }
    if (qr > mid) {
        res += query(rc(p), mid + 1, r, ql, qr, x);
    }
    return res;
}

void update(int p, int l, int r, int ql, int qr, int x) { //反转
    if (ql <= l && r <= qr) {
        move_tag(p, l, r, x);
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p, l, r, x);
    if (ql <= mid) {
        update(lc(p), l, mid, ql, qr, x);
    }
    if (qr > mid) {
        update(rc(p), mid + 1, r, ql, qr, x);
    }
    push_up(p, x);
}

void solve() {
    n = read();
    for (int i = 0; i < 20; ++i) { //初始化（一定要初始化）
        d[i] = (1 << i);
    }
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
    }
    for (int i = 0; i < 20; ++i) {
        build_tree(1, 1, n, i);
    }
    m = read();
    while (m--) {
        int op = read();
        int l = read(), r = read();
        if (op == 1) {
            long long res = 0; //开ll
            for (int i = 0; i < 20; ++i) {
                res += 1LL * d[i] * query(1, 1, n, l, r, i);
            }
            cout << res << '\n';
        }
        if (op == 2) {
            int x = read();
            for (int i = 0; i < 20; ++i) {
                if (x & d[i]) update(1, 1, n, l, r, i);
            }
        }
    }
}

int main() {
    solve();
    return 0;
}
```



---

## 作者：critnos (赞：12)

暴力草标算。

除了循环展开还有什么办法呢？指令集！

这东西的原理类似压位高精，把多个数同时处理。

说句闲话，因为这题要 `long long` 所以并不利于指令集。因为指令集一般只有 $256$ 位，可以压 $8$ 个 `int` （$\dfrac {256} {32}=8$），但却只能压 $4$ 个 `long long` （$\dfrac {256} {64}=4$）。

跑的比循环展开快多了。52.19s 和 26.95s 的差距。

```cpp
#pragma GCC target("avx,avx2")
#pragma GCC optimize("Ofast,fast-math")
#include<bits/stdc++.h>
#include<immintrin.h>
#define ll long long
using namespace std;
__m256i a[25005];
int read()
{
   int s=0;
   char ch=getchar();
   while(ch<'0'||ch>'9') ch=getchar();
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s;
}
void add(int l,int r,int x)
{
    for(;(l-1&3)&&l<=r;l++)
		((ll*)(a+(l>>2)+1))[(l&3)-1]^=x;
    if(l==r+1) return;
    for(;(r&3)&&l<=r;r--)
		((ll*)(a+(r>>2)+1))[(r&3)-1]^=x;
    if(l==r+1) return;
    l=(l>>2)+1,r>>=2;
    __m256i x2=_mm256_set_epi64x(x,x,x,x);
    for(;l<=r;l++)
		a[l]=_mm256_xor_si256(a[l],x2);
}
ll ask(int l,int r)
{
    int i;
    ll s=0;
    for(;(l-1&3)&&l<=r;l++)
		s+=((ll*)(a+(l>>2)+1))[(l&3)-1];
    if(l==r+1) return s;
    for(;(r&3)&&l<=r;r--)
		s+=((ll*)(a+(r>>2)+1))[(r&3)-1];
    if(l==r+1) return s;
    l=(l>>2)+1,r>>=2;
    __m256i s2=_mm256_set_epi64x(0,0,0,0);
    for(;l<=r;l++)
		s2=_mm256_add_epi64(a[l],s2);
    for(i=0;i<4;i++)
        s+=((ll*)&s2)[i];
    return s;
}
int main()
{
	int n,q,opt,l,r,i,j,p;
	int x[10];
    scanf("%d",&n);
    for(i=1;i<=n>>2;i++)
    {
        for(j=0;j<4;j++)
            scanf("%d",&x[j]);
        a[i]=_mm256_set_epi64x(x[3],x[2],x[1],x[0]);
    }
    for(i=0;i<(n&3);i++)
        scanf("%d",&x[i]);
    a[(n>>2)+1]=_mm256_set_epi64x(x[3],x[2],x[1],x[0]);
    scanf("%d",&q);
	while(q--)
    {
        opt=read(),l=read(),r=read();
        if(opt==2)
        {
        	p=read();
			add(l,r,p);
		}   
        else printf("%lld\n",ask(l,r));
    }
}
```


---

## 作者：YLWang (赞：7)

一发过了来写个题解。

遇见异或问题，常见的思路无非就两种。

第一种是做前缀和。非常常见。

第二种就是拆位。01Trie就是这种思想的一个体现。

这题显而易见的要上个数据结构，然而传统的线段树并不能实现区间异或，原因就在于你对一个区间异或后无法维护他们的和。

那么就拆位喽。用21棵线段树分别维护每一个位置上的数。这样就变成了维护一个01串，操作就是区间异或0和1，区间询问1的个数。这是个经典的区间翻转问题，非常地简单。

希望大家能够从此篇题解中收益。
```cpp

const int MAXN = 100005, MAXW = 25;
int n, v[MAXW][MAXN];
struct Segment_tree {
	int n, val[MAXN << 2], tag[MAXN << 2];
	void Clear() {mst(val, 0); mst(tag, 0); n = 0;}
	#define ls (k << 1)
	#define rs (k << 1 | 1)
	#define mid ((l + r) >> 1)
	void Build(int num, int k, int l, int r) {
		if(l == r) {val[k] = v[num][l], tag[k] = 0; return;}
		Build(num, ls, l, mid); Build(num, rs, mid+1, r);
		val[k] = val[ls] + val[rs];
	}
	void pushdown(int k, int l, int r) {
		if(tag[k]) {
			tag[k] = 0, tag[ls] ^= 1, tag[rs] ^= 1;
			val[ls] = (mid-l+1) - val[ls];
			val[rs] = (r - mid) - val[rs];
//			assert(val[ls] >= 0); assert(val[rs] >= 0);
		}
	} 
	int query(int k, int l, int r, int ql, int qr) {
//		cout << l << ' ' << r << ' ' << ql << ' ' << qr << endl;
		if(l == ql && r == qr) return val[k];
		pushdown(k, l, r); assert(l <= r);
		if(qr <= mid) return query(ls, l, mid, ql, qr);
		else if(mid < ql) return query(rs, mid+1, r, ql, qr);
		else return query(ls, l, mid, ql, mid) + query(rs, mid+1, r, mid+1, qr);
	}
	int Query(int l, int r) {return query(1, 1, n, l, r);}
	void rev(int k, int l, int r, int rl, int rr) {
		if(l == rl && r == rr) {
			tag[k] ^= 1; val[k] = (r - l + 1) - val[k];
			return;
		}
		pushdown(k, l, r);
		if(rr <= mid) rev(ls, l, mid, rl, rr);
		else if(mid < rl) rev(rs, mid+1, r, rl, rr);
		else {rev(ls, l, mid, rl, mid); rev(rs, mid+1, r, mid+1, rr);}
		val[k] = val[ls] + val[rs];
	}
	void Reverse(int l, int r) {rev(1, 1, n, l, r);}
}tr[MAXW];
signed main()
{
	cin >> n;
	For(i, 1, n) {
		int x = read();
		for(int j = 0; (1 << j) <= x; j++)
			v[j][i] = (x >> j) & 1;
	}
	For(i, 0, 20) {
		tr[i].Clear(); tr[i].n = n; 
		tr[i].Build(i, 1, 1, n);
	}
	int Qnum = read();
	while(Qnum--) {
		int op = read(), l = read(), r = read();
		if(op == 1) {
			int ans = 0;
			For(i, 0, 20)
				ans += tr[i].Query(l, r) * (1ll << i);
			printf("%lld\n", ans);
		} else {
			int x = read();
			For(i, 0, 20)
				if((x >> i) & 1)
					tr[i].Reverse(l, r);
		}
	}
    return 0;
}
```

---

## 作者：破忆 (赞：5)

楼上的巨佬用的都是线段树

本蒟蒻用分块水一发题解


------------


### 【题目大意】

数列区间异或，区间求和

------------


### 【算法】
分块


------------

### 【分析】

#### 区间求和
在块内统计所有数的和
#### 区间异或
先统计区间内某位是$0，1$的个数

第$i$位记为$f[0/1][i]$

如果异或的那个数第$i$位为$1$

那么异或后就交换 $f[0][i]$与$f[1][i]$

并且在每个块记录公共异或和，方便单点异或
#### 单点查询
这个点当前值异或所在的块的异或和
#### 单点异或
先把当前点异或块内公共异或和

再针对修改前和修改后，分别计算对$f$数组以及区间和的影响


------------

### 【代码】
```cpp
#include<bits/stdc++.h>
#define IN inline
#define RE register 
#define LL long long
using namespace std;
const int maxn=1e5+5,maxt=maxn<<2,maxb=405;
int n,q,siz,cnt,p[22];
int a[maxn];
struct why{
	int l,r,tag,f[2][22]; 
	LL s;
   //s 是块内区间和，tag是公共异或和，f数组表示每位是0/1的数量
}block[maxb];

IN int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
LL write(LL x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}

IN LL query(int l,int r){//询问
	RE LL ret=0;
	for(RE int i=1;i<=cnt;i++){
		if(block[i].r<l) continue; //分离
		if(r<block[i].l) break;   //分离
		if(l<=block[i].l&&block[i].r<=r) ret+=block[i].s;else //包含
		if(block[i].l<=l&&r<=block[i].r){               //包含
			for(RE int j=l;j<=r;j++) ret+=(a[j]^block[i].tag);
			break;
		}else
		if(block[i].l<=l&&block[i].r<=r){  //相交
			for(RE int j=l;j<=block[i].r;j++) ret+=(a[j]^block[i].tag);
			continue;
		}else
		if(l<=block[i].l&&r<=block[i].r){  //相交
			for(RE int j=block[i].l;j<=r;j++) ret+=(a[j]^block[i].tag);
			continue;
		}
	}
	return ret;
}

IN void work(int l,int r,int x,int i){ //单点修改
	for(RE int j=l;j<=r;j++){
		a[j]^=block[i].tag;//先异或上区间异或和
		block[i].s-=a[j];
		for(RE int k=0;k<=21;k++){ //计算修改对区间的影响
			if(a[j]&(1<<k)) block[i].f[1][k]--;
			else block[i].f[0][k]--;
		}
		a[j]^=x;
		block[i].s+=a[j];
		for(RE int k=0;k<=21;k++){
			if(a[j]&(1<<k)) block[i].f[1][k]++;
			else block[i].f[0][k]++;
		}
		a[j]^=block[i].tag;
	}
}
IN void change(int l,int r,int x){//修改
	for(RE int i=1;i<=cnt;i++){
		if(block[i].r<l) continue;
		if(r<block[i].l) break;
		if(l<=block[i].l&&block[i].r<=r){
			block[i].tag^=x;
			block[i].s=0;
			for(RE int j=0;j<=21;j++){ //计算区间改变后的数据
				if(x&(1<<j)) swap(block[i].f[0][j],block[i].f[1][j]);
				block[i].s+=(1ll<<j)*block[i].f[1][j];
			}
			continue;
		}
		if(block[i].l<=l&&r<=block[i].r){  //相交
			work(l,r,x,i);
			break;
		}else
		if(block[i].l<=l&&block[i].r<=r){  //相交
			work(l,block[i].r,x,i);
			continue;
		}else
		if(l<=block[i].l&&r<=block[i].r){  //相交
			work(block[i].l,r,x,i);
			continue;
		}
	}
}

int main(){
	freopen("CF242E.in","r",stdin);
	freopen("CF242E.out","w",stdout);
	n=read(),q=read();
	siz=sqrt(n);
	for(RE int i=1;i<=n;i++){ //初始化先计算一遍需要的数据
		a[i]=read();
		if((i-1)%siz==0) block[++cnt].l=i;
		if(i%siz==0||i==n) block[cnt].r=i;
		block[cnt].s+=a[i];
		for(RE int j=0;j<=21;j++){
			if(a[i]&(1<<j)) block[cnt].f[1][j]++;
			else block[cnt].f[0][j]++;
		}
	}
	for(RE int i=1;i<=q;i++){
		int t=read();
		if(t==1){
			int l=read(),r=read();
			write(query(l,r));
			putchar(10);
		}
		else{
			int l=read(),r=read(),x=read();
			change(l,r,x);
		}
	}
//	printf("%d\n",clock()); 
	return 0;
}
```


---

## 作者：do_while_true (赞：4)

UPD: 删了很多废话。

如果你只想看这道题的解析，请直通 $\mathcal{Part2}$

## $\mathcal{Part1}$

#### 题目: [P2574](https://www.luogu.com.cn/problem/P2574)

简单概述一下就是维护一个01串的区间和，支持区间取反的操作。

取反可以看做异或操作。

可以用线段树维护这个操作，如果当前这一段区间要进行取反，区间内 $1$ 的个数 会变成(区间的元素个数-区间内 $1$ 的个数)，也就是 $0$ 的个数。

懒标记该怎么打，首先要明白一个性质: ```a^b^b==a```，可以通过枚举法证明只有一个二进制位的情况。可以扩展到多个二进制位。所以如果对一个区间连续取反偶数次，实际上相当于没有变化。所以当懒标记为奇数的时候，再进行取反操作。

#### $\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define re register
using namespace std;
struct node{
	ll l,r,sum,tag;
}tree[5000010];
ll n,m,ans,inp;
inline ll read()
{
	re ll r=0,w=1;
	re char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		r=(r<<3)+(r<<1)+(ch^48);
		ch=getchar();
	}
	return r*w;
}
inline void pushup(ll x){tree[x].sum=tree[x<<1].sum+tree[x<<1|1].sum;}
inline void pushdown(ll x)
{
	if(tree[x].tag){
		re ll p=tree[x].tag;
		tree[x].tag=0;
		tree[x<<1].tag+=p;tree[x<<1|1].tag+=p;
		if(p&1){
			tree[x<<1].sum=(tree[x<<1].r-tree[x<<1].l+1)-tree[x<<1].sum;
			tree[x<<1|1].sum=(tree[x<<1|1].r-tree[x<<1|1].l+1)-tree[x<<1|1].sum;
		}
	}
}
void build(ll x,ll l,ll r)
{
	tree[x].l=l;tree[x].r=r;
	if(l==r)
	{
		scanf("%1lld",&tree[x].sum);
		return ;
	}
	re ll mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void qurey(ll x,ll l,ll r)
{
	if(tree[x].l>=l&&tree[x].r<=r)
	{
		ans+=tree[x].sum;
		return ;
	}
	re ll mid=tree[x].l+tree[x].r>>1;
	pushdown(x);
	if(mid>=l) qurey(x<<1,l,r);
	if(mid<r) qurey(x<<1|1,l,r);
	pushup(x);
}
void change(ll x,ll l,ll r)
{
	if(tree[x].l>=l&&tree[x].r<=r)
	{
		tree[x].sum=(tree[x].r-tree[x].l+1)-tree[x].sum;
		tree[x].tag++;
		return ;
	}
	re ll mid=tree[x].l+tree[x].r>>1;
	pushdown(x);
	if(mid>=l) change(x<<1,l,r);
	if(mid<r) change(x<<1|1,l,r);
	pushup(x);
}
int main()
{
	n=read();m=read();
	build(1,1,n);
	re ll opt,x,y,k;
	while(m--)
	{
		opt=read();x=read();y=read();
		if(opt==0)
			change(1,x,y);
		else
		{
			ans=0;
			qurey(1,x,y);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

## $\mathcal{Part2}$

#### 题目: [CF242 E](http://codeforces.com/problemset/problem/242/E)

简单概述一下就是维护一个整数序列的区间和，支持区间异或一个数的操作。

我们来回顾一下 $\mathcal{Part1}$ 中```a^b^b==a```的证明中从一个二进制位(0或1)到多个二进制位(整数)是怎样扩展的。可以把按位异或看做每个二进制位的不进制加法，也就是说你一个二进制位的结果不会影响到其他二进制位的结果。所以这个结论成立。

因为整数序列里的数最大是 $10^6$ , 而 $2^{20}=1048576$ 所以这道题可以把这一个整数序列按照二进制位拆分成 $20$ 个01串，把这 $20$ 个01串按照 $\mathcal{Part1}$ 的方式，开 $20$ 个线段树进行维护。

因为每个二进制位互不干扰，所以我们开20个线段树分别维护每个二进制位不影响答案的正确性。

这样这道题就瞬间简单多了，注意空间大小，不要开得过多。

#### $\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#define ll int
#define re register
using namespace std;
struct node{
	ll l,r,tag;
	long long sum;
}tree[400010][22];
ll n,m,maxk,maxx,a[100001];
long long ans,ans2;
inline ll read()
{
	re ll r=0,w=1;
	re char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		r=(r<<3)+(r<<1)+(ch^48);
		ch=getchar();
	}
	return r*w;
}
inline void pushup(ll x,ll k){tree[x][k].sum=tree[x<<1][k].sum+tree[x<<1|1][k].sum;}
inline void pushdown(ll x,ll k)
{
	if(tree[x][k].tag){
		re ll p=tree[x][k].tag;
		tree[x][k].tag=0;
		tree[x<<1][k].tag+=p;
		tree[x<<1|1][k].tag+=p;
		if(p&1){
			tree[x<<1][k].sum=(tree[x<<1][k].r-tree[x<<1][k].l+1)-tree[x<<1][k].sum;
			tree[x<<1|1][k].sum=(tree[x<<1|1][k].r-tree[x<<1|1][k].l+1)-tree[x<<1|1][k].sum;
		}
	}
}
void build(ll x,ll l,ll r)
{
	for(int k=1;k<=21;k++)
		tree[x][k].l=l,tree[x][k].r=r;
	if(l==r)
	{
		for(int k=1;k<=21;k++)
			if(a[l]&(1<<(k-1)))
				tree[x][k].sum=1;
		return ;
	}
	re ll mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	for(int k=1;k<=21;k++)
		tree[x][k].sum=tree[x<<1][k].sum+tree[x<<1|1][k].sum;
}
void qurey(ll x,ll k,ll l,ll r)
{
	if(tree[x][k].l>=l&&tree[x][k].r<=r)
	{
		ans+=tree[x][k].sum<<(k-1);
		return ;
	}
	re ll mid=tree[x][k].l+tree[x][k].r>>1;
	pushdown(x,k);
	if(mid>=l) qurey(x<<1,k,l,r);
	if(mid<r) qurey(x<<1|1,k,l,r);
	pushup(x,k);
}
void change(ll x,ll k,ll l,ll r)
{
	if(tree[x][k].l>=l&&tree[x][k].r<=r)
	{
		tree[x][k].sum=(tree[x][k].r-tree[x][k].l+1)-tree[x][k].sum;
		tree[x][k].tag++;
		return ;
	}
	re ll mid=tree[x][k].l+tree[x][k].r>>1;
	pushdown(x,k);
	if(mid>=l) change(x<<1,k,l,r);
	if(mid<r) change(x<<1|1,k,l,r);
	pushup(x,k);
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	build(1,1,n);
	m=read();
	ll opt,l,r,inx,k;
	for(int i=1;i<=m;i++)
	{
		opt=read();l=read();r=read();
		if(opt==1){
			ans=0;
			for(int k=1;k<=21;k++)
			{
				ans2=0;
				qurey(1,k,l,r);
				ans+=ans2;
			}
			printf("%lld\n",ans);
		}
		else{
			inx=read();
			for(int k=1;1<<(k-1)<=inx;k++)
				if(inx&(1<<(k-1)))
					change(1,k,l,r);
		}
	}
	return 0;
}
```


---

## 作者：hovny (赞：4)

## [题面](https://www.luogu.org/problemnew/show/CF242E)

长度为$n$的数列，现有两种操作：

1、区间异或操作

2、区间求和操作

对于每个查询，输出答案

## 思路：

### 线段树+二进制拆位

线段树**区间修改**一般使用的都是**懒标记**的方法，但是对于异或，懒标记的方法显然是行不通的，于是就考虑**二进制拆位**

主要的思路就是将一个数，拆成若干个二进制位，然后对于**异或操作**，就转换成了**每一位上**的**异或操作**

分类讨论一下：

1、当$x$的第$i$位为$1$时，$1\ xor\ 0=1$，$1\ xor\ 1=0$

也就是看成**区间取反**操作

2、当$x$的第$i$位为$0$时，$0\ xor\ 0=0$，$0\ xor\ 1=1$

也就是说操作前后没有变化，所以就不执行修改操作

Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100010
using namespace std;
int n,a[N],res,L,R,T,x;
int f[N<<2][25],tag[N<<2][25];//1e6<2^20
ll b[25],ans;//别忘记long long
int read(){ int s=0;char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)){s=(s<<1)+(s<<3)+c-'0';c=getchar();}
    return s;
}
void built(int k,int l,int r)
{
	if(l>r) return;
	if(l==r)
	{
		res=a[l];
		for(int i=0;i<21;i++)//拆位
			if((res>>i)&1) f[k][i]=1;
		return;
	}
	int mid=(l+r)>>1,cur=k<<1;
	built(cur,l,mid);
	built(cur|1,mid+1,r);
	for(int i=0;i<21;i++)
		f[k][i]=f[cur][i]+f[cur|1][i];
	return;
}
void push(int k,int l,int r,int p)//p表示第几位
{
	f[k][p]=(r-l+1)-f[k][p];//区间取反
	if(l!=r)
	{
		int cur=k<<1;
		tag[cur][p]^=1;
		tag[cur|1][p]^=1;
	}
	tag[k][p]=0;
}
void Modify(int k,int l,int r,int p)//p同上
{
	if(tag[k][p]) push(k,l,r,p);
	if(r<L||R<l) return;
	if(L<=l&&r<=R)
	{
		push(k,l,r,p);
		return;
	}
	int mid=(l+r)>>1,cur=k<<1;
	Modify(cur,l,mid,p);
	Modify(cur|1,mid+1,r,p);
	f[k][p]=f[cur][p]+f[cur|1][p];
}
void Query(int k,int l,int r)//查询，所有位的懒标记都要下放
{
	for(int i=0;i<21;i++)
		if(tag[k][i]) push(k,l,r,i);
	if(r<L||R<l) return;
	if(L<=l&&r<=R)
	{
		for(int i=0;i<21;i++) ans+=f[k][i]*b[i];
		return;
	}
	int mid=(l+r)>>1,cur=k<<1;
	Query(cur,l,mid);
	Query(cur|1,mid+1,r);
}
int main()
{
    int i,j;b[0]=1;
    for(i=1;i<=21;i++) b[i]=b[i-1]<<1;//初不初始化都可以，就是上面b[i]要变成1<<i
    n=read();
    for(i=1;i<=n;i++) a[i]=read();
    built(1,1,n);
    T=read();
    while(T--)
    {
    	if(read()==1)
    	{
    		L=read();R=read();ans=0;
    		Query(1,1,n);
    		printf("%lld\n",ans);
		}
		else
		{
			L=read();R=read();x=read();
			for(i=0;i<21;i++)//判断x的第i位是不是1，并进行修改
				if((x>>i)&1) Modify(1,1,n,i);
		}
	}
    return 0;
}
```



---

## 作者：Luan_233 (赞：4)

## Solution

+ 看起来像是一个线段树题，但是这种位运算操作还是头一次见。注意到区间异或不可以直接累加，但是可以通过维护一些奇奇怪怪的定西来使这个操作变得可行。

+ 我们不妨牺牲一下空间，维护一个区间内 位权$2^i$的值为$1$的数的出现次数。对于位运算来讲，每一位的运算都是独立的，所以说对于一个新加入的数，直接$O(logn)$统计要异或上的值的每一位，若某一位是$1$则翻转当前区间的这个位权，对应的$sum$也要随之改变，$pushup$，$pushdown$维护一下就好。具体的实现可以看代码。总体复杂度$O(qlog^2n)$。

## Code

```
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

#define N 200005
#define Re register

using namespace std;

template<typename T> inline void read(T &x){
    x=0; char ch=getchar();
    while((ch<'0')||(ch>'9')) ch=getchar();
    while((ch>='0')&&(ch<='9')){
        x=(x<<1)+(x<<3)+(ch^'0');
        ch=getchar();
    }
}

typedef long long LL;

int n,q,l[N],r[N],ls[N],rs[N],bit[N][23],lazy[N],cnt;

LL sum[N];

inline void pushup(int cur){
    sum[cur]=0;
    for(Re int i=0;i<=20;i++){
        bit[cur][i]=bit[ls[cur]][i]+bit[rs[cur]][i];
        sum[cur]+=(1ll<<i)*bit[cur][i];
    }
}

void build(int L,int R,int cur){
    if(L==R){
        read(sum[cur]);
        for(Re int i=0;i<=20;++i){
            bit[cur][i]=(sum[cur]&(1<<i))?1:0;
        }
        l[cur]=r[cur]=L;
        return ;
    }
    int mid=(L+R)>>1;
    ls[cur]=++cnt; build(L,mid,ls[cur]);
    rs[cur]=++cnt; build(mid+1,R,rs[cur]);
    l[cur]=l[ls[cur]],r[cur]=r[rs[cur]];
    pushup(cur);
}

inline void pushdown(int cur){
    if(!lazy[cur]) return ;
    lazy[ls[cur]]^=lazy[cur],lazy[rs[cur]]^=lazy[cur];
    for(Re int i=0;i<=20;i++){
        if(lazy[cur]&(1<<i)){
            sum[ls[cur]]-=(1ll<<i)*bit[ls[cur]][i];
            bit[ls[cur]][i]=r[ls[cur]]-l[ls[cur]]+1-bit[ls[cur]][i];
            sum[ls[cur]]+=(1ll<<i)*bit[ls[cur]][i];
        }
        if(lazy[cur]&(1<<i)){
            sum[rs[cur]]-=(1ll<<i)*bit[rs[cur]][i];
            bit[rs[cur]][i]=r[rs[cur]]-l[rs[cur]]+1-bit[rs[cur]][i];
            sum[rs[cur]]+=(1ll<<i)*bit[rs[cur]][i];
        }
    }
    lazy[cur]=0;
}

void update(int L,int R,int cur,int val){
    if((L<=l[cur])&&(R>=r[cur])){
        for(Re int i=0;i<=20;i++){
            if(!(val&(1<<i))) continue;
            sum[cur]-=(1ll<<i)*bit[cur][i];
            bit[cur][i]=r[cur]-l[cur]+1-bit[cur][i];
            sum[cur]+=(1ll<<i)*bit[cur][i];
        }
        lazy[cur]^=val;
        return ;
    }
    pushdown(cur);
    int mid=(l[cur]+r[cur])>>1;
    if(L<=mid) update(L,R,ls[cur],val);
    if(R>mid) update(L,R,rs[cur],val);
    pushup(cur);
}

LL query(int L,int R,int cur){
    if((L<=l[cur])&&(R>=r[cur])) return sum[cur];
    int mid=(l[cur]+r[cur])>>1; LL ret=0;
    pushdown(cur);
    if(L<=mid) ret+=query(L,R,ls[cur]);
    if(R>mid) ret+=query(L,R,rs[cur]);
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    read(n);
    build(1,n,++cnt);
    read(q);
    while(q--){
        int opt,li,ri,xi;
        read(opt);
        if(opt==1){
            read(li),read(ri);
            printf("%lld\n",query(li,ri,1));
        }
        else if(opt==2){
            read(li),read(ri),read(xi);
            update(li,ri,1,xi);
        }
    }
    return 0;
}
```

---

## 作者：louhao088 (赞：1)

线段树+二进制

## 思路

最开始想要用和直接异或

但着很显然是不行的

如 $(1xor1)+(1xor1)=0$而$(1+1)xor1=3$

所以不能那么做


------------

那要怎么做呢

我们很快想到，因为是$xor$运算，所以可以按位来做，把所有值都转二进制，在线段树中维护即可

遇到异或时，若异或值为1就全部取反，否则不变


```cpp
 void x2(int x)//转二进制
 {
 	t=0;
  	while(x)b[++t]=x%2,x=x/2;
 }
 void yihuo(int x,int rt)//异或
 {
  	x2(x);
  	for(int i=1;i<=t;i++)
  		if(b[i])tr[rt].c[i]=(tr[rt].r-tr[rt].l+1)-tr[rt].c[i];
 }
  
```

求和时只要把每位相加即可

注意要$push$和$pushup$


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
const int maxn=1e5+5;
#define ls rt<<1
#define rs rt<<1|1
struct node
{
	int l,r,tag,c[22];
}tr[maxn*4];
int a[maxn],b[22],n,m,x,y,z,k,t;
void x2(int x)
{
	t=0;
	while(x)
	{
		b[++t]=x%2;x=x/2;
	}
}
void pushup(int rt)
{
	for(int i=1;i<=21;i++)
		tr[rt].c[i]=tr[ls].c[i]+tr[rs].c[i];
}
void push(int rt)
{
	tr[rs].tag=tr[rt].tag^tr[rs].tag;tr[ls].tag=tr[ls].tag^tr[rt].tag;
	x2(tr[rt].tag);
	for(int i=1;i<=t;i++)
		if(b[i])tr[ls].c[i]=(tr[ls].r-tr[ls].l+1)-tr[ls].c[i];
	x2(tr[rt].tag);
	for(int i=1;i<=t;i++)
		if(b[i])tr[rs].c[i]=(tr[rs].r-tr[rs].l+1)-tr[rs].c[i];
	tr[rt].tag=0;
}
void build(int rt,int l,int r)
{
	tr[rt].l=l,tr[rt].r=r;tr[rt].tag=0;
	if(l==r)
	{
		x2(a[l]);
		for(int i=1;i<=t;i++)tr[rt].c[i]=b[i];
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);pushup(rt);
}
void change(int rt,int l,int r,int L,int R,int x)
{
	
	if(l>R||r<L)return;
	if(l>=L&&r<=R)
	{
		x2(x);
		for(int i=1;i<=t;i++)
			if(b[i])
				tr[rt].c[i]=(tr[rt].r-tr[rt].l+1)-tr[rt].c[i];
		tr[rt].tag=tr[rt].tag^x;
		return;
	}
	push(rt);int mid=l+r>>1;
	change(ls,l,mid,L,R,x),change(rs,mid+1,r,L,R,x);pushup(rt);
}
int query(int rt,int l,int r,int x,int y)
{
	if(l>y||r<x)return 0;
	if(l>=x&&r<=y)
	{
		int p=1,res=0;
		for(int i=1;i<=21;i++)
			res+=p*tr[rt].c[i],p=p*2;
		return res;
	}
	push(rt);int mid=l+r>>1;
	return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);m=read();
	for(int i=1;i<=m;i++)
	{
		k=read();
		if(k==1)
		{
			x=read(),y=read();
			printf("%lld\n",query(1,1,n,x,y));
		}
		else 
		{
			x=read(),y=read(),z=read();
			change(1,1,n,x,y,z);
		}
	}
	return 0;
}
```





---

## 作者：Warriors_Cat (赞：0)

简单题，做是为了复习线段树。

### $Solution:$

异或这个东西很难办，考虑拆位。

把一个数按照二进制拆位，每一位建立一棵线段树，一共有 $20$ 棵。

然后每一棵线段树的一个节点代表这个区间中 $1$ 的个数。

异或其实就相当于 $1$ 和 $0$ 的个数反过来。

于是这题就做完了，时间复杂度为 $O(q\log n \log a_i)$。

记得 `ans` 开 `long long`。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int N = 100010;
int n, m, a[N], opt, x, y, z, d[N << 2][30], f[N << 2][30];
inline void pushup(int p, int q){ d[p][q]= d[p << 1][q] + d[p << 1 | 1][q]; }
inline void upd(int p, int l, int r, int q){
	d[p][q] = (r - l + 1) - d[p][q];
	f[p][q] ^= 1;
}
inline void pushdown(int p, int l, int r, int q){
	if(f[p][q]){
		dingyi;
		upd(ls, l, mid, q);
		upd(rs, mid + 1, r, q);
		f[p][q] = 0;
	}
}
inline void build(int p, int l, int r, int q){
	if(l == r){ d[p][q] = ((a[l] & (1 << q)) ? 1 : 0); return; }
	dingyi; build(ls, l, mid, q); build(rs, mid + 1, r, q); pushup(p, q);
}
inline void change(int p, int l, int r, int x, int y, int q){
	if(x <= l && r <= y){ upd(p, l, r, q); return; } dingyi; pushdown(p, l, r, q);
	if(x <= mid) change(ls, l, mid, x, y, q);
	if(y > mid) change(rs, mid + 1, r, x, y, q);
	pushup(p, q);
}
inline int query(int p, int l, int r, int x, int y, int q){
	if(x <= l && r <= y) return d[p][q]; dingyi; pushdown(p, l, r, q); int ans = 0;
	if(x <= mid) ans += query(ls, l, mid, x, y, q);
	if(y > mid) ans += query(rs, mid + 1, r, x, y, q);
	return ans;
}
signed main(){
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 0; i <= 20; ++i) build(1, 1, n, i);
	m = read();
	while(m--){
		opt = read(); x = read(); y = read();
		if(opt == 1){
			int ans = 0;
			for(int i = 0; i <= 20; ++i) ans += (1 << i) * query(1, 1, n, x, y, i);
			printf("%lld\n", ans);
		}
		if(opt == 2){
			z = read();
			for(int i = 0; i <= 20; ++i) if(z & (1 << i)) change(1, 1, n, x, y, i);
		}
	}
	return 0;
}
```


---

## 作者：顾z (赞：0)

> ### Description
>
> 给定一个长为$n(n<=10^5)$的数组
>
> 数组里的数不超过$10^6$
>
> 有两种操作：
>
> 1:求$sum[l,r]$;
>
> 2:对$[l,r]$中的所有数和$x$异或
>
> ### Input
>
> 第一行一个整数$n$,代表有一个长度为$n$的数组。
>
> 第二行$n$个整数,代表$a_i$
>
> 第三行为一个整数$m$,代表有$m$次操作。
>
> 接下来$m$行每行描述一个操作。
>
> ### Output
>
> 对于每一个操作$1$,输出一行代表$sum[l,r]$.

这题不错,**线段树+二进制拆位**

由于异或不具有叠加性,所以不能用$lazy$标记直接异或。

我们记录$tr[o][i]$代表当前节点$o$,二进制位$i$上是$1$的数有多少个。

由于,如果某一二进制位上原来为$1$,且当前异或的数$x$,当前二进制位上也有$1$,那么我们的当前$tr[o][i]=r-l+1-tr[o][i]$。

可以理解为$01$交换。

然后由于$2^{20}$比$10^6$要大。

所以只需要拆到$20$即可。

然后直接计算即可。

PS：记得开$long \ long$！

``代码``

```c++
#include<cstdio>
#include<algorithm>
#include<iostream>
#define int long long 
#define R register

using namespace std;

const int gz=1e5+8;

inline void in(R int &x)
{
	R int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}

int n,tr[gz<<2][21],tg[gz<<2],m;

#define ls o<<1
#define rs o<<1|1

inline void up(R int o)
{
	for(R int i=20;~i;i--)
		tr[o][i]=tr[ls][i]+tr[rs][i];
}

void build(R int o,R int l,R int r)
{
	if(l==r)
	{
		R int x;in(x);
		for(R int i=20;~i;i--)
			if((x>>i)&1)tr[o][i]++;
		return;
	}
	R int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	up(o);
}

inline void down(R int o,R int l,R int r)
{
	if(tg[o]==0)return;
	tg[ls]^=tg[o];tg[rs]^=tg[o];
	R int mid=(l+r)>>1;
	for(R int i=20;~i;i--)
	{
		if((tg[o]>>i)&1)
			tr[ls][i]=mid-l+1-tr[ls][i],
			tr[rs][i]=r-mid-tr[rs][i];
	}
	tg[o]=0;
	return;
}

void change(R int o,R int l,R int r,R int x,R int y,R int k)
{
	if(x<=l and y>=r)
	{
		tg[o]^=k;
		for(R int i=20;~i;i--)
			if((k>>i)&1)
				tr[o][i]=r-l+1-tr[o][i];
		return;
	}
	down(o,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)change(ls,l,mid,x,y,k);
	if(y>mid) change(rs,mid+1,r,x,y,k);
	up(o);
}

int query(R int o,R int l,R int r,R int x,R int y)
{
	if(x<=l and y>=r)
	{
		R int res=0;
		for(R int i=20;~i;i--)
			res+=(1<<i)*tr[o][i];
		return res;
	}
	down(o,l,r);
	R int mid=(l+r)>>1,as=0;
	if(x<=mid)as+=query(ls,l,mid,x,y);
	if(y>mid)as+=query(rs,mid+1,r,x,y);
	return as;
}

signed main()
{
	in(n);build(1,1,n);in(m);
	for(R int opt,l,r,x;m;m--)
	{
		in(opt);
		if(opt==1)
		{
			in(l),in(r);
			printf("%lld\n",query(1,1,n,l,r));
		}
		else
		{
			in(l),in(r),in(x);
			change(1,1,n,l,r,x);
		}
	}
}
```

---

## 作者：两年打铁 (赞：0)

题目中给定的数值都是小于1e6的，

那么我们就可以暴力把线段树上的每个点拆成二进制表达，也就是20位，线段树上的每个点的二进制表示这个区间这位二进制为1的数量。

建树就非常简单，考虑懒标记和查询还有修改。

我们知道异或是满足分配率的，即（x^y）^c=x^(y^c);

那么我们就可以用懒标记来维护异或值；

每次修改区间，我们再暴力拆开异或值，如果一位是1，那么这个区间的这个位上的1就等于$(r-l+1)-f[i][k]$;

懒标记就是直接异或上一层懒标记同时对这个区间进行修改就行了

查询的时候把下面的两个区间的1的数量相加就行。

最后得到答案的时候再把二进制转回来就行了。

复杂度$ O(20nlogn) $ ???
算了还是 $ O(能过)$


```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int L=1000000;
char ppp[L];
char *p1,*p2;
inline char gc()
{
    if(p1==p2)
    {
        p2=(p1=ppp)+fread(ppp,1,L,stdin);
    }
    return *p1++;
}
#define getchar gc
inline void read(int &x)
{
    x=0;
    char ch=getchar();
    int pd=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            pd=-pd;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    x*=pd;
    
}
inline void write(const int &x)
{
    int tmp=x;
    char ggg[10001];
    int s=0;
    if(tmp==0)
    {
        putchar('0');
        return ;
    }
    if(tmp<0)
    {
        putchar('-');
        tmp=-tmp;
    }
    while(tmp>0)
    {
        ggg[s++]=tmp%10+'0';
        tmp/=10;
    }
    while(s>0)
    {
        putchar(ggg[--s]);
    }
}

const int N=1e5+10;
int f[21][1000010],n,m,a[N];
int tag[1000010];

void build(int k,int l,int r)
{
    if(l==r)
    {
        int hh=a[l];
        for(register int i=0;i<=20;++i)
        {
            f[i][k]=hh&1;
            hh>>=1;
        }
        return;
    }
    int mid=(l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
    for(register int i=0;i<=20;++i)
    {
        f[i][k]=(f[i][k<<1]+f[i][k<<1|1]);
    }
}

void push_down(int k,int l,int r)
{
    tag[k<<1]^=tag[k];
    tag[k<<1|1]^=tag[k];
    int mid=(l+r)>>1;
    int hh=tag[k];
    for(register int i=0;i<=20;++i)
    {
        if((hh)&1)
        {
            f[i][k<<1]=(mid-l+1)-f[i][k<<1];
            f[i][k<<1|1]=(r-mid)-f[i][k<<1|1];
            
        }hh>>=1;
    }
    tag[k]=0;
}

void change (int k,int l,int r,int p,int q,int v)
{
    if(l>=p&&r<=q)
    {
        tag[k]^=v;
        int hh=v;
        for(register int i=0;i<=20;++i)
        {
            if(hh&1)
            {
                f[i][k]=(r-l+1)-f[i][k];
            }
			hh>>=1;
        }
        return ;
    }
    int mid=(l+r)>>1;
    push_down(k,l,r);
    if(p<=mid)
    {
        change(k<<1,l,mid,p,q,v);
    }
    if(q>mid)
    {
        change(k<<1|1,mid+1,r,p,q,v);
    }
    for(register int i=0;i<=20;++i)
    {
        f[i][k]=(f[i][k<<1]+f[i][k<<1|1]);
    }
    
}
struct dd
{
    int rs[21];
    void clear()
    {
        memset(rs,0,sizeof(rs));
    }
};
dd query(int k,int l,int r,int p,int q)
{
    if(l>=p&&r<=q)
    {
        dd ans;
        for(register int i=0;i<=20;++i)
        {
            ans.rs[i]=f[i][k];
        }
        return ans;
    }
    int mid=(l+r)>>1;
    dd ans;
    ans.clear();
    push_down(k,l,r);
    if(p<=mid)
    {
        dd now;
        now=query(k<<1,l,mid,p,q);
        for(register int i=0;i<=20;++i)
        {
            ans.rs[i]=now.rs[i];
        }
    }
    if(q>mid)
    {
        dd now;
        now=query(k<<1|1,mid+1,r,p,q);
        for(register int i=0;i<=20;++i)
        {
            ans.rs[i]+=now.rs[i];
        }
    }
    return ans;
}


signed main()
{
    read(n);
    for(register int i=1;i<=n;++i)
    {
        read(a[i]);
    }
    build(1,1,n);
    read(m);
    for(register int i=1;i<=m;++i)
    {
        int aa;
        read(aa);
        if(aa==1)
        {
            int ll,rr;
            read(ll);
            read(rr);
            dd ans=query(1,1,n,ll,rr);
            int last=0;
            for(register int i=0;i<=20;++i)
            {
                last+=(1<<i)*ans.rs[i];
            }
            write(last);
            puts("");
        }
        else 
        {
            int ll,rr,vv;
            read(ll);
            read(rr);
            read(vv);
            change(1,1,n,ll,rr,vv);
        }
    }
}
```


---

