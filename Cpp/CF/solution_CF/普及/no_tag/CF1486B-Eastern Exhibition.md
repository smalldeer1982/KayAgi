# Eastern Exhibition

## 题目描述

You and your friends live in $ n $ houses. Each house is located on a 2D plane, in a point with integer coordinates. There might be different houses located in the same point. The mayor of the city is asking you for places for the building of the Eastern exhibition. You have to find the number of places (points with integer coordinates), so that the summary distance from all the houses to the exhibition is minimal. The exhibition can be built in the same point as some house. The distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ , where $ |x| $ is the absolute value of $ x $ .

## 说明/提示

Here are the images for the example test cases. Blue dots stand for the houses, green — possible positions for the exhibition.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/ef8e7107a46bf60bf70b2b89dad798828df776de.png)

First test case.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/3bfbc5c12bc5661837030d46309064e5728abb33.png)

Second test case. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/f4355abdf55b6e2aba57eaba9ac1bd5b3e9a9937.png)

Third test case. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/7ac3252595a464db25ea4d6a5a88bb674df5da85.png)

Fourth test case. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/2ad0e39ceaeb8df93cdbdc07468766d61acf71ed.png)

Fifth test case. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486B/bf530ae677a95adfe7eacb87263816efab51ccdb.png)

Sixth test case. Here both houses are located at $ (0, 0) $ .

## 样例 #1

### 输入

```
6
3
0 0
2 0
1 2
4
1 0
0 2
2 3
3 1
4
0 0
0 1
1 0
1 1
2
0 0
1 1
2
0 0
2 0
2
0 0
0 0```

### 输出

```
1
4
4
4
3
1```

# 题解

## 作者：pomelo_nene (赞：6)

考虑到 $x$ 和 $y$ 是两个互不影响的量。分开来考虑。

假设考虑第一维，降维抽象成一个数轴，上面有若干点。你需要选取一个点，使得所有点到这个点的距离和最小。求可以选取的点的范围。

这是一个初中常见的问题，主要是研究绝对值性质与几何结合所用。这里不拓展只给出结论。选取的范围是，如果 $n$ 是奇数，则为 $n$ 个点的中位数的对应点；否则为两个中位数形成的闭区间。

