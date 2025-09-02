# 「RdOI R1」变换(turn)

## 题目描述

有 $n$ 个变换，其中第 $i$ 个有两个属性值 $p_i$ 和 $q_i$，当这个变换作用到 $x$ 时，$x$ 将会变成 $f_i(x),f_i(x)$ 的定义为：

$$f_i(x)=\left\lfloor\dfrac{x}{p_i}\right\rfloor+q_i$$

给定 $m$ 条操作，操作分两种：

**修改**操作可以修改某个变换的属性值；

**查询**操作将会给定 $x$ 以及两个序号 $s$ 和 $t$，你需要计算并输出：

$$f_{t}(f_{t-1}(\cdots f_{s+1}(f_{s}(x))))$$

## 说明/提示

【数据范围】

- 对于 $20\%$ 的数据，$1 \le n \le 10^3,1 \le m \le 10^4$。
- 对于另外 $30\%$ 的数据，$1 \le n \le 10^4,1 \le m \le 10^5$。
- 对于 $100\%$ 的数据，$1 \le n \le 10^5,1 \le m \le 2 \times 10^5$。

---

【文件读入读出】**（模拟，提交代码时不需使用）**

- 文件名：`turn.cpp`
- 读入文件名：`turn.in`
- 读出文件名：`turn.out`

## 样例 #1

### 输入

```
3 3
2 1 2
1 1 1
q 100 1 3
m 2 2 0
q 100 1 3```

### 输出

```
27
13```

## 样例 #2

### 输入

```
见附件中的 turn-big-sample1.in```

### 输出

```
见附件中的 turn-big-sample1.out```

# 题解

## 作者：weilycoder (赞：2)

## 法 1

题目要求的实际上就是这样的函数的复合：

$$
\begin{aligned}
f(x)&=\left\lfloor\dfrac{x}{p}\right\rfloor+q \\
&=\left\lfloor\dfrac{x+pq}{p}\right\rfloor
\end{aligned}
$$

所以我们求一下 $f_2(f_1(x))$ 看看啥样：

$$
\begin{aligned}
f_2(f_1(x))&=\left\lfloor\dfrac{\left\lfloor\frac{x+p_1q_1}{p_1}\right\rfloor+p_2q_2}{p_2}\right\rfloor \\
&=\left\lfloor\dfrac{x+p_1q_1+p_1p_2q_2}{p_1p_2}\right\rfloor
\end{aligned}
$$

注意到函数始终是 $\left\lfloor\frac{x+C}{a}\right\rfloor$ 的形式，我们考虑线段树维护。

但是由于复合后的 $a$ 和 $C$ 要做乘法，数大的时候会炸掉，考虑用 `long double` 乱搞一下。

我们把函数写成 $f(x)=\left\lfloor\frac{x}{a}+b\right\rfloor$ 的形式，这里 $a,b$ 均为实数，复合的形式是

$$
f_2(f_1(x))=\left\lfloor\dfrac{\left\lfloor\frac{x}{a_1}+b_1\right\rfloor}{a_2}+b_2\right\rfloor=\left\lfloor\dfrac{x}{a_1a_2}+\left(\dfrac{b_1}{a_2}+b_2\right)\right\rfloor
$$

上线段树即可。

## 法 2

观察一下 $f(x)=\left\lfloor\frac{x+c}{a}\right\rfloor$，不妨改成 $f(x)=\left\lfloor\frac{x+c}{a}\right\rfloor+b$ 的形式，其中 $0\le c<a$。

由于 $0\le x\le 10^6$，我们讨论 $a$ 是否大于 $10^6$。

若 $a\le 10^6$，暴力维护。

若 $a\gt 10^6$，由于 $x\le 10^6$，原函数就是

$$
f(x)=\begin{cases}
b&,x>a-c \\
b+1&,\text{otherwise}
\end{cases}
$$

这个玩意不好和其他函数复合，不妨把它写成

$$
f(x)=\left\lfloor\dfrac{x+\max(10^6+1-(a-c),0)}{10^6+1}\right\rfloor+b
$$

容易证明在 $x\le 10^6$ 时两个函数是同一函数。

上线段树维护。

## Code

这是方法 1 的代码，被 Hack 了叫我一声，有 dalao 证明正确了也叫我一声。

