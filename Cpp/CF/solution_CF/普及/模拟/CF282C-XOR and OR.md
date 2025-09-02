# XOR and OR

## 题目描述

The Bitlandians are quite weird people. They do everything differently. They have a different alphabet so they have a different definition for a string.

A Bitlandish string is a string made only of characters "0" and "1".

BitHaval (the mayor of Bitland) loves to play with Bitlandish strings. He takes some Bitlandish string $ a $ , and applies several (possibly zero) operations to it. In one operation the mayor may take any two adjacent characters of a string, define one of them as $ x $ and the other one as $ y $ . Then he calculates two values $ p $ and $ q $ : $ p=x xor y $ , $ q=x or y $ . Then he replaces one of the two taken characters by $ p $ and the other one by $ q $ .

The $ xor $ operation means the bitwise excluding OR operation. The $ or $ operation is the bitwise OR operation.

So for example one operation can transform string 11 to string 10 or to string 01. String 1 cannot be transformed into any other string.

You've got two Bitlandish strings $ a $ and $ b $ . Your task is to check if it is possible for BitHaval to transform string $ a $ to string $ b $ in several (possibly zero) described operations.

## 样例 #1

### 输入

```
11
10
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1
01
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
000
101
```

### 输出

```
NO
```

# 题解

## 作者：潜翎 (赞：6)

嗯哼，蒟蒻看这里没有题解就自己写写

其实是道非常非常简单的题，并没有绿题该有的难度。

仔细思考就会发现，如果A串中有一个1，就可以通过0和相邻的1的异或操作把A串全部换成1。

像这样  
###### 0010 -->(2与3异或) 0110 -->(1与2异或) 1110 -->(4与3异或) 1111

A串全为1之后呢，我们同理可通过异或操作在B串对应位造出0

故只要A串B串中都含1（无论数量）或A，B串都仅有0且AB长度相同就是YES

代码效率不高，看着玩玩就好。

```cpp
#include <stdio.h>
#include <string.h>
#define N 1000010
char a[N],b[N];
int n1,n2,f1,f2;
int main()
{
	scanf("%s %s",a+1,b+1);
	int l1=strlen(a+1),l2=strlen(b+1);
	if(l1!=l2) {printf("NO");return 0;}
	for(int i=1;i<=l1;i++) if(a[i]=='1'){f1=1;break;}
	for(int i=1;i<=l1;i++) if(b[i]=='1'){f2=1;break;}
	if((f1&&f2)||(!f1&&!f2)) printf("YES");
	else printf("NO");
	return 0;
}
```

---

## 作者：无意识躺枪人 (赞：2)

异或（xor）是一个数学运算符。它应用于逻辑运算。异或的数学符号为“⊕”，计算机符号为“xor”

a⊕b = (¬a ∧ b) ∨ (a ∧¬b)

直接用异或性质即可

```c
#include<bits/stdc++.h>
using namespace std;
char s1[1000005],s2[1000005];
int main()
{
	while(scanf("%s",s1)!=EOF)
	{
		scanf("%s",s2);
		int len1=strlen(s1);
		int len2=strlen(s2);
		if(len1!=len2) {printf("NO\n");continue;}
		else
		{
			long long num1=0,num2=0;
			for(int i=0;i<len1;i++) if(s1[i]=='1') num1++;
			for(int i=0;i<len2;i++) if(s2[i]=='1') num2++;
			if((num1==0&&num2==0)||(num1*num2!=0)) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}
```

注意开 long long

---

## 作者：zibenlun (赞：1)

# 题意理解
给定两个字符串，通过相邻两位的异或和或运算，使一个字符串变成另一个。


# 思路

本题的关键是或运算，因为或运算的结果都是 $1$,所以只要有了一个 $1$，那么所有的 $0$ 就都能够变成 $1$，所以我们可以得出结论，只要 $B$ 字符串中有 $1$，那么 $A$ 中必须也有一个 $1$，不然就不能变成 $B$ 串。


