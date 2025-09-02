# [CCC 2008 J2] Do the Shuffle

## 题目描述

那些播放数字音乐的小型音乐设备实际上是计算机，它们负责管理和播放音乐文件。CCC 音乐播放器 $(C^3MP)$ 正在开发中，并将很快上市！在这个问题中，你需要模拟一个 $C^3MP$。

$C^3MP$ 音乐播放器将会在内存中保存 5 首歌曲，其标题总是 `A`、`B`、`C`、`D`、`E`。$C^3MP$ 还会记录一个播放列表，即所有歌曲的排序。$C^3MP$ 有 4 个按钮，用户可以按下这些按钮来重新排列播放列表并播放歌曲。

最初，$C^3MP$ 的播放列表是 `A,B,C,D,E`。这 4 个控制按钮的功能如下：

- 按钮 $1$：将播放列表中的第一首歌移动到播放列表的末尾。例如：`A,B,C,D,E` 将变为 `B,C,D,E,A`。

- 按钮 $2$：将播放列表中的最后一首歌移动到播放列表的开头。例如：`A,B,C,D,E` 将变为 `E,A,B,C,D`。

- 按钮 $3$：交换播放列表中的前两首歌。例如：`A,B,C,D,E` 将变为 `B,A,C,D,E`。

- 按钮 $4$：停止重新排列歌曲并输出播放列表。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
1
3
1
2
3
4
1```

### 输出

```
B C D A E```

# 题解

## 作者：banglee (赞：7)

# P9855 [CCC 2008 J2] Do the Shuffle 题解
[题目传送门](https://www.luogu.com.cn/problem/P9855)


# 正文
一道非常简单的模拟题，考察数组前移、后移、交换、输出。

要注意的是，题目的输入并没有给出输入多少组，因此我们要使用

```while(cin>>b>>n)```

来进行输入。

- $b=1$ 进行数组前移操作
- $b=2$ 进行数组后移操作
- $b=3$ 数组前两个元素交换
- $b=4$ 输出数组

## 数组前移
```cpp
void change_1(){
     char t=c[0];
     for(int i=0;i<4;i++)  //后面的数据不停覆盖前面的数据，实现数组前移
          c[i]=c[i+1];
     c[4]=t;
}
```
## 数组后移
```cpp
void change_2(){
     char t=c[4];
     for(int i=4;i>=0;i--)  //前面的数据不停覆盖后面的数据，实现数组后移
          c[i]=c[i-1];
     c[0]=t;
}
```
## 元素交换
元素交换有两种方式，一种是用临时变量，另一种是用 ```swap``` 函数来进行交换

### 方法一
```cpp
int t;
t=c[0],c[0]=c[1],c[1]=t;
```
### 方法二
```cpp
swap(c[0],c[1]);
```

有了以上知识，我们便可以写出 AC 代码

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int b,n;
char c[10]={'A','B','C','D','E'}; //初始化字符数组

void change_1(){ //数组前移
     char t=c[0];
     for(int i=0;i<4;i++) //后面的数据不停覆盖前面的数据，实现数组前移
          c[i]=c[i+1];
     c[4]=t;
}

void change_2(){ //数组后移
     char t=c[4];
     for(int i=4;i>=0;i--) //前面的数据不停覆盖后面的数据，实现数组后移
          c[i]=c[i-1];
     c[0]=t;
}

void change_3(){ //元素交换
     swap(c[0],c[1]);
}

void output(){ //输出
     for(int i=0;i<5;i++)
          cout<<c[i]<<" ";
}
int main() {
     while(cin>>b>>n)  //题目的输入并没有给出输入多少组，要用 while 输入
	 { 
          if(b==1)  //第一种情况，数组前移
               for(int i=1;i<=n;i++) //执行 n 次
                    change_1();
          if(b==2)  //第二种情况，数组后移
               for(int i=1;i<=n;i++)
                    change_2();
          if(b==3)  //第三种情况，元素交换
               for(int i=1;i<=n;i++)
                    change_3();
          if(b==4)  //第四种情况，输出
          {
               output();
               break;  //题目说要终止程序，而在本题此处 break 和 return 0 的效果是相同的
          }
     }
     return 0;  //完结撒花
}
```

---

## 作者：XingnoYi (赞：4)

**很明显的一道模拟题，分四部分操作即可。**

