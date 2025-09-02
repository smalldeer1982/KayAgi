# 题目信息

# Voting

## 题目描述

There are $ n $ employees in Alternative Cake Manufacturing (ACM). They are now voting on some very important question and the leading world media are trying to predict the outcome of the vote.

Each of the employees belongs to one of two fractions: depublicans or remocrats, and these two fractions have opposite opinions on what should be the outcome of the vote. The voting procedure is rather complicated:

1. Each of $ n $ employees makes a statement. They make statements one by one starting from employees $ 1 $ and finishing with employee $ n $ . If at the moment when it's time for the $ i $ -th employee to make a statement he no longer has the right to vote, he just skips his turn (and no longer takes part in this voting).
2. When employee makes a statement, he can do nothing or declare that one of the other employees no longer has a right to vote. It's allowed to deny from voting people who already made the statement or people who are only waiting to do so. If someone is denied from voting he no longer participates in the voting till the very end.
3. When all employees are done with their statements, the procedure repeats: again, each employees starting from $ 1 $ and finishing with $ n $ who are still eligible to vote make their statements.
4. The process repeats until there is only one employee eligible to vote remaining and he determines the outcome of the whole voting. Of course, he votes for the decision suitable for his fraction.

You know the order employees are going to vote and that they behave optimal (and they also know the order and who belongs to which fraction). Predict the outcome of the vote.

## 说明/提示

Consider one of the voting scenarios for the first sample:

1. Employee $ 1 $ denies employee $ 5 $ to vote.
2. Employee $ 2 $ denies employee $ 3 $ to vote.
3. Employee $ 3 $ has no right to vote and skips his turn (he was denied by employee $ 2 $ ).
4. Employee $ 4 $ denies employee $ 2 $ to vote.
5. Employee $ 5 $ has no right to vote and skips his turn (he was denied by employee $ 1 $ ).
6. Employee $ 1 $ denies employee $ 4 $ .
7. Only employee $ 1 $ now has the right to vote so the voting ends with the victory of depublicans.

## 样例 #1

### 输入

```
5
DDRRR
```

### 输出

```
D
```

## 样例 #2

### 输入

```
6
DDRRRR
```

### 输出

```
R
```

# AI分析结果

### 题目内容
# 投票

## 题目描述
在Alternative Cake Manufacturing (ACM)公司有 $n$ 名员工。他们正在就某个非常重要的问题进行投票，全球主要媒体都在试图预测投票结果。

每位员工都属于两个派别之一：民主共和党（depublicans）或共和民主党（remocrats），这两个派别对投票结果持相反意见。投票程序相当复杂：
1. $n$ 名员工依次发表声明。从员工 $1$ 开始，到员工 $n$ 结束。如果轮到第 $i$ 名员工发表声明时，他已不再拥有投票权，他就跳过自己的轮次（并且不再参与此次投票）。
2. 当员工发表声明时，他可以什么都不做，或者声明剥夺另一名员工的投票权。可以剥夺已经发表过声明的员工或尚未发表声明的员工的投票权。如果有人被剥夺投票权，他将不再参与投票，直至投票结束。
3. 当所有员工都完成声明后，程序重复：再次从 $1$ 到 $n$，让仍然有投票资格的员工发表声明。
4. 这个过程一直重复，直到只剩下一名有投票资格的员工，他将决定整个投票的结果。当然，他会投票支持适合自己派别的决定。

你知道员工投票的顺序，并且知道他们会采取最优策略（他们也知道顺序以及每个人所属的派别）。请预测投票结果。

## 说明/提示
考虑第一个示例的一种投票场景：
1. 员工 $1$ 剥夺员工 $5$ 的投票权。
2. 员工 $2$ 剥夺员工 $3$ 的投票权。
3. 员工 $3$ 没有投票权，跳过他的轮次（他被员工 $2$ 剥夺了投票权）。
4. 员工 $4$ 剥夺员工 $2$ 的投票权。
5. 员工 $5$ 没有投票权，跳过他的轮次（他被员工 $1$ 剥夺了投票权）。
6. 员工 $1$ 剥夺员工 $4$ 的投票权。
7. 现在只有员工 $1$ 有投票权，所以投票以民主共和党（depublicans）的胜利结束。

## 样例 #1
### 输入
```
5
DDRRR
```
### 输出
```
D
```

## 样例 #2
### 输入
```
6
DDRRRR
```
### 输出
```
R
```

### 算法分类
模拟

### 题解综合分析与结论
这些题解主要围绕如何模拟投票过程展开，核心在于处理员工发言、禁言以及判断最终获胜方。不同题解在实现方式上有所差异，有的使用队列，有的通过数组模拟，还有的利用变量记录禁言次数等。大部分题解思路清晰，部分题解在代码简洁性和优化程度上存在提升空间。

### 所选的题解
- **作者：BINYU (赞：4)**
  - **星级**：4星
  - **关键亮点**：清晰梳理题意，通过队列模拟发言过程，并记录两派禁言次数和现存人数来处理禁言情况，逻辑清晰，代码简洁明了。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt,r,d,cntr,cntd;
