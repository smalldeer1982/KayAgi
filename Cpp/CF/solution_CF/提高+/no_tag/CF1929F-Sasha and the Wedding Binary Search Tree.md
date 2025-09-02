# Sasha and the Wedding Binary Search Tree

## 题目描述

Having overcome all the difficulties and hardships, Sasha finally decided to marry his girlfriend. To do this, he needs to give her an engagement ring. However, his girlfriend does not like such romantic gestures, but she does like binary search trees $ ^{\dagger} $ . So Sasha decided to give her such a tree.

After spending a lot of time on wedding websites for programmers, he found the perfect binary search tree with the root at vertex $ 1 $ . In this tree, the value at vertex $ v $ is equal to $ val_v $ .

But after some time, he forgot the values in some vertices. Trying to remember the found tree, Sasha wondered — how many binary search trees could he have found on the website, if it is known that the values in all vertices are integers in the segment $ [1, C] $ . Since this number can be very large, output it modulo $ 998\,244\,353 $ .

 $ ^{\dagger} $ A binary search tree is a rooted binary tree in which for any vertex $ x $ , the following property holds: the values of all vertices in the left subtree of vertex $ x $ (if it exists) are less than or equal to the value at vertex $ x $ , and the values of all vertices in the right subtree of vertex $ x $ (if it exists) are greater than or equal to the value at vertex $ x $ .

## 说明/提示

In the first test case, the binary search tree has the following form:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1929F/10be688b7b5fc578d734940b94aa6e533b605a1c.png)Then the possible values at the vertices are: $ [2, 2, 3, 2, 2] $ , $ [2, 2, 3, 2, 3] $ , $ [2, 2, 3, 3, 3] $ , and $ [3, 2, 3, 3, 3] $ .

In the second test case, the values at all vertices are known, so there is only one suitable binary search tree.

## 样例 #1

### 输入

```
3
5 5
2 3 -1
-1 -1 2
4 -1 3
-1 5 -1
-1 -1 -1
3 69
2 3 47
-1 -1 13
-1 -1 69
3 3
2 3 -1
-1 -1 -1
-1 -1 -1```

### 输出

```
4
1
10```

# 题解

## 作者：Diaоsi (赞：9)

