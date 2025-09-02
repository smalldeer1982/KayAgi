# 「SWTR-3」Plane Mirrors

## 题目背景

小 $\mathrm{A}$ 在学物理。

老师在讲“平面镜成像”这个物理现象。

但老师讲课太无聊，所以他就睡着了。

## 题目描述

小 $\mathrm{A}$ 梦见自己站在了一个平台上，在他的周围有一些平面镜，我们假定他的位置为 $(0,0)$。

他发现，每个平面镜都有一个初始不透明度，记做 $v_i$。

下文中，我们定义：

- 一个射线的“不透明度”为：该射线穿过的所有平面镜的初始不透明度之和。

- 一个平面镜的“视觉不透明度”为：所有**从 $(0,0)$ 发出**且**经过该平面镜**的射线的不透明度最大值。

小 $\mathrm{A}$ 突然发现自己能够控制这些平面镜，于是就有了下面这道题目。

小 $\mathrm{A}$ 需要你完成以下操作：

`1 x1 y1 x2 y2 v`：变出一个两端分别在 $(x_1,y_1),(x_2,y_2)$，初始不透明度为 $v$ 的平面镜。

`2 d`：摧毁第 $d$ 个变出来的平面镜，保证未被摧毁。

`3 x y`：设 $\mathrm{A=(0,0),B=(x,y)}$，询问射线 $\mathrm{AB}$ 的不透明度。

`4 d`：询问第 $d$ 个平面镜的视觉不透明度，如已被摧毁则输出 `oops!`。

## 说明/提示

---

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/f7i3u2l6.png)

如图，蓝色代表射线，红色代表平面镜。

对于第 $1$ 次询问：可以看出射线只穿过了平面镜 $1$，答案为 $7$。

对于第 $2$ 次询问：可以看出射线只穿过了平面镜 $2$，答案为 $10$。

对于第 $3$ 次询问：可以看出射线穿过了平面镜 $1,2$，答案为 $7+10=17$。

对于第 $4$ 次询问，可以看出射线穿过了平面镜 $3$，答案为 $17$。

对于第 $5$ 次询问，可以看出穿过平面镜 $2$ 的不透明度最大的射线为 $(0,0)(2,2)$（射线不唯一），穿过了平面镜 $1,2$，答案为 $7+10=17$。

对于第 $6$ 次询问，可以看出穿过平面镜 $2$ 的不透明度最大的射线为 $(0,0)(2,2)$（射线不唯一），穿过了平面镜 $2$，答案为 $10$。

对于第 $7$ 次询问，因为平面镜 $1$ 已被摧毁，所以输出 `oops!`。

---

### 数据范围与约定

测试点编号|$n\leq$|特殊性质
:-:|:-:|:-:
$1-4$|$1000$|$x,y$ 绝对值小于 $10^3$ 且**没有 $4$ 询问**
$5-8$|$2\times 10^5$|所有 $y$ 相等
$9-12$|$2\times 10^5$|$x\ge 0$
$13-20$|$2\times 10^5$|无

对于 $100\%$ 的数据，有 $1\leq n\leq 2\times 10^5$，$1\leq v\leq 10^3$ 且 $0\leq |x|,|y|\leq 10^5$。

保证平面镜的总数不会超过 $10^5$。

保证所有平面镜不会穿过 $(0,0)$，但**不保证**平面镜会退化成一个点。

保证所有 $3$ 询问 $(x,y)\neq(0,0)$。

---

对于所有测试点，时间限制 $2\mathrm{s}$，空间限制 $128\mathrm{MB}$。

## 样例 #1

### 输入

```
11
1 -1 2 2 -1 7
1 2 2 -1 0 10
1 2 1 1 -1 17
3 5 4
3 -99999 0
3 -3 6
3 1 -1
4 2
2 1
4 2
4 1
```

### 输出

```
7
10
17
17
17
10
oops!```

# 题解

## 作者：caeious (赞：2)

upd: 在看了 SF 的文章后修了修格式；另外题解的渲染真的很丑。。。建议点击 “在 Ta 的博客查看”。

