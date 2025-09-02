# Gena's Code

## 题目描述

给定 $n$ 个整数 $a_1, a_2, a_3,..., a_n$，求它们的乘积（保证有且仅有一个数 $a_i$ 满足 $\log_{10}a_i$ 不为整数）。

## 说明/提示

第一个样例中，$5\times 10\times 1 = 50$。

第二个样例中，$1\times 1\times 10\times 11 = 110$。

第三个样例中，由于 $0$ 的出现，乘积为 $0$。

## 样例 #1

### 输入

```
3
5 10 1
```

### 输出

```
50```

## 样例 #2

### 输入

```
4
1 1 10 11
```

### 输出

```
110```

## 样例 #3

### 输入

```
5
0 3 1 100 1
```

### 输出

```
0```

# 题解

## 作者：EatBread (赞：4)

## 题目描述：

这道题的题目翻译有问题 （或者是数据问题？）

题目说**保证有且仅有一个数 $a_i$ 满足 $\log_{10}$ $ai$ 不为整数**。

但在第九个点中却都是 $10$ 的幂次方，害得我蒙了好一会。

# 思路：
其实简单，因为最多只有一个数不是 $10$ 的幂次方，也就是说，除了那一个数，其他的数全部是一个 $1$ 后面 $n$ 个 $0$ ，而乘上之后 $1$ 忽略不计，也就是：除了那个不是 $10$ 的幂次方的数，其他的都可以转化为 $size-1$ 个 $0$ 。

而怎样找出那个不是 $10$ 的幂次方的数呢？可以用字符串中的
`find_last_not_of('0')`函数，大概作用是：倒着找某个字符串中第一个不是子串`‘0’`的位置，所以一旦这个位置不是零或者第零位不是一就找到了。

输出也不需要单独输出 $0$ 可以用一个字符串存起来，统一输出，也就是将是 $10$  的幂次方的数的第一位用`erase`删掉，再另用一个字符串存起剩下的数，结尾统一输出。

**注意：有可能全是 $1$ 所以要特判。**


## 程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c;
int n,k; 
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		cin>>a;
		if(a=="0"){cout<<0;return 0;}
		if(a.find_last_not_of('0')!=0&&a.size()>1||a[0]!='1'){c=a;}
		else{a.erase(0,1);b+=a;}
	}
	if(c=="")c="1";
	cout<<c<<b;
	return 0;
}
```


---

## 作者：lbh666 (赞：1)

## 题目大意
给出 $n$ 个数，保证只有一个不是 $10 ^ x$，求它们的乘积。

## 前置知识
- $10 ^ x$ 乘一个数，相当于在这个数后面加上 $x$ 个 $0$。

## 思路分析
题目数据范围很大，暴力是不能过的，考虑优化。

- 当某一个数是 $0$ 时，直接输出 $0$。

- 当某一个数是 $1$ 时，直接跳过，因为它对答案没有贡献。

- 其它的数做一次统计后导 $0$ 的操作，并删去这些 $0$。

- 判断是否是 $10 ^ x$，如果是，把统计好的后导 $0$ 加进答案里，如果不是，就把这个数不是后导 $0$ 的部分记录，其余 $10 ^ x$ 就只要加上 $x$ 个 $0$ 就好了。

- 统计答案并输出。

## AC Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,sum,tot=0;
string s,s2,s3,s4;

int main(){
	cin>>n;
	while(n--){
		cin>>s2; 
		s4=s2; //保存字符串 
		if(s2=="0"){
			cout<<0;
			return 0;
		}else if(s2=="1")continue;//处理0或1的情况 
		for(int i=s2.size()-1;i>=0;--i){
			if(s2[i]=='0'){
				s+="0"; //统计后导0，加进答案字符串s中 
				s4.erase(i,1);//一边同时在s4中做删除操作 
			}else break;
		}
		if(s4!="1")s3+=s4;//如果这个数不是10的x次方，统计前面的部分 
	}
	if(s3=="")s3="1"; //特判是否是空串，如果是，就说明n个数都是10的x次方 
	cout<<s3<<s;//输出 
	return 0;
}
```

---

## 作者：atarashiTLE (赞：1)

字符串水题。

---
### 题意简述：
输入n及n个高精度数（位数不超过$10^5$位），输出它们的乘积（保证有且仅有一个数$\log_{10}$不为整数）。

---
### 思路:
考虑高精度，发现$O(n(10^5)^2)$，TLE。

我们发现有且仅有一个数$\log_{10}$不为整数,所以考虑字符串。

