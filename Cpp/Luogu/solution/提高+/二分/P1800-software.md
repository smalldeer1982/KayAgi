# software

## 题目描述

一个软件开发公司同时要开发两个软件，并且要同时交付给用户，现在公司为了尽快完成这一任务，将每个软件划分成 $m$ 个模块，由公司里的技术人员分工完成，每个技术人员完成同一软件的不同模块的所用的天数是相同的，并且是已知的，但完成不同软件的一个模块的时间是不同的，每个技术人员在同一时刻只能做一个模块，一个模块只能由一个人独立完成而不能由多人协同完成。一个技术人员在整个开发期内完成一个模块以后可以接着做任一软件的任一模块。写一个程序，求出公司最早能在什么时候交付软件。

## 说明/提示

### 样例解释

最快的方案是第一个技术人员完成第二个软件的 $18$ 个模块，用时 $18$ 天，第三个技术人员完成第一个软件的 $18$ 个模块，用时 $18$ 天，其余的模块由第二个技术人员完成，用时 $12$ 天，做完所有模块需要 $18$ 天。如果第一个技术人员完成第二个软件的 $17$ 个模块，第三个技术人员完成第一个软件的 $17$ 个模块，其余的模块由第二个技术人员完成，需要用时 $18$ 天，做完所有模块仍然需要 $18$ 天，所以少于 $18$ 天不可能做完所有模块。

## 样例 #1

### 输入

```
3 20
1 1
2 4
1 6
```

### 输出

```
18```

# 题解

## 作者：ghy21 (赞：17)

萌新第一次写题解，望包含

