# Hard Work

## 题目描述

After the contest in comparing numbers, Shapur's teacher found out that he is a real genius and that no one could possibly do the calculations faster than him even using a super computer!

Some days before the contest, the teacher took a very simple-looking exam and all his $ n $ students took part in the exam. The teacher gave them $ 3 $ strings and asked them to concatenate them. Concatenating strings means to put them in some arbitrary order one after the other. For example from concatenating Alireza and Amir we can get to AlirezaAmir or AmirAlireza depending on the order of concatenation.

Unfortunately enough, the teacher forgot to ask students to concatenate their strings in a pre-defined order so each student did it the way he/she liked.

Now the teacher knows that Shapur is such a fast-calculating genius boy and asks him to correct the students' papers.

Shapur is not good at doing such a time-taking task. He rather likes to finish up with it as soon as possible and take his time to solve 3-SAT in polynomial time. Moreover, the teacher has given some advice that Shapur has to follow. Here's what the teacher said:

- As I expect you know, the strings I gave to my students (including you) contained only lowercase and uppercase Persian Mikhi-Script letters. These letters are too much like Latin letters, so to make your task much harder I converted all the initial strings and all of the students' answers to Latin.
- As latin alphabet has much less characters than Mikhi-Script, I added three odd-looking characters to the answers, these include "-", ";" and "\_". These characters are my own invention of course! And I call them Signs.
- The length of all initial strings was less than or equal to $ 100 $ and the lengths of my students' answers are less than or equal to $ 600 $
- My son, not all students are genius as you are. It is quite possible that they make minor mistakes changing case of some characters. For example they may write ALiReZaAmIR instead of AlirezaAmir. Don't be picky and ignore these mistakes.
- Those signs which I previously talked to you about are not important. You can ignore them, since many students are in the mood for adding extra signs or forgetting about a sign. So something like Iran;;-- is the same as --;IRAN
- You should indicate for any of my students if his answer was right or wrong. Do this by writing "WA" for Wrong answer or "ACC" for a correct answer.
- I should remind you that none of the strings (initial strings or answers) are empty.
- Finally, do these as soon as possible. You have less than $ 2 $ hours to complete this.

## 样例 #1

### 输入

```
Iran_
Persian;
W_o;n;d;e;r;f;u;l;
7
WonderfulPersianIran
wonderful_PersIAN_IRAN;;_
WONDERFUL___IRAN__PERSIAN__;;
Ira__Persiann__Wonderful
Wonder;;fulPersian___;I;r;a;n;
__________IranPersianWonderful__________
PersianIran_is_Wonderful
```

### 输出

```
ACC
ACC
ACC
WA
ACC
ACC
WA
```

## 样例 #2

### 输入

```
Shapur;;
is___
a_genius
3
Shapur__a_is___geniUs
is___shapur___a__Genius;
Shapur;;is;;a;;geni;;us;;
```

### 输出

```
WA
ACC
ACC
```

# 题解

## 作者：yggdyy_ (赞：4)

这是一道很适合新手训练基础字符串的基础题。  
### 首先我们来阐述一下题意  
给定你三个原始字符串和$N$个答案字符串。对于每一个答案字符串，判断在忽略原始字符串和答案字符串的非字母符号后，能否将三个原始字符串首尾相连，拼接成该答案字符串。（三个原始字符串可以按任意顺序排列，忽略大小写）  
### 我相信这题现在已经有翻译了，但我做这题的时候它还没有...  
我的英语被狠狠地干了一波。  
不过最后在~~有道翻译~~我坚强的意志的带领下，我还是看懂了题目。  
### 然后来讲讲我的做法  
本人很弱，不像各路大佬可以使用各类高级做法。在这里提供一种很朴素的方法。**除去多余字符 -> 忽略大小写比较 -> 输出答案**。  
  
