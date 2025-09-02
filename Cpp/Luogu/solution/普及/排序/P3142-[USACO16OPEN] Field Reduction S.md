# [USACO16OPEN] Field Reduction S

## 题目描述

Farmer John 的 $N$ 头奶牛（$5 \leq N \leq 50,000$）都位于他二维牧场中的不同位置。FJ 希望用一个边平行于 $x$ 轴和 $y$ 轴的矩形围栏围住所有的奶牛，并且他希望这个围栏尽可能小，以便能够包含每头奶牛（允许奶牛位于边界上）。

不幸的是，由于上个季度牛奶产量低，FJ 的预算非常紧张。因此，他希望如果可能的话，建造一个更小的围栏，并且他愿意从他的牛群中出售最多三头奶牛来实现这一目标。

请帮助 FJ 计算在从他的牛群中移除最多三头奶牛后，他可以用围栏围住的最小可能面积（然后为剩余的奶牛建造最紧密的围栏）。

对于这个问题，请将奶牛视为点，将围栏视为四条线段的集合（即不要将奶牛视为“单位正方形”）。请注意，答案可能为零，例如如果所有剩余的奶牛最终站在一条共同的垂直线或水平线上。

## 样例 #1

### 输入

```
6
1 1
7 8
10 9
8 12
4 100
50 7```

### 输出

```
12```

# 题解

## 作者：Unordered_OIer (赞：10)

# P3142 题解
            ——————————一篇为新手村准备的题解  
大致思路是一样的，就是暴力枚举删除每一头牛的情况。但是我看了一下，有dalao的题解中的代码本新手认为不是非常易懂，于是诞生了这篇为新手提供的代码。  
思路：直接正面进攻这一题，似乎不是那么好做。那么我们就瞄准一个**重要**的条件：**卖掉三只牛**。  

“三”只牛，这个数据实在是太小了，我们只需要暴力枚举最优的情况，就行了。但是怎么确定围栏的面积呢？  

我们知道，围栏是一个矩形，矩形的面积计算是长×宽，那么问题就变为**怎么确定长和宽**？  

这个问题实际上就非常好解决了，我们只需要确定$maxx-minx$与$maxy-miny$，就对应了长与宽。那么面积问题解决了，还有一个问题：如果数据较小，容易出现**一头牛删了两次**的情况。  

怎么解决呢？很简单，使用一个数组记录每头牛的“id”，然后使用这个“id”进行循环就行了。  
(本人觉得标记数组的方法有些像分块或者离散化)

这里切记切记，必须要按$x,y$分别写$cmp$函数，混了之后就不对了。


这里需要**注意**，设无穷大的值的时候一定要设精确，因为输出的最大值我们可以估算一下，题目数据给的是$40000$，计算面积少不了平方，就是$40000^2=1.6*10^9=1600000000$  
所以我们在设定的时候最好要大于这个值，设$2e10$是最方便的，本人在这里被坑了好多次。

