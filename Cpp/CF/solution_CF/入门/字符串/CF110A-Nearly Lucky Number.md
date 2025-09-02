# Nearly Lucky Number

## 题目描述

### 题目要求
如果一个数仅包含4和7，那么它就是一个"幸运数字"。
如果一个数**本身不是**幸运数，但是它所含有的数字4和7的个数之和为一个"幸运数字"，那么它就是一个"类幸运数字"。
给您一个数，请编程判断它是不是"类幸运数字"。

## 样例 #1

### 输入

```
40047
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
7747774
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
1000000000000000000
```

### 输出

```
NO
```

# 题解

## 作者：williamlyz (赞：7)

**题意**

输入一个数，其中4和7的数量是否为4或者7，是则输出‘YES’，否则输出‘NO’。

**思路**

~~超级无敌大水题~~

先统计数中4和7的数量，再看看这个数是不是4或者7；

我们可以用字符串来做，把这个数当成一个字符串，再把字符串从头到尾枚举，如果是4或者7，计数器加1；最后再用计数器的最终值来判断是否为4或者7。

话不多说，直接上代码
```cpp
#include<bits/stdc++.h>	//万能头，用string类 
using namespace std;
int main()
{
	string a;
	int sum=0;//计数器 
	cin>>a;
	for(int i=0;i<=a.length();i++)//a.length()为string类中用来计算字符串的长度，也可以是a.size(),为什么后面再说 
	{
		if(a[i]=='4'||a[i]=='7')//如果字符串中某一位是'4'或者'7',计数器就加一； 
		{
			sum++;
		}
	}
	if(sum==4||sum==7)//计数器的值是否为4或者7； 
	{
		cout<<"YES";
	}
	else
		cout<<"NO";
	return 0;//养成好习惯； 
}



```
**补充：为什么string类中 .length()和 .size()一样**

我们来看看这两个函数的源代码:

.length():

