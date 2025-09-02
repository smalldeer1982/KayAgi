# 环形跑道 Just Finish it up

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2034

[PDF](https://uva.onlinejudge.org/external/110/p11093.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11093/4a8ff08dc895659b141306f5ab2159a69456d4a3.png)

## 样例 #1

### 输入

```
2
5
1 1 1 1 1
1 1 2 1 1
7
1 1 1 10 1 1 1
2 2 2 2 2 2 2```

### 输出

```
Case 1: Not possible
Case 2: Possible from station 4```

# 题解

## 作者：ExcaIibur (赞：7)

这道题是刘汝佳紫书上**高效算法设计**一章中的例题，题意非常清楚，就是找最小能够满足跑完全程的加油站编号，算法就是贪心+模拟。

然而，数据范围达到了1e5，难点在于如何优化时间复杂度。

根据题意和实际情况，我们很容易得到“**如果总油量不足以支持跑完全程，就一定无解**”的结论。

那么，是否存在**总油量>=所需油量但仍然无解**的情况呢？我们可以这样想：由于走的是环形跑道，我们总可以找到一个起点使得油量足够支撑跑完全程，因为如果不存在这样的点，则把每一个点当作起点都会有ai+...+aj<bi+...+bj出现，这样的话就有a1+a2+...+an<b1+b2+..+bn，与我们的假设矛盾，所以**这种情况不存在**。

再考虑有解的情况，基于最直接的模拟，我们尝试从1号加油站枚举，遇到不能到达的情况就直接退出枚举下一个，时间复杂度为**O（n^2）**,TLE。

如何优化呢？我们在计算中发现：从枚举的起点到不能到达站点之间的数据信息蕴含在了我们的判断条件（能否走完这段路程）中，能不能“**把这些信息分离出来从而省略判断一些点**”呢？我们考虑：去掉起点以第二个点为起点，由于原先的起点一定满足ai>=bi，所以从现在的起点出发仍不能通过上一个中断点，更别说一些中间点还到不了此时的中断点呢，下面用式子来说明：

假如我们从1号点出发，到3号点油量不能支撑，有以下关系式：

A: **a1>=b1**

B: **a1+a2>=b1+b2**

C: **a1+a2+a3<b1+b2+b3**

显然，由A式和C式可以推出**a2+a3<b3+b3**，由B式和C式可以推出**a3<b3**(~~不推也知道~~）

也就是说，**一旦出现不能到达的情况时，经过的这些点都不可能作为起点了**，时间复杂度可以优化到**O（n）**。

另外，当确定答案时我们需要遍历所有n个点吗？回答是不需要。我们只用判断从1-n出发能否到第n点就行了。（可别忘了我们的前提——**总油量>=所需油量！**）

献上我自以为比其他题解更简洁的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int a[maxn],b[maxn],now; 
int main(){
	int t,n;
	scanf("%d",&t);
	for(int k=1;k<=t;++k){
		scanf("%d",&n);
		now=0;
		for(int i=1;i<=n;++i)
			scanf("%d",a+i),now+=a[i];
		for(int i=1;i<=n;++i)
			scanf("%d",b+i),now-=b[i];
		printf("Case %d: ",k);
		if(now<0)printf("Not possible\n");
		else{
			int ans;
			for(int i=1;i<=n;){//这里的i代表起点
				now=0,ans=i;
				for(;now>=0&&i<=n;++i)//这里的i代表以后的点
					now+=a[i]-b[i];
			}
			printf("Possible from station %d\n",ans);
		}
	}
	return 0;
}
```












---

## 作者：_byta (赞：3)

声明：这题本人未在洛谷提交，但在 uva 主站 AC 了，所以代码正确性有保证。

首先我们对于所有加油量小于所有耗油量的情况可以直接特判无解。

接下来考虑其他情况，我们可以从一开始向后枚举。那枚举到什么时候结束呢，入果枚举到形成环时结束，复杂度为 $n^2$，显然过不了，事实上当我们到达 $n$ 时就可以结束了，因为 $n$ 后面的点我们在之前就枚举过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[N], c[N];
inline int read()
{
    register int x = 0, f = 1;
	char ch = getchar();
    while(!isdigit(ch))
	{
		if(ch == '-') f=-1;
		ch = getchar();
	}
    while(isdigit(ch))
	{
		x=(x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
    return x * f;
}
int main()
{
    int T = read();
    while(T--)
    {
    	bool flag = 0;
    	t++;
    	n = read();
    	sum = 0;
    	for(int i = 1; i <= n; i++)
    	{
    		a[i] = read();
    		sum += a[i];
		}
		for(int i = 1; i <= n; i++)
		{
			b[i] = read();
			sum -= b[i];
		}
		printf("Case %d: ",t);
		if(sum < 0) 
		{
			printf("Not possible\n");
			continue;
		}
		sum = 0;
		for(int i = 1; i <= n; i++)
		{
			ans = i;
			sum = 0;
			for(int j = i; j <= n; j++)
			{
				sum = sum + a[j] - b[j];
				if(sum <= 0) break;
				if(j == n)
				{
					cout << "Possible from station " << i << endl;
					flag = 1;
					i = n + 3;
				}
			}
		}
		if(!flag) printf("Not possible\n");
	}
    return 0;
}


```




---

## 作者：ybe2007 (赞：2)

一题多解。

第一种方法比较直观而且暴力，其关键在于转化题意。此题中的关键，在于对每一个起点 $i$ 的判定。如果暴力 $O(n)$ 扫一遍，总时间复杂度就会是 $O(n^2)$，超时，因此考虑转化题意后用数据结构优化。

（下述 $p$ 表示 $p$ 原意义的前缀和，$q$ 同理）

我们可以发现，对于一个起点 $i$ ，如果它满足题意，那么就有：

1. $\forall j\in \left[i,n\right]$，$p_j-p_{i-1}\geq q_j-q_{i-1}$，将常量与变量分别移到不等式两边，就有$p_j-q_j\geq p_{i-1}-q_{i-1}$，也就是说对于所有在 $i$ 右边的点都能顺利开到下一个点。数学上来看，区间内所有数都满足大于等于的条件，那么就要求最小值也满足，因此我们只需要用线段树来维护即可。

2. $\forall j\in \left[1,i-1\right]$，$p_n-p_{i-1}+p_j\geq q_n-q_{i-1}+q_j$。式子意义、化简，以及维护方法均与上同，不再赘述。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n;
int a[N],b[N],P[N],Q[N];
struct Seg
{
	int val[N<<2];
	void build(int p,int l,int r)
	{
		val[p]=1e9;
		if(l==r)
		{
			val[p]=P[l]-Q[l];
			return ;
		}
		int mid=l+r>>1;
		build(p<<1,l,mid),build(p<<1|1,mid+1,r);
		val[p]=min(val[p<<1],val[p<<1|1]);
	}
	int ask(int p,int l,int r,int L,int R)
	{
		if(L>R) return 1e9;
		if(L<=l&&R>=r) return val[p];
		int mid=l+r>>1,res=1e9;
		if(L<=mid) res=min(res,ask(p<<1,l,mid,L,R));
		if(R>mid) res=min(res,ask(p<<1|1,mid+1,r,L,R));
		return res;
	}
}t1;
int main()
{
	int T;
	scanf("%d",&T);
	for(int rnd=1;rnd<=T;rnd++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),P[i]=P[i-1]+a[i];
		for(int i=1;i<=n;i++) scanf("%d",&b[i]),Q[i]=Q[i-1]+b[i];
		t1.build(1,1,n);
		bool flag=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]<b[i]) continue;//小小的优化 
			int Rmn=t1.ask(1,1,n,i,n);
			if(Rmn<P[i-1]-Q[i-1]) continue;
			int Lmn=t1.ask(1,1,n,1,i-1);
			if(Lmn<Q[n]-Q[i-1]-P[n]+P[i-1]) continue;
//			printf("i=%d Lmn=%d Rmn=%d\n",i,Lmn,Rmn);
			printf("Case %d: Possible from station %d\n",rnd,i);
			flag=1;
			break;
		}
		if(!flag) printf("Case %d: Not possible\n",rnd);
	}
}
```

第二种方法也是源于暴力的思考，为了保证时间复杂度，我们希望能够**在线性扫的同时排除不可能作为起点的那些点**。恰好在本题中，有一个显然的结论，也就是：从点 $i$ 出发，如果在点 $j$ 没油了，那么$\left[i,j\right]$内的所有点均不可能作为起点。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n;
int a[N],b[N],st;
int work(int x,int now,int dep)
{
	if(x>n) x-=n;
	if(now<0) return x;
	if(dep==n) return -1;
	return work(x+1,now+a[x]-b[x],dep+1);
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int rnd=1;rnd<=T;rnd++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) scanf("%d",&b[i]);
		st=1;
		int ans=-1;
		while(1)
		{
			int ed=work(st,0,0);
			if(ed==-1)
			{
				ans=st;
				break;
			}
			if(ed<=st) break;
			st=ed;
		}
		if(ans==-1) printf("Case %d: Not possible\n",rnd);
		else printf("Case %d: Possible from station %d\n",rnd,ans);
	}
}
```

