# cAPS lOCK

## 题目描述

我们为什么需要大写锁定键（Caps Lock）？

Caps Lock 是计算机键盘上的一个按键。按下它后，输入模式会变为默认输入大写字母。如果不小心按下了它，就会导致像第一段中那样的“事故”。

我们认为，如果一个单词是在不小心打开 Caps Lock 的情况下输入的，那么它应满足以下条件之一：

- 要么它只包含大写字母；
- 要么除第一个字母外，其余所有字母都是大写字母。

在这种情况下，我们应该自动将所有字母的大小写进行转换。例如，像 "hELLO"、"HTTP"、"z" 这样的单词，其字母的大小写都应该被改变。

请编写一个程序，按照上述规则处理输入的单词。如果不满足上述规则，则保持单词不变。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
cAPS
```

### 输出

```
Caps```

## 样例 #2

### 输入

```
Lock
```

### 输出

```
Lock
```

# 题解

## 作者：hychen (赞：3)

**直接判断下标从1到最后一个是否大写，，，**

------------
**判断是否大/小写：isupper()/islower()；转化成大/小写：toupper()/tolower()，都需用库cctype**

c++代码：
```cpp
#include<bits/stdc++.h>
#include<cctype>
using namespace std;
char a[101];
int main()
{
    scanf("%s",a);
    int l=strlen(a),biao=0;
    for(int i=1;i<l;i++)
    if(isupper(a[i])==0)
    {
        biao=1;
        break;
    }
    if(biao==1)
    puts(a);
    else
    {
        if(isupper(a[0])==0)
        {
            char c=toupper(a[0]);
            cout<<c;
        }
        else
        {
            char c=tolower(a[0]);
            cout<<c;
        }
        for(int i=1;i<l;i++)
        {
            char c=tolower(a[i]);
            cout<<c;
        }
    }
}
```

---

## 作者：天有不测风云 (赞：1)

我们先分析一下题意。

题意翻译第一行说“若它的所有字母都是大写或只有第一个字母是小写，将这个单词的所有字母大小写反转后输出”。一般可以想到的思路是先判断第一个字符，再判断后面的字符。但是由于第一个字符大写和小写都可以，故可以不用判断。

下面贴上我的代码，~~不用在意我的码风~~（正版防抄）：


------------


```cpp
#<iostream>//输入输出头文件
#<string>//字符串头文件
using namespace std;//名字空间
long long a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z；//这些不用在意
string S；//定义字符串变量
main()
{
	cin>>S；//输入
	for(i=1；i<S.size()；i++）
	{
		if((S[i]<'A')||(S[i]>'Z')）//判断如果第一个以后的字符不在大写范围内，则直接输出
		{
			cout<<S<<endl；
			return 0；
		}
	}
	for(i=0;i<S.size();i++）//转换大小写
	{
		if((S[i]>='A')&&(S[i]<='Z')）
		{
			S[i]+=32；//大小写相差32
			continue；
		}
		if((S[i]>='a')&&(S[i]<='z')）
		{
			S[i]-=32；//同上
			continue；
		}
	}
	cout<<S<<endl；//输出
	return 0；
}
```


---

## 作者：zhengrunzhe (赞：1)

提供std::string迭代器遍历式代码

iostream自带函数：

isupper(a) 判断a是否为大写字母 是返回true 否返回false

islower(a) 同理

toupper(a) 返回字母a的大写形式

tolower(a) 同理

string::iterator k; 构建一个字符串的迭代器叫作k 存储的是地址

s.begin() 返回字符串s首位的地址

s.end() 返回字符串s末尾的后一位的空地址

k++ 迭代器+1 访问下一位的地址

*k 表示迭代器地址k所指向的元素(字符)

```cpp
#include<string>
#include<iostream>
using namespace std;
string s;
int main()
{
	cin>>s;
	string::iterator k=s.begin()+1; //第一位无所谓 故从第二位开始判断
	while (isupper(*k)&&k!=s.end())k++; //如果是大写字母就继续往下 知道遇到小写字母或末尾为止
    //如果遍历到了末尾的下一位 即除第一位后面全是大写字母
	if (k==s.end())for (k=s.begin();k!=s.end();k++)*k=islower(*k)?toupper(*k):tolower(*k);
    //是小写就转大写 是大写就转小写
	cout<<s;
	return 0;
}
```

---

## 作者：ygl666666 (赞：0)

## 题意
判断一个单词，如果全是大写或只有第一个字母是小写来判断
的话就要大小写互换，其他就可以不管。
## 思路
先统计一下大小写的数量，小写我分了两次，来判断是不是第一个是不是小写，和其他的小写，最后根据全是大写或只有第一个字母是小写来判断即可
## code
```
/**/
#include<bits/stdc++.h>
using namespace std;
string s; 
int ans,ansa,ansb;
int main(){
	ios::sync_with_stdio(false);
	cin>>s;
	int len=s.length();
	for(int i=0;i<len;i++){
		if(s[i]>='A'&&s[i]<='Z'){
			ans++;
		}
		if(s[i]>='a'&&s[i]<='z'&&i==0){
			ansa++;
		}
		if(s[i]>='a'&&s[i]<='z'&&i!=0){
			ansb++;
		}
	}
	if(ansa==1&&ansb==0||ans==len){
		for(int i=0;i<len;i++){
			if(s[i]>='A'&&s[i]<='Z'){
				s[i]+=32;
			}
			else if(s[i]>='a'&&s[i]<='z'){
				s[i]-=32;
			}
		}
	}
	cout<<s;
	return 0;
}
```



---

## 作者：封禁用户 (赞：0)

## 前言

这道题目是一道模拟题。

根据题目意思来解决即可。

## 分析

输入一个单词，**若它的所有字母都是大写或只有第一个字母是小写**，将这个单词的所有字母大小写**反转**后输出，否则按照原来的输入将这个单词输出。 

输入格式：只有一行，包含一个只有大小写字母的单词。 

输出格式：只有一行，为处理过后的单词。

那么按照题目模拟即可，也就是判断除第一个字母外，是否有小写字母的存在，如果存在那么就反转一下。

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
string s1;
bool flag;
//flag 表示是否要反转，s1 表示输入的字符串
signed main()
{
        cin>>s1;
        //字符串也只能用 cin 读入
        int len=s1.length();
        flag=true;
        //先标记为 true 也就是需要反转
        for (int i=1; i<len; i++)//注意，这里字符串是从 0 开始读入的，那么我抛弃掉开头的字母，然后查找是否有小写字母的存在。
                if (s1[i]<'A' || s1[i]>'Z')
                {
                        flag=false;
                        break;
                        //如果有小写字母，那么直接 break 并且不需要反转。
                }
        if (flag)
        {
                if (s1[0]>='A' && s1[0]<='Z') s1[0]=s1[0]+('a'-'A');
                else s1[0]=s1[0]-('a'-'A');
                //上面特判 开头 字母，因为开头字母有可能是小写 也有可能是大写。
                for (int i=1; i<len; i++) s1[i]=s1[i]+('a'-'A');
                //这个就是将整个字符串反转的过程。
        }
        cout<<s1<<endl;
        return 0;
        //然后输出就愉快地解决了这道题目
}

```

## 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

**谢谢观赏！**

---

## 作者：hensier (赞：0)

大模拟！

这道题定义一个字符数组把整个输入进来的字符跑一遍即可。在$i∈[1,|s|)$（$|s|$为$s$字符数组的长度）区间进行循环，只要找到一个小写就退出循环。这样就能作出标记。判定方法是：如果$i==|s|$就说明除第一个字符外其他都是大写，反之亦然。反转只需要合理利用字符的值即可。

$AC$代码：

```cpp
#include<cstdio>
char s[101];
int i,len;
int main()
{
    gets(s);
    for(;s[len];len++);//这样可以求出s的大小
    for(i=1;s[i];i++)if(s[i]>='a'&&s[i]<='z')break;//只要不满足就退出
    if(i-len)puts(s);//如果第一个字符以后有小写就直接输出
    else//否则反转
    {
        for(i=0;s[i];i++)
        {
            if(s[i]>='a'&&s[i]<='z')putchar(s[i]-'a'+'A');//如果小写就输大写
            else putchar(s[i]-'A'+'a');//如果大写就输小写
        }
    }
}
```


---

## 作者：ACE_ZY (赞：0)

字符串模拟题

程序如下(Pascal):

```pascal
var
  i:longint;
  p:boolean;
  s,s1,s2:string;
begin
  readln(s);
  s1:=upcase(s);//把s字符串所有字符转大写
  if s1=s then begin s1:=lowercase(s);writeln(s1);exit;end;//如果把s字符串所有字符转大写等于原本的字符串,说明这个字符串是大写的,满足了第1个条件,因此把s字符串所有字符转小写即可(因为已确定这个字符串是大写了,所有相反处理就是把大写转小写),lowercase是大写转小写
  s1:=s;//在s1字符串的存一个s字符串
  p:=true;//假设满足第2个条件(只有第一个字母是小写,其它都是大写)
  for i:=1 to length(s) do
  begin
    if (i=1) and (s[i] in ['A'..'Z']) then begin p:=false;break;end;//如果字符串第一个字符是大写,说明不满足条件,p=false,退出循环
    if (i<>1) and (s[i] in ['a'..'z']) then begin p:=false;break;end;//如果字符串其它字符中(除了第1个)有一个是小写,说明不满足条件,p=false,退出循环
    if s[i] in ['A'..'Z'] then s[i]:=lowercase(s[i])//如果上面两个都不满足,可以直接做相反处理了
      else s[i]:=upcase(s[i]);//入上
  end;
  if p then writeln(s)//如果满足第2个条件,直接输出s(s上面已经做了相反处理了)
    else writeln(s1);//否则将之前存着的s的字符串s1输出
end.
```

望通过,谢谢

---

## 作者：judgejudge (赞：0)

# 带有技巧性优化的题解！！！
首先对于这种大小写反转的题目，最直接的反应是**ASCII码的问题，如果是小写字母就-=32；大写字母就+=32**

那么就有了基本思路：

1. 输入字符串，判断是否满足条件（即是否“**它的所有字母都是大写或只有第一个字母是小写**”）
1. 如果是，就开始转，**大写字母+=32；小写字母-=32**
1. 若不是，**直接输出**

下面奉上AC代码以及我个人的一些小优化：
```cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
	int i,j,k=0,n;
	string st;
	cin>>st;
	for(i=1;i<st.length();i++)//优化1：这里只要判断1至st.length()-1位
	if(st[i]<'A'||st[i]>'Z')k++;//因为只需要判断这个范围内是否是大写
	if(k==0){
		j=0;//注意：最容易漏掉这一步，如果不加就会重复转大小写！！！
		if(st[0]>='A'&&st[0]<='Z'){
		    st[0]+=32;
		    j++;//这样++
		}
		if(st[0]>='a'&&st[0]<='z'&&j==0){//用j==0判断是否转过
			st[0]-=32;
		}//优化2：此处指判断第一位，因为前面已经判断过1至st.length()-1位是大写
		for(i=1;i<st.length();i++)
		st[i]+=32;//所以不需要再进行判断，省时间
		cout<<st<<endl;
	}
	else cout<<st<<endl;//不是就直接输出
	return 0;
}
```



---

## 作者：米奇奇米 (赞：0)

```cpp
     这是一道模拟题，只要按照题目意思：判断哪些情况时直接输出。哪些情况要大小写转换。
#include<bits/stdc++.h>
using namespace std;
int ans1,ans2,len;//ans1统计大写字母数量，ans2统计小写字母数量
string s;
int main() {
	getline(cin,s);
	len=s.length();
	//cout<<len<<" ";
	for(int i=0; i<len; i++) {
		if('A'<=s[i] && s[i]<='Z') ans1++;
		if('a'<=s[i] && s[i]<='z') ans2++;
	}
	if(ans2==len) {//如果都是小写字母，就照样输出
		cout<<s<<endl;
		return 0;
	}
	if(ans2==len-1 && 'A'<=s[0] && s[0]<='Z')  {
		cout<<s<<endl;
		return 0;
	} else {
		for(int i=0; i<len; i++) {
			if('A'<=s[i] && s[i]<='Z') s[i]+=32;
			else s[i]-=32;//否则按照题目意思进行大小写转换
		}
	}
	cout<<s<<endl;//输出变化后的字符串
	return 0;
}

```

---

