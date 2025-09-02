# [NOIP 2008 普及组] ISBN 号码

## 题目描述

每一本正式出版的图书都有一个 ISBN 号码与之对应，ISBN 码包括 $9$ 位数字、$1$ 位识别码和 $3$ 位分隔符，其规定格式如 `x-xxx-xxxxx-x`，其中符号 `-` 就是分隔符（键盘上的减号），最后一位是识别码，例如 `0-670-82162-4`就是一个标准的 ISBN 码。ISBN 码的首位数字表示书籍的出版语言，例如 $0$ 代表英语；第一个分隔符 `-` 之后的三位数字代表出版社，例如 $670$ 代表维京出版社；第二个分隔符后的五位数字代表该书在该出版社的编号；最后一位为识别码。

识别码的计算方法如下：

首位数字乘以 $1$ 加上次位数字乘以 $2$ ……以此类推，用所得的结果 $ \bmod 11$，所得的余数即为识别码，如果余数为 $10$，则识别码为大写字母 $X$。例如 ISBN 号码 `0-670-82162-4` 中的识别码 $4$ 是这样得到的：对 `067082162` 这 $9$ 个数字，从左至右，分别乘以 $1,2,\dots,9$ 再求和，即 $0\times 1+6\times 2+……+2\times 9=158$，然后取 $158 \bmod 11$ 的结果 $4$ 作为识别码。

你的任务是编写程序判断输入的 ISBN 号码中识别码是否正确，如果正确，则仅输出 `Right`；如果错误，则输出你认为是正确的 ISBN 号码。


## 说明/提示

2008 普及组第一题


## 样例 #1

### 输入

```
0-670-82162-4```

### 输出

```
Right```

## 样例 #2

### 输入

```
0-670-82162-0```

### 输出

```
0-670-82162-4```

# 题解

## 作者：合451518 (赞：21)

又是一道水题。

计算方面就不细说了，主要来说一说这一题最后的判断和易错点。

开始看题目时，没有看到s mod 11 =10时验证码为‘X’，WA50..

输出的判断稍不留神就会错。

可以这样判断：

1）如果s mod 11=ord(st[13])-48 （//st[13]是验证码，此时'0'<=st[13]<='9'） 或者 （s mod 11=0 and st[13]=‘X’）（//单独判断余数为'X'的情况 ） 时输出Right;

2）否则（一定是出问题了）

先输出字符串的前十二位，再输出自己算的验证码，注意还要讨论'X'的情况...

代码：

 
 
```cpp
var
 st:ansistring;
 i,s,n:longint;
begin
 readln(st);
 n:=0;
 s:=0;
 for i:=1 to 11 do
  if st[i]<>'-' then begin
   inc(n);
   inc(s,(ord(st[i])-48)*n);
  end;
 if (s mod 11=ord(st[13])-48) or (s mod 11=10) and (st[13]='X') then write('Right')
  else begin
   for i:=1 to 12 do write(st[i]);
   if s mod 11<10 then write(s mod 11) else write('X');
  end;
end.
```

---

## 作者：aj_pj (赞：19)

[题面传送门](https://www.luogu.com.cn/problem/P1055)

用枚举除了最后一位数字之外的数字和，然后模掉 
$11$，在特判一下最后一位是 $10$ 的情况，就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,c,d,e,f,g,h,i,s1,s2;
	char j;
    scanf("%1d-%1d%1d%1d-%1d%1d%1d%1d%1d-%c",&a,&b,&c,&d,&e,&f,&g,&h,&i,&j);
    s1=(a*1+b*2+c*3+d*4+e*5+f*6+g*7+h*8+i*9)%11;
    if(j=='X')
		s2=10;
    else
		s2=j-'0';
		
    if(s1==s2)
    cout<<"Right";
    else if(s1==10)
    cout<<a<<"-"<<b<<c<<d<<"-"<<e<<f<<g<<h<<i<<"-X";
    else
    cout<<a<<"-"<<b<<c<<d<<"-"<<e<<f<<g<<h<<i<<"-"<<s1;
	return 0;
}


```
也可以这样写

```cpp

