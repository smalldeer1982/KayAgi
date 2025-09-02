# [USACO10JAN] Buying Feed, II S

## 题目描述

Farmer John needs to travel to town to pick up K (1 <= K <= 100) pounds of feed. Driving D miles with K pounds of feed in his truck costs D\*K cents.

The county feed lot has N (1 <= N <= 100) stores (conveniently numbered 1..N) that sell feed. Each store is located on a segment of the X axis whose length is E (1 <= E <= 350). Store i is at location X\_i (0 < X\_i < E) on the number line and can sell FJ as much as F\_i (1 <= F\_i <= 100) pounds of feed at a cost of C\_i (1 <= C\_i <= 1,000,000) cents per pound. Amazingly, a given point on the X axis might have more than one store.

FJ starts at location 0 on this number line and can drive only in the positive direction, ultimately arriving at location E, with at least K pounds of feed. He can stop at any of the feed stores along the way and buy any amount of feed up to the the store's limit.

What is the minimum amount FJ has to pay to buy and transport the K pounds of feed? FJ knows there is a solution.

Consider a sample where FJ needs two pounds of feed from three stores (locations: 1, 3, and 4) on a number line whose range is 0..5:

```
0   1   2   3   4   5 
+---|---+---|---|---+ 
    1       1   1      Available pounds of feed 
    1       2   2      Cents per pound 
```
It is best for FJ to buy one pound of feed from both the second and third stores. He must pay two cents to buy each pound of feed for a total cost of 4. When FJ travels from 3 to 4 he is moving 1 unit of length and he has 1 pound of feed so he must pay 1\*1 = 1 cents.

When FJ travels from 4 to 5 he is moving one unit and he has 2 pounds of feed so he must pay 1\*2 = 2 cents.

The total cost is 4+1+2 = 7 cents. 

FJ 开车去买 $K$ 份食物，如果他的车上有 $X$ 份食物。每走一里就花费 $X$ 元。FJ 的城市是一条线，总共 $E$ 里路，有 $E+1$ 个地方，标号 $0\sim E$。 FJ 从 $0$ 开始走，到 $E$ 结束（不能往回走），要买 $K$ 份食物。 城里有 $N$ 个商店，每个商店的位置是 $X_i$（一个点上可能有多个商店），有 $F_i$ 份食物，每份 $C_i$ 元。 问到达 $E$ 并买 $K$ 份食物的最小花费。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/1720.png)


## 样例 #1

### 输入

```
2 5 3
3 1 2
4 1 2
1 1 1```

### 输出

```
7```

# 题解

## 作者：幽界の冥神 (赞：32)

```cpp
#include "cstdio"
#include "algorithm"
using namespace std;
struct food{int val,num;}f[102];//num为这个商店的存货,val为在这个商店买一份食物的价钱
int number,s,n,ans=0;
bool cmp(food a,food b){return a.val<b.val;}//从小到大排序 
int Min(int a,int b){return a<b?a:b;}
int main(){
    scanf("%d%d%d",&number,&s,&n);//number为总共要买的食物,s为总路程,n为商店数 
    for(int i=1,a,b;i<=n;i++){
        scanf("%d%d%d",&a,&f[i].num ,&b);
        f[i].val=s-a+b;//在这个商店买一份食物的价钱 
    }
    sort(f+1,f+1+n,cmp);//排序,取最小值 
    for(int i=1;i<=n&&number>0;i++){
        ans+=Min(number,f[i].num)*f[i].val;//每到一个商店就取光光 
        number-=f[i].num;//剩下需要买的食物 
    }
    printf("%d",ans);//输出 
    return 0;
}
```
个人认为这是比较简短的代码了，缩进不大好看，见谅。。。
一般贪心必将配合排序（至少我做的题目是这样的）不排序的贪心很可能有问题。。。

基本就是这样了，注释应该还蛮详细的


---

## 作者：tktp_AK (赞：17)

这道题不需要用背包

仅仅只需要一个**结构体**就可以搞定

