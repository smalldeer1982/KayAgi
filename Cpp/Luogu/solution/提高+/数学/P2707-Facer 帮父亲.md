# Facer 帮父亲

## 题目背景

Facer 可是一个孝顺的孩纸呦


## 题目描述

Facer 的父亲是一名经理，现在总是垂头丧气的。

Facer 问父亲，怎么啦？父亲说，公司出了点问题啊。

公司管理着 $n$ 个风景点，每个风景点都有不少人来参观。

可是现在！人民投诉票价太高了，他不得不调整票价。

具体来说，第 $i$ 个景点如果票价是 $x$，来的人数就是 $\max( (a_i - b_i\times x),0 )$。

你需要分配每个景点的门票，使得所有景点的门票总价之和不超过 $k$，求最大的收益。


## 说明/提示

样例解释：

景点 $1$ 票价 $3$，景点 $2$ 票价 $1$。

景点 $1$ 人数：$50 - 3\times 2 = 44$，收益：$132$。

景点 $2$ 人数：$40 - 1\times 1 = 39$，收益：$39$。

总收益为 $171$。


- 对于 $10\%$ 的数据，$ 1 \le n \le 5 , 1 \le k \le 5$；
- 对于 $30\%$ 的数据，$ 1 \le n \le 100, 1 \le k \le 100$；
- 对于 $60\%$ 的数据，$ 1 \le n \le 2000, 1 \le k \le 2000$；
- 对于 $100\%$ 的数据，$ 1 \le n \le 100000, 1 \le k \le 100000,1 \le a_i , b_i \le 100000$。


鸣谢 zhouyonglong 提供解法。

## 样例 #1

### 输入

```
2 4
50 2
40 1```

### 输出

```
171```

# 题解

## 作者：Just_do_it (赞：13)

### 思路：

我们将收益表达出来是$v = ax - bx^2$
这是一个二次函数，在二次函数的对称轴之前函数单调递增但斜率不断变小，及$x$每增加$1$所增加的$v$会不断变小。因此我们将所有当前门票增加所增加的收益放进大根堆里，贪心每次加最大的那个，重新计算后加入堆。

## 当然没有函数基础的人可以这么想

当前收益$v_1 = x(a-bx) = ax - bx^2$

$x$增加1之后的收益$v_2 = (x+1)(a-b(x+1)) = (ax - bx^2) + a-b-2bx$

$x$增加$1$之后的收益增加值$\Delta v = v_2-v_1 = a-b-2bx $

我们发现$\Delta v$在$x$的增加后不断变小，可以贪心每次增加最大的收益增加值的$x$。

且$\Delta v$的改变量为

$(a-b-2bx)-(a-b-2b(x+1)) = 2b$

这个改变量与$x$没有关系，只用记$b$来更新增加的收益

## 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x){
	int f = 1;x = 0;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x*10+ch-'0';ch = getchar();}
	x *= f;
}

const int N = 100005;
int n,k;
ll ans;
struct node{
	int val,b;
	friend bool operator <(node a,node b){
		return a.val < b.val;
	}
}u;
priority_queue<node> Q;

