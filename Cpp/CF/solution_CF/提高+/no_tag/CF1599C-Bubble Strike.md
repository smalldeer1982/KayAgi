# Bubble Strike

## 题目描述

你和你的对手一起玩一个游戏，该游戏共有 $n$ 张地图，系统会先从中随机选择 $3$ 张，你和你的对手需要各自从中选择一张删去（可以相同），系统会在剩下的若干张中随机选一张作为本次游戏的地图

为了赢得更多的胜利，你想预先学习一些地图。但是由于时间有限，你希望学习尽量少的地图，并且满足每次玩到自己学习过的地图的概率至少为 $p$。请问满足条件最少需要学习的地图数是多少。对手不知道你预习了哪些地图。

## 样例 #1

### 输入

```
7 1.0000```

### 输出

```
6```

# 题解

## 作者：龙潜月十五 (赞：6)

## CF1599C Bubble Strike

#### 题目描述

你和你的对手一起玩一个游戏，该游戏共有 $n$ 张地图，系统会先从中随机选择 $3$ 张，然后你和你的对手需要各自从中选择一张删去，剩下的那张就是本次游戏的地图。

为了赢得更多的胜利，你想预先学习一些地图。但是由于时间有限，你希望学习尽量少的地图，并且满足每次玩到自己学习过的地图的概率至少为 $p$。请问满足条件最少需要学习的地图数是多少。

#### 输入格式

第一行包括两个数 $n(3\leq n \leq 10^3)$，$p(0\leq p\leq 1)$ 。$p$ 小数点后最多有四位。

#### 输出格式

一个整数，表示答案。

#### 题解

$n$ 最多只有 $10^3$，因此我们可以直接从小到大枚举学习的地图数 $i$，直到满足条件就直接输出。

考虑如何判断是否满足条件，假设系统已经选出了 $3$ 张牌，那么这 $3$ 张牌的情况有 $4$ 种：

1. 设 $3$ 张牌都学过的情况数为 $d_3$，这种情况下无论如何剩下的都是自己学过的地图；

2. 设有 $2$ 张牌学过的情况数为 $d_2$，同样剩下的也一定是学过的；

3. 设有 $1$ 张牌学过的情况数为 $d_1$，自己一定会删去没学过的地图，剩下 $2$ 张对手删去哪张概率都是 $\frac{1}{2}$，剩下学过的地图概率是 $\frac{d_1}{2}$；

4. 设没有学过的牌的情况数为 $d_0$，那么不可能了。

   因此最后剩下自己学过地图的概率为

$$\frac{d_3+d_2+\frac{d_1}{2}}{d_3+d_2+d_1+d_0}$$

现在考虑 $d$ 怎么计算，设学过 $i$ 张地图，那么 
$$d_3=C_{i}^3\cdot C_{n-i}$$
$$d_2=C_{i}^2\cdot C_{n-i}^1$$
$$d_1=C_{i}^1\cdot C_{n-i}^2$$
$$d_0=C_{i}^0\cdot C_{n-i}^3$$

最后代入上式计算即可。



#### 代码

```cpp
#include<bits/stdc++.h>
#define ln puts("")
#define re register
#define mk make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef long double ld;

inline ll read() {
	ll sum = 0, ff = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')
			ff = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
		sum = sum * 10 + ch - 48, ch = getchar();
	return sum * ff;
}

void write(ll x) {
	if(x < 0)
		x = ~(x - 1), putchar('-');
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

void writesp(ll x) {
	write(x), putchar(' ');
}

void writeln(ll x) {
	write(x), ln;
}

int n;
ld p;

ld c2(int n) {
	return n * (n - 1) / 2;
}

ld c3(int n) {
	return n * (n - 1) * (n - 2) / 6;
}

int main() {
	n = read(), scanf("%Lf", &p);
	for(re int i = 0; i < n; ++i)
		if((c3(i) + c2(i) * (n - i) + i * c2(n - i) / 2) / (c3(i) + c2(i) * (n - i) + i * c2(n - i) + c3(n - i)) >= p)
			return write(i), 0;
	return 0;
}
```









