# Birthday

## 题目描述

Anna's got a birthday today. She invited many guests and cooked a huge (nearly infinite) birthday cake decorated by $ n $ banana circles of different sizes. Maria's birthday is about to start in 7 minutes too, and while Anna is older, she decided to play the boss a little. She told Maria to cut the cake by $ k $ straight-line cuts (the cutting lines can intersect) to divide banana circles into banana pieces.

Anna has many guests and she wants everyone to get at least one banana piece. That's why she told Maria to make the total number of banana pieces maximum. It's not a problem if some banana pieces end up on the same cake piece — the key is to make the maximum number of banana pieces. Determine what result Maria will achieve.

## 样例 #1

### 输入

```
1 1
0 0 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 1
0 0 1
3 0 1
6 0 1
```

### 输出

```
6
```

## 样例 #3

### 输入

```
1 3
0 0 1
```

### 输出

```
7
```

# 题解

## 作者：xuanxuan001 (赞：4)

这题终于过了，发篇题解纪念一下。

这题还是去年 12 月初，教练每天给我们布置一整套 CF 题，基本都是远古场，一开始连两位数的都布置过，然后有一天就布置了这一场。

其实那时候布置这种套题也不是要我们都做出来，但那时我做完 BCD 后开了这一题，跟这题的~~冤缘~~就从此开始了。

咳咳扯远了，下面开始讲题~~讲接下来的剧情~~。

提前说明一下，下面配的图都是下面这组数据：

```
3 1
0 3 1
3 3 1
6 3 1
```

其实就是样例 2 整体往上挪了 3。

接下来讲的可能比较长，做好心理准备。

正文
-
首先这题本质就是让我们求出一个直线，使得它穿过的圆最多（相切不算），设这个直线穿过了 $x$ 个圆，那么答案就是 $n + xk + \dfrac{k(k-1)}{2}$。

证明很简单，只要你能找到一个直线，你必然就可以将这个直线变成一个很窄的道（因为相切不算），使得它依然经过这 $x$ 个圆。那么你只需要让这 $k$ 条直线都在这个道里，那么块数就增加了 $xk$ 个。然后再让这 $k$ 条直线在一个圆中来一个平面分割问题，块数就又增加了 $\dfrac{k(k-1)}{2}$ 个（经典的分割应该是 $\dfrac{k(k+1)}{2}$，但别忘了我们前面已经统计过 $k$ 个了）。再加上本来就有 $n$ 个圆即可。

一开始看到这题，可能大(jiu)部(zhi)分(you)人(wo)上来就会想枚举每个圆，然后限制这条直线必须经过这个圆。然后就可以以这个圆心为中心求出其他每个圆对应的角度区间，然后将这个区间加一，最后取区间 $\max$ 和答案取 $\max$。

但是很快就会发现它是错的，因为它其实限制了必须经过选中圆的圆心，但是这个直线可能一个圆心也不会经过。我看了 CF 上一些 AC 代码，应该是以这个思路为基础进行了更深的推导，最后是一个圆对应两个区间加一，但我看不懂是为什么，官方题解也几乎啥重要的东西都没讲，所以我暂时放弃了。

但到了今年 1 月中，我突然有了新的想法，这个想法完全抛弃了前面的思路。

首先，找到一个过原点的直线 $l$ 并限制找的直线必须与 $l$ 垂直。

然后以纵坐标增加的方向为正方向建一个与 $l$ 重合的数轴，单位长度与平面直角坐标系的单位长度相同，那么对于一个圆，设它的圆心与数轴的垂足位于数 $x$。那么其实这个圆就是数轴上的 $(x-r,x+r)$ 这一段区间，如果找的直线与 $l$ 的交点在这个区间里那么就过这个圆。

