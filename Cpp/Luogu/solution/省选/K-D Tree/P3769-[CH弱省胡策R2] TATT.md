# [CH弱省胡策R2] TATT

## 题目描述

四维空间真是美妙。现在有 $n$ 个四维空间中的点，请求出一条最长的路径，满足任意一维坐标都是单调不降的。

注意路径起点是任意选择的，并且路径与输入顺序无关（路径顺序不一定要满足在输入中是升序）。

**路径的长度是经过的点的数量，任意点只能经过一次。**

## 说明/提示

记 $m_i=\max(|a_i|,|b_i|,|c_i|,|d_i|),m=\max(m_i)$
|  测试点编号| $n\le$ | $m\le$ | 特殊说明 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $2000$ | $10^9$ |  |
| $2$ |$5\times 10^4$  | $8$ |  |
| $3\sim 4$ | $5\times 10^4$ | $10^5$ |  所有点的第三，四维坐标相同|
| $5\sim 6$| $5\times 10^4$ | $10^5$ |  所有点的第四维坐标相同 |
| $7\sim 8$ | $5\times 10^4$ |$100$  |  |
|  $9\sim 10$| $5\times 10^4$ | $10^9$ |  |

## 样例 #1

### 输入

```
4
2 3 33 2333
2 3 33 2333
2 3 33 2333
2 3 33 2333
```

### 输出

```
4
```

# 题解

## 作者：EnofTaiPeople (赞：27)

不论是听说还是看题，都让我们知道这是一道四维偏序问题，许多人的做法都是 CDQ 套 CDQ 的 $O(n\log_2^3n)$ 和 三维 K-D Tree 的 $O(n^\frac{5}{3})$，如果不是这题数据比较随机，一旦出题人把你卡满，就危险了，反正我不敢用三维 K-D Tree，于是想了一个神奇的时间 $O(n^\frac{3}{2})$，空间 $n\log_2n$ 的做法。

第一步是大家都要做的，通过将 $a$ 维排序将静态四维偏序转换成动态三维偏序，接下来，将编号按 $b$ 维排序，此处相同的不应去重，而应按编号继续比较；然后，使用树状数组套二维 K-D Tree，先建树，每次得到答案后在树上修改即可：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5e4+4,M=1e6+6;
char buf[M+5],*p1,*p2,c;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,M,stdin),p1==p2)?EOF:*p1++)
inline int read(){
    int x;for(c=gc;c<'!';c=gc);
    for(x=0;c>'!';x=x*10+(48^c),c=gc);
    return x;
}
int lx[M],rx[M],ly[M],ry[M],mx[M],my[M],xa[M],ma[M];
int t[M][2],cnt,nrb,nt,lz[M];
int cnt1,cnt2;
struct Tp{int x,y;}a[N];
char now;
inline bool operator<(const Tp &x,const Tp &y){
    return now?x.x<y.x:x.y<y.y;
}
#define ls t[x][0]
#define rs t[x][1]
#define Max(x,y) if(x<y)x=y
#define Min(x,y) if(x>y)x=y
int build(int l,int r){
    int x=++cnt,md=l+r>>1,i;now^=1;
    nth_element(a+l,a+md,a+r+1);
    lx[x]=rx[x]=mx[x]=a[md].x;
    ly[x]=ry[x]=my[x]=a[md].y;
    if(l<md){
        ls=build(l,md-1);Min(lx[x],lx[ls]);
        Min(ly[x],ly[ls]);Max(rx[x],rx[ls]);
        Max(ry[x],ry[ls]);
    }
    if(md<r){
        rs=build(md+1,r);Min(lx[x],lx[rs]);
        Min(ly[x],ly[rs]);Max(rx[x],rx[rs]);
        Max(ry[x],ry[rs]);
    }
    return x;
}
inline bool ck(int x){
    return x&&lx[x]<=mx[0]&&ly[x]<=my[0]&&xa[x]>ma[0];
}
inline bool ck2(int x){
    return x&&lx[x]<=mx[0]&&rx[x]>=mx[0]&&ly[x]<=my[0]&&ry[x]>=my[0];
}
inline void pd(int x){
    Max(ma[x],lz[x]);
    if(ls){Max(lz[ls],lz[x]);Max(xa[ls],lz[ls]);}
    if(rs){Max(lz[rs],lz[x]);Max(xa[rs],lz[rs]);}
    lz[x]=0;
}
void ask(int x){
    if(lz[x])pd(x);
    if(rx[x]<=mx[0]&&ry[x]<=my[0]){
        Max(ma[0],xa[x]);return;
    }if(mx[x]<=mx[0]&&my[x]<=my[0])
        Max(ma[0],ma[x]);
    if(ck(ls))ask(ls);
    if(ck(rs))ask(rs);
}
void cg(int x){
    if(lx[x]==mx[0]&&rx[x]==mx[0]&&ly[x]==my[0]&&ry[x]==my[0]){
        Max(lz[x],ma[0]);Max(xa[x],lz[x]);
    }else{
        if(mx[x]==mx[0]&&my[x]==my[0]){
            Max(ma[x],ma[0]);Max(xa[x],ma[x]);
        }if(ck2(ls)){cg(ls);Max(xa[x],xa[ls]);}
        if(ck2(rs)){cg(rs);Max(xa[x],xa[rs]);}
    }
}
struct kdt{
    int rt;
    inline int qry(int x,int y){
        mx[0]=x,my[0]=y,ma[0]=0;
        if(ck(rt))ask(rt);
        return ma[0];
    }
    inline void add(int x,int y,int d){
        mx[0]=x,my[0]=y,ma[0]=d;
        if(ck2(rt))cg(rt);
    }
}tr[N];
int n,bI[N],rk[N],mt,ans[N];
struct Dat{int a[4];}d[N];
int main(){
    int i,j,x;
    for(n=read(),i=1;i<=n;++i)
        d[bI[i]=i]={{read(),read(),read(),read()}};
    stable_sort(d+1,d+n+1,[&](Dat x,Dat y){
        for(i=0;i<4;++i)
            if(x.a[i]!=y.a[i])return x.a[i]<y.a[i];
        return false;
    });
    stable_sort(bI+1,bI+n+1,[&](int x,int y){
        return d[x].a[1]==d[y].a[1]?x<y:d[x].a[1]<d[y].a[1];
    });
    for(i=1;i<=n;++i)rk[bI[i]]=i;
    for(i=1;i<=n;++i){
        nt=i&-i;
        for(j=1;j<=nt;++j){
            x=bI[i-j+1];
            a[j]={d[x].a[2],d[x].a[3]};
        }
        tr[i].rt=build(1,nt);
    }
    for(i=1;i<=n;++i){
        for(j=rk[i];j;j-=j&-j)
            ans[i]=max(ans[i],tr[j].qry(d[i].a[2],d[i].a[3]));
        ans[0]=max(ans[0],++ans[i]);
        for(j=rk[i];j<=n;j+=j&-j)
            tr[j].add(d[i].a[2],d[i].a[3],ans[i]);
    }
    printf("%d\n",ans[0]);
    return 0;
}
```
空间复杂度很好理解，为什么时间复杂度是 $O(n^\frac{3}{2})$ 而不用再加一只 $\log$？

因为树状数组和 K-D Tree 真的很般配！

设 $k=\log_2n$，则单次查询最坏时间为 $\sum_{i\le k}\sqrt{2^i}\le2\sum_{i<=\frac{k}{2}}2^i\le2^{\frac{k}{2}+2}=O(\sqrt{n})$

---

## 作者：年华天地 (赞：15)

### 思路
首先一看，四维偏序的裸题，怎么做呢？三维偏序是排序处理第一维，cdq处理第二维，数据结构处理最后一维，那么四维呢？我们可以用cdq套cdq来处理第二维和第三维。

### 具体实现

三维偏序的CDQ本质就是把每个$(x,y,z)(x,y,z)$ 转化若干为 $(0,y,z)(0,y,z)$ 对 $(1,y,z)(1,y,z)$ 的贡献。剩下的就是个经典二维偏序问题。

四维偏序中珂以沿用三维偏序中的思路。

把若干 $(x,y,z,w)$分成$ (0/1,0/1,z,w))$，然后计算 $(0,0,z,w) $对 $(1,1,z,w)$的贡献。

——by Froggy

那么我们在第一层CDQ的时候把$[l,mid]$区间内的数打上一个标记，表示他们的第一维是1，在第二层CDQ的时候计算[l,mid]中标记为1的数对[mid+1,r]中标记为0的数的贡献就好了。


### 注意

- 在CDQ时我们必须先递归计算左区间，算完左区间对右区间的贡献后在递归计算右区间，不然得出的值会变小。

- CDQ的排序一定要注意，特别注意相等的情况。


### 代码

```
#include<cstdio>
#include<algorithm>
#define int long long
#define inf 1e17
using namespace std;
const int N=1e6;
int n,tm[N],top=1,pos1[N],t[N],ans[N],res,pos2[N];
struct node{
	int ok,a,b,c,d,w,id,ans;
}s[N],tmp[N];
inline void read(int &x)
{
	x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if (c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	x=f?x:-x;
}
inline bool cmp1(const node&A,const node&B) {return A.a==B.a?(A.b==B.b?(A.c==B.c?A.d<B.d:A.c<B.c):A.b<B.b):A.a<B.a;}
inline bool cmp2(const node&A,const node&B) {return A.b==B.b?(A.a==B.a?(A.c==B.c?A.d<B.d:A.c<B.c):A.a<B.a):A.b<B.b;}
inline bool cmp3(const node&A,const node&B) {return A.c<B.c;}
void add(int x,int p){for (int i=x;i<=n;i+=i&-i)t[i]=max(t[i],p);}
void del(int x){for (int i=x;i<=n;i+=i&-i)t[i]=0;}
int ask(int x)
{
	int ans=0;
	for (int i=x;i;i-=i&-i)ans=max(ans,t[i]);
	return ans;
}
void cdq2(int l,int r)
{
	if (l==r)return ;
	int mid=l+r>>1,L=l;
	cdq2(l,mid);
	sort(s+l,s+mid+1,cmp3);
	sort(s+mid+1,s+r+1,cmp3);
	for (int i=mid+1;i<=r;++i)
	{
		while(s[L].c<=s[i].c&&L<=mid)
		{
			if (s[L].ok)add(s[L].d,s[L].ans);
			L++;	
		}
		if (!s[i].ok)
			s[i].ans=max(ask(s[i].d)+s[i].w,s[i].ans);
	}
	for (int i=l;i<L;++i)if (s[i].ok)del(s[i].d);
	for (int i=l;i<=r;++i)tmp[pos2[s[i].id]]=s[i];
	for (int i=l;i<=r;++i)s[i]=tmp[i];
	cdq2(mid+1,r);
}
void cdq1(int l,int r)//第二维 
{
	if (l==r)return ;
	int mid=l+r>>1;
	cdq1(l,mid);
	for (int i=l;i<=mid;++i)s[i].ok=1;
	for (int i=mid+1;i<=r;++i)s[i].ok=0;
	sort(s+l,s+r+1,cmp2);
	for (int i=l;i<=r;++i)pos2[s[i].id]=i;
	cdq2(l,r);
	for (int i=l;i<=r;++i)tmp[pos1[s[i].id]]=s[i];
	for (int i=l;i<=r;++i)s[i]=tmp[i];
	cdq1(mid+1,r);
}
signed main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	scanf("%lld",&n);
	for (int i=1,a,b,c,d;i<=n;++i)
	{
		read(a),read(b),read(c),read(d);
		s[i]=(node){0,a,b,c,d,1};
		tm[i]=d;	
	}
	sort(tm+1,tm+n+1);
	int num=unique(tm+1,tm+n+1)-tm-1;//去重
	for (int i=1;i<=n;++i)s[i].d=lower_bound(tm+1,tm+num+1,s[i].d)-tm;//对第四位离散化，树状数组插值 
	sort(s+1,s+n+1,cmp1);//按第一维排序 
	for (int i=2;i<=n;++i)
	{
		if(s[i].a!=s[i-1].a||s[i].b!=s[i-1].b||s[i].c!=s[i-1].c||s[i].d!=s[i-1].d)s[++top]=s[i];//去重 
		else s[top].w+=s[i].w;
	}
	for (int i=1;i<=top;++i)s[i].id=i,s[i].ans=s[i].w,pos1[s[i].id]=i;
	cdq1(1,top);
	for (int i=1;i<=n;++i)res=max(res,s[i].ans);
	printf("%lld",res);
	return 0;
}
```

---

## 作者：hs_black (赞：11)


做kd-tree题找到了这道题 顺便推销[blog](https://www.cnblogs.com/Hs-black/p/12382450.html)

---

这题是四维意义下的最长上升子序列, 但如果将第一维排序就变成三维问题了, kd-tree时间复杂度应该会更优

总而言之就是
$$
dp_i = \max_{x_j\le x_i,y_j\le y_i,z_j \le z_i} dp_j + 1
$$
从前向后扫, 找到三维都比它小的dp值最大的点, 找点可以用kd-tree来优化

可以采用以下技巧和剪枝:

* 如果当前子树dp最大值小于等于当前已搜出的最优答案直接返回即可肯定不会更新了
* 如果当前子树的点都在范围内, 直接拿最大值更新答案返回
* 如果当前子树有一维的最小值超过了范围, 那么代表着这个子树中无一满足条件, 直接返回即可
* 每次插入不用替罪羊思想重构, 可以直接提前把树建出来, 初始dp值都设为零, 加入操作相当于激活一个点, 具体就是像线段树那样从上向下搜到那个点, 返回时一路更新就行了

有了以上剪枝, 足够通过此题

[这里有一些数据可能对你有用](http://noi-test.zzstep.com/contest/Round/TATT/testCase/19001) 可以修改url找到其他数据 从18998到19003

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define I inline
#define ll long long
using namespace std;

template <typename T>
void read(T &x) {
    x = 0; bool f = 0;
    char c = getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=1;
    for (;isdigit(c);c=getchar()) x=x*10+(c^48);
    if (f) x=-x;
}

const int N = 200500;
struct node {
	int d[4];
	bool operator < (const node &k) const {
		for (int i = 0;i < 4; i++) 
			if (d[i] != k.d[i]) return d[i] < k.d[i];
		return 0;
	}
}p[N];

int g[N], k;

I bool cmp(int a, int b) {
	return p[a].d[k] < p[b].d[k];
}

#define ls son[x][0]
#define rs son[x][1]

int son[N][2];
int mx[N][3], mn[N][3], mxa[N], res[N], ans;
I void Mn(int &x, int y) { if (x > y) x = y; }
I void Mx(int &x, int y) { if (x < y) x = y; }

I void maintain(int x) {
	for (int i = 0;i <= 2; i++) {
		mx[x][i] = mn[x][i] = p[x].d[i+1];
		if (ls) Mx(mx[x][i], mx[ls][i]), Mn(mn[x][i], mn[ls][i]);
		if (rs) Mx(mx[x][i], mx[rs][i]), Mn(mn[x][i], mn[rs][i]);
	}
}
int build(int l, int r, int d) {
	if (l > r) return 0;
	int mid = (l + r) >> 1;
	k = d + 1, nth_element(g + l, g + mid, g + r + 1, cmp);
	son[g[mid]][0] = build(l, mid - 1, (d + 1) % 3);
	son[g[mid]][1] = build(mid + 1, r, (d + 1) % 3);
	maintain(g[mid]); return g[mid];
}

int tmp;

// 判断x点是否在y点范围以内 
inline bool in(int *x, int *y) {
	int cnt = 0;
	for (int i = 0;i < 3; i++) cnt += (x[i] <= y[i]);
	return cnt == 3;
}

void query(int x, int y) {
	if (mxa[x] <= tmp) return;
	if (!in(mn[x], p[y].d + 1)) return;
	if (in(mx[x], p[y].d + 1)) return tmp = mxa[x], void();
	if (in(p[x].d + 1, p[y].d + 1)) Mx(tmp, res[x]);
	if (ls) query(ls, y); if (rs) query(rs, y);
}

// 激活操作 
void upit(int x, int y) {
	if (x == y) {
		res[x] = tmp, Mx(mxa[x], res[x]); return;
	}
	if (!in(p[y].d + 1, mx[x]) || !in(mn[x], p[y].d + 1)) return;
	// 如果y点不在里面就返回 
	if (ls) upit(ls, y); if (rs) upit(rs, y);
	Mx(mxa[x], mxa[ls]), Mx(mxa[x], mxa[rs]);
}

int rt, n;
int main() {
	freopen ("hs.in","r",stdin);
	read(n);
	for (int i = 1;i <= n; i++) {
		read(p[i].d[0]), read(p[i].d[1]);
		read(p[i].d[2]), read(p[i].d[3]);
		g[i] = i;
	}
	sort(p + 1, p + n + 1); rt = build(1, n, 0);
	for (int i = 1;i <= n; i++) 
		tmp = 0, query(rt, i), tmp++, upit(rt, i), Mx(ans, tmp);
	cout << ans << endl;
	return 0;
}

```