第二种方法要比第一种快，理论与实践皆是如此。

---

## 作者：伟大的王夫子 (赞：2)

这道题根本就只需暴力就可以解决了

记 $s(l,r)=\sum_{i=l} ^r a_i- b_i$

对于一个 $i$，如果以他当起点是可行的，这当且仅当

 $\forall j \in [i, n], s(i,j) \ge0$

且 $\forall j \in [1, i - 1], s(i,n) + s(1, j) \ge 0 $。

其中对于 $s(i, j)$ 与 $s(1, j)$，如果用一个 st 表维护其最小值，每次将最小值取出进行判断，如果可行即可。这样就可以做到 $O(n \log n)$ 的复杂度，且容易想到。面对此题的测试数据，该算法完全足够。当然，因为有多组数据，每次处理完一组数据之后，应记得清空。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100010], b[100010], s[100010], f[100010][20];
int ask(int l, int r) {
	if (l > r) return 1e9;
	int k = log2(r - l + 1);
	return min(f[l][k], f[r - (1 << k) + 1][k]);
}
int main() {
	int T, num = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (register int i = 1; i <= n; ++i) scanf("%d", b + i), s[i] = s[i - 1] + a[i] - b[i], f[i][0] = s[i];
		for (register int j = 1; j <= 20; ++j)
			for (register int i = 1; i + (1 << j) - 1 <= n; ++i)
				f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		bool flag = 0;
		for (register int i = 1; i <= n; ++i) {
			int val = ask(i, n);
			if (val < s[i - 1]) continue;
			val = ask(1, i - 1);
			if (val + s[n] - s[i - 1] < 0) continue;
			printf("Case %d: Possible from station %d\n", ++num, i);
			flag = 1;
			break;
		}
		if (!flag) printf("Case %d: Not possible\n", ++num);
	}	
}
```
	

---

## 作者：metrixgo_caozhendi (赞：1)

看到这题第一反应就是枚举站点，因为要你去求出发点嘛。所以最简单的方法就是暴力枚举站点，然后递归查看能否绕一圈回到起点。

但是很显然，$O(n^2)$ 的复杂度在 $n\le10^5$ 的前提下肯定会 TLE，所以我们要优化一下算法。

首先让我们观察一下题目，要求的是找到一个最小的站点出发，一直往右走，走到尽头就回到最左边，直至返回出发点。若没找到则输出 "Not possible"。这该怎么优化呢？有一个很重要的结论：


------------
如果 $a$ 站点**无法到达** $b$ 站点 $(a<b)$，那么对于任意的 $a<i<b$，$i$ 站点均不可能到达
$b$ 站点。

------------
这条结论也应该很明显了，如果你不能到后面的一个点，那么你从中间出发也不能到后面的点，因为总油量永远比总需求要少。这样，我们可以在每次没油的时候记录一下地点，下次递归时就从这个地点递归。

几个注意事项：

1 递归出口应该依次是有没有走到尽头，有没有没油，有没有走完，否则顺序乱了会判断错误。

2 如果没油的地点是在目前递归的地点之前，说明已经绕了一圈并且还没走到。这种情况就说明后面的地点都不可能走到。所以直接输出 "Not possible" 即可。

代码如下，先别急着抄，跟着注释走一遍。代码亲测 AC。
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,n,t,gas[100005],need[100005],cnt,pd;

int drv(int start,int remain,int step)//递归函数
{
 if(start>n) start=1;//如果走到尽头了就回到1

 if(remain<0) return start;//走到一半没油了就说明这个站之前都不可能是起点

 if(step>n) return -114514;//走完返回负数

 return drv( start+1,remain+gas[start]-need[start],step+1 );//进行递归
}
int main()
{
cin>>t;
for(cnt=1;cnt<=t;cnt++){
cout<<"Case "<<cnt<<": ";//注意空格格式
cin>>n;
for(i=1;i<=n;i++) cin>>gas[i];  //输入每个站点可以加多少油

for(i=1;i<=n;i++) cin>>need[i];  //每个站点到下一站耗油

for(i=1;i<=n;i++)//枚举站点，考虑从i站点出发能否绕一圈
{
  pd=drv(i,0,1);//递归
    if(pd<0)//如果记录走完一圈了就输出
     {
      cout<<"Possible from station "<<i<<endl;
      break;
     }
    if(pd<=i){break;}//转过一圈已经扫过的还走不通直接退出
  i=pd-1;//如果没走到就从没油的点和出发点考前的开始走，注意要-1抵消++
}
 if(pd>=0)//没有路径可以到达，输出不可能
 {cout<<"Not possible"<<endl;}

}
return 0;
}
```

