# Gotta Catch Em' All!

## 题目描述

Bash wants to become a Pokemon master one day. Although he liked a lot of Pokemon, he has always been fascinated by Bulbasaur the most. Soon, things started getting serious and his fascination turned into an obsession. Since he is too young to go out and catch Bulbasaur, he came up with his own way of catching a Bulbasaur.

Each day, he takes the front page of the newspaper. He cuts out the letters one at a time, from anywhere on the front page of the newspaper to form the word "Bulbasaur" (without quotes) and sticks it on his wall. Bash is very particular about case — the first letter of "Bulbasaur" must be upper case and the rest must be lower case. By doing this he thinks he has caught one Bulbasaur. He then repeats this step on the left over part of the newspaper. He keeps doing this until it is not possible to form the word "Bulbasaur" from the newspaper.

Given the text on the front page of the newspaper, can you tell how many Bulbasaurs he will catch today?

Note: uppercase and lowercase letters are considered different.

## 说明/提示

In the first case, you could pick: Bulbbasaur.

In the second case, there is no way to pick even a single Bulbasaur.

In the third case, you can rearrange the string to BulbasaurBulbasauraddrgndgddgargndbb to get two words "Bulbasaur".

## 样例 #1

### 输入

```
Bulbbasaur
```

### 输出

```
1
```

## 样例 #2

### 输入

```
F
```

### 输出

```
0
```

## 样例 #3

### 输入

```
aBddulbasaurrgndgbualdBdsagaurrgndbb
```

### 输出

```
2
```

# 题解

## 作者：外太空 (赞：6)

大家好！今天我来给大家带来CF757A的题解！
很高兴大家看到这道题目！
因为这道题的背景是我翻译的！
```
Bash有一天想成为一名宠物小精灵大师。虽然他喜欢很多口袋妖怪，但他一直对Bulbasaur（妙蛙种子：在它出生的时候背上就背着种子。妙蛙种子经常在阳光下酣睡。它背上的种子通过吸收阳光渐渐长大）最为着迷。很快，事情开始变得严肃起来，他的迷恋变成了一种痴迷。由于他太小（未成年），不能出去捕捉Bulbasaur，他想出了自己捕捉Bulbasaur的方式。

每天，他都会看报纸的头版（他很闲）。他从报纸头版的任何地方一次切出一个字母（闲的一批），形成“Bulbasaur”字样（木有引号好吧！）并将它贴在墙上。 Bash非常讲究（是一个活泼的讲究怪）“Bulbasaur”的第一个字母必须是大写字母，其余字母必须是小写字母。通过这样做，他认为他抓住了一个Bulbasaur，（然后放入精灵球是吧！）。然后他在左边的报纸上重复了这一步骤。他一直这样做，直到不可能从报纸上形成“Bulbasaur”这个词。

鉴于报纸头版的文字，你能告诉他今天会抓到多少个Bulbasaurs？

注意：大写和小写被视为不同。
```

