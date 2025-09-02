# Exponential notation

## 题目描述

You are given a positive decimal number $ x $ .

Your task is to convert it to the "simple exponential notation".

Let $ x=a·10^{b} $ , where $ 1<=a&lt;10 $ , then in general case the "simple exponential notation" looks like "aEb". If $ b $ equals to zero, the part "Eb" should be skipped. If $ a $ is an integer, it should be written without decimal point. Also there should not be extra zeroes in $ a $ and $ b $ .

## 样例 #1

### 输入

```
16
```

### 输出

```
1.6E1
```

## 样例 #2

### 输入

```
01.23400
```

### 输出

```
1.234
```

## 样例 #3

### 输入

```
.100
```

### 输出

```
1E-1
```

## 样例 #4

### 输入

```
100.
```

### 输出

```
1E2
```

# 题解

## 作者：2023gdgz01 (赞：5)

## 题意

给出一个数 $s$，求 $s=a\times 10^b$。

## 解题步骤

模拟题，所以恕没有分析过程。

设要转换的数为 $s$，存储为字符串形式。

接下来分四步：

1. 找 $s$ 的整数部分最左边的非零数码，设其下标为 $l$；

2. 找 $s$ 的最右边的非零数码，设其下标为 $r$；

3. 找 $s$ 的小数点，设其下标为 $x$；

4. 输出：

- 若 $l=-1$，则结果一定为 $0$，并跳过接下来的操作。

- 否则先输出 $a_l$：

- 若 $l\ne r$，则 $s$ 一定为小数，输出小数点，随后输出 $a_{l+1}$ 至 $a_r$。

- 若 $l+1\ne x$，则 $s$ 的整数部分一定不为一位数，先输出字符 `E`，随后输出 `x - l - (l < x)`。

## 代码

```cpp
#include <iostream>
#include <string>

using namespace std;

int l, r, x, n;
string s;

int main() {
	cin >> s;
	n = s.size();
	l = -1;
	for (register int i = 0; i < n; ++i) {
		if (s[i] != '0' && s[i] != '.') {
			l = i;
			break;
		}
	}
	for (register int i = n - 1; i >= 0; --i) {
		if (s[i] != '0' && s[i] != '.') {
			r = i;
			break;
		}
	}
	x = s.find('.');
	if (x == -1) x = n; //防止 s 为整数。
   	if (l == -1) cout << "0";
	else {
		cout << s[l];
		if (l != r) {
			cout << ".";
			for (register int i = l + 1; i <= r; ++i)
				if (s[i] != '.') //防止重复输出小数点。
					cout << s[i];
		}
		if (l + 1 != x)
			cout << "E" << x - l - (l < x);
	}
	cout << "\n";
	return 0;
}
```

