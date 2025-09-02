# [FJCPC 2025] 致谢 | FJCPC2025全体参赛选手&赛事staff

## 题目描述

亲爱的参赛者：

衷心感谢你参与第十二届福建省大学生程序设计竞赛暨福建邀请赛。

同时，向在比赛幕后默默付出的教练老师和赛事组织人员致以诚挚的谢意，正是因为你们的辛勤付出，比赛才能顺利进行。

此外，也要感谢历届福建省赛(FJCPC)的承办院校为该系列赛事所做出的巨大贡献。

接下来是历届福建省赛(FJCPC)的承办院校及其比赛时间的具体信息：

| 届数 | 比赛时间     | 承办院校               | 英文名                          | 缩写 |
|------|----------------|--------------|-----------------|----------|
| 1    | 2010-5-23    | 福州大学               | Fuzhou University               | FZU      |
| 2    | 2011-5-15    | 福建师范大学           | Fujian Normal University        | FNU      |
| 3    | 2012-12-02   | 福州大学               | Fuzhou University               | FZU      |
| 4    | 2013-12-15   | 福州大学               | Fuzhou University               | FZU      |
| 5    | 2014-11-30   | 福建农林大学           | Fujian Agriculture and Forestry University | FAFU     |
| 6    | 2015-12-20   | 华侨大学               | Huaqiao University              | HQU      |
| 7    | 2016-5-22    | 闽江学院               | Minjiang University             | MJU      |
| 8    | 2017-5-17    | 厦门理工学院           | Xiamen University of Technology | XMUT     |
| 9    | 2018-6-10    | 泉州师范学院           | Quanzhou Normal University      | QNU      |
| 10   | 2019-5-19    | 集美大学               | Jimei University                | JMU      |
| 11   | 2024-5-26    | 福州大学               | Fuzhou University               | FZU      |

 CFJ 希望你能输出第 $n$ 届FJCPC的承办院校英文缩写。

再次向所有为第十二届福建省大学生程序设计竞赛暨福建邀请赛奉献力量的每一个人表示最衷心的感谢！

也祝愿你能比赛中取得理想的成绩！

## 说明/提示

由表可知，第一届 FJCPC 承办校是福州大学，第二届 FJCPC 承办校是福建师范大学。

## 样例 #1

### 输入

```
1```

### 输出

```
FZU```

## 样例 #2

### 输入

```
2```

### 输出

```
FNU```

# 题解

## 作者：wf2025 (赞：6)

这是一个简单的查找表问题，根据输入的届数直接输出对应的缩写。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	string A[] = {
		"FZU", "FNU", "FZU", "FZU", "FAFU",
		"HQU", "MJU", "XMUT", "QNU", "JMU", "FZU"
	};
	int n;
	cin >> n;
	if(n >= 1 && n <= 11) {
		cout << A[n-1] << endl;
	}
	return 0;
}

```

---

## 作者：0Io_oI0 (赞：5)

罕见语法题！

可以发现：
- 当 $n=1,3,4,11$ 时，应该输出 `FZU`。
- 当 $n=2$ 时，应该输出 `FNU`。
- 当 $n=5$ 时，应该输出 `FAFU`。
- 当 $n=6$ 时，应该输出 `HQU`。
- 当 $n=7$ 时，应该输出 `MJU`。
- 当 $n=8$ 时，应该输出 `XMUT`。
- 当 $n=9$ 时，应该输出 `QNU`。
- 当 $n=10$ 时，应该输出 `JMU`。

然后套上分支结构即可 AC 本题！

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    if(n==1||n==3||n==4||n==11)puts("FZU");
    else if(n==2)puts("FNU");
    else if(n==5)puts("FAFU");
    else if(n==6)puts("HQU");
    else if(n==7)puts("MJU");
    else if(n==8)puts("XMUT");
    else if(n==9)puts("QNU");
    else puts("JMU");
    return 0;
}
```
亲测可过，请勿抄袭！

---

## 作者：popcorn_pizza_3 (赞：4)

