# Battle Cows

## 题目描述

有 $ n $ 头奶牛参加编程比赛。奶牛 $ i $ 的 Cowdeforces 评级为 $ a_i $（奶牛们的评级全部不同）。它们最初处于 $ i $ 的位置。比赛由 $ n-1 $ 个比赛组成，规则如下所示：

- 第一场比赛是在位置 $ 1 $ 的奶牛和位置 $ 2 $ 的奶牛之间。
- 随后，每场比赛 $ i $ 在位置 $ i+1 $ 的奶牛和比赛 $ i-1 $ 的获胜者之间。
- 在每场比赛中，Cowdeforces 评级较高的奶牛获胜并进入下一场比赛。

你是奶牛 $ k $ 的主人。对你来说，赢得比赛并不重要。你希望你的奶牛在尽可能多的比赛中获胜。作为比赛组织者的熟人，你可以要求他们将你的奶牛与另一头奶牛交换一次位置，或者什么都不做。请问你的奶牛最多胜利几场？

## 说明/提示

在第一组数据中，应该什么都不做。设 $ a' $ 是原始顺序中奶牛的 Cowdeforces 评级（你的奶牛评级会加粗）。

- 最初，$ a' = [\mathbf{12}， 10， 14， 11， 8， 3] $ 。
- 你的奶牛与 Cowdeforces 评级为 $ 10 $ 的奶牛对战并获胜。现在 $ a' = [\mathbf{12}， 14， 11， 8， 3] $ 。
- 你的奶牛与 Cowdeforces 评级为 $14$ 的奶牛对战，输掉了比赛。

你的奶牛赢得了 $ 1 $ 场比赛。在第二组数据中，应该将奶牛交换到位置 $ 3 $ 。然后，设 $ a' $ 是交换后顺序中奶牛的 Cowdeforces 评级。

- 最初，$ a' = [7， 2， \mathbf{12}， 10， 727， 13] $ .
- Cowdeforces 评级为 $ 7 $ 的奶牛与Cowdeforces评级为 $ 2 $ 的奶牛对战并获胜。现在 $ a' = [7， \mathbf{12}， 10， 727， 13] $ .
- Cowdeforces 评级为 $ 7 $ 的奶牛与你的奶牛对战，你的奶牛获胜。$ a' = [\mathbf{12}， 10， 727， 13] $ .
- 你的奶牛与 Cowdeforces 评级为 $ 10 $ 的奶牛对战并获胜。现在 $ a' = [\mathbf{12}， 727， 13] $ .
- 你的奶牛与 Cowdeforces 评级为 $727$ 的奶牛对战，输掉了比赛。

你的奶牛赢得了 $ 2 $ 场比赛。

## 样例 #1

### 输入

```
3
6 1
12 10 14 11 8 3
6 5
7 2 727 10 12 13
2 2
1000000000 1```

### 输出

```
1
2
0```

# 题解

## 作者：qusia_MC (赞：4)

dalao们讲的很专业但是不易理解，我给大家讲详细一点。
## 题目描述
有 $n$ 头牛打擂台，你有一个特权可以调换一次位置，请问你最多可以赢几轮？
## 思路分析
首先我们要知道打擂台是个什么玩意。

我们在找最大（小）值的时候，往往都会使用这种方法，就是先定义一个数当擂主然后其他数打擂最后谁存活谁就是胜者。

这个题也差不多，也就是强的牛会强者运强，一直赢下去。所以我们要让我们尽量在第一个，或者前面没有更强的牛，这样才能赢更多场。

------
回归正题，我们首先找的就是“**最靠前**”的威胁。因为如果我们前面有比我们强的牛，那等它打到我们这里时我们就废了，一场也赢不了。

如果“最靠前”的威胁在**我们后面**的话，那就无需顾虑了，直接托关系到第 $1$ 位，这样的话从“第 $2$ 位”一直到“最靠前的威胁”的前一头牛我们一定能全部干趴下。能赢“最靠前的威胁”$-2$ 次（一个 $-1$ 是比赛数量是牛数 $-1$，另一个是“最靠前”的威胁我们不能击败）。

但是，如果最靠前的威胁在我们前面的话，我们如果换到第 $1$ 位的话未必是最佳方案，我们可以把威胁**换走**这样我们就可以打败前面的擂主（一定比我们弱）加上后面直到下一个我们的威胁前面的一头牛。

