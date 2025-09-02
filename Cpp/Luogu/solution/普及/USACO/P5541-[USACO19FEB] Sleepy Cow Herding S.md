# [USACO19FEB] Sleepy Cow Herding S

## 题目描述

Farmer John 的 $N$ 头奶牛，总是会迷路走到农场上遥远的地方去！他需要你帮助将她们一起赶回来。

农场的草地大体是一块狭长的区域——我们可以将其想象成一条数轴，奶牛可以占据数轴上的任意整数位置。这 $N$ 头奶牛现在正位于不同的整数位置，Farmer John 想要移动她们，使得她们占据 $N$ 个相邻的位置（例如，位置 $6$、$7$、$8$）。

不幸的是，奶牛们现在很困，Farmer John 要让她们集中精力听从命令移动并不容易。任意时刻，他只能使得一头处在“端点”（在所有奶牛中位置最小或最大）位置的奶牛移动。当他移动奶牛时，他可以命令她走到任意一个未被占用的整数位置，只要在新的位置上她不再是一个端点。可以看到随着时间的推移，这样的移动可以使奶牛们趋向越来越近。

请求出使得奶牛们集中到相邻位置所进行的移动次数的最小和最大可能值。

## 说明/提示

2019 USACO 二月月赛银牌组第一题

## 样例 #1

### 输入

```
3 
4 
7 
9```

### 输出

```
1
2```

# 题解

## 作者：The_Tarnished (赞：37)

居然还有橙题没有题解？？？虽然我觉得这道题不属于橙题（可能我太弱了）
不过本体还是很有思维的（~~我没有夸自己~~）

- 首先要**排序**（从小到大）！！！

# 最小值：
首先，我们应该知道，解决问题后**奶牛的长度最少应该是N**，所以，对于一段长度为N的区域，如果我们要想把所有奶牛都移到里面，至少要**奶牛总数N减去这段区域里面本来就有的奶牛**。

那么，怎么可以是答案最小呢，只要找到一段长度为N的区域里面本来就有的奶牛数量最多就行了（本来就在里面，你还移动他？？？）

```cpp
int ansmin(){
	if((a[n-2]-a[0]==n-2&&a[n-1]-a[n-2]>2)||(a[n-1]-a[1]==n-2&&a[1]-a[0]>2))
		return 2;
	int j=0;
	for(int i=0;i<n;i++){
    	while(j<n-1&&a[j+1]-a[i]<=n-1)
			j++;
    	x=max(x,j-i+1);
	}
	return n-x;
}
```
# 最大值：
其实最大值要比最小值好求（从代码长度就知道了）

最多就是一个一个移动，先判断 _第一个到倒数第二个_ 与 _第二个到倒数第一个_ 那个长（因为你要最大值嘛），在减去N-2。

考虑A[1]-A[0]和A[N-1]-A[N-2]的两个端点间隙。我们的第一步必须“牺牲”其中的一个缺口，这就意味着我们不能把任何一头牛移到这个缺口中。然而，除了这一个缺口之外，我们还可以确保一头奶牛落在我们队列中A[0]和A[N-1]之间的每一个空白处。我们可以通过在排序左侧有两个相邻牛的状态和排序右侧有两个相邻牛的状态之间切换来实现这一点。

```cpp
int ansmax(){
	return max(a[n-2]-a[0],a[n-1]-a[1])-n+2;
}
```


（我可能~~语文不好~~，你要没看懂，你就在看看代码，模拟一下样例，可能就理解了）

# 上代码！！

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm> 
using namespace std;
 
int n,a[100005],x=0;

int ansmin(){
	if((a[n-2]-a[0]==n-2&&a[n-1]-a[n-2]>2)||(a[n-1]-a[1]==n-2&&a[1]-a[0]>2))
    //特判，如果a[n-2]到a[0]或a[n-1]到a[1]的间隔正好是N-2，而且a[n-1]到a[n-2]或a[1]到a[0]的距离大于2
    //那么只要a[n-1]和a[n-2]或a[1]和a[0]各移动一次就可以了（你可以模拟试一试）
		return 2;
	int j=0;
	for(int i=0;i<n;i++){
    	while(j<n-1&&a[j+1]-a[i]<=n-1)
			j++;
    	x=max(x,j-i+1);
	}
	return n-x;
}

