# Generate Login

## 题目描述

The preferred way to generate user login in Polygon is to concatenate a prefix of the user's first name and a prefix of their last name, in that order. Each prefix must be non-empty, and any of the prefixes can be the full name. Typically there are multiple possible logins for each person.

You are given the first and the last name of a user. Return the alphabetically earliest login they can get (regardless of other potential Polygon users).

As a reminder, a prefix of a string $ s $ is its substring which occurs at the beginning of $ s $ : "a", "ab", "abc" etc. are prefixes of string "{abcdef}" but "b" and 'bc" are not. A string $ a $ is alphabetically earlier than a string $ b $ , if $ a $ is a prefix of $ b $ , or $ a $ and $ b $ coincide up to some position, and then $ a $ has a letter that is alphabetically earlier than the corresponding letter in $ b $ : "a" and "ab" are alphabetically earlier than "ac" but "b" and "ba" are alphabetically later than "ac".

## 样例 #1

### 输入

```
harry potter
```

### 输出

```
hap
```

## 样例 #2

### 输入

```
tom riddle
```

### 输出

```
tomr
```

# 题解

## 作者：文·和 (赞：7)

### 冲击最短代码

思路：所谓字典序就是逐个比对字符，出现字符不同时字符ASCLL大的对应的字符串大。例如"743nlbcd"和"743nlkcd"中，比对至b和k时发现b更小，那么第一个串更小。

那么思路就简单了：因为两个串的开头必须输出，而第一个串的开头必须放第一个输入，以后则只需扫串1，找到小于第二个串首字符的字符就输出。注意若大于就需退出。

贴出代码：

```
#include <bits/stdc++.h>
using namespace std;
int i;
string s,s2;
int main(){
	cin>>s>>s2;
	cout<<s[0]；//先将首字符输出
	for(i=1;i<s.size();i++) if(s[i]<s2[0]) cout<<s[i]; else break;//扫一遍串一，发现符合就输出。
	cout<<s2[0];//最后输出即可
	return 0;
}
```
# 珍爱生命，请勿抄袭

代码里有秘密抄了有惊喜哦~

求通过qwq.....


---

## 作者：frankchenfu (赞：7)

我们考虑贪心。

我们首先先输出第一个串的第一个字符，因为要求非空。
我们注意到无论如何，第二个串只需要一个字符即可，因为长度短的串字典序小。如果加上第二个字符一定会使字典序更大。

例如：`xxxxp`字典序比`xxxx`大。无论`xxxx`后面加上什么字符，字典序都比原串大。

然后我们每次判断，如果第一个串中的剩余的当前字符仍然比第二个串的首字符小，那么总字典序肯定也比直接加上后一个串的长度小。
当我们发现一个串中字符字典序$\ge$第二个串的首字符，那么我们直接输出第二个串首字符，然后结束程序即可。

代码：
```cpp
#include<cstdio>
#include<cstring>
char ch1[20],ch2[20];int n;

int main()
{
	scanf("%s%s",ch1,ch2);
	n=strlen(ch1);
	putchar(ch1[0]);
	for(int i=1;i<n;i++)
	{
		if(ch1[i]<ch2[0])
			putchar(ch1[i]);
		else
			break;
	}
	putchar(ch2[0]);
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：4)

由于数据小，枚举所有可能子串即可。详见代码。

代码：

```cpp
#include <bits/stdc++.h>
#define maxn 10001
using namespace std;
string s,ss;
int k[26];
int a[26];
int main()
{
    cin>>s>>ss;
    int x=s.length(),y=ss.length();
    string s1="zzzzzzzzzzzz";
    string s2;
    for(int i=0;i<x;i++)//枚举子串
    {
        for(int j=0;j<y;j++)
        {
            s2=s.substr(0,i+1)+ss.substr(0,j+1);//把两个字符串枚举的部分拼在一起
            s1=min(s1,s2);//比较字典序最小的
        }
    }
    cout<<s1<<endl;
    return 0;
}
```

---

## 作者：Kafka1 (赞：2)

要选出最小的字典序字符串，肯定先考虑贪心啦，我们先创建一个
StringBuilder类，添加第一个字符串为名的首字符（~~因为外国人都是名在前姓在后~~）

然后通过枚举，逐一比较两边前缀的字典序大小，也就是ASCII的值，有一种特殊情况就像样例2那样当所有的名都输出之后，输出姓的第一个字符

```java
import java.util.Scanner;

