# s-palindrome

## 题目描述

Let's call a string "s-palindrome" if it is symmetric about the middle of the string. For example, the string "oHo" is "s-palindrome", but the string "aa" is not. The string "aa" is not "s-palindrome", because the second half of it is not a mirror reflection of the first half.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691B/4db2e6d4ff8e49af69a33905ad7864160ff04588.png)English alphabetYou are given a string $ s $ . Check if the string is "s-palindrome".

## 样例 #1

### 输入

```
oXoxoXo
```

### 输出

```
TAK
```

## 样例 #2

### 输入

```
bod
```

### 输出

```
TAK
```

## 样例 #3

### 输入

```
ER
```

### 输出

```
NIE
```

# 题解

## 作者：fantianqi (赞：3)

没什么好说的，直接判断就好了。

相对于其他题解，我觉得更清晰一点吧。

以下是稍微缩过一点点的代码:

```
#include<bits/stdc++.h>
char f[255],s[1005];int main(){
	f['A']='A';f['H']='H';f['I']='I';f['M']='M';f['O']='O';f['T']='T';
	f['U']='U';f['V']='V';f['W']='W';f['X']='X';f['Y']='Y';f['b']='d';
	f['d']='b';f['o']='o';f['p']='q';f['q']='p';f['v']='v';f['w']='w';
	f['x']='x';scanf("%s",s);
	for (int i=0,j=strlen(s)-1;i<=j;++i,--j)
	if(f[s[i]]!=s[j]){puts("NIE");return 0;}
	puts("TAK");return 0;
}

```

然后就水了一道深蓝题...


---

## 作者：pV_equals_nRT (赞：1)

因为诸位Dalao都发了代码，所以本蒟蒻只发思路~
---
因为似乎只有‘b’‘d’‘p’‘q’比较特殊,其他都只需要相等即可\
【思路】：先输入，并计算字符串长度为奇数或者偶数，由中间向两边搜索，进行判定，如不匹配直接输出并退出；如果到最后仍然匹配则为对称。
```cpp
#include<bits/stdc++.h>//有点丑
using namespace std;
char k[1001];
int main()
{
    gets(k);
    for(int i=strlen(k)%2?strlen(k)/2:strlen(k)/2,j=strlen(k)%2?strlen(k)/2+2:strlen(k)/2+1;i>=0,j<strlen(k);i--,j++)//三目运算符选择,如果是奇数，则最中间的字母不用判定；如果是偶数，中间的字母进行判定
    {
        if(k[i]=='b')//如果是‘b’的情况
        {
            if(k[j]!='d')
            {
                printf("NIE");//不匹配
                return 0;
            }
        }
        else
        {
        if(k[i]=='d')//如果是‘d’的情况
        {
            if(k[j]!='b')
            {
                printf("NIE");//不匹配
                return 0;
            }
        }else
        {
        if(k[i]=='p')//如果是‘p’的情况
        {
            if(k[j]!='q')
            {
                printf("NIE");//不匹配
                return 0;
            }
        }else
        {
        if(k[i]=='q')//如果是‘q’的情况
        {
            if(k[j]!='p')
            {
                printf("NIE");//不匹配
                return 0;
            }
        }else//特判
        {
        if(k[i]!=k[j])
        {
            printf("NIE");//如果不为bdpq，就进行一般判定：如果两个字母不一样，则判定为不对称。
            return 0;
        }//一般判断
        }
        }
        }
        }
    }
    printf("TAK");//如符合即为对称
}
```
最后普及一下三目运算符：a?b:c(如果a为真，执行b，否则执行c)\
也可以写成
```cpp
if(a为真)
{
	b;
}
else c;
```

---

## 作者：strategist_614 (赞：1)

