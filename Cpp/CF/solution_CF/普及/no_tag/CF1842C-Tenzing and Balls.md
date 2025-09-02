# Tenzing and Balls

## 题目描述

Enjoy erasing Tenzing, identified as Accepted!



Tenzing has $ n $ balls arranged in a line. The color of the $ i $ -th ball from the left is $ a_i $ .

Tenzing can do the following operation any number of times:

- select $ i $ and $ j $ such that $ 1\leq i < j \leq |a| $ and $ a_i=a_j $ ,
- remove $ a_i,a_{i+1},\ldots,a_j $ from the array (and decrease the indices of all elements to the right of $ a_j $ by $ j-i+1 $ ).

Tenzing wants to know the maximum number of balls he can remove.

## 说明/提示

In the first example, Tenzing will choose $ i=2 $ and $ j=3 $ in the first operation so that $ a=[1,3,3] $ . Then Tenzing will choose $ i=2 $ and $ j=3 $ again in the second operation so that $ a=[1] $ . So Tenzing can remove $ 4 $ balls in total.

In the second example, Tenzing will choose $ i=1 $ and $ j=3 $ in the first and only operation so that $ a=[2] $ . So Tenzing can remove $ 3 $ balls in total.

## 样例 #1

### 输入

```
2
5
1 2 2 3 3
4
1 2 1 2```

### 输出

```
4
3```

# 题解

## 作者：Zhddd_ (赞：22)

题意简述：给定数组 $a$，可选择 $i,j$，$1\le i< j\le |a|$ 且 $a_i = a_j$，删去 $[i, j]$ 的所有数，后面的数（如果有）接上，问最多能删几个数。

考虑 Dp：为了方便，调换题目中 $i,j$ 的大小关系。

令 $f_i$ 表示前 $i$ 个数里面最多能删多少个数，则有：

$$f_i = \max(f_{j - 1} + i - j + 1, f_{i - 1})$$

其中 $1\le j< i\le |a|$ 且 $a_i = a_j$。

观察发现，其中主要的未知量就是 $f_{j - 1} - j + 1$，可以用 $mx_x$ 记录对于数字 $x$，满足 $a_j = x$ 的最大的 $f_{j - 1} - j + 1$，即可在 $O(1)$ 的时间内转移了，时间复杂度 $O(n)$。

```cpp
// 代码省略了不重要的内容。
vector<int> a(n + 1);
vector<int> f(n + 1);
vector<int> mx(n + 1, -INF);
for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
}
for (int i = 1; i <= n; i++) {
    f[i] = max(f[i - 1], i + mx[a[i]]);
    mx[a[i]] = max(mx[a[i]], f[i - 1] - i + 1);
}
printf("%d\n", f[n]);
```

---

## 作者：_GW_ (赞：8)

## 思路
一眼 dp。

用 $f_i$ 表示从 $1$ 删到 $i$，最多能删多少个数。

然后枚举所有 $1$ 到 $i-1$，找所有与 $a_i$ 相等的数。

若 $a_i=a_j$：

此时状态转移方程为 $f_i=\max(f_{i-1},f_{j-1}+i-j+1)$

但复杂度是 $O(n^2)$。

考虑将方程中的 $f_{j-1}-j$ 提出，将所有 $j$ 满足 $a_i=a_j$ 中 $f_{j-1}-j$ 最大的一个存到 $sum_{a_i}$ 中。

