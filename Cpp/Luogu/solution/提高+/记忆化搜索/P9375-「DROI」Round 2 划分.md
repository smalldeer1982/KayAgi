# 「DROI」Round 2 划分

## 题目背景

与其编写苍白无力的背景，不如出更有质量的题。

## 题目描述

给定长度为 $n$ 的序列 $A$。

定义序列 $A$ 的某个子段 $[L,R]$ 的权值为: 

$$ \sum_{i=L}^{R}[\vert A_i - A_L \vert是完全平方数] \times \sum_{i=L}^{R}[\vert A_R - A_i \vert是完全平方数]$$

现在你需要将序列 $A$ **不重不漏**地划分成若干个子段，使得对于 $\forall i \in [1,n]$，长度为 $i$ 的子段有 $c_i$ 个。

在此基础上，求一种划分方案使所有子段权值和最大，输出这个最大值即可。特殊地，若不存在任意一种划分方案，则输出 `-1`。

**对题意不清楚的，可见下方说明提示。**


## 说明/提示

#### 样例解释
对于样例一，一种最优划分是分别在第二、三个数后面将序列断开。

对于样例二，一种最优划分是分别在第三、四、五、八个数后面将序列断开。


------------

#### 数据范围

**「本题采用捆绑测试」**

- $\operatorname{Subtask} 1(10\%)$：$n \leq 20$。

- $\operatorname{Subtask} 2(20\%)$：$n \leq 50,\sum_{i=1}^{n}c_i \leq 20$。

- $\operatorname{Subtask} 3(20\%)$：$n \leq 50,\forall i>5,c_i=0$。

- $\operatorname{Subtask} 4(50\%)$：无特殊限制。

对于 $100\%$ 的数据：$0 \leq c_i\leq n \leq 120,1 \leq a_i \leq 10^4$。

------------

#### 说明提示

- 我们规定，$0$ 是完全平方数。

- $[P]=1$ 当且仅当 $P$ 是真命题，否则 $[P]=0$。


## 样例 #1

### 输入

```
6
2 1 4899 4 1 4
1 1 1 0 0 0```

### 输出

```
9```

## 样例 #2

### 输入

```
10
1 1 1 2 4 3 3 3 8 8
2 1 2 0 0 0 0 0 0 0```

### 输出

```
24```

# 题解

## 作者：baoziwu2 (赞：10)

~~关于多维 dp，它还活着。~~

**观前提示：**

本题解主要是关于 $50$ 分部分的多维 dp 卡过本题的乱搞做法（理论上可以算作合法解，毕竟实际的状态数其实一点也不多），同时运用一些技巧降低代码复杂度。想学习正解的小伙伴可以去看看其他的题解。

由于个人编码的习惯，在题解前文中的变量在阐明定义后会采用相对简单的命名，在代码中会采用与不一定前文一致，但足够清晰的变量名，望各位海涵。

**正文：**

