# [GCPC 2023] Balloon Darts

## 题目描述

如你所知，在 ICPC 比赛中，每解决一道题目你就会获得一个彩色气球。
你在上一次比赛中表现出色，现在拥有了 $n$ 个令人瞩目的气球收藏。
显而易见，你想用飞镖把这些气球全部戳破。
然而，你只有三支飞镖。

![](https://cdn.luogu.com.cn/upload/image_hosting/3lkiybcb.png)

:::align{center}
游乐园里的气球射击项目。图片来自 blende12，[Pixabay](https://pixabay.com/photos/balloon-leisure-time-4525887/)
:::

这些气球被建模为平面上的点，位置固定。
每次投掷飞镖时，你可以自由选择起点和方向。
飞镖会沿着一条直线飞行，将路径上的所有气球全部戳破。

由于你在过去几年里练习了很多，
你可以精确地朝任意方向投掷飞镖，并且飞镖会无限远地飞行。
因此，如果有人能用三支飞镖戳破所有气球，那一定是你。
不过，在开始享受乐趣之前，你需要先判断
是否可以用至多三支飞镖戳破所有气球。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
0 0
1 1
2 4
3 9
4 16
5 25```

### 输出

```
possible```

## 样例 #2

### 输入

```
7
0 0
1 1
2 4
3 9
4 16
5 25
6 36```

### 输出

```
impossible```

## 样例 #3

### 输入

```
7
-1 -1
0 0
1 1
2 4
3 9
4 16
5 25```

### 输出

```
possible```

# 题解

## 作者：blackwhitekey (赞：3)

### 题解：P13667 [GCPC 2023] Balloon Darts
**思路**
---

首先，我们看看数据范围，$n\leq 10^{4} $ 这说明了什么，这说明了枚举根本过不了此题，于是，我们掏出秘密武器，随机化。每一次进行 $\mathcal{O}(n)$ 的枚举，再用除法取一下枚举次数的上限。但随机化的正确性呢？虽然我不会，但我从一位大佬那拿到了证明过程（已同意）。
![](https://cdn.luogu.com.cn/upload/image_hosting/i48nqq55.png)
从这张图片中我们可以得出，每次随机到的两个点共线的概率高于 $\frac{1}{3}$，于是，随机化的正确率也有了保证。于是，我们就可以爽快的过掉此题。

---

**代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e4+100;
int n;
int ax[N];
int ay[N];
int b[N];
int main()
{
  cin>>n;
  for(int i=1; i<=n; i++)
    cin>>ax[i]>>ay[i];
  int t=1000;
  while(t--)
  {
    for(int i=1; i<=n; i++)
      b[i]=0;
    int ans=0,x,y;
    for(int i=1; i<=3; i++)
    {
      while(1)
      {
        if(ans==n)
          break;
        x=rand()%n+1;
        if(b[x]==0)
          break;
      }
      b[x]=1;
      ans=min(ans+1,n);
      while(1)
      {
        if(ans==n)
          break;
        y=rand()%n+1;
        if(b[y]==0)
          break;
      }
      b[y]=1;
      ans=min(ans+1,n);
      for(int j=1; j<=n; j++)
      {
        if(b[j]==0)
        {
          if(abs((ay[j]-ay[x])*(ax[y]-ax[x])-(ay[y]-ay[x])*(ax[j]-ax[x]))==0)
          {
            b[j]=1;
            ans++;
          }
        }
      }
    }
    if(ans==n)
    {
      cout<<"possible";
      return 0;
    }
  }
  cout<<"impossible";
  return 0;
}
```

---

## 作者：Fire_flys (赞：1)

~~这题一看就很随机化。~~

分析一下题面。题目问你能不能用三条直线覆盖这平面上所有给出的点，那我们肯定要通过某些点来构造一些直线，于是就想到了随机化。最朴素的想法肯定是直接随机找 $6$ 个点暴力枚举他们之间所有可能的斜率再进行验证，但这样肯定会时间超限。

于是我就想出了一个更好的方法。我们每次在前几次没有覆盖的点中任意选取两个点构造出一条直线，再循环枚举一遍所有在这条直线上的点，给他们打上标记，并记录有多少个点，重复三遍，如果最终覆盖的点的数量刚好与给出的 $n$ 相同，就代表找到了一组合法的解。如果一次不成功，搞多几次就好了。根据概率公式算了一下，每次失败的概率最坏 $\frac{1}{3}$ 左右，搞个 $30$ 次左右，正确率就挺高了。

如果还有不懂的可以看看代码实现。
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int n,cnt,wz[N],tot;//wz[i]存储的是当前没被覆盖到的点的下标 
struct node{
	int x,y;
}c[N];
bool vis[N];//存储在当前情况下这个点有没有被覆盖到
bool check(int i,int j,int k){//检查是否三点共线 
	return ( (c[j].y-c[i].y)*(c[k].x-c[j].x) == (c[j].x-c[i].x)*(c[k].y-c[j].y) );//交叉相乘判断斜率防止精度问题 
} 
mt19937 rrand(time(0));
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>c[i].x>>c[i].y;
	for(int t=1;t<=30;t++){
		for(int i=1;i<=n;i++)vis[i]=0;
		tot=0;
		for(int dnt=1;dnt<=3;dnt++){
			cnt=0;
			for(int i=1;i<=n;i++){
				if(!vis[i])wz[++cnt]=i;//临时存储还没被覆盖的点的下标 
			}
			if(cnt<2){//如果只剩一个点或者没有点了那就可以直接退出了，因为过一个点有无数条直线 
				tot=n;
				break;
			}
			int xx=rrand()%cnt+1,yy=rrand()%cnt+1;//随机选取两个点 
			while(xx==yy)yy=rrand()%cnt+1;
			int sx=wz[xx],sy=wz[yy];//获取点的下标 
			for(int i=1;i<=n;i++){
				if(vis[i])continue;
				if(check(sx,sy,i)==true){
					tot++;vis[i]=true; 
				}
			} 
		}
		if(tot==n)return puts("possible"),0; 
	}
	cout<<"impossible"<<"\n";
	return 0;
}

```

---

## 作者：迟暮天复明 (赞：1)

把前四个点拿出来，里面一定存在两个点满足它们的连线是最终的一条线。枚举这两个点，问题转化为：有若干个点，问是否可以使用两条线覆盖所有的点。

考虑新的问题：把前三个点拿出来，里面一定存在两个点满足它们的连线是最终的一条线。枚举这两个点，那么除了它们确定的直线以外，其他所有点必须全部共线。

```cpp
struct Point{
  int x,y;
  Point(){}
  Point(int x,int y):x(x),y(y){}
  Point operator+(Point&b)const{return{x+b.x,y+b.y};}
  Point operator-(Point&b)const{return{x-b.x,y-b.y};}
  int operator*(Point b)const{return x*b.y-y*b.x;}
};
bool check(std::vector<Point>&q,int flag){
  int sz=q.size();
  if(sz<=2)return 1;
  Point P=q[1]-q[0];
  rep(i,2,sz-1)if(P*(q[i]-q[0]))return 0;
  return 1;
}
bool check(std::vector<Point>&p){
  int sz=p.size();
  if(sz<=4)return 1;
  rep(i,0,2)rep(j,i+1,2){
    std::vector<Point>q;
    Point P=p[j]-p[i];
    rep(k,0,sz-1)if(P*(p[k]-p[i]))q.pb(p[k]);
    if(check(q,1))return 1;
  }
  return 0;
}
void solve(){
  std::vector<Point>p;
  int n;read(n);p.resize(n);
  for(Point&x:p)read(x.x),read(x.y);
  if(n<=6){puts("possible");goto end;}
  rep(i,0,3)rep(j,i+1,3){
    std::vector<Point>q;
    Point P=p[j]-p[i];
    rep(k,0,n-1)if(P*(p[k]-p[i]))q.pb(p[k]);
    if(check(q)){puts("possible");goto end;}
  }
  puts("impossible");
}
```

---

## 作者：WuMin4 (赞：0)

## 题意

二维坐标系上有 $n$ 个整点，问能否找 $3$ 条直线穿过所有点。

## 思路

又一道神秘题。

两点确定一条直线不必多说。

根据鸽巢原理，当 $3$ 条直线能穿过所有点时，一定至少有一条直线穿过了 $\lceil{\frac{n}{3}}\rceil$ 个点。

于是我们可以随机选择 $2$ 个点，选到这条直线上的 $2$ 个点的概率一定大于 $\frac{1}{9}$。

假设我们选到了这条直线，问题就变为了 $2$ 条直线能否穿过剩下的点。类似的，随机选择 $2$ 个点在一条直线上的概率一定大于 $\frac{1}{4}$，剩下的一条直线可以直接判断。

假设数据有解，则我们每随机一次，找到正确答案的概率一定会大于 $\frac{1}{9}\times \frac{1}{4}=\frac{1}{36}$（实际概率比这个高得多，因为选到一条直线的概率变小时选到其他直线的概率会变大）。于是我们多随几次，如果找不到解，则无解。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
mt19937 rnd(time(0));
struct node{
	int x,y;
};
vector<node> m0,m1,m2;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int x,y,i=1;i<=n;i++)
		cin>>x>>y,m0.push_back({x,y});
	if(n<=4){
		cout<<"possible";
		return 0;
	}
	//防止丢失精度，将k用(fz/fm)表示，则有 y=(fz/fm)x+b->y*fm=fz*x+b*fm
	for(int T=1;T<=1000;T++){
		int fz,fm,g,b,x,y;
		//第一条直线（随机）
		x=0,y=0;
		while(x==y)
			x=rnd()%m0.size(),y=rnd()%m0.size();
		fz=m0[y].y-m0[x].y,fm=m0[y].x-m0[x].x;
		if(fm!=0){//注意判分母为0
			g=gcd(fz,fm);
			fz/=g,fm/=g;
		}
		b=m0[x].y*fm-fz*m0[x].x;
		m1.clear();
		for(int i=0;i<m0.size();i++)
			if(m0[i].y*fm!=fz*m0[i].x+b)
				m1.push_back(m0[i]);
		if(m1.size()<=3){
			cout<<"possible";
			return 0;
		}
		//第二条直线（随机）
		x=0,y=0;
		while(x==y)
			x=rnd()%m1.size(),y=rnd()%m1.size();
		fz=m1[y].y-m1[x].y,fm=m1[y].x-m1[x].x;
		if(fm!=0){
			g=gcd(fz,fm);
			fz/=g,fm/=g;
		}
		b=m1[x].y*fm-fz*m1[x].x;
		m2.clear();
		for(int i=0;i<m1.size();i++)
			if(m1[i].y*fm!=fz*m1[i].x+b)
				m2.push_back(m1[i]);
		if(m2.size()<=2){
			cout<<"possible";
			return 0;
		}
		//第三条直线
		x=0,y=1;
		fz=m2[y].y-m2[x].y,fm=m2[y].x-m2[x].x;
		if(fm!=0){
			g=gcd(fz,fm);
			fz/=g,fm/=g;
		}
		b=m2[x].y*fm-fz*m2[x].x;
		bool flag=0;
		for(int i=0;i<m2.size();i++)
			if(m2[i].y*fm!=fz*m2[i].x+b){
				flag=1;
				break;
			}
		if(!flag){
			cout<<"possible";
			return 0;
		}
	}
	cout<<"impossible";
	return 0;
}
```

---

## 作者：枫原万叶 (赞：0)

刚开始 [老师](https://www.luogu.com.cn/user/42082) 也没看出来，他给出的思路是把一个点以一根线旋转 180 度，那么就枚举这样的范围中哪个点的情况是最优的，但是这个思路时间复杂度过高（其实是我精度调不出来），下面来看一下正解。

考虑一下朴素的搜索是先以此确定三条直线，然后看看是否能穿过所有点，但是这样的做法时间复杂度达到 $O(n^3)$ 显然是不够优秀的，这个时候你可以看看展开标签中的第一个标签，考虑用鸽巢原理去优化。

因为对于 $n$ 个点放在 $3$ 条直线上，如果有解,那么 $4$ 个点一定有 $2$ 个在同一个直线上，那只需要找前 $4$ 个点组成的所有直线即可。

总结一下就是，对于平面上的任意 $(k+2)$ 个点，如果不能用k条直线覆盖，那么至少存在 $(k+1)$ 个点共线。

代码很好写，这里直接附上。

```cpp
#include<bits/stdc++.h>
#define endl "\n"
#define Robin ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
using namespace std;

typedef long long LL;

struct P {
	LL x, y;
	P(LL x=0, LL y=0) : x(x), y(y) {}
};

bool col(P a, P b, P c) {
	return (b.x-a.x)*(c.y-a.y) == (b.y-a.y)*(c.x-a.x);
}

bool f(vector<P> p, int k) {
	int n=p.size();
	if(n<=k) return 1;
	if(!k) return 0;
	if(k==1) {
		for(int i=2;i<n;i++)
			if(!col(p[0],p[1],p[i])) return 0;
		return 1;
	}
	int m=min(n,k+1);
	for(int i=0;i<m;i++)
		for(int j=i+1;j<m;j++) {
			vector<P> t;
			for(int x=0;x<n;x++)
				if(!col(p[i],p[j],p[x])) t.push_back(p[x]);
			if(f(t,k-1)) return 1;
		}
	return 0;
}

int main() {
	int n; cin>>n;
	vector<P> p(n);
	for(int i=0;i<n;i++) cin>>p[i].x>>p[i].y;
	cout<<(f(p,3)?"possible":"impossible")<<endl;
	return 0;
} 
```

---