最后[安利一下我的blog](https://www.luogu.com.cn/blog/291706/)

```cpp
#include<bits/stdc++.h>
#define N 50005
#define INF 2e10
using namespace std;
typedef long long ll;
struct Cow{ll x,y;}a[N];
ll n,b[N],c[N],d[N],ans=INF;
bool cmp1(ll x,ll y){
	return a[x].x<a[y].x || (a[x].x==a[y].x && a[x].y<a[y].y);
}
bool cmp2(ll x,ll y){
	return a[x].y<a[y].y || (a[x].y==a[y].y && a[x].x<a[y].x);
}
void work(ll x,ll y,ll z){
	memset(d,0,sizeof(d));
	for (ll i=1; i<=x; i++) d[b[i]]=1;
	for (ll i=1; i<=y; i++) d[b[n-i+1]]=1;
	//
    ll m=0;
	for (ll i=1; i<=n; i++)
		if (!d[i]) c[++m]=i;
       //标记数组
	sort(c+1,c+m+1,cmp2);//排序
	for (ll i=1; i<=z; i++) d[c[i]]=1;
	for (ll i=1; i+x+y+z<=3; i++) d[c[m-i+1]]=1;//用标记数组标记d
	ll mxx=0,mxy=0,mix=INF,miy=INF;
	for (ll i=1; i<=n; i++)
		if (!d[i]){
			mxx=max(maxx,a[i].x);
			mix=min(minx,a[i].x);
			mxy=max(maxy,a[i].y);
			miy=min(miny,a[i].y);
		}//标记端点
	if (mxx<=mix || mxy<=miy) ans=0;
	else ans=min(ans,(mxx-mix)*(mxy-miy));
    //计算面积
}
int main(){
	scanf("%lld",&n);
	for (ll i=1; i<=n; i++) scanf("%lld%lld",&a[i].x,&a[i].y);
	for (ll i=1; i<=n; i++) b[i]=i;//注意要标记好b
	sort(b+1,b+n+1,cmp1);//b要按cmp1排序
	for (ll i=0; i<=3; i++)
		for (ll j=0; i+j<=3; j++)
			for (ll k=0; i+j+k<=3; k++)
				work(i,j,k);//暴力
	printf("%lld\n",ans);//输出
	return 0;
}
```
本人的一篇良心题解，望管理员给过吧。  
$update:2020-02-18$

---

## 作者：ikunTLE (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P3142)

### 思路

没有任何技巧可言，只卖三只牛，单纯**暴力**。想要求出最终围栏围起来的面积，只需要计算 $(maxx-minx)(maxy-miny)$ 的值即可。

首先，我们先用 $X_i$ 排序，求得最大的 $3$ 个点和最小的 $3$ 个点。同样的方法给 $Y_i$ 排序，求得最大的 $3$ 个点和最小的 $3$ 个点。我们要暴力的答案中必定包含这 $12$ 个点（当然有重复的点要**去重**）。

接下来就是暴力的核心，用 dfs 每一次选择 $3$ 个点，然后最后计算它的面积，取最小值即可。（如果这个不会，建议先做[这道题](https://www.luogu.com.cn/problem/P1157)）

---

## 作者：Zenith_Yeh (赞：4)

看到只删3头牛，想到暴力。

我们枚举在四周的3头牛（因为里面的牛不影响答案）。又由于有可能一头牛既是 $x$ 的最值也是 $y$ 的最值，所以分两步标记。

1. 首先删 $x$ 的最值，将数组以 $x$ 的大小排序。
2. 再将没删的放入一个新的数组。
3. 然后删 $y$ 的最值，将数组以 $y$ 的大小排序。
4. 最后看没被删的，计算最值即可。

**上菜：**
```cpp
#include<bits/stdc++.h>
#define inf 20000000000000000//设大点
#define int long long//不开long long见祖宗
#define read() Read<int>()
namespace pb_ds{//优美的快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
struct bb
{	int x,y,id;
	bb operator =(const bb &a)//重载运算符
	{	x=a.x;
		y=a.y;
		id=a.id;
		return *this;
	}
}op[50005],now[50005];//建两个，一个初始，一个临时
int n,ans=inf;
bool bj[50005];
inline bool cmp_x(bb a,bb b)//以x排序
{	return a.x==b.x?a.y<b.y:a.x<b.x; 
}
inline bool cmp_y(bb a,bb b)//以y排序
{	return a.y==b.y?a.x<b.x:a.y<b.y; 
}
inline int pd(int a,int b,int c,int d)
{	memset(bj,0,sizeof(bj));//注意清空
	for(register int i=1;i<=a;++i)bj[op[i].id]=1;//打标记
	for(register int i=1;i<=b;++i)bj[op[n-i+1].id]=1;
	int cnt=0;
	for(register int i=1;i<=n;++i)//存进新的数组
		if(!bj[i])now[++cnt]=op[i];
	sort(now+1,now+cnt+1,cmp_y);//以y排序
	for(register int i=1;i<=c;++i)bj[now[i].id]=1;
	for(register int i=1;i<=d;++i)bj[now[cnt-i+1].id]=1;
	int max_x=0,max_y=0,min_x=inf,min_y=inf; 
	for(register int i=1;i<=n;++i)
		if(!bj[op[i].id])//没被删的
		{	max_x=max(max_x,op[i].x);
			max_y=max(max_y,op[i].y);
			min_x=min(min_x,op[i].x);
			min_y=min(min_y,op[i].y);
		}
	if(max_x<min_x||max_y<min_y)return 0;//避免负负得正
	ans=min(ans,(max_x-min_x)*(max_y-min_y));//更新答案
}
signed main()
{	n=read();
	for(register int i=1;i<=n;++i)op[i].x=read(),op[i].y=read(),op[i].id=i;
	sort(op+1,op+n+1,cmp_x);//以x排序
    for(register int i=0;i<=3;++i)
		for(register int j=0;i+j<=3;++j)
			for(register int k=0;i+j+k<=3;++k)
					pd(i,j,k,3-i-j-k); 
	cout<<ans;
	return 0;
}
```


---

## 作者：Violet___Evergarden (赞：3)

最优解第三。
# 思路
可以用变量  $maxx_1$，$maxx_2$，$maxx_3$，$minx_1 \cdots miny_3$ 等分别先把横坐标、纵坐标最大和最小的 $12$ 头牛的编号记录下来，在通过手算枚举出 $3$ 头牛的各种排列组合的方式，最后直接模拟算出答案。

**手算需要注意的：**
如果我们没有选择 $maxx_1$，那么我们一定不会选择 $maxx_2$ 和 $maxx_3$，因为我们没有将最大的横坐标删掉的话，其他的横坐标一定会在这个包围起来的矩形里面，删掉之后不会对答案产生贡献。


------------
# AC CODE
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
#define RE register
#define IN inline
using namespace std;
const int kMaxN=5e4+1;
int n,ans=LLONG_MAX;
int maxx[4],minx[4],maxy[4],miny[4];
struct COW
{
  int x,y;//每头牛的坐标
  int num;//每头牛的编号
}cow[kMaxN];
bool cmp1(COW i,COW j)//按横坐标从大到小排序
{
  if(i.x!=j.x)return i.x<j.x;
  return i.y<j.y;//如果横坐标相同，那么删除纵坐标最外面的最划算
}
bool cmp2(COW i,COW j)//按纵坐标从大到小排序
{
  if(i.y!=j.y)return i.y<j.y;
  return i.x<j.x;
}
IN void solve(int a,int b,int c)//模拟计算删除3个点后矩形的面积
{
  int maxx=-1,minx=LLONG_MAX,maxy=-1,miny=LLONG_MAX;
  for(RE int i=1;i<=n;i++)
  {
    if(cow[i].num==a||cow[i].num==b||cow[i].num==c)continue;
    maxx=max(maxx,cow[i].x);
    minx=min(minx,cow[i].x);
    maxy=max(maxy,cow[i].y);
    miny=min(miny,cow[i].y);
  }
  ans=min(ans,(maxx-minx)*(maxy-miny));
}
signed main()
{
//freopen("reduce.in","r",stdin);
//freopen("reduce.out","w",stdout);
cin>>n;
for(RE int i=1;i<=n;++i)
{
  cin>>cow[i].x>>cow[i].y;
  cow[i].num=i;
}
sort(cow+1,cow+n+1,cmp1);//记录思路上所说的12个值
maxx[1]=cow[n].num;
maxx[2]=cow[n-1].num;
maxx[3]=cow[n-2].num;
minx[1]=cow[1].num;
minx[2]=cow[2].num;
minx[3]=cow[3].num;
sort(cow+1,cow+n+1,cmp2);
maxy[1]=cow[n].num;
maxy[2]=cow[n-1].num;
maxy[3]=cow[n-2].num;
miny[1]=cow[1].num;
miny[2]=cow[2].num;
miny[3]=cow[3].num;
solve(maxx[1],maxx[2],maxx[3]);//枚举各种可能
solve(maxx[1],maxx[2],minx[1]);
solve(maxx[1],minx[1],minx[2]);
solve(minx[1],minx[2],minx[3]);
solve(maxx[1],maxy[1],maxy[2]);
solve(maxx[1],maxy[1],miny[1]);
solve(maxx[1],miny[1],miny[2]);
solve(maxx[1],maxx[2],maxy[1]);
solve(maxx[1],maxx[2],miny[1]);
solve(maxx[1],minx[1],maxy[1]);
solve(maxx[1],minx[1],miny[1]);
solve(minx[1],maxy[1],maxy[2]);
solve(minx[1],maxy[1],miny[1]);
solve(minx[1],miny[1],miny[2]);
solve(minx[1],minx[2],maxy[1]);
solve(minx[1],minx[2],miny[1]);
solve(maxy[1],maxy[2],maxy[3]);
solve(maxy[1],maxy[2],miny[1]);
solve(maxy[1],miny[1],miny[2]);
solve(miny[1],miny[2],miny[3]);
cout<<ans;
return 0;
//fclose(stdin);
//fclose(stdout);
}
```

---

## 作者：mysterys (赞：2)

# 思路
1. 题面非常简洁，注意到 $5 \leq N \leq 50,000$，所以大概率时间复杂度是 $O(N)$。
1. 最后一句话说从奶牛中选出 $3$ 头卖掉，其实就是在最外侧的 $3$ ，所以考虑枚举横、纵坐标最大或最小的 $3$ 头牛。
# 时间复杂度
由于是枚举四个方向上的 $3$ 头奶牛，所以极限情况也只有 $12$ 头奶牛。

复杂度：$O(N)$。
# 注意事项
- **如果一个奶牛是横坐标上的极值，也是纵坐标上的极值，只能算一次。**
- 答案会超出 int 范围，需要开 long long。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
const int N=50005;
int n;
ll ans=1e18;
struct node{
	ll x,y;
	int down;
}b[N];
int g[N],cnt,m;
bool cmp1(node r1,node r2) {return r1.x<r2.x;}
bool cmp2(node r1,node r2) {return r1.y<r2.y;}
inline void check(int r1,int r2,int r3){
	ll minx=LLONG_MAX,maxx=-1;
	ll miny=LLONG_MAX,maxy=-1;
	for(int i=1;i<=n;i++){
		if(b[i].down==r1||b[i].down==r2||b[i].down==r3) continue;
		minx=min(minx,b[i].x);
		maxx=max(maxx,b[i].x);
		miny=min(miny,b[i].y);
		maxy=max(maxy,b[i].y);
	}
	ans=min(ans,(maxx-minx)*(maxy-miny));//和新的答案取最小值 
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i].x>>b[i].y;
		b[i].down=i;
	}
	stable_sort(b+1,b+n+1,cmp1);
	for(int i=1;i<=3;i++){g[++cnt]=b[i].down;}
	for(int i=n;i>=n-2;i--){g[++cnt]=b[i].down;}
	stable_sort(b+1,b+n+1,cmp2);
	for(int i=1;i<=3;i++){g[++cnt]=b[i].down;}
	for(int i=n;i>=n-2;i--){g[++cnt]=b[i].down;}
	stable_sort(g+1,g+cnt+1);
	m=unique(g+1,g+cnt+1)-g;//去重，防止重复贡献。 
	for(int i=1;i<=m;i++){//枚举奶牛 
		for(int j=1;j<=m;j++){
			for(int k=1;k<=m;k++){
				if(k==j||i==j||i==k) continue;
				check(g[i],g[j],g[k]);
			}
		}
	}
	cout<<ans;
	return 0;
}  
```

---

## 作者：Victorique (赞：2)

楼下的题解看上去有些，不易理解。其实说法是很正确的，这个题，看上去很复杂，判断坐标什么的，确实不好办，所以我们就不往那个地方去想，这个题直接暴力枚举那三头牛应该被去掉就可以了，又因为在数学上易证，肯定删除的是边上的牛就是最优情况，所以排好序直接枚举就行了，复杂度大概是O（3^4\*4）不过的话没天理了。

还有一个地方需要注意，删去横纵坐标最大或最小的牛时，有可能删除了重复的一头牛（数据小时极其容易出现这种情况）所以用结构体对其进行排序，然后用一个标记数组进行标记，如果这头牛已经搜过就直接下一头，不增加当前已经去掉的牛的数量

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define re register
#define maxn 999999999
#define ll long long
using namespace std;
struct cow
{
    long long x,y;
    int id;
};
cow a[50005],b[50005];
long long ans=maxn,s,n,m,d,x[50005],y[50005],sx[50005],sy[50005],use[50005];
long long l1,l2,r1,r2;
inline bool cmp1(cow x,cow y)
{
    return x.x<y.x;
}
inline bool cmp2(cow x,cow y)
{
    return x.y<y.y;
}
inline void dfs(int lx,int ly,int rx,int ry,int t)
{
    if(t==3)
    {
        while(use[a[lx].id])
        lx++;
        while(use[a[rx].id])
        rx--;
        while(use[b[ly].id])
        ly++;
        while(use[b[ry].id])
        ry--;
        if((a[rx].x-a[lx].x)*(b[ry].y-b[ly].y)<ans)
        {
            l1=a[lx].x;
            l2=a[rx].x;
            r1=b[ly].y;
            r2=b[ry].y;
            ans=(a[rx].x-a[lx].x)*(b[ry].y-b[ly].y);
        }
        return;
    }
    for(re int i=1;i<=4;i++)
    {
        if(i==1)
        if(!use[a[lx].id])
        {
            use[a[lx].id]=1;
            dfs(lx+1,ly,rx,ry,t+1);
            use[a[lx].id]=0;
        }else
        dfs(lx+1,ly,rx,ry,t);
        if(i==2)
        if(!use[a[rx].id])
        {
            use[a[rx].id]=1;
            dfs(lx,ly,rx-1,ry,t+1);
            use[a[rx].id]=0;
        }else
        dfs(lx,ly,rx-1,ry,t);
        if(i==3)
        {
            if(!use[b[ly].id])
            {
                use[b[ly].id]=1;
                dfs(lx,ly+1,rx,ry,t+1);
                use[b[ly].id]=0;
            }else
            dfs(lx,ly+1,rx,ry,t);
        }
        if(i==4)
        {
            if(!use[b[ry].id])
            {
                use[b[ry].id]=1;
                dfs(lx,ly,rx,ry-1,t+1);
                use[b[ry].id]=0;
            }else
            dfs(lx,ly,rx,ry-1,t);
        }
    }
}
int main()
{
///    freopen("reduce.in","r",stdin);
//    freopen("reduce.out","w",stdout);
    cin>>n;
    ans*=10000000;
    for(re int i=1;i<=n;i++)
    {
        cin>>a[i].x>>a[i].y;
        b[i].x=a[i].x;
        b[i].y=a[i].y;
        a[i].id=b[i].id=i;
    }
    sort(a+1,a+n+1,cmp1);
    sort(b+1,b+n+1,cmp2);
    dfs(1,1,n,n,0);
    cout<<ans;    
}
/*
6
1 1
7 8
10 9
8 12
4 100
50 7
*/
```

---

## 作者：Orion_Rigel (赞：2)

发一个没有太大意义的题解好了。

其实就是考虑删去的点只能在周围一圈，所以考虑最靠近边上的几个点就可以了。

反正中间删了也不会对结果造成影响。

但是数据太弱，这样就过了。

也许是因为x或y值都是随机的，相同的情况太少了。

···
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
struct node{
    int x;
    int y;
    int pos;
}list[50001],real[20];
int can[50001];
int n,cnt=0;
long long ans=1000000000000;
inline bool cmp1(node a,node b)
{return a.x<b.x;}
inline bool cmp2(node a,node b)
{return a.y<b.y;}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        scanf("%d%d",&list[i].x,&list[i].y);
        list[i].pos=i;
    }
    sort(list+1,list+n+1,cmp1);
    for (int i=1;i<=4;++i) if (!can[list[i].pos]) real[++cnt]=list[i],can[list[i].pos]=1;
    for (int i=n;i>=n-3;--i) if (!can[list[i].pos]) real[++cnt]=list[i],can[list[i].pos]=1;
    sort(list+1,list+n+1,cmp2);
    for (int i=1;i<=4;++i) if (!can[list[i].pos]) real[++cnt]=list[i],can[list[i].pos]=1;
    for (int i=n;i>=n-3;--i) if (!can[list[i].pos]) real[++cnt]=list[i],can[list[i].pos]=1;
    for (int i=0;i<(1<<(cnt));++i)
    {
        int all=0,x=i;
        while (x)
        {
            if (x&1) all++;
            x>>=1;
        }
        if (all==cnt-3)
        {
            int xmin=inf,ymin=inf,xmax=-inf,ymax=-inf;
            for (int j=1;j<=cnt;++j)
            if (i&(1<<(j-1))){
                xmin=min(xmin,real[j].x);
                xmax=max(xmax,real[j].x);
                ymin=min(ymin,real[j].y);
                ymax=max(ymax,real[j].y);
            }
            long long tmp=((ll)xmax-xmin)*((ll)ymax-ymin);
            ans=min(tmp,ans);
        }
    }
    printf("%lld\n",ans);
}
···
```

---

## 作者：D23lhc (赞：1)

### 分析
这道题的面积是一个矩形，所以这道题就比较简单了。我先将各个方向的最前面四个点存入一个数组（不能有相同的点）。因为有可能这四个点在同一行或列中，但我们只能删去三个点，所以这个方向就是不可行的。另外有可能会将三个在同一行或列中的点删去，所以我们要取第四个点来，方便计算面积。
我们只需要在取出的点中枚举 3 个，然后计算面积取 min 就好了。

## 代码
```
#include<bits/stdc++.h>
#define MAXN 50007
#define INF 40000*40000+10//INF太小
using namespace std;
int n,sum,ans=INF;
bool vis[MAXN];
struct node
{
    int x,y;
    int id;
}a[MAXN];
struct ant
{
    int x,y;
    int id;
}b[20];
bool cmp1(node p,node q)
{
    return p.x<q.x;
}
bool cmp2(node p,node q)
{
    return p.y<q.y;
}
void check(int x,int y,int z)
{
    int maxx=0,maxy=0,minx=INF,miny=INF;
    for(int i=1;i<=sum;i++)
    {
        if(i==x||i==y||i==z)
            continue;
        maxx=max(maxx,b[i].x);
        minx=min(minx,b[i].x);
        maxy=max(maxy,b[i].y);
        miny=min(miny,b[i].y);
    }
    ans=min(ans,(maxx-minx)*(maxy-miny));
    return;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp1);
    for(int i=1;i<=4;i++)
    {
        if(!vis[a[i].id])
        {
            vis[a[i].id]=1;
            b[++sum].x=a[i].x;
            b[sum].y=a[i].y;
            b[sum].id=a[i].id;
        }
    }
    for(int i=n;i>=n-3;i--)
    {
        if(!vis[a[i].id])
        {
            vis[a[i].id]=1;
            b[++sum].x=a[i].x;
            b[sum].y=a[i].y;
            b[sum].id=a[i].id;
        }
    }
    sort(a+1,a+n+1,cmp2);
    for(int i=1;i<=4;i++)
    {
        if(!vis[a[i].id])
        {
            vis[a[i].id]=1;
            b[++sum].x=a[i].x;
            b[sum].y=a[i].y;
            b[sum].id=a[i].id;
        }
    }
    for(int i=n;i>=n-3;i--)
    {
        if(!vis[a[i].id])
        {
            vis[a[i].id]=1;
            b[++sum].x=a[i].x;
            b[sum].y=a[i].y;
            b[sum].id=a[i].id;
        }
    }
    for(int i=1;i<=sum;i++)
    {
        for(int j=1;j<=sum;j++)
        {
            if(i==j)
                continue;
            for(int k=1;k<=sum;k++)
            {
                if(i==k||j==k)
                    continue;
                check(i,j,k);
            }
        }
    }
    printf("%d",ans);
}

```

---

## 作者：羚羊WANG (赞：1)

相信大家看到这里的时候，都已经理解了题目意思

他说只用删掉三只，“三”这个数字十分的小，我们可以直接
考虑暴力

首先，我们以$x$作为关键字，用搜索来删掉$x$的最值
然后，我们还可以在搜索的时候枚举删掉关于$x$最值的数量
剩下的删关于$y$的最值，最后统计答案即可

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
struct node{
	int x,y;
	int id;
}e[50010],e1[50010];
int n;
int ans=10000000000;
bool vis[50010];
int sum=0;
inline bool cmp1(node a,node b){
	if(a.x!=b.x)
		return a.x<b.x;
	return a.y<b.y;
}
inline bool cmp2(node a,node b){
	if(a.y!=b.y)
		return a.y<b.y;
	return a.x<b.x;
}
inline void check(int a,int b,int c,int d){
	memset(vis,0,sizeof(vis));
	sum=0;
	for(register int i=1;i<=a;++i)
		vis[e[i].id]=1;
	for(register int i=1;i<=b;++i)
		vis[e[n-i+1].id]=1;
	for(register int i=1;i<=n;++i)
		{
			if(!vis[i])
				{
					sum++;
					e1[sum].x=e[i].x;
					e1[sum].y=e[i].y;
					e1[sum].id=e[i].id;
				}
		}
	sort(e1+1,e1+sum+1,cmp2);
	for(register int i=1;i<=c;++i)
		vis[e1[i].id]=1;
	for(register int i=1;i<=d;++i)
		vis[e1[n-i+1].id]=1;
	int maxx,maxy;
	int minx,miny;
	maxx=maxy=0;
	minx=miny=100000000;
	for(register int i=1;i<=n;++i)
		{
			if(!vis[e[i].id])
				{
					maxx=max(maxx,e[i].x);
					maxy=max(maxy,e[i].y);
					minx=min(minx,e[i].x);
					miny=min(miny,e[i].y);
				}
		}
	if(maxx<minx || maxy<miny)
		return;
	ans=min(ans,(maxx-minx)*(maxy-miny));
	return;
}
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)	
		{
			e[i].x=read();
			e[i].y=read();
			e[i].id=i;
		}
	sort(e+1,e+n+1,cmp1);
	for(register int i=0;i<=3;++i)
		for(register int j=0;i+j<=3;++j)
			for(register int k=0;i+j+k<=3;++k)
				check(i,j,k,3-i-j-k);
	write(ans);
	return 0;
}
```


---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P3142)
# 思路
## 题目大意
有 $n$ 个点在一个平面上，要去除 $3$ 个点，要用一个最小的矩形围住其他的点（矩形的所有边都与 $x$ 或 $y$ 轴平行），请问这个最小的矩形面积是多少？
## 做法
把横坐标、纵坐标最大和最小的 $12$ 头牛的编号记录下来（注意去重），然后三重循环枚举得出最小值。
## 注意
### 去重函数
其实去重也是有一个函数的，它叫 unique 函数。  
格式为：`unique(容器名.begin(),容器名.end())`。

最后这个结果得到的是去重后数组剩下的个数（当然也保留了去重后的数组）。
### 类型
答案会超出 int 范围，需要开 long long。
# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define LMX LONG_LONG_MAX
#define LMN LONG_LONG_MIN
const int N=50000+5;
const int M=12+5;
struct node
{
	int x,y,id;
} a[N];
int n;
int m[M];
int idx=0;
int minans=LMX;
bool cmp1(node a,node b)
{
	return a.x<b.x;
}
bool cmp2(node a,node b)
{
	return a.y<b.y;
}
void to_m()
{
	sort(a+1,a+n+1,cmp1);
	m[++idx]=a[1].id;
	m[++idx]=a[2].id;
	m[++idx]=a[3].id;
	m[++idx]=a[n].id;
	m[++idx]=a[n-1].id;
	m[++idx]=a[n-2].id;
	sort(a+1,a+n+1,cmp2);
	m[++idx]=a[1].id;
	m[++idx]=a[2].id;
	m[++idx]=a[3].id;
	m[++idx]=a[n].id;
	m[++idx]=a[n-1].id;
	m[++idx]=a[n-2].id;
	sort(m+1,m+idx+1);
}
int getans(int p1,int p2,int p3)
{
	int maxx=LMN;
	int minx=LMX;
	int maxy=LMN;
	int miny=LMX;
	for(int i=1;i<=n;i++)
	{
		if(a[i].id==p1 || a[i].id==p2 || a[i].id==p3) continue;
		maxx=max(maxx,a[i].x);
		minx=min(minx,a[i].x);
		maxy=max(maxy,a[i].y);
		miny=min(miny,a[i].y);
	}
	int ans=(maxx-minx)*(maxy-miny);
	return ans;
}
void dfs()
{
	for(int i=1;i<=idx;i++)
	{
		for(int j=i+1;j<=idx;j++)
		{
			for(int k=j+1;k<=idx;k++)
			{
				int tmp=getans(m[i],m[j],m[k]);
				minans=min(minans,tmp);
			}
		}
	}
}
signed main()
{
	cin >>n;
	for(int i=1;i<=n;i++)
	{
		cin >>a[i].x>>a[i].y;
		a[i].id=i;
	}
	to_m();
	int c=unique(m+1,m+idx+1)-m;
	idx=c;
	dfs();
	cout <<minans;
	return 0;
}


```