首先看到除去多余字符，本人使用了STL里的string类，个人认为string重载了操作符 '+' 非常有效。（虽然我认为使用C++的OIers都会STL，但在这里我还是说一下，string类里的 '+' 是将两个字符串拼在一起）  
除去多余字符的大体思路如下，原始字符串在输入进来之后，遍历整个字符串，如果一个字符**是字母**，就把它拼接到一个新的字符串的后面。   
当然，题目还要求忽略大小写，因此，可以在进行上述除去非字母字符时顺便把大写字母变成小写字母。    
给出代码：  
```c++
for(int i=0;i<S.size();i++){
	if(S[i]>='a' && S[i]<='z')T=T+S[i];
	if(S[i]>='A' && S[i]<='Z')T=T+(char)(S[i]-'A'+'a');//大写字母转小写字母
}//S是输入进来的字符串，T是除去非字母字符后的字符串
```  
  
接下来就是对于每一个答案字符串进行判断了（不要忘了，答案字符串也要除去非字母字符）。不过题目里面还有一句话"**三个原始字符串可以按任意顺序排列**"，这就使得我们要列举出这三个字符串的所有排列方法。  
下面列出了三个字符串的所有排列方法：  
```
A + B + C  
A + C + B
B + A + C
B + C + A
C + A + B
C + B + A
```  
现在整道题的做法已经清楚了，附上代码：（难看）   
```c++
#include <bits/stdc++.h>
using namespace std;
int n;
string in_x,in_y,in_z;//三个未除去非字母字符的原始字符串
string x,y,z;//除去非字母字符后的原始字符串
string in_st,st;//答案字符串（没除和除了的）
int main(){
	cin>>in_x>>in_y>>in_z;//输入
	for(int i=0;i<in_x.size();i++){//除去非字母字符
		if(in_x[i]>='a' && in_x[i]<='z')x=x+in_x[i];
		if(in_x[i]>='A' && in_x[i]<='Z')x=x+(char)(in_x[i]-'A'+'a');
	}
	for(int i=0;i<in_y.size();i++){
		if(in_y[i]>='a' && in_y[i]<='z')y=y+in_y[i];
		if(in_y[i]>='A' && in_y[i]<='Z')y=y+(char)(in_y[i]-'A'+'a');
	}
	for(int i=0;i<in_z.size();i++){
		if(in_z[i]>='a' && in_z[i]<='z')z=z+in_z[i];
		if(in_z[i]>='A' && in_z[i]<='Z')z=z+(char)(in_z[i]-'A'+'a');
	}
	cin>>n;//输入答案字符串个数
	for(int i=1;i<=n;i++){
		cin>>in_st;
		st="";
		for(int j=0;j<in_st.size();j++){//答案字符串除去非字母字符
			if(in_st[j]>='a' && in_st[j]<='z')st=st+in_st[j];
			if(in_st[j]>='A' && in_st[j]<='Z')st=st+(char)(in_st[j]-'A'+'a');
		}
		if(
		st==x+y+z ||//列举排列方式
		st==x+z+y ||
		st==y+x+z ||
		st==y+z+x ||
		st==z+x+y ||
		st==z+y+x
		){
			cout<<"ACC"<<endl;
		}else cout<<"WA"<<endl;
	}
	return 0;
} 
```  
### 但是，这代码又长又臭，根本不配放在题解中  
蒟蒻想了想，可以使用**引用**来把除去非字母字符的过程放到一个函数里。  
给出这个函数的代码  
```c++
void strcls(string &S){
	string T="";
	for(int i=0;i<S.size();i++){
		if(S[i]>='a' && S[i]<='z')T=T+S[i];
		if(S[i]>='A' && S[i]<='Z')T=T+(char)(S[i]-'A'+'a');
	}
	S=T;
	return;
}
```  
把这个函数扔到代码里面就可以出现一个好看的程序了~  
  
感谢各位的支持

---

## 作者：zct_sky (赞：2)

### Solution:
-----
首先输入三个字符串 $S_1,S_2,S_3$，然后去除这三个字符串中的非字母字符，并将大写字母都变成小写字母（也可以将小写字母都变成大写字母）。

然后排列组合 $S_1,S_2,S_3$ 的首尾相连拼接情况：
1. $S_1+S_2+S_3$；
2. $S_1+S_3+S_2$；
3. $S_2+S_1+S_3$；
4. $S_2+S_3+S_1$；
5. $S_3+S_1+S_2$；
6. $S_3+S_2+S_1$。