* ~~题目被恶意评分~~
* 分析题目的要求比普通回文串多了要求根据英文字母的样子使得在满足回文串基础上对称。通过26个大小写字母逐一判断和什么字母对称模拟就可以了。

 ```C++{.line-numbers}
 #include<bits/stdc++.h>
using namespace std;
map<char,char> mp;
char a[1005];
int main ()
{ 
    mp['A'] = 'A';
    mp['b'] = 'd';
    mp['d'] = 'b';
    mp['H'] = 'H';
    mp['I'] = 'I';
    mp['M'] = 'M';
    mp['O'] = 'O';
    mp['o'] = 'o';
    mp['T'] = 'T';
    mp['U'] = 'U';
    mp['V'] = 'V';
    mp['v'] = 'v';
    mp['W'] = 'W';
    mp['w'] = 'w';
    mp['X'] = 'X';
    mp['x'] = 'x';
    mp['Y'] = 'Y';
    mp['q'] = 'p';
    mp['p'] = 'q';
    scanf("%s",a+1);
    int len = strlen(a+1);
    if(len % 2)
    {
      char ch = a[len/2+1];//奇数串特判中间的字母是不是对称字母
      if(ch != mp[ch]) 
      {
      	cout<<"NIE"<<endl;
      	return 0;
      } 
      for(int i =1;i<=len/2;i++)
      {
         if(mp[a[i]] != a[len-i+1])
         {
         	cout<<"NIE"<<endl;
         	return 0;
         }  
      }
      cout<<"TAK"<<endl;
    }
    else //偶数串直接判断
    {
    	for(int i =1;i<=len;i++)
    	{
           if(mp[a[i]] != a[len-i+1]) 
           {
           	  cout<<"NIE"<<endl;
           	  return 0;
           } 
    	}
    	cout<<"TAK"<<endl;
    }	
    return 0 ;
}
```


---

## 作者：CR7_houyetong (赞：1)

# 题意
一道很好读懂的题目，刚开始我还以为是判断回文字符串，直到我看到第二个样例才发现我的理解是错的。题意是如果正着读的字符串和字母翻转后的字符串相等输出```TAK```，否则输出```NIE```。

由于字符串的长度不超过 $1000$，所以可以直接模拟。

$\texttt{Q:}$何为字母翻转？

$\texttt{A:}$就是将字母的方向反一下，例如 $b$ 的那个肚子是面向右边的，翻转后肚子面向左边变成了 $d$。

# 分析
统计了一下可以颠倒的字符，发现可以分成两类：

1. 翻转过来还是本身的，如 $H$ 翻转过来还是 $H$。
1. 翻转过来是其他正常字母的，如 $b$ 翻转过来是 $d$。

大部分的字母都是第一种情况或是无法翻转，只有 $b$、$d$、$q$、$p$ 是第二种情况，于是思路就有了：

- 把所有 $b$ 变成 $d$，或是把所有 $d$ 变成 $b$；接着把所有 $p$ 变成 $q$，或是把所有 $q$ 变成 $p$。
- 这样就排除了第二种情况，只要判断该字符串是否回文就可以了。

# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
char a[1010];
int len,i,t,w;
signed main(){
    cin>>a+1;//令字符串的首个位置变成1。
    len=strlen(a+1);//计算字符串的长度。
    for (i=1;i<=len;i++){
        if (a[i]=='b')
          a[i]='d';//如果该字母是b，那么将其变成d。
        if (a[i]=='p')
          a[i]='q';//如果该字母是p，那么将其变成q。
    }
    t=1;//t指针从首个位置出发。
    w=len;//w指针从末个位置出发。
    while (t<=w){//执行到头尾交叉后结束。
        if (a[t]==a[w]){
            t++;
            w--;
        }//如果两个字符相同，两个指针往中间移动继续判断。
        else
          return cout<<"NIE",0;//如果两个字符不相同，那么这个字符串肯定不是回文，直接结束程序。
    }
    return cout<<"TAK",0;//表明这是回文串，输出TAK。
}
```


---

## 作者：happy_zero (赞：0)

### 思路
先用 map 记录相互对称的字符，这里一定要细心！
容易错的有： 

- n 和 m  和自己本身不是对称的
- q 和 p 是对称的
- U 和自己本身是对称的

再从头到一半开始扫，判断第 $i$ 个字符和第 $n-i+1$ 个字符是否对称。
#### 注意！
当 $n$ 为奇数时，要特判最中间的字符本身是不是对称的。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[10005];
int n;
map<char,char>p;
int main(){
    p['A']='A';
    p['b']='d';
    p['d']='b';
    p['H']='H';
    p['I']='I';
    p['M']='M';
    p['O']='O';
    p['o']='o';
    p['p']='q';
    p['q']='p';
    p['T']='T';
    p['U']='U';
    p['V']='V';
    p['v']='v';
    p['W']='W';
    p['w']='w';
    p['x']='x';
    p['X']='X';
    p['Y']='Y';
    cin>>s;
    n=strlen(s);
    if(n%2){
        if(p[s[n/2]]!=s[n/2]){
            cout<<"NIE";
            return 0;
        }
    }
    for(int i=1;i<=n/2;i++){
        if(s[i-1]!=p[s[n-i]]){
            cout<<"NIE";
            return 0;
        }
    }
    cout<<"TAK";
    return 0;
}
```


