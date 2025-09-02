# New Year and Counting Cards

## 题目描述

翻译：

你的朋友有N张牌。

每一张卡片上都有一个小写的英文字母和一个数字。

现在，你的朋友已经把卡片放在了一张桌子上，所以每张卡片只有一面可见。你很想知道你的朋友对所拥有的卡片的描述是否正确：“如果一张卡片上有一个元音，那么它的另一面一定是一个偶数”(元音是“A”、“E”、“I”、“O”或“u”的一个，偶数是“0”、“2”、“4”、“6”或“8”的一种)。

例如，如果一张牌的一面是“A”，另一面有“6”，那么这句话是对的。此外，一张有“B”和“4”的卡片，以及一张有“B”和“3”的卡片的描述也是正确的（因为字母不是元音）。

而有“E”和“5”的卡是错误的。

如果所有的卡都是符合要求的，你会感兴趣。另外，如果没有卡是元音，描述是真的。

为了确定这一点，你可以翻转一些卡片来显示另一面。你想知道在最坏的情况下需要翻转的最小卡片数。

## 样例 #1

### 输入

```
ee
```

### 输出

```
2
```

## 样例 #2

### 输入

```
z
```

### 输出

```
0
```

## 样例 #3

### 输入

```
0ay1
```

### 输出

```
2
```

# 题解

## 作者：引领天下 (赞：4)

这回是真正的题解了


其实思路楼上已经说过，我只是来一发C++的


代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int ans;
bool k[256];//我选择了用桶进行优化，这样减少了代码，也变快了
int main(){
    k['a']=k['o']=k['e']=k['i']=k['u']=k['1']=k['3']=k['5']=k['7']=k['9']=true;//打表，需要翻过来的定义为true（1）
    cin>>s;
    for (int i=0;i<s.size();i++)ans+=(k[s[i]]);//直接进行计算
    cout<<ans;
    return 0;
}
```

---

## 作者：hswfwkj_ (赞：2)

~~咕值又掉了，赶紧涨回来。~~

本题其实就是让你求一个字符串里有多少个元音字母和奇数。理由如下：
- 如果牌上是辅音字母，那不管它后面是什么数字这张牌都是合法的。
- 如果牌上是偶数，那不管另一面是元音还是辅音，这张牌也是合法的。

那么，我们可以得出：
- 如果牌这面是元音，那么我们需要翻一下验证它背面是不是偶数。
- 如果这张牌这面是奇数，那么我们需要翻一下验证它背面是不是辅音。

明确思路之后，我们就可以很轻松的写出代码啦！贴上我的代码，给大家作为参考：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	char c[10001];
	int i,ans=0;
	cin>>c;
	for(i=0;i<strlen(c);i++){
		if(c[i]=='a'||c[i]=='A'||c[i]=='e'||c[i]=='E'||c[i]=='i'||c[i]=='I'||c[i]=='o'||c[i]=='O'||c[i]=='u'||c[i]=='U')
		ans++;
		if(c[i]=='1'||c[i]=='3'||c[i]=='5'||c[i]=='7'||c[i]=='9')
		ans++;
	}
	cout<<ans;
	return 0;
}

```
最后，大家如果觉得我的题解对你们有帮助的话，请挪动你们的手指给我点一个赞，你们的支持就是对我最大的鼓励！

---

## 作者：thomas_zjl (赞：1)

很水，模拟就可以了。

首先理解一下题意，要翻的牌为元音字母和为奇数的数。

元音字母：$Aa,Ee,Ii,Oo,Uu$。

为奇数的数：$1,2,3,4,5$。

注意，字母区分大小写。

来看看代码吧。

```
#include<bits/stdc++.h> 
using namespace std;
int main() 
{
	int sum=0;
	string a;
	cin>>a;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]=='A'||a[i]=='a')//判断这个字符是否为A或a。
		{
			sum++;
		}
		if(a[i]=='E'||a[i]=='e')//判断这个字符是否为E或e。
		{
			sum++;
		}
		if(a[i]=='I'||a[i]=='i')//判断这个字符是否为I或i。
		{
			sum++;
		}
		if(a[i]=='O'||a[i]=='o')//判断这个字符是否为O或o。
		{
			sum++;
		}
		if(a[i]=='U'||a[i]=='u')//判断这个字符是否为U或u。
		{
			sum++;
		}
		if(a[i]=='1')//判断这个字符是否为1。
		{
			sum++;
		}
		if(a[i]=='3')//判断这个字符是否为3。
		{
			sum++;
		}
		if(a[i]=='5')//判断这个字符是否为5。
		{
			sum++;
		}
		if(a[i]=='7')//判断这个字符是否为7
        。
		{
			sum++;
		}
		if(a[i]=='9')//判断这个字符是否为9。
		{
			sum++;
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：to_be_continued (赞：1)

这题是英文题刚开始我很迷茫，后来经过翻译这题其实很水

异常简单。

意思如下

输入一个串

并将这个串进行统计，如果有‘a’‘e’‘i’‘o’‘u’则累加

或有单数也累加

最后将累加值输出。

多么easy啊


  
```cpp
var
  i,j,l,k,m,n:longint;
  s:ansistring;//不管先开这个这个。不虚