最后输入 $n$ 个字符串，同样去除这 $n$ 个字符串中的非字母字符，并将大写字母都变成小写字母，然后将这 $n$ 个字符串与 6 种情况比较，如果是其中之一，输出 `ACC` ，否则输出 `WA` 。 
### Code:
-----
```c++
#include<bits/stdc++.h>
using namespace std;
int n;
string s1,s2,s3,ans[6],b;
void scan(string &x){//输入 
	string a;
	cin>>a;
    for(int i=0,l=a.length();i<l;i++)
        if((a[i]>='A'&&a[i]<='Z')) x+=a[i]+32;
        else if(a[i]>='a'&&a[i]<='z') x+=a[i];
    return;
}
void A(){//排列组合 
	ans[0]=s1+s2+s3;
    ans[1]=s1+s3+s2;
    ans[2]=s2+s1+s3;
    ans[3]=s2+s3+s1;
    ans[4]=s3+s1+s2;
    ans[5]=s3+s2+s1;
}
int main(){
    scan(s1),scan(s2),scan(s3);
    A();
    cin>>n;
    for(int n1=0;n1<n;n1++){
    	b="",scan(b);
        bool f=1;
        for(int i=0;i<6;i++)
            if(b==ans[i]){
            	f=0;
            	break;
			}
	    if(f) cout<<"WA\n";
	    else cout<<"ACC\n";
	}
    return 0;
}

```

---

## 作者：Essinsop (赞：1)

对于这道题，我们可以暴力匹配所有的三个序列的排序情况来得到最终答案。

我们可以直接遍历字符串， 逐个找到是字母的元素，将其添加到新的字符串里。

同时，我们还应该将所有的大写字母转换为小写字母，方便之后的比较。

因此，对于一个字符串 A，我们的处理代码应该如下：

```
for(int i = 1;i <= t1;i++) {//t1是A原始的长度
	if(A[i] >= 'a' && A[i] <= 'z') A[++tot] = A[i];//tot代表把第tot位变为下一个找到的字母元素
	else if(A[i] >= 'A' && A[i] <= 'Z') A[++tot] = A[i] - 'A' + 'a';//如果是大写字母就将其转换为小写字母
	else p1 --;//p1代表转换后A的长度
}
```

通过这个方法，我们可以处理掉 $S1,S2,S3$ 三个字符串以及所有需要比较的字符串。

由于只有 3 个字符串，我们可以直接手动枚举，情况便是这六种：

S1,S2,S3 S1,S3,S2 S2,S1,S3 S2,S3,S1 S3,S1,S2 S3,S2,S1

这里给出上述第一种情况的代码(mps1 为 S1 mps2 为 S2 mps3 为 S3)。

此外，p1，p2，p3 分别为 mps1 mps2 mps3 的长度, ask 为查询的序列

```
bool first() {
	for(int i = 1;i <= p1;i++) if(mps1[i] != ask[i]) return false;
	for(int i = p1 + 1;i <= p1 + p2;i++) if(mps2[i - p1] != ask[i]) return false;
	for(int i = p1 + p2 + 1;i <= p1 + p2 + p3;i++) if(mps3[i - p1 - p2] != ask[i]) return false;
	return true;
}
```
细节:如果查询的序列长度不为给定三个序列的长度总和，可直接输出 WA。

因此，我们得到如下代码：

