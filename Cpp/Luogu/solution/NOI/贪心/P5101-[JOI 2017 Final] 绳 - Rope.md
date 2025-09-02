# [JOI 2017 Final] 绳 / Rope

## 题目描述

**题目译自 [JOI 2017 Final](https://www.ioi-jp.org/joi/2016/2017-ho/) T5「[縄](https://www.ioi-jp.org/joi/2016/2017-ho/2017-ho.pdf) / [Rope](https://www.ioi-jp.org/joi/2016/2017-ho/2017-ho-en.pdf)」**

 JOI 小宝宝正拿着一根绳子玩。绳子可视为一条长度为 $N$ 的左右延伸的线段。绳子由 $N$ 根线连接而成，每根线的长度为 $1$，厚度为 $1$。绳子上的线共有 $M$ 种颜色，左数第 $i$ 根线 $(1\leqslant i\leqslant N)$ 的颜色为 $C_i(1\leqslant C_i\leqslant M)$。**绳子的左端点**意为左数第 $1$ 根线的左端点，**绳子的右端点**意为右数第 $1$ 根线的右端点。显然左数第 $i$ 根线 $(1\leqslant i\leqslant N)$ 的右端点 到 绳子的左端点 的距离为 $i$。

JOI 把绳子的长度缩短了。具体来说，JOI 反复地进行以下过程，直到绳长缩短至 $2$。

* 假设此时绳子的长度为 $L$。指定一个整数 $j(1\leqslant j<L)$，使绳子左数第 $j$ 根线成为绳子的左端点（最左的线），并折叠绳子。也就是说，
  - 如果 $j\leqslant \Large\frac{L}{2}$，则将左数第 $i$ 根线 $(1\leqslant i\leqslant j)$ 与左数第 $(2j-i+1)$ 根线拧成一股。此时，绳子原本的右端点仍是右端点，绳长变为 $L-j$。
  - 如果 $j> \Large\frac{L}{2}$，则将左数第 $i$ 根线 $(2j-L+1\leqslant i\leqslant j)$ 与左数第 $(2j-i+1)$ 根线拧成一股。此时，绳子原本的左端点变为右端点，绳长变为 $j$。
* 两条线的颜色相同才能拧成一股。在将两条线拧成一股前，可以任意改变线的颜色。将线染成其他颜色所需的费用 等于 线的厚度。颜色匹配后，两条线将被拧成一股，新的一股线的厚度 将为 两条线的厚度之和。

我们把绳长缩短至 $2$ 的绳子称为最终的绳子。JOI 希望使得将绳长缩短至 $2$ 所需的费用尽可能小。对于每种颜色，JOI 都想知道，在最终的绳子中包含这种颜色的情况下，将绳长缩短至 $2$ 所需的最小费用。

你的任务是帮 JOI 解决这个问题。

## 说明/提示

#### 样例解释 1
通过下述步骤，只需花费 $2$，就可以使得最终的绳子中包含颜色 $1$。
* 把左数第 $2$ 根线染成颜色 $1$。折叠绳子使得 原本到左端点的距离为 $1$ 的端点 变为 新的左端点。现在，从左往右数，线的颜色依次是 $1,$ $ 3,$ $ 3,$ $ 2$，厚度依次是 $2,$ $ 1,$ $ 1,$ $ 1$。
* 把左数第 $4$ 根线染成颜色 $1$。折叠绳子使得 原本到左端点的距离为 $2$ 的端点 变为 新的左端点。现在，从左往右数，线的颜色依次是 $3, 1$，厚度依次是 $2, 3$。

通过下述步骤，只需花费 $1$，就可以使得最终的绳子中包含颜色 $2$ 和 $3$。
* 折叠绳子使得 原本到左端点的距离为 $3$ 的端点 变为 新的左端点。现在，从左往右数，线的颜色依次是 $3,$ $ 2,$ $ 1$，厚度依次是 $2,$ $ 2,$ $ 1$。
* 把左数第 $3$ 根线染成颜色 $2$。折叠绳子使得 原本到左端点的距离为 $2$ 的端点 变为 新的左端点。现在，从左往右数，线的颜色依次是 $2, 3$，厚度依次是 $3, 2$。

#### 样例解释 2
通过下述步骤，只需花费 $2$，就可以使得最终的绳子中包含颜色 $1$。
* 折叠绳子使得 原本到左端点的距离为 $2$ 的端点 变为 新的左端点。
* 把左数第 $1$ 根线染成颜色 $1$。折叠绳子使得 原本到左端点的距离为 $1$ 的端点 变为 新的左端点。注意这次染色的费用为 $2$，因为此时左数第 $1$ 根线的厚度为 $2$。
* 折叠绳子使得 原本到左端点的距离为 $3$ 的端点 变为 新的左端点。
* 折叠绳子使得 原本到左端点的距离为 $1$ 的端点 变为 新的左端点。

#### 数据范围与提示
对于 $15\%$ 的数据，$N\leqslant 15, M\leqslant 10$。  
对于另外 $30\%$ 的数据，$N\leqslant 10^5, M\leqslant 10$。  
对于另外 $10\%$ 的数据，$N\leqslant 10^5, M\leqslant 500$。  
对于另外 $20\%$ 的数据，$N\leqslant 10^5, M\leqslant 5000$。  
对于所有数据，$2\leqslant N\leqslant 10^6, 1\leqslant M\leqslant N, 1\leqslant C_i\leqslant M(1\leqslant i\leqslant N)$，在初始状态的绳子上，颜色 $1, 2, \ldots, M$ 都至少出现了一次。

## 样例 #1

### 输入

```
5 3
1 2 3 3 2```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
7 3
1 2 2 1 3 3 3```

### 输出

```
2
2
2```

## 样例 #3

### 输入

```
10 3
2 2 1 1 3 3 2 1 1 2```

### 输出

```
3
3
4```

# 题解

## 作者：Log_x (赞：21)

## Solution

题目的限制有些复杂，先做一些简化。

首先染色一定不会折叠的过程中进行，因为厚度可以叠加的限制恰好保证了在折叠过程中染色不会比一开始染色更优，并且也没有必要把同一根线染色多次。

由此可知，染色之后的绳子至多只有两种颜色。

一个关键的结论：

>  染色之后绳长可以缩短至 $2$ 的充分必要条件是：除了首尾两段，其余的**同色连续段**的长度都为偶数。

证明：

> 1. 充分性：
>
>    即需要对于每种满足该条件的绳子构造出一种方案，使得绳长能够缩短至 $2$。
>
>    - 首先将最后一段的长度缩短至 $1$；
>
>    - 若倒数第二段不是第一段，取倒数第二段的中线，将绳子沿着这条中线翻折，翻折之后倒数第二段变为最后一段，重复上述过程；
>    - 若倒数第二段是第一段，将第一段的长度缩短至 $1$，总的绳长缩短至 $2$，折叠结束。
>
> 2. 必要性：
>
>    即需要证明不满足该条件的绳子都无法构造出方案，使得绳长能够缩短至 $2$。
>
>    - 取出既不是首段也不是尾段的某一个长度为奇数的段，考虑每一次折叠的影响；
>    - 因为与该段相邻的是两个异色的段，每次折叠所取的中线一定不能在该段内；
>    - 对于所取中线在该段外的折叠，折叠过后与该段相邻的仍是两个异色的段；
>    - 只要与该段相邻的是两个异色的段，绳长就永远无法被缩短至 $2$。

因为长度为偶数的连续段可以划分为若干个长度为 $2$ 的小段，我们只需要枚举第一个长度为 $2$ 的小段是在位置 $1$ 还是在位置 $2$，保证每一个长度为 $2$ 的小段内线的颜色都相同，最后在两种情况中取最优解。

考虑枚举其中一种颜色 $i$，计算包含颜色 $i$ 的答案。

讨论一个长度为 $2$ 的小段中的几种情况：

1. 如果小段内两根线同色且都为 $i$，显然不需要再更改；
2. 如果小段内其中一根线颜色为 $i$，将另一根线也改为 $i$ 显然不会更劣；
3. 如果小段内两根线的颜色都不为 $i$，则需要根据所取的另一种颜色来决定费用。

设 $cnt_i$ 表示初始时颜色 $i$ 的出现次数，$f_{i,j}$ 表示两根线的颜色恰好为 $i,j$ 的小段数，则我们所求即为 $\min \limits_{j \neq i}\{n - cnt_i - cnt_j + f_{i,j}\}$。

考虑枚举每个颜色为 $i$ 的线的出现位置，若与其同处一个小段的线的颜色为 $j(j \neq i)$，则令 $cnt_j$ 减一，需要动态维护 $\max\limits_{j \neq i}\{cnt_j\}$，可以用一个桶维护，支持 $\mathcal O(1)$ 修改和查询。

总的时间复杂度 $\mathcal O(n)$。

## Code

```cpp
#include <bits/stdc++.h>

const int S = 1 << 20;
char frd[S], *ihead = frd + S;
const char *itail = ihead;

inline char nxtChar()
{
	if (ihead == itail)
		fread(frd, 1, S, stdin), ihead = frd;
	return *ihead++;
}

template <class T>
inline void read(T &res)
{
	char ch; 
	while (ch = nxtChar(), !isdigit(ch));
	res = ch ^ 48;
	while (ch = nxtChar(), isdigit(ch))
		res = res * 10 + ch - 48;
} 

char fwt[S], *ohead = fwt;
const char *otail = ohead + S;

inline void outChar(char ch)
{
	if (ohead == otail)
		fwrite(fwt, 1, S, stdout), ohead = fwt;
	*ohead++ = ch;
}

template <class T>
inline void put(T x)
{
	if (x > 9)
		put(x / 10);
	outChar(x % 10 + 48);
}

using std::vector;
const int N = 1e6 + 5;
const int Maxn = 0x3f3f3f3f;

vector<int> v[N];
int n, m, mx;
int cnt[N], apr[N], ans[N], col[N], mth[N];

template <class T>
inline void CkMin(T &x, T y) {x > y ? x = y : 0;}
template <class T>
inline void CkMax(T &x, T y) {x < y ? x = y : 0;}

inline void del(int x)
{
	--apr[cnt[x]];
	!apr[cnt[x]] && cnt[x] == mx ? --mx : 0;
	++apr[--cnt[x]];
}

inline void add(int x)
{
	--apr[cnt[x]];
	cnt[x] == mx ? ++mx : 0;
	++apr[++cnt[x]];
}

inline void solve()
{
	for (int i = 1; i <= m; ++i)
	{
		int tmp = cnt[i];
		for (int j = 1; j <= tmp; ++j)
			del(i);
		for (int j = 0, jm = v[i].size(); j < jm; ++j)
		{
			int x = v[i][j];
			if (mth[x] && col[mth[x]] != i)
				del(col[mth[x]]);
		}
		CkMin(ans[i], n - tmp - mx);
		for (int j = 0, jm = v[i].size(); j < jm; ++j)
		{
			int x = v[i][j];
			if (mth[x] && col[mth[x]] != i)
				add(col[mth[x]]);
		}
		for (int j = 1; j <= tmp; ++j)
			add(i);
	}
}

int main()
{
	read(n); read(m);
	if (m == 1)
		return puts("0"), 0;

	for (int i = 1; i <= m; ++i)
		ans[i] = Maxn;
	for (int i = 1; i <= n; ++i)
	{
		read(col[i]);
		v[col[i]].push_back(i);
		++cnt[col[i]];
	}	
	for (int i = 1; i <= m; ++i)
		CkMax(mx, cnt[i]), ++apr[cnt[i]];
	for (int i = 1; i <= n; i += 2)
		if (i < n)
			mth[i] = i + 1, mth[i + 1] = i;
		else
			mth[i] = 0;
	solve();

	mth[1] = 0;
	for (int i = 2; i <= n; i += 2)
		if (i < n)
			mth[i] = i + 1, mth[i + 1] = i;
		else
			mth[i] = 0;
	solve();

	for (int i = 1; i <= m; ++i)
		put(ans[i]), outChar('\n');
	fwrite(fwt, 1, ohead - fwt, stdout);
	return 0;	
}

```

---

## 作者：unputdownable (赞：6)

谔谔，结论很好猜也很好证。

--------

由于染色需要厚度的代价，那么相当于对每根叠在这里的线都染了一次。

那么在把绳子先染色再对折必然不劣。

直接考虑这根绳子最后会变成什么样：

首先对折后总长度为 $2$，不妨假设他就在数轴的 $[0,2]$ 之间，其中 $[0,1]$ 和 $[1,2]$ 上的线段必然是同一种颜色。

然后你会发现，顺着这跟绳子走，（除了开头和结尾）必然是从 $1$ 走到 $0$ 或 $2$ 再走回来，而这两步走的绳子颜色必然相同，于是我们就有一个必要条件：除了开头或者结尾，**颜色连续段长度必然为偶数**。

充分性是好证明的，从最后一直往前折就行，一直把最后的颜色连续段长度折成 $1$，就能往前对折了。

----------

考虑直接对（原来绳子上的）线段配对，那么 $i$ 只能和 $i-1$ 和 $i+1$ 配对；枚举两种情况。

对于颜色 $c$，我们找出有颜色 $c$ 的每个位置，把和这条线段配对的线段染成 $c$ 必然不劣。

剩下的部分相当于求其他颜色数量的最大值，保存每种颜色数量的桶，就能做到 $\Theta(1)$ 修改查询最大值了。

复杂度 $\Theta(n+m)$。

--------

**Code:**

```cpp
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#include <bits/stdc++.h>
// #define int long long
#define i64 long long
#define pii pair <int, int> 
using namespace std;
inline int read(void) {
    int x=0,sgn=1; char ch=getchar();
    while(ch<48||57<ch) {if(ch==45)sgn=0;ch=getchar();}
    while(47<ch&&ch<58) {x=x*10+ch-48;   ch=getchar();}
    return sgn? x:-x;
}
void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,m;
int col[1000006],cnt[1000006],ccc[1000006],MXCNT,MXCOL,NXCNT;
vector <int> E[1000006];
inline int trans(int x,int st) {
    if(st==1) return x^1;
    else return ((x+1)^1)-1;
}
inline int work(int c,int st) {
    int k,res;
    for(int x : E[c]) {
        if(x==st) continue;
        k=trans(x,st);
        if(col[k]==c) continue;
        --ccc[cnt[col[k]]];
        --cnt[col[k]];
        ++ccc[cnt[col[k]]];
    }
    k=(c==MXCOL ? NXCNT : MXCNT);
    --ccc[cnt[c]];
    for(; k>=0; --k) if(ccc[k]) { res=n-cnt[c]-k; break; }
    ++ccc[cnt[c]];  // reverse
    for(int x : E[c]) {
        if(x==st) continue;
        k=trans(x,st);
        if(col[k]==c) continue;
        --ccc[cnt[col[k]]];
        ++cnt[col[k]];
        ++ccc[cnt[col[k]]];
    }
    return res;
}
signed main() {
    n=read(); m=read();
    for(int i=1; i<=n; ++i) {
        E[col[i]=read()].push_back(i);
        ++cnt[col[i]];
    }
    for(int i=1; i<=m; ++i) {
        ++ccc[cnt[i]];
        if(cnt[i]>=MXCNT) NXCNT=MXCNT,MXCNT=cnt[i],MXCOL=i;
        else if(cnt[i]>=NXCNT) NXCNT=cnt[i];
    }
    if(m==1) return puts("0"),0;
    for(int i=1; i<=m; ++i) write(min(work(i,1),work(i,n))),puts("");
    return 0;
}

```



---

## 作者：takanashi_mifuru (赞：1)

想不到长度为 2 的转化，吃了一个半小时分讨的狗屎，还没讨出来……

首先考虑这个东西反正每次染色也是看厚度，那我肯定是一开始染好。

然后你发现你可以一个一个叠把开头的连续段叠成长度为 $1$ 的连续段，然后这个段想要再优化就必须叠到右边的 $1$ 上，这就需要中间这段跳板长度为偶数，跳完了之后又变成子问题……直到最后只剩下两段，就不需要跳板了。

这也就告诉我们，把他看成连续段的形式，那么除掉开头结尾不准存在奇数长度。

这个时候这个问题看着就很好解决，你很想嗯分讨，然后就寄了。

考虑把偶数段剖成长度为 $2$ 的段，那么每一段里面的点颜色都相同，进一步可以把两边的无限制段也搞进来，容易发现也都满足条件。

然后就简单了，你发现我们的问题本质就是取颜色 $i$ 和 $j$ 然后来凑这个条件，考虑对于一个段，如果里面有两个颜色 $i$，那就不管，如果有两个颜色 $j$，那也不管，如果出现了有且仅有一个颜色 $i$ 与有且仅有一个颜色 $j$ 的段，必然要操作至少一次，如果这俩都没有就要操作两次，考虑枚举 $i$ 之后，先把有且仅有一个颜色 $i$ 的记录，这个时候顺便减掉段 $(i,j)$ 的贡献，然后对于一个 $j$，他的贡献就是他每出现一次就可以少操作一次（当然没有 $i$）出现，那么我们需要维护的是单点加减和全局max，考虑开个桶，再给桶开个桶维护就行了。

当然考虑到奇偶性问题，起始位置不同可以安排两个不同的分段方法，分别求出最值后拿答案就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int col[1000005];
int ans[1000005];
vector<int> need[1000005];
int cnt[1000005];
int T[1000005];
int Max;
void add(int x){//cnt[x]++;
    T[cnt[x]]--;
    T[++cnt[x]]++;
    Max=max(Max,cnt[x]);
    return;
}
void del(int x){
    if(Max==cnt[x]&&T[cnt[x]]==1)Max=cnt[x]-1;
    T[cnt[x]]--;
    T[--cnt[x]]++;
    return;
}
void solve(int st){
    for(int i=1;i<=n;i++){
        T[i]=0,cnt[i]=0;
        need[i].clear();
    }
    for(int i=1;i<=n;i++)add(col[i]);
    for(int i=st;i<=n;i+=2){
        int A=col[i],B=col[i+1];
        // add(A),add(B);
        if(A==B)continue;
        need[A].push_back(B);
        need[B].push_back(A);
    }
    for(int i=1;i<=m;i++){
        int tmp=cnt[i],all=0;
        for(int j=1;j<=tmp;j++)del(i);
        for(int j=0;j<need[i].size();j++){
            int neta=need[i][j];//
            del(neta);
        }
        int tmpans=n-tmp-Max;
        ans[i]=min(tmpans,ans[i]);
        for(int j=0;j<need[i].size();j++){
            int neta=need[i][j];
            add(neta);
        }
        for(int j=1;j<=tmp;j++)add(i);
    }
    return;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&col[i]);
    }
    for(int i=1;i<=m;i++)ans[i]=1e9;
    solve(1),solve(2);
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
```

---

## 作者：xukehg (赞：0)

很好的题目！

如果你尝试建一个博弈树之类的东西（类似[合并书本](https://www.luogu.com.cn/problem/P9483)），你会发现颜色不同所付出的代价恰好等于两个结点中叶子数较小的树的叶子数。这启示我们提前将子树的叶子染成需要的颜色，不仅没有更多的花费，而且能减少中途改颜色的消耗。于是我们有了第一个结论：

- **对于每种颜色，一定存在一种方案，满足对折过程中没有再次染色，且代价最小。**

考虑这种方案，注意到，如果开始有 $x$ 种颜色，最后也只会有 $x$ 种颜色，而我们最多只能剩下两种颜色，得出结论二：

- **对于上述的方案，开始对折前一定只剩最多两种颜色。**

于是乎我们得到了一个类似于只包含 $0$ 和 $1$ 的字符串，其中 $1$ 的位置肯定不会修改，一部分位置既可以填 $0$ 也可以填 $1$，求最少把几个 $0$ 修改成 $1$。

这个东西似乎不是很好做，我们尝试打一下表：注意都如果字符串含有 $101$ 或 $11101$ 之类的结构，一定无法复原，且只有头尾例外。将相邻的 $0$ 或 $1$ 合并成为一块后，我们推出奇数长度的连通块无法消去，仅在头尾例外，有了第三个结论：

- **除了头尾的极长连通块，所有极长连通块的长度为偶数，且颜色交替。**

~~我往二分和动态规划想了半天~~容易推出：

- **除了头尾的极长连通块，相同颜色的极长连通块的首位置奇偶性相同。**

~~做完了~~这个条件可以归纳[证明](https://www.luogu.com.cn/paste/hjiyfd2j)是充分必要的。考虑枚举每一种颜色，再枚举首位置的奇偶性，双指针找到每个极长连通块，如果不合法就向左右扩展，最后找到不在极长连通块中出现次数最多的颜色的出现次数即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

int n,m;
int a[N],siz[N],num[N],maxn;
vector<int> col[N];
void del(int x){
	if (siz[num[x]] == 1 && maxn == num[x]) maxn--;
	siz[num[x]]--;++siz[--num[x]];
}
void add(int x){siz[num[x]]--;num[x]++;siz[num[x]]++;}//只用来回溯，不更新maxn 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	if (m == 1) return cout << 0 << "\n",0;
	for (int i = 1;i <= n;i++) cin >> a[i],num[a[i]]++,col[a[i]].push_back(i);
	for (int i = 1;i <= m;i++) siz[num[i]]++,maxn = max(maxn,num[i]);
	for (int i = 1;i <= m;i++){
		int ans = 1e9 + 7,p = 0,q,ymax = maxn,sum = col[i].size();//p,q是连通块的头尾指针，ymax方便回溯
		siz[num[i]]--;while (!siz[maxn]) maxn--;int nw = maxn;
		//情况1：同颜色块的起始位置是奇数
		while (p < sum){
			q = p;
			while (q < sum && col[i][q] - col[i][p] == q - p) q++;
			if (!(col[i][p] & 1)) del(a[col[i][p] - 1]);//向左扩展 
			if (col[i][q - 1] != n && (col[i][q - 1] & 1)) del(a[col[i][q - 1] + 1]);//向右扩展 
			p = q;
		}ans = min(ans,n - num[i] - maxn);
		maxn = nw;p = 0;
		//回溯 
		while (p < sum){
			q = p;
			while (q < sum && col[i][q] - col[i][p] == q - p) q++;
			if (!(col[i][p] & 1)) add(a[col[i][p] - 1]);
			if (col[i][q - 1] != n && (col[i][q - 1] & 1)) add(a[col[i][q - 1] + 1]);
			p = q;
		}p = 0;
		while (p < sum){
			q = p;
			while (q < sum && col[i][q] - col[i][p] == q - p) q++;
			if (col[i][p] != 1 && (col[i][p] & 1)) del(a[col[i][p] - 1]);
			if (col[i][q - 1] != n && !(col[i][q - 1] & 1)) del(a[col[i][q - 1] + 1]);
			p = q;
		}ans = min(ans,n - num[i] - maxn);
		cout << ans << "\n";
		maxn = ymax;p = 0;++siz[num[i]];
		while (p < sum){
			q = p;
			while (q < sum && col[i][q] - col[i][p] == q - p) q++;
			if (col[i][p] != 1 && (col[i][p] & 1)) add(a[col[i][p] - 1]);
			if (col[i][q - 1] != n && !(col[i][q - 1] & 1)) add(a[col[i][q - 1] + 1]);
			p = q;
		}
	}
	return 0;
}
/*
2 (2) 1 1 (3) (3) 2 1 1 2    0
(2 1 1 1 1 2) 2 1 1 2     	 3
1 1 2 (2 1 1 2)           	 3
(1 1) 2 2 1               	 3
(1 2 2 1)                 	 3
1 2                       	 3
*/

---

## 作者：SudoXue (赞：0)

[更好的阅读体验](https://www.cnblogs.com/xueruhao/p/18978533)

题目关键在于证明：无论怎样折来折去，最后留下来的两根线只能按照 $(1,2),(3,4),\dots$ 或 $(2,3),(4,5),\dots$ 这两种配对方案出现。折叠相当于对区间做翻转并截去一段，端点的相对次序保持奇偶性不变，因此所有合法折叠序列的极限形态只能是上述两套邻接配对。我们分别在这两种配对上独立求解，再取较小者即为答案。

把每一对并成一段，整根绳子最终被分成 $\lfloor N/2\rfloor$ 段，记颜色出现次数为 $f_c$。设目标颜色为 $c$，最终必须保证左右两束中至少有一束被染成颜色 $c$。如果先把整根绳子都刷成 $c$，费用是 $N-f_c$；随后若选择另一束颜色为 $y\ne c$，可以在不含 $c$ 的段内挽回部分费用：若一段两端都是 $y$ 可节省 $2$，若为 $(y,z)$ 则节省 $1$。设 $p_{c,y}$ 为在当前配对中出现 $(c,y)$ 或 $(y,c)$ 的段数，那么省下的总费用是 $f_y-p_{c,y}$。于是最小代价公式为

$$
\operatorname{Ans}(c)=N-f_c-\max_{y\ne c}(f_y-p_{c,y})
$$

实现时先扫描统计 $f_c$，再按配对遍历所有段，用哈希表累计不同色段次数并记录每种颜色的度数。接着重建稀疏图：同色段无边，异色段 $(a,b)$ 的权即为出现次数。把颜色编号按 $f_c$ 降序排成数组，再对每个 $c$ 遍历邻接表更新候选值，同时顺序扫降序数组找到第一个既非 $c$ 又与 $c$ 无边的颜色获得 $f_y$。

时间复杂度 $O(N+M\log M)$。

[link](https://www.luogu.com.cn/record/223626825)

---