[AC 链接](https://www.luogu.com.cn/record/134795549)

---

## 作者：Juanzhang (赞：4)

[CF691C](https://www.luogu.org/problemnew/show/CF691C)

**思路：**

 **模拟**

1 . 对原$string$进行处理
 - 处理前缀0
 - 处理小数点后缀0
 - 处理无用小数点

```cpp
	// str为输入的string
	// l, r为当前要处理的string范围
    // l, r初始化:l = 1, r = strlen(str) - 1
	gets(str + 1); // 从1起读
	r = strlen(str + 1);
	int point = find('.');
    // 自定义函数find(find(char ch)):找到str[l..r]中第一个ch出现的位置，未出现则为EOF
	for (; str[l] == 48; l++); // 处理前缀0
	for (; (~point) && str[r] == 48; r--); // 处理小数点后缀0
	if (str[r] == '.') {
		r--;
	} // 处理无用小数点
```

2 . 处理形式为 $a\cdot{10^{-x}}$ ( $1≤|a|<10$ & $x ∈ N*$ ) 的数
 
```cpp
	// str 为处理后的string
	int e = -1, pos = l + 1; // 设原数为a*10^e;pos为当前处理到的string
	for (; str[pos] == '0'; pos ++, e--); // 处理位数
	putchar(str[pos]);
	if (pos != r) {
		putchar('.');
		for (int i = pos + 1; i <= r; i++)
			putchar(str[i]);
	}
	printf("E%d", e); // 输出指数
	return 0;
```

3 . 处理形式为 $a\cdot 10^x$ ( $1≤|a|<10$ & $x ∈ Z$ & $x ≥ 0$ ) 的数

```cpp
	// point 同上
	int e = ((~point) ? point - 1 : r) - l;
	int _ = r; // [l,_] 为需要输出的部分
	for (; _ > l && str[_] == 48; _--); // 不输出后缀0
	putchar(str[l]);
	if (e && _ > l) {
		putchar('.');
	} // 是否输出小数点
	for (int i = l + 1; i <= _; i++) {
		if (str[i] != '.' || !e) {
			putchar(str[i]);
		} // 处理小数点
	} // 输出
	if (e) {
		printf("E%d", e);
	} // 输出指数
```

注意**str要开1e6**

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int l = 1, r;
char str[maxn];

int find(char ch) {
	for (int i = l; i <= r; i++) {
		if (str[i] == ch) {
			return i;
		}
	}
	return EOF;
}

int main() {
	gets(str + 1);
	r = strlen(str + 1);
	int point = find('.');
	for (; str[l] == 48; l++);
	for (; (~point) && str[r] == 48; r--);
	if (str[r] == '.') {
		r--;
	}
	if (str[l] == '.') {
		int e = -1, pos = l + 1;
		for (; str[pos] == '0'; pos ++, e--);
		putchar(str[pos]);
		if (pos != r) {
			putchar('.');
			for (int i = pos + 1; i <= r; i++)
				putchar(str[i]);
		}
		printf("E%d", e);
		return 0;
	}
	int e = ((~point) ? point - 1 : r) - l;
	int _ = r;
	for (; _ > l && str[_] == 48; _--);
	putchar(str[l]);
	if (e && _ > l) {
		putchar('.');
	}
	for (int i = l + 1; i <= _; i++) {
		if (str[i] != '.' || !e) {
			putchar(str[i]);
		}
	}
	if (e) {
		printf("E%d", e);
	}
	return 0;
}
```

---

## 作者：__qkj__ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF691C)

## 题目意思
求科学计数法，也就是 $x \times 10^y$。

## 解题过程
1. 去前导零、后导零；
1. 找小数点，若没有，将他的位置设为最后；
1. 输出 `E` 以前的部分，也就是输出 $x$，如果有多位还要输出小数点，接着继续输出；
1. 如果 $y$ 非零，还要输出 `E` 以及 $y$。

时间复杂度为 $O(n)$。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin>>s;
	int l=0,r=s.size()-1;
	while(s[l]=='0'||s[l]=='.')l++;  //去前导零
	while(s[r]=='0'||s[r]=='.')r--;  //去后导零
	int d=s.find(".");  //找小数点
	if(d==string::npos)d=s.size();
	/*输出 E 以前的部分*/
	cout<<s[l];
	if(l!=r)cout<<'.';
	for(int i=l+1;i<=r;i++)
		if(s[i]!='.')
			cout<<s[i];
	/*输出 E 以后的部分*/
	int now=d-l;
	if(l<d)now--;
	if(now)cout<<'E'<<now;
	return 0;
}

```

---

## 作者：Peaky (赞：1)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF691C)。  
### 题意
把 $x$ 转换成[科学计数法](https://baike.baidu.com/item/%E7%A7%91%E5%AD%A6%E8%AE%B0%E6%95%B0%E6%B3%95/1612882)。
### 思路
分类讨论：  
1. 若 $x$ 是 $00.000$ 则直接输出 $0$ 即可。
2. 若 $x$ 的整数位为零，则要找到小数位的最高位，并将 E 后面的 b 改为位数，将小数点移到小数位最高位的后一位即可。
```cpp
if(tt1==hh1){
	while(que2[hh2]=='0') hh2++;
	cout<<que2[hh2++];
	int E=hh2;
	if(hh2!=tt2) cout<<".";
	while(hh2!=tt2) cout<<que2[hh2++];
	cout<<"E-"<<E;
	return 0;
}
```
3. 若整数位不为 $0$，则正常输出即可。
```cpp
int E=tt1-hh1-1;
if(tt2==hh2){
	while(que1[tt1-1]=='0') tt1--;
}
cout<<que1[hh1++];
if(tt1==hh1&&tt2==hh2){
	if(E==0) return 0;
	cout<<"E"<<E;
	return 0;
}
cout<<".";
while(tt1!=hh1) cout<<que1[hh1++];
while(hh2!=tt2) cout<<que2[hh2++];
if(E==0) return 0;
cout<<"E"<<E;
```
### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=1e6+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int z,x,dol,tt1,hh1,tt2,hh2;
char que1[N],que2[N];
int main(){
	string s;
	cin>>s;
	int n=s.size();
	for(int i=0;i<n;i++){
		if(s[i]=='.'){
			dol=i+1;
			continue;
		}
		if(!dol) que1[tt1++]=s[i];
		if(dol) que2[tt2++]=s[i];
	}
	while(que1[hh1]=='0') hh1++;
	while(que2[tt2-1]=='0') tt2--;
	if(tt1==hh1&&tt2==hh2){
		cout<<0;
		return 0;
	}
	if(tt1==hh1){
		while(que2[hh2]=='0') hh2++;
		cout<<que2[hh2++];
		int E=hh2;
		if(hh2!=tt2) cout<<".";
		while(hh2!=tt2) cout<<que2[hh2++];
		cout<<"E-"<<E;
		return 0;
	}
	int E=tt1-hh1-1;
	if(tt2==hh2){
		while(que1[tt1-1]=='0') tt1--;
	}
	cout<<que1[hh1++];
	if(tt1==hh1&&tt2==hh2){
		if(E==0) return 0;
		cout<<"E"<<E;
		return 0;
	}
	cout<<".";
	while(tt1!=hh1) cout<<que1[hh1++];
	while(hh2!=tt2) cout<<que2[hh2++];
	if(E==0) return 0;
	cout<<"E"<<E;
	return 0;
}
```

---

## 作者：Jinzixun (赞：1)

一道模拟题。

首先去掉前缀后缀 $0$，接下来输出，具体做法见代码。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int x, y;
int main(){
	cin >> s;
	y = s.size() - 1;
	while(s[x] == '0' || s[x] == '.')	x++;//去前缀0。
	while(s[y] == '0' || s[y] == '.')	y--;//去后缀0。
	int dot = s.find('.');//找到小数点的的位置。
   	if(dot == s.npos)   dot = s.size();//没有小数点默认在最后。
	printf("%c", s[x]);//输出科学记数法中的个位数。
	if(x != y)	printf(".");//如果有多个数输出小数点。
	for(int i = x + 1; i <= y; i++){
		if(s[i] != '.')	printf("%c", s[i]);//输出科学记数法中小数点后面的数。
	}
	int wei = x < dot ? dot - x - 1 : dot - x;//找到E后面的数。
	if(wei)	printf("E%d", wei);//输出E后面的数，为0不用输出。
	return 0;
}
```

---

## 作者：TemplateClass (赞：0)

一个比较简单的字符串模拟。

由于开始给出的字符串就有前导零和后置零，而改写成科学计数法的时候又会挪动小数点导致前导零和后置零。为了方便，我们可以先写一个函数，方便调用。

```cpp
inline std::string clear0(const std::string& s, bool cleandot, bool adddot) {
	bool isfloat = (s.find(".", 0) != std::string::npos);
	
	int begin = 0, end = s.size() - 1;
	while(s[begin] == '0') ++begin;
	while(isfloat && s[end] == '0') --end;
	
	if(cleandot && s[end] == '.') --end;
	return s.substr(begin, end - begin + 1) + (adddot && !isfloat ? "." : "");
}
```

解释一下参数 `cleandot` 和 `adddot`：

为了方便进行改写，接下来的代码中会经常地寻找 `.` 的位置，如果它输入的时候就是一个整数，那么在寻找 `.` 的时候就需要特殊的判断，不够方便，所以如果参数 `adddot` 为 `true`，函数就会自动地在末尾添加上 `.`。

当然不能这样输出多余的一个 `.`，所以 `cleandot` 为 `true` 时，就会删除多余的 `.`。

由于题目要求当指数为 $0$ 的时候，不输出指数部分。实际上就是如果小数点前只有一位（非零的）数字位时直接输出。否则，我们就统计第一个非零的数字，将小数点挪到这个数字后面，然后计算出指数，输出即可。

记得输出时也要调用 `clear0` 函数。

```cpp
// 此处省略 clear0 函数的定义。

void solve(){
	std::string n; std::cin >> n;
	std::string std_n = clear0(n, false, true);
	
	if(std_n[1] == '.') {
		std::cout << clear0(n, true, false);
		return ;
	}
	
	int first_no_zero = -1;
	for(int i = 0; i < std_n.size(); ++i) {
		if(std::isdigit(std_n[i]) && std_n[i] != '0') {
			first_no_zero = i;
			break;
		}
	}
	
	int e = std_n.find(".", 0) - first_no_zero;
	if(e > 0) --e;
	std::string ans = "";
	ans += std_n[first_no_zero]; ans += '.';
	for(int i = first_no_zero + 1; i < std_n.size(); ++i) {
		if(std_n[i] != '.') ans += std_n[i];
	}
	std::cout << clear0(ans, true, false) << "E" << e;
}
```

---

## 作者：liyp (赞：0)

## 思路
很简单的模拟题。

这道模拟题有一个难点就是如何将一个不符合规范的数转换成符合规范的数。

首先就是去除多余的零，这里我们只需要通过两遍循环，记录一下符合规范的数在给定的字符串中实际的头尾 $l$、$r$。

```cpp
l = -1;
for (int i = 0; i < s.size(); i++) {
    if (s[i] != '0' && s[i] !='.') {
        l = i;
        break;
    }
}
for (int i = s.size() - 1; i> -1; i--) {
    if (s[i] != '0' && s[i] != '.') {
        r = i;
        break;
    }
}
```

然后直接用自带的函数找到小数点的位置。
```cpp
s.find('.');
```

难点解决了。

接下来就是将一个字符串转换成科学计数法规范下的数。

实际上这个过程并不算难，按照数学转换的模拟即可。

```cpp
if (l == -1) {
    cout << 0;
    return 0;
}
if (l == r) {
    cout << s[l];
}
if (l != r) {
    cout <<s[l]<< ".";
    for (int i = l + 1; i <= r; ++i)
        if (s[i] != '.')
            cout << s[i];
}
if (l + 1 != xsd) cout << "E" << xsd - l - (l < xsd);
```
## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >> s;
    int l, r;
    l = -1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '0' && s[i] !='.') {
            l = i;
            break;
        }
    }
    for (int i = s.size() - 1; i> -1; i--) {
        if (s[i] != '0' && s[i] != '.') {
            r = i;
            break;
        }
    }
    int xsd = s.find('.');
    if (xsd == -1) {
        xsd = s.size();
    }
    if (l == -1) {
        cout << 0;
        return 0;
    }
    if (l == r) {
        cout << s[l];
    }
    if (l != r) {
        cout <<s[l]<< ".";
        for (int i = l + 1; i <= r; ++i)
            if (s[i] != '.')
            cout << s[i];
    }
    if (l + 1 != xsd) cout << "E" << xsd - l - (l < xsd);
    return 0;
}
```

---

## 作者：HUANGRUI11 (赞：0)

题目让我们求一个数的标准科学计数法。

比较简单的模拟，只是要注意以下几点：

 $1.$ 去掉头尾多余的零。
 
 $2.$ 转化后科学技术法中 $a \times 10^b $ 的 $a$ 后
 不能有多余零。

 $3.$ 注意指数为零的情况。

见代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
string s,ss="0";
int t,k;
bool p=true;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>s;
	s+='.';//以防是正数找不到小数点
	for(ri i=0;i<=s.size()-1;i++)
	if(s[i]>='0'&&s[i]<='9') ss+=s[i];//找出数字
	else if(s[i]=='.'&&p) p=false,k=i;//记录第一个小数点的位置
	int tt=ss.size()-1;//取长度
	while(t<ss.size()&&ss[t]=='0') t++;//去零
	while(tt>t&&ss[tt]=='0') tt--;
	cout<<ss[t];
	if(t!=tt) cout<<".";
	for(ri i=t+1;i<=tt;i++) cout<<ss[i];
	if(k-t!=0) cout<<"E"<<k-t;//判断不是指数零
	return 0;
} 
```
完结散花。

