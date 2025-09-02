# Array Walk

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , consisting of $ n $ positive integers.

Initially you are standing at index $ 1 $ and have a score equal to $ a_1 $ . You can perform two kinds of moves:

1. move right — go from your current index $ x $ to $ x+1 $ and add $ a_{x+1} $ to your score. This move can only be performed if $ x<n $ .
2. move left — go from your current index $ x $ to $ x-1 $ and add $ a_{x-1} $ to your score. This move can only be performed if $ x>1 $ . Also, you can't perform two or more moves to the left in a row.

You want to perform exactly $ k $ moves. Also, there should be no more than $ z $ moves to the left among them.

What is the maximum score you can achieve?

## 说明/提示

In the first testcase you are not allowed to move left at all. So you make four moves to the right and obtain the score $ a_1 + a_2       + a_3 + a_4 + a_5 $ .

In the second example you can move one time to the left. So we can follow these moves: right, right, left, right. The score will be $ a_1 + a_2 + a_3 + a_2 + a_3 $ .

In the third example you can move four times to the left but it's not optimal anyway, you can just move four times to the right and obtain the score $ a_1 + a_2 + a_3 + a_4 + a_5 $ .

## 样例 #1

### 输入

```
4
5 4 0
1 5 4 3 2
5 4 1
1 5 4 3 2
5 4 4
10 20 30 40 50
10 7 3
4 6 8 2 9 9 7 4 10 9```

### 输出

```
15
19
150
56```

# 题解

## 作者：钓鱼王子 (赞：16)

DP

设 $dp_{i,j}$ 为耗费了 $i$ 次向左走的机会，当前在位置 $j$ 的最大收益。

显然，转移为 $dp_{i,j}=\max(dp_{i,j-1},dp_{i-1,j+1})+a_j$。

注意当 $j=n$ 时不能从右边转移。

到某个状态走的步数即为 $i\times 2+j$，当这个数为给定的步数时求一个 $\max$。

```cpp
#include<bits/stdc++.h>
#define re register
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
} 
using namespace std;
int n,m,a[1000002],k,dp[100002][6],ans,t;
int main(){
	t=read();
	while(t--){
		n=read(),m=read(),k=read();ans=0;
		for(re int i=1;i<=n;++i)a[i]=read();
		for(re int i=0;i<=k;++i){
			for(re int j=1;j<=n;++j){
				dp[j][i]=dp[j-1][i]+a[j];
				if(i&&j!=n)dp[j][i]=max(dp[j][i],dp[j+1][i-1]+a[j]);
				if(j-1+i*2==m)ans=max(ans,dp[j][i]);
			}
		}
		printf("%d\n",ans);
	}
}
```


---

## 作者：Yizhixiaoyun (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/CF1389B)

此题似乎很多 $\text{dp}$ 题解，这里分享一篇同机房大佬的**贪心**题解。

## 题目分析

由于这道题说明了不能连续向左走两步，那么**如果要向左走，接下来一步一定要向右走，也就是进行了“横跳”**。

我们要做的，就是想办法让“横跳”的收益最大化。

此时有两种情况：

**- 最后一步向右走**

此时我们就可以轻松找到最大收益的“横跳”，即找到 $a_i + a_{i+1}$ 的最大值。

**核心代码：**

```cpp
for(register int i=0;i<=min(z,num/2);++i) ans=max(ans,sum[num-i*2]+b[num-i*2]*i)
```

**- 最后一步向左走**

由于不能连续向左走两步，所以上一步一定是向右走的。此时转化成为最后一步向右走的情况，单独计算最后一步即可。

**核心代码：**

```cpp
for(register int i=1;i<=min(z,num/2);++i) ans=max(ans,sum[num-2*(i-1)-1]+b[num-2*(i-1)-1]*(i-1)+sum[num-2*(i-1)-2]-sum[num-2*(i-1)-3])
```

最后，别忘了使用**前缀和**维护！

