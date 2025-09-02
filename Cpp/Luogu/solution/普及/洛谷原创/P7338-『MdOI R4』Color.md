# 『MdOI R4』Color

## 题目描述

小 M 同学有一张 $2$ 行 $n$ 列的方格纸，一开始所有格子都是白色的。

她决定对一些格子染色，具体地，每次她会选择两个**相邻的（四联通的，也就是有公共边的）白色**格子，其中一个染成红色，另一个染成蓝色。

她的目标是通过**任意次操作**让指定的一些格子变成红色，**对其他格子没有要求**。请你帮她判断一下，能否通过上述操作达成目标呢？

## 说明/提示

【样例解释】

![temp.png](https://i.loli.net/2020/09/27/oCRpYnPAlFk7GuS.png)

上图中左侧为第一组测试数据的一种方案，右侧为第三组测试数据的一种方案，对于第二组测试数据，并没有满足要求的方案。

【数据规模与约定】 

**本题采用捆绑测试**

|子任务编号|$n\le$|特殊性质|$T\le$|分值|
|:-|:-|:-|:-|:-|
|$1$|$3$|无特殊限制|$10$|$10$|
|$2$|$10$|无特殊限制|$10$|$20$|
|$3$|无特殊限制|所有 $1$ 都在同一行|$10$|$1$|
|$4$|无特殊限制|$1$ 不超过 $4$ 个|$10$|$13$|
|$5$|$10^3$|无特殊限制|$10$|$25$|
|$6$|无特殊限制|无特殊限制|$10$|$30$|
|$7$|$16$|无特殊限制|$65536$|$1$|

对于所有数据，满足 $1\le n\le 10^5$，$\sum n\le 2^{20}$。

## 样例 #1

### 输入

```
3
5
01110
10010
5
11000
01100
5
00101
10100
```

### 输出

```
RP
++
RP```

# 题解

## 作者：yummy (赞：10)

# B. Color

我验BF姐姐出的题，BF 姐姐验我出的题，我和 BF 贴贴/qq

这题的题目背景是 yummy 第一次尝试歌词集句呢，接得不是很顺，大家凑合着看哈。

字非常的丑，但是也只能这样，至少能识别。

这些歌都来自 Grace VanderWaal，第一次知道她是在 *Stargirl* 这部电影里面呢。

## Subtask 1

手玩。首先 $1$ 超过 $n$ 个显然可以直接输出`++`。

考虑 $1$ 不超过 $n$ 个的情况，$n=1\operatorname{or} 2$ 时显然输出`RP`。

对于$n=3$ 的情况，观察发现，应该输出`++`，当且仅当有一个 $1$ 的周围全都是 $1$。

## Subtask 2

显然这道题换一种说法就是：

> 在 $2$ 行 $n$ 列的方格纸中，对于每个 $1$ 找一个相邻 $0$，且每个 $1$ 对应的 $0$ 互不相同。

那么 $n\le10$ 的方法就很显然了。首先，当 $1$ 多于 $n$ 个时，直接输出`++`。

接下来，对于每一个 $1$，暴力枚举它对应哪一个相邻的 $0$，然后进行判断。

每个 $1$ 对应的 $0$ 的可能不超过 $3$ 种，故总时间复杂度 $O(Tn3^n)$，在 $n\le 10$ 时稳。

## Subtask 3

读题分。由于其中一行不作要求，故对于每个 $1$ ，选取这一列的 $0$ 即可。故答案必为`RP`。

## Subtask 4

手玩。第一步仍然是“如果一个 $1$ 的周围全是 $1$ 则直接 `++`”。

相比于 Subtask 1，这个 Subtask 需要多进行的一个特判就是形如样例第 $2$ 组数据这样的形状。

## Subtask 5

我觉得可能有二维 DP 做法，但是目前没有想到。

该 Subtask 是为了照顾大常数选手，以及 Subtask 6 写假了的选手。

**Update：根据赛时情况发现还有匈牙利二分图匹配的选手和网络流大常数选手。**

## Subtask 6&7

我们从左往右一列一列满足。

假设前 $i-1$ 列的 $1$ 都找到了 $0$，考虑第 $i$ 列的 $1$ 怎么找 $0$。

首先，若这个 $1$ 的左边是没被占用的 $0$，则优先选择这个 $0$，因为从第 $i+1$ 列开始，这个 $0$ 是不会被用到的。

如果左边不是没被占用的 $0$，那么我们应该优先选择同一列的 $0$，因为同一列的 $0$ 从第 $i+2$ 列开始就不会被用到，但是右边的 $0$ 从第 $i+3$ 列开始才不会被用到。

如果某一个 $1$ 的左边，同一列和右边都无法选择，那么输出`++`；如果最后一列也成功选择，那么输出 `RP`。

时间复杂度 $\Theta(Tn)$，常数较小。

Subtask 7 是赛后添加的，目的是让假的算法（如一些细节未考虑）通不过。

然后我发现这个 Subtask 有一个副作用就是直接 `memset` 的同学会 TLE，但 TLE 的似乎比WA多。

但是我相信随着时间的推移TLE会变少，因为后来的应该不会直接交比赛代码吧。

## std
这题题面简洁，代码清新，是不可多得的贪心入门题，为良心出题人点赞！

(请注意 std 的数组从 $0$ 开始。）
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char up[100005],down[100005];
bool cup(int x){//尝试给上面这行第x个位置染色
	if(up[x]!='0')return 1;
	up[x]='2';return 0;}
bool cdown(int x){//尝试给下面这行第x个位置染色
	if(down[x]!='0')return 1;
	down[x]='2';return 0;}
int main(){
	for(scanf("%d",&t);t;t--){
		scanf("%d%s%s",&n,up,down);
		bool flag=1;
		if(up[0]=='1'&&cdown(0)&&cup(1)||down[0]=='1'&&cup(0)&&cdown(1))//对于第0列因为没有上一列我们需要特判
			flag=0;
		for(int i=1;i<n;i++)
			if(up[i]=='1'&&cup(i-1)&&cdown(i)&&cup(i+1)||down[i]=='1'&&cdown(i-1)&&cup(i)&&cdown(i+1)){
			//利用&&的短路特性，即&&前面的语句为false就会不执行后面的语句，而且&&是右结合的
				flag=0;break;
			}
		if(flag)puts("RP");
		else puts("++");
	}
    return 0;
}
```

## Further More

这题在行数 $h\ge 3$ 时怎么做呢？

由于我一开始一直准备的贪心解法，所以我顺延贪心思想，一直觉得这题需要状压 DP。

具体地，$dp(S,k)$ 表示当前在讨论第 $k$ 列，这列 $h$ 个格子（是 $(1)$ 不是 $(0)$ 未占用的 $0$）能否满足。

对于这一列的每个格子：

- 如果是 $1$ 则先找同一列占用一个 $0$，不行找下一列。
- 如果是未占用的 $0$，则看一眼下一列同一行是不是 $1$，是的话把下一列这个格子变成已占用的 $0$。
- 如果是已占用的 $0$ 那么没什么事了。

状态有 $n\cdot 2^h$ 种，而总复杂度就是每个状态中（ $1$ 左移 $010$ 子串的数量）的和。

我们可以将其近似地看作 $1$ 左移 $\min(\text{0 的个数,1 的个数})$，计算得复杂度为 $O(n\cdot 3^h)$。

---

但是赛场上，我发现有些人使用了一种比正解码量大很多的算法：二分图最大匹配。

具体地，考虑对于所有的 $1$，向有公共边的所有 $0$ 连一条边，然后使用Dinic跑二分图最大匹配。

由于此时边数和格子数同阶，故总时间复杂度为 $\Theta(Tn\sqrt{n})$，$10\times 10^5\times\sqrt{10^5}=3.16\times 10^8$。

再加上很难卡满，所以实际上也是可以过的。而且这可以用于 $h\ge 3$ 的情况。

yummy 并不打算搞加强版，因为这个非常套路，不管状压还是网络流都接近板子。


---

## 作者：cyffff (赞：4)

# P7338 Color
#### [_传送门_](https://www.luogu.com.cn/problem/P7338)
## 思路
对于这道题，有一个~~显然的~~贪心策略，但是我太弱了赛时没想到...

这种贪心可以去看别的 dalao 的题解，我这篇题解讲述一种不一样的解题思路。

**二分图最大匹配**

不会的可以左转模板区 [->Click Here<-](https://www.luogu.com.cn/problem/P3386).

对于一个要求是红色的点，向周围三个方向不要求为红色的点连边，其中要求为红色的点互不连边，不要求的也互不连边，显然，这是一张二分图。

然后设有 $x$ 个点要求为红色，则如果最大匹配数为 $x$，就代表可行，否则不可行。

对于这道题，利用这种方法可以拓展到 $n\times m$ 的矩阵上。

这里有个细节需要注意，每次匹配不能直接 $memset$，这样会导致被卡常。需要打上时间戳，匹配时改一改即可，具体实现见代码。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,maxn,p[2][N],head[N<<1],match[N<<1],cnt,ans,tim;
int vis[N<<1];
struct edge{
	int to,next;
}a[N<<2];
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline int read(){
		reg char ch=gh();
		reg int x=0;
		while(ch<'0'||ch>'9')   ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return x;
	}
	inline int getaint(){
		reg char ch=gh();
		while(ch<'0'||ch>'1') ch=gh();
		return ch-'0';
	}
}using namespace IO;
inline void add(int u,int v){
	cnt++;
	a[cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
inline bool dfs(int x){
	for(int i=head[x];i;i=a[i].next){
		int t=a[i].to;
		if(vis[t]!=tim){
			vis[t]=tim;
			if(!match[t]||dfs(match[t])){
				match[t]=x;
				return true;
			}
		}
	}
	return false;
}
inline void init(){
	cnt=0;
	ans=0;
}
int main(){
	int t=read();
	while(t--){
		init();
		n=read();
		for(int j=0;j<=1;j++){
			for(int i=1;i<=n;i++){
			    head[j*n+i]=match[j*n+i]=0;
				p[j][i]=getaint();
			}
		}
		int cnt=0;
		for(int i=0;i<=1;i++){
			for(int j=1;j<=n;j++){
				if(p[i][j]){
					if(j!=1&&!p[i][j-1]){
						add(n*i+j,n*i+j-1);
					}
					if(j!=n&&!p[i][j+1]){
						add(n*i+j,n*i+j+1);
					}
					if(!p[!i][j]){
						add(n*i+j,n*(!i)+j);
					}
					cnt++;
				}
			}
		}
		for(int i=1;i<=n+n;i++){
			tim++;
			ans+=dfs(i);
		}
		if(ans==cnt){
			puts("RP");
		}else{
			puts("++");
		}
	}
	return 0;
}
/*
Time:96ms
Memory:7.74MB 
*/
```
再见了 qwq~

---

## 作者：SUNCHAOYI (赞：3)

这是一道不错的贪心题目，同时也考察了选手们的读题仔细程度。先给出几个关键点：

1. 只能对两个**相邻**且均为**白色**的格子进行染色，也就是说染色是不能够覆盖的

2. 对于输入中的 `1` 的位置一定要为**红色**，其余位置随意。

以某行的第 $i$ 列 ($1 \le i \le n$)为基准，**若所在的两个格子均存在**，则有可能的三种染法：
1. $p_i$ 与 $q_i$
2. $p/q_i$ 与 $p/q_{i - 1}$ 
3. $p/q_i$ 与 $p/q_{i + 1}$

这其中有一个**贪心的顺序**，若调换可能会出现错误。想要去进行最优的染色一定是按照 $2-> 1 -> 3$ 的顺序才能充分利用所有的白色格子。想通这个后，接下去就是一些细节的实现了。

```cpp
n = read ();
scanf ("%s%s",da,db);
ok = 1;
for(register int i = 0;i <= n;++i) ca[i] = cb[i] = 0;//注意一下，不要用 memset 会超时哦
//0 white 1 red 2 blue
for (register int i = 0;i < n;++i)
{
	if (da[i] == '1')//第一行的第 i 块需要被染色
	{
		if (ca[i] == 1) ;//已经被染成目标色
        	//注意要两个格子均存在且均为白色才能染
		else if (!ca[i - 1] && !ca[i] && i >= 1) ca[i - 1] = 2,ca[i] = 1;//2
		else if (!ca[i] && !cb[i] && db[i] == '0') ca[i] = 1,cb[i] = 2;//1，这里要注意若两行均为 1 则不能进行此操作，否则不是最优方法/无法成功染色
		else if (!ca[i + 1] && !ca[i] && da[i + 1] == '0' && i < n - 1) ca[i] = 1,ca[i + 1] = 2;//3
		else {ok = 0;break;}//无法实现
	}
	if (db[i] == '1')//第二行的第 i 块需要被染色
	{
		if (cb[i] == 1) ;
		else if (!cb[i - 1] && !cb[i] && i >= 1) cb[i - 1] = 2,cb[i] = 1;
		else if (!ca[i] && !cb[i] && da[i] == '0') ca[i] = 2,cb[i] = 1;	
		else if (!cb[i + 1] && !cb[i] && db[i + 1] == '0' && i < n - 1) cb[i] = 1,cb[i + 1] = 2;
		else {ok = 0;break;} 
	}
}
if (ok) printf ("RP\n");
else printf ("++\n");
} 
```

---

## 作者：Caesium (赞：3)

## P7338 color 题解
本题的题意主要是，每次要选两个四连通格子，两个格子**必须都没染色**，最后要把指定的染成红色。
也就是说，我们要对每个要涂成红色的格子匹配一个专属的白色格子。

一开始做的时候没有看到 $ 2$ 行 $ n$ 列，想了很久怎么做（wtcl）。

不说了，说多了都是泪QAQ。

对于这个题，我的思路是一个贪心的解法，因为对于一个格子，如果我么假定左边都已经完成了涂色，由于我涂在右边有可能会占用右边的生存资源，而左边的已经分配完毕，所以我如果涂在左边一定不会比我涂在右边，或者下面（上面）差，然后再依次考虑下面（上面），右边。

至此本题就做出来了，细节请看代码。
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n;
char ch;
string a;//a是读入上面那一排
string b;//b是下面那一排
bool flag;

bool judge(int k)//判断一列格子能否放置
{
	if (a[k] == '1')//如果上面有格子（如果上下都有格子，先做那个都一样，留给读者证明
	{
		if (a[k-1] == '0') a[k-1] = '2';//优先左边
		else if (b[k] == '0') b[k] = '2';//再下面
		else if (a[k+1] == '0') a[k+1] = '2';//右边
		else return false;
	}
	if (b[k] == '1')
	{
		if (b[k-1] == '0') b[k-1] = '2';
		else if (a[k] == '0') a[k] = '2';
		else if (b[k+1] == '0') b[k+1] = '2';
		else return false;
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);//加速，因为有字符串而我太蒟了不会写快读
	cin >> t;
	while(t--)
	{
		cin >> n;
		flag = true;
		cin >> a >> b;
		a = '2' + a + '2';//首位加个2，告诉编译器这里不能放
		b = '2' + b + '2';
		for (int i = 1; i <= n; i++)
		{
			if (!judge(i))//返回false，不能放置
			{
				cout << "++" << endl; 
				flag = false;//
				break;
			}
		}
		if (flag)
		{
			cout << "RP" << endl;
		}
	}
	return 0;
 } 
```


---

## 作者：囧仙 (赞：3)

## 题目大意

> 有一个 $2\times n$ 的矩阵，其中有若干格需要涂成红色。你可以选择两个相邻的格子，其中一个涂成蓝色，另外一个涂成红色；但是你不能重叠，也不能超出矩阵范围。询问是否存在一个方案满足题目条件。

## 题解

**结论**：从左到右考虑每个红色格子，**依次**考虑其左侧、下侧（上侧）、右侧能否涂色。如果能，就涂色；否则判断无解。

考虑如何证明：

- 由于我们是从左往右考虑，因此考虑到第 $i$ 列时，前 $i-1$ 列的红色格子已经达成要求。于是只考虑下侧（上侧），以及右侧的情况。

- 如果这两个情况只能选择其中之一，显然只能选择那种方案。

- 否则选择下方（上方）显然不劣。因为选择后只会影响到第 $i+1$ 列的红色格子；此时由于当前考虑的格子右侧的格子也能选择，因此第 $i+1$ 列红色格子不会受到影响。

$$\def{\arraystretch}{1.5}\begin{array}{|c|c|} \hline
\textbf{\color{red}红} & \textbf{空} \cr \hline
\textbf{空} & \textbf{\color{red}红} \cr \hline
\end{array} \qquad
\begin{array}{|c|c|} \hline
\textbf{\color{red}红} & \textbf{空} \cr \hline
\textbf{空} & \textbf{空} \cr \hline
\end{array}
$$

如图，显然选择下方（或上方）的空格不会更劣。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN =1e6+3;
char S[MAXN],T[MAXN]; int n;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    dn(qread(),1,TT){
        n=qread(); scanf("%s%s",S+1,T+1);
        S[n+1]=T[n+1]='!';
        up(1,n,i){
            if(S[i]=='1'){ if(S[i-1]=='0') S[i-1]='!';
            else if(T[i]=='0') T[i]='!'; else if(S[i+1]=='0') S[i+1]='!'; else goto no;}
            if(T[i]=='1'){ if(T[i-1]=='0') T[i-1]='!';
            else if(S[i]=='0') S[i]='!'; else if(T[i+1]=='0') T[i+1]='!'; else goto no;}
        }
        puts("RP"); goto yes; no: puts("++"); yes:;
    }
    return 0;
}
```

---

## 作者：cmll02 (赞：0)

考虑涂色顺序。

从左往右扫一遍。

假如目标块的左边是白的，那一定往左涂蓝色（反正用不上这个格子）。

如果不行，就往上/下涂。

如果还不行，就只能往右了。

如果还不行，那就 `++`。

这为什么是正确的？

优先往左显然正确，对于上下和往右：

![](https://cdn.luogu.com.cn/upload/image_hosting/ktgx4hsi.png)

Code：
```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//#define int long long
//char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
	int num = 0,f=1; char c = getchar();
	while (c<48 || c>57)f=(c=='-'?-1:f),c = getchar();
	while (c >= 48 && c <= 57)num = (num << 3) + (num << 1) + (c ^ 48), c = getchar();
	return num*f;
};
inline int read1d()
{
	int num = 0,f=1; char c = getchar();
	while (c<48 || c>57)c = getchar();
	//while (c >= 48 && c <= 57)num = (num << 3) + (num << 1) + (c ^ 48), c = getchar();
	return c-48;
};
int a[100005][2],dp[100005][2];
signed main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		for(int i=0;i<2;i++)
			for(int j=0;j<n;j++)
				a[j][i]=read1d(),dp[j][i]=a[j][i];
		for(int i=0;i<n;i++)
		{
			if(a[i][0])
			{
				if(i>0&&dp[i-1][0]==0)dp[i-1][0]=1;
				else if(dp[i][1]==0)dp[i][1]=1;
				else if(i<n-1&&dp[i+1][0]==0)dp[i+1][0]=1;
				else {puts("++");goto qaq;}
			}
			if(a[i][1])
			{
				if(i>0&&dp[i-1][1]==0)dp[i-1][1]=1;
				else if(dp[i][0]==0)dp[i][0]=1;
				else if(i<n-1&&dp[i+1][1]==0)dp[i+1][1]=1;
				else {puts("++");goto qaq;}
			}
		}
		puts("RP");
		qaq:;
	}
	return 0;
}
```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7338)

考虑一个直观的贪心。

一般地，对于一个格子，要把它染成红色，那么它的周围必须要有至少一个空格子用来染成蓝色。也就是说，如果答案合法，那么必然每个红色格子旁边都有一个它自己专属的蓝色格子。

那么可以直接一列列模拟染色的过程。把染成红色的格子标记为$1$，染成蓝色的格子标记为$2$，白色格子标记为$0$。

当然有可能出现这种情况：一个红色格子周围有不止一个白色格子可供染色。那么染色的优先级是向左$>$向下$>$向右。

这个结论证明非常显然。因为向左染色不会对任何未枚举过的格子造成影响，向下染色可能会对右下的一个格子造成影响，而向右染色会对右下和向右两格的格子都造成影响，所以向左$>$向下$>$向右。

时间复杂度$O(Tn)$，可以通过本题。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned long long
using namespace std;
int read()
{
    int x=0,f=1;
	char ch=getchar();
    while(ch<'0'||ch>'9')
    {
      	if(ch=='-')
      		f=-1;
      	ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
      	x=x*10+ch-'0';
      	ch=getchar();
    }
    back x*f;
}
int n,m,t,k,sum;
string p,q;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		cin>>p>>q;
		for(ri i=0;i<n;i++)
		{
			if(p[i]=='1')
			{	
				sum=0;
				if(i>0&&p[i-1]=='0'&&sum!=1)
				{
					p[i-1]='2';
					sum=1;
				}	
				if(q[i]=='0'&&sum!=1)
				{
					q[i]='2';
					sum=1;
				}
				if(i<n-1&&p[i+1]=='0'&&sum!=1)
				{
					p[i+1]='2';
					sum=1;
				}
				if(sum!=1)
				{
					cout<<"++"<<endl;
					break; 
				}
			}
			if(q[i]=='1')
			{	
				sum=0;
				if(i>0&&q[i-1]=='0'&&sum!=1)
				{
					q[i-1]='2';
					sum=1;
				}
				if(p[i]=='0'&&sum!=1)
				{
					p[i]='2';
					sum=1;
				}	
				if(i<n-1&&q[i+1]=='0'&&sum!=1)
				{
					q[i+1]='2';
					sum=1;
				}
				if(sum!=1)
				{
					cout<<"++"<<endl;
					break;
				}
			}
			if(i==n-1)
				cout<<"RP"<<endl;
		}
		
	}
    back 0;
}
```

---

## 作者：daiarineko (赞：0)

## 0. 题目描述

小 M 同学有一张 $2$ 行 $n$ 列的方格纸，一开始所有格子都是白色的。

她决定对一些格子染色，具体地，每次她会选择两个**相邻的（四联通的，也就是有公共边的）白色**格子，其中一个染成红色，另一个染成蓝色。

她的目标是通过**任意次操作**让指定的一些格子变成红色，**对其他格子没有要求**。请你帮她判断一下，能否通过上述操作达成目标呢？

## 1. 题目分析&主要代码

考察点：贪心

题目难度：普及/提高-

时间复杂度：$\Theta(n)$

### 题目分析

赛时我先想到的是傻做法，暴力搜索，时间 $\Theta(\operatorname{feb}(n))$（注：这是递推出来的结果），而经（Python）测试，$\operatorname{feb}(1000)\approx7e+200$，这肯定是不行的。

于是我仔细看了下数据范围，1e6，能行的只有 $\Theta(n)$ 的贪心和 $\Theta(n\sim n^{1.5})$（本蒟蒻算不出来）的动规。

先试试贪心，~~没准还能爆标呢（事实证明除了 $\Theta(\log n)$ 以外不可能爆标）~~

贪心，怎么贪呢？我最开始想到了这样的设计：判断每一个 $2\times2$ 区域如果一个**红方块**（指必须涂红的方块）边上有一个方块没有规定颜色，那么这个红方块就是“安全”（指不会导致无方案）的。否则如果红方块在右面，那么这个红方块还有可能恢复“安全”，因为下一个区域还包含这个红方块。如果红方块在左边，就完全废了，直接输出 `++`。

后来（大概十分钟）我又想到了一个完美的方法，把上面的“在左边”“在右边”合并起来，就得到了一个更好的方法：我们遍历 $i$ 从左到右，如果 $i$ 列 $1$（索引从 $1$ 开始）行是红方块，那么按照 `左->上->右` 判断，如果某个方向可以放蓝方块，就放蓝方块。这样优先判断上次遍历剩下的方块，达到了局部最优性。  
如果 $i$ 列 $2$ 行是红方块，这时候还是如此，不过变成了 `左->下->右` 。  
如果某一次判断完成后没有可放的地方，那么说明失败，输出 `++`。遍历全部完成，输出 `RP`。

这样，我们成功在 $\Theta(n)$ 复杂度下完成了这样的判断。

### 主要代码

注意讲解时索引从 $1$ 开始，但代码索引从 $0$ 开始！

首先，使用两个 $(1e6,2)$ 的二维数组 `p` 和 `u`，`p` 是题面的变量名，代表是否必须涂红色；`u` 就是 `used`，代表某格是否已经涂上蓝色。
```cpp
bool p[1000000][2],u[1000000][2];
```

接下来我们使用一个“保护壳”，就是一个判断索引是否合法的函数，例如第 $1$ 列，我们不可能再判断左侧，为了防止读取到错误的值导致 WA。因为这个函数判断的是 `p` 数组，我们取名为 `p_`。
```cpp
inline bool p_(int x,int y){
    if(x<0||x>=n||y<0||y>=2){
        return 0;
    }
    return 1;
}
```

好了，现在才是重头戏，主函数 `do_`（防关键字）。
```cpp
cin>>n;
memset(u,0,sizeof(u));//多测不清空，爆零两行泪
string s;
cin>>s;
for(int i=0;i<n;++i){
    p[i][0]=s[i]-'0';
}
cin>>s;
for(int i=0;i<n;++i){
    p[i][1]=s[i]-'0';
}
```
读入部分不用多说了，不过这里用到了一个小技巧，因为输入的 `01` 串是连起来的，所以不能直接输入一个数，采用先输入成字符串，再逐字符拷贝的方式。**注意这里有个大坑，记得 `-'0'` 哦！**  
大大大坑：**多 测 不 清 空，爆 零 两 行 泪**！

接下来是主循环的循环体：
```cpp
if(p[i][0]){
    bool f=0;
    if(p_(i-1,0)){
        if(p[i-1][0]==0&&u[i-1][0]==0){
            u[i-1][0]=1;
            f=1;
        }
    }
    if(f==0){
        if(p[i][1]==0&&u[i][1]==0){
            u[i][1]=1;
            f=1;
        }
    }
    if(f==0){
        if(p_(i+1,0)){
            if(p[i+1][0]==0&&u[i+1][0]==0){
                u[i+1][0]=1;
                f=1;
            }
        }
    }
    if(f==0){
        cout<<"++"<<endl;
        return;
    }
}
```
`f` 代表是否已经成功涂上蓝色格子。

左侧判断：
```cpp
if(p_(i-1,0)){
    if(p[i-1][0]==0&&u[i-1][0]==0){
        u[i-1][0]=1;
        f=1;
    }
}
```
注意用到的 `p_` 函数。

上/下判断：
```cpp
if(f==0){
    if(p[i][1]==0&&u[i][1]==0){
        u[i][1]=1;
        f=1;
    }
}
```
注意这里又没有用到 `p_` 函数，因为只有两行，两行的代码可以分开写，一段只向下判断，一段只向上判断。

右侧判断：
```cpp
if(f==0){
    if(p_(i+1,0)){
        if(p[i+1][0]==0&&u[i+1][0]==0){
            u[i+1][0]=1;
            f=1;
        }
    }
}
```

再不行就是这组数据不行了，输出 `++`。
```cpp
if(f==0){
    cout<<"++"<<endl;
    return;
}
```
没必要继续执行下去。

这只是第一行的代码，第二行代码同理，可以复制后少量修改，见完整代码。

主函数没必要看，不过还是放出来吧：
```cpp
int main(){
    ios::sync_with_stdio(false);//IO加速
    int t;
    cin>>t;
    while(t--){//多测专用
        do_();
    }
    return 0;
}
```

## 2. 完整代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
bool p[1000000][2],u[1000000][2];
int n;
inline bool p_(int x,int y){
    if(x<0||x>=n||y<0||y>=2){
        return 0;
    }
    return 1;
}
void do_(){
    cin>>n;
    memset(u,0,sizeof(u));
    string s;
    cin>>s;
    for(int i=0;i<n;++i){
        p[i][0]=s[i]-'0';
    }
    cin>>s;
    for(int i=0;i<n;++i){
        p[i][1]=s[i]-'0';
    }
    for(int i=0;i<n;++i){
        if(p[i][0]){
            bool f=0;
            if(p_(i-1,0)){
                if(p[i-1][0]==0&&u[i-1][0]==0){
                    u[i-1][0]=1;
                    f=1;
                }
            }
            if(f==0){
                if(p[i][1]==0&&u[i][1]==0){
                    u[i][1]=1;
                    f=1;
                }
            }
            if(f==0){
                if(p_(i+1,0)){
                    if(p[i+1][0]==0&&u[i+1][0]==0){
                        u[i+1][0]=1;
                        f=1;
                    }
                }
            }
            if(f==0){
                cout<<"++"<<endl;
                return;
            }
        }
        if(p[i][1]){
            bool f=0;
            if(p_(i-1,1)){
                if(p[i-1][1]==0&&u[i-1][1]==0){
                    u[i-1][1]=1;
                    f=1;
                }
            }
            if(f==0){
                if(p[i][0]==0&&u[i][0]==0){
                    u[i][0]=1;
                    f=1;
                }
            }
            if(f==0){
                if(p_(i+1,1)){
                    if(p[i+1][1]==0&&u[i+1][1]==0){
                        u[i+1][1]=1;
                        f=1;
                    }
                }
            }
            if(f==0){
                cout<<"++"<<endl;
                return;
            }
        }
    }
    cout<<"RP"<<endl;
    return;
}
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        do_();
    }
    return 0;
}
```
## 3. ~~出题人挖坑不埋~~

