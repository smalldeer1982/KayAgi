# Guess the String

## 题目描述

This is an interactive problem. You have to use flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout), in Java or Kotlin — System.out.flush(), and in Python — sys.stdout.flush().

The jury has a string $ s $ consisting of characters 0 and/or 1. The first character of this string is 0. The length of this string is $ n $ . You have to guess this string. Let's denote $ s[l..r] $ as the substring of $ s $ from $ l $ to $ r $ (i. e. $ s[l..r] $ is the string $ s_ls_{l+1} \dots s_r $ ).

Let the prefix function of the string $ s $ be an array $ [p_1, p_2, \dots, p_n] $ , where $ p_i $ is the greatest integer $ j \in [0, i-1] $ such that $ s[1..j] = s[i-j+1..i] $ . Also, let the antiprefix function of the string $ s $ be an array $ [q_1, q_2, \dots, q_n] $ , where $ q_i $ is the greatest integer $ j \in [0, i-1] $ such that $ s[1..j] $ differs from $ s[i-j+1..i] $ in every position.

For example, for the string 011001, its prefix function is $ [0, 0, 0, 1, 1, 2] $ , and its antiprefix function is $ [0, 1, 1, 2, 3, 4] $ .

You can ask queries of two types to guess the string $ s $ :

- $ 1 $ $ i $ — "what is the value of $ p_i $ ?";
- $ 2 $ $ i $ — "what is the value of $ q_i $ ?".

You have to guess the string by asking no more than $ 789 $ queries. Note that giving the answer does not count as a query.

In every test and in every test case, the string $ s $ is fixed beforehand.

## 说明/提示

The example contains one possible way of interaction in a test where $ t = 2 $ , and the strings guessed by the jury are 011001 and 00111. Note that everything after the // sign is a comment that explains which line means what in the interaction. The jury program won't print these comments in the actual problem, and you shouldn't print them. The empty lines are also added for your convenience, the jury program won't print them, and your solution should not print any empty lines.

## 样例 #1

### 输入

```
2 // 2 test cases
6 // n = 6

0 // p[3] = 0

1 // q[2] = 1

4 // q[6] = 4

1 // p[4] = 1

1 // answer is correct
5 // n = 5

1 // p[2] = 1

2 // q[4] = 2

2 // q[5] = 2

1 // answer is correct```

### 输出

```
1 3      // what is p[3]?

2 2      // what is q[2]?

2 6      // what is q[6]?

1 4      // what is p[4]?

0 011001 // the guess is 011001


1 2      // what is p[2]?

2 4      // what is q[4]?

2 5      // what is q[5]?

0 00111  // the guess is 00111```

# 题解

## 作者：Brilliance_Z (赞：6)

[Luogu CF1765G Guess the String](https://www.luogu.com.cn/problem/CF1765G)

观察到交互器不是自适应的，$789$ 很接近 $n=1000$，且一次询问一定能确定至少 $1$ 个未知字符，于是猜测本题每次随机一种询问，一次询问尽可能地直接确定 $2$ 个未知字符。如果一次询问不能直接确定 $2$ 个未知字符，则再使用一次询问。

先使用一次询问 `1 2` 确定 $s_2$ 。

从 $s[3..4]$ 开始从左往右两个一对确定字符 $s[i-1..i]$。

随机一种询问 `op i`（$op\in[1,2]$），交互器回答 $j$。

- 若 $j≥2$，则可直接确定 $s[i-1..i]$。

若 $j<2$，看上去似乎只能确定 $s_i$，如果此时直接再使用一次询问 `op i-1`，就很容易通过构造字符串把询问次数卡到超过 $789$（e.g.串 $s$ 为 $011111\dots$）。现在的问题就在于没有充分利用已知的信息。

$s[i-1..i]:j(j\le 2)$ 与 $s[1..2],op$ 的关系如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ip2o53s4.png)

- 若 $j=1$ 且 $s_2=0$，或 $j=0$ 且 $s_2=1$ 时，依然可以唯一确定 $s[i-1..i]$。
- 否则，当前只能确定 $s_i$，需要再使用一次询问 `1 i-1` 确定 $s_{i-1}$。

