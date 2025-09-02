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

# 题解

## 作者：dead_X (赞：3)

## 题意
有一个 Robot,它会用一个长度为 $n$ 的出招序列 $s$ 和你玩 $n$ 局石头剪刀布。它的出招方式为从 $s$ 中随机的一个状态(石头/剪刀/布)开始，依次往下轮一整圈。

你需要设置一个自己的出招顺序，使得**胜利**轮数期望最大。
## 思路
结论:每一次都出克制 $t$ 的状态，其中 $t$ 为 $s$ 中最多的状态。

证明:

对于每一轮单独考虑贡献。

显然每一轮 Robot 会等概率出这个 $s$ 中任意的一个状态。

所以这个结论对于每一轮正确，对于整个游戏过程也正确。
## 代码
```
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
}//QAQ
```

---

## 作者：CQ_Bab (赞：2)

# 思路
这道题其实就只用分类讨论，首先我们知道剪刀是克布的，布是克石头的，石头是克剪刀的。那么我们可以先把剪刀石头和布的数量统计出来后分四种情况讨论：第一种三种数量一样那么输出原始的序列，后三种都是其中一个最大，那么输出克最大的那个的即可。
# AC代码
很简单了呀！
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
		if(a==b&&b==c) { // 四种情况 
			for(int i=0; i<s.size(); i++) cout<<s[i]; // 输出原序列 
			puts("");
		} else {
			int x=max(a,max(b,c)); // 输出克它的 
			if(a==x) out('P');
			else if(b==x) out('R');
			else out('S');
		}
	}
	return 0;
}
```


---

## 作者：szhqwq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1380B)

## 分析

因为我们不知道AI出拳的顺序，所以我们需要从字符串 $s$ 之中分解出各个字符出现的次数，然后要使得你的期望胜利次数最大，我们就要尽可能的去出那个出现次数最多的字符，取一个 $\max$，然后直接输出可以战胜那个字符的字符就可以了。

这里需要注意的是，如果每个字符出现次数都相同，那么，就直接输出字符串 $s$。

[AC 记录](https://www.luogu.com.cn/record/90316203)

AC code

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
	while(n--) { // 多组数据
		int a=0,b=0,c=0;
		cin>>s;
		for(int i=0;i<s.size();i++) { // 统计
			if(s[i]=='R') a++;
			else if(s[i]=='S') b++;
			else c++;
		}
		if(a==b && b==c) for(int i=0;i<s.size();i++) cout<<s[i]; // 特判
		else if(max(a,max(b,c))==a) for(int i=0;i<s.size();i++) cout<<"P";
		else if(max(a,max(b,c))==b) for(int i=0;i<s.size();i++) cout<<"R";
		else if(max(a,max(b,c))==c) for(int i=0;i<s.size();i++) cout<<"S";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：linyihdfj (赞：1)

## B.Universal Solution ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16450318.html)
### 题目描述： ###
[原题面](https://codeforces.com/problemset/problem/1380/B)
### 题目分析： ###
看到这个题第一个反应就是输出对应位置能打败它的那个，但是这样只能保证完全按照给定顺序可以很优，而一旦改变就可能非常差。而还有一种策略就是全部输出能打败最多的手势的手势，这样虽然某些情况不如上面的优，但是整体来看每种排列方式都至少都战胜 $\frac{1}{3}$ 个所以整体的期望更优。
### 代码详解： ###
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt[5];
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(cnt,0,sizeof(cnt));
		string s;
		cin>>s;
		for(int i=0; i<s.size(); i++){
			if(s[i] == 'R'){
				cnt[1]++;
			}
			else if(s[i] == 'S'){
				cnt[2]++;
			}
			else if(s[i] == 'P'){
				cnt[3]++;
			}
		}
		int mx = max(cnt[1],max(cnt[2],cnt[3]));
		if(cnt[1] == mx){
			for(int i=0; i<s.size(); i++){
				printf("P");
			}
		}
		else if(cnt[2] == mx){
			for(int i=0; i<s.size(); i++){
				printf("R");
			}
		}
		else if(cnt[3] == mx){
			for(int i=0; i<s.size(); i++){
				printf("S");
			}
		} 
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：刘健铭 (赞：1)

# Universal Solution

为了使总和最大化，我们需要选择击败最大数量的选择，或者换句话说，让我们找到出现频率最高的字符并选择对应击败它的选择。

思路：用贪心去做，直接先遍历一遍找到数量最多的那个就行。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int ans1=0,ans2=0,ans3=0;
		cin>>s;
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='R') ans1++;
			else if(s[i]=='S') ans2++;
			else ans3++;
		}
		if(ans1>=ans2&&ans1>=ans3)for(int i=0;i<s.size();i++) cout<<"P";
		else if(ans2>=ans1&&ans2>=ans3)for(int i=0;i<s.size();i++) cout<<"R";
		else if(ans3>=ans2&&ans3>=ans1)for(int i=0;i<s.size();i++) cout<<"S";
		/*
		针对对方出的最多的手势，直接出克制对方最多的手势。 
		*/
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：G__G (赞：0)

# [醒目的传送门](https://www.luogu.com.cn/problem/CF1380B)
## 题目描述

- 有一个剪刀石头布的AI，以指定的顺序出手势。但是你并不知道他从这个顺序的哪里开始，所以请给出一个另一个顺序，使得你的期望胜利次数最大。

- R: 石头 S: 剪刀 P:布

- 石头赢剪刀，剪刀赢布，布赢石头

## 求解过程

因为我们不知道AI出拳的顺序，所以我们需要从字符串 s 之中统计每种字母出现的次数，然后要使得你的期望胜利次数最大，我们就要尽可能的去出克制那个出现次数最多的字符，取一个最大值，然后直接输出可以战胜那个字符的字符就可以了。

## [$AC$](https://www.luogu.com.cn/record/91968511)代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        string s; 
        cin>>s;
        int a=0,b=0,c=0,d=s.size();
        for(int i=0;i<s.size();i++){
            if(s[i]=='R'){
            	a++;
			}
            if(s[i]=='S'){
            	b++;
			}
            if(s[i]=='P'){
            	c++;
			}
            if(i==s.size()-1){
                if (a==max(a,max(b,c))){
                    while(d--){
                    	cout<<'P';
					}
                }
                else if (b==max(a,max(b,c))){
                    while(d--){
                    	cout<<'R';
					}
                }
                else if (c==max(a,max(b,c))){
                    while(d--){
                    	cout<<'S';
					}
                }
            }
        }
        cout<<endl;
    }
    return 0;
}
```


