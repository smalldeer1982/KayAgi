# Full Binary Tree Queries

## 题目描述

You have a full binary tree having infinite levels.

Each node has an initial value. If a node has value $ x $ , then its left child has value $ 2·x $ and its right child has value $ 2·x+1 $ .

The value of the root is $ 1 $ .

You need to answer $ Q $ queries.

There are $ 3 $ types of queries:

1. Cyclically shift the values of all nodes on the same level as node with value $ X $ by $ K $ units. (The values/nodes of any other level are not affected).
2. Cyclically shift the nodes on the same level as node with value $ X $ by $ K $ units. (The subtrees of these nodes will move along with them).
3. Print the value of every node encountered on the simple path from the node with value $ X $ to the root.

Positive $ K $ implies right cyclic shift and negative $ K $ implies left cyclic shift.

It is guaranteed that atleast one type $ 3 $ query is present.

## 说明/提示

Following are the images of the first $ 4 $ levels of the tree in the first test case:

Original:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960D/3753965d34e08b83256fa92db7096f66de1db941.png) After query 1 2 1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960D/d6350f6795afab08bec95128db23af58d71e24a4.png) After query 2 4 -1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960D/1c7af7fd089110021fd920d50be3656fe800bbdb.png)

## 样例 #1

### 输入

```
5
3 12
1 2 1
3 12
2 4 -1
3 8
```

### 输出

```
12 6 3 1 
12 6 2 1 
8 4 2 1 
```

## 样例 #2

### 输入

```
5
3 14
1 5 -3
3 14
1 3 1
3 14
```

### 输出

```
14 7 3 1 
14 6 3 1 
14 6 2 1 
```

# 题解

## 作者：Karry5307 (赞：4)

### 题意

给定一棵无限层数的满二叉树，有 $n$ 次操作，每次操作形如以下三种：

- `1 x k`：将 $x$ 所在层的所有节点的往右循环移动 $k$ 单位。

- `2 x k`：将 $x$ 所在层的所有节点连带子树往右循环移动 $k$ 单位。

- `3 x`：求出 $x$ 到根路径上所有节点的编号。

不保证 $k$ 是正数。

$\texttt{Data Range:}1\leq n\leq 10^5$

### 题解

还行吧，就是细节有点多。

首先定义一个节点 $x$ 的顺位为：将这一层的所有节点依次拿出来，这个 $x$ 所在的位置减 $1$，比如题目中所给的这张图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960D/3753965d34e08b83256fa92db7096f66de1db941.png)

$12$ 的顺位为 $4$，因为将这一层的所有节点拿出来之后 $12$ 排第五个，减去 $1$ 即为 $4$。

很明显，在没有任何修改的时候 $x$ 的顺位为 $x-2^k$，其中 $2^k\leq x<2^{k+1}$，有了这个概念之后就很方便理解了。

对于 $1$ 操作而言，实际上是将这一层内所有节点的顺位增加 $k$。对于 $2$ 操作而言，是将这一层内所有节点顺位增加 $1$，下一层内所有节点顺位增加 $2$，以此类推。

于是可以维护一个东西表示这一层内每个点的实际顺位相较于没修改时候的顺位增加了多少，这样就可以方便的在顺位和实际的位置之间转换。

对于 $3$ 操作来说，顺位有一个很好的性质：$x$ 的父亲的顺位为 $x$ 的顺位除以 $2$ 下取整。于是，对于所需要询问的节点 $x$ 来说，求出它的顺位，然后每一次再用顺位还原会真正的节点就好了。