[Sasha and the Wedding Binary Search Tree](https://www.luogu.com.cn/problem/CF1929F)

~~C 跟 F 真该换一换~~

首先根据 $\mathtt{BST}$ 的性质，通过中序遍历得到的权值序列一定是一个单调不降序列，记这个序列为 $h$。

由于有一些权值不确定，$h$ 中会出现若干个的 $-1$ 段。于是问题就变成了把每个 $-1$ 填上一些值，使得序列 $h$ 单调不降的填法的方案数。

把每个 $-1$ 段拿出来讨论，所有的 $-1$ 段都长这样：

$$h_i,\,-1,\,-1,\,\cdots,\,-1,\,h_j$$

这样问题就转化成了构造一个长度为 $j-i-1$ 单调不降序列，序列中元素的值域为 $[h_i,h_j]$，求构造的方案数。

先给出结论，答案为：

$$\color{blue}\binom{h_j-h_i+j-i-1}{j-i-1}$$

记 $l=j-i-1$，由于值域很大，预处理阶乘的办法无法使用。但是观察到 $\mathcal{O}\left(\sum l\right)=\mathcal{O}(n)$，所以直接暴力求组合数就行。


建完 $\mathtt{BST}$ 后只需要跑一遍中序遍历，时间复杂度为 $\mathcal{O}(n)$。[Code](https://codeforces.com/contest/1929/submission/247054516)

------------


接下来给出上面那个结论的求法：

记 $l=j-i-1,\,s=h_j-h_i+1$，不妨把值域平移一下，原问题等价于求一个长为 $l$ 值域为 $[1,s]$ 的不降序列的个数。

而上面这个问题又等价于求长为 $l$ 值域为 $[1,l+s-1]$ 的**严格递增**序列的个数。为什么呢，考虑如下变换：

对于上面的不降序列，将其第二项加 $1$，第三项加 $2$，以此类推，最后一项加 $l-1$。

由于原序列是不降的，执行完上述操作之后就会变成严格递增的序列，且值域为 $[1,l+s-1]$。同理，将上述操作逆过来作用于严格递增序列，也会得到一个值域为 $[1,s]$ 的不降序列。所以这两种序列的构造方案是**一一对应**的。


长为 $l$ 值域为 $[1,l+s-1]$ 的严格递增序列个数就是在 $l+s-1$ 个元素中选择 $l$ 个的方案数，故答案为：

$$\color{blue}\binom{l+s-1}{l}$$



------------


组合意义天地灭，代数推导保平安。

如果没有想到上面的这个做法怎么办，别急，我们还有更暴力的做法。

已经确定了元素值域的范围，最终求出的的不降序列中的元素的集合一定是值域的一个子集，且子集大小至多为 $l$，考虑枚举这个子集的大小并求出子集的选法。

显然，对于一个大小为 $t$ 的子集，它的选法有 $\dbinom{s}{t}$ 种，而根据隔板法可知，将这个子集扩展成长度为 $l$ 的序列总共能构成 $\dbinom{l-1}{t-1}$ 种序列。

于是答案就是：

$$\sum_{t=1}^{l}\dbinom{s}{t}\dbinom{l-1}{t-1}$$


不妨令 $t$ 从 $0$ 开始枚举，而不合法的组合数视为 $0$，再稍加变换，上面的式子变成：

$$\sum_{t=0}^{l}\dbinom{s}{t}\dbinom{l-1}{t-1}=\sum_{t=0}^{l}\dbinom{s}{t}\dbinom{l-1}{l-t}$$

于是我们惊喜地发现上面这个东西是个范德蒙德卷积，稍稍证明一下：

$$\begin{aligned}\sum_{t=0}^{l}\dbinom{s}{t}\dbinom{l-1}{l-t}&=\left[x^l\right]\left(1+x\right)^{s}\left(1+x\right)^{l-1}\\&=\left[x^l\right]\left(1+x\right)^{l+s-1}\\&=\color{blue}\binom{l+s-1}{l}\end{aligned}$$

殊途同归。

---

## 作者：Gold14526 (赞：5)

$\rm Problem:$[Sasha and the Wedding Binary Search Tree](https://www.luogu.com.cn/problem/CF1929F)

$\rm Difficulty:2300$

感觉难度远远不如 E 题。

### 题意

有一棵 $n(2\le n\le 5\times10^5)$ 个节点的二叉搜索树，每个节点的权值都在 $[1,C](1\le C\le10^9)$ 中，这棵树的一部分节点权值是未知的，求这棵树节点的权值有多少种可能性，对 $998244353$ 取模。

### 做法

为方便说明，这里举一个例子：

![fdavx](https://cdn.luogu.com.cn/upload/image_hosting/t76ipqkx.png)

将树拍成序列（求中序遍历历序）：

![tdyfguohip](https://cdn.luogu.com.cn/upload/image_hosting/uy6g6wr9.png)

由于二叉搜索树的性质，我们可以知道这是一个单调不减的序列。

于是，原题变为：

> 给出一个单调不减的序列，每个数都在 $[1,C]$ 内，其中有一些数未知，求该序列有多少种可能

假定 $C=6$。

对于刚才取出的序列：

```
-1 -1 2 -1 -1 4 -1 -1
```

开头两个数必须在 $[1,2]$ 中，中间两个在 $[2,4]$ 中，最后两个在 $[4,6]$ 中。

显然，求出这三个子串的可能再相乘即为答案。

考虑一个子串的怎么求。

假设一个子串长度为 $x$，每个数在 $[l,r]$ 中。

换个角度想，将 $x$ 个下标放入 $[l,r]$ 中。

设 $y=r-l+1$，即求将 $x$ 个相同物品放入 $y$ 个不同盒子的方案数（可以为空），插板法可得方案数为 $C_{x+y-1}^{y-1}$。

直接算会超时，因为 $y$ 是 $C$ 级别的，考虑 $C_n^m=C_n^{n-m}$，所以方案数为 $C_{x+y-1}^x$，$x$ 是 $n$ 级别的，复杂度正确。

时间复杂度 $O(n)$ 或 $O(n\log C)$，区别在于是否线性预处理逆元。

### 代码

```cpp
#include<bits/stdc++.h>
#define cint const int
#define iint inline int
#define ll long long
#define cll const long long
#define ill inline long long
using namespace std;
iint read()
{
	int num=0,zf=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')zf=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return num*zf;
}
cint mod=998244353;
int n,c,tot;
int l[500001],r[500001],v[500001],a[500001];
int inv[500001];
void init()
{
	inv[1]=1;
	for(int i=2;i<=5e5;++i)
	{
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	}
}
void dfs(cint x)
{
	if(x==-1)return;
	dfs(l[x]);
	a[++tot]=v[x];
	dfs(r[x]);
}
int C(cint x,cint y)
{
	if(x<y||y<0)return 0;
	if(y>x-y)return C(x,x-y);
	int t=1;
	for(int i=x-y+1;i<=x;++i)t=1ll*t*i%mod;
	for(int i=1;i<=y;++i)t=1ll*t*inv[i]%mod;
	return t;
}
int calc(cint x,cint y)
{
	return C(x+y-1,y-1);
}
int lst,d,ans;
void solve()
{
	n=read();
	c=read();
	for(int i=1;i<=n;++i)
	{
		l[i]=read();
		r[i]=read();
		v[i]=read();
	}
	tot=0;
	dfs(1);
	lst=d=ans=1;
	for(int i=1;i<=n;++i)
	{
		if(a[i]!=-1)
		{
			ans=1ll*ans*calc(i-lst,a[i]-d+1)%mod;
			d=a[i];
			lst=i+1;
		}
	}
	ans=1ll*ans*calc(n+1-lst,c-d+1)%mod;
	printf("%d\n",ans);
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	init();
	int T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：McIron233 (赞：5)

吐槽：为什么这场比赛的 F 会是这样一个典题。

题目给出的是一个二叉搜索树，它满足的性质题目已经给出，容易想到求它的中序遍历（左根右），我们就得到了一个单调不下降的序列。

考虑序列上两个已知元素，要求两个元素中间没有其他的已知元素，设这两个元素的值分别是 $x,y$，中间一共有 $k$ 个未知元素，那么问题就转化成了：一个长度为 $k$ 的空序列，往里面填位于 $[x,y]$ 的正整数，要求序列单调不下降，求方案数。这是一个经典排列组合问题，答案是 $\displaystyle \large \tbinom{k}{y-x+k}$。

对于开头的第一个已知元素 $x$，前面有 $k$ 个未知元素，那么问题可以理解为：一个长度为 $k$ 的空序列，往里面填位于 $[1,x]$ 的正整数，要求序列单调不下降，求方案数。结尾同理。

实现细节：

-   如果使用预处理的线性求乘法逆元来求组合数，会出现 $\texttt{Runtime Error}$ 的错误，这是因为 $1 \leq C \leq 10^9$；我们应该直接暴力求组合数，这是因为 $\sum k \leq n \leq 10^6$，不会出现 $\texttt{Time Limit Exceeded}$。
-   对于序列开头和结尾的已知元素，我们可以预先在序列开头和结尾先添加 $1$ 和 $C$，这样可以方便代码实现。
-   更多细节见[提交记录](https://codeforces.com/contest/1929/submission/246655299)。

---

## 作者：KingPowers (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1929F)

这个 F，就挺难绷的，更难绷的是我场上还真不会。

BST 有个广为人知的重要性质就是中序遍历单调不降，因此考虑先把原树中序遍历求出来，这样就相当于是在序列上填数使其单调不降。

考虑现在中序遍历中的一段连续的 $-1$，这段 $-1$ 左右的数均已知，也就限制了这些数的范围。那么现在每段 $-1$ 就对应了这么一个子问题：求长度为 $n$ 且值域在 $[l,r]$ 范围内的单调不降序列数。

这个子问题是比较经典的，答案为 $\binom{r-l+n}{n}$，这里做个简要说明：不降的限制是不好做的，考虑将序列中的第 $i$ 个数加上 $i$，那么原来的不降序列现在一定对应一个严格递增的序列，而递增序列的计数只需要在值域范围内选出来 $n$ 个不同的数即可，此时的值域为 $[l+1,r+n]$，故答案为 $\binom{r-l+n}{n}$。

直接将每段 $-1$ 的答案乘起来就是最终的答案了。

注意的一点是组合数的下标太大不能预处理，但是上标的总和不超过 $n$，因此算组合数直接暴力乘就行了。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e6 + 5;
template<int mod>
unsigned int down(unsigned int x) {return x >= mod ? x - mod : x;}
template<int mod>
struct ModInt{
	unsigned int x;
	ModInt() = default;
	ModInt(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, ModInt& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, ModInt a) {return out << a.x;}
	friend ModInt operator+(ModInt a, ModInt b) {return down<mod>(a.x + b.x);}
	friend ModInt operator-(ModInt a, ModInt b) {return down<mod>(a.x - b.x + mod);}
	friend ModInt operator*(ModInt a, ModInt b) {return 1ULL * a.x * b.x % mod;}
	friend ModInt operator/(ModInt a, ModInt b) {return a * ~b;}
	friend ModInt operator^(ModInt a, int b) {ModInt ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend ModInt operator~(ModInt a) {return a ^ (mod - 2);}
	friend ModInt operator-(ModInt a) {return down<mod>(mod - a.x);}
	friend ModInt& operator+=(ModInt& a, ModInt b) {return a = a + b;}
	friend ModInt& operator-=(ModInt& a, ModInt b) {return a = a - b;}
	friend ModInt& operator*=(ModInt& a, ModInt b) {return a = a * b;}
	friend ModInt& operator/=(ModInt& a, ModInt b) {return a = a / b;}
	friend ModInt& operator^=(ModInt& a, int b) {return a = a ^ b;}
	friend ModInt& operator++(ModInt& a) {return a += 1;}
	friend ModInt operator++(ModInt& a, int) {ModInt x = a; a += 1; return x;}
	friend ModInt& operator--(ModInt& a) {return a -= 1;}
	friend ModInt operator--(ModInt& a, int) {ModInt x = a; a -= 1; return x;}
	friend bool operator==(ModInt a, ModInt b) {return a.x == b.x;}
	friend bool operator!=(ModInt a, ModInt b) {return !(a == b);}
};
using mint = ModInt<998244353>;
int n, c, tot, val[N], w[N], ls[N], rs[N];
mint fac[N], ifac[N];
void init(int n){
	fac[0] = 1;
	For(i, 1, n) fac[i] = fac[i - 1] * i;
	ifac[n] = 1 / fac[n];
	Rof(i, n, 1) ifac[i - 1] = ifac[i] * i;
}
mint C(int n, int m){
	mint res = 1;
	For(i, n - m + 1, n) res *= i;
	res *= ifac[m];
	return res;
}
mint calc(int n, int l, int r){  //长度为 n，值域为 [l,r] 的不降序列
	return C(r - l + n, n);
}
void dfs(int now){
	if(ls[now] != -1) dfs(ls[now]);
	w[++tot] = val[now];
	if(rs[now] != -1) dfs(rs[now]);
}
void Solve(){
	cin >> n >> c;
	For(i, 1, n) cin >> ls[i] >> rs[i] >> val[i];
	w[tot = 1] = 1; dfs(1); w[++tot] = c;
	mint res = 1;
	For(i, 1, tot){
		if(w[i] != -1) continue;
		int j = i;
		while(j < tot && w[j + 1] == w[i]) j++;
		res *= calc(j - i + 1, w[i - 1], w[j + 1]);
		i = j;
	}
	cout << res << '\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	init(1919810);
	int T = 1; cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：hzxphy (赞：2)

## 题目大意
不多说，题面已经讲的很清楚了。
## 题目分析
我们可以发现题目给定的不是一个普通的二叉树，而是二叉搜索树。

考虑一个二叉搜索树的性质：

**attribute：二叉搜索树的中序遍历序列是一个从小到大的序列。**

同时 SGT 也是二叉搜索树的一种（二叉平衡树）。

所以我们考虑类似 SGT 的平衡操作，把~平衡树~中序遍历，我们会得到一个从小到大的序列。我们以已知值为临界，可以得到若干组区间。具体的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/99yzfe2o.png)

当然这里面是会有空的，而空的 $-1$ 会随机出现在各个地方。

因此我们认为如果把 $2$ 和 $3$ 替换为 $-1$，设 $C=21$，虽然 $2$ 和 $3$ 这一段与 $C$ 无关，我们可以发现这是一个固定的区间。

考虑推广方案，我们设这一段可填入值属于区间 $[l,r]$，显然化为插板法问题，最终可以通过大组合数计算法可得。

**因此我们总结：**
## 题目思路
### main 思路
1. 求逆元用于计算组合数。
2. 接下来输入，进行 DFS 得到中序序列。
3. 直接插板计算得到答案。
### 求组合数思路
**注：函数 $C^x_y$ 表示组合数。**

假设我们现在要求 $C^x_y$ 的值。
1. 若 $x>y-x$，又公式 $C^x_y=C^{y-x}_y$，可优化为 $C^{y-x}_y$。
2. 此时逆元派上用场，具体方式如下——
```
int ans=1;
for(int i=y-x+1;i<=y;i++)ans=1ll*ans*i%mod;
for(int i=1;i<=x;i++)ans=1ll*ans*inv[i]%mod;
```
至此我们就完成了全部过程。

完结撒花！

## 接下来是大家期待的 AC 代码
```cpp
#include<bits/stdc++.h>
#define NaOH(x,y) (C((x)+(y)-1,(y)-1)%mod)
using namespace std;
typedef long long ll;
const int MAXN=5e5,mod=998244353;
int n,CC;
int lson[MAXN+1],rson[MAXN+1],val[MAXN+1],inv[MAXN+1];
vector<int>order;
void init(void){
	inv[1]=1;
	for(int i=2;i<=MAXN;++i){
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	}
	return;
}
void DFS(int u){
	if(u==-1)return;
	DFS(lson[u]);
	order.push_back(val[u]);
	DFS(rson[u]);
	return;
}
int C(int x,int y){
	if(x<y||y<0)return 0;
	if(y>x-y)return C(x,x-y);
	int t=1;
	for(int i=x-y+1;i<=x;i++)t=1ll*t*i%mod;
	for(int i=1;i<=y;i++)t=1ll*t*inv[i]%mod;
	return t;
}
void solve(void){
	order.resize(1);
	scanf("%d%d",&n,&CC);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",lson+i,rson+i,val+i);
	}
	DFS(1);
	int lst,ans;
	lst=ans=1;
	int d=1;
	for(int i=1;i<=n;i++){
		if(order[i]!=-1){
			ans=1ll*ans*NaOH(i-lst,order[i]-d+1)%mod;
			d=order[i];lst=i+1;
		}
	}
	ans=1ll*ans*NaOH(n+1-lst,CC-d+1)%mod;
	printf("%d\n",ans);
	return;
}
int main(){
	init();
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

简单题。

二叉搜索树的限制不好处理，考虑求出中序遍历后，限制等价于其不减，对于一段极长的未填区域，可以通过插板求出填数方案，虽然组合数的上标非常大，但是下标的和是 $O(n)$ 的，于是暴力处理即可做到 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 5e5+114;
int L[maxn],R[maxn];
int a[maxn],b[maxn],tot;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int n,c;
void build(int cur){
    if(cur==-1) return ;
    build(L[cur]);
    b[++tot]=a[cur];
    build(R[cur]);
}
int C(int n,int m){
    int res=1;
    for(int i=n;i>=n-m+1;i--) res=res*i%mod;
    for(int i=1;i<=m;i++) res=res*qpow(i,mod-2)%mod;
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        tot=0;
        cin>>n>>c;
        for(int i=1;i<=n;i++) cin>>L[i]>>R[i]>>a[i];
        build(1);
        int lstp=0,lstv=1;
        int res=1;
        for(int i=1;i<=n;i++){
            if(b[i]!=-1){
                res=res*C(b[i]-lstv+i-lstp-1,i-lstp-1)%mod;
                lstp=i;
                lstv=b[i];
            }
        }
        res=res*C(c-lstv+n+1-lstp-1,n+1-lstp-1)%mod;
        cout<<res<<"\n";
    }
    return 0;
}
```

---

## 作者：arrow_king (赞：0)

给定一棵形态固定的二叉树，有些节点上有一个数字，求在所有数在 $[1,c]$ 内的情况下给没有数的节点填数使得这棵树是 BST 的方案数。$n\le5\times10^5$，$c\le10^9$。

# Sol

因为是二叉搜索树，所以我们拍扁这棵树，得到了一个中间挖空的单调序列，求序列方案数。合法序列和 BST 有双射关系。

我们令 $\{a_1,a_2,\dots,a_n\}$ 为拍扁后形成的序列，并拓展序列使得 $a_0=1,a_{n+1}=c$。考虑两个相邻的不为 $-1$ 的位置 $l,r$，那么本质上就是在中间选择 $m=a_r-a_l$ 个分界点。合法方案等价于方程组 $x_1+x_2+\dots+x_{r-l}=a_r-a_l$ 的非负整数解数，而这个值等于 $\dbinom{a_r-a_l+r-l-1}{r-l-1}$。

注意到值域很大，因此不能预处理，但是下标 $r-l-1$ 的总和不会超过 $n$，因此组合数直接暴力求答案即可。

```cpp
il ll C(ll n,ll m) {
	ll ans=1,fac=1,inv=1;
	n%=mod,m%=mod;
	for(ll i=0;i<m;i++) fac=fac*(n-i)%mod,inv=inv*(i+1)%mod;
	return fac*qpow(inv,mod-2)%mod;
}
il void dfs(int u) {
	if(ch[u][0]!=-1) dfs(ch[u][0]);
	plc++;val[plc]=a[u];
	if(ch[u][1]!=-1) dfs(ch[u][1]);
}
il void mian() {
	n=read(),c=read(),plc=0;
	for(int i=1;i<=n;i++) ch[i][0]=read(),ch[i][1]=read(),a[i]=read();
	dfs(1);
	ll lst=0,v=1,ans=1;
	val[0]=1,val[n+1]=c;
	for(int i=1;i<=n+1;i++) {
		if(val[i]==-1) continue;
		ans=ans*C(val[i]-v+i-lst-1,i-lst-1)%mod;
		lst=i,v=val[i];
	}
	printf("%lld\n",ans);
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

[更好的阅读体验](http://blog.cyx2009.top/archives/261/)

# 题目翻译

给定 $n$ 个点的 BST（二叉搜索树），目前点权为 $-1$ 的节点可以染色 $[1,C]$，问可能的 BST 个数。答案对 $998,244,353$ 取模。

多测，$1\leq t\leq 10^5,1\leq \sum n\leq 5\times 10^5,1\leq C\leq 10^9$。

# 题目思路

BST 的一个性质是中序遍历点权单调不降。

中序遍历的顺序之后，我们只需要对于相邻两对不为 $-1$ 的数（我们定为 $L$ 和 $R$）直接的 $-1$ 填充即可。填充只能填充 $[L,R]$ 的数。

那么这个问题转化为对于长度为 $k$ 的序列，求填充 $[L,R]$ 且单调不降的方案数。观察到我们只需要知道可以选的个数，不需要知道具体选什么，所以答案只与 $len=R-L+1$ 有关。也就是用 $len$ 个数填充长度为 $k$ 的序列且单调不降的方案数。

这是经典组合数题，答案是 $\binom{len+(k-1)}{k}$。我的考虑方式和别的题解不太一样，你考虑对于只能单调上升的答案是 $\binom{len}{k}$，那么你加入 $k-1$ 个决策，表示 $\forall i\in[2,k]$，第 $i$ 个位置和第 $i-1$ 个位置填一样颜色。

实现需要支持多次查询 $\binom{n}{i}$，但是 $\sum i\leq n$ 所以直接暴力做就行。

# 完整代码

modint 部分已经省略。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int p = 998244353;
using Z = mod_int<p>;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
typedef long long ll;
int n;
ll c;
struct node
{
    int l, r;
    ll val;
} a[500020];
vector<int> v;
void dfs(int u)
{
    if (~a[u].l)
        dfs(a[u].l);
    v.push_back(u);
    if (~a[u].r)
        dfs(a[u].r);
}
Z C(int n, int i) // n 选 i 方案数
{
    Z ret = 1;
    for (int j = 1; j <= i; j++)
        ret *= n - j + 1;
    for (int j = 1; j <= i; j++)
        ret /= j;
    return ret;
}
Z F(int n, int L, int R) // n 个数升序，且都在 [L,R] 的方案数
{
    int len = R - L + 1;
    // 等价于 C(n + len - 1 , n)
    return C(n + len - 1, n);
}
void solve()
{
    read(n, c);
    for (int i = 1; i <= n; i++)
        read(a[i].l, a[i].r, a[i].val);
    v.clear();
    dfs(1);
    int minus = 0, l = 1;
    Z ans = 1;
    for (int i : v)
    {
        if (~a[i].val)
        {
            ans *= F(minus, l, a[i].val);
            minus = 0;
            l = a[i].val;
        }
        else
            minus++;
    }
    ans *= F(minus, l, c);
    cout << ans << '\n';
}
int main()
{
    int t;
    read(t);
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：xDebM (赞：0)

让我们按照数值的顺序列出顶点的编号。设为 $v1, \ldots, vn$ 。那么它必须满足 $value{vi} \leq value{v{i + 1}}$。

那么在这个顺序中，我们有一些线段的值是未知的。对于每个线段，我们都知道这个线段中的值可以取的最大值和最小值，比方说 $L$ 和 $R$。然后，我们需要从区间 $(L, R)$ 中为该段中的每个数字选择一个值，以保持相对顺序。这是一个已知问题，有 $\binom{R - L + len}{len}$ 种可能的方法，其中 $len$ 是线段的长度。然后，我们需要将所有这些二项式系数相乘。

现在，请注意 $R - L + len$ 很大，因此计算时我们可以简单地使用公式 $\binom{n}{k} = \frac{n \cdot (n - 1) \cdot \ldots \cdot (n - k + 1)}{k!}$，因为总和 $len$ 不会超过 $n$。

---

## 作者：AllenAlien (赞：0)

# 题意简述

给定一棵 $n$ 节点的二叉搜索树，其中一些节点的权值未知，节点权值的范围在 $[1,C]$ 之间，求有多少种符合条件的二叉树，结果对 $998244353$ 取模。

# 思路分析

首先我们需要将所有节点排序。根据二叉搜索树的性质，只要跑一遍中序遍历就可以啦。

```c++
        int cur = 1;
        int tot = 0;
        stack<int> s;
        while (!s.empty() || cur) { // 求中序遍历
            while (cur) {
                s.push(cur);
                cur = chd[cur][0];
            }
            cur = s.top();
            s.pop();
            pos[++tot] = val[cur];
            cur = chd[cur][1];
        }
```

这里的 $pos$ 数组就是所有节点排序之后的数组，若 $pos[i]>0$ 则表示该节点权值已知，若 $pos[i]=-1$ 则表示该节点权值未知。为了方便接下来的计算，令 $pos[0]=1$，$pos[n+1]=C$。这样一来，我们发现，所有连续的未知节点两端一定存在已知节点。于是，整个 $pos$ 数组就可以被分割成若干个仅由连续未知数及两个已知端点所组成的区间。下文称这样的区间为未知区间。根据乘法原理，只需要将所有未知区间合法情况的种数计算出来，然后将所有结果相乘，就是这道题的答案啦。

令每个未知区间两端的已知数差值为 $s$，且该未知区间的长度为 $t$。接下来，问题就转化为：如何计算长度为 $t$，范围为 $[0,s]$ 的所有单调不减序列的总个数 $ans_{t,s}$。

首先给出结论：答案就是
$$
ans_{t,s}=C_{t+s}^{t}
$$
至于结论的证明，不感兴趣的小伙伴可以直接跳过。

__（证明部分开始）__

---

我们可以用~~数学dp~~数学归纳法。

①当 $t=1$ 时，对于任意的 $s$，答案显然是 $s+1$。于是，有
$$
C_{t+s}^t=C_{1+s}^1=s+1=ans_{1,s}
$$
结论成立。

②对于 $\forall t\in Z^+$，假设 $t=t_0$ 时结论成立，即
$$
ans_{t_0,s_0}=C_{t_0+s_0}^{t_0}
$$
那么，我们就需要证明
$$
ans_{t_0+1,s_0}=C_{t_0+1+s_0}^{t_0+1}
$$
也就是怎么通过 $t=t_0$ 时的结果推出 $t=t_0+1$ 时的结果。

对于长度为 $t_0+1$，范围为 $[0,s_0]$ 的未知区间，我们假设最后一项（第 $t_0+1$ 项）已经确定为 $s_1\in[0,s_0]$，该数列的前 $t_0$ 项的取值就是
$$
ans_{t_0,s_1}=C_{t_0+s_1}^{t_0}
$$
于是，有
$$
ans_{t_0+1,s_0}=ans_{t_0,s_0}+ans_{t_0,s_0-1}+\dots+ans_{t_0,1}+ans_{t_0,0}=C_{t_0+s_0}^{t_0}+C_{t_0+s_0-1}^{t_0}+\dots+C_{t_0+1}^{t_0}+C_{t_0}^{t_0}
$$
记该等式为①式。

而对于组合数 $C_m^n$，有一个很常用的结论：
$$
C_m^n=C_{m-1}^{n-1}+C_{m-1}^n
$$
将这个结论应用到 $C_{t_0+1+s_0}^{t_0+1}$ 上，有
$$
C_{t_0+1+s_0}^{t_0+1}=C_{t_0+s_0}^{t_0}+C_{t_0+s_0}^{t_0+1}
$$
对等式右边的第二项再次应用该结论，我们得到
$$
C_{t_0+s_0}^{t_0+1}=C_{t_0+s_0-1}^{t_0}+C_{t_0+s_0-1}^{t_0+1}
$$
注意到每次应用结论时第二项 C 上方的数不变，而下方的数减 1，于是我们对第二项反复应用该结论，直到下方的数减为 $t_0+1$，此时有
$$
C_{t_0+1+s_0}^{t_0+1}=C_{t_0+s_0}^{t_0}+C_{t_0+s_0-1}^{t_0}+\dots+C_{t_0+2}^{t_0}+C_{t_0+1}^{t_0}+C_{t_0+1}^{t_0+1}
$$
对于该等式右边的最后一项，我们知道
$$
C_{t_0+1}^{t_0+1}=C_{t_0}^{t_0}=1
$$
代回上式，再和①式逐项对比，是不是一模一样！

至此，我们就成功证明了
$$
ans_{t_0+1,s_0}=C_{t_0+1+s_0}^{t_0+1}
$$
结论得证。

---

__（以上是证明部分）__

好了，证明结束，可以愉快地计算了。乍一看这个表达式：
$$
C_{t+s}^{t}
$$
这不是[Lucas定理](https://www.luogu.com.cn/problem/P3807)吗?

仔细一想，不对，这道题的 $p$ 太大了，用不了...

再仔细读题，$n\le 5\times10^5$，直接计算就可以了！

我们知道，
$$
C_{t+s}^{t}=\frac{(t+s)(t+s-1)\dots t}{1\times2\times\dots\times s}
$$
对于分子，直接相乘即可，对于分母，需要求出在模 $998244353$ 下的逆元，然后再相乘，就可以得到结果。

```c++
i64 cal(int t, int s) { // t: 长度 s: 范围
    i64 n = 1;
    for (int i = 1; i <= t; ++i) {
        n *= s + i;
        n %= MOD;
        n *= arr[i]; // 直接用费小也可以 亲测和线性求逆元时间几乎一样
        n %= MOD;
    }
    return n;
}
```

由于本题数据范围并不大，且模数始终为 $998244353$，因此可以先通过线性算法将所有逆元先预处理好，计算的时候就可以直接访问了。关于求逆元的线性算法，参阅[洛谷P3811](https://www.luogu.com.cn/problem/P3811)。

```c++
    arr[1] = 1;
	for (int i = 2; i <= 500000; i++) // 预处理逆元，洛谷P3811
        arr[i] = (MOD - MOD / i) * arr[MOD % i] % MOD;
```

以上就是本题的完整思路，附上code：

# AC Code

```c++
#include <iostream>
#include <stack>

#define MAXN 500005
#define MOD ((119<<23)+1)
using namespace std;
using i64 = long long;

int pos[MAXN];
int chd[MAXN][2];
int val[MAXN];
i64 arr[MAXN];

inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}

/*
i64 qpow(i64 x, i64 e) {
    i64 ans = 1;
    i64 base = x;
    while (e) {
        if (e & 1) {
            ans *= base;
            ans %= MOD;
        }
        e >>= 1;
        base *= base;
        base %= MOD;
    }
    return ans;
}
*/

i64 cal(int t, int s) { // t: 长度 s: 范围
    i64 n = 1;
    for (int i = 1; i <= t; ++i) {
        n *= s + i;
        n %= MOD;
        n *= arr[i]; // 直接用费小也可以 亲测和线性求逆元时间几乎一样
        n %= MOD;
    }
    return n;
}

signed main() {
//    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
    int T;
    cin >> T;
    arr[1] = 1;
    for (int i = 2; i <= 500000; i++) // 预处理逆元，洛谷P3811
        arr[i] = (MOD - MOD / i) * arr[MOD % i] % MOD;
    while (T--) {
        int n = read(), c = read();
        for (int i = 1; i <= n; i++) {
            int l = read(), r = read();
            val[i] = read();
            if (l > 0) chd[i][0] = l;
            else chd[i][0] = 0;
            if (r > 0) chd[i][1] = r;
            else chd[i][1] = 0;
        }
        int cur = 1;
        int tot = 0;
        stack<int> s;
        while (!s.empty() || cur) { // 求中序遍历
            while (cur) {
                s.push(cur);
                cur = chd[cur][0];
            }
            cur = s.top();
            s.pop();
            pos[++tot] = val[cur];
            cur = chd[cur][1];
        }
        i64 ans = 1;
        pos[n + 1] = c;
        int tmp = 0;
        int pre = 1;
        for (int i = 1; i <= n + 1; i++) {
            if (pos[i] > 0) { // 遇到已知值则计算当前未知区间的结果
                ans *= cal(tmp, pos[i] - pre);
                ans %= MOD;
                pre = pos[i];
                tmp = 0;
            } else {
                tmp++; // 记录有多少个连续的未知值
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

~~个人认为比较简单的一道div2F，写篇题解氵一下~~



---

## 作者：ganpig (赞：0)

题目大意：给出一棵二叉搜索树，值域为 $[1,C]$，有一些结点的数未知，求可能的二叉搜索树种数。

容易发现**二叉搜索树的中序遍历是单调不降序列**，于是问题转化成了：给出一个序列，其中有一些位置的数未知，求使序列单调不降的填数方案数。

容易发现每个 $-1$ 的连续段的填数方案互不影响，于是可以分别计算每个连续段的答案，依据乘法原理，全部相乘即可。

容易发现一个连续段的答案只与其长度 $l$ 以及两侧已知数的差 $d$ 有关。

容易发现 $\{a_i\}$ 单调不降等价于 $\{a_i+i\}$ 单调上升，即连续段的答案即长度为 $l$，值域为 $[1,l+d-1]$ 的单调上升序列数。

容易发现这个数其实就是在 $(l+d-1)$ 个数中选出互不相同的 $l$ 个的方案数，即 $\tbinom {l+d-1}{l}$。
（咦，好眼熟的式子，[CF1931G](https://www.luogu.com.cn/problem/CF1931G) [刚见过](https://www.luogu.com.cn/blog/ganpig/solution-cf1931g)。）

但这题有些不同的地方，那就是 $l+d-1$ 很大，阶乘没法预处理，咋办？慌什么慌，容易发现 $\sum l \le n$，直接爆算组合数就行，总复杂度 $O(n \log p)$，这个 $\log$ 来自快速幂求逆元。

然后愉快地写好代码提交——好，TLE on 18！

看来我们得想办法把 $\log$ 优化掉。容易发现需要求逆元的数都在 $n$ 以内，可以用线性预处理一下逆元，总复杂度降到了 $O(n)$。

然后愉快地写好代码提交——好，TLE on 22！

~~不会真的有人像我赛时一样 `cin` 没关同步然后死活卡不过去吧~~

此题卡常空间很大，同样的复杂度能从 $>\text{2000ms}$ 卡到 [$\text{77ms}$](https://codeforces.com/contest/1929/submission/247101479)（目前是 CF 榜一）

### $\text{Code}$

```cpp
#include <bits/stdc++.h>
 
char *nowp = new char[5 << 21];
 
inline int read() {
    int x = 0;
    while (*nowp < '-')
        nowp++;
    if (*nowp == '-')
        return nowp += 3, 0;
    do
        x = x * 10 + (*nowp++ ^ '0');
    while (*nowp >= '0');
    return x;
}
 
constexpr int mod = 998244353, N = 5e5 + 5;
 
int l[N], r[N], v[N], inv[N];
 
int last, lastpos, pos;
long long ans;
 
inline void cal(int d, int n) {
    for (int i = 1; i <= n; i++)
        ans = ans * (d + i) % mod * inv[i] % mod;
}
 
void dfs(int u) {
    if (l[u])
        dfs(l[u]);
    pos++;
    if (v[u]) {
        if(pos != lastpos + 1)
            cal(v[u] - last, pos - lastpos - 1);
        last = v[u], lastpos = pos;
    }
    if (r[u])
        dfs(r[u]);
}
 
int main() {
    inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    fread(nowp, 1, 5 << 21, stdin);
    int T = read();
    while (T--) {
        int n = read(), c = read();
        for (int i = 1; i <= n; i++)
            l[i] = read(), r[i] = read(), v[i] = read();
        ans = last = 1, lastpos = pos = -1, dfs(1);
        cal(c - last, n - lastpos - 1);
        printf("%lld\n", ans);
    }
}
```

---

## 作者：int08 (赞：0)

## 前言

这个 Div.2 F 怎么比隔壁 [Div.3 G](https://www.luogu.com.cn/problem/CF1931G) 还简单啊（个人意见），还是同一个知识点。

不过第一次打 CF，还是加以纪念。
## 题意
给定一颗二叉搜索树的形态，并确定部分节点的值，剩下节点值在 $[1,C]$ 之间，询问满足条件的二叉搜索树赋值方法。

# Solution
看似题目中提到二叉搜索树，但是二叉搜索树形态都给定了，那二叉搜索树就失去意义了。

直接 DFS 得出其中序遍历序列，就把树上问题转化为序列问题：

一个长为 $n$ 序列，部分位置给定，剩下的在 $[1,C]$ 之间，问有多少种不同的不降序列。

若把两个相邻给定位置中间的称为一段未知区间，那么很容易发现不同未知区间计算答案互不干扰，乘起来即可。

对于一个未知区间，假设左右定值为 $x,y$，位置分别在第 $i,j$ 个，问题变成：

一个长为 $j-i-1$ 序列，每个数在 $[x,y]$ 之间，问有多少种不同的不降序列。

~~打表可以猜出结论。~~

但是从组合意义考虑也不算很难，考虑差分数组，就相当于把 $(y-x)$ 的增量分配给 $j-i$ 个位置，每个位置可以分配 $0$，经典[插板法](https://oi-wiki.org/math/combinatorics/combination/#%E6%8F%92%E6%9D%BF%E6%B3%95)，得出答案为：

$$ \binom{y-x+j-i-1}{j-i-1} $$

全部乘起来即可。

算组合数的除法使用逆元代替，复杂度 $\text{O}(n\log mod)$。

## AC Code
```cpp
#include<bits/stdc++.h> 
#define int long long
#define mod 998244353
using namespace std;
int qp(int x,int y)
{
	int ans=1;
	for(int i=1,j=x;i<=y;i*=2,j=(j*j)%mod) if(i&y) ans=(ans*j)%mod;
	return ans;
}
int C(int x,int y)
{
	if(y>x||y<0) return 0;
	int ans=1;
	for(int i=1;i<=y;i++) ans=(ans*(x+1-i))%mod,ans=(ans*qp(i,mod-2))%mod;
	return ans;
 } 
int t,n,ls[1919810],rs[1919810],dfn[1919810],val[1919810],reval[1919810],df,ans,c,i;
void dfs(int u)
{
	if(ls[u]!=-1)
	dfs(ls[u]);
	df++;
	reval[df]=val[u];
	if(rs[u]!=-1)
	dfs(rs[u]);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	for(int ac=1;ac<=t;ac++)
	{
		cin>>n>>c;
		df=0;ans=1;
		for(i=1;i<=n;i++)
		cin>>ls[i]>>rs[i]>>val[i];
		dfs(1);
		int last=0,lastv=1;reval[n+1]=c;
		for(i=1;i<=n+1;i++)
		{
			if(reval[i]!=-1)
			{
				int num=reval[i]-lastv,giv=i-last;
				ans=(ans*C(num+giv-1,giv-1))%mod;
				last=i;lastv=reval[i];
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
## 后记（一些胡言乱语）

人生第一场 CF Div.2 就碰见了难得一遇的超水 2F，不过却没有抓住机会。

想当年也是啥都不会的时候，打了第一场洛谷月赛，Rank 300 多，觉得低了，却在九个月，七场比赛中没有更高的排名。

后来我会了那场的 D（也是[我的第一紫](https://www.luogu.com.cn/problem/P7569)），觉得很唐。

这一次我又觉得我打得很唐，但是会不会，之后的几次，我更唐？

“那也总比没有开始过好。”
# The End.

---

## 作者：wangzhiyuan123 (赞：0)

显然要把二叉搜索树求中序遍历变成序列，相当于补全一个不降数组的方案数。  
对于一个长度为 $s$ 的极长的没有填数的连续段，设前一个数为 $a$，后一个数为 $b$（$0$ 号位设为 $1$，$n+1$ 号位设为 $c$），考虑插板，得出答案为 $\binom{b-a+s}{s}$。   
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
inline int read(){
	int w=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f=(ch=='-'?-1:f),ch=getchar();
	while(isdigit(ch)) w=w*10+ch-'0',ch=getchar();
	return w*f;
}
inline int qpow(int x,int b){
	int v=1;
	while(b){
		if(b&1) v=v*x%mod;
		x=x*x%mod;
		b>>=1;
	}
	return v;
}
int t;
int n=500000,c;
int a[500005],tot;
int deh[500005];
void init(){
	for(int i=1;i<=n;i++) deh[i]=qpow(i,mod-2);
}
int C(int n,int m){
	if(n<m) return 0;
	int nw=1;
	for(int i=1;i<=m;i++) nw=nw*deh[i]%mod*(n-i+1)%mod;
	return nw;
}
int L[500005],R[500005],val[500005];
void dfs(int x){
	if(L[x]!=-1) dfs(L[x]);
	a[++tot]=val[x];
	if(R[x]!=-1) dfs(R[x]);
}
main(){
	t=read();
	init();
	a[0]=1;
	while(t--){
		n=read(),c=read();
		tot=0;
		for(int i=1;i<=n;i++) L[i]=read(),R[i]=read(),val[i]=read();
		dfs(1);
		a[++tot]=c;
		int ans=1;
		for(int i=1,sum=0,lst=1;i<=tot&&ans;i++){
			if(a[i]!=-1){
				ans=ans*C(a[i]-lst+sum,sum)%mod;
				lst=a[i];
				sum=0;
			}else sum++;
		}
		printf("%lld\n",ans);
	}
}
```


---

## 作者：pyiming (赞：0)

# Sasha and the Wedding Binary Search Tree
## 题意简述
题目要求在给定二叉搜索树形态和一些节点的权值的情况下，计算有多少种方式填充剩余节点的权值，使得所有节点的权值都在 $[1, C]$ 的范围内。
## 题目分析
### 思路概述
1. **中序遍历**：首先对二叉搜索树进行中序遍历，这样可以得到一个节点权值从小到大的序列。
2. **序列问题转化**：在中序遍历得到的序列中，每两个相邻的已知权值 $l$ 和 $r$ 之间，可能有若干个未知权值的节点。这些未知权值的节点必须填入 $[l, r]$ 范围内的数值，并且这些数值需要有序。
3. **插板法**：对于每个区间 $[l, r]$ 内的未知节点，其填充方案数可以通过组合数学中的插板法计算。具体来说，如果有 $cnt$ 个未知节点，那么方案数为 $C(cnt + r - l, r - l)$。
4. **计算优化**：直接计算 $C(cnt+r-l,r-l)$ 显然会超时，只需求出 $\prod _ {i=r-l+1} ^ {cnt+r-1} i$ 和 $cnt!$ 即可。
### 代码解析
1. **中序遍历**：使用深度优先搜索（DFS）进行中序遍历，将节点权值存入一个数组。
2. **计算方案数**：遍历中序遍历得到的数组，对于每个连续的未知权值区间，使用插板法计算方案数。
3. **模运算和优化**：由于答案需要模 $998\,244\,353$，所有计算都在模意义下进行。使用预处理阶乘和逆元来优化计算过程。
### 时间复杂度
- 中序遍历的时间复杂度为 $O(n)$。
- 计算方案数的时间复杂度为 $O(n)$。
- 总时间复杂度为 $O(n)$。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353,N=5e5;
class tree{
    public:
    ll *lc,*rc;
    ll *v;
    tree(ll n){
        lc=new ll[n+1];
        rc=new ll[n+1];
        // fa=new ll[n+1];
        v=new ll[n+1];
        for(ll i=1;i<=n;i++){
            scanf("%lld%lld%lld",&lc[i],&rc[i],&v[i]);
            // if(lc[i]!=-1) fa[lc[i]]=i;
            // if(rc[i]!=-1) fa[rc[i]]=i;
        }
    }
    ~tree(){
        delete[] lc,rc,v;
    }
    void dfs(ll x,vector<ll> &s){
        if(lc[x]!=-1) dfs(lc[x],s);
        s.push_back(v[x]);
        if(rc[x]!=-1) dfs(rc[x],s);
    }
};
ll pow(ll a,ll b,ll p){
    ll ans=1;
    while(b){
        if(b&1) ans=ans*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ans;
}
ll jie[N+1],ijie[N+1];
int main(){
    jie[0]=1;
    for(ll i=1;i<=N;i++){
        jie[i]=jie[i-1]*i%mod;
    }
    ijie[N]=pow(jie[N],mod-2,mod);
    for(ll i=N-1;i>=0;i--){
        ijie[i]=ijie[i+1]*(i+1)%mod;
    }
    int T;
    scanf("%d",&T);
    while(T--){
        ll n,c;
        scanf("%lld%lld",&n,&c);
        tree t(n);
        vector<ll> s;
        t.dfs(1,s);
        ll l=1,cnt=0;
        ll ans=1;
        for(ll i:s){
            if(i==-1){
                cnt++;
            }
            else{
                ll t=1;
                for(ll j=i-l+1;j<=cnt+i-l;j++){
                    t=t*j%mod;
                }
                ans=ans*t%mod*ijie[cnt]%mod;
                cnt=0;
                l=i;    
            }
        }
        if(cnt){
            ll t=1;
            for(ll i=c-l+1;i<=cnt+c-l;i++){
                t=t*i%mod;
            }
            ans=ans*t%mod*ijie[cnt]%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

## 总结
本题的关键在于将二叉搜索树问题转化为序列问题，并应用组合数学中的插板法来计算填充方案数。

---

## 作者：wth2026 (赞：0)

# 题目大意
给我们一颗二叉搜索树，要求一共有多少种填充点权且最大点权不超过 $C$。
# 思路
先求出这棵树的中序遍历，然后用隔板发可以推出，
$$
ans = \sum C_{R - L + K}^{K}
$$
其中 $L$ 为所取权值的左端点，$R$ 为右端点，$K$ 为这一段连续的 $-1$ 的个数。
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define float double
#define int long long
#define inf 998244353

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")

using namespace std;

#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<20, stdin), p1 == p2) ? EOF : *p1 ++)
char *p1 ,*p2, buf[1 << 20 + 5];

inline int read() {
	int x = 0, f = 1;
	char c = gc();
	
	while (!isdigit(c)) {
		if (c == '-') {
			f = -1;
		}
		
		c = gc();
	}
	
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = gc();
	}
	
	return x * f;
}

inline void print(int x){
    if (x > 9) {
		print(x / 10);
	}
	
    putchar(x % 10 + '0');
}

int ksm(int x, int y, int mod) {
	int ans = 1, _ = x;
  
	while (y) {
		if (y & 1) {
			ans *= _;
			ans %= mod;
		}
		
		y >>= 1;
		_ *= _;
		_ %= mod;
	}
  
	return ans;
}

int C(int x, int y, int mod) {
	if (y > x || y < 0) {
		return 0;
	}
	
	if (!y) {
		return 1;
	}
	
	if (x - y < y) {
		y = x - y;
	}
	
	int ans = 1;
	
	for (int i = 1; i <= y; ++ i) {
		ans = (ans * (x + 1 - i)) % mod;
		ans = (ans * qp(i, mod - 2, mod)) % mod;
	}
	
	return ans;
}

void init() {
}

struct BST {
	int l, r, u;
} tr[500005];

int cnt, zx[500005];

void zxbl(int k) {
	if (k == -1) {
		return;
	}
	
	zxbl(tr[k].l);
	zx[++ cnt] = tr[k].u;
	zxbl(tr[k].r);
}

int T, n, c, l, r, u, L, R, K, ans;

signed main() {
	init();
	
	T = read();
	
	while (T --) {
		cnt = 0;
		ans = 1;
		L = 1;
		K = 0;
		n = read();
		c = read();
		R = c;
		
		for (int i = 1; i <= n; ++ i) {
			l = read();
			tr[i].l = l;
			r = read();
			tr[i].r = r;
			u = read();
			tr[i].u = u;
		}
		
		zxbl(1);
		
//		for (int i = 1; i <= n; ++ i) {
//			cout << zx[i] << ' ';
//		}
//		
//		cout << endl;
//		
		for (int i = 1; i <= n; ++ i) {
			if (zx[i] == -1) {
				++ K;
			} else {
				R = zx[i];
				ans *= C(R - L + K, K, inf);
				ans %= inf;
				K = 0;
				L = zx[i];
			}
		}
		
		if (K) {
			ans *= C(c - L + K, K, inf);
			ans %= inf;
		}
		
		print(ans);
		puts("");
	}
	
	return 0;
}
```

---

