# [NEERC 2013] Bonus Cards

## 题目描述

德米特里非常喜欢编程比赛。著名的冠军联赛决赛正在德米特里的家乡城市举行，所以他想去观看比赛。比赛非常受欢迎，但大多数门票都保留给 VIP 和赞助商。  

对于普通公众，冠军联赛决赛的门票以以下方式分发。希望观看比赛的观众提交他们的请求，说明他们希望用哪种支付方式来支付门票。假设有 $n$ 个可用座位。进行若干轮抽签。在每一轮中，每个尚未满足的请求根据支付方式获得一定数量的抽签机会。然后从这些机会中随机选择一个。该机会所属的请求被视为已满足，并不再参与后续的抽签轮次。抽签在 $n$ 轮后或没有未满足请求时结束，以先发生者为准。国际卡处理公司（ICPC）是冠军联赛的赞助商。选择 ICPC 卡作为支付方式的人在每轮抽签中获得两个机会，而使用其他支付方式的用户仅获得一个。  

德米特里有一张 ICPC 的卡，但他也有一张高级信用商品（ACM）的卡，该卡为他的所有消费提供奖金。他的兄弟 Petr 在负责分发门票的公司工作，所以他提前告诉德米特里已经有多少人决定使用 ICPC 卡以及多少人决定使用其他方法。现在德米特里想知道如果他使用 ICPC 卡或 ACM 卡，获得门票的概率是多少，以便做出明智的选择。他的请求将是 Petr 告诉他的请求数量的附加。  

你能帮忙吗？

## 说明/提示

时间限制：1 秒，内存限制：128 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1 1 2
```

### 输出

```
0.3333333333333333
0.2
```

## 样例 #2

### 输入

```
10 10 10
```

### 输出

```
0.5870875690480144
0.3640355515319861
```

# 题解

## 作者：fervency (赞：5)

这么好的题居然没有题解！qwq

先看 Dmitry 参与一类抽选并被选中的概率，答案是 $n$ 轮中每一轮被选中的概率之和。

设计状态 $\mathit{f}_{i,j}$，

肯定有一位是轮数，另外我们需要知道一类二类各有多少人以及被抽中的概率，
所以 $\mathit{f}_{i,j} \Rightarrow$ 已经进行 $i$ 轮，一类中有 $j$ 个人被选中。
   
考虑状态转移 $ \mathit{f}_{i,j}\Rightarrow\mathit{f}_{i+1,j},\mathit{f}_{i+1,j+1} $，
   
如果下一轮选中的是二类 $\mathit{f}_{i,j}$：

该状态发生的概率是 $\mathit{f}_{i,j}\times $ ( 二类剩余人数 )/( 总剩余人数 ) ；
       
如果下一轮选中的是一类 $\mathit{f}_{i+1,j+1}$：

该状态发生的概率是 $\mathit{f}_{i,j} \times$ ( 一类剩余人数 ) / ( 总剩余人数 ) ；
        
注意 ：一类被抽中的概率是二类的两倍，使一类权值为 $2$（ 或者假设有两倍的一类 ） 并且当 Dmitry 作为一类时，分母中加的数也是 $2$ 。
    
对于具体的统计答案，并不是简单的 $n$ 轮概率之和，而是：假设 Dmitry 是在第 $i$ 轮，作为第 $j$ 个人被抽中的，那么答案应该加上此时符合状态 **“经进行 $i$ 轮，一类中有 $j$ 个人被选中”** 的概率再除以此时剩余人数。
    
因为剩下这么多人，只有人数分之一的概率使得被抽中的是 Dmitry。

**Code：**
```cpp
//概率DP （看数据范围得知是n方） 
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3010;
double n,A,B,f[N][N][2],ans1,ans2;
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
//其实根本不用快读 
signed main()
{
	n=read(),A=read(),B=read();
//	Dmitry本身不算在 A B 里面 
	if(n>A+B){puts("1.0");puts("1.0");return 0;}
	f[0][0][0]=f[0][0][1]=1;
	for(int i=0;i<n;i++)
	for(int j=0;j<=i&&j<=A;j++)
	{
		if(f[i][j][0]==0) continue;
		if(A-j>0) f[i+1][j+1][0]+=f[i][j][0]*(2*(A-j)/(2*(A-j)+(B-i+j)+2));
		if(B-i+j>0) f[i+1][j][0]+=f[i][j][0]*((B-i+j)/(2*(A-j)+(B-i+j)+2));
	}
	for(int i=0;i<n;i++)
	for(int j=0;j<=i&&j<=A;j++) ans1+=2*f[i][j][0]/(2*(A-j)+(B-i+j)+2); 
	printf("%.16lf\n",ans1);
	
	for(int i=0;i<n;i++)
	for(int j=0;j<=i&&j<=A;j++)
	{
		if(f[i][j][1]==0) continue;
		if(A-j>0) f[i+1][j+1][1]+=f[i][j][1]*(2*(A-j)/(2*(A-j)+(B-i+j)+1));
		if(B-i+j>0) f[i+1][j][1]+=f[i][j][1]*((B-i+j)/(2*(A-j)+(B-i+j)+1));
	}
	for(int i=0;i<n;i++)
	for(int j=0;j<=i&&j<=A;j++) ans2+=f[i][j][1]/(2*(A-j)+(B-i+j)+1);
	printf("%.16lf\n",ans2);
	return 0;
}