## 贴上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int T;
int n,k,z,ans,tot,num;
int a[maxn],b[maxn],sum[maxn];
int main(){
    cin>>T;
    while(T--){
        memset(b,0,sizeof(b));
        ans=0;
        cin>>n>>k>>z;num=k+1;
        for(register int i=1;i<=n;++i) cin>>a[i];
        for(register int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
        for(register int i=2;i<=n;++i) b[i]=max(b[i-1],sum[i]-sum[i-2]);
        for(register int i=0;i<=min(z,num/2);++i) ans=max(ans,sum[num-i*2]+b[num-i*2]*i);
        for(register int i=1;i<=min(z,num/2);++i) ans=max(ans,sum[num-2*(i-1)-1]+b[num-2*(i-1)-1]*(i-1)+sum[num-2*(i-1)-2]-sum[num-2*(i-1)-3]);
        cout<<ans<<endl;
    }
    // system("pause");
}
```

---

## 作者：lingfunny (赞：6)

前言：我相信没人像我一样打了个DP。
## 题意翻译
一个长度为 $n$ 的数组 $a_1,a_2,...,a_n$，一开始你在下标位 $1$ 的 $a_1$ 上，且总分为 $a_1$ 。接下来你可以做出两种操作：
1. 向右移动一步。若你当前在 $a_x$ $(x<n)$上，则移动到 $a_{x+1}$ 上，且你的总分会加上 $a_{x+1}$。
2. 向左移动一步。若你当前在 $a_x$ $(x>1)$上，则移动到 $a_{x-1}$ 上，且你的总分会加上 $a_{x-1}$ 上。

你可以走 $k$ 步，且最多只能往左走 $z$ 步，试问最后总分最大为多少。

**注1：不可以连续向左走$2$步及以上。**

**注2：你一定要完整走完 $k$ 步。**

#### 数据范围
$T$ 组数据且 $1\le T\le 1000$ ；

$2\le n\le10^5,1\le k\le n-1, 0\le z\le min(5,k))$；

$1\le a_i\le 10^4$；

$\sum_{i=1}^Tn_i\le3\times10^5$
## 题目分析
看数据范围和题意可以得到如下结论：
1. 所有的 $a_i$ 均为整数，所以每一步都是有价值的。走 $x$ 步所得总分的最优解一定小于走 $x+1$ 步所得总分的最优解。
2. 如果往左走了 $z$ 步，则最后无论怎么走下标也不会超过 $k+1-2z$ 。

很简单易懂的结论。

最后，看到 $n$ 和 $z$ 的大小，我直接写下了 DP。

设`dp[i][j]`为向左走了 $i$ 步，当前位置为 $j$，通过这个也可以很容易推出来现在已经走了 $j-1+2i$ 步。

于是我开心的写下了以下的状态转移方程：
```cpp
for(int i=1;i<=z;++i)
for(int j=1;j<=k+1-2*i;++j)
dp[i][j] = max(dp[i-1][j+1] + a[j], dp[i][j-1] + a[j]);
```
然后……`AC`了。

但我个人认为这里是有问题的，因为`dp[i-1][j+1]`的值也有可能时由`dp[i-2][j+2]`转化过来的，所以可能连续往左走了两步。然而我盲猜了一个结论：向左连续走 $k$ 步是没必要的。个人认为是正确的，但证明……

所以为了保险起见，我把状态改为：

`dp[i][j][1]`表示向左走了 $i$ 步，当前为 $k$ ，且最后一步是向左走的。

`dp[i][j][0]`同理，但表示的是最后一步是向右走的。

于是开开心心的又写下了以下的状态转移方程：
```cpp
for(int i=1;i<=z;++i)
for(int j=1;j<=k-i*2+1;++j){
	dp[i][j][1] = dp[i-1][j+1][0]+a[j];
	dp[i][j][0] = max(dp[i][j-1][0]+a[j], dp[i][j-1][1] + a[j]);
}
```
方程意思很明显了，`dp[i][j]`要么是从左边过来的，要么是从右边过来的。最后因为时间复杂度是 $\mathcal{O(nz)}$ 的，所以这题还是很愉快的AC了。

## 代码
```cpp
#include <cctype>
#include <cstdio>
#include <cstring>
 
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0; char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x; 
}
inline int max(int x, int y){return x>y?x:y;}
 
