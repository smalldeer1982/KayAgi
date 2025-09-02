# Ferry Loading II

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1381

[PDF](https://uva.onlinejudge.org/external/104/p10440.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10440/62f4e72b9730523fdb77b04f21f28f29a3eff81d.png)

## 样例 #1

### 输入

```
2
2 10 10
0
10
20
30
40
50
60
70
80
90
2 10 3
10
30
40```

### 输出

```
100 5
50 2```

# 题解

## 作者：Steadywelkin (赞：2)

看到了题解中有动态规划的做法，这里给出一个贪心的思路。

首先我们一定不会让这一边的车的数量超出了船的限重才开始运送，因为这样造成了更多的车的等待。而且由于不管船上有多少辆车，来回的运送时间是一定的，所以我们要考虑的是什么时候开始运输未过河的车以达到最大的运输效率。

考虑贪心，我们在每一次这边车的数量到达船的限重时就将这边岸上的所有船都运送到对岸，实现对船的运输效率的最大化。同时我们还要考虑车的数量不被船的载重整除的情况，我们会把这种情况放在最开始就解决。

我们的目的是让所有车都过岸，实际上就是求出最晚到达的车的过岸时间，如果我们将剩余的车都放在最后，与将剩余的车放在最开始的区别在于，放在一开始时在过岸过程中有车辆到来，这一段时间里同时完成了车的积累，而放在最后就不会有车到来，浪费了这一段时间。

注意细节：在最后一次运输的过程中不需要考虑返回时间，所以在最后要减去。同时还要考虑船返回到达的时间与到达限重的最后一辆车到达的时间要取最大值。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;

const int mod=1e9+7;
const int N=1e4+5;
int n,t,m,a[N];

inline int read()
{
	int a=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())
		a=(a<<3)+(a<<1)+ch-'0';
	return a*f;
}

inline int solve(int n,int t,int m)
{
	int k=m%n,ans=0,sum=0;
	for(int i=1;i<=m;i++)
		a[i]=read();
	sort(a+1,a+m+1);
	for(int i=1;i<=k;i++)
		ans=max(ans,a[i]);
	if(k) ans+=t*2;
	for(int i=1;i<=m/n;i++)
	{
		for(int j=k+(i-1)*n;j<=k+i*n;j++)
			sum=max(sum,a[j]);
		ans=max(ans,sum)+2*t;
	}
	return ans-t;
}

signed main()
{
	int T=read();
	while(T--)
	{
		n=read(),t=read(),m=read();
		printf("%d %d\n",solve(n,t,m),m%n==0?m/n:m/n+1);
	}
	return 0;
}

```


---

## 作者：multiverse_ (赞：2)

//定义：
int f[1510];//第i辆车到达对岸的时间
int d[1510];//到第i辆车及以前的运送次数
int a[1510];//第i辆车到达岸边的时间 

//初始化：
//最先开始每辆车的到达对岸的时间为正无穷大
//f[0]=-t; 

//动态转移方程：
//f[i]=min(f[i],max(f[j]+t,a[i])+t); 
//f[j]为第j辆车到对岸的时间
//f[j]+t为送第j辆车的那趟船回来的时间
//以等它前面的车的那趟开回来和它到达的时间
//中的最大值作为开船时间
//再加上过去的时间t 
//在与之前求出的到达时间取最小值

//答案：
//f[n](第n辆车到达对岸的最小时间） 

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1510];//第i辆车到达对岸的时间
int d[1510];//到第i辆车及以前的运送次数
int a[1510];//第i辆车到达岸边的时间 
int m,t,n,k;
int main(){
//	freopen("ferry.in","r",stdin);
//	freopen("ferry.out","w",stdout);
	cin>>k;
	for(int i=1;i<=k;i++){		
		cin>>m>>t>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			f[i]=INT_MAX;
			d[i]=0;//初始化 
		}
		f[0]=-t;
		for(int i=1;i<=n;i++){
			for(int j=max(0,i-m);j<=i-1;j++){
				int w=f[i];
				 f[i]=min(f[i],max(f[j]+t,a[i])+t);
				if(f[i]!=w)d[i]=d[j]+1;
			}
		}
		cout<<f[n]<<" "<<d[n]<<endl;
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}


```

---

