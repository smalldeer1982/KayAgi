# Yet Another Number Game

## 题目描述

Since most contestants do not read this part, I have to repeat that Bitlandians are quite weird. They have their own jobs, their own working method, their own lives, their own sausages and their own games!

Since you are so curious about Bitland, I'll give you the chance of peeking at one of these games.

BitLGM and BitAryo are playing yet another of their crazy-looking genius-needed Bitlandish games. They've got a sequence of $ n $ non-negative integers $ a_{1},a_{2},...,a_{n} $ . The players make moves in turns. BitLGM moves first. Each player can and must do one of the two following actions in his turn:

- Take one of the integers (we'll denote it as $ a_{i} $ ). Choose integer $ x $ $ (1\le x\le a_{i}) $ . And then decrease $ a_{i} $ by $ x $ , that is, apply assignment: $ a_{i}=a_{i}-x $ .
- Choose integer $ x $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF282D/cfd12ee35f4fd2cdcce2f524b91ce3785f31af4d.png). And then decrease all $ a_{i} $ by $ x $ , that is, apply assignment: $ a_{i}=a_{i}-x $ , for all $ i $ .

The player who cannot make a move loses.

You're given the initial sequence $ a_{1},a_{2},...,a_{n} $ . Determine who wins, if both players plays optimally well and if BitLGM and BitAryo start playing the described game in this sequence.

## 样例 #1

### 输入

```
2
1 1
```

### 输出

```
BitLGM
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
BitAryo
```

## 样例 #3

### 输入

```
3
1 2 1
```

### 输出

```
BitLGM
```

# 题解

## 作者：cff_0102 (赞：6)

枚举每个状态，用一个数组 $a$ 标记当前状态先手是否会赢（$1$ 表示先手赢，$0$ 表示先手输，后手赢）。

众所周知，当 $a_{i,j,k}=1$，则所有从状态 $(i,j,k)$ 能到的状态必须有一个为 $0$。当 $a_{i,j,k}=0$，所有能到状态 $(i,j,k)$ 的状态必然为 $1$。

所以直接循环枚举每个状态，假如这个状态是 $0$ 就把所有能到这个状态的状态设为 $1$。

