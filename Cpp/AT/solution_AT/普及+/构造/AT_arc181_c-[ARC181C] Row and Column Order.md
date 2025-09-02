# [ARC181C] Row and Column Order

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc181/tasks/arc181_c

$ (1,2,\dots,N) $ の順列 $ P=(P_1,P_2,\dots,P_N),\ Q=(Q_1,Q_2,\dots,Q_N) $ が与えられます。

$ N $ 行 $ N $ 列からなるマス目の各マスに文字 `0`, `1` のいずれかを書き込み、以下の条件がすべて成り立つようにしてください。

- $ i $ 行目のマスに書かれている文字を、 $ 1,2,\dots,N $ 列目の順につなげて得られる文字列を $ S_i $ としたとき、辞書順で $ S_{P_1}\ <\ S_{P_2}\ <\ \dots\ <\ S_{P_N} $ が成り立つ
- $ i $ 列目のマスに書かれている文字を、 $ 1,2,\dots,N $ 行目の順につなげて得られる文字列を $ T_i $ としたとき、辞書順で $ T_{Q_1}\ <\ T_{Q_2}\ <\ \dots\ <\ T_{Q_N} $ が成り立つ
 
なお、どのような $ P,Q $ に対しても、条件をすべて満たす書き込み方が $ 1 $ つ以上あることが証明できます。

  辞書順で $ X\ が成り立つとは？ $文字列 $ X=X_1X_2\dots\ X_{|X|} $ と $ Y\ =\ Y_1Y_2\dots\ Y_{|Y|} $ について、**辞書順で $ X\ が成り立つ $**とは、下記の 1. と 2. のどちらかが成り立つことを言います。 ここで、$ |X|,\ |Y| $ はそれぞれ $ X,\ Y $ の長さを表します。

1. $ |X|\ \lt\ |Y| $ かつ $ X_1X_2\ldots\ X_{|X|}\ =\ Y_1Y_2\ldots\ Y_{|X|} $。
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |X|,\ |Y|\ \rbrace $ が存在して、下記の $ 2 $ つがともに成り立つ。 
  - $ X_1X_2\ldots\ X_{i-1}\ =\ Y_1Y_2\ldots\ Y_{i-1} $
  - $ X_i $ が $ Y_i $ より小さい。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 500 $
- $ P,Q $ は $ (1,2,\dots,N) $ の順列
- 入力はすべて整数
 
### Sample Explanation 1

この入出力例の場合、 $ S_1= $`001` $ ,\ S_2= $`101` $ ,\ S_3= $`110` であり、 $ T_1= $`011` $ ,\ T_2= $`001` $ ,\ T_3= $`110` です。よって $ S_1\ <\ S_2\ <\ S_3 $ かつ $ T_2\ <\ T_1\ <\ T_3 $ が成り立ち、条件を満たします。

## 样例 #1

### 输入

```
3
1 2 3
2 1 3```

### 输出

```
001
101
110```

## 样例 #2

### 输入

```
15
8 15 10 2 4 3 1 13 5 12 9 6 14 11 7
4 1 5 14 3 12 13 7 11 8 6 2 9 15 10```

### 输出

```
010001111110101
001000000101001
010001001100010
010000011110010
010011101101101
100101110100000
111100011001000
000001001100000
100011011000101
000111101011110
101010101010101
011010101011110
010011000010011
100110010110101
000101101100100```

# 题解

## 作者：mayike (赞：10)

一道于我而言很棒的构造题。

~~当然我是个菜鸡，我也是看了题解才会的。~~

