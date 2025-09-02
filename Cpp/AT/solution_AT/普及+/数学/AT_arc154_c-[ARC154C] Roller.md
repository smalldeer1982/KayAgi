# [ARC154C] Roller

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc154/tasks/arc154_c

長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N),B=(B_1,B_2,\dots,B_N) $ が与えられます。

あなたは以下の操作を好きな回数（$ 0 $ 回でもよい）繰り返すことができます。

- $ 1\ \le\ i\ \le\ N $ を満たす整数 $ i $ を選び、$ A_i $ を $ A_{i+1} $ で置き換える。
 
ただし、$ A_{N+1} $ とは $ A_1 $ のこととします。

$ A $ を $ B $ に一致させることが出来るか判定してください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 5000 $
- $ 1\ \le\ N\ \le\ 5000 $
- $ 1\ \le\ A_i,B_i\ \le\ N $
- $ 1 $ 個の入力に含まれるテストケースについて、それらの $ N $ の総和は $ 5000 $ を超えない。
 
### Sample Explanation 1

$ 1 $ 個目のテストケースでは、以下のように操作することにより $ A $ を $ B $ と一致させることが出来ます。 - $ i=1 $ を選ぶ。$ A_1 $ を $ A_2 $ で置き換える。$ A=(2,2) $ となる。 $ 2 $ 個目のテストケースでは、以下のように操作することにより $ A $ を $ B $ と一致させることが出来ます。 - $ i=4 $ を選ぶ。$ A_4 $ を $ A_1 $ で置き換える。$ A=(2,3,1,2) $ となる。 - $ i=2 $ を選ぶ。$ A_2 $ を $ A_3 $ で置き換える。$ A=(2,1,1,2) $ となる。 $ 3 $ 個目のテストケースでは、どのように操作しても $ A $ を $ B $ と一致させることは出来ません。

## 样例 #1

### 输入

```
3
2
1 2
2 2
4
2 3 1 1
2 1 1 2
2
1 1
2 2```

### 输出

```
Yes
Yes
No```

# 题解

## 作者：Daidly (赞：4)

# 题意

$t$ 组数据，每组给出 $n$ 和长度为 $n$ 的两个序列 $a,b$。定义一次操作为将 $a_{i}$ 赋值为 $a_{i+1}$，特别的，$a_{n+1}=a_1$。问 $a$ 是否能操作到 $b$。

# 题解

考虑将相邻的相同值合并成一个值，那么整个环形序列就分成了若干块。每次操作都可以将两个相邻块的边界左移，之后可能左边的块会消失，也可能只是大小缩短。抽象出以上是此题的难点。

显然这个块长是可以动态调整的，但是相对位置不能改变，也就是说，$a$ 能变到 $b$ 的充要条件是：压缩过的 $b$ 是压缩过的 $a$ 的环形从某一点断开后的子序列。

我们考虑能从某一点断开的条件是什么？需要一个无关紧要的点，它可以是在 $a$ 中而不在 $b$ 中的值，可以是 $a$ 中该值段数多余 $b$ 中的，也可以是相邻的相同值。冷静一下，可以发现相邻相同值的范围很广，只需要判断无相邻不同的情况即可。

当 $a$ 所有块长度均为 $1$，只需要判断 $a,b$ 是否完全相同。其余情况 $a$ 都可以环形旋转块，枚举起点判断是否是子序列就行了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=5e3+5;
int n,a[N<<1],b[N],ta[N],tb[N],na,nb,Ta[N],Tb[N];

bool solve(){
	n=read(),na=nb=0;
	for(int i=1;i<=n;++i)a[i]=a[i+n]=read();
	for(int i=1;i<=n;++i)b[i]=read();
	for(int i=1;i<=n;++i)if(a[i]!=a[i%n+1])ta[++na]=a[i];
	for(int i=1;i<=n;++i)if(b[i]!=b[i%n+1])tb[++nb]=b[i];
	if(!na)ta[++na]=a[1];
	if(!nb)tb[++nb]=b[1];
	if(na==n&&nb==n){
		for(int i=1;i<=n;++i)if(a[i]!=b[i])return 0;
		return 1;
	}
	for(int i=1;i<=na;++i){
		int pos=1;
		for(int j=0;j<na;++j)if(ta[(i+j)%na?(i+j)%na:na]==tb[pos])pos++;
		if(pos>nb)return 1;
	}
	return 0;
}

signed main(){
	int tt=read();
	while(tt--)puts(solve()?"Yes":"No");
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：1)

# [ARC154C] Roller

## 题面翻译

