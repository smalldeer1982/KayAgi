# [ABC076D] AtCoder Express

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc076/tasks/abc076_d

$ 2168 $年、AtCoder 社は成長し、ついに "AtCoder特急" という鉄道を建設することを決めた。

さて、社長の高橋君は、"AtCoder特急" の列車を以下のように運行することを計画した。

- 列車の走行時間は、$ (t_1\ +\ t_2\ +\ t_3\ +\ ...\ +\ t_N) $ 秒である。
- 最初の $ t_1 $ 秒間は、列車は速度 $ v_1 $ m/s 以内で走っていなければならない。また、次の $ t_2 $ 秒間は、列車は速度 $ v_2 $ m/s 以内で走っていなければならない。 次の $ t_3 $ 秒間、またそれ以降についても同様である。
- 最後の $ t_N $ 秒間は、列車は速度 $ v_N $ m/s 以内で走っていなければならない。

ただし、列車の性能上、加速度は ±$ 1m/s^2 $ 以内でなければならない。また、走行開始時と走行終了時には列車は止まっていなければならない。

列車が発車してから停車するまでに走れる最大の距離を求めなさい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ t_i\ \leq\ 200 $
- $ 1\ \leq\ v_i\ \leq\ 100 $
- 入力はすべて整数である

### Sample Explanation 1