![](https://cdn.luogu.com.cn/upload/image_hosting/7kc51zuc.png?x-oss-oss-process=image/resize,m_lfit,h_510,w_675)

比如在 $l$ 是上图的样子的时候，三个区间就是这样的，这时只需要将这 $2n$ 个端点离散化，然后就是区间加，全局 $\max$ 了（上面那个图的数轴单位长度不匹配，但应该不影响理解，主要是几何画板的数轴没法斜过来，是用的直尺然后删到只剩刻度实现的）。

但是这样的 $l$ 有很多，求一次就需要 $O(n)$，所以看似很不可行。

但是如果你在闭上眼想象一下这个直线 $l$ 的旋转过程的话，你会发现：这些区间会不断地在数轴上移动~~废话~~，那么这 $2n$ 个值的大小关系也在不断变化~~废话 x2~~。

但是重点来了：每次的变化都是两个值的大小关系反转！而且我们并不关心这 $2n$ 个值在数轴上到底是多少，我们只关心它们间的一个排名，所以我们可以在发生一次变化后统计一次答案，而每次只是两个值交换，所以可以用一个线段树每次 $O(\log n)$ 维护。

下面考虑大小关系会变化多少次：继续想象一下，这次只有两个圆，设它们的圆心是 $A$ 和 $B$。区间不好考虑，我们只考虑它的中点，也就是圆心对应的位置，那么当 $l \bot AB$ 时，$AB$ 在数轴上的对应位置重合。当 $l \parallel AB$ 时，$AB$ 在数轴上的对应位置距离最远，等于 $\overline{AB}$，由于题目保证所有圆相离，所以这时的两个区间肯定是不相交的。所以可以大致脑补出这个两个区间应该是先完全分开然后再合到一起，直到大的区间包含小的区间（也有可能反之）。所以这两个区间中小的区间会“穿过”大的区间的一个端点两次，每次“穿过”对应着 2 次相交，所以共产生了 4 次变化，所以总的变化次数约为 $2n^2$，因此复杂度有保证。

有了大致思路后，接着就是如何找到每次变化发生的时间（认为发生是 $l$ 与 x 轴正半轴的夹角，下同）。

其实这部分比较好推，就是很简单的三角函数（下面的配图就省掉不必要的东西了）。

![](https://cdn.luogu.com.cn/upload/image_hosting/2zmpojvy.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

有了上面这个图，就很容易地推出 $AB$ 在数轴上对应的位置的距离为 $\overline{AB}\cos \alpha$。

反之，设 $AB$ 在数轴上对应的位置的距离为 $d$，那么 $\alpha = \operatorname{acos} \dfrac{d}{\overline{AB}}$。

发现 $A$ 区间与 $B$ 区间的端点有相交其实就是在 $d = r_A + r_B$ 或 $\operatorname{abs}(r_A - r_B)$ 的时候，以此求出对应的 $\alpha$，然后可以配合线段 $AB$ 的斜率求出 $l$ 的斜率，进而求出时间。一个 $\alpha$ 应该对应着两个时间，因为只要是相差 $\alpha$  就可以，有加减两种。知道了相等的时刻，那么只需要判断这个时刻前或者后一点时间时的大小关系就可以知道是哪个超过哪个了。

由于这些区间都不包含端点，所以在发生变化的时刻的答案一定不比发生完后优。

那么只需要求出每个变化的事件并记录下来，然后动态维护直线 $l$ 在旋转过程中这 $2n$ 个点的大小关系以及全局最大值即可。

实现过程极其艰难，我写出了到现在我 OI 生涯中最长的代码，（AC 代码短一些）5.79K。不建议各位把事件花在写这个代码上面，当时 1 月我是啥都没干码了整整三四天。

实现时还遇到了一个问题，就是同一时刻可能会有多个值相同，如下图（省掉了圆 1 的圆，因为如果再画出来就太乱了）：

![](https://cdn.luogu.com.cn/upload/image_hosting/i0ez26n4.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

可以发现当 $l$ 继续旋转到与 y 轴重合时，r1，r2，r3 会同时重合（l1，l2，l3也是），这时需要特殊处理。

1 月时我傻了，直接给所有的变化关系建图然后拓扑，同时求出每个联通块的排名然后再重新分配，需要开一堆 vector 来记录用过哪些点什么的，常数可想而知，当时好不容易写完了结果卡不过去（CF 编号小于 500 的运行时间翻倍，所以虽然时限有 4s 但其实我只有 2s 的时间），然后就只能放弃了。

但现在我又想了起来，想再卡一卡，优化了一些别的地方的常数后我觉得主要是需要解决这个拓扑。其实如果有多个，那么发生相遇前它们的排名一定是连续的，并且变化后一定是排名整体翻转。所以只需要用一个并查集记录每个变化关系形成的联通块即可，而新排名直接联通块中最大排名 - 入度即可。

改完后代码长度直接减了好几百 B，常数也小了不少，最后终于卡过去了。

复杂度：$O(n^2 \log n)$。这个的常数着实可观，最大时间一次 3836ms 一次 3774ms，基本是卡着时限过的，而且得靠选 C++20(64) 过，选 C++14 就 T 了。

代码
-
```
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#define Ty int
#define MAXN 1002
#define FOR(i,a,b) for(Ty i=a;i<=b;i++)
#define fOR(i,a,b) for(Ty i=a;i<b;i++)
#define ROF(i,a,b) for(Ty i=a;i>=b;i--)
#define rOF(i,a,b) for(Ty i=a;i>b;i--)
using namespace std;
typedef long long ll;
typedef double db;
const db eps=1e-7,PI=acos(-1);
typedef unsigned long long ull;
Ty _abs(Ty a){return a<0?-a:a;}
Ty maxn(Ty a,Ty b){return a>b?a:b;}
Ty minn(Ty a,Ty b){return a<b?a:b;}
bool eq(db a,db b){return a-b<eps&&b-a<eps;}
Ty sq(Ty a){return a*a;}
Ty qr(){
	char ch=getchar();Ty s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';
	return x*s;
}Ty n,k,x[MAXN],y[MAXN],r[MAXN],cnt,b[MAXN<<1],id[MAXN<<1],rk[MAXN<<1],t[MAXN<<1],ans;
Ty tre[MAXN<<3],tag[MAXN<<3],in[MAXN<<1],fa[MAXN<<1],mx[MAXN<<1],p,now,x1,x2;vector<Ty>spt;
db ag[MAXN],ds[MAXN],ang,a1,a2;bool c1,c2,vis[MAXN<<1];Ty sgl,sgr,sgk;
Ty getfa(Ty u){return fa[u]!=u?fa[u]=getfa(fa[u]):u;}
struct node{db t;Ty p1,p2;bool l1,l2;}a[MAXN*MAXN<<1];
//p1,p2 表示圆编号，l1,l2 表示是哪边的端点，1 表示左。意思是 2 的大小值超过了 1
bool cmp(node a,node b){return a.t<b.t;}
bool cmp2(Ty x,Ty y){return b[x]!=b[y]?b[x]<b[y]:in[x]>in[y];}
db _atan(Ty x,Ty y){
	if(x){
		if(y){
			if(y>0)return atan((db)y/x);
			else return atan((db)y/x)+PI;
		}else if(x>0)return 0;
		else return PI;
	}else if(y>0)return PI/2;
	else return PI*1.5;
}db js(Ty i,db ang){//解出圆 i 的圆心与 l(与 x 正半轴夹角为 ang)的垂足到圆心的距离（即数轴上的对应值）
	db k=tan(ang),b,fx,fy,ans;if(eq(k,0))return x[i];
	b=y[i]+(db)x[i]/k;fx=b*k/(k*k+1);fy=fx*k;
	ans=sqrt(fx*fx+fy*fy);return fy<0?-ans:ans;
}void slv(Ty i,Ty j,Ty d){//找到一个事件的发生时间
	db dst=sqrt(sq(x[i]-x[j])+sq(y[i]-y[j]));
	db p=_atan(x[j]-x[i],y[j]-y[i]),q=acos((db)d/dst);
	if(p<eps)p+=2*PI;a1=p-q;a2=p+q;if(a1<eps)a1+=PI;
	while(a1-PI>-eps)a1-=PI;while(a2-PI>-eps)a2-=PI; 
	c1=eq(js(i,a1),js(j,a1)+d);c2=eq(js(i,a2),js(j,a2)+d);if(eq(a1,a2))c2=false;
}void crct(Ty d){//确定事件的大小关系是谁超过谁（反了就交换）
	if(a[cnt].t>0.0005){
		if(js(a[cnt].p1,a[cnt].t-0.0001)-js(a[cnt].p2,a[cnt].t-0.0001)-d<eps){
			a[cnt].p1^=a[cnt].p2^=a[cnt].p1^=a[cnt].p2;
			a[cnt].l1^=a[cnt].l2^=a[cnt].l1^=a[cnt].l2;
		}
	}else{//如果目前的时间太靠前就不能以它之前为依据而要以它之后（前面那里写 >0.0001 应该也可以）
		if(js(a[cnt].p1,a[cnt].t+0.0001)-js(a[cnt].p2,a[cnt].t+0.0001)-d>-eps){
			a[cnt].p1^=a[cnt].p2^=a[cnt].p1^=a[cnt].p2;
			a[cnt].l1^=a[cnt].l2^=a[cnt].l1^=a[cnt].l2;
		}
	}
}void build(Ty i,Ty j,Ty id){//区间加全局 max 的线段树，没啥说的
	if(i==j){tre[id]=t[i];return;}Ty mid=i+j>>1;
	build(i,mid,id<<1);build(mid+1,j,id<<1|1);
	tre[id]=maxn(tre[id<<1],tre[id<<1|1]);
}void chang(Ty i,Ty j,Ty id){
	if(sgl<=i&&j<=sgr){tre[id]+=sgk;tag[id]+=sgk;return;}
	Ty mid=i+j>>1,sn=id<<1;
	tre[sn]+=tag[id];tre[sn|1]+=tag[id];
	tag[sn]+=tag[id];tag[sn|1]+=tag[id];tag[id]=0;
	if(sgl<=mid)chang(i,mid,sn);
	if(sgr>mid)chang(mid+1,j,sn|1);
	tre[id]=maxn(tre[sn],tre[sn|1]);
}int main(){
	fOR(i,0,MAXN<<1)id[i]=fa[i]=i;
	n=qr();k=qr();
	FOR(i,1,n){
		x[i]=qr();y[i]=qr();r[i]=qr();
		ds[i]=sqrt(sq(x[i])+sq(y[i]));//预处理一些信息
		ag[i]=_atan(x[i],y[i]);
		if(ag[i]<eps)ag[i]+=2*PI;
	}FOR(i,1,n)FOR(j,1,n){//找到所有时间
		if(i==j)continue;
		slv(i,j,r[i]+r[j]);
		if(c1){
			a[++cnt].t=a1;
			a[cnt].p1=i;a[cnt].p2=j;
			a[cnt].l1=1;a[cnt].l2=0;
			crct(r[i]+r[j]);
		}if(c2){
			a[++cnt].t=a2;
			a[cnt].p1=i;a[cnt].p2=j;
			a[cnt].l1=1;a[cnt].l2=0;
			crct(r[i]+r[j]);
		}slv(i,j,_abs(r[i]-r[j]));
		if(c1){
			a[++cnt].t=a1;a[cnt].p1=i;a[cnt].p2=j;
			a[cnt].l1=a[cnt].l2=r[i]>r[j]||(r[i]==r[j]&&i>j);
			crct(_abs(r[i]-r[j]));
		}if(c2){
			a[++cnt].t=a2;a[cnt].p1=i;a[cnt].p2=j;
			a[cnt].l1=a[cnt].l2=r[i]>r[j]||(r[i]==r[j]&&i>j);
			crct(_abs(r[i]-r[j]));
		}
	}sort(a+1,a+cnt+1,cmp);
	for(p=1;p<=cnt&&a[p].t<eps;p++){//先处理完在 l 与 x 轴重合时就发生的事件并更新对应答案
		++in[x1=a[p].p1*2-a[p].l1];
		x2=a[p].p2*2-a[p].l2;
		if(!vis[x1])spt.push_back(x1);
		if(!vis[x2])spt.push_back(x2);
		vis[x1]=vis[x2]=true;
	}FOR(i,1,n){b[i*2-1]=x[i]-r[i];b[i<<1]=x[i]+r[i];}
	sort(id+1,id+(n<<1)+1,cmp2);FOR(i,1,n<<1)rk[id[i]]=i;
	fOR(i,0,spt.size())in[fa[spt[i]]=spt[i]]=vis[spt[i]]=0;
	spt.clear();FOR(i,1,n){++t[rk[i*2-1]];--t[rk[i<<1]];}
	n<<=1;FOR(i,2,n)t[i]+=t[i-1];build(1,n,1);ans=tre[1];
	FOR(i,p,cnt){
		x1=a[i].p1*2-a[i].l1;x2=a[i].p2*2-a[i].l2;
		if(!vis[x1]){//处理事件，先撤销涉及到的圆对应的贡献（由 vis 和 spt 记录）
			spt.push_back(x1);if(x1&1){
				if(!vis[x1+1]){
					sgl=rk[x1];sgr=rk[x1+1]-1;
					sgk=-1;chang(1,n,1);
				}
			}else if(!vis[x1-1]){
				sgl=rk[x1-1];sgr=rk[x1]-1;
				sgk=-1;chang(1,n,1);
			}
		}if(!vis[x2]){
			spt.push_back(x2);if(x2&1){
				if(!vis[x2+1]){
					sgl=rk[x2];sgr=rk[x2+1]-1;
					sgk=-1;chang(1,n,1);
				}
			}else if(!vis[x2-1]){
				sgl=rk[x2-1];sgr=rk[x2]-1;
				sgk=-1;chang(1,n,1);
			}
		}vis[x1]=vis[x2]=true;fa[getfa(x1)]=getfa(x2);++in[x1];
		if(i==cnt||!eq(a[i].t,a[i+1].t)){//不一样就开始处理
			fOR(j,0,spt.size()){getfa(spt[j]);mx[fa[spt[j]]]=maxn(mx[fa[spt[j]]],rk[spt[j]]);}
			fOR(j,0,spt.size()){
				rk[spt[j]]=mx[fa[spt[j]]]-in[spt[j]];
				in[fa[spt[j]]=spt[j]]=vis[spt[j]]=0;//更新排名和贡献并清空其它涉及到的数组
				if(spt[j]&1){
					if(!vis[spt[j]+1]){
						sgl=rk[spt[j]];sgr=rk[spt[j]+1]-1;
						sgk=1;chang(1,n,1);
					}
				}else if(!vis[spt[j]-1]){
					sgl=rk[spt[j]-1];sgr=rk[spt[j]]-1;
					sgk=1;chang(1,n,1);
				}
			}fOR(j,0,spt.size())mx[fa[spt[j]]]=0;
			spt.clear();ans=maxn(ans,tre[1]);
		}
	}printf("%lld",(n>>1)+k*ans+(1ll*k*(k-1)>>1));
	return 0;
}
```

---