int ansmax(){
	return max(a[n-2]-a[0],a[n-1]-a[1])-n+2;
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort(a,a+n);
	printf("%d\n%d\n",ansmin(),ansmax());
	return 0;
}

```


---

## 作者：Sophon (赞：19)

&emsp;&emsp;对于第一问求最小操作次数，由于每一步操作都在占领空位，而最终状态为一段包含连续$\;n\;$个数的区间，所以可以从结果出发，只要枚举这个定长区间的左端点，找到包含的点位最多（即空位数最少）的一个区间，接下来就可以一一将区间外的点移到空位上，补全所有空位。所以操作次数即为最少空位数。除此以外，还存在两种特殊情况。如果前$\;n-1\;$个位置紧邻，而最后一个位置离倒数第二个位置距离大于$\;2\;$，比如$\;1,2,3,4,7\;$，答案应为$\;2\;$。同理，如果后$\;n-1\;$个位置紧邻，而第一个位置离第二个位置距离大于$\;2\;$，答案也应为$\;2\;$。       

&emsp;&emsp;对于第二问求最大操作次数，同样可以从结果出发，由于目标为移动次数最大，所以最终区间需要尽可能向左或者向右靠，也就是左右端点中有一个不移动。如果最终区间在中间某个位置，即左右端点都进行了移动，于是第一个位置和第二个位置间的空位以及倒数第一个位置和倒数第二个位置间的空位没有被更充分的利用，结果一定不优。所以，只需比较这两种方式的次数多少即可。  
&emsp;&emsp;那这两种方式的移动次数如何求呢？回到 “**每一步操作都在占领空位**” 这句话上，一次操作对应着一个空位被占领，要使得结果更大，就需要尽可能地占领途中的空位。显然，由于每次都是移动端点，所以每个空位最多只能被占领一次，于是只需比较第二个位置到最后一个位置之间空位数（向右移）和第一个位置到倒数第二个位置之间空位数（向左移），取更大者，即可确定答案。
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000 + 20;

int n, min_ans, max_ans;

int a[N];

//求最小答案
int xhl()
{
//两种特判
	if (a[n - 2] - a[0] == n - 2 && a[n - 1] - a[n - 2] > 2)
	{
		return 2;
	}
	if (a[n - 1] - a[1] == n - 2 && a[1] - a[0] > 2)
	{
		return 2;
	}

	int tmp = 0;//区间能够覆盖的最大点位数
	for (int i = 0, j = 0; i < n; i++)//枚举左端点
	{
		while (j < n - 1 && a[j + 1] - a[i] <= n - 1)
		{
			j++;//移动右端点
		}
		tmp = max(tmp, j - i + 1);
	}
	return n - tmp;//最小答案，最小空位数
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	sort(a, a + n);

	min_ans = xhl();
    //计算最大空位数，即总长减去已经被占的位置数
	max_ans = max(a[n - 2] - a[0], a[n - 1] - a[1]) - n + 2;

	cout << min_ans << endl << max_ans << endl;
}
```

---

## 作者：神眷之樱花 (赞：15)

## 题意
一条数轴上有 $n$ 头奶牛，每次挪动端点上的奶牛，且挪动后的奶牛不能还是端点，问最少和最多挪动次数。
## 最小值
考虑到不管怎么挪动，挪动完后的奶牛序列长度一定为 $n$，所以只需要找一段最开始时长度为 $n$，且其中包含的奶牛最多的线段，再每次把端点上的奶牛挪动到这条线段的空隙中来就行了，因为这样需要挪动的奶牛数最少，所以挪动次数也最少。最后还要注意特判。


