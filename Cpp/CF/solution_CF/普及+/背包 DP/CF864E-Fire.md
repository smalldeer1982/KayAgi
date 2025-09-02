# Fire

## 题目描述

某人的房子着火了，他想从大火中带走价值总和尽量多的物品，每次他只能带走一个，分别给出挽救某物品需要的时间 $t$，该物品开始燃烧的时间 $d$（从 $d$ 时间开始就不能再挽救该物品了），该物品的价值 $p$。

## 样例 #1

### 输入

```
3
3 7 4
2 6 5
3 7 6
```

### 输出

```
11
2
2 3 
```

## 样例 #2

### 输入

```
2
5 6 1
3 3 5
```

### 输出

```
1
1
1 
```

# 题解

## 作者：Dfkuaid (赞：12)

# #1.0 简单分析

> 01背包的变式。约束条件由空间变为了时间，这里要注意到时间的一个特殊的性质：**具有顺序**。

首先，要进行一步很简单但很重要的步骤：**排序**。

那么为什么要排序呢？

~~显然。~~题目中给的顺序并不是时间顺序，而对于所有物品，我们应当先考虑烧毁时间较早的物品，原因很简单：每拯救一个物品需要消耗一定的时间。假如我们先考虑在时段 $0\sim t$ 拯救烧毁时间较后的物品 A，接着，我们在考虑烧毁时间较前的物品 B，但我们并不知道之前 A 物品具体是在什么时候拯救的，如果要枚举，显然数据量太大了。

假设我们有两个物品 A,B，A 比 B 先烧毁，那么如果我们先考虑 A 得到的结果，一定不会比先考虑 B 得到的结果差，毕竟我们可以通过一些手段放弃之前的选择，而且可以更好地记录每个物品选取的时间。



注意到，我们还需要输出路径，那么可以增设状态，保存前驱，然后递归地遍历。



**设计状态**：

- $f_{i,j}$ 表示当前考虑到第 $i$ 个物品，拯救出的最后一个物品的拯救结束时间为 $j$ 的最大收益。
- $g_{i,j}$  —— 第 $i-1$ 个物品时，拯救出的最后一个拯救结束时间为 $g_{i,j}$ 。

**状态转移**： 可以直接按 01 背包进行转移。



还有一点要注意：

这里的答案并不像普通的 01 背包一般是 $f_{n,T}$，而是 $f_{n,1}\sim f_{n,T}$ 中的最大值，原因也很简单：我们设计的状态中的 $j$ 是**拯救出的最后一个物品的拯救结束时间**，这个**最后一个物品**不一定是哪一个物品，自然会有不同的答案。



*具体实现请见代码及注释。*



# #2.0 代码实现

``` cpp
const int N = 110;
const int M = 2010;
const int INF = 0x3fffffff;

struct T{
    int t,d,p;
    int ind;
};T a[N];

int n,f[N][M],g[N][M],maxn = -INF,ans = -INF;
int list[N],cnt,ans2;

inline int cmp(const T &x,const T &y){
    return x.d < y.d;
}

inline int Max(const int &x,const int &y){
    return x > y ? x : y;
}

inline void Path(int k,int t){ //递归遍历方案，并数清个数
    if (k <= 0) return;
    Path(k - 1,g[k][t]);
    if (f[k][t] != f[k - 1][t]) //判断这个物品是否被选——f[i] 与 f[i-1] 是否相等
      list[++ cnt] = k;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        scanf("%d%d%d",&a[i].t,&a[i].d,&a[i].p);
        a[i].ind = i; 
    }
    sort(a + 1,a + 1 + n,cmp); //排序
    for (int i = 1;i <= n;i ++){
        for (int j = 1;j <= 2000;j ++) //继承
          f[i][j] = f[i - 1][j],g[i][j] = j;
        for (int j = a[i].d - 1;j >= a[i].t;j --)
          if (f[i][j] < f[i - 1][j - a[i].t] + a[i].p){ //更新
              f[i][j] = f[i - 1][j - a[i].t] + a[i].p;
              g[i][j] = j - a[i].t;
          }  
    }
    for (int j = 1;j <= 2000;j ++) //找到最大答案
      if (f[n][j] > ans) ans = f[n][j],ans2 = j;
    Path(n,ans2); //统计
    printf("%d\n%d\n",ans,cnt);
    for (int i = 1;i <= cnt;i ++)
      printf("%d ",a[list[i]].ind);
    return 0;
}

```



# END

希望能给您带来收获。



---

## 作者：IGA_Indigo (赞：9)

## 题意分析
这道题是明显的 01 背包题，$f$ 数组的 $2$ 个维度分别是挽救需要的时间 $t$，和价值 $p$，因为当前状态只与上一个状态有关，所以可以使用滚动数组优化。

这里也要注意有一个限制是物品开始燃烧的时间 $d$，因为从 $d$ 时间开始就不能再挽救该物品了，所以我们需要优先处理燃烧时间小的物品。