begin
  readln(s);
  for i:=1 to length(s) do
    if ord(s[i])>59 then //对元音字母进行处理
      case s[i] of 
        'a':inc(m);
        'e':inc(m);
        'i':inc(m);
        'o':inc(m);
        'u':inc(m);
      end
    else 
    begin//对技术进行处理
      k:=ord(s[i])-48;
      if odd(k) then inc(m);
    end;
  writeln(m);//不虚的输出
end.
```

---

## 作者：清清老大 (赞：0)

## 思路

题目要求验证“如果一张卡片上有一个元音，那么它的另一面一定是一个偶数”是否正确，所以：

- 如果卡的正面是元音，则要翻过来验证反面是否是偶数。
- 如果卡的正面是奇数，则要翻过来验证反面是否是元音。

按照上面的思路模拟就可以了。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    int sum = 0;
    cin >> s;
    for(int i = 0;i < s.length();i ++)
    {
        if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == '1' || s[i] == '3' || s[i] == '5' || s[i] == '7' || s[i] == '9')
        {
            sum ++;
        }
    }
    cout << sum;
}
```


---

## 作者：阳歌童圣 (赞：0)

欢迎来到CF908A号游泳池，我是教练冰块

这道题是一道类似按条件找东西的游戏，这种题交给代码是再适合不过了。

题目给了我们一堆只能看到一面的纸牌，上面可能是**小写字母**，也可能是**数字**；

目的是要让我们将一些纸片翻面。

现在题目又给了我们需要翻面纸片的条件：

- 如果纸片上是小写字母，它如果是元音字母（及 ‘a’,  ‘e’，‘i’，‘o’，‘u’其中一个），它就需要翻转查看背面是否是偶数。


- 如果纸片上是数字，它如果是奇数，它就需要翻转查看背面是否是元音（这里要注意，题目中已经说明“如果是偶数，它的背面一定是偶数”，所以只要翻转奇数即可）

题目中还说“你想知道在最坏的情况下需要翻转的最小卡片数”，指明我们要一一检查。

给你（输入）纸片，要你输出在保证你能确定所有牌的情况下的最小翻转次数。

好了，下面就是我们代码的时间了，代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int ans;
char a[51];
int main(){
scanf("%s",a);//用字符串的方式将长度不一的纸片字母输入
int len=strlen(a);//检测输入的字符串长度。
for(int i=0;i<len;i++){
if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u') ans++;
if(a[i]=='1'||a[i]=='3'||a[i]=='5'||a[i]=='7'||a[i]=='9') ans++;

}//检查
cout<<ans;//输出
return 0;//完结散花
} 
```
我们也可以把代码写的更花一点，如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int ans;
char a[51];
#define special(m) for(int i=0;i<m;i++)
int wow(int k){
	if(k=='a'||k=='e'||k=='i'||k=='o'||k=='u') ans++;
    if(k=='1'||k=='3'||k=='5'||k=='7'||k=='9') ans++;
    return ans;
}
signed main(){
scanf("%s",a);
int len=strlen(a);
special(len){
wow(a[i]);
}
cout<<ans;//输出
return 0;//完结散花
} 
```


好了，这道题就结束了，大家千万要自己写，代码仅供参考。

---

## 作者：昊月星辰 (赞：0)

#### 首先审题：

有若干张卡片，每张卡片都有一个小写字母和一个数字。
 
 然后让你判断“如果一张卡片上有一个元音，那么它的另一面一定是一个偶数”这句话是否正确。
 
 思路很好想，如果一个卡片露出来的那一面是一个元音，那么你需要翻开它来验证背面是否为偶数。如果是辅音的话就不用翻了，必然合法。反之，如果是偶数，就不用翻开验证，如果是奇数就需要翻开验证。
 
 $AC \  \ Code:$
 ```cpp
#include<bits/stdc++.h>

using namespace std;

string a;

int sum=0;

int main(){
	cin>>a;\\读入
	int len=a.size();
	for(int i=0;i<len;i++){
		if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u'||a[i]=='1'||a[i]=='3'||a[i]=='5'||a[i]=='7'||a[i]=='9') sum++;\\判断是否需要翻开
	}
	cout<<sum;\\输出
	return 0;
}
```


---

## 作者：Keep_RAD (赞：0)

其实题目看着那么绕（以至于刚看以为这一道题是黄题），把它归归类其实很简单：

如果这个字母是辅音字母（不是$a$ $e$ $i$ $o$ $u$）,那么这张牌一定是对的，不需要翻；

