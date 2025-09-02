# [ABC145E] All-you-can-eat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc145/tasks/abc145_e

高橋君は食べ放題のお店に来ました。

$ N $ 種類の料理があり、$ i $ 番目の料理は、食べるために $ A_i $ 分必要で、美味しさは $ B_i $ です。

この店のルールは以下の通りです。

- $ 1 $ 度に $ 1 $ つの料理のみを注文することができます。注文した料理は即座に提供され、食べ始めることができます。
- 同じ種類の料理を $ 2 $ 度以上注文することはできません。
- 提供済みの料理を食べ終わるまで次の料理を注文することはできません。
- 最初の注文から $ T-0.5 $ 分後以降に注文することはできませんが、提供済みの料理を食べることはできます。

高橋君の満足度を、この来店で高橋君が食べる料理の美味しさの合計とします。

高橋君が適切に行動したとき、満足度は最大でいくらになるでしょうか。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ T\ \leq\ 3000 $
- $ 1\ \leq\ A_i\ \leq\ 3000 $
- $ 1\ \leq\ B_i\ \leq\ 3000 $
- 入力中のすべての値は整数である。

### Sample Explanation 1

$ 1 $ 番目、$ 2 $ 番目の順に料理を注文することで、満足度は $ 110 $ になります。 注文が時間内に間に合えば、食べるのにどれだけ時間がかかっても良いことに注意してください。

### Sample Explanation 2

$ 60 $ 分以内に全ての料理を食べることができます。

### Sample Explanation 3

$ 2 $ 番目、$ 3 $ 番目の順に料理に注文することで、満足度を $ 50 $ にできます。 どのような順に料理を注文しても、料理を $ 3 $ つ注文することはできません。

## 样例 #1

### 输入

```
2 60
10 10
100 100```

### 输出

```
110```

## 样例 #2

### 输入

```
3 60
10 10
10 20
10 30```

### 输出

```
60```

## 样例 #3

### 输入

```
3 60
30 10
30 20
30 30```

### 输出

```
50```

## 样例 #4

### 输入

```
10 100
15 23
20 18
13 17
24 12
18 29
19 27
23 21
18 20
27 15
22 25```

### 输出

```
145```

# 题解

## 作者：Grisses (赞：8)