------------

$$min = n - x$$

其中 $x$ 长度为 $n$ 的线段包含的最多的奶牛数。

------------
## 最大值
因为要满足挪动后的奶牛不能还是端点，所以每次挪动奶牛不得不把 $n$ 号奶牛往 $1$ 号奶牛和 $n - 1$ 号奶牛之间挪或者把 $1$号奶牛往 $2$ 号奶牛和 $n$ 号（排完序之后的号数）奶牛之间挪。所以找出最大的空隙再减去 $n - 2$ 就好了。为什么要减去 $n - 2$ 呢？因为向上述某段中间挪时，那段的两个端点是不用挪动的。
## 代码
```cpp
#include<cstdio>
#include<algorithm>
const int N = 1e5 + 5;
int n,ans = 0,a[N];
inline int read() {
	int x = 0,flag = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')flag = -1;ch = getchar();}
	while(ch >='0' && ch <='9'){x = (x << 3) + (x << 1) + ch - 48;ch = getchar();}
	return x * flag;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	std::sort(a + 1,a + 1 + n);
	if(a[n - 1] - a[1] == n - 2 && a[n] - a[n - 1] > 2 || a[n] - a[2] == n - 2 && a[2] - a[1] > 2) ans = n - 2;
	else {
			for(int i = 1,j = 1; i <= n; i++) {
			while(j < n && a[j + 1] - a[i] + 1 <= n) j++;
			ans = std::max(ans,j - i + 1);
		}
	}
	printf("%d\n%d",n - ans,std::max(a[n - 1] - a[1],a[n] - a[2]) - n + 2);
	return 0;
}

```


---

## 作者：龙行龘龘 (赞：7)

# 就差喷出来

普及-你们在想什么???

先读进来排下序,再把总长减去已经被占的位置数就是最小答案

#### 那么还有最大答案

只需比较向右移和向左移，取更大者作为最大答案就可以了

智障的我还自己写了快排...

顺便献上我的blog:https://www.luogu.org/blog/Root-std-admin/

搞代码:

```cpp
//Written By:Jason_Root
//Time Limit : 1000 MS
//Memory Limit : 65536 KB
#include<bits/stdc++.h>
using namespace std;
inline int max(int x1,int x2) {
	return x1>x2 ? x1 : x2;
}
inline int read() {
	char ch = getchar();
	int x = 0, f = 1;
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void quickSort(int a[],int L,int R) {
	if(L > R) return;
	int i = L,j = R;
	int temp = a[L];
	while(i != j) {
		while(a[j] >= temp && i < j)
			j--;
		while(a[i] <= temp && i < j)
			i++;
		if(i < j)
			swap(a[i],a[j]);
	}
	swap(a[L],a[i]);
	quickSort(a,L,i-1);
	quickSort(a,i+1,R);
}
int n,a[100005];
int min() {
	int x = 0;
	if((a[n-2]-a[0] == n-2 && a[n-1]-a[n-2] > 2) || (a[n-1]-a[1] == n-2 && a[1]-a[0] > 2)) {
		return 2;
	}
	int j = 0;
	for(int i = 0; i < n; i++) {
		while(j < n-1 && a[j+1]-a[i] <= n-1) {
			j++;
		}
		x = max(x,j-i+1);
	}
	return n-x;
}
void func() {
	ios_base::sync_with_stdio(false);
	n = read();
	for(int i = 0; i < n; i++) {
		a[i] = read();
	}
	quickSort(a,0,n-1);
	printf("%d\n%d",min(),(max(a[n-2]-a[0],a[n-1]-a[1])-n+2));
	return;
}
int main(int argc, char const *argv[]) {
	func();
	return 0;
}

```
真心感谢大家观看,谢谢!!!

---

## 作者：L_zaa_L (赞：6)

