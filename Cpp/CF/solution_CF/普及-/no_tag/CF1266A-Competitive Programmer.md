# Competitive Programmer

## 题目描述

Bob is a competitive programmer. He wants to become red, and for that he needs a strict training regime. He went to the annual meeting of grandmasters and asked $ n $ of them how much effort they needed to reach red.

"Oh, I just spent $ x_i $ hours solving problems", said the $ i $ -th of them.

Bob wants to train his math skills, so for each answer he wrote down the number of minutes ( $ 60 \cdot x_i $ ), thanked the grandmasters and went home. Bob could write numbers with leading zeroes — for example, if some grandmaster answered that he had spent $ 2 $ hours, Bob could write $ 000120 $ instead of $ 120 $ .

Alice wanted to tease Bob and so she took the numbers Bob wrote down, and for each of them she did one of the following independently:

- rearranged its digits, or
- wrote a random number.

This way, Alice generated $ n $ numbers, denoted $ y_1 $ , ..., $ y_n $ .

For each of the numbers, help Bob determine whether $ y_i $ can be a permutation of a number divisible by $ 60 $ (possibly with leading zeroes).

## 说明/提示

In the first example, there is one rearrangement that yields a number divisible by $ 60 $ , and that is $ 360 $ .

In the second example, there are two solutions. One is $ 060 $ and the second is $ 600 $ .

In the third example, there are $ 6 $ possible rearrangments: $ 025 $ , $ 052 $ , $ 205 $ , $ 250 $ , $ 502 $ , $ 520 $ . None of these numbers is divisible by $ 60 $ .

In the fourth example, there are $ 3 $ rearrangements: $ 228 $ , $ 282 $ , $ 822 $ .

In the fifth example, none of the $ 24 $ rearrangements result in a number divisible by $ 60 $ .

In the sixth example, note that $ 000\dots0 $ is a valid solution.

## 样例 #1

### 输入

```
6
603
006
205
228
1053
0000000000000000000000000000000000000000000000
```

### 输出

```
red
red
cyan
cyan
cyan
red
```

# 题解

## 作者：1qaz234Q (赞：2)

