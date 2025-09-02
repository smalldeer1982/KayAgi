# Asesino (Hard Version)

## 题目描述

这是该问题的困难版本。在本版本中，你必须使用尽可能少的询问次数。只有在两个版本都被解决的情况下，你才能进行 Hack。

这是一个交互式问题。

在墨西哥国家 IOI 集训中，有一个传统游戏叫做“Asesino”，它类似于“Among Us”或“Mafia”。

今天，有 $n$ 名玩家（编号从 $1$ 到 $n$）将参与“Asesino”游戏，游戏中有以下三种角色：

- 骑士（Knight）：骑士总是说真话。
- 恶棍（Knave）：恶棍总是说谎。
- 冒名顶替者（Impostor）：冒名顶替者表面上被所有人认为是骑士，实际上却是恶棍。

每个玩家都会被分配一个角色。游戏中恰好有一名冒名顶替者，但骑士和恶棍的人数可以为任意（可能为零）。

作为游戏主持人，你不小心忘记了每个人的角色，但你需要确定谁是冒名顶替者。

为了找出冒名顶替者，你可以提出一些问题。每次提问，你可以选择两个玩家 $i$ 和 $j$（$1 \leq i, j \leq n$，$i \neq j$），并询问玩家 $i$ 是否认为玩家 $j$ 是骑士。问题的回答规则如下表所示：

|         | 骑士（Knight） | 恶棍（Knave） | 冒名顶替者（Impostor） |
|---------|:--------------:|:-------------:|:----------------------:|
| 骑士    | 是             | 否            | 是                     |
| 恶棍    | 否             | 是            | 否                     |
| 冒名顶替者 | 否           | 是            | —                      |

表中第 $a$ 行第 $b$ 列的回答表示当 $i$ 的角色为 $a$，$j$ 的角色为 $b$ 时的回答。例如，第一行第三列的“是”表示当 $i$ 是骑士，$j$ 是冒名顶替者时的回答是“是”。

请用最少的询问次数找出冒名顶替者。也就是说，设 $f(n)$ 为对于 $n$ 个玩家，存在一种策略最多用 $f(n)$ 次询问就能确定冒名顶替者。你必须在不超过 $f(n)$ 次询问内确定冒名顶替者。

注意：评测器是自适应的：玩家的角色在一开始并未固定，可能会根据你的提问动态变化。但保证始终存在一种角色分配方式，使得所有已提问的问题都满足本题的约束。

## 说明/提示

注意，示例测试用例并不代表最优的提问策略，仅用于演示交互格式。实际上，通过示例中的提问无法确定冒名顶替者。

在第一个测试用例中，第 $2$ 和第 $6$ 位玩家是骑士，第 $1$、$3$、$5$、$7$ 位玩家是恶棍，第 $4$ 位玩家是冒名顶替者。以下是各次提问的解释：

- 第一次提问，$i$ 是恶棍，$j$ 是恶棍。回答为“是”，因为恶棍总是说谎。
- 第二次提问，$i$ 是恶棍，$j$ 是骑士。回答为“否”，因为恶棍总是说谎。
- 第三次提问，$i$ 是骑士，$j$ 是恶棍。回答为“否”，因为骑士总是说真话。
- 第四次提问，$i$ 是骑士，$j$ 是骑士。回答为“是”，因为骑士总是说真话。
- 第五次提问，$i$ 是冒名顶替者，$j$ 是恶棍。回答为“是”，因为冒名顶替者总是说谎。
- 第六次提问，$i$ 是冒名顶替者，$j$ 是骑士。回答为“否”，因为冒名顶替者总是说谎。
- 第七次提问，$i$ 是恶棍，$j$ 是冒名顶替者。回答为“否”，因为恶棍总是说谎，并且恶棍认为冒名顶替者是骑士。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
7

1

0

0

1

1

0

0

4

0

1

1

1```

### 输出

```
? 1 3

? 7 6

? 2 5

? 6 2

? 4 5

? 4 6

? 1 4

! 4

? 1 2

? 2 3

? 3 4

? 4 1

