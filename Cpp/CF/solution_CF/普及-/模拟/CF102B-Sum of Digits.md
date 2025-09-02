# Sum of Digits

## 题目描述

Having watched the last Harry Potter film, little Gerald also decided to practice magic. He found in his father's magical book a spell that turns any number in the sum of its digits. At the moment Gerald learned that, he came across a number $ n $ . How many times can Gerald put a spell on it until the number becomes one-digit?

## 说明/提示

In the first sample the number already is one-digit — Herald can't cast a spell.

The second test contains number $ 10 $ . After one casting of a spell it becomes $ 1 $ , and here the process is completed. Thus, Gerald can only cast the spell once.

The third test contains number $ 991 $ . As one casts a spell the following transformations take place: $ 991→19→10→1 $ . After three transformations the number becomes one-digit.

## 样例 #1

### 输入

```
0
```

### 输出

```
0
```

## 样例 #2

### 输入

```
10
```

### 输出

```
1
```

## 样例 #3

### 输入

```
991
```

### 输出

```
3
```

# 题解

## 作者：wpj20241021005 (赞：1)

我第一眼看这道题，并没有在意这道题的数据范围，用int类型的交上去，第7点就WA了，然后我就很奇怪，看了一眼原文（译文没有给数据范围），发现这一道题的数据是非常大，unsigned long long 都不行，于是，我就想到了C++的一个非常棒的东西——STL库（C++党的福利）。STL库里有个叫做String的函数，可以给我们省去很多麻烦。

思路就是先读入这个数，然后呢就用一个计数器来记录它第一次变形后的大小，而这个数最大也完全不可能超过long long 的范围（最大为9乘100000 ），其实用int应该也可以，接下来就是常规操作了。**注意：最后结果要加一！！！**

下面是我的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long ans=1,cnt;
string n;//字符串
int change(long long num){ //各数位相加函数
	long long sum=0;
	while(num>0){
		sum+=num%10;
		num=num/10;
	}
	return sum; //返回下一个数
}
int main(){
	cin>>n;
	if(n.size()==1){ //特判当读入为10以内的数
		cout<<0<<endl;
		return 0;// 撒花
	}
	for(int i=0;i<n.size();i++)//进行第一次转换
		cnt=cnt+n[i]-'0';
	while(cnt>=10){//进入循环
		ans++;//答案+1
		cnt=change(cnt);//转换
	}
	cout<<ans<<endl;//输出答案，撒花
}
```


---

## 作者：Bronya18C (赞：1)

# 本题为何会成为绿题，是人性的……，也许是愚人节题吧！（~~话说今年chen_zhe也太毒瘤了~~）
---
## 本题数据并不大，只是要一个一个模拟，第一个最大是10^100000，要用字符串，后面可以用int/long long(第二次最大是99999*9)，最后答案加上1即可。
## 可是，如果它原本是一位数，输出会是1，所以要特判。
```
#include<bits/stdc++.h>

using namespace std;
long long N,n,ans=1,sum; 
char k;
int main()
{
    while(cin>>k)
    {
        N+=k-'0';
        sum++;
    }
    if(sum==1)
    {
        cout<<"0"<<endl;
        return 0;
    }//特判
    while(N>=10)
    {
    n=0; 
    for(int i=N;i>0;i/=10)
    {
        n+=i%10;
    }
    N=n;
    ans++;
    }
    cout<<ans<<endl;
    return 0;
} 
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个数 $n$，每次操作可以将 $n$ 变成 $n$ 各位数之和。问你几次操作之后可以将 $n$ 变为一位数。

**数据范围：$1\leqslant n\leqslant 10^{10^5}$。**
## Solution
一看这么大个数字我们就不能够用 `int`，`long long` 之类的类型读入了，只能够用字符串、字符数组。然后考虑将所有的数位暴力拆开求和，然后再代入求出操作后的数字，直到变成一位数为止。
## Code
请注意下面的代码需要特判是否本来就是一位数。

