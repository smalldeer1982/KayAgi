# [USACO16FEB] Load Balancing S

## 题目背景

*本题与 [白金组同名题目](/problem/P6172) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 1000$）散布在整个农场上。整个农场是一个无限大的二维平面，第 $i$ 头奶牛的坐标是 $(x_i,y_i)$（保证 $x_i,y_i$ 均为正奇数，且 $x_i,y_i \leq 10^6$），且没有任意两头奶牛在同一位置上。

FJ 希望修建一条竖直方向的栅栏，它的方程是 $x=a$，他还希望修建一条水平方向的栅栏，它的方程是 $y=b$。为了防止栅栏经过奶牛，$a,b$ 均要求是偶数。容易发现，这两个栅栏会在 $(a,b)$ 处相交，将整个农场分割为四个区域。

FJ 希望这四个区域内的奶牛数量较为均衡，尽量避免一个区域奶牛多而另一个区域奶牛少的情况。令 $M$ 为四个区域里奶牛最多区域的奶牛数量，请帮 FJ 求出 $M$ 的最小值。

## 样例 #1

### 输入

```
7
7 3
5 5
7 13
3 1
11 7
5 3
9 1```

### 输出

```
2```

# 题解

## 作者：曹老师 (赞：13)

~~感谢@mimi提供二维前缀和做法~~

**知识点：二维前缀和**

先离散化处理！

再预处理前缀和

输出四个象限中的最大值

```
max(max(sum[i][j],sum[i][n]-sum[i][j]),max(sum[n][j]-sum[i][j],sum[n][n]-sum[n][j]-sum[i][n]+sum[i][j]))
```

用一个~~超~~长的max来做

里面四个对比的值分别为四个象限内的数

~~自己理解一下，易懂~~

然后输出最小的最大值~~(如此绕嘴想到二分)~~就好了

**时间复杂度：O(n^2)**
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=1005;
struct node{
	LL int s,num;
};
node zx[L],zy[L];
bool cmp(const node &b,const node &c)
{
	return b.s<c.s;
}
LL int n,x[L],y[L],ans=INF,sum[L][L];
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&zx[i].s,&zy[i].s);
		zx[i].num=i;
		zy[i].num=i;
	}
	sort(zx+1,zx+n+1,cmp);
	sort(zy+1,zy+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		x[zx[i].num]=i;
		y[zy[i].num]=i;
	}//离散化 
	for(int i=1;i<=n;i++)
		sum[x[i]][y[i]]++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];//预处理部分 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans=min(ans,max(max(sum[i][j],sum[i][n]-sum[i][j]),max(sum[n][j]-sum[i][j],sum[n][n]-sum[n][j]-sum[i][n]+sum[i][j])));//四个象限 
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：kczno1 (赞：9)

虽然n<=1000,但是有nlogn的做法。

就是从左到右枚举x的线，之后二分y的线。

也就是

如果l..mid的左右点数max <= mid+1..r的左右点数max

那么l=mid+1。

只要维护好以y为下标，点数为权值的线段树，在线段树上二分，时间就是一个log。

(目前唯一的0ms..)