int main(){
	read(n); read(k);
	for(int i = 1,a,b;i <= n;++i){
		read(a),read(b);
		if(a-b > 0) Q.push((node){a-b,b});
	}
	while((k--) && (!Q.empty())){
		u = Q.top(); Q.pop();
		ans += u.val; u.val -= 2*u.b;
		if(u.val <= 0) continue;
		Q.push(u);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：xhhhh36 (赞：6)

[传送门](https://www.luogu.com.cn/problem/P2707)

根据题意可以知道票价为 $x_i$ 的收益为 $a_i\times x_i-b_i\times x_i^2$，票价为 $x_i+1$ 的收益为 $a_i\times (x_i+1)-b_i\times (x_i+1)^2$。那么 $x_i$ 增加 $1$，收益就会增加 $v_i=a_i-b_i-2 b_i x_i$，最开始 $x_i$ 均为 $0$，那么 $v_i=a_i-b_i$。每次 $x_i$ 增加一时，$v_i'=a_i-b_i-2 b_i (x_i+1)=a_i-b_i-2 b_i x_i-2 b_i=v_i-2b_i$，也就是 $v_i$ 要减少 $2b_i$。那么我们可以考虑用一个大根堆来贪心的让 $v_i$ 最大的景点的票价加一，然后让答案加上 $v_i$，$v_i$ 减去 $2b_i$ 之后重新放入堆中，重复进行 $k$ 次增加操作。当 $v_i \le 0$ 时，让 $x_i$ 增加并不会让答案更优，因为题目只要求票价小于等于 $k$，所以此时可以不用继续操作。
# AC code

```cpp
#include <bits/stdc++.h>
#define int long long
#define pr pair<int,int>
#define f first
#define s second
using namespace std;
const int N=1e5+5;
int n,k,ans;
priority_queue<pr> q;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		int a,b;cin>>a>>b;q.push({a-b,b});
	}
	while (k--&&!q.empty()){
		pr t=q.top();q.pop();
		if (t.f<=0) break;
		ans+=t.f;t.f-=t.s*2;
		q.push(t);
	}cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Viva_Hurricane (赞：5)

今天突然想做堆的题，于是就翻到了二叉堆中的第一道蓝题.

进入正题：

设第i个景点的票价为pi,

由题意知，每个景点可得的收益为 ai\*pi-bi\*pi\*pi

是一个完美的关于pi二次函数.

则根据二次函数的性质，当pi=ai/(2\*bi)时，

该景点获得收益最大.

但是票价和却有一个上限k(当然票价和小于上限时直接输出就好),

所以只能将一部分的票价降低.

而对于第i个景区，降低1的票价，

收益将会降低 ai\*pi-bi\*pi\*pi-(ai\*(pi-1)-bi\*(pi-1)\*
(pi-1))，

即为ai+bi-2\*bi\*pi(其他大佬算过了)，记为vi.

所以为了获得最大收益，

应将vi排序(当然要用堆，不然会炸)，

每次将最小的vi所对应的pi减1，再计算vi，再排序.

当pi减小到0时，要将对应的景点移出堆，避免出现负票价.

直到总票价小于等于上限k时，输出答案.

大概思路就是这样，

~~目前最快，无O2~~代码如下:
```cpp
#include<cstdio>
using namespace std;
int n,m;
int a[100010],b[100010];
int p[100010],v[100010];//p记录票价，v记录减少票价时减少的收益.
int tot=0,num=0;//tot是总票价.
struct heap{//这是一个堆.
    int v,i;//i代表第i个景点.
};
heap h[100010];
int pre(int a,int b){//计算二次函数顶点.
    b*=2;
    int k=a/b;
    if(a-b*k>b*(k+1)-a)
        return k+1;
    return k;
}
int value(int k){
    return a[k]+b[k]-2*b[k]*p[k];
}
//一大坨手写堆的代码.
void swap(int a,int b){
    int change1=h[a].v;
    h[a].v=h[b].v; h[b].v=change1;
    int change2=h[a].i;
    h[a].i=h[b].i; h[b].i=change2;
}
void down(int k){
    int t=k;
    while(true){
        if((k<<1)<=num){
            if(h[k<<1].v<h[t].v)
                t=k<<1;
        }
        if((k<<1|1)<=num){
            if(h[k<<1|1].v<h[t].v)
                t=k<<1|1;
        }
        if(t!=k){
            swap(t,k);
            k=t;
        }
        else
            return ;
    }
}
void up(int k){
    while(k!=1){
        if(h[k].v<h[k>>1].v){
            swap(k,k>>1);
            k=k>>1;
        }
        else
            return ;
    }
}
void remove(){
    h[1].v=h[num].v;
    h[1].i=h[num].i;
    num--;
    down(1);
}
void print(){
    long long ans=0;
    for(int i=1;i<=n;i++)
        ans+=(long long)a[i]*p[i]-(long long)b[i]*(long long)p[i]*p[i];
    printf("%lld",ans);
}
int main(){
	freopen("666.in","r",stdin);
    freopen("666.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i],&b[i]);
        p[i]=pre(a[i],b[i]);
        tot+=p[i];
        v[i]=value(i);
    }
    if(tot<=m){
        print();
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(a[i]>b[i]&&p[i]>0){
            num++;
            h[num].v=v[i];
            h[num].i=i;
            up(num);
        }
    }
    while(tot>m){
        int i=h[1].i;
        tot--; p[i]--;
        if(p[i]==0){
            remove();//避免出现负票价.
            continue;
        }
        v[i]=value(i);
        h[1].v=v[i];
        down(1);
    }
    print();
    return 0;
}
```


---

## 作者：FiraCode (赞：3)

## 题解思路：

因为当钱数是 $x$ 时收益为 $\max\{a_i-b_ix, 0\} \times x$。

因为这个 $\max$ 不好化简，那么不妨设 $a_i - b_i \times x \ge 0$。

当第 $i$ 个票价为 $x$，则收益为：
$$(a_i-b_ix)x$$
$$=a_ix-b_ix^2$$

把第 $i$ 个的票价增加 $1$，就变成了：
$$(a_i-b_i(x+1))(x+1)$$
$$=a_i(x+1)-b_i(x+1)^2$$
$$=a_ix+a_i-b_ix^2-2b_ix-b_i$$

发现把第 $i$ 个票价增加 $1$，比原来多了 $a_i-2b_ix-b_i$。

那么就贪心的选多的最多的，即 $a_i-2b_ix-b_i$ 最大的。

扩展完之后再把扩展完的下一个增加的收益放到堆里即可。

## CODE:
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k;
int a[100010], b[100010], cnt[100010];
priority_queue<pair<ll, int>> q;
ll ans;//开long long！

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i], &b[i]);
	for (int i = 1; i <= n; ++i) {
		q.push({a[i] - 2 * b[i] - b[i]});//初始值
	}
	for (int i = 1; q.size() && i <= k; ++i) {
		auto t = q.front();
		q.pop();
		if (t.first < 0) break;
		ans += t.first;//加上这段增加的值
		cnt[t.second]++;//增加了一个
		q.push({a[i] - 2 * (cnt[t.second] + 1) * b[i] - b[i], t.second});//增加完之后放上
	}
	printf("%lld\n", ans);
	return 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ctj
}
```

---

## 作者：TheShuMo (赞：3)

## 题面简析

共有 $N$ 个景区，每个景区有一个对应的 $a_i,b_i$，设第 $i$ 个景区的票价为 $x_i$，那么来游玩这个景区的人数就是 $a_i - b_i \times x$，若小于零则代表没人来。规定所有景区的门票数总和都不能超过 $k$，求最大的总收益。

## 思路

注意到一个景区的门票总和就是 $a_ix-b_ix^2$，上过二次函数的读者就会知道，这是一个开口向下的二次函数。因此，当 $x$ 逐渐增大时，增加一张票所增加的收益就会不断减少。

考虑使用优先队列进行维护，每次从优先队列中拿出最大收益的一个景点加一张门票，然后把它下一次的收益放入优先队列中，不断如此操作 $k$ 次即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long

namespace IO {
    #define int long long 
    #define gh getchar
    inline int read(){char ch=gh();int x=0;bool t=0;while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();return t?-x:x;}
    inline char getc(){char ch=gh();while(ch<'a'||ch>'z') ch=gh();return ch;}
    inline void write(int x){if(x < 0){putchar('-');x = -x;}if(x > 9){write(x / 10);}putchar((x % 10 + '0'));}
}
using namespace IO;
using namespace std;
const int Maxn = 100010;
int a[Maxn], b[Maxn];
struct Node{
    int id, sy;
};
bool operator<(Node a,Node b){return a.sy<b.sy;}
priority_queue<Node> q;
signed main(){
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i] >> b[i];
        if(a[i]-b[i] > 0)q.push({i,a[i]-b[i]});
    }
    int ans = 0;
    for(int i = 1; i <= k and !q.empty(); i++){
        Node p = q.top();
        q.pop();
        ans += p.sy;
        if(p.sy-2*b[p.id] < 0)continue;
        q.push({p.id,p.sy-2*b[p.id]});
    }
    cout << ans;
}

```

---

## 作者：eastcloud (赞：2)

## P2707 Facer帮父亲 题解
### 题意简析

对于每个景点，票价为 $x$，人数为 $\max ( (a_i - b_i * x ) , 0 )$，安排每个景点的 $x$ 且总和不超过 $k$ ，使收益最大。

### 题目分析

题目的要求为安排 $x$ 使收益最大，换句话说，我们需要每次将一个景点的票价数增加，重复 $k$ 次（增加时不会更改收益的情况除外），使收益最大。

设 $a_i - b_i * x > 0$

当前收益 $v = a_ix - b_ix^2$

$x$ 加 $1$ 后收益 $ v_2 = a_ix + a_i - b_ix^2 - 2b_ix -b_i$

增加的价格为 $ v_2 - v = a_i - b_i - 2b_ix$

由此，我们得出了每次增加的值，因而可以想到一个贪心算法：
1. 开始时将 $x = 0$ 时所有景点下次增加的价格及对应的景点插入一个大根堆。

2. 每次取出堆顶，累加答案。

3. 将对应景点的 $x + 1$，将景点及增加的价格插入大根堆。

需要注意的是，如果堆顶的权值为0，那么我们可以直接退出循环，因为之后都不可能产生大于0的增加价格。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long//记得开long long
using namespace std;
struct Node{
	ll a,b;
}won[100100];
struct node{
	ll val,num,ti;
};
bool operator <(node a,node b){
	return a.val<b.val;
}
priority_queue<node> t;
int main(){
	ll n,k;
	cin>>n>>k;
	ll ans=0;
	for(ll i=1;i<=n;i++)cin>>won[i].a>>won[i].b;
	for(ll i=1;i<=n;i++)t.push((node){won[i].a-won[i].b-2*won[i].b*0,i,0});//x为0时下次增加的权值
	while(k){
		node tmp=t.top();
		ll i=tmp.num;
		if(tmp.val<=0) break;
		ans+=tmp.val;
		t.pop();
		t.push((node){won[i].a-won[i].b-2*won[i].b*(tmp.ti+1),i,tmp.ti+1});//将下次增加的答案加入堆中
		k--;
	}
	cout<<ans;
}
```


---

## 作者：Fan_Tuan (赞：2)

## 题意：
$n$ 个景点，每个景点来的人数与票价成函数关系，让你分配每个景点的票价，票价总和不超过 $k$，最大化收益。

## 思路：
贪心。
有每个景点人数 $sum = a_{i} - b_{i} \times x$ 可以推出每个景点的收益 $val = a_{i} \times x - b_{i} \times x^2$，我们贪心的分配每一元，将 $a_{i} \geq b_{i}$ 的景点放入大根堆中，不满足的显然不能分配。堆中每个景点维护当前能获得的最大收益，然后每次将分配一元后能获得最大收益的景点的票价加一，累加增加的收益，并且重新将这个景点放入堆中，直到各个景点的收益都为负数或 $k$ 元分配完。最后累加的收益总和即为最大收益。

## 代码：
```cpp
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#define int long long
using namespace std;

inline int read() {
	int f = 0, s = 0;
	char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void print (int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print (x / 10);
	putchar(x % 10 + '0');
}

int n, k, ans;

struct node {
	int a, b, x, lasum;
	bool operator < (const node &p) const {
		return a * (x + 1) - b * (x + 1) * (x + 1) - lasum < p.a * (p.x + 1) - p.b * (p.x + 1) * (p.x + 1) - p.lasum;
	}
};

priority_queue<node> q;

signed main() {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) {
		int a, b;
		a = read(), b = read();
		if (a >= b) q.push((node){a, b, 0, 0});
	}
	while(!q.empty() && k--) {
		node p = q.top();
		q.pop();
		int res = p.a * (p.x + 1) - p.b * (p.x + 1) * (p.x + 1) - p.lasum;
		if (res <= 0) break;
		ans += res;
		p.x++, p.lasum += res, q.push(p);
	}
	print(ans);
}
```

---

## 作者：HPXXZYY (赞：2)

$\color{blue}{\texttt{[Solution]}}$

对于第 $i$ 个景区而言，如果门票为 $p$ 时，收益为 $p \times (a_i - b_i \times p)=p \times a_i-p^2 \times b_i$（我们先假设这里的 $a_i-b_i \times p>0$，方便我们讨论）。

当 $p$ 增加 $1$ 时，收益会增加：

$$[(p+1) \times a_i - (p+1)^2\times b_i] -[p \times a_i-p^2 \times b_i]$$

经过计算可得上式的值为 $a_i - b_i - 2 \times p \times b_i$。

当门票的总和增加 $1$ 时，我们只能让一个景区的门票费用加 $1$，那么我们加谁呢？很简单，上面那个式子最大的景区。

如何维护这个最大，相信一定难不倒大家，是的，用个堆就可以了。

注意，如果所有景区收益增加量（就是上面那个式子）是负数（意味着再加门票要亏了）的时候，直接结束，因为题目要求是不超过即可。

当然 $a_i <b_i$ 的景区我们无需讨论，但是为了使代码简单一点，我的代码里没有特判，其实这样是对的。因为这些点的门票只要从 $0$ 增加到 $1$，就一定是亏了，我们会先考虑赚钱的。当考虑到它们的时候，就意味着算法的结束了。

应该要开 `long long` 哦。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=1e5+100;
struct node{
	int pri,a,b;
	inline long long F(){
		return 1ll*a-b-2ll*pri*b;
	}
	bool operator < (node c) const{
		long long FT=1ll*a-b-2ll*pri*b;
		register long long Fc=c.F();
		return FT<Fc;
	}
}t[N];int n,k;long long ans;
priority_queue<node> q;
int main(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		t[i].a=read();t[i].b=read();
		t[i].pri=0;q.push(t[i]);
	}
	for(int i=1;i<=k;i++){
		node u=q.top();q.pop();
		if (u.F()<0) break;
		ans+=u.F();//累加增量 
		u.pri++;q.push(u);
	}
	printf("%lld",ans);
	return 0;
}