---

## 作者：kaaaai (赞：0)

## 分析
模拟，此题难点在于找到指数和处理多余的 $0$。用字符串存下数字，然后从左往右遍历出最左端有效数字的下标 $l$ 和小数点下标 $p$，从右往左遍历出最右端有效数字的下标 $r$。定义**有效数字**为除前导和后导 $0$ 之外的数字。特殊情况：

1. 如果输入数字中没有小数点，则把 $p$ 放在数字的右边，即 $p = len$。
2. 如果从右往左扫过了小数点的位置，则**小数点往左一位**就是最右端有效数字，即 $r = p-1$。这对于上一条所定义的 $p$ 也有效。

然后下标在 $[l,r]$ 中的就是输入中有效的部分，此时将该数字改为科学计数法只需要移动小数点即可。可以分类讨论：

- 若 $p < l < r$，例如输入 `.032330`，此时 $p = 0$，$l = 2$，$r = 5$，则易知应输出 `3.233E-2`，指数 $-2 = p-l$。对于原数，应输出一位后接小数点，再输出剩下的位数和指数。

- 若 $l < r < p$，例如输入 `31040.0`，此时 $p = 5$，$l = 0$，$r = 4$，则易知应输出 `3.104E4`，指数 $4 = r-l$。同理，输出一位原数后接小数点，再输出后面的数。但是要注意处理多余的 $0$，我的方法是找到最后一位应该输出的数字 $last$，输出 $last$ 及其之前的数字。在例子中 $last=3$。

