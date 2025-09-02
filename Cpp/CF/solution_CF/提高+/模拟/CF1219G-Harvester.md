# Harvester

## 题目描述

现在正值 Bubble Cup 决赛季，农夫 Johnny Bubbles 必须收获他的泡泡。这些泡泡分布在一个由 $N \times M$ 个方格组成的矩形泡泡田中，共有 $N$ 行 $M$ 列。第 $i$ 行第 $j$ 列的地块能产出 $A_{i,j}$ 个泡泡。

Johnny Bubbles 有一台非常特殊的自动驾驶泡泡收割机，每次只需手动将其放置在某一行或某一列的起点，它就会自动收割该行或该列的所有泡泡。当收割机到达该行或该列的末端后会停止，需要重新手动放置。收割机可以多次经过同一个地块，但每个地块的泡泡只能被收割一次。

Johnny 非常忙碌，所以每天最多只能手动放置收割机 4 次。同时他也很急切，希望第一天能收获尽可能多的泡泡。

请你帮助 Johnny 计算第一天最多能收获多少个泡泡。

## 说明/提示

在第一个样例中，Johnny 可以通过将收割机分别放在第一行和第二行，收割所有泡泡。

在第二个样例中，一种收割最多泡泡的方法是将收割机分别放在第二行、第四行、第二列和第四列。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2
1 2
3 4
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 5
0 9 2 7 0
9 0 3 0 5
0 8 0 3 1
6 7 4 3 9
3 6 4 1 0
```

### 输出

```
80
```

# 题解

## 作者：Melon_Musk (赞：10)

[Harvester题面](https://www.luogu.com.cn/problem/CF1219G)

个人感觉这题在绿题范围

## 题面描述

n * m的网格中，在第i行j列有a[i][j]个泡泡，每次可以收割一行或一列的泡泡，最多可以收割4次，问最多可以收割到多少泡泡。

## 分析

#### 1.错误的想法①

拿到题面，我首先的思路是一个简易的模拟：

直接读入二维数组，首先用前缀和统计每一行和每一列的总和

```cpp
for(ll i=1;i<=n;i++)
{
	for(ll j=1;j<=m;j++)
	{
		cin>>a[i][j];
		xx[i]+=a[i][j];
		yy[j]+=a[i][j];
	}
}
```

再在行和列中找到当前收割走此行/列后可以得到最多泡泡的行/列，每次收割走就把它会影响到的行/列处理一下

具体例子如第二个样例

5 5

0 9 2 7 0

9 0 3 0 5

0 8 0 3 1

6 7 4 3 9

3 6 4 1 0

第一次我们拿了第四行(xx[4])，所以要把所有列的前缀和都减去a[4][j],以防重复添加。

然后再重复四次。

提交后，惊奇地发现，第四个点就WA了，why？

这种想法很显然是错误的，当我们发现某行取走能得到当前的最大值，然后取了这行之后会把所有列都减小，但是有可能此时取要多个列更优。即这种模拟做法可能会失去最大的结果

#### 2.错误的想法②

既然会失去某些结果，那要不就在上一种代码的思路上dfs把所有能取的方法走一遍

但是，显而易见这种$O(C_{n+m}^4)$的复杂度会炸掉（提交后第4个点就TLE了）

#### 3.正解

那么这条路看起来已经走到头了，所以正解要怎么搞！？

不妨换一种思路,既然只有四次取泡泡的机会，那取的方案应该只有5种：

1.取四行

2.取四列

3.取一行三列

4.取一列三行

5.取两行两列

那么我们只要矩阵中分别以以上5种方法计算一遍取最大值就可以了！

对于第1种方案，只需把所有行排序一下并把最大的四行加起来就行（当然不排序直接找最大四行也是可以的），复杂度$O(NlogN)$。

```cpp
for(ll i=1;i<=n;i++) xxx[i]=xx[i];
sort(xxx+1,xxx+n+1,cmp);
for(ll i=1;i<=4;i++) sum+=xxx[i];
ll maxx=sum
```

对于第2种方案，同上。

```cpp
for(ll i=1;i<=m;i++) yyy[i]=yy[i];
sort(yyy+1,yyy+m+1,cmp);
for(ll i=1;i<=4;i++) sum+=yyy[i];
maxx=max(maxx,sum);
```


对于第3种方案，先选择一行，再在所有列里面找最大的三列，复杂度$O(NM)$。

```cpp
for(ll i=1;i<=n;i++)
	{
		ll max1=0,max2=0,max3=0;
		for(ll j=1;j<=m;j++)
		{
			yyy[j]=yy[j]-a[(i-1)*m+j];
			if(yyy[j]>=max1) max3=max2,max2=max1,max1=yyy[j]; else 
			if(yyy[j]>=max2) max3=max2,max2=yyy[j]; else
			if(yyy[j]>=max3) max3=yyy[j];
		} 
		sum=max1+max2+max3+xx[i];
		maxx=max(maxx,sum);
	}
```


对于第4种方案，同上。

```cpp
for(ll i=1;i<=m;i++)
	{
		ll max1=0,max2=0,max3=0;
		for(ll j=1;j<=n;j++)
		{
			xxx[j]=xx[j]-a[(j-1)*m+i];
			if(xxx[j]>=max1) max3=max2,max2=max1,max1=xxx[j]; else 
			if(xxx[j]>=max2) max3=max2,max2=xxx[j]; else
			if(xxx[j]>=max3) max3=xxx[j];
		} 
		sum=max1+max2+max3+yy[i];
		maxx=max(maxx,sum);
	}
```


对于第5种方案，先用两个循环固定两行，再在所有列里面找最大的两列，复杂度$O(N^2M)$

```cpp
for(ll i=1;i<n;i++)
 	{
 		for(ll j=i+1;j<=n;j++)
 		{
 			ll max1=0,max2=0;
 			for(ll k=1;k<=m;k++)
 			{
 				yyy[k]=yy[k]-a[(i-1)*m+k]-a[(j-1)*m+k];
				if(yyy[k]>=max1) max2=max1,max1=yyy[k]; else 
				if(yyy[k]>=max2) max2=yyy[k]; 
			}
			sum=max1+max2+xx[i]+xx[j];
			maxx=max(maxx,sum);
		}
	}
