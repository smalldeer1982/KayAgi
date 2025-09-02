# Reversing Encryption

## 题目描述

A string $ s $ of length $ n $ can be encrypted by the following algorithm:

- iterate over all divisors of $ n $ in decreasing order (i.e. from $ n $ to $ 1 $ ),
- for each divisor $ d $ , reverse the substring $ s[1 \dots d] $ (i.e. the substring which starts at position $ 1 $ and ends at position $ d $ ).

For example, the above algorithm applied to the string $ s $ ="codeforces" leads to the following changes: "codeforces" $ \to $ "secrofedoc" $ \to $ "orcesfedoc" $ \to $ "rocesfedoc" $ \to $ "rocesfedoc" (obviously, the last reverse operation doesn't change the string because $ d=1 $ ).

You are given the encrypted string $ t $ . Your task is to decrypt this string, i.e., to find a string $ s $ such that the above algorithm results in string $ t $ . It can be proven that this string $ s $ always exists and is unique.

## 说明/提示

The first example is described in the problem statement.

## 样例 #1

### 输入

```
10
rocesfedoc
```

### 输出

```
codeforces
```

## 样例 #2

### 输入

```
16
plmaetwoxesisiht
```

### 输出

```
thisisexampletwo
```

## 样例 #3

### 输入

```
1
z
```

### 输出

```
z
```

# 题解

## 作者：Trollz (赞：7)

~~终于找到我会的了~~

本蒟蒻第一次提交题解，如果不好请见谅。

这道题的意思就是从$1$遍历到$n$（字符串长度），如果$n$可以被$i$整除，就反转这个字符串，范围是第一个字符到这个字符串的第$n$个字符。

所以这道题很简单，只要你知道怎么翻转，就OK了啦！

$Code:$
```
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
string a;
int main(){
	int t;
	cin>>t>>a;
	for(int i=2;i<=t;i++){
		if(t%i==0){
			reverse(a.begin(),a.begin()+i);
		}else{
			continue;
		}
	}
	cout<<a;
	return 0;
}
```
### 那么，reverse是什么？
$reverse$是反转函数，在这里可以把一个字符串从第$n$个元素到第$m$个元素进行反转。

用法：
typedef typename _Iterator::iterator_category iterator_category\
其中iterator代表指针。翻译出来就是(开始指针，目标指针)。

所以如果你从头要反转一个字符串，那么只要输入reverse(a.begin()[代表这个字符串的开头],a.begin+s[代表目标指针])。

注意：反转字符串时，指针里不可以用$a[i]$这种，那是因为它们代表的是一个字符。

#### 最后，新人写题解不易，望审核大大通过！


---

## 作者：Register (赞：5)

### 模拟大水题

这题没有翻译，先奉上题目大意吧：

	有个字符串长度为n
    从1~n挨个遍历，如果能被n整除，那就翻转从1到这里的整个区间
    
这里不是下标，一定要记住！

翻转字符串区间，只需要循环长度除以2次，从头尾逼近中心

奉上代码：
```cpp
#include <iostream>
using namespace std;
int main(){
	int n;
	string s;
	cin>>n>>s;
	for(register int i=1;i<=n;i++)
		if(n%i==0)//如果被整除
			for(register int j=0;j<i/2;j++) {char temp=s[j];s[j]=s[i-j-1];s[i-j-1]=temp;}//将整个区间翻转
	cout<<s<<endl;
	return 0;
}
```

---

## 作者：风浔凌 (赞：2)

那个。。。我只是来介绍一个STL——reverse的用法的。

这个东西呢。。。可以在一定范围内使字符串反转。

举一个超级超级简单的例子吧：
比如一个字符串abcdefg如何变成fedcbag——

```c
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int main(){
	string s="abcdefg";
    reverse(s.begin(),s.end()-1);
	cout<<s<<endl;
    return 0;
}

```

呐。。还是蛮好玩的，因为这个也可以操作字符数组：

比如下面的代码也可以达到同样的效果：
```c
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int main(){
	char s[]="abcdefg";
    reverse(s,s+6);
	cout<<s<<endl;
    return 0;
}
```
啊。。那么这道题就很简单了。。。
```c
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int main(){
	int n;
	cin>>n;
	string s;
    cin>>s;
    for(int i=1;i<=n;i++)
    {
    	if(n%i!=0) continue;
    	reverse(s.begin(),s.begin()+i);
    	//cout<<i<<" "<<s<<endl;
	}
	cout<<s<<endl;
    return 0;
}

```

---

## 作者：_lgh_ (赞：0)

# 思路：
#### ~~蒟蒻提供另一种做法~~
使用一个数组记录 $n$ 的因子，然后共翻转其因子个数的轮数，对于每轮，交换当前因子的个数的一半。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
int prime[105],n;
int main()
{
  cin>>n>>str;
  if(n==1) cout<<str;
  else if(n==2)
  {
    swap(str[0],str[1]);
    cout<<str;
  }
  else if(n==3)
  {
    swap(str[0],str[2]);
    cout<<str;
  }
  else
  {
    int cnt=0;
    for(int i=1; i<=n; i++) //记录因子
      if(n%i==0) prime[cnt++]=i;//如果可以整除就存入
    for(int i=0; i<cnt; i++) //总共交换的次数为因子个数
      for(int j=0; j<prime[i]/2; j++) //每轮交换共交换 因子/2次
        swap(str[j],str[prime[i]-j-1]);
    cout<<str;
  }
  return 0;
}
```

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF999B)
# 前置芝士：

[reverse 的用法](https://www.cnblogs.com/yuanch2019/p/11591995.html)

# 思路：

枚举从 $1$ 到 $n$ 的每一个数

设当前数为 $i$

如果 $i$ 能被 $n$ 整除，那么就翻转从 $1$ 到 $i$ 的字符串

# AC CODE:
```cpp
#include<bits/stdc++.h> 
using namespace std;
string a;
int t;
int main(){
	cin>>t>>a;//输入字符串的长度与字符串 
	for(int i=2;i<=t;i++){//从 2 开始枚举 
		if(t%i==0)reverse(a.begin(),a.begin()+i);//t 是 i 的倍数，则翻转从 1 到 i 的字符串 
	}
	cout<<a<<endl;//输出字符串 
	return 0;//结束程序 
}
```


---

## 作者：Eason_AC (赞：0)

## Content
给一个长度为 $n$ 的字符串 $s$，执行以下操作：

- 降序遍历 $n$ 的所有因子（从 $n$ 到 $1$）。
- 对于每一个因子 $i$ 翻转字符串 $s_{[1,i]}$。

现在给出操作后的字符串，求原字符串。

**数据范围：$1\leqslant n\leqslant 100$。**
## Solution
既然原来的操作是降序遍历因子，那么还原的时候不正是升序遍历因子吗？所以，按照逆推的思想，我们可以按照下面的操作模拟：

- 升序遍历 $n$ 的所有因子（从 $1$ 到 $n$）。
- 对于每一个因子 $i$ 翻转字符串 $s_{[1,i]}$。

操作完以后的字符串就是我们想要的原字符串了。
## Code
```cpp
int n;
string s;

int main() {
	getint(n); cin >> s;
	_for(i, 2, n) {
		if(!(n % i))
			for(int l = 0, r = i - 1; l <= r; ++l, --r)
				swap(s[l], s[r]);
	}
	cout << s;
	return 0;
}
```

---

## 作者：happybob (赞：0)

代码很简单，逆推其实也很简单，和加密方法一样，其实也是一样的，速度还是挺快的，不知怎么回事cin240ms排第三，快读竟然变成272ms……：

快读代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

inline int read()
{
    int x = 0;
    char ch = getchar();
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}

string s;

int main()
{
    int n;
    n = read();
    cin >> s;
    for(int i = 2; i <= n; i++)
    {
        if(n % i == 0)
        {
            reverse(s.begin(), s.begin() + i);
        }
    }
    cout << s << endl;
    return 0;
}
```

cin代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

bool yinshu(int x, int n)
{
    return n % x == 0;
}

string s;

int main()
{
    int n;
    cin >> n >> s;
    for(int i = 2; i <= n; i++)
    {
        if(yinshu(i, n))
        {
            reverse(s.begin(), s.begin() + i);
        }
    }
    cout << s << endl;
    return 0;
}
```

还有cin不用函数的，242ms：
```
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

bool yinshu(int x, int n)
{
    return n % x == 0;
}

string s;

int main()
{
    int n;
    cin >> n >> s;
    for(int i = 2; i <= n; i++)
    {
        if(n % i == 0)
        {
            reverse(s.begin(), s.begin() + i);
        }
    }
    cout << s << endl;
    return 0;
}
```

reverse针对数组和STL容器，两个值均为迭代器，而STL中可以迭代器 + int类型的数据只有vector，string。

注意，迭代器名++不要写成 迭代器名 = 迭代器名 + 1，迭代器的++，--，!=这些都是系统重载过的，和普通理解的不一样

注意循环从2开始就好了，为什么题目也说了

---

## 作者：Times_New_man (赞：0)

# 题解CF999B Reversing Encryption
其实这题,我们只需要暴力枚举就行了,因为$n$并不是非常大。

下面我们介绍一下reverse()函数。  
它传入两个参数,一个是开头,一个是结尾。  
它的作用是可以把字符串从开头到结尾进行大翻身(倒过来)  
比如让$s$翻转从$1$到$i$就是reverse(s.begin(),s.begin()+i);

是不是很简单?下面我们来看看本题的代码吧!
```cpp
#include<iostream>
#include<algorithm>		//包含reverse()函数
using namespace std;

long long n;		//字符串长度
string s;			//这个字符串

int main()
{
    cin>>n>>s;		//输入长度和这个字符串
    for(int i=1;i<=n;i++)		//从1枚举到n
        if(n%i==0)			//如果i能被n整除
        	reverse(s.begin(),s.begin()+i);		//**重点**使用reverse大翻身
    cout<<s;		//输出处理好的字符串
    return 0;		//一定不要忘了return 0,否则有几率RE
}
```

---

