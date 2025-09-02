# Packmen Strike Back

## 题目描述

Game field is represented by a line of $ n $ square cells. In some cells there are packmen, in some cells there are asterisks and the rest of the cells are empty. Packmen eat asterisks.

Before the game starts you can choose a movement direction, left or right, for each packman. Once the game begins all the packmen simultaneously start moving according their directions. A packman can't change the given direction.

Once a packman enters a cell containing an asterisk, packman immediately eats the asterisk. Once the packman leaves the cell it becomes empty. Each packman moves at speed 1 cell per second. If a packman enters a border cell, the packman stops. Packmen do not interfere with the movement of other packmen; in one cell there can be any number of packmen moving in any directions.

Your task is to assign a direction to each packman so that they eat the maximal number of asterisks. If there are multiple ways to assign directions to eat the maximal number of asterisks, you should choose the way which minimizes the time to do that.

## 说明/提示

In the first example the leftmost packman should move to the right, the rightmost packman should move to the left. All the asterisks will be eaten, the last asterisk will be eaten after 4 seconds.

## 样例 #1

### 输入

```
6
*.P*P*
```

### 输出

```
3 4
```

## 样例 #2

### 输入

```
8
*...P..*
```

### 输出

```
1 3
```

# 题解

## 作者：犇犇犇犇 (赞：6)

[题目链接](https://www.luogu.com.cn/problem/CF883D)

有两个问题，第一个问题满足吃到的豆子数目最多，第二个问题保证所用时间最短。  

首先我们求出能吃到最多的豆子。  

如果只有一只吃豆人，那么它要么往左走，要么往又走，**直接求出往两个方分别能吃到的豆子数和所需时间。吃到的豆子数直接取** $\max$ 就行了。

```
if(num==1) //num表示吃豆人数量
	{
		int f=0,num1=0,num2=0,t1=n,t2=0; 
        //num1:左侧豆子数 num2:右侧豆子数
        //t1:左侧第一个豆子位置 t2:右侧最后一个豆子位置
		for(int i=1;i<=n;i++)
		{
			if(a[i]==2)
				f=i; 
			else if(a[i]==1) 
			{
				if(f==0) //当前在左侧
				{
					num1++;
					t1=min(t1,i);
				}
				else //当前在右侧
				{
					num2++;
					t2=max(t2,i);
				}
			}
		}
		if(num1>num2) //左边多,时间为吃豆人到第一个豆子的时间
			cout<<num1<<" "<<f-t1<<endl;
		else if(num1<num2) //同上
			cout<<num2<<" "<<t2-f<<endl;
		else //两边一样多，取时间最短的
			cout<<num1<<" "<<min(f-t1,t2-f)<<endl;
		return 0;
	}
```

如果有两个及以上的吃豆人，我们可以发现我们只要任意选出两个吃豆人，左侧的那个往右边吃，右侧的往左边吃，便可以吃掉所有的豆子。**所以第一问的答案就是豆子数**。  

下面我们需要求最短的时间。  

我们可以发现如果时间限制为 $k$ 满足要求，那么时间限制为 $k+1$ 也满足要求。所以我们可以**二分最短的时间**。  

假设当前最短的时间为 $k$ 。我们需要 check 这个时间是否满足要求。  
如果当前 $1$ 到 $i-1$ 所有吃豆人的方向都已经确定，此时第 $i$ 只吃豆人，设它的位置为 $p_i$ 。那么在 $k$ 秒的时间内，它可以吃掉从 $p_i-k$ 到 $p_i$ （左走）或者 $p_i$ 到 $p_i+k$ （右走）范围内的所有豆子。  
对于 $1$ 到 $p_i-k$ 的豆子，必须由前 $i-1$ 只吃豆人吃掉。  
如果 $p_i-k$ 到 $p_i$ 之间没有豆子，即从 $1$ 到 $p_i$ 范围内的豆子已经全部吃完，则第 $i$ 只吃豆人可以直接**往右走**，以吃掉更多的豆子。  
对于 $p_i-k$ 到 $p_i$ 的所有豆子，它可以由**第 $i$ 只吃豆人向左走**吃掉，也可以由**第 $i-1$ 只吃豆人向右走**吃掉。因为第 $i-1$ 只往右可以比 $i-2$ 只往右走吃掉更多的豆子，所以我们只需要考虑 $i-1$ 只往右就行了。 

所以一共有 $3$ 种情况：  

1. 第 $i$ 只朝右（$p_i-k$ 到 $p_i$ 之间没有豆子）
2. 第 $i$ 只朝左（第 $i$ 只往左吃掉 $p_i-k$ 到 $p_i$ 之间的豆子)
3. 第 $i-1$ 只朝右且第 $i$ 只朝左 （第 $i-1$ 只往右吃掉 $p_i-k$ 到 $p_i$ 之间的豆子）

