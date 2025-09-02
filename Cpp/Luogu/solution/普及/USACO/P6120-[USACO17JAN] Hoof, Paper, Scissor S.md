# [USACO17JAN] Hoof, Paper, Scissor S

## 题目背景

*本题与 [金组同名题目](/problem/P3609) 在题意上一致，唯一的差别在于对变手势次数的限制。*

## 题目描述

你可能玩过“石头，剪刀，布”，这个游戏在奶牛中同样流行，不过它的名字变成了“蹄子，剪刀，布”。

“蹄子，剪刀，布”和“石头，剪刀，布”的规则十分类似，两只奶牛数到三，然后出一个代表蹄子，剪刀或布的手势。蹄子胜过剪刀，剪刀胜过布，布胜过蹄子。特别地，如果两只奶牛的手势相同，则视为平局。

现在 FJ 和 Bassie 要进行 $N$ 轮对抗。Bassie 已经预测了 FJ 每一轮要出的手势。然而 Bassie 很懒，她最多只想变换一次手势。

现在请你帮 Bassie 求出她最多能赢多少轮。

## 样例 #1

### 输入

```
5
P
P
H
P
S```

### 输出

```
4```

# 题解

## 作者：OfstAutomataMachine (赞：11)

楼下的人的代码都很长~~抄都不想抄~~，但真的这么复杂吗？

首先，如果要在第 $k$ 次变，前面是出x手势，后面出y手势，那么就是$k[x]_{1-x}$+$k[y]_{x-n}$。

其实k数组是可以用前缀和完成。

所以代码显而易见，由于我说不是很清楚，具体细节看代码。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,s[100001],p[100001],h[100001],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		s[i]=s[i-1];//s的前缀和
		p[i]=p[i-1];//p的前缀和
		h[i]=h[i-1];//h的前缀和
		char c;
		cin>>c;
		if(c=='S')
			s[i]++;
		if(c=='P')
			p[i]++;
		if(c=='H')
			h[i]++;
	}
	for(int i=1;i<=n;i++)
		ans=max(ans,max(s[i],max(p[i],h[i]))/*前面最多的*/+max(s[n]-s[i],max(p[n]-p[i],h[n]-h[i])/*后面最多的（因为最多换一次所以可以不换）*/));
	cout<<ans;
	return 0;
}
```


---

## 作者：wylt (赞：7)

USACO 2017 January 白银组T1 Hoof, Paper, Scissors

原题面（英文）：[http://www.usaco.org/index.php?page=viewproblem2&cpid=691](http://www.usaco.org/index.php?page=viewproblem2&cpid=691)

官方题解（英文）：[http://www.usaco.org/current/data/sol_hps_silver_jan17.html](http://www.usaco.org/current/data/sol_hps_silver_jan17.html)


------------
### 题意简述

现在你知道对手 $N$ 轮中每一轮所出的手势，有 $H,S,P$ 三种，

相应的，你也可以出其中任意一种手势，每种手势会被一个克，但又能克另外一个。

可比较懒的你最多只想变换 $1$ 次手势，问此时你最多能胜利多少轮。

其中 $N\le10^5$ 。

### 题目分析

最开始我的想法是用 dp ，即对于每一轮，靠递推求出这一轮前总共变换了 $0$ 次和 $1$ 次的方案数，

再标记上上一轮所出的手势，每次分为不变手势和改变手势两种讨论即可。

但稍微想一下就会发现时间复杂度上不行，并且实现过于复杂。

那么再思考一下发现只能变换一次不就是意味着这 $N$ 轮可以分为前面一个手势，后面再换了一个手势，

通过 dp 的想法我们可以发现前面 $i$ 轮可以胜利的数量就等同于这 $i$ 轮对手所出的那个手势的数量，

而变换手势后胜利的数量就等同于另一个手势的总数再减去前 $i$ 轮对手出这种手势的数量。

例如我们用 $h(i)$ 来表示前到第 $i$ 轮出现的 $H$ 手势的数量，

用$s(i)$ 来表示前到第 $i$ 轮出现的 $S$ 手势的数量，$sc$ 表示对手出的 $S$ 手势的总数，

那么我们可以得出当第 $i$ 轮我们出了 $H$ 手势，而第 $i+1$ 轮准备出 $S$ 手势所能胜利的轮数 $cnt$ 为

$$cnt=h(i)+sc-s(i)$$

所以，我们只要枚举每个断电，求出此时下一轮准备出另一个手势的胜利总轮数，

再与前面所有情况的 $\max(cnt)$ 求最大值即可。

所以，在输入时，我们要记录前 $i$ 轮每个手势出现的次数，再记录每个手势出现的总数就好了。

但是不要忘了在最后还要加上与一次手势都不换能胜利的轮数的比较。



------------
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int h[100005]={0},s[100005]={0},p[100005]={0};
int hc=0,sc=0,pc=0;
//hc,sc,pc表示每个手势出现的总数
//h[i],s[i],p[i]表示前i轮每个手势出现的次数 

int main(){
	int n;
	cin>>n;
	char c;
	for(int i=1;i<=n;i++){
		cin>>c;
		h[i]=hc;
		s[i]=sc;
		p[i]=pc;
		//先将他们标记为此时每个手势的出现次数 
		if(c=='H'){
			hc++;
			h[i]=hc;
		}
		if(c=='S'){
			sc++;
			s[i]=sc;
		}
		if(c=='P'){
			pc++;
			p[i]=pc;
		}
	}
	int cnt=0;
	for(int i=1;i<n;i++){
		cnt=max(cnt,h[i]+sc-s[i]);
		cnt=max(cnt,h[i]+pc-p[i]);
		cnt=max(cnt,s[i]+hc-h[i]);
		cnt=max(cnt,s[i]+pc-p[i]);
		cnt=max(cnt,p[i]+hc-h[i]);
		cnt=max(cnt,p[i]+sc-s[i]);
		//分类讨论6种情况 
	}
	cnt=max(cnt,hc);
	cnt=max(cnt,sc);
	cnt=max(cnt,pc);
	//最后与不变手势胜利轮数比较 
	cout<<cnt;
	return 0;
}

```


