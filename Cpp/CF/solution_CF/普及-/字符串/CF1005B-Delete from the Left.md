# Delete from the Left

## 题目描述

You are given two strings $ s $ and $ t $ . In a single move, you can choose any of two strings and delete the first (that is, the leftmost) character. After a move, the length of the string decreases by $ 1 $ . You can't choose a string if it is empty.

For example:

- by applying a move to the string "where", the result is the string "here",
- by applying a move to the string "a", the result is an empty string "".

You are required to make two given strings equal using the fewest number of moves. It is possible that, in the end, both strings will be equal to the empty string, and so, are equal to each other. In this case, the answer is obviously the sum of the lengths of the initial strings.

Write a program that finds the minimum number of moves to make two given strings $ s $ and $ t $ equal.

## 说明/提示

In the first example, you should apply the move once to the first string and apply the move once to the second string. As a result, both strings will be equal to "est".

In the second example, the move should be applied to the string "codeforces" $ 8 $ times. As a result, the string becomes "codeforces" $ \to $ "es". The move should be applied to the string "yes" once. The result is the same string "yes" $ \to $ "es".

In the third example, you can make the strings equal only by completely deleting them. That is, in the end, both strings will be empty.

In the fourth example, the first character of the second string should be deleted.

## 样例 #1

### 输入

```
test
west
```

### 输出

```
2
```

## 样例 #2

### 输入

```
codeforces
yes
```

### 输出

```
9
```

## 样例 #3

### 输入

```
test
yes
```

### 输出

```
7
```

## 样例 #4

### 输入

```
b
ab
```

### 输出

```
1
```

# 题解

## 作者：清小秋ovo (赞：6)

# CF1005B

