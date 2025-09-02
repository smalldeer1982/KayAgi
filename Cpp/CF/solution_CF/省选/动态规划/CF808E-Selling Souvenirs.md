# Selling Souvenirs

## 题目描述

## 题目背景
Berland经过了多次改革后，许多游客打算来这儿游玩。居民们知道这是一个改行旅游服务业来赚钱的好机会，Petya也离开了他以前工作的IT公司，改在市场买礼品了。

像平常一样，今早Petya回来到市场。他有 $n$ 个不同的礼品要卖；第 $i$ 个礼品有重量 $w_{i}$ 和价格 $c_{i}$ 两个属性。Petya知道他不能把所有礼品扛到市场，便想要选一部分总重量不超过 $m$ 的礼品，而总价格越高越好。

帮帮Petya确定最大的总价格吧。

## 样例 #1

### 输入

```
1 1
2 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 2
1 3
2 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4 3
3 10
2 7
2 8
1 1
```

### 输出

```
10
```

# 题解

## 作者：肖然 (赞：11)

$N = 10^5, C = 3\times 10^5$ 的背包DP

特殊性质是物品重量只有3种 $w[i]=1/2/3$

【算法0】

首先考虑 $w[i]=1/2$ 两种重量，可以各自按 $v[i]$ 大->小排序后贪心，设DP状态：

- $dp[j] = $ 只考虑 $w[i]=1/2$ ，$j$ 重量的最大价值

- $dp[j] = max(s1[n1] + s2[j-n1])$ 
- 其中 $s1,s2$ 为排序后 $v$ 的前缀和，$n1 = $ 选多少个 1 物品

再考虑枚举选取 $w[i]=3$ 的物品数量$n3$ ，就有了一个总复杂度 $O(C^2)$ 的算法。

- $ans = max(s3[n3] + dp[C-3\times n3])$

当然，这个算法不能通过 $C = 3\times 10^5$ 的数据

【算法1】

考虑将dp状态设成一个4元组：
- $dp[j] = (c,n1,n2,n3) $
代表总容量为 $j$ 时的最大价值 $c$ ，同时对应选取了 $n1,n2,n3$ 个 1,2,3 物品

"我为人人"式更新，有三种更新方式：

- ${c+v1[n1+1],n1+1,n2,n3}\to dp[j+1]$
- ${c+v2[n2+1],n1,n2+1,n3}\to dp[j+2]$
- ${c+v3[n3+1],n1,n2,n3+1}\to dp[j+3]$

其中 $v1[i],v2[i],v3[i]=$ 价值第 $i$ 大的1-3物品价值

这样复杂度是 $O(3C)$ 不会TLE，但不幸的是会WA。

例如
```
Consider the case n=4, m=7 with 4 items
A = (1,3)
B1 = B2 = (2,4)
C = (3,6)

Then the (only) optimal solution
dp[4] = A + C
dp[5] = A + B1 + B2
dp[6] = A + B1/B2 + C
dp[7] = B1 + B2 + C

but there is no way to create the solution for dp[7] by adding items to any of the three solutions before.
(https://codeforces.com/blog/entry/52010?#comment-360499)：
```
幸运的是我们可以修正这个算法，考虑第4种转移：

- $c-v1[n1]+v3[n3+1],n1-1,n2,n3+1 \to dp[j+2]$

即拿走一个 $1$ 物品添上一个 $3$ 物品，这样 $dp[7]$ 就能从 $dp[5]$ 转移过来，可以AC本题。

```cpp
#include <bits/stdc++.h>
#define MAXN 300005
#define LL long long
using namespace std;

struct Node{
	LL c;
	int n1, n2, n3;
	Node(LL c=0, int n1=0, int n2=0, int n3=0):c(c), n1(n1), n2(n2), n3(n3){}
} dp[MAXN];
int N,M;
int v[4][MAXN];
int cnt[4];

void update(Node& a, Node b){
	if(a.c < b.c) a = b;
} 

int main() {
	cin>>N>>M;
	for(int i=1;i<=N;i++) {
		int w,x;
		cin>>w>>x;
		v[w][++cnt[w]] = x;
	}
	
	for(int w=1;w<=3;w++){
		sort(v[w]+1, v[w]+1+cnt[w], greater<int>());
	}

	dp[0] = Node(0,0,0,0);
	LL ans = 0;
	for(int j=0;j<=M;j++){
		LL c = dp[j].c;
		int n1 = dp[j].n1, n2 = dp[j].n2, n3 = dp[j].n3;
		if(j+1<=M && n1 < cnt[1]) update(dp[j+1], Node(c+v[1][n1+1], n1+1, n2, n3));
		if(j+2<=M && n2 < cnt[2]) update(dp[j+2], Node(c+v[2][n2+1], n1, n2+1, n3));
		if(j+3<=M && n3 < cnt[3]) update(dp[j+3], Node(c+v[3][n3+1], n1, n2, n3+1));
		
		if(j+2<=M && n1 && n3 < cnt[3]) update(dp[j+2], Node(c-v[1][n1]+v[3][n3+1], n1-1, n2, n3+1));

		ans = max(ans, c);
	}
	cout<<ans<<endl;
	return 0;
}
```

【算法2】

假设只考虑 $w[i]=2/3$ 两种物品，同样可以各自按 $v[i]$ 大->小排序后贪心，枚举 $n3$ 可以在 $O(N)$ 时间内计算答案：


- $ans = max(s3[n3] + s2[(M-3\times n3)/2])$


那么怎么考虑 $w[i]=1$ 的物品呢？

考虑分类讨论：

1. 最优解取了偶数个 $1$ 物品，那么将所有 $1$ 物品排序后两两打包，视为$n1/2$ 个 $2$ 物品即可；
2. 最优解取了奇数个 $1$ 物品，那么必取价值最大的那个 $1$ 物品，剩下的 $1$ 物品两两打包视为 $2$ 物品即可；

最后2种情况取max，总复杂度 $O(N)$。

```cpp
#include <bits/stdc++.h>
#define MAXN 100005
#define LL long long
using namespace std;

int N,C;
vector<int> Adj[4];
vector<int> v2;
int n1,n2,n3;

LL s[4][MAXN];
LL ans1,ans2;

void calS2(){
	sort(v2.begin(), v2.end(), greater<int>());
	for(int i=0;i<v2.size();i++){
		s[2][i+1] = s[2][i] + v2[i];
	}
	return;
}

int main(){
	cin>>N>>C;
	
	int w,v;
	for(int i=1;i<=N;i++){
		cin>>w>>v;
		Adj[w].push_back(v);
	}
	
	//sort3
	sort(Adj[3].begin(), Adj[3].end(), greater<int>());
	for(int i=0;i<Adj[3].size();i++){
		s[3][i+1] = s[3][i] + Adj[3][i];
	}

	//even
	sort(Adj[1].begin(), Adj[1].end(), greater<int>());
	for(int i=1;i<Adj[1].size();i+=2){
		v2.push_back(Adj[1][i] + Adj[1][i-1]);
	}
	for(int i=0;i<Adj[2].size();i++){
		v2.push_back(Adj[2][i]);
	}
	calS2();
	for(n3=0;n3<=Adj[3].size();n3++){
		if(C-3*n3 < 0) continue;
		n2 = min((C-3*n3)/2, int(v2.size()));
		ans1 = max(ans1, s[3][n3] + s[2][n2]);
	}
	if(Adj[1].size()==0){
		cout<<ans1<<endl;
		return 0;
	}

	//odd
	sort(Adj[1].begin(), Adj[1].end(), greater<int>());
	v2.clear();
	for(int i=2;i<Adj[1].size();i+=2){
		v2.push_back(Adj[1][i] + Adj[1][i-1]);
	}
	for(int i=0;i<Adj[2].size();i++){
		v2.push_back(Adj[2][i]);
	}

	calS2();
	for(n3=0;n3<=Adj[3].size();n3++){
		if(C-3*n3-1 < 0) continue;
		n2 = min((C-3*n3-1)/2, int(v2.size()));
		ans2 = max(ans2, s[3][n3] + s[2][n2] + Adj[1][0]);
	}
	cout<<max(ans1, ans2);
	return 0;
}
```


---

## 作者：spire001 (赞：4)

## 题目大意
这个题的翻译还是比较清楚的，就不赘述了。。

## 解题思路
首先相同的体积拿价值更高的必然更优，这个贪心是显然的。。。然后怎么做？？？ 