$t\ (1\ \le\ T\ \le\ 5000)$ 组数据，每组给出 $n$ 和长度为 $n$ 的两个序列 $a,b\ (1\ \le\ A_i,B_i\ \le\ N)$。定义一次操作为将 $a_{i}$ 赋值为 $a_{i+1}$，特别的，$a_{n+1}=a_1$。问 $a$ 是否能操作到 $b$。

## 思路

初看本题，模拟不行，那么就去找它的数学规律。

我们从序列 $a$ 中所含有的数字种类（不考虑数字的数量）来分类讨论：

- $a$ 中缺少 $b$ 中的任意数字。

毋庸置疑，这种情况下 $a$ 无法操作到 $b$。

- $a$ 中有 $b$ 中的任何数字且有 $b$ 中没有的数字

这种情况我们把多余的数字看成空白即可，因为我们很容易就可以将 $a$ 进行操作，使得 $a$ 变成下面这种情况。

- $a$ 中含有的数字恰好与 $b$ 中的数字相同。

这种情况我们需要着重考虑。

首先观察题目：$a_{i}$ 可以赋值为 $a_{i+1}$，$a_{n+1}=a_1$，很明显是一个环形结构。

我们不考虑每个数字的数量，只考虑每种数字与其他数字的相对位置。经过证明，我们得出：如果 $a$ 中每种数字与其他数字的相对位置与 $b$ 中每种数字与其他数字的相对位置相同，则能。反之则不能。

这一点也很好证明。

如果 $a$ 与 $b$ 初始状态就相同，那么 ~~结案~~ 肯定能操作。

如果 $a$ 与 $b$ 初始状态不同且每种数字与其他数字的相对位置在 $a$ 和 $b$ 中均相同，那么就肯定有数字多了，有数字少了。那么我们就可以让多了的数字（我们假定它为 $i$）后面的数字“侵占”$i$ 的位置，让 $i$ 的数量与 $b$ 中 $i$ 的数量相同，然后不断重复这个操作。这个操作就像推箱子，$i$ 多了，多出来的位置就相当于空位，有空位我们就可以慢慢地、一步一步的把箱子往前移，直到变成 $b$。

如果存在 $a$ 中某种数字与其他数字的相对位置与 $b$ 中的不同的情况，那么经过模拟，我们发现，除非让某些（种）数字全部消失，否则不可能让相对位置变成正确的。

例如 $[a_1,b_1,b_2,c_1,d_1,d_2,d_3,e_1,e_2]$序列中，我们要让数字 $b$ 出现在 $d$ 后面，考虑环形结构，我们就要覆盖 $a_1,e_2,e_1$ 这三个数字才行。如果这些数字是 $b$ 中没有的，那么可以进行操作。但是这种情况（即“$a$ 中含有的数字恰好与 $b$ 中的数字相同”）保证每种数字都有用，那么就不能进行操作了。

## 代码实现

我们将 $a$ 复制一遍接在 $a$ 末尾（这是处理环形问题的基本套路了）。把 $a$，$b$ 去重储存在数组 $ta,tb$ 中。注意，如果原数组的首位字符相同，则忽略末尾的数字。

首先判断是否“ $a$ 中缺少 $b$ 中的任意数字”。若否，则继续，去掉 $a$ 中多余的数字（即 $b$ 中没有的数字种类），枚举环 $a$ 的起点，与 $b$ 进行逐一比对。

如果满足要求，我们还需要检查一下 $a$ 中每种数字的个数。若每一种数字都只有一个，但位置和 $b$ 却是错位的，这种情况也不能操作（就相当于推箱子时缺少了最初的空位）。

## Code

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
#define i1n int i=1;i<=n;i++
#define in1 int i=n;i>=1;i--
using namespace std;

const int N=2e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int t,n,a[N],b[N],ta[N],flg,tb[N];

bool judge(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i+n]=a[i];
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	int na=0,nb=0;//记录去重后的数字个数
	for(int i=1;i<=n;i++)if(a[i]!=a[i%n+1])ta[++na]=a[i];//去重并处理环形
	for(int i=1;i<=n;i++)if(b[i]!=b[i%n+1])tb[++nb]=b[i];
	if(!na)ta[++na]=a[1];
	if(!nb)tb[++nb]=b[1];
	if(na==n&&nb==n){//说明每个数字都恰好只有一个(特判:每一种数字都只有一个，但位置和b却是错位的)
		for(int i=1;i<=n;i++)
			if(a[i]!=b[i])return 0;
		return 1;
	}
	for(int i=1;i<=na;i++){
		int idb=1;
		for(int j=0;j<na;j++){
			int ida;
			if((i+j)%na)ida=(i+j)%na;//处理环形
			else ida=na;	
			if(ta[ida]==tb[idb])idb++;
		}
		if(idb>nb)return 1;
	}
	return 0;
		
}