![](https://img.atcoder.jp/abc076/69c1f4241b608bc36f1f08dd4184d3f0.png) - 最初の $ 30 $ 秒は、加速度を $ 1m/s^2 $ にし、加速します。その間に列車は $ 450m $ 走ります。 - 次の $ 40 $ 秒は、速度 $ 30m/s $ を保ちます。その間に列車は $ 1200m $ 走ります。 - 最後の $ 30 $ 秒は、加速度を $ -1m/s^2 $ にし、減速します。その間に列車は $ 450m $ 走ります。 合計で、$ 450 $ + $ 1200 $ + $ 450 $ = $ 2100m $ 走ることができます。

### Sample Explanation 2

![](https://img.atcoder.jp/abc076/a3e07ea723f50df04461165bc2cc8890.png) - 最初の $ 34 $ 秒は、加速度を $ 1m/s^2 $ にし、加速します。その間に列車は $ 578m $ 走ります。 - 次の $ 26 $ 秒は、速度 $ 34m/s $ を保ちます。その間に列車は $ 884m $ 走ります。 - 次の $ 4 $ 秒は、加速度を $ 1m/s^2 $ にし、加速します。その間に列車は $ 144m $ 走ります。 - 次の $ 8 $ 秒は、速度 $ 38m/s $ を保ちます。その間は列車は $ 304m $ 走ります。 - 最後の $ 38 $ 秒は、加速度を $ -1m/s^2 $ にし、減速します。その間に列車は $ 722m $ 走ります。 合計で、$ 578 $ + $ 884 $ + $ 144 $ + $ 304 $ + $ 722 $ = $ 2632m $ 走ることができます。

### Sample Explanation 3

![](https://img.atcoder.jp/abc076/77f821f590cb19d8e449303a102422dc.png) - 最初の $ 6 $ 秒は、加速度を $ 1m/s^2 $ にし、加速します。その間に列車は $ 18m $ 走ります。 - 次の $ 2 $ 秒は、速度 $ 6m/s $ を保ちます。その間に列車は $ 12m $ 走ります。 - 次の $ 4 $ 秒は、加速度を $ -1m/s^2 $ にし、減速します。その間に列車は $ 16m $ 走ります。 - 次の $ 14 $ 秒は、速度 $ 2m/s $ を保ちます。その間は列車は $ 28m $ 走ります。 - 最後の $ 2 $ 秒は、加速度を $ -1m/s^2 $ にし、減速します。その間に列車は $ 2m $ 走ります。 合計で、$ 18 $ + $ 12 $ + $ 16 $ + $ 28 $ + $ 2 $ = $ 76m $ 走ることができます。

### Sample Explanation 4

![ ](https://img.atcoder.jp/abc076/ebde8cbeb649ae7fd338180c0562ae0b.png) - 最初の $ 4.5 $ 秒は、加速度を $ 1m/s^2 $ にし、加速します。その間に列車は $ 10.125m $ 走ります。 - 最後の $ 4.5 $ 秒は、加速度を $ -1m/s^2 $ にし、減速します。その間に列車は $ 10.125m $ 走ります。 合計で、$ 10.125 $ + $ 10.125 $ = $ 20.25m $ 走ることができます。

## 样例 #1

### 输入

```
1
100
30```

### 输出

```
2100.000000000000000```

## 样例 #2

### 输入

```
2
60 50
34 38```

### 输出

```
2632.000000000000000```

## 样例 #3

### 输入

```
3
12 14 2
6 2 7```

### 输出

```
76.000000000000000```

## 样例 #4

### 输入

```
1
9
10```

### 输出

```
20.250000000000000000```

## 样例 #5

### 输入

```
10
64 55 27 35 76 119 7 18 49 100
29 19 31 39 27 48 41 87 55 70```

### 输出

```
20291.000000000000```

# 题解

## 作者：fly20040720 (赞：4)

题意：	有一列车，要行使n个区间，第i个区间有ti秒，限速vi，开始和结束时速度必须是0，加速度的绝对值不能超过(1m/s)/s。问最多能走多远。

我们从简单的情况开始考虑。先假设只有一个限制条件，为在l~r内最快v，则最大速度S关于时间t的函数如下：

- S=v+l-t (0<=t<=l)
- S=v     (l<t<r)
- S=v+t-r (r<=t<=T)

现在我们加进去所有限制条件。同时，把初始和结束为0当成限制条件加入。这样可以在O(NT)时间确定所有区间的最大值。然后当成梯形求面积即可。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

int t[200],v[200],l[200],r[200],pt[200],d[50000];
	
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>t[i];
		t[i]*=2;
		pt[i]=pt[i-1]+t[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>v[i];
		v[i]*=2;
		l[i]=min(l[i-1],v[i]-pt[i]);
	}
	r[n]=0;
	for(int i=n-1;i>=0;i--)
		r[i]=min(r[i+1], v[i+1]-(pt[n]-pt[i]));
	for(int i=1;i<=n;i++)
		for(int j=pt[i-1];j<=pt[i];j++)
		{
			d[j]=min(l[i-1]+j, r[i]+(pt[n]-j));
			d[j]=min(d[j], v[i]);
		}
	double ans=0;
	for(int i=0;i<pt[n];i++)
		ans+=d[i]+d[i+1];
	printf("%.15f\n",ans/8.0);
}
```

---

## 作者：roger_yrj (赞：1)

通过观察可以发现，加速度只可能是 $+1,0,-1$ 中的一种。

我们考虑 DP：$f_{i,j}$ 表示当前在时间 $i$，速度为 $j$ 的最大路程。从 $f_{i,j-1/j/j+1}$ 转移即可。

但是时间和速度可能为小数怎么办呢？把速度和时间都 $\times 2$ 就行了。$f$ 的值同理。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=210,T=4e4+10;
int n,f[T][N],v[T],t,L[N],R[N];
int main(){
	memset(v,0x3f,sizeof(v));
	cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		L[i]=2*t,R[i]=2*t+2*x;
		t+=x;
	}
	for(int i=1,y;i<=n;i++){
		cin>>y;
		for(int j=L[i];j<=R[i];j++)v[j]=min(v[j],y*2);//暴力处理每个时间点的限速 
	}
	memset(f,-0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=2*t;i++){//DP 
		for(int j=0;j<=v[i];j++){
			if(j>0)f[i][j]=max(f[i][j],f[i-1][j-1]+2*j-1);
			f[i][j]=max(f[i][j],f[i-1][j+1]+2*j+1);
			f[i][j]=max(f[i][j],f[i-1][j]+2*j);
		}
	}
	printf("%.15f",f[2*t][0]/8.0);
}
```

---

## 作者：aCssen (赞：0)

### Solution

提供另一种状态设计的方法。

考虑把每个时间段看做一个整体考虑，然后我们关注的是这段走完时的速度。所以设 $f_{i,j}$ 表示走完了前 $i$ 段，且走出第 $i$ 段的速度是 $j$ 的答案。

转移考虑枚举一个 $k$，表示上一段的速度，现在我们要从 $f_{i-1,k}$ 转移到 $f_{i,j}$，也就是要把速度从 $k$ 转到 $j$。

有一个大致的流程，就是整段运动的过程一定是加速 $\to$ 匀速 $\to$ 减速的过程，匀速是因为碰到了速度限制，减速是因为最后要达到 $j$。同时因为位移 $s=v_0t+\frac{1}{2}at^2$，先减速会使 $v_0$ 变小，肯定不优。同时也知道了，$a$ 一定会取到边界，因为匀速时的位移才是最大的，所以要尽快达到匀速，尽晚脱离匀速。

这样整个过程就很清晰，如果 $k<j$ 就会先加速到 $j$，如果 $k>j$ 最后会减速到 $j$。先把这一部分的量算出来，如果时间不够用就不合法；如果减速但是 $k$ 比当前的速度限制大，那么一定有一个位置是超了的，也不合法。否则就可以转移，考虑算出来能加速到多少。如果是加速就用 $j$，减速就用 $k$，因为整个过程是先加速的，加速的最大时间是总剩余的一半。如果不超速度限制就直接加速再减速，超了就加上一段匀速。

不能达到的状态不能赋成 $0$，要到 $-\infty$。时间复杂度 $\mathcal{O}(nv^2)$。

### Code

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
	template<typename T=int> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
double f[105][105];
int t[105],v[105];
double calc(double v0,double vt,double a){
	return (vt*vt-v0*v0)/(2*a);
}
int main(){
	int n=read();
	for(int i=1;i<=n;i++)
		for(int j=0;j<=100;j++) f[i][j]=-1e9;
	for(int i=1;i<=n;i++) t[i]=read();
	for(int i=1;i<=n;i++) v[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<=v[i];j++){
			for(int k=0;k<=v[i-1];k++){
				double Add=0;
				if(k<j){
					double rest=t[i]-(j-k);
					if(rest<0) continue;
					Add+=calc(k,j,1);
					double Ed=j+rest/2;
					if(Ed<=v[i]) Add+=2*calc(j,Ed,1);
					else Add+=(2*calc(j,v[i],1)+v[i]*(rest-2*(v[i]-j)));
				}
				if(k==j){
					double Ed=k+t[i]*0.5;
					if(Ed<=v[i]) Add+=2*calc(k,Ed,1);
					else Add+=(2*calc(k,v[i],1)+v[i]*(t[i]-2*(v[i]-k)));
				}
				if(k>j){
					double rest=t[i]-(k-j);
					if(rest<0||k>v[i]) continue;
					Add+=calc(k,j,-1);
					double Ed=k+rest/2;
					if(Ed<=v[i]) Add+=2*calc(k,Ed,1);
					else Add+=(2*calc(k,v[i],1)+v[i]*(rest-2*(v[i]-k)));
				}
				f[i][j]=max(f[i][j],f[i-1][k]+Add);
			}
		}
	}
	printf("%.12lf",f[n][0]);
	return 0;
}
```

---

