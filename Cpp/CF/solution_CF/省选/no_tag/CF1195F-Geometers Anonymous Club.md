# Geometers Anonymous Club

## 题目描述

n个凸多边形 $（1 <= n <= 100000  ）$ ,顶点总数不超过$ 300000 $ ；

有q $(1 <= q <= 100000)$  个询问，每个询问到$r_i$编号多边形的闵可夫斯基和

（闵可夫斯基和：A ，B的闵可夫斯基和就是C = {a+b},a,b是A，B中的元素，结合图形理解一下qwq）

## 样例 #1

### 输入

```
3
3
0 0
1 0
0 1
4
1 1
1 2
0 2
0 1
3
2 2
1 2
2 1
3
1 2
2 3
1 3
```

### 输出

```
5
5
6
```

# 题解

## 作者：Fading (赞：6)

### 题意

给定$n$个凸包，多次询问，求编号$[l,r]$之间的所有凸包做闵可夫斯基和得到的凸包的边数。
 
显然两个凸包的所有按照极角序连起来的边，斜率递增。

然后考虑闵可夫斯基和的构造方式，就是根据极角序归并。

所以相同斜率的边，只会出现一次（重复的点都省略了）。

对于每一个凸包，极角排序，求出相邻点的斜率，然后每一次询问等价于求区间有多少个不同的斜率。

直接离线+树状数组即可。 

### 细节

注意$+0,-0$算两种，$+\infty,-\infty$ 算两种。  
 
仿佛给定的凸包已经极角排序好了，所以直接连就可以了？
注意离散化。 

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
	static char now[1<<16],*S,*T;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
