# New Year Parties

## 题目描述

【问题描述】

新的一年到了,是时候和你的朋友聚在一起，回顾过去一年里发生的暖心事了。

n个人住在一个可以用数轴表示的城市里，第i个人住在一个整数坐标xi的房子里。第i个人可以和坐标xi - 1, xi+1一起来家里庆祝新年，或者呆在xi，每个人只能移动一次。对于房子在1或n的人，他们可以来到坐标0或n+1的房子。

例如，初始位置为x=[1,2,4,4]。最后的位置可以是[1,3,3,4]，[0,2,3,3]，[2,2,5,5]，[2,1,3,5]等等。被占用的房屋总数等于在最终房屋中不同位置的总数。

所有人可以随意选择三种操作之一，然后计算有人的房屋总数。有人的房屋可能达到的最小数量和最大数量各是多少?

## 说明/提示

在样例1中，人们可以转到[2,2,3,3]，x1到x1+1，x2不动，x3到x3 - 1，x4到x4 - 1。[1,1,3,3],[2,2,3,3]或[2,2,4,4]也是获得最小数量的选择。

对于已占用的房屋的最大数量，人们可以转到[1,2,3,4]或[0,2,4,5]。

【数据规模和约定】

1<=n<=2*10^5 , 1<=xi<=n

## 样例 #1

### 输入

```
4
1 2 4 4
```

### 输出

```
2 4
```

## 样例 #2

### 输入

```
9
1 1 8 8 8 4 4 4 4
```

### 输出

```
3 8
```

## 样例 #3

### 输入

```
7
4 3 7 1 4 3 3
```

### 输出

```
3 6
```

# 题解

## 作者：xiaomuyun (赞：9)