这道题数据量很小，我们可以打表，把所有的答案存到一个字符串数组里，对于每个测试点输出对应的答案即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s[15]={"","FZU","FNU","FZU","FZU","FAFU","HQU","MJU","XMUT","QNU","JMU","FZU"};
int n;
int main(){
	cin>>n;
	cout<<s[n];
}
```

---

## 作者：easy42 (赞：3)

这是一道简单的模拟题，考察分支语句。

按 $n$ 的表分类输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
signed main() {
	cin>>n;
	if(n==1) cout<<"FZU";
	else if(n==2) cout<<"FNU";
	else if(n==3) cout<<"FZU";
	else if(n==4) cout<<"FZU";
	else if(n==5) cout<<"FAFU";
	else if(n==6) cout<<"HQU";
	else if(n==7) cout<<"MJU";
	else if(n==8) cout<<"XMUT";
	else if(n==9) cout<<"QNU";
	else if(n==10) cout<<"JMU";
	else if(n==11) cout<<"FZU";
	return 0;
}
```

---

## 作者：__CJY__ (赞：3)

## 思路
建一个 `string` 类型的数组 $s$，把每一届的缩写都存进去。为了方便操作，可以将 $s_0$ 设为空（其实就是用来占位），最后直接输出 $s_n$ 即可。
>|届数|比赛时间|承办院校|英文名| 缩写 |
>|:-:|:-:|:-:|:-:|:-:|
>|1|2010-5-23|福州大学|Fuzhou University|FZU|
>|2|2011-5-15|福建师范大学|Fujian Normal University|FNU|
>|3|2012-12-02|福州大学|Fuzhou University|FZU|
>|4|2013-12-15|福州大学|Fuzhou University|FZU|
>|5|2014-11-30|福建农林大学|Fujian Agriculture and Forestry University|FAFU|
>|6|2015-12-20|华侨大学|Huaqiao University|HQU|
>|7|2016-5-22|闽江学院|Minjiang University|MJU|
>|8|2017-5-17|厦门理工学院|Xiamen University of Technology|XMUT|
>|9|2018-6-10|泉州师范学院|Quanzhou Normal University|QNU|
>|10|2019-5-19|集美大学|Jimei University|JMU|
>|11|2024-5-26|福州大学|Fuzhou University|FZU|
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s[]={"","FZU","FNU","FZU","FZU","FAFU","HQU","MJU","XMUT","QNU","JMU","FZU"};
int main(){
	int n;cin>>n;
	cout<<s[n];
}
```

---

## 作者：Clare613 (赞：3)

## 思路：
这是本场比赛最水的题目，只需要按照题目模拟即可，表格如下：
| 届数 | 比赛时间     | 承办院校               | 英文名                          | 缩写 |
|------|----------------|--------------|-----------------|----------|
| 1    | 2010-5-23    | 福州大学               | Fuzhou University               | FZU      |
| 2    | 2011-5-15    | 福建师范大学           | Fujian Normal University        | FNU      |
| 3    | 2012-12-02   | 福州大学               | Fuzhou University               | FZU      |
| 4    | 2013-12-15   | 福州大学               | Fuzhou University               | FZU      |
| 5    | 2014-11-30   | 福建农林大学           | Fujian Agriculture and Forestry University | FAFU     |
| 6    | 2015-12-20   | 华侨大学               | Huaqiao University              | HQU      |
| 7    | 2016-5-22    | 闽江学院               | Minjiang University             | MJU      |
| 8    | 2017-5-17    | 厦门理工学院           | Xiamen University of Technology | XMUT     |
| 9    | 2018-6-10    | 泉州师范学院           | Quanzhou Normal University      | QNU      |
| 10   | 2019-5-19    | 集美大学               | Jimei University                | JMU      |
| 11   | 2024-5-26    | 福州大学               | Fuzhou University               | FZU      |

其中只有第一列和最后一列有用，按照届数输出即可。
## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	int id;
	cin>>id;
	if(id==1) cout<<"FZU";
	if(id==2) cout<<"FNU";
	if(id==3) cout<<"FZU";
	if(id==4) cout<<"FZU";
	if(id==5) cout<<"FAFU";
	if(id==6) cout<<"HQU";
	if(id==7) cout<<"MJU";
	if(id==8) cout<<"XMUT";
	if(id==9) cout<<"QNU";
	if(id==10) cout<<"JMU";
	if(id==11) cout<<"FZU";
	return 0;
}
```

