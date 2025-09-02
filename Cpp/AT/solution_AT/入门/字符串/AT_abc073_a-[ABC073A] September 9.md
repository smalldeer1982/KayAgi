# [ABC073A] September 9

## 题目描述

今天是日本的 9 月 9 日。给定一个两位数的整数 $N$，请判断在十进制表示下，$N$ 是否包含数字 $9$。

## 说明/提示

## 限制条件

- $10 \leq N \leq 99$

## 样例解释 1

$29$ 的个位是 $9$。

## 样例解释 2

$72$ 中不包含 $9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
29```

### 输出

```
Yes```

## 样例 #2

### 输入

```
72```

### 输出

```
No```

## 样例 #3

### 输入

```
91```

### 输出

```
Yes```

# 题解

## 作者：އ_昔年™_ (赞：3)

本以为要用字符串一位位判断是否为9，结果看了数据范围，我笑了

数据最多只有两位，所以，我们只需要取这个数的十位和个位，判断其中是否有9就可以了

```pascal
var
  a:longint;
begin
  read(a);
  if(a mod 10=9)or(a div 10=9) then writeln('Yes')
                               else writeln('No');
// a mod 10 就可以取出该数的个位，判断是否为9
// a div 10 取出该数的十位，如果该数只有一位，a div 10 为0
 对结果没有影响
end.
```

---

## 作者：CZQ_King (赞：2)

本题很~~难~~，还以为用字符串
## 结果只有$2$位数
看到那么多$dalao$发的题解，本以为没位置发了，仔细一看，心生一计：
# 打表！！！
因为只有$2$位数，所以共有$(10-1)+10-1$种方法。
```cpp
/*此题打表*/
#include<bits/stdc++.h>//
using namespace std;
int a;//
int main(){
    cin>>a;//
    switch(a){
        case 19:cout<<"Yes";break;
        case 29:cout<<"Yes";break;
        case 39:cout<<"Yes";break;
        case 49:cout<<"Yes";break;
        case 59:cout<<"Yes";break;
        case 69:cout<<"Yes";break;
        case 79:cout<<"Yes";break;
        case 89:cout<<"Yes";break;
        case 90:cout<<"Yes";break;
        case 91:cout<<"Yes";break;
        case 92:cout<<"Yes";break;
        case 93:cout<<"Yes";break;
        case 94:cout<<"Yes";break;
        case 95:cout<<"Yes";break;
        case 96:cout<<"Yes";break;
        case 97:cout<<"Yes";break;
        case 98:cout<<"Yes";break;
        case 99:cout<<"Yes";break;
        default:cout<<"No";break;
    }//打表大法
    cout<<endl;//回车保平安
    return 0;//结束
}
```

---

## 作者：空城旧梦— (赞：2)

## 大舞台上怎么能没有pascal呢？？
### 幸好还有我！！

首先这道题能用两种方法做

1. 可以用简单的打表，因为n只限于两位数
2. 可以用字符串+比较

首先是第一种思路的代码
```pascal
var n,i,j,k,l,s1,s2:longint;
begin
  readln(n);
  s1:=n div 10;//计算十位
  s2:=n mod 10;//计算个位
  if  (s1=9)or(s2=9)then  
    begin
      writeln('Yes');
      exit;//直接退出，避免再次输出'No'
    end;  
  writeln('No');//注意要换行输出，否则AT系列的题都会全WA
end.  
```
这种方法简单易懂，适用于新手入门。但有很大漏洞，如果数字数位很大就要用while循环或者repeat代码长且容易错

那么我们就会想到一种简单的字符串算法，具体见下

```pascal
var  i,j,k:longint;
     s:ansistring;//给小蒟蒻讲一下ansistring是无限长度字符串且内存可伸缩
begin
  readln(s);
  for  i:=1  to  length(s)  do
    if  s[i]='9'  then
      begin
        writeln('Yes');
        exit;//找到直接退出
      end;
  writeln('No');
end.

```
这样就可以计算数位很大的数字而且还不用开数组

感谢研究本人的题解，希望能对pascal的同学有帮助哦

---

## 作者：RioBlu (赞：1)

题目说了:10≦N≦99

## 我想说
# “只有两位啊!”


所以给各位一个python2题解
```
a=input()
if a/10==9 or a%10==9:
    print "Yes"
else:
    print "No"
```

---

## 作者：Minecraft_slime (赞：1)

                               # 水题


```cpp
	#include<bits/stdc++.h>//万能头文件
	using namespace std;
	int a;//定义要输入的数
	int main()
	{
 	cin>>a;//输入
 	if(a%10==9 || a/10==9)//判断十位和个位是不是九
 
	{
 		cout<<"Yes";//如果是的话输出Yes
 		return 0;//结束代码
 	}
 	cout<<"No";//如果没有结束的话，就是说数字里没有九，所以输出No
 	return 0;
	}

```

---

## 作者：Hola_chen (赞：0)

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int main()
{
    //本题直接转string形式判断是否有9 
    string a; //string
    getline(cin,a);//输入 
    int n;//计数 
    n=a.size();//size函数 
    for(int i=0;i<n;i++)//for从0开始，这很重要
    {
        if(a[1]=='-')//特判
        {
            cout<<"No";//输出
            return 0;//return 0;
        }
        if(a[i]=='.')//特判
        {
            cout<<"No";//输出 
            return 0;//return 0;
        }
        if(a[i]=='9')//if判断 
        {
            cout<<"Yes";//输出 
            return 0;//return 0;
        }
        else
        {
            cout<<"No";//输出
            return 0;//return 0;
        } 
    } 
    //结束 
    return 0;
}
```

---

## 作者：xyn0901 (赞：0)

一开始以为n会很大，所以我用的超长字符串

后来看数据没想到这么水。。。

不说废话上代码
```pascal
var s:ansistring;
i:longint;
begin
read(s);
for i:=1 to length(s) do
if s[i]='9' then begin writeln('Yes'); halt; end;
writeln('No');
end.
```


--------------------------华丽丽的结束---------------------------


---

## 作者：yuzhechuan (赞：0)

~~真的水~~

------------

```cpp
#include<bits/stdc++.h>//万能库
using namespace std;
char c;//只需一个字符即可
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);//输入输出加速
    while(cin>>c)//如果有字符就一直读，一直做
    	if(c=='9')//如果是字符9
    	{
    		cout<<"Yes"<<endl;//就输出Yes和换行
    		return 0;//并结束程序
		}
	cout<<"No"<<endl;//如果读完了还没退出的话就输出No和换行
}
```


------------

##### （此程序在编译器中，由于while循环判断的原因，可能读入有点困难，改成文件式读入即可）

---