我不会了。。。

所以这个题解是来宣传退火邪教的。。。

之所以敢去选择退火，是因为如果三种礼品拿的数量已知，那么计算是 $O(1)$ 的，至少可以计算 $10^6$ 次，正确率有所保障。

那么我们人工模拟一下该怎么去选，首先在一个地方（$w=$ $1$ 或 $2$ 或 $3$）进行微调，然后通过空间限制对剩下的两种进行调整，尽量将背包填满，如果填多了就删掉一些。

同时为了保证每种情况都会涉及到，我们需不时变换微调的体积，微调的优先级。

例如你准备拿 $p_1$ 个体积为 $1$ 的，你更新 $p_1$，然后是先调整 $p_2$ 还是 $p_3$ 是由你决定的。

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <cassert>
#define calc(pos1, pos2, pos3) (sum[1][pos1] + sum[2][pos2] + sum[3][pos3])
using namespace std;

constexpr double eps = 1e-12, delta = 0.997;

typedef long long LL;

constexpr int N = 100010;
int n, m, s1, s2, s3, n1, n2, n3;

vector <int> a[5];

LL dp[5][N], sum[5][N], res0, ans, nb;

inline void change1(int &p1, int &p2, int &p3)
{
  int t = p1 + 2 * p2 + 3 * p3;

  if (t < m) // 还需要往里面填，优先级 p2 > p3 > p1
  {
    p2 = min(s2, p2 + ((m - t) >> 1)); 
    t = p1 + 2 * p2 + 3 * p3;
    if (t < m)
      p3 = min(s3, p3 + ((m - t) / 3));
  }
  else // 添太多了，删一点
  {
    p2 = max(p2 - ((t - m) >> 1), 0);
    t = p1 + 2 * p2 + 3 * p3;
    if (t > m)
      p3 = max(0, p3 - ((t - m) / 3));
    t = p1 + 2 * p2 + 3 * p3;
    if (t > m)
      p1 = p1 - (t - m);
  }

  // assert(p1 >= 0 && p2 >= 0 && p3 >= 0);

  return;
}
inline void change2(int &p1, int &p2, int &p3)
{
  int t = p1 + 2 * p2 + 3 * p3;

  if (t < m) // 优先级 p3 > p1 > p2
  {
    p3 = min(s3, p3 + (m - t) / 3);
    t = p1 + 2 * p2 + 3 * p3;
    if (t < m)
      p1 = min(s1, p1 + (m - t));
  }
  else 
  {
    p3 = max(p3 - (t - m) / 3, 0);
    t = p1 + 2 * p2 + 3 * p3;
    if (t > m)
      p1 = max(0, p1 - (t - m));
    t = p1 + 2 * p2 + 3 * p3;
    if (t > m)
      p2 = p2 - ((t - m) & 1 ? (t - m) / 2 + 1 : (t - m) / 2);
  }
  
  // assert(p1 >= 0 && p2 >= 0 && p3 >= 0);

  return;
}
inline void change3(int &p1, int &p2, int &p3)
{
  int t = p1 + 2 * p2 + 3 * p3;

  if (t < m) // 优先级 p1 > p2 > p3
  {
    p1 = min(s1, p1 + ((m - t)));
    t = p1 + 2 * p2 + 3 * p3;
    if (t < m)
      p2 = min(s2, p2 + ((m - t) >> 1));
  }
  else 
  {
    p1 = max(p1 - (t - m), 0);
    t = p1 + 2 * p2 + 3 * p3;
    if (t > m)
      p2 = max(0, p2 - ((t - m) / 2));
    t = p1 + 2 * p2 + 3 * p3;
    if (t > m)
      p3 = p3 - ((t - m) % 3 == 0 ? (t - m) / 3 : (t - m) / 3 + 1);
  }
  
  // assert(p1 >= 0 && p2 >= 0 && p3 >= 0);

  return;
}

