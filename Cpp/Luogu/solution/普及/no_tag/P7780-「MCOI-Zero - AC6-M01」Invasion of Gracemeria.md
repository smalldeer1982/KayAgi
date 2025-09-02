# 「MCOI-Zero / AC6-M01」Invasion of Gracemeria

## 题目背景

我们的首都 Gracemeria 正在遭受不明势力袭击！

空袭造成的破坏遍布全城。

全机，立刻紧急升空迎击！

---

「Garuda 1，你可以起飞了。」

……

「Garuda 1，升空。Cerberus 队，跑道已经清空，你们准备好了就起飞。」

「所有飞机升空后听从 AWACS 的命令。」

「这不是演习。重复一遍，这不是演习！」

……

「这里是 AWACS Ghost Eye。」

……

「Garuda 1，你没僚机。」

「让我看看……   
　Shamrock。」
 
「你也是单机一架，对吗？」

「很好。   
　从现在起你就是 Garuda 2 了。」
 
「你好，这里是 Garuda 2。」

「没时间自我介绍了，快。   
　Garuda 1，加速，我会跟上。」

「尽管给我命令就好。」

「Garuda 队，你们已经可以同 Gracemeria 上空的敌军交战。」

……

**「May the Golden King smiles on us！！」**

$$_{{\frac{\large\text{ACE COMBAT }\Large6}{\tiny{\text{F i r e s\quad O f\quad L i b e r a t i o n}}}}}\\ \text{Mission 01} \\\Large\text{Invasion Of Gracemeria}\\\tiny -\textit{ Through the Heart Of a Nation }-$$

