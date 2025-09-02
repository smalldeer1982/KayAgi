# [ABC274F] Fishing

## 题目描述

有 $n$ 条鱼在数轴上移动。

第 $i$ 条鱼在时刻 $0$ 时在位置 $x_i$ 处，价值为 $w_i$，将会以每时刻 $t_i$ 的速度向数轴正方向前进。

你是一个渔夫，你有感应河流的能力，你已经知晓所有鱼的 $x,w,t$ 属性。

你会选择一个时刻 $t$，在位置 $x$ 撒下一张长度为 $a$ 的网，所有在时刻 $t$ 时处于区间 $[x,x+a]$ 的鱼都会被你捕获。

你想求出你撒一次网能捕获的鱼的价值和的最大值。

## 说明/提示

对于所有数据，$1\leq n\leq 2\times 10^3,1\leq a,w_i,x_i,t_i\leq 10^4$。

Translate by Zek3L.

## 样例 #1

### 输入

```
3 10
100 0 100
1 10 30
10 20 10```

### 输出

```
111```

## 样例 #2

### 输入

```
3 10
100 100 100
1 10 30
10 20 10```

### 输出

```
100```

## 样例 #3

### 输入

```
4 10
1000 100 10
100 99 1
10 0 100
1 1 1```

### 输出

```
1110```

# 题解

## 作者：Missa (赞：6)

比较有趣的用点思维的题。

在学校和 DYS 一起推出来的题，庆祝 AT 复活写个题解。

感觉用无序列表列出自己思绪的过程很简洁扼要，但是行文节奏过快。介于我想重现自己今天上午的思路过程，这篇题解用对话体写出。

---------

师：现在，让我们看 abc274F。给定 $n$ 条鱼的初始位置、速度、重量，请任选一个时刻撒下一张长度为 $A$ 的网，最大化网中鱼的重量和。时刻与撒网端点都不必是整数。$n \leq 2000$