大体代码（伪程序）：
```
/*输入*/
int p;//就是“最靠前”的威胁
p=1;//初始值为一
while(a[p]>a[k])p++;
if(k<p)
{
    printf("%d",p-2);//卡点不会T，不敢用cout
 }
 else
 {
     printf("%d",max(下一个威胁前面的一头牛-p-1(如果p是1的话这里就不-1了），p-2/*也可以换到第一位*/);
}
```
最后，奉上代码：
```
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[100010];
int main() {
	cin>>t;
	while(t--) 
	{
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		int maxid=1;//“最靠前”的威胁
		while(a[maxid]<=a[k]&&maxid<=n)maxid++;
		int minid=maxid+1;//下一个威胁之前的牛
		while(a[minid]<a[k]&&minid<=n)minid++;
		if(k<maxid) printf("%d\n",maxid-2);
        //直接换到第一位
		else printf("%d\n",max(minid-maxid-1+(maxid==1?0:1),max(maxid-2,0)));
        //统计两种方案的最大值
	}
	return 0;
}
```

---

## 作者：Harrylzh (赞：3)

## 题意

有 $n$ 头牛排成一排在比赛，每只牛有一个能力值。第 $1$ 轮 $1$ 号奶牛和 $2$ 号奶牛比，后面第 $i$ 轮 $i-1$ 轮获胜的奶牛和第 $i$ 只奶牛比。每场比赛能力值高的获胜。你是第 $k$ 只奶牛的主人，你希望你的奶牛获胜的次数尽量多。你现在可以把你的奶牛和任意一头奶牛交换，也可以什么都不做。求你的奶牛获胜的次数的最大值。

## 思路

这是一个打擂台形式的比赛，所以第 $i$ 轮胜出的奶牛一定是前 $i$ 只种能力值最大的。也就是说，如果你的奶牛前面有能力值比它大的，那它就一场也赢不了。所以要尽量让前面没有比它大的。
![](https://cdn.luogu.com.cn/upload/image_hosting/wc80rtzn.png)

如图，$p_1$ 表示第一个能力比 $a_k$ 大的奶牛，$p_2$ 表示 $p_1$ 之后最后一个能力比 $a_k$ 小的奶牛。

考虑两种情况：

- $k < p_1$

- $k>p_1$

如果是第一种情况，则肯定把奶牛交换到第一位是最大的，赢了 $p_1-2$ 场。

如果是第二种情况，有两种选择：

- 交换到第一位，赢 $p_1-2$ 场（如果 $p_1=1$，这种情况赢 $0$ 场）

- 交换到 $p_1$ 位，如果 $p_1=1$，则赢 $p_2-p_1$ 场，否则赢 $p_2-p_1+1$ 场。

在两种情况中取最大值即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long n,k;
long long a[1000000+5];
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&k);
		for(long long i=1;i<=n;i++) scanf("%lld",&a[i]);
		long long p1=1;
		while(a[p1]<=a[k]&&p1<=n) p1++;
		if(k<p1)
		{
			printf("%lld\n",p1-2);
		}
		else
		{
			long long p2=p1;
			while(a[p2+1]<a[k]) p2++;
			if(p1!=1) p2++;
			p2-=p1;
			printf("%lld\n",max(p2,max(p1-2,0ll)));
		}
	}
	return 0;
}
```

---

## 作者：a18981826590 (赞：1)

# [Battle Cows](https://www.luogu.com.cn/problem/CF1951B)
## 解题思路
这道题很简单，分两种情况讨论。

因为只能赢得自己后面的比赛，所以应该把自己换得尽可能靠前。

找到第一头比自己 $a_{k}$ 强的牛 $a_{i}$，如果这头牛在自己后面（$1 \le k<i \le n$），说明从 $1$ 到 $i-1$ 中自己是最大的，把自己换到最前面，自己可以赢得 $i-2$ 场比赛（共 $i-1$ 场比赛，最后一场赢不了）。如果这头牛在自己前面（$1 \le i<k \le n$），把自己换到最前面，自己可以赢得 $i-2$ 场比赛（特别地，当 $i=1$ 时自己可以赢得 $0$ 场比赛）；但把自己换到最前面不一定是最优的,也可以把自己和这头牛交换位置，找到这头牛后面，自己前面第一头比自己强的牛 $a_{j}$，交换位置后从 $i$ 到 $j-1$ 中自己是最大的，自己可以赢得 $j-i$ 场比赛（特别地，当 $i=1$ 时自己可以赢得 $j-2$ 场比赛）；取这两种情况的最大值即可。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],m,n,t,x,y;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		x=1;
		while(a[x]<=a[m]&&x<=n) x++;
		if(m<x){
			cout<<x-2<<'\n';
			continue;
		}
		y=x+1;
		while(a[y]<a[m]&&y<m) y++;
		cout<<max(y-x-bool(x==1),x-2+bool(x==1))<<'\n';
	}
	return 0;
}
```