```
**感谢管理员耐心指正（鞠躬orz）**

---

## 作者：Arson1st (赞：1)

## [P6997 [NEERC2013] Bonus Cards 题解](https://www.luogu.com.cn/problem/P6997)

### 题意

有两类名额，$n$ 轮抽奖。其中一类名额中奖概率为二类的两倍，现在给出两类名额数量分别为 $a$、$b$，分别求出：Dmitry 参与一类名额的获奖概率和参与二类名额的获奖概率。（$a,b$ 个人不包括 Dmitry）

### 算法：记搜+期望DP

题目是典型的期望 DP，但是本蒟蒻写这类动规时一般习惯写记搜（不想倒推转移，似乎记搜更符合直觉？毕竟是直接的正向逻辑），所以就有了这一篇记忆化搜索题解。

### 分析

#### 状态设计

套路地，设状态 $f(m,x,y)$ 表示已经抽过了 $m$ 次奖，已经抽中了 $x$ 个一类名额和 $y$ 个二类名额的情况下，Dmitry 中奖的概率。当然，直接这么开会爆空间（$n\le 3000$），但是不难发现 $x+y=m$，所以可以压掉一维，开到 $O(n^2)$。最后的答案为 $f[0][0]$。

#### 状态转移

先讨论 Dmitry 买了 **一类名额**，预先将 $a$ 加 $1$。考虑一轮抽奖，剩余 $a-x$ 个一类名额和 $b-y$ 个二类名额未中奖的情况，即搜索到了 $(m,x,y)$。（~~为什么要这么麻烦的表示剩余名额而不直接更改状态设计？因为 $a$、$b$ 都是 $10^9$ 级别，数组开不下，只能这样设计了~~）那么结果无非三种情况：

1. Dmitry 获奖。
2. 另一个一类名额的人获奖
3. 一个二类名额的人获奖

我们考虑这些情况对 Dmitry 最终中奖概率的贡献：首先，总的概率为 $1$，按一类占两份，二类占一份的比例，可以视作 $1$ 被等分成了 $S=2\times (a-x)+(b-y)$ 份。或者严格地，设二类名额中奖概率 $P(w_2)=p$，一类名额中奖概率 $P(w_1)=2p$。且有 $\displaystyle\sum_{\omega\in Q}P(w)=1⇒(b-y)\times p+(a-x)\times 2p=1$，不难解得 $p=\cfrac1{2(a-x)+b-y}$。则在此基础上，我们讨论：

1. Dmitry 获奖，概率为 $2p$。所以对当前状态的贡献即为 $2p$。
2. 另一个一类名额的人获奖，概率为 $(a-x-1)\times 2p$，因为需要减去 Dmitry 的一份贡献。假设已经搜索求到 $f(m+1,x+1,y)$ 的值，那么对当前状态的贡献为 $(a-x-1)\times 2p\times f[m+1][x+1]$。
3. 一个二类名额的人获奖，概率为 $(b-y)\times p$。假设已经搜索求到 $f(m+1,x,y+1)$ 的值，那么对当前状态的贡献为 $(b-y)\times p\times f[m+1][x]$。

综上，三者之和即为 $f[m][x]$ 的值。

最后考虑边界返回值：

- $m=n$ 时，抽奖次数已经用完，返回 $0$。
- $x=a$ 时，Dmitry 一定已经抽到了，返回 $1$。
- $y=b+1$ 时，当前状态已经非法，返回 $0$。
- 初始 $n>a+b$ 时，Dmitry 一定能抽到，不用搜索便可返回 $1$。

Dmitry 买了 **二类名额** 的情况同理，区别在于 $case1$ 中，Dmitry 中奖概率减半，而原本在 $case2$ 中减一的细节变成在 $case3$ 中减一。

### 细节

精度要求不高，double 够用，开 int 数组就行，不然容易爆空间。状态记录数组一开始记得赋初值。

### 代码

变量名都比较直观，两个函数分别对应两类名额，可以再借助代码理解状态转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3010;

int n, a, b;
double f[N][N], g[N][N], ans;

double dfs1(int x, int y, int m) {
	if (m == n) return 0;
	if (x == a) return 1;
	if (y == b + 1) return 0;
	if (f[m][x] != -1) return f[m][x];
	double all = 2.0*(a-x) + b-y;
	double won = 2.0 / all, Awon = 2.0*(a-x-1) / all, Bwon = 1.0*(b-y) / all;
	double res1 = 0, res2 = 0;
	if (x < a) res1 = dfs1(x+1, y, m+1);
	if (y < b) res2 = dfs1(x, y+1, m+1);
	f[m][x] = won + Awon * res1 + Bwon * res2;
	return f[m][x];
}

double dfs2(int x, int y, int m) {
	if (m == n) return 0;
	if (y == b) return 0;
	if (x == a + 1) return 0;
	if (g[m][x] != -1) return g[m][x];
	double all = 2.0*(a-x) + b-y;
	double won = 1.0 / all, Awon = 2.0*(a-x) / all, Bwon = 1.0*(b-y-1) / all;
	double res1 = 0, res2 = 0;
	if (x < a) res1 = dfs2(x+1, y, m+1);
	if (y < b) res2 = dfs2(x, y+1, m+1);
	g[m][x] = won + Awon * res1 + Bwon * res2;
	return g[m][x];
}

int main() {
	scanf("%d%d%d", &n, &a, &b);
	if (n > a+b) {
		printf("1.0\n1.0\n");
		return 0;
	}
	for (int i = 0; i <= n; i ++)
		for (int j = 0; j <= n; j ++)
			f[i][j] = -1;
	for (int i = 0; i <= n; i ++)
		for (int j = 0; j <= n; j ++)
			g[i][j] = -1;
			
	a ++; ans = dfs1(0, 0, 0);
	printf("%.16lf\n", ans);
	a --;
	b ++; ans = dfs2(0, 0, 0);
	printf("%.16lf\n", ans);
	b --;
	
	return 0;
}
```



---