```cpp
#include<bits/stdc++.h>
using namespace std;

void chmin(int &x,int y)
{
    if(x>y)x=y;
}

const int N=1005;
int n,i,u;
int px[N],py[N];
int id[N];

bool py_xiao(int x,int y) 
{
   return py[x]<py[y];
}
bool px_xiao(int x,int y) 
{
   return px[x]<px[y];
}
int lisan_py()
{
    for(i=1;i<=n;++i)id[i]=i;
    sort(id+1,id+n+1,py_xiao);
    int now=0,top=0;
    for(i=1;i<=n;++i)
    {
      int x=id[i];
      if(py[x]!=now){now=py[x];++top;}
      py[x]=top;
    }
    return top;
}

#define cl (i<<1)
#define cr (cl+1)
int al[N*3],ar[N*3],d;
void init(int *a)
{
    for(i=1;i<=n;++i)++a[d+py[i]];
    for(i=u+d>>1;i;--i) a[i]=a[cl]+a[cr];
}
void add(int *a,int i,int w)
{
    for(i+=d;i;i>>=1) a[i]+=w;
}
int erfen()
{
    i=1;
    int all=0,alr=0,arl=0,arr=0;
    while(i<=d)
    {
        int mxl=max(all+al[cl],arl+ar[cl]),mxr=max(alr+al[cr],arr+ar[cr]);
        //假设选择[l,mid],[mid+1,r]来划分 左右的max 
        if(mxl<=mxr) { all+=al[cl];arl+=ar[cl];i=cr; }
        else { alr+=al[cr];arr+=ar[cr];i=cl; }
    }
    int mxl=max(max(all+al[i],arl+ar[i]),max(all,arr)),
        mxr=max(max(alr+al[i],arr+al[i]),max(all,arl));
    //i分在左/右 
    return min(mxl,mxr); 
}

int main()
{
    freopen("1.in","r",stdin);
    int i;
    scanf("%d",&n);
    for(i=1;i<=n;++i)scanf("%d%d",px+i,py+i);
    
    u=lisan_py();
    for(d=1;d<u;d<<=1);d-=1;
    init(ar);
    
    sort(id+1,id+n+1,px_xiao);
    int ans=n;
    for(i=1;i<=n;++i)
    {
        int x=id[i];
        add(ar,py[x],-1);
        add(al,py[x],1);
        chmin(ans,erfen());
    }
    printf("%d\n",ans);
}
```

---

## 作者：xixike (赞：8)

~~虽然标签里有线段树，实际上只要做个二维前缀和，然后枚举最小值就可以了~~

不过，由于本题每个点的坐标较大，需要离散化。

什么叫**离散化**：

通俗的来说，就是只记录几个数的大小关系，而不记录它们的数值是多少。例如，我们要将100，1000，10000这三个数离散化，存到数组里就只用存1，2，3就行了。

当然离散化的方式有很多，不限于上述的这一种。

**附代码**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100

using namespace std;

struct node{
	int x,y,id;
}pos[N];
int n;
int sum[N][N],x[N],y[N];

bool cmp1(node a,node b){
	return a.x<b.x;//以x坐标排序，离散化
}

bool cmp2(node a,node b){
	return a.y<b.y;//以y坐标排序，离散化
}
//计算一个竖线和一个横线分割出的4个部分中，奶牛数量最多的一块数量是多少，看不懂的话，可以自己手推一下（挺简单的qwq）
int calc(int i,int j){
	return max(max(sum[i][j],sum[n][n]-sum[i][n]-sum[n][j]+sum[i][j]),max(sum[i][n]-sum[i][j],sum[n][j]-sum[i][j]));
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&pos[i].x,&pos[i].y);
		pos[i].id=i;
	}
//-------------------------------------离散化
	sort(pos+1,pos+n+1,cmp1);
	for(int i=1;i<=n;i++)
		x[pos[i].id]=i;
	sort(pos+1,pos+n+1,cmp2);
	for(int i=1;i<=n;i++)
		y[pos[i].id]=i;