[题面传送门](https://www.luogu.org/problemnew/show/P1800)

这道题很有难度

先观察题目:不难想到是一个背包题，背包容量:m,物品重量:1,物品数量:n

物品价值是什么?

是前i个人完成软件1后,最多能完成几个软件2

这便将问题转化为完全背包了

但是,如果纯打完全背包,只能得60分

怎么优化呢?

经过观察发现:答案具有单调性

于是可以用二分答案优化了

你懂了吗?可以看代码
```cpp
/*
  This code is made by ghy.
  Algorithm : Two Points Answer && Dynamic Programming (DP).
  I don't know what this code is.
*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n,m,a[105],b[105],dp[105][105],l=1,r=20000;//r(max)=m(max)*day(max)=20000
bool check(int ntime){
    int time_else;
    memset(dp,0,sizeof(dp));	//记得初始化
    dp[0][0]=1;
    for(int i=1;i<=n;i++)	//枚举第i个人 
    	for(int j=0;j<=m;j++)
   			for(int k=j;k>=0;k--){
        		time_else=ntime-a[i]*(j-k);    //表示前i个人模块1做了j-k个情况下,他们能用来做模块2的时间
				if(time_else<0) 	//用ntime的时间做不了j-k个模块1		
					break;
        		if(dp[i-1][k]>0) 	//前i-1个人可以做k个模块1的同时做1个及以上的模块2
					dp[i][j]=max(dp[i][j],dp[i-1][k]+time_else/b[i]);    //状态转移方程(类完全背包) 
    		}
    return dp[n][m]>m;    //dp[n][m]:前n个人做m个模块1的同时,在time_else内还能做多少个模块2 
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i],&b[i]);
    int mid;
    while(l<=r){	//二分答案,其中l,r都能取到	 
        mid=(r+l)>>1;
        if(check(mid))
			r=mid-1;
		else
			l=mid+1;
    }
    printf("%d\n",l);
    return 0;
}
```

---

## 作者：RoRoyyy (赞：9)

窝太菜了， ~~没想出来用$dp$来计算$check$..~~

这题二分答案很显然， 因为时间如果给少了可能不够， 时间又要求给定限制内的最少， 所以二分答案， 满足限制就缩小， 不满足就扩大。

难点在于$check$， 首先观察数据范围， 咦？才$100$， 显然是一个$n^{3}$的$check$，或者$n^{2}log(n)$， 所以思考这么奇怪复杂度的算法， 只能是$dp$比较灵活。
其次可以推导式子:


**我们发现：**

$max(use(i)) <= mid$，我们肯定会先列出这个， 然后发现无从下手， 深入思考后发现， 我们$mid$出来的答案可以作为条件， 这样的话我们贪心点来考虑， 让每一个人都工作$mid$天如果都不能全干完， 那么肯定比$mid$少更不行， 所以我们就得到了**第一点思路。**， 让每个人工作$mid$天求最大价值。

然后我~~就看题解了~~们继续思考， 发现很类似背包， 但是由于是两个包， 我们为了避免后效性， 这样设计转移：

$dp[i][j]$为前$i$个人， 完成$j$个1模块之后还能完成最大的2模块。

这样最终答案就是$dp[n][m]$了，我们只需要判断它是否大于$m$就行了。

转移很显然， 在代码中给出了。

```cpp
#include <cstdio>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <cstring>
template<typename T> 
inline void read(T &x) {
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) {x = x * 10 + ch - '0'; ch = getchar();}
    x *= f;
}
/*
1e6 * log(1e4) = 1.3e7能过
二分答案：
公司于d天后交付软件
每个人干d天，检查能不能干出来
dp[i][j] 前i个人做了j个模块1的情况下还能做几个模块2
dp[i][j] = max(dp[i][j], dp[i - 1][k] + (d - (cost1[i] * (j - k)) / cost2[i]))
*/
const int N = 105;
using namespace std;
int n, m;
int cost1[N], cost2[N];
int dp[N][N];
bool check(int mid) {
    memset(dp, 0xcf, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            for(int k = 0; k <= j; k++) {//前面做了k个模块1， 现在做了j个模块1， 这个人做了（j-k）个模块1， 剩余时间可以来做模块2
                int need1 = cost1[i] * (j - k);
                int rest = mid - need1;
                if(rest < 0) continue;
                dp[i][j] = max(dp[i][j], dp[i - 1][k] + rest / cost2[i]);
            }
        }
    }
    return dp[n][m] >= m;
}
int main() {
    read(n), read(m);
    for(int i = 1; i <= n; i++) 
        read(cost1[i]), read(cost2[i]);
    int l = 0, r = 1e4;
    while(l < r) {
        int mid = l + (r - l) / 2;
        if(!check(mid)) l = mid + 1;
        else r = mid; 
    }
    printf("%d\n", l);
    return 0;
}
```


---

## 作者：zhenjianuo2025 (赞：5)

$\texttt{Upd. 2022.07.29}$ 

修正了 $\LaTeX$ 的小错误。

------------

### Preface

竟然抢到了主题库的题解，有点小鸡冻……


### Solve1

我们可以从小到大枚举答案 $t$，然后考虑类似**完全背包**的做法来验证答案。


设 $f_{i,j}$ 表示**前 $i$ 个人做了 $j$ 个软件 $1$ 的模块的时候，他们最多还能做几个软件 $2$ 的模块**。 

直接放状态转移方程：


$f_{i,j}=\max \{$前 $i-1$ 个人做了 $k$ 个软件 $1$ 的模块的时候，他们最多还能做软件 $2$ 的模块的个数$+$第 $i$ 个人在剩余的时间内做完 $j-k$ 个软件 $1$ 的模块最多还能做软件 $2$ 的模块的个数$\}$

也就是

$f_{i,j}=\max \{f_{i-1,k} + \left \lfloor \dfrac{t-d_{1_i}\times (j-k)}{d_{2_i}}\right \rfloor \}$ $(0\le k\le j)$

其中 $d_{1_i},d_{2_i}$ 分别表示第 $i$ 技术人员完成第 $1$ 个或第 $2$ 个软件中的一个模块所需的天数。

~~柿子太长了，不要怕，来一起分析一下：~~

$k$ 是前 $i-1$ 个人做的软件 $1$ 的模块的个数，第 $i$ 个人做了 $j-k$ 个软件 $1$ 的模块，还剩 $t-d_{1_i}\times (j-k)$ 的时间用来做软件 $2$ 的模块，可以做 $\left \lfloor \dfrac{t-d_{1_i}\times (j-k)}{d_{2_i}}\right \rfloor$ 个软件 $2$ 的模块。



### Code1
 
```cpp
#include <iostream>
#include <cstring>
using namespace std;
#define MAXN 110
int n, m, d1[MAXN], d2[MAXN];
int f[MAXN][MAXN];
// f[i][j] 表示 前 i 个人做了 j 个软件 1 的模块的时候，他们最多还能做几个软件 2 的模块 
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> d1[i] >> d2[i];
	for (int t = 1; ; t++) {   // 枚举答案
		memset(f, 0xcf, sizeof f);   // 初始化极小值
		f[0][0] = 0;
		for (int i = 1; i <= n; i++)   // 枚举前 i 个人 
			for (int j = 0; j <= m; j++)   // 枚举前 i 个人做 j 个软件 1 的模块
				for (int k = 0; k <= j; k++)   // 枚举前 i - 1 个人做 k 个软件 1 的模块 
					if (t - d1[i] * (j - k) >= 0)
						f[i][j] = max(f[i][j], f[i - 1][k] + (t - d1[i] * (j - k)) / d2[i]);   // 状态转移
		if (f[n][m] >= m) {   // n 个人可以在 t 时间内做完软件 1 的同时做完软件 2
			cout << t << endl;
			break;
		}
	}
	return 0;
}
```


### Solve2

考虑正解二分答案。

~~不过这二分貌似没有直接枚举快，枚举 $94$ $\texttt{ms}$ 完虐二分 $202$ $\texttt{ms}$，还进了最优解第二页……~~

~~数据太 \** 水沝淼㵘了！~~


很容易想到，答案具有**单调性**，因为如果当前时限内都不能满足，那么比它还小的时限内就更不可能满足了。

```cpp
while (l <= r) {
	int mid = (l + r) >> 1;
	if (check(mid)) 
		r = mid - 1;
	else 
		l = mid + 1;
}
cout << l << endl;
```


### Code2

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define MAXN 1010
int n, m, d1[MAXN], d2[MAXN];
int f[MAXN][MAXN];
int l = 1, r = 1e4;
// f[i][j] 表示 前 i 个人做了 j 个软件 1 的模块的时候，他们最多还能做几个软件 2 的模块 
bool check(int t) {
	memset(f, 0xcf, sizeof f);   // 初始化极小值
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)   // 枚举前 i 个人 
		for (int j = 0; j <= m; j++)   // 枚举前 i 个人做 j 个软件 1 的模块
			for (int k = 0; k <= j; k++)   // 枚举前 i - 1 个人做 k 个软件 1 的模块 
				if (t - d1[i] * (j - k) >= 0)
					f[i][j] = max(f[i][j], f[i - 1][k] + (t - d1[i] * (j - k)) / d2[i]);   // 状态转移
	return f[n][m] >= m;   // n 个人可以在 t 时间内做完软件 1 的同时做完软件 2
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> d1[i] >> d2[i];
	while (l <= r) {   // 二分答案 
		int mid = (l + r) >> 1;
		if (check(mid)) 
			r = mid - 1;
		else 
			l = mid + 1;
	}
	cout << l << endl;
	return 0;
}
```


蒟蒻的第一篇垃圾题解。

---

## 作者：MD_17L (赞：4)

1. 题意：某公司要开发两个软件，每个有m个模块，有n个技术人员，每个人开发不同软件的时间不同。
2. 思路：属于求最大值最小问题，求两个任务完成的最大天数的最小值。而且答案是单调的，于是想到了二分答案，就得到了天数，所以需要判断能否行得通，这时就想到了DP（类完全背包）。用软件1做m个时 当前天数是否满足做m个软件2为判断依据。
3. 方程含义：f[i][j]表示前i个人做j个软件1的模块时最多能做几个软件二的模块。 
### 4. 方程 :f[i][j]=max{f[i][j],f[i-1][k]+res/b[i]}//详见代码注释

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int N=110;
int n,m,a[N],b[N],l,r,mid,ans;
int f[N][N];

 bool dp(int num)
{
	memset(f,0,sizeof(f));
	f[0][0]=1;//初始化
	int i,j,k,res;
	for (i=1; i<=n; i++)
		for (j=0; j<=m; j++)
			for (k=j; k>=0; k--)//i-1个人做k个软件1模块，第i个人做j-k个
			{
				res=num-a[i]*(j-k);
				if (res<0) break;//判断第i个人能否做
				if (f[i-1][k]>0) f[i][j]=max(f[i][j],f[i-1][k]+res/b[i]);
			}
	
	if (f[n][m]>m) return true;
	return false;
}
 int main()
{
	int tmp=0;
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) 
	{
		scanf("%d%d",&a[i],&b[i]);
		if (a[i]+b[i]>tmp) tmp=a[i]+b[i];
	}
	r=tmp*m; l=1;
	while (l<=r)
	{
		mid=(l+r)/2;
		if (dp(mid)) {ans=mid; r=mid-1;}
		else l=mid+1;
	}//熟悉的二分
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：哔哩哔哩 (赞：4)

### 【分析】
因为要完成2个软件，01背包是做不到的，因此我们想到了完全背包。

我同学的一个三维完全背包的打法。暴力出奇迹:D（逃

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int a[110][5],f[110][110][110]/*f[110][110][5],t[110][110][5]*/,ans=0,n,m;
void work(int p,int x,int y)
{
	int o=0x7fffffff;
	for(int i=0;i<=x;i++)
	for(int j=0;j<=y;j++){
		if(f[p-1][x-i][y-j]==-1)work(p-1,x-i,y-j);
		o=min(o,max(f[p-1][x-i][y-j],a[p][1]*i+a[p][2]*j));
	}
	f[p][x][y]=o;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=2;j++)cin>>a[i][j];
	memset(f,-1,sizeof(f));
	for(int i=0;i<=m;i++)for(int j=0;j<=m;j++)f[1][i][j]=a[1][1]*i+a[1][2]*j;
	work(n,m,m);
	cout<<f[n][m][m]<<endl;
	return 0;
}
```
很可惜，只有60分。  
因为答案是单调的，很可以二分优化qwq  
二分答案还是好理解的qwq。
```cpp
#include<cstdio>
#include<cstring>
int n,m,a[105],b[105],f[105][105],maxa,maxb;
int max(int x,int y){
	return x>y? x:y;
}
bool check(int time){
	int i,j,k,now;
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for (i=1;i<=n;i++)
	for (j=0;j<=m;j++)
	for (k=j;k>=0;k--){
		now=time-a[i]*(j-k);//表示第i个人第一个模块做了j-k个情况下，第i个人能用来做第二个模块的时间 
		if (now<0) break;
		if (f[i-1][k]>0) f[i][j]=max(f[i][j],f[i-1][k]+now/b[i]);
	}
	return f[n][m]-1>=m;//f[n][m]表示前n个人第一个模块做了m个，第二模块一共能做多少模块 
}
int main(){
	int i,L,R,mid;
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		if (a[i]>maxa) maxa=a[i];
		if (b[i]>maxb) maxb=b[i];
	}
	L=1;R=maxa*m+maxb*m;
	while (L<=R){
		mid=(R-L>>1)+L;
		check(mid)?R=mid-1:L=mid+1;
	}
	printf("%d\n",L);
	return 0;
}
```

