# [AGC006B] Median Pyramid Easy

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc006/tasks/agc006_b

$ N $ 段のピラミッドがあります。 段は上から順に $ 1 $, $ 2 $, $ ... $, $ N $ と番号が振られています。 各 $ 1\ <\ =i\ <\ =N $ について、$ i $ 段目には $ 2i-1 $ 個のブロックが横一列に並んでいます。 また、各段の中央のブロックに注目すると、これらは縦一列に並んでいます。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc006_b/a992c42b0e9b0597f104bf82a0adc1131324bb4f.png)$ N=4 $ 段のピラミッド

 

すぬけ君は $ N $ 段目のブロックに ($ 1 $, $ 2 $, $ ... $, $ 2N-1 $) を並べ替えたもの（順列）を書き込みました。 さらに、次のルールに従い、残りすべてのブロックに整数を書き込みました。

- あるブロックに書き込まれる整数は、そのブロックの左下、真下、右下のブロックに書き込まれた整数の中央値である。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc006_b/545e109d7af3caf92b1a8f9ac80715efa6c3d3db.png)ブロックに整数を書き込む例

 

その後、すぬけ君はすべてのブロックに書き込まれた整数を消してしまいました。 すぬけ君は、$ 1 $ 段目のブロックに書き込まれた整数が $ x $ であったことだけを覚えています。

$ N $ 段目のブロックに書き込まれた順列としてあり得るものが存在するか判定し、存在するならばひとつ求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =N\ <\ =10^5 $
- $ 1\ <\ =x\ <\ =2N-1 $

### Sample Explanation 1

問題文中の図の例です。

### Sample Explanation 2

$ N $ 段目のブロックにどのような順列を書き込んでも、$ 1 $ 段目のブロックに書き込まれる整数は $ 2 $ となります。

## 样例 #1

### 输入

```
4 4```

### 输出

```
Yes
1
6
3
7
4
5
2```

## 样例 #2

### 输入

```
2 1```

### 输出

```
No```

# 题解

## 作者：cqbzjyh (赞：4)

一道挺有意思的构造题

其实有很多种构造方法，这里介绍一种比较好想的方法。

