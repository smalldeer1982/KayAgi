# Buggy Robot

## 题目描述

Ivan has a robot which is situated on an infinite grid. Initially the robot is standing in the starting cell $ (0,0) $ . The robot can process commands. There are four types of commands it can perform:

- U — move from the cell $ (x,y) $ to $ (x,y+1) $ ;
- D — move from $ (x,y) $ to $ (x,y-1) $ ;
- L — move from $ (x,y) $ to $ (x-1,y) $ ;
- R — move from $ (x,y) $ to $ (x+1,y) $ .

Ivan entered a sequence of $ n $ commands, and the robot processed it. After this sequence the robot ended up in the starting cell $ (0,0) $ , but Ivan doubts that the sequence is such that after performing it correctly the robot ends up in the same cell. He thinks that some commands were ignored by robot. To acknowledge whether the robot is severely bugged, he needs to calculate the maximum possible number of commands that were performed correctly. Help Ivan to do the calculations!

## 样例 #1

### 输入

```
4
LDUR
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
RRRUU
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6
LLRRRR
```

### 输出

```
4
```

# 题解

## 作者：Miller2019 (赞：6)

题意：计算一个字符串中$\ 'L'$ ，$\ 'R'$ , $\ 'U'$ , $\ 'D'$ 出现的次数，然后输出两倍的它们中前两个中的较小数加上后两个中的较小数。

方法：做一个函数计算一个字符在字符串中间出现的个数，然后在输出时调用即可。

```cpp
#include<iostream>
#include<bits/stl_algobase.h>
using namespace std;
string str;int n;
int s(char a)
{
	int ans=0,k;
	while(k=str.find(a),k!=str.npos)	//在字符串str中寻找字符 a ，用 k 记录 a 的位置。当 k 等于 str.npos 时（未找到），循环终止。
	{
		str.erase(k,1);	//删除字符。
		ans++;	//答案自加 1 。
	}
	return ans;	//返回答案。
}
int main()
{
    cin>>n>>str;	//读入长度 n 和字符串 str 。
    cout<<2*(min(s('L'),s('R'))+min(s('U'),s('D'))); //调用函数，输出。
    return 0;	//Don't forget this.
}
```

蒟蒻橙后第 7 篇题解。


---

## 作者：Scrutiny (赞：4)

作为一个`multiset`爱好者，蒟蒻打算写一篇用`multiset`的题解。

看到题目就想到`count`函数，于是我想到了用`multiset`。

思路：先输入$n$，然后循环输入字符，并将输入的字符放入`multiset`中。

最后分别统计`multiset`中的`L`,`R`,`U`,`D`的个数，按照题目要求输出即可。

注意：

$1.$必须用`multiset`而不能用`set`！

$2.$养成用`multiset`先定义`iterator`的好习惯。


```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt1,cnt2,cnt3,cnt4,n;
char c;
int main(){
	cin>>n;
	multiset<char> s;
	multiset<char>::iterator it;
	for(int i=1;i<=n;++i){
		cin>>c;
		s.insert(c);
	}
	cnt1=s.count('L');
	cnt2=s.count('R');
	cnt3=s.count('U');
	cnt4=s.count('D');
	cout<<2*(min(cnt1,cnt2)+min(cnt3,cnt4));
	return 0;
}
```


---

## 作者：REAL_曼巴 (赞：2)

此题的题意十分清楚，问我们若机器人在最后仍然待在原地，它执行命令命令数的最大值。本题有四种操作，分别是上，下，左，右。其中我们可以把上下看为一组，左右看为一组。不难发现，每组中操作数量最少的操作必将执行全部，我们可以用最小值的函数来进行求解，再将每组最小值加起来。注意，这不是最后结果，还要将其乘 $2$ 。

```cpp
#include <iostream>
using namespace std;
int len;
int L=0,R=0,U=0,D=0;//建立四个计数器，统计每一种操纵，注意清0
char c;
int main(){
    cin>>len;
    while(len--){//因为有len个操作，循环len次
        cin>>c;
        if(c=='L')//把每种操作的数量记录
            L++;
        if(c=='R')
            R++;
        if(c=='U')
            U++;
        if(c=='D')
            D++;
    }
    int ans=2*(min(L,R)+min(U,D));//使用min函数，根据上方的解释，求出每组操作最小值的和，并乘2
    cout<<ans;
    return 0;
}

```


