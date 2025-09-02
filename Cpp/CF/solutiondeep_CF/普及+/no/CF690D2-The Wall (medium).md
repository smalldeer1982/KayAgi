# 题目信息

# The Wall (medium)

## 题目描述

Heidi the Cow is aghast: cracks in the northern Wall? Zombies gathering outside, forming groups, preparing their assault? This must not happen! Quickly, she fetches her HC $ ^{2} $ (Handbook of Crazy Constructions) and looks for the right chapter:

How to build a wall:

1. Take a set of bricks.
2. Select one of the possible wall designs. Computing the number of possible designs is left as an exercise to the reader.
3. Place bricks on top of each other, according to the chosen design.

This seems easy enough. But Heidi is a Coding Cow, not a Constructing Cow. Her mind keeps coming back to point 2b. Despite the imminent danger of a zombie onslaught, she wonders just how many possible walls she could build with up to $ n $ bricks.

A wall is a set of wall segments as defined in the easy version. How many different walls can be constructed such that the wall consists of at least $ 1 $ and at most $ n $ bricks? Two walls are different if there exist a column $ c $ and a row $ r $ such that one wall has a brick in this spot, and the other does not.

Along with $ n $ , you will be given $ C $ , the width of the wall (as defined in the easy version). Return the number of different walls modulo $ 10^{6}+3 $ .

## 说明/提示

The number $ 10^{6}+3 $ is prime.

In the second sample case, the five walls are:

```
<pre class="verbatim"><br></br>            B        B<br></br>B., .B, BB, B., and .B<br></br>
```

In the third sample case, the nine walls are the five as in the second sample case and in addition the following four:

```
<pre class="verbatim"><br></br>B    B<br></br>B    B  B        B<br></br>B., .B, BB, and BB<br></br>
```

## 样例 #1

### 输入

```
5 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 2
```

### 输出

```
9
```

## 样例 #4

### 输入

```
11 5
```

### 输出

```
4367
```

## 样例 #5

### 输入

```
37 63
```

### 输出

```
230574
```

# AI分析结果

### 题目内容
# 城墙（中等）

## 题目描述
奶牛海蒂惊恐万分：北方城墙出现裂缝？僵尸在城外集结，成群结队，准备发动攻击？这绝不能发生！她迅速拿起她的《疯狂建筑手册》（$HC ^{2}$），寻找合适的章节：

如何建造城墙：
1. 准备一组砖块。
2. 从可能的城墙设计中选择一种。计算可能的设计数量留作读者练习。
3. 根据所选设计将砖块一块块叠放。

这看起来相当简单。但海蒂是一只编程奶牛，并非建筑奶牛。她的思绪总是回到第2点。尽管僵尸即将来袭，她还是想知道用至多$n$块砖能建造多少种不同的城墙。

城墙由简单版本中定义的城墙段组成。能建造出多少种不同的城墙，使得城墙由至少$1$块且至多$n$块砖组成？如果存在某一列$c$和某一行$r$，使得一面城墙在该位置有砖，而另一面没有，则这两面城墙不同。

除了$n$，你还会得到$C$，即城墙的宽度（如简单版本中所定义）。返回不同城墙的数量对$10^{6}+3$取模的结果。

## 说明/提示
数字$10^{6}+3$是质数。

在第二个样例中，五种城墙如下：
```
<pre class="verbatim"><br></br>            B        B<br></br>B.,.B, BB, B., and.B<br></br>
```

在第三个样例中，九种城墙是第二个样例中的五种，另外还有以下四种：
```
<pre class="verbatim"><br></br>B    B<br></br>B    B  B        B<br></br>B.,.B, BB, and BB<br></br>
```

## 样例 #1
### 输入
```
5 1
```
### 输出
```
5
```

## 样例 #2
### 输入
```
2 2
```
### 输出
```
5
```

## 样例 #3
### 输入
```
3 2
```
### 输出
```
9
```

## 样例 #4
### 输入
```
11 5
```
### 输出
```
4367
```