我们想让 $x$ 作为最顶层的元素，最好的方法就是让 $x$ 一直处于中间。于是我们就可以使得 $x$ 左右两边的数都比 $x$ 小，分别为 $x - 1$ 和 $x + 1$,如图
~~（有点难看）~~
![](https://cdn.luogu.com.cn/upload/image_hosting/37wjorjn.png)

这里我们可以证明一下 $x$ 一直处在中间

若 $y1 >= x$ 则 $y2 = x$

若 $y1 < x$ 则 $y2 = x-1$

所以 $y2 =$ $x$ 或 $x-1$

同理

若 $z1 <= x$ 则 $z2 = x$

若 $y1 > x$ 则 $y2 = x+1$

所以 $z2 =$ $x$ 或 $x+1$

综上，无论 $y2$ 和 $z2$ 怎么搭配，中间的数一定是 $x$

所以我们写程序的时候只用将 $x-1,x,x+1$ 放在中间即可，其他的数可以随便放置

对于无法构造的情况我们只需判断 $x$ 是否等于 $1$ 或 $2×n+1$

---
完整代码
```cpp
#include <cstdio>
int a[200005], tot = 1;
int main() {
	int n, x;
	scanf("%d %d", &n, &x);
	if (x == 1 || x == 2 * n - 1) {
		printf("No");
		return 0;
	}
	printf("Yes\n");
	a[n - 1] = x - 1, a[n] = x, a[n + 1] = x + 1;
	for (int i = 1; i <= n - 2;) {
		if (tot == x - 1 || tot == x || tot == x + 1) tot++;
		else a[i] = tot, tot++, i++;
	}
	for (int i = n + 2; i <= 2 * n - 1;) {
		if (tot == x - 1 || tot == x || tot == x + 1) tot++;
		else a[i] = tot, tot++, i++;
	}
	for (int i = 1; i <= 2 * n - 1; i++) {
		printf("%d\n", a[i]);
	}
	return 0;
}
```




---

## 作者：wheneveright (赞：2)

## Update 2021/04/12

更新了几个错别字。。。

## 思路整理

作为一道构造题，要思考那些东西对结果有用，那些没用。

看看这个例子：$1\ 5\ 3\ 7\ 6\ 2\ 4$。

暴力的思路向上推，过程：

$${\color{red} 6}$$
$$5\ \  {\color{red} 6\ \  6}$$
$$3\ \ 5\ \ {\color{red} 6\ \ 6}\ \ 4$$
$$1\ \ 5\ \ {\color{red} 3\ \ 7\ \ 6\ \ 2}\ \ 4$$

发现过程中有多个 $6$ 出现，然后答案也是 $6$，思考有没有什么联系。

观察形如 $x\ x\ y$ 的三元组，在向上一层传递的时候肯定是 $x$ （思考为什么）。

然后进一步推出 $x\ x\ y$ 的上一层结果应该是 $x\ x\ z$ （思考为什么）。

得到结论：当出现形如 $x\ x$ 的排列时，所有在此排列上方的数都为 $x$，所以这个构造题的一种思路就是使在倒数第二排时在中间有两个连续的数出现（肯定就是求的数，不然就没了），就像上面的例子。

## 代码实现

在代码中我定义输入的数为 $N$ 和 $K$。

首先思考几个特殊情况：

- $K = 1$ 和 $K = 2 \times N - 1$ 时（即 $K$ 处于极端数据时），无解，因为没法使其成为中位数，这个很好理解。

- $N = 2$ 时，有且只有 $K = 2$ 有解，因为当 $N = 2$ 时，结果一定为 $2$（思考为什么）。

于是就有了开头这一段：

```cpp
cin >> N >> K;
if (K == 1 || K == 2 * N - 1) {printf ("No\n"); return 0;}
if (N == 2 && K == 2) {printf ("Yes\n1 2 3\n"); return 0;}
if (N == 2) {printf ("No\n"); return 0;}
```

然后输出 `Yes`，开始操作。

```cpp
A[N] = K; A[N - 1] = K - 1; A[N + 1] = K + 1; A[N + 2] = K - 2;
for (register int i = 1, j = 1; i <= N * 2 - 1; i++){
    if (i == N - 1) i = N + 3;
    if (j == K - 2) j = K + 2;
    A[i] = j++;
}
```

先把第一层变成这样（上面一层是数值，下面是位置）：

$$\cdots\ \ K - 1\ \ K \ \ K + 1 \ \ K - 2 \ \ \cdots$$
$$\cdots\ \ N - 1\ \ N \ \ N + 1 \ \ N + 2 \ \ \cdots$$

这样放置就可以使倒数第二层变成这样：

$$\cdots\ \ K \ \ \ \ \ K \ \ \ \ \ \cdots$$
$$\cdots\ \ N \ \ N + 1 \ \ \cdots$$

之后就能做出正确的答案。

还有一个点就是当 $K = 2$ 时要注意不能出现 $K - 2$ 会变成 $0$，你就 `WA` 了，所以这个地方要另外处理，代码就不放了。

---

## 作者：OIerAlbedo (赞：1)

根据那句老话， 暴力出奇迹，打表拿省一。


我们来做了这道题
首先做出这道题，我们需要一个暴力的代码（相信大家都是做紫题的dalao了，不会连暴力打吧）

当然，我还是会给出我的暴力代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300000],b[300000],c[300000];
bool f[300000];
int n,m,nn;
bool flag;
void sc(int t)
{
	if (flag) return ;
	int i,j;
	if (t>n)
	   {
	   	int tt;
	   	for (i=1;i<=n;i++) b[i]=a[i];
	   	for (i=1;i<=nn;i++)
	   	     {
	   	     	for (j=i+1;j<=n-i;j++)
	   	     	     {
	   	     	     	int x=b[j-1],y=b[j],z=b[j+1];
	   	     	     	if (x>y){tt=x;x=y;y=tt;}
						if (x>z){tt=x;x=z;z=tt;}
					    if (y>z){tt=y;y=z;z=tt;}
						c[j]=y;
						 }
				for (j=i+1;j<=n-i;j++) b[j]=c[j];
				}
		if (b[nn]==m)
		    {
		    	for (i=1;i<=n;i++) cout<<a[i]<<endl;
		    flag=true;
			}
	   	return;
	   }
	for (i=1;i<=n;i++) 
	   if (f[i]==false)
	       {
	       	f[i]=true;a[t]=i;sc(t+1);f[i]=false;a[t]=0;
		   }
}
int main()
{
	cin>>n>>m;nn=n;n=n*2-1;
	if ((m==1)||(m==n))
	    {
	    	cout<<"No"<<endl;
	    	return 0;
		}
	cout<<"Yes"<<endl;
	sc(1);
	return 0;
}
```


我们首先输入样例，然后发现，答案居然是1 2 3 4 5 6 7
根据这个规律，我们输入5 5；6 6；7 7；发现答案也是如此，于是我们大胆猜测输入为 $ n $ ，答案就是 $ 1 $ ~ $ n $

然后输入5 2；5 3；5 4；
得到了这些答案

3 4 5 1 2 6 7 8 9

1 4 5 2 3 6 7 8 9

1 2 5 3 4 6 7 8 9


我们发现 $ n $ 后面的总是不变的

再输入6 2；6 3；6 4；6 5

答案为

3 4 5 6 1 2 7 8 9 10 11

1 4 5 6 2 3 7 8 9 10 11

1 2 5 6 3 4 7 8 9 10 11

1 2 3 6 4 5 7 8 9 10 11

我们发现第 $ n-2 $ 个数总是 $ n $ ，然后将 $ m+1 $ ~ $ n $ 插入到 $ m+1 $ ~ $ n $ 的位置，将被替换的数顺次接到 $ n-1 $ ~ $ n $ 的位置

对于 $ m>n $ 也是用如此的方法，便不再赘论。

### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,xx,yy,i,x,y;
int main()
{
	cin>>n>>m;
	if (m==n)
	    {
	    	cout<<"Yes"<<endl;
	    	for (i=1;i<=2*n-1;i++) cout<<i<<endl;
	    	return 0;
		}
	if (m<n)
	    {
	    	if (m==1){cout<<"No"<<endl;return 0;}
	    	cout<<"Yes"<<endl;
		    x=n-2;
		    y=n-m;
		    for (i=1;i<=x-y;i++) cout<<i<<endl;
		    for (i=n-y+1;i<=n;i++) cout<<i<<endl;
		    for (i=1;i<=n;i++)
		        {
		        	if ((i>=1)&(i<=x-y)) continue;
		        	if ((i>=n-y+1)&(i<=n)) continue;
		        	cout<<i<<endl;
				}
		    for (i=n+1;i<=2*n-1;i++) cout<<i<<endl;
		}
	if (m>n)
	    {
	    	if (m==2*n-1)
	    	   {
	    	   	cout<<"No"<<endl;
	    	   	return 0;
			   }
		cout<<"Yes"<<endl;
	      for (i=1;i<n;i++) cout<<i<<endl;
		  y=m-n;
		  xx=n;yy=n+y-1;
		  cout<<n+y<<endl;
		  cout<<n+y+1<<endl;
		  for (i=xx;i<=yy;i++) cout<<i<<endl;
		  for (i=n+1;i<=2*n-1;i++)
		      {
		      	if ((i>=xx)&(i<=yy)) continue;
		      	if ((i==n+y)||(i==n+y+1)) continue;
		      	cout<<i<<endl;
				  }	
		}
	return 0;
}
```