---

## 作者：DeepSkyBlue__ (赞：2)

这道题其实翻译给得很直接了，这篇题解就简单把这个公式推一下。

可以看出机器人只执行了其中一些指令后才回到起点，要回到起点向左与向右的步数必定要相同，向上与向下的步数也应该相同。

要能尽量执行更多的指令， L 与 R 中个数最少的就必须全部被执行，多出来的部分就被机器人忽略了，对于 U 和 D 也是一样。

那么能够执行的最多步数就等于 L 和 R 中最少的个数与 U 和 D 中最少的个数之和再乘以2。

推出了公式后这题就不难了。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int x;
    cin>>x;//长度
    int l=0,r=0,u=0,d=0;//计数器
    for(int i=1;i<=x;i++)
    {
        char c;
        cin>>c;
        if(c=='L')l++;//统计个数
        if(c=='R')r++;
        if(c=='U')u++;
        if(c=='D')d++;
    }
    cout<<2*(min(l,r)+min(u,d))<<endl;//根据公式输出答案
    return 0;
}
```


---

## 作者：wuwenjiong (赞：1)

## 题目：
一个机器人，有四种指令控制它， $U$ 表示向上， $D$ 表示向下， $L$ 表示向左， $R$ 表示向右，现在给出命令，机器人可能未执行命令，问：如果机器人最好回到了原位，最多执行了几次命令。
## 思路：
众所周知，左与右相对，上与下相对，要想机器人仍然在原位，向左移动的单位肯定等于向右移动的单位，向上移动的单位肯定等于向下移动的单位。所以，我们可以分别记录下向上，向下，向左，向右的命令数，取向上和向下的较小值，取向左和向右的较小值，把他们相加就得出结果了。

最后，放代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d;
int main()
{
	char x;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		if(x=='U')
			a++;
		if(x=='D')
			b++;
		if(x=='L')
			c++;
		if(x=='R')
			d++;
	}
	a=min(a,b);
	b=min(c,d);
	cout<<2*a+2*b;
	return 0;
}
```
谢谢！！！

---

## 作者：159号程序员 (赞：1)

纯模拟，比较简单，我们可以先找出有几个字符，在按照公式进行操作。

 _AC Code_ 
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, sum1, sum2, sum3, sum4, sum;
    sum = sum1 = sum2 = sum3 = sum4 = 0;
    string s;
    cin >> n;
    cin >> s;
    for(int i = 0; i < n; i++)//每一位进行相加
    {
        if(s[i] == 'L')//如果是L，L的个数+1
        {
            sum1++;
        }
        if(s[i] == 'R')//如果是R，R的个数+1
        {
            sum2++;
        }
        if(s[i] == 'U')//如果是U，U的个数+1
        {
            sum3++;
        }
        if(s[i] == 'D')//如果是D，D的个数+1
        {
            sum4++;
        }
    }
    sum = 2 * (min(sum1, sum2) + min(sum3, sum4));//求出最终值
    cout << sum;
    return 0;
}
```
下面来解释一下程序：

1. 定义变量，输入，不用多讲(记住，所有的 _sum_ 一定要为0)。

1. 开始一个遍历整个字符数组的循环。

1. 用**计数器**的形式求出字符的个数。

| L | U | R | L | D | R |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |

如上图，假如我要求出 _L_ 的个数，我首先要定义一个变量： _sum_

看到第一位，是 _L_ ，sum++

看到第二位，是 _U_ ，不做操作。

看到第三位，是 _R_ ，不做操作。

看到第四位，是 _L_ ，sum++

看到第五位，是 _D_ ，不做操作。

看到第六位，是 _R_ ，不做操作。

 _sum_ 最终为2，输出2。

---

## 作者：Indulge_myself (赞：0)

# 题目大意

给你机器人的总操作数和每一次的操作（上下左右），求如果它最后回到原点最多执行多少次操作。

# 简化版题意

求 $ \min(L,R)\times2+\min(U,D)\times2 $ 的值。

下面我们分析这个式子。

## 题目分析

作为一个思路不会拐弯的人，我看到这一题就想到了搜索。但是我后来想了想。

如果样例是。
```
LUDRLR
```

那么把它改成这样。
```
LLRRUD
```

有什么问题吗？

所以这一题关键是理解操作是没有先后顺序的，因此可以直接取消搜索。

让机器人回到原点有两种情况。

1. 做了 n 次 L 和 n 次 R ， ( $ n=n $ )。

2. 做了 n 次 U 和 n 次 D ， ( $ n=n $ )。

如果 $ U=3,D=4 $，n 的值一定不可能是 4，因为 $ 4>3 $。所以只能是 3。如果 $ U=x,D=y $，那么 n 的值一定为 $ \min(x,y) $。

但是 $ \min(x,y) $ 需要 $ \times2 $，因为你计算的是两个变量。

所以我们就可以愉快的得到以下的代码。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    char a;
    int L=0,R=0,U=0,D=0;
    for(int i=0;i<n;i++)
    {
        cin>>a;
        switch(a)
        {
            case 'L':L++;break;
            case 'R':R++;break;
            case 'U':U++;break;
            case 'D':D++;break;
        }
    }
    cout<<min(L,R)*2+min(U,D)*2<<endl;
    return 0;
}
```