讲解在代码上

代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,f,c;
}a[550];//先定义一个结构体，x表示商店的位置
//f表示商店里有多少食物，c表示将一份食物带回家所需要的成本 
bool cmp(node x,node y){return x.c<y.c;}//排序由成本从小到大排 
int main()
{
	//freopen("testdata.in","r",stdin);
	int k,e,n;scanf("%d%d%d",&k,&e,&n);//要买K份食物，有e里路，共n个商店 
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a[i].x,&a[i].f,&a[i].c);
		//输入每个商店的位置，粮食数量和每份食物的价格
		a[i].c+=e-a[i].x;//成本为每份食物的价格加上路费 
	}
	sort(a+1,a+n+1,cmp);//排序 
	long long ans=0,t=0;//ans为需要多少钱，t为目前一共买了多少份粮食 
	for(int i=1;i<=n;i++)
	{
		if(t+a[i].f>k)
		//如果当前买的粮食份数加上这个商店有的粮食份数超过了所需的粮食数量 
		{
			ans+=(k-t)*a[i].c;//ans只用加上买够k的钱数就行了 
			break;//退出循环 
		}
		else
		{
			ans+=a[i].f*a[i].c;//否则就买完整个商店的粮食 
			t+=a[i].f;//将t进行更新 
		}
	}
	printf("%lld\n",ans);//输出结果 
	return 0;
}
```
纯代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
	int x,f,c;
}a[550];
bool cmp(node x,node y){return x.c<y.c;}
int main()
{
	//freopen("testdata.in","r",stdin);
	int k,e,n;scanf("%d%d%d",&k,&e,&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a[i].x,&a[i].f,&a[i].c);
		a[i].c+=e-a[i].x;
	}
	sort(a+1,a+n+1,cmp);
	long long ans=0,t=0;
	for(int i=1;i<=n;i++)
	{
		if(t+a[i].f>k)
		{
			ans+=(k-t)*a[i].c;
			break;
		}
		else
		{
			ans+=a[i].f*a[i].c;
			t+=a[i].f;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：SunsetLake (赞：6)

### 思路
一看到题就知道是贪心，题目让我们求最小花费，那么我们就要知道最小花费的构成:路费+餐费。也就是说，只有在餐费和路费都最小的情况下才能达到总费用最小。我们可以把每个点的花费表示出来，再进行排序，这就是贪心策略。那么，每个点的花费怎么求呢？不仅要算单价，还要加上这个点到终点的距离（仔细想想），所以每个点的单价： $c_i+(e-x_i)$ 。知道了这点，此题也就迎刃而解了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,e,n,ans;
struct node{
	int x,f,c,tal;
}st[110];//结构体用来存每个点的坐标、食物总量、食物单价和总共单价
bool cmp(node s,node g){
	return s.tal<g.tal;
}
int main(){
	cin>>k>>e>>n;
	for(int i=1;i<=n;i++){
		cin>>st[i].x>>st[i].f>>st[i].c;
		st[i].tal=st[i].c+e-st[i].x;//计算出第i个点的总共单价
	}
	sort(st+1,st+1+n,cmp);//以总共单价从小到大排序，贪心
	for(int i=1;;i++){
		k-=st[i].f;//买下第i个点的食物
		if(k>=0){//判断买完第i个点总量达没达到k
			ans+=st[i].tal*st[i].f;//没达到则将总花费加上当前点的总单价*当前点的总数量，继续前往下一个点
		}
		else{//超过了则只买还差的k份，并跳出循环输出答案
			k+=st[i].f;
			ans+=k*st[i].tal;
			break;
		}
	}
	cout<<ans;
	return 0;
}

```
本蒟蒻的第一篇题解，求过，谢谢管理员大大。

---

## 作者：Sirius_X (赞：4)