对于这 $3$ 种情况，可以直接用一个 dp 来实现。$dp[i]$ 表示前 $i$ 个吃豆人能吃到的从最右边的豆子。也就是 $dp[i] = j$ 表示前 $i$ 个吃豆人最多可以吃掉 $1$ 到 $j$ 范围内的所有豆子。

我们假设 $b[i]$ 表示从 $1$ 到 $i$ 一共又多少豆子。即如果 $b[i]=b[j]$，表示从 $i+1$ 到  $j$ 没有豆子。$p[i]$ 表示第 $i$ 只吃豆人的位置。$d[i]$ 表示从 $1$ 到 $i$ 一共有多少吃豆人，即一共有 $d[n]$ 只吃豆人。这些可以用前缀和 $O(n)$ 预处理。

第一种:  
如果 $dp[i-1]$ 到 $p_i$ 范围内没有豆子，那么此时它可以直接往右走。 

```cpp
if(dp[i-1]>=p[i]-1 || b[dp[i-1]]==b[p[i]-1])
			dp[i]=max(dp[i],p[i]+k);
```

第二种：
如果 $dp[i-1]$ 到 $p_i$ 范围内有豆子。让第 $i$ 只往左吃掉 $p[i]-k$ 到 $p[i]$的豆子。

```cpp
if(dp[i-1]>=p[i]-k-1 || b[dp[i-1]]==b[p[i]-k-1])
			dp[i]=max(dp[i],p[i]);
```

第三种：  

第 $i-1$ 只朝右且第 $i$ 只朝左 ，第 $i-1$ 只往右吃掉 $p[i-1]$ 到 $p[i-1]+k$ 之间的豆子，第 $i$ 只往左吃掉 $p[i]-k$ 到 $p[i]$ 的豆子。此时由于第 $i-1$ 只不能往左吃掉豆子，$dp[i-2]$ 到 $p[i]-k-1$ 之间的豆子没法被第 $i-1$ 只吃掉，必须没有豆子。
```cpp
if(i>1 && (dp[i-2]>=p[i]-k+1 || b[dp[i-2]]==b[p[i]-k-1]))
			dp[i]=max(dp[i],p[i-1]+k);
```

如果最后一只狗吃到的豆子 $dp[d[n]]$ 到 $n$ 之间没有豆子，那么满足要求，否则不满足要求。

check 的代码。  

```
bool check(int k) 
{ 
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=d[n];i++)
	{
		if(dp[i-1]>=p[i]-1 || b[dp[i-1]]==b[p[i]-1])
			dp[i]=max(dp[i],p[i]+k);
		if(dp[i-1]>=p[i]-k-1 || b[dp[i-1]]==b[p[i]-k-1])
			dp[i]=max(dp[i],p[i]);
		if(i>1 && (dp[i-2]>=p[i]-k+1 || b[dp[i-2]]==b[p[i]-k-1]))
			dp[i]=max(dp[i],p[i-1]+k);
		dp[i]=min(dp[i],n); //p[i]+k可能超过n，防止下标越界。
	}
	if(b[dp[d[n]]]==b[n])
		return 1;
	else return 0;
}
```


完整代码：  
```
#include <bits/stdc++.h>
const int MAXN = 1e6+5;
using namespace std;
int n,a[MAXN],num,d[MAXN],b[MAXN];
int p[MAXN],dp[MAXN];
string s;
bool check(int k) 
{ 
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=d[n];i++)
	{
		if(dp[i-1]>=p[i]-1 || b[dp[i-1]]==b[p[i]-1])
			dp[i]=max(dp[i],p[i]+k);
		if(dp[i-1]>=p[i]-k-1 || b[dp[i-1]]==b[p[i]-k-1])
			dp[i]=max(dp[i],p[i]);
		if(i>1 && (dp[i-2]>=p[i]-k+1 || b[dp[i-2]]==b[p[i]-k-1]))
			dp[i]=max(dp[i],p[i-1]+k);
		dp[i]=min(dp[i],n);
	}
	if(b[dp[d[n]]]==b[n])
		return 1;
	else return 0;
}
int main()
{
	cin>>n>>s;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='.')
			a[i+1]=0;
		else if(s[i]=='*')
			a[i+1]=1;
		else
		{
			a[i+1]=2;
			num++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==2)
		{
			d[i]=d[i-1]+1;
			p[d[i]]=i;
		}
		else
			d[i]=d[i-1];
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==1)	
			b[i]=b[i-1]+1;
		else
			b[i]=b[i-1];
	}
	if(num==1)
	{
		int f=0,num1=0,num2=0,t1=n,t2=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]==2)
				f=i;
			else if(a[i]==1)
			{
				if(f==0)
				{
					num1++;
					t1=min(t1,i);
				}
				else 
				{
					num2++;
					t2=max(t2,i);
				}
			}
		}
		if(num1>num2)
			cout<<num1<<" "<<f-t1<<endl;
		else if(num1<num2)
			cout<<num2<<" "<<t2-f<<endl;
		else 
			cout<<num1<<" "<<min(f-t1,t2-f)<<endl;
		return 0;
	}
	int l=1,r=n,ans=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			r=mid-1;
			ans=mid;
		}
		else
			l=mid+1;
	}
	cout<<b[n]<<" "<<ans<<endl;
	return 0;
}
```