## Solution
用极角做真的更简单诶。。。  
在本题解中，极角的值域默认为 $(-\pi,\pi]$。  
#### 平面镜
设两个端点极角为 $\alpha,\ \beta(\alpha < \beta)$.  
$\because$ 平面镜不经过原点  
$\therefore$ $\beta - \alpha \neq \pi$  
如果 $\beta - \alpha > \pi$, 说明平面镜跨过射线 $\theta = \pi$,就对应两段 $[-\pi,\alpha]$、$[\beta,\pi]$。  
否则对应一段 $[\alpha,\beta]$。  
#### 射线
显然，若设 $(x,y)$ 极角为 $\varphi$ , 则对应区间 $[\varphi,\varphi]$。
#### 综上
- opt = 1: 区间 $[\alpha',\beta']$ 增加 $v$
- opt = 2: 区间$[\alpha',\beta']$ 减少 $v$
- opt = 3: 查询区间 $[\alpha',\alpha']$ 的 $\max$
- opt = 4: 查询区间 $[\alpha',\beta']$ 的 $\max$  

具体实现先将输入中出现的极角集合 $S$ 离散化，再用线段树维护区间加、区间求 $\max$ 就好了。
#### 浮点误差
$\because |x|,|y| <= 10^5$，输入中都是整点   
$\therefore$ $\forall \alpha,\beta \in S(\alpha \neq \beta),$ 有 $|\alpha - \beta| \geq \frac{\pi}{4} - \arctan(1 - 10^{-5}) \approx 5.1 \times 10^{-6}$.  
$\therefore$ 离散化角度时取EPS = $10^{-10}$ 足够（其实即使不用EPS也能过qwq)。
## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
typedef long long ll;
const int LEN = 100000;