题目翻译得很到位，废话就不多说了，下面讲一下思路。

## 大体思路
因为我们要优先处理燃烧时间小的物品，我们需要对这几个物体的燃烧时间 $d$ 进行贪心的排序。

### 状态设置
$f[i][j]$ 表示前 $i$ 个物品，使用 $j$ 时间去挽救所能得到的最大值。

如果是滚动数组的话可以直接 $f[j]$ 表示使用 $j$ 时间去挽救所能得到的最大值。
### 状态转移方程
#### 不优化
$f[i][j]=\max(f[i−1][j],f[i−1][j−t _i]+p_i)$
#### 优化
$f[j]=\max(f[j],f[j-t[i]]+p[i])$
### 存储答案
对于输出第三行，我们要按带走顺序输出能带走的物品的编号，可以定义一个二维 vector 数组，在处理和输出的时候比队列栈啥的方便。
#### 输出答案
- 遍历整个 $f$ 数组，取最大值为可以带走的最大的价值总和。

- vector 的长度是能带走的物品的数量。

- 然后输出所有 vector 里的元素，是能带走的物品的编号（按带走顺序排序）。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int t,d,p,b;
}a[105];//用结构体储存物品的数据，b为物品的下标
int f[2005];//f数组应初始化为0
vector<int> q[2005];//二维vector存放答案
bool cmp(node aa,node bb){
	return aa.d<bb.d;
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].t>>a[i].d>>a[i].p;
		a[i].b=i;
	}
	sort(a+1,a+1+n,cmp);//按照d的大小从小到大排序
	for(int i=1;i<=n;i++){
		for(int j=a[i].d-1;j>=a[i].t;j--){
			if(f[j]<f[j-a[i].t]+a[i].p){//如果挽救了这个物品的价值更大
				f[j]=f[j-a[i].t]+a[i].p;//就挽救这个物品
				q[j]=q[j-a[i].t];//因为是以下标为‘j-a[i].t’为基础的增加物品，所以存储的物品编号就替换成q[j-a[i].t]存储的物品编号
				q[j].push_back(a[i].b);//然后再加上当前物品
			}
		}
	}
	int maxb=0;//maxb存的是能挽救的最大价值的下标
	int maxx=0;//maxx和存的是能挽救的最大价值
	for(int i=1;i<=2000;i++){
		if(maxx<f[i]){
			maxx=f[i];
			maxb=i;
		}
	}//求出maxx和它所对应的下标maxb
	int diao=q[maxb].size();//这是可挽救物品的数量
	cout<<maxx<<'\n'<<diao<<'\n';
	for(int i=0;i<diao;i++){
		cout<<q[maxb][i]<<" ";//输出挽救物品的编号
	}
	return 0;
} 
```
## THE END.

---

## 作者：Bitter_Tea (赞：6)

## $01背包$

本题是$01$背包的变形。

我们需要对$d_i$进行排序后跑$01$背包。

但是我们为什么要对$d_i$进行排序呢，相信有些童鞋存在困惑.

其实这是为了满足$dp$的条件:无后效性。

度娘如是说：

>将各阶段按照一定的次序排列好之后，对于某个给定的阶段状态，它以前各阶段的状态无法直接影响它未来的决策，而只能通过当前的这个状态。换句话说，每个状态都是过去历史的一个完整总结。这就是无后向性，又称为无后效性。

所以我们应该先对$d_i$从小到大进行排序，这样进行转移时才能满足无后效性。如果我们直接按照原顺序，极有可能出现读入位置靠后但$d_i$小的物品对前面的决策产生影响。

至于方案输出，我是用的$vector$,似乎和大家的都一样，很方便$qwq$。

$Code$
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct D{int t,d,v,id;}e[101];
int f[2005],ans,ti;
vector<int> q[2005];
int n;
bool cmp(const D&a,const D&b) {return a.d<b.d;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d%d%d",&e[i].t,&e[i].d,&e[i].v),e[i].id=i;
	sort(e+1,e+n+1,cmp);
	for(int i=1;i<=n;i++)
	for(int j=e[i].d-1;j>=e[i].t;j--)
	{
		if(f[ j-e[i].t ]+e[i].v>f[j])
		{
			f[j]=f[ j-e[i].t ]+e[i].v;
			q[j]=q[ j-e[i].t ];
			q[j].push_back(e[i].id);
		}
	}
	for(int i=1;i<=2000;i++)
	if(f[i]>ans) ans=f[i],ti=i;
	printf("%d\n%d\n",ans,q[ti].size());
	for(int i=0;i<q[ti].size();i++)
	printf("%d ",q[ti][i]);
	return 0;
}
```



---

## 作者：Daniel_7216 (赞：3)

先考虑转移方程，这道题是一道比较板的 01 背包，容量就是时间，每一次需要特判是否被烧毁。设 $dp_j$ 表示在 $j$ 分钟内可获得的最大价值，套一下模板就可以得到 $dp_j = \max(dp_j,dp_{j-t_i}+p_i)$，阶段是从第一个开始正序枚举每一件物品，状态是不同的时间 $j$，要倒序枚举。有一个坑就是 $j$ 一定要从 $d_i - 1$ 开始枚举，因为当 $d_i$ 时这件物品就没救了。