```


在上面五种方案里选最大的那个就是答案了

## 本题注意点

1.因为$n*m<=10^5$ ，所以这里可以把二维数组压成一维来储存，把原来的$a[i][j]$储存在$a[(i-1)*m+j]$中

```cpp
for(ll i=1;i<=n;i++)
	for(ll j=1;j<=m;j++)
	{
		cin>>a[(i-1)*m+j];
		xx[i]+=a[(i-1)*m+j];
		yy[j]+=a[(i-1)*m+j];
	}
```
2.对于第五种方案$O(N*N*M)$的时间复杂度，很可能会超时（实测第6个点TLE了）。

所以在n>m 时，我们把整个数组旋转90°，即把nm互换。


```cpp
if(n>m)
	{ 
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				b[(j-1)*n+i]=a[(i-1)*m+j];
		swap(n,m);
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				a[(i-1)*m+j]=b[(i-1)*m+j];
	}
```

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=100010;
unsigned long long ans,anss;
ll n,m;
ll xx[maxn],yy[maxn],xxx[maxn],yyy[maxn],a[maxn],b[maxn];
ll tt[5],rt[5];
bool cmp(ll x,ll y) {return x>y;}
ll work()
{
	ll sum=0;
	for(ll i=1;i<=n;i++) xxx[i]=xx[i];
	sort(xxx+1,xxx+n+1,cmp);
	for(ll i=1;i<=4;i++) sum+=xxx[i];
	ll maxx=sum;
	sum=0;
//	cout<<maxx<<endl;
	
	for(ll i=1;i<=m;i++) yyy[i]=yy[i];
	sort(yyy+1,yyy+m+1,cmp);
	for(ll i=1;i<=4;i++) sum+=yyy[i];
	maxx=max(maxx,sum);
	sum=0;
//	cout<<maxx<<endl;
	
	for(ll i=1;i<=n;i++)
	{
		ll max1=0,max2=0,max3=0;
		for(ll j=1;j<=m;j++)
		{
			yyy[j]=yy[j]-a[(i-1)*m+j];
			if(yyy[j]>=max1) max3=max2,max2=max1,max1=yyy[j]; else 
			if(yyy[j]>=max2) max3=max2,max2=yyy[j]; else
			if(yyy[j]>=max3) max3=yyy[j];
		} 
		sum=max1+max2+max3+xx[i];
		maxx=max(maxx,sum);
	}
	sum=0;
//	cout<<maxx<<endl;
	
	for(ll i=1;i<=m;i++)
	{
		ll max1=0,max2=0,max3=0;
		for(ll j=1;j<=n;j++)
		{
			xxx[j]=xx[j]-a[(j-1)*m+i];
			if(xxx[j]>=max1) max3=max2,max2=max1,max1=xxx[j]; else 
			if(xxx[j]>=max2) max3=max2,max2=xxx[j]; else
			if(xxx[j]>=max3) max3=xxx[j];
		} 
		sum=max1+max2+max3+yy[i];
		maxx=max(maxx,sum);
	}
	sum=0;
//	cout<<maxx<<endl;
	
	if(n>m)
	{ 
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				b[(j-1)*n+i]=a[(i-1)*m+j];
		swap(n,m);
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				a[(i-1)*m+j]=b[(i-1)*m+j];
	}
 	for(ll i=1;i<n;i++)
 	{
 		for(ll j=i+1;j<=n;j++)
 		{
 			ll max1=0,max2=0;
 			for(ll k=1;k<=m;k++)
 			{
 				yyy[k]=yy[k]-a[(i-1)*m+k]-a[(j-1)*m+k];
				if(yyy[k]>=max1) max2=max1,max1=yyy[k]; else 
				if(yyy[k]>=max2) max2=yyy[k]; 
			}
//			cout<<max1<<' '<<max2<<' '<<xx[i]<<' '<<xx[j]<<endl;
			sum=max1+max2+xx[i]+xx[j];
			maxx=max(maxx,sum);
		}
	}
	return maxx;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(ll i=1;i<=n;i++)
	{
		for(ll j=1;j<=m;j++)
		{
			cin>>a[(i-1)*m+j];
			xx[i]+=a[(i-1)*m+j];
			yy[j]+=a[(i-1)*m+j];
		}
	}
	cout<<work()<<endl;
	return 0;
}
```

---

## 作者：jdsb (赞：5)

## 题意
给出一个$n*m$的矩阵，矩阵上每个点都有一个权值，我们需要从中收割4次，每次收割都可以收取一行或一列的权值，每个点最多只能求$1$次，求出最大权值和。

