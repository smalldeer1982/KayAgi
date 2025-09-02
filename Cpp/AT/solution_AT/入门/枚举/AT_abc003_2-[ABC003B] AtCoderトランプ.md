# [ABC003B] AtCoderトランプ

## 题目描述

在 AtCoder 公司，流行着一种一个人玩的扑克牌游戏。  
AtCoder 公司特制的扑克牌上，每张牌上写有一个小写英文字母（`a`～`z`），或者是 `@` 字符。  

游戏按照以下步骤进行：

1. 将牌等分为两列，分别组成两个字符串。
2. `@` 牌可以替换为 `a`、`t`、`c`、`o`、`d`、`e`、`r` 中的任意一个字母。
3. 如果两列所表示的字符串完全相同，则获胜，否则失败。

现在给定按照步骤 1 排列好的两个字符串，请你编写程序判断，是否可以通过适当替换 `@`，使得在这个游戏中获胜。  
输入通过标准输入给出，格式如下：

> $S$  
> $T$

1. 第 1 行给出第 1 列扑克牌所表示的字符串 $S$。
2. 第 2 行给出第 2 列扑克牌所表示的字符串 $T$。
3. 保证 $S$ 和 $T$ 只包含小写英文字母和 `@` 字符。
4. 保证 $S$ 和 $T$ 的长度相等，且长度在 $1$ 到 $10$ 之间。

如果可以获胜，输出 `You can win`，否则输出 `You will lose`（不包含单引号），并在输出末尾添加换行符。

例如：

```
ch@ku@ai
choku@@i
```

输出：

```
You can win
```

- 例如，可以巧妙地将 `@` 替换为合适的字母，使得两个字符串都变成 `chokudai`，从而一致。

```
aoki
@ok@
```

输出：

```
You will lose
```

- 第 4 个字符无法用 `@` 替换为 `i`，因此无法一致。

```
arc
abc
```

输出：

```
You will lose
```

- 第 2 个字符无法一致。

## 说明/提示

无。

由 ChatGPT 4.1 翻译

# 题解

## 作者：珅肐 (赞：3)

相比于楼下的题解, 我的更适合新手~~(毕竟来AtCoder···)~~

#### 代码：
```cpp
#include<iostream>
#include<string>
using namespace std;
string a,b;
int main()
{
    cin>>a>>b;//
    int la=a.length();//因为题目保证两个字符串长度相同, 写一个就够
    for(int i=0;i<la;++i)//遍历整个字符串
        if(a[i]!=b[i])//逐位比较
		{
		    if(a[i]!='@' && b[i]!='@')
            {//a[i]b[i]如果不相同而且不是‘@’，直接输出"You will lose"
		    	cout<<"You will lose"<<endl;
            	return 0;
			}
			else if(a[i]=='@'&& b[i]!='a'&& b[i]!='t'&& b[i]!='c'&&
			b[i]!='o'&& b[i]!='d'&& b[i]!='e'&& b[i]!='r') 
            {//暴力判断，如果a[i]为‘@’，b[i]'atcoder'中的一个，直接输出"You will lose"，下同
		    	cout<<"You will lose"<<endl;
            	return 0;
			}
			else if(b[i]=='@'&& a[i]!='a'&& a[i]!='t'&& a[i]!='c'&&
			a[i]!='o'&& a[i]!='d'&& a[i]!='e'&& a[i]!='r') {
		    	cout<<"You will lose"<<endl;
            	return 0;
			}
		}
    cout<<"You can win"<<endl;//程序进行到这里就说明没有问题，输出"You can win"
    return 0;
}
```

---

## 作者：_Qer (赞：2)

题意：给定两个由'a'~'z'的字符或'@'组成字符串，其中@可以转换为'a','t','c','o','d','e','r'中的任意一个字符，请问是否可以通过替换'@'字符使两个字符串相等。

这题还是比较简单的，用两个string存下输入的字符串，逐位进行比较，如果能够通过转换变成相等的就不管，否则直接输出不行然后结束程序。

如何才算能够转换成相等的呢？

| char a | x | @ | @ | @ | @ | @ | @ | @ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| char b | x | a | t | c | o | d | e | r |


| char a | a | t | c | o | d | e | r |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| char b | @ | @ | @ | @ | @ | @ | @ |

注：第一个字符串第i个字符为char a，第二个字符串第i个字符为char b。上下对应的为可以转化为相等的。x代表任意字符。

从上表可以看出，当char a或char b相等时成立。
若其中一个为'@'，则另一个为'a','t','c','o','d','e','r','@'
中任意一个即可成立。

于是我们可以开始写程序了：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
string at="atcoder@";//其中一方为'@'，另一方的成立条件
bool check(char a,char b){//检查两个字符是否可以变成相同的
    if(a==b){//相等情况
        return true;
    }
    if(a=='@'){//若一方为'@'，下同
        for(int i=0;i<=7;++i){//下标0开始
            if(b==at[i]){//若成立
                return true;
            }
        }
        return false;//不等于以上任何一个
    }
    if(b=='@'){
        for(int i=0;i<=7;++i){
            if(a==at[i]){
                return true;
            }
        }
        return false;
    }
    return false;//最后为a,b不相等且都不为'@'的情况，不成立
}
int main(){
    cin>>a>>b;//两个字符串
    for(int i=0;i<a.length();++i){//题目保证两个字符串长度相等
        if(!check(a[i],b[i])){//如果不成立
            cout<<"You will lose"<<endl;
            return 0;//直接输出并结束程序，避免多次输出
        }
    }
    cout<<"You can win"<<endl;//都是成立的
    return 0;
}
```

---

## 作者：两年打铁 (赞：1)

这道题还是比较~~难的~~（虽然我还红绿相间了一次）
这道题字符串长度相同，所以我们可以一位一位比较。
# 接下来呈上新手的代码。


------------


```cpp
#include <bits/stdc++.h>
using namespace std;
char s[1001],h[1001],g[1001];  
int a,b,c,d,e,i,j,k,m,n;
int main()
{
  cin>>s>>h;
  for(i=0; i<strlen(s); ++i) //因为字符串输入第0位才是第一个，所以我们要从0开始
  {
    if(s[i]=='@')   //一开始有点懵，就判了两次。（第一次，也就是当第一个串中有“@”时。）
    {
    	if(h[i]=='a'||h[i]=='t'||h[i]=='c'||h[i]=='o'||h[i]=='d'||h[i]=='e'||h[i]=='r'||h[i]=='@')continue;  //因为@只能转换为这几个字母，直接判断。
    	else
		{
		 cout<<"You will lose"<<endl;
		 return 0;
		}	
	}
	if(h[i]=='@')//（第二个串）
    {
    	if(s[i]=='a'||s[i]=='t'||s[i]=='c'||s[i]=='o'||s[i]=='d'||s[i]=='e'||s[i]=='r'||s[i]=='@')continue;
    	else
		{
		 cout<<"You will lose"<<endl;
		 return 0;
		}	
	}
    if(s[i]!=h[i])  //有点恐怖的是其实只要不是@的两个字符不相同，就可以直接判不合法。
    {
      cout<<"You will lose"<<endl;
      return 0;
    }
  }
  cout<<"You can win"<<endl;
  return 0;
}

```

>第N次提交水题题解。


---

