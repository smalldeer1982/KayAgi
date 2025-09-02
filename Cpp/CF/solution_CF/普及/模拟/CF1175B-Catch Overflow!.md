# Catch Overflow!

## 题目描述

You are given a function $ f $ written in some basic language. The function accepts an integer value, which is immediately written into some variable $ x $ . $ x $ is an integer variable and can be assigned values from $ 0 $ to $ 2^{32}-1 $ . The function contains three types of commands:

- for $ n $ — for loop;
- end — every command between "for $ n $ " and corresponding "end" is executed $ n $ times;
- add — adds 1 to $ x $ .

After the execution of these commands, value of $ x $ is returned.

Every "for $ n $ " is matched with "end", thus the function is guaranteed to be valid. "for $ n $ " can be immediately followed by "end"."add" command can be outside of any for loops.

Notice that "add" commands might overflow the value of $ x $ ! It means that the value of $ x $ becomes greater than $ 2^{32}-1 $ after some "add" command.

Now you run $ f(0) $ and wonder if the resulting value of $ x $ is correct or some overflow made it incorrect.

If overflow happened then output "OVERFLOW!!!", otherwise print the resulting value of $ x $ .

## 说明/提示

In the first example the first "add" is executed 1 time, the second "add" is executed 150 times and the last "add" is executed 10 times. Note that "for $ n $ " can be immediately followed by "end" and that "add" can be outside of any for loops.

In the second example there are no commands "add", thus the returning value is 0.

In the third example "add" command is executed too many times, which causes $ x $ to go over $ 2^{32}-1 $ .

## 样例 #1

### 输入

```
9
add
for 43
end
for 10
for 15
add
end
add
end
```

### 输出

```
161
```

## 样例 #2

### 输入

```
2
for 62
end
```

### 输出

```
0
```

## 样例 #3

### 输入

```
11
for 100
for 100
for 100
for 100
for 100
add
end
end
end
end
end
```

### 输出

```
OVERFLOW!!!
```

# 题解

## 作者：bigclever (赞：5)

本蒟蒻的第一篇 C++ 题解，如有错误请多多包涵。 



# 思路
dalao 们都讲的很清楚了，**答案就是 add 语句被执行的次数**。问题的关键是怎么求当前 add 语句被执行的次数。

其实只需要看看套在 add 语句外面的循环循环了多少次就行了，举个例子：
```
for 5
for 7
add
end
end
```
此时 add 语句外面有两层循环，分别循环了 $5$ 次和 $7$ 次。所以 add 语句被执行了 $5\times7=35$ 次。

#### 那怎么解决呢？我们此时可以使用 STL 中自带的数据结构——栈（ stack ）。 ####
栈大概支持以下几种操作：
```
stack<int> stk;//声明栈，stk为栈的名字
stk.push(x)//将元素x放入栈中
stk.top()//获取栈顶元素
stk.pop()//弹出栈顶元素
```
所以我们只要看到 for 语句，就把它自己执行的次数和当前栈顶元素相乘的值放入栈中，求出它真正的执行次数。这样  for 语句的问题就解决了。

遇到 add 语句只需将结果加上栈顶元素即可；遇到 end 语句弹出栈顶元素，也就是结束当前循环即可。

# Code :
```cpp
#include<bits/stdc++.h>
using namespace std; 
using ll=long long;//相当于 typedef long long ll
const ll MAX=(1ll<<32);//让MAX=2^32
int main(){
    ll q,n,x=0;
    string s;
    stack<ll> stk;
    stk.push(1);//先放入1，否则乘的结果都是0
    cin>>q;
    while(q--){
	cin>>s;
	if(s=="for")
	    cin>>n,stk.push(min(stk.top()*n,MAX));//如果当前值大于MAX，放入MAX即可，避免放入元素过大
	else if(s=="add")x+=stk.top();
	else stk.pop();
    }
    if(x>=MAX)cout<<"OVERFLOW!!!";//大过MAX直接输出OVERFLOW
    else cout<<x;//输出结果
    return 0;
}
```


---

## 作者：Mistybranch (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1175B)

题目大概意思是：现在有一个函数，这个函数里会有一个变量 $x = 0$，并且只会有三种操作，即为：

- $\texttt{for}$ $n$：循环 $n$ 次；

- $\texttt{end}$：对应循环结束；

- $\texttt{add}$：$x = x + 1$。

求最后 $x$ 的值，如果 $x$ 超过 $2^{32} - 1$ 则输出 $\texttt{OVERFLOW!!!}$

这道题我们只需要计算每一层循环里边的操作等于将 $x$ 加了几，乘上循环的操作次数就等于这一整个循环将 $x$ 加了几。

具体思路可以用栈来实现，每个元素代表一层循环，包括两个整数，一个是循环次数，另一个是循环内将 $x$ 加了几，下面以样栗为例举栗子：

```
9
add
for 43
end
for 10
for 15
add
end
add
end
```
首先先定义一个变量 $x = 0$ 和一个空栈。