## 样例 #5
### 输入
```
37 63
```
### 输出
```
230574
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是将原问题转化为组合数学问题，利用插板法来计算方案数。主要难点在于如何将用至多$n$块砖在宽度为$C$的区域建造城墙的问题，转化为熟悉的组合问题模型，并处理好边界条件（如不能一块砖都不放）。各题解都通过不同方式对问题进行了转化，最终得出答案为${{n + C} \choose {C}} - 1$，在实现上都涉及到组合数的计算以及取模运算，部分题解还使用了Lucas定理优化组合数计算。

### 所选的题解
- **作者：_ZHONGZIJIE0608_**  星级：4星
    - **关键亮点**：将问题转化为求$x_1+x_2+\cdots+x_c=k,k \in [1,n]$的非负整数解个数，通过引入变量$x_{c + 1}$，利用插板法得出答案公式，代码实现中使用Lucas定理优化组合数计算，效率较高。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int p=1e6+3;
int farc[N];
inline int Pow(int a,int b,int p){int s=1ll;while(b){if(b&1ll)s=s*a%p;a=a*a%p;b>>=1ll;}return s%p;}
inline int C(int n,int m,int p){if(m>n)return 0;return farc[n]*Pow(farc[m],p-2ll,p)%p*Pow(farc[n-m],p-2ll,p)%p;}
inline int Lucas(int n,int m,int p){if(!m)return 1ll;return 1ll*Lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	int n,m;cin>>n>>m;farc[0]=1;
	for(int i=1;i<=p;++i)farc[i]=(farc[i-1]*i)%p;
	cout<<(Lucas(n+m,m,p)-1+p)%p<<'\n';
	return 0;
}
```
核心实现思想：通过预处理阶乘数组`farc`，利用快速幂函数`Pow`计算逆元，进而通过`C`函数计算组合数，`Lucas`函数利用Lucas定理优化大组合数计算，最终得出答案。

- **作者：lfxxx**  星级：4星
    - **关键亮点**：巧妙地通过改变放球的盒子数量和球的总数，将原问题等价转化为经典的组合问题，思路清晰简洁。
    - **核心代码（无，思路阐述为主）**：
思路为：先考虑放入$C + 1$个盒子再丢掉最后一个盒子，需要把$n$个球放完；然后通过放$n + C + 1$个球放入$C + 1$个盒子，最后每个盒子丢掉一个球，等价于原问题，得出答案为${n + C \choose C}-1$。

- **作者：minecraft_herobrine**  星级：4星
    - **关键亮点**：详细地将原问题逐步转化为熟悉的组合问题，从矩形分解到自然数组合，再到装球问题，逻辑清晰，代码实现完整且注释详细。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e6+3;
ll qpow(ll base,ll p)
{
	ll res=1;
	while(p>0)
	{
		if(p&1) res=(res*base)%mod;
		base=(base*base)%mod;
		p>>=1;
	}
	return res;
}
ll C(ll n,ll m)
{
	m=min(m,n-m);
	ll a=1,b=1,i;
	for(i=1;i<=m;i++)
	{
		a=a*i%mod;
		b=b*(n+1-i)%mod;
	}
	a=qpow(a,mod-2);
	return (a*b)%mod;
}
int main()
{
	ll n,m;
	scanf("%lld %lld",&n,&m);
	printf("%lld",(C(n+m,m)+mod-1)%mod);
	return 0;
}
```
核心实现思想：通过快速幂函数`qpow`计算逆元，在`C`函数中利用逆元计算组合数，最终在`main`函数中得出答案。

### 最优关键思路或技巧
将实际问题转化为经典的组合数学模型，如将用砖建城墙问题转化为球放入盒子的问题，利用插板法求解。在计算组合数时，使用快速幂计算逆元来处理取模运算，部分题解还利用Lucas定理优化大组合数的计算。

### 可拓展之处
同类型题通常围绕组合数学的模型转化，如将一些实际场景问题转化为球盒模型、不定方程非负整数解模型等。类似算法套路是遇到此类问题，尝试建立数学模型，利用组合数、排列数等知识求解，同时注意取模运算和边界条件处理。

### 洛谷相似题目
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：涉及二项式定理和组合数计算。
- [P2822 [NOIP2016 提高组] 组合数问题](https://www.luogu.com.cn/problem/P2822)：主要考察组合数性质及取模运算。
- [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)：专注于Lucas定理的应用。 

---
处理用时：81.73秒