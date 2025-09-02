# [BalticOI 2008] 选举

## 题目描述

The citizens of Byteland have recently been voting in the parliamentary elections. Now, when the results
have been published, the parties have to decide on a coalition to form the government.

Each party received a certain number of seats in the parliament. The coalition must be a subset of the
parties such that together they have strictly more than half of all the seats in the parliament. It is desirable for
the coalition to have as many seats as possible, to ensure they can still pass their proposed laws even if a few
of their members are absent from a parliament session.
A coalition is called redundant if one of its parties can be removed with the remaining ones still having
more than half of the seats in the parliament. Of course, such a removable party would effectively have no
power — the other members of the coalition would be able to force the laws regardless of its opinion.


Write a program that:

- reads the election results from the standard input,
- finds a non-redundant coalition that has the maximal possible number of seats in the parliament,
- writes the description of this coalition to the standard output.

### Input

The first line of the standard input contains one integer $n\ (1\le n\le 300)$ — the number of parties that participated in the elections. The parties are numbered from $1$ to $n$.

The second line contains n nonnegative integers $a_1,\dots,a_n$, separated by single spaces, where $a_i$
is the
number of seats received by the $i$-th party. You may assume that the total number of seats in the parliament
will be positive and lower or equal to $100000$.

Additionally, in test cases worth $40\%$ of points, the number of parties will not exceed $20$.

### Output

The first line of the standard output should contain one integer $k$ — the number of parties in a non-redundant
coalition which has the maximal number of seats.
The second line should contain $k$ distinct integers separated by single spaces — the numbers of parties
that form the coalition.

If there are several non-redundant coalitions with the maximal number of seats, you may output any of
them. The member parties can be listed in any order.

### 题目翻译

Byteland 国的居民最近一直为议会选举投票。现在，当结果公布的时候，党派不得不决定联合组建政府。 

每个党派都会获得议会中的一定席位。联合政府由这些党派中的一部分组成，他们在议会中的席位数之和**严格大于**总席位数的一半。对于联合政府来说，席位越多越好。

一个**过剩**的联合政府是指联合政府中的一个党派被移出后，剩余的联合政府在国会中仍有过半数的席位。

请写一个程序能够：

-    读取选举结果；
-    找到一个在议会中有着**最大可能席位数**且**不过剩**的联合政府；
-    输出这个联合政府的描述。


## 说明/提示

对于 $40\%$ 的数据，$n\le 20$；

对于全部数据，$1\le n\le 300$。

## 样例 #1

### 输入

```
4
1 3 2 4```

### 输出

```
2
2 4```

# 题解

## 作者：CodyTheWolf (赞：2)

提供一个比较不一样的背包解法：（时空都是$O(n)$)


------------

当第$i$个党派是过剩党派的时候，那么满足不等式：

$k - a_i\leq s/2$

（其中$a_i$是党派的人数，$s$是总人数，$k$是联合政府人数）

这个是很显然的

对于一个确切的$a_i$，我们能知道这个$a_i$，在$k$等于什么的时候，这个$a_i$是可以被选进联合政府的（也就是说肯定不会是过剩党派）

其实就是变形一下:

$a_i \leq k \leq a_i + s/2$

（左边要大于等于$a_i$是因为既然要选$a_i$那肯定有$a_i$个嘛）

考虑暴力，我们只用枚举$k$，然后先用上述的不等式挑选出合适的党派，然后再跑一个01背包，看看能不能刚好凑到$k$人。但是这样肯定复杂度不对。

我们突然发现，好像可以不枚举这个$k$，直接跑01背包，找出最大能到达的背包状态（也就是最大的$k$）不就可以了吗。其实这中间有后效性问题，我们拿样例举例：

```
4
1 3 2 4
```
他们分别对应的最大$k$值是（其实就是$s/2+a_i$）：
```
6 9 7 8
```
在最后一个4的时候，它可以和3组成7，这是合法的，答案也是这个。

但是按照01背包，他和1、2组成7也是可以的，但是这里的问题是，1的最大$k$是6，而现在$k$已经到7了，也就是说其实是非法的。看来如果直接做01背包会有后效性。

现在问题变成了，有一堆物品，有重量，但是某些物品在背包重量大于等于某个值的时候是非法的。要解决这个问题也很简单，~~因为我们的不等式太简单了。~~

