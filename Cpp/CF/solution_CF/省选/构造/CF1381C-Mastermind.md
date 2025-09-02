# Mastermind

## 题目描述

In the game of Mastermind, there are two players — Alice and Bob. Alice has a secret code, which Bob tries to guess. Here, a code is defined as a sequence of $ n $ colors. There are exactly $ n+1 $ colors in the entire universe, numbered from $ 1 $ to $ n+1 $ inclusive.

When Bob guesses a code, Alice tells him some information about how good of a guess it is, in the form of two integers $ x $ and $ y $ .

The first integer $ x $ is the number of indices where Bob's guess correctly matches Alice's code. The second integer $ y $ is the size of the intersection of the two codes as multisets. That is, if Bob were to change the order of the colors in his guess, $ y $ is the maximum number of indices he could get correct.

For example, suppose $ n=5 $ , Alice's code is $ [3,1,6,1,2] $ , and Bob's guess is $ [3,1,1,2,5] $ . At indices $ 1 $ and $ 2 $ colors are equal, while in the other indices they are not equal. So $ x=2 $ . And the two codes have the four colors $ 1,1,2,3 $ in common, so $ y=4 $ .

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1381C/0a0bf21772b2a037969dab6b2775ca2f40f3672c.png) Solid lines denote a matched color for the same index. Dashed lines denote a matched color at a different index. $ x $ is the number of solid lines, and $ y $ is the total number of lines. You are given Bob's guess and two values $ x $ and $ y $ . Can you find one possibility of Alice's code so that the values of $ x $ and $ y $ are correct?

## 说明/提示

The first test case is described in the statement.

In the second test case, $ x=3 $ because the colors are equal at indices $ 2,4,5 $ . And $ y=4 $ because they share the colors $ 1,1,1,2 $ .

In the third test case, $ x=0 $ because there is no index where the colors are the same. But $ y=4 $ because they share the colors $ 3,3,5,5 $ .

In the fourth test case, it can be proved that no solution exists.

## 样例 #1

### 输入

```
7
5 2 4
3 1 1 2 5
5 3 4
1 1 2 1 2
4 0 4
5 5 3 3
4 1 4
2 3 2 3
6 1 2
3 2 1 1 1 1
6 2 4
3 3 2 1 1 1
6 2 6
1 1 3 2 1 1```

### 输出

```
YES
3 1 6 1 2
YES
3 1 1 1 2
YES
3 3 5 5
NO
YES
4 4 4 4 3 1
YES
3 1 3 1 7 7
YES
2 3 1 1 1 1```

# 题解

## 作者：Singercoder (赞：7)

# 序

（一道很考验思维质量的构造好题，而且需要注意的细节也很多。）

本题解主体使用的是简洁且小常数的$O(nlogn)$时间复杂度代码，并且包含其他方法的分析留给读者自行实现（~~其实是自己不会写或者写崩了~~）。

**后记有$O(n)$时间复杂度的~~反向~~优化。**

# 题意

共t组数据，每组数据第一行是n,x,y，其中n表示数列规模。接下来一行是n个数表示数列，要求输出任意一个数列，它与原数列满足：

+ 有x个数字位置相同且大小相同

+ 打乱原数列顺序后，最多能有y个元素位置相同且大小相同。

# 转义

为方便分析，这里对题目进行转义，我们认为**新数列是由原数列变换位置后得到的**，并**重新定义**下列字母：

+ $x$表示位置不变的数字个数
+ $y$表示新旧位置在原数列的对应位置上，颜色不同的数字个数
+ $z$表示舍弃的数字个数。

```cpp
	n=read();
	x=read();
	y=read()-x;
	z=n-x-y;
```

解释一下**舍弃**：存在可以舍弃掉的数字，其原因在于颜色总值域为[1,n+1]，故必然存在原数组颜色值域以外的颜色(记为$off$)，$x$和$y$按规则变换位置后，剩余位置填上$off$即可。

体现在原数组里面就相当于有 $z$个元素被舍弃。

# 分析

$x$是位置不变，$z$是直接舍弃，显然这二者都不涉及到有无解的问题。

而$y$要求新旧位置必须颜色不同，这一点可能无法满足，所以我们重点分析这$y$个数字的选取和转移。

而且非常容易被错误理解的一点是：在选定$y$个数字后，我们的转移终点并不一定必须也在这$y$个数字的位置上。显然$x$的位置是无法作为终点的，但$z$反正被舍弃，**其留下的空位置便可以作为终点**！

## 定性选取

不难发现：在所选的$y+z$个数字中，频数最大的颜色频数越小，越容易有解。

通俗来讲就是颜色分布越多样、均匀，越容易有解。

因为如果某一种颜色过多，就可能导致$y$没有足够的转移终点。

因此第一步就是贪心地去均匀选数，可以用堆选取$x$个数字使得剩余数字的颜色的最大频数尽可能小（$nlogn$），也可以直接开个二维vector如下均匀选取（排序也要$nlogn$）