```
#include <bits/stdc++.h>
using namespace std;
char mps1[100005];
char mps2[100005];
char mps3[100005];
char ask[100005];
int t1, t2, t3, t4, p1, p2, p3, p4;
bool first() {//暴力枚举每一种情况
	for(int i = 1;i <= p1;i++) if(mps1[i] != ask[i]) return false;
	for(int i = p1 + 1;i <= p1 + p2;i++) if(mps2[i - p1] != ask[i]) return false;
	for(int i = p1 + p2 + 1;i <= p1 + p2 + p3;i++) if(mps3[i - p1 - p2] != ask[i]) return false;
	return true;
}
bool second() {
	for(int i = 1;i <= p1;i++) if(mps1[i] != ask[i]) return false;
	for(int i = p1 + 1;i <= p1 + p3;i++) if(mps3[i - p1] != ask[i]) return false;
	for(int i = p1 + p3 + 1;i <= p1 + p2 + p3;i++) if(mps2[i - p1 - p3] != ask[i]) return false;
	return true;
}
bool third() {
	for(int i = 1;i <= p2;i++) if(mps2[i] != ask[i]) return false;
	for(int i = p2 + 1;i <= p2 + p3;i++) if(mps3[i - p2] != ask[i]) return false;
	for(int i = p2 + p3 + 1;i <= p1 + p2 + p3;i++) if(mps1[i - p2 - p3] != ask[i]) return false;
	return true;
}
bool forth() {
	for(int i = 1;i <= p2;i++) if(mps2[i] != ask[i]) return false;
	for(int i = p2 + 1;i <= p2 + p1;i++) if(mps1[i - p2] != ask[i]) return false;
	for(int i = p2 + p1 + 1;i <= p1 + p2 + p3;i++) if(mps3[i - p2 - p1] != ask[i]) return false;
	return true;
}
bool fifth() {
	for(int i = 1;i <= p3;i++) if(mps3[i] != ask[i]) return false;
	for(int i = p3 + 1;i <= p3 + p1;i++) if(mps1[i - p3] != ask[i]) return false;
	for(int i = p3 + p1 + 1;i <= p1 + p2 + p3;i++) if(mps2[i - p1 - p3] != ask[i]) return false;
	return true;
}
bool sixth() {
	for(int i = 1;i <= p3;i++) if(mps3[i] != ask[i]) return false;
	for(int i = p3 + 1;i <= p3 + p2;i++) if(mps2[i - p3] != ask[i]) return false;
	for(int i = p3 + p2 + 1;i <= p1 + p2 + p3;i++) if(mps1[i - p3 - p2] != ask[i]) return false;
	return true;
}
int main() {
	cin >> mps1 >> mps2 >> mps3;
	t1 = strlen(mps1), t2 = strlen(mps2), t3 = strlen(mps3);
	p1 = t1, p2 = t2, p3 = t3;
	int tot = 0;
	for(int i = t1;i >= 1;i--) mps1[i] = mps1[i - 1];//将读入数组后移一位
	for(int i = t2;i >= 1;i--) mps2[i] = mps2[i - 1];//个人喜好
	for(int i = t3;i >= 1;i--) mps3[i] = mps3[i - 1];
	
	for(int i = 1;i <= t1;i++) {//依次处理3个读入的字符串
		if(mps1[i] >= 'a' && mps1[i] <= 'z') mps1[++tot] = mps1[i];
		else if(mps1[i] >= 'A' && mps1[i] <= 'Z') mps1[++tot] = mps1[i] - 'A' + 'a';
		else p1 --;
	}
	tot = 0;
	for(int i = 1;i <= t2;i++) {
		if(mps2[i] >= 'a' && mps2[i] <= 'z') mps2[++tot] = mps2[i];
		else if(mps2[i] >= 'A' && mps2[i] <= 'Z') mps2[++tot] = mps2[i] - 'A' + 'a';
		else p2 --;
	}
	tot = 0;
	for(int i = 1;i <= t3;i++) {
		if(mps3[i] >= 'a' && mps3[i] <= 'z') mps3[++tot] = mps3[i];
		else if(mps3[i] >= 'A' && mps3[i] <= 'Z') mps3[++tot] = mps3[i] - 'A' + 'a';
		else p3 --;
	}
	int T;
	scanf("%d", &T);
	while(T--) {
		cin >> ask;
		tot = 0;
		t4 = strlen(ask), p4 = t4;
		for(int i = t4;i >= 1;i--) ask[i] = ask[i - 1];//后移一位,个人喜好
		for(int i = 1;i <= t4;i++) {
			if(ask[i] >= 'a' && ask[i] <= 'z') ask[++tot] = ask[i];
			else if(ask[i] >= 'A' && ask[i] <= 'Z') ask[++tot] = ask[i] - 'A' + 'a';
			else p4 --;
		}
		if(p4 != p1 + p2 + p3) {
			printf("WA\n");
			continue;
		}
		if(first() || second() || third() || forth() || fifth() || sixth()) printf("ACC\n"); //暴力枚举每一种情况
		else printf("WA\n");
	}
}
```