题目中要求输出方案，我们需要用一个二维数组存储，第一维存储的是所需时间，第二维是在这个时间下的救出的物品列表，当每一个状态更新时将物品编号插入数组的尾部。显然，每一次转移时都要先复制上一个状态的答案。

按照这个思路写出来的程序可以过样例，但是第三个点会 WA。因为我们要满足“最优子结构”，但是如果我们枚举的第一个物品要等很久才会烧毁，我们先抢救它的话就得不到最优解了。为此我们要给每一件物品按烧毁时间的前后排序，越早被烧毁的应该先救。~~这也是标签里有贪心的原因~~

还有一个细节，取最大价值的变量初始值必须为 $0$，否则无法过第二十三个点。这是因为如果取了至少一个物品的话负数确实会被更新，但是如果没有取就不好说了。

好了上代码：
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;
int n, ans = 0;
int dp[2001], best_i;
vector <int> ans2[2001];
struct thing{
	int d, t, p, id;
}item[101]; 
bool cmp(thing a, thing b){
	return a.d  < b.d;
}
int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d%d%d", &item[i].t, &item[i].d, &item[i].p);
		item[i].id = i;
	}
	sort(item + 1, item + 1 + n, cmp);
	for (int i = 1; i <= n; i++){
		for (int j = item[i].d - 1; j >= item[i].t; j--){
			if (dp[j] < dp[j - item[i].t] + item[i].p){
				dp[j] = dp[j - item[i].t] + item[i].p;
				ans2[j] = ans2[j - item[i].t];
				ans2[j].push_back(item[i].id); 
			}
			if (ans < dp[j]){
				ans = dp[j];
				best_i = j;
			}
		}
	}
	printf("%d\n%d\n", ans, ans2[best_i].size());
	for (int i = 0; i < ans2[best_i].size(); i++){
		printf("%d ", ans2[best_i][i]);
	}
	return 0;
}
```

---

## 作者：wanggiaoxing (赞：3)

### 01背包
这道题是由 01 背包转变而成的，只不过是将背包容量变成了时间，并且要输出方式罢了，但是时间具有先后顺序，如果按照输入的 $d$ 来做的话就不符合 $dp$ 的无后效性了，举个例子，假设一个 $d$ 较小的物品排在最后，那么在更新前面较大的 $d$ 时就不会考虑到这个 $d$ 较小的物品，而在检查答案时也不会更新到它，从而使答案变小，所以我们要排序。输出方案的话只需要把之前去最大值的部分改下即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int t,d,p,k;
};
int dp[3001],n,ans,ans1;
node z[101];
vector<int>v[3001];
bool cmp(node a,node b)
{
	return a.d<b.d;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>z[i].t>>z[i].d>>z[i].p,z[i].k=i;
   sort(z+1,z+1+n,cmp);//排序
	for(int i=1;i<=n;i++)
		for(int j=z[i].d-1;j>=z[i].t;j--)
		{
			if(dp[j]<dp[j-z[i].t]+z[i].p）//储存路径
			{				
				dp[j]=dp[j-z[i].t]+z[i].p;
				v[j]=v[j-z[i].t];
				v[j].push_back(z[i].k);
			}
		}
	for(int i=0;i<=2200;i++)
		if(dp[i]>ans)
			ans=dp[i],ans1=i;
	cout<<ans<<endl<<v[ans1].size()<<endl;
	for(int i=0;i<v[ans1].size();i++)
		cout<<v[ans1][i]<<" ";
}
```


---

## 作者：Ian_Shi (赞：2)


## 心路历程：
这道题上来就有救和不救两种情况，所以自然就想到了用 01 背包来做。

易想到：先救先着火的东西，一定比救后着火的好。

唯一不同的是，这题选的是区间，不能直接标记选不选。

所以在最后解出救什么也要 dp 。

因为需要记录拿了什么，所以用二维 01 背包，便于记录。


## 小知识：

二维01背包转移方程：

$dp[i][j]=\max(dp[i-1][j],dp[i-1][j-w[i]]+v[i])$


如果还不会 01 背包的小伙伴，去看一下 P1048 采药的题解学一下（经典 01 背包）。