---

## 作者：Shadow_T (赞：1)

### 题目分析

这是一种比较不同的做法，复杂度 $\mathcal{O}(n\log n \log n)$。

很明显，$a_i$ 可以获胜的分数可以这样计算：

- 如果前面的最大值已经超过 $a_i$ 那么 $a_i$ 直接获胜 $0$ 场。

- 否则，答案为 $a_i$ 后面第一个大于它的值的下标和 $i$ 的距离再减一，因为 $a_i$ 还赢了 $a_{i-1}$ 一场，所以再加一。如果  $a_i$ 后面第一个大于它的值的下标为 $k$，那么答案为 $k-i$，当然 $i=1$ 答案为 $k-i-1$ 因为没有 $a_0$。

然后我们可以线段树维护区间动态最小值，我们可以一个一个把要交换的数枚举过去，在线段树里交换。每次找第一个大于它的值的下标就可以二分：

- 如果 $\operatorname{query\_max}(i+1,m)>a_k$，那么缩小范围，$r=m$。

- 否则扩大范围 $l=m+1$。

想起来比较无脑，但是运行慢，极限大概 $2.7 \times 10^7$ 次运算，似乎喜提最差解（

[通过记录](https://codeforces.com/contest/1951/submission/257035292)。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int bt[maxn*4],a[maxn];
void build(int l,int r,int Node)
{
	if(l==r)
	{
		bt[Node]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(l,mid,Node*2);
	build(mid+1,r,Node*2+1);
	bt[Node]=max(bt[Node*2],bt[Node*2+1]);
}
void update(int l,int r,int Node,int p,int v)
{
	if(l==r)
	{
		bt[Node]=v;
		return;
	}
	int mid=(l+r)/2;
	if(mid<p) update(mid+1,r,Node*2+1,p,v);
	else update(l,mid,Node*2,p,v);
	bt[Node]=max(bt[Node*2],bt[Node*2+1]);
}
int query(int l,int r,int Node,int L,int R)
{
	if(l>=L&&r<=R) return bt[Node];
	int mid=(l+r)/2,ans=0;
	if(mid>=L) ans=max(ans,query(l,mid,Node*2,L,R));
	if(mid<R) ans=max(query(mid+1,r,Node*2+1,L,R),ans);
	return ans;
}
void solve()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	build(1,n,1);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		update(1,n,1,i,a[k]);
		update(1,n,1,k,a[i]);
		//if(i>1)cout<<query(1,n,1,1,i-1)<<"\n";
		if(i>1) if(query(1,n,1,1,i-1)>a[k]) 
		{
			update(1,n,1,i,a[i]);
			update(1,n,1,k,a[k]);
			continue;
		}
		if(i==n)
		{
			update(1,n,1,i,a[i]);
			update(1,n,1,k,a[k]);
			ans=max(ans,1);
			continue;
		}
		int l=i+1,r=n;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(query(1,n,1,i+1,mid)>a[k]) r=mid;
			else l=mid+1;
		}
		int z=l-i-1;
		if(query(1,n,1,l,l)<=a[k]) z=n-i;
		if(i>1) z++;
		ans=max(ans,z);
		update(1,n,1,i,a[i]);
		update(1,n,1,k,a[k]);
	}
	cout<<ans<<"\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve(); 
}
```

---

## 作者：donnieguo (赞：0)

## 题意简述

有 $n$ 头奶牛，第 $i$ 头奶牛的 Cowdeforces 评级为 $a_i$，现在这 $n$ 头奶牛进行 $n-1$ 场比赛，Cowdeforces 评级较高的奶牛进入下一场比赛。你是第 $k$ 头奶牛的主人，现在你有一个特权，可以调换你的奶牛和一只其他奶牛的位置，问你的奶牛最多可以赢得几场比赛。

## 思路

其实这种比赛方式就是类似于我们再区间内查找最大（小）值时使用的打擂法。

- 打擂法：顾名思义，就是每次在擂主和当前遍历到的数中取最大（小）值，最后存活下来的就是这个区间内的最大（小）值。最开始先定义任意一个数当擂主。

比如现在我要在 $a_1 \sim a_n$ 中取最大值：

```cpp
int maxn = a[1];
for (int i = 2; i <= n; i++) maxn = max(maxn, a[i]);
cout << maxn << '\n';
```

`maxn` 即为最大值。

---

那么有了这个打擂法的介绍，我们就很容易发现：

- 如果第 $k$ 头奶牛之前有至少一个 $a_i > a_k(1 \le i \le k)$，那么在不调换位置的情况下，第 $k$ 头奶牛一场比赛都赢不了，因为第 $k-1$ 头将要和第 $k$ 头奶牛打比赛的奶牛一定就是 $\max(a_1\sim a_{k-1})$，而又因为 $a_1\sim a_{k-1}$ 中有 $a_i > a_k$，所以第 $k$ 头奶牛就被无情的淘汰了，并且一场也没赢。

- 如果第 $k$ 头奶牛之前没有任何一个 $a_i > a_k(1\le i \le k)$，那么就很好办了，我们直接~~人情世故~~使用特权，将第 $k$ 头奶牛换到第 $1$ 头，那么第 $k$ 头奶牛能赢的场数应该这么算：

  记从左到右的第一个 $a_i > a_k$ 的 $i$ 为 $p1$ （下同），能赢的场数为 $\max(p1-2, 0)$。
  - $-2$ 是因为 $n$ 头奶牛只能比 $n-1$ 场，而且与 $a_{p1}$ 比的时候赢不了。
  
  - 与 $0$ 取 $\max$ 是因为如果 $p1 = 1$，那么第 $k$ 头奶牛一场都赢不了，但是如果 $1-2$ 就成了 $-1$，不是 $0$。
 
那么现在问题就成了如何考虑 $a_i > a_k(1\le i\le k)$ 的情况。

其实这里我们有两种方案：

- 还是将第 $k$ 头奶牛换到第 $1$ 头的位置，赢 $\max(p1-2, 0)$ 场。

- 将第 $k$ 头奶牛换到第 $p1$ 头奶牛的位置，为了方便说明，我们记 $p2$ 为 $p1$ 之后 $a$ 中最后一个小于 $a_k$ 的值的下标（即 $p1$ 之后第一头 Cowdeforces 评级不小于 $a_k$ 的奶牛），那么奶牛 $k$ 最多能赢的场数应该这么算：

  - 如果 $p1=1$，那么场数为 $p2-p1-1$；
  	
    这里的 $-1$ 是因为如果 $p1=1$，那么其实还是前面一种情况，此时 $p1\sim p2$ 之间有 $p2-p1+1$ 头奶牛，能赢 $p2-p1+1-2 = p2-p1-1$ 场。
  
  - 否则场数为 $p2-p1$。
  	
    这里不 $-1$ 是因为 $p1\sim p2$ 之间有 $p2-p1+1$ 头奶牛，能赢 $p2-p1+1-1=p2-p1$ 场。

最后把上面的情况取一个 $\max$ 即可。
  
为了方便大家理解，我们举两个例子。（此处均省略数据组数）：

样例 $1$：

```
5 3
11 4 5 1 4
```

此时的 $p1=1$，$p2=3$。

第 $3$ 头奶牛最多能赢的场数为 $\max(\max(1-2,0),3-1-1)=1$。

验证：

将第 $3$ 头奶牛和第 $1$ 头奶牛调换位置是最优的。

此时的 $a$ 数组：

```
5 4 11 1 4
```

最多可以赢 $1$ 场。

样例 $2$：

```
6 5
1 9 1 9 8 10
```

此时的 $p1=2$，$p2=4$。

第 $5$ 头奶牛最多能赢的场数为 $\max(\max(2-2,0),4-2)=2$。

验证：

将第 $5$ 头奶牛和第 $2$ 头奶牛换位置是最优的。

此时的 $a$ 数组：

```
1 8 1 9 9 10
```

最多可以赢 $2$ 场。

## AC 代码

```cpp
#include <iostream>
#define N 100010
using namespace std;

