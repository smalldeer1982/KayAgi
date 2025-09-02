# 题目信息

# [WFOI - 01] 硬币（coin）

## 题目描述

你面前有一排 $n$ **堆**硬币排成一线，**同一堆硬币**的面值相同，记第 $i$ 堆硬币的面值为 $a_i$。而**每堆硬币**的数量都相同，记为 $x$。

现在你知道每第 $i$ 堆硬币的面值 $a_i$，你需要确定一个**正整数** $x$，使得**每堆硬币的总金额的**方差最接近于一个**正整数** $k$。

两数 **“最接近”** 的定义：两数之差的绝对值最小。

方差定义：方差 $s ^ 2 = \cfrac{(a_1 - \bar x)^2 + (a_2 - \bar x) ^ 2 + \cdots + (a_n - \bar x) ^ 2}{n}$，其中 $\bar x$ 代表 $x$ 的平均值。

## 说明/提示


**【样例 $\#1$ 解释】**

  当 $x=3$ 时，第 $i$ 个堆的硬币金额为 $3\times a_i$，这些硬币堆的金额分别为 $21,6,12,18,9,21,30$，可以计算得这些硬币金额的方差约为 $58.78$，可以证明当 $x=3$ 时方差最接近 $47$。

**【样例 $\#2$ 解释】**

  可以发现，无论 $x$ 的取值，方差都会为 $0$，所以输出 `No answer!`。







**【数据规模】**

**本题采用 Subtask 捆绑测试。**

Subtask 编号 | $n,\forall a_i\le$ | $k\le$ | $\footnotesize\texttt{测试点数目}$ |
:-: | :-: | :-: | :-:
**Subtask #0 $(20\texttt{pts})$** | $10^3$ | $10^9$| $6$ |
**Subtask #1 $(25\texttt{pts})$** | $10^5$ | $10^{12}$| $6$ |
**Subtask #2 $(25\texttt{pts})$** | $10^5$ | $10^{18}$| $6$ |
**Subtask #3 $(30\texttt{pts})$** | $7\times10^6$ | $3\times 10^{18}$| $6$ |

对于 $100\%$ 的数据，$1\le n,\forall a_i\le7\times10^6$，$1\le k\le3\times10^{18}$。记原来 $a$ 数组的方差为 $p$，则数据满足 $p=0$ 或 $p\in[0.25,\ 2^{63}-1]$ 。