#include<bits/stdc++.h>
using namespace std;
int main()
{
char s[14];
int a[14],m=0;
cin>>s;
a[1]=s[0]-'0';
a[2]=s[2]-'0';
a[3]=s[3]-'0';
a[4]=s[4]-'0';
a[5]=s[6]-'0';
a[6]=s[7]-'0';
a[7]=s[8]-'0';
a[8]=s[9]-'0';
a[9]=s[10]-'0';
 if(s[12]=='X')
      a[10]=10;
   else
   a[10]=s[12]-'0';
for(int i=1;i<=9;i++)
    {
       m+=a[i]*i;
     }
    m%=11;
 if(m==a[10])
    cout<<"Right";
 else   
    {for(int i=0;i<12;i++)
        cout<<s[i];
    if(m==10)
       cout<<'X';
    else
       cout<<m;
    }
return 0;
}



```
撒花！！！完美结束！！！

~~这是本蒟蒻第1次写题解，希望管理员大大通过。~~

---

## 作者：pomelo_nene (赞：19)

看了各位大佬的题解，我突然发现没人发string类型的

但是大家可能会问：

string到底怎么做？

string类型有一个函数，叫做：

##.at(int)##

它的作用是：提取字符串中间int+1个字符，相当于一个小小的数组

同时，大家也可以用char数组来做

代码简洁明了，希望大家喜欢。
```cpp
#include<cstring>
#include<iostream>
using namespace std;
string s;
int main(){
	cin>>s;//string类型只能够用cin读入
	int tell=s.at(0)-48+(s.at(2)-48)*2+(s.at(3)-48)*3+(s.at(4)-48)*4+(s.at(6)-48)*5+(s.at(7)-48)*6+(s.at(8)-48)*7+(s.at(9)-48)*8+(s.at(10)-48)*9;//得到应该得到的值：因为at返回的是一个字符，所以说要减去'0'（48），根据题意，得到这个算式
	char right=tell%11+48;//正确的最后一位的值
	if(right>'9')	right='X';//因为module 11 之后可能会有10，根据题意得到'X'
	if(right==s.at(12))	cout<<"Right";//如果相等，那就是正确的
	else//否则
	{
		for(int i=0;i<=11;++i)	cout<<s.at(i);//从0~10输出前面的字符
		cout<<right;//然后输出正确的最后一位
	}
	return 0;
}
```
注意！！！

如果要使用at，千万不要超过输入的字符串的位数！

~~你会发现一大堆一大堆的字符对在你面前，然后停止运行~~

---

## 作者：ikunTLE (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/P1055)

### 思路

一道**模拟**题。

首先将字符串 $S$ 除最后一位每一个数字位存到 `int` 类型的序列 $A$ 中，那么 $A$ 就变成了一个长度为 $9$ 的序列。然后用 $i$ 遍历 $A$，第 $i$ 位要乘对应的 $A_i$，所以统计出数字总和为 $\sum_{i=1}^9A_i\times i$。

然后需要将其对 $11$ 取模，得到一个整数 $C$。这时将输入的字符串中最后一位与 $C$ 比较，若相同输出 `Right`，否则将去掉最后一位的字符串与得到转为 `char` 的 $C$ 拼接输出。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=15;
char s[N];
int main(){
	scanf("%s",s);
	int a[]={0,s[0]-'0',s[2]-'0',s[3]-'0',s[4]-'0',s[6]-'0',s[7]-'0',s[8]-'0',s[9]-'0',s[10]-'0'};
	int sum=0;
	for(int i=1;i<=9;++i)
		sum=(sum+(a[i])*i)%11;
	char ch;
	if(sum==10)
		ch='X';
	else ch=sum+'0';
	if(ch==s[12])
		printf("Right\n");
	else printf("%d-%d%d%d-%d%d%d%d%d-%c\n",a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],ch);
	return 0;
}
```

---

## 作者：Cold_Eyes_bystander (赞：5)

考虑模拟。

我们提取关键信息，发现这是个诈骗题，我们枚举字符串，对于每一个不是最后一位的数字字符串，我们都把他们转为数字去计算。

