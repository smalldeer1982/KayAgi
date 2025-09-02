# Way Too Long Words

## 题目描述

有时候，像“localization”或“internationalization”这样的词汇如此之长，以至于在一篇文章中多次写下这些词语令人厌烦。

让我们考虑一个词太长，如果它的长度严格超过 10个字符。太长的单词应该用一个特殊的缩写代替。

这个缩写是这样写的：我们写下一个单词的第一个和最后一个字母，并在它们之间写出第一个和最后一个字母之间的字母数。该数字是十进制系统，不包含任何前导零。

因此，“localization”将拼写为“l10n”，而“internationalization”将拼写为”i18n”。

建议您使用缩写来自动更改单词的过程。因为所有太长的单词应该用缩写代替，不太长的单词不应该经历任何改变。

## 样例 #1

### 输入

```
4
word
localization
internationalization
pneumonoultramicroscopicsilicovolcanoconiosis
```

### 输出

```
word
l10n
i18n
p43s
```

# 题解

## 作者：封禁用户 (赞：16)

这道题思路灰常的明确...就是~~一个字~~暴力
```cpp
#include<bits/stdc++.h>\\传说中的万能头文件
using namespace std;
int main()
{
	
    int n;//n个单词
	string a;//...单词
	int i;
	cin>>n;//输入
	for(i=0;i<n;i++)
	{
		cin>>a;//在每个循环内输入单词
	 	if(a.length()>10)//计算单词长度
	 	{
	 	      cout<<a[0]<<a.length()-2<<a[a.length()-1]<<endl;//如果大于十就要输出第一个字符和最后一个，注意中间长度要减二
		 }
		 else
		 {
		 	cout<<a<<endl;//否则直接输出
		 }
	} 
	return 0;
}//华丽结束，这是本蒟蒻的第一篇题解如果哪位大佬能认真地看到这，深表感谢。

```

---

## 作者：wuyutong111 (赞：3)

```pascal
这道题真是很水，就是先判断这个字符串是否小于等于10，如果是，你们原样输出，不是的话输出字符串第一个字符，字符串长度-2（因为去掉首和末），字符串的最后一个字符。
话不多说，看看我的程序----
var
 i,n:longint;
 s:ansistring;
begin
 readln(n);//有n个字符串需输入
 for i:=1 to n do
  begin
   readln(s);//
   if length(s)<=10 then writeln(s)//如过字符串长度小于等于10就原样输出
                    else
                       writeln(s[1],length(s)-2,s[length(s)]);//不然的话，你知道的...【上面有↑
 end;
end.
```
请不要抄袭，谢谢！

---

## 作者：Aw顿顿 (赞：2)

这道题考察字符串

看以下代码我们继续讲解：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1001][1001];
int n=0;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		if(strlen(a[i])<=10)cout<<a[i]<<endl;
		else cout<<a[i][1]<<strlen(a[i])-2<<a[i][strlen(a[i])-1]<<endl;
	}
	return 0;
}
```

这个代码当中，首先输入n

接着开启一个**循环次数为n**的for循环

接着输入字符串，这里用了一个判断

然后这个代码WA了

为什么？

我改了一下思路

其实没有必要开**二维字符数组**

应该直接用字符串

可是我忽然发现：WA评测点$\ne$AC评测点个数

大就有了这个代码：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n;
string a; 
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        cin>>a;
        if(a.size()>10)cout<<a[0]<<a.size()-2<<a[a.size()-1]<<endl;
		else cout<<a<<endl;
    }
    return 0;
}

```
$\bigstar$用string~~果然比用char更好~~

---

## 作者：Zirnc (赞：1)