![](https://cdn.luogu.com.cn/upload/image_hosting/lbme2prl.png)

.size():

![](https://cdn.luogu.com.cn/upload/image_hosting/yj6ufnfs.png)

可以发现没有任何区别，只有名字不同，所以这就是为什么这两个函数做用一样。。。

---

## 作者：test_check (赞：4)

[$\huge CF110A \  Nearly  \ Lucky  \ Number$](https://www.luogu.org/problem/CF110A)    
还是一道比较不错的题目，可以拿来练练手$(QAQ)$。

------------
题目中虽说$n$在$long \  long$范围内，但不知为什么，我一看到要分解数字就想用**字符串**做。   
$$First:\text{输入}$$
输入因为太$(wo)$简$(mei)$单$(xie)$了，~~就不说了（逃）~~   

------------
$$Second:\text{正式解决问题}$$
因为要判断$n$是否为"类幸运数字"，所以，我们可以开一个自定义函数```pd1```,函数的类型应该是```bool```，因为要判断是否为"类幸运数字"吗。   
```cpp
bool pd1(string s)  //自定义函数
{
	int t=0;  //计数器清零
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='7'||s[i]=='4')
	    t++;  //如果数是'4'或'7'的话，计数器++
	}
	if(pd2(t)) return 1;  //判断计数器是否符合条件
	return 0;   //不符合条件，返回0
}
```
嘿，本代码还没写完整，看到代码中的这一句了吗```if(pd2(t)) return 1;``` ```pd2(t)```又是什么鬼？别急别急，我们再给出一下代码：
```cpp
bool pd2(int n)
{
	if(n==0) return 0;  //没有'4'或'7' ，返回0
	while(n!=0)
	{
		if(n%10!=7)
		{
			if(n%10!=4)
			return 0;  //不符合条件，返回0
		}
		if(n%10!=4)
		{
			if(n%10!=7)
			return 0;  //不符合条件，返回0
		}
		n/=10;
	}   //分解n
	return 1;   //一定符合条件，返回1
}
```

------------

好了，大致内容就这些，下面给出完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool pd2(int n)
{
	if(n==0) return 0;
	while(n!=0)
	{
		if(n%10!=7)
		{
			if(n%10!=4)
			return 0;
		}
		if(n%10!=4)
		{
			if(n%10!=7)
			return 0;
		}
		n/=10;
	}
	return 1;
}
bool pd1(string s)
{
	int t=0;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='7'||s[i]=='4')
	    t++;
	}
	if(pd2(t)) return 1;
	return 0;
}
int main()
{
	string s;
	cin>>s;
	if(pd1(s)) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
}
```

---

## 作者：A_Đark_Horcrux (赞：2)

这题真的折腾了我好久……

大家看到题目一定都有疑问：幸运数字到底算不算类幸运数字？如果算，为什么题目里没讲？如果不算，为什么样例2输出YES？

#### 幸运数字是不算类幸运数字的，样例2输出YES是因为它有五个7和两个4，共有七个4或7，而7是幸运数字！

#### 那么，47、747、777777不是类幸运数字，而1526384656778884是类幸运数字。题意就其实是：统计一个数里4和7的个数，看个数是不是一个幸运数字。

代码如下。

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
char a[150],c[150]; long long i,s; bool f;
int main()
{
	scanf("%s",a);
	for(i=0;i<=strlen(a)-1;i++)
		s+=(a[i]=='4'||a[i]=='7');//统计一个数里4和7的个数
	sprintf(c,"%lld",s);//用sprintf把个数转成字符串
	for(i=0;i<=strlen(c)-1;i++)
		if(c[i]!='4'&&c[i]!='7')//判断这个字符串是不是只有4和7组成
			return !printf("NO\n");//如果有别的数字输出NO
	puts("YES");//判断完成输出YES
	return 0;
} //sprintf自行百度
```

---

## 作者：静静是他的， (赞：2)


题中 4 和 7 是幸运数字
问题是要求一个数的 各个位 是 幸运数字 的 个数 
是不是 幸运数字 
```
#include<iostream>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cmath>

using namespace std;

string st;
int ans;//统计幸运数字的个数

int main()
{
    cin>>st;//输入这个数字
    for(int j=0;j<st.size();j++)
    	if (st[j]=='4'||st[j]=='7') ans++;//判断各个位是不是幸运数字，是的话就加一
    if (ans==4||ans==7) puts("YES");//最后判断ans的个数是不是幸运数字
	else puts("NO");
    return  0;
}
```

---

## 作者：可爱的小白 (赞：1)

本题题意是：如果一个数仅包含4和7，那么它就是一个"幸运数字"。 如果一个数本身不是幸运数，但是它所含有的数字4和7的个数之和为一个"幸运数字"，那么它就是一个"类幸运数字"。 给您一个数，请编程判断它是不是"类幸运数字"。     
上代码                       
```cpp
#include<bits/stdc++.h>//万能头文件，应该都知道
using namespace std;
string s;//10的18次方就是10000000000000000000，太大，用字符串 
int ans;//一个计数器 
int main()
{
	cin>>s;//输入字符串 
	for(int i=0;i<s.size();i++)//一个for循环 
	{//一个大括号 
		if(s[i]=='4' || s[i]=='7')  ans++;//如果有 ，计数器++ 
	}
	if(ans==4 || ans==7)  cout<<"YES";//如果 计数器是一个幸运数字，那么输出YES； 
	else    cout<<"NO";//否则输出NO 
	
	return 0;//就这么愉快的结束了 
}//我们下次再见 
```
本次题解已结束，下次再见

---

## 作者：Franka (赞：0)

### **题目**
问一个数是不是"**类幸运数字**"。

类幸运数字是指**不是**幸运数，但它**4和7的个数** _是_ 一个**幸运数**的数。

幸运数表示**只含有4和7的数**。
### **思路**
因为题目中给出了这个数小于int64，那我们不妨把int64算出来。

int64的最大**正**整数的范围：$2^{63}-1=9223372036854775807$。

数一数，刚好**19**位。

**假设**这个数的4和7的个数是一个**两位数**，那么就**不可能**是类幸运数字了。
#### 所以只用判断这个数中4和7的个数是不是4和7中的一个就行了。
### **代码**
```pascal
var
 n:int64;//n的范围是int64
 s:longint;//s代表4和7个数的总数
begin
 readln(n);//读入n
 while(n<>0)do//拆分n
  begin
   if(n mod 10=7)or(n mod 10=4)then inc(s);//如果是4或7中的一个，s累加
   n:=n div 10;//分解
  end;
 if(s=4)or(s=7)then writeln('YES')//判断是否是类幸运数字
               else writeln('NO');//否则输出NO
end.
```


---

## 作者：午尘 (赞：0)

做个水题都WA……ε=(´ο｀*)))唉