当 $n$ 为奇数时，$s_n$ 没有和其他字符组成一对，最后还需要单独询问 `1 n` 确定 $s_n$。

计算询问的期望次数：根据上文的分析，因为每次随机一种询问，所以一次询问直接确定 $2$ 个未知字符的概率与字符串的内容无关，概率为 $\frac{1}{2}$。$s[3..n]$ 构成约 $\frac{n}{2}$ 对，故可省下约 $\frac{n}{2}\times\frac{1}{2}=\frac{n}{4}$ 次询问。所以询问的期望次数约为 $n-\frac{n}{4}=\frac{3n}{4}$，当 $n=1000$ 时需要约 $750$ 次询问。

[详细代码见云剪贴板。](https://www.luogu.com.cn/paste/s2tsxw24)

---

## 作者：cmk666 (赞：3)

[题目传送门](/problem/CF1765G)

观察到询问次数上界和 $n$ 差的并不远，比例大约在 $1.26$ 左右，启示我们要用一个询问来获得两个字符的关系。

先用一次询问问出 $p_2$ 来推断 $s_2$ 的值。

考虑当前所有 $[1,i-2]$ 的字符已经确定，询问 $p_i$：

- 若 $p_i\ge2$，则有 $s[i-1,i]=s[p_i-1,p_i]$；
- 若 $p_i=1$，则当 $s_2=\texttt{0}$ 时可推出 $s[i-1,i]=\texttt{10}$，否则无法确定；
- 若 $p_i=0$，则当 $s_2=\texttt{1}$ 时可推出 $s[i-1,i]=\texttt{11}$，否则无法确定。

询问 $q_i$ 同理：

- 若 $q_i\ge2$，则有 $s[i-1,i]=s[q_i-1,q_i]$ 的每个字符取反；
- 若 $q_i=1$，则当 $s_2=\texttt{0}$ 时可推出 $s[i-1,i]=\texttt{01}$，否则无法确定；
- 若 $q_i=0$，则当 $s_2=\texttt{1}$ 时可推出 $s[i-1,i]=\texttt{00}$，否则无法确定。

观察到询问 $p_i$ 和 $q_i$ 之后，必定会走到某一个分支里（$p_i$ 和 $q_i$ 不可能同时为 $0$ 或 $1$），所以只要至多两次询问就能确定相邻的两个字符。

虽然但是，这个做法在最坏情况下，一次询问平均还是只能问出一个字符，而且出题人有点脑子都会把你卡掉，所以还是过不去。

然而，如果我们每次询问，不是固定询问 $p_i$ 或 $q_i$，而是随机一个，这样没法构造数据来卡，期望就降到了平均 $1.5$ 次询问能问出两个字符，整个字符串期望问 $750$ 次左右，可以通过。

核心代码如下：
```cpp
int n, p[1009], q[1009], op, a, pos; char s[1009];
inline int query_p(int x) { /* 询问 p_x 的值 */ }
inline int query_q(int x) { /* 询问 q_x 的值 */ }
inline void ans() { /* 输出答案 s */ }
inline char qwq(char c) { return '0' + '1' - c; } // 取反
inline bool f(int op, int x, int y)
{       // 对于询问的分类讨论，返回 true 表示确定，反之不确定
	if ( op == 0 && y > 1 ) { s[x - 1] = s[y - 1], s[x] = s[y]; return true; }
	if ( op == 0 && !y && s[2] == '1' ) { s[x - 1] = s[x] = '1'; return true; }
	if ( op == 0 && y && s[2] == '0' ) { s[x - 1] = '1', s[x] = '0'; return true; }
	if ( op == 1 && y > 1 ) { s[x - 1] = qwq(s[y - 1]), s[x] = qwq(s[y]); return true; }
	if ( op == 1 && !y && s[2] == '1' ) { s[x - 1] = s[x] = '0'; return true; }
	if ( op == 1 && y && s[2] == '0' ) { s[x - 1] = '0', s[x] = '1'; return true; }
	return false;
}
mt19937 rnd(time(nullptr));
inline void work()
{
	memset(p, -1, sizeof(p)), memset(q, -1, sizeof(q));
	read(n), s[n + 1] = '\0', s[1] = '0', s[2] = query_p(2) ? '0' : '1';
	for ( int i = 3 ; i <= n ; i += 2 )
	{
		op = rnd() & 1, pos = i + ( i + 1 <= n ), a = op ? query_q(pos) : query_p(pos);
        // 随机问一个，如果能推断出来就不用再问第二次了
		if ( f(op, pos, a) ) continue;
		op = !op, f(op, pos, op ? query_q(pos) : query_p(pos));
        // 问第二次，可以证明这次 f 的返回值一定是 true，即一定可以确定这两位
	}
	ans();
}
int main() { int t; read(t); For(tt, 1, t) work(); return 0; }
```

---

## 作者：Purslane (赞：0)

# Solution

考虑用 $n-1$ 次操作确定整个序列。

很明显，我们从 $2$ 开始，每次询问 `1 i`。如果返回的值 $v \ge 1$，那么 $S_i=S_v$；否则，$S_i = 1$。

很明显，我们这么做“损失了很多信息”。

那么考虑每次询问第 $2$，$4$，$6$，$8$ 等偶数位置。

如果这时候返回的数值 $\ge 2$，那么一下子可以确定 $2k-1$ 和 $2k$ 两个位置；否则，你必定可以确定 $2k$ 的位置，而且特别的如果你确定了 $2k$ 这个位置和 $2$ 能匹配上，你还能确定第 $2k-1$ 位置的值（必定和第 $1$ 个位置不能匹配）。这样也许有可能用少于 $n$ 次操作确定所有数的位置。

但是出题人会卡，而且很容易卡。

但是你发现实际上，如果这个状态下我用第一种询问被迫进行两次，另一种操作最多进行一次。（这时候只能有 $a_{2k} \neq a_2$，而另一种操作要进行两次必须有 $a_{2k} = a_2$，这两个是矛盾的。）

因此我们随机选择到底是选用那种询问。

这样期望要用 $\dfrac{3}{4} n$ 次操作（在极端情况下，每个位置都有一半的概率是 $2$ 次操作）。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10;
int T,n,res[MAXN]; 
mt19937 myrand(【】);
int query_p(int n) {
	cout<<1<<' '<<n<<endl;
	int ans; cin>>ans;
	return ans;	
}
int query_q(int n) {
	cout<<2<<' '<<n<<endl;
	int ans; cin>>ans;
	return ans;	
}
int main() {
	cin>>T;
	while(T--) {
		cin>>n;
		int pos=2;
		if(query_p(2)==1) res[2]=res[1];
		else res[2]=res[1]^1;
		while(pos+2<=n) {
			pos+=2;
			if(myrand()%2==0) {
				int v=query_p(pos);
				if(v==pos-1) res[pos-1]=res[pos-2],res[pos]=res[pos-1];	
				else if(v>=2) res[pos]=res[v],res[pos-1]=res[v-1];
				else {
					if(v==1) res[pos]=0;
					else res[pos]=1;
					if(res[pos]==res[2]) res[pos-1]=res[1]^1;
					else {
						int v=query_p(pos-1);
						if(v) res[pos-1]=res[v];
						else res[pos-1]=1;
					}
				}
			}
			else {
				int v=query_q(pos);
				if(v==pos-1) res[pos-1]=res[pos-2]^1,res[pos]=res[pos-1]^1;
				else if(v>=2) res[pos]=res[v]^1,res[pos-1]=res[v-1]^1;
				else {
					if(v==1) res[pos]=1;
					else res[pos]=0;
					if(res[pos]==res[2]^1) res[pos-1]=res[1];
					else {
						int v=query_p(pos-1);
						if(v) res[pos-1]=res[v];
						else res[pos-1]=1;
					}
				}
			}
		}
		if(pos<n) {
			int v=query_p(n);
			if(v) res[n]=res[v];
			else res[n]=1;	
		}
		cout<<0<<' ';
		ffor(i,1,n) cout<<res[i];
		cout<<endl;
		cin>>n;
	}
	return 0;
}
```

---

