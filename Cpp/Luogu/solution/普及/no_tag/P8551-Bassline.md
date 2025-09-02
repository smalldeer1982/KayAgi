# Bassline

## 题目背景

fuwa↑ fuwa↑ fuwa↑ fuwa↑

赫尔德开始使用当下热潮的聊天软件 BassLine，那么第一步自然是加好友了！加好友既需要确认自己和对方有共同兴趣，又需要能加到足够多的好友。赫尔德将其抽象成了下面这个问题，让你来帮她解决。

## 题目描述

本题中，区间 $[l,r]$ 指所有大于等于 $l$ 且小于等于 $r$ 的整数组成的集合，如 $[3,3]$ 代表 $\{3\}$，$[3,7]$ 代表 $\{3,4,5,6,7\}$。

给定 $n$ 个区间，第 $i$ 个区间是 $[l_i,r_i]$。

你需要选择两个整数 $x\le y$，满足：

- 对于所有区间 $[l_i,r_i]$（$1\le i \le n$），以下两个条件之一满足：
	1. $[x,y]$ 被 $[l_i,r_i]$ 包含，换言之， $[x,y]\cap[l_i,r_i]=[x,y]$。
    2.  $[x,y]$ 与 $[l_i,r_i]$ 无交集，换言之，$[x,y]\cap[l_i,r_i]=\varnothing$。

若有 $k$ 个区间满足条件 1，则你的得分是 $k(y-x)$。输出你最大的可能的得分。

## 说明/提示

**【样例解释】**

对于样例，$[5,6]$ 是最优的区间之一，其含于 $[4,7],[5,9]$，且与 $[1,3],[7,10]$ 没有交集。此时 $k=2$，因此答案为 $2\times(6-5)=2$。$[1,3]$ 也是一个最优的区间。

$[5,7]$ 并非合法的区间，因为它与 $[7,10]$ 有交集，也并不含于 $[7,10]$。

---

**【数据范围】**

对于所有数据保证 $1 \le n \le 3 \times {10}^5$，$1 \le l_i \le r_i \le 3 \times {10}^5$。

- 子任务 1（20 分）：$n,l_i,r_i \le 10$；
- 子任务 2（20 分）：$n \le {10}^3$；
- 子任务 3（20 分）：$l_i, r_i \le {10}^3$；
- 子任务 4（40 分）：无特殊限制。

## 样例 #1

### 输入

```
4
1 3
4 7
5 9
7 10
```

### 输出

```
2
```

# 题解

## 作者：dottle (赞：15)

我们先来思考，怎样的 $[x,y]$ 是合法的。

直接给出结论：$[x,y]$ 合法，当且仅当 $[x+1,y]$ 其不包含任意一个左端点，$[x,y-1]$ 不包含任意一个右端点。

比如说 $[x+1,y]$ 包含了端点 $l_i$，那么 $[x,y]$ 一定不被 $[l_i,r_i]$ 包含，但他们有交集，这就不合法了。反之，如果 $[x,y]$ 不被 $[l_i,r_i]$ 包含，但他们有交集，那么要么 $[x+1,y]$ 其包含 $l_i$，要么 $[x,y-1]$ 包含 $r_i$。

接下来考虑代码实现，为了方便，我们把上面对左端点的约束写成 $[x,y-1]$ 不包含任意一个 $l_i-1$，即将读入的左端点向左平移一个位置。这样我们的条件就变成了 $[x,y-1]$ 不包含任意一个端点了。

因为我们想要最大化 $k(y-x)$，那么我们一定是选一段尽可能长的区间作为答案。那么我们选取的 $x$ 一定是某个端点的右边一个位置，选取的 $y$ 一定是 $x$ 后面的第一个端点。可以使用前缀和的方式求出对于两个端点之间，有多少线段覆盖了它。这样，就可以统计答案了。

时间复杂度 $O(x)$，其中 $x$ 是值域大小。

