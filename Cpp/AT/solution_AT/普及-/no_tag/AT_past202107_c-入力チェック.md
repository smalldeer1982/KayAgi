# 入力チェック

## 题目描述

[problemUrl]: https://atcoder.jp/contests/past202107-open/tasks/past202107_c

`0` から `9` の数字からなる文字列 $ S $ が与えられます。  
 $ S $ を整数の十進数表示として見たとき、以下の $ 2 $ つの条件をともに満たすかどうか判定してください。

- 先頭に不要な `0` がない。
- $ L $ 以上 $ R $ 以下である。

## 说明/提示

### 注意

この問題に対する言及は、2021/7/17 18:00 JST まで禁止されています。言及がなされた場合、賠償が請求される可能性があります。 試験後に総合得点や認定級を公表するのは構いませんが、どの問題が解けたかなどの情報は発信しないようにお願いします。

### 制約

- $ S $ は `0` から `9` の数字からなる文字列
- $ 1\ \leq\ |S|\ \leq\ 100 $
- $ 0\ \leq\ L\ \leq\ R\ \leq\ 10^9 $
- $ L $ と $ R $ は整数

### Sample Explanation 1

$ 13579 $ は先頭に不要な `0` を持たず、 $ 10000 $ 以上 $ 20000 $ 以下であるため、条件を満たします。 よって、`Yes` と出力します。

### Sample Explanation 2

$ S $ が表す整数は、$ 64 $ ビット整数型で表現できる最大値よりも大きいことがあります。

### Sample Explanation 3

$ 05 $ は先頭に不要な `0` を持つので、条件を満たしません。 よって、`No` と出力します。

### Sample Explanation 4

$ 0 $ の先頭の `0` は、不要な `0` ではないことに注意してください。

## 样例 #1

### 输入

```
13579
10000 20000```

### 输出

```
Yes```

## 样例 #2

### 输入

```
12345678901234567890
0 1000000000```

### 输出

```
No```

## 样例 #3

### 输入

```
05
5 5```

### 输出

```
No```

## 样例 #4

### 输入

```
0
0 1```

### 输出

```
Yes```

# 题解

## 作者：_s_z_y_ (赞：8)

## 思路
输入后，先判断字符串 $ S $ 是否有前导 $ 0 $，这里要特判这个数是 $ 0 $ 的情况。

然后由于范围 $ 0 \le L,R \le 10^9 $，当 $  |S|>10 $ 时直接输出 No。

最后判断 $ S $ 转换为数字后是否在 $ L $ 和 $ R $ 之间。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r,num;
string s;
int main()
{
	cin>>s;
	cin>>l>>r;
	if(s.size()>1&&s[0]=='0')//判断前导 0 
	{
		puts("No");
		return 0;
	} 
	if(s.size()>10)//数位超过 10 位 
	{
		puts("No");
		return 0;
	}
	for(int i=0;i<s.size();i++)//转换成数字
		num=num*10+(s[i]-'0');
	if(num<l||num>r)// S 不在范围内 
		puts("No");
	else
		puts("Yes");
	return 0;
}
```

---

## 作者：Molina (赞：5)

# 题目大意：
### 题目链接：[luogu](https://www.luogu.com.cn/problem/AT_past202107_c) 
# 本题思路：
直接**模拟**即可，没什么思维难度。

输入后，先判断字符串 $ s $ 是否有前导 $ 0 $。注意，这里还要特判一下只有一个 $ 0 $ 的情况。

然后见函数，函数的作用是将字符串 $ s $ 转换成数字。
```cpp
long long cz(){
	long long sum=0,k=1;
	for(int i=s.size()-1;i>=0;i--){
		sum+=(s[i]-'0')*k;
		k*=10;//移位
	}
	return sum;
}
```

有了函数，便可以开始判断了，判断返回的值是否大于等于 $ l $，小于等于 $ r $，之后就可以输出了。

注意：需要开 ```long long``` 才可以。
# 代码来咯~
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;
string s;
long long cz(){//将字符串转换成数字的函数
	long long sum=0,k=1;
	for(int i=s.size()-1;i>=0;i--){
		sum+=(s[i]-'0')*k;
		k*=10;//移位
	}
	return sum;
}
int main(){
	cin>>s>>l>>r;
	int len=s.size();
	if(s[0]=='0' && len>1){//判断是否有前导0
		cout<<"No";
		return 0;
	} 
	if(l<=cz()  &&  cz()<=r)  cout<<"Yes";//判断是否在范围内
	else   cout<<"No";
	return 0;
}
```

