# Bill Total Value

## 题目描述

Vasily exited from a store and now he wants to recheck the total price of all purchases in his bill. The bill is a string in which the names of the purchases and their prices are printed in a row without any spaces. Check has the format " $ name_{1}price_{1}name_{2}price_{2}...name_{n}price_{n} $ ", where $ name_{i} $ (name of the $ i $ -th purchase) is a non-empty string of length not more than $ 10 $ , consisting of lowercase English letters, and $ price_{i} $ (the price of the $ i $ -th purchase) is a non-empty string, consisting of digits and dots (decimal points). It is possible that purchases with equal names have different prices.

The price of each purchase is written in the following format. If the price is an integer number of dollars then cents are not written.

Otherwise, after the number of dollars a dot (decimal point) is written followed by cents in a two-digit format (if number of cents is between $ 1 $ and $ 9 $ inclusively, there is a leading zero).

Also, every three digits (from less significant to the most) in dollars are separated by dot (decimal point). No extra leading zeroes are allowed. The price always starts with a digit and ends with a digit.

For example:

- "234", "1.544", "149.431.10", "0.99" and "123.05" are valid prices,
- ".333", "3.33.11", "12.00", ".33", "0.1234" and "1.2" are not valid.

Write a program that will find the total price of all purchases in the given bill.

## 样例 #1

### 输入

```
chipsy48.32televizor12.390
```

### 输出

```
12.438.32
```

## 样例 #2

### 输入

```
a1b2c3.38
```

### 输出

```
6.38
```

## 样例 #3

### 输入

```
aa0.01t0.03
```

### 输出

```
0.04
```

# 题解

## 作者：Bai_R_X (赞：1)