---

## 作者：lidundun (赞：0)

# Universal Solution
首先我们研究一下题目，不难看出我们没有必胜的策略，但是可以使胜利的概率最大化。

我们可以研究以下这组样例：`RSPRSPRSPRRR`

最理想的情况就是：`PRSPRSPRSPPP`

但是对方很可能变成：`SPRSPRSPRRRR`

这样你的获胜次数就只有 $3$ 次。但是如果我们全是`P`呢？这样你就可以胜利 $6$ 次。

由此我们可以推算出一个结论：当你试图寻找更优策略时，电脑总有办法让你的策略变得更差，但是如果你给出的答复永远一致，获胜概率反而最大。

为什么是这样呢？首先我们可以设电脑给出的串为 $x$，答复串为 $y$，如果 $y$ 串是全部相同的情况下，那么胜利次数最多为 $x$ 串中出现次数最多的字符的出现次数，既 $k$。

但如果 $y$ 串中有不同字符，我们可以将 $x$ 和 $y$ 串也就可以分成两个部分：前面一段全是相同的，后面不同的。

此时最优情况是电脑没有针对不同字符给出克制的字符，因为电脑可以更改顺序，所以他一定会让后面的字符被克制。此时的最优解不可能大于 $k$。

而前面那段的字符的问题又变成了上一个阶段的问题。

