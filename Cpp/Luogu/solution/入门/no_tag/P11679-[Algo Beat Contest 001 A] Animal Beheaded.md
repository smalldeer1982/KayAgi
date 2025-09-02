# [Algo Beat Contest 001 A] Animal Beheaded

## 题目背景

|               Problem               | Score |                         Idea                          |                             Std                              |                      Data                       |                            Check                             |                           Solution                           |
| :---------------------------------: | :---: | :---------------------------------------------------: | :----------------------------------------------------------: | :---------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|    $\text{A - Animal Beheaded}$     | $100$ | [remmymilkyway](https://www.luogu.com.cn/user/551981) |    [remmymilkyway](https://www.luogu.com.cn/user/551981)     | [joe_zxq](https://www.luogu.com.cn/user/623577) |     [fcy20180201](https://www.luogu.com.cn/user/866154)      | [Link](https://www.luogu.com.cn/article/zptsxa3j) by [joe_zxq](https://www.luogu.com.cn/user/623577) |

有些容易死的坏人要向原始人民共和王国的国王行断头礼了。

![](https://pic.imgdb.cn/item/674eed94d0e0a243d4dcd33a.png)

![](https://pic.imgdb.cn/item/674eed94d0e0a243d4dcd33b.png)

## 题目描述

在 Z 星球上，每一个碳基生物都是一个字符串。每个人的身高（也就是该碳基生物字符串的长度）都是 $3$ 的倍数。把这个字符串三等分，第一段是身体，第二段是头，第三段是眼睛。

现在一个碳基生物被国王砍头了！它的头落到了地上！此时这个碳基生物的第二段就掉到了第一段前，第三段掉到第二段后。也就是说碳基生物成为了头、身体、眼睛的顺序。

给定这个碳基生物被砍头前的字符串，求出这个碳基生物被砍头后的字符串。


> 形式化题面：给定一个长度为 $3$ 的倍数的字符串 $S$，令 $N$ 为 $S$ 的长度，请输出 $S_{\frac{N}{3} +1}S_{\frac{N}{3}+2} \dots S_{\frac{2N}{3} } S_1 S_2 \dots S_{\frac{N}{3}} S_{\frac{2N}{3} +1} S_{ \frac{2N}{3} +2} \dots  S_N$。

## 说明/提示

#### 样例解释 #1

碳基生物的身体为 `11`，头为 `45`，眼睛为 `14`，则按照题目描述的顺序摆放应为 `451114`。

#### 数据范围

- $1 \le N \le 10^5$ 且 $N$ 是 $3$ 的倍数。
- $S$ 只包含小写字母或数位。

## 样例 #1

### 输入

```
6
114514```

### 输出

```
451114```

## 样例 #2

### 输入

```
12
iaminmygrave```

### 输出

```
nmygiamirave```

## 样例 #3

### 输入

```
9
uctrelant```

### 输出

```
reluctant```

# 题解

## 作者：封禁用户 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P11679)

简单题，按题意模拟下标的变化，一一输出即可。记得把字符串的下标改成从 $1$ 开始。

核心代码：

```cpp
int n;
string s;
cin >> n >> s; s = ' ' + s;
FOR(i, n / 3 + 1, 2 * n / 3) cout << s[i]; // 从 n/3+1 到 2n/3
FOR(i, 1, n / 3) cout << s[i]; // 从 1 到 n/3
FOR(i, 2 * n / 3 + 1, n) cout << s[i]; // 从 2n/3 到 n
```

---

## 作者：M1__ (赞：2)

# 题解：P11679 [Algo Beat Contest 001 A] Animal Beheaded
[题目传送门](https://www.luogu.com.cn/problem/P11679)
## 题目思路
- 按题意模拟即可。
- 注意字符串的首项下标为 $0$。
- 定义三个字符串 $S_1$，$S_2$，$S_3$，将字符串 $S$ 分成下标为 $\left[ 0,\frac{n}{3}-1\right]$，$\left[ \frac{n}{3}, \frac{2n}{3}-1\right]$，$\left[\frac{2n}{3} ,n-1 \right]$ 的三个区间的子串，令 $S_1$，$S_2$，$S_3$ 分别等于这三个子串。然后将 $S_1$ 和 $S_2$ 位置调换即可。
## 代码实现
### 模拟
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	int n;
	string s,s1="",s2="",s3="";
	cin>>n;
	cin>>s;
	for(int i=0;i<n/3;i++){
		s1+=s[i];
	}
	for(int i=n/3;i<(n/3)*2;i++){
		s2+=s[i];
	}
	for(int i=(n/3)*2;i<n;i++){
		s3+=s[i];
	}
	cout<<s2<<s1<<s3;
}
```
- 对于直接模拟，为了防止字符串越界，要将 $S_1$，$S_2$，$S_3$ 设置为空，并用 ```+=``` 来进行操作。
### 用函数来实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	string s,s1="",s2="",s3="";
	cin>>n>>s;
	s1=s.substr(0,n/3);
	s2=s.substr(n/3,n/3);
	s3=s.substr((n/3)*2,n/3);
	cout<<s2<<s1<<s3;
}
```

---

## 作者：jiqihang (赞：2)

### 题目链接
[P11679 [Algo Beat Contest 001 A] Animal Beheaded](https://www.luogu.com.cn/problem/P11679)
### 分析
自认为简易化题意复杂了。

观察样例或看题目描述不难发现就是将字符串每 $N \div 3$ 位一段，分成三段，再组合。

实现方法：
1. 首先读取长度 $N$ 和字符串 $S$。
2. 求出每段的长度。
3. 将字符串按第二步求出的每段的长度三等分，依次代表身体、头和眼睛部分。
4. 按照头、身体、眼睛的顺序重新组合字符串。
5. 输出重新组合后的字符串。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() 
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    int cd=n/3;//每段长度
    string a=s.substr(0,cd);
    string b=s.substr(cd,cd);
    string c=s.substr(2*cd);
    //substr截取
    cout<<b+a+c<<endl;
    return 0;
}
```

---

## 作者：getchar_unlocked (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11679)

### 思路

**模拟**题。题干中明确了 $3$ 段字符串的起点和终点。用变量 $i$ 做 $3$ 次 for 循环遍历 $3$ 段字符串，每次输出 $S_i$ 即可。

**注意事项**

- 字符串下标从 $1$ 开始。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e5+10;
char s[N];
int main(){
	int n=read();
	scanf("%s",s+1);
	for(int i=n/3+1;i<=n*2/3;++i)
		printf("%c",s[i]);
	for(int i=1;i<=n/3;++i)
		printf("%c",s[i]);
	for(int i=n*2/3+1;i<=n;++i)
		printf("%c",s[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：Pufflet233 (赞：1)

### 题目描述
有一个长度为 $N$ 的字符串被切成了 3 段，当中 $N$ 一定为3的倍数，每段长度为 $\frac{N}{3}$ ，现在第 1 段和第 2 段交换位置，变成了字符串 $S$ ，要找原始没被输出的字符串。
### 解题思路
把字符串 $S$ 切割成 3 段，先输出字符串 $S$ 的第二段，然后输出第 1 段，最后输出第 2 段即可。

例如字符串 $S$ 为 ```abcdef``` ，首先我们需要把字符串切成 3 段，分别为 ```ab``` 、```cd``` 和 ```ef``` ，然后先输出第二段 ```cd``` ，接着输出第一段 ```ab``` ，最后输出第三段 ```ef``` 。

我们在 C++ 语言中可以利用 ```substr()``` 函数获取子字符串，用法为 ```str.substr(a, b)``` ，当中 ```str``` 为字符串的名字， ```a``` 为起始位置，```b``` 为获取的子字符串长度。

切割后三段字符串的长度都为 $\frac{N}{3}$ ，起始位置分别为 $0$ ，$\frac{N}{3}$ 和 $\frac{2N}{3}$ 。我们可以用 ```S.substr(0, N/3)``` 、 ```S.substr(N/3, N/3)``` 和 ```S.substr(2*N/3, N/3)``` 获取三段字符串。交换第 1 段和第 2 段字符串并输出即可通过本题。

以下是 C++ 语言的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int N;
    string S;
    cin >> N >> S;//输入N和S
    cout << S.substr(N/3, N/3) << S.substr(0, N/3) << S.substr(2*N/3, N/3);//把字符串S切割成3段并且输出
    return 0;
}
```

---

## 作者：Sun_pirf (赞：1)

# 思路

按题意模拟即可。

简单思考可知，三小段长度为 $\frac{n}{3}$，新的三段开头分别为：$\frac{n}{3}$，$1$，$\frac{2 \times n}{3}$，最后按顺序输出即可。

代码容易实现。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char c[100005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	for(int i=1;i<=n/3;i++){
		cout<<c[n/3+i];
	}
	for(int i=1;i<=n/3;i++){
		cout<<c[i];
	}
	for(int i=1;i<=n/3;i++){
		cout<<c[2*n/3+i];
	}
	return 0;
}
```

---

## 作者：yedalong (赞：1)

## 简化题意

给定一个字符串 $S$，且 $S$ 的长度为 $N$，输出 $S_{\frac{N}{3}+1}S_{\frac{N}{3}+2}…S_{\frac{2N}{3}}S_1S_2…S_{\frac{N}{3}}S_{\frac{2N}{3}+1}S_{\frac{2N}{3}+2}…S_N$。

## 思路

输入后分为三段输出，第一段从 $S_{\frac{N}{3}+1}$ 到 $S_{\frac{2N}{3}}$，第二段从 $S_1$ 到 $S_{\frac{N}{3}}$，第三段从 $S_{\frac{2N}{3}+1}$ 到 $S_N$。

## AC code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s,ans;
int main(){
    cin>>n>>s;
    s=' '+s;
    for(int i = n/3+1;i<=n/3*2;i++) ans+=s[i];
    for(int i = 1;i<=n/3;i++) ans+=s[i];
    for(int i = n/3*2+1;i<=n;i++) ans+=s[i];
    cout<<ans;
    return 0;
}
```

---

## 作者：__CJY__ (赞：1)

~这不是截肢吗，太恐怖了！出题人脑洞有点大呀……~
## 思路
使用 `substr` 函数把字符串分成 $3$ 个部分，然后再按照题目要求的顺序输出即可。

三个部分的**起始下标**分别为：$0$、$n\div3$、$2 \times (n\div3)$，每个部分的字符个数都为 $n\div3$。

不用考虑要不要判断 $n$ 是否为 $3$ 的倍数，题目中已经保证：
>$1 \le N \le 10^5$ 且 $N$ 是 $3$ 的倍数。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;cin>>n;
	string s;cin>>s;
	string s1=s.substr(0,n/3),s2=s.substr(n/3,n/3),s3=s.substr(2*(n/3),n/3);
	cout<<s2<<s1<<s3;
}
```

---

## 作者：banglee (赞：1)

### P11679 [Algo Beat Contest 001 A] Animal Beheaded 题解
[题目传送门](https://www.luogu.com.cn/problem/P11679)

## 前置知识
`substr()` 是用于字符串处理的预定义函数。`string.h` 是字符串函数所需的头文件。

此函数将两个值 $pos$ 和 $len$ 作为参数，并返回一个新构造的字符串对象，其值初始化为该对象的子字符串的副本。从 $pos$ 开始复制字符串，直到 $pos+len$。表示为 $[pos,pos+len)$。

此外，`substr()` 还有很多用法，大家可以去多寻找一下。

ps：摘选自 [csdn](https://blog.csdn.net/weixin_42745979/article/details/132309594)。
## 思路
将字符串 $S$ 分割为身体、头和眼睛三部分，利用 `substr()` 按照头、身体、眼睛的顺序将三部分重新组合成新的字符串。

因为要将 $S$ 分成 $3$ 部分，所以令 $k=N \div 3$。

看题，不难发现头的部分是 `s.substr(k,k)`，身体的部分是 `s.substr(0,k)`，眼睛的部分是 `s.substr(2*k)`。

最后输出即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
string s;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>s;
	int k=n/3;
	cout<<s.substr(k,k)<<s.substr(0,k)<<s.substr(2*k);
	return 0;
}
```

---

## 作者：Camellia_Spoil (赞：1)

# 思路
简单的模拟题。只需要依次枚举整个字符串被分成三等分后的中间，开头，结尾，然后输出即可。

# AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline long long read()
{
	long  long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main(){
	string s;
	int n;
	cin>>n>>s;
	int k=n/3;
	for(int i=k;i<k+k;i++) cout<<s[i];
	for(int i=0;i<k;i++) cout<<s[i];
	for(int i=k+k;i<n;i++) cout<<s[i];
	return 0;
}
```

---

## 作者：e_zhe (赞：1)

### 分析

固然可以直接计算下标再用 `for` 输出，但 `string` 类型为我们提供了更为简便的 `substr` 函数。

```cpp
string s="abcde";
//格式：s.substr(起始位置，截取长度)
cout<<s.substr(1,3);
//输出：bcd，注意下标是从0开始的 
```

细节内容见代码注释。

### Code

```cpp
#include<bits/stdc++.h>
#define i64 long long

using namespace std;

int main(){
	ios::sync_with_stdio(false),
	cin.tie(nullptr),cout.tie(nullptr);
	
	int n;cin>>n;
	string s;cin>>s;
	//n 和 s 如题目 
	
	cout<<s.substr(n/3,n/3)<<s.substr(0,n/3)<<s.substr(n/3*2,n/3);
	//三段，每段的长度都是 n/3 
	return 0;
}
```

---

## 作者：joe_zxq (赞：1)

出题人的脑洞真大。

---

简单的模拟题。

显然是可以直接处理出三个字符串然后按要求顺序输出的，但是使用 `substr()` 截取显然更加方便，注意截取子串的开头位置和长度。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, ans;
string s;

int main() {

	cin >> n >> s;
	cout << s.substr(n / 3, n / 3) + s.substr(0, n / 3) + s.substr(n / 3 * 2);

	return 0;
}
```

---

## 作者：违规用户名^3Zj=Oha (赞：1)

## 一、思路分析
不做过多处理，直接算出每段长度用三个循环输出即可。

## 二、代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
string s;
signed main(){
	cin>>n>>s;
	for(int i=n/3;i<n/3*2;i++) cout<<s[i];
	for(int i=0;i<n/3;i++) cout<<s[i];
	for(int i=n/3*2;i<n;i++) cout<<s[i];
	return 0;
}
```

---

## 作者：InfiniteRobin (赞：1)

## 分析

简单题，模拟即可。

以下下标从 $0$ 开始。

首先我们先输出字符串中间的部分，即 $S_{\frac{N}{3}} \dots S_{\frac{2N}{3}-1}$。

接下来，输出剩余部分即可，对于下标 $i$：

- 若 $\frac{N}{3} \le i < \frac{2N}{3}$，无需输出。
- 否则输出 $S_i$ 即可。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	string s;
	int n;
	cin>>n>>s;
	for(int i=n/3;i<=2*n/3-1;i++){
		cout<<s[i];
	}
	for(int i=0;i<n;i++){
		if(n/3<=i&&i<n*2/3) continue;
		cout<<s[i];
	}
	
	return 0;
} 
```

---

## 作者：GSQ0829 (赞：1)

### 前置知识：[substr](https://blog.csdn.net/zq9955/article/details/121643591)
---
### 思路：
这题很简单，就是将字符串平均分为三段，保证是三的倍数，最后按照 ```2,1,3```的顺序，来输出字符串。

本题我将提供两种思路，一种是用循环的方式来截取三段字符，并且输出。另一种是直接调用库函数来输出。

---
### code：
方法一：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

int main() {
	cin >> n >> s;
// 用for循环的方式来截取三段字符
	for (int i = n / 3; i < n / 3 * 2; i++) cout << s[i];
	for (int i = 0; i < n / 3; i++) cout << s[i];
	for (int i = n / 3 * 2; i < n; i++) cout << s[i];
	return 0;
}
```
方法二：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, ans;
string s;

int main() {
	cin >> n >> s;
// 直接调用stl解决
	cout << s.substr(n / 3, n / 3) + s.substr(0, n / 3) + s.substr(n / 3 * 2);
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### Analysis
输出 $S_{\frac{N}{3} + 1} S_{\frac{N}{3} + 2} \dots S_{\frac{2N}{3}} S_1 S_2 \dots S_{\frac{N}{3}} S_{\frac{2N}{3} + 1} S_{\frac{2N}{3} + 2} \dots S_N$ 即可。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

#define P(i, a, b) for(int i = a; i <= b; i++)
#define Q(i, a, b) for(int i = a; i >= b; i--)
const int maxn = 100005;
const int inf = 0x3f3f3f3f;

mt19937 rnd(chrono::duration_cast<chrono::nanoseconds>
           (chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

signed main(){

    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    string s; cin >> s;
    cout << s.substr(n / 3, n / 3) + s.substr(0, n / 3) + s.substr(n / 3 * 2) << endl;

}
```

---

## 作者：Your_Name (赞：0)

## 题解
注意到 $N$ 是三的倍数，所以直接按题目输出即可。

## AC_Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> s;
    s = ' ' + s;
    for(int i = n / 3 + 1; i <= n / 3 * 2; i ++){
        cout << s[i];
    }
    for(int i = 1; i <= n / 3; i ++){
        cout << s[i];
    }
    for(int i = n / 3 * 2 + 1; i <= n; i ++){
        cout << s[i];
    }
    return 0;
}
```
 _完结撒花。_

---

## 作者：CCY20130127 (赞：0)

## 题目大意：
[题目传送门](https://www.luogu.com.cn/problem/P11679)

## 题目思路：
没什么好说的，用三个字符串将原字符串切割出来，再输出就行了。

## 正解：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
string s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>s;
	ll l=n/3;
	string s1=s.substr(0,l);
	string s2=s.substr(l,l);
	string s3=s.substr(2*l,l);
	cout<<s2<<s1<<s3;
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

既然要输出头、身体、眼睛的顺序，那么调换一下输出顺序即可。

在这里令 $x$ 为 $\frac{n}{3}$ 的结果（字符串下标从 $1$ 开始）。也就是首先输出 $x + 1$ 至 $x \times 2$ 的这一部分，再输出 $1$ 至 $x$ 的这一部分，最后输出 $x \times 2 + 1$ 至 $n$ 的这一部分。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int n, x;
char a[MAXN];
int main () {
    cin >> n >> (a + 1);
    x = n / 3;
    for (int i = x + 1; i <= x * 2; i ++) cout << a[i];
    for (int i = 1; i <= x; i ++) cout << a[i];
    for (int i = x * 2 + 1; i <= n; i ++) cout << a[i];
    return 0;
}
```

---

## 作者：Vct14 (赞：0)

题目即把字符串三等分，中间一部分取出来放到最前面。我们的思路是循环三次，第一次输出原字符串中间的部分，第二次输出原字符串前面的部分，第三次输出原字符串后面的部分。

```cpp
#include<bits/stdc++.h>
using namespace std;

char ch[100002];

int main(){
	int n;cin>>n;
	for(int i=1; i<=n; i++) cin>>ch[i];
	for(int i=n/3+1; i<=n/3*2; i++) cout<<ch[i];
	for(int i=1; i<=n/3; i++) cout<<ch[i];
	for(int i=n/3*2+1; i<=n; i++) cout<<ch[i];
	return 0;
}

```

其实就是按照形式化题意模拟输出。

---

## 作者：easy42 (赞：0)

如何把字符串截成几段？

直接使用内置的 `substr` 函数，可以截成几段，只要提供字符串的开始截取位置和截取长度就好了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
string s;
signed main(){
	cin>>n;
	cin>>s;
	string a=s.substr(0,s.size()/3);
	string b=s.substr(s.size()/3,s.size()/3);
	string c=s.substr(2*s.size()/3,s.size()/3);
	cout<<b<<a<<c;
	return 0;
}
```

---

## 作者：yu1128_AKIOI (赞：0)

## 思路

按题意模拟即可。注意题中的下标均是从一开始。故需要将其下标减一后输出。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	string s;
	cin>>n>>s;
	for(int i=n/3;i<2*n/3;i++) cout<<s[i];
	for(int i=0;i<n/3;i++) cout<<s[i];
	for(int i=n/3*2;i<n;i++) cout<<s[i];
}
```

---