[本题](https://www.luogu.com.cn/problem/AT5276)是一个简单 DP。

我们设 $dp_i$ 表示最后一道菜在 $i$ 时刻时吃完的最大美味值。

这就是一个简单的 0-1 背包了。


其中设$dp_j$ 表示最后吃的一盘菜在 $j$ 时刻吃完带来的最大美味值。对于第 $i$ 盘菜，我们如果不点，那 $dp_j$ 就不变。如果点，$dp_j$ 就等于 $dp_{j-a_i}+b_i$。不难推出：
$$dp_j=\max(dp_j,dp_{j-a_i}+b_i),(a_i\le j)$$

本题的还有一个重点是要将每道菜先按 $a$ 从小到大排序。这是因为我们肯定要优先点食用时间短的菜，这样才可以尽量多的吃菜。

最后，因为 $1\le a,t\le 3000$，所以 $j$ 的最大值是 $a+t-1=5999$。

### 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,t,dp[6005],ans;
  struct node{//结构体用来存储a[i]和b[i]
      int a,b;
      bool operator<(const node &t)const{//运算符重载
          return a<t.a;
      }
  }a[3005];
  int main()
  {
      scanf("%d%d",&n,&t);
      for(int i=1;i<=n;i++)scanf("%d%d",&a[i].a,&a[i].b);
      sort(a+1,a+n+1);//先将食物按食用时间从小到大排序
      for(int i=1;i<=n;i++){
          for(int j=t+a[i].a-1;j>=a[i].a;j--){//因为再t时刻之后依然可以吃菜，但必须在t时刻前点菜，所以j是从t+a[i].a-1到a[i].a的闭区间
              dp[j]=max(dp[j],dp[j-a[i].a]+a[i].b);//01背包
          }
      }
      for(int i=1;i<=5999;i++)ans=max(ans,dp[i]);//取最大值
      printf("%d",ans);
      return 0;
  }
```

---

## 作者：xibaohe (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc145_e)

# 题目大意
帮助高桥君点菜，每道菜只能点一次，吃完才能点下一道菜。每道菜都有吃完所需要的时间 $a_i$ 和吃完所获得的美味程度 $b_i$，问怎样吃才能在不超过 $T$ 分钟的情况下吃到最多的美味程度值。

# 题目思路
这道题中有一个很重要的信息是时间到后没吃完的菜可以吃完，因此就涉及到要不要用最后一分钟点菜权的问题。看到题解区的很多大佬都用了**背包型动规**，蒟蒻今天来分享一种与众不同的做法：

### 升维型动规

升维型动规，就是把 $dp$ 数组的维度从正常的 $2$ 维升高至 $3$ 维或更多。在这道题中，蒟蒻用一个 $3$ 维 $dp$ 数组来进行动规。状态表示如下：

### $dp_{i,j,0}$ 表示前 $i$ 道菜吃 $j$ 分钟所能得到的最大美味程度且没用最后一分钟的点菜权。

### $dp_{i,j,1}$ 表示前 $i$ 道菜吃 $j$ 分钟所能得到的最大美味程度且用了最后一分钟的点菜权。

# 状态转移

我们的状态转移方程共分为两种情况。

### 没用最后一分钟点菜权

没用最后一分钟点菜权共有两种情况：

 - 没用最后一分钟点菜权，不点菜。
```cpp
f[i][j][0]=max(f[i][j][0],f[i-1][j][0]);
```
 - 没用最后一分钟点菜权,点菜。
```cpp
f[i][j][0]=max(f[i][j][0],f[i-1][j-w[i]][0]+v[i]);
```
 
注意不用最后一分钟点菜权点菜的前提是时间足够。

### 用了最后一分钟点菜权

用了最后一分钟点菜权共有两种情况：

 - 用了最后一分钟点菜权，前面的菜用掉的，不点菜。
```cpp
f[i][j][1]=max(f[i][j][1],f[i-1][j][1]);
```
 - 用了最后一分钟点菜权，前面的菜用掉的，点菜。
```cpp
f[i][j][1]=max(f[i][j][1],f[i-1][j-w[i]][1]+v[i]);
```
 - 用了最后一分钟点菜权，这道菜用掉的，点菜。
```cpp
f[i][j][1]=max(f[i][j][1],f[i-1][j][0]+v[i]);
```
注意不用最后一分钟点菜权点菜的前提是时间足够。
 
### 总状态转移方程如下：
```cpp
if(j>=w[i])
{
    f[i][j][0]=max(f[i-1][j][0],f[i-1][j-w[i]][0]+v[i]);
    f[i][j][1]=max(f[i-1][j][0]+v[i],max(f[i-1][j][1],f[i-1][j-w[i]][1]+v[i]));
}
else
{
    f[i][j][0]=f[i-1][j][0];
    f[i][j][1]=max(f[i-1][j][0]+v[i],f[i-1][j][1]);
}
```

# 满分代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,w[3005],v[3005],t,f[3005][3005][2];

int main(){
    cin>>n>>t;
    for(int i=1;i<=n;i++) cin>>w[i]>>v[i];
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=t;j++)
    	{
    		if(j>=w[i])
    		{
    			f[i][j][0]=max(f[i-1][j][0],f[i-1][j-w[i]][0]+v[i]);
    			f[i][j][1]=max(f[i-1][j][0]+v[i],max(f[i-1][j][1],f[i-1][j-w[i]][1]+v[i]));
    		}
    		else
    		{
    			f[i][j][0]=f[i-1][j][0];
    			f[i][j][1]=max(f[i-1][j][0]+v[i],f[i-1][j][1]);
    		}
    	}
    }
    cout<<f[n][t-1][1]<<endl;
    return 0;
}
```

 

---

## 作者：COsm0s (赞：2)

简单背包。

只需要将时间当做容量，把美味程度看做价值，就可以转化为背包了。

需要注意的是，题目中给出了这么一段话：**一旦开始了吃就一定会吃完这道菜，哪怕时间超过 $T$ 分**。

这就导致方程的边界发生了变化：最大边界变成了 $T+a_i-1$，也就是说 $a_i$ 最多可以是 $T$，此时当吃完这盘菜时间就到了 $T+a_i-1$，所以边界就确定了。

有这个与普通背包不同的特性，我们就要先排序一遍，使得最小时间排在最前，从而让最后一个吃的菜尽可能大。

## Code：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(int x) {
	if(x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
struct info {
	int x, y;
} a[6000];
int f[6000];
inline bool cmp(info x, info y) {
	return x.x < y.x;
}
signed main() {
	int n = read(), t = read();
	for(int i = 1; i <= n; i ++) a[i].x = read(), a[i].y = read();
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i ++)
		for(int j = t + a[i].x - 1; j >= a[i].x; j --)
			f[j] = max(f[j], f[j - a[i].x] + a[i].y);
	int ans = 0;
	for(int i = 1; i < 6000; i ++) ans = max(ans, f[i]);
	write(ans);
	return 0;
}

```


---

## 作者：BotYoung (赞：1)

前置知识：**0/1背包 DP**

### 分析：
这道题是一道背包 DP 打卡题，但是却与正常的背包 DP 有所不同。首先便考察了我们审题的仔细程度，发现到达规定时间以后只能吃东西，并且在规定时间也只能吃东西。
 
所以背包的容量在 DP 时将有所变化，从正常的 $[m, a_i]$ 这一区间循环变为                  $(m+a[i],a[i]]$ 区间内的循环(通俗的讲，我们原先“容量不超过限制”的题面，变成了“最后一次选择时容量不超过限制”)。由此推理出状态转移方程：
$$DP[j]=DP[j-a[i]]+b[i]$$

代码实现并不难，下面给出一段代码：
```cpp
For(i, 1, n)
	for (int j = m + a[i].a - 1; j >= a[i].a; j--){
		dp[j] = max(dp[j], dp[j - a[i].a] + a[i].b);
		ans = max(ans, dp[j]);
	}
write(ans);
return 0;
```
然后就可以得到光荣的 $37$ 分。

再次分析题目，会发现这道题目隐藏了一个贪心的思想，这是与其他题目十分不同的，也是这道题目的精髓所在。由于能否得到一样事物，只与用时有关。而我们要使总价值最高，与我们对题目新的理解就会发现，**我们要想得到高的价值，就必须优先考虑用时低的食物，故要在 DP 前排序。**

重新给出代码：
```cpp
#include<cstdio>
#include<algorithm>
#define int long long
#define For(i, l, r) for(int i = l; i <= r; i++)
using namespace std;
struct food{
	int a, b;
}a[3005];
int n, m, dp[6005], ans;
inline int read(){
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * f;
}
inline void write(int x){
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
inline bool cmp(food x, food y){
	return x.a < y.a;
}
//快读快写，有需要的童鞋请自便
signed main(){
	n = read(), m = read();
	For(i, 1, n) a[i].a = read(), a[i].b = read();
	sort(a + 1, a + n + 1, cmp);
	For(i, 1, n)
		for (int j = m + a[i].a - 1; j >= a[i].a; j--){
			dp[j] = max(dp[j], dp[j - a[i].a] + a[i].b);
			ans = max(ans, dp[j]);
		}
	write(ans);
	return 0;
}
```
最后温馨提醒一下，不要忘了开**ll**哦！


---

## 作者：Unnamed114514 (赞：0)

首先，看到本题，可以轻松想到它是大名鼎鼎的 $\color{red}\text{0/1 背包问题}$，它有如下的一个性质：
- 每个物品的状态可以用 $0/1$ 表示。
即每个物品只有取或不去两种状态。

从这个定义出发，我们可以设 $dp_{i,j}$ 表示轮到第 $i$ 个食品时间为 $j$ 的最大美味值。若取，就是 $dp_{i-1,j-a_i}+b_i$，表示取后时间减少 $a_i$，美味值增加 $b_i$；或者不取，就是 $dp_{i-1,j}$。综上，$dp_{i,j}\gets\max(dp_{i-1,j},dp_{i-1,j-a_i}+b_i)$。

但是，如果你这样交上去，就会 $\color{red}\text{WA}$，但是，考虑一下，我们如果选择当前解，那么如果把时间长的排后面，那么中间也许还可以插进去，所以我们还需要按照时间升序排列。

此时，我们可以第一维压掉。我们如果仍要推导，枚举时间时就倒序枚举，才能防止 $dp_i$ 更新掉 $dp_{i-1}$。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define a(i) f[i].a
#define b(i) f[i].b
#define up(i,a,b) for(int i=a;i<=b;++i)
#define down(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
struct node{
	int a,b;
	bool operator <(const node &t) const{
		return a<t.a;
	}
}f[3005];
inline int read(){
	int a;
	scanf("%d",&a);
	return a;
}
int n=read(),t=read(),dp[6005],ans;
int main(){
	for(int i=1;i<=n;f[i++]=node({read(),read()}));
	stable_sort(f+1,f+n+1);
	up(i,1,n)
		down(j,t+a(i)-1,a(i))
			dp[j]=max(dp[j],dp[j-a(i)]+b(i)),ans=max(ans,dp[j]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：cqbzhyf (赞：0)

首先，这是一道简单的背包问题。

再其次，这是一道简单的 **0/1** 背包问题。

首先贪心地排序，时间越短先选择，因为时间到了还可以继续（只是不可以选择而已）

## 证明贪心
首先，时间越少，意味着可以选择更多的物品（也可以不选），就好比矿泉水瓶先装小石子，再装大石子时可以拿出小石子

然后我们就以时间定义状态，压缩一维序号，就有了熟知的状态转移方程 $dp_j=\max(dp_j,dp_{j-a_i}+b_i)$。

然后就结束了……

上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,dp[6005],ans;
struct Q{
	int a,b;
}A[3005];
inline bool cmp(Q x,Q y){return x.a<y.a;}
signed main(){
	cin>>n>>t;
	for(int i=1;i<=n;++i)cin>>A[i].a>>A[i].b;
	sort(A+1,A+1+n,cmp);
	for(int i=1;i<=n;++i){
		for(int j=t+A[i].a-1;j>=A[i].a;--j){
			dp[j]=max(dp[j],dp[j-A[i].a]+A[i].b);
			ans=max(ans,dp[j]);
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：pandaSTT (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT5276)

## 前言

标签建议评 黄  

## 思路

一眼可以看出这是一道**背包**模板，把时间当做背包容量，品尝每道菜的时间作为体积，每道菜的美味程度作为价值，其余注意事项代码详解。

## 代码&注意事项

```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  inline char gc(){
      static char buf[1000010],*p1=buf,*p2=buf;
      return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;
  }
  inline int read(){
      register int x=0,f=0;
      static char s=gc();
      while(s<'0'||s>'9')f|=s=='-',s=gc();
      while(s>='0'&&s<='9'){
          x=(x<<3)+(x<<1)+(s^48);s=gc();
      }return f?-x:x;
  }
  inline void write(register int x){
      if(x<0)putchar('-'),x=-x;
      if(x>9)write(x/10);putchar(x%10^48);
  }
  int n,t,dp[6005],ans;
  struct nobe{
      int a,b;//品尝每道菜的时间与每道菜的美味程度
      friend bool operator<(nobe x,nobe y){
          return x.a<y.a;
      }
  }a[3005]; 
  signed main(){
      n=read(),t=read();
      for(int i=1;i<=n;i++){
          a[i].a=read(),a[i].b=read();
      }
      sort(a+1,a+n+1);//进行 DP 需要提前排序
      for(int i=1;i<=n;i++){
          for(int j=t+a[i].a-1;j>=a[i].a;j--){//由于可以再时间结束后继续品尝，所以 j 的初始值应为 t+a[i]-1 
              dp[j]=max(dp[j],dp[j-a[i].a]+a[i].b);
          }
      }
      for(int i=1;i<=6000;i++){//枚举所有可能时间计算最大值
          ans=max(ans,dp[i]);
      }
      cout<<ans;
      return 0;
  }
```


---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
这道题是一道 DP 题，我们只需要按照时间去进行就可以了。

首先我们可以给每一道菜品按照时间去排一个序，把用时少的菜品放到前面。然后把每一道菜品放到 $M$ 这个时间范围之内的任意时间之中，我们就可以得到一个动态转移方程式： 
```cpp
dp[min(m,j+a[i].y)]=max(dp[min(m,j+a[i].y)],dp[j]+a[i].x);
```
这样跑完一遍，然后输出最大值就可以了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[3001];
struct f{
	int x,y;
}a[3001];
int cnt(f x,f y)
{
	if(x.y==y.y) return x.x>y.x;
	return x.y<y.y;
}
int main()
{
	long long n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i].y>>a[i].x;
	for(int i=1;i<=n;i++) dp[i]=0;
	sort(a+1,a+1+n,cnt);
	for(long long i=0;i<m;i++)dp[min(a[1].y+i,m)]=a[1].x;
	for(long long i=2;i<=n;i++)
		for(long long j=m-1;j>=0;j--)
			dp[min(m,j+a[i].y)]=max(dp[min(m,j+a[i].y)],dp[j]+a[i].x);
	long long ma=0;
	for(int i=0;i<=m;i++) ma=max(ma,dp[i]);
	cout<<ma;
	return 0;
 } 
```


---

## 作者：cccyyyxxx (赞：0)

## 题意：

有  $n$  道菜，时间限制为  $m$  ，每道菜的代价为  $a_i$  ，收益为  $b_i$  ，求最高收益。

注意：第  $m$  分钟就不能再点菜了，但之前点的，现在正在吃的还能继续，并计入总收益。

## 分析:

长得很像  $01$  背包。

设  $dp_i$  **表示最后一盘菜在第  $i$  分钟吃完的最高收益**。由于最后一盘菜可能在第  $m$  分后吃完，且  $a_i\le 3000$  ，因此  $dp$  数组**开两倍空间。**

另外为了使收益最大，将代价从小到大排序，这样才能吃更多的菜。

**转移**：

  $dp_j=\max(dp_j,dp_{j-a_i}+b_i)$
  
## 注意：

循环第二层应该从  $m+a_i-1$  到  $a_i$  。因为时间过后还能吃菜，但最后不能点菜，因此要减一。


## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N =6e3+10;
struct node{
	int time,val;
}a[N];
int n,m,ans,dp[N];
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
bool cmp(node a,node b){
	return a.time<b.time;
}
signed main(){
	n=read(); m=read();
	for(int i=1;i<=n;i++){
		a[i].time=read();
		a[i].val=read();
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
		for(int j=m+a[i].time-1;j>=a[i].time;j--){
			dp[j]=max(dp[j],dp[j-a[i].time]+a[i].val);
			ans=max(ans,dp[j]);
		}
	cout<<ans<<endl;		
	return 0;
}

```


---