但怎么算了？我们知道 0 的 ASCII 码是 48，剩下的数字一次加一，那我们减去 48 就是我们想要的结果了，这时我们只用枚举就行了。

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    string s;
    cin>>s;
    int cnt=1;
    int sum=0;
    for(int i=0;i<s.size()-1;i++)
    {
      	if(s[i]!='-')
        {
            sum+=((s[i]-48)*cnt)%11;
            cnt++;
        }
    }
    sum%=11;
    if(sum==10)
    {
        if(s[s.size()-1]=='X')
        {
            cout<<"Right";
        }
        else
        {
            for(int i=0;i<s.size()-1;i++)
            {
                cout<<s[i];
            }
            cout<<"X";
        }
    }
    else 
    {
        if((s[s.size()-1]-48)==sum)
        {
            cout<<"Right";
        }
        else
        {
            for(int i=0;i<s.size()-1;i++)
            {
                cout<<s[i];
            }
            cout<<sum;
        }
    }
    return 0;
}
```

---

## 作者：qhr2023 (赞：4)

## solution

小模拟。

我们按照题意算出给定字符串正确的识别码，再和给定的识别码比较，若不相等则把给定识别码改为正确识别码，注意特判识别码为 $10$ 的情况。

[通过记录](https://hydro.ac/record/6788ace34299fffd5438c3c4)。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int l, n, sum; 
string s;
int main(){
	cin >> s;
	l=s.size();
	for (int i=0; i<l-1; ++i)
		if (s[i]>='0'&&s[i]<='9')
			sum+=(s[i]-'0')*(++n);
	if (sum%11+'0'==s[l-1]||(sum%11==10&&s[l-1]=='X'))
		puts("Right");
	else
		s[l-1]=(sum%11==10?'X':sum%11+'0'),
		cout << s;
	return 0;
}
```

---

## 作者：WsW_ (赞：3)

### 思路
按题意模拟即可。  
首先输入字符串 $s$，把最后一位识别码扔掉，再把剩下的字符串中所有的数字按题意加起来并算出正确的识别码。  
最后判断输入的识别码和算出来的识别码是否相同。如果相同，则输出 `Right`；否则把识别码换一下然后输出正确的 ISBN 号码。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100];
int main(){
	scanf("%s",a);
	int x=0;
	int sum=0;
	for(int i=0;i<=10;i++){
		if(isdigit(a[i])){
			x++;
			sum+=(x*(a[i]-'0'));
		}
	}
	if(a[12]=='X')x=10;
	else x=a[12]-'0';
	sum%=11;
	if(sum==x)printf("Right");
	else{
		for(int i=0;i<=11;i++)cout<<a[i];
		if(sum==10)printf("X");
		else printf("%d",sum);
	}
	return 0;
}
```

---

## 作者：mairuisheng (赞：2)

[P1055 [NOIP2008 普及组] ISBN 号码](https://www.luogu.com.cn/problem/P1055)

算法：模拟

分析：先把前面的数字按题目要求得到乘积，再把所得乘积取模得到余数，再检验它是否与识别码相同，如果相同，输出 `Right`；否则把除了识别码的字符串按顺序输出，最后输出余数，注意：当余数为十时，输出 `X`。
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[14];
long long i,sum=0,co,j=0;
int main()
{
	for(i=1;i<=13;i++)
	{
		cin>>a[i];
		if(a[i]!='-'&&i!=13)
		{
			j++;
			sum+=(a[i]-48)*j;
		}
	}
	if(a[13]=='X')co=10;
	else
	{
		co=(a[13]-48);
	}
	if(sum%11==co)
	{
		cout<<"Right";
		return 0;
	}
	else
	{
		for(i=1;i<=12;i++)
		{
			cout<<a[i];
		}
		if(sum%11!=10)cout<<sum%11;
		else cout<<"X";
	}
	return 0;
}
```

---

## 作者：MCbucket (赞：2)