---

## 作者：A天天t (赞：3)


动态规划可以用二维数组，也可以用一维数组（只用倒序做即可）

此题类似一个背包问题，背包容量即为任务一的大小（即为m）

填的物品价值即为第i个人昨完任务一以后还能够用来用来做几个任务二。


至于天数，直接猜（因为每个模块的最多天数为100，最多200个模块，所以最多200\*100 天就可以做完），答案肯定在1  到20000之间，二分查找当然是最快的方法。


下面是我的代码












        
```cpp
type 
    int=longint;
const 
mn=100;
md=100;
ok=true;
var 
f,d1,d2:array[0..mn]of int;
i,j,k,x,n,m:int;
function max(x,y:int):int;
begin 
if x>y then exit(x) ;exit(y);
end;
function min(x,y:int):int;
begin 
if x>y then exit(y) else exit(x);
end;
procedure init;
begin 
readln(n,m);
for i:=1 to n do 
    readln(d1[i],d2[i]);
end;
function tian(x:int):boolean;
begin 
tian:=false;
fillchar(f,sizeof(f),$9f);
f[0]:=0;
for i:=1 to n do  
    for j:=m downto 0 do     //完成了j个模块的情况下
        for k:=0 to  min(x div d1[i],j) do //第i个人做k(0,j,)个模块一
           f[j]:=max(f[j],f[j-k]+(x-k*d1[i])div d2[i]);
if f[m]>=m then exit(true); 
end;
function   erfen_find(l,r:int):int;
var mid:int;
begin 
if l+1=r then exit(r);
mid:=(l+r) div 2;
if tian(mid)=ok then   exit(erfen_find(l,mid))
else exit(erfen_find(mid,r));
end;
begin 
init;
 writeln(erfen_find(0,mn*md*2));
end.

```