struct fastio{
  int it,len;
  char s[LEN + 5];
  fastio(){
    it = len = 0;
  }
  char get(){
    if(it < len) return s[it++];
    it = 0, len = fread(s,1,LEN,stdin);
    return len ? s[it++] : EOF;
  }
  bool notend(){
    char c;
    for(c = get();c == ' ' || c == '\n';c = get());
    if(it) it--;
    return c != EOF;
  }
  void put(char c){
    if(it == LEN) fwrite(s,1,LEN,stdout), it = 0;
    s[it++] = c;
  }
  void flush(){
    fwrite(s,1,it,stdout);
  }
}buff,bufo;
inline int getint(){
  char c; int res = 0, sig = 1;
  for(c = buff.get();c < '0' || c > '9';c = buff.get()) if(c == '-') sig = -1;
  for(;c >= '0' && c <= '9';c = buff.get()) res = res * 10 + (c - '0');
  return sig * res;
}
inline ll getll(){
  char c; ll res = 0, sig = 1;
  for(c = buff.get();c < '0' || c > '9';c = buff.get()) if(c == '-') sig = -1;
  for(;c >= '0' && c <= '9';c = buff.get()) res = res * 10 + (c - '0');
  return sig * res;
}
inline void putint(int x,char suf){
  if(!x) bufo.put('0');
  else{
    if(x < 0) bufo.put('-'), x = -x;
    int k = 0; char s[15];
    while(x){
      s[++k] = x % 10 + '0';
      x /= 10;
    }
    for(;k;k--) bufo.put(s[k]);
  }
  bufo.put(suf);
}
inline void putll(ll x,char suf){
  if(!x) bufo.put('0');
  else{
    if(x < 0) bufo.put('-'), x = -x;
    int k = 0; char s[25];
    while(x){
      s[++k] = x % 10 + '0';
      x /= 10;
    }
    for(;k;k--) bufo.put(s[k]);
  }
  bufo.put(suf);
}
inline char get_char(){
  char c;
  for(c = buff.get();c == ' ' || c == '\n';c = buff.get());
  return c;
}
#define maxn 200005
const double pi = acos(-1);
struct Query{
  int opt,x0,y0,x2,y2,v;
  // opt = 2: v = d
  // opt = 3: (x0,y0) = (x,y)
  // opt = 4: v = d
}qs[maxn];
int id[maxn],num;
int n,len;
vector <double> thetas;
struct Sgt{
  int maxi[maxn << 3],add[maxn << 3];
  void up(int id){
    maxi[id] = max(maxi[id << 1],maxi[id << 1 | 1]);
    maxi[id] += add[id];
  }
  void down(int id){
    if(add[id]){
      maxi[id << 1] += add[id];
      add[id << 1] += add[id];
      maxi[id << 1 | 1] += add[id];
      add[id << 1 | 1] += add[id];
      add[id] = 0;
    }
  }
  void _plus(int id,int l,int r,int ql,int qr,int x){
    if(ql <= l && r <= qr){
      maxi[id] += x;
      add[id] += x;
    }else{
      down(id);
      int mid = (l + r) >> 1;
      if(ql <= mid) _plus(id << 1,l,mid,ql,qr,x);
      if(mid < qr) _plus(id << 1 | 1,mid + 1,r,ql,qr,x);
      up(id);
    }
  }
  int query(int id,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr) return maxi[id];
    down(id);
    int mid = (l + r) >> 1, res = 0;
    if(ql <= mid) res = max(res,query(id << 1,l,mid,ql,qr));
    if(mid < qr) res = max(res,query(id << 1 | 1,mid + 1,r,ql,qr));
    return res;
  }
}sgt;
void range_add(double a,double b,int v){
  if(a > b) swap(a,b);
  int id_a = lower_bound(thetas.begin(),thetas.end(),a) - thetas.begin() + 1,
      id_b = lower_bound(thetas.begin(),thetas.end(),b) - thetas.begin() + 1;
  if(b - a > pi){
    sgt._plus(1,1,len,1,id_a,v);
    sgt._plus(1,1,len,id_b,len,v);
  }else{
    sgt._plus(1,1,len,id_a,id_b,v);
  }
}
int query_max(double a,double b){
  if(a > b) swap(a,b);
  int id_a = lower_bound(thetas.begin(),thetas.end(),a) - thetas.begin() + 1,
      id_b = lower_bound(thetas.begin(),thetas.end(),b) - thetas.begin() + 1;
  if(b - a > pi)
    return max(sgt.query(1,1,len,1,id_a),sgt.query(1,1,len,id_b,len));
  return sgt.query(1,1,len,id_a,id_b);
}
int main(){
  n = getint();
  thetas.push_back(-pi);
  thetas.push_back(pi);
  for(int i = 1;i <= n;i++){
    qs[i].opt = getint();
    if(qs[i].opt == 1){
      id[++num] = i;
      qs[i].x0 = getint(), qs[i].y0 = getint(),
      qs[i].x2 = getint(), qs[i].y2 = getint(), qs[i].v = getint();
      thetas.push_back(atan2(qs[i].y0,qs[i].x0)),
      thetas.push_back(atan2(qs[i].y2,qs[i].x2));
    }else if(qs[i].opt == 2){
      qs[i].v = getint();
    }else if(qs[i].opt == 3){
      qs[i].x0 = getint(), qs[i].y0 = getint();
      thetas.push_back(atan2(qs[i].y0,qs[i].x0));
    }else{
      qs[i].v = getint();
    }
  }
  sort(thetas.begin(),thetas.end());
  thetas.erase(unique(thetas.begin(),thetas.end()),thetas.end());
  len = thetas.size();
  for(int i = 1;i <= n;i++){
    if(qs[i].opt == 1){
      range_add(atan2(qs[i].y0,qs[i].x0),atan2(qs[i].y2,qs[i].x2),qs[i].v);
    }else if(qs[i].opt == 2){
      int j = id[qs[i].v];
      range_add(atan2(qs[j].y0,qs[j].x0),atan2(qs[j].y2,qs[j].x2),-qs[j].v);
      id[qs[i].v] = -1;
    }else if(qs[i].opt == 3){
      printf("%d\n",
        query_max(atan2(qs[i].y0,qs[i].x0),atan2(qs[i].y0,qs[i].x0)));
    }else{
      int j = id[qs[i].v];
      if(j == -1) puts("oops!");
      else{
        printf("%d\n",
          query_max(atan2(qs[j].y0,qs[j].x0),atan2(qs[j].y2,qs[j].x2)));
      }
    }
  }
  return 0;
}
```
RunID: [28847331](https://www.luogu.com.cn/record/28847331)，跑的还挺快。。。

---

## 作者：Alex_Wei (赞：2)

$\color{#9400d3}\mathrm{This\ is\ Sweet\ Round\ 03.}$

[$\color{#9400d3}\mathrm{Link:T5\ Plane\ Mirrors}$](https://www.luogu.com.cn/problem/T112464)

基础数据结构 $+$ 计算几何。

---

$\mathrm{Sol\ 1}:$

对于每个 $3$ 询问，暴力枚举所有平面镜，判断是否在该射线上。

#### 如何判断射线是否在平面镜上？

我们设 $r_1=\dfrac{y_1}{x_1},r_2=\dfrac{y_2}{x_2},r=\dfrac{y}{x}$。如果 $x=0$，那么可以把 $r$ 看成一个很大的数，例如 $10^9+7$。

- 如果该平面镜没有穿过 $y$ 轴：

![](https://cdn.luogu.com.cn/upload/image_hosting/47lvdbc5.png)

如图，不妨设 $r_1\leq r_2$，如果 $r_1\leq r\leq r_2$，那么该射线就穿过了该平面镜（图中 $r_1=-0.56,r=3.12,r_2=5.789$）。

- 如果该平面镜穿过了 $y$ 轴：

不妨设 $x_1<0,x_2\ge0$。计算出该平面镜与 $y$ 轴的交点 $P(x_P,y_P)$，然后把平面镜从该点断开，拆成两个没有穿过 $y$ 轴的平面镜，再判断即可。

- 如何计算平面镜与 $y$ 轴的交点？

将该平面镜看成一个一次函数，用平面镜两个端点计算出函数表达式，再求出 $x=0$ 时 $y$ 的值即可。

```cpp
#define ld long double
ld zero(ld x1,ld y1,ld x2,ld y2){
	ld k=(y1-y2)/(x1-x2),b=y1-k*x1;
	return b;
}
```

时间复杂度：$\mathcal O(n^2)$。

- 可以通过测试点 $1-4$。

期望得分：$20\%$。

```cpp
#include<iostream>
using namespace std;
#define ld long double
const int N=1e3+5;
const ld inf=1e9;
int n,cnt;
struct Plane_Mirror{
	int x1,x2,y1,y2,v,pd;
}c[N];
ld ratio(ld x,ld y){
	if(x==0)return y>0?inf:-inf;
	else return y/x;
}
ld zero(ld x1,ld y1,ld x2,ld y2){
	ld k=(y1-y2)/(x1-x2),b=y1-k*x1;
	return b;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int op;
		scanf("%d",&op);
		if(op==1){
			cnt++;
			scanf("%d%d%d%d%d",&c[cnt].x1,&c[cnt].y1,&c[cnt].x2,&c[cnt].y2,&c[cnt].v);
		}
		if(op==2){
			int d;
			scanf("%d",&d);
			c[d].pd=1;
		}
		if(op==3){
			int x,y,ans=0;
			scanf("%d%d",&x,&y);
			ld r=ratio(x,y);
			for(int j=1;j<=cnt;j++)
				if(!c[j].pd){
					int x1=c[j].x1,y1=c[j].y1,x2=c[j].x2,y2=c[j].y2;
					ld r1=ratio(x1,y1),r2=ratio(x2,y2);
					if(x1>=0&&x2>=0){
						if(x<0)continue;
						if(r1>r2)swap(r1,r2);
						if(r1<=r&&r<=r2)ans+=c[j].v;
					}
					else if(x1<0&&x2<0){
						if(x>=0)continue;
						if(r1>r2)swap(r1,r2);
						if(r1<=r&&r<=r2)ans+=c[j].v;
					}
					else if(x1>=0&&x2<0){
						ld cont=zero(x1,y1,x2,y2);
						if(x<0&&(cont>0&&r<=r2||cont<0&&r2<=r))ans+=c[j].v;
						if(x>=0&&(cont>0&&r1<=r||cont<0&&r<=r1))ans+=c[j].v;
					}
					else{
						ld cont=zero(x1,y1,x2,y2);
						if(x<0&&(cont>0&&r<=r1||cont<0&&r1<=r))ans+=c[j].v;
						if(x>=0&&(cont>0&&r2<=r||cont<0&&r<=r2))ans+=c[j].v;
					}
				}
			cout<<ans<<endl;
		}
	}
    return 0;
}
```


---

$\mathrm{Sol\ 2}:$

观察到测试点 $5-8$ 中所有 $y$ 相等。

用线段树维护区间加法与区间求最大值即可，甚至连离散化都不需要。为了避免访问到负数下标，我们可以将所有 $x$ 加上 $10^5+1$。

时间复杂度：$\mathcal O(n\log n)$。

- 可以通过测试点 $5-8$。

期望得分：$20\%$，结合 $\mathrm{Sol\ 1}$ 可得 $40\%$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
struct Plane{
	int a,b,c,d,v;
}p[N<<2];
struct Seg_Tree{
	int v[N<<4],lz[N<<4];
	void push_down(int x){
		lz[x<<1]+=lz[x],v[x<<1]+=lz[x];
		lz[x<<1|1]+=lz[x],v[x<<1|1]+=lz[x];
		v[x]=max(v[x<<1],v[x<<1|1]);
		lz[x]=0;
	}
	void modify(int l,int r,int ql,int qr,int x,int val){
		if(ql<=l&&r<=qr){
			v[x]+=val,lz[x]+=val;
			return;
		}
		push_down(x);
		int m=(l+r)>>1;
		if(ql<=m)modify(l,m,ql,qr,x<<1,val);
		if(m<qr)modify(m+1,r,ql,qr,x<<1|1,val);
		v[x]=max(v[x<<1],v[x<<1|1]);
	}
	ll query(ll l,ll r,ll ql,ll qr,ll x){
		push_down(x);
		v[x]=max(v[x<<1],v[x<<1|1]);
		if(ql<=l&&r<=qr)return v[x];
		ll m=l+r>>1,ans=0;
		if(ql<=m)ans=max(ans,query(l,m,ql,qr,x<<1));
		if(m<qr)ans=max(ans,query(m+1,r,ql,qr,x<<1|1));
		return ans;
	}
}t;
int n,cnt,des[N<<2];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int opt;cin>>opt;
		if(opt==1){
			cnt++;
			cin>>p[cnt].a>>p[cnt].b>>p[cnt].c>>p[cnt].d>>p[cnt].v;
			if(p[cnt].a>p[cnt].c)swap(p[cnt].a,p[cnt].c);
			t.modify(1,N<<1,p[cnt].a+N,p[cnt].c+N,1,p[cnt].v);
		}
		if(opt==2){
			int d;
			cin>>d;
			des[d]=1;
			t.modify(1,N<<1,p[d].a+N,p[d].c+N,1,-p[d].v);
		}
		if(opt==3){
			int x,y;
			cin>>x>>y;
			cout<<t.query(1,N<<1,x+N,x+N,1)<<endl;
		}
		if(opt==4){
			int d;
			cin>>d;
			if(des[d])puts("oops!");
			else cout<<t.query(1,N<<1,p[d].a+N,p[d].c+N,1)<<endl;
		}
	}
    return 0;
}
```


