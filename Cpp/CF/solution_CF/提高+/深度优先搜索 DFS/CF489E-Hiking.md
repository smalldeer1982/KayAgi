# Hiking

## 题目描述

一个旅行者正在计划沿着河水进行一场水上远足。经过探测，他已经探明了这条河上适合晚上休息的 $n$ 个地点，记录了这些地点与出发点的距离。

每一个地点都有一个美丽度。对于第 $i$ 个地点，它和起点的距离为 $x_i$，它的美丽度为 $b_i$。

每一个地点都在出发点的下游，且这个旅行者在旅行的时候只会顺流而下。

简言之，我们可以把河流看成一个数轴，出发点的坐标是 $0$，第 $i$ 个地点的坐标是 $x_i$。旅行者只会沿正方向前进。

这个旅行者对他一天的前进距离设定了一个基准值 $l$，如果他某天的所前进的距离大于或小于了这个基准值，都会使他疲劳。假设他一天走了 $r_i$ 的距离，那么他产生的疲劳值为 $\sqrt{|r_j-l|}$，他整个旅程的总疲劳值为每一天的疲劳值之和。

显然，这个旅行者晚上需要休息，所以必须到达一个休息地点才能结束一天的行程，并在这个地点过夜。假设他当天晚上在第 $i$ 个地点休息，那么他当天的舒适度为这个地点的美丽度，即 $b_i$。他整个旅程的总舒适度是每一天（包括最后一天）的舒适度之和。

现在他希望你帮助他规划旅游路线，确定出每一天在哪个地点休息，他对旅游的天数没有要求，但是要求最后一天必须在第 $n$ 个地点休息。他希望你的这个规划足够合理，使得这次旅行的**总疲劳值除以总舒适度**的结果最小化。

## 说明/提示

### 样例解释
样例中总疲劳值除以总舒适度的最小值为 $\frac{1+1+\sqrt 2+0}{10+10+5+10}\approx0.097549$。

## 样例 #1

### 输入

```
5 9
10 10
20 10
30 1
31 5
40 10
```

### 输出

```
1 2 4 5 ```

# 题解

## 作者：George_Plover (赞：5)

### $2020\cdot FDUXCPC\cdot Spring-2-Problem H$
### 题意：
 
一个旅行者从一条数轴的$0$点出发旅行。数轴上一共有$n$个景点，每个景点坐标$x_i$不同，且按输入顺序递。同时每个景点有一个美丽度$b_i$。输入数据中还有一个用于计算疲劳度的值$l$.

旅行者会在每天从一个点出发，沿正方向前进到达一个景点，然后休息。规定，如果他从景点$u$到达$v$，那么他这天的疲劳度$f=\sqrt{\big|(x_v-x_u)-l\big|}$.同时这天他获得的满意度等于停留景点的美丽度。

现在需要你规划他的旅游日程，按顺序输出每天他停留的景点编号，这个旅游计划需要满足下面的条件：

* 最后必须以景点n结束

* 满足上述条件的情况下，最优化疲劳度之和与满意度之和的比率，即要求$\frac{\sum f_i}{\sum b_i}$尽可能小

### 算法：

#### 01分数规划+递推求最短路

令$\frac{\sum f_i}{\sum b_i}=\eta$

有$\sum f_i-\eta \sum b_i=0$

即$\sum(f_i-\eta b_i)=0$

接下来是01分数规划常用套路，二分$\eta$的值，对于一天的行程$u -> v$可以视为$(u,v)$之间有一条边权为$f_{(u,v)}-\eta b_v$ 的单向边。由于题目特点，转移边与景点共同构成一个DAG，直接递推求最短路，如果最段路的值大于0，则说明需要增大$\eta$，反之减少。

在每次求最短路的时候保留每个点的前置转移点，当$\eta$达到一定精度时，利用最后一次记录的前置转移点输出答案即可。

复杂度$O\big(n^2log(\sum f_i)\big)$

代码：（和描述的式子有些出入，但方法是一样的）