---

## 作者：wsyhb (赞：4)

## 前言

强烈谴责某题解！某题解只写转移方程，不写转移条件……

## 题解

首先，样例一提示我们：当吃豆人个数 $\ge 2$ 时，一定可以把所有豆子吃完。（右侧的向左，左侧的向右即可）

于是先**特判吃豆人个数 $=1$ 的情况**：左侧豆子多就向左走，右侧豆子多就向右走，如果两侧一样多就把时间取个 $\min$。

接着**考虑吃豆人个数 $\ge 2$ 时，如何求最小时间**。

容易发现这东西不能贪心且很难构造，于是考虑 **DP**。

直接 DP 似乎也做不了——把 DP 值设定为最小时间会有后效性。（样例一就是一个很好的例子）

但是我们注意到，所吃豆子数量随时间增加是单调不降的，这意味着我们可以二分答案（即最小时间）。

**二分答案的好处在于，check 时只需考虑如何把所有豆子吃完，而无需考虑如何最小化时间。**

------------

具体地，设共有 $k$ 个吃豆人，从左到右位置依次为 $p_1,p_2,\cdots,p_k$。

**设 $f_i$ 表示考虑前 $i$ 个吃豆人后，能覆盖到的最右位置**（即 $1$ 到 $f_i$ 的豆子全部被吃掉）。

另外设当前二分的值为 $x$（即当前要 check 的值为 $x$）。

则有以下几种情况：

1. $i$ 号吃豆人向左，且 $i-1$ 号吃豆人向右。

	- 条件：区间 $(f_{i-2},\min\{p_{i-1},p_i-x\})$ 和 $(p_{i-1}+x,p_i-x)$ 中没有豆子。

	- 转移：$max(p_i,p_{i-1}+x) \to f_i$。（$y \to x$ 表示令 $x =\max(x,y)$，下同）

1. $i$ 号吃豆人向左，且 $i-1$ 号吃豆人向左。

	- 条件：区间 $(f_{i-1},p_i-x)$ 中没有豆子。

	- 转移：$p_i \to f_i$。

	- Q1：上述条件为什么可以保证 $i-1$ 号吃豆人向左？$f_{i-1}$ 并没有限定 $i-1$ 的方向啊。

	- A1：事实上，**上述条件的确不能保证 $i-1$ 号吃豆人向左**。但若满足第二种情况的条件，且 $f_{i-1}$ 记录的是 $i-1$ 号吃豆人向右的情况，则第一种情况的条件必定满足（即会进行第一种转移），因此**该转移仍是正确的**。

	- Q2：为什么不考虑 $i-1$ 号左边的吃豆人向右对 $f_i$ 的贡献？

	- A2：（在本情况的条件下）设存在 $k<i-1$ 满足 $k$ 号吃豆人向右。若其对 $f_i$ 有贡献，则 $p_k+x>p_i$，移项得 $p_i-x<p_k$。那么令 $k$ 号吃豆人向左，$i-1$ 号吃豆人向右，其余的不变，也是合法的——即存在第一种转移。而第一种转移中的 $p_{i-1}+x$ 显然比 $p_k+x$ 要优，因此无需考虑 $p_k+x$。

1. $i$ 号吃豆人向右。

	- 条件：区间 $(f_{i-1},p_i)$ 中没有豆子。

	- 转移：$p_i+x \to f_i$。

	- 说明：$i$ 号左边的吃豆人向左或向右都不会对 $f_i$ 产生贡献，故无需讨论。

若区间 $(f_k,n]$ 中没有豆子，则说明 $x$ 合法，否则 $x$ 不合法。

判断区间 $[l,r]$ 中是否有豆子的方法：先判断区间是否为空（即 $l>r$），若不为空则用**前缀和**作差进行判断。

至此问题已解决，总时间复杂度 $O(n\log{n})$。

------------

P.S.

顺带说一句，cz 题解代码中“$i$ 号吃豆人向左，且 $i-1$ 号吃豆人向右”这一情况的条件为“区间 $(f_{i-2},p_i-x)$ 中没有豆子”，也是正确的，原因如下：