# 分析
题目大意是，将位于数轴上的分散的正整数点通过若干次操作变成一坨（感觉一坨非常的形象）相邻的点，每次操作只能将位于两端的一个点置于另两个点之间，求最少及最多次数所以模拟就好了，也可以找规律。
## 最小
为了保证最小，我们可以先找到奶牛最密集的一坨。再用总奶牛数减去最大的一坨奶牛，即可找到正确答案。

具体实践如下：
```
	for(int i=1;i<=n;i++){
	    while(c<n&&a[c+1]-a[i]<=n-1)
		c++;
	    x=max(x,c-i+1);
	}
	ans1=n-x;
```

## 最大

考虑一定是往一边缩的感觉，于是是端点先跳到一边的里面，然后这一边开始往里缩，直到缩成一坨。

具体实践如下：
```
max(a[n−1]−a[1]+1,a[n]−a[2]+1)−(n−1)+1;
```
最后的加一是刚开始端点往里跳的代价。
# 题解
```
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans,ans2;//ans是最小值，ans2是最大值
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);//快排，将奶牛从小到大排序，以便计算答案
	if((a[n-1]-a[1]==n-2 && a[n]-a[n-1]>2) || (a[n]-a[2]==n-2 && a[2]-a[1]>2)) ans=2;//特判
	else
	{
		int c=1,x=0;//x记录这个范围内最大一坨的奶牛数量
		for(int i=1;i<=n;i++)
		{
	    	while(c<n && a[c+1]-a[i]<=n-1)c++;
	    	x=max(x,c-i+1);
		}//找最大一坨的奶牛的数量
		ans=n-x;//计算最小的值
	}
	printf("%d\n%d\n",ans,max(a[n-1]-a[1],a[n]-a[2])-n+2);//输出最小的和最大的值
	return 0;
}
```
望管理员通过。

---

## 作者：WhiteSunFlower (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P5541)

