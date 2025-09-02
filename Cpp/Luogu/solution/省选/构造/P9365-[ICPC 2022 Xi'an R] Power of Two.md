# [ICPC 2022 Xi'an R] Power of Two

## 题目描述

SolarPea 喜欢通过发送电力塔来炸毁 PolarSea 的博客 $2$。由于塔太高，网页的堆栈溢出。所以博客已经不能用了。  

现在 SolarPea 拥有两个 $a_1、a_2、ldots、a_n$、$x$ 位 AND 运算符、$y$ 位 OR 运算符和 $z$ 位 XOR 运算符的 $n$ 次方。保证 $n = x + y + z$。  

Solarpea 希望使用这些数字和运算符构造一个算术表达式。正式地定义 $x_0 = 0$ 和 $x_i = x_{i - 1}\ \mathrm{op}_i\ b_i$，其中 $b$ 是 $a$ 的排列，这意味着我们可以重新排列 $a$ 来得到 $b$，而 $\mathrm{op}_i$ 是上述三种类型的按位运算符之一。那么 $x_n$ 就是表达式的结果。

表达式越大，就越有可能使 PolarSea 的博客无法工作。SolarPea 希望你帮他找到最大的 $x_n$ 并构造这样的表达式。如果有多个解决方案，则输出其中任何一个。

您需要独立处理 $T$ 个测试用例。

## 说明/提示

**来源**：2022 ICPC 亚洲习安区域赛问题 H.  
**作者**： Alex_Wei.

## 样例 #1

### 输入

```
4
4 3 0 1
1 0 1 0
4 1 0 3
1 0 1 0
8 0 2 6
1 5 5 7 1 5 5 7
8 0 0 8
1 5 5 7 1 5 5 7
```

### 输出

```
0010
&&^&
0 0 1 1
0011
^^&^
0 1 0 1
10100000
^^|^^^^|
1 5 5 7 1 5 5 7
00000000
^^^^^^^^
1 5 5 7 1 5 5 7
```

# 题解

## 作者：jun头吉吉 (赞：3)

## 题意
给定 $n$，长度为 $n$ 的序列 $\{a_i\}$ 和 $\{op_i\}$，其中 $a_i=2^{c_i}$，$\{op_i\}$ 由 $x$ 个与(&)，$y$ 个或(|)，$z$ 个异或(^)组成，现在 $x_0=0,x_i=x_{i-1}\ op_i\ a_i$，现在你需要重排 $a$ 和 $op$ 使得 $x_n$ 最大，给出最大值并构造一组方案。

多测，$0\le x,y,z\le 2^{16},\sum n\le 2^{20}$。

## 题解

我的做法好麻烦不知道有没有高论喵。

设 $buc_i$ 表示序列 $\{c_i\}$ 中 $i$ 出现的次数，$c$ 表示 $buc_i>0$ 的 $i$ 的个数，$cc$ 表示 $buc_i>1$ 的个数，$mn$ 表示最小的 $buc_i>0$ 的 $i$。

首先如果 $x=0$，那么不存在与操作，一位如果希望是 $1$，要么 $buc_i$ 是奇数，否则就需要用掉至少一次或操作。从高位往低位做，优先保证高位是一即可。

然后如果 $y+z<c$，那么最多只有 $y+z$ 位能够是 $1$，取高 $y+z$ 位即可。

否则我们有一种除了 $mn$ 位其他所有出现的位都是 $1$ 的策略就是先与 $2^{mn}$，然后剩下的所有位再与操作之后或/异或一次，剩下的操作全部丢到与 $2^{mn}$ 之前即可。

所以我们现在的目标是判断能否全部出现的位都是 $1$。

一个最简单的情况是 $x\ge 2,cc\ge 2$，因为我们可以连续与两个不同的数把所有位清零，之后就所有位都或/异或一次，剩下的操作丢到两次与之前即可。

否则的话我们可以断言，每次与操作后面跟着的数都是相同的，假设是 $2^i$。因为我们需要保证第 $i$ 位为一，所以首先要有 $buc_i>x$，然后我们的构造方案还是类似的，仍然是其他位在之后或/异或一次（优先选择异或），那么如果 $y\ne 0$，那么对于 $2^i$ 肯定可以被或一下，因此肯定可行。否则只有与和异或操作，那么一个条件就是 $buc_i-x$ 是奇数，那么这位肯定是 $1$，否则就是不行。

然后只要模拟一下就行了叭。