# 你们最爱看的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
//快读，快写
inline int read(){
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		s=(s<<3)+(s<<1)+(ch^48);
		ch=getchar();
	}
	return s;
}
inline void write(long long x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string a,b;
	cin>>a>>b;
	if(a.size()!=b.size()){
		cout<<"NO";
		return 0;
	}
	int flaga=0,flagb=0;
	for(int i=0;i<a.size();i++){
		if(a[i]=='1') flaga=1;
		if(b[i]=='1') flagb=1;
	}
	if(flagb==1&&flaga==0 || flaga==1&&flagb==0) cout<<"NO";
	else cout<<"YES";
	return 0;
}


```
点个赞再走吧~

---

## 作者：wangjiajian (赞：1)

## [洛谷该题地址](https://www.luogu.com.cn/problem/CF282C)
## [ CodeForces 该题地址](https://codeforces.com/problemset/problem/282/C)


## 题目大意
给两个 $01$ 串 $a$ 和 $b$，每次取 $a$ 串相邻的两个数 $x$ 和 $y$，得到 $p = x\oplus y, q = x|y$，用 $p$ 和 $q$ 代替 $x$ 和 $y$。

问经过若干次操作后，是否能得到 $b$ 串。

## 解题思路
1. 通过观察可以发现，$01$ 和 $10$ 和 $11$ 可以通过若干次操作相互转换。
2. 通过观察可以发现，$00$ 只能保持为 $00$。


那么只要 $a$ 串与 $b$ 串都有或都无 $1$，他们之间就一定可以相互转换。注意，长度必须也一样。
## 答案代码
```cpp
#include <bits/stdc++.h>
using namespace std;

bool opt1, opt2;
string a, b;

int main() {
	cin >> a >> b;
	for(int i=0; i<a.length(); i++) {
		if(a[i] == '1') {
			opt1 = true;
			break;
		}
	}
	for(int i=0; i<b.length(); i++) {
		if(b[i] == '1') {
			opt2 = true;
			break;
		}
	}
	if(opt1==opt2 && a.length()==b.length())
		puts("YES");
	else
		puts("NO");
	return 0;
}
```


---

## 作者：xiaofeng_and_xiaoyu (赞：0)

由题意可知，输入的是长度小于 $10^{6}$ 的 $01$ 串。

给出样例：

>$0\oplus1=1$，$1\oplus1=0$，$0\oplus0=0$

>$0\parallel1=1$，$1\parallel1=1$，$0\parallel0=0$

我们可以发现，一个字符串中若有 $1$，则它相邻的数可以变为 $0$ 或 $1$。

也就是说，如果两个字符串想要相等，要么都全是 $0$，要么两个都必须有 $1$。

另外，这两个字符串必须长度相等，否则肯定无法变换成功。

代码如下：

```cpp
#include<iostream>
using namespace std;
int main(){
	string x,y;
	cin>>x>>y;
	if(x.length()!=y.length()){
		cout<<"NO"<<endl;
		return 0;
	}
	bool x1=0,y1=0;
	for(int i=0;i<x.length();i++){
		if(x[i]=='1'){
			x1=1;
			break;
		}
	}
	for(int i=0;i<x.length();i++){
		if(y[i]=='1'){
			y1=1;
			break;
		}
	}
	if(x1==y1){
		cout<<"YES";
		return 0;
	}else{
		cout<<"NO";
		return 0;
	}
}
```


---

## 作者：ICU152_lowa_IS8 (赞：0)

这一题……说白了就是个思维题，分类讨论就行了。

------------


举个例子：

我们现在有一个字符串 $0001$。

字符串从右往左数第一位和第二位异或，可以得到 $0011$ 这个字符串，再将第二位和第三位异或，以此类推……就可以得到一个全是 $1$ 的字符串。

那如果我们需要 $0$ 怎么办？

还是之前那个字符串，现在它已经是 $1111$ 了。比如说我们需要 $1011$，那么只需要将从左往右数第一位和第二位异或就行了。当我们需要有一个位置为 $0$ 时，只需要将这一位和后一位异或一下就行了。

由此我们得到一个结论：**当一个字符串内有 $1$ 的时候，可以构成除了形如 $0000$ 这样的全零字符串之外的所有的字符串长度的二进制数（这里的二进制数可以加上前导零）。**

至于为什么一个有字符 $1$ 的字符串不能构成全零字符串稍微想一想应该就知道了，作者就不多说了。


------------
那么分类讨论就很简单了！

如果两个字符串长度相等且都拥有 $1$ 或者都全部是 $0$，那么肯定可以构成相同字符串，输出 YES，否则输出 NO。


------------
代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	string a,b;
	cin>>a>>b;
	if(a.length()!=b.length()){
		cout<<"NO";
		return 0;
	}
	int flaga0=1,flagb0=1;
	for(int i=0;i<a.length();i++){
		if(a[i]=='1'){
			flaga0=0;
			break;
		}
	}
	for(int i=0;i<b.length();i++){
		if(b[i]=='1'){
			flagb0=0;
			break;
		}
	}
	if(flaga0!=flagb0){
		cout<<"NO";
		return 0;
	}
	cout<<"YES";
	return 0;
}

```