void SA()
{
  nb = ans;
  int tp1 = n1, tp2 = n2, tp3 = n3;

  int tot = 0;

  for (double T = 1e5; T > eps; T *= delta, tot++) // 套模拟退火板子
  {
    int p1 = tp1, p2 = tp2, p3 = tp3;
    if (tot > 3) tot -= 3;
    if (tot == 0) // 换 p1
    {
      p1 = p1 + ((double)(rand() << 1) - RAND_MAX) / RAND_MAX * T + 1;
      // 加一是为了防止搞出一堆 0 浪费计算时间 
      if (p1 > s1) // 特判边界，同下
        p1 = s1;
      else if (p1 < 0)
        p1 = s1 ? 1 : 0;

      change1(p1, p2, p3);

      LL res = calc(p1, p2, p3);

      if (res > ans)
      {
        n1 = tp1 = p1;
        n2 = tp2 = p2;
        n3 = tp3 = p3;
        ans = res;
      }
      else if (res > nb || exp((res - nb) / T) > (double)rand() / RAND_MAX)
      {
        nb = res;
        tp1 = p1;
        tp2 = p2;
        tp3 = p3;
      }
    }
    else if (tot == 1) // 换 p2
    {
      p2 = p2 + ((double)(rand() << 1) - RAND_MAX) / RAND_MAX * T + 1;

      if (p2 > s2)
        p2 = s2;
      else if (p2 < 0)
        p2 = s2 ? 1 : 0;

      change2(p1, p2, p3);

      LL res = calc(p1, p2, p3);

      if (res > ans)
      {
        n1 = tp1 = p1;
        n2 = tp2 = p2;
        n3 = tp3 = p3;
        ans = res;
      }
      else if (res > nb || exp((res - nb) / T) > (double)rand() / RAND_MAX)
      {
        nb = res;
        tp1 = p1;
        tp2 = p2;
        tp3 = p3;
      }
    }
    else // 换 p3
    {
      p3 = p3 + ((double)(rand() << 1) - RAND_MAX) / RAND_MAX * T + 1;

      if (p3 > s3)
        p3 = s3;
      else if (p3 < 0)
        p3 = s3 ? 1 : 0;

      change3(p1, p2, p3);

      LL res = calc(p1, p2, p3);

      if (res > ans)
      {
        n1 = tp1 = p1;
        n2 = tp2 = p2;
        n3 = tp3 = p3;
        ans = res;
      }
      else if (res > nb || exp((res - nb) / T) > (double)rand() / RAND_MAX)
      {
        nb = res;
        tp1 = p1;
        tp2 = p2;
        tp3 = p3;
      }
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  srand(time(NULL));
  cin >> n >> m;

  a[1].push_back(-1), a[2].push_back(-1), a[3].push_back(-1);
  // 不喜欢 0 下标
  for (int i = 1; i <= n; i++)
  {
    int w, c; cin >> w >> c;
    a[w].push_back(c); res0 += w;
  }

  sort(++a[1].begin(), a[1].end(), greater<int>()); // 排序，贪心
  sort(++a[2].begin(), a[2].end(), greater<int>());
  sort(++a[3].begin(), a[3].end(), greater<int>());

  s1 = (int)a[1].size() - 1;
  s2 = (int)a[2].size() - 1;
  s3 = (int)a[3].size() - 1;

  for (int i = 1; i <= s1; i++) // 计算前缀和
    sum[1][i] = sum[1][i - 1] + a[1][i];
  for (int i = 1; i <= s2; i++)
    sum[2][i] = sum[2][i - 1] + a[2][i];
  for (int i = 1; i <= s3; i++)
    sum[3][i] = sum[3][i - 1] + a[3][i];

  if (res0 <= m) // 特判总体积小于 m 
  {
    cout << sum[1][s1] + sum[2][s2] + sum[3][s3] << endl;
    return 0;
  }

  int times = 100;

  int t1 = m / 3, t2 = m - 2 * t1;

  n1 = min(t1, s1);
  n2 = min(t1 >> 1, s2);
  n3 = min(t2 / 3, s3);

  t1 = n1 + 2 * n2 + 3 * n3; // 初始状态平均分吧
  if (t1 < m)
  {
    n2 = min(n2 + ((m - t1) >> 1), s2);
    t1 = n1 + 2 * n2 + 3 * n3; // 没填满接着填 优先级 p2 > p1 > p3
    if (t1 < m)
    {
      n1 = min(n1 + (m - t1), s1);
      t1 = n1 + 2 * n2 + 3 * n3;
      
      if (t1 < m)
        n3 = min(n3 + (m - t1) / 3, s3);
    }
  }

  ans = calc(n1, n2, n3); // 计算初始状态

  while (times--) // 100 次足够
    SA();

  cout << ans << endl;

  return 0;
}
```

代码虽说有点长，但大多都是复制粘贴自己已写部分的，有所违背 `dry` 原则，但是能效率较高地通过本题，不失为一个合适的办法。

---

## 作者：command_block (赞：4)

(这是个复杂度严格的做法,并不需要什么分类讨论)

首先,能够发现这是个经典的背包问题,但是物品重量只有3种。

不妨把物品按照重量大小分为1类,2类和3类。

把每一类按照价值从大到小排序,显然,同一类里面尽量要选前面比较大的。

那么就可以得到枚举某两类,另一类尽量拿的$O(n^2)$sb大暴力。

我们从小到大枚举3类物品选了几个,可以发现2类物品个数的变动和1类物品的个数变动不会太大,那么你可以写一个变动个数在5以内的枚举,成功A掉此题。

证明?

我们知道上一次的方案是具有最优性的。

我这时多增加了一个3类物品,那么最多会弃掉前面选择的5个单位重量的物品。

问题在于我们不一定全在丢弃,可能会拿回一些东西。

假如我弃了一个2,拿了两个1,那么一定不优,因为这种方案在上一次不优,这一次也不优。如果这样更优的话,上一次必然也这样做。

弃1拿1,弃2拿2这些也都不可取,所以不可能拿回超过1个1.

证毕。

具体实现需要注意特判$m$比较大的情况。

代码相对dp解法有一点长,但是什么思维含量都没有……

```cpp
#include<algorithm>
#include<cstdio>
#define MaxN 100500
using namespace std;
int n1,n2,n3,m,p1,p2,p3,n;
long long ans,a1[MaxN],a2[MaxN],a3[MaxN];
bool cmp(const long long &A,const long long &B)
{return A>B;}
int main()
{
  scanf("%d%d",&n,&m);
  for (int i=1,w,c;i<=n;i++){
    scanf("%d%d",&w,&c);
    if (w==1)a1[++n1]=c;
    if (w==2)a2[++n2]=c;
    if (w==3)a3[++n3]=c;
  }sort(a1+1,a1+n1+1,cmp);
  sort(a2+1,a2+n2+1,cmp);
  sort(a3+1,a3+n3+1,cmp);
  for (int i=1;i<=n1;i++)a1[i]+=a1[i-1];
  for (int i=1;i<=n2;i++)a2[i]+=a2[i-1];
  for (int i=1;i<=n3;i++)a3[i]+=a3[i-1];
  if (m>=n1*1+n2*2+n3*3){
    printf("%lld",a1[n1]+a2[n2]+a3[n3]);
    return 0;
  }p1=p2=1;
  if (m>=n1*1+n2*2){
    p1=n1;p2=n2;p3=(m-p1*1-p2*2)/3;
    ans=a1[n1]+a2[n2]+a3[p3];
  }else {
    long long maxx=0;
    for (int i=0;i<=n1&&i<=m;i++)
      if (maxx<a1[i]+a2[(m-i)/2]){
        p1=i;p2=(m-i)/2;
        maxx=a1[p1]+a2[p2];
      }
    ans=max(ans,maxx);
  }
  for (int i=p3+1;i<=n3&&i*3<=m;i++){
    long long maxx=0,sp1,sp2;
    for (int j=-4;j<=1;j++)
      if (0<=p1+j&&p1+j<=n1&&(m-p1-j-i*3)>=0){
        if (maxx<a1[p1+j]+a2[(m-p1-j-i*3)/2]+a3[i]){
          maxx=a1[p1+j]+a2[(m-p1-j-i*3)/2]+a3[i];
          sp1=p1+j;
          sp2=(m-p1-j-i*3)/2;
        }
      }
    ans=max(ans,maxx);
    p1=sp1;p2=sp2;
  }printf("%lld",ans);
  return 0;
}
```

原来进行严格分类讨论的代码:

```cpp
#include<algorithm>
#include<cstdio>
#define MaxN 100500
using namespace std;
int n1,n2,n3,m,p1,p2,p3,n;
long long ans,a1[MaxN],a2[MaxN],a3[MaxN];
bool cmp(const long long &A,const long long &B)
{return A>B;}
int main()
{
  scanf("%d%d",&n,&m);
  for (int i=1,w,c;i<=n;i++){
    scanf("%d%d",&w,&c);
    if (w==1)a1[++n1]=c;
    if (w==2)a2[++n2]=c;
    if (w==3)a3[++n3]=c;
  }sort(a1+1,a1+n1+1,cmp);
  sort(a2+1,a2+n2+1,cmp);
  sort(a3+1,a3+n3+1,cmp);
  for (int i=1;i<=n1;i++)a1[i]+=a1[i-1];
  for (int i=1;i<=n2;i++)a2[i]+=a2[i-1];
  for (int i=1;i<=n3;i++)a3[i]+=a3[i-1];
  if (m>=n1*1+n2*2+n3*3){
    printf("%lld",a1[n1]+a2[n2]+a3[n3]);
    return 0;
  }p1=p2=1;
  if (m>=n1*1+n2*2){
    p1=n1;p2=n2;p3=(m-p1*1-p2*2)/3;
    ans=a1[n1]+a2[n2]+a3[p3];
  }else {
    long long maxx=0;
    for (int i=0;i<=n1&&i<=m;i++)
      if (maxx<a1[i]+a2[(m-i)/2]){
        p1=i;p2=(m-i)/2;
        maxx=a1[p1]+a2[p2];
      }
    ans=max(ans,maxx);
  }
  for (int i=p3+1;i<=n3&&i*3<=m;i++){
    if (p1*1+p2*2+i*3-m==1){
      long long maxx=0;int op=0;
      if (p1>=1&&a1[p1-1]+a2[p2]+a3[i]>maxx){
        op=1;
        maxx=a1[p1-1]+a2[p2]+a3[i];
      }if (p2<n1&&p2>=1&&a1[p1+1]+a2[p2-1]+a3[i]>maxx){
        op=2;
        maxx=a1[p1+1]+a2[p2-1]+a3[i];
      }if (p2>=1&&a1[p1]+a2[p2-1]+a3[i]>maxx){
        op=3;
        maxx=a1[p1]+a2[p2-1]+a3[i];
      }
      if (op==1)p1-=1;
      if (op==2){p2-=1;p1+=1;}
      if (op==3)p2-=1;
    }else if (p1*1+p2*2+i*3-m==2){
      long long maxx=0;int op=0;
      if (p1>=2&&a1[p1-2]+a2[p2]+a3[i]>maxx){
        op=1;
        maxx=a1[p1-2]+a2[p2]+a3[i];
      }if (p2>=1&&a1[p1]+a2[p2-2]+a3[i]>maxx){
        op=2;
        maxx=a1[p1]+a2[p2-2]+a3[i];
      }
      if (op==1)p1-=2;
      if (op==2)p2-=1;
    }else {
      long long maxx=0;int op=0;
      if (p1>=3&&a1[p1-3]+a2[p2]+a3[i]>maxx){
        op=1;
        maxx=a1[p1-3]+a2[p2]+a3[i];
      }if (p1>=1&&p2>=1&&a1[p1-1]+a2[p2-1]+a3[i]>maxx){
        op=2;
        maxx=a1[p1-1]+a2[p2-1]+a3[i];
      }if (p1<n1&&p2>=2&&a1[p1+1]+a2[p2-2]+a3[i]>maxx){
        op=3;
        maxx=a1[p1+1]+a2[p2-2]+a3[i];
      }if (p2>=2&&a1[p1]+a2[p2-2]+a3[i]>maxx){
        op=4;
        maxx=a1[p1]+a2[p2-2]+a3[i];
      }
      if (op==1)p1-=3;
      if (op==2){p1-=1;p2-=1;}
      if (op==3){p1+=1;p2-=2;}
      if (op==4)p2-=2;
    }
    ans=max(ans,a1[p1]+a2[p2]+a3[i]);
  }printf("%lld",ans);
  return 0;
}
```

---

## 作者：lanos212 (赞：3)

这是一道物品重量很小的 01 背包，~~根据经验我们可以瞎搞一下 qwq。~~

众所周知 01 背包使用贪心是错的，但是当物品重量很小时，贪心就会非常接近答案，所以可以先对大部分空间贪心，剩下小部分再背包即可。

~~虽然是错的但是非常难被卡掉。~~

具体贪心实现的话，每次花 $6$ 个单位背包空间来装一些东西，枚举所有装东西的方案且每种重量的物品都从价值最大的开始装，直到空间剩余较小停止贪心，然后开始背包。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,f[300001],now[4],sum,sv,ans;
vector<long long> v[4];
inline bool cmp(long long a,long long b){return a>b;}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;++i){
		long long x,y;
		cin>>x>>y;
		v[x].push_back(y);
		sv+=y; sum+=x;
	}
	if (sum<=m){cout<<sv; return 0;}//特判全都能装下的情况 
	for (int i=1;i<=3;++i) sort(v[i].begin(),v[i].end(),cmp);
	now[1]=now[2]=now[3]=-1;
	while (m>=220){//剩这些就完全够了 
		long long tmp1=0,tmp2=0,tmp3=0,tmp4=0,tmp5=0,tmp6=0,tmp7=0;//1*6 1*4+2 1*2+2*2 2*3 1*3+3 1+2+3 3*2共七种方法 
		if (now[1]+6<v[1].size()) tmp1=v[1][now[1]+1]+v[1][now[1]+2]+v[1][now[1]+3]+v[1][now[1]+4]+v[1][now[1]+5]+v[1][now[1]+6];
		if (now[1]+4<v[1].size() && now[2]+1<v[2].size()) tmp2=v[1][now[1]+1]+v[2][now[2]+1]+v[1][now[1]+2]+v[1][now[1]+3]+v[1][now[1]+4];
		if (now[1]+2<v[1].size() && now[2]+2<v[2].size()) tmp3=v[1][now[1]+1]+v[2][now[2]+1]+v[1][now[1]+2]+v[2][now[2]+2];
		if (now[2]+3<v[2].size()) tmp4=v[2][now[2]+1]+v[2][now[2]+2]+v[2][now[2]+3];
		if (now[1]+3<v[1].size() && now[3]+1<v[3].size()) tmp5=v[1][now[1]+1]+v[1][now[1]+2]+v[1][now[1]+3]+v[3][now[3]+1];
		if (now[1]+1<v[1].size() && now[2]+1<v[2].size() && now[3]+1<v[3].size()) tmp6=v[1][now[1]+1]+v[2][now[2]+1]+v[3][now[3]+1];
		if (now[3]+2<v[3].size()) tmp7=v[3][now[3]+1]+v[3][now[3]+2];
		if (tmp1>=tmp1 && tmp1>=tmp2 && tmp1>=tmp3 && tmp1>=tmp4 && tmp1>=tmp5 && tmp1>=tmp6 && tmp1>=tmp7) ans+=tmp1,now[1]+=6;
		else if (tmp2>=tmp1 && tmp2>=tmp2 && tmp2>=tmp3 && tmp2>=tmp4 && tmp2>=tmp5 && tmp2>=tmp6 && tmp2>=tmp7) ans+=tmp2,now[1]+=4,++now[2];
		else if (tmp3>=tmp1 && tmp3>=tmp2 && tmp3>=tmp3 && tmp3>=tmp4 && tmp3>=tmp5 && tmp3>=tmp6 && tmp3>=tmp7) ans+=tmp3,now[1]+=2,now[2]+=2;
		else if (tmp4>=tmp1 && tmp4>=tmp2 && tmp4>=tmp3 && tmp4>=tmp4 && tmp4>=tmp5 && tmp4>=tmp6 && tmp4>=tmp7) ans+=tmp4,now[2]+=3;
		else if (tmp5>=tmp1 && tmp5>=tmp2 && tmp5>=tmp3 && tmp5>=tmp4 && tmp5>=tmp5 && tmp5>=tmp6 && tmp5>=tmp7) ans+=tmp5,now[1]+=3,++now[3];
		else if (tmp6>=tmp1 && tmp6>=tmp2 && tmp6>=tmp3 && tmp6>=tmp4 && tmp6>=tmp5 && tmp6>=tmp6 && tmp6>=tmp7) ans+=tmp6,++now[1],++now[2],++now[3];
		else ans+=tmp7,now[3]+=2; 
		m-=6;
	}
	for (int pp=1;pp<=3;++pp)//剩下一点空间背包 
	for (int i=now[pp]+1;i<v[pp].size();++i) for (int j=m;j>=pp;--j) f[j]=max(f[j],f[j-pp]+v[pp][i]);
	long long anss=0;
	for (int i=0;i<=m;++i) anss=max(anss,f[i]);
	cout<<ans+anss;
return 0;
}
```

---

## 作者：xuchuhan (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF808E)

## Preface

做完近似于强化版的[这道题](https://loj.ac/p/6039)来做了本题。

## Description

0-1 背包问题，但 $n,m$ 都很大。

## Analysis

发现 $n,m$ 都很大但 $c_i$ 很小，考虑是否可以将复杂度往 $c_i$ 靠拢。

将所有 $c_i$ 相同的物品分为一组，对于每组按价值从大到小排序，则形成分组背包。设 $dp_{i,j}$ 表示前 $i$ 组选了体积为 $j$ 所得最大价值，$s_{i,j}$ 表示第 $i$ 组前 $j$ 个物品的 $w_i$ 之和，即价值之和。

则有 $dp_{c,i}=\max_{k=0}^{\lfloor\frac{i}{c}\rfloor} dp_{c-1,i-k\times c}+s_{c,k}$。此时发现 $i,i-k\times c$ 除以 $c$ 的余数相同。

第一维当然可以滚动数组滚掉，我们再把第二维换个形式：$dp_{i\times c+t}=\max_{j=0}^{i}dp_{j\times c+t}+s_{i-j}$。其中 $t$ 当然是余数。设 $f(x)=dp_{x\times c+t},w(l,r)=\sum_{i=l}^r w_i=s_r-s_{l-1}$，则有 $f(i)=\max_{j=0}^{i} f(j)+w(1,i-j)$。

稍加推导就可发现 $w(l,r)$ 满足四边形不等式，所以 $f(x)$ 满足决策单调性，可以用分治求解。

## Code

```cpp
//部分变量名字与文章描述存在出入 
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=305,M=1e6+5;
int n,K,m;
int p[M],sum[M],g[M],dp[M];//dp,g是滚动数组 
vector<int>v[N];
void divide(int l,int r,int L,int R){ //分治求解 
	if(l>r)
		return;
	int mid=(l+r)/2,pos=mid; //注意pos初始值要赋为mid 
	for(int i=L;i<=min(mid,R);i++)
		if(g[p[mid]]<dp[p[i]]+sum[mid-i])
			g[p[mid]]=dp[p[i]]+sum[mid-i],pos=i; //求解答案 
	divide(l,mid-1,L,pos);
	divide(mid+1,r,pos,R);
	return;
}
signed main(){
	cin>>n>>K;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
	}
	for(int i=1;i<=3;i++){//c[i]<=3
		sort(v[i].begin(),v[i].end());
		reverse(v[i].begin(),v[i].end()); //从大到小排序 
		sum[0]=0;
		for(int j=0;j<v[i].size();j++)
			sum[j+1]=sum[j]+v[i][j];
		for(int j=v[i].size()+1;i*j<=K;j++)
			sum[j]=sum[j-1];
		//求取前缀和 
		for(int j=0;j<=K;j++)
			g[j]=0; 
		for(int j=0;j<i;j++){ 
			m=0;
			for(int k=j;k<=K;k+=i)
				p[++m]=k;
			//p[i]:第i个mod c[i]=j的数 
			if(m) 
				divide(1,m,1,m);//分治求解 
		}
		for(int j=0;j<=K;j++)
			dp[j]=g[j]; 
		//滚动数组 
	}
	for(int j=1;j<=K;j++)
		dp[j]=max(dp[j],dp[j-1]);//j-1的代价能取到的,j的代价当然也能取到 
	cout<<dp[K]; 
	return 0;
}
```

如读者发现错误或是存在疑问，欢迎私信或评论指出。

完结撒花！

---

## 作者：紊莫 (赞：2)

一个牛逼又好写的做法！

首先，因为 $w$ 很小，我们可以先把物品按照性价比排序，然后贪心的选择，最后在小范围内背包（$m \le 300$）。

这样的话会 WA on #21，因为会被形如这样的数据卡掉：

```
4001 12000
1 10000
3 10001
3 10001
3 10001
3 10001
3 10001
3 10001
3 10001
3 10001
3 10001
3 10001
...
```

这样的话虽然 $1$ 的性价比更高，但是会导致钱浪费了，于是我们可以反悔一下，在价格为 $1, 2, 3$ 中分别选择一个最小的价值去返回，然后继续做背包即可。

为什么只需要反悔一个呢？假设我们在上面反悔了多个，显然 $\sum w \ge 6$ 肯定是不优的，如果在之前反悔了很多，然后在下面选这么多肯定还不如之前的。

对于 $\sum w < 6$ 的情况也可以类似去考虑分讨。

然后就做完了。

```cpp
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
const int N = 100005, M = (N << 1), inf = 1e16, mod = 1e9 + 7;
int n, m, ans, sum, f[10], x[4];
struct node {
    int w, c;
    bool operator < (node x) const { return w * x.c < c * x.w; }
} a[N];
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    F(i, 1, n) cin >> a[i].w >> a[i].c;
    sort(a + 1, a + n + 1);
    int pos = 1;
    memset(x, 0x3f, sizeof x);
    while (m > 6 && pos <= n) {
        m -= a[pos].w, sum += a[pos].c;
        if (x[a[pos].w] > a[pos].c) x[a[pos].w] = a[pos].c; pos++;
    }
    if (pos > n) cout << sum, exit(0);
    memset(f, 0xcf, sizeof f); f[0] = 0; 
    F(i, pos, n) dF(j, m + 3, a[i].w) f[j] = max(f[j], f[j - a[i].w] + a[i].c);
    F(i, 1, m + 3) f[i] = max(f[i], f[i - 1]);
    F(i, 1, 3) if (x[i] < inf) ans = max(ans, sum - x[i] + f[m + i]);
    cout << max(ans, sum + f[m]) << '\n';
    return 0;
}

```

---

## 作者：hgckythgcfhk (赞：2)

先按重量分组，对每一组降序排序，选前面的一定比选后面的不劣，把每 $6$ 个单位我容量分为 $1$ 组，每次计算每组的最优方案，然后把选过的删掉，再对剩下的进行 01 背包。

目前已经有一篇[题解](https://www.luogu.com.cn/blog/lanos212/solution-cf808e)介绍了这个方法，但是这篇题解写的大分讨实在是一言难尽，~~因为我的实现能力很差~~所以我会给出一种比较友好的实现方式。

维护 $3$ 个指针 $p_1$、$p_2$、$p_3$，枚举每组选几个，这样的花费和价值都是好计算的，一共有 $6\times3\times2=36$ 中**可能**（后面会解释）合法的方案，加个 break 优化一下跑不满，但是没必要，所以这里可以视为 $O(1)$。这样枚举既避免了大型分讨导致的容易出错，又方便通过前缀和计算贡献来避免写很多元素加来加去和一堆烦人且容易写错的常数。

注意，这里的指针表示的是**第一个没选过的元素**的位置，不是最后一个选过的元素的位置。

最后把每组从指针所指的开始后面全存到一个数组进行背包，不要直接在原数组背包，因为我们已经把所有元素分成了 $3$ 组，如果直接用原数组会出现需要判空等不必要的麻烦。

这样实现起来很简单，一共不到 $30$ 行，而且有几处是复读机和可有可无的卡常实际上除了复制粘贴只需要写不到 $20$ 行。

一个注意事项，不要把 $m$ 卡的很死，一定到小于 $6$ 才肯放过它，这样会导致循环过程中凑不够 $6$ 容易写错，这就是上文说的可能，把 $m$ 剩的大一点，看似这个时间复杂度是 $O(res_n\times res_m)$ 的，但是 $res_n$ 一定不大于 $res_m$ 因为当它最大的时候是剩下的都是一些 $1$ 的时候，否则一定不会更大，也就是说，我们可以把 $m$ 剩下 $10^3$，事实上，由于时限是 $3s$，所以如果卡常卡的好剩到 $2\times10^4$ 甚至更大一点也能过~~说不定指令集+暴力+乱剪枝也能过~~。

```
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int register unsigned
#define void inline void
#define ll long long
using namespace std;constexpr unsigned N=3e5+1;inline unsigned ll max(cit ll a,cit ll b){return a>b?a:b;}
unsigned ll a[4][N],dp[1001],w[N],v[N],ans,sz[4],p1=1,p2=1,p3=1;
inline bool cmp(cit ll&x,cit ll&y){return x>y;}
#define get(w,l,r) (ll)(a[w][r]-a[w][l-1])
signed main(){open;int n,m;cin>>n>>m;
	while(n--){int ll b,c;cin>>b>>c;a[b][++sz[b]]=c;}
	sort(a[1]+1,a[1]+sz[1]+1,cmp);for(int i=1;i<=sz[1];++i)a[1][i]+=a[1][i-1];
	sort(a[2]+1,a[2]+sz[2]+1,cmp);for(int i=1;i<=sz[2];++i)a[2][i]+=a[2][i-1];
	sort(a[3]+1,a[3]+sz[3]+1,cmp);for(int i=1;i<=sz[3];++i)a[3][i]+=a[3][i-1];
	while(m>1000){int ll t1,t2,t3,res=0;
		for(int ll i1=0;i1<=6&&p1+i1-1<=sz[1];++i1)//1*6=6，所以1最多选6个
			for(int ll i2=0;i2<=3&&p2+i2-1<=sz[2];++i2)//同理2最多选3个
				for(int ll i3=0;i3<=2&&p3+i3-1<=sz[3];++i3)//不考虑size选满一定比不选满优，所以不用考虑小于6，而大于6被判掉，所以一定等于6 
					if(i1+i2*2+i3*3<=6&&get(1,p1,p1+i1-1)+get(2,p2,p2+i2-1)+get(3,p3,p3+i3-1)>res)
					res=get(1,p1,p1+i1-1)+get(2,p2,p2+i2-1)+get(3,p3,p3+i3-1),t1=i1,t2=i2,t3=i3;
		p1+=t1,p2+=t2,p3+=t3;ans+=res,m-=t1+t2*2+t3*3;}
	for(int i=p1;i<=sz[1];++i)v[++sz[0]]=get(1,i,i),w[sz[0]]=1;
	for(int i=p2;i<=sz[2];++i)v[++sz[0]]=get(2,i,i),w[sz[0]]=2;
	for(int i=p3;i<=sz[3];++i)v[++sz[0]]=get(3,i,i),w[sz[0]]=3;
	for(int i=1;i<=sz[0];++i)for(int j=m;j>=w[i];--j)dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
	cout<<dp[m]+ans;}
```

再给出一个错误做法，蒟蒻不会形式化的证明，但是数据证明这个做法错了，大家看看怎么证明。

排序后每组一定选一个前缀，对于每个 $i \le m$，从 $3$ 到 $1$ 枚举，二分一个位置 $p$，使得 $dp_i+dp_{i-p\times w} $ 更劣，决策点大概率在 $p$ 附近，但是事实上，这个做法被 hack 了，但是什么情况下不对呢？我没有推出一般的规律，一个 hack 是第 $13$ 组数据，具体见 CF 主站，欢迎大家对这个做法证伪。

---

## 作者：daitouzero (赞：2)

一眼即可发现这是个背包问题，但 $n,m$ 都很巨大，直接爆做 01背包下界就是 $O(nm)$，铁定过不了。

01背包复杂度下界都过不了说明肯定有特殊条件，然后你观察数据范围发现这物品的代价很小。

有个非常显然的贪心就是代价相同的物品先选大的，我们尝试把代价相同的物品放在一起来考虑，类似分组背包。

那么设 $dp_{i,j}$ 是已经考虑过代价在 $1$ 到 $i$ 之间的物品后，总代价为 $j$ 时的最大价值。

易有 DP 方程 $dp_{i,j}=\max(dp_{i-1,j-ki}+s_{i,k})$，$s_{i,k}$ 表示代价为 $i$ 的物品中价值前 $k$ 大的价值和。

这个方程看起来不能直接单调队列优化，那就猜猜有没有决策单调性，然后你发现貌似随着 $i$ 的后挪这个 $k$ 也不会往前挪，因为这个 $s_i$ 的差分是单调递减的。

想到这里这题就完了，若用分治写决策单调性的话代码也很短，没什么坑点。总复杂度是 $Cm\log m$，$C$ 是代价的最大值。

代价更大版本的见 [LOJ6039](https://loj.ac/p/6039)。

代码如下：~~自认为还行~~

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<climits>
#include<random>
#include<cassert>
#include<vector>
#include<queue>
#include<cmath>
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
const int N=1e6+5;
int n,K;
std::vector<ll>S[305];
ll f[N],pre[N],g[N],point[N],tot;
inline void solve(int l,int r,int L,int R)
{
    int mid=(l+r)/2,p=mid;
    for (int i=L;i<=std::min(mid,R);i++)
        if (g[point[mid]]<f[point[i]]+pre[mid-i])
        {
            g[point[mid]]=f[point[i]]+pre[mid-i];
            p=i;
        }
    if (l<mid) solve(l,mid-1,L,p);
    if (mid<r) solve(mid+1,r,p,R);
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);
    std::cin>>n>>K;
    for (int i=1;i<=n;i++)
    {
        ll C,V;
        std::cin>>C>>V;
        S[C].push_back(V);
    }
    for (int i=1;i<=300;i++)
    {
        if (S[i].empty()) continue;
        std::sort(S[i].begin(),S[i].end(),
            [](auto x,auto y){return x>y;});
        for (int j=1;j<=S[i].size();j++)
            pre[j]=pre[j-1]+S[i][j-1];
        for (int j=S[i].size()+1;j*i<=K;j++)
            pre[j]=pre[j-1];
        for (int j=0;j<=K;j++) g[j]=0;
        for (int j=0;j<i;j++)
        {
            tot=-1;
            for (int k=j;k<=K;k+=i)
                point[++tot]=k;
            if (~tot) solve(0,tot,0,tot);
        }
        for (int j=0;j<=K;j++) f[j]=g[j];
    }
    std::cout<<f[K];
    return 0;
}
```

---

## 作者：Mihari (赞：2)

# 题目

[传送门](http://codeforces.com/problemset/problem/808/E)

# 题解

这道题有两种做法，前者 $\mathcal O(n)$，后者 $\mathcal O(n\log_{\frac{3}{2}}n)$ .（此处将 $n,m$ 视作同阶，不作明显区分）

首先定义 $a[i][j]$ 为重量为 $i$ 而价格在重量为 $i$ 的第 $j$ 贵的物品.

**方法一 —— DP**

令 $f[i]$ 表示在空间为 $i$ 时，只选重量为 $1$ 和 $2$ 的商品的最大价值，那么我们有初始化 $f[1]=a[1][1]$

而后，我们可以每 $2$ 的跨度为一个单位，每次考虑是选一个 $2$ 物品还是两个 $1$ 物品，进行比较之后更新 $f$ 数组即可

在得到 $f$ 数组之后，我们用 $\mathcal O(\frac{m}{3})$ 的复杂度暴力枚举 $3$ 物品选了多少个，用 $\mathcal O(1)$ 即可算出价值

**方法二 —— 三分查找**

同样的思路，首先暴力枚举选了多少个 $3$ 物品，然后，在重量固定时，以 $2$ 物品的数量为 $x$，定义 $f(x)$ 为价值，可以证明 $f(x)$ 是单峰的

>在 $x$ 越大时，选入的 $2$ 物品价值会越来越小，而剩下的空间来选 $1$ 物品，一定是尽量往大选，所以，当 $f(x)$ 下降时，表示再加入的一个 $2$ 物品价值已经少于扔掉的俩 $1$ 物品的价格，而扔掉的 $1$ 物品会随 $x$ 增加而越来越大，而加入的 $2$ 物品价值会随 $x$ 增加而越来越小，所以，当 $f(x)$ 开始下降之后，就没有可能再增加，即可证明 $f(x)$ 是单峰的，所以可以使用三分

那么，外圈枚举 $3$ 物品，对于每一个 $i$ 做三分，最后标记最大价值即可.

# 代码

**方法一与方法二**

```cpp
https://www.cnblogs.com/Arextre/p/13379824.html
```


---

## 作者：UperFicial (赞：1)

感觉与楼下的分类讨论 DP 做法不是很一样啊。

同样是只考虑 $w_1,w_2$ 两个重量的物品，设 $f_i$ 表示重量为 $i$ 时的最大价值。

然后就考虑最后选取的某个重量的物品，一定是将价格从大到小排序后的一段前缀。

那么，对于 $f_i$，它可以是 $f_{i-1}$ 选取一个 $w_1$ 后得来，或者 $f_{i-2}$ 选取两个 $w_1$ 或者一个 $w_2$ 得来。

对于从 $f_{i-1}$ 的转移，我们显然只要求 $f_{i-1}$ 选取 $w_1$ 的数量尽量少，才能得到一个最大的 $w_1$，当然若要选取 $w_2$，我们应当让 $w_2$ 选取的尽量少。

所以说就可以记录端点 $p_{i,0/1}$，表示当重量为 $i$ 时，$w_1$ 选取的尽量少 / $w_2$ 选取的尽量少时，选取了多少个 $w_1$。

然后求出 $f$ 之后，就可以枚举选取了多少个 $w_3$ 加起来就行了。

代码我还没写，但昨晚我真的和 lzqy 炫饭了。

Update 2.20 11:44：

妈的傻逼，真你妈难写，调了老子两个小时。

我就不信还有傻逼会用这种做法。

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<set>
#include<vector>
#include<queue>
#include<stack>
#include<cstring>
#include<cstdlib>
#include<ctime>
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define rev(i,a,b) for(register int i=a;i>=b;--i)
#define gra(i,u) for(register int i=head[u];i;i=edge[i].nxt)
#define Clear(a) memset(a,0,sizeof(a))
#define yes puts("YES")
#define no puts("NO")
using namespace std;
typedef long long ll;
const int INF(1e9+10);
const ll LLINF(1e18+10);
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
template<typename T>
inline T Min(T x,T y){return x<y?x:y;}
template<typename T>
inline T Max(T x,T y){return x>y?x:y;}
template<typename T>
inline void Swap(T&x,T&y){T t=x;x=y;y=t;return;}
template<typename T>
inline T Abs(T x){return x<0?-x:x;}

const int MAXN(1e5+10);
const int MAXM(3e5+10);

int n,m;
vector<int>G[4]; 
ll f[MAXM];
int pos[MAXM][2];

inline bool cmp(int x,int y){return x>y;}

int main()
{
//	freopen("read.txt","r",stdin);
	n=read(),m=read();
	rep(i,1,3) G[i].push_back(INF);
	rep(i,1,n)
	{
		int w=read(),c=read();
		G[w].push_back(c);
	}
	rep(i,1,3) sort(G[i].begin(),G[i].end(),cmp);
	int s1=G[1].size(),s2=G[2].size();
	if(s1!=1)
	{
		f[1]=G[1][1],pos[1][0]=1,pos[1][1]=1;
	}
	rep(i,2,m)
	{
		f[i]=f[i-1],pos[i][0]=pos[i-1][0],pos[i][1]=pos[i-1][1];
		if(pos[i-1][0]+1<s1)
		{
			f[i]=f[i-1]+G[1][pos[i-1][0]+1];
			pos[i][0]=pos[i-1][0]+1;
			if(f[i]==f[i-1]+G[1][pos[i-1][1]+1]) pos[i][1]=pos[i-1][1]+1;
			else pos[i][1]=pos[i-1][0]+1;
		}
		if(i==2&&s2!=1)
		{
			if(f[i]<G[2][1])
			{
				f[i]=G[2][1];
				pos[i][0]=0,pos[i][1]=0;
			}
			else if(f[i]==G[2][1])
			{
				pos[i][0]=0;	
			}
		}
		
		if((i-2-pos[i-2][1])%2==0&&(i-2-pos[i-2][1])/2<s2-1)//一个 w2 
		{
			int p2=(i-2-pos[i-2][1])/2;
			
			
			if(f[i]<f[i-2]+G[2][p2+1])
			{
				f[i]=f[i-2]+G[2][p2+1];
				pos[i][0]=pos[i-2][1],pos[i][1]=pos[i-2][1];
			}	
			else if(f[i]==f[i-2]+G[2][p2+1])
			{
				pos[i][0]=Min(pos[i][0],pos[i-2][1]);
				pos[i][1]=Max(pos[i][1],pos[i-2][1]);
			}
			
			p2=(i-2-pos[i-2][0])/2;
			if(f[i]==f[i-2]+G[2][p2+1])
			{
				pos[i][0]=Min(pos[i][0],pos[i-2][0]);
				pos[i][1]=Max(pos[i][1],pos[i-2][0]);
			}
		 } 
		 
		if(i>=3&&pos[i-2][0]<s1-2)
		{
			int p=pos[i-2][0];
			if(f[i]<f[i-2]+G[1][p+1]+G[1][p+2])
			{
				f[i]=f[i-2]+G[1][p+1]+G[1][p+2];
				pos[i][0]=pos[i-2][0]+2,pos[i][1]=pos[i-2][0]+2;
			}
			else if(f[i]==f[i-2]+G[1][p+1]+G[1][p+2])
			{
				pos[i][0]=Min(pos[i][0],pos[i-2][0]+2);
				pos[i][1]=Max(pos[i][1],pos[i-2][0]+2);
			}
			
			p=pos[i-2][1];
			if(f[i]==f[i-2]+G[1][p+1]+G[1][p+2])
			{
				pos[i][0]=Min(pos[i][0],pos[i-2][1]+2);
				pos[i][1]=Max(pos[i][1],pos[i-2][1]+2);
			}
//			if(f[i]==14) puts("YES");
		}
//			printf("check:%d\n",i);
//			printf("f:%lld\n",f[i]);
//			printf("pos:%d %d\n",pos[i][0],pos[i][1]);
//		puts("");
	}
	ll sum=0,ans=f[m];
	rep(i,1,(int)G[3].size()-1)
	{
		sum+=G[3][i];
		if(i*3<=m) ans=Max(ans,sum+f[m-i*3])/*,printf("%d %lld\n",i,sum+f[m-i*3])*/;
	}
//	if(n==100&&m==101)
//	{
//		printf("%d %d %d\n",s1,s2,G[3].size());
//	}
	printf("%lld\n",ans);
	return 0;
}
/*
6 12
1 7
1 10
2 8
1 2
2 9
3 5
*/
```

---

## 作者：CQ_Bab (赞：1)

# 前言
同学的互测题中出了这道题，赛时用了一种神奇的方法过了发现题解中没有就来发一篇题解。
# 思路
我们发现如果 $v_i\leq 2$ 很好做，就是考虑枚举一个数的个数然后就是一个经典贪心了，那么这道题中 $v_i\leq 3$ 所以考虑也用相同的思路假设我们枚举 $2$ 选了几个那么能算出剩的空间为 $m-2\times x$ 所以我们只需要预处理出在空间剩下 $i$ 的情况下只用 $1$ 和 $3$ 能获得的最大价值，那么我们定义 $f_i$ 为上述状态然后考虑转移 $f_i=\max(f_{i-1}+Max_{i-1,1},f_{i-3}+Max_{i-3,3})$ 这里用 $Max_{i,j}$ 表示在 $f_{i}$ 最优的前提下 $j$ 在空间用 $i$ 是能拿到的最大价值，然后我们发现这里从 $i-1$ 和 $i-3$ 来之后最大的是一定不会再还回去的所以考虑对于每一个 $m$ 都建立两棵主席树（一个存 $1$ 一个存 $3$）然后我们只需要在主席树上找最大值即可，然后答案就是 $\max(Ans_i+f_{m-2\times i})$，这里的 $Ans_i$ 表示 $2$ 中前 $i$ 大的值的和。

注意要离散化不然空间开不下。
# 代码
~~石山代码~~。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define ll long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n,m;
const int N=3e5+10,M=1e9;
struct node{
	int l,r,cnt;
}tr_1[N*35],tr_3[N*35];
int rt[N],rt1[N];
int idx,idx1;
void up(int x) {
	tr_1[x].cnt=tr_1[tr_1[x].l].cnt+tr_1[tr_1[x].r].cnt;
}
void up1(int x) {
	tr_3[x].cnt=tr_3[tr_3[x].l].cnt+tr_3[tr_3[x].r].cnt;
}
int arr[N],tot;
int modify(int u,int l,int r,int k,int c) {
	int p;
	p=++idx;
	tr_1[p]=tr_1[u];
	if(l==r) {
		tr_1[p].cnt+=c;
		return p;
	}
	int mid=l+r>>1;
	if(mid>=k) {
		tr_1[p].l=modify(tr_1[p].l,l,mid,k,c);
	}
	else tr_1[p].r=modify(tr_1[p].r,mid+1,r,k,c);
	up(p);
	return p;
}
int modify1(int u,int l,int r,int k,int c) {
	int p=++idx1;
	tr_3[p]=tr_3[u];
	if(l==r) {
		tr_3[p].cnt+=c;
		return p;
	}
	int mid=l+r>>1;
	if(mid>=k) tr_3[p].l=modify1(tr_3[p].l,l,mid,k,c);
	else tr_3[p].r=modify1(tr_3[p].r,mid+1,r,k,c);
	up1(p);
	return p;
}
int Ans(int u,int l,int r,int k) {
	if(l==r) return l;
	int mid=l+r>>1;
	if(tr_1[tr_1[u].r].cnt) return Ans(tr_1[u].r,mid+1,r,k);
	return Ans(tr_1[u].l,l,mid,k);
}
int Ans1(int u,int l,int r,int k) {
	if(l==r) return l;
	int mid=l+r>>1;
	if(tr_3[tr_3[u].r].cnt) return Ans1(tr_3[u].r,mid+1,r,k);
	return Ans1(tr_3[u].l,l,mid,k);
}
priority_queue<int>q;
ll f[N];
vector<int>th,one;
void solve() {
	in(n),in(m);
	idx=idx1=false;
	while(q.size()) q.pop();
	int vv=false;
    rt[0]=rt1[0]=1;
	rep(i,1,n) {
		int v,w;
		in(v),in(w);
		if(v==2) q.push(w);
		else {
			if(v==1) one.pb(w),arr[++tot]=w,vv++;
			if(v==3) th.pb(w),arr[++tot]=w,vv+=3;
		}
	}
	sort(arr+1,arr+1+tot);
	int mm=unique(arr+1,arr+1+tot)-arr-1;
	for(auto to:one) {
		to=lower_bound(arr+1,arr+1+mm,to)-arr;
		rt[0]=modify(rt[0],1,mm,to,1);
	}
	for(auto to:th) {
		to=lower_bound(arr+1,arr+1+mm,to)-arr;
		rt1[0]=modify1(rt1[0],1,mm,to,1);
	}
    rep(i,0,m) f[i]=false;
	rep(i,1,min(vv,m)) {
		ll dis=-1;
		int kk=0;
		if(tr_1[rt[i-1]].cnt>=1) kk=Ans(rt[i-1],1,mm,1),dis=f[i-1]+1ll*arr[kk];
		ll dis1=-1;
		int kk1=0;
		if(tr_3[rt1[i-3]].cnt>=1) kk1=Ans1(rt1[i-3],1,mm,1),dis1=f[i-3]+1ll*arr[kk1];
		if(dis==dis1&&dis==-1) {
			rt[i]=rt[i-1];
			rt1[i]=rt1[i-1];
			f[i]=f[i-1];
			continue;
		}
		if(dis>dis1) {
			rt[i]=rt[i-1];
			rt[i]=modify(rt[i],1,mm,kk,-1);
			rt1[i]=rt1[i-1];
		}else {
			rt[i]=rt[i-3];
			rt1[i]=rt1[i-3];
			rt1[i]=modify1(rt1[i],1,mm,kk1,-1);
		}
		f[i]=max({dis,dis1});
	}
	ll res=0;
	rep(i,1,m) {
		res=max(res,f[i]);
		f[i]=res;
	}
	int len=q.size();
	ll sum=false;
	rep(i,1,min(len,m/2)) {
		sum+=1ll*q.top();
		q.pop();
		res=max(res,sum+f[m-2*i]);
	}
	printf("%lld\n",res);
}
fire main() {
	T=1;
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：StaroForgin (赞：0)

~~竟然没有用三分做的人，赶紧来发一发~~

因为它总共只有三种重量，先根据重量分组，显而易见，如果要在任意一组中选择一定的礼品，则我们一定会选择其中价值最大的部分，可以先将每组礼物内按价格先排好序。

显而易见，如果已经知道了2,3两组的各自买的数量，则第一组买的数量也是可以求出来的。故而，枚举二三组选的数量，再得出总价值是一定可以得出答案的。

但上述做法时间复杂度达到了  
$$ O(n^{2})$$  
明显是过不了这道题的，考虑优化。

我们发现，再枚举1，2两组分界线时，会出现一个单峰函数，于是可以用三分来寻找它的最高点。但是再这个单峰上会出现平台，影响我们的判断，说以需要再平台出现时，对其进行特殊处理，将右端舍弃，只取左端。

于是，就可以
$$ O(nlog_{n})$$
的时间中处理掉了。

## 源码
~~有些难调~~
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<bitset>
using namespace std;
typedef long long LL;
#define gc() getchar()
template<typename _T>
void read(_T &x){
	_T f=1;x=0;char s=gc();
	while(s>'9'||s<'0'){if(s=='-')f=-1;s=gc();}
	while(s>='0'&&s<='9'){x=(x<<3)+(x<<1)+(s^48);s=gc();}
	x*=f;
}
LL n,m,ans;
vector<LL>c[5];
bool cmp(LL x,LL y){return x>y;}
LL check(LL x,LL y){
	//printf("%d %d\n",x,y/2);
	if(y%2)x++;
	if(c[1].size()==0||x==0)x=0;
	else x=c[1][min(x-1,(LL)c[1].size()-1)];
	if(c[2].size()==0||y<2)y=0;
	else y=c[2][min(y/2-1,(LL)c[2].size()-1)];
	return x+y;
}
signed main(){
	read(n);read(m);
	for(int i=1;i<=n;i++){
		LL W,C;read(W);read(C);
		c[W].push_back(C);
	}
	for(int i=1;i<4;i++)sort(c[i].begin(),c[i].end(),cmp);
	for(int i=1;i<4;i++){
		int siz=c[i].size();
		for(int j=1;j<siz;j++)
			c[i][j]+=c[i][j-1]; 
	}
	for(int i=0;i<=c[3].size()&&i*3<=m;i++){
		LL l=0,r=min(m-3*i,(LL)c[1].size()),tmp=m-3*i;
		//printf("%d %d %d\n",tmp,l,r);
		if(c[1].size()+2ll*c[2].size()<=tmp)
			ans=max(ans,(i?c[3][i-1]:0)+check(c[1].size(),2ll*c[2].size()));
		else{
			while(l<r){
				LL mid1=l+(r-l)/3;
				LL mid2=r-(r-l)/3;
				LL tmp1=check(mid1,tmp-mid1);
				LL tmp2=check(mid2,tmp-mid2);
				if(tmp1>tmp2)r=mid2-1;
				else l=mid1+1;
				//printf("%d %d %d %d\n",mid1,mid2,tmp1,tmp2);
				//printf("%d %d %d\n",i,l,r);
			}
			ans=max(ans,(i?c[3][i-1]:0)+check(l,tmp-l));
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Holy_Push (赞：0)

这道题真的调的我心态爆炸啊……可能是我太菜了。

一开始看到这道题，你的想法是：这不是裸背包嘛？

打到一半，你的想法是：这数据不像是背包能过的题？

再过一会儿，你的想法是：$w_i≤3?$这看起来是一个突破口。

所以我们要针对这个$w_i≤3$来做这道题。这里我给出我做这道题时候的想法。

首先，很自然的把物品按照重量分类，我们暂且把$w_i=1$的叫做一类物品，$w_i=2$的叫做二类物品，$w_i=3$的叫做三类物品。

由于价值要最大，所以我们很自然地想到，我们选的物品肯定是每类中价值最大的物品。于是有一种贪心的做法。

我是蒟蒻$QnQ$，所以我现在认为先全部选三类物品，再全部选二类物品，再拿剩下的选一类物品方案最优。

坐我左边的是$dalao$，他告诉我如果把选取的二类物品价值最低的物品拿掉几个，去换一类物品中价值最大的还没选的物品，能得到更多的价值。

坐我右边的是$julao$，他告诉我如果把选取的一类物品价值最低的物品拿掉几个，去换二类物品中价值最大的还没选的物品，能得到更多的价值。

坐我前面的是$jilao$，他告诉我如果把选取的三类物品价值最低的物品拿掉几个，去换一类二类物品，能得到更多的价值。

我这个蒟蒻受到了极大的打击$QhQ$，正当我要放弃我的做法的时候，坐我后面的$Female-Dressed-dalao$鼓励我说要坚持我的做法$!Q\omega Q!$

于是我把四种结合起来，得到了以下的做法：

1. 先按照蒟蒻的贪心思想，先选完三类物品，再选完二类物品，再选一类物品，转入步骤二。
2. 按照$dalao$和$julao$的思路去调整我们的选择，转入步骤三。
3. 再按照$jilao$的思路，我们每次去掉我们选的价值最低的三类物品，转入步骤四。
4. 再按照蒟蒻的贪心思想，选完二类物品，再选一类物品，转入步骤二。

如此调整下来，我们可以就可以得到我们最终的答案啦！时间复杂度有些玄学，但是能过。

注意开**long long**，否则你连怎么T的都不知道！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int n,m;
vector<int>V[4];
ll ans,val;

signed main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) 
	{
		int W,C;scanf("%d%d",&W,&C);
		V[W].push_back(C);
	}
	int p1=V[1].size(),p2=V[2].size(),p3=V[3].size();
	sort(V[1].begin(),V[1].end());
	sort(V[2].begin(),V[2].end());
	sort(V[3].begin(),V[3].end());//分类
	int r1=V[1].size()-1,r2=V[2].size()-1,r3=V[3].size()-1;
	for (;r3>=0&&m>=3;--r3) val+=V[3][r3],m-=3;
	for (;r2>=0&&m>=2;--r2) val+=V[2][r2],m-=2;
	for (;r1>=0&&m>=1;--r1) val+=V[1][r1],m--;//蒟蒻的第一步想法
	while (r1>=0&&r2<p2-1)
	{
		ll svr1=r1,svr2=r2,svval=val,svm=m;
		m+=2;r2++;val-=V[2][r2];
		while (m&&r1>=0) {val+=V[1][r1];--r1;--m;}
		if (val<=svval) {r1=svr1;r2=svr2;val=svval;m=svm;break;}
	}
	while (r2>=0&&r1<p1-1)
	{
		ll svr1=r1,svr2=r2,svval=val,svm=m;
		while (r1<p1-1&&m<2) ++r1,++m,val-=V[1][r1];
		while (m>=2&&r2>=0) val+=V[2][r2],--r2,m-=2;
		if (val<=svval) {r1=svr1;r2=svr2;val=svval;m=svm;break;}
	}//第二步，不断地调整
	ans=val;
	while (r3<p3-1)
	{
		m+=3;r3++;val-=V[3][r3];
		for (;r2>=0&&m>=2;--r2) val+=V[2][r2],m-=2;
		for (;r1>=0&&m>=1;--r1) val+=V[1][r1],m--;
		while (r1>=0&&r2<p2-1)
		{
			ll svr1=r1,svr2=r2,svval=val,svm=m;
			m+=2;r2++;val-=V[2][r2];
			while (m&&r1>=0) {val+=V[1][r1];--r1;--m;}
			if (val<=svval) {r1=svr1;r2=svr2;val=svval;m=svm;break;}
		}
		while (r2>=0&&r1<p1-1)
		{
			ll svr1=r1,svr2=r2,svval=val,svm=m;
			while (r1<p1-1&&m<2) ++r1,++m,val-=V[1][r1];
			while (m>=2&&r2>=0) val+=V[2][r2],--r2,m-=2;
			if (val<=svval) {r1=svr1;r2=svr2;val=svval;m=svm;break;}
		}
		if (val>ans) ans=val;
	}//第二、三、四步
	cout<<ans<<endl;
} 
```


---

## 作者：AlicX (赞：0)

很好的一道分类讨论题。

观察数据范围，$w \leq 3$，不难想到，将 $w$ 分为 $1,2,3$ 种情况，如果直接贪心选会不难发现是错的。但是如果 $w$ 的值只有 $2$ 种，就像 $w=1/2$ 的情况，将 $w=1/2$ 的数据按价值排序，最后枚举每种选多少即可。但是 $w=3$ 就会显得难以处理，需要讨论将多少种 $w=1/2$ 的商品取出，十分不简洁。

于是考虑贪心选 $w=2/3$ 的，不难想到，可以将 $w=1$ 的两个商品合成一个混进 $w=2$ 的商品中，然后枚举两种商品各占的空间，取最大值即可。

值得注意的地方在于，如果 $w=1$ 的商品个数为奇数，肯定会剩下一个，那么如果要选这一个的话必须让其价值最大。

求解过程中，计算价值为 $O(1)$，合并以及枚举空间都为 $O(n)$，排序为 $O(n \log n)$，所以总时间复杂度为 $O(n \log n)$，可以通过此题。


---

