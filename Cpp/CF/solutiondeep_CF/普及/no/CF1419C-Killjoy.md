# 题目信息

# Killjoy

## 题目描述

A new agent called Killjoy invented a virus COVID-2069 that infects accounts on Codeforces. Each account has a rating, described by an integer (it can possibly be negative or very large).

Killjoy's account is already infected and has a rating equal to $ x $ . Its rating is constant. There are $ n $ accounts except hers, numbered from $ 1 $ to $ n $ . The $ i $ -th account's initial rating is $ a_i $ . Any infected account (initially the only infected account is Killjoy's) instantly infects any uninfected account if their ratings are equal. This can happen at the beginning (before any rating changes) and after each contest. If an account is infected, it can not be healed.

Contests are regularly held on Codeforces. In each contest, any of these $ n $ accounts (including infected ones) can participate. Killjoy can't participate. After each contest ratings are changed this way: each participant's rating is changed by an integer, but the sum of all changes must be equal to zero. New ratings can be any integer.

Find out the minimal number of contests needed to infect all accounts. You can choose which accounts will participate in each contest and how the ratings will change.

It can be proven that all accounts can be infected in some finite number of contests.

## 说明/提示

In the first test case it's possible to make all ratings equal to $ 69 $ . First account's rating will increase by $ 1 $ , and second account's rating will decrease by $ 1 $ , so the sum of all changes will be equal to zero.

In the second test case all accounts will be instantly infected, because all ratings (including Killjoy's account's rating) are equal to $ 4 $ .

## 样例 #1

### 输入

```
3
2 69
68 70
6 4
4 4 4 4 4 4
9 38
-21 83 50 -59 -77 15 -71 -78 20```

### 输出

```
1
0
2```

# AI分析结果

### 题目内容重写

#### 题目描述

Killjoy 发明了一种名为 COVID-2069 的病毒，该病毒会感染 Codeforces 上的账号。每个账号都有一个评分，用一个整数表示（可能是负数或非常大的数）。

Killjoy 的账号已经被感染，其评分恒为 $x$。除了她的账号外，还有 $n$ 个账号，编号从 $1$ 到 $n$。第 $i$ 个账号的初始评分为 $a_i$。任何被感染的账号（最初只有 Killjoy 的账号被感染）会立即感染任何未被感染的账号，如果它们的评分相等。这种情况可能在一开始（在评分变化之前）或每次比赛后发生。一旦账号被感染，就无法恢复。

Codeforces 上定期举行比赛。在每场比赛中，这 $n$ 个账号中的任意一个（包括被感染的账号）都可以参与。Killjoy 不能参与比赛。每场比赛后，评分会发生变化：每个参与者的评分会变化一个整数，但所有变化的总和必须为零。新的评分可以是任意整数。

找出感染所有账号所需的最少比赛次数。你可以选择每场比赛中哪些账号参与，以及评分如何变化。

可以证明，所有账号都可以在有限的比赛次数内被感染。

#### 说明/提示

在第一个测试用例中，可以将所有评分变为 $69$。第一个账号的评分增加 $1$，第二个账号的评分减少 $1$，因此所有变化的总和为零。

在第二个测试用例中，所有账号会立即被感染，因为所有评分（包括 Killjoy 的账号评分）都等于 $4$。

#### 样例 #1

##### 输入

```
3
2 69
68 70
6 4
4 4 4 4 4 4
9 38
-21 83 50 -59 -77 15 -71 -78 20
```

##### 输出

```
1
0
2
```

### 算法分类
数学、构造

### 题解分析与结论

本题的核心在于通过最少次数的比赛将所有账号的评分变为 $x$，从而感染所有账号。题解主要集中在如何通过数学分析和构造操作来实现这一目标。大多数题解都得出类似的结论：答案只能是 $0$、$1$ 或 $2$，具体取决于初始评分的情况。

### 评分较高的题解

#### 题解作者：pigstd (赞：4)

**星级：4.5**

**关键亮点：**
- 清晰地分析了三种情况：$0$ 次、$1$ 次和 $2$ 次。
- 通过数学推导证明了答案的合理性。
- 代码简洁明了，逻辑清晰。

**核心代码：**
```cpp
int t,n,x;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		int h,f,sum; h=f=sum=0;
		for(int i=1,a;i<=n;++i){
			cin>>a;
			h|=(x==a),f|=(x!=a),sum+=a;
		}
		printf("%d\n",n*x==sum?f:2-h);
	}
}
```

**实现思想：**
- 通过遍历所有账号，判断是否所有账号的评分都等于 $x$，或者是否存在至少一个账号的评分等于 $x$。
- 根据这些条件，输出相应的比赛次数。

#### 题解作者：ql12345 (赞：3)

**星级：4**

**关键亮点：**
- 详细解释了每种情况的判断条件。
- 提供了清晰的证明过程，确保答案的正确性。
- 代码实现简洁，易于理解。

**核心代码：**
```cpp
int t,n,x;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		int h,f,sum; h=f=sum=0;
		for(int i=1,a;i<=n;++i){
			cin>>a;
			h|=(x==a),f|=(x!=a),sum+=a;
		}
		printf("%d\n",n*x==sum?f:2-h);
	}
}
```

**实现思想：**
- 通过遍历所有账号，判断是否所有账号的评分都等于 $x$，或者是否存在至少一个账号的评分等于 $x$。
- 根据这些条件，输出相应的比赛次数。

#### 题解作者：SSerxhs (赞：2)

**星级：4**

**关键亮点：**
- 提供了详细的分类讨论，确保所有情况都被覆盖。
- 代码实现简洁，逻辑清晰。
- 通过数学推导证明了答案的合理性。

**核心代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e3+2;
int a[N];
int n,c,fh,i,t,x,tot;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int main()
{
	read(t);
	while (t--)
	{
		read(n);read(x);tot=0;
		for (i=1;i<=n;i++) read(a[i]);
		for (i=1;i<=n;i++) if (a[i]!=x) break;
		if (i>n) {puts("0");continue;}
		for (i=1;i<=n;i++) if (a[i]==x) {puts("1");break;}
		if (i<=n) continue;
		for (i=1;i<=n;i++) tot+=a[i];
		if (x*n==tot) puts("1"); else puts("2");
	}
}
```

**实现思想：**
- 通过遍历所有账号，判断是否所有账号的评分都等于 $x$，或者是否存在至少一个账号的评分等于 $x$。
- 根据这些条件，输出相应的比赛次数。

### 最优关键思路或技巧

1. **分类讨论**：通过将问题分为几种情况（所有账号评分等于 $x$、存在至少一个账号评分等于 $x$、所有账号评分总和等于 $n \times x$），可以简化问题并快速得出答案。
2. **数学推导**：通过数学分析，确保在每种情况下都能通过最少次数的比赛感染所有账号。
3. **代码实现简洁**：通过简单的遍历和条件判断，快速得出答案，代码简洁且易于理解。

### 可拓展之处

类似的问题可以通过分类讨论和数学分析来解决，特别是在涉及最小操作次数或最优解的问题中。这种思路可以应用于其他需要构造操作或优化步骤的题目。

### 推荐题目

1. [P6746](https://www.luogu.com.cn/problem/P6746) - 与本题类似，考察通过最少操作次数达到目标状态。
2. [P1001](https://www.luogu.com.cn/problem/P1001) - 考察通过最少操作次数达到目标状态。
3. [P1002](https://www.luogu.com.cn/problem/P1002) - 考察通过最少操作次数达到目标状态。

### 个人心得摘录

- **pigstd**：通过分类讨论和数学推导，确保答案的正确性，代码简洁明了。
- **ql12345**：详细解释了每种情况的判断条件，提供了清晰的证明过程。
- **SSerxhs**：通过详细的分类讨论，确保所有情况都被覆盖，代码实现简洁。

---
处理用时：50.48秒