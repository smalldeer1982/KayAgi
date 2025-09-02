# [USACO18FEB] Taming the Herd G

## 题目描述

清晨，Farmer John 被木头碎裂的声音吵醒。原来是奶牛们又一次从谷仓里逃出来了！
Farmer John 对奶牛们的清晨逃跑行为感到厌烦，他决定受够了：是时候采取强硬措施了。他在谷仓的墙上钉了一个计数器，用于记录自上次逃跑以来的天数。因此，如果某天早上发生了逃跑，计数器当天会显示 $0$；如果最近一次逃跑发生在 $3$ 天前，计数器会显示 $3$。Farmer John 每天都会仔细记录计数器的值。

年末到了，Farmer John 准备进行一些统计。他说，奶牛们要为此付出代价！但他发现他的记录似乎有些不对劲……

Farmer John 想知道自从他开始记录以来发生了多少次逃跑。然而，他怀疑奶牛们篡改了他的记录，他唯一能确定的是他开始记录的那天发生了一次逃跑。请帮助他确定，对于可能发生的逃跑次数，记录中必须被篡改的最小条目数。

## 说明/提示

如果只有 $1$ 次逃跑，那么正确的记录应该是 `0 1 2 3 4 5`，这与给定的记录有 $4$ 个条目不同。

如果有 $2$ 次逃跑，那么正确的记录可能是 `0 1 2 3 0 1`，这与给定的记录有 $2$ 个条目不同。在这种情况下，逃跑发生在第 $1$ 天和第 $5$ 天。

如果有 $3$ 次逃跑，那么正确的记录可能是 `0 1 2 0 0 1`，这与给定的记录只有 $1$ 个条目不同。在这种情况下，逃跑发生在第 $1$ 天、第 $4$ 天和第 $5$ 天。

以此类推。

题目来源：Brian Dean 和 Dhruv Rohatgi

## 样例 #1

### 输入

```
6
1 1 2 0 0 1```

### 输出

```
4
2
1
2
3
4```

# 题解

## 作者：Dilute (赞：12)

## 竟然没有人写题解2333那本蒟蒻就来$H_2O$一篇吧

首先，看完题面不难想到DP，之后再看数据范围考虑$O(N^3)$DP，之后瞎搞一通可以想到
> $f[i][j]$表示在前$i$个里面经历$k$次出逃可以取到最少的修改数

> 那么接下来我们就发现$f[i][j]$可以影响的范围为$f[u][j+1]$($i < u ≤n$)，然后我们就可以写出如下的程序：

```cpp
#include<bits/stdc++.h>

using namespace std;

int Num[110];
int Cnt[110][110];
int f[110][110]; // dp数组

int main(){
	memset(f, 127, sizeof(f)); // f数组初值极大
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &Num[i]);
    /*
     * Cnt[i][j]表示如果第i天出逃那么到第j天如果改成输入的序列需要修改的次数
     * 这里我们把Cnt预处理以下
     */
	for(int i = 0; i <= n; i++){
		int Cou = 0;
		for(int j = i; j <= n; j++){
			if(Num[j] != j - i)
				Cou++;
			Cnt[i][j] = Cou;
		}
	}
    // dp
	f[0][0] = 0;
	for(int i = 0; i <= n; i++)
		for(int j = 1; j <= n; j++)
			for(int u = i+1; u <= n; u++) // 枚举f[i][j]可以更新的状态
				if(f[u][j] > f[i][j-1] + Cnt[i+1][u]) // 如果更优
					f[u][j] = f[i][j-1] + Cnt[i+1][u];
    // 不难看出答案就是f[n][1]……f[n][n]
	for(int i = 1; i <= n; i++)
		printf("%d\n", f[n][i]);
}
```

---

## 作者：foreverlasting (赞：8)

