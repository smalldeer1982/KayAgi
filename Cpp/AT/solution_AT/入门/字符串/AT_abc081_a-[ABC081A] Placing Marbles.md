# [ABC081A] Placing Marbles

## 题目描述

读入一个字符串s，求它的数字和是多少

## 样例 #1

### 输入

```
101```

### 输出

```
2```

## 样例 #2

### 输入

```
000```

### 输出

```
0```

# 题解

## 作者：tZEROちゃん (赞：2)

**[题目传送门](https://www.luogu.com.cn/problem/AT3717)。**

_______

**分析**

我们可以把字符串中所有数加起来输出，那么到底怎么把一个字符变成一个数字呢。我们只需要减去字符$0$就可以了。

********

**详细步骤**

1. 定义字符串$s$并将其输入。
```cpp
    string s;
    cin>>s;
```

2. 我们可以将每一个字符减去字符$0$，然后将它们一次相加并输出。
```cpp
    cout<<s[0]-'0'+s[1]-'0'+s[2]-'0';
```

--------------

**CODE**
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    cout<<s[0]-'0'+s[1]-'0'+s[2]-'0';
    return 0;
}
```

---

## 作者：RioBlu (赞：1)

本题就是输入一个长度为$3$字符串

输出有几个$1$

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int ans=0;
	string a;
	cin>>a;
	if(a[0]=='1')ans++;
	if(a[1]=='1')ans++;
	if(a[2]=='1')ans++;
	cout<<ans<<endl;
}
```

---

## 作者：死神审判 (赞：0)

### 思路:
输入一个长度为3字符串并求出所有数的加和，可以用 $ \operatorname{string}$ 来写。

------------
### 解法：
从 $0$ 循环到 $2$ ，每一个字符减去ASCII码为48字符'0'后加到统计的 $ans$ 中，最后输出即可。

------------
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	int ans=0;
	cin>>s;
	for(int i=0;i<3;i++)
		ans+=s[i]-'0';//统计
	cout<<ans<<'\n';//输出
	return 0;
}

```
------------

但由于这题中的字符串只包含 $1$ 或 $0$ ，所以还可以判断每一位是不是'1'，如果是， $ans$ 加 $1$。

------------

### 代码2：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	int ans=0;
	cin>>s;
	for(int i=0;i<3;i++)
		ans+=(s[i]=='1');//统计
	cout<<ans<<'\n';//输出
	return 0;
}

```


---

## 作者：youyou2007 (赞：0)

这道题叫我们求字符串中1的个数，可以定义一个字符串，判断一下即可。

上代码
```cpp
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
string a;
int s,i,n;
int main()
{
    cin>>a;
    n=a.length();
    for(i=0;i<n;i++)
    {
        if(a[i]=='1')//判断是否为1
        s++;
    }
    cout<<s<<endl;
    return 0;
}
```

---

