# [USACO18FEB] Snow Boots S

## 题目描述

农场的冬天到了，这意味着下雪了！从农舍到谷仓的路上有 $N$ 块地砖，方便地编号为 $1 \dots N$，第 $i$ 块地砖上覆盖了 $f_i$ 英尺的雪。

Farmer John 从第 $1$ 块地砖出发，必须到达第 $N$ 块地砖去叫醒奶牛。第 $1$ 块地砖被农舍的屋顶遮蔽，第 $N$ 块地砖被谷仓的屋顶遮蔽，因此这两块地砖上没有雪。但要踩在其他地砖上，Farmer John 需要穿靴子！

在他的恶劣天气背包中，Farmer John 有 $B$ 双靴子，编号为 $1 \dots B$。有些靴子比其他靴子更耐用，有些靴子比其他靴子更灵活。具体来说，第 $i$ 双靴子允许 Farmer John 在最多 $s_i$ 英尺深的雪中行走，并且每步最多可以移动 $d_i$ 块地砖。

不幸的是，靴子的打包方式使得 Farmer John 在任何时候只能访问最上面的一双靴子。因此，Farmer John 可以随时穿上最上面的一双靴子（丢弃旧靴子）或丢弃最上面的一双靴子（使下一双靴子可访问）。

Farmer John 只能在地砖上更换靴子。如果该地砖上有 $f$ 英尺的雪，那么他脱下的靴子和穿上的靴子都必须能够承受至少 $f$ 英尺的雪。他丢弃但未穿过的中间靴子不需要满足此限制。

请帮助 Farmer John 最小化浪费，确定他到达谷仓需要丢弃的最少靴子对数。假设 Farmer John 最初没有穿任何靴子。

## 说明/提示

题目来源：Brian Dean 和 Dhruv Rohatgi

## 样例 #1

### 输入

```
10 4
0 2 8 3 6 7 5 1 4 0
2 3
4 2
3 4
7 1```

### 输出

```
2
```

# 题解

## 作者：nihanchu (赞：18)

   不知道我好像什么时候听别人说过，一般n=250的数据
时间复杂度都是O(n^3)来着，反正这道题确实是。
   我们枚举当前用第i双靴子走路，用g[j]表示前i-1双靴子是否能走到第j块地砖，若g[j]=true且s[i]>=f[j]，说明第i双靴子可以在当前砖块被换上。那么我们就可以用第i双靴子去更新从第j块之后不超过d[i]块的砖块是否能到达。
   表示题目很简单，但我一开始的题意理解其实出了很大的问题，然后想复杂了。。。
   下面是具体程序。