- 若 $l < p < r$，例如输入 `089.3560`，此时 $p = 3$，$l = 1$，$r = 6$，则易知应输出 `8.9356E1`，指数 $4 = p-l-1$。输出同上。

其他的按照题目要求格式输出即可。

## 代码
~~很屎山~~。
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[1000005];
int main(){
	
	cin >> a;
	int len = strlen(a),l = -1,r = 0,p = len;
	for(int i = 0;i < len;i++){
		if(a[i]>='1'&&a[i]<='9'&&l==-1)l = i;
		if(a[i]=='.'){
			p = i;
			if(l!=-1)break;
		}
	}
	for(int i = len-1;i >= 0;i--){
		if(a[i]>='1'&&a[i]<='9'){
			r = i;
			break;
		}
		if(i==p-1){
			r = i;
			break;
		}
	}
	
	if(p>=r){
		int pos = r-l,last = -1;
		for(int i = l;i <= r;i++){
			if(i==l+1&&pos!=0){
				bool check = 0;
				for(int j = r;j >= i;j--){
					if(a[j]>='1'&&a[j]<='9'){
						check = 1;
						last = j;
						break;
					}
				}
				if(check)cout << '.';
			}
			if(i<=last||i<l+1)cout << a[i];
		}
		if(pos!=0)cout << 'E' << pos;
		return 0;
	}
	
	if(l>p){
		int pos = p-l;
		for(int i = l;i <= r;i++){
			if(i==l+1)cout << '.';
			cout << a[i];
		}
		cout << 'E' << pos;
		return 0;
	}
	
	if(p>l&&p<r){
		int pos = p-l-1;
		for(int i = l;i <= r;i++){
			if(i==l+1)cout << '.';
			if(a[i]!='.')cout << a[i];
		}
		if(pos!=0)cout << 'E' << pos;
		return 0;
	}
}
```

---

## 作者：Phoenix114514 (赞：0)

# CF691C 
## Exponential notation
## 题目大意
给你一个数 $N$，将其转换成标准的科学计数法。
## 思路
用一个字符串存数，找到三个东西的位置：最高位，最低位，小数点。因为有前缀零和后缀零，处理起来比较麻烦，所以具体怎么找呢？

1、下标从 0 开始找，找一个既非 0 又非小数点的位置，把它存在 $l$ 里，既最高位。

2、下标从输入字符串的最后一位开始找，找一个既非 0 又非小数点的位置，把它存在 $r$ 里，既最低位。

3、如果有小数点，那么把小数点存在 $c$ 里，否则 $c$ 等于 $s$ 的长度。

4、处理“E”前面的数，无论如何输出 $s_l$，如果 $l$ 不等于 $r$，再输出小数点。最后输出所有“E”前面的数（非小数点）。

然后我们来到这道题最难的部分（个人观点）：算“E”后面的数。

如果小数点再 $l$ 的前面，$d$ 就等于小数点的位置减 $l$ 的位置再减一。否则 $d$ 等于 $c-l$。最后如果 $d$ 不等于 0，就输出。

### $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin>>s;
    int l=0,r=0;
    for (l=0;s[l]=='0'||s[l]=='.';l++);
    for (r=s.size()-1;s[r]=='0'||s[r]=='.';r--);
    int c=s.find('.');
    if (c==-1)c=s.size();
    cout<<s[l];
    if (l!=r)cout<<'.';
    for (int i=l+1;i<=r;i++){
        if (s[i]=='.')continue;
        cout<<s[i];
    }
    int d;
    if (c>l)d=c-l-1;
    else d=c-l;
    if (d)cout<<'E'<<d;
    return 0;
}
```
制作不易，点个赞吧！

