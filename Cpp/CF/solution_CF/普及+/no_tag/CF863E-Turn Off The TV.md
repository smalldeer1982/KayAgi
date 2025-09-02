# Turn Off The TV

## 题目描述

Luba 有 $n$ 台电视，并且她知道每台电视的工作时间是从 $l$ 到 $r$。现在 Luba 想要关掉一些电视，使得播放电视节目的时间点不少于关掉这些电视之前。请你帮助 Luba，告诉她可以关闭哪些电视，若任何一台都不能关闭，输出 `-1`。

## 样例 #1

### 输入

```
3
1 3
4 6
1 7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
0 10
0 10
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
1 2
3 4
6 8
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3
1 2
2 3
3 4
```

### 输出

```
2
```

# 题解

## 作者：_edge_ (赞：8)

~~数据结构？不存在的！~~

这里事 $O(n)$ 的做法呢。

考虑一个线段，把它映射到一个数轴上，我们需要做的就是统计哪一个线段会被某些线段的并集覆盖掉。

那么也就是说，如果我们将所有线段 $[l,r]$ 都 $+1$，这样之后如果某个线段 $[l,r]$ 事里面的数全都是 $\ge 2$ 的，那么这个线段就合法了。

这个 …… 可以用动态开点权值线段树乱杀，也可以离散化之后用树状数组来维护。

但是难道就一定要数据结构么？

当然不是，我们看到这个区间它实际上事静态的，没有修改操作，并且询问事在线段给出之后，区间加，单点查询，想到了什么？

是不是差分？

对于线段 $[l,r]$ ，在 $f_l$ 处 $+1$，在 $f_{r+1}$ 处 $-1$，然后就可以了。

当然要记得离散化。

但是我们有一个很坑的点，就是 ……

```cpp
3
3 10 
1 5
9 11
```

$[3,10]$ 中间有一段没被覆盖掉，但是！它居然被算进了贡献，这就错掉了。

所以我们在离散化的时候，要注意把要离散化的数值全部加上一，然后再扔到离散化的数组里面。

然后我们这时候要查询的即为 $[l,r]$ 区间是否全都 $\ge 2$，这个操作很好维护，就记录 $l_r$ 表示 $r$ 为左端点，向右延伸，伸到哪里事最大的一段且他们当中数值 $\ge 2$，注意特判 $l=r$ 的情况，以及数组要开大。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF=1e6+5;
int n,l[INF],r[INF],cnt[INF],d[INF],ll[INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>l[i]>>r[i];
		cnt[++cnt[0]]=l[i];
		cnt[++cnt[0]]=r[i];
	}
	sort(cnt+1,cnt+1+cnt[0]);
	int res=unique(cnt+1,cnt+1+cnt[0])-cnt-1;
	for (int i=2;i<=cnt[0];i++)
		if (cnt[i]!=cnt[i-1]) cnt[++res]=cnt[i-1]+1;
	sort(cnt+1,cnt+1+res);
	res=unique(cnt+1,cnt+1+res)-cnt-1;
	for (int i=1;i<=n;i++) {
		l[i]=lower_bound(cnt+1,cnt+1+res,l[i])-cnt;
		r[i]=lower_bound(cnt+1,cnt+1+res,r[i])-cnt;
		d[l[i]]++;d[r[i]+1]--;
	}
	for (int i=1;i<=res;i++) {
		d[i]+=d[i-1];
//		cout<<d[i]<<" "<<ll[i-1]<<" ?\n";
		if (d[i]>=2 && d[i-1]>=2) ll[i]=ll[i-1];
		else ll[i]=i;
	}