# CF1283E New Year Parties 题解
[题面链接](https://www.luogu.com.cn/problem/CF1283E)
## 题意
有 $n$ 个点在一条线段上，每个点都有一个位置 $x_i$（$1\leq x_i\leq n$）。我们称两个点不同当且仅当它们的位置不同。现在已知这 $n$ 个点的位置，以及它们可以做的动作：向左边或者右边移动一个单位，也就是说位置 $+1$ 或 $-1$。也可以不动。现在题目要问的是在这条线段上最多和最少一共有多少个点（位置相同的两个点我们看作一个，且位置可以为 $0$ 或 $n+1$）。
## 分析
我们将两个问题分开来看。
### 1. 求最少的点的数量
为了让它们尽可能的放在一起，所以对于每个点，如果在它的移动范围内有点，就可以直接跳过，去判断别的点即可（因为它可以直接移到那个点的位置）；如果在它的移动范围内没有点，就可以让它向右移一个位置，并将 $cnt+1$（这个后面会说），这样如果后面的点可以移到这里的话，就可以直接移过来。在遍历的过程中维护一个 $vis$ 数组，用来存当前位置有没有点。还要弄一个 $cnt$，来记录不同的点的数量。
### 2. 求最多的点的数量
为了让它们尽可能的不放在一起，所以对于每个点，我们要在它的移动范围里面尽可能选没有点的，而且还要靠左（因为靠右会影响后面的点的匹配）。如果它的移动范围里面有位置没有点，就可以让那个点的 $vis$ 设为 $1$；如果没有位置没有点，则什么也不用管（$cnt$ 不用 $+1$，$vis$ 也不用改）。
## 代码
```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int n,x[200001],cnt=0;
bool vis[200001];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&x[i]);
	sort(x+1,x+1+n);
	for(int i=1;i<=n;++i){//求最小值
		if(!vis[x[i]-1]&&!vis[x[i]]&&!vis[x[i]+1]) ++cnt,vis[x[i]+1]=true;
	}
	printf("%d ",cnt);
	cnt=0;
	memset(vis,false,sizeof vis);//记得清零
	for(int i=1;i<=n;++i){//求最大值
		if(!vis[x[i]-1]) ++cnt,vis[x[i]-1]=true;
		else if(!vis[x[i]]) ++cnt,vis[x[i]]=true;
		else if(!vis[x[i]+1]) ++cnt,vis[x[i]+1]=true;
	}
	printf("%d\n",cnt);
	return 0;
}
```
## 总结
点个赞吧，管理员求过！

---

## 作者：乐哥 (赞：4)

[原题传送门](https://codeforces.com/problemset/problem/1283/E)

[cf题解(英文)](https://codeforces.com/blog/entry/72592)

首先，将这两个子任务视为完全独立的问题。

对于这两种解决方案，构建cnt数组，其中cnti是住在i号房子里的人数。

### 1. 最小值

用贪心思想从左到右统计答案。如果cnti=0，则跳转i+1，否则答案加1，跳转i+3(i~i+2均可到达i+1位置因此可跳过不计)。

如果从i开始的3个连续的房子里都有人，那么2次合并是最优解，跳过任何一次合并都不会得到更好的答案。如果只有两个已经被占据了，一次合并就够了。而一所单独居住的房子显然无法进行合并。

### 2. 最大值

同样贪心，用cnt作为类似桶的容器来处理这些房子的连续位置。如果一段连续房屋的总数大于这一段的长度，那么你可以将这段房子向左或向右扩展。如果总和至少比长度大2，那么可以同时在前后两个方向上扩展它。

因此，贪心的思路会起作用。用i,j两个指针从左到右更新片段，对于每一段，检查到前一段的距离(如果向右扩展，则考虑新的右边界)。如果你可以扩展当前段并且左边有空间，那么就扩大它。如果你还可以扩展这部分，那就向右扩大。注意1->0和n->n+1两个边界情况。
#### 整体时间复杂度:O (n)。

代码见下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=200005;
int n,cnt[MAXN],a;
int solve_min() //最小值 
{
	int res=0,i=1;
	while(i<=n) //贪心 
	{
		if(cnt[i]) res++,i+=3; //若i位置有人，则答案加一，跳过连续三个可到达i+1位置的单位
		else i++; //若i位置没人，则跳一个单位 
	}
	return res;
}
int solve_max() //最大值 
{
	int res=0,dist=2; //res统计答案，dist统计段前空房子数
	bool ok=false; //ok标记段前空房子是否被占用过 
	for(int i=1;i<=n;i++)
	{
		if(!cnt[i]) //统计段前空房数 
		{
			dist++;
			continue;
		}
		int j=i-1,sum=0;
		while(j+1<=n&&cnt[j+1])
			j++,sum+=cnt[j]; //j指针右移，统计最长连续段
		res+=(j-i+1); //答案加上连续段长
		if(sum>j-i+1&&(!ok||dist>1))
			sum--,res++; //段前扩展 
		ok=false;
		if(sum>j-i+1)
			ok=true,res++; //段后扩展 
		i=j; dist=0; //更新i，重置dist 
	}
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a),cnt[a]++; //cnt[a]表示住在房子a中的人数 
	printf("%d %d",solve_min(),solve_max());
	return 0;
}
```
~~基本就是抄了一遍cf巨佬的题解~~

蒟蒻第一次发题解，求通过

#### 巨佬轻喷

---

## 作者：lin_rany (赞：1)

两个问题分开考虑，先对位置进行从小到大排序（所以时间复杂度是O(nlogn)）。

求最小值就让每一个人尽可能往右住，因为这样位置比他右的就可能可以和他住一个房间了。
求最大值就让每一个人尽可能往左边的空房间住，因为他这样就可以占领更多的房间。

代码：
```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(2)
#include<iostream>
#include<stdio.h>
#include<string>
#include<cstring>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<algorithm>
#define ll long long
#define lowbit(x)  (x)&(-x)
using namespace std;
const ll N=200000+10;
int n,w[N],ansmin,ansmax;
bool vis[N];
bool isok(int x)//看在x位置的人要不要在开一间房 
{
	if(vis[x]||vis[x-1]||vis[x+1])
		return true;
	return false;
}
int find(int x)//找到最左的一间空房，没找到返回-1 
{
	if(!vis[x-1])
		return x-1;
	if(!vis[x])
		return x;
	if(!vis[x+1])
		return x+1;
	return -1;
}
int main()
{
	//ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    //freopen("167.txt","r",stdin);
	#endif // ONLINE_JUDGE
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	sort(w+1,w+1+n);
	for(int i=1;i<=n;i++)
	{
		if(isok(w[i]))continue;
		else ansmin++,vis[w[i]+1]=1;
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
	{
		if(find(w[i])!=-1)vis[find(w[i])]=1,ansmax++;
	}
	printf("%d %d",ansmin,ansmax);
 	return 0;
}


```


---

## 作者：xiezihanAKIOI (赞：0)

~~看了一眼题解，好像没人用我这种做法，赶紧发篇题解。~~

一道明显的贪心题。

题意：

给你 $n$ 个数，每个数可以 +1 或 -1。求最后重合的点的最大值和最小值。

1.最小值。如果要求重合的点最少，我们就尽量把点往点多的地方移动。先定义一个数组 $ans$ 标记已经移动过的点的位置，我们可以统一先把所有点往一个方向移，如果另外一个方向已经有一个点了，那么我们就往反方向移动。使他们尽量重叠。如果一个点有多个人就把它们看做一个人，一起移动。

2.最大值。。如果当前的点有一个人，那么不必移动。如果有多个人，先从前，后找一个点没有人的，（如果都有人统一向后移。）移动之后如果这个点只剩一人，就不用移动了。如果还有人，那就将多的人找同一个方向（最好是每人的。）统一移动。

详情见代码注释：

```
#include<bits/stdc++.h>

using namespace std;

int a[200005], cnt, ans[200005], x, n;

int main () {
	ios::sync_with_stdio (false), cin.tie (0), cout.tie (0);
	cin >> n;
	for (int i = 1 ; i <= n ; i++) cin >> x, a[x]++;
	for (int i = 1 ; i <= n ; i++) {
		if (a[i]) { //如果当前点有人。 
			if (ans[i]) continue; //如果当前点不止一人，那此时就是最优解，不必再移动。 
			if (ans[i - 1]) continue; //如果前面的点有人，向前移动。 
			else { //否则统一向后移动。 
				ans[i + 1] = 1;
			}
		}
	}
	int cnt = 0;
	for (int i = 0 ; i <= n + 1 ; i++) cnt += ans[i], ans[i] = 0;
	cout << cnt << " ";
	for (int i = 1 ; i <= n ; i++) {
		if (a[i]) { //如果当前点有人。 
			if (!ans[i - 1]) { //如果前面没人，向前移动。 
				a[i]--; //统计当前剩下的人数。 
				ans[i - 1] = 1;
			}
			if (a[i]) { //如果还有人。 
				if (ans[i]) ans[i + 1] = 1; //如果当前点有人，且前面已经有人了，向后移动。 
				else { //当前点没人，停留在原地即可。 
					ans[i] = 1;
					if (a[i] > 1) { //如果还是有人。 
						ans[i + 1] = 1; //统一向后移。 
					}
				}
			}
		}
	}
	cnt = 0;
	for (int i = 0 ; i <= n + 1 ; i++) cnt += ans[i];
	cout << cnt;
}
```

---

## 作者：zsyyyy (赞：0)

## CF1283E 1800

### 题目描述：

$n$ 个数，每个数可以 $+1$ 或 $-1$ 或 $+0$，求最后不同的数的个数的最大值和最小值。


### 输入格式：

第一行一个整数 $n$，第二行 $n$ 个数。


### 输出格式：

两个整数，表示最大个数和最小个数。


### 思路

考虑贪心。

对于最小值，处理所有值为 $x$ 的数，不变显然不会是最优的。如果有数等于 $x-1$，也就是说 $x-1$ 已经被占上了，那么 $x$ 进行 $-1$ 操作变为 $x-1$ 一定是最优的；否则，就让 $x$ 进行 $+1$ 的操作，因为这样有可能让 $x$ 和 $x+1$ 或 $-1$ 后的 $x+2$ 合并。

对于最大值，处理所有值为 $x$ 的数，如果没有数等于 $x-1$，那么把一个值为 $x$ 的数变为 $x-1$，如果还有值为 $x$ 的数，就把一个值为 $x$ 的数变为 $x+1$。

注意，因为一个数只能进行一次操作，所以需要记录哪些是操作后的，哪些是原本的。



#### 代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+10;
int n,t1[MAXN],t2[MAXN],tmp,ans1,ans2,p1[MAXN],p2[MAXN];
//t[i]表示有多少个数本来就等于i，p[i]表示当前有多少个数等于i且是从其他数变来的（也就是说不能变了）
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&tmp);
		t1[tmp]++;
		t2[tmp]++;
	}
	for(int i=1;i<=2e5+5;i++) //求最小值
	{
		if(p1[i])  continue;
		if(p1[i-1]||t1[i-1])
		{
			p1[i-1]+=t1[i];
			t1[i]=0;
		}
		p1[i+1]+=t1[i];
		t1[i]=0;
	}
	for(int i=1;i<=2e5+5;i++) //求最大值
	{
		if(!t2[i])  continue;
		if(!t2[i-1]&&!p2[i-1])
		{
			p2[i-1]++;
			t2[i]--;
		}
		if(t2[i]>1||t2[i]==1&&p2[i])
		{
			p2[i+1]++;
			t2[i]--;
		}
	}
	for(int i=0;i<=2e5+5;i++)
	{
		if(t1[i]||p1[i])  ans1++;
	}
	for(int i=0;i<=2e5+5;i++)
	{
		if(t2[i]||p2[i])  ans2++;
	}
	printf("%lld %lld\n",ans1,ans2);
	return 0;
}
```



---

