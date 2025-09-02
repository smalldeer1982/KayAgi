# Minimum Sum

## 题目描述

You are given a set of $ n $ vectors on a plane. For each vector you are allowed to multiply any of its coordinates by -1. Thus, each vector $ v_{i}=(x_{i},y_{i}) $ can be transformed into one of the following four vectors:

- $ v_{i}^{1}=(x_{i},y_{i}) $ ,
- $ v_{i}^{2}=(-x_{i},y_{i}) $ ,
- $ v_{i}^{3}=(x_{i},-y_{i}) $ ,
- $ v_{i}^{4}=(-x_{i},-y_{i}) $ .

You should find two vectors from the set and determine which of their coordinates should be multiplied by -1 so that the absolute value of the sum of the resulting vectors was minimally possible. More formally, you should choose two vectors $ v_{i} $ , $ v_{j} $ ( $ 1<=i,j<=n,i≠j $ ) and two numbers $ k_{1} $ , $ k_{2} $ ( $ 1<=k_{1},k_{2}<=4 $ ), so that the value of the expression $ |v_{i}^{k_{1}}+v_{j}^{k_{2}}| $ were minimum.

## 说明/提示

A sum of two vectors $ v=(x_{v},y_{v}) $ and $ u=(x_{u},y_{u}) $ is vector $ s=v+u=(x_{v}+x_{u},y_{v}+y_{u}) $ .

An absolute value of vector $ v=(x,y) $ is number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF120J/f38b71729f5e7990a499daa93821211f59c1e021.png).

In the second sample there are several valid answers, such as:

(3 1 4 2), (3 1 4 4), (3 4 4 1), (3 4 4 3), (4 1 3 2), (4 1 3 4), (4 2 3 1).

## 样例 #1

### 输入

```
5
-7 -3
9 0
-8 6
7 -8
4 -5
```

### 输出

```
3 2 4 2
```

## 样例 #2

### 输入

```
5
3 2
-4 7
-6 0
-8 4
5 1
```

### 输出

```
3 4 5 4
```

# 题解

## 作者：lottle1212__ (赞：3)

# [CF120J Minimum Sum](https://www.luogu.com.cn/problem/CF120J)

首先要知道平面最近点对，即一个平面内的 $n$ 个点两两距离的最小值，是可以在 $O(n \log n)$ 的时间内求出的。而在这题中，要求两个向量和的模长最小值。向量模长的公式与距离公式类似，因此容易想到：把加改成减，即将其中一个向量的 $x, y$ 都取负再与另一向量相减，模长就成了两点间的距离，即可用上述算法求解。

再说说平面最近点对。在分治算法中，比较妙的就是处理经过左右两边的贡献时的操作。假设当前左右区间分别处理完后最小距离为 $d$，则新的产生贡献的点对横坐标之差不超过 $d$，因此只留下距离中间的分割点横坐标之差不超 $d$ 的点。同理，新点对纵坐标之差也应不超 $d$。精髓便在此处。如果枚举到左侧一个点，则只需考虑右侧横纵坐标之差均不超过 $d$ 的点，而右侧的点两两间距离必不小于 $d$（因为 $d$ 是最小距离）。即在右侧一个 $d \times 2d$ 的矩阵内，距离不超 $d$ 的点最多只能放 $6$ 个，这样左侧每个点最多只需判断 $6$ 次，可视为常数。

上述讲了最精妙的部分，具体实现就是排个序然后双指针，而排序可用归并实现，则单层复杂度 $O(n)$，总复杂度  $O(n \log n)$。

最后提醒一点，这题有文件输入输出。

以上简略讲述，具体详见代码。