[[ARC181C] Row and Column Order](https://atcoder.jp/contests/arc181/tasks/arc181_c)

## 思路

首先，这题的 $N\times N$ 的网格就隐约透露点什么了。

对于字典序的 $S_i<S_j$，我这种蒟蒻还是知道解决问题要简化的，显然 $S_i \in S_j$ 将会方便许多；不然我仍然不会做。

若如此，对于 $n$ 行，每行 $p_i$ 我们都复制 $p_{i-1}$ 行的串然后再将一个原来是 $0$ 的位置变为 $1$，这么做满足了行的字典序要求，因为我们对每行 $p_i$ 都比上一行 $p_{i-1}$ 多了一个 $1$。上面 $N\times N$ 的题目条件就给这种构造起到很恰好的保障作用了，使得按添加顺序来说第 $i$ 行有 $i$ 个 $1$，对列的构造有很大的保障。

现在考虑列，发现列构成了一个奇妙的叠加方式：

```cpp
1 0 0 0
1 1 0 0
1 1 1 0
1 1 1 1
```

也就是说，越先添加 $1$ 的列到最后变得越多。由于我们的列可以每行随便多填一个 $1$，那么我们按 $q_i$ 从大到小的顺序来填充的话是完全可以满足字典序要求的。

那么这题就解决了，实在是很有意义的一题！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,a[N][2],b[N][N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int j=0;j<=1;j++)
		for(int i=1;i<=n;i++)cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=n-i+1;j<=n;j++)b[a[i][0]][a[j][1]]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)cout<<b[i][j];
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Register_int (赞：10)

不会做 Ad-hoc 应该先想想自己的原因。

如果你把 $A<B$ 改成 $A\subset B$，那么有个显然的做法：对于第 $A_i$ 行，将第 $B_{n-i+1}\sim B_n$ 列全填上。横着看，$A_i$ 在 $A_{i-1}$ 的基础上多加了个 $B_{n-i+1}$。竖着看，$B_i$ 在 $B_{i-1}$ 的基础上多加了个 $A_{n-i+1}$，所以是对的。

然后你会发现 $A\subset B$ 等价于 $A<B$，所以做完了……

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e2 + 10;

int n, a[MAXN], b[MAXN]; char s[MAXN][MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) s[i][j] = '0';
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) s[a[i]][b[n - j + 1]] = '1';
	}
	for (int i = 1; i <= n; i++) printf("%s\n", s[i] + 1);
}
```

---

## 作者：linjunye (赞：8)

给一种人类智慧做法。

假设构造出的矩阵中，里面的数可以任意。

那么，根据样例，若我们可以不满足条件 $2$，那么可以轻松构造出如下矩阵：

```
111
222
333
```

如果我们可以不满足条件 $1$，那么可以轻松构造出如下矩阵：

```
213
213
213
```

这个很好构造，就是先构造 $1$ 列 / 行，再往右 / 下填充。

然后我们充分发扬人类智慧，将两个矩阵相加，得：

```
324
435
546
```

神奇的是，它竟然能满足两个条件（就像我把两条限制相加一样）。

但是这个矩阵只能有 $0$ 和 $1$ 两个数怎么办？

于是我们继续发扬人类智慧，使用刚才构造的矩阵，然后将 $\le n$ 的数改成 $0$，否则改成 $1$。

最后，我们的最终矩阵如下（有兴趣的可以验证一下）：

```
001
101
111
```

那么我们就能在最短的思考时间内做出此题了。

[代码](https://atcoder.jp/contests/arc181/submissions/56493113)。

---

## 作者：晴空一鹤 (赞：6)

三行哥过于神仙，这里讲一个常人做法。

首先取出排名最大的行，全填 $1$，显然这样能为后面的解创造最大生存空间。

这时你会发现一个非常好的性质，就是前面填的行对列的大小关系没有影响，所以相当于把这一行删了。

我们把这一行叉掉，再对列进行类似操作，矩阵大小减 $1$。

但在这之后我们不能再找最大的行全填 $1$ 了，怎么办？找最小的行全填 $0$ 再叉掉，列类似。

然后就是按照 叉掉最大的行->叉掉最大的列->叉掉最小的行->叉掉最小的列 这样循环，直到矩阵被叉完，然后输出就行了。

正确性感性理解一下即可，证明也并不困难。

#### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[505],q[505],a[505][505];
int main(){
  cin>>n;
  for(int i=1;i<=n;i++)cin>>p[i];
  for(int j=1;j<=n;j++)cin>>q[j];
  int i=1,j=n;
  for(i=1,j=n;j-i>=0;){
  for(int k=1;k<=n;k++)if(a[p[i]][k]==0)a[p[i]][k]=1;
  for(int k=1;k<=n;k++)if(a[k][q[i]]==0)a[k][q[i]]=1; 
  for(int k=1;k<=n;k++)if(a[p[j]][k]==0)a[p[j]][k]=2;
  for(int k=1;k<=n;k++)if(a[k][q[j]]==0)a[k][q[j]]=2;
  i++,j--;
  }
  for(int i=1;i<=n;i++){
  for(int j=1;j<=n;j++)
  cout<<a[i][j]-1;
  cout<<"\n";
  }
}
```

