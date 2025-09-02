# [PA 2022] Liczenie punktów

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 1 [Liczenie punktów](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/pun/)**

PA 的裁判们已经厌倦了不断计算所有提交代码的得分。请帮助他们实现这一过程的自动化。

对于每道题，一次提交可以得 $0$ 到 $10$ 分。一道题中有 $n$ 组测试数据，其中 $n$ 可以被 $10$ 整除。如果这个代码可以通过前 $\frac{n}{10}$ 组数据，那么会得一分，如果代码可以通过接下来的 $\frac{n}{10}$ 组数据，就会再得一分。一次提交可以因为全部通过了一个测试点内所有 $\frac{n}{10}$ 组数据而独立地获得一分。如果在一个测试点内的某组数据出现错误，那么这次提交就拿不到这个测试点的分数。

注意：

1. 为了简单，我们假设每个测试点中都有相同组的测试数据，但是实际的算法竞赛中并不是这样。
2. 任何你写过的代码都可能拿来妨碍你（宇航员笑话）。

## 说明/提示

对于 $100\%$ 的数据，满足：

$10\le n\le 100$。

## 样例 #1

### 输入

```
20
TTNNTTNTNTNNNNNNNNTT
```

### 输出

```
3
```

# 题解

## 作者：liruixiong0101 (赞：5)

## P0 前置知识：
模拟，字符串。

## P1 题意：
给你一个由 `T` 和 `N` 的长度为 $n$ 的字符串，请问把他从左往右平均分成 $10$ 个长度为 $\frac{n}{10}$ 的字串为新字符串，请问有多少个新字符串全是由 `T` 组成的。

## P2 思路：
按照题意模拟，先把字符串平均分成 $10$ 份，然后依次枚举每一个新字符串的每一个字符，若全是 `T` 计数器加一，否则计数器不变。

---

其实并不需要把每一个新字符串存在数组里，临时求就可以了。  
这里引出一个函数 `substr`，简单来说就是给你两个参数一个是起始位置，第二个是长度，可以帮你算出来从起始位置开始长度为第二个参数的字符串的子串（[`substr` 还不会的戳这里](https://oi-wiki.org/lang/csl/string/#%E6%88%AA%E5%8F%96%E5%AD%90%E4%B8%B2)）。  
所以就可以用 `substr` 来提取字串，方便又快捷。

---

但是若一个一个枚举新字符串的每一个字符太麻烦了时间复杂度也很高。我们需要发现一点这些新字符串的长度都是相同的所以合法的字符串一定是全由 `T` 组成的长度为 $\frac{n}{10}$ 的字符串，判断一下他们是否相同即可。

## P3 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , l , ans;//l为长度，ans为答案
string s , p;//p为全部由T组成的字符串
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	cin >> n >> s;
	s = " " + s;
	l = n / 10;
	for(int i = 1; i <= l; i++) p += "T";
	//算出p
	for(int i = 1; i <= n; i += l){
		if(s.substr(i , l) == p) ans++;
		//判断是否相同
	}
	cout << ans;
	return 0;
}
```

---

## 作者：lichenzhen (赞：4)

## 题目大意
输入 $n$ 和一个长度为 $n$ 的仅包含 `T` 和 `N` 的字符串。求其中有几个长度为 $\frac{n}{10}$ 仅包含 `T` 的子字符串。

## 题目解法
很简单的一道题目，$n$ 的范围很小，直接用暴力即可。

写一个二重循环，第一层循环从 $0$ 到 $n-1$，循环变量为 $i$，第二层循环从 $i$ 往后找 $\frac{n}{10}$。

具体实现可看代码。

### 参考代码
```cpp
#include<iostream>
using namespace std;
int ans,n,t;
string s;
bool f;
int main()
{
    cin>>n>>s;
    t=n/10; 
    for(int i=0;i<n;i+=t)
    {
    	f=true;//记录是否出现了N 
    	for(int j=i;j<i+t;j++)
            if(s[j]=='N'){
                f=false;//如果出现了N就标记一下并跳出第二层循环（没有必要继续扫了） 
                break;
            }
        if(f) ans++;//如果没出现过N就将计数器加一 
	}
    cout<<ans; 
    return 0;
}
```

**说句闲话：我是目前是最优解，祝你们成功（滑稽。**

---

## 作者：Peck (赞：3)

## 题意

把一个数列划分为 $10$ 段，每段长 $\frac{n}{10}$ ，求有多少段字符串全部由 $T$ 组成？

## 分析

在题意上会有很多人形成误解：接下来的 $\frac{n}{10}$ 组数据是什么意思？实际上，它是指紧接着前面的 $\frac{n}{10}$ 组数据，后面的数据，并不包含前面的数据。

那么这道题就是一个模拟，枚举有多少个长为 $\frac{n}{10}$ 的数据全部由 $T$ 组成，累加答案即可。

## 代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int n, ans = 0;
string a;

bool allT(string a) {//判断是否全部由 t 构成 
	for (int i = 0; i < a.length(); i++)
		if (a[i] == 'N')//只要有一个是 N 就不行 
			return false;
	return true;
}

int main() {
	cin >> n >> a;
	int l = n / 10;
	for (int i = l; i <= a.length(); i += l)//每次前进 l 步 
		if (allT(a.substr(i - l, l)))//注意这里是取长度为 l 的字符型 
			ans++; 
	cout << ans << endl;
	return 0;
} 
```


