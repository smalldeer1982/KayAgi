# [ARC121C] Odd Even Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc121/tasks/arc121_c

$ (1,2,\ \ldots,\ N) $ を並び替えた数列 $ p $ が与えられます。 はじめ、$ p $ の第 $ n $ 項は $ p_{n} $ です。

あなたの目的は $ N^2 $ 回以下 *操作* を行い $ p $ を昇順に並び替えることです。 あなたは操作により以下のように $ p $ を変更することができます。

- **奇数** 回目の操作では $ 1 $ 以上 $ N-1 $ 以下の **奇数** $ n $ を選んで $ p_n $ と $ p_{n+1} $ を入れ替えます。
- **偶数** 回目の操作では $ 2 $ 以上 $ N-1 $ 以下の **偶数** $ n $ を選んで $ p_n $ と $ p_{n+1} $ を入れ替えます。

この問題の制約下で必ず目的を達成できることが証明できます。 そのような操作列を $ 1 $ つ求めてください。

$ T $ 個のテストケースが与えられるのでそれぞれについて答えを求めてください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ T\ \leq\ 250 $
- $ 2\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ p_i\ \leq\ N $
- $ p $ は $ (1,2,\ldots,N) $ を並び替えて得られる。
- $ 1 $ つの入力ファイルにおいて $ N $ の総和は $ 500 $ を超えない。

### Sample Explanation 1

\- $ 1 $ つ目のテストケースについて説明します。 - $ 1 $ 回目の操作で $ 1 $ を選ぶと $ p $ は $ (1,2,3,5,4) $ となります。 - $ 2 $ 回目の操作で $ 4 $ を選ぶと $ p $ は $ (1,2,3,4,5) $ となります。 - $ (1,4) $ は操作列として正しいですが、$ (4,1) $ は操作列として正しくないことに注意してください。 - 操作を $ 1 $ 度も行わなくともよいこと、操作回数を最小にする必要はないことに注意してください。

## 样例 #1

### 输入

```
2
5
2 1 3 5 4
2
1 2```

### 输出

```
2
1 4
0```

# 题解

## 作者：lmy_2011 (赞：2)

因为我们完全可以进行最多 $n^2$ 次操作，方法明显可以模拟。

题目中的交换位置我们可以理解交换 $(p_i,p_{i+1})$，至于偶数和奇数，根本不需多管，那我们可以使用类似冒泡排序的操作，将两个位置之间每次交换，再统一循环答案。

但如果我给出一个数对：$[1,2,5,7,16,37,11]$，此时，我们已经来到了第 $7$ 步（这是个奇数步），而要交换的却正是为偶数下标的 $37$ 和 $11$，那我们就得多费步数了。

### 解决方案
我们可以维护一个下标 $cur$，而他一直处于与当前步数的奇偶性相反的位置，这样我们就可以避免浪费 $2$ 步，出现错误。

细节在代码里有注释：
```cpp
void dfs(int cur)//维护下标 
{
    if(cur == n - 2)//当前下标可以进行操作 
	{
        while(!(temp[n - 2] < temp[n - 1] && temp[n - 1] < temp[n]))
		{
			if(nxt != 0)//下一个下标 
			{
				swap(temp[pos1], temp[pos1 + 1]);//“pos1”为奇数 
				ans.push_back(pos1);//定义一个向量，将每一次的位置键入 
			}
			else
			{
				swap(temp[pos2], temp[pos2 + 1]);//“pos2”为偶数 
				ans.push_back(pos2);
			}
            nxt ^= 1;//位运算操作，维护奇偶性 
        }
        return;
    }
	int i = cur; 
	if(temp[i] == cur)
	{
       	if(i == cur)
		{
			dfs(cur + 1);
			return;
		}
        else if(i % 2 == nxt)
		{
           	if(i == n)
			{
           		swap(temp[n - 2], temp[n - 1]);//注意每次要交换，不然每次都是重复在做 
				ans.push_back(n - 2);
           		nxt ^= 1;
			}
			else
			{
				swap(temp[i], temp[i + 1]);
				ans.push_back(i);
            	swap(temp[i - 1], temp[i]);
				ans.push_back(i - 1);
	           	i ++;//这一步很关键，因为当前nxt的奇偶性正确，需要+1 
			}
        }
        for(int j = i - 1; j >= cur; j --)
		{
            swap(temp[j], temp[j + 1]);
            ans.push_back(j);
			nxt ^= 1;
        }
        dfs(cur + 1);
        return;
    }
	}
	return;
}
```

