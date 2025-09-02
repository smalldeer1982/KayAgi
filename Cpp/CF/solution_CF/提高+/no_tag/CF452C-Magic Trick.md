# Magic Trick

## 题目描述

Alex enjoys performing magic tricks. He has a trick that requires a deck of $ n $ cards. He has $ m $ identical decks of $ n $ different cards each, which have been mixed together. When Alex wishes to perform the trick, he grabs $ n $ cards at random and performs the trick with those. The resulting deck looks like a normal deck, but may have duplicates of some cards.

The trick itself is performed as follows: first Alex allows you to choose a random card from the deck. You memorize the card and put it back in the deck. Then Alex shuffles the deck, and pulls out a card. If the card matches the one you memorized, the trick is successful.

You don't think Alex is a very good magician, and that he just pulls a card randomly from the deck. Determine the probability of the trick being successful if this is the case.

## 说明/提示

In the first sample, with probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF452C/11122857c8fbc4142ef5e22b839ee7f4cb432c56.png) Alex will perform the trick with two cards with the same value from two different decks. In this case the trick is guaranteed to succeed.

With the remaining ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF452C/c171d3ec3c02b9089b571e24a262c7ab1c15c85e.png) probability he took two different cards, and the probability of pulling off the trick is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF452C/fda96725ccc697b767e5edbf0d5cfb5ba17d9aa2.png).

The resulting probability is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF452C/a205e249fe823af48892b89b115b150661d33162.png)

## 样例 #1

### 输入

```
2 2
```

### 输出

```
0.6666666666666666
```

## 样例 #2

### 输入

```
4 4
```

### 输出

```
0.4000000000000000
```

## 样例 #3

### 输入

```
1 2
```

### 输出

```
1.0000000000000000
```

# 题解

## 作者：AKPC (赞：8)

### 题意
有 $nm$ 张牌，共 $n$ 种颜色，每种都有 $m$ 张。

现在小 A 从 $nm$ 张牌中抽取 $n$ 张牌，然后从这 $n$ 张牌中抽 $1$ 张，记录这个颜色，然后放回去再抽 $1$ 张，记录这个颜色。问两种颜色相同的概率。
### 思路
- 如果这 $n$ 张牌中放回性地抽 $2$ 次是同样的牌，那么概率为 $\dfrac{1}{n}$。

- 如果牌不相同，但是颜色相同，显然不是同一张概率为 $\dfrac{n-1}{n}$，除了第一次抽的牌，剩余牌中颜色与这张牌相同的概率为 $\dfrac{m-1}{nm-1}$（相同颜色牌有 $m$ 张，除开第一次抽的有 $m-1$ 张，总共剩余 $nm-1$ 张）。

由于两种情况独立，那么把这两种的概率相加即可，即 $\dfrac{1}{n}+\dfrac{n-1}{n}\times\dfrac{m-1}{nm-1}$。

注意特判，当 $n=m=1$，结果为 $1$，因为只可能抽这一张牌。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
double n,m;
int main(){
	cin>>n>>m;
	if (n==1&&m==1) cout<<1;
	else printf("%.15lf",(n-1)/n*(m-1)/(n*m-1)+1.0/n);
	return 0;
}
```


---

## 作者：wxzzzz (赞：3)

### 思路

本题显然是一道概率题，先简单介绍概率中的事件：

- 和事件：记作 $A\cap B$ 或 $A+B$，当且仅当事件 $A$ 和事件 $B$ 至少一个发生时，事件 $A\cup B$ 发生。

- 积事件：记作 $A\cap B$ 或 $AB$，当且仅当事件 $A$ 和事件 $B$ 同时发生时，事件 $A\cap B$ 发生。

- 互斥事件：记作 $A\cap B=\varnothing$，事件 $A$ 和事件 $B$ 的交集为空，即不能同时发生

- 对立事件：$A\cup B=S$ 且 $A\cap B=\varnothing$，整个样本空间仅有事件 $A$ 和事件 $B$，即每次实验必有一个且仅有一个发生。

然后，可以将答案分为两部分：

1. **抽到的两张牌是同一张**

	因为一共有 $n$ 张牌，概率为 $\dfrac{1}{n}$。

1. **抽到的两张牌不是同一张但点数相同**
	
   抽到的两张牌不是同一张的概率显然是 $\dfrac{n-1}{n}$。
   
   一种牌共有 $m$ 张，抽走一张还剩 $m-1$ 张，一共有 $n×m$ 张牌，抽走一张还剩 $n×m-1$ 张，因此点数相同的概率是 $\dfrac{m-1}{n×m-1}$。

	此部分的两个条件是积事件，相乘就是此部分成立的概率，为 $\dfrac{n-1}{n}×\dfrac{m-1}{n×m-1}$。

可以发现，这两个部分答案满足 $A\cap B=\varnothing$，为互斥事件，因此把它们加起来就是完整的答案。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
double n, m;
int main() {
    cin >> n >> m;

    if (n == 1 && m == 1)
        cout << '1';
    else
        cout << 1 / n + (n - 1) / n*(m - 1) / (n * m - 1);

    return 0;
}
```