A：有初始位置，匀速增长，区间求值……我想到了 [P6405](https://www.luogu.com.cn/problem/P6405)！

B：P6405 要求的是恰好相等，相等具有传递性，但是网住没有传递性。能同时网住 AB 与能同时网住 BC 不意味着能同时网住 ABC。这个思路没法做下去。

师：我们已经迈出了第一步。想想看，为什么这个网看着难以处理？

A：时刻任意，位置任意，变量也太多了点！

B：但是 $n$ 仅有 $2000$，我们完全可以枚举其中一个再处理。

如果时间确定，能网住一条鱼的网的对应左端点是一个固定区间。如果位置确定，能网住一条鱼的下网时刻也是一个固定区间。问题变为：数轴上 $n$ 条线段，每条线段有权值，求一个点让覆盖其的线段的权值和最大。这可以用线段树+离散化 $O(n \log n)$ 解决。$O(n^2 \log n)$ 是能接受的，只需要 $O(n)$ 枚举其中一个变量。枚举哪个好呢？

A：我发现了一个性质。一定存在渔网左端点位于一条鱼上时的最优解。看起来，我们可以枚举那条鱼。

B：那么我们需要让位置确定。把其它所有鱼的速度减去这条鱼的速度，这条鱼就会相对静止，也就是这条鱼的位置不变，即下网左端点不变。运用上面说的方法，我们就能在 $O(n^2 \log n)$ 内解决问题！

事实上，我自己开始看错题以为 $x$ 给定，然后直接想到了确定一个数的做法，再结合 DYS 发现的性质，拼在一起，居然做完了题。有意识地简化问题，有时是通往正解的道路。

---

## 作者：Ratio_Y (赞：5)

## 思路
首先挺显然的，最优策略时开始撒网的地点肯定有一条鱼。

发现 $n\le 2000$，所以考虑枚举左端点的鱼，然后对剩下的鱼求出有贡献的答案范围，复杂度是 $O(n^2)$ 的。

## 细节

对于速度相同的两条鱼，显然只看初始位置就好了。

实现上，为了防止精度出现误差，存位置的变量尽量使用 double 类型。

对于两条鱼，有 $\Delta s=x_2-x_1+t\times \left(v_2-v_1\right)$，做出贡献的范围为 $\Delta s\in \left[0,a\right]$，那么移项可得 $t\in\left[\frac{x_1-x_2}{v_2-v_1},\frac{a+x_1-x_2}{v_2-v_1}\right]$，这样我们便可以依据时间算出贡献，存储用个 map 就好。

## Code：
```cpp
#include<bits/stdc++.h>

using namespace std;
const int Ratio=0;
const int N=2e4+5;
const double eps=1e-9;

int n,m,ans=-1e9;
struct rmm
{
    int w,x,v;
}fis[N];
map<double,int>mp;

namespace Wisadel
{
    short main()
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d%d%d",&fis[i].w,&fis[i].x,&fis[i].v);
        for(int i=1;i<=n;i++)
        {
            mp.clear();
            int w=fis[i].w,x=fis[i].x,v=fis[i].v;
            int now=w;
            for(int j=1;j<=n;j++)
            {
                if(i==j) continue;
                if(fis[j].v==v&&fis[j].x>=x&&fis[j].x<=x+m)
                {// 速度相同的情况
                    now+=fis[j].w;
                    continue;
                }
                double fw1=1.0*(x-fis[j].x)/(fis[j].v-v),fw2=1.0*(m+x-fis[j].x)/(fis[j].v-v);
                if(fw1>fw2) swap(fw1,fw2);
                // 左右边界
                if(fw2>=0)
                {
                    if(fw1<1.0*0) fw1=1.0*0;
                    mp[fw1]+=fis[j].w,mp[fw2+eps]-=fis[j].w;
                    // 右边界 +eps 即为超出答案范围一点点的位置
                }
            }
            int anss=now;
            for(auto [a,b]:mp) now+=b,anss=max(anss,now);
            // 根据边界界定找最优答案
            ans=max(ans,anss);
        }
        printf("%d\n",ans);
        return Ratio;
    }
}
int main(){return Wisadel::main();}
```

完结撒花~

---

## 作者：翼德天尊 (赞：3)

场上没时间打了，赛后补的，其实很简单。

注意到每一条鱼实际上就是一个向量，而对于任意两条鱼，我们都可以知道他们距离在 $a$ 以内时的时间段，且该时间段一定唯一。

那么假设我们确定了一条鱼，其他鱼与这条鱼距离在 $a$ 以内的时间段一定都可以被算出来，我们将端点离散化一下，就变成了一个线段覆盖，求哪一时刻总线段的价值最大，这显然是好做的，随便用一个数据结构即可维护。

所以我们枚举每一条鱼，将这条鱼的所有相关时间段全部算出来，最后将所有答案取最大值即可。注意不要忘记考虑只覆盖一条鱼的情况。

时间复杂度 $O(n^2\log n)$.

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2005;
const double eps=1e-6;
int n,ltot,ans;
double lsh[N*N*2],a;
struct node{
	double x,v;
	int w;
}p[N];
struct node1{
	double l,r;
	int w;
	node1 (double l=0,double r=0,int w=0)
		:l(l),r(r),w(w){}
};
vector<node1> ve[N];
struct node2{
	int c[N*N*2];
	int lowbit(int x){
		return x&(-x);
	}
	void add(int x,int k){
		for (int i=x;i<=ltot;i+=lowbit(i))
			c[i]+=k;
	}
	int query(int x){
		int sum=0;
		for (int i=x;i;i-=lowbit(i))
			sum+=c[i];
		return sum;
	}
	void clear(int x){
		for (int i=x;i<=ltot;i+=lowbit(i))
			c[i]=0;
	}
}S;
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
} 
bool cmp(node1 x,node1 y){
	return x.r>y.r;
}
int main(){
	n=read(),a=read();
	for (int i=1;i<=n;i++){
		p[i].w=read(),p[i].x=read(),p[i].v=read();
		ans=max(ans,p[i].w);
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (i!=j){
				if (p[i].v==p[j].v){
					if (p[i].x-p[j].x<=a&&p[i].x-p[j].x>=0)
						lsh[++ltot]=0,lsh[++ltot]=1e9,ve[i].push_back(node1(0,1e9,p[j].w));
				}else{
					double l=(-p[i].x+p[j].x)/(p[i].v-p[j].v),r=(a-p[i].x+p[j].x)/(p[i].v-p[j].v);
					if (p[i].v<p[j].v) swap(l,r);
					l=max(l,0.0);
					lsh[++ltot]=l,lsh[++ltot]=r;
			//		cout<<l<<" "<<r<<" "<<i<<" "<<j<<"\n";
					if (l<=r+eps) ve[i].push_back(node1(l,r,p[j].w));
				}
			}
		}
		sort(ve[i].begin(),ve[i].end(),cmp);
	}
	sort(lsh+1,lsh+1+ltot);
	ltot=unique(lsh+1,lsh+1+ltot)-lsh-1;
	for (int i=1;i<=n;i++){
		int len=ve[i].size();
		for (int j=0;j<len;j++)
			ve[i][j].l=lower_bound(lsh+1,lsh+1+ltot,ve[i][j].l)-lsh,
			ve[i][j].r=lower_bound(lsh+1,lsh+1+ltot,ve[i][j].r)-lsh;
	}
	for (int i=1;i<=n;i++){
		int len=ve[i].size();
		for (int j=0;j<len;j++){
		//	cout<<ve[i][j].l<<" "<<ve[i][j].r<<" "<<i<<"\n";
			S.add(ve[i][j].l,ve[i][j].w);
			int sum=S.query(ve[i][j].r);
			ans=max(ans,sum+p[i].w);
		}
		for (int j=0;j<len;j++) S.clear(ve[i][j].l);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：2)