1. 多测不清空，爆零两行泪；
2. `p_` 函数很重要，虽然没测过，但 RE 就不值得了；
3. 别忘了判断如果 `f==0` 才能继续判断，否则一个红格就会导致最多三个格变蓝，会导致 WA；
4. 输入用 `string`（`char` 亦可），并且记得 `-'0'`。

## 4. Update

写题解写到一半，发现数据加强我 TLE 了，检查题面发现 $T$ 变成了 $65536$，别人居然还能 $17ms$ 过，所以是常数导致我 TLE。分析一下，也就是读入可以优化。我先是在读入的同时改一下 `u` 数组，去掉 `memset`，然后又发现 `string` 可以搞成 `char`，但是我用了 `iostream` 优化，所以只能继续用 `cin cout`。令我惊喜的是，$66ms$ 成功 AC。新的代码重新展示一下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
bool p[1000000][2],u[1000000][2];
int n;
inline bool p_(int x,int y){
    if(x<0||x>=n||y<0||y>=2){
        return 0;
    }
    return 1;
}
void do_(){
    cin>>n;
    char c;
    for(int i=0;i<n;++i){
        cin>>c;
        p[i][0]=c-'0';
        u[i][0]=0;
    }
    for(int i=0;i<n;++i){
        cin>>c;
        p[i][1]=c-'0';
        u[i][1]=0;
    }
    for(int i=0;i<n;++i){
        if(p[i][0]){
            bool f=0;
            if(p_(i-1,0)){
                if(p[i-1][0]==0&&u[i-1][0]==0){
                    u[i-1][0]=1;
                    f=1;
                }
            }
            if(f==0){
                if(p[i][1]==0&&u[i][1]==0){
                    u[i][1]=1;
                    f=1;
                }
            }
            if(f==0){
                if(p_(i+1,0)){
                    if(p[i+1][0]==0&&u[i+1][0]==0){
                        u[i+1][0]=1;
                        f=1;
                    }
                }
            }
            if(f==0){
                cout<<"++"<<endl;
                return;
            }
        }
        if(p[i][1]){
            bool f=0;
            if(p_(i-1,1)){
                if(p[i-1][1]==0&&u[i-1][1]==0){
                    u[i-1][1]=1;
                    f=1;
                }
            }
            if(f==0){
                if(p[i][0]==0&&u[i][0]==0){
                    u[i][0]=1;
                    f=1;
                }
            }
            if(f==0){
                if(p_(i+1,1)){
                    if(p[i+1][1]==0&&u[i+1][1]==0){
                        u[i+1][1]=1;
                        f=1;
                    }
                }
            }
            if(f==0){
                cout<<"++"<<endl;
                return;
            }
        }
    }
    cout<<"RP"<<endl;
    return;
}
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        do_();
    }
    return 0;
}
```

所以说，有时候静态差错真的、真的、真的很重要！（手机端改完被卡没了，还得重改。。。）

---

## 作者：novax (赞：0)

#### 题意
有一个 $2 \times n$ 的方格纸，其中一些格子必须被涂成红色，每次涂两个相邻的格子，一个涂成红色，另一个涂成蓝色。给你希望涂成的样子，问是否可能实现。

#### 思路
对于每个需要被染成红色的格子，有三种可能的染色方法：横着染色且当前格子在右侧，如下方左图；竖着染色；横着染色且当前格子在左侧，如下方右图。

![](https://cdn.luogu.com.cn/upload/image_hosting/n2tv1eto.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/pe2if4kr.png)

我们可以从左到右，按列处理需要被染色成红色的格子。因为是从左往右处理，所以当我们碰到需要被染成红色的格子时，如果这个格子左侧没有被染过颜色，则优先按照第一种方法染色（即蓝色格子在左边），因为给左侧未染色的点染上颜色不会对接下来的处理产生任何影响，所以优先按第一种方法染色；如果这个格子左边被染过颜色了，那么如果它同一列的格子没被染色，就优先把与它同一列的格子染上蓝色，因为在同一列染色最多只会对当前格子右侧的一列造成影响，影响较小，所以这种情况下优先选择第二种方法；如果当前点的左侧、同一列都被染过颜色，那么如果当前点的右侧还没被染过颜色，就把右侧染成蓝色。这种染色方式可能会影响右侧两列的染色，影响最大，所以当前两种情况都不满足时，用第三种方法染色；如果当前点需要被染成红色，但同行的左/右，同列都被染过颜色了，说明不存在合法的染色方法使当前点被染成红色，此时输出```++```，如果到了最后一列都合法，则输出```RP```。

时间复杂度 $O(Tn)$。

#### 代码

```cpp
#include <cstdio>
#include <cstring>
int T;
char p[100010],q[100010];//读入的01串
int u1[100010],u2[100010];//记录第一行，第二行的第i个格子是否被染过颜色 0为没被染过，1为已经/需要被染色
int N;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		int i,fl;
		fl=0;
		scanf("%d",&N);
		scanf("%s%s",&p,&q);
		for(i=0;i<N;i++)
		{
			u1[i+1]=p[i]-'0';
			u2[i+1]=q[i]-'0';
		} 
		u1[0]=1;u2[0]=1;//注意两侧边界不能染色
		u1[N+1]=1;u2[N+1]=1;
		for(i=1;i<=N;i++)
		{
			if(p[i-1]=='1')//处理第一行
			{
				if(u1[i-1]==0)
					u1[i-1]=1;
				else
					if(u2[i]==0)
						u2[i]=1;
					else
						if(u1[i+1]==0)
							u1[i+1]=1;
						else
						{
							fl=1;
							break;
						}
			}
			if(q[i-1]=='1')//处理第二行
			{
				if(u2[i-1]==0)
					u2[i-1]=1;
				else
					if(u1[i]==0)
						u1[i]=1;
					else
						if(u2[i+1]==0)
							u2[i+1]=1;
						else
						{
							fl=1;
							break;
						}
			}
		}
		if(fl)
			printf("++\n");
		else
			printf("RP\n");
	}
} 
```
注意：本题虽然有多组数据，但使用```memset```容易在sub7TLE。

---

## 作者：Vocalise (赞：0)

重开博客。（

正解是贪心，但是完全不会贪心，于是强行写了一个压 4 位 DP 的大常数解法。

然后还挂了两发（

$f_{i,v}$ 表示考虑前 $i$ 列，第 $i$ 列与第 $i + 1$ 列的是否占用状态形如 $v$ （1 表示占用，0 表示空白）是否可行。

是这样压位的：（$k$ 表示二进制第 $k$ 位）

```
  i i+1