## 代码部分：
TALKING IS CHEAP! CODE IS HERE!（缩进不好看请担待）
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[105][2005];//二维01背包数组
//dp[i][j]表示在j的时候，救i件物品最多获得多少价值
bool flag[105][2005];//记录选没选
//flag[i][j]表示在j的时候，第i件物品是不是正好开始救。
struct item{
	int t,d,v,id;//v是p，id是编号
}st[105];//物品数组
bool cmp(const item &a,const item &b){
	return a.d<b.d;
}//结构体排序函数，以开始着火时间排序
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>st[i].t>>st[i].d>>st[i].v;
		st[i].id=i;
	}//输入
	sort(st+1,st+n+1,cmp);
   //结构体排序
	for(int i=1;i<=n;i++){
		for(int j=0;j<st[i].d;j++){
			if(st[i].t>j||dp[i-1][j]>=dp[i-1][j-st[i].t]+st[i].v){
				dp[i][j]=dp[i-1][j];
   //如果已经在救其他东西或已经有不救它，还比它好的，不救
			}else{
				dp[i][j]=dp[i-1][j-st[i].t]+st[i].v;
				flag[i][j]=1;
   //否则就救它
			}
		}
	}
	int x=0;
	for(int j=1;j<st[n].d;j++){
		if(dp[n][j]>dp[n][x])x=j;
	}
	printf("%d\n",dp[n][x]);
   //找到最好的方案，并记下救完最后一件的时间
	vector<int> ans;
   //vector记录答案并帮忙排序
	for(int i=n,j=x;i>=1;i--){//从后往前看
		if(flag[i][j]){ans.push_back(st[i].id);j-=st[i].t;}
   //如果在这时救了第i件物品，加入记录答案的vector并往前倒至开始救它的时间   		
	}
	printf("%d\n",ans.size());
   //输出选了几个
	for(int i=ans.size()-1;i>=0;i--)printf("%d ",ans[i]);
   //输出选了什么
	return 0;
}
```

---

## 作者：PosVII (赞：2)

**前言**

------------

本题会使用到简单背包以及一点点的贪心。

**思路**

------------

我们不难想到排序，排序时我们可以使用一点贪心的思路，我们肯定是要先救出更早被烧掉的物品，其它的再救也不迟。

本题的难点在于，我们要把我们救出的物品数量和物品编号输出，那么我们可以打一个布尔类型的数组存储我们的选择，即在时间为 $j$ 时我们是否选择救援第 $i$ 个物品，如果选择是，我们就在在辅助数组里存下这个选择，并减去对应的时间继续递归寻找选择。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int t,d,p,i;
}fire[106];
bool cmp(node a,node b) {
	return a.d<b.d;
}
int n,dp[106][2006],sum,print[106];
bool pre[106][2006]; 
void pri(int x,int ti) {
	if(x==0) return;
	if(pre[x][ti]==1) {
		pri(x-1,ti-fire[x].t);
		print[++sum]=x;
	}
	else pri(x-1,ti);
}
int ind,maxn;
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>fire[i].t>>fire[i].d>>fire[i].p;
		fire[i].i=i;
	}
	sort(fire+1,fire+1+n,cmp);
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=fire[i].t-1;j++) dp[i][j]=dp[i-1][j];
		for(int j=fire[i].d;j<=2000;j++) dp[i][j]=dp[i-1][j];
		for(int j=fire[i].t;j<fire[i].d;j++) {
			dp[i][j]=max(dp[i-1][j],dp[i-1][j-fire[i].t]+fire[i].p);
			if(dp[i-1][j-fire[i].t]+fire[i].p>dp[i-1][j]) {
				pre[i][j]=1;
			}
		}
	}
	for(int i=0;i<=2000;i++) {
		if(dp[n][i]>maxn) {
			maxn=dp[n][i];
			ind=i;
		}
	}
	cout<<maxn<<endl;
	pri(n,ind);
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++) cout<<fire[print[i]].i<<" ";
	return 0;
} 
```

**总结**

------------

此题不难，只是需要了解如何存储选择即可。善用递归和状态，就可以将此题转化为递归和动态规划了。

---

## 作者：Priori_Incantatem (赞：2)

~~不知道为什么是蓝题~~，其实就是把01背包稍微变形了一下，把背包容量改为了时间限制

首先，将所有的物品按照开始燃烧的时间从小到大排个序，优先考虑早开始燃烧的  
我们把时间限制当做背包容量，每个物品所占空间就是抢救该物品所需的时间  
设状态$f[i]$表示前$i$分钟能抢救到的物品的最大总价值  
剩下的转移就跟01背包一样啦

对于第二问：我们使用vector存一下每一个$f[i]$已经选过的物品，最后输出最大的$f[i]$对应的选过得我物品就可以了

```cpp
#include<cstdio> 
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int Maxn=110,Maxm=2010,inf=0x3f3f3f3f;
int f[Maxm],n,ans;
struct node{
	int d,t,v,id;
}a[Maxn];
vector <int> bin[Maxm];
inline bool cmp(node x,node y)
{
	return x.d<y.d;
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
	//freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i].t=read(),a[i].d=read(),a[i].v=read();
		a[i].id=i;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;++i)
	for(int j=a[i].d-1;j>=a[i].t;--j)
	if(f[j]<f[j-a[i].t]+a[i].v)
	{
		f[j]=f[j-a[i].t]+a[i].v;
		bin[j].clear();
		bin[j]=bin[j-a[i].t];
		bin[j].push_back(a[i].id);
	}
	for(int i=1;i<=2000;++i)
	if(f[i]>f[ans])ans=i;
	printf("%d\n%d\n",f[ans],bin[ans].size());
	for(int i=0;i<bin[ans].size();++i)
	printf("%d ",bin[ans][i]);
	printf("\n");
	return 0;
}
```

