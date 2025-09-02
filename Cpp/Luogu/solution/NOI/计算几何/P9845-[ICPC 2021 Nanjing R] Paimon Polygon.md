# [ICPC 2021 Nanjing R] Paimon Polygon

## 题目描述

派蒙在平面上放置了$n+1$个互异的点，其中有一特殊点$O=(0,0)$，并记其余点为$\mathbb{S}$。

我们称一个点集 $\mathbb{U}$ 为$\textit{strict convex set}$，当且仅当点集中点的个数大于等于3（$|\mathbb{U}| \ge 3$）且$\mathbb{U}$中的所有点位于$\mathbb{U}$构成的凸包上，且任意三点不共线。


你需要将$\mathbb{S}$划分为两个集合 $\mathbb{A}$ 和$\mathbb{B}$，使其满足
- $\mathbb{A} \cap \mathbb{B}=\emptyset$.
- $\mathbb{A} \cup \mathbb{B}=\mathbb{S}$.
- $|\mathbb{A}| \ge 2, |\mathbb{B}| \ge 2$.

- 点集 $\mathbb{A} \cup \{O\}$ 是 $\textit{strict convex set}$，并记它的凸包为$C_{\mathbb{A} \cup \{O\}}$。
- 点集 $\mathbb{B} \cup \{O\}$是 $\textit{strict convex set}$，并记它的凸包为 $C_{\mathbb{B} \cup \{O\}}$。
- $C_{\mathbb{A} \cup \{O\}}$和 $C_{\mathbb{B} \cup \{O\}}$ 的轮廓 仅在 $O$相交。 这也就是说，仅有点$O$既在$C_{\mathbb{A} \cup \{O\}}$的轮廓上，又在$C_{\mathbb{B} \cup \{O\}}$的轮廓上。
  
请协助派蒙计算出这两个凸包周长之和的最大值。
这也就是说，找到一个合法的划分方案$\mathbb{A}$ 和 $\mathbb{B}$，使得 $(L(C_{\mathbb{A} \cup \{O\}}) + L(C_{\mathbb{B} \cup \{O\}}))$最大，其中$L(\text{polygon})$代表多边形的周长。

## 样例 #1

### 输入

```
3
4
0 3
3 0
2 3
3 2
5
4 0
5 -5
-4 -2
1 -2
-5 -2
4
0 1
1 0
0 2
1 1
```

### 输出

```
17.2111025509
36.6326947621
0.0000000000
```

# 题解

## 作者：Diaоsi (赞：0)