------------
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#define maxn 500
using namespace std;
int d[maxn],b[maxn],a[maxn],n,m;
bool f[maxn];
int main()
{
  scanf("%d%d",&n,&m);
  for (int i=1;i<=n;i++) scanf("%d",&d[i]);
  for (int i=1;i<=m;i++) scanf("%d%d",&a[i],&b[i]);
  for (int i=1;i<=n;i++) f[i]=false;
  f[1]=true;
  int ans;
  for (int i=1;i<=m;i++)
  {
  	for (int j=1;j<=n;j++)
  	if (f[j]&&(a[i]>=d[j]))
  	{
  	 for (int k=j;k<=min(n,j+b[i]);k++)
	 if (a[i]>=d[k]) f[k]=true;	
	}
  	if (f[n]) {ans=i;break;}
  }
  printf("%d\n",ans-1);
  return 0;
}
```

---

## 作者：communist (赞：17)

提供一种无脑$DP$做法

题目中大概有这么些东西：位置，穿鞋，跑路

数据小，那么暴力开数组暴力$DP$吧

设$dp[i][j]$表示穿着鞋子$j$，到达位置$i$是否可行

无脑转移

枚举位置，正在穿哪双鞋，换成哪双走出去，走几步

小的注意事项

1，穿这双鞋不能到这个地方就可以直接跳过，它不能用来转移

2，如果这只鞋不能满足在这个地方死不了，我们就不能穿这双鞋走出去

3，如果走这些步到达的地方，这双鞋不能承受，就不能转移

最后枚举最少穿几双走到$n$即可

```
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=260;
int n,b,dp[maxn][maxn],f[maxn],s[maxn],d[maxn];
int main()
{
    scanf("%d%d",&n,&b);
    for(int i=1;i<=n;i++)
        scanf("%d",&f[i]);
    for(int i=1;i<=b;i++)
        scanf("%d%d",&s[i],&d[i]);
    dp[1][1]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=b;j++)
            if(dp[i][j])
                for(int k=j;k<=b;k++)
                    if(f[i]<=s[k])
                        for(int l=i+1;l<=min(n,i+d[k]);l++)
                            if(f[l]<=s[k])
                                dp[l][k]=1;
    for(int i=1;i<=b;i++)
        if(dp[n][i])
        {
            printf("%d\n",i-1);
            return 0;
        }
    return 0;
}
```

---

## 作者：KarL05 (赞：5)

### 题解 P4265 
这里写一篇java的题解，第一次写，多多指教qwq

------------


### 题目大意:

有N块地砖，FJ要从第一块走到第$N$块，其中每块地砖都有积雪$f_{i}$。

- FJ有$B$双鞋子，可以承受$s_{i}$的积雪 (只有 $s_{i}$>$f_{j}$时可以走到该地砖上) 

- 靴子i最多可以走$d_{i}$ 步。

- 每次只能对最上面的鞋子进行以下两种操作:

1. 丢弃 (以后也无法使用)
2. 穿上 (需要丢弃现在穿的)

问最少丢弃几双鞋子，FJ一开始没穿鞋。


------------
解法:

使用DFS或者动态规划，这里用的DFS。假设状态为

### $f_{i,j}$ = f[穿的鞋子编号][在的雪地编号]
而在搜索的时候,虽然需要同时枚举走的步数和丢弃的鞋子(也就是第一个和第二个变量) 我们可以观察得到

#### 而$f_{i+b,j+a}$<-DFS-$f_{i,j+a}$<-DFS-$f_{i,j}$

也就是说 先 **丢弃靴子** 再 **走一定的步数**

这可以分为两步，所以再dfs里面我们分步写就可以了

综上在DFS的时候我们的结构可以写成 
```java
DFS (int pos, int boots) {
	结束条件
	枚举走的步数
    枚举丢弃鞋子数量
}
```


放上可爱的Java代码

~~注: 由于这道题是我初学时写的因此还没有学到动态规划.但是我相信银组的题应该用不到dp所以就没重新写(qwq)~~

JAVA本身有非常强的东西 类似于

java.math.bigInteger 自动高精度

java.math.bigDecimal 自动高精度(分数)
等等等等 

尽管Java本身速度慢很多，但是在USACO赛制中java有两秒的时间仅此其实没有太大的影响。

```java
import java.io.*; //JAVA万能头文件
import java.util.*; //JAVA万能头文件

