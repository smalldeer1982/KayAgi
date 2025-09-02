# Chess Tournament

## 题目描述

### 题意翻译

$n$ 个人进行比赛，每场比赛的结果只有输，赢，平局三种情况。

每个玩家对于比赛都有自己的期望，有以下两种类型：

1. 玩家不想输掉任何一场比赛；

2. 玩家想要赢得至少一场比赛。

判断是否存在所有比赛的结果，使得所有玩家都满足他们的期望。 如果有多种可能的结果，输出任意一种即可。 如果没有，输出 No。

## 说明/提示

$1\le t \le 200,2\le n \le50$。

译者：@smyslenny

## 样例 #1

### 输入

```
3
3
111
2
21
4
2122```

### 输出

```
YES
X==
=X=
==X
NO
YES
X--+
+X++
+-X-
--+X```

# 题解

## 作者：Jerrlee✅ (赞：7)

## 题意
参加比赛的 $n$ 个棋手都有自己的愿望，它们可以是以下两种愿望之一：

1. 玩家不想输掉任何一场比赛（以零个败场完赛），

2. 玩家想要赢得至少一场比赛（以至少一个胜场完赛）。

不能满足打印 `NO` ，否则打印 `YES` 和 $n \times n$（$n$ 行 $n$ 列） 个字符：

- 赢了是 `+`;

- 输了是 `-`;

- 平局是 `=`;

- 如果打印的 $i$ 行 $j$ 列中，$i=j$ 了，打印 `X`。

## 思路
由于第一类棋手一局都不想输，所以第一类棋手之间的每场比赛都应该以平局结束（这样他们都不会被打败）。第一类棋手和第二类棋手之间的比赛应该以第一类获胜或平局结束。为了方便，直接让所有有第一类棋手的游戏都以平局结束。

第二类棋手之间的比赛中，如果只有 $1$ 或 $2$ 个这样的棋手，那就没有答案了。否则，我们让第二类的 $i$ -th 棋手赢 $i+1$ -th 的棋手，最后一个战胜第一个就行了（每个第二类棋手各一个胜场）。

## 注意
这双是一个多解的题目，样例对的，但不代表只能是样例！

---

## 作者：smyslenny (赞：3)

# CF1569B
## Description

$n$ 个人进行比赛，每场比赛的结果只有输，赢，平局三种情况。

每个玩家对于比赛都有自己的期望，有以下两种类型：

1. 玩家不想输掉任何一场比赛；

2. 玩家想要赢得至少一场比赛。

判断是否存在所有比赛的结果，使得所有玩家都满足他们的期望。 如果有多种可能的结果，输出任意一种即可。 如果没有，输出 No。

## Solution

以下均用 $1$ 表示当前这个人想要 $1$ 的结果，$2$ 同上。 

我们发现，如果只有一个 $2$，那么其他的都是 $1$，$2$ 想要至少应一场，而 $1$ 不想输，那这就矛盾了，因此这种情况不行。

如果只有两个 $2$ ，$2$ 是不能赢 $1$ 的，如果一个 $2$ 赢了另一个 $2$，那么另一个 $2$ 就输了，输了的那个 $2$ 也就不能满足了，而且它也不能赢 $1$，因此这种情况也不行。

当 $2$ 大于两个的时候，他们的输赢情况可以构成一个环，互相满足。

