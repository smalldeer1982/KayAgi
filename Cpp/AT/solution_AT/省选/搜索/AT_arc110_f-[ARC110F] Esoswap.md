# [ARC110F] Esoswap

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc110/tasks/arc110_f

$ 0,\ 1,\ \ldots,\ N\ -\ 1 $ を並び替えた数列 $ P\ =\ P_0,\ P_1,\ \ldots,\ P_{N\ -\ 1} $ があります。

あなたは $ P $ に対して、以下の操作を最大 $ 2\ \times\ 10^5 $ 回まで行うことができます。

- 整数 $ i\ ~\ (0\ \leq\ i\ \leq\ N\ -\ 1) $ を宣言する。$ P_i $ と $ P_{(i\ +\ P_i)\ \textrm{\ mod\ }\ N} $ を入れ替える

適切に操作を行うことで、$ P $ を昇順に並び替えてください。もしそれが不可能な場合、`-1` を出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \leq\ N\ \leq\ 100 $
- $ P $ は $ 0,\ 1,\ \ldots,\ N\ -\ 1 $ を並び替えた数列

### Sample Explanation 1

この操作列は、以下のように $ P $ を昇順に並び替えます。 - まず $ i $ として $ 6 $ を宣言し、$ P_6\ (=\ 5) $ と $ P_{(6\ +\ 5)\ \textrm{\ mod\ }\ 8}\ =\ P_3\ (=\ 6) $ を入れ替える。$ P $ は $ 7,\ 1,\ 2,\ 5,\ 4,\ 0,\ 6,\ 3 $ になる - 次に $ i $ として $ 0 $ を宣言し、$ P_0\ (=\ 7) $ と $ P_{(0\ +\ 7)\ \textrm{\ mod\ }\ 8}\ =\ P_7\ (=\ 3) $ を入れ替える。$ P $ は $ 3,\ 1,\ 2,\ 5,\ 4,\ 0,\ 6,\ 7 $ になる - 次に $ i $ として $ 3 $ を宣言し、$ P_3\ (=\ 5) $ と $ P_{(3\ +\ 5)\ \textrm{\ mod\ }\ 8}\ =\ P_0\ (=\ 3) $ を入れ替える。$ P $ は $ 5,\ 1,\ 2,\ 3,\ 4,\ 0,\ 6,\ 7 $ になる - 次に $ i $ として $ 0 $ を宣言し、$ P_0\ (=\ 5) $ と $ P_{(0\ +\ 5)\ \textrm{\ mod\ }\ 8}\ =\ P_5\ (=\ 0) $ を入れ替える。$ P $ は $ 0,\ 1,\ 2,\ 3,\ 4,\ 5,\ 6,\ 7 $ になる

## 样例 #1

### 输入

```
8
7 1 2 6 4 0 5 3```

### 输出

```
4
6
0
3
0```

# 题解

## 作者：星星与辰 (赞：25)

## 题意
给出一个整数 $N(2\leq N\leq 100)$ 和一个从 $0$ 开始的长度为 $N$ 的排列 $P=P_0,P_1,P_2\cdots P_{N-1}$，你可以进行以下操作：

- 选择一个整数 $i(0\leq i \leq N-1)$。
- 交换当前数列上的 $P_{(p_0+P_{p_0})\bmod N}$ 两个位置上的数字。

求能否在 $2\times 10^5$ 之内构造出一种操作方案使得整个序列单调上升，如果有，则在第一行输出操作个数 $K$，接下来 $K$ 行，每行按顺序输出数列操作的位置 $i$，若没有，则输出 $-1$。

## 思路
观察一下有什么性质，我们容易得出以下基础结论：

- **性质 1：每一个数字在序列中出现且仅出现一次。**
> 因为这是一个排列。
- **性质 2：对于不同的数字在同一个位置上时，它们对应交换的位置（即对应的 $P_{(p_0+P_{p_0})\bmod N}$ 均不相同。**
> 因为其 $P_i$ 不同。

在这个的性质的基础下，我们继续思考（或者尝试手玩样例），就得到了一个神奇的基础推论：

- **推论 1：在无论当前数列长什么样的情况下，如果对一个位置 $p_0$ 不断进行操作（即不断交换 $P_{p_0}$ 与 $P_{(p_0+P_{p_0})\bmod N}$ 两个位置上的数字）至多 $N-1$ 次，那么我们最终一定会使位置 $p_0$ 上的数字为 $0$。**