这道题很容易，判断一下。
如果字符串的长度大于 10，那就用缩写。否则就直接输出字符串。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s.size() > 10) 
        { //                减去头和尾，就是 -2
            cout << s[0] << s.size()-2 << s[s.size()-1] << endl;
        } else {
            cout << s << endl;
        }
    }
    return 0;
}
```


---

## 作者：k2saki (赞：1)

没什么可以说，其实就是暴力模拟，直接上代码吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    string s;
    for(int i=1;i<=n;++i)//多组测试数据
    {
        cin>>s;//读入
        if(s.size()>10)//如果大于十
        {
            cout<<s[0]<<s.size()-2<<s[s.size()-1]<<endl;//输出首字母，长度-2，末字母
        }//判断长度是否大于10
        else cout<<s<<endl;
    }
}
```

---

## 作者：SKTelecomT1_Faker (赞：0)

这道题目较为简单，思路是这样的：先输入组数，再从1到n做循环，再定义字符串并输入，判断其长度.

如果>10就输出首位，字符串长度-2，末位，其余的情况直接输出原本的字符串即可。
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
signed main( )//主函数
{
    int n;
    cin>>n;//输入数据组数
    for(register int i=1;i<=n;i++)//做循环方便输入
    {
        string s;//定义字符串
        cin>>s;//输入
        if(s.size()>10) cout<<s[0]<<s.size()-2<<s[s.size()-1]<<endl;//判断长度之后输出首位，字符串长度-2，末位
        else cout<<s<<endl;//无脑输出
    }
	exit(0);//好习惯伴我们一生
}
```
既然这篇文章提到了string，我们不妨来介绍一下它的用法：

string是C++、java、VB等编程语言中的字符串，字符串是一个特殊的对象，属于引用类型。 C++标准库中string类以类型的形式对字符串进行封装，且包含了字符序列的处理操作。在c++中头文件是#include<cstring>（string或string.h均可qaq）

int capacity()const; //返回当前容量（即string中不必增加内存即可存放的元素个数）

int max_size()const; //返回string对象中可存放的最大字符串的长度

int size()const; //返回当前字符串的大小

int length()const; //返回当前字符串的长度

bool empty()const; //当前字符串是否为空

void resize(int len,char c);//把字符串当前大小置为len，并用字符c填充不足的部分

这些都是一些常用技巧，string类长度用size求，为string(你自己设的未知量）.size(),读入用cin或scanf（记住是%s），输出用cout或printf（记住也是%s）相加后直接把两个拼在一起等。

希望对大家有帮助qwq。



---

## 作者：向日葵小班 (赞：0)

# $\color{red}\text{这是一道大水题}$
**$\color{red}\text{不就是i18n的加强版吗，虽然只加强了一点点（手动滑稽），但我还要做一做}$**

**$\color{red}\text{太水不讲，直接放代码吗}$**

## 放代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n;//定义n
string a[110];//定义字符串
int main()
{
     cin>>n;//输入n
	 for(int i=1;i<=n;i++)//循环n次
	 cin>>a[i];//输入a[i] 
	 for(int i=1;i<=n;i++)//循环n次
	 {
	 	if(a[i].size()>10)cout<<a[i][0]<<a[i].size()-2<<a[i][a[i].size()-1]<<endl;//如果a[i]的长度大于10，cout<<a[i][0]<<a[i].size()-2<<a[i][a[i].size()-1]<<endl;
	 	else cout<<a[i]<<endl;//否则，cout<<a[i]<<endl;
	 }
    return 0;//完美结束
}
```



---

## 作者：可爱的小白 (赞：0)

