# [POI 2014] LAM-Solar lamps

## 题目描述

Byteasar has a large and pretty garden.

As he would like to be able to appreciate its beauty even after dusk,he installed lamps across the garden.

The lamps are directional, i.e., they illuminate only a certain angle, common to them all.

Moreover, Byteasar has aligned them so that they all face the same direction.

Last but not least, these are solar lamps, i.e., they come with solar panelsbut no batteries, strangely enough!  You might think the panels are thus useless,and each lamp will require electricity at night, but not quite: A lamp will produce lightif a sufficient number of lamps illuminate it.

By now, Byteasar has even come up with an order he is going supply the lamps with electricity,thus turning them on.

For simplicity, we number the lamps from 1 to $n$ in this order, i.e., the lamp no. $i$ is supplied with electricity at time $i$.  The only thing left for Byteasar (and you, of course!) is tofigure out when exactly each lamp will start emitting light.  Help Byteasar by writing a programthat will determine the answer to this question.

给N盏灯，没盏灯能照到的角度范围是相同的，第i盏灯在第i秒或者被ki盏灯照到后都会亮起，问所有灯都在什么时刻亮起


## 说明/提示

给N盏灯，没盏灯能照到的角度范围是相同的，第i盏灯在第i秒或者被ki盏灯照到后都会亮起，问所有灯都在什么时刻亮起


## 样例 #1

### 输入

```
5
3 1 1 3
2 1
1 4
3 4
5 6
5 2
1 2 1 3 2
```

### 输出

```
1 2 1 2 5
```

# 题解

## 作者：墨舞灵纯 (赞：2)

第一感觉就是毒瘤计算几何，然后看了看题解，发现要转换坐标系，把给定的向量看成方向向量，作为基底解方程。

$$a_i(x_1,y_1)+b_i(x_2,y_2)=(x_i,y_i)$$

$$a_i=\frac{x_iy_2-x_2y_i}{x_1y_2-x_2y_1},b_i=\frac{x_1y_i-x_iy_1}{x_1y_2-x_2y_1}$$

然后发现分母没啥影响，所以我们可以转化为求一个二维的第$K$大。

带修主席树吼啊！ $\rightarrow$    卡内存！

树套树吼啊！$\rightarrow$    卡常数！（当然据说线段树套平衡树可以过，可惜我人丑常数大。。）

于是又看了看题解，发现可以整体二分。

$solve(L,R,l,r)$表示$l,r$范围内被照亮的时间为$L,R$，二分递归下去解决。关键问题是求一盏灯什么时候被点亮。这个的关键在于求它左下角有多少灯。这是一个经典的二维数点的问题，第一维排序第二维树状数组统计即可，左下角$\gt k_i$或者编号$\gt mid$
就归到左区间去，反之去右区间。

哦对，还有一个问题就是光线可能是一条直线，所以我们要把向量稍微偏移一个角度。

复杂度$O(nlog^2n)$

upd：没过审……补充一点代码实现的细节吧。

首先是处理角度，这个判断一下是否为直线然后处理偏移就好。

然后就是转换坐标系并离散化坐标，也不必多说。

接下来就是整体二分。思路就是考虑编号$\le mid$的点和左下角$\le k_i$的点都归为左区间，然后把这个点加到树状数组里去，否则就把这个点的$k_i$减去它左下角有的点。

然后就是递归求解，但要注意判断边界。