---

## 作者：LoongPig (赞：2)

## 思路

直接按题目中的表格写判断就好了。

| 届数 | 比赛时间     | 承办院校               | 英文名                          | 缩写 |
|------|----------------|--------------|-----------------|----------|
| 1    | 2010-5-23    | 福州大学               | Fuzhou University               | FZU      |
| 2    | 2011-5-15    | 福建师范大学           | Fujian Normal University        | FNU      |
| 3    | 2012-12-02   | 福州大学               | Fuzhou University               | FZU      |
| 4    | 2013-12-15   | 福州大学               | Fuzhou University               | FZU      |
| 5    | 2014-11-30   | 福建农林大学           | Fujian Agriculture and Forestry University | FAFU     |
| 6    | 2015-12-20   | 华侨大学               | Huaqiao University              | HQU      |
| 7    | 2016-5-22    | 闽江学院               | Minjiang University             | MJU      |
| 8    | 2017-5-17    | 厦门理工学院           | Xiamen University of Technology | XMUT     |
| 9    | 2018-6-10    | 泉州师范学院           | Quanzhou Normal University      | QNU      |
| 10   | 2019-5-19    | 集美大学               | Jimei University                | JMU      |
| 11   | 2024-5-26    | 福州大学               | Fuzhou University               | FZU      |

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    if(n==1||n==3||n==4||n==11) cout<<"FZU";
    if(n==2) cout<<"FNU";
    if(n==5) cout<<"FAFU";
    if(n==6) cout<<"HQU";
    if(n==7) cout<<"MJU";
    if(n==8) cout<<"XMUT";
    if(n==9) cout<<"QNU";
    if(n==10) cout<<"JMU";
    return 0;
}
```

---

## 作者：Doraeman (赞：2)

哇，我抢到了**红题的首个 AC** 和**红题题解提交通道**！~~上次抢到还是在上次。~~
## 解法
### 解法 A
根据表格，把所有院校的名字写到一个字符串数组中，问哪个就输出哪个。
### 解法 B
写 $11$ 个 ```if```，判断 $n$ 的值并输出对应的院校。比较麻烦。
## 代码
### 解法 A 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

string name[] = {
"", "FZU", "FNU", "FZU", "FZU", "FAFU", 
"HQU", "MJU", "XMUT", "QNU", "JMU", "FZU"
};

int main(){
    int n; cin >> n;
    cout << name[n];
}
```

---

## 作者：swate114514 (赞：2)

要求输出第 $n$ 届 FJCPC 的承办院校英文缩写，可以把所有英文缩写存在一个数组里，然后输出即可。

### Code
```cpp
#include <bits/stdc++.h>
#define qwq(i,a,b) for(int i=(a);i<=(b);++i)
#define qaq(i,a,b) for(int i=(a);i>=(b);--i)

using namespace std;

typedef long long ll;

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	string s[] = {
		"FZU",
		"FNU",
		"FZU", 
		"FZU",
		"FAFU",
		"HQU", 
		"MJU", 
		"XMUT", 
		"QNU",
		"JMU",
		"FZU"
	};
	
	int n;
	cin >> n;
	cout << s[n - 1] << endl;
}
```

---

## 作者：L_T_L (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P13101)

这道题目非常简单，考察判断语句与输出语句的应用。只需按照表格，根据输入的 $n$ 输出对应的校名缩写即可。

CODE：

