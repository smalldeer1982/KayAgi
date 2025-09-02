# [CEOI 2002] A decorative fence

## 题目描述

理查德刚刚盖完他的新房子。现在房子唯一缺少的是一个可爱的小木栅栏。他不知道如何制作木栅栏，所以他决定订购一个。不知何故，他拿到了 $\texttt{ACME Fence Catalog 2002}$――可爱的小木栅栏的旗舰版资源（注：ACME 是一家什么都造的公司）。看完它的前言，他已经知道，什么使小木栅栏变得可爱。  
一个木栅栏由 $N$ 块木板组成，每块木板垂直排成一排。除此之外，当且仅当满足以下条件时，围栏看起来很可爱：  
- 木板有不同的长度，即 $1,2,\cdots,N$ 为木板长度单位。  
- 每块有两个相邻的木板，它要么比它的相邻的都大，要么比它相邻的都小。（即，这会使得围栏顶部交替上升和下降（高低起伏））。  

因此，我们可以将每个用 $N$ 块木板的可爱的栅栏唯一地描述为一个排列 $a_1,\cdots,a_N$（$\forall i$，$1 < i < N$）$(a_i - a_{i−1}) × (a_i - a_{i+1}) > 0$。反之亦然，每个这样的排列都描述了一个可爱的围栏。  
很明显，可能有许多不同的可爱木栅栏由 $N$ 块木板制成。ACME 的销售经理决定以下列方式排列可爱围栏并放入清单：栅栏 A（由排列 $a_1,\cdots,a_N$ 表示）在栅栏 B 之前（由 $b_1,\cdots,b_N$ 表示），当且仅当存在这样的 $i$，使得（$\forall j < i$）$a_j = b_j$ 和 （$a_i < b_i$）。（也就是说，比较两个围栏中哪个在清单中更早相当于取它们对应的排列，找出它们第一个不同的地方，并比较这个地方的值。）所有 $N$ 块木板的可爱围栏都被按照它们在清单中出现的顺序编号（从 $1$ 开始）。这个号码被称为他们的清单号。 
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/9kopwi5p.png)
仔细检查所有的可爱的小木栅栏后，理查德决定要它们中的一些。他记下木板的数量 $N$ 和清单号 $C$。后来，他遇到了他的朋友，他想向他们展示他围栏，但他失去了清单。他得到的唯一的事情是他的笔记。请帮助他查明，他的围栏将为何等样子。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq K \leq 100$，$1 \leq N \leq 20$。你可以认为，$20$ 块木板的可爱小木栅栏的总数适合转换为 $64$ 位有符号整数变量（C/C++ 中的 `long long`，FreePascal 中的 `int64`）。你也可以认为输入是正确的，特别是 $C$ 最小是 $1$ 并且它不超过有 $N$ 块木板的可爱围栏的数量。  
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2002 的 [A decorative fence](https://web.ics.upjs.sk/ceoi/documents/tasks/fence-tsk.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
2
2 1
3 3```

### 输出

```
1 2
2 3 1```

# 题解

## 作者：ListenSnow (赞：9)

## 题意

有 $N$ 块长方形的木板，长度分别为 $1,2,…,N$，宽度都是 $1$。

现在要用这 $N$ 块木板组成一个宽度为 $N$ 的围栏，满足在围栏中，每块木板两侧的木板要么都比它高，要么都比它低。

也就是说，围栏中的木板是高低交错的。

我们称“两侧比它低的木板”处于高位，“两侧比它高的木板”处于低位。

显然，有很多种构建围栏的方案。

每个方案可以写作一个长度为 $N$ 的序列，序列中的各元素是木板的长度。

把这些序列按照字典序排序，如下图所示，就是 $N=4$ 时，所有满足条件的围栏按照木板长度的字典序排序后的结果。

![](https://cdn.luogu.com.cn/upload/image_hosting/9kopwi5p.png)

现在给定整数 $C$，求排名为 $C$ 的围栏中，各木板的长度从左到右依次是多少。

#### 数据范围

$1 \leq N \leq 20$，$0 < C <2^{63}$。

### 思路

思路来源于蓝书。

本题要求字典序排名为 $C$ 的方案，而字典序的排序方式决定了本题可以采用**试填法**。具体地，第 $i$ 个木板长度**从小到大**枚举到 $j$ 时，第 $i$ 位，固定填 $j$， $i+1 \sim n$ 的所有填法数量大于等于要求的方案的排名 $m$ ，那么答案中的第 $i$ 位就必然是 $j$。考虑如何预处理出方案数。

定义 $f[n][j][k]$ 表示用 $n$ 块木板组成围栏，最左边的木板在这些木板中**排名**为 $j$ （题目中隐含了每种长度只能用 $1$ 次的条件），且最左边的木板状态为 $k$ （$k=0$ 表示低位，$k=1$ 表示高位）的所有方案数。可以得到状态转移方程：

$f[i][j][1]=\sum_{k=1}^{j-1} f[i-1][k][0]$。

$f[i][j][0]=\sum_{k=j}^{i-1} f[i-1][k][1]$。

注意到第二个转移方程的 $k \in[j,i-1]$，这是因为 $k$ 代表的是排名，而不是真实的长度，这里其实用到了离散的思想 (如对于 $f[3][1][1]$，$1,3,2$ 和 $4,7,5$ 在状态中都认为是 $1,3,2$，且只会被计算一次)。

接下来就考虑如何试填。由于题目中木板的长度是高低交替，于是可以先确定第一块木板的状态，再用一个数不断异或 $1$ 来表示当前木板需要的状态。后面就可以从小到大枚举，依次确定每一块木板的长度，总复杂度为 $O(N^2)$，预处理的复杂度为 $O(N^3)$。

一些实现细节见代码。

### code：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int N=30;
#define int long long
int f[N][N][2],n,m,T;
bool vis[N];
void init()
{
	f[1][1][1]=f[1][1][0]=1;
	for(int i=2;i<=20;i++)
	    for(int j=1;j<=i;j++)
        {
	        for(int k=1;k<j;k++) f[i][j][1]+=f[i-1][k][0];
	        for(int k=j;k<i;k++) f[i][j][0]+=f[i-1][k][1];
		}
}
signed main()
{
	init();scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		memset(vis,0,sizeof(vis));
		int last,k;
		for(int i=1;i<=n;i++)
		{
			if(f[n][i][1]>=m)//由于是按照字典序，所以优先考虑第二块木板最小的情况 
			{
				last=i,k=1;
				break;
			}
			else m-=f[n][i][1];//由于f[i][j][k] 表示的是方案数，而不是排名，所以需要减去字典序更小的方案数 
			if(f[n][i][0]>=m)
			{
				last=i,k=0;
				break;
			}
			else m-=f[n][i][0];
		}
		printf("%lld",last);vis[last]=true;
		for(int i=2;i<=n;i++)
		{
			k^=1;int rank=0;//rank 表示len在剩余没有选用的木板中排名rank,因为状态中需要用排名 
			for(int len=1;len<=n;len++)
			{
				if(vis[len]) continue;rank++;
				if(k==0&&len<last||k==1&&len>last)
                {
                	if(f[n-i+1][rank][k]>=m)
                	{
                		last=len;
                		break;
					}
					else m-=f[n-i+1][rank][k];
				}
			}
			vis[last]=true;//注意标记当前木板被使用过 
			printf(" %lld",last);
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：yaoxiangyuan (赞：6)

修改于$2022$ $2.28$,感觉之前写的很不好，于是修改一下。

[题目链接](https://www.luogu.com.cn/problem/P7690)

### 1.题意
有 $N$ 块长方形的木板，长度分别为 $1, 2 ,…,N$，宽度都是 $1$ 。

现在要用这 $N$ 块木板组成一个宽度为 $N$ 的围栏，满足在围栏中，每块木板两侧的木板要么都比它高，要么都比它低。

也就是说，围栏中的木板是高低交错的。

我们称“两侧比它低的木板”处于高位，“两侧比它高的木板”处于低位。

显然，有很多种构建围栏的方案。

每个方案可以写作一个长度为 $N$ 的序列，序列中的各元素是木板的长度。

把这些序列按照字典序排序,给定整数 $C$ ,求排名为 $C$ 的围栏中，各木板的长度从左到右依次是多少。

### 2.知识点前置

计数 dp ,还有类似于康托展开的思想。

①动态规划不仅对于求解最优解问题有效，还可以用来求解各种排列组合的个数、概率或者期望之类的计算。而计数 dp 便有这个功能。

②一般的康托展开可以用来求一个 $1$ 到 $n$ 的任意排列的排名。

### 3.解题思路

只考虑最左边的一位  $x$  应该是多少?

如果第一位  $x=h$ , 后面的  $N-1$  个空构成的方案数为  $T_{1}    \geq C$  ，那么第一位就应该是 $ h $。

否则, 第一位  $x=x+1$,$ C=C-T_{1}$ , 再次重复考虑

复杂一点的话, 有一道例题需要与处理, 问题是一个位还分为 高位, 低位, 高位和低位要进行状态编码, $0$ 表示低位, $1$ 表示高位

 $f(i, j, 0)$  表示一共有  $i$  块木板, 第一位填的是  $j$ , 这一位处于低位  $j$  等价于最左边的木板的排名是  $j $。

$f(i, j, 0)=\sum_{p=j}^{i-1} f(i-1, p, 1) $

$f(i, j, 1)=\sum_{p=1}^{j-1} f(i-1, p, 0)$

### 4.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
long long m,f[25][25][5];
bool pd[25];
void csh(){
	f[1][1][0]=f[1][1][1]=1;
	for(int i=2;i<=20;i++){
		for(int j=1;j<=i;j++){
			for(int k=j;k<=i-1;k++){
				f[i][j][0]+=f[i-1][k][1];
			}
			for(int k=1;k<=j-1;k++){
				f[i][j][1]+=f[i-1][k][0];
			}
		}
	}
}
int main(){
	csh();
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld",&n,&m);
		memset(pd,0,sizeof(pd));
		int las,kk;
		for(int j=1;j<=n;j++){
			if(f[n][j][1]>=m){
				las=j;
				kk=1;
				break;
			}else{
				m-=f[n][j][1];
			}
			if(f[n][j][0]>=m){
				las=j;
				kk=0;
				break;
			}else{
				m-=f[n][j][0];
			}
		}
		printf("%d",las);
		pd[las]=1;
		for(int j=2;j<=n;j++){
			kk^=1;
			int pm=0;
			for(int l=1;l<=n;l++){
				if(pd[l]){
					continue;
				}
				pm++;
				if(kk==0&&l<las||kk==1&&l>las){
                	if(f[n-j+1][pm][kk]>=m){
                		las=l;
                		break;
					}else{
						m-=f[n-j+1][pm][kk];
					}
				}
			}
			pd[las]=1;
			printf(" %d",las);
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：hh弟中弟 (赞：4)

### [cnblogs](https://www.cnblogs.com/Ishar-zdl/p/18240544)
如果只是询问方案数，是 [P2467 [SDOI2010] 地精部落](https://www.luogu.com.cn/problem/P2467) 这道题，设 $f_{i,j,1/0}$ 表示以 $j$ 个数中从小到大的第 $i$ 个数处于**高/低**位开头的方案数。\
显然有

$$\begin{aligned}
    \begin{cases}
    f_{i,j,1}=\sum_{k=1}^{i-1}f_{k,j-1,0}\\
    f_{i,j,0}=\sum_{k=i}^{j-1}f_{k,j-1,1}
    \end{cases}
\end{aligned}$$

朴素的转移是 $O(n^3)$ 的，拿前缀和优化一下可以做到 $O(n^2)$。\
处理出来这个后，我们利用倍增的思想查找每一位应该停留在哪个数字上，如果加上这个数字的方案数后，当前总方案数大于等于 $C$，则这一位应该填这个数字。\
具体来说，可以通过记录这一位处于高位还是低位，然后找出每一位后递归下一位来实现。具体看代码。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=25;
int n,f[N][N][N],C,ans[N];
inline void work(int x,int now,int sum,int pd){
	ans[n-sum]=x;
	if(!sum)return;
	if(pd==-1||pd==1){
		for(int i=1;i<x;++i){
			if(now+f[i][sum][0]>=C){
				work(i,now,sum-1,0);
				return;
			}
			now+=f[i][sum][0];
		}
	}
	if(pd==-1||pd==0){
		for(int i=x;i<=sum;++i){
			if(now+f[i][sum][1]>=C){
				work(i,now,sum-1,1);
				return;
			}
			now+=f[i][sum][1];
		}
	}
    \\ 递归查找，pd=1表示当前处于高位找低位，pd=0反之，pd=-1表示当前是开头，找高低位无所谓。
}
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	f[1][1][0]=1;f[1][1][1]=1;
	for(int j=2;j<=20;++j){
		for(int i=1;i<=j;++i){
			for(int k=1;k<i;++k){
				f[i][j][1]+=f[k][j-1][0];
			}
			for(int k=i;k<=j-1;++k){
				f[i][j][0]+=f[k][j-1][1];
			}
		}
	}
	int T=read();
	while(T--){
		memset(ans,0,sizeof(ans));
		n=read(),C=read();
		int st=0,zc=0;
		for(int i=1;i<=n;++i){
			zc+=f[i][n][0]+f[i][n][1];
			if(zc>=C){st=i;zc-=f[i][n][0]+f[i][n][1];break;}
		}
		work(st,zc,n-1,-1);
		std::vector<int> v;
		for(int i=1;i<=n;++i)v.push_back(i);
		v.erase(v.begin()+st-1);
		for(int i=2;i<=n;++i){
			int zc=ans[i];
			ans[i]=v[ans[i]-1];
			v.erase(v.begin()+zc-1);
		}
		for(int i=1;i<=n;++i)std::cout<<ans[i]<<' ';std::cout<<'\n';
	}
}
```

---

## 作者：Adolfo_North (赞：2)

结合蓝书进行的精简与补充说明。

计数类型的动态规划。

定义 $f_{i,j,op}$ 为：

- $i$：已经放置的木板数。
- $j$：当前排列的最后一个木板的高度在剩余可选木板中的高度排名（即第 $j$ 小的木板）。
- $op$：当前的位置状况，$op=1$ 表示当前在高位，$op=0$ 当前在低位。

显然我们有如下转移：

::::info[$op=1$]{open}
$f_{i,j,1}=\sum_{p=1}^{j-1}f_{i-1,p,0}$

:::info[解释]
我选择的下一个应该比当前木板低，所以在 $[1,j-1]$ 中找。
:::
::::
::::info[$op=0$]{open}
$f_{i,j,0}=\sum_{p=j}^{i-1}f_{i-1,p,0}$

:::info[解释]
我选择的下一个应该比当前木板高，所以在 $[j,i-1]$ 中找。
:::
::::

处理完 $f$ 数组后，我们采用试填法确定每一位，设当前正在考虑第 $i$ 块木板，其长度为 $len$，该长度在剩余木板中的排名为 $j$，此时需要根据当前 $op$ 的状态，调整 $len$ 与 $lastlen$ 之间的关系。若 $f_{n-i+1,j,op}<c$ 则令 $c$ 减去 $f_{n-i+1,j,op}$ 并且尝试更大的 $j$。否则当前的长度就是 $len$。

需要特殊注意的是，第一块木板可以是低位也可以是高位，需单独处理。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=27;
int f[N][N][2],fl[N];
int n,c;
void init(){
	f[1][1][1]=f[1][1][0]=1;
	for(int i=2;i<=20;i++){
		for(int j=1;j<=i;j++){
			for(int k=1;k<j;k++) f[i][j][1]+=f[i-1][k][0];
			for(int k=j;k<i;k++) f[i][j][0]+=f[i-1][k][1];
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	init();
	int T;
	cin>>T;
	while(T--){
		memset(fl,0,sizeof fl);
		cin>>n>>c;
		int lst,op;
		for(int i=1;i<=n;i++){
			if(f[n][i][1]>=c) {
				lst=i,op=1;
				break;
			}
			else c-=f[n][i][1];
			if(f[n][i][0]>=c) {
				lst=i,op=0;
				break;
			}
			else c-=f[n][i][0];
		}
		fl[lst]=1;
		cout<<lst<<' ';
		for(int i=2;i<=n;i++){
			op^=1;
			int j=0;
			for(int len=1;len<=n;len++){
				if(fl[len]) continue;
				j++;
				if((op==0&&len<lst)||(op==1&&len>lst)){
					if(f[n-i+1][j][op]>=c){
						lst=len;
						break;
					}
					else c-=f[n-i+1][j][op];
				}
			}
			fl[lst]=1;
			cout<<lst<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Jasonshan10 (赞：2)

## 题意

给定 $n,c$，表示有长度为 $1\sim n$ 的 $n$ 块木板。

你需要满足围栏中的木板是**高低交错**排列的，问字典序第 $c$ 小的排列中，从左到右各木板的长度。

## 思路

首先，我们需要考虑如何求出所有可能的方案数，于是 DP。

我们定义 $dp
_{n,i,op}$ 表示现有 $n$ 块木板，最后一块木板排名为 $i$，最后一块木板的状态是 $op$ 的方案数。

  - 如果 $op=0$，表示最后一块木板比倒数第二块木板低。
  - 如果 $op=1$，表示最后一块木板比倒数第二块木板高。

然后，我们就可以预处理出 $n\le 20$ 的所有情况的方案数。

状态转移方程就是：

  - $dp_{i,j,0}= {\textstyle \sum_{p=j}^{i-1}} dp_{i-1,j,1}$
  
  - $dp_{i,j,1}= {\textstyle \sum_{p=1}^{j-1}} dp_{i-1,j,0}$

注意：这里的 $p$ 指的是**排名**，并不是长度。

接下来处理字典序第 $c$ 小我们可以考虑**试填法**，先确定第 $1$ 块木板的状态，再确定第 $2$ 块木板的状态，以此类推。

预处理时间复杂度为 $O(n^3)$，试填法时间复杂度为 $O(n^2)$。总时间复杂度为 $O(n^3+kn^2)$，可以通过此题。

~~所以这道题开 1MB 的目的何在？~~

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=22;
int vis[MAXN];
ll dp[MAXN][MAXN][2];
int main(){
	dp[1][1][1]=dp[1][1][0]=1;
	for(int i=2;i<=20;++i){
		for(int j=1;j<=i;++j){
			for(int k=1;k<j;++k) dp[i][j][1]+=dp[i-1][k][0];
			for(int k=j;k<i;++k) dp[i][j][0]+=dp[i-1][k][1]; 
		}
	}
	int T;
	scanf("%d",&T);
	while (T--){
		ll n,m,ans,k;
		scanf("%lld %lld",&n,&m);
		for(int i=1;i<=n;++i) vis[i]=0;
		for(int i=1;i<=n;++i){
			if (m<=dp[n][i][1]){ans=i;k=1;break;}
			else m=m-dp[n][i][1];
			if (m<=dp[n][i][0]){ans=i;k=0;break;}
			else m-=dp[n][i][0];
		}
		printf("%lld ",ans);
		vis[ans]=1;
		for(int i=2;i<=n;++i){
			ll temp=0; k^=1;
			for(int j=1;j<=n;++j){
				if (!vis[j]){
					++temp;
					if (k==0&&j<ans||k==1&&j>ans){
						if (m<=dp[n-i+1][temp][k]){ans=j; break;}
						else m-=dp[n-i+1][temp][k];
					}
				}
			}
			printf("%lld ",ans);
			vis[ans]=1;
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：hutongzhou (赞：1)

## 题意
把高度为 $1$ 到 $N$ 的木板拼起来，并且每块的两个相邻的木板，它要么比它的相邻的都大，要么比它相邻的都小。
这可以有多种排列方式。我们按字典序排序，问第 $C$ 小的排序方式是什么？  
数据范围  $1\leq N \leq 20$，$1\leq C \leq 2^{63}-1$。
## 思路
我们可以一位一位的填木板，就像“试填法”。但是看 $C$ 的范围是大于 `int` 范围一个一个求太慢了，所以想到倍增

用倍增预处理出第一个木板$1$到$N$的所有情况，因为还要区分这个数的前后两位是比它高还是低所以还要存这个木板是处于高位还是低位，用$1,0$表示。  

所以很容易想出状态 $f[ i ][ j ][ k ]$ ，表示用 $i$ 块木板拼成栅栏其中最左边的长度从小到大在第 $j$ 位，并且状态为 $k$ ($k$ 指是处于高位还是低位)。  

这里特别强调 $j$ 是**从小到大的第 $k$ 位**而不是木板真实的长度。因为如果是真实的长度，每一个个状态是唯一的，就是和暴力枚举是一样的，不方便倍增计数。  

这里第 $j$ 大的有点像离散化思想，把真实的值用从大到小的编号相互映射，以达到减少枚举数量的目的。  
#### 状态转移方程  
$f [ i ][ j ][ 0 ] = \sum_{p=j}^{i-1} f [ i - 1 ][ p ][ 1 ]$ 。  
  
$f [ i ][ j ][ 1 ] = \sum_{p=1}^{j-1} f [ i - 1 ][ p ][ 0 ]$ 。  

第一个实在是当前为低位时，那它的前一个就是高位并比它高。  
第二个式子是当前为高位是，那它的前一个就是低位并比它低。  
当倍增处理后只需要从小到大依次减去个数，从而求出第 $C$ 小的排列（有一点像数位dp），当然每减去一次，$k$ 就要取反一次，因为每一块木板肯定是高低交错的。  
#### 时间复杂度 
预处理 $O(N^{3})$，求答案时 $O(N^{2})$ 。
## code
一些细节看代码注释。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
bool vis[30];
long long m,f[30][30][2];
void get_f()//预处理
{
	f[1][1][0]=f[1][1][1]=1;//初始化
	for(int i=2;i<=20;i++)
	for(int j=1;j<=i;j++)
	{
		for(int k=j;k<=i-1;k++)
		f[i][j][0]+=f[i-1][k][1];
		for(int k=1;k<=j-1;k++)
		f[i][j][1]+=f[i-1][k][0];
	}
}
int main()
{
	
	cin>>T;
	get_f();
	while(T--)
	{
		memset(vis,0,sizeof vis);//多组数据要清空
		cin>>n>>m;
		int las,k;//las指当前数字，k指状态（高位还是低位）  
        	//一位一位的找，先找第一位
		for(int j=1;j<=n;j++)
		{
			if(f[n][j][1]>=m)//为了使字典序更小必须k是1开头，就是后面一位是低位
			{
				las=j;
				k=1;
				break;
			}
			else m-=f[n][j][1];
			if(f[n][j][0]>=m)
			{
				las=j;
				k=0;
				break;
			}
			else m-=f[n][j][0];
		}
		vis[las]=1;//vis是来存是否出现过，因不能有重复
		cout<<las<<" ";
        	//找后面几位
		for(int i=2;i<=n;i++)
		{
			k^=1;//必须是一个高位一个低位
			int j=0;//j是枚举前i位，这个数的排位
			for(int l=1;l<=n;l++)//l是当前的真实长度
			{
				if(vis[l])continue;//找过了就不着了
				j++;
				if(k==0&&l<las||k==1&&l>las)//0,1分两种考虑
				{
					if(f[n-i+1][j][k]>=m)
					{
						las=l;
						break;
					}
					else m-=f[n-i+1][j][k];
				}
				
			}
			vis[las]=1;
			cout<<las<<" ";
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7690)

# 前置知识

[计数 DP](https://oi-wiki.org/dp/count/)

# 解法

方案数统计同 [luogu P2467 [SDOI2010] 地精部落](https://www.luogu.com.cn/problem/P2467)，但部分写得不太好看的状态转移方程在本题中并不适用，但仍可借鉴其“离散化”思想。

考虑试填。

设 $f_{i,j,0/1}$ 表示用 $i$ 块不同的木板构成栅栏，其中最左边的木板的长度从小到大排在第 $j$ 位（仅是相对大小关系），处于低位/高位的方案数，状态转移方程为 $\begin{cases} f_{i,j,0}=\sum\limits_{k=j}^{i-1}f_{i-1,k,1} \\ f_{i,j,1}=\sum\limits_{k=1}^{j-1}f_{i-1,k,0} \end {cases}$，边界为 $f_{1,1,0/1}=1$。

特别处理第 $1$ 块木板的长度和低/高位情况 $k$。接着枚举每位的实际长度 $j$ 和排名 $rk$ 使其符合排名即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll f[25][25][2],vis[25];
int main()
{
	ll t,n,c,ans,rk,i,j,k,h;
	cin>>t;
	f[1][1][0]=f[1][1][1]=1;
	for(i=2;i<=20;i++)
	{
		for(j=1;j<=i;j++)
		{
			for(k=j;k<=i-1;k++)
			{
				f[i][j][0]+=f[i-1][k][1];
			}
			for(k=1;k<=j-1;k++)
			{
				f[i][j][1]+=f[i-1][k][0];
			}
		}
	}
	for(h=1;h<=t;h++)
	{
		cin>>n>>c;
		k=ans=-1;
		memset(vis,0,sizeof(vis));
		for(i=1;i<=n;i++)
		{
			if(f[n][i][1]>=c)
			{
				ans=i;
				k=1;
				break;
			}
			else
			{
				c-=f[n][i][1]; 
			}
			if(f[n][i][0]>=c)
			{
				ans=i;
				k=0;
				break;
			}
			else
			{
				c-=f[n][i][0];
			}
		}
		vis[ans]=1;
		cout<<ans<<" ";
		for(i=2;i<=n;i++)
		{
			k^=1;
			rk=0;
			for(j=1;j<=n;j++)
			{
				if(vis[j]==0)
				{
					rk++;
					if((k==0&&j<ans)||(k==1&&j>ans))
					{
						if(f[n-i+1][rk][k]>=c)
						{
							ans=j;
							break;
						}
						else
						{
							c-=f[n-i+1][rk][k];
						}
					}
				}
			}
			vis[ans]=1;
			cout<<ans<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：云雷心柠檬听 (赞：0)

### 题意简述
有 $1$ 到 $N$ 共 $N$ 个数，将他们排列为大小交错的数，即满足任意相邻三个数 $a_1 < a_2$ 且 $a_2 > a_3$ 或 $a_1 > a_2$ 且 $a_2 < a_3$
求按字典序排序后排名为 $C$ 的排列。

### 分析
这道题的思路类似于倍增优化 $DP$ 中的“拼凑”思想，可以用“试填法”确定排名为 $C$ 的栅栏中各木板的长度，最终确定使用动态规划的思路。

### 实现
我们定义状态，设 $\mathit{f}_{i,j,k}$ 表示用第 $i$ 块长度不同的木板构成栅栏，其中最左边的木板长度从小到大排在第 $j$ 位，并且位置状况为 $k$ ，即当 $k=0$ 时表示处在低位， $k=1$ 时表示处在高位。

状态转移方程为
$$\mathit{f}_{i,j,0}=\sum\limits_{p=j}^{i-1}\mathit{f}_{i-1,p,1}$$

$$\mathit{f}_{i,j,1}=\sum\limits_{p=1}^{j-1}\mathit{f}_{i-1,p,0}$$

假设我们已经确定了从左至右 $i-1$ 块木板的长度，我们要考虑第 $i$ 块木板。记录了上一块木板的长度 $last$ 和上一块木板的高低位置状况 $k$ （意义与上文相同），我们可以枚举还未使用的木板，寻找排名为 $C$ 的木板的长度。

特别地，而第 $1$ 块木板相较于第 $0$ 块木板（即不存在的数）的高度情况是未知的，需要分类讨论，所以单独处理。

### 复杂度分析
动态规划的时间复杂度： $O(n^3)$ ，试填法的过程时间复杂度为 $O(n^2)$ ，可以通过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=29;
int t,n;
ll m,f[N][N][2];

void input(){//动态规划（预处理）
	f[1][1][0]=f[1][1][1]=1;
	for(int i=2;i<=20;i++){
		for(int j=1;j<=i;j++){
			for(int p=j;p<=i-1;p++){
				f[i][j][0]+=f[i-1][p][1];
			}
			for(int p=1;p<=j-1;p++){
				f[i][j][1]+=f[i-1][p][0];
			}
		}
	}
	cin>>t;
}

void solve(){
	cin>>n>>m;
	bool used[N];
	memset(used,0,sizeof(used));
	int lst,k;
	for(int j=1;j<=n;j++){//第一块木板特别处理
		if(f[n][j][1]>=m){
			lst=j,k=1;
			break;
		}
		else m-=f[n][j][1];
		if(f[n][j][0]>=m){
			lst=j,k=0;
			break;
		}
		else m-=f[n][j][0];
	}
	used[lst]=1;
	cout<<lst;
	for(int i=2;i<=n;i++){//其他木板
		k^=1;
		int j=0;
		for(int len=1;len<=n;len++){
			if(used[len]) continue;
			j++;
			if(k==0&&len<lst||k==1&&len>lst){
				if(f[n-i+1][j][k]>=m){
					lst=len;
					break;
				}
				else{
					m-=f[n-i+1][j][k];
				}
			}
		}
		used[lst]=1;
		cout<<" "<<lst;
	}
	cout<<endl;
}

int main(){
	input();
	while(t--){
		solve();
	}
	return 0;
}

```

### 其他
题解中部分内容参考 《算法竞赛进阶指南》。

---