---

## 作者：Cutler (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF282C)

简化题意：

判断一个 $01$ 串是否可以通过相邻两位异或的方式转换成另一个 $01$ 串。

显然可以根据异或的性质得到：**只要一个01串中含有一个1，那么整个串都可以变成一个全是1的串**。

然后我们就可以在 $A$ 串的对应位置替换成 $0$。

所以除两个串中一个有一，一个没有，或者两串的长度不一之外的情况都可以成功转换。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

string a, b;
int o, z;

int main(){
	cin >> a >> b;
	if(a.size() != b.size()) {puts("NO");return 0;}
	for(int i = 0;i < a.size();++ i)
		o = max(o, (int)(a[i] == '1')),
		z = max(z, (int)(b[i] == '1'));
	puts(o ^ z ? "NO" : "YES");
	return 0;
}
```

优雅结束。

---

## 作者：zyh888 (赞：0)

# 题意
给定两个 $01$ 串，问 $A$ 是否可以通过相邻两位的异或和或操作得到 $B$ 串。

这个翻译对于相邻两位的操作解释有些不当，正确的应该是：任意取两个相邻字符 $x$ 和 $y$，设 $p$ 为 $x$ 异或 $y$，$q$ 为  $x$ 或 $y$，然后任意将选的两个数替换为 $p$ 和 $q$。

# 思路
前置芝士：异或，$x$ 异或 $y$ 定义为：如果 $x$ 与 $y$ 相等，返回 $0$，否则返回 $1$。（或就不多说了，大家都会吧qwq）

首先无论相邻两位怎么搞，也不可能将字符串的位数改变，所以如果两个字符串长度不同，就不行

如果两个字符串全由 $0$ 组成，那么就不用进行任何操作。

如果 $A$ 中有 $1$，就可以将一个与 $0$ 相邻的 $1$ 进行操作，得到两个 $1$，将两个位置都替换为 $1$，重复这个操作，就可以将 $A$ 串变为全部由 $1$ 组成。

接着我们要用 $A$ 串尝试造出 $B$ 串，首先我们知道 $1$ 异或 $1$ 为 $0$，或为 $1$，对于 $B$ 串中的每个 $0$，就可以将 $A$ 串中它对应的位置和相邻的 $1$ 进行操作，这样就造出了一个 $0$ 和一个 $1$，把 $B$ 串中有 $0$ 的位置在 $A$ 串中换成 $0$，重复这个操作，可以发现最后不管怎么操作 $A$ 串中都有一个 $1$，所以 $B$ 中至少要有一个 $1$，才能将 $A$ 变成 $B$。


# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string a,b;
	cin>>a>>b;
	int c=a.size(),d=b.size();
	bool f=false,f1=false;
	if(a.size()^b.size()){ //两串长度不等，直接输出NO
		cout<<"NO";
		return 0;
	} 
	for(int i=0;i<c;i++){ //因为长度一样，所以只用循环一个串的长度
		if(f&&f1){ //两串中都至少有一个1
			cout<<"YES"; 
			return 0;
		} 
		if(a[i]=='1') f=true;
		if(b[i]=='1') f1=true;
	}
	if(f^f1) cout<<"NO"; //两串都没有1也就是都是0
	else cout<<"YES";	
	return 0;
}
```