---

## 作者：kaceqwq (赞：0)

# 题目大意：
给出一个字符串 $s$，判断它是否由中线对称。

# 分析：
简单模拟题，如果字符串长度 $len$ 为偶数，设置两个变量 $i$ 和 $j$，分别从 0 到 $len \div 2$ 递增和从 $len - 1$ 到 $len \div 2$ 递减，判断 $s_i$ 对称过去是否是 $s_j$；如果字符串长度是奇数，除了特判最中间的字母是否是轴对称字母以外，其余同上。

所以我们首先可以使用 map 来存储每一个字母翻转过去的字母，然后打表出每一种符合对称的情况，再如上模拟即可，并且这也可以很好解决字符串长度为奇数时的特判，即当一个字母翻转过去仍为它本身时，那么这个字母本身就是轴对称的字母。

**注意：**

$m$ 与 $m$ 和 $n$ 与 $n$ 并不算完全的对称，我当时就因为这个坑 WA 了。

# Code: 
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
string s;
int len;
map <char, char> q;
bool flag;
signed main() {
	q['x'] = 'x';
	q['X'] = 'X';
	q['d'] = 'b';
	q['b'] = 'd';
	q['o'] = 'o';
	q['O'] = 'O';
	q['w'] = 'w';
	q['W'] = 'W';
	q['A'] = 'A';
	q['M'] = 'M';	
	q['H'] = 'H';
	q['U'] = 'U';
	q['p'] = 'q';
	q['q'] = 'p';
	q['T'] = 'T';
	q['Y'] = 'Y';
	q['v'] = 'v';
	q['V'] = 'V';
	q['I'] = 'I';    //打表出所有符合对称的
	cin >> s;
	len = s.size();
	if (len % 2 == 0) {    //偶数的情况
		for (int i = 0, j = len - 1; i < len / 2 + 1, j > len / 2 - 1; i++, j--) {
			if (q[s[i]] != s[j]) {
				cout << "NIE" << '\n';
				flag = 1;
				break;
			}
		}
		if (!flag) cout << "TAK" << '\n';
	}
	else {   //奇数的情况，与偶数一致，增加了一个特判
		char c = s[len / 2];
		if (q[c] != c) {      //特判最中间的字母
			cout << "NIE" << '\n';
			return 0; 
		}
		for (int i = 0, j = len - 1; i < len / 2 + 1, j > len / 2; i++, j--) {
			if (q[s[i]] != s[j]) {
				cout << "NIE" << '\n';
				flag = 1;
				break;
			}
		}
		if (!flag) cout << "TAK" << '\n';
	}
	return 0;
}
```


---

## 作者：OoXiao_QioO (赞：0)




# 前言

我的这篇题解应该比其他大佬的题解要好理解一点点吧，毕竟是被坑了 $10$ 次的代价。

这道题只要细心找找规律就行，但我还是被坑了至少 $10$ 次。。。。

# 题目描述 & 思路

一个字符串，要你判断是不是呈对称的关系，但这里却和普通的规则有所不同。

注意事项：

- 这道题不是回文串，例如 $\verb!abba!$ 虽然是回文串，但是在此题却**不成**对称关系。

- 在这道题中，判断的标准是**完全对称，也就是是呈镜像**（很像小学所学的轴对称图形）。

- 注意诸多字母的判断，例如 $n$ 严格来说并不是完全镜像，而 $m$ 同理。但是 $b$ 和 $d$ 是完全镜像的，$p$ 和 $q$ 也是完全镜像的。~~我被他们俩坑了有三四次。~~

- 有些字母大小写皆可成为镜像。

- 注意 $p$ 和 $q$ 是镜像的，反过来，$q$ 和 $p$ 也是镜像的。（啥也没说）。

- 注意要把全部呈镜像的都要找出来

以上几点为重要注意事项，弄明白了以后就可以来轻松水掉此题了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义
	 
	int l,i,f;// l 表示字符串长度, f 表示是否成完全镜像的字符串。 
	char s[1001],x,y;
	
	//输入
	 
	scanf("%s",s);
	
	//变量赋初值
	 
	l = strlen(s);
	f = 1;//假设一开始成立 
	
	for(i=0;i<=l/2;i++)//我们只需找到字符串的一半就可以了，注意 i <= l/2 ，不然遇上 a 这种数据就会被卡掉。 
	{
		x = s[i];//用 x 更方便表示 s[i]。 
		y = s[l-i-1];//用 y 更方便表示 s[l-i-1]。
		//x 和 y 也可以不用，只不过这样看的更方便。 
		 
		//根据x 和  y 来判断是否镜像，这里是按字母表的顺序来列出的。
		//注意有些字母大小写、或者反过来都是成立镜像的。 
		if(x=='A'&&y=='A')
			;
		else if(x=='b'&&y=='d'||x=='d'&&y=='b')
			;
		else if(x=='H'&&y=='H')
			;
		else if(x=='I'&&y=='I')
			;
		else if(x=='M'&&y=='M')
			;
		else if(x=='o'&&y=='o'||x=='O'&&y=='O')
			;
		else if(x=='q'&&y=='p'||x=='p'&&y=='q')
			;
		else if(x=='T'&&y=='T')
			;
		else if(x=='U'&&y=='U')
			;
		else if(x=='v'&&y=='v'||x=='V'&&y=='V')
			;
		else if(x=='w'&&y=='w'||x=='W'&&y=='W')
			;
		else if(x=='x'&&y=='x'||x=='X'&&y=='X')
			;
		else if(x=='Y'&&y=='Y')
			;
		//以上满足条件，啥也不用做。 
		else
		{
			f = 0;//不满足条件，f 设置成 0。 
			break;//及时跳出循环。 
		}
	}
	//根据 f 的值来输出。
	//注意是 NIE 而不是 NTE ！！！ 
	printf("%s\n",f?"TAK":"NIE");
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

# 题意
  给出一个只有小写字符字符串，判断它是否对称。如果对称输出 TAK ，否则输出 NIE 。

# 思路

  本题被恶意评分 ， 细节非常多 。
  
1.  如果这个字符串长度是奇数 , 那么中间的字符一定是一个轴对称的字母 。


2.  除了中间的字符，其他字符只有两种可能 ：

$ \ \ \ \  \ \ \ ( 1 ) $ 轴对称字符

        ( 注意 ：同样的字符必须要在左右对称的位置  ) 
    
$ \ \ \ \  \ \ \ ( 2 ) $ ‘ b ’ 对 ‘ d ’ 或者 ‘ p ’ 对‘ q ’ 

        ( 注意 ：‘ b ’‘ d ’ 或 ‘ p ’‘ q ’ 必须要在左右对称的位置 )
   
$ ( $ 轴对称字母有 : A 、 H 、 I 、 M 、 O 、 T 、 U 、 V 、 W 、 X 、 Y 、 o 、 v 、 w 、 x  $  ) $ 

# 代码

```
#include<bits/stdc++.h>
using namespace std;
int check1(char x,char y)
{
    if(x=='A'&&y=='A')
        return 0;
    if(x=='H'&&y=='H')
        return 0;
    if(x=='I'&&y=='I')
        return 0;
    if(x=='M'&&y=='M')
        return 0;
    if(x=='O'&&y=='O')
        return 0;
    if(x=='T'&&y=='T')
        return 0;
    if(x=='U'&&y=='U')
        return 0;
    if(x=='V'&&y=='V')
        return 0;
    if(x=='W'&&y=='W')
        return 0;
    if(x=='X'&&y=='X')
        return 0;
    if(x=='b'&&y=='d')
        return 0;
    if(x=='d'&&y=='b')
        return 0;
    if(x=='o'&&y=='o')
        return 0;
    if(x=='q'&&y=='p')
        return 0;
    if(x=='v'&&y=='v')
        return 0;
    if(x=='w'&&y=='w')
        return 0;
    if(x=='x'&&y=='x')
        return 0;
    if(x=='p'&&y=='q')
        return 0;
    if(x=='Y'&&y=='Y')
    	return 0;
    return 1;
} 
int check2(char x)
{
	if(x=='A')
	    return 0;
	if(x=='H')
  	 	return 0;
	if(x=='I')
 	  	return 0;
	if(x=='M')
    	return 0;
	if(x=='O')
 	  	return 0;
    if(x=='T')
 	  	return 0;
	if(x=='U')
 	  	return 0;
	if(x=='V')
	   	return 0;
	if(x=='W')
	   	return 0;
	if(x=='X')
   		return 0;
	if(x=='Y')
	   	return 0;
   if(x=='o')
	   	return 0;
   if(x=='v')
	   	return 0;
	if(x=='w')
	   	return 0;
	if(x=='x')
	   	return 0;
	return 1;
}
string st;
int ln,f;
int main()
{
	cin>>st;
	ln=st.size();
	for(int i=0;i<ln/2;i++)
		if(check1(st[i],st[ln-i-1])==1){
			f=1;
			break;
        }
    if(f==0){
    	if(ln%2==0){
            printf("TAK\n");
    		return 0;
        }
       if(ln%2==1)
           if(check2(st[ln-ln/2-1])==0){
               printf("TAK\n");
    		   return 0;
           }
    }
    printf("NIE\n");
    return 0;
}
请勿抄题解

