# Football

## 题目描述

在某一届的“代码杯”中，举办方决定让各个队伍踢踢足球。所有参赛者被分为$n$个队，进行了几场比赛，每两个队踢一场。


裁判帕维尔在比赛时睡着了，醒来后，他发现比赛已经结束了，各队都想知道所有比赛的结果。

帕维尔不想让任何人发现他在睡觉，他迫切知道比赛的结果（因为他是裁判）。因此，他询问了所有的球队，每支球队击败其他球队正好$k$次。帮助帕维尔找出符合条件的所有比赛结果可能性，如果不可能，输出$-1$。

## 样例 #1

### 输入

```
3 1
```

### 输出

```
3
1 2
2 3
3 1
```

# 题解

## 作者：如履薄冰 (赞：3)

# 解法
这道题是一道**图论**题，数学问题中的比赛问题也是使用类似的图解决的。我们可以将所有球队的比赛状态转化成一个有向图。举个例子，如果图中的甲结点通向乙结点，那么甲就输给了乙。好啦，接下来我们来分析一下有解与无解两种情况的处理方式吧。
## 无解
如果这个图的边数大于这个图对应的完全图的边数，那么无解，直接输出 $-1$。
## 有解
我们只需要把一个对应的点进行配对，这里我们要考虑配对溢出的情况。如果溢出，需要取模。
# 代码
这个部分请大家自行完成。

---

## 作者：linan04195 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF417C)
---
## 思路
读完题目，我们可以发现这题是一道图论题。

图的边数为 $\frac{n \times (n-1)}{2}$ 条，而方案数恰好等于 $\frac{n \times (n-1)}{2}$，就是 $n \times k$ 个方案,每个点 $j$ 都向区间 $[j+1,j+k]$ 里所有点连接，每个点的出度都是 $k$，不会出现重边，直接构造取模输出。

如果 $n \times k$ 比 $\frac{n \times (n-1)}{2}$ 大，则无解。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k;

int main(){
	cin>>n>>k;
	
	if(n*k>n*(n-1)/2) cout<<-1;//判断无解
	
	else{
		printf("%d\n",n*k);
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=k;j++){
				if((i+j)%n==0) printf("%d %d\n",i,n);
				else printf("%d %d\n",i,(i+j)%n);
			}
		}	
	}
}
```

---

## 作者：loser_seele (赞：1)

发现本题题意就是构造一张每个节点的出度都为 $ k $ 的有向图（两点之间最多只能有一条有向边）。

如果边数比完全图的边数还要多显然是无解的，直接输出无解即可。

否则可以构造一张图，每个点 $ i $ 都向区间 $ [i+1,i+k] $ 里所有点连边，这样每个点的出度都是 $ k $，且不会出现边重复的问题，于是这个问题就解决了。注意如果点的编号超过范围需要取模。

时间复杂度 $ \mathcal{O}(nk) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int mymod(int a,int n)
{
if(a%n==0)
return n;
return a%n;
}
int main()
{
int n,k;
cin>>n>>k;
if(n*k>n*(n-1)/2)
cout<<-1;
else
{
cout<<n*k<<'\n';
for(int i=1;i<=n;i++)
for(int j=1;j<=k;j++)
cout<<i<<' '<<mymod((i+j),n)<<'\n';
}
}
```


---

## 作者：XXh0919 (赞：1)

看到题的第一反应就是：这是有关图论的题吧！

### 题目大意

构造一个每个节点的出度都为 $k$ 的有向图，若无法构造则输出 $-1$，否则输出这张图有几条边和每边上的点。

首先我们可以知道：如果这张图的边数比**完全图**的边数（即 $\frac{n(n-1)}{2}$ 条边）还要多显然是无解的，直接输出 $-1$ 就结束。否则就构建一张每个点的出度都是 $k$ 的图（即让每个节点 $V$ 都向区间 $[V+1,V+k]$ 里的每个点连边，这样可以保证每个点的出度都是 $k$ 而没有重边的现象）即可。还有一个很重要的判断，就是若点的编号 $v$ 大于了 $n$，就需要将 $v$ 对 $n$ 进行取模。