---

## 作者：凌幽 (赞：2)

# CF864E Fire

### 先送上翻译...

题意: 某人的房子着火了,他想从大火中带走价值总和尽量多的物品,每次他只能带走一个,分别给出挽救某物品需要的时间t,该物品开始燃烧的时间d(在d时间开始燃烧就不能再挽救该物品了),该物品的价值p

读入: 第一行: 物品总数n(1<=n<=100)
     以下n行,每行分别三个整数ti(1<=ti<=20),di(1<=di<=2000),pi(1<=pi<=20)

输出: 第一行: 能带走的最大的价值总和
      第二行: 这些物品的数量 
      一行,数与数用空格分隔开,分别是能带走物品的编号(按读入顺序)

### 解题思路

显然,我们可以想到背包,但是每个物品的开始燃烧时间d有个限制,限制了我们必须在d之前考虑这件物品,怎么办呢?我们可以将所有的物品以d为关键字排序,这样以时间顺序考虑物品即可

对于输出哪些物品,我们可以另外记录一个数组vis[i,j]表示第i个物品在时间j时有更新,然后倒叙贪心选取适合的物品
      
### 那么AC代码???
```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register
#define M 102
#define L 2002 

int N;

struct good{
	int t,d,p,id;
	bool operator < (const good &t) const{return d<t.d;}
}A[M];

bool vis[M][L];
int Ans,f[L];
int cnt,can[M];

inline int dy(){
	scanf("%d",&N);
	for(R int i=1;i<=N;++i){
		scanf("%d%d%d",&A[i].t,&A[i].d,&A[i].p);
		A[i].id=i;
	}
	sort(A+1,A+1+N); // 以物品开始燃烧的时间为关键字从小到大排序
	for(R int i=1;i<=N;++i)
		for(R int j=A[i].d-1;j>=A[i].t;--j)
			if(f[j]<f[j-A[i].t]+A[i].p){
				f[j]=f[j-A[i].t]+A[i].p; // 背包
				vis[i][j]=1;
			}
	for(R int i=1;i<=A[N].d;++i)
		if(f[i]>f[Ans]) Ans=i;	
	printf("%d\n",f[Ans]);
	for(R int i=N;i;--i)
		if(vis[i][Ans]) can[++cnt]=A[i].id,Ans-=A[i].t; // 贪心
	printf("%d\n",cnt);
	for(R int i=cnt;i;--i) printf("%d ",can[i]); // 按照读入顺序从小到大输出所选物品的编号
	return 0;
}

int QAQ = dy();
int main(){;}
```

---

## 作者：littlebug (赞：1)

补背包 $6/48$。

背包记录历史路径板子题，不明白为什么有绿。

## Solution

显然有一个简单的 01 背包，$f_j$ 为消耗 $j$ 时间能取得的最大价值。

注意到，按 $d_i$ 从小到大抢救物品不会更劣，选择的时间段都是连续的不会更劣，于是排序之后这个限制就只剩下 $d_i$ 对 $j$ 的限制了。