public class Main {
	static boolean[][] visited; //vis数组 访问过就跳过
	static int min = Integer.MAX_VALUE; //答案
	static int n; 
	static int b;
	static int f[];
	static int s[];
	static int d[]; //题目给出的信息

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(in.readLine()); //快(慢)速读入 
		n = Integer.parseInt(st.nextToken());
		b = Integer.parseInt(st.nextToken());
		f = new int[n+1];
		s = new int[n+1];
		d = new int[n+1]; 
		visited = new boolean[n+1][n+1];//java数组定义方式
		st = new StringTokenizer(in.readLine()); //换行
		for (int i=1;i<=n;i++) {
			f[i]=Integer.parseInt(st.nextToken());
		}
		for (int i=1;i<=b;i++) {
			st = new StringTokenizer(in.readLine());
			s[i]=Integer.parseInt(st.nextToken());
			d[i]=Integer.parseInt(st.nextToken());
		} //数据读入
		dfs(1,1); //大法师
		System.out.print(min); //输出答案
	}
	static void dfs(int pos, int boot) {
		if (visited[pos][boot]) {
			return;
		} //走过就不走类似于走迷宫你不会走走过的路吧
		visited[pos][boot]=true;
		if (pos==n/*到了终点*/) {
			min = Math.min(min, boot-1);
			return;
		}
		for (int i=1;i<=d[boot];i++) { //枚举走的步数
			if (pos+i>n) {
				return;
			}
			if (f[pos+i]>s[boot]) {
				continue;
			}
			dfs(pos+i,boot); //继续搜索
		}
		for (int i=boot+1;i<=b;i++) { //枚举抛弃鞋子的个数
			if (s[i]<f[pos]) { 
				continue;
			}
			dfs(pos,i); //继续搜索
		}
	}
}
```





---

## 作者：金银花露 (赞：4)

[ P4265 【[USACO18FEB]Snow Boots S】](https://www.luogu.com.cn/problem/P4265)

### 前言：

今天上午的考试中，考了这道题。开始没想出来，后来用贪心乱搞竟然也有70分，后来才在同学的讲解中明白了，来写篇题解整理思路。

## 1.审题

题目大意：

给定一些地砖，以及上面积的雪，有一些靴子，可以在地砖上通过，但是要求踏在地砖上时靴子的耐受度 $s_i$ 要比雪的厚度 $f_i$ 要大，并且要使跨过去的长度小于 $t_i$。

注意：**一双靴子可以跨很多步。**

## 2.解题

### 2.1方法确定

思路一（错误）：贪心，将每一双靴子走到不能再走了才换。

这种思路看起来很对，但实际上会出现错误，**如果出现在一个地方换，可能会有其他地方换，而可以跳过这个地方而不换的，就会有错**。

思路二：动态规划，由刚刚的错误思想，现在就可以明确方向了。

### 2.2状态设计

题解区已经有了很多的状态，这里给出一种。

我们令 $f_i$ 为到达第 $i$ 个地砖的**最少用鞋数**

则答案是很明确的：$f_N-1$ 。最后的一双是穿在脚上的。

### 2.3递推方程

$f_i=\min{k}$ 要求：$1$ 与 $i$ 中有一个 $j$，表示从第 $j$ 个跳到第 $i$ 个上，$k$ 要在 $f_j$ 和 $B$ 中选一个，保证距离和不会陷进去就行了。

### 2.4边界

$f_1=0$，不用换鞋。

## 3.实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,B,ans=0;
int f[255];
int s[255],t[255];
int F[255];
int main()
{
	scanf("%d%d",&N,&B);
	for(int i=1;i<=N;i++)scanf("%d",&f[i]);
	for(int i=1;i<=B;i++)scanf("%d%d",&s[i],&t[i]);
	for(int i=1;i<=N;i++)F[i]=1e9;
	F[1]=0;
	for(int i=2;i<=N;i++)
	for(int j=1;j<i;j++)
	for(int k=F[j];k<=B;k++)
	{
		if(s[k]>=f[i]&&s[k]>=f[j]&&t[k]>=i-j)
		{
		   F[i]=min(F[i],k);
		   break;
		}
	}
	cout<<F[N]-1;
	return 0;
}
```






---

## 作者：All_Might (赞：3)

~~我看这道题题解可少了，而且题目难度虚高？？就来写了个题解233~~

这道题很明显，我做过（逃，正好在复盘dfs，我就重新写了一遍，顺手提交，a了？

### 好了，回到正题。

题目思路：很明显的dfs暴搜，记忆化，俩for循环结束，但是作为一个做过的人来说第一遍做的时候竟然会卡住？？

那么我就来讲解一下这道题，我是用结构体做的，实则两个一维数组也可以，因为不需要排序。


```cpp
struct boot
{
	int h;//高
	int l;//步幅
}b[300];
```
这就是定义结构体，h为鞋子的高（这里就理解为鞋子只要够高，能踩到雪里面），l是步幅，就是能走多少路， **注意这里走的路是可以跨过去的，不用考虑中间有走不过的情况**，

定义完结构体，直接dfs，函数里两个变量，m和ch。m指的是当前位置，ch指的是已经穿到第几双鞋子。**记住，输出的时候要减一，因为这是穿到第几双而不是丢了几双**。开一个记忆化用的数组，bool形。

dfs中，先判断是否到达目的地，与最优解~~比大小~~。再看有没有走过（记忆化啦），然后再把记忆化数组标记为true说明走过了。后面就是典型的dfs的for循环了。

第一个循环就是走路，从走一步，到走最多步，每一步一个dfs（懒得剪枝了反正数据可小了），如果超了目的地，就break，如果没超而且这靴子能走，那就dfs。第二个循环是换鞋子，这个很简单，你现在在的雪块上面，这个换下来的靴子能站着，那就dfs下一个点。

