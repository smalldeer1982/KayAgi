# Mike and palindrome

## 题目描述

麦克有一个只有小写英文字母的字符串 _s_ 。他想通过改变一个字符 的方式来让整个字符串成为回文字符串。

回文字符串是一个正着读和反着读都一样的字符串。比如说"z"， "aaa"，"aba"， "abccba"是回文字符串，而"codeforces"， "reality"和"ab"不是回文字符串。

## 样例 #1

### 输入

```
abccaa
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
abbcca
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
abcda
```

### 输出

```
YES
```

# 题解

## 作者：skyping (赞：2)

两个指针i，j模拟

最后特判cnt=0 && 长度为奇数的情况（可修改中间的数）

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=16;
char str[maxn];
int cnt;
int main()
{
	cin>>str;
	int i=0,j=strlen(str)-1;
	while (i < j)
	{
		if (str[i] != str[j]) ++cnt;
		++i,--j;
	}
	printf((cnt == 1 ) || (cnt == 0 && strlen(str)%2 == 1) ? "YES" : "NO");
	return 0;
}
```


---

## 作者：wpj20241021005 (赞：1)

这道题初看不算太难，打起来当然也不难，但我信心满满地交上去时，却发现第5点WA了，交了多次（10次）才发现，这道题是强制换字母！！！（我一直没有注意）。

回文顾名思义就是从头到尾，再从尾到头，两次读起来一样，也就是可以完全重和，怎么判断呢，那就用指针吧，一个指开头，一个指结尾，判断是否相等，如果两个指针相遇，只有一处不一样的话，那就是可以的啦。如果大于1的话，就不行了，可以提前跳出循环。如果完全相等的话，还要判断字符串长度，入果是偶数，就不行了（因为强制换一个字母），如果是奇数，则可以换掉中间的字母。

上代码！

```
#include<bits/stdc++.h>
using namespace std;
string a;//定义字符串
int sum;
int main(){
	cin>>a;
	char b,c;
	for(int i=0;i<a.size()/2;i++){ //进循环
		b=a[i];
		c=a[a.size()-i-1];
		if(b!=c&&sum==1){//提前结束
			cout<<"NO";
			return 0;
		}
		if(b!=c) sum++;
	}
	if(sum==0&&a.size()%2==1) cout<<"YES";//特判
	if(sum==1) cout<<"YES";
	if(sum==0&&a.size()%2!=1) cout<<"NO";
}
```

好了，就这么多了，如果有描述不规范的地方，还请多多包涵


---

## 作者：紫妹只有17岁 (赞：1)

还是CF上的题目喵~>.<~

这道题看题解区的dalao用的就是判断有多少个位数是不回文的

然后蒟蒻我用的是暴力（我太蒟了）

去除前面的特判和判断回文函数，剩下的就是一位一位从a-z来更改，如果更改之后是回文就YES，反正s最长也就15,15*26=？？？诶呀反正不超1000就对了喵~>.<~

主要算法没问题，但是特判挺坑的

长度为1随便改也是YES，然后原来是回文但是长度是偶数就不行，奇数就可以喵~>.<~……

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
bool Is_Huiwen(string str)//判断是否为回文字符串
{
	for(int i=0;i<str.length()/2;i++)//从第一位到长度/2进行模拟
	{
		if(str[i]!=str[str.length()-i-1])//如果某一位不相同就false
			return false;
	}
	return true;
}
int main()
{
	cin>>s;
	if(s.length()==1)//特判1：长度为1
	{
		printf("YES\n");
		return 0;
	}
	if(Is_Huiwen(s)==true&&s.length()%2!=0)//特判2：原来就是回文的而且长度为奇数
	{
		printf("YES\n");//比如abcba
		return 0;//把中间的c改成a-z任意一个都是回文的
	}
	if(Is_Huiwen(s)==true&&s.length()%2==0)//特判3：原来就是:回文的但是长度为偶数
	{
		printf("NO\n");//比如abccba
		return 0;//这样不管改那个，都是不行的
	}
	for(int i=0;i<s.length();i++)
	{
		for(int j=1;j<=26;j++)//从a-z轮流修改当前位
		{
			string stt=s;//stt是用来比较的
			stt[i]=(char)('a'+j-1);//修改stt[i]
			if(Is_Huiwen(stt)==true)//如果某次修改使它成为了回文串
			{
				printf("YES\n");//就输出YES
				return 0;
			}
		}
	}
	printf("NO\n");//一直不能变成回文串就输出NO
	return 0;
}
```

这是去掉注释的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
bool Is_Huiwen(string str)
{
    for(int i=0;i<str.length()/2;i++)
    {
        if(str[i]!=str[str.length()-i-1])
            return false;
    }
    return true;
}
int main()
{
    cin>>s;
    if(s.length()==1)
    {
        printf("YES\n");
        return 0;
    }
    if(Is_Huiwen(s)==true&&s.length()%2!=0)
    {
        printf("YES\n");
        return 0;
    }
    if(Is_Huiwen(s)==true&&s.length()%2==0)
    {
        printf("NO\n");
        return 0;
    }
    for(int i=0;i<s.length();i++)
    {
        for(int j=1;j<=26;j++)
        {
            string stt=s;
            stt[i]=(char)('a'+j-1);
            if(Is_Huiwen(stt)==true)
            {
                printf("YES\n");
                return 0;
            }
        }
    }
    printf("NO\n");
    return 0;
}
```

希望管理员大大让过喵~>.<~

---

## 作者：liuyifan (赞：1)

统计有多少个字符不回文,如果为0或2则Yes,否则输出No

因为回文是成对的,所以2个不回文的字符只需要改1个就能变成回文

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register//将变量储存在CPU寄存器中,有时可以加速
using namespace std;
string a;//C++字符串
int sum;//不回文的个数
int main()
{
    getline(cin,a);//读入一整行,等价于对于字符数组的gets
    for(reg int i=0;i<a.length();i++)
    if(a[i]!=a[a.length()-i-1])sum++;
    if(a.length()&1&&sum==0)sum+=2;//a&1==a%2,位运算能加速
    puts(sum==2?"YES":"NO")//如果sum==2输出Yes,否则输出No
    return 0
}
```
拒绝抄袭,共建和谐洛谷

---

## 作者：houpingze (赞：0)

本题不难，但很坑！

思路：定义一个计数器。从0~s.size()/2-1遍历一遍，如果$s[i]!=s[s.size()-i-1]$，这个计数器就加一。最后看看计数器是不是1（只要改一个字符）或者在$f(a)==0$和$a.size()$ % $2=1$的条件共同成立的情况下（因为这种条件成立了，字符串的长度必然是奇数，只要改中间那个字符就行了），输出YES，反之输出NO

## AC CODE：
```cpp
#include<iostream>
typedef long long ll;
using namespace std;
int f(string s){
	int cnt=0;//计数器
	for(int i=0;i<s.size()/2;i++) if(s[i]!=s[s.size()-i-1]) cnt++;
	return cnt;
}//判断0~s.size()/2中有多少不回文的字符串
int main(){
	string a;
	cin>>a;//输入
	if(f(a)==1||(f(a)==0&&a.size()%2)) cout<<"YES";
    //YES的情况
	else cout<<"NO";//NO的情况
	return 0;
}
```


---

