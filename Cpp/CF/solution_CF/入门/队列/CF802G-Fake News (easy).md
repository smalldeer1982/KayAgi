# Fake News (easy)

## 题目描述

As it's the first of April, Heidi is suspecting that the news she reads today are fake, and she does not want to look silly in front of all the contestants. She knows that a newspiece is fake if it contains heidi as a subsequence. Help Heidi assess whether the given piece is true, but please be discreet about it...

## 说明/提示

A string $ s $ contains another string $ p $ as a subsequence if it is possible to delete some characters from $ s $ and obtain $ p $ .

## 样例 #1

### 输入

```
abcheaibcdi
```

### 输出

```
YES```

## 样例 #2

### 输入

```
hiedi
```

### 输出

```
NO```

# 题解

## 作者：char32_t (赞：9)

# 题解 CF802G 【Fake News (easy)】

------------

提示：此题与[CF58A 【Chat room】](https://www.luogu.org/problemnew/show/CF58A)几乎完全相同


题目大意：在一个序列中判断它是否包含子序列**"heidi"**


那么我们可以将"h" "e" "i" "d" "i"依次放入队列（需要包含头文件`<queue>`），利用队列先进先出（FIFO）的原则，每当从序列中扫到队首元素时，就将队首元素出队。那么当序列扫完时，如果队列为空，则可以完成要求，输出"YES"；

如果队列不空，则不能完成要求，输出"NO"。


```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
char ch[110];
queue<char> que;//建队
int main() {
    que.push('h');
    que.push('e');
    que.push('i');
    que.push('d');
    que.push('i');//将子序列放入队列
    scanf("%s", ch);//读入序列
    int len=strlen(ch);//获得序列长度
    for(int i=0; i<len; i++)//扫描序列
    if(ch[i]==que.front()) que.pop();//如果此时序列元素为队首元素，则弹出队首元素
    if(que.empty()) printf("YES");//如果队列为空，输出"YES"
    else printf("NO");//否则输出"NO"
    return 0;
}
```

---

## 作者：zhengrunzhe (赞：6)

### STLNB
采用stl的string

s.find(ch,pos) 表示在字符串s中从pos开始找字符ch，返回第一个的位置

===string::npos表示没找到

这样就很容易理解了吧

找到第一个h之后 在这个位置往后找e 以此类推
```cpp
#include<string>
#include<iostream>
using namespace std;
string s;
int main()
{
	cin>>s;
	if (s.find('i',s.find('d',s.find('i',s.find('e',s.find('h')))))==string::npos)cout<<"NO";
	else cout<<"YES";
	return 0;
}
```

---

## 作者：judgejudge (赞：1)

# 运用字符串+字符数组

------------
首先我们要**顺序查找**heidi，所以我们必须使其的位置是一个**上升序列**。因此我想到了一个方法：

因为如果存在YES的情况，那么这个字符串中的heidi肯定是按照**h,e,i,d,i的顺序出现**，那么就有了思路：

1. **定义一个字符数组为c[5]，储存h,e,i,d,i，并用k表示c数组的指针**
1. 定义总量sum为0
1. 开始for循环，从头到尾判断，**如果st[i]==c[k]，sum++，k++**
1. **如果sum==5，说明存在heidi，**输出YES；否则输出NO

下面奉上AC代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
char c[5]={'h','e','i','d','i'};//定义字符数组，储存heidi
int main(){
	int i,j,k,n,sum=0;//定义总量sum为0
	string st;
	cin>>st;
	k=0;
	for(i=0;i<st.length();i++){//for循环，从头到尾开始判断
		if(st[i]==c[k]){//如果相等
			sum++;总量加1
			k++;指针往后挪一位
		}
	}
	if(sum==5)cout<<"YES"<<endl;//总量为heidi的长度，说明存在
	else cout<<"NO"<<endl;
	return 0;
}
```




---

## 作者：Rocket_raccoon_ (赞：1)

本题和CF58A几乎一模一样啊。  
应该可以说是较短且易懂的代码（思路）了......  
这里用了一个比较巧妙的方法，先用字符数组把需要的字符串存起来，然后每发现一个字符ans所表示的字符相等，就将ans的值+1。这样就可以很省代码的判定是否满足条件，最后只需根据ans的大小判断是否符合条件即可

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
char r[6]={"heidi"}//预处理需要的字符串;

int main(){
	int i,ans=0;
	char s;
	
	while (cin>>s){//如果读入一个字符
		if (s==r[ans]) ans++;//判断是否符合条件
	}
	if (ans>=5) cout<<"YES";
	else cout<<"NO";
	
	
	return 0;
}
```

---

## 作者：zoezoykit (赞：0)

先来康康题目大意：

给定一个字符串s，询问能否通过删除一些字母使其变为"heidi"；

如果可以输出"YES"，否则输出"NO"。

思路很简单：

先定义一个与 char 数组“heidi”相对应的 **bool** 类型数组，类似 **hash table** 的原理，一个元素一个元素**映射**。

本题的关键就是字符的顺序，所以这里要判断一下，当符合【**此字符与值已经变为 true 的连续映射元素的末尾元素的下一个元素的对应字符相同**】（中括号里的话有点难懂，要多理解几遍）时，才能让此对应字符的映射元素的值变为 **true**，而不能只是双层循环判断是不是有某个字符，否则判断不了顺序是否正确。

最后只有每个元素的值都为 **true**，才能输出"YES"。

下面是泥萌最喜欢的完整AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

char word[6]={"heidi"};
int pd;					//pd变量是循环里的判断值 
bool k[6];				//k数组为word数组的映射 
string heidi;				//"heidi"字符串为需判断的原字符串 

int main()
{
	getline(cin,heidi);			//这样输入字符串方便测试（但要谨慎使用）
	for(int i=0;i<heidi.length();i++)
	{
		pd=0;
		for(int j=1;j<=5;j++)
		{
			if(k[j]==1)		//这里是上文所述的判断 
			{
				pd++;
			}
			else break;
		}
		if(heidi[i]==word[pd]) 
		{
			k[pd+1]=true;
		}
    }
	if(k[1]&&k[2]&&k[3]&&k[4]&&k[5])
	{
		cout<<"YES";
	}
    else 
	{
		cout<<"NO";
	}

    return 0;
}
```

---

## 作者：不到前10不改名 (赞：0)

//看到本题一群大佬用什么stl啊find做就很233，分明是暴力么~QAQ
```
#include<stdio.h>
#include<string.h>
int i,sry=1;
char srx[1001],lhy[11]={'0','h','e','i','d','i'};//数组存储
int main()
{
    scanf("%s",srx);
    for(i=0;i<strlen(srx);i++)//strlen等价于size
    {if(srx[i]==lhy[sry])
    sry++;
    if(sry>5)//出于数组习惯，初始值是1，所以实际上是6才符合
    {printf("YES");
    return 0;}}
    printf("NO");//若符合就结束了，若还没结束就是不符合
    return 0;
}
//qwq
```

---

## 作者：haohaoh4 (赞：0)

因为寻找的过程中必须要按从左向右的位置找，所以可以用一个变量储存所找的字符串的位置，找到后++就可以了。

```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str,find="heidi";
	int f=0;
	cin>>str;
	for(int i=0;i<str.length() && f<find.length();i++)
		if(str[i]==find[f])
			f++;
	if(f==find.length())cout<<"Y\n";//找到所有字符以后正好就是find的长度
	else cout<<"N\n";
	return 0;
}
```

---

## 作者：zhylj (赞：0)

不必一个一个判断，只需要有一个数组记录要判断的字符（"heidi"）
然后扫一遍字符串即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
char p[6]="heidi",c[1005];
int main()
{
    int x=0;  //前面x个已经找到了
    gets(c);  //读入
    for(int i=0;i<strlen(c);i++)
        if(c[i]==p[x]) x++;  //若又找到一个，继续找下一个
    if(x>=5) cout<<"YES"<<endl;  //如果每一个都找到了就输出yes
    else cout<<"NO"<<endl;  //否则输出No
    return 0;
}
```

---