```cpp
#include <iostream>
#include <algorithm>
#include <string.h>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define fst first
#define scd second
#define db double
#define ll long long
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector <int>
#define pii pair <int, int>
#define sz(x) ((int)x.size())
#define ms(f, x) memset(f, x, sizeof(f))
#define L(i, j, k) for (int i=(j); i<=(k); ++i)
#define R(i, j, k) for (int i=(j); i>=(k); --i)
#define ACN(i, H_u) for (int i=H_u; i; i=E[i].nxt)
using namespace std;
template <typename INT> void rd(INT &res) {
	res=0; bool f=false; char ch=getchar();
	while (ch<'0'||ch>'9') f|=ch=='-', ch=getchar();
	while (ch>='0'&&ch<='9') res=(res<<1)+(res<<3)+(ch^48), ch=getchar();
	res=(f?-res:res);
}
template <typename INT, typename...Args>
void rd(INT &x, Args &...y) { rd(x), rd(y...); }
//dfs
const int inf=0x3f3f3f3f;
const int maxn=1e5;
const int N=maxn+10;
int n, xi, yi, xk, yk, m, ans=inf;
//wmr
struct node {
	int x, y, id;
	node () {}
	node (int _x, int _y, int _id) { x=_x, y=_y, id=_id; }
	bool operator < (const node &k) const { return x<k.x||x==k.x&&y<k.y; }
} a[N<<2], b[N<<2], pl[N<<2], pr[N<<2];
int sq(int x) { return x*x; }
int dist(node x, node y) { return sq(x.x-y.x)+sq(x.y-y.y); }
void minimize(int &d, node x, node y) {
	int res=dist(x, y);
	if (res<d) d=res;
	if (res<ans) {
		ans=res;
		xi=(x.id-1)%n+1;
		yi=(y.id-1)%n+1;
		xk=(x.id-1)/n+1;
		yk=4-(y.id-1)/n;
	}
}
//incra
int divide(int l, int r) {
	if (l==r) return inf;
	int mid=l+r>>1; node pmid=a[mid];
	int d=min(divide(l, mid), divide(mid+1, r));
	int cntl=0, cntr=0;
	L(i, l, mid) if (sq(a[i].x-pmid.x)<=d) pl[++cntl]=a[i];
	L(i, mid+1, r) if (sq(a[i].x-pmid.x)<=d) pr[++cntr]=a[i];
	int cur=1;
	L(i, 1, cntl) {
		while (cur<=cntr&&sq(pl[i].y-pr[cur].y)>d&&pl[i].y>pr[cur].y) ++cur;
		int ccur=cur;
		while (ccur<=cntr&&sq(pl[i].y-pr[ccur].y)<=d) {
			if (pl[i].id%n!=pr[ccur].id%n) minimize(d, pl[i], pr[ccur]);
			++ccur;
		}
	}
	int curl=l, curr=mid+1; cur=l-1;
	while (curl<=mid&&curr<=r)
		if (a[curl].y<a[curr].y) b[++cur]=a[curl++];
		else b[++cur]=a[curr++];
	while (curl<=mid) b[++cur]=a[curl++];
	while (curr<=r) b[++cur]=a[curr++];
	L(i, l, r) a[i]=b[i];
	return d;
}
//lottle
signed main() {
//	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("CF120J.in", "r", stdin);
	freopen("CF120J.out", "w", stdout);
	rd(n);
	L(i, 1, n) {
		int x, y; rd(x, y);
		a[i]=node(x, y, i);
		a[i+n]=node(-x, y, i+n);
		a[i+n*2]=node(x, -y, i+n*2);
		a[i+n*3]=node(-x, -y, i+n*3);
	}
	sort(a+1, a+(n<<2)+1);
	divide(1, n<<2);
	printf("%d %d %d %d\n", xi, xk, yi, yk);
	return 0;
}
/*
input
5
-7 -3
9 0
-8 6
7 -8
4 -5
output
3 2 4 2
*/
```

---

## 作者：juju527 (赞：2)

### 平面最近点对问题

不会的同学可以考虑学习一下

