# [ABC105C] Base -2 Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc105/tasks/abc105_c

整数 $ N $ が与えられるので、$ N $ の $ -2 $ 進数表現を求めてください。

ここで、$ S $ が $ N $ の $ -2 $ 進数表現であるとは、以下を全て満たすことです。

- $ S $ は `0` および `1` のみからなる文字列である
- $ S\ = $ `0` でなければ $ S $ の先頭の文字は `1` である
- $ S\ =\ S_k\ S_{k-1}\ ...\ S_0 $ とすると、$ S_0\ \times\ (-2)^0\ +\ S_1\ \times\ (-2)^1\ +\ ...\ +\ S_k\ \times\ (-2)^k\ =\ N $ が成り立つ

なお、任意の整数 $ M $ に対して $ M $ の $ -2 $ 進数表現が一意に定まることが証明できます。

## 说明/提示

### 制約

- 入力はすべて整数である
- $ -10^9\ \leq\ N\ \leq\ 10^9 $

### Sample Explanation 1

$ (-2)^0\ +\ (-2)^1\ +\ (-2)^3\ =\ 1\ +\ (-2)\ +\ (-8)\ =\ -9 $ なので `1011` は $ -9 $ の $ -2 $ 進数表現です。

## 样例 #1

### 输入

```
-9```

### 输出

```
1011```

## 样例 #2

### 输入

```
123456789```

### 输出

```
11000101011001101110100010101```

## 样例 #3

### 输入

```
0```

### 输出

```
0```

# 题解