有趣。

对于既要选时刻，又要选位置，很复杂。

我们考虑枚举一个，贪心定下另外一个。  
但是没有有限的供枚举。

发现性质：最优时渔网的左端一定在一条鱼上。

此时网的位置可以枚举了。  
考虑贪心定下时刻。

考虑：当渔网位置固定时，一条鱼能被捕捉当且仅当其在什么时刻。  
这是是小学奥数追及问题。~~只是细节多了一点~~

然后就转化为在时间轴上有若干线段，每条线段带权，你选一个点，使得所有覆盖该点的线段和最大。

离散化扫一遍即可。

时间复杂度 $\mathcal{O(n^2\log n)}$。

细节看代码。

```cpp
il pdb F(int a,int b)//在 a 下网,对于 b 的捕捉区间 
{
	if(a[v]==b[v])	return a[x]<=b[x]&&b[x]<=a[x]+m?pdb{0,1e9}:pdb{-1,-1};
	db dx=x[b]-x[a],dv=v[a]-v[b],l=sd max(dx/dv,.0),r=sd max((dx-m)/dv,.0);
	if(x[b]==x[a]+m&&v[a]<v[b]) return {0,0};
	return l||r?pdb{sd min(l,r),sd max(l,r)}:pdb{-1,-1};
}
il int Calc(int cur)
{
	int s=0,res=0;
	a.clear();
	for(int i=1;i<=n;++i)
	{
		auto x=F(cur,i);
		if(x.x==-1&&x.y==-1) continue;
		a.push_back({x.x,w[i]}),a.push_back({x.y,-w[i]});
	}
	sd stable_sort(begin(a),end(a),[](pdi a,pdi b){return a.x==b.x?a.y>b.y:a.x<b.x;});
	for(pdi x:a) s+=x.y,cx(res,s);
	return res;
}
void Solve()
{
	rd(n,m);
	for(int i=1;i<=n;++i) rd(w[i],x[i],v[i]);
	for(int i=1;i<=n;++i) cx(ans,Calc(i));
	wrt(ans);
	return;
}
```