那么，这个问题就很显然易见了。如果 $n$ 是奇数，答案为 $1$；否则就将 $x,y$ 坐标分别排序，求其中位数选取的范围区间包含的整数点个数乘积之和。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL x[1005],y[1005],n;
int main(){
	LL T;
	scanf("%lld",&T);
	while(T-->0)
	{
		scanf("%lld",&n);
		for(LL i=1;i<=n;++i)	scanf("%lld %lld",&x[i],&y[i]);
		if(n&1)
		{
			puts("1");
			continue;
		}
		sort(x+1,x+1+n),sort(y+1,y+1+n);
		LL sx=x[n/2+1]-x[n/2]+1,sy=y[n/2+1]-y[n/2]+1;
		printf("%lld\n",sx*sy);
	}
	return 0;
}
```

---

## 作者：BrotherCall (赞：4)

## 一道 ~~初中数学题~~ 数论题
### 我们先尝试将二维转换为一维来理解：
![](https://cdn.luogu.com.cn/upload/image_hosting/dfnijmz4.png)

#### 如图：

在一个数轴上，存在 $a_1$ 和 $a_2$ 两点，问如何取一点 $x$ ，使 $x$ 到 $a_1$ 和 $a_2$ 的距离和最小？

由初中平面几何知识可知，当 $x$ 位于 $a_1$ 和 $a_2$ 之间时，任取一点都可使距离和最小。距离和最小值为 $|a_2 - a_1|$ 。

#### 简单说明一下结论的正确性：

如图的 $x_1$ 点，位于 $a_1$ 点的左侧。它与 $a_1$ 和 $a_2$ 两点的最小距离和为 $2|a_1 - x_1| + |a_2 - a_1|$ 。由于 $2|a_1 - x_1|$ 大于零，故 $x_1$ 点一定是比 $x$  劣的点。$x_2$ 点同理。

### 如果存在更多限制的点呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/34ggf60l.png)

#### 当存在偶数个的点的时候：

如图所示，我们就可以利用化归思想，两两分组。

将 $a_1$ 与 $a_4$ 分为一组，则最优的点应在 $a_1$ 与 $a_4$ 之间；

将 $a_2$ 与 $a_3$ 分为一组，则最优的点应在 $a_2$ 与 $a_3$ 之间。

两者取交集，则 $a_2$ 与 $a_3$ 之间为整体的最优解。

#### 当存在奇数个的点的时候：

可看作 $a_2$ 与 $a_3$ 点重合，则最优解即取最中间的点。

### 回到二维中理解：

#### 思路：

由于是求曼哈顿距离，所以横坐标与纵坐标是两个独立的区块，互不影响。所以我们选择将横坐标和纵坐标分别用数组记下，用一维的方式，求出它的最优区间。再用两变量记录每个坐标轴的答案，两答案相乘即可。

若该轴为偶数个数：则最优区间大小为 最中间两个数之差加一，即 $ans = x_{\frac{n}{2}+1} - x_{\frac{n}{2}} + 1$。

若该轴为奇数个数：则最优区间大小为 $1$ ，即 $ans = 1$。

#### 代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;

int T,n;
ll x[1010],y[1010],ans1,ans2,a,b;

int main(){
	cin>>T;
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&a,&b);
			x[i] = a;
			y[i] = b;
            //记录所有横坐标与纵坐标的位置
		}
		if(n & 1 == 1){  //如果n为奇数，则直接输出1
			cout<<1<<endl;
			continue;
		}
        //如果n为偶数，则分别计算两坐标轴答案，再相乘
		sort(x + 1,x + 1 + n);
		sort(y + 1,y + 1 + n);
		ans1 = x[n/2+1] - x[n/2] + 1;
		ans2 = y[n/2+1] - y[n/2] + 1;
		cout<<ans1 * ans2<<endl;
	}
	return 0;
}
```


---

## 作者：npqenqpve (赞：1)

#### 题意：

给你 $n$ 个坐标 $p_i$ （$i\leq n$），求满足到 $p_i$ 的曼哈顿距离之和最小的整点个数 。

#### 思路：

初中课本教过我们这个题目的弱化版：求到数轴上到 $n$ 个点距离之和最小的点的个数，当 $n$ 为奇数时只能取 $n$ 个数的中位数，偶数时可以取 $p_\frac{n}{2}$ 到 $p_{\frac{n}{2}+1}$ 之间的所有点，整点则共有 $p_{\frac{n}{2}+1}-p_\frac{n}{2}+1$ 个 （此时假设 $n$ 个点顺序排列）。