[题面](https://www.luogu.org/problemnew/show/P4267)

DP。

思路好像和楼上不一样。$dp[i][j][k]$表示已经到了第$i$天，逃了$j$次，今天计数器记的数为$k$的最小值。那么两种转移：

1、当$k=0$时，$dp[i][j][0]=min(dp[i-1][j-1][p])+(a[i]!=0)$

2、当$k!=0$时，$dp[i][j][k]=dp[i-1][j][k-1]+(a[i]!=k)$

在第一条方程里，需要枚举$p$。所以复杂度是$O(n^4)$。然后我们可以用一个$g$维护一下$min(dp[i-1][j-1][p])$，所以变成了$O(n^3)$。

其实$i$和$j$这两维都可以滚掉，但我懒得写了。

code:
```
//2018.9.28 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=1e2+10;
namespace MAIN{
    int n;
    int dp[N][N][N],g[N][N];
    int a[N];
    inline void MAIN(){
        n=read();
        for(res i=1;i<=n;i++)a[i]=read();
        memset(g,inf,sizeof(g));
        memset(dp,inf,sizeof(dp));
        dp[0][0][0]=0;
        g[0][0]=0;
        for(res i=1;i<=n;i++)
            for(res j=1;j<=i;j++)
                for(res k=0;k<i;k++){
                    if(!k)dp[i][j][k]=g[i-1][j-1]+(a[i]!=0),g[i][j]=_min(g[i][j],dp[i][j][k]);
                    else dp[i][j][k]=dp[i-1][j][k-1]+(a[i]!=k),g[i][j]=_min(g[i][j],dp[i][j][k]);
                }
        for(res i=1;i<=n;i++)printf("%d\n",g[n][i]);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：vеctorwyx (赞：5)

## 好像没有 $O(n^2)$ 的题解，提供一个 $O(n^2)$ 做法

设 $dp[i][j]$ 表示前 $i$ 天出逃 $j$ 次的**最大符合天数**（不是最小不符合天数）。

对于每一个 $i$ 都有两种情况：

1. 当天的计数器是不正确的，则直接从上一天转移即可；

2. 当天的计数器是正确的，那么上次出逃的日子是可以算出来的，即 $i - a_i$ 。

$i - a_i$ 到 $i$ 之间的贡献可以提前预处理出来。

于是就有了两种转移（ $sum$ 是区间贡献）：

$$dp[i][j] = \max(dp[i - 1][j], dp[i - a[i] - 1][j - 1] + sum[i - a[i]][i])$$

然后由于第一天一定是出逃的，预处理只有一次出逃的情况即可。

**还有一种特殊情况**， 就是出逃次数很多的时候就要算每天出逃的情况，就是多算一种情况：

$$dp[i][j] = \max(dp[i][j], dp[i - 1][j - 1])$$

最后别忘了把最大符合换算成最小不符合。

code：

```
#include<bits/stdc++.h>
using namespace std;
int n, a[110], qc[110][110];
int dp[110][110], dp0[110][110], jc[110][110];
signed main(){
	memset(dp, -1, sizeof(dp));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++){//预处理区间贡献
		qc[i][i] = (a[i] == 0);
		int qwq = 1;
		for(int j = 1; j <= a[i] && i - j >= 1; j++){
			if(a[i - j] == a[i] - j)
				qwq++;
			qc[i][i - j] = qwq;
		}
	}
	dp[1][1] = (a[1] == 0);
	dp[0][0] = 0;
	int js = dp[1][1];
	for(int i = 2; i <= n; i++)//预处理j = 1的情况
		if(a[i] == i - 1)
			dp[i][1] = ++js;
		else
			dp[i][1] = js;
	for(int i = 2; i <= n; i++)
		dp[0][i] = dp[1][i] = 0;
	for(int i = 2; i <= n; i++){
		for(int j = 2; j <= i; j++){
				if(i - a[i] - 1 >= j - 1)
					dp[i][j] = max(dp[i - a[i] - 1][j - 1] + qc[i][i - a[i]], dp[i - 1][j]);
			else
				dp[i][j] = dp[i - 1][j];
			dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
		}
		for(int j = i + 1; j <= n; j++)
				dp[i][j] = 0;
	}
	for(int i = 1; i <= n; i++)
		cout << n - dp[n][i]<<"\n";
}
```

~~然后就以复杂度优势轻轻松松取得最优解。~~

---

## 作者：heaksicn (赞：5)

### 1 题目分析
题目说在一个牛棚里有一个计数器，用来记录每一天有没有奶牛逃跑。  
假设今天是第 $i$ 天，如果今天有奶牛逃跑，那么计数器就为 $0$  。   
如果在第 $i-j$ 天有奶牛逃跑，那么计数器就为 $j$   。  
但是记录有可能被篡改，给定一个记录的数列（有可能被篡改过），求在有 $i$ 个奶牛逃跑时的最小被篡改量。  
### 2 思路
因为求的是最小值，我们可以想到 dp 。  
我们可以用 $dp[i][j]$ 表示到第 $i$ 天为止有 $j$ 头奶牛逃跑时的最小被篡改数量  。  
容易得出，对于每一个 $u(i<u<=n)$ ，有 $dp[u][j]=min(dp[u][j],f[i][j-1]+$ 第 $i+1$ 到第 $u$ 天的篡改量)  。  
如果在循环内求出第 $i+1$ 到第 $u$ 天的篡改量，那么时间复杂度是 $O(n^4)$ ，有点憋屈。那么我们考虑优化  。  
新开一个数组 $sum$ ， $sum[i][j]$ 表示如果第 $i$ 天有人出逃那么到第 $j$ 天位置有几个地方被篡改过  。   
那么我们可以 $n^2$求出每一个 $sum$ ，状态转移也变成了 $f[u][j]=min(f[u][j],f[i][j-1]+sum[i+1][u])$ 。    

最终时间复杂度 $O(n^3)$ 。  
### 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110];
int sum[110][110];
int f[110][110];//f即dp
int main(){
    memset(f,127,sizeof(f));//初始值无穷大
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=0;i<=n;i++){//n^2预处理
        int cnt=0;
        for(int j=i;j<=n;j++){
            if(a[j]!=j-i) cnt++;//如果不一样计数
            sum[i][j]=cnt;
        }
    }
    f[0][0]=0;
    for(int i=0;i<=n;i++)//枚举i
        for(int j=1;j<=n;j++)//枚举j
            for(int u=i+1;u<=n;u++)//对于每一个u
                if(f[u][j]>f[i][j-1]+sum[i+1][u])  f[u][j]=f[i][j-1]+sum[i+1][u];//状态转移
    for(int i=1;i<=n;i++)cout<<f[n][i]<<endl;//输出
    return 0;//完结撒花！！！
}
```