```cpp
const int N = 1e5 + 7;
int digit[N], tmp[N], tmp2[N], sum, ans;

inline int td(char x) {return x - '0';}

int main() {
	crstr(s, n);
	if(n == 1) return printf("0"), 0;
	F(i, 0, n - 1) digit[i + 1] = td(s[i]);
	while(1) {
		memset(tmp, 0, sizeof(tmp));
		memset(tmp2, 0, sizeof(tmp2));
		sum = 0;	//Clear all!!! 
		F(i, 1, n) sum += digit[i];
		while(sum) {
			tmp[++tmp[0]] = sum % 10;
			sum /= 10;
		}
		R(i, tmp[0], 1) tmp2[i] = tmp[tmp[0] - i + 1];
		memset(digit, 0, sizeof(digit));
		F(i, 1, tmp[0]) digit[i] = tmp2[i];
		n = tmp[0], ans++;
		if(n == 1) break;
	}
	return write(ans), 0;
} 
```

---

## 作者：simonG (赞：0)

### 前言
一个数n，注意n的数据范围$0<=n<=10000000000000...00000$
### 详解
>* 1,输入n，n很大，所以我们用字符辅助输入，再直接求出它的数位和
>* 2,直接用字符串处理,再求数位之和，继续递推。然后把数字之和用$sprintf$打印给自己更新
>* 3,输出
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[110000];
int ans;
int main() {
	cin>>s;
	int len=strlen(s);
	while(len!=1){
		int plus=0;
		for(int i=0;i<=len-1;i++)
			plus+=s[i]-'0';
		sprintf(s,"%d",plus);
		len=strlen(s);
		ans++;
	}
	cout<<ans;
	return 0;
}
```

### 后记
STL多用

---

## 作者：Insouciant21 (赞：0)

依据题意直接模拟即可

需要注意数据范围 $0\leq n\leq10^{100000}$ 

可以先使用 `string` 读入然后计算一次数位和。

可得到的最大值为 $9\times99999=899991<2^{31}-1$，此时使用 `int` 继续处理即可。

由于我们已经使用 `string` 计算了一次数位和，所以次数原本就为 $1$ ，但是当原先 $n<10$ 时，这一次是多余的，故须去除直接输出 $0$ 。

AC 代码
```
#include <bits/stdc++.h>

using namespace std;

string p;

