# 题目信息

# Universal Solution

## 题目描述

Recently, you found a bot to play "Rock paper scissors" with. Unfortunately, the bot uses quite a simple algorithm to play: he has a string $ s = s_1 s_2 \dots s_{n} $ of length $ n $ where each letter is either R, S or P.

While initializing, the bot is choosing a starting index $ pos $ ( $ 1 \le pos \le n $ ), and then it can play any number of rounds. In the first round, he chooses "Rock", "Scissors" or "Paper" based on the value of $ s_{pos} $ :

- if $ s_{pos} $ is equal to R the bot chooses "Rock";
- if $ s_{pos} $ is equal to S the bot chooses "Scissors";
- if $ s_{pos} $ is equal to P the bot chooses "Paper";

In the second round, the bot's choice is based on the value of $ s_{pos + 1} $ . In the third round — on $ s_{pos + 2} $ and so on. After $ s_n $ the bot returns to $ s_1 $ and continues his game.

You plan to play $ n $ rounds and you've already figured out the string $ s $ but still don't know what is the starting index $ pos $ . But since the bot's tactic is so boring, you've decided to find $ n $ choices to each round to maximize the average number of wins.

In other words, let's suggest your choices are $ c_1 c_2 \dots       c_n $ and if the bot starts from index $ pos $ then you'll win in $ win(pos) $ rounds. Find $ c_1 c_2 \dots c_n $ such that $ \frac{win(1) + win(2) + \dots + win(n)}{n} $ is maximum possible.

## 说明/提示

In the first test case, the bot (wherever it starts) will always choose "Rock", so we can always choose "Paper". So, in any case, we will win all $ n = 4 $ rounds, so the average is also equal to $ 4 $ .

In the second test case:

- if bot will start from $ pos = 1 $ , then $ (s_1,         c_1) $ is draw, $ (s_2, c_2) $ is draw and $ (s_3, c_3) $ is draw, so $ win(1) = 0 $ ;
- if bot will start from $ pos = 2 $ , then $ (s_2, c_1) $ is win, $ (s_3, c_2) $ is win and $ (s_1, c_3) $ is win, so $ win(2) = 3 $ ;
- if bot will start from $ pos = 3 $ , then $ (s_3, c_1) $ is lose, $ (s_1, c_2) $ is lose and $ (s_2, c_3) $ is lose, so $ win(3) = 0 $ ;

 The average is equal to $ \frac{0 + 3 + 0}{3} = 1 $ and it can be proven that it's the maximum possible average. A picture from Wikipedia explaining "Rock paper scissors" game:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1380B/19e6d37b1bc101bbdb7001f87def1e230fc259d2.png)

## 样例 #1

### 输入

```
3
RRRR
RSP
S```

### 输出

```
PPPP
RSP
R```

# AI分析结果

### 题目内容
# 通用解法

## 题目描述
最近，你发现了一个可以一起玩“石头剪刀布”的机器人。不幸的是，这个机器人使用了一种相当简单的算法来进行游戏：它有一个长度为 $n$ 的字符串 $s = s_1 s_2 \dots s_{n}$ ，其中每个字母要么是R（石头），S（剪刀），要么是P（布）。

在初始化时，机器人会选择一个起始索引 $pos$（$1 \le pos \le n$），然后它可以进行任意轮游戏。在第一轮中，它根据 $s_{pos}$ 的值来选择“石头”“剪刀”或“布”：
 - 如果 $s_{pos}$ 等于R，机器人选择“石头”；
 - 如果 $s_{pos}$ 等于S，机器人选择“剪刀”；
 - 如果 $s_{pos}$ 等于P，机器人选择“布”。

在第二轮中，机器人的选择基于 $s_{pos + 1}$ 的值。在第三轮基于 $s_{pos + 2}$ 的值，依此类推。在到达 $s_n$ 之后，机器人会回到 $s_1$ 并继续游戏。

你计划玩 $n$ 轮游戏，并且你已经知道了字符串 $s$，但仍然不知道起始索引 $pos$ 是什么。但是由于机器人的策略非常无聊，你决定找出每一轮的 $n$ 个选择，以最大化平均获胜次数。

换句话说，假设你的选择是 $c_1 c_2 \dots c_n$，如果机器人从索引 $pos$ 开始，那么你将在 $win(pos)$ 轮中获胜。找到 $c_1 c_2 \dots c_n$，使得 $\frac{win(1) + win(2) + \dots + win(n)}{n}$ 尽可能大。

## 说明/提示
在第一个测试用例中，无论机器人从哪里开始，它总是会选择“石头”，所以我们总是可以选择“布”。因此，在任何情况下，我们都将赢得全部 $n = 4$ 轮，所以平均值也等于 $4$。

在第二个测试用例中：
 - 如果机器人从 $pos = 1$ 开始，那么 $(s_1, c_1)$ 是平局，$(s_2, c_2)$ 是平局，$(s_3, c_3)$ 是平局，所以 $win(1) = 0$；
 - 如果机器人从 $pos = 2$ 开始，那么 $(s_2, c_1)$ 是胜利，$(s_3, c_2)$ 是胜利，$(s_1, c_3)$ 是胜利，所以 $win(2) = 3$；
 - 如果机器人从 $pos = 3$ 开始，那么 $(s_3, c_1)$ 是失败，$(s_1, c_2)$ 是失败，$(s_2, c_3)$ 是失败，所以 $win(3) = 0$；