```cpp
#define George_Plover
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define LL long long
#define MAXN 1001

using namespace std;
int b[MAXN],loc[MAXN],n,m;
double dp[MAXN];
int pre[MAXN];
void out(int x);
bool check(double x)
{
    for(int i=1;i<=n;i++)
        dp[i]=1e19;
    dp[0]=0.00;
    
    for(int i=0;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            double tmp=dp[i]+sqrt(abs(loc[j]-loc[i]-m))*x-b[j];
            if(dp[j]>tmp)
            {
                dp[j]=tmp;
                pre[j]=i;
            }
        }
    }
    //out(n);
    //printf("\n");
    if(dp[n]<0)
        return 0;
    return 1;
}
void out(int x)
{
    if(!x)
        return;
    
    out(pre[x]);
    
    printf("%d ",x);
}
int main()
{
    scanf("%d%d",&n,&m);
    
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&loc[i],&b[i]);
    }
    double L=0,R=1e6;
    while(abs(L-R)>1e-9)
    {
        //cout<<L<<" "<<R<<endl;
        double mid=(L+R)/2.0;
        if(check(mid))
        {
            R=mid;
        }
        else
        {
            L=mid;
        }
    }
    //cout<<L<<endl;
    out(n);
    return 0;
}

```


---

## 作者：zhikong (赞：2)


### 题解
要让上下和比值最小，显然0/1分数规划。
设L为每次走的疲劳度，有
$$p={{\sum^{}_{}{L}} \over {\sum^{}_{}{b_i}}}$$

则
$${{\sum^{}_{}{(L-{p \times b_i)}}}}=0$$
然后二分p，求1到n的最短路，其中(u,v)之间有一条边权为$\sqrt {| (x_v-x_u)-l |}−{p \times b_v}$​ 的单向边，构成一个DAG求最短路。设$dp_i$为到i的最短距离递推可得，若值非负则增大p。
至于路径就在递推时记录一下前驱即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e6+5;
int n,L;
int pre[M];
double dp[M];
struct node{
	int x,y;
};
node a[M];
bool check(double mid){
	for(int i=1;i<=n;i++) dp[i]=1e19;
	dp[0]=0;
	for(int i=0;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			double tot=sqrt(abs(a[j].x-a[i].x-L))+dp[i]-a[j].y*mid;
			if(dp[j]>=tot){
				dp[j]=tot;
				pre[j]=i;
			}
		}
		
	}
	if(dp[n]>=0) return 1;
	else return 0;
}
void find(int z){
	if(!z) return;
	find(pre[z]);
	printf("%d ",z);
	return;
}
int main(){
	scanf("%d %d",&n,&L);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&a[i].x,&a[i].y);
	}
	double l=0,r=1e8,mid;
	while(abs(r-l)>1e-9){
		mid=(l+r)/2.0;
		if(!check(mid)) r=mid;
		else l=mid;
	}
	find(n); 
	return 0;
}
```


---

## 作者：绝顶我为峰 (赞：1)

这个式子的形式一看就是分数规划捏。

二分值 $mid$，记选出来的点下标为 $p_1,\cdots,p_m$ 如果可以取到则有 $\frac{\sum_{i=1}^m\sqrt{|l-x_{p_i}+x_{p_{i-1}}|}}{\sum_{i=1}^mc_{p_i}}\leq mid$，变形得到 $\sum_{i=1}^m(\sqrt{|l-x_{p_i}+x_{p_{i-1}}|}-c_{p_i}\times mid)\leq 0$。

这个式子是容易 dp 出来的，记 $dp_i$ 表示最后一次在 $i$ 过夜的最小值，转移直接枚举上一次过夜在哪里即可。

时间复杂度 $O(n^2\log V)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
int n,m,x[1001],val[1001],pre[1001];
double dp[1001];
inline bool check(double mid)
{
    for(int i=0;i<=n;++i)
    {
        dp[i]=1e9;
        pre[i]=0;
    }
    dp[0]=0.0000;
    for(int i=1;i<=n;++i)
        for(int j=0;j<i;++j)
        {
            double w=dp[j]+sqrt(abs(m-x[i]+x[j]))-val[i]*mid;
            if(w<dp[i])
            {
                dp[i]=w;
                pre[i]=j;
            }
        }
    return dp[n]<=0.000;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        cin>>x[i]>>val[i];
    double l=1e-6,r=1e6,mid;
    for(int i=1;i<=50;++i)
    {
        mid=(l+r)/2;
        if(check(mid))
            r=mid;
        else
            l=mid;
    }
    check(l);
    vector<int> v;
    for(int i=n;i;i=pre[i])
        v.emplace_back(i);
    reverse(v.begin(),v.end());
    for(auto i:v)
        cout<<i<<" ";
    cout<<'\n';
    return 0;
}
```

