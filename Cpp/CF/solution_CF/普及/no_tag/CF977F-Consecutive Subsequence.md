# Consecutive Subsequence

## 题目描述

You are given an integer array of length $ n $ .

You have to choose some subsequence of this array of maximum length such that this subsequence forms a increasing sequence of consecutive integers. In other words the required sequence should be equal to $ [x, x + 1, \dots, x + k - 1] $ for some value $ x $ and length $ k $ .

Subsequence of an array can be obtained by erasing some (possibly zero) elements from the array. You can erase any elements, not necessarily going successively. The remaining elements preserve their order. For example, for the array $ [5, 3, 1, 2, 4] $ the following arrays are subsequences: $ [3] $ , $ [5, 3, 1, 2, 4] $ , $ [5, 1, 4] $ , but the array $ [1, 3] $ is not.

## 说明/提示

All valid answers for the first example (as sequences of indices):

- $ [1, 3, 5, 6] $
- $ [2, 3, 5, 6] $

All valid answers for the second example:

- $ [1, 4] $
- $ [2, 5] $
- $ [3, 6] $

All valid answers for the third example:

- $ [1] $
- $ [2] $
- $ [3] $
- $ [4] $

All valid answers for the fourth example:

- $ [1, 2, 3, 7, 8, 9] $

## 样例 #1

### 输入

```
7
3 3 4 7 5 6 8
```

### 输出

```
4
2 3 5 6 
```

## 样例 #2

### 输入

```
6
1 3 5 2 4 6
```

### 输出

```
2
1 4 
```

## 样例 #3

### 输入

```
4
10 9 8 7
```

### 输出

```
1
1 
```

## 样例 #4

### 输入

```
9
6 7 8 3 4 5 9 10 11
```

### 输出

```
6
1 2 3 7 8 9 
```

# 题解

## 作者：爬行者小郑 (赞：7)

## 动态规划+STL：map做法

### 题目的意思就是求出最长连续上升子序列

什么是最长上升连续子序列呢？

**最长**：不用解释，就是子序列越长越好

**连续**：子序列中每个数都是连续的（既差为1）

**上升**：子序列的数是单调递增的

**子序列**：子序列就是原来序列中的一部分构成的序列，这里不一定需要在原来序列中是相邻的

~~翻译不太好~~


方法是什么呢？由于每个数和它-1的数的答案是有关系的，也就是+1，那么我们就可以采用动态规划的做法

$ans[i]:$以i结尾的最长连续上升子序列的元素个数的最大值。

那么我们可以利用STL中的map来访问a[i]-1的编号

于是方程就是：

$1.map[a[i]-1]!=0:ans[i]=ans[map[a[i]-1]]+1$

$2.map[a[i]-1]==0:ans[i]=1$(因为它是新的子序列的开始)

**注意！不能用数组来当桶用**

为什么呢？你看一下a[i]的范围就知道了

输出ans数组中最大的元素就是第一问的答案

第二问怎么输出这个子序列呢？

我们找到ans[i]最大值以及它在数组中的值，因为是连续的，所以我们可以知道子序列开始的数

那么，再循环一边找到子序列在原来序列中的下标就可以了

好的，代码开始：
```cpp
#include <iostream>//基本输入输出流 
#include <map>//一会要用map来查询编号 
using namespace std;
map<int,int>m;//数->编号的映射 
int n;
int ans[200005],a[200005];//ans就是动归变量 
int maxa;//第一问答案 
int l,r;//子序列元素的最小值和最大值 
int main()
{
	cin>>n;//输入个数 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//输入原来序列的每个数 
		int tmp=m[a[i]-1];//找到前一个的编号 
		if(tmp)//如果非零（在原序列中存在） 
		{
			ans[i]=ans[tmp]+1;//等于以上一个元素的答案+1 
		}
		else ans[i]=1;//如果为零（在原序列中不存在） ，它就是新的子序列的开始 
		m[a[i]]=i;//关联起来数和编号 
	}
	for(int i=1;i<=n;i++)
	{
		if(ans[i]>maxa)maxa=ans[i],r=a[i];
		//找到最大的子序列长度以及其中最大的数 
		//a[i]一定是以它结尾的子序列的最后一个数 
	}
	cout<<maxa<<endl;//输出第一问答案 
	l=r-maxa+1;//求出子序列的最小数 
	int idx=l;//记录一下 
	for(int i=1;i<=n;i++)
	{
		if(a[i]==idx)//如果子序列开始 
		{
			cout<<i<<" ";//输出它的编号 
			idx++;//要找的数+1（因为子序列是连续上升的） 
		}
	}
	return 0;//养成好习惯，竞赛中没有直接爆零 
}
```
测第一个样例，发现不对！