```cpp
struct color
{
	int col,id;
	color(int C=0,int I=0):col(C),id(I){}
};

struct cmp1
{
	bool operator () (const vector<color> &x,const vector<color> &y)
	{
		return x.size()>y.size();
	}
};

	n=read();
	x=read();
	y=read()-x;
	z=n-x-y;
	
	//将输入存储于二维vector中 
	for(ri i=1;i<=n;++i)a[i]=read();
	
	vector<vector<color> > vec(n+1);
	
	for(ri i=1;i<=n;++i)
		vec[a[i]-1].push_back(color(a[i],i));
	
	sort(vec.begin(),vec.end(),cmp1());
	while(!vec.back().size())vec.pop_back();
	
	//尽可能多样地选取y+z个col 
	vector<color> arr;
	
	for(ri i=1,p=0;i<=y+z;++i)
	{
		arr.push_back(vec[p].back());
		vec[p].pop_back();
		if(++p==vec.size())
		{
			while(vec.size() && !vec.back().size())vec.pop_back();
			p=0;
		}
	}
```

## 定量判断

可对于选出的$y+z$个数字，我们如何定量判断是否无解？

记其中颜色的最大频数为$maxcnt$

则它们还需要颜色不同的$maxcnt$个终点进行转移

故若$maxcnt*2-(y+z) \le 0$必然有解

但需要注意的是：

1. 仅当频数超过$\lfloor {{y+z} \over 2} \rfloor$上式才有可能$>0$，故最多只有有一种颜色存在这样的风险。

2. 并不是所有$maxcnt$个数字都必须有转移终点 ，我们完全可以舍弃其中的$z$个数字不作转移，**但它们留下的空位置并不能作为剩余同颜色数字的转移终点**，故若$0 < maxcnt*2-(y+z) \le z$则也有解。

   (如果不容易理解可以画图：在长为$y+z$的区间上，$maxcnt*2$相当于顶着区间两端各放一条线段，减去$y+z$的区间总长，得到的是两线段的重叠部分，这便是必须舍弃的部分)

综上：若$maxcnt*2-(y+z) \le z$则有解，反之无解。

```cpp
	//统计个数，获得各颜色个数排名
	int maxcnt=0,off;
	
	for(ri i=1;i<=n+1;++i)cnt[i]=0;
	for(ri i=0;i<arr.size();++i)++cnt[arr[i].col];
	
	for(ri i=1;i<=n+1;++i)
	{
		if(cnt[i])maxcnt=max(maxcnt,cnt[i]);
		else off=i;
	}
	if(maxcnt*2-(y+z)>z){printf("NO\n");return;}
```

## 构造转移

这是一个卡了我很久的点（~~主要是我看了ltao的题解发现他直接一笔带过就很离谱~~）

我们费尽功夫选好了$y+z$个点，判断出了有无解，可真到了构造转移的时候应该怎么处理。

显然前面没选的$x$个数字原地tp即可，不在话下。

对于选好的$y+z$个数字，最初的想法如下：

1. 颜色集中分布，按颜色频数从小到大排序。（$logn$）
2. 对于频数最大的颜色，我们优先处理它的转移终点，若$maxcnt*2-(y+z) \le 0$则不必动用舍弃名额，直接 在剩余颜色里面按频数从小到大选就可以；否则就舍弃$maxcnt*2-(y+z)$个。
3. 对于剩余颜色，按频数从大到小处理，每种颜色的转移终点从比频数比它大的里面选（可以用queue存储频数比它大的位置），由于上一步是从小到大选的故这一步必然有解。
4. 如果有剩余的舍弃名额就随便舍。

正确性显然，但代码实现繁琐，留给读者自行思考。

---