---

## 作者：zcysky (赞：11)

谈一下蒟蒻的做法……

考场上我不会写三维的K-D-Tree,于是就写了个四维的，但由于复杂度的问题四维K-D-Tree肯定要gg……

先看这题，裸题，就是要求四维偏序。

对第一维排序，排序完了之后我们就在三维里面查找符合要求（即在符合要求的空间范围内的点）。

然而我并不是讲的怎么做，我们发现每一层对于相应的维度，在KD树上有类似于BST的性质，然而对于二叉树，我们肯定是希望这棵树越平衡越好。

考虑我们常用的两个平衡树——Splay，Treap（旋转式）

很显然KD树在区间划分上有类似于线段树的性质，我们不能把KD树随便乱转，否则层数和维度的对应关系会遭到破坏

所以我们必须考虑一种不旋转的平衡树。作为无实力选手我可能只会替罪羊树。

对于替罪羊树，我们的做法很咸鱼（非常符合咸鱼选手zcy的个性），就是当我们发现哪里不太平衡了，就把它暴力地拍扁重建（zcy很喜欢这个名字）

具体的实现也简单得很。

```cpp
#include<bits/stdc++.h>
#define N 50010
#define inf 1000000009
#define lson (t1[o].l)
#define rson (t1[o].r)
using namespace std;
typedef long long ll;
int n,m,q[N],rt,dis,top=0;int tot=0,F;
inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}int ans=0;
struct Point{
    int d[4],maxv[4],minv[4],l,r,f,size,v,ma;
    inline int& operator [] (int x){return d[x];}
    inline int in(){for(int i=0;i<4;i++)d[i]=read();}
}t1[N],t2[N],it;
bool cmp(int a,int b){return t1[a][F]<t2[b][F];}
bool operator < (Point a,Point b){
    for(int i=0;i<=3;i++){
        if(a.d[i]<b.d[i])return 1;
        if(a.d[i]>b.d[i])return 0;
    }
    return 0;
}
inline void pushup(int o){
    for(int i=0;i<=3;i++){
        t1[o].minv[i]=min(t1[o].d[i],min(t1[lson].minv[i],t1[rson].minv[i]));
        t1[o].maxv[i]=max(t1[o].d[i],max(t1[lson].maxv[i],t1[rson].maxv[i]));
    }
    t1[o].ma=max(t1[o].v,max(t1[lson].ma,t1[rson].ma));
    t1[o].size=t1[lson].size+t1[rson].size+1;
}
    int build(int l,int r,int f){
        int mid=(l+r)>>1;F=f;
        nth_element(q+l,q+mid,q+r+1,cmp);
        int o=q[mid];t1[o].f=f;lson=0;rson=0;
        if(l<mid)lson=build(l,mid-1,(f+1)%4);
        if(r>mid)rson=build(mid+1,r,(f+1)%4);
        pushup(o);return o;
    }
    void dfs(int o){
        if(!o)return;q[++top]=o;
        dfs(lson);dfs(rson);
    }
    void rebuild(int &o){
        top=0;dfs(o);
        o=build(1,top,t1[o].f);
    }
    inline int newnode(int f){
        int o=++tot;t1[tot].f=f;t1[o]=it;
        for(int i=0;i<=3;i++)t1[o].minv[i]=t1[o].maxv[i]=t1[o][i];
        t1[o].ma=t1[o].v;t1[o].size=1;
        return o;
    }
    void ins(int &o,int f){
        if(!o){o=newnode(f);return;}
        if(t1[o][f]<it[f]){
            ins(lson,(f+1)%4);
            pushup(o);
            if(t1[lson].size>t1[o].size*0.75)rebuild(o);
        }
        else{
            ins(rson,(f+1)%4);
            pushup(o);
            if(t1[rson].size>t1[o].size*0.75)rebuild(o);
        }
    }
    inline int check(int o){
        if(!o)return 0;int _=0;
        for(int i=0;i<=3;i++)if(t1[o].maxv[i]<=it.d[i])_++;
        if(_==4)return _;
         _=1;
        for(int i=0;i<=3;i++)if(t1[o].minv[i]>it[i])_=0;
        return _;
    }
    inline int calcdis(Point x,Point y){
        for(int i=0;i<=3;i++)if(x[i]>y[i])return 0;
        return x.v;
    }
    void query(int o){
        ans=max(calcdis(t1[o],it),ans);
        int dl=check(lson),dr=check(rson);
        if(dl==4)ans=max(ans,t1[lson].ma);
        else if(dl&&ans<t1[lson].ma)query(lson);
        if(dr==4)ans=max(ans,t1[rson].ma);
        else if(dr&&ans<t1[rson].ma)query(rson);
    }
int main(){
    n=read();
    for(int i=0;i<=3;i++)t1[0].minv[i]=inf,t1[0].maxv[i]=-inf;
    t1[0].ma=-inf;
    for(int i=1;i<=n;i++){
        t2[i].in();t2[i].v=1;
    }
    sort(t2+1,t2+n+1);
    int _=0;
    for(int i=1;i<=n;i++){
        ans=0;it=t2[i];
        query(rt);
        t2[i].v+=ans;it=t2[i];
        _=max(_,t2[i].v);ins(rt,0);
    }
    printf("%d\n",_);
}
```

---

## 作者：bcdmwSjy (赞：10)

这道题让我们求四维偏序，显然有 dp 式：

$$f_i=\max\limits_{a_j\le a_i,b_j\le b_i,c_j\le c_i,d_j\le d_i}f_j+1$$

按照 $a$ 排序后，我们可以使用分治等方法优化它，我们还可以采用三维数据结构进行优化，只需要单点修改，立体查询即可，但是我们发现一个问题，树套树套树有着高达好几个 log 的复杂度，即使有 512 MB 也无法通过，时间上也比较紧张。

于是我们想办法优化这个做法，我们发现动态开点线段树每次修改会新建出 $\log n$ 个点，我们不需要这么多点，所以我们在新建节点时记录一下这个点开到了哪里和记录了哪个数，然后直接返回，在查询时把标记的点算上即可。

一种可能的代码实现（最内层树）：

```cpp
struct Node{
    int ls,rs,idx,maxn,cnt;
};

int cnt;
int rt[3200000];
Node tr[3200000];

void update(int &i,int l,int r,int x,int k){
	if (i==0){
		i=++cnt;
		tr[i].idx=x;
		tr[i].cnt=tr[i].maxn=k;
		return;
	}
	tr[i].maxn=max(tr[i].maxn,k);
	if (tr[i].idx==x){
		tr[i].cnt=max(tr[i].cnt,k);
		return;
	}
	if (l==r) return;
	int mid=(l+r)>>1;
	if (mid>=x) update(tr[i].ls,l,mid,x,k);
	else update(tr[i].rs,mid+1,r,x,k);
}

int query(int i,int l,int r,int ql,int qr){
	if (i==0) return 0;
	if (l>=ql and r<=qr) return tr[i].maxn;
	int mid=(l+r)>>1,ans=0;
	if (ql<=tr[i].idx and tr[i].idx<=qr) ans=tr[i].cnt;
	if (mid>=ql) ans=max(ans,query(tr[i].ls,l,mid,ql,qr));
	if (mid+1<=qr) ans=max(ans,query(tr[i].rs,mid+1,r,ql,qr));
	return ans;
}
```

其中 `idx` 记录这个区间内新建点的下标，`cnt` 记录这个点的贡献，`maxn` 是正常的区间最大值。

但是，有了这个优化后还是不能通过，我们发现不仅最内层树可以这样做，中间的动态开点线段树也可以用同样的操作，用两个线段树分别记录 `cnt` 和 `maxn`。

这样，我们就可以轻松在只用 64 MB，最大点 515ms 的情况下通过这道题了。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg{
	struct Node{
		int ls,rs,idx,maxn,cnt;
	};

	int cnt;
	int rt[3200000];
	Node tr[3200000];

	void update(int &i,int l,int r,int x,int k){
		if (i==0){
			i=++cnt;
			tr[i].idx=x;
			tr[i].cnt=tr[i].maxn=k;
			return;
		}
		tr[i].maxn=max(tr[i].maxn,k);
		if (tr[i].idx==x){
			tr[i].cnt=max(tr[i].cnt,k);
			return;
		}
		if (l==r) return;
		int mid=(l+r)>>1;
		if (mid>=x) update(tr[i].ls,l,mid,x,k);
		else update(tr[i].rs,mid+1,r,x,k);
	}

	int query(int i,int l,int r,int ql,int qr){
		if (i==0) return 0;
		if (l>=ql and r<=qr) return tr[i].maxn;
		int mid=(l+r)>>1,ans=0;
		if (ql<=tr[i].idx and tr[i].idx<=qr) ans=tr[i].cnt;
		if (mid>=ql) ans=max(ans,query(tr[i].ls,l,mid,ql,qr));
		if (mid+1<=qr) ans=max(ans,query(tr[i].rs,mid+1,r,ql,qr));
		return ans;
	}
}segin1,segin2;

struct Node{
	int ls,rs,idx;
};

struct Point{
	int a,b,c,d;
};

int n,rt[150001],b[150001],cnt,tot;
Node tr[3200000];
Point a[50001];
int f[50001];

void update(int &i,int l,int r,int x,int y,int k){
	if (i==0){
		i=++cnt;
		tr[i].idx=x;
		segin1.update(segin1.rt[i],1,tot,y,k);
		segin2.update(segin2.rt[i],1,tot,y,k);
		return;
	}
	segin1.update(segin1.rt[i],1,tot,y,k);
	if (tr[i].idx==x){
		segin2.update(segin2.rt[i],1,tot,y,k);
		return;
	}
	if (l==r) return;
	int mid=(l+r)>>1;
	if (mid>=x) update(tr[i].ls,l,mid,x,y,k);
	else update(tr[i].rs,mid+1,r,x,y,k);
}

int query(int i,int l,int r,int ql,int qr,int qlin,int qrin){
	if (i==0) return 0;
	if (l>=ql and r<=qr) return segin1.query(segin1.rt[i],1,tot,qlin,qrin);
	int mid=(l+r)>>1,ans=0;
	if (ql<=tr[i].idx and tr[i].idx<=qr) ans=segin2.query(segin2.rt[i],1,tot,qlin,qrin);
	if (mid>=ql) ans=max(ans,query(tr[i].ls,l,mid,ql,qr,qlin,qrin));
	if (mid+1<=qr) ans=max(ans,query(tr[i].rs,mid+1,r,ql,qr,qlin,qrin));
	return ans;
}