若 $p_{i-1}+x>p_i$，则 $p_{i-1}>p_i-x$，此时该种情况的条件就可以简化成这样。而其代码考虑了用 $p_i$ 更新 $f_i$，因此是正确的。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int max_n=1e6+5;
char Map[max_n];
int sum[max_n];
inline bool check_empty(int l,int r)
{
	return l>r||sum[r]==sum[l-1];
}
int cnt_P,p[max_n],f[max_n];
inline bool check(int x)
{
	for(int i=1;i<=cnt_P;++i)
	{
		f[i]=0;
		// to left
		if(i>1&&check_empty(f[i-2]+1,min(p[i-1],p[i]-x)-1)&&check_empty(p[i-1]+x+1,p[i]-x-1))
			f[i]=max(p[i],p[i-1]+x);
		else if(check_empty(f[i-1]+1,p[i]-x-1))
			f[i]=p[i];
		// to right
		if(check_empty(f[i-1]+1,p[i]-1))
			f[i]=p[i]+x;
	}
	return check_empty(f[cnt_P]+1,n);
}
int main()
{
	scanf("%d%s",&n,Map+1);
	for(int i=1;i<=n;++i)
	{
		sum[i]=sum[i-1]+(Map[i]=='*');
		if(Map[i]=='P')
			p[++cnt_P]=i;
	}
	assert(cnt_P>=1);
	if(cnt_P==1)
	{
		int pos=p[1];
		int ans1=max(sum[pos-1],sum[n]-sum[pos]);
		assert(ans1>0);
		int ans2=1e9;
		if(sum[pos-1]==ans1)
		{
			for(int i=1;i<=pos-1;++i)
			{
				if(Map[i]=='*')
				{
					ans2=min(ans2,pos-i);
					break;
				}
			}
		}
		if(sum[n]-sum[pos]==ans1)
		{
			for(int i=n;i>=pos+1;--i)
			{
				if(Map[i]=='*')
				{
					ans2=min(ans2,i-pos);
					break;
				}
			}
		}
		printf("%d %d\n",ans1,ans2);
		return 0;
	}
	int L=1,R=n-1,res=n-1;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(check(mid))
			res=mid,R=mid-1;
		else
			L=mid+1;
	}
	printf("%d %d\n",sum[n],res);
	return 0;
}
```

---

## 作者：xzy090626 (赞：1)

真是一道好题。做完之后会对整体的做题思路有很大的启发。

首先先考虑第一问，很明显有 $\geq 2$ 的吃豆人时一定可以吃完所有的豆子；否则，答案就是唯一的吃豆人向左和向右的较大值。

但是此时我们会感到无从下手。鉴于 $n\le10^6$，我们一般只会考虑贪心地构造某种策略，但是这似乎不可行。

可以从答案出发，考虑最终的时间具有哪些性质。发现时间限制满足单调性，也就是说任意 $t^{\prime}$ 满足 $t^{\prime} \geq$ 最终答案 $t$，都能使吃豆人吃完所有豆子。

于是我们考虑二分这个 $t$。那么原问题就被转化成了当前 $t$ 的合法性判定问题，而 $t$ 可以为我们确定每个吃豆人的覆盖范围。

---
我们尝试从左到右地处理这些吃豆人。如果当前处理到了第 $i$ 个吃豆人，而且前 $i-1$ 个吃豆人吃掉了 $[1,x]$ 中所有的豆子，那么一个明显的状态设计呼之欲出了：设 $f(i)$ 表示前 $i$ 个吃豆人最大能覆盖 $[1,f(i)]$ 的区间。

状态有了，考虑如何转移。这个时候 $t$ 就起到了作用。我们设 $p_i$ 为第 $i$ 个吃豆人的初始位置，那么它能覆盖的空间就是 $[p_i-t,p_i+t]$，设 $w(l,r)$ 为 $[l,r]$ 区间内的豆子个数。

为了方便，我们设 $dp_{i,0}$ 为向左走，$dp_{i,1}$ 为向右走，结合这个 `check` 函数的代码细节来看转移过程。

```cpp
int w[N],n;//豆子个数的前缀和
int bg,ed;//第一个和最后一个豆子的下标
int p[N],num;//代表吃豆人下标
int W(int l,int r){//代表区间内豆子个数
	if(l>r) return 0;
	l = max(l,1);r = min(r,N-5);
	return (w[r]-w[l-1]);
}
int dp[N][2];// dp[i][0] 代表向左，dp[i][1] 代表向右
bool check(int tm){//二分的时间
	memset(dp,0,sizeof dp);
	for(int i=1;i<=num;++i){
		if(W(dp[i-1][0]+1,p[i]-tm-1)==0) dp[i][0] = max(dp[i][0],p[i]);
		if(W(dp[i-1][1]+1,p[i]-tm-1)==0) dp[i][0] = max(dp[i][0],p[i]);
      //先处理向左的情况
		if(W(max(dp[i-1][0],dp[i-1][1])+1,p[i]-1)==0) dp[i][1] = p[i]+tm;
      //处理向右的情况
		dp[i][1] = max(dp[i][1],max(dp[i-1][0],dp[i-1][1]));
		dp[i][0] = max(dp[i][0],max(dp[i-1][0],dp[i-1][1]));
      //继承前面的范围
		if(i>1 && W(dp[i-1][1]+1,p[i]-tm-1)==0) dp[i][0] = max(dp[i][0],p[i-1]+tm);//处理 i-1 向右，i 向左的情况
	}
	return max(dp[num][0],dp[num][1])>=ed;
}
```

---
剩下的代码。
```cpp
signed main(){
	cin>>n>>(s+1);
	for(int i=1;i<=n;++i){
		w[i] = w[i-1];
		if(s[i]=='*'){
			w[i]++,ed = i;
			if(w[i]==1) bg = i;
		}
		if(s[i]=='P') p[++num] = i;
	}
	if(num==1){
		if(W(1,p[1])>W(p[1],n) || (W(1,p[1])==W(p[1],n) && p[1]-bg<ed-p[1])) cout<<W(1,p[1])<<' '<<p[1]-bg;
		else cout<<W(p[1],n)<<' '<<ed-p[1];
		return 0;
	}
	cout<<w[n]<<' ';
	int l = 0,r = n-1,ans = n-1;
	while(l<=r){
		int mid = (l+r)/2;
		if(chk(mid)) ans = mid,r = mid - 1;
		else l = mid + 1;
	}
	cout<<ans;
	return 0;
}
```
写的时候注意开闭区间的边界问题，还有就是判定方案是否合法并不能完全依赖于区间范围，而要结合豆子的位置。

---
总结一下。这个题目的关键在于两个部分，一个是二分答案，从而获得每个吃豆人的活动范围，同时将问题转化为判定；一个是从前向后逐个地 dp ，巧妙状态的设计也非常关键。

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2500}$
---
### 解题思路：

首先分出只有一个吃豆人和有两个及以上的情况。

只有一个时，由于只能往一边走，吃到的豆子个数也是不确定的，直接优先选择豆子多的一侧走就行了。这种情况很简单，但也很特殊。

如果有两个或者两个以上的吃豆人，则一定能够有至少易购构造方案使得所有的豆子被吃，问题的关键变成了如何使得时间最短。

直接构造一种方案使得时间最短很复杂，但是如果只是判断一下能否在某一个时间内吃掉所有的豆子却容易，数据范围没有特别大，考虑二分时间，并由此转化到判定性问题。

转化后的问题可以抽象为：已知直线上若干个点和若干条长度已知且相等的线段的一个端点，要求确定一个覆盖方案使得所有的点在至少一条线段上。

这个问题很明显可以用动态规划解决，记 $f_i$ 表示考虑到第 $i$ 个吃豆人在吃完前面所有的豆子之后能够到达的最远位置。

转移的时候考虑最后至多两个吃豆人的状态，并从中得出是否可行。为了方便表述，记长度为 $len$，第 $i$ 个吃豆人的位置为 $p_i$。

1. 最后一个吃豆人方向向左，此时如果 $f_{i-1}$ 到 $p_{i}-len$ 之间没有任何一个星号则可以进行转移，此时的结果为 $p_i$。

2.  最后一个吃豆人的方向向右，此时需要满足 $f_{i-1}$ 到 $p_i$ 之间没有任何的星号，转移的结果为 $p_i+len$。

3. 最后一个吃豆人向左，倒数第二个吃豆人向右，这种转移有产生贡献的一个必要条件为 $p_{i-1}+len>p_i$，否则是和第一种一样的情况。转移条件为 $f_{i-2}$ 到 $min(p_{i-1},p_i-len) $ 之间没有星号，转移的结果为 $p_{i-1}+len$。

4. 平凡情况，直接从 $f_{i-1}$ 继承。

这四种情况中的最大值即为最终答案，如果中途出现了完全无法转移或者在转移到最后也不能覆盖最后的几个星号，说明问题在当前长度下无解。



---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,s[1000005],p[1000005],cnt,le,ri,l,r,mid,ans,f[10000005],res;
char c;
bool st(int l,int r){
	if(l>r)return 1;
	if(s[r]-s[l-1]<=0)return 1;
	return 0;
}
bool check(int x){
	for(int i=1;i<=cnt;i++)f[i]=0;
	for(int i=1;i<=cnt;i++){
		f[i]=f[i-1];
		if(st(f[i-1]+1,p[i]-x-1))f[i]=max(f[i],p[i]);
		if(st(f[i-1]+1,p[i]-1))f[i]=max(f[i],p[i]+x);
		if(i>=2&&st(f[i-2]+1,min(p[i-1]-1,p[i]-x-1))&&p[i-1]+x>p[i])f[i]=max(f[i],p[i-1]+x);
		if(f[i]<p[i])return 0;
	}
	if(f[cnt]<ri)return 0;
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		c=getchar();
		while(c=='\n'||c=='\r'||c==' ')c=getchar();
		if(c=='P')p[++cnt]=i;
		if(c=='*'){
			s[i]=s[i-1]+1;
			if(le==0)le=i;
			ri=i;res++;
		}
		else s[i]=s[i-1];
	}
	if(cnt==1){
		if(s[p[1]]>s[n]-s[p[1]])printf("%d %d\n",s[p[1]],p[1]-le);
		if(s[p[1]]<s[n]-s[p[1]])printf("%d %d\n",s[n]-s[p[1]],ri-p[1]);
		if(s[p[1]]==s[n]-s[p[1]])printf("%d %d\n",s[p[1]],min(p[1]-le,ri-p[1]));
		return 0;
	}
	l=0;r=n+1;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d %d",res,ans);
	return 0;
}
```