最后，只要统计出电脑最多的手势，然后答复 $n$ 个克制手势就行了。

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans[1000010];
char bz,s[1000010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		memset(ans,0,sizeof(ans));
		cin>>s+1;
		int len=strlen(s+1);
		for(int j=1;j<=len;j++)  ans[s[j]]++;
		if(ans['R']>=ans['S']&&ans['R']>=ans['P'])  bz='P';
		if(ans['S']>=ans['R']&&ans['S']>=ans['P'])  bz='R';
		if(ans['P']>=ans['R']&&ans['P']>=ans['S'])  bz='S';
		for(int j=1;j<=len;j++)  printf("%c",bz);
		printf("\n");
	}
}
```

---

## 作者：Siteyava_145 (赞：0)

**题目：**
- 某AI石头剪刀布软件，按照你输入的顺序出手势，但你不确定它从顺序哪里开始（例如输入 ```RPRPRP```
，可能从第 $2$ 个字符 $P$ 开始，也可能从第 $1$ 个字符 $R$ 开始），让你确定一种方案**保证**能赢的把数最多。

**分析：**

- 题目要求保证胜场最多，就要考虑变换顺序的情况。

- 输入字符串为 ```RSP```，如果假定AI按此方法出手势，那么最优招为 ```PRS```，结果为 $0:3$，但如果AI的顺序是 ```SPR```，那么再用 ```PRS``` 的招数，将会 $3:0$，**爆零，变为更差的结果**，而……
- 还有另外一种可以**保证**胜率的策略！——全出一样的！不过这时，我们还需要验证……

- 如果每一次出的拳都一样，那么即使怎样变换顺序，都不会对结果有任何影响。

- 这样，只要找到AI的顺序里面出现次数最多的手势，再输出能打败他的手势就可以啦（能保证的胜率最高，至少 $33.3\%$）,回过头来看，如果是对于某一特定AI顺序制定策略，虽然这种顺序下可以达到 $100\%$ 的胜率，但如果它变换一下顺序，就一定会让你的某一步的对阵发生变化，从而降低胜率；而此胜率，正好是全出一样时的保证胜率。
 
证明结束~~~
（先把代码贴上）

[神奇的AC](https://www.luogu.com.cn/record/78489148) code：
```
#include<bits/stdc++.h>
using namespace std;
inline int maxx(int a,int b,int c){
    return max(a,max(b,c));
}
int main(){
    int T;
    cin>>T;
    while(T--){
        char c[200005];
        cin>>c;
        int a1=0,a2=0,a3=0,a4=strlen(c);
        for(int i=0;i<strlen(c);i++){
            if(c[i]=='R')a1++;
            if(c[i]=='S')a2++;
            if(c[i]=='P')a3++;
            if(i==strlen(c)-1){
                if (a1==maxx(a1,a2,a3)){
                    while(a4--)cout<<'P';
                }
                else if (a2==maxx(a1,a2,a3)){
                    while(a4--)cout<<'R';
                }
                else if (a3==maxx(a1,a2,a3)){
                    while(a4--)cout<<'S';
                }
            }
        }
        cout<<endl;
    }
}
```

本蒟蒻的第二篇题解啦~~~

---

## 作者：_lgh_ (赞：0)

# 思路：
因为不确定开始的，所以用 $3$ 个变量来分别存储石头、剪刀、布的个数，然后直接全部输出最多的即可。

**证明：**

因为获得最大胜率可以看成每一轮尽量赢对方，又因为不知道出的顺序，那么可以针对对方出的最多的手势，直接出克制对方最多的手势。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
  int T;
  scanf("%d",&T);//输入
  while(T--)
  {
    string s;
    int a=0,b=0,c=0;//三个计数器
    cin>>s;
    for(int i=0; i<s.size(); i++)
    {
    //下面是遍历中计数器的处理
      if(s[i]=='R') a++;
      else if(s[i]=='S') b++;
      else c++;
    }
    int Max=max(a,max(b,c));//直接使用三目运算符，也可以一个一个判断
    if(Max==a) for(int i=1; i<=s.size(); i++) cout<<'P';
    else if(Max==b) for(int i=1; i<=s.size(); i++) cout<<'R';
    else for(int i=1; i<=s.size(); i++) cout<<'S';
    puts("");
  }
  return 0;
}
```


---

## 作者：Allanljx (赞：0)

## 题意
- 有一个剪刀石头布的 $AI$，以指定的顺序出手势。但是你并不知道他从这个顺序的哪里开始，所以请给出一个另一个顺序，使得你的期望胜利次数最大。
- $R:$ 石头；$S:$ 剪刀；$P:$布
- 石头赢剪刀，剪刀赢布，布赢石头

## 思路
我们每次出：克制出现次数最多的那个。这样你可以保证能赢 $ans$ 次（出现次数最多的所出现的次数）。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int sum1=0,sum2=0,sum3=0;
		cin>>s;
		for(int i=0;i<s.length();i++)
		{
			if(s[i]=='R') sum1++;//石头出现的次数
			else if(s[i]=='S') sum2++;//剪刀出现的次数
			else sum3++;//布出现的次数
		}
		if(sum1>=sum2&&sum1>=sum3)//石头最多
			for(int i=0;i<s.length();i++) cout<<"P";
		else if(sum2>=sum1&&sum2>=sum3)//剪刀最多
			for(int i=0;i<s.length();i++) cout<<"R";
		else if(sum3>=sum2&&sum3>=sum1)//布最多
			for(int i=0;i<s.length();i++) cout<<"S";
		cout<<endl;
	}
}
```


---