inline int lowbit(int x){
	return x&(-x);
}

void add(int x,int y,int z,int c){
	for (;x<=tot;x+=lowbit(x)) update(rt[x],1,tot,y,z,c);
}

int query(int x,int y,int z){
	int ans=0;
	for (;x;x-=lowbit(x)) ans=max(ans,query(rt[x],1,tot,1,y,1,z));
	return ans;
}

bool cmp(Point a,Point b){
	if (a.a==b.a){
		if (a.b==b.b){
			if (a.c==b.c){
				return a.d<b.d;
			}
			return a.c<b.c;
		}
		return a.b<b.b;
	}
	return a.a<b.a;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b>>a[i].c>>a[i].d;
		b[++tot]=a[i].b;
		b[++tot]=a[i].c;
		b[++tot]=a[i].d;
	}
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for (int i=1;i<=n;i++){
		a[i].b=lower_bound(b+1,b+tot+1,a[i].b)-b;
		a[i].c=lower_bound(b+1,b+tot+1,a[i].c)-b;
		a[i].d=lower_bound(b+1,b+tot+1,a[i].d)-b;
	}
	for (int i=1;i<=n;i++){
		f[i]=query(a[i].b,a[i].c,a[i].d)+1;
		add(a[i].b,a[i].c,a[i].d,f[i]);
	}
	cout<<*max_element(f+1,f+n+1);
	return 0;
}
```

---

## 作者：dengjunhaodejia09 (赞：10)

一个单根复杂度，空间线性的做法，以下默认块长为 $\sqrt{n}$ 。

考虑对点按 $a$ 为第一关键字排序后分块，对于每个块单独考虑。

思路即是每次考虑到了一个块，就把前缀块按 $b$ 为第一关键字排序，把当前块也按 $b$ 为第一关键字排序。然后扫描线，一个个考虑当前块的元素，将前缀块中 $b\leq $ 当前元素 $b$ 的 $c$ ， $d$ 塞进二维值域分块中，再对当前块的点查询 $c$ 比他小的且 $d$ 比他小的数的 $dp$ 的最大值即可。

发现一个惊人的事实，前缀块的 $c$ 与 $d$ 中可以对当前块的 $c$ 与 $d$ 相对大小关系离散化，这样值域范围就是单根，二维值域分块即是插入 $O(1)$ ，查询 $O(\sqrt[4]{n} \cdot \sqrt[4]{n})=O(\sqrt{n})$。因为做了 $\sqrt{n}$ 次扫描线，每次 $n$ 次插入，复杂度 $O(n\sqrt{n})$。共有 $n$ 次查询，每次 $O(\sqrt{n})$ ，复杂度 $O(n\sqrt{n})$ 。

对于块内的转移直接暴力即可，每个点至多从块中的 $\sqrt{n}$ 个元素转移，复杂度为 $O(n\sqrt{n})$ 。

对于离散化，先对于块内排序，复杂度为均摊整体为 $O(n\log_{2}{n})$ 。再对前缀块已经排好序的数列归并排序，只有 $\sqrt{n}$ 次，单次 $O(n)$ ，复杂度为 $O(n\sqrt{n})$ 。

总结一下，我们得出了复杂度单根，空间 $O(n)$ 的做法，我们因为发现前缀块的点能对当前块离散化而提出了此解法，可惜我自己实现的常数较大，如果有人有小常数解法，欢迎与我交流。

后来与其他人交流后发现有多种方法可以做到此复杂度，并且可能更好写或常数更小，但或许我这个方法也有自己的意义，就分享出来了。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int B=256,mb=16;
int mBid[B+10];
struct node{
    int fen[mb+2][mb+2],a[B+10][B+10],fen1[mb+2][B+10],fen2[B+10][mb+2];
    void Clear(){
        memset(fen,0,sizeof(fen));
        memset(a,0,sizeof(a));
        memset(fen1,0,sizeof(fen1));
        memset(fen2,0,sizeof(fen2));
    }
    void insert(int x,int y,int w){
        a[x][y]=max(a[x][y],w);
        fen1[mBid[x]][y]=max(fen1[mBid[x]][y],w);
        fen2[x][mBid[y]]=max(fen2[x][mBid[y]],w);
        fen[mBid[x]][mBid[y]]=max(fen[mBid[x]][mBid[y]],w);
    }
    int query(int x,int y){
        int Max=0;
        for(int i=x;i>=1;i--){
            if(mBid[i]!=mBid[x]){
                break;
            }
            for(int j=y;j>=1;j--){
                if(mBid[j]!=mBid[y]){
                    break;
                }
                Max=max(Max,a[i][j]);
            }
            for(int j=mBid[y]-1;j>=1;j--){
                Max=max(Max,fen2[i][j]);
            }
        }
        for(int j=y;j>=1;j--){
            if(mBid[j]!=mBid[y]){
                break;
            }
            for(int i=mBid[x]-1;i>=1;i--){
                Max=max(Max,fen1[i][j]);
            }
        }
        for(int i=mBid[x]-1;i>=1;i--){
            for(int j=mBid[y]-1;j>=1;j--){
                Max=max(Max,fen[i][j]);
            }
        }
        return Max;
    }
}Kuai;
struct nodee{
    int a,b,c,d,dp,W;
}A[50005],C[50005];
vector<int> lsha,lshb,lshc,lshd;
bool cmp(nodee aa,nodee bb){
    if(aa.a==bb.a){
        if(aa.b==bb.b){
            if(aa.c==bb.c){
                return aa.d<bb.d;
            }
            return aa.c<bb.c;
        }
        return aa.b<bb.b;
    }
    return aa.a<bb.a;
}
bool cmpp(nodee aa,nodee bb){
    if(aa.b==bb.b){
        if(aa.c==bb.c){
            if(aa.d==bb.d){
                return aa.a<bb.a;
            }
            return aa.d<bb.d;
        }
        return aa.c<bb.c;
    }
    return aa.b<bb.b;
}
int L[305],R[305],idB[50005],tot;
nodee num_yuan[50005],ti[50005],pai[50005],cun[50005];
bool cmpb(nodee aa,nodee bb){
    return aa.b<bb.b;
}
bool cmpc(nodee aa,nodee bb){
    return aa.c<bb.c;
}
bool cmpd(nodee aa,nodee bb){
    return aa.d<bb.d;
}
int Id_num_c[50005],Id_num_d[50005];
int n;
void chuli_c(int id){
    for(int i=1;i<=tot;i++){
        for(int j=pai[i-1].c+1;j<=pai[i].c;j++){
            Id_num_c[j]=i;
        }
    }
    for(int i=pai[tot].c+1;i<=n;i++){
        Id_num_c[i]=tot+1;
    }
}
void chuli_d(int id){
    for(int i=1;i<=tot;i++){
        for(int j=pai[i-1].d+1;j<=pai[i].d;j++){
            Id_num_d[j]=i;
        }
    }
    for(int i=pai[tot].d+1;i<=n;i++){
        Id_num_d[i]=tot+1;
    }
}
int main(){
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    cin>>n;
    for(int i=1;i<=B;i++){
        mBid[i]=(i-1)/mb+1;
    }
    for(int i=1;i<=n;i++){
        cin>>A[i].a>>A[i].b>>A[i].c>>A[i].d;
        lsha.push_back(A[i].a);
        lshb.push_back(A[i].b);
        lshc.push_back(A[i].c);
        lshd.push_back(A[i].d);
    }
    stable_sort(lsha.begin(),lsha.end());
    stable_sort(lshb.begin(),lshb.end());
    stable_sort(lshc.begin(),lshc.end());
    stable_sort(lshd.begin(),lshd.end());
    for(int i=1;i<=n;i++){
        A[i].a=lower_bound(lsha.begin(),lsha.end(),A[i].a)-lsha.begin()+1;
        A[i].b=lower_bound(lshb.begin(),lshb.end(),A[i].b)-lshb.begin()+1;
        A[i].c=lower_bound(lshc.begin(),lshc.end(),A[i].c)-lshc.begin()+1;
        A[i].d=lower_bound(lshd.begin(),lshd.end(),A[i].d)-lshd.begin()+1;
        A[i].W=1;
    }
    stable_sort(A+1,A+n+1,cmp);
    int N=0;
    for(int i=1;i<=n;i++){
        if(i==1 || A[i].a!=A[i-1].a || A[i].b!=A[i-1].b || A[i].c!=A[i-1].c || A[i].d!=A[i-1].d){
            C[++N]=A[i];
        }else{
            C[N].W++;
        }
    }
    for(int i=1;i<=N;i++){
        A[i]=C[i];
        A[i].dp=A[i].W;
    }
    n=N;
    int Cnt=0;
    for(int i=1;i<=n;i++){
        idB[i]=(i-1)/B+1;
        if(L[idB[i]]==0){
            L[idB[i]]=i;
        }
        R[idB[i]]=i;
        Cnt=(i-1)/B+1;
    }
    int Max=0;
    for(int i=1;i<=Cnt;i++){
        tot=0;
        for(int j=L[i];j<=R[i];j++){
            pai[++tot]=A[j];
            cun[tot]=A[j];
        }
        int cnt_c=0,cnt_d=0;
        stable_sort(pai+1,pai+tot+1,cmpc);
        chuli_c(i);
        int lst=0;
        for(int j=1;j<=tot;j++){
            cnt_c++;
            if(j==1 || pai[j].c!=lst){
                lst=pai[j].c;
                pai[j].c=cnt_c;
            }else{
                lst=pai[j].c;
                pai[j].c=pai[j-1].c;
            }
        }
        stable_sort(pai+1,pai+tot+1,cmpd);
        chuli_d(i);
        lst=0;
        for(int j=1;j<=tot;j++){
            cnt_d++;
            if(j==1 || pai[j].d!=lst){
                lst=pai[j].d;
                pai[j].d=cnt_d;
            }else{
                lst=pai[j].d;
                pai[j].d=pai[j-1].d;
            }
        }
        for(int j=1;j<L[i];j++){
            num_yuan[j].c=Id_num_c[num_yuan[j].c];
            num_yuan[j].d=Id_num_d[num_yuan[j].d];
            // cout<<num_yuan[j].a<<" "<<num_yuan[j].b<<' '<<num_yuan[j].c<<' '<<num_yuan[j].d<<' '<<num_yuan[j].dp<<'\n';
        }
        // cout<<"xiaofenge\n";
        stable_sort(pai+1,pai+tot+1,cmpp);
        stable_sort(cun+1,cun+tot+1,cmpp);
        int idl=1;
        Kuai.Clear();
        for(int j=1;j<=tot;j++){
            while(idl<L[i] && num_yuan[idl].b<=pai[j].b){
                Kuai.insert(num_yuan[idl].c,num_yuan[idl].d,num_yuan[idl].dp);
                idl++;
            }
            cun[j].dp=max(cun[j].dp,cun[j].W+Kuai.query(pai[j].c,pai[j].d));
            // cout<<cun[j].a<<' '<<pai[j].b<<' '<<pai[j].c<<' '<<pai[j].d<<' '<<pai[j].dp<<'\n';
        }
        for(int j=1;j<=tot;j++){
            for(int k=1;k<j;k++){
                if(cun[j].a>=cun[k].a && cun[j].b>=cun[k].b && cun[j].c>=cun[k].c && cun[j].d>=cun[k].d){
                    cun[j].dp=max(cun[j].dp,cun[k].dp+cun[j].W);
                }
            }
        }
        memcpy(num_yuan,ti,sizeof(num_yuan));
        merge(num_yuan+1,num_yuan+L[i],cun+1,cun+tot+1,ti+1,cmpp);
        memcpy(num_yuan,ti,sizeof(num_yuan));
        // cout<<"ZHONGFEN\n";
        // for(int j=1;j<=R[i];j++){
        //     cout<<num_yuan[j].a<<' '<<num_yuan[j].b<<' '<<num_yuan[j].c<<" "<<num_yuan[j].d<<' '<<num_yuan[j].dp<<'\n';
        // }
        // cout<<"Dafenge\n";
    }
    Max=0;
    for(int i=1;i<=n;i++){
        Max=max(Max,num_yuan[i].dp);
    }
    cout<<Max;
    return 0;
}
/*
13
10 5 9 9
12 10 1 13
13 13 6 1
3 7 1 5
9 8 7 8
6 9 4 11
8 1 11 6
5 3 1 10
7 2 12 11
10 5 8 3
2 11 5 2
4 4 12 4
1 11 10 7


*/
```

---

## 作者：zhengrunzhe (赞：10)

提供个排序后转成三维的，快了一倍

不难写出dp方程
```cpp
f[i]=max{f[j]}+1 (a[j]<=a[i],b[j]<=b[i],c[j]<=c[i],d[j]<=d[i])
```
这是个经典的四维偏序问题，先按a升序排序掉一维之后用kdtree实现b,c,d的三维偏序

把(b,c,d)三元组想象成一个三维坐标系内的点，点权是其对应的f值，查询出当前kdtree中在矩形{(-inf,-inf,-inf),(b[i],c[i],d[i])}中的点权最大值+1即是f[i]，再把(b[i],c[i],d[i])带上点权f[i]插入到kdtree中即可

