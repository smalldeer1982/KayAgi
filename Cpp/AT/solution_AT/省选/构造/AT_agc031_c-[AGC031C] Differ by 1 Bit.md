# [AGC031C] Differ by 1 Bit

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc031/tasks/agc031_c

整数 $ N,\ A,\ B $ が与えられます。 $ (0,\ 1,\ ...\ 2^N-1) $ の順列 $ (P_0,\ P_1,\ ...\ P_{2^N-1}) $ であって、 次の条件をすべて満たすものが存在するかどうか判定してください。 また、存在するなら $ 1 $ つ構成してください。

- $ P_0=A $
- $ P_{2^N-1}=B $
- すべての $ 0\ \leq\ i\ <\ 2^N-1 $ について、$ P_i $ と $ P_{i+1} $ は $ 2 $ 進数表記でちょうど $ 1 $ 桁だけ異なる。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 17 $
- $ 0\ \leq\ A\ \leq\ 2^N-1 $
- $ 0\ \leq\ B\ \leq\ 2^N-1 $
- $ A\ \neq\ B $
- 入力される値はすべて整数である。

### Sample Explanation 1

$ P=(1,0,2,3) $ を $ 2 $ 進数表記すると $ (01,00,10,11) $ となり、どの隣り合う $ 2 $ 要素もちょうど $ 1 $ 桁だけ異なります。

## 样例 #1

### 输入

```
2 1 3```

### 输出

```
YES
1 0 2 3```

## 样例 #2

### 输入

```
3 2 1```

### 输出

```
NO```

# 题解

## 作者：agicy (赞：7)

本文将同步发布于：