[[ICPC2021 Nanjing R] Paimon Polygon](https://www.luogu.com.cn/problem/P9845)

恶心题，先分类讨论。

由于 $O$ 这个点比较特殊，我们可以从它入手，讨论它是否在 $\mathbb{S}\cup \{O\}$ 的凸包上。下文中的凸包都默认为严格凸包，即凸包轮廓上不存在三点共线。

**第一种情况：**$O\in C_{\mathbb{S}\cup \{O\}}$

对于这种情况，答案可能有两类，一类是完全包含，另一类是以极角序相邻的点作为分界。需要进一步划分。

**1. 完全包含：** 此时外层的凸包只能是 $C_{\mathbb{S}\cup \{O\}}$，把这个凸包求出来之后判断剩余的点和 $O$ 是否构成一个凸包即可。

![4](https://cdn.luogu.com.cn/upload/image_hosting/mgr5q8t8.png)

但是此时内层的凸包不一定合法，题目中要求两个凸包的交只能是 $O$，所以还要判掉下面这种情况：

![5](https://cdn.luogu.com.cn/upload/image_hosting/57o258y2.png)

即内层凸包中的点与外层凸包的轮廓重合。判断的方法也很简单，在最开始求外层凸包时，可以先求出非严格凸包。不难发现如果求出来的非严格凸包存在三点共线，那一定是不可能构成包含的局面的，可以直接跳过。

**2. 按照极角序分界：**

这种情况比较直观，可以参考下图：

![6](https://cdn.luogu.com.cn/upload/image_hosting/de1j4lkp.png)

首先把所有点按照极角排序，然后找到相对于 $O$ 的后继（图中为 $A$）按照逆时针的顺序把所有点扫一遍，扫的过程中把点集分成两半并判断两边是否合法，合法则计入答案。

判断合法的方式有很多，我们考虑极角序上相邻的三个点（逆时针顺序）,若其构成的向量为 $\mathbf{u}$ 和 $\mathbf{v}$ 且 $\mathbf{u}\times\mathbf{v}\leq 0$，那么这三个点一定不能在同一个集合中。

当前这种分裂方式只能消耗两组叉乘为负的点，大于两组则当前这种划分方式无解，暴力逐个判断即可，这个方法会在下一个大类中沿用。

**第二种情况：**$O\notin C_{\mathbb{S}\cup \{O\}}$

这种情况比较棘手，由于被划分的两个集合在按极角排序之后一定是一段连续的区间，故可以考虑旋转卡壳。

先将所有的点按照极角排序，令两个指针 $L,R$ 在点集上移动，$[L,R]$ 中的点划分至 $\mathbb{A}$，剩余的点划分至 $\mathbb{B}$。

考虑对于一个特定的 $L$，$R$ 的取值范围是 $[l,r]$。设 $L$ 的前驱为 $L^\prime$，$R$ 的后继为 $R^\prime$，两个集合分别合法的一个必要条件是 $\angle LOR<180^\circ$ 且 $\angle L^\prime OR^\prime <180^\circ$。

发现 $[l,r]$ 一定是 $\angle L^\prime OL$ 的对顶角划分出来的一段区间。而所有 $L$ 对应的区间都是**互不相交**且随着 $L$ 单调移动的，所以总的划分方案只有 $\mathcal{O}(n)$ 种。

![9](https://cdn.luogu.com.cn/upload/image_hosting/iyfjgpx2.png)

如上图，$B$ 对应的 $[l,r]$ 就是 $\{E,F,G,H\}$，发现这东西很好用旋转卡壳维护，每次扫到一个 $R$ 都考虑把 $L^\prime L$ 和 $RR^\prime$ 断开。

但角度这个条件并不充要，还是得考虑相邻的三元组。所有向量叉乘非正的三元组至多只能有四个（每断一条边至多消耗两个），所以在旋转卡壳的过程中还要判断所有的三元组是否都被消耗。

时间复杂度 $\mathcal{O}(n\log n)$，瓶颈在排序，代码细节较多。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=500010,M=5000010,INF=0x3f3f3f3f;
const ld eps=1e-6,inf=1e18;
int T,n,m,t,flg,s[N],v[N],w[N],b[N];
ld ans1,ans2;
struct rec{int x,y,z;};
vector<rec> h;

struct node{
	ll x,y;
	node(ll xx=0,ll yy=0){x=xx,y=yy;}
	void in(){scanf("%lld%lld",&x,&y);}
	void out(){printf("%lld %lld\n",x,y);}
}p[N],q[N];

node operator +(node a,node b){return node(a.x+b.x,a.y+b.y);}
node operator -(node a,node b){return node(a.x-b.x,a.y-b.y);}
ll operator *(node a,node b){return a.x*b.x+a.y*b.y;}
ll operator ^(node a,node b){return a.x*b.y-a.y*b.x;}

node operator *(ll x,node b){return node(x*b.x,x*b.y);}

node O(0,0),P(-1,0);
bool cmp1(node a,node b){return a.x!=b.x?a.x<b.x:a.y<b.y;}
bool cmp2(node a,node b){
	if(((a-O)^(b-O))==0){
		if(a*b>0)return a*a<b*b;
		else if((a^P)==0)return a.x<b.x;
		else return (a^P)<(b^P);
	}
    if(((P-O)^(a-O))==0&&(P.x-O.x)*(a.x-O.x)>0)return 1;
    if(((P-O)^(b-O))==0&&(P.x-O.x)*(b.x-O.x)>0)return 0;
    if((((P-O)^(a-O))>0)!=(((P-O)^(b-O))>0))return ((P-O)^(a-O))>((P-O)^(b-O));
    return ((a-O)^(b-O))>0;
}

ld sqr(ld x){return (ld)x*x;}
ld dis(node a,node b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}

ll chk(node a,node b,node c){
	return (b-a)^(c-b);
}

int pre(int i){return i==1?n:i-1;}
int nxt(int i){return i==n?1:i+1;}

bool check(){
	for(rec t:h)
		if(v[t.x]==v[t.y]&&v[t.x]==v[t.z])return 0;
	return 1;
}
ld solve1(){
	flg=0;
	int cnt=0,tot=0,cur=0;
	ld res=0;
	for(int i=1;i<=n;i++)q[i]=p[i];
	m=n+1;q[m]=node(0,0);
	//outer
	sort(q+1,q+m+1,cmp1);
	for(int i=1;i<=m;i++)v[i]=0;
	s[t=1]=1;
	for(int i=2;i<=m;i++){
		while(t>1&&chk(q[s[t-1]],q[s[t]],q[i])<0)t--;
		s[++t]=i;
	}
	for(int i=1;i<=t;i++){
		if(i>1)res+=dis(q[s[i-1]],q[s[i]]);
		v[s[i]]=1;
	}
	for(int i=1;i<=t;i++)b[++cur]=s[i];
	s[t=1]=1;
	for(int i=2;i<=m;i++){
		while(t>1&&chk(q[s[t-1]],q[s[t]],q[i])>0)t--;
		s[++t]=i;
	}
	for(int i=1;i<=t;i++){
		if(i>1)res+=dis(q[s[i-1]],q[s[i]]);
		v[s[i]]=1;
	}
	for(int i=t-1;i>1;i--)b[++cur]=s[i];
	for(int i=1;i<=m;i++){
		if(v[i]&&!q[i].x&&!q[i].y)w[++cnt]=i,flg=1;
		if(v[i])continue;
		if(!q[i].x&&!q[i].y)return 0;
		w[++cnt]=i;
	}
	//inner
	s[t=1]=w[1];
	for(int i=2;i<=cnt;i++){
		while(t>1&&chk(q[s[t-1]],q[s[t]],q[w[i]])>=0)t--;
		s[++t]=w[i];
	}
	for(int i=1;i<=t;i++){
		if(i>1)res+=dis(q[s[i-1]],q[s[i]]);
		v[s[i]]=2;
	}
	s[t=1]=w[1];
	for(int i=2;i<=cnt;i++){
		while(t>1&&chk(q[s[t-1]],q[s[t]],q[w[i]])<=0)t--;
		s[++t]=w[i];
	}
	for(int i=1;i<=t;i++){
		if(i>1)res+=dis(q[s[i-1]],q[s[i]]);
		v[s[i]]=2;
	}
	for(int i=1;i<=m;i++){
		if(!v[i])return 0;
		tot+=(v[i]==2);
	}
	if(tot<3)return 0;
	for(int i=1;i<=cur;i++)
		if(!chk(q[b[i==1?cur:i-1]],q[b[i]],q[b[i==cur?1:i+1]]))return 0;
	return res;
}
ld solve2(){
	ld res=0,tmp=0;
	h.clear();
	sort(p+1,p+n+1,cmp2);
	for(int i=1;i<=n;i++)v[i]=0;
	for(int i=1;i<=n;i++){
		if(chk(p[pre(i)],p[i],p[nxt(i)])<=0)h.pb((rec){pre(i),i,nxt(i)});
		if(!(p[i]^p[nxt(i)])&&(p[i]*p[nxt(i)])>0)return 0;
	}
	if(h.size()>4)return 0;
	if(flg){
		int flag=0,j=1;
		p[0]=node(0,0);
		for(int i=1;i<=n;i++)
			if((p[i]^p[nxt(i)])<=0)j=nxt(i);
		for(int i=1,k=j;i<=n;i++,k=nxt(k))
			tmp+=dis(p[k],p[nxt(k)]);
		tmp-=dis(p[pre(j)],p[j]);
		tmp+=dis(p[0],p[j]);
		tmp+=dis(p[0],p[pre(j)]);
		v[j]=1;j=nxt(j);
		for(int i=2;i<n-1;i++,j=nxt(j)){
			v[j]=1;
			if(!check())continue;
			flag=1;
			res=max(res,tmp+dis(p[0],p[j])+dis(p[0],p[nxt(j)])-dis(p[j],p[nxt(j)]));
		}
		if(flag)return res;
		return 0;
	}
	for(int i=1;i<=n;i++)tmp+=dis(p[i],p[nxt(i)]);
	v[1]=1;
	for(int i=1,j=1,k=1;i<=n;i++,k--){
		while((p[i]^p[nxt(j)])>0){
			j=nxt(j),v[j]=1,k++;
			if(!check()||n-k<2||(p[nxt(j)]^p[pre(i)])<=0)continue;
			res=max(res,tmp-dis(p[pre(i)],p[i])-dis(p[j],p[nxt(j)])
				+dis(p[0],p[i])+dis(p[0],p[j])+dis(p[0],p[pre(i)])+dis(p[0],p[nxt(j)]));
		}
		v[i]=0;
	}
	return res;
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)p[i].in();
	ans1=solve1();
	ans2=solve2();
	printf("%.10Lf\n",max(ans1,ans2));
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：5ab_juruo (赞：0)

两个凸集只有两种关系：包含或分离。

若两个凸集为包含关系，则外面的凸集必然为所有点（包括 $(0,0)$）的凸包。把整体的凸包剥掉后，剩下的点和 $(0,0)$ 必然构成另一个凸集，判断这组解是否合法即可。

若两个凸集分离，则考虑以 $(0,0)$ 为中心做极角排序，显然若两点极角序相同则必然无解。注意到两个凸集分别对应两个区间。

对于极角序上相邻三个点，若其叉积非正，则这三个点不能出现在同一个凸集中。注意到其逆命题也是成立的，即若一个区间上所有这样的三元组都合法，则这个区间就是一个合法的凸集。

考察如下过程：我们钦定点 $i$ 为一个凸集的起点，令 $j,k$ 为与点 $i$ 相对的点在极角序上的前驱后继，注意到只有 $[i,j]$ 可能成为一个合法的凸集区间。即，可能合法的凸集只有 $O(n)$ 个。这个过程可以双指针维护。

考虑如何判断是否合法。注意到两个分界点最多“消耗”掉 $4$ 个不合法的三元组，其余的三元组必须均合法。所以若不合法的三元组超过了 $4$ 个就直接无解，否则在 check 时，对于每个不合法的三元组，暴力判断是否被消耗即可。

代码：<https://qoj.ac/submission/111042>。

---

