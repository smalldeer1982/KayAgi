# [AGC047E] Product Simulation

## 题目描述

题目名称：乘法模拟


这是一个只输出的题目，输入不会被给出。

简单来说，这是一个要求用比较 $(x < y)$ 和加法 $(x + y)$ 来模拟整数乘法的问题。没有输入，只需要输出操作序列。

假设有一个长度为 $N$ 的长数组 $a[0], a[1], \ldots, a[N-1]$。前两个元素的初始值为非负整数 $A, B$（你并不知道它们的值），其余元素的初始值为 $0$。你的目标是最终让 $a[2]$ 等于乘积 $A \cdot B$。

你可以执行两种形式的操作（这里，$0 \leq i, j, k < N$）：

- `+ i j k`: 令 $a[k] = a[i] + a[j]$。
- `< i j k`: 令 $a[k] = a[i] < a[j]$。也就是说，如果 $a[i] < a[j]$，则 $a[k]$ 将为 $1$，否则 $a[k]$ 将为 $0$。

操作的次数最多为 $Q$ 次，并且在操作过程中，数组 $a$ 的元素不能超过 $V$。不过，指定的索引 $(i, j, k)$ 可以重复使用，而且可以重写数组中的任何元素（包括前两个元素）。值得注意的是，问题的判定机制会在单个测试案例中对多个 $(A, B)$ 的组合执行操作序列。每次，判定机制会选择 $A, B$ 的值生成数组 $a = [A, B, 0, 0, \ldots, 0]$，并应用提交的操作序列来验证最终的 $a[2]$ 是否等于 $A \cdot B$。

## 说明/提示

对于所有测试数据，满足：

- $0\leq A,B\leq {10}^9$
- $N=Q=2\times{10}^5$
- $V={10}^{19}$

部分分：

- 如果你的程序能通过 $A,B\leq 10$ 的测试数据，你将得到 $800$ 分。
- 其余的 $1000$ 分只有通过所有测试数据才能获得。

### 样例一解释

输入案例 $1$ 中，判定机制仅对 $(A, B) = (2, 3)$ 的组合验证了提交的操作序列。上述输出通过了该测试案例，过程如下：
- 一开始，$a[0] = 2$，$a[1] = 3$，$a[2] = a[3] = \ldots = a[N-1] = 0$。
- 操作 `< 0 1 8` 后，$a[0] < a[1]$ 成立，因此 $a[8] = 1$。
- 操作 `+ 0 1 2` 后，$a[2] = a[0] + a[1] = 5$。
- 操作 `+ 2 8 2` 后，$a[2] = a[2] + a[8] = 6$。
- 操作 `+ 0 0 0` 后，$a[0] = a[0] + a[0] = 4$。
- 最终，$a[2] = 6 = A \cdot B$，达成要求。

## 样例 #1

### 输入

```
```

### 输出

```
4
< 0 1 8
+ 0 1 2
+ 2 8 2
+ 0 0 0```

# 题解

## 作者：houzhiyuan (赞：3)

模拟赛题，感觉非常难啊。

步数 $2966$，应该是最优的了。

先考虑一个 $O(xy)$ 的做法（这个我就想了一个小时）。

首先搞出两个个长度为 $O(x)$ 的序列，然后第一个序列里面有 $x$ 个 $1$，第二个里面有 $y$ 个 $1$，这个是好做的。

然后枚举上面的每一个元素，下面的每一个元素，那么答案加上它们与起来即可。

看到这个像竖式一样的东西，那么容易想到二进制拆分一下，那么相当于上面第 $i$ 位和下面第 $j$ 位产生 $2^{i+j}$ 的贡献。

二进制拆分部分是 $O(\log^2 V)$ 的，后面解竖式部分直接做是 $O(\log^3 V)$ 的，步数大约 $30000$。

然后发现竖式部分每次暴力算 $2^{i+j}$ 很浪费，可以开个桶记录 $i+j$ 相同的东西再算，然后也不用每次重新算，可以用秦久韶算法，也就是 $a_0+2(a_1+2(a_2+2(...)))$。