难道在多个数的情况下，输出字典序最大的答案吗？

完了，需要将所有可能的答案记录下来，在用trie数搜字典序？？？

其实不用，我们看一下题目，没说

样例说明也说了可以输出其他答案，我的代码是输出字典序最小的

那就没事了~~~

谢谢大家

---

## 作者：泠小毒 (赞：5)

嗯，这道题难度是假的，明明是道水题awa

题意就是求一个最长的值连续上升的子序列，要求输出长度和每个元素的位置

可以想到dp吧
问题是普通的n方不行

那么就到map出场了

每次读进来一个数，压进map

动态转移方程就是a[i]=max(a[i-1]+1,a[i])

最后找答案就O(n)遍历一遍

具体看代码吧
```cpp
#include<bits/stdc++.h>
using namespace std;
int s,n,ans=0,w=0,x[200010],flg=0;
map<int,int>a;
void print(int y)
{
	if(flg)printf(" ");
	else flg=1;
	printf("%d",y);
	return ;
}
int main()
{
	//freopen("sequence.in","r",stdin);
	//freopen("sequence.out","w",stdout);
	scanf("%d%d",&s,&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&s);
		x[i]=s;
        //原序列要存一下，方便查位置
		a[s]=max(a[s],a[s-1]+1);
        //dp过程
		if(a[s]>ans)ans=a[s],w=s;
        //途中顺便找答案
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		if(x[i]==w-ans+1)print(i),ans--;
        //因为序列是连续递增的，每找到一个直接输出就可以了
	return 0;
}
```

---

## 作者：FishingStar (赞：3)

说是提高加，我感觉其实不到，一个 map 类型 s 存储值为 key 的数最后一个出现在哪里（序号）。

动规也很好理解，原始问题没有办法求，我们换一个问题：以第 i 个数为结尾的最长子序列，只要找一个：$s[a[i] - 1]$ 的序号然后在 dp 数组里dp[s[a[i] - 1]] + 1,那么我们的状态转移方程也就出来了：

$if（在之前出现过 a[i] - 1）f(n) = f(n - 1) + 1 如果没有 f(n) = 1 $

这里会有人要问，你说的有问题啊，万一最后一个在你的数的后面，会出问题呀

给自己举个例子：

5

1 2 3 4 3

如果按照一开始读入时就往 map 里放显然会出现错误：

```
dp 数组内
i   0  1  2  3  4
a[i] 1  2  3  4  3
val  1  2  3  1  3
```
哎，你这 dp[3] 怎么是1啊？因为 s 中记载的 3 在后面，dp[4] 还没有赋值欸，所以 $dp[3] = s[4] + 1;$ 0 + 1 = 1,显然不对。

但是我如果是跟着动规的过程来写 s 的，也就是说在 s 中的数都已经被算过了，那么(dp[4]) 很显然就不会出现了。那如果再往后走，有把你替换的呢？也没有关系，你有这么多个数，后面与你相同的元素也一样至少有这么多个数。

