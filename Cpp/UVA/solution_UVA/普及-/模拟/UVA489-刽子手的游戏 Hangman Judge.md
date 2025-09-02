# 刽子手的游戏 Hangman Judge

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=430

[PDF](https://uva.onlinejudge.org/external/4/p489.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA489/5235bc315d8684bc30728d37f52e7f53bcd8dccb.png)

## 样例 #1

### 输入

```
1
cheese
chese
2
cheese
abcdefg
3
cheese
abcdefgij
-1```

### 输出

```
Round 1
You win.
Round 2
You chickened out.
Round 3
You lose.```

# 题解

## 作者：blackfrog (赞：32)

## 大家好~欢迎来到我的题解
安利博客先：[blog](https://www.luogu.org/blog/blackfrog/)

当我看到题目的时候，就暗暗想:这绝对是一道模拟题。  
但是在模拟的过程当中，也有一些小技巧能让你的代码更加优美，**儒雅随和**。

在这里，来讲一下这道题目的几个小技巧/小知识点：
### 关于输入输出
这道题的输入输出，对于一些小牛来说可能是一种比较特殊的输入输出，即碰到一个特定的值停止。其实，这不需要考虑太多。因为在c++里，我们完全可以这么写：
```cpp
while(cin>>order/*order是游戏编号*/){
    if(!~order){
        break;
    }
}
```
可能有些人会看不懂这么精简的代码，那我就来精讲一下：
- 关于while语句大家可能不知道的是里面也可以塞cin语句，不过你只要while里面有个break就保证可以终止输入
- 什么是~符号？~是位运算的符号，表示取反（在二进制位中0转1,1转0）,而-1这个数的反码正好就是0，所以我们可以用~变量名 来表示它不是-1.
关于输出你可能不知道的是，输出之后再继续输出是完全可以的，所以你不需要把输出存起来，等输入完了再输出。

### 关于判断函数
你无需跟我写的一样，但是我为了代码的**儒雅随和**，特地写了一个判断游戏结果的函数-wacnt（wrong answers count）

分析：  
我们的输出结果是根据2个指标来定的，一个是是否猜完所有字母，一个是机会是否用光。  
这一段我写的比较奇葩：
```cpp
int wacnt(string s1,string s2){
    int str[128];
    int wacnt;
    for(int i = 0;i<s1.size();i++){
        str[s1[i]] =1;
    }
    for(int i = 0;i<s2.size();i++){
        if(!str[s2[i]])wacnt++;
        else{
            if(str[s2[i]]!=1)wacnt++;
            str[s2[i]]++;
        }
    }
}
```
*核心思想*，也是你之后刷题经常要用到的思想（敲黑板划重点）：
用数组来存储，每一个数组的下标对应的是字母对应的$ASCII$码，一共128个。
那么这个数组的处理方式非常巧妙（我就是因为这个写的题解）：  
1. 在正确答案中，先把一部分字母对应值从0改成1。
2. 验证玩家的答案。分几种情况讨论。
- 值为0.错误次数++。
- 值为1.不加错误次数，将值改为2，表示已经访问过此值。
- 值为2.已经访问过此值，错误次数++。
至此，机会是否用光我们已经用这个wacnt来确定了。

那么，是否猜完所有字母怎么来写呢？
这里我想的十分奇葩，因为是否猜完所有字母，它肯定是一个bool值，要么0，要么1，我们就把错误次数\*2，然后用wacnt的奇偶性来表示是否猜完所有字母。代码如下：
```cpp
wacnt*=2;
for(int i = 0;i<s1.size();i++){
    if(str[s1[i]]==1){
        wacnt++;
        break;
    }
}
return wacnt;
```
出现1时，说明这是一个正确答案，并且没有被访问过（访问过就是2了），所以字母没有被猜完。  
好了，这就是所有的一些注意点和小技巧，完整代码如下：  
```cpp
#include<string>
#include<iostream>
using namespace std;
int order;
int wacnt(string s1,string s2){
    int str[128];
    int wacnt;
    for(int i = 0;i<s1.size();i++){
        str[s1[i]] =1;
    }
    for(int i = 0;i<s2.size();i++){
        if(!str[s2[i]])wacnt++;
        else{
            if(str[s2[i]]!=1)wacnt++;
            str[s2[i]]++;
        }
    }
    wacnt*=2;
    for(int i = 0;i<s1.size();i++){
        if(str[s1[i]]==1){
            wacnt++;
            break;
        }
    }
    return wacnt;
}

int main(){
    while(1){
        cin>>order;
        if(!~order){
            break;
        }
        cout<<"Round "<<order<<endl;
        string a,b;
        cin>>a>>b;
        if(wacnt(a,b)/2>6){
            cout<<"You lose."<<endl;
            continue;
        }
        else if(wacnt(a,b)%2==1){
            cout<<"You chickened out."<<endl;
        }
        else{
            cout<<"You win."<<endl;
        }
    }
    return 0;
}
```

##如果喜欢本篇题解，别忘记点个赞哦~QWQ

---

## 作者：PC_DOS (赞：6)

这是一道字符串模拟题，我们只需要遍历猜测的串，将其中的每一个字符在答案串之中搜索一遍，确定是否存在于答案串之中即可。

注意，由于重复猜为错，因此每一次校验猜测的字符时都应将答案串从头到尾遍历一遍并在猜对的情况下将对应位置的字符标识为不可能猜到的字符(比如空格)。同时由于存在弃权的情况，应该同时对胜利和失败做出标识。

代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
int GetGuessResult(string &sAnswer, char chrGuess){ //判断猜测的字符chrGuess是否在答案串sAnswer之中出现的函数，返回值为猜中的次数(即sAnswer中有多少个字符和chrGuess相同)
	int i,nRight=0; //i-循环计数器；nRight-猜中次数(即sAnswer中有多少个字符和chrGuess相同)
	for (i = 0; i < sAnswer.length(); ++i){ //遍历答案串
		if (sAnswer[i] == chrGuess){ //如果发现相同
			++nRight; //猜中次数加一
			sAnswer[i] = ' '; //将对应位置标识为非可猜字符
		}
	}
	return nRight; //返回猜中次数
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sAnswer, sGuess; //sAnswer-答案串；sGuess-猜测串
	int i, iLenAnswer, iLenGuess, iRoundIndex, nChance, nLeft, iGuessResult; //i-循环计数器；iLenAnswer、iLenGuess-答案串和猜测串的长度；iRoundIndex-回合数；nChance-剩余的次数；nLeft-尚未被猜到的字符数；iGuessResult-存放每一次猜测的结果(即GetGuessResult的返回值)
	bool IsWin, IsLose; //存放胜负结果
	cin >> iRoundIndex; //输入回合数
	while (iRoundIndex != -1){ //回合数非-1时
		cin >> sAnswer >> sGuess; //输入答案和猜测
		iLenAnswer = sAnswer.length(); //计算答案串长度
		iLenGuess = sGuess.length(); //计算猜测串长度
		nLeft = iLenAnswer; //记录剩余字符数
		nChance = 7; //初始化剩余机会为7
		IsWin = false;
		IsLose = false; //不输也不赢
		for (i = 0; i < iLenGuess; ++i){ //遍历答案串
			iGuessResult = GetGuessResult(sAnswer, sGuess[i]); //获得本轮猜测结果
			if (iGuessResult > 0){ //如果有猜到
				nLeft -= iGuessResult; //剩余字符数减去猜中次数(由于计算剩余字符数时没有考虑相同的字符，因此要减去猜中次数而不是固定值)
			}
			else{ //没有猜到
				--nChance; //机会次数减一
			}
			if (nLeft == 0){ //如果所有字符都被猜中
				IsWin = true; //胜利
				break; //结束循环
			}
			else if (nChance == 0){ //如果已经没有机会了
				IsLose = true; //失败
				break; //结束循环
			}
		}
		cout << "Round " << iRoundIndex << endl; //输出标头(回合数)
		if (IsWin){ //如果胜利
			cout << "You win.\n"; //提示
		}
		else if (IsLose){ //如果失败
			cout << "You lose.\n"; //提示
		}
		else{ //否则为弃权
			cout << "You chickened out.\n"; //提示
		}
		cin >> iRoundIndex; //读入下一个回合数
	}
	return 0; //结束
}
```

---

## 作者：Jiang_zi_chuan (赞：6)

# 本题解来自算法竞赛-入门经典！！！

代码：

```cpp
#include <stdio.h>
#include <string.h>
#define maxn 100
int left, chance;           //还需要猜left这个位置，错chance次之后就会输
char s[maxn], s2[maxn];     //答案是字符串s，玩家猜的字母序列是s2
int win, lose;              //win=1表示已经赢了；lose=1表示是已经输了

void guess(char ch) {
	int bad = 1;
	for (int i = 0; i < strlen(s); i++) 
		if (s[i] == ch) { left--; s[i] = ' '; bad = 0; }
	if (bad) --chance;
	if (!chance) lose = 1;
	if (!left) win = 1;
}

int main() {
	int rnd;
	while (scanf("%d%s%s", &rnd, s, s2) = 3 && rnd != -1) {
		printf("Round %d\n", rnd);
		win = lose = 0;
		left = strlen(s);
		chance = 7;
		for (int i = 0; i < strlen(s2); i++) {
			guess(s2[i]);                   //猜一个字母
			if (win || lose) break;         //检查状态
		}
		//根据结果进行输出
		if (win) printf("You win.\n");
		else if (lose) printf("You lose.\n");
		else printf("You chickened out\n");
	}
}
```

---

## 作者：1446435502l (赞：2)

一开始理解错题意了……wa了好久

其实我们不用这么复杂，一步一步去模拟。观察一下，每猜中一个字母都会把所有字母给显示出来，那么我们可不可以把问题转化为，计算机给出的单词中有多少种不同的字母，而猜的序列中又有没有这些字母并满足题目要求）
所以我们的任务就是检索一遍猜的序列，看有没有计算机给出的单词的字母。有的话就统计起来（用num代替），计算机给出的字母用sum代替，如果最后sum==num，那就证明任务完成，可以结束了。当sum！=num且wa（猜错的次数）<7时，我们就认为他是没有完成任务的（可以自己想想）。这个题目有一个坑点，就是当你已经完成任务是，后面还有一大堆错的时候例如：
- a
- jefihaiefj 


这样的数据，你也得输出win。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int n,wa,ji[10005],num,sum;//ji数组是统计有没有重复猜某些字母 
char s1[10005],s2[10005];
bool z1[10005],z2[10005],flag,tong;//z1就是计算机给出了哪些字母，z2就是你猜了哪些字母 
int main()
{
	//freopen("123.txt","w",stdout);
S1:	while(scanf("%d",&n)&&n!=-1)
	{
		sum=num=0;
		wa=0;
		printf("Round %d\n",n);
		memset(s1,0,sizeof(s1));
		memset(z1,false,sizeof(z1));
		memset(z2,false,sizeof(z2));
		memset(ji,0,sizeof(ji));
		flag=true;
		memset(s2,0,sizeof(s2));
		scanf("%s%s",s1+1,s2+1);
		for(int i=1;i<=strlen(s1+1);i++)
		{
			if(z1[s1[i]-'a'+1]==false)sum++;
			z1[s1[i]-'a'+1]=true;
		}
		for(int i=1;i<=strlen(s2+1);i++)//无论猜没猜对都要统计已经猜过的字母哦 
		{
			if(wa>=7)break;//wa>=7就已经可以结束了 
			if(ji[s2[i]-'a'+1]!=0)
			{
				wa++;
				continue;
			}
			if(z1[s2[i]-'a'+1])//如果猜的序列出现过某些字母，就统计下来吧 
			{
				ji[s2[i]-'a'+1]++;
				num++;
			}
			else
			{
				ji[s2[i]-'a'+1]++;
				wa++;
			}
		if(sum==num)//这里就是我前面说的要注意的点，每一步检索都要判断一次，防止踩陷阱 
		{
			printf("You win.\n");
			goto S1;
		}
		}
		if(sum!=num&&wa<7)printf("You chickened out.\n");
		else
		{
			if(wa>=7)
			{
				printf("You lose.\n");
			}
			else
			{
				printf("You win.\n");
			}
		}
	}
} 
```


---

## 作者：MrFish (赞：1)

### 一道模拟题
### 直接看代码

先安利一下博客：[blog](https://www.luogu.com.cn/blog/ArthurYu/)


```cpp
#include<iostream>
#include<cstring> 

using namespace std;

bool win=false,lose=false;  //赢或输

bool include(string a,string b,int i)  //判断b[i]是否在a里面
{
	for(int j=0;j<a.size();j++)
	{
		if(a[j]==b[i])
		{
			return true;
		}
	}
	return false;
}

void chk(string right,string guess)  //重点！！！
{
	int wa=0;//猜错的
	string guessed;  //猜对了的数字
	bool gur[right.size()]={false};  //猜对了
	for(int i=0;i<guess.size();i++)
	{
		bool ri=false;
		for(int j=0;j<right.size();j++)
		{
			if(!ri&&right[j]==guess[i]&&!include(guessed,guess,i)) //判断
			{
				guessed+=guess[i];
				ri=true;
				gur[j]=true;
			}
			if(ri&&right[j]==guess[i])
			{
				gur[j]=true;
			}  
		}
		if(!ri)
		{
			wa++;
		}  //猜错了
		if(wa>=7)
		{
			lose=true;
			return;
		}
		bool chkwin=true;
		for(int j=0;j<right.size();j++)
		{
			if(gur[j]!=true)
			{
				chkwin=false;
			}
		}  //是否全都猜出来了
		if(chkwin)
		{
			win=true;
			return;
		}
	}
	return;
}

int main()
{
	int n;
	string right,guess;
	while(cin>>n) //输入
	{
		if(n==-1)
		{
			break;
		}
		cin>>right>>guess;
		cout<<"Round"<<' '<<n<<endl;
		win=false;
		lose=false;
		chk(right,guess);
		if(win)
		{
			cout<<"You win."<<endl;
		}
		else
		{
			if(lose)
			{
				cout<<"You lose."<<endl;
			}
			else
			{
				cout<<"You chickened out."<<endl;
			}
		}
	}
	return 0;
}

```
## AC 100!!!


---

## 作者：封禁用户 (赞：1)

几篇题解里都没有用~~红黑树~~set做的，那就发一篇题解吧。


**首先说一下这道题我为什么想到用set。**

~~1.STL重度依赖症~~

1.题目中明确说明，“如果单词里有那个字母，所有该字母会显示出来”，也就意味着某个字母不管出现多少次，其效果和出现一次是没有区别的。这符合set排斥重复元素的特征。

2.根据题意，我们需要判断用户猜测的字符是否在计算机的字符串里面出现过，set对象的成员函数count()刚好可以满♂足我们。

3.不能猜测已经猜过的字符。set对象的成员函数erase()又一次满♂足了我们。具体来说，就是猜到某个字符之后就把它从set里面删掉，这样下次查询时就不会查到它，则按错误处理（妙啊）。

4.树形结构与字符串结合紧密，容易想到（Trie：为啥不是我）


**STL的内容还有一个好处，就是操作简便以至于有点傻瓜，基本上用STL模板做的题都是出了思路直接码，爽的一批**

~~（这也成为代码可以不写注释的理由）~~

放代码

```cpp
#include <iostream>
#include <set>
#include <string>

using namespace std;

set<char> s;
string str;
int r, cnt;

int main(void)
{
	cin >> r;
	while (r != -1)
	{
		cin >> str;
		s.clear(), cnt = 0;		//记得重置一下！
		cout << "Round " << r << endl;
		for (auto i : str)
		{
			s.insert(i);
		}
		cin >> str;
		for (auto i : str)
		{
			if (s.count(i))
			{
				s.erase(i);
				if (s.empty())
				{
					cout << "You win." << endl;
					goto END;
				}
			}
			else
			{
				if (++cnt == 7)
				{
					cout << "You lose." << endl;
					goto END;
				}
			}
		}
		cout << "You chickened out." << endl;
	END:;
		cin >> r;
	}
	//system("pause");
	return 0;
}

```


---

## 作者：chino123 (赞：1)

这是一道字符串模拟的题目，我们只需要将系统生成的单词和玩家猜的单词跑一遍，再做好标记，就可以确定答案。
统计各字符串中字母出现与否，用bool值标记进行模拟。
猜词过程中满足win条件时要提前break(不然会WA)。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char kafuu[10000],chino[10000];
bool non[26];
int main()
{
	int n;
	while(cin>>n){
		if(n==-1)break;
        //个人习惯做字符串题先memset一遍
		memset(kafuu,'\0',sizeof(kafuu));
		memset(chino,'\0',sizeof(chino));
		memset(non,false,sizeof(non));
		cin>>kafuu;
		cin>>chino;
		int len1=strlen(kafuu),len2=strlen(chino);
		int sum=0;//统计生成字符串中字母个数。
		for(int i=0;i<len1;i++){
			if(non[kafuu[i]-'a']==false){
			non[kafuu[i]-'a']=true;
			sum++;
			}
		}
		int tot=0;//容错
		for(int i=0;i<len2;i++){
			if(!sum)break;//当完成win条件时break
			if(non[chino[i]-'a']){
			sum--;
			non[chino[i]-'a']=false;
			}
			else tot++;
		}
		cout<<"Round "<<n<<endl;
		if(tot>6) puts("You lose.");
		else if(sum) puts("You chickened out.");
		else puts("You win.");	
	} 
}

```
首先，开两个数组~~智乃最棒啦~~，和一个标记数组non。
然后数组初始化。
声明一个sum用来统计生成串的字母种数。non[26]中0-25表示a-z，遍历生成串给non注入灵魂。

再声明一个变量tot，统计错误数量。
每次匹配到一个true值，将true转成false，然后计数，并且保证重复字母只统计一次且多次重复判断为错误。
完成win条件(sum==0)时break;避免后续串重复项影响结果。
最后根据tot和sum的值依次给出结果。tot优先判断。其次是sum。最后得出结论。

---