---

## 作者：PineappleSummer (赞：1)

[$\color{orangered}\text{题目传送门}$](https://www.luogu.com.cn/problem/P9254)
## Problem
给你一个由 `T` 和 `N` 的长度为 $n$ 的字符串，请问把他从左往右平均分成 $10$ 个长度为 $\dfrac{n}{10}$ 的子串为新字符串，请问有多少个新字符串全是由 `T` 组成的。
## Solution
思路很清晰，双重循环枚举每个子串，判断每个子串是否只由 `T` 构成。外循环枚举子串的左端点，内循环枚举当前子串的长度。

这里有一个坑点：外循环不能写成
```cpp
for(int i=0;i<s.size();i++)
```

这是因为子串要每 $\dfrac{n}{10}$ 个枚举，每两个子串都没有重合部分，
应改为：
```cpp
for(int i=0;i<s.size();i+=n/10)
```
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
string s;
int main()
{
	cin>>n>>s;//输入
	for(int i=0;i<s.size();i+=n/10)
	{
		bool flag=0;//用于标记的变量初始值为0
		for(int j=0;j<n/10;j++)
		{
			if(s[i+j]!='T')
			{
				flag=1;//flag标记为1
				break;
			}
		}
		if(!flag) ans++;//整个子串全由T构成，答案加1
	}
	cout<<ans;//输出答案
    return 0;
}
```

---

## 作者：hycqwq (赞：1)

## Problem

给出一个字符串，把它平均分成 $10$ 个部分，问有几个部分全部都是 `T`。

## Solution

模拟有什么好说的。

枚举每个部分，看看是否都是 `T` 即可。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
#define elif else if
#define il inline

bool chk(string s)
{
    for (char i : s)
        if (i != 'T')
            return false;
    return true;
}

int n, c = 0;
string s;

int main()
{
    cin >> n >> s;
    n /= 10;
    for (int i = 0; i <= s.size() - n; i += n)
        if (chk(s.substr(i, n)))
            c++;
    cout << c << endl;
    return 0;
}
```

---

## 作者：SunnyLi (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9254)

## 思路

盲猜题目暴力不会超时，结果还真就是……

我们可以先算出它的周期 $\frac{10}{n}$，然后每次取出每个长度为一个周期的子字符串，再在这个长度为一个周期的字符串判断是否出现了 `N`。我们可以设置一个标记 `flag`，将其初始设置为 `true`。如果有 `N` 则把标记设置为 `false`，这时总数就不需要加 $1$。反之，如果这个子串中的所有字符都为 `T`，则 `sum++`。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

bool pd(string x){
    if(x=="N")	return 0;
    else	return 1;
}

int main(){
    int n,sum=0,t;
    string s,a;
    cin >> n >> s;
    t = n/10;
    for(int i=0;i<=n/t-1;i++){
    	bool flag=true;
    	a = s.substr(i*t,t);
    	for(int j=0;j<=t-1;j++)	if(pd(a.substr(j,1))==false)	flag=false;
		if(flag)	sum++;
	}
    cout << sum;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/109037474)

---

## 作者：Red0rangE (赞：0)

## 题意理解

给出一个正整数 $n$ 和一个长度为 $n$ 的字符串 $s$，只由 ```T``` 和 ```F``` 两种字符组成，分别表示通过和不通过。$n$ 保证可以被 $10$ 整除，将 $s$ 按先后顺序等分为十个部分，如果对于每一个部分如果字符都是 ```T``` 则将分数加一。求总分。

## 思路阐述

循环十次，嵌套循环比较区间内字符是否相同且为 ```T```，具体内容见代码注释。

## 代码呈现

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;//字符串
int l,k;//总长度，每个区间的长度
int ans;//答案
bool f;//标记每个区间的字符是否相同
int pos;//位置

signed main(){
    
    cin>>l>>s;//输入
    k=l/10;//求出区间长度
    for (int i=1;i<=10;i++){//循环十次
        f=1;//初始标记字符都相同
        for (int j=1;j<k;j++){//循环比较字符是否相同
            if (s[pos]!=s[pos+1]) f=0;//字符不同，更改标记
            pos++;//更新位置
        }
        if (f && s[pos]=='T') ans++;//字符相同且都是T，得分加一
        pos++;
    }
    printf("%d",ans);//输出
    return 0;
    
}

```

希望可以帮到各位大佬。

---

