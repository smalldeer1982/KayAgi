# Uniform String

## 题目描述

```plain

给你两个数, $n$,$k$

你的任务是构造一个长度为$n$的字符串 $S$, 使得英文字母表中前 $k$ 个字符在字符串中出现至少一次,并且不出现其他字母,你需要最大化出现次数最小的字母的出现次数.

你要回答 $t$ 组询问,询问之间独立.


给你两个数, $n$,$k$

你的任务是构造一个长度为$n$的字符串 $S$, 使得英文字母表中前 $k$ 个字符在字符串中出现至少一次,并且不出现其他字母,你需要最大化出现次数最小的字母的出现次数.

你要回答 $t$ 组询问,询问之间独立.

## 样例 #1

### 输入

```
3
7 3
4 4
6 2
```

### 输出

```
cbcacab
abcd
baabab
```

# 题解

## 作者：Yi_Fan (赞：2)

# 题意：
给一个长度为 $n$ 的字符串 $S$, 使得英文字母表中前 $k$ 个字符在字符串中出现至少一次,并且不出现其他字母,要每个字母都出现得尽量的多


------------
# 分析：

一道鸽巣题目，我知道证明，只是这里空间太小，我就不多写了，就直接写出：

**鸽巣原理最简单的表达形式:**

**物体个数 $÷$ 鸽巣个数 $=$ 商 $……$ 余数**

**那么至少个数=商 $+1$**


------------
# 程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
//变量区 
int t;//次数 
int n;// 
int k;// 
//主函数 
int main()
{
	cin >> t;
	while( t --){
		cin >> n >> k;
		for(int i = 1; i <= n;i++){
			cout << char(i % k + 'a');//鸽巣原理
		}
		cout << endl;
	}
 	return 0;
}
```


---

## 作者：YYen (赞：1)

### 思路：贪心
题目要求出现次数最少的字母的出现的次数尽可能多，所以我们需要尽可能平均的分配字母。

由于需要前 $ k $ 个小写字母，我们先本着平均分配原则，则每个字母可以出现 $ \lfloor n / k \rfloor $ 次，然后我们将剩余的 $ n \bmod k $ 个位置分别用不同的字母填满即可。

### 代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, k;
        cin >> n >> k;
        char c = 'a';
        for (int i = 1; i <= n; i++)
        {
            cout << c;
            c++;
            if (c - 'a' + 1 > k) c = 'a';
        }
        cout << endl;
    }
    return 0;
}
```


---

## 作者：XzJerry (赞：1)

题意是说一共要有$m$种不同字符，所以我们可以就用$a$,$b$......
```
/************************************************
*Author        :  xzj213
*Created Time  :  2018.12.18 22:39
*Mail          :  xzj213@qq.com
*Problem       :  a.cpp
************************************************/
#include<bits/stdc++.h>
using namespace std;
int T,n,m; 
int read() {
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}//毫无意义的快读
int main() {
	cin>>T;//多组数据
	while(T--){
		cin>>n>>m;
		if(n%m==0){//如果N%M==0,那么所有字符个数一样
			int s=n/m;
			char a='a';
			for(int i=1;i<=m;i++){
				for(int j=1;j<=s;j++)printf("%c",a);//从A开始输出
				a+=1;//字符ASCII码+1
			}
			puts("");
			continue;
		}
        //N%M!=0的情况
		int s=ceil((n-1)/m)+1;//抽屉原理，在这里不详讲
		char a='a';
		for(int i=1;i<=s;i++)printf("%c",a);//输出A的个数
		int sum=0;m--;n-=s;
		while(n%m!=0){
			n-=s;m--;sum++;
		}
		for(int i=1;i<=sum;i++){
			a+=1;
			for(int j=1;j<=s;j++)printf("%c",a);
		}//个数仍然是S的字符
		for(int i=1;i<=m;i++){
			a+=1;
			for(int j=1;j<s;j++)printf("%c",a);
		}//不是S个数的字符
		puts("");//换行
	}
    return 0;//大功告成
}
```

---

## 作者：Zechariah (赞：1)

显然k个字符轮流输出就行了，我们用一个now来表示当前输出的是哪个字符，每次递增now用取模来轮流输出
```
for (rg int i = 1; i <= n; ++i)
	putchar('a' + now), (++now) %= k;
```

---

## 作者：Mr_Avalan (赞：0)

### 题目大意

输出一个尽量使字母表中前 $k$ 个字母平均分配的长度为 $n$ 的字符串。

### 题目分析

因为要平均分配，所以就把字母表的前 $k$ 个字母循环输出，直到输出 $n$ 位为止。

### 注意

输出时要把 $int$ 型强转成 $char$ ，而且是小写字母。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,m;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;//输入
		m=1;
		while(m<=n)//输出n位
		{
			printf("%c",m+'a'-1);//强转类型
			m++;
			if(m>k)
			{
				m=1;n-=k;//控制m只在前k个字母中循环
			}
		}
		cout<<endl;//每组数据之间要有换行
	}
	return 0;
}
```

---

## 作者：Creator_157 (赞：0)

### 题目大意:
$T$ 组数据。每组数据给你两个数： $n$、$k$，要求用字母表前 $k$ 个字母构成长度为 $n$ 的字符串。

------------
### 解题思路：
着眼一看，这不就是我们~~小学二年级~~学过的[鸽巢问题](https://wenku.baidu.com/view/da2e585376a20029bc642d35.html)吗¿
这里就不再赘述了。直接上代码！

------------
### code：
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
int T,n,k;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)
        {
            cout<<char(i%k+'a');
        }
        cout<<endl;
    }
    return 0;
}
```


---

## 作者：Ouaoan (赞：0)


每次输出的形式都形如 abcdabcdabc 这样的，k个字母循环输出。

只需要写一个循环维护一下就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define read(x) scanf("%d",&x)

int n;

int main() {
	read(n);
	for(int i=1;i<=n;i++) {
		int x,y;
		read(x),read(y);
		for(int j=1;j<=x;j++) {
			printf("%c",j%y+'a');
		}
		printf("\n");
	}
	return 0;
}
```

---