如果你不是很清楚如何对这道题进行多维 dp，那你可以先去看看[乌龟棋](https://www.luogu.com.cn/problem/P1541)这道题，本题的状态设计与状态转移和上面那道题**完全一致**。

当然在这里也会浅浅说一下：

首先有一个较为显然的结论就是不同长度的子段数不会超过 $15$ 个（因为 $\sum_{1}^{15} = 120$），也就是说我们 dp 的维数不会超过 $15$。

根据这个结论也能发现读入的 $c_i$ 中应该会有很多 $0$，所以还需要把 $c$ 重映射，留下具有实际意义的作为 dp 的维数。具体的操作为对于每一个 $c_i \neq 0$，我们令 `len[++ idx] = i, cnt[idx] = c[i]`。

同时也需要 $O(n^3)$ 预处理出所有区间的权值，其中 $v_{l, r}$ 表示 $a_l$ 到 $a_r$ 的权值。

有了这些前置条件，我们就可以愉快地设 dp 方程了，先以 $4$ 维的举个例：

设 $f_{a,b,c,d}$ 重映射后为用了 $a$ 个一号子段，$b$ 个二号子段，$c$ 个三号子段，$d$ 个四号子段的操作集合中得到的最大权值。

那么有转移方程：

$$
t = a \times len_1 + b \times len_2 + c \times len_3 + d \times len_4 
$$

$$
f_{a,b,c,d} = \max \begin{cases}
f_{a - 1, b, c, d} + v_{t - len_1 + 1, t} 
\\f_{a,b-1,c,d} + v_{t-len_2+1, t}
\\f_{a, b, c - 1, d} + v_{t-len_3+1, t}
\\f_{a,b,c,d-1} +v_{t-len_4+1, t} 
\end{cases}
$$

仿照上例即可推出 $15$ 维的方程。

当然仅仅这样是不够的，单是空间就够 MLE 好几次了，但如果我们稍加思考就会发现空间实际上严重不满，我们要做的只是动态开空间，在这里先使用 `struct` 自定义节点并用 `std::map` 作为 $f$ 数组。

于是可以得到部分~~极具观赏性~~的代码（这里只有十一层循环的原因是面向数据）。

```C++
struct node {
  int b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11;
  bool operator <(const node&t)const {
    if (b1 != t.b1) return b1 < t.b1;
    if (b2 != t.b2) return b2 < t.b2;
    if (b3 != t.b3) return b3 < t.b3;
    if (b4 != t.b4) return b4 < t.b4;
    if (b5 != t.b5) return b5 < t.b5;
    if (b6 != t.b6) return b6 < t.b6;
    if (b7 != t.b7) return b7 < t.b7;
    if (b8 != t.b8) return b8 < t.b8;
    if (b9 != t.b9) return b9 < t.b9;
    if (b10 != t.b10) return b10 < t.b10;
    return b11 < t.b11;
  }
}; // node 节点定义及重载预算符

// dp 主体
for (int a1 = 0; a1 <= cnt[1]; ++ a1)
  for (int a2 = 0; a2 <= cnt[2]; ++ a2)
    for (int a3 = 0; a3 <= cnt[3]; ++ a3)
      for (int a4 = 0; a4 <= cnt[4]; ++ a4)
        for (int a5 = 0; a5 <= cnt[5]; ++ a5)
          for (int a6 = 0; a6 <= cnt[6]; ++ a6)
            for (int a7 = 0; a7 <= cnt[7]; ++ a7)
              for (int a8 = 0; a8 <= cnt[8]; ++ a8)
                for (int a9 = 0; a9 <= cnt[9]; ++ a9)
                  for (int a10 = 0; a10 <= cnt[10]; ++ a10)
                    for (int a11 = 0; a11 <= cnt[11]; ++ a11) {
                      int& op = mp[ {a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11}];
                      int opt = a1 * len[1] + a2 * len[2] + a3 * len[3] + a4 * len[4] + a5 * len[5] + a6 * len[6] + a7 * len[7] + a8 * len[8] + a9 * len[9] + a10 * len[10] + a11 * len[11];
                      if (a1) op = max(op, mp[ {a1 - 1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11}] + v[opt - len[1] + 1][opt]);
                      if (a2) op = max(op, mp[ {a1, a2 - 1, a3, a4, a5, a6, a7, a8, a9, a10, a11}] + v[opt - len[2] + 1][opt]);
                      if (a3) op = max(op, mp[ {a1, a2, a3 - 1, a4, a5, a6, a7, a8, a9, a10, a11}] + v[opt - len[3] + 1][opt]);
                      if (a4) op = max(op, mp[ {a1, a2, a3, a4 - 1, a5, a6, a7, a8, a9, a10, a11}] + v[opt - len[4] + 1][opt]);
                      if (a5) op = max(op, mp[ {a1, a2, a3, a4, a5 - 1, a6, a7, a8, a9, a10, a11}] + v[opt - len[5] + 1][opt]);
                      if (a6) op = max(op, mp[ {a1, a2, a3, a4, a5, a6 - 1, a7, a8, a9, a10, a11}] + v[opt - len[6] + 1][opt]);
                      if (a7) op = max(op, mp[ {a1, a2, a3, a4, a5, a6, a7 - 1, a8, a9, a10, a11}] + v[opt - len[7] + 1][opt]);
                      if (a8) op = max(op, mp[ {a1, a2, a3, a4, a5, a6, a7, a8 - 1, a9, a10, a11}] + v[opt - len[8] + 1][opt]);
                      if (a9) op = max(op, mp[ {a1, a2, a3, a4, a5, a6, a7, a8, a9 - 1, a10, a11}] + v[opt - len[9] + 1][opt]);
                      if (a10) op = max(op, mp[ {a1, a2, a3, a4, a5, a6, a7, a8, a9, a10 - 1, a11}] + v[opt - len[10] + 1][opt]);
                      if (a11) op = max(op, mp[ {a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11 - 1}] + v[opt - len[11] + 1][opt]);
                    }
```

十分甚至有九分震撼，相信应该不会有人选择上面的代码的（但确实能过）。

自此本题解的算法环节结束，接下开始优化代码复杂度：

1. `node` 的定义太麻烦了，可不可以不写那么多条件分支。

    当然可以，使用 `std::vector` 可以并使用内置的小于号即可完成比较。
2. $11$ 层循环太逆天了，有无办法消除。

    没有问题，可以使用递归控制循环层数，同时赋值操作相似度很高，考虑使用一个 `std::vector` 存入所有的循环变量，稍加修改即可。

值得一提的是把上面的循环改成递归后常数会大很多，因为上面的代码相当于使用了循环展开卡常。

细节方面就是在代码实现中记得判无解情况。

**代码：**

```C++
#include <bits/stdc++.h>

using namespace std;

int const N = 5e3;

int n, idx;
int a[N], score[N][N]; // 对应 a, v 数组
map<vector<int>, int> dp; // 对应 f 数组
vector<int> loopVariables(15, 0); 
int segmentLength[N], segmentCount[N]; // 对应 len, cnt 数组

void calculateMaxScore(int step) { // dp 主体
	if (step == idx + 1) {
		int &opt = dp[loopVariables];
		int totalLength = 0;
		for (int i = 1; i <= idx; ++ i)
			totalLength += loopVariables[i] * segmentLength[i];
		for (int i = 1; i <= idx; ++ i) {
			if (loopVariables[i] == 0) continue;
			loopVariables[i] -= 1;
			opt = max(opt, dp[loopVariables] + score[totalLength - segmentLength[i] + 1][totalLength]);
			loopVariables[i] += 1;
		}
		return;
	}
	for (int i = 0; i <= segmentCount[step]; ++ i) {
		loopVariables[step] = i;
		calculateMaxScore(step + 1);
	}
}

main() {
	cin >> n;
	for (int i = 1; i <= n; ++ i) cin >> a[i];
	
	int totalLength = 0;
	for (int i = 1, x; i <= n; ++ i) {
		cin >> x;
		if (x != 0) {
			segmentLength[++ idx] = i;
			segmentCount[idx] = x;
		}
		totalLength += x * i;
	}
	
	if (totalLength != n) { // 无解判定
		puts("-1");
		return 0;
	}
	
	function<bool(int)> isPerfectSquare = [](int num) -> bool { // 定义一个局部函数
		int root = sqrt(num);
		return root * root == num;
	};
	
	for (int i = 1; i <= n; ++ i) { // 预处理
		for (int j = i; j <= n; ++ j) {
			int tempScore1 = 0, tempScore2 = 0;
			for (int k = i; k <= j; ++ k) {
				tempScore1 += isPerfectSquare(abs(a[k] - a[i]));
				tempScore2 += isPerfectSquare(abs(a[k] - a[j]));
			}
			score[i][j] = tempScore1 * tempScore2;
		}
	}
	
	calculateMaxScore(1);
	
	cout << dp[loopVariables] << endl;
	return 0;
}
```

---

## 作者：Demeanor_Roy (赞：2)

- 出题人题解。

------------

前三档分别是爆搜、状压 dp、多维 dp，直接送 $50$ 分。

考虑这样一个问题：

- 给定 $n,v$，求一个长度为 $n$ 的序列 $s$，满足 $\sum_{i=1}^{n}s_i \times i = v$，且 $\prod_{i=1}^{n}(s_i+1)$ 最大。

不难发现这个最大值即为本题状态数，让我们推推式子确定一下：

$$\prod_{i=1}^{n}(s_i+1)$$

$$= \frac{1}{n!}\prod_{i=1}^{n}(is_i+i)$$

$$\leq \frac{1}{n!}(\frac{\sum_{i=1}^{n}(is_i+i)}{n})^n$$

$$= \frac{1}{n!}(\frac{v+\frac{n(n+1)}{2}}{n})^n$$

$$= \frac{1}{n!}(\frac{v}{n}+\frac{(n+1)}{2})^n$$

然后你就会发现代入 $n=v=120$ 是 $10^{15}$ 数量级的，~~也就是上面那个式子其实没用。~~

但这是因为上式求的是实数范围最大值，如果你有着惊人的直觉，就会发现其实在整数范围内远远取不到最大值。

考虑使用**启发式搜索**搜出整数范围内的最大值，你就会发现真正的状态数只有 $70$ 多万个。于是可以构造一个 hash 将每个状态对应一个数，然后暴力记搜即可。时间复杂度 $O(Sn)$。其中 $S$ 是状态数。（注意使用 STL 的 hash 函数应该是会被卡掉的）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=130,MAXN=1e6+10;
int n,tot,f[MAXN],A[N],suc[N],v[N][N];
struct node{short c[N];}lim;
inline bool check(int x){int y=sqrt(x);return y*y==x;}
inline int vary(node now){int id=0;for(int i=1;i<=n;i++) id+=now.c[i]*suc[i+1];return id;}
inline int dp(node x)
{
	int now=vary(x);
	if(~f[now]) return f[now];
	int sum=0;
	for(int i=1;i<=n;i++) sum+=x.c[i]*i;
	for(int i=1;i<=n;i++)
	{
		if(!x.c[i]) continue;
		node y=x;y.c[i]--;
		f[now]=max(f[now],dp(y)+v[sum-i+1][sum]);	
	}	
	return f[now];
}
int main()
{
	memset(f,-1,sizeof f);
	scanf("%d",&n);
	f[0]=0;suc[n+1]=1;
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=1;i<=n;i++) scanf("%hd",&lim.c[i]),tot+=i*lim.c[i];
	for(int i=n;i>=1;i--) suc[i]=suc[i+1]*(lim.c[i]+1);
	if(tot!=n) return puts("-1"),0;
	for(int l=1;l<=n;l++)
		for(int r=l;r<=n;r++)
		{
			int sum=0;
			for(int k=l;k<=r;k++) if(check(abs(A[l]-A[k])))	sum++;
			for(int k=l;k<=r;k++) if(check(abs(A[r]-A[k]))) v[l][r]++;
			v[l][r]*=sum;
		}
	printf("%d",dp(lim));
	return 0;	
}
```







---

## 作者：gcx12012 (赞：1)

#### 题意
给定 $n$ 个数的数列 $a_i$ 和 $c_i$，求一种划分数组 $a$ 的方案，使得划分后的数组的权值和最大并且满足长度为 $i$ 的段有 $c_i$ 个。
#### Solution
显然当 $\sum_{i=1}^n i\times c_i$ 不等于 $n$ 时是不存在合法方案的，特判掉这个以后考虑存在合法方案时的做法。

Sub 1 的做法不必多说，直接爆搜都能过。

注意到 Sub 2 的 $\sum_{i=1}^n c_i \le 20$，我们知道它的状态数很少，于是爆搜同样能过。 

Sub 3 显然是一个 $\le 5$ 维的 dp，做法跟  P1541 [NOIP2010 提高组] 乌龟棋几乎一样。
```cpp
int f1[21][21][21][21][21],f2[51][16][16][16][16];
int P(int i1,int i2,int i3,int i4,int i5){
	return 1+(c[1]-i1)+2*(c[2]-i2)+3*(c[3]-i3)+4*(c[4]-i4)+5*(c[5]-i5);
}
void sol(){
	if(c[1]<=20){
		Rof(i1,c[1],0){
			Rof(i2,c[2],0){
				Rof(i3,c[3],0){
					Rof(i4,c[4],0){
						Rof(i5,c[5],0){
							if(i1) f1[i1-1][i2][i3][i4][i5]=
							max(f1[i1-1][i2][i3][i4][i5],
							f1[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1-1,i2,i3,i4,i5)-1]);
							if(i2) f1[i1][i2-1][i3][i4][i5]=
							max(f1[i1][i2-1][i3][i4][i5],
							f1[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1,i2-1,i3,i4,i5)-1]);
							if(i3) f1[i1][i2][i3-1][i4][i5]=
							max(f1[i1][i2][i3-1][i4][i5],
							f1[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1,i2,i3-1,i4,i5)-1]);
							if(i4) f1[i1][i2][i3][i4-1][i5]=
							max(f1[i1][i2][i3][i4-1][i5],
							f1[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1,i2,i3,i4-1,i5)-1]);
							if(i5) f1[i1][i2][i3][i4][i5-1]=
							max(f1[i1][i2][i3][i4][i5-1],
							f1[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1,i2,i3,i4,i5-1)-1]);
						}
					}
				}
			}
		}
		ans=f1[0][0][0][0][0];
	}else{
		Rof(i1,c[1],0){
			Rof(i2,c[2],0){
				Rof(i3,c[3],0){
					Rof(i4,c[4],0){
						Rof(i5,c[5],0){
							if(i1) f2[i1-1][i2][i3][i4][i5]=
							max(f2[i1-1][i2][i3][i4][i5],
							f2[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1-1,i2,i3,i4,i5)-1]);
							if(i2) f2[i1][i2-1][i3][i4][i5]=
							max(f2[i1][i2-1][i3][i4][i5],
							f2[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1,i2-1,i3,i4,i5)-1]);
							if(i3) f2[i1][i2][i3-1][i4][i5]=
							max(f2[i1][i2][i3-1][i4][i5],
							f2[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1,i2,i3-1,i4,i5)-1]);
							if(i4) f2[i1][i2][i3][i4-1][i5]=
							max(f2[i1][i2][i3][i4-1][i5],
							f2[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1,i2,i3,i4-1,i5)-1]);
							if(i5) f2[i1][i2][i3][i4][i5-1]=
							max(f2[i1][i2][i3][i4][i5-1],
							f2[i1][i2][i3][i4][i5]+jz[P(i1,i2,i3,i4,i5)][P(i1,i2,i3,i4,i5-1)-1]);
						}
					}
				}
			}
		}
		ans=f2[0][0][0][0][0];
	}
}
```
赛时为了省空间写成了这样子，但是后来发现没必要。

接下来我们考虑正解。

我们发现状态数其实并不多，大概是 $\prod_{i=1}^n (c_i+1)$ 个，不超过 $10^6$ 个。

但是它的维数太多，数组不好开，怎么办呢？

这里提供一个压维的线性 dp 写法。

把它比作一个 $n+1$ 位的数，每一位是一个 $c_i+1$ 进制数。

然后我们就可以愉快的 AC 这道压维 dp 了。

不懂的可以看看代码实现。
```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define N 150
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rof(i,a,b) for(int i=a;i>=b;i--)
#define pb push_back