/**
 * Created on 09:09  08/02/2020
 * Description:
 *
 * @author Weleness
 */

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String name = sc.next();
        String xin = sc.next();

        StringBuilder sb = new StringBuilder(name.charAt(0) + "");
        boolean flag = true; // 作为结束标记
        int i = 1; // 名的索引
        int j = 0; // 姓的索引
        while (flag) {
            if (i < name.length() && j < xin.length()) { // 保证不越界的情况下
                if (name.charAt(i) < xin.charAt(j)) { // 如果名的字符的ASCII的值小于姓的
                    sb.append(name.charAt(i));//添加进builder里
                    i++; // 往后查找
                }else {
                    sb.append(xin.charAt(j)); // 否则添加姓的，此时已经不符合名在前姓在后的条件了，可以退出了
                    j++;
                    flag = false;
                }
            }else if(i == name.length()){ // 所有的姓的前缀字符都不符合，添加第一个，退出
                sb.append(xin.charAt(j)); 
                flag = false;
            }
        }
        System.out.println(sb.toString()); // 输出
    }
}

```


---

## 作者：北雪2009 (赞：0)

这道题是一道暴力题。   
这道题只需要枚举每一个串就行了。   
附上代码：   
```cpp
#include<bits/stdc++.h>   //万能头，贪简单
#include<stdio.h>    //万能头2，以防万一
using namespace std;   
string str1,str2,str="zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";    //定义，str1与str2是输入用，str3是比较用。因为str3是要用来比最小的，所以str3一定要尽量大。
int main(){
	ios::sync_with_stdio(false);   //cin，cout快读快输。用scanf和printf的朋友就不要用了，会RE
	cin>>str1>>str2;   //读入两个字符串
	for(int i=0;i<str1.size();i++)   //枚举，第一重循环，代表str1		
    		for(int j=0;j<str2.size();j++)  //枚举，第二重循环，代表str2
			str=min(str,str1.substr(0,i+1)+str2.substr(0,j+1));  //暴力枚举出奇迹，枚举每一个前缀
	cout<<str;   //输出
    return 0;   //结束
}
```


---

## 作者：不到前10不改名 (赞：0)

//什么暴力枚举所有可能性，很明显s2字典序最短是是只选第一个字母，而在s1选择中，选完第一个字母，然后向后依次搜索，若小于s2开头字母（也就是加上后使字典序更小就选，否则退出）
```
#include<stdio.h>
#include<string.h>
char srx[20],sry[20];
int i;
int main()
{
    scanf("%s%s",srx,sry);
    printf("%c",srx[0]);
    for(i=1;i<strlen(srx);i++)//友情提示，从1开始（0输出过了）
    {if(srx[i]<sry[0])//s1中是否选择
    printf("%c",srx[i]);
    else
    break;}//非空前缀和！不能打continue！
    printf("%c",sry[0]);//s2中选的数
    return 0;
}
```

---

## 作者：Hola_chen (赞：0)

# 非喜勿喷~
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int main()
{
	string s1,s2,s="~~~~AC之神嘉骏最帅~~~~";//string~AC之神嘉骏最帅 
	cin>>s1>>s2;//输入 
	for(int i=0;i<s1.size();i++)//for 
	    for(int j=0;j<s2.size();j++)//for*2 
	    {
	    	s=min(s,s1.substr(0,i+1)+s2.substr(0,j+1));//substr函数 ：取字符串的子串。当i+len超过原字符串的长度，只取剩下的字符 
		}
		cout<<s;//输出 
    return 0;
}

```

---