如果这个字母是元音字母（$a$ $e$ $i$ $o$ $u$），那么需要翻开看一看是不是对的，对不对应偶数，```sum++```；

如果这个是偶数数字，那么一定是对的，不需要翻；

如果这个是奇数数字，那么需要翻开看对不对应元音字母，如果对应就是错的，```sum++```;

清晰了吧！

具体实现看代码：

```
#include<bits/stdc++.h> 
using namespace std;
char a[55];
int main() 
{
	int sum=0;
	getline(cin,a);
	for(int i=0;i<a.size();i++)
	{
		if(a[i]=='a')  //题目说了小写字母，只是翻译不准确，不需判断大写
			sum++;
		if(a[i]=='e')
			sum++;
		if(a[i]=='i')
			sum++;
		if(a[i]=='o')
			sum++;
		if(a[i]=='u')
			sum++;
		if(a[i]=='1')
			sum++;
		if(a[i]=='3')
			sum++;
		if(a[i]=='5')
			sum++;
		if(a[i]=='7')
			sum++;
		if(a[i]=='9')
			sum++;
	}
	cout<<sum;
	return 0;
}
```

懂了吗？

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 张卡牌，每张卡牌上只会有大小写字母和 $0\sim 9$ 的阿拉伯数字。有这样一个描述：“如果卡牌正面写有元音字母（$\texttt{A,E,I,O,U}$ 五个字母中的一个），那么它的反面必然是偶数”。你很想知道这个描述是否正确，因此你可以选择翻开一些卡牌来验证这个描述。求最坏情况下至少需要翻开的牌的数量。

**数据范围：$1\leqslant n\leqslant 50$。**
## Solution
我们只需要找到元音字母和**奇数**的牌翻开就行。为什么是奇数？因为这样的话如果反面是元音字母，那么就可以证明这个描述是错误的。
## Code
```cpp
int main() {
	string s;
	int ans = 0;
	cin >> s;
	for(int i = 0; i < s.size(); ++i)
		ans += (s[i] == 'A' || s[i] == 'a' || s[i] == 'E' || s[i] == 'e' || s[i] == 'I' || s[i] == 'i' || s[i] == 'o' || s[i] == 'O' || s[i] == 'U' || s[i] == 'u' || s[i] == '1' || s[i] == '3' || s[i] == '5' || s[i] == '7' || s[i] == '9');
	writeint(ans);
	return 0;
}
```

---

## 作者：江山_远方 (赞：0)

本题是一道水题$QwQ$~~我也只会做水题了~~  
读入了一个字符串，问你有多少个字符需要判定  
需要判定即为本卡牌露出来的字符可能出现错误，出现错误即为元音字母遇上了奇数牌，那么假如一个字符是元音或者奇数，那么就要翻牌判定啦。  
所以我萌就可以在每一位上枚举，最后把需要判定的次数加起来就好啦.  
代码如下:
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int ans;
int main()
{
	cin>>st;//读入
	for(int i=0;i<st.size();i++)if(st[i]=='a'||st[i]=='e'||st[i]=='i'||st[i]=='o'||st[i]=='u'||(st[i]>='0'&&st[i]<='9'&&(st[i]-'0')%2==1))ans++;//如果是元音或者是奇数，那么就要翻牌
	cout<<ans;//输出
}
```
~~AC抱回家~~

---

## 作者：GusyNight (赞：0)

**题意：**
```
有一堆卡片，每张牌一面是数字一面是字母。题目给出了一个规则：只要牌面是元音字母则它的对照面一定是偶数，然后给你一个字符串，问最少翻多少张最终判断这些牌面对照是对的
```

**题解：**
```
根据题目我们可以分析得到：元音字母对应的一定是偶数，我们必须逆转元音字母看否是偶数，其次是奇数逆转看是否是非元音字母。
```

```cpp
#include <bits/stdc++.h>
using namespace std;
bool temp(char c){
    if(c ='a'||c=='e'||c=='i'||c=='o'||c =='u')return true;
    return false;
}
int main(){
    string str;
    cin>>str;
    int siz = str.length();
    int cnt=0;
    for(int i=0;i<siz;i++){
       if(temp(str[i]))cnt++;
       else if(!isalpha(str[i])&&(str[i]-'0')&1)cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}
```

---

## 作者：凌幽 (赞：0)

...思考题...
```
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
#define R register

char s[60];
int len,Ans;

int main()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	for(R int i=1;i<=len;++i)
		if(s[i]>='0' && s[i]<='9' && s[i]-48&1) Ans++; 
		// 若卡牌正面为奇数,翻开,若卡牌背面是元音字母则不合法 
		else if(s[i]=='a' || s[i]=='e' || s[i]=='i' || s[i]=='o' || s[i]=='u') Ans++; 
		// 若卡牌正面为元音字母,翻开,若卡牌背面是奇数则不合法 
	printf("%d",Ans);
	return 0;
}
```

---