![](https://cdn.luogu.com.cn/upload/image_hosting/nd20pe59.png)

## 题目描述

给定一个长度为 $n$ 的序列 $a$，初始都是 $0$，和一个正整数 $k$。

现有 $q$ 次操作，每次操作给定 $i,v$，表示给序列 $a$ 的后缀 $a_{[i,n]}$ 加上 $v$。

每次操作后，请你输出 **所有数在序列中出现次数的 $k$ 次方和** 对 $20051131$ 取模的结果。

$20051131$ 是质数。

## 说明/提示

第一次操作后，有 $5$ 个 $1$，答案为 $5^2=25$。

第二次操作后，有 $1$ 个 $1$ 和 $4$ 个 $2$，答案为 $1^2+4^2=17$。

类似的，答案分别为 $1^2+1^2+3^2=11,1^2+1^2+1^2+2^2=7,5\times 1^2=5$。

---

- Subtask 1（20 pts）：$n,q\leq 2\times 10^3$。
- Subtask 2（40 pts）：$n\leq 2\times 10^3$。
- Subtask 3（40 pts）：无特殊限制。

对 $100\%$ 的数据，保证 $1\leq n,v,k\leq 20051130$，$1\leq q\leq 5\times 10^5$，$1\leq i\leq n$。

idea：Sol1，solution：Sol1，code：Sol1，data：Sol1 & 斜揽残箫

## 样例 #1

### 输入

```
5 5 2
1 1
2 1
3 1
4 1
5 1```

### 输出

```
25
17
11
7
5```

# 题解

## 作者：Aw顿顿 (赞：2)

题意清晰，不重述。

前置知识：[暴力数据结构 ODT 珂朵莉树](https://www.luogu.com.cn/blog/LinearExpectation/ODT-Chtholly)。

-------

由于每一次修改都是对于某一个位置的后缀进行操作，不难发现这个序列会保持单调不降。那么修改会影响到的答案显然在它所属于的区间内。

这样的答案修改可以在 $\texttt{split}$ 操作中进行。实际上，当我们将一个区间分为两个不同的部分，相当于要删掉整个区间并重新加入两个单独区间。这样的思想可以同样应用在答案的维护上。

对于区间 $[l,r]$ 其长度为 $r-l+1$，因此对于答案 $s$，首先去掉 $(r-l+1)^k$。但是新加入的贡献则分两块计算，分别是：

- $(pos-l+1)^k$。
- $(r-pos)^k$。

而这个更新的初始值应该是多少呢？实际上应该是 $n^k$（一共 $n$ 个 $0$ 全部相等）。由于这一题的特殊性，一个正整数 $v$ 并不影响结果，是个冗余条件。同时 $\texttt{split}$ 不需要返回任何一个指针。

实现代码如下：

```cpp
#include<bits/stdc++.h>
#define it set<node>::iterator
#define mod 20051131
#define int long long
using namespace std;
int n,q,k,s;
int ksm(int b,int p){
	int ans=1;b%=mod;
	while(p){
		if(p&1)ans=ans*b%mod;
		b=b*b%mod;p>>=1;
	}return ans;
}struct node{
    int l,r;
    mutable int v;
    node(int l,int r,int v):l(l),r(r),v(v){}
    bool operator<(const node &x)const{
		if(l!=x.l)return l<x.l;
		return r<x.r;
	}
};set<node>tr;
void modify(int l,int r,int x){
	int t1=ksm(r-l+1,k);
	int t2=ksm(x-l+1,k);
	int t3=ksm(r-x,k);
	s=((s+mod-t1+t2)%mod+t3)%mod;
}void split(int pos){
    it x=tr.lower_bound(node(pos,pos,0));
    if(x!=tr.end()&&x->l==pos)return;
    --x;int l=x->l,r=x->r,v=x->v;
    tr.erase(x);modify(l,r,pos-1);
    tr.insert(node(l,pos-1,v));
    tr.insert(node(pos,r,v));
}signed main(){
	scanf("%lld%lld%lld",&n,&q,&k);
	tr.insert(node(1,n,0));s=ksm(n,k);
	for(int i=1;i<=q;i++){
		int x,v;scanf("%lld%lld",&x,&v);
		split(x);printf("%lld\n",s);
    }return 0;
}
```



---

## 作者：一只书虫仔 (赞：2)

#### Description

> 有一个长度为 $n$ 的序列，初始全部为 $0$，每次操作给定 $i,v$，使得 $a_{[i,n]}$ 都加上 $v$，每次操作后求所有数在序列中出现次数的 $k$ 次方和对 $20051131$ 取模的结果。

#### Solution

珂朵莉树入门题（不是（只是觉得思路很像罢了）~~所以是不是应该评蓝 ~ 紫啊~~

考虑到每次都是给后缀加上一个不为 $0$ 的数 $v$，因此序列一定是非下降的序列，每次更新后面的答案时不需要考虑前面的数。

于是我们可以考虑直接上 ODT，设 $i$ 所在的区间为 $[l,r]$，将其分裂为 $[l,i-1]$ 和 $[i,r]$，更新答案即可。

更新答案时，假设分裂成 $[l,x]$ 与 $[x+1,r]$，需要进行的答案更改即为（设原本答案为 $A$）：

- $A \leftarrow A-(r - l + 1)^k$
- $A \leftarrow A+(x - l + 1) ^k + (r - x)^k$

初始设 $A=n^k$ 即可。

#### Code

```cpp
#include <bits/stdc++.h>
#define Mod 20051131

using namespace std;

long long binpow (long long b, long long p, long long k) {
	b %= k;
	long long res = 1;
	while (p > 0) {
		if (p & 1)
			res = res * b % k;
		b = b * b % k;
		p >>= 1;
	}
	return res;
}

struct range {
	long long l;
	long long r;
	mutable long long v;
	bool operator < (const range& a) const {
		if (l != a.l) return l < a.l;
		else return r < a.r;
	}
};

set <range> s;
long long n, q, k;
long long ans = 0;

void change (long long l, long long x, long long r) {
	ans += Mod;
	ans -= binpow(r - l + 1, k, Mod);
	ans += binpow(x - l + 1, k, Mod);
	ans %= Mod;
	ans += binpow(r - x, k, Mod);
	ans %= Mod;
	return;
} // [l, r] -> [l, x], [x + 1, r]

set <range>::iterator split (long long p) {
	range tmp;
	tmp.l = p, tmp.r = p, tmp.v = 0;
	set <range>::iterator it = s.lower_bound(tmp);
	if (it != s.end() && (*it).l == p) return it;
	it--;
	long long l = (*it).l, r = (*it).r, v = (*it).v;
	s.erase(it);
	range L, R;
	L.l = l, L.r = p - 1, L.v = v;
	R.l = p, R.r = r, R.v = v;
	change(l, p - 1, r);
	s.insert(L);
	return s.insert(R).first;
}

int main () {
	scanf("%lld%lld%lld", &n, &q, &k);
	range qwq;
	qwq.l = 1, qwq.r = n, qwq.v = 0ll;
	s.insert(qwq);
	ans = binpow(n, k, Mod);
	while (q--) {
		long long i, v;
		scanf("%lld%lld", &i, &v);
		set <range>::iterator p = split(i);
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Epitome (赞：1)

## 题意

后缀加求全局数种类。

## 解法

>首先可以写出 $a_i = \sum\limits_{j = 1}^{j \leq q}
[q_j \leq i]$，然后容易发现重复的只会是相邻的？
好像是的！
然后每次操作如果这个位置之前操作过就答案不变，否则答案
会加上一个后面第一个操作过的位置减去当前位置的贡献，
然后这个东西是要动态维护的？
草了这不就是把数列翻转过来然后前缀最大值吗？
然后树状数组秒了？
不对感觉复杂了，我设那个减法为 $s$，然后贡献就是，
不对我取对总答案柿子做分析：每个段长度的 $k$ 次
方之和，新加一个段就是减去之后加两个段草这不是
`set` 模板题吗思考这么久我也是服了。

以上摘自总结，应该还是比较难看懂的，首先对于每一次加操作这个位置之前如果没有操作过是会把这一段相同的分成两段相同的，然后数据结构维护每一段段头的位置就可以动态计算了。

## 代码

口胡是容易的，请展示你的代码。

```cpp
// 39 X 03

#include <bits/stdc++.h>

using namespace std;

const int N = 3e7 + 5, Mod = 20051131; // 666 出这种空间

int n, q, k, ans;

set<int> s;

int add( int x, int y ) { return (x + y) % Mod; }

int sub( int x, int y ) { return (x - y + Mod) % Mod; }

int mul( int x, int y ) { return 1ll * x % Mod * (y % Mod) % Mod; }

int pw( int x, int y ) {
  int res = 1;
  for (; y; y >>= 1) {
    if (y & 1) {
      res = mul (res, x);
    }
    x = mul (x, x);
  }
  return res;
}

int main() {
  ios :: sync_with_stdio(0), cin.tie(0);
  cin >> n >> q >> k;
  ans = pw (n, k), s.insert (1), s.insert (n + 1);
  for (int i, v; q--; ) {
    cin >> i >> v; // 哈哈哈 v 没卵用给我笑到了
    if (*s.lower_bound (i) != i) {
      auto u = prev (s.lower_bound (i));
      auto v = next (u);
      ans = sub (ans, pw (*v - *u, k));
      ans = add (ans, pw (i - *u, k));
      ans = add (ans, pw (*v - i, k));
      s.insert (i);
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：QianRan_GG (赞：1)

前置知识：`set`，快速幂。

## 题目大意

给定 $n,q,k$ 和一个初始为 $0$ 的序列，有 $q$ 次操作，每次输入 $u,v$ 对序列从 $u$ 开始的后缀加上 $v$，每次操作后求序列中不同数的个数的 $k$ 次方的和。  
注意：开始时的 $0$ 也要算！~~吐槽一下牛马样例~~

## 解题思路

因为每次是对序列的后缀进行操作，所以整个序列一定是单调不降。  
且因为求不同数个数进行计算，所以与 $v$ 无关。  
而某次修改时之前修改比它小的区间都不用考虑，因为所有在它之前比它小的区间也都要加上 $v$，对答案统计不变。  
所以我们只要找到 $u$ 左边和右边的某次被修改的起始点，设为 $ul,ur$，对 $ul,ur$ 组成的区间进行计算。  
这相当于一个线段从中间截断，只要使 $ans$ 减去 $(ur - ul)^k$，加上 $(u - ul)^k$ 和 $(ur - u)^k$ 就行了。  
所以对于一个 $u$，我们要快速找到它左边和右边的值，使用 `set` 就好了，每次我们都把 $u$ 放进去，即能使用迭代器快速求出它左边和右边。  
对于 $a^k$，我们可以利用快速幂快速求出。  
这样我们就解决了这题，时间复杂度 $O(q \log q)$。

## 代码

```cpp
#include <set>
#include <iostream>

using namespace std;

const int mod = 20051131;

set <int> s;
int n, q, k;
long long ans;

inline long long fpow(long long a, long long k)
{
	long long ans = 1;
	while(k)
	{
		if(k & 1) ans = ans * a % mod;
		a = a * a % mod, k >>= 1;
	}
	return ans;
} // 利用快速幂快速求出 a ^ k

inline void ins(int u)
{
	if(s.find(u) != s.end()) return ;
	s.insert(u);
	set <int>::iterator t = s.find(u); // find() 返回的是迭代器
	set <int>::iterator t1 = t, t2 = t;
	t1 -- , t2 ++ ; // 减一是左边，加一是右边
	ans = (ans - fpow(*t2 - *t1, k) + mod) % mod;
	ans = (ans + fpow(u - *t1, k)) % mod;
	ans = (ans + fpow(*t2 - u, k)) % mod; // 计算答案
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> q >> k;
	s.insert(1);
	s.insert(n + 1); // 先放入左右边界，防止出界
	ans = fpow(n, k) % mod; // 记录 0 的答案
	for(int i = 1; i <= q; ++ i)
	{
		int u, v;
		cin >> u >> v; ins(u); // v 没有用，放入 u
		cout << ans << '\n';
	}
}
```

---

## 作者：Sol1 (赞：1)

~~idea 来自校内讨论奇怪问题~~

显然序列保持不降，所以搞一个 set 维护所有同色连续段，每一次分裂连续段的时候减去原长度的 $k$ 次方再加上两个新长度的 $k$ 次方之和就可以了。

复杂度 $O(q\log k)$。

---

## 作者：Testlya (赞：0)

要用 set 真的对像我这种不会 STL 的 C-- 选手很不好呢 QAQ。

## 分析

- 很容易观察发现，由于是不断对后缀进行加上正数的操作。最后这个数列一定会呈单调递增。

- 询问的是数列中每种数字数量的 $k$ 次方和，所以与加上的 $v$ 无关。

- 观察发现，每次操作后，相同的数字总是在数列中连续出现，不同数字之间的间隔是每次操作的起始点。

- **把连续的同种数字看做一条线段，答案相当于每条线段的 $k$ 次方和**。

- 所以每次操作相当于把操作的起始点 $x$ 所在的线段从 $x-1$ 和 $x$ 之间断开，只有这条线段对答案有影响。每次询问只要让上一次的答案**减去断开前线段的长度的 $k$ 次方**，再**加上断开后两段线段长度的 $k$ 次方**即可。

所以就剩下最后一个问题：如何在可接受的复杂度内查询 $x$ 点所在的线段。

各位大佬用的 set，但由于我是 C-- 选手，所以我用的平衡树。我太菜了，只会 treap。

每个节点代表一条线段，询问时找到 $x$ 所在线段，修改线段右端点 $r$ 为 $x-1$，再插入 $[x,r]$。复杂度 $O(Q\log Q)$，卡卡常还是轻松过的。

## 代码

```cpp
#include<bits/stdc++.h>
#define ri register int
#define mod 20051131
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;register char c=getchar();register bool f=false;
	while(!isdigit(c)&&c!='-')c=getchar();
	if(c=='-')f=true,c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+c-'0',c=getchar();
	x=f?-x:x;
}
int n,m,k,wa;
inline ll ksm(ll x)
{
	ll y=1;
	if(x<=1)return x;
	for(ri i=k;i;i>>=1)
	{
		if(i&1)y=y*x%mod;
		x=x*x%mod;
	}
	return y;
}
ll ans;
struct treap
{
	int son[2],l,r,dat;
}tr[500005];
int tot,rot;
inline int append(int l,int r)
{
	tr[++tot].l=l;
	tr[tot].r=r;
	tr[tot].dat=rand();
	return tot;
}
inline void rotate(int d,int &t)
{
	int temp=tr[t].son[d^1];
	tr[t].son[d^1]=tr[temp].son[d];
	tr[temp].son[d]=t;
	t=temp;
}
inline void insert(int l,int r,int &t)
{
	if(!t)
	{
		t=append(l,r);
		return;
	}
	else
	{
		int d=(l>tr[t].r);
		insert(l,r,tr[t].son[d]);
		if(tr[tr[t].son[d]].dat>tr[t].dat)rotate(d^1,t);
	}
}
inline void split(int x,int &t)//将所在线段分裂成两条的操作（修改一条插入一条）
{
	if(tr[t].l==x)return;
	if(tr[t].l>x)split(x,tr[t].son[0]);
	else if(tr[t].r<x)split(x,tr[t].son[1]);
	else
	{
		ans=((ans-ksm(tr[t].r-tr[t].l+1)+ksm(x-tr[t].l)+ksm(tr[t].r-x+1))%mod+mod)%mod;//修改答案，取模里做减法可能会出现负数，要%mod+mod)%mod
		int temp=tr[t].r;
		tr[t].r=x-1;
		insert(x,temp,rot);//要从rot开始插入不然不平衡
	}
}
int main()
{
	read(n);
	read(m);
	read(k);
	ans=ksm(n);
	insert(1,n,rot);
	for(ri i=1;i<=m;i++)
	{
		read(wa);
		split(wa,rot);
		read(wa);
		printf("%d\n",ans);
	}
	return 0;
}
```


---