```cpp
#include<stdio.h>
#include<algorithm>
#define it register int
#define ct const int
#define il inline
using namespace std;
const int N=1000005;
struct ky{
	int x,y,id,k;
}a[N];
int ans[N],n,X1,Y1,X2,Y2,tr[N];
typedef long long ll;
ll x[N],y[N],tmp[N];
il bool cmp(const ky p,const ky q){return p.x^q.x?p.x<q.x:p.y<q.y;}
template <class I>
il void sp(I &p,I &q){I x=p;p=q,q=x;}
il void add(it x,ct num){while(x<N) tr[x]+=num,x+=(x&-x);}
il void que(it x,int &num){num=0;while(x) num+=tr[x],x-=(x&-x);}
il void solve(ct u,ct v,ct l,ct r){
	if(u==v){
		for(it i=l;i<=r;++i) ans[a[i].id]=u;
		return;
	}
	ct Mid=u+v>>1;it mid=l-1;
	std::sort(a+l,a+r+1,cmp);
	for(it i=l,now;i<=r;++i)
		que(a[i].y,now),(a[i].id<=Mid||now>=a[i].k)?add(a[i].y,1),++mid,sp(a[mid],a[i]),0:a[i].k-=now;//按照上文的思路写
	for(it i=l;i<=mid;++i) add(a[i].y,-1);
	if(l<=mid) solve(u,Mid,l,mid);
	if(mid<r) solve(Mid+1,v,mid+1,r);
}
template <class I>
il I Max(I p,I q){return p>q?p:q;}
template <class I>
il I A(I p){return p<0?-p:p;}
il void cgd(int &x,int &y){
	ct mx=Max(A(x),A(y)),d=((ll)2e9+mx-1)/mx;
	x*=d,y*=d,++x;
}
int main(){ 
	scanf("%d%d%d%d%d",&n,&X1,&Y1,&X2,&Y2);it i,xx,yy;
	if((0ll+X1)*Y2==(0ll+X2)*Y1) cgd(X1,Y1);//一条直线 改变角度 偏移一下
	if((0ll+X1)*Y2<(0ll+X2)*Y1) sp(X1,X2),sp(Y1,Y2);//调整方向
	for(i=1;i<=n;++i)
		scanf("%d%d",&xx,&yy),a[i].id=i,x[i]=(0ll+xx)*Y2-(0ll+X2)*yy,y[i]=(0ll+X1)*yy-(0ll+xx)*Y1;
	for(i=1;i<=n;++i) scanf("%d",&a[i].k);
	for(i=1;i<=n;++i) tmp[i]=x[i];
	std::sort(tmp+1,tmp+1+n),tmp[0]=std::unique(tmp+1,tmp+1+n)-tmp-1;
	for(i=1;i<=n;++i) a[i].x=std::lower_bound(tmp+1,tmp+1+tmp[0],x[i])-tmp;
	for(i=1;i<=n;++i) tmp[i]=y[i];
	std::sort(tmp+1,tmp+1+n),tmp[0]=std::unique(tmp+1,tmp+1+n)-tmp-1;
	for(i=1;i<=n;++i) a[i].y=std::lower_bound(tmp+1,tmp+1+tmp[0],y[i])-tmp; 
    //离散化坐标
	solve(1,n,1,n);//整体二分
	for(i=1;i<=n;++i) printf("%d ",ans[i]);
	return 0; 
}



---

## 作者：renhao (赞：1)

## Solar lamps

二维平面上有一堆灯，这些灯的照射范围在固定的两个向量 $(x_1,y_1),(x_2,y_2)$ 之间

一盏灯 $i$ 被点亮当且仅当它被通电或被至少 $k_i$ 盏灯照亮。

问每盏灯被照亮的最短时间。

也是很显然的一个二分。

但是这个平面几何很难处理啊。

然后就去看了题解。

然后才知道要把坐标系转一下变成标准的二维平面直角坐标系。
这个就有点不怎么方便了，但是其实可以直接把给定向量看成方向向量，作为基底，直接乘过去，就表示了向量坐标系的点。
$a_i(x1,y1)+b_i(x2,y2)=(x_i,y_i);$

$a_ix1+b_ix2=x_i;$

$a_iy1+b_iy2=y_i$

$a_i=\frac{(x_iy2-y_ix2)}{(x1y2-y1x2)}$

$b_i=\frac{(x_iy1-y_ix1)}{(x1y2-y1x2)}$




由于这个题目在距离等比变化的情况下并没有差别，所以可以直接把分母忽略。

那么就把问题变成在一个二维平面内求一个矩阵里面的第k个被点亮的点。

起先看到了不小心点开来的 Tag 发现树套树我还是不会写啊。

但是发现所有人都写了整体二分，那么就写整体二分吧。

话说这题如果整体二分的话真的是十分好写
就是用排序去掉一维，用BIT维护另一维，那么就特别优秀了。

复杂度 $\Theta(n*log^2)$
```c
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define db double
#define x1 mo
#define y1 th
#define x2 er 
#define y2 fu
#define dot cker
using namespace std;
const int INF=2e9;
const int N=2e5+10;
int n;
void rot(ll &x,ll &y){
	ll mx=max(abs(x),abs(y));
	mx=(mx+INF-1)/mx;
	x*=mx;
	y*=mx;
	x++;
}
struct node{
	ll x,y;
	int id;
	