题目大概就是这个亚子的思路了。二话不说，贴代码↓（里面有些简单的思路或者优化我就不说了

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,boot,minn=INT_MAX;
int snow[300];
bool f[300][300];
struct boot
{
	int h;//高
	int l;//步幅
}b[300];
void dfs(int m, int ch)//m位置ch已换
{
	if(m==n)
	{
		minn=min(minn,ch);
		return;
	}
	if(f[m][ch])
		return;
	f[m][ch]=true;
	for(int i=1;i<=b[ch].l;i++)
	{
		if(m+i>n)
			break;
		if(snow[m+i]<=b[ch].h)
			dfs(m+i,ch);
	}
	for(int i=ch+1;i<=boot;i++)
	{
		if(snow[m]<=b[i].h)
			dfs(m,i);
	}
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    
	cin>>n>>boot;
	
	for(int i=1;i<=n;i++)
		cin>>snow[i];
		
    for(int i=1;i<=boot;i++)
        cin>>b[i].h>>b[i].l;
	dfs(1,0);
	cout<<minn-1<<endl;
	return 0;
}

```


然后，谢谢大家的观看啦QAQ



---

## 作者：sycqwq (赞：2)

~~老奶牛了~~

一看数据范围，老 $O(n^3)$ 了

一看题面，老dp了

__思路__:

dp[i] 为从 1 号砖到第 i 号砖需要丢的鞋子

然后有一点最短路的思想

可以从任意编号比 i 小的地砖 j 到 i 需要丢的鞋子

代码：

```
#include<bits/stdc++.h>
#define inf 19260817
using namespace std;
int n,b,mi=inf,f[255],s[255],d[255],dp[255];
int main(){
//	freopen("snowboots.in","r",stdin);
//	freopen("snowboots.out","w",stdout);
	cin>>n>>b;
	for(int i=1;i<=254;i++)
		dp[i]=inf;
	for(int i=1;i<=n;i++)
	{
		cin>>f[i];
	}
	for(int i=1;i<=b;i++)
	{
		cin>>s[i]>>d[i];
	}
	dp[1]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)//通过j到i
			for(int k=dp[j]+1;k<=b;k++)
			{
				if(j+d[k]>=i&&s[k]>=f[i]&&s[k]>=f[j])
				{
					dp[i]=min(dp[i],k-1);
				}
				
			}
//		cout<<dp[i]<<endl;
	}
	cout<<dp[n];
	return 0;
}
/*
10 4
0 2 8 3 6 7 5 1 4 0
2 3
4 2
3 4
7 1
*/
```

---

## 作者：Zenith_Yeh (赞：2)

首先看到 $2≤N,B≤250$ (~~250这个数字很有深意~~)。可以想到复杂度大概是 $O(n^3)$。

我们可以定义 $dp[i]$ 为走到第 $i$ 块砖的最小浪费靴子数(~~虽然我也不知道John哪来的那么多靴子~~)。

**就可以很容易地得出：**

$dp[i]=min(dp[i],k)|(2≤i≤N\ ,\ j<i\ ,\ dp[j]≤k≤B)$

恭喜你！掉坑了。。。

因为你会误以为第 $k$ 个靴子能跳到第 $i$ 个砖块就一定能踩在第 $j$ 个砖块上。题目上说 “如果这块地砖的积雪有 $f_i$ 英尺，他换下来的靴子和他换上的那双靴子都要能够承受至少 $f_i$ 英尺的积雪”，所以要满足 $f_j≤s_k\ ,\ f_i≤s_k$。

若第 $k$ 个靴子的 $f_i≤s_k<f_j$，它就会产生刚刚所说的那种情况。

**所以最终得到的转移方程为：**

$dp[i]=min(dp[i],k)|(2≤i≤N\ ,\ j<i\ ,\ dp[j]≤k≤B\ ,\ f_j≤s_k\ ,\ f_i≤s_k)$

**上菜：**
```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//优美的快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
struct bb
{	int s,d;
}op[255];
int n,m,d_s[255],f[255];
signed main()
{	n=read(),m=read();
	for(register int i=1;i<=n;++i)d_s[i]=read();
	for(register int i=1;i<=m;++i)op[i].s=read(),op[i].d=read();
	memset(f,0x3f,sizeof(f));//注意初始化
	f[1]=1;//不能不穿靴子
	for(register int i=2;i<=n;++i) 
		for(register int j=1;j<i;++j)
			for(register int k=f[j];k<=m;++k)
				if(op[k].s>=d_s[i]&&op[k].d>=i-j)//要判第k个靴子能踩在第i个砖块上，并且能从第j个砖块跳到第i个砖块
					if(op[k].s>=d_s[j])f[i]=min(f[i],k);//要判第k个靴子能踩在第j个砖块上
	cout<<f[n]-1;
	return 0;
}