### 题意简述
给出 $n$ 个数，将这 $n$ 个数的数位重新组合后，如果可以被 $60$ 整除，输出 $red$，否则，输出 $cyan$。
### 题目分析
- 因为 $60=2^{2}\times3\times5=3\times20$，所以我们只需要判断重新组合后是否可被 $3$ 和 $20$ 整除即可。
- 如果它能被 $3$ 整除，那么它的数字和能被 $3$ 整除。
- 如果它能被 $20$ 整除，那么它的个位为 $0$ 并且十位为偶数，所以它除了末位的 $0$ 外还会有一个偶数。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        string a;
        bool flag = 0;
        int sum = 0; // 数字和
        int cnt = 0; // 偶数个数
        cin >> a;
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] == '0') // 如果它为数字0
            {
                flag = 1;
            }
            sum += int(a[i] - '0');
            if (int(a[i] - '0') % 2 == 0) // 如果它为偶数
            {
                cnt++;
            }
        }
        cnt--;                               // 去掉末尾的0
        if (flag && sum % 3 == 0 && cnt > 0) // 如果它含数字0并且数字和能被3整除并且除末尾的0外还有另一个偶数
        {
            cout << "red" << endl;
        }
        else
        {
            cout << "cyan" << endl;
        }
    }
}
```


---

## 作者：Marshall001 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1266A)

## 题目大意

输入 $n$ 个数，对于每个数，是否可以将这个数的数位重新组合（可以有前导零），使其可以被 $60$ 整除，若可以，则输出$red$，否则，输出 $cyan$。

## 思路

我们知道，若 $A\div B=0$，那么 $B$ 的所有质因数 $A$ 都有。$60=2\times 2\times 3\times 5$，但质因数 $2$ 重复了，所以我们把因数 $5$ 换成 $5\times 2=10$。

我们要怎么判断 $A$ 重组后是否有 $2,3,10$ 这几个因数呢？

- 如果这个数中有 $0,2,4,6,8$ ，那么这个数重组后就可以被 $2$ 整除。
- 如果这个数各个数位之和是 $3$ 的倍数，那么这个数重组后就可以被 $3$ 整除。
- 如果这个数中有 $0$ 那么这个数重组后就可以被 $10$ 整除。

注意：如果这个数各个数位中只有 $0$ 这一个偶数，那么这个数就不可以被 $60$ 整除。为什么呢？就像 $30$ 这个数，他除以 $10$ 后剩下 $3$，无法被 $2$ 整除了。因为 $0$ 这个数被 $2$ 和 $10$ 共用了。

这样，这个错误代码就出来了。

```cpp
#include <iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		int can2=0,can3=0,can10=0;
		for(int i=0;i<s.size();i++){
			int a=s[i]-'0';
			can3+=a;
			if((a%2==0&&a!=0)||(a==0&&can10==1)){
				can2=1;
			}
			if(a==0){
				can10=1;
			}
		}
		if(can3%3==0){
			can3=1;
		}
		if(can2==1&&can3==1&&can10==1){
			cout<<"red";
		}
		else{
			cout<<"cyan";
		}
		cout<<endl;
	}
	return 0;
}
//注：错误代码。
```

为什么会错呢？试试 $100$ 这个样例吧！你会发现这个代码输出了这个：

```cpp
red
```
为什么呢？应为 $1+0+0=1$，于是 $can3$ 就等于一了。那么我们需要加一个判断。

正确代码如下：

## 代码

```cpp
#include <iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		int can2=0,can3=0,can10=0;
		for(int i=0;i<s.size();i++){
			int a=s[i]-'0';
			can3+=a;
			if((a%2==0&&a!=0)||(a==0&&can10==1)){
				can2=1;
			}
			if(a==0){
				can10=1;
			}
		}
		if(can3%3==0){
			can3=1;
		}
		else{//判断
			can3=0;
		}
		if(can2==1&&can3==1&&can10==1){
			cout<<"red";
		}
		else{
			cout<<"cyan";
		}
		cout<<endl;
	}
	return 0;
}
```
## THE END

---

## 作者：codemap (赞：1)

这道题比较简单,直接说方法:

如果可以通过调整数位使原数被$60$整除,要满足如下条件:

1. 要含$0$(被$10$整除)

2. 除了这个$0$之外还要有一个偶数(被$20$整除)

3. 数字和被$3$整除(被$3$整除)

然后就做完了(~~是不是很简单~~)

上代码
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,i,j,s,t;
	bool f1,f2;//分别判断条件1,条件2
	string a;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a;
		f1=0;
		f2=0;
		s=0;
		t=0;
		//初始化
		for(j=0;j<a.size();j++)
		{
			if(a[j]=='0')//如果有0
			{
				f1=1;//满足条件1
				t++;//要对0计数
				if(t==2)//如果有两个0
					f2=1;//也满足条件2
			}
			if(a[j]=='2'||a[j]=='4'||a[j]=='6'||a[j]=='8')//如果有偶数
				f2=1;//满足条件2
			s+=a[j]-'0';//累加数字和
		}
		if(f1&&f2&&s%3==0)//如果三个条件均满足
			cout<<"red"<<endl;
		else//否则
			cout<<"cyan"<<endl;
	}
	return 0;//结束
}
```
# 请勿抄袭

---

## 作者：可爱的甜甜猫 (赞：1)

这道题我们需要判断 $n$ 个可能有前导 $0$ 的数是否可以通过重新组合数位的方式被 $60$ 整除，可以就输出 $red$，否则输出 $cyan$。显然使用字符串是一个极好的方法。 

我们来分析一下：一个能被 $60$ 整除的数，必然是个整十数（即最后一位为 $0$），并且是 $3$ 的倍数，它的十位（即倒数第二位）必须是偶数。同时满足以上三点的数就能被 $60$ 整除。  

转化到这个问题，我们做的就是要判断这个数的所有数位加起来是否为 $3$ 的倍数（众所周知，一个能被 $3$ 整除的十进制数，它的各个数位之和也能被 $3$ 整除，反之亦然）；判断它是否含有至少一个 $0$；判断它去掉一个 $0$ 之后是否各个数位上还能找出一个偶数。  