![](https://cdn.luogu.com.cn/upload/image_hosting/tnvc9htn.png)

就像上图，这样就满足了每个人至少赢一场，而对于 $1$ 来说，保证他不输，那我们直接让与他对战的人打平手就好了。

**注意**:答案中 $i,j$ 和 $j,i$ 的情况是对应的，如果 $i,j$ 是 `+` ，那么 $j,i$ 就是 `-` ，打这场比赛的时候没注意导致交了好几发。

##  Code

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>

using namespace std;
const int M=1e3+5;
int T,n;
int read()
{
	int x=0,y=1;
	char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') y=0;c=getchar();}
	while(c>='0' && c<='9') { x=x*10+(c^48);c=getchar();}
	return y?x:-x;
}
char s[M],Ans[M][M];
int sz[M];
int js_a,js_b;
int main()
{
	T=read();
	while(T--)
	{
		js_a=js_b=0;
		memset(sz,0,sizeof(sz));
		n=read();
		scanf("%s",s+1);
		for(int i=1;i<=n;i++) sz[i]=s[i]-'0',js_a+=sz[i]==2,js_b+=sz[i]==1;
		if(js_a==1 || js_a==2)// 2 的个数为 1 2 时，没有答案
		{
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		for(int i=1;i<=n;i++)
		{
			for(int j=i;j<=n;j++)
			{
				if(i==j) Ans[i][j]='X';
				else
					if(sz[i]==1 || sz[j]==1) Ans[i][j]=Ans[j][i]='=';//有 1 时候，直接平局就行
				else//这里我们只要认为让所有的 2 只赢一场
					if(sz[i]==2)
					{
						sz[i]=0;
						Ans[i][j]='+';
						Ans[j][i]='-';
					}
				else
					if(sz[j]==2) 
					{
						sz[j]=0;
						Ans[i][j]='-';
						Ans[j][i]='+';
					}
				else
					Ans[i][j]=Ans[j][i]='=';
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				cout<<Ans[i][j];
			printf("\n");
		}
	}
	return 0;
}
```



---

## 作者：lianchanghua (赞：2)

感谢 @[I_like_magic](https://www.luogu.com.cn/user/778235) 帮忙修改 Markdown 和 $\LaTeX$。


#### 题目大意

有 $n$ 个人进行比赛，每场比赛的结果只有输，赢，平局三种情况。

每个玩家对于比赛都有自己的期望，有以下两种类型：

1. 玩家不想输掉任何一场比赛；

2. 玩家想要赢得至少一场比赛。

判断是否存在所有比赛的结果，使得所有玩家都满足他们的期望。如果有多种可能的结果，输出 `Yes` 并输出任意一种即可。如果没有，输出 `No`。

#### 思路

我们分两种情况讨论：

- 当玩家需求为第一种时，我们可以将他们都设置为平局。

- 当玩家需求为第二种时，我们就可以让他们进行内部循坏，如：$x_1$ 赢 $x_2$，$x_2$赢 $x_3$，$x_3$ 赢 $x_1$。

当然，如果第二种玩家的个数 $0 < x < 3$ 时，就无法满足他们全部人，所以，此时就要输出 `No`。

#### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n;
		char c[105],ans[105][105];
		int f=0;
		cin>>n>>(c+1);
		for(int i=1;i<=n;i++)	if(c[i]=='2')	f++;
		if(f<=2&&f!=0){
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				if(i==j)			ans[i][j]='X';
				else if(c[i]=='1'||c[j]=='1'){
					ans[i][j]='=';
					ans[j][i]='=';
				}
				else if(c[i]=='2'){
					ans[i][j]='+';
					ans[j][i]='-';
					c[i]=0;
				}
				else if(c[j]=='2'){
					ans[i][j]='-';
					ans[j][i]='+';
					c[j]=0;
				}	
				else{
					ans[i][j]='=';
					ans[j][i]='=';
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cout<<ans[i][j];
			}
			cout<<"\n";
		}
	}
	return 0;
}

```

---

## 作者：xixike (赞：2)

**一道比较简单的构造题**。

# Solution

我们对于两种类型分别考虑：

- 类型 1：**一场都不能输**，我们把这样的选手的每场比赛都设定为为**平局**。

证明：首先我们发现胜利还是失败是不影响类型 1 的选手的，而如果把这样的选手的某一场比赛设定为**胜利**，那么对手就为败。不难发现，不论对手为类型 1 还是类型 2，失败一场都不如平局更优。

- 类型 2：**至少胜利一场**，我们直接令这样的选手胜负情况构成一个环。

即，假设 $x_1$，$x_2$，$x_3$ 三人均为类型 2，我们直接令 $x_1$ 胜 $x_2$，$x_2$ 胜 $x_3$，$x_3$ 胜 $x_1$（我的代码里是反过来的）。

容易发现，当**只有 1 人或 2 人**为类型 2 时，无解（无法构成环）。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int T, n, cnt, pos;//cnt: 类型 2 选手个数
char s[60], ans[60][60];
int pre[60];//记录前一个类型 2 的选手的编号

inline void init(){//初始化
	for(int i = 1; i <= 50; i++){
		pre[i] = 0;
		for(int j = 1; j <= 50; j++)
			ans[i][j] = '0';
	}
	cnt = pos = 0;
}

int main(){
	scanf("%d", &T);
	while(T--){
		init();
		scanf("%d%s", &n, s + 1);
		for(int i = 1; i <= n; i++){
			ans[i][i] = 'X';//自己和自己
			if(s[i] == '2')
				cnt++, pre[i] = pos, pos = i;
		}
		if(cnt == 1 || cnt == 2){
			puts("NO");
			continue;
		}
		int p;
		for(p = pos; pre[p]; p = pre[p])
			ans[p][pre[p]] = '+', ans[pre[p]][p] = '-';
		ans[p][pos] = '+', ans[pos][p] = '-';
		puts("YES");
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				putchar(ans[i][j] == '0' ? '=' : ans[i][j]);
			}
			puts("");
		}
	}
	return 0;
}
```

# End

---

## 作者：_Han (赞：2)

# CF1569B
## 题意
$t$ 组数据，$n$ 名选手进行比赛，比赛仅有输，赢，平三种结果。 

每名选手都有自己的要求：  

输入 $1$ 代表该选手不想输掉**任何一场**比赛。  
输入 $2$ 代表该选手**至少**想赢得一场比赛。  

判断是否有满足条件的对局，如有输出 YES ，并输出相应的对局情况；若不存在符合条件的对局，则仅输出一行 NO 。

## **Sol**

( 为方便起见，下文称要求 $1$ 的选手为 $1$ ，要求 $2$ 的选手为 $2$ 。  

考虑对 $2$ 进行讨论，不难发现，当 $2$ 的个数为 $0$ 时，只要使得每个 $1$ 的对局都打平就能符合条件。  

当 $2$ 的个数为 $1$ 时，$1$ 与 $1$ 一定会出现对局的情况，若 $2$ 获胜，就不能满足 $1$ 不想输的情况，则此时输出为 NO 。  

当 $2$ 的个数为 $2$ 时，$2$ 不能胜 $1$ ，同时 $2$ 也不能胜 $2$ ，那么该情况也为 NO 。

当 $2$ 的个数为 $3$ 时，不难发现 $3$ 个 $2$ 可以构成一个环。这时，只要使所有的 $1$ 打平，就能构造出符合要求的对局情况。  

当 $2$ 的个数大于 $3$ 时，~~手玩不难发现~~所有的 $2$ 一定能构成一个环，这时也只要使得所有的 $1$ 均打平就行了。  

## Code
```cpp
// f数组记录最终的对局结果
// +为胜，-为败，=为平
	cin>>t;
	while (t--)
	{
		cin>>n;
		cin>>st;
		int tot2=0;
		memset(a,0,sizeof(a));
		for (int i=0;i<n;i++)
		  if (st[i]=='1') a[i+1]=1;
			else a[i+1]=2,tot2++;
		if (tot2==1||tot2==2) 
		{
			puts("NO");
			continue;
		} //当2的个数为1或2是无法构造出满足条件的对局
		puts("YES");
		for (int i=1;i<=n;i++)
		  for (int j=i;j<=n;j++)
		  {
		    if (i==j) f[i][j]='X';
		      else if (a[i]==1||a[j]==1) f[i][j]=f[j][i]='=';
		      	else if (a[i]==2) a[i]=0,f[i][j]='+',f[j][i]='-';
		      	  else if (a[j]==2) a[j]=0,f[j][i]='+',f[i][j]='-';
		      	    else f[i][j]=f[j][i]='=';
		  }
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++) cout<<f[i][j];
			cout<<endl; 
		}
	}