---

## 作者：jxbe6666 (赞：0)

看见别的 dalao 都用什么 $\text{strlen、char}$ 等等。作为一个蒟蒻，我不禁感慨 STL 库的伟大。


------------
#### 题目分析：
众所周知，字符串的题目都是非常的烦人的，这道也不例外，不仅要去掉除字母以外的所有字符，还得去验证是否为前面 3 个子串拼接而成。这时候 STL 库带着它的函数上场了！

#### 题目思路：
我们先把前三个字符串读进来，再进行删除，通过排列组合一共有 6 种可能。再读入 n 个字符串依旧按照格式删除，再跟这 6 种进行比较，如果相等输出 ACC，一个也不相等则输出 WA。

------------
```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
string s1, a, b, c;
string ans[7];
string answer[1005];
int n;
char ch;
string New_string(string s1)// 按照格式删除
{
    string new_string;
    int len1 = s1.length();
    for (int i = 0; i < len1; i++)
    {
        if (isalpha(s1[i]) == 1)
        {
            new_string += s1[i] + 'a' - 'A';
        }
        if (isalpha(s1[i]) == 2)
        {
            new_string += s1[i];
        }
    }
    return new_string;
}
bool check(string s1)// 判断
{
    for (int i = 1; i <= n; i++)
    {
        if (s1 == ans[i])
        {
            return 1;
        }
    }
    return 0;
}
int main()
{
    cin>>a>>b>>c;
    a = New_string(a);
    b = New_string(b);
    c = New_string(c);
    cin >> n;
    ans[1] = a + b + c;
    ans[2] = a + c + b;
    ans[3] = b + a + c;
    ans[4] = b + c + a;
    ans[5] = c + a + b;
    ans[6] = c + b + a;
    // 排列组合
    for (int i = 1; i <= n; i++)
    {
        cin>>s1;
        s1 = New_string(s1);
        if(check(s1)){
            puts("ACC");
        }
        else{
            puts("WA");
        }
    }
    I AK IOI
}

```


---

## 作者：StarryWander (赞：0)

# 字符串模拟题

思路：将开始给出的三个字符串进行处理（去除字符串中的**除字母外的字符**），同时**将字符串中的所有字母转换为大写或小写**（大小写都可），枚举三个已处理的字符串排列的情况，判断后来给出的字符串是否可能。

避坑：给出的 $n$ 个字符串有可能是大小写转化过后的，因此，每给出的字符串也需要**进行统一处理成大写或小写**。


### 字符串处理函数：

```cpp
string cl(string s){
	string k="";
	for(int i=0;i<s.size();i++){
		if(s[i]>='a'&&s[i]<='z') k+=s[i];//如果是小写，直接加
		else if(s[i]>='A'&&s[i]<='Z'){//大写，转换小写再加上去
			s[i]+=32;
			k+=s[i];
		}
	}
	return k;
}
```
### 完整Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string cl(string s){//字符串处理
	string k="";
	for(int i=0;i<s.size();i++){
		if(s[i]>='a'&&s[i]<='z') k+=s[i];
		else if(s[i]>='A'&&s[i]<='Z'){
			s[i]+=32;
			k+=s[i];
		}
	}
	return k;
}
int main(){
	int n;
	string a,b,c;
	cin>>a>>b>>c;
	a=cl(a);//将三个字符串处理
	b=cl(b);
	c=cl(c);
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		s=cl(s);
		if(s==a+b+c||s==a+c+b||s==b+a+c||s==b+c+a||s==c+a+b||s==c+b+a) cout<<"ACC"<<endl;//枚举拼接情况，看是否存在
		else cout<<"WA"<<endl;
	}
	return 0;
}