---

## 作者：Ryo_Yamada (赞：2)

看到这题的第一感觉显然就是dp。其实这题dp是能过的，小常数，复杂度$O(n)$。

将“蹄子”，“剪刀”和“布”用$0,1,2$号表示。

用$dp_{i,j,k}$表示第$i$轮，已经变换了$j$次手势，这一轮出的是$k$号手势。

在循环中，$k$表示上一轮出的手势，$l$表示这一轮出的手势，$t$表示能赢这一轮的手势。

于是可以得到状态转移方程：

$dp_{i,j,k}=\max(dp_{i,j,k},dp_{i-1,j-1,l} + (l=t)) (j≠0)$

$dp_{i,j,k}=\max(dp_{i,j,k},dp_{i-1,j,l}+(l=t)$

P.S. 这题我是直接拷贝的金组同名题目我的代码，所以数组开的有点大，原来的$K$变量也还留着，没有改成$1$，见谅。

Code：

```
#include <bits/stdc++.h>
using namespace std;
int a[100005], dp[100001][21][3];
int check(char c) {
	if(c == 'H') return 0;
	else if(c == 'S') return 1;
	return 2;
}//转换手势号
int get_win(int i) {
	if(!i) return 1;
	else if(i == 1) return 2;
	return 0;
}//判断赢过i手势的手势号
int main() {
    int n, K = 1;
    cin >> n;
    for(int i = 1; i <= n; i++) {
    	char c;
    	scanf(" %c", &c);//用scanf的话要有个空格：" %c"
    	a[i] = check(c);//存储手势
	}
	for(int i = 1; i <= n; i++) {
		int t = get_win(a[i]);//这一轮需要出手势t才能赢
		for(int j = 0; j <= K; j++) {
			for(int k = 0; k < 3; k++) {
				dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k] + (k == t));
				for(int l = 0; l < 3; l++) {
					if(l != k && j) {
						dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][l] + (l == t));
					}
					if(l == k) {
						dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][l] + (l == t));
					}//状态转移
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < 3; i++) {
		ans = max(dp[n][K][i], ans);
	}//最后取最大
	cout << ans;
    return 0;
}
```


---

## 作者：zhy137036 (赞：2)

## 基本思路

题目中说，“她最多只想变换一次手势”。

这就是说，它前几局出的是一种手势，后几局出的是一种手势，前后手势可能一样，也可能不一样。

所以可以预处理出前（或后） $i$ 局出第 $j$ 种手势能赢多少局。

## 细节处理

设 $f(i,j)$ 表示**前** $i$ 局一直出第 $j$ 种手势能赢的局数。

设 $g(i,j)$ 表示从第 $i$ 局开始**之后**一直出第 $j$ 种手势能赢的局数。

比如说，`P` 是第一种手势，`S` 是第二种手势，`H` 是第三种手势。

定义 $\operatorname{cmp}(i,j)$ 表示第 $i$ 种手势能否赢第 $j$ 种手势。

那么容易得到：$f(i,j)=f(i-1,j)+\operatorname{cmp}(j,a_i)$。

其中 $a_i$ 表示对手第 $i$ 局出的手势。

以及 $g(i,j)=g(i+1,j)+\operatorname{cmp}(j,a_i)$。

那么最终的答案应该是：

$${\large\max_{i=1}^{n-1}(}\max f(i),\max g(i){\large)}$$

## 代码

先上完整代码再讲：

```cpp
#include<iostream>
#include<algorithm>
#define Max 100010
using namespace std;
int n,a[Max],f[Max],b[Max],front[Max][3],back[Max][3];
bool cmp(int x,int y){
	if(x==2&&y==0)return false;
	if(x==0&&y==2)return true;
	return x>y;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		switch(c){
			case'P':a[i]=0;break;
			case'S':a[i]=1;break;
			case'H':a[i]=2;break;
		}
	}
	for(int j=0;j<3;j++){
		for(int i=1;i<=n;i++){
			front[i][j]=front[i-1][j];
			if(cmp(j,a[i]))front[i][j]++;
		}
		for(int i=n;i>=1;i--){
			back[i][j]=back[i+1][j];
			if(cmp(j,a[i]))back[i][j]++;
		}
	}
	for(int i=1;i<=n;i++){
		f[i]=max(max(front[i][0],front[i][1]),front[i][2]);
		b[i]=max(max(back[i][0],back[i][1]),back[i][2]);
	}
	int ans=0;
	for(int i=1;i<n;i++)
		ans=max(ans,f[i]+b[i+1]);
	cout<<ans<<endl;
	return 0;
}
```

### `cmp` 函数

这么定义手势数的好处就是，大部分情况都是值大的手势能赢值小的手势，小部分情况即 $0$ 号手势能赢 $2$ 号手势。

```cpp
bool cmp(int x,int y){
	if(x==2&&y==0)return false;
	if(x==0&&y==2)return true;//两种情况需特判
	return x>y;//其他情况直接比较
}
```

### `f` 数组和 `b` 数组

上面 `ans` 的定义比较复杂，如果在一个式子里写出会非常难看。所以我先预处理出 $\max f(i)$ 和 $\max g(i)$。

```cpp
    for(int i=1;i<=n;i++){
		f[i]=max(max(front[i][0],front[i][1]),front[i][2]);
		b[i]=max(max(back[i][0],back[i][1]),back[i][2]);
	}
	int ans=0;
	for(int i=1;i<n;i++)
		ans=max(ans,f[i]+b[i+1]);//多清爽
```

---

## 作者：胡金梁 (赞：1)

看看数据，太弱了，暴力枚举都能过。于是就是直接暴力了。用 $sum_{1,i}$ 表示从第 $1$ 到第 $i$ 轮蹄子胜的次数，用 $sum_{2,i}$ 表示从第 $1$ 到第 $i$ 轮剪刀胜的次数，用 $sum_{2,i}$ 表示从第 $1$ 到第 $i$ 轮布胜的次数。接着暴力枚举，第一重循环枚举没变之前出什么，第二重循环枚举变了之后出什么，第三重循环枚举在哪一轮之后变。接着统计一下最大值，就完事了。
```cpp
/*胡金梁*/
#include<bits/stdc++.h>
using namespace std;
#define __MY_TEST__ 0
int sum[4][100005];
signed main(){
#if __MY_TEST__
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		char ch;
		cin>>ch;
		sum[1][i]=sum[1][i-1];
		sum[2][i]=sum[2][i-1];
		sum[3][i]=sum[3][i-1];
		if(ch=='P')
		{
			sum[2][i]++;
		}
		if(ch=='H')
		{
			sum[3][i]++;
		}
		if(ch=='S')
		{
			sum[1][i]++;
		}
	}
	int maxn=0;
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			for(int k=1;k<n;k++)
			{
				maxn=max(maxn,sum[i][k]+sum[j][n]-sum[j][k]);
			}
		}
	}
	cout<<maxn;
#if __MY_TEST__
	fclose(stdin);
	fclose(stdout);
#endif
}

```


---

## 作者：QDHSLGYYJK (赞：1)

[P6120 [USACO17JAN]Hoof, Paper, Scissor S](https://www.luogu.com.cn/problem/P6120)

让我们把一次只用一种手势的出法称为一段。

显然，我们可以用前缀和保存每一段能赢多少次，然后再试着把任意两段一同从任意一点断开再接上能赢多少次即可。

```cpp
#include<cstdio>
#include<algorithm>
#define fwin(x)	(x+1)%3
#define flose(x) (x+2)%3
//代码中用0代表蹄子，1代表剪刀，2代表布。
#define sum(x,y,i) a[x][i]+a[y][n]-a[y][i]
using namespace std;
const int N=1e5;
int a[3][N+5],n,x,ans;
void readch(int &x){
	char ch=getchar();
	while(ch!='P'&&ch!='H'&&ch!='S')
		ch=getchar();
	if (ch=='P')
		x=0;
	if (ch=='H')
		x=1;
	if (ch=='S')
		x=2; 
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		readch(x);
		a[x][i]=a[x][i-1];
		a[fwin(x)][i]=a[fwin(x)][i-1]+1;
		a[flose(x)][i]=a[flose(x)][i-1];
	}
	for (int i=1;i<=n;++i){
		ans=max(ans,sum(0,1,i));
		ans=max(ans,sum(0,2,i));
		ans=max(ans,sum(1,0,i));
		ans=max(ans,sum(1,2,i));
		ans=max(ans,sum(2,0,i));
		ans=max(ans,sum(2,1,i));
	}
	printf("%d",ans);
	return 0;
}
```

或者任取一点时算出前段最大和后段最大相加即可。
```cpp
#include<cstdio>
#include<algorithm>
#define fwin(x)	(x+1)%3
#define flose(x) (x+2)%3
//代码中用0代表蹄子，1代表剪刀，2代表布。
#define sum(x,y,i) a[x][i]+a[y][n]-a[y][i]
using namespace std;
const int N=1e5;
int a[3][N+5],n,x,ans;
void readch(int &x){
	char ch=getchar();
	while(ch!='P'&&ch!='H'&&ch!='S')
		ch=getchar();
	if (ch=='P')
		x=0;
	if (ch=='H')
		x=1;
	if (ch=='S')
		x=2; 
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		readch(x);
		a[x][i]=a[x][i-1];
		a[fwin(x)][i]=a[fwin(x)][i-1]+1;
		a[flose(x)][i]=a[flose(x)][i-1];
	}
	for (int i=1;i<=n;++i)
		ans=max(ans,max(max(a[0][i],a[1][i]),a[2][i])+max(max(a[0][n]-a[0][i],a[1][n]-a[1][i]),a[2][n]-a[2][i]));
	printf("%d",ans);
	return 0;
}
```



---

## 作者：_Imaginary_ (赞：1)

这道题虽然是绿题，但仔细想了之后其实不难。

首先，题目中要求求出最多能赢的次数。赢的规则：

> H胜S，S胜P，P胜H

我们可以看出，H、S、P是完全等价的。

所以，我们可以简单地理解为：

> H胜H，S胜S，P胜P

并不影响最终结果。原因：将变形后出的所有S改成出H也能赢。

这个简化可能并不必要，不过个人觉得挺有用的。

接下来，题目就变成了：最多改变一次，问最多有几次手势相同。

我们分两类讨论：

1. 改变手势。我们可以枚举改变手势的位置i，算一算 $1\sim i$中最多的手势个数和 $i+1\sim n$中的个数。由于总有一个端点是1和n，可以考虑前缀和后缀处理。

1. 不改变手势。我们可以理解为浪费一次机会，将手势改成原来的手势，与前一种相同。

至此，分析结束。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=0,H=1,S=2,MX=3;
int n;
int pre[100005][4],suc[100005][4];
char s[100005];
string tmp;
int find(char x)
{
	switch(x)
	{
		case 'P': return P;
		case 'H': return H;
		case 'S': return S;
		default: return -1;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		cin>>tmp;
		s[i]=tmp[0];
	}
	for(int i=1;i<=n;i++)
	{
		pre[i][0]=pre[i-1][0];
		pre[i][1]=pre[i-1][1];
		pre[i][2]=pre[i-1][2];
		pre[i][find(s[i])]++;
	}
		
	for(int i=1;i<=n;i++)
		pre[i][MX]=max(max(pre[i][0],pre[i][1]),pre[i][2]);
	for(int i=n;i>=1;i--)
	{
		suc[i][0]=suc[i+1][0];
		suc[i][1]=suc[i+1][1];
		suc[i][2]=suc[i+1][2];
		suc[i][find(s[i])]++;
	}
//		suc[i][find(s[i])]=suc[i+1][find(s[i])]+1;
	for(int i=1;i<=n;i++)
		suc[i][MX]=max(max(suc[i][0],suc[i][1]),suc[i][2]);
	int ans=0;
//	for(int i=1;i<=n;i++) printf("%d %d %d || %d %d %d\n",pre[i][0],pre[i][1],pre[i][2],suc[i][0],suc[i][1],suc[i][2]);
	for(int i=0;i<=n;i++)
	{
//		printf("%d %d\n",pre[i][MX],suc[i][MX]);
		ans=max(ans,pre[i][MX]+suc[i+1][MX]);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Masna_Kimoyo (赞：1)

讲真，这题不配做绿题（别喷
## 思路

### 1、

我们首先可以这样想，假如在一个区间内，我们想赢的次数最多，那我们只需要算出对手出得最多的手势（~~中指~~），然后配上对付他的手势，就没问题了。

举个例子：
```cpp
P P H S P S P
```

在这里，我们发现，赢的次数最多是 $4$ 。手出的最多的是布，我们只要都出剪刀，就可以让赢的次数最多

### 2、

回到题目，我们看到 $Bessie$ 可以变一次手势。我们可以设置一个断点，把数组分成两半，在断点的一边，我们可以用刚刚的方法，算出赢的最多的次数，在另一边（改变手势后），我们也可以用同样的方法算出赢的最多的次数

最后，两边加起来，就成了“断点设置在此位置”时，赢的最多次数

## 实现

### 1、

经过稍稍一分析，我们就会发现，这道题可以用前缀和来做

首先，我们统计每一阶段已有的 $P$,$H$,$S$ 数量

根据前缀和推出的定理，我们知道，假如要求 $i$~$n$ 的数量，只需要求出 $f[n]$ $-$ $f[i]$ 就行了，求 $1$~$i$ 的数量，只需要求出 $f[i]$ 就行了

于是，断点前后赢的最多次数就解决了

### 2、

再看题目，我们知道，手势不可能在玩 “石头剪刀布” 之后出现变化，所以我们在循环手势变化的位置（断点）时，只需要从 $1$ 开始，从 $n-1$ 结束

## 代码

经过上面的思路和实现的重点，我们就可以得到这样一份代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,INF=2147483647;
int n,ans=-INF;
int f1[N],f2[N],f3[N];
char hand;
inline int read()
{
	int x=0;
	bool w=0;
	char c=getchar();
	while(!isdigit(c))
		w|=c=='-',c=getchar();
	while(isdigit(c))
		x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return w?-x:x;
}
signed main()
{
	n=read();
	for(register int i=1;i<=n;++i)
	{
		cin>>hand;
		f1[i]=f1[i-1];
		f2[i]=f2[i-1];
		f3[i]=f3[i-1];
		if(hand=='P')	++f1[i];
		if(hand=='H')	++f2[i];
		if(hand=='S')	++f3[i];
	}
//	for(register int i=1;i<=n;++i)
//		cout<<f1[i]<<' '<<f2[i]<<' '<<f3[i]<<endl;
	for(register int i=1;i<n;++i)
	{
		int before=max(max(f1[i],f2[i]),f3[i]);
		int after=max(max(f1[n]-f1[i],f2[n]-f2[i]),f3[n]-f3[i]);
		ans=max(ans,before+after);
	}
	printf("%d",ans);
	return 0;
}

```

## 望管理通过








---

## 作者：Ezis (赞：1)

这道题首先说明了有 $3$ 个手势 $P$ , $H$ ,    $S$。

我们可以开三个数组分别把他们记下来。

定义 $f[i][j][k]$ 为当前第 $i$ 轮，是否用了手势，当前是 $P$ 或 $H$ 或 $S$。

转移方程：

$f[i][j][0]=max(f[i][j][0],max(f[i-1][j][0]+h[i],max(f[i-1][j-1][1]+h[i],f[i-1][j-1][2]+h[i])));$

$f[i][j][1]=max(f[i][j][1],max(f[i-1][j][1]+s[i],max(f[i-1][j-1][0]+s[i],f[i-1][j-1][2]+s[i])));$

$f[i][j][2]=max(f[i][j][2],max(f[i-1][j][2]+p[i],max(f[i-1][j-1][0]+p[i],f[i-1][j-1][1]+p[i])));$

$\left( 1 \leq i \leq n \right)$
$\left( 0 \leq j \leq 1 \right)$

最后的答案为

$ans=\max(f[n][i][0],\max(f[n][i][1],f[n][i][2])));$ $\left( 0 \leq i \leq 1 \right)$

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int p[100005];
int h[100005];
int s[100005];
int f[100005][25][3];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		char tmp;
		cin>>tmp;
		if(tmp=='P')
			p[i]=1;
		if(tmp=='H')
			h[i]=1;
		if(tmp=='S')
			s[i]=1;
	}
    f[1][0][0]=h[1];
    f[1][0][1]=s[1];
    f[1][0][2]=p[1];
    for(int i=1;i<=n;i++)
    	for(int j=0;j<=1;j++){
    		f[i][j][0]=max(f[i][j][0],max(f[i-1][j][0]+h[i],max(f[i-1][j-1][1]+h[i],f[i-1][j-1][2]+h[i])));
    		f[i][j][1]=max(f[i][j][1],max(f[i-1][j][1]+s[i],max(f[i-1][j-1][0]+s[i],f[i-1][j-1][2]+s[i])));
			f[i][j][2]=max(f[i][j][2],max(f[i-1][j][2]+p[i],max(f[i-1][j-1][0]+p[i],f[i-1][j-1][1]+p[i])));
		}
	int ans=0;
    for(int i=0;i<=1;i++)
        ans=max(ans,max(f[n][i][0],max(f[n][i][1],f[n][i][2])));
    printf("%d",ans);
	return 0;
}
```


---

## 作者：羚羊WANG (赞：0)

相信大家都玩过“石头剪刀布”这个游戏

那么，相信大家知道：

$1.$石头赢剪刀

$2.$剪刀赢布

$3.$布赢石头

而又因为，在这道题目中，蹄子等价于石头，所以有

$1.$蹄子赢剪刀

$2.$剪刀赢布

$3.$布赢蹄子

而题目中说了，因为奶牛懒，只想变一次手势

而$1 \leq N \leq 100000$

所以，我们可以考虑用$O(n)$的时间来暴力枚举每一个点

然后维护一个$1 - N$的前缀和，来求出当前点变手势的获胜
次数

最后，直接求最大值即可

最后的最后，一定要不换手势的情况

最后的最后的最后

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))
		{
			f|=(c=='-');
			c=getchar();
		}
	while(isdigit(c))
		{
			x=(x<<3)+(x<<1)+(c^48);
			c=getchar();
		}
	return f?-x:x;
}
inline void write(int x){
	if(x<0)
		{
			putchar('-');
			x=-x; 
		}
	if(x>9)
		write(x/10);
	putchar(x%10+'0'); 
}
int n;
int v[100010];
int ans;
int sumh,sums,sump;
int vh[100010],vs[100010],vp[100010];
inline int find1(char c){
	if(c=='H')
		return 1;
	if(c=='S')
		return 2;
	if(c=='P')
		return 3;
}
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		{
			char c;
			cin>>c;
			v[i]=find1(c);
		}
	for(register int i=1;i<=n;++i)
		{
			vh[i]=sumh;
			vs[i]=sums;
			vp[i]=sump;
			if(v[i]==1)
				{
					sumh++;
					vh[i]=sumh;
				}
			if(v[i]==2)
				{
					sums++;
					vs[i]=sums;
				}
			if(v[i]==3)
				{
					sump++;
					vp[i]=sump;
				}
		}
	ans=max(ans,max(sump,max(sums,sumh))); 
	for(register int i=1;i<=n;++i)
		{
			ans=max(ans,vh[i]+sums-vs[i]);
			ans=max(ans,vh[i]+sump-vp[i]);
			ans=max(ans,vs[i]+sumh-vh[i]);
			ans=max(ans,vs[i]+sump-vp[i]);
			ans=max(ans,vp[i]+sumh-vh[i]);
			ans=max(ans,vp[i]+sums-vs[i]);
		}
	write(ans);
	return 0;
}
```


---

## 作者：Viktley (赞：0)

**题目大意：**

奶牛 $A$ 正在和奶牛 $B$ 剪刀石头布（规则都懂），

问奶牛A只变一次手势，问他最多能 $win$ 多少局？

------------

**思路：**

将这道题换一种方式理解，那就非常简单了！

求最多有几个相同手势在变换前后，那二者和就是答案。

为什么这样理解，其实并不用考虑输赢问题，各种手势是相克的

那么只用求出同一种手势的多少，那出它的相克手势不就 $win$ 了？

所以题目就换成了求最多有几个相同手势在变换前后

------------

**Code:**

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int n, sum[N][3], sum1[N][3], ans; //sum表示前缀和，sum1表示后缀和
char a[N];
int main()
{
	scanf("%d", &n);
	char b = getchar();  //处理空格回车的情况
	for(int i = 1; i <= n; i++) scanf("%c", &a[i]), b = getchar();	
	for(int i = 1; i <= n; i++)  //前缀和的预处理
	{
		if(a[i] == 'P') sum[i][1]++;
		else if(a[i] == 'H') sum[i][2]++;
		else sum[i][3]++;
		sum[i + 1][1] = sum[i][1];   //'P'
		sum[i + 1][2] = sum[i][2];   //'H'
		sum[i + 1][3] = sum[i][3];   //'S'
	}
	for(int i = n; i >= 1; i--)  //后缀和的预处理
	{
		if(a[i] == 'P') sum1[i][1]++;
		else if(a[i] == 'H') sum1[i][2]++;
		else sum1[i][3]++;
		sum1[i - 1][1] = sum1[i][1];  //同上
		sum1[i - 1][2] = sum1[i][2];
		sum1[i - 1][3] = sum1[i][3];
	}
	for(int k = 1; k <= n; k++)
	 for(int i = 1; i <= 3; i++)
	  for(int j = 1; j <= 3; j++)
	  	ans = max(ans, sum[k][i] + sum1[k + 1][j]);  
        //枚举变换前后的每一种情况，然后求一个最大值
	printf("%d", ans);
	return 0;
}
```