```


---

## 作者：haozinojc (赞：1)

这道题是一道很简单的**模拟**题。

### 思路：

这道题中有两种人，第一种是**一直不输**的人，第二种是**至少赢一局**的人。

- 对于第一类人，我们只需要让他们每一局都不是输即可，方便起见，让他们的每一局都平局就可以了。

- 对于第二类人，此处需要一个特判，当存在第二类人且数量少于三个时，此时无解。因为第二类人只能打赢第二类人，他们**不能去打赢第一类人**（题目说的），所以当第二类人数大于零且小于三时，会有一个人无法获胜一局。而当第二类人大于等于三个时，就能构成一个环，这样才能保证每个人都能获胜至少一次。

那么分析完这两种人后，就很容易做了。让第一类人参与的全部为平局，第二类人组成一个环，前面的人能够打赢后面的人。特别的，最后一个打赢最前面的人。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
char ans[100][100],s[100];
signed main(){
	cin>>t;
	while(t--){
		int flag=0;
		cin>>n>>s;
		for(int i=0;i<n;i++)if(s[i]=='2')flag++;
		if(flag<=2&&flag!=0){puts("NO");continue;}
		puts("YES");
		for(int i=0;i<n;i++){
			for(int j=i;j<n;j++){
				if(i==j)ans[i][j]='X';
				else if(s[i]=='1'||s[j]=='1'){ans[i][j]='=';ans[j][i]='=';}
				//第一类人参加 
				else if(s[i]=='2'){ans[i][j]='+';ans[j][i]='-';s[i]=0;}
				//前面打后面 
				else if(s[j]=='2'){ans[i][j]='-';ans[j][i]='+';s[j]=0;}
				//后面打前面 
				else {ans[i][j]='=';ans[j][i]='=';}
				//其他的 
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)cout<<ans[i][j];
			cout<<"\n";
		}
	}
	return 0;
}
```