此时转移方程为 $f_i=\max(f_{i-1},sum_{a_i}+i+1)$，时间复杂度降为 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,a[N],b[N],num,val,sum[N],n,m,f[N];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		memset(f,0,sizeof f);
		memset(sum,-0x3f,sizeof sum);
		for(int i=1;i<=n;i++)
		{
			f[i]=max(f[i-1],sum[a[i]]+i);
			sum[a[i]]=max(sum[a[i]],f[i-1]-i+1);
		}
		cout<<f[n]<<endl;
	}
	return 0;
}
```


---

## 作者：shipeiqian (赞：5)

# CF1842C 题解

## 题意

在一个大小为 $n$ 的数组 $a$ 中进行任意次操作：选择 $i,j (1\leq i<j \leq n)$，使 $a_i=a_j$，把 $a_i~a_j$ 全部删掉，问最多能删除几个元素。

## 思路

这题求的是最大值，考虑可以用 dp，又因为可以进行任意次操作，每次可以删除一些数字，就可以定义一个二维的 $dp$ 数组，第一维表示在 $i$ 的位置，第二位表示删（1）或不删（0）$dp_{i,j}$ 表示最大删除的数量，那么答案就是 $dp_{n,1}$（删除第 $n$ 个）和 $dp_{n,0}$（不删第 $n$ 个）的最大值。

考虑转移方程，我们发现一个数字可删除所有与它相同所有数字，所以可以先用一个数组 $lst$ 记录每个最近的相同数字的位置，$lst_i$ 表示数字 $i$ 在 $lst_i$。如果不删除第 $i$ 个数字，那么他就可以从前一个没有删或前一个删了转移过来，转移方程为

$$dp_{i,j}=\max(dp_{i-1,0},dp_{i-1,1})$$

如果删除了这个数字，那么有两种情况：第一种，没有其他与当前数字相同的，那么就没法删，所以 $dp_{i,j}=0$；第二种，可以删，那么能删除的数量就是和当前相同的数的最大删除数量加上这次删除的数量 

$$dp_{i,j}=\max(dp_{lst_{a_i},0}+(i-lst_{a_i}+1),dp_{lst_{a_i},1}+(i-lst_{a_i}))$$

然后修改 $lst$ 的值，就是 $i$。

## 代码

```cpp
#include <bits/stdc++.h>
#define de "debug"
using namespace std;
typedef long long ll;
const int N=200005;
int n,a[N],dp[N][2],lst[N];
void solve(){
    cin >>n;
    for(int i=1;i<=n;i++){
        cin >>a[i];
        lst[i]=0;//没有第一个数字没有最近的相同的数字的位置
    }
    for(int i=1;i<=n;i++){
        dp[i][0]=max(dp[i-1][0],dp[i-1][1]);//不改
        if(lst[a[i]]!=0)dp[i][1]=max(dp[lst[a[i]]][0]+i-lst[a[i]]+1,dp[lst[a[i]]][1]+i-lst[a[i]]);//改得了
        else dp[i][1]=0;//改不了
        lst[a[i]]=i;//修改lst
    }
    cout <<max(dp[n][0],dp[n][1]) <<"\n";//答案
}
int main(){
    int T=1;
    cin >>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：柠檬布丁吖 (赞：4)

# 题意

若 $a_i=a_j$，且 $1≤i<j≤|a|$。则删除 $a_{i\dots j}$。

求出能删除数列中的数的最大数量。

# 思路

dp！

$f_i$ 表示将第 $i$ 个球作为目标，最多可以删去多少个球。
枚举 $j<i$ 的位置，且满足 $a[j]=a[i]$，则 $f_i=f_{j-1}+(i-j+1)$。

考虑只能从和目标值相同的地方转移。所以用 $b_x$ 表示所有 $a_j=x$ 的位置中 $f_{j-1}-j$ 的最大值。最后转移就是：$f_i=b_{a_i}$

时间复杂度：$O(n)$

# code

~~可可爱爱的代码~~

```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn=3e6+55,inf=1e9;

void solve(){
	int a[maxn],f[maxn],b[maxn],n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];b[i]=-inf;
	}
	for(int i=1;i<=n;i++){
		f[i]=max(f[i-1],b[a[i]]+i+1);
		b[a[i]]=max(b[a[i]],f[i-1]-i);
	}
	cout<<f[n]<<endl;
}
signed main(void){
	
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	
	return 0;
}
```

# 双倍经验

[P1868 饥饿的奶牛](https://www.luogu.com.cn/problem/P1868)

和这道丁真题的转移方程是一样的。我们在奶牛题目里面要在区间之间进行选择，这道丁真题也是在区间之间进行动态规划。

---

## 作者：Eddie08012025 (赞：3)

本题题意翻译描述已经足够简明，在此不再阐述。

首先，有些人看到这道题会考虑贪心，但显然贪心很容易被卡掉。

如一下这个例子：

```
2 3 2 1 4 3 4
```
贪心思路会选择 $i=2,j=6$，最后得到的答案是 $5$。

但显然最优是选择 $i=1,j=3$ 和 $i=5,j=7$，最终答案应该是 $6$。

然后考虑 dp。
## 原始思路

选择一对 $i,j (a_i=a_j,i<j)$ 并将 $i$ 与 $j$ 中间的所有数删掉。

定义一个 $dp$ 数组表示前 $i$ 个数中最多删除的数的个数。

再不优化的情况下，直接暴力 dp,外层循环枚举 $j$，内层循环枚举 $i$，在满足 $a_i=a_j,i<j$ 时更新 $dp_j$，易得一下转移方程：
$$dp_j=\max(dp_{j-1},dp_{i-1}+i-j+1)$$
主要代码如下：
```cpp
for(int i=1;i<=n;i++)
  for(int j=1;j<i;j++)
    if(z[i]==z[j])
      dp[i]=max(dp[i-1],dp[j-1]+i-j+1);
```
时间复杂度 $O(n^2)$，只能过 cf 上的第一个点。

## 优化思路
尝试优化 dp 压掉一层循环。

转移方程中 $dp_{j-1}-j+1$ 可以预处理，用一个数组 $x$ 来表示，$x_p$ 表示所有 $a_i=p$ 中最大的 $dp_{i-1}-i+1$。

转移方程可以优化成：
$$dp_j=\max(dp_{j-1},x_{a_i}+i)$$
$$x_{a_i}=\max(x_{a_i},dp_{i-1}-i+1)$$
主要代码如下：
```cpp
for(int i=1;i<=n;i++){
  dp[i]=max(dp[i-1],i+x[z[i]]);
  x[z[i]]=max(x[z[i]],dp[i-1]-i+1);
}
```
**感谢观看**

---

## 作者：D0000 (赞：2)

# CF1842C Tenzing and Balls
本人第二篇题解（第一篇还没过）
## 题目大意
就是每次输入一个序列，如果存在两个位置不同但数字一样的元素，就把它们及他们中间的元素全部删掉，问最多能删多少。
## 解法
### 法1：贪心+模拟（WA）
这个方法实现起来相对容易，我一开始也是用的这种方法。大概就是每次找到符合条件且距离最远的两个数，接着统统删掉，直到最后不存在有数字相同的两个数，附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){//快读 
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}
int main()
{
	//freopen("B.in","r",stdin);
	//freopen("B.out","w",stdout); 做测试时用的 
	int t=read();
	while(t--)
	{
		int n=read(),a[200000],mina=2147483647;
		for(int i=0;i<n;i++)a[i]=read();
		if(n<3)cout<<0<<endl;
		sort(a,a+n);
		for(int i=0;i<=n-3;i++)for(int j=i+1;j<=n-2;j++)mina=min(mina,max(max((a[i]-a[0]+1)/2,(a[j]-a[i+1]+1)/2),(a[n-1]-a[j+1]+1)/2));
		if(n>=3)cout<<mina<<endl;
	}
	return 0;//好习惯 
}
```
### 法2：深搜（不靠谱）
我的同学不知道怎么写的，空间复杂度、时间复杂度均为 $O({n}^{3})$，绝对要超。
### 法3：动规（正解）
先分析一下我原来的做法，一眼看还蛮有道理的吗。但是只要仔细一想就会发现问题

举个例子：

当原来的为：$6,2,6,3,2,3$ 时

贪心方法为：$6,3$ 删掉了 $4$ 个

正解为空，删掉了 $6$ 个

其实只要想到动态规划，稍加分析就能得出一下状态转移方程：

$$dp[i]=i+(dp[i-1]-(j-1))$$

再选取最大。就差不多了

C++ 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 #define int long long
typedef pair<int,int> PII;
typedef unsigned long long ULL;
const int N = 4e5 + 10;
int mod = 998244353;
void solve()
{
	int n;
	cin >> n;
	vector<int> dp(n + 10),mx(n + 10,-1e9),a(n + 10);
	for(int i = 1;i <= n;i++)cin >> a[i];
	for(int i = 1;i <= n;i++)
	{
		dp[i] = dp[i - 1];
		dp[i] = max(dp[i],mx[a[i]] + i);
		mx[a[i]] = max(mx[a[i]],dp[i - 1] - (i - 1));
	}
	cout << dp[n] <<"\n";
}
 
int main()
{
	ios::sync_with_stdio(0 );
	cin.tie(0);cout.tie(0);
	int t = 1;
	cin >> t;
	while(t--)solve(); 
}
```
居然有 $98$ 个测试点！

特别感谢[wuyufeng9960](https://www.luogu.com.cn/user/926043)、[yishanjie](https://www.luogu.com.cn/user/926043)、[wwlw](https://www.luogu.com.cn/user/83337)

---

## 作者：Eason_cyx (赞：1)

记 $f_i$ 表示前 $i$ 个数中能删最多能删多少个数，则易得状态转移方程：

$$f_i=\max(f_{i-1},f_{j-1}+i-j+1)$$

其中 $1 \le j < i$，且 $a_i=a_j$。

不难发现这个程序是 $\Theta(n^2)$ 的，无法通过。

那么我们发现其实对于所有相同的 $a_i$ 来说，$f_{j-1}-j+1$ 这个部分是可以提出来的。所以我们记 $l_x$ 表示在所有 $a_i=x$ 中，$f_{i-1}-i+1$ 最大的一个。于是我们的状态转移方程就变成了：

$$f_i=\max(f_{i-1},i+l_{a_i})$$

这样是 $\Theta(n)$ 的，可以通过。每次求 $f$ 结束后更新 $l_{a_i}$ 即可。

```cpp
for(int i = 1;i <= n;i++) cin >> a[i];
		for(int i = 1;i <= n;i++) {
			f[i] = max(f[i-1],i+last[a[i]]);
			last[a[i]] = max(last[a[i]],f[i-1]-i+1);
		}
		cout << f[n] << endl;
```

注意 $l_i$ 的值很可能在某个阶段变成 $0$，所以初值不能设为 $0$，最好设为无穷小，如 `0xc0c0c0c0`。

---

## 作者：Austin0116 (赞：0)

# 分析

决策性问题，考虑 DP 或贪心。贪心思路，选取最大区间去消除，很容易被 hack，在此不多叙述。所以考虑 DP。

很容易想到 $f[i]$ 表示前 $i$ 个数中最大消除的数的个数。

转移方程为 
```cpp
for(int i=1;i<=n;i++)
  for(int j=1;j<i;j++)
    if(a[j]==a[i])
      f[i]=max(f[i],f[j-1]+i-j+1);
```

时间复杂度为 $O(n^2)$。

考虑优化，可以定义 $g[a[i]]$ 为颜色为 $a[i]$ 的所有的数前最小未消除数的消除数（可能会有点绕，结合代码看）。然后就可以用 $g[a[i]]$ 来优化转移。时间复杂度为 $O(n)$。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[200005],f[200005],g[200005],id[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){//初始化
			id[i]=2e9;
			g[i]=f[i]=0;
		} 
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++){
			f[i]=max(f[i-1],g[a[i]]+i-id[a[i]]+1);//更新DP数组
			if(i-f[i-1]<id[a[i]]-g[a[i]]){//更新g数组
				g[a[i]]=f[i-1];
				id[a[i]]=i;
			} 
		}
		printf("%d\n",f[n]);//输出答案
	}
	return 0;
}
```

---

## 作者：_NightFire666_ (赞：0)

#### 推荐用[博客](https://www.luogu.com.cn/blog/20111219zhr/solution-cf1842c)食用！
## _Brief description of the title_

若 $a_i=a_j$ 且 $1\le i < j\le |a|$。则删除 $a_{i}$ 到 $a_j$ 所有数。求出能删除数列中的数的最大数量。

## _Solution_

考虑动态规划：

### 状态：

$f_i$ 表示前 $i$ 个数里面最多能删除多少个数。

$maxn_{a_i}$ 表示对于数 $a_i$，满足 $a_j=x$ 的最大的 $f_{i-1}-j+1$ 的值。

### 状态转移方程
$$
f_i=\max(f_{i-1},\max_{1\le j<i \wedge a_i=a_j}f_{j-1}+i-j+1)
$$
可化简为：
$$
f_i=\max(f_{i-1},maxn_{a_i}+i+1)
$$

### 边界

$f_0=0$

### 答案

$f_n$

## _Code_

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Size=3e6+55;
const int infi=-100e7;//相当于1e9
signed main(){
	int t;
	cin>>t;
	while(t--){
		int a[Size],f[Size],maxn[Size],n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i],maxn[i]=infi;
		for(int i=1;i<=n;i++){
			f[i]=max(f[i-1],maxn[a[i]]+i+1);
			maxn[a[i]]=max(maxn[a[i]],f[i-1]-i);
		}
		cout<<f[n]<<endl;
	}
	return 0;
}
```