可能废话有些多，上代码： 
```cpp
#include<bits/stdc++.h>
using namespace std;
bool f(string s){//使用函数判断，简单明了
	int sum=0;//用于统计各个数位上数字的和
	bool a=0,b=0;
   //a用于判断是否有0，b用于判断除此之外还有没有偶数
	for(int i=0;i<s.size();i++){
		int x=s[i]-'0';//x表示这个数位上的数
		sum+=x;//统计数位上数字之和
		if(x==0&&a==0){
			a=1;
            //如果在此之前没有0则将a的值改为1
		}else if(x%2==0){
			b=1;
            //除此之外有偶数，让b为1
		}
	}
	if(sum%3==0&&a==1&&b==1)return 1;
 //同时满足有0，除掉一个0还有偶数，各个数位的数之和能被三整除则返回1
	return 0;
 //否则返回0
}
int main(){
	int n;
	cin>>n;//我们需要判断n个数
	for(int i=1;i<=n;i++){
		string s;//使用字符串进行判断
		cin>>s;
		if(f(s)==1){
			cout<<"red"<<endl;
		}else{
			cout<<"cyan"<<endl;
		}//输出不解释
	}
	return 0;
}
```


---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1266A)

一道模拟题。

纯模拟肯定不行，考虑优化。$60 = 2^2 \times 3 \times 5$，也就是说我们判断组合后的数字能否被 $2$，$3$，$10$ 整除即可。

如果这个数能被 $2$ 整除，那么原数一定会存在偶数；如果这个数能被 $3$ 整除，那么它的数字和应该也能被 $3$ 整除；如果这个数能被 $10$ 整除，那么原数一定存在 $0$。

值得注意的是，如果原数只出现过一个 $0$，那么该数是不能被 $10$ 和 $2$ 同时整除的。因此，我们还需要判断一下原数是否有除了 $0$ 以外的偶数或者 $2$ 个以上的 $0$。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n;
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; // 不要用 int，否则会出错
        int sum = 0, cnt1 = 0, cnt2 = 0; // sum 是数位和，cnt1 是 0 的个数，cnt2 是除了 0 以外的偶数的个数
        bool flag1 = 0, flag2 = 0, flag3 = 0; // flag1 判断能否被 3 整除，flag2 判断能否被 10 整除，flag3 判断能够被 2 整除
        cin >> s;
        for (int i = 0; i < s.size(); i++) {
            int num = s[i] - '0';
            sum += num;
            if (num == 0) cnt1++;
            else if (num % 2 == 0) cnt2++;
        }
        if (sum % 3 == 0) flag1 = 1;
        if (cnt1) flag2 = 1;
        if (cnt2 or cnt1 > 1) flag3 = 1; // 如果有两个 0 也可以
        if (flag1 and flag2 and flag3) cout << "red\n";
        else cout << "cyan\n";
    }
    return 0;
}
```


---

## 作者：Huhu12346 (赞：0)

#### 题目大意：给出 $n$ 个数,问对于每个数,是否可以将这个数的数位重新组合(可以有前导零),使其可以被 $60$ 整除,若可以则输出 red ,否则,输出 cyan

## 思路： 
 $1$.首先对 $60$ 进行质因数分解，即 $60$ $=$ $2$ $\times$ $2$ $\times$ $3$ $\times$ $5$
 
 $2$.判断是否有 $0$ ,这里提供一种更简单的方法，就是先判断 $3$ 的倍数 ，即如下代码：
 ```cpp
    char a[10005];
    cin>>a;
    int s=strlen(a),cnt=0;
    for(int i=0;i<s;i++) 
	{
		cnt+=a[i]-48;//求数字根
	} 
    if(cnt%3!=0)
	{
        cout<<"cyan\n";
        continue;
    }