[更好的阅读体验](https://www.luogu.com.cn/blog/guicai-qq-1443870605/solution-p5541)

## 题目大意
一条数轴上有 $n$ $(3 \leq n \leq 10^{5})$ 头奶牛，通过我们充满智慧的操作来将所有的奶牛变成相邻的，每次仅可以将最左或最右端的奶牛向中间移动，求出移动次数的最小和最大值。
## 做题之前的思考
###### Zeroth ： 这题不止橙吧
### First：  可行性证明
很多朋友刚刚看见这一题都会考虑是否一定可以达成我们想要的目标，即通过题目规定的移动方式将所有奶牛移至相邻的位置。

通过思考，我们可以发现：奶牛 $X$ 不可移动，当且仅当：

>1. $X$ 在边界处

>2. $X$ 不与任意一头奶牛相邻

>3. 除 $X$ 以外所有奶牛都相邻

**全部**满足

发现：左右端点可以同时满足 $(1)$ $(2)$ ，但不可能同时满足 $(3)$ 。

即：在所有奶牛都相邻之前左右端点处至少有一头奶牛可以移动且每次移动都会使奶牛之间更紧凑直至全部相邻。

证毕。
***
### Second： 最小步数
接下来让我们先解决第一个问题：最小的移动步数。
通过~~肉眼观察法~~我们可以发现大多数情况下边界处的奶牛可以一步跳到除掉他以后剩余奶牛的左端点至右端点之间任意一个空格处。

这么说可能有点抽象，我们来看看图：
![](https://cdn.luogu.com.cn/upload/image_hosting/ngwizfmp.png)

假如我们要移动在 $2$ 位置上的奶牛，那么所有绿色标注的位置都可以一步跳过去，我们猜测所有不符合要求的奶牛都可以通过一次操作进行移动，我们的目的就是让尽可能多的奶牛待着不动，而所有奶牛最终的位置都是相邻的 $n$ 个，于是我们~~自然而然地~~想到了利用尺取找出连续 $n$ 个位置中奶牛最多的一段。

代码如下：

```cpp
int get_min(){
	int l=1,r=1;
	while(a[r]<n&&r<=n)r++;//先找出右端
	int maxcover=r-1;//maxcover：连续n个位置中最多覆盖的奶牛的数量
	while(r<=n){
		while(a[r]-a[l]+1>n&&l<r)l++;
		maxcover=max(maxcover,r-l+1);
		r++;
	}
	return n-maxcover;//其余全部一步跳过去
}
```
这时我们发现了一个问题，假如奶牛们这样排布：
![](https://cdn.luogu.com.cn/upload/image_hosting/lnjcokv6.png)

我们尺取到红色方框，显然无法一步过去，那么怎么办呢?

我们
![](https://cdn.luogu.com.cn/upload/image_hosting/a634hze0.png)
只要将左端跳过去作为跳板就好啦！~~可惜需要多出一步来~~。

怎么处理呢?

看代码!
```cpp
for(int i=2;i<=n;i++)
	if(a[i]==a[i-1]+1){
		b[bl]++;
	}else{
		++bl;
		b[bl]++;
		c[bl]=a[i]-a[i-1]-1;
		sigmac+=c[bl];
	}
//b -> 平台,记录每组连续的奶牛。
//c -> 空位,c[i]表示b[i]与b[i-1]之间空格的数量。
```
然后
```cpp
if(bl==2&&(b[1]==1||b[2]==1)&&c[2]!=1)return 2;
//当且仅当有两块且一块为一时特殊处理。
//注意空格为一也是可以一步过去的哦。
```
这个特判多么 ~~ex~~ 友好啊。
***
### Third： 最大步数

终于到了程序最后的阶段了！我们来思考最大值的求法。

#### $\bigstar$ 转换思路

这是我课堂比赛时做的题目，当时许多大佬都卡在了这题上，现在让我们换一种思考这题的方式——不考虑如何去填满一个连续区间，而是将问题转化为将**一个**大的区间缩小成为一个长度为 $n$ 的区间(如下图由蓝色变为红色)。
![](https://cdn.luogu.com.cn/upload/image_hosting/3udrnu68.png)

不难思考出：理想状态下，对一个长度非1的区间进行滚动，每次缩小1，最大操作数为：
>$(R-L+1)-n$   ($L,R$ 为最右和最左端奶牛的坐标)

在脑海中模拟一下~~好吧我懒得画图了~~，只要最左或最右有连续大于等于  $2$ 只奶牛，那么就可以不断地滚过去，每次缩小一个，答案为  $((R-L+1)-n)$。

如果两边同时都是一个，那就必须先跳在滚过去，选择跳的近的就好啦。

看代码!
```cpp
int get_max(){
	if(b[1]==1&&b[bl]==1)return max(sigmac-c[2],sigmac-c[bl]);
	return sigmac;
}
//sigmac -> c数组的和，等价于(R-L+1-n).
```

***
### 简单汇总一下 ： ACcode

注释看上面哟。
```cpp
#include<bits/stdc++.h>
#define Whitesunflower int main()
using namespace std;
const int N=100005;
int n,a[N],b[N],bl,c[N],sigmac;
int get_min(){
	int l=1,r=1;
	while(a[r]<n&&r<=n)r++;
	int maxcover=r-1;
	while(r<=n){
		while(a[r]-a[l]+1>n&&l<r)l++;
		maxcover=max(maxcover,r-l+1);
		r++;
	}
	if(bl==2&&(b[1]==1||b[2]==1)&&c[2]!=1)return 2;
	return n-maxcover;
}
int get_max(){
	if(b[1]==1&&b[bl]==1)return max(sigmac-c[2],sigmac-c[bl]);
	return sigmac;
}
Whitesunflower{
	cin >> n;
	for(int i=1;i<=n;++i)cin >> a[i];
	sort(a+1,a+1+n);//排序很重要.
	b[1]++,bl=1;
	for(int i=2;i<=n;++i)
		if(a[i]==a[i-1]+1){
			b[bl]++;
		}
		else{
			++bl;
			b[bl]++;
			c[bl]=a[i]-a[i-1]-1;
			sigmac+=c[bl];
		}
	cout << get_min() << '\n' << get_max() << '\n';
	return 0;
}
```
本萌新题解写的比较少，有什么说的不清楚的地方欢迎各位 dalao 斧正。

---

## 作者：Demoe (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/P5541)

## 前置知识

无。（（（

## 题意

- 有 $n$ 个点分布在数轴上，你需要将它们调整到连续的 $n$ 个位置上。

- 每次操作可以将边缘上的点移到中间的空位上，但是不能还在边缘上。

- 求最小最大操作次数。

## 简单数学

### 最小值

这个嘛，要移一下肯定有方法嘛qaq。

最小，那么我们固定一个端点，然后。（

暴力。（（（

对于以第 $i$ 个为左端点，我们不断枚举直到 $a_i+n \le a_j$，那么此时答案即为 $n-j+i$。

写一发（假设你最大写好了），一看，没有 $\texttt{TLE}$！

~~Ohhhhhhhhhhhhhhhhhhh~~

再看一眼，$\texttt{WAWAWA}$。（（（

仔细看一眼代码，暴力没打错啊qaq。

这时候你就需要尝试去Hack自己。

有这样一种情况。

$n-1$ 个点抱团，还有 $1$ 个点孤零零的在一边。

这时候那个点不能 $1$ 步到达，因为题目说不能从边界到边界。

那么这时就必须要 $2$ 步。（把团中间一个移出来，再把边上那个弄进去。）

这样交一发——青青草原qwq。

### 最大值

因为不能从边缘还到边缘，所以一定是区间一直在**收拢**。

我们尽量让区间持续较大。

那么我们固定最边上的一个点，使另一边不断只往里面跳到最远的可行处即可。

这样的话，我们就会把 $[a_0,a_{n-1}]$ 或 $[a_1,a_n]$ 中所有初始空点跳过一遍。

因此我们只需把它们两中的初始空点数量比较即可。

最优解rk1代码qwq。（其实有被Hack风险，因为懒得剪枝）

![](https://cdn.luogu.com.cn/upload/image_hosting/vs9jeqfp.png)

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+5;
ll n,a[N],ans=1;
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);
	for(ll i=0;i<n;i++) rd(a[i]);
	sort(a,a+n);
	if(a[n-2]-a[0]==n-2&&a[n-1]-a[n-2]>2||a[n-1]-a[1]==n-2&&a[1]-a[0]>2) ans=n-2;
	else
		for(ll i=0,sum=0;i<n;i++){
			sum=1;
			for(ll j=i+1;j<n;j++,sum++)
				if(a[j]>=a[i]+n) break;
			ans=max(ans,sum);
		}
	wr(n-ans);puts("");
	wr(max(a[n-2]-a[0],a[n-1]-a[1])+1-n+1);puts("");
	return 0;
}
```


---

## 作者：lnwhl (赞：3)

一道很好的思维题啊，~~个人感觉绝对不止橙，评绿都不过分~~。这里提供两种方法。
## 思路
### 最小值
#### 思路1：双指针
首先，可以贪心的想到把奶牛移到一个**原来奶牛最集中的区域**，这样肯定次数最小。而且在最小的条件下，**最终线段的一个端点肯定是原有的奶牛**。所以我们可以想到比较以每一个奶牛为右端点（左端点也可）的区域内的空的个数，最小值即为答案。显然区间的左端点具有**单调性**，所以很明显就可以双指针啊。
#### 思路2：二分
同样，我们也可以二分求出第一个在区间内的奶牛，求出答案。

**但是，还有一组 hack 数据**：

![](https://cdn.luogu.com.cn/upload/image_hosting/tatznxm7.png)

如果所有的奶牛都连在一起，而只有一个分离在 $2$ 格之外，答案为 $2$，需要特判一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/wg7but7h.png)

### 最大值
最大值相对好想一点。首先，我们会发现，由于每次移动一个端点，且移动之后该奶牛不再是端点，所以**每次移动后，区间都在变小**。那么，我们就可以贪心的让每次都移到最远的位置，区间缩小尽量小。

那么我们的任务其实就是找初始的区间最大长度，所以答案就是 
$$\max(a_{n}-a_{2},a_{n-1}-a_{1})-n+2$$
## Code
双指针的：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100005],ans_max=0,ans_min=1e9;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	int j=1;
	for(int i=1;i<=n;i++)
	{
		while(a[i]-a[j]+1>n)j++;
		ans_min=min(ans_min,n-i+j-1);
	}
	if(a[n-1]-a[1]==n-2&&a[n]-a[n-1]>2||a[n]-a[2]==n-2&&a[2]-a[1]>2)
		ans_min=2;//特判
	ans_max=max(a[n]-a[2],a[n-1]-a[1])-n+2;
	cout<<ans_min<<endl<<ans_max;
	return 0;
}
```
二分的：
```cpp
int j=lower_bound(a+1,a+n+1,a[i]-n+1)-a;
ans_min=min(ans_min,n-i+j-1);
```
**rp++;**

---

## 作者：newbie666 (赞：3)

# 一道模拟水题
### 先来分析样例1:
最小移动次数为1——如果Farmer John将位置4的奶牛移动到位置8，那么奶牛们就处在连续的位置7、8、9。最大移动次数为2。例如，位置9的奶牛可以被移动到位置6，然后位置7的奶牛可以被移动到位置5。\
题目思想：先找出间距最大的两个端点，把另外一个端点移到其中一个端点，再用现在的端点重复此过程，直到三个点相邻为止。
#### 直接看代码吧：
# Coding:
```cpp
#include<bits/stdc++.h>
#define SIZE 100020
using namespace std;
int n,Min,Max;
int a[SIZE];
int f() {
	if (a[n - 2] - a[0] == n - 2 && a[n - 1] - a[n - 2] > 2) return 2;
	if (a[n - 1] - a[1] == n - 2 && a[1] - a[0] > 2) return 2;
	int tmp = 0;//区间能够覆盖的最大点位数
	for (int i = 0, j = 0; i < n; i++) { //注意从0开始 
		//枚举左端点
		while (j<n-1 && a[j+1]-a[i]<=n-1) {
			j++;//右端点进行移动
		}
		tmp = max(tmp, j - i + 1);
	}
	return n - tmp;//最小的答案(返回)
}
int main() {
	cin >> n; //输入 
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a+n); //快速排序STL大法 
	Min = f();
	//计算总长减已被占的位数
	Max=max(a[n-2]-a[0],a[n-1]-a[1])-n+2;
	cout<<Min<<endl<<Max<< endl;
	return 0; //完美结束 
}
```
### 完美撒花qwq

---

## 作者：信守天下 (赞：2)

## [洛谷传送门](https://www.luogu.com.cn/problem/P5541)
## 思路
我们分别分析最小和最大次数的情况。
### 最少次数
不妨先简化问题，取消移动的限制。

此时就是要找到一个长为 $N$ 的区间，使得其中有尽可能多的点。

这些点是不用移动的，其他点都需要移动到该区间中来。

然后尝试沿⽤这个思路，将移动限制加上。

假定⽬标区间为 $[l,r]$ ，其中 $r = l + n - 1$ 。

区间中的左右端点位置分别为 ${l}' , {r}'$ 。

那么不难发现，对于位置 $l$ ，需要满⾜下列两种情况之⼀，才可能有解。

位置 $r$ 同理。

1. $l = {l}'$ ，位置 $l$ 上已经有点，该点不⽤移动，保证移动后的位置不会是左端点。

2. 位置 $l$ 不是端点，这样才能将点移动到该位置。此时还需要额外满⾜ $[ {l}' , {r}' ]$ 之间有⼀个空位，⽤于将 $l$ 左边最后剩下的端点移动进来。注意，如果位置 $r$ 也是该情况，还需要⼀个额外的空位。

实际上，位置 $l$ 和位置 $r$ 上都没有点的情况对于求解是没有意义的。

我们可以将区间向右移动到位置 $l$ 上刚好有点，此时求解的限制变得更少。

因此，我们只需要枚举所有左边界在点上的区间即可。

### 最多次数

每次移动都必然会让点的范围缩小。

为了让移动次数尽可能大，就需要让范围缩小的速度尽可能慢。

由于每次操作需要选择端点移动，所以每次移动会让左右两端的某个缝隙消失。

最优情况下，存在⻓度为 $0$ 的缝隙，这样移动后点的范围就只会缩小 $1$ 。

不难发现，最优情况是很容易实现的。

每次移动时，将选择的端点删除后，插⼊到新的任意端点内侧的最近空位。

这样每次移动后都能保证依然存在⻓度为 $0$ 的缝隙。

如果最初两端没有⻓度为 $0$ 的缝隙，我们应该选择⼀个较小的缝隙删除。
## 复杂度分析
### 时间复杂度
排序 $O(N \log N)$ 。

计算最小次数，枚举左边界 $O(N)$ ， 维护右边界总共 $O(N)$ 。

计算最⼤次数，直接计算 $O(1)$ 。

总时间复杂度为 $O(N \log N)$ 。
### 空间复杂度
记录点 $O(N)$ 。
## $code$
~~~cpp
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

int a[kMaxN];
int n;

int C() {
  int v = 0;                                      // 初始化答案
  for (int i = 1, j = 1; i <= n; i++) {           // 枚举左边界
    for (; j <= n && a[j] - a[i] + 1 < n; j++) {  // 维护右边界，使得长度达到n
    }
    if (j <= n && (a[j] == a[i] + n - 1 || a[j - 1] - a[i] + 2 != n)) {  // 右边界存在，要么正好在点上，要么左边有缝隙
      v = max(v, j - i + (a[j] - a[i] + 1 == n));                        // 更新区间内最大点数
    }
  }
  return n - v;  // 区间内最少空位
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + 1 + n);
  cout << C() << endl;                                              // 最小次数
  cout << a[n] - a[1] + 2 - n - min(a[2] - a[1], a[n] - a[n - 1]);  // 最大次数，选择较小缝隙删除
  return 0;
}

~~~


---

## 作者：ryf_loser (赞：1)

这道题看不少大佬都是用贪心做得

但也可以用尺取法（同双指针）做

~~一道水题~~

这道题尺取法是建立在贪心基础之上的，我们可以用贪心策略想到把奶牛移到一个原来奶牛最集中的区域，这样肯定次数最小。

其次在最小的答案下，最终奶牛的一个端点肯定是原有的奶牛。所以我们可以想到比较以每一个奶牛为一个端点的区域内的空的个数，最小值即为答案。显然区间的左端点具有单调性。

最大值

最大值就是找初始的区间最大长度，所以答案就是

$max(a_{n}-a_{2},a_{n-1}-a_{1})-n+2$

## ac代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[100005],maxx=0,minn=2147483647;//int最大取值
int read(){//快读
	int x=0,f=1;char c;
	c=getchar();
	while ((c<'0'||c>'9')&&c!='-')c=getchar();
	if (c=='-'){f=-1;c=getchar();}
	while (c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}
	return f*x;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+1+n);
	for(int i=1,j=1;i<=n;i++){//i和j为两个指针变量，从两头搜索
		while(a[i]-a[j]+1>n)j++;
		minn=min(minn,n-i+j-1);//取最小值
	}
	if(a[n-1]-a[1]==n-2&&a[n]-a[n-1]>2||a[n]-a[2]==n-2&&a[2]-a[1]>2)minn=2;//特判
	maxx=max(a[n]-a[2],a[n-1]-a[1])-n+2;//取最小值
	printf ("%d\n%d",minn,maxx);
	return 0;
}
```


---