[$\color{green}\checkmark$](https://atcoder.jp/contests/abc274/submissions/43067608)。

---

## 作者：Charlie_ljk (赞：2)

发现 $n$ 很小有很多操作空间。

显然对于一次捕捞，其左端点紧挨着一只鱼是最优的，这样还有可能在右面多捞几只。

所欲枚举左端点是那一条鱼，那么对于其他的鱼定义其在范围内的时刻为区间 $[l_i,r_i]$，处理完之后将其按照左端点排序扫一遍即可。

可以使用堆，将其右端点为第一关键字扔进去，加入新决策时将右端点小于当前左端点的排除即可，同时更新答案。

处理其合法时刻区间 $[l_i,r_i]$ 的时候细节比较多，当时打的时候因为少取了一个等挂分了，同时 double 不要直接进行大小比较，要用 eps。

复杂度 $O(n^2\log n)$，开 O2 和不开 O2 区别挺大的。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=2e3+10,M=4e6+10;
const double eps=1e-10;
template<typename Tp> inline void read(Tp&x)
{
    x=0;register bool z=true;
    register char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
    for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
    x=(z?x:~x+1);
}
template<typename Tp> inline void wt(Tp x)
{if(x>9)wt(x/10);putchar((x%10)+'0');}
template<typename Tp> inline void write(Tp x)
{if(x<0)putchar('-'),x=~x+1;wt(x);}
int n,m,tot,w[N],x[N],v[N],ans;
struct aa {double l,r; int w;}e[N];
bool cmp(aa a,aa b) {return a.l-b.l<eps;}
priority_queue<pair<double,int> >q;
signed main()
{
    read(n),read(m);
    for(int i=1;i<=n;i++) 
        read(w[i]),read(x[i]),read(v[i]);
    for(int i=1;i<=n;i++)
    {
        tot=0;
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            if(x[j]<x[i]&&v[j]<=v[i]) continue;
            if(x[j]>x[i]+m&&v[j]>=v[i]) continue;
            double vji=(double)(v[j]-v[i]);
            double vij=-vji;
            double xij=(double)(x[i]-x[j]);
            double xji=-xij;
            double ximj=(double)(x[i]+m-x[j]);
            double xjim=-ximj;
            double l,r;
            if(x[j]<x[i]) l=xij/vji;
            else 
            {
                if(x[j]>x[i]+m)
                    l=xjim/vij;
                else l=0;
            }
            if(v[i]==v[j]) r=1e11;
            else if(v[j]>v[i]) r=ximj/vji;
            else if(v[j]<v[i]) r=xji/vij;
            if(r-l<eps&&abs(r-l)>eps) continue;
            e[++tot]={l,r,w[j]};
        }
        sort(e+1,e+1+tot,cmp);
        int sum=w[i];
        ans=max(ans,sum);
        for(int j=1;j<=tot;j++)
        {
            while(!q.empty())
            {
                auto a=q.top();
                int x=a.second;
                double y=-a.first;
                if(y-e[j].l<eps&&abs(y-e[j].l)>eps)
                {
                    q.pop();
                    sum-=x;
                }
                else break;
            }
            sum+=e[j].w;
            q.push(make_pair(-e[j].r,e[j].w));
            ans=max(ans,sum);
        }
        while(!q.empty()) q.pop();
    }
    write(ans);
}
```

---

## 作者：Morax2022 (赞：1)

作为少数在模拟赛上直接切出的蓝题，特写一篇题解以表纪念。

# Solution
一个性质：撒网的时候，网的左端点一定有一条鱼（否则左端点与离它最近能捕到的鱼中间还有一段距离，显然不优）。

于是我们考虑枚举是哪条鱼，设当前鱼速度为 $v$，位置为 $x$，网的长度为 $l$，设下文中其他鱼的位置为 $y$。

考虑什么时候其他鱼有机会被捕到：
- 若 $y < x$ 处有条鱼速度为 $v_2$，此时鱼并不在网内，若 $v < v2$，这条鱼就会追上当前鱼，而后超过它。
- 若 $y > x + l$ 处有条鱼速度为 $v_3$，此时鱼并不在网内，若 $v > v3$，这条鱼就会被当前鱼追上，而后被超过。
- 若 $x \le y \le x + l$ 处有条鱼速度为 $v_4$，此时鱼在网内，无论相对于当前鱼往前或往后都会有一段时间在网内。

于是我们可以假设 $v = 0$，那么此时可以得出其他鱼相对此鱼的移速。结合上面的分析，我们也可以知道一条鱼有没有可能在网内，若有可能，可以得知其在网内的起始与终止时间。

再仔细想想，时间这个东西的大小是无关紧要的。我们可以将其离散掉并将时间轴作为使用数据结构的基础。对于每条能在网内的鱼，我们对于其起始与终止这段区间打上其价值，而后对于整条时间轴求出最大值便是答案。

最后，记得枚举每条鱼是相互独立的，我们要把数据结构清空掉，时间复杂度为 $O(n \log n)$。

# AC Code

```cpp
#include <bits/stdc++.h>
#define debug cout << "CCF\n";
//#define int long long
using namespace std;
const int maxn = 2e6 + 5;
struct fish{
	int pos, w, v;
}a[maxn], b[maxn];
int n, l;
struct Tim{
	double st, ed;
}T[maxn];
double now[maxn];
int cnt;
map<double, int> mp;
namespace Seg{
	struct seg{
		int l, r, val, tag;
	}t[maxn << 2];
	void pushup(int p){
		t[p].val = max(t[p << 1].val, t[p << 1 | 1].val);
	}
	void pushdown(int p){
		if (!t[p].tag) return;
		int l = t[p].l, r = t[p].r, mid = t[p].l + t[p].r >> 1;
		t[p << 1].val += t[p].tag, t[p << 1 | 1].val += t[p].tag;
		t[p << 1].tag += t[p].tag, t[p << 1 | 1].tag += t[p].tag; t[p].tag = 0;
	}
	void build(int l, int r, int p){
		t[p].l = l, t[p].r = r;
		if (l == r) return;
		int mid = l + r >> 1;
		build(l, mid, p << 1), build(mid + 1, r, p << 1 | 1);
	}
	void update(int l, int r, int p, int k){
		if (l <= t[p].l && r >= t[p].r) {
			t[p].tag += k; t[p].val += k;
			return;
		}
		pushdown(p);
		int mid = t[p].l + t[p].r >> 1;
		if (l <= mid) update(l, r, p << 1, k);
		if (r > mid) update(l, r, p << 1 | 1, k);
		pushup(p);
	}
	int query(int l, int r, int p){
		if (l <= t[p].l && r >= t[p].r) return t[p].val;
		int mid = t[p].l + t[p].r >> 1, ans = 0;
		pushdown(p);
		if (l <= mid) ans = max(ans, query(l, r, p << 1));
		if (r > mid) ans = max(ans, query(l, r, p << 1 | 1));
		return ans;
	}
}
using namespace Seg;
int ans = 0;
main(){
//	freopen("fishing.in", "r", stdin);
//	freopen("fishing.out", "w", stdout);
//	freopen("test.in", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> l; build(0, n * 2, 1);
	for (int i = 1; i <= n; i++) cin >> a[i].w >> a[i].pos >> a[i].v;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++) T[j].st = T[j].ed = 0, b[j] = {a[j].pos, a[j].w, a[j].v - a[i].v};
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (b[j].pos < b[i].pos && b[j].v > 0){
				T[j].st = (b[i].pos - b[j].pos) * 1.0 / b[j].v;
				T[j].ed = T[j].st + l * 1.0 / b[j].v;
				now[++cnt] = T[j].st, now[++cnt] = T[j].ed;
			}else if (b[j].pos > b[i].pos + l && b[j].v < 0){
				int v = abs(b[j].v);
				T[j].st = (b[j].pos - b[i].pos - l) * 1.0 / v;
				T[j].ed = T[j].st + l * 1.0 / v;
				now[++cnt] = T[j].st, now[++cnt] = T[j].ed;
			}else if (b[j].pos >= b[i].pos && b[j].pos <= b[i].pos + l){
				T[j].st = 0; int v = abs(b[j].v);
				if (!b[j].v) T[j].ed = 2e9;
				else if (b[j].v > 0) T[j].ed = (b[i].pos + l - b[j].pos) * 1.0 / v;
				else T[j].ed = (b[j].pos - b[i].pos) * 1.0 / v;
				now[++cnt] = T[j].st, now[++cnt] = T[j].ed;
			}
		}
		sort(now + 1, now + cnt + 1);
		int len = unique(now + 1, now + cnt + 1) - now - 1; cnt = 0;
		for (int j = 1; j <= len; j++) mp[now[j]] = j;
		for (int j = 1; j <= n; j++) T[j].st = mp[T[j].st], T[j].ed = mp[T[j].ed]; mp.clear();
		for (int j = 1; j <= n; j++) if ((i != j) && ((b[j].pos >= b[i].pos && b[j].pos <= b[i].pos + l) || (b[j].pos > b[i].pos + l && b[j].v < 0) || (b[j].pos < b[i].pos && b[j].v > 0))) update(T[j].st, T[j].ed, 1, b[j].w);
		ans = max(ans, query(0, n * 2, 1) + b[i].w);
		for (int j = 1; j <= n; j++) if ((i != j) && ((b[j].pos >= b[i].pos && b[j].pos <= b[i].pos + l) || (b[j].pos > b[i].pos + l && b[j].v < 0) || (b[j].pos < b[i].pos && b[j].v > 0))) update(T[j].st, T[j].ed, 1, -b[j].w);
	}
	cout << ans;
}
```

这是我的考场代码，有点冗长有点丑，请见谅！

---

## 作者：_xixi (赞：0)

很显然有一个贪心，网的左端一定会有一条鱼。

设最左边是第 $i$ 条鱼， $x=t \times t_i+x_i$，移项可得  $t=\dfrac{x-x_i}{t_i}$。

考虑对于第 $j$ 条鱼，第 $j$ 条鱼被捕获当且仅当 $x_j+t \times t_j \in [x, x+a]$。

再将 $t=\dfrac{x-x_i}{t_i}$ 带入并化简即可得到 $(\dfrac{t_j}{t_i}-1) \times x \in [\dfrac{t_j \times x_i}{t_i}-x_j,\dfrac{t_j \times x_i}{t_i}-x_j+a]$。

这个可以用数据结构维护，总时间复杂度为 $\Theta(n^2 \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 2005;
int n, m, ans;
long double b[maxn][2], T[maxn << 1];
bool vis[maxn];
struct nd{
	long double w, x, v;
}a[maxn];
struct node{
	int l, r, mx, laz;
}tree[maxn << 3];

void pushup(int p){tree[p].mx = max(tree[p << 1].mx, tree[p << 1 | 1].mx);}

void build(int p, int l, int r){
	tree[p].l = l, tree[p].r = r, tree[p].laz = 0, tree[p].mx = 0;
	if(l == r) return;
	int mid = l + r >> 1;
	build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
	pushup(p);
}

void pushdown(int p){
	if(tree[p].laz){
		int x = tree[p].laz;
		tree[p].laz = 0;
		tree[p << 1].laz += x;
		tree[p << 1 | 1].laz += x;
		tree[p << 1].mx += x;
		tree[p << 1 | 1].mx += x;
	}
} 

void update(int p, int l, int r, int op){
	if(l <= tree[p].l && tree[p].r <= r){
		tree[p].laz += op;
		tree[p].mx += op;
		return;
	}
	pushdown(p);
	int mid = tree[p].l + tree[p].r >> 1;
	if(l <= mid) update(p << 1, l, r, op);
	if(mid < r) update(p << 1 | 1, l, r, op);
	pushup(p);
}

void solve(auto v, auto x){
	int tot = 0;
	for(int i = 1; i <= n; i++){
		long double x1 = (a[i].v * x) / v - a[i].x;
		long double x2 = (a[i].v * x) / v - a[i].x + m;
		long double x3 = a[i].v / v - 1;
		if(!x3){if(x1 <= 0 && x2 >= 0) tot += a[i].w;vis[i] = 1;continue;}
		if(x3 < 0) b[i][0] = x2 / x3, b[i][1] = x1 / x3;
		else b[i][0] = x1 / x3, b[i][1] = x2 / x3;
		b[i][0] = max(b[i][0], x);
		T[i * 2 - 1] = b[i][0], T[i * 2] = b[i][1];
	}
	sort(T + 1, T + n * 2 + 1);
	int len = unique(T + 1, T + n * 2 + 1) - T - 1;
	build(1, 1, len);
	for(int i = 1; i <= n; i++){
		b[i][0] = lower_bound(T + 1, T + len + 1, b[i][0]) - T;
		b[i][1] = lower_bound(T + 1, T + len + 1, b[i][1]) - T;
		if(b[i][0] > b[i][1]) continue;
		if(!vis[i]) update(1, b[i][0], b[i][1], a[i].w);
	}
	memset(vis, 0, sizeof(vis));
	ans = max(ans, tree[1].mx + tot); 
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i].w >> a[i].x >> a[i].v;
	for(int i = 1; i <= n; i++){
		solve(a[i].v, a[i].x);
	}
	cout << ans;
	
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：0)

一看数据范围是 $n^2$ 级别的，可以放心地想枚举。\
时间和位置都是变化的，考虑固定一个，时间无从下手，考虑位置。\
简单观察发现，每次把位置固定到一条鱼的身上一定不劣，它能覆盖到尽可能多的鱼。\
所以我们考虑枚举每一条鱼作为左端点，然后计算出每一条鱼经过这条鱼撒网范围的起始和终止时间。并且给他赋上一个 $\pm w_i$，这个时候按时间为第一关键字排个序，价值为第二关键字从小到大排个序，扫一遍就做完了。\
按时间排序比较好理解，按价值排序是因为要尽可能地让鱼全进来后再出去，使价值最大化。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e3+10,inf=1e15;
int p[N],w[N],v[N],n,len,ans;
std::vector<std::pair<double,int>> e;
inline void work(int x){
    e.clear();
    int res=w[x];
    for(int i=1;i<=n;++i){
        if(i==x)continue;
        double l,r;             //懒得找通式了，直接大力分讨
        if(v[i]==v[x]){
            if(p[i]>=p[x]&&p[i]<=p[x]+len){
                l=0,r=inf;
                e.push_back({l,-w[i]});
                e.push_back({r,w[i]});
            }
            continue;
        }
        if(p[i]>=p[x]){
            if(p[i]<=p[x]+len){
                if(v[i]>v[x]){
                    l=0,r=(p[x]+len-p[i])*1.0/(v[i]-v[x]);
                    e.push_back({l,-w[i]});e.push_back({r,w[i]});
                    continue;
                }else{
                    l=0,r=(p[i]-p[x])*1.0/(v[x]-v[i]);
                    e.push_back({l,-w[i]});e.push_back({r,w[i]});
                    continue;
                }
            }
            else{
                if(v[i]<v[x]){
                    l=(p[i]-p[x]-len)*1.0/(v[x]-v[i]);r=(p[i]-p[x])*1.0/(v[x]-v[i]);
                    e.push_back({l,-w[i]});e.push_back({r,w[i]});
                }
                continue;
            }
        }else{
            if(v[i]>v[x]){
                l=(p[x]-p[i])*1.0/(v[i]-v[x]);r=(p[x]+len-p[i])*1.0/(v[i]-v[x]);
                e.push_back({l,-w[i]});e.push_back({r,w[i]});
            }
            continue;
        }
    }
    std::sort(e.begin(),e.end());
    ans=std::max(ans,res);
    for(auto it:e){
        res-=it.second;
        ans=std::max(ans,res);
    }
}
signed main(){
    //freopen("in.in","r",stdin);freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
    n=read(),len=read();
    for(int i=1;i<=n;++i){w[i]=read(),p[i]=read(),v[i]=read();}
    for(int i=1;i<=n;++i)work(i);
    std::cout<<ans<<'\n';
}
```