---

## 作者：Jasoncwx (赞：5)

本题已经有翻译了，这里不再阐述。
## 题目思路
本题不需要用到高精度。

我们发现，$0\le L\le R\le 10^9$。所以当 $|S|>10$ 直接输出 `No`。

如果 $S$ 有前导零，也就是 $S_0$ 为 `0` 也要输出 `No`。但这里要特判一下当 $S$ 为 `0` 时，不能直接输出 `No`。

如果 $S$ 不满足上面这两个条件，就把 $S$ 转换成整数，再判断是否 $L\le S\le R$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int string_to_int(string str){
	int ans=0;
	for(int i=0;i<str.size();i++)ans=ans*10+str[i]-'0';
	return ans;
}//把字符串转换为整数
int main(){
	string str;
	cin>>str;
	if(str[0]=='0'&&str!="0"||str.size()>10)return puts("No"),0;//直接输出No
	int l,r;
	cin>>l>>r;
	int n=string_to_int(str);//转换为整数
	if(l<=n&&n<=r)cout<<"Yes";//符合条件
	else cout<<"No";
}
```

---

## 作者：YuTianQwQ (赞：2)

# 题目解析

这个代码的目标是判断一个字符串形式的数字是否在两个长整型区间 $[l, r]$ 内。如果在区间内，则返回 "Yes"，否则返回 "No"。它首先检查字符串的第一个字符是否为 "0"，然后在一个循环中计算字符串所代表的数字，并同时判断该数字是否超过了区间的上界 $r$。

## 解题思路

1. **读取输入**：读取字符串 $s$ 以及长整型区间的两个界 $l$ 和 $r$。

    ```cpp
    cin >> s >> l >> r;
    ```

2. **处理字符串首字符为 "0" 的情况**：如果字符串的第一个字符是 "0"，并且字符串长度大于 1，那么这个字符串所表示的数字不可能在区间 $[l, r]$ 内，因此输出 "No" 并结束程序。

    ```cpp
    if(s[0] == '0' && s.size() > 1)
    {
        cout << "No" << endl;
        return 0;
    }
    ```

3. **计算字符串所代表的数字**：用一个循环逐个处理字符串中的每个字符，并计算出字符串所代表的数字。在这个过程中，如果发现数字已经超过了 $r$，则输出 "No" 并结束程序。

    ```cpp
    ll n = 0;
    for(char c : s)
    {
        if (n > r/10 || (n == r/10 && c-'0' > r%10))
        {
            cout << "No" << endl;
            return 0;
        }
        n = n*10+c-'0';
    }
    ```

4. **判断数字是否在区间内**：如果数字在区间 $[l, r]$ 内，则输出 "Yes"，否则输出 "No"。

    ```cpp
    if(n >= l && n <= r) cout << "Yes" << endl;
    else cout << "No" << endl; 
    ```

总结起来，这个程序通过计算字符串所代表的数字，并判断这个数字是否在给定的区间内，来决定输出 "Yes" 还是 "No"。

# 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    string s;
    ll l, r;
    cin >> s >> l >> r;
    if(s[0] == '0' && s.size() > 1)
	{
        cout << "No" << endl;
        return 0;
    }
    ll n = 0;
    for(char c : s)
	{
        if (n > r/10 || (n == r/10 && c-'0' > r%10))
		{
            cout << "No" << endl;
            return 0;
        }
        n = n*10+c-'0';
    }
    if(n >= l && n <= r) cout << "Yes" << endl;
    else cout << "No" << endl; 
    return 0;
}


---

## 作者：_7Mr (赞：1)

# 思路
- 如果输入的字符串的第一位有 $0$ 那么也就是有前导 $0$，输出 ```No```。**注意这里要特判只有 $1$ 个 $0$ 的情况。**

- 如果不符合上面的那一种情况，那么我们就将字符串转换成数字，然后判断数字是否在范围内，如果在范围内，那么输出 ```Yes```，否则输出 ```No```。

# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
string s;
int l,r;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>s>>l>>r;
	if(s[0]=='0' && s.size()>1){//判断是否有前导0，注意特判只有一个0的情况
		cout<<"No\n";
		return 0;
	} 
	int ans=0;//转换成数字
	for(int i=0; i<s.size(); i++) ans=ans*10+(s[i]-'0');
	if(l<=ans && ans<=r) cout<<"Yes\n";//判断是否在范围内
	else cout<<"No\n";
	return 0;
}

```