在kdtree中查询时遇到整个子树中的最大值小于等于当前搜到的最大值时就可以剪枝~~(我绝对不会说我一开始没判这个还以为被卡常了交了n遍)~~
```cpp
#include<cstdio>
#include<algorithm>
#define reg register
using std::max;
using std::min;
const int N=5e4+10,INF=1e9+10;
const short K=4;
inline const void read(reg int &in)
{
    in=0;reg char ch=getchar();reg short fh=1;
    while (ch<48||ch>57)fh=ch=='-'?-1:fh,ch=getchar();
    while (ch>47&&ch<58)in=(in<<3)+(in<<1)+ch-48,ch=getchar();
    in*=fh;
}
short f;
int n,ans,flag;
struct point
{
    int d[K],w;
    inline const bool operator<(reg const point &p)const
    {
        if (d[f]^p.d[f])return d[f]<p.d[f];
        for (reg short i=0;i<K-flag;i++)
        	if (d[i]^p.d[i])
        		return d[i]<p.d[i];
        return 0;
    }
}a[N];
template<short K>
class kD_Tree
{
    private:
        const static double alpha=0.75;
        struct tree
        {
            int size,mxw;
            tree *son[2];
            point range,mn,mx;
            inline const void pushup()
            {
               	size=son[0]->size+1+son[1]->size;
                mxw=max(max(son[0]->mxw,son[1]->mxw),range.w);
                for (reg short i=0;i<K;i++)
                    mn.d[i]=min(range.d[i],min(son[0]->mn.d[i],son[1]->mn.d[i])),
                    mx.d[i]=max(range.d[i],max(son[0]->mx.d[i],son[1]->mx.d[i]));
            }
            inline const bool unbalanced()
            {
                return son[0]->size>size*alpha||son[1]->size>size*alpha;
            }
            inline const bool in(reg const point &a,reg const point &b)
            {
                for (reg short i=0;i<K;i++)
                    if (a.d[i]>mn.d[i]||b.d[i]<mx.d[i])
                        return 0;
                return 1;
            }
            inline const bool out(reg const point &a,reg const point &b)
            {
                for (reg short i=0;i<K;i++)
                    if (a.d[i]>mx.d[i]||b.d[i]<mn.d[i])
                        return 1;
                return 0;
            }
            inline const bool at(reg const point &a,reg const point &b)
            {
                for (reg short i=0;i<K;i++)
                    if (range.d[i]<a.d[i]||range.d[i]>b.d[i])
                        return 0;
                return 1;
            }
        }memory_pool[N],*tail,*null,*root,*recycle[N];
        point down;
        int top;
        inline const void init()
        {
            tail=memory_pool;
            null=tail++;
            for (reg short i=0;i<K;i++)
                null->mn.d[i]=INF,
                down.d[i]=null->mx.d[i]=-INF;
            null->son[0]=null->son[1]=null;
            root=null;
        }
        inline tree *spawn(reg const point &x)
        {
            reg tree *p=top?recycle[--top]:tail++;
            p->son[0]=p->son[1]=null;
            p->range=p->mn=p->mx=x;
            p->mxw=x.w;
            p->size=1;
            return p;
        }
        point b[N];int rnk;
        inline const void travel(reg tree *p)
        {
            if (p==null)return;
            travel(p->son[0]);
            b[++rnk]=p->range;
            recycle[top++]=p;
            travel(p->son[1]);
        }
        inline tree *build(reg int l,reg int r,reg short d)
        {
            if (l>r)return null;
            reg int mid=l+r>>1;f=d;
            std::nth_element(b+l,b+mid,b+r+1);
            tree *p=spawn(b[mid]);
            if (l==r)return p;
            p->son[0]=build(l,mid-1,(d+1)%K);
            p->son[1]=build(mid+1,r,(d+1)%K);
            return p->pushup(),p;
        }
        inline const void rebuild(reg tree *&p)
        {
            rnk=0;
            travel(p);
            p=build(1,rnk,0);
        }
        int ans;
        inline const void query(reg tree *p,reg const point &a,reg const point &b)
        {
            if (p==null)return;
            if (p->out(a,b))return;
            if (p->in(a,b))return (void)(ans=max(p->mxw,ans));
            ans=max(ans,p->at(a,b)?p->range.w:0);
           	if (p->son[0]->mxw>ans)query(p->son[0],a,b);
           	if (p->son[1]->mxw>ans)query(p->son[1],a,b);
        }
        inline tree **findbad(reg tree *&p,reg const point &x,reg short d)
        {
            if (p==null)return p=spawn(x),&null;
            tree **bad=findbad(p->son[p->range.d[d]<x.d[d]],x,(d+1)%K);
            p->pushup();
            if (p->unbalanced())bad=&p;
            return bad;
        }
    public:
        inline kD_Tree()
        {
            init();
        }
        inline const int query(reg const point &up)
        {
            ans=0;query(root,down,up);return ans;
        }
    	inline const void insert(reg const point &p)
    	{
            reg tree **bad=findbad(root,p,0);
            if (*bad==null)return;
            rebuild(*bad);
        }
};
kD_Tree<K-1>kdt;
int main()
{
    read(n);
    for (reg int i=1;i<=n;i++)
    	for (reg short j=0;j<K;j++)
        	read(a[i].d[j]);
    std::sort(a+1,a+n+1);flag=1;
    for (reg int i=1;i<=n;i++)
    	for (reg short j=0;j<K-1;j++)
    		a[i].d[j]=a[i].d[j+1];
    for (reg int i=1;i<=n;i++)
        ans=max(ans,a[i].w=kdt.query(a[i])+1),
        kdt.insert(a[i]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：zltttt (赞：6)

写的时候刚学KD-Tree不久......


由于太弱本蒟蒻甚至没有想到排序优化掉一维......现在一想当时简直太zz了......

由于太弱本蒟蒻不会替罪羊树这么高端的东西......这么久过去了咱还是不会......


### **然而以上的东西是完全不需要的。**

直接四维裸KD-Tree即可通过此题。


可以考虑像线段树一样建好一棵空的树，初始给每个节点赋值为0。

建树考虑这么建:在传统的每一层维度不相同的基础上，对于每一个节点取出当前节点管辖区间以当前坐标排序后处于正中间的点作为当前节点，这就能尽可能保持区间大小较为平衡了~


然后给所有点按四维大小排序，每次选择一个点，询问其答案，并修改树中它的权值，这就是常见的DP了。


对于每个节点，可以维护其内部的四维分别的最小坐标（也就是说可以不来自同一个点），用于判断该不该访问~

同时搜完一个儿子后要判断一下另一个儿子值不值得搜再决定是否向下搜。


然后是一个很关键的剪枝:对于修改操作，直接记录每个节点的父亲，并在更新时直接向上更新父亲。

为什么说它重要，可以去看看[咱的博客](http://blog.csdn.net/zlttttt/article/details/72892239)或者听一下口胡:

如果你选择了直接向下寻找节点的话，想象一下如果恰好出现了你要访问的目标节点与当前节点在当前维度的坐标相等的情况。

此时左儿子和右儿子的管辖区间均可能包含你想要的节点，都搜一次会TLE的。

虽然这是可以避免的，然而常数还是比直接记父亲更大.....(这个版本咱的博客上有)


这是咱跑得最快的一份代码：

（如果想看看咱做此题的经历~~错得有多惨~~欢迎围观[本蒟蒻的博客](http://blog.csdn.net/zlttttt/article/details/72892239)）


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>

using namespace std;

const int N=50009;

int main_d;

inline int minn(int a,int b){if(a<b)return a;return b;}
inline int maxx(int a,int b){if(a>b)return a;return b;}
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || '9'<ch){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch && ch<='9'){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

struct point
{
    int coord[4],mn[4],id,l,r,mv,v,f;

    int &operator [](int x)
    {
        return coord[x];
    }
    void init()
    {
        for(int i=0;i<=3;i++)
            mn[i]=coord[i];
        v=mv=f=0;
    }
};

bool operator <(point satori,point koishi)
{
    return satori[main_d]<koishi[main_d];
}
inline bool ecmp(point a,point b)
{
    for(int i=0;i<=3;i++)
        if(a[i]!=b[i])
            return 0;
    return 1;
}
inline bool judge(point satori,point koishi)
{
    for(int i=0;i<=3;i++)
        if(satori[i]>koishi[i])
            return 0;
    return 1;
}
inline bool valid(point satori,point koishi)
{
    for(int i=0;i<=3;i++)
        if(satori.mn[i]>koishi[i])
            return 0;
    return 1;
}

int p[N];
int sumt[5];

struct k_dimensional_tree
{
    int root,maxval;
    point t[N];
    void update(int x)
    {
        for(int i=0;i<=3;i++)
            t[x].mn[i]=minn(t[x].mn[i],minn(t[t[x].l].mn[i],t[t[x].r].mn[i]));
        t[x].mv=maxx(t[x].v,maxx(t[t[x].l].mv,t[t[x].r].mv));
    }
    void push(int x)
    {
        t[x].mv=maxx(t[x].v,maxx(t[t[x].l].mv,t[t[x].r].mv));
    }
    inline int check(int x,point p)
    {
        if(!x)return x;
        int ret=1;
        for(int i=0;i<=3;i++)
            if(p[i]<t[x].mn[i])
                ret=0;
        return ret;
    }
    int biu(int l,int r,int d)
    {
        main_d=d;
        int mid=l+r>>1,nxt;
        nth_element(t+l,t+mid,t+r+1);
        nxt=d+1;
        if(nxt==4)
            nxt=1;
        t[mid].init();
        if(l<mid)
            t[mid].l=biu(l,mid-1,nxt),t[t[mid].l].f=mid;
        if(mid<r)
            t[mid].r=biu(mid+1,r,nxt),t[t[mid].r].f=mid;
        update(mid);
        return mid;
    }
    void query(int x,point p,int d)
    {
        sumt[0]++;
        if(judge(t[x],p) && maxval<t[x].v)
            maxval=t[x].v;

        int nxt=d+1;
        if(nxt==4)
            nxt=1;
        if(p[d]>=t[x][d])
        {
            int a=t[x].l,b=t[x].r;
            if(t[a].mv<t[b].mv)
                swap(a,b);

            if(valid(t[a],p) && t[a].mv>maxval)
                query(a,p,nxt);
            if(valid(t[b],p) && t[b].mv>maxval)
                query(b,p,nxt);
        }
        else
            if(valid(t[t[x].l],p) && t[t[x].l].mv>maxval)
                query(t[x].l,p,nxt);
    }
    void modify(int x,int v)
    {
        t[x].v=v;
        push(x);
        while(x=t[x].f)
            push(x);
    }
}koishi;    
bool pcmp(int a,int b)
{    
    for(int i=0;i<=3;i++)
        if(koishi.t[a][i]!=koishi.t[b][i])
            return koishi.t[a][i]<koishi.t[b][i];
    return 0;
}

int main()
{
    int n=read();
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        for(int j=0;j<=3;j++)
            koishi.t[i][j]=read();
        koishi.t[i].id=i;
    }

    koishi.root=koishi.biu(1,n,1);
    sort(p+1,p+n+1,pcmp);

    for(int i=1;i<=n;i++)
    {
        koishi.maxval=0;
        int o=p[i];
        koishi.query(koishi.root,koishi.t[p[i]],1);
        koishi.modify(p[i],koishi.maxval+1);
    }
    printf("%d\n",koishi.t[koishi.root].mv);
    return 0;
}
```

---

## 作者：CQ_Bab (赞：5)

# 前言

我们可以发现这就是一个四维偏序，那么我们就可以采用 cdq 套 cdq 来解决它，然后这里还有两个双倍经验。

# 思路

我们可以得出一个 $n^2$ dp，用 $f_i=\max(f_j+1)$ 其中的 $j$ 要满足四维不大于 $i$。

首先我们可以一维一维的来考虑。

对于第一维，和三位偏序一样直接排序即可。

```cpp
il bool cmpa(node a,node b) {
	if(a.a!=b.a) return a.a<b.a;
	if(a.b!=b.b) return a.b<b.b;
	if(a.c!=b.c) return a.c<b.c;
	return a.d<b.d;
}
```

然后我们就需要来考虑如何既保证第 $1$ 维有序有保证第 $2$ 维有序，这里我们可以采用一种标记的形式（毕竟我们只需要加上 $l\sim mid$ 到 $mid+1\sim r$ 互相的贡献）所以我们这里将 $l\sim mid$ 标记成一种颜色再将 $mid+1\sim r$ 标记成另一种颜色即可，然后我们在对于第 $2$ 维进行排序再去算第 $3$ 维即可。

```cpp
bool cmpb(node a,node b) {
	if(a.b!=b.b) return a.b<b.b;
	if(a.c!=b.c) return a.c<b.c;
	if(a.d!=b.d) return a.d<b.d;
	return a.a<b.a;
}
void cdq(int l,int r) {
	if(l==r) return ;
	int mid=l+r>>1;
	cdq(l,mid);
	rep(i,l,r) pb[i]=s[i],pb[i].f=(i<=mid?1:2);
	sort(pb+l,pb+r+1,cmpb);
	cdq2(l,r);
	cdq(mid+1,r);
}
```

这里我们按照三位排序的方法处理最后一维（树状数组）然后我们按照三维排序（分为 $l\sim mid$ 和 $mid+1\sim r$ 分别排序，因为需要保证第 $2$ 维的顺序)的方法先将第三维排序再用双指针去看，如果一个在 $l\sim mid$ 的值被标记为了在 $L\sim Mid$(这里表示再上面的标记中标记为了 $1$) 中 ，就将它的贡献加入树状数组，然后如果遍历到了一个 $mid+1\sim r$ 的一个的标记为 $2$ 就可以取最大值，只需要用树状数组处理出最大值即可。

