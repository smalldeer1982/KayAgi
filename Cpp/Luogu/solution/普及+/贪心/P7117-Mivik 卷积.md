# Mivik 卷积

## 题目背景

卷王之王卷穿肠（doge

## 题目描述

从前有一只 Mivik，他喜欢卷积。他定义两个仅与 $x$ 有关的多项式函数 $f\left(x\right)$ 和 $g\left(x\right)$ 的 Mivik 卷积如下：

$$
f\left(x\right)\otimes g\left(x\right)=\sum_{k=0}^{\deg f +\deg g}\max_{i\in [0,\deg f] \land j\in [0,\deg g]\land i+j=k}\left\{\left[x^i\right]f\left(x\right)+\left[x^j\right]g\left(x\right)\right\} x^k
$$

其中 $\deg f$ 表示 $f$ 的最高项次数，$\left[x^i\right]f\left(x\right)$ 代表 $f\left(x\right)$ 这一函数中 $x^i$ 这一项的系数。

请注意，Mivik 卷积是左结合的，也就是说 $a\otimes b\otimes c=(a\otimes b)\otimes c$。

Mivik 定义 Mivik 函数为能表示为 $f\left(x\right)=ax+b$ 形式的函数，其中 $a$、$b$ 均为整数。例如 $f\left(x\right)=-3+2x$ 是 Mivik 函数，而 $f\left(x\right)=\frac{1}{x}$ 不是。

Mivik 又定义一个函数 $f\left(x\right)$ 是 simple 的，当且仅当存在一个 Mivik 函数的序列 $S$（大小为 $\left|S\right|$），使得：

$$
f\left(x\right)=S_1\otimes S_2\otimes S_3\otimes\cdots\otimes S_{\left|S\right|}.
$$

现在 Mivik 给了你一个多项式函数，问你这个函数是不是 simple 的；如果是，请顺便告诉他任意一种可能的 $S$。

## 说明/提示

### 样例解释 #1

给定的函数 $f\left(x\right)=2+3x+3x^2$ 可以由 $\left(2x+1\right)\otimes\left(x+1\right)$ 得到。

### 测试点约束

**本题采用捆绑测试。**

对于全部数据，有 $1\le n\le 5\times 10^5$，$-10^8\le f_i\le 10^8$。

每个子任务的具体限制见下表：

| 子任务编号 | 分值 | $n\le$ |
|:-:|:-:|:-:|
| 1 | 5 | $1$ |
| 2 | 5 | $2$ |
| 3 | 20 | $20$ |
| 4 | 30 | $5000$ |
| 5 | 40 | $5\times 10^5$ |

**本题读入输出量较大，请使用较快的读入输出方式。**

## 样例 #1

### 输入

```
3
2 3 3
```

### 输出

```
simple
2
2 1
1 1
```

## 样例 #2

### 输入

```
3
97 109 101
```

### 输出

```
simple
2
54 42
47 55
```

## 样例 #3

### 输入

```
9
9 9 8 2 4 4 3 5 3
```

### 输出

```
nice
```

# 题解

## 作者：Mivik (赞：14)


[欢迎到我的博客查看](https://mivik.gitee.io/2020/solution/mivik-newbie-and-chinos-contest-2020-solution-convolution/)

两个多项式 $A$ 和 $B$ 通过 Mivik 卷积得到 $C$ 可以文字描述为：

> 两个盒子，从第一个里面选 $i$ 个（$0\le i<|A|$）物品权值为 $A_i$，从第二个里面选 $j$ 个（$0\le j<|B|$）权值为 $B_j$。$C_i$（$0\le i<|A|+|B|-1$）的值为从两个盒子里面选总共 $i$ 个的最大权值和。

容易证得 Mivik 卷积的结合律和交换律（考虑下标的和）。然后我们发现整个问题就变成了：

> 要求构造 $|S|-1$ 个物品，第 $i$ 个物品不选的权值为 $b_i$，选的权值为 $a_i$，使得从其中选 $i$ 个物品（$0\le i<|S|$）的最大权值和恰为 $S_i$。

我们考虑如果给定物品我们怎么计算 $S$。我们首先把所有的 $b_i$ 加起来得到 $S_0$，然后把所有物品按 $(a_i-b_i)$ 从大到小排序，则 $S_k$ 等于 $S_0$ 加上前 $k$ 大的 $(a_i-b_i)$。

我们发现 $S$ 合法当且仅当对于任意一个 $i$（$1\le i<|S|-1$），都有 $S_i-S_{i-1}\ge S_{i+1}-S_i$。我们可以用这个条件判合法。然后我们如下构造 $a$ 和 $b$ 数组（下标从 $1$ 开始）：$b_1$ 设置为 $S_0$，$a_1$ 设置为 $S_1$，对于其它的 $i$，$b_i$ 设置为 $0$，$a_i$ 设置为 $v_i-v_{i-1}$。注意对 $|S|=1$ 要特判答案。

~~所以这真的是一道良心语文题。~~

[mivik.h](https://mivik.gitee.io/mivik.h)

[代码](https://paste.ubuntu.com/p/QsSnbvTPzf/)


---

## 作者：_H17_ (赞：5)

## 改成算是人话

$f\left(x\right)\otimes g\left(x\right)=\sum_{k=0}^{\deg f +\deg g}\max_{i\in [0,\deg f] \land j\in [0,\deg g]\land i+j=k}\left\{\left[x^i\right]f\left(x\right)+\left[x^j\right]g\left(x\right)\right\} x^k$

意思大致是：把从 $f,g$ 中选取一共 $k$ 个数，将这堆数去最大值在乘上 $x^k$（就是把原先 $x^k$ 的系数取最大值）其中 $0 \le k \le \deg f+ \deg g$，的所有情况求和得到卷积。

## 思路（大致同官方）

我们发现 $S$ 合法当且仅当对于任意一个 $i(1\le i < \lvert S\rvert-1)$，都满足 $S$ 差单调不上升。然后我们如下构造 $a,b$ 数组 $b_1=S_0,a_1=S_1$ 对于其它 $i$ 让 $b_i=0,a_i=v_i-v_{i-1}$。注意对 $\lvert S\rvert=1$ 进行特判。

## 代码

~~终于附上能看的代码了~~。

```cpp
#include<bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")//比赛别乱用
using namespace std;
int n,v[1000001],l=0x3f3f3f3f;
inline char gc(){
	static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int x=0;
	char f=1,ch=gc();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-f;
		ch=gc();
	}
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=gc();
	return x*f;
}
inline void write(int a){
	if(a<0)
		putchar('-'),a=-a;
	if(a<10){
		putchar(a+48);
		return;
	}
	write(a/10);
	putchar(a%10+48);
	return;
}
void write(string a){
    for(int i=0;i<a.size();i++)
        putchar(a[i]);
    return;
}//听说要卡I/O，虽然没卡
int main(){
    n=read();
    for(int i=1;i<=n;i++)
        v[i]=read();
    for(int i=2,k;i<=n;i++){
        k=v[i]-v[i-1];
        if(l<k){
            write("nice");
            exit(0);
        }//判单调不上升
        l=k;
    }
    write("simple\n");
    if(n==1){//|S|=1
        write("1\n0 "),write(v[1]),write("\n");
        exit(0);
    }
    write(n-1);
    putchar('\n');
    for(int i=2,k;i<=n;i++){
        k=((i==2)?v[1]:0);//k表示b
        write(k+v[i]-v[i-1]),putchar(' '),write(k),putchar('\n');
    }
    return 0;
}
```

---

