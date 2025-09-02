# [JSOI2008] Blue Mary的职员分配

## 题目描述

由于 Blue Mary 呕心沥血的管理，Blue Mary 的网络公司蒸蒸日上。现在一共拥有了 $n$ 名职员，可惜没有任何的金钱和声誉。平均每名每天职员都可以给公司带来 $x$ 单位金钱或者 $y$ 单位声誉（名利不能双全）。并且可以花费 $z$ 单位的金钱在人才交易市场发布广告招聘职员，每次发布广告三天以后就会招聘到一名职员，并且必须在发布广告并且招聘到职员的那一天才能发布下一次广告。 

Blue Mary 计划以最快的时间获得至少 $A$ 单位金钱和至少 $B$ 单位声誉，请你计算一下他至少需要多少时间才能达到他的目标。

## 说明/提示

提示：

$1 \le n,x,y,z,A,B \le 20$。

## 样例 #1

### 输入

```
1 2 3 4 5 6```

### 输出

```
5```

# 题解

## 作者：attack (赞：8)

std真的好~~暴力~~妙啊

感觉这题只要能列出状态来剩下的就是调代码了。。。

$f[i][a][b][sta]$表示此时已经有了$i$个人，$a$点金钱，$b$点声誉，离上一次打广告过去了$sta$天

转移的时候枚举一下当前的$i$个人干什么。

对于$sta$需要分类讨论，代码里有注释


```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 1e5 + 10, INF = 1e9 + 10;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, x, y, z, A, B; 
int f[41][21][21][4];
void Min(int &x, int y) {
	if(y < x) x = y;
}
main() {
#ifdef WIN32
	freopen("a.in", "r", stdin);
#endif
	N = read(); x = read(); y = read(); z = read(); A = read(); B = read();
	int ans = INF;
	memset(f, 0xf, sizeof(f));
	f[N][0][0][0] = 0;
	for(int i = N; i <= 40; i++) {
		for(int sta = 0; sta <= 3; sta++) {
			for(int a = 0; a <= max(A, z); a++) {//已经有了a的金钱 
				for(int b = 0; b <= B; b++) {//b的荣誉  
					if(f[i][a][b][sta] < ans) {
						int cur = f[i][a][b][sta];
						if(a >= A && b >= B) {ans = min(ans, cur); continue;}
						for(int pep = 0; pep <= i; pep++) {//有i个人挣钱 
							int na = min(a + pep * x, max(A, z)), nb = min(B, b + y * (i - pep));
							if(sta == 0) {
								Min(f[i][na][nb][0], cur + 1);
								if(na >= z) Min(f[i][na - z][nb][1], cur + 1);
							}
							//当前没有发广告，接下来可以不发广告，可以发广告 
							else if(sta == 1 || sta == 2) Min(f[i][na][nb][sta + 1], cur + 1);
							//当前已经发了广告，只能等着。。 
							else {
								Min(f[i + 1][na][nb][0], cur + 1);
								if(na >= z) Min(f[i + 1][na - z][nb][1], cur + 1); 
							}
							//当前发完了广告，考虑是否继续发广告 
						}						
					}
					//	if(f[i][a][b][sta] <= 100000)printf("%d %d %d %d %d\n", i, a, b, sta, f[i][a][b][sta]);
				}	
			}			
		}

	}
	printf("%d", ans);
}
```

---

## 作者：天南星魔芋 (赞：6)

比较暴力的做法。

------------

可以通过数据范围发现达成目标不会超过 $40$ 天，而招募员工一次要 $3$ 天，

并且因为招募越早越好，所以直接暴力枚举招募员工数量，然后暴力枚举天数（不超过 $15$）。

由于我们招募员工要钱，所以先集中赚钱，然后把多的退还回声誉即可。



```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,z,A,B;
int ans=0x7fffffff;
int minn(int x,int y){
	return x>y? y:x;
}
void js(int r,int m,int d){// 第 d 天，有 r 个人 ，有 m 元钱 
	while(m<A){m+=r*x;d++;}
	int b=B;
	while(m-x>=A){b-=y;m-=x;}
	while(b>0){b-=r*y;d++;}
	ans=minn(ans,d);
}
void dfs(int r,int m,int d){//枚举招募人数
	if(r>n+10)return ;
	js(r,m,d);
	while(m<z){m+=r*x;d++;}
	m+=r*x*3;
	d+=3;
	m-=z;
	dfs(r+1,m,d);
}
int main(){
	cin>>n>>x>>y>>z>>A>>B;
	dfs(n,0,0);
	cout<<ans<<endl;
}
```