这题很简单，判断一下长度是否大于10，输出就行了
废话不多说，直接上代码
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
long long n;//定义一个n 
string s[100000+1];//再定义一个字符串 
int main()
{
	cin>>n;//输入n 
	for(int i=1;i<=n;i++)  cin>>s[i];//输入字符串 
	for(int i=1;i<=n;i++)
	{
		if(s[i].size()>10)  cout<<s[i][0]<<s[i].size()-2<<s[i][s[i].size()-1]<<endl;//如果字符串长度超过10，就输出第一个字符和最后一个字符，中间 
		else    cout<<s[i]<<endl;//否则输出整个字符串 
	}

	return 0;
}
```


---

## 作者：开心的猪 (赞：0)

这道题的关键只有两个字：暴力！！！

对每一个单词进行如下操作：

第一步：读入字符串

第二步：判断长度，如果长度小于等于10，直接打印，如果长度大于10，执行第三步

第三步：打印第一个字符，打印字符数-2，打印最后一个字符，以上步骤按顺序进行。

以下是代码：

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int a;
	scanf("%d", &a);
	char b[100]={0};
	for(int i=0; i<a; i++)
	{
		cin>>b;
		if(strlen(b)>10)
		{
			printf("%c%d%c\n", b[0], strlen(b)-2, b[strlen(b)-1]);
		}
		else
		{
			printf("%s\n", b);
		}
	}
	return 0;
}
```


---

## 作者：TCZN (赞：0)

这道题有坑啊（对于蒟蒻我来说）

在输入样例那里我一直以为是有⑤个单词，

然后就一直没注意，最后还以为要输出“word”这个单词，

导致蒟蒻一直错，

最后是看到题解才幡然醒悟

## 进入正题：

思路：很多人可能会想到怎样输出，

其实只要把3个字符合并在一起就行了
```
var
  i,j,s,n:longint;
  a:array[1..123] of string;
begin
 readln(n);
  for i:=1 to n do
   readln(a[i]);  //蒟蒻专属读入方法
     for i:=1 to n do
      if length(a[i])>10 then //如果字符大于10就输出
       begin
        write(a[i][1],length(a[i])-2,a[i][length(a[i])]); //一定要用write，writeln会有空格
        writeln; //换行
       end
        else writeln(a[i]); //不然输出这个字符
end.
```


---

## 作者：土间太平 (赞：0)

## 为P党带来一篇入门题解

思路很简单，每次读入之后进行判读即可

# Code
```
var n,i,len:longint;//len 表示长度
    s:string;
begin
 readln(N);
 for i:=1 to n do
  begin
   readln(s);
   len:=length(s);
   if len>10 then//注意是严格大于，没有等号
    begin
     write(s[1]);
     write(len-2);
     writeln(s[len]);
    end else
    begin
     writeln(s);
    end;
  end;
end.
```

---

## 作者：PC_DOS (赞：0)

直接按照题目要求模拟即可。

首先读入字符串sInput，之后判断其长度iLength，如果大于10，则依次输出sInput[0]、iLength、sInput[iLength-1]、换行符；否则直接输出sInput和换行符即可。

代码:
```
#include <iostream>
#include <string>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nCount, iLength; //nCount-个数；iLength-长度
	register int i; //循环计数器
	string sInput; //字符串
	cin >> nCount; //读入个数
	for (i = 1; i <= nCount; ++i){ //逐个读入字符串
		cin >> sInput; //读入
		iLength = sInput.length(); //计算长度
		if (iLength > 10) //如果长度大于10
			cout << sInput[0] << iLength - 2 << sInput[iLength - 1] << endl; //依次输出sInput[0]、iLength、sInput[iLength-1]、换行符
		else //否则
			cout << sInput << endl; //直接输出sInput和换行符
	}
	return 0; //结束
}
```

---

## 作者：人间凡人 (赞：0)

题目大意：输入$n$个字符串，如果长度大于10，就依次输出第一个字符、长度$-2$、最后一个字符。否则就输出原串。

模拟样例：

$word$ 长度4 小于10 直接输出原串。

$localization$ 长度12 大于10 输出$l10n$。

思路：求出字符串的长度$len$，判断一下即可,没什么好说的吧。

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,len;
char s[105];
int main() {
	scanf("%d%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s);len=strlen(s);
		if(len>10)
			printf("%c%d%c\n",s[0],len-2,s[len-1]);
		else printf("%s\n",s);
	}
	return 0;
}

```


---

