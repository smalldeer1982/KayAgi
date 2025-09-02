# [ABC233Ex] Manhattan Christmas Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc233/tasks/abc233_h

$ 2 $ 次元平面上にクリスマスツリーが $ N $ 個あり、$ i $ 個目のクリスマスツリーは座標 $ (x_i,y_i) $ にあります。

以下の $ Q $ 個のクエリに答えてください。

> クエリ $ i $ ： $ (a_i,b_i) $ からマンハッタン距離で $ K_i $ 番目に近いクリスマスツリーまでの距離はいくつですか？

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 10^5 $
- $ 0\leq\ x_i\leq\ 10^5 $
- $ 0\leq\ y_i\leq\ 10^5 $
- $ i\neq\ j $ ならば $ (x_i,y_i)\ \neq\ (x_j,y_j) $
- $ 1\leq\ Q\ \leq\ 10^5 $
- $ 0\leq\ a_i\leq\ 10^5 $
- $ 0\leq\ b_i\leq\ 10^5 $
- $ 1\leq\ K_i\leq\ N $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ (3,5) $ から $ 1,2,3,4 $ 個目のクリスマスツリーまでのマンハッタン距離は、それぞれ $ 2,2,5,1 $ です。 よって、最初の $ 4 $ つのクエリの答えはそれぞれ $ 1,2,2,5 $ です。

## 样例 #1

### 输入

```
4
3 3
4 6
7 4
2 5
6
3 5 1
3 5 2
3 5 3
3 5 4
100 200 3
300 200 1```

### 输出

```
1
2
2
5
293
489```

# 题解

## 作者：kkxacj (赞：6)

#### 思路

用曼哈顿距离表示两点间的距离为 $\left |  x_1 - x_2\right | +\left |  y_1 - y_2\right | $，由于有两个绝对值，直接求距离第 $k$ 近会很复杂。