关于记录历史路径，有两种方式，各有优劣，可以见 [这个](https://www.luogu.com.cn/article/td58tl9w)。

## Code

```cpp
int n,f[N][N*20],g[N][N*20];
struct ele{int t,d,p,id;} a[N];

signed main()
{
    read(n); {rep(i,1,n) read(a[i].t,a[i].d,a[i].p),a[i].id=i;}
    sort(a+1,a+n+1,[](const auto a,const auto b){return a.d<b.d;});

    rep(i,1,n)
    {
        rep(j,0,2001) f[i][j]=f[i-1][j],g[i][j]=-1;
        rpe(j,a[i].d-1,a[i].t) if(f[i][j-a[i].t]+a[i].p>f[i][j])
        {
            f[i][j]=f[i][j-a[i].t]+a[i].p;
            g[i][j]=j-a[i].t;
        }
    }

    int ans=mxele(f[n],f[n]+2000+1),pos=-1;
    rpe(j,2000,0) f[n][j]==ans && (pos=j);
    write(ans,'\n');
    
    vector <int> v;
    rpe(i,n,1) if(g[i][pos]!=-1) v.pb(a[i].id),pos=g[i][pos];
    write((int)v.size(),'\n');
    reverse(all(v));
    _::w(v);
    
    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Vitamin_B (赞：1)

# 思路
显然是个 01 背包问题，背包容量 $\max d_i-1$，每个物品可以的拯救结束时间是 $t_i\sim d_i-1$，然后 $dp_{i,j}$（$dp_{i,j}$ 表示拯救第 $1\sim i$ 个物品用了至多 $j$ 个时间能获得的最大价值）可以从 $dp_{i-1,j-t_i}+p_i$ 转移过来。然后这题要输出方案，所以我们可以设一个 $last_{i,j}$ 数组表示 $dp_{i,j}$ 是从 $dp_{i,last_{i,j}}$ 成功转移过来的，最后递归输出。如果 $last_{i,j}=j$ 说明没有拯救这个物品，不用输出，直接递归。
# 注意事项
必须对 $d_i$ 从小到大排序，因为肯定是用结束时间小的去更新结束时间大的物品，具体解释详见[这里](//www.luogu.com.co/discuss/262811)。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
struct node {
	int t, d, p, id;
	bool operator < (const node& x) const {
		return d < x.d;
	}
} a[105];
int n, dp[105][2005], m, maxi, lst[105][2005];
vector <int> ans;
inline void dfs (int step, int x) {
	if (! step)
		return ;
	dfs (step - 1, lst[step][x]);
	if (lst[step][x] < x)
		ans.emplace_back (a[step].id);
	return ;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i].t >> a[i].d >> a[i].p;
		a[i].id = i;
		m = max (m, a[i].d);
	}
	sort (a + 1, a + n + 1);
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j < m; ++ j)
			dp[i][j] = dp[i - 1][j], lst[i][j] = j;
		for (int j = a[i].t; j < a[i].d; ++ j)
			if (dp[i - 1][j - a[i].t] + a[i].p > dp[i][j])
				dp[i][j] = dp[i - 1][lst[i][j] = j - a[i].t] + a[i].p;
	}
	for (int i = 1; i < m; ++ i)
		if (dp[n][i] > dp[n][maxi])
			maxi = i;
	dfs (n, maxi);
	cout << dp[n][maxi] << '\n' << ans.size () << '\n';
	for (int i : ans)
		cout << i << ' ';
	return 0;
}
```

---

## 作者：Harry_Hedwig (赞：1)

# 0x00 思路
先看题。

>某人的房子着火了,他想从大火中带走**价值总和**尽量多的物品,每次他**只能带走一个**,分别给出挽救某物品需要的时间 $t$ ,该物品开始燃烧的时间 $d$ (在 $d$ 时间**开始燃烧就不能再挽救该物品了**),该物品的价值 $p$。

由于每个物品只有一个，且只有 $2$ 种可能，带走或不带走（~~带不走就先不考虑了~~），所以这就是 01 背包。但是有一点变形的是：第 $i$ 个物品在救援时只能在前 $d_i$ 秒进行救援。因此，为了满足 dp 无后效性的要求，我们决定：给它们排序,接着就是 01 背包输出序列的模板题了~~吗~~。

# 0x01 排序
由于~~我们坚信~~，越早烧起来的就越有价值，于是我们按照它们的燃烧时间排序，就做到了只会出现 $2$ 种选择，选或不选，而且之后不能反悔（无后效性）。

# 0x02 定义状态
```d[i]```：在前 $i$ 秒内最多能带走的物品价值总和。

# 0x03 状态转移方程
同 01 背包。因为你如果要带走第 $j$ 件物品，那么需要腾出 $t_j$ 秒来拯救 Ta，剩下的就只有 $i-t_j$ 秒来拯救了。

所以状态转移是这样的:
```c
d[j]=max(d[j-a[i].t]+a[i].p,d[j]);
```

# 0x04 输出序列
这件事是不用多说的，因为相信大家都做过这种类型的题。用 pre 数组存储我救的物品,则 ```pre[i][j]``` 表示在第 $j$ 秒时我是否选择救第 $i$ 个物品。如果我选择了这个物品在此时救，那么就把值置为 $1$ （原来值为 $0$），由于要价值最大，遍历整个 d 数组（从小到大），找到最大值，从这个位置开始遍历，若值为 $1$ 则遍历上一行，否则继续遍历，若未遍历到 $1$ 同样也遍历上一行。

# 0x05 code
```c
#include<bits/stdc++.h>
using namespace std;
struct f
{
	int t,d,p,i;
}a[105];
bool cmp(f b,f c)
{
	return b.d<c.d;
}
int d[5005],p[105][5005],tot=0,n;
void print(int i,int j)
{
	if(i<=0)
	{
		printf("%d\n",tot);
		return;
	}
	if(p[i][j])
	{
		tot++;
		if(j>=a[i].t)
			print(i-1,j-a[i].t);
		printf("%d ",a[i].i);
	}
	else
		print(i-1,j);
}
int main()
{
	int m,i,j,ans=0,x=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d %d %d",&a[i].t,&a[i].d,&a[i].p),a[i].i=i;
	sort(a+1,a+1+n,cmp);
	for(i=1;i<=n;i++)
	{
		for(j=a[i].d-1;j>=a[i].t;j--)
		{
			if(d[j]<d[j-a[i].t]+a[i].p)
			{
				d[j]=d[j-a[i].t]+a[i].p;
				p[i][j]=1;
			}
			ans=max(ans,d[j]);
		}
	}
	printf("%d\n",ans);
	for(i=0;i<=a[n].d;i++)
		if(d[i]>d[x])
			x=i;
	print(n,x);
	return 0;
}
```

---

## 作者：zhyn (赞：0)

## **01 背包**
本题只能每个物品只能拿一次，所以想到 01 背包。


## **思路**
对于任意一个物品，有两种情况，取和不取。可推出动态转移方程 $dp_{j}=\max(dp_{j},dp_{j-t_{i}}+p_{i})$。但和其他 01 背包不同，我们可以想到，我们应该先去救马上要燃烧的，再救然后要燃烧的，这样可以尽可能得多救一些物品，因为如果先救后燃烧的，先燃烧的可能燃烧无法拯救。这样我们可以**应用结构体按 $d$ 从小到大排序**，并记录编号。




可以写出 01 背包：


```cpp
for(int i=1;i<=n;i++){
		for(int j=num[i].d-1;j>=0;j--){
			if(j>=num[i].t){
				if(dp[j]<dp[j-num[i].t]+num[i].p){    //取这个物品 
					dp[j]=dp[j-num[i].t]+num[i].p;
				}
```

但此题还要求，输出得救物品。由于我们不知道救了几个，所以可以用 vector，每次取物品的时候，将物品编号加进去。

注意：$j$ 的起始值为 $d_{i}-1$，因为如果在 $d_{i} $ 时救这个物品，它已经开始燃烧，不能救了，所以要 $-1$。

最后要遍历整个 $dp$ 数组，找到最大值。

 AC 代码：

```cpp
#include<bits/stdc++.h>
#define maxn 2005
using namespace std;

struct node{    
	int t,d,p,ind;      //ind记录编号 
}num[maxn];

int n,dp[maxn];
vector<int>f[maxn];

bool cmp(node x,node y){   //结构体排序，要按抢救时间紧迫排序 
	return x.d<y.d;
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>num[i].t>>num[i].d>>num[i].p;
		num[i].ind=i;
	}
	sort(num+1,num+n+1,cmp);
	
	//01背包 
	for(int i=1;i<=n;i++){
		for(int j=num[i].d-1;j>=0;j--){
			if(j>=num[i].t){
				if(dp[j]<dp[j-num[i].t]+num[i].p){    //取这个物品 
					dp[j]=dp[j-num[i].t]+num[i].p;
					f[j]=f[j-num[i].t];
					f[j].push_back(num[i].ind);   //存储物品的编号 
				}
			}
		}
	}
	
	
	int ans=0,cnt=0;
	for(int i=1;i<=2000;i++){       //查找最大值 
		if(ans<dp[i]){
			ans=dp[i];
			cnt=i;
		}
	}
	cout<<dp[cnt]<<"\n";
	cout<<f[cnt].size()<<"\n";           //size()有多大，就有几个物品 
	for(int i=0;i<f[cnt].size();i++){      //输出 
		cout<<f[cnt][i]<<" ";
	}
	
	return 0;
}
```

---

## 作者：caoshuchen (赞：0)

# [Fire](https://www.luogu.com.cn/problem/CF864E)

## 思路

观察题目，很明显是 $01$ 背包变形。

$dp[i][j]$ 表示前 $i$ 个物品，恰好在时刻 $j$ 挽救最后一个物品的最大收益。递推式就是很简单的 $01$ 背包，直接看代码即可。

初始值：$dp[0][0] = 0$；其它值为 -$\inf$。

但难点有 $2$ 处。

### 递推顺序

如果以随便的顺序进行递推，你将成功获得样例正确而 $0$ pts 的好成绩。

为什么呢？其实我们模拟一遍会发现，对于两个物品 $A,B$，设 $A$ 先燃烧，则当我们先递推 $B$ 后推 $A$ 时，可能发生 $dp[B][t]$ 是 $B$ 最大收益，但是当 $A$ 到 $t$ 时刻燃烧了，那么按我们的递推 $dp[A][t] = dp[B][t]$ 即 $A$ 不选，不更新结果。但有可能先推 $A$ 时，$dp[B][t]$ 能够更新最大收益，所以：先推 $A$ 后推 $B$ 一定不比反过来推的结果差。

所以我们按燃烧时间从早到晚排序即可。

### 反推顺序

这道题还让我们求出挽救物品的顺序，怎么办呢？

我们可以倒着反推即 $n\to1$，先枚举推出 $dp[n][w]$ 最大值时，$w$ 的值是多少。这里，$w$ 其实就是当前花费总时间。

然后再用递推式验证：

- 如果 $w\ge t_i$ 并且 $w<d_i$ 并且 $dp[i-1][w-t_i]+p_i=dp[i][w]$ 即这个物品能选，并且选这个物品能达到最优，选，$w$ 减去 $t_i$。

- 否则，不选，啥也不干。

那我们这样就能知道选择的人，那顺序是什么呢？

很容易发现，$w$ 越小的时候挽救，则代表你挽救的时间越早，而刚刚反推的过程中 $w$ 不断减小，所以将反推的顺序倒过来输出即可。说着可能听不懂，结合一下代码。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

struct Item {
	int t, d, p, id;
} a[105];

int n;
int dp[105][2005];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i].t >> a[i].d >> a[i].p, (a[i].id = i);
	sort(a + 1, a + n + 1, [](Item x, Item y){return x.d < y.d;});
	memset(dp, ~0x3f, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= 2000; j++) {
			dp[i][j] = dp[i - 1][j];
			if (j >= a[i].t && j < a[i].d)
				dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i].t] + a[i].p);
		}
	}
	int ans = 0, w = 0;
	for (int i = 0; i <= 2000; i++) {
		if (dp[n][i] > ans)
			ans = dp[n][i], w = i;
	}
	cout << ans << endl;
	stack<int> st;
	for (int i = n; i >= 1; i--) {
		if (w >= a[i].t && w < a[i].d && dp[i - 1][w - a[i].t] + a[i].p == dp[i][w])
			st.push(a[i].id), w -= a[i].t;
	}
	cout << st.size() << endl;
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	return 0;
}

