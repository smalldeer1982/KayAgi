# Genetic Engineering

## 题目描述

You will receive 3 points for solving this problem.

Manao is designing the genetic code for a new type of algae to efficiently produce fuel. Specifically, Manao is focusing on a stretch of DNA that encodes one protein. The stretch of DNA is represented by a string containing only the characters 'A', 'T', 'G' and 'C'.

Manao has determined that if the stretch of DNA contains a maximal sequence of consecutive identical nucleotides that is of even length, then the protein will be nonfunctional. For example, consider a protein described by DNA string "GTTAAAG". It contains four maximal sequences of consecutive identical nucleotides: "G", "TT", "AAA", and "G". The protein is nonfunctional because sequence "TT" has even length.

Manao is trying to obtain a functional protein from the protein he currently has. Manao can insert additional nucleotides into the DNA stretch. Each additional nucleotide is a character from the set {'A', 'T', 'G', 'C'}. Manao wants to determine the minimum number of insertions necessary to make the DNA encode a functional protein.

## 说明/提示

In the first example, it is sufficient to insert a single nucleotide of any type between the two 'T's in the sequence to restore the functionality of the protein.

## 样例 #1

### 输入

```
GTTAAAG
```

### 输出

```
1
```

## 样例 #2

### 输入

```
AACCAACCAAAAC
```

### 输出

```
5
```

# 题解

## 作者：Aliemo (赞：5)

# 这道题很简单，不知为何会有嫩么多人不过
### 定义和sum 如果是一样就++，不一样就判断 if %2==0 ans++ 最终的就是结果啦，对字串的掌握。。


```cpp
#include<iostream> //头文件不解释
#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
#include<iomanip>
#include<cmath>
#include<algorithm>
using namespace std;
char a[10001];
int main()
{
	int sum=0,ans=0;
	cin>>a;        //读入字串
	int na=strlen(a);
	for(int i=0;i<na;++i)
	{
		if(a[i]==a[i+1])
		{
			sum++;  //相同就++
		}
		else
		{
			if(sum%2!=0) ans++;//偶数就ans++
			sum=0;
		}
	}
	cout<<ans;//输出ans就可以了，so easy
	return 0;
}
```

---

## 作者：Adrien_Mertens (赞：3)

# 一、对该题的分析
### ①首先，题并不算难，就是找‘A’,'T','G','C'同一字母连续出现偶数次的子串的个数，我们大概只需要跑一下循环
### ②其次用char数组（或string）存一下目标的偶数次tot=1，然后一一比较（可先采用除或mod）
### ③最后，进行比较
# 二、具体解法
### 代码首先奉上
```cpp
#include<iostream> //本人是用C++
#include<cstdio>  //头文件
#include<cstring>
using namespace std;
int main()
{
    char a[105];  //char数组来存（也可用string，但不方便寻找）
    int tot=1,ans=0;// 用来存输入文章，
    scanf("%s",a);  //输入
    for(int i=1;i<=strlen(a);i++) //strlen检测字符串长度，进行循环
    {
        if(a[i]==a[i-1]) tot++;//每两位进行比较
        else
        {
            if(tot%2==0) ans++;//判断是否成立
            tot=1;
        }
    }
    cout<<ans;//进行输出
} 
```
### 输入数据，用一个char数组进行存放，对每一位进行搜索，如果成立，就进行输出
### 本人使用C++语言，如果有改进意见可以向我提出

---

## 作者：封禁用户 (赞：1)

