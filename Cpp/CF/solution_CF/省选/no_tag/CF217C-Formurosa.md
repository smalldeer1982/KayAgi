# Formurosa

## 题目描述

The Bytelandian Institute for Biological Research (BIBR) is investigating the properties of two species of bacteria, named simply 0 and 1. Even under a microscope, bacteria of those two species are very difficult to distinguish. In fact, the only thing the scientists possess that is able to differentiate between them is a plant called Formurosa.

If the scientists place a sample of colonies of bacteria on each on Formurosa's leaves, it will activate a complicated nutrition process. During that process color of Formurosa changes to reflect the result of a — possibly very complicated — logical formula on the species of bacteria, involving constants and the operators $ | $ (OR), $ &amp; $ (AND) and $ ^ $ (XOR). If it is 0, the plant will turn red, otherwise — it will turn blue.

For example, if the nutrition process of Formurosa is described by the formula: $ (((?^?)|?)&amp;(1^?)) $ ; then Formurosa has four leaves (the "?" signs denote the leaves). If we place $ 0,1,0,0 $ on the respective leaves, the result of the nutrition process will be $ (((0^1)|0)&amp;(1^0))=1 $ , therefore the plant will turn blue.

The scientists have $ n $ colonies of bacteria. They do not know their types; the only thing they know for sure is that not all colonies are of the same type. They want to attempt to determine the bacteria's species by repeated evaluations with Formurosa. During each evaluation they must place exactly one sample on every leaf of the plant. However, they may use multiple samples of one colony during a single evaluation; they can even cover the whole plant with bacteria from one colony!

Is it possible for them to always determine the species of each colony, no matter what they are (assuming they are not all the same)?

## 样例 #1

### 输入

```
2
(?^?)
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
10
?
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
2
((?^?)&?)```

### 输出

```
YES
```

# 题解

## 作者：Lucky_Glass (赞：7)

