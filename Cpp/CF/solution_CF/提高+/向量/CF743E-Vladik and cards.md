# Vladik and cards

## 题目描述

Vladik was bored on his way home and decided to play the following game. He took $ n $ cards and put them in a row in front of himself. Every card has a positive integer number not exceeding $ 8 $ written on it. He decided to find the longest subsequence of cards which satisfies the following conditions:

- the number of occurrences of each number from $ 1 $ to $ 8 $ in the subsequence doesn't differ by more then $ 1 $ from the number of occurrences of any other number. Formally, if there are $ c_{k} $ cards with number $ k $ on them in the subsequence, than for all pairs of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF743E/0c6cc5f621659ae2ddf5ab0dac10dd28e326ec14.png) the condition $ |c_{i}-c_{j}|<=1 $ must hold.
- if there is at least one card with number $ x $ on it in the subsequence, then all cards with number $ x $ in this subsequence must form a continuous segment in it (but not necessarily a continuous segment in the original sequence). For example, the subsequence $ [1,1,2,2] $ satisfies this condition while the subsequence $ [1,2,2,1] $ doesn't. Note that $ [1,1,2,2] $ doesn't satisfy the first condition.

Please help Vladik to find the length of the longest subsequence that satisfies both conditions.

## 说明/提示

In the first sample all the numbers written on the cards are equal, so you can't take more than one card, otherwise you'll violate the first condition.

## 样例 #1

### 输入

```
3
1 1 1
```

### 输出

```
1```

## 样例 #2

### 输入

```
8
8 7 6 5 4 3 2 1
```

### 输出

```
8```

## 样例 #3

### 输入

```
24
1 8 1 2 8 2 3 8 3 4 8 4 5 8 5 6 8 6 7 8 7 8 8 8
```

### 输出

```
17```

# 题解

## 作者：Mihari (赞：4)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF743E)

# 题解

因为所有数字的选择必须连续，也就是说，同一数字的选择越少，其要求越容易达成，并且题目要求任意两个数字的出现次数 $c(i),c(j)$ 都必须保证 $\mid c(i)-c(j)\mid \le 1$，我们不妨二分数字出现的最小次数 $k$（有少部分数字出现次数为 $k+1$）然后对这个 $k$  进行合法性检查，显然，$k$ 越大，答案序列越大。

现在问题在于如何进行合法性检查，我们定义 $f[i][j]$ 为到第 $i$ 位，数字出现的集合为 $j$ 时的最大序列长度？

其实有更好的定义方法，定义 $f[i][j]$ 为到第 $i$ 位，数字出现的集合为 $j$ 时，出现次数为 $k+1$ 的数字最多的出现次数，因为我们已经固定每个数字**至少**出现 $k$ 次，那么出现 $k+1$ 次的数字越多，序列长度必然越大。

考虑如何进行转移：

我们可以将每个数字的出现位置单独储存起来，并用类似于指针的数组记录第 $i$ 位时，数字 $num$ 应该从哪个位置开始，因为有些位置在 $i$ 之前，已经不能选择了，为了快速得到起始位置，我们才这样做，我们记这个数组为 $cur$

对于一个数字 $t$，假设我们已经要选择它，那么显然我们要选择它的连续的 $k$ 个位置，即起始位置为 $pos_{cur_{t,i}}$，终止位置为 $pos_{cur_{t,i}+k-1}$，然后我们检验第 $i$ 位之后是否还存在 $k$ 个 $t$ 即可