然后在这里分析一下[ltao的构造思路](https://www.luogu.com.cn/blog/lov-kyn/solution-cf1381c)（确实很妙，我也加入了一些自己的理解）：

首先注意在上一步的代码中我们已经将arr按颜色集中分布。

记录两个指针$i,j$，分别表示转移的**终点和起点**。（注意顺序）

初始化$i=0,j=maxcnt$，令它们有$maxcnt$的初始间隔，见下例（没选的$x$个已省略，$y=5,z=2$）

| arr.col​ | 1    | 2    | 2    | 2    | 2    | 3    | 3    |
| ------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 指针i​   | i​    |      |      |      |      |      |      |
| 指针j​   |      |      |      |      | j​    |      |      |
| b​       |      |      |      |      |      |      |      |

若$i,j$对应颜色不同，则设置转移并记录在新数列中，由于初始间隔的存在，**不难证明当$i$和$j$任意一者对应颜色不是频数最大的颜色时，必然可以转移**，即$i,j$同时向右移动（注意$j$在$arr.end()$时的取模）即可；

而需要特殊处理的是$i,j$对应颜色相同的情况，如下例：

| arr.col​ | 1    | 2    | 2    | 2    | 2    | 3    | 3    |
| ------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 指针i​   |      |      |      |      | i​    |      |      |
| 指针j​   |      | j​    |      |      |      |      |      |
| b​       | 2    | 3    | 3    | 1    |      |      |      |

此时我们保持起点$j$不动，继续寻找终点$i$直至可行（可见，途径不可行的都是**被舍弃的终点**）：

| arr.col​ | 1    | 2    | 2    | 2    | 2    | 3    | 3    |
| ------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 指针i​   |      |      |      |      |      | i​    |      |
| 指针j   |      | j​    |      |      |      |      |      |
| b​       | 2    | 3    | 3    | 1    | 4​    | 2    |      |

直到每一个终点都被尝试过，结束算法。可见由于$j$的停滞，同样存在一些**被舍弃的起点**：

| arr.col​ | 1    | 2    | 2    | 2    | 2    | 3    | 3    |
| ------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 指针i​   |      |      |      |      |      |      | i​    |
| 指针j​   |      |      | j​    |      |      |      |      |
| b​       | 2    | 3    | 3    | 1    | 4​    | 2    | 2    |

该算法核心就在于初始间隔$maxcnt$的设置能够很好地处理非最大频数颜色的转移；而面对最大频数颜色的冲突，我们也可以通过$j$的停滞来舍弃**最大频数颜色**末尾的部分数字，以保证有解。（~~啥也别说了都快去%[ltao](https://www.luogu.com.cn/user/232125)~~）

upd[2020.7.23]：如果还是不太懂（~~有可能是因为luogu表格炸了看不清~~，[点击以获取更好的阅读体验](https://www.cnblogs.com/-SingerCoder/p/13367166.html)），就体会一下ltao的原话：

>前面你判了一定有解对吧
>
>所以之后只需要排序 然后 肯定会有解的
>
>所以 你只要把这个排好序的序列平移 一半（即maxcnt）
>
>注意 这个平移还是要留下之前的索引
>
>然后可以保证排好序的数组至少ok
>
>那么，按照你存的索引直接找回去就OK

这应该是ltao最初从宏观角度思考的算法思路了，还不明白可以看代码

```cpp
struct cmp2
{
	bool operator () (const color &x,const color &y)
	{
		return cnt[x.col]!=cnt[y.col] ? cnt[x.col]>cnt[y.col] : x.col>y.col;
	}
};

	//填入y+z个元素的b
	for(ri i=1;i<=n;++i)b[i]=0;
	sort(arr.begin(),arr.end(),cmp2());
	
	for(ri i=0,j=maxcnt,sz=arr.size();i<sz;++i)
	{
		if(j<maxcnt+y && arr[i].col!=arr[j%sz].col)
			b[arr[i].id]=arr[(j++)%sz].col;
		else
			b[arr[i].id]=off;
	}
	
	//输出b
	printf("YES\n");
	for(ri i=1;i<=n;++i)
	{
		put(b[i] ? b[i] : a[i]);
		pc(' ');
	}
	pc('\n');
```

# 后记

在实现了上述代码并成功$AC$后，你发现代码中有两个$sort$格外显眼：

1. 给二维vector按照一维的size排序（选数阶段）
2. 给arr按照颜色集中分布的排序（转移阶段）

这个2很好处理，因为我们转移时，没有必要特意按频数排序，只要颜色集中就可以（~~看见我上面给的那个样例故意没排序了吗~~），这一点可以在统计颜色的时候处理。

```cpp
	//统计个数，获得maxcnt，并将arr按颜色集中分布 
	int maxcnt=0,off;
	
	vector<vector<color> > tarr(n+1);
	while(arr.size())
	{
		tarr[arr.back().col-1].push_back(arr.back());
		arr.pop_back();
	}
	
	for(ri i=0;i<n+1;++i)
	{
		if(tarr[i].size())
		{
			maxcnt=max(maxcnt,(int)tarr[i].size());
			while(tarr[i].size())
			{
				arr.push_back(tarr[i].back());
				tarr[i].pop_back();
			}
		}
		else off=i+1;
	}
	
	if(maxcnt*2-(y+z)>z){printf("NO\n");return;}
```

至于1确实不易实现，因为会有size相同的一维vector，所以我们再给它开个桶（~~给桶桶排的桶应该叫啥？桶的桶？二阶桶？~~）

```cpp
	//将输入存储于二维vector中 
	for(ri i=1;i<=n;++i)a[i]=read();
	
	vector<vector<color> > vec(n+1);//二维vector 桶 
	vector<vector<vector<color> > >tax(n);//三维vector 桶的桶（笑） 
	
	for(ri i=1;i<=n;++i)
		vec[a[i]-1].push_back(color(a[i],i));
	
	while(vec.size())//这桶排写得属实烧脑 
	{
		if(vec.back().size())
			tax[vec.back().size()-1].push_back(vec.back());
		vec.pop_back();
	}
	for(ri i=n-1;i>=0;--i)
	{
		while(tax[i].size())
		{
			vec.push_back(tax[i].back());
			tax[i].pop_back();
		}
	}
```

然后踌躇满志地提交，你会发现：

上文$O(nlogn)$[提交记录](https://www.luogu.com.cn/record/35573970)

线性$O(n)$[提交记录](https://www.luogu.com.cn/record/35585775)

”喂这什么情况啊这波怎么成了反向优化了“

“废话分析分析常数不就知道了”

~~事实证明sort的常数还是很优的~~

---

## 作者：water_tomato (赞：2)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1381c-mastermind-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1381C)。

给你一个序列 $a$，让你输出一个序列 $b$ ，这个 $b$ 满足跟 $a$ 有 $x$ 个位置上的元素一样。有 $y$ 个元素跟 $a$ 里边的元素一样。值域是 $1\le v \le n+1$。

## 解析

先考虑这么一件事情：假如你已经确定了这 $x$ 个位置是什么，那么问题转化为：你需要将若干个元素交换位置，使得与原来元素相同的位置不超过 $n-y$ 个（由于值域为 $[1,n+1]$，一定存在一个合法的且没有在 $a$ 中出现过的元素）。

对于这个问题，我们可以将相同的元素相邻排列，例如得到一个序列 $[1,1,1,2,2,2,3,3,4]$，我们记其中最长的相同元素长度为 $l$（例如在上述序列中，$l=3$），然后将所有元素向右平移 $l$ 个单位。

然后我们发现，答案不合法当且仅当 $l$ 大于序列长度的一半。换言之，我们需要使最长的相同元素最短，这样我们对于选定的 $x$ 个位置，只需要一直选择当前最多的那种元素即可，这可以通过优先队列实现。

对于剩下的元素，我们可以在排列元素时按从多至少排列（上述例子序列就符合这一点），这样的话最终若不合法，不合法元素一定出现在序列的最前面，因此我们只需要强令序列的前 $n-y$ 个元素为那个未出现过的元素，其余位置依照平移法则即可。若仍然不符合要求，则输出 `NO`。

## 代码

```cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define fi first
#define se second
#define mk make_pair
using namespace std;
const int N=1e5+5;
int T,n,x,y,a[N],ans[N],K;
pi b[N];
struct node{
	int cnt;
	queue<int> q;
}c[N];
priority_queue<pi> q;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&x,&y);
		while(!q.empty()) q.pop();
		for(int i=1;i<=n+1;i++){
			c[i].cnt=0;
			while(!c[i].q.empty()) c[i].q.pop();
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			c[a[i]].cnt++;c[a[i]].q.push(i);
		}
		for(int i=1;i<=n+1;i++){
			q.push(mk(c[i].cnt,i));
			if(!c[i].cnt) K=i;
		}//将每个元素放在一起，并找出未出现的元素
		for(int i=1;i<=x;i++){
			pi t=q.top();
			int u=t.se;q.pop();
			ans[c[u].q.front()]=u;
			c[u].q.pop();
			if(t.fi!=1) q.push(mk(t.fi-1,t.se));
		}//优先选择最多的 x 个元素
		int now=1,l=q.top().fi;
		while(!q.empty()){
			pi t=q.top();q.pop();
			int u=t.se;
			while(!c[u].q.empty()){
				b[now]=mk(u,c[u].q.front());
				c[u].q.pop();now++;
			}
		}//其他元素重新排列
		for(int i=1;i<=n-y;i++){
			ans[b[i].se]=K;
		}//强行处理前 n-y 个
		for(int i=n-y+1;i<=n-x;i++){
			int pos=i-l;if(pos<=0) pos+=n-x;
			ans[b[i].se]=b[pos].fi;
		}//其余的遵循平移法则
		int cnt=0;
		for(int i=1;i<=n;i++) if(ans[i]==a[i]){cnt++;}
		if(cnt>x){printf("NO\n");}
		else{
			printf("YES\n");
			for(int i=1;i<=n;i++) printf("%d ",ans[i]);
			printf("\n");
		}
	}
	return 0;
}
```



---

## 作者：Z1qqurat (赞：1)

观察一下，将 $b$ 中的数分为三类：

* $b_i=a_i$ 的，共 $x$ 个。
* $b_i=a_j,b_j\ne a_j$，共 $y-x$ 个。
* $b_i$ 在 $a$ 中没出现过（其实这种不一定要卡这么严，但是这样构造比较无脑）。

问题在于前两类的分配。先不管第一种，考虑如果已经确定了第二种里面的是哪些 $j$，怎么分配最好。不难想到一种贪心，就是把剩下的位置将 $a_j$ 相同的放到一块里面，然后按照块 size 从大到小处理。每次处理一个颜色块的时候，肯定是尽量用它后面的颜色来填充，填不了就用前面的。所以开两个 set，$pre,nxt$ 分别表示当前颜色块前后的位置集合，贪心地取。感性理解这样很优。

然后就是怎么确定第一类的位置。一开始有一个很 naive 的想法，就是尽量取 $a_i$ 出现次数多的，但是会被卡掉：

```
5 3 4
1 1 2 1 2
```

调整一下，发现如果第二类数中每种颜色的 size 尽可能平均，且颜色种类尽量多，那么会更优。所以选第一类数的时候合理安排，使得留下的第二类数颜色块平均，避免一家独大的情况就可以了。

具体实现细节很多，注意 vector 和 set 等 STL 的正确使用。

[Submission.](https://codeforces.com/contest/1381/submission/267144853)

---

## 作者：tzc_wk (赞：1)

首先，读完题目我们可以很自然地产生这样一个感觉：当 $y$ 固定时，肯定是 $x$ 越大，越有可能存在合法的解，因此我们肯定每次会想着贪心匹配出现次数最多的数。

我们不妨先考虑以下弱化版本：$x=0,y=n$，那么显然，如果出现次数最多的数的出现次数乘 $2$ 大于 $n$ 那答案就是 NO，否则我们将所有数按照其出现次数排成一排，譬如 $1,2,3,1,2,1,2$ 排成一排就是 $2,2,3,3,1,1,1$，然后我们先用**出现次数最多的数去匹配前面的数，然后对于出现次数不是最多的数，我们就按照它们在上述序列中的顺序依次往上填**，譬如在上面的例子中，填出来的序列就是 $1,1,1,2,2,3,3$，然后对应位置上的数依次匹配即可。

接下来考虑原问题，根据上面的推论，我们肯定希望出现次数最多的数的出现次数尽可能小，因此对于 $x$​ 个 $a_i=b_i$​ 的 $i$​，我们肯定会尽量选择出现次数最多的值，这个可以 set 维护。比较困难的是 $n-y$ 个不出现在原序列中的数即可，由于我们可以填的数的范围为 $[1,n+1]$，因此必然存在一个数 $\in[1,n+1]$ 且没有在 $a$ 中出现过，我们假设该数为 $X$，记 $mx$ 为 $a$ 序列中出现次数最多的数的出现次数，那么可以发现，如果 $(n-x-mx)+(n-y)<mx$，那答案就是 NO，否则，我们还是将剩余未被匹配的数按照上面的方式排成一列，即 $1,2,3,1,2,1,2$ 排成 $2,2,3,3,1,1,1$，然后我们从后往前填 $X$，有多少个 $n+1$ 就填多少个，然后对于出现次数最多的数，我们从前往后填，填到出现次数最多的数用完了或者下一个匹配的数就是出现次数最多的数为止，然后对于剩余的数，再按照顺序填补剩余的空位，这样说的可能不太清楚，举个例子，如果序列为 $1,2,2,3,3,3,3,3$，且 $n-y=2$​，那么我们先从后往前填两个 $X$，现在 $b$ 序列变为 $?,?,?,?,?,?,X,X$，然后我们从左往右填 $3$，填上 $3$ 个 $3$ 以后序列变为 $3,3,3,?,?,X,X$，由于如果我们在第四个问号处填 $3$ 就会出现自己与自己匹配的情况，因此我们只能填三个 $3$，最后填补剩余空位，除去出现次数最多的数之后，剩余的序列是 $1,2,2$，我们就按顺序填即可，得到 $3,3,3,1,2,X,X$，符合题意。

时间复杂度 $n\log n$。

```cpp
const int MAXN=1e5;
int n,x,y,a[MAXN+5],cnt[MAXN+5],res[MAXN+5],ord[MAXN+5];
queue<int> q[MAXN+5],tq[MAXN+5];
void solve(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n+1;i++){
		cnt[i]=0;res[i]=0;
		while(!q[i].empty()) q[i].pop();
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),cnt[a[i]]++,q[a[i]].push(i);
	int nt=0;for(int i=1;i<=n+1;i++) if(!cnt[i]) nt=i;
	multiset<pii> st;
	for(int i=1;i<=n+1;i++) if(cnt[i]) st.insert(mp(cnt[i],i));
	for(int i=1;i<=x;i++){
		pii p=*st.rbegin();st.erase(st.find(p));
		int c=p.se,id=q[c].front();q[c].pop();
		res[id]=c;p.fi--;if(p.fi) st.insert(p);
	} int sum=0,mx=0;
	for(int i=1;i<=n+1;i++) if(q[i].size()>mx) mx=q[i].size();
	for(int i=1;i<=n+1;i++) ord[i]=i;
	if((n-x-mx)+(n-y)<mx) puts("NO");
	else{
		puts("YES");
		sort(ord+1,ord+n+2,[&](int x,int y){return q[x].size()>q[y].size();});
		for(int i=1;i<=n+1;i++) tq[i]=q[i];
		int nd=n-y;
		for(int i=1;i<=n+1;i++){
			int x=ord[i];
			while(nd&&!q[x].empty()){
				int id=q[x].front();q[x].pop();
				res[id]=nt;nd--;
			}
		}
		int x=ord[1],cur=n+1;
		while(!q[x].empty()){
			while(!tq[ord[cur]].empty()&&!q[x].empty()){
				int P=tq[ord[cur]].front();tq[ord[cur]].pop();
				int Q=q[x].front();q[x].pop();res[Q]=ord[cur];
			} cur--;
		}
		cur=0;vector<int> seq;
		for(int i=1;i<=n+1;i++){
			int x=ord[i];
			while(!tq[x].empty()){
				int y=tq[x].front();tq[x].pop();
				seq.pb(x);
			}
		} //printf("%d\n",seq.size());
		for(int i=2;i<=n+1;i++){
			int x=ord[i];
			while(!q[x].empty()){
				int id=q[x].front();q[x].pop();
				res[id]=seq[cur++];
			}
		}
		for(int i=1;i<=n;i++) printf("%d%c",res[i]," \n"[i==n]);
	}
}
int main(){
	int qu;scanf("%d",&qu);
	while(qu--) solve();
	return 0;
}
```

---

## 作者：_LanFeng_ (赞：1)

如果图片炸了可以[点击](https://www.cnblogs.com/dingxingdi/p/15460102.html)

首先观察题目，发现题目要求 $x$ 个一模一样的数

因为这 $x$ 个数是定下来的，所以从这里突破

假设已经选择了 $x$ 个数，还剩下 $n-x$ 个数，我们的目标是从中取出 $y-x$ 个数，然后让这些数在这 $n-x$ 个位置里面移动，直到这 $y-x$ 个数不与原序列上的数一样，然后剩下的 $n-y$ 个数用这个序列里没有出现的那个数填上即可

首先判断是否有解

我们将剩下的这 $n-x$ 个数按照个数排序，让出现次数更多的一种数排在后面，如果两种数出现次数相同，则按编号排序

举个例子，样例：

```
5 2 4
3 1 1 2 5
```


假设我们选了前两个数作为 $x$ 个数，那么还剩下

```
1 2 5
```


其中 $1$ 、$2$ 、$3$ 的个数都是1（都只出现了一次）

如果我们选择第一个数和第四个数作为 $x$ 个数，那么还剩下

```
1 1 5
```


排序之后变为（分别出现了两次和一次）

```
5 1 1
```
 

换个普遍的，抽象的图

![](https://img2020.cnblogs.com/blog/2490134/202110/2490134-20211025191008605-1899956601.png)

假设这是已经排好序了的数组，颜色表示不同数字，长方形的长度代表这种数字的出现次数

我们将其按照这种方式进行重排序：

![](https://img2020.cnblogs.com/blog/2490134/202110/2490134-20211025191256109-296817785.png)

即将最后一种数字放到最前面，剩下的数字之间的相对顺序不变，然后依次放在后面

注意，现在表示的意义：与原来的长方形相比，所相对的数字的位置该放的数

我知道说了听不懂，所以举个例子

假设原数组

```
1 2 2 3 3 3

```

排序后：

```
3 3 3 1 2 2
```


代表的意思就是原来放1的位置（第一个位置）现在放3；原来两个放2的位置（第二个位置和第三个位置）现在放了两个三；原来放3的位置（第四五六个位置）现在放了一个1（第四个位置）和两个2（第五六个位置），一 一对应

如果此时最长的一个长方形的长度没有超过总长度的一半，很显然就是一个可行解

如果超过了一半，比如下图

![](https://img2020.cnblogs.com/blog/2490134/202110/2490134-20211025192041083-680411778.png)

由于我们还有 $n-y$ 个位置可以填充，那么就会变成下面这个样子

![](https://img2020.cnblogs.com/blog/2490134/202110/2490134-20211025192129561-603319706.png)

如果这 $n-y$ 个位置让最长的长方形的长度在减小后不在超过总长度的一半，那么此时也是一个解

如果再加上了这 $n-y$ 个位置之后最长的长方形的长度都还超过了一半，那么就肯定无解了

请认真思考为什么这种放置和重新排序一定是最优的（即不可能存在另一种方式使得在我们这种策略无解的情况下有解）

那么我们只需要限制每个长方形的长度取数即可

有许多细节，建议好好写代码

下面给出参考代码

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
int n;
int a[N];
int pot[N],tot[N],cnt[N],ans[N];
int num;
vector<int> pos[N];
bool vis[N],mark[N];
void init()
{
	num=0;
	for(int i=1;i<=n+1;i++) vis[i]=mark[i]=cnt[i]=tot[i]=pot[i]=0;
	for(int i=1;i<=n+1;i++) pos[i].clear();
}
int read()
{
	int x=0,f=1;char s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-') f=-f;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=x*10+s-48;
		s=getchar();
	}
	return x*f;
}
bool cmp(int i,int j)
{
	if(tot[a[i]]==tot[a[j]]) return a[i]<a[j];
	return tot[a[i]]<tot[a[j]];
}
int main()
{
	int t=read();
	while(t--)
	{
		n=read();
		int x=read(),y=read();
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			vis[a[i]]=1;
			pos[a[i]].push_back(i);
			cnt[a[i]]++;
		}
		int temp=n-x;
		for(int i=1;i<=n+1;i++)
		if(vis[i])
		{
			if(temp>min((n+n-y-x>>1),cnt[i]))
			{
				temp-=min((n+n-y-x>>1),cnt[i]);
				tot[i]=min((n+n-y-x>>1),cnt[i]);
			}
			else
			{
				tot[i]=temp;
				temp=0;
				break;
			}
		}
		if(temp)
		{
			printf("NO\n");
			init();
			continue;
		}
		for(int i=1;i<=n+1;i++)
		for(int j=1;j<=tot[i];j++)
		pot[++num]=pos[i][j-1];
		sort(pot+1,pot+num+1,cmp);
		for(int i=num,j=num-tot[a[pot[num]]];j;i--,j--)
		ans[pot[i]]=a[pot[j]],mark[pot[i]]=1;
		for(int j=1;j<=tot[a[pot[num]]];j++)
		ans[pot[j]]=a[pot[num]],mark[pot[j]]=1;
		for(int i=1;i<=n+1;i++)
		if(!vis[i])
		{
			temp=i;
			break;
		}
		if(tot[a[pot[num]]]>n-y)
		for(int i=tot[a[pot[num]]]-n+y+1;i-(tot[a[pot[num]]]-n+y+1)<n-y;i++)
		ans[pot[i]]=temp;
		else 
		for(int i=1;i<=n-y;i++)
		ans[pot[i]]=temp;
		for(int i=1;i<=n;i++)
		if(!mark[i])
		{
			x--;
			ans[i]=a[i];
			mark[i]=1;
			if(!x) break;
		}
		printf("YES\n");
		for(int i=1;i<=n;i++) printf("%d ",ans[i]);
		puts("");
		init();
	}
	return 0;
}
```

---

## 作者：Anita_Hailey (赞：1)

### 题意分析：

给你一个序列 $a$，让你输出一个序列 $b$ ，这个 $b$ 满足跟 $a$ 有 $x$ 个位置上的元素一样。有 $y$ 个元素跟 $a$ 里边的元素一样。值域是 $1\le v \le n+1$

### 解题报告：

当时 就差一点点就出来了 qwq。

假定我们找出了 $y$  个元素了那么，观察这个 $n+1$ 的值域，发现这个东西 a 序列里一定有一种元素没有，那么我们把这个元素 $mx$ 找出来，然后，剩下的 $n-y$ 个位置都是 $mx$，再考虑如何去找出这个 y 个元素。

首先，我们确定一下 $x$ 个元素，就是位置也要一模一样，贪心的想，我对于所有元素，留下来的一种元素的个数最大值最小最好，所以，用一个大根堆去存一下每个长度，然后只要每次找出最长的就好了，这个过程重复 $x$ 次。

考虑剩下的 $y-x$ 元素，首先我们如果要是剩下最多的元素的个数是 $f$ ,不难证明的是这时候最少的重叠次数是 $2f -(n-x)$ 因为如果 $f \ge ( n-x )/2$ 的话，那么，只有他自己会重叠，反之则没有重叠。那么 当 $n-y < 2f-(n-x)$ 的时候会无解，反之则存在解。

首先注意到，这玩意其实是无关顺序的，所以不妨排个序，与之前的东西做对应。之后对于这个数组，索引移动 $f$ 就可以取到最好的情况了。

```c++
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::pair;
using std::vector;

const int Maxn = 1e5 + 11;

vector < int > elvahs[ Maxn ];

void solve( )
{
	int n, x, y;
	cin >> n >> x >> y;
	y -= x;
	for( int i = 1; i <= n + 1; ++i )
		elvahs[ i ].clear( );
	vector < int > ans( n );
	std::priority_queue < pair < int, int >, vector < pair < int, int > >, std::less < pair < int, int > > > Q;
	for( int i = 0, a; i < n; ++i )
	{
		cin >> a;
		elvahs[ a ].push_back( i );
	}
	int mx = 0;
	for( int i = 1; i <= n + 1; ++i )
	{
		if( !elvahs[ i ].size( ) )
			mx = i;
		else
			Q.push( std::make_pair ( elvahs[ i ].size( ), i ) );
	}
	for( int i = 1; i <= x; ++i )
	{
		auto tp = Q.top();
		Q.pop();
		ans[ elvahs[ tp.second ].back( ) ] = tp.second; 
		elvahs[ tp.second ].pop_back( );
		if( elvahs[ tp.second ].size( ) )
			Q.push( std::make_pair( elvahs[ tp.second ].size( ), tp.second ) );
	}
	vector < pair < int, int > > S;
	int most = 0;
	for( int i = 1; i <= n + 1; ++i )
	{
		most = std::max( most, ( int ) elvahs[ i ].size( ) );
		for( int j = 0; j < ( int ) elvahs[ i ].size( ); ++j )
			S.push_back( std::make_pair ( elvahs[ i ][ j ], i ) );
	}
	if( n - y  - x < most * 2 - ( n - x ) )
	{
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	int cnt = 0;
	// 大概是 n-x 
	for( int i = 0; i < S.size( ); ++i )
	{
		most %= S.size( );
		if( cnt == y )
			break;
		if( S[ i ].second != S[ most ].second )
		// 要是就是和你想要的不一样的话，就改呗
		// 但是可以要 
			ans[ S[ i ].first ] = S[ most++ ].second,
			cnt++; 
	}
	for( auto &i : ans )
		cout << ( i ? i : mx ) << " "; 
	cout << '\n';
	return;
}

int main( )
{
	std::ios::sync_with_stdio( false );
	int t;
	cin >> t;
	while( t-- )
		solve( );
	return 0;
}
```



---

## 作者：CodingOIer (赞：0)

## [CF1381C] Mastermind 题解

### 思路分析

先考虑对于一个数列 $p$ 如何赋值得到 $b$ 使得对于 $i \in [1, n], p_i \not = b_i$ 且 $p$ 和 $b$ 中相同的元素数量最多。

显然将 $p$ 排序后循环右移 $\lfloor\dfrac{n}{2}\rfloor$ 得到 $b$ 即是最优的。

考虑最多的数为 $k$，数量为 $x$。

- 对于 $x \le \lfloor\dfrac{n}{2}\rfloor$ 的情况，显然对于任何数的右边 $\lfloor\dfrac{n}{2}\rfloor$ 不可能是他本身，因为这个数就只有 $x$ 个。
- 对于 $x > \lfloor\dfrac{n}{2}\rfloor$ 的情况，$n - x$ 个 $k$ 都可以与其余的数配对，而剩下的 $n - x$ 个数都可以与 $k$ 配对。

综上，显然最多的数越少，我们能创造出的相同元素越多。

对于需要完全相同的 $x$ 个数，可以直接无脑取当前最多的那个数中的一个。

接着，按照最开始的思路统计出所有剩下的数，计算出最多可以元素相同的数量以及方案，取 $y - x$ 个，最后把剩下的还没有值的全部赋值为在原数组中没有出现的某一个数字即可。

（因为值域为 $[1, n + 1]$，而最多只有 $n$ 个数，所以肯定至少有一个数没有出现过）

### 代码实现

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e5 + 5;
int n, x, y;
int p[MaxN];
int cnt[MaxN];
int answer[MaxN];
std::queue<int> que;
std::vector<int> v;
std::vector<int> w[MaxN];
std::priority_queue<std::tuple<int, int>> queue;
inline void solve()
{
    memset(cnt, 0, sizeof(cnt));
    v.clear();
    scanf("%d%d%d", &n, &x, &y);
    for (int i = 1; i <= n; i++)
    {
        w[i].clear();
        scanf("%d", &p[i]);
    }
    w[n + 1].clear();
    for (int i = 1; i <= n; i++)
    {
        w[p[i]].push_back(i);
    }
    int undefine = -1;
    for (int i = 1; i <= n + 1; i++)
    {
        if (!w[i].empty())
        {
            queue.push({w[i].size(), i});
        }
        else
        {
            undefine = i;
        }
    }
    for (int i = 1; i <= x; i++)
    {
        auto [k, id] = queue.top();
        queue.pop();
        k--;
        answer[*w[id].rbegin()] = id;
        w[id].pop_back();
        if (k != 0)
        {
            queue.push({k, id});
        }
    }
    for (; !queue.empty();)
    {
        auto [k, id] = queue.top();
        queue.pop();
        cnt[id] = k;
        for (int i = 1; i <= k; i++)
        {
            v.push_back(id);
        }
    }
    std::sort(v.begin(), v.end());
    int l = int(v.size() + 1) / 2;
    std::vector<std::tuple<int, int>> can;
    for (int i = 0; i < int(v.size()); i++)
    {
        if (v[i] != v[(i + l) % int(v.size())])
        {
            can.push_back({v[i], v[(i + l) % int(v.size())]});
        }
        else
        {
            cnt[v[i]]--;
            answer[*w[v[i]].rbegin()] = undefine;
            w[v[i]].pop_back();
        }
    }
    int to = y - x;
    if (int(can.size()) < to)
    {
        printf("No\n");
        return;
    }
    for (int i = 0; i < to; i++)
    {
        answer[*w[std::get<0>(can[i])].rbegin()] = std::get<1>(can[i]);
        w[std::get<0>(can[i])].pop_back();
        cnt[std::get<0>(can[i])]--;
    }
    for (int i = 1; i <= n + 1; i++)
    {
        for (; cnt[i] != 0;)
        {
            cnt[i]--;
            answer[*w[i].rbegin()] = undefine;
            w[i].pop_back();
        }
    }
    printf("Yes\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", answer[i]);
    }
    printf("\n");
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}

```

---