---

## 作者：Loser_King (赞：0)

前缀和/后缀和练手题。

（同时也可以用dp做，但我不会）

## 题意

> 给定一个长为 $n$ 的石头剪子布的序列，求只换一次手势的情况下，最多能赢几局。

## 做法

由于在石头剪子布的规则里，任一一种手势都有唯一的赢与克的手势，

所以本质上，枚举 Bessie 的手势和枚举 FJ 最长不换手势的局势是一样的。

这可能有点抽象，用样例举个例子：

```text
i:   1 2 3 4|5
FJ:  P P H P|S
B:   S S S S|H
FJ': P P P P|S
ans: 1+1+1+0+1 = 4
```

可以看出，我们只要枚举 `FJ'` 的前后手势和手势换的位置。于是就有了 $O(n)$ 的做法。

只要先预处理出前缀和和后缀和，然后如上枚举即可。

## 代码

```c++
//P6120 AC Code
//written by Loster_King(159686)
//33ms / 5.66MB / 650B C++ O2
#include<bits/stdc++.h>
using namespace std;
int n,ans,a[233333],p[3][233333],s[3][233333];
//a[i]表示第i位置的手势(0~2)
//p[i][j]表示数字i表示的手势在[1,j]中出现了多少次
//s[i][j]表示数字i表示的手势在[j,n]中出现了多少次
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		char c;cin>>c;
		switch(c){
			case'H':a[i]=0;break;
			case'S':a[i]=1;break;
			case'P':a[i]=2;break;
		}
	}
	for(int i=1;i<=n;i++)
	    for(int j=0;j<=2;j++)p[j][i]=p[j][i-1]+(j==a[i]);//预处理前缀和
	for(int i=n;i>=1;i--)
	    for(int j=0;j<=2;j++)s[j][i]=s[j][i+1]+(j==a[i]);//预处理后缀和
	for(int i=0;i<=2;i++)//枚举变换前手势
	    for(int j=0;j<=2;j++){//枚举变换后手势
	    	int t=0;
	    	for(int k=1;k<n;k++)t=max(t,p[i][k]+s[j][k+1]);//枚举变换手势的位置
	    	ans=max(ans,t);
	    }
	cout<<ans<<endl;
}
```