首先，保存那个$\log_{10}$不为整数的数，在输出时直接输出它。

其次，统计输入中$0$的个数($n$)，在输出中输出$n$个$0$。

---
code:
```cpp
#include<bits/stdc++.h>
#define N 100010
using namespace std;
string c,ans="114514,1919810";
int n,zeronum;
bool pd(string n){
	if(n[0]!='1')	
		return true;
	for(int i=1;i<n.size();i++)
		if(n[i]!='0')return true;
	return false;
}
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>c;
		if(c=="0"){
			cout<<0<<endl;
			return 0;
		}
		else if(pd(c)&&ans=="114514,1919810")
			ans=c;
		else zeronum+=max(0,(int)(c.length()-1));
	}
	if(ans=="114514,1919810")
		cout<<1;
	else cout<<ans;
	while(zeronum>0){
		cout<<0;
		zeronum--;
	}
	cout<<endl;
    return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 题意简述
> 给定 $n$ 个数 $a_1,a_2,a_3 \dots a_n$，求它们的乘积。

## 开始解题！
不用看，这一题就是高精，但是，Python 自带高精，对于 Python 来说，正常写即可，代码如下：
```python
a=int(input())
b=input().split()
ans=1
for i in range(a):
    ans*=int(b[i])
print(ans)
```

---

## 作者：shenbairui (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF614B)

### 题目大意

给定 $n$ 个整数 $a_1, a_2, a_3,\dots, a_n$，求它们的乘积。

### 题目分析

众所周知，Python 自带高精，所以可以用 Python 水过！

### 代码

```python
a=int(input())
b=input().split()
c=1
for i in range(a):
    c*=int(b[i])
print(c)
```

#### 下期见！拜拜！

---

## 作者：zsh_haha (赞：0)

### 解题思路

瞟了一眼，发现是高精度乘法，可以用 Python 水过，大喜！

### AC 代码

```python
n=int(input())
pro=1
x=list(input().split());
while n>0:
    n-=1
    pro*=int(x[n])
print(pro)
```

---

## 作者：InfSauf (赞：0)

输入 $n$ 个正整数，保证只有 $1$ 个不是 $10^n$。

刚看到题，直接累乘，结果精度不够，爆 ```int``` 了，然后用 ```long long``` 爆了，```int128``` 照爆不误。

我们换种方法，用字符串去输入，```vector``` 存储答案，对各种情况进行分类讨论：

1. 输入数字的最高位不是 $1$ 则记录下来，因为这一定不是 $10^n$。
2. 输入数字最后一位不是 $0$ 则记录下来，因为这也一定不是 $10^n$。
3. 输入数字中含有多个 $1$ 则记录下来，因为这也一定不是 $10^n$。

在讨论完之后，也就能写出来了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s, b = "";
vector<int> v;
int num;
signed main(){
	int n;
	int sum;
	cin >> n;
	for(int i = n; i --> 0;){
		//int a;
		cin >> s;
		if(n == 1){//如果只有一个数则输入直接输出 
			cout << s;
			return 0;
		}
		if(s == "0"){//如果有0则直接输出0 
			cout << 0;
			return 0;
		}
		for(int j = 0; j < s.size(); j++){//统计10^n 中0的个数 
			if(s[j] == '1')num++;
		}
		if((num >= 2 || s[s.size() - 1] != '0' || s[0] != '1')&& s != "1")b = s;//分类讨论部分 
		
		else{
			for(int i = 1; i < s.size(); i++){//往答案后面加入0 
				v.push_back(s[i] - '0');
			}
		}
		num = 0;
	}
	if(b == ""){//没有不是10^n的数 
		cout << 1;
		for(int i = 0; i < v.size(); i++)cout << 0;
	}
	else{
		cout << b;
		for(int i = 0; i < v.size(); i++)cout << 0;
	}
}
```


---

## 作者：xiaofeng_and_xiaoyu (赞：0)

~~python 大法好！~~

高精题用 python，直接累乘就可以了。

给出不到 $100\mathrm{B}$ 的代码：
```python
a=int(input())
b=input().split()
c=1
for i in range(a):
    c*=int(b[i])
print(c)
```


---

## 作者：19x31 (赞：0)

## 题意
给出 $n-1$ 个为 $10^k$ 的数，以及一个不为 $10^k$ 的数，求他们的乘积。

## 思路
首先考虑高精，$O((10^{5\times2})n)$ 超时。

但是我们知道，在乘法里，$10^k$ 这类数可以直接转化为 $0$ 输出，所以不妨换个思路，储存那个不为 $10^k$ 的数，直接输出，再算需要输出几个 $0$。