[原题传送门](https://codeforces.com/problemset/problem/1005/B)

[洛谷原题](https://www.luogu.com.cn/problem/CF1005B)

## 题意

此题直接根据题意模拟即可。

首先给出两个字符串，规定一次操作为每次只能从字符串的最左端删除一个字符。

问对于规定的两个字符串至少需要操作多少次才能使最终两个字符串完全相同。

字符串可以为空。

对于两个完全不同的字符串，直接输出两串的长度和。


## 思路

创建两个指针，从字符串的最后从头开始扫，并对比连续相同字符的数量。一旦出现不同的字符，扫描终止。

随后我们输出第一个字符串的长度与第二个字符串长度的和减去两倍的末尾相同字符数量。

设第一个字符串长度为 $a$，第二个字符串长度为 $b$, 末尾连续相同字符数量为 $c$, 则有：

$$ (a+b)-2\times c$$

## 代码

已经推到这一步了，此题的答案应该已经非常明了了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
   string a,b;
   cin>>a>>b;
   int count=0; 
   int i=a.length()-1; // 创建两个指针
   int j=b.length()-1;
   while(i>=0&&j>=0){ //从后往前扫
       if(a[i]==b[j]) count++;
       else break; //如果不一样退出扫描
       i--,j--;
   }
   cout<<a.length()+b.length()-2*count<<endl; 
}

```

完美结束！

---

## 作者：灵小沙 (赞：3)

	#include <bits/stdc++.h>//万能头文件 
	using namespace std;
	int main()
	{
    string s,t;//定义两个字符串 
    while(cin>>s>>t)//之后一定要加入return 0 
    {
        int len1=s.length();//取len1的长度 
        int len2=t.length();//取len2的长度 
        int s=0;//一定要清零（废话） 
        for(int i=len1-1,j=len2-1;i>=0,j>=0;i--,j--)
        {
            if(s[i]==t[j]) s+=2;//一定要加2 
            else break;//如果没有就退出 
        }
        cout<<len1+len2-s<<endl;
        return 0;//否则，也没有太大的关系，还是AC了 
    }
	//    return 0;
	}


---

## 作者：VenusM1nT (赞：2)

作为$div3B$题，水是不可避免的，毕竟是$PJ$组【滑稽

那么这题也是一道很水的题啦

大意如下：两个字符串同时从左往右删字符，求要删除多少个字符才能使两个字符串相同

看到此题，第一想法应该是使用$dfs$，这里就不多阐述了

显而易见地，$dfs$会超时，而且你会被罚时 $10min$【逃

我们不妨转换一下思想，我们最终的目的是要使两个字符串相等，而且是从左向右删除字符

这意味着我们最终求到的相同字符串肯定是在两个字符串的最右边

既然如此，我们为何不从每个字符串的最右端一起开始向左循环，找到第一个不同的字符后记录相同串的长度，记录为$k$

然后就可以很轻松地计算出答案了，即：$lena+lenb-k*2$

---

## 作者：happybob (赞：1)

本题就是求最长公共后缀。后缀自动机？不用那么麻烦，复杂度又高，若输入两个字符串长度分别为 $ len\_a \,\text{和}\, len\_b$ 只需要 $ \text{O(min(len\_a, len\_b))}$ 的复杂度即可，从最后一位往前倒推，我是先把两个字符串 `reverse` 一遍再从前往后推，找到不相等就输出，`reverse` 是线性的复杂度。

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	string a, b;
	cin >> a >> b;
	if (a == b)
	{
		cout << "0\n";
		return 0;
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int lena = a.length() - 1, lenb = b.length() - 1, min_len = min(lena, lenb);
	for (register int i = 0; i <= min_len; i++)
	{
		if (a[i] != b[i]) //前一位为最长后缀的起始位（不反转时）
		{
			int x = i - 1;
			cout << (lena - x) + (lenb - x) << endl;
			return 0;
		}
	}
	cout << (lena > min_len ? lena - min_len : lenb - min_len) << endl;
	return 0;
}
```


---

## 作者：Gsmdog_H (赞：0)

### 题目

[CF1005B](https://www.luogu.com.cn/problem/CF1005B)

### 题意

给定两个字符串，从左往右开始删除，问经过几次操作后两字符串一样。

### 思路

根据题意可以判断枚举每一个字符判断是否相同，但是复杂度极高，我们可以根据题意从后往前看有多少个一样的，然后用一共的减去一样的即可。

### AC Code

```cpp
#include<bits/stdc++.h>

using namespace std;

string a, b;
int sum;

int main(){
	getline(cin , a);
	getline(cin , b);
	
	int lena = a.size(), lenb = b.size();
	
	for(register int i = lena - 1, j = lenb - 1; i >= 0, j >= 0; --i, --j){
		if(a[i] == b[j])
			sum++;
		else break;
	}
	
	cout << lena + lenb - sum * 2;//因为是两字符串都一样所以要*2 
	
	return 0;
}
```

没了。

---

## 作者：xzllll07 (赞：0)

我们先来读题，给定两个字符串，每次可以删除其中一个字符串的最左面的一个字符，问最少操作多少次才能使两个字符串相同。

我们要求有多少不同的字符需要删除，并不是很好计算。但是，要计算在字符串的末尾有多少个相同的字符可以保留，是很好计算的。

如果求出有多少个末尾的字符相同，那么用两个字符串的总长度减去相同字符数量的两倍（因为两个字符串内的字符都可以保留，所以是两倍），就等于需要删除字符的个数。

代码非常简单，但注意一下两个字符串长度不一定相同，右端不一定对齐，我这个蒟蒻选择了 $\operatorname{algorithm}$ 头文件中的 $\operatorname{reverse}$ 函数来反转两个字符串，从字符串开头开始循环遍历，如果字符不同，就结束循环。

完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s1,s2;
    cin>>s1>>s2;
    int len1=s1.length();
    int len2=s2.length();
    int counter=0;
    reverse(s1.begin(),s1.end()); //反转，对齐
    reverse(s2.begin(),s2.end());
    for (int i=0;i<=min(len1,len2)-1;i++) //注意这里！！循环变量从0开始，要循环到短的字符串末尾，所以是 min(len1,len2)-1，一定要记得 -1，字符串是从0开始输入，长度是 n，下表是从 0 到 n-1。
    {
        if (s1[i]==s2[i])
        {
            counter++;
        }
        else break;//不同就终止循环
    }
    cout<<len1+len2-counter*2;
}
```


---