用位运算的时候有一个注意的地方就是**一定是 `1ll<<d` 而不是 `1<<d`！**

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=2e5+51;
ll n,op,x,kk,d;
ll rot[64];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void rotate(ll d,ll kk)
{
	while(d!=63)
	{
		rot[d]=(rot[d]+kk)&((1ll<<d)-1),d++,kk<<=1;
	}
}
inline void query(ll d,ll x)
{
	x=((x+rot[d])&((1ll<<d)-1))+(1ll<<d);
	while(d)
	{
		printf("%lld ",((x-rot[d])&((1ll<<d)-1))+(1ll<<d)),x>>=1,d--;
	}
	puts("1");
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		op=read(),x=read(),d=63-__builtin_clzll(x);
		if(op==1)
		{
			kk=(read()&((1ll<<d)-1)+(1ll<<d))&((1ll<<d)-1);
			rot[d]=(rot[d]+kk)&((1ll<<d)-1);
		}
		if(op==2)
		{
			kk=(read()&((1ll<<d)-1)+(1ll<<d))&((1ll<<d)-1),rotate(d,kk);
		}
		if(op==3)
		{
			query(d,x);
		}
	}
}
```

---

## 作者：hfctf0210 (赞：2)

这题是一年前的一场div 1+2，当时思维能力比较差想错了还不知道，最后果然翻车了。

现在看看就是一道不太难的题，因为所有操作都是对整个一层进行的，所以不难发现其实只需记录一个数组d[i]表示第i层整体右移了d[i]位。其中d[i]要对2^(i-1)，即第i层的节点数取模。

对于操作1，直接修改d[i]；对于操作2，旋转子树等于把下一层旋转2k个位置，直接向下递归，一共只有63层，所以不会超时。对于操作3，需要记录一个函数pos，计算当前节点在此行从左向右第几个位置，这个根据d[i]也不难计算。走的时候注意按照d[i]偏移即可，具体细节见code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll c[80],d[80];
ll getdep(ll x)
{
	ll tmp=1,cnt=0;
	while(tmp<=x)tmp*=2,cnt++;
	return cnt;
}
ll getpos(ll x)
{
	ll tmp=1,cnt=0;
	while(tmp<=x)tmp*=2,cnt++;
	ll pos=x-tmp/2;
	return (pos+d[cnt])%c[cnt];
}
int main()
{
	c[1]=1;for(int i=2;i<=63;i++)c[i]=2*c[i-1];
	int T;scanf("%d",&T);
	while(T--)
	{
		int op;ll x,k,dep,pos;
		scanf("%d%lld",&op,&x);
		if(op==1)
		{
			scanf("%lld",&k);
			dep=getdep(x),k%=c[dep];
			d[dep]=(d[dep]+k+c[dep])%c[dep];
		}
		else if(op==2)
		{
			scanf("%lld",&k);
			dep=getdep(x),k%=c[dep];
			while(dep<=62)d[dep]=(d[dep]+k+c[dep])%c[dep],k=k*2%c[++dep];
		}
		else{
			dep=getdep(x),pos=getpos(x);
			while(dep>=1)
			{
				ll tmp=(pos-d[dep]+c[dep])%c[dep];
				printf("%lld ",c[dep]+tmp);
				dep--,pos=pos/2;
			}
			puts("");
		}
	}
}
```


---

## 作者：皎月半洒花 (赞：2)

以下做法渐进复杂度最低，为 `log_2` 外线性。是迄今为止全站最快的做法。

正文：

比较麻烦的找性质+模拟题，但还是秒了。~~但是由于各种细节实现上花了好久~~

一开始的想法就是，对操作 $(1)$ 的每一层打反向的标记，然后向上跳的时候遇到这一层反向跳一下，第二个操作打另一种正向的标记就好了。写了半天才写出来，这里说几个小细节：

1、两个操作的标记都打在当前层而不是上一层。但是两个标记释放的时刻不同。第二个标记每次要在跳之前下传当前层的，而第一个标记要在跳之后下传下一层的。原因是第一个标记是整体有效的，第二个标记是暂时有效的。

2、第一个标记在输出之后要清除。

3、注意到操作 $(1)$ 标记反向是因为跳的时候要走相对位移。但是如果一开始起点时存在标记，这个标记的作用应该是正向的。判一下即可。