我们可以定义如下数组：
```char ans[7] = {'_','A','B','C','D','E','_'};```。

为什么要留出两个位置（```'_'```）呢？下面我将进行分析。

## $b = 1$ 的情况：

> 将前面第一个字符移到末尾去，执行 $n$ 次。

我们可以考虑将所有字符前移一位，空出 ```ans[5]```，再将第一个字符赋值给空出的位置。

```cpp
if(b == 1)
{
    n %= 5;
    while(n--)
    {
        for(int i = 0;i <= 4;i++) //这时 ans[0] 派上用场了。
        {
            ans[i] = ans[i+1];
        }
        ans[5] = ans[0];
    }
}
 ```
 
## $b = 2$ 的情况：

> 将末尾字符移到首位去，执行 $n$ 次。

思路同上：我们可以考虑将所有字符后移一位，空出```ans[1]```，再将最后一个字符赋值给空出的位置。

```cpp
if(b == 2)
{
    n %= 5;
    while(n--)
    {
        for(int i = 6;i >= 2;i--) // 这时 ans[6] 派上用场了。
        {
            ans[i] = ans[i-1];
        }
        ans[1] = ans[6];
    }
}
 ```
 
## $b = 3$ 的情况：
 
> 交换前 $2$ 个字符的位置，执行 $n$ 次。
 
这个简单，没什么好说的。
 
```cpp
if(b == 3)
{
    n %= 2;
    while(n--)
    {
        swap(ans[1],ans[2]);
    }
}
```

## $b = 4$ 的情况：

> 输出当前的字符数组（每个字符用空格隔开），并终止程序。

直接输出！！

```cpp
if(b == 4)
{
    for(int i = 1;i <= 5;i++)
    {
        printf("%c ",ans[i]);
    }
    break; // It's important! Don't forget it!
}
```

## 一些优化：

相信眼尖的读者已经看到了这两行：

- ```n %= 5;```
- ```n %= 2;```

为什么会有这个优化？

1. 当 ```b = 1``` 或 ```b = 2``` 时，将最前（后）的字符移至最后（前）。数组长度为 $5$，显然操作 $5$ 次又变回原形，可以适当优化。

2. 当 ```b = 3``` 时，交换位置。显然 $2$ 次交换相当于没有交换。

注：虽然此题 $1 \le n \le 10$，但是如果 $n$ 很大，这个优化将变得尤为重要。

## 完整代码：

```cpp
#include <iostream>
#define big long long
using namespace std;
big b,n;
char ans[7] = {'_','A','B','C','D','E','_'};
int main()
{
    while(1)
    {
        cin >> b >> n;
        if(b == 4)
        {
            for(big i = 1;i <= 5;i++)
            {
                printf("%c ",ans[i]);
            }
            break;
        }
        if(b == 1)
        {
            n %= 5;
            while(n--)
            {
                for(big i = 0;i <= 4;i++)
                {
                    ans[i] = ans[i+1];
                }
                ans[5] = ans[0];
            }
        }
        if(b == 2)
        {
            n %= 5;
            while(n--)
            {
                for(big i = 6;i >= 2;i--)
                {
                    ans[i] = ans[i-1];
                }
                ans[1] = ans[6];
            }
        }
        if(b == 3)
        {
            n %= 2;
            while(n--)
            {
                swap(ans[1],ans[2]);
            }
        }
    }
    return 0;
}
```

 

---

## 作者：n0ip (赞：2)

这是算比较水的一道题，4种情况，枚举就行了。

代码如下：
```
#include <bits/stdc++.h>
using namespace std;
char a[5] = {'A', 'B', 'C', 'D', 'E'};
char c[5];
int b,n;
void cout_a()
{
	for (int i=0;i<5;i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void one()
{
	for (int i=0;i<5;i++)
	{
		c[i] = a[(i + n) % 5];
	}
	for (int i=0;i<5;i++) a[i] = c[i];
}

void two()
{
	for (int i=0;i<5;i++)
	{
		c[i] = a[(i - n + 10) % 5];
	}
	for (int i=0;i<5;i++) a[i] = c[i];
}

void three()
{
	if (n % 2)
	{
		swap(a[0], a[1]);
	}
}

int main()
{
	cin >> b >> n; 
	while (b != 4)
	{
		if (b == 1) one();
		if (b == 2) two();
		if (b == 3) three();
		cin >> b >> n;
	}
	cout_a();
}
```