//--------------------------------------
	for(int i=1;i<=n;i++)//有奶牛的位置加1
		sum[x[i]][y[i]]++;
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n;j++)
//			cout<<sum[i][j]<<" ";
//		cout<<endl;
//	}
//	cout<<endl;
	for(int i=1;i<=n;i++)//二维前缀和
		for(int j=1;j<=n;j++)
			sum[i][j]=sum[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	int ans=1e9;
	for(int i=1;i<=n;i++)//枚举每一条竖线和横线，取最小值
		for(int j=1;j<=n;j++)
			ans=min(ans,calc(i,j));
	printf("%d\n",ans); 
	return 0;
}
```

---

## 作者：localhost (赞：3)

虽然题目标签有线段树，但是一点关系都没有，直接用二维前缀和就可以了。
既然没人打二维前缀和，那我就来写一篇吧。
由于坐标太大，得先离散化。
坐标离散化后，就开始前缀和
然后枚举坐标，更新答案。
上代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define fur(i,x,y) for(i=x;i<=y;i++)
#define fdr(i,x,y) for(i=x;i>=y;i--)
#define Fur(i,x,y) for(ll i=x;i<=y;i++)
#define Fdr(i,x,y) for(ll i=x;i>=y;i--)
#define in2(x,y) in(x);in(y)
#define in3(x,y,z) in2(x,y);in(z)
#define in4(a,b,c,d) in2(a,b);in2(c,d)
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
/*---------------------------------------*/
namespace fib{char b[300000]= {},*f=b;}
#define gc ((*fib::f)?(*(fib ::f++)):(fgets(fib::b,sizeof(fib::b),stdin)?(fib::f=fib::b,*(fib::f++)):-1))
inline void in(ll &x){x=0;char c;bool f=0;while((c=gc)>'9'||c<'0')if(c=='-')f=!f;x=c-48;while((c=gc)<='9'&&c>='0')x=x*10+c-48;if(f)x=-x;}
namespace fob{char b[300000]= {},*f=b,*g=b+300000-2;}
#define pob (fwrite(fob::b,sizeof(char),fob::f-fob::b,stdout),fob::f=fob::b,0)
#define pc(x) (*(fob::f++)=(x),(fob::f==fob::g)?pob:0)
struct foce{~foce(){pob;fflush(stdout);}} _foce;
namespace ib{char b[100];}
inline void out(ll x){if(x==0){pc(48);return;}if(x<0){pc('-');x=-x;}char *s=ib::b;while(x) *(++s)=x%10,x/=10;while(s!=ib::b) pc((*(s--))+48);}
inline void outn(ll x){out(x);pc('\n');}
inline void swap(ll &x,ll &y){ll t=x;x=y;y=t;}
inline ll jdz(ll x){return x>=0?x:-x;}
/*-------------------以上为自定义，不要理-------------------------*/
#define N 1011
ll x[N],y[N],n,s[N][N],ans=2333333;
struct ls{ll s,id;}zx[N],zy[N];
inline bool cmp(ls a,ls b){return a.s<b.s;}
inline ll cl(ll i,ll j){
	return max(max(s[i][j],s[i][n]-s[i][j]),max(s[n][j]-s[i][j],s[n][n]-s[n][j]-s[i][n]+s[i][j]));
}
int main(){
    in(n);
    Fur(i,1,n){
    	in2(x[i],y[i]);
    	zx[i].id=i;zx[i].s=x[i];
    	zy[i].id=i;zy[i].s=y[i];
	}stable_sort(zx+1,zx+n+1,cmp);stable_sort(zy+1,zy+n+1,cmp);
	Fur(i,1,n)x[zx[i].id]=i,y[zy[i].id]=i;
    //离散化
	Fur(i,1,n)s[x[i]][y[i]]++;
	Fur(i,1,n)
		Fur(j,1,n)
		s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
    //二维前缀和预处理
	Fur(i,1,n)
		Fur(j,1,n)
		ans=min(ans,cl(i,j));
    //枚举
	outn(ans);
}
```
![前缀和的图片（帮助解释）](https://cdn.luogu.com.cn/upload/pic/16500.png )

---

## 作者：Only_My_Whisper (赞：3)

这道题的数据范围是1000，所以O(n^2logn)的算法是可以接受的。

先穷举X轴分割线，再把分割线两边的点分别加入两个集合之中（按Y轴排序）

然后推Y轴分割线一趟推完即可。

代码如下

#include<bits/stdc++.h>

using namespace std;

class cow{

public:

```cpp
        int x,y;
        bool operator >(const cow &b)const{
            return y>b.y;
        }
        bool operator <(const cow &b)const{
            return y<b.y;
        }
        //重载运算符。
};
int cmp(cow a,cow b){
    return a.y<b.y;
}
int main(){
    int n,i,j;
    cin>>n;
    cow a[n+1];
    for(i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
    }
    int ans=1000000;
    for(i=1;i<=n-1;i++){
        multiset<cow>ms1;
        multiset<cow>ms2;
        int n1=0,n2=0;
        for(j=1;j<=n;j++){
            if(a[j].x<a[i].x+0.5){
                ms1.insert(a[j]);
                n1++;
            }
            else{
                ms2.insert(a[j]);
                n2++;
            }
        }
        //加入集合。
        int n3,n4,n5,n6;
        sort(a+1,a+n+1,cmp);
        for(j=1;j<=n-1;j++){
            while((*ms1.begin()).y<a[j].y+0.5&&!ms1.empty()){
                ms1.erase(ms1.begin());
            }
            while((*ms2.begin()).y<a[j].y+0.5&&!ms2.empty()){
                ms2.erase(ms2.begin());
            }
            n3=n1-ms1.size();
            n4=n2-ms2.size();
            n5=ms1.size();
            n6=ms2.size();
            ans=min(ans,max(n3,max(n4,max(n5,n6))));
        }
        //推Y轴。
    }
    cout<<ans;
}
```

---

## 作者：Xdl_rp (赞：2)

solution
------------
这题运用离散化和二位前缀和

- 离散化：将坐标范围从 $10^6$ 变到 $10^3$，变化的方法是利用点数不超过 $1000$，所以不同横坐标值和不同纵坐标值的数量均不超过 $1000$，我们可以将每个点的横坐标变成其在所有横坐标值中排序后的位置，纵坐标也类似。

- 由于离散化后的坐标值在 $1000$ 以内，所以我们水平分割线和竖直分割线均只需要考虑 $1000$ 种可能，对于每种可能，我们如果要在 $O(1)$ 时间内求出四个区域的奶牛数，需要利用二维前缀和。

- 二维前缀和：用 $sum[i][j]$ 表示坐标 $(i, j)$ 左下方的奶牛数量，则 $sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i][j]$，其中 $a[i][j] = 1$ 表示坐标 $(i, j)$ 处有奶牛，否则 $a[i][j] = 0$。

上面已经讲得很清楚了，就不需要给代码了，相信大家看了之后也能写出代码。

---

## 作者：zhenjianuo2025 (赞：1)

### Solve

题目中的 $N$ 最多不大于 $1000$，直接枚举竖直方向和水平方向的栏杆的位置显然不会超时，而我们要做的，就是枚举时 $\mathcal{O}(1)$ 计算四个区域的奶牛数量。不难想到使用二维前缀和即可实现 $\mathcal{O}(1)$ 计算。

```cpp
// 前缀和
void init() {   // 初始化
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
{
int calc(int x1, int y1, int x2, int y2) {   // 左上角 (x1, y1)，右下角 (x2, y2) 的矩形 
	return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1]; 
}
```

仔细观察题目，发现 $x,y\le 10^6$，直接开一个这么大的二维前缀和数组空间会飞起，而 $N$ 很小，于是考虑离散化。


如何将一些类似 $(x_i,y_i)$ 的坐标离散化呢？

只需要将 $x$ 坐标和 $y$ 坐标分别离散化即可，发现这样可以在不改变每个元素的位置，也不改变 $x$ 坐标和 $y$ 坐标的相对大小的情况下尽可能地压缩 $x$ 和 $y$ 坐标。

例如，将坐标 $\{(4,19),(114514,520),(520,1919810)\}$ 对 $x$ 坐标和 $y$ 坐标分别离散化后得到 $\{(1,1),(3,2),(2,3)\}$。

```cpp
for (int i = 1; i <= n; i++) 
	nx[i].idx = ny[i].idx = i;
sort(nx + 1, nx + n + 1, cmp);
sort(ny + 1, ny + n + 1, cmp);
// 离散化
for (int i = 1; i <= n; i++) 
	x[nx[i].idx] = y[ny[i].idx] = i;
```

### Code

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n, x[1010], y[1010], s[1010][1010];
struct node {
	int x, idx;
} nx[1010], ny[1010];
bool cmp(node a, node b) {
	return a.x < b.x;
}
int calc(int x1, int y1, int x2, int y2) {
	return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1]; 
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		nx[i].idx = ny[i].idx = i;
		cin >> nx[i].x >> ny[i].x;
	}
	sort(nx + 1, nx + n + 1, cmp);
	sort(ny + 1, ny + n + 1, cmp);
	for (int i = 1; i <= n; i++) 
		x[nx[i].idx] = y[ny[i].idx] = i;
	for (int i = 1; i <= n; i++)
		s[x[i]][y[i]]++;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
	int ans = 1e9;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int now = max(max(max(calc(1, 1, i, j), calc(1, j + 1, i, n)), calc(i + 1, 1, n, j)), calc(i + 1, j + 1, n, n));
			ans = min(ans, now);
		}
	cout << ans << endl;
	return 0; 
}
```


---

## 作者：qwq___qaq (赞：1)

$n=1000$，显然支持 $O(n^2)$ 的做法。

因为取的位置和顺序不重要，我们可以离散化，然后使用二位前缀和，这样就可以求出左上角的奶牛数，然后再枚举分割线即可，答案公式如下：
```cpp
max({sum[i][j],sum[i][n]-sum[i][j],sum[n][j]-sum[i][j],sum[n][n]-sum[n][j]-sum[i][n]+sum[i][j]}))
```
因为用的 `set+map` 离散化，常数和空间稍微大点。
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum[1005][1005],ans=1e9+7;//答案初始化为极大值
set<int> s1,s2;//set离散化，自带去重
unordered_map<int,int> mp1,mp2;//标记离散化后的=值
struct node{
	int x,y;
}f[1005];
inline int read(){
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return res;
} //读入优化
int main(){
	n=read();
	for(int i=1;i<=n;++i)
		f[i]=node({read(),read()}),s1.insert(f[i].x),s2.insert(f[i].y);
	int tot=0;
	set<int>::iterator i;//迭代器遍历 set
	for(i=s1.begin();i!=s1.end();++i)
		mp1[*i]=++tot;
	tot=0;
	for(i=s2.begin();i!=s2.end();++i)
		mp2[*i]=++tot;//离散化
	for(int i=1;i<=n;++i)
		sum[mp1[f[i].x]][mp2[f[i].y]]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];//二维前缀和
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			ans=min(ans,max({sum[i][j],sum[i][n]-sum[i][j],sum[n][j]-sum[i][j],sum[n][n]-sum[n][j]-sum[i][n]+sum[i][j]}));//求解
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：tribool4_in (赞：1)

看到题目，要求一个区域内的奶牛的数量，自然想到二维前缀和。

二维前缀和 $s_{i,j}$ 表示 $(1,1)$ 到 $(i,j)$ 的矩形的所有数之和，易知递推式：

$s_{i,j}=s_{i,j-1}+s_{i-1,j}-s_{i-1,j-1}+a_{i,j}$

求 $(i,j)$ 到 $(k,l)$ 的和：

$s_{k,l}-s_{i-1,l}-s_{k,j-1}+s_{i-1, j-1}$

如果不好理解可以画图。

最后，题目中数据比较大，需要离散化。

代码：

```cpp
// Code By WLS
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	register int s=0, w=1;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
const int N = 1e3 + 5;
int n;
struct node {
	int s, i;
	bool operator < (node rhs) const {
		return s < rhs.s;
	}
} xs[N], ys[N];
int x[N], y[N];
int a[N][N], s[N][N];
signed main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		xs[i].s = read(), ys[i].s = read();
		xs[i].i = i, ys[i].i = i;
	}
	sort(xs + 1, xs + n + 1);
	sort(ys + 1, ys + n + 1);
	for (int i = 1; i <= n; i++) {
		x[xs[i].i] = i, y[ys[i].i] = i;
	}
	for (int i = 1; i <= n; i++) a[x[i]][y[i]] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
		}
	}
	int minn = 0x7f7f7f7f;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			minn = min(minn, max(max(s[i][j], s[i][n] - s[i][j]), max(s[n][j] - s[i][j], s[n][n] - s[i][n] - s[n][j] + s[i][j])));
		}
	}
	cout << minn << endl;
	return 0;
}
```

---

## 作者：KaguyaH (赞：1)

> [P3138](https://www.luogu.com.cn/problem/P3138).
> [Github blog](https://9u46-mx.github.io/post/Solution-P3138/).

---

平面上有 $n$ 个点 $(x_i, y_i)(2 \nmid x \land 2 \nmid y)$，找到两条直线 $x = a, y = b\,(2 \mid a \land 2 \mid b)$，使得平面被分成的四部分中包含点数最多的部分点数最小。

求这个最小值。

$1 \leqslant n \leqslant 10^3$，$0 < x, y \leqslant 10^6$。

---

考虑 $a$ 取 $x_i + 1$ 时必然不劣，$a$ 有 $n$ 种取值；同理 $b$ 有 $n$ 种取值。

将 $a$ 的取值排序，用两个树状数组维护直线 $x = a$ 左右的点的纵坐标，再枚举 $b$ 的取值即可。

时间复杂度 $\mathcal O(n^2 \log y)$，空间复杂度 $\mathcal O(n + y)$。

---

> [一种更优秀但常数更大的做法](https://www.luogu.com.cn/blog/236807/Solution-P6172)。

---

```cpp
# include <cstdio>
# include <cstring>
# include <algorithm>