联想到另外一种距离表示公式，**切比雪夫距离**，它的距离表示方式为 $\max \left \{ \left |x_1-x_2  \right |,\left | y_1 - y_2 \right | \right \} $，这两个距离公式是可以互相转化的，我在[这篇博客](https://www.luogu.com.cn/article/u2h05qd9)曾讲了如何将切比雪夫距离转为曼哈顿距离，读者可以根据上面那篇博客的启发尝试自行推出如何将曼哈顿距离转为切比雪夫距离。

最后可以推出把 $\left ( x,y\right ) $ 转为 $\left ( x+y,x-y\right ) $，然后用切比雪夫距离表示方式求出的距离就是两点间的曼哈顿距离。

转成切比雪夫距离，这里就好做了，设当前要求距 $\left ( x,y\right )$ 第 $k$ 近的点是哪一个，直接二分一个距离 $mid$，看以 $\left ( x+y,x-y\right )$ 为中心，长度为 $mid \times 2$ 的正方形包含了几个点，与 $k$ 比较即可，可以用主席树维护即可。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+10;
int n,m,x,y,z,z1,z2,cnt,ans,l,r,mid,c[N*100],d[N*100],rt[N*100],o;
struct w
{
	int ad,l,r;
}b[N*100];
vector<int>a[N*3];
int change(int p,int l,int r,int k)
{
	b[++cnt] = b[p],b[cnt].ad++,p = cnt;
	if(l >= r) return p;
	int mid = (l + r)>>1;
	if(k <= mid) b[p].l = change(b[p].l,l,mid,k);
	else b[p].r = change(b[p].r,mid + 1,r,k);
	return p;
}
int ask(int fl,int fr,int l,int r,int L,int R)
{
	if(L <= l && r <= R) return b[fr].ad - b[fl].ad;
	int mid = (l + r)>>1,ans = 0;
	if(L <= mid) ans = ask(b[fl].l,b[fr].l,l,mid,L,R);
	if(mid < R) ans += ask(b[fl].r,b[fr].r,mid + 1,r,L,R);
	return ans;
}
signed main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d%d",&x,&y),a[x+y+1].push_back(x-y);
	for(int i = 1;i <= N*2;i++) 
	{
		rt[i] = rt[i-1];
		for(int j = 0;j < a[i].size();j++) rt[i] = change(rt[i],-N,N,a[i][j]);
	}
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d%d",&z1,&z2,&z);
		x = z1+z2,y = z1-z2;
		l = 0,r = N,ans = 0;
		while(l <= r)
		{
			mid = (l + r) >> 1;
			if(ask(rt[max(0ll,x-mid)],rt[min(2*N,x+mid+1)],-N,N,y-mid,y+mid) >= z) ans = mid,r = mid - 1;
			else l = mid+1;
		}
		printf("%d\n",ans);
	}
    return 0;
}
```

---

## 作者：MSqwq (赞：4)

![](https://img1.imgtp.com/2023/03/20/iTv3T3Wg.png)  

先介绍一下切比雪夫（？ 貌似很多人不知道这东西，挺常用的。    
首先由一类问题是这样的，对于单个点的移动的轨迹是国际象棋国王那样可以去到相邻八个格子，然后点 A 到点 B 的最短距离。  
公式就是 $dis=\max(\left| x_1-x_2 \right|,\left| y_1-y_2 \right|)$ 这个很显然。  
稍微推广一下在 n 维向量上是 $dis=\max(\left| x_{1i}-x_{2i} \right|)$。  
在 OI 中的运用可能大部分就是切比雪夫距离和曼哈顿距离的转化吧
转化是这样的 :  
曼哈顿坐标转切比雪夫坐标 $(x,y)$ 变为 $(x+y,x-y)$。  
切比雪夫坐标转曼哈顿坐标 $(x,y)$ 变为 $(\frac{x+y}{2},\frac{x-y}{2})$。  
三维以上就不能转化了（？ 不太会证明，在知乎看到了一个说这个的，[感兴趣可以看看](https://www.zhihu.com/question/396319776)。   
几何上是这样的  
欧几里得距离：  
![](https://img1.imgtp.com/2023/03/20/4Y6MrcGZ.png)    
曼哈顿距离：  
![](https://img1.imgtp.com/2023/03/20/OHNevLB0.png)  
切比雪夫距离：   
![](https://img1.imgtp.com/2023/03/20/D9OlABC9.png)  
这样就很明显可以看出三者关系了，比赛的时候如果忘了上面那东西可以现推一下（？  
无所谓了大概知道这些就差不多了，推荐几道板子（？  
[[TJOI2013]松鼠聚会](https://www.luogu.com.cn/problem/P3964)  
[[COCI2009-2010#7] KRALJEVI](https://www.luogu.com.cn/problem/P8075)  
[ [IOI2007] pairs 动物对数](https://www.luogu.com.cn/problem/P4648)  
[[POI2006]MAG-Warehouse](https://www.luogu.com.cn/problem/P3439)  
[[USACO08OPEN]Cow Neighborhoods G](https://www.luogu.com.cn/problem/P2906)  

------------

模拟赛被切比雪夫干爆了，甚至被签到干爆了。所以找了一个板子玩玩。（？   
首先你会发现这题如果直接用曼哈顿距离是不好维护的，因为你要考虑横纵两个坐标差的和，非常不好维护，但是转化为切比雪夫距离就会很好维护，只需要看 max 这个东西可以直接二位数点，更具体的就是这样横纵坐标独立，这就是为啥用曼哈顿距离维护不太好的原因。    
问题就变成正常的二维数点了，这个用主席树维护一下就完了，代码：  
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
    return x*f;
}

inline void wr(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>=10)wr(x/10);putchar(x%10+'0');
}

const int N=3e5+10,M=1e5;
vector<int>v[N];
int rt[N],num;
struct yqy{
    int ls,rs,v;
}t[N*50];

void insert(int &p,int l,int r,int v)
{
    t[++num]=t[p];p=num; 
    int mid=(l+r)>>1;
    if(l==r){t[p].v++;return;}
    if(v<=mid)insert(t[p].ls,l,mid,v);
    else insert(t[p].rs,mid+1,r,v);
    t[p].v=t[t[p].ls].v+t[t[p].rs].v;
}

int query(int p1,int p2,int l,int r,int ql,int qr)
{
    if(ql<=l&&r<=qr)return t[p2].v-t[p1].v;
    int mid=(l+r)>>1,ans=0;
    if(ql<=mid)ans+=query(t[p1].ls,t[p2].ls,l,mid,ql,qr);
    if(qr>=mid+1)ans+=query(t[p1].rs,t[p2].rs,mid+1,r,ql,qr);
    return ans;
}


int main()
{
    auto st=clock();
    int n=read();
    for(int i=1;i<=n;i++)
    {
        int x=read(),y=read();
        v[x+y+1].push_back(x-y+M+1);
    }
    int mx=2*M+1;
    for(int i=1;i<=mx;i++)
    {
        rt[i]=rt[i-1];
        for(auto x:v[i])insert(rt[i],1,mx,x);
    }
    int q=read();
    while(q--)
    {
        int xx=read(),yy=read(),k=read();
        int x=xx+yy+1,y=xx-yy+M+1;
        int l=0,r=mx,ans;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(query(rt[max(0,x-mid-1)],rt[min(mx,x+mid)],1,mx,max(1,y-mid),min(mx,y+mid))>=k)ans=mid,r=mid-1;
            else l=mid+1;
        }
        wr(ans);puts("");
    }
    auto en=clock();
    cerr<<en-st<<endl;
    return 0;
}
```  
最近好要 $APIO$ 和省选了（？ 祝大家 $RP++$ 