```



---

## 作者：tZEROちゃん (赞：0)

### Translation

判断字符串 $s_1, s_2, s_3$ 能否通过首位相连的方式组成 $t_i$（不考虑大小写）。

### Solution

首先，输入 $3$ 个字符串 $s_1, s_2, s_3$，因为不考虑大小写，所以可以把它们全部都变成小写（这里以小写为例，大写也可以）。

接着，读入一个 $n$ ，表示有多少个 $t_i$。

然后，用 `while 循环` 读入 $t_i$，对于每一次循环：
- 转换成小写字母。
- 比对 $6$ 中情况（详见代码）。
   - 符合输出 $\texttt{ACC}$。
   - 否则输出 $\texttt{WA}$。
   
### Code

- [here](https://www.cnblogs.com/tearing/p/13938383.html) or [here](https://www.luogu.com.cn/paste/6cbuxtfu)。

---

## 作者：黄文烽 (赞：0)

## Hard Work题解
[题目传送门](https://www.luogu.com.cn/problem/CF61B)
### 关于数据
对于$100$%的数据,$0 \leq n \leq 1000$,$S1,S2,S3,T_i$均只包含"-", ";" , "_" 和字母字符。
保证$0 \leq S1.length,S2.length,S3.length \leq 100$,$0 \leq T_i.length \leq 600$
### 初始化
首先,我们发现题目有一个很重要的要求：**忽略大小写及非字母字符!**

所以,我们可以在输入结束的时候就处理字符串。

代码很简单：
```cpp
#include<iostream>
#include<string>

using namespace std;

int n;
string a, b, c;
string t[1005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); //优化cin
	
	cin >> a >> b >> c >> n;
	
	clr(a), clr(b), clr(c);
	
	for(int i = 0; i < n; i++){
		cin >> t[i];
		clr(t[i]);
	} 
	
	return 0;
}
```
$clr$函数的写法如下:
```cpp
void clr(string &s){
	string ans = ""; //初始化ans为空串
	
	for(int i = 0; i < s.length(); i++){
		char c = toupper(s[i]); //toupper即为转大写字母的函数
		if(c <= 'Z' && c >= 'A') ans += c; //如果转完结果为大写字母
	}
    
   s = ans;
	
	return; //返回字符串s
}
```
### 字母约定
这里记第一个字符串为$a$,$a$的长度为$lena$,第二个字符串为$b$,$b$的长度为$lenb$,第三个字符串为$c$,$c$的长度为$lenc$
### 一些巨佬做法
"解决字符串的问题的万能钥匙——分割(split)" ——yggdyy_

如果一个字符串$str$能够满足题目要求,那么一定可以取到两个下标$x$和$y$,使得$str_x..._y$,$str_0..._x$和$str_y..._n$($n$为$str$的长度)与$a,b,c$相互对应。

所以说我们到这里就可以暴力解决了。(虽然这样子不可能AC)

通过分析我们发现,$x$的取值只有三种可能,即$lena,lenb,lenc$,$y$的取值则为$lena+lenb+lenc-x$,所以说这样就可以在$O(N)$的时间复杂度做出来了(因为输入就是$O(N)$)。

代码很多巨佬都已经给出了,这里就不直接提供代码了。
### 本蒟蒻的思路
本蒟蒻的思路和各位巨佬恰恰相反,本蒟蒻是通过枚举所有可能的排列来判断是否能够拼出$T_i$。

因为题目只需要拼$3$个字符串,所以可能的排列只有$a+b+c,a+c+b,b+a+c,b+c+a,c+a+b,c+b+a$

然后就可以得到代码了：
### Code
```cpp
#include<iostream>
#include<string>

using namespace std;

int n;
string a, b, c;
string t; //用t代替t[i],因为t[i]的处理允许与输入同时进行 

bool check(string s){ //判断函数 
	return (s == a + b + c) || (s == a + c + b) || (s == b + a + c) || (s == b + c + a) || (s == c + a + b) || (s == c + b + a); 
}

void clr(string &s){
	string ans = ""; //初始化ans为空串
	
	for(int i = 0; i < s.length(); i++){
		char c = toupper(s[i]); //toupper即为转大写字母的函数
		if(c <= 'Z' && c >= 'A') ans += c; //如果转完结果为大写字母
	}
    
    s = ans;
	
	return; //返回字符串s
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); //优化cin
	
	cin >> a >> b >> c >> n;
	
	clr(a), clr(b), clr(c);
	
	for(int i = 0; i < n; i++){
		cin >> t;
		clr(t);
		if(check(t)) cout << "ACC\n"; 
		else cout << "WA\n";
	} 
	
	return 0;
}
```

---

