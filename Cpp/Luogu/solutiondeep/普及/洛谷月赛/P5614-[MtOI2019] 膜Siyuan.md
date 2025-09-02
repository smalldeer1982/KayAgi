# 题目信息

# [MtOI2019] 膜Siyuan

## 题目背景

你强归你强，$\mathsf S\mathsf{\color{red} iyuan}$ 比你强。——$\mathsf S \mathsf{\color{red} iyuan}$

disangan233 最近发现了一款 OIer 们的游戏：[膜 $\color{black} \mathsf S \mathsf{\color{red} iyuan}$](https://lmoliver.github.io/mosiyuan/index.html)。

他被里面的「真理 IV」所困惑，于是他找到了你寻求帮助。


## 题目描述

给你 $1$ 个正整数 $M$，$n(n\leq 5)$ 个正整数 $3$ 元组 $\{a_i,b_i,c_i\}(a_i,b_i,c_i\leq M\leq 2000)$，请你求出所有满足

$$
\forall i\leq n ,s.t.~|a_i-x|\oplus |b_i-y|\oplus |c_i-z| = 9
$$

的**有序**正整数 $3$ 元组 $\{x,y,z\}(x,y,z \leq M)$的个数。

其中，$\forall$ 表示 "对于所有"，$s.t.$ 表示 "使得"，$A \oplus B \oplus C$ 表示 $A,B,C$ 的异或和。

对于 C++，`A^B^C` 或 `A xor B xor C` 即为 $A \oplus B \oplus C$ 的答案 。

这里提供一份模板：

```cpp
if ((a ^ b ^ c) == 9) 
{
	Your code here...
}
```

对于 $2$ 个有序 $3$ 元组 $A,B$，如果 $x_A \not =x_B$ 或 $y_A \not =y_B$ 或 $z_A \not =z_B$，$A,B$ 即被视为是不同的。


## 说明/提示

#### 样例解释 $1$

所有满足条件的 $\{x,y,z\}$ 有： 

$\{88,88,120\}$，$\{88,104,104\}$，$\{120,120,120\}$ 和 $\{120,136,104\}$。

共 $4$ 个。

### 子任务

对于 $10\%$ 的数据，保证与样例完全一致。

对于 $60\%$ 的数据，保证 $M\leq 200$。

对于所有数据，保证 $a_i,b_i,c_i\leq M\leq 2000$，$n\leq 5$。


### 题目来源

[MtOI2019 Extra Round](https://www.luogu.org/contest/22614) T2

出题人：disangan233

验题人：Studying Father


## 样例 #1

### 输入

```
5 200
21 84 198
38 47 102
44 47 132 
63 150 166
76 79 132```

### 输出

```
4```

# AI分析结果

### 综合分析与结论

本题的核心是求解满足特定异或条件的三元组 `{x, y, z}`。大多数题解都采用了类似的思路：通过枚举 `x` 和 `y`，利用异或的性质推导出 `z` 的可能值，再通过验证这些值是否满足所有给定的三元组条件。这种思路将时间复杂度从 `O(M^3)` 优化到 `O(M^2)`，显著提升了效率。

#### 关键思路与技巧：
1. **异或的性质**：利用异或的自反性和交换律，推导出 `|c_i - z|` 的值，从而减少枚举的维度。
2. **绝对值方程的解**：通过 `|c_i - z| = p` 推导出 `z` 的两个可能值，并验证其合法性。
3. **去重与边界处理**：当 `z` 的两个解相同时，避免重复计数，并确保 `z` 的值在 `[1, M]` 范围内。

#### 可拓展之处：
- **类似问题**：类似的问题可以通过减少枚举维度来优化，例如通过数学性质推导出某些变量的值。
- **异或相关题目**：异或的性质在算法竞赛中经常出现，掌握其性质可以帮助解决更多类似问题。

### 推荐题目：
1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469) - 考察异或的性质。
2. [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811) - 涉及数学推导与优化。
3. [P3390 【模板】矩阵快速幂](https://www.luogu.com.cn/problem/P3390) - 通过数学性质优化算法。

### 所选题解

#### 1. **作者：StudyingFather (5星)**
- **关键亮点**：思路清晰，代码简洁，优化到位。通过枚举 `x` 和 `y`，利用异或性质推导出 `z`，并处理了去重和边界条件。
- **个人心得**：强调了异或的优先级问题，提醒了在实现时需要注意的细节。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
 int a,b,c;
}p[15];
int main()
{
 int n,m,ans=0;
 scanf("%d%d",&n,&m);
 for(int i=1;i<=n;i++)
  scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].c);
 for(int i=1;i<=m;i++)
  for(int j=1;j<=m;j++)
  {
   int tmp=abs(i-p[1].a)^abs(j-p[1].b)^9;
   int res1=p[1].c+tmp,res2=p[1].c-tmp;
   int flag1=(res1>0&&res1<=m),flag2=(res2>0&&res2<=m);
   for(int k=2;k<=n;k++)
   {
    if((abs(i-p[k].a)^abs(j-p[k].b)^abs(res1-p[k].c))!=9)flag1=false;
    if((abs(i-p[k].a)^abs(j-p[k].b)^abs(res2-p[k].c))!=9)flag2=false;
   }
   if(res1==res2)flag2=false;
   ans+=flag1+flag2;
  }
 printf("%d\n",ans);
 return 0;
}
```

#### 2. **作者：Hexarhy (4星)**
- **关键亮点**：详细解释了异或的性质，并通过数学推导优化了算法。代码实现清晰，处理了去重和边界条件。
- **个人心得**：强调了异或的自反性和交换律，帮助理解推导过程。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN=15;
int n,m;
int a[MAXN],b[MAXN],c[MAXN];
int ans;
void input()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	 cin>>a[i]>>b[i]>>c[i];
}
void solve()
{
	for(int x=1;x<=m;x++)
	 for(int y=1;y<=m;y++)
	 {
		 const int t=abs(x-a[1])^abs(y-b[1])^9;
		 const int z1=c[1]+t,z2=c[1]-t;
		 bool f1=(0<z1 && z1<=m),f2=(0<z2 && z2<=m);
		 for(int i=2;i<=n;i++)
		 {
			 if((abs(x-a[i])^abs(y-b[i])^abs(z1-c[i]))!=9)
			  f1=false;
			 if((abs(x-a[i])^abs(y-b[i])^abs(z2-c[i]))!=9)
 			  f2=false;
		 }
		 ans=ans+f1+f2;
         if(z1==z2)
          ans--;
	 }
}
int main()
{
	input();
	solve();
	cout<<ans<<endl;
	return 0;
}
```