```cpp
void cdq2(int l,int r) {
	if(l==r) return ;
	int mid=l+r>>1;
	cdq2(l,mid);
	rep(i,l,r) pc[i]=pb[i];
	sort(pc+l,pc+1+mid,cmpc);
	sort(pc+mid+1,pc+1+r,cmpc);
	int j=l;
	for(int i=mid+1;i<=r;i++) {
		while(pc[i].c>=pc[j].c&&j<=mid) {
			if(pc[j].f==1) add(pc[j].d,f[pc[j].id]);
			j++;
		}
		if(pc[i].f==2) f[pc[i].id]=max(f[pc[i].id],Ans(pc[i].d)+pc[i].e);
	}
	rep(i,l,j) if(pc[i].f==1) clean(pc[i].d);
	cdq2(mid+1,r);
}
```



# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T;
int n,tot;
const int N=5e4+10,M=2e5+10;
struct node{
	int a,b,c,d,e;
	int f,id;
}p[N],s[N],pb[N],pc[N];
il bool cmpa(node a,node b) {
	if(a.a!=b.a) return a.a<b.a;
	if(a.b!=b.b) return a.b<b.b;
	if(a.c!=b.c) return a.c<b.c;
	return a.d<b.d;
}
bool cmpb(node a,node b) {
	if(a.b!=b.b) return a.b<b.b;
	if(a.c!=b.c) return a.c<b.c;
	if(a.d!=b.d) return a.d<b.d;
	return a.a<b.a;
}
bool cmpc(node a,node b) {
	if(a.c!=b.c) return a.c<b.c;
	if(a.d!=b.d) return a.d<b.d;
	if(a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}
int f[N];
int tr[M];
int idx;
int lowbit(int x) {
	return x&-x;
}
void add(int x,int k) {
	for(;x<=idx;x+=lowbit(x)) tr[x]=max(tr[x],k);
}
int Ans(int x) {
	int res=-INT_MAX;
	for(;x;x-=lowbit(x)) res=max(res,tr[x]);
	return res;
}
void clean(int x) {
	for(;x<=idx;x+=lowbit(x)) tr[x]=-1000100000000000;
}
bool cmp(node a,node b) {
	return a.d<b.d;
}
unordered_map<int,int>mp;
int getd(int x) {
	if(!mp[x]) mp[x]=++idx;
	return mp[x];
}
void cdq2(int l,int r) {
	if(l==r) return ;
	int mid=l+r>>1;
	cdq2(l,mid);
	rep(i,l,r) pc[i]=pb[i];
	sort(pc+l,pc+1+mid,cmpc);
	sort(pc+mid+1,pc+1+r,cmpc);
	int j=l;
	for(int i=mid+1;i<=r;i++) {
		while(pc[i].c>=pc[j].c&&j<=mid) {
			if(pc[j].f==1) add(pc[j].d,f[pc[j].id]);
			j++;
		}
		if(pc[i].f==2) f[pc[i].id]=max(f[pc[i].id],Ans(pc[i].d)+pc[i].e);
	}
	rep(i,l,j) if(pc[i].f==1) clean(pc[i].d);
	cdq2(mid+1,r);
}
void cdq(int l,int r) {
	if(l==r) return ;
	int mid=l+r>>1;
	cdq(l,mid);
	rep(i,l,r) pb[i]=s[i],pb[i].f=(i<=mid?1:2);
	sort(pb+l,pb+r+1,cmpb);
	cdq2(l,r);
	cdq(mid+1,r);
}
void solve() {
	in(n);
	int ans=-INT_MAX;
	rep(i,1,n) cin>>p[i].a>>p[i].b>>p[i].c>>p[i].d,p[i].e=1,ans=max(ans,p[i].e);
	sort(p+1,p+1+n,cmp);
	rep(i,1,n) p[i].d=getd(p[i].d);
	sort(p+1,p+1+n,cmpa);
	int sum=false;
	rep(i,1,n) {
		sum+=p[i].e;
		if(p[i].a!=p[i+1].a||p[i].b!=p[i+1].b||p[i].c!=p[i+1].c||p[i].d!=p[i+1].d) {
			s[++tot]={p[i].a,p[i].b,p[i].c,p[i].d,sum,0,tot};
			sum=false;
		}
	}
	rep(i,1,n) tr[i]=-1000100000000000;
	n=tot;
	rep(i,1,n) f[i]=s[i].e;
	cdq(1,n);
	rep(i,1,n) ans=max(ans,f[i]);
	printf("%lld",ans);
	return;
}
fire main() {
	T=1; 
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：critnos (赞：4)

一个神奇的乱搞。

首先按一个维度排序之后就变成了有三个限制的 LIS，即：

$$f_i=\max f_j[1\le j<i,x_j\le x_i,y_j\le y_i,z_j\le z_i]+1$$

这个东西看起来很难优化，似乎只能用 KDT 或者 CDQ，事实上一开始也确实是这样，我写了一个暴力和三维动态开点 BIT 都 T 飞了。

考虑一种神奇的思路：

每次转移的时候，从小到大遍历 $f$ 数组，也就是把 $f$ 数组动态的从大到小排序，每次遍历一下，然后判断这个 $f_j$ 能否转移，即满足上面的转移条件。如果可以就直接跳出。这个正确性是显然的：第一个满足条件的因为已经从小到大排序所以肯定是最优的。

那么什么 ds 可以动态支持插入和从小到大遍历呢？set 是大多数人最先想到的，但是常数太大了。

vector 是个不错的选择，因为 $n$ 较小，所以可以使用 vector 暴力的 insert 功能。

然后惊险的加了个快读过了，复杂度是 $n^2$ 但是 vector insert 的常数实在太小了。。至于如果用 set 实现的呢？最坏仍然是 $n^2$ 但是期望复杂度就不会证了。。

虽说跑不过 KDT 和 CDQ，但是这东西好写啊！1k 代码长度比 KDT 和 CDQ 的 3，4k 好写多了。

说起来复杂，其实代码挺好实现的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
   int s=0;
   char ch=getchar();
   while(ch<'0'||ch>'9') ch=getchar();
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s;
}
struct node
{
	int x,y,z,p;
}a[100005];
bool cmp(node x,node y)
{
	if(x.x==y.x)
		if(x.y==y.y)
			if(x.z==y.z)
				return x.p<y.p;
			else
				return x.z<y.z;
		else
			return x.y<y.y;
	else
		return x.x<y.x;
}
struct node2
{
	int s,x,y,z;
	friend bool operator <(node2 x,node2 y)
	{
		return x.s>y.s;
	}
	node2(){}
	node2(int S,int X,int Y,int Z)
	{
		s=S,x=X,y=Y,z=Z;
	}
};
set<node2> p;
int main()
{
	set<node2>::iterator it;
	int n=read(),i,j,s,mx=0,ans;
	for(i=0;i<n;i++)
		a[i].x=read(),a[i].y=read(),a[i].z=read(),a[i].p=read();
	sort(a,a+n,cmp);
	p.insert(node2(0,-1e9,-1e9,-1e9));
	for(i=0;i<n;i++)
	{
		for(it=p.begin();a[i].y<it->x||a[i].z<it->y||a[i].p<it->z;j++);
		ans=it->s+1;
		mx=max(mx,ans);
		p.insert(node2(ans,a[i].y,a[i].z,a[i].p));
	}
	cout<<mx;
}
```


---

## 作者：shinkuu (赞：4)

四维偏序板子题怎么只有一篇 cdq 题解呢/yiw

首先简单介绍一下 cdq 套 cdq 的思路。我们知道 cdq 的递归树可以理解成一棵线段树。cdq 的过程就是递归到叶子，再回溯回来。而 cdq 套 cdq 的过程则可以如此理解：

- 在第一层递归中到达点 $x$。

- 从 $x$ 进入第二层递归。

- 处理当前贡献。

- 在第二层递归中遍历 $x$ 的子树。

- 回溯，返回第一层递归。

- 在第一层递归中遍历 $x$ 的子树。

- 回溯。

并且，cdq 的本质是使若干个 $(0,b,c)$ 的对向 $(1,b,c)$ 做贡献。而在 cdq 套 cdq 中，则变成了 $(0,0,c,d)$ 向 $(1,1,c,d)$。其中第一维在第一层 cdq 中处理，第二维则在第二层。

到这里，其实读者应该已经可以明白甚至自己解决这个问题了，也可以尝试类似地推导更多层的。然而这题还有许多地方是需要注意的：

- 因为是维护 dp，所以需要类似中序遍历递归树。

- 回溯时要注意还原序列，否则 $[mid+1,r]$ 对应的不是序列实际上的 $[mid+1,r]$。

- **一定要注意使用稳定排序（stable_sort）或者给每个元素多赋一个关键字！** 否则处理相同元素时会出现问题，建议有重复元素都用这种处理方法。

code：

```cpp
int n,m,d[N],tr[N];
struct node{
	int a,b,c,d,dp,id;
	bool pd;
}e[N],tmp[N];
#define lowbit(x) (x&(-x))
il void update(int x,int y){
	while(x<=n){
		tr[x]=max(tr[x],y);
		x+=lowbit(x);
	}
}
il int query(int x){
	int ret=0;
	while(x){
		ret=max(ret,tr[x]);
		x-=lowbit(x);
	}
	return ret;
}
il void init(int x){
	while(x<=n){
		tr[x]=0;
		x+=lowbit(x);
	}
}
il bool cmp1(node x,node y){
	return x.a!=y.a?x.a<y.a:(x.b!=y.b?x.b<y.b:(x.c!=y.c?x.c<y.c:x.d<y.d));
}
il bool cmp2(node x,node y){
	return x.b!=y.b?x.b<y.b:(x.c!=y.c?x.c<y.c:x.d<y.d);
}
il bool cmp3(node x,node y){
	return x.c!=y.c?x.c<y.c:x.d<y.d;
}
void cdq2(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq2(l,mid);
	stable_sort(e+l,e+mid+1,cmp3),stable_sort(e+mid+1,e+r+1,cmp3);
	for(int i=l,j=mid+1;j<=r;j++){
		while(i<=mid&&e[i].c<=e[j].c){
			if(!e[i].pd)
				update(e[i].d,e[i].dp);
			i++;
		}
		if(e[j].pd)
			e[j].dp=max(e[j].dp,query(e[j].d)+1);
	}
	rep(i,l,mid){if(!e[i].pd)init(e[i].d);}
	stable_sort(e+l,e+r+1,cmp2);
	cdq2(mid+1,r);
}
void cdq1(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq1(l,mid);
	rep(i,l,mid)e[i].pd=false;
	rep(i,mid+1,r)e[i].pd=true;
	stable_sort(e+l,e+r+1,cmp2);
	cdq2(l,r);
	stable_sort(e+l,e+r+1,cmp1);
	cdq1(mid+1,r);
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%d%d%d%d",&e[i].a,&e[i].b,&e[i].c,&e[i].d);
		e[i].dp=1,e[i].id=i;
		d[i]=e[i].d;
	}
	stable_sort(d+1,d+n+1),m=unique(d+1,d+n+1)-d-1;
	rep(i,1,n){
		e[i].d=lower_bound(d+1,d+m+1,e[i].d)-d;
	}
	stable_sort(e+1,e+n+1,cmp1);
	cdq1(1,n);
	int ans=0;
	rep(i,1,n){
		ans=max(ans,e[i].dp);
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：spire001 (赞：3)

## P3769题解


### 分析
题目考察的是 cdq 分治优化 dp。

很模板的四维最长上升子序列，本题的动态规划转移为四维偏序，所以需要使用 cdq 套 cdq 来优化 dp。

需要注意，转移时多使用排序，需仔细分析回溯时，是否需要将数组返回原始状态，强烈推荐对所有排序使用 `stable_sort` 而非 `sort`。

### 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define lowbit(x) (x & -(x))

using namespace std;

constexpr int N = 100010;

int _dp[N], n, m, b[N], ln, ans, c[N];
inline void add(const int x, const int val) { for (int i = x; i <= n; i += lowbit(i)) c[i] = max(c[i], val); return; }
inline int ask(const int x) { int res = 0; for (int i = x; i; i &= i - 1) res = max(res, c[i]); return res; } // 树状数组维护最大前缀
inline void clear(const int x) { for (int i = x; i <= n; i += lowbit(i)) c[i] = 0; return; }

enum color { LEFT, RIGHT, NONE };

struct node {
  int a, b, c, d, id, val;
  enum color flag;

  inline bool operator == (const node &Q) const
  {
    return a == Q.a && b == Q.b && c == Q.c && d == Q.d;
  }
  bool operator < (const node &Q) const
  {
    return id < Q.id;
  }
  int& dp()
  {
    return _dp[id];
  }
} a[N], tmp[N];

void cdq2(const int, const int);
void cdq1(const int l, const int r)
{
  if (l == r) return;

  const int mid = (l + r) >> 1;
  cdq1(l, mid);

  for (int i = l; i <= mid; i++) tmp[i] = a[i], tmp[i].flag = LEFT;
  for (int i = mid + 1; i <= r; i++) tmp[i] = a[i], tmp[i].flag = RIGHT;

  stable_sort(tmp + l, tmp + r + 1, [&](const node &A, const node &B) {
    if (A.b != B.b) return A.b < B.b;
    if (A.c != B.c) return A.c < B.c;
    return A.d < B.d;
  }); // 按 b 排序

  cdq2(l, r);

  cdq1(mid + 1, r);
}

void cdq2(const int l, const int r)
{
  if (l == r) 
  {
    tmp[l].dp() = max(tmp[l].dp(), tmp[l].val);
    return;
  }

  const int mid = (l + r) >> 1;
  cdq2(l, mid);

  auto cmp = [&](const node &A, const node &B) {
    if (A.c != B.c) return A.c < B.c;
    return A.d < B.d;
  }; // 按 c 排序

  stable_sort(tmp + l, tmp + mid + 1, cmp);
  stable_sort(tmp + mid + 1, tmp + r + 1, cmp);

  int i = l, j = mid + 1;

  while (j <= r)
  {
    while (i <= mid && tmp[i].c <= tmp[j].c)
    {
      if (tmp[i].flag == LEFT)
        add(tmp[i].d, tmp[i].dp());
      i++;
    }
    if (tmp[j].flag == RIGHT)
      tmp[j].dp() = max(tmp[j].dp(), tmp[j].val + ask(tmp[j].d));
    ans = max(ans, tmp[j].dp());
    j++;
  }

  for (int p = l; p != i; p++) 
    if (tmp[p].flag == LEFT)
      clear(tmp[p].d);
  
  stable_sort(tmp + mid + 1, tmp + r + 1, [&](const node &A, const node &B) {
    if (A.b != B.b) return A.b < B.b;
    if (A.c != B.c) return A.c < B.c;
    return A.d < B.d;
  }); // 恢复初始状态

  cdq2(mid + 1, r);

  return;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> n; 

  for (int i = 1; i <= n; i++)
    cin >> tmp[i].a >> tmp[i].b >> tmp[i].c >> tmp[i].d, b[i] = tmp[i].d;

  stable_sort(b + 1, b + n + 1); ln = unique(b + 1, b + n + 1) - b - 1;
  for (int i = 1; i <= n; i++) tmp[i].d = lower_bound(b + 1, b + ln + 1, tmp[i].d) - b; // 第四位需要离散化

  stable_sort(tmp + 1, tmp + n + 1, [&](const node &A, const node &B) {
    if (A.a != B.a) return A.a < B.a;
    if (A.b != B.b) return A.b < B.b;
    if (A.c != B.c) return A.c < B.c;
    return A.d < B.d;
  }); // 初始按 a 排序

  int tot = 0;
  for (int i = 1; i <= n; i++)
  {
    tot++; 
    if (!(tmp[i] == tmp[i + 1])) // 去重操作
    {
      m++;
      a[m] = tmp[i];
      a[m].val = tot; 
      a[m].id = m;
      ans = max(ans, tot);
      tot = 0;
    }
  }

  cdq1(1, m);

  cout << ans << endl;

  return 0;
}

/*
begin: 2024年6月12日14:26:32
debug: 2024年6月12日14:50:44
finish: 2024年6月12日15:11:09
stable_sort 的重要性 ...
*/

```

---

## 作者：Shunpower (赞：3)

额，自己发明了 cdq 套 cdq。但好像很正常。

------------

考虑优化一个显然 dp：$f_i$ 表示以 $i$ 结尾的最长单调不降子序列长度。你发现 $f_i\gets \max(f_j+1)$ 的 $j$ 必须满足 $i,j$ 在四维偏序上都 $i\geq j$。

考虑类似三维偏序，我们使用 cdq 分治套 cdq 分治。

对于第一维 $a$，排序解决。

第二维 $b$，cdq 分治，把区间掰成两半。像三维偏序的 dp 一样，先把左边区间的 $f$ 值全部处理出来，再左右各自排序，然后进行归并。

归并操作有些不同之处，需要重新考虑左边的数怎样对右边进行贡献。可以发现对于 $(c_i,d_i)$，它想对 $(c_j,d_j)$ 做 $dp_i+1$ 的贡献当且仅当 $c_i\geq c_j\land d_i\geq d_j$。那么转移过程相当于我们需要一个数据结构，每次在二维平面上插入一个带权点，或查询一个矩形内部点的最大权。

比较暴力的 ds 方案可以直接使用 KDT，但也可以考虑离线。

可以发现，加上时间维之后这个问题转化为了一个三维偏序。按照时间维排序，然后把操作按照 $c$ 从大到小排序之后掰成两半，考虑左边的插入操作对右边的询问做的贡献，那么只需要一个支持求区间最大值的线段树解决掉 $d$ 维就可以了。

回到外层 cdq 之后记得要继续递归考虑右区间 $f$。

talk is cheap，代码感觉清晰一些：

```cpp
int n;
struct node{
    int a,b,c,d;
    int dp;
} p[N];
struct query{
    int op,x,y,w;
    int t,id,ans;
} q[N<<1];
int tot;
void conb(int id,int op){
    tot++;
    q[tot]={op,p[id].c,p[id].d,p[id].dp,tot,id,0};   
}
bool cmpa(node x,node y){
    if(x.a==y.a){
        if(x.b==y.b){
            if(x.c==y.c) return x.d<y.d;
            return x.c<y.c;
        }
        return x.b<y.b;
    }
    return x.a<y.a;
}
bool cmpb(node x,node y){
    if(x.b==y.b){
        if(x.c==y.c) return x.d<y.d;
        return x.c<y.c;
    }
    return x.b<y.b;
}
bool cmpx(query &x,query &y){
    if(x.x==y.x){
        if(x.y==y.y) return x.id<y.id;
        return x.y<y.y;
    }
    return x.x<y.x;
}
bool cmpt(query &x,query &y){
    if(x.t==y.t){
        if(x.x==y.x){
            if(x.y==y.y) return x.id<y.id;
            return x.y<y.y;
        }
        return x.x<y.x;
    }
    return x.t<y.t;
}
#define mid (l+r>>1)
int rt;
struct Segment_Tree{
    int tot;
    int maxn[N*40],ls[N*40],rs[N*40];
    void insert(int &p,ll l,ll r,int d,int x){
        if(!p){
            tot++;
            p=tot;
        }
        if(l==r) return maxn[p]=max(maxn[p],x),void();
        if(d<=mid) insert(ls[p],l,mid,d,x);
        else insert(rs[p],mid+1,r,d,x);
        maxn[p]=max(maxn[ls[p]],maxn[rs[p]]);
    }
    int query(int p,ll l,ll r,int ml,int mr){
        if(!p) return 0;
        if(ml<=l&&r<=mr) return maxn[p];
        int ans=0;
        if(ml<=mid) ans=max(ans,query(ls[p],l,mid,ml,mr));
        if(mid<mr) ans=max(ans,query(rs[p],mid+1,r,ml,mr));
        return ans;
    }
} T;
void querycdq(int l,int r){
    if(l==r) return p[q[l].id].dp=max(p[q[l].id].dp,(q[l].ans+1)*(q[l].op==2)),void();
    querycdq(l,mid);
    sort(q+l,q+mid+1,cmpx);
    sort(q+mid+1,q+r+1,cmpx);
    int i=l,j=mid+1;
    // cout<<"!"<<l<<" "<<r<<endl;
    while(j<=r){
        while(i<=mid&&q[i].x<=q[j].x){
            if(q[i].op==1) T.insert(rt,0,V+V,q[i].y+V,q[i].w);
            // cout<<q[i].x<<" "<<q[i].y<<" "<<q[i].w<<"!"<<endl;
            i++;
        }
        q[j].ans=max(q[j].ans,T.query(rt,0,V+V,1,q[j].y+V));
        // cout<<q[j].op<<"?"<<q[j].id<<"///"<<q[j].y<<" "<<q[j].ans<<endl;
        j++;
    }
    rt=0;
    fr1(i,1,T.tot) T.ls[i]=T.rs[i]=T.maxn[i]=0;
    T.tot=0;
    sort(q+mid+1,q+r+1,cmpt);
    querycdq(mid+1,r);
}
void cdq(int l,int r){
    if(l==r) return;
    cdq(l,mid);
    sort(p+l,p+mid+1,cmpb);
    sort(p+mid+1,p+r+1,cmpb);
    int i=l,j=mid+1;
    tot=0;
    while(j<=r){
        while(i<=mid&&p[i].b<=p[j].b) conb(i,1),i++;
        conb(j,2);
        j++;
    }
    // cout<<l<<","<<r<<","<<tot<<"!"<<endl;
    querycdq(1,tot);
    sort(p+mid+1,p+r+1,cmpa);
    cdq(mid+1,r);
}
#undef mid
int main(){
#ifdef Griffin
    freopen("hack.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n;
    fr1(i,1,n) p[i].dp=1;
    fr1(i,1,n) cin>>p[i].a>>p[i].b>>p[i].c>>p[i].d;
    sort(p+1,p+n+1,cmpa);
    cdq(1,n);
    int ans=0;
    fr1(i,1,n) ans=max(ans,p[i].dp);
    cout<<ans<<'\n';
    ET;
}
//ETERNAL LOVE FOR Zhang Junhao, Mu Zhicheng and Zuo Hang.
//ALL FOR Zhang Junhao.
```

---

## 作者：NATURAL6 (赞：2)

## 题意

求四维最长不降链。

可以很快想到一个 $O(n^2)$ 的做法，那就是对于每个数按第一维排序，然后暴力找到合法前缀最大值，更新这个数的答案。

那么实际上就是个三维偏序问题。

## 解法

考虑分块，将序列按第一维排序后分块，块长为 $B$。

先假设我们已经有了对于现在块内每个数在前面的块中的最大合法答案，那么只需要把这个答案和块内前面的合法点一一比较即可，时间复杂度 $O(nB)$。

考虑怎么求这个答案。

可以对所有数先离散化一边，然后把答案对应到该三维点上，再求一遍三维前缀最大值，但这样的时间复杂度是 $O(\dfrac{n^4}{B})$， 明显过不了。

实际上，我们要求的只是对这个块内点的答案，所以完全不需要每次对整个值域做上述操作。

所以我们可以把所有数按该块内的数进行离散化，这样子不影响它们之间的相对大小，也就不影响答案，但要做的问题规模变成了 $B$。

于是就可以在 $O(\dfrac{n}{B}(B^3+n))$ 的时间内求出来块内每个数在前面的块中的最大合法答案。

总时间复杂度为 $O(nB+\dfrac{n}{B}(B^3+n))$， 在 $B$ 为 $\sqrt[3]{n}$ 时为最优，空间线性。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int qread()
{
	register int a=0,f=1;register char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){(a*=10)+=(ch^48);ch=getchar();}
	return a*f;
}
int n,cl,c[50010],st[50010],ed[50010],ans[50010],mp[100][100][100],que[3][50010],en[3],b[200010],tot;
int xx,yy,zz,cc[3][200010],p[3];
struct poin
{
	int a,b,c,d;
}a[50010];
inline bool cmp(register poin x,register poin y){return x.a==y.a?(x.b==y.b?(x.c==y.c?x.d<y.d:x.c<y.c):x.b<y.b):x.a<y.a;}
inline int find(register int x,register int y,register int z)
{
	int an=0;
	an=max(an,mp[x-1][y][z]);
	an=max(an,mp[x][y-1][z]);
	an=max(an,mp[x][y][z-1]);
	return an;
} 
inline bool check(register int x,register int y)
{
	if(a[x].b>a[y].b)return 0;
	if(a[x].c>a[y].c)return 0;
	if(a[x].d>a[y].d)return 0;
	return 1;
}
int main()
{
	n=qread();
	cl=pow(n,0.333333)+1;
	for(register int i=1;i<=n;++i)b[++tot]=a[i].a=qread(),b[++tot]=a[i].b=qread(),b[++tot]=a[i].c=qread(),b[++tot]=a[i].d=qread(),c[i]=(i-1)/cl+1,ed[c[i]]=i;
	sort(b+1,b+1+tot);
	tot=unique(b+1,b+1+tot)-b-1;
	for(register int i=1;i<=n;++i)
	{
		a[i].a=lower_bound(b+1,b+1+tot,a[i].a)-b;
		a[i].b=lower_bound(b+1,b+1+tot,a[i].b)-b;
		a[i].c=lower_bound(b+1,b+1+tot,a[i].c)-b;
		a[i].d=lower_bound(b+1,b+1+tot,a[i].d)-b;
	}
	for(register int i=n;i;--i)st[c[i]]=i;
	sort(a+1,a+1+n,cmp);
	for(register int i=1;i<=c[n];++i)
	{
		en[0]=en[1]=en[2]=0;
		for(register int j=st[i];j<=ed[i];++j)
		{
			que[0][++en[0]]=a[j].b;
			que[1][++en[1]]=a[j].c;
			que[2][++en[2]]=a[j].d;
		}
		sort(que[0],que[0]+en[0]+1);
		sort(que[1],que[1]+en[1]+1);
		sort(que[2],que[2]+en[2]+1);
		en[0]=unique(que[0],que[0]+en[0]+1)-que[0]-1;
		en[1]=unique(que[1],que[1]+en[1]+1)-que[1]-1;
		en[2]=unique(que[2],que[2]+en[2]+1)-que[2]-1;
		p[0]=p[1]=p[2]=0;
		for(register int j=1;j<=n*4;++j)
		{
			while(que[0][p[0]]<j&&p[0]<=en[0])++p[0];
			while(que[1][p[1]]<j&&p[1]<=en[1])++p[1];
			while(que[2][p[2]]<j&&p[2]<=en[2])++p[2];
			cc[0][j]=p[0],cc[1][j]=p[1],cc[2][j]=p[2];
		}
		for(register int j=1;j<st[i];++j)
		{
			xx=cc[0][a[j].b];
			yy=cc[1][a[j].c];
			zz=cc[2][a[j].d];
			mp[xx][yy][zz]=max(mp[xx][yy][zz],ans[j]);
		}
		for(register int j=1;j<=en[0];++j)
		{
			for(register int k=1;k<=en[1];++k)
			{
				for(register int l=1;l<=en[2];++l)
				{
					mp[j][k][l]=max(mp[j][k][l],find(j,k,l));
				}
			}
		}
		for(register int j=st[i];j<=ed[i];++j)
		{
			xx=cc[0][a[j].b];
			yy=cc[1][a[j].c];
			zz=cc[2][a[j].d];
			ans[j]=mp[xx][yy][zz]+1;
			for(register int k=st[i];k<j;++k)if(check(k,j))ans[j]=max(ans[j],ans[k]+1);
		}
		for(register int j=1;j<=en[0]+1;++j)
		{
			for(register int k=1;k<=en[1]+1;++k)
			{
				for(register int l=1;l<=en[2]+1;++l)
				{
					mp[j][k][l]=0;
				}
			}
		}
	}
	for(register int i=1;i<=n;++i)ans[0]=max(ans[0],ans[i]);
	printf("%d",ans[0]);
	return 0;
}
```


---

## 作者：happybob (赞：1)

考虑按照 $4$ 维依次作为关键字排序，那么就是求这个序列的最长不降子序列，其中每一维度都要不降。

显然的 $f_i$ 表示以 $i$ 结尾的最长上升子序列，排序后有 $f_i= (\max \limits_{j \in [1,i) \land b_j \leq b_i \land c_j \leq c_i \land d_j \leq d_i} f_j) + 1$。

直接做是三次方的，注意到这是一个三维偏序，可以直接上 K-D Tree 维护，复杂度 $O(n^\frac{5}{3})$，可以通过。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

const int N = 5e4 + 5;

int n;
int f[N], ans;
struct Point
{
	int x[4];
}p[N], g[N];

class KD_Tree
{
public:
	int idx;
	struct Node
	{
		int lson, rson;
		int x[3];
		int minn[3], maxn[3], val, maxval;
	}tr[N];
	void pushup(int u)
	{
		tr[u].maxval = max({ tr[tr[u].lson].maxval, tr[tr[u].rson].maxval, tr[u].val });
		for (auto& i : { 0, 1, 2 })
		{
			tr[u].minn[i] = min({ tr[u].x[i], (tr[u].lson ? tr[tr[u].lson].minn[i] : (int)2e9), (tr[u].rson ? tr[tr[u].rson].minn[i] : (int)2e9) });
			tr[u].maxn[i] = max({ tr[u].x[i], (tr[u].lson ? tr[tr[u].lson].maxn[i] : (int)-2e9), (tr[u].rson ? tr[tr[u].rson].maxn[i] : (int)-2e9) });
		}
	}
	int build(int l, int r, int g)
	{
		int u = ++idx;
		int mid = l + r >> 1;
		nth_element(p + l, p + mid, p + r + 1, [&](const auto& x, const auto& y) {return x.x[g + 1] < y.x[g + 1]; });
		tr[u].x[0] = p[mid].x[1], tr[u].x[1] = p[mid].x[2], tr[u].x[2] = p[mid].x[3];
		tr[u].val = 0;
		if (l == r)
		{
			pushup(u);
			return u;
		}
		if (l < mid) tr[u].lson = build(l, mid - 1, (g == 2 ? 0 : g + 1));
		if (mid < r) tr[u].rson = build(mid + 1, r, (g == 2 ? 0 : g + 1));
		pushup(u);
		return u;
	}
	void update(int x, int y, int z, int u, int val)
	{
		if (!u) return;
		if (tr[u].minn[0] > x || tr[u].maxn[0] < x || tr[u].minn[1] > y || tr[u].maxn[1] < y || tr[u].minn[2] > z || tr[u].maxn[2] < z) return;
		if (tr[u].x[0] == x && tr[u].x[1] == y && tr[u].x[2] == z)
		{
			tr[u].val = max(tr[u].val, val);
			pushup(u);
			return;
		}
		update(x, y, z, tr[u].lson, val);
		update(x, y, z, tr[u].rson, val);
		pushup(u);
	}
	int query(int x, int y, int z, int u)
	{
		if (!u) return (int)-2e9;
		if (tr[u].maxn[0] <= x && tr[u].maxn[1] <= y && tr[u].maxn[2] <= z) return tr[u].maxval;
		if (tr[u].minn[0] > x || tr[u].minn[1] > y || tr[u].minn[2] > z) return (int)-2e9;
		int res = (int)-2e9;
		if (tr[u].x[0] <= x && tr[u].x[1] <= y && tr[u].x[2] <= z) res = tr[u].val;
		res = max({ res, query(x, y, z, tr[u].lson), query(x, y, z, tr[u].rson) });
		return res;
	}
}tr;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> p[i].x[0] >> p[i].x[1] >> p[i].x[2] >> p[i].x[3];
	}
	sort(p + 1, p + n + 1, [&](const auto& x, const auto& y) {for (auto& i : { 0, 1, 2, 3 }) { if (x.x[i] ^ y.x[i]) { return x.x[i] < y.x[i]; } } return false; });
	for (int i = 1; i <= n; i++) g[i] = p[i];
	tr.build(1, n, 0);
	for (int i = 1; i <= n; i++)
	{
		int res = tr.query(g[i].x[1], g[i].x[2], g[i].x[3], 1);
		f[i] = max(res, 0) + 1;
		tr.update(g[i].x[1], g[i].x[2], g[i].x[3], 1, f[i]);
		ans = max(ans, f[i]);
	}
	cout << ans << "\n";
	return 0;
}
```


---

## 作者：lupengheyyds (赞：1)

## 思路：
这是一道的四维 LIS 问题，类比二维 LIS，我们可以先将第一位排序。接着使用 DP 求解。

为了快速找出另外三维都比它小的数，我们可以用KD树进行维护。（**KD 树擅长维护多维信息**）

## 实现

### 排序
需要注意的是，这里不能仅仅考虑第一维，而是要考虑所有，只是优先级不同。

例：对于输入：
```
2
1 0 0 1
1 0 0 0
```
如果只考虑第1维，那么其顺序不会发生改变。由于第前一个数据不能在第后一个数据的基础上更新，最后输出将为 `1`，但实际应该是 `2`。
代码：
```cpp
bool cmp(Point a,Point b){
	if(a.dim[0]!=b.dim[0])return a.dim[0]<b.dim[0];
	if(a.dim[1]!=b.dim[1])return a.dim[1]<b.dim[1];
	if(a.dim[2]!=b.dim[2])return a.dim[2]<b.dim[2];
	return a.dim[3]<b.dim[3];
}
sort(ele+1,ele+1+n,cmp);//主函数中

```
### 插入元素
由于 KD 树无法旋转或分裂，这里使用替罪羊树进行维护平衡。
```cpp
int bin[szl],top;//注意写垃圾回收
int New(){
	return top?bin[top--]:++tot;
}
void Slap(int u){
	if(!u) return;
	Slap(ls(u));
	order[++cnt] = kdt[u].poi;
	bin[++top]=u;
	Slap(rs(u));
	return;
}
int Build(int l,int r,int d){
	if(l>r)return 0;
	d=d%(K-1)+1;
	int p=New();
	int mid=l+r>>1;
	cmpd=d;
	nth_element(order+l,order+mid,order+r+1);
	poi(p)=order[mid];
	ls(p)=Build(l,mid-1,d+1);
	rs(p)=Build(mid+1,r,d+1);
	Up(p);
	return p;
}
bool imblce(int p){
	return siz(ls(p))>alpha*siz(p)||siz(rs(p))>alpha*siz(p);
}
void Insert(int &p,Point now,int d){
	d=d%(K-1)+1;
	if(!p){
		p=New();
		ls(p)=rs(p)=0,poi(p)=now;
		Up(p);
		return;
	}
	if(now.dim[d]<=poi(p).dim[d])Insert(ls(p),now,d+1);
	else						 Insert(rs(p),now,d+1);
	Up(p);
	if(imblce(p)){
		cnt=0;
		Slap(p);
		p=Build(1,siz(p),d);
	}
}
```
### 查询
分为全部符合，全部不符合，和部分符合。
```cpp
int Query(int p,int x,int y,int z){//找最大值 
	if(!p)return 0;
	if(mx(p)[1]<=x&&mx(p)[2]<=y&&mx(p)[3]<=z)return mxval(p);//完全符合
	if(mn(p)[1]>x||mn(p)[2]>y||mn(p)[3]>z)return 0;//完全不符合
	//部分符合，向下寻找 
	bool d=poi(p).dim[1]<=x&&poi(p).dim[2]<=y&&poi(p).dim[3]<=z;
	return max(max(Query(ls(p),x,y,z),Query(rs(p),x,y,z)),d*poi(p).val);
}
```
## 最终代码：
```cpp
//KD-Tree优化DP 
#include<bits/stdc++.h>
using namespace std;
const int szl=5e5+5,K=4;//树中用1~K-1维 
const double alpha=0.75;
int n,cmpd,tot,cnt,root;
struct Point{
	int dim[K],val;
	void Read(){
		for(int i=0;i<K;i++)cin>>dim[i];
		val=0;
		return;
	}
	bool operator<(const Point &tmp)const{
		return dim[cmpd]<tmp.dim[cmpd];
	}
}ele[szl],order[szl];
bool cmp(Point a,Point b){
	if(a.dim[0]!=b.dim[0])return a.dim[0]<b.dim[0];
	if(a.dim[1]!=b.dim[1])return a.dim[1]<b.dim[1];
	if(a.dim[2]!=b.dim[2])return a.dim[2]<b.dim[2];
	return a.dim[3]<b.dim[3];
}
int bin[szl],top;
int New(){
	return top?bin[top--]:++tot;
}
struct KdTr{
	int mn[K],mx[K],ls,rs,mxval,siz;
	Point poi; 
	//用于减少码量
	#define ls(x) kdt[x].ls
	#define rs(x) kdt[x].rs
	#define mn(x) kdt[x].mn
	#define mx(x) kdt[x].mx
	#define mxval(x) kdt[x].mxval
	#define siz(x) kdt[x].siz
	#define poi(x) kdt[x].poi
}kdt[szl];
void Up(int p){
	for(int i=1;i<K;i++){
		mn(p)[i]=mx(p)[i]=poi(p).dim[i];
		if(ls(p)){
			mn(p)[i]=min(mn(p)[i],mn(ls(p))[i]);
			mx(p)[i]=max(mx(p)[i],mx(ls(p))[i]);
		}
		if(rs(p)){
			mn(p)[i]=min(mn(p)[i],mn(rs(p))[i]);
			mx(p)[i]=max(mx(p)[i],mx(rs(p))[i]);
		}
	}
	mxval(p)=max(max(mxval(ls(p)),mxval(rs(p))),poi(p).val);
	siz(p)=siz(ls(p))+siz(rs(p))+1;
	return;
}
void Slap(int u){
	if(!u) return;
	Slap(ls(u));
	order[++cnt] = kdt[u].poi;
	bin[++top]=u;
	Slap(rs(u));
	return;
}
int Build(int l,int r,int d){
	if(l>r)return 0;
	d=d%(K-1)+1;
	int p=New();
	int mid=l+r>>1;
	cmpd=d;
	nth_element(order+l,order+mid,order+r+1);
	poi(p)=order[mid];
	ls(p)=Build(l,mid-1,d+1);
	rs(p)=Build(mid+1,r,d+1);
	Up(p);
	return p;
}
bool imblce(int p){
	return siz(ls(p))>alpha*siz(p)||siz(rs(p))>alpha*siz(p);
}
void Insert(int &p,Point now,int d){
	d=d%(K-1)+1;
	if(!p){
		p=New();
		ls(p)=rs(p)=0,poi(p)=now;
		Up(p);
		return;
	}
	if(now.dim[d]<=poi(p).dim[d])Insert(ls(p),now,d+1);
	else						 Insert(rs(p),now,d+1);
	Up(p);
	if(imblce(p)){
		cnt=0;
		Slap(p);
		p=Build(1,siz(p),d);
	}
}
int ans=0;
int Query(int p,int x,int y,int z){//找最大值 
	if(!p)return 0;
	if(mx(p)[1]<=x&&mx(p)[2]<=y&&mx(p)[3]<=z)return mxval(p);//完全符合
	if(mn(p)[1]>x||mn(p)[2]>y||mn(p)[3]>z)return 0;//完全不符合
	//向下寻找 
	bool d=poi(p).dim[1]<=x&&poi(p).dim[2]<=y&&poi(p).dim[3]<=z;
	return max(max(Query(ls(p),x,y,z),Query(rs(p),x,y,z)),d*poi(p).val);
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)ele[i].Read();
	sort(ele+1,ele+1+n,cmp);
	for(int i=1;i<=n;i++){
		ele[i].val=Query(root,ele[i].dim[1],ele[i].dim[2],ele[i].dim[3])+1;
		Insert(root,ele[i],1);
	}
	cout<<mxval(root);
	return 0;
}
```

---

## 作者：Rorschachindark (赞：1)

# TATT
[题目传送门](https://www.luogu.com.cn/problem/P3769)
## 题目大意
求$4$位偏序。
## 思路
首先不用讲的是，先按照第一维排序。不过小蒟蒻有一点不是很理解，为什么排序的时候不能写成：
```cpp
bool operator < (const node &p)const
{
	return x[0] < p.x[0];
}
```

我这样就只有$64$了。zbl。。。希望评论区有dalao空降拯救一下我这个小蒟蒻。

然后我们就可以把剩下三维连带$dp$值插进$\text {K-D Tree}$（$dp$值就是LIS里面的那个），然后查询的时候直接查询比当前节点小的点的$dp$值最大的即可。

一开始没剪枝以为代码写锅了，一直盯代码也查不出错。

这是一份氧中毒的代码。
## $\text {Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 50005

int Ans,split;

struct point
{
	int x[3],w;
	bool operator < (const point &p)const{return x[split] < p.x[split];}
	bool operator > (const point &p)const
	{
		for (Int i = 0;i <= 2;++ i)
			if (x[i] < p.x[i])
				return 0;
		return 1;
	}	
};

class K_DTree
{
#define alpha 0.75
#define lson tree[k].ls
#define rson tree[k].rs
	private:
		int cur,tot,rub[MAXN];
		point a[MAXN];
		struct node
		{
			int mx[3],mi[3],ls,rs,maxw,size;point tp;
		}tree[MAXN];
		int newnode (){if (tot) return rub[tot --];else return ++ cur;}
		void Pushup (int k)
		{
			tree[k].maxw = tree[k].tp.w;
			if (lson) tree[k].maxw = max (tree[k].maxw,tree[lson].maxw);
			if (rson) tree[k].maxw = max (tree[k].maxw,tree[rson].maxw);
			for (Int i = 0;i <= 2;++ i)
			{
				tree[k].mx[i] = tree[k].mi[i] = tree[k].tp.x[i];
				if (lson) tree[k].mx[i] = max (tree[k].mx[i],tree[lson].mx[i]);
				if (lson) tree[k].mi[i] = min (tree[k].mi[i],tree[lson].mi[i]);
				if (rson) tree[k].mx[i] = max (tree[k].mx[i],tree[rson].mx[i]);
				if (rson) tree[k].mi[i] = min (tree[k].mi[i],tree[rson].mi[i]);
			}
			tree[k].size = tree[lson].size + tree[rson].size + 1;
		}
	public:
		int build (int l,int r,int deg)
		{
			if (l > r) return 0;
			int mid = (l + r) >> 1,k = newnode ();
			split = deg;
			nth_element (a + l,a + mid,a + r + 1);
			tree[k].tp = a[mid];
			lson = build (l,mid - 1,(deg + 1) % 3);
			rson = build (mid + 1,r,(deg + 1) % 3);
			Pushup (k);
			return k;
		}
		void pia (int k,int num)
		{
			if (lson) pia (lson,num);
			a[num + tree[lson].size + 1] = tree[k].tp;rub[++ tot] = k;
			if (rson) pia (rson,num + tree[lson].size + 1);
		}
		void check (int &k,int deg)
		{
			if (tree[lson].size > tree[k].size * alpha || tree[rson].size > tree[k].size * alpha)
				pia (k,0),k = build (1,tree[k].size,deg); 
		}
		void Insert (int &k,point tmp,int deg)
		{
			if (!k){k = newnode (),lson = rson = 0,tree[k].tp = tmp,Pushup (k);return ;}
			if (tmp.x[deg] <= tree[k].tp.x[deg]) Insert (lson,tmp,(deg + 1) % 3);
			else Insert (rson,tmp,(deg + 1) % 3);
			Pushup (k);
			check (k,deg);
		}
		void query (int k,point tmp)
		{
			if (!k) return ;
			if (tree[k].maxw <= Ans) return ;
			if (tmp.x[0] < tree[k].mi[0] || tmp.x[1] < tree[k].mi[1] || tmp.x[2] < tree[k].mi[2]) return ;
			if (tmp > tree[k].tp) Ans = max (Ans,tree[k].tp.w);
			if (tmp > point {tree[k].mx[0],tree[k].mx[1],tree[k].mx[2],0}) 
			{
				Ans = max (Ans,tree[k].maxw);
				return ;
			}
			query (lson,tmp);
			query (rson,tmp);
		}
#undef lson
#undef rson
#undef alpha
};

K_DTree Tree;

int n;

struct node
{
	int x[4];
	bool operator < (const node &p)const
	{
		for (Int i = 0;i <= 3;++ i)
			if (x[i] < p.x[i]) return 1;
			else if (x[i] > p.x[i]) return 0;
		return 0;
	}
}a[MAXN];

int read ()
{
	int x = 0;char c = getchar();int f = 1;
	while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}
	while (c >= '0' && c <= '9'){x = (x << 3) + (x << 1) + c - '0';c = getchar();}
	return x * f;
}

void write (int x)
{
	if (x < 0){x = -x;putchar ('-');}
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
}

signed main()
{
	n = read ();
	for (Int i = 1;i <= n;++ i)
	{
		int x = read (),y = read (),z = read (),w = read ();
		a[i] = node {x,y,z,w};
	} 
	sort (a + 1,a + n + 1);
	int rt = 0,maxAns = 0;
	for (Int i = 1;i <= n;++ i)
	{
		Ans = 0;
		Tree.query (rt,point {a[i].x[1],a[i].x[2],a[i].x[3],0});
		maxAns = max (maxAns,Ans + 1);
		Tree.Insert (rt,point {a[i].x[1],a[i].x[2],a[i].x[3],Ans + 1},0); 
	}
	write (maxAns),putchar ('\n');
	return 0;
}
```