```

---

## 作者：Node_Edge (赞：0)

这题可以把自己本身左右对称的字母和与其对称的字母建立一个映射，这里用字符数组存，由于太多，请看向代码。

判断一个字符串是否对称，可以建立两个变量，$i$ 指向字符串开头，$j$ 指向字符串结尾，每次循环 $i \gets i+1$ 且 $j \gets j-1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
char f[500];
string s;
//建立映射
void xyz(){
    f['A']='A';f['H']='H';f['I']='I';f['M']='M';f['O']='O';f['T']='T';f['U']='U';
    f['V']='V';f['W']='W';f['X']='X';f['Y']='Y';f['b']='d';f['d']='b';f['o']='o';
    f['p']='q';f['q']='p';f['v']='v';f['w']='w';f['x']='x';
}
int main(){
    cin>>s;
    xyz();
    int i=0,j=s.size()-1;
    //判断对称
    while(i<=j){
        if(f[s[i]]!=s[j]){
            cout<<"NIE";
            return 0;
        }
        i++,j--;
    }
    cout<<"TAK";
    return 0;
}
```


---

## 作者：取名困难症 (赞：0)

恶意评分的题。。。
-----------------

字符串头和尾诶个比较就行了，不用特殊判断，~~懂英语就行~~

重点在于会不会少判断，我因此卡了两次才过。。。

