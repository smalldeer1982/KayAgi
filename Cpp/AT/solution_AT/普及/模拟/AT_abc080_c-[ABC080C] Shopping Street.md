# [ABC080C] Shopping Street

## 题目描述

Joisino计划要在商店街开一家店。

这家店在周一到周五的$5$ 个工作日都有营业，其中每个工作日又被划分成上午和下午$2$ 个时间段，也就是共有$10$ 个时间段。当然，至少要有$1$ 个时间段这家店营业。

商店街原来有$N$ 个店铺，从$1$ 到$N$ 编号。

这些店铺的营业时间将以$F_{i,j,k}=1$ 的形式给出。如果$F_{i,j,k}=1$ ，第$i$ 家店将在第$j$ 天的第$k$ 个时间段营业。在这里，我们这样定义：第$1$ 天是周一，第$2$ 天是周二，第$3$ 天是周三，第$4$ 天是周四，第$5$ 天是周五。同样的，第$1$ 个时间段是上午，第$2$ 个时间段是下午。

设$c_i$ 为第$i$ 家店和Joisino的店同时营业的时间段数，则Joisino商店的收益将会是$P_{1,c1}+P_{2,c2}+...+P_{N,cN}$ 。

请决定Joisino在这$10$ 个时间段分别是否营业，并求出Joisino商店可能的最大收益，且保证它至少要有$1$ 个时间段营业。

## 说明/提示

### 样例解释1
如果商店仅在第$1$ 家店营业时营业，收益将会是$8$ ，这是可能的最大收益。

### 样例解释2
由于必须至少有一个时间段商店营业，所以收益可能会是负数。

- $1 \leq N \leq 100$ 
- $0 \leq F_{i,j,k} \leq 1$ 
- 对所有满足 $1 \leq i \leq N$ 的 $i$ , 总有一对$(j, k)$ 满足$F_{i,j,k}=1$ 。
- $-10^7 \leq P_{i,j} \leq 10^7$ 
- 所有输入数据均为整数。

by @月见之兔

## 样例 #1

### 输入

```
1
1 1 0 1 0 0 0 1 0 1
3 4 5 6 7 8 9 -2 -3 4 -2```

### 输出

```
8```

## 样例 #2

### 输入

```
2
1 1 1 1 1 0 0 0 0 0
0 0 0 0 0 1 1 1 1 1
0 -2 -2 -2 -2 -2 -1 -1 -1 -1 -1
0 -2 -2 -2 -2 -2 -1 -1 -1 -1 -1```

### 输出

```
-2```

## 样例 #3

### 输入

```
3
1 1 1 1 1 1 0 0 1 1
0 1 0 1 1 1 1 0 1 0
1 0 1 1 0 1 0 1 0 1
-8 6 -2 -8 -8 4 8 7 -6 2 2
-9 2 0 1 7 -5 0 -2 -6 5 5
6 -6 7 -9 6 -5 8 0 -9 -7 -7```

### 输出

```
23```

# 题解

## 作者：SunSkydp (赞：5)

~~我的第一篇题解，管理员大大求过 QAQ~~