---

## 作者：Grisses (赞：2)

你有 $m$ 副相同牌，每一副有 $n$ 张带有不同数值的牌，从所有牌里面选出来 $n$ 张，再在这 $n$ 张牌先后里面选两张（可以是同一张），求这两张牌上的数值是相同的的概率。

首先，我们考虑两次选的是同一张牌，概率为 $\dfrac{1}{n}$。这是因为，当我们先选了一张牌之后就必须再选它。

然后，我们考虑第二次选的牌不是原来的那一张，但是只与其相同。不是同一张的概率为 $\dfrac{n-1}{n}$，这很明显。然后在剩下的 $nm-1$ 张牌中，有 $m-1$ 张牌的数值与第一次选的牌相同，选中的概率为 $\dfrac{m-1}{n\cdot m-1}$。所以这种情况的概率为 $\dfrac{n-1}{n}\times \dfrac{m-1}{n\cdot m-1}$。

最后，我们把两种情况的概率加起来就行了。

**注意：当 $n=m=1$ 时需要特判，这时的答案为 1。**

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,m;
  signed main()
  {
      scanf("%d%d",&n,&m);
      if(n==1&&m==1)puts("1");//特判
      else printf("%.15lf",1.0/n+1.0*(n-1)/n*(m-1)*1.0/(n*m*1.0-1)*1.0);//输出
      return 0;
  }
```

---

## 作者：cysxc11111 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF452C)

------------
**题目大意**

有 $m$ 个桌子，每一个桌子有 $n$ 张卡牌，从这 $m\times n$ 个卡牌中选出 $n$ 张。然后，从这 $n$ 张选中一张，记住点数，重新洗牌。请问再次抓中相同点数的牌的概率。

**解题思路**

这道题需要运用概率求法。对于这选出来的 $n$ 张卡牌，抽一次再抽中原来的那张的概率是 $\dfrac{1}{n}$，剩下求不是原来那张而且最后点数相同的概率。

不是原来的那张概率为 $\dfrac{n-1}{n}$，剩下点数和原来的相同，即从剩下 $m-1$ 个相同的卡牌中选。剩下 $m\times n-1$ 的卡牌等概率出现在 $n-1$ 张卡牌中。

所以该率式 $=(n-1)÷n\times (m-1)÷(m\times n-1)$。

最后得出成功概率 $=\dfrac{1}{n}+ \dfrac{n-1}{n}\times \dfrac{m-1}{m\times n-1}$。

**代码如下**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	if(n==1&&m==1){
		cout<<1;
		return 0;
	}
	double ans=1.0/n+(double)(n-1)/(double)(n)*(m-1)/(n*m-1);
	printf("%.9lf\n",ans);
	return 0;
}
/*Code in*/
```

完结撒花~

---

## 作者：zhanghaosong (赞：1)

# CF452C Magic Trick 题解

小学数学题。