```cpp
#include <cmath>
#include <iostream>
using namespace std;

const int N = 1e5 + 7;
int n, m, P[N], Q[N];
struct node_t {
  long double a, b;
  inline node_t operator*(const node_t &g) const {
    return {a * g.a, g.b / a + b};
  }
  inline int64_t operator()(int x) const { return floorl(x / a + b); }
} tree[N << 2];
#define lc (p << 1)
#define rc (p << 1 | 1)
void build(int p, int l, int r) {
  if (l == r) {
    tree[p] = {(long double)P[l], (long double)Q[l]};
    return;
  }
  int mid = ((r - l) >> 1) + l;
  build(lc, l, mid), build(rc, mid + 1, r);
  tree[p] = tree[rc] * tree[lc];
}
void update(int p, int l, int r, int x, int a, int b) {
  if (l == r) {
    tree[p] = {(long double)a, (long double)b};
    return;
  }
  int mid = ((r - l) >> 1) + l;
  if (x <= mid)
    update(lc, l, mid, x, a, b);
  else
    update(rc, mid + 1, r, x, a, b);
  tree[p] = tree[rc] * tree[lc];
}
node_t ask(int p, int l, int r, int s, int t) {
  if (s <= l && r <= t)
    return tree[p];
  int mid = ((r - l) >> 1) + l;
  node_t res{(long double)1, (long double)0};
  if (s <= mid)
    res = ask(lc, l, mid, s, t) * res;
  if (t > mid)
    res = ask(rc, mid + 1, r, s, t) * res;
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> P[i];
  for (int i = 1; i <= n; ++i)
    cin >> Q[i];
  build(1, 1, n);
  while (m--) {
    char op;
    cin >> op;
    switch (op) {
    case 'm': {
      int i, p, q;
      cin >> i >> p >> q;
      update(1, 1, n, i, p, q);
      break;
    }
    case 'q': {
      int x, s, t;
      cin >> x >> s >> t;
      cout << ask(1, 1, n, s, t)(x) << '\n';
    }
    }
  }
  return 0;
}
```

---

## 作者：a___ (赞：1)

首先，我们考虑连续几次变换后式子会变成什么。

$$f_1(x)=\lfloor\frac x{p_1}\rfloor+q_1=\lfloor\frac {x+p_1q_1}{p_1}\rfloor$$

$$f_2(f_1(x))=\lfloor\frac {\lfloor\frac {x+p_1q_1}{p_1}\rfloor+p_2q_2}{p_2}\rfloor=\lfloor\frac {x+p_1q_1+p_1p_2q_2}{p_1p_2}\rfloor$$

显然，连续任意次的变换都可以表示为 $\lfloor\frac{x+c}a\rfloor$ 的形式，所以我们只要快速维护 $a$ 和 $c$ 即可。  

但是，这里有一个问题，即这里的 $a$ 和 $c$ 可能达到 $1000^{100000}$，计算会彻底炸掉。

我们重新设若干次变换为 $\lfloor\frac{x+c}a\rfloor+b\ (c\lt a)$，易知 $b$ 一定在可运算范围内，数量级大约是 $10^3$。这样我们就只需要让 $a$ 和 $c$ 不要太大就好。 

1. $c\lt a\lt 10^6$  
	保持原样不管。
    