const int maxn = 1e5+5;
 
int T, n, k, z, a[maxn], ans;
int dp[6][maxn][2];
 
int main(){
	T = read();
	while(T--){
		ans = 0; n = read(); k = read(); z = read();
		for(int i=1;i<=n;++i){
			a[i] = read();
			for(int j=0;j<=5;++j)dp[j][i][1] = dp[j][i][0] = 0;
		}
		dp[0][1][0] = a[1];
		for(int i=1;i<=k+1;++i)dp[0][i][0] = dp[0][i-1][0] + a[i]; ans = dp[0][k+1][0];		//初始化
		for(int i=1;i<=z;++i)
		for(int j=1;j<=k-i*2+1/*结论2*/;++j){
			dp[i][j][1] = dp[i-1][j+1][0]+a[j];
			dp[i][j][0] = max(dp[i][j-1][0]+a[j], dp[i][j-1][1] + a[j]),
			ans = max(ans, max(dp[i][j][1], dp[i][j][0]) );				//随时更新。因为结论1，所以可以不用担心是否完整走完k步。
		}
		printf("%d\n", ans);
	}
	return 0;
} 
```

---

## 作者：_Flame_ (赞：4)

## 思路

很容易看出来，这是一个 **DP** 题。

我们假设 $dp_{i,j}$ 中的 $i$ 表示当前一共向左走了 $i$ 次， $j$ 表示在位置 $j$ 上的最大收益，用一个 $v$ 数组来储存每个格子对应的分值。很容易推出转移方程为 $dp_{i,j}=max(dp_{i,j-1},dp_{i-1,j+1})+v_{j}$ ,然后在对于每个状态的步数 $i\times2 +j$ 用一个 $ans$ 取一个 $max$ 值就好了。

然而光这样写还过不了，要注意一些细节。首先当 $j=n$ 时，是不能向右跳的，要加一个特判。然后还要注意是多组数据，要注意每一次操作时将数组与 $ans$ 清零。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,ans,T;
int v[1000010];
int dp[100010][6];
int main(){
	cin>>T;
	while(T--){
		memset(dp,0,sizeof(dp));
		cin>>n>>m>>k;
		ans=0;
		for(int i=1;i<=n;i++){
			cin>>v[i];
		}
		for(int i=0;i<=k;i++){
			for(int j=1;j<=n;j++){
				dp[j][i]=dp[j-1][i]+v[j];
				if(i!=0&&j!=n){
					dp[j][i]=max(dp[j][i],dp[j+1][i-1]+v[j]);
				}
				if(j-1+i*2==m){
					ans=max(ans,dp[j][i]);
				}
			}
		}
		cout<<ans<<endl;
	}
}

---

## 作者：Isshiki_Hugh (赞：3)

$O(2n+2z)$解法

~~我觉得我写的挺优美的(大概)~~

第一眼看过去大概都觉得是``dp``，事实上``dp``也是正解，但是仔细想想的话完全没必要，`O(N)`贪心完全可以实现。但是有注意点，注意到特判情况以后代码就很优美(确信

首先我们发现这样一件事情，数据范围里的$z$特别小，那我们直接枚举$z$不是爽歪歪(doge


- 情况一：最后一步往右边走

然后我们仔细观察题面，一次最多只能往左连续走一次，所以我们可以发现，但凡最后一步不是往左走，假设我们在$i$位的时候往左走，那么我们的`a[i]`和`a[i-1]`就会被重复一次，仔细思考发现，如果我们有这样往回走的机会，且不把向左安排在最后，只要对最大的`a[i]+a[i-1]`进行反复就可以达到最大的。

```cpp
rep(i,0,z) ans = std::max(ans,sum[k - i*2] + mx[k - i*2] * i);
```

- 情况二：最后一步往左边走

为什么要把最后一步讨论，这是因为如果最后一步往左走，就没有与他匹配的往右走，即没法形成`a[i]+a[i-1]`的组合，所以我们需要对此进行另外的处理

那么总体怎么做呢

```cpp
//注意，因为最后一步往左走所以至少i不能小于1
rep(i,1,z)  ans = std::max(ans,sum[k - 2*(i-1) - 1] + mx[k - 2*(i-1) - 1]*(i-1) + sum[k - 2*(i-1) - 2] - sum[k - 2*(i-1) - 3]);
```

- 说明：我刚开始k自增了一次，是为了让k直接表示在第几位

我们先用前缀和维护``sum[i]``，然后用`mx[i]`维护$1$~$i$位上最大的`a[i]+a[i-1]`，我们只需要枚举$z$，然后考虑除将这$z$位后走到的最远位置 $k-i*2$ 前最大的`mx[k-i*2]`重复$i$次，再加上`sum[k-i*2]`，就可以得到这种情况下的最大答案，当然，这是情况一。如果是情况二，需要先排除最后一步进行枚举，方法类似，最后再加上最后一步，也就是利用前缀和自减反推某一位的权值。

### 代码：
```cpp
#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define rep(i,a,b) for(register int i = (a);i <= (b);++i)
#define per(i,a,b) for(register int i = (a);i >= (b);--i)  
typedef long long ll;
typedef unsigned long long ull;
using std::string;using std::cin;using std::cout;