---

## 作者：Aw顿顿 (赞：0)

## 题意

给定两个 $01$ 串 $A$ 和 $B$，问能不能通过**相邻位**的 $\textbf{or}$ 或者 $\textbf{xor}$ 把 $A$ 变成 $B$。

## 异或操作

异或运算特性：若两数相同（同为 $1$ 或 $0$）那么两数异或结果为 $0$，反之为 $1$。

| $x$ | $y$ | $x\text{ xor }y$ |
| :-: | :-: | :--------------: |
| $1$ | $1$ |        $0$       |
| $1$ | $0$ |        $1$       |
| $0$ | $1$ |        $1$       |
| $0$ | $0$ |        $0$       |

## 转换 $\small 01$ 串


对于一个**非全 $0$ 串**，我们一定能将其转化为全 $1$ 串。我们以 $010001$ 为例：

异或顺序：$1,3,4,5$，也就是所有为 $0$ 的位置，为什么？我们每次异或（将与 $1$ 相邻的 $0$ 异或），都可以将这个 $0$ 变成 $1$，同样地，我们可以重复这个过程。

这样我们就将一个含有 $1$ 的串变成了只含有 $1$ 的串。

这是第一步，接下来，我们要让 $A$ 串（这个已经成为全 $1$ 串的东西）靠近 $B$ 串，我们这么办：

对于在 $B$ 当中是 $0$ 的位置，我们再做一次异或运算，就能使他为 $0$，因为他的周围都是 $1$，和它（变换前的）本身一样。

也就是说，只要两个 $01$ 串都有 $1$，就能够将 $A$ 转化为 $B$。

但是只有这样才行么？不，两个全 $0$ 串也能满足条件。哦对了，如果两个 $01$ 串长度不同，是不能转换的。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
bool fa,fb;
int main(){
    cin>>a>>b;
    if(a==b){
        puts("YES");
        return 0;
    }if(a.size()!=b.size()){
        puts("NO");
        return 0;
    }
    for(int i=0;i<a.size();i++)
        if(a[i]=='1'){
            fa=1;break;
        }
    for(int i=0;i<b.size();i++)
        if(b[i]=='1'){
            fb=1;break;
        }
    if(fa&&fb)puts("YES");
    else puts("NO");
}
```

---

## 作者：chenkaiwen (赞：0)

这一题主要考点是异或运算的性质，总结一下，要输出“YES”就会有两个条件：

1. 两个字符串的长度相同
2. 一个字符串能转移成另一个字符串

第一个条件很好理解，但是第二个条件则比较复杂，我们可以通过异或运算的性质得知，一个字符串只要有1个“1”那么它就可以转移成任意字符串，假如两个字符串都没有“1”那么他们肯定是相同的（因为只要“1”和“0”两种字符，没有“1”的话，剩下的肯定都是“0”）所以，第二个条件就变成了：两个字符串都有“1”或者都没有“1”，那么想要判断的二个条件，只要用 $O(n)$ 的暴力算法，从头到尾的搜一遍就可以了，其他细节我会在代码的注释中详细写出，这里就不多讲了。

代码如下：

[AC证明](https://www.luogu.com.cn/record/31717436)

```cpp
#include<bits/stdc++.h>//多余的头文件最好要删去 
#include <iostream>
using namespace std;
string s1,s2; 
int l1,l2;//存字符串长度 
bool ans1=0,ans2=0;
int main() {
	ios::sync_with_stdio(0);
	cin>>s1>>s2;//输入 
	l1=s1.length(),l2=s2.length();
	if(l1!=l2){//如果长度不同，直接输出NO 
		cout<<"NO"<<endl;
		return 0;
	}
	for(int i=0;i<l1;i++){
		if(s1[i]=='1'){ 
			ans1=1;
		}
		if(s2[i]=='1'){
			ans2=1;
		}
	}
	if(ans1==ans2){//如果都有一，则输出YES 
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;//否则输出NO 
	}
	return 0;
}




```


---