namespace Main {
    namespace Source {
        typedef short unsigned int hu;
        typedef unsigned int uint;
        static inline const hu min(const hu a, const hu b) { return b < a ? b : a; }
        static inline const hu max(const hu a, const hu b) { return a < b ? b : a; }
        static inline const void amin(hu& a, const hu b) { a = min(a, b); }
        static const hu Max_hu(0xffff);
        template <const uint N>
        class Fenwick_tree {
            hu t[N + 1];
            static inline const uint lowbit(const uint x) { return x bitand ~x + 1; }
        public:
            Fenwick_tree() { memset(t, 0, sizeof t); }
            inline const void mp(uint x) { while (++t[x], (x += lowbit(x)) <= N); }
            inline const void mm(uint x) { while (--t[x], (x += lowbit(x)) <= N); }
            inline const hu query(uint x) const
            { hu r(0); while (r += t[x], x ^= lowbit(x)); return r; }
        };
    }
    using namespace Source;
    enum { N = 1000, Y = (const uint)1e6 };
    struct point {
        uint x, y;
        inline const void read() { scanf("%u%u", &x, &y); }
        friend inline const bool operator<(const point& a, const point& b) { return a.x < b.x; }
    };
    static hu n;
    static point p[N];
    static Fenwick_tree<Y> l, r;
    static hu sl, sr;
    static uint x[N], y[N], lx, ly;
    static hu ans(Max_hu);
    static inline const void main() {
        scanf("%hu", &n), sr = n;
        for (hu i(0); i < n; ++i) p[i].read(), x[i] = p[i].x + 1, y[i] = p[i].y + 1, r.mp(p[i].y);
        std::sort(&p[0], &p[n]);
        std::sort(&x[0], &x[n]), lx = std::unique(&x[0], &x[n]) - x;
        std::sort(&y[0], &y[n]), ly = std::unique(&y[0], &y[n]) - y;
        for (hu i(0), j(0); i < lx; ++i) {
            while (j < n and p[j].x <= x[i]) r.mm(p[j].y), --sr, l.mp(p[j].y), ++sl, ++j;
            for (hu k(0); k < ly; ++k)
                amin(ans,
                max(max(l.query(y[k]), sl - l.query(y[k])), max(r.query(y[k]), sr - r.query(y[k]))));
        }
        printf("%hu\n", ans);
    }
}