---

## 作者：Butterfly_qwq (赞：0)

怎么这题还可以写题解呢？

K-D Tree 较为板子的题目吧。

符号约定：记二元组 $(a,b)\le(c,d)$，当且仅当 $a\le b$ 且 $c\le d$，可以递归定义（也就是说可以接受 $((a,b),(c,d))$ 这种形式）。

首先朴素 dp，设 $f_i$ 表示只有前 $i$ 个点的答案，则显然 $f_i=\max\limits_{((a_j,b_j),(c_j,d_j))\le((a_i,b_i),(c_i,d_i))}f_j+1$。

然后很容易发现可以随便选个东西比如 $a$ 排序，剩下三维假装是三个坐标依次扔 KDT 里，维护一下三维区间点数就可。

时间复杂度 $O(n^{\frac{5}{3}})$。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005,L=20;
struct dat
{
	int t,x,y,z;
}p[N];
struct node
{
	int x[3],w,mks,lc,rc,mn[3],mx[3];
	#define x(i,j) kdt[i].x[j]
	#define mn(i,j) kdt[i].mn[j]
	#define mx(i,j) kdt[i].mx[j]
	#define w(i) kdt[i].w
	#define mks(i) kdt[i].mks
	#define lc(i) kdt[i].lc
	#define rc(i) kdt[i].rc
}kdt[N];
int n,cnt,tot,rec[N],ans,rt[L],ql[3],qr[3];
void del(int &u)
{
	if(!u)return;
	rec[++cnt]=u;
	del(lc(u));
	del(rc(u));
	u=0;
}
void pushup(int u)
{
	mks(u)=max(max(mks(lc(u)),mks(rc(u))),w(u));
	for(int i:{0,1,2})
	{
		mn(u,i)=mx(u,i)=x(u,i);
		if(lc(u))
		{
			mn(u,i)=min(mn(u,i),mn(lc(u),i));
			mx(u,i)=max(mx(u,i),mx(lc(u),i));
		}
		if(rc(u))
		{
			mn(u,i)=min(mn(u,i),mn(rc(u),i));
			mx(u,i)=max(mx(u,i),mx(rc(u),i));
		}
	}
}
int build(int l,int r,int d)
{
	int mid=l+r>>1;
	nth_element(rec+l,rec+mid,rec+r+1,[d](int a,int b){return x(a,d)<x(b,d);});
	int rt=rec[mid];
	if(l<mid)lc(rt)=build(l,mid-1,(d+1)%3);
	if(r>mid)rc(rt)=build(mid+1,r,(d+1)%3);
	pushup(rt);
	return rt;
}
void update(int x[],int w)
{
	tot++;
	for(int i:{0,1,2})x(tot,i)=x[i];
	w(tot)=w;
	rec[cnt=1]=tot;
	for(int i=0;;i++)
	{
		if(rt[i])del(rt[i]);
		else
		{
			rt[i]=build(1,cnt,0);
			break;
		}
	}
}
int query(int u,int l[],int r[])
{
	if(!u)return 0;
	int f=1;
	for(int i:{0,1,2})f&=(l[i]<=mn(u,i)&&mx(u,i)<=r[i]);
	if(f)return mks(u);
	for(int i:{0,1,2})if(mx(u,i)<l[i]||mn(u,i)>r[i])return 0;
	f=1;
	for(int i:{0,1,2})f&=(l[i]<=x(u,i)&&x(u,i)<=r[i]);
	return max(max(query(lc(u),l,r),query(rc(u),l,r)),f*w(u));
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i].t>>p[i].x>>p[i].y>>p[i].z;
	sort(p+1,p+n+1,[](dat a,dat b)->bool{if(a.t!=b.t)return a.t<b.t;if(a.x!=b.x)return a.x<b.x;if(a.y!=b.y)return a.y<b.y;if(a.z!=b.z)return a.z<b.z;return 0;});
	for(int i=1,la;i<=n;i++)
	{
		ql[0]=ql[1]=ql[2]=0xc0c0c0c0;
		qr[0]=p[i].x;qr[1]=p[i].y;qr[2]=p[i].z;
		la=0;
		for(int i=0;i<L;i++)la=max(la,query(rt[i],ql,qr)+1);
		update(qr,la);
		ans=max(ans,la);
	}
	cout<<ans;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