---

## 作者：PDAST (赞：0)

本来一次 A 掉就有可乐，但由于一个愚蠢的错误导致 RE，绷不住了。
## 题意
将一个形式奇怪的数改写成科学计数法。

样例输入：$0.0120$；

样例输出：$1.2E-2$。
## 思路
先去除前后导零，再查找小数点的位置，把小数点放到第二位并使第一位不为 $0$，统计该数是 $10$ 的几次方，再去除一次前后导零并输出，最后输出"E"和该数是 $10$ 的几次方即可。
## 注意事项
+ 去除前导与后导零时，一定要小心越界。
+ 处理小数点时一定要小心删去了非后导的零
+ 最后一定要再去除一次前后导零
## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
void doit(string &st){
	int len=st.size()-1,i=0;
	while(i<len&&st[i]=='0')i++;
	st=st.substr(i,len-i+1);
	if(st.find(".")==string::npos)return ;
	len=st.size()-1;//愚蠢的错误就在这
	while(st[len]=='0'&&len>0)len--;
	if(st[len]=='.')len--;
	st=st.substr(0,len+1);
}
int main(){
	string st;
	cin>>st;
	doit(st);
	int it=st.find(".");
	if(it==string::npos){
		it=st.size();
		st+=".";
	}
	if(st[0]=='.'){
		if(st.size()==1){
			cout<<"0";
			return 0;
		}
		if(st.size()==2){
			cout<<st[1]<<"E-1";
			return 0;
		}
		for(int i=1;i<st.size();i++){
			swap(st[i],st[i-1]);
			it--;
			if(st[i-1]>'0')break;
		}
		it++;
	}else for(int i=it;i>1;i--)swap(st[i],st[i-1]);
	doit(st);
	if(st[st.size()-1]=='.'){
		st.pop_back();
	}
	cout<<st;
	if(it!=1)cout<<"E"<<it-1;
} 
~~~