read() 函数就是快读，我写得丑，大家就自己写吧。
```

---

## 作者：没见过AC (赞：1)

对于门票价格的分配，我们可以一元一元地分配，每次显然要分配到最优的景点。

考虑每个景点在当前收益下获得一元分配后收益的增加量。

若当前的收益为 $w_1=x \times ( a - b \times x ) $，则再获得一元分配后的收益 $w_2=(x+1)\times [a-b\times(x+1)]$，那么增加量 $d=w_2-w_1$，每次分配到 $d$ 最大的景点。

将景点放到堆里按 $d$ 排序，每次取出来处理完再放回去即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1000;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
inline ll read()
{
    char c=getchar();ll x=0,f=1;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
struct node{
	ll a,b,x,d,id;
}p[N];
struct cmp{
	inline bool operator()(node a,node b)
	{
		if(a.d<b.d) return 1;
		return 0;
	}
};
priority_queue<node,vector<node>,cmp> da;
ll m,n,k,ans=0;
int main()
{
    n=read();
    k=read();
    for(int i=1;i<=n;i++)
    {
    	p[i].a=read(); 
    	p[i].b=read();
		p[i].id=i;
		p[i].x=0;
		p[i].d=(p[i].x+1)*max((p[i].a-p[i].b*(p[i].x+1)),1ll*0)-p[i].x*max((p[i].a-p[i].b*p[i].x),1ll*0);
		da.push(p[i]);
	}
	for(int i=1;i<=k;i++)
	{
		node y;
		y=da.top();
		ll id=y.id;
		da.pop();
		p[y.id].x++;
		p[y.id].d=(p[id].x+1)*max((p[id].a-p[id].b*(p[id].x+1)),1ll*0)-p[id].x*max((p[id].a-p[id].b*p[id].x),1ll*0);
		da.push(p[id]);
	}
	for(int i=1;i<=n;i++)
	{
		ans+=p[i].x*max((p[i].a-p[i].b*p[i].x),1ll*0);
	}
	cout<<ans;
	return 0;
}


```