## 代码
```cpp
int T,n,x,y,z,c,cc,a[N],buc[N];
#define _(X,a,b) op##X.pb(a),nums##X.pb(b),buc[b]--,(a=='&'?x:a=='|'?y:z)--
#define AA(i) _(A,'&',i)
#define AO(i) _(A,'|',i)
#define AX(i) _(A,'^',i)
#define BA(i) _(B,'&',i)
#define BO(i) _(B,'|',i)
#define BX(i) _(B,'^',i)
#define rev(X) reverse((X).begin(),(X).end())
signed main(){
	read(T);for(int testcase=1;testcase<=T;testcase++){
		read(n,x,y,z);for(int i=0;i<n;i++)buc[i]=0;
		for(int i=1;i<=n;i++)read(a[i]),buc[a[i]]++;
		vector<int>opA,numsA,opB,numsB;
		if(x==0){
			for(int i=n-1;~i;i--)if(buc[i]){
				if(buc[i]%2||y){
					pc('1');int _=buc[i]%2?0:1;
					while(buc[i]>_&&z)AX(i);
					while(buc[i])AO(i);
				}else{pc('0');while(buc[i])AX(i);}
			}else pc('0');
			goto end;
		}else{
			c=cc=0;for(int i=0;i<n;i++)c+=buc[i]>0,cc+=buc[i]>1;
			if(y+z<c){
				for(int i=n-1;~i;i--)if(buc[i]&&(y||z)){
					pc('1');if(y)BO(i);else BX(i);
				}else pc('0');
				goto end;
			}
			if(x>=2&&cc>=2){
				for(int i=0;i<n;i++)if(buc[i]>1)for(int j=i+1;j<n;j++)if(buc[j]>1){
					BA(i);BA(j);
					for(int k=n-1;~k;k--)if(buc[k]){
						pc('1');if(y)BO(k);else BX(k);
					}else pc('0');
					goto end;
				}
			}
			for(int i=0;i<n;i++)if(buc[i]>x&&(y||(buc[i]-x)%2)){
				for(int j=n-1;~j;j--)if(buc[j]){
					pc('1');if(i!=j){if(z)BX(j);else BO(j);}
				}else pc('0');
				if(y){BA(i);rev(opB);rev(numsB);BO(i);}
				else{while(x)BA(i);rev(opB);rev(numsB);while(buc[i])BX(i);}
				goto end;
			}
			for(int mn=0;mn<n;mn++)if(buc[mn]){
				for(int j=n-1;~j;j--)pc('0'+(buc[j]&&j!=mn));
				BA(mn);
				for(int j=0;j<n;j++)if(buc[j]&&j!=mn){if(y)BO(j);else BX(j);}
				goto end;
			}
		}
		end:pc('\n');
		for(int i=0;i<n;i++)while(buc[i]){if(x)AA(i);else if(y)AO(i);else AX(i);}
		for(uint i=0;i<opA.size();i++)pc(opA[i]);
		for(uint i=0;i<opB.size();i++)pc(opB[i]);
		pc('\n');
		for(uint i=0;i<numsA.size();i++)write(numsA[i]),pc(' ');
		for(uint i=0;i<numsB.size();i++)write(numsB[i]),pc(' ');
		pc('\n');
	}
}
```

---

## 作者：dead_X (赞：1)

小正太能不能不要攻击我了。

假设我们有 $m$ 种本质不同的数。

不难发现先 XOR 然后 AND 然后 XOR 最后 OR 是非常优的。

没 AND 的情况非常平凡就不说了。

先考虑有一个没贡献的数怎么做，我们用它来将整个序列全部置为 $0$，一个位置最后是 $1$ 当且仅当这个数最后 OR 了一次或者 XOR 了一次，非常非常简单，随便做。

然后就是很阴间的要处理全取到的情况，同时满足多条优先判断上方的。

- 有 $\geq m$ 个 XOR/OR，$m+1=n$，Yes。
- 有 $\geq m$ 个 XOR/OR，$m+2\leq n$，有 $\geq 1$ 个 OR，Yes。
- 有 $m+2k$ 个 XOR，$m+2\leq n$，只有一个数出现了 $>1$ 次，Yes。
- 有 $m+2k+1$ 个 XOR，$m+2\leq n$，只有一个数出现了 $>1$ 次，No。
- 有 $\geq m$ 个 XOR，$m+2\leq n$，有 $\geq 2$ 个 AND，Yes。
- 有 $\geq m$ 个 XOR，$m+2\leq n$，有一个数出现了偶数次，Yes。
- 剩下的所有情况，No。

一些构造：

- AND $x$，AND $y$，OR $z_1,z_2,\cdots,z_n$。
- OR $x$，AND $x$，XOR $y_1,y_2,\cdots,y_n$。

我确信我做烦了，不过我都快退役了，能 AC 就是胜利吧。

这题他肯定会做。

---

