# 【MX-X9-T4】『GROI-R3』区间

## 题目描述

小巡给你 $m$ 个**长度互不相等**的区间 $[l_1,r_1], \ldots, [l_m,r_m]$ 、一个长度为 $n$ 的整数序列 $a_1,\ldots,a_n$、和一个整数 $v$。

小巡想让你求有多少个整数 $k\in [1,v]$ 使得不存在整数 $i, j$（$1\le i\le n$、$1\le j\le m$）满足 $a_i+k\in[l_j,r_j]$。

## 说明/提示

**【样例解释 #1】**

符合条件的 $k$ 有 $7,8,9,10$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n,m,a_i\le$ | $l_i,r_i,v\le$ | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| 1 | $500$ | $500$ | $10$ |
| 2 | $5000$ | $5000$ | $10$ |
| 3 | $5000$ | $10^{18}$ | $20$ |
| 4 | $2\times10^5$ | $10^{18}$ | $30$ |
| 5 | $5\times10^5$ | $10^{18}$ | $30$ |

对于 $100\%$ 的数据，保证 $1\le n,m,a_i\leq 5\times10^5$，$1\le l_i\le r_i\leq10^{18}$，$1\le v\le 10^{18}$，对任意 $1\leq i<j\leq m$ 都有 $r_j-l_j\neq r_i-l_i$。

## 样例 #1

### 输入

```
3 3 15
1 2 4
2 3 
5 7 
15 114514
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 5 100
5 10 92 23 1 70 33 45 81 20
2 30
1 4
5 19
5 31
91 93```

### 输出

```
49```

# 题解

## 作者：是青白呀 (赞：4)

~~最困难的是~~注意到 $a_i\le 5\times 10^5$。

可以看作是把每个区间分别向左平移 $a_i$ 个位置后覆盖数轴，问 $[1,v]$ 中有几个点没被覆盖到。$a_i$ 非常小，说明所有区间的平移距离都很小，相交的可能性很大。考虑对于每一个区间 $[l_i,r_i]$，求出其平移后形成的区间的并。

在这里，观察到对于一个长度为 $len$ 的区间，若 $|a_i-a_j|\le len$ 的，则该区间平移 $a_i$ 和平移 $a_j$ 形成的两个区间会合并成一个区间。因此，所有平移后形成的区间并起来，最多形如 $\frac{\max a_i}{len}$ 个区间。又因为区间长度两两不同，故最终总的区间个数只有 $O(n\ln n)$ 个。

我们可以将 $a_i$ 排序，从小到大枚举 $1\sim 5\times 10^5$ 内的每一个区间长度，并判断当前每一个还未合并到一起的 $a_i,a_{i+1}$ 能否合并，使用连续段并查集维护这个合并过程，同时也可以求出该长度的区间在平移且取并后，区间的个数。由于间隔个数等于区间个数减 $1$，因此总判断次数也是 $O(n\ln n)$ 的。

