# Autocomplete

## 题目描述

Autocomplete is a program function that enables inputting the text (in editors, command line shells, browsers etc.) completing the text by its inputted part. Vasya is busy working on a new browser called 'BERowser'. He happens to be working on the autocomplete function in the address line at this very moment. A list consisting of $ n $ last visited by the user pages and the inputted part $ s $ are known. Your task is to complete $ s $ to make it an address of one of the pages from the list. You have to find the lexicographically smallest address having a prefix $ s $ .

## 样例 #1

### 输入

```
next
2
nextpermutation
nextelement
```

### 输出

```
nextelement
```

## 样例 #2

### 输入

```
find
4
find
findfirstof
findit
fand
```

### 输出

```
find
```

## 样例 #3

### 输入

```
find
4
fondfind
fondfirstof
fondit
fand
```

### 输出

```
find
```

# 题解

## 作者：温情 (赞：4)

对于这种字符串查找匹配串的题...

怎么少得了C++中的string类呢.

介绍一下string.find()函数的重载版本:

```
size_t find (const string& str, size_t pos = 0) const noexcept;
size_t find (const char* s, size_t pos = 0) const;
size_t find (const char* s, size_t pos, size_type n) const;
size_t find (char c, size_t pos = 0) const noexcept;
```

既可以用来查找字符串中是否拥有某个字符,也可以用来查找子串,找到了返回字符或子串的起始位置下标.没有则返回
```
string::npos
```
特殊值.

附上代码:

```
#include<bits/stdc++.h>                  //C++万能库 
using namespace std;
int main()
{
	string *str,var;                     //string类指针及var变量 
	int n;                               //用来读取输入 
	cin>>var>>n;                         //输入要找的子串和有几个用于匹配的串 
	str=new string[n];                   //为要输入的匹配串申请内存 
	for(int i=0;i<n;i++)                 //循环输入串 
		cin>>str[i];
	sort(str,str+n);                     //字典序升序快排,标准库中包括对string类的快排函数重载 
	for(int i=0;i<n;i++)                 
	{
		if(str[i].find(var)==0)          //如果在匹配串中找到了这个子串,且是以子串开头 
		{
			cout<<str[i]<<endl;          //输出匹配串
			return 0;                    //直接return 0 
		}
	}
	cout<<var<<endl;                     //如果找完了匹配串还没找到就输出原串
	return 0;                         
}
```

---

## 作者：Kizuna_AI (赞：4)

# [本人博客](https://blog.likecoding.ooo/2019/05/25/%E6%B4%9B%E8%B0%B7cf53a%E9%A2%98%E8%A7%A3/)
## ~~我太弱了所以使用了set~~  
我首先想到set的原因是他是自动排序的（也就是string类型自动按照字典序排序）  
那么于是我们只需判断是否符合条件，把他加入set中，这样第一个就是符合条件的。（如果set中没有任何东西，就代表着没有符合条件的）。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
string st[110];
set<string> se;
set<string>::iterator it;
bool k;
int main() {
    cin>>s;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>st[i];
    //开始检查是否满足条件
    for(int j=1;j<=n;j++) {
        k=false;
        for(int i=0;i<s.size();i++)
            if(s[i]!=st[j][i]) {
                k=true;break;
            }
        //若满足条件则添加到set中
        if(!k) se.insert(st[j]);
    }
    //如果set中没有任何内容，就代表着没有符合条件的
    if(se.empty()) {
        cout<<s;
        exit(0);
    }
    //如果有，那么第一个就是答案（自动按照字典序排序）
    it=se.begin();
    cout<<*it;
    return 0;
}
```

---

## 作者：ACE_ZY (赞：1)

**p党福利**

这一题的意思十分简单,判断字符串s是否在a[1]~a[n]字符串的**开头**

代码如下:
```pascal
var
  n,i,j,l:longint;
  t,s:string;
  p:boolean;
  a:array[0..100000] of string;