---

## 作者：Hell0_W0rld (赞：4)

# ARC181C Row and Column Order 题解
省流：A>B>C。

第一次元 ARC 给我吓到了。
## 1 题面翻译

给你 $(1,2,\dots,N)$ 的两个排列 $P=(P_1,P_2,\dots,P_N)$ 和 $Q=(Q_1,Q_2,\dots,Q_N)$。

请在 $N\times N$ 的网格中的每个单元格中写入一个字符 `0` 和 `1`，以便满足以下所有条件：

- 假设 $S_i$ 是把第 $i$ 行中的字符从 $1$ 列连接到 $N$ 列得到的字符串，则 $S_{P_1}<S_{P_2} <\dots<S_{P_N}$。
- 假设 $T_i$ 是把从第 $i$ 列中的字符从 $1$ 行连接到 $N$ 行得到的字符串，则 $T_{Q_1}< T_{Q_2}<\dots<T_{Q_N}$。

求一个满足条件的 `01` 矩阵。
## 2 破题思路
我们初始化一个这样的矩阵。

```
00000...000
00000...001
00000...011
...     ...
01111...111
```
这个矩阵满足 $P_i=Q_i=i$ 的矩阵，正确性显然。

然后我们把这个矩阵的第一行换到 $P_1$ 行，第二行换到 $P_2$ 行，以此类推。那么我们可以得到一个矩阵满足行大小关系的限制。（因为原矩阵中 $S_1<S_2<\cdots<S_N$）

接着在列处进行同样的交换，则满足列的限制（若 $Q_i<Q_j$，则满足若 $A_{i,x}=1$，则 $A_{j,x}=1$，且$T_i\neq T_j$，得证，行同理。）

然后你就做完了。

~~阴间样例~~
## Code
```cpp
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)


rep(i,1,n)cin>>s[i],sp[s[i]]=i;
rep(i,1,n)cin>>t[i],tp[t[i]]=i;
rep(i,1,n)Rep(j,n-i+2,n)a[i][j]=1;
rep(i,1,n){
	rep(j,1,n)cout<<a[sp[i]][tp[j]];
	cout<<endl;
}
```

---

## 作者：MarSer020 (赞：4)

萌萌构造/se

$\Large\text{Solution}$

考虑字典序是不好判断的，所以要将字典序的条件放宽。

考虑对于两个数 $i\not=j$，若 $i\land j=i$，则有 $i<j$，即 $i$ 的字典序小于 $j$。所以将字典序关系转化为包含关系是一个好的选择。

