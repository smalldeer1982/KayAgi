# Running with Obstacles

## 题目描述

A sportsman starts from point $ x_{start}=0 $ and runs to point with coordinate $ x_{finish}=m $ (on a straight line). Also, the sportsman can jump — to jump, he should first take a run of length of not less than $ s $ meters (in this case for these $ s $ meters his path should have no obstacles), and after that he can jump over a length of not more than $ d $ meters. Running and jumping is permitted only in the direction from left to right. He can start andfinish a jump only at the points with integer coordinates in which there are no obstacles. To overcome some obstacle, it is necessary to land at a point which is strictly to the right of this obstacle.

On the way of an athlete are $ n $ obstacles at coordinates $ x_{1},x_{2},...,x_{n} $ . He cannot go over the obstacles, he can only jump over them. Your task is to determine whether the athlete will be able to get to the finish point.

## 样例 #1

### 输入

```
3 10 1 3
3 4 7
```

### 输出

```
RUN 2
JUMP 3
RUN 1
JUMP 2
RUN 2
```

## 样例 #2

### 输入

```
2 9 2 3
6 4
```

### 输出

```
IMPOSSIBLE
```

# 题解

## 作者：OIerJiang_1017 (赞：3)

## [CF637D 题目传送门](https://www.luogu.com.cn/problem/CF637D)

## 题目大意
运动员在一条可以看作是数轴的跑道上跑步，从坐标为 $x_{start}=0$ 的起点开始，跑向坐标为 $x_{finish}=m$ 的终点。跑道上设置了 $n$ 个障碍，放置的位置坐标分别为。运动员只能通过跳跃跨过这些障碍，每次跳跃，运动员首先需要进行一段不少于 $s$ 米的助跑，每次跳跃的距离不超过 $d$ 米。为了跨越某个障碍物，运动员必须严格地落在该障碍物右侧的第一个点上。你的任务是判断运动员是否能够到达终点。

## 解决方法
可以发现，跑道上有 $n$ 个障碍，运动员需要一定的助跑距离才能跳跃，所以只要让这个助跑距离最大，就更有机会跳过去，因此本题思路是贪心。很容易想到，每次在障碍的前一个单位跳跃，在障碍的后一个单位落下，可以使中间没有障碍的那一段助跑距离最大。当这样求出所有障碍之间的最大助跑距离后，仍有一些障碍之间的助跑距离不够，可以将这种障碍合在一起考虑。

## 注意事项
$2 \leq m,s,d \leq 10^9$，需要开 `long long`。

---

## 作者：zym20249_ (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF637D)
## 题意
运动员在一条可以看作是数轴的跑道上跑步，从坐标为 $ x_{start}$ 的起点开始，跑向坐标为 $x_{finish}$ 的终点。跑道上有 $n$ 个障碍，位置坐标为 $x_1$ 到 $x_n$。运动员要跳跃跨过这些障碍，每次跳跃，运动员首先需要进行一段助跑，每次跳跃的距离不能超过 $d$ 米。为了跨越某个障碍物，运动员必须落在该障碍物右侧。你来是判断运动员是否能够到达终点。
## 思路
如果两个障碍之间的距离不够分次跳跃，则要一次性跳过这两个障碍
贪心，尽量跑少跳，所以我们跳过每个区后都是停在 $R_i+1$ 的位置，这样就会有更大的空间助跑。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
const int maxn=4e5+10;
using namespace std;
ll n,a[maxn],nw,tot,N,L[maxn],R[maxn],s,d,m,as[maxn];
ll read()
{
	ll ret=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
void anso()
{
	for(int i=1;i<=N;i++)
		if(R[i]-L[i]+2>d)
		{
			puts("IMPOSSIBLE");
			return;
		}
	for(int i=1;i<=N;i++)
	{
		as[++tot]=L[i]-nw-1;nw=R[i]+1;
		as[++tot]=R[i]-L[i]+2;
	}
	for(int i=1;i<=tot;i+=2) printf("RUN %lld\nJUMP %lld\n",as[i],as[i+1]);
	if(nw<m) printf("RUN %lld",m-nw);
}
int main()
{
	n=read();
	m=read();
	s=read();
	d=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	a[0]=-(1<<30);
	if(a[1]<=s)
	{
		puts("IMPOSSIBLE");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==a[i-1])continue;
		if(a[i]-a[i-1]-1>s)L[++N]=a[i],R[N]=a[i];
		else R[N]=a[i];
    }
	anso();
	return 0;
}

``````

---

## 作者：LlLlCc (赞：3)

首先，如果两个障碍之间的距离不够助跑跳跃，那么肯定要一次性跳过这两个障碍，即可以和成一个区间

$n$个障碍物预处理，我们已经得出$N$个区间每个的$L_i,R_i$

贪心思想，能跑就跑，不能跑再跳，所以我们跳过每个区后都是停在$R_i+1$的位置，这样就会有更大的空间助跑

就按这种贪心的思想，模拟即可