! 3```

# 题解

## 作者：int08 (赞：5)

## 前言
神仙题。
## 题意
交互题，有 $n$ 个人，其中有一些好人和一些坏人，还有一个内鬼，你每次可以选择问一个人回答另一个人是不是好人，回答如下表：


||好人|坏人|内鬼|
|:-:|:-:|:-:|:-:|
|好人|Yes|No|Yes|
|坏人|No|Yes|No|
|内鬼|No|Yes|-|

例如，你问内鬼一个好人是不是好人，他会回答 No。

简单版中，你需要通过 $n+69$ 次询问确定内鬼，困难版中，你需要用尽可能少的次数确定，交互库自适应，所以就等于确定一个策略使最坏情况下次数最少。

# Solution

### Easy Version

如果不考虑内鬼，发现直接的 Yes 或者 No 带来了很少的信息，你同时交换所有人的身份甚至仍然是对的。

进一步的假如没有内鬼，事实上 Yes 和 No 带来的信息是两个人身份相同 / 不同。

不过内鬼会在相同和不同上露馅，如果两个人互相问问，答案应该是一样的，如果中间有一个内鬼，答案就不同。

所以，我们可以用两次询问确定内鬼是否在某两个人当中。

这样很简单了，我们两个人两个人问，如果确定在这两个人当中，选择这两人中的一个和外面的一个人（此时可以确定不是内鬼）再做一次就可以确定是这两个人中哪一个了。

否则最后必然剩下一到两个人，用一样的方案确定即可。

观察到这种情况下，$n$ 为偶数最坏 $n$ 次询问，$n$ 为奇数时候最坏 $n+1$ 次询问（剩下最后 $3$ 人，用了 $4$ 次才确定），可以通过简单版。

~~你不会以为这个就能通过困难版了吧。~~

### Hard Version
为啥不是最优啊？

首先感觉一下，最优解应该不可能小于 $n$，证明见最下面。

看来偶数已经是最优了，奇数还可以优化。

感觉上，奇数的方案上，还剩 $3$ 个的时候两种情况用了 $2$ 和 $4$ 次，不平衡，可以优化。

但是我们穷尽了 $n=3$ 的所有问法，也找不到只用 $3$ 次的，~~所以为什么还没有 AC？~~

看来只能是 $n\ge 5$ 时候有优化了。

我们需要避免最后剩三个的情况，考虑一开始就除去三个。

最开始就让 $1$ 问 $2$，$2$ 问 $3$，$3$ 问 $1$，如果没有内鬼，应该全是 Yes 或者一个 Yes 两个 No。

否则说明在他们三个中间，我们再用 $4$ 次确定是谁，否则我们就用 $3$ 次排除了三个人。

这下 $n\ge 7$ 最优了，仍然没有 AC，说明还可以优化 $n=5$！

发现在他们三个中间的时候，我们再问 $4$ 次中有两次前面问过了，直接用就行，所以只需要 $5$ 次，我们也终于得到了 AC。
## AC Code
[Link](https://codeforces.com/contest/2022/submission/285814695)
### proof
（翻译自 CF 官方题解）
>考虑由查询生成的有向图。根据鸽巢原理，至少有一个节点的入度为 $0$，至少有一个节点的出度为 $0$。
>
> - 如果这两个节点不同，则称 $A$ 为入度为 $0$ 的节>点，$B$ 为出度为 $0$ 的节点，存在两种情况满足回答全部是 Yes：
>
>   - $A$ 是内鬼，其他人都是坏人。
>    
>   - $B$ 是内鬼，其他人都是好人。
> - 如果这两个节点相同，那么图看起来就像是一个循环和一个孤立节点的集合。假设最后一次询问是 $A$ 询问 $B$，存在两种情况满足回答除了最后一次全是 Yes：
>    
>    - $A$ 是内鬼，循环中的其他人都是好人。
>    
>    - $B$ 是内鬼，循环中的其他人都是好人。
>
> 因此，我们已经证明，在 $n - 1$ 个询问中，无论问什么问题，都不可能在 $n$ 个人中找到内鬼。 $\blacksquare$
>
# The End.

---

## 作者：Annihilation_y (赞：2)

原来我的证明是对的。被同学反复质疑了一个早上。感觉早上的课都听得不是很认真。

## 思路

我们把对 $x$ 询问 $y$ 当做一条边，就相当于是建图。

玩一玩表格可以发现，如果 $x$ 到 $y$ 的双向边不相同，那么内鬼一定在 $x$ 和 $y$ 中。否则这两个点一定都不是内鬼。

~~然后赛时成功想出了 $1$ 和 $i$ 连双向边这种智慧做法，简单版本都过不去。~~

- 对于偶数来说，可以通过至多 $n-2$ 次的询问，每次 $i$ 和 $i+1$ 连双向边，来确定内鬼到底在哪两个点中。再把两个点中的其中一个点与已经确定的不是内鬼的点连双向边，就可以求出内鬼是哪个，总共的次数是 $n$ 次。

- 可是对于奇数来说，我们用至多 $n-1$ 次询问确定了内鬼在哪里，总次数就是 $n+1$，显然不够优秀。首先 $n=3$ 是肯定优化不了了。对于 $n=5$，我们采用~~询问同学~~打表可以发现是可以优化的。

- 具体做法如下：我们先把前三个点连成一个环，显然我们是可以判断环中有没有内鬼的。如果有，再用两次把内鬼找出来，如果没有，内鬼就在剩下两个当中，用两次找出来。容易发现，$n \ge 5$ 的奇数都可以这么干。这样，我们对于所有 $n > 3$ 的数都可以用 $n$ 次解决了。

现在，我们需要证明，我们不能用 $n-1$ 次找出答案。

由于只有 $n-1$ 条边，所以一定有一个点入度为 $0$，一定还有个点出度为 $0$。

假设不是一个点，那么对于这个子图，我们对所有的边的权值都设成 $1$，那么就有两种情况。

- 入度为 $0$ 的点是内鬼，其他的是骗子。

- 出度为 $0$ 的点是内鬼，其他的是好人。

所以是判断不了的。

假设是一个点，那么相当于用 $n-1$ 条边，确定了内鬼在哪条边中。最差的情况是还需要通过两次确定内鬼到底是哪个。

证明部分可能不是特别严谨，如果有问题私信问我。

## Code

```c++
#include <bits/stdc++.h>
using namespace std;
namespace yhy{
	const int MAXN=1e5+5;
	int n;
	inline void Output(int x,int y) {
		int t=x-1;
		if(t==0) t=n;
		int a,b;
		cout<<"? "<<x<<" "<<t<<endl;
		cin>>a;
		cout<<"? "<<t<<" "<<x<<endl;
		cin>>b;
		if(a==b) cout<<"! "<<y<<endl;
		else cout<<"! "<<x<<endl;
	}
	int main() {
//		freopen(".in","r",stdin);
//		freopen(".out","w",stdout);
		std::ios::sync_with_stdio(false);
		cin.tie(0);cout.tie(0);
		int T;cin>>T;
		while(T--) {
			cin>>n;
			if(n==3) {
				int x1,x2;
				int y1,y2;
				cout<<"? 1 2"<<endl;cin>>x1;
				cout<<"? 2 1"<<endl;cin>>x2;
				cout<<"? 1 3"<<endl;cin>>y1;
				cout<<"? 3 1"<<endl;cin>>y2;
				if(x1==x2 && y1!=y2) cout<<"! 3"<<endl;
				if(x1!=x2 && y1==y2) cout<<"! 2"<<endl;
				if(x1!=x2 && y1!=y2) cout<<"! 1"<<endl;
			}
			else if(n&1) {
				int a,b,c;
				cout<<"? 1 2"<<endl;cin>>a;
				cout<<"? 2 3"<<endl;cin>>b;
				cout<<"? 3 1"<<endl;cin>>c;
				if(a+b+c==0 || a+b+c==2) {
					int x,y;
					cout<<"? 2 1"<<endl;cin>>x;
					cout<<"? 1 3"<<endl;cin>>y;	
					if(a==x && c!=y) cout<<"! 3"<<endl;
					if(a!=x && c==y) cout<<"! 2"<<endl;
					if(a!=x && c!=y) cout<<"! 1"<<endl;
				}
				else {
					int flag=0;
					for(int i=4;i<=n-2;i+=2) {
						int x,y;
						cout<<"? "<<i<<" "<<i+1<<endl;
						cin>>x;
						cout<<"? "<<i+1<<" "<<i<<endl;
						cin>>y;
						if(x!=y) {
							Output(i,i+1);
							flag=1;
							break;
						}
					}
					if(!flag) {
						Output(n-1,n);
					}
				}
			}
			else {
				int flag=0;
				for(int i=1;i<=n-2;i+=2) {
					int x,y;
					cout<<"? "<<i<<" "<<i+1<<endl;
					cin>>x;
					cout<<"? "<<i+1<<" "<<i<<endl;
					cin>>y;
					if(x!=y) {
						Output(i,i+1);
						flag=1;
						break;
					}
				}
				if(!flag) {
					Output(n-1,n);
				}
			}
		}
		return 0;
	}
}
signed main() {
	yhy::main();
	return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：1)