```


---

## 作者：封禁用户 (赞：1)

使用爆搜。

在当前位置枚举走的步数和要不要换鞋。

状态一共有$O(N^2)$个。

时间复杂度$O(N^3)$

能过。
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <utility>
#include <functional>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define dec(i,a,b) for(int i=(a);i>=(b);--i)
#define endll putchar('\n');
#define RI register int 
#define gc() getchar()
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int maxn=500;
inline ll read(){
    char ch=getchar();ll x=0,f=1;
    while(ch<'0'||ch >'9') {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void print(ll k){
    if(k<0) k=-k,putchar('-');
    if(k>9) print(k/10);
    putchar(k%10+48);
}
inline void println(ll k){
    print(k);
    endll;
}
inline void printsp(ll p){
    print(p);
    putchar(' ');
}
inline void printspfirst(ll p){
    putchar(' ');
    print(p);
}
struct boot{
	int s,d;
	boot(){}
	~boot(){}
	boot(int _s,int _d){s=_s;d=_d;}
}bt[maxn];
int dep[maxn];
bool state[maxn][maxn];
int n,b;
int ans=0x3f3f3f3f;
void dfs(int pos,int bot){
	if(state[pos][bot]==true) return ;
	state[pos][bot]=true;
	if(pos==n){
		ans=min(ans,bot-1);
		return ;
	}
	rep(i,pos+1,pos+bt[bot].d){
		if(i>n) break;
		if(bt[bot].s>=dep[i]) dfs(i,bot);
	}
    //枚举每一个能到的位置
	rep(i,bot+1,b) if(bt[i].s>=dep[pos]) dfs(pos,i);
    //枚举每一双能换的鞋子
}
int main(){
	n=read();
	b=read();
	rep(i,1,n) dep[i]=read();
	rep(i,1,b){
		int s=read(),d=read();
		bt[i]=boot(s,d);
	}
	dfs(1,1);
	println(ans);
	return 0;
}
```

---

## 作者：忘怀星 (赞：1)

~~随机跳到这道题，简单看了一下题面，然后直接点开题解。~~

言归正传，看了这里面好几篇题解，都是 $n^3$ 复杂度的，不过我思考了一下这道题完全可以 $n^2$ 通过。

我们设状态 $dp[i]$ 意义为我们走到点 $i$ 的时候穿的最小编号的鞋子的编号，如果为 $0$ 就意味着走不到这里，我们设初值 $dp[1] = 1$ ，理由应该是比较显然。

我们考虑转移，考虑朴素的想法，我们现在穿着第 $i$ 双鞋子，要考虑能不能走到第 $j$ 块砖上。思考上一步在哪里，一定是第 $i$ 双鞋子可以走到的地方，也就是  $f_k <= s_i$ 的地方，同时我们还必须保证上一步的地方我们能走到，也就是 $dp[k] \neq 0$ ，以及需要我们能一步走过来，既 $i - k \leq d_i$ 。当这些条件都满足的时候，我们可以从 $k$ 走到 $i$ 。

整理一下，对于同一个 $i$ ，我们可以找出一些砖 $k$ 满足 `k<=i && dp[k] && f[k]<= s[i]` 这些条件，我们可以将他们标记上。那么我们如何求在 $i$ 前 $d_i$ 个砖里面有没有标记的点呢？我们可以用类似滑动窗口的方法来进行处理。

综上，我们需要枚举每一双鞋子，还要枚举出每一块砖，复杂度是 $O(NB)$ 。

具体细节可以看代码来理解，相信大家都能读懂不到 $500B$ 的代码的！
```cpp
int n,b,f[N],dp[N];
int main()
{
	n = read(),b = read();dp[1] = 1;
	for(int i = 1;i <= n;i ++) f[i] = read();
	for(int i = 1;i <= b;i ++) {
		int s = read(),d = read();
		for(int j = 1,p = 1,tmp=0;j <= n;j ++) {
			while(j-p > d) {
				if(dp[p] && f[p] <= s) tmp --;
				++p;
			}
			if(tmp && !dp[j] && f[j] <= s) dp[j] = i;
			if(dp[j]&&f[j]<=s) ++tmp;
		}
		if(dp[n]) {printf("%d",dp[n]-1);return 0;}
	}
	printf("%d ",dp[n]-1);
	return 0;
}
```

---