---

## 作者：Lizj (赞：1)

## 题意分析

题意：一条环形赛道上有 $n$ 个加油站，第 $i$ 个加油站可以加油 $p_i$ 加仑，而从第 $i$ 个加油站开到第 $i+1$ 个加油站需要消耗 $q_i$ 加仑汽油，在任意一个加油站都可以加油；求可以跑完赛道的编号最小的加油站，如无解，输出 `Not possible`。

分析：因在每一站都加满油的策略不会更坏，所以在所有加油站的油相加仍小于跑完跑道需耗的油时，即：

$$\sum_{i=1}^{n}p_i<\sum_{i=1}^{n}q_i$$

问题无解，无论从哪个站出发，都无法跑完。此时，输出 `Not possible`。

如问题有解，可以枚举每一站，再从每一站出发，模拟当前方案是否合法，如合法，输出当前站点，跳出循环；但可以优化，由于不合法情况只会在某一站发生，所以可以在枚举站时在上一站的基础上继续向后枚举，省去了 $1\sim{i-1}$ 的枚举。

每组问题时间复杂度不足 $O(n^2)$，由于有 $T$ 组数据，总时间复杂度为 $O(Tn^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int p[100010],q[100010];
int main(){
	int T,cas=0;
	cin>>T;
	while(T--){
		int n,sum=0;
		bool f=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>p[i];
			sum+=p[i];
		}
		for(int i=1;i<=n;i++){
			cin>>q[i];
			sum-=q[i];
		}
		cas++;
		cout<<"Case "<<cas<<": ";
		if(sum<0){
			cout<<"Not possible"<<endl;	//判断无解
			continue;
		}
		sum=0;
		f=0;
		for(int i=1;i<=n;i++){	//枚举答案
			sum=0;
			for(int j=i;j<=n;j++){	//模拟是否合法当前答案
				sum+=(p[j]-q[j]);
				if(sum<=0)
					break;
				if(j==n){
					cout<<"Possible from station "<<i<<endl;
					i=n+1;	//跳出循环
					f=1;
				}
			}
		}
		if(!f){
			cout<<"Not possible"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Snowlanuck (赞：1)

题目地址:https://www.luogu.com.cn/problem/UVA11093

紫书分析原文

```
考虑1号加油站，直接模拟判断它是否为解。如果是，直接输出；如果不是，说明在模
拟的过程中遇到了某个加油站p，在从它开到加油站p+1时油没了。这样，以2, 3,…, p为起点
也一定不是解（想一想，为什么）。这样，使用简单的枚举法便解决了问题，时间复杂度
为O(n)。
```

按照这个思路我写下了程序

参考代码

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 50;

int T, N, A[maxn], B[maxn];

bool isOK(int x, int &last)
{
	last = x;//last是不成功情况下走的最远的位置
	for (int i = 0, Oil = 0, index; i < N; i++)
	{
		index = (x + i) % N;
		Oil += A[index];
		if (Oil < B[index]) { last = index; return false; }
		Oil -= B[index];
	}
	return true;
}

int main()
{
	cin >> T;
	for (int cnt = 1; cnt <= T; cnt++)
	{
		printf("Case %d: ", cnt);
		cin >> N;
		for (int i = 0; i < N; i++) { cin >> A[i]; }
		for (int i = 0; i < N; i++) { cin >> B[i]; }
		int ans = -1;
		for (int i = 0, last; i < N; i++)
		{
			if (isOK(i, last)) { ans = i + 1; break; }
			if (i == N - 1 || last < i) { break; }
			i = last;//不成立就跳过之前走过的路
		}
		if (ans != -1)
			cout << "Possible from station " << ans << endl;
		else
			cout << "Not possible" << endl;
	}

	return 0;
}
```


---

## 作者：念古兰 (赞：1)

    首先，我们一定要贪心地走，什么意思呢？就是说，我们到一个点就一定要把油全部加上去，这样一定不会更差
    可以知道，从第1个站开始，遇到一个不能过的，在中间选择任何一个站都是不可能是答案的，所以我们只需要从第一个开始，走一遍，看一下是否能过，不能过的话就排除掉中间的，然后再继续检验就可以了；  
然后呢，由于说我们走一圈时O(n)的，而且找到一个第一个不可以通过的站与继续找不可以通过的的时间复杂度总和为O(n)  
因此，这样就可以在O(n)的复杂度内解决了  
最后就是特别丑的代码了：  
~~由于作者太懒~~为了锻炼读这篇题解的同学的阅读能力，本代码不加注释，大家自己看完思路后写代码之后如果wa了再食用更佳
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+10;
int a[maxn],n;
int check(int k)
{
	ll sum=0;
	for(register int i=0;i<n;i++)
	{
		int tmp=(k+i)%n;
		if(tmp == 0) tmp=n;
		sum+=a[tmp];
		if(sum<0) return tmp;
	}
	return -1;
}
int main()
{
	int t=0,kase=0,flag=0;
	scanf("%i",&t);
	while(t--&&++kase)
	{
		memset(a,0,sizeof(a));
		scanf("%i",&n);
		for(register int i=1;i<=n;i++) scanf("%i",a+i);
		for(register int i=1;i<=n;i++) scanf("%i",a),a[i]-=a[0];
		int last=0,ans=0;
		bool ok=0;
		for(register int i=1;i<=n;i++)
		{
			int k=check(i);
			if(k == -1) {ok=1;ans=i;break;}
			else
			{
				if(k>last) last=i,i=k;
				else break;
			}
		}
	if(!ok) printf("Case %i: Not possible",kase);
	else    printf("Case %i: Possible from station %i",kase,ans);
     putchar('\n');
}
	return 0;
}
```


---

## 作者：lmy_2011 (赞：0)

这题跟今年[第 $2$ 题](https://www.luogu.com.cn/problem/P9749)有十分相像，是一道贪心。

我们分两种情况讨论，有解和误解。

### 有解
最基本的做法当然是枚举每个站点啦，但不过时间复杂度明显不合格，考虑极限数据，$n$ 为 $10^5$，尽管 $T$ 只有 $25$，但枚举过程还要 $\mathrm{O}(n^2))$ 的时间复杂度，根本行不通。

再考虑优化，我们枚举时可以考虑逆向思维，从 $i$ 向 $n$ 枚举，这样每次无需枚举多次，只需要从原有的价值 $sum$，也就是从 $1$ 到 $i-1$ 的价值，然后在里面枚举就行了。

注意停止条件，只需要等他枚举完，根本不需要多优化。
### 无解
无解的情况就是当前站点 $i$ 可加的油量达不到 $i+1$ 站点，那么就输出 ``Not possible``。

### 代码
下面给出大致的代码框架，请按理解写代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int p[100005], q[1000005];
void work(int x)
{
	int n, cntp = 0, cntq = 0;
	cin >> n;
	cout << "Case " << x <<": ";
	for (int i = 1 ; i <= n ; i++)//边输入边统计能加的油 
	{
		cin >> p[i];
		/**/
	}
	for (int i = 1 ; i <= n ; i++)//边输入边统计要耗的油 
	{
		cin >> q[i];
		/**/
	}
	if(/**/)//先看总体是否达到 
	{
		cout<<"Not possible\n";	
		return ;
	}
	for(int i = 1 ; i <= n ; i++)
	{
		int cnt = 0; 
		for(int j = /**/ ; j <= n ; j++)
		{
			int tmp = /**/;//当前油量，防止达不到 
			cnt += tmp;
			if (/**/)
			{
				cout<<"Not possible\n";
				return ;
			}
		}
		cout << "Possible from station " << i << "\n";
	}
	cout<<"Not possible\n";
	return ;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for (int i = 1 ; i <= t ; i++)
	{
		work(i);
	}
	return 0;
}

```


---