---

## 作者：smallpeter (赞：0)

# CF1569B Chess Tournamentt题解

## 题目大意

$n$ 个人进行比赛，每场比赛的结果只有输，赢，平局三种情况。

每个玩家对于比赛都有自己的期望，有以下两种类型：

1. 玩家不想输掉任何一场比赛。

2. 玩家想要赢得至少一场比赛。

判断是否存在所有比赛的结果，使得所有玩家都满足他们的期望。如果有多种可能的结果，输出任意一种即可。如果没有，输出 $\texttt{N0}$。


$2\le n \le50$

## 解题思路

第一类选手之间的比赛最好情况为平局。因为对于第一类选手来说，赢跟平局没什么区别，但不能输。若第一类选手 $A$ 赢了另一位第一类选手 $B$ ，那 $B$ 选手的期望就无法满足了。$A$ 选手若与 $B$ 选手平局，则两人的期望在这局都能实现~~可以说是皆大欢喜~~。

第一类选手与第二类选手之间的比赛最好情况为平局或第一类选手赢了第二类选手。对于第一类选手 $A$ 来说，赢了第二类选手 $B$ 跟与 $B$ 平局没什么区别（这里同上）。对于第二类选手 $B$ 来说，赢了自然好，但输了也不会立刻出局。所以 $A$ 选手不能输给 $B$ 选手，赢了 $B$ 选手跟与 $B$ 选手平局没有区别。为了方便我们当其平局。

**所以我们可以把第一类选手的所有比赛状态全部设置为平局。**

剩下的比赛就是第二类选手之间的比赛了，假设有 $m$ 个第二类选手，不难证明当 $m\le2$ 的时候无解。当 $m>3$ 的时候我们可以通过构造一个环来实现这 $m$ 个第二类选手的期望。

**所以第二类选手的数量若小于等于 2，则无解。反之可构造环来实现。**


### 例子

$S=2122$

选手 1 赢了选手 3，与选手 2 平局，输给了选手 4。

选手 2 与选手 1、3、4 都平局。

选手 3 赢了选手 4，与选手 2 平局，输给了选手 1。

选手 4 赢了选手 1，与选手 2 平局，输给了选手 3。

这便是一种合法解。

---

## 作者：Nt_Tsumiki (赞：0)

## 题意