不妨把 $x_{p_i}$ 与 $y_{p_i}$ 分开在两个数轴上考虑，那么所选的点一定是满足到 $x_{p_i}$ 距离之和最小的点且到 $y_{p_i}$ 距离之和最小的点，显然这样的点在 $n$ 为奇数时只有 $1$ 个，$n$ 为偶数时有 $(x_{p_{\frac{n}{2}+1}}-x_{p_\frac{n}{2}}+1) \times (y_{p_{\frac{n}{2}+1}}-y_{p_\frac{n}{2}}+1)$ ，排序一下再统计即可。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long //No long long see your ancestor!!!
#define ull unsigned long long //Have long long see your ancestor!!!
#define ld long double //No long double see your ancestor!!!
using namespace std;
struct node
{
	int x,y;
}p[1005];
bool cmp1(node a,node b)
{
	return a.x<b.x;
}
bool cmp2(node a,node b)
{
	return a.y<b.y;
}
int main()
{
	int t;cin>>t;
	while(t--)
	{
		memset(p,0,sizeof(p));
		int n;cin>>n;
		for(int i=1;i<=n;i++) 
		{
			cin>>p[i].x>>p[i].y;
		}		
		ll ans=1;
		if(n%2==0)
		{
			sort(p+1,p+1+n,cmp1);
			ans*=p[n/2+1].x-p[n/2].x+1;
			// cout<<p[n/2+1].x-p[n/2].x+1<<"\n";
			sort(p+1,p+1+n,cmp2);
			ans*=p[n/2+1].y-p[n/2].y+1;
			// cout<<p[n/2+1].y-p[n/2].y+1<<"\n";
		}
		cout<<ans<<"\n";
	}
	// system("pause");
}
```



---

## 作者：Rolling_L (赞：1)

~~标题翻译：车万展览~~

回归正题，这题我们可以这样考虑：

首先，对于曼哈顿距离，我们可以将横坐标和纵坐标分开考虑，因为横纵坐标互不影响。

然后，我们就将问题转化为了一个一维问题：数轴上有 $n$ 个点，坐标分别为 $x_{1},x_{2},……,x_{n}$ ，求有多少个数 $x_{0}$ ，使 $\sum\limits_{i=1}^{n}\left|x_{0}-x_{i}\right|$ 最小。

对于这个问题，有一个显而易见的结论：

对于 $n$ 为奇数，$x_{0}$ 为中位数。

对于 $n$ 为偶数，$x_{0}$ 在 $x_{\frac{n}{2}}$ 和 $x_{\frac{n}{2}+1}$ 之间（含）。

简要说明一下（以 $n$ 为奇数为例）：

如果 $x_{0}$ 不是中位数，那么相对于中位数而言，至少有 $\frac{n+1}{2}$ 个数对距离和的贡献 $+1$ ，而至多有 $\frac{n-1}{2}$ 个数对距离和的贡献 $-1$ ，相对于中位数，距离之和变大了，矛盾！

其实对于偶数，情况是差不多的，相当于是中位数由单点 变成区间。

最后，由乘法原理，答案的点的个数为：

横坐标答案个数 $\times$ 纵坐标答案个数

最后放一下非常简洁的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x[1005];
long long y[1005];
int T;
int main(){
	cin>>T;
	while(T--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d",&x[i],&y[i]);
		}
		if(n%2){//n为奇数时答案为1*1=1
			printf("1\n");
			continue;
		}
		sort(x+1,x+n+1);
		sort(y+1,y+n+1);
		printf("%lld\n",(x[n/2+1]-x[n/2]+1ll)*(y[n/2+1]-y[n/2]+1ll));
	}
	return 0;
}
```


---

## 作者：miao5 (赞：1)

首先我们不难发现这题中的x轴和y轴是相互独立的，最后处理答案的时候乘起来就可以了。

之后我们考虑处理x轴和y轴的答案。

根据中位数的性质，我们可以发现如果 $n$ 是奇数，那么答案就是1 。

否则的话答案就是最中间那两个数的差加1 。