```

---

## 作者：caramel_qwq (赞：0)

本题是贪心 + 01 背包的综合应用。顺便写了个骚气的栈输出。


------------
## 注意点

- 输出编号时要按照抢救的顺序来。
- 注意题目背包的容量是抢救的时间。



------------

## 基本步骤
1. 读入数据，推荐使用结构体，另外每读入一组数据都要编号。
1. 结构体数组按照每种物品烧毁时刻的先后排序。
1. 套 01 背包模板。
1. 按照题目要求的顺序输出。

------------
## 关于 dp
$\mathit{dp}_{i,j}$ 表示第 $i$ 个时刻抢救 $j$ 个物品的最大价值。

DP 数组的两个上限分别是物品总数和最大价值。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tsum=0,ans=0;
struct node{
    int t,d,p,id;
}a[108];
bool flag[108][2008];
int dp[108][2008]={};
bool cmp(node x,node y){
    return x.d<y.d;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a[i].t,&a[i].d,&a[i].p);
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    tsum=a[n].d;
    for(int i=1;i<=n;i++){
        for(int j=0;j<a[i].d;j++){
            if(j<a[i].t||dp[i-1][j]>=dp[i-1][j-a[i].t]+a[i].p){
                dp[i][j]=dp[i-1][j];
            }else{
                dp[i][j]=dp[i-1][j-a[i].t]+a[i].p;
                flag[i][j]=1;
            }
        }
    }
    int t=0,len=0;
    for(int i=1;i<=tsum;i++) if(dp[n][i]>dp[n][t]) t=i;
    printf("%d\n",dp[n][t]);
    stack<int> s;
    for(int i=n,j=t;i>=1;i--){
        if(flag[i][j]){
            s.push(a[i].id);
            len++;
            j-=a[i].t;
        }
    }
    printf("%d\n",len);
    while(!s.empty()){
        printf("%d ",s.top());
        s.pop();
    }
    printf("\n");
    return 0;
}
```
## 亲测无毒，放心食用。