$n=1$ 时不需要循环，直接结论：$x=0$ 是先手输。否则先手赢。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[332][332][332],b[332][332]; 
int main(){
	ios::sync_with_stdio(false);
	int n;cin>>n;
	if(n==3){
		int x,y,z;cin>>x>>y>>z;
		for(int i=0;i<=x;i++){
			for(int j=0;j<=y;j++){
				for(int k=0;k<=z;k++){
					if(a[i][j][k]==0){
						for(int t=1;t<=300;t++){
							if(i+t<=x)a[i+t][j][k]=1;
							if(j+t<=y)a[i][j+t][k]=1;
							if(k+t<=z)a[i][j][k+t]=1;
							if(i+t<=x&&j+t<=y&&k+t<=z)a[i+t][j+t][k+t]=1;
						}
					}
				}
			}
		}
		if(a[x][y][z]==0)cout<<"BitAryo";
		else cout<<"BitLGM";
	}if(n==2){
		int x,y;cin>>x>>y;
		for(int i=0;i<=x;i++){
			for(int j=0;j<=y;j++){
				if(b[i][j]==0){
					for(int t=1;t<=300;t++){
						if(i+t<=x)b[i+t][j]=1;
						if(j+t<=y)b[i][j+t]=1;
						if(i+t<=x&&j+t<=y)b[i+t][j+t]=1;
					}
				}
			}
		}
		if(b[x][y]==0)cout<<"BitAryo";
		else cout<<"BitLGM";
	}if(n==1){
		int x;cin>>x;
		if(x==0)cout<<"BitAryo";
		else cout<<"BitLGM";
	}
	return 0;
}
```

---

## 作者：skyskyCCC (赞：4)

## 前言。
博弈论，数据范围极小，讨论范围及其小。可以采用动态规划。

题意简述：两个人取石子，规则有两条。
- 每次选择 $n$ 堆石子中的任意一堆，取走任意多的石子，前提是能取到。
- 可以选择所有的石子堆，每堆取走一样多的石子，前提取走的石子数必须能在任意的石子堆中取到。

一个人先手，一个人后手，取到最后的胜利，且每次至少取一个石子，问谁必胜。
## 分析。
数据范围 $n\leq 3$ 显然我们可以分成三种情况：
- 只有一堆。

如果 $a_1$ 不等于 $0$ 即不为空，直接先手必赢，因为可以直接取走所有的这一堆的石子。
- 有两堆石子。

考虑胜负态划分。定义 $f\left(i,j\right)$ 表示第一堆有 $i$ 个石子第二堆有 $j$ 个时先手是否必胜，是则取 $1$ 反之取 $0$。

则分成三种可能的取法然后进行统筹转移即可。这三种条件是否可行取决于 $i$ 和 $j$ 的个数。即分成 $\leq i$ 和 $\leq j$ 以及小于等于它们之间的最小值进行划分即可。

记最多的那一堆石子数为 $a_k$ 个则时间复杂度为 $O\left(a_k^3\right)$。
- 有三堆石子。

一种方法已经很显然了，前缀和优化上面的转移方程即可。但是博弈论的题怎么能简简单单用动态规划水过去呢？有一个经典的思路：按位异或。我们令 $a$，$b$ 和 $c$ 分别表示三堆石子中取过后的剩余的石子数。

设 $a\oplus b=k$ 则分成两种情况讨论。如果 $c>k$ 则可以任意选择一个堆，然后取走一些石子（操作 $1$）让 $c$ 变成 $k$ 即可。如果 $c<k$ 则有 $a\oplus b>c$ 即 $a>b\oplus c$ 那么我们现在只需要再任选一堆取走一些石子（操作 $1$）使得 $a$ 变成 $b\oplus c$ 即可。得到一条结论：如果当前 $a\oplus b\oplus c\neq 0$ 则先手一定能找到一种操作使得 $a\oplus b\oplus c=0$ 换言之 $a\oplus b=c$。

此时后手就是 $a\oplus b\oplus c=0$ 的情况了。如果他进行操作 $1$ 则因为操作前 $a\oplus b=c$ 的情况存在，所以我们可以假设 $a\oplus b=k$ 则 $c=k$。然而题目要求至少取 $1$ 颗石子，违背了，所以不可以仍然存在这个状态。如果进行操作 $2$ 则我们设在每堆石子中取了 $x$ 个，由于 $a\oplus b=c$ 则 $a$，$b$ 和 $c$ 的各位在二进制下只有四种可能情况：
```
0 0 0
0 1 1
1 1 0
1 0 1
```
如果 $x$ 为奇数，则上述四种情况的末尾必发生翻转，此时 $a\oplus b\neq c$。如果 $x$ 为偶数，则我们不妨设 $x$ 的末尾有 $m$ 个 $0$ 然后删除它们，从后面的第一个 $1$ 看起，此时就转换成了奇数的情况。状态不可能存在。于是我们又得出一个结论：在后手的情况下，无论他如何操作，总不能使得 $a\oplus b\oplus c=0$ 依然存在。

那么这样重复操作，先手总能使得 $a\oplus b\oplus c\neq 0$ 而后手会永远面临着 $a\oplus b\oplus c=0$ 的情况。换言之，后手会出现 ```0 0 0``` 的情况，即都取完，而先手没有这种情况。

总结就是，如果 $a\oplus b\oplus c\neq 0$ 则先手必胜，反之先手必败。

代码如下，仅供参考：
```
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
int n;
int a,b,c;
bool dp[1005][1005];
int main(){
    cin>>n;
    if(n==1){
        cin>>a;
        if(a) cout<<"BitLGM\n";
        else cout<<"BitAryo\n";
    }
    else if(n==2){
        cin>>a>>b;
        dp[0][0]=0;
        for(int i=1;i<=500;i++){
            dp[i][0]=dp[0][i]=1;
        }
        for(int i=1;i<=500;i++){
            for(int j=1;j<=500;j++){
                for(int k=1;k<=i;k++){
                    dp[i][j]|=!(dp[i-k][j]);
                }
                for(int k=1;k<=j;k++){
                    dp[i][j]|=!(dp[i][j-k]);
                }
                for(int k=1;k<=min(i,j);k++){
                    dp[i][j]|=!(dp[i-k][j-k]);
                }
            }
        }
        if(dp[a][b]){
		    cout<<"BitLGM\n";
		}
		else cout<<"BitAryo\n";
    }
    else{
        cin>>a>>b>>c;
        if(a^b^c){
		    cout<<"BitLGM\n";
		}
		else cout<<"BitAryo\n";
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：cff_0102 (赞：4)

$n=1,2,3$ 都可以 $O(1)$。

$n=1$ 就不用说了。

$n=2$ 时，这道题就是威佐夫游戏，可以搜到证明，这里就直接放结论了。设 $a_1\le a_2$，当 $\lfloor\dfrac{\sqrt5+1}{2}(a_2-a_1)\rfloor=a_1$，则先手输，否则先手赢。

$n=3$ 时也是可以 $O(1)$ 做的。可以证明，$a_1\oplus a_2\oplus a_3=0$ 时先手必败。

首先证明：当 $a_1\oplus a_2\oplus a_3\ne0$，经过一步操作，是可以走到 $a_1\oplus a_2\oplus a_3=0$ 的情况的。

当 $a_1\oplus a_2\oplus a_3\ne0$，则 $a_1\oplus a_2\oplus a_3$ 的二进制一定至少有一位是 $1$。把最高位挑出来，那么那一位对应的 $a_1,a_2,a_3$ 原数的这一位一定是有两个 $0$ 一个 $1$，或者三个 $1$ 的。设其中两个这一位相同的数为 $a_2,a_3$，另一个这一位是 $1$ 的数为 $a_1$，则一定有 $a_2\oplus a_3<a_1$。那么，可以将 $a_1$ 取石子取成 $a_2\oplus a_3$ 这个数，取完后，发现 $a_1'\oplus a_2\oplus a_3=0$。所以，当 $a_1\oplus a_2\oplus a_3\ne0$，经过一步操作，是可以走到 $a_1\oplus a_2\oplus a_3=0$ 的情况的。

接着证明：首先证明：当 $a_1\oplus a_2\oplus a_3=0$，不管怎么操作，一步之后是一定会走到 $a_1\oplus a_2\oplus a_3\ne0$ 的情况的。

这也不难证明。假设走一步后得到的 $a_1'\oplus a_2'\oplus a_3'$ 还是 $0$，那么就有 $(a_1'+k)\oplus a_2'\oplus a_3'=0$（把 $+k$ 挪到其它地方一样的）或 $(a_1'+k)\oplus(a_2'+k)\oplus(a_3'+k)=0$。前者显然，后者通过观察最后一个变化的二进制位也能看出。

证明了当 $a_1\oplus a_2\oplus a_3\ne0$，经过一步操作，是可以走到 $a_1\oplus a_2\oplus a_3=0$ 的情况的，当 $a_1\oplus a_2\oplus a_3=0$，不管怎么操作，一步之后是一定会走到 $a_1\oplus a_2\oplus a_3\ne0$ 的情况的，那么就可以推导出 $a_1\oplus a_2\oplus a_3=0$ 时先手必败了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	if(n==1){
		int a;cin>>a;
		if(a)cout<<"BitLGM";
		else cout<<"BitAryo";
	}else if(n==2){
		int a,b;cin>>a>>b;
		if(a>b)swap(a,b);
		if(int(floor(1.0*(b-a)*(sqrt(5.0)+1.0)/2.0))==a)cout<<"BitAryo";
		else cout<<"BitLGM";
	}else{
		int a,b,c;cin>>a>>b>>c;
		if(a^b^c)cout<<"BitLGM";
		else cout<<"BitAryo";
	}
	return 0;
}
```

---

## 作者：pldzy (赞：2)

简单说一下两种做法，一种直接 dp，另一种是威佐夫博弈及其拓展。

-----

很经典的博弈论的 dp 转移。转移逻辑老套路了，若后继全部必胜则必败；若后继存在必败则必胜。

直接 dp 是 $O(V^4)$ 的。但很多时候向前转移和向后转移的复杂度是不一样的。考虑用每一种必败状态向后转移。同时试图证明必败状态的个数不会超过 $O(V^2)$。试图证明对于确定的 $a,b$，至多存在一种 $c$ 使得 $(a,b,c)$ 是必败。根据必败的定义，它的后继一定都是必胜，所以对于 $c' < c$，$(a,b,c')$ 一定是必胜。考虑 $c' > c$ 的情况，若它存在一个后继必败态 $(a,b,c)$，所以它也一定是必胜态。综上所述，必败态不会超过 $O(V^2)$。考虑只针对必败态进行 $O(V)$ 向后转移。总复杂度 $O(V^3)$，可过。

-----

首先我们回归一下 Nim 游戏。Nim 游戏当且仅当在全局异或和为 $0$ 的情况下才先手必败，反之先手总是必胜。这个是如何证明的？

首先，Nim 游戏证明的一个引理，对于 $n$ 堆石子，无论 $n$ 取多大，且当前所有堆数量异或和不为 $0$，那么经过一次操作之后，一定可以让它变为 $0$。考虑当前异或和 $res$ 的最高位，一定有一个 $x$，它的这一位是 $1$，那么我只要让 $x'$ 在这一位不为 $1$，后面取和 $res \oplus v$ 一样的即可。$v$ 是 $x$ 去掉 $res$ 最高位之前部分后的值。

第二个引理，如果当前异或和为 $0$，那么经过一次拿取之后，异或和一定不为 $0$。即 $res \oplus x \oplus x' = 0$，且 $res = 0$，则有 $x \oplus x' = 0$，即 $x= x'$，也就是一点没拿，不符合规则。

有了这两个引理，就很好证明了。说明在初始异或和不为 $0$ 时，先手总是能在不为 $0$ 的局面操作，并操作成为 $0$ 的局面给后手。直到最后后手无法继续操作，先手获胜。但在初始异或和为 $0$ 时，局面刚好调转，此时先手必败。

-----

回归到这个威佐夫博弈问题。原威佐夫博弈问题，$n=2$。考虑这个问题和 Nim 问题的不同之处在于，它多了一种操作，即给每一堆都同时拿走若干石子。

我们只考虑这个操作带来的、相较于 Nim 游戏的变化。在 $n=2$ 的情况下。很显然，此时异或和为 $0$ 的局面经过一次操作后，异或和仍然可以为 $0$。也即，先手如果把不为 $0$ 的局面操作为 $0$，反倒而会导致后手直接获胜。所以这个游戏就不是 Nim 游戏这么简单的了。

威佐夫博弈在 $n=2$ 的情况下，假设石子的个数分别为 $x, y( x < y )$，那么先手必败当且仅当 $\left\lfloor\frac{\sqrt 5 + 1}{2}(y-x)\right\rfloor = x$。对，前面那个是 $1.618$，写代码的时候直接写 $1.618$ 即可。细节在实现的时候，一定要注意转型问题，多打几个括号。正确写法：`(int)(1.618 * (b - a)) == a`。


但上述情况在 $n=3$ 时又有所不同了。考虑在 $n=3$ 时全局异或和为 $0$ 的一种情况。
```
x y z
1 0 1
0 0 0
1 1 1
0 1 1
```
由 $x \oplus y \oplus z = 0$ 可知，在任意一位，三者的情况一定属于上述 $4$ 种的一种。此时再考虑如果我们同时从这三个数中都拿走 $m$。若 $m$ 为奇数，三者最低位的 01 状态一定会同时取反。可显然，同时取反后，$3$ 个数在最低位的 01 状态不符合上述任何一种情况，即异或和为 $0$ 的情况不复存在。若 $m$ 为偶数，那就找到 $m$ 从低往高的第一个 $1$，一定也满足上述情况。

所以在 $n=3$ 的情况下，异或和为 $0$ 的局面经过一次操作后不可能依旧为 $0$。如此一来我们在 Nim 证明中的两条引理依旧适用，先手必败的条件也就依旧适用。

Bonus：在 $n$ 为奇数的情况下，似乎都适用。

---

## 作者：_edge_ (赞：2)

属于是比较简单的博弈论，可以考虑分开来进行讨论。

考虑 $n=1$ 的情况，显然，除了 $x=0$ 先手必赢，因为先手一下就能把石子全都取完。

考虑 $n=2$ 的情况，这时候并不是简单的动动脑子的事情了，就需要用到与博弈论有关的 DP。

如何设定这个状态？发现这个 $a_i$ 非常非常小，只有 $300$ ，可以压进状态里面，即 $f_{i,j}$ 表示两堆石子分别是 $i$ 和 $j$，然后如何转移？

看到题目所给出的条件，每次可以取出一些石头或者全都取出相同数量的，可以枚举哪一堆取出，然后取出的数量也可以枚举出来。

注意博弈论先后手在 DP 下是要反一反的，在转移的状态如果后手赢，那么转移过来就是先手必赢。

总时间复杂度 $O(n^3)$。

```cpp
		int x=0,y=0;
		cin>>x>>y;
		f1[0][0]=0;
		for (int i=1;i<=max(x,y);i++) f1[0][i]=f1[i][0]=1;
		for (int i=1;i<=x;i++)
			for (int j=1;j<=y;j++) {
				for (int k=1;k<=i;k++)
					f1[i][j]|=f1[i-k][j]^1;
				for (int k=1;k<=j;k++)
					f1[i][j]|=f1[i][j-k]^1;
				for (int k=1;k<=min(i,j);k++)
					f1[i][j]|=f1[i-k][j-k]^1;
			}
		if (f1[x][y]) cout<<"BitLGM\n";
		else cout<<"BitAryo\n";
		return 0;
```

然后我们考虑 $n=3$ 的情况，发现它也可以 DP，但是这个 DP 稍微要搞一搞，因为它整一个暴力 DP 复杂度是 $O(n^4)$，本地跑了 15s 多一点。

考虑如何去优化它，显然状态好像不太好进行优化，考虑优化转移。

转移的时候，我们发现它只和一维有关，搞一个类似于前缀和一样的东西就可以了。

然后还有全部取出来的方案，那就将 $3$ 堆都减去最小值，然后压进那个状态就可以了。

```cpp
		int x=0,y=0,z=0;cin>>x>>y>>z;
		f2[0][0][0]=0;
		for (int i=1;i<=max(max(x,z),y);i++) f2[i][0][0]=f2[0][i][0]=f2[0][0][i]=1;
		for (int i=0;i<=x;i++)
			for (int j=0;j<=y;j++) {
				for (int l=0;l<=z;l++) {
					if (i==j && j==l && j==0) continue;
					f2[i][j][l]|=f3[i][j][0]|f3[i][l][1]|f3[j][l][2];
					if (i<j && i<l) f2[i][j][l]|=f3[j-i][l-i][3];
					if (j<i && j<l) f2[i][j][l]|=f3[i-j][l-j][4];
					if (l<i && l<j) f2[i][j][l]|=f3[i-l][j-l][5];
//					for (int k=1;k<=i;k++) {
//						f2[i][j][l]|=f2[i-k][j][l]^1;
//						if (f2[i][j][l]) break;
//					}
//					if (f2[i][j][l]) continue;
//					for (int k=1;k<=j;k++) {
//						f2[i][j][l]|=f2[i][j-k][l]^1;
//						if (f2[i][j][l]) break;
//					}
//					if (f2[i][j][l]) continue;
//					for (int k=1;k<=l;k++) {
//						f2[i][j][l]|=f2[i][j][l-k]^1;
//						if (f2[i][j][l]) break;
//					}
//					if (f2[i][j][l]) continue;
//					for (int k=1;k<=min(i,min(j,l));k++) {
//						f2[i][j][l]|=f2[i-k][j-k][l-k]^1;
//						if (f2[i][j][l]) break;
//					}
					if (f2[i][j][l]==0) {
						f3[i][j][0]=1,f3[i][l][1]=1,f3[j][l][2]=1;
						if (i<j && i<l) f3[j-i][l-i][3]=1;
						if (j<i && j<l) f3[i-j][l-j][4]=1;
						if (l<i && l<j) f3[i-l][j-l][5]=1;
					}
				}
			}
		if (f2[x][y][z]) cout<<"BitLGM\n";
		else cout<<"BitAryo\n";
```

对于 $n=3$ 的情况下，有类似 nim 博弈可以做到 $O(1)$，~~请读者自行思考。~~

感谢阅读。

---