## 思路
这一题重点在于小数的判断，而小数的判断又关键在于**最后一个**小数点后数字的数量（因为中间肯定是整数的分割），这样就可以判断它是整数中的分割还是小数与整数的分割。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string S,s;
int i,j;
double ans;
int get(int st,int ed)
{
	int w=1,sum=0;
	for(int i=ed;i>=st;i--)
	{
		if(s[i]=='.')continue;
		sum+=(s[i]-'0')*w;
		w*=10;
	}
	return sum;
}
void write(int x)
{
	string ans;
	int w=0;
	while(x)
	{
		w++;
		ans.push_back(x%10+'0');
		if(w==3)
		{
			ans.push_back('.');
			w=0;
		}
		x/=10;
	}
	reverse(ans.begin(),ans.end());
	for(int i=ans[0]=='.';i<ans.size();i++)cout<<ans[i];
}
signed main()
{
    cin>>S;
    for(i=0;i<S.size();i++)
    {
    	if((!isdigit(S[i]))&&S[i]!='.')
    	{
    		if(i!=S.size()-1&&isdigit(S[i+1]))s.push_back(' ');
    		continue;
		}
		s.push_back(S[i]);
	}
	s.push_back(' ');
	for(i=1;i<s.size();)
	{
		int end;
		for(j=i+1;j<s.size();j++)
		{
			if(s[j]==' ')
			{
				end=j+1;
				break;
			}
		}
		int dot=0,point=-1;
		for(j=i+1;j<end-1;j++)
		{
			if(s[j]=='.')
			{
				dot=end-j-2;
				point=j;
			}
		}
		if(dot==0||dot==3)ans+=get(i,end-2);
		else if(dot==2)ans+=get(i,point-1)+get(point+1,end-2)*0.01;
		i=end;
	}
	write(ans);
	if(int(ans)==0)cout<<"0";
	if((ans-int(ans))*100!=0)
	{
		cout<<".";
		if((ans-int(ans))*100<10)cout<<"0";
		cout<<(ans-int(ans))*100;
	}
    return 0;
}
```

---

## 作者：ZQIN_P (赞：1)

[在我的博客中阅读](https://zqin-blog.netlify.app/2023/08/20/CF727B-Bill-Total-Value-%E9%A2%98%E8%A7%A3/)

[题目传送门](https://www.luogu.com.cn/problem/CF727B)

## 题目大意：
给出一份账单，其中商品名称仅由小写字母构成，每件商品后有一个价格，价格由数字和 ```.``` 构成，其中价格的整数部分为从最低位到最高位三位数字一组，用 ```.``` 隔开；小数部分若有则固定为两位，与整数部分用 ```.``` 分隔，所有商品名称与价格之间无空格。要求求出商品的总价格，并参照每件商品价格的书写方式输出。

## 思路：

### 一.输入：
首先是对账单的输入。因为此题没有存储必要，故我们可以用 ```while``` 循环逐个输入每个字符，并对其进行判断和处理。我们用变量 $pri$ 存储输入的商品价格，用 $ans$ 记录商品的总价格，用 $b$ 存储是否出现过字符 ```.```，用 $w$ 存储目前该价格数字在 ```.``` 后或已输入的位数。输入的字符有三种可能的情况：

#### 1.输入字符为数字。
当输入的字符为数字时，我们需要将其放到当前价格的最后一位，并让此时在 ```.``` 后或输入的位数增加 $1$。代码如下：
```cpp
if('0'<=c&&c<='9'){
	pri*=10;
	pri+=c-'0';
	w++;
}
```

#### 2.输入字符为 ```.```。
当输入的字符为 ```.``` 时，我们要将记录 ```.``` 后数字位数的变量清空，并记录此时数字中已经出现过 ```.``` 了。代码如下：
```cpp
else if(c=='.'){
	w=0;
	b=true;
}
```

#### 3.输入字符为小写字母。
当输入的字符为小写字母时，说明正在输入的是商品的名称。此时我们需要判断有没有商品价格需要处理。如果有，就处理记录好的商品价格，并将其累加到总价格中。

处理时，由于整数部分每三位的分隔符与小数部分同整数部分的分隔符同为 ```.```，故我们需要判断此时数字中是否出现过 ```.```。如果出现过，则要判断 ```.``` 后数字的位数是否为 $2$。若是，则将其除以 $100$ 后加入总价格；若不是，则直接将其加入总价格。如果没有出现过，那么直接将其加入总价格即可。代码如下：
```cpp
else{
	if(w!=0){
		if(b){
			if(w==2) ans+=pri*1.0/100;
			else ans+=pri;
		}
		else ans+=pri;
		b=false;
		pri=0;
		w=0;
	}
}
```

### 二.输出：
输入结束后，我们就要对记录的总价格进行输出。由于数字的整数部分是从最低位到最高位每三位一 ```.``` 分隔，所以需要对数字进行数位分离并倒序输出。此操作与栈的后进先出十分类似，所以我们可以想到利用栈来实现。由于 ```double``` 类型无法进行取模运算，故需要将记录的总价格乘 $100$ 后再进行操作。代码如下：
```cpp
ans1=ans*100;
w=1; //由于小数部分为两位，所以将w赋值为1。
while(ans1>0){
	st.push(char(ans1%10+'0'));
	ans1/=10;
	w++;
	if(w&&ans1&&w%3==0) st.push('.');
}
while(!st.empty()){
	printf("%c",st.top());
	st.pop();
}
```

但是仅有上面的代码只能正确输出有两位小数且整数部分大于 $0$ 的结果，所以我们要对于数字的数位进行判断，如果其只有一位小数，则向栈中加入 ```0.0```；如果只有两位小数，则加入 ```0.```。代码如下：
```cpp
if(ans<0.1){
	st.push('0');
	st.push('.');
	st.push('0');
}
	else if(ans<1){
	st.push('.');
	st.push('0');
}
```

我们还需要在进行入栈操作之前进行对小数部分的去 $0$ 操作，很好实现，但是需要注意的是，必须小数部分两位都为 $0$ 才进行此操作。代码如下：
```cpp
if(ans1%100==0){
	ans1/=100;
	w=0;
}
```

### 三.改进
至此，我们的代码就已经实现完成了。但是在提交时，会出现一个致命的问题：由于 C++ 的特性，$0.83$ 在运算时会按照 $0.82\dot 9$ 来进行计算，所以会在进行 ```double``` 类转化为 ```int``` 类时导致最后一位减 $1$，造成评测无法通过的情况。我们只需要对输入为小写字母时的代码进行一个修改：
```cpp
else{
	if(w==3||!b) ans+=pri*100;
	else ans+=pri;
	b=false;
	pri=0;
	w=0;
}
```

这段代码实际上是将累加时整数部分的最后两位当作小数部分来进行累加，以此来避免上述问题。之后只要将其他部分进行相应的修改即可。完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,ans1;
char c;
int pri,w,num;
bool b=false;
stack<char> st;
int main(){
    char c;
    int w=0;
    while(cin>>c){
        if('0'<=c&&c<='9'){
            pri*=10;
            pri+=c-'0';
            w++;
        }
        else if(c=='.'){
            w=0;
            b=true;
        }
        else{
            if(w==3||!b) ans+=pri*100;
            else ans+=pri;
            b=false;
            pri=0;
            w=0;
        }
    }
    if(pri!=0){
        if(w==3||!b) ans+=pri*100;
        else ans+=pri;
    }
    ans1=ans;
    w=1;
    if(ans1%100==0){
        ans1/=100;
        w=0;
    }
    while(ans1>0){
        st.push(char(ans1%10+'0'));
        ans1/=10;
        w++;
        if(w&&ans1&&w%3==0) st.push('.');
    }
    if(ans<10){
        st.push('0');
        st.push('.');
        st.push('0');
    }
    else if(ans<100){
        st.push('.');
        st.push('0');
    }
    while(!st.empty()){
        printf("%c",st.top());
        st.pop();
    }
    return 0;
}
```