```
$\rightarrow$ 意思是如果它不能被 $3$ 整除，就肯定不能被 $60$ 整除。

$3$.紧接着我们再判断 $10$ 和 $2$ ：

```cpp
if(kss(a,"00"))
{
    cout<<"red\n";
    continue;
}
else if(kss(a,"0")
{
    if(kss(a,"2")||kss(a,"4")||kss(a,"6")||kss(a,"8")){
        cout<<"red\n";
        continue;
    }
	else
	{
        cout<<"cyan\n";
        continue;
    }
}
else
{
    cout<<"cyan\n";
    continue;
}
```
就行了，附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    char a[50005];
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a;
        int s=strlen(a),cnt=0;
        for(int i=0;i<s;i++)
	{
		cnt+=a[i]-48;
	}
        if(cnt%3!=0)
	{
            cout<<"cyan\n";
            continue;
        }
        if(kss(a,"00"))
	{
            cout<<"red\n";
            continue;
        }
	else if(kss(a,"0"))
	{
            if(kss(a,"2")||kss(a,"4")||kss(a,"6")||kss(a,"8"))
	    {
                cout<<"red\n";
                continue;
            }
	    else
	    {
                cout<<"cyan\n";
                continue;
            }
        }
		else
		{
            		cout<<"cyan\n";
            		continue;
        	}
    }
}
```



---

## 作者：Sky_exe (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1266A)

### 思路1：暴力枚举

枚举重新组合的所有可能性，判断其中是否有一个是 $60$ 的倍数。

~~(然后就TLE了~~。



------------


### 思路2：分解因数

想要使 $A\bmod B = 0$ 那么 $A$ 就必须是 $B$ 所有因子的倍数。

这题也不例外： $60 = 2\times2\times3\times5 $。

其中 $2$ 和 $5$ 可以相乘得 $10$。

于是原题就变成了使这个数能被 $2$ $3$ $10$ 整除。

其中每个数字都刚好有整除的规律：

- $2$ 的规律：

只要这个数中有一位是偶数即可。

- $3$ 的规律

只要这个数本身能被 $3$ 整除，即各个位置之和能被 $3$ 整除，那么无论它变成什么样子都能被 $3$ 整除。

所以累加一下各个数字之和即可。

- $10$ 的规律

有一个 $0$。

于是就有了这份代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int num;
int sum0;
int sum3;
bool check2,check3,check10;
void init()//初始化 
{
	check2 = false;
	check3 = false;
	check10 = false;
	sum0 = 0;
	sum3 = 0;
}
int main()
{
	int n;//多组数据 
	cin >> n;
	while(n--)
	{
		init();
		cin>>s;
		for(int i=0;i<s.size();i++)
		{
			num = s[i]-'0';//将字符串转为数字 
			if(num % 2 == 0)
			{
				check2 = 1;
			}
			if(num == 0)
			{
				check10 = 1;
				check2 = 1;
			}
			sum3+=num;
		}
		if(sum3 %3 == 0)
		{
			check3 = 1;
		}
		if(check10 && check2 && check3)
		{
			cout<<"red"<<endl;
		}
		else
		{
			cout<<"cyan"<<endl;
		}
	}
}
 
```
结果样例都没过……

问题出现在 $1053$ 这个数。

$0$ 既可以被 $2$ 整除，也能被 $10$ 整除。

但是我们要的是在除过 $2$ 后又能被 $10$ 整除，只有一个 $0$ 后除 $10$ 就不能满足是偶数了。

所以如果只有 $0$ 这一个偶数且只有一个 $0$ 就不满足条件。

改进后的 AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int num;
int sum0;
int sum3;
bool check2,check3,check10;
void init()
{
	check2 = false;
	check3 = false;
	check10 = false;
	sum0 = 0;
	sum3 = 0;
}
int main()
{
	int n;
	cin >> n;
	while(n--)
	{
		init();
		cin>>s;
		for(int i=0;i<s.size();i++)
		{
			num = s[i]-'0';
			if((num % 2 == 0 && num != 0) || (num == 0 && check10))//注意此处要么这个数是非0偶数，或者这个数中有不止一个0，才行
			{
				check2 = 1;
			}
			if(num == 0)
			{
				check10 = 1;
			}
			sum3+=num;
		}
		if(sum3 %3 == 0)
		{
			check3 = 1;
		}
		if(check10 && check2 && check3)
		{
			cout<<"red"<<endl;
		}
		else
		{
			cout<<"cyan"<<endl;
		}
	}
}
 
```


---

## 作者：Together_ (赞：0)

## 题目大意：

给出 $n$ 个数，把每个数的所有数字重新排列后，能否使其能被 $60$ 整除，能就输出 $\mathtt{red}$，否则输出 $\mathtt{cyan}$。

## 思路：

把 $60$ 分解质因数，$60=2^2×3×5$，为了方便，我们可以把这个式子转化成 $60=2×3×10$。

**能被 $60$ 整除，则必能被 $2$、$3$、$10$ 整除。**

- #### 如何判断能否被 $2$ 整除？

遍历一遍这个数的各个数位，只要有 $2$、$4$、$6$、$8$ 中任意一个，就说明这个数能被 $2$ 整除。（注意：$0$ 是不行的，因为 $0$ 在被 $10$ 整除是已经用过了，**除非有 $2$ 个 $0$**）

- #### 如何判断能否被 $3$ 整除？

将这个数的各个数位上的数字累加，判断这个和是否是 $3$ 的倍数。

- #### 如何判断能否被 $10$ 整除？

遍历一遍这个数的各个数位，只要有 $0$，就说明这个数是 $10$ 的倍数

**小技巧**：为了方便计算，我们可以将这个数用字符串形式输入。

## 代码：

```cpp
#include <iostream>

using namespace std;

string s;
int if_3 = 0, if_2 = 0, if_10 = 0;

int main(){
    int n;
    cin>>n;
    while(n--){
        cin>>s;
		if_3 = if_2 = if_10 = 0;
		for(int i=0; i<s.size(); i++){
		    if_3 += (s[i]-'0');
		    if((s[i]-'0')%2 == 0 && (if_10 && s[i]=='0' || s[i] != '0')) if_2 = 1;
		    if(s[i] == '0') if_10 = 1;
		}
		if(if_3%3 == 0 && if_2 && if_10)
			cout<<"red\n";
		else cout<<"cyan\n";
    }
    return 0;
}
```



---

## 作者：CEFqwq (赞：0)

这是一道典型的数学题，主要思想就是因数与倍数。

我们先对 $60$ 进行质因数分解： $60=2 \times 2 \times 3 \times 5$

那么我们要怎么思考呢？很明显，把 $2$ 和 $5$ 相乘，得到 $10$ ，也就是我们只需要判断 $0$ 即可。

然而我们不应该先判断 $0$ ，我们可以先考虑是不是3的倍数。

要求 $3$ 的倍数，也就是要求数字根。

判断代码如下:

```cpp
	char a[10005];
	cin>>a;
	int s=strlen(a),root=0;
	for(int i=0;i<s;i++)root+=a[i]-48;//求数字根
	if(root%3!=0){
		cout<<"cyan\n";
		continue;
	}
```
也就是如果不能被 $3$ 整除，就不能被 $60$ 整除。

接下来，我们判断 $10$ 和 $2$ 。

```cpp
if(strstr(a,"00")){//能被300整除就能被60整除
	cout<<"red\n";
	continue;
}else if(strstr(a,"0"){//能被10整除
	if(strstr(a,"2")||strstr(a,"4")||strstr(a,"6")||strstr(a,"8")){//能被2整除
		cout<<"red\n";
		continue;
	}else{
		cout<<"cyan\n";
		continue;
	}
}else{
	cout<<"cyan\n";
	continue;
}
```
这样就完成了判断。

附上完整代码：

```cpp
#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		char a[10005];
		cin>>a;
		int s=strlen(a),root=0;
		for(int i=0;i<s;i++)root+=a[i]-48;
		if(root%3!=0){
			cout<<"cyan\n";
			continue;
		}
		if(strstr(a,"00")){
			cout<<"red\n";
			continue;
		}else if(strstr(a,"0")){
			if(strstr(a,"2")||strstr(a,"4")||strstr(a,"6")||strstr(a,"8")){
				cout<<"red\n";
				continue;
			}else{
				cout<<"cyan\n";
				continue;
			}
		}else{
			cout<<"cyan\n";
			continue;
		}
	}
}
```

---

## 作者：_ouhsnaijgnat_ (赞：0)

这道题其实还是挺水的。

## 题目大意

这道题意思是给你 $n$ 个数，让你把他们重新组合，能否使他们被 $60$ 整除，能就输出 $red$，否则再输出 $cyan$。

## 思路

我们可以把 $60$ 分解质因数，$60=2^2\times3\times5$，再把这个式子变化一下。$60=2\times3\times10$,这样就很好判断。

能被 $2$ 整除的数末尾都是 $0,2,4,6,8$。

而能被 $3$ 整除的数各位之和能被 $3$ 整除。

而能被 $10$ 整除的数就更简单了，看他有没有 $0$ 就行。

注意：如果有个 $0$ 已经被 $10$ 算过了，那么 $2$ 就不能再算。

无注释版代码奉上。

## 代码

```cpp
#include <iostream>
using namespace std;
string str;
int s3,s4,s10;
int pd(string s){
	s3=s4=s10=0;
	for(int i=0;i<s.size();i++){
		s3+=(s[i]-'0');
		if((s[i]-'0')%2==0&&(s10&&s[i]=='0'||s[i]!='0'))s4=1;
		if(s[i]=='0')s10=1;
	}
	if(s3%3==0&&s4&&s10){
		cout<<"red\n";
	}else cout<<"cyan\n";
}
int main(){
	int n;
	cin>>n;
	while(n--){
		cin>>str;
		pd(str);
	}
	return 0;
}
```


---

