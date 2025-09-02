# String Typing

## 题目描述

You are given a string $ s $ consisting of $ n $ lowercase Latin letters. You have to type this string using your keyboard.

Initially, you have an empty string. Until you type the whole string, you may perform the following operation:

- add a character to the end of the string.

Besides, at most once you may perform one additional operation: copy the string and append it to itself.

For example, if you have to type string abcabca, you can type it in $ 7 $ operations if you type all the characters one by one. However, you can type it in $ 5 $ operations if you type the string abc first and then copy it and type the last character.

If you have to type string aaaaaaaaa, the best option is to type $ 4 $ characters one by one, then copy the string, and then type the remaining character.

Print the minimum number of operations you need to type the given string.

## 说明/提示

The first test described in the problem statement.

In the second test you can only type all the characters one by one.

## 样例 #1

### 输入

```
7
abcabca
```

### 输出

```
5
```

## 样例 #2

### 输入

```
8
abcdefgh
```

### 输出

```
8
```

# 题解

## 作者：wcop114514 (赞：1)

**题目分析**

首先1.我们可以加入一个字符，此时步骤 $+1$。

   2.可以复制当前内容添加添加到后方，步骤 $+1$。

   对于第一种直接无脑加就行了。
    对于第二种可以使用`substr`函数，解释： 
    从 $a$ 开始截取字符串的开始位置（注：当 $a$ 等于 $0$ 或 $1$ 时，都是从第一位开始截取）。
    
   所以判断当出现重复字符串时，就输出  $n - i + 1$，如果都没有，输出 $n$ 即可。
```cpp
   给各位大佬奉上代码。
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
    int n;
    string s;
    cin>>n>>s;
    for(int i=n;i>0;i--){
        if(s.substr(0,i)==s.substr(i,i)){
            cout<<n-i+1<<endl;
            return 0;
        }
    }
    cout<<n<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

 # 题目分析：
给定一个字符串`str`和长度 $n$，存在两种操作方法：  
- 一个一个加入（遍历过去即可）；  
- 把复制的添加到后面。
 
 
对于操作 $2$，有一种函数`substr(p,l)`。
该函数可以判断从下标为 $p$ 到 $l$ 的子字符串是否在后面出现过。
 
综合一下思路：
遍历字符串，每次判断后面是否出现了前面的字符串，则输出 $n - i + 1$，如果没有，输出 $n$ 就好啦。
## 代码
```cpp
#include<bits/stdc++.h> //头文件
using namespace std;
int main(){
	int n;//长度
	string str;//字符串
	cin>>n>>str;//读入进去
	for(int i=n;i>;i--){//遍历字符串
           if(str.substr(0,i)==str.substr(i,i)){//重复判断前面的字符串是否在后面出现过
		cout<<n-i+1;//出现过，输出
		return 0;//结束啦
	   }
	}
	cout<<n;//从来没有出现过，输出
	return 0;//干完了
}
```

---

## 作者：GaryH (赞：1)

# 哈喽！
其实此题思路不难，但我很~~憨憨~~就用了一个 _FANTASTIC_ 的方法.

我在代码里定义了一个判断是否能复制的函数，即check(int x)：

```cpp
inline bool check(int x){int p=0;
	for(int i=0;i<x&&!p;i++){
		if(str[i]!=str[i+x])p=1;//如果不等就把p赋成1
	}
	if(p)return 1;//不行
	return 0;//可以
}
```
好了，既然又了此函数，我们便可以进行非常方便的求解问题，即一遍遍查找最优解，那我放一下代码 **(解释在代码里)**

```cpp
#include<bits/stdc++.h>
//万能头牛逼 
using namespace std;
string str;
int n,ans;
inline bool check(int x){int p=0;
	for(int i=0;i<x&&!p;i++){
		if(str[i]!=str[i+x])p=1;
	}
	if(p)return 1;
	return 0;
}//判断函数，前面已解释 
int main(){
	cin>>n;
	cin>>str;
	//输入 
	int i=n/2+1;
	while(1)/*一遍遍查找*/{
		if(check(i)==0)/*判断是否可以复制*/{
			ans=max(ans,i-1);
			//判断是否是最优解 
		}
		i--;//减一不要忘 
		if(i==0)break;//如果查找完就退出 
	}
	cout<<n-ans;
	//ans为可用复制省略的最大步数,用n-ans即为答案 
	return 0;
}
```
好了，题解结束了，再见！

---

## 作者：封禁用户 (赞：1)

多水的橙题！

题意：

该你一个长度为 $n$ 的字符串，然后让你用以下的 $2$ 个操作，来成功写出这个字符串。

1：一个一个的字母输入。

2：复制前面的字符串添加至末尾。

问至少需要多少步才能成功写出这个字符串。

思路：

其实这题只需判断一下这个字符串中是否有重复的子串，如果有就那总位数减重复字符的末尾的位数 $ +1$（因为重复字符还算一位），此时我们可以用 ```substr```这个函数解决问题。

如果没有就直接输出 $n$ 就行了。

代码：

```
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	for(int i = 1;i <= n ;i ++) {
	if(s.substr(0,i) == s.substr(i,i)) {
		cout << n - i + 1;
		cout << endl;
	return 0;
}
}
cout << n;
}
```



---

## 作者：Terry2011 (赞：0)

# 题目分析

- 首先，这道题可以执行一次复制前面已经添加的字符，把复制的添加到后面，然后继续添加字符。各位想到了什么？提取子串！

- 看来，不仅题目良心，string 也很良心。substr 听过把，我们可以循环便利整个字符串（当然，半个也可以）来判断后面是否出现前面的子串。如果出现了，就输出 $n-i+1$，如果从始至终都没有，输出 $n$ 即可。
# Code

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
	int n;string s;//声明
	cin>>n>>s;//输入
	for(int i=n;i>0;i--){//循环便利
	    if(s.substr(0,i)==s.substr(i,i)){//每次判断后面是否出现前面的子串
			cout<<n-i+1<<endl;//输出
			return 0;//华丽结束
		}
	}
	cout<<n<<endl;//字母都不相同，输出字母个数
	return 0;
}
```

