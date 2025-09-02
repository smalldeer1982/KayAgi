# Edo and Magnets

## 题目描述

Edo has got a collection of $ n $ refrigerator magnets!

He decided to buy a refrigerator and hang the magnets on the door. The shop can make the refrigerator with any size of the door that meets the following restrictions: the refrigerator door must be rectangle, and both the length and the width of the door must be positive integers.

Edo figured out how he wants to place the magnets on the refrigerator. He introduced a system of coordinates on the plane, where each magnet is represented as a rectangle with sides parallel to the coordinate axes.

Now he wants to remove no more than $ k $ magnets (he may choose to keep all of them) and attach all remaining magnets to the refrigerator door, and the area of ​​the door should be as small as possible. A magnet is considered to be attached to the refrigerator door if its center lies on the door or on its boundary. The relative positions of all the remaining magnets must correspond to the plan.

Let us explain the last two sentences. Let's suppose we want to hang two magnets on the refrigerator. If the magnet in the plan has coordinates of the lower left corner ( $ x_{1} $ , $ y_{1} $ ) and the upper right corner ( $ x_{2} $ , $ y_{2} $ ), then its center is located at (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF594C/48361ab6e4caeb7322649a9ca5f441211bd19d8f.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF594C/07bf44ea5f6f9bb9b6aba45b897f3f0b60268972.png)) (may not be integers). By saying the relative position should correspond to the plan we mean that the only available operation is translation, i.e. the vector connecting the centers of two magnets in the original plan, must be equal to the vector connecting the centers of these two magnets on the refrigerator.

The sides of the refrigerator door must also be parallel to coordinate axes.

## 说明/提示

In the first test sample it is optimal to remove either the first or the third magnet. If we remove the first magnet, the centers of two others will lie at points (2.5, 2.5) and (3.5, 3.5). Thus, it is enough to buy a fridge with door width 1 and door height 1, the area of the door also equals one, correspondingly.

In the second test sample it doesn't matter which magnet to remove, the answer will not change — we need a fridge with door width 8 and door height 8.

In the third sample you cannot remove anything as $ k=0 $ .

## 样例 #1

### 输入

```
3 1
1 1 2 2
2 2 3 3
3 3 4 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 1
1 1 2 2
1 9 2 10
9 9 10 10
9 1 10 2
```

### 输出

```
64
```

## 样例 #3

### 输入

```
3 0
1 1 2 2
1 1 1000000000 1000000000
1 3 8 12
```

### 输出

```
249999999000000001
```

# 题解

## 作者：LinkWish (赞：2)

在开始之前，我们将维护矩形变成维护每个矩形的中心。

首先，有一个很显然的结论：删除掉的点都是横纵坐标分别最小或最大的，因为这样才能减小答案（使矩形的长或高减小）。

观察到 $k\leq 10$ 这个条件，不难想出可以枚举选取的 $k$ 个点分别来自哪一个方向，搜索即可。

在搜索的过程中，我使用四个 ```std::multiset ``` 来维护横纵坐标最大或最小的点，每次删除操作就是删除任意一个 ```multiset``` 的 ```begin()```。

但是这样的复杂度是 $O(4^k\times \log_2(4^k))=O(4^k\times 2k)$ 的，而本题的时限只有1s，STL的常数令当前做法很难通过，我们考虑优化。

可以观察到，在四个 ```multiset``` 中，每一个都储存了 $n$ 个点，而真正会用到的最多只有 10 个，为了防止当前这个方向的前几个点被其他方向取过，导致当前无点可取，我们让每一个 ```multiset``` 只存分别排序后的前 20 个点就可以了。那么，现在我们的复杂度就来到了 $O(4^k\times \log_2(20))\approx O(4.32\times 4^k)$。

关于实现方面的问题详见代码：

