# Card Game

## 题目描述

一种纸牌游戏。
有许多张卡牌，每张卡牌有一个套装（“S”，“H”，“D”和“C”）和一个等级（按升序排列“6”，“7”，“8”，“9”，“T”， “J”，“Q”，“K”和“A”）
**规则：**
以下情况卡牌A才能赢卡牌B:
1、A有王牌套装，B没有
2、A和B的套装相同，但A的等级比B高
否则B赢

## 样例 #1

### 输入

```
H
QH 9S
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
S
8D 6D
```

### 输出

```
YES```

## 样例 #3

### 输入

```
C
7H AS
```

### 输出

```
NO```

# 题解

## 作者：LuffyLuo (赞：3)

### 题目解析
Card Game 的题目分析：

意思是 A，B 组合卡牌中各有等级卡牌以及套装卡牌（说实话这套装卡牌几乎没有什么用），然后是两种情况算 A 赢，其他情况算 B 赢：

* 若 A 的套装卡牌是必胜卡牌（即随便在套装卡牌中选出），而且 B 没有，那么 A 胜利。

* 若 A 与 B 都未有必胜卡牌，那么若 A 与 B 的套装卡牌都是相同的，而且 A 的等级卡牌大于 B 的等级卡牌，那么 A 胜利。

### 题目思路：
思路简单，用分支结构诉说出我上面的情况就可以。

### 题目代码：
我想代码应该不需要我多说明了：

```
#include<bits/stdc++.h>
using namespace std;
char s[10]{'6','7','8','9','T','J','Q','K','A'};
int main(){
	char winning_card,Arank,Brank,Acard,Bcard;int Aranksum,Branksum,i;
	cin>>winning_card;
	cin>>Arank>>Acard;
	cin>>Brank>>Bcard;
	for(i=0;i<=8;i++)
		if(s[i]==Arank){
			Aranksum=i;
			break;
		} 
	for(i=0;i<=8;i++)
		if(s[i]==Brank){
			Branksum=i;
			break;
		} 
	if(Acard==winning_card&&Bcard!=winning_card||Acard!=winning_card&&Bcard!=winning_card&&Acard==Bcard&&Aranksum>Branksum) printf("YES\n");
	else printf("NO\n");
	return 0;
}
```

//不用说谢谢，不因客套，只因能见您的笑容，以及您电脑上的 AC，您已经回报。

//祝大家信息学越来越棒哦！

---

## 作者：alm_crax (赞：1)

## 题目[传送门](https://www.luogu.com.cn/problem/CF106A)
### 1. 题目大意：

现有 A 和 B 的套装和套装等级，和王牌套装，判断 A 能不能获胜。

### 2. 获胜条件：
- 若 A 的套装是王牌套装，且 B 的套装不是王牌套装，则 A 获胜。

- 若 A 的套装与B的套装相同，且 A 的套装等级大于 B 的套装等级，则 A 获胜。

- 其余情况 A 输。
## 思路

根据获胜条件判断两种获胜情况，若都不符合输出“NO”。

## 代码

（代码含有注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
char wangpai;//王牌套装 
char dengji[10]={'6','7','8','9','T','J','Q','K','A'};//等级 
string a,b;//A和B的套装
int main()
{
	cin>>wangpai;
	cin>>a>>b;
	if(a[1]==wangpai&&b[1]!=wangpai)//判断情况1
	{
		cout<<"YES";
	}
	else if(a[1]==b[1])//判断情况2
	{
		for(int i=0;i<9;i++)//枚举等级 
		{
			if(dengji[i]==a[0])//先匹配到A的等级 
			{
				cout<<"NO";
				break;
			}
			if(dengji[i]==b[0])//先匹配到B的等级 
			{
				cout<<"YES";
				break;
			}
		}
	}
	else//情况1和2都不符合 
	{
		cout<<"NO";
	}
    return 0;
}
```
本人第一篇题解，如有不足，还请见谅。

---

## 作者：精神小伙！ (赞：1)

## 思路

首先判断是不是王牌套装，分以下两种情况：

- A 是王牌套装并且 B 不是，A 胜利。

- B 是王牌套装并且 A 不是，B 胜利。

接下来开始比较。如果套装不相等就查找套装，看看谁的套装大谁赢。

如果套装相等就找等级，看看谁的等级大谁赢。

比较时可以采用打表的方法。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
char king,A_lv,A_suit,B_lv,B_suit;
//king表示王牌套装,lv表示等级,suit表示套装 
char s1[]={'6','7','8','9','T','J','Q','K','A'};
//打表-表示每个字母的等级 
char s2[]={'S','H','D','C'};
int main()
{
	cin>>king;
	cin>>A_lv>>A_suit;
	cin>>B_lv>>B_suit;
	if(king==A_suit&&king!=B_suit) //如果A有王牌套装并且B没有A肯定获胜 
	{cout<<"YES"<<endl;return 0;}
	if(king==B_suit&&king!=A_suit) //反之，如果B有而A没有，则A输 
	{cout<<"NO"<<endl;return 0;}
	if(A_suit==B_suit)//如果套装一样就找等级 
	{
		int A_ans=0,B_ans=0;
		for(int i=0;i<9;++i)
		{
	    	if(s1[i]==A_lv) A_ans=i;
			if(s1[i]==B_lv) B_ans=i;	
			//分别找出A和B的等级 
		}
		if(A_ans>B_ans) cout<<"YES"<<endl;
		else            cout<<"NO"<<endl;//比较 
		return 0;
	}
	else      //否则比谁的套装大 
	{
		int A_ans=0,B_ans=0;
		for(int i=0;i<5;++i)
		{
	    	if(s1[i]==A_suit) A_ans=i;
			if(s1[i]==B_suit) B_ans=i;	
			//分别找出A和B的套装 
		}
		if(A_ans>B_ans) cout<<"YES"<<endl;
		else            cout<<"NO"<<endl;//比较 
		return 0;
	}
	return 0;
}
```