## 作者：jiang_cheng (赞：0)

## 解题思路：
这道题可以暴力$DP$，想到这就比较简单了。然后描述转移，需要枚举转移前的位置、换的鞋子和到达的位置就行了。终点时穿的第$n$双鞋子，答案就为$n-1$。（注意：鞋子要承受两个地方的积雪才能转移！！！）
## 附上代码：
```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 251;

struct E {
  int s, d;  //鞋子能承受的积雪，鞋子的最大步长
} e[kMaxN];

int n, b;
int a[kMaxN], f[kMaxN];  //每个地方的积雪，转移到每个地方的状态

int main() {
  //freopen("snowboots.in", "r", stdin);
  //freopen("snowboots.out", "w", stdout);
  cin >> n >> b;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= b; i++) {
    cin >> e[i].s >> e[i].d;
  }
  fill(f + 1, f + n + 1, b);                               //初始化状态
  f[1] = 1;                                                //出发时穿的是第一双鞋
  for (int i = 1; i < n; i++) {                            //枚举转移前位置
    for (int j = f[i]; j <= b; j++) {                      //枚举换的鞋子
      for (int o = i + 1; o <= min(n, i + e[j].d); o++) {  //枚举到达位置
        if (e[j].s >= max(a[i], a[o])) {                   //判断能否转移
          f[o] = min(f[o], j);                             // 更新答案
        }
      }
    }
  }
  cout << f[n] - 1;  //终点时穿的鞋子减一就是丢掉鞋的个数
  return 0;
}
```


---

## 作者：Parat_rooper (赞：0)

首先分析题面，他不可能往回走，所以这题有拓扑序。

递推直接走起，令 $f_{i  ,j}$ 表示当前在第 $i$ 块砖，用第 $j$ 双鞋能不能走，转移就枚举 $j$ 之后的一双鞋，再枚举走的步数，看能不能走就成了。答案就是 $f_n$ 中能走的最小的一双。

然后再考虑简化状态，因为对于每一个 $f_{i,j}$ ，$j$ 越小所包含的转移就越多，也就越优。所以考虑状态分组，将所有同一 $i$ 的状态分成一组，然后我们就可以把 $j$ 做为最优化属性了，就完成了一维的递推。

上代码：

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

const int kMaxN = 255;

int n, b, f[kMaxN], dp[kMaxN];

struct boot {
  int s, d;
} a[kMaxN];

int main() {
  cin >> n >> b;
  for (int i = 1; i <= n; i++) {
    cin >> f[i];
  }
  for (int i = 1; i <= b; i++) {
    cin >> a[i].s >> a[i].d;
  }
  for (int i = 1; i <= n; i++) {
    dp[i] = b;  
  }
  dp[1] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = dp[i]; j <= b; j++) {
      for (int k = i + 1; k <= min(n, i + a[j].d); k++) {
        if (a[j].s >= max(f[k], f[i])) {
          dp[k] = min(dp[k], j);
        }
      }
    }
  }
  cout << dp[n] - 1;
  return 0;
}
```


---

## 作者：Constant (赞：0)

## 题意归纳：

有 $N$ 块格子，每块格子上有一个雪的深度 $f_i$ ，要从 $1$ 号格子走到 $N$

号格子，还有 $B$ 双靴子，每双靴子有两个限制，表示最多能在雪深为 $s_i$ 的

格子中行走，每次最多走 $d_i$ 格，而且靴子是按照输入顺序依次使用，如果要

更换靴子，那么换掉的就不能继续用第二次，求最小的靴子更换次数，另外还要注

意的是，每次由于可以走多个格子，只需要考虑开头和结尾的格子即可，这是题意

易错点。

## Solution：

本题可以 $DP$ ，可以记忆化搜索，二者的本质是一样的，不过记忆化搜索的实现

方式在本题显然更加简便，于是我们使用记忆化搜索。

用一个函数 $dfs(k,wz)$ 表示当前的一种状态，表示当前已经用到了第 $k$ 双靴

子，走到了位置 $wz$ 的最小更换次数，考虑如何进入接下来的状态。

总的来谈，这类题目的经典考虑方式是换与不换。

如果不换，每次可以走的最多步数是 $d_k$。

每次在 $dfs$ 内枚举走的步数，更新到 $dfs(k,wz+i)$ 即可。

如果要换，那么考虑换到哪一双靴子，从当前 $k$ 开始枚举换到某双靴子 $i$ 

即可，下一个状态是 $dfs(i,wz)$ 。

既然是记忆化搜索，那么我们用一个数组 $r$ 记录某个状态 $dfs(k,wz)$ 是否

可以达到，如果在搜索过程中发现已经可以达到了，则不需要再次重复做无用

功，直接返回即可。

另外还有一个剪枝，如果当前算出来的最小靴子数比已经求出来的答案还要大

了，那正在枚举的方案一定不是最优的，返回即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int r[300][300],n,b,f[300],s[300],d[300],change,ans=9999999;
void dfs(int k,int wz)
{
    if(change>=ans) return;
    if(r[k][wz]==1) return;
    r[k][wz]=1;
	if(wz==n)
	{
		if(change<ans) ans=change;
		return;
	}
	else
	{
		for(int i=1;i<=d[k];i++)
		{
			if(f[wz+i]<=s[k])
			{
				dfs(k,wz+i);
			}
		}
		for(int i=k+1;i<=b;i++)
		{
			if(f[wz]<=s[i])
			{
				change=change+i-k;
				dfs(i,wz);
				change=change-i+k;
			}
		}
	}
}
int main()
{
	cin>>n>>b;
	for(int i=1;i<=n;i++) cin>>f[i];
	for(int i=1;i<=b;i++) cin>>s[i]>>d[i];
	dfs(1,1);
	cout<<ans;
	return 0;
}
```