//	cout<<d[r[3]]<<" ???\n";
	for (int i=1;i<=n;i++) {
		if (ll[r[i]]<=l[i]) {
			if (l[i]==r[i] && d[l[i]]<2) continue;
			cout<<i<<"\n";
			return 0;
		}
	}
	cout<<"-1\n";
	return 0;
}
```


---

## 作者：Flanksy (赞：3)

### 离散化

------------

给出 $n$ 条线段 $[l_i,r_i]$，对于每一条线段 $x$ 判断除 $x$ 以外线段的并是否等于原有 $n$ 条线段的并。

离散给出线段的左右端点，使用差分统计每个位置被覆盖的次数。对每个线段询问其包含的所有位置被覆盖次数的最小值。最小值大于等于 $2$ 说明这条线段可被删除，输出线段编号，使用 ST 表解决静态区间最小值问题。

令输入的线段左端点为 $l_i$，右端点为 $r_i$，离散后左端点为 $ld_i$，右端点为 $rd_i$。**在离散化时加入所有 $r_i+1$ 的值才能正确统计区间最小值**，因为差分操作的影响必须在真实位置 $r_i+1$ 处结束。对离散后序列差分时如果不加入 $r_i+1$，差分的实际生效范围将是 $[ld_i,rd_{i+1}-1]$，映射回数轴很可能不为 $[l_i,r_i]$ 从而导致错误。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt,l[200001],r[200001],p[600001],lo[600001],s[23][600005];
inline int min(int x,int y){return x<y ? x:y;}
int query(int l,int r){
    int o=lo[r-l+1];
    return min(s[o][l],s[o][r-(1<<o)+1]);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&l[i],&r[i]);
        p[++cnt]=l[i],p[++cnt]=r[i];
        p[++cnt]=r[i]+1;
    }
    sort(p+1,p+cnt+1);
    cnt=unique(p+1,p+cnt+1)-p-1;
    for(int i=1;i<=n;i++){
        l[i]=lower_bound(p+1,p+cnt+1,l[i])-p;
        r[i]=lower_bound(p+1,p+cnt+1,r[i])-p;
        s[0][l[i]]++,s[0][r[i]+1]--;
    }
    for(int i=1;i<=cnt;i++) s[0][i]+=s[0][i-1];
    for(int i=1;1<<i<=cnt;i++)
        for(int j=1;j+(1<<i)-1<=cnt;j++)
            s[i][j]=min(s[i-1][j],s[i-1][j+(1<<i-1)]);
    for(int i=2;i<=cnt;i++) lo[i]=lo[i>>1]+1;
    for(int i=1;i<=n;i++) if(query(l[i],r[i])>=2)
        return printf("%d\n",i),0;
    puts("-1");
    return 0;
}
```


---

## 作者：yanghanyv (赞：2)

## 题意
给出若干条线段，询问一条线段是否能被其他线段的组合完全覆盖。

## 解法

### 一、线段树
如果擅长数据结构题，肯定一眼就看出这是个线段树模板题。  
具体思路是用线段树维护区间内被覆盖次数的最小值，对每条线段依次进行询问，当询问结果为 $1$ 时，就找到了答案。  
时间复杂度 $\Theta(n\log{n})$ 。

### 二、扫描线
线段树毕竟太麻烦了，我们考虑换一种思路。  
可以发现只需考虑线段的两个端点的覆盖次数，于是把一条线段拆分为两个端点，这种思路在很多题中都可以用，比如[P7913 [CSP-S 2021] 廊桥分配](https://www.luogu.com.cn/problem/P7913)。  
于是，我们对端点坐标排序，然后用扫描线扫一遍。在扫的同时用 set 维护一下能够扫到的线段。当 set 的大小为 $1$ 时，就找到了答案。  
时间复杂度 $\Theta(n\log{n})$ 。

## 代码
这里附上扫描线解法的代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,l,r;
bool vis[N];
set<int> S;
struct node{
	int x,id,t;
	bool operator < (const node &node1) const{
		return x<node1.x;
	}
}p[2*N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l,&r);
		p[2*i-1].x=l;
		p[2*i-1].t=1;
		p[2*i].x=r+1;//这个+1是一个关键，相当于取[l,r+1)
		p[2*i].t=-1;
		p[2*i-1].id=p[2*i].id=i;
	}
	sort(p+1,p+2*n+1);//按端点坐标排序
	for(int i=1;i<=2*n;i++){
		if(p[i].t==1){
			S.insert(p[i].id);//加入线段
		}else{
			S.erase(p[i].id);//删除线段
		}
		if(p[i+1].x!=p[i].x){
			if(S.size()==1){
				vis[*S.begin()]=1;//判断是否为答案
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			printf("%d",i);
			exit(0);
		}
	}
	printf("-1");
	return 0;
}
```


---

## 作者：RainFestival (赞：2)

~~抢题解一血~~

对于我们这道题目

设$val_i$为第$i$时刻有多少台电视机工作

对于每一台电视机

我们将$val_x,x\in[l,r]$通通$+1$

最后一遍找，对于每个$i$,如果$\min\limits_{k=l_i}^{r_i} val_k\ge2$,即第$i$台电视的控制区间都有电视可以替代，那么答案就是$i$

如果找完了还没有找到一个满足条件的$i$,那么没有一台电视可以关掉

我们用动态开点线段树实现

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#define sz 1000000020
#include<cstdlib>
struct node
{
	int ls,rs,val,tag;
};
node a[10000005];
int n,l[200005],r[200005],cnt=1;
void pushup(int k){a[k].val=std::min(a[a[k].ls].val,a[a[k].rs].val);}
void tg(int k,int l,int r,int v){a[k].val=a[k].val+v;a[k].tag=a[k].tag+v;}
void pushdown(int k,int l,int r)
{
	if (!a[k].tag) return;
	int mid=(l+r)/2;
	tg(a[k].ls,l,mid,a[k].tag);
	tg(a[k].rs,mid+1,r,a[k].tag);
	a[k].tag=0;
}
void add(int k,int l,int r,int x,int y,int v)
{
	if (x<=l&&r<=y)
	{
		tg(k,l,r,v);
		return;
	}
	int mid=(l+r)/2;
	if (!a[k].ls&&!a[k].rs) a[k].ls=++cnt,a[k].rs=++cnt;
	pushdown(k,l,r);
	if (x<=mid) add(a[k].ls,l,mid,x,y,v);
	if (mid<y) add(a[k].rs,mid+1,r,x,y,v);
	pushup(k);
}
int query(int k,int l,int r,int x,int y)
{
   	if (x<=l&&r<=y) return a[k].val;
	int mid=(l+r)/2,ans=2000000000;
	if (!a[k].ls&&!a[k].rs) a[k].ls=++cnt,a[k].rs=++cnt;
	pushdown(k,l,r);
	if (x<=mid) ans=std::min(ans,query(a[k].ls,l,mid,x,y));
	if (mid<y) ans=std::min(ans,query(a[k].rs,mid+1,r,x,y));
	return ans;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		add(1,1,sz,l[i]+1,r[i]+1,1);
	}
	for (int i=1;i<=n;i++)
		if (query(1,1,sz,l[i]+1,r[i]+1)>=2)
	    {
			printf("%d\n",i);
			return 0; 
		}
	puts("-1");
	return 0;
}
```



