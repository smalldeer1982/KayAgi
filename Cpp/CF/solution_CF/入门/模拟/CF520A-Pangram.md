# Pangram

## 题目描述

A word or a sentence in some language is called a pangram if all the characters of the alphabet of this language appear in it at least once. Pangrams are often used to demonstrate fonts in printing or test the output devices.

You are given a string consisting of lowercase and uppercase Latin letters. Check whether this string is a pangram. We say that the string contains a letter of the Latin alphabet if this letter occurs in the string in uppercase or lowercase.

## 样例 #1

### 输入

```
12
toosmallword
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
35
TheQuickBrownFoxJumpsOverTheLazyDog
```

### 输出

```
YES
```

# 题解

## 作者：HoshizoraZ (赞：3)

我看大佬们写这题时都统一了大小写，其实不用

一个条件分支就可以解决这个问题。

举个栗子：'Z' - 'A' = 'z' - 'a'

所以字符作差不用改大小写

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int a[26],s,i,n;			//a[26]就是为了存储每个字母出现的次数，数组放在全局变量位置是因为全局变量里的数组的值默认为0，不用赋值
int main()
{
    scanf("%d\n",&n);	   //这里要空行，不然电脑以为数字n这就是这个字符串
    char c[101];
    gets(c);
    for(i=0;i<n;i++)		//长度已经有了，用上
    {
        if(c[i]>='a'&&c[i]<='z') a[c[i]-'a']++;//若这个字母是小写，就让它减去'a',再存进数组里
        if(c[i]>='A'&&c[i]<='Z') a[c[i]-'A']++;//若这个字母是大写，就让它减去'A',再存进数组里
    }
    for(i=0;i<=25;i++)		//检查每一个数组里存的数
    {
        if(a[i]==0)		   //如果这个字母没出现过就停止并输出NO
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES");			//不然就输出YES
    return 0;    
}
```

---

## 作者：Zirnc (赞：3)

~~实在是不可多得的好水题~~

很简单。

开一个数组，然后每个位置代表一个字符。（可能有一点桶排序的思想）然后一个一个地处理字符，如果是大写就变成小写，然后 `table[s[i]-'a]++;`。再一个一个处理桶数组，如果有 0 的就输出 $NO$，然后退出程序。最后如果 26 个字符都有了就输出 $YES$。

然后刚开始还可以加一个判断：字符数是否小于 26，是的话就直接输出 $NO$ ~~这个题解里好像都没有呢~~

------

```cpp
#include <bits/stdc++.h>
using namespace std;

int table[26];

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    if (n < 26)
    {
        cout << "NO" << endl;
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (s[i] <= 'Z' && s[i] >= 'A')
        {
            s[i] += 32;
        }

        table[s[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (table[i] == 0)
        {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
}
```

---

## 作者：lwzheng00000 (赞：3)

#### 不是很明白为啥用字符串
所以写了个读一个，判断一个的做法~~其实是字符串不会写~~
#### 直接放代码了

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int bj[30];//标记这某个字母有没有出现
int main(){
	memset(bj,0,sizeof(bj));//这个数组一定要初始化
	int n;
	scanf("%d",&n);
	for(int i=0;i<=n;i++){//从0是因为有个'\n'被读进来
		int c=getchar();//读入
		if(c>'Z'){
			c-=32;//全部变大写，为标记做准备
		}
		for(int j=1;j<=26;j++){
			if(c-'A'+1==j){//出现过就做标记
				bj[j]=1;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=26;i++){
		if(bj[i]){//枚举一遍标记,数一下出现过多少不同字母
			ans++;
		}
	}
	if(ans==26){//都出现了就输出
		printf("YES");
		return 0;//不用else，直接退
	}
	printf("NO"); 
	return 0;
}
```
#### 这代码能过我都震惊了

---

## 作者：不到前10不改名 (赞：1)

//看着一群ak的大佬如何虐杀此道题目:打表,爆搜,多重暴力判断,桶思想...  
//然后我却用一些歪门邪道的东西...
```
#include<stdio.h>
int n,i,sry[1001],lhy[101];
char srx[1001];
int main()
{
    scanf("%d",&n);
    if(n<26)//贪心，连26个字母都没有，又何谈全齐？
    {printf("NO");
    return 0;}
    scanf("%s",srx);
    for(i=0;i<n;i++)
    if(srx[i]>='a'&&srx[i]<='z')
    srx[i]-=32;//先全部转换成大写（没办法，c党没有函数...strupr不给用）
    for(i=0;i<n;i++)
    sry[i]=srx[i]-=64;//转换成1~26
    for(i=0;i<n;i++)
    lhy[srx[i]]++;//桶记录
    for(i=1;i<=26;i++)
    if(lhy[i]==0)
    {printf("NO");//查找
    return 0;}
    printf("YES");
    return 0;
    }
//qwq
```

---

## 作者：empty (赞：1)

本蒟蒻用了一上午的时间用字符串做这道题，最后居然全WA了而且还整不好   
本蒟蒻~~可不是好惹的一生气~~就打算用暴力绕过原理   
先将字符转换成数字，随后进行数字查找，考虑到时空复杂度，我就用二分查找，辅用归并排序。   
### 果然

------------
暴力出奇迹
------------ 

------------

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cctype>
using namespace std;
int str[101],r[101];
int Find(int a[],int n,int num)//二分查找，查找字母
{  
 int l=0,r=n,mid=0;  
 while(l<r) 
 {  
  mid=(l+r)/2;  
  if(num==a[mid]) {return mid;} 
                           else if(num<a[mid]) {r=mid;} 
                                          else if(num>a[mid]) {l=mid+1;}  
 }  
 return -1;  
}  
void Gb(int s,int t)//因为二分查找必须有序，所以我打算练练归并
{
 if(s==t) return;
 int mid=(s+t)/2;
 Gb(s,mid);
 Gb(mid+1,t);
 int i=s,j=mid+1,k=s;
 while((i<=mid)&&(j<=t))
  {
   if(str[i]<=str[j])
   {
    r[k]=str[i];k++;i++;
   }
   else
   {
    r[k]=str[j];k++;j++;
   }
  }
 while(i<=mid)
 {
  r[k]=str[i];k++;i++;
 }
 while(j<=t)
 {
  r[k]=str[j];k++;j++;
 }
 for(int i=s;i<=t;i++) str[i]=r[i];
}
int main()
{
 int n;
 char ch;
 cin>>n;
 if(n<26) {printf("NO");exit(0);}
 for(int i=0;i<n;i++) cin>>ch,str[i]=int(toupper(ch));//将字符转换成数字
 Gb(0,n-1);
 /* 以下用来判断，如果有的话，find会传回下标。 */
 /* 但可能传回下标0，所以+1，如果没有，传回-1。 */
 /* ∵-1+1=0，∴大功告成，不喜勿喷。我只是个蒟蒻 */
 if((Find(str,n,int('A'))+1)&&(Find(str,n,int('B'))+1)&&(Find(str,n,int('C'))+1)&&(Find(str,n,int('D'))+1)&&(Find(str,n,int('E'))+1)&&(Find(str,n,int('F'))+1)&&(Find(str,n,int('G'))+1)&&(Find(str,n,int('H'))+1)&&(Find(str,n,int('I'))+1)&&(Find(str,n,int('J'))+1)&&(Find(str,n,int('K'))+1)&&(Find(str,n,int('L'))+1)&&(Find(str,n,int('M'))+1)&&(Find(str,n,int('N'))+1)&&(Find(str,n,int('O'))+1)&&(Find(str,n,int('P'))+1)&&(Find(str,n,int('Q'))+1)&&(Find(str,n,int('R'))+1)&&(Find(str,n,int('S'))+1)&&(Find(str,n,int('T'))+1)&&(Find(str,n,int('U'))+1)&&(Find(str,n,int('V'))+1)&&(Find(str,n,int('W'))+1)&&(Find(str,n,int('X'))+1)&&(Find(str,n,int('Y'))+1)&&(Find(str,n,int('Z'))+1)) cout<<"YES";
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    else cout<<"NO";
 return 0;
}
```
谨记

**暴力出奇迹** 
------------

---

## 作者：一滴小水滴 (赞：0)

我的思路比较简单：输入、将大写字母转换为小写字母（反之也可以）、入桶、判断、输出。

小伙伴门可以自己先做一做

***

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
bool t[30];
bool full()
{
	for(int i=0;i<26;i++)
		if(!t[i])return 0;
	return 1;
}   //判断函数，如果有一个缺失，则不是那个传说中神奇的字符串。
int main()
{
	memset(t,0,sizeof(t));
	cin>>n;
	getchar();
	getline(cin,s);
	for(int i=0;i<n;i++)
		if(isupper(s[i]))s[i]=s[i]-'A'+'a';
             //将大写字母转换为小写
	for(int i=0;i<n;i++) 
		t[s[i]-'a']=1;    //入桶
	if(full())puts("YES");
	else puts("NO");  //输出
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：0)

题意：输入一个字符串，判断这个字符串是否包含了所有的字符（a到z，不区分大小写）。

由于字符串长度n只有100，一共也只有26个字母，我们可以开一个数组打标记。对于每一个字符，如果是大写，那么数组中下标为该字符的ASCII码-'A'的ASCII码的元素++；小写同理。最后O(n)搜一遍看是不是所有0~25下标都不是0，就AC了：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	char c[643];
    cin>>n>>c;
    int a[43]={0},i;//a为标记数组
    for(i=0;i<n;i++)
    {
        if((c[i]>='a') && (c[i]<='z'))//处理小写字母
		{
			a[c[i]-'a']++;
		}
        else if((c[i]>='A') && (c[i]<='Z'))//处理大写字母
		{
			a[c[i]-'A']++;
		}
    }
    for(i=0;i<=25;i++)
    {
        if(a[i]==0)
        {
            cout<<"NO\n";
            return 0;
        }
    }
    cout<<"YES"<<endl;
    return 0;    
}
```

---

## 作者：rill4474 (赞：0)

## 看了楼上的字符串做法
## 感觉太麻烦
### 于是便有了这个题解
```pascal
var
 a:array['A'..'Z']of longint;//后面会说到为什么大写
 ch:char;//输入用的
 i,len,f:longint;//len表示长度
begin
  readln(len);//输入长度
  for i:=1 to len do 
   begin
    read(ch);//输入字符
    ch:=upcase(ch);//转大写
    inc(a[ch]);//累加字母出现次数
   end;//桶排思想
for ch:='A' to 'Z' do if a[ch]<>0 then 
                      inc(f);//累加出现次数
if f>=26 then write('Yes')//如果26个字母都出现了就输出
        else write('No');//不然（滑稽）
end.//完美的end
```
# 不抄袭是洛谷成员基本~~**妹得**~~美德
#### 这个题目名字也有点怪怪的（滑稽）

---

## 作者：Andysun06 (赞：0)

# 题解 CF520A~~~
------------
## 水题一道.也没什么可以讲的，直接见代码：
    var a:array[1..100]of integer;
        s:ansistring;
        i,l,f:longint;
    begin
     readln(l);//输入个数
     readln(s);//输入字符串
      s:=upcase(s);//把字母都改大写
      for i:=1 to l do//循环判断
       a[ord(s[i])-64]:=1;//有就加一
      for i:=1 to 26 do
       if a[i]=0 then//如果有字母没有
        begin
         f:=1;//f为1
        end;
       if f<>0 then
         writeln('NO')//如果f<>0就输出NO
       else
        writeln('YES');//如果f=0就输出YES
     end.
# 严禁抄袭！！！     

---

## 作者：PC_DOS (赞：0)

这是一道字符串模拟题，我们只需要将字符串化成大写在从头到尾遍历一遍，对每种字母做出标记，最后确定标记总数是否为26即可。

代码:
```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
string ToUpper(string sOrigin){ //将字符串转换为全大写的函数
	string ans("");
	long i;
	for (i = 0; i <= sOrigin.length() - 1; ++i){
		if (sOrigin[i] >= 'a' && sOrigin[i] <= 'z')
			ans += char(sOrigin[i] + ('A' - 'a'));
		else
			ans += sOrigin[i];
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	string sInput; //输入的字符串
	int iLength,nCount=0; //iLength-长度；nCount-标记个数
	register int i; //循环计数器
	bool arrChars[26] = { 0 }; //对26个字母的标记
	cin >> iLength >> sInput; //读入长度和字符串
	sInput = ToUpper(sInput); //转换为全大写
	for (i = 0; i < iLength; ++i){ //遍历字符串
		if (!arrChars[sInput[i] - 'A']){ //如果字母尚未标记，即发现新字母
			++nCount; //标记数加一
			arrChars[sInput[i] - 'A'] = true; //标记，防止重复
		}
	}
	if (nCount == 26) //26个字母全
		cout << "YES"; //肯定
	else //否则
		cout << "NO"; //否定
	return 0; //结束
}
```

---

## 作者：06ray (赞：0)

这道题算是一个较水的题目。这道题可以既可以用一个桶来模拟，还可以用STL里面的map来做。map通俗的来说是一个下标可以用char,string等等的一个容器，可以看看[这里](https://www.cnblogs.com/fnlingnzb-learner/p/5833051.html)。（如果本蒟蒻有什么说的不好的话，请各位dalao勿喷）

简单介绍完map后我们回到正题。这道题的主要思路是:读入一个字符串（当然字符数组也可以），然后遍历它的每一个字符，用map存入这个字符（类似于桶的一个操作）比如说m[s[i]]=1;最后在枚举26个字母，如果发现map中有一个字母没有出现，就是if(!m[c])，那么就输出NO，并结束程序。最后即可在循环外输出YES。总体思路就是这样。

下面上代码。

```cpp
#include <iostream>
#include <string>
#include <map>//定义map的头文件 
using namespace std;
map <char,int> m;//定义map，注意下标为char型 
int main()//主函数
{
	string s;
	int n;
	cin>>n;//读入字符串长度
	cin>>s;//读入字符串
	for(int i=0; i<n; i++)//遍历每个字符
	{
		if(s[i]>='A'&&s[i]<='Z') s[i]=char(s[i]+32);//这里很重要，要把大写字母转为小写字母
		m[s[i]]=1;//m[s[i]]标记为1
	}
	for(char c='a'; c<='z'; c++)//定义变量c从a到z
	{
		if(!m[c]) //如果map里没有这个字母
		{
			cout<<"NO";//输出NO
			return 0;//结束程序
		}
	}
	cout<<"YES";//可以直接输出YES
	return 0;//就这样没了？
}
```

---

## 作者：liuyifan (赞：0)

## 基于map和tolower的题解

## 前置知识:std::tolower和std::toupper

toloer和toupper是c++的内置函数,使用时要加#include<cctype>~~用bits的同学请忽略~~
  
它们的原型声明如下:
```cpp
int tolower(int c)
{
	if ((c >= 'A') && (c <= 'Z'))
		return c + ('a' - 'A');
	return c;
}
int toupper(int c)
{
	if ((c >= 'a') && (c <= 'z'))
		return c + ('A' - 'a');
	return c;
}
```
相信从中也可以看出它们的作用了,就是字符的大写小写转换,**NOIP中可用**

极致压行code:
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
map<char,bool>a;int n;//定义map和n
int naim()
{
	scanf("%d",&n);
	getchar();?/将回车过滤掉，不加会RE||WA
	for(reg int i=1;i<=n;i++)a[tolower(getchar())]=1;
	//此行功能:getchar()读取一个字符,tolower(getchar())转为小写,a[tolower(getchar())]=1给map赋值
	for(reg char i='a';i<='z';i++)//i从'a'到'z'
	if(!a[i])return puts("NO"),0;//逗号在压行时很有用,此行功能:输出NO,然后return 0
	//逗号表达式的值取决于最后一个函数||值
	return puts("YES"),0;//同上
}
```
Ps:[map用法](https://www.luogu.org/blog/liuyifan/solution-p1428)
## 拒绝抄袭,共建和谐洛谷

---

## 作者：OdtreePrince (赞：0)

# -字符串-

说实话，大佬们的代码蒟蒻我真心看不懂！

蒟蒻发一段在简单不过的代码来秀一秀吧！

其实，a、A的ASCLL码都不用记，用'A','a'代替即可！

把当前字符减去'a'or'A',用b数组表示该字符是否出现。

上代码！

~~~
#include<bits/stdc++.h>
using namespace std;
int b[200];
int main(){
    int l;
    string s;
    cin>>l>>s;
    for(int i=0;i<l;i++){
        if(s[i]<='z'&&s[i]>='a'){
            b[s[i]-'a']++;
        }
        else b[s[i]-'A']++;
    }
    for(int i=0;i<26;i++){
        if(!b[i]){
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES";
    return 0;
}
~~~

---

## 作者：char32_t (赞：0)

# 题解 CF520A 【Pangram】
------------
题意：给出一个字符串，判断其中是否包含所有字母（不分大小写）。

简单的字符串模拟，因为不区分大小写，所以我们可以将所有大写字母转换为小写字母，再扫描字符串，进行判断。

Code：
```cpp
#include<cstdio>
#include<ctype.h>//字符转换头文件 
bool alp[27];//标志数组 
char ch[110];//字符串数组 
int main(){
	int len, count=0;//长度、计数器 
	scanf("%d", &len);//读入长度 
	getchar(); //吃掉换行符 
	for(int i=1; i<=len; i++){
		scanf("%c", &ch[i]);//读入字符串 
		if(isupper(ch[i])) ch[i]=tolower(ch[i]);//如果是大写字母，就转换为小写字母 
		alp[ch[i]-'a'+1]=true;//将对应数组元素置为true 
	}
	for(int i=1; i<=26; i++) if(alp[i]==true) count++;//扫描字符串 
	if(count==26) printf("YES");//如果包含所有字母，输出YES 
	else printf("NO");//否则输出NO 
	return 0;
}
```

---