int _,n,k,z,a[200010],sum[200010],mx[200010],ans;

int main(){
    // std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("in.in", "r", stdin);
    cin >> _;
    while(_--){
        cin >> n >> k >> z;
        z = std::min(z,k/2);
        k = k + 1 , ans = 0;  // k自增，方便处理
        rep(i,1,n) cin >> a[i];
        rep(i,1,n) mx[i] = 0; // 初始化
        rep(i,1,n) sum[i] = sum[i-1] + a[i];  // 前缀和维护
        rep(i,2,n) mx[i] = std::max(mx[i-1],sum[i] - sum[i-2]); // 维护1到i位中最大的a[i]+a[i-1]的值
        //下面一行都在做情况一
        rep(i,0,z) ans = std::max(ans,sum[k - i*2] + mx[k - i*2] * i);
        //下面一行做情况二
        rep(i,1,z)  ans = std::max(ans,sum[k - 2*(i-1) - 1] + mx[k - 2*(i-1) - 1]*(i-1) + sum[k - 2*(i-1) - 2] - sum[k - 2*(i-1) - 3]);
        cout << ans << "\n";
    }
    return 0;
}
}
```

---

## 作者：momoguli (赞：3)

本蒟蒻在做本题是并没有看到z<=5这个条件，所以算法复杂度与z无关，可供大家参考。

首先我们可以经过推理发现这样一件事情，往回走只可能在一个位置发生并且每次只会往回走1步。

若我们不往回走，答案就一定是 $\sum_{i=1}^{k+1}a_i$ 。

若我们选择在$i$处往回走一步，走到$a_{i-1}$，相当于把原先的答案去掉尾部$a_k$和$a_{k+1}$再加上$a_i$和$a_{i-1}$。

若我们选择在同一位置一下子往回走两步，相当于把原先的答案去掉尾部$a_{k+1}$、$a_{k}$、$a_{k-1}$、$a_{k-2}$再加上$a_i+2a_{i-1}+a_{i-2}$。这时，我们可以发现若我们先往回走一步，再往前走一步，再往回走一步，消耗的k和z与一下子走两步等价，而加上的代价却变成了2($a_i$+$a_{i-1}$)。

若在$i-1$处向回走一步，加上的答案是2($a_{i-1}$+$a_{i-2}$)，而max(2($a_i$+$a_{i-1}$),2($a_{i-1}$+$a_{i-2}$))一定大于等于$a_i$+2$a_{i-1}$+$a_{i-2}$，所以连续往回走两步一定不优。

而选择往回走一步时，消耗的k和z都相同，所以只要找到最大的$a_i$和$a_{i-1}$就行了，但还需要注意一件事情，就是有些位置并不能将z使用完，所以对于每一个位置不能将z使用完的$i$都需要进行一遍额外的统计，能将z使用完的位置直接找最大的$a_i$和$a_{i-1}$即可。

时间复杂度O(n)。

下面是我比赛上写的代码，由于时间仓促，所以对每个位置都进行了统计，但易知正确性不会有问题。

```
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define F(i,j,k) for(int i=(j);i<=(k);i++)
#define DF(i,j,k) for(int i=(j);i>=(k);i--)
using namespace std;
template<typename T>inline void read(T &n){
    T w=1;n=0;char ch=getchar();
    while(!isdigit(ch)&&ch!=EOF){if(ch=='-')w=-1;ch=getchar();}
    while(isdigit(ch)&&ch!=EOF){n=(n<<1)+(n<<3)+(ch^48);ch=getchar();}
    n*=w;
}
template<typename T>inline void write(T x){
    ull y=0;
    T l=0;
    if(x<0){x=-x;putchar('-');}
    if(!x){putchar(48);return;}
    while(x){y=y*10+x%10;x/=10;l++;}
    while(l){putchar(y%10+48);y/=10;l--;}
}
template<typename T>inline void writeln(T x){
    write(x);
    puts("");
}
template<typename T>inline void checkmax(T &a,T b){a=a>b?a:b;}
template<typename T>inline void checkmin(T &a,T b){a=a<b?a:b;}
const int N=3e5+10;
int a[N],sum[N];
int main(){
 	int t;read(t);
 	while(t--){
 		int n,k,z,ans=0;read(n);read(k);read(z);
 		F(i,1,n)read(a[i]);
 		int s=0;
 		F(i,1,k+1){
			s+=a[i];
		 	sum[i]=sum[i-1]+a[i];
 		}
 		F(i,1,k){
 			if(k-i>=z*2)checkmax(ans,s+(a[i]+a[i+1])*z-(s-sum[k+1-z*2]));
 			else checkmax(ans,s+(a[i]+a[i+1])*((k-i)/2)+a[i]*((k-i)&1)-(s-sum[i+1]));
 		}
 		writeln(ans);
 	}
    return 0;
}