[原题链接](https://www.luogu.com.cn/problem/AT3715)

这道题直接暴力肯定会 [WA](https://www.luogu.com.cn/record/61426778)。

所以我们要考虑其他方法。

我们会发现，一共只有 $10$ 个时期

那么我们可以直接枚举所有状态，共 $2^{10} = 1024$ 种状态。

**提醒：** 必须从 $1$ 开始枚举， 因为至少得有一个时期开放。

[AC](https://www.luogu.com.cn/record/61426099)代码:
```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f //无限大
using namespace std;
int f[110][12]; 
int p[110][12];
int tmp[110]; //tmp存储状态
int main() {
	int n, ans = -inf;
	cin >> n;
	for(int i = 1; i <= n; i++)  
		for(int j = 1; j <= 10; j++)
			cin >> f[i][j];
	for(int i = 1; i <= n; i++)
		for(int j = 0; j <= 10; j++)
			cin >> p[i][j];
    //枚举每一种状态
	for(int i = 1; i < 1024; i++) {
		memset(tmp,0,sizeof(tmp));
		for(int j = 1; j <= n; j++) //对店铺枚举
			for(int k = 1; k <= 10; k++) //10个时段
				if(f[j][k] && ((1 << (k - 1)) & i)) tmp[j]++; //1 << (k - 1) 表示 2 的 k - 1 次方
		int now=0;
		for(int j = 1; j <= n; j++) now += p[j][tmp[j]]; //计算收益
		ans = max(ans, now); //打擂
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：幸存者 (赞：5)

## 思路
一看到这道题，就想到了 dfs 的做法。

定义一个求最大盈利值的变量 $maxn$。

直接枚举每个时间段是否营业，枚举完之后先判断是否至少有一个时间段营业，接着计算出盈利值，最后求出 $maxn$ 与其相比较较大的值存入 $maxn$ 即可。

注意：$maxn$ 初始值应设为 $-10^9$，因为 $n$ 最大值为 $100$，$P_{i,j}$ 最小值为 $-10^7$，所以 $maxn$ 初始值应设为 $100 \times -10^7=-10^9$。
## AC Code
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int n, f[110][20], p[110][20], a[20], maxn = -1e9;
void dfs(int step)
{
	if (step > 10)
	{
		bool flag = false;
		for (int i = 1; i <= 10; i++) if (a[i] == 1)
		{
			flag = true;
			break;
		}
		if (!flag) return;
		int sum = 0;
		for (int i = 1; i <= n; i++)
		{
			int cnt = 0;
			for (int j = 1; j <= 10; j++) if (a[j] == 1 && f[i][j] == 1) cnt++;
			sum += p[i][cnt];
		}
		maxn = max(maxn, sum);
		return;
	}
	a[step] = 0;
	dfs(step + 1);
	a[step] = 1;
	dfs(step + 1);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= 10; j++) cin >> f[i][j];
	for (int i = 1; i <= n; i++) for (int j = 0; j <= 10; j++) cin >> p[i][j];
	dfs(1);
	cout << maxn << endl;
	return 0;
}
```

---

## 作者：wanxinlian (赞：3)

**[题目链接](https://www.luogu.com.cn/problem/AT3715)**

乂，这题竟然没人发题解(~~交了20几次的我~~)，让我来吧。

**蒟蒻第一篇题解**

读完题目，大概了解是让我们计算最大利润，这种题目大概就是用 max 函数计算出结果，其实就是复杂的模拟题，像是 [P5016](https://www.luogu.com.cn/problem/P5016) 、 [AT3849](https://www.luogu.com.cn/problem/AT3849)  都是比较~~水~~好的模拟题。

梳理一下思路：

读入 --》 枚举每一天是否营业  --》计算利润 --》比较出最大值

### 举个栗子

那题目样例来说

```
1
1 1 0 1 0 0 0 1 0 1
3 4 5 6 7 8 9 -2 -3 4 -2
```
此时的 $N$ $=$ $1$ 只有一家店铺。一天有十个时段，这家店营业5天。

要想获得的利润多，让 $P_{1,c1}$ 最大。

```
3 4 5 6 7 8  9 -2 -3 4 -2
	      |最大同时营业五天
	      |而同时营业五天盈利最大
```
这样就得出答案为 $P_{1,5}$ $=$ $8$。

还有几个坑点：

1. 必须营业一天，所以要注意。
2. 计算 $c_i$ 时注意先清零。
3. 因为要算最大值，而答案又可能是负数，所以 ans 初始化时要注意。

再来看看蒟蒻的代码：
```
#include<bits/stdc++.h>
using namespace std;

int f[105][20],p[105][15],c[300],n；
int ans=-1e9,t[30];// ans 一定要开够小！

void init(){ //读入的函数
	cin>>n;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=10;j++) cin>>f[i][j];
	for(int i=1;i<=n;i++) 
		for(int j=0;j<=10;j++) cin>>p[i][j];
	return;
}

void fs(int m,int cnt){
	if(m>10&&cnt>0) { //特判一下是否会一天都不干
		for(int i=1;i<=n;i++) c[i]=0; //记得初始化
		int sum=0;
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=10;j++) {
				if(f[i][j]==1&&t[j]==1) c[i]++;
			}
		}
		for(int i=1;i<=n;i++) sum+=p[i][c[i]]; //计算总利润
		ans=max(ans,sum);return;//max函数计算最大
	}
	if(cnt==0&&m>10) return; //如果一天都不干，就直接返回
	t[m]=1;
	fs(m+1,cnt+1);
	t[m]=0;
	fs(m+1,cnt);
	
}

int main(){
	init();
	fs(1,0);
	cout<<ans<<endl;
	return 0;
}
```
### 谢谢欣赏

---

## 作者：Sirkey (赞：2)

这个题是妥妥的阅读理解。

~~我旁边的同学没看懂。~~

其实题目很简单。 你有 $10$ 个时间段，每个时间段要么营业，要么不营业。另外，你有另外的 $n$ 个店，他们也有一个营业时间。与他们第 $i$ 个点家一起营业了 $j$ 个时间段，就可以获得  `p[i][j]` 元钱。问你最大营业额。

~~好像真的有点复杂。~~

读懂了思路就好说了，说白了就是构造一个营业状态，再去计算你的营业额。

构造状态是关键。不难想到用状态压缩，但也可以用大法师。

讲到着题目就解决了，剩下的是代码实现问题，具体就看代码了。

Code:

```
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
//
//
//
using namespace std;
inline ll read() {
	ll f=0,t=0;
	char c=getchar();
	while(!isdigit(c)) t|=(c=='-'),c=getchar();
	while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
	return t?-f:f;
}
inline void out(ll x) {
	if(x<0) putchar('-');
	if(x>9) out(x/10);
	putchar('0'+x%10);
}
ll a[1005][20],s[1005][21],vis[1005];
ll ansk=-1e9;//细节一:有负数情况
int main() {
	int n=read();
	FOR(i,1,n) FOR(j,1,10) a[i][j]=read();
	FOR(i,1,n) FOR(j,0,10) s[i][j]=read();
	FOR(sub,1,(1<<10)-1) {
    //细节二:只能算2进制10位的数。
		memset(vis,0,sizeof(vis));
		FOR(i,1,n) 	FOR(j,1,10) if(a[i][j] && sub&(1<<(j-1))) vis[i]++;
		ll ans=0;
		FOR(i,1,n) ans+=s[i][vis[i]];
		ansk=max(ans,ansk);
	}
	cout<<ansk;
	return 0;
}
```
——end——


---

## 作者：hyc1026 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT3715)

思路：非常明显，因为情况较少，本题用 DFS 深搜即可。

为了求最大的盈利值，我们可能需要定义变量 $maxn$ 以记录最大值。注意：$maxn$ 要设成 $-10^9$，因为 $P_{i,j}$ 的最大值为 $-10^7$，所以 $maxn$ 应设成 $-10^9$，不能设成 $-10^7$，更不能设成 $0$。

对于数组建议开二维的。

对于变量建议开全局，因为程序有 DFS 算法，部分变量需要开全局。

此题还要判断店铺情况是否满足题意。因为店铺至少需要营业一个时间段。


### 代码如下：

```cpp
int a[15];
int f[110][15];
int p[110][15]; //使用二位数组记录利润
int maxn = -1e9; //不要设成0或者-1e7，仔细看数据范围
int n; //n要开全局

void dfs(int step)
{
	if(step > 10)
	{
		bool flag = false;
		for(int i=1; i<=10; i++)
			if(a[i] == 1) flag = true;
		if(!flag) return; //必须要有1个时间段营业
		int ans = 0;
		for(int i=1; i<=n; i++)
		{
			int cnt = 0;
			for(int j=1; j<=10; j++)
			{
				if(f[i][j] == 1 && a[j] == 1) cnt++;
			}
			ans += p[i][cnt];
		}
		maxn = max(maxn,ans); //求最大利益
		return;
	}
	a[step] = 0;
	dfs(step+1);
	a[step] = 1;
	dfs(step+1);
}
```

以上是深搜部分的代码。

接下来是主函数的（相较于 DFS 比较简单）。

```cpp
int main()
{
	cin >> n;
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=10; j++)
		{
			cin >> f[i][j];
		}
	}
	for(int i=1; i<=n; i++)
	{
		for(int j=0; j<=10; j++) //注意j要从0开始
		{
			cin >> p[i][j];
		}
	}
	dfs(1);
	cout << maxn;
	return 0;
}
```

以上为本题的题解。给个赞再走呗~

---

## 作者：AirQwQ (赞：0)

## 入手
* 对于 $ N \le 100 $，时间复杂度 $ O(n) $，所以 dfs 爆搜就好。

* 对于 $ ans \ge -10^9 $ 所以，用最大值变量 $ans$ 扫一遍即可。

* 具体爆搜思路：$2^{10}$ 判断每个时间段营业利益，用样例一为例（第一天上午就用 $1$ 代替，下午用 $2$，第二天上午用 $3$，营业用 $1$ 表示，不营业用 $0$）：

|  | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ | $10$ | 利润 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 第 $1$ 种情况 | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ |不合法
| 第 $2$ 种情况 | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $1$ |$4$
| 第 $3$ 种情况 | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $1$ | $0$ |$3$
| 第 $4$ 种情况 | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $1$ | $1$ |$4$
| 第 $5$ 种情况 | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $1$ | $0$ | $0$ |$4$
| 第 $6$ 种情况 | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $0$ | $1$ | $0$ | $1$ |$5$
| ··· | ··· | ··· | ··· | ··· | ··· | ··· | ··· | ··· | ··· | ··· | ···
| 第 $1024$ 种情况 | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ |$8$

枚举完即可得到最大值为 $8$。（其实不止第 $1024$ 种情况为 $8$，但是要把 $1024$ 行表放上来的话，就太夸张了）

## 实现

* 枚举每个时间段的如果利益和大于 $ ans $ 就更新。

```cpp
   if(step>10){
        int sum=0;
        for(int i=1;i<=n;i++){
            int num=0;
            for(int j=1;j<=10;j++) 
                num+=plan[j]*a[i][j];
                //利用bool的性质简写（少打字）
            sum+=b[i][num];
        }
        ans=max(ans,sum);
        return;
    }
```

* 多增加一个参数 $ cnt $ 于函数内更好判断是否全部不营业。（比最后判断更简洁）

```cpp
	if(cnt==0) return ;
```

## AcCode

```cpp
#include<bits/stdc++.h>
using namespace std;
int b[105][15],ans=-1e9,n;//价值可能是负数所以开-1e9。
bool a[105][15],plan[50];
void dfs(int step,int cnt){
    if(step==11){
        if(cnt==0) return ;//全部不营业。
        int sum=0;
        for(int i=1;i<=n;i++){
            int num=0;
            for(int j=1;j<=10;j++) 
                num+=plan[j]*a[i][j];
            sum+=b[i][num];//num表示同时营业数，因为在输入时已经处理所以能直接加。
        }
        ans=max(ans,sum);
        return;
    }
    plan[step]=0;
    dfs(step+1,cnt);
    plan[step]=1;
    dfs(step+1,cnt+1);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=10;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=0;j<=10;j++)
            cin>>b[i][j];//从0表示同时运营个数，方便dfs内加。 
    dfs(1,0);
    cout<<ans;
    return 0;
}

```

---

## 作者：SegTree (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/AT3715)

## 题目分析

首先输入 $n$，$f$ 数组和 $p$ 数组。

可以考虑枚举子集，枚举 $2^{10}$ 次，每次按照二进制判断是否营业，然后从 $1$ 枚举到 $n$，计算每次同时营业次数 $cnt$，将答案加上即可。计算完毕之后更新答案。由于 $\min\{{p_{i,j}}\}=-10^7$，$\max\{{p_{i,j}}\}=10^7$，$\max\{n\}=10^2$，所以答案最大为 $10^9$，最小为 $-10^9$，故使用 `int` 存储，并将答案初始值设为 $-10^9$ 或者 `INT_MIN`。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[11],f[103][11];
int n,p[103][11],maxn=-1e9,ans,cnt;
inline void check(int x){
    for(int i=1;i<=10;++i)a[i]=x%2,x/=2;
    return;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=10;++j)cin>>f[i][j];
    }
    for(int i=1;i<=n;++i){
        for(int j=0;j<=10;++j)cin>>p[i][j];
    }
    for(int i=1;i<1024;++i){
        check(i);
        ans=0;
        for(int j=1;j<=n;++j){
            cnt=0;
            for(int k=1;k<=10;++k){
                if(f[j][k]&&a[k]){
                    cnt++;
                }
            }
            ans+=p[j][cnt];
        }
        maxn=max(ans,maxn);
    }
    cout<<maxn<<endl;
    return 0;
}
```

---

## 作者：PeterBei (赞：0)

这道题可以使用 DFS 解决，需要对 Joisino 在哪一天营业进行搜索。

将搜索出的营业的天数直接代入数据得出营业额，再求最大值就行了。

需要单独注意两点：

1.因为至少要营业一天，所以要记录以营业天数，并排除掉营业天数为 0 的情况；

2.最大营业额可能为负数，在比较前需要将 ```maxx``` 赋值为 ```-0x3f3f3f3f```。

另外，Atcoder 貌似不允许出现名为 data 的变量数组名，需要额外注意。

代码：

```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;

int read()
{
	char c = getchar();
	int f = 1;
	int a = 0;
	while(c != '-' && (c > '9' || c < '0'))
	{
		c = getchar();
	}
	if(c == '-')
	{
		f = -1;
		c = getchar();
	}

	while(c >= '0' && c <= '9')
	{
		a = a * 10 + (c - '0');
		c = getchar();
	}

	return f * a;
}

int f[110][20];
int p[110][20];
int data[20];
int maxx = -0x3f3f3f3f;
int n = 0;

void dfs(int now, int sum)
{
	if(now != 10)
	{
		data[++now] = 0;
		dfs(now, sum);
		data[now] = 1;
		dfs(now, sum + 1);
	}
	else
	{
		if(sum == 0)
		{
			return ;
		}
		else
		{
			int cnt = 0;
			for(int i = 1; i <= n; i++)
			{
				int psum = 0;
				for(int j = 1; j <= 10; j++)
				{
					if(data[j] == f[i][j] && f[i][j])
					{
						psum++;
					}
				}
				cnt = cnt + p[i][psum];
			}
			if(cnt >= maxx)
			{
				maxx = cnt;
			}
		}
	}
}

int main()
{
	n = read();
	
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= 10; j++)
		{
			f[i][j] = read();
		}
	}
	
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= 10; j++)
		{
			p[i][j] = read();
		}
	}
	
	dfs(0, 0);
	
	cout << maxx;

	return 0;
}