code：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n;
long long x[1005],y[1005];
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
		sort(x+1,x+n+1);
		sort(y+1,y+n+1);
		if(n%2==1) cout<<1<<endl;
		else cout<<(x[n/2+1]-x[n/2]+1)*(y[n/2+1]-y[n/2]+1)<<endl; 
	}
	return 0;
}
```

---

## 作者：Lizj (赞：0)

题面题意非常清晰，在此不再赘述。

由于每个点的 $x$ 坐标和 $y$ 坐标之间不会相互影响，所以将两坐标分别计算，最后再相乘求总数。

将两个维度为抽象为两个数轴，就可以将题意简化为求数轴中距离其余各点距离最近的点的数量。

接下来考虑如何求解新的问题，可以先从数轴上只有两个点的情况开始分析。当数轴上仅剩两个点时：

![数轴上仅剩两个点时](https://cdn.luogu.com.cn/upload/image_hosting/ubyjx9fk.png?x-oss-process=image)

此时有三种情况：

1. 点在 $A$ 点左侧

2. 点在 $A$、$B$ 点之间，此时距离为 $|A|-|B|$

3. 点在 $B$ 点右侧

显然，此时第二种情况为最短距离（其余情况距离为无穷大）。

数轴上有三个点时也同理，不同处在于中间的点，只有在中间的点上时距离最短。

所以只需要将点的每个维度进行升序排序，再计算，最后相乘即可。

由此我们推出了数轴上有奇数个点和偶数个点时的答案：

- 当数轴上有奇数个点时，答案为 $1$；

- 当数轴上有偶数个点时，答案为 $a_{\frac{n}{2}+1}-a_{\frac{n}{2}}+1$（$a$ 数组已进行升序排序）

由此，可以通过该题，时间复杂度约为 $O(n \log n)$：


```cpp
#include<bits/stdc++.h>
using namespace std;
int x[1010],y[1010];
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x[i]>>y[i];
		}
		if(n%2){
			cout<<1<<endl;
			continue;
		}
		sort(x+1,x+n+1);
		sort(y+1,y+n+1);
		long long ans1=x[n/2+1]-x[n/2]+1,ans2=y[n/2+1]-y[n/2]+1;
		cout<<(long long)(ans1*ans2*1ll)<<endl;
	}
	return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：0)

显然 $x$ 轴和 $y$ 轴情况独立，最后乘一下即可。

那么一维问题怎么处理呢？我们按照求中位数的方法，满足条件的点肯定在两个方向上都是中位数。

那么如果 $n$ 是奇数，答案是 $1$。

否则答案为最中间那两个的差加一。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[1005],b[1005];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i],&b[i]);
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);
		if(n%2==1)puts("1");
		else printf("%lld\n",(a[n/2+1]-a[n/2]+1)*(b[n/2+1]-b[n/2]+1)); 
	}
	return 0;
}