## 题解：CF2022D2 Asesino (Hard Version)

### 解题思路

神仙题。

观察发现若 $x , y$ 中有一人是冒名顶替者当且仅当询问 `? x y` 和 `? y x` 的答案不同。

于是若 $n$ 为偶数可以通过在 $1$ 至 $n - 2$ 个元素两两排除，在最后两个元素中再判断其中一个做到 $n$ 次询问。

若 $n$ 为奇数则在最后的判断中是留下 $3$ 个数字，做到 $n + 1$ 次询问。

此时已经可以通过简单版本。

偶数显然已经是最优。

我们考虑手摸 $n = 3$。发现 $4$ 次已经是最优，不可能减少。

我们发现若 $n \ge 7$，则可先用 $3$ 次判断前 $3$ 个中是否有冒名顶替者，若有，通过 $4$ 次判断是哪个；若无，按照偶数时的方法解决剩下的位置。到达 $n$ 次操作，显然最优。

只有 $n = 5$ 有些难办。可以使用惊人的观察力发现，若询问 `? 1 2`、`? 2 3`、`? 3 1` 且其中存在内鬼，则在后续判断中会有相同询问被使用，于是我们可以记录以上询问获得的值，并且在后续需要的时候直接调用。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t , n , a , b , c;
bool flag;
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n;
		if(n == 3)
		{
			cout << "? 1 2" << endl;
			cin >> a;
			cout << "? 2 1" << endl;
			cin >> b;
			if(a == b)
			{
				cout << "! 3" << endl;
				continue;
			}
			cout << "? 1 3" << endl;
			cin >> a;
			cout << "? 3 1" << endl;
			cin >> b;
			if(a == b)
			{
				cout << "! 2" << endl;
			}
			else
			{
				cout << "! 1" << endl;
			}
			continue;
		}
		if(n == 4)
		{
			cout << "? 1 2" << endl;
			cin >> a;
			cout << "? 2 1" << endl;
			cin >> b;
			if(a == b)
			{
				cout << "? 1 3" << endl;
				cin >> a;
				cout << "? 3 1" << endl;
				cin >> b;
				if(a == b)
				{
					cout << "! 4" <<endl;
				}
				else
				{
					cout << "! 3" << endl;
				}
				continue;
			}
			cout << "? 1 3" << endl;
			cin >> a;
			cout << "? 3 1" << endl;
			cin >> b;
			if(a == b)
			{
				cout << "! 2" << endl;
			}
			else
			{
				cout << "! 1" << endl;
			}
			continue;
		}
		if(n == 5)
		{
			int a12 , a23 , a31;
			cout << "? 1 2" << endl;
			cin >> a12;
			cout << "? 2 3" << endl;
			cin >> a23;
			cout << "? 3 1" << endl;
			cin >> a31;
			if((a12 + a23 + a31) % 2 == 1)
			{
				cout << "? 1 4" << endl;
				cin >> a;
				cout << "? 4 1" << endl;
				cin >> b;
				if(a == b)
				{
					cout << "! 5" << endl;
				}
				else
				{
					cout << "! 4" << endl;
				}
			}
			else
			{
				cout << "? 2 1" << endl;
				cin >> a;
				if(a12 == a)
				{
					cout << "! 3" << endl;
				}
				else
				{
					cout << "? 3 2" << endl;
					cin >> a;
					if(a23 == a)
					{
						cout << "! 1" << endl;
					}
					else
					{
						cout << "! 2" << endl;
					}
				}
			}
			continue;
		}
		if(n % 2 == 1)
		{
			cout << "? 1 2" << endl;
			cin >> a;
			cout << "? 2 3" << endl;
			cin >> b;
			cout << "? 3 1" << endl;
			cin >> c;
			if((a + b + c) % 2 == 1)
			{
				flag = 1;
				for(int i = 4 ; i + 2 <= n ; i += 2)
				{
					cout << "? " << i << ' ' << i + 1 << endl;
					cin >> a;
					cout << "? " << i + 1 << ' ' << i << endl;
					cin >> b;
					if(a != b)
					{
						cout << "? 1 " << i << endl;
						cin >> a;
						cout << "? " << i << " 1" << endl;
						cin >> b;
						if(a == b)
						{
							cout << "! " << i + 1 << endl;
						}
						else
						{
							cout << "! " << i << endl;
						}
						flag = 0;
						break;
					}
				}
				if(flag)
				{
					cout << "? 1 " << n << endl;
					cin >> a;
					cout << "? " << n << " 1" << endl;
					cin >> b;
					if(a == b)
					{
						cout << "! " << n - 1 << endl;
					}
					else
					{
						cout << "! " << n << endl;
					}
				}
			}
			else
			{
				cout << "? 2 1" << endl;
				cin >> c;
				if(a == c)
				{
					cout << "! 3" << endl;
				}
				else
				{
					cout << "? 3 2" << endl;
					cin >> a;
					if(a == b)
					{
						cout << "! 1" << endl;
					}
					else
					{
						cout << "! 2" << endl;
					}
				}
			}
			continue;
		}
		else
		{
			cout << "? 1 2" << endl;
			cin >> a;
			cout << "? 2 1" << endl;
			cin >> b;
			if(a == b)
			{
				flag = 1;
				for(int i = 3 ; i + 2 <= n ; i += 2)
				{
					cout << "? " << i << ' ' << i + 1 << endl;
					cin >> a;
					cout << "? " << i + 1 << ' ' << i << endl;
					cin >> b;
					if(a != b)
					{
						cout << "? 1 " << i << endl;
						cin >> a;
						cout << "? " << i << " 1" << endl;
						cin >> b;
						if(a == b)
						{
							cout << "! " << i + 1 << endl;
						}
						else
						{
							cout << "! " << i << endl;
						}
						flag = 0;
						break;
					}
				}
				if(flag)
				{
					cout << "? 1 " << n << endl;
					cin >> a;
					cout << "? " << n << " 1" << endl;
					cin >> b;
					if(a == b)
					{
						cout << "! " << n - 1 << endl;
					}
					else
					{
						cout << "! " << n << endl;
					}
				}
			}
			else
			{
				cout << "? 1 3" << endl;
				cin >> a;
				cout << "? 3 1" << endl;
				cin >> b;
				if(a == b)
				{
					cout << "! 2" << endl;
				}
				else
				{
					cout << "! 1" << endl;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：1)

独立想的，感觉比较牛。

这里说一下思路。

首先发现，如果不考虑 Impostor，那么 Yes 和 No 的意义就相当于 $i$，$j$ 两个人的阵营是否相同（类似异或？）。

我们加入 Impostor 并为其赋予一个意义，发现在这个人处在 $j$ 的位置时相当于 Knight，否则相当于 Knave。

考虑利用这一两面性，把 No 看成身份（Knight，Knave）的反转，此时 Impostor 就相当于一个内部的反转，然后尝试与询问建立联系，（由样例）可知对于一个环，反转的次数一定是偶数，由上文，若我们在这一个环中问到了奇数个 No，则这一个环中一定要有 Impostor 才能保证逻辑自洽。

同时，可知如果不与环相连一定无法确定是否有 Impostor，可以得出 $f(n)\ge n$。

接下来考虑问出一个含有 Impostor 的环后如何做，先假设环不包含所有点，则不被包含的点一定不是 Impostor，考虑选一个环内的点和一个环外的点，问包含这两个点的环，就可以确定环内的点是否是 Impostor。

这样，把点两两分组，问一个组内是否有 Impostor 就可以做到 $n+4$ 次，但还有很大的优化空间。

我们发现，不一定要问所有环上的点，只需要问环长 $-1$ 次就可以确定 Impostor 的位置，由此就可以优化到 $n+2$ 次。

再然后，上文的结论对含有 Impostor 的点集也适用，故可以省掉对最后一组的询问，次数为 $n+n\bmod 2$。

提交，发现 WA on #2。

此时我们需要对 $n\bmod 2=1$ 的情况优化，发现有一组只有一个点，这很浪费。

考虑把这一组和另外一组合并，这相当于一个 $n=3$ 的问题，但 $n=3$ 问二元环和三元环都不能做到 $3$ 次，只能做到 $4$ 次，但 $n>3$ 时，处理这个问题就不一定要 $3$ 次了。

首先判断长度为 $3$ 的组，这样就可以用 $7$ 次询问解决，进而把 $n\ge 7$ 优化到 $n$ 次。

提交，WA on #2。

只有 $n=5$ 可以优化了，此时虽然直接问行不通，但是可以把当前的三个点当成一个 $n=3$ 的问题，因为这时我们已经在这三个点之间问了 $3$ 次了，套用 $n=3$ 的做法并加上记忆化即可优化到 $n$ 次。

做完了，精细实现复杂度 $O(n)$。

代码：


```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
#define lb(x) ((x)&(-(x)))
#define gp(i,j) (((i)>>(j-1))&1)
#define ppc __builtin_popcount
#define ushort unsigned short
#define db long double
using namespace std;
const int N=1e5+10,mod=998244353,LM=2.1e7;
const ll inf=1e18+10;
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
map<pii,int> q;
bool ask(int i,int j){
    cout<<"? "<<i<<' '<<j<<endl;
    int res;cin>>res;
    q[mk(i,j)]=res;
    return res;
}
bool vis[N];
int n;
void slv(){
    cin>>n;q.clear();
    for(int i=1;i<=n;i++) vis[i]=0;
    vector<int> err;int pos=0;
    for(int i=1;i+2<=n;i+=2){
        if(i==1&&n%2==1&&n!=3){
            int w1=ask(i,i+1),w2=ask(i+1,i+2),w3=ask(i+2,i);
            if((w1+w2+w3)%2==1){
                vis[i]=1;vis[i+1]=1;vis[i+2]=1;
            }else{
                for(int j=i+3;j<=n;j++) vis[j]=1;
                break;
            }i++;
        }else{
            int w1=ask(i,i+1),w2=ask(i+1,i);
            if(w1==w2){
                vis[i]=1;vis[i+1]=1;
            }else{
                for(int j=i+2;j<=n;j++) vis[j]=1;
                break;
            }
        }
    }for(int i=1;i<=n;i++) if(!vis[i]) err.push_back(i);
    if(err.size()==1){
        cout<<"! "<<err.back()<<endl;
    }else if(n!=5||err.size()==2){
        for(int i=1;i<=n;i++) if(vis[i]) pos=i;
        for(int i=1;i<err.size();i++){
            int ele=err[i];
            int w1=ask(ele,pos),w2=ask(pos,ele);
            if(w1!=w2){
                cout<<"! "<<ele<<endl;
                return ;
            }
        }cout<<"! "<<err[0]<<endl;
    }else{
        int w1=ask(2,1),w2=q[mk(1,2)];
        if(w1==w2){
            cout<<"! "<<3<<endl;
        }else{
            w1=ask(3,2),w2=q[mk(2,3)];
            if(w1==w2){
                cout<<"! "<<1<<endl;
            }else{
                cout<<"! "<<2<<endl;
            }
        }
    }
}
int main(){
    int t=1;cin>>t;
    while(t--) slv();
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2022D2)

**题目大意**

> 给定 $n$ 个人，每个人是骑士或骗子，骑士总说真话，骗子总说假话，但现在有一个骗子进行了伪装，使得其他人都认为他是骑士。
>
> 你可以询问第 $i$ 个人是否认为第 $j$ 个人是骑士，在最少次数内确定伪装的骗子。
>
> 数据范围：$n\le 10^5$。

**思路分析**

询问 $i,j$ 相当于查询 $i,j$ 身份是否相同，因此询问 $(i,j),(j,i)$ 的答案相同时，说明这两人中没有伪装者，反之说明其中恰有一个伪装者。

如果 $n$ 为偶数，$n-2$ 次询问可以确定伪装者在哪两人之间，再询问两次即可确定答案。

否则需要 $n+1$ 次，尝试优化，我们发现如果询问一个环，环上没有伪装者当且仅当有偶数个人回答否。

因此先询问一个三元环，即可变成 $n$ 为偶数的情况，如果伪装者在三元环中，询问两条反向边即可确定答案。

此时在 $n>3$ 时都可以做到 $n$ 次询问。

可以证明不能更小，否则我们可以把欺骗者安排到没有入度的点或没有出度的点上。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
 #include<bits/stdc++.h>
using namespace std;
bool qry(int x,int y) {
	cout<<"? "<<x<<" "<<y<<endl;
	int z; cin>>z; return z^1;
}
void solve() {
	int n;
	cin>>n;
	if(n&1) {
		if(n==3) {
			if(qry(1,2)!=qry(2,1)) {
				bool o=qry(1,3)^qry(3,1);
				cout<<"! "<<(o?1:2)<<endl;
			} else cout<<"! "<<3<<endl;
			return ;
		}
		int a=qry(n,n-1),b=qry(n-1,n-2),c=qry(n-2,n);
		if((a+b+c)&1) {
			a^=qry(n-1,n),b^=qry(n-2,n-1);
			cout<<"! "<<(a&&b?n-1:(a?n:n-2))<<endl;
			return ;
		} else n-=3;
	}
	int p=1,q=3;
	for(int i=3;i<n;i+=2) if(qry(i,i+1)^qry(i+1,i)) {
		p=i,q=1; break;
	}
	bool o=qry(p,q)^qry(q,p);
	cout<<"! "<<(o?p:p+1)<<endl;
}
signed main() {
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