2. $a\gt 10^6$  
	由于 $x\lt 10^6\lt a$，所以只有两种情况，即当 $x\lt a-c$ 时，$\lfloor\frac{x+c}a\rfloor=0$；当 $x\ge a-c$ 时，$\lfloor\frac{x+c}a\rfloor=1$。  
    我们只要令 $a'=10^6+1,c'=\max(0,a'-(a-c))$ 就好。
    
总结一下，我们现在每次合并两种变换有两件事：  

1. $\lfloor\frac{\lfloor\frac{x+c_1}{a_1}\rfloor+b_1+c_2}{a_2}\rfloor+b_2=\lfloor\frac{x+c_1+a_1(b_1+c_2)}{a_1a_2}\rfloor+b_2$，所以令 $a=a_1a_2,b=b_2,c=c_1+a_1(b_1+c_2)$，然后调整使 $c<a$。

2. 若 $a\gt 10^6$，则令 $a'=10^6+1,c'=\max(0,a'-(a-c))$

线段树维护就好。

时间复杂度 $\mathbf O((n+m)\log n)$，不知道出题人为什么只开了 $10^5$。

代码   
```cpp
#include<cstdio>
const int N=1e5+10;
int n,p[N],q[N];
inline long long max(long long a,long long b){return a>b?a:b;}
struct node
{
	long long a,b,c;
	node(long long a=0,long long b=0,long long c=0):a(a),b(b),c(c){}
	inline node operator+ (const node &x) const
	{
		long long ra=a*x.a,rb=x.b,rc=c+a*(b+x.c);rb+=rc/ra;rc%=ra;
		if(ra>1e6)rc=max(0,(int)1e6+1-ra+rc),ra=1e6+1;
		return node(ra,rb,rc);
	}
	inline long long query(int x)
	{
		return (x+c)/a+b;
	}
}t[N<<2];
void build(int rt,int l,int r)
{
	if(l==r)return (void)(t[rt]=node(p[l],q[l],0));
	int m=(l+r)>>1;
	build(rt<<1,l,m);build(rt<<1|1,m+1,r);
	t[rt]=t[rt<<1]+t[rt<<1|1];
}
void update(int rt,int l,int r,int x)
{
	if(l==r)return (void)(t[rt]=node(p[l],q[l],0));
	int m=(l+r)>>1;
	x<=m?update(rt<<1,l,m,x):update(rt<<1|1,m+1,r,x);
	t[rt]=t[rt<<1]+t[rt<<1|1];
}
node query(int rt,int l,int r,int ql,int qr)
{
	if(ql==l&&r==qr)return t[rt];
	int m=(l+r)>>1;
	if(qr<=m)return query(rt<<1,l,m,ql,qr);
	else if(ql>m)return query(rt<<1|1,m+1,r,ql,qr);
	else return query(rt<<1,l,m,ql,m)+query(rt<<1|1,m+1,r,m+1,qr);
}
int main()
{
	int i,m,x,y;char op[5];
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&p[i]);
	for(i=1;i<=n;i++)scanf("%d",&q[i]);
	build(1,1,n);
	while(m--)
	{
		scanf("%s%d%d%d",op,&i,&x,&y);
		if(op[0]=='m')p[i]=x,q[i]=y,update(1,1,n,i);
		else printf("%lld\n",query(1,1,n,x,y).query(i));
	}
	return 0;
}
```

---

## 作者：_LiWenX_ (赞：0)

来个更暴力的分块做法。

首先我们去观察 $f_i(x)$ 的一些性质。

由于答案的上界是 $10^8$ 左右，所以函数 $f_i(x)$ 的最多会有 $10^8$ 种不同的输入，也就是定义域的大小。

接下来分类讨论，当 $p_i=1$ 时，其实就是对 $x$ 做了一次加法，直接特殊处理即可。

对于 $p_i>1$，也许 $x$ 的值会变大，但是值域只会有最多 $O(\dfrac{S_i}{p_i})$ 种可能，那么只要经过 $O(\log n)$ 次 $p_i>1$ 的操作后，答案就只有 $1$ 种可能了，也就是说输入的 $x$ 根本不重要，$x=1$ 和 $x=10^6$ 的答案是完全一致的。

于是我们考虑分块，对于一个块我们维护这些东西：

$flag_i$ 表示从块的左侧到右侧，依次执行所有操作，$x$ 不管是几，最后的结果是否一样，维护它就只用带入 $x=0$ 和 $x=10^8$ 看结果是否一致即可。

若 $flag_i=1$，则 $t_i$ 表示 $x=0$ 时，遍历完整个块后的答案。

于是在查询的时候，对于一个 $flag_i=1$ 的块，由于 $x$ 不重要，直接把答案赋值为 $t_i$，我们就可以 $O(1)$ 跳过它了。

对于 $flag_i=0$，由上面的分析可以知道这个块中只有小于 $O(\log n)$ 个操作的 $p_i>1$，而其它 $p_i=1$ 的是做加法，直接把它们合并成一个操作，那么整个块也只有 $O(\log n)$ 个不同的操作要处理，直接暴力去算就好了。

对于修改操作，直接暴力重构整个块就好了。

对于散块，直接暴力做操作，处理一个整块最劣势 $O(\log n)$ 的，那么理论上将块长设为 $\sqrt{n\log n}$ 时，复杂度达到最优，为 $O(q\sqrt{n\log n})$，事实上完全跑不满，块长随便调都可以过，而且不用任何卡常。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int p[100001],q[100001];
int le[100001],re[100001],in[100001],size;
bool flag[100001];int t[100001];
int f[100001],sum[100001];
void rebuild(int x,int op){
	flag[x]=0;
	int t1=0,t2=1.1e8;
	for(int i=le[x];i<=re[x];i++){
		t1=(t1/p[i])+q[i];
		t2=(t2/p[i])+q[i];
	}
	if(t1==t2){
		flag[x]=1;
		t[x]=t1;
	}
	for(int i=re[x];i>=le[x];i--){
		if(p[i]==1){
			if(i==re[i]) f[i]=i+1,sum[i]=q[i];
			else f[i]=f[i+1],sum[i]=sum[i+1]+q[i];
		}
		else{
			sum[i]=0,f[i]=i;
		}
	}
}
int ask(int x,int l,int r){
	if(in[l]+1==in[r]||in[l]==in[r]){
		for(int i=l;i<=r;i++){
			x=(x/p[i])+q[i];
		}
		return x;
	}
	for(int i=l;i<=re[in[l]];i++){
		x=(x/p[i])+q[i];
	}
	for(int i=in[l]+1;i<in[r];i++){
		if(flag[i]){
			x=t[i];
			continue;
		}
		for(int j=le[i];j<=re[i];){
			if(p[j]!=1){
				x=(x/p[j])+q[j];
				j++;
			}
			else{
				x+=sum[j];
				j=f[j];
			}
		}
	}
	for(int i=le[in[r]];i<=r;i++){
		x=(x/p[i])+q[i];
	}return x;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	size=200;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) cin>>q[i];
	for(int i=1;i<=n;i++){
		in[i]=((i-1)/size)+1;
		re[in[i]]=i;
		if(!le[in[i]]) le[in[i]]=i;
	}
	for(int i=1;i<=in[n];i++){
		rebuild(i,0);
	}
	while(m--){
		char op;int l,r,x,P,Q;
		cin>>op;
		if(op=='q'){
			cin>>x>>l>>r;
			cout<<ask(x,l,r)<<'\n';
		}
		else{
			cin>>x>>P>>Q;
			p[x]=P,q[x]=Q;
			rebuild(in[x],1);
		}
	}
}
```

---