这道题，其实不是很难，我的思路是：
## 动态规划，将这道题转化为多重背包问题
大家对多重背包（每个物品最多能选n[i]件）应该不是很陌生，其核心代码为：
``````C++
for(int i=1;i<=n;i++)
	for(int j=m;j>=0;j--)
		for(int k=0;k<=n[i];k++){
			if(j<k*v[i]) continue;
			f[j]=mx(f[j],f[j-k*v[i]]+k*c[i]);
		}
``````
### 那么我们怎么将这道题转化为多重背包呢？
#### 首先，我们可以令每份食物的体积为1，份数为题目已经给的f[i],价值则为c[i]+e-x[i]，背包容积为总共要买的食物份数k
#### 那么状态转移方程则为：dp[j]=mn(dp[j],dp[j-l]+l*(c[i]+e-x[i]));
#### 又因为是求最小值，所以我们一开始要将dp数组1-n的部分初始化成无穷大，这样才不会影响最终答案
下面是我的代码：
``````C++
#include<cstdio>
int dp[105];
int mn(int x,int y){
	return x<y?x:y;
}
int main(){
	int n,e,k,x,f,c;
	scanf("%d %d %d",&k,&e,&n);
	for(int i=1;i<=k;i++)
		dp[i]=1<<30;//初始化为无穷大
	for(int i=1;i<=n;i++){//采用了边读边做的方法，能够节省一点空间
		scanf("%d %d %d",&x,&f,&c);
		for(int j=k;j>=1;j--)//枚举背包容积
			for(int l=1;l<=f;l++){//放l个第i种食物在背包里
				if(l>j) break;//如果l个食物的体积，已经超过背包容积j，退出循环
				dp[j]=mn(dp[j],dp[j-l]+l*(c+e-x));//状态转移方程，因为有l份食物，所以体积为(l*1=)l,价值也乘l
			}
	}
	printf("%d\n",dp[k]);//因为求得是买k份食物的最小值，所以直接输出dp[k]
	return 0;
}

``````

---

## 作者：zilingheimei (赞：3)

首先，我们先看题目

