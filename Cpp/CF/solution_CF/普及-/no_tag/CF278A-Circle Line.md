# Circle Line

## 题目描述

有$n$个车站排成一个环形，给定$n$个车站之间的距离，求从第$s$个车站到第$t$个车站所需的最短距离。

## 样例 #1

### 输入

```
4
2 3 4 9
1 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
5 8 2 100
4 1
```

### 输出

```
15
```

## 样例 #3

### 输入

```
3
1 1 1
3 1
```

### 输出

```
1
```

## 样例 #4

### 输入

```
3
31 41 59
1 1
```

### 输出

```
0
```

# 题解

## 作者：Andysun06 (赞：7)

## CF278A 题解

这题既然没有pascal题解，那我就来一篇

### 题目描述：
有 $n$ 个车站排成一个**环形**，给定 $n$ 个车站之间的距离，求从第$s$个车站到第 $t$ 个车站所需的最短距离。

### 题目分析：

也就是说，有一个这样的车站：

![1](https://i.loli.net/2020/05/01/i6pjY3a4hyAgNno.png)

他可以这样走：

![1](https://i.loli.net/2020/05/01/C1y8PTSFVeHWnLE.png)

也可以这样走：

![1](https://i.loli.net/2020/05/01/bC5XiJ6HIA8Bucs.png)

现在告诉你：
- ① 和 ② 的距离为 2
- ② 和 ③ 的距离为 3
- ③ 和 ④ 的距离为 1
- ④ 和 ① 的距离为 8

也就是下面这种状况：

![1](https://i.loli.net/2020/05/01/GFHVh5N2ysExeR3.png)

那有的人就想，我只要判断出那个路线距离短就可以了呀，那么请看下面：

你要从 ① 走到 ④，你会怎么走？

- 是从 ① --> ② --> ③ --> ④
- 还是 ① --> ④

很明显，当然是 ① --> ② --> ③ --> ④ 要短一点，所以，路线短不一定距离短，好了，既然理解了题目和易错点，就要开始写程序了

### 做法分析：

我们先用一个数组，把每个点之间的距离存下来，然后计算总路程

```pas
read(n);
   for i:=1 to n do
   begin
       read(f[i]);
       sum:=sum+f[i];//计算总路程
   end;
```

然后输入 $s$ , $t$ 并且将小的放在前面

```pas
if s>t then //如果s大于t，就将他们交换过来
   begin 
       q:=s; //交换
       s:=t;
       t:=q;
   end;
```

再计算从 $s$ 到 $t$ 的路线距离，这时候可能有人问：不是要计算两条吗？

计算两条当然是可以的，但是我们之前已经计算了总长度，所以说，总长度 减去 $s$ 到 $t$ 的路线距离 就等于 另一条路线长度。

```pas
for i:=s to t-1 do
    k:=k+f[i];
```

最后，只要一个判断输出，就可以了

```pas
if k<(sum-k) then
       writeln(k)
   else
       writeln(sum-k);
```

下面是完整代码：

```
var n,s,t,sum,k,i,q:longint;
    f:array [1..102] of longint;
Begin
   read(n);
   for i:=1 to n do
   begin
       read(f[i]);
       sum:=sum+f[i];
   end;
   read(s,t);
   if s>t then
   begin 
       q:=s;
       s:=t;
       t:=q;
   end;
   for i:=s to t-1 do
       k:=k+f[i];
   if k<(sum-k) then
       writeln(k)
   else
       writeln(sum-k);
end.
```

希望本题解对大家有帮助，也感谢管理员百忙之中帮我审核题解，谢谢！

End.

---

## 作者：Lips (赞：2)

# 不一样的做法&最优解

这明明是 $dijkstra$ 的模板题鸭！对于每一个 $d_i$，只要将 $i$ 与 $i+1$ 之间连一条长度为 $d_i$ 的**双向边**，对于 $i=n$ 时的情况特殊处理：连一条 $1$ 与 $n$ 之间的双向边，即可。最后以 $s$ 为起点，跑一边 $dijkstra$ 的模板，答案就是存在 $dis$ 数组中的 $dis[t]$。

目前来康这种做法是最优解，毕竟楼下的做法**对我来说**不能一下子想出来（

$\color{Limegreen}Code:$

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=110;
int n,d[MAXN],s,t;
struct edge//结构体存边 
{
	int to,cost;
	edge(int to,int cost):to(to),cost(cost){}//构造函数 
};
vector<edge>G[MAXN];
typedef pair<int,int>P;
inline int read()//快读 
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
void dijkstra(int s)//模板 
{
	priority_queue<P,vector<P>,greater<P> >q;
	for(register int i=1;i<=n;i++) d[i]=1e9;
	d[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		P p=q.top();
		q.pop();
		int v=p.second;
		if(d[v]<p.first) continue;
		for(register int i=0;i<G[v].size();i++)
		{
			edge e=G[v][i];
			if(d[e.to]>d[v]+e.cost)
			{
				d[e.to]=d[v]+e.cost;
				q.push(make_pair(d[e.to],e.to));
			}
		}
	}
}
int main()
{
	n=read();
	for(register int u=1;u<n;u++)//建图 
	{
		int v=u+1,w=read();
		G[u].push_back(edge(v,w));
		G[v].push_back(edge(u,w));
	}
	int w=read();//对于i==n特殊处理 
	G[n].push_back(edge(1,w));
	G[1].push_back(edge(n,w));
	s=read(),t=read();
	dijkstra(s);//模板使我快乐 
	printf("%d\n",d[t]);//输出 
	return 0;
}
```
完结撒花

---

## 作者：yanxingyu0910 (赞：1)

## 题目链接

[CF278A Circle Line](https://www.luogu.com.cn/problem/CF278A)

## 题意描述
 
* 有 n 个车站排成一个**环形**，给定 $n$ 个车站之间的距离，求从第 $s$ 个车站到第  $t$ 个车站所需的最短距离。

## 思路

* 不难看出有两种，于是我们可以进行**分类讨论**。

### 至于分类讨论的思路：

* 我们可以拿样例一来看一下：

* 第一站到第二站的距离是 2 ，第二站到第三站的距离是 3 把这两个加起来等于 5 就是**正**着讨论的一种情况啦。

* 第三站到第四站的距离是 4 ，第四站到第一站的距离是 9 吧这两个加起来等于 13 就是**反**着讨论的一种情况啦。

* 要输出最短的距离我们把 5 输出就是结果啦。


## 代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001],b,c,i,n,t,s,zheng,fan,ans;
signed main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	cin>>s>>t;
	if(s==t){//这里把相等的情况提前输出了防止出bug 
		cout<<0;
		return 0;
	}
	else if(s>t){//先进行初始化 
		b=s;
		c=t;
	}
	else if(s<t){
		c=s;
		b=t;
	}
	//b永远是最大的，c永远是最小的 
	for(i=c;i<=b-1;i++){
		zheng+=a[i];//正着枚举 
	}
	for(i=1;i<=c-1;i++){
		fan+=a[i];//反着枚举，从1到最小的前面 
	}
	for(i=n;i>=b;i--){
		fan+=a[i];//反着枚举，从最大的到n 
	}
	ans=min(zheng,fan);//最短的 
	cout<<ans;
	return 0;//好习惯 
}
```
这可能或许不是标准解但也是一种思路，欢迎 $hack$ ，感谢观看~

---

## 作者：丧黑福造 (赞：1)

由于快期末了，本来不想刷题了，可是这题实在太水了。。

题解里的思路太难想/kk

看到题目马上想到**最短路**，且$n\leq100$，所以本题采用[$floyd$](https://www.cnblogs.com/wangyuliang/p/9216365.html)算法来求最短路

$code:$

```cpp
#include<stdio.h>
int d[105][105];
inline int mn(int x,int y){
	return x<y?x:y;
}
main()
{
	int n;
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
		for(register int j=1;j<=n;j++)
			d[i][j]=0x3f3f3f3f;//赋初值 
	for(register int i=1;i<n;i++){
		int x;
		scanf("%d",&x);
		d[i][i+1]=d[i+1][i]=x;//是无向图		
	}
	int x;
	scanf("%d",&x);
	d[1][n]=d[n][1]=x;//n特判 
	int s,t;
	scanf("%d%d",&s,&t);
	for(register int k=1;k<=n;k++){
		for(register int i=1;i<=n;i++){
			for(register int j=1;j<=n;j++){
				d[i][j]=mn(d[i][j],d[i][k]+d[k][j]);
			}
		}
	}
	if(s==t) puts("0");//需要特判 
	else printf("%d\n",d[s][t]);
	return 0;
}
```

---

## 作者：As_Snow (赞：0)

题目链接：[CF278A](https://www.luogu.com.cn/problem/CF278A)
### 题意
有 $n$ 个车站排成一个**环形**，并给定每一对相邻车站之间的距离，求从起点到终点最短距离是多少。

### 分析
题目的终点就是**环形**两个字，这就意味着从起点到终点有顺时针走和逆时针走两种走法（如图）。
![](https://s1.ax1x.com/2022/10/12/xUzQk6.png)![](https://s1.ax1x.com/2022/10/12/xUzKTx.png)
但是也只有这两种走法，所以我们只需要顺时针遍历一遍和逆时针遍历一遍，然后判断怎么走距离最少就可以了。
## Code
```
#include<bits/stdc++.h>
using namespace std;
const int N = 1e2+12;
int n,ans1,ans2,s,t,a[N];
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	scanf("%d%d",&s,&t);
	for(int i=s;i!=t;(i%=n)++)//顺时针走一遍
		ans1+=a[i];
	for(int i=t;i!=s;(i%=n)++)//逆时针走一遍
		ans2+=a[i];
	printf("%d",min(ans1,ans2));
	return 0;
}
```

---

## 作者：许多 (赞：0)

由题意可知，这是一个环形。

所以 $s$ 到 $t$ 有两种走法。

一个是从 $s$ 走到 $s+1$ 一直走到 $t$。

另一个是从 $t$ 走到 $t+1$ 一直走到 $s$。

所以我们可以得到简单的代码：

```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'&&ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int n,d[1000],s,t,ans1=0,ans2=0;
int main(){
	n=read();
	for(int i=1;i<=n;i++)d[i]=read();
	s=read();t=read();
	for(int i=s;;i++){
		if(i>n)i=1;
		if(i==t)break;//一定注意，从s走到t时不加d[t]。
		ans1+=d[i];
	}
	for(int i=t;;i++){
		if(i>n)i=1;
		if(i==s)break;//同上。
		ans2+=d[i];
	}
	cout<<min(ans1,ans2);
	return 0;
}
```

---

## 作者：小杨小小杨 (赞：0)

## 题意
有 $n$ 个车站排成一个环形，给定 $n$ 个车站之间的距离，求从第 $x$ 个车站到第 $y$ 个车站所需的最短距离。
## 思路
看到大佬们都用最短路，萌新瑟瑟发抖啊。   
个人思路比较简单：前缀和嘛，用一个 $s$ 数组记录下每一个点到第一个点的距离，然后减去前面一段的长度即可。     
仔细看题：可以成为一个环……    
那么就破环成链：把这个数组重复一遍复制到原数组后面，生成一个长度为 $2n$ 的链，然后进行前缀和，设 $mi$ 为 $x$ 和 $y$ 中较小的数，$ma$ 为 $x$ 和 $y$ 中较大的数。最后从 $s(ma - 1) - s(mi - 1)$ 和 $s(mi + n - 1) - s(ma - 1)$ 中取最小值即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,x,y,mi,ma,a[10001],s[10001];
int main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	for (i=1;i<=n*2;i++)
		s[i]=s[i-1]+a[(i-1)%n+1];//破环成链+前缀
	scanf("%d%d",&x,&y);
	mi=min(x,y);ma=max(x,y);//取mi和ma
	printf("%d\n",min(s[ma-1]-s[mi-1],s[mi+n-1]-s[ma-1])); //输出
	return 0;
}

```


---

## 作者：123456Mm (赞：0)

本题由题意可知，共有2种走法。第一种走法即不通过环形交界处，另一种通过。
对于第一种情况：我们只需要从较小数进行累加，到较大数小一即可。
对于第二种情况：首先累加较大时到最后一个，再从最头累加到较小数减一即可
输出两种情况中较小一种即可通过此题
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,x,y,ans1=0,ans2=0,ans3=0;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>x>>y;
	for(int i=min(x,y);i<=max(x,y)-1;i++){
		ans1+=a[i];
	}
	for(int i=max(x,y);i<=n;i++){
		ans2+=a[i];
	}
	for(int i=1;i<=min(x,y)-1;i++){
		ans2+=a[i];
	}
	cout<<min(ans1,ans2)<<endl;
} 
```


---

## 作者：damage (赞：0)

# 题意

有$n$个车站排成一个环形，给定$n$个车站之间的距离，求从第$s$个车站到第$t$个车站所需的最短距离。

### 输入格式

第一行给定车站个数$n$。

第二行给定$n$个车站之间的距离，其中第$i$个数表示第$i$个车站到第$i+1$个车站的距离$d_{i}$。特别地，最后一个数表示第一个车站与最后一个车站之间的距离。

第三行给定两个整数$s$和$t$，表示起点和终点。

### 输出格式

输出共一行，表示第$s$个车站到第$t$个车站之间的最短距离。

---

# 题解

注意题目说了车站是围成一个**环形**的！

所以有两种走法~~（不然直接暴力、前缀和、线段树、树状数组求区间和）~~，一种是从$s$走到$t$，还有一种是反着走（废话）。

为了方便计算，如果输入的$s\gt{t}$，那么就交换$s$和$t$，保证$s\leq{t}$.

> 注： 本文代码使用的交换方法是用的位运算，只不过快一点，其实跟普通的方法是一样的。

然后其实会发现此时$s$车站到$t$车站的距离有两种：

1. 正着走，就是$s$到$t$的区间和

2. 反着走，其实反过来想，就等于总路程长度（$1$~$n$）减去$1$情况下的$s$到$t$的区间和

那么接下来只要比较一下谁小就可以了。

---

# 代码

```cpp
#include<stdio.h>
int n,d[110],s,t,sum,dis;
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
	{
		scanf("%d",&d[i]); //输入路程
		sum+=d[i]; //求总路程
	}
	scanf("%d%d",&s,&t);
	if(s>t) //如果s>t就交换s和t
	{
		s^=t; //使用的是位运算交换的
		t^=s; //只是快一点
		s^=t; //如果不会的（不存在的）大佬们可以就用朴素的方法
	}
	for(register int i=s;i<t;++i) dis+=d[i]; //求区间和，注意题目描述，此时的约束条件为i<t而不是i<=t
	printf("%d\n",dis<sum-dis? dis:sum-dis); //比较1情况和2情况的距离，输出短的距离
	return 0;
}
```

---