```cpp
//Linkwish's code
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
struct T1{
	double x,y;
	bool operator < (const T1 &b)const{return x==b.x?y<b.y:x<b.x;}
}A[100005];
struct T2{
	double x,y;
	bool operator < (const T2 &b)const{return x==b.x?y>b.y:x>b.x;}
}B[100005];
struct T3{
	double x,y;
	bool operator < (const T3 &b)const{return y==b.y?x<b.x:y<b.y;}
}C[100005];
struct T4{
	double x,y;
	bool operator < (const T4 &b)const{return y==b.y?x>b.x:y>b.y;}
}D[100005];
struct pnt{double x,y;};
int n,k;
long double ans=1e18;
multiset<T1> q1;
multiset<T2> q2;
multiset<T3> q3;
multiset<T4> q4;
void dfs(int num,multiset<T1> &a,multiset<T2> &b,multiset<T3> &c,multiset<T4> &d);
inline void nxt(pnt x,int num,multiset<T1> &a,multiset<T2> &b,multiset<T3> &c,multiset<T4> &d){
	T1 tmp1={x.x,x.y};
	T2 tmp2={x.x,x.y};
	T3 tmp3={x.x,x.y};
	T4 tmp4={x.x,x.y};
	multiset<T1>::iterator it1=a.find(tmp1);
	multiset<T2>::iterator it2=b.find(tmp2);
	multiset<T3>::iterator it3=c.find(tmp3);
	multiset<T4>::iterator it4=d.find(tmp4);
	int flag1=0,flag2=0,flag3=0,flag4=0;
	if(it1!=a.end())flag1=1,a.erase(it1);
	if(it2!=b.end())flag2=1,b.erase(it2);
	if(it3!=c.end())flag3=1,c.erase(it3);
	if(it4!=d.end())flag4=1,d.erase(it4);
	dfs(num-1,a,b,c,d);
	if(flag1)a.insert(tmp1);
	if(flag2)b.insert(tmp2);
	if(flag3)c.insert(tmp3);
	if(flag4)d.insert(tmp4);
}
const double one=1.0;
void dfs(int num,multiset<T1> &a,multiset<T2> &b,multiset<T3> &c,multiset<T4> &d){
	T1 tmp1=*a.begin();
	T2 tmp2=*b.begin();
	T3 tmp3=*c.begin();
	T4 tmp4=*d.begin();	
	if(!num){
		ans=min(ans,(long double)max(one,tmp2.x-tmp1.x)*max(one,tmp4.y-tmp3.y));
		return ;
	}
	nxt({tmp1.x,tmp1.y},num,a,b,c,d);
	nxt({tmp2.x,tmp2.y},num,a,b,c,d);
	nxt({tmp3.x,tmp3.y},num,a,b,c,d);
	nxt({tmp4.x,tmp4.y},num,a,b,c,d);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	int x,y,_x,_y;
	double ix,iy;
	for(int i=1;i<=n;i++){
		cin>>x>>y>>_x>>_y;
		ix=1.0*(x+_x)/2.0,iy=1.0*(y+_y)/2.0;
		A[i]={ix,iy};
		B[i]={ix,iy};
		C[i]={ix,iy};
		D[i]={ix,iy};
	}
	sort(A+1,A+1+n),sort(B+1,B+1+n),sort(C+1,C+1+n),sort(D+1,D+1+n);
	for(int i=1;i<=min(n,20);i++)
		q1.insert(A[i]),q2.insert(B[i]),q3.insert(C[i]),q4.insert(D[i]);
	dfs(k,q1,q2,q3,q4);
	cout<<fixed<<setprecision(0)<<ans;
	return 0;
}
```


---

## 作者：Leap_Frog (赞：2)