---

## 作者：NashChen (赞：1)

# 【题意】

给定一个字符串，上面有吃豆人 `'P'` 和豆子 `'*'` ，用 `'.'` 表示空地。

每个吃豆人只能往一个方向吃豆子。求能吃到的最多豆子和吃到这些豆子用的最短时间。

# 【题解】

这是一道非常好的思维题。~~还不是因为你贪心贪了一年没贪出来~~

首先，略加思考就可以发现，有两只以上的吃豆人就可以相向而行吃完所有的豆子，第一问可以直接输出豆子总数。

而一只吃豆人不一定能吃完所有的豆子，所以我们把一只吃豆人的情况拿出来特判。

然后问题就转化为两只以上的吃豆人如何耗时最短吃完所有的豆子。

做法：二分时间 $t$ ，转化为判定在时间 $t$ 内是否能吃完所有的豆子

设第 $i$ 个吃豆人的位置是 $x_i$， $f_i$ 为在吃完 $(1,x_i)$ 内的所有豆子的情况下，能够到达的最右端。

讨论第 $i$ 个吃豆人的方向

* 若前面的吃豆人能吃完 $x_i$ 之前的豆子，那么第 $i$ 个吃豆人就能向右走。

等价于若 $(f_{i-1},x_i)$ 内没有豆子，则 $f_i=x_i+t$