上面是我写的背景，题目是[这个人](https://www.luogu.org/space/show?uid=58543)写的！
题目翻译在提一下
```
Bash有一张报纸，上面有一些字。

Bash可以剪下这些字

他想把这些字拼成"Bulbasaur"(不包括引号)

问可以拼成多少个 $Bulbasaur$ (注意本题区分大小写)

输入一个字符串代表Bash的那张报纸里面的字

输出可以拼成多少个 $Bulbasaur$ 
```

好的开始讲题目了！
其实这道题并不难，
使用数组计数可以过！
什么个数组计数法呢！
首先本题目是会大小写区分的,
然后后有个坑是Bulbasaur这个单词
小写的u和a出现了两次；
所以我们数组计数后要除以二，
其实看起来全英文不想看，
但是还是很适合新手的呢！
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std; 
int B,s,r,a,b,l,u;//定义不说了
int main()
{
	string st;
	cin>>st;//输入
	int n=st.length();//把字符串位数存好否则会达到n^2的时间复杂度因为它会每一次循环计算一次
	for(int i=0;i<n;i++)
	{
		if(st[i]=='B')//数组计数
			B++;
		if(st[i]=='u')
			u++;
		if(st[i]=='l')
			l++;
		if(st[i]=='b')
			b++;
		if(st[i]=='a')
			a++;
		if(st[i]=='s')
			s++;
		if(st[i]=='r')
			r++;
	}
	a/=2;//除以二（多了一个也不可以）
	u/=2;
	cout<<min(min(B,min(u,l)),min(min(b,a),min(s,r)));//算出最小的，输出
} 
```

加油洛谷

---

## 作者：pigstd (赞：2)

这么多人都不用数组做，可能是做的人少，但枚举就太麻烦了
Bulbasaur中有两个'a'和'u'，只要除以2就行了

c++代码：

```
#include<bits/stdc++.h>
using namespace std;
char b[]={"Bulbasr"};//把一个u和a去掉
int a[20];//Bulbasr中各个字母出现的次数
char s[100010];
int main()
{
	cin>>s;
	int len=strlen(s);
	int lenb=strlen(b);
	for (int i=0;i<len;i++)
	{
		char ch=s[i];
		for (int j=0;j<lenb;j++)
			if (b[j]==ch)
				a[j]++;
	}
    //统计
	a[4]/=2;
	a[1]/=2;
    //'u'和'a'的数量除以2
	int minn=999999;
	for (int i=0;i<lenb;i++)//寻找最小的
		minn=min(minn,a[i]);
	cout<<minn;
	return 0;
}
```

求通过

---

## 作者：hanyuchen2019 (赞：1)

### 2021-11-27:修改奇怪措辞。

### 思路：

可以用桶来做（~~虽然很坑~~）。

### 读入：
但是这题有一个特殊点：输入字符可能是**大写**！因此，我们可以腾出一个空位 $t_{26}$，给开头的大写`B`存储，其他的大写字母可以忽略（坑点：如果忘了判断是不是其他的大写字母，你会在第 $2$ 个测试点~~光荣的~~RE）。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t[30];
int main()
{
	char ch;
	while(cin>>ch)
	{
		if(ch=='B')t[26]++;
		else if(ch>='a'&&ch<='z') t[ch-'a']++;
	}
```
### 处理&输出：

~~通过仔细观察~~，我们发现一个`Bulbasaur`有：

- $2$ 个 `a`
- $1$ 个 `b`
- $1$ 个 `l`
- $1$ 个 `r`
- $1$ 个 `s`
- $2$ 个 `u`
- $1$ 个 `B`

现在，我们可以使用木桶原理。最终的组数，取决于其中最少的组数。

```cpp
	int ans=99999999;
	if(t['a'-'a']/2<ans) ans=t['a'-'a']/2;
	if(t['b'-'a']<ans)   ans=t['b'-'a'];
	if(t['l'-'a']<ans)   ans=t['l'-'a'];
	if(t['r'-'a']<ans)   ans=t['r'-'a'];
	if(t['s'-'a']<ans)   ans=t['s'-'a'];
	if(t['u'-'a']/2<ans) ans=t['u'-'a']/2;
	if(t[26]<ans)        ans=t[26];
	cout<<ans<<endl;
	return 0;
}
```
完整代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t[30];
int main()
{
	char ch;
	while(cin>>ch)
	{
		if(ch=='B')t[26]++;
		else if(ch>='a'&&ch<='z') t[ch-'a']++;
	}
	int ans=99999999;
	if(t['a'-'a']/2<ans) ans=t['a'-'a']/2;
	if(t['b'-'a']<ans)   ans=t['b'-'a'];
	if(t['l'-'a']<ans)   ans=t['l'-'a'];
	if(t['r'-'a']<ans)   ans=t['r'-'a'];
	if(t['s'-'a']<ans)   ans=t['s'-'a'];
	if(t['u'-'a']/2<ans) ans=t['u'-'a']/2;
	if(t[26]<ans)        ans=t[26];
	cout<<ans<<endl;
	return 0;
}
```
bye~

---

## 作者：_Cloud_ (赞：1)

题目叙述简化一下：就是一个字符串任意组合，有多少个“Bulbasaur”。
#### 首先我们会想到“数组模拟”。
那怎么实现呢？

很显然，无论字母怎么组合，每种字母的个数不会变。

这就好办了，我们用一个数组“word”来存储字符串中我们所需要的字母种类的个数。在根据个数来判断。

具体详见代码： ~~原谅我奇怪的码风~~
```c
#include <iostream>
#include <cstdio>//我喜欢写两个标准头文件

using namespace std;//“Bulbasaur”中有1个B l b s r ;2个u a;

int word[8],ans;//7种字符，1下标开8个足够了；

char s[100005];//100000的数据

int main()
{
	scanf("%s",s+1);//读入
	for(int i=1;s[i];i++)//当s[i]为''时，就停止循环；
	{
		if(s[i]=='B')word[1]++;//将需要的字符用word记录下来；
		if(s[i]=='u')word[2]++;
		if(s[i]=='l')word[3]++;
		if(s[i]=='b')word[4]++;
		if(s[i]=='a')word[5]++;
		if(s[i]=='s')word[6]++;
		if(s[i]=='r')word[7]++;
	}
	while(word[1]>0&&word[2]>1&&word[3]>0&&word[4]>0&&word[5]>1&&word[6]>0&&word[7]>0)//当至少有1个B，l，b，s，r；2个u，a时，循环执行。（超级长的判断……）
	{
		ans++;//计数器加一
		word[1]--,word[2]-=2,word[3]--,word[4]--,word[5]-=2,word[6]--,word[7]--;//将已经组成的字符减掉
	}
	printf("%d\n",ans);//轻松的输出答案~
	return 0;//愉快的结束~
}
```
   
  
# 打字这么累，不点个赞再走吗？
###### 求通过，求通过，求通过。。。


---

## 作者：moqizhu2005 (赞：0)

## 这道题目是关于字符串的问题
#### 对于储存字符的个数，可以使用STL的map映射
### map有一个好处，是可以直接带入储存
#### 只要定义map<char,int>即可
### 代码如下
```cpp
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
string a;
map<char,int> m;//STLmap定义方法char和int可以换成不同的数据类型
char c[10]="Bulbasr";//由于此字符串中u和a都出现了两次，所以只要查一次就可以了
int ans=999999;//初始化
int main()
{
	cin>>a;
	for(int i=0;i<a.length();i++)
		m[a[i]]++;//map直接定义，方便快捷
	m['u']/=2,m['a']/=2;//记得在u和a两个字符除以2
	for(int i=0;i<7;i++)
		ans=min(ans,m[c[i]]);//寻找最小的匹配即可
	cout<<ans;
	return 0;
}
```
### 简单来说 map还是很强大的

---

## 作者：Hanson水题大佬 (赞：0)

# 这道题其实很简单~~但是我不小心在if后面加了;后来被大佬发现~~
## 就在代码里讲解一下


------------
```cpp
#include <bits/stdc++.h>
#define LD long double
#define LL long long
using namespace std;
char s[10000005];
LL ls;
LD ans1 = 0, ans2 = 0, ans3 = 0, ans4 = 0, ans5 = 0, ans6 = 0, ans7 = 0;//因为后面要用到小数，所以用long double 
LL sum = 0;
int main()
{
	scanf("%s", s);
	ls = strlen(s);
	if(ls <= 8)//因为组成一个 Bulbasaur 至少要9个字符，所以<=8个就直接输出0 
	{
		printf("0");
		return 0;//这是要结束程序，不然会继续执行下面的爆搜 
	}
	for(LL i = 0; i < ls;i ++)//爆搜，纯属暴力 
	{
		if(s[i] == 'B')//一个一个字母搜下去 
			ans1 ++;
		if(s[i] == 'u')
			ans2 += 0.5;//注意一个单词中有两个u，所以只加0.5 
		if(s[i] == 'l')
			ans3 ++;
		if(s[i] == 'b')
			ans4 ++;
		if(s[i] == 'a')
			ans5 += 0.5;//这里的a也一样 
		if(s[i] == 's')
			ans6 ++;
		if(s[i] == 'r')
			ans7 ++;
		if(ans1 >= 1 && ans2 >= 1 && ans3 >= 1 && ans4 >= 1 && ans5 >= 1 && ans6 >= 1 && ans7 >= 1)//如果每个字母的次数都大于等于1(u,a其实是大于等于2) 
		{
			ans1 --;//每个计数器-1 
			ans2 --;
			ans3 --;
			ans4 --;
			ans5 --;
			ans6 --;
			ans7 --;
			sum ++;//次数+1 
		}
	}
	printf("%lld", sum);//输出最终的次数 
	return 0;
}
//Bulbasaur
```


------------
最后祝大家AK IOI

---

## 作者：A_Cute_757 (赞：0)

这一题的难点主要就是min，还有对重复字符的处理了。
```cpp
#include<bits/stdc++.h>
using namespace std; 
int B,s,r,a,b,l,u;	//每一种字符的计数器 
string ss;			//字符串 
int len;			//字符串的长度 
int main()
{
    cin>>ss;		//读入字符串 
    len=ss.size();	//计算字符串的长度 
    for(int i=0;i<len;i++)//从0开始。这是字符串的特质 
    {
        if(ss[i]=='B')B++;//遇到哪种数组就计数 
        if(ss[i]=='u')u++;//遇到哪种数组就计数
        if(ss[i]=='l')l++;//遇到哪种数组就计数
        if(ss[i]=='b')b++;//遇到哪种数组就计数
        if(ss[i]=='a')a++;//遇到哪种数组就计数
        if(ss[i]=='s')s++;//遇到哪种数组就计数
        if(ss[i]=='r')r++;//遇到哪种数组就计数
    }
    cout<<min(min(B,min(u/2,l)),min(min(b,a/2),min(s,r)));//min就是这题的难点，对于重复的字符要处理 
} 
```

---

## 作者：Jinyeke (赞：0)

#### 题目:Bash有一张报纸，上面有一些字。Bash可以剪下这些字，他想把这些字拼成"Bulbasaur"(不包括引号)，问可以拼成多少个Bulbasaur(注意本题区分大小写)，输入一个字符串代表Bash的那张报纸里面的字，输出可以拼成多少个Bulbasaur
### 大概思路：先把组成Bulbasaur的每个字母数量求出来，再找找其中最小的是谁，即可算出一共可以组成多少组。
#### 代码如下（pascal）:
```
var
 a1:array['A'..'Z'] of longint;//统计大写字母的数组
 a2:array['a'..'z'] of longint; //统计小写字母的数组
 i,min,k:longint;
 s:string;
 ch:char;
begin
 read(s);//输入一个字符串
 for i:=1 to length(s) do 
  if s[i] in ['A'..'Z'] then inc(a1[s[i]])//统计每个大写字母各有几个
   else if s[i] in ['a'..'z'] then inc(a2[s[i]]);//统计小写字母各有几个
 min:=maxlongint;//min最好先定大一点
 for ch:='a' to 'z' do//找小写字母
  begin 
   case ch of //枚举需要的字母（也可以写成if的形式）
    'u':k:=a2['u'] div 2; //u在单词里有两个所以要除以2
    'l':k:=a2['l'];//只有一个所以直接加
    'b':k:=a2['b'];//只有一个所以直接加
    'a':k:=a2['a'] div 2;//a在单词里有两个所以要除以2
    's':k:=a2['s'];//只有一个所以直接加
    'r':k:=a2['r'];//只有一个所以直接加
   end;
  if k<min then min:=k;//再看一下是不是小于当前最小的那个数
 end;
 if a1['B']<min then min:=a1['B'];//大写字母只有一个所以直接判断就可以了
 write(min);//输出最小的那个，也就是单词的组数
end.
```
### 求过！
### 共建文明洛谷，请勿Ctrl+C！


---

## 作者：CZQ_King (赞：0)

## 这道题很简单，而且是我的第一篇CF题解。
我用了8个变量，因为$Bulbasaur$中，$u$和$a$是重复的，还有一个字符串。
### 只需要找到$B,u,l,b,a,s,r$就可以了，不需要管其他的。最后找到最少的字，就是次数。
** 注意：因为在$Bulbasaur$中，$u,a$是重复的，所以要把$a$和$u$个数除以二。**
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string str;//字符串
int B,u,l,b,a,s,r;//Bulbasaur
int main(){
    cin>>str;
    for(int i=0;i<str.length();i++){
        if(str[i]=='B')B++;
        if(str[i]=='u')u++;
        if(str[i]=='l')l++;
        if(str[i]=='b')b++;
        if(str[i]=='a')a++;
        if(str[i]=='s')s++;
        if(str[i]=='r')r++;//看着好像打表啊
    }
    cout<<min(B,min(u/2,min(l,min(a/2,min(s,min(b,r))))))<<endl;//眼花缭乱的min
    return 0;//完美结束
}
```

---

## 作者：RioBlu (赞：0)

输入这个字符串本来想统计最这9个字符但是a和u出现了两次！

那么统计的时候就要做点手脚

if(k[1]>k[7]) k[7]++; else k[1]++;

if(k[4]>k[6]) k[6]++; else k[4]++;
```
#include<bits/stdc++.h>
using namespace std;
string a;
char o[10]="Bulbasaur";
int k[10];
int main()
{
	cin>>a;
	for(int s=0;s<a.size();s++)
	{
		for(int v=0;v<9;v++)
		{
			if(a[s]==o[v])
			{
				if(v!=1&&v!=4)//不用做手脚
				{
					k[v]++;
				}
				else//做手脚的地方到了！
				{
					if(v==1)//o[s]是u
					{
						if(k[7]<k[1])k[7]++;
						else
						k[1]++;
					}
					if(v==4)//o[s]是a
					{
						if(k[6]<k[4])k[6]++;
						else
						k[4]++;
					}
				}
				break;
			}
		}
	}
	sort(k,k+9);
	cout<<k[0]<<endl;
}
```

---