int s(int n) { // 计算数位和
    int res = 0;
    while (n) {
        res += n % 10;
        n /= 10;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> p;
    int sum = 0;
    for (int i = 0; i < p.length(); i++)
        sum += (p[i] - '0');
    int cnt = 0;
    if (p.length() > 1) // 大于 10 为 1
        cnt = 1;
    while (sum >= 10) {
        sum = s(sum);
        cnt++;
    }
    cout << cnt << endl;
    return 0;
}
```

---

## 作者：Autism_ever (赞：0)

#### 此题就一直变，没别的，继续变
一一一一一一一一一一一一一一一一分界线

### 上代码，啊，记得开long long，否则会爆

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
unsigned long long ans=1,cnt;//不开ULL见祖宗 
string s;//字符串
int con(long long num)//各数位相加函数
{ 
	long long sum=0;
	while(num!=0)//如果不为0，继续 
	{
		sum+=num%10;//记录余数 
		num=num/10;//记录商 
	}
	return sum; //返回下一个数，继续 ，加油，奥利给 
}
int main()
{
	cin>>s;
	if(s.size()==1)//个位数输出0，不管 
	{
		cout<<0<<endl;
		return 0;//结束，return 0; 
	}
	for(int i=0;i<s.size();i++)//进行第一次转换
	{
		cnt=cnt+s[i]-'0';//将是s[i]转化为整数，好相加，字符串不可以直接加 
	}
	while(cnt>=10)//进入循环
	{
		ans++;//答案+1
		cnt=con(cnt);//转换开始，重点来了 
	}
	cout<<ans<<endl;//输出答案
}
```


---

## 作者：AB_IN (赞：0)

## ~~python可太香了~~
写一个函数把字符串转化成各个数位的数字之和。
套进一个while循环就行了。

```python
def f(x):
    cnt=0
    for i in x:
        cnt+=int(i)
    return cnt
while True:
    try:
        s=input().strip();num=0
        while int(s)>=10:
            s=f(str(s))
            num+=1
        print(num)
    except:
        break

```


---

## 作者：Cult_style (赞：0)

这道题不能不用字符串，不过就算它是最大的99999（100000的各各位数之和没99999的各各位数之和大）操作完一次之后也是45所以我们先用一个变量sum来存着已经完成了一次操作后的数，然后再一个一个数字地拆，拆出来的数用k来表示,再让sum=k,拿样例991来说：

- 完成第一次操作之后，sum=19,k=10
- 完成第二次操作之后，sum=10，k=1
- 完成第三次操作之后，sum=1,k=1

不过还有一点，如果字符的长度已经一开始就是1的话，就要特判，直接输出零，不然会输出1
```
#include<bits/stdc++.h>
using namespace std;
int ans;
char s[100005];
int sum;
void c(int x){
    while(x>0){
	sum+=x%10;
	x/=10;
        //拆数的过程
    }
}
int main(){
    scanf("%s",s);
    //输入一串字符
    int n=strlen(s);
    //求出字符的长度
    if(n==1){
	printf("%d",0);
	return 0;
    }
    //如果长度为一，也就是说一开始就是一位数，就输出0，然后直接结束
    for(int i=0;i<n;i++)
	sum+=s[i]-'0';
    //这是执行的第一次操作，要把字符强制转换为数字
    ans=1;
    //表示已经执行过了一次操作
    while(sum>9){
    //如果它还没被拆成一位数，就一指禅
	ans++;
    	//没拆一次执行的次数加1
	int k=sum;
    	//拆数的准备工作，先让k=sum，准备拆数
	sum=0;
    	//让sum=0,在c函数中会让sum有新的值
	c(k);
    	//拆数，并给sum赋值
    }
    printf("%d",ans);
    //输出
	
    return 0;
} 
```

---

## 作者：AlwaysForward (赞：0)

# 呃……这可能是我做过的最简单的蓝题了
#### ~~我不想说它shui，不能毁了一道超难的蓝题~~

思路大概这样：一个个模拟，因为是10^10000，用int会爆，得用字符串，其中有两个要特判（代码已标注），不然都输出的2，会WA。
```
#include<bits/stdc++.h>
using namespace std;
int sb(int n){
	int top=0,h=n;
	for(int i=1;;i++){
		top+=h%10;
		h/=10;
		if(h==0)break;
	}
	return top;
}
int main(){
    string s;
    cin>>s;
    int i,n=s.size(),top=0;
    for(i=0;i<n;i++){
    	top+=int(s[i])-48;
	}
	if(n==1){
		cout<<"0";//特判1
		return 0;
	}
	if(top<10){
		cout<<"1";//特判2
		return 0;
	}
	for(i=1;;i++){
		top=sb(top);
		if(top/10==0){
			cout<<i+1;
			return 0;
		}
	}
} 
```
写得还可以吧~希望通过

---

## 作者：谦谦君子 (赞：0)

## 思路：
#### 不停的把一个数位数相加，直到是一个个位数
# 代码见下
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int main()
{
	int k;
	while (cin>>a)
	{
		int sum=0,len=a.size();
	    if (len==1)
	    {
	    	cout<<"0"<<endl;
	    	continue;
		}
	    for (int i=0;i<len;i++)
	    {
	    	sum+=a[i]-'0';
		}
		int ans=sum,num=0;
		while (ans/10>0)
		{
			int t=0;
			while (sum)
			{
				t+=sum%10;
				sum/=10;
			}
			sum=ans=t;
			num++;
		}
		num++;
		cout<<num<<endl;
	}
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

直接暴力枚举即可。

要注意的是，这个数据范围很大，但是 $n$ 的数字和也不会超过 int ，于是第一次直接用字符串 string 模拟即可。

要特别注意的是，当直接输入一位数时应直接输出 ```0``` 。

# Code

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string s;
int t,ans=1;
int sum(int x){
	int r;
	while(x){
		r+=x%10;
		x/=10;
	}
	return r;
}
int main(){
	cin>>s;
	if(s.length()==1){cout<<"0";return 0;}
	for(int i=0;i<s.length();i++)
		t+=(s[i]-'0');
	while(t>9){
		t=sum(t);
		ans++;
	}
	cout<<ans;
}
```

---