题目传送>>[CF391A](https://www.luogu.com.cn/problem/CF391A)  
### 题意简述：  
求字符串中同一字母连续出现偶数次的子串的个数。  
### 题目分析:  
据题意模拟遍历字符串，分别记录同一字母连续出现的次数，如为偶数次满足则累加答案。  
### Code:  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char st[101];    //开数组存字符串中的字符
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	gets(st);   //gets 为专门读字符串的函数，读取一行字符串
	int sum=1,ans=0;   //定义字母连续出现的次数(注意初始化为1)，满足的子串的个数
	for(int i=0;i<strlen(st);i++)    //strlen 计算字符串的长度
	{
		if(st[i]==st[i+1])   //字母连续出现
		{
			sum++;
		}
		else
		{
			if(sum%2==0)   //字母连续出现的次数为偶数次
			{
				ans++;
				sum=1;    //字母连续出现的次数归为1
			}
		}
	}
	cout<<ans;    //结束整个程序
	return 0;
}
```
### 结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/gyt4n1ex.png)  
企鹅的题解到此结束，祝各位 OIers 进步++~

---

## 作者：CobaltChloride (赞：1)

```
#include<bits/stdc++.h>
using namespace std;
int i,l,ans,ll;
string s;
int main(){
	cin>>s;
	l=s.length();
	i=0;//初始化
	while(i<l-1){//由于程序中有出现s[i+1],故范围到l-1
		ll=1;//相同串长度
		if(s[i]==s[i+1]){//有相同
			while(s[i]==s[i+1]&&i<l-1) i++,ll++;//往下搜索
			if(ll%2==0) ans++;//判断长度
		}
		else i++;//千万别忘加1
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_Veritas (赞：1)

# 这道题不是很难，只需要跑一遍循环即可
## 具体解法
1. 读入字符串，这一步在C++和Python中都可以直接读
2. 跑循环，如果这个字符与上一个不同，说明已经读完一个子串
3. 每读完一个子串判断长度，如果是偶数，计数器加一

------------

#### 以下是代码
### c++
```c
#include<bits/stdc++.h>//头文件
using namespace std;
int main()
{
    char a[10000];
    cin>>a;//输入
    int tot=1,ans=0,l=strlen(a);
  
    int i=1;
    while(i<l+1)
    {
        if(a[i]==a[i-1])//如果相邻两个字符一样
            tot++;
        else//不一样时，tot内存的就是这个子串的长度
        {
            if(tot%2==0)
                ans++;
            tot=1;//长度初始化
        }
        i++;
        while(1);
    }
    cout<<ans;//输出结果
    return 0;//结束
}
```
### Python
```python
tot=1
ans=0
a=input()
l=len(a)
i=1
while i<l+1:
    if a[i]==a[i-1]:
        tot+=1
    else:
        if tot%2==0:
            ans+=1
        tot=1
    i+=1
print(ans)
```

---

## 作者：Ybocean_s (赞：0)

题意：给出一个字符串，让求出相同字母出现偶次的字串个数。


------------
思路：求出每个相连字母字串的长度，进行判断统计符合要求的个数，最后进行输出。


------------
如何判断长度：若前一个字符与后一个字符相同，则继续进行，否则判断，并把计算长度的变量归零。

------------
代码：

```cpp
#include<cstring>
#include<iostream>
using namespace std;
int main()
{
	int js=0,ans=0;
	string s;//输入。
	cin>>s;
	for(register int i=0;i<s.size();i++){
		if(s[i]==s[i+1]){//相同累加长度。
			js++;
		}else{//否则。
			if(js%2!=0){//判断。
				ans++;
			}
			js=0;
		}
	}
	cout<<ans;//输出。
	return 0;
}
```
撒花。

---

## 作者：thomas_zjl (赞：0)

水题，就是求连续$n$个相同字符的个数是否为偶数。

首先我们来看一下样例。

```
GTTAAAG
```

我们从字符串开头开始遍历。

一开始$G$的连续个数为$1$。

所以$ans$不用增加。

后来$T$的个数为$2$，$ans$增加为$1$。

$A$有$3$个，$G$又只有$1$个，所以$ans$不用增加。

接下来看看代码。
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a;
	cin>>a;
	int sum=1;//sum要设为1。
	int ans=0;
	for(int i=0;i<a.length();i++)
	{
		if(a[i]==a[i+1])//如果这位=下一位的话,sum+1。
		{
			sum++;
		}
		else//如果不是。
		{
			if(sum%2==0)//如果sum是偶数。
			{
				ans++;//ans+1。
			}
			sum=1;//sum重新设为1。
		}
	}
	cout<<ans;//输出ans。
	return 0; 
}
```


---

## 作者：Franka (赞：0)

~~一道最大平台长度的模板题~~

### **题目**
给出一个**字符串**$n$，求字符串中**同一字母** _连续出现_ **偶数次**的子串的个数。
### **思路**
$s$的初始值为$1$，然后一个$for$循环，从**2**到$n$字符串的长度，一一枚举即可。

但是这里还要注意一点：最后要加一个**特判**
### **代码**
```pascal
var
 n:string;//定义n字符串
 s,i,sum:longint;//定义别的变量
begin
 read(n);//读入n
 s:=1;//s初始值
 for i:=2 to length(n) do//从2到n字符串的长度
  if n[i]=n[i-1] then inc(s)//如果相邻的两个相等，则s加以
                 else//否则
                  begin
                   if s mod 2=0 then inc(sum);//如果s是偶数，则sum加1
                   s:=1;//找到了新的起点，继续
                  end;
 if s mod 2=0 then inc(sum);//特判最后一位
 write(sum);//输出sum
end.
```

---

## 作者：TRZ_2007 (赞：0)

既然大佬们都发了$string$的，那么我这个蒟蒻只能发一个$char$的了。  
题目上已经说过，字符串最长不超过100，那就定义110以防意外。  
暴力扫描所有有相同字符的串，记录长度，如果是偶数计数器++，最后输出即可。    
$code$
```
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
char s[N];
int main()
{
	gets(s);
	int len=strlen(s),ans=0,lenth=1;
	for(int i=0;i<len;)//i表示子串开始的位置
		for(int j=i+1;j<=len;j++)//j表示当前位置，查找子串
		{
			if(s[i]==s[j])//仍然是同一子串
				lenth++;
			else
			{
				if(lenth%2==0)//长度为偶数
					ans++;//计数器自加
				lenth=1;//子串长度改为一
				i=j;//重新从这个位置开始寻找
			}
		}
	cout<<ans<<"\n";
}
```

---

## 作者：Goldbach (赞：0)

用getline读入字符串

用g表示重复个数

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;//字符串
	int g=1,ans=0;//g最开始定义为1
	getline(cin,s);
	for(int i=0;i<s.size();){
		for(int j=i+1;j<=s.size();j++){
			if(s[j]==s[i]){//判断
				g++;
			}else{
				if(g%2==0)ans++;//在这时就判断是否为偶数
				g=1;
				i=j;//将i变为不等于s[i]的字符的下标，继续判断
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：xyf007 (赞：0)

# 按题意模拟即可
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
string s;
int main()
{
	cin>>s;
	int now=1,len=s.size(),temp=1,ans=0;
	while(now<len)
	{
		if(s[now]==s[now-1])
		{
			temp++;
		}
		else
		{
			if(!(temp&1))
			{
				ans++;
			}
			temp=1;
		}
		now++;
	}
	if(!(temp&1))
	{
		ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