这个结论要稍微想一会，我们会在尝试证明它时得到一个新的重要性质:

- **性质 3：在只对一个位置 $p_0$ 操作时，若该位置上数字为 $A$，则对其进行一次操作后，$A$ 将不再出现在位置 $p_0$ 上**
> 因为我们当前只操作一个位置 $p_0$，所以只有当位置 $p_0$ 的数主动与现在的 $A$ 所在位置交换，才可能使得位置 $p_0$ 的数为 $A$，但能使其做这样交换的数字只有 $A$，而 $A$ 又只有当位置 $p_0$ 的数字为 $A$ 时交换才可能得到，从而可知 $A$ 不会再次出现在位置 $p$。

![](https://cdn.luogu.com.cn/upload/image_hosting/6tpioaxu.png)


 _图示,数字表示第几次操作，连线两端为交换的两个数的位置。_ 

这时，我们再回头来证明推论 1：
> 如果当前位置 $p_0$ 的数字是 $0$，那么我们就已经得到了 $0$，就算对其操作，也一定不会改变其位置。

> 如果当前不是 $0$，设其为 $A$，那么我们对其进行操作，一定会使位置 $p_0$ 上为另一个数，根据性质3，位置 $p_0$ 上不会再出现 $A$，因此，若不断对其进行操作，则位置 $p_0$ 上会不断出现新数，直到位置 $p_0$ 上的数字为 $0$ 停下，此时，我们进行了至多 $N-1$ （最多多少不同数的数量）次操作。

那么我们能不能尝试按照某种顺序（比如从后往前或从前往后）一一确定这些数字？是可以的，利用我们已经得知的性质3，我们将其扩展发现了另一个性质4：
- **性质 4：在当前 $p_0$ 为 $0$ 时，我们称其前一个位置为 $p_1$，我们再不断对其进行更改则同样，经过至多 $N-2$ 次操作，我们 $p_1$ 上会出现 $1$，并在出现 $1$ 后的 $1$ 次操作后，会使该$p_1$上出现 $0$，并且此时，$p_0$ 上为 $1$。**
> 与性质3的证明同理，因为当前只对 $p_1$ 进行操作，根据性质3我们可知，当 $p_1$ 上不是 $0$ 时，我们会不断得到一个新数，但因为 $0$ 在位置 $p_0$ 上，也就是说，只有当 $p_1$ 上为 $1$ 时，才可能在这个位置上出现 $0$，再次之前一定会不断变换数字，直到 $p_1$ 上为 $1$，然后再次一次操作则会与 $0$ 交换，此时 $p_1$ 与 $p_0$ 两个位置上局部、连续有序。

![](https://cdn.luogu.com.cn/upload/image_hosting/u52qjhsg.png)


_图示，蓝色为出现 $1$ 前的操作，红色为出现 $1$ 后的操作。_

既然发现了以上的性质，我们思考是否能将其归纳为一个更通用的、更广泛的推论？我们再仔细思考一下，感性地猜测一下，如果有下一步的话，是不是应该继续在 $p_1$ 前一个位置操作，的确是的，于是有了这个推论:
- **推论2：对于一个连续的长度为 $k$ 位的，整体有序的包含数字 $0\leq i \lt k$ 的区间 $S$，我们此时对该区间前一个位置 $p_k$ 不断进行操作至多 $N-1$ 次操作后，我们会得到一个连续的长度为 $k+1$ 的，整体有序的，包含数字 $0\leq i \leq k$ 的从 $p_k$ 开始、$p_k+k$ 结束的区间 $S'$。**
> 该证明与上面的同理，因为当前只对 $p_k$ 进行操作，那么在 $0$ 到 $k$ 内的数出现在这个位置上之前，后面 $S$ 区间内的数均不会出现在这个位置上，而其中 $0\leq i\leq k-1$ 的数都在区间 $S$ 内，所以，只有该位置上为 $k$ 之后，才可能出现区间 $S$ 内的数，而在出现 $k$ 时，此时至多经过 $N-k-1$ 次操作，再次操作它，该位置上则会为 $k-1$（与区间 $S$ 内最后一个数字交换），再次操作，则该位置上则会为 $k-2$（与元区间 $S$ 内倒数第二个数字交换），即在出现 $k$ 后的第 $i$ 次操作，该位置上的数字为 $k-i$，并在下一次操作时与位置为 $p_k+k-i$ 的数字交换，直到 $p_k$ 上的数为 $0$，此时，再操作，序列不变，这样的操作本质上是区间 $S$ 内的数被取出然后重新倒着从大到小重新插入回区间 $S$，并且发现此时会生成我们想要的区间 $S'$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ghhqcxpc.png)


_蓝色序列为 $k$ 出现前的操作最终序列，红色序列出现后的第 $i$ 次操作过程。_

于是我们发现利用推论 2，就可以做完这道题了，我们只需要在最后一个位置不断操作，使其出现 $0$，使序列上出现一个合法的长度为 $1$ 的区间，然后继续在该区间前继续操作，得到一个新的合法区间，直至这样的合法区间覆盖整个序列就可以了，这样的操作数是 $N\times N \lt 2\times 10^5$ 的。

然后就是本题最出人意料的部分了，直接上代码。
## Code
```cpp
#include <cstdio>
int main() {
	int n;
	scanf("%d", &n);
	printf("%d\n", n * n);
	for (int i = n - 1; ~i; --i) {
		for (int j = 0; j < n; ++j) {
			printf("%d\n", i);
		}
		//刚刚说过如果该位置为0时继续操作不变，而我们每一次操作之后一定会使得该位置为0，懒得特判节约操作了，反正都能过。
	}
}
```
## 总结
本体代码挺简单的~~不知道是谁在AT上卡最短解~~，不过其背后的原理值得引人思考。~~做题时不要只顾着口胡~~，严格证明更能帮助我们思维的提升。

---

## 作者：kkio (赞：12)

upd：打太快一堆错别字，被讽了...

看楼上同机房大佬扯了一堆结论还有图，实在是看不懂，不如来看小清新理解。

首先你用脑子想一下，你就会知道，如果一直盯着一个位置换，那他最后会换成 $ 0 $ 。因为位置固定，你要交换另一个位置所需要的值也是固定的，而他被换走了，就再也换不到了。

然后你在 $ 0 $ 的前面一直操作，他最后也会变成 $ 0 $ ，而且他一定会在变成 $ 1 $ 后变成 $ 0 $ ，因为要和后一位交换。

于是你从前往后一直这样操作，最后就可以将 $ 0 $ 和 $ 1 $ 换到最前面，而且在换第 $ 0 $ 位的时候，如果你的值是 $ x $ ，那他一定会被换到第 $ x $ 位。所以后面也是有序的。

然后你就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n;
int main()
{
	scanf("%d",&n);
	printf("%d\n",n*n);
	for(int i=n-1;i>=0;i--)
		for(int j=n-1;j>=0;j--)
			printf("%d\n",i);
}
```


---

## 作者：wangzhechun (赞：3)

### (づ｡◕‿‿◕｡)づ[ARC110F] Esoswap 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc110_f)

[博客查看更佳](https://www.luogu.com.cn/article/xs31j07w)

首先因为 $2 \le N \le 100$，我们发现不会出现 `-1` 的情况，所以我们 DFS ~~纯爆捜~~就能过，注意以下几点：

* 每搜一次 `for` 一遍，检查是否完成交换。
* 当当前搜到的位置 $i$ 已经换好或 $a_i=0$ 就跳过，其余的能换就换。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100], b[20001];
void find(int num) {
    for (int i = 0; i < n; i++) {
        if (a[i] != i)
            break;

        if (i == n - 1 && a[i] == i) {
            cout << num << "\n";

            for (int j = 1; j <= num; j++)
                cout << b[j] << "\n";

            exit(0);
        }
    }

    if (num >= min(n * n, 20000))
        return;

    for (int i = 0; i < n; i++) {
        if (a[i] != 0 && a[i] != i) {
            int x = i, y = (i + a[i]) % n;
            swap(a[x], a[y]);
            b[num + 1] = x;
            find(num + 1);
            swap(a[x], a[y]);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    find(0);
    return 0;
}   //Code by wangzhechun
```
然后我们就可以完美的AC这道题啦~(≧▽≦)/~。

---

## 作者：Kreado (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc110_f)。

## 思路

**引理**：对一个位置 $x$，进行不超过 $n$ 次交换操作一定会使得该位置上的数变为 $0$ 。

Proof：

假设位置 $x$ 上的数不为 $0$，若最后操作该位置上的数不为 $0$，那么中途一定存在一个循环。

对位置 $x$ 进行一次交换操作交换的是值 $p_x$ 和 $p_{(p_x+x)\bmod n}$，想要把 $p_x$ 在换到位置 $x$ 上来必须用 $p_x$，可是 $p_x$ 已经被换走了，所以不存在这样的循环，由于交换过程中最多只会有 $n$ 种不同的数，因此 $n$ 次操作后该位置上的数一定会化为 $0$。

**正题**：

考虑先对位置 $n-1$ 进行 $n$ 次操作，那么有 $p_{n-1}=0$。

现在在对位置 $n-2$ 进行 $n$ 次操作，那么有 $p_{n-2}=0$，那么这个 $0$ 是从哪来的呢？很显然，只有当位置 $p_{n-2}=1$ 时才能和 $p_{n-1}$ 交换，所以现在有 $p_{n-2}=0,p_{n-1}=1$。

再考虑对位置 $n-3$ 进行 $n$ 次操作，那么有 $p_{n-3}=0$，那么这个 $0$ 又是从哪来的呢？当且仅当 $p_{n-3}=1$ 时才有，那么这个 $1$ 又是从哪来的呢？当且仅当 $p_{n-3}=2$ 才有。最后操作得到 $p_{n-3}=0,p_{n-2}=1,p_{n-1}=2$。

归纳得到，我们倒序从位置 $n-1$ 依次操作 $n$ 次，最终操作到位置 $1$ 时序列一定是 $0,1,2,\cdots,n-2,n-1$，也就是有序的。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n;

int main(){
	scanf("%d",&n);
	printf("%d\n",n*n);
	for(int i=n-1;~i;i--) for(int j=1;j<=n;j++) printf("%d\n",i);
	return 0;
}



```


---

## 作者：Nights_watcher (赞：2)

众所周知， AC 这道题，他可以用这种方法：
```cpp
printf ("%d\n" , n * n);
for (int i = n - 1;i >= 0;i --) for (int j = 1;j <= n;j ++) printf ("%d " , i);
```
但是，我决定提供一种不同的方法。根据上面的代码 ↑ ，我们知道，操作数量最多为 $n ^ 2$ 次。那么我们就可以打一个暴力 dfs 。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , a[1505] , cz[10004] , cnt;
void dfs (int step)
{
    bool flag = true;
    for (int i = 1;i <= n;i ++)
        if (a[i] != i - 1)
        {
            flag = false;
            break;
        }
    if (flag)
    {
        cout << step << endl;
        for (int i = 0;i < step;i ++) cout << cz[i] << " ";
        exit (0);
    }
    if (step >= n * n) return;
    for (int i = 1;i <= n;i ++)
    {
        cz[step] = i - 1;
        int x = (i + a[i] - 1) % n + 1;
        swap (a[i] , a[x]);
        dfs (step + 1);
        swap (a[i] , a[x]);
    }
}
signed main ()
{
    ios :: sync_with_stdio (false);
    cin.tie (0);
    cout.tie (0);
    cin >> n;
    for (int i = 1;i <= n;i ++) cin >> a[i];
    dfs (0);
    return 0;
}
```
不出意外，它果然 T 了。既然如此，我们可以考虑一下剪枝优化。
### 优化1
如果 $a_i = 0$ ，那么 $a_i$ 它一定不会被选否则就是自己跟自己换。
### 优化2
如果 $a_i$ 这个位置已经对位了，那如果换它一定不是最优的。\
那么 AC 代码就新鲜出炉了。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , a[1505] , cz[10004] , cnt;
void dfs (int step)
{
    bool flag = true;
    for (int i = 1;i <= n;i ++)
        if (a[i] != i - 1)
        {
            flag = false;
            break;
        }
    if (flag)
    {
        cout << step << endl;
        for (int i = 0;i < step;i ++) cout << cz[i] << " ";
        exit (0);
    }
    if (step >= min (n * n , 10000)) return;
    for (int i = 1;i <= n;i ++)
        if (a[i] != 0 && a[i] != i - 1)
        {
            cz[step] = i - 1;
            int x = (i + a[i] - 1) % n + 1;
            swap (a[i] , a[x]);
            dfs (step + 1);
            swap (a[i] , a[x]);
        }
}
signed main ()
{
    ios :: sync_with_stdio (false);
    cin.tie (0);
    cout.tie (0);
    cin >> n;
    for (int i = 1;i <= n;i ++) cin >> a[i];
    dfs (0);
    return 0;
}
```
1ms 通过

---

## 作者：yanqijin (赞：2)

# 题意
有一个从 $0$ 开始的长度为 $N$ 的排列 $a$，每一次操作可以将第 $i$ 个数与第 $(i+a_i)\bmod N$ 个数交换位置，问如何操作才能将 $A$ 变为单调递增的。
# 思路
~~我绝对不会告诉你我在比赛时先全输出 $-1$ 结果爆零了~~。

如果你在比赛中试一下全输出 $-1$ 就会发现 **没有一个点输出负一**，这说明 **我们一定可以构造出一个满足的序列**，现在考虑如何构造。

### 定理
**对于一个数重复操作 $n$ 次以后这个数一定为 $0$**。

考虑证明。因为每次都会换过来一个新的数，所以一定不会换到以前换过的，而再换到 $0$ 之后操作不再有效，所以最多 $n$ 次后这个数一定为 $0$。

所以，只需从 $n-1$ 到 $0$ 来枚举，每次重复输出 $n$ 次即可。

# Code
```cpp
#include<cstdio>
using namespace std;
int n;
void read(int &x) {
	x=0;
	char ch=getchar();
	while(ch<'0' or ch>'9') {
		ch=getchar();
	}
	while(ch>='0' and ch<='9') {
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
}
void write(int x) {
	int sta[10],top=0;
	do {
		sta[top++]=x%10;
		x/=10;
	} while(x);
	while(top--) putchar(sta[top]+48);
	putchar('\n');
}
int main() {
	read(n);
	write(n*n);
	for(int i=n-1; i>=0; i--) {
		for(int j=n-1; j>=0; j--) write(i);
	}
	return 0;
}
```

---

## 作者：Inui_Sana (赞：1)

为啥这种题大半的题解会都是一样的？来个不同做法的。

首先可以发现，对于一个固定位置操作若干次大概是能使这个位置变成任意一个数的。于是有个猜测的做法：倒序枚举 $i$ 不断对 $0$ 操作直到 $P_0=i$，然后再操作一次使 $P_i=i$。

试了一下发现不太行。因为如果此时 $a_0=0$ 就怎么也动不了了。然后发现 $0$ 其实非常不好，但是发现，可以通过操作若干次数字 $n-1$ 的方式使 $P$ 循环位移，于是先不断操作 $n-1$ 使 $0$ 固定到 $P_{n-1}$ 的位置。

这一步似乎也可以通过不断操作位置 $n-1$ 做到。

然后考虑依次使 $n-2,n-3,\cdots,2,1$ 到 $0$ 再到对应位置。此时又发现一个问题：当 $P_0=n-1$ 的时候又会出问题。

但是发现这个时候好操作很多：只需要不断操作数字 $n-1$，使它去到还没归位的数的末尾。然后变成不断操作 $1$ 即可。再发生一次就变成不断操作 $2$，以此类推。

最后再不断操作数字 $n-1$，整个 $P$ 满足要求即可。

code：

```cpp
int n,m,a[N],p[N];
vector<int> ans;
il void work(int x){
	ans.eb(x);
	int y=(x+a[x])%n;
	swap(p[a[x]],p[a[y]]);
	swap(a[x],a[y]);
}
void Yorushika(){
	read(n);
	rep(i,0,n-1){
		read(a[i]);
		p[a[i]]=i;
	}
	while(a[n-1]){
		work(p[n-1]);
	}
	int x=0;
	drep(i,n-2,1){
		while(a[x]!=i&&a[(x+i)%n]!=i){
			if(a[x]==n-1){
				drep(j,n-2,i){
					work(p[n-1]);
				}
				x=(x+1)%n;
			}else{
				work(x);
			}
		}
		if(a[x]==i){
			work(x);
		}
	}
	while(a[0]||a[n-1]!=n-1){
		work(p[n-1]);
	}
	printf("%d\n",ans.size());
	for(int i:ans){
		printf("%d\n",i);
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：TLEWA (赞：1)

魔怔抽象结论题。

先讲正解。发现操作次数上限大概在 $n^2$ 级别，考虑 $O(n)$ 次操作确定一个数字的位置。我们发现确定了操作的位置后，根据这个下标上当前的数值，交换的目标下标一定是确定且不重复的。也就是说，每次操作该下标和一个不同下标进行交换操作，一定不会操作到在这个下标中进行过操作的数值。

那这个性质有什么用呢？我们考虑题面给出的最特殊的一个数 $0$，显然当 $P_i = 0$ 时，对于任意 $i < N$，都有 $(i+P_i) \bmod N=i$，也就是说下标为 $0$ 的点的交换对象总是自己。结合上面的结论，我们在任意下标进行至多 $n-1$ 次操作总能将该下标上的值变为 $0$。

但是光把 $0$ 移过来好像也没什么用？题目要求我们构造升序序列，注意到我们可以用 $n-1$ 次操作钦定 $0$ 的下标，再用 $n-1$ 次操作把 $0$ 换到任意下标，把 $0$ 换过来的最终一步所用的数一定是确定的，达到钦定任意数到任意下标的目的。

可惜的是，直接这样操作可能会打乱其它已经钦定好的数的顺序，考虑构造特殊的操作顺序使操作之间不互相影响。

我们不妨钦定 $1$ 作为交换出 $0$ 的数字，这样交换出 $1$ 的数值一定更大，契合使序列有序的目的。注意到我们可以很容易地构造出 $...01$ 的特殊序列，这样我们在 $n-2$ 的下标下交换出 $1$ 只能使用 $2$，$n-1$ 次操作后，序列变为 $...012$，对于更大的情况类似，考虑按照下标从高到低分别进行 $n-1$ 次操作，这样我们就可以在 $n(n-1)$ 操作内构造出有序的序列了。

[AC 代码](https://atcoder.jp/contests/arc110/submissions/57015291)

想要学习这道题正确做法的现在就可以退出了。接下来讲一个歪打正着的乱搞做法：

注意到操作次数的限制十分宽松，考虑 dfs 寻找操作序列。每次从头开始遍历寻找有效操作，寻找到正确操作后直接输出即可。

看起来似乎十分不可思议，但是这个做法可以过题。[放个我朋友的 dfs 做法代码](https://www.luogu.com/paste/6c92qbws)

简单理解一下，这种 dfs 的暴力过程找到的前几个操作序列其实和正解的操作是本质接近的，期望在很短的时间内就能找到正确答案，不过似乎也可以卡。

---

## 作者：SegTree (赞：0)

首先，可以将序列倒序排序。具体来说，如果 $p_x\ne n-1-x$ 就一直操作直到合法，则前面的操作一定不会影响后面的，所以倒着操作一定不会出现矛盾。

然后每次我们尝试将一个长度为 $x$ 的后缀从 $[x+1,0,\cdots,x]$ 操作成 $[0,1,\cdots,x,x+1]$。

具体来说：

操作 $x+1$，得到 $[x,0,1,\cdots,x-1,x+1]$；

操作 $x$，得到 $[x-1,0,1,\cdots,x-2,x,x+1]$；

以此类推，经过操作就可以操作成 $[0,\cdots,x+1]$。

每次将一个后缀进行排序即可。

```cpp
down(i,n-1,0)while(p[i]!=n-1-i)OP(i);
down(i,n-2,0)while(p[i])OP(i);
```

---

## 作者：_luanyi_ (赞：0)

统一 VP ARC 时遇到了这道题，发现我的乱搞做法竟然过了，且题解是清一色，因此我来分享一下我的做法。

注意到，如果 $a_0\neq 0$，设 $a_0=x$，则对 $0$ 进行一次操作，可以使 $a_x=x$。

因此这启示我们：如果 $a_0\neq 0$，就一直对 $0$ 操作，直到 $a_0=0$，说不定就自己排好了呢！

在这之后，如果还没排好，有两种情况。

第一种，存在一个 $i$ 满足 $(i+a_i)\bmod n=0$，也就是对 $i$ 操作之后 $a_i$ 这个数会跑到位置 $0$ 上去。那么就可以沿用之前的做法了！

第二种，不存在这样的 $i$，比如 $0,1,2,4,3$。这意味着，无论怎么操作，一定会让至少一个已经归位的数字被打乱，怎么办？

我的方法是找到一个最大的数 $a_j$ 满足 $j\neq a_j$ 也就是数字 $a_j$ 还没有归位。然后对 $j$ 进行一次操作，以尝试打破这种僵局。

然后就不可思议地通过了！

正确性我不会证明，如果有人会证明或者有 hack 可以联系我。

```cpp
#define fnq(i,a,b) for (int i = (a); i < (b); i++)
const int maxn = 110;
int a[maxn], ys[maxn], n;
vector <int> ansl;
void work (int x) {
	int y = (x + a[x]) % n;
	swap (ys[a[x]], ys[a[y]]);
	swap (a[x], a[y]);
	ansl.pb (x);
}
signed main () {
	cin >> n;
	fnq (i, 0, n) cin >> a[i];
	fnq (i, 0, n) ys[a[i]] = i;
	
	int cnt =0;
	while (1) {
		while (a[0]) work (0);
		bool flg = 1;
		fnq (i, 0, n) if (a[i] != i) {flg = 0; break;}
		if (flg) break;
		int id = -1;
		fnq (i, 1, n) if (a[i] != i && (a[i] + i) % n == 0) {id = i; break;}
		if (id != -1) {work (id); continue;}
		int j = n-1; while (ys[j] == j) --j;
		work (ys[j]); continue;
	}
	
	cout << ansl.size () << endl;
	for (auto i : ansl) cout << i << endl;
	return 0;
}
```

注意到操作次数上限很高，因此不会爆。

---

## 作者：zyh_helen (赞：0)

模拟赛上怵悌人把这题加强啦，顺便引导我想出来个吊打 std 的做法。

---
---

前面跟正解差不多，考虑含有 0 的置换环可以直接操作。

---

考虑那些没有 0 的置换环，我们直接把它和别的任何一个置换环合并，那么环数减一次操作后，就只剩一个置换环了，而那个置换环必定含有 0，直接操作即可。

合并就是找到置换环上的某个点，它操作后的位置不在它所在的置换环上，那么我们操作一次它就相当于合并了两个置换环。

---

注意特判 0 在开头的情况。

在 $n=1500$ 的情况下甚至只需要 2200 次操作！！

---
---

```cpp
#include<bits/stdc++.h>
//#include<Windows.h>
//#define int long long
//#define ll long long
//#define double long double
#define fi first
#define se second
//#define ls t[p].l
//#define rs t[p].r
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 2e3 + 10, inf = 1e9, M = 2e5;
//const double eps = 1e-16;
const int mod = 1e9 + 7;
//const int mod;
//const int AQX = 9;
mt19937 rnd(time(0) ^ clock());
int random(int l, int r){
	return rnd() % (r - l + 1) + l;
}
const int offset = 101, offset2 = 103;
/*
		    	           _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/
//struct Graph{
//	int head[N], tot;
//	struct edge{
//		int t, f;
//		int d, fa;
//		int next;
//	}e[N << 1];
//	void edge_add(int u, int v, int w = 0){
//		e[++tot].next = head[u];
//		e[tot].t = v;
//		e[tot].d = w;
//		e[tot].f = u;
//		head[u] = tot;
//	}
//	void clear(int n){
//		for(int i = 1;i <= tot;i++)e[i].t = e[i].f = e[i].d = e[i].next = 0;
//		for(int i = 1;i <= n;i++)head[i] = 0;
//		tot = 0;
//	}
//}g1, g2;
//int qmr(int x, int a){
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}

int n, a[N], v[N], cnt;
vector<int>ans;
signed main(){
	cin >> n;
	for(int i = 0;i < n;i++)scanf("%d", a + i);
	if(a[0] == 0){
		int x;
		for(int i = 0;i < n;i++)if(a[i] == 1)x = i;
		for(int i = x;i < n;i++)ans.push_back(i), swap(a[i], a[(i + 1) % n]);
	}
	vector<int>p;
	while(1){
		memset(v, 0, sizeof(v));
//        for(int i = 0;i < n;i++)cout << a[i] << " ";
//        cout << endl;
        int f = 0;
		for(int i = 0;i < n;i++){
			if(v[i])continue;
			int x = i;
			cnt++;
			p.clear();
			while(!v[x]){
				v[x] = cnt;
				p.push_back(x);
				x = a[x];
			}
			if(!i)continue;
			for(int x : p)if(v[(x + a[x]) % n] != cnt){
				ans.push_back(x), swap(a[x], a[(x + a[x]) % n]);
				f = 1;
				break;
			}
			if(f)break;
		}
        if(!f)break;
	}
	while(a[0])ans.push_back(0), swap(a[0], a[a[0]]);
	cout << ans.size() << endl;
	for(int i : ans)printf("%lld ", i);
	return 0;
}
/*


2 3
3 1
2 2
1 1
3 3
3 2
1 2
1 3
2 1
*/

---