最后将所有区间排序即可求出总覆盖长度。总复杂度 $O(n\ln n \log n)$，跑得很快。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define lowbit(i) (i&-i)
#define int long long
#define qingbai qwq
using namespace std;
typedef long long ll;
const int N=5e5+5,M=2e6+5,mo=998244353,inf=(ll)1e18+7;
const double PI=acos(-1);
void read(int &a){
    int x=0,w=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    a=x*w;
}
int n,m,v,a[N];
pii p[N];
struct bcj{
    int fa[N];
    void init(){
        rep(i,1,n)
            fa[i]=i;
    }
    int find(int x){
        if(x==fa[x])return fa[x];
        return fa[x]=find(fa[x]);
    }
    void merge(int x,int y){
        x=find(x),y=find(y),fa[x]=y;
    }
}B;
vector<int>id[N];
vector<pii>s;
signed main(){
    read(n),read(m),read(v);
    rep(i,1,n)
        read(a[i]);
    sort(a+1,a+n+1),n=unique(a+1,a+n+1)-a-1;
    rep(i,1,m){
        read(p[i].fir),read(p[i].sec);
        int len=p[i].sec-p[i].fir+1;
        if(len<=500000)id[len].push_back(i);
    }
    B.init();
    rep(i,1,500000){
        int j=B.find(1);
        while(j<n){
            if(a[j+1]-a[j]<=i)B.merge(j,j+1);
            else j++;
            j=B.find(j);
        }
        int le=1;
        while(le<=n){
            int ri=B.find(le);
            for(auto j:id[i])
                s.push_back(mp(max(1ll,p[j].fir-a[ri]),min(v,p[j].sec-a[le])));
            le=ri+1;
        }
    }
    rep(i,1,m)
        if(p[i].sec-p[i].fir+1>500000)s.push_back(mp(max(1ll,p[i].fir-a[n]),min(v,p[i].sec-a[1])));
    sort(s.begin(),s.end());
    int nwv=0,ans=0;
    for(auto i:s)
        if(i.sec>nwv)ans+=min(i.sec-nwv,i.sec-i.fir+1),nwv=i.sec;
    printf("%lld\n",v-ans);
    return 0;
}
```

---

## 作者：ykzzldz (赞：3)

这个题还是比较有趣的。

首先分析一下题目，题目中给出了一个比较奇怪的限制，区间长度不同。一般来说，这种限制要么是为了保证题目有解，要么是保证复杂度。这题中显然不是前者，但具体是如何保证复杂度的，我们先继续思考。

另外，发现除了 $a_i$ 之外，其他的值域都是 $10^{18}$ 级别，说明最后的复杂度大概率与 $a_i$ 有关。

题目给出的条件其实是说对于给定的 $m$ 个区间，将每个区间向左平移 $a_i$ 个单位，被区间覆盖的位置是被 ban 掉的，求没被 ban 掉的数的个数。由于 $a_i$ 非常小，我们对这个题目有一个大体的感受，那就是区间之间会有许多交集。

具体分析一下，若有一个区间 $[l,r]$，分别有两个平移的距离 $a_i<a_j$，最后形成的区间 $[l-a_i,r-a_i]$ 和 $[l-a_j,r-a_j]$ 有交的条件为 $l-a_j\le r-a_i$，即 $a_i-a_j\le r-l$。考虑将每 $r-l$ 分为一段，一段中的 $a_i$ 都是可以合并的，也就是说，每段会合并出一个区间。这样，形成的区间个数是 $\frac{a_i}{r-l}$ 的。在复杂度的分析中，默认 $O(a_i)=O(n)$。由于区间长度不同，根据调和级数，区间的个数是 $O(n\log n)$ 的。这也印证了我们一开始的关于区间长度不同保证复杂度的猜想。

令 $S=n\log n$，这样总的时间复杂度为 $O(S\log S)$，可能无法通过这题。但是，我们只要对每个区间处理的时候先按上面的步骤合并一次，再将合并出的区间合并第二次，就会大大减少区间的个数。经过实测，两次合并后的区间个数小于 $10^6$ 个，可以非常轻松地通过。不过我也不太清楚这里的复杂度是否有所改变，因为这里合并后的区间个数居然是 $O(n)$ 级别的，希望大家可以一起分析一下。下面给出代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5,M=1e6,inf=2e18;
struct node{
	int l,r;
}b[M],c[N];
bool cmp(node a,node b){
	return a.l<b.l;
}
int n,m,v,a,l,r,L[N+10],R[N+10],cnt;
signed main(){
	scanf("%lld%lld%lld",&n,&m,&v);
	memset(R,127,sizeof R);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		L[a]=R[a]=a;
	}
	for(int i=1;i<=N;i++){
		L[i]=max(L[i],L[i-1]);
	}
	for(int i=N;i>=1;i--){
		R[i]=min(R[i],R[i+1]);
	}
	c[0]={inf,inf};
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&l,&r);
		int len=r-l,cnt0=0;
		for(int ll=1;ll<=N;ll+=len+1){
			int rr=ll+len;
			if(rr>N)rr=N;
			int a1=R[ll],a2=L[rr];
			if(a1>rr||a2<ll)continue;
			int LL=l-a2,RR=r-a1;
			if(RR<1)continue;
			if(LL<1)LL=1;
			if(LL>v)continue;
			if(RR>v)RR=v;
			c[++cnt0]={LL,RR};
		}
		int lll=c[cnt0].l,rrr=c[cnt0].r;
		for(int j=cnt0-1;j>=0;j--){
			if(c[j].r<=rrr)continue;
			if(c[j].l<=rrr)rrr=c[j].r;
			else{
				b[++cnt]={lll,rrr};
				lll=c[j].l,rrr=c[j].r;
			}
		}
	}
	sort(b+1,b+1+cnt,cmp);
	int ans=v,mx=0;
	for(int i=1;i<=cnt;i++){
		if(b[i].r<=mx)continue;
		if(b[i].l<=mx)ans-=(b[i].r-mx);
		else ans-=(b[i].r-b[i].l+1);
		mx=b[i].r;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Rain_chr (赞：2)

### Part 1 前言

怎么大家都是双 $\log$？我本不想写题解的，但是看到题解复杂度都是双 $\log$ 就来发一篇除排序外可视作线性的题解。

### Part 2 解法

首先将 $a$ 从小到大排序去重，对于一个区间 $[l_i,r_i]$ 和一个数 $a_j$，$\forall k \in [l_i-a_j,r_i-a_j]$ 都是不合法的。

直接暴力做显然是不对的，但是考虑到有很多 $a_i$ ban 掉的位置是有交的，我们可以并作一个区间再来处理。考虑如下做法：

用并查集维护 ban 掉的值域并是一个区间的连续段，从小到大枚举每一个长度，先合并掉所有由无交变成有交的相邻两个连续段，然后对于每一个连续段求出 ban 掉的区间，最后把所有 ban 掉的区间求并。

乍一看这样子错飞了，但是我们可以考虑相邻两个数 $a_i,a_{i+1}$ 在什么情况下两个元素 ban 掉的区间无交。当 $l-a_i>r-a_{i+1}$ 时，也就是 $a_{i+1}-a_i>r-l$ 时，这两个元素的区间才是无交的。而所有时刻连续段的总数就是可以视作所有时刻相邻两个数区间无交的数量，也就是 $O(\sum a_{i+1}-a_i)=O(V)$，所以总连续段个数就是 $O(V)$ 的，上述看似暴力的做法实质上是 $O(V\log V)$ 的。

### Part 3 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int a[N];
int n,m,v;
struct DSU
{
    int fa[N];
    int find(int x)
    {
        if(fa[x]==x) return x;
        return fa[x]=find(fa[x]);
    }
    void clear(){for(int i=1;i<=n+1;i++) fa[i]=i;}
    void merge(int x,int y){fa[find(x)]=find(y);}
}T;
vector<int> upd[N];
struct node{int l,r;};
vector<node> vt,ask[N];
bool cmp(node x,node y){return x.l<y.l;}
void add(int l,int r)
{
    l=max(l,1ll),r=min(r,v);
    if(l>r) return ;
    vt.push_back((node){l,r});
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>v;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    n=unique(a+1,a+1+n)-a-1;
    T.clear();
    for(int i=1;i<n;i++) upd[a[i+1]-a[i]].push_back(i);
    for(int i=1;i<=m;i++)
    {
        int l,r;
        cin>>l>>r;
        ask[min(r-l,n)].push_back((node){l,r});
    }
    for(int i=0;i<=n;i++)
    {
        for(auto j:upd[i]) T.merge(j,j+1);
        for(auto j:ask[i])
        {
            int l=1;
            while(l<=n)
            {
                int r=T.find(l);
                add(j.l-a[r],j.r-a[l]),l=r+1;
            }
        }
    }
    sort(vt.begin(),vt.end(),cmp);
    int ans=0,r=0;
    for(auto i:vt)
    {
        if(i.l<=r) ans+=max(r,i.r)-r,r=max(r,i.r);
        else ans+=i.r-i.l+1,r=i.r;
    }
    cout<<v-ans<<'\n';
    return 0;   
}

```