4、`<cmath> log2()` 贼慢，甚至比手写的还要慢…


```cpp
int T ;
ll buc1[70] ;
ll buc2[70] ;

il int i_lg2(ll n){
    int m = 0 ;
    if (n >> 32) m |= 32, n >>= 32 ;
    if (n >> 16) m |= 16, n >>= 16 ;
    if (n >> 8) m |= 8, n >>= 8 ;
    if (n >> 4) m |= 4, n >>= 4 ;
    if (n >> 2) m |= 2, n >>= 2 ;
    if (n >> 1) m |= 1, n >>= 1 ;
    return m ;
}

int main(){
    qr(T) ; int p ;
    ll x, y, z, s, t, yf ;
    while (T --){
        qr(x), qr(y) ;
        if (x == 1)
            y = i_lg2(y), qr(z), buc1[y] -= z ;
        else if (x == 2)
            y = i_lg2(y), qr(z), buc2[y] += z ;
        else {
            qw(y, ' ') ;
            p = i_lg2(y) ;
            z = 1ll << p ;
            s = (z << 1) - 1 ;
            t = - buc1[p] & (z - 1) ;
            if (t < 0)
                t = (t + z) & (z - 1) ;
            x = y + t ;
            if (x > s)
                x = (x & s) + z ;
            y = x ;
            while (p > 0){
                s = (z << 1) - 1 ;
				t = buc2[p] & (z - 1) ;
                if (t < 0)
                    t = (t + z) & (z - 1) ;
                x = y + t ;
                if (x > s)
                    x = (x & s) + z ;
                y = x ;
                
                -- p ;
                s = z - 1 ;
                z = z >> 1 ;
                y = y >> 1 ;
                t = buc1[p] & (z - 1) ;
                if (t < 0)
                    t = (t + z) & (z - 1) ;
                x = y + t ;
                if (x > s)
                    x = (x & s) + z ;
                yf = y ; y = x ;
                qw(y, ' '), y = yf ;
            }
            putchar('\n') ;
        }
    }
}
```

# 

---

## 作者：SFlyer (赞：0)

模拟也太难了。

首先定义“原来的”为没有任何操作前的二叉树，“现在的”是目前操作后的二叉树。

首先发现因为 $x\le 10^{18}$，记录 $60$ 层就够了。每一次旋转 $2$ 操作可以看成是给当前层次及其以下的做旋转 $1$。

重要的是输出路径。假设我们现在在 $x$，递归进行：

- 输出 $x$。
- 算出 $x$ 在“现在的”对应到“原来的”是什么节点。
- 往上爬一层，$x\gets x/2$。
- 算出 $x$ 在“原来的”对应到“现在的”是什么节点。

第二次对应关系其实就是反着旋转。然后就做完了。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5+5;

ll tr[62],pw[62];

ll lvl(ll x){
	int cnt=1;
	while (x>=2) cnt++,x/=2;
	return cnt;
}

