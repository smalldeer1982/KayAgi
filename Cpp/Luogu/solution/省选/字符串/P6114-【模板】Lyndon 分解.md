# 【模板】Lyndon 分解

## 题目描述

这是一道模板题。

读入一个由小写英文字母组成的字符串 $s$ ，请把这个字符串分成若干部分 $s=s_1s_2s_3\cdots s_m$，使得每个 $s_i$ 都是 [$\text{Lyndon Word}$](https://en.wikipedia.org/wiki/Lyndon_word)，且 $\forall 1\le i<m:s_i\ge s_{i+1}$。输出 $s_1$ 到 $s_m$ 这些串长度的右端点的位置。位置编号为 $1$ 到 $n$。

一个字符串 $s$ 是一个 $\text{Lyndon Word}$，当且仅当 $s$ 是其所有后缀中最小的字符串。

为了减小输出量，你只需要输出所有右端点的异或和。

## 说明/提示

第一组样例的答案为 `2 4 5`。

第二组样例的答案为 `1 2 4 6 9 13 18`。

- 对于 $20\%$ 的数据，保证 $1\le n\le 1000$；
- 对于 $100\%$ 的数据，保证 $1\le n\le 5\times 10^6+1$。

## 样例 #1

### 输入

```
ababa
```

### 输出

```
3
```

## 样例 #2

### 输入

```
bbababaabaaabaaaab
```

### 输出

```
23
```

# 题解

## 作者：wucstdio (赞：86)

大概是我贡献的第二道模板？

## $\text{Lyndon}$ 分解详解

我们定义一个串是 $\text{Lyndon}$ 串，当且仅当这个串的最小后缀就是这个串本身。

该命题等价于这个串是它的所有循环表示中字典序最小的。

---

#### 引理 1：如果 $u$ 和 $v$ 都是 $\text{Lyndon}$ 串并且 $u<v$，则 $uv$ 也是 $\text{Lyndon}$ 串。

证明：

##### 1、若 $\operatorname{len}(u)\ge\operatorname{len}(v)$

这时，$u$ 和 $v$ 这两个串在 $\operatorname{len}(v)$ 之前就出现了不同的字符，所以有 $v>uv$，又因为 $v$ 是 $\text{Lyndon}$ 串，所以 $v$ 的所有后缀都大于 $v$，所以 $uv$ 的所有后缀都大于 $uv$，故 $uv$ 是 $\text{Lyndon}$ 串。

##### 2、若 $\operatorname{len}(u)<\operatorname{len}(v)$

若 $u$ 不是 $v$ 的前缀，那么有 $v>uv$，得证。

若 $u$ 是 $v$ 的前缀，那么如果 $v<uv$，则必有 $v[\operatorname{len}(u)+1:]<v$（也就是各自去掉了前 $|u|$ 个字符），矛盾。

---

我们定义一个串 $S$ 的 $\text{Lyndon}$ 分解为一个字符串序列 $A_1,A_2,\dots,A_m$，满足：

- $\forall i \in [1,m]$，满足 $A_i$ 是 $\text{Lyndon}$ 串。
- $\forall i \in [1,m-1]$，满足 $A_i\ge A_{i+1}$。

可以证明这种划分存在且唯一。

### 存在性证明

初始令 $m=|S|$ 并且 $A_i=S[i]$，然后每次不断找到 $A_i<A_{i+1}$ 并且合并为一个串。最后一定能使得所有的 $A_i\ge A_{i+1}$。

### 唯一性证明

假设对于字符串 $S$ 存在两个 $\text{Lyndon}$ 分解：

$$S=A_1A_2\cdots A_iA_{i+1}A_{i+2}\cdots A_{m_1}$$

$$S=A_1A_2\cdots A_iA^\prime_{i+1}A^\prime_{i+2}\cdots A^\prime_{m_1}$$

不妨设 $\operatorname{len}(A_{i+1})>\operatorname{len}(A^\prime_{i+1})$。

观察 $A_{i+1}$ 在第二种分解中的对应情况。假设 $A_{i+1}=A^\prime_{i+1}A^\prime_{i+2}\cdots A^\prime_{k}A^\prime_{k+1}[:l]$。

那么由 $\text{Lyndon}$ 串的性质可知：

$$A_{i+1}<A^\prime_{k+1}[:l]\le A^\prime_{k+1}\le A^\prime_{i+1}<A_{i+1}$$

矛盾。

---

#### 引理2：若字符串 $v$ 和字符 $c$ 满足 $vc$ 是某个 $\text{Lyndon}$ 串的前缀，则对于字符 $d>c$ 有 $vd$ 是 $\text{Lyndon}$ 串。

证明：

设该 $\text{Lyndon}$ 串为 $v+c+t$。

则 $\forall i \in [2,|v|],v[i:]+c+t>v+c+t$，也就是说 $v[i:]+c\ge v$。

所以 $v[i:]+d>v[i:]+c\ge v$。

同时因为 $c>v[1]$，我们有 $d>c>v[1]$。

故 $v+d$ 是一个 $\text{Lyndon}$ 串。

---

### $\text{Duval}$ 算法

这个算法可以在 $O(n)$ 时间复杂度，$O(1)$ 空间复杂度内求出一个串的 $\text{Lyndon}$ 分解。

该算法中我们仅需维护三个变量 $i,j,k$。

维持一个循环不变式：

- $s[:i-1]=s_1s_2\cdots s_g$ 是固定下来的分解，也就是 $\forall l\in[1,g],s_l$ 是 $\text{Lyndon}$ 串且 $s_l>s_{l+1}$。
- $s[i,k-1]=t^h+v(h>1)$ 是没有固定的分解，满足 $t$ 是 $\text{Lyndon}$ 串，且 $v$ 是 $t$ 的可为空的不等于 $t$ 的前缀，且有 $s_g>s[i,k-1]$

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tc73fjp1.png)

当前读入的字符是 $s[k]$，令 $j=k-|t|$。

分三种情况讨论：