---

## 作者：我和鱼过不去 (赞：1)

### 题目大意
每张卡牌有一个套装和一个等级（第一个字母为卡牌的等级、第二个字母为卡牌的套装）。
规定以下情况卡牌 A 赢过卡牌 B：

+ 卡牌 A 有王牌套装，而卡牌 B 没有；
+ 卡牌 A 与卡牌 B 的套装相同，但是卡牌 A 的等级高过卡牌 B 的等级。  

题目将给出王牌套装和卡牌A、B，判断卡牌 A 是否能赢过卡牌 B。

### 思路
用 ```map``` 映射卡牌的等级，再 if 判断一下就可以了。

这里简单介绍一下 ```map``` 。  
```map``` 本质上就像一个数组，  
只不过你可以自己定义键和值 ~~（其实就是下标与它所对应的元素）~~ 类型。
```cpp
map<string,int> mp;  
```
这样你就有了一个可以用 string 类型映射到 int 类型的 ```map``` 数组 $mp$ 。
```cpp
mp["hello"] = 532;
```
这意味着在 $mp$ 数组里，
$\mathtt{"hello"}$ 对应着 $\mathtt{532}$
。
```cpp
mp.count("hello");
mp.count("world");
```
判断该元素之前是否存在映射。
返回值分别为 $\mathtt{1}$ 和 $\mathtt{0}$。  
```cpp
#include<bits/stdc++.h>
using namespace std;
string king,a,b;
map<char,int>grade;   //map数组 
int main()
{
    cin>>king>>a>>b;
    //手动建立映射 
    grade['6'] = 1;	
    grade['7'] = 2;
    grade['8'] = 3;
    grade['9'] = 4;
    grade['T'] = 5;
    grade['J'] = 6;
    grade['Q'] = 7;
    grade['K'] = 8;
    grade['A'] = 9;
    if(a.find(king)==true&&b.find(king)!=true)   //如果卡牌A有王牌套装而卡牌B没有 
    {
        cout<<"YES"<<endl;
    }
    else if(a[1]==b[1]&&grade[a[0]]>grade[b[0]])   //如果套装相同，判断等级 
    {
        cout<<"YES"<<endl;
    }
    else      //其余情况都是卡牌B赢 
    {
        cout<<"NO"<<endl;
    }
    return 0 ;
}
```


---

## 作者：TsH_GD (赞：0)

模拟水题好吧。

### 题意简化

给出王牌卡牌和 A、B 两个组合，求 A 是否能赢。

## 胜利条件

1. A 有王牌套装 B 没有。
2. A 和 B 的套装相同，但 A 的等级比 B 高。

除了这两种条件其余都是 B 赢。

**注意： 即使 A、B 两个组合完全相同也算 B 赢。**

### 解决

使用`map`数组记录。

```cpp
#include<string>
#include<iostream>
#include<map>
using namespace std;
string king,A,B;
map<char,int>point;
int main(){
	point['6']=1;point['7']=2;point['8']=3;point['9']=4;point['T']=5;point['J']=6;point['Q']=7;point['K']=8;point['A']=9;
	cin>>king>>A>>B;
    if(A[1]==king[0]&&B[1]!=king[0]||A[1]==B[1]&&point[A[0]]>point[B[0]]) puts("YES");
    else puts("NO");
}
```

---

## 作者：billzd (赞：0)

首先我们知道，$A$ 要想赢下 $B$ 只有两种可能：

1. $A$ 有王牌套装，$B$ 没有。
1. $A$ 和 $B$ 的套装相同，但 $A$ 的等级比 $B$ 高。

**其余情况都是 $B$ 赢。**

那么用代码实现就很简单了，判断 $A$ 能不能赢。