ll rel(ll x,ll lv){
	tr[lv]=(tr[lv]+pw[lv])%pw[lv];
	x+=tr[lv];
	if (x>=pw[lv]*2ll) x-=pw[lv];
	return x;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int q;
	cin>>q;
	pw[1]=1;
	for (int i=2; i<61; i++){
		pw[i]=pw[i-1]*2ll;
	}
	while (q--){
		ll op,x,k;
		cin>>op>>x;
		if (op==1){
			cin>>k;
			ll lv=lvl(x);
			k%=pw[lv];
			(tr[lv]+=k)%=pw[lv];
		}
		else if (op==2){
			cin>>k;
			ll lv=lvl(x);
			for (int i=lv; i<61; i++){
				k%=pw[i];
				(tr[i]+=k)%=pw[i];
				k*=2;
			}
		}
		else{
			ll lv=lvl(x);
			while (x){
				cout<<x<<" ";
				if (x==1) break;
				x=rel(x,lv);
				x/=2;
				tr[lv-1]*=-1;
				x=rel(x,lv-1);
				tr[lv-1]*=-1;
				lv--;
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：0)

> 有一棵无限深的二叉树，设父节点编号为 $x$，则初始状态下儿子结点编号为 $2x,2x+1$。
>
> 支持将一层的结点向右循环 $k$ 次，或将一层的结点连带子树向右循环 $k$ 次。每次询问一个点到根的路径，询问结点编号不超过 $10^{18}$。

注意到实际有用的层数不超过 $\log_2 10^{18}$，考虑暴力修改。

记 $f_i$ 为第 $i$ 层的结点向右循环了多少次。对于操作一，只需更改此层的信息；操作二相似，只不过下一层的循环次数是上一层的两倍。

询问的 $x$ 需要先逆向循环求出这个位置的原始编号。每次将原始编号除 $2$，加上 $f_i$ 并处理取模后输出。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=70;
int q,d[N],l[N],r[N],len[N];
int get(int x,int k){
	int dep=(int)log2(x)+1;
	k%=len[dep];
	x-=l[dep]-1;x+=k;
	while(x>len[dep]) x-=len[dep];
	while(x<=0) x+=len[dep];
	return l[dep]+x-1;
}
signed main(){
	int res=1;
	rep(i,1,63) l[i]=res,res*=2,r[i]=res-1,len[i]=r[i]-l[i]+1;
	read(q);
	while(q--){
		int op;read(op);
		if(op==1){
			int x,k;read(x);read(k);
			int dep=(int)log2(x)+1;k%=len[dep];
			d[dep]=(d[dep]+k)%len[dep];
		}
		if(op==2){
			int x,k;read(x);read(k);
			int _d=1,dep=(int)log2(x)+1;k%=len[dep];
			rep(i,dep,63){
				d[i]=(d[i]+_d*k)%len[i];
				_d*=2;
			}
		}
		if(op==3){
			int x;read(x);
			int dep=(int)log2(x)+1;
			x=get(x,d[dep]);
			printf("%lld ",get(x,-d[dep]));x/=2;
			per(i,dep-1,1){
				printf("%lld ",get(x,-d[i]));
				x/=2;
			}puts("");
		}
	}
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：0)

先构造出来一个层次数量为 $60$ 的一个虚满二叉树。观察到如果对每一个层维护”旋转度数“，所有修改操作仅仅会修改这些旋转次数。

然后就直接是大细节模拟了：

 - 输入需要把（旋转过的值）转换成（真实位置）。
 - 输出需要把（真实位置）转换成（旋转过的置）。
 - 输入旋转度需要对当前层大小取模，并且转换成正数。
 - 用 `63-__builtin_clzll(x)` 找到 `x` 所在的层。

赛时代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
 
#define ll long long
#define pii pair<int, int>
//#define int ll
const int MOD = 1000000007;

ll b[62];
ll sh[62];

void pr(ll node) {
    int d = 63 - __builtin_clzll(node);
    cout << (node - sh[d]) % b[d] + b[d] << ' ';
    if(d) pr(node/2);
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    b[0] = 1;
    rep1(i, 61) b[i] = 1ll<<i;
    int q; cin >> q;
    while(q--) {
        int t; ll x; cin >> t >> x;
        int d = 63 - __builtin_clzll(x);
        x = b[d] + (x + sh[d]) % b[d];
        if(t == 1) { 
            ll k;
            cin >> k; 
            k = ((k % b[d]) + b[d]) % b[d]; 
            sh[d] = (sh[d] + k) % b[d];
        }
        if(t == 2) {
            ll k;
            cin >> k; 
            k = ((k % b[d]) + b[d]) % b[d]; 
            iter(dd, d, 62) {
                sh[dd] = (sh[dd] + k) % b[dd];
                k *= 2;
            }
        }
        if(t == 3) {
            //cout << x << endl;
            pr(x);
            cout << endl;
        }
    }
}

```

---

