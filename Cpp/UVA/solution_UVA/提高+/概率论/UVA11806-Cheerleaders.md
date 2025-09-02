# Cheerleaders

## 题目描述

你有一个 $n\times m$ 的网格图，现在你要将 $k$ 个人放在网格中，满足以下条件：
- 网格图的四个边都至少有一个人；
- 每个格子上不能有两个人；
- 每个人必须都有位置。

求放的方案数，答案对 $10^6+7$ 取模。

注意：四个角的人可以同时算作在两个边上。

## 说明/提示

数据范围：$T\le 50,2\le n,m\le 20,k\le 500$。

## 样例 #1

### 输入

```
2
2 2 1
2 3 2```

### 输出

```
Case 1: 0
Case 2: 2```

# 题解

## 作者：Sternenlicht (赞：5)

思路：

用容斥原理，将问题转换成：求第一行、第一列、最后一行、最后一列都没有石子的方案数。

设满足 “第一行没有石子” 的方案集为 $A$，满足 “最后一行没有石子” 的方案集为 $B$。

设满足 “第一列没有石子” 的方案集为 $C$，满足 “最后一列没有石子” 的方案集为 $D$。

设全集为 $S$，答案为“在 $S$ 中但不在 $A$，$B$，$C$，$D$ 任何一个集合中” 的元素个数。很明显为容斥原理。

用二进制来表示 $A$，$B$，$C$，$D$ 的所有搭配（$S$ 为空搭配）。

若在集合 $A$ 和 $B$ 中，相当于少了一行。

若在集合 $C$ 和 $D$ 中，相当于少了一列。

设最后剩了 $r$ 行 $c$ 列，方案数为 $C^{rc}_k$。


```
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e6+7;
const int N = 500+10;
int C[N][N],T;
int main(){
	//求组合数，注意初始化 
	C[0][0]=1;
	for (int i=0;i<=N-10;i++){
		C[i][0]=C[i][i]=1;
		for (int j=1;j<i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	scanf("%d",&t);
	for (int Case=1;Case<=T;Case++){
		int n,m,k,ans=0;scanf("%d%d%d",&n,&m,&k);
		for (int S=0;S<16;S++){//枚举16种搭配方式 
			int cnt=0,r=n,c=m;//cnt统计集合个数，r为行数，c为列数 
			if (S&1)r--,cnt++;
			if (S&2)r--,cnt++;
			if (S&4)c--,cnt++;
			if (S&8)c--,cnt++;
			if (cnt&1)ans=(ans+mod-C[r*c][k])%mod;//奇数个条件做减法 
			else ans=(ans+C[r*c][k])%mod;//偶数个条件做加法 
		}
		printf("Case %d: %d\n",Case,ans);
	}
    return 0;
}

---

## 作者：potatoler (赞：4)

#### [题目](https://www.luogu.com.cn/problem/UVA11806)大意

有一个 n*m 的网格场地，现在把 k 个人放进去，要求满足：

1. 四个边都至少有一个人
2. 一个格子最多放一个人
3. 每个人都要放进去

求有多少种合法的放法——答案对 1e6+7 取模

注：四个角上的人可以看做同时在一行和一列

#### 思路

这道题中计算合法的方案数比较困难，所以我们可以计算出全部的方案数再减去不合法的方案数

不考虑约束条件，单纯地将这些人放进网格中，方案数显然有 $allAnswer=C^k_{mn}$

我们知道有四种因素会导致方案不合法，我们用四个集合表示具有某种因素的不合法方案：

- $A:$ 第一行没有人

- $B:$ 最后一行没有人

- $C:$ 第一列没有人
- $D:$ 最后一列没有人

于是就可以通过容斥原理计算合法的方案数了：
$$
approvedAnswer=allAnswer+A\cap B\cap C\cap D$$
$$-(A\cap B\cap C+A\cap B\cap D+A\cap C\cap D+B\cap C\cap D)$$
$$+(A\cap B+A\cap C+A\cap D+B\cap C+B\cap D+C\cap D)-(A+B+C+D)
$$
对于任意一种方案数我们都可以用一个四元组表示这种方案具有哪几个不合法因素，其中每个元素1表示具有这种不合法因素，0表示没有。更进一步的，可以将这个四元组通过状态压缩记录在一个整形中，于是我们只需要通过0到15这16个数就可以遍历所有方案的种类，通过与1，2，4，8进行&运算就可以判断是否具有某种不合法因素。

如果一种方案具有$A$这个不合法因素，那么这种方案其实就是将原来的网格场地消去一行之后所有的方案数，即对于(n-1)*m的场地放k个人的全部方案数——$C^k_{m(n-1)}$，和我们一开始求出的 $allAnswer$ 得到了统一。

上面的公式中，约束条件的个数决定了加减，即满足「偶加奇减」原则。因为 $allAnswer$ 实质上是不受任何不合法条件约束的一种特殊的不合法情况，其不合法因素数是0，所以在&1时结果为0，判断为偶数，于是也要加上——和公式相符，不需要特判。

至此，这道题就做完了。不过还有值得注意的一点：在不合法因素数为奇数，需要减去时，我们需要先累加一个模数在进行减法运算，这样就可以保证在取模意义下结果正确而不会因减法运算后得到负数而导致取模后得到负数，以致答案错误。

#### 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int mod=1e6+7,maxn=405;
int n,m,k,T;
int c[maxn][maxn],ans;
void init(){//Calculate value of combinatorial number at the very first.
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<maxn;i++){
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
}
int main(){
	init();
	scanf("%d",&T);
	for(int gameRound=1;gameRound<=T;gameRound++){
		ans=0;
		scanf("%d%d%d",&n,&m,&k);
		for(int gameCase=0;gameCase<16;gameCase++){
			int fieldRow=n,fieldColumn=m,situationSummary=0;
			if(gameCase&1) fieldRow--,situationSummary++;
			if(gameCase&2) fieldRow--,situationSummary++;
			if(gameCase&4) fieldColumn--,situationSummary++;
			if(gameCase&8) fieldColumn--,situationSummary++;
			if(situationSummary&1) ans=(ans+mod-c[fieldRow*fieldColumn][k])%mod;
			//Plus "mod" to avoid "ans" becoming a negative.
			else ans=(ans+c[fieldRow*fieldColumn][k])%mod;
		}
		printf("Case %d: %d\n",gameRound,ans);
	}
	return 0;
}
```