这样大概就需要 $3700$ 步，也是我能想出来的部分，[code](https://atcoder.jp/contests/agc047/submissions/43263775)

后面比较阴间，上面步数是 $4\log^2 V$ 级别的，发现加法的时候两个取与非常浪费啊。

注意到 $!x \& y = x < y$，因此可以先把 $a_0$ 的二进制翻转，然后中间只需要一步即可。

这样就进入 $3000$ 了，然后疯狂卡常。

[code](https://atcoder.jp/contests/agc047/submissions/43265017)

---

## 作者：jun头吉吉 (赞：3)

## 题意
有一个长度为 $N$ 的数组 $a[0],a[1],\dots,a[N-1]$，其中 $a[0]=A,a[1]=B$。

你需要构造一个操作序列，长度不超过 $Q$，使得操作完之后 $a[2]=A\times B$，操作有两种：

- `+ i j k`，表示 $a[k]=a[i]+a[j]$
- `< i j k`，表示 $a[k]=a[i]<a[j]$，得到 $0/1$

$0\le A,B\le 10^9,N=Q=2\times 10^5$

过程中不能超过 $10^{19}$。

## 题解

简单构造。

首先如果 $A=B=0$ 时，序列不管怎么搞都是全 $0$，所以最后 $a[2]$ 肯定是对的。

加下来考虑 $A+B>0$ 的情况。考虑实现一个二进制拆分。

首先可以造出一个 $1$，就是 $a[3]=a[0]+a[1],a[3]=a[4]<a[3]$，那么现在 $a[3]$ 就一定是 $1$ 了。

二进制拆分就维护一个前缀 $s$，然后尝试当前位 $2^i$ 是否是 $1$，如果是 $1$ 那么 $s+2^i\le x$。因为只有 $<$ 所以要把 $a[0]=a[0]+a[3],a[1]=a[1]+a[3]$。然后就可以得到 $a[0]$ 和 $a[1]$ 所有二进制位了。

对于 $\{0,1\}\times \{0,1\}$ 的乘法是简单的，就考虑 $a\times b=1<a+b$。把所有二进制为乘起来加到 $a[2]$ 即可。

次数是 $\mathcal O(\log ^2)$ 的。

## 代码

两个 `namespace` 分别是输出方案和测试方案得到的值。

```cpp
const int N=2e5;
namespace A1{
	vector<tuple<char,int,int,int>>res;
	struct inf{char op;int i,j;inf(char op,int i,int j):op(op),i(i),j(j){}};
	struct node{
		int i;
		void operator=(inf b){
			res.eb(b.op,b.i,b.j,i);
		}
	}a[N];
	inf operator+(node a,node b){return inf('+',a.i,b.i);}
	inf operator<(node a,node b){return inf('<',a.i,b.i);}
	void init(){
		for(int i=0;i<N;i++)a[i].i=i;
	}
	void end(){
		writeln(res.size());
		for(auto[op,i,j,k]:res)pc(op),pc(' '),writeln(i,j,k);
	}
}
namespace A2{
	ll A,B,a[N];
	void init(){
		A=114643,B=516344;
		a[0]=A,a[1]=B;
	}
	void end(){
		writeln(A,B,a[2],A*B);
	}
}
using namespace A1;
void zero(int i){a[i]=a[3]<a[4];}
void one(int i){a[i]=a[4]<a[3];}
void pw(int i,int c){while(c--)a[i]=a[i]+a[i];}
signed main(){
	init();
	a[3]=a[0]+a[1];
	a[3]=a[4]<a[3];
	a[0]=a[0]+a[3];
	a[1]=a[1]+a[3];
	for(int i=29;~i;i--){
		one(65);
		pw(65,i);
		a[67]=a[66]+a[65];
		a[5+i]=a[67]<a[0];
		a[65]=a[67]<a[0];
		pw(65,i);
		a[66]=a[66]+a[65];
	}
	zero(66);
	for(int i=29;~i;i--){
		one(65);
		pw(65,i);
		a[67]=a[66]+a[65];
		a[35+i]=a[67]<a[1];
		a[65]=a[67]<a[1];
		pw(65,i); 
		a[66]=a[66]+a[65];
	}
	for(int i=0;i<30;i++){
		zero(66);
		for(int j=29;~j;j--){
			a[65]=a[5+i]+a[35+j];
			a[65]=a[3]<a[65];
			pw(66,1);
			a[66]=a[66]+a[65];
		}
		pw(66,i);
		a[2]=a[2]+a[66];
	}
	end();
}
```

---

## 作者：xiaosi4081 (赞：1)

这种神秘构造题我们可以模块化处理，可以把一个操作封装成一个函数，就能使思路更清晰。

当 $a_0 = a_1 = 0$ 时，这种情况无论如何 $a_2$ 都会为 $0$，所以可以忽略。

1. $a_2$ 为所求。
2. $a_3 = 0$。
3. $a_4 = 1 = [[a_0 > 0] + [a_1 > 0] > 0]$。$a_0 = a_1 = 0$ 的情况如上述，可以忽略。
4. 当 $a_i \in \{0, 1\}$ 时，$\neg a_i \Leftrightarrow  a_i < 1 \Leftrightarrow  a_i < a_4$。
5. $a_i \leq a_j \Leftrightarrow \neg(a_i > a_j)$。
6. $a_i \in \{0, 1\}, a_j \in \{0, 1\}$ 时，$a_ia_j = a_i\&a_j = [a_i+a_j = 2] = [a_i+a_j > 1]$。
7. 定义 $\mathrm{lf}(a, i) = a\times 2^i$，可以通过 $a_i = a_i+a_i$ 递推求得。
8. 考虑把 $a_0 \times a_1$ 变为二进制下的竖式乘法。
9. 将 $x$ 转化为二进制数 $w$，从大到小枚举每一位，设当前位为第 $i$ 位（从右往左数），维护当前设为 $1$ 的位的权值和 $s$。则 $w_i =[s+2^i \leq x]$ ，$2$ 的幂可以预处理出来。
10. 设 $a_0$ 的二进制数为 $w_1$, $a_1$ 的二进制数为 $w_2$。
11. 二进制乘法如下：结果中 $w_{3, i} = w_{1, j}\times w_{2, i-j} = w_{1, j}\& w_{2, i-j}(i \geq j)$，这里的 $w_{3, i}$ 可以 $> 1$。
12. $ans = a_2 = \sum w_{3, i}\times 2^i$。

可以用函数把上面的一些操作封装起来。

次数是 $O(\log^2 n)$ 级别的，常数大，总共是 $6303$ 次。
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int a[N], q;
struct node{
	int op, i, j, k;
} s[N];
int _0, _1, ans = 2, cnt = 2, tmp[2];
inline void add(int i, int j, int k){ a[k] = a[i]+a[j], s[++q] = {1, i, j, k}; }
inline void leq(int i, int j, int k){ a[k] = a[i] < a[j], s[++q] = {2, i, j, k}; }
inline void re(int i){ leq(i, _1, i); }
inline void le(int i, int j, int k){ leq(j, i, k), re(k); }
inline void an(int i, int j, int k){ add(i, j, k), leq(_1, k, k); }
inline void lf(int i, int k){ while(k--) add(i, i, i); }
inline void gi(int i, int j){ add(_0, j, i); }
int w1[62], w2[62], pw[62], w3[62];
signed main(){
	a[0] = 1000000000, a[1] = 1000000000;
	_0 = ++cnt;
	leq(_0, 0, ++cnt); leq(_0, 1, ++cnt);
	add(cnt, cnt-1, cnt-1); _1 = cnt-1;
	leq(_0, _1, _1);
	int su = ++cnt; tmp[0] = ++cnt;
	pw[0] = ++cnt, gi(pw[0], _1);
	for(int i = 1; i <= 31; i++){
		pw[i] = ++cnt;
		add(pw[i-1], pw[i-1], pw[i]);
	}
	for(int i = 31; i >= 0; i--){
		w1[i] = ++cnt;
		add(su, pw[i], tmp[0]);
		le(tmp[0], 0, w1[i]);
		gi(tmp[0], w1[i]), lf(tmp[0], i);
		add(su, tmp[0], su);
	} add(_0, _0, su);
	for(int i = 31; i >= 0; i--){
		w2[i] = ++cnt;
		add(su, pw[i], tmp[0]);
		le(tmp[0], 1, w2[i]);
		gi(tmp[0], w2[i]), lf(tmp[0], i);
		add(su, tmp[0], su);
	}
	int res = 0;
	for(int i = 0; i <= 60; i++){
		w3[i] = ++cnt;
		for(int j = max(0ll, i-31); j <= min(i, 31ll); j++){
			an(w1[j], w2[i-j], tmp[0]);
			add(w3[i], tmp[0], w3[i]); 
		}
		lf(w3[i], i);
	} for(int i = 0; i <= 60; i++) add(ans, w3[i], ans);
	cout << q << endl;
	for(int i = 1; i <= q; i++){
		if(s[i].op == 1) cout << "+ " << s[i].i << " " << s[i].j << " " << s[i].k << "\n";
		else cout << "< " << s[i].i << " " << s[i].j << " " << s[i].k << "\n";
	}
	return 0;
} 
```

---

## 作者：zhiyin123 (赞：1)

这是一个简单的 $O(\log ^ 3 V)$ 次询问的做法。

# 一

首先，不妨设 $\text{ans} = 2$，而 $a[\text{ans}]$ 存放的就是答案。

容易发现，当 $A = B = 0$ 时，无论如何操作，$a[\text{ans}]$ 都是 $0$，符合要求。所以，不妨设 $A$ 和 $B$ **不同时为** $0$。

---

为了方便做出这道题，我们先考虑获得一些**常数变量**。

首先，是常量 $0$。对于一个**整数** $\text{zero}\in [0,N)$，$a[\text{zero}]$ 本来就是 $0$。于是我们就获得了常量 $0$。

有了常量 $0$，我们就可以拷贝一个变量了。例如，我们要让 $a[x]\gets a[y]$，就可以这么做：

$$
a[x]\gets a[y]+0
$$

复杂度 $O(1)$。

---

然后，是常量 $1$。设我们希望 $a[\text{one}]$ 等于 $1$，那么可以这么做：（其中**整数** $\text{tmp}_1\in [0,N)$ 且不与之前出现过的变量相等；换句话说，它是一个临时变量）

$$
\begin{gathered}
a[\text{one}]\gets 0\\
a[\text{one}]\gets [a[\text{one}]<A]\\
a[\text{tmp}_1]\gets 0\\
a[\text{tmp}_1]\gets [a[\text{tmp}_1]<B]\\
a[\text{one}]\gets a[\text{one}]+a[\text{tmp}_1]\\
a[\text{one}]\gets [a[\text{zero}]<a[\text{one}]]
\end{gathered}
$$

这是 $O(1)$ 的。由于 $A,B$ 不同时为 $0$，所以这是正确的。

---

有了 $1$，我们就可以进行 $01$ 反转操作了。若 $a[x]\in \{0,1\}$，要将它**反转**（即令 $a[x]\gets \lnot a[x]$），可以这样：

$$
a[x]\gets [a[x]<1]
$$

这是 $O(1)$ 的。

---

有了 $01$ 反转，我们就可以做出这个操作了：$a[z]\gets [a[x]\leq a[y]]$（不大于比较）。具体做法为：

$$
\begin{gathered}
a[z]\gets [a[y]<a[x]]\\
a[z]\gets \lnot a[z]
\end{gathered}
$$
这是 $O(1)$ 的。

---

实际上，一些逻辑运算也可以做到。下面要讲实现逻辑 $\operatorname{and}$。不妨设 $a[x],a[y]\in\{0,1\}$，要想让 $a[z]\gets a[x]\operatorname{and}a[y]$，可以这么做：

$$
\begin{gathered}
a[z]\gets a[x] + a[y]\\
a[z]\gets [1<a[z]]
\end{gathered}
$$

这是 $O(1)$ 的。

---

为了能快速的乘法，我们考虑实现一下**左移**操作。例如，要让 $a[x]\gets a[x] \times 2^u$（其中 $u\geq 0$），我们可以直接进行 $u$ 次

$$
a[x]\gets a[x] + a[x]
$$

复杂度为 $O(\log V)$。

# 二

实现了一些基本操作后，考虑如何做这道题。发现，关于 $A,B$ 的运算非常难处理，因为需要再运算时进行**条件判断**。为了方便条件判断，不妨将 $A$ 和 $B$ **二进制拆分**。

设 $A$ 在二进制下从低到高的第 $i$ 位为 $A_i$（索引从 $0$ 开始，$A_i\in\{0,1\}$），$B_i$ 同理。不妨设 $A$ 和 $B$ 均有 $h$ 位，则 $h=O(\log V)$。

如何求出所有 $A_i$ 呢？不妨**从大到小**枚举 $i$，并实时维护 $A$ 的第 $i+1$ 位以上的和，形式化的，维护 $\displaystyle S_{i+1} = \sum_{j = i + 1} ^ h A_j\times 2^{j}$，就能够求出了。

具体的，当 $i$ 枚举时，$S_{i+1},S_{i+2},\dots,S_h$ **已经被求出**，$A_{i+1},A_{i+2},\cdots,A_{h}$ 也**已被求出**，现在我们要求出 $S_i$ 和 $A_i$，可以这样做：（其中 $a[\text{tmp}_1],a[\text{tmp}_2]$ 是临时变量）

$$
\begin{gathered}
a[\text{tmp}_1]\gets 1\\
a[\text{tmp}_1]\gets a[\text{tmp}_1]\times 2^i\\
a[\text{tmp}_2]\gets S_{i+1}+a[\text{tmp}_1]\\
A_i\gets [a[\text{tmp}_2]\leq A]\\
S_i\gets A_i\\
S_i\gets S_i\times 2^i\\
S_i\gets S_i+S_{i+1}
\end{gathered}
$$

这部分时间复杂度 $O(h)\cdot O(\log V) = O(\log ^2 V)$，空间复杂度 $O(h)=O(\log V)$。

然后我们如法炮制，也求出所有的 $B_i$。

---

考虑如何统计答案。

不妨枚举 $A_i$ 和 $B_j$，然后算出 $A_i\times B_j$ 是多少，然后加到 $a[\text{ans}]$ 上。

具体的，让 $i$ 枚举 $\{0,1,\dots,h\}$，$j$ 枚举 $\{0,1,\dots,h\}$（这部分 $O(h^2)$），然后进行如下操作：（$a[\text{tmp}_1]$ 是临时变量）

$$
\begin{gathered}
a[\text{tmp}_1]\gets A_i\operatorname{and}B_j\\
a[\text{tmp}_1]\gets a[\text{tmp}_1]\times 2^{i+j}\\
a[\text{ans}]\gets a[\text{ans}]+a[\text{tmp}_1]
\end{gathered}
$$

这部分时间是 $O(\log ^3 V)$ 的。

最终，总时间复杂度位 $O(\log ^3 V)$，空间复杂度位 $O(\log V)$。

# 代码

```cpp
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<utility>
#include<numeric>
#include<algorithm>
using std::cerr; using std::setw; using std::endl;
using std::cin; using std::cout;
constexpr int Q=2e5,N=2e5,LOGV=30;
constexpr int Zero=3,One=4,Two=5;
constexpr int Tmp1=6,Tmp2=7,Tmp3=8;
constexpr int A=0,B=1,Ans=2,Al=9,Bl=Al+LOGV+1,End=Bl+LOGV+1;
struct opt_t{
	char typ; int i,j,k;
};
std::vector<opt_t> opt;
void add(int i,int j,int k){
	opt.push_back({'+',i,j,k});
	return ;
}
void cmp(int i,int j,int k){
	opt.push_back({'<',i,j,k});
	return ;
}
void copy(int to,int from){
	add(to,from,Zero);
	return ;
}
void flip(int i){
	cmp(i,i,One);
	return ;
}
void left(int i,int c){
	for(int t=1;t<=c;t++){
		add(i,i,i);
	}
	return ;
}
void getand(int i,int j,int k){
	add(i,j,k);
	cmp(i,One,i);
	return ;
}
void setN(){
	//zero ok!
	cmp(One,One,0);
	cmp(Two,Two,1);
	add(One,One,Two);
	cmp(One,Zero,One);// One ok!
	add(Two,One,One);
	return ;
}
void chai(int x,int beg){
	// Tmp1  sum 2^a     Tmp2 2^a
	copy(Tmp1,Zero);
	for(int v=LOGV;v>=0;v--){
		copy(Tmp2,One); left(Tmp2,v);
		int pos=beg+v;
		add(pos,Tmp1,Tmp2);
		
		//compare
		cmp(pos,x,pos);
		flip(pos);
		
		// update Tmp1
		copy(Tmp2,pos); left(Tmp2,v);
		add(Tmp1,Tmp1,Tmp2);
	}
	return ;
}
void calcans(){
	for(int v1=0;v1<=LOGV;v1++){
		for(int v2=0;v2<=LOGV;v2++){
			getand(Tmp1,Al+v1,Bl+v2);
			left(Tmp1,v1+v2);
			add(Ans,Ans,Tmp1);
		}
	}
	return ;
}
int main(){
	std::ios::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
	setN();
	chai(A,Al);
	chai(B,Bl);
	calcans();
//	for(int i=3;i<End;i++) cmp(i,i,i);
	cout<<opt.size()<<'\n';
	for(int i=0;i<opt.size();i++){
		auto &o=opt[i];
		cout<<o.typ<<' '<<o.j<<' '<<o.k<<' '<<o.i;
		if(i+1<opt.size()) cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Mine_King (赞：1)

[在我的博客获得更好的阅读体验。](https://caijimk.netlify.app/post/202307problemrecord)

非常有意思的造计算机题！

**目前最优解，次数为 $2938$，内存单元个数为 $96$。**

首先，如果 $a _ 0 = a _ 1 = 0$，那么无论如何无法构造出非 $0$ 的数，所以怎么做都是合法的。

考虑竖式乘法，第一步是将两个数转化为二进制，然后把每一位存下来。  
我们需要搞出所有 $2 ^ i$，那么一种朴素的想法就是先获得 $1$，然后不断乘 $2$（即两个相同的数相加）。  
获得 $1$ 的方法是：$a _ 3 \gets a _ 0 + a _ 1, a _ 3 \gets [a _ 4 < a _ 3]$，这样就能使 $a _ 3 = 1$。然后就可以求出所有 $2 ^ i$，用若干内存单元存下来。

```cpp
add(3, 0, 1);
cmp(3, 4, 3);
for (int i = 1; i <= 29; i++) add(3 + i, 3 + i - 1, 3 + i - 1);
// for each i in 3 ~ 32: 2 ^ {i - 3}
```

接下来考虑从高位到低位求。具体来说，设当前是第 $i$ 位，我们用一个数记录只考虑当前已经求得值的几位的结果，然后将它与 $2 ^ i$ 相加，如果 $\le a _ 0$，则 $a _ 0$ 这一位为 $1$，否则为 $0$。由于没有 $\le$ 操作，我们先让 $a _ 0 \gets a _ 0 + 1$。

```cpp
// 93: temp value
// 94: temp digit
add(0, 0, 3);
for (int i = 29; i >= 0; i--) {
    add(94, 93, 3 + i);
    cmp(94, 94, 0);
    add(32 + i + 1, 32 + i + 1, 94);
    for (int j = 1; j <= i; j++) add(94, 94, 94);
    add(93, 93, 94);
}
```

对 $a _ 1$ 的拆分相同。

然后考虑竖式乘法，我们直接枚举没一位，然后计算这两位相乘的结果，因为是二进制，所以结果就是按位与的结果。具体实现是：设这两位分别为 $x, y$，分别为第 $i, j$ 位，则令 $z \gets x + y, z \gets [1 < z]$，然后再乘上 $2 ^ {i + j}$（即重复 $\times 2$ 操作 $i + j$ 遍）即可。

```cpp
for (int i = 0; i <= 58; i++) {
    cmp(93, 93, 95); // a[95] = 0，使用这种方法清 0 一个内存单元。
    for (int j = 0; j <= min(29, i); j++) {
        if (i - j > 29) continue;
        add(94, 32 + i - j + 1, 62 + j + 1);
        cmp(94, 3, 94);
        add(93, 93, 94);
    }
    for (int j = 1; j <= i; j++) add(93, 93, 93);
    add(2, 2, 93);
}
```

完整代码：

记录：[Submission #43274995](https://atcoder.jp/contests/agc047/submissions/43274995)。

```cpp
// Think twice, code once.
#include <tuple>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
// #define DEBUG
using namespace std;

int a[1005];
vector<tuple<char, int, int, int>> ans;

void cmp(int i, int j, int k) {ans.emplace_back('<', j, k, i); a[i] = a[j] < a[k]; return ;}
void add(int i, int j, int k) {ans.emplace_back('+', j, k, i); a[i] = a[j] + a[k]; return ;}

int main() {
#ifdef DEBUG
	scanf("%d%d", &a[0], &a[1]);
#endif
	add(3, 0, 1);
	cmp(3, 4, 3);
	add(0, 0, 3), add(1, 1, 3);
	for (int i = 1; i <= 29; i++) add(3 + i, 3 + i - 1, 3 + i - 1);
	// for each i in 3 ~ 32: 2 ^ {i - 3}
	// 93: temp value
	// 94: temp digit
	// 95: zero
	for (int i = 29; i >= 0; i--) {
		add(94, 93, 3 + i);
		cmp(94, 94, 0);
		add(32 + i + 1, 32 + i + 1, 94);
		for (int j = 1; j <= i; j++) add(94, 94, 94);
		add(93, 93, 94);
	}
	// for each i in 33 ~ 62: x's (i - 33)th digit in binary.
	cmp(93, 93, 95);
	for (int i = 29; i >= 0; i--) {
		add(94, 93, 3 + i);
		cmp(94, 94, 1);
		add(62 + i + 1, 62 + i + 1, 94);
		for (int j = 1; j <= i; j++) add(94, 94, 94);
		add(93, 93, 94);
	}
	// for each i in 63 ~ 92: y's (i - 63)th digit in binary.
	for (int i = 0; i <= 58; i++) {
		cmp(93, 93, 95);
		for (int j = 0; j <= min(29, i); j++) {
			if (i - j > 29) continue;
			add(94, 32 + i - j + 1, 62 + j + 1);
			cmp(94, 3, 94);
			add(93, 93, 94);
		}
		for (int j = 1; j <= i; j++) add(93, 93, 93);
		add(2, 2, 93);
	}
#ifndef DEBUG
	printf("%d\n", (int)ans.size());
	for (auto i : ans) printf("%c %d %d %d\n", get<0>(i), get<1>(i), get<2>(i), get<3>(i));
#else
	printf("%d\n", a[2]);
#endif
	return 0;
}
```

此时操作次数为 $5673$。

---

然后考虑优化。

首先，竖式乘法部分，我们可以将所有 $i + j$ 相同的点加起来一起处理，这样复杂度就变成了 $O(\log ^ 2 V)$。  
以及可以使用秦九韶算法优化（[houzhiyuan 的做法](https://www.luogu.com.cn/blog/98490/solution-at-agc047-e)），也就是将结果当成一个 $x = 2$ 的多项式，然后加速计算。

```cpp
for (int i = 58; i >= 0; i--) {
    if (i != 58) add(2, 2, 2);
    for (int j = 0; j <= min(29, i); j++) {
        if (i - j > 29) continue;
        add(94, 32 + i - j + 1, 62 + j + 1);
        cmp(94, 3, 94);
        add(2, 2, 94);
    }
}
```

此时次数为 $3902$。

记录：[Submission #43275171](https://atcoder.jp/contests/agc047/submissions/43275171)。

---

然后在二进制拆分 $a _ 1$ 时，我们可以新开一个内存单元而不是清空 $a _ {93}$，这样次数变为 $3901$，内存单元个数变为 $97$。

接下来转而优化二进制拆分部分。

我们发现可以直接把值赋给存储二进制的内存单元而不是先存到 $a _ {94}$ 这个临时变量中，这样再把值赋给 $a _ {94}$ 时就可以直接进行一次 $\times 2$，次数减少 $2 \times 29 = 58$。  
另外，当 $i = 0$ 时我们只需要前两个操作（求值，赋值给存储二进制的内存单元），又可以减少 $2 \times 2 = 4$ 次操作。

```cpp
for (int i = 29; i >= 0; i--) {
    add(94, 93, 3 + i);
    cmp(32 + i + 1, 94, 0);
    if (i) {
        add(94, 32 + i + 1, 32 + i + 1);
        for (int j = 1; j < i; j++) add(94, 94, 94);
        add(93, 93, 94);
    }
}
```

此时次数为 $3839$。

记录：[Submission #43287946](https://atcoder.jp/contests/agc047/submissions/43287946)。

---

**接下来是质的飞跃。**

我们发现之前的做法中竖式乘法的 $\log ^ 2$ 部分有高达 $3$ 的常数，尝试去优化它。  
发现 $x \mathbin{\mathrm{and}} y = (x \mathbin{\mathrm{xor}} 1) < y$，所以我们考虑将 $a _ 0$ 取反，这样就减少了 $1$ 倍常数。

我们发现原本确定 $a _ 0$ 某一位的值时，是求 $[a _ {94} < a _ 0 + 1]$，那么取反之后就变成 $[a _ {94} \ge a _ 0 + 1]$，即 $[a _ 0 < a _ {94}]$，那么我们只要不在最开始让 $a _ 0 \gets a _ 0 + 1$ 就好了。

但是我们更新 $a _ {93}$ 时还需要 $a _ 0$ 这一位真实的值，所以无法使用上面说的在赋值时直接 $\times 2$ 的优化。

```cpp
for (int i = 29; i >= 0; i--) {
    add(94, 93, 3 + i);
    cmp(32 + i + 1, 0, 94);
    if (i) {
        cmp(94, 32 + i + 1, 3);
        for (int j = 1; j <= i; j++) add(94, 94, 94);
        add(93, 93, 94);
    }
}
// ...
for (int i = 58; i >= 0; i--) {
    if (i != 58) add(2, 2, 2);
    for (int j = 0; j <= min(29, i); j++) {
        if (i - j > 29) continue;
        cmp(94, 32 + i - j + 1, 62 + j + 1);
        add(2, 2, 94);
    }
}
```

次数为 $2967$。

记录：[Submission #43288524](https://atcoder.jp/contests/agc047/submissions/43288524)。

---

接下来时一个常数优化。

我们发现在二进制拆分时的第一步 $a _ {93}$ 是空的，所以没必要去 $a _ {94}$ 那边转一下，这样就减少了 $2 \times 1$ 次。

此时次数为 $2965$。

记录：[Submission #43288916](https://atcoder.jp/contests/agc047/submissions/43288916)。

---

看起来没有优化空间了？

并不是，在询问 [yyandy](https://www.luogu.com.cn/user/234101) 后，我学习到了一种更加优秀的求取反后二进制的方法，可以把之前抛弃的直接 $\times 2$ 优化搞回来。

那就是，我们记录 $2 ^ {30}$，然后用 $a _ 0 + 2 ^ i$ 与其比大小。若 $a _ 0 + 2 ^ i \ge 2 ^ {30}$，则 $a _ 0$ 这一位是 $1$，否则是 $0$。于是我们只要求 $[2 ^ {30} < a _ 0 + 2 ^ i]$ 就能获得 $a _ 0$ 这一位取反后的结果。在求完值后将 $a _ 0$ 这一位设为 $1$ 即可。  
缺点是无法使用上面的第一步优化。

```cpp
add(93, 3 + 29, 3 + 29);
for (int i = 29; i >= 0; i--) {
    add(94, 0, 3 + i), cmp(32 + i + 1, 94, 93);
    if (i) {
        add(94, 32 + i + 1, 32 + i + 1);
        for (int j = 1; j < i; j++) add(94, 94, 94);
        add(0, 0, 94);
    }
}
```

次数：$2938$。

记录：[Submission #43292834](https://atcoder.jp/contests/agc047/submissions/43292834)。

yyandy 大概是没有使用第一步优化，所以次数比我多了 $1$，让我侥幸获得最优解。

---

最后啊，我们发现已经不需要清零操作了，所以 $a _ {95}$ 已经没用了，那么将所有 $a _ {96}$ 替换为 $a _ {95}$ 就可以让内存单元数量变回 $96$。

完整代码：

```cpp
// Think twice, code once.
#include <tuple>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
// #define DEBUG
using namespace std;

long long a[1005];
vector<tuple<char, int, int, int>> ans;

void cmp(int i, int j, int k) {ans.emplace_back('<', j, k, i); a[i] = a[j] < a[k]; return ;}
void add(int i, int j, int k) {ans.emplace_back('+', j, k, i); a[i] = a[j] + a[k]; return ;}

int main() {
#ifdef DEBUG
	scanf("%lld%lld", &a[0], &a[1]);
#endif
	add(3, 0, 1);
	cmp(3, 4, 3);
	add(1, 1, 3);
	for (int i = 1; i <= 29; i++) add(3 + i, 3 + i - 1, 3 + i - 1);
	// for each i in 3 ~ 32: 2 ^ {i - 3}
	// 93: temp value
	// 95: the other temp value
	// 94: temp digit
	add(93, 3 + 29, 3 + 29);
	for (int i = 29; i >= 0; i--) {
		add(94, 0, 3 + i), cmp(32 + i + 1, 94, 93);
		if (i) {
			add(94, 32 + i + 1, 32 + i + 1);
			for (int j = 1; j < i; j++) add(94, 94, 94);
			add(0, 0, 94);
		}
	}
	// for each i in 33 ~ 62: x's (i - 33)th digit in binary.
	for (int i = 29; i >= 0; i--) {
		if (i != 29) add(94, 95, 3 + i), cmp(62 + i + 1, 94, 1);
		else add(95, 95, 3 + i), cmp(62 + i + 1, 95, 1);
		if (i) {
			if (i != 29) {
				add(94, 62 + i + 1, 62 + i + 1);
				for (int j = 1; j < i; j++) add(94, 94, 94);
				add(95, 95, 94);
			} else {
				add(95, 62 + i + 1, 62 + i + 1);
				for (int j = 1; j < i; j++) add(95, 95, 95);
			}
		}
	}
	// for each i in 63 ~ 92: y's (i - 63)th digit in binary.
	for (int i = 58; i >= 0; i--) {
		if (i != 58) add(2, 2, 2);
		for (int j = 0; j <= min(29, i); j++) {
			if (i - j > 29) continue;
			cmp(94, 32 + i - j + 1, 62 + j + 1);
			add(2, 2, 94);
		}
	}
#ifndef DEBUG
	printf("%d\n", (int)ans.size());
	for (auto i : ans) printf("%c %d %d %d\n", get<0>(i), get<1>(i), get<2>(i), get<3>(i));
#else
	printf("%lld\n", a[2]);
#endif
	return 0;
}
```

次数：$2938$。内存单元个数：$96$。

记录：[Submission #43294401](https://atcoder.jp/contests/agc047/submissions/43294401)。


---

## 作者：larsr (赞：0)

评分虚高，感觉只有紫？

如果 $x,y\le 1$，如何求 $xy$。直接随便乱试就试出来了：

- $a=y<x$。
- $b=a+y$。
- $c=x+y$。
- $d=b<c$。

$d$ 即为 $xy$。其中 $b$ 可以理解成 $\max(x,y)$，而 $xy=\max(x,y) < x+y$。

完成第一步之后就可以想到计算可以利用二进制分解，然后再二进制合并起来。

预处理出 $2^a$ 和 $2^a-1$，可以使用 $0<x$ 得到 $1$，如果 $x=0$，得到的 $2^x$ 就是 $0$，但 $x=0$ 时分解出来的 $x$ 已经是全 $0$ 了，所以没关系。

分解从高位到低位考虑，如果需要这个位就加入这个位即可。

- 目前判断是否加入 $2^a$。
- 维护 $tmp$ 即目前已经加入的位的和。
- $b=(tmp+2^a-1)<x$，那么 $b$ 就代表着第 $a$ 位的值。
- 更新 $tmp$，使用 $a$ 次 `b=b+b`，然后再加入 $tmp$ 即可。

二进制合并用刚才的 $x,y\le1$ 的乘法即可，无需考虑进位。得到二进制之后再得到十进制很简单，不讲。

总操作次数 $5844$。

[sub](https://atcoder.jp/contests/agc047/submissions/63109681)

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

给一个思路和更容易理解的代码。

注意到，当 $a_0=a_1=0$ 时，任意操作的结果都是 $0$，因此对于任何操作序列都是可以通过的。下面认为 $a_0+a_1>0$。

有一个思路是：每个变量都变成 $0$ 或 $1$ 可以将问题简单化。

首先考虑将 $1$ 创造出来。注意到 $[0<a_0+a_1]=1$ 是恒成立的。创造了 $1$ 后可以顺便将 $2^i(1\le i\le30)$ 都创造出来，显然有 $2^{i-1}+2^{i-1}=2^i$。并且，也可以注意到将一个数乘 $2^i$ 等价于自己加自己 $i$ 次，这是一个以后要用的性质。

接下来考虑将 $a_0$ 和 $a_1$ 分解为二进制形式。可以考虑从高往低分解。假设我们现在分解 $w$ 的第 $i$ 位（即为 `(w>>i)&1`），已经分解出来的部分为 $la$（有 `la=(w>>(i+1))<<(i+1)`），那么有 $w$ 的第 $i$ 位为 $![w<2^i+la]=[[w<2^i+la]<1]$，这是容易转化为操作的。

将 $a_0$ 和 $a_1$ 分解为二进制形式后，可以考虑进行竖式计算。注意到如果 $x,y\in\{0,1\}$，那么有 $xy=[1<x+y]$。最后将 $a_0$ 的第 $i$ 位乘 $a_1$ 的第 $j$ 位的结果乘上 $2^{i+j}$，直接计入答案。

操作次数大概是 $\log^3$ 级别的，不需要其他优化即可通过，代码更容易理解。

### 2 代码与记录

```cpp
// LUOGU_RID: 203418929
#include<bits/stdc++.h>
using namespace std;
struct A{int op,x,y,to;};
vector<A>ans;
long long a[200000];
inline void add(int to,int x,int y){ans.push_back((A){0,x,y,to});}
inline void cmp(int to,int x,int y){ans.push_back((A){1,x,y,to});}
int main(){
	#ifdef dzy
	freopen("e_1.out","w",stdout);
	#endif
	add(10,0,1); cmp(10,12345,10);//创造一个1
	for(int i=1;i<=30;++i)add(i+10,i-1+10,i-1+10);//计算2^i
	for(int i=30;i>=0;--i){//分解为二进制 
		add(12000,8,i+10); cmp(i+100,0,12000); cmp(i+100,i+100,10);
		add(12000,i+100,12345); for(int j=1;j<=i;++j)add(12000,12000,12000); add(8,8,12000);
		add(12000,9,i+10); cmp(i+200,1,12000); cmp(i+200,i+200,10);
		add(12000,i+200,12345); for(int j=1;j<=i;++j)add(12000,12000,12000); add(9,9,12000);
	}
	for(int i=0;i<=30;++i){//二进制竖式乘法 
		for(int j=0;j<=30;++j){
			add(12000,i+100,j+200); cmp(12000,10,12000);
			for(int k=1;k<=i+j;++k)add(12000,12000,12000);
			add(2,2,12000);
		}
	}
	printf("%d\n",(int)ans.size());
	for(auto u:ans){
		if(!u.op)printf("+ ");
		else printf("< ");
		printf("%d %d %d\n",u.x,u.y,u.to);
	}
	return 0;
}
```

[记录传送门](https://atcoder.jp/contests/agc047/submissions/62858722)

By **dengziyue**

---

## 作者：wwwwwza (赞：0)

很聪明的一道题。

首先要凑个 $1$ 出来，设 $a_2=a_1+a_0,a_{100}=a_2<a_3$，当 $A=B=0$ 时，$a_{100}=0$ 不对答案造成影响。

将 $A,B$ 拆成二进制的形式，从高往低判断这一位能填什么，注意题目给的是 $<$ 的形式，而判断要用 $\leq$ 的形式，所以要将 $A,B$ 分别 $+1$。

然后就是做二进制乘法，当 $A=B=1$ 时才能做乘法，显然 $A=B=1$ 等价于 $(!A)<B$。

考虑如何将 $A$ 取反，发现 $!A$ 等价于 $A<1$。

$5087$ 步，时间复杂度为 $O(\log^2 V)$。

代码比较丑，还很不优美，不建议抄。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5;
int a[N],cnt=0;
void add(int i,int j,int k){
	cnt++;
	printf("+ %lld %lld %lld\n",i,j,k);
	a[k]=a[i]+a[j];
}
void bol(int i,int j,int k){
	cnt++;
	printf("< %lld %lld %lld\n",i,j,k);
	a[k]=a[i]<a[j];
}
signed main(){
	printf("5087\n");
	add(0,1,2),bol(3,2,100);
	add(0,100,10),add(1,100,11);
	for(int i=101;i<=160;i++)add(i-1,i-1,i);
	for(int i=230;i>=200;i--){
		add(i-100,270,280),bol(280,10,i),add(3,i,275);
		for(int j=1;j<=i-200;j++)add(275,275,275);
		add(270,275,270);
	}
	for(int i=330;i>=300;i--){
		add(i-200,370,380),bol(380,11,i),add(3,i,375);
		for(int j=1;j<=i-300;j++)add(375,375,375);
		add(370,375,370);
	}
	for(int i=200;i<=230;i++)bol(i,100,i);
	for(int i=200;i<=230;i++){
		for(int j=300;j<=330;j++){
			bol(i,j,600);
			add(600,i+j,i+j);
		}
	}
	bol(3,3,2);
	for(int i=500;i<=560;i++){
		for(int j=1;j<=i-500;j++)add(i,i,i);
		add(2,i,2);
	}
	return 0;
}

```

---

## 作者：Feyn (赞：0)

感觉上并没有那么难，只是有些细节需要注意。

考虑到这道题给的操作次数限制比较宽，我们可以使用比较朴素的方法来解决，即考虑把 $A,B$ 分别进行二进制拆分（令 $S$ 从低到高第 $i$ 位是 $S_i$），然后枚举一对 $i,j$，如果 $A_i$ 和 $B_j$ 都是 $1$，那么给答案加上 $2^{i+j}$，否则什么都不干。然后来分析为了实现这个框架我们需要做什么。

首先是如何凑出 $2^t$，这是比较简单的。首先假设我们有一个 $a_x=1$，那么我们只需要重复 $t$ 次 $a_x\leftarrow a_x+a_x$ 即可（也就是后面代码中的 make 函数）。那么如何得到 $1$ 呢，大概分类讨论一下。如果 $a_0=a_1=0$，那么容易发现任何操作都无法制造出 $1$，也就是说最后 $a_2$ 一定是 $0$，恰好是正确答案；如果 $a_0+a_1\ne 0$，那么容易令 $a_3=[a_4< a_0+a_1]$ 得到一个 $a_3=1$，于是就解决了这个问题。

然后思考如何对一个数进行二进制拆分。最高位是很好判断的，如果 $2^t<c+1$，其中 $t$ 是位数的上限，那么显然可以发现 $c$ 的这一位是 $1$，否则就是 $0$。但是剩下的位置并没有那么好判断，因为我们并不能给上面的 $c$ 减去已经匹配的二进制位，但是可以反向思考，我们可以给当前匹配的 $2^t$ 加上前面已经匹配的数，如果和仍然小于 $c+1$，那么说明 $c$ 这一位是 $1$，更新那个匹配的和，随便维护一下即可。于是我们就得到了两个数的二进制拆分。

最后一步是简单的，就考虑枚举 $i,j$，如果 $1<A_i+B_j$，那么说明应该加上 $2^{i+j}$，否则就什么都不干，很好实现。

可以发现总的操作数是 $O(\log^3V)$ 的，可以通过。

```cpp
#include<bits/stdc++.h>
//#define feyn
using namespace std;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int cnt=4;
inline void make(int wh,int k){
	for(int i=1;i<=k;i++)printf("+ %d %d %d\n",wh,wh,wh);
}

void solve(int a[],int pl){
	int xx=++cnt,rx=++cnt,now=++cnt;
	for(int i=30;i>=0;i--){
		printf("+ 4 3 %d\n",++cnt);
		make(cnt,i);
		printf("+ %d %d %d\n",rx,cnt,xx);
		printf("+ 3 %d %d\n",pl,now);
		int mark=++cnt;
		printf("< %d %d %d\n",xx,now,mark);
		a[i]=mark;++cnt;
		printf("+ 4 %d %d\n",mark,cnt);
		make(cnt,i);
		printf("+ %d %d %d\n",cnt,rx,rx);
	}
}

int x[32],y[32];

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	
	puts("33947");
	puts("+ 0 1 3");
	puts("< 4 3 3");
	solve(x,0);solve(y,1);
	for(int i=0;i<=30;i++){
		for(int j=0;j<=30;j++){
			++cnt;
			printf("+ %d %d %d\n",x[i],y[j],cnt);
			printf("< 3 %d %d\n",cnt,cnt);
			make(cnt,i+j);
			printf("+ 2 %d 2\n",cnt);
		}
	}
	
	return 0;
}
```

---