---

## 作者：PosVII (赞：1)

**声明**

------------

其实，这道题是道简单的构造题……但需要思考较久还有很多小坑点，如果是在考场上爆搜就可以骗分了。

本题解中若没有声明，则使用的算法都为自己想出来的算法，通常情况下是有着超高时间空间复杂度，不能与其他大佬相比较的，本题解只是有着一些思路引导。

**构造**

------------

考试题，我们可以简单打出一份暴力搜索代码，在考场中可以不花太多时间得60分也是一个很好的思路。

但是它肯定是有思路解法的，我的思路重点在于“保护”要出现在顶端的x数，我们只需要满足形如：

```
           x
       x-1 x x+1
```

这样的形式便能使x可以一直活到最顶端，但这样的模型仅适用于 $x$ 为 $[1,2 \times (n-1)]$
的中位数时才能够简单推出最后
$2 \times n-1$
个数的排列

但是我们可以发现它是存在多答案的，我们就可以找到更简单的方法。

我们发现：

```
            x
         x  x x+1
```

这样的模型是能够保证x能到一直活到中间的，那么我们仅需要使下面能够形成这样的模型在中间就完了。

注意 $x = 2$ 的情况会使其中保证 $x$ 左边的数是 $x$ 的方法错误，要特判，并且 $x=1$ 或 $x=2 \times (n-1)$ 时是绝对不会有正确方法的。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
int main() {
	cin>>n>>x;
	if(x==1||x==2*n-1) cout<<"No";
	else if(n>2){
		if(x==2) {
			int otp=1;
			cout<<"Yes"<<endl;
			for(int i=1;i<=n*2-1;i++) {
				if(i==n-2) cout<<x+2<<endl;
				else if(i==n-1) cout<<x-1<<endl;
				else if(i==n) cout<<x<<endl;
				else if(i==n+1) cout<<x+1<<endl;
				else {
					if(otp==x-1) otp=x+3;
					cout<<otp<<endl;
					otp++;
				}
			}
		}
		else {
			int otp=1;
			cout<<"Yes"<<endl;
			for(int i=1;i<=n*2-1;i++) {
				if(i==n-1) cout<<x-1<<endl;
				else if(i==n) cout<<x<<endl;
				else if(i==n+1) cout<<x+1<<endl;
				else if(i==n+2) cout<<x-2<<endl;
				else {
					if(otp==x-2) otp=x+2;
					cout<<otp<<endl;
					otp++;
				}
			}
		}
	}
	else {
		if(n==2&&x==2) {
			cout<<"Yes"<<endl;
			cout<<1<<endl<<2<<endl<<3;
		}
		else if(n==2) {
			cout<<"No";
		}
	}
	return 0;
} 
```


---

## 作者：ZCETHAN (赞：1)

[AT2163](https://www.luogu.com.cn/problem/AT2163)

## 题目大意
给定这样一个 $n$ 层的方格金字塔：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210401105847970.png)
然后最后一行是 $1\sim n\times 2-1$ 的排列，之后每一格都是正下方、左下方、右下方 $3$ 个格子中的数的中位数。

然后给定第一层的数 $x$，要求你构造一个合法的最后一层。
## Solution
显然不可能枚举然后验证，那么这显然是一道构造题（~~阿巴阿巴~~）

首先观察它构造的规律。如果三个数中，有 $2$ 个是相等的，那么这三个数“合成”的数也一定是与那两个数相等。所以在任意位置，一旦有 $2$ 个相邻的并且相等的数，那么这两个数所在的列一定都是这个数。

即：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210401110609145.png)
所以，为了使得第一层的那个唯一的数是 $x$，最简单的构造就是把上图中黄色的一列构造成$x$。

可是最后一层并不是上图那么美好，而是 $1\sim n\times 2-1$ 的排列诶。所以就需要构造。

首先把最后一层中间填上 $x$，如图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210401111155491.png)
此时，只需要满足：

- $A>x$ 且 $B,C<x$$\qquad$构造一
- 或 $A<x$ 且 $B,C>x$$\qquad$构造二

就可以使得上图中，$x$ 和 $A$ 的上方都被强迫构造成$x$。

此时，还余留亿点点问题。

首先是上面两种构造选哪种，是等价的吗？  
显然不是，如果 $x=2$ ，那么就没有 $2$ 个数比 $2$ 要小，就无法用上述中第一种构造法。同理，$x=n\times 2-2$ 时就不能用第二种。

其次，什么时候是无解的。  
这不能再简单了，就是 $1$ 或者 $n\times 2-1$ 是无解的。因为这俩连一个比它小(大)的都没有。
## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int MAXN=2e5+10;
bool vis[MAXN];
int ans[MAXN];
int main()
{
	int n,x;
	scanf("%d%d",&n,&x);
	if(x==1||x==2*n-1){puts("No");return 0;}//先判无解，白给
	if(x==2){//我选择特判2，但是相信你一定知道如果特判n*2-2也是可以的
	//如果是2，那么不能用第一种构造
		puts("Yes");
		ans[n+1]=1;
		ans[n]=2;
		ans[n-1]=2*n-1;
		ans[n+2]=2*n-2;
		for(int i=1,j=3;i<=n-2;i++,j++)
			ans[i]=j;
		for(int i=n*2-1,j=2*n-3;i>=n+3;i--,j--)
			ans[i]=j;
		for(int i=1;i<=n*2-1;i++)
			printf("%d\n",ans[i]);
	}else{//同理
		puts("Yes");
		ans[n]=x;vis[x]=1;
		ans[n+1]=2*n-1;vis[2*n-1]=1;
		ans[n-1]=1;vis[1]=1;
		ans[n+2]=2;vis[2]=1;
		for(int i=1,j=1;i<=n*2-1;i++,j++){
			while(ans[i]) i++;
			while(vis[j]) j++;
			ans[i]=j;
		}
		for(int i=1;i<=n*2-1;i++)
			printf("%d\n",ans[i]);
	}
}
/*这是用我的代码的样例1的输出~
   4
  444
 34446
3514726
*/
```
## The end