考虑如何构建包含关系：对于 $p_i$ 行，可以钦定其恰好包含 $i$ 个 $1$，且是 $p_{i+1}$ 行的真子集。考虑如何钦定：容易发现令 $\{q_j\mid j\in \left[n-i+1,n\right]\}$ 列为 $1$ 是合法的。于是就做完了。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[505],b[505];
bool c[505][505];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=1;i<=n;i++)
		for(int j=n-i+1;j<=n;j++)
			c[a[i]][b[j]]=1;
	for(int i=1;i<=n;i++,cout<<'\n')
		for(int j=1;j<=n;j++)
			cout<<c[i][j];
	return 0;
}
```

---

## 作者：fantastic_dream (赞：2)

#### 解答
发现只有对行和列的限制，我们知道，每行或每列最多能放 $n$ 个 $0$，那么我们考虑直接用 $0$ 的个数来区分大小。具体地，先处理行上的，按字典序关系 $S_{P_1} < S_{P_2} < \dots < S_{P_N}$，分别在第 $P_1,P_2 ,\dots,P_n$ 行上分别放 $1,2,\dots,n$ 个 $0$，剩下的放 $1$，然后要思考的就是在每行中哪些位置能放 $0$。

非常简单，我们已经知道每行放多少个 $0$ 和 $1$，我们只要按照列的字典序关系 $T_{Q_1} < T_{Q_2} < \dots < T_{Q_N}$ 来放 $0$，具体地，对于 $Q_i$ 列，若该行能放的 $0$ 的个数不小于 $i$ 则放 $0$，反之放 $1$。一这样的策略放满即可。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int ma=505;
int n,p[ma],q[ma],sz[ma][ma];
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>p[i];
	for(int i=1;i<=n;i++)	cin>>q[i];
	for(int i=1;i<=n;i++){
		int now=n-i+1;
		for(int j=1;j<=n;j++){
			if(j<=now)	sz[p[i]][q[j]]=0;
			else	sz[p[i]][q[j]]=1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)	cout<<sz[i][j];
		cout<<'\n';
	}
	return 0;
} 
```

---

## 作者：Hadtsti (赞：2)

### 题意简述

给定 $1\sim n$ 的排列 $p_i$ 和 $q_i$。构造一个 $n\times n$ 的 $01$ 矩阵 $M$，使得 $p_i$ 为 $1\sim n$ 按照 $M$ 对应行的字符串字典序升序后的排列，$q_i$ 为 $1\sim n$ 按照 $M$ 中对应列的字符串字典序升序后的排列。同时应保证 $M$ 不存在两行或两列完全相同。

### 题目分析

赛场上 B 竟然忘记判断长度为负数的无解情况，死磕到最后也没看出来。无力吐槽最近的做题状态，总结一下就是菜就多练。

C 赛后 10min 会了，绷。

再审一遍题：需要保证对每个 $i=1,\cdots,n-1$，答案矩阵的第 $p_i$ 行严格小于第 $p_{i+1}$ 行。转化一下就是设 $j$ 是满足 $M_{p_i,j}\neq M_{p_{i+1},j}$ 的最小的 $j$，必有 $M_{p_i,j}<M_{p_{i+1},j}$。我们不妨先严格控制这两行的每一个位置，使得至少存在一个 $j$ 使得 $M_{p_i,j}<M_{p_{i+1},j}$，而其它位置都满足 $M_{p_i,j}=M_{p_{i+1},j}$，看看能不能构造出一种合法情况。很幸运，是可以的。

姑且扔掉列的限制不管。我们设 $a_i$ 满足 $a_{p_i}=i$。那么 $M$ 第 $i$ 列的大小就与 $a_i$“正相关”（只是一个不严谨的称呼）。考虑到答案矩阵是 $01$ 矩阵，我们可以令 $M$ 的值变为关于 $a_i$ 的表达式。具体地，我们可以令 $M_{i,j}=[a_i+j>n]$。这样对于不同的两行，一定会有一些位置满足 $a_i$ 更大的那行是 $1$ 而 $a_i$ 更小的那行是 $0$。至此行的限制解决了。