[P2616 [USACO10JAN]Buying Feed, II S](https://www.luogu.com.cn/problem/P2616)

#### 这题我们可以用贪心+排序来做

------------

### 思路

#### 1. 首先我们要知道——对于某些购买很便宜的不代表选择它的花费最小，因为还有路程的花费

如：

$1$ $1000$ $3$ 

$1$ $3$ $1$

$999$ $3$ $2$

显而易见，选择距离为 $999$ 的更优

- 因此我们比较的时候应该比较它们的  _购买花费_  和 _路程携带花费_ 之和

#### 2. 对于我们路上遇到的花费（指 $1.$ 中的花费定义）较小时，应在可以购买的范围购买 _尽可能多_

#### 3. 当再买就会超出需求时，就买 _刚好需求_ 即可，因为花费不可能是负数



------------

所以便有了以下代码，带注释

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,e,k,ans,sum;
struct point {
	int x,f,c;//距离起点 数量 价钱 
	int cost;//花费 
}a[10010];
bool cmp(point x,point y){
	return x.cost<y.cost;
}
int main(){
	cin>>k>>e>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].f>>a[i].c;
		a[i].cost=e-a[i].x+a[i].c;//代表买一份食物并带走的价钱 
	}
	sort(a+1,a+n+1,cmp);//将食物的花费从小到大排序 
	for(int i=1;i<=n;i++){
		if(sum>=k)break;//当数量足够，终止 
		ans+=min(k-sum,a[i].f)*a[i].cost;//购买尽可能多的食物 
		sum+=min(k-sum,a[i].f);//数量叠加 
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：RatingStar (赞：2)

这题乍一看以为是最短路，觉得要申黄。仔细一看才发现很水。

**大意：贪心**

1. 对于每个价格，加上他们要走的路程，也就是 $(K-X)$，那么整体的价格就为 $(K-X)+C$。

2. 排一遍序（升序），然后从前往后遍历最小值直到买完所有商品。

3. 输出答案。

需要注意的几个点：

1. 排序要是升序排列。因为题目说不能往回走，所以前面买的自然就不能比后面的大。这样也得不到最优解。

2. 函数最好调用库里面有的。不然手打最小值很容易造成错误。

3. 尽量，尽量不要使用 $STL$ 库，锻炼自己的手打能力。

代码 **杜 绝 抄 袭**（上文看不懂下面有注释）：
```cpp
#include<cstdio>
#include<iostream>
int K,E,N,X,ans;
int F[105],P[105],C;
int main()
{
    scanf("%d%d%d",&K,&E,&N);
    for(int i=1;i<=N;i++)
    {
		scanf("%d%d%d",&X,&F[i],&C);
		P[i]=(E-X)+C;//上文提到
	}
	for(int i=1;i<=N-1;i++)//对数组进行排序
		for(int j=1;j<=N-i;j++)
			if(P[j]>P[j+1])//以价格为基准进行判定
			{
				std::swap(P[j],P[j+1]);
				std::swap(F[j],F[j+1]);//F[]跟着P[]交换
			}
    for(int i=1;i<=N&&K>0;i++)//此处还要判断商品还需不需要，即K>0
    {
		ans+=std::min(K,F[i])*P[i];//当此时不需要买那么多商品时，就把剩下还需要的买空，不然就把这个商店的商品买完，当然也承担了路费
	    K-=F[i];//需要的商品数--
    }
    printf("%d",ans);
    return 0;
}
```



---

## 作者：yezl (赞：2)

### 题目大意：

农夫约翰在一个直线的长度为 $ E $ 的城市，这有 $ N $ 个商店卖饲料，第 $ i $ 个商店位于 $ x_i $ 的位置，第 $ i $ 个商店可出售 $ f_i $ 磅的饲料，每磅饲料成本为 $ c_i $ ，卡车载着 $ K $ 磅饲料开 $ D $ 英里要花 $ K\times D $ 美分。约翰只能一直向前开，问他买 $ K $ 磅饲料的最小花费为多少。

### 思路分析：

~~这题的标签告诉我们~~，要用到贪心和排序，那么其实很好解决的，首先我们记录下在第 $ i $ 个商店买一磅饲料用的钱，易得为：  
 $$ E-x_i+c_i $$ 
 
这下就可以直接按价钱**从小到大**排序啦，然后从最便宜的开始枚举，直到达到需求量 $ K $ 就好啦。

$ \large\mathcal{My\;Code:} $

```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>//这库有快排函数sort
using namespace std;
const int N=110;//定义常变量
int k,e,n,ans;//ans存答案
struct node{//记得用结构体
	int val,num;//val存单价，num就是这个商店有的数量
}f[N];
inline int read()//快读函数，比scanf快点o
{
    int num=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0' && ch<='9')
    {
        num=(num<<1)+(num<<3)+ch-'0';
        ch=getchar();
    }
    return num;
}
bool cmp(node x,node y)//排序函数
{
	return x.val<y.val;//按单价从小到大排序
}
int main()
{
	k=read(),e=read(),n=read();//读入
	for(int i=1;i<=n;i++)
	{
		int x,c;//这个定义个临时的就可以了
		x=read(),f[i].num=read(),c=read();
		f[i].val=e-x+c;//单价存起来
	}
	sort(f+1,f+1+n,cmp);//排序
	for(int i=1;i<=n && k>0;i++)//k要大于0吖，因为底下我是直接减
	{
		ans+=min(k,f[i].num)*f[i].val;//可能它给的直接超过需求量，取其中小的
		k-=f[i].num;//k就全减啦，这里可以换成减min(k,f[i].num)，这样什么就可以直接=0了
	}
	printf("%d",ans);//输出
	return 0;
}
```

希望可以帮到大家。

---

## 作者：rsdbk_husky (赞：1)

放在前面：为对应“普及-”的难度，本文讲解的是 $O(nW^2)$ 复杂度的朴素 DP，如想挑战更高难度请进 [Here](https://www.luogu.com.cn/problem/P4544)，并欢迎大家来该题题解看我的[另一篇博客](https://rsdbk-husky.blog.luogu.org/luogu-p4544-usaco10novbuying-feed-g)上的 $O(nW)$ 解法。 

## 零. 安利：

[安利一下我的博客。](https://rsdbkhusky.github.io/)

### 一. 变量声明：

- $W$：代替题目中的 $K$，到家时应带的饲料吨数，相当于背包中的背包最大承重（weight）。
- $n$：代替题目中的 $N$，商店数量，相当于背包问题中的物品数。
- $x_i$：同题目中的 $x_i$。
- $w_i$：代替题目中的 $f_i$，商店 $i$ 食物数量。
- $v_i$：代替题目中的 $c_i$，商店 $i$ 食物单价。

## 二. 思路

#### 1. 思考解法

- 路线上后面的商店不会影响路线前半部分的最优解，**符合无后效性**。
- 有最大容量 $W$，有可选择的物品，每个物品有重量和价值，明显是背包类问题。

所以考虑背包 DP。

#### 2. 初始状态

$d_{i,j}=\begin{cases} 0~~~~~~~~~(i=0~\land~j=0)\\ \infty~~~~~~~(else) \end{cases}$

#### 3. 结束状态

$d_{\operatorname{home},W}$        （$\operatorname{home}$：见代码和代码中的注释）

#### 4. 确定状态转移方程

$d_{i,j}$：已经经过前 $i$ 个商店（已到 $i$ 号商店买了东西但还没有往 $i+1$ 号走）且恰好一共买了 $j$ 份食物时最少花费的费用。

本题就是一道改装版的[多重背包问题](https://www.luogu.com.cn/problem/P1776)，就加了一个转移花费，转移花费怎么求呢？$i$ 店与上一家店距离差为 $x_i-x_{i-1}$，若在 $i$ 号店买的食物份数为 $k$ ，在 $i$ 店购物后车上的食物份数为 $j$（$j$ 和 $k$ 这两个量都是 for 循环枚举出来的），则这段路上车辆运送的食物数为 $j-k$。转移花费就是 $(x_i-x_{i-1})\times (j-k)$。

**综上所述，状转方程**：$d_{i,j}=\min_{k=0}^{k\leqslant w_i}\{{d_{i-1,j-k}+(x_i-x_{i-1})\times (j-k)+v_i\times k}\}$ 


## 三. 代码

代码中有一些例如构造函数和重载运算符一样的技巧，这些暂时不会也不妨碍理解算法，只需看 ```main``` 函数中的内容就行了。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define re register

const int MAXn = 500;
const int MAXW = 10000;

template <class T>    //模板函数
inline void read(T &a) {
    register char c;while (c = getchar(), c < '0' || c >'9');register T x(c - '0');while (c = getchar(), c >= '0' && c <= '9')x = (x << 1) + (x << 3) + c - '0';a = x;  
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

struct Shop {
	int x;
	int w;
	int v;
	
	Shop(): x(0), w(0), v(0){}    //构造函数 
	Shop(int x_, int w_, int v_): x(x_), w(w_), v(v_) {}    //同上 
	inline bool operator < (Shop &a) {    //重载运算符 
		return this->x < a.x;
	}
};

Shop shop[MAXn + 10];
int W, n, d[MAXn + 10][MAXW + 10];

int main() {
	int E;
	read(W), read(E), read(n);
	shop[0] = Shop(0, 0, 0);    //本人将起点和终点（家）时当做食物数为 0 的商店，这样能避免特判，所以“home”就是n+1
	for (re int i = 1, x, w, v; i <= n; ++i) {
		read(x), read(w), read(v);
		shop[i] = Shop(x, w, v);
	}
	shop[n + 1] = Shop(E, 0, 0);    //同上 
	sort(shop, shop + n + 2);
	memset(d, 0x3f, sizeof(d));
	d[0][0] = 0;
	for (re int i = 1; i <= n + 1; ++i) {    //i：当前阶段是在哪个店 
		for (re int j = W; j >= 0; --j) {    //j：当前状态要求车上有多少饲料 
			for (re int k = 0; k <= shop[i].w; ++k) {    //k：当前转移中要从本店买多少饲料 
				if (j < k) continue;
				d[i][j] = min(d[i][j], d[i - 1][j - k] + (shop[i].x - shop[i - 1].x) * (j - k) + k * shop[i].v);
			}
		}
	}
	printf("%d", d[n + 1][W]);
}
```



---

## 作者：花千树 (赞：1)

本题思路：不难贪心+排序，排序用sort，不然好多新手思路对了排序排错了，那就尴尬了

定义一个结构体数组f，读入时，用公式**（很重要）**计算出f[i].a的值，公式为：f[i].a=s-l+k;s路程，l为商店的位置，k为饲料的单价（这里公式的推导留给各位自己思考，为什么要这样写，不要照搬硬套，题解是用来借鉴的）只要用了公式计算，本题就简单多了

话不多说，上代码！！！！！

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>//sort必备万能头文件
using namespace std;
struct AC{//定义结构体
    int a,b;
};
AC f[105]; //结构体数组f
int ans;//最终答案
bool cmp(const AC&x,const AC&y){//sort的cmp
     return x.a<y.a;
}
int main(){//过程华丽开始
    int m,n,s,l,k;//定义
    cin>>m>>s>>n;//读入
    for(int i=1;i<=n;i++){//读入
        scanf("%d%d%d",&l,&f[i].b,&k);
        f[i].a=s-l+k;//利用重要公式计算
    }
    sort(f+1,f+1+n,cmp);//快排
    int i=1;
    while(m>0){//主要处理循环
        if(i>n)break;//如果商店走完，退出
            if(m>f[i].b)ans+=f[i].b*f[i].a;//如果需要的饲料大于当前商店饲料数，购买次商店所有（因为sort过了，前面的必定是划算的）
        else ans+=m*f[i].a;//不然能买多少买多少
        m-=f[i].b; //总量减去这次买的
        i++;
    }
    printf("%d\n",ans);//完美输出
    return 0;//过程华丽结束
}
```

---

## 作者：化学小哥 (赞：1)

一个大贪心……

记录每个货物的价格为（m-t）\*c，然后贪心……


```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct shu {int jia,num;}a[505];//jia 为价格   ，num为数量
int k,m,n,t,c,ans;
int compare(shu x,shu y)
{
    return x.jia<y.jia;
}
int main()
{
    scanf("%d%d%d",&k,&m,&n);
    for (int i=1;i<=n;i++)
    {scanf("%d%d%d",&t,&a[i].num,&c);a[i].jia=(m-t)+c;}//预处理
    sort(a+1,a+n+1,compare);//排序找最小
    for (int i=1;i<=n;i++)
    {ans+=min(k,a[i].num)*a[i].jia;
     k-=a[i].num;
     if (k<=0) break;//取最小值
    }
    printf("%d",ans);
}
```

---

## 作者：int32 (赞：0)

[P2616](https://www.luogu.com.cn/problem/P2616)

~~蒟蒻双来水题解啦~~

## 思路概述

贪心

尽量买小花费的，如果大于目前需求量则不买

总价$=$单价$×$数量

其实还可以用$dp$做

## Code

```
#include<bits/stdc++.h>
using namespace std;
int k, e, n, v;//v:答案
struct buy{
    int how, use;//how:食物份数,use:食物单价
}p[101];
inline bool cp(const buy& a, const buy&b){
    return a.use<b.use;//小的优先
}
int main(){
    cin>>k>>e>>n;
    for(int i=1;i<=n;i++){
        int w, ww;
        cin>>w>>p[i].how>>ww;
        p[i].use=e-w+ww;//食物单价
    }
    sort(p+1,p+n+1,cp);
    for(int i=1;i<=n;i++){
        if(k<=0) break;//不需要了
        v+=min(k,p[i].how)*p[i].use;//花费
        k-=p[i].how;//需求量变少
    }
    cout<<v;
    return 0;
}
```
蒟蒻求赞

 #### 管理员大大求过

---

## 作者：Samsam (赞：0)

做的时候直接想到的就是动态规划不过也打出来了

我的做法和背包差不多


同样滚动数组


f[j]表示当前位置j份食物的最小价值



f[j]=min(f[j-l]+l\*c) 1<=l<=f

而且在每一步走的时候



f[j]+=j

然后就行了。。


```cpp
#include <cstdio>  
#include <cstring> 
#include <cmath>  
#include <string>  
#include <iostream>  
#include <algorithm>  
#include <queue>  
using namespace std;  
#define rep(i, n) for(int i=0; i<(n); ++i)  
#define for1(i,a,n) for(int i=(a);i<=(n);++i)  
#define for2(i,a,n) for(int i=(a);i<(n);++i)  
#define for3(i,a,n) for(int i=(a);i>=(n);--i)  
#define for4(i,a,n) for(int i=(a);i>(n);--i)  
#define CC(i,a) memset(i,a,sizeof(i))  
#define read(a) a=getint()  
#define print(a) printf("%d", a)  
#define dbg(x) cout << #x << " = " << x << endl  
#define printarr(a, n, m) rep(aaa, n) { rep(bbb, m) cout << a[aaa][bbb]; cout << endl; }  
inline const int getint() 
{
    int r=0, k=1; char c=getchar(); 
    for(; c<'0'||c>'9'; c=getchar()) if(c=='-') k=-1; 
    for(; c>='0'&&c<='9'; c=getchar()) r=r*10+c-'0'; 
    return k*r; 
}  
inline const int max(const int &a, const int &b) 
{ 
    return a>b?a:b; 
}  
inline const int min(const int &a, const int &b)
{ 
     return a<b?a:b; 
}    
const int N=105, K=105, E=400;  
int n, k, e;  
int f[K];  
struct dat 
{ 
      int x, f, c; 
}
a[N];    
int main() 
{      
    read(k); 
    read(e); 
    read(n);      
    for1(i, 1, n) read(a[i].x), read(a[i].f), read(a[i].c);      
    CC(f, 0x3f); f[0]=0;      
    for1(p, 0, e) {          
        for1(j, 1, k) f[j]+=j;          
        for1(i, 1, n) if(a[i].x==p){              
            for3(j, k, 1) {                  
                for1(l, 1, a[i].f) if(j-l>=0)                      
                f[j]=min(f[j], f[j-l]+l*a[i].c);              
            }          
        }      
    }      
    print(f[k]);      
    return 0;  
}
```

---

## 作者：YuanZihan1225 (赞：0)

从题上来看，可以很明显发现这是一道贪心题。

**分析：**

1. 对于每一个价格，加上要走的所有路程，就能得到: $(k - t)$ 。那么整体的价格就为：　$\sum _ {i = 1} ^ {n} (k - t)c _ i$ 。

2. 给序列以 **升序** 排一遍序，然后 **从前往后遍历最小值** 直到卖完所有的商品。

3. 输出答案。

**注意，千万要升序**，因为题目说不能往回走，所以前面买到的就必须必后面小，才能得到最优解。

代码见下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x, f, c;
	bool operator < (const node &b) const
	{
		return c < b.c;
	}
}a[600];
int k, e, n;
signed main()
{
	cin >> k >> e >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i].x >> a[i].f >> a[i].c;
		a[i].c += e - a[i].x;
	}
	sort (a + 1, a + n + 1);
	int ans = 0, t = 0;
	for(int i = 1; i <= n; i++)
	{
		if(t + a[i].f > k)
		{
			ans += (k - t) * a[i].c;
			break;
		}
		else
			ans += a[i].f * a[i].c, t += a[i].f;
	}
	cout << ans;
	return 0;
}
```

---