---

## 作者：DepContain (赞：4)

**#### 题目链接 : [Link](https://www.luogu.com.cn/problem/CF1599C)

## Description
给定 $n \in [3, 10^3], p \in [0, 1]$。

你和你的对手一起玩一个游戏，该游戏共有 $n$ 张地图，先从中随机选择 $3$ 张，然后你和你的对手需要各自从中选择一张删去，剩下的那张就是本次游戏的地图。

为了赢得更多的胜利，你想预先学习一些地图。但是由于时间有限，你希望学习尽量少的地图，并且满足每次玩到自己学习过的地图的概率至少为 $p$ 。请问满足条件最少需要学习的地图数是多少。**对手不知道你预习了哪些地图**。


## Solution

~~大水题~~

假设至少需要预先学习 $x$ 张地图。

分类讨论: 
- case1: 

	选取的三张地图中都预习过，
    
   方案数:$ C ^3 _x $ 
   
   选到预先学习过的概率为 $1$。
   
- case2: 

	选取的三张地图中有两张预习过，
    
   方案数:$ C^2 _x \times C^1_{n - x}$ 
   
   选到预先学习过的概率为 $1$。
   
- case3: 

	选取的三张地图中只有一张预习过，
    
   方案数:$C^1 _x \times C^2_{n-x}$ 
   
   选到预先学习过的概率为 $ \frac{1}{2}$。
   
- case4: 

	选取的三张地图中都没有预习过，
    
   方案数:总方案数-以上三种的方案数和$(C^3_{n - x})$
   
   选到预先学习过的概率为 $0$。

观察到 $n \in [3, 10^3]$，

可以从 $0$ 到 $n$ 依次枚举，计算概率, 判断是否合法。

## AC Code
```cpp
#include <bits/stdc++.h>
typedef long long ll;
constexpr int maxn = 2e3 + 10;
using namespace std;

int n;
double p;

double C(int x, int tot) {
	if(tot < x) return 0;
	double ans = 1;
	for(int i = 1; i <= x; ++i) {
		ans *= tot;
		tot--;
	}
	for(int i = 1; i <= x; ++i) ans /= i;

	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n >> p;
	double sum = 0, cnt = C(3, n);
	for(int i = 0; i <= n; ++i) {
		sum = (double)C(3, i) + C(1, i) * C(2, n - i) * 0.5 + C(2, i) * C(1, n - i);
		if(sum >= p * cnt) {
			cout << i;
			return 0;
		}
	}

	return 0;
}
```


---

## 作者：Cute__yhb (赞：1)