---

## 作者：luyan (赞：1)

# 题目

[题目链接](https://www.luogu.com.cn/problem/CF489E)

## 题目大意

一个数轴上有n个点，每个点的坐标均为正整数，每个点有一个美丽值。

给定常数p，从原点出发，只能向正方向移动，每次必须停在一个点上，假设经过的距离为d，那么这次hike的疲劳值为$\sqrt{abs(d-p)}$。现在要从原点前往最左端的点，求总疲劳值/总美丽值的最小值。

总美丽值为停留的点的美丽值之和。

# 题目分析

## 分数规划

注意到求两个和式的比值，并且以一个点为终点就要对疲劳值、美丽值都产生贡献。

所以可以考虑01分数规划

1.二分一个答案，然后令新点权为 上个点到这里的距离-二分答案*该点美丽值

2.dp求解判断是否合法

关于[01分数规划](https://blog.csdn.net/luyan0408/article/details/106750403)

## 动态规划

现在问题就转化为了在跳跃的过程中获得最小点权。

考虑最简单的动态规划：$dp[i]$表示到i号点的时候的最小点权。

那么$dp[i]=min(dp[k]+c[i])$

其中c表示点权，$k∈(1,i-1)$

# 代码

下附AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	char s;
	int x=0,f=1;
	s=getchar();
	while(s<'0'||s>'9'){
		if(s=='-')f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9'){
		x*=10;
		x+=s-'0';
		s=getchar();
	}
	return x*f;
}
const int N=1010;
int n,len;
int x[N],c[N];
double dp[N];
int pre[N];//记录答案路径 
bool check(double limit){
	for(int i=1;i<=n;i++){
		dp[i]=1e9;
		for(int j=0;j<i;j++){
			double tmp=dp[j]+sqrt(abs(len-(x[i]-x[j])))-limit*c[i];
			if(tmp<dp[i]){
				pre[i]=j;
				dp[i]=tmp;
			}
		}
	}
	return dp[n]>0;
}
int ans[N];
int main(){
	n=read(),len=read();
	for(int i=1;i<=n;i++){
		x[i]=read(),c[i]=read();
	}
	double l=0,r=1e10;
	while(r-l>1e-8){
		double mid=(l+r)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	check(l);
	int cnt=1;
	int id=n;
	while(id>0){
		ans[cnt++]=id;
		id=pre[id];
	}
	for(int i=cnt-1;i>0;i--){
		printf("%d ",ans[i]);
	}
}
```



---

## 作者：EricWan (赞：1)

又是一遍过的一题！[绿油油的评测记录](https://www.luogu.com.cn/record/120034386)

这篇题解应该成功写出了正常人的思维过程，中要的东西已经用 $\LaTeX$ 大字或 Markdown 加粗标出。

本题乍一看不可能有思路，但看数据范围发现需要的效率大概是比 $O(n^2)$ 大一点的，我们就考虑动态规划，可是有两个关键字而答案计算方式很奇怪，我们就不得不抛弃直接动规而选择先~~看题解~~推式子。

假设规定除了 $0$ 点我们经过的点编号为 $a_1,...,a_k$，而 $x_{a_0}=0$，$a_k=n$，那么，答案 $ans$ 应为**满足**

$$\large{ans\ge\frac{\sum_{i=1}^{k}\sqrt{\left|l-(x_i-x_{i-1})\right|}}{\sum_{i=1}^{k}b_i}}$$

**时的最小值**，因为 $k\le1$，$\sum_{i=1}^{k}b_i>0$，所以我们让等式两边同乘 $\sum_{i=1}^{k}b_i$ 后得到：

$$\sum_{i=1}^{k}b_i\times ans\ge\sum_{i=1}^{k}\sqrt{\left|l-(x_i-x_{i-1})\right|}$$

$$\large{0\ge\sum_{i=1}^{k}\Big(\sqrt{\left|l-(x_i-x_{i-1})\right|}-b_i\times ans\Big)}$$

之后，我们发现答案有单调性，于是我们进行二分答案。

在二分时，我们的 check 函数就可以用 dp 了。

定义 $dp_i$ 为选择部分前 $i-1$ 个休息地点而且选择第 $i$ 个休息地点时（假设选择 $k$ 个）最小的 $\sum_{i=1}^{k}(\sqrt{\left|l-(x_i-x_{i-1})\right|}-b_i\times ans)$。

这里的 dp 我们可以对于每一个 $i$，在 $1,...,i-1$ 遍历，枚举上一个休息地点的左右可能情况，效率为 $O(n^2)$，外面套个二分，总体效率就是 $O(n^2\times\log_2(1000000\times\texttt{精度}))$

建议使用伟大的 `long double`。

贴一下本人 AC 代码：
```cpp
#include <bits/stdc++.h>
#define double long double
using namespace std;
int n, L, st[1005], x[1005], b[1005], pre[1005];
double l, r, mid, dp[1005];
bool check(double ans) {
	for (int i = 1; i <= n; i++) {
		dp[i] = 1e10;
		for (int j = 0; j < i; j++) { //上一个节点可能是 0~i-1
			if (dp[i] > dp[j] + sqrt(abs(L - (x[i] - x[j]))) - b[i] * ans) { //转移判断，竟然没有用 sqrtl 也过了
				dp[i] = dp[j] + sqrt(abs(L - (x[i] - x[j]))) - b[i] * ans; //转移
				pre[i] = j; //更新向前的伪指针
			}
		}
	}
	return dp[n] <= 0;
}
signed main() {
	cin >> n >> L; //输入
	for (int i = 1; i <= n; i++) //输入
		cin >> x[i] >> b[i]; //输入
	l = 0, r = 10000000;
	while (r - l > 0.0000001) { //快乐的实数二分模板
		mid = (r + l) / 2;
		if (check(mid)) r = mid;
		else l = mid;
	}
	check(l); //最后一遍计算，求出最终的 pre
	register signed x = n; //求答案用的临时变量
	while (x != 0) { //向前遍历求答案
		st[++st[0]] = x;
		x = pre[x];
	}
	for (int i = st[0]; i >= 1; i--) cout << st[i] << " "; //输出
	return 0;
}
```

---

## 作者：plafle (赞：1)

- # CF489E Hiking

  ## 1.[题目描述](https://www.luogu.com.cn/problem/CF489E)

  ## 2.解法

  ​	这是一道01分数规划题。这里也有一个技巧。如果一个题求的是一个分式的最值，那么就很有可能是用01分数规划了。

  ​	设第$i$天获得的舒适度为$f_i$，疲劳值为$t_i$，二分枚举一个最小的$mid$使得：
  $$
  \frac{\sum t_i}{\sum f_i} \le mid
  $$
  代数变换一下可得
  $$
  \sum (t_i - mid \cdot f_i) \leq 0
  $$
  

$$
\sum(mid \cdot f_i - t_i) \ge 0
$$

​		如果把每个地点看成一个点，从点$a$到点$b$连一条有向边表示可以从点$a$走向点$b$，因为旅行者只能顺流而下，所以可以构建出一个$DAG$。问题转化成从0号点走到$n$号点能否找到一条路径使得上面一个代数式成立。因为是在一个$DAG$上面找路径，自然想到$dp$。

​	设$f[k]$表示走到$k$号点时$\sum(mid \cdot f_i - t_i)$的最大值，那么显然有：
$$
f[k] = max(f[j] + mid \cdot f[k] - d(j,k)) (0\le j<k)
$$
​	其中$d(j,k)$表示$j$与$k$之间的距离。

​	最后看一下$f[n]$是否大于0即可。

​	至于要输出休息地点的问题，开个前趋数组记录一下即可。

​	最后不要忘了精度开得高一点，$1e-8$差不多。



## 3.Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

const int maxn = 1e6 + 5;
const double esp = 1e-10;
int n,d,x[maxn],b[maxn],qq[maxn]; //qq是前趋数组
bool used[maxn],vis[maxn];
double f[maxn];

double fabs(double x) {
	if (x < 0)
		return -x; else
		return x;
}

bool check(double m) {
	memset(vis,0,sizeof(vis));
	f[0] = 0;
	qq[1] = 0;
	for (int i=1; i<=n; i++) {
		f[i] = -1e9;
		for (int j=0; j<i; j++)
			if (f[j] + m * (double)b[i] - sqrt(fabs(x[i] - x[j] - d)) > f[i]) {
				f[i] = f[j] + m * (double)b[i] - sqrt(fabs(x[i] - x[j] - d));//dp
				qq[i] = j;
			}
	}
	
	
	if (f[n] >= 0) {
		int x = n;
		memset(used,0,sizeof(used));
		while (x) {
			used[x] = 1;
			x = qq[x];
		}
		return 1;
	} else
		return 0;
	
}

int main() {
	scanf("%d%d",&n,&d);
	for (int i=1; i<=n; i++)
		scanf("%d%d",&x[i],&b[i]);
	double l = 0,r = 1e9,mid;
	
	while (r - l > esp) {
		mid = (r + l) / 2;
		if (check(mid)) {
			r = mid;
		} else
			l = mid;
	}

	for (int i=1; i<=n; i++)
		if (used[i])
			printf("%d ",i);
	return 0;
}
```



---

## 作者：zyy121212 (赞：1)

# 作者：c_cl
原文：<https://blog.csdn.net/c_czl/article/details/77893469>
题意：

数轴上有n个点，每个点有个距离源点的距离xi和美观值bi  主人公站在源点，他希望每步步长len，但每一步必须落在n个点其中一个上，且行进方向唯一，走到点n后可以计算旅行的价值

对于所有走过的点i  val = sum( sqrt( abs(x[i]-x[i-1]-len) ) / b[i] )  目标val尽量小  打印路径方案

思路：

第一次做分数规划题  这题是比较典型的01规划

简单描述一下01规划  就是 ans = sum(ci* xi)/sum(di* xi) 其中xi为{0,1}

常规的解法是变形上述式子 F(ans) = sum(ci* xi) - sum(di* xi) * ans 这时我们将ans当成自变量  构造一个函数  容易发现F是单调的  那么就可以二分ans  将求解最值问题转换成判定可行性问题

对于本题  我们可以将val变形**val = sum(sqrt( abs(x[i]-x[i-1]-len))/sum(b[i])** 那么也可以构建F函数**F(val) = sum(sqrt( abs(x[i]-x[i-1]-len) ) - sum(b[i]) * val**这时我们发现这个表达式由于计算中存在i和i-1位置的联系所以不是那么简单  

但是也可以发现  我们将原本的除法式子变成了减法式子   _这就会出现承袭性！！_   我们可以利用dp计算状态之间的转移 **dp[i] = dp[j] + sqrt( abs(x[i]-x[j]-len ) - b[i] * val**(
~~真谛就是用dp[j]包含了F中的sum~~)

这时二分val是logn的  对于每次的val我们可以用n^2的dp进行判定


### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1010
 
int n, len;
int x[N], b[N];
int pre[N], out[N];
double dp[N];
 
bool yes(double ans) {
	for (int i = 1; i <= n; i++) {
		dp[i] = 1e30;
		for (int j = 0; j < i; j++) {
			double tmp = dp[j] + sqrt(1e-8 + abs(x[i] - x[j] - len))
					- ans * b[i];
			if (dp[i] > tmp) {
				dp[i] = tmp;
				pre[i] = j;
			}
		}
	}
	return dp[n] < 0;
}
 
int main() {
	scanf("%d%d", &n, &len);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &x[i], &b[i]);
	double l = 0, r = 1e10, mid;
	while (r - l > 1e-8) {
		mid = (l + r) / 2;
		if (yes(mid)) {
			r = mid;
		} else
			l = mid;
	}
	yes(l);
	len = 0;
	out[0] = n;
	while (pre[out[len]]) {
		out[len + 1] = pre[out[len]];
		len++;
	}
	for (int i = len; i >= 0; i--)
		printf("%d%s", out[i], (i == 0) ? "\n" : " ");
	return 0;
}
```



---

## 作者：NuoCarter (赞：1)

# CF489E Hiking 题解

形如
从$n$个物体中选出$k$个，求出：
$$
\frac{\Sigma_{i=1}^{k} a_i}{\Sigma_{i=1}^{k} b_i}(Min | Max)
$$
这样的问题，一般采用 01分数规划 解决。

如果你现在对于 01分数规划 一无所知的话，请去做几道板子题练练手。

回到这个题：

## 题意

有$n$个点，每一个点有一个权值$b_i$和一个值$x_i$

求出$\frac{\Sigma_{j=1}^{k} \sqrt{a_j-a_{j-1}-l}}{\Sigma_{j=1}^{k} b_j}(Min)$

看一看数据范围：

01分数规划 中的 二分答案 单独的复杂度为($log$ $V$)

算下来的话答案判定的复杂度是可以支持$O(n^2)$的

所以我考虑了递推或者说$DP$?

## 解题过程：

设此时我们要判定的为$mid$

我们设代价为$\Sigma_{i=1}^{k}{\sqrt{a_j-a_{j-1}-l}}-mid*\Sigma_{i=1}^{k}b[i]$）

再设$f[i][j]$为第$i$个营地到第$j$个营地的代价

定义一个数组$dp[i]$表示到达第$i$个营地的最小代价

那么转移方程可以推出是这样的：

``` cpp
f[i][j]=sqrt(fabs(a[i].x-a[j].x-l))-x*a[i].b;
//dp[i]=min(dp[i],f[i][j]+dp[j]);
if(dp[i]>f[i][j]+dp[j]){mypath[i]=j;dp[i]=f[i][j]+dp[j];}

```

因为要求限制了必须在$n$结束，所以我们只需要判定$dp[n]$是否$\leq0$就可以了。

二分答案的答案判定就是这样。

路径的记录也在下面的代码中

整个复杂度$O(n^2logn)$

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double l;
double eps=1e-10;

double f[1005][1005];

const int INF=0x3f3f3f3f;
double ud[1005];
struct node{
	double x,b;
}a[1005];
int mypath[1005];
inline bool check(double x){
	for(int i=1;i<=n;++i){ud[i]=INF;}
	ud[0]=0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<i;++j){
			f[i][j]=sqrt(fabs(a[i].x-a[j].x-l))-x*a[i].b;
			//ud[i]=min(ud[i],f[i][j]+ud[j]);
			if(ud[i]>f[i][j]+ud[j]){mypath[i]=j;ud[i]=f[i][j]+ud[j];}
		}
	}
	return ud[n]<=0;
}
int pre[1005];
inline void print(int x){
	if(!x){return;}
	print(mypath[x]);
	printf("%d ",x);
}
int main(){
	// freopen("hiking.in","r",stdin);
	// freopen("hiking.out","w",stdout);
	scanf("%d%lf",&n,&l);
	double L=0,R=0;
	double suma=0,sumb=0;
	for(int i=1;i<=n;++i){
		scanf("%lf%lf",&a[i].x,&a[i].b);
		suma+=a[i].x;
	}
	R=1e7;
	double mid,res;
	while(L+eps<R){
		mid=(L+R)/2.0;
		if(check(mid)){
			R=mid;
			res=mid;
		}
		else{L=mid;}
	}
	print(n);
	return 0;
}

```

---