---

## 作者：WaterSun (赞：0)

# 思路

因为此题撒网的时间和位置都是未知的，所以必须枚举出一个。

又因为时间有可能是一个小数，不好枚举，因此考虑枚举位置。

首先，有一个显然的贪心策略，每一次撒网的位置的左端点一定是一条鱼。

那么，我们不妨枚举撒网位置的左端点为第 $i$ 条鱼。

然后可以算出其余的鱼能被一起捕到的时间段。

那么，问题就转变为了，在一堆时间段中，取一个点，使得这个点所在的时间段的权值之和最大。

直接用差分维护一个即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2010;
const double eps = 1e-9;
int n,len,ans;
int w[N],x[N],v[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	len = read();
	for (re int i = 1;i <= n;i++){
		w[i] = read();
		x[i] = read();
		v[i] = read();
	}
	for (re int i = 1;i <= n;i++){
		map<double,int> mp;
		int res = w[i];
		for (re int j = 1;j <= n;j++){
			if (i == j) continue;
			if (v[i] == v[j]){//当 v[i] = v[j] 时，i 和 j 的相对位置不变，判断 0 时刻能否被捕到即可 
				if (x[j] >= x[i] && x[j] - x[i] <= len) res += w[j];
			}
			else{
				double l = 1.0 * (x[i] - x[j]) / (v[j] - v[i]);//算出左右端点 
				double r = 1.0 * (x[i] - x[j] + len) / (v[j] - v[i]);
				if (r - l < eps) swap(l,r);
				if (r >= 0){
					l = max(l,0.0);
					mp[l] += w[j];
					mp[r + eps] -= w[j];
				}
			}
		}
		ans = max(ans,res);
		for (auto it = mp.begin();it != mp.end();it++){
			res += it -> second;
			ans = max(ans,res);
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：王熙文 (赞：0)

前言：这是一篇乱搞题解。

## 思路

首先如果我们确定了 $t$，则可以把游动之后的鱼的坐标求出来，排序之后双指针求出答案。

猜测一下，每个 $t$ 的答案随着 $t$ 的增长一定是先增后减的，即单峰函数。但是有可能会有相等的，因此普通的三分会错，原因是如果一大段都相等了突然在某一个位置有一个峰，有可能选择了它前面/后面的两个位置，计算值发现相等，然后错失了这个峰。

但是我就是用三分过的，接下来会介绍一下如何乱搞过。

首先三分并不需要每次分三段，然后保留 $\dfrac{2}{3}$。可以每次就取 $\dfrac{1}{20}$ 左右（参数需要调，但是接下来的参数保证能过），这样错失峰的机会会比较小。

研究第三个样例可以发现，只有在 $t=1$ 的时候答案是 $1110$，其他位置，比如 $0.999999$ 和 $1.000001$ 的答案都小于 $1110$。因此我们猜测答案大概会是一个比较整的点。所以三分到 $r-l\le 3$ 时就结束，然后在 $[l-5,r+5]$ 中暴力取整的点跑。我选的精度是 $10^{-3}$，即最开始保留三位小数，然后每次加 $10^{-3}$，取这些点的最大值。这样乱搞即可通过了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct fish
{
	int a,x,y;
	double xx;
} f[2010];
bool cmp(fish x,fish y)
{
	return x.xx<y.xx;
}
int check(double t)
{
	if(t<0) return 0;
	t=(int)(t*10000)/10000.0; // 保证精度
	for(int i=1; i<=n; ++i) f[i].xx=f[i].x+f[i].y*t;
	sort(f+1,f+n+1,cmp);
	int ans=0,now=1,nowsum=0;
	for(int i=1; i<=n; ++i)
	{
		while(now<=n && f[now].xx-f[i].xx<=m) nowsum+=f[now].a,++now;
		ans=max(ans,nowsum);
		nowsum-=f[i].a;
	}
	return ans;
}
int main()
{
	cin>>n>>m;
	for(int i=1; i<=n; ++i) cin>>f[i].a>>f[i].x>>f[i].y;
	double l=0,r=1e9,mid1,mid2;
	for(int i=1; i<=1000 && r-l>3; ++i)
	{
		mid1=l+(r-l)/20,mid2=r-(r-l)/20;
		if(check(mid1)<check(mid2)) l=mid1;
		else r=mid2;
	}
	l=(int)(l*1000)/1000.0,r=(int)(r*1000)/1000.0;
	int ans=0;
	for(double i=l-5; i<=r+5; i+=0.001) ans=max(ans,check(i));
	cout<<ans;
	return 0;
}
```

---