int T, n, k;
int a[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n >> k;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		int p1 = 1;
		while (a[p1] <= a[k] && p1 <= n)
			p1++;
		int p2 = p1 + 1;
		while (a[p2] < a[k])
			p2++;
		if (k < p1)
			cout << max(0, p1 - 2) << '\n';
		else
			cout << max(max(p1 - 2, 0), p2 - p1 - 1 + (p1 == 1 ? 0 : 1)) << '\n';
	}
	return 0;
}
```

## 结语

这道题目还是有一定思维难度的。本蒟蒻 WA 了 $7$ 次才 AC ~~（我太菜了）~~。

---

## 作者：niaoji (赞：0)

## 题意
有 $n$ 头奶牛进行单败淘汰赛。你的奶牛位于 $k$，你有交换一次奶牛位置的权利。问你的奶牛最多可以赢几场比赛。
## 分析
能否赢得比赛，关键在于 $CF$ 值，一旦出现 $CF$ 值比我们的奶牛高的情况，比赛就结束了。那么既然想要胜场更多，就要尽可能避开这些“强者”。（以下称“强者”为 $CF$ 值大于第 $k$ 头牛的牛）
“强者”的出现有几种情况：  
1. 在第 $k$ 只奶牛前有 1 个强者。
1. 在第 $k$ 只奶牛前有多个强者。
1. 在第 $k$ 只奶牛前有 1 个强者，在它后面还有多个强者。
## 实现
- 先存入一个数组，再把“强者”们的下标存入另一个数组。
- 处理移位操作。**敲黑板，重头戏来了**
1. 前面没有比他大的——直接把这个 $k$ 移动到第一个位置。
1. 前面有好多个比他大的——取和第一头牛交换或者和第一个强者交换的较大值。
1. 取和第一头牛交换或者和第一个强者交换的较大值。（这个时候，是 $k$ 到 $t_0$ 的距离，而上面是 $t_0$ 到 $t_1$ 的距离）
## 关键代码
```cpp
void solve()
{
	int n,k;
	cin>>n>>k;//n个数字  第k个数字
	vector<int> a(n+1),t;
	for(int i=1; i<=n; i++)
		cin>>a[i];//存入a数组
	for(int i=1; i<=n; i++)
		if(a[i]>a[k]) t.push_back(i);//大于第k的，就存进去（存的是下标）
	if(t.empty())
	{
		cout<<n-1<<"\n";//如果t为空，整个数组里没有比第k个大的
		return;
	}
	if(t.size()==1) //如果只有一个比他大的
	{
		if(t[0]>k) cout<<t[0]-2<<"\n";
		else
			cout<<max(t[0]-2,k-t[0]-1+(t[0]!=1))<<"\n";
		return;
	}
	if(t[0]>k) //前面没有比他大的（那就把第k个移动到第一个）
		cout<<t[0]-2<<"\n";
	else if(t[1]<k)  //前面有好几个大的
		cout<<max(t[0]-2,t[1]-t[0]-1+(t[0]!=1))<<"\n";
	else  //这是卡在第一个和第二个之间对吧？
		cout<<max(t[0]-2,k-t[0]-1+(t[0]!=1))<<"\n";
}
```

---

## 作者：HasNoName (赞：0)

### 思路

如果将 $a_i$ 和 $a_k$ 交换，则 $a_i$ 之前没有比 $a_k$ 大的数，否则答案为零。

枚举每一个 $i$，对 $a_i>a_k$ 和 $a_i\le a_k$ 分类讨论，若 $i>1$ 且 $a_{i-1}>a_k$ 则停止枚举。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int a[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T,n,k;
    cin>>T;
    while(T--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]>a[k])//分类讨论
            {
                if(i>k)break;//当i>k时，交换后答案是零
                for(int j=i+1;j<=n;j++)//a[i]后面的数
                {
                    if(a[j]>a[k]||j==k)//a[j]>a[k]
                    {
                        if(i==1)j--;//当i=1时答案要减一
                        ans=max(ans,j-i);//j-i-1+1，a[i]前面算一个(i>1)
                        break;
                    }
                }
                break;
            }
            ans=max(ans,i-1);//当a[i]<=a[k]时，因为对于1<=j<=i，a[j]<=a[k]，所以答案为i-1
        }
        cout<<ans<<'\n';
    }
    return 0;
}

```