---

## 作者：快斗游鹿 (赞：0)

先考虑合法的 $k$ 要满足什么条件，显然对于任意 $i,j,1\le i\le n,1\le j\le m$，都要有 $k<l_j-a_i$ 或 $k>r_j-a_i$。这不太好做，但可以发现不合法的 $k$ 判定条件会比较优美，即存在 $i,j,1\le i\le n,1\le j\le m$，满足 $k\in [l_j-a_i,r_j-a_i]$。朴素的想法就是直接求区间并，但是区间个数有 $O(nm)$ 个，无法接受。

注意到 $a$ 的值域并不大，先对 $a$ 排序并去重。进一步观察发现，对于一个长为 $len$ 的区间，如果 $a_{i+1}-a_i\le len$，那么 $[l_j-a_i,r_j-a_i],[l_j-a_{i+1},r_j-a_{i+1}]$ 可以合并成一个区间，所以按 $len$ 从小往大扫，一边合并区间即可，这样最后的区间个数是可以接受的，大概估计一下，因为 $len$ 两两不同，所以最多也就只有 $\dfrac{n}{1}+\dfrac{n}{2}+\dots+\dfrac{n}{n}=O(n\ln n)$ 个区间，但事实上远远不满，因此跑的飞快。理论总时间复杂度是 $O(n\ln n\log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18;
bool M1;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N=5e5+5;
struct Node{
	int l,r,len;
}e[N];
struct node{
	int l,r;
}p[N];
int n,m,v,a[N];
vector<pair<int,int> >b;
bool cmp(Node xxx,Node yyy){
	return xxx.len<yyy.len;
}
void cl(int len){
	vector<pair<int,int> >c;
	for(int i=0;i<b.size();i++){int pos=i;
		for(int j=i+1;j<b.size();j++){
			if(b[j].first-b[j-1].second>len)break;
			pos=j;
		}
		c.push_back({b[i].first,b[pos].second});
		i=pos;
	}
	swap(b,c);
}
int lsh[N<<4],len,d[N<<4];
int getlsh(int x){
	return lower_bound(lsh+1,lsh+1+len,x)-lsh;
} 
int G(int x){
	if(x<1)return 1;
	return x;
}
bool M2;
signed main(){
    //freopen("data.in","r",stdin);
    n=read();m=read();v=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=m;i++)e[i].l=read(),e[i].r=read(),e[i].len=e[i].r-e[i].l+1;
    sort(e+1,e+1+m,cmp);
    sort(a+1,a+1+n);n=unique(a+1,a+1+n)-a-1;
    for(int i=1;i<=n;i++)b.push_back({a[i],a[i]});
    int ccc=0;
	for(int i=1;i<=m;i++){
    	cl(e[i].len);
    	for(int j=0;j<b.size();j++){
    		p[++ccc].l=e[i].l-b[j].second;
    		p[ccc].r=e[i].r-b[j].first;
    		//cerr<<"add:"<<p[ccc].l<<" "<<p[ccc].r<<'\n';
    		//cerr<<"?"<<b[j].first<<" "<<b[j].second<<'\n';
		}
	}
	for(int i=1;i<=ccc;i++){
		if(p[i].l>v)continue;
		if(p[i].r<1)continue;
		p[i].r=min(p[i].r,v);
		lsh[++len]=G(p[i].l),lsh[++len]=G(p[i].r+1);
		//cout<<G(p[i].l)<<" "<<G(p[i].r+1)<<'\n';
	}
	sort(lsh+1,lsh+1+len);len=unique(lsh+1,lsh+1+len)-lsh-1;
	for(int i=1;i<=ccc;i++){
		if(p[i].l>v)continue;
		if(p[i].r<1)continue;
		d[getlsh(G(p[i].l))]++;
		d[getlsh(G(p[i].r+1))]--;
	}
	int ans=v;
	for(int i=1;i<=len;i++)d[i]+=d[i-1];
	for(int i=1;i<=len;i++){
		if(d[i])ans-=(lsh[i+1]-lsh[i]);//,cout<<lsh[i+1]<<" "<<lsh[i]<<'\n';
	}
	cout<<ans<<'\n';
    cerr<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC<<"s"<<endl;
    cerr<<"Memory:"<<(&M1-&M2)/1024/1024<<"MB"<<endl;
    return 0;
}