列的限制同理。注意到交换上文构造的 $M$ 的两列并不会破坏行的限制，那我们完全可以如法炮制，设序列 $b_i$ 满足 $b_{q_i}=i$，取 $M_{i,j}=[a_i+b_j>n]$ 即可。问题解决。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[510],b[510];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
		scanf("%d",&x),a[x]=i;
    for(int i=1;i<=n;i++)
    	scanf("%d",&x),b[x]=i;
    for(int i=1;i<=n;printf("\n"),i++)
        for(int j=1;j<=n;j++)
        	printf("%d",a[i]+b[j]>n);
    return 0;
}
```

---

## 作者：banned_gutongxing (赞：1)

## 思路

简单。

首先我们可以考虑按着 $p$ 数组的顺序遍历。

接着因为题目要求字典序最小，我们可以将 $q$ 数组倒着来讲后面 $i$ 个标记为 $1$，此时我们保证了 $p$ 数组中是字典序从小到大的，又保证了 $q$ 数组中是按照字典序排序的。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//#define int long long
namespace gtx{
//	Fast IO
    void read(int &x){
        x = 0;int h = 1;char tmp;
        do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
        while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
        x*=h;
    }
    void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
    void write(char x){putchar(x);}
    void write(int x){
        if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
        do{st[++tot]=x%10,x/=10;} while(x);
        while(tot){putchar(st[tot--]+'0');};
    }
    void write(int x,char y){write(x);write(y);}
    const int MAXN = 510;
    int n,p[MAXN],q[MAXN],ans[MAXN][MAXN];
    signed main(){
        read(n);
        for(int i = 1;i<=n;i++){
            read(p[i]);
        }
        for(int i = 1;i<=n;i++){
            read(q[i]);
        }
        reverse(q+1,q+1+n);
        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=i;j++){
                ans[p[i]][q[j]] = 1;
            }
        }
        for(int i = 1;i<=n;i++){for(int j = 1;j<=n;j++) write(ans[i][j]);write(endl);}
        return 0;
    }
}
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T = 1;
//	gtx::read(T);
    while(T--) gtx::main();
    return 0;
}
```

---

## 作者：Shxt_Plus (赞：0)

神秘构造题。

题意：给出两个长度为 $n$ 的排列 $P,Q$。

定义 $S_i$ 为 $01$ 矩阵中的第 $i$ 行组成的字符串，$T_i$ 为 $01$ 矩阵中第 $i$ 列组成的字符串。

让你构造出一个 $01$ 矩阵使得 $S_{P_1}<S_{P_2}<\cdots<S_{P_n}$ 且 $T_{Q_1}<T_{Q_2}<\cdots<T_{Q_n}$。

显然若一个 $S_a$ 的 $1$ 完全包含 $S_b$ 且数量比 $S_B$ 多那么必然存在 $S_a>S_b$，所以考虑让 $S_{p_i}$ 拥有 $i$ 个 $1$，并将这些 $1$ 放在 $Q_n,Q_{n-1},\cdots,Q_{n-i+1}$ 列，对于行之间肯定满足，考虑列，显然 $Q_i$ 列有 $i$ 个 $1$，且 $Q_{i-1}$ 中所有的 $1$ 在 $Q_i$ 列肯定也是 $1$，所以列之间也满足。

---

## 作者：Halberd_Cease (赞：0)

比较智慧的一道题，和出题人脑电波对上了就很简单。

题目大概是说给你两个排列 $p,q$，你需要构造一个 01 矩阵，使得按每一行划分一个字符串，第 $p_i$ 行的排名是 $i$，按每一列划分字符串，第 $q_i$ 列的排名是 $i$。

考虑找一下特殊情况，如果 $p=q=(1,2,\dots,n)$，那么显然可以构造一组左上半部分是 0、右下半部分是 1 的矩阵，更形式化的来讲，对于矩阵中第 $i$ 行 $j$ 列的元素，如果 $i+j<n$，那么这个元素是 0，否则是 1，我们设这个矩阵