首先 $dp_i$ 表示以第 $i$ 个点结尾的最长长度，则状态转移方程为：

$$dp_i=\max([a_j \le a_i][b_j \le b_i][c_j \le c_i][d_j \le d_i] dp_j + 1)$$

朴素转移是 $O(N^2)$ 的，一般情况下会超时~~乱搞能冲过去~~。

因为这题本质是一个四维偏序问题，可以先将第一维 $a$ 进行排序后，变成了三维空间内求一个长方体内最大点值。

考虑使用数据结构进行维护，开一个三层的树套树，外层是树状数组，中层和下层是动态开点线段树。

这样时间和空间复杂度是 $O(N \log^3 N)$ 的，空间上貌似不允许，考虑 cdq 分治算法。

对于三维偏序问题，先将第一维排序，然后设当前分治区间为 $[l,r]$，将左右两区间按照第二维排序，现在要计算 $[l,mid]$ 对 $[mid+1,r]$ 的贡献。

明显可以走指针，对于第三维使用树状数组维护即可，时间复杂度为 $O(N \log^3 N)$，但是空间复杂度基本是 $O(N)$。

其实 cdq 分治本质上是将左右两区间变成 $(a_1,0,c_1)$ 和 $(a_2,1,c_2)$ 的形式，使得左区间的第二维对于右区间都满足条件。