---

## 作者：羚羊WANG (赞：0)

[题目传输门](https://www.luogu.com.cn/problem/P4265)

~~相信大家看到这道题的第一眼肯定就是DP吧~~

然后推了三个小时，还是没有推出来~~QAQ~~

终于，在一个美妙的时刻，有了几分思路。

设$DP[i]$表示走到$i$号雪地鞋子编号的最小值

那么我们可以在$ $1$ - $($i$ - $1$)$ $当中转移到这里来

所以$DP[i]$ $=$ $DP[j]$ (穿$dp[j]$号鞋可以走到i)

然而只有这一个条件吗

还有走到第$i$号地方的时候要可以承受住$a[i]$,$a[j]$的雪

~~还有其他的条件吗~~

莫得了

# 上代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
int m;
int a[310];
int dp[310];
struct node{
	int val;
	int s;
}e[310];
signed main(){
	n=read();
	m=read();
	for(register int i=1;i<=n;i++)
		a[i]=read();
	for(register int i=1;i<=m;i++)
		{
			e[i].val=read();
			e[i].s=read();
		}
	for(register int i=1;i<=n;i++)
		dp[i]=10000000;
	dp[1]=1;
	for(register int i=2;i<=n;i++)
		for(register int j=1;j<i;j++)
			for(register int k=dp[j];k<=m;k++)
				{
					if(e[k].val<a[j])
						continue;
					if(e[k].s+j<i || e[k].val<a[i])
						continue;
					dp[i]=min(dp[i],k);
				}
//	for(register int i=1;i<=n;i++)
//		write(dp[i]),puts("");
	write(dp[n]-1);
	return 0;
}

```

最后祝大家$AC$此题

---

## 作者：OfstAutomataMachine (赞：0)

一个DP，个人认为比较毒瘤。

首先，用 $dp(i,j)$ 表示FJ能穿着第 $i$ 号靴子走到第 $j$ 格。

初始状态：$dp(1,1)=1$;

如果 $dp(i,k)=1(k<j)$,则 $dp(l,j)=1|i<l\leq min(n,i+d_j),k<j\leq b,dep_l\leq s_j$。

听上去很复杂，不是吗？

但代码还是很简单的，具体看代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,b,dep[251],s[251],wid[251],dp[251][251];
int main()
{
	cin>>n>>b;
	for(int i=1;i<=n;i++)
		cin>>dep[i];
	for(int i=1;i<=b;i++)
		cin>>s[i]>>wid[i];
	dp[1][1]=1;
	for(int i=1;i<n;i++)
		for(int j=1;j<=b;j++)
			if(dp[i][j])
				for(int l=j;l<=b;l++)
					if(dep[i]<=s[l])
						for(int k=i+1;k<=min(i+wid[l],n);k++)
							if(dep[k]<=s[l])
								dp[k][l]=1;
	for(int i=1;i<=b;i++)
		if(dp[n][i])
		{
			cout<<i-1;
			return 0;
		}
}
```


---