[题目传送门](https://www.luogu.com.cn/problem/CF1569B)

有 $n$ 个人比赛，每个人有一种要求，以字符串输入，为以下的 $1$ 或  $2$。

- $1$：不能输；

- $2$：至少赢一场。

规定获胜输出 ```+```，输了输出 ```-```，平局输出 ```=```，求是否有合法的方案满足每个人的要求，有输出 ```YES``` 和方案，没有输出 ```NO```。

## 做法

一道大模拟。

分别考虑一下 $1$ 和 $2$。

情况 $1$：不能输的情况有哪些呢，平局和获胜，由于有多种答案，我们统一规定，要求为 $1$ 的人始终平局。

情况 $2$：至少赢一场，我们可以在第一遍模拟到 $2$ 时让他赢，之后把它标记成 $0$（不再搜它了），即可。

另外我们可以发现，当 $2$ 的个数有一个或者两个时，没有合法的答案（解释在后面），所以，在那时直接输出 ```NO```。

解释：

- $2$ 有一个时，它想赢一局，但其他的 $1$ 不想输，矛盾。

- $2$ 有两个时，假设第一个 $2$ 赢了第二个 $2$，那么，由于两个人之间只能比一场，所以，第二个 $2$ 就没有 $2$ 再可以赢，状态始终为输，矛盾。

## Code

```cpp
#include <iostream>
#include <string>

using namespace std;
int t,n;
int a[51];
char ans[51][51];//答案

int main() {
   cin>>t;
   while (t--) {
      cin>>n;
      string s;
      cin>>s;
      int j=0,tp=0;
      for (auto i:s) {//转换成整形方便模拟
         a[++j]=i-'0';
         tp+=(a[j]==2);
      }
      if (tp==1 or tp==2) {//特判
         cout<<"NO"<<endl;
         continue;
      }
      cout<<"YES"<<endl;
      for (int i=1;i<=n;i++)
         for (int j=i;j<=n;j++) {
            if (i==j) ans[i][j]='X';
            else if (a[i]==1 or a[j]==1) ans[i][j]=ans[j][i]='=';//有 1 存在，就标为平局
            else if (a[i]==2) a[i]=0,ans[i][j]='+',ans[j][i]='-';
            else if (a[j]==2) a[j]=0,ans[j][i]='+',ans[i][j]='-';
            //一个点为 + 时，其对应点就应是 -，需要注意
            else ans[i][j]=ans[j][i]='=';//0 情况
         }
      for (int i=1;i<=n;i++) {//输出
         for (int j=1;j<=n;j++)
            cout<<ans[i][j];
         cout<<endl;
      }
   }
   return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

对于所有不想输的人，安排他们平局。

然后找出所有想赢的人。设有 $wi$ 个想赢的人，分别是 $w[1],w[2],w[3],......,w[wi]$。

如果 $wi=1\operatorname{or}wi=2$，则无解。

否则，设 $i\to j$ 表示 $i$ 赢下 $j$。我们可以这么安排：

$$\begin{matrix}w[1]\to w[2]\\w[2]\to w[3]\\w[3]\to w[4]\\......\\w[wi]\to w[1]\end{matrix}$$

然后对于依然没有确定的场次（如 $w[1]\longleftrightarrow w[3]$），全部平局。

感谢 @[dengzijun](/user/387836) 提供亿点点思路。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 50
int t;
int n;
char a[max_n+2];
int g[max_n+2][max_n+2];//1,2,3 从失败到胜利
int w[max_n+2];
int wi;
bool ok;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1569B_2.in","r",stdin);
	freopen("CF1569B_2.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%s",&n,a+1);
		memset(g,0,sizeof(g));
		memset(w,0,sizeof(w));
		wi=0;
		ok=true;
		for(int i=1;i<=n;++i){
			if(a[i]=='1'){
				for(int j=1;j<=n;++j){
					if(i!=j)g[i][j]=g[j][i]=2;
				}
			}
			else w[++wi]=i;
		}
		if(wi==1||wi==2){
			printf("NO\n");
			continue;
		}
		for(int x=1,i;x<wi;++x){
			g[w[x]][w[x+1]]=3;
			g[w[x+1]][w[x]]=1;
		}
		g[w[wi]][w[1]]=3;
		g[w[1]][w[wi]]=1;
		printf("YES\n");
		for(int i=1;i<=n;++i){
			for(int j=i+1;j<=n;++j){
				if(i!=j&&g[i][j]==0)g[i][j]=g[j][i]=2;
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(g[i][j]==0)putchar('X');
				if(g[i][j]==1)putchar('-');
				if(g[i][j]==2)putchar('=');
				if(g[i][j]==3)putchar('+');
			}
			printf("\n");
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/57865741)

By **dengziyue**

---

## 作者：Umbrella_Leaf (赞：0)

### 题目大意

> 有 $n$ 个人参加一场比赛，每两人之间都要比一局，结果有胜、负、平。这 $n$ 个人中，有两种人：
> 
> - 第一种人不希望输掉任何一场比赛。
> 
> - 第二种人希望至少赢一局。
> 
> 若有解，输出`YES`，并给出一种胜负方案，满足所有人的需求。若无解，输出`NO`。

### 做法

考虑将所有的第二种人找出来，塞进一个`vector`里。

由于他们都得赢至少一局，又不能赢第一种人，因此让他们像一个环一样赢下一个人。

对于第一种人，让他与其他所有人平局即可。

最后要注意的是，如果第二种人的个数是`1`或`2`，就是无解的。因为一个人不能赢自己，也不能两个人互相赢对方。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read(){
	int res=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){
		res=res*10+(c^48);
		c=getchar();
	}
	return res;
}
int n;
char a[105];
vector<int> v;
int ans[105][105];
int main(){
	int T=read();
	while(T--){
		v.clear();memset(ans,0,sizeof(ans));
		n=read();
		scanf("%s",a+1);
		for(int i=1;i<=n;i++)if(a[i]=='2')v.push_back(i);
		if(v.size()==1||v.size()==2){
			puts("NO");
			continue;
		}
		puts("YES");
		for(int i=0;i<v.size();i++)ans[v[i]][v[(i+1)%v.size()]]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i==j)putchar('X');
				else{
					if(ans[i][j]==1)putchar('+');
					else if(ans[j][i]==1)putchar('-');
					else putchar('=');
				}
			}
			puts("");
		}
	}
	return 0;
}
```

---