---

## 作者：zmnjkl (赞：0)

本人水的第四篇题解哦~


------------
### 题意：

有 $N$ 头牛在平面内，删除三头牛后保证最小的面积。

### 分析：

- 这三头删掉的牛一定是在最外圈的，所以我们只需要去考虑最大最小的 $x$ 和 $y$ 的牛就可以了，枚举所有可能。

### 思路：

- 开两个数组，一个按照 $x$ 排序，一个按照 $y$ 排序。

- 排完序后用 DFS 去枚举这 $3$ 个点，从 $x$ 最小，最大，$y$ 最小，最大依次枚举。

- **这里要排除 $x$ 和 $y$ 重复的部分！！！** 如果 $x$ 和 $y$ 删除的值是重复的，则需要更改其中一个的值。~~（这个部分我改了一整天）~~

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[114514],xmin,xmax,ymin,ymax,ans=2147483647;
struct Node{
	int x,y;
}xc[51234],yc[51234];//xc按照x坐标排序，yc按照y坐标
vector<int>cx;
bool x(Node a,Node b){
	return a.x<b.x;
}
bool y(Node a,Node b){
	return a.y<b.y;
}
bool checkx(int m){//查看dfs跑的过程中x的值和y是否有重复
	for(int i=0;i<cx.size();i++){
		if(yc[m].x==xc[cx[i]].x&&yc[m].y==xc[cx[i]].y){
			return 0;
		}
	}
	return 1;
}
void dfs(int idx,int len){//这里加个len可以保证不会重复计算
	if(idx==3){//如果已经计算了三次，则直接计算答案返回
		int a=0,b=0;
		while(!checkx(ymin)){//因为这里还没有查看过当前y是否和x重复，所以要多判定一次
			ymin++;
			a++;
		}while(!checkx(ymax)){
			ymax--;
			b++;
		}
		ans=min(ans,abs(xc[xmax].x-xc[xmin].x)*abs(yc[ymax].y-yc[ymin].y)); //算出答案
		ymin-=a;//回溯
		ymax+=b;
		return;
	}
	for(int i=len;i<4;i++){
		int cnt=0;
		if(i==0){//对于每个x元素的操作只需要记录，不需要查看是否和y有重复
			cx.push_back(xmin); 
			xmin++;
			dfs(idx+1,i);
			xmin-=cnt+1;
			cx.pop_back();
		}else if(i==1){
			cx.push_back(xmax);
			xmax--;
			dfs(idx+1,i);
			xmax+=cnt+1;
			cx.pop_back();
		}else if(i==2){//访问y元素的时候需要查看与x是否重复
			while(!checkx(ymin)){
				ymin++;
				cnt++;
			}
			ymin++;
			dfs(idx+1,i);
			ymin-=cnt+1;
		}else{
			while(!checkx(ymax)){
				ymax--;
				cnt++;
			}
			ymax--;
			dfs(idx+1,i);
			ymax+=cnt+1;
		}
	}
}
int main(){
	cin >> n;
	xmax=n-1,ymax=n-1;
	for(int i=0;i<n;i++){
		cin >> xc[i].x >> xc[i].y;
		yc[i]=xc[i];
	}
	sort(xc,xc+n,x);
	sort(yc,yc+n,y);
	dfs(0,0);
	cout << ans;
}

```


---