[题目传送门](https://www.luogu.com.cn/progenblem/P1055#submit)

是一道字符串水题，只用枚举除了最后一位数字之外的数字和，然后模掉 $11$，在特判一下最后一位是 $10$ 的情况，就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	char s[14],c;//s是ISBN号码，c是最后一位
	cin>>s;
	int h=0,k=0;//h是ISBN号码的和，k是号码的编号
	for(int i=0;i<11;i++){
		if(s[i]!='-'){
			k++;//编号加1
			h+=k*(s[i]-'0');//和加上编号*数字
		}
	}
	h%=11;//和模上11是题目意思
	if(h==10)c='X';//特判是10的情况
	else c=h+'0';
	if(c==s[12])cout<<"Right"<<endl;
	else{
		s[12]=c;//修改成对的
		cout<<s;
	}
	return 0;
}
```

这是本蒟蒻第一次写题解，请求管理员通过吧！

---

## 作者：GZXUEXUE (赞：1)

### 思路

简单字符串模拟。观察到「ISBN号码」长度较短，考虑直接模拟。

我们定义两个变量 $\text{ans}$ 和 $\text{index}$，分别表示正确的识别码和当前遍历到的位置，每次发现「ISBN号码」中的字符 `-` 就换到下一个字符，对于非字符 `-` 的数字字符就令 $\text{ans}$ 累加计算。

遍历完成后，我们对比变量 $\text{ans}$ 这个「ISBN号码」的最后一位数即可，注意特判当最后一位是字符 `X` 是 $\text{ans}$ 应该等于 $10$。

最后，我们输出 `Right` 或正确的「ISBN号码」即可，$\text{ans} = 10$ 时最后一位应该是 `X`。

时间复杂度为 $O(L)$。其中，$L = 9$，表示「ISBN号码」的长度。

### 实现

```cpp
# include <iostream>
# include <cstring>
using namespace std;
int main(){
	string isbn;
	cin >> isbn;
	int ans = 0,index = 0;
	for (int base = 1;base <= 9;base++){ // base表示当前这一位要乘几
		if (isbn[index] == '-') index++;
		int num = isbn[index] - '0';
		ans += base * num;
		ans %= 11;
		index++;
	}if (isbn[isbn.size()-1] == 'X' && ans == 10){
		cout << "Right";
	}else if (ans == (isbn[isbn.size()-1] - '0')){
		cout << "Right";
	}else if (ans != 10){
		cout << isbn.substr(0,isbn.size()-1) << ans;
	}else{
		cout << isbn.substr(0,isbn.size()-1) << "X";
	}return 0;
}
```

---

## 作者：niuniudundun (赞：1)

# P1055 [NOIP2008 普及组] ISBN 号码题解

## 题目大意

编写程序判断输入的 ISBN 号码中识别码是否正确，如果正确，则仅输出 `Right`；如果错误，则输出正确的 ISBN 号码。

## 解法

这题主要就是计算识别码，依题意模拟即可。

设 ISBN 码的数字为 $a_{1\cdots 9}$，计算 $\displaystyle \sum_{i=1}^{9} i\times a_i$，对和 $\bmod 11$，判断给定识别码是否为余数，是输出 `Right`，否则输出余数。

代码：

复杂度：$O(l)$，$l$ 是 ISBN 号码长度。

```cpp
#include<iostream>
#include <cstring>
using namespace std;
char a[13],mod[12]="0123456789X";
int main(){
//	for(int i=0;i<13;i++) cin>>a[i];
	cin>>a;
	int sum=0,j=1;
	for(int i=0;i<12;i++){
		if(a[i]>='0'&&a[i]<='9'){
			sum=sum+(a[i]-'0')*j;
			j++;
		}
	}
	sum=sum%11;
//	cout<<mod[sum]<<" "<<sum<<endl;
	if(mod[sum]==a[12]){ 
		cout<<"Right"<<endl;
	}
	else{
		a[12]=mod[sum];
		printf("%s",a);
	}
	return 0;
}
```

---

## 作者：lucky_Mrzhao (赞：1)

## 思路

由于数据过小，考虑模拟。

将输入的号码中的 `-` 先全部过滤，紧接着将每一位数字与 `1` 到 `9` 中的每一位数字相乘，最后求出识别码，如果识别码相等，则输出 `Right` ，否则将最后一位更改为正确的识别码即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string k = "0123456789X";
int main()
{
	char a[25];
	int ans = 1,sum = 0;
	for(int i = 1;i <= 13;i++){
		cin >> a[i];
		if(a[i]!='-'&&i!=13){
			sum += (a[i]-'0') * ans;
			ans++;
		}
	}
	sum %= 11;
	if(a[13]==k[sum]){
		cout << "Right";
		return 0;
	}
	else{
		for(int i = 1;i <= 12;i++) cout << a[i];
		cout << k[sum]; 
	}
	return 0;
}
```

---

## 作者：zjinyi (赞：1)

# 题解：P1055 ISBN 号码
## 题目大意
给定一个 **ISBN 号码**，你的任务是编写程序判断输入的 ISBN 号码中识别码是否正确，正确则输出 `Right`；错误则输出正确的号码。（2008 普及组第一题）

## 题目分析
这道题的题面看起来比较长，但大部分都没有什么用。只需要根据题意计算识别码，再判断识别码是否正确，就能得出答案。