#### 3. **作者：Crab_Dave (4星)**
- **关键亮点**：通过枚举 `x` 和 `y`，推导出 `z` 的值，并验证其合法性。代码实现简洁，处理了去重和边界条件。
- **个人心得**：提醒了在实现时需要注意的细节，如异或的优先级问题。

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,M,fl;
int u[7],v[7],w[7],ans;
int main()
{
	scanf("%d%d",&n,&M);
	for(register int i=1;i<=n;i++)
		scanf("%d%d%d",&u[i],&v[i],&w[i]);
	for(register int x=1;x<=M;x++)
		for(register int y=1;y<=M;y++)
		{
			int t=abs(u[1]-x)^abs(v[1]-y)^9;
			int z=w[1]-t;
			if(z>0)
			{
				fl=0;
				for(register int i=2;i<=n;i++)
					if(abs(u[i]-x)^abs(v[i]-y)^abs(w[i]-z)^9){fl=1;}
				if(!fl)ans++;
			}
			if(t)
			{
				z=w[1]+t;
				if(z<=M)
				{
					fl=0;
					for(register int i=2;i<=n;i++)
						if(abs(u[i]-x)^abs(v[i]-y)^abs(w[i]-z)^9){fl=1;}
					if(!fl)ans++;
				}
			}
		}
	printf("%d\n",ans);
	return 0;
}
```

### 总结
以上题解均通过枚举 `x` 和 `y`，利用异或的性质推导出 `z` 的值，并验证其合法性。StudyingFather 的题解最为简洁清晰，Hexarhy 的题解则详细解释了异或的性质，Crab_Dave 的题解则提供了简洁的实现。这些题解都值得参考，尤其是对于异或性质的理解和优化思路的应用。

---
处理用时：61.88秒