---

## 作者：11D_Beyonder (赞：3)

[食用博客](https://pro_11d_beyonder.gitee.io/2020/07/11/UVA-11806-Cheerleaders/)   
&emsp;&emsp;In most professional sporting events, cheerleaders play a major role in entertaining the spectators. Their roles are substantial during breaks and prior to start of play. The world cup soccer is no exception.  
&emsp;&emsp;Usually the cheerleaders form a group and perform at the center of the field. In addition to this group, some of them are placed outside the side line so they are closer to the spectators. The organizers would like to ensure that at least one cheerleader is located on each of the four sides. For this problem, we will model the playing ground as an $m\times n$ rectangular grid. The constraints for placing cheerleaders are described below.  
&emsp;&emsp;There should be at least one cheerleader on each of the four sides. Note that, placing a cheerleader on a corner cell would cover two sides simultaneously. There can be at most one cheerleader in a cell. All the cheerleaders available must be assigned to a cell. That is, none of them can be left out.  
![](https://i.niupic.com/images/2020/07/11/8ojh.png)  
&emsp;&emsp;The organizers would like to know, how many ways they can place the cheerleaders while maintaining the above constraints. Two placements are different, if there is at least one cell which contains a cheerleader in one of the placement but not in the other.  
## Input  
&emsp;&emsp;The first line of input contains a positive integer $T ≤ 50$, which denotes the number of test cases.   
&emsp;&emsp;$T$ lines then follow each describing one test case. Each case consists of three nonnegative integers, $2 ≤ m,n ≤ 20$ and $k ≤ 500$. Here $m$ is the number of rows and $n$ is the number of columns in the grid. Kdenotes the number of cheerleaders that must be assigned to the cells in the grid.  
## Output  
&emsp;&emsp;For each case of input, there will be one line of output. It will first contain the case number followed by the number of ways to place the cheerleaders as described earlier. Look at the sample output for exact formatting. Note that, the numbers can be arbitrarily large. Therefore you must output the answers modulo $1000007$.  
## Sample Input  
2
2 2 1
2 3 2
## Sample Output  
Case 1: 0  
Case 2: 2  
## Idea  
&emsp;&emsp;直接考虑四个边界的放置情况较难，采用**正难则反**的策略。考虑第一行不放棋子，最后一行不放棋子，第一列不放棋子，最后一列不放棋子的情况。  
&emsp;&emsp;设 $A$ 为第一行不妨棋子的方案集合，$B$ 为最后一行不放棋子的方案集合，$C$ 为第一列不放棋子的方案集合，$D$ 为最后一列不放棋子的方案集合。在 $m\times n$ 棋盘中放置 $k$ 个棋子的总方案数为 $\begin{pmatrix}mn\\k\end{pmatrix}$，则满足题目要求的方案数为 $\begin{pmatrix}mn\\k\end{pmatrix}-|A\cup B\cup C\cup D|$。  
&emsp;&emsp;根据容斥原理，$|A\cup B\cup C\cup D|=|A|+|B|+|C|+|D|-|A\cap B|-|A\cap C|-|A\cap D|-|B\cap C|-|B\cap D|-|C\cap D|+|A\cap B\cap C|+|A\cap B\cap D|+|A\cap C\cap D|+|B\cap C\cap D|-|A\cap B\cap C\cap D|$。  
&emsp;&emsp;$A$：第一行不放棋子，$|A|=\begin{pmatrix}(m-1)n\\k\end{pmatrix}$。   
&emsp;&emsp;$B$：最后一行不放棋子，$|B|=\begin{pmatrix}(m-1)n\\k\end{pmatrix}$。   
&emsp;&emsp;$C$：第一列不放棋子，$|C|=\begin{pmatrix}m(n-1)\\k\end{pmatrix}$。   
&emsp;&emsp;$D$：最后一列不放棋子，$|D|=\begin{pmatrix}m(n-1)\\k\end{pmatrix}$。    
&emsp;&emsp;$A\cap B$：第一行和最后一行都不放棋子，$|A\cap B|=\begin{pmatrix}(m-2)n\\k\end{pmatrix}$。
&emsp;&emsp;$A\cap C$：第一行和第一列都不放棋子，$|A\cap C|=\begin{pmatrix}(m-1)(n-1)\\k\end{pmatrix}$。   
&emsp;&emsp;$A\cap D$：第一行和最后一列都不放棋子，$|A\cap D|=\begin{pmatrix}(m-1)(n-1)\\k\end{pmatrix}$。   
&emsp;&emsp;$B\cap C$：最后一行和第一列都不放棋子，$|B\cap C|=\begin{pmatrix}(m-1)(n-1)\\k\end{pmatrix}$。   
&emsp;&emsp;$B\cap D$：最后一行和最后一列都不放棋子，$|B\cap D|=\begin{pmatrix}(m-1)(n-1)\\k\end{pmatrix}$。   
&emsp;&emsp;$C\cap D$，第一列和最后一列都不放棋子，$|C\cap D|=\begin{pmatrix}m(n-2)\\k\end{pmatrix}$。   
&emsp;&emsp;$A\cap B\cap C$，第一行、最后一行、第一列都不放棋子，$|A\cap B\cap C|=\begin{pmatrix}(m-2)(n-1)\\k\end{pmatrix}$。   
&emsp;&emsp;$A\cap B\cap D$，第一行、最后一行、最后一列都不放棋子，$|A\cap B\cap D|=\begin{pmatrix}(m-2)(n-1)\\k\end{pmatrix}$。   
&emsp;&emsp;$A\cap C\cap D$，第一行、第一列、最后一列都不放棋子，$|A\cap C\cap D|=\begin{pmatrix}(m-1)(n-2)\\k\end{pmatrix}$。   
&emsp;&emsp;$B\cap C\cap D$，最后一行、第一列、最后一列都不放棋子，$|B\cap C\cap D|=\begin{pmatrix}(m-1)(n-2)\\k\end{pmatrix}$。   
&emsp;&emsp;$A\cap B\cap C\cap D$：第一行、最后一行、第一列、最后一列都不放棋子，$|A\cap B\cap C\cap D|=\begin{pmatrix}(m-2)(n-2)\\k\end{pmatrix}$。     
&emsp;&emsp;综上所述，答案为 $\begin{pmatrix}mn\\k\end{pmatrix}-2\times \begin{pmatrix}(m-1)n\\k\end{pmatrix}-2\times \begin{pmatrix}m(n-1)\\k\end{pmatrix}+\begin{pmatrix}(m-2)n\\k\end{pmatrix}+\begin{pmatrix}m(n-2)\\k\end{pmatrix}+4\times \begin{pmatrix}(m-1)(n-1)\\k\end{pmatrix}-2\times \begin{pmatrix}(m-2)(n-1)\\k\end{pmatrix}-2\times \begin{pmatrix}(m-1)(n-2)\\k\end{pmatrix}+\begin{pmatrix}(m-2)(n-2)\\k\end{pmatrix}$。    
## Code  
```cpp
#include <iostream>
using namespace std;
const int mod=1000007;
const int N=502;
int C[N][N];
int m,n,k;
void init()
{
	int i,j;
	for(i=0;i<N;i++)
	{
		C[i][0]=C[i][i]=1;
		for(j=0;j<i;j++)
		{
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
}
int main()
{
	init();
	int _,CASE=0;
	for(cin>>_;_;_--)
	{
		scanf("%d%d%d",&m,&n,&k);
		printf("Case %d: %lld\n",++CASE,
		((C[m*n][k]
		-2*C[(m-1)*n][k]-2*C[m*(n-1)][k]
		+C[(m-2)*n][k]+C[m*(n-2)][k]+4*C[(m-1)*(n-1)][k]
		-2*C[(m-2)*(n-1)][k]-2*C[(m-1)*(n-2)][k]
		+C[(m-2)*(n-2)][k])%mod+mod)%mod);
	}
	return 0;
}
```
## PostScript  
&emsp;&emsp;注意！$1000007=29\times 34483$，$1000007$ 不是质数。求 $x$ 的逆元时，万万不可直接利用 $\mathrm{inv}(x)\equiv x^{p-2}\pmod p$。这题数据范围不大，老老实实打表吧。  

---

## 作者：Hzao (赞：2)

20190912 upd:审核通过之后发现之前写的组合数格式$C[n][m]$太难看了，重新优化了成了$C_{n}^{m}$的亚子。

这是一个不用容斥原理的做法。


以下内容中$C_{n}^{m}$表示组合数。


考虑四角上四个点的情况:

$1.$**四个角都不放人。**

显然需要枚举最外圈（第一行、最后一行、第一列、最后一列的并集）除开四个角之外的放置方案。

设第一列、最后一列、第一行、最后一行中除开第一个位置和最后一个位置分别放置$j_1,j_2,k_1,k_2$个人，那么它们分别有：$C_{n-2} ^{j_1},C_{n-2}^{j_2}, C_{m-2}^{k_1},C_{m-2}^{k_2}$种放置方法。(需要保证$1 \leq j_1,j_2,k_1,k_2 <k$且$j_1+j_2+k_1+k_2 \leq k$)

除开最外圈，里面还剩下$left=k-(j_1+j_2+k_1+k_2)$个人，需要把他们放置在中间共$(m-2) (n-2)$ 个位置上。有$ C_{(m-2)  (n-2)}^{left} $ 种方法。


所以一共有$ ( \sum C_{n-2}^{j_1} C_{n-2}^{j_2} C_{m-2}^{k_1} C_{m-2}^{k_2})  C_{(m-2)  (n-2)}^{left}$种方案。

(也就是说要枚举$j_1,j_2,k_1,k_2$)




$2.$**仅一个角放人。** 那么又有四种情况:左上、左下、右上、右下。显然这四种是等价的，求一种之后乘以$4$即为答案。

为了方便讲述，假设选择了左上的那一个角。

那么第一行、第一列都不需要找了。为了使方案合法，我们需要一种方案，使得最后一行、最后一列都有人。

因为左下、右上、右下都不放人，所以最后一列$n-2$个位置中至少要选择一个人，最后一行$m-2$个位置中要选择至少一个人。

假设最后一列放$j_1$个人，最后一行放$k_1$个人，那么方案数为$C_{n-2}^{j_1}  C_{m-2}^{k_1}$.

除去左上角一个点、最后一整列、最后一整行，还剩下$(m-1)  (n-1)-1$个点可以放人，还剩下$k-j_1-k_1-1$个人需要放。

于是放这剩下的$k-j_1-k_1-1$个人就有$C_{(m-1) (n-1)-1}^{k-j_1-k_1-1}$种方法。

于是这种情况下有$(\sum C_{n-2}^{j_1}  C_{m-2}^{k_1}) C_{(m-1)  (n-1)-1} ^ { k-j_1-k_1-1}$种方法。

**3.有且只有两个角放人。** 

 _假设这两个人不在同一对角线上_ ：
 
 那么只有在$n>2$时才能在左上左下、右上右下放置。只有在$m>2$时才能在左上右上、左下右下放置。(否则若要满足情况，则不止要放$2$个角)。

假设$n>2$且在左上左下(或者右上右下)放置，那么只有最后一列(或者第一列)没有被覆盖了。我们需要在最后一列(或者第一列)的$n-2$个位置上选出至少一个人来参与。设选择$j$人，那么方案数为$C_{n-2}^{j}$。

还剩下$left=k-2-j$个人，放置在$nm-2-n$个位置。

方案数为$(\sum C_{n-2}^{j})  C_{n  m-2-n}^{left}$。
由于可以选左上左下或者右上右下，所以需要把这个玩意乘以$2$。

同理，如果$m>2$且选择左上右上（或者左下右下)，给最后一行（或者第一行）放置$j$个人，那么方案数共为：$(\sum C_{m-2}^{j})  C_{n  m-2-m}^{left}$。同样需要计数时乘以$2$。


 _假设在同一对角线上：_ 

除了四个角，每个位置都可以放置，方案数为$C_{n m-4}^{k-2}$。在对角线上有两种情况（左上右下，左下右上），所以这个数也要乘以$2$。

**4.有且只有三个角放人。**

那么无论怎么放，都是满足条件的。
$4$个点中选出$3$个有$C_{4}^{3}$种方法，除开四角有$C_{n  m - 4}^{k-3}$种方法。

所以计数：$C_{4}^{3}C_{nm-4}^{k-3}$。


**5.所有角都放人。**


那么所有角都放人有一种方法，除开这四个角共有$C_{n  m -4}^{k-4}$种方法，所以计数$C_{nm-4}^{k-4}$。

当然要记得每步取模。

代码:

```cpp
#include<cstdio>
#include<cstring>
// #define LOC

const long long mod=1000007;
long long C[505][505];
long long n,m,k;
long long ans;
long long T;
int kase;
void init(){
    C[0][0]=1;
    for(register int i=1;i<=500;++i){
        C[i][0]=1;
        for(register int j=1;j<=i;++j){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
            C[i][j]%=mod;
            // printf("C[%d][%d]=%lld\n",i,j,C[i][j]);
        }
    }
}

void work(){
    scanf("%lld%lld%lld",&n,&m,&k);
    ans=0;
    if(m*n>=k){
        {//四个角都不放人
            for(register int j1=1;j1<=n-2;++j1){
                if(j1>=k)continue;
                for(register int j2=1;j2<=n-2;++j2){
                    if(j1+j2>=k)continue;
                    for(register int k1=1;k1<=m-2;++k1){
                        if(j1+j2+k1>=k)continue;
                        for(register int k2=1;k2<=m-2;++k2){
                            if(j1+j2+k1+k2>k)continue;
                            ans+=C[n-2][j1]*C[n-2][j2]%mod*C[m-2][k1]%mod*C[m-2][k2]%mod*C[(m-2)*(n-2)][k-(j1+j2+k1+k2)]%mod;
                            ans%=mod;
                        }
                    }
                }
            }
            ans%=mod;
        }

        {// 一个角上放人
            for(register int j1=1;j1<=n-2&&j1<k;++j1){
                for(register int k1=1;k1<=m-2;++k1){
                    if(j1+k1+1>k)continue;
                    ans+=C[n-2][j1]*C[m-2][k1]%mod*C[(m-1)*(n-1)-1][k-1-j1-k1]%mod*4%mod;
                    ans%=mod;
                }
            }
            ans%=mod;
        }

        {//左上左下或者右上右下放置
            for(register int j=1;j<=n-2&&j<=k-2;++j){
                ans+=C[n-2][j]*C[m*n-n-2][k-2-j]%mod*2%mod;
                ans%=mod;
            }
            ans%=mod;
        }
        
        {//左上右上或者左下右下放置
            for(register int j=1;j<=m-2&&j<=k-2;++j){
                ans+=C[m-2][j]*C[m*n-m-2][k-2-j]%mod*2%mod;
                ans%=mod;
            }
            ans%=mod;
        }


        if(k>=2){//对角线上放置
            ans+=2*C[m*n-4][k-2];
            ans%=mod;
        }

        if(k>=3){//三个角都放
            ans+=C[4][3]*C[m*n-4][k-3]%mod;
            ans%=mod;
        }

        if(k>=4){//四个角都放
            ans+=C[m*n-4][k-4];
            ans%=mod;
        }
    }
    printf("Case %d: %lld\n",++kase,ans);
}
int main(){
    scanf("%lld",&T);
    init();
    while(T--){
        work();
    }
    return 0;
}
```


---

## 作者：Katoumegumi (赞：1)

很显然~~一眼~~容斥.

由于其不合法状态的好统计性(原谅我用这么鬼畜的自创名词),所以我们会很容易想到容斥解决.状压表示下第一行不放,第一列不放,最后一行不放,最后一列不放四种情况.

根据容斥原理有**奇减偶加**,我们就可以~~随便乱搞乱搞~~,欢声笑语敲出代码.可以注意我代码中常数的优化~~(当然没开读优啦,这么小的数据读优写完正解都敲完了)~~

$code:$
```c++
#include<stdio.h>
#include<algorithm>
#define ll long long
#define mod 1000007
using namespace std;

inline int add(int a,int b){return a+b<mod?a+b:a+b-mod;};
inline int sub(int a,int b){return a-b<0?a-b+mod:a-b;}

int n,m,k,t;
int c[505][505];
int ans,tim;
int main()
{
    c[0][0]=1;
    for(int i=1;i<=501;i++)
    for(int j=0;j<=i;j++)
    c[i][j]=j?add(c[i-1][j-1],c[i-1][j]):1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        ans=0;
        for(int i=0;i<16;i++)
        {
            int heng=m,zong=n,tot=0;
            for(int j=0;j<4;j++)
            {
                if(i&(1<<j))
                {
                    if(j&1) zong--;
                    else heng--;
                    tot++;
                }
            }
            if(tot&1) ans=sub(ans,c[heng*zong][k]);
            else ans=add(ans,c[heng*zong][k]);
        }
        printf("Case %d: %d\n",++tim,ans);
    }
}
 
```

---

## 作者：roger_yrj (赞：0)

## 前言

基础容斥，建议降绿

## 题解

根据容斥原理，答案为：保留 $4$ 条边的方案数-保留 $3$ 条边的方案数+保留 $2$ 条边的方案数-保留 $1$ 条边的方案数+保留 $0$ 条边的方案数，组合数计算即可。

注意 $1e6+7=29\times 34483$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e6+7,N=510;
int n,m,k,C[N][N];
void solve(int T){
	cin>>n>>m>>k;
	cout<<"Case "<<T<<": "<<(C[n*m][k]-C[n*m-n][k]+mod-C[n*m-n][k]+mod-C[n*m-m][k]+mod-C[n*m-m][k]+mod
							+C[n*m-n-m+1][k]+C[n*m-n-m+1][k]+C[n*m-n-m+1][k]+C[n*m-n-m+1][k]+C[n*m-n-n][k]+C[n*m-m-m][k]
							-C[n*m-n-n-m+2][k]+mod-C[n*m-n-n-m+2][k]+mod-C[n*m-n-m-m+2][k]+mod-C[n*m-n-m-m+2][k]+mod+C[n*m-n-n-m-m+4][k])%mod<<"\n";
}
int main(){
	int T;cin>>T;
	C[0][0]=1;
	for(int i=1;i<=500;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	for(int i=1;i<=T;i++)solve(i);
}
```

---

## 作者：hyjdouSHEN (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/UVA11806)

## 题目分析
如果题目求的是“第一行，最后一行，第一列，最后一行都没有人”的方案数，该有多好啊！这相当于一共只有 $m-2$ 行， $n-2$ 列，答案自然是组合数。利用容斥原理，我们设满足“第一行没有人”的方案集为 $A$，最后一行没有人的方案集为 $B$，第一列与最后一列依次为 $C$ 与 $D$，全集为 $S$，则所求答案就是“在 $S$ 中但不在 $A$， $B$， $C$， $D$ 任何一个集合中”的元素个数，可以用容斥原理求解。

具体详情请看代码。

## 代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000007;
const int maxk=500;
int c[maxk+10][maxk+10];
int main()
{
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=0;i<=maxk;i++){
		c[i][0]=c[i][i]=1;    //不要忘记写边界情况 
		for(int j=1;j<i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	int T;
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++){
		int n,m,k,sum=0;
		scanf("%d%d%d",&n,&m,&k);
		for(int s=0;s<16;s++){//枚举所有16种"搭配方式" 
			int b=0,r=n,gg=m; //b用来统计集合的个数，r和c是可以放置的行列数 
			if(s&1){          //第一行没有石头，可以放石头的行数r减1 
				r--;
				b++;
			}
			if(s&2){
				r--;
				b++;
			}
			if(s&4){
				gg--;
				b++;
			}
			if(s&8){
				gg--;
				b++;
			}
			if(b&1) sum=(sum+mod-c[r*gg][k])%mod;  //奇数个条件，做减法 
			else sum=(sum+c[r*gg][k])%mod;		   //偶数个条件，做加法 
		}
		printf("Case %d: %d\n",kase,sum);
	}
	return 0;
}
```
希望这篇题解对你有帮助

---

## 作者：望眼浮云 (赞：0)

**题意：**在一个m行n列的矩形网格里放k个相同的石子，问有多少种方法？每个格子最多放一个，第一行，最后一行，第一列，最后一列都要有石子。

**思路：**第一行，最后一行，第一列，最后一列都要有石子，直接求方案数不方便，考虑把问题转换一下。先求总方案数，然后减去不合法的方案数，即先算出C(n*m,k)，不合法的方案怎么算呢？

四个集合表示：A{第一行没有放}，B{最后一行没有放}，C{第一列没有放}，D{最后一列没有放}，然后用容斥原理即可

**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=1000007;
int n,m,k,r,c,b,f[510][510],sum,i;
void zz()  //预处理组合数
{
    for(int i=0;i<500;i++)
    {
        f[i][0]=f[i][i]=1;
        for(int j=1;j<i;j++)
            f[i][j]=(f[i-1][j]+f[i-1][j-1])%p;
    }
}
int main()
{
    zz();
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++)
    {
        scanf("%d%d%d",&n,&m,&k); 
        sum=0;   //记录答案
        for(int s=0;s<16;s++) //枚举不合法的方案数的搭配方式
        {
            r=n;c=m;b=0; //b表示几个不合法集合搭配
            if(s&1) r--,b++; //第一行不放
            if(s&2) r--,b++; //最后一行不放
            if(s&4) c--,b++; //第一列不放
            if(s&8) c--,b++; //最后一列不放
            if(b%2==1) sum=(sum+p-f[r*c][k])%p;//奇数种不合法情况搭配，由容斥原理，减去
            else sum=(sum+f[r*c][k])%p; //偶数种，加上
        }
        printf("Case %d: %d\n",i,sum);
    }
}
```

---