```cpp
#include<iostream>
using namespace std;
int n;
int main(){
    cin>>n;
    if(n==1)
        cout<<"FZU";
    else if(n==2)
        cout<<"FNU";
    else if(n==3)
        cout<<"FZU";
    else if(n==4)
        cout<<"FZU";
    else if(n==5)
        cout<<"FAFU";
    else if(n==6)
        cout<<"HQU";
    else if(n==7)
        cout<<"MJU";
    else if(n==8)
        cout<<"XMUT";
    else if(n==9)
        cout<<"QNU";
    else if(n==10)
        cout<<"JMU";
    else
        cout<<"FZU";
    return 0;
}
```

---

## 作者：AFO_Lzx (赞：2)

这题竟然没关题解通道。

打表并根据表内序号输出即可。

```cpp
#include<bits/stdc++.h>
using ll = long long;
using namespace std;

const string s[] = {"FZU", "FNU", "FZU", "FZU", "FAFU", "HQU", "MJU", "XMUT", "QNU", "JMU", "FZU"};

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int x;
	cin >> x;
	cout << s[x - 1];
	return 0;
}
```

注意代码中数组起始下标为 $0$。

---

## 作者：GSQ0829 (赞：2)

### 解题思路：
这道题很简单，~~疑似出题组没有出题的思路，随便出的一道题~~。这题就是判断 $n$ 是多少，然后根据题目中的列表，去对应出是哪个院校的缩写，最后输出即可。

---
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
	cin >> n;
	if (n == 1 || n == 3 || n == 4 || n == 11) cout << "FZU";
	if (n == 2) cout << "FNU";
	if (n == 5) cout << "FAFU";
	if (n == 6) cout << "HQU";
	if (n == 7) cout << "MJU";
	if (n == 8) cout << "XMUT";
	if (n == 9) cout << "QNU";
	if (n == 10) cout << "JMU";
	return 0;
}
```

---

## 作者：SatoruXia (赞：1)

这是本场比赛的签到题吧。  
具体做法：按照表中数据，将缩写以字符串形式一个个写入数组中，最后按下标输出即可。  
注意数组下标从 $0$ 开始。

```cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
    string a[12]={"","FZU","FNU","FZU","FZU","FAFU","HQU","MJU","XMUT","QNU","JMU","FZU"};
    int n;
    cin>>n;
    cout<<a[n];
    return 0;
}
```

---

## 作者：Zskioaert1106 (赞：1)

题目传送门：[P13101 致谢 | FJCPC2025全体参赛选手&赛事staff](https://www.luogu.com.cn/problem/P13101)

将所有名字按编号存在数组里，输出即可。

数组下标从 $0$ 开始。

```cpp
#include<iostream>
const std::string a[]={"","FZU","FNU","FZU","FZU","FAFU","HQU","MJU","XMUT","QNU","JMU","FZU"};
int main(){
    short n;
    std::cin>>n;
    std::cout<<a[n];
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/222595306)。

---

## 作者：yueyan_WZF (赞：0)

感觉本题就是红题难度。

可以定义一个字符串数组，用来存每届的缩写，$i$ 届就是下标为 $i-1$ 的字符串。


```cpp
#include<bits/stdc++.h>
using namespace std;
string a[20]={"FZU","FNU","FZU","FZU","FAFU","HQU","MJU","XMUT","QNU","JMU","FZU"};
int n;
signed main(){
    cin>>n;
    cout<<a[n-1]; //数组下标从 0 开始。
}
```

---

## 作者：M1__ (赞：0)

# 题解：P13101 致谢 | FJCPC2025全体参赛选手&赛事staff

按题意模拟即可。

由题意可得，每一个编号都对应了一所对应的高校。

所以我们使用分支结构判断编号。输出对应的高校缩写即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
int main(){
    cin>>n;
    if(n==1) cout<<"FZU";
    if(n==2) cout<<"FNU";
    if(n==3) cout<<"FZU";
    if(n==4) cout<<"FZU";
    if(n==5) cout<<"FAFU";
    if(n==6) cout<<"HQU";
    if(n==7) cout<<"MJU";
    if(n==8) cout<<"XMUT";
    if(n==9) cout<<"QNU";
    if(n==10) cout<<"JMU";
    if(n==11) cout<<"FZU";
    return 0;
}
```

---