---

$\mathrm{Sol\ 3}:$

观察到测试点 $9-12$ 中 $x\ge 0$。

求出所有 $r_1,r_2,r$，离散化后用**一个**线段树**离线**维护即可。

时间复杂度：$\mathcal O(n\log n)$。

- 可以通过测试点 $9-12$。

期望得分：$20\%$，结合 $\mathrm{Sol\ 1,2}$ 可得 $60\%$。

---

$\mathrm{Sol\ 4}:$

求出所有 $r_1,r_2,r$，根据 **$x$ 是否不大于 $0$** **分别离散化后用两个**线段树**离线**维护。如果一个平面镜穿过了 $y$ 轴，则像 $\mathrm{Sol\ }1$ 一样，将它分成两半分别考虑。

时间复杂度：$\mathcal O(n\log n)$。

期望得分：$100\%$。

---

$\mathrm{std:}$

常数极大，细节较多。

（据说用极角比这种方法更简单，但是出题人太菜，不会）

```cpp
#include<map>
#include<iostream>
#include<algorithm>
using namespace std;
#define ld long double
inline int read(){
	int x=0,sign=1;char s=getchar();
	while(!isdigit(s)){
		if(s=='-')sign=-1;
		s=getchar();
	}
	while(isdigit(s)){
		x=(x<<1)+(x<<3)+(s^48);
		s=getchar();
	}
	return x*sign;
}
int max(int a,int b){
	return a>b?a:b;
}
const int N=2e5+5;
const ld inf=2e9;
struct operation{
	int opt,x1,y1,x2,y2,d;
	int v;
	ld r1,r2;
}p[N];
struct Segment_Tree{//维护区间加法，区间求最大值的线段树
	int v[N<<3],lz[N<<3],siz;
	void push_up(int x){
		v[x]=max(v[x<<1],v[x<<1|1]);
	}
	void push_down(int l,int r,int x){
		if(!lz[x])return;
		v[x<<1]+=lz[x];
		v[x<<1|1]+=lz[x];
		lz[x<<1]+=lz[x];
		lz[x<<1|1]+=lz[x];
		lz[x]=0;
	}
	void modify(int l,int r,int ql,int qr,int x,int val){
		if(ql<=l&&r<=qr){
			v[x]+=val;
			lz[x]+=val;
			return;
		}
		push_down(l,r,x);
		int m=l+r>>1;
		if(ql<=m)modify(l,m,ql,qr,x<<1,val);
		if(m<qr)modify(m+1,r,ql,qr,x<<1|1,val);
		push_up(x);
	}
	int query(int l,int r,int ql,int qr,int x){
		if(ql<=l&&r<=qr)return v[x];
		push_down(l,r,x);
		int ans=0,m=l+r>>1;
		if(ql<=m)ans=max(ans,query(l,m,ql,qr,x<<1));
		if(m<qr)ans=max(ans,query(m+1,r,ql,qr,x<<1|1));
		return ans;
	}
}lt,rt;//lt为x<0时的线段树，rt为x>=0时的线段树
map <ld,int> lmp,rmp;//分别离散化
ld lpo[N<<1],rpo[N<<1];//落在（左/右）边的点的r值
int n,cnt,pl[N],lp,rp,des[N];//lp/rp 为落在（左/右）边的点的个数，des[i]为第i个平面镜是否被摧毁
void swap(operation &x)//交换平面镜的两个端点
{
	swap(x.x1,x.x2);
	swap(x.y1,x.y2);
	swap(x.r1,x.r2);
}
ld ratio(ld x,ld y){//求r值 
	if(x==0)return y>0?inf:-inf;//特判x为0的情况，这时候可以设r为一个极（大/小）值
	else return y/x;
}
ld zero(ld x1,ld y1,ld x2,ld y2){//求平面镜与y轴的交点的纵坐标
	ld k=(y1-y2)/(x1-x2),b=y1-k*x1;//待定系数法
	return b;
}
void init(){
	n=read();
	for(int i=1;i<=n;i++){
		p[i].opt=read();
		if(p[i].opt==1){
			p[i].x1=read(),p[i].y1=read();
			p[i].x2=read(),p[i].y2=read();
			p[i].v=read();
			if(p[i].x1>=0)p[i].r1=rpo[++rp]=ratio(p[i].x1,p[i].y1);
			else p[i].r1=lpo[++lp]=ratio(p[i].x1,p[i].y1);
			if(p[i].x2>=0)p[i].r2=rpo[++rp]=ratio(p[i].x2,p[i].y2);
			else p[i].r2=lpo[++lp]=ratio(p[i].x2,p[i].y2);//上面四行都是加点，求r
			if((p[i].x1>=0&&p[i].x2>=0||p[i].x1<0&&p[i].x2<0)&&p[i].r1>p[i].r2)swap(p[i]);//将所有未穿过y轴的平面镜的端点变为r1<=r2，方便计算
			if(p[i].x1<0&&p[i].x2>=0)swap(p[i]);//将所有穿过y轴的平面镜的端点变为x1>=0,x2<0，方便计算 
		}
		if(p[i].opt==2||p[i].opt==4)p[i].d=read();
		if(p[i].opt==3){
			p[i].x1=read(),p[i].y1=read();
			if(p[i].x1>=0)p[i].r1=rpo[++rp]=ratio(p[i].x1,p[i].y1);
			else p[i].r1=lpo[++lp]=ratio(p[i].x1,p[i].y1);//上面两行都是加点，求r
		}
	}
	rt.siz=rp;
	lt.siz=lp;
}
void discretize(){//离散化
	sort(rpo+1,rpo+rp+1);
	for(int i=1;i<=rp;i++)rmp[rpo[i]]=i;
	sort(lpo+1,lpo+lp+1);
	for(int i=1;i<=lp;i++)lmp[lpo[i]]=i;
}
void Add_Plane_Mirror(int x1,int y1,int x2,int y2,ld r1,ld r2,int val){//添加/摧毁平面镜 
	if(x1>=0&&x2>=0){
		rt.modify(1,rt.siz,rmp[r1],rmp[r2],1,val);
	}
	else if(x1<0&&x2<0){
		lt.modify(1,lt.siz,lmp[r1],lmp[r2],1,val);
	}
	else{
		ld cont=zero(x1,y1,x2,y2);
		if(cont>0){
			rt.modify(1,rt.siz,rmp[r1],rt.siz,1,val);
			lt.modify(1,lt.siz,1,lmp[r2],1,val);
		}
		else{
			rt.modify(1,rt.siz,1,rmp[r1],1,val);
			lt.modify(1,lt.siz,lmp[r2],lt.siz,1,val);
		}
	}
}
void solve(){
	for(int i=1;i<=n;i++){
		if(p[i].opt==1){
			pl[++cnt]=i;
			Add_Plane_Mirror(p[i].x1,p[i].y1,p[i].x2,p[i].y2,p[i].r1,p[i].r2,p[i].v);
		}
		if(p[i].opt==2){
			if(!des[p[i].d]){
				int d=pl[p[i].d];
				Add_Plane_Mirror(p[d].x1,p[d].y1,p[d].x2,p[d].y2,p[d].r1,p[d].r2,-p[d].v);
				des[p[i].d]=1;
			}
		}
		if(p[i].opt==3){
			int pos;
			if(p[i].x1>=0){
				pos=rmp[p[i].r1];
				printf("%d\n",rt.query(1,rt.siz,pos,pos,1));
			}
			else{
				pos=lmp[p[i].r1];
				printf("%d\n",lt.query(1,lt.siz,pos,pos,1));
			}
		}
		if(p[i].opt==4){
			if(des[p[i].d])puts("oops!");
			else{
				int d=pl[p[i].d];
				if(p[d].x1>=0&&p[d].x2>=0){
					printf("%d\n",rt.query(1,rt.siz,rmp[p[d].r1],rmp[p[d].r2],1));
				}
				else if(p[d].x1<0&&p[d].x2<0){
					printf("%d\n",lt.query(1,lt.siz,lmp[p[d].r1],lmp[p[d].r2],1));
				}
				else{
					ld cont=zero(p[d].x1,p[d].y1,p[d].x2,p[d].y2);
					if(cont>0){
						printf("%d\n",max(rt.query(1,rt.siz,rmp[p[d].r1],rt.siz,1),lt.query(1,lt.siz,1,lmp[p[d].r2],1)));
					}
					else{
						printf("%d\n",max(rt.query(1,rt.siz,1,rmp[p[d].r1],1),lt.query(1,lt.siz,lmp[p[d].r2],lt.siz,1)));
					}
				}
			}
		}
	}
}
int main(){
	init();
	discretize();
	solve();
	return 0;
}
```


---