- [洛谷博客](https://www.luogu.com.cn/blog/Lu-Anlai/solution-at4693)；
- [csdn](https://blog.csdn.net/Lu_Anlai/article/details/117405503)；
- [博客园](https://www.cnblogs.com/Lu-Anlai/p/14829076.html)；
- [简书](https://www.jianshu.com/p/fe8c758e7873)；

## 题目

题目链接：[洛谷 AT4693](https://www.luogu.com.cn/problem/AT4693)、[AtCoder agc031_c](https://atcoder.jp/contests/agc031/tasks/agc031_c)。

### 题意概述

给定三个数 $n,a,b$，求一个 $0\sim 2^n-1$ 的排列满足下列三个条件：

- $p_1=a$；
- $p_{2^n}=b$；
- $\operatorname{popcount}(p_i\oplus p_{i+1})=1$，其中 $\oplus$ 表示按位异或。

请你判定是否可以构造并输出方案（若可以）。

## 题解

### 启发式的画图

直接考虑这个问题，似乎有些困难？

我们先用简单的语言，将它转化为一个图论问题。

#### 图论转化

如果两个整数 $a,b\in[0,2^n)$，满足 $\operatorname{popcount}(a\oplus b)=1$，那么我们就在 $a,b$ 之间连一条边。

那么问题转化为了给定起点与终点，求一条长度为 $2^n$ 的简单路径。

---

转化成了图论问题，我们肯定要用几何直观来看看这个图到底是什么样子，采用画图工具 [Graph Editor](https://csacademy.com/app/graph_editor/)，取 $n=2,3$ 时：

图片 $n=2$：![n2.png](https://i.loli.net/2021/05/30/eLqTFkylOmhbJp4.png)

图片 $n=3$：![n3.png](https://i.loli.net/2021/05/30/HR1B8AP5U6erQ2t.png)

这提醒我们，整个图将会形成一个 $n$ 维立方体。

具体地，我们考虑证明这件事，非常简单，换个角度即可。我们将一个二进制数各位上的数分开，看作各个维度的坐标值，例如 $0=(00)_2\to (0,0),2=(10)_2\to (1,0)$。那么我们不难得到此结论。

### 熟练解决图论问题

我们不难发现，这个图是一个二分图，其中左部点编号对应的二进制数中 $1$ 的个数为偶数，右部点编号对应的二进制数中 $1$ 的个数为奇数。

我们由此得到结论，如果存在答案，那么 $\operatorname{popcount}(a\oplus b)\equiv 1\pmod 2$。

这个条件对解的必要性已经得到证明，下面我们通过构造来证明其充分性。

### 构造与递推

首先为了化简问题，我们不难发现从 $a$ 走到 $b$ 等价于从 $0$ 走到 $a\oplus b$，这是因为异或的自反律与交换律，即 $p_i\oplus x\oplus p_{i+1}\oplus x=p_i\oplus p_{i+1}$。

**对于 $n$ 维立方体，它一定是由两个 $n-1$ 维立方体上下拼接而成。**

因此，我们考虑用类似数学归纳法的方式进行构造。

我们具有归纳基础，因为显然我们会 $n=1$ 时的情况（一条线段从 $0$ 走到 $1$）；

我们考虑如何通过 $n-1$ 维的方案构造 $n$ 维的方案，我们决定分类讨论：

- 根据上面的理论，我们分类讨论终点的位置（起点为 $0$）；
- 终点 $t$ 与起点在不同的层：我们找到一条合法的从起点走 $n-1$ 维空间到达 $x$ 的方案，然后 $x$ 走到另一层对应的点 $x'$，再在 $n-1$ 维空间中从 $0$ 走到 $t\oplus x'$ 的方案，$x$ 可任取；
- 终点 $t$ 与起点在同一层：我们直接从 $0$ 走到 $t$，然后把路径从路径中任意两个相邻点之间直接分割开来，在中间插入一个下层的 $n-1$ 维的路径。

上面的文字叙述可能有点难懂，我们画个三维空间的图：

第一种情况：![case1.png](https://i.loli.net/2021/05/30/HeqlW7TAPNBi842.png)

第二种情况：![case2.png](https://i.loli.net/2021/05/30/gYL341FCIcpmXJS.png)

至此，我们用构造的方法证明了条件的充分性，可解决本题。

时间复杂度为 $T(n)=2T(n-1)+\Theta(2^n)$，分析可知为 $\Theta(2^nn)$。

### 参考程序

参考程序中情况一选取 $x=1$，情况二选取起点和路径的第二个点。

`__builtin_parity(x)` 表示求 $x$ 的二进制表示中 $1$ 的个数的奇偶性，奇数为 $1$，偶数为 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline void writeln(const char *s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=17;

inline void solve(reg int x,reg int a,reg int ans[]){
	if(!x)
		ans[0]=0;
	else if(x==1)
		ans[0]=0,ans[1]=1;
	else{
		reg int val=1<<(x-1);
		if(a&val){
			solve(x-1,1,ans),solve(x-1,a^(val+1),ans+val);
			for(reg int i=val;i<(1<<x);++i)
				ans[i]=ans[i]^(val+1);
		}
		else{
			solve(x-1,a,ans),solve(x-1,ans[1],ans+val);
			for(reg int i=val;i<(1<<x);++i)
				ans[i]=ans[i]^val;
			static int tmp[1<<MAXN];
			tmp[0]=ans[0];
			for(reg int i=0;i<val;++i)
				tmp[i+1]=ans[i+val];
			for(reg int i=val+1;i<(1<<x);++i)
				tmp[i]=ans[i-val];
			for(reg int i=0;i<(1<<x);++i)
				ans[i]=tmp[i];
		}
	}
	return;
}

int n,A,B;
int ans[1<<MAXN];

int main(void){
	scanf("%d%d%d",&n,&A,&B);
	B^=A;
	if(__builtin_parity(B)){
		writeln("YES");
		solve(n,B,ans);
		reg int U=(1<<n)-1;
		for(reg int i=0;i<=U;++i)
			write(ans[i]^A),putchar(i==U?'\n':' ');
	}
	else
		writeln("NO");
	flush();
	return 0;
}
```


---

## 作者：zhylj (赞：2)

这大概是一个比较直接的构造方法的题解。

首先必要条件是 $A\oplus B$ 的二进制位个数是奇数，我们要断言它是充分的。

证明考虑归纳法，当 $n=1$ 时显然。

否则 $B$ 至少存在一位与 $A$ 在二进制下不同，否则 $A\oplus B=0$ 显然不满足条件，任取不同的一位，记这一位为第 $j$ 位，我们把所有数的第 $j$ 位和第 $n$ 位调换。

于是我们考虑的都是 $n$ 位为 $1$ 的方案，容易想到可以将序列拆成两半，前半部分 $A_0=A,B_0=A\oplus 1$（均为去掉第 $n$ 位，下同），后半部分 $A_1 = A,B_1=B$，做完之后给后半部分的第 $n$ 位设为 $1$ 即可。容易发现这两部分仍满足归纳假设。

然后把第 $j$ 位和第 $n$ 位再调换回来即可得到构造。然后就证完了。

模拟上述过程即可通过此题。

[提交记录](https://atcoder.jp/contests/agc031/submissions/26358848)。

---

## 作者：约瑟夫用脑玩 (赞：2)

神仙构造题解，$N\le17$ 想象 $N$ 维立方体真劝退，这里来一篇属于绿题(?)构造题的题解。

设 $X=P_1,Y=P_{2^n}$，以下 $\ \hat{}\ $ 代表二进制下的异或运算。

要求 $X\to Y$ 的一种方案，不难想到只要求出 $0\to (X\ \hat{}\  Y)$ 的一种方案，然后全部异或一个 $X$ 就变回来了。

再注意到我们并不关心 $X\ \hat{}\  Y$ 中 1 的相对位置，可以随便打乱，为了~~好看~~方便可以把它们全部放在前面，现在要求的就是形如 $(000..)_ 2\to(111..\text{(k个1)}000..)_ 2$ 的一种方案。

首先每一步相当于对某一位异或 1，总共有 $2^n-1$ 步，那么 $k$ 必须为奇数，否则无解。

为了使读者易懂，我先归纳 $k=1$ 的方案，以下设 $n=x,k=y$ 从 $(000..)_ 2$ 走到 $(111..\text{(k个1)}000..)_ 2$ 的方案为 $s_{x,y}$：

如果 $n=1$，异或一下即可，否则假设我们已构造出 $s_{n-1,1}$。

考虑在 $s_{n-1,1}$ 的每一步前面加上一个 0，那么我们通过 $2^{n-1}-1$ 步走出了 $(0000...)_ 2\to (0100..)_ 2$ 的方案。

然后我们走一步到 $(1100..)_ 2$，然后后面 $n-1$ 位按 $s_{n-1,1}$ 的方案倒着走回去即为 $(1000...)_ 2$。

至此我们轻易的构造出了所有的 $s_{n,1}$。

考虑倒着走的过程相当于：把开始操作后多出来的 1 通过 $s_{n-1,1}$ 给异或掉了，如果我们稍微错开一下，是不是就可以多异或出一个 1 来？

显然可以，把往回走的方案改为加了 1 的 $s_{n-1,1}$ ，并把第二个位置和第三个位置交换，那么我们走出来的就是 $(1110...)_ 2$，即 $s_{n,3}$ 而不是 $s_{n,1}$ 了。

那么我们可以很容易的想到，如果我们构造出了 $s_{n-1,x}$ 和 $s_{n-1,y}$ 的方案，那么我们可以通过先走 $s_{n-1,x}$，加个 1，再错开走 $s_{n-1,y}$ 的方式构造出 $s_{n,x+y+1-(\text{两方案没错开，也即重叠的部分})* 2}$。

其实到了这一步我们已经完了，因为我们已经可以依次构造出 $\forall n,\text{k是奇数},s_{n,k}$ 了，换下 1 的顺序，再异或一下就是原题所求。

但不难看出 $s_{n-1,x},s_{n-1,y}$ 有多种选择，任意一种都是对的。

为了方便，观察到 $y=1$ 时可以方便的构造出所有 $s_{n,k}$，包括 $s_{n,1}$，那么我们选用 $s_{n-1,1}$ 和 $s_{n-1,\max{(1,k-2)}}$ 来转移出所有的 $s_{n,k}$ 即可。

注意一下 $s_{n,1}$ 需要重叠一下异或抵掉，这边建议写倒着走的方便。

复杂度没细想，应该是 $O(n2^n)$ 的瓶颈。

[代码](https://www.luogu.com.cn/paste/hjcbpg8r)实现的并不好，正经的办法应该是写个函数，内部处理一下位置映射的关系，以达到换 1 的顺序。

我由于偷懒，前面换 1 的顺序只用两个位置交换，后面只用搞 1 次出答案就暴力换的，~~反正都不是瓶颈~~。

---

## 作者：zesqwq (赞：0)

## [AGC031C] Differ by 1 Bit sol

下文中用 $\oplus$ 表示异或。

一个很简单的套路题，就是在已知能简单判断是否合法的情况下递归构造。

首先我们发现，如果 $\text{popcnt}(A\oplus B)$ 是偶数显然无解，否则我断言它就是有解的。

那假设这个断言是正确的，考虑递归构造，我们发现这个构造看着就很松，我们可以大胆想象：我们取出 $A\oplus B$ 的最高位 $g$，然后考虑构造 $A,...,A\oplus t$ 和 $A\oplus t\oplus 2^g,...,B$ 这样的序列。

那么我们发现，如果 $t$ 二进制下不包含 $2^g$ 且 $\text{popcnt}(t)$ 是奇数，那么我们就可以递归构造，也就是说我们定义 $\text{solve}(A, B, \{S\})$ 表示要构造由 $A$ 到 $B$ 的并且只有 $S$ 中的这些二进制位可以作为相邻两个的异或值。

那么显然可以递归到 $\text{solve}(A, B, \{S\}) = \text{solve}(A, A\oplus t, \{S\}-  2^g) + \text{solve}(A\oplus t \oplus 2^g, B, \{S\}-  2^g)$。

那么我们就找到这样的 $t$ 后递归构造就好了，发现总是能找到的，于是就做完了。

```cpp
const int N = 1 << 20;

inline basic_string<int> solve(int n, int A, int B, int fw) {
    if (n == 1) return {A, B};
    int kel = A ^ B;
    int c = __lg(kel);
    for (int t = fw;; t = (t - 1) & fw) {
        if ((t >> c & 1 ^ 1) && __builtin_parity(t)) {
            auto a = solve(n - 1, A, A ^ t, fw ^ (1 << c));
            auto b = solve(n - 1, A ^ t ^ (1 << c), B, fw ^ (1 << c));
            return a + b;
        }
        if (t == 0) break;
    }
    assert(0);
}
int n, x, y;
int main() {
    read(n, x, y);
    if (!__builtin_parity(x ^ y)) return println("NO"s), 0;
    println("YES"s);
    auto c = solve(n, x, y, (1 << n) - 1);
    for (int v : c) write(v, ' ');
    return 0;
}
```

---

## 作者：Zpair (赞：0)

先考虑一个特殊化的问题：$A=0,B=2^n-1$。

首先不难发现其 $1$ 的个数是奇偶交替出现的，且第一个是偶数。

所以最后一个数应该是奇数，所以 $n$ 为偶数时一定无解，下面考虑奇数。

使用归纳来构造，首先 $n=1$ 只需 $0-1$ 即可。

考虑如何从 $n$ 到 $n+2$，把前面的两个与后面的分开考虑。

我们考虑再每一次后面的奇偶交替时都将前面的 $00$ 变回 $00$，只在最后一次变成 $11$，不难发现其是类似的。

下面令 $S$ 为偶串，$S'$ 为奇串。

$00S-01S-11S-10S-10S'-11S'-01S'-00S'$

$00S-01S-11S-10S-10S'-00S'-01S'-11S'$ 

所以归纳成立。

然后把过程中所有数都 $\oplus A$，等价于 $A=0,B=A\oplus B$ 的情况。

正确性易证，只需考虑异或对每一位是互不影响的即可。

下面令：$C=A\oplus B$，为了叙述简单，我们把 $0$ 的位移到后面，$1$ 的位移到前面。

于是构造就显然了，把后面 $0$ 的位按格雷码和逆格雷码的方式变换，$1$ 的位置按上面 $A=0,B=2^n-1$ 的方式变换，并且每次变换一次前面的 $1$ 就将后面的 $0$ 整体按格雷码或逆格雷码变换。

格雷码并不依赖于数字位数，且也是两个周期的变换回到 $0$，刚好可以和前面的奇偶交替放到一起，所以并不增加无解的判断。所以无解当且仅当 $A \oplus B$ 的 $1$ 的个数为偶数时无解。

---