最后输出时其实也要费一点脑筋，用一个数组 last 存储第 i 个数的上一个的序号是什么，如果没有上一个存储自己，这里就是一个跟链表有点像的遍历，只要$last[t] != t $ 就一直将 t 设为 last[t] 好了，由于要求倒向输出，我们还要用另一个再倒一下，这道题就做~~水~~完了。
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;
int a[200005];
int dp[200005];
int last[200005];
int ans_index[200005];
int main(){
	map<int, int> s;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
	}
	dp[0] = 1;
	s[a[0]] = 0;
	int ans = 1;
	int ans_i = 0;
	for(int i = 1; i < n; i++){
	    s[a[i]] = i;
	    if(s.find(a[i] - 1) != s.end()){
	        dp[i] = dp[s[a[i] - 1]] + 1;
	        last[i] = s[a[i] - 1];
		} else {
		    dp[i] = 1;
		    last[i] = i;
		}
		if(dp[i] > ans){
		    ans = dp[i];
		    ans_i = i;
		}
	}
	cout << ans << endl;
	int t = ans_i;
	int count = 0;
	ans_index[count++] = ans_i + 1;
	while(last[t] != t){
	    t = last[t];
		ans_index[count++] = t + 1;
	}
	for(int i = count - 1; i >= 0; i--){
	    cout << ans_index[i] << " ";
	}
	return 0;
}
```



---

## 作者：dbg_8 (赞：1)

（其实是看到其他人都是用 map 写的才来写这篇题解的）

[也发表在了博客园上](https://www.cnblogs.com/dbg-8/p/15318091.html)

~~为什么标点必须是全角啊，嘤嘤嘤。~~

#### 题目大意

给定一个长度为 $n$ 的数列 $A$，求 $A$ 中最长连续上升子序列的长度并输出任意一种最长的序列中每个数在 $A$ 中的位置。

#### 思路

求长度应该比较好求，我们可以设 $d[i]$ 为 从 $Ai$ 开始的子序列的最长长度，显然有 $d[Ai] = d[Ai+1] + 1$。那么最长长度(假设她叫 $ans$)即为 $max(\forall d[Ai])$，而输出位置的话我们只需要在计算$ans$时顺便看这个序列的第一个节点是什么(假如他是 st)，然后在 $A$ 中从左到右依次寻找 $st$, $st+1$, ..., $st+ans$ 的位置即可。

发现 $Ai <= 1e9$，就必须离散化。

如果用普通的离散话会 WA（我一开始就是这样的），代码如下（$ma$ 是用来离散化的）：
```cpp
#include <stdio.h>
#include <algorithm>
#define max(x, y) ((x) > (y) ? (x) : (y))

struct NODE {
	int oldnum;
	int oldid;
	int truerank;
	const inline bool operator < (const NODE &rhs) const {
		return oldnum < rhs.oldnum;
	}
} ma[200003];

int n;

int a[200003];
int d[200003];
int ans = 0;
int st;

int main () {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]),
		ma[i].oldnum = a[i],
		ma[i].oldid = i;
	std:: sort(ma + 1, ma + n + 1);
	for (int i = 1; i <= n; i++)
		if (ma[i].oldnum == ma[i - 1].oldnum)
			ma[i].truerank = ma[i - 1].truerank;
		else
			ma[i].truerank = i;
	for (int i = 1; i <= n; i++)
		a[ma[i].oldid] = ma[i].truerank;
	for (int i = n; i >= 1; i--) {
		d[a[i]] = d[a[i] + 1] + 1;
		if (ans < d[a[i]]) {
			st = a[i];
			ans = d[a[i]];
		}
	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++)
		if (a[i] == st)
			printf("%d ", i),
			st++;
	return 0;
}
```
为什么会 WA 呢？

给个例子, 输入 ``2 1 3`` 时离散化 $A$ 成为 $\{1, 2\}$, 这样做时程序就会以为产生误判，原本不连续的两个数被离散化连续了。

那么只要将原本不连续的两个数离散化之后还是不连续不就行了吗！我们在离散化时将原本不连续的两个数中间隔一个数就可以了，原来的公式仍然成立！

P.S. 加了注释的那几行就是改动了的代码，其他代码都不用动。

#### 正解代码
```cpp
#include <stdio.h>
#include <algorithm>
#define max(x, y) ((x) > (y) ? (x) : (y))

struct NODE {
	int oldnum;
	int oldid;
	int truerank;
	const inline bool operator < (const NODE &rhs) const {
		return oldnum < rhs.oldnum;
	}
} ma[200003];

int n;

int a[400003];
int d[400003];
int ans = 0;
int st;