begin
  readln(s);//字符串s
  readln(n);//n个字符串
  for i:=1 to n do readln(a[i]);//读入
  for i:=1 to n-1 do//这边运用了一个排序,将字典序最小的放在前面
    for j:=i+1 to n do
    if (length(a[i])>length(a[i])) or (a[i]>a[j]) then
    begin
      t:=a[i];a[i]:=a[j];a[j]:=t;
    end;
  for i:=1 to n do//从字符串最小的开始判断
  begin
    p:=false;
    for j:=1 to length(s) do//判断第i个字符的前(s的长度)个是否与s相同
      if s[j]<>a[i][j] then begin p:=true;break;end;//如果不同p=true 退出
    if p=false then begin writeln(a[i]);exit;end;//如果全部相同p就是false,输出a[i]
  end;
  writeln(s);//否则就是没有相同的,输出s
end.
```
望通过,谢谢了!!!

---

## 作者：da32s1da (赞：1)

一道简单的字符串模拟
```
#include<bits/stdc++.h>
using namespace std;
char a[1000],b[1000],c[1000];
int s,d;
int main()
{
    scanf("%s%d",a,&s); //输入初始字符串和匹配字符串个数 
    d=strlen(a);   //求出初始字符串长度 
    while(s--){
    	scanf("%s",b);    //读入匹配字符串 
    	if(!strncmp(a,b,d)){    //若前d个字符匹配成功 
    		if(!c[0]) strcpy(c,b);    //若还没有答案，保存 
    		if(strcmp(b,c)<=0) strcpy(c,b);   //若前面已经有答案，比较字典序并存下 
		}
	}if(c[0]) printf("%s",c);    //若有答案，输出 
	else printf("%s",a);   //若无答案，输出初始字符串 
    return 0;
}
```

---

## 作者：loi_hjh (赞：1)

其实完全不用写那么多奇奇怪怪的函数，这样看起来整齐一些但稍显冗长

~~请忽略那些奇奇怪怪的头文件（好看的）~~ 

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int la,lb,lc,n;
char a[10001],b[10001],c[10001];
bool x;
void ll(){
	if(!x){//第一次有解直接赋上就可以 
		x=true;
		for(int i=1;i<=la;i++)
			c[i]=a[i];
			return;
	}
	if(strcmp(a+1,c+1)<0){//如果字典序更小 
		memset(c,0,sizeof(c));//忘记这个被坑数次否则请看样例1的输出 
		for(int i=1;i<=la;i++)//改变c 
		c[i]=a[i];
	}
}
void gg(){
	bool y=true;
	memset(a,0,sizeof(a));
	scanf("%s",a+1);
	la=strlen(a+1);
	if(la<lb) return;//直接不够长，根本不可能匹配 
	for(int i=1;i<lb;i++){
		if(a[i]!=b[i]){//无法匹配 
			y=false;
			break;
		}
		if(a[i]>c[i]){//最优化剪枝，a的字典序一定大于c 
			y=false;
			break;
		}
	}
	if(y) ll();//改变c 
}
int main(){
	scanf("%s",b+1);
	lb=strlen(b+1);//求b的长度，下同 
	for(int i=1;i<=lb;i++)//如果到最后都没有变化就是无解，直接输出b（相当于） 
		c[i]=b[i];
	lc=lb;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		gg();
	printf("%s",c+1);//输出c字符串 
	return ~~(0-0);
}
```

---

## 作者：OdtreePrince (赞：1)

# —很多人看不懂字符串函数—
$\color{blue}\texttt{因此让蒟蒻为广大洛谷朋友以最原始的代码来解析吧。}$
$\color{red}\texttt{求欣赏}$
~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    string a,b,c;
    cin>>a;
    c=a;
    int n,p=1;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>b;
        int k=1;
        for(int j=0;j<a.size();j++){
            if(a[j]!=b[j]) k=0;
        }
        if(k){
            if(p) c=b,p=0;
            else{
                int kk=0;
                for(int j=0;j<min(c.size(),b.size());j++){
                    if(c[j]>b[j]){
                        c=b;
                        kk=1;
                        break;
                    }
                    if(c[j]<b[j]){
                        kk=1;
                        break;
                    }
                }
                if(kk==0){
                    if(c.size()>b.size()) c=b;
                }
            }
        }
    }
    cout<<c;
    return 0;
}
~~~

---