---

## 作者：hao_zi6366 (赞：1)

## 题目分析

按照题意模拟即可，我们可以使用双端队列这一数据结构简化模拟过程。

接下来介绍几种双端队列的用法：

- `std::deque<char> c` 定义一个名为 c 的双端队列；

- `c.push_front()` 在 c 首位插入一个元素；

- `c.pop_front()` 删除 c 首位元素；

- `c.push_back()` 在 c 末尾插入一个元素；

- `c.pop_back()` 删除 c 末尾元素。

有了它，这题就很简单了。

## 完整代码

```cpp
#include<bits/stdc++.h>
typedef long long ll;

int main(){
	std::ios::sync_with_stdio(0);
	std::cout.tie(0);
	std::cin.tie(0);
	
    std::deque<char> c;
    c={'A','B','C','D','E'};
    int b,n;
    while(std::cin>>b>>n){
        if(b==1){                       //b==1时
            for(int i=1;i<=n;i++){
                c.push_back(c.front());//尾部插入首部元素
                c.pop_front();         //首部元素删除
            }
        }else if(b==2){                 //b==2时
            for(int i=1;i<=n;i++){
                c.push_front(c.back());//首部插入尾部元素
                c.pop_back();          //尾部元素删除
            }
        }else if(b==3){                 //b==3时
            for(int i=1;i<=n;i++){
                std::swap(c[0],c[1]);   //交换
            }
        }else if(b==4){                 //b==4时
            for(int i=0;i<5;i++){
                std::cout<<c[i]<<" ";   //输出
            }
            return 0;
        }

    }
	return 0;
}
```


---

## 作者：qwertim (赞：0)

按照题意暴力模拟即可。
- $b=1$：

建立一个新的字符数组 $C$，每次把原数组 $c_2$ 至 $c_5$ 的字符赋到 $C_1$ 到 $C_4$ 里去，最后使 $C_5=c_1$，再把 $C$ 复制到 $c$ 即可。

执行 $n$ 次即可。
```cpp
void a1(){
	char C[6];
	fo(i,1,n){
		fo(j,1,4)C[j]=c[j+1];
		C[5]=c[1];
		fo(j,1,5)c[j]=C[j];
	}
}
```
- $b=2$：

其实和 $b=1$ 的情况本质一样，只不过把它倒过来而已。

只要把 $c$ 翻转一下，在执行 $a1$ 操作，最后再把 $c$ 翻转一下即可。
```cpp
void a2(){
	reverse(c+1,c+6);//翻转函数，此处意为翻转c[1]到c[5]
	a1();
	reverse(c+1,c+6);
}
```
- $b=3$：

这应该不用我多说了吧，执行 $n$ 次 `swap(c[1],c[2])` 就好了。
```cpp
void a3(){
	fo(i,1,n)swap(c[1],c[2]);//交换函数，此处意为交换c[1]和c[2]
}
```
- $b=4$：

直接 `for` 循环遍历输出即可，**记得结束程序**。
```cpp
void a4(){
	fo(i,1,n)cout<<c[i]<<' ';
	exit(0);//结束程序 
}
```

于是就做完了。

---

## 作者：noi2077 (赞：0)

观察到数据范围较小，用一个 `vector` 按题意模拟即可。先定义一个 `vector<char> v`，初始值是 `{'A', 'B', 'C', 'D', 'E'}`。

- 操作 $1$：将 `v.front()` 复制到最后一个，然后删掉 `v[0]`。
- 操作 $2$：将 `v.back()` 复制到第一个，然后删掉最后一个。
- 操作 $3$：直接交换 `v[0]` 和 `v[1]`。
- 操作 $4$：用 `break` 跳出循环。

```cpp
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<char> v{'A', 'B', 'C', 'D', 'E'};
    int b, n;
    while(cin >> b >> n)
    {
        if(b == 1) while(n--) v.emplace_back(v.front()), v.erase(v.begin());
        if(b == 2) while(n--) v.emplace(v.begin(), v.back()), v.pop_back();
        if(b == 3) while(n--) swap(v[0], v[1]);
        if(b == 4) break;
    }
    for(auto x: v) cout << x << ' ';
    return 0;
}
```

---