---

## 作者：___nyLittleT___ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1951B)  
## 题意
$n$ 头奶牛打排位，从前往后，以前一组的获胜者与当前奶牛打比赛。你的奶牛是 $k$ 号，它最多能打赢多少场。  
## 思路
按照比赛规则，我们知道如果 $k$ 前面的战斗力有大于 $a_k$ 的，那它一局也别想赢。  
考虑两个变量 $firstbig$ 和 $lastsmall$，顾名思义，$firstbig$ 代表第一个战力值大于 $a_k$ 的奶牛。以下简称 $fb$。$lastsmall$ 代表最后一个比 $a_k$ 小的。以下简称 $ls$。  
如果 $a_k<fb$，答案为 $fb-2$。  
否则答案为以下两种情况的最大值：  
- 找关系换到第一位，答案为 $ls-fb$。
- 佛系，啥也不干，一切随缘，答案为 $\max\{fb-2,0\}$。  
按要求输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k,n;
int a[100005];
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		int fb=0,ls=0;
		while(a[fb]<=a[k]&&fb<=n) fb++;
		ls=fb+1;
		while(a[ls]<a[k]) ls++;
		if(fb!=1) ls++;
		if(k<fb) printf("%d\n",fb-2);
		else printf("%d\n",max(ls-fb-1,max(fb-2,0)));
	}
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1951B
## 题意
有 $n$ 头奶牛，第 $i$ 头奶牛有一个能力值 $a_{i}$，现在有 $n-1$ 场比赛，第一轮的参加者为 第 $1$ 头奶牛和第 $2$ 头奶牛，第 $i$ 场比赛的参加者为 第 $i-1$ 场比赛的获胜者和第 $i+1$ 头奶牛。每场的获胜者为能力值更大的那头奶牛。你是第 $k$ 头奶牛的主人，你可以将你的奶牛与任意一头奶牛调换位置，问最终获胜的场数最多是多少。
## 思路
本题是一道找规律的题目。我们可以发现，如果第 $k$ 头奶牛前面的奶牛的能力值有比它大的，不调换位置获胜场数将为 $0$。于是我们可以顺着这个思路想下去：