## code
```
#include<bits/stdc++.h>
#define maxn 400005
#define ll long long
using namespace std;
ll n,a[maxn],Now,tot,N,L[maxn],R[maxn],s,D,m,Ans[maxn];
inline ll read(){
	ll ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void Solve(){
	for (int i=1;i<=N;i++) if (R[i]-L[i]+2>D){puts("IMPOSSIBLE");return;}
	for (int i=1;i<=N;i++){
		Ans[++tot]=L[i]-Now-1;Now=R[i]+1;
		Ans[++tot]=R[i]-L[i]+2;
	}
	for (int i=1;i<=tot;i+=2) printf("RUN %lld\nJUMP %lld\n",Ans[i],Ans[i+1]);
	if (Now<m) printf("RUN %lld",m-Now);
}
int main(){
	n=read(),m=read(),s=read(),D=read();
	for (int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);a[0]=-(1<<30);
	if (a[1]<=s){puts("IMPOSSIBLE");return 0;}
	for (int i=1;i<=n;i++){
	  if (a[i]==a[i-1]) continue;
	  if (a[i]-a[i-1]-1>s) L[++N]=a[i],R[N]=a[i];
	  else R[N]=a[i];
    }
	Solve();
	return 0;
} 
```


---

## 作者：water_tomato (赞：3)

实际已有的题解已经把大体思路阐述出来了，但我认为缺少很多对细节的解答，故再写了一篇。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF637D)

大体题意不再阐述，这里有几点需要注意，首先，跳跃后到达的那一格是**不算**助跑距离的。其次，能跳跃 $d$ 个单位不是跨越过 $d$ 个单位，而是在当前位置的基础上前进 $d$ 个单位。

## 解析

首先看到数据范围，很容易想到此题是 dp 或者贪心。

然后我们发现，跑道上有若干个障碍，而运动员想要跳跃需要一定的助跑距离，那我们只要让这个助跑距离尽可能大，就更有机会跳过去，因此我们确定这道题的思路为贪心。

我们很容易想到，每次在障碍的前一个单位跳跃，在障碍的后一个单位落下，可以使中间没有障碍的那一段助跑距离尽可能大。当我们这样求出所有障碍之间的最大助跑距离后，仍然有一些障碍之间的助跑距离是不够的，我们可以将这种障碍**合在一起**，作为一个大障碍考虑。

大体思路如上，但作为一道 CF 的毒瘤题，我们接着还需要通过部分代码来说明几个注意点。

### 预处理

``` cpp
scanf("%lld%lld%lld%lld",&n,&m,&s,&d);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+1+n);
	if(a[1]-1<s){
		printf("IMPOSSIBLE\n");
		return 0;
	}
	a[0]=-(1e9+7);
	for(int i=1;i<=n;i++){
		if(a[i]-a[i-1]-1>s) e[++cnt].l=a[i],e[cnt].r=a[i];
		else e[cnt].r=a[i];
	} 
```

这里有几个非常重要的注意点！一不小心就错了。

首先，我们预处理是从 $1$ 号障碍开始的，因此如果刚开始助跑距离就不够，直接输出 `IMPOSSIBLE`  即可。

其次，一定要把 $a_0$ 的初值设为无穷小，因为第一个障碍一定要形成一个独立的大障碍，不可能也不能存在其与 $a_0$ 相连的情况。

另外别忘了障碍不一定是有序的，需要先排序。

### 寻找答案

```cpp
for(int i=1;i<=cnt;i++)
		if(e[i].r-e[i].l+1>=d){
			printf("IMPOSSIBLE\n");
			return 0;
		}
	int now=0;
	for(int i=1;i<=cnt;i++){
		if(e[i].l!=1){
			printf("RUN %lld\n",e[i].l-1-now);
			printf("JUMP %lld\n",e[i].r+1-(e[i].l-1));
			now=e[i].r+1;
		}
	}
	if(now<m)  printf("RUN %lld\n",m-now);
```

这部分相对简单，主要注意当障碍长度等于 $d$ 时，是无法跳跃过去的（在题意中阐述了原因）；以及如果最终无法到终点，还需要跑几步就可以了。

代码都在上边呈现了，不再赘述。

---

## 作者：cqbztz2 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF637D)

# 思路：

首先将点排序，两点之间距离太短不够起跳的两点放在一个区间，这样问题转化为跨过若干个区间。

如果能跨过某一个区间，那么一定有办法停在 $ v+1 $ ，就是区间右端点 $ +1 $ 的位置，而且这样不会比最优解差。

转化出的区间一个一个顺次跨，这样也不会比最优解差。

# 代码：

~~(写的很麻烦但 $ AC $ 了)~~

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,m,r,j,a[200005],tot=1,cnt;
  struct nobe{
      int w,v;
  }b[200005];
  bool check(){
      b[0].v=-1;
      for(int i=1;i<=n;i++){
          if(r>=b[i].w-(b[i-1].v+1)||b[i].v-b[i].w+2>j ){
              return false;
          }
      }
      return true;
  }
  void print(int x,int t){
      if(x==0){
          cout<<"RUN "<<b[1].w-1<<endl;
          return;
      }
      print(x-1,b[x].w-1);
      cout<<"JUMP "<<b[x].v+1-b[x].w+1<<endl;
      if(b[x].v+1!=t){
          cout<<"RUN "<<t-b[x].v-1<<endl;
      }
  }
  int main(){
      cin>>n>>m>>r>>j;
      for(int i=1;i<=n;i++){
          cin>>a[i];
      }
      sort(a+1,a+n+1);
      while(tot<=n){
          b[++cnt].w=a[tot];
          while(tot<n&&a[tot+1]-(a[tot]+1)<=r){
             tot++;
          }
          b[cnt].v=a[tot];
          tot++;
      }
      n=cnt;
      if(check()==false){
          cout<<"IMPOSSIBLE";
          return 0;
      }
      print(n,m);
      return 0;
  }
```


---