```


---

## 作者：huayucaiji (赞：2)

我们先来分析题目中一个重要的条件：

>Also, you can't perform two or more moves to the left in a row.

我们不能一次向左移动两格。所以这代表一次左后必定是右。那么我们很容易可以想到一个贪心的策略，我们无论如何，先走到 $k+1$。我们再来反悔，由于 $z$ 很小，我们可以枚举往后走几步，并且维护前面相邻两个数的和的最大值，选择在这里后退前进。于是我们可以得到下面的程序：


```cpp
//Don't act like a loser.
//You can only use the sode for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10;

int n,a[maxn],sum[maxn],maxx[maxn],k,z;

signed main() {
	int t=read();
	while(t--) {
		n=read();k=read();z=read();
		for(int i=1;i<=n;i++) {
			a[i]=read();
			sum[i]=sum[i-1]+a[i];
		}
		fill(maxx,maxx+n+1,0);
		
		for(int i=1;i<=n;i++) {
			maxx[i]=max(maxx[i-1],a[i]+a[i-1]);
		}
		int ans=sum[k+1];
		for(int i=1;i<=z;i++) {
			if(k+1-2*i>=2) {
				ans=max(ans,maxx[k+1-2*i]*i+sum[k+1-2*i]);
			}
		}
		
		printf("%d\n",ans);
	}
	return 0;
}