```cpp
#include<bits/stdc++.h>
#define N 300050
#define int long long
using namespace std;
int f[N],x,y,v[N],mx,pre=1,sum,ans,n;

signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&x,&y);
    	v[x-1]=1,v[y]=1;// 标记哪些位置有端点，注意左端点往左移动一个位置
    	f[x]++,f[y+1]--;// x 到 y 位置被覆盖的次数 +1
    	mx=max(mx,y);// 记录最大的坐标
    }
	for(int i=1;i<=mx;i++){
		sum+=f[i];// 计算当前位置被多少个线段覆盖了
		if(v[i])ans=max(ans,sum*(i-pre)),pre=i+1;//若这里有一个端点，则作为 y，与之前记录的 x 更新答案；然后更新 x 为此端点右边一个位置
	}
	printf("%lld",ans);
}
```

## 

---

## 作者：if_OF (赞：5)

# P8551 Bassline 题解

## 分析

这道题做月赛的时候想了好久，最后发现其实很简单。

我们用样例数据来分析：

![](https://cdn.luogu.com.cn/upload/image_hosting/c22rrcqh.png)

如图所示，我们将每个区间抽象化为一个一个的长条。题目给我们的两个要求可以理解为 $[x,y]$ 所覆盖的列中没有任意一个长条开始或结束，如图中第 4 列就是绿色长条的开始部分，第 7 列就是绿色长条的结束部分，它们都不满足要求，所以 $[x,y]$ 不能包含这两列。

理解到这里了，这道题就很简单了：我们只需要用有长条开始或者结束的列将最大区间分成几个部分（如下图），取区间长度减一乘以区间内的长条数的最大值即 $k-(y-x)$ 就行了。

![](https://cdn.luogu.com.cn/upload/image_hosting/pmu5uahe.png)

## 思路

我们使用一个数组存储每一个数（即上面分析时所说的列）是多少个区间的起点和终点，我用的是结构体 `x[i]` ，当然你也可以用两个数组解决。对于读入的每个区间 $[l_i,r_i]$，我们让 `x[li].geb++,x[ri].end++`，并且存储最左边的点 `left` 和最右边的点 `right`。

接着，我们从 `left` 循环到 `right` ，用 `cnt` 来记录能被选择的 $[x,y]$ 区间中的元素个数（即 $y-x$ ），每当遇到一个区间的开始或结束就将 `cnt` 清零，再用 `k` 记录每一个数上的区间个数，每次用 `cnt*k` 跟答案比较取最大值就好了。

## 程序

```c++
#include<bits/stdc++.h>
using namespace std;
int n;
struct Node
{
	int beg=0,end=0;
}x[300005];//使用结构体存储每个数字是多少个区间的起点和终点
int main()
{
	scanf("%d",&n);
	int left=300005,right=-1,k=0,cnt=0;
	for(long long i=1;i<=n;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		x[l].beg++,x[r].end++;//区间[l,r]开头和结尾的数字的起点个数和终点个数分别+1
		left=min(l,left);
		right=max(right,r);
	}
	long long ans=0;//一定记得开long long，不然最后一个点会炸
	for(int i=left;i<=right;i++)
	{
		++cnt;//记录这个可选区间中y-x的值
		if(x[i].beg || x[i-1].end)
			cnt=0;//如果i是某个区间的起点或者终点就将cnt清零
		k+=x[i].beg;//用k记录i上的区间个数
		ans=max(ans,cnt*k);//取最优解
		k-=x[i].end;
	}
	printf("%lld\n",ans);
}
```



---

## 作者：晴空一鹤 (赞：3)


[题面传送门](https://www.luogu.com.cn/problem/P8551)

# Solution

首先，题目的意思是构造出一个最大的区间，对于每个输入所给的区间来说，这个区间要么完全被包含，要么与其无交集。

考虑一个合法的区间 $[L,R]$ 应该满足的条件，

如果 $[L,R]$ 跨过了某个区间的端点，则 $[L,R]$ 有一部分将在该区间内，有一部分在该区间外，不合法。

因此我们可以把这些端点看作断点，一个合法的区间必然在相邻的两断点之间，这点可以通过排序做到。

最后再注意一下边界情况，因为被包含时两区间左右端点可以重合，无交集时则不能重合，如果两个相邻的断点靠前的为左端点，则说明在这两个断点内可选的最大区间 $[L,R]$ 被左断点所在区间包含,因此 $[L,R]$ 的 $L$ 可以与其重合，否则不可。同理，若靠后的为右端点，则 $[L,R]$ 的 $R$ 可以与其重合，反之不可。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct no
{
    ll x,y,z;
}t[1000001];
bool inline cmp(no a,no b)
{
    if(a.x==b.x)
    return a.y>b.y;
    return a.x<b.x;
}
ll n,a[1000001],ans=0,sum=0;
int main()
{
    cin>>n;
    for(int i=1;i<=n*2;i++)
    {
    cin>>a[i];
    t[i].x=a[i],t[i].y=i%2==0?-1:1,t[i].z=(i+1)/2;
    }
    sort(t+1,t+n*2+1,cmp);

    for(int i=1;i<=n*2;i++)
    {
       sum+=t[i].y;
       ans=max(ans,sum*(t[i+1].x-t[i].x-2+(t[i].y!=-1)+(t[i+1].y!=1)));
    }
    cout<<ans<<endl;
}
```

~~这么简单的题你应该不会抄题解把~~

---

## 作者：_hxh (赞：2)

## 分析

这道题目的主要信息为：对于每个区间 $[l_i,r_i] (1 \le i \le n)$，须满足 $[x,y] \cap [l_i,r_i] = [x,y]$ 或 $[x,y] \cap [l_i,r_i] = \varnothing$。设 $k$ 为满足条件1的区间数量，我们需要求一个区间 $[x,y]$，使 $k \times (y - x)$ 最大。

把第一段的内容翻译一下。

设一个集合 $A$，$A \gets [x,y] \cap [l_i,r_i]$，则要么 $A = [x,y]$，要么 $A = \varnothing$。

1. $A = [x,y]$，则 $[x,y] \in [l_i,r_i]$，$l_i \le x \le y \le r_i$。
2. $A = \varnothing$，很简单，$A$ 和 $[l_i,r_i]$ 没有交集，即 $y < l_i$ 或 $r_i < x$。

所以对于所选区间 $[x,y]$，$[x + 1,y]$ 不能包含任何一个 $l_i$，$[x,y - 1]$ 不能包含任何一个 $r_i$。因为我们要使 $k \times (y - x)$ 最大，所以 $(y - x)$ 要尽量大，$x$ 要尽量小，$y$ 要尽量大，所以 $x$ 一定等于某个 $l_i$，$y$ 一定等于某个 $r_i$。一定注意，$[x + 1,y - 1]$ 中一定不包含任何 $l_i$ 或 $r_i$，因为这违反前面两条规定。

对于实际的程序，我们可以不用关心 $(y - x)$ 是否有更大值，$\Theta(1)$ 跑一遍就行了。

总结了这么多了，接下来看代码吧。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int N = 3e5 + 5;
int n,k,y_x,l,r,__start[N],__end[N],_left = 1e9,_right = -1,ans = -1;
signed main()//不开long long会痛失40分 
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> l >> r;
		__start[l]++;
		__end[r]++;
		_left = min(_left,l);
		_right = max(_right,r);
	}
	for (int i = _left;i <= _right;i++)
	{
		y_x++;//y_x为y - x的值 
		if (__start[i] || __end[i - 1])//判断是否为某个区间的起点或者终点 
			y_x = 0;//因为不能包含，所以清空y - x的值 
		k += __start[i];//满足条件1的区间数 
		ans = max(ans,k * y_x);
		k -= __end[i];
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：2)

## 题面
[P8551 Bassline](https://www.luogu.com.cn/problem/P8551)

## 分析
容易发现所选的区间一定不会与所给区间有部分重合的情况。
那么我们可以从最小的 $l_i$ 一直枚举到最大的 $r_j$，定义 $num$ 为右端点为 $i$ 的最长合法区间。如果当前的i为某一个已给的区间的左端点或者上一步为某一个已给的区间的右端点，那就重置 $num$。

再定义一个 $cnt$ 表示当前这个合法区间所覆盖的区间数。容易发现答案就是所有 $cnt \times num$ 的最大值。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 300010
using namespace std;
int L[MAXN],R[MAXN];
int visl[MAXN],visr[MAXN];
int n;
int num,cnt,ans;
inline int read()
{
	int x=0;
	char c=getchar();
	while(!isdigit(c))
	{
		c=getchar();
	}
	while(isdigit(c))
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x;
}
inline void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inline int max(int x,int y)
{
	return x<y?y:x;
}
inline int min(int x,int y)
{
	return x>y?y:x;
}
signed main()
{
	n=read();
	int l=MAXN,r=0;
	for(register int i=1;i<=n;i++)
	{
		L[i]=read(),R[i]=read();
		visl[L[i]]++;
		visr[R[i]]++;
		r=max(r,R[i]);
		l=min(l,L[i]);
	}
	for(register int i=l;i<=r;i++)
	{
		num++;
		if(visl[i])num=0;
		if(visr[i-1])num=0;
		cnt+=visl[i];
		ans=max(ans,num*cnt);
		cnt-=visr[i];
	}
	write(ans);
	return 0;
}
```


---

## 作者：Lyccrius (赞：2)

> `2022/10/16` AC 300 祭 [Bassline](https://www.luogu.com.cn/record/90241856)

***

> 本文思路来自 [dottle](https://www.luogu.com.cn/blog/dottle/bassline)  
> 在其基础上扩写而成  
> 让我们感谢他的贡献  

> 题目链接：[P8851 Bassline - 洛谷](https://www.luogu.com.cn/problem/P8551)

## 读题

先对题目中的易混淆点进行强调：  

> 你需要选择两个整数 $x\le y$，满足：
> 
> - 对于所有区间 $[l_i,r_i]$（$1\le i \le n$），以下两个条件之一满足：
>	1. $[x,y]$ 被 $[l_i,r_i]$ 包含，换言之， $[x,y]\cap[l_i,r_i]=[x,y]$。
>    2.  $[x,y]$ 与 $[l_i,r_i]$ 无交集，换言之，$[x,y]\cap[l_i,r_i]=\varnothing$。
> 
> 若有 $k$ 个区间满足条件 1，则你的得分是 $k(y-x)$。输出你最大的可能的得分。

这里 $x, y$ 是我们要求的数，$k$ 也是。~~（废话……~~

但关于 $k$ 的来源，请注意，是满足包含 $[x, y]$，或与 $[x, y]$ 无交集的 $[l_i, r_i]$，而 $[l_i, r_i]$ 是题目给定的数据。

换言之，$k$ 的含义，并不是有多少个 $[x, y]$ 满足上述条件（那样 $k$ 将为定值），而是针对我们给出的 $[x, y]$，有多少个输入给定的 $[l_i, r_i]$ 将其包含或与之无交集。

这样一来，$k$ 的值是随不同的 $[x, y]$ 而变化的。我们只需根据每一个合法的 $[x, y]$，求出有多少个 $[l_i, r_i]$ 满足条件，取最大值即是答案。

## 解题

要 $[x, y]$ 合法，那么 $(x, y]$ 内不能出现任何一个 $l_i$，同时 $[x, y]$ 内不能出现任何一个 $r_i$。

> 这里的 $(), []$ 都没有打错。  
> * $()$ 表示开区间，不包含左右端点；  
> * $[]$ 表示闭区间，包含左右端点；

当 $k$ 的值一定时（满足条件的 $[l_i, r_i]$ 一定），$y - x$ 最大时答案最大。

我们考虑两种条件：  
*由于 $l, r$ 在这里作为左右端点的约束条件存在，其下标不一定相同，故舍去。*  
1. $[x, y]$ 被 $[l, r]$ 包含：  
    $x = l, y = r$；
2. $[x, y]$ 与 $[l, r]$ 无交集：  
	$x = r + 1, y = l - 1$.
我们发现边界出现 $+1, -1$ 不是很好处理，于是考虑：  
令 $l' = l - 1$，  
则：  
1. $[x, y]$ 被 $[l, r]$ 包含：  
    $x = l' + 1, y = r$；
2. $[x, y]$ 与 $[l, r]$ 无交集：  
	$x = r + 1, y = l'$.

这样一来，两种条件的区间形式就统一了。

不难发现：
* 每个 $l' + 1, r + 1$ 可以作为 $x$;
* 每个 $l', r$ 可以作为 $y$.  
即
* 每个 $l, r + 1$ 可以作为 $x$；
* 每个 $l - 1, r$ 可以作为 $y$.  

可以推出，我们考虑的每一个 $y$，都可以将 $y + 1$ 作为下一次考虑的 $x$。

## 写题

用 $point_i$ 表示第 $i$ 位能否作为 $y$，在读入 $l_i, r_i$ 时，将 $l_i - 1, r_i$ 作好标记；  
用 $cover_i$ 以差分的方式表示第 $i$ 位被多少 $[l_i, r_i]$ 覆盖，在读入 $l_i, r_i$ 时，将 $cover_l + 1, cover_{r + 1} - 1$；  
用 $last$ 存储 $y$ 最后一次出现的位置，即 $\max(r_i)$，以便与后续遍历。

遍历下标 $i$，同时用 $cnt$ 计算 $cover_i$ 的前缀和，即可得到第 $i$ 位的 $k$；  
若 $i$ 可以作为 $y$：  
* 计算 $k (y - x)$ 的值，并记录；
* 更新 $l = i + 1$（$l$ 初始值为 $1$.

## 代码

```
#include <cstdio>
#include <algorithm>

const int maxn = 3e5 + 10;

int n;
int x, y;

int point[maxn];
int cover[maxn];
int last;
int cnt;
int pre = 1;
long long ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
	scanf("%d%d", &x, &y);
    	point[x - 1] = 1;
        point[y] = 1;
    	cover[x]++;
        cover[y + 1]--;
    	last = std::max(last, y);
    }

    for (int i = 1; i <= last; i++) {
	cnt += cover[i];
	if (point[i]) {
            ans = std::max(ans, (long long)cnt * (i - pre));
            pre = i + 1;
        }
    }

    printf("%lld\n", ans);

    return 0;
}
```

### 备注

此题中 $1 \le n \le 3 \times {10}^5$，数组需开全局，否则会 WA。  
> Lyccrius 交了 17 遍才过。

---

## 作者：ForeverCC (赞：1)

对于一个区间 $[x,y]$：

- 如果在 $[x,y-1]$ 中有一个区间的结尾，则 $[x,y]$ 与那个区间有交集但不包含。

- 如果在 $[x+1,y]$ 中有一个区间的开头，则 $[x,y]$ 与那个区间有交集但不包含。

用差分加前缀和可以求任意一个区间的 $k$。

用变量 `cnt` 表示 $x-y$ 的值，遍历 $i$ 从 $1$ 到 $300000$，如果满足 $i-1$ 不是一个区间的结尾，$i$ 不是一个区间的开头，`cnt++`，答案即为最大的 `k*cnt`。

参考程序：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 300005 
using namespace std;
int n,l,r,cnt,s[N],q[N],ans=-1e9;
bool head[N],tail[N];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&l,&r);
		head[l]=tail[r]=1;//记录是否为头尾 
		s[l]++,s[r+1]--;//差分 
	}
	for(int i=1;i<=300000;i++)q[i]=q[i-1]+s[i];//前缀和 
	for(int i=1;i<=300000;i++){
		if(!tail[i-1]&!head[i])cnt++,ans=max(ans,q[i]*cnt);
		else cnt=0;
	}
	printf("%lld\n",ans);
	return 0; 
}
```


---

## 作者：Untitled10032 (赞：1)

通过观察题面，可以得到结论：对于所有给定区间，它们的左界和右界不能出现在所选区间（$[x, y]$）内部。

更细致一点，所选区间 $[x, y]$ 的左界可以和给定区间的左界重合，但不能和给定区间右界重合；所选区间 $[x, y]$ 的右界可以和给定区间的右界重合，但不能和给定区间左界重合；且所选区间内部不能出现给定区间的左右界。

即 $\forall i \in [1, n], l_i \in [1, x] \cup (y, 3 \times 10^5]$ 且 $r_i \in [1, x) \cup [y, 3 \times 10^5]$

_（本题解中区间的定义与题目中的一致，题解中的区间 $[l, r]$ 表示数学中的 $[l, r] \cap \mathbb{Z}$）_ 

而且可以知道，在同一位置，选定区间 $[x, y]$ 越大，解越优。即：若 $[x_1, y_1] \subset [x_2, y_2]$，且 $[x_1, y_1]$ 和  都符合要求，则 $[x_2, y_2]$ 的得分 $\geq$ $[x_1, y_1]$ 的得分。



所以我们可以先处理出 $x$ 和 $y$ 到哪里就需要停，区间再扩大就会不满足要求，这样就在整个数轴上划出了许多不重叠的区间，它们都有可能成为最优解。枚举这些区间，取分数最大值即可。

至于如何计算题目中的 $k$，则可以使用一个前缀和数组和一个后缀和数组，前缀和数组 $pre_i$ 记录 $[1, i]$ 之间出现过几次给定区间的右界，后缀和数组 $suf_i$ 记录 $[i, 3 \times 10^5]$ 之间出现过几次给定区间的左界。$[x, y]$ 对应的 $k$ 就是 $n - pre_{x - 1} - suf_{y + 1}$。

代码：

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
constexpr int N = 300000;
int pre[N + 100]; //集合右界，前缀和
int suf[N + 100]; //集合左界，后缀和
bool stopl[N + 100];    //所选区间左界需要在这里停顿
bool stopr[N + 100];    //所选区间右界需要在这里停顿
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        pre[r]++;   //添加右界
        suf[l]++;   //添加左界
        stopl[l] = stopl[r + 1] = stopr[r] = stopr[l - 1] = true;
    }
    for (int i = 1; i < N; i++)
        pre[i] += pre[i - 1];   //计算前缀和
    for (int i = N; i > 0; i--)
        suf[i] += suf[i + 1];   //计算后缀和
    int l = 1, r = 1;
    ll mxScore = 0; //最大分数，注意分数要开long long

    //枚举可行的最大区间
    while (true) {
        while (!stopl[l] && l <= N)
            l++;    //找到左界下一个需要停顿的地方
        if (l > N)  break;  //找到头了就停
        r = l;
        while (!stopr[r] && r <= N)
            r++;    //从左界开始找到第一个右界需要停顿的地方
        if (r > N)  break;
        const ll nowScore = (ll)(r - l) * (n - pre[l] - suf[r]);    //计算分数
        mxScore = max(mxScore, nowScore);   //更新最大值
        l = r;  //寻找下一可行的区间
        if (stopl[l])    l++;   //避免死循环
    }

    printf("%lld", mxScore);
    return 0;
}
```


---

## 作者：CI_is_safe (赞：1)

# P8551 Bassline 题解
[题目传送门](https://www.luogu.com.cn/problem/P8551)
## 思路
样例对应的区间如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7fwutja1.png)

可以发现如果我们选择的区间如果跨越了至少一个端点，那么这个区间必定不合法。但是还有一些边界情况，如 $[3,4]$ 区间，它没有跨越任何一个端点，但它却是不合法的区间。这时可以发现还有一个充要条件是，如果 $[x,y]$ 区间合法，那么 $[x+1,y]$ 不含任意一个左端点，$[x,y-1]$ 不含任意一个右端点。像 $[4,5]$ 区间，因为 $[5,5]$ 区间包含了一个左端点 $5$ ，所以它不合法，而 $[7,8]$ 区间，因为 $[7,7]$ 区间包含了 $7$ 这个右端点，所以它也不合法。而要算一个点被几个点覆盖，只需要差分和前缀和即可计算。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300002;
int n,l,r,s[N],pre=1;
bool v[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int l,r;
		scanf("%d%d",&l,&r);
		v[l-1]=1,v[r]=1,++s[l],--s[r+1];
	}
	long long sum=0,ans=0;
	for(int i=1;i<N;++i){
		sum+=s[i];
		if(v[i])ans=max(ans,sum*(i-pre)),pre=i+1;
	}
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：Dregen_Yor (赞：1)

## 讲一个非正解的玄学做法

~~虽然玄学但依然跑的飞快。~~

# 思路

根据题目中所给的条件，我们不难看出，合法的区间被线段覆盖的条数肯定是区间内任意两个点都相等，如果存在覆盖条数不相等的情况，那么它一定是这种情况：


![](https://cdn.luogu.com.cn/upload/image_hosting/65224dzg.png)

其中蓝色表示题中给出的限制区间，红色表示所选区间。

很显然是不符合题意的，但如果只凭借区间覆盖的线段条数来做的话，你会发现样例测试输出为 $3$。我们来简单画一下样例的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/h2y47my0.png)

你会发现区间 $[1,4]$ 都被 $1$ 条线段所覆盖，但覆盖他们的并不是同一个线段，这样的话运算出的答案为 $1 \times (4-1)=3$，但实际答案应该为 $2$。

为了避免上述情况，我们可以给每一个线段赋一个权值。由于权值的大小对本题并无影响，且为了避免一些特殊情况和极端情况，我们将线段的权值赋为一个**随机数**，这样在运行程序的时候，一个所有点的权值之和全部相等的区间一定是一个合法的区间，这样我们只需遍历一遍区间就可以求出答案，区间赋值用**差分和前缀和**维护即可。

时间复杂度：$\mathcal O(n)$。

注意一定要开 long long。

# 代码

```cpp
#include<bits/stdc++.h>
#include<time.h>
#define int long long
using namespace std;
int n,sum[300010],ans,siz[300010];
signed main(){
	srand(time(0));
	srand(rand());
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		int l,r;
		scanf("%lld%lld",&l,&r);
		siz[l]++;
		siz[r+1]--;
		int k=rand()|rand();
		sum[l]+=k;
		sum[r+1]-=k;
	}
	for(int i=1;i<=300010;i++){
		sum[i]+=sum[i-1];
		siz[i]+=siz[i-1];
		//printf("%d ",sum[i]);
	}
	int l=1;
	for(int i=1;i<=300010;i++){
		if(sum[i]==sum[l]){
			ans=max(ans,siz[i]*(i-l));
		}
		else{
			l=i;
		}
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：zxh923 (赞：0)

# P8551 Bassline 题解

[题目传送门](https://www.luogu.com.cn/problem/P8551)

### 分析

先考虑贪心，如果想要使得分最大，需要将 $x$ 放在一个端点的后一个点，$y$ 放在 $x$ 后的第一个端点，这样区间长度就是当前最大的。

所以我们可以用一个数组记录下所有的这些点，如果可行就改为 $1$。

接着，差分记录被覆盖的数量，统计时进行前缀和即可。

最后扫一遍覆盖的区域，按题目中的式子求得分即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 300005
using namespace std;
int n,a[N],l,r,b[N],maxx,cnt,las=1,ans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//读写优化
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l>>r;
		b[l]++;
		b[r+1]--;//差分
		a[l-1]=a[r]=1;
		maxx=max(maxx,r);//找出最大的右端点
	}
	for(int i=1;i<=maxx;i++){
		cnt+=b[i];//前缀和
		if(a[i]){
			ans=max(ans,cnt*(i-las));//求最大的得分
			las=i+1;//区间左端点
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Forever1507 (赞：0)

解法：双指针

时间复杂度：$\Theta(n)$

首先观察到一个性质，就是当 $x$ 固定，且 $y$ 不进入或脱离其它线段时，$y$ 越大越好（因为 $k$ 此时不变），反之，那么为了满足 $[x,y]$ 区间的合法性，我们要将 $x$ 赋值为 $y$。（不然就有交集但不包含了）

所以只要把 $y$ 一直加，并将答案不断取 $\max$ 即可，当 $y$ 离开一个线段（可以将线段终点位置标记）或进入新线段时执行 `x=y;` 即可。

$x$ 的值不动 $k$ 也就不动，所以只要在更新 $x$ 的时候算 $k$ 就可以了，这个可以差分处理。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,diff[300005];
struct node{
	int l,r;
}line[300005];
bool lt[300005],rt[300005];
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	int x=1e12,y,mx=0;
	for(int i=1;i<=n;++i){
		cin>>line[i].l>>line[i].r;
		lt[line[i].l]=1;
		rt[line[i].r]=1;
		diff[line[i].l]++;
		diff[line[i].r+1]--;
		x=min(x,line[i].l);
		mx=max(mx,line[i].r);
	}
	y=x;
	for(int i=1;i<=mx;++i)diff[i]+=diff[i-1];
	int maxn=0,cnt=diff[x];
	while(1){
		++y;
		if(y==mx+1)break;
		if(lt[y]||rt[y-1]){
			x=y;
			cnt=diff[y];
		}
		maxn=max(maxn,cnt*(y-x));
	} 
	cout<<maxn;
	return 0;
}

```


---

## 作者：Elairin176 (赞：0)

我们不妨换一个题意？    
有 $n$ 个地毯，第 $i$ 个铺在 $[l_i,r_i]$ 里，现要求再找出一个区间 $[x,y]$，使得这个地毯被包含的次数是最多的，并与其他地毯无关联。      
这样，我们就好办了。    
我们可以先统计各个地毯都出现在哪里，以及哪里有地毯。统计的这部分可以用 unordered_map 做，但它会爆空间。所以这里我们用一些更高级的方法——**累加**！   
我们先给这些区间编号，比如第 $i$ 个区间的编号为 $i$。如果一个端点 $d$ 被多个地毯覆盖，则可以用覆盖在 $d$ 上的所有区间的编号相加。    
比如有 $2$ 个区间，分别为 $[1,3]$ 和 $[2,5]$，就可以这样统计（假设这个累加所用的数组为 $A$)：  
假设 $[1,3]$ 的编号是 $1$，$[2,5]$ 的编号是 $2$，那么  
$A_1=1$   
$A_2=1+2$   
$A_3=1+2$...(后面的以此类推）   
这里这一部分完成了。   
下一部分，统计随便一个点 $d$ 有没有地毯。   
这个比较好写，定义一个 bool 数组，那个点有区间覆盖就为 true，没有为 false。  
有人会问：你有一个 bool 数组了，为什么还要统计地毯出现在哪里啊？    
因为，那个 bool 数组可能会出现一段区间不在另一个区间之内，而用累加的方法就可以去掉这些情况。 
还有，累加的数字会很大，要用 long long。   
并且，还要使用差分优化时间，不然最后一个 subtask 会 TLE。   
CODE：   
```cpp
#include <iostream>
using namespace std;
int n,l,r,a[300005],m,len,c[300005],d[300005];
long long b[300005],x,maxx;
inline int read(){//快读，加快速度
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x;
}
inline void write(unsigned long long a){
    if(a>9) write(a/10);
    putchar(a%10+48);
}
int main(void){
	n=read();
	long long ii=1;
	while(n--){
		l=read();
		r=read();
		c[l]+=ii;//差分 
		c[r+1]-=ii;
		++d[l];
		--d[r+1];
		ii++;
		m=max(r,m);
	}
	n=m+1;
	for(int i=0;i<n;i++){//还原数组 
		if(i==0){
			b[i]=c[i];
			a[i]=d[i];
		}else{
			b[i]=c[i]+b[i-1];
			a[i]=d[i]+a[i-1];
		} 
	}
	for(int i=0;i<n;++i){//操作
		x=b[i];
		len=0;
		for(;i<n&&b[i]==x;++i){
			++len;
		}
		--i;
		maxx=max(maxx,(long long)a[i]*(len-1));
	}
	write(maxx);
}
```


---