```

---

## 作者：__Cartesian__Tree__ (赞：0)

用 $DFS$ 枚举新店铺的营业时间，

之后再计算利润。

**注意要判断是否满足店铺条件！！！**

$AC$ $Code$：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n, maxx = -100000000;
int a[10000];
int f[1010][20];
int p[1010][20];
void dfs(int step){
    if (step > 10){
      bool fg = true;
      for (int i = 1; i <= 10; i++)
          if (a[i] == 1) fg = false;//注意要判断是否不满足条件
      if (fg) return ;
      //计算利润
      int ans = 0;
      for (int i = 1; i <= n; i++){
          int cnt = 0;
          for (int j = 1; j <= 10; j++)
              if (f[i][j] == 1&& a[j] == 1)
                  cnt++;
          ans += p[i][cnt];
      }
      //取最大
      maxx = max(maxx, ans);
      return;
    }
    a[step] = 0;
    dfs(step + 1);
    a[step] = 1;
    dfs(step + 1);
}
int main(){
    cin>>n;
    //输入利润和原店铺的营业时间
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= 10; j++)
            cin >> f[i][j];
    }
    for (int i = 1; i <= n; i++){
        for (int j = 0; j <= 10; j++)
            cin >> p[i][j];
    }
    dfs(1);
    cout << maxx;
    return 0;
}
```

---