这里的 $(f_{i-1},x_i)$ 相当于，初始设定吃豆人向左走的第 $i$ 个吃豆人“管理”的区域，如果不需要它管，就可以直接向右走了。

* 若前面的吃豆人吃不完 $x_i$ 之前的豆子，那么第 $i$ 个吃豆人只能向左走。如果还是吃不完，就直接判定无法完成。因为第 $i$ 个吃豆人向左走有可能覆盖到 $(f_{i-2},x_{i-1})$，此时第 $i-1$ 个吃豆人就可以向右走。

因为当 $i-2$ 号能向右走时， $i-1$ 号也能向右走，而且 $i-1$ 向右走的距离肯定会更远，所以只需要讨论 $i-1$ 号向右走。

等价于若 $(f_{i-1},x_i-t)$ 内有豆子，则 `return false;`

若 $[x_i-t,x_i)$ 内有豆子，且 $(f_{i-2},x_i-t)$ 没有豆子，则 $f_i=max(f_{i-1}+t,x_i)$

若 $[x_i-t,x_i)$ 内有豆子，且 $(f_{i-2},x_i-t)$ 没有豆子，则 $f_i=x_i$

### 整理一下

---

若 $(f_{i-1},x_i-t)$ 内有豆子，则 `return false;`

若 $[x_i-t,x_i)$ 内没有豆子，则 $f_i=x_i+t$

若 $[x_i-t,x_i)$ 内有豆子，且 $(f_{i-2},x_i-t)$ 没有豆子，则 $f_i=max(f_{i-1}+t,x_i)$

若 $[x_i-t,x_i)$ 内有豆子，且 $(f_{i-2},x_i-t)$ 没有豆子，则 $f_i=x_i$

---

这些有无豆子的区间判定用前缀和维护一下，就可以通过本题了。

# 【代码】

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN= 1000005;
int N,P[MAXN],rsum[MAXN],f[MAXN],cnt,ans;
char ch;

bool sec_empty(int l,int r) {return l>r || rsum[r]==rsum[l-1];}
bool check(int t){
	for(int i=1;i<=cnt;++i) f[i]= 0;
	for(int i=1;i<=cnt;++i){
		f[i]= P[i];
		if(!sec_empty(f[i-1]+1,P[i]-t-1)) return false;
		if(sec_empty(f[i-1]+1,P[i]-1)) f[i]= P[i]+t;
		else
			if(i>=2 && sec_empty(f[i-2]+1,P[i]-t-1))
				f[i]= max(f[i],P[i-1]+t);
	}
	if(!sec_empty(f[cnt]+1,N)) return false;
	return true;
}

void binary(){
	int l=1,r=N,mid;
	while(l<r){
		mid= (l+r)>>1;
		if(check(mid)) r= mid;
		else l= mid+1;
	}
	ans= l;
	return;
}

void Input(){
	scanf("%d",&N);
	for(int i=1;i<=N;++i){
		ch= getchar();
		if(ch=='\n') ch= getchar();
		rsum[i]= rsum[i-1];
		if(ch=='*') ++rsum[i];
		if(ch=='P') P[++cnt]=i;
	}
	return;
}