我们考虑调整，首先如果保持 $q=(1,2,\dots,n)$，只有 $p$ 变化的话，我们可以通过对 $p,q$ 都有序的答案进行相应的调整，使得原答案矩阵的 $p_i$ 行对应现答案矩阵的第 $i$ 行。这样操作，$p$ 的要求一定可以满足。考虑 $q$，我们需要使相邻两列的字典序相对大小不变，这也是一定可以满足的。考虑相邻两列，其对应位置元素不同的情况会且仅会出现一次，而且一定是原来字典序相对较大的是 1，较小的是 0，因此可以满足。

考虑在上面讨论的基础上，再变化 $q$，也可以通过直接按列排序，将交换了行的矩阵第 $q_i$ 列放到第 $i$，列上，如此，矩阵的列排名要求就可以满足。考虑每行，在仅交换列的操作中，行排名也是不会发生变化的，证明可以参考为什么交换行的时候列的排名不变，上面有讲。

所以你只需要把 $p=q=(1,2,\dots,n)$ 的答案矩阵构造出来，然后按要求交换行和列即可，时间复杂度 $O(n^2)$，瓶颈在于输出。

---

## 作者：Crazyouth (赞：0)

## 分析

先提出一个结论，对于一个三角形，例如：

```
0001
0011
0111
1111
```

无论如何交换两列，所有行的字典序大小关系不变，因为若某一行某一位为 $1$，那么它下面的行的那一位都是 $1$，但是该行总有一位会满足它是 $0$ 但它下面是 $1$。

因此我们先构造这样一个三角形，把它的每一行先按题目要求排序，再交换它的列，就可以构造出满足题目条件的解。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[510],t[510],u[510];
int p[510],q[510],id[510],n;
string check(int k)
{
	string ret=" ";
	for(int i=1;i<=n;i++) ret+=t[i][k];
	return ret;
}
int cmp(int x,int y)
{
	return check(x)<check(y);
}
void cpt(int x,int y)
{
	for(int i=1;i<=n;i++) u[i][y]=t[i][x];
} 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		id[i]=i;
		s[i]=" ";
		t[i]=" ";
		u[i]=" ";
		for(int j=1;j<=n;j++)
		s[i]+='0',t[i]+='0',u[i]+='0';
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		s[i][n-j+1]='1';
	}
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) cin>>q[i];
	for(int i=1;i<=n;i++) t[p[i]]=s[i];
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;i++) cpt(id[i],q[i]);
	for(int i=1;i<=n;i++) cout<<u[i].substr(1,n)<<'\n';
	return 0;
}

---

## 作者：stswkl (赞：0)

## 题意
给你两个 $1,2,3,\dots,N$ 的排列 $P$ 和 $Q$，要求你构造一个 $N\times N$ 的 $01$ 矩阵 $X$，满足 $X$ 的第 $P_1$ 行的字典序小于 $X$ 的第 $P_2$ 行的字典序，以此类推；$X$ 的第 $Q_1$ 列的字典序小于 $X$ 的第 $Q_2$ 列的字典序，以此类推。

## 思路
对于这个问题，我们可以先构造一个 $01$ 矩阵 $A$ 满足越往下字典序越大和越往右字典序越大，然后在 $A$ 的基础上构造满足 $P$ 要求的 $01$ 矩阵 $B$，继而可以在 $B$ 的基础上构造满足 $Q$ 要求的 $01$ 矩阵 $X$。

矩阵 $A$ 构造如下，至于为什么这样构造后面会讲。

$$
A=\begin{bmatrix}
0&0&0&\cdots&0&0&1\\
0&0&0&\cdots&0&1&1\\
\vdots&\vdots&\vdots&\ddots&\vdots&\vdots&\vdots\\
0&1&1&\cdots&1&1&1\\
1&1&1&\cdots&1&1&1
\end{bmatrix}
$$