---

## 作者：highkj (赞：0)

# 思路
这道题一眼 Dp，我们定义 $f_i$ 为从 $1\sim i$ 能删去的最长长度，那么我们就能得到一个显然的状态转移方程 $f_i=\max(f_{i-1},f_{lst-1}+(i-lst+1))$ 这里的 $lst$ 表示所有 $a_i$ 出现过的位置除了 $i$，但是这样的时间复杂度度是过不去的。

所以我们来想如何优化，首先最外面的一层 $i$ 是优化不了的，所以我们就来思考如何优化掉最里面的一层最大值，这里我们明显可以将方程给变为 $f_i=\max(f_{lst-1}-lst+1)+i$ 那么这不就可以预处理了吗？

我们定义 $Max_i$ 为所有出现过 $i$ 的位置上 $f_{i-1}-i+1$ 的 `最大值` 那么我们就可以将方程转换为 $f_{i}=\max(f_{i-1},Max_{a_i}+i)$，最后的答案就是 $f_n$。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define w(x) while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int t;
int n,a[200100];
int Max[200100];
int f[200100];
fire main() {
	cin>>t;
	w(t) {
		in(n);
		rep(i,1,n) in(a[i]);
		memset(f,0,sizeof f);
		memset(Max,-0x3f,sizeof Max);
		rep(i,1,n) {
			f[i]=f[i-1];
			f[i]=max(f[i],Max[a[i]]+i);
			Max[a[i]]=max(Max[a[i]],f[i-1]-i+1);
		}
		cout<<f[n]<<endl;
	}
	return false;
}

