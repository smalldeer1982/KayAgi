# Tower Capturing

## 题目描述

有 $n$ 个塔，分别位于 $n$ 个不同的点 $(x_1, y_1), (x_2, y_2), \ldots, (x_n, y_n)$，保证没有三点共线，也没有四点共圆。最开始，你拥有 $(x_1, y_1)$ 和 $(x_2, y_2)$ 这两个塔，你的目标是占领所有的塔。为此，你可以进行如下操作任意次：

- 选择你已经拥有的两个塔 $P$ 和 $Q$，以及一个你尚未拥有的塔 $R$，要求经过 $P$、$Q$、$R$ 的圆能够包含所有 $n$ 个塔在其内部或边界上。
- 然后，你可以占领在三角形 $\triangle PQR$ 内部或边界上的所有塔，包括 $R$ 本身。

一次“攻击方案”是指一系列选择 $R$（$R_1, R_2, \ldots, R_k$）的操作，最终使你占领了所有的塔。注意，只有当某一步选择的 $R$ 不同时，两个攻击方案才被认为是不同的；如果选择的 $R$ 相同，但 $P$ 和 $Q$ 不同，则认为是同一个方案。请你计算最短长度的攻击方案的数量。如果无法占领所有塔，输出 $0$。

由于答案可能很大，请输出对 $998\,244\,353$ 取模后的结果。

## 说明/提示

在第一个测试用例中，只有一种最短的攻击方案，如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1984H/4db430879d9ca247997fc2913e9569a1772c78ba.png)

- 第一步，选择 $P=$塔 $1$，$Q=$塔 $2$，$R=$塔 $5$。经过这三座塔的圆包含了所有塔，因此塔 $3$ 和塔 $5$ 都被占领。
- 第二步，选择 $P=$塔 $5$，$Q=$塔 $1$，$R=$塔 $4$。经过这三座塔的圆包含了所有塔，因此塔 $4$ 被占领。