完全不是一个蓝题的难度，建议降橙。

题目编号 $4399$ 好评。(



---

## 作者：Chiesl (赞：4)

最近学动规，闲着没事瞎跳题，~~跳到了这道水题~~。
## 题意简述

每名员工可以赚 $x$ 单位钱或 $y$ 单位声誉，且可以招募员工，求：赚到不少于 $A$ 单位钱以及 $B$ 单位声誉。

###### **~~达成 Blue Mary 名利双收的奢望~~**

## 算法

这是一道多维 DP 的题目啊，需要维护的状态不止一个。（此废话也！）

## 思路 & 解题过程

### 划分阶段：

那么先考虑划分阶段，以有多少个~~苦力~~员工为阶段。

最开始有 $n$ 个员工，则员工最多的情况为 40 人，证眀：

用数学归纳法：

#### 基本情况：

1. 当 $n = 1$ 时，公司有一个职员，不需要发布广告。公司总职员数不大于 40。

#### 归纳过程：

1. 假设在公司当前拥有 $k$ 名职员的情况下，公司总职员数不超过 40。即，公司当前有 $k$ 名职员，满足条件。

2. 考虑在增加一个职员后的情况，即 $k = k + 1$。公司有 $k + 1$ 名职员，需要确定是否仍然不超过 40 名职员。

	a. 如果公司已经满足 $A$ 和 $B$ 的要求（$kx \geq A$ 且 $ky \geq B$），则不需要发布广告，公司总职员数不超过 40。

	b. 如果公司当前的金钱或声誉不足以满足 $A$ 和 $B$ 的要求，公司需要发布广告。

	c. 每次发布广告三天后招聘到一个职员，必须等到招聘成功后才能发布下一次广告。因此，在 $k$ 名职员的情况下，公司每三天增加一个职员。

	d. 如果公司需要 $A$ 单位金钱，假设需要 $m$ 次发布广告，公司将获得 $\frac{mx}{3}$ 单位金钱（每次广告会获得 $x$ 单位金钱）。同样，如果公司需要 $B$ 单位声誉，需要 $p$ 次发布广告，公司将获得 $\frac{py}{3}$ 单位声誉（每次广告会获得 $y$ 单位声誉）。

	e. 现在考虑这些广告期间，公司新增的职员数量。由于每三天增加一个职员，公司在这段时间内将增加 $\frac{m}{3}$ 或 $\frac{p}{3}$ 名职员，取较小值。因此，在这些广告招聘成功后，公司将有 $k + \frac{m}{3}$（或 $k + \frac{p}{3}$）名职员。

综上所述，公司在 $k+1$ 名职员的情况下，会在原有 $k$ 名职员的基础上增加 $\frac{m}{3}$（或 $\frac{p}{3}$）名职员，总数为 $k + \frac{m}{3}$（或 $k + \frac{p}{3}$）。根据步骤 2 的假设，初始 $k$ 名职员的情况下不会超过 40 名职员，因此 $k + \frac{m}{3}$（或 $k + \frac{p}{3}$）也不会超过 40 名职员。

那么就用阶段变量 $i$ 表示当前公司有 $i$ 个人。

### 设计状态：

当该公司有 $i$ 个人时，有几种状态需要维护：

1. 此时距离公司最近一次发广告的时间。
2. 公司赚到的钱。
3. 公司赚到的声誉。

### 确定决策：

决策多少人赚钱，设 $m$ 人赚钱，则有：$0 \le m \le i$

### 确定状态转移方程：

设 $j$ 表示此时距离公司最近一次发广告的时间，$m$ 表示该单位时间赚钱员工数（$0 \le m \le i$），$k$ 表示这天之前总钱数，$l$ 表示这天之前总声誉数，$a$ 表示这天赚钱数量，$b$ 表示这天获得声誉数量。

则有：$a = k + m \times z$，$b = j + (i - m) \times y$

$f[i][a][b][j]$ 表示有 $i$ 个人，赚得 $a$ 元，$b$ 声誉，距离上次发广告 $j$ 天时最少天数。

分情况讨论：

1. 当 $j = 0$ 时：
	
    $f[i][a][b][j] = \min(f[i][a][b][j], f[i][k][l][j] + 1)$ 
    
    如果此时 $z \le a$，则有：$f[i][a - z][b][j + 1] = \min(f[i][a - z][b][j + 1], f[i][k][l][j] + 1)$
2. 当 $j = 1$ 或 $2$ 时：
	
    $f[i][a][b][j + 1] = \min(f[i][a][b][j + 1], f[i][k][l][j] + 1)$

3. 当 $j = 3$ 时：
	
    $f[i + 1][a][b][0] = \min(f[i + 1][a][b][0], f[i][k][l][j] + 1)$
    
    如果此时 $z \le a$，则有：$f[i + 1][a - z][b][1] = \min(f[i + 1][a - z][b][1], f[i][k][l][j] + 1)$
    
综上所述，状态转移方程共四种，由上可知。

### 确定边界：

当人数为初始人数，所赚取得金钱、声誉皆为零，且未发出广告时，需要的天数为零，即：$f[n][0][0][0] = 0$

### 目标解：

设$f[i][a][b][j]$ 表示有 $i$ 个人，赚得 $a$ 元，$b$ 声誉，距离上次发广告 $j$ 天时最少天数。

则目标解为所有 $a \ge A$ 且 $b \ge B$ 情况的天数最小值。

## 程序实现：

### 递推实现：
分数：100 分
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[42][22][22][4];
int main () {
	int n, x, y, z, A, B, M1, ans = INT_MAX;
	scanf("%d%d%d%d%d%d", &n, &x, &y, &z, &A, &B);//用c风格，养成好习惯
	memset(f, 0x7f, sizeof(f));	//0x3f可能会WA，保险起见用0x7f
	M1 = max(A, z);
	f[n][0][0][0] = 0;
	for (int i = n; i <= 40; i++) {
		//枚举人数
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k <= M1; k++) {
				for (int l = 0; l <= B; l++) {				
					if (f[i][k][l][j] >= ans) continue;
					//此时的天数已无法带来最优解。放在递推里的"剪枝"，没见过吧？
					int d = f[i][k][l][j];
					if (k >= A && l >= B) {//更新最优解
						ans = min(ans, d);
						continue;
					}
					for (int m = 0; m <= i; m++) {
						int a = min(k + m * x, M1), 
						/*对于a的计算，对于所有赚到的钱大于A和z的，算作A和z中较大者就行
						（从题解区大佬attack那学到的，不然数组要开的更大，膜拜大佬）*/
						b = min(l + y * (i - m), B);
						if (!j) {
							f[i][a][b][j] = min(f[i][a][b][j], d + 1);
							if (a >= z) f[i][a - z][b][j + 1] = min(f[i][a - z][b][j + 1], d + 1);
						} else if (j < 3) {
							f[i][a][b][j + 1] = min(f[i][a][b][j + 1], d + 1);
						} else {
							f[i + 1][a][b][0] = min(f[i + 1][a][b][0], d + 1);
							if (a >= z) f[i + 1][a - z][b][1] = min(f[i + 1][a - z][b][1], d + 1);
						}//上面有详细讲解，此处不过多赘述					
					}

				}
			}
		}
	}
	printf("%d", ans);
	return 0;
}
```
递归实现：（完全没必要好吧）

分数：50 分

蒟蒻太菜，就不放出来了 qwq。

---

## 作者：allenchoi (赞：2)

### 前言：  
一道水题（要是现在的省选这个难度就好力
### 科技：  
广搜（似乎是  
### 思路：  
设 $f_{i,a,b,c,l}$ 表示第 $i$ 天，有 $a$ 单位的钱和 $b$ 单位的声誉，有 $c$ 名已开始工作的员工，上次招聘的员工还有 $l$ 天开始工作（如果上一次招聘在 $3$ 天或以前则 $l=0$）。  
但是我们感觉这样子很难转移，于是改成广搜：  
假设我们知道第 $i$ 天所有的状态，我们就可以依此推出第 $i+1$ 天所有可能的状态：  
更新员工数量，枚举这一天有多少员工赚钱（其余的提高声誉），是否招聘新的员工（可以的话）。  
不过要注意剪枝：  
可以发现，在最优解的情况下，$a$ 的值都不会超过 $\left\lceil\dfrac{A}{x}\right\rceil\times x$，$b$ 的值都不会超过 $\left\lceil\dfrac{B}{y}\right\rceil\times y$，经过计算可得，$a,b\le40$，因此，我们可以首先把 $a>40$ 或 $b>40$ 的状态删去。  
然后，一定要把重复的状态去掉（因为脑子抽了没加这个，导致状态存不下一直 MLE，加了就 AC...）。  
### 代码：  
用了滚动数组实现，所以看起来雀食不大像广搜...  
~~~cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 5;
int n,x,y,z,a,b,t1,t2,vis[45][45][45][5];
struct stm{int a,b,c,l;} p[N],f[N],tmp;
bool upd(stm x)
{
	if(vis[x.a][x.b][x.c][x.l]) return false;
	f[++t2] = x;
	vis[x.a][x.b][x.c][x.l] = 1;
	return true;
}
int main()
{
	scanf("%d%d%d%d%d%d",&n,&x,&y,&z,&a,&b);
	t1 = 1;
	p[1] = (stm){0,0,n,0};
	for(int i = 1;;i++)
	{
		memset(vis,0,sizeof(vis));
		t2 = 0;
		for(int j = 1;j <= t1;j++)
		{
			if(p[j].l == 1) p[j].c++;
			for(int k = 0;k <= p[j].c;k++)
			{
				if(p[j].a + k * x > 40 || p[j].b + (p[j].c - k) * y > 40) continue;
				tmp.l = max(p[j].l - 1,0);
				tmp.c = p[j].c;
				tmp.a = p[j].a + k * x;
				tmp.b = p[j].b + (p[j].c - k) * y;
				if(upd(tmp) && f[t2].l == 0 && p[j].a >= z)
				{
					tmp = f[t2];
					tmp.a -= z;
					tmp.l = 3;
					upd(tmp);
				}
			}
		}
		t1 = t2;
		for(int j = 1;j <= t2;j++)
		{
			if(f[j].a >= a && f[j].b >= b)
			{
				printf("%d\n",i);
				return 0;
			}
			p[j] = f[j];
		}
	}
	return 0;
}
~~~

---

## 作者：XL4453 (赞：2)

---
### 解题思路：

数据范围很小，考虑动态规划。

设 $f_{i,j,k,l}$ 表示已经有了 $i$ 个职员，$j$ 单位金钱，$k$ 单位荣誉，当前广告的状态为 $l$，能到达此状态的最小天数。其中，$l=0$ 表示未发广告，$l=1,2,3$ 分别表示发完之后过了 $1$，$2$，$3$ 天。  

然后考虑转移，哪一些人骗钱哪一些人骗荣誉是需要枚举的，然后很据 $l$ 的状态分情况讨论。如果当前 $l$ 的状态不为 $1$ 或者 $2$ 且金钱足够就可以发广告，当然，也可不发。否则的话只能将 $l$ 的状态加一，也就是等待。

---
招员工的金钱可能要比最后要求达到的金钱数量多，所以要对这两者进行取模。转移的时候要将所有的超过的金钱和荣誉划归为最大值。

最后注意循环枚举状态的顺序，$l$ 的枚举要放在外面，这一维其实也就是一种变相的“时间”维。

---
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,x,y,z,a,b,f[45][40][25][5],ans;
int main(){
	scanf("%d%d%d%d%d%d",&n,&x,&y,&z,&a,&b);
	memset(f,0x3f,sizeof(f));
	f[n][0][0][0]=0;ans=2147483647;
	//0 未发广告  1，2 发了广告之后第一，二天  3 收到人  
	for(int i=n;i<=40;i++){
		for(int l=0;l<=3;l++){
			for(int j=0;j<=max(z,a);j++){
				for(int k=0;k<=b;k++){
					int now=f[i][j][k][l];
					if(j>=a&&k==b)ans=min(ans,f[i][j][k][l]);
					
					for(int ii=0;ii<=i;ii++){
						
						if(l==1||l==2)
						f[i][min(max(a,z),j+x*ii)][min(b,k+y*(i-ii))][l+1]=
						min(f[i][min(max(a,z),j+x*ii)][min(b,k+y*(i-ii))][l+1],f[i][j][k][l]+1);
						
						if(l==0){
							f[i][min(max(a,z),j+x*ii)][min(b,k+y*(i-ii))][0]=
							min(f[i][min(max(a,z),j+x*ii)][min(b,k+y*(i-ii))][0],f[i][j][k][l]+1);
							
							if(j+x*ii-z>=0)
							f[i][min(max(a,z),j+x*ii-z)][min(b,k+y*(i-ii))][1]=
							min(f[i][min(max(a,z),j+x*ii-z)][min(b,k+y*(i-ii))][1],f[i][j][k][l]+1);
						}
						
						if(l==3){
							f[i+1][min(max(a,z),j+x*ii)][min(b,k+y*(i-ii))][0]=
							min(f[i+1][min(max(a,z),j+x*ii)][min(b,k+y*(i-ii))][0],f[i][j][k][l]+1);
							
							if(j+x*ii-z>=0)
							f[i+1][min(max(a,z),j+x*ii-z)][min(b,k+y*(i-ii))][1]=
							min(f[i+1][min(max(a,z),j+x*ii-z)][min(b,k+y*(i-ii))][1],f[i][j][k][l]+1);
						}
					}
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：mlj2004 (赞：1)

## P4399 Blue marry的职员分配



本题数据实在过水... 20 的范围完全可以扩大到 1e6... 本题解给出一种 $O(m \log m)$ $(m = \max(A,B))$ 复杂度的解法~


---

#### 翻译题干：

初始有 $n$ 名员工进行工作获得 $x$ 金钱或 $y$ 声誉。在第 $k$ 天时，若前 $k-1$ 天挣到的总钱数大于 $z$ ，则可以花费 $z$ 金钱进行招募，第 $k+3$ 天获得一名员工（第 $k+3$ 天可工作）且第 $k+1$ 和 $k+2$ 无法进行招募。

### 解题思路：

先不考虑招人操作，假如总工作时长一定，可以注意到选择挣钱还是挣声誉的顺序并不重要，只需要总工作时长大于 $\lceil \frac{A}{x} \rceil+ \lceil \frac{B}{x}\rceil$ 即可。

#### 考虑二分答案+贪心

假设总共进行 $t$ 天直接暴力模拟每一天，统计总工作时长 $s$，不难发现其中只有招人操作需要决策。若第 $k$ 天前金钱足够招人，考虑招到新人造成的工时收益为 $t-k-2$ 个工时，考虑到 $z$ 不一定是 $x$ 的整数倍，考虑通过等效金钱比较是否为正收益,即 $(t-k-2) \times x \ge z$ 即可。因此局部最优等价于全局最优，可以贪心（因为只需要总工时足够即可，可以随意调整顺序不必担心金钱溢出等）。

由于只统计了了总工时，所以招募后不能不立即扣钱，通过记录 $c$ 表示招募总花费，判断挣到的钱够不够招人时 判断 $s \times x \ge z+w$ 并且 A += w 的方式在算答案时变向扣除费用。

注意到 $n,x,y \ge 1$ 因此总天数 $s$ 小于等于 $m=\max(A,B)$ 直接二分答案复杂度 $O(\log m)$，贪心判断 $O(m)$，总复杂度 $O(m\log m)$。 


代码附上：（有注释供参考）

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

#define LL long long

using namespace std;

LL read(){
	LL x=0,k=1;char ch=getchar();
	while('0'>ch || ch >'9'){if(ch=='-')k=-1;ch=getchar();}
	while('0'<=ch && ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*k;
}
int n,x,y,z,A,B;
bool check(int t){
	int sum=0,lst=-5,w=n,c=0;
    //sum表示总工时，lst表示最后一次招募时间
    //w表示员工数，c表示招募总费用
	for(int k=1;k<=t;k++){
		if(lst == k-3 )w++;  //招募到新人
		if(lst <= k-3 && sum*x >= c+z && x*(t-k-2) >= z){
			//判断是否发广告
			c+=z; //更新当前招募总费用
			lst=k; 
		}
		sum+=w; //统计总工时
	}
	if(((A+c)+x-1)/x + (B+y-1)/y <=sum) return 1;
  //判断总工时是否充足
	return 0;
}
int main()
{
    n=read();x=read();y=read();z=read();A=read();B=read();
	int l=1,r=40,ans=-1;//二分答案
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	cout<<ans<<endl;
    return 0;
}
```
PS：本蒟蒻阅读能力欠佳，模糊题干读不懂一点，样例强度属实过低毫无启发性，调了半天才过~