---

## 作者：Priestess_SLG (赞：0)

先对值域离散化，然后建树记录每一个点被区间覆盖的次数。

枚举每一个区间，若这个区间中每一个点都被至少覆盖了两次那么这个区间就合法。考虑先差分+前缀和求出每一个点被覆盖的次数，然后用线段树维护区间最小值即可。时间复杂度为 $O(n\log n)$。

[代码](https://codeforces.com/contest/863/submission/280974547)

---

## 作者：_lgh_ (赞：0)

**[CF863E](https://www.luogu.com.cn/problem/CF863E)**


*2000.

提供一个除了离散化之外线性的做法。

首先考虑一个段能被覆盖的充要条件是这个段每个位置被覆盖次数都 $\ge 2$，这个东西差分一下就能维护。

但是发现值域太大了，需要离散化。

考虑每次修改改的是 $a_l,a_{r+1}$，所以注意离散化的时候需要把 $l,r,r+1$ 都加入数组，因为这样才能保证差分不出错。

代码：

```cpp
//class ST...

void solve() {
    int n; rd(n);
    vi lsh; vector<pii>a(n+1);
    for(int i=1; i<=n; i++) rd(a[i].fst,a[i].sec),lsh.pb(a[i].fst),lsh.pb(a[i].sec),lsh.pb(a[i].sec+1);
    sort(all(lsh)),unique(all(lsh));
    for(int i=1; i<=n; i++)
        a[i].fst=lower_bound(all(lsh),a[i].fst)-lsh.begin(),
        a[i].sec=lower_bound(all(lsh),a[i].sec)-lsh.begin();
    vi sum(lsh.size()+1,0);
    debug(a);
    for(int i=1; i<=n; i++) sum[a[i].fst]++,sum[a[i].sec+1]--;
    for(int i=1; i<sum.size(); i++) sum[i]+=sum[i-1];
    debug(sum);
    assert(*min_element(all(sum))>=0);
    ST s(sum);
    for(int i=1; i<=n; i++)
        if(s.get(a[i].fst,a[i].sec)>=2) {
            cout<<i<<endl; return;
        }
    cout<<"-1"<<endl;
}
```

---

## 作者：ifffer_2137 (赞：0)

## 题意
给定 $n$ 条线段，输出任意一条被其他线段完全覆盖的线段，无解输出 $-1$。
## 解法
看到线段覆盖，很自然地想到按右端点升序排序。

考虑一条线段被覆盖的条件。两种情况：一种是完全被覆盖在另一条线段内，这显然是 naive 的；另一种是在已排序的情况下，由前一条线段和后面所有线段当中左端点最小的线段共同覆盖，即 $\min_{j=i+1}^{n}l_{j}\le r_{i-1}+1$，其中 $\min_{j=i+1}^{n}l_{j}$ 这个东西我们显然可以用数据结构来优化，我比较懒所以就写了一棵线段树，实际上不带修线段树是没必要的。最终时间复杂度 ${O}(n\log_{2}{n})$，可以通过此题。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
inline void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x<10){putchar(48+x);return;}
    write(x/10),putchar((x+10)%10+48);
}
const int maxn=2e5+5;
int n;
struct seg{
	int id,l,r;
	bool operator < (const seg &x) const{
		return r==x.r?l>x.l:r<x.r;
	}
}a[maxn];
struct Segment_Tree{//线段树
	int minv[maxn*4];
	void build(int o,int l,int r){
		if(l==r){
			minv[o]=a[l].l;
			return;
		}
		int m=(l+r)/2;
		build(o*2,l,m);
		build(o*2+1,m+1,r);
		minv[o]=min(minv[o*2],minv[o*2+1]);
	}
	int query(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y){
			return minv[o];
		}
		int m=(l+r)/2,mn=inf;
		if(x<=m) mn=min(mn,query(o*2,l,m,x,y));
		if(y>m) mn=min(mn,query(o*2+1,m+1,r,x,y));
		return mn;
	}
}tr;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		a[i].id=i;
		a[i].l=read(),a[i].r=read();
	}
	sort(a+1,a+n+1);
	tr.build(1,1,n);
	a[0].r=-1;
	for(int i=1;i<=n;i++){
		int x=max(a[i].l,a[i-1].r+1);//两种情况合到一起了
		int y=tr.query(1,1,n,i+1,n);
		if(y<=x){
			write(a[i].id);
			putchar(10);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：Hellsing_Alucard (赞：0)

## [Turn Off The TV](https://www.luogu.com.cn/problem/CF863E)

>题意：给定 $n$ 个区间，判断是否有一个区间能够被其他区间完全覆盖。

我们可以转化一下，加入一个区间等价于把这个区间整体加一，询问这个区间能否够被其他区间完全覆盖理解为查询这个区间的最小值是否大于等于 $2$。

那么就是一个简单的线段树区间加，区间最小值，由于范围比较大，需要动态开点。

```cpp

struct node{
	int ls,rs,minl,tag;
}tr[N<<5];
int n,m,cnt=1;//一定要赋值成1
inline void push_up(int k){
	tr[k].minl=min(tr[tr[k].ls].minl,tr[tr[k].rs].minl);
}
inline void push_down(int k,int l,int r){
    if(tr[k].tag){
        if(!tr[k].ls)tr[k].ls=++cnt;
        if(!tr[k].rs)tr[k].rs=++cnt;
        tr[tr[k].ls].tag+=tr[k].tag;
       	tr[tr[k].rs].tag+=tr[k].tag;
        int mid=(l+r)>>1;
        tr[tr[k].ls].minl+=tr[k].tag;
        tr[tr[k].rs].minl+=tr[k].tag;
        tr[k].tag=0;
    }
}
inline void change(int &k,int l,int r,int x,int y,int val){
	if(!k)k=++cnt;
	if(x<=l&&r<=y) {
        tr[k].tag+=val;
		tr[k].minl+=val;
        return;
    }
    int mid=(l+r)>>1;
    push_down(k,l,r);
    if(x<=mid)change(tr[k].ls,l,mid,x,y,val);
    if(y>mid)change(tr[k].rs,mid+1,r,x,y,val);
    push_up(k);
}
inline int ask(int k,int l,int r,int x,int y){
    if(!k)return 0;
    if(x<=l&&y>=r)return tr[k].minl;
    push_down(k,l,r);
    int mid=(l+r)>>1,res=inf;
    if(x<=mid)res=min(res,ask(tr[k].ls,l,mid,x,y));
    if(y>mid)res=min(res,ask(tr[k].rs,mid+1,r,x,y));
    return res;
}
int L[N],R[N];
signed main(){
	n=read();
    int l,r;
    up(i,1,n){
        L[i]=read();R[i]=read();
        int tmp=1;
        change(tmp,0,mod,L[i],R[i],1);
    }
    up(i,1,n){
        int tmp=1;
        int t=ask(tmp,0,mod,L[i],R[i]);
        if(t>=2){
            cout<<i;
            return 0;
        }
    }
    cout<<-1;
    return 0;
}
```

---