p 0 2
q 1 3
```

发现有 $4$ 位，用 0~15 的整数表示。

注意，我们对第 $i$ 列的状态不考虑 $i + 1$ 列是否有红色。

还有，有一些状态是不可能存在的，如 $8$，$9$，但我们保留。

讨论一下。

### Case 1: $p_i=q_i=0$

空行。

于是我们直接把 $i -1$ 列的后两位状态搬过来就行。 $i+1$ 列两位一定为空。

```cpp
			for(int j = 0;j < 16;j++)
				f[i][j >> 2] |= f[i - 1][j];
```

### Case 2: $p_i=1,q_i=0$

讨论红格子向哪边染色。

#### 左

$i-1$ 的 $0,2$ 位没有，$1$ 位可能有。

若 $3$ 位有，对应 $i$ 的状态 $3$；

若没有，对应状态 $1$。

```cpp
			f[i][1] = f[i - 1][0] | f[i - 1][2];
			f[i][3] = f[i - 1][8] | f[i - 1][10];
```

#### 下

$i-1$ 的 $2,3$ 位没有，剩下的 $0,1$ 位随便。对应的是 $i$ 的状态 $3$。

```cpp

			for(int j = 0;j < 4;j++) f[i][3] |= f[i - 1][j];
```

#### 右

$i-1$ 的 $2$ 位没有，$0,1$ 位随便。

若 $3$ 位有，对应 $i$ 的状态 $7$；

若没有，对应状态 $5$。

```cpp
			for(int j = 0;j < 4;j++) f[i][5] |= f[i - 1][j];
			for(int j = 0;j < 4;j++) f[i][7] |= f[i - 1][8 + j];