## 作者：Blikewsr (赞：5)

 - [$\color{grey}\text{[AT4239 原题连接]}$](https://www.luogu.com.cn/problem/AT4239) 
 
 - 题目描述     
   给出一个整数 `N` ， 满足 $ -10^9 ≤ N ≤ 10^9 $ ，请计算出其 `-2` 进制表示的数。       
 
 - 输入格式                           
   一个十进制数 `N` ， 满足 $ -10^9 ≤ N ≤ 10^9 $ 。            
 
 - 输出格式    
   `N` 的 `-2` 进制的数。               
 
 - 思路   
   首先， 我们先看求一个十进制数的 `2` 进制怎么做？
   
   | 十进制数 | 二进制数 |
   | :----------: | :----------: |
   | 1 | 1 |
   | 2 | 10 |
   | 3 | 11 |
   | 4 | 100 |
   | 5 | 101 |
   
   十进制转二进制， 其实就是不断地做除法， 每次把除得的余数加上去。
   
   我们拿 `4` 举例：
   
   | 整数部分 | 余数 |
   | :----------: | :----------:|
   | 2 | 0 |
   | 1 | 0 |
   | 0 | 1 |
   
   所以， 把余数从下往上倒序看，得： `4` 的 `2` 进制数是 `100` 。
   
   那么， 十进制转二进制的代码就是：      
   ```cpp
   while(n) {
       ans[++ top] = n % 2;
       n = (n - ans[top]) / 2;
   }	
   ```
   同样的， 把一个十进制整数转 `-2` 的代码就是：
   ```cpp
   while(n) {
       ans[++ top] = n % (-2);
       n = (n - ans[top]) / (-2);
   }
   ```
   但是， 我们发现， 进制数是一个非负数。
   
   所以， 我们只用在 `n` `%` `(-2)` 这里再加一个绝对值就行了。 
   
   该部分代码：
   ```cpp
   while(n) {
       ans[++ top] = abs(n % (-2));
       n = (n - ans[top]) / (-2);
   }
   ```
   最后， 在输出时只用倒叙输出就行了。
   
   注意： 当 `N = 0` 时， 直接输出 `0` 。                         
   
 - 代码实现              
 ```cpp
#include <bits/stdc++.h>
#define int long long
#define N 99999999 
using namespace std;
int x, a[N]; 
int abs_math(int y) {        // 绝对值函数
	return y < 0 ? (-y) : y;  
}
signed main() {
	cin >> x;
	if(!x) {
		cout << 0 << '\n';
		return 0;
	}
	int top = 0;
	while(x) {
		a[++ top] = abs_math(x % (- 2));
		x = (x - a[top]) / (- 2);
	}
	for(int i = top; i >= 1; i--) {
		cout << a[i];	
	}
	cout << '\n';
	return 0;	
}
 ```

 - 此题解仅供参考， 感谢 ！

---

## 作者：Acerkaio (赞：4)

### 题外话
刚写完这题就水了这片题解，写完之后没过，再看一遍才发现没这么简单。对不起，管理员大大。
- ## 题意：  
给定 N 个数，求其 -2 进制。
- ## 思路:
二进制相信大家都会了就不多说了，当为 $-2$ 进制的时候，先一样转化为二进制，然后偶数项不用管，设奇数项 $m$ ,我们发现 $2^m=2^{(m+1)}-2^m=(-2)^{(m+1)}+(-2)^m$,所以我们可以用 $2$ 进制代替 $-2$ 进制，遇到奇数项为1就在后一项上再加个 $1$ 就好了。
- ## CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[50], en;
int main() {
	int n, k=-2;
	scanf("%d", &n);
	en = 0;
	while(n) {
		ans[en] = n & 1;
		n >>= 1;
		if((en & 1) && (ans[en] & 1) )    n++;
		en++;
	}
	if(en) {
		for(int i = en - 1; i >= 0; --i) printf("%d", ans[i]);
		puts("");
	} else {
		puts("0");
	}
	return 0;
}
```


---

## 作者：Fcersoka (赞：3)

这道题十分的简单啊 ，题目意思是给你一个十进制整数 ,求出这个十进制整数的 $-2$ 进制 。  
我们的知道将一个十进制整数转化为 $n$ 进制时 ，我们可以用短除法来求 。而这里呢 ，也不例外 。需要注意的是 ：  
1. 当给出的十进制整数为 $0$ 时 ，这个数的 $-2$ 进制也为 $0$；
2. 用短除法计算出来的余数 ，必须是非负的 ，只需要用 abs 即可 ；
3. 每次循环结束前 ，需要将十进制整数 $n$ 减去余数 ，最后再除以 $-2$。  
我是用 while 循环来写的 。  
AC 代码如下 。 
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],ans;
int main(){
	cin>>n;
	if(n==0){//特判
		cout<<0<<endl;
		return 0;
	}
	while(n){
		a[++ans]=abs(n%(-2));//用数组a来存储结果
		n=(n-a[ans])/(-2);
	}
	for(int i=ans;i>0;i--)
	cout<<a[i];
	return 0;
}
```
感谢您的观看 ！


---

## 作者：_cmh (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/AT4239)

[双倍经验](https://www.luogu.com.cn/problem/UVA11121)

## $\texttt{Description}$

给出一个整数 $n$，输出它在 $-2$ 进制下表示的数。

## $\texttt{Solution}$

本题同 $2$ 进制转换一样，也可以用短除法解决。

注意几个点：

- 短除法时，注意答案需要倒过来输出。此处我用的是 `stack` 来输出。

- 同时，$n\bmod -2$ 有可能为 $-1$，输出时记得转化成 $1$ 输出，此处我用的是 $-1$。

- 注意特殊数据 $n=0$ 时，应特判输出 $0$。

- $n\div 2$ 时记得减去余数后再除，而余数是 $-1$ 时应该化为 $1$。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int x;
	scanf("%d",&x);
	if(x==0)
		puts("0");
	else{
		stack<int>ans;
		while(x){
		    int now=abs(x%(-2));
			ans.push(now);
			x=(x-now)/(-2);
		}
		while(!ans.empty()){
			printf("%d",ans.top());
			ans.pop();
		}
	}
	return 0;
}
```

感谢观看。

---

## 作者：RBI_GL (赞：1)

# 题意

给定一个整数 $n$，将其转换为 $-2$ 进制数并输出。

# 思路

和转换为 $2$ 进制数一样，利用短除法进行操作，用一个 ```vector``` 保存答案。输出时将所有 $-1$ 换成 $1$ 后输出。

这里 $n=0$ 时要特判。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> v; // 保存答案 
int main() {
	cin >> n;
	if (n == 0) {
		puts("0");
		return 0;
	}
	int cnt = -1;
	while(n) { // 短除 
		v.push_back(n % (-2));
		cnt++;
		n /= (-2);
		if (v[cnt] == -1) n++;
	}
	for(int i = v.size() - 1; i >= 0; --i) printf("%d", v[i] == -1 ? 1 : v[i]);
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

### 题目翻译

给定一个 $10$ 进制数，将其转变成 $-2$ 进制。

### 题目思路

和二进制一样短除法。

注意事项：

- 特判数据 $n=0$ ，不特判的话，它本身进入不了短除法代码，答案就没有记录。

- 任何位置上不可能出现 $-1$，要转成 $1$ 输出。

- 短除法倒着输出。

### 题目代码 

```cpp
void solve()//没加上快读快写、long long定义ll，防抄袭
{
	int a[105];//存储答案
	ll n=read();
	int x=-1;//存储答案位数
	if(n==0){puts("0");return;}//特判
	while(n!=0)//短除法
	{
		a[++x]=n%(-2);
		n/=(-2);
		if(a[x]==(-1))//注意事项栏
		{
			n++;
			a[x]=1; 
		}
	}
	reverse(a,a+x+1);//倒着输出，翻转区间
	for(int i=0;i<=x;write(a[i++]));
}
```



---