//r:R党禁言次数，d:D党禁言次数.
//cntr:R党现存多少人，cntd:D党现存多少人
char a;
queue <char> q;//生成队列
int main()
{
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>a;
		q.push(a);
		if(a == 'R')cntr++;//统计R党人数
		else cntd++;//统计D党人数
	}
	while(cntr > 0&&cntd > 0)//判断结束
		if(q.front() == 'D')//D党发言
			if(r >= 1)r--,q.pop(),cntd--;//被禁言
			else d++,q.push(q.front()),q.pop();//未被禁言
		else//R党发言
			if(d >= 1)d--,q.pop(),cntr--;//被禁言
			else r++,q.push(q.front()),q.pop();//未被禁言
	cout<<q.front();
	return 0;//好习惯
}
```
  - **核心思想**：利用队列模拟发言顺序，每次取出队首元素判断所属党派，根据对方党派禁言次数决定该元素是否被禁言，同时更新对应党派现存人数和禁言次数，循环至一方人数为0。

- **作者：李至擎 (赞：1)**
  - **星级**：4星
  - **关键亮点**：详细阐述思路，从不禁言时的发言顺序引入队列的使用，对于禁言操作，通过记录两派禁言次数来模拟，与BINYU思路类似，但解释更细致，代码可读性好。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include<bits/stdc++.h> 
using namespace std;
char opt;//opt是输入字符时的工具 
queue<char>q;//q是用来储存当前发言队列的 
int d,r,n,D,R;//d和r是当前两党各剩下多少个能发言的人，n是初始总人数，D和R是当前两党各还有多少次禁言机会 
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>opt;//输入 
		q.push(opt);//加入发言队列 
		if(opt=='D')d++;//如果是D党，则D党人数+1 
		else r++;//如果是R党，则R党人数+1 	
	}
	while(d&&r)//如果两党都还有剩下的人（还能打起来） 
	{
		char p=q.front();//p是当前发言人 
		q.pop();//用了这次发言机会 
		if(p=='D')//如果此人是D党
		{
			if(R)d--,R--;//如果此时R党还有禁言次数没用，则用掉此次禁言机会，禁言这个D党的人 
			else D++,q.push(p);//反之，则D党获得并保留一次机会，同时将此人加入下一轮发言队列 
		}
		else//如果此人是R党 
		{
			if(D)D--,r--;//如果此时D党还有禁言次数没用，则用掉此次禁言机会，禁言这个R党的人
			else R++,q.push(p);//反之，则R党获得并保留一次机会，同时将此人加入下一轮发言队列 
		}
	}
	if(d)cout<<"D";//如果最后剩下的人是D党，则D党获胜 
	else cout<<"R";//反之，则R党获胜  
	return 0;//结束程序 
}
```
  - **核心思想**：与BINYU题解类似，借助队列模拟发言流程，每次取出队首元素判断党派，依据对方党派禁言次数处理当前元素，更新相关人数和禁言次数，直至一方无人。

- **作者：_Winham_ (赞：1)**
  - **星级**：4星
  - **关键亮点**：通过比较两队最早发言人编号决定谁能禁言对方，用队列存储人员编号，思路新颖且实现简洁，直接模拟出最终获胜方。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
#include<cstdio>
#include<queue>
#include<stack>
#include<deque>
using namespace std;
#define int long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
string s;
int n,a,b; 
queue<int>d,r;
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>n>>s;
	for(int i=0;i<n;i++)
		(s[i]=='D')?d.push(i):r.push(i);
	while(!d.empty()&&!r.empty()){
		a=d.front(),b=r.front();
		d.pop();r.pop();
		if(a>b)r.push(b+n);
		else d.push(a+n);
	}
	cout<<((!d.empty())?"D":"R")<<endl;
	return 0;
}
```
  - **核心思想**：分别用队列存储D党和R党人员编号，每次取出两队队首编号比较，编号小的一方禁言对方队首，存活方编号加上n后重新入队，循环至一方队列为空。

### 最优关键思路或技巧
- **队列的使用**：多数题解采用队列模拟发言顺序，利用队列先进先出的特性，符合题目中员工依次发言且发言后回到队尾等待下一轮的规则。
- **记录禁言次数**：通过记录两派的禁言次数，巧妙解决了在队列操作中难以直接处理禁言特定人员的问题，简化了模拟过程。

### 拓展思路
此类题目属于模拟类问题，关键在于理解复杂规则并准确模拟。类似题目常涉及按特定顺序执行操作、改变状态等，可通过合理选择数据结构（如队列、数组等）优化模拟过程。对于更复杂场景，可能需结合其他算法或数据结构，如链表可方便删除被禁言人员。

### 洛谷相似题目推荐
- [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)：同样是按顺序操作并淘汰元素，最后确定剩余元素，与本题模拟思路类似。
- [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)：通过给定规则对字符串进行变换，需模拟变换过程找到最少变换次数，与本题模拟操作过程有相似之处。
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：在棋盘上按规则移动棋子，模拟棋子移动路径并统计方案数，在模拟具体场景方面与本题类似。 

---
处理用时：79.21秒