```

呵呵,WA。

我们再来仔细想想比如对于：

```plain
1
5 4 2
50 40 30 20 10
```

我们的最优方案是 $50->40->50->40->50$ 答案为 $230$。但是我们上面的程序给出的答案是 $50->40->50->40->30$。答案为 $210$。为什么呢？原因就是我们珂以退回去后就不行再往前走了，留在后面的格子里。所以我们还要加上这一段代码：

```cpp
if(k+2-2*i>=2) {
	ans=max(ans,sum[k+1-2*i]+i*(a[k-i*2+1]+a[k-i*2+2]));
}
```

**注意一些下标的问题哦~**

---

## 作者：f_x_f (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1389B)
# 题目分析
首先，这道题比较的简单，是一道较为标准的 dp ，~~虽说有大佬说可以用贪心做，但本蒟蒻不会~~ 。

首先， $0 \leq z\leq \min(5,k)$ 所以我们可以开一个二维 dp ，其中有一位用来记录现在所到的位置 $i$ 以及向右一共要走的步数 $j$ ，由于可以向左或者是向右走。于是就可以想出 dp 转移方程式。
## dp 转移方程式：
$dp_{i,j} = \begin{cases}
   dp_{i-1,j}+a_i  &\text{if } 1\leq i ,j\leq z\\
   \max(dp_{i+1,j-1}+a_i,dp_{i-1,j}+a_i) &\text{if  }j \ne 0,i\ne n
\end{cases}$

而当 $i+2 \ast j=k$ 的时候，就要对 $ans$ 的值进行更新，将其更新为 $dp_{i,j}$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,z;
int a[100001];
int dp[100001][10];
int ans;
void solve(){
	ans=0;
	cin>>n>>k>>z;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int j=0;j<=z;j++){
		for(int i=1;i<=n;i++){
			dp[i][j]=dp[i-1][j]+a[i];
			if(j&&i!=n){
				dp[i][j]=max(dp[i+1][j-1]+a[i],dp[i][j]);
			}
			if(i-1+j*2==k){
				ans=max(ans,dp[i][j]);
			}
		}
	}
	cout<<ans<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		solve();
	}
}

```

---

## 作者：V1mnkE (赞：1)

## 思路

考虑 dp 的做法，令 $dp_{i,j}$ 表示向左走了 $i$ 次时在位置 $j$ 的最大收益，易得状态转移方程：$dp_{i,j}=\max(dp_{i,j-1},dp_{i-1,j+1})+a_j$。

显然，走到某个状态的步数为 $j+2i$，当 $j+2i=k$ 时，记录一个 $ans$ 取最大值即可。