---

## 作者：zhmshitiancai (赞：4)

裸DP题


设$f[i][j]$为在第$i$天开始出逃，到第$j$天时有多少个不同的记录条数。

$dp[i][j]$为前$i$天中，出逃$j$次的不同的记录条数的最小值。
答案为$dp[n][1] dp[n][n]$

转移方程 $dp[i][j]=min(dp[k-1][j]+dp[k])$

**code**
``` cpp

//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long  
const int INF=0x3f3f3f3f,MAX=100+5;
int n;
int a[MAX],f[MAX][MAX],dp[MAX][MAX];
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++)
			f[i][j]=f[i][j-1]+(a[j]!=(j-i));
	
	memset(dp,INF,sizeof(dp));
	for(i=0;i<=n;i++)
		dp[0][i]=0;
	
	dp[1][1]=(a[1]!=0);
	for(i=2;i<=n;i++)
	{
		for(j=1;j<=i;j++)
			for(int k=max(1,j);k<=i;k++)
			{
				dp[i][j]=min(dp[i][j],dp[k-1][j-1]+f[k][i]);
			}
	}
	for(i=1;i<=n;i++)
	{
		cout<<dp[n][i]<<endl;
	}
	return 0;
}
```

---

## 作者：ny_jerry2 (赞：2)

## 题意
农夫想要知道从他开始记录以来发生过多少次出逃。但是，他怀疑奶牛们篡改了它的记录，现在他所确定的只有他是从发生出逃的某一天开始记录的。

请帮助他求出，对于每个从他开始记录以来可能发生的出逃次数，他被篡改了的记录条数的最小值。
***

## 做法
仍然是**分段式线性 DP**
***

## 分析

1. 状态定义：$f_{i,j}$：前 $i$ 天中，出逃 $j$ 次记录的与给定序列不同的最小数目。

2. 状态转移：$f(i,j) = \min(f_{k-1,j-1}+g_{k,i})$  
   其中：$1 \le i \le n，1 \le j \le i，1 \le k \le i$
   
   因为前 $i$ 天中最多出逃 $i$ 次，所以 $j \le i$（但设为 $j \le m$ 也没关系）。
   
   意思是：前 $(k-1)$ 天出逃 $(j-1)$ 次（且第 $k$ 天出逃），一直到第i天再出逃的最小不同数量，与 $f_{i,j}$ 取最小值。
 
   唯一与模板不同的是 $g_{k,i}$。
   
   $g_{k,i}$ 表示在第 $k$ 天开始出逃，到第 $i$ 天时有多少个不同的记录条数。  
   可以预处理得到。
   