int main(){
	Input();
	if(cnt==1){
		int v1= rsum[P[1]],v2= rsum[N]-rsum[P[1]];
		printf("%d %d\n",v1,v2);
		int lb= upper_bound(rsum,rsum+N,0)-rsum;
		int rb= lower_bound(rsum,rsum+N,rsum[N])-rsum;
		if(v1 == v2) printf("%d\n%d\n",v1,min(P[1]-lb,rb-P[1]));
		if(v1 > v2) printf("%d\n%d\n",1,P[1]-lb);
		if(v1 < v2) printf("%d\n%d\n",1,rb-P[1]);
		return 0;
	}
	binary();
	printf("%d\n%d\n",rsum[N],ans);
	return 0;
}
```

---

## 作者：篮网总冠军 (赞：0)

暑假题单通过的第一题，准备这个题单过的所有题都来一发题解。

令吃豆人数量为 $cnt$，豆子数量前缀和数组 $pean$，吃豆人位置 $w$。

先考虑把最简单的情况拿掉。

$cnt = 0$ 的时候，直接输出 ``0 0``。 

$cnt = 1$ 的时候，左右两边检查豆子个数，相同再比较时间即可。

好的，进入 $cnt > 1$ 的正题。

题目看到第一眼二分答案，这种时间具有单调性的题目大概率是二分答案。

但现在要考虑的是，怎么 $O(n)$ 解决 $dp$。

思维有一定难度，但是建议自己想。

假设 $dp_i$ 表示第 $1 \sim i$ 个吃豆人可以吃掉 $1 \sim dp_i$ 的豆子。

那么我们可以得出，有两种情况。

第一种：往右走。必须保证左边豆子被前 $i-1$ 个吃豆人吃完了，答案为 $w_i + t$。

第二种：往左走。必须保证可吃范围之外的均已被吃完，答案 $\max(p_i,p_{i-1}+t)$。

如两种都不行就直接返回 $0$。

令 $dou$ 为吃豆人个数，$lastp$ 为最后一粒豆的位置。

最后比较 $dp_{dou}$ 和 $lastp$ 大小判断即可。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

int n,cnt,dou;
string s;
int p[1000005];
int dp[1000005];
int pean[1000005];
int lastp;
bool check(int k){
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=dou;i++){
		if ((i-1==0?-1:dp[i-1])>=p[i]-1||(i-1==0?0:pean[dp[i-1]])==pean[p[i]]) dp[i]=max(dp[i],p[i]+k);
		if ((i-1==0?-1:dp[i-1])>=p[i]-k-1||(i-1==0?0:pean[dp[i-1]])==((p[i]-k-1>=0)?pean[p[i]-k-1]:0)) dp[i]=max(dp[i],p[i]);
		if (i>1&&((i-2==0?-1:dp[i-2])>=p[i]-k-1||(i-2==0?0:pean[dp[i-2]])==((p[i]-k-1>=0)?pean[p[i]-k-1]:0))) dp[i]=max(dp[i],p[i-1]+k);
		if (dp[i]<p[i]) return false;
	}
	if (lastp<=dp[dou]) return true;
	else return false;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++) if (s[i]=='P') cnt++;
	if (cnt==0){
		cout<<"0 0"<<endl;
	}
	else if (cnt==1){
		int c=0; 
		for(int i=0;i<n;i++){
			if (s[i]=='P') c=i;
		}
		int l1=0,g1=0,l2=0,g2=0;
		for(int i=c-1;i>=0;i--){
			if (s[i]=='*') g1++,l1=c-i;
		}
		for(int i=c+1;i<n;i++){
			if (s[i]=='*') g2++,l2=i-c;
		}
		if (g1>g2) cout<<g1<<" "<<l1<<endl;
		else if (g1<g2) cout<<g2<<" "<<l2<<endl;
		else cout<<g1<<" "<<min(l1,l2)<<endl;
	}
	else{
		for(int i=0;i<n;i++) pean[i]=(s[i]=='*')+((i-1>=0)?pean[i-1]:0);
		for(int i=0;i<n;i++) if (s[i]=='*') lastp=i;
		for(int i=0;i<n;i++) if (s[i]=='P') p[++dou]=i;
		int l=n,r=0;
		while(l>r){
			int mid=(l+r-1)/2;
			if (check(mid)) l=mid;
			else r=mid+1;
		}
		cout<<pean[n-1]<<" "<<l<<endl; 
	}
	return 0;
}

```

---

## 作者：Erica_N_Contina (赞：0)

也许并不难。

一开始我们会考虑贪心构造：

将序列分为 $4$ 类：

```C++
A: []P[]P[]
B: []p[]P
C: P[]P[]P
D: P[]P[]
```


然后要么就是 $A$，要么就是 $BCC\dots CD$。贪心策略是：对于 $A$，除了中间有一组路径交叉外，其它的 `P` 都是外向的。对于 $C$，除了中间有一组路径交叉外，其它的 `P` 都是内向的。于是贪心……发现存在 hack 数据，如下：

```C++
12
P**.*P*P*P**
```


手模后发现贪心的结果为 $4$，答案为 $3$（方向为右右左右）。