首位数字乘以 $1$ 加上次位数字乘以 $2$ ……以此类推，用所得的结果求余 $11$，所得的余数即为 ISBN 号码的识别码。

只需要遍历 ISBN 号码，并用一个 `cnt` 变量每次加 `1`，乘上每一位数字并求余 $11$，并从一个字符数组中找出余数代表的识别码，最后判断即可。要注意余数为 `10` 时识别码为 `X`。

## 代码
```cpp
#include <iostream>
using namespace std;

char c[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'X'}; // 字符数组，第 i 个字符表示余数 i 的识别码 
int main()
{
	string s;
	cin >> s; // 输入 ISBN 号码 
	int cnt = 1, sum = 0;
	for (int i = 0; i < s.size() - 1; ++i) // 遍历 ISBN 号码  
	{
		if (s[i] == '-') // 只计算数字的乘积 
		{
			continue;
		}
		sum += (s[i] - '0') * cnt; // 将乘积求和 
		cnt += 1;
	}
	char ans = c[sum % 11]; // sum 对 11 求余，得到识别码 
	if (ans == s[s.size() - 1]) // 判断识别码是否正确 
	{
		cout << "Right";
	}
	else
	{
		for (int i = 0; i < s.size() - 1; ++i) // 输出正确的识别码 
		{
			cout << s[i];
		}
		cout << ans;
	}
	return 0;
}
```

---

## 作者：kunkun127 (赞：1)

## 思路

这篇题解讲一下字符串模拟。

我们直接用 `scanf` 读入，然后用 `to_sting` 函数转换，并连接为一个字符串。按照题意计算识别码，再看识别码是否匹配。匹配就输出 `Right`；不匹配，就输出正确的 ISBN 号码。

## 注意事项

- `10` 应该表示为 `X`。
- 输出正确的 ISBN 号码记得输出 `-`。
- 如使用 `to_string` 函数，应在 C++11 环境下运行，用处就是将变量转换为字符串。

## 参考代码


```cpp
#include <bits/stdc++.h>
#define lsq using
#define love namespace
#define hyh std
lsq love hyh;

int main()
{
	int t, a, b, sum = 0;
	char c;
    scanf("%d-%d-%d-%c", &t, &a, &b, &c);
    string s = to_string(t) + to_string(a) + to_string(b);
    for (int i = 0; i < 9; i++) sum += int((s[i] - '0') * (i + 1));
    sum %= 11;
    char ch = sum + '0';
    if (sum == 10) ch = 'X';
    if (c == ch) cout << "Right" << endl;
    else printf("%d-%d-%d-%c\n", t, a, b, ch);
	return 0;
}

```

---

## 作者：Ak_hjc_using (赞：0)

## 思路
我们可以考虑使用字符串处理与模拟来实现本题。

我们可以按照题目中给定的规则，计算出识别码，再判断是否与给定的识别码相同：

- 如果相同，输出 `Right`。
  
- 如果不同，输出正确的字符串。
### 时间复杂度
我们把每个字符处理了一遍，因此总时间复杂度是 $O(n)$、

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

int main() {
  string str;
  cin >> str;
  int sum = 0;
  for (int i = 0, j = 1; i + 1 < str.size(); i++) {
    if (str[i] != '-') {
      sum += (str[i] - '0') * j;
      j++;
    }
  }
  sum %= 11;
  char c = 'X';
  if (sum < 10) {
   c = '0' + sum;
  }
  if (c == str.back()) {
    puts("Right");
  }
  else {
    str.back() = c;
    cout << str << endl;
  }
  return 0;
}
```

---

## 作者：Jerry_zpl (赞：0)

本题算法：模拟。\
难度建议：红。\
本题难度较小，主要思路如下：

- 首先，题目给我们的号码有一个特点：号码的长度是一样的且都是数字。所以我们可以用字符变量一个一个的输入。
- 号码乘积如和算捏？根据题目给我们的信息，我们可以得知：号码乘积就是第一位的数字乘一加上第二位的数字乘二的和一直加到第九位的数字乘九的和。
- 如果乘积对 $11$ 取模的结果是 $10$ 并且最后一位是 `X` 就是特殊情况，输出 `Right`。
- 否则修改号码即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    char a;
    char b,c,d;
    char e,f,g,h,i;
    char j;
    char x1,x2,x3;
    cin>>a>>x1>>b>>c>>d>>x2>>e>>f>>g>>h>>i>>x3>>j;
    int ans1=(a-'0')*1+(b-'0')*2+(c-'0')*3+(d-'0')*4+(e-'0')*5+(f-'0')*6;
    int ans2=(g-'0')*7+(h-'0')*8+(i-'0')*9;
    int ans=ans1+ans2;
    if(ans%11==10&&j=='X') 
    {
    	cout<<"Right";
    	return 0;
	}
    int x=j-'0';
    if(ans%11==x) cout<<"Right";
    else if(ans%11==10)  cout<<a<<x1<<b<<c<<d<<x2<<e<<f<<g<<h<<i<<x3<<'X';
    else cout<<a<<x1<<b<<c<<d<<x2<<e<<f<<g<<h<<i<<x3<<ans%11;
	return 0;
} 
```

