# Contest for Robots

## 题目描述

Polycarp is preparing the first programming contest for robots. There are $ n $ problems in it, and a lot of robots are going to participate in it. Each robot solving the problem $ i $ gets $ p_i $ points, and the score of each robot in the competition is calculated as the sum of $ p_i $ over all problems $ i $ solved by it. For each problem, $ p_i $ is an integer not less than $ 1 $ .

Two corporations specializing in problem-solving robot manufacturing, "Robo-Coder Inc." and "BionicSolver Industries", are going to register two robots (one for each corporation) for participation as well. Polycarp knows the advantages and flaws of robots produced by these companies, so, for each problem, he knows precisely whether each robot will solve it during the competition. Knowing this, he can try predicting the results — or manipulating them.

For some reason (which absolutely cannot involve bribing), Polycarp wants the "Robo-Coder Inc." robot to outperform the "BionicSolver Industries" robot in the competition. Polycarp wants to set the values of $ p_i $ in such a way that the "Robo-Coder Inc." robot gets strictly more points than the "BionicSolver Industries" robot. However, if the values of $ p_i $ will be large, it may look very suspicious — so Polycarp wants to minimize the maximum value of $ p_i $ over all problems. Can you help Polycarp to determine the minimum possible upper bound on the number of points given for solving the problems?

## 说明/提示

In the first example, one of the valid score assignments is $ p = [3, 1, 3, 1, 1] $ . Then the "Robo-Coder" gets $ 7 $ points, the "BionicSolver" — $ 6 $ points.

In the second example, both robots get $ 0 $ points, and the score distribution does not matter.

In the third example, both robots solve all problems, so their points are equal.

## 样例 #1

### 输入

```
5
1 1 1 0 0
0 1 1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
0 0 0
0 0 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
1 1 1 1
1 1 1 1```

### 输出

```
-1```

## 样例 #4

### 输入

```
9
1 0 0 0 0 0 0 0 1
0 1 1 0 1 1 1 1 0```

### 输出

```
4```

# 题解

## 作者：do_while_true (赞：3)

### 题目翻译:

有两个机器人，n道题，给出两个机器人能否完成每道题，让你分配n道题每道题的分数，使得第一个机器人的得分超过第二个机器人，并且使这些题的最高分数最小。如果不管怎样分配分数，第一个机器人都无法超过第二个机器人，输出-1

#### 输入格式

第一行 一个整数n，表示有n道题

第二行 n个整数 如果第i个数为1代表第一个机器人会做第i道题，反之则不会做

第三行 n个整数 如果第i个数为1代表第二个机器人会做第i道题，反之则不会做

#### 输出格式

如果适当分配分数能使第一个机器人超过第二个机器人，则输出n道题中分数最大的题，并保证这个分数最小

如果不能的话，输出-1

### 题目分析:

首先两个机器人都能答对的和都不能答对的怎么分配都不会对最后结果有影响，所以说都答对和都不能答对的我们不需要考虑。

我们假设想取胜的是**A**，另一个是**B**，我们现在只需要考虑给**只有A答对的**，和**只有B答对的**分配分数。设**只有A答对的题**有$cnt1$个，**只有B答对的题**有$cnt2$个。

我们想让A获胜就要尽可能地给只有B答对的题分配低分，给只有A答对的题分配高分。

给只有B答对的题分配低分，而最低分是1，所以我们将**只有B答对的题**都划为1，那么现在不计算**只有A答对的题**，B现在超过A $cnt2$分

想要A和B分数相等，则每道**只有A答对的题**要分配$cnt2/cnt1$分，如果想要A超过B，则要分配$cnt2/cnt1+1$分

显然如果除数cnt1为0的时候属于无解的情况

### *Code:*

```
#include<iostream>
using namespace std;
int n,a[101],b[101],cnt1,cnt2;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	   scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	   scanf("%d",&b[i]);
	for(int i=1;i<=n;i++){
		if(a[i]&&(!b[i])) cnt1++;
		if(b[i]&&(!a[i])) cnt2++;
	}
	if(cnt1==0) puts("-1");
	else printf("%d\n",cnt2/cnt1+1);
    return 0;
}
```