---

## 作者：_Fontainebleau_ (赞：0)

这题是一道 **01背包** 变形。

考虑先将物品按开始燃烧时间 $d$ 从小到大排序，循环时将第二层的条件改为燃烧时间（第 $i$ 件物品从 $d_i$ 时刻开始着火，故循环从 $d_i -1$ 开始）。

$f_i$ 表示 第 $i$ 个时间可以获得的最大价值，转移方程为 $f_j=\max (f_j,f_{j-t_i}+p_i)$.

解决了最大价值总和，如何保存带走的物品总数与编号？

想到可以用 vector 存下每个时间救出的物体。遍历时从 $1$ 遍历到最后一个物品燃烧的时间（即 $d_n$ ），找 $f_i$ 的最值，记录下当前时间，按顺序输出当前时间的 vector 中的值。

code
```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int n;
int f[2001];
struct point{
	int t,d,p,num;
}a[101];
vector<int> v[2001];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*f;
}
inline bool cmp(point x,point y)
{
	return x.d<y.d;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i].t=read(),a[i].d=read(),a[i].p=read(),a[i].num=i;
	stable_sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
		for(int j=a[i].d-1;j>=a[i].t;j--)
			if(f[j]<f[j-a[i].t]+a[i].p)
			{
				f[j]=f[j-a[i].t]+a[i].p;
				v[j]=v[j-a[i].t];
				v[j].push_back(a[i].num);
			}
	int p,ans=-2e9;//极小值
	for(int i=1;i<=a[n].d;i++)
		if(f[i]>ans)
			ans=f[i],p=i;
	printf("%d\n%d\n",ans,v[p].size());
	for(vector<int>::iterator it=v[p].begin();it!=v[p].end();it++)
		printf("%d ",*it);
	return 0;
}

```
❀完结撒花❀

---