而四维偏序也是同理，考虑将左右两区间变为 $(a_1,0/1,0/1,d_1)$ 和 $(a_2,0/1,0/1,d_2)$ 的形式。

考虑用 cdq 套 cdq 解决，先变为 $(a_1,0,c_1,d_1)$ 和 $(a_2,1,c_2,d_2)$ 的形式，然后将这个区间的第三维进行 cdq 分治。

时间复杂度为 $O(N \log^3 N)$。

**注意第四维要先离散化。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
using namespace std;
typedef long long ll;
const ll N=50050; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,cnt,ans;
ll b[N];
struct Node{
	ll a,b,c,d;	
	ll ans;
	bool f;
}a[N];
class BIT{
public:
	ll a[N];
	void add(ll x,ll v){
		for(ll i=x;i<=cnt;i+=lowbit(i))
		  a[i]=max(a[i],v);
	}
	void clear(ll x){
		for(int i=x;i<=cnt;i+=lowbit(i))
		  a[i]=0;
	}
	ll qurey(ll x){
		ll ans=0;
		for(int i=x;i;i-=lowbit(i))
		  ans=max(ans,a[i]);
		return ans;
	}
}T;
bool cmp1(const Node&x,const Node&y){
	if(x.a!=y.a)
	  return x.a<y.a;
	if(x.b!=y.b)
	  return x.b<y.b;
	if(x.c!=y.c)
	  return x.c<y.c;
	return x.d<y.d;
}
bool cmp2(const Node&x,const Node&y){
	if(x.b!=y.b)
	  return x.b<y.b;
	if(x.c!=y.c)
	  return x.c<y.c;
	return x.d<y.d;
}
bool cmp3(const Node&x,const Node&y){
	if(x.c!=y.c)
	  return x.c<y.c;
	return x.d<y.d;
}
void cdq2(ll l,ll r){
	if(l==r)
	  return;
	ll mid=(l+r)>>1;
	cdq2(l,mid);
	stable_sort(a+l,a+mid+1,cmp3);
	stable_sort(a+mid+1,a+r+1,cmp3);
	ll i=l,j=mid+1;
	for(;j<=r;j++){
		while(i<=mid&&a[i].c<=a[j].c){
			if(!a[i].f)
			  T.add(a[i].d,a[i].ans);
			i++;
		}
		if(a[j].f)
		  a[j].ans=max(a[j].ans,T.qurey(a[j].d)+1);
	}	
	for(int j=l;j<i;j++)
	  if(!a[j].f)
	    T.clear(a[j].d);
	stable_sort(a+l,a+r+1,cmp2);
	cdq2(mid+1,r);
}
void cdq1(ll l,ll r){
	if(l==r)
	  return;
	ll mid=(l+r)>>1;
	cdq1(l,mid);
	for(int i=l;i<=mid;i++)
	  a[i].f=0;
	for(int i=mid+1;i<=r;i++)
	  a[i].f=1;
	stable_sort(a+l,a+r+1,cmp2);
	cdq2(l,r);
	stable_sort(a+l,a+r+1,cmp1);
	cdq1(mid+1,r);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]={read(),read(),read(),read(),1,0};
		b[++cnt]=a[i].d;
	}
	stable_sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-(b+1);
	for(int i=1;i<=n;i++)
	  a[i].d=lower_bound(b+1,b+cnt+1,a[i].d)-b;
	stable_sort(a+1,a+n+1,cmp1);
	cdq1(1,n);
	for(int i=1;i<=n;i++){
		ans=max(ans,a[i].ans);
//		cerr<<a[i].ans<<' ';
	}
	write(ans);
	return 0;
}
```

---