int main () {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]),
		ma[i].oldnum = a[i],
		ma[i].oldid = i;
	std:: sort(ma + 1, ma + n + 1);
	for (int i = 1; i <= n; i++)
		if (ma[i].oldnum == ma[i - 1].oldnum)
			ma[i].truerank = ma[i - 1].truerank;
		else if (ma[i - 1].oldnum + 1 == ma[i].oldnum)	// 可以 AC 的离散化, 好耶!! 
			ma[i].truerank = ma[i - 1].truerank + 1;
		else
			ma[i].truerank = ma[i - 1].truerank + 2;
	for (int i = 1; i <= n; i++)
		a[ma[i].oldid] = ma[i].truerank;
	for (int i = n; i >= 1; i--) {
		d[a[i]] = d[a[i] + 1] + 1;
		if (ans < d[a[i]]) {
			st = a[i];
			ans = d[a[i]];
		}
	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; i++)
		if (a[i] == st)
			printf("%d ", i),
			st++;
	printf("\n");
	return 0;
}
```

---

## 作者：sto_yyrdxh_orz (赞：0)

## 题目大意：
第一行输入一个数字 $n$，第二行输入 $n$ 个数字，输出共两行，第一行一个正整数表示从下标为 $1$ 的数开始的最长递增序列的长度 `maxL`，第二行输出 `maxL` 个数，表示递增元素的下标。

## 题目分析：
我们可以用到动态规划和 `map` 解题，具体的方法在思路和代码注释里都讲了。

#### 思路：
`map` 是可以同时存储键值和实值两个元素的容器，我们可以把值存到键值里，把值的位置存到实值里，同时利用动规的思想把以当前元素为结尾的最长递增序列的长度存到 $dp[i]$ 里同时将 `maxL` 更新为 $\max(maxL, dp[i]) $ 。

#### 具体代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+7;
int n, a[N], dp[N], maxL, maxV;
//dp[i]：以第i个元素结尾的最长递增子序列的长度
map<int, int> m;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[i]=dp[m[a[i]-1]]+1;
		//更新以第i个元素结尾的最长递增子序列的长度
		//推出前一个元素a[i]-1 
		if(dp[i]>maxL){
			maxL=dp[i];
			maxV=a[i];
			//更新最大长度与结尾元素值 
		}
		m[a[i]]=i;
		//记录值与位置的关系 
	}
	cout<<maxL<<endl;
	int x=maxV-maxL+1;
	//求出最长递增子序列的开头元素 
	for(int i=1;i<=n;i++){
		//输出对应元素位置 
		if(a[i]==x){
			cout<<i<<" ";
			x++;
		}
	}
	return 0;
}
```
不了解 `map` 的点[这里](https://blog.csdn.net/sevenjoin/article/details/81943864)。

---

## 作者：Suffix_Sum (赞：0)

这一道题不到蓝，个人觉得差不多黄。

题意：找出一个子序列（按原来的顺序排好），是由连续递增的自然数构成，输出最长序列和每一个数所在原数组位置的编号（任何一个）。

用 $f_i$ 记录以第 $i$ 个数结尾满足题目要求的最长序列，$f_i=$ 以 $a_i-1$ 结尾满足题目要求的最长序列$+1$，用 $map$ 存储对于每一个数结尾满足题目要求的最长序列长度，和他的编号，每一次更新 $f$ 后更新 $map$，然后再用 $father$ 数组记录每一位上一个数所在原数组位置的编号

代码：
```cpp
#include<iostream>
#include<map>
using namespace std;
map<int,pair<int,int> >m;//first记录长度，second记录编号
int n;
int a[200001],f[200001],father[200001],maxx,id;
//maxx代表最长长度，id代表最后一个数的编号
void dfs(int x)//输出
{
	if(x==0)
	{
		return;
	}
	dfs(father[x]);
	cout<<x<<" ";
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		f[i]=m[a[i]-1].first+1;//更新f
		father[i]=m[a[i]-1].second;//更新father
		if(m[a[i]].first<f[i])//判断是否更新map
		{
			m[a[i]].first=f[i];
			m[a[i]].second=i;
		}
		if(maxx<f[i])//更新答案
		{
			maxx=f[i];
			id=i;
		}
	}
	cout<<maxx<<endl;
	dfs(id);
	return 0;
}

```



---