---

## 作者：EityDawn (赞：1)

# 思路
函数各位 OIer 应该都会吧？题目中给出的收益函数 $v$ 是一个关于 $x$ 的二次函数，具体形式为 $v=-b \times x^2+a \times x$，其中 $a$ 和 $b$ 为常数。

这个二次函数的图像是一个开口朝下的抛物线，其顶点坐标为 $(\frac{a}{2b},-\frac{\Delta}{4b})$，其中 $\Delta=a^2-4b\times v$ 表示函数的判别式。当 $b>0$ 时，函数的最大值为 $v=\frac{\Delta}{4b}$，此时 $x=\frac{a}{2b}$；当 $b<0$ 时，函数的最小值为 $v=\frac{\Delta}{4b}$，此时 $x=\frac{a}{2b}$。

考虑将 $x$ 加上一个 $1$，则对应的二次函数变为 $v=-b \times (x+1)^2+a \times (x+1)=-b \times x^2-(2b-a) \times x+(a-b)$。此时，函数的变化量为 $a-b-(2b-a) \times x$，即 $v$ 关于 $x$ 的一次函数。

因此，我们只需要遍历每个二次函数，计算其变化量，并将其存入优先队列中。每次从优先队列中取出变化量最大的函数进行选择，同时更新该函数的变化量，即将 $x$ 值加 $1$，重新计算变化量，再将更新后的节点重新入堆。直到选取了 $k$ 个函数或者堆顶元素的变化量小于等于0为止。最终，累加选择的函数的变化量，即为所求的最大收益。

 
## code
```cpp
#include<iostream>
#include<queue>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N],b[N];
int n,k;
struct node{
	int val,id,c;//依次存储变化量，编号，和 x 的值
	bool operator < (const node &a) const{return val<a.val;}
};
priority_queue<node>q;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		q.push({a[i]-b[i],i,0});//初始值
	}
	int ans=0;
	while(k--)
	{
		node u=q.top();q.pop();
		if(u.val<=0) break;//如果堆顶都小于零了，直接退出
		ans+=u.val;//累加变化量
		u.val=a[u.id]-b[u.id]-2*(++u.c)*b[u.id];
     	//更新一下，重新入堆
		q.push(u);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：紊莫 (赞：1)

做法是很简单的，每次用优先队列维护当前价格加一时 $\Delta M$ 最大的值。假设当前的价格为 $x$，这里的 $\Delta M$ 定义为 $cost(x+1)-cost(x)$，$cost$ 即为题意所示。

简单说一下这个贪心为什么是对的，首先观察到题中所给的关系是开口向下的二次函数，求导后可得斜率是一直在变小的，也就意味着，当前最大的 $\Delta M$ 就是永远最大的，之后的值一定不如它优，所以如此。  

[示例代码。](https://www.luogu.com.cn/paste/5pe8ybwt)

---

## 作者：Kwork (赞：1)

【都没人写题解，我来水一把】

首先想到全部枚举，但是过不了所有数据。看到标签是堆(也不知道洛谷的这一功能是否有害)，所以强行YY。

根据题意，i门票の收益=x\*(ai-bi\*x)=-bi\*x²+ai\*x. 在(0,(int)(ai/(2\*ai)+0.5)上是递增的。(记得最大值的自变量是对称轴的四舍五入，不然只有30分，记得开 long long(int64))。我们可以把门票收入若干份区间为1的收入，即票价为t的门票收入看成t份x区间为1的收入（区间【0，1】，【1，2】……）。二次函数的斜率是在不断降低的，所以同一门票对应的区间收入随着左右区间的增大而降低。所以我们将每一种门票的最大区间收入入堆，每次取出最大值，并将其对应的门票的第二大区间收入入堆……具体细节看代码。

[codec]





```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
const int maxn=100000+10;
typedef long long ll;
typedef pair<long long,int>P;
struct data{ll a;ll b;};
data tick[maxn];
ll tool[maxn],limit[maxn],last[maxn];
priority_queue<P>que;
int n,k;
int calc(int i){
    double a=(double) tick[i].b;
    double b=(double) tick[i].a;
    a=b/(2*a);
    return (ll)(a+0.5);
}
ll max(ll x,ll y){
    return x>y ? x:y;
}
void init(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>tick[i].a>>tick[i].b;
        limit[i]=calc(i);
        last[i]=max(tick[i].a-tick[i].b,0);
        tool[i]=0;
        if(tool[i]>=limit[i]) continue;
        tool[i]++;
        P p(last[i],i);
        que.push(p);
    }
    return;
}
void solve(){
    ll ans=0,cnt=0;
    while(!que.empty()){
        if(cnt>=k) break;
        P p=que.top(); que.pop();
        ans+=p.first; cnt++;
        int v=p.second;
        if(tool[v]>=limit[v]) continue;
        tool[v]++;
        ll temp=tool[v]*(tick[v].a-tick[v].b*tool[v]);
        P pp(temp-last[v],v);
        last[v]=temp;
        que.push(pp);
    }
    printf("%lld",ans);
    return;
}
int main(){
    freopen("1.txt","r",stdin);
    std::ios::sync_with_stdio(false);
    init();
    solve();
    return 0;
}
[/codec]
```

---

## 作者：fish_love_cat (赞：0)

一个很典的做法是对每个景点价格从零开始增加。

由于给出了柿子所以很容易计算增加产生的贡献，贪心取最大的做即可。

利用优先队列可以 $O(n\log n)$，那么做完了。

注意当最大贡献是负贡献时可以直接退出。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct fish{
    int a,b,x;
    int flc;
    bool operator<(const fish x)const{
		return flc<x.flc;
	}
};
int add(fish x){
    return (x.x+1)*max(0ll,x.a-x.b*(x.x+1))-(x.x)*max(0ll,x.a-x.b*(x.x));
}
priority_queue<fish>q;
int ans;
signed main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        fish x;
        cin>>x.a>>x.b;
        x.flc=add(x);
        if(x.flc>0)q.push(x);
    }
    while(k--&&!q.empty()){
        fish x=q.top();
        q.pop();
        ans+=x.flc;
        x.x++;
        x.flc=add(x);
        if(x.flc>0)q.push(x);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：PokerKing (赞：0)

## 分析：

首先我们分析一下，实际上给定的景点的 $a$ 和 $b$ 就是二次函数的两个参数，我们可以计算得到，一个景点的票价每增加 $1$ 获得的收益会变化的数值是：$a(x+1)-b(x+1)^2-(ax-bx^2)= a-b-2bx$。

那么就好办了，我们只需要求出 $x$ 为 $1$ 的情况，然后放入优先队列中维护，每次取出最大的统计答案，然后更新数值继续放入堆中维护，当然，每一次的增加值实际上只有 $a-b-2bx-(a-b-2b(x+1))=2b$，所以直接把取出值减去 $2b$ 就行了。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long ans;
struct Node {
	int b,v;
	bool operator < (const Node x) const {
		return v<x.v;
	}
};
priority_queue<Node> q;
inline int read() {
	char ch=getchar();
	int num=0;
	bool flag=false;
	while( ch<'0' || ch>'9' ) {
		if( ch=='-' ) flag=true;
		ch=getchar();
	}
	while( ch>='0' && ch<='9' ) {
		num=num*10+ch-'0';
		ch=getchar();
	}
	return flag ? -num : num;
}
int main() {
	n=read();
	m=read();
	Node now;
	int x,y;
	for(int i=1; i<=n; ++i) {
		x=read(), y=read();
		if( x-y>0 ) q.push((Node) {
			y,x-y
		});
	}
	while( (m--) && (!q.empty()) ) {
		now=q.top();
		q.pop();
		ans+=now.v;
		now.v-=(2*now.b);
		if( now.v<=0 ) continue;
		q.push(now);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

## 前言

好题。

## 思路分析

首先发现价值函数是一个二次函数：

$$f(x)=-b_ix^2+a_ix$$

考虑动态更新票价，也就是每次选择一个票价，使其增加 $1$。

根据初中知识，设 $g(x)=f(x+1)-f(x)$，那么 $g(x)$ 在定义域内单调递减。

也就是说，对于同一个函数 $f(x)$ 来说，选择它的收益单调递减。

所以可以做一个经典的堆贪心：每次选择收益最大的价值函数，然后更新它的收益。

注意 $f(x)$ 会和 $0$ 取 $\max$。

然后就做完了，总体复杂度 $O(k\log n)$。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a,b,ans;
struct node{
	int a,b,c,val;
	bool operator <(const node &a)const{
		return val<a.val;
	}
};
priority_queue<node> q;
int f(int a,int b,int x){
	return max(0ll,a*x-b*x*x);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		q.push({a,b,0,f(a,b,1)-f(a,b,0)});
	}
	while(k--){
		node t=q.top();
		q.pop();
		if(t.val<=0) break;
		ans+=t.val;
		q.push((node){t.a,t.b,t.c+1,f(t.a,t.b,t.c+2)-f(t.a,t.b,t.c+1)});
	}
	cout<<ans;
	return 0;
}

```

## 后记

bonus：当 $k\le 10^9$ 怎么做。

---

## 作者：lfxxx (赞：0)

不妨 $f_i(x) = x \times (a_i - b_i \times x)$。

导一下：$f_i(x)'=(a_i - b_i \times x) - b_i \times x = a_i - 2 \times b_i \times x$，这是一个导数单减的凸函数，由于门票价格可以小于 $k$，所以可以直接把函数导数减少的部分丢掉，那么函数与 $0$ 取 $\max$ 得到的原题意表示的函数就与我们现在分析的没有区别，然后就是堆模拟一下闵可夫斯基和即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
int a[maxn],b[maxn],c[maxn];
int val(int id,int x){
	return x*max(a[id]-b[id]*x,0*1ll);
}
priority_queue< pair<int,int> > q;
int n,k;
int sum;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		q.push(make_pair(val(i,1)-val(i,0),i));
	}
	for(int i=1;i<=k;i++){
		pair<int,int> tp=q.top();
		q.pop();
		if(tp.first<0) break;
		sum+=tp.first;
		c[tp.second]++;
		tp.first=val(tp.second,c[tp.second]+1)-val(tp.second,c[tp.second]);
		q.push(tp);
	}
	cout<<sum<<'\n';
	return 0;
}
```

---