---

## 作者：_determination_ (赞：3)

凭啥你们都写主席树，两只 $\log$ 了不起是不是（气愤），我要写树套树！

曼哈顿转切比雪夫的过程其他题解已经讲得很清楚了，这里主要讲如何用三只 $\log$ 的树套树卡过这道题。

注意到我们只有单点修，所以可以把线段树套线段树改成树状数组套线段树，可以大幅减小常数。

然后我们发现这里是 AT，可以用火车头。

最后我们使用 `inline` 就可以概率通过这道题！

过不去的可以多交几发或随机选几个时间点交一发，反正我过了。

[Link](https://atcoder.jp/contests/abc233/submissions/55706436)，等有空了我会补主席树做法。

主席树做法：

当我们想要查询左上角为 $(x_1,y_1)$，右下角为 $(x_2,y_2)$ 的矩形时，考虑将其拆分为两个询问。

即 $(1,y_1,x_2,y_2)$ 和 $(1,y_1,x_1-1,y_2)$。而这两个询问均可以用主席树 $n\log n$ 预处理 $\log n$ 一次查询。算上二分的一个 $\log$ 复杂度总共为 $O(n\log^2n)$，无压力通过。

[哦哦补一下主席树做法的代码](https://atcoder.jp/contests/abc233/submissions/55729492)。

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc233_h)

## 思路

我们首先要把坐标轴旋转 $45$ 度。

为什么呢？可以观察到一个规律，与 $(x,y)$ 的曼哈顿距离 $\le k$ 的点是一个斜的矩形。

![](https://cdn.luogu.com.cn/upload/image_hosting/p9q9mp4u.png)

所以我们把 $(a,b)$ 的坐标变成 $(a+b,a-b)$，接下来就可以维护这个东西了。

然后有 $\verb!dalao!$ 告诉我这个东西叫做切比雪夫距离。

然后我们就可以二分一个距离，设这个距离为 $mid$。

使用主席树二维数点出矩形 $(x-mid,x+mid,y-mid,y+mid)$ 中的点数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e5+10;
int rt[N],root;vector<int>a[N];
struct hjt_Tree{
    #define ls (lc[x])
    #define rs (rc[x])
    #define mid ((l+r)>>1)
    int c[N*40],lc[N*40],rc[N*40];
    inline void update(int &x,int la,int l,int r,int p){
        x=++root;c[x]=c[la];ls=lc[la];rs=rc[la];
        if (l==r) return ++c[x],void();
        if (p<=mid) update(ls,lc[la],l,mid,p);
        else update(rs,rc[la],mid+1,r,p);
        c[x]=c[ls]+c[rs];
    }
    inline int query(int x,int l,int r,int ll,int rr){
        if (ll<=l && r<=rr) return c[x];
        int res=0;
        if (ll<=mid) res+=query(ls,l,mid,ll,rr);
        if (mid<rr) res+=query(rs,mid+1,r,ll,rr);
        return res;
    }
}T;
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;int x,y;
    for (int i=1;i<=n;++i) cin>>x>>y,a[x+y].push_back(x-y);
    for (int i=0;i<=2e5;++i){if (i>0) rt[i]=rt[i-1];for (auto v:a[i]) T.update(rt[i],rt[i],-1e5,1e5,v);}
    int q;cin>>q;
    while (q--){
        int a,b,k;cin>>a>>b>>k;
        int x=a+b,y=a-b;int l=0,r=4e5;
        while (l<r){
            int L=max((int)-1e5,y-mid),
                R=min((int)1e5,y+mid);
            int tmp=T.query(rt[min((int)2e5,x+mid)],-1e5,1e5,L,R);
            if (x-mid>0) tmp-=T.query(rt[x-mid-1],-1e5,1e5,L,R);
            if (tmp>=k) r=mid;else l=mid+1;
        }
        cout<<l<<'\n';
    }
    return 0;
}
```

---

## 作者：StayAlone (赞：1)

首先发现，对于一个点，距离它曼哈顿距离 $k$ 的所有点形成一个旋转 $45$ 度的正方形。考虑二分答案，那么只需要查询这样的一个正方形内有多少点即可。

显然，这是一个二维数点问题。考虑用主席树维护斜线：第 $i$ 棵树表示，在直线 $y=x+i$ 上的所有点的集合；容易发现在（斜着）同一行上的所有点 $(u, v)$，都满足 $u+v$ 是定值，所以只需要以此作为第二维即可。

省流：对于点 $(u, v)$，以 $v-u$ 为横坐标，$u+v$ 为纵坐标插入二维平面。

查询就非常简单了，写代码的时候注意处理负数和边界。

[AC record](https://www.luogu.com.cn/record/123509737)

```cpp
int n, root[MAXN];
const int P = 2e5 + 5; vector <int> pos[MAXN];

struct setr {
	struct {
		int lp, rp, cnt;
	} t[MAXN * LOGN << 1];
	int tot;
	
	il void pushup(int x) {
		t[x].cnt = t[t[x].lp].cnt + t[t[x].rp].cnt;
	}
	
	il int upd(int x, int l, int r, int k) {
		int now = ++tot; t[now] = t[x];
		if (l == r) return ++t[now].cnt, now;
		int mid = l + r >> 1;
		if (k <= mid) t[now].lp = upd(t[x].lp, l, mid, k);
		else t[now].rp = upd(t[x].rp, mid + 1, r, k);
		return pushup(now), now;
	}
	
	il int query(int v1, int v2, int l, int r, int ql, int qr) {
		if (l > qr || r < ql) return 0;
		int now = t[v2].cnt - t[v1].cnt;
		if (l >= ql && r <= qr) return now;
		int mid = l + r >> 1;
		return query(t[v1].lp, t[v2].lp, l, mid, ql, qr) + query(t[v1].rp, t[v2].rp, mid + 1, r, ql, qr);
	}
} T;

int main() {
	read(n);
	rep1(i, 1, n) {
		int x, y; read(x, y);
		pos[y - x + (P >> 1)].eb(x + y);
	}
	rep1(i, 1, P) {
		root[i] = root[i - 1];
		for (auto v : pos[i]) root[i] = T.upd(root[i], 0, P, v);
	}
	for (int Q = read(), u, v, k; Q--; ) {
		read(u, v, k); int w = v - u + (P >> 1), w2 = u + v;
		int l = 0, r = P;
		while (l ^ r) {
			int mid = l + r >> 1;
			if (T.query(root[max(w - mid - 1, 1)], root[min(w + mid, P)], 0, P, max(w2 - mid, 0), min(w2 + mid, P)) >= k) r = mid;
			else l = mid + 1;
		} printf("%d\n", l);
	}
	rout;
}
```

---

## 作者：Masterwei (赞：1)

#### 前言

昨天 VP 了一场，然后秒了，结果没调出来。

#### 思路

发现本题的距离是曼哈顿距离，考虑将其转化为切比雪夫距离，也就是将点 $(x,y)$ 转化为 $(x+y,x-y)$。

对于一个询问，我们可以二分一个答案，然后找距离这个点小于等于二分的值的点有几个，再与 $k$ 作比较即可。

具体的，此问题被转化为二维数点，发现没有修改操作，主席树预处理即可。

代码是比较好写的。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=1e5+5,V=3e5+5;
struct Tree{int ls,rs,data;}t[V<<9];
int cnt;
int root[V<<2];
void change(int&x,int y,int l,int r,int d){
	x=++cnt;t[x]=t[y];t[x].data++;if(l==r)return;
	int mid=l+r>>1;
	if(mid>=d)change(t[x].ls,t[y].ls,l,mid,d);
	else change(t[x].rs,t[y].rs,mid+1,r,d);
}
int query(int x,int y,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[x].data-t[y].data;
	int mid=l+r>>1,res=0;
	if(mid>=L)res=query(t[x].ls,t[y].ls,l,mid,L,R);
	if(mid<R)res+=query(t[x].rs,t[y].rs,mid+1,r,L,R);
	return res;
}
inline bool check(int L,int R,int L1,int R1,int k){
	R=min(R,2*V-1);L=max(L,0);
	return query(root[R+1],root[L],-V,V,L1,R1)>=k;
}
vector<int>v[V<<1];
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		int a=x+y,b=x-y;
		v[a+1].push_back(b);
	}
	for(int i=1;i<=V*2;i++){
		root[i]=root[i-1];
		for(int j=0;j<v[i].size();j++)
			change(root[i],root[i],-V,V,v[i][j]);
	}
	int q=read();
	while(q--){
		int xx=read(),yy=read(),k=read();
		int x=xx+yy,y=xx-yy;
		int l=0,r=V,mid=0,res=0;
		while(l<=r){
			mid=l+r>>1;
			if(check(x-mid,x+mid,y-mid,y+mid,k))res=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",res);
	}
	return 0;
}
```

---

## 作者：Mu_leaf (赞：0)

## [思路]
一个显然的思路是，根据单调性，考虑二分距离，求与询问点的距离小于二分值的个数。

但是可以发现曼哈顿距离需要用到 $x$ 坐标和 $y$ 坐标，很难维护。考虑将曼哈顿距离换成切比雪夫距离，这样两点之间的距离可以表示为 $\max(|x_1-x_2|,|y_1-y_2|)$。

剩下的就很好做了，考虑以 $(x+y,x-y)$ 中心的一个边长为 $2\times mid$ 的正方形内的点数量，$mid$ 是二分的距离。

显然变成了模板二位数点，主席树维护就完了。

## Code:
```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (son[x][0])
#define rs (son[x][1])
#define mid ((l+r)>>1)
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>
	void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T,typename ...Args>
	void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>
	void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>
	void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int N=2e5+5,V=1e5;
int n,m,root[N*100],tr[N*100],son[N*100][2],cnt;
vector<int> p[N<<2];
int change(int x,int l,int r,int v){
    tr[++cnt]=tr[x];son[cnt][0]=son[x][0],son[cnt][1]=son[x][1];
    x=cnt;
    if(l==r) {
        // cout << x << "\n";
        tr[x]++;
        return x;
    }
    if(v<=mid) son[x][0]=change(son[x][0],l,mid,v);
    else son[x][1]=change(son[x][1],mid+1,r,v);
    tr[x]=tr[son[x][0]]+tr[son[x][1]];
    return x;
}
int query(int p1,int p2,int l,int r,int lt,int rt){
    if(l>=lt && r<=rt){
        // cout << p1 << " " << p2 << "\n";
        // cout << tr[p1] << " " << tr[p2] << "\n";
        // puts("-------QAQ--------");
        return tr[p2]-tr[p1];
    }
    int ans=0;
    if(lt<=mid) ans+=query(son[p1][0],son[p2][0],l,mid,lt,rt);
    if(rt> mid) ans+=query(son[p1][1],son[p2][1],mid+1,r,lt,rt);
    return ans;
}
signed main(){
    read(n);
    for(int i=1,x,y;i<=n;i++){
        read(x),read(y);
        p[x+y+1].push_back(x-y);
    }
    for(int i=1;i<=N*2;i++){
        root[i]=root[i-1];
        for(auto v:p[i]) root[i]=change(root[i],-N,N,v);
    }
    
    read(m);
    while(m--){
        int a,b,x,y,k;
        read(a),read(b),read(k);
        x=a+b,y=a-b;
        int l=0,r=N,res=-1;
        while(l<=r){
            int dis=l+r>>1;
            int tmp=query(root[max(0ll,x-dis)],root[min(N*2,x+dis+1)],-N,N,y-dis,y+dis);
            // cout << tmp << " " << dis << "\n";
            if(tmp>=k) res=dis,r=dis-1;
            else l=dis+1;
        }
        write(res);putch('\n');
    }
	flush();
	return 0 ; 
}
```

---