1. $\texttt{add}$：发现栈为空则 $x = x + 1$ 现在 $x = 1$；

1. $\texttt{for}$：$43$ 将栈加入元素 $(43, 0)$；

1. $\texttt{end}$：将栈顶元素 $(43, 0)$ 弹出，发现 $43 \times 0 = 0$ 则 $x$ 不加值；

1. $\texttt{for}$：$10$ 将栈加入元素 $(10, 0)$；

1. $\texttt{for}$：$15$ 将栈加入元素 $(15, 0)$；

1. $\texttt{add}$：发现栈顶为元素 $(15, 0)$ 则 将第二个元素 $+ 1$，将元素改为 $(15, 1)$；

1. $\texttt{end}$：将栈顶元素 $(15, 1)$ 弹出，将剩余的栈顶元素 $(43, 0)$ 加上 $15 \times 1$，，将元素改为 $(43. 15)$；

1. $\texttt{add}$：发现栈顶为元素 $(10, 15)$ 则 将第二个元素 $+ 1$，将元素改为 $(10, 16)$；

1. $\texttt{end}$：将栈顶元素 $(10, 16)$ 弹出，发现 $10 \times 16 = 160$ 则 $x = x + 160$，最终答案 $161$。

记得住意 long long 以及判断溢出（每次更新值的时候判断一下）即可。

完整代码：
```cpp


#include <bits/stdc++.h>

using namespace std;

int _l;
long long _x;
stack<pair<long long, long long> > _st;

void ParseInCore () { 
	string str;
	int num;
	pair<long long, long long> pa;
	
	cin >> _l;
	
	for (int i = 1; i <= _l; i++) {
		cin >> str;
		
		if (str == "add") {
			if (!_st.empty()) {
				_st.top().second++;
				
				if (_st.top().second > (long long)(((long long)1 << 32) - (long long)1)) {
					_x = -1;
					return ;
				}
			}
			
			else {
				_x++;
				
				if (_x > (long long)(((long long)1 << 32) - (long long)1)) {
					_x = -1;
					return ;
				}
			}
		}
		
		else if (str == "end") {
			pa = _st.top();
			_st.pop();
			
			if (!_st.empty()) {
				_st.top().second += pa.first * pa.second;
				
				if (_st.top().second > (long long)(((long long)1 << 32) - (long long)1)) {
					_x = -1;
					return ;
				}
			}
			
			else {
				_x += pa.first * pa.second;
				
				if (_x > (long long)(((long long)1 << 32) - (long long)1)) {
					_x = -1;
					return ;
				}
			}
		}
		
		else {
			cin >> num;
			
			_st.push(make_pair(num, 0));
		}
	}
}

void WriteOut () {
	if (_x == -1) {
		cout << "OVERFLOW!!!" << endl;
	}
	
	else {
		cout << _x << endl;
	}
}

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	ParseInCore();
	WriteOut();
	
	return 0;
}
```


---

## 作者：mydcwfy (赞：1)

## 1. 题意

给定一串语句，并有变量 $x$，初始为 $0$，仅含有一下三种类型：

1. `for n`：表示循环 $n$ 次，直到与之匹配的 `end`。
2. `end`：表示循环结束。
3. `add`：将 $x$ 加一。

执行完后，如果 $x\geq2^{32}$，输出 `OVERFLOW!!!`，否则输出 $x$ 的值。

## 2. 思路

$x$ 的值就是 `add` 的执行次数。

我们可以在记录一个变量 $mul$，表示当前的语句将会被执行多少次。

所以碰到 `add` 的时候，将当前的 $x$ 加上 $mul$ 即可。

注意，这道题 $mul$ 最大会达到 $100^{5000}$，所以注意我们如果 $mul\geq 2^{32}$，就可以直接赋值为 $2^{32}$。

但是，这里又有一个问题：$mul=2^{32}$ 之后，碰上 `end`，我们将要 $mul$ 除以当前的循环次数，明显就错误了。

处理方法也很简单：用一个栈记录所有的 `for n`，然后使用前缀积 $pre$ 维护，于是退栈的时候，我们直接将当前的 $mul$ 赋值为 $pre[top-1]$ 即可。

## 3. 代码

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const ll INF = (1ll << 32) - 1;
char str[N];
int n, top;
ll x, stk[N], tmp, pre[N];

void overflow()
{
    puts("OVERFLOW!!!");
    exit(0);
}