---

## 作者：Malkin_Moonlight (赞：0)

## Solution

简单模拟题。先来一个字符串 $s$，拿来输入那一串号码，再维护一个变量 $cnt$ ，表示现在识别到第 $cnt$ 个数字，和一个变量 $sum$，表示目前总和。接下来遍历字符串，判断当前位置是否为数字，如果是，那么 $cnt$ 加上 $1$，再让这个数字乘上 $cnt$，累加到 $sum$ 中。最后判断识别码是否正确，正确输出 `Right`，错误就把号码最后一位（识别码）改成 $sum$ 取模 $11$ 的值，再输出。

注意在判断识别码是否正确时别忘了还有个特殊情况，也就是识别码是 `X`，要特判一下。

代码不放了，很好写。

---

## 作者：FastIO_DP (赞：0)

## 题目大意

每一本正式出版的图书都有一个 ISBN 号码，格式为 `x-xxx-xxxxx-x`，其中 `-`  是分隔符，最后一位是识别码。题目中识别码的计算方法：

$$
\text{识别码} = \left( \sum_{i=1}^{9} s_i \times i \right) \bmod 11
$$

其中，$s_i$ 表示第 $i$ 位数字。如果余数为 10，则识别码为 `X`。

输出的是判断输入的 ISBN 号码的识别码是否正确，如果正确，输出 `Right`；否则，输出正确的 ISBN 号码。

## 解题步骤

首先提取输出的 ISBN 码的数字。
其次计算识别码：

- 将提取的 9 位数字分别乘以 1 到 9 的权重，累加求和。

- 对和取模 11，得到识别码。如果余数为 10，识别码为 `X`；否则为余数对应的数字。

最后然后比较识别码，如果一致，输出 `Right`；否则，修正识别码并输出正确的 ISBN 号码。

## 代码实现

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    char s[14]; // ISBN 号码最多 13 字符 + 1 结束符
    scanf("%s", s);

    int sum = 0, cnt = 1; // sum 为加权和，cnt 为当前权重
    for (int i = 0; i < 11; i++) {
        if (s[i] == '-') continue; // 跳过分隔符
        sum += (s[i] - '0') * cnt++; // 加权累加
    }

    char check = (sum % 11 == 10) ? 'X' : (sum % 11 + '0'); // 计算识别码
    if (check == s[12]) {
        puts("Right"); // 识别码正确
    } else {
        s[12] = check; // 修正识别码
        puts(s); // 输出正确的 ISBN 号码
    }

    return 0;
}
```

## 复杂度分析

- **时间复杂度**：$O(1)$，因为 ISBN 号码长度固定，遍历次数为常数。
- **空间复杂度**：$O(1)$，仅使用固定大小的字符数组。

---

## 作者：sjh0626 (赞：0)

## 思路分析
我们根据题意模拟就好，判断正确是很简单的，就是一直读入和取模，但是输出正确的号码要花一点时间。

因为要判断识别码是不是 $10$，还要把原本的识别码替换掉，这就需要麻烦一点。
## 代码解析
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    int sum=0,j=0;
    cin>>s;
    for(int i=0;i<12;i++){
    	if(s[i]!='-'){
			j++,sum+=(s[i]-'0')*j;
		}
		sum%=11;
	}
	sum%=11;
	if(sum==10)sum='X';
	else sum='0'+sum;
	if(int(s[12])!=sum){
		s.replace(12,1,"");
		cout<<s<<char(sum);
	}
	else cout<<"Right";
}
```

---