在第二个测试用例中，例如，位于 $(3, 10\,000)$ 的塔永远无法被占领。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
5
1 1
2 5
3 3
4 2
5 4
6
1 1
3 3
1 2
2 1
3 10000
19 84
7
2 7
-4 -3
-3 6
3 1
-5 2
1 -4
-1 7```

### 输出

```
1
0
10```

# 题解

## 作者：Nightingale_OI (赞：4)

### 大意

给定二维平面上的 $n$ 个点 $(x_i,y_i)$，保证没有任意两点重合、没有任意三点共线、没有任意四点共圆。初始时，你拥有点 $1$ 和点 $2$，剩下 $n-2$ 个点是未拥有的。

每次操作可以选择三个不同的点 $P,Q,R$，需要满足你拥有点 $P,Q$，未拥有点 $R$，且所有的 $n$ 个点都在过 $P,Q,R$ 得到的圆内。然后你拥有 $\triangle PQR$ 内的还未拥有的点（包括点 $R$）。

问有多少种不同的操作序列能够让你拥有所有点。两个操作序列不同当且仅当它们的长度不同，或某一步操作选择的无序三元组 $(P,Q,R)$ 不同。

保证 $n\leq 100,\sum n\leq 1000,0\leq|x_i|,|y_i|\leq 10^4$。

### 思路

找到这 $n$ 个点的凸包。操作时选择的 $P,Q,R$ 都必须在凸包上，否则过它们的圆一定会把凸包分成两部分，包含不了所有的 $n$ 个点。称 $\triangle PQR$ 是好的，当且仅当所有的 $n$ 个点都在过 $P,Q,R$ 得到的圆内（$P,Q,R$ 是凸包的顶点）。

先说结论，所有好的三角形构成这 $n$ 个点的凸包的三角剖分。等价表述是：

1. 任意两个好的三角形公共面积为 $0$。
2. 所有好的三角形的并为凸包。

证明 $1$ 考虑两个好的三角形 $\triangle ABC,\triangle DEF$，过 $A,B,C$ 得到圆 $P$，过 $D,E,F$ 得到圆 $Q$。

由于圆 $P$ 和圆 $Q$ 都包含所有的 $n$ 个点，所以两个圆肯定相交。两个圆的公共部分（红色）包含所有的 $n$ 个点，即 $A,B,C,D,E,F$ 都在两个圆的公共部分内。

如图所示，又因为 $A,B,C$ 都在圆 $P$ 上，所以只能在 $l$ 的左边，同理 $D,E,F$ 都在圆 $Q$ 上，所以只能在 $l$ 的右边，所以这两个三角形的公共面积为 $0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4eyjjyqx.png)

证明 $2$ 考虑任意好的三角形 $\triangle PQR$。我们称 $R$ 在直线 $PQ$ 的右侧，另一侧为左侧。

因为不存在四点共圆，若 $PQ$ 左侧还有点，一定可以找到一个唯一的点 $R'$ 使得 $\triangle PQR'$ 是好的的。

因此我们可以递归地进行三角剖分。

我们操作过所有好的三角形就是拥有所有点的充要条件。也就是总操作数是确定的。

初始拥有的两个点必须在凸包上，其会将凸包分为两部分，这两部分答案独立，最后将两部分的操作序列合并，乘上一个组合数。

递归三角剖分时，我们找到过 $P,Q$ 两点的好三角形，又会分出两个独立的子问题，合并时同样乘组合数。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
#define double long double
const int N=202,mo=998244353;
const double eps=1e-5;
struct xy{int x,y;}a[N];int c[N][N];
xy operator*(xy a,xy b){return {a.x+b.x,a.y*b.y%mo*c[a.x+b.x][a.x]%mo};}
void mdl(int i,int j,double&A,double&B,double&C){
	xy p=a[i],q=a[j];
	double X=(p.x+q.x)*0.5,Y=(p.y+q.y)*0.5;
	A=(p.x-q.x);B=(p.y-q.y);C=-A*X-B*Y;
}
int ck(int x,double X,double Y){
	#define D(a)(a.x-X)*(a.x-X)+(a.y-Y)*(a.y-Y)
	f(i,1,n)if(D(a[i])>D(a[x])+eps)return 0;
	return 1;
}
xy dfs(int x,int y,int fa){
	xy f={0,1},g;double A,B,C,D,E,F,G;
	f(z,1,n)if(z!=x&&z!=y&&z!=fa){
		mdl(x,z,A,B,C);mdl(y,z,D,E,F);G=A*E-B*D;
		if(ck(x,(B*F-C*E)/G,(C*D-A*F)/G)){
			g=dfs(x,z,y)*dfs(y,z,x);++g.x;f=f*g;
		}
	}
	return f;
}
inline void doing(){
	cin>>n;
	f(i,1,n)cin>>a[i].x>>a[i].y;
	f(i,0,n)f(j,0,i)c[i][j]=(j?c[i-1][j]+c[i-1][j-1]:1)%mo;
	xy f=dfs(1,2,0);cout<<(f.x>0)*f.y<<"\n";
}
signed main(){
	int t;
	cin>>t;
	while(t--)doing();
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

**CF1984 H**

我觉得这道题是滔天大芬，为什么唯一一篇题解写得这么轻松。

------------------------------------------------------

~~对于没有思路的计算几何先找找凸包，看有没有什么相关性质。~~

不过由于三点对应的圆要包含所有点，那么三个点必须得在凸包上，一个感性反证是考虑极限，想要包含所有点的充要条件是包含整个凸包，而由于某个点在凸包内那么这个圆的某条弦对应的某个端点附近的一小块区域是在凸包内的，也就不可能包含所有点。

[![pAEB8iD.png](https://s21.ax1x.com/2024/08/31/pAEB8iD.png)](https://imgse.com/i/pAEB8iD)

记能包含所有点的圆 PQR 对应的三角形 PQR 是合法的。

接下来发现没有好的突破口，只能考虑找合法三角形自身的性质了。

- 任意的两个合法三角形公共面积为 0。

考虑两个对应的圆，由于两个三角形都在凸包内，所以两个三角形都在两个圆的公共区域内。



[![pAEBHSJ.png](https://s21.ax1x.com/2024/08/31/pAEBHSJ.png)](https://imgse.com/i/pAEBHSJ)



如图蓝线为两圆的公共弦，而由于两个三角形要分别出现在两个圆上且要在公共区域上，所以只能在公共区域内蓝线的左右两边出现。

- 任意两个点确定下来，可以组成合法三角形关联的第三个点至多有两个。

由性质一，这两个点组成的线段就是公共弦，而公共弦左右两边只会出现一个合法三角形。

- 在存在合法方案的情况下所有合法三角形的并为凸包本身

由性质一，如果最后能把所有点都包含下来那必然所有合法三角形要把凸包上的所有点取完才行。

又由于合法三角形的所有点都在凸包上，且任意合法三角形公共面积为 0，所以**凸包上的每条边都会出现在合法三角形中**，不然凸包上一定会有一个凸出去的点被某个合法三角形“独立”出去以至于在后续无法被加入已拥有的点，如图紫点：

[![pAEDwc9.png](https://s21.ax1x.com/2024/08/31/pAEDwc9.png)](https://imgse.com/i/pAEDwc9)





自然的，凸包内有区域没被合法三角形的并覆盖可以对应到有凸包上的点没有被覆盖，故所有合法三角形的并一定是凸包，结合性质一可以知道这是一个三角剖分。

观察到存在递归形式的计数方法：

- 我们每次传入三个参数代表对应的合法三角形的三个端点，其中前两个参数表示现在要在这个三角剖分内扩展下一个合法三角形对应的边端点，称这条边为扩展边。
- 寻找这条边扩展到的下一个合法三角形（由性质二只会有至多一个）。
- 该合法三角形的新端点和原合法三角形的扩展边对应的两个点组合成新的两个扩展边，继续递归下去，递归完后由于存在选择的先后关系所以要在信息中记录可能产生的所有合法三角形的数量，对应的组合问题为合并各自相对顺序确定的待操作数为 $m$ 和  $n$ 的两种操作，乘上 $C_{m}^n$ 即可。
- 注意到最开始只有扩展边，所以可能存在向两个方向扩展的合法三角形，特判一下即可。

忠告：开 long double。

时间复杂度 $O(n^3)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
#define db long double
#define int long long
const int Len = 205 , mod = 998244353;
const db eps = 1e-5;
int n,m,c[Len][Len];
struct info
{
	int x,y;
	info(){x = 0 , y = 1;}
	info(int X,int Y){x = X , y = Y;}
};
info operator + (info a,info b){return info(a.x + b.x , a.y * b.y % mod * c[a.x + b.x][a.x] % mod);}
struct V
{
	db x,y;
	V(){x = y = 0;}
	V(db X,db Y){x = X , y = Y;}
	inline void clr(){x = y = 0;}
}a[Len];
struct line{V d,a,b;line(){d.clr() , a.clr() , b.clr();}line(V D,V A,V B){d = D , a = A , b = B;}};
inline V operator + (V x,V y){return V(x.x + y.x , x.y + y.y);}
inline V operator - (V x,V y){return V(x.x - y.x , x.y - y.y);}
inline V operator * ( V x, db a){return V(x.x * a , x.y * a);}
inline V operator / ( V x, db a){return V(x.x / a ,x.y / a);}
inline V vc( V x){return V(-x.y , x.x);}//vertical
inline db operator ^ (V x,V y){return x.x * y.y - x.y * y.x;}
inline db len(V x){return sqrt(x.x * x.x + x.y * x.y);}
inline V uni(V x){return x / len(x);}
inline db erdis(V x,V y){return (y.x - x.x) * (y.x - x.x) + (y.y - x.y) * (y.y - x.y);}
inline V crs(line a,line b)
{
	db k = ((b.a - a.a) ^ b.d) / (a.d ^ b.d);
  	return a.a + (a.d * k);
}
inline V midP(V a,V b){return V((a.x + b.x) / 2 , (a.y + b.y) / 2);}
inline line mkline(V a,V b)
{
	V A,B,D;
	A = midP(a , b) , D = vc(uni(b - a));
	return line(D , A , A + D * 10);
}
inline int ck(int id,db X,db Y)
{
	for(int i = 1 ; i <= n ; i ++) if(erdis(a[id] , V(X , Y)) < -eps + erdis(a[i] , V(X , Y))) return 0;
	return 1;
}
info dfs(int x,int y,int ff)
{
	info f,g;V O;
	//printf("#%d %d %d\n",x,y,ff);
	for(int z = 1 ; z <= n ; z ++)
	{
		if(z == x || z == y || z == ff) continue;
		O = crs(mkline(a[x] , a[z]) , mkline(a[y] , a[z]));
		if(ck(x , O.x , O.y)) 
		{
			g = dfs(x , z , y) + dfs(y , z , x);
			g.x ++;
			f = f + g;
			if(ff) return f;
		}
	}
	return f;
}
signed main()
{
	int T;scanf("%lld",&T);
	while(T --)
	{
		scanf("%lld",&n);
		for(int i = 1 ; i <= n ; i ++) scanf("%llf %llf",&a[i].x,&a[i].y);
		for(int i = 0 ; i <= n ; i ++) for(int j = 0 ; j <= i ; j ++) c[i][j] = (j ? c[i - 1][j] + c[i - 1][j - 1] : 1) % mod;
		info ans = dfs(1 , 2 , 0);
		printf("%lld\n",(ans.x > 0) * ans.y); 
	}
	return 0;
}
```