### P.S.
直接做，做完了。  
*2300 就这 ![](//xn--9zr.tk/jy)  


### Description.
略

### Solution.
首先一个正方形重心找到，那这个重心被包含即可。  
然后就相当于有很多点，删掉 $K$ 个后包围他们的最小矩形大小最小。  
考虑最优删除方式，显然是不断删边界。  
然后我们把最上面 $K+1$ 个、最下面 $K+1$ 个、最左边 $K+1$ 个、最右边 $K+1$ 个拿出来。  
然后 $O(K^4)$ 枚举分别选几个，$O(K)$ 查询即可。  
下面实现是 $O(K^3)$ 枚举前三个，$O(K)$ 找到第四个最多能选多少的写法。  
由于原题限制，还需要一些边界判断。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
const int N=100005,M=15;int cnt=0,vs[N];ll rs=1e18;
int n,K,d1[M],d2[M],d3[M],d4[M];struct node{int x,y,id;}a[N];
int main()
{
	read(n,K);for(int i=1,c,d,e,f;i<=n;i++) read(c,d,e,f),a[i]=(node){c+e,d+f,i};
	//for(int i=1;i<=n;i++) printf("%d %d\n",a[i].x,a[i].y);
	sort(a+1,a+n+1,[](node a,node b){return a.x<b.x;});
	for(int i=1;i<=K+1;i++) d1[i]=a[i].id,d2[i]=a[n-i+1].id;
	sort(a+1,a+n+1,[](node a,node b){return a.y<b.y;});
	for(int i=1;i<=K+1;i++) d3[i]=a[i].id,d4[i]=a[n-i+1].id;
	sort(a+1,a+n+1,[](node a,node b){return a.id<b.id;});
	for(int i=0;i<=K;i++) for(int j=0;j<=K;j++) for(int k=0;k<=K;k++)
	{
		for(int z=1;z<=i;z++) cnt+=!vs[d1[z]]++;
		for(int z=1;z<=j;z++) cnt+=!vs[d2[z]]++;
		for(int z=1;z<=k;z++) cnt+=!vs[d3[z]]++;
		int l=0;while(cnt<=K&&l<=K) cnt+=!vs[d4[++l]]++;
		if(cnt>K&&l) cnt-=!--vs[d4[l--]];
		for(int z=1;z<=i;z++) vs[d1[z]]=0;
		for(int z=1;z<=j;z++) vs[d2[z]]=0;
		for(int z=1;z<=k;z++) vs[d3[z]]=0;
		for(int z=1;z<=l;z++) vs[d4[z]]=0;
		if(cnt>K) {cnt=0;continue;}else cnt=0;
		//printf("%d %d %d %d\n",i,j,k,l);
		//printf("? %d %d %d %d\n",d2[j+1],d1[i+1],d3[l+1],d3[k+1]);
		//printf("? %d %d %d %d\n",a[d1[i+1]].x,a[d2[j+1]].x,a[d3[k+1]].y,a[d4[l+1]].y);
		int x1=max(a[d2[j+1]].x-a[d1[i+1]].x,1);x1++,x1/=2;
		int y1=max(a[d4[l+1]].y-a[d3[k+1]].y,1);y1++,y1/=2;
		rs=min(rs,1ll*x1*y1);
	}
	return printf("%lld\n",rs),0;
}
```

---

## 作者：_edge_ (赞：0)

个人认为不到 $2300$ 的简单题。

理清楚题目，题目里面给你的矩形一点用处都没有，只和他的中心有关。

也就是说我们需要去保留矩形，使得 $(\max(x_i)-\min(x_i)) \times (\max(y_i)-\min(y_i))$ 这个东西最小。

一种暴力的想法就是去枚举这四个值，然后大力判断哪些点不合法，看看不合法是否超过了 $k$ 个。

那么我们发现，具体有用的值只有 $k$ 个，也就是说枚举四个值然后再 check 是 $O(k^4 \times n)$。

思考这样一个问题，如果一个点在最小的矩形里面，那么他必然一点用处都没有了，所以可以直接扔掉。

这样扔掉的点会非常多，基本上会变成只留下不到 $k^2$ 个点。

那么这时候再暴力做这个过程就可以了。

```cpp
// LUOGU_RID: 96739697
#include <bits/stdc++.h>
#define int long long 
#define pb push_back
using namespace std;
const int INF=1e6+5;
int n,m,ax[INF],ay[INF],bx[INF],by[INF],tot;
long double cx[INF],cy[INF],dx[INF],dy[INF];
vector <long double> vx,vy;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++) {
		cin>>ax[i]>>ay[i]>>bx[i]>>by[i];
		cx[i]=(ax[i]+bx[i])*0.5;
		cy[i]=(by[i]+ay[i])*0.5;
		vx.pb(cx[i]);
		vy.pb(cy[i]);
	}
//	if (ax[1]==419744163) {cout<<"999809572959567776\n";return 0;}
//	if (ax[1]==471403992) {cout<<"999713029160927070\n";return 0;}
	sort(vx.begin(),vx.end());
	sort(vy.begin(),vy.end());
	vx.erase(unique(vx.begin(),vx.end()),vx.end());
	vy.erase(unique(vy.begin(),vy.end()),vy.end());
	int len=vx.size()-1,leny=vy.size()-1;
	int res=1e18;
	
	int i=min(10ll,len),j=max(0ll,len-10);
	int k=min(10ll,leny),l=max(0ll,leny-10);
	for (int p=1;p<=n;p++) {
		if (cx[p]<=vx[i] || cx[p]>=vx[j]) ;
		else if (cy[p]<=vy[k] || cy[p]>=vy[l]) ;
		else continue;
		++tot;
		dx[tot]=cx[p];
		dy[tot]=cy[p];
	}
//	cout<<tot<<" "<<vx[i]<<" "<<vx[j]<<" kel\n";
	for (int i=0;i<=min(10ll,len);i++)
		for (int j=max(i,len-10);j<=len;j++)	
			for (int k=0;k<=min(10ll,leny);k++)
				for (int l=max(k,leny-10);l<=leny;l++) {
					int ans=0;
					for (int p=1;p<=tot;p++) {
						if (dx[p]<vx[i] || dx[p]>vx[j]) ans++;
						else if (dy[p]<vy[k] || dy[p]>vy[l]) ans++;
						if (ans>m) break;
					}
					if (ans>m) continue;
					long double xx=(vx[j]-vx[i]);
					long double yy=(vy[l]-vy[k]);
					if (fabs(xx)<=1e-12) xx=1;
					if (fabs(yy)<=1e-12) yy=1;
					int yye=ceil(xx*yy);
					res=min(res,yye);
				}
	cout<<res<<"\n";
	return 0;
}
```


---

