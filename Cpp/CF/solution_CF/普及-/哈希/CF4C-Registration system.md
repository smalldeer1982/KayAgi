# Registration system

## 题目描述

### 题目背景

一个名为 "Berlanddesk" 的电子邮件系统即将在 Berland 上线运营。该电子邮件系统的管理员希望整个系统的建设可以尽早完成，因此他们找到了资深程序员您，希望您能够为他们开发一个用户注册系统的原型产品。

该系统的运行遵循以下原则:

新用户注册时，他将向系统发送一则内容为其用户名的请求，如果该用户名尚未存在于系统数据库内，则将该用户名插入数据库，同时用户得到回应信息 ```OK``` 表示其已经成功注册。如果用户请求的用户名已经存在于数据库内，那么系统将产生一个新的用户名并将其加入数据库。新用户名由用户请求的用户名与正整数 $i$ 构成，$i$ 为使 "用户名i" 尚未存在于数据库内的最小的 $i$。

## 样例 #1

### 输入

```
4
abacaba
acaba
abacaba
acab
```

### 输出

```
OK
OK
abacaba1
OK
```

## 样例 #2

### 输入

```
6
first
first
second
second
third
third
```

### 输出

```
OK
first1
OK
second1
OK
third1
```

# 题解

## 作者：aiyougege (赞：12)

### CF4C 【Registration system】
#### Solution
　　做这道字符串题需要干什么呢?需要判重, 判断一个字符串有没有出现, 出现了几次.

　　所以这个问题用map可以很好解决了.首先需要了解一下map的基本操作:
  
- 建立 `map<string,int>m;`, 从字符串映射到整数.
- 插入 `m[str]=key;`, str为字符串, key为映射到的整数.
- 迭代器 `map<string,int>::iterator it;`, 迭代器相当于是指针(或者说是一种数据类型).
- 查询字符串是否存在 `it=find(str)`, it为对应元素的迭代器.
- 通过迭代器获取元素的整数值 `int key=it->second`, first 是对应的string, second 是对应的字符串.(map中的元素为pair)

　　这样我们就可以将字符串插入map, **不重复**, 每个字符串对应的那个整数就是我们记录**这个字符串出现几次**的数组的**对应下标**.
#### Code
```c++
#include<map>
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;

map<string,int> m;
int co[100005];//字符串出现几次

int main(){
    int n;string str;
    scanf("%d",&n);
    map<string,int>::iterator it;//迭代器
    for(int i=1;i<=n;++i){
        cin>>str;it=m.find(str);//是否出现
        if(it==m.end()){m[str]=i;printf("OK\n");}
        else {
        	int s=it->second;//在数组co中位置
            cout<<str<<++co[s]<<endl;
        }
    }
    return 0;
}
```

---

## 作者：SocietyNiu (赞：11)

看见没有用结构体的，那让我来水一波  
首先定义一个结构体包含姓名及拥有此姓名的用户个数，其次边输入边进行判断，如果未找到则输出“OK”并存储，如果找到就看他有几个，进行++后输出即可
```
#include<iostream>
#include<algorithm>
using namespace std;
struct name
{
	string n;//代表名字
	int num;//代表个数
}a[100005];
int main()
{
	int jl=0;//记录上一次判断字符串所到达位置，缩短时间 
	int N;
	cin>>N;
	for(int i=1;i<=N;i++)
	{
		string c;cin>>c;
		bool flag=0;//标记是否查找到
		for(int j=0;j<=jl;j++)
			if(a[j].n==c) 
  			{
            	a[j].num++;//先加再输出
            	cout<<a[j].n<<a[j].num<<endl;
          	  flag=1;
          	  break;
          	  }
		if(!flag)
			cout<<"OK"<<endl,a[jl++].n=c;
	}
	return 0;
}
```

---

## 作者：MujicaSaki (赞：10)

~~似乎题解没有我的做法~~

### 思路：

模拟就行了，我们可以开两个 map 来做，一个用来存用户名，一个用来判断用户名后面的数字。

如果前面没有重复的就把用户名存进 map 否则的话就输出第二个 map 还没有用过的数字。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
map<string,int> m,m1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(m.find(s)==m.end()){
			m[s]=i;
			cout<<"OK"<<endl;
		}
		else{
			cout<<s<<m1[s]+1<<endl;
			m1[s]++;
		}
	}
}
```


---

## 作者：PC_DOS (赞：10)

本题只需要使用STL的map结构，建立从字符串到整数的对应关系即可。


用户输入一个字符串，先在map中检索是否存在记录，如果不存在(字符串对应的值为0)，则输出"OK"并在map中加入一条以该字符串为索引的记录并赋初值1；如果存在，则输出该字符串本身以及map中该字符串为索引的记录的值，再将字符串为索引的记录的值加一。


代码:

```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std; //头文件和命名空间
map<string, long long> mapDatabase; //定义以string为键类型，long long为值类型的map
int main(){
    ios::sync_with_stdio(false); //一定意义上的输入输出加速
    string sNameInput; //定义字符串，表示用户输入
    long long nCount,i; //nCount-输入个数，i-循环变量
    cin >> nCount; //读入输入个数
    getline(cin, sNameInput); //读取掉输入后留下的不需要的东西
    for (i = 1; i <= nCount; ++i){ //循环读取
        getline(cin, sNameInput); //读入"用户名"
        if (mapDatabase[sNameInput] != 0){ //如果对应值非0，也就是已经有人用这个ID注册过
            cout << sNameInput << mapDatabase[sNameInput] << '\n'; //输出原始字符串和这个ID已被注册的次数
            ++mapDatabase[sNameInput]; //已被注册次数加1
        }
        else{
            cout << "OK\n"; //ID可用
            mapDatabase[sNameInput] = 1; //将这个ID的记录添加到map中并且赋初值1
        }
    }
    return 0; //结束
}
```

---