还要注意一些 corner case，如 $j=n$ 时不能从右边转移状态。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0' && c<='9') {x=x*10+c-48;c=getchar();}
	return x*f;
}
inline void write(int x){
    static char buf[20];
    static int len=-1;
    if(x<0)putchar('-'),x=-x;
    do buf[++len]=x%10,x/=10;while(x);
    while(len>=0)putchar(buf[len--]+'0');
    putchar('\n');
}
int t,n,k,z,ans,a[100005],dp[6][100005];
int main(){
	t=read();
	while(t--){
	    memset(dp,0,sizeof(dp));
	    ans=0;
	    n=read(),k=read(),z=read();
    	for(int i=1;i<=n;i++)a[i]=read();
    	for(int i=0;i<=z;i++){
    		for(int j=1;j<=n;j++){
    			dp[i][j]=dp[i][j-1]+a[j];
    			if(i&&j!=n)dp[i][j]=max(dp[i][j],dp[i-1][j+1]+a[j]);
    			if(j-1+i*2==k)ans=max(ans,dp[i][j]);
    		}
    	}
    	cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1389B)         
dfs 水题。       
题解大部分都写的是 dp，这里写记忆化搜索。        
我们 dfs 要传 $4$ 个值，这里称为 $last,left,pos,step$，它们的含义为上一步的操作（往左走称为 $0$，往右为 $1$）、向左走了几步、目前位置、步数。        
我们设当前情况下的答案为 $ans$，则有：      
1. $step=k$ 的时候，$ans=a_{pos}$。       
2. $left≠z$、$last≠0$ 和 $pos≠1$ 的时候，代表可以向左，向左计算一次答案。        
3. $pos≠n$ 的时候，向右一次。      
4. 除了第一个情况，其他情况的最后答案都为 $ans+a_{pos}$。       

这个 dfs 很容易写出来，接下来我们加记忆化。       
发现 $0\le z\le\min(5,k)$，所以我们可以使用 $z$ 来进行记忆化。       
我们可以设 $dp_{s,l}$ 为 $step=s$ 和 $left=l$ 的情况下的最大答案。         
直接加记忆化就可以了。      
[CODE](https://www.luogu.com.cn/paste/mlnv8jk7)

---

## 作者：FReQuenter (赞：0)

考虑 DP。

设 $f_{i,j,k}$ 为走了 $i$ 步，其中 $j$ 步向左走，$k$ 为 $0$ 时 上一步向左，否则向右。

状态转移：

显然，走了 $i$ 步，向左 $j$ 步，当前位置为 $now=i-j\times 2+1$。

$$f_{i,j,1}=\max\{f_{i-1,j,0},f_{i-1,j,1}\}+a_{now}$$

$$f_{i,j,0}=f_{i-1,j-1,0}+a_{now}$$

最终答案为 

$$f_{K,j,k}(1\leq j\leq Z,0\leq k\leq1)$$ 


Code:

```cpp
int a[100005],n,f[100005][6][2],k,z,ans;
signed main(){
	int t;
	cin>>t;
	while(t--){
		ans=0;
		cin>>n>>k>>z;
		for(int i=1;i<=n;i++) cin>>a[i];
		f[0][0][0]=a[1];//边界条件
		for(int i=1;i<=k;i++){
			for(int j=0;j<=z;j++){
				int now=i-j*2+1;
				if(now<1) break;
				f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1])+a[now];
				if(j>=1) f[i][j][1]=f[i-1][j-1][0]+a[now];
           //状态转移，注意数组不要越界
				ans=max(ans,f[i][j][0]);
				ans=max(ans,f[i][j][1]);
           //统计答案
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：dead_X (赞：0)

# 题意
给定一个长度为 $n$ 的数列 $a$，初始收益为 $a_1$。你一开始在数列的第一个元素上，让你在数列中走 $k$ 步，每一步你可以向左走一步或者向右走一步并获得等同于你走到的那个数的收益，你不能连续向左走两步，至多想左走 $z$ 步，求最大收益。
# 思路
最终的操作序列一定是由以下三部分组成的：

1. 有一些向右走一步的操作。

2. 在上面的序列任意一些连续操作之间插入**向左走一步再向右走一步**的操作。

3. 在上面的序列的最后增加一个**向左走一步**的操作或者什么也不加。

证明显然。


然后注意到第二条中插入操作获得的收益可以取到最大值，那么第一条确定后第二，第三条的插入收益很好求，那么枚举所有操作序列即可。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003];
int main()
{
	int T=read();
	while(T--)
	{
		int n=read(),k=read()+1,z=read(); 
		for(int i=1; i<=n; i++) a[i]=read();
		if(n==2) 
		{
			printf("%d\n",a[1]+a[2]);
			continue;
		}
		long long now=a[1],ans=0;
		int mx=0;
		for(int i=2; i<=min(n,k); i++)
		{
			mx=max(mx,a[i]+a[i-1]);
			now+=a[i];
			if(k-i<=2*z) if((k-i)&1) ans=max(ans,now+1LL*(k-i)/2*mx+a[i-1]);
			else ans=max(ans,now+1LL*mx*(k-i)/2);
		}
		printf("%lld\n",ans);
	} 
    return 0;
}
```

---

## 作者：kradcigam (赞：0)

简要题意：

>你前面一共有 $n$ 个格子，每个格子都有它的分值 $a_x$。当你到达第 $x$ 个格子就能获得第 $x$ 个格子的得分 $a_x$。
>
>初始时你站在第 $1$ 个格子，每一次移动你可以选择向左或向右，特别地，向左移动的次数不能超过 $z$。
>
>现在，请问你**正好**走了 $k$ 步后，最大得分是多少？

这道题比赛时，我先写了个正解，结果发现出了点问题，然后不知道怎么想的，去写了 $2$ 个显然是假的的贪心，然后又跑回去重新按照第 $1$ 次的思路写了一遍，然后就过了。于是我就丢人地做了 $50$ 分钟 $B$，导致没来得及写完 $D$。

这道题考虑这样一件事，我们没走一步，虽然位置并不一定单调不降，但是向左走的步数和总共走的步数一定是单调不降的，换句话说就是这 $2$ 个量无后效性，这就是本题的突破口。

我们知道向左走的步数和总共走的步数就可以知道当前在哪个格子，然后我们再来决定这步是从哪里转移过来的，上一步是向右走的还是向左走的。

思路大概就是这样，希望一些细节大家还是自己推一下，还是比较复杂的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
const int MAXN=1e5+10;
int a[MAXN],f[6][MAXN];
int work(){
	int n,k,z;
	read(n);read(k);read(z);
	for(int i=1;i<=n;i++)read(a[i]);
	f[0][0]=a[1];
	for(int i=0;i<=z;i++)
		for(int j=1;j<=k;j++){
			f[i][j]=f[i][j-1]+a[j-i*2+1];
			if(i!=0)f[i][j]=max(f[i][j],f[i-1][j-1]+a[j-i*2+1]);
		}
	int ans=0;
	for(int i=0;i<=z;i++)ans=max(ans,f[i][k]);
	cout<<ans<<endl;
	return 0;
}
int main(){
	int T;read(T);
	while(T--)work();
	return 0;
}
```

---

## 作者：Theophania (赞：0)

题意大概是说有个数列，初始在最左边，总共有 $k$ 次跳的机会，其中最多能向左跳 $z$ 次，不能连续向左跳，也不能跳出边界。很明显是个DP。

首先对于 $z=0$ 的情况，显然最终结果是 $dp_0=max_0=\sum_{i=1}^{k+1}a_i$，所以可以建一个前缀和数组。

$z=1$的时候除了不仅可以像上面那样走，还可以选择在路径中间后退一次或者在末端后退一次。在中间后退使得路径长度减少2，中间有连续的两个块会被经过两次；在末端后退会路径长度减少1，路径的倒数第二个块经过两次。于是可以再开一个数组记录到当前位置为止的最大相邻块值的和，即$m[i] = \max(m[i - 1], a[i - 1] + a[i])$

那么 $max_1=\max(pre[k-1] + m[k-1], pre[k]  + a[k-1])$

显然，$dp_1=\max(dp_0,max_1)$

$z\ge2$ 的时候以此类推，可以得到 $dp_i=\max(dp_{i-1},max_i)$ 以及
$max_i=\max(pre[k + 1 - 2 \times i] + i \times m[k + 1 - 2 \times i], pre[k + 2 - 2 \times i] + (i - 1) \times m[k + 2 - 2 \times i] + a[k + 1 - 2 \times i])$

于是这题就做完了，复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 9;
inline int read()
{
    int data = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        data = (data << 3) + (data << 1) + ch - '0';
        ch = getchar();
    }
    return f * data;
}
int arr[maxn], pre[maxn], m[maxn];
int main()
{
    int T;
    T = read();
    while (T--)
    {
        memset(m, 0, sizeof(m));
        int n = read(), k = read(), z = read();
        for (int i = 1; i <= n; ++i)
        {
            arr[i] = read();
            pre[i] = pre[i - 1] + arr[i];
            m[i] = max(m[i - 1], arr[i - 1] + arr[i]);
        }
        int ans = pre[k + 1], tmp;
        for (int i = 1; i <= z; ++i)
        {
            if (k < 2 * i - 1)
                break;
            tmp = max(pre[k + 1 - 2 * i] + i * m[k + 1 - 2 * i], pre[k + 2 - 2 * i] + (i - 1) * m[k + 2 - 2 * i] + arr[k + 1 - 2 * i]);
            ans = max(ans, tmp);
        }
        cout << ans << '\n';
    }
    return 0;
}

```


---