由于字符串只有两个字符，所以找到下标直接比较即可,另一个 $A$ 赢的情况用 $C++$ 的 $map$ 存值，再进行比较就可以得到结果。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string king,A,B;
map<char,int>lg;
int main(){
	cin>>king>>A>>B;
	lg['6'] = 1;//存值。
	lg['7'] = 2;
	lg['8'] = 3;
	lg['9'] = 4;
	lg['T'] = 5;
	lg['J'] = 6;
	lg['Q'] = 7;
	lg['K'] = 8;
	lg['A'] = 9;
    if(A[1]==king[0]&&B[1]!=king[0]||A[1]==B[1]&&lg[A[0]]>lg[B[0]])
    	puts("YES");//判A是否赢了。
    else
    	puts("NO");//B赢了。
	return 0;//华丽的结束。
}
```


---

## 作者：Allanljx (赞：0)

## 题意
有两套卡牌，每套卡牌有一个等级和一个卡，另外还有一个王牌卡。当第一套卡牌有这个王牌卡且第二套没有时 $A$ 胜，第一套和第二套的卡相同且第一套的等级要大于第二套时也是 $A$ 胜，否则 $B$ 胜。

## 思路
用 $a[0]$ 数组记录A的等级、用 $a[1]$ 数组记录B的等级
然后判断两个条件

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int a[101];
signed main()
{
	string s1,s2;
	getline(cin,s1);
	getline(cin,s2);
	//判断等级 
	if(s2[0]=='T') a[0]=11;
	if(s2[0]=='J') a[0]=12;
	if(s2[0]=='Q') a[0]=13;
	if(s2[0]=='K') a[0]=14;
	if(s2[0]=='A') a[0]=15;
	if(s2[3]=='T') a[1]=11;
	if(s2[3]=='J') a[1]=12;
	if(s2[3]=='Q') a[1]=13;
	if(s2[3]=='K') a[1]=14;
	if(s2[3]=='A') a[1]=15;
	if(s2[0]>='6'&&s2[0]<='9') a[0]=(int)(s2[0]-'0');
	if(s2[3]>='6'&&s2[3]<='9') a[1]=(int)(s2[3]-'0');
	//A有王牌卡而B没有 
	if(s2[1]==s1[0]&&s2[4]!=s1[0])
	{
		cout<<"YES\n";return 0;
	}
	//A、B都有同一张卡且A的等级比B高 
	if(s2[1]==s2[4]&&a[0]>a[1])
	{
		cout<<"YES\n";return 0;
	}
	cout<<"NO\n";
    return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
一种纸牌游戏有许多张卡牌，每张卡牌有一个套装（`S`，`H`，`D`和 `C`）和一个等级（按升序排列`6`，`7`，`8`，`9`，`T`， `J`，`Q`，`K`，`A`）。 规定以下情况卡牌 A 才能赢卡牌 B: 

- A 有王牌套装，B 没有。
- A 和 B 的套装相同，但 A 的等级比 B 高。

否则 B 赢。

现在，给出王牌套装和卡牌 A、卡牌 B，问卡牌 A 是否能赢卡牌 B。

**数据范围：保证输入合法。**
## Solution
我们先按照题目所给的顺序求出卡牌 A 和卡牌 B 的等级，不妨设 T 为 10，J 为 11，Q 为 12，K 为 13，A 为 14，其他照旧。然后就是一波 if-else 判断了。

先判断 A 是否有王牌套装，如果 A 有，判断 B 是否有。如果 B 没有那就 A 赢，如果 B 也有而 A 的等级比 B 大，那么还是 A 赢，否则 B 赢。

如果 A 没有王牌套装，那么判断 B 是否有，如果 B 有那就 B 赢；否则看它们两张卡牌是否是同一个套装。**如果不是同一个套装则 B 赢**（这里特别注意！），是同一个套装就比较它们的等级。如果 A 的等级比 B 大，那么 A 赢，否则 B 赢。
## Code
```cpp
string king, a, b;

int main() {
	cin >> king >> a >> b;
	int a1 = (a[0] == 'T' ? 10 : (a[0] == 'J' ? 11 : (a[0] == 'Q' ? 12 : (a[0] == 'K' ? 13 : (a[0] == 'A' ? 14 : a[0] - '0'))))), b1 = (b[0] == 'T' ? 10 : (b[0] == 'J' ? 11 : (b[0] == 'Q' ? 12 : (b[0] == 'K' ? 13 : (b[0] == 'A' ? 14 : b[0] - '0')))));
	if(king[0] == a[1]) {
		if(king[0] == b[1]) {
			if(a1 > b1) puts("YES");
			else puts("NO");
		} else puts("YES");
	} else {
		if(king[0] == b[1]) puts("NO");
		else if(a[1] == b[1]) {
			if(a1 > b1) puts("YES");
			else puts("NO");
		} else puts("NO");
	}
	return 0;
}
```

---

## 作者：世末OIer (赞：0)

按照题目大意来就是了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int rank[128];
	rank['6']=0; rank['7']=1; rank['8']=2; rank['9']=3; rank['T']=4;
	rank['J']=5; rank['Q']=6; rank['K']=7; rank['A']=8;   //将大小关系转化成数字
	char c,a[3],b[3]; scanf("%c%s%s",&c,a,b);
	puts(a[1]==c&&b[1]!=c || a[1]==b[1]&&rank[a[0]]>rank[b[0]] ?  "YES" : "NO");   //比较
	return 0;
}
```

---