int main()
{
    cin >> n;
    pre[0] = 1;
    while (n --)
    {
        scanf("%s", str + 1);
        if (str[1] == 'a') x += pre[top];
        else if (str[1] == 'f')
        {
            scanf("%lld", &tmp);
            stk[++ top] = tmp;
            pre[top] = pre[top - 1] * tmp;
            if (pre[top]) ;
        }
        else if (str[1] == 'e') top --;
        if (pre[top] > INF) pre[top] = INF + 1;
        if (x > INF) overflow();
    }
    cout << x << endl;
    return 0;
}
```



---

## 作者：ImposterAnYu (赞：1)

~~这蓝怎么这么水~~

# 解析
这题的目标很明确，就是让我们计算 `add` 被调用的次数。

但是这题有个指令 `for`，会让一段代码重复调用，直到配对上一个 `end`。根据题目的要求，每一个 `for` 都会和它后面的第一个 `end` 配对。那么，如何为 `for` 配对 `end` 呢？

其实，这个问题很简单。只要我们把 `for` 视为 `(`，`end` 视为 `)`，我们就可以发现——

这不就是个基本的括号配对吗？！

于是，我们可以开一个栈 $b$，每遇到 `for` 指令就在栈中加入 $n$，每遇到 `end` 指令就将栈顶元素弹出。

还有一个问题：循环次数这么多，该怎么计算 `add` 被调用的次数呢？其实这也很好办。因为我们可以直接将

```
for
add
add
...
add（a 个 add）
end
```
视为将 $x$ 加上 $a$，所以每遇到一个 `add`，我们就将用于计算 `add` 调用次数的 $a_t$ 给加上 $1$（$t$ 为栈内元素个数），等到栈顶弹出时，再将 $a_{t-1}$ 加上 $a_t \times b_t$，最后将 $t$ 减小 $1$ 即可（~~别忘了在 $t$ 减小之前把 $a_t$ 赋为 $0$~~）。

最后一个问题：如何判断 $x$ 是否溢出？

题解区有几篇题解都选择在 $a_{t - 1}$ 溢出时将 $a_{t - 1}$ 赋为 $2^{32}$，而我选择在计算 $a_t$ 和 $a_{t - 1}$ 时就判断（因为这题的 $x$ 不会减小，所以当 $a_t$ 和 $a_{t - 1}$ 溢出了的话，$x$ 势必也会溢出）。如果溢出了，就标记一下，不执行后面的任何指令，并在最后输出 `OVERFLOW!!!` 就行了。

我可能没法把解法讲得很清楚，但我已经尽力了。如果您觉得我还是没讲明白的话，就只能看代码~~或者其他题解~~了（
# ACcode
```c++
#include<bits/stdc++.h>
#define int1 long long
#define p 100005
using namespace std;
int1 n,t,a[p],b[p],s = (1ll << 32ll);
string c;
bool f;

int1 read(){//又是快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}

void print(int1 x){//又是快写。
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 ^ 48);
  	return ;
}

int main(){
	n = read();
	while(n--){
		cin >> c;
		if(f){//为了省时间（bushi），只要有了标记，后面就不再执行任何指令（（（ 
			continue;
		}
		if(c == "for"){
			b[++t] = read();//n 入栈。 
		}else if(c == "add"){
			a[t]++;
			if(a[t] >= s){//如果溢出了就标记一下。 
				f = 1;
			}
		}else{
			a[t - 1] += a[t] * b[t],a[t] = 0;
			t--;//栈顶出栈。 
			if(a[t] >= s){//如果溢出了就标记一下。 
				f = 1;
			}
		}
	}
	if(f){
		printf("OVERFLOW!!!");
	}else{
		print(a[0]);//很明显，最后的答案就是 a[0]，具体的原因应该不用我解释吧…… 
	}
	return 0;
}
```

---

## 作者：StudyingFather (赞：0)

首先明确一点，答案显然等于`add`语句的执行次数。

我们可以采用这样的方式计算`add`语句的执行次数：每进入一层循环，就将该层循环内语句的执行次数（之前所有`for`循环执行次数的乘积）压入栈中，遇到一次`add`操作就将答案加上栈顶的值，遇到`end`就弹出栈顶。

看上去是对的，但是最坏情况下`add`的执行次数，远远超过了`long long`的表示范围，导致我们无法判断变量的值是否真正溢出。

解决这个问题的方法很简单：当压入栈中的值超过了变量最大值（ $ 2^{32} -1 $ ）的时候，我们用 $ 2^{32} $ 代替真正的执行次数压入栈。

最坏情况下，变量的值最大只有 $ 50000 \times 2^{32} $ ，在`long long`的范围之内，我们就可以正确判断变量是否溢出了。

```cpp
#include <iostream>
#include <stack>
using namespace std;
const long long INF=1ll<<32;
stack<long long> sta;
char op[5];
int main()
{
 ios::sync_with_stdio(false);
 long long l,ans=0;
 cin>>l;
 sta.push(1);
 for(int i=1;i<=l;i++)
 {
  int x;
  cin>>op;
  if(op[0]=='a')ans+=sta.top();
  else if(op[0]=='f')
  {
   cin>>x;
   sta.push(min(INF,sta.top()*x));
  }
  else sta.pop();
 }
 if(ans<INF)cout<<ans<<endl;
 else cout<<"OVERFLOW!!!"<<endl;
 return 0;
}
```

---