只要按“对应的最大$k$值”（其实就是把$a_i$）从大到小排序，再按顺序做01背包就可以消除后效性了。一个物品在塞入背包的时候，之前的物品的最大$k$值肯定比它大，所有这个物品可以随意组合在它自己的最大$k$值内的物品。

最后一个问题就是输出方案的问题：其实我们上面的背包只用记录存不存在就可以了，这个背包是没有类似标准01背包那样还有价钱的。我们只用在背包的权值处记录这个重量其实是加了某个物品$a_i$以后到达的，那我们每次减去$a_i$就可以慢慢回溯到背包的0重量状态。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN=305,MAXT=1e5+5;
pii a[MAXN];//（结构体都懒得写.jpg）
int bag[MAXT];
int ans[MAXN],tail;
int n,s,mx;

signed main(void)
{
	cin>>n;
	for(int i=1,x;i<=n;i++) scanf("%d",&x),s+=x,a[i]={x,i};
	sort(a+1,a+n+1),bag[0]=n+1;
	for(int i=n;i>=1;i--)
		for(int k=s/2+a[i].first;k>=a[i].first;k--)
			if(bag[k-a[i].first]&&!bag[k]) bag[k]=i;
	for(int i=1e5;i>=0;i--)
		if(bag[i]) {mx=i;break;}
	while(mx) ans[++tail]=a[bag[mx]].second,mx=mx-a[bag[mx]].first;
	printf("%d\n",tail);
	for(int i=1;i<=tail;i++) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：Irisany (赞：1)

其他人的方法都好麻烦啊…咱写个简介一点的？

> $n$ 个政党要组成一个联合内阁，每个党都有自己的席位数。 
>
> 现在希望你找出一种方案，你选中的党的席位数要大于总数的一半，并且联合内阁的席位数越多越好。 
>
> 对于一个联合内阁，如果某个政党退出后，其它党的席位仍大于总数的一半，则这个政党被称为是多余的，这是不允许的。
>
> 求最大席位并构造一组解。
>
> $1\leq n\leq 300,1\leq m\leq 10^5$ 。

发现倒着贪心并不是对的…虽然观察数据范围发现 $O(nm)$ 可过，但是一般情况下很难想到要去背包，因为有一个「多余」的限制…

但是发现如果从大到小排完序之后再背包，当前加进去的东西一定是最小的。此时如果出现把这个东西拿出来，剩下的都一定比这个大。所以不难理解这么更新的正确性。

考虑如何记录方案。可以对于每种权值都开一个 `bitset`，对于每种权值，第一次更新的时候顺便更新 `bitset`（根据单调性这样一定是最合法的那个）。那么最后的复杂度就是 $O(nm+\frac{nm}{w})$。注意到这么写的意义在于，通过聚和分析可以得知，对于每个权值 $m$ 至多会与其他的价值 $or$ 一次，所以本质上是 $O(\frac{nm}{w})$ 而不是 $O(\frac{n^2m}{w})$（虽然也能过就是了）。

```cpp
int f[MAXM] ;
int half, sum ;
int i, v, ans, n ; 
bitset <MAXN> b[MAXM] ;
pair<int,int> base[MAXN] ; 

inline bool cmp(pair<int,int> a, pair<int,int> b){ return a.fr > b.fr ;}
int main(){
	cin >> n ; f[0] = 1 ;
	for(i = 1; i <= n ; i ++){
		scanf("%d", &base[i].fr) ;
		sum += base[i].fr, base[i].sc = i ; 
	}
	sort(base + 1, base + n + 1, cmp) ; half = sum >> 1 ;
	for(i = 1; i <= n ; i ++){
		for (v = sum ; v >= base[i].fr ; v --){ 
			if (!f[v] && f[v - base[i].fr])
				b[v] = b[v - base[i].fr], b[v].set(base[i].sc), f[v] = 1 ;    
			if (v > half && f[v] && v - base[i].fr <= half) ans = max(ans, v) ; 
			
		}
	}
	cout << b[ans].count() << '\n' ; 
	for (int i = 1 ; i <= n ; ++ i)
		if (b[ans][i]) cout << i << ' ' ; 
}
```



---

## 作者：Hope2075 (赞：1)

又一道卡空间题

这题只给32MB空间，看起来不是DP，而是贪心

但是如果你真的写贪心，会发现：WA?!

这题状态可能有点难想

首先对每个党派排序

这样在相同人数下，人数最少的党派要有最多人数

考虑```dp[i][j]```表示已经考虑前i个党派，现在共有j个人能得到什么状态

这里合法的定义是能拼凑出这个数

如果数值为0，表示非法

如果为1，表示不选第i个党派

如果为2，则表示选这个党派

转移时，首先考虑不选这个党派

然后考虑选这个党派，求出选后的人数转移就行

如果考虑选当前党派，就判断当前状态是否为合法解，如果合法，与当前最优解比较，取更优

在转移过程中，上一个党派是否选并没有影响，所以只要能凑出来就可以转移

最后利用记录的信息，在dp数组里跳就能得到方案

这就是前面记录1和2的原因，可以把dp数组和前驱数组压缩到一起

也可以试试按位压缩省空间

这样数组大小不会爆空间，能够通过

代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=302,M=100002;
struct group{
	int num,id;
};
bool operator<(group a,group b){
	return a.num>b.num;
}
group list[N];
int n;
char pr[N][M];
int termid,termcnt;
int sum;
int cnt;
int ans[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>list[i].num;
		list[i].id=i;
		sum+=list[i].num;
	}
	sort(list+1,list+n+1);
	pr[0][0]=1;
    //初始状态，可以看出不会导致后面跳的时候出问题
	for(int i=1;i<=n;i++){
		for(int j=0;j<=sum;j++){
			if(pr[i-1][j]){
				pr[i][j]=1;
			}else{
				pr[i][j]=0;
			}
		}
		for(int j=0;j<=sum-list[i].num;j++){
			if(pr[i-1][j]){
				pr[i][list[i].num+j]=2;
				if(j<=sum/2&&list[i].num+j>sum/2){
					if(termcnt<list[i].num+j){
						termid=i;
						termcnt=list[i].num+j;
					}
				}
			}
		}
	}
	for(int i=termid,j=termcnt;i>0;i--){
		if(pr[i][j]==2){
			ans[cnt++]=list[i].id;
			j-=list[i].num;
		}
        //否则表示没选
	}
	cout<<cnt<<endl;
	for(int i=0;i<cnt;i++){
		cout<<ans[i]<<" ";
	}
	cout<<endl;
}
```

---

## 作者：huangxuhan (赞：0)

这道题做法跟[这道题](https://www.luogu.org/problem/P4394)很像，~~双倍经验？~~，可以具体参考这道题，不同的是输出具体方案。输出方案我们利用新的数组$mem[i][j]$表示前$i$个人中选取的填满$j$个背包最后一个选取的是哪个物品，最后我们进行一次递归，利用$vector$从前往后记录每次选取的方案就好，至于递归的方法，每次找$dg([i-1][j-v[i]],j-v[i])$即可  

------------

于是我们就被卡空间了  
这里我们借题解的方案用 $char$型定义$mem$数组，就可过


------------
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch>'9'||ch<'0');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
vector<int> q;
struct data{
	int v,h;
}a[310];
int comp(const data a,const data b)
{
	return a.v>b.v;
}
int n,m,f[100010],sum;
char mem[310][100010];
void dg(char i,int j)
{
	if (i==0) return ;
	dg(mem[i-1][j-a[i].v],j-a[i].v);	
	q.push_back(a[i].h);
	return;
}
int main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		a[i].h=i;
		a[i].v=read();
		sum+=a[i].v;
	}
	sort(a+1,a+n+1,comp);
	f[0]=0;
	int ans=0,book1=0,book2=0;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=sum;j++) mem[i][j]=mem[i-1][j];//不选i件物品
		for (int j=sum;j>=a[i].v;j--)//选
		{
			if (f[j]<f[j-a[i].v]+a[i].v)
			{
				f[j]=f[j-a[i].v]+a[i].v;
				mem[i][j]=i;
			}
            //更新答案
			if (ans<f[j]&&f[j]>sum/2&&f[j]-a[i].v<=sum/2)
			{
				ans=f[j];
				book1=i;
				book2=j;
			}
		}
	}
    //递归
	dg(book1,book2);
	cout<<q.size()<<endl;
	for (int i=0;i<q.size();i++) cout<<q[i]<<" ";
	cout<<endl;
}
```


---

