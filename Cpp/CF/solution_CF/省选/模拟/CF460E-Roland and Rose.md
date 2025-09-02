# Roland and Rose

## 题目描述

Roland loves growing flowers. He has recently grown a beautiful rose at point $ (0,0) $ of the Cartesian coordinate system. The rose is so beautiful that Roland is afraid that the evil forces can try and steal it.

To protect the rose, Roland wants to build $ n $ watch towers. Let's assume that a tower is a point on the plane at the distance of at most $ r $ from the rose. Besides, Roland assumes that the towers should be built at points with integer coordinates and the sum of squares of distances between all pairs of towers must be as large as possible. Note, that Roland may build several towers at the same point, also he may build some of them at point $ (0,0) $ .

Help Roland build the towers at the integer points so that the sum of squares of distances between all towers is maximum possible. Note that the distance in this problem is defined as the Euclidian distance between points.

## 样例 #1

### 输入

```
4 1
```

### 输出

```
16
0 1
0 1
0 -1
0 -1
```

## 样例 #2

### 输入

```
3 6
```

### 输出

```
312
0 6
5 -3
-5 -3
```

# 题解

## 作者：BFSDFS123 (赞：1)

暴力，启动！

很容易猜测，答案中的所有点距离圆心越远越好，这样它们之间的距离就会更大。

如果在圆上的整点有超过 $n$ 个，显然一定是在圆上的点更优，只需要暴力搜索圆上的点即可。

如果不足 $n$ 个，为了使两两之间距离平方更大，我们只需要找出与圆心距离稍近的整点，然后如果不够继续向内缩小……

不难发现，这样实际上就是我们让答案尽量在在凸包上，然后我们只需要暴力找即可。

什么时候凸包上的点最多呢？

在 $r=27$ 的时候，凸包上有 $36$ 个点，此时也是 $1\le r \le 30$ 中最多的。容易发现，凸包上的点，过圆心一定有与其相对的点，即与原点对称的那个点。

所以我们只需要将圆内所有整点排序，从大到小选择 $18$ 个点，然后暴力搜索就可以了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eps 1e-8
const int inf=0x3f3f3f3f;
const int Maxn=1e6+10;
double dist(int x1,int y1,int x2,int y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int dists(int x1,int y1,int x2,int y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
pair<int,int> G[Maxn];
bool cmp(pair<int,int> a,pair<int,int> b)
{
	double dist1=dist(a.first,a.second,0,0);
	double dist2=dist(b.first,b.second,0,0);
	return dist1>dist2;
}
int tot=0;
int res=0;
vector<int> reso;
vector<int> op;
int n,r;
void dfs(int now,int len,int ans)
{
	if(len==n)
	{
		if(res<ans)
		{
			res=ans;
			reso=op;
		}
		return ;
	}
	for(int i=now;i<=tot;i++)
	{
		int lans=0;
		for(int j=0;j<op.size();j++)
		{
			lans+=dists(G[i].first,G[i].second,G[op[j]].first,G[op[j]].second);
		}
		op.push_back(i);
		dfs(i,len+1,ans+lans);
		op.pop_back();
	}
	
	
}
int main()
{
	scanf("%d%d",&n,&r);
	for(int i=-r;i<=r;i++)
	{
		for(int j=-r;j<=r;j++)
		{
			if(dist(i,j,0,0)<=r*1.0)
			{
				G[++tot]=make_pair(i,j);
			}
		}
	}
	
	sort(G+1,G+1+tot,cmp);
	tot=min(tot,18);
	
	dfs(1,0,0);
	printf("%d\n",res);
	for(auto i:reso)
	{
		printf("%d %d\n",G[i].first,G[i].second);
	}
	return 0;
}

```

---

## 作者：听取MLE声一片 (赞：1)

模拟退火，启动！

首先把圆内整点都进行标号，问题转化为给每个塔填上一个标号。每个塔起始给定一个标号，然后每次修改指定随机一个塔改为一个随机的标号。

如果最开始的标号是随机撒的，那么这样写会过不去。

考虑如何找到一个更优的初始状态。第一个样例给我们的启示是把一半填在 $(0,r)$ 另一半填在 $(0,-r)$ 就算比较优的了。把这个设为初始状态就可以通过本题了。

```
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mkp make_pair 
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=5010;
const int M=4294967295;
int n,m,R,a[N],A[N],f1,f2;
int ans;
pii b[N];
mt19937 rnd(time(0));
void F(int s){
	if(s>ans){
		ans=s;
		for(int i=1;i<=n;i++)
			A[i]=a[i];
	}
}
int solve(){
	int res=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			res+=(b[a[i]].fi-b[a[j]].fi)*(b[a[i]].fi-b[a[j]].fi)+(b[a[i]].se-b[a[j]].se)*(b[a[i]].se-b[a[j]].se);
	return res;
}
void SA(){
	int ww=n/2;
	for(int i=1;i<=ww;i++)
		a[i]=f1;
	for(int i=ww+1;i<=n;i++)
		a[i]=f2;
	int res=solve();
	F(res);
	double t=100000,T=t,p=0.9996;
    while(T>1e-10){
        int x=rnd()%n+1,y=rnd()%m+1,w=a[x];
        a[x]=y;
        int s=solve();
        F(s);
        if(s>res||rnd()*1.0/M<exp(-fabs(s-res)/T))
			res=s;
		else a[x]=w;
        T*=p;
    }
}
signed main()
{
	n=read(),R=read();
	for(int i=-R;i<=R;i++)
		for(int j=-R;j<=R;j++)
			if(i*i+j*j<=R*R){
				b[++m]=mkp(i,j);
				if(i==0&&j==R)f1=m;
				if(i==0&&j==-R)f2=m;
			}
				
	for(int i=1;i<=200;i++)
	SA();
	cout<<ans<<'\n';
	for(int i=1;i<=n;i++)
		cout<<b[A[i]].fi<<' '<<b[A[i]].se<<'\n';
	return 0;
}



```

---