---

## 作者：CLCK (赞：0)

## ~~水题~~

u1s1 这个翻译感觉并不是很好（像机翻）建议撤下

如题，有两种方法读入长度为 $n$ 的字符串：

- 直接输入
- 把前面的 `Ctrl(Command)+C` 然后 `Ctrl(Command)+V`

显而易见，如果能找到 **从头开始** 的一个字串连续重复两次，就可以用一次操作代替。

注意：$2$ **只能使用一次**，故从 $\frac{n}{2}$ 向下倒序遍历，避免了不合法内存空间也 **确保为最优解**。

如果找不到则直接输出长度即可。

```cpp
#include <iostream>
#include <cstring> //substr函数的头文件
using namespace std;
int n;
string s;
int main(){
	cin >> n >> s;
	for (int i = n / 2; i > 0; i--) {
		if (s.substr(0, i) == s.substr(i, i)) { //可以用substr函数截取，省去循环判断
			cout << n - i + 1 << endl;
			return 0;
		}
	}
	cout << n << endl;
	return 0;
}
```

完结撒花～

---

## 作者：DengDuck (赞：0)

本题十分简单，观察一下题目，我们发现：

- 两种插入都是插入在最右端。
- 如果使用复制操作，那么字符串应该有两个一样的字符串作为一个前缀。

显然复制操作优于一个一个插入，所以先看能不能用复制，如果能，且有多种复制方案，那么应该选复制字符串长度最长的一个，答案就是 $n-|S|+1$，其中 $|S|$ 复制的字符串的长度。

否则答案是一个一个放的 $n$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len;
string s;
int main()
{
    cin>>n>>s;
    len =s.size();
    for(int i=len/2;i>0;i--)
    {
        if(s.substr(0,i)==s.substr(i,i))
        {
            cout<<(n-i+1)<<endl;
            return 0;
        }
    }
    cout<<n<<endl;
}
```


---

## 作者：Sternenlicht (赞：0)

思路：模拟。

设 $len$ 是将要复制的字符串长度，则我们要找到最大的 $len$ 满足要求，输出 $n-len+1$。因为复制长度为 $len$ 的字符串需花一次操作，但省了 $len$ 次添加操作，所以输出 $n-len+1$。

若找不到符合要求的 $len$，输出 $n$，因为这时候我们只能一次添加一个字符。

```cpp
#include <bits/stdc++.h>

std::string s;int n;
int main(){
	std::cin>>n>>s;
	for (int i=n/2;i;i--)//i就是len，注意倒序循环判断 
		if (s.substr(0,i)==s.substr(i,i))//若相等 
			return std::cout<<n-i+1,0;//输出长度 
	std::cout<<n;//没有相同串，输出原本长度n 
	return 0;
}
```

---

## 作者：oimaster (赞：0)

我们按照题目意思模拟即可。设 $i$ 是前面将要复制的字符串的长度，那么可以得知：
- `s.substr(0,i)` 是前面要复制的字符串。
- `s.substr(i,i)` 是复制出来的字符串。

其中，`s.substr(a,b)` 指从 $s$ 下标 $a$ 开始选 $b$ 个字符所得到的字串。

我们找到最大的 $i$ 满足要求，输出 $n-i+1$。如果找不到，输出 $n$，因为只能一个字符一个字符添加。

如何推出 $n-i+1$？我们知道，复制一个长度为 $i$ 字符串可以省掉添加 $i$ 个字符所花的 $i$ 步，然而复制就要花一步，所以是 $n-i+1$。
```cpp
#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	for(int i=n/2;i>0;--i)
		if(s.substr(0,i)==s.substr(i,i)){
			cout<<n-i+1<<endl;
			return 0;
		}
	cout<<n<<endl;
	return 0;
}
```

水题一道![cy](https://cdn.luogu.com.cn/upload/pic/62225.png)

---