---

## 作者：nevergiveuphhhh (赞：1)

# 题意
  简单来说就是一个工作安排的最优情况。
  
  首先第一眼看到就是到是 DP 。
  
  但是考场上直接就只敲了一个四维的暴力 DP ，40 分。
    
    
    
# 正解

## 题型
 二分答案 + DP，类似[P1281](https://www.luogu.com.cn/problem/P1281)一题。

## 分析
求最早的完成时间，显然，如果时间更多也能完成任务，答案满足单调性，即求**最大的最小值**，想到用二分答案。

二分答案软件需要完成的时间，设答案为 $mid$ 。

直接枚举并判断答案肯定要超时的，想到用 DP 。

## 解答

状态： 表示完成第一个软件的 $f[j]$ 个模块，此时还可以完成第二个软件的最多的总模块数。

~~也可以设立 $f[i][j]$ 表示前 $i$ 个人完成第一个软件 $j$ 个模块，还可以完成的第二个软件的最多的总模块数，转移方程留给读者思考。~~

设第 $i$ 个人要完成 $k$ 个模块，那么前 $i-1$ 个人完成了 $j-k$ 个模块，完成第二个软件的模块数就为 $(mid-k \times t1[i]) \div t2[i]$。
那么方程还是比较好想的：

$$f[j]=max(f[j],f[j-k] + (mid-k \times t1[i]) \div t2[i]))$$ 