- 当 $s[k]=s[j]$ 时，直接 $k\leftarrow k+1,j\leftarrow j+1$，周期 $k-j$ 继续保持
- 当 $s[k]>s[j]$ 时，由**引理 2** 可知 $v+s[k]$ 是 $\text{Lyndon}$ 串，由于 $\text{Lyndon}$ 分解需要满足 $s_i\ge s_{i+1}$，所以不断向前合并，最终整个 $t^h+v+s[k]$ 形成了一个新的 $\text{Lyndon}$ 串。
- 当 $s[k]<s[j]$ 时，$t^h$ 的分解被固定下来，算法从 $v$ 的开头处重新开始。

复杂度分析：$i$ 只会单调往右移动，同时 $k$ 每次移动的距离不会超过 $i$ 移动的距离，所以时间复杂度是 $O(n)$ 的。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char s[5000005];
int n,ans;
int main()
{
	scanf("%s",s+1);
	n=(int)strlen(s+1);
	for(int i=1;i<=n;)
	{
		int j=i,k=i+1;//初始化
		while(k<=n&&s[j]<=s[k])
		{
			if(s[j]<s[k])j=i;//合并为一整个
			else j++;//保持循环不变式
			k++;
		}
		while(i<=j)//从v的开头重新开始
		{
			ans^=i+k-j-1;
			i+=k-j;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：pomelo_nene (赞：16)

## 浅谈 $\text{Lyndon Word}$ 

## 前置约定与定义

$\text{Lyndon Word}$ 的学习似乎并不需要太多的前置芝士，但是如果在进阶的时候不学一些基础的字符串算法会比较麻烦，在此之前请保证自己会拓展 KMP，后缀数组，最小表示等一些基础字符串算法，有些可能还会比较冷门。

一个字符可以看成一个长度为 $1$ 的字符串。

字符和字符串没有特别区分，注意区别。

对于一个字符串 $s$，记其长度为 $|s|$。对于两个字符串 $u,v$，记 $uv$ 为两个字符串按顺序拼接成为的新字符串，对于 $n$ 个字符串 $s_1,s_2,\dots,s_n$，同理记 $s_1s_2\dots s_n$ 为 $n$ 个字符串拼接形成的新字符串。请注意，$s_is_{i+1} \dots s_j$ 有特别区分 $s[i\dots j]$ 这一部分。如果单取一个字符串 $s$ 中的第 $x$ 个字符，则直接写为 $s[x]$。

定义 $\operatorname{pre}(s,x)$ 为 $s$ 的前缀，长度为 $x$；$\operatorname{suf}(s,x)$ 为 $s$ 的后缀，长度为 $x$。真前缀定义为对于字符串 $s$，使得$v=\operatorname{pre}(s,x)$ 且 $x \neq |s|$，$v$ 即是 $s$ 的真前缀，真后缀同理。

若 $0 \leq r < |s|$，满足 $\operatorname{pre}(s,r)=\operatorname{suf}(s,r)$，即称 $\operatorname{pre}(s,r)$ 为 $s$ 的 $\operatorname{border}$。长度为 $k$ 的 $\operatorname{border}$ 即 $\operatorname{pre}(s,k)=\operatorname{suf}(s,k)$。

对于一个字符串 $s$，$s^r$ 为它的反串。 

对于一个字符串 $s$，$s^a$（$a$ 为一个具体数值）表示 $a$ 个 $s$ 相拼接。

## 定义

### $\text{Lyndon Word}$ 定义

定义一个字符串 $s$ 为 $\text{Lyndon Word}$，当且仅当 $s$ 是所有后缀中最小的。

简单来说，如果 $s$ 满足其最小后缀为 $s$ 本身的串，即为 $\text{Lyndon Word}$。也就是 $\forall i \in [1,|s|),s<\operatorname{suf}(s,i)$。

在 Wiki 上还有另外一个等价的定义：$s$ 是其所有循坏位移中最小的一个。相对来说上面那个会好理解一些。

### $\text{Lyndon}$ 分解定义

$\text{Lyndon}$ 分解即是将字符串 $s$ 分解成 $s_1,s_2,\dots ,s_n$，使得 $\forall i \in [1,n],s_i$ 为 $\text{Lyndon Word}$，并且 $\forall 1 \leq i < m:s_i \geq s_{i+1}$。

## 性质

#### 引理 1

若两个字符串 $u,v$ 为 $\text{Lyndon Word}$ 并且 $u<v$，则 $uv$ 同为 $\text{Lyndon Word}$。

证明：

考虑分类讨论长度大小关系：  

1，若 $|u|>|v|$：   
因为 $v$ 是一个 $\text{Lyndon Word}$，所以 $v$ 的所有后缀大于 $v$；考虑证明 $v>uv$，因为 $v>u$，显然；   
2，若 $|u| \leq |v|$：

- 如果 $u$ 不是 $v$ 的前缀，显然 $v>uv$；   
- 如果 $u$ 是 $v$ 的前缀，若 $uv$ 不为 $\text{Lyndon Word}$，也就是 $v<uv$，则有 $\operatorname{suf}(v,|v|-|u|)<v$，而这和 $v$ 是 $\text{Lyndon Word}$ 矛盾，故得证。

#### 引理 2

$\text{Lyndon}$ 分解唯一。（唯一性）

证明：   
假设有两种 $\text{Lyndon}$ 分解使得分解不唯一，则：

$$s=s_1s_2 \dots s_is_{i+1} \dots s_n$$

同时有：

$$s=s_1s_2 \dots s_i's_{i+1}' \dots s_n'$$

假设 $|s_i| > |s_i'|$，且令 $s_i=s_i's_{i+1}'\dots s_k' \operatorname{pre}(s_{k+1}',l)$，所以有 $s_i < \operatorname{pre}(s_{k+1}',l) \leq s_{k+1}' \leq s_i' <s_i$，推出矛盾，故分解唯一。

#### 引理 3

对于每一个字符串，都有其 $\text{Lyndon}$ 分解。（存在性）

证明：   
假设在开始的时候有 $n$ 个长度为 $1$ 的字符串 $s_1,s_2,\dots ,s_n$，我们对于每一次合并，只需要将相邻的两段 $s_i < s_{i+1}$ 进行合并就行了。

#### 引理 4

如果字符串 $v$（$|v|=r-1$） 与某个字符串 $c$（$|c|=1$），满足 $vc=\operatorname{pre}(s,r)$（满足 $s$ 是一个 $\text{Lyndon Word}$），则对于一个字符串 $d$（$d>c$ 并且 $|d|=1$），使得 $vd$ 是一个 $\text{Lyndon Word}$。

证明：   
设 $s=vct$，则 $\forall i \in[2,|v|],v[i]ct>vct$，因而 $v[i]c\geq v$。且 $d>c$，所以 $v[i]d>v[i]c\geq v$。

因为 $c>v[i]$，有 $d>c>v[1]$，得证。

#### 引理 5

设有三个字符串 $s_1,s_2,s_3$，其中 $s_1$ 是一个 $\text{Lyndon Word}$ 并且 $s_1>s_2\geq s_3$。那么 $s_1>s_2+s_2\geq s_2+s_3$。

证明：   
- 如果 $s_2$ 为 $s_1$ 的后缀，根据定义有 $s_1>\operatorname{pre}(s_1,|s_2|)>s_2 \geq s_3$，成立；   
- 如果 $s_2$ 不为 $s_1$ 的后缀，显然成立。

#### 性质 1

如果 $s$ 为 $\text{Lyndon Word}$，则 $s$ 不存在 $\operatorname{border}$。

证明：

如果 $s$ 存在 $\operatorname{border}$，则根据 $\operatorname{border}$ 的定义，存在某个前缀等于后缀，因此这个后缀小于整个串，得证。

#### 性质 2

如果 $s$ 是 $\text{Lyndon Word}$，$s=uv$ 且 $|u|>0,|v|>0$，满足 $u<v$。

$u<uv$ 而 $uv<v$，所以 $u<v$。

#### 性质 3

如果 $|s|>2$，$s$ 是一个 $\text{Lyndon Word}$ 充要条件是满足 $s=uv$，且 $|u|>0,|v|>0,u<v$ 并且 $u,v$ 都是 $\text{Lyndon Word}$。

证明：

- 充分性：查引理 1；   
- 必要性：

  假设有字符串 $s$ 有后缀 $\operatorname{suf}(s,|s|-i+1)$，满足其是 $s$ 的次小后缀。
  
  又假设 $\operatorname{pre}(s,i-1)$ 有长度为 $k$ 的 $\operatorname{border}$，而 $k<i-1$，所以 $k+1 \neq i$。
  
  因为 $s$ 是 $\text{Lyndon Word}$，而 $\operatorname{suf}(s,|s|-i+1)$ 是其次小后缀，所以 $\operatorname{suf}(s,|s|-i+1)<\operatorname{suf}(s,|s|-k)$，所以 $\operatorname{suf}(s,|s|-i+k+1)<s$，与假设 $s$ 是一个 $\text{Lyndon Word}$ 矛盾，所以假设不成立，$\operatorname{pre}(s,i-1)$ 没有 $\operatorname{border}$。
  
  根据 $s$ 是一个 $\text{Lyndon Word}$ 和 $\operatorname{pre}(s,i-1)$ 没有 $\operatorname{border}$ 可以推出：$\forall 1<j \leq i-1$，$\exists j \leq  k \leq i-1$，满足 $s[k]>s[k-j+1]$，也就是 $s[j\dots i-1]>\operatorname{pre}(s,i-1)$，所以 $\operatorname{pre}(s,i-1)$ 是一个 $\text{Lyndon Word}$。
  
  而 $\operatorname{suf}(s,|s|-i+1)$ 是 $s$ 的次小后缀，不存在 $j>i$，使得 $\operatorname{suf}(s,|s|-j+1)<\operatorname{suf}(s,|s|-i+1)$，所以 $\operatorname{suf}(s,|s|-i+1)$ 是一个 $\text{Lyndon Word}$。
  
  综上，因为 $s=\operatorname{pre}(s,i-1)\operatorname{suf}(s,|s|-i+1)$，而 $\operatorname{pre}(s,i-1)$ 和 $\operatorname{suf}(s,|s|-i+1)$ 均为 $\text{Lyndon Word}$，得证。
  
证明了这些性质，主要是用于介绍下面的算法及题目。

## 算法

不难想到 二分+Hash 和 后缀数组 的做法，下面只介绍专用的算法。

### $\text{Duval}$ 算法

$\text{Duval}$ 算法可以在 $O(n)$ 的时间复杂度和 $O(1)$ 的**额外**空间复杂度求出一个串的 $\text{Lyndon}$ 分解。

在整个算法流程中维护三个变量 $i,j,k$。$i$ 的意思是接下来开始划分的位置，意为 $[1,i-1]$ 区间内的字符都已经划分成功。

类似于维护一个循环不变式：

- $\operatorname{pre}(s,i-1)=s_1s_2\dots s_g$ 已经固定，且满足 $s_l$ 为 $\text{Lyndon Word}$，并且 $s_l \geq s_{l+1}$；

- $s[i \dots k-1]=t_1t_2\dots t_hv(h\geq 1)$ 还没有固定，满足 $t_1$ 是 $\text{Lyndon Word}$，$t_1=t_2=\dots=t_h$，$v$ 是 $t_h$ 的真前缀，且有 $s_g \gg s[i,k-1]$。

![](http://61.186.173.89:2019/2020/03/02/3a1b0548677c9.png)

这里就直接截 pdf 里面的图了。（其实是懒）

维护指针 $j \gets i,k \gets i+1$，循环分类判断：

- 若 $a[k]>a[j]$，由引理 4 得到 $v+s[k]$ 为一个 $\text{Lyndon Word}$。根据 $\text{Lyndon}$ 分解的要求，必须 $s[i] \geq s[i+1]$，则往前合并，所以 $j \gets i,k \gets k+1$；
- 若 $a[k]=a[j]$，有一定可能比原来的小，$j \gets j+1,k \gets k+1$，继续查找，周期保持；
- 否则这里一定要进行划分，$t_h$ 固定，退出循环，重新开始。

可以证明一个字符最多经过 $3$ 次，因此时间复杂度为 $O(n)$。

[【模板】$\text{Lyndon}$ 分解](https://www.luogu.com.cn/problem/P6114)

真·板子题。

```cpp
#include<cstdio>
#include<cstring>
char s[5000005];
int main(){
	scanf("%s",s+1);
	int len=strlen(s+1);
	int i,j,k,ans=0;
	i=1;
	while(i<=len)
	{
		for(j=i,k=i+1;k<=len && s[k]>=s[j];++k)
			if(s[k]>s[j])	j=i;
			else	++j;
		while(i<=j)	ans^=(i+k-j-1),i+=k-j;
	}
	printf("%d",ans);
	return 0;
}
```

另外，这个算法可以用同样的思路求出所有 $s$ 前缀字符串的最大/小的后缀。可以自己思考上手实验。


1. [$\text{Lyndon Word}$ 学习笔记](https://blog.csdn.net/qq_36797743/article/details/89191890)；
3. [P6127 wucstdio 的题解](https://www.luogu.com.cn/blog/wucstdio/solution-p6127)；
4. [Wiki](https://en.wikipedia.org/wiki/Lyndon_word)；
5. [字符串算法选讲（下载链接已挂，此为预览）](https://wenku.baidu.com/view/850f93f4fbb069dc5022aaea998fcc22bcd1433e.html)。

如有不对请指出。

---

## 作者：L_zaa_L (赞：9)

### 什么是 Lyndon 串

我们定义一个串是 Lyndon 串，当且仅当这个串的**最小后缀**就是这个串本身。

也就是说 Lyndon 串等价于这个串是它的所有循环表示中**字典序最小**的（必须是最小的，不能有多个，比如说：`aa` 就不是一个 Lyndon 串，因为 `a`的字典序小于`aa`）。

### Lyndon 分解定义

将一个字符串 $S$ 分解为若干个子串：$s_1s_2s_3\dots s_m$。对于任意 $i\in [1,m]$，使得 $s_i$ 为 Lyndon 串，且 $\forall i\in[1,m-1],s_i\ge s_{i+1}$。

### 一些性质

- #### 若 $u,v$ 都为 Lyndon 串，且 $u<v$，那么 $uv$ 一定为 Lyndon 串。

**证明**：

如果想要证明 $uv$ 是 Lyndon 串，就要证明 $uv$ 是其最小后缀。

也就是只需要证明 $uv<v$，由于 $u<v$，那么显然成立。

- #### 存在性

**证明**：

我们可以吧所有字符单独成立一个字符串，然后根据上面那一条性质，我们可以不断找到 $s_i<s_{i+1}$ 的，将这两个进行合并（合并之后还为 Lyndon 串），最后肯定能弄成所有 $s_i$ 都是 Lyndon 串且 $s_i\ge s_{i+1}$ 的。

- #### 唯一性

**证明**：

我们设有两种分解方式分别为：

$s_1s_2s_3\dots s_{i-1}s_{i}s_{i+1}\dots s_m$

$s_1s_2s_3\dots s_{i-1}s_{i}'s_{i+1}'\dots s_k'$

我们发现从第 $i$ 个 Lyndon 串开始两种分解方式开始不一样了，我们不妨设 $s_i=s_i's_{i+1} 's_{i+2}'\dots s_p'[:l]$，其中 $s_p'[:l]$ 表示第 $p$ 个字符串的前 $l$ 个字符组成的字符串。

我们可以因为 Lyndon 分解的定义推断出 $s_i'\ge s_{i+1}'\ge s_{i+2}'\ge \dots\ge  s_p'[:l]$。

那么因为 $s_i'$ 是 $s_i$ 的前缀，那么 $s_i'<s_i$，所以 $s_i>s_i'\ge s_{i+1}'\ge s_{i+2}'\ge \dots\ge  s_p'[:l]$。

然后又因为 $s_i$ 也为 Lyndon 串（也就是说 $s_i$ 是其所有子串中最小的），那么 $s_i>s_i'\ge s_{i+1}'\ge s_{i+2}'\ge\dots\ge s_p'[:l] >s_i$。

如果 $s_i>s_i$ 显然不成立，所以分解是唯一的。

### Duval 算法

考虑分为三个部分：第一部分已经分解完的，第二部分正在分解的，第三部分还没分解的。

Duval 的算法思想是保证第二部分是 Lyndon 串的情况下，然第二部分的元素越多越好。


我们维护三个变量：$i,j,k$。

$S[1,i-1]=s_1s_2\dots s_q$ 表示已经固定下来的分解，其中 $s_i>s_{i+1}$，

$S[i,k-1]=|t|^p+v$ 表示是还没有确定下来的分解，对于循环的 $|t|$ 他们一定是满足 $t_i>t_{i+1}$ 的，所以把他们分在一起。

那么我们就能设当前第二部分开头的位置为 $i$，要加入第二部分的指针为 $k$，$j$ 为 $|t|$ 这个循环中的某一位置，将 $j$ 与 $k$ 这两个位置上的字符进行比较，那么：

- 当 $s_k=s_j$ 时，没有什么问题，直接匹配下一个字符。

- 当 $s_k>s_j$ 时，加入的字符后第二部分还是一个 Lyndon 串。

- 当 $s_k<s_j$ 时，$t_1,t_2\dots t_h$ 的分解被固定下来，算法从 $v$ 重新开始。

### Code

**例题**[**P6114 【模板】Lyndon 分解**](https://www.luogu.com.cn/problem/P6114#submit)

```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*f;
}
int main(){
	int n,ans=0;
	char s[5000005];
	scanf("%s",s+1);
	n=strlen(s+1);
	int i=1;
	while(i<=n){
		int j=i,k=i+1;
		while(k<=n&&s[j]<=s[k]){
			if(s[j]==s[k]) ++j;
			else j=i;
			++k;
		}
		for(;i<=j;i+=(k-j))
			ans^=(i+k-j-1);
	} 
	printf("%d",ans);
	return 0;
}
```
时间复杂度：$O(n)$。

---

## 作者：zac2010 (赞：4)

### 题意

定义 $\text{Lyndon}$ 串为：其本身是最小后缀的串。

再定义 $\text{Lyndon}$ 分解为：将一个串分解为一些 $\text{Lyndon}$ 串，且这些串的字典序是一个单调不升的关系。

求一个串的 $\text{Lyndon}$ 分解的方案。

### 思路

首先，我们能确定：$\text{Lyndon}$ 分解一定存在且唯一。

用构造法证明：首先，找出最小后缀，作为一个 $\text{Lyndon}$ 串。然后，在剩余字符串里一直重复此过程。一直到剩余的字符串为空为止。

首先，上述证明有解是显而易见的；其次，每次我们若不按照上述方法取的话，分两种情况：

* 取的一段比最小后缀长

  显然这个字符串不是 $\text{Lyndon}$ 串。

* 取的后缀比最小后缀短

  不满足 $\text{Lyndon}$ 串单调不升的定义。假设最小后缀从第 $i$ 个字符开始，那么 $i$ 位置必然作为一个 $\text{Lyndon}$ 串的开头（不然 $i$ 位置所处的那个串就不是 $\text{Lyndon}$ 串）。再由于当前是一段后缀，位置必定在剩下的所有分解的串之后，显然 $i$ 位置所处的那个 $\text{Lyndon}$ 串与当前后缀不满足不升序的关系。

故而只存在唯一解。

那我们该怎么求呢？

### 方法 $1$：后缀数组 $\text{SA}$

我们考虑按照上述构造法中规中矩地求。会发现求最小后缀一事可以对后缀进行排序，然后把所有的后缀丢进一个堆里，堆顶为拥有最小字典序的后缀。若我们发现堆顶的后缀是一个合法的后缀（假设当前的剩余字符串为 $1$ 到 $x$，然后堆顶是 $y$ 开头的后缀，合法当且仅当 $1 \leq y \leq x$），那么最小后缀就是它。否则删除堆顶元素，因为之后它也不可能合法了。

注：上述合法的定义表达的意思是堆顶的后缀与当前剩余的字符串有交，即产生的 $\text{Lyndon}$ 串不为空。

用倍增法求解，时间复杂度 $O(n \log n)$；若是 $\text{DC3}$ 算法，时间复杂度 $O(n)$。

### 方法 $2$：$\text{Duval}$ 算法

注意，本方法与上述构造法无关。

考虑正着求。我们将把字符串 $s$ 分为 $3$ 个部分：

1. $s1$ 表示前面已经分解完的 $\text{Lyndon}$ 串。
2. $s2$ 表示当前正在处理的 $\text{Lyndon}$ 串。
3. $s3$ 表示未分解、未在处理的剩下的串。

有 $s=s1+s2+s3$（$+$ 表示字符串拼接）。

$\text{Duval}$ 算法的思想就是每次保证 $s2$ 是 $\text{Lyndon}$ 串的情况下，且让 $s2$ 的元素越多越好。具体来说，是要维护一个周期，下面会有详细的讲解。

* 先给出以下定理：

  > 若 $a,b$ 都是一个 $\text{Lyndon}$ 串，且 $a<b$，那 $a+b$ 必定也是 $\text{Lyndon}$ 串。

  证明：考虑 $b$ 既然是 $\text{Lyndon}$ 串，那最小后缀必定为其本身。要想 $a+b$ 不是 $\text{Lyndon}$ 串，必定有 $a>b$，与条件不符。

于是我们设当前 $s2$ 的开头为位置 $i$，要考虑加入的字符为 $k$，当前 $k$ 与周期中的 $j$ 位置作比较，有以下三种情况：
1. $s_k=s_j$

	无事发生。
   $j$ 自增 $1$，$k$ 也自增 $1$，继续对下一个字符的比较。
2. $s_k>s_j$

	即当前的字符加入依旧是一个 $\text{Lyndon}$ 串（根据上述定理），由于字符的不一样，前面的所有周期加这个 $s_k$ 都变成同一个 $\text{Lyndon}$ 串。
    
   由于当前整个变成了一个新周期，继续从头开始比较，所以有：$j$ 赋值为 $i$，$k$ 自增 $1$。
3. $s_k<s_j$

	显然不再满足一个 $\text{Lyndon}$ 串的性质。假设 $t$ 为当前 $s2$ 中的一个周期，$t'$ 为 $t$ 的前缀，有 $s2=t+t+...+t+t'$，所以把之前的每个周期 $t$ 分解为一个 $\text{Lyndon}$ 串。对于 $t'$，继续和后面的字符做 $\text{Lyndon}$ 分解。
   
   若论更为具体的处理，我们有：
   * 周期长度为 $k-j$。
   * 从 $i$ 开始，一直加上这个周期，边加边统计答案 $i-1$。重复此操作直到 $i + (k-j) \leq k$（即 $k$ 前的最后一个周期），移项得 $i \leq j$。

时间复杂度 $O(n)$。假设每次寻找到的周期长度为 $len$，那么我们每次会处理掉那些完整的周期 $t$，最后的 $t'$ 留到下次去处理。发现 $t'$ 的长度必定不大于周期的长度。所以每删除一段，最多产生双倍的线性时间，且删除了就放入了 $s1$ 不会再恢复。故而为 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 5e6 + 10;
int n, i = 1, j, k, ans;
char s[N];
int main(){
    scanf("%s", s + 1), n = strlen(s + 1);
    while(i <= n){
        for(j = i, k = i + 1; k <= n && s[k] >= s[j]; k++)
            j = (s[k] == s[j]? j + 1 : i);
        for(; i <= j; i += k - j, ans ^= i - 1);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：guodong (赞：4)

本文为对 `xht37` 以及 `wucstdio` 博客的补充、解释。
## 定义
若一个字符串的最小表示是它本身，那么这个字符串就是一个$\rm Lyndon$ 串。

考虑字符串 $S$ ，倘若我们把它分成：$\text{S} = a_1a_2a_3a_4 \dots a_n$ ，若满足：

- 每一个 $a_i$ 都是 $\rm Lyndon$ 串。
- 按照字典序比较，$a_i > a_{i+1}$。

那么我们就称 $a_1a_2a_3\dots a_n$ 是字符串 $S$ 的 $\rm Lyndon $ 分解。**可以证明一个字符串有且仅有一个 $\rm Lyndon$ 分解**。

并且一个 $\rm Lyndon$ 串的 $\rm Lyndon$ 分解是它本身。

## 求解

__定义__：若字符串 $w'$ 为 $\rm Lyndon$ 串 $ w$ 的前缀，我们就称 $w'$ 为一个**近似$\rm Lyndon$ 串**

$\rm Duval$ 算法的概括：在一个循环 $\rm Lyndon$ 串与近似$\rm Lyndon$串 （即$ww\dots w w+ w'$）中 , 加入一个新的字符，对以下`3` 种情况进行讨论：
1. 近似 $\rm Lyndon$ 串变长。(也可能因为加入这个字符之后近似$\rm Lyndon$ 串变成了一个真正的 $\rm Lyndon$ 串。）
2. 成为一个新的 $\rm Lyndon$ 串。
3. 不满足前两点，此时 $[i,k)$ 为一个新的 $\rm Lyndon$ 分解。


设 `3` 个指针 $i,j,k$

$i$ 为循环 $\rm Lyndon$ 串的起始位置 ,

$j$ 为 $k$ 对应的循环 $\rm Lyndon$ 串位置 ，

$k$ 为我们考虑的新加字符。

考虑以下 `3` 种情况：
1. `S[j] == S[k]`
2. `S[j] > S[k]`
3. `S[j] < S[k]`

按照上面所述的讨论方法讨论即可。（序号依次对应）

代码实现大同小异（由于长度短）
```cpp
signed main()
{
	scanf("%s",S);
	int n = strlen(S);
	int i = 0 , j = 1, k = 0,ans = 0;int lstans = 0;
	while(i < n){
		j = i, k = i + 1;
		while(S[j] <= S[k] && k < n){
			if(S[k] == S[j])
				++j;
			else
				j = i;	
			++k;
		}
		while(i <= j){
			i += k - j;
		//	putchar(' ');lstans = i ;
			ans ^= i;
		}
	}
	printf("%d\n",ans);
	return 0;
}

---

## 作者：约瑟夫用脑玩 (赞：3)

其实模板题不用卡得这么紧吧，只要复杂度不对的算法过不去就行了。

这里提供一种 $O(n)$ 但被卡常的做法，说优势的话除了好想啥也没有，劣势就是性质少了许多，不太能扩展，不过做模板够了。

> 如果在考场碰到 $\mathrm{Lyndon}$ 分解模板但是忘了 $\mathrm{Duval}$ 算法怎么办？

首先回忆一下 $\mathrm{Lyndon}$ 分解存在性：

> 如果串 $u$ 与 $v$ 都是 $\mathrm{Lyndon}$ 串且 $u<v$，则 $uv$ 也是 $\mathrm{Lyndon}$ 串。
>
> 初始令 $m=|S|$ 并且 $A_i=S[i]$，然后每次不断找到 $A_i<A_{i+1}$ 并且合并为一个串，最后一定能使得所有的 $A_i\ge A_{i+1}$。

为了使我们的算法有序进行，我们从后往前不断找到第一个 $A_i<A_{i+1}$ 并且合并为一个串。

先不考虑判断两个子串大小的复杂度，发现至多只会进行 $O(n)$ 次合并，故复杂度 $O(n)$。

只差判断两个子串大小了，由于我不会后缀数组，于是我用了后缀自动机。

正常跑反串把后缀自动机建出来，然后用 $O(n)-O(1)$ 最近公共祖先拿出来，对于两个子串我们可以 $O(1)$ 的求出它们的 $LCP$。

由于与合并相同，至多只会判断 $O(n)$ 次，故复杂度仍为 $O(n)$。

不会真的有人要看[被卡常](https://www.luogu.com.cn/record/64153141)的[代码](https://www.luogu.com.cn/paste/l14ys87r)吧？

注：由于普通的后缀自动机会被卡，代码实现的是 $O(n\times \log{26})$ 的后缀自动机，然后还是被卡了就没办法了。

 _附：为什么被卡了？_ 
 
 _以下偷换一下概念，用 $O(A)-O(B)$ 代表空间复杂度为 $A$，时间复杂度为 $B$。_ 
 
 _由于字符集大小，后缀自动机其实是 $O(n\times \log{26})-O(n\times \log{26})$ 或是 $O(n26)-O(n)$ 的。_ 
 
 _而且光是算法常数差不多就有 $5$ 倍了。_ 

---

## 作者：Glacial_Shine (赞：1)

~~模拟赛考 runs，于是学 runs，于是学 Lyndon 分解。~~

## Lyndon Word

首先，我们先要知道什么是 Lyndon Word。

> 若字符串 $S$ 的所有严格后缀（即不等于 $S$ 的后缀）都大于 $S$，则称 $S$ 为 **Lyndon Word**。

为了后面好证明先规范几个符号。

- 对于字符串 $A$ 和 $B$，$AB$ 即将 $A$ 和 $B$ 拼接后形成的字符串，$A^k$ 为将 $A$ 重复拼接 $k$ 次后形成的字符串。
- 对于字符串 $A$ 和 $B$，$A < B$ 表示 $A$ 的字典序小于 $B$。
- 对于字符串 $A$，$A[i]$ 表示其第 $i$ 位的字符。

在知道 Lyndon 分解之前，我们还需要几个定理。

- **定理 1**：对于任意一个 Lyndon Word $S = AB$（$A$ 与 $B$ 均非空），都有 $A < B$。

  **证明**：我们知道 $AB < B$（Lyndon Word 的定义），$A < AB$，则 $A < AB < B$，证毕。
  
- **定理 2**：对于四个字符串 $A,B,C,D$，若 $A < B$ 且 $A$ 不为 $B$ 的前缀，则 $AC < BD$。

  **证明**：比较显然，因为 $A < B$ 且 $A$ 不为 $B$ 的前缀，则存在一个 $i$ 使得 $A[i] < B[i]$，则无论后面的字符串长啥样，都有前一个字符串小于后一个字符串，则自然可以在后面加字符。

- **定理 3**：对于两个 Lyndon Word $A,B$，若有 $A < B$，则 $AB$ 是 Lyndon Word。

  **证明**：假设 $A, B$ 的严格后缀分别为 $A', B'$，因为 $A < A'$，由定理 2 得，$AB < A'B$，因为 $A < B < B'$，则 $AB < B'$，又因为 $A < B$，则 $AB$ 是 Lyndon Word。（其所有严格后缀都小于其本身）

## Lyndon 分解的性质

首先我们要知道什么是 Lyndon 分解
> 字符串 $S$ 的 Lyndon 分解就是将其分解成 $s_1, s_2, \cdots, s_n$，其中 $s_i$ 为 Lyndon Word 且有 $s_1 \geq s_2 \geq \cdots \geq s_n$。

一个字符串的 Lyndon 分解是唯一的，且任意一个字符串皆有 Lyndon 分解，下面证一下。

- 对于 Lyndon 分解一定存在，我们可以把一个长为 $n$ 的字符串 $S$ 先分解成 $n$ 个字符，设为 $s_1,s_2,\cdots, s_n$，对于任意两个相邻的字符串，若存在 $s_{i - 1} <s_i$，则将两个字符串合并，由于定理 3 得知，合并后的字符串一定是 Lyndon Word，则最后一定剩下的字符串一定满足 $s_1 \geq s_2 \geq \cdots \geq s_m$ 且都为 $Lyndon Word$，此时的 $m$ 个字符串就是 Lyndon Word。

- 对于 Lyndon 分解唯一，可以考虑反证，留给读者自己思考。~~（其实是太懒了懒得写，啥时候兴致大发来补了它）~~

## 求 Lyndon 分解

根据 Lyndon Word 分解是唯一的证明，我们可以得到一个做法，即每次从头到尾开始合并，如果一次扫描没有合并任何两个字符串，则退出。

但是此时的时间复杂度并不是很优，考虑其他做法。

有一种 $O(n)$ 的做法，名叫 **Duval**。

对于一个字符串 $S$，我们从前往后一个一个考虑。

假设我们考虑完前 $i-1$ 个字符，$[1,p-1]$ 的字符串已经分解完成，我们将 $[p,i-1]$ 中的字符串形式为 $u^ku'$。（其中，$u$ 是Lyndon Word，$u'$ 是 $u$ 的前缀）在往后考虑的过程中，我们要一直维护这个形式。

接下来考虑第 $i$ 个字符，我们设 $j=(i-p) \% |U| + 1$，即是将他拼接到 $u'$ 后对应 $u$ 的哪个字符。

有三种情况。

- 若是第 $i$ 个字符与 $u'$ 拼接后还是 $u$ 的前缀，即 $S[i] = u[j]$，此时直接继续维护 $u^ku'$ 的形式就好了。
- 若 $S[i] < u[j]$，此时则有 $u's[i] < u$，对于后面拼接任意一个字符串 $t$，由于定理 2，得到 $u's[i]t < u^ku's[i]t$，所以不可能为 Lyndon Word。此时前面 $k$ 个 $u$ 即是已经分好的 Lyndon Word，我们直接将其记录下来，然后将 $p$ 加上 $k|u|$，并且 $i$ 重新从 $p$ 开始考虑。
- 若 $S[i] > u[j]$，由定理 得 $u's[i]$ 是一个 Lyndon Word，又因为 $u < u's[i]$，所以我们可以将这些字符串全部合并，变成一个新的 Lyndon Word。

于是，你就会了 **Duval** 了。

接下来，回到这一题，会发现这道题就是板子。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[5000005];
int n, ans;
int main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	s[n + 1] = -1e9;
	for (int i = 2, p = 1, len = 1, k = 1; i <= n + 1; ) {
		int j = (i - p) % len + p;
		if (s[i] == s[j])
			i++;
		else if (s[i] > s[j])
			len = i - p + 1, i++;
		else {
			for (; p + len <= i; p += len)
				ans = ans ^ (p + len - 1);
			i = p + 1, len = 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

参考资料：

- [《Lyndon & Runs》- command_block](https://www.luogu.com/article/d4y3zqqv)

---

## 作者：kuikuidadi (赞：0)

# 思路
Lyndon 分解可以将一个字符串分为若干个 Lindon 串，并且前一个 Lindon 串的字典序大于等于后一个 Lyndon 串的字典序。

用三个指针维护：$i,k,j,l$ 分别维护新的 Lyndon 串的起始位置，当前枚举到的位置，维护从 $i$ 开始的字符串到 $k$ 的最短的 Lyndon 循环，那么如果  $s_k=s_j$ 的话，$j+1,k+1$ 维护循环长度。

例如：abcabc

$k$ 在 $3$ 的时候，$j=0$，$k$ 在 $4$ 的时候 $j=1$，$k$ 在 $5$ 的时候 $j=2$。

1. 那么如果 $s_k=s_j$ 的话，$j+1,k+1$ 维护循环长度。

2. $s_j<s_k$ 的话，表示从 $i$ 开始变成了一个新的 Lyndon 串。

例如：abcabd

$k=3$ 时，$j=0$，$k=4$ 时，$j=1$，$k=5$ 时，$j=0$。

因为 Lyndon 分解是要保证前一个 Lyndon 串的字典序大于等于后一个串的字典序，所以 abd 把 abc 合并了。

3. $s_j>s_k$，也就说明后面的循环的 Lyndon 串要小于前面的了，于是循环结束，以后面的循环开始下一个 Lyndon 分解。

例如：abcabb

$k=5$ 时，$j=3$，发现 $s_k$ 比较小，于是爆炸，然后 $i$ 从 $3$ 开始，$j$ 从 $3$ 开始，$k$ 从 $4$ 开始重新 Lyndon 分解。

可证 Lyndon 分解的时间复杂度是 $O(n)$ 的。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
char s[10000007];
vector<int> g;
int ans;
void lyndon(char *s){
	int n=strlen(s);
	for(int i=0;i<n;){
		int j=i,k=i+1;
		while(k<n&&s[j]<=s[k]){
			if(s[j]==s[k]) j++;
			else j=i;
			k++;
		}
		while(i<=j){
			i+=k-j;
			ans^=i;
			g.push_back(i-1);
		}
	}
}
int main(){
	cin>>s;
	lyndon(s);
	cout<<ans;
}
```

---

## 作者：larsr (赞：0)

参考 <https://www.luogu.com.cn/article/lt2rnl6d>。

**Lyndon 串**：字符串 $S$ 是 Lyndon 串当且仅当 $S$ 是 $S$ 所有后缀中最小的。

**Lyndon 分解**：将 $S$ 分解成 $s_1s_2\ldots s_k$，满足 $s_i$ 是 Lyndon 串，并且 $s_i\ge s_{i+1}$。

**引理 $1$：如果字符串 $u,v$ 都是 Lyndon 串，并且 $u<v$，那么 $uv$ 也是 Lyndon 串。**

若 $uv < v$，那么 $uv$ 就是 Lyndon 串，对于 $v$ 所有后缀 $v^\prime\ge v>uv$，即正确。分类讨论：
- $|u|\ge|v|$，那么在第 $|v|$ 个字符之前 $u$ 和 $v$ 就已经出现了不同字符，$uv < v$。
- $|u|<|v|$，若 $u$ 不是 $v$ 的前缀，那么和上面一样，$uv<v$。否则，因为 $v$ 是 Lyndon 串，$v<v[|u|+1:]$，那么 $uv<v$。

**引理 $2$：Lyndon 分解有且仅有一个。**

>**存在性**：考虑构造方案，先字符串分解成单个字符，若 $s_i < s_{i+1}$，则合并 $s_i$ 和 $s_{i+1}$，所有必定有解。

> **唯一性**：假设有两个不同的分解方案，如下
>
> $$S=s_1s_2\ldots s_is_{i+1}s_{i+2}\ldots$$
> $$S=s_1s_2\ldots s_is^\prime_{i+1}s^\prime_{i+2}\ldots$$
>
> 不妨设 $|s_{i+1}|>|s^\prime_{i+1}|$。可知 $s_{i+1}=s_{i+1}^\prime\ldots s_{i+k}^\prime[:l]$，那么可以得到以下：
>
> $$s_{i+1} < s_{i+k}^\prime[:l] \le s_{i+k} \le s_{i+1}^\prime <s_{i+1}$$
>
> 明显矛盾，故 Lyndon 分解只存在一个。

**引理 $3$：$c$ 是一个字符，$vc$ 是一个 Lyndon 串的前缀，若字符 $d$ 满足 $d>c$，那么 $vd$ 是一个 Lyndon 串**。

因为 $v[i:]+d>v[i:]+c>vd$，故成立。

**Duval 算法**：

考虑已经确定了前缀 $i-1$ 的 Lyndon 分解，目前考虑 $S[i,k]$。$S[i,k-1]$ 可以分解成 $t^hv$，$t$ 是 Lyndon 串，并且 $v$ 是 $t$ 的前缀或空串，并且 $s_g>t$。设 $j=k-|t|$

考虑加入字符 $s_k$：
- $s_j=s_k$，$t$ 保持不变，$|t^hv|$ 增大 $1$。
- $s_j<s_k$，让 $t^hv$ 成为新的 $t$。
- $s_j>s_k$，让 $h$ 个 $t$ 成为新的分解串，让 $v$ 变成新的 $t$。

```cpp
#include<cstdio>
#include<cstring>
#define N 5000010
using namespace std;
int n;
char s[N];
int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int ans = 0;
	for(int i = 1; i <= n;)
	{
		int j = i, k = i + 1;
		while(k <= n && s[j] <= s[k])
		{
			if(s[j] < s[k])j = i;
			else j++;
			k++;
		}
		while(i <= j)
		{
			ans ^= i + k - j - 1;
			i += k - j;
		}
	}
	printf("%d\n", ans);
	return 0;
}

```

---

## 作者：awdereye (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6114)

本题解讲解的方法是 Duval 算法。
### Duval 算法
Duval 是一种可以在 $O(n)$ 的时间复杂度完成字符串的 Lyndon 分解。对于任意的一个字符串 $s$ 可以分成 $a,b,c$ 三个部分:
- $a$ 在最前面，且 $a$ 为 Lyndon 串。
- $b$ 在中间，并且由多个循环节构成，每一个循环节都是 Lyndon 串，后面多余一部分为循环节的前缀。
- $c$ 为未处理部分。

所以我们只需要用 $i$ 进行遍历，$i$ 代表 $b$ 首字母的下标，每一次循环用 $j$ 代表向 $b$ 后插入的 $c$ 首字母的下标，$k$ 代表 $b$ 的上一个循环节的对应字符，所以会有一下三种情况：
-  $s[j]=s[k]$ 这代表将 $s[j]$ 加入进去若后面字符继续相同将成为又一个循环节，故 $j,k$ 自增即可。
- $s[j]>s[k]$ 之前的循环被破坏，但它还是一个 Lyndon 串，所以 $j$ 自增，$k=i$。
- $s[j]<s[k]$ 时前面的都不成立，所以不自增，而是跳出循环记录分解，每一次都是一个一个循环节地增加 $i$，然而此时一个循环节的长度正好是 $j-k$。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=5*1e6+1;
int cnt;
char s[N];
int main(){
		scanf("%s",s+1);
		for(int i=1;i<=strlen(s+1);){
			int j=0,k=0;
			for(j=i+1,k=i;j<=strlen(s+1)&&s[k]<=s[j];){
				if(s[j]==s[k]){
					k++;
				} else{
				k=i;
				}j++;
			}
			while(i<=k){
				cnt^=i+j-k-1;
				i+=j-k;
			}
		}
		cout<<cnt;
		return 0;
} 
```
注：本题解代码需要 O2 优化，因字符串过长所以不用字符串类型。

---