```

---

## 作者：wxzzzz (赞：0)

### 思路

考虑所有 $k$ 应满足的条件：$\forall i,j:a_i+k\notin[l_j,r_j]$，即 $\forall i,j:k\notin[l_j-a_i,r_j-a_i]$。

也就是说，不合法 $k$ 的集合是每条线段向左分别平移 $a_1,a_2,\dots,a_n$ 个单位构成的并。

考虑这个平移的过程，若平移时区间数没有增加，只需拓展端点，是好维护的。令 $V=\max\{a_i\}$，则新增区间最多只会有 $\lfloor\cfrac{V}{r_j-l_j+1}\rfloor$ 个。又因为区间长度互不相同，所以区间个数在 $O(V\ln V)$ 级别。

可以二分找到下一个新区间，最后把所有区间取并即可。复杂度 $O(V\ln V\log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[500005];
long long lim;
vector<pair<long long, long long>> sg;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> lim;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    n = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= m; i++) {
        long long l, r, tl, tr;
        cin >> l >> r;
        l -= a[1], r -= a[1];
        int j = 1, k;
        while (j <= n) {
            k = lower_bound(a + j + 1, a + n + 1, a[j] + r - l + 2) - a;
            tl = max(l - (a[k - 1] - a[j]), 1ll), tr=min(r, lim);
            if (tl <= tr) {
                sg.push_back({tl, tr});
                if (sg.back().first == 1)
                    break;
            }
            l -= a[k] - a[j], r -= a[k] - a[j], j = k;
        }
    }
    sort(sg.begin(), sg.end());
    sg.push_back({1e18, 0});
    long long pl = 0, pr = -1, ans = lim;
    for (auto i: sg) {
        if (i.first > pr + 1) {
            ans -= pr - pl + 1;
            pl = i.first, pr = i.second;
        }
        else pr = max(pr, i.second);
    }
    cout << ans;
    return 0;
}
/*
2 1 1
2 3 
1 1

1

5 1 3
2 2 1 3 3 
4 4

0

1 5 2
1 
5 5
2 3
4 5
5 5
2 5

0
*/
```

---