signed main(){
	cin>>t;
	while(t--){
		if(!judge())cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}

```




---

## 作者：EuphoricStar (赞：1)

被这题干爆了![](//图.tk/6)

考虑把 $a, b$ 两个环，值相等的元素压缩成一块。这样一次操作就是，选择两个相邻的块，把左边块长度减 $1$，右边块长度加 $1$。

特判 $a, b$ 所有块长都是 $1$ 的情况，这种情况不能操作。

排除掉上面的情况，我们断言：有解的充要条件是，存在某一种 $a$ 的顺序，使得 $b$ 是它的子序列。

充分性：因为存在长度 $> 1$ 的块，所以块的位置可以随意移动，只要保持相对位置不变即可。

必要性：考虑证明它的逆否命题。如果不是子序列，那 $a$ 不可能凭空中间冒出一个块使得有解，因为只能扩充或压缩块。

然后这个东西朴素 $O(n^2)$ 判定即可。

[code](https://atcoder.jp/contests/arc154/submissions/42874503)

---

## 作者：e4fsrc2e4fsrc2 (赞：1)

## [ARC154C Roller](https://www.luogu.com.cn/problem/AT_arc154_c)
## 题目翻译
给定两个长度为 $N$ 的序列:

$A:A_1,A_2,A_3,\cdots,A_N\quad B:B_1,B_2,B_3,\cdots,B_N$。

你可以执行以下操作（包括 $0$ 次）：选择一个整数 $i(1\le i\le n)$，然后令 $A_i=A_{i+1}$，特别的，令 $A_{n+1}=A_1$。

请问是否可以将 $A$ 序列变成 $B$ 序列。
## 思路分析
变化数 $A_i$ 相当于在 $A_i$ 的后面添加一个序列中有的数。

对于第 $i$ 到第 $j$ 个数（设这几个数均相等）来说，我们可以把这几个连续的数变成一样的数，所以把这一串数当成一个数来看。

所以，我们可以将序列 $A$ 的 $N$ 个数变成，一串长度为 $\verb|cnt1|$ 的序列 $\verb|x1|$。同理，序列 $B$ 就可以变成长度为 $\verb|cnt2|$ 的序列 $\verb|x2|$。

$1$.若这两串数的长度均为 $N$，那么就直接比较这两串数的每一位是否相等，相等就输出 $\verb|Yes|$，否则输出 $\verb|No|$。

$2$.如果这两串数的长度不相等，那么判断 $\verb|x2|$ 是否为 $\verb|x1|$ 的子序列即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=5e3+2;
int a[N],b[N],n,t;
int c1,c2,v1[N],v2[N];
void init(){c1=c2=0;}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;init();
        for(R i=1,x; i<=n; i++)cin>>a[i];a[n+1]=a[1];
        for(R i=1,x; i<=n; i++)cin>>b[i];b[n+1]=b[1];
		for(R i=1; i<=n; i++)if(a[i]!=a[i+1])v1[++c1]=a[i];
		for(R i=1; i<=n; i++)if(b[i]!=b[i+1])v2[++c2]=b[i];
		if(!c1)v1[++c1]=a[1];if(!c2)v2[++c2]=b[1];
		bool f=0;
        if(c1==n&&c2==n){
        	f=1;
        	for(R i=1; i<=n; i++)
				if(a[i]!=b[i]){f=0;break;}
		}else for(R i=1; i<=c1; i++){
			R cnt=1;
			for(R j=0; j<c1; j++)
				if(i+j==c1){if(v1[c1]==v2[cnt])cnt++;}
				else if(v1[(i+j)%c1]==v2[cnt])cnt++;
			if(cnt>c2){f=1;break;}
		}
		if(f)cout<<"Yes\n";
		else cout<<"No\n";
    }
    return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc154_c)
# 题目解释
共有 $T$ 组数据，对于每组数据有两个序列 $a$，$b$。其中每一次操作为 $a_{i}=a_{i+1}$，$a_{n+1}=a_{1}$。

求 $a$ 能否转移到 $b$。
# 题目分析
操作其实可以转化为在 $a_{}$ 的后面添加一个序列中有的数。

因为操作的特殊性，所以对于 $\forall i,j,a_{i}=a_{j}$ 的序列，我们可以把这一串数当成一个数来看。

所以，我们可以将序列 $a$ 转化为长度为 $p$ 的序列 $x$。同理，序列 $b$ 就可以转化为长度为 $q$ 的序列 $y$。

+ 若这两串数的长度均为 $n$。比较这两串数的每一位是否相等，相等就输出 `Yes`，否则输出 `No`。

+ 如果这两串数的长度不相等，那么判断 $y$ 是否为 $x$ 的子序列即可。
# 参考代码
~~码风太差就不放了。~~

---