```

---

## 作者：11D_Beyonder (赞：0)

### Idea    
&emsp;&emsp;假设最后选定的坐标为 $(X,Y)$。设坐标 $x_i\le X$ 的个数有 $u$，而 $x_i>X$ 的坐标有 $v$，则 $X$ 产生的路程贡献为 $(uX-\sum\limits_{x_i\le X}x_i)+(\sum\limits_{x_i>X}x_i-vX)$；对于 $Y$ 的路程贡献，同理。从式中可以看出，$X$ 和 $Y$ 相互独立，互不产生影响。接下来只讨论 $X$ 的取值。  

&emsp;&emsp;考虑枚举 $u$，我们先将 $x$ 序列升序排列；枚举到 $x_i$ 时，对于 $x_i\sim x_{i+1}$ 种的任何 $X$ 值，都有 $u=i$ 且 $v=n-i$；令 $sum_i=\sum\limits_{j=1}^i x_j$，则 $X$ 产生的贡献为 $(2i-n)X+sum_n-2sum_i$，其中 $x_i\le X<x_{i+1}$。显然，对于 $2i-n<0$，$X=x_i$ 为最优；对于 $2i-n>0$，$X=x_{i+1}-1$ 为最优；对于 $2n-i=0$，$X$ 可取 $[x_i,x_{i+1}-1]$ 中的任意正整数。

&emsp;&emsp;用```unordered_map<long long,long long>```记录贡献为 $C$ 的 $X$ 的个数。

&emsp;&emsp;值得注意一些细节：若某一 $X$ 值已经被取过，不可重复计数，需要用```unordered_set```记录；考虑 $X=x_n$ 和 $X=x_1$ 的边界情况；一定要注意枚举到 $x_i$ 时 $X$ 的取值范围。

&emsp;&emsp;$Y$ 的计算与之同理。

&emsp;&emsp;假设 $X$ 产生的最小的路程贡献为 $C_{Xmin}$，同理可定义 $C_{Ymin}$；取到 $C_{Xmin}$ 的 $X$ 个数为 $c_x$，同理有 $c_y$；答案为 $c_x\times c_y$。

### Code
```cpp
/******************************************************************
Copyright: 11D_Beyonder All Rights Reserved
Author: 11D_Beyonder
Problem ID: CF14586B
Date: 2021 Mar. 3rd
Description: Construction
*******************************************************************/
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<unordered_set>
using namespace std;
typedef long long ll;
const int N=1003;
int _;
int n;
ll x[N],y[N];
//记录取到贡献C的坐标数
unordered_map<ll,ll>costNumX,costNumY;
//前缀和
ll sumX[N],sumY[N];
//记录取到某一值
unordered_set<int>visX,visY;
ll leastCostX,leastCostY;
int nx,ny;
int main(){
	for(cin>>_;_;_--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x[i]>>y[i];
		}
		//排序
		sort(x+1,x+1+n);
		sort(y+1,y+1+n);
		for(int i=1;i<=n;i++){
			//预处理前缀和
			sumX[i]=sumX[i-1]+x[i];
			sumY[i]=sumY[i-1]+y[i];
		}
		//清空
		costNumX.clear();
		visX.clear();
		costNumY.clear();
		visY.clear();
		for(int i=1;i<=n;i++){
			if(i>n-i){
				const ll X=x[i];
				const ll Y=y[i];
				const ll costX=(2*i-n)*X-2*sumX[i]+sumX[n];
				const ll costY=(2*i-n)*Y-2*sumY[i]+sumY[n];
				//检验X是否取到
				if(visX.find(X)==visX.end()){
					costNumX[costX]++;
					visX.insert(X);
				}
				if(visY.find(Y)==visY.end()){
					visY.insert(Y);
					costNumY[costY]++;
				}
			}else if(i<n-i){
				if(i<n){
					const ll X=max(x[i+1]-1,x[i]);
					const ll Y=max(y[i+1]-1,y[i]);
					const ll costX=(2*i-n)*X-2*sumX[i]+sumX[n];
					const ll costY=(2*i-n)*Y-2*sumY[i]+sumY[n];
					if(visX.find(X)==visX.end()){
						costNumX[costX]++;
						visX.insert(X);
					}
					if(visY.find(Y)==visY.end()){
						visY.insert(Y);
						costNumY[costY]++;
					}
				}else{
					const ll X=x[n];
					const ll Y=y[n];
					const ll costX=n*X-sumX[n];
					const ll costY=n*Y-sumY[n];
					if(visX.find(X)==visX.end()){
						costNumX[costX]++;
						visX.insert(X);
					}
					if(visY.find(Y)==visY.end()){
						visY.insert(Y);
						costNumY[costY]++;
					}
				}
			}else{
				const ll X=x[i];
				const ll Y=y[i];
				const ll costX=(2*i-n)*X-2*sumX[i]+sumX[n];
				const ll costY=(2*i-n)*Y-2*sumY[i]+sumY[n];
				if(i<n){
					//x[i]没有取过
					//那么x[i]~x[i+1]-1也没有取过
					if(visX.find(X)==visX.end()){
						costNumX[costX]+=max(x[i+1]-x[i],1ll);
						visX.insert(X);
					}else{
						costNumX[costX]+=max(x[i+1]-x[i]-1,0ll);
					}
					if(visY.find(Y)==visY.end()){
						visY.insert(Y);
						costNumY[costY]+=max(y[i+1]-y[i],1ll);
					}else{
						costNumY[costY]+=max(y[i+1]-y[i]-1,0ll);
					}
				}
			}
		}
		leastCostX=leastCostY=0x7f7f7f7f7f7f7f7f;
		for(auto& cX:costNumX){
			leastCostX=min(leastCostX,cX.first);
		}
		for(auto& cY:costNumY){
			leastCostY=min(leastCostY,cY.first);
		}
		//一定要开ll
		cout<<costNumX[leastCostX]*costNumY[leastCostY]<<endl;
	}
	return 0;
}
```

---