### AC Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,k;

signed main() {
	scanf("%lld %lld",&n,&k);
	if(n*k>n*(n-1)/2){//不符合
		puts("-1");
		return 0;
	}
	printf("%lld\n",n*k);//点的数量
	for(int i=1;i<=n;++i){
		for(int j=1;j<=k;++j){
			int t=i+j;
			printf("%lld %lld\n",i,(t%n!=0)?(t%n):n);//简写一下
		}
	}
    return 0;
}
```

---

## 作者：syf159 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF417C)

## 分析

对于本题，我们可以把每一场比赛看成图上的有向边，队伍看成图上的点。

首先，求出方案数。方案数固定为 $\frac{n×(n+1)}{2}$。若 $\frac{n×(n+1)}{2}<n×k$，则说明没有可行方案，输出 $-1$ 即可。

然后输出方案即可

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	if(n*k>n*(n-1)/2) cout<<-1;
	else
	{
		printf("%d\n",n*k);
		for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=k; j++)
			{
				if((i+j)%n==0) printf("%d %d\n",i,n);
				else printf("%d %d\n",i,(i+j)%n);
			}
		}	
	}
	
	return 0;
}
```

---

## 作者：Pollococido (赞：0)

### 思路
可以转化成图来做，将胜负关系转化成有向边，边的起点赢了重点，然后取模即可。

既然这样，那每个点的出度就是 $k$，方案数就是边数，那么方案数就是 $n \times k$。

#### 怎么判断无解？
这个图最多是完全图，边数就是 $\dfrac{n(n+1)}{2}$，如果 $n \times k > \dfrac{n(n+1)}{2}$，那么无解。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;

int main() {
	cin >> n >> k;
	if (n * k > (n + 1) * n / 2) {
		cout << -1;
		return 0;
	}
	cout << n * k << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			cout << i << " " << ((i + j) % n == 0 ? n : (i + j) % n) << endl;//三目简化一下
		}
	}
	return 0;
}
```

---

## 作者：_zhaosihan_qwq_ (赞：0)

# 题解：CF417C Football
## 题目大意
对于每个球队，请你求出使得任意一个球队都赢了 $k$ 次的方案数，并求出其中一个方案。感谢 Red_river 提供翻译。
## 思路
这道题是一道模拟，需要图论的知识，首先有一张有向图和一张完全图，无解的方式就只有一种，这支球队构成的有向图的边数比完全图的边数要大，那么肯定无解。其余的方案就是将有向图的边向外延伸，补全有向图，成为完全图，求出来补充的边数就行了，输出时注意边数计算，不能计算的是朝向的个数，注意数据范围取模运算，这样的思路时间复杂度就 $nk$ ，AC 妥妥的。

---

## 作者：Red_river (赞：0)

### 题目大意
对于每个球队，请你求出使得任意一个球队都赢了 $k$ 次的方案数，并求出其中一个方案。
### 题意分析
不难发现我们似乎可以将它转移到图上来讲，即对于一个**有向边**，它的起点赢了终点，当然不可能出现两个点之间有类似于无向边的情况。于是乎我们最多只能将其看做一个完全图了，即任意一个点都有一条有向边，所以边数最多为 $n\times (n-1)\div2$ 条边。我们又可以发现边数等于方案数，所以即为 $n\times k$ 的方案数，接下来就是构造了，直接取模就行。
### CODE

```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define int long long
#define mod 998244353
#define N 200005
#define NO printf("No\n")
#define YES printf("Yes\n")
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int head[N],dis[N],vis[N],wis[N],f[N];

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9')){
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x){
	if(x==0){
		putchar('0');
		return;
	}
	if(x<0){
		x=-x;
		putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}
//快读快输。
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(m);
	if(n*m>(n*(n-1))/2) wh(-1);
	else{
		wh(n*m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				wk(i);//第i个球队的情况。
				if((i+j)%n) wh((i+j)%n);//所赢的队伍。
				else wh(n);//特判是否溢出即刚好是n的情况。
			}
		}
	}
	return 0;
}
```

---