具体的，我们可以把 $P_i$ 视为 $B$ 的第 $P_i$ 行是 $A$ 中字典序第 $i$ 小的行，也就是 $A$ 的第 $i$ 行，这样构造出来的 $01$ 矩阵 $B$ 必然满足 $P$ 要求，$Q_i$ 同理，我们可以如何证明改变列的顺序可以让这个矩阵满足 $Q$ 的要求，证明如下：
> 不妨设 $B$ 中有两行 $B_i$ 和 $B_j$ 满足 $B_i<B_j$，在矩阵 $A$ 的构造下，若有 $B_i<B_j$，则 $B_i$ 的前 $x$ 个元素与 $B_j$ 的前 $x$ 个元素相同，$x$ 显然可以为 $0$，且 $B_{i\ x+1},B_{i\ x+2},\dots,B_{i\ x+y}(y>0)$ 均为 $0$, $B_{j\ x+1},B_{j\ x+2},\dots,B_{j\ x+y}$ 均为 $1$，$B_i$ 和 $B_j$ 的其他元素均为 $1$，那么对于某一列 $z$，有 $B_{i\ z}\le B_{j\ z}$，故无论怎么改变列的顺序都有 $B_i<B_j$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
int n,p[N],q[N];
int a[N][N],b[N][N],c[N][N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<=n;i++)cin>>q[i];
	for(int i=1;i<=n;i++)
	for(int j=n;j>=n-i+1;j--)
		a[i][j]=1; //构造 A 矩阵
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		b[p[i]][j]=a[i][j]; //构造 B 矩阵
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		c[j][q[i]]=b[j][i]; //构造 C矩阵
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)cout<<c[i][j];
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：xyz105 (赞：0)

$$\begin{Bmatrix}\color{red}\LARGE\bold{Solution}\\\normalsize\texttt{No.010 }\bold{AT\_arc181\_c}\end{Bmatrix}\times\footnotesize\texttt{ By Xyz105}$$

### 题目描述

给定两个长度为 $n$ 的排列 $P,Q$。试构造出一个 $N\times N$ 的 $01$ 矩阵，要求满足：
- 对于每个 $i$，将该矩阵的上数第 $i$ 行看成长度为 $N$ 的 $01$ 字符串 $S_i$，则有 $S_{P_1}<S_{P_2}<\cdots<S_{P_N}$。
- 对于每个 $i$，将该矩阵的左数第 $i$ 列看成长度为 $N$ 的 $01$ 字符串 $T_i$，则有 $T_{Q_1}<T_{Q_2}<\cdots<T_{Q_N}$。

称两个字符串 $A,B$ 为小于关系当且仅当 $A$ 的字典序比 $B$ 小。


### 解题思路

场上唐了没想出来。在此 Orz @STUDENT0。

先处理出对于所有 $i$，该矩阵的上数第 $i$ 行在字典序意义下应该是第几小的，记作 $P\_rk_i$。读入时令所有 $P\_rk_{P_i}=i$ 即可。对于左数第 $i$ 列也同理，令所有 $Q\_rk_{Q_i}=i$。

接下来就是本题最关键的部分。如果两个长为 $N$ 的 $01$ 字符串 $A,B$ 满足 $A\subsetneq B$（即对于每一位 $i$ 有 $A_i\le B_i$，如果 $A_i$ 为 $1$ 则 $B_i$ 必为 $1$，$B_i$ 为 $1$ 时 $A_i$ 不一定为 $1$，注意 $A,B$ 不能相同），那么字典序意义下 $A<B$ 也必然满足。

构造方法：令第 $i$ 行代表的 $01$ 串 $S_i$ 中有 $P\_rk_i$ 个 $1$，并且这 $P\_rk_i$ 个 $1$ 所在的列的 $Q\_rk$ 值应该是前 $P\_rk_i$ 大的（$n-Q\_rk+1$ 是前 $P\_rk_i$ 小的）。