上代码：
--
```
#include<bits/stdc++.h>
using namespace std;
int pd(char x,char y)
{
    if(x=='A'&&y=='A')
        return 0;
    if(x=='H'&&y=='H')
        return 0;
    if(x=='I'&&y=='I')
        return 0;
    if(x=='M'&&y=='M')
        return 0;
    if(x=='O'&&y=='O')
        return 0;
    if(x=='T'&&y=='T')
        return 0;
    if(x=='U'&&y=='U')
        return 0;
    if(x=='V'&&y=='V')
        return 0;
    if(x=='W'&&y=='W')
        return 0;
    if(x=='X'&&y=='X')
        return 0;
    if(x=='b'&&y=='d')
        return 0;
    if(x=='d'&&y=='b')
        return 0;
    if(x=='o'&&y=='o')
        return 0;
    if(x=='q'&&y=='p')
        return 0;
    if(x=='v'&&y=='v')
        return 0;
    if(x=='w'&&y=='w')
        return 0;
    if(x=='x'&&y=='x')
        return 0;
    if(x=='p'&&y=='q')
        return 0;
    if(x=='Y'&&y=='Y')
    	return 0;
    return 1;
 } 
 int pd2(char x)
 {
 	if(x=='A')
 	return 0;
 	if(x=='H')
 	return 0;
 	if(x=='I')
 	return 0;
 	if(x=='M')
 	return 0;
 	if(x=='O')
 	return 0;
    if(x=='T')
 	return 0;
 	if(x=='U')
 	return 0;
 	if(x=='V')
 	return 0;
 	if(x=='W')
 	return 0;
 	if(x=='X')
 	return 0;
 	if(x=='o')
 	return 0;
    if(x=='v')
 	return 0;
     if(x=='w')
 	return 0;
 	if(x=='x')
 	return 0;
 	if(x=='Y')
 	return 0;
 	return 1;
 }
 int main()
 {
 	string str;
 	cin>>str;
 	int len=str.size();
 	int f=0;
 	for(int i=0;i<len/2;i++)
 	{
 		if(pd(str[i],str[len-i-1])==1)
 		{
 			f=1;
 			break;
         }
     }
     if(f==0)
     {
     	if(len%2==0)
     	{
     		cout<<"TAK"<<endl;
     		return 0;
         }
        if(len%2==1)
        {
            if(pd2(str[len-len/2-1])==0)
            {
                cout<<"TAK"<<endl;
     			return 0;
            }
        }
     }
     cout<<"NIE"<<endl;
 }//别抄题解

```