---

## 作者：Happy_Dream (赞：0)

这题我发现大部分神犇都是用DP做的，然而需要吗？
***
首先我们可以考虑暴力，我们可以外层枚举哪一局换手势，内层算能赢多少局，这样复杂度是$O(N^2)$的。

之后我没就可以考虑优化，我们发现外层循环是优化不掉的，至少很难优化掉，我们可以优化内层使得查询每一次是$O(1)$的，怎么办呢？很显然我们只要用一个前缀和维护。计算赢多少局时我们只需要看输给他的那个手势出了多少次就行了。

细节声明：

1，要开三个前缀和数组来维护赢多少局（一共三种手势

2，当我们计算换了之后的手势等赢多少局时，应该是$S[n]-S[k-1]$。$k$是当前下标。

3，别忘了还要分别枚举换之前手势是什么，和换之后是什么。由于可能不换，所以只要写一下如下循环就可以了
```cpp
for(int i=1;i<=3;i++)
{
	for(int j=1;j<=3;j++)//我们不需要判断i是否等于j,因为可以一直不换
    {
    }
}
```
这样我们的代码就出来啦！

$MY CODE:$
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[n+5];
	int h[n+5],s[n+5],p[n+5];//三个前缀和数组
   //A数组其实没啥用
	s[0]=h[0]=p[0]=0;
	for(int i=1;i<=n;i++)
	{
		char c;
		cin>>c;
		s[i]=s[i-1];
		h[i]=h[i-1];
		p[i]=p[i-1];
		if(c=='H')
		{
			a[i]=1;
			h[i]++;//记录蹄子出了多少次
		}
		if(c=='S')
		{
			a[i]=2;
			s[i]++;//记录剪刀出了多少次
		}
		if(c=='P')
		{
			a[i]=3;
			p[i]++;//记录纸出了多少次
		}
	}if(max(p[n],max(h[n],s[n]))==n)//如果全是一个手势就输出N
	{
	    cout<<n;
	    return 0;
	}
	int ans=0;
	for(int i=1;i<=3;i++)
	{
		for(int j=1;j<=3;j++)
		{
			for(int k=1;k<=n;k++)
			{
				int sum=0;
				if(i==1)
				sum+=s[k];
				if(i==2)
				sum+=p[k];
				if(i==3)
				sum+=h[k];
				if(j==1)
				sum+=s[n]-s[k-1];
				if(j==2)
				sum+=p[n]-p[k-1];
				if(j==3)
				sum+=h[n]-h[k-1];
           			//算赢了多少局
				ans=max(ans,sum);//记录最大值
			}
		}
	}
	cout<<ans;//输出
	return 0;
}
``

---