---

## 作者：abensyl (赞：0)

原题：[CF691C Exponential notation](https://www.luogu.com.cn/problem/CF691C)。

非常经典的一道题目。

## 思路

本题为数学题，主要考察写题的能力。

如果写不好，本体很容易 TLE。

首先，我们需要知道，科学计数法的表示方式。

举个例子：$3.14\times10^5 = 314000$。

我们将 $314000$ 的小数点标出来，为 $314000.0$，我们在科学计数法中，小数点在 $3$ 和 $14$ 之间，我们在 $314000.0$ 的 $3$ 和 $14$ 之间也加入小数点，为 $3.14000.0$，发现两个小数点之间正好五位数字，而 $314000$ 恰好等于 $3.14\times 10^5$，多测试几个数字，手算一下，易发现两点之间的数字数目和指数是相同的。

我们只要判断小数点应该加在哪里，然后计算两个小数点之间的数字数目即可。

另外要注意的是 **前导零和后倒零要去掉，如果指数为 $0$，则不要输出 `E0`**。

## 代码

```cpp
#include <bits/stdc++.h>

#pragma g++ optimize(2)
#pragma g++ optimize(3)
#pragma g++ optimize("inline")
#pragma g++ optimize("Ofast")

using namespace std;

#define ll long long
#define ull unsigned long long
#define s(v) (int)v.size()

const int mod=998244353,N=1000005,INF=1<<30;

bool q[N],h[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  string s;
  cin>>s;
  int len=s(s);
  bool flg=0;
  for(int i=0;i<len;++i) if(s[i]=='.') {flg=1;break;}
  if(!flg) s+='.',len++;
  int tpa,tpb;
  for(int i=len-1;i>=0;--i) h[i]=h[i+1]|(s[i]!='0'&&s[i]!='.');
  flg=1;
  for(int i=0;i<len;++i) {
  	if(s[i]=='.') {tpa=i;continue;}
  	else if(flg&&s[i]!='0') flg=0,tpb=i+1;
  	if(s[i]=='0'&&flg==1) continue;
  	if(h[i]) {
  		cout<<s[i];
  		if(i==tpb-1&&h[i+1]) cout<<'.';
  	}
  }
  int tt=(tpa>=tpb)?tpa-tpb:tpa-tpb+1;
  if(tt!=0) cout<<"E"<<tt;
  return 0;
}
```

我的 [AC 记录](https://www.luogu.com.cn/record/101085077)。

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定一个数字 $x$，将其转化为标准的科学计数法形式 $x=a \times 10^b$。若 $b \neq 0$，输出 $aEb$ 的形式；否则，输出 $a$。$x$ 的位数不超过 $10^6$。

## 思路

大致想法：我们首先想到要处理前导零与后置零，然后移动小数点位置，看看移动几次就能得到答案。

字符串输入。

首先，我们处理前导零，注意不能每次遇见前导零就 
```cpp
s.substr()
```
或
```cpp 
s.erase() 
```
因为这都是 $O(n)$ 的，当 $x$ 的位数多的时候，你就会超时。为了解决这个问题，我们可以找到所要删去的最后一个零的位置，然后再删除即可。

我们可以先特判一位数，直接输出。

如果不是一位数，那么我们将处理过的数转化成等价的
```
整数部分.小数部分
```
的形式。然后分类讨论：

当原数 $x \geq 10$，那么此时小数点是需要向左移动，设此时小数点在 $s_p$ 的位置，那么移动的位数应为 $p-1$ 位，$b=p-1$，重组字符串，记录下答案。

当原数 $1 \leq x < 10$，那么此时小数点是无需动的，记录下答案。

当原数 $x<1$ 时，此时小数点需要向右移动，移动到第一个不是零的数之后，设移动了 $q$ 次，那么 $b=-q-1$。重组字符串，记得去除前导零，记录下答案。

最后我们去除后置零，同样是先找到位置再删去，不然会超时。

判断输出的形式，然后输出即可。

## 代码

根据以上思路，我们就可以写出以下代码了。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>s;
    int l=s.size();
    while(s[s.size()-l]=='0'&&l>=0)l--;
    s=s.substr(s.size()-l);
    if(!isdigit(s[0]))s="0"+s;
    if(s.size()==1){
	cout<<s<<endl;
	return 0;
    }
    bool f=0;
    for(int i=0;i<s.size();i++){
	if(s[i]=='.')f=1;
    }
    if(!f)s+=".";
    int b;
    for(int i=0;i<s.size();i++){
	if(s[i]=='.')b=i-1;
    }
    if(s[0]=='0'&&b==0){
	while(s[b+2]=='0')b++;
	s=s.substr(b+2,1)+"."+s.substr(b+3);
	b=-b-1;
    }
    else s=s.substr(0,1)+"."+s.substr(1,b)+s.substr(b+2);
    l=s.size();
    while(s[--l]=='0');
    s=s.substr(0,l+1);
    if(s[s.size()-1]=='.')s=s.substr(0,s.size()-1);	
    cout<<s;
    if(b!=0)cout<<"E"<<b<<endl;
    return 0;
}
```

## 另解

当然不只是只有这一种写法。

我们可以看原数有无小数点，没有的话，去除前导零判断移动位数就输出，如果有，那就把它分成小数点前以及小数点后两段，分类操作即可。

详细过程看一下代码，还是比较简单易懂的:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string f, r;
    bool dot = false;

    for (;;)
    {
        char ch;
        if (scanf(" %c",&ch) != 1) break;

        if (ch == '.') dot = true;
        else if (dot == false)
        {
            if (f.empty() && ch == '0') continue;
            f.push_back(ch);
        }
        else
        {
            r.push_back(ch);
        }
    }

    while (r.empty() == false && r.back() == '0') r.pop_back();

    if (f.empty())
    {
        int skipped = 0;
        while (r[skipped] == '0') skipped++;
        if (r.size() > skipped + 1) printf("%c.%s", r[skipped], &r[skipped + 1]);
        else printf("%c", r[skipped]);
        printf("E-%d\n", skipped + 1);
        return 0;
    }
    else
    {
        if (f.size() == 1 && r.empty())
        {
            printf("%s\n", &f[0]);
        }
        else
        {
            string rr = string(&f[1]) + r;
            while (rr.empty() == false && rr.back() == '0') rr.pop_back();
            if (rr.empty() == false) rr.insert(rr.begin(), '.');
            printf("%c%s", f[0], &rr[0]);
            if (f.size() >= 2) printf("E%d\n", (int)f.size() - 1);
        }
    }
}
```


---

## 作者：wpj20241021005 (赞：0)

这道题虽然是一道绿题，但也不是非常得难，主要思路就是模拟。

我主要是分三种情况来做的:1.指数为0时；2.指数为负数；3.指数为正数。

指数为0时就不要考虑太多东西，直接把首尾的0去掉，再原样输出就行了。

而指数为负数时，就取离小数点最近的一位不为0的数作为科学计数法小数点前的一位，然后输出之后的数，位数就是小数部分中不为0的第一位到小数点的距离的相反数-1.

指数为正数时，就先输出第一个不为0的数，然后输出其到小数点的距离（如果没有小数点，就输出它的数位-1）

下面就是我的代码

```
#include<bits/stdc++.h>
using namespace std;
string a;
bool flag,b,p;
int first=0,last,s,k,sum;//定义首尾指针和其它东西
int main(){
	cin>>a;
	last=a.size()-1;
	for(int i=0;i<=a.size();i++)//寻找小数点
		if(a[i]=='.') {
			s=i;
			flag=true;
			break;
		}
	for(int i=0;i<a.size();i++){//去除开头多余的0
		if(a[i]=='0') first++;
		else break;
	}
	if(flag==true)//去除小数尾部多余的0
		for(int i=a.size()-1;i>=s;i--){
			if(a[i]=='0') last--;
			else break;
		}
	if(a[first+1]=='.'){//第一种情况
		for(int i=first;i<=last;i++){
			if(i==last&&a[i]=='.') break;
			cout<<a[i];
		}
		return 0;
	}
	if(a[first]=='.'){//第二种
		for(int i=first+1;i<=last;i++){
			if(a[i]!='0'){
				if(p==false) k=i-s;
				p=true;
			}
			if(a[i]!='0'||p==true){
				if(b==false&&i!=last){
					cout<<a[i]<<".";
					b=true;
				}
				else cout<<a[i];
			} 
		}
		cout<<"E-"<<k;
		return 0;//结束
	} 	
	//第三种情况
	if(a[last]=='.') last--;
	for(int i=last;i>=first;i--){//去除尾部多余的0，并计数位
		if(a[i]=='0'){
			sum++;last--;
		}
		else break;
	}
	if(first==last) cout<<a[first];
	else{
		cout<<a[first]<<".";
		for(int i=first+1;i<=last;i++){
			if(a[i]!='.') {
				cout<<a[i];
				sum++;
			}
		}
	}
	if(flag==true) cout<<"E"<<s-first-1;
	else if (sum!=0) cout<<"E"<<sum;//输出
	return 0;//结束撒花
}
```

---

## 作者：iiawaKL (赞：0)

###### 蒟蒻又写题解啦
今天我们来讲一道绿题，本蒟蒻自认为不是特别地难。

题意：很复杂，我就不说了。

思路：模拟


1 . 对原string进行处理:

处理前缀0
	
处理小数点后缀0
	
处理无用小数点

注意str要开1e6

首先，先要把首尾连续的0去掉，然后去掉无用的小数点，然后再取首位输出，就行了。

Code->

```
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int main(){
	string s;
	cin>>s;
	s='0'+s;
	int pos=-1,r=-1,l=-1;
	while(++pos<s.size()&&s[pos]!='.');
	if(pos==s.size())
	s+=".0";
	while(s[++r]=='.'||s[r]=='0');
	l=s.size();
	while(s[--l]=='.'||s[l]=='0');
	if(l==r){
		cout<<s[r];
		if(r<pos){
			if(r==pos-1)
			return 0;
			cout<<"E"<<pos-r-1;
			return 0;
		}
		cout<<"E"<<pos-r;
		return 0;
	}
	cout<<s[r]<<".";
	for(int i=r+1;i<=l;i++){
		if(s[i]=='.')
		continue;
		cout<<s[i];
	}
	if(r==pos-1)return 0;
	if(r<pos)cout<<"E"<<pos-r-1<<endl;
	else cout<<"E"<<pos-r<<endl;
	return 0;
}
```


---

