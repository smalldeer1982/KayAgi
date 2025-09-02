# Yahoo

## 题目描述

高桥君打算开办一家新公司，而这个公司决定建立一个搜索网站，因此他决定将 `yahoo` 这个五个字母重新排列后得到的字符串作为公司的名字。

他的朋友青木提议将字符串 $S$ 作为新公司的名字，请你判定这个字符串是否符合高桥君的要求。
### 题意简化
给定一个长度为 $5$ 的字符串，判断其是否由字符串 `yahoo` 重新排列得到。

## 说明/提示

### 数据限制
- 字符串 $S$ 的长度 $|S| = 5$。
- 字符串 $S$ 均为小写字母。

## 样例 #1

### 输入

```
oohay```

### 输出

```
YES```

## 样例 #2

### 输入

```
abcde```

### 输出

```
NO```

## 样例 #3

### 输入

```
yahoo```

### 输出

```
YES```

## 样例 #4

### 输入

```
yohaa```

### 输出

```
NO```

# 题解

## 作者：Bronya18C (赞：4)

## 题意

- 度为5的字符串，若其中有1个y，1个a，1个h，2个o，输出YES，否则输出NO

---
## 标签
- 字符串
- 枚举，暴力

---
## 做法
- 模拟，找到1个Y就Y++，（也可以用其他变量），其他也一样。最后判断有没有1个y，1个a，1个h，2个o就行了。

---
## 附上本蒟蒻的代码（这是多么希望RP++啊！（~~手动滑稽~~））
```
#include<bits/stdc++.h>
using namespace std;
long long rp,NOI2018rp,NOIPrp,NOIP2018rp;
string str;
int main()
{
    cin>>str;
    for(int i=0;i<5;i++)
    {
     if(str[i]=='y')rp++;
     if(str[i]=='a')NOI2018rp++;
     if(str[i]=='h')NOIPrp++;
     if(str[i]=='o')NOIP2018rp++;
    }
    if(rp==1&&NOI2018rp==1&&NOIPrp==1&&NOIP2018rp==2)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}
```

---

## 作者：liangbob (赞：3)

### AT_yahoo_procon2017_qual_a 题解

#### 思路分析

题目要求我们判断输入的是否为字符串 ```yahoo```的全排列。

若一个字符串为字符串 ```yahoo```的全排列，则它**所含有的全部字母**一定为字符串 ```yahoo```**所含有的全部字母**。即要求判断下列条件是否**都**成立。

- y 的个数为一个。
- a 的个数为一个。
- h 的个数为一个。
- o 的个数为两个。

统计个数后判断即可。

#### 关键代码

```cpp
int y = 0, a = 0, h = 0, o = 0;
for(int i = 0;i < s.size();i++)
{
    y += (s[i] == 'y');// 因为有就为1，无就为0。刚好起到统计的作用。
    a += (s[i] == 'a');
    h += (s[i] == 'h');
    o += (s[i] == 'o');
}
if(y == 1 && a == 1 && h == 1 && o == 2)
{
    cout << "YES" << endl;
}
else
{
    cout << "NO" << endl;
}
```


---

## 作者：初音Miku (赞：2)

## 首先，题意了解一下      
“给定一个长度为5的字符串，若其中有1个y，1个a，1个h，2个o，输出YES，否则输出NO。
## 感谢@da32s1da 
然后，进入正题
```cpp
#include<iostream>
#include<string>
#include<Hatsune_Miku>//防抄标记
using namespace std;
int a,b,c,d;//自定义变量，随便起
int main()//大哥登场
{
	string s;//定义字符串
	cin>>s;//cin读入
	for(int i=0;i<=5;i++)//由题意得，长度只有5，所以从0循坏，到5即可。
	{
		if(s[i]=='a')a++;//记录a出现的次数
		if(s[i]=='y')b++;//记录y出现的次数
		if(s[i]=='h')c++;//记录h出现的次数
		if(s[i]=='o')d++;//记录o出现的次数
	}
	if(b==1&&a==1&&c==1&&d==2)//如果满足题意，输出YES（注意，大写，大写，大写）
    cout<<"YES"<<endl;
	else cout<<"NO"<<endl;//不满足直接NO结尾
	return 0;
}
```

---

## 作者：不会dp退役菜鸡 (赞：1)

sort真的是个好东西

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[5];
int main()
{
	cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4];//懒得打for了
	sort(a,a+5);//sort一下
	if(a[0]=='a'&&a[1]=='h'&&a[2]==a[3]&&a[2]=='o'&&a[4]=='y') cout<<"YES";
	else cout<<"NO";
    return 0;
}
```

---