using namespace std;
int a[N],c[N],jz[N][N],mc[N];
int n,sum,ans=0;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();} 
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int f[1000010];
int calc(int x){
	int s=1;
	For(j,1,n) s+=j*(c[j]-(x%mc[j-1])/mc[j]);
	return s;
}
void sol2(){
	Rof(i,mc[0]-1,0){
		int now=calc(i);
		For(j,1,n){
			if(i%mc[j-1]>=mc[j]) f[i-mc[j]]=max(f[i-mc[j]],f[i]+jz[now][now+j-1]);
		}
	}
	ans=f[0];
}

int main()
{
	n=read();
	For(i,1,n) a[i]=read();
	For(i,1,n) c[i]=read(),sum+=i*c[i];
	if(sum!=n){
		cout<<"-1";
		return 0;
	}
	sum=0;
	For(i,1,n) sum+=c[i];
	mc[n]=1;
	Rof(i,n-1,0) mc[i]=mc[i+1]*(c[i+1]+1);
	//For(i,0,n) cout<<mc[i]<<' ';
	//cout<<endl;
	For(l,1,n){
		For(r,l,n){
			int s1=0,s2=0;
			For(i,l,r){
				int now=abs(a[l]-a[i]);
				int e=sqrt(now);
				if(e*e==now) s1++;
			}
			For(i,l,r){
				int now=abs(a[r]-a[i]);
				int e=sqrt(now);
				if(e*e==now) s2++;
			}
			jz[l][r]=s1*s2;
		}
	}
	sol2();
	cout<<ans<<endl;
	return 0;
}                          
```


---

## 作者：caohan (赞：1)

# 声明 and 致谢

本题解 hash 的思路来源于

   [Demeanor_Roy](https://www.luogu.com.cn/user/297806)       






特此致谢

# 思路

## 无解

 $\sum_{1}^{n} c_i \times i \ne n$      的时候，绝对没有方案，直接抬走。

## 有解

肯定想到暴力：先进行区间权值的预处理，然后大法师。

大法师的策略是：

在确认了剩下的区间和最后未分的一段的长度后，对当前剩余的可操作的区间的长度进行遍历，如果这个长度的区间还有，那么就使用一个该长度的区间，计算一下去掉这个区间后最大取值是多少，再求加上该区间对应的取值的结果之后的值，用这个值和原来不理会的结果取最大即可。

能吃到一半的分。

于是试图优化，可以考虑记忆化搜索，但真的按照数据划分，可能会很麻烦，空间照样爆炸。

便试图整合这些数据：使用状态对应。

本质是用运算将多个值变成一个值。但是因为算法本身的特性，会有小概率的重复，即多个不同状态指向同一个值，这时应用多重判定减少这个概率。

~~这里其实不用~~

状态对应式子就是用那位大神的。

# 代码

```cpp
//前炎：照样是dfs，但是有了 hash
#include<bits/stdc++.h>
using namespace std;
const int N=130,MAXN=1000000+10;
int n,tot,f[1000000+10],a[130],suc[130],v[130][130];
struct node
{
	short c[130];
}lim;//用结构体封装，方便在dfs的时候去对应状态 
inline bool check(int x)
{
	int y=sqrt(x);//开根后下取整，令非整数平方根损失精度 
	return y*y==x;//没损失精度就是合格的平方数 
}//检查是否为平方数的函数 
inline int vary(node now)
{
	int id=0;
	for(int i=1;i<=n;i++)
	{
		id+=now.c[i]*suc[i+1];//把这个式子的原型乘起来，求和
	}
	return id;
}//状态对应的核心 
inline int dp(node x)
{
	int now=vary(x);
	if(~f[now])
	{
		return f[now];
	}
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		sum+=x.c[i]*i;
	}//计算当前剩余的长度 
	for(int i=1;i<=n;i++)
	{
		if(!x.c[i])
		{
			continue;
		}//没得可分就不分了 
		node y=x;
		y.c[i]--;//给下一层筹备好状态 
		f[now]=max(f[now]/*原值大保留原值*/,dp(y)/*扣掉这个在最后的选中区间后剩下的值*/+v[sum-i+1][sum]/*这个区间的取值*/);	
	}	
	return f[now];//返回 
}
int main()
{
	memset(f,-1,sizeof f);
	scanf("%d",&n);
	f[0]=0;suc[n+1]=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%hd",&lim.c[i]);
		tot+=i*lim.c[i];
	}//读入，记和 
	if(tot!=n)
	{
		puts("-1");
		return 0;
	}//分段的和不够，那就没法拼了 
	for(int i=n;i>=1;i--)
	{
		suc[i]=suc[i+1]*(lim.c[i]+1);
	}//预处理
	for(int l=1;l<=n;l++)
	{
		for(int r=l;r<=n;r++)
		{//枚举区间 
			int sum=0;
			for(int k=l;k<=r;k++)
			{
				if(check(abs(a[l]-a[k])))
				{
					sum++;//有一组平方数 
				}
			}
			for(int k=l;k<=r;k++)
			{
				if(check(abs(a[r]-a[k]))) 
				{
					v[l][r]++;//有一组平方数 
				}
			}
			v[l][r]*=sum;//算出该区间平方数的组数（权值） 
		}
	}
	printf("%d",dp(lim));//计算最终的值 
	return 0;	
}
```

---