## 分析
* 首先观察数据，我们发现是$n*m<=10^5$，而不是单独的$n$或$m$的取值，所以有可能有这样的几组数据：$n=1,m=10^5;n=10^5,m=1$，这时我们发现单纯地开二维数组是不能同时处理这样的数据的，所以我们就需要压维，将两维压成一维，来处理数据。就像这个函数:
```cpp
int ya(int x,int y)
{
    return (x-1)*m+y;
}
```
* 对于要取的四次，我们来枚举要取的哪种情况，总共有五种情况，分别是取四行，三行一列，两行两列，一行三列，四列。我们先求出每行每列的前缀和，然后来分情况讨论。对于第一种第五种可以一起考虑，我们用一个小根堆来存最大的前四行，然后暴力求出答案，时间复杂度$O(n)$。对于第二种第四种可以一起考虑，先锁定好一列，再用跟前面一样的方法暴力求出剩下三行的答案，但要注意重叠的数只能算一次，时间复杂度$O(nm)$。对于第三种情况，我们先锁定好两列，再用跟前面一样的方法暴力求出剩下两行的答案，时间复杂度为$O(n^2m)$，这个时间复杂度其实挺危险的，如果n恰好为大的那个数就有可能超时，所以我们要先进行判断，如果$n>m$就将数组旋转$90°$，使得$n$更小。这样最坏情况时，时间也只有$\sqrt [\frac{3}{2}]{10^5}≈3*10^6$，就可以轻松过这道题啦。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
ll n,m,a[N],b[N],row[N],column[N],ans;
int ya(int x,int y)
{
	return (x-1)*m+y;
}
priority_queue<ll,vector<ll>,greater<ll> > q;
void solve1()
{
	ll sum=0;
	for(int i=1;i<=n;i++)
	{
		ll val=row[i];
		if(q.size()<4)	q.push(val);
		else
		{
			if(val>q.top())
			{
				q.pop();
				q.push(val);
			}
		}
	}
	while(q.size())
	{
		sum+=q.top();
		q.pop();
	}
	ans=max(ans,sum);
}
void solve2()
{
	ll sum=0;
	for(int i=1;i<=m;i++)
	{
		ll val=column[i];
		if(q.size()<4)	q.push(val);
		else
		{
			if(val>q.top())
			{
				q.pop();
				q.push(val);
			}
		}
	}
	while(q.size())
	{
		sum+=q.top();
		q.pop();
	}
	ans=max(ans,sum);
}
void solve3()
{
	for(int i=1;i<=n;i++)
	{
		ll sum=row[i];
		for(int j=1;j<=m;j++)
		{
			ll val=column[j]-a[ya(i,j)];
			if(q.size()<3) q.push(val);
			else
			{
				if(val>q.top())
				{
					q.pop();
					q.push(val);
				}
			}
		}
		while(q.size())
		{
			sum+=q.top();
			q.pop();
		}
		ans=max(ans,sum);
	}
}
void solve4()
{
	for(int i=1;i<=m;i++)
	{
		ll sum=column[i];
		for(int j=1;j<=n;j++)
		{
			ll val=row[j]-a[ya(j,i)];
			if(q.size()<3) q.push(val);
			else
			{
				if(val>q.top())
				{
					q.pop();
					q.push(val);
				}
			}
		}
		while(q.size())
		{
			sum+=q.top();
			q.pop();
		}
		ans=max(ans,sum);
	}
}
void solve5()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			ll sum=row[i]+row[j];
			for(int k=1;k<=m;k++)
			{
				ll val=column[k]-a[ya(i,k)]-a[ya(j,k)];
				if(q.size()<2) q.push(val);
				else
				{
					if(q.top()<val)
					{
						q.pop();
						q.push(val);
					}
				}
			}
			while(q.size())
			{
				sum+=q.top();
				q.pop();
			}
			ans=max(ans,sum);
		}
	}
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lld",&b[ya(i,j)]);
	if(n>m)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[(j-1)*n+i]=b[ya(i,j)];
		swap(n,m);
	}
	else
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[ya(i,j)]=b[ya(i,j)];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int x=a[ya(i,j)];
			row[i]+=x;
			column[j]+=x;
		}
	solve1();
	solve2();
	solve3();
	solve4();
	solve5();
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：FFTotoro (赞：2)

## 前言

分类讨论好题 & 100 蓝 AC 祭。

## 解法

首先，因为我们只能确定 $N\times M$ 的范围，所以数组需要使用 `std::vector` 存储。

其次，用数组 $s_1,s_2$ 分别维护每一行、每一列的泡泡的数量总和；

接着，容易观察到，本题的最大值可能有 $5$ 种情况：

- 选择 $4$ 行；

- 选择 $4$ 列；

- 选择 $3$ 行 $1$ 列；

- 选择 $3$ 列 $1$ 行；

- 选择 $2$ 行 $2$ 列。

对于前两种情况，只需要从预处理出的 $s_1,s_2$ 中分别选择出最大的四个相加就可以了；

对于三、四种情况，确定那唯一的 $1$ 行 / $1$ 列，再从剩下的列 / 行中选择出**减去它与那唯一的 $1$ 行 / $1$ 列交界处的泡泡**（容斥原理）的三个最大的相加；

对于第五种情况，判断一下 $N$ 和 $M$ 的大小关系：

- 若 $N>M$，我们就枚举那两个列，接着按照类似三、四中的方法选出去除交点后总和最大的两列相加；

- 否则，枚举两个行，然后再选出两个去除交点后总和最大的两行相加；

五种情况取最大值即可。