---

## 作者：Union_of_Britain (赞：0)

由于四点不共圆，$\odot  PQR$（不妨设 $R$ 在 $PQ$ 右侧）可以覆盖所有点的一个必要条件是：$R$ 是所有 $PQ$ 右侧点 $A$ 中 $\angle PAQ$ （唯一）最小的点。

充要条件则是任意 $PQ$ 左侧点 $B$ 均满足 $\angle PBQ\le \pi -\angle PQR$。

此外，如果 $\odot PQR$ 覆盖了所有点，显然 $P,Q,R$ 均在所有点的凸包上。

回到原问题，易见可以忽略非凸包点；过程是比较简单的，一开始的点 $1,2$ 向左右扩展唯一（甚至可能不存在，此时答案为 $0$）的点 $3,4$ 再递归子问题 $1\to 3,3\to 2,2\to 4,4\to 1$……

这样的过程是否唯一？相当于，是否可能存在这样的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/i13nme4p.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

这里 $ABD,ABC$ 的外接圆均包含了所有点，而这样已经知道 $AB$ 是不可能再用的；而经过简单的导角可以得到 $\angle CED>\angle CBD>\angle CAB$，$\odot CED$ 是不可能覆盖所有点的。

因此这样的过程唯一，实际上问题答案即树的拓扑序计数。这是容易的，而每次分治下去只需找到最小角度，显然可以 $O(n^2)$ 完成，应该可以借助数据结构工具做到更好。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e3+5,mod=998244353;
#define db double
const db pi=acos(-1.0),eps=1e-6;
struct pt{int x,y,id;}p[maxn];
int T,n,fac[1005],ifac[1005];
pt operator +(pt A,pt B){return {A.x+B.x,A.y+B.y,-1};}
pt operator -(pt A,pt B){return {A.x-B.x,A.y-B.y,-1};}
int operator *(pt A,pt B){return A.x*B.x+A.y*B.y;}
int operator ^(pt A,pt B){return A.x*B.y-A.y*B.x;}
db len(pt A){return sqrt(A.x*A.x+A.y*A.y);}
db angle(pt A,pt B){
	if(A*B==0)return pi/2;
	if(A*B>0)return asin(1.0*(A^B)/len(A)/len(B));
	return pi-asin(1.0*(A^B)/len(A)/len(B));
}
int dcmp(db x){return (x>eps)-(x<-eps);}
int stk[maxn],tp=0,C,ans=1;
bool cmp(pt A,pt B){
	db ta=atan2(A.y-p[1].y,A.x-p[1].x),tb=atan2(B.y-p[1].y,B.x-p[1].x);
	if(dcmp(ta-tb)==0)return len(A-p[1])<len(B-p[1]);
	return ta<tb;	
}
int G(int x){++x;if(x==tp+1)x=1;return x;}
int P(int x){--x;if(x==0)x=tp;return x;}
int dis(int x,int y){int t=0;while(x!=y)++t,x=G(x);return t-1;}
int qp(int a,int b){
	if(b==0)return 1;
	int T=qp(a*a%mod,b>>1);
	if(b&1)T=T*a%mod;
	return T;
}
int CC(int a,int b){return fac[a]*ifac[b]%mod*ifac[a-b]%mod;}
void solve(int a,int b){
	if(b==G(a))return ;
	vector<int> T;int x=G(a);
	while(x!=b)T.push_back(x),x=G(x);
	db mn=1e9;int pos=-1;
	for(auto x:T){
		db A=angle(p[stk[x]]-p[stk[b]],p[stk[x]]-p[stk[a]]);
		if(A<mn)mn=A,pos=x;
	}bool flg=1;
	x=G(b);while(x!=a){
		db A=angle(p[stk[x]]-p[stk[a]],p[stk[x]]-p[stk[b]]);
		if(dcmp(A-(pi-mn))<0)flg=0;
		x=G(x);
	}
	if(!flg)return ans=0,void();
	ans=ans*CC(dis(a,pos)+dis(pos,b),dis(a,pos))%mod;
	solve(a,pos),solve(pos,b);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;int N=1000;
	fac[0]=1;for(int i=1;i<=N;i++)fac[i]=fac[i-1]*i%mod;
	ifac[N]=qp(fac[N],mod-2);for(int i=N-1;i>=0;i--)ifac[i]=ifac[i+1]*(i+1)%mod;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>p[i].x>>p[i].y,p[i].id=i;
		C=1;for(int i=2;i<=n;i++)if(p[i].y<p[C].y||(p[i].y==p[C].y&&p[i].x<p[C].y))C=i;
		swap(p[1],p[C]);sort(p+2,p+n+1,cmp);
		stk[tp=1]=1;
		for(int i=2;i<=n;i++){
			while(tp>1&&((p[i]-p[stk[tp-1]])^(p[stk[tp]]-p[stk[tp-1]]))>0)--tp;
			stk[++tp]=i;
		}int r1=-1,r2=-1;
		for(int i=1;i<=tp;i++){
			if(p[stk[i]].id==1)r1=i;
			if(p[stk[i]].id==2)r2=i;
		}
		if(r1==-1||r2==-1)cout<<0<<endl;
		else{
			ans=CC(dis(r1,r2)+dis(r2,r1),dis(r1,r2));
			solve(r1,r2);
			solve(r2,r1);
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