---

## 作者：xiaoming007 (赞：1)

## 思路

由于 $1 \leq |S| \leq 100$，那么显然，无论是 `int`，`long long` 还是 `__int128` 都存不下，我们只能用一个 `string` 存。

此时我们再来看看题目的条件：

- $S$ 不能有前导 $0$。

- $S$ 需要介于 $L$ 和 $R$ 之间。

很容易想到判前导 $0$ 的方法：即第一个字符是否为 `0`。

但是此处有个特例，当 $S = 0$ 时，它不算包含前导 $0$，需单独特判。

接下来由于范围 $0 \leq L,R \leq 10^9$。

而 $10^9$ 转换为数字有 $10$ 位，那么当 $|S| > 10$ 时，肯定不能介于中间。

剩下的 $S$ 就可以被 `long long` 储存，只需利用快读原理将其转化为数字判断即可。

## 代码

```cpp
//Author: Saint_ying_xtf
//xiaoming007 = Saint_ying_xtf
#include <bits/stdc++.h>
using namespace std;
#define int long long
main(){
	string s;
	int l, r, ans = 0;
	cin >> s;
	scanf("%lld %lld", &l, &r);
	if(s == "0"){
	    if(l == 0) puts("Yes");
	    else puts("No");
    }else if(s[0] == '0'){
		puts("No");
	}else if(s.size() > 10){
		puts("No");
	}else{
		for(int i = 0; i < s.size(); i++){
			ans = (ans << 1) + (ans << 3) + (s[i] ^ '0');
		}
		if(l <= ans && ans <= r){
			puts("Yes");
		}else{
			puts("No");
		}
	}
	return 0;
}
```

---

## 作者：togeth1 (赞：1)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/AT_past202107_c)

### [题意解析]
给你一个只包含数字的字符串 $s$ 和两个边界 $l$ 与 $r$。如果 $s$ 满足：

+ 没有前导 $0$，且这个数在 $64$ 位整型的范围之内，也就是说它的不能超过 $10$ 个数位。

+ $s$ 在 $l$ 和 $r$ 之间，也就是 $l\leq s\leq r$。

那就输出 $\verb!Yes!$，否则输出 $\verb!No!$。

### [思路分析]
按题目说的做就好了，先求出字符串 $s$ 的长度，再把 $s$ 转成 $\verb!int!$ 类型，最后和 $l$ 与 $r$ 比较，输出 $\verb!Yes!$ 或者 $\verb!No!$ 就好了。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[110];
int l,r,ans;
int main()
{
	cin>>(s+1)>>l>>r;
	/*让 s 从下标 1 开始读入*/
	int n=strlen(s+1);
	/*求出 s 的长度*/
	if((s[1]=='0'&&n!=1)||n>10){cout<<"No";return 0;}
	/*如果有前导 0 且这个数不是 0，或者数位超过 10 位，直接输出 No*/
	for(int i=1; i<=n; i++)ans=ans*10+(s[i]-'0');
	/*把字符串转成整形*/
	if(l<=ans&&ans<=r)cout<<"Yes";
	else cout<<"No";
	/*判断是否在区间之内*/
	return 0;
}
```

---

## 作者：____someone____ (赞：1)

## Description:

[$\text{\color{OrangeRed}{题目传送门}}$](https://www.luogu.com.cn/problem/AT_past202107_c)

[$\text{\color{OrangeRed}{更好的食用效果}}$](https://www.luogu.com.cn/blog/666someonebk999/solution-at-past202107-c)

一个 $0\sim9$ 的字符串 $S$，代表一个十进制整数。

当满足以下两个条件时输出 `Yes`：
- $S$ 没有多余的前导 $0$，且不超过 $64$ 位整型的最大值；
- $S$ 在 $L$ 和 $R$ 之间（包括 $L$ 和 $R$）。

否则输出 `No`。

## Solution:
$0\le L\le R\le10^9$ 该用 __long long__ 了。

首先，我们要注意一点，当 $S$ 为 `0` 时，这个 $0$ 不算无用的前导 $0$，所以要特判一下。

其次， $64$ 位整型的判断只要数字位数小于 $11$ 位就可以。

还有就是由字符串向数字的转换可以定义一个函数来实现，代码如下如下：

```
int pp(string s) 
{
	int sum=0;  //用来存字符代表的数 
	for(int i=0;i<s.size();i++)
	{
		sum*=10;  //向左移一位 
		sum+=int(s[i]-'0');  //加上s[i]代表的数字 
	}
	return sum;  //返回sum的值 
}
```
OK，这样，就可以愉快地写代码了！

## AC Code（杜绝抄袭）:
```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int l,r;