**【提示】**

  本题读入量较大，请使用合适的读入方式。此处推荐[快速读入模板](https://www.luogu.com.cn/paste/bcfvgxr7)，对于 $\texttt{C/C++}$ 语言，你也可以使用 `scanf` 语句完成读入。
  
  为避免卡精度，建议 `C/C++` 选手使用 $\texttt{double}$ 类型，并不建议使用 `eps`。

## 样例 #1

### 输入

```
7 47
7 2 4 6 3 7 10```

### 输出

```
3```

## 样例 #2

### 输入

```
4 4
4 4 4 4```

### 输出

```
No answer!```

# AI分析结果

• 综合分析与结论：所有题解均先推导得出当数列每个数乘\(x\)时，方差变为原方差乘\(x^2\)这一关键结论。基于此，先计算原数列方差，若为\(0\)则输出 “No answer!” ；否则，计算\(\sqrt{k / s^2}\) ，由于\(x\)需为正整数，所以答案为\(\lfloor\sqrt{k / s^2}\rfloor\) 或\(\lceil\sqrt{k / s^2}\rceil\) ，通过比较这两个值与\(k\)的接近程度确定最终答案。各题解思路差异不大，主要区别在于细节处理和代码实现。

所选的题解：
  - 作者：Elgo87 (5星)
    - 关键亮点：思路阐述极为清晰，先引入前置知识推导数列乘\(x\)时方差的变化规律，再详细说明求解过程及不同情况的处理方式，代码注释详尽。
    - 个人心得：无
    - 重点代码核心实现思想：先读入数据，计算原数列方差，若方差为\(0\)输出 “No answer!” ；否则计算\(\lfloor\sqrt{k / s^2}\rfloor\) 和\(\lceil\sqrt{k / s^2}\rceil\) ，根据与\(k\)的接近程度输出答案。
```cpp
#include<bits/stdc++.h>
#define N 10001001
using namespace std;
typedef double db;
typedef long long ll; 
inline void read(ll &ret)  
{
	ret=0;char c=getchar();bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
ll n,k;
ll a[N];
signed main()
{
	read(n);
	read(k);
	db now=0.0;
	for(int i=1;i<=n;i++)
		read(a[i]),now+=1.0*a[i];
	now/=n;
	db sum=0.0;
	for(int i=1;i<=n;i++)
		sum+=(now-1.0*a[i])*(now-1.0*a[i]);
	sum/=n;   
	if(fabs(sum)<1e-9)  
	{
		puts("No answer!");
		exit(0);
	}
	ll x=floor(sqrt(k/sum)),y=ceil(sqrt(k/sum));  
	if(!x)  
	{
		printf("%lld\n",y);
		return 0;
	}
	if(fabs(x*x*1.0*sum-k)<=fabs(y*y*1.0*sum-k))  
		printf("%lld\n",x);
	else
		printf("%lld\n",y);
	return 0;
}
```
  - 作者：Inkyo (4星)
    - 关键亮点：在阐述方差变化规律及解题思路时，结合方差公式详细推导，逻辑连贯，代码简洁明了，注释恰当。
    - 个人心得：在处理答案为\(0\)的情况时遇到困难，强调答案必须为正整数这一要点。
    - 重点代码核心实现思想：读入数据并计算原数列平均数与方差，若方差为\(0\)输出 “No answer!” ；否则计算\(\lfloor\sqrt{k / s^2}\rfloor\) ，比较\(k - ans^2s^2\) 与\((ans + 1)^2s^2 - k\) 的大小确定答案，同时处理\(ans = 0\) 的情况。
```cpp
#include<bits/stdc++.h>
#define maxn 7000005
using namespace std;

int n;
int a[maxn];
long long k, ans;
double aver, s; 

inline int read()
{
	int now = 0, nev = 1; char c = getchar();
	while(c < '0' || c > '9') { if(c == '-') nev = -1; c = getchar();}
	while(c >= '0' && c <= '9') { now = (now << 1) + (now << 3) + (c & 15); c = getchar(); }
	return now * nev;
}

int main()
{
	scanf("%d%lld", &n, &k);
	for(register int i = 1; i <= n; i ++) 
	{
		a[i] = read();
		aver += a[i];
	}
	aver /= n;
	
	for(register int i = 1; i <= n; i ++) 
		s += ((a[i] - aver) * (a[i] - aver));
	s /= n;
	
	if(s == 0) 
	{
		printf("No answer!");
		return 0;
	}
	
	ans = sqrt(k / s);
	double x = abs(k - ans * ans * s), y = abs(k - (ans + 1) * (ans + 1) * s);
	if(x > y) ans ++;
	if(ans == 0) ans ++; 
	
	printf("%lld", ans);
	
	return 0;
} 
```
  - 作者：Eason_AC (4星)
    - 关键亮点：先严谨证明数列乘\(x\)后方差变为\(x^2\cdot p\)这一结论，再据此给出详细解题思路，包括如何确定两个候选答案及根据条件选择最终答案，代码采用代码块形式，结构清晰。
    - 个人心得：被精度问题困扰约40分钟，强调注意数据类型选择。
    - 重点代码核心实现思想：读入数据，计算原数列方差，若方差为\(0\)输出 “No answer!” ；否则计算\(\lfloor\sqrt{k / p}\rfloor\) 和\(\lceil\sqrt{k / p}\rceil\) ，根据与\(k\)的接近程度及正整数要求输出答案。
```cpp
namespace Solution {
#define int ll 
	const int N = 7e6 + 7;
	int n, k, a[N];
	
	iv Main() {
		read(n, k); F(int, i, 1, n) read(a[i]);
		double ave = 0.0, ans = 0.0;
		F(int, i, 1, n) ave += a[i]; ave /= n;
		F(int, i, 1, n) ans += (a[i] - ave) * (a[i] - ave); ans /= n;
		if(ans == 0.0) {puts("No answer!"); return;}
		double t = sqrt(k * 1. / ans); 
		int k1 = (int)t, k2 = k1 + 1;
		if(!k1 || fabs(k1 * k1 * ans - k) > fabs(k2 * k2 * ans - k)) write(k2);
		else write(k1);
		return;
	}
#undef int
}
```
• 最优关键思路或技巧：通过数学推导得出数列每个数乘\(x\)时方差的变化规律，将问题转化为求与\(\sqrt{k / s^2}\) 最接近的正整数，简化问题求解过程。同时，注意数据读入优化、数据类型选择以避免精度问题和答案为\(0\)等细节处理。
• 拓展：此类题目属于数学规律推导结合数值求解类型，类似套路为通过分析题目条件推导关键数学关系，将复杂问题简单化。比如在一些涉及数据变换与统计量计算的题目中，可通过推导变换前后统计量（如均值、方差等）的关系来解题。
• 相似知识点洛谷题目：
  - P1279 字串距离：涉及字符串操作及数值计算，可类比本题通过分析字符串变换前后某些特征值的变化规律求解。
  - P2671 求和：同样需要根据题目条件推导数学关系，结合数列运算求解，与本题推导方差变化规律类似。
  - P1993 小K的农场：通过建立数学模型，利用不等式关系求解，与本题通过数学推导解决问题的思路相似。 

---
处理用时：55.24秒