```

### Case 3: $p_i=0,q_i=1$

同 Case 2，换位即可。

```cpp
			f[i][2] = f[i - 1][0] | f[i - 1][1];
			f[i][3] = f[i - 1][4] | f[i - 1][5];
			for(int j = 0;j < 4;j++) f[i][3] |= f[i - 1][j];
			for(int j = 0;j < 4;j++) f[i][10] |= f[i - 1][j];
			for(int j = 0;j < 4;j++) f[i][11] |= f[i - 1][4 + j];
```

### Case 4: $p_i=q_i=1$

讨论上下两格红格向哪边指。

#### 都左

此时 $i-1$ 必须没有。对应状态 $3$。

```cpp
			f[i][3] = f[i - 1][0];
```
#### 都右

$i-1$ 位 $2,3$ 位没有，$0,1$ 位随便取。对应状态 $15$。

```cpp
			for(int j = 0;j < 4;j++) f[i][15] |= f[i - 1][j];
```

#### 上左下右和上右下左

此时只有 $i-1$ 的 $1$ 位随便，其他没有，对应状态 $11$。

另一种类似。

```cpp
			f[i][11] = f[i - 1][0] | f[i - 1][2];
			f[i][7] = f[i - 1][0] | f[i - 1][1];
```

初始条件，因为不能让 $1$ 列往 $0$ 指，只有 `f[0][3] = true`。

最后只要 `f[n][0]` 到 `f[n][3]` 有一个行就行。

垃圾做法常数被吊打。感谢能看到这里。完整代码略去了。

---