signed int main() { Main::main(); return 0; }
```

---

## 作者：文艺平衡树 (赞：1)

实际上这道题可以用数据结构加暴力做，开一个二维树状数组，用来统计左上角的和。枚举中心分割点的位置，算出左上，左下，右上，右下的点数和，取最大值与ans比较并更新。
开始先进行离散化以节约空间，就是按x排一遍序，将其x坐标改为排名（这样不会改变上下相对关系），再按y排一遍序，同上。
开始要预处理出left[i]即y坐标小于等于i的，和up[i]即x坐标小于等于i的。
```
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#define inf 0x3f3f3f3f
using namespace std;
int c[1001][1001],n,m,xs[1001],ys[1001],ans=inf;
struct point{
	int x;
	int y;
};
struct point p[1001];
//一堆比较函数 
bool cmp(struct point a,struct point b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
bool cmp1(struct point a,struct point b){
	return a.x<b.x;
}
bool cmp2(struct point a,struct point b){
	return a.y<b.y;
}
//模板树状数组 
int Lowbit(int x){
	return x&(-x);
}
int query(int x,int y){
	int i,ans;
	ans=0;
	while(x>0){
		i=y;
		while(i>0){
			ans+=c[x][i];
			i-=Lowbit(i);
		}
		x-=Lowbit(x);
	}
	return ans;
}
void change(int x,int y){
	int i;
	while(x<=n){
		i=y;
		while(i<=n){
			c[x][i]++;
			i+=Lowbit(i);
		}
		x+=Lowbit(x);
	}
	return;
}
int max(int a,int b){
	if(a>=b) return a;
	else return b;
}
int min(int a,int b){
	if(a<=b) return a;
	else return b;
}
//统计四个象限和 
void sum(int x,int y){
	int x1,x2,x3,x4;
	x1=query(x,y);//左上 
	x2=xs[x]-x1;//右上（即上方减左上） 
	x3=ys[y]-x1;//左下（即左边减左上） 
	x4=n-x1-x2-x3;//余下的就是右下 
	ans=min(ans,max(max(x1,x2),max(x3,x4)));
}
int main(){
	int i,j,k;
	int count=1;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y);
	//离散化 x 
	sort(p+1,p+n+1,cmp1);
	i=1;
	while(i<=n){
		j=i;
		//有可能出现x相同的 ，count表示排名 (可以并列) 
		while(p[i].x==p[j].x&&j<=n) //x相同就向后推进 
			j++;
		for(k=i;k<j;k++)
			p[k].x=count;
		xs[count]=j-1;//预处理出离散化后x小于count的 
		i=j;count++;
	}
	//离散化y，同理 
	sort(p+1,p+n+1,cmp2);
	i=1;count=1;
	while(i<=n){
		j=i;
		while(p[i].y==p[j].y&&j<=n)
			j++;
		for(k=i;k<j;k++)
			p[k].y=count;
		ys[count]=j-1;
		i=j;count++;
	}
	sort(p+1,p+n+1,cmp);
	//建立 树状数组 
	for(i=1;i<=n;i++){
		change(p[i].x,p[i].y);
	}
	//枚举中心位置 
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			sum(i,j);
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：scp020 (赞：0)

### 题目大意

给定 $n$ 头奶牛，奶牛分布在农场上，每头奶牛的坐标为 $(x_i,y_i)$，其中 $x_i \equiv1 \pmod{2}$ 且 $y_i \equiv1 \pmod{2}$。

让你找出一条水平的线和一条竖直的线，分农场为四个区域，希望每个区域的奶牛数量平均。

求有最多奶牛的区域最少可以有说少头奶牛。

### 解法

二维前缀和加上离散化。

考虑到农场为 $10^6 \times 10^6$ 的地图，无论是时间复杂度还是空间复杂度都太大，无法通过本题，又注意到本题只有 $n \le 10^3$，故考虑离散化处理。

对于每输入一组 $(x_i,y_i)$，我们存储它的坐标和输入顺序，以便确定该点离散后的位置。这里离散化可以使用 $sort$ 排序，记录排序后的位置即可（在这里之前存储每个点的输入顺序就有用了），新坐标为 $(nx_i,ny_i)$。

开始二位前缀和，$sum_{i,j}$ 表示坐标为 $(i,j)$ 的点前面（包括自己）有几头牛。

枚举每一个点，然后以该点为坐标原点建立平面直角坐标系，则四个象限的牛的头数分别为：

第二象限（左上）：$sum_{i,j}$。

第一象限（右上）：$sum_{i,n} - sum_{i,j}$。

第三象限（左下）：$sum_{n,j} - sum_{i,j}$。

第四象限（右下）：$sum_{n,n}+sum_{i,j}-sum_{i,n}-sum_{n,j}$。

把这四个象限的值取 $\max$ 然后与 $ans$ 比较取最小值即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void read(int &x)
{
	int f=1;
	char ch=getchar();
	x=0;
	for(;ch>57 || ch<48;ch=getchar()) if(ch==45) f=-1;
	for(;ch<=57 && ch>=48;ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	x=x*f;
}
struct number{int order,num;};
number x[1010],y[1010];
bool cmp(number a,number b)
{
	return a.num<b.num;
}
int n,nx[1010],ny[1010],sum[1010][1010],ans=0x3f3f3f3f;
int main()
{
	read(n);
	for(register int i=1;i<=n;i++) read(x[i].num),read(y[i].num),x[i].order=y[i].order=i;
	sort(x+1,x+n+1,cmp),sort(y+1,y+n+1,cmp);
	for(register int i=1;i<=n;i++) nx[x[i].order]=i,ny[y[i].order]=i;//标记离散化后的位置 
	for(register int i=1;i<=n;i++) sum[nx[i]][ny[i]]++;
	for(register int i=1;i<=n;i++)//二维前缀和 
		for(register int j=1;j<=n;j++) sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			ans=min(ans,max(max(sum[i][j],sum[i][n]-sum[i][j]),max(sum[n][j]-sum[i][j],sum[n][n]+sum[i][j]-sum[i][n]-sum[n][j])));
	cout<<ans;
	return 0;
}
```



---