## \# 题面
\> Linked [Codeforces 217C](http://codeforces.com/problemset/problem/217/C)

\> Linked [洛谷 CF217C](https://www.luogu.com.cn/problem/CF217C)

有 $n$ 个`bool`未知量 $x_1,x_2,\dots,x_n$（取值`false`/`true`）以及一个含若干互不相同的参数的表达式 $F(a_1,a_2,\dots,a_k)$。

表达式只包含：
- `?` 表示一个参数，所有参数互不相同；
- `&`,`|`,`^` 三种运算，即逻辑与、逻辑或和逻辑异或；
- `(`,`)` 表示运算的优先级，**保证每个运算符外围都有一对括号**（也可以认为是一对括号内只有恰好一个运算符）。

你可以进行的操作是将每个参数 $a_i$ 代换成未知量 $x_j$，同一个未知量可以代入多个不同的参数。然后你可以知道这个表达式的值。

你可以进行无限次操作，求你能否通过这些操作确定每一个未知量的取值。

另外需要注意的是，**未知量的取值一定不全相同**。

$2\le n\le10^6$；表达式以字符串形式输入，长度不超过 $10^6$。

---
## \# 解析
可以发现没有必要真的考虑“一次代入很多未知量”；因为保证了未知量有零有一，且所有未知量地位相同，就相当于我们可以做到“**将每个参数指定代换成零或一**”。

于是用二进制数 $S$，表示一个指定参数值的方案，$S$ 的第 $i$ 位表示参数 $a_i$ 的取值。

在这个基础上，有结论“若存在一种 $S$ 使得 $F(S)\neq F(\overline S)$，则可以解出”。（$\overline S$ 指把 $S$ 的每一位都取反）。

首先是必要性。考虑反证，所有代入方式 $S$ 都有 $F(S)=F(\overline S)$。若 $t_1,t_2,\dots,t_n$ 是未知量的解，则 $\overline{t_1},\overline{t_2},\dots,\overline{t_n}$ 代入表达式的值一定和该解完全相同，即存在无法区别开的两种解。

然后是充分性。如果存在一种 $S$ 使得 $F(S)\neq F(\overline S)$，如何构造出一种求解的方案？

如果 $S=(111\dots1)_2$，则直接把**所有参数代换成一个未知量**，就可以直接判断该未知量是什么值。

如果 $F[(111\dots1)_2]=F[(00\dots0)_2]=a$，不妨假设情况为 $F(S)=a$，则 $F(\overline S)=\overline a$。那么我们可以每次**代入两个未知量** $x_p,x_q$：$x_p$ 代入 $S$ 中为 $1$ 的参数，$x_q$ 代入 $S$ 中为 $0$ 的参数。由于未知量有零有一，所以对 $x_i$ 一定找得到 $x_j$ 通过上述方式代入后得到 $\overline a$，于是可以判断 $x_i=1,x_j=0$。

然后就是如何判断是否存在 $F(S)\neq F(\overline S)$ 了，比较显然的是可以对每个子表达式递归处理。

对于一个子表达式，有三种 $(S,\overline S)$：

- $F(S)=F(\overline S)=0$，记为*Ⅰ类*；
- $F(S)=F(\overline S)=1$，记为*Ⅱ类*；
- $F(S)\neq F(\overline S)$，记为*Ⅲ类*。

于是可以用一个三位的二进制状态表示对于该子表达式，是否存在上述类型的 $(S,\overline S)$。

初始状态，`?` 只存在Ⅲ类，`0/1` 分别只存在Ⅰ/Ⅱ类。

合并两个子表达式 $G,H$，$F$ 的状态需要分类讨论：

- $G,H$ 通过 `&` 连接：
	- Ⅰ类：
		- $G,H$ 有一个有Ⅰ类；
		- $G,H$ 都有Ⅲ类，比如 $G(S)=1,H(T)=0$，则
		$$
		\begin{aligned}
		&F(ST)=G(S)\land H(T)=0\\
		&F(\overline{ST})=G(\overline S)\land H(\overline T)=0
		\end{aligned}
		$$
	- Ⅱ类：
		- $G,H$ 都有Ⅱ类；
	- Ⅲ类：
		- $G$ 有Ⅱ类，$H$ 有Ⅲ类，因为 $G(S)\land1$ 的值取决于 $S$；
		- $G$ 有Ⅲ类，$H$ 有Ⅱ类，同理；
		- $H,G$ 都有Ⅲ类。

其他的都分类讨论……比较类似就不列举了。

---
## \# 源代码

```cpp
/*Lucky_Glass*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=1e6+10;
#define ci const int &
#define cc const char &

int n,m,nstk;
char equ[N];
int opr[N],stk[N];

inline bool IfOper(cc c){return c=='|' || c=='&' || c=='^';}
inline int Number(cc c){return c=='?'? 4:c=='0'? 1:2;}

int Solve(ci le,ci ri){
    if(opr[le]){
        int resL=Solve(le+1,opr[le]-1),resR=Solve(opr[le]+1,ri-1);
        bool l0=resL&1,l1=resL>>1&1,l2=resL>>2&1,
             r0=resR&1,r1=resR>>1&1,r2=resR>>2&1,
             t0=0,t1=0,t2=0;
        switch(equ[opr[le]]){
            case '&':{
                t0=l0|r0|(l2&r2);
                t1=l1&r1;
                t2=(l2&r2)|(l1&r2)|(l2&r1);
                break;
            }
            case '|':{
                t0=l0&r0;
                t1=l1|r1|(l2&r2);
                t2=(l2&r2)|(l0&r2)|(l2&r0);
                break;
            }
            case '^':{
                t0=(l0&r0)|(l1&r1)|(l2&r2);
                t1=(l0&r1)|(l1&r0)|(l2&r2);
                t2=((l0|l1)&r2)|(l2&(r0|r1));
                break;
            }
        }
        return t0|(t1<<1)|(t2<<2);
    }
    else return Number(equ[le]);
}
int main(){
    scanf("%d%s",&n,equ+1);
    m=(int)strlen(equ+1);
    if(m==1){
        printf("%s\n",equ[1]=='?'? "YES":"NO");
        return 0;
    }
    for(int i=1;i<=m;i++)
        switch(equ[i]){
            case '(':{stk[++nstk]=i;break;}
            case ')':{nstk--;break;}
            default:{
                if(IfOper(equ[i])) opr[stk[nstk]]=i;
                break;
            }
        }
    printf("%s\n",(Solve(1,m)>>2&1)? "YES":"NO");
    return 0;
}
```

---
## THE END
### Thanks for reading!


---