[记录](https://codeforces.com/problemset/submission/1599/290502779)

Duel 时抽到的，来水一篇题解。

## 思路

注意到如果学习 $x$ 张地图可行，那么学习 $y (y>x) $ 张地图一定可行，即答案满足单调性。

根据这一点，我们就可以二分答案。

假设当前学习了 $x$ 张地图，分类讨论一下满足条件的情况。

- 三张地图都学习过。

  此时有 $C^{3}_{x}$ 种情况。
  
- 学习过两张地图。

  此时有 $C^{2}_{x} \times C^{1}_{n-x}$ 种情况，我们只要删去没学过的，剩下的我们都学过。

- 只学习过一张地图

  此时有 $C^{1}_{x} \times C^{2}_{n-x} \times \frac{1}{2}$ 种情况，我们肯定删去没学过那张，剩下的两张交给对手删，所以要乘 $\frac{1}{2}$。

- 一张也没学过

  无贡献，不考虑。

最后的概率即为前面所有情况总和除以 $C^{3}_{n}$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define F(i,l,r) for(int i=l;i<=r;i++)
#define UF(i,r,l) for(int i=r;i>=l;i--)
#define p_q priority_queue
#define pb push_back
#define mk make_pair
#define pii pair<int,int> 
#define ve vector
#define endl '\n'
#define fi first
#define se second
#define INF 0x3f3f3f3f
int n;
double p;
bool check(int mid){
	double sum=0;
	if(mid>=1&&n-mid-1>=1){//只有1张
		sum+=3*0.5*mid*(n-mid)*(n-mid-1);
	}
	if(mid>=2&&n-mid>=1){//两张
		sum+=3*mid*(mid-1)*(n-mid);
	}
	if(mid>=3){//3张
		sum+=mid*(mid-1)*(mid-2);
	}
	sum=sum/(1.0*n*(n-1)*(n-2));//除以总方案数
	return sum>=p;
}
int main(){
	cin>>n>>p;
	int l=0,r=n,ans=0;
	while(l<=r){//二分
		int mid=(l+r)/2;
		if(check(mid)){
			r=mid-1;
			ans=mid;//记录答案
		}else l=mid+1;
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：__yun__ (赞：0)

### 思路
设练了 $m$ 张。

- $3$ 张都练过的，方案数为 $C_{m}^3$，有 $1$ 的概率选到练过的，  
概率为 $\frac{C_m^3}{C_n^3}$。

- 有 $2$ 张练过的，方案数为 $C_m^2C_{n-m}^1$，有 $1$ 的概率选到   
练过的（自己删掉没练过的），概率为 $\frac{C_m^2C_{n-m}^1}{C_n^3}$。

- 有 $1$ 张练过的，方案数为 $C_m^1C_{n-m}^2$，有 $0.5$ 的概率  
选到练过的，概率为 $0.5\times \frac{C_m^1C_{n-m}^2}{C_n^3}$。

- 没有练过的，概率为 $0$。

枚举 $m$ 即可。

### $Code:$
```cpp
#include<bits/stdc++.h>
#define int double
using namespace std;
int n,p;
signed main(){
	cin>>n>>p;
	for(int i=0;i<=n;i++){
		int ans=0;
		if(n-i-1>=1) ans+=0.5*(n-i)*(n-i-1)*i*3/(n*(n-1)*(n-2));
		if(n-i>=1) ans+=(n-i)*i*(i-1)*3/(n*(n-1)*(n-2));
		if(i-2>=1) ans+=i*(i-1)*(i-2)/(n*(n-1)*(n-2));
		if(ans>=p){
			cout<<i;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Φρανκ (赞：0)

题意：有 $n$ 张地图，每次选择选其中 $3$ 张，其中弃去一张，任弃一张，剩余地图中随机选一张。要求选中指定 $k$ 张中一张的概率大于等于 $p$，求 $k$ 的最小值。

核心思想：分类讨论

解：

初始 $3$ 张地图可能的情况是：

1. $3$ 张都学习过，显然可以。此情况可以的期望为 $\frac{C^3_k}{C^3_n}$。
2. $3$ 张中两张学习过，去掉剩下一张即可。此情况可以的期望为 $\frac{C^2_kC^1_n}{C^3_n}$。
3. $3$ 张中只学过一张，此时己方选择一张未学过的地图，对手选择己方学过的地图，同一张未学过的地图，另一张未学过的地图，成功的概率分别是 $0,\frac{1}{2},1$，此情况可以的期望为 $\frac{C^1_kC^2_n}{2C^3_n}$。
4. $3$ 张均未学过，显然不可。此情况可以的期望为 $0$。

根据这些情况将 $k$ 从小到大依次枚举即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long double n, p, k;
int main()
{
	cin>>n>>p;
	for(int i=0; i<n; i++)
	{
		k=i;
		if(k*(k-1)*(k-2)+3*k*(k-1)*(n-k)+1.5*k*(n-k)*(n-k-1)>=p*n*(n-1)*(n-2))//比较期望与p
		{
			cout<<i;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：presucc (赞：0)

这题还没有中文翻译。这里提供一个我粗略译的中文版题面。

#### 题目大意
有 $N$ 个棋子，其中 $k$ 个子是黑棋，另外 $N-k$ 个是白棋。从中随机选取三个棋子，你可以去掉其中一个棋子（你知道每个棋子的颜色），再在剩下的两个棋子中随机取出一个。设这个棋子为黑的概率为 $P_k$ 。

你希望取出黑子的概率至少为 $P$. 求出一个最小的 $k$, 使得 $P_k \ge P$.

#### 输入格式

一行，第一个数是正整数 $N(3\le N\le 10^{3})$，表示棋数；接着是一个小数 $P(0\le P\le1)$, 表示所需概率。两个数用空格隔开，保证 $P$ 的小数点后至多有四位。

#### 输出格式

一行，一个正整数 $k$. 表示黑棋的最少数量。


### 做法

一道比较水的 $2000$ 分题。

考虑有 $k$ 个黑棋时，每次操作取到黑棋的平均概率。

因为每次都是完全随机去取，所以总的黑棋期望数除以总取法数就等于概率了。

总取法数为从 $n$ 个子中取 $3$ 个，即 $C^{3}_{n}$.

接下来算每个情况中黑棋被取到的期望次数。

**情况 $1$**

如果取到的白棋有 $0$ 个，黑棋有 $3$ 个，则方案数为 $C^{3}_{k}\times C^{0}_{n-k}=C^{3}_{k}$. 

无论怎么随机取，因为这三个都是黑色的，所以最终一定能取到黑色的，即单次取到黑棋的期望次数为 $1$ ，总期望为 $C^{3}_{k}\times 1$.

**情况 $2$**

如果取到的白棋有 $1$ 个，黑棋有 $2$ 个，则方案数为 $C^{2}_{k}\times C^{1}_{n-k}$. 

你取到了两黑一白，那么只需要把那个白色的丢掉即可。这样能保证你一定能取到黑棋。单次取到黑棋的期望次数为 $1$ ，则总期望为 $C^{2}_{k}\times C^{1}_{n-k}\times 1$.

**情况 $3$**

如果取到的白棋有 $2$ 个，黑棋有 $1$ 个，则方案数为 $C^{1}_{k}\times C^{2}_{n-k}$. 

为了尽量取到黑棋，你需要把一个白棋丢掉。此时还剩下一黑一白。接下来的选棋是随机的，所以单次取到黑棋的期望次数为 $\frac{1}{2}$，总期望为 $C^{1}_{k}\times C^{2}_{n-k}\times \frac{1}{2}$.

**情况 $4$**

如果取到的白棋有 $3$ 个，黑棋有 $0$ 个，则方案数为 $C^{0}_{k}\times C^{3}_{n-k}=C^{3}_{n-k}$. 

三个棋全是白棋，那无论如何都取不到黑棋。期望次数为 $0$ ，总期望次数也为 $0$.

把上面四种情况的期望加起来再除以总次数，就得到了 $k$ 个黑棋时的概率。

枚举 $k$ 从 $0$ 到 $n$，第一个能使取黑棋概率大于等于 $P$ 的 $k$ 即所求。

代码实现非常简单。时间复杂度 $O(n)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define db double
const int maxn=100010;
db ans,p;
int n;
int C(int n,int m)
{
	if (n==0||n<m) return 0;
	int res=1;
	for (int i=1;i<=m;i++) res*=n-i+1;
	for (int i=1;i<=m;i++) res/=i;
	return res;
}
int main()
{
	scanf("%d%lf",&n,&p);
	int all=C(n,3);
	for (int i=0;i<=n;i++)
	{
		int h0b3=C(n-i,3),h1b2=C(n-i,2)*C(i,1),h2b1=C(n-i,1)*C(i,2),h3b0=C(i,3);
		db res=h0b3*0+h1b2*0.5+h2b1*1.0+h3b0*1.0;
		if (res>=p*(db)all) printf("%d\n",i),exit(0);
	}
}
```

---