[蒟蒻的AC记录](https://www.luogu.com.cn/record/120438957)|[本题 in 洛谷](https://www.luogu.com.cn/problem/CF452C)|[本题 in CF](https://codeforces.com/problemset/problem/452/C)

### 题意简化

共有 $mn$ 张牌，牌上的数字分别为 $1,1,1,\dots n,n,n$（其中每一种数字共有 $m$ 张）。现在任意抽出 $n$ 张。抽取一张牌并放回，再抽一张，求这两张牌的数字一样的概率。

### 推导

（敲黑板）以下是重点 $\downarrow$。

1. 如果抽两次牌正好是同一张，概率很好算，是 $\frac{1}{n}$。

1. 如果不是同一张牌，但是牌上的数字相同，概率为 $1-\frac{1}{n}=\frac{n-1}{n}$。此时还剩 $mn-1$ 张（易知），与前一张数字相同的有 $m-1$ 张，那总概率就好算了，即 $\frac{n-1}{n}\times\frac{mn-1}{m-1}$。

对于两种互不重合的情况，直接相加即可得答案。其实我们完全不用化简出来，直接带入数字计算即可。记得保留 $6$ 位小数。

### 小坑

当 $n=m=1$ 的时候，易知抽出同一张牌的概率为 $100\%$，要输出 `1`。

### 代码

这么简单的题还需要代码？！（逃逸）

---

## 作者：zyh888 (赞：1)

## 题意
有 $m$ 套相同的牌，每套牌有 $n$ 张互不相同的牌。将这 $m$ 套牌混合在一起后等概率随机地从中抽取 $n$ 张，并从抽出的 $n$ 张牌中等概率随机放回地抽取两张牌，求这两张牌相同的概率。
## 思路
- 当 $n=1$ 时需要特判，因为在一张牌中抽一张牌就只有一种情况。

- 将概率分为两部分
	
     1、在选完 $n$ 张牌后，随机放回一张牌，另外一张牌有 $\frac{1}{n}$ 的概率与这张牌一样，这一部分的概率即为 $\frac{1}{n}$。
    
    2、还有 $\frac{n-1}{n}$的概率选的与第一张不同，那现在只需在除去第一次放回的牌中，选一张与放回的那张牌相同的牌，也就是在 $n*m-1$ 张牌中选出一张与第一次放的牌相等的牌，而这张牌还剩 $m-1$ 张(原本每张牌都有 $m$ 张，扣去第一次放回的那张牌还剩 $m-1$ 张牌可以选)。这部分的概率是：$\frac{n-1}{n} *\frac{m-1}{n*m-1}$。
    
# code
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	double n,m;
	scanf("%lf%lf",&n,&m);
	if(n==1) return !printf("1");
	printf("%.6lf",1.0/n+(n-1)/n*(m-1)/(n*m-1));
	return 0;
}
```



---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF452C)
## 前置知识：概率
### 概率的几种不同的事件与关系：
- 事件：随机试验 $E$ 的样本空间 $\Omega$ 的子集(或某些样本点的子集），称为 $E$ 的随机事件，简称事件。

- 必然事件：在一定的条件下重复进行试验时，有的事件在每次试验中必然会发生，这样的事件叫必然事件，必然事件的概率为 $1$。

- 不确定事件：概率中把在一定条件下可能发生的事件叫不确定事件，不确定事件的概率位于区间 $(0,1)$ 中。

- 不可能事件：不可能事件是概率论中把在一定条件下不可能发生的事件叫不可能事件。不可能事件的概率为 $0$。

- 包含关系：一般地，对于事件 $A$ 与事件 $B$，如果事件 $A$ 发生，则事件 $B$ 一定发生，这时称事件 $B$ 包含事件 $A$（或称事件 $A$ 包含于事件 $B$）。记为 $A \subseteq B$ 或者 $B \supseteq A$。

- 相等关系：一般地，对事件 $A$ 与事件 $B$ ，若 $A \subseteq B$ 且 $B \subseteq A$，那么称事件 $A$ 与事件 $B$ 相等，记作 $A=B$。

- 并事件（和事件）：事件 $A$ 或事件 $B$ 中至少有一个发生的充要条件，则称此事件为事件 $A$ 与事件 $B$ 的并事件（和事件），记作 $A+B$ 或 $A \cup B$。

- 交事件（积事件）：事件 $A$ 或事件 $B$ 同时发生的充要条件，则称此事件为事件 $A$ 与事件 $B$ 的交事件（积事件），记作 $AB$ 或 $A \cap B$。

- 互斥事件：若 $A \cap B$ 为不可能事件，那么称事件 $A$ 与事件 $B$ 互斥，其含义是：事件 $A$ 与事件 $B$ 在任何一次试验中都不会同时发生。

- 对立事件： 若 $A \cap B$ 为不可能事件，$A \cup B$ 为必然事件，那么称事件 $A$ 与事件 $B$ 互为对立事件，其含义是事件 $A$ 与事件 $B$ 在任何一次试验中有且仅有一个发生。

### 古典概率，主观概率与试验概率
**古典概率**

$\,\,\,\,\,\,\,\,\,\,$古典概率通常又叫事前概率，是指当随机事件中各种可能发生的结果，及其出现的次数都可以由推理得知，而无需经过任何统计试验即可计算各种可能发生结果的概率。古典概率是以这样的假设为基础的,即随机现象所能发生的事件是有限的、互不相容的,而且每个基本事件发生的可能性相等。一般说来,如果在全部可能出现的基本事件范围内构成事件 $A$ 的基本事件有 $a$ 个,不构成事件 $A$ 的事件有 $b$ 个,则出现事件 $A$ 的概率为:

$$P(A) =\frac{a}{a + b}$$

**主观概率**

$\,\,\,\,\,\,\,\,\,\,$主观概率，是指建立在过去的经验与判断的基础上，根据对未来事态发展的预测和历史统计资料的研究确定的概率。反映的只是一种主观可能性。

**试验概率**

$\,\,\,\,\,\,\,\,\,\,$在许多实际问题中，要将全部观察或试验结果列举出来往往是不可能的，同时，试验结果的等可能性假定也是很难成立的，难以按古典概率计算概率，而只能利用实际频数数据来估计概率。因此，根据大量的、重复的统计试验结果计算随机事件中各种可能发生结果的概率，称为试验概率或频率概率。

~~[以上摘自百度百科]~~

**那么接下来，我们开始看这道题**
## 题目
### 题意
有 $m$ 套相同的牌，每套牌有 $n$ 张互不相同的牌。将这 $m$ 套牌混合在一起后等概率随机地从中抽取 $n$ 张，并从抽出的 $n$ 张牌中等概率随机地抽取第 $1$ 张牌，抽完后记住这张牌，将这 $n$ 张牌放回，再取出 $n$ 张牌，同样取出第 $2$ 张牌记住，求这 $2$ 张牌相同的概率。
### 分析
这道题分为两种事件 $A$ 和 $B$，且这两种事件关系为并事件。

- $A$ 事件：取出的 $2$ 张牌为完全相同的一张牌，这一张牌被连续取出了 $2$ 次；

- $B$ 事件：取出的 $2$ 张牌为 $2$ 套牌中外观相同的 $2$ 张牌。

那么，整个事件的概率
$$ P(S) = P(A) + P(B)$$
接下来，我们分别计算 $A$ 事件与 $B$ 事件的概率：

#### $A$ 事件：$P(A)$
为了方便理解，我们把 $n$ 张牌标号为 $1,2,3,\cdots,n$。

那么，假设我们第一次选出的牌是 $k$，这个事件 $C$ 发生的概率 $P(C)$ 为 $1$，因为我们一定会抽到一张牌；

在把第 $k$ 张牌放回去后，下一次再抽到第 $k$ 张牌的概率 $P(D)$ 为 $1 \over n$；

显而易见，事件 $C$ 与事件 $D$ 是一个交事件，因为事件 $A$ 只有事件 $C$ 和事件 $D$ 同时发生时才会发生，所以

$$
\begin{aligned}
P(A)
&= P(C) \cap P(D) \\
&= 1 \times {1 \over{n}}\\
&= {1 \over n}
\end{aligned}
$$

#### $B$ 事件：$P(B)$
为了方便理解，我们继续把 $n$ 张牌标号为 $1,2,3,\cdots,n$。

那么，为了与事件 $A$ 区分，我们必须保证抽出来的 $2$ 张牌不能是同一张牌，这个事件 $E$ 与事件 $C$ 为互斥事件，所以事件 $E$ 发生的概率 $P(E)$ 为 $1 - {1 \over n}$；

接下来讨论抽出的 $2$ 张牌外观一样但不是同一张牌的概率。

由古典概率的定义我们知道，本题无需任何试验便可以通过推理得出结论，且每种情况发生的概率相等，所以本题属于古典概率。

那么这个事件 $F$ 的概率 $P(F)$ 为抽出的 $2$ 张牌外观一样但不是同一张牌（符合条件的个数）与抽出的两张牌不是同一张牌（总个数）的比值。

- 不是同一张牌：总牌数有 $n \times m$ 张，那么抽出与第 $1$ 次不是一张的的牌，可以抽 $n \times m - 1$ 张牌

- 外观一样且不是同一张牌：所有的牌中，每一套牌都有一张相同的牌，我们记这 $m$ 套牌为 $1,2,\cdots,m$，那么假设抽出的第 $1$ 张牌位于第 $l$ 套牌中，那么第 $2$ 次所能抽出的牌可以在 $1,2,\cdots,l-1,l+1,\cdots,m$ 套中抽出相同的牌，可以抽 $m-1$ 张牌。

所以
$$P(F) = {{m - 1} \over {{n \times m} - 1}}$$

显而易见，事件 $E$ 与事件 $F$ 是一个交事件，因为事件 $B$ 只有在事件 $E$ 和事件 $F$ 同时发生时才会发生，所以
$$
\begin{aligned}
P(B)
&= P(E) \cap P(F) \\
&= ({1 - {1 \over n}}) \times {{{m - 1} \over {{n \times m} - 1}}}\\
&= {{n - 1} \over n} \times {{m - 1} \over {{n \times m} - 1}}\\
&= {{n \times m - n - m + 1} \over {{n^2} \times m} - n}
\end{aligned}
$$

那么
$$
\begin{aligned}
P(S)
&= P(A) + P(B) \\
&= {{1 \over n} + {{n \times m - n - m + 1} \over {{n^2} \times m} - n}}\\
&= {{{n \times m - 1} \over {n^2 \times m - n}} + {{n \times m - n - m + 1} \over {{n^2} \times m} - n}}\\
&= {{2 \times n \times m - n - m} \over {n^2 \times m - n}}\\
\end{aligned}
$$

这个式子是不能再化简了，但是学过初中数学的人都知道，分式的分母不能为 $0$；

当分母为 $0$ 时，
$${n^2 \times m - n = 0}$$
$${n^2 \times m = n}$$
$$\because n \neq 0$$
$$\therefore n \times m = 1$$

所以当 $n=1$，$m=1$ 时需要特判，很显然两次抽出的必然是同一张牌，答案为 $1$。

所以最终的答案为

$$
ans =
\begin{cases} {{2 \times n \times m - n - m} \over {n^2 \times m - n}} & n \neq 1\,\,\,or \,\,\,m \neq 1 \\
1 & n = 1,m = 1
\end{cases}
$$

接下来，就可以写出 AC 代码了。
### 代码
下面是 AC 代码：[AC 代码](https://www.luogu.com.cn/paste/ab1dm8xc)
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,m;
	cin >> n >> m;
	if(n == 1 && m == 1) cout << "1.0000000000000000" << endl;
	else
	{
		double ans = (2 * n * m - n - m) * 1.0 / (n * n * m - n);
		cout << setprecision(16) << ans << endl;
	}
}
```
我的 [AC](https://www.luogu.com.cn/record/121289676) 记录

## 关于翻译
另外，本题的翻译有些许歧义，会让~~大部分人~~我一开始理解不了，所以下面给一下我的翻译。 [翻译](https://www.luogu.com.cn/paste/pw2paslv)

## 题目描述
Alex 喜欢表演魔术，他有一个需要扑克牌的魔术。他有 $m$ 套相同的牌，每套牌中有 $n$ 张不同的牌，魔术表演前，Alex 会将所有牌洗匀。当 Alex 想要表演这个魔术时，他会从所有的牌中随机拿出 $n$ 张牌，并用这些牌表演这个魔术。他拿出的牌可能会有一模一样的牌。

魔术的原理本身如下：首先 Alex 会让你从牌组中随机选择一张牌。你拿出卡片并记下卡片，再把它放回卡牌堆里。然后 Alex 再次洗牌，从中拿出一张牌。如果这张卡片与你记住的卡片一样，那么这个魔术就成功了。

你并不认为 Alex 是一个很好的魔术师，他只是从所有牌中随机抽出一张牌。如果是这样的话，求出魔术成功的概率。

## 输入格式
输入仅有一行，由两个整数 $n$ 和 $m$ 组成，中间用空格分隔，$n$，$m$ 分别代表每个牌组中的牌数和牌的套数。

## 输出格式
输出仅有一个数，为 Alex 成功表演魔术的概率，保留 $16$ 位小数。误差不超过 $10^{-6}$ 即判为正确。

## 数据范围
$1 \leq n,m \leq 1000$

---

## 作者：Cathy_zy (赞：0)

# 题目大意
有 $mn$ 个纸牌，$n$ 个颜色，每个有 $m$ 张，从这 $n$ 张牌中分别抽 $2$ 次，求这两次牌面颜色相同的概率。




------------


[CF链接地址（双倍经验）](https://codeforces.com/problemset/problem/452/C)
## 正解想法
+ 如果两张牌为同样一张，总共 $n$ 张，所以概率为 $\frac{1}{n}$。
+ 则不是同一张的概率为 $\frac{n-1}{n}$，和剩余牌  $n\times m-1$ 与之相同的概率为 $\frac{m-1}{n\times m-1}$。


#### 综上所述公式为
$$\frac{n-1}{n}\times \frac{m-1}{n\times m-1} $$

### 正解代码

```c
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	if(n==1)printf("%.16lf",1*1.0);
	else printf("%.16lf",1/(n*1.0)+(n-1)/(n*1.0)*(m-1)/((n*m-1)*1.0));

return 0;
}

```
### 注意题目有坑：只有一张牌时，直接输出 $1$ 即可。


---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF452C)

我们来分析一下，我们发现，如果我们要同时计算 $2$ 张牌，那么是非常难计算的。（毕竟是两个啊）

我们怎么才能不同时计算两张牌的概率，而只计算一张呢？

我们发现，对于每一种牌，他们都具有对称性（每次都一样），所以我们可以先随便取出一张，再计算概率。

但是这里需要特判一下，因为题目中是放回地拿出，所以如果再次拿出了这一张，那么概率就是 $\displaystyle \frac 1 n$。这个概率最后加上就可以了。

那么，就还有 $\displaystyle \frac {n-1}n$ 的情况。我们的问题就成为了在 $n\times m-1$ 张牌中，有 $m-1$ 中情况可以成功，求成功的概率。

那这不是很简单吗？这一部分的概率就是 $\displaystyle \frac {m-1}{n\times m-1}$ 了。

我们总结一下公式：

$$\displaystyle \frac 1 n+\displaystyle \frac {m-1}{n\times m-1}\times \displaystyle \frac {n-1}n$$

我们提交一下，发现在第 $7$ 个点错了。怎么回事呢？我们发现他们的输入 $n$ 是 $1$。

我们在考虑一下特殊情况：

如果 $n$ 是 $1$，那么概率一定是 $100\%$，直接输出 $1$ 就可以了。

---
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b;
int main(){
	scanf("%lf%lf",&a,&b);
	if(a==1)printf("1");
	else printf("%.15lf",1/a+(a-1)/a*(b-1)/(a*b-1));
	return 0;
}
```


---

## 作者：qwq_hwc (赞：0)

## 题面翻译
有 $m$ 套相同的牌，每套牌有 $n$ 张互不相同的牌。将这 $m$ 套牌混合在一起后等概率随机地从中抽取 $n$ 张，并从抽出的 $n$ 张牌中等概率随机放回地抽取两张牌，求这两张牌相同的概率。

输出与答案误差不超过 $10^{-6}$ 即判为正确。
## 思路
假设有 $m$ 副牌，每副牌有 $n$ 个不同的值，再选两张，求选两张牌是同一张的概率。

如果两次选的是同一张牌，那么概率是 $\displaystyle \frac{1}{n}$ ，如果不是同一张，概率为 $\displaystyle \frac{n-1}{n}$ 。

在剩下的 $nm-1$ 张牌中选出一张与第一次放的牌相等的牌，（还有 $m-1$ 张）概率是 $\displaystyle \frac{n-1}{n} * \displaystyle \frac{m-1}{nm-1}$ 。

由此，我们可以列出 $(n-1)/n*(m-1)/(n*m-1)+1.0/n$ 的代码，但是注意，如果 $m$ 或 $n=$ 1时,要输出`1` 。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
double n,m;
int main(){
	cin>>n>>m;
	if (n==1&&m==1) cout<<1;
	else printf("%.15lf",(n-1)/n*(m-1)/(n*m-1)+1.0/n);
	return 0;
}
```

---

## 作者：zxh923 (赞：0)

# CF452C Magic Trick 题解

[题目传送门](https://www.luogu.com.cn/problem/CF452C)

### 题意翻译

有 $m \times n$ 张牌，有 $n$ 个种类，每个种类有 $m$ 张，现在抽一张放回，再抽一张，这张牌与第一张抽出的牌种类相同的概率是多少？

### 思路

有两种可能：

第一种，两次抽出的牌是同一张，概率为 $\frac 1n$。

第二种，两次抽出的牌不是同一张但种类相同，第一张概率为 $\frac {n-1}n$。此时还剩 $m \times n-1$ 张，相同种类的还剩 $m-1$张。总概率为 $\frac {n-1}n$ $\times$ $\frac {m \times n-1 }{m-1}$。其实我们也可以认为指的是抽完不放回。

所以根据加乘原理，把两个概率相加即可。

### 坑点

如果只有一张牌怎么办？输出 `1` 即可，因为只有一种可能：两次都抽到这一张牌。

### 代码

```cpp
#include<iostream>//有的时候不用万能头文件
double n,m;
int main(){
	scanf("%lf%lf",&n,&m);
	if(n==1&&m==1){
		printf("%d",1);
		return 0;
	}
	else{
		printf("%.7lf",(n-1)/n*(m-1)/(n*m-1)+1.0/n);//1.0可以进行强制转换	
	} 
	return 0;
}
```

### 完结撒花！

---

## 作者：jasonshen_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF452C)

一道简单的数学概率题。

首先分类讨论选两张牌时的不同情况。

- 拿相同位置上的：$\frac 1n$。
- 第二次拿不同位置上的，以为第一次已经拿了 $nm$，所以要从 $nm-1$ 张牌中选出 $m-1$ 张。

**综上所述，我们可以推出公式**：
$$

\frac 1n+\frac{ n-1}{n}\times\frac{m-1}{nm-1}
$$

下面的就是简单的输入输出和代入公式计算了，不再赘述。

**但是要注意**，当 $m=1$ 时，公式就化简变为：

$$
\frac{1}{n}
$$


AC CODE(-std=c++14 -O2)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main()
{
	cin>>n>>m;
	if(m==1)
	{
		cout<<fixed<<setprecision(16)<<1.0/(n*1.0);
		return 0;
	}
	cout<<fixed<<setprecision(16)<<1/(n*1.0)+(n-1)/(n*1.0)*(m-1)/((n*m-1)*1.0);
}

```

---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF452C)&[CF 链接](http://codeforces.com/problemset/problem/452/C)

## 题目简述

有 $m \times n$ 张牌，有 $n$ 个种类，每个种类有 $m$ 张，现在抽一张放回，再抽一张，求这张牌与第一张抽出的牌**种类相同**的概率。

## 思路

本题是一道**结论题**，我们来推一下公式。

首先需要特判一个点：只有 $1$ 张牌，即 $n = m = 1$，那么两次抽都会是这张牌，**所以概率为 $1$，输出 $1$ 即可**。

接着分类模拟：

1. 两次抽到的牌是**同一张牌**，则这种情况的概率为 $\frac{1}{n}$。

2. 两次抽到的牌**种类相同**，但**不是同一张**的概率为 $\frac{n - 1}{n}$，那么去除第一次抽的牌，第二张牌与第一张**种类相同**的概率为 $\frac{m - 1}{n \times m - 1}$。

因两种情况**互不相干**，故最终的概率为 $\frac{1}{n} + \frac{n - 1}{n} \times \frac{m - 1}{n \times m - 1}$。

下面是代码**参考**：

```cpp
#include<iostream>
using namespace std;

double n, m; // 建议直接用 double

int main() {
	cin >> n >> m;
	if(m == 1 && n == 1) return printf("1\n"), 0; // 特判概率为 1 的情况。
	printf("%.12lf\n", (n - 1) / n * (m - 1) / (m * n - 1) + 1.0 / n); // 推的公式
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/120595216)

$$\texttt{The End!}$$

---

## 作者：Astatinear (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF452C)

~~交了 n 次的 CE 代码。。~~

首先，我们考虑选出的两张牌中，如果我们选的是同一位置上的，就是 $\dfrac {1}{n}$ 的概率。然后在考虑选的不同位置上的，首先第二次选时，我们考虑先选任意一个，然后选完这个之后，要选出另一个相同的概率就是从剩下的 $n\times m-1$ 个数中选出的于其相同的 $m-1$ 个。

所以总概率就是将两个加起来，也就是 $\dfrac{1}{n}+\dfrac{n-1}{n}\times \dfrac{m-1}{n\times m -1}$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main()
{
	cin>>n>>m;
	if(m==1)
	{
		printf("%.10lf\n",1.0/(n*1.0));
		continue;
	}
	printf("%.8lf",1/(n*1.0)+(n-1)/(n*1.0)*(m-1)/((n*m-1)*1.0));
}
```

---

## 作者：灵茶山艾府 (赞：0)

关键思路是把抽牌的概率放到整体（$n\cdot m$ 张牌）上考虑，这样计算会简单许多。

把牌按从 $1$ 到 $n$ 的顺序编号，由于第一次可以抽到任意牌，不妨假设第一次抽到的牌为 $1$ 号牌，分两种情况讨论：

1. 前后抽的两张牌是同一张，这就相当于在 $n$ 张牌中抽到那一张牌，概率为 $\dfrac{1}{n}$；
2. 前后抽的两张牌不是同一张（概率为 $\dfrac{n-1}{n}$），且第二次抽到的牌为 $1$ 号牌。由于我们固定第一次抽到的牌为 $1$ 号牌，这相当于在剩下的 $n\cdot m-1$ 张牌中抽到其余的 $m-1$ 张 $1$ 号牌，概率为 $\dfrac{m-1}{n\cdot m-1}$

因此总概率为

$$
\dfrac{1}{n}+\dfrac{n-1}{n}\cdot\dfrac{m-1}{n\cdot m-1}
$$

注意要特判 $n$ 为 $1$ 的情况，此时概率为 $1$。

AC 代码（Golang）：

```go
package main
import ."fmt"

func main() {
	var n, m float64
	Scan(&n, &m)
	if n == 1 {
		Print(1)
		return
	}
	Printf("%.8f", (1+(n-1)*(m-1)/(n*m-1))/n)
}
```



---