然后，便可得到状转
$$
f[pos_{cur_{t,i}+k-1}][j']=\max\{f[pos_{cur_{t,i}}][j]\}
$$
其中，$j'$ 是 $j$ 多出 $t$ 这个数字的集合

但是这只是一种情况，数字 $t$ 显然有可能出现 $k+1$ 次，我们只需再检验第 $i$ 位之后是否还存在 $k+1$ 个 $t$ 之后，再用状转
$$
f[pos_{cur_{t,i}+k}][j']=\max\{f[pos_{cur_{t,i}}][j]+1\}
$$
注意两个式子中的细微差别，还要些细节可直接见代码

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13442790.html
```



---

## 作者：Jμdge (赞：4)

```
贡献一篇题解（由于这道题我水挂了，掉进了巨坑）
其实这就是一道状压dp+二分答案（还是那句话，想到就挺简单）
但是还是要分析分析的：
这道题首先要想到，我们提取出的子序列中任意一个数都是连在一块的
（就是坨在一块儿的），那么这些数字中夹杂的其他数字也就是作废了。
假设我们要在“1,2,3,1,2,1,3,3,1”中提取出3个1，
1. 我们可以选择“ **1** ,2,3, **1** ,2, **1** ,3,3,1”这三个加粗的1，那么“2,3,2”就被作废了，不能用了，
2. 我们也可以提取“**1** ,2,3, **1** ,2,1,3, **1** ”中这三个不连续、不紧凑的1呢？
那么我们浪费的其他数字显然更多了（2,3,3,2,3,3），所以明显前者更优，然后我们只需要开个向量存每个数字的位置（当然是升序存的），
计算得出当前点后面添上的数字串的末尾所处的位置，以及一系列的操作后就可以完成dp的推导了。
```

```cpp
#include<bits/stdc++.h>
#define M 1010
using namespace std;
inline int read(){
	int x=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x;
}
int n,ans;
int x[M],num[10];
int f[M][(1<<8)+10];
vector<int> at[10];
bool check(int tim){ //check函数，ans在这里更新
	memset(num, 0 ,sizeof(num)); //每次清零
	memset(f , 250 , sizeof(f)); //每次变成-inf
	f[0][0]=0; int tot=-0x3f3f3f3f;
	for(int i=0;i<n;++i){ //线性推i
		for(int j=0;j<(1<<8);++j) if(f[i][j]>=0) //枚举状态
		for(int k=0;k<8;++k){ //枚举当前位后接下来要添上的tim个数字k
			if(j&(1<<k)) continue;
		    int now=num[k]+tim-1; //计算得出k最后一位的位置
		    if(now<at[k].size())
		    	f[at[k][now]][j|(1<<k)]=max(f[at[k][now]][j|(1<<k)],f[i][j]);
		    if(++now<at[k].size())
		    	f[at[k][now]][j|(1<<k)]=max(f[at[k][now]][j|(1<<k)],f[i][j]+1);
		}
	    ++num[x[i]]; //将当前位在所处的向量数组中减去（相当于减去，也就是不能用了）
	}
	for(int i=0;i<=n;++i)
		tot=max(tot , f[i][(1<<8)-1]);
	if(tot<0) return false; //没有dp成功直接return false
	ans=max(ans , 8*tim+tot); //dp成功了ans就等于八倍的tim加上额外的个数
	return true;
}

int main(){
	n=read(); x[0]=9;//巨坑在这里，x0要变成9，不然check里i=0的时候。。。哎。。。栽这儿了
	for(int i=1;i<=n;++i)
		x[i]=read()-1,at[x[i]].push_back(i);
	int l=0,r=n/8+1;
	for(int i=0;i<8;++i) //先对r做个优化（能说是剪枝么？）
		r=min(r,(int)at[i].size());
	if(!r){  //特判，如果有任意一个数没出现过
		for(int i=0;i<8;++i)
			if(at[i].size()) ++ans;
		printf("%d\n",ans);
		return 0;
	}
	while(l<=r){ //主函数很简短，主要就是二分
		int mid=l+r>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：HenryHuang (赞：1)

upd（20200226）:对当时的一些笔误做了修改，并添加了一些内容

正解当然是 $\texttt{DP}$,在这里不在多说。

但是如果想不到 $\texttt{DP}$,在考场上又该怎么办呢？

在这里提供一种切实可过的思路。

我们发现，当我们所要取的数的顺序确定，以及每个数要取多少个也确定的时候，那么这个时候整个序列的最优取法就已经被确定了。因为这个时候，肯定是越靠前越好。

比如1,2,2,1,1,2,2,如果我要取 1,2,2

显然应该取靠前的，即 **1,2,2**,1,1,2,2,而不会去取 1,2,2,1,**1,2,2**,这样显然是不够优秀的。

由于答案具有单调性，所以我们可以考虑二分每个数要取多少个，再枚举排列。

这样的时间复杂度为 $O(8! \cdot \log_2n)$

但是我们刚刚的想法并没有考虑问题中的限制二，即任意两种数字的数量差不大于一。

这个也好办，在二分的时候，我们已经求出了各个数字的数量全部一样时的最优解

这个时候只需要再暴力枚举一下每个数的数量能不能加一，dfs一遍即可。

时间复杂度为 $O(8 \cdot 2^8)$

注意，要实现这样的复杂度，还需要提前预处理一下每一个位置之后的每一种数，第 $i$ 个在什么位置，这样才能够做到 $O(1)$ 转移

代码十分好实现，就不贴出来了

总时间复杂度为 $O(8!\cdot8\cdot 2^8\cdot \log_2n)$。理论上是可以通过本题的。且由于数据的特性，即使是最强的数据该算法也无法跑满。所以请放心使用。

我还是把当年丑得要死代码贴出来吧：

[这里是代码](https://www.luogu.com.cn/paste/g4sqnvfs)

---

## 作者：帅到报警 (赞：1)

### 【题意】
我们要在一个只存在 1 - 8 的序列中寻找一个子序列，使得这个子序列相同的元素出现位置在一起，而且 1 - 8 这几个数的出现次数相差不超过 1。求符合条件的最长的子序列。

### 【分析】
刚看到这道题的时候，我 &^&*&%^*&$

然后，我就 &*%$^@(@ (☄◣ω◢)☄

在考场上的我就草草打了一把暴力深捜，还整整调了半个小时，最后便怒得 10 分。。。。。

那么这道 CF E题到底该怎么做呢？？？像这样的去掉几个数的题目，一般都是要~~贪心一把~~ dp 一把。但是这样有非常多的状态，该怎么解决呢？

在考场上，我就想到了用**二分枚举每个元素的个数来解决**。因为每个比答案小的状态都是包含在答案的状态中的，即这样的答案是有单调性的，可以用二分解决。

然后考虑 dp，我们发现 n 的范围是小于 1000 的，那么状压一下就可以找出所有的可行状态了。

### 【核心代码】
1、dp 方程：

对于每一个枚举的答案，dp[ i ][ j ] 表示**前 i 个数中 j 状态下的出现过的数的最多的出现次数。** (j 表示此时的状态，其中 1 表示此位数字出现了)。
```cpp
inline int check(int len)
{
    memset(cur, 0, sizeof(cur));
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < (1 << 8); j++)
        {
            if(dp[i][j] == -1) continue;
            for(int k = 1; k <= 8; k++)
            {
                if(j & (1 << (k - 1))) continue;
                int x = cur[k] + len - 1;
                if(x >= g[k].size()) continue;
                dp[g[k][x]][j | (1 << (k - 1))] = Max(dp[g[k][x]][j | (1 << (k - 1))], dp[i][j]);
                if((++x) >= g[k].size()) continue;
                dp[g[k][x]][j | (1 << (k - 1))] = Max(dp[g[k][x]][j | (1 << (k - 1))], dp[i][j] + 1);
            }
        }
        ++cur[a[i]];
    }
    int ans = -1;
    for(int i = 1; i <= n; i++)
        ans = Max(ans, dp[i][(1 << 8) - 1]);
    if(ans == -1) return -1;
    return ans * (len + 1) + (8 - ans) * len;
}
```

2、二分查找答案：

因为最多 1000 个数，所以每个数最多出现次数为 125 次，二分边界就是 n / 8。然后有一个特判，**如果二分时没有找到就说明是不存在 1 个及以上的合法状态，那么就统计出现了的数的个数即可**。
```cpp
void Solve()
{
	int l = 1, r = n / 8, mid;
    while(l + 1 < r)
    {
        mid = (l + r) >> 1;
        if(check(mid) != -1) l = mid;
        else r = mid - 1;
    }
    int ans = Max(check(l), check(r));
    if(ans == -1)
    {
        ans = 0;
        for(int i = 1; i <= 8; i++)
            if(g[i].size()) ans++;
    }
    printf("%d\n", ans);
}
```
### 【正解】
```
#include <bits/stdc++.h>
#define N 1010
using namespace std;

int n;
vector<int> g[10];
int a[N], p[10], cur[10], dp[N][1 << 8];

inline int Max(int a, int b)
{
	return a > b ? a : b;
}

inline int check(int len)
{
    memset(cur, 0, sizeof(cur));
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < (1 << 8); j++)
        {
            if(dp[i][j] == -1) continue;
            for(int k = 1; k <= 8; k++)
            {
                if(j & (1 << (k - 1))) continue;
                int x = cur[k] + len - 1;
                if(x >= g[k].size()) continue;
                dp[g[k][x]][j | (1 << (k - 1))] = Max(dp[g[k][x]][j | (1 << (k - 1))], dp[i][j]);
                if((++x) >= g[k].size()) continue;
                dp[g[k][x]][j | (1 << (k - 1))] = Max(dp[g[k][x]][j | (1 << (k - 1))], dp[i][j] + 1);
            }
        }
        ++cur[a[i]];
    }
    int ans = -1;
    for(int i = 1; i <= n; i++)
        ans = Max(ans, dp[i][(1 << 8) - 1]);
    if(ans == -1) return -1;
    return ans * (len + 1) + (8 - ans) * len;
}

void Solve()
{
	int l = 1, r = n / 8, mid;
    while(l + 1 < r)
    {
        mid = (l + r) >> 1;
        if(check(mid) != -1) l = mid;
        else r = mid - 1;
    }
    int ans = Max(check(l), check(r));
    if(ans == -1)
    {
        ans = 0;
        for(int i = 1; i <= 8; i++)
            if(g[i].size()) ans++;
    }
    printf("%d\n", ans);
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        g[a[i]].push_back(i);
    }
    Solve();

    return 0;
}
```

---

## 作者：clockwhite (赞：1)

# [CF743E] Vladik and cards

## 一.前言

​	把子序列看成子串还真是对不起了。[题目链接](https://www.luogu.com.cn/problem/CF743E)

## 二.思路

​	首先由每两个数字出现的次数之差不超过1可以知道，以下几点。对于一个可以记入答案的序列，有

- 所有的数字都在里面（除非部分数字只选一个，其余不选）
- 所有出现的数字的出现次数之中有一个最小值 k
- 有部分数字的出现次数为 k+1

然后我们试着看一看k和答案的关系，假如设 **add 为出现次数为 k+1 的数字个数**，那么很显然的有 $ans=8*k+add$.并且有 ans和k成**正相关的**关系。

​	有了以上的结论之后，我们可以**二分猜k**,然后试图计算出在完成每个数字至少出现k个的标准时，add的值。若是无法达到标准，那么就将k下调，否则上升。

​	现在只需要解决如何求add的问题。这里使用状压DP，**$f[x][j]$表示在x的位置 j 所代表的数字都已经出现至少 k 次的add。然后需要一个辅助变量，$pos[x][i]$表示序列中第 i 个 x 的位置**。这里用了一小点贪心的思想，即如果我们要选一些相同的数出来，那么这些**数肯定是靠的越近越好**，这样才能为后面的DP提供更多的机会。

​	那么转移方程可以比较清楚的推出，这里写不清楚，还是看代码会比较容易。需要注意的是，每次进行转移的时候，我们是先选出状态以外的一个数 p，然后得**出这个 p 之后第 k-1 的 p的位置**，转移到那上面去。（这样**总共就有k个p**），然后如果后面**还剩的有 k 个 p（即总可塞入的有k+1个）**那么也转移一下。

​	如何得到之后第 k-1 个 p 的位置是依靠于pos数组，但是每次**不可能从$pos[p][1]$ 开始往后面算**，那么再用一个 start 数组表示应该是从 $pos[p][start[p]]$ 开始找 k-1 个，即求出 $pos[p][start[p]+k-1]$，**注意$start$随着i而变化**。

​	最后初始化$f[0][0]=0$就可以轻松解决掉这道题啦！

## 三.CODE

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<fstream>
#include<cmath>
#include<cstring>
using namespace std;
int read(){
	char ch=getchar();
	int res=0,f=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())res=res*10+(ch-'0');
	return res*f;
}
const int MAXN=(1<<8)-1;
int n,a[1005],t[9],pos[9][1005],r=1<<15,l;
int start[9],f[1005][MAXN+5],ans;
inline int maxx(int x,int y){
	return x>y?x:y;
}
bool check(int x){
	for(int i=1;i<=8;++i)start[i]=1;//初始化
	memset(f,250,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<n;++i){
		for(int j=0;j<MAXN;++j)
		if(f[i][j]>=0)//用它去更新
			for(int k=1;k<=8;++k){//选一个数
				if(j&(1<<(k-1)))continue;
				int u=start[k]+x-1,g=j|(1<<(k-1));
				if(u<=t[k])f[pos[k][u]][g]=maxx(f[pos[k][u]][g],f[i][j]);
				if(++u<=t[k])f[pos[k][u]][g]=maxx(f[pos[k][u]][g],f[i][j]+1);//可以选出x+1个
			}
		++start[a[i]];//更新，每次选的数都要在i及其以后
	}
	int add=-1;
	for(int i=8;i<=n;++i)add=maxx(add,f[i][MAXN]);//前7个不可能有答案
	if(add==-1)return 0;
	ans=maxx(ans,8*x+add);
	return 1;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		pos[a[i]][++t[a[i]]]=i;//记录位置
	}
	for(int i=1;i<=8;++i)r=min(r,t[i]);
	if(r==0){//特判是否有数字没有，那么就是括号内的特殊情况
		int res=0;
		for(int i=1;i<=8;++i)if(t[i])res++;
		cout<<res;
		return 0;
	}
	while(l<=r){//二分猜k
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1;
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：kkkk0369 (赞：1)

[题解传送门](https://blog.csdn.net/qq_41034353/article/details/81735458)

具体就看题解吧。

下面直接贴代码#_#

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define INF 0x3f3f3f3f
using namespace std;
int n,L,R,ans;
int a[1010],ct[1010];
int f[1010][1<<8];
vector <int> rec[1010];
int check(int x)//判断M是否合法 
{
	memset(ct,0,sizeof(ct));
	for(int i=0;i<=n;i++)
	for(int j=1;j<(1<<8);j++) f[i][j]=-INF;
	f[0][0]=0;//初始化 
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<8);j++)
		if (f[i][j]!=-INF)
		for(int k=0;k<8;k++)
		if ((j&(1<<k))==0)
		{
			int h=x+ct[k]-1;
			if (h>=rec[k].size()) continue;//判断h是否存在 
			f[rec[k][h]+1][j|(1<<k)]=max(f[rec[k][h]+1][j|(1<<k)],f[i][j]);
			h++;
			if (h>=rec[k].size()) continue;
			f[rec[k][h]+1][j|(1<<k)]=max(f[rec[k][h]+1][j|(1<<k)],f[i][j]+1);//DP，详见题解					
		}
		ct[a[i+1]-1]++;//出现次数+1 
	}
	int cnt=-INF;
	for(int i=0;i<=n;i++) cnt=max(cnt,f[i][(1<<8)-1]);
	return cnt==-INF?-1:x*8+cnt;//找最优解 
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) rec[a[i]-1].push_back(i-1);//存储数字i出现的位置 
	L=1;R=n>>3;
	while(L<=R)//二分答案 
	{
		int M=(L+R)>>1;
		if (check(M)!=-1) ans=max(ans,check(M)),L=M+1;//M合法，保存其值并去除非最优解 
		else R=M-1;//M不合法，去除M及M以上的不合法解 
	}
	if (ans==0) for(int i=0;i<8;i++) if (rec[i].size()) ans++;//讨论x=0的情况 
	printf("%d",ans);
	/*for(int i=1;i<=n;i++)
	for(int j=1;j<(1<<8);j++) printf("%d ",f[i][j]);*/
	return 0;
}
```

---

## 作者：Others (赞：0)

考试时看到两个条件第一个想到的是状压 dp，状压很容易想，但 dp 很。

先考虑 zqw 大佬的记忆化搜索，但是算算空间 $1000\times1000\times2^8B$ 大概是 $400$ 多兆的样子，只好不用搜索。

然后想到 dp 可以滚动，但是这题选子序列而且相同数字必须相邻，所以无法滚动，然后就是舍弃 dp。

其实我做到这里已经快放弃了.....

然后思考哪一维可以省掉，滚动不行了，没有顺序，所以每个状态肯定要枚举到，所以只剩数量了，这里的数量总共只有两个（$mid,mid+1$），所以我们考虑二分，在 $check()$ 函数里 dp 就行了，空间时间相平衡 qwq。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline ll max(const ll &x,const ll &y){return x>y?x:y;}
inline ll min(const ll &x,const ll &y){return x<y?x:y;}
void qr(ll &x){
	bool f=x=0;
	char c=getchar();
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x=f?~(x-1):x;
	return ;
}
ll dp[1005][256],n,lst[1005],a[1005],pos[15];
ll check(ll x){//[x,x+1]
	memset(dp,128,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<8);j++) dp[i][j]=dp[i-1][j];
		int id=i;
		for(int j=1;j<x;j++) id=lst[id];
		if(!id) continue;
		for(int j=0;j<(1<<8);j++) if(j&(1<<a[i]-1)) dp[i][j]=max(dp[i][j],max(dp[id-1][j^1<<a[i]-1]+x,lst[id]?dp[lst[id]-1][j^1<<a[i]-1]+x+1:-1919810114514));
	}
	if(dp[n][(1<<8)-1]<0) return -1;
	return dp[n][(1<<8)-1];
}
int main() {
//	freopen("subsequence.in","r",stdin);
//	freopen("subsequence.out","w",stdout);
	qr(n);
	for(int i=1;i<=n;i++) {
		qr(a[i]);
		lst[i]=pos[a[i]],pos[a[i]]=i;
	}
	for(int i=1;i<=8;i++) {
		if(!pos[i]){
			int tot=0;
			for(int j=1;j<=8;j++) tot+=!!pos[j];
			printf("%d",tot);
			return 0;
		}
	}
	ll l=0,r=(n+7)/8,mid;
	while(r-l>1){
		mid=l+r>>1;
		if(~check(mid)) l=mid;
		else r=mid-1;
	}
	if(~check(r)) printf("%lld",check(r));
	else printf("%lld",check(l));
//	for(int i=1;i<=n;i++)
//		for(int j=0;j<(1<<8);j++) if(dp[i][j]>=0) printf("dp[%d][%d]=%lld\n",i,j,dp[i][j]);
	return 0;
}
```

---

## 作者：TulipeNoire (赞：0)

### 思路

这个题用状压显而易见，但是时间复杂度可能需要卡一卡。

我们先枚举每种元素选择数量区间 $k\sim k+1$。这里就有一个卡常的空间，因为其实 $k$ 枚举到 $\frac{n}{8}$ 就可以了，再大没必要了。

然后就是正常状压dp了。定义 $dp_{i,j}$ 表示到第 $i$ 个元素，$j$ 为 $8$ 种元素的出现状态。那么此时转移就很好转移了。我们记录每个元素往前延伸的数量，就不用在状态转移的时候暴力了。但要注意细节。详见注释。

复杂度：$O(\frac{n}{8}\times n\times 2^8)=O(n^2\times2^5)$，显然可过。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,a[N],lst[N][N],tot,ans;
int dp[N][1<<8];
int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    for (int i=1;i<=n;i++) {
        int sum=0;
        for (int j=i;j>=1;j--) {
            if (a[i]==a[j]) lst[i][++sum]=j;
        }
    }
    memset(dp[0],192,sizeof dp[0]);//排除不合法的答案
    for (tot=0;tot<=n/8;tot++) {
        for (int i=0;i<=n;i++) dp[i][0]=0;
        for (int i=1;i<=n;i++) {
            for (int j=0;j<1<<8;j++) {
                dp[i][j]=dp[i-1][j];//不选这个
                if (!tot) {
                    if (j&(1<<a[i]-1)) dp[i][j]=dp[i-1][j^(1<<a[i]-1)]+1;
                    for (int k=1;k<=8;k++) {
                        if ((j&(1<<k-1))==0) continue;
                        dp[i][j]=max(max(dp[i][j^(1<<k-1)],dp[i-1][j^(1<<k-1)]),dp[i][j]);
                    }
                } else {
                    int k=a[i];
                    if ((j&(1<<k-1))==0) continue;
                    if (!lst[i][tot]) continue;
                    dp[i][j]=max(dp[i][j],dp[lst[i][tot]-1][j^(1<<k-1)]+tot);
                    if (!lst[i][tot+1]) continue;
                    dp[i][j]=max(dp[i][j],dp[lst[i][tot+1]-1][j^(1<<k-1)]+tot+1);
                }
            }
        }
        for (int i=1;i<=n;i++) {
            ans=max(ans,dp[i][(1<<8)-1]);
        }//答案不一定是最后一个
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Durancer (赞：0)

### 前置知识

- 二分答案

- 状压DP

### 思路

一看这种题目并没有什么很奇妙的思路，我们考虑用二分答案的方法来解决。

首先二分的肯定是最小的一个数字的连续段的长度，此时的一个连续段要么 $len$，要么 $len+1$。

设 $f_{i,j}$ 表示前 $i$ 个数，选择的数字的连续段的状态为 $j$ 的多出来的长度。

我们考虑每次枚举完一个地方的时候，记录一下这个数的前驱长度，以便于下一次进行计算。

下一次的合法长度的终点为第 $cur_k+len-1$ 个 $k$ 所在的位置，当判断一下此时的长度合法时，就更新。

```cpp
f[g[k][x]][s|(1<<(k-1))]=max(f[g[k][x]][s|(1<<(k-1))],f[i][s]);
				
```

并且考虑判断下一个 $k$ 的位置，如果还是合法，那么就可以考虑加上 $1$ ,因为多出来一块了 $\text{qwq}$。

```cpp
f[g[k][x]][s|(1<<(k-1))]=max(f[g[k][x]][s|(1<<(k-1))],f[i][s]+1); 
			
```
最后就是一种特殊情况了，没有出现所有的 $[1,8]$ 内的数，那么最多每一个数选择一个，判断那些数存在，输出存在的数的种类就行了。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
using namespace std;
const int N=1e3+9;
const int M=1e3+9;
const int K=(1<<8)+9;
int n,a[N];
int ans;
int f[N][K];
int cur[N];
int l,r;
vector<int> g[9];
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
int check(int len)
{
	memset(f,-1,sizeof(f));
	memset(cur,0,sizeof(cur));
	f[0][0]=0;
	for(int i=0;i<n;i++)
	{
		for(int k=1;k<=8;k++)
		{
			for(int s=0;s<(1<<8);s++)
			{
				int x=cur[k]+len-1;//表示当前出现的位置
				if(s&(1<<(k-1))) continue;
				if(f[i][s]==-1) 
					continue; 
				if(x>=g[k].size()) 
					continue;//办不了了
				f[g[k][x]][s|(1<<(k-1))]=max(f[g[k][x]][s|(1<<(k-1))],f[i][s]);
				x++;
				if(x>=g[k].size()) 
					continue;
				f[g[k][x]][s|(1<<(k-1))]=max(f[g[k][x]][s|(1<<(k-1))],f[i][s]+1); 
			}		 
		}
		cur[a[i]]++;//记录一下所有前驱的位置 
	}
	int ans=-1;
	for(int i=1;i<=n;i++)
		ans=max(ans,f[i][(1<<8)-1]);
	if(ans==-1) return -1;
	else return 8*len+ans;
}
int Get_ans()
{
	int Fir=check(l);
	int Sec=check(r);
	int ans=max(Fir,Sec);
	if(ans!=-1)
		return ans;
	ans=0;
	for(int i=1;i<=8;i++)
		if(g[i].size()!=0)
			ans++;
	return ans;//如果不足 8 个的话，那么就木拉木拉 
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		g[a[i]].push_back(i);//记录每一个的位置 
	}
	l=1; r=n/8;
	while(l<r-1)
	{
		int mid=(l+r)>>1;
		if(check(mid)!=-1)
			l=mid;
		else r=mid-1;	
	}	
	printf("%d\n",Get_ans()); 
	return 0;
}

```


---

## 作者：Celtic (赞：0)

题意：题面描述的很清晰了。

题解：

二分答案。

因为每种数字只能有 $k$ 或 $k+1$ 个，所以二分这个 $k$ ，显然 $k$ 越大，答案越大。

考虑怎么判断是否可行。


看到每种数字必须连续，我们就找到了入手点。

首先考虑一个贪心就是每种数字都要取连续的一段。

比如 $1,1,2,1,3,4,5,6,7,8$

这个情况下，显然可以取两个 $1$ ,剩下的都取一个，答案为 $9$。

但是如果我们取第一个和第三个 $1$ ，也就是这个 $2$ 相当于被我们“浪费”掉了，此时方案不可行。

于是为了让“浪费”的数字数尽量少，同种数字应该取连续的一段。

然后因为每种数字都小于 $8$ ，容易想到状压。

设$dp_{i,s}$表示当前到第 $i$ 个数，前面的数字状态为 $s$ 的方案数。

然后枚举转移，也就是枚举 $j$ ，在状态中加入这个 $j$。

当然如果状态中已经有 $j$ 了就直接`continue`。

考虑新的状态应该到第几个数字。

我们把每种数字出现的位置存到 $vecter$ 里。

记 $now_i$ 表示 $i$ 这个数字已经到了第几个位置。

每次枚举完 $i$ 之后就 $now_{a_i}++$ 。

所以新的位置就是 $v[j][now[j]+k-1]$ 。

状态转移方程

然后状态转移方程就很好写出了，在代码中。

当然还有另一种情况，就是选$k+1$个数。

此时的位置就是 $v[j][now[j]+k]$ 。

同样的方法来处理。

代码

```cpp
#include<bits/stdc++.h>
#define N 2001001
#define MAX 2001
#define re register
using namespace std;
typedef long long ll;
typedef double db;
const ll mod=1000000007; 
inline void read(re ll &ret)
{
    ret=0;re char c=getchar();re bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,a[N],l,r,mid,tmp,now[10],dp[1200][267];
vector<ll>v[10];
inline ll check(re ll k)
{
    if(!k)
        return -1;
    re ll maxn=(1<<8)-1;
    memset(now,0,sizeof(now));
    memset(dp,-1,sizeof(dp));
    for(re int i=1;i<=n;i++)
        dp[i][0]=0;
    for(re int i=1;i<=n;i++)
    {
        for(re int s=0;s<=maxn;s++)
            if(dp[i][s]!=-1)
            {
                for(re int j=1;j<=8;j++)
                {
               //     cout<<i<<" "<<s<<" "<<j<<endl;
                    if((s>>(j-1))&1)
                        continue;
                    re ll cur=now[j]+k-1;
                    if(cur>=v[j].size())
                        continue;
                    dp[v[j][cur]][s^(1<<j-1)]=max(dp[v[j][cur]][s^(1<<j-1)],dp[i][s]);
                    if((++cur)>=v[j].size())
                        continue;
                    dp[v[j][cur]][s^(1<<j-1)]=max(dp[v[j][cur]][s^(1<<j-1)],dp[i][s]+1);
                //    cout<<i<<" "<<s<<" "<<j<<endl;
                }
            }
        now[a[i]]++;
    }
    re ll ret=-1;
    for(re int i=1;i<=n;i++)
        ret=max(ret,dp[i][maxn]);
    if(ret==-1)
        return -1;
    return ret*(k+1)+(8-ret)*k;
}
signed main()
{
    read(n);
    for(re int i=1;i<=n;i++)
        read(a[i]),v[a[i]].push_back(i);
    l=1,r=n/8;
    while(l+1<r)
    {
        mid=l+r>>1;
        if(check(mid)!=-1)
            l=mid;
        else
            r=mid-1;
    }
    tmp=max(check(l),check(r));
    if(tmp==-1)
    {
        tmp=0;
        for(re int i=1;i<=8;i++)
            if(v[i].size())
                tmp++;
    }
        
    printf("%lld\n",tmp);
    #ifdef WIN32
    system("pause");
    #endif
	exit(0);
}

```


---