	//first: x second: y 
	bool operator <(const node &a)const{
		if(x!=a.x) return x<a.x;
		return y<a.y;	
	}
};
node A[N],Left[N],Right[N];
int k[N];//need
int ori[N],ans[N];
ll x1,y1,x2,y2;
vector<int>ve;
int bit[N<<1];//the compressed indice of nodes might be twice as large as n

//BIT
void Add(int x,int a){
	while(x<=n*2){
		bit[x]+=a;
		x+=x&-x;
	}
}
int Query(int x){
	int cnt=0;
	while(x){
		cnt+=bit[x];
		x-=x&-x;
	}
	return cnt;
}
void Solve(int L,int R,int l,int r){
	if(L>R) return ;
	
	if(L==R){
		for(int i=l;i<=r;i++){
			ans[A[i].id]=L;
		}
		return ;
	}
	
	int mid=(L+R)>>1;
	sort(A+l,A+r+1);
	
	//clear
	ve.clear();
	for(int i=l;i<=r;i++) ori[i]=k[A[i].id];
	
	//scan
	for(int i=l;i<=r;i++){
		int x=A[i].id,to=Query(A[i].y);
		k[x]-=to;
		if(k[x]<=0||x<=mid){
			Add(A[i].y,1);
			ve.pb(i);
		}
	}
	
	//recover
	int p=0,q=0;
	for(int i=l;i<=r;i++){
		int x=A[i].id;
		if(k[x]>0&&x>mid){
			Right[++q]=A[i];
		}
		else{
			Left[++p]=A[i];
			k[x]=ori[i];
		}
	}
	for(int i=0;i<ve.size();i++) Add(A[ve[i]].y,-1);
	
	int pt=l;
	for(int i=1;i<=p;i++) A[pt++]=Left[i];
	for(int i=1;i<=q;i++) A[pt++]=Right[i];
	
	Solve(L,mid,l,l+p-1);
	Solve(mid+1,R,l+p,r);
}

vector<ll>xs;
int main(){
//	freopen("lamps.in","r",stdin);
//	freopen("lamps.out","w",stdout);
	
	scanf("%d",&n);
	scanf("%lld %lld %lld %lld",&x1,&y1,&x2,&y2);
	
	//special condition
	if(x1*y2==x2*y1) rot(x1,y1);
	if(1ll*x1*y2<1ll*x2*y1)swap(x1,x2),swap(y1,y2);
	//redefination
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		A[i].x=(1ll*x*y2-y*x2);
		A[i].y=(1ll*x1*y-x*y1);
		xs.pb(A[i].x);
		xs.pb(A[i].y);
	}
	
	//compress
	sort(xs.begin(),xs.end());
	xs.erase(unique(xs.begin(),xs.end()),xs.end());
	for(int i=1;i<=n;i++){
		A[i].x=lower_bound(xs.begin(),xs.end(),A[i].x)-xs.begin()+1;
		A[i].y=lower_bound(xs.begin(),xs.end(),A[i].y)-xs.begin()+1;
		A[i].id=i;
	}
	
	for(int i=1;i<=n;i++) scanf("%d",&k[i]);
	
	//binary search
	Solve(1,n,1,n);
	
	for(int i=1;i<=n;i++){
		printf("%d",ans[i]);
		if(i!=n) printf(" ");
	}
	return 0;
}
```

---