判断是否合法，就比较 $f[m]$与 $m$ 的大小，如果 $f[m] \geq m$ 则说明答案可行。

# 参考代码

```
#include <bits/stdc++.h>
using namespace std;
int t1[105], t2[105], f[105];
int n, m;
bool check(int mid)
{
    for (int i = 1; i < 105; i++) {
        f[i] = -0x3f3f3f3f;
    }
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 0; k <= min(mid / t1[i], j); k++) {
                f[j] = max(f[j], f[j - k] + (mid - t1[i] * k) / t2[i]);
            }
        }
    }
    return f[m] >= m;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> t1[i] >> t2[i];
    }
    int l = 1, r = 1000000;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << l << endl;
    return 0;
}
```

---

## 作者：Hongse_Fox (赞：1)

[题目链接](https://www.luogu.org/problem/P1800)

拿到题目第一件事：~~秒切~~ 找关键字眼

这么长一道题目，只有两个字是最耀眼的：最早

看到最值，脑海中浮现的是动态规划 和 二分答案 以及 ~~费用流~~......
# 解法 二分答案+动态规划
## 思路
我们想到，对于一个程序猿，能决定它搞多少个程序的只有天数，那么我们就可以二分它的天数

如果我们确定了天数，那么这个问题就转换成了在某一段时间内能否搞定这么多个A B软件

对于这样一个问题，我们可以进行再拆分，因为我们发现如果答案成立，那么若我们强制刚好搞完所有A，剩下的时间肯定可以搞完所有的B。而反过来这个命题也是成立的，即如果强制搞完所有A，若剩下的时间可以搞到要求的B，那么答案成立。

这像极了什么？

这像极了 ~~爱情~~ 背包问题，这样的话就可以搞一个动态规划切掉这道题

如果我们搞一个$f[i][j]$表示对于前$i$个程序猿，如果搞了$j$个A，那么最多可以搞多少个B

这样定义的话，我们不难发现任何时候，只要发现$f[i][j]>B$需要的数量，答案就可行

再想一下动态转移方程怎么写

对于第i个程序猿，假如他搞k个A，而剩下的时间可以搞$p$个B，那么$f[i][j]$就可以通过上一个状态$f[i-1][j-k]+p$转移过来，那么实现起来也就十分清晰明了了：
```cpp
int f[105][105];//f[i][k]:到第i个人时修k个A时修B的最大值 
inline bool check(int x){
    memset(f,0,sizeof(f));//重置 
    int tot=0;//作用在下面 
    for(register int i=1;i<=n;i++){//第i个人 
        for(register int j=0;j<=x/da[i];j++){//那个人修j个A
            int help=(x-j*da[i])/db[i];//剩下的时间最多能修多少个B 
            for(register int k=j;k<=min(tot+j,m);k++){//加上前面的共修k个A
                                                      //tot统计前面最多修多少个A 
		  				      //如果修不了这么多还更新答案可能会错 
                f[i][k]=max(f[i][k],f[i-1][k-j]+help);//通过状态转移方程转移 
            }
        }
        tot+=x/da[i];//更新一下最多修的A 
        if(f[i][m]>=m) return 1;//任何情况下只要发现可行就可以返回 
    }
    return 0;//怎样都弄不了就是不行了 
}
```
那么二分内部的实现已经over了

剩下的就是主函数了
## 完整代码
```
#include<cstdio>
#include<cctype>
#include<cstring>
using namespace std;
inline int max(int a,int b){return a>b? a:b;}
inline int min(int a,int b){return a<b? a:b;}
inline int R(){
    int r=0;char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=getchar();
    return r;
}
int n,m,da[105],db[105],l=1,r=0x7fffffff;
int f[105][105];//f[i][k]:到第i个人时修k个A时修B的最大值 
inline bool check(int x){
    memset(f,0,sizeof(f));//重置 
    int tot=0;//作用在下面 
    for(register int i=1;i<=n;i++){//第i个人 
        for(register int j=0;j<=x/da[i];j++){//那个人修j个A
            int help=(x-j*da[i])/db[i];//剩下的时间最多能修多少个B 
            for(register int k=j;k<=min(tot+j,m);k++){//加上前面的共修k个A
                                                      //tot统计前面最多修多少个A 
						      //如果修不了这么多还更新答案可能会错 
                f[i][k]=max(f[i][k],f[i-1][k-j]+help);//通过状态转移方程转移 
            }
        }
        tot+=x/da[i];//更新一下最多修的A 
        if(f[i][m]>=m) return 1;//任何情况下只要发现可行就可以返回 
    }
    return 0;//怎样都弄不了就是不行了 
}
int main(){
    n=R();m=R();
    for(register int i=1;i<=n;i++){
        da[i]=R(),db[i]=R();
        r=min(r,(da[i]+db[i])*m);
    }
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    printf("%d\n",l);
    return 0;
}
```
搞掂

Finally，谢谢大家

[更好的阅读体验](https://www.luogu.org/blog/HongseFox/ruan-jian-kai-fa)

---

## 作者：zhenglier (赞：1)

看到答案满足单调性，很容易想到二分。

这题的判断转移比较复杂（对于小蒟蒻来说），但状态很好设，所以采用记忆化搜索。

设$dp[i][j]$为当第一个物品完成进度$i$时，且当前搜到第$j$个人时第二个物品的最大完成度。

所以枚举每个人花在第一个物品上的时间就可以转移了。

这里要注意不要让第一个物品的完成度过大，要减枝。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[110],b[110];
int dp[110][110];
int limit;
int dfs(int x,int i){
	if(i>n&&x<m)return -1e9;
	if(i>n)return 0;
	if(x>=m)return limit/b[i]+dfs(x,i+1);
    if(~dp[x][i])return dp[x][i];
	int ret=-1e9; 
	for(int j=0;j*a[i]<=limit;++j){
        ret=max(ret,(limit-j*a[i])/b[i]+dfs(x+j,i+1));
        if(j+x>m)break;
	}
	return dp[x][i]=ret;
}
bool check(int x){
    memset(dp,-1,sizeof dp);
    limit=x;
    int ans=dfs(0,1);
    return ans>=m;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        scanf("%d%d",a+i,b+i);
	}
	int l=0,r=20000,ans=0;
	while(l<r){
		int mid=l+r>>1;
	    if(check(mid)){
	        ans=mid;
	        r=mid;
		}else l=mid+1;
	}
	cout<<ans<<endl;
}
```

---

## 作者：Kwork (赞：0)

唉~~~初始化~~~~~~~

这道题，我看着标签是二分就二话不说先把solve()过程打好了~~没有check函数~~。

然后想不出怎么check，感觉是DP然后感觉又没有必要二分了，直接就求解了。。估计会超时。。。。然后查了一些神犇的blog。。。

知道方程的我却已知没有过样例点，是的因为初始化的时候没有从0开始循环。。。

----------------------------------------------------------------------------------------------------

做法：首先答案是单调的，采用二分。然后呢，我们要判断能否在mid天内完成任务，那么我们只要知道在完成第一个软件的情况下，最多能完成多少模块的第二个软件。然后DP。






```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int maxn=105,INF=1234567890;
int n,m,work[maxn][5],l=0,r=10000,mid,f[maxn][maxn];
inline int read(){
    char ch=getchar();
    int data=0;
    while(ch<'0' || ch>'9') ch=getchar();
    do{
        data=data*10+ch-'0';
        ch=getchar();
    }while(ch>='0' && ch <='9');
    return data;
}
void init(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        work[i][1]=read();
        work[i][2]=read();
    }
    return;
}
bool check(int now){
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++) f[i][j]=-INF;
    f[0][0]=0;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)
            for(int k=0;k<=min(now/work[i][1],j);k++)
                f[i][j]=max(f[i][j],f[i-1][j-k]+((now-work[i][1]*k)/work[i][2]));
    if(f[n][m]>=m) return true;
    return false;
}
void solve(){
    while(l<r){
        mid=(l+r)/2;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    printf("%d",l);
    return;
}
int main(){
    init();
    solve();
    return 0;
}
```

---

## 作者：NishikinoMaki (赞：0)

##二分+DP

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int f[101][101];//第i个人完成1模块的j块，大家还可以完成2模块的最多模块数
int d[101][2]/*i是人，1,2是模块，存效率*/,l,mid,r,n,m,t;
int main()
{
    //freopen("software.in","r",stdin);
    //freopen("software.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&d[i][0],&d[i][1]);
    r=10000; 
    while (l<r)                                //二分枚举天数； 
    {
        mid=(l+r)/2;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++) 
                f[i][j]=-9999999;               
        f[0][0]=0;
        for(int i=1;i<=n;i++)                  //枚举人；  
            for(int j=0;j<=m;j++)              //枚举模块； 
                for(int k=0;k<=min(j,mid/d[i][0])/*第i个人mid天最多完成1模块数*/;k++)//枚举第i个人做几个1模块； 
                    f[i][j]=max(f[i][j],f[i-1][j-k]+(mid-d[i][0]*k)/d[i][1]);
```
/\*f[i-1,j-1]是第i-1个人做完j-k个1模块还能做几个2模块
mid-d[i,0]\*k是第i个人做k个1模块还剩的时间

(mid-d[i][0]\*k)/d[i][1]第i个人还能做几个2模块

所以f[i-1][j-k]+(mid-d[i][0]\*k)/d[i][1]是大家一共可以做几个2模块\*/

```cpp
        if (f[n][m]>=m)//如果可以完成的多； 
            r=mid;//短几天； 
        else 
            l=mid+1;//长一天； 
    }
    printf("%d",l);
}
```

---