## 总结：
此题的思维难度并不高，但是对编写代码的能力有一定的要求，在写代码的时候也需要注意很多的细节，对想练习代码能力或细心程度的小伙伴们是一个不错的选择。

---

## 作者：ISTP (赞：1)

[更好的阅读体验](https://www.luogu.com.cn/blog/528540/solution-cf727b)

### 题面

[原题面：https://www.luogu.com.cn/problem/CF727B](https://www.luogu.com.cn/problem/CF727B)

题意简述：

给你一行一个字符串，由多组物品名称（只含字母的字符串）和价格组成，中间不含空格。价格的格式为：整数部分从低位起每三位用 ```.``` 间隔，若有小数部分则固定两位小数（与整数部分用 ```.``` 间隔）。求出所有物品的总价。**输出格式与输入的单价格式相同，且若有小数部分则输出两位小数，否则不输出小数部分。**

### 思路

先提取出字符串中的价格，相加得到总价，再按照给定格式（其实就是外国的数字写法，三位一点）输出。

判断含小数点的单价是否有小数，**关键在于它从左数的第一个小数点后有几位。只有两位则这两位是小数，** 否则整个数字是一个整数。

下面用到的 ```isdigit(char)``` 函数是个很方便的判断参数是否为十进制数字字符的函数，包含在头文件 ```ctype.h``` 中。

细节解释见代码注释部分。

### 代码

肯定有比这更简洁的写法，这里仅供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
string bill; //初始的账单字符串
double ans;
double getprice(int);
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> bill;
	int len = bill.size();
	for(int i = len - 1; i >= 0; i --)
		if(isdigit(bill[i])) i = getprice(i); //这里的返回值是 i 跳过当前数字后应该移动到的下标
	int t1 = (int)ans, t2 = 0; //t2提取出倒序整数
	len = 0;
	while(t1) t2 = t2 * 10 + t1 % 10, t1 /= 10, len ++;
	if(!len) cout << 0; //整数部分为 0 时的特判
	while(len){ //按格式输出整数部分
		cout << t2 % 10;
		t2 /= 10, len --;
		if(len && len % 3 == 0) cout << '.';
	}
	int t3 = ((ans - (int)ans) * 1000 + 1) / 10; //提取小数部分
	if(t3 && t3 < 10) cout << ".0" << t3; //输出小数部分，若 t3 只有 1 位则补上中间漏掉的 0
	else if(t3) cout << '.' << t3; //否则正常输出两位，注意都要判断是否有小数部分，没有则不输出
	return 0;
}
double getprice(int x){
	int l = x, r = x;
	while(bill[l - 1] == '.' || isdigit(bill[l - 1])) l --; //找到该价格最左端下标
	double num = 0; //统计该单价
	if(x > 1 && bill[x - 2] == '.') //特判边界及小数
		num += (bill[x - 1] - '0') * 0.1 + (bill[x] - '0') * 0.01, r -= 3;
	for(int i = 0; l <= r; i ++, r --){
		if(bill[r] == '.') r --;
		num += (bill[r] - '0') * pow(10, i); //字符转数字
	}
	ans += num; //价格累加
	return l; //返回下一次统计的起始下标，这里不返回 l - 1 因为在主函数的 for 循环里还要 l --
}
```

### 小结

这题除了处理有点烦没什么难点。至于为什么我会把小数部分转成整数再输出，因为美丽的 C艹 特性。

举个栗子，总价算出来 ```0.3```，实际存储在里面的是 ```0.2999...```。

绝了。

真没了。祝你们顺利切掉这题。

---

## 作者：xuyifei0302 (赞：0)

我们发现只需要统计最后的答案，但美分是两位小数，美元中每三位有一个小数点，而题目是字符串输入，十分麻烦。

所以我们可以先将其变成一个数，记录是否有美分这两位，分开处理。

我们对于每一位，在最后按位拆开。

+ 若这个总价格有美分位，就在前两位进栈后添加小数点，然后每三位添加小数点。

+ 若这个总价没有美分位，只需每三位添加小数点。

模拟即可。

下面是代码环节：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int sum;
stack<char> st;
bool p, tmp;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	int len = s.size();
	s = " " + s;
	int sum1 = 0, num = 0;
	for (int i = 1; i <= len; i ++) {
		if (s[i] >= '0' && s[i] <= '9') {
			sum1 *= 10;
			sum1 += s[i] - '0';
			if (tmp) {
				num ++;
			}
		}
		if (s[i] == '.') {
			tmp = true;
			num = 0;
		}
		if (s[i] >= 'a' && s[i] <= 'z') {
			if (num == 3 || !tmp) {
				sum1 *= 100;
			}
			sum += sum1;
			sum1 = 0;
			if (num == 2) {
				p = true;
			}
			num = 0;
			tmp = false;
		}
	}
	if (num == 3 || !tmp) {
		sum1 *= 100;
	}
	sum += sum1;
	sum1 = 0;
	if (num == 2) {
		p = true;
	}
	num = 0;
	tmp = false;
	int num1 = 0;
	if (sum % 100 == 0 && p) {
		p = false;
	}
	if (p) {
		p = false;
		while (sum) {
			char ch = sum % 10 + '0';
			st.push(ch);
			num ++;
			if (num == 2 && !p) {
				num = 0;
				st.push('.');
				p = true;
			} else if (p && num == 3) {
				num = 0;
				st.push('.');
			}
			sum /= 10;
			num1 ++;
		}
		if (num1 == 1 && !p) {
			st.push('0');
			st.push('.');
			st.push('0');
		} else if (num1 == 2 && !p) {
			st.push('.');
			st.push('0');
		} else if (num1 == 2 && p) {
			st.push('0');
		}
		if (st.top() == '.') {
			st.pop();
		}
		while (!st.empty()) {
			cout << st.top();
			st.pop();
		}
	} else {
		sum /= 100;
		while (sum) {
			char ch = sum % 10 + '0';
			st.push(ch);
			num ++;
			if (num == 3) {
				num = 0;
				st.push('.');
			}
			sum /= 10;
		}
		if (st.top() == '.') {
			st.pop();
		}
		while (!st.empty()) {
			cout << st.top();
			st.pop();
		}
	}
	return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

一道字符串模拟题

总体分为两部分：读入和输出

## 输入

首先读入整个字符串，因为没有空格，所以可以 `scanf`

```cpp
scanf("%s",s);
```

依次扫描整个字符串

字母只起到分隔数字的作用，所以如果遇到非数字，直接跳过

```cpp
if(s[i]<'0'||s[i]>'9') continue;
```

否则开始累计这个数，先把它当作整数来计算

可以参考快读的计算方式，每一次令 $x=10x+ch-'0'$

```cpp
int x=0;
while(i<len && ((s[i]>='0'&&s[i]<='9') || s[i]=='.'))
{
  x=(x<<3)+(x<<1)+(s[i]^'0'); //等价于 x=x*10+s[i]-'0'; 
  i++;
}
```

再计数的时候标记是否有 `.` 符号，并统计最后一个 `.` 后数字的数量

```cpp
int x=0,cnt=0; bool have_dot=false;
while(i<len && ((s[i]>='0'&&s[i]<='9') || s[i]=='.'))
{
  if(s[i]=='.')
  {
    have_dot=true;
    cnt=0,i++;
    continue;
  }
  x=(x<<3)+(x<<1)+(s[i]^'0'); //等价于 x=x*10+s[i]-'0'; 
  cnt++,i++;
}
```

然后判断这个数是整数还是分数，如果有 `.` 并且其数量为 $2$，代表最后为 `.xx` 的形式，那么这个数为小数，需要 `/=100.0` 后累加，否则直接作为整数累加到答案内。

```cpp
if(have_dot&&cnt==2) ans+=(double)x/100.0;
else ans+=x;
```

## 输出

首先分离整数和小数部分，并把小数部分存为整数（注意四舍五入）

```cpp
int inter=(int)ans;
int dec=(ans-inter+0.005)*100.0;
```

把整数部分的每一数位存到一个数组里面（此时存入的数位是倒序的）

```cpp
while(inter)
{
	num[++numcnt]=inter%10;
	inter/=10;
}
```

倒序输出整数部分，如果 $(i-1) \bmod 3=0$，此时应该输出一个 `.`（注意避免最后多一个 `.`，需要特判）

```cpp
for(int i=numcnt;i>=1;i--)
{
  printf("%d",num[i]);
  if((i-1)%3==0 && i!=1) putchar('.');
}
```

若没有整数部分，即 $ans<1$，这时需要补充一个 $0$（在上面补充应该也行）

```cpp
if(ans<1) putchar('0');
```

如果有小数部分则输出小数部分

如果小数部分不到 $0.1$，还需在前面补一个 $0$

```cpp
if(dec>=10) printf(".%d\n",dec);
else if(dec) printf(".0%d\n",dec);
```

## 完整 AC 代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
char s[1005];
int main()
{
	scanf("%s",s);
	int len=strlen(s);
	double ans=0;
	for(int i=0;i<len;i++)
	{
		if(s[i]<'0'||s[i]>'9') continue;
		int x=0,cnt=0; bool have_dot=false;
		while(i<len && ((s[i]>='0'&&s[i]<='9') || s[i]=='.'))
		{
			if(s[i]=='.')
			{
				have_dot=true;
				cnt=0,i++;
				continue;
			}
			x=(x<<3)+(x<<1)+(s[i]^'0'); //等价于 x=x*10+s[i]-'0'; 
			cnt++,i++;
		}
		if(have_dot&&cnt==2) ans+=(double)x/100.0;
		else ans+=x;
	}
	int inter=(int)ans;
	int dec=(ans-inter+0.005)*100.0;
	int num[15],numcnt=0;
	while(inter)
	{
		num[++numcnt]=inter%10;
		inter/=10;
	}
	for(int i=numcnt;i>=1;i--)
	{
		printf("%d",num[i]);
		if((i-1)%3==0 && i!=1) putchar('.');
	}
	if(ans<1) putchar('0');
	if(dec>=10) printf(".%d\n",dec);
	else if(dec) printf(".0%d\n",dec);
	return 0;
}
```

---

## 作者：wangziwenhk (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF727B)
[通过提交](https://www.luogu.com.cn/record/138293826)
这是一道非常好的字符串处理题目。
我们将整个题目分成**三部分**来看：

1. 提取数字
2. 计算数字
3. 输出数字

## 提取数字

首先将每个商品的名称**和价钱提取**出来。
例如：

```c++
chipsy48.32televizor12.390
```

可以分成：

```c++
chipsy 1.148.32
televizor 12.390
```

因为有些数字的**整数部分**被`.`分割了。
所以我们可以**再拆分**,得到：

```c++
chipsy 1 148 32
televizor 12 390
```

得到代码：

```c++
vector<string> vec(1);//string方便存
for(auto j:i) {
    if(j=='.')vec.push_back("");//分割符遇到就说明要开新的片段
    else vec.back()+=j;//复制片段
    
}
```

## 计算数字

根据题目可以得到
数字的小数部分固定为 **$2$ 位**,而整数部分 **$3$ 位**为一组。
所以我们可以先处理**小数部分**：

```c++
if(vec.back().size()==2) {
    double temp=atoi(vec.back().c_str());
    sum+=temp/100.0;//因为小数部分是两位的,所以要将小数点左移两位
    vec.erase(vec.end()-1);//删除小数部分,防止后面多出一部分
}
```

然后在处理**整数部分**，只需要一个**权重** k 就可以了（进制转换？）

```c++
double k=1;
double temp=0;
for(int j=vec.size()-1;j>=0;j--) {
    temp +=atoi(vec[j].c_str())*k;
    k*=1000;
}
sum+=temp;
```

## 输出数字

这个部分有点烦,我的 Ans 的 `reserve()` 方法
和 `string(s.cbegin(),s.cend())` 都没用（可能编译器问题）

首先，我们先把 sum 给**转换成 string 类型**，然后在进行**分段处理**。
当然，**直接转换**是**不行**的，转换结果有小数会很难处理。
所以我们先处理整数部分：

```c++
string temp=to_string(static_cast<long long>(sum));//转换
int k=0;//计数器，当存入片段内的数字到达三个就输出截断符
string Ans="";//存储整数部分
for(int i=temp.size()-1;i>=0;i--){
    k++;//计数器增加
    if(k>3){//片段内数字到达3个
        Ans+='.';//添加标记符
        k=1;//计数器清零
    }
    Ans+=temp[i];//片段插入
}
```

当然，用这种方法写出来的 Ans 是**不能够直接输出**的，

由于我们从后往前遍历，所以 Ans 中存的也是**反转的结果**，

所以我们需要先将 Ans **反转再输出**（直接反转输出也可以）：

````c++
for(int i=Ans.size()-1;i>=0;i--)cout<<Ans[i];
````

最后，我们就可以处理**小数部分**了：

```c++
if(sum-static_cast<long long>(sum)!=0) {//判断sum中是否还有小数部分没有处理
    Ans=to_string(sum-static_cast<long long>(sum));//转换
    Ans.erase(Ans.begin());//删除前导0
    cout << Ans[0] << Ans[1] << Ans[2];//由于小数部分固定两位，所以直接输出.XX
}
```

此处附完整代码：

```c++
#include <bits/stdc++.h>

using namespace std;


int main() {
    //输入
    string s;
    cin >> s;

    //拆分
    vector<string> name(1),num;
    bool flag=true;
    for(int i=0;i<s.size();i++) {
        if(s[i]>='0'&&s[i]<='9' ||s[i]=='.'){
            if(!flag)num.push_back(string());
            flag = true;
            num.back().push_back(s[i]);
        }
        else{
            if(flag)name.push_back(string());
            flag =false;
            name.back().push_back(s[i]);
        }
    }
    //计算
    double sum=0;
    for(auto i:num) {
        vector<string> vec(1);
        for(auto j:i) {
            if(j=='.')vec.push_back("");
            else {
                vec.back()+=j;
            }
        }
        if(vec.back().size()==2) {
            double temp=atoi(vec.back().c_str());
            sum+=temp/100.0;
            vec.erase(vec.end()-1);
        }
        double k=1;
        double temp=0;
        for(int j=vec.size()-1;j>=0;j--) {
            temp +=atoi(vec[j].c_str())*k;
            k*=1000;
        }
        sum+=temp;
    }
    //输出
    string temp=to_string(static_cast<long long>(sum));
    int k=0;
    string Ans="";
    for(int i=temp.size()-1;i>=0;i--){
        k++;
        if(k>3){
            Ans+='.';
            k=1;
        }
        Ans+=temp[i];
    }
    for(int i=Ans.size()-1;i>=0;i--)cout<<Ans[i];
    if(sum-static_cast<long long>(sum)!=0) {
        Ans=to_string(sum-static_cast<long long>(sum));
        Ans.erase(Ans.begin());
        cout << Ans[0] << Ans[1] << Ans[2];
    }
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

一道大模拟。题目很容易理解，考察代码实现能力。

题目很简单，求出一堆价格的和。但是数字出现了分隔符，还有小数，非常烦人。所以我们可以考虑将整型变量扩大 $100$ 倍，用于存储小数情况。

我们发现价格有两位小数和分隔符，于是，我们先判断属于哪种类型。定义两个变量 $x,y$，记录分隔符最后出现的位置，和小数点最后出现的位置，如果相差得 $2$，说明是小数点。否则就是分隔符。按照快读的方式，将每个数字读入，记录在 $ans$ 中。

```
cin>>s;
  for(int i=0;i<s.size();i++)
  {
  	if(s[i]>='0'&&s[i]<='9') sum=sum*10+s[i]-48,x=i;//快读&记录数字
  	else if(s[i]=='.') y=i;//记录分隔符位置
  	if(s[i]>='a'&&s[i]<='z'||i==s.size()-1)
	{
	  if(y+2==x) ans+=sum;//相差得2，是小数点
	  else ans+=sum*100;//注意扩大100倍表示整数
	  sum=0;
	}
  }
```
然后就是输出阶段。这里我们分成整数和小数来做。先搞个函数，用于分割整数和小数。
```
string sto(int x)
{
  string s="";
  if(x%100)
  {
  	t+=char(x/10%10+48);
    t+=char(x%10+48);
  }//记录小数部分
  x/=100;
  while(x)
  {
  	s+=char(x%10+48);
  	x/=10;
  }//记录整数部分
  if(s=="") s="0";//特判ans=0，防止没有整数部分
  reverse(s.begin(),s.end());//由于是从个位开始，翻转还原。
  return s;
}
```

然后开始输出分隔符。倒序输出比较烦人，我们利用 ```s.size()``` 函数判断是否需要分隔符。当满足长度减去当前位置的值可以被 $3$ 整除时，说明该放分隔符了。注意，最后一个数字不用放。

最后输出小数部分。一道小清新模拟题就做好了。

```
for(int i=0;i<s.size();i++)
  {
  	cout<<s[i];
  	if((s.size()-i-1)%3==0&&i<s.size()-1) cout<<".";
  }
if(ans%100) cout<<"."<<t;
```

---