对于每一种情况，中间取最大的若干个值可以使用优先队列维护。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  int n,m; cin>>n>>m;
  vector<vector<int> > a(n,vector<int>(m));
  vector<int> s(n),s2(m),r(8);
  for(auto &i:a)for(auto &j:i)cin>>j;
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
      s[i]+=a[i][j],s2[j]+=a[i][j];
  priority_queue<int> q[2];
  for(auto &i:s)q[0].emplace(i);
  for(int i=1;i<=4&&!q[0].empty();i++)
    r[0]+=q[0].top(),q[0].pop();
  for(auto &i:s2)q[1].emplace(i);
  for(int i=1;i<=4&&!q[1].empty();i++)
    r[1]+=q[1].top(),q[1].pop();
  for(int i=0;i<n;i++){
    priority_queue<int> p;
    for(int j=0;j<m;j++)
      p.emplace(s2[j]-a[i][j]);
    r[5]=s[i]; for(int i=1;i<=3&&!p.empty();i++)
      r[5]+=p.top(),p.pop();
    r[2]=max(r[2],r[5]);
  }
  for(int i=0;i<m;i++){
    priority_queue<int> p;
    for(int j=0;j<n;j++)
      p.emplace(s[j]-a[j][i]);
    r[5]=s2[i]; for(int i=1;i<=3&&!p.empty();i++)
      r[5]+=p.top(),p.pop();
    r[3]=max(r[3],r[5]);
  }
  if(n>m){
    for(int i=0;i<m-1;i++)
      for(int j=i+1;j<m;j++){
        priority_queue<int> p;
        for(int k=r[5]=0;k<n;k++)
          p.emplace(s[k]-a[k][i]-a[k][j]);
        for(int i=1;i<=2&&!p.empty();i++)
          r[5]+=p.top(),p.pop();
        r[4]=max(r[4],r[5]+s2[i]+s2[j]);
      }
  }
  else{
    for(int i=0;i<n-1;i++)
      for(int j=i+1;j<n;j++){
        priority_queue<int> p;
        for(int k=r[5]=0;k<m;k++)
          p.emplace(s2[k]-a[i][k]-a[j][k]);
        for(int i=1;i<=2&&!p.empty();i++)
          r[5]+=p.top(),p.pop();
        r[4]=max(r[4],r[5]+s[i]+s[j]);
      }
  }
  cout<<*max_element(r.begin(),r.end())<<endl;
  return 0;
}
```

---

## 作者：123zbk (赞：1)

直接暴力。一共选 $4$ 次，$5$ 种情况：

- 四行，排序选前四个。

- 四列，同理。

- 一行三列，枚举每一行，再选最多的前三列，注意不能算重复。

- 三行一列，同理。

- 两行两列，枚举两行，再选前两列。

但是第五种情况 $O(n^2m)$ 很容易 TLE，所以如果 $n>m$ 就把 $n$ 和 $m$ 调换一下即可，此时复杂度 $O(nm \sqrt{nm})$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int n,m,a[maxn],x[maxn],y[maxn],xx[maxn],yy[maxn],mx,sum,max1,max2,max3,b[maxn];
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%lld",&a[(i-1)*m+j]);
            x[i]+=a[(i-1)*m+j];
            y[j]+=a[(i-1)*m+j];
        }
    }

    for(int i=1;i<=n;i++)
    {
        xx[i]=x[i];
    }
    sort(xx+1,xx+n+1,greater<int>());
    for(int i=1;i<=4;i++)
    {
        sum+=xx[i];
    }
    mx=sum;
    sum=0;

    for(int i=1;i<=n;i++)
    {
        yy[i]=y[i];
    }
    sort(yy+1,yy+m+1,greater<int>());
    for(int i=1;i<=4;i++)
    {
        sum+=yy[i];
    }
    mx=max(mx,sum);
    sum=0;

    for(int i=1;i<=n;i++)
    {
        max1=max2=max3=0;
        for(int j=1;j<=m;j++)
        {
            yy[j]=y[j]-a[(i-1)*m+j];
            if(yy[j]>max1)
            {
                max3=max2;
                max2=max1;
                max1=yy[j];
            }
            else if(yy[j]>max2)
            {
                max3=max2;
                max2=yy[j];
            }
            else if(yy[j]>max3)
            {
                max3==yy[j];
            }
        }
        sum=max1+max2+max3+x[i];
        mx=max(mx,sum);
    }
    sum=0;

    for(int j=1;j<=m;j++)
    {
        max1=max2=max3=0;
        for(int i=1;i<=n;i++)
        {   
            xx[i]=x[i]-a[(i-1)*m+j];
            if(xx[i]>max1)
            {
                max3=max2;
                max2=max1;
                max1=xx[i];
            }
            else if(xx[i]>max2)
            {
                max3=max2;
                max2=xx[i];
            }
            else if(xx[i]>max3)
            {
                max3=xx[i];
            }
        }
        sum=max1+max2+max3+y[j];
        mx=max(mx,sum);
    }
    sum=0;

    if(n>m)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                b[(j-1)*n+i]=a[(i-1)*m+j];
            }
        }

        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)
            {
                a[(i-1)*n+j]=b[(i-1)*n+j];
            }
        }
        swap(m,n);
    }

    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            max1=max2=0;
            for(int k=1;k<=m;k++)
            {
                yy[k]=y[k]-a[(i-1)*m+k]-a[(j-1)*m+k];
                if(yy[k]>max1)
                {
                    max2=max1;
                    max1=yy[k];
                }
                else if(yy[k]>max2)
                {
                    max2=yy[k];
                }
            }
            sum=max1+max2+x[i]+x[j];
            mx=max(mx,sum);
        }
    }
    printf("%lld",mx);
    return 0;
}
```

---

## 作者：_Ponder_ (赞：1)