***
## 时间复杂度
预处理 $g$ 数组约为 $O(n^2)$。  
dp 约为 $O(n^3)$。

总时间复杂度约为 $O(n^3)$。

## 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=110;
int n;
int a[N];
int f[N][N];
int g[N][N];
int main(){
    memset(f,0x3f,sizeof f);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            g[i][j]=g[i][j-1]+(a[j]!=(j-i));
        }
    }
    f[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){//n可改为i,降低时间
            for(int k=1;k<=i;k++){
                f[i][j]=min(f[i][j],f[k-1][j-1]+g[k][i]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<f[n][i]<<endl;
    }
}
```

---

## 作者：DengDuck (赞：2)

这道题 $n\leq 100$，三维 DP 还蛮好想的。

设 $f(i,j,k)$ 表示处理到第 $i$ 项，奶牛出逃了 $j$ 次，计数器为 $k$。

由于第一天奶牛必然出逃，所以边界条件 $f(1,1,0)=[a_1\not =0]$。

接下来的状态很好弄，对于普通的 $k\not =0$ 的状态，显然只需要:

$$
f(i,j,k)=f(i-1,j,k-1)+[a_i\not =k]
$$

然而对于 $k=0$，前面是什么都有可能，所以我们需要枚举：

$$
f(i,j,0)=\min _{k=1}^{i-1}f(i-1,j-1,k) +[a_i\not =0]
$$

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=105;
LL n,a[N],f[N][N][N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	memset(f,27,sizeof(f));
	f[1][1][0]=(0!=a[1]);
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			if(j!=0)
			{
				for(int k=0;k<=n;k++)
				{
					f[i][j][0]=min(f[i][j][0],f[i-1][j-1][k]+(0!=a[i]));
				}	
			}
			for(int k=1;k<=n;k++)
			{
				f[i][j][k]=min(f[i][j][k],f[i-1][j][k-1]+(k!=a[i]));
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		LL mn=1e9;
		for(int j=0;j<=n;j++)
		{
			mn=min(mn,f[n][i][j]);
		}
		cout<<mn<<endl;
	}
}
```

---

## 作者：亦笙箫 (赞：2)

**前排吐槽**:这道题的翻译是真的毒瘤.~~(不看提示不明题意系列~~

附上提示[翻译链接](https://www.luogu.org/discuss/show/154229)

好了,看完提示并稍加思索过后,就知道这道题是一道裸的$DP$题了.

> 我们用$f[i][j]$表示从第$i$天开始出逃，到了第$j$天最少有多少次篡改了的记录.

>然后就可以得到$DP$的转移式子了.

然后就得到以下程序:


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

const int MAXX = 100;

int n;
int a[MAXX+5];
int f[MAXX+5][MAXX+5];
int cnt[MAXX+5][MAXX+5];

int main()
{
	memset(f,0x3f,sizeof(f));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<=n;i++)
	{
		int t=0;
		for(int j=i;j<=n;j++)
		{
			if(a[j]!=j-i)
				t++;
			cnt[i][j]=t;
		}
	}
	f[0][0]=0;
	for(int i=0;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int u=i+1;u<=n;u++)
				f[u][j]=min(f[u][j],f[i][j-1]+cnt[i+1][u]);
	for(int i=1;i<=n;i++)
		printf("%d\n",f[n][i]);
	return 0;
}
```


---

## 作者：TSY48 (赞：1)

**解题思路**

---

首先，看到数据范围不难想到区间 dp.

令 $g_{i,j}$ 代表让区间 ${a_i,a_{i+1},\dots,a_j}$ 变成 ${1,2,\dots,j-i+1}$，则 $g_{i,j}$ 可用 $O(n^3)$ 暴力求出。

在设 $f_{i,k}$ 代表目前考虑到 $i$，有 $k$ 次逃出。

由题意可知，每次逃出所代表的记录为 $[1,2,\dots,k]$，假设下次逃出在第 $k+1$ 天。

由上可推出，$f$ 的递推式为：
$$
f_{i,k}=\min \sum_{j=0}^{i-1} f_{j,k-1}+g_{j+1,i}
$$
答案即为 $f_{n,k}$，$k$ 从 $1$ 到 $n$。复杂度为 $O(n^3)$。

[AC 代码](https://www.luogu.com.cn/paste/70o3pq1b)

---

## 作者：YuYuanPQ (赞：1)

# 洛谷 P4267 题解

## 题目大意

此为简要概括：

农夫想要知道从他开始记录以来发生过多少次出逃。但是，他怀疑奶牛们篡改了它的记录，现在他所确定的只有他是从发生出逃的某一天开始记录的。请帮助他求出，对于每个从他开始记录以来可能发生的出逃次数，他被篡改了的记录条数的最小值。（题目中的，可自行查看）

## 分析

看到数据范围很小，于是想到了用动态规划**暴力**解决。

**时间复杂度**为 $\mathcal{O}{(N^2)}$。

提前**预处理**好一个二维数组 $s$。

$s[i][j]$ 表示假如在第 $i$ 天有奶牛跑了，到第 $j$ 天有多少记录被篡改（可能有点**难懂**）。

先设一个**状态** $dp[k][j]$。

$3$ 重循环，枚举 $i$，$j$，$k$。

它表示：前 $k$ 天有 $j$ 头奶牛逃跑时的**最小被篡改次数**。

那么，这个状态是怎么**转移**的呢？

很明显是由前 $i$ 天时，有 $j-1$ 头奶牛逃跑时的最小被篡改次数加上 $sum[i+1][k]$，和这个状态自己取个最小值。

（可看代码第 $39$ 行）

## 具体做法

- 输入。
- 动态规划。
- 输出。

## 注意事项

- 将 $dp$ 数组**赋极大值**。
- 输出的是 $N$ 行数，不是 $1$ 行数。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110];
int s[110][110];
int dp[110][110],n;
int qread()
{
    char ch=getchar();
    int fu=1,sum=0;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') fu=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        sum=(sum<<1)+(sum<<3)+ch-'0';
        ch=getchar();
    }
    return sum*fu;
}
int main(){
    memset(dp,0x3f,sizeof(dp));
    n=qread();
    for(int i=1;i<=n;i++) a[i]=qread();
    for(int i=0;i<=n;i++){
        int k=0;
        for(int j=i;j<=n;j++)
        {
            if(a[j]!=j-i) k++;
            s[i][j]=k;
        }
    }
    dp[0][0]=0;
    for(int i=0;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=i+1;k<=n;k++)
                if(dp[k][j]>dp[i][j-1]+s[i+1][k])
                    dp[k][j]=dp[i][j-1]+s[i+1][k];
    for(int i=1;i<=n;i++)
        printf("%d\n",dp[n][i]);
    return 0;
}
```

## 另附

- [题目链接](https://www.luogu.com.cn/problem/P4267)
- 如有**更好**做法，欢迎[私信我](https://www.luogu.com.cn/chat?uid=1029900)。
- [我的提交记录](https://www.luogu.com.cn/record/list?pid=P4267&user=1029900)
- 这是我第 $6$ 次写题解，如有错误请各位大佬**指出**。

---

## 作者：Jessica2333 (赞：1)

## 思路
### 1、分析
这是一道 dp 题 ~~（大概还是比较容易看出来的吧）~~，状态有：时间、出逃情况、篡改的记录。时间这个状态可以用一个维度表示。出逃情况包含出逃总的次数和每次出逃分别的时间，每次出逃分别的时间——这看起来不太好维护。但是我们思考：状态的转移需要用到每一次的出逃时间吗？在状态转移时，假设我们要转移到第 $k$ 天，出逃次数为 $j$ 的状态，那么我们可以选择在某天出逃，那么就只要出逃次数为 $j-1$ 的状态；我们也可以选择不出逃，那么我们就需要当前出逃次数下的最后一次出逃的时间。

最后我们发现：**对于出逃情况，其实状态的转移只会用到总的出逃次数和最后一次出逃时间。** 所以我们：**记 $dp[k][i][j]$ 表示到第 $k$ 天，总共出逃 $i$ 次，最后一次出逃是在第 $j$ 天的这种状态下，最少的篡改记录次数。**

### 2、转移方程

这天不出逃：
$$dp_{k,i,j}=\min(dp_{k-1,i,j}+opt)$$
$opt$ 为 $a[k]$ 是否等于 $k-j$，是则为 $0$，否则为 $1$。

如果不出逃，就通过原有的出逃 $i$ 次的状态来转移；最后一次出逃是在第 $j$ 天，那么从第 $j$ 天开始，正确数据就是 $0,1,2,3\dots$所以到第 $k$ 天时正确数据就应该为 $k-j$，我们就只需要看第 $k$ 天计数器读数（$a[k]$）是不是等于正确数据（$k-j$），以此决定是否要在 $k-1$ 天、出逃 $i$ 次、最后出逃在第 $j$ 天的状态上加一；

这天出逃：
$$dp_{k,i,j}=\min(dp_{j-1,i-1,x}+opt)$$
$opt$ 为计数器读数从第 $j$ 天到第 $k$ 天，篡改数据的数量。

选择出逃，也就是说最后在第 $j$ 天出逃，那么状态就需要从到第 $j-1$ 天、出逃次数 $-1$ 的状态转移得来，在这些状态中取 $min$ 即可；由于最后是在第 $j$ 天出逃，所以从 $j$ 开始所对应的正确数据就是 $0,1,2,3\dots$那么就还得看计数器在从 $j$ 到 $k$ 的这段时间的记录否等于正确数据；若不是则篡改次数加一。

时间复杂度 $O(n^4)$，$n$ 很小只有 $100$，~~不用优化都稳稳当当~~能过，但是可以优化。

### 3、优化
我们发现在选择出逃状态转移需要用到从到第 $j-1$ 天、出逃次数 $-1$ 的状态最小值（这里最后一次出逃的时间是需要枚举的），那么我们可以用一个二维数组 $ans[i][j]$ 来存到第 $i$ 天，出逃次数为 $j$ 的所有状态中，篡改次数的最小值，这样就可以直接使用而不需要枚举。

除此之外在选择出逃状态的状态转移还需要用到当最后一次出逃是在第 $j$ 天时，计数器读数从第 $j$ 天到第 $k$ 天，篡改数据的数量（也就是从 $a[j]$ 到 $a[k]$ 与 $0,1,2,3\dots$不同的数据的数量），这个我们是遍历来求的，但是我们在开始 $dp$ 前可以预处理一下，用 $dif[i][j]$ 来存假设从第 $i$ 天出逃，到第 $j$ 天不发生新的出逃的数据与计数器读数不同数据的数量，也就是篡改数据的数量，这样在状态转移时就可以直接使用啦^_^。

时间复杂度 $O(n^3)$。

## 变量

$a[i]$：计数器第 $i$ 天的读数；

$dp[k][i][j]$：到第 $k$ 天，总共出逃 $i$ 次，最后一次出逃是在第 $j$ 天的这种状态下，最少的篡改记录次数；

$ans[i][j]$：到第 $i$ 天，出逃次数为 $j$ 的所有状态中，篡改次数的最小值；

$dif[i][j]$：从第 $i$ 天出逃，到第 $j$ 天（不发生新的出逃）数据被篡改了的数量。

## 代码
```cpp
#include<iostream>
#include<string.h>
using namespace std;
int N,a[108],dp[108][108][108],dif[108][108],ans[108][108];
int main()
{
	int i,j,k;
	cin>>N;
	for(i=1;i<=N;i++) cin>>a[i];
	memset(dp,0x3f,sizeof(dp));
	memset(ans,0x3f,sizeof(ans));
	dp[1][1][1]=(a[1]==0?0:1);
	for(i=1;i<=N;i++)
		for(j=i;j<=N;j++)
			dif[i][j]=dif[i][j-1]+(a[j]==j-i?0:1);
	for(k=1;k<=N;k++)
	{
		for(i=1;i<=k;i++)
		{
			for(j=i;j<=k;j++)
			{
				dp[k][i][j]=min(dp[k][i][j],ans[j-1][i-1]+dif[j][k]);
				dp[k][i][j]=min(dp[k][i][j],dp[k-1][i][j]+(a[k]==k-j?0:1));
				ans[k][i]=min(ans[k][i],dp[k][i][j]);
			}
		}
	}
	for(i=1;i<=N;i++)
		cout<<ans[N][i]<<endl;
	return 0;
}
//2023.5.9 by Jessica2333 ^_^
```


---

## 作者：lishujia (赞：1)

## 思路分析

一道dp题。

设 $f[i][j][k]$ 表示前 $i$ 天发生了 $j$ 次出逃且最后一次出逃发生在第 $k$ 天篡改了的记录条数的最小值。

1. 当 $i=k$ 时，
$f[i][j][k]=min(f[i][j][k],f[i-1][j-1][t])+(a[i]!=0)$
1. 当 $i!=k$ 时，
$f[i][j][k]=f[i-1][j][k]+(i-k!=a[i])$

我们还可以新建一个数组 $g$ 维护 $f[i-1][j-1][t]$ 最小值，将时间复杂度优化至 $O(n^3)$ 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,a[N],f[N][N][N],g[N][N];
int main()
{
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	f[0][0][0]=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	    scanf("%d",a+i);
	for(int i=1;i<=n;i++)
	{
		if(i!=1)f[i][1][1]=f[i-1][1][1];
		else f[i][1][1]=0;
		if(i-1!=a[i])f[i][1][1]++;
		g[i][1]=min(g[i][1],f[i][1][1]);
	}
	for(int i=2;i<=n;i++)
	    for(int j=2;j<=i;j++)
	        for(int k=j;k<=i;k++)
	        {
	        	if(k==i)f[i][j][k]=min(f[i][j][k],g[i-1][j-1])+(a[i]!=0);
				else f[i][j][k]=f[i-1][j][k]+((i-k)!=a[i]);
				g[i][j]=min(g[i][j],f[i][j][k]);
			}
    for(int i=1;i<=n;i++)
    {
    	int ans=1e9;
    	for(int j=i;j<=n;j++)
    	    ans=min(ans,f[n][i][j]);
    	printf("%d\n",ans);
	}
	return 0;
}

---

## 作者：lgswdn_SA (赞：1)

这不是非常显然的一个 DP 吗（真的。

题目中有 $4$ 个要素，$n$，出逃次数，当前距离上一次出逃有多少次，最少篡改数。显然前 $3$ 个都可以被计入决策中，求最后一个。就这样：$f(i,j,k)$ 代表前 $i$ 天出逃了 $j$ 且第 $i$ 天显示的记录（未篡改）是 $k$ 的最大未篡改的数量。转移方程就非常显然，如果 $k=0$ 代表这天有新的出逃，$f(i,j,0)=\max f(i-1,j-1,x)+[a_i=0]$。如果 $k\neq 0$，$f(i,j,k)=f(i-1,j,k-1)+[a_i=k]$。

时间复杂度 $O(n^3)$，空间复杂度把 $i$ 滚动掉就是 $O(n^2)$（但不滚动也没什么问题）。

一些边界和初始化问题。$f$ 初始化为 $-\inf$，$f(1,1,0)=[a_1=0]$。

方程中有一个 $\max f(i-1,j-1,x)$，我们记录 $g(i,j)=\max f(i,j,x)$，所以答案就是 $ans_j=n-g(n,j)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
const int N=109;

int n,a[N],f[N][N][N],g[N][N];

int main() {
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	memset(f,128,sizeof(f)), memset(g,128,sizeof(g));
	f[1][1][0]=g[1][1]=(a[1]==0);
	rep(i,2,n) rep(j,1,i)
		rep(k,0,i) {
			if(k==0) f[i][j][0]=g[i-1][j-1]+(a[i]==0);
			else f[i][j][k]=f[i-1][j][k-1]+(a[i]==k);
			g[i][j]=max(g[i][j],f[i][j][k]);
		}
	rep(j,1,n) printf("%d\n",n-g[n][j]);
	return 0;
}
```

---

## 作者：RayAstRa_ (赞：0)

## Description

在 $n$ 天的时间内，有一个计数器会每天记录当天距离上一次出逃事件的日期（若当天发生出逃则记录为 0），但是数列被篡改了。给出记录的数列 $A$，对于 $\forall i \in [1,n]$，求在所有发生 $i$ 次出逃事件的序列中，和序列 $A$ 不一致的元素个数的最小值。

## Idea

考虑动态规划，设 $f_{i,j,k}$ 表示当前第 $i$ 天，共发生了 $j$ 次出逃事件且上一次出逃发生在第 $k$ 天。

设函数 $chk(i,j)=\begin{cases}
   1 &,a_i\not= i-j \\
   0 &,a_i=i-j
\end{cases}$。

枚举 $i,j,k$，若当天未发生出逃，则 $k$ 表示上一次发生出逃的日期，$f_{i,j,k}=f_{i-1,j,k}+chk(i,k)$。若当天发生出逃，则 $k$ 表示当天前上一次发生出逃的日期，$f_{i,j,i}=\min f_{i-1,j-1,k}+chk(i,i)$。特别地，对于只发生一次出逃的情况需单独统计，$f_{i,1,1}=f_{i-1,1,1}+chk(i,1)$。

对于发生 $i$ 次出逃的情况，答案即为 $\min f_{n,i,k}$。

另外对于循环范围，注意若发生 $x$ 次出逃，则上一次发生出逃的最小日期为 $x$。

时间复杂度为 $O(n^3)$，足以通过本题。

## Code

```cpp
#include<bits/stdc++.h>
#define reg register int
#define min(x,y) (x<y?x:y)
using namespace std;
template<class T>inline void read(T &k){
	char c=0;k=0;int t=1;
	while(!isdigit(c)){
		if(c=='-')t=-1;
		c=getchar();
	}
	while(isdigit(c))k=k*10+c-48,c=getchar();
	k*=t;
}
namespace Main{
const int N=150,inf=1e9;
int n,a[N],f[N][N][N],ans;
inline bool chk(int d,int l){
	return a[d]!=d-l;
}
void Main(){
	read(n);
	for(reg i=1;i<=n;i++)
		read(a[i]);
	for(reg i=1;i<=n;i++)
		for(reg j=1;j<=n;j++)
			for(reg k=1;k<=n;k++)
				f[i][j][k]=inf;
	f[1][1][1]=chk(1,1);
	for(reg i=2;i<=n;i++){
		f[i][1][1]=f[i-1][1][1]+chk(i,1);
		for(reg j=2;j<=i;j++){
			for(reg k=1;k<i;k++)
				f[i][j][i]=min(f[i][j][i],f[i-1][j-1][k]+chk(i,i));
			for(reg k=j;k<i;k++)
				f[i][j][k]=f[i-1][j][k]+chk(i,k);	
		}		
	}
	cout<<f[n][1][1]<<endl;
	for(reg i=2;i<=n;i++){
		ans=inf;
		for(reg j=i;j<=n;j++)
			ans=min(ans,f[n][i][j]);
		cout<<ans<<endl;
	}

}
} 
signed main(){
	Main::Main();
	return 0;
}
```

---

## 作者：OreoTheGreat (赞：0)

三维dp 


------------
i 表示过了多少天，j 表示出逃了多少次，k 表示上次出逃的天数

------------
Code: (JAVA)
```java
import java.io.*;
import java.util.*;
public class taming {
	static int INF = (int)(2*Math.pow(10, 9));
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new FileReader("taming.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("taming.out")));
		int N = Integer.parseInt(br.readLine());
		int[] log = new int [N+1];
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i = 1; i <= N; i++)
			log[i] = Integer.parseInt(st.nextToken());
		br.close();
		
		int[][][] dp = new int [N+1][N+1][N+1]; //i: Number of Days, j: Number of breakouts, k: Date of last breakout. i >= k >= j
		
		//dp array initialization
		for(int i = 1; i <= N; i++) 
			for(int j = 1; j <= N; j++) 
				for(int k = 1; k <= N; k++) 
					dp[i][j][k] = INF;
		
		//Base Case
		dp[1][1][1] = (log[1] == 0)?0:1;
		for(int i = 1; i <= N; i++)
			dp[i][1][1] = Math.min(dp[i][1][1], dp[i-1][1][1] + ((log[i] == (i-1))?0:1));
		
		//Transformation
		for(int i = 2; i <= N; i++) {
			for(int k = 2; k <= N; k++) {
				for(int j = 2; j <= N; j++) {
					if (i < j) {continue;}
					if (i < k) {continue;}
					if (k < j) {continue;}
					if (i == k) 
						for(int a = j-1; a <= (i-1); a++) 
							dp[i][j][k] = Math.min(dp[i][j][k], dp[i-1][j-1][a] + ((log[i] == 0)?0:1));
					else
						dp[i][j][k] = Math.min(dp[i][j][k], dp[i-1][j][k] + ((log[i] == (i-k))?0:1));
				}
			}
		}
		
		//output
		for(int j = 1; j <= N; j++) { //for each number of breakouts 
			int min = INF;
			if (j == 1) 
				out.println(dp[N][j][1]);
			else {
				for(int k = j; k <= N; k++) 
					min = Math.min(min, dp[N][j][k]);
				out.println(min);
			}
		}
		out.close();
	}
}
```


---