---

## 作者：Heart_Of_Iron_4 (赞：0)

这道题是 $dp$ 毫无疑问，但我提供一个压成 $3$ 维的想法。\
因为每个员工每天能搞到 $x$ 个钱，$y$ 个声誉，所以 $y$ 个声誉 $=x$ 个钱。\
所以我们令 $a=a+\lceil a\div y \rceil \times x$，\
（$\lceil \rceil$ 是上取整函数），这样只算钱就行了。\
$dp_{i,j,k}=l$\
指现在有 $i$ 个职员，下次时刻为 $j$ 时能发广告，有 $k$ 个钱，时刻为 $l$。

转移方程如下：

```cpp
//新招收员工
dp[i+1][dp[i][j][k]+3][k-z+3*i*x]=min(dp[i][j][k]+3)

//原来的员工赚了一天钱
dp[i][j][k+i*x]=min(dp[i][j][k]+1)
```

最后统计一下 钱比 $a$ 多的状态 的时刻最小值就行了 qaq。\
其他细节在代码里。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define getmin(qwe,wer) qwe>wer?qwe=wer:114514
int dp[110][110][610];
int n,x,y,z,a,b,ans;
signed main()
{
	memset(dp,0x3f3f3f3f,sizeof dp);
	cin>>n>>x>>y>>z>>a>>b;
	a+=ceil(b*1.0/y)*x;
	//cout<<a<<endl;
	dp[n][0][0]=0;
	for(int i=n;i<=n+15;++i)
	{
		for(int j=0;j<=40;++j)
		{
			for(int k=0;k<=a+40;++k)
			{
				if(dp[i][j][k]>=4557430888798830399)continue;
				//printf("%lld %lld %lld %lld\n",i,j,k,dp[i][j][k]);
				if(dp[i][j][k]<j)continue;
				if(dp[i][j][k]>=j&&k>=z)
				{
					getmin(dp[i+1][dp[i][j][k]+3][k-z+3*i*x],dp[i][j][k]+3);
				}
				getmin(dp[i][j][k+i*x],dp[i][j][k]+1);
			}
		}
	}
	ans=INT_MAX;
	for(int i=a;i<=a+40;++i)
	{
		for(int j=n;j<=n+15;++j)
		{
			for(int k=0;k<=40;++k)
			{
			//	if(dp[j][k][i]<ans)cout<<j<<" "<<k<<" "<<i<<" "<<dp[j][k][i]<<endl;
				ans=min(dp[j][k][i],ans);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：I_am_Lord_Voldemort (赞：0)

刚拿到题目，发现数据规模是真的小，所以直接爆搜。而且数据规模大致可以过。（$2^{20}\times400=4\times10^8$，可以剪枝）。那么那些数值会影响我们的决策呢？

我们发现，人数，钱，声誉，时间以及上一次招募时间会影响答案，因此要记录这些信息。有了这些，就可以愉快的暴力了。

我们枚举当前所有的人数，暴力枚举多少人挣钱，其余人就挣声望。如果钱足够，可以去多找个人，然后记录上次招人时间，三天后人数增加。细节见代码。

对了，记得剪枝喔。我们可以记录每个状态是否到达过，同时判断当前日期是否超过了当前答案。这样就通过啦（63ms，跑得飞快）。

时间复杂度估计如下：由于数据小于二十，所以一个人最多四十天就整完了。如果多余四十天会自动剪枝。因此找的人数也不会太多，至少要三天才一个。由于后面的剪枝比较厉害，所以天数正常就最多十几天。复杂度在 $O(x^{10})$ 左右吧。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int n,x,y,z,A,B,ans=40;
bool tag[41][20][100][100][41];
void dfs(int tim,int sum,int a,int b,int last){ //sum为人,x为钱,y为誉,last为日
	if(tag[tim][sum][a][b][last]) return;
	tag[tim][sum][a][b][last]=1;
	if(tim>=ans) return;
	if(a>=A&&b>=B){
		ans=min(ans,tim);
		return; 
	}
	if(tim-last==3&&last) sum++;
	for(int i=0;i<=sum;i++){
		dfs(tim+1,sum,a+i*x,b+(sum-i)*y,last);
		if(a+i*x>A) break;
		if(a>=z) dfs(tim+1,sum,a+i*x-z,b+(sum-i)*y,tim);
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	cin>>n>>x>>y>>z>>A>>B;
	dfs(0,n,0,0,0);
	cout<<ans;
}
```

---

