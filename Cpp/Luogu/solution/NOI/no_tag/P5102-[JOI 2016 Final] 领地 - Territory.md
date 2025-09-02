# [JOI 2016 Final] 领地 / Territory

## 题目描述

**本题译自 [JOI 2016 Final](https://www.ioi-jp.org/joi/2015/2016-ho/index.html) T4「[縄張り](https://www.ioi-jp.org/joi/2015/2016-ho/2016-ho.pdf)」**

有一个平面直角坐标系。JOI 君位于 $(0, 0)$ 。  
JOI 君**每天**都按照一个固定的程序移动一轮。该程序有 $N$ 个步骤，用一个长度为 $N$ 的字符串 $S$ 描述。这个字符串仅由大写字母 $\texttt{E, N, W, S}$ 构成。  
左数第 $i$ 个字符 $C_i (1\leqslant i\leqslant N)$ 表示 JOI 君会移动到哪里。如果在执行步骤 $i$ 前，JOI 君位于 $(x, y)$：
* $C_i=\texttt{E}$：JOI 君将移动到 $(x+1,y)$；
* $C_i=\texttt{N}$：JOI 君将移动到 $(x,y+1)$；
* $C_i=\texttt{W}$：JOI 君将移动到 $(x-1,y)$；
* $C_i=\texttt{S}$：JOI 君将移动到 $(x,y-1)$。

次日 JOI 君会从他前一天停止的位置开始执行程序。  
JOI 君会把 $(0, 0)$ 以及每个步骤结束后到达的点作标记。开始时 JOI 君没有标记任何点。$K$ 天后，对于任意整数 $a, b$，如果 $(a,b),$ $(a+1,b),$ $(a,b+1),$ $(a+1,b+1)$ 这四个点都被标记了一次或以上，以这四个点为顶点的 $1\times 1$ 的正方形就属于 JOI 君的领地。  
请问 $K$ 天后，JOI 君有多少个领地。

## 说明/提示

#### 样例解释 1

![](https://cdn.luogu.com.cn/upload/image_hosting/5h9x63g9.png)

> 图中的字是之前完整题面的，懒得改了。「市政厅」表示 $(0, 0)$，「散步路径」表示移动路线。  
> 图我没有仔细 PS 过，可能对不齐、不对称，强迫症的同学们麻烦忍一忍

#### 样例解释 2
样例 2 与样例 1 的不同在于在样例 2 中 JOI 君走了两天。

![](https://cdn.luogu.com.cn/upload/image_hosting/26nj2fc2.png)

#### 数据范围与提示
对于所有数据，$1\leqslant N\leqslant 10^5, 1\leqslant K\leqslant 10^9$。

|Subtask #|特殊限制|分值|
|-|-|-|
|1|$N\leqslant 50, K = 1$|5|
|2|$K = 1$|10|
|3|$N\leqslant 50$|23|
|4|无|62|

## 样例 #1

### 输入

```
12 1
EENWSEEESWWS```

### 输出

```
3```

## 样例 #2

### 输入

```
12 2
EENWSEEESWWS```

### 输出

```
7```

## 样例 #3

### 输入

```
7 1
ENNWNNE```

### 输出

```
0```

## 样例 #4

### 输入

```
16 5
WSESSSWWWEEENNNW```

### 输出

```
21```

# 题解

## 作者：UnyieldingTrilobite (赞：6)

这题啊……真的是无话可说了，做完浑身舒畅的那种。

我们先不考虑 corner case。

首先肯定是按套路假设一轮过完之后起点移动的向量是 $(dx,dy)$。

我们考虑每一次的到达的点其实是很有规律的，对应点坐标之间会恰好差一个 $(dx,dy)$。那我们不难想到给它取模一下（不妨 $dx>0$）。

具体来说，我们用 $(x,y,t)$ 来表示 $(x+t\times dx,y+t\times dy)$，同时要求 $x\in[0,dx)$。

这样的话，我们如果先暴力走一轮，那么对于一个走到的点 $(x,y,r)$（注意这里 $r$ 不一定等于 $0$，因为有可能走到 $dx$ 外面去），我们实际上能走到的点是 $(x,y,r),(x,y,r+1),\cdots,(x,y,r+k-1)$，这本身是一个很好看的区间形式。注意起始点要特判一下，不过这不重要。

那么我们考虑正方形的四个顶点。我们会发现，如果对于一个 $r$，这四个点的前两维坐标都是合法的，那么就会产生 $1$ 的贡献。那么我们不妨换它一下，枚举四个顶点的前两维坐标（实际上只会有线性个这样的坐标，因为它们一定都在第一轮中出现过），然后考虑它们出现的位置（一定分别是若干个区间的并，这个开始扫一遍就可以搞定）的交，这玩意就很好处理了，来挑战这道题的人想必都会。注意有可能比如枚举左下角的时候发现另外三个点里有点的 $x$ 坐标达到了 $dx$，那没有关系，还是先转换成我们的标准坐标形式，对搞出来的范围平移一下就好了。

接下来是一些 corner case。

1. $dx<0$

把所有 `E` 和 `W` 交换就好了。

2. $dx=0,dy\not=0$

把 $dx$ 和 $dy$ 交换一下就好了。有可能需要用上面第一种情况额外处理一下。

3. $dx=dy=0$

每一轮都一样，走一轮就好了。可以把 $dx$ 手动改成充分大来回避其他问题。

代码（采用的区间是左闭右开的）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>itv;
int dx,dy;
map<itv,set<itv>>cnt;
void init(){
	int n,k;
	string s;
	cin>>n>>k>>s;
	auto op=[](int&x,int&y,char c){
		switch(c){
			case 'E':++x;break;
			case 'N':++y;break;
			case 'W':--x;break;
			case 'S':--y;break;
		}
	};
	for(char c:s)op(dx,dy,c);
	auto trans=[&s](vector<pair<char,char>>trs){
		for(char&c:s)
			for(auto[c1,c2]:trs)
				if(c==c1)c=c2;
				else if(c==c2)c=c1;
	};
	if(!dx){
		swap(dx,dy),trans({{'E','N'},{'W','S'}});
		if(!dx)dx=250637,k=1;
	}
	if(dx<0)dx=-dx,trans({{'E','W'}});
	auto ins=[](itv pos,itv val){
		auto&st=cnt[pos];
		auto itl=st.lower_bound({val.first,INT_MIN});
		if(itl!=st.begin()&&prev(itl)->second>=val.first)--itl;
		auto itr=st.upper_bound({val.second,INT_MAX});
		if(itl==itr)st.insert(val);
		else{
			int l=min(itl->first,val.first),r=max(prev(itr)->second,val.second);
			st.erase(itl,itr),st.emplace(l,r);
		}
	};
	ins({0,0},{0,1});
	for(int x=0,y=0;char c:s){
		op(x,y,c);
		int dt=x/dx,px=x-dt*dx,py=y-dt*dy;
		if(px<0)px+=dx,py+=dy,--dt;
		ins({px,py},{dt,k+dt});
	}
}
signed main(){
	long long ans=0;
	auto atval=[](int x,int y){
		vector<itv>ret;
		int dt=0;
		if(x==dx)x-=dx,y-=dy,dt=1;
		if(auto it=cnt.find({x,y});it!=cnt.end()){
			ret.reserve(it->second.size());
			copy(it->second.begin(),it->second.end(),back_inserter(ret));
			for(auto&[l,r]:ret)l-=dt,r-=dt;
		}
		return ret;
	};
	auto merge=[](auto x,auto y){
		vector<itv>ret;
		for(auto pos=y.begin();auto[l,r]:x)
			while(pos!=y.end()){
				while(pos!=y.end()&&pos->second<=l)++pos;
				if(pos==y.end()||pos->first>=r)break;
				ret.emplace_back(max(l,pos->first),min(r,pos->second));
				if(pos->second>=r)break;
				else ++pos;
			}
		return ret;
	};
	for(init();auto[pos,iv]:cnt){
		auto[x,y]=pos;
		for(auto[l,r]:merge(merge(atval(x,y),atval(x+1,y+1)),merge(atval(x+1,y),atval(x,y+1))))
			ans+=r-l;
	}
	return cout<<ans<<endl,0;
}
```

---

## 作者：sunzh (赞：4)

路径上经过的所有点可以用按照轮次和位置表示为$(x,y,r)$表示第$r$轮走在$(x,y)$位置

如果我们默认每次的起点都是$(0,0)$那么$(x,y,r)$表示的就是$(x+r\times tx,y+r\times ty)$

我们如果把所有的点的$x$坐标都限制在$0$到$tx$范围内，那么我们就把所有本质一样的点都压在了一个位置，只要轮数一致，那就是完全重合的两个点

对于$x$不在$0$到$tx$之间的点，我们通过调整轮数使它在合法区间内

我们对于每个点可以处理出存在的轮数区间，考虑每个店作为左下角时，其它三个点对应的位置和轮数区间，四个点所对应的轮数同时合法那就计入答案，也就是将区间统一标准后求交集即可

$tx=0$的时候要特判

具体细节可以看代码

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<set>
#include<vector>
#include<cmath>
#include<map>
#define PII pair<int,int>
#define pb push_back
#define ep emplace_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f==1?x:~x+1;
}
inline void print(int x){
	if(x<0) putchar('-'),x=~x+1;
	if(x>=10) print(x/10);
	putchar((x%10)|48);
}
int n,k;
char str[100010];
map<PII,vector<PII> >Map;
int tx,ty;
void merge(vector<PII>&s,vector<PII>t){
	vector<PII>res;
	auto it=t.begin();
	for(auto i:s){
		while(it!=t.end()){
			while(it!=t.end()&&it->se<i.fi) ++it;
			if(it==t.end()) break ;
			if(it->fi>i.se) break ;
			res.ep(max(it->fi,i.fi),min(it->se,i.se));
			if(it->se>i.se) break ;
			++it;
		}
	}
	s=res;
}
int main(){
	n=read(),k=read();
	scanf("%s",str+1);
	for(int i=1;i<=n;++i){
		switch(str[i]){
			case 'E':++tx;break ;
			case 'N':++ty;break ;
			case 'W':--tx;break ;
			case 'S':--ty;break ;
		}
	}
	if(tx==0&&ty==0) {k=1;tx=1e9;}
	else if(tx==0){
		swap(tx,ty);
		for(int i=1;i<=n;++i){
			switch(str[i]){
				case 'E':str[i]='N';break;
				case 'N':str[i]='E';break;
				case 'W':str[i]='S';break;
				case 'S':str[i]='W';break;
			}
		}
	}
	if(tx<0){
		for(int i=1;i<=n;++i){
			switch(str[i]){
				case 'E':str[i]='W';break;
				case 'W':str[i]='E';break;
			}
		}
		tx=-tx;
	}
	if(ty<0){
		for(int i=1;i<=n;++i){
			switch(str[i]){
				case 'N':str[i]='S';break;
				case 'S':str[i]='N';break;
			}
		}
		ty=-ty;
	}
	Map[mp(0,0)].pb(mp(1,k));
	for(int i=1;i<=n;++i){
		static int x=0,y=0;
		switch(str[i]){
			case 'E':++x;break ;
			case 'N':++y;break ;
			case 'W':--x;break ;
			case 'S':--y;break ;
		}
//		printf("i:%d,x:%d,y:%d\n",i,x,y);
		int d=x/tx;
		int ax=x-d*tx,ay=y-d*ty;
		if(ax<0) --d,ax+=tx,ay+=ty;
//		printf("d:%d,ax:%d,ay:%d\n\n\n",d,ax,ay);
		Map[mp(ax,ay)].pb(mp(d+1,d+k));
	}
	for(auto &i:Map){
		auto &v=i.se;
		sort(v.begin(),v.end());
		int l=-1e6,r=-1e6;
		vector<PII>nw;
		for(auto p:v){
			if(l==-1e6){
				l=p.fi,r=p.se;
			}
			else if(p.fi<=r) r=max(r,p.se);
			else{
				nw.ep(l,r);
				l=p.fi,r=p.se;
			}
		}
		nw.ep(l,r);
		v=nw;
	}
	auto mt=[&](PII x){
		if(x.fi>=tx) x.fi-=tx,x.se-=ty;
		return x;
	};
	long long ans=0;
	for(auto i:Map){
		PII nod=i.fi;
		PII x2=mp(nod.fi+1,nod.se),x3=mp(nod.fi,nod.se+1),x4=mp(nod.fi+1,nod.se+1);
		if(Map.count(mt(x2))&&Map.count(mt(x3))&&Map.count(mt(x4))){
			auto gs=[&](PII x){
				if(x.fi>=tx){
					x.fi-=tx,x.se-=ty;
					vector<PII>t=Map[x];
					vector<PII>res(t.size());
					auto minus=[&](PII a){
						return mp(a.fi-1,a.se-1);
					};
//					printf("Mns:\n");
//					for(auto a:t) printf("%d %d\n",a.fi,a.se);
					std::transform(t.begin(),t.end(),res.begin(),minus);
//					printf("Res:\n");
//					for(auto a:res) printf("%d %d\n",a.fi,a.se);
//					printf("\n\n");
					return res;
				}
				else return Map[x];
			};
			vector<PII>v=i.se;
			merge(v,gs(x2));merge(v,gs(x3));merge(v,gs(x4));
			for(auto x:v) ans+=x.se-x.fi+1;
//			printf("%d %d ans:%d\n",nod.fi,nod.se,ans);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：int_R (赞：1)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18254699/P5102)

模拟赛题，但是赛时挂在了取模上，就差一点啊啊啊啊啊啊。

记 $(x_i,y_i)$ 是移动了 $i$ 次后的坐标。

肯定要从周期的方面考虑，每一组操作产生的点是上一组操作产生的点在 $x$ 轴方向平移了 $x_n$，$y$ 轴方向平移了 $y_n$ 得到的，即 $\forall i\geq n,(x_i,y_i)=(x_{i\bmod n}+k x_n,y_{i\bmod n}+k y_n)$，其中 $k=\lfloor \dfrac{i}{n} \rfloor$。

那我们考虑将所有可以表示为 $(x'+kx_n,y'+ky_n)$ 的点分为一组，每个点也只会分到一组中。在一组中钦定唯一一个位置使其编号即 $k$ 值为 $0$，这样每个点都获得了一个编号。

那么我们现在有一个点编号为 $p$，进行所有 $K$ 组操作后，这个点覆盖的编号区间即 $[p,p+K-1]$。我们可以直接在每组中做这个，然后取区间并，就得到了这组点中所有可以覆盖的地方。

现在我们对每组点同时做原问题，其实就相当于找到另外三组点，然后求它们覆盖的区间交。

初始点数是 $O(n)$ 的，所以组数也是 $O(n)$ 的，所以区间数也是 $O(n)$ 的，中间需要一些排序，所以时间复杂度是 $O(n\log n)$。

再说一些细节。

$x_n=y_n=0$ 要特别处理一下，也就是每个点单独是一组，一些写法可能要把 $K$ 手动改成 $1$。

分组相当于每组点在一条直线上，每条直线的斜率也是一样的，所以可以通过截距找出每条直线。截距是 $y-\dfrac{y_n}{x_n}x$，可以乘一个分母变成整数，同时防止除以 $0$。

但是每条直线不一定是一个组，同一截距每个 $x\equiv x'\pmod {x_n}$ 是一组，$x_n$ 为 $0$ 时可以改为用 $y$ 和 $y_n$ 做，后面一些东西也是。注意取模的时候负数和正数的取模值是不一样的，要转一下。

这样每组对应一个截距和 $x\bmod x_n$ 组成的二元组，可以用哈希表存一下。每组可以把第一个加进去的点的 $k$ 值设为 $0$。求每个点 $(x,y)$ 对应的 $k$ 值直接用 $x$ 减去第一个点的横坐标再除一下 $x_n$ 即可。

求区间交的时候，每组点编号并不统一，手动统一一下就行。比方说当前组 $k=0$ 的点是 $(x,y)$，那么找到 $(x,y+1)$ 在他们组当中的 $k$ 值 $k'$，然后每个端点减去 $k'$，就可以统一编号了。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>
#define ll long long
using namespace std;
const int MAXN=1e5+10;
string s;int T,n,kx,ky,tot;ll ans;
unordered_map <ll,int> H;
struct ple{ll x,y,z;};vector <ple> v;
inline bool cmp(ple x,ple y)
    {return x.x!=y.x?x.x<y.x:x.z>y.z;}
inline bool ccmp(ple x,ple y)
    {return x.x!=y.x?x.x<y.x:x.y<y.y;}
struct node
{
    vector <ple> v,t,f;
    inline void work()
    {
        for(ple now:v) t.push_back({now.z,now.z+(T-1)});
        sort(t.begin(),t.end(),ccmp);ll l=t[0].x,r=t[0].y;
        for(int i=1;i<t.size();++i)
        {
            if(r>=t[i].x-1){r=max(r,t[i].y);continue;}
            f.push_back({l,r}),l=t[i].x,r=t[i].y;
        }
        f.push_back({l,r});return ;
    }
}t[MAXN];
inline ll M(ll x,ll y){y=abs(y);return (x%y+y)%y;}
inline ll pos(ll x,ll y)
{
    if(!kx&&!ky) return x*1000000+y;
    return (y*kx-x*ky)*100000+(kx?M(x,kx):M(y,ky));
}
inline ll F(ll x,ll y)
{
    if(!kx&&!ky) return 0;
    ll num=pos(x,y);int pos=H[num];
    ll prex=t[pos].v[0].x,prey=t[pos].v[0].y;
    return (kx?(x-prex)/kx:(y-prey)/ky);
}
inline void upd(ll x,ll y)
{
    ll num=pos(x,y);if(!H[num])
        H[num]=++tot,t[tot].v.push_back({x,y,0});
    else
    {
        if(!kx&&!ky) return ;
        int pos=H[num],prex=t[pos].v[0].x,prey=t[pos].v[0].y;
        if(kx) t[pos].v.push_back({x,y,(x-prex)/kx});
        else t[pos].v.push_back({x,y,(y-prey)/ky});
    }
}
signed main()
{
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n>>T>>s;
    for(char c:s)
    {
        if(c=='N') ++ky;if(c=='S') --ky;
        if(c=='E') ++kx;if(c=='W') --kx;
    }
    if(!kx&&!ky) T=1;upd(0,0);int x=0,y=0;
    for(int i=1;i<=n;++i)
    {
        char c=s[i-1];
        if(c=='N') ++y;if(c=='S') --y;
        if(c=='E') ++x;if(c=='W') --x;
        upd(x,y);
    }
    for(int i=1;i<=tot;++i) t[i].work();
    for(int i=1;i<=tot;++i)
    {
        ll x=t[i].v[0].x,y=t[i].v[0].y,s=0,pre;
        ll num1=pos(x,y+1);if(!H[num1]) continue;
        ll num2=pos(x+1,y);if(!H[num2]) continue;
        ll num3=pos(x+1,y+1);if(!H[num3]) continue;
        ll pos[4]={i,H[num1],H[num2],H[num3]};
        ll del[4]={0,F(x,y+1),F(x+1,y),F(x+1,y+1)};
        for(int o=0;o<4;++o) for(ple now:t[pos[o]].f)
            v.push_back((ple){now.x-del[o],o,1}),
            v.push_back((ple){now.y-del[o],o,0});
        sort(v.begin(),v.end(),cmp);
        for(ple now:v)
        {
            if(s==15) ans+=now.x-pre+1;
            s^=(1<<now.y),pre=now.x;
        }v.clear();
    }
    cout<<ans<<'\n';return 0;
}
```

---

## 作者：dAniel_lele (赞：0)

设一轮后会移动 $dx,dy$，特判 $dx=dy=0$。

否则考虑将会移动到一起的一整条直线归在一个点计算（即，所有 $i+p\times dx=i',j+p\times dy=j'$ 的 $(i,j)$，$(i',j')$ 放在一起计算）。那么每个点对应的出现的是一整段 $p\in[l,r]$。

对于每一整条直线，把相邻出现的合并在一起，记录成若干个 $(l_i,r_i)$。

对于每条直线，考虑以这条线上点为左上角的正方形，将相邻 $4$ 条直线的 $(l_i,r_i)$ 取出并做扫描线，所有覆盖区间的二元组数量为 $4$ 的区间即可记入答案。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
map<int,int> mp[500005];
map<pair<int,int>,int> mpp;
vector<pair<int,int>> vc[200005];
int cnt;
int cycx,cycy;
pair<pair<int,int>,int> reduc(int nowx,int nowy){
	int rx,ry,num;
	if(!cycx){
		rx=nowx; ry=nowy%cycy; num=nowy/cycy;
	}
	else if(!cycy){
		rx=nowx%cycx; ry=nowy; num=nowx/cycx;
	}
	else{
		num=min(nowx/cycx,nowy/cycy);
		rx=nowx-num*cycx; ry=nowy-num*cycy;
	}
	return make_pair(make_pair(rx,ry),num);
}
int rrx[200005],rry[200005];
signed main(){
	int n,k; cin>>n>>k;
	string s; cin>>s;
	// int k; cin>>k;
	int nowx=250000,nowy=250000;
	int tot=1;
	mp[nowx][nowy]=1;
	for(int i=0;i<s.size();i++){
		if(s[i]=='W') nowy--;
		if(s[i]=='E') nowy++;
		if(s[i]=='N') nowx--;
		if(s[i]=='S') nowx++;
		if(!mp[nowx][nowy]) mp[nowx][nowy]=1,tot++;
	}
	if(nowx==250000&&nowy==250000){
		int ans=0;
		for(int i=0;i<=500000;i++){
			for(auto v:mp[i]){
				int x=i,y=v.first;
				if(mp[x][y]&&mp[x][y+1]&&mp[x+1][y]&&mp[x+1][y+1]) ans++;
			}
		}
		cout<<ans;
		return 0;
	}
	cycx=nowx-250000,cycy=nowy-250000;
	nowx=250000,nowy=250000;
	for(int i=0;i<s.size();i++){
		auto tmp=reduc(nowx,nowy);
		int rx=tmp.first.first,ry=tmp.first.second,num=tmp.second;
		if(!mpp[make_pair(rx,ry)]) mpp[make_pair(rx,ry)]=++cnt,rrx[cnt]=rx,rry[cnt]=ry;
		vc[mpp[make_pair(rx,ry)]].push_back(make_pair(num,num+k+(i==0)-1));
		if(s[i]=='W') nowy--;
		if(s[i]=='E') nowy++;
		if(s[i]=='N') nowx--;
		if(s[i]=='S') nowx++;
	}
	int ans=0;
	for(int i=1;i<=cnt;i++){
		sort(vc[i].begin(),vc[i].end());
		int lstl=-1e18,lstr=-1e18;
		vector<pair<int,int>> nvc;
		for(auto v:vc[i]){
			if(v.first>lstr+1){
				if(lstr!=-1e18){
					nvc.push_back(make_pair(lstl,lstr));
				}
				lstl=v.first,lstr=v.second;
			}
			else{
				lstr=max(lstr,v.second);
			}
		}
		if(lstr!=-1e18){
			nvc.push_back(make_pair(lstl,lstr));
		}
		vc[i]=nvc;
	}
	// cout<<cycx<<" "<<cycy<<"\n\n";
	// for(int i=1;i<=cnt;i++){
	// 	cout<<rrx[i]<<" "<<rry[i]<<"\n";
	// 	for(auto v:vc[i]){
	// 		cout<<v.first<<" "<<v.second<<"\n";
	// 	}
	// 	cout<<"\n";
	// }
	for(int i=1;i<=cnt;i++){
		int p1=i,s1=0,p2,s2=0,p3,s3=0,p4,s4=0;
		{
			auto tmp=reduc(rrx[i],rry[i]+1);
			int rx=tmp.first.first,ry=tmp.first.second,num=tmp.second;
			p2=mpp[make_pair(rx,ry)],s2=num;
			if(!p2) continue;
		}
		{
			auto tmp=reduc(rrx[i]+1,rry[i]);
			int rx=tmp.first.first,ry=tmp.first.second,num=tmp.second;
			p3=mpp[make_pair(rx,ry)],s3=num;
			if(!p3) continue;
		}
		{
			auto tmp=reduc(rrx[i]+1,rry[i]+1);
			int rx=tmp.first.first,ry=tmp.first.second,num=tmp.second;
			p4=mpp[make_pair(rx,ry)],s4=num;
			if(!p4) continue;
		}
		vector<pair<int,pair<int,int>>> pv;
		for(auto v:vc[p1]) pv.push_back(make_pair(v.first-s1,make_pair(1,1))),pv.push_back(make_pair(v.second+1-s1,make_pair(-1,1)));
		for(auto v:vc[p2]) pv.push_back(make_pair(v.first-s2,make_pair(1,2))),pv.push_back(make_pair(v.second+1-s2,make_pair(-1,2)));
		for(auto v:vc[p3]) pv.push_back(make_pair(v.first-s3,make_pair(1,3))),pv.push_back(make_pair(v.second+1-s3,make_pair(-1,3)));
		for(auto v:vc[p4]) pv.push_back(make_pair(v.first-s4,make_pair(1,4))),pv.push_back(make_pair(v.second+1-s4,make_pair(-1,4)));
		sort(pv.begin(),pv.end());
		int lst=-1e18,cnt=0;
		for(int i=0;i<pv.size();i++){
			if(cnt==4){
				ans+=pv[i].first-lst;
			}
			lst=pv[i].first;
			cnt+=pv[i].second.first;
		}
	}
	cout<<ans;
	return 0;
}
```

---

