# 题目信息

# Train and Peter

## 题目描述

Peter 很喜欢坐火车去旅行。他实在是太喜欢坐火车了，以至于在火车上睡着了（雾）。

在一个夏天，Peter 正在一个从 A 城开往 B 城的列车上。像往常一样，他睡着了。突然，他醒了过来（?），开始看窗外的景物。他发现每一个火车站都有一面彩旗（旗上只有一种颜色）。

Peter 开始记忆他看到的彩旗的顺序。但是很快地，他又睡着了。不幸地，他没睡多久又醒来了，并且他开始继续记他看到的彩旗。一段时间以后，他又睡着了，这次直到旅途结束都没醒来。

到站以后，他告诉了他的父母他在旅途中看到的彩旗的顺序——在他中途睡着之前和中途睡着之后分别看到的两个颜色序列。

他的父母知道 Peter 特别喜欢幻想，所以他们把 Peter 说的序列给了你，并请你判断他的乘车方向。

他的父母用不同的小写字母表示不同的颜色。相同字母表示相同颜色，不同字母表示不同颜色。

## 说明/提示

列车一直都在移动，所以一面同样的旗子不可能被看到两次。

## 样例 #1

### 输入

```
atob
a
b
```

### 输出

```
forward
```

## 样例 #2

### 输入

```
aaacaaa
aca
aa
```

### 输出

```
both
```

# AI分析结果

### 题目内容重写
Peter 很喜欢坐火车去旅行。他实在是太喜欢坐火车了，以至于在火车上睡着了（雾）。

在一个夏天，Peter 正在一个从 A 城开往 B 城的列车上。像往常一样，他睡着了。突然，他醒了过来（?），开始看窗外的景物。他发现每一个火车站都有一面彩旗（旗上只有一种颜色）。

Peter 开始记忆他看到的彩旗的顺序。但是很快地，他又睡着了。不幸地，他没睡多久又醒来了，并且他开始继续记他看到的彩旗。一段时间以后，他又睡着了，这次直到旅途结束都没醒来。

到站以后，他告诉了他的父母他在旅途中看到的彩旗的顺序——在他中途睡着之前和中途睡着之后分别看到的两个颜色序列。

他的父母知道 Peter 特别喜欢幻想，所以他们把 Peter 说的序列给了你，并请你判断他的乘车方向。

他的父母用不同的小写字母表示不同的颜色。相同字母表示相同颜色，不同字母表示不同颜色。

### 说明/提示
列车一直都在移动，所以一面同样的旗子不可能被看到两次。

### 样例 #1
#### 输入
```
atob
a
b
```
#### 输出
```
forward
```

### 样例 #2
#### 输入
```
aaacaaa
aca
aa
```
#### 输出
```
both
```

### 题解分析与结论
这些题解的核心思路都是通过在原字符串和反转后的字符串中查找给定的两个子串，判断它们是否按顺序出现，从而确定列车的行驶方向。主要使用了C++的`string`类中的`find`函数和`reverse`函数。

#### 关键思路与技巧
1. **字符串查找**：使用`find`函数在字符串中查找子串，并确保第二个子串出现在第一个子串之后。
2. **字符串反转**：通过`reverse`函数反转字符串，模拟列车反向行驶的情况。
3. **条件判断**：根据查找结果判断列车的行驶方向，输出相应的结果。

#### 可拓展之处
1. **多子串查找**：可以扩展到查找多个子串的顺序，判断更复杂的行驶方向。
2. **其他语言实现**：类似的思路可以应用于其他编程语言，如Python、Java等。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
3. [P3371 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P3371)

### 精选题解
#### 题解作者：SIXIANG32 (赞：8)
**星级：5星**
**关键亮点**：代码简洁，使用三目运算符进行条件判断，逻辑清晰。
**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{ 
	string s1,s2,s3,cs1;
	cin>>s1>>s2>>s3,cs1=s1,reverse(cs1.begin(),cs1.end());
	int pos1=s1.find(s2),pos2=cs1.find(s2),f1=s1.find(s3,pos1+s2.size()),f2=cs1.find(s3,pos2+s2.size());
	cout<<((pos1==-1&&pos2==-1)?("fantasy"):((f1!=-1&&f2==-1)?("forward"):((f1==-1&&f2!=-1)?("backward"):((f1!=-1&&f2!=-1)?("both"):("fantasy"))))); 
}
```

#### 题解作者：Forever1507 (赞：6)
**星级：4星**
**关键亮点**：代码可读性强，注释详细，适合初学者理解。
**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	bool forward=0,backward=0;
	string a,b,c;
	getline(cin,a);
	getline(cin,b);
	getline(cin,c);
	int a1=a.size();
	if(a.find(b)<=a1&&a.find(c,a.find(b)+b.size())<=a1){
		forward=1;
	}
	reverse(a.begin(),a.end());
	if(a.find(b)<=a1&&a.find(c,a.find(b)+b.size())<=a1){
		backward=1;
	}
	if(forward==1&&backward==1){
		cout<<"both";
	}
	else if(forward==1){
		cout<<"forward";
	}
	else if(backward==1){
		cout<<"backward";
	}
	else{
		cout<<"fantasy";
	}
	return 0;
}
```

#### 题解作者：Soshine_溯闪 (赞：1)
**星级：4星**
**关键亮点**：思路清晰，代码结构合理，逻辑明确。
**核心代码**：
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
string a,b,c;
int ok1,ok2;
int main(){
	cin>>a>>b>>c;
	ok1=ok2=0;
	int fb1=a.find(b,0);
	int fc1=a.find(c,fb1+b.length());
	if(fb1<a.size()&&fb1>=0&&fc1<a.size()&&fc1>=0) ok1=1;
	reverse(a.begin(),a.end());
	int fb2=a.find(b,0);
	int fc2=a.find(c,fb2+b.length());
	if(fb2<a.size()&&fb2>=0&&fc2<a.size()&&fc2>=0) ok2=1;
	if(ok1&&ok2) cout<<"both"<<endl;
	else if(!ok1&&!ok2) cout<<"fantasy"<<endl;
	else if(ok1&&!ok2) cout<<"forward"<<endl;
	else if(!ok1&&ok2) cout<<"backward"<<endl;
	return 0;
}
```

---
处理用时：39.20秒