[模板](https://www.luogu.com.cn/problem/P1429)

我们要找到两个向量加起来使得向量的模最小

因为对于每一个向量原题中都允许使用x，y分别取负的向量

我们考虑$(x_1+x_2,y_1+y_2)$

等于$(x_1-(-x_2),y_1-(-y_2))$

而$(-x_2,-y_2)$这个向量同样是我们可以用的

我们就能强行把向量的和的模看作平面上两点的距离

然后对于每一个向量4组向量都当作一个点去跑平面最近点对

记录一下哪了哪一个向量，最后输出时因对称反转一下第二个向量

因为我们算距离时第二个点用的是x,y反转后的向量

**然后注意要开文件**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005,inf=1e9;
const double eps=1e-8;
struct point{
	int id,flag;
	double x,y;
	bool operator <(point i)const{
		return x<i.x;
	}
}a[4*maxn],t[4*maxn];
double dis=inf;
int p,u,q,v;
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
int change(int x){
	if(x==1)return 4;
	if(x==2)return 3;
	if(x==3)return 2;
	return 1;
}
bool cmp(point p,point q){
	return p.y<q.y;
}
double dist(point p,point q){
	double x=p.x-q.x,y=p.y-q.y;
	return sqrt(x*x+y*y);
}
double dfs(int l,int r){
	if(l==r)return inf;
	if(r-l==1){
		if(a[l].id==a[r].id)return inf;
		if(dis-dist(a[l],a[r])>eps){
			dis=dist(a[l],a[r]);
			p=a[l].id;u=a[l].flag;
			q=a[r].id;v=a[r].flag;
		}
		return dist(a[l],a[r]);
	}
	int mid=l+((r-l)>>1);
	double d1=dfs(l,mid),d2=dfs(mid+1,r);
	double d=min(d1,d2);
	int cnt=0;
	for(int i=l;i<=r;i++)
		if(fabs(a[i].x-a[mid].x)-d<eps)
			t[++cnt]=a[i];
	sort(t+1,t+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		for(int j=i+1;j<=cnt;j++){
			if(fabs(t[i].y-t[j].y)-d>eps)break;
			if(t[i].id==t[j].id)continue;
			if(d-dist(t[i],t[j])>=eps){
				d=dist(t[i],t[j]);
				if(dis-d>eps){
					dis=d;
					p=t[i].id;u=t[i].flag;
					q=t[j].id;v=t[j].flag;
				}
			}
		}
	}
	return d;
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	n=read();
	for(int i=1;i<=n;i++){
		int x,y;
		x=read();y=read();
		a[i].id=i;a[i].flag=1;a[i].x=x;a[i].y=y;
		a[i+n].id=i;a[i+n].flag=2;a[i+n].x=-x;a[i+n].y=y;
		a[i+2*n].id=i;a[i+2*n].flag=3;a[i+2*n].x=x;a[i+2*n].y=-y;
		a[i+3*n].id=i;a[i+3*n].flag=4;a[i+3*n].x=-x;a[i+3*n].y=-y;
	}
	sort(a+1,a+4*n+1);
	dfs(1,4*n);
	printf("%d %d %d %d",p,u,q,change(v));
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF120J)     
## 解法
首先，我们可以把向量的加法变为减法，即 $\left|v_1^{k1}+v_2^{k2}\right|=\left|v_1^{k1}-(-v_2^{k2})\right|$。    
那么这题就转化为了一个[平面最近点对](https://www.luogu.com.cn/problem/P7883)问题。    
我们处理出所有可能的点，之后在求解平面最近点对的过程中判断两个点是否是同一个点即可。    
注意输出时需要把第二个向量的状态取反。   
CODE：   
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
const int N=4e5;
int n;
Point p[N+10];
vector<int>pans,vans;
il db dist(cst Point& a,cst Point& b){
	ret (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
il int get(cst int& x){
	if(x==1){
		ret 4;
	}else if(x==2){
		ret 3;
	}else if(x==3){
		ret 2;
	}else{
		ret 1;
	}
}
struct node{
	db ans;
	vector<int>v;
	il void init(){
		for(int i=0;i<4;i++){
			v.push_back(0);
		}
	}
};
il bool operator<(cst db& a,cst node& b){
	ret dcmp(a-b.ans)<0;
}
il node min(cst node& a,cst node& b){
	ret a.ans>b.ans?b:a;
}
il node sqrt(cst node& a){
	ret node{sqrt(a.ans),a.v};
}
il node findmin(int l,int r){
	if(r-l<=6){
		node ans;
		ans.ans=1e18;
		ans.init();
		for(int i=l;i<=r;i++){
			for(int j=i+1;j<=r;j++){
				if(p[i].id==p[j].id){
					continue;
				}
				if(dist(p[i],p[j])<ans){
					ans.v[0]=p[i].id;
					ans.v[1]=p[i].k;
					ans.v[2]=p[j].id;
					ans.v[3]=get(p[j].k);
					ans.ans=dist(p[i],p[j]);
				}
			}
		}
		sort(p+l,p+1+r,[](cst Point& a,cst Point& b){ret a.y<b.y;});
		ret ans;
	}
	int mid=l+r>>1;
	double xm=0.5*(p[mid].x+p[mid+1].x);
	node h2=findmin(l,mid);
	h2=min(findmin(mid+1,r),h2);
	node h=sqrt(h2);
	inplace_merge(p+l,p+mid+1,p+r+1,[](cst Point& a,cst Point& b){ret a.y<b.y;});
	static Point B[N+10];
	int bcnt=0;
	for(int i=l;i<=r;i++){
		if(dcmp(p[i].x-(xm-h.ans))>=0&&dcmp(p[i].x-(xm+h.ans))<=0){
			B[++bcnt]=p[i];
		}
	}
	node ans=h2;
	ans.init();
	for(int i=1;i<=bcnt;i++){
		for(int j=i-1;j>=1&&dcmp(B[j].y-(B[i].y-h.ans))>=0;j--){
			if(B[i].id==B[j].id){
				continue;
			}
			if(dist(B[i],B[j])<ans){
				ans.v[0]=B[i].id;
				ans.v[1]=B[i].k;
				ans.v[2]=B[j].id;
				ans.v[3]=get(B[j].k);
				ans.ans=dist(B[i],B[j]);
			}
		}
	}
	ret ans;
}
int tot;
il void add(cst db& x,cst db& y,cst int& z,cst int& k){
	p[++tot].x=x;
	p[tot].y=y;
	p[tot].id=z;
	p[tot].k=k;
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	for(int i=0;i<4;i++){
		pans.push_back(0);
		vans.push_back(0);
	}
	cin>>n;
	for(int i=1;i<=n;i++){
		double x,y;
		cin>>x>>y;
		add(x,y,i,1);
		add(-x,y,i,2);
		add(x,-y,i,3);
		add(-x,-y,i,4);
	}
	n=tot;
	sort(p+1,p+1+n,[](cst Point& a,cst Point& b){ret a.x<b.x;});
	node ans=findmin(1,n);
	for(int i=0;i<4;i++){
		cout<<ans.v[i]<<" ";
	}
	ret 0;
}
```


---