---

## 作者：promise_ (赞：1)

## 题意
给定一个长度为 $n$ 的序列 $a$，你需要在 $n^2$ 的操作数内把序列变为升序

对于奇数次操作，交换 $a_q$ 与 $a_{q+1}$（ $q$ 为奇数）。

对于奇数次操作，交换 $a_q$ 与 $a_{q+1}$（ $q$ 为偶数）。

## 思路

由于 $n^2$ 次的操作放的很宽，我们不妨考虑一种类似冒泡排序的暴力思路。

首先，根据题意，操作位置要么是奇数位，要么是偶数位。不妨先扫一遍排列中的奇数位置和偶数位置。

对于奇数位置上的元素，我们可以考虑遍历整个奇数的范围，每次选取两个相邻的奇数位置，如果它们的元素不满足升序关系，则交换它们。这样可以保证奇数位置上的元素满足升序关系。

偶数同理。



---

## 作者：_luanyi_ (赞：0)

发现 $n$ 很小，$n^2$ 的操作次数很宽，因此直觉上来讲可以乱搞来做。

在众多排序算法中选择一个，那就选择排序吧。

具体地，从大到小依次给数尝试往右移，以试图让它能移到他最终要在的位置。

设这一次操作的操作编号奇偶性为 $c\in\{0,1\}$，当前轮到的数下标为 $i$。

当 $i\bmod 2=c$ 时，显然可以直接移动。重点在 $i\bmod 2\neq c$ 的情况。

在这种情况下，我们尝试浪费这一次操作，若能不太改变局面，那么下一个操作就变成了 $i\bmod 2=c$ 的操作，就可以将当前的数向右移以靠近目标。

怎么浪费呢？一个比较简单的想法是试图操作最左边几个位置，因为这几个位置一定是在右边所有位置都已经归为后才需要去处理的，因此在右边没怎么搞好时我们并不关心最左边那几个位置长什么样。

一个简单的实现流程如下：

- 若 $c=1$：若 $i=2$ 则操作位置 $3$，否则操作位置 $1$。注意到这里在 $n=3$ 的时候只能操作 $1$，需要特判。
- 若 $c=0$：发现如果只操作 $2$ 会导致死循环（比如对于 $4,3,1,2$）。因此可以构造操作序列：操作 $2$，再操作 $1$，再操作 $2$。其他合理的操作方法也是可以的，这里连续三次看似无厘头的操作是为了防止死循环。~~为什么是先 2 再 1 再 2 呢？实际上是我这么写了之后发现某样例不会死循环了之后交上去直接过了。~~

然后如果不死循环的话正确性就是对的了。

实践是检验真理的唯一标准，交上去没有死循环，那就过了吧。

```cpp
const int maxn = 200200;
int n, a[maxn], c;
vector <int> ansl;
void work (int i) {
	c ^= 1; swap (a[i], a[i+1]); ansl.pb (i);
}
void solve () {
	cin >> n;
	fq (i, 1, n) cin >> a[i];
	ansl.clear ();
	c = 1;
	while (1) {
		bool flg = 1;
		for (int i = 1; i < n; i++) if (a[i] > a[i + 1]) {flg = 0; break;}
		if (flg) break;
		int x = n; while (a[x] == x) --x;
		int j = 1; while (a[j] != x) ++j;
		if ((j & 1) == c) {work (j); continue;}
		if (c == 1) {
			if (j == 2) {work (n == 3 ? 1 : 3); continue;}
			work (1);
		} else {
			work (2); work (1); work (2);
		}
	}
	cout << ansl.size () << endl;
	for (auto i : ansl) cout << i << ' '; cout << endl;
}
```