代码可能雷同，这里给出比赛时我的[提交](https://codeforces.com/contest/1321/submission/72175167)以证明此篇题解并非抄袭

---

## 作者：Aehnuwx (赞：1)

使用贪心思想。如果第一队在第 $i$ 轮比赛中输给第二队或平局，显然 $p_i=1$。

统计第一队平局的次数为 $a$，输的次数为 $b$，赢的次数为 $c$。显然，当 $a+b=n$ 时需输出`-1`。否则，输出 $\lceil \dfrac{b+1}{c} \rceil$ 即可。

其正确性显然：当第一队输或平局了所有比赛，显然无法完成任务；否则，若想把丢掉的分数（$b$ 分）追回来，则需要在赢得比赛中总共得到 $(b+1)$ 分；又因为一共赢下了 $c$ 场比赛，故 $\max p_i=\lceil \dfrac{b+1}{c} \rceil$。

---

## 作者：B_lhx (赞：1)

[CF1321A 【Contest for Robots】](https://www.luogu.com.cn/problem/CF1321A)
===
题目大概翻译
--
两队比赛，0表示一道题不可以做出来，1表示一道题可以做出来，$Polycarp$想让第一队赢（注意：平局不算），他可以改变每一道题的分数（必须大于等于1），求改完分数后每题分数中最大值最小是多少（如果一队赢不了输出-1）

思路
----
1输入两队的题目情况

2统计第一队有几题只有他会做

3统计第二队有几题只有他会做

4剪枝

5计算
详见代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;//一个变量n，象征n道题
int a[100005];//数组a，表示第一队
int b[100005];//数组b，表示第er队
int px=0,py=0;//两个计数器~~
int main() {
cin>>n;//输入n
for(int i = 0;i<n;i++){//循环
	cin>>a[i];//输入
}
for(int i = 0;i<n;i++){//循环
	cin>>b[i];//输入
	if(a[i]==1&&b[i]==0){//统计第一队有几题只有他会做
		px++;//计数器++
	}
	if(a[i]==0&&b[i]==1){//统计第二队有几题只有他会做
		py++;//计数器++
	}
}
if(px==0){//特判剪枝（如果一队会做的二队都会做）
	cout<<-1;//输了
	return 0;
}
int o=1;//统计
while(o*px<=py){//如果当前用不行
	o++;//下一项
}
cout<<o;//输出
   return 0; 
}
```


---

## 作者：dead_X (赞：1)

## 1 题意简述
给出长度为 $n(n\leq100)$ 的两个01数列 $a,b$ ，让你设计一个长度为 $n$ 的正整数列 $k$ ，使得 $\Sigma a_i k_i > \Sigma b_i k_i$。

求 $max(k_i| 1\leq i \leq n)$ 的最小值。
## 2 思路简述
按位比较，如果 $a_i=b_i$ ，那么无论 $k_i$ 为几，两个数列的差不变。

所以分别统计 $a_i=1,b_i=0$ 和 $a_i=0,b_i=1$ 的 $i$ 的数量，记为 $k,l$

$l=0$ 时显然不可能办到，直接输出``-1``

不然输出 $\lfloor \frac{k}{l} \rfloor +1$ 即可
## 3 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[100003],b[100003]; 
int main()
{
	int n,k=0,l=0;
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=n; i++) scanf("%d",&b[i]);
	for(int i=1; i<=n; i++) if(!a[i]) if(!b[i]) continue; else k++; else if(b[i]) continue; else l++;
	if(!l) return 0&printf("-1");
	printf("%d",k/l+1);
	return 0;
}
```
## 4 评价
赛时想出做法所用时间:0min

比赛A掉所用时间:7min

建议难度:红

---

## 作者：AlanSP (赞：0)

### 题意：给定2个01串，构造一个p数组，使得上面1的位置对应p的总得分大于下面的，输出最大值。

我们可以使用2个cnt，分别记录两种情况：

1. 上面1，下面0。

2. 下面1，上面0。

同0同1的情况可以忽略，因为对答案没有影响。

记录完后，我特判了两种情况。

1. 上面没有1，那一定是不行的，输出-1。

2. 下面没有1，最大值放1就行，输出1。

我们只需要考虑最大值即可，不关注位置。

贪心，我们只要保证第二种情况每次得分取1就行。

然后依次枚举最大得分，什么时候第一次超过第二种的得分（数量），就输出即可。

（记住是严格大于而不能大于等于~~因为这个爆了50分QAQ~~）。
```cpp

 #include <bits/stdc++.h>
using namespace std;
#define int long long
 
int n,cnt1,cnt2;
int a[109],b[109];
 
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++)
	{
		if(a[i]&&!b[i])
		{
			cnt1++;
		}
		if(!a[i]&&b[i])
		{
			cnt2++;
		}
	}
	if(!cnt1)
	{
		puts("-1");
		return 0;
	}
	if(!cnt2||cnt1>cnt2)
	{
		puts("1");
		return 0;
	}
	for(int i=1;i<=0x3f3f3f3f;i++)
	{
		if(cnt1*i>cnt2)
		{
			printf("%d",i);
			return 0;
		}
	}
	return 0;
}

```


---

## 作者：Reanap (赞：0)

作为$div2$的第一题还是比较不错的。

首先，想让一号机器人赢，就必须让只有一号机器人会的题的分值比只有二号机器人会的题的分值高。

下面分类讨论：

1、如果一号机器人没有只有它会做的题，则不可能赢。

2、如果只有一号机器人会的题比只有二号机器人会的题多，那么每道题的分值只用为$1$即可。

3、否则，先把每道题的分值设成$1$，那么发现一号机器人低了$x$分，那么我们把这$x+1$分平均分给只有一号机器人的会的题就可以保证最高分最小

我们只需要判断出只有一号机器人会的题和只有二号机器人会的题即可。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int r[105] , l[105];
int main() {
	int n;
	scanf("%d" , &n);
	for (int i = 1; i <= n; ++i) scanf("%d" , &r[i]);
	for (int i = 1; i <= n; ++i) scanf("%d" , &l[i]);
	int x = 0 , y = 0;
	for (int i = 1; i <= n; ++i) {
		if(l[i] > r[i]) y ++;
		else if(l[i] < r[i]) x ++;
	}
	if(x == 0) printf("-1");
	else if(x > y) printf("1");
	else if(x == y) printf("2");
	else printf("%d" , y / x + 1);
	return 0;
}

```

---

## 作者：formkiller (赞：0)

### Problem :

有 $N$ 个任务，给出两台机器分别可以完成的任务。现在让你给每个任务取一个正整数作为分数，使得第一台机器的得分总和大于第二台机器，求这 $N$ 个任务里最大分数最小化。当无论如何都不存在第一台机器的得分总和大于第二台机器时输出 $-1$。


------------
### Solution :

考虑到如果两台机器可以解决同一个任务，那么比较他们的得分总和时不会因这个任务的分值大小而改变，既然我们要使得最大值最小化，那么取 $1$ 可以使对答案的影响最小；同理，若两台机器都不能解决一个任务，得分总和也不会因这个任务的分值大小而改变，同样的取 $1$ 即可。

剩下的任务就分成两类：第一台机器能做而第二台不能做的，第一台机器不能做而第二台能做的。我们记第一类任务的数量为 $A$ ，第二类任务的数量为 $B$ 。为了使第一台机器的得分总和大于第二台机器，我们让第二台机器的总分值尽可能小，这样就可以使得第一台机器的得分尽可能小，均摊下来的每个任务的分值也会较小。我们让第二类任务的分值均为 $1$，所以第二台机器的总得分取到最小值 $B$，当第一类任务取到 $\frac{B}{A}$ 时，得分相同。但由于每个任务的分数只能是正整数，并且要 $A$ 严格大于 $B$ ，所以取每个任务的分数为 $\frac{B}{A} + 1$ ，由于 C++ 的向下取整，所以可以直接保存答案。最后特判当 $A$ 为0的情况即可。

~~太久没有写过题解可能略显啰嗦，见谅~~

------------
### Code:
```cpp
//good luck
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <string>
# include <algorithm>

#define is(a) (a>='0'&&a<='9')

using namespace std;

int N,a[maxn],b[maxn],A,B;

inline void read(int &x)
{
  x=0;bool f=0;char ch=getchar();
  for (;!is(ch);ch=getchar()) f|=ch=='-';
  for (;is(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
  x=f?-x:x;
}

int main()
{
	read(N);
	for (int i = 1; i <= N; ++i) read(a[i]);
	for (int i = 1; i <= N; ++i) read(b[i]);
	for (int i = 1; i <= N; ++i)
	{
		if (a[i]&&!b[i]) ++A;
		if (!a[i]&&b[i]) ++B;
	}
	if (A==0) cout << -1 << endl;
	else	  cout << B/A+1 << endl;
    return 0;
}

```
 


---