---

## 作者：ddxrS_loves_zxr (赞：1)

### 思路:

知道了最上面的数 $x$ 后，只要保证它下面的三个数分别为：$x-1,x,x+1$ 即可。

**1.不行的情况**

>即没有 $x-1$ ，与 $x+1$ 。也就是说，当 $x=1$ 或 $x=n\times 2-1$ 时，无解输出"No"；
>
---

**2.可以的情况**

>有 $x-1$ 与 $x+1$ ，这个时候最下面的一排一定有：
![](https://cdn.luogu.com.cn/upload/image_hosting/dkrkhlyu.png)
其它的格子随便填入其他的数字即可。
>

**代码:**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,tot;
int ans[5000005];
bool flag[5000005];
int main()
{
	cin>>n>>x;//读入
	if(x == 1 || x == n * 2 - 1)//判断x的值是否可行
	{
		cout<<"No";
	}
	else
	{
		cout<<"Yes"<<endl;
		ans[n - 1] = x - 1;//用ans数组保存答案
		ans[n] = x;
		ans[n + 1] = x + 1;
		flag[0] = flag[x - 1] = flag[x] = flag[x + 1] = true;//标记某个数是否用过
		for(int i = 1 ; i <= n * 2 - 1 ; i++)//枚举最后一排的位置，最小是1最大是n*2-1
		{
			if(i != n - 1 && i != n && i != n + 1)//中间三个位置被填入了
			{
				while(flag[tot]) tot++;//这个数字被填过了，一直向上找，直到没有用过
				flag[tot] = true;//标记用过
				ans[i] = tot;//存入答案数组
			}	
		}	
		for(int i = 1 ; i <= n * 2 - 1 ; i++)
			cout<<ans[i]<<endl;//输出答案
	}
   return 0;//结束
} 
```
**求过**

---

## 作者：Enderturtle (赞：0)


这题可以和[hard](https://www.luogu.com.cn/problem/AT2165)思路一样，考虑柱子的贡献。我们可以这样构造，正中间三个数分别为”$x-1$，$x$，$x+1$“。想一想这样为什么就是对的。

1.我们先考虑数字小于等于$x$的柱子，显然离正中心的是”$x-1$，$x$“，那么我们这样构造的最终数字一定小于等于$x$。

2.现在我们考虑小于等于$x-1$的柱子，显然离正中心的是“$x$，$x+1$”，那么我们最终数字一定大于$x-1$。

由上述两种情况我们可以证明出最终这样构造的答案就是$x$，并且也证明出$1$和$2n-1$不可能是答案（其实想一下如果$1$和$2n-1$在金字塔第二层，他们一定不会是这一层$3$个数字的中位数）。

至此本题结束，并需要特像楼上题解那样特判$n=2$。

代码实现

```cpp
//Code by Enderturtle
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define il inline
using namespace std;
il int read(){
	int x=0;bool f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=0;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?x:-x;
}
/*----- head end -----*/
int n,x,now=1;
int main(){
	n=read();x=read();
	if(x==1 || x==(2*n-1)) puts("No");
	else{
		puts("Yes");
		rep(i,1,n-2){
			while(now==x || now==x-1 || now==x+1) ++now;
			printf("%d\n",now);
			++now;
		}
		printf("%d\n%d\n%d\n",x-1,x,x+1);
		rep(i,1,n-2){
			while(now==x || now==x-1 || now==x+1) ++now;
			printf("%d\n",now);
			++now;			
		}
	}
	return 0;
}
```

---

## 作者：zhylj (赞：0)

考虑如果有两个 $x$ 在底层正中央（第 $n$ 个位置），那么它们可以一直上到最顶上。如

$$\begin{matrix}&  & x & & & \\& \cdots & x & x & & \\& & \vdots & \vdots & & \\& \cdots & x & x & \cdots & \\\cdots & x - 2 & x & x + 1 & x - 1 & \cdots \\\end{matrix}$$

这样，我们发现对于任意 $x \neq 1, 2n-1$，都可以构造出来（$2$ 需要用 $x + 2, x, x-1, x + 1$ 等，其实原理是一样的）

显然 $1$ 和 $2n - 1$ 是无解的。

要注意特判 $n=2$ 的情况。

```cpp
#include <bits/stdc++.h>

int main() {
	int n, x;
	scanf("%d%d", &n, &x);
	if(x == 1 || x == 2 * n - 1) {
		printf("No\n");
	} else if(n > 2) {
		printf("Yes\n");
		if(x != 2) {
			int ptr = 1;
			for(int i = 1; i < n - 1; ++i, ++ptr) {
				if(ptr == x - 2) ptr = x + 2;
				printf("%d\n", ptr);
			}
			printf("%d\n%d\n%d\n%d\n", x - 2, x, x + 1, x - 1);
			for(int i = 1; i < n - 2; ++i, ++ptr) {
				if(ptr == x - 2) ptr = x + 2;
				printf("%d\n", ptr);
			}
		} else {
			int ptr = 1;
			for(int i = 1; i < n - 1; ++i, ++ptr) {
				if(ptr == x - 1) ptr = x + 3;
				printf("%d\n", ptr);
			}
			printf("%d\n%d\n%d\n%d\n", x + 2, x, x - 1, x + 1);
			for(int i = 1; i < n - 2; ++i, ++ptr) {
				if(ptr == x - 1) ptr = x + 3;
				printf("%d\n", ptr);
			}
		}
	} else {
		printf("Yes\n1\n2\n3\n");
	}
	return 0;
}
```

---