首先，怎么找到那个不为 $10^k$ 的数，你可以用 ```find_last_not_of('0')``` 函数，也可以直接枚举。

其次，剩下的数因为是以字符串储存的，直接加上 $size-1$ 个 $0$ 即可。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
string s;
int n,sum; 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s=="0"){
			cout<<0;
			return 0;
		}//特判0 
		if(s.find_last_not_of('0')!=0&&s.size()>1||s[0]!='1'){
			cout<<s;//不是10的幂次方的数 
		}else{
			sum+=s.size()-1;
		}//是10的幂次方的数
	}
	for(int i=1;i<=sum;i++){
		cout<<0;
	}
	if(sum==0)cout<<1;//特判1 
	return 0;
}
```



---

## 作者：codeLJH114514 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF614B)

# 题目大意

给你 $n$ 个高精度整数 $a_1, a_2, a_3, \cdots, a_n$，要你计算 $\prod^{n}_{i = 1}a_i$

## 特殊条件 (坑点)

这里我稍微更改一下原题条件，原题说**有且仅有** $1$ 个数 $\log_{10}$ 不是整数，其实在 #$9$ 中全是 $\log_{10}$ 是整数的数，所以条件应改为**至多有** $1$ 个数 $\log_{10}$ 不为整数。(我待会会说我是怎么发现的。)

# 解题思路

该题的特殊条件很重要!

暴力:

可以直接用高精度计算出 $\prod^{n}_{i = 1}a_i$，时间复杂度为 $\mathit{\Theta}(n l^2)$ ($l$ 为数最大长度，在本题中 $l \to 10^5$) 该数为 $10^5 \times (10^5)^2 \to 10^{15}$，TLE。

正解:

考虑字符串，把不是 $10$ 的整次幂的数存下来，输出它，再统计输入的是 $10$ 的整次幂的数的 $0$ 的个数 ($m$)，输出 $m$ 个 $\texttt{0}$。

代码 ($\color{red}{\text{WA}}$):

```cpp
#include <iostream>
#include <vector>
#define maxn 131072
using namespace std;
vector<string> v;
string is[maxn];
int n;
string Ten, NotZero;
int IsBase10(string);
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> is[i];
    for (int i = 1; i <= n; i++)
        if (is[i] == "0") {
            cout << "0"; // 如果有0则直接输出0并退出程序
            return 0;
        } else if (is[i] != "1")
            v.push_back(is[i]); // 乘以1等于没乘，所以只有不是1的才加入vector
    n = 0;
    for (auto i : v) {
        int Zero = IsBase10(i);
        if (not Zero)
            NotZero = i;
        else 
            n += Zero;
    } // 计算0的个数和不为10的整次幂的数
    cout << NotZero;
    for (int i = 1; i <= n; i++)
        cout << '0'; // 输出
    return 0;
}
// 函数功能 : 如果s不是10的整次幂，返回0，否则返回log10(s)
int IsBase10(string s) { 
    if (s[0] != '1')
        return 0;
    for (int i = 1; i < s.size(); i++)
        if (s[i] != '0')
            return 0;
    return s.size() - 1;
}
```

错误提示:

```
Wrong Answer.
Wrong output format
000000000000000000000000000000...0000000000000000000000000000000
is not a valid integer
```

有评测记录为证 : [WA](https://www.luogu.com.cn/record/71260927)

所以我们需要一个标记：

如果到最后 $\text{NotZero}$ 还是空字符串，那么先输出 $1$, 再输出 $m$ 个 $0$。

AC Code:

```cpp
#include <iostream>
#include <vector>
#define maxn 131072
using namespace std;
vector<string> v;
string is[maxn];
int n;
string Ten, NotZero;
int IsBase10(string);
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> is[i];
    for (int i = 1; i <= n; i++)
        if (is[i] == "0") {
            cout << "0";
            return 0;
        } else if (is[i] != "1")
            v.push_back(is[i]);
    n = 0;
    for (auto i : v) {
        int Zero = IsBase10(i);
        if (not Zero and NotZero == "")
            NotZero = i;
        else 
            n += Zero;
    }
    if (NotZero == "")
        cout << 1; // 坑点!!
    else
        cout << NotZero;
    for (int i = 1; i <= n; i++)
        cout << '0';
    return 0;
}
int IsBase10(string s) {
    if (s[0] != '1')
        return 0;
    for (int i = 1; i < s.size(); i++)
        if (s[i] != '0')
            return 0;
    return s.size() - 1;
}
```

---