---

## 作者：liuyifan (赞：0)

## 可读性高一点的题解
解法和下面差不多,加了一些优化

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
using namespace std;
string s;
int main()
{
	cin>>s;
	if(s.length()%2==0)
	{
		for(reg int i=0;i<s.length()/2;i++)
		if(!((s[i]=='A'&&s[s.length()-i-1]=='A')||(s[i]=='b'&&s[s.length()-i-1]=='d')||(s[i]=='d'&&s[s.length()-i-1]=='b')||(s[i]=='x'&&s[s.length()-i-1]=='x')||(s[i]=='X'&&s[s.length()-i-1]=='X')||(s[i]=='U'&&s[s.length()-i-1]=='U')||(s[i]=='V'&&s[s.length()-i-1]=='V')||(s[i]=='v'&&s[s.length()-i-1]=='v')||(s[i]=='W'&&s[s.length()-i-1]=='W')||(s[i]=='w'&&s[s.length()-i-1]=='w')||(s[i]=='Y'&&s[s.length()-i-1]=='Y')||(s[i]=='p'&&s[s.length()-i-1]=='q')||(s[i]=='q'&&s[s.length()-i-1]=='p')||(s[i]=='O'&&s[s.length()-i-1]=='O')||(s[i]=='o'&&s[s.length()-i-1]=='o')||(s[i]=='H'&&s[s.length()-i-1]=='H')||(s[i]=='I'&&s[s.length()-i-1]=='I')||(s[i]=='M'&&s[s.length()-i-1]=='M')||(s[i]=='T'&&s[s.length()-i-1]=='T')))return puts("NIE"),0;
        //暴力判断
		return puts("TAK"),0;
	}
	if(s[(s.length()-1)/2]!='A'&&s[(s.length()-1)/2]!='O'&&s[(s.length()-1)/2]!='o'&&s[(s.length()-1)/2]!='M'&&s[(s.length()-1)/2]!='W'&&s[(s.length()-1)/2]!='T'&&s[(s.length()-1)/2]!='H'&&s[(s.length()-1)/2]!='I'&&s[(s.length()-1)/2]!='U'&&s[(s.length()-1)/2]!='X'&&s[(s.length()-1)/2]!='x'&&s[(s.length()-1)/2]!='V'&&s[(s.length()-1)/2]!='v'&&s[(s.length()-1)/2]!='w'&&s[(s.length()-1)/2]!='Y')return puts("NIE"),0;
	for(reg int i=0;i<=(s.length()-1)/2-1;i++)
    //继续暴力
	if(!((s[i]=='A'&&s[s.length()-i-1]=='A')||(s[i]=='b'&&s[s.length()-i-1]=='d')||(s[i]=='d'&&s[s.length()-i-1]=='b')||(s[i]=='x'&&s[s.length()-i-1]=='x')||(s[i]=='X'&&s[s.length()-i-1]=='X')||(s[i]=='U'&&s[s.length()-i-1]=='U')||(s[i]=='V'&&s[s.length()-i-1]=='V')||(s[i]=='v'&&s[s.length()-i-1]=='v')||(s[i]=='W'&&s[s.length()-i-1]=='W')||(s[i]=='w'&&s[s.length()-i-1]=='w')||(s[i]=='Y'&&s[s.length()-i-1]=='Y')||(s[i]=='p'&&s[s.length()-i-1]=='q')||(s[i]=='q'&&s[s.length()-i-1]=='p')||(s[i]=='O'&&s[s.length()-i-1]=='O')||(s[i]=='o'&&s[s.length()-i-1]=='o')||(s[i]=='H'&&s[s.length()-i-1]=='H')||(s[i]=='I'&&s[s.length()-i-1]=='I')||(s[i]=='M'&&s[s.length()-i-1]=='M')||(s[i]=='T'&&s[s.length()-i-1]=='T')))return puts("NIE"),0;
	puts("TAK");
	return 0;
}
```

---

## 作者：wzq731201 (赞：0)

活生生的暴力打表，
因为要对称，所以先判断长度，如果是偶数，长度为2n，则将1到n与2n到n+1一一比较，判断是否对称，其中对称的有......自己看代码吧其中p和q，b和p以及它们反一下不能遗落，如果是奇数，则只要比偶数多判一下中间那个字母是否左右对称即可，对称的有……还是看下面。

特别要注意的是看表，不是书写体所以不能忘了“U”“v”“w”这些书写体不对称但在该题对称的字母

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string mmp;
ll len,cnm;
int main()
{cin>>mmp;
len=mmp.length();
if(len%2==0)
{for(int i=0;i<=len/2-1;i++)
if((mmp[i]=='A'&&mmp[len-i-1]=='A')||(mmp[i]=='b'&&mmp[len-i-1]=='d')||(mmp[i]=='d'&&mmp[len-i-1]=='b')||(mmp[i]=='x'&&mmp[len-i-1]=='x')||(mmp[i]=='X'&&mmp[len-i-1]=='X')||(mmp[i]=='U'&&mmp[len-i-1]=='U')||(mmp[i]=='V'&&mmp[len-i-1]=='V')||(mmp[i]=='v'&&mmp[len-i-1]=='v')||(mmp[i]=='W'&&mmp[len-i-1]=='W')||(mmp[i]=='w'&&mmp[len-i-1]=='w')||(mmp[i]=='Y'&&mmp[len-i-1]=='Y')||(mmp[i]=='p'&&mmp[len-i-1]=='q')||(mmp[i]=='q'&&mmp[len-i-1]=='p')||(mmp[i]=='O'&&mmp[len-i-1]=='O')||(mmp[i]=='o'&&mmp[len-i-1]=='o')||(mmp[i]=='H'&&mmp[len-i-1]=='H')||(mmp[i]=='I'&&mmp[len-i-1]=='I')||(mmp[i]=='M'&&mmp[len-i-1]=='M')||(mmp[i]=='T'&&mmp[len-i-1]=='T')) continue;
else 
{cout<<"NIE";
return 0;
}
}
else{
cnm=(len-1)/2;
if(mmp[cnm]!='A'&&mmp[cnm]!='O'&&mmp[cnm]!='o'&&mmp[cnm]!='M'&&mmp[cnm]!='W'&&mmp[cnm]!='T'&&mmp[cnm]!='H'&&mmp[cnm]!='I'&&mmp[cnm]!='U'&&mmp[cnm]!='X'&&mmp[cnm]!='x'&&mmp[cnm]!='V'&&mmp[cnm]!='v'&&mmp[cnm]!='w'&&mmp[cnm]!='Y')
{cout<<"NIE";
return 0;
}
for(int i=0;i<=cnm-1;i++)
if((mmp[i]=='A'&&mmp[len-i-1]=='A')||(mmp[i]=='b'&&mmp[len-i-1]=='d')||(mmp[i]=='d'&&mmp[len-i-1]=='b')||(mmp[i]=='x'&&mmp[len-i-1]=='x')||(mmp[i]=='X'&&mmp[len-i-1]=='X')||(mmp[i]=='U'&&mmp[len-i-1]=='U')||(mmp[i]=='V'&&mmp[len-i-1]=='V')||(mmp[i]=='v'&&mmp[len-i-1]=='v')||(mmp[i]=='W'&&mmp[len-i-1]=='W')||(mmp[i]=='w'&&mmp[len-i-1]=='w')||(mmp[i]=='Y'&&mmp[len-i-1]=='Y')||(mmp[i]=='p'&&mmp[len-i-1]=='q')||(mmp[i]=='q'&&mmp[len-i-1]=='p')||(mmp[i]=='O'&&mmp[len-i-1]=='O')||(mmp[i]=='o'&&mmp[len-i-1]=='o')||(mmp[i]=='H'&&mmp[len-i-1]=='H')||(mmp[i]=='I'&&mmp[len-i-1]=='I')||(mmp[i]=='M'&&mmp[len-i-1]=='M')||(mmp[i]=='T'&&mmp[len-i-1]=='T')) continue;
else 
{cout<<"NIE";
return 0;
}
}
cout<<"TAK";
return 0;
}
```

---