平均值等于 $\frac{0 + 3 + 0}{3} = 1$，并且可以证明这是最大可能的平均值。一张来自维基百科解释“石头剪刀布”游戏的图片：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1380B/19e6d37b1bc101bbdb7001f87def1e230fc259d2.png)

## 样例 #1
### 输入
```
3
RRRR
RSP
S
```
### 输出
```
PPPP
RSP
R
```

### 算法分类
贪心

### 综合分析与结论
所有题解思路基本一致，均基于贪心策略。要点在于通过统计字符串中“R”“S”“P”各自出现的次数，找出出现次数最多的字符，然后每一轮都选择能克制该字符的选择，以此来最大化平均获胜次数。部分题解还考虑了三种字符出现次数相同的特殊情况，此时直接输出原字符串。解决难点在于理解为何这种贪心策略能保证整体平均获胜次数最大，即每一轮机器人等概率出字符串中的任意状态，所以针对出现最多的状态出克制状态，对每一轮及整个游戏过程都正确。

### 题解
 - **作者：dead_X (赞：3)  星级：4星**
    - **关键亮点**：思路清晰，先阐述题意，再给出核心结论并简单证明，代码简洁明了。
    - **重点代码核心思想**：通过`read`函数读取输入，统计字符串中“P”“R”“S”的个数，根据个数比较结果输出对应克制字符。
```cpp
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline long long readll(){
   long long s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
char ch[1000003];
int main()
{
	int T=read();
	while(T--)
	{
		scanf("%s",ch);
		int t=strlen(ch),x=0,y=0,z=0;
		for(int i=0; i<t; i++) if(ch[i]=='P') x++; else if(ch[i]=='R') y++; else z++;
		if(x>y) if(x>z) for(int i=0; i<t; i++) printf("S");
		else for(int i=0; i<t; i++) printf("R");
		else if(y>z) for(int i=0; i<t; i++) printf("P");
		else for(int i=0; i<t; i++) printf("R");
		puts("");
	}
	return 0;
}
```
 - **作者：CQ_Bab (赞：2)  星级：4星**
    - **关键亮点**：对情况进行分类讨论，逻辑清晰，代码通过自定义函数`out`输出结果，结构较清晰。
    - **重点代码核心思想**：读取输入，统计“R”“S”“P”个数，根据三种字符个数关系，分情况输出对应克制字符或原字符串。
```cpp
#include <bits/stdc++.h>
using namespace std ;
int n,a,b,c;
string s;
void out(char c) {
	for(int i=0; i<s.size(); i++) cout<<c;
	puts("");
}
int main() {
	cin>>n;
	while(n--) {
		a=0,b=0,c=0;
		cin>>s;
		for(int i=0; i<s.size(); i++) {
			if(s[i]=='R') a++;
			else if(s[i]=='S') b++;
			else c++;
		}
		if(a==b&&b==c) {
			for(int i=0; i<s.size(); i++) cout<<s[i];
			puts("");
		} else {
			int x=max(a,max(b,c));
			if(a==x) out('P');
			else if(b==x) out('R');
			else out('S');
		}
	}
	return 0;
}
```
 - **作者：szhqwq (赞：1)  星级：4星**
    - **关键亮点**：分析部分清晰说明解题思路，代码使用`max`函数简洁地比较字符出现次数，整体简洁明了。
    - **重点代码核心思想**：读取多组数据，统计字符串中各字符个数，根据个数比较结果输出对应克制字符，特殊情况输出原字符串。
```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N=4;

int n;
string s;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	while(n--) {
		int a=0,b=0,c=0;
		cin>>s;
		for(int i=0;i<s.size();i++) {
			if(s[i]=='R') a++;
			else if(s[i]=='S') b++;
			else c++;
		}
		if(a==b && b==c) for(int i=0;i<s.size();i++) cout<<s[i];
		else if(max(a,max(b,c))==a) for(int i=0;i<s.size();i++) cout<<"P";
		else if(max(a,max(b,c))==b) for(int i=0;i<s.size();i++) cout<<"R";
		else if(max(a,max(b,c))==c) for(int i=0;i<s.size();i++) cout<<"S";
		cout<<endl;
	}
	return 0;
}
```

### 最优关键思路或技巧
贪心策略的运用，通过分析每轮机器人出拳的等概率性，得出针对出现次数最多的出拳选择克制拳，能最大化整体平均获胜次数。

### 拓展
同类型题通常围绕博弈场景，在不确定性条件下通过分析概率、状态等因素，运用贪心或其他策略寻找最优解。例如一些游戏策略制定、资源分配类题目，在面对多种选择和未知起始条件时，通过合理的策略制定来达到最优目标。

### 相似知识点洛谷题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据进行分析，利用贪心策略解决分配问题。
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及博弈场景，需分析双方策略，运用贪心思想找到最优解。
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：同样是基于贪心策略，对数据进行排序和分析以解决问题。 

---
处理用时：84.47秒