map<pair<int,int>,int> has;
int n,m,col[620001],id,cnt,K[620001][2],tr[620001],L[620001],R[620001];
int las[620001],pre[620001];
inline int query(int x){
	int ans=0;
	for (;x;x-=x&-x) ans+=tr[x];
	return ans;
}
inline void add(int x,int y){
	if (!x) return;  
	for (;x<=cnt;x+=x&-x) tr[x]+=y;
}
int ans[1000001];
struct QUE{
	int l,r,id;
}q[1000001];
inline bool cmp(QUE a,QUE b){
	return (a.r==b.r?a.l<b.l:a.r<b.r);
}
signed main(){
	n=read();
	for (int i=1;i<=n;i++){
		L[i]=cnt+1;R[i]=L[i]+read()-1;
		for (int j=1;j<=R[i]-L[i]+1;j++){
			K[j][0]=read();K[j][1]=read();
		}
		for (int j=2;j<=R[i]-L[i]+1;j++){
			pair<int,int> P=make_pair(K[j][1]-K[j-1][1],K[j][0]-K[j-1][0]);
			int G=__gcd(abs(P.first),abs(P.second));
			P.first/=G;P.second/=G; 
			if (!has.count(P)) has[P]=++id;
			col[++cnt]=has[P];
		}
		pair<int,int> P=make_pair(K[1][1]-K[R[i]-L[i]+1][1],K[1][0]-K[R[i]-L[i]+1][0]);
		int G=__gcd(abs(P.first),abs(P.second));
		P.first/=G;P.second/=G; 
		if (!has.count(P)) has[P]=++id;
		col[++cnt]=has[P];
	}
	m=read();
	for (int i=1;i<=m;i++){
		q[i].id=i;q[i].l=L[read()];q[i].r=R[read()];
	}
	for (int i=1;i<=cnt;i++){
		pre[i]=las[col[i]];las[col[i]]=i;
	}
	sort(q+1,q+1+m,cmp);
	for (int tmp=1,i=1;i<=m;i++){
		for (;tmp<=q[i].r;tmp++) add(tmp,1),add(pre[tmp],-1);
		ans[q[i].id]=query(q[i].r)-query(q[i].l-1);
	}
	for (int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}

```


---

## 作者：Piwry (赞：0)

## 解析

考虑做闵可夫斯基和的过程：就是将边向量排序；而方向相同的边向量排序后都是相邻的，会成为**同一条边**

于是每次询问实质上就是在求区间内所有凸包的不同的边向量种类数

考虑给每种边向量染上同一颜色，于是我们需要做的实际上就是统计区间颜色个数（只是这里的区间中每个位置可能有多组颜色...）

可以直接离线线段树搞；但莫队也可以

可能第一印象会觉得复杂度比较奇怪。实际上只要考虑将每个位置的凸包内的边元素都 “展开”，于是每组询问本质上仍是一般的区间查询，只不过 $l, r$ 的最小增量大于 $1$ 罢了

（例如对于 $\{p_0, p_1, p_2\}, p_0=\{l_0, l_1, l_2\}, p_1 =\{l_3, l_4, l_5, l_6\}, p_2=\{l_7, l_8, l_9\}$，可以 “展开” 变为 $\{l_0, l_1, l_2, l_3, l_4, l_5, l_6, l_7, l_8, l_9\}$）

如有不太清楚的地方可以参考代码内注释理解 \kk

## CODE

```cpp
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using std::vector;
using std::map;
using std::pair;
using std::sort;

const int MAXN =1e5+20, MAXK =4e5+20;

/*------------------------------IO------------------------------*/

namespace MyIO{
	const int MAXB =1<<18;
	char gbuf[MAXB], *ps =gbuf, *pt =gbuf;
	char pbuf[MAXB+1], *pp =pbuf;
	struct Flusher{
		~Flusher(){
			fwrite(pbuf, 1, pp-pbuf, stdout);
		}
	}flusher;
	
	inline char Getchar(){
		if(ps == pt){
			ps =gbuf;
			pt =gbuf+fread(gbuf, 1, MAXB, stdin);
		}
		return (ps == pt) ? EOF : *ps++;
	}
	inline void Putchar(const char &ch){
		if(pp == pbuf+MAXB){
			pp =pbuf;
			fwrite(pbuf, 1, MAXB, stdout);
		}
		*pp++ =ch;
	}
}
#define getchar MyIO::Getchar
#define putchar MyIO::Putchar

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

void write(const int &x){
	if(x/10)
		write(x/10);
	putchar('0'+x%10);
}

/*------------------------------Pre------------------------------*/

int gcd(int a, int b){
	while(b ^=a ^=b ^=a %=b) ;
	return a;
}

inline int Abs(const int &x){ return (x < 0) ? -x : x; }

struct line{
	int k_up, k_down;/*斜率的分子，分母*/
	
	line(){}
	line(const int &KU, const int &KD){
		if(KU == 0 || KD == 0){
			k_up =(KU != 0) ? ((KU > 0) ? 1 : -1) : 0;
			k_down =(KD != 0) ? ((KD > 0) ? 1 : -1) : 0;
		}
		else{
			// 边向量的不同朝向会在分子分母的符号中体现出来 //
			int Gcd =Abs(gcd(KU, KD));
			k_up =KU/Gcd;
			k_down =KD/Gcd;
		}
	}
	
	bool operator < (const line &B) const{/*仅用于 map 做区分*/
		if(k_up == B.k_up)
			return k_down < B.k_down;
		else
			return k_up < B.k_up;
	}
};

int tot;
map<line, int> Map;

/*------------------------------莫队------------------------------*/

vector<int> poly[MAXN];

struct query{
	int l, r, cl, id;
	
	bool operator < (const query &B) const{
		if(cl == B.cl)
			return (cl&1) ? r < B.r : r > B.r;
		else
			return cl < B.cl;
	}
}q[MAXN];

int cnt[MAXK];
int Ans;

void add(const int &pos){
	for(int col:poly[pos])
		if(++cnt[col] == 1)
			++Ans;
}

void del(const int &pos){
	for(int col:poly[pos])
		if(--cnt[col] == 0)
			--Ans;
}

/*------------------------------Main------------------------------*/

int ans[MAXN];

int pre[MAXN];
//	 ^- 展开后，原序列位置对应的新序列位置的下标 ( 这里是从 1 开始 ) //

int main(){
	int n =read();
	for(int i =0; i < n; ++i){
		int k =read();
		pre[i+1] =pre[i]+k;
		int s_x =read(), s_y =read();
		int pre_x =s_x, pre_y =s_y;
		for(int j =0; j < k-1; ++j){
			int x =read(), y =read();
			line l =line(y-pre_y, x-pre_x);
			if(Map.count(l))
				poly[i].push_back(Map.find(l)->second);
			else{
				poly[i].push_back(++tot);
				Map.insert(pair<line, int>(l, tot));
			}
			pre_x =x, pre_y =y;
		}
		line l =line(s_y-pre_y, s_x-pre_x);
		if(Map.count(l))
			poly[i].push_back(Map.find(l)->second);
		else{
			poly[i].push_back(++tot);
			Map.insert(pair<line, int>(l, tot));
		}
	}
	
	int Q =read();
	int S =sqrt(1.0*pre[n]*pre[n]/Q);/*<<- */
	if(S == 0)
		S =1;
	for(int i =0; i < Q; ++i){
		q[i].l =read()-1, q[i].r =read()-1;
		q[i].id =i, q[i].cl =pre[q[i].l+1]/S;/*<<- */
	}
	sort(q, q+Q);
	for(int i =0, l =0, r =0; i < Q; ++i){
		while(l < q[i].l) del(l++);
		while(l > q[i].l) add(--l);
		while(r < q[i].r+1) add(r++);
		while(r > q[i].r+1) del(--r);
		ans[q[i].id] =Ans;
	}
	
	for(int i =0; i < Q; ++i)
		write(ans[i]), putchar('\n');
}
```

---