正确性证明：  
1. 对于两行 $a,b$ 满足 $P\_rk_a<P\_rk_b$，即要求第 $a$ 行代表的串小于第 $b$ 行，不难发现如果第 $j$ 列满足 $Q\_rk_j$ 值是前 $P\_rk_a$ 大的，那么 $Q\_rk_j$ 值也是前 $P\_rk_b$ 大的，反之则不一定。于是行方面符合题意。
2. 对于两列 $a,b$ 满足 $Q\_rk_a<Q\_rk_b$，即要求第 $a$ 列代表的串小于第 $b$ 列，不难发现某一列的 $Q\_rk$ 值越大，就越有更多的行在这一列设为 $1$，同上述分析可得列方面符合题意。


### 参考代码

代码写法整体较简单。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n, p[510], q[510];

char res[510][510];

int main()
{
	cin >> n;
	for (int i = 1, i1; i <= n; i++) cin >> i1, p[i1] = i;
	for (int i = 1, i1; i <= n; i++) cin >> i1, q[i1] = i;
	memset(res, '0', sizeof(res));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (p[i] >= n - q[j] + 1) res[i][j] = '1';
	for (int i = 1; i <= n; i++)
		res[i][n + 1] = '\0', printf("%s\n", res[i] + 1);
	
	return 0;
}
```

---

## 作者：Lame_Joke (赞：0)

- ### 题目大意

  给定 $P$ 数组和 $Q$ 数组，试构造一个由 $0$ 和 $1$ 组成的 $N\times N$ 矩阵，使矩阵每行连在一起组成的字符串按字典序排列顺序按照 $P$ 数组升序，每列按照 $Q$ 数组升序排列。

- ### 大体思路

  此题思想十分贪心，我们可以考虑当 $P$ 数组和 $Q$ 数组中的数都是按照 $1$ 到 $N$ 升序的顺序排列时，矩阵的情况，其中一种情况一定是以矩阵的右上角到左下角为对角线，上面是 $0$，下面是 $1$。那么构造出来这样一个数组有什么用呢？我们只需要对 $Q$ 和 $P$ 数组进行排序，在交换的时候也交换一下矩阵中的对应的行列，最后就可以得到答案矩阵。

- ### 具体实现

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,p[505],q[505],ans[505][505];
  void qsort(int l,int r)
  {
  	int i=l,j=r,mid=p[(l+r)/2+1];
  	while(i<=j)
  	{
  		while(p[i]<mid) i++;
  		while(p[j]>mid) j--;
  		if(i<=j)
  		{
  			swap(p[i],p[j]);
  			for(int k=1;k<=n;k++) swap(ans[i][k],ans[j][k]);
  			i++;
  			j--;
  		}
  	}
  	if(l<j) qsort(l,j);
  	if(i<r) qsort(i,r);
  }
  void qsort1(int l,int r)
  {
  	int i=l,j=r,mid=q[(l+r)/2+1];
  	while(i<=j)
  	{
  		while(q[i]<mid) i++;
  		while(q[j]>mid) j--;
  		if(i<=j)
  		{
  			swap(q[i],q[j]);
  			for(int k=1;k<=n;k++) swap(ans[k][i],ans[k][j]);
  			i++;
  			j--;
  		}
  	}
  	if(l<j) qsort1(l,j);
  	if(i<r) qsort1(i,r);
  }
  int main()
  {
  	scanf("%d",&n);
  	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
  	for(int i=1;i<=n;i++) scanf("%d",&q[i]);
  	for(int i=1;i<=n;i++)
  	{
  		for(int j=1;j<=n;j++)
  		{
  			ans[i][j]=(i+j>n);
  		}
  	}
  	qsort(1,n);
  	qsort1(1,n);
  	for(int i=1;i<=n;i++)
  	{
  		for(int j=1;j<=n;j++)
  		{
  			printf("%d",ans[i][j]);
  		}
  		printf("\n");
  	}
  }
  ```

---