- 当第 $k$ 头奶牛前面的奶牛的能力值有比它大的，我们只能与第一头能力值比它大的奶牛交换位置，然后统计胜利场数即可。

- 当前面的奶牛的能力值都比第 $k$ 头奶牛小，为了让获胜场数更多，与第一头奶牛交换位置，然后统计胜利场数即可。

为了使代码更简单，我们可以记录第 $k$ 头奶牛前第一个能力值比它大的编号，以及第二个能力值比它大的编号，再记录第 $k$ 头奶牛后第一头能力值比它大的编号，最后分类讨论即可。

最后要注意交换后位置是否为 $1$，是的要把答案减掉一。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t,n,k,a[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		int f1=0,f2=0,f3=0,sum=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<k;i++){
			if(a[i]>a[k]){
				sum++;
				if(sum==1)f1=i;
				if(sum==2)f2=i;
			}
		}
		for(int i=k+1;i<=n;i++){
			if(a[i]>a[k]){
				f3=i;
				break;
			}
		}
		if(!f1){//前面一个也没有比它大 
			if(f3)cout<<f3-2<<endl;
            else cout<<n-1<<endl;
		}else if(!f2){//只有一个比它大 
			if(f1==1)cout<<max(max(0,f1-2),k-f1-1)<<endl;
            else cout<<max(max(f1-2,0),k-f1)<<endl;
		}else{//有两个及以上 
			if(f1==1)cout<<max(max(f1-2,0),f2-f1-1)<<endl;
            else cout<<max(max(f1-2,0),f2-f1)<<endl;
		}
	}
	return 0;
}
```

---