下面约定：$cnt$ 为 `P` 的个数，$pos_i$ 为第 $i$ 个 `P` 的下标，越界情况不转移。

事实上我们不应该这样考虑。正难则反，考虑将求最优值变为判定可行性。于是我们考虑二分答案，问题转换为固定长度线段全覆盖模型。即我们知道 $cnt$ 条线段的某个端点，以及线段长度均为 $t =mid$，求是否可以将所有 `*` 全覆盖。

考虑 dp，设 $f_i$ 为考虑前 $i$ 个 `P`，在覆盖了 $i$ 以前的所有 `*` 的前提下，可以覆盖到的最右端为 $f_i$。

转移如下：

- 不选（继承）：$f_i←f_{i-1}$。

- 当前 `P` 向右：$f_i←pos_i+t$，条件为 $count(f_{i-1}+1,pos_i-1)=0$。其中 $count(l,r)$ 表示 $[l,r]$ 中 `*` 的个数，如 $l>r$ 则为 $0$。

- 当前 `P` 向左：$f_i←pos_i$，条件为 $count(f_{i-1}+1,pos_i-t-1)=0$。

- 当前 `P` 向左，但是上一个 `P` 向右。这种情况就是为了应对上述 hack 数据。$f_i←pos_{i-1}+t$，条件为 $count(f_{i-2}+1,pos_{i-1}-1)=0$ 且 $pos_{i-1}+t>pos_i$，这既保证了有解，又保证了这样转移有意义。

如果 $cnt=1$ 应该特判。

```C++
// Problem: C. 狗
// Contest: Hydro
// URL: http://www.nfls.com.cn:10611/p/P5290?tid=67356ef290bb8042a5906b42
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Challenger: Erica N
// ----
// 
#include<bits/stdc++.h>

using namespace std;
#define rd read()
#define ull unsigned long long
#define int long long 
#define pb push_back
#define itn int
#define ps second 
#define pf first


#define rd read()
int read(){
  int xx = 0, ff = 1;char ch = getchar();
  while (ch < '0' || ch > '9'){
    if (ch == '-')ff = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')xx = xx * 10 + (ch - '0'), ch = getchar();
  return xx * ff;
}
#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() {cerr << endl;}
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) {
	for (auto v: a) cerr << v << ' ';err(x...);
}
template<typename T, typename... A>
void err(T a, A... x) {
	cerr << a << ' ';err(x...);
}
#else
#define dbg(...)
#endif
const int N=2e6+5;
const ull P=137;
const int INF=1e18+7;
/*

策略


*/	



int pl[N],pr[N],pos[N],b[N],prel[N],sufr[N];
int midl[N],midr[N];
int n;
int l[N],r[N];
int pre[N];
string s;

int cnt=0;

int f[N];//前i个dog在吃完外面的后可以到达的最后端

inline int get(int a,int b){
	if(a<b)return 0;
	return pre[b]-pre[a];
}

bool check(int t){
	for(itn i=1;i<=cnt;i++){
		f[i]=0;
	}
	
	for(int i=1;i<=cnt;i++){
		f[i]=f[i-1];
		if(get(pos[i]-t-1,f[i-1])==0)f[i]=max(f[i],pos[i]);
		if(get(pos[i]-1,f[i-1])==0)f[i]=max(f[i],pos[i]+t);
		if(i>1){
			if(pos[i-1]+t>=pos[i]){
				if(get(pos[i]-t-1,f[i-2])==0)f[i]=max(f[i],pos[i-1]+t);
			}
		}
		
		// cdbg(f[i]);
	}
	
	return get(n,f[cnt])==0;
}
signed main(){
	// freopen("dogs.in","r",stdin);
	// freopen("dogs.out","w",stdout);
	 n=rd;
	cin>>s;
	s=" "+s;
	for(int i=1;i<=n;i++){
		if(s[i]=='P'){
			pos[++cnt]=i;
		}
		pre[i]=pre[i-1]+(s[i]=='*');
		// cdbg(pre[i]);
	}
	if(cnt==0){
		cout<<"0 0";
		return 0;
	}
	
	if(cnt==1){
		int l=pre[pos[1]-1],r=pre[n]-l;
		int fi,la;
		for(int i=1;i<=n;i++){
			if(s[i]=='*'){
				fi=i;
				break;
			}
		}
		for(int i=n;i;i--){
			if(s[i]=='*'){
				la=i;
				break;
			}
		}
		fi=pos[1]-fi;
		la=la-pos[1];
		if(l>r){
			cout<<l<<' '<<fi;
		}else if(r>l){
			cout<<r<<' '<<la;
		}else{
			if(fi<=la)cout<<l<<' '<<fi;
			else cout<<r<<' '<<la;
		}
		return 0;
	}
	
	
	int l=1,r=n;
	int res=0;
	while(l<=r){
		// cdbg(l,r);
		int mid=l+r>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	
	cout<<pre[n]<<' '<<res<<endl;
	
	
	
}

```

---

