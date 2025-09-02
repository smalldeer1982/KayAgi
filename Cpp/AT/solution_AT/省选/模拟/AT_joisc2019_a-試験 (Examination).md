# 試験 (Examination)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2019/tasks/joisc2019_a



# 题解

## 作者：Zpair (赞：4)

当 $x+y \ge z$ 第三个限制没用，可以直接二维数点。下面假设 $x+y<z$。

![](https://cdn.luogu.com.cn/upload/image_hosting/spd4uakr.png)

（这是官方题解的图）

先算出黑框部分的点数，即 $a+b \ge z$ 的点数，随便数一下点即可。

然后需要减去 $a<x$，$a+b \ge z$ 和 $b<y$，$a+b \ge z$ 的点数，二维数点一下。

考虑减重的部分，即 $a<x$，$b<y$，$a+b \ge z$ 的点，我们假设了 $x+y<z$，所以不存在重复部分。

综上只需二维数点，时间复杂度为线性对数。

---

## 作者：lzyqwq (赞：3)

**[更好的阅读体验](https://www.cnblogs.com/MnZnOIerLzy/articles/17205561.html)**

# $\texttt{Description}$

**[洛谷题目链接](https://www.luogu.com.cn/problem/AT_joisc2019_a "洛谷题目链接")**

**[AtCoder 题目链接](https://atcoder.jp/contests/joisc2019/tasks/joisc2019_a "AtCoder 题目链接")**

**[PDF 题面](https://www.ioi-jp.org/camp/2019/2019-sp-tasks/day1/examination.pdf "PDF 题面")**

> - 有 $n$ 个二元组 $(a_i,b_i)$ 和 $q$ 个询问 $(x_j,y_j,z_j)$，每个询问求满足 $a_i\ge x_j$，$b_i\ge y_j$，$a_i+b_i\ge z_j$ 的二元组个数。
>
>- $n,q\le 10^5$，$a_i,b_i,x_j,y_j\le 10^9$，$z_j\le 2\times 10^9$。

# $\texttt{Solution}$

三维偏序模板题，考虑使用**权值树状数组套平衡树**。

先对于 $b_i$ 和 $y_j$ 离散化，开一棵权值树状数组，内部嵌套平衡树。

再把所有信息按照 $a_i$ 和 $x_j$ **从大到小**排序，使得每个询问统计的都是 $\ge x_j$ 的贡献。若相同，则把**二元组**排在前，因为这些二元组是满足 $a_i\ge x_j$ 的，可能会产生贡献（若没有则会在树套树中被舍去，所以要排在前）。

对于每个二元组，把 $a_i+b_i$ 插入到自己和祖先的平衡树上。注意插入一个二元组，用第二元来维护可重。

对于每个询问，查询 $[1,y_j]$ 的平衡树中，$[z_j,\infty]$ 中的元素个数。由于没有上界，可以用整棵树的大小减去 $<z_j$ 的个数。树状数组前缀查询即可。

时间复杂度 $\mathcal{O}((n+q)\log^2n)$，空间复杂度 $\mathcal{O}(n\log n)$。可以在被 cdq 分治吊打的同时接受，当然还是可以吊打权值树状数组套动态开点线段树的。

# $\texttt{Code}$

代码实现细节：

- 注意权值树状数组开 $2$ 倍空间，因为二元组和询问一起离散化。

- 可以用指令集加快代码效率。

- 我是使用 `set` 和 `map` 两个 STL 来实现离散化的。

- 我是使用 [`pb_ds` 库中的 `rb_tree_tag`（红黑树）](https://oi.wiki/lang/pb-ds/tree/ "`pb_ds`")来实现平衡树的。码量较小，理论效率较优，但是常数较大。


**[Submission](https://atcoder.jp/contests/joisc2019/submissions/39580060 "Submission")**

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define g __gnu_pbds
#define N 100005
#define pii pair<int,int>
#define tp make_pair
using namespace std;
int n,q,lsh,ans[N],cnt;
set<int>s;
map<int,int>mp;
g::tree<pii,g::null_type,less<pii>,g::rb_tree_tag,g::tree_order_statistics_node_update>bit[N<<1];
struct query{
    int a,b,c,id;
    query(){
        a=b=c=id=0;
    }
}p[N<<1];
void modify(int x,int k){
    for(int i=x;i<=lsh;i+=i&-i){
        bit[i].insert(tp(k,++cnt));
    }
}
int qnum(int x,int k){
    int ret=0;
    for(int i=x;i;i-=i&-i){
        ret+=bit[i].size()-bit[i].order_of_key(tp(k,0));
    }
    return ret;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i){
        scanf("%d%d",&p[i].a,&p[i].b);
        s.insert(-p[i].b);//取反实现大的在前
        p[i].c=p[i].a+p[i].b;
    }
    for(int i=1;i<=q;++i){
        scanf("%d%d%d",&p[n+i].a,&p[n+i].b,&p[n+i].c);
        s.insert(-p[n+i].b);
        p[n+i].id=i;
    }
    for(int i:s){
        mp[-i]=++lsh;
    }
    for(int i=1;i<=n+q;++i){
        p[i].b=mp[p[i].b];
    }
    sort(p+1,p+1+n+q,[](query u,query v){return u.a^v.a?u.a>v.a:u.id<v.id;});
    for(int i=1;i<=n+q;++i){
        if(p[i].id){
            ans[p[i].id]=qnum(p[i].b,p[i].c);
        }else{
            modify(p[i].b,p[i].c);
        }
    }
    for(int i=1;i<=q;++i){
        printf("%d\n",ans[i]);
    }
}
```

---

## 作者：Hoks (赞：1)

## 前言
水题吧，三维偏序板子。

~~但是不知道为什么没有卡暴力，暴力也能过。~~
## 思路分析
因为二元组 $(a,b)$ 都为给定的，所以 $a+b$ 也为一个定值了。

令 $c=a+b$，则我们可以把一个二元组 $(a,b)$ 写为 $(a,b,c)$。

那题面就变成了给定 $(x,y,z)$ 询问有多少组 $(a,b,c)$ 满足 $x\le a,y\le b,z\le c$。

也就是三维偏序板子。

因为值域很大所以考虑离散化。

但用到值域的只有树状数组，所以我们只需要给 $c,z$ 离散化就行了。

对于三维偏序，考虑 CDQ 分治。

先把询问和给定的 $(a,b,c)$ 都加进来，放进一个三维平面里，优先处理正常点，然后再处理询问。

然后跑正常的 CDQ 就行了，具体细节可以看代码。
## 代码
```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define get(x) (lower_bound(c+1,c+1+tot,x)-c)
#define int long long
using namespace std;
const int N=3e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
struct node{int x,y,z,id;}a[N];
int n,m,tot,c[N<<1],ans[N];
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    inline void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    inline int query(int x){int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
    inline void mdf(int l,int r,int v){modify(l,v),modify(r+1,-v);}
}tt;
namespace fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void print(int x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x>9) print(x/10);
		putchar(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='M'||c=='Q'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}using namespace fast_IO;
inline bool cmpx(node x,node y){return (x.x^y.x)?x.x>y.x:x.id<y.id;}
inline bool cmpy(node x,node y){return (x.y^y.y)?x.y>y.y:x.id<y.id;}
void cdq(int l,int r)
{
	if(l==r)return;cdq(l,mid);cdq(mid+1,r);
	sort(a+l,a+mid+1,cmpy);sort(a+mid+1,a+r+1,cmpy);
	int i=mid+1,j=l;
	for(;i<=r;i++)
	{
		while(a[j].y>=a[i].y&&j<=mid) tt.modify(a[j].z,!a[j].id),j++;
		ans[a[i].id]+=tt.query(a[i].z);
	}
	for(i=l;i<j;i++) tt.modify(a[i].z,-!a[i].id);
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read(),c[++tot]=a[i].z=a[i].x+a[i].y,a[i].id=0;
	for(int i=n+1;i<=m+n;i++) a[i].x=read(),a[i].y=read(),c[++tot]=a[i].z=read(),a[i].id=i-n;
	sort(c+1,c+1+tot);tot=unique(c+1,c+1+tot)-c-1;tt.n=n+m;
	for(int i=1;i<=n+m;i++) a[i].z=-get(a[i].z)+tot+1;
	sort(a+1,a+1+n+m,cmpx);cdq(1,n+m);
	for(int i=1;i<=m;i++) print(ans[i]),puts("");
	return 0;
}
```

---

## 作者：strcmp (赞：0)

呜，好爽惹~

---

这题三维数点的做法过于不动脑子，来点单 log 机械降神。

首先如果 $x + y \ge z$ 那直接不用管了，就是一个二维数点。

那么转过去考虑 $x + y < z$ 的情况。

将二元组 $(a,\,b)$ 看作二维点。

直接启动容斥。

我们的限制是：$a \ge x \wedge b \ge y \wedge a + b \ge z$，满足 $x + y < z$。

全集先定为 $a + b \ge z$ 的点个数，这随便数数就完了。

先考虑容斥 $a < x \wedge a + b \ge z$ 的点，二维数点即可。

然后容斥掉 $b < y \wedge a + b \ge z$ 的点，也是一个二维数点。

然后我们发现 $a < x \wedge b < y \wedge a + b \ge z$ 减了两次。

但是：$a < x,\,b < y \Rightarrow a + b < x + y < z$。

  所以这种情况不存在。

至此问题全部都是平凡的二维数点，直接做即可。

时间复杂度 $\Theta(n \log n)$。

写了一大坨常数极大。

正睿 24ab 测 Day8 T1 用了几乎完全一样的容斥的说。

```cpp
#include <bits/stdc++.h>
#define re register
#define X first
#define Y second
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define pb push_back
#define lb lower_bound
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
constexpr int maxn = 1e6 + 10, mod = 998244353, r2 = 499122177;
const ll inf = 1145141919810520L;
struct Que { int lf, x, y, z; } q[maxn];
inline int cmp(const Que& p1, const Que& p2) { return p1.lf != p2.lf ? p1.lf < p2.lf : p1.z < p2.z; }
inline int cmp2(const Que& p1, const Que& p2) { return p1.lf != p2.lf ? p1.lf > p2.lf : p1.z > p2.z; }
int n, l[maxn], r[maxn], L[maxn], R[maxn], K[maxn], c[maxn], sum[maxn], d[maxn], t = 0; int ans[maxn], Q;
inline void add(int x, int d) { while (x <= t) c[x] += d, x += x & -x; }
inline int qry(int x) { int s = 0; while (x) s += c[x], x -= x & -x; return s; }
inline int id(int x) { return lb(d + 1, d + t + 1, x) - d; }
int main() {
	//freopen("01-11.in", "r", stdin);
	//freopen("01-11.out", "w", stdout);
	scanf("%d%d", &n, &Q);
	for (int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]), d[++t] = l[i], d[++t] = r[i], d[++t] = l[i] + r[i];
	for (int i = 1; i <= Q; i++) scanf("%d%d%d", &L[i], &R[i], &K[i]), d[++t] = L[i], d[++t] = R[i], d[++t] = L[i] + R[i], d[++t] = K[i];
	sort(d + 1, d + t + 1); t = unique(d + 1, d + t + 1) - d - 1;
	for (int i = 1; i <= n; i++) ++sum[id(r[i] + l[i])];
	for (int i = t; i >= 1; i--) sum[i] += sum[i + 1];
	for (int i = 1; i <= Q; i++) if (R[i] + L[i] < K[i]) ans[i] = sum[id(K[i])]; int p = 0;
	for (int i = 1; i <= Q; i++) if (R[i] + L[i] < K[i]) q[++p] = { id(L[i]), id(K[i]), i, 0 };
	for (int i = 1; i <= n; i++) q[++p] = { id(l[i]), id(r[i] + l[i]), i, 1 }; int u = 1; q[++p] = { (int)1e9, 0, 0, 0 };
	sort(q + 1, q + p + 1, cmp);
	//for (int i = 1; i <= p; i++) cout << q[i].lf << " " << q[i].y << " " << q[i].z << "\n";
	for (int i = 1; i <= t; i++) {
		while (q[u].lf <= i) {
			if (q[u].z == 0) ans[q[u].y] -= qry(t) - qry(q[u].x - 1);
			else add(q[u].x, 1); ++u;
		}
	}
	for (int i = 1; i <= p; i++) q[i] = { 0, 0, 0, 0 };
	p = 0, u = 1;
	for (int i = 1; i <= t; i++) c[i] = 0;
	for (int i = 1; i <= Q; i++) if (R[i] + L[i] < K[i]) q[++p] = { id(R[i]), id(K[i]), i, 0 };
	for (int i = 1; i <= n; i++) q[++p] = { id(r[i]), id(r[i] + l[i]), i, 1 }; q[++p] = { (int)1e9, 0, 0, 0 };
	sort(q + 1, q + p + 1, cmp);
	for (int i = 1; i <= t; i++) {
		while (q[u].lf <= i) {
			if (q[u].z == 0) ans[q[u].y] -= qry(t) - qry(q[u].x - 1);
			else add(q[u].x, 1); ++u;
		}
	}
	for (int i = 1; i <= p; i++) q[i] = { 0, 0, 0, 0 }; p = 0, u = 1;
	for (int i = 1; i <= t; i++) c[i] = 0;
	for (int i = 1; i <= Q; i++) if (R[i] + L[i] >= K[i]) q[++p] = { id(L[i]), id(R[i]), i, 0 };
	for (int i = 1; i <= n; i++) q[++p] = { id(l[i]), id(r[i]), i, 1 }; 
	sort(q + 1, q + p + 1, cmp2);
	//for (int i = 1; i <= p; i++) cout << q[i].lf << " " << q[i].x << " " << q[i].y << " " << q[i].z << "\n";
	for (int i = t; i >= 1; i--) {
		while (q[u].lf >= i) {
			if (q[u].z == 0) {
				if (q[u].lf > t) break;
				ans[q[u].y] = qry(t) - qry(q[u].x - 1);
			}
			else add(q[u].x, 1); ++u;
		}
	}
	for (int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：gyyyyx (赞：0)

很水啊，很板啊。

看数据范围可以直接上三维偏序，这里其他题解都有讲就不写了。

但三维偏序要两只 $\log$，如果数据大一点，比如 $n\leq 10^6$ 的话是过不了的。

那是否有办法优化？

观察到实际上这并不是一个普通的三维偏序，每个点的第三维是和前两维紧密相关的。

考虑将其转化为二维。

对于第 $i$ 个询问画出直线 $x=x_i,y=y_i,x+y=z_i$，则我们每次询问要求的就是这么一个黑框部分的点数。

![](https://cdn.luogu.com.cn/upload/image_hosting/r4qqtk5v.png)

注意这里只考虑 $x_i+y_i<z_i$ 的情况。

我们容斥一下，那么答案就是 $cnt_A=cnt_{AB}-cnt_B$，其中 $cnt_X$ 指属于 $X$ 这个区域的点数。

![](https://cdn.luogu.com.cn/upload/image_hosting/egjx752l.png)

显然 $cnt_{AB}$ 就是一个简单的二维数点。

下面考虑如何计算 $cnt_B$，我们发现一个点 $(a,b)$ 属于 $B$ 当且仅当：$x_i\leq a\leq z_i-y_i,b\geq y_i,a+b<z_i$。

这还是一个三维偏序问题，考虑继续容斥。

我们先作一条辅助线，增加一个区域 $C$。

![](https://cdn.luogu.com.cn/upload/image_hosting/q5o2qtmi.png)

此时有 $cnt_B=cnt_{BC}-cnt_{C}$，显然 $cnt_C$ 是一个二维数点。

而对于梯形区域 $BC$，我们发现其中的点满足 $x_i\leq a\leq z_i-y_i,a+b<z_i$，这也是个二维数点。

那我们只需要做三次二维数点，答案即为 $cnt_A=cnt_{AB}+cnt_C-cnt_{BC}$。

码量和代码难度不大，虽然有 $3$ 倍常数，但可以用树状数组而不用 CDQ 分治，常数也不大。

而且理论时间复杂度只有一只 $\log$，远优于三维偏序。

最后注意特判 $x_i+y_i>=z_i$，此时只需要数 $a+b>=z_i$ 的条件是无效的，只需要一次二位偏序即可。

如果没有特判会容斥出奇怪的东西（不要问我怎么知道的，问就是血与泪的教训）。

还有记得开 $3$ 倍数组，并且要离散化。

代码：

```cpp
#include<bits/stdc++.h>
#define N 200005
#define M 600006
using namespace std;
int n,q,a[N],b[N],x[N],y[N],z[N];
int ans[N];
struct Node{
	int x,y,id,flg;
	Node(int a=0,int b=0,int c=0,int d=0):x(a),y(b),id(c),flg(d){}
	bool operator < (const Node &k)const {return x^k.x?x<k.x:id<k.id;}
} p[M];
int tot;
int H[M],len;
inline void PreWorkHash(){
	for(int i(1);i<=tot;++i) H[i]=p[i].y;
	sort(H+1,H+1+tot);len=unique(H+1,H+1+tot)-H-1;
	for(int i(1);i<=tot;++i) p[i].y=lower_bound(H+1,H+1+len,p[i].y)-H;
}
int c[M];
inline int lowbit(int x){return x&-x;}
inline void Add(int x){
	while(x<=len){
		++c[x];
		x+=lowbit(x);
	}
}
inline int Sum(int x){
	int ret(0);
	while(x){
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}
inline void Solve(){
	PreWorkHash();
	sort(p+1,p+1+tot);
	for(int i(1);i<=tot;++i){
		if(p[i].id) ans[p[i].id]+=Sum(p[i].y)*p[i].flg;
		else Add(p[i].y);
	}
	memset(c,0,sizeof(c));
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i(1);i<=n;++i) scanf("%d%d",&a[i],&b[i]);
	for(int i(1);i<=q;++i) scanf("%d%d%d",&x[i],&y[i],&z[i]);
	for(int i(1);i<=n;++i) p[++tot]=Node(-a[i],-b[i]);
	for(int i(1);i<=q;++i) p[++tot]=Node(-x[i],-y[i],i,1);
	Solve();tot=0;
	for(int i(1);i<=n;++i) p[++tot]=Node(a[i],b[i]);
	for(int i(1);i<=q;++i){
		if(z[i]<=x[i]+y[i]) continue;
		p[++tot]=Node(z[i]-y[i],y[i]-1,i,1);
		p[++tot]=Node(x[i]-1,y[i]-1,i,-1);
	}
	Solve();tot=0;
	for(int i(1);i<=n;++i) p[++tot]=Node(a[i],a[i]+b[i]);
	for(int i(1);i<=q;++i){
		if(z[i]<=x[i]+y[i]) continue;
		p[++tot]=Node(z[i]-y[i],z[i]-1,i,-1);
		p[++tot]=Node(x[i]-1,z[i]-1,i,1);
	}
	Solve();
	for(int i(1);i<=q;++i) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Endline (赞：0)

## k-D Tree

这显然是一个三维偏序，可以将给出的二元组 $(a,b)$，变成三元组 $(a,b,a+b)$，然后就变成三维偏序的板子题了。

考虑 k-D Tree。我们发现如果对原来的三元组序列建树，再对每一个查询在线回答，复杂度会达到 $\Theta(qn^{\frac23})$，虽然理论上能过，但是 k-D Tree 的巨大常数[让我 T 成了 sb](https://atcoder.jp/contests/joisc2019/submissions/46647994)。

考虑如何优化。可以将查询离线下来从大到小排序，并将原来的三元组从大到小加入 k-D Tree，这样我们需要动态 k-D Tree，用替罪羊树的重构思想保证树高，最后可以优化到 $\Theta(q\sqrt n)$，可以通过。[~~但喜提最劣解~~](https://www.luogu.com.cn/record/129687082)

## AC Code

```cpp
#include<bits/stdc++.h>
#define MAXN 100002
using namespace std;
double alpha=0.7;
int n,q,ans,cnt,root;
int rub[MAXN],top;
int res[MAXN];
pair<int,int>p[MAXN];
struct dat
{
    int a[3];
    inline int&operator[](int x){return a[x];}
    inline bool in(int x[])
    {
        for(int i=0;i<=2;i++)
            if(a[i]<x[i])return false;
        return true;
    }
}d[MAXN];
struct qry
{
    int a[3],id;
    inline int&operator[](int x){return a[x];}
}qr[MAXN];
struct node
{
    pair<int,int>crl;
    int ls,rs,siz;
    int minn[2],maxx[2];
    inline bool all_in(pair<int,int>k){return minn[0]>=k.first&&minn[1]>=k.second;}
    inline bool all_out(pair<int,int>k){return maxx[0]<k.first||maxx[1]<k.second;}
}tr[MAXN];
inline bool cmp0(pair<int,int>x,pair<int,int>y){return x.first!=y.first?x.first<y.first:x.second<y.second;}
inline bool cmp1(pair<int,int>x,pair<int,int>y){return x.second!=y.second?x.second<y.second:x.first<y.first;}
inline int newnode()
{
    if(top)return rub[top--];
    return ++cnt;
}
inline void pushup(int tp)
{
    tr[tp].siz=1;
    tr[tp].minn[0]=tr[tp].maxx[0]=tr[tp].crl.first;
    tr[tp].minn[1]=tr[tp].maxx[1]=tr[tp].crl.second;
    if(tr[tp].ls)
    {
        tr[tp].siz+=tr[tr[tp].ls].siz;
        for(int i=0;i<=1;i++)
            tr[tp].minn[i]=min(tr[tp].minn[i],tr[tr[tp].ls].minn[i]),
            tr[tp].maxx[i]=max(tr[tp].maxx[i],tr[tr[tp].ls].maxx[i]);
    }
    if(tr[tp].rs)
    {
        tr[tp].siz+=tr[tr[tp].rs].siz;
        for(int i=0;i<=1;i++)
            tr[tp].minn[i]=min(tr[tp].minn[i],tr[tr[tp].rs].minn[i]),
            tr[tp].maxx[i]=max(tr[tp].maxx[i],tr[tr[tp].rs].maxx[i]);
    }
    return;
}
int build(int l,int r,bool opt)
{
    if(l>r)return 0;
    int tp=newnode(),mid=l+r>>1;
    nth_element(p+l,p+mid,p+r+1,opt?cmp1:cmp0);
    tr[tp].crl=p[mid];
    tr[tp].ls=build(l,mid-1,opt^1);
    tr[tp].rs=build(mid+1,r,opt^1);
    pushup(tp);
    return tp;
}
void vat(int tp,int id)
{
    if(tr[tp].ls)vat(tr[tp].ls,id);
    p[id+tr[tr[tp].ls].siz+1]=tr[tp].crl,rub[++top]=tp;
    if(tr[tp].rs)vat(tr[tp].rs,id+tr[tr[tp].ls].siz+1);
    return;
}
inline void check(int&tp,bool opt)
{
    if(max(tr[tr[tp].ls].siz,tr[tr[tp].rs].siz)>alpha*tr[tp].siz)
    {
        vat(tp,0);
        tp=build(1,tr[tp].siz,opt);
    }
    return;
}
void insert(int&tp,pair<int,int>k,bool opt)
{
    if(!tp)
    {
        tp=newnode();
        tr[tp].crl=k;
        tr[tp].ls=tr[tp].rs=0,tr[tp].siz=1;
        pushup(tp);
        return;
    }
    if(opt)
    {
        if(k.second>tr[tp].crl.second)insert(tr[tp].rs,k,opt^1);
        else insert(tr[tp].ls,k,opt^1);
    }
    else
    {
        if(k.first>tr[tp].crl.first)insert(tr[tp].rs,k,opt^1);
        else insert(tr[tp].ls,k,opt^1);
    }
    pushup(tp);check(tp,opt);
}
void query(int tp,pair<int,int>k)
{
    if(!tp)return;
    if(tr[tp].crl.first>=k.first&&tr[tp].crl.second>=k.second)ans++;
    if(tr[tr[tp].ls].all_in(k))ans+=tr[tr[tp].ls].siz;
    else if(!tr[tr[tp].ls].all_out(k))query(tr[tp].ls,k);
    if(tr[tr[tp].rs].all_in(k))ans+=tr[tr[tp].rs].siz;
    else if(!tr[tr[tp].rs].all_out(k))query(tr[tp].rs,k);
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>d[i][0]>>d[i][1];
        d[i][2]=d[i][0]+d[i][1];
    }
    sort(d+1,d+n+1,[](dat x,dat y){return x[0]<y[0];});
    for(int i=1;i<=q;i++)
    {
        cin>>qr[i][0]>>qr[i][1]>>qr[i][2];
        qr[i].id=i;
    }
    sort(qr+1,qr+q+1,[](qry x,qry y){return x[0]<y[0];});
    for(int i=q,j=n+1;i>=1;i--)
    {
        while(j>=2&&d[j-1][0]>=qr[i][0])
        {
            j--;
            insert(root,make_pair(d[j][1],d[j][2]),0);
        }
        ans=0;
        query(root,make_pair(qr[i][1],qr[i][2]));
        res[qr[i].id]=ans;
    }
    for(int i=1;i<=q;i++)
        printf("%d\n",res[i]);
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

首先值域很大，限制是偏序关系，考虑离散化。

然后看到三个限制，考虑转三维偏序。

对于给定二元组 $(a,b)$ 考虑构造一个三维空间上的点 $(a,b,a+b)$ 对于询问直接构造三维空间上的点 $(x,y,z)$，然后问题就顺利变成了一个三维偏序。

因为询问点只询问不做贡献，二元组点只做贡献不询问，而我们不能将做贡献与做询问混为一谈，因此考虑给每个点按照以位置 $(a,b,c)$ 与其的类型排序，将询问点排到贡献点的后边，合并相同的点（位置类型均相同）接着就使得所有点互不相同且有序。

考虑做一遍使用树状数组维护的 CDQ 分治即可。时间复杂度 $O(n \log^2 n)$ 空间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) (x&-(x))
using namespace std;
const int maxn = 1e6 + 114;
const int mod = 1e9 + 7;
const int top = 1000000;
struct Point {
    int x, y, z, cnt;
    bool operator>(const Point &X) {
        if (x == X.x) {
            if (y == X.y) {
                if (z == X.z)
                    return cnt > X.cnt;
                else
                    return z > X.z;
            } else
                return y > X.y;
        }

        return x > X.x;
    }
    Point(int X = 0, int Y = 0, int Z = 0, int ID = 0, int CNT = 0) {
        x = X, y = Y, z = Z;
        id = ID, cnt = CNT;
    }
    int id;
} a[maxn]; //点
int tot;
int answer[maxn];
int tr[maxn];
void add(int x, int v) {
    while (x <= top)
        tr[x] += v, x += lowbit(x);
}
int pre(int x) {
    int res = 0;

    while (x > 0)
        res += tr[x], x -= lowbit(x);

    return res;
}
vector<Point> p;
map<int, map<int, int>> Index[maxn];
pair<int, pair<int, int>> found[maxn];
void CDQ(int l, int r) {
    if (l == r) {
        return ;
    }

    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    int q1 = l, q2 = mid + 1;
    stack< pair<int, int>> del;

    while (q2 <= r) {
        while (a[q1].y >= a[q2].y && q1 <= mid) {
            add(a[q1].z, a[q1].cnt);
            del.push(make_pair(a[q1].z, a[q1].cnt));
            q1++;
        }

        if (a[q2].cnt == 0)
            answer[a[q2].id] += (pre(top - 1) - pre(a[q2].z - 1));

        q2++;
    }

    while (del.size() > 0)
        add(del.top().first, -del.top().second), del.pop();

    int p1 = l, p2 = mid + 1;

    while (p1 <= mid || p2 <= r) {
        if (p1 == mid + 1) {
            p.push_back(a[p2++]);
        } else if (p2 == r + 1) {
            p.push_back(a[p1++]);
        } else if (a[p1].y > a[p2].y) {
            p.push_back(a[p1++]);
        } else {
            p.push_back(a[p2++]);
        }
    }

    for (int i = l; i <= r; i++) {
        a[i] = p[i - l];
    }

    p.clear();
}
bool cmp(Point A, Point B) {
    return A > B;
}
int n, q;
map<int, int> A, B, C;
int aA[maxn], aB[maxn], aC[maxn];
int cA, cB, cC;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].z = a[i].x + a[i].y;
        a[i].cnt = 1;
        a[i].id = i;
    }

    for (int i = n + 1; i <= n + q; i++) {
        cin >> a[i].x >> a[i].y >> a[i].z;
        a[i].cnt = 0;
        a[i].id = i;
    }

    //离散化
    for (int i = 1; i <= n + q; i++)
        aA[i] = a[i].x, aB[i] = a[i].y, aC[i] = a[i].z;

    sort(aA + 1, aA + n + q + 1);
    sort(aB + 1, aB + n + q + 1);
    sort(aC + 1, aC + n + q + 1);

    for (int i = 1; i <= n + q; i++)
        A[aA[i]] = ++cA;

    for (int i = 1; i <= n + q; i++)
        B[aB[i]] = ++cB;

    for (int i = 1; i <= n + q; i++)
        C[aC[i]] = ++cC;

    for (int i = 1; i <= n + q; i++)
        a[i].x = A[a[i].x];

    for (int i = 1; i <= n + q; i++)
        a[i].y = B[a[i].y];

    for (int i = 1; i <= n + q; i++)
        a[i].z = C[a[i].z];

    for (int i = n + 1; i <= n + q; i++) {
        found[i].first = a[i].x;
        found[i].second.first = a[i].y;
        found[i].second.second = a[i].z;
    }

    vector<Point> seq;
    int c = 0;
    sort(a + 1, a + n + q + 1, cmp);

    for (int i = 1; i <= n + q; i++) {
        if (a[i].x != a[i + 1].x || a[i].y != a[i + 1].y || a[i].z != a[i + 1].z || a[i].cnt != a[i + 1].cnt ||
                i == n + q)
            seq.push_back(Point(a[i].x, a[i].y, a[i].z, ++tot, c + a[i].cnt)), c = 0;
        else
            c += a[i].cnt;
    }

    for (int i = 1; i <= tot; i++)
        a[i] = seq[i - 1];

    sort(a + 1, a + tot + 1, cmp);

    for (int i = 1; i <= tot; i++)
        if (a[i].cnt == 0)
            Index[a[i].x][a[i].y][a[i].z] = a[i].id;

    CDQ(1, tot);

    for (int i = n + 1; i <= n + q; i++)
        cout << answer[Index[found[i].first][found[i].second.first][found[i].second.second]] << '\n';

    return 0;
}
```


---