感谢各位收看，点个赞吧。

---

## 作者：yf最qhhh (赞：0)

[题目位置](https://www.luogu.com.cn/problem/CF888B)

[更好的阅读体验请戳这里](https://www.luogu.com.cn/blog/yfyongyuandeshen/solution-cf888b)

------------

这道题思路很简单，问的其实就是最多行走多少次能回到原地。

那么我们把这个问题看小，当一个物体在一个地方想移动又回到原地只有四种方法：向前再向后，向后再向前，向左再向右，向右再向左。

所以不难想到这道题的答案即为：

$\qquad 2\times(min(U,D)+min(L,R))$

为肾么要取 $min$ 呢？

因为，题目求的是最多，但又要保证方案合法，即走出去了一定要能走回来，所以在 $x$ 和 $y$ 方向各取一个最小值，再乘 $2$ 即为答案。

$ACCode:$
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rll register long long
using namespace std;
char a[1000005];
int main(){
	rll n,i,U=0,D=0,L=0,R=0;
	scanf("%lld",&n);
	scanf("%s",a+1);
	for(i=1;i<=n;i++){
		if(a[i]=='U')U++;
		else if(a[i]=='D')D++;
		else if(a[i]=='L')L++;
		else R++;//这个循环是为了记录UDLR的数量
	}
	printf("%lld",2*(min(U,D)+min(L,R)));//直接输出答案即可
	return 0;
}

```


---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/19/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces888B%20Buggy%20Robot)

### Description in Chinese

给你一个字符串，让你求$2 \times (\min(\texttt{'L'的个数, 'R'的个数}) + \min(\texttt{'U'的个数，'D'的个数}))$。

### Solution

给你一个字符串，先计算出$\mathrm{L}$，$\mathrm{R}$，$\mathrm{U}$，$\mathrm{D}$的个数，最后按题目给出的表达式输出即可。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

int n;
string st;
int main() {
    scanf("%d", &n);
    cin >> st;
    int L = 0, R = 0, U = 0, D = 0;
    for (int i = 0; i < st.length(); i++)
        if (st[i] == 'L') L++; else
        if (st[i] == 'R') R++; else
        if (st[i] == 'U') U++; else
        if (st[i] == 'D') D++;//统计数量
    printf("%d\n", (min(L, R) + min(U, D)) << 1);
    return 0;
}
```

---

## 作者：yzx72424 (赞：0)

%一下楼下的dalao。。
 

我的思路：一个U跟一个D抵消，一个L和一个R抵消，对它们计数

```
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
string s;
int main() {
    cin>>n;
    cin >> s; 
    for (char c : s) {
    	if(c=='U')y++;
    	else if(c=='D')y--;
    	else if(c=='L')x--;
    	else if(c=='R')x++; 
    }
    cout << n-abs(x)-abs(y) <<endl;
}


```



---