```

---

## 作者：zhongpeilin (赞：0)

## C:Tenzing and Balls
题目大意：给你一个长度为 $n$ 的序列 $a_{i}$ ,每一次操作你可以选择两个整数 $1 \leq i < j \leq n$，且 $a_{i} = a_{j}$，那么你可以选择将 $i$ 到 $j$ 这一段删掉，次数不限，请问最多能删元素个数是多少？

------

### 解题思路
首先不难想到一个错误的贪心：选最大段的删掉，但是这样是不对的，比如：  
$a$ 数组：`4 7 4 1 1 2 7 2`  
贪心答案：`2`，正确答案：`0`   

那我们以右端点排序，然后能选就选，行吗？也不行。  
$a$ 数组：`4 7 4 1 2 3 7`  
贪心答案：`4`，正确答案：`1`

所以贪心好像做不了了，那么不难想到：$dp$。  
为了方便，设 $dp_{i}$ 表示前i个位置最后最少剩多少数。
$$
dp_{i} = \min_{a_{i}=a_{j}}\{dp_{j - 1}\}
$$
$$
dp_{i} = \min\{dp_{i}, dp_{i - 1} + 1\}
$$
但是暴力枚举 $j$ 是 $O(n^2)$ 的，怎么优化呢？  
不难发现：$a_{i} \leq n$, 那么我们可以用一个桶来优化 $dp$。  
设 $to_{i}$ 表示目前为止 $a_{i}$ 为 $i$ 的最小 $dp$。 

那么

$$
dp_{i} = \min\{to_{a_{i}}, dp_{i-1} + 1\} 
$$

$$
to_{a_{i}} = \min\{to_{a_{i}}, dp_{i-1}\}
$$

时间复杂度 $O(n)$。

[AC 代码](https://codeforces.com/contest/1842/submission/219110045)

---

## 作者：foryou_ (赞：0)

一眼 dp。

状态：令 $dp_i$ 表示前 $i$ 个数进行若干次操作能删除的最多的数的个数。

转移方程：

$$
dp_i = \max(dp_{i-1},dp_{j-1}+i-j+1)
$$

其中 $j$ 满足 $1 \le j < i$ 且 $a_i = a_j$。

不过这样朴素地转移，时间复杂度是 $O(n^2)$ 的，无法接受。

我们观察到，对于上述转移方程，未知量是 $dp_{j-1}-j+1$。

于是我们考虑令 $f_i$ 表示数 $i$（注意不是下标 $i$）对应的满足 $a_j=i$ 的最大的 $dp_{j-1}-j+1$。

这个 $f_i$ 可以在转移的同时维护，转移方程：

$$
f_{a_i}=\max(f_{a_i},f_{i-1}-i+1)
$$

注意这个转移方程中的 $i$ 就不是数值而是下标了。

最后输出 $dp_n$ 即可。时间复杂度降至 $O(n)$。

代码很好写，就不展示了。

---