注意到复杂度大概是 $O(n^3)$ 规模，因此不优化是不会超时的。

---

## 作者：wzt2012 (赞：0)

### 题目概述

有一个长度为 $n$ 的排列，要求通过 $n^2$ 次操作把他变成 $1,2\dots n$ 的排列：

- 奇数次操作可以操作奇数位置 $x$，即交换 $p[x],p[x+1]$

- 偶数次操作可以操作偶数位置 $x$，即交换 $p[x],p[x+1]$


$n\le 500$

### 解题方法

$n^2$ 次操作这么宽松，可以考虑一下一次把 $1,2,3\dots $ 换到第一个位置，第二个位置，第三个位置 $\dots $

看上去交换是很容易的，如果目标数字在奇数位置，现在操作也在奇数位置怎么办？这就涉及了浪费步数的问题，递归到 $n=3$ 的情况是可以特判的，那么我们考虑 $n>3$ 的情况。

可以直接操作目标数字，再操作初始目标数字位置的前一位浪费步数，那么现在奇偶性就对得上了，直接往前一直操作就行。注意如果目标数字在 $n$ 这个位置，就操作 $n - 2$ 浪费步数即可。

对于 $n=3$ 一直无脑乱换，可以证明有限步内达到答案状态。

### 参考代码

```
#include<bits/stdc++.h>
using namespace std;
const int M = 505;
int read(){
	int x = 0;
	int f = 1;
	char c;
	while((c = getchar()) < '0' || c > '9'){
		if(c == '-') f = -1;
	}
	while(c >= '0' && c <= '9'){
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
int T, n, nw, f, ji, ou, p[M];
vector<int> ans;
void work(int &nw){
    if(nw){
		swap(p[ji], p[ji + 1]);
		ans.push_back(ji);
	}else{
		swap(p[ou], p[ou + 1]);
		ans.push_back(ou);
	}
    nw ^= 1;
}
void solve(int x){
    if(x == n - 2){
        while(!(p[n - 2] < p[n - 1] && p[n - 1] < p[n])){
			if(nw){
				swap(p[ji], p[ji + 1]);
				ans.push_back(ji);
			}else{
				swap(p[ou], p[ou + 1]);
				ans.push_back(ou);
			}
            nw ^= 1;
        }
        return;
    }
    for(int i = x; i <= n; i ++)
        if(p[i] == x){
        	if(i == x){
				solve(x + 1);
				return;
			}
            if(i % 2 == nw){
            	if(i == n){
            		swap(p[n - 2], p[n - 1]);
					ans.push_back(n - 2);
            		nw ^= 1;
				}else{
					swap(p[i], p[i + 1]);
					ans.push_back(i);
	            	swap(p[i - 1], p[i]);
					ans.push_back(i - 1);
	            	i ++;
				}
            }
            for(int j = i - 1; j >= x; j --){
                swap(p[j], p[j + 1]);
                ans.push_back(j);
				nw ^= 1;
            }
            solve(x + 1);
            return;
        }
}
signed main(){
    T = read();
    while(T --){
        n = read();
		ans.clear();
		nw = 1;
        if(n % 2 == 0){
        	ji = n - 1;
			ou = n - 2;
		}else{
			ji = n - 2;
			ou = n - 1;
		}
        for(int i = 1; i <= n; i ++) p[i] = read();
        if(n == 2){
            if(p[1] == 1) puts("0\n");
            else printf("1\n1\n");
            continue;
        }
        solve(1);
        printf("%d\n", ans.size());
        for(int i = 0; i < ans.size(); i ++) printf("%d ", ans[i]);
        puts("");
    }
    return 0;
}


```

---