## 作者：FurippuWRY (赞：0)

本题可以用[双端队列](https://oi-wiki.org/ds/queue/#c-stl-%E4%B8%AD%E7%9A%84%E5%8F%8C%E7%AB%AF%E9%98%9F%E5%88%97)来模拟。

首先定义一个双端队列 `a`，类型为 `char`。

```cpp
deque<char> a;
```

然后把 `A` 到 `E` 插入到队列中。

```cpp
for (char i = 'A'; i <= 'E'; ++i) {
    a.push_back(i);
}
```

#### 操作 1：

访问队首元素，并插入到队尾，弹出队尾元素。

```cpp
if (b == 1) {
	while (n--) {
		a.push_back(a.front());
		a.pop_front();
	}
}
```

#### 操作 2：

与操作 1 同理，把队首和队尾的操作交换一下即可。

```cpp
if (b == 2) {
	while (n--) {
		a.push_front(a.back());
		a.pop_back();
	}
}
```

#### 操作 3：

判断 $n$ 的奇偶性，如果 $n$ 为偶数，则不需要修改队列，反之若为奇数，只需交换一次前两个元素即可。

```cpp
if (b == 3) {
	if (n % 2 == 1) {
		x = a.front();
		a.pop_front();
		y = a.front();
		a.pop_front();
		a.push_front(x);
		a.push_front(y);
	}
}
```

#### 操作 4：

循环输出并结束程序即可。

```cpp
if (b == 4) {
	for (ll i = 0; i < 5; ++i) {
		cout << a[i] << ' ';
	}
	return 0;
}
```

------------

整合在一起就有了 AC code：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll b, n;
deque<char> a;
char x, y;

int main() {
    for (char i = 'A'; i <= 'E'; ++i) {
    	a.push_back(i);
	}
	while (cin >> b >> n) {
		if (b == 1) {
			while (n--) {
				a.push_back(a.front());
				a.pop_front();
			}
		}
		if (b == 2) {
			while (n--) {
				a.push_front(a.back());
				a.pop_back();
			}
		}
		if (b == 3) {
			if (n % 2 == 1) {
				x = a.front();
				a.pop_front();
				y = a.front();
				a.pop_front();
				a.push_front(x);
				a.push_front(y);
			}
		}
		if (b == 4) {
			for (ll i = 0; i < 5; ++i) {
				cout << a[i] << ' ';
			}
			return 0;
		}
	}
    return 0;
}
```

---

## 作者：Vct14 (赞：0)

本题中 $b$ 为 $1$ 或 $2$ 时，都要在序列的首尾进行插入和删除操作。因此不难想到双端队列。

- 对于操作一，因为执行 $5$ 次后会复原，所以实际上只执行了 $n\bmod5$ 次。每次将队头元素取出压进队尾，再弹出队头元素即可。
- 对于操作二，同操作一，将队尾元素取出压进队头，再弹出队尾元素。
- 对于操作三，因为执行 $2$ 次后就会复原，所以实际上只执行了 $b\bmod2$ 次。每次操作将队头前两个数取出，再按相反的顺序从队头压进去。
- 对于操作四，可以不停地取出队头元素输出，直到队列为空。

```c++
#include<bits/stdc++.h>
using namespace std;

deque<char>a;

int main(){
	for(int i=0; i<5; i++) a.push_back((char)('A'+i));
	int b,n;
	while(cin>>b>>n){
		if(b==1){
			n%=5;//
			while(n--){
				a.push_back(a.front());
				a.pop_front();
			}
		}
		if(b==2){
			n%=5;//
			while(n--){
				a.push_front(a.back());
				a.pop_back();
			}	
		}
		if(b==3){
			//if(n%2)
			n%=2;
			while(n--){
				char c1=a.front();
				a.pop_front();
				char c2=a.front();
				a.pop_front();
				a.push_front(c1);
				a.push_front(c2);
			} 
		}
		if(b==4){
			while(!a.empty()){
				cout<<a.front()<<" ";
				a.pop_front();
			}
			return 0;
		}
	}
	return 0;
}
```

事实上，因为 $n\leqslant10$，所以操作一、二也可以不进行取模优化；操作三实际上最多只会执行 $1$ 次，所以也可以不用 `while`，仅判断 $b\bmod2$ 是否等于 $1$，是则执行 $1$ 次即可。

---