先放代码吧~

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,m,i,j,k,s,ans,t,len,tf;
char st[100001],ch[100001];
int main(){
   cin>>st;
   len=strlen(st);
  /* tf=1;
   for (i=0;i<=len-1;i++)
     if (st[i]!='4' && st[i]!='7') tf=0;
   if (tf)   { cout<<"YES"<<endl; return 0; }*/
   s=0;
   for (i=0;i<=len-1;i++)
     if (st[i]=='4' || st[i]=='7')  s++;
   if (s==4 || s==7) cout<<"YES"<<endl;
                else cout<<"NO"<<endl;
  return 0;
}
```

被注释掉的那部分是因为题意有误？。。

```
如果一个数本身不是幸运数，但是它所含有的数字4和7的个数之和为一个"幸运数字"，那么它就是一个"类幸运数字"。
```
应该是本身没有关系啦~

然后倒数第三四行的话，也可以一步步除以10和mod10，但有点麻烦。

因为位数少，就特判喽~

---

## 作者：HAO233 (赞：0)

看了下好像没人用$stringstream$的。。。   
这道题的解法很简单：先统计出$s$中$4$和$7$的个数，然后再相加，判断相加后的和是否只由$4$和$7$构成。

那么我们如何统计一个数是否仅由$4$和$7$构成呢？很简单，把这个数转换为字符串就行了，那么如何把一个数字简单的转换为字符串呢？这里就可以用$C++$的特性—— $stringstream$

$ stringstream$是一个很方便的东西，其用法类似于$iostream$，可以很方便的完成字符串与数字，数字与字符串之间的转换。举个例子：

```cpp
	string s;//定义一个字符串
	stringstream ss;//定义一个字符串流变量
    int a = 3;//定义一个int类型的变量
    ss << a;
    ss >> s;//现在s为"3"了
    s="4";
    ss.clear();//清空
    ss << s;
    ss >> a;//此时a为4
    cout << a;
```

是不是比$sprintf$看起来方便？原生的$string$支持，便捷的操作，大部分类型都可以转。

好了，下面就是使用$stringstream$的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;
int n;

int main() {
    cin >> s;
    for (int i = 0; i < s.length(); i ++) {
        if (s[i] == '4' || s[i] == '7') n ++;//统计4和7的数量
    }
    stringstream ss;
    ss << n;
    ss >> s;//转换为字符串
    for (int i = 0; i < s.length(); i ++) {
        if (s[i] == '4' || s[i] == '7') {
            continue;
        } else {
            cout << "NO";//如果不由4和7构成，那么输出NO
            return 0;
        }
    }
    cout << "YES";
    return 0;
}
```



---

## 作者：不到前10不改名 (赞：0)

```
#include<stdio.h>
long long srx,sry;//三年OI一场空，不开LongLong见祖宗（2333，我就是~qwq）
int main()
{
    scanf("%lld",&srx);
    while(srx)//按位分解
    {if(srx%10==4||srx%10==7)//4和7是幸运数字
    sry++;//统计幸运数字数
    srx/=10;}//分离
    if(sry==4||sry==7)//因为最多只有20位（longlong），所以只会有4和7两种
    printf("YES");
    else
    printf("NO");
    return 0;
}
```

---

## 作者：HoshizoraZ (赞：0)

如何不写 "<string>" 与 ".size( )" ? 很简单。

每个字符串在结尾都会有一个 " \0 "

因此，只要一个字符串出现了它，便是这个字符串的末尾了。

所以写循环时来一句 for( i=0 ; c[i] != '\0' ; i++ )即可

写上代码：
```
	#include<bits/stdc++.h>
	using namespace std;
	int main(){
    	int i,s=0;
    	char c[64];
    	gets(c);
    	for(i=0;c[i]!='\0';i++)
   			if(c[i]=='4'||c[i]=='7') s++;//累加出现4和7的次数
            
    	if(s==0){			//本人就曾倒在这个坑里（看样例三）
        	printf("NO");
        	return 0;
    	}
    	while(s!=0){		//检查每一位是否为4或7，不是的结束，注意，虽然题目数据出现4或7的次数为一位数，但不排除有s=47等可能。
        	if(s%10!=4&&s%10!=7){	//所以这样写更妥善
            	printf("NO");
            	return 0;
        	}
        	s/=10;			 //去尾
    	}
    	printf("YES"); 		//没结束的输出YES
    	return 0;			  //搞定
	} 
```

---

## 作者：封禁用户 (赞：0)

我发现没有人写“length()”，“length()”会很伤心的，那我就发一篇吧。
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int main()
{
    string a;
    int tot=0,len;
	cin>>a;
    len=a.length();//计算a字符串的长度
	for(int i=0;i<len;i++)
    if (a[i]=='4'||a[i]=='7') 
	tot++;
    if(tot==4||tot==7) //判断
	cout<<"YES"<<endl;
    else
	cout<<"NO"<<endl;
    return  0;//AC
}
```
求过

---