[Harvester](https://www.luogu.com.cn/problem/CF1219G)

### 题目大意

给定 $n\times m$ 的网格，每次可以选一行或一列，将这一行或一列上的数全部取走，最多可以取四次，问取走的数的和的最大值。

### 思路分析

~~没事干了把以前写过的题拿出来写题解。~~

分类讨论题。

在只能取四次的情况下一共只有这么几种可能：

- 选四行：

毫无疑问，行之间互不干扰，把每行的和求出来选四个最大的就可以了。

- 选四列： 类似于选四行的情况。

- 选一行三列：

枚举选哪行，再扫一遍求出去掉这一行之后最大的三列就行了，时间复杂度 $O(nm)$。（不过用排序求的时间复杂度就是 $O(nm\log m)$）

- 选一列三行：类似于选一行三列的情况。

- 选两行两列：

枚举选哪两行，再扫一遍求出去掉这两行之后最大的两列就行了。时间复杂度 $O(n^2m)$。

注意到 $n$ 很大，$m$ 很小时时间复杂度会炸，因此这时我们直接将行列交换就行了。时间复杂度为 $O(\min(n^2m, m^2n))=O(nm\sqrt {nm})$。

将所有情况取最大值就做完了，总时间复杂度为 $O(nm\sqrt {nm}+nm\log (n+m))$。

### 代码

（写麻烦了）

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int N = 100100;
#define inf 0x3f3f3f3f
#define int long long

int n, m, ans;
int mp[N], sum13[N], sum31[N], sum42[N], sum24[N];

int point(int x, int y){
    if (x < 1 || y < 1 || x > n || y > m) return 0;
    return (x - 1) * m + y;
}

bool cmp(int a, int b){
    return a > b;
}

int calc(vector <int> v, int siz){
    int res = 0;
    for (int i = 0; i < min(siz, (int)v.size()); i ++) res += v[i];
    return res;
}

signed main(){
    scanf("%lld %lld", &n, &m);
    for (int i = 1; i <= n * m; i ++)
        scanf("%lld", &mp[i]);
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++) {
            sum42[point(i, j)] = sum42[point(i, j - 1)] + mp[point(i, j)];
            sum13[point(i, j)] = sum13[point(i - 1, j)] + mp[point(i, j)];
        }
    for (int i = n; i >= 1; i --)
        for (int j = m; j >= 1; j --) {
            sum24[point(i, j)] = sum24[point(i, j + 1)] + mp[point(i, j)];
            sum31[point(i, j)] = sum31[point(i + 1, j)] + mp[point(i, j)];
        }
    vector <int> v1, v2;
    for (int i = 1; i <= n; i ++) v1.push_back(sum24[point(i, 1)]);
    for (int i = 1; i <= m; i ++) v2.push_back(sum31[point(1, i)]);
    sort(v1.begin(), v1.end(), cmp);
    sort(v2.begin(), v2.end(), cmp);
    ans = max({ans, calc(v1, 4), calc(v2, 4)});
    for (int i = 1; i <= n; i ++) {
        vector <int> v;
        for (int j = 1; j <= m; j ++)
            v.push_back(sum13[point(i - 1, j)] + sum31[point(i + 1, j)]);
        sort(v.begin(), v.end(), cmp);
        ans = max(ans, sum24[point(i, 1)] + calc(v, 3));
    }
    for (int i = 1; i <= m; i ++) {
        vector <int> v;
        for (int j = 1; j <= n; j ++)
            v.push_back(sum42[point(j, i - 1)] + sum24[point(j, i + 1)]);
        sort(v.begin(), v.end(), cmp);
        ans = max(ans, sum31[point(1, i)] + calc(v, 3));
    }
    if (n < m) {
        for (int i = 1; i <= n; i ++)
            for (int j = i + 1; j <= n; j ++) {
                int mmax = 0, smax = 0;
                for (int k = 1; k <= m; k ++) {
                    int t = sum31[point(1, k)] - mp[point(i, k)] - mp[point(j, k)];
                    if (t >= mmax) smax = mmax, mmax = t;
                    else if (t >= smax) smax = t;
                }
                ans = max(ans, sum24[point(i, 1)] + sum24[point(j, 1)] + mmax + smax);
            }                    
    }
    else {
        for (int i = 1; i <= m; i ++)
            for (int j = i + 1; j <= m; j ++) {
                int mmax = 0, smax = 0;
                for (int k = 1; k <= n; k ++) {
                    int t = sum24[point(k, 1)] - mp[point(k, i)] - mp[point(k, j)];
                    if (t >= mmax) smax = mmax, mmax = t;
                    else if (t >= smax) smax = t;
                }
                ans = max(ans, sum31[point(1, i)] + sum31[point(1, j)] + mmax + smax);
            }      
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：No21 (赞：1)

### 解题思路

一道很不错的分类讨论题，注意到操作次数很少，一次我们考虑一共有几种操作的可能。

首先不难发现，对于收割的泡泡的总数量来说，收割的顺序并不重要，因此我们只需要考虑收割哪几行或哪几列即可。

一共可以收割 $4$ 次，我们考虑每种收割方案一定在以下几种情况中：

- 首先，若 $N \leqslant 4$ 或者 $M \leqslant 4$，那么直接收割所有的泡泡。否则，则有下面几种情况。

- 取 $4$ 行泡泡。

- 取 $4$ 列泡泡。

- 取 $1$ 行和 $3$ 列泡泡。

- 取 $3$ 行和 $1$ 列泡泡。

- 取 $2$ 行和 $2$ 列泡泡。

好了，知道了这些，我们考虑怎么处理每种情况。

首先无论是哪种情况，我们需要的都是和，因此我们先处理出来每一行和每一列的和。

第一种情况很简单，直接把每一行（或者每一列）加起来即可。

第二种情况和第三种情况类似，找四行（四列）最大的即可。

第四种情况和第五种情况类似，我们可以枚举每一行（一列），然后找删掉每一行（一列）后所有列（行）中的最大的三个值即可。

第六种情况的思路和第四种第五种相似，但这里要注意，$O(N^2M)$ 的复杂度和 $O(NM^2)$ 的复杂度在一些极端数据下是完全不同的，因此我们需要判断一下 $N$ 和 $M$ 的大小，然后选择枚举两行去找所有列在删掉这两行后最大的两个值或者枚举两列去找所有行在删掉这两列后最大的两个值。

### 细节

- 因为题目只保证了 $N \times M$ 的范围，因此本题需要使用 vector。

- 记得开 long long

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace TO
{
    int n,m,ans1,ans2,ans3,ans4,ans5,aa;
    vector <int> a[100021];
    struct sum
    {
        int val,id;
    }sumi[100021],sumj[100021];
    bool cmp(sum x,sum y)
    {
        return x.val<y.val;
    }
    int mian()
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)
        {
            a[i].push_back(0);
            sumi[i].id=i;
            for(int j=1;j<=m;j++)
            {
                cin>>aa;
                a[i].push_back(aa);
                sumi[i].val+=a[i][j];
                sumj[j].val+=a[i][j];
                sumj[j].id=j;
            }
        }
        if(n<=4)
        {
            for(int i=1;i<=4;i++)
                ans1+=sumi[i].val;
            cout<<ans1<<'\n';
            return 0;
        }
        if(m<=4)
        {
            for(int i=1;i<=4;i++)
                ans2+=sumj[i].val;
            cout<<ans2<<'\n';
            return 0;
        }
        sort(sumi+1,sumi+1+n,cmp);
        sort(sumj+1,sumj+1+m,cmp);
        ans1=sumi[n].val+sumi[n-1].val+sumi[n-2].val+sumi[n-3].val;
        ans2=sumj[m].val+sumj[m-1].val+sumj[m-2].val+sumj[m-3].val;
        for(int i=1;i<=n;i++)
        {
            int maxx1=0,maxx2=0,maxx3=0;
            for(int j=1;j<=m;j++)
            {
                if(sumj[j].val-a[sumi[i].id][sumj[j].id]>=maxx1)
                {
                    maxx3=maxx2;
                    maxx2=maxx1;
                    maxx1=sumj[j].val-a[sumi[i].id][sumj[j].id];
                }
                else if(sumj[j].val-a[sumi[i].id][sumj[j].id]>=maxx2)
                {
                    maxx3=maxx2;
                    maxx2=sumj[j].val-a[sumi[i].id][sumj[j].id];
                }
                else if(sumj[j].val-a[sumi[i].id][sumj[j].id]>maxx3)
                    maxx3=sumj[j].val-a[sumi[i].id][sumj[j].id];
            }
            ans3=max(ans3,sumi[i].val+maxx1+maxx2+maxx3);
        }
        for(int j=1;j<=m;j++)
        {
            int maxx1=0,maxx2=0,maxx3=0;
            for(int i=1;i<=n;i++)
            {
                if(sumi[i].val-a[sumi[i].id][sumj[j].id]>=maxx1)
                {
                    maxx3=maxx2;
                    maxx2=maxx1;
                    maxx1=sumi[i].val-a[sumi[i].id][sumj[j].id];
                }
                else if(sumi[i].val-a[sumi[i].id][sumj[j].id]>=maxx2)
                {
                    maxx3=maxx2;
                    maxx2=sumi[i].val-a[sumi[i].id][sumj[j].id];
                }
                else if(sumi[i].val-a[sumi[i].id][sumj[j].id]>=maxx3)
                    maxx3=sumi[i].val-a[sumi[i].id][sumj[j].id];
            }
            ans4=max(ans4,sumj[j].val+maxx1+maxx2+maxx3);
        }
        if(n<m)
        {
            for(int i=1;i<n;i++)
            {
                for(int j=i+1;j<=n;j++)
                {
                    int maxx1=0,maxx2=0;
                    for(int k=1;k<=m;k++)
                    {
                        if(sumj[k].val-a[sumi[i].id][sumj[k].id]-a[sumi[j].id][sumj[k].id]>=maxx1)
                        {
                            maxx2=maxx1;
                            maxx1=sumj[k].val-a[sumi[i].id][sumj[k].id]-a[sumi[j].id][sumj[k].id];
                        }
                        else if(sumj[k].val-a[sumi[i].id][sumj[k].id]-a[sumi[j].id][sumj[k].id]>=maxx2)
                            maxx2=sumj[k].val-a[sumi[i].id][sumj[k].id]-a[sumi[j].id][sumj[k].id];
                    }
                    ans5=max(ans5,sumi[i].val+sumi[j].val+maxx1+maxx2);
                }
            }
        }
        else
        {
            for(int i=1;i<m;i++)
            {
                for(int j=i+1;j<=m;j++)
                {
                    int maxx1=0,maxx2=0;
                    for(int k=1;k<=n;k++)
                    {
                        if(sumi[k].val-a[sumi[k].id][sumj[i].id]-a[sumi[k].id][sumj[j].id]>=maxx1)
                        {
                            maxx2=maxx1;
                            maxx1=sumi[k].val-a[sumi[k].id][sumj[i].id]-a[sumi[k].id][sumj[j].id];
                        }
                        else if(sumi[k].val-a[sumi[k].id][sumj[i].id]-a[sumi[k].id][sumj[j].id]>=maxx2)
                            maxx2=sumi[k].val-a[sumi[k].id][sumj[i].id]-a[sumi[k].id][sumj[j].id];
                    }
                    ans5=max(ans5,sumj[i].val+sumj[j].val+maxx1+maxx2);
                }
            }
        }
        cout<<max(max(max(ans1,ans2),max(ans3,ans4)),ans5)<<'\n';
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：DYYqwq (赞：0)

简单题啊。

首先注意到 $n \times m \leq 10^5$，想到和根号相关算法。不妨限定 $n \leq \sqrt{10^5}$（否则行列反转）。

考虑收割 $4$ 个行或列有什么情况。

- 都是行
- 三行一列
- 两行两列
- 一行三列
- 都是列

第一种不用说，直接找 $O(n)$。

第二种直接找一列和所有行最大三行。$O(nm)$。

第三种固定两行（一定要是行，是那个 $n \leq \sqrt{10^5}$ 的行），然后找所有列中最大两个。$O(n^2m)$。

第四种同第二种。$O(nm)$。

第五种同第一种。$O(m)$。

都算一遍取 $\max$ 即可。复杂度 $O(n^2m+2nm+n+m)$。由于 $n \leq \sqrt{10^5}$，完全可以通过。

注意特判 $n \leq 4$ 或 $m \leq 4$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n , m , a[100010] , sum1[100010] , sum2[100010] , b[100010] , tmp[100010];

// 计算每行和每列的总和
//void calc1(int n , int m) {for(int i = 1 ; i <= n ; i ++) for(int j = 1 ; j <= m ; j ++) ;}

// 计算前 k 大元素的和
int calc2(int sz , int k , bool op)
{
    for(int i = 1 ; i <= sz ; i ++) tmp[i] = (op ? sum1[i] : sum2[i]);
    sort(tmp + 1 , tmp + sz + 1 , greater<int>());
    int sum = 0;
    for(int i = 1 ; i <= k ; i ++) sum += tmp[i];
    return sum;
}

// 计算去掉某一行或某一列后，选取三个最大列和或行的和
int calc3(int n , int m , bool op)
{
    int ans = 0;
    if(op)
	{
        for(int i = 1 ; i <= n ; i ++)
		{
            int mx1 = 0 , mx2 = 0 , mx3 = 0;
            for(int j = 1 ; j <= m ; j ++)
			{
                int qwq = sum2[j] - a[(i - 1) * m + j];
                if(qwq > mx1) mx3 = mx2 , mx2 = mx1 , mx1 = qwq;
                else if(qwq > mx2) mx3 = mx2 , mx2 = qwq;
                else if(qwq > mx3) mx3 = qwq;
            }
            ans = max(ans , mx1 + mx2 + mx3 + sum1[i]);
        }
    }
	else
	{
        for(int j = 1 ; j <= m ; j ++)
		{
            int mx1 = 0 , mx2 = 0 , mx3 = 0;
            for(int i = 1 ; i <= n ; i ++)
			{
                int qwq = sum1[i] - a[(i - 1) * m + j];
                if(qwq > mx1) mx3 = mx2 , mx2 = mx1 , mx1 = qwq;
                else if(qwq > mx2) mx3 = mx2 , mx2 = qwq;
                else if(qwq > mx3) mx3 = qwq;
            }
            ans = max(ans , mx1 + mx2 + mx3 + sum2[j]);
        }
    }
    return ans;
}

// 计算去掉两行后，选取两个最大列的和
int calc4(int n , int m)
{
    int ans = 0;
    for(int i = 1 ; i < n ; i ++)
	{
        for(int j = i + 1 ; j <= n ; j ++)
		{
            int mx1 = 0 , mx2 = 0;
            for(int k = 1 ; k <= m ; k ++)
			{
                int qwq = sum2[k] - a[(i - 1) * m + k] - a[(j - 1) * m + k];
                if(qwq > mx1) mx2 = mx1 , mx1 = qwq;
                else if(qwq > mx2) mx2 = qwq;
            }
            ans = max(ans , mx1 + mx2 + sum1[i] + sum1[j]);
        }
    }
    return ans;
}

signed main()
{
    scanf("%lld%lld" , &n , &m);
    int qwqans = 0;
	for(int i = 1 ; i <= n ; i ++) for(int j = 1 ; j <= m ; j ++) scanf("%lld" , &a[(i - 1) * m + j]) , qwqans += a[(i - 1) * m + j] , sum1[i] += a[(i - 1) * m + j] , sum2[j] += a[(i - 1) * m + j];
	if(n <= 4 || m <= 4) return printf("%lld" , qwqans) , 0; // 全都拿走。 
	
	// 计算每行和每列的总和
//    calc1(n , m);

    // 计算前 4 大行和的和
    int ans = calc2(n , 4 , true);
    // 计算前 4 大列和的和
    ans = max(ans , calc2(m , 4 , false));

    // 计算去掉某一行后，选取三个最大列和的和
    ans = max(ans , calc3(n , m , true));
    // 计算去掉某一列后，选取三个最大行和的和
    ans = max(ans , calc3(n , m , false));

    if(n > m)
	{
        // 交换矩阵的行和列
        for(int i = 1 ; i <= n ; i ++) for(int j = 1 ; j <= m ; j ++) b[(j - 1) * n + i] = a[(i - 1) * m + j];
        for(int i = 1 ; i <= m ; i ++) for(int j = 1 ; j <= n ; j ++) a[(i - 1) * n + j] = b[(i - 1) * n + j];
        swap(n , m);
        
		// 重新计算每行和每列的总和
//        calc1(n , m);
    }

    // 计算去掉两行后，选取两个最大列和的和
    ans = max(ans , calc4(n , m));
    printf("%lld" , ans);
    return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1219G Harvester](https://www.luogu.com.cn/problem/CF1219G)

# 解题思路

就是个嗯分讨题。

发现最终选择的方案总共就以下五种情况：

- 选 $4$ 行 $0$ 列。

- 选 $3$ 行 $1$ 列。

- 选 $2$ 行 $2$ 列。

- 选 $1$ 行 $3$ 列。

- 选 $0$ 行 $4$ 列。

对于第一，五种情况，直接取每行或每列的前四大值即可，时间复杂度 $O(n \log n)$。

对于第二，四种情况，直接枚举取的单独的一行或一列。然后取每行或每列的前三大值即可，注意要去重，时间复杂度 $O(nm \log n)$。

对于第三种情况，我们可以直接枚举取的那两行。然后取每列的前二大值即可，注意要去重，时间复杂度 $O(n^2m)$。

总时间复杂度 $O(n^2m)$，如果有 $n > m$,记得翻转矩阵，这样就会有 $n \le \sqrt{10^5}$，可以通过此题。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re int (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
ll n,m;
bool cmp(ll x,ll y){
    return x>y;
}
void solve()
{
    _clear();
    cin>>n>>m;
    ll c[n+5][m+5];
    ll a[min(n,m)+5][max(n,m)+5],b[m+5][n+5];
    ll ans=-1e18;
    forl(i,1,n)
        forl(j,1,m)
            cin>>c[i][j];
    if(n>m)
    {
        forl(i,1,n)
            forl(j,1,m)
                b[j][i]=c[i][j];
        swap(n,m);
        forl(i,1,n)
            forl(j,1,m)
                a[i][j]=b[i][j];
    }
    else
    {
        forl(i,1,n)
            forl(j,1,m)
                a[i][j]=c[i][j];
    }
    ll sumx[n+5]={},sumy[m+5]={},d[max(n,m)*2+5]={},k=0;
    forl(i,1,n)
        forl(j,1,m)
            sumx[i]+=a[i][j];
    forl(i,1,n)
        forl(j,1,m)
            sumy[j]+=a[i][j];
    k=0;
    forl(i,1,n)
        d[++k]=sumx[i];
    sort(d+1,d+1+k,cmp);
    Max(ans,d[1]+d[2]+d[3]+d[4]);
    forl(i,0,max(n,m)+4)
        d[i]=0;
    k=0;
    forl(i,1,m)
        d[++k]=sumy[i];
    sort(d+1,d+1+k,cmp);
    Max(ans,d[1]+d[2]+d[3]+d[4]);
    forl(i,0,max(n,m)+4)
        d[i]=0;

    forl(i,1,n)
    {
        forl(j,0,k+4)
            d[j]=0;
        k=0;
        forl(j,1,m)
            d[++k]=sumy[j]-a[i][j];
        sort(d+1,d+1+k,cmp);
        Max(ans,sumx[i]+d[1]+d[2]+d[3]); 
    }
    k=0;
    forl(i,0,max(n,m)+4)
        d[i]=0;

    forl(i,1,m)
    {
        forl(j,0,k+4)
            d[j]=0;
        k=0;
        forl(j,1,n)
            d[++k]=sumx[j]-a[j][i];
        sort(d+1,d+1+k,cmp);
        Max(ans,sumy[i]+d[1]+d[2]+d[3]); 
    }
    k=0;
    forl(i,0,max(n,m)+4)
        d[i]=0;   

    forl(i,1,n)
        forl(j,i+1,n)
        {
            ll maxn1=0,maxn2=0;
            forl(l,0,k+4)
                d[l]=0;
            k=0;
            forl(l,1,m)
            {
                ll num=sumy[l]-a[i][l]-a[j][l];
                if(maxn1==0)
                    maxn1=num;
                else if(maxn2==0)
                {
                    maxn2=num;
                    if(maxn1<maxn2)
                        swap(maxn1,maxn2);
                }
                else
                {
                    if(num>=maxn1)
                        maxn2=maxn1,maxn1=num;
                    else if(num>=maxn2)
                        maxn2=num;
                }
            }
            Max(ans,sumx[i]+sumx[j]+maxn1+maxn2);
        }
    cout<<ans<<endl;
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
//    cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：_edge_ (赞：0)

分类讨论题，要有点耐心调题和分类。

可以分成好几种情况，这里只对行进行讨论，列的话就翻转一下即可。

请看清楚题目的数据范围，可以认为 $n,m \le 300$。(雾

1. 选四个行

那想都不用想选四个最大总和的行就可以了。

复杂度 $O(n \log n)$。

1. 选一个行三个列

这个时候，我们需要去枚举这个行，然后对于列的总和进行维护，最后取出三个最大的即可。

复杂度 $O(nm \log m)$。

1. 选两个行两个列

我们发现，这个时候暴力枚举好像会 TLE，但事实上并没有，因为 $n$ 和 $m$ 最小的那个肯定是不超过 $\sqrt n$ 的，因此，如果遇到了 $n>m$ 的情况，就交换一下，然后枚举两个行，去确定一下那两个列。

如果实现不好的话就会变成 $O(n^2m \log m)$，这个复杂度是通过不了这道题目的，考虑我们本质上就是寻找最大值和次大值，可以 $O(1)$ 进行维护。

```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#define int long long 
#define pb push_back 
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
using namespace std;
const int INF=1e5+5;
int n,m,ans[INF],ans1;
vector <int> a[INF],sum[INF],sum1[INF];
bool cmp(int x,int y) {return x>y;}
signed main()
{
	n=read();m=read();
	for (int i=0;i<=n;i++) 
		for (int j=0;j<=m+1;j++) 
			a[i].pb(0),sum[i].pb(0),sum1[i].pb(0);
//	cout<<sum[1]<<" jaier\n"; 
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			a[i][j]=read();
			sum1[i][j]=sum1[i-1][j]+a[i][j];
			sum[i][j]=sum[i][j-1]+a[i][j];
			
		}
	for (int i=1;i<=m;i++) 
		ans[i]=sum1[n][i];
	sort(ans+1,ans+1+m,cmp);
	int res=0;
	for (int i=1;i<=min(m,4ll);i++)
		res+=ans[i];
	ans1=max(ans1,res);
	// 四行
	for (int i=1;i<=n;i++) 
		ans[i]=sum[i][m];
	sort(ans+1,ans+1+n,cmp);
	res=0;
	for (int i=1;i<=min(n,4ll);i++)
		res+=ans[i];
	ans1=max(ans1,res);
	// 四列
	
	// 一行三列
	for (int i=1;i<=n;i++) {
		int res=0;
		for (int j=1;j<=m;j++) { 
			sum1[n][j]-=a[i][j],res+=a[i][j];
		} 
		for (int j=1;j<=m;j++) {
			ans[j]=sum1[n][j];
		}
		sort(ans+1,ans+1+m,cmp);
		for (int j=1;j<=min(m,3ll);j++)
			res+=ans[j];
		ans1=max(ans1,res);
		for (int j=1;j<=m;j++)
			sum1[n][j]+=a[i][j];
//		cout<<res<<" "<<i<<" "<<<"\n";
	}
	
	// 一列三行 
	for (int i=1;i<=m;i++) {
		int res=0;
		for (int j=1;j<=n;j++)
			sum[j][m]-=a[j][i],res+=a[j][i];
		for (int j=1;j<=n;j++) 
			ans[j]=sum[j][m];
		sort(ans+1,ans+1+n,cmp);
		for (int j=1;j<=min(n,3ll);j++)
			res+=ans[j];
		ans1=max(ans1,res);
		for (int j=1;j<=n;j++)
			sum[j][m]+=a[j][i];
	}
	// 两行两列
	if (n<=m) {
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) {
				if (i==j) continue;
				int res=0;
				for (int k=1;k<=m;k++)
					sum1[n][k]-=a[i][k]+a[j][k],res+=a[i][k]+a[j][k];
				int Max=0,Max1=0;
				for (int k=1;k<=m;k++) { 
					ans[k]=sum1[n][k];
					if (ans[k]>Max) Max1=Max,Max=ans[k];
					else if (ans[k]>Max1) Max1=ans[k];
				}
				if (m>=2) res+=Max+Max1;
				else res+=Max;
				ans1=max(ans1,res);
				for (int k=1;k<=m;k++)
					sum1[n][k]+=a[i][k]+a[j][k];
			}
	}
	else {
		for (int i=1;i<=m;i++)
			for (int j=1;j<=m;j++) {
				if (i==j) continue;
				int res=0;
				for (int k=1;k<=n;k++)
					sum[k][m]-=a[k][i]+a[k][j],res+=a[k][i]+a[k][j];
				int Max=0,Max1=0;
				for (int k=1;k<=n;k++) {
					ans[k]=sum[k][m];
					if (ans[k]>Max) Max1=Max,Max=ans[k];
					else if (ans[k]>Max1) Max1=ans[k];
				}
				if (n>=2) res+=Max+Max1;
				else res+=Max;
				ans1=max(ans1,res);
				for (int k=1;k<=n;k++)
					sum[k][m]+=a[k][i]+a[k][j];
			}
	}
	cout<<ans1<<"\n";
	return 0;
}
```


---