int pp(string s) 
{
	int sum=0;  //用来存字符代表的数 
	for(int i=0;i<s.size();i++)
	{
		sum*=10;  //向左移一位 
		sum+=int(s[i]-'0');  //加上s[i]代表的数字 
	}
	return sum;  //返回sum的值 
}

int main()
{
	cin>>s>>l>>r;
	if(s=="0")  //特判 
	{
		if(l==0)cout<<"Yes"<<endl; 
		else cout<<"No"<<endl;
		return 0;  //直接结束程序，防止继续执行 
	}
	if(s[0]=='0'||s.size()>=11) //如果有多余的前导0或超过10位 
	{
		cout<<"No"<<endl;
		return 0;
	}
	long long n=pp(s);  //由字符串向数字的转换 
	if(l<=n&&n<=r)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
```


[$\text{\color{blue}AC记录}$](https://www.luogu.com.cn/record/98046122)

---

## 作者：VitrelosTia (赞：0)

题意翻译说得很清楚，不再复述了。思路很显然，两种情况分别判断看是否符合，都不符合输出 `No` 就行了。

第一种情况直接判断第一个字符为 $0$ 且字符串不为 `0` 并且字符串长度大于 $10$。第二种情况把字符串转换成数字，判断是否不在 $L$ 和 $R$ 之间。均不满足就输出 `Yes`。

注意需要开 `long long`。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

string s;
int l, r;

int f(string s) {
    int ans = 0;
    for (int i = 0; i < s.size(); i++) ans = ans * 10 + (s[i] - '0');
    return ans;
}

bool check() {
    if ((s[0] == '0' && s != "0") || s.size() > 10) return false;
    if (l > f(s) || f(s) > r) return false;
    return true;
}

signed main() {
    cin >> s >> l >> r;
    puts(check() ? "Yes" : "No");
    return 0;
}
```

---

## 作者：whx2009 (赞：0)

## 本题思路：
这道题其实非常简单，因为题目中保证了数据都在 long long 以内，那么我们就可以直接判定这个数字是否前缀为零，若是就输出 No，若不是就判断 $S$ 是否在 $L$ 与 $R$ 之间，如果在就输出 Yes，如果不在就输出 No。

这样有的人就问了，不是题目中还要判定这个数是否超出范围吗？其实我们并不用，因为超出范围了计算机里面自动转为了负数，怎么样都不会打出 Yes。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
char s[101];
int main()
{
	cin>>s+1;
	int n=strlen(s+1);
	if(s[1]-'0'==0 && n>1)
	{
		cout<<"No";
		return 0;
	}
	long long c=0;
	for(int i=1;i<=n;i++)
	{
		c=c*10+s[i]-'0';
	}
	cin>>a>>b;
	if(c>=a&&c<=b) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```


---

## 作者：jsisonx (赞：0)

# 题目思路

先来看看数据范围 $1≤∣S∣≤100$ 显然不能用普通的  ```long long ``` 来存储数据。考虑使用字符串。

接着进行特判：

- 若 $S=0$:符合要求，继续执行；
- 若 $S>0$:且 S 的最高位是 0：不符合要求（有前导 0），直接输出 ```No ```；
- 若 $\mid S \mid>10$:超出 64 位整型范围，直接输出 ```No```；
- 若上述情况均没有，那么继续执行。

字符串的大小比较：其实比较大小不需要转成数字。 c++ 支持字符串（ ```string``` 类型）使用基本的比较运算符进行大小比较，所以直接像数字一样比较大小即可。

# 代码

```
#include<iostream>
#include<cstring>
using namespace std;
int main(){
	string a,b,c;
	cin>>a>>b>>c;
	if((a[0]=='0'&&a.size()!=1)||a.size()>=10){
		cout<<"No"<<endl;
		return 0;
	}
	if(a>=b&&a<=c){
		cout<<"Yes"<<endl;
		return 0;
	}
	cout<<"No"<<endl;
	return 0;
}
```



---

## 作者：Milthm (赞：0)

## AT_past202107_c 题解

### 前置知识

- 字符串的比较

### 题目解法

看到好多大佬都是把字符串转成数字的，但是蒟蒻没有读题，没看到 $L,R$ 的数据范围，然后写了个字符串比较大小，其实也不是很难，不失为一种不错的思路（就算 $L,R$ 的数字很大也适用）。

首先，你读入的这个数字不能有前导零。所以是不是判断一下字符串的第一项是不是零就可以呢？

当然不是，这样你会 WA 掉。因为字符串有可能本身就是 $0$。你还要特判一下。

这个数字还要在六十四位整数内？我们仔细观察，发现了 $0\le L,R\le10^9$ 这一串，那就直接判断字符串长度是否大于 $9$ 就可以了。因为 $10^9$ 比 $2^{63}-1$ 小，所以判断 $10^9$ 就连带着判断了第二个条件。

接下来就是喜闻乐见的字符串数字比大小了。可以写个函数，如果两个数位数不一样，比较位数就可以了。如果两个数位数相同，那么从高位到低位一个一个数位比较。如果第一个数的某个数位大于第二个数，那么第一个数一定大于第二个数。同理，如果第一个数的某个数位小于第二个数，那么第一个数一定小于第二个数。

这样比较出来，就可以完美 AC 啦！

### AC 代码

```cpp
#include<iostream>
using namespace std;
string s,l,r;
bool check(string a,string b){//这个函数是判断 a 是否小于等于 b。
	int la=a.size(),lb=b.size();
	if(la<lb)return 1;
	for(int i=0;i<la;++i){
		if(a[i]<b[i])return 1;//小于的情况
		if(a[i]>b[i])return 0;//大于的情况
	}
	return 1;//因为你判断的是小于等于所以两个数相等应当返回 1
}
int main(){
	cin>>s>>l>>r;
	int ls=s.size(),ll=l.size(),lr=r.size();
	if(s!="0"&&s[0]=='0'||ls>9){//不合法的情况
		cout<<"No";return 0;
	}
	if(ls>lr&&ls<ll){//位数超出区间限制的情况
		cout<<"No";
	}
	else{
		if(check(l,s)&&check(s,r)){//如果 s 在 [l,r] 区间内，输出 Yes
			cout<<"Yes";
		}
		else cout<<"No";//否则输出 No
	}
	return 0;
}
```




---

## 作者：tbdsh (赞：0)

# 题意
[题目传送门](/problem/at_past202107_c)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-past202107-c)

输入一个字符串 $S(1\le|S|\le100)$ 和两个正整数 $L,R(1\le L,R\le10^9)$，判断一下条件是否都成立。都成立输出 `Yes` 否则输出 `No`：

>1.$S$ 无多余的前导 $0$，并且在 $64$ 位整型范围内；
>
>2.保证 $L\le S\le R$（这里 $S$ 指十进制数）。

# 分析
本题将对每个判断条件单独分析。
### $S$ 无前导 $0$
直接判断 $S_1$ 是否为 $0$ 并且整个数是否就是 $0$ 即可。
### $S$ 在六十四位整形范围内＆$\le R$
因为 $R\le10^9$ 所以这两个条件可以同时判断。

我们先把 $R$ 用字符串读入。如果 $|S|>|R|$ 就同时说明 $S>R$。

### $L\le S\le R$
此时上面两个条件均已判断完毕，所以可以保证 $S<R$，将 $S$ 和 $R$ 转回整型，判 $L\le S\le R$ 即可。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
string s, r;
int a, l, b;
int main(){
  cin >> s >> l >> r;
  if (s.size() > r.size() || s[0] == '0' && s.size() > 1){
    cout << "No";
    return 0;
  }//这里条件 1 和条件 2 一起判断
  for (int i = 0; i < s.size(); i++){
    a = a * 10 + s[i] - '0';
  }
  for (int i = 0; i < r.size(); i++){
    b = b * 10 + r[i] - '0';
  }//转型
  if (l <= a && a <= b){//条件 3 判断
    cout << "Yes";
  }else {
    cout << "No";
  }
  return 0;
}
```

---

