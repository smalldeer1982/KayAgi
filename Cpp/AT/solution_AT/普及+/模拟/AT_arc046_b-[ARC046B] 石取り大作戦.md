# [ARC046B] 石取り大作戦

## 题目描述

高桥和青木决定使用 $N$ 个石头组成的石山来玩取石游戏。游戏规则如下：

- 玩家交替从山上取一块以上的石头。
- 取了最后的石头的玩家的胜利。

先手高桥君一次最多可以拿下 $A$ 个石头，而后手青木君一次最多可以取出 $B$ 个石头。你的工作就是当两个人采取最佳行动时，来判断获胜的玩家。

## 说明/提示

$1\le N\le 10^9$

$1\le A,B\le 10^9$。

## 样例 #1

### 输入

```
5
3 3```

### 输出

```
Takahashi```

## 样例 #2

### 输入

```
4
3 3```

### 输出

```
Aoki```

## 样例 #3

### 输入

```
5
3 2```

### 输出

```
Takahashi```

## 样例 #4

### 输入

```
1000000000
1000000000 1```

### 输出

```
Takahashi```

# 题解

## 作者：xujian (赞：8)

### 人生中第一道灰题的题解，好激动

~~之前以为是数据错误交了$n$遍卡数据~~

## 思路：

首先我们可以知道，手里能拿石头更多的人就拥有更多的选择权。因此我们只要保持每一轮拿完后的石头都是$n$的因数，那么后拿的那个人就可以获得胜利。假设是$a$，$b$两人，有更多的选择权的那个人只要保证剩下的那个人无论如何也不能保证剩下的石头是$n$的因数就可以获胜了。即n%a+1!=0或n==b+2。注意这里一定要判断$ab$两人谁是拥有更多选择权的人。

### 还有就是要注意一下特殊情况，如果两个人中间有人能一次拿完，则那个人直接获胜。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b;
int main(){
    cin>>n>>a>>b;
    if(a>=n||(n%(a+1)&&(a>=b))||(b+2==n))puts("Takahashi");
    else puts("Aoki");
    return 0;
}
```
求管理员大大给过……

---

## 作者：可爱的小于 (赞：1)

题目大意：有 $n$ 块石子，先手每次最多取 $a$ 颗，后手每次最多取 $b$ 颗，当石子被取完时，谁就获胜。求两个人采取最佳行动时，获胜的玩家是谁。

当先手想要获胜，就可以从以下三方面考虑：

$1.$ 如果先手能取的石子数比总石子多，可以直接获胜。

$2.$ 如果石子数 $n$ 不是 $a+1$ 的倍数则说明先手可以转换为后手（但先手能取的石子数必须比后手多），从而胜利。

$3.$ 先手取 $1$ 块，后手无论取多少颗，先手都能取完（将先手转化为后手）。 

条件不满足就是后手赢了。

那么代码就很好写了：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b;
bool cheak(){//判断先手是否能获胜 
	if(a>=n)return true;//如果先手能取的石子数比总石子多，可以直接获胜 
	if(n%(a+1)!=0&&a>=b)return true;
	//如果石子数 n 不是 a+1 的倍数
	//则说明先手可以转换为后手（但取得石子数要比后手多） 
	if(b+2==n&&a>=n-2)return true;//先手取 1 个，后手取多少，先手都能取完 
	return false;
}
int main()
{
    cin >> n >> a >> b;
    if(cheak())cout<<"Takahashi"<<endl;
    else cout<<"Aoki"<<endl;
    return 0;
}
```


---

## 作者：勘探员·引魂人 (赞：1)

**前言：终于要发第一篇紫题的题解了！（虽然WA了3个点）**

**思路：保证剩下的石头是n的因数就可以获胜了（即n%a+1!=0或n==b+2）注意这里一定要判断ab两人谁是拥有更多选择权的人(用check函数判断)**

```
#include<iostream>
#include<cstring>
#include<cstdio>//文件头啊，你太难啦
using namespace std;
long long n,a,b;//定义要判断的三个数（long long 类型）
bool check(int x,int y,int z)//check函数（bool类型）
{
	if(y>=x||(x%(y+1)&&(x>=z))||(z+2==x)) return true;//如果获胜(x%y+1!=0或x==z+2)，答案为真
	else return false;否则答案为假
}
int main()
{
    scanf("%lld%lld%lld",&n,&a,&b);//输入三个数
    if(check(n,a,b)) cout<<"Takahashi"<<endl;//如果答案为真，输出"Takahashi"（换行！）
    else cout<<"Aoki"<<endl;//否则输出"Aoki"（换行！）
    
    return 0;//结束“题解 AT1712 【石取り大作戦】”
}
```

---

## 作者：Rhapsodia (赞：0)

没人发 $Python$ 的题解，那我就发一篇吧。

来分一下情况：

1. $n \le a$ 时，先手胜。

2. $a = b$ 时，

	- 若 $n \equiv 0 \pmod{a + 1}$
    	后手可以与先手凑 $a + 1$ ，后手胜。
   - 否则，先手把余数取走，然后凑 $a + 1$ ，先手胜。

3. $a < b$ 时，后手胜。

4. $a > b$ 时，先手胜。

代码如下：

```python
n = int(input())
a, b = map(int, input().split())
if n <= a:
  print("Takahashi")
  exit(0) ##n<=a的情况
 
if a == b:
  if n % (a + 1) == 0: print("Aoki")
  else: print("Takahashi")
elif a < b: print("Aoki")
else: print("Takahashi")
```

---

## 作者：hyc1026 (赞：0)

本题主要分以下几种情况讨论：

1. $a\ge n$

在这种情况下，由于先手可以直接取完，所以输出 `Takahashi`。

2. $n\bmod (a+1)\not=0$ 并且 $a+1>b$

在这种情况下，只要 $a+1>b$，则在无论后手取多少，只要取对应的数凑满 $a+1$ 个即可。（只要一开始先手取 $n\bmod (a+1)$ 个即可。）

若 $n\bmod (a+1)=0$ 则相当于先手变成了“后手”。若 $a+1>b$，则后手可以直接取 $a+1$ 个打破局面。

3. $b+2=n$ 并且 $a+2\ge n$

在这种情况下，先手取 $1$ 个，后手无论取多少，先手都能直接取完。

AC Code:

```cpp
#include <bits/stdc++.h>
#define T cout<<"Takahashi"<<endl
#define A cout<<"Aoki"<<endl
using namespace std;

int main()
{
    int n,a,b;
    cin >> n >> a >> b;
    if(a >= n) T;
    else if(n % (a+1) != 0 && a+1 > b) T;
    else if(b+2 == n && a+2 >= n) T;
    else A;
}
```

---

## 作者：cqbzlwz (赞：0)

## 题目分析

首先可以看到这是一个取石子的问题，因此我们要对~~我最讨厌的~~**游戏策略**进行分析。

总共有以下情况：

- 若某人在开始可以直接取完，则那个人直接获胜。
- 若 $b + 2 = n$，那么高桥可以先取 $1$ 个，此时的 $b+1$ 个，无论青木怎么取都会至少留下一个，此时高桥获胜。
- 当 $b \leq a$ 且 $n\ \bmod\ (a + 1) \not= 0$ 时，可以发现，该状态可以转化成 $b + 2 = n$ 的情况。

## 代码

```cpp
#include <cstdio>
int n, a, b;
int main() {
    scanf("%d%d%d", &n, &a, &b);
    if (a >= n || (n % (a + 1) && a >= b)|| b + 2 == n && a >= n - 2) puts("Takahashi");
    else puts("Aoki");
    return 0;
}

```

---

## 作者：Aurora_Borealis_ (赞：0)

先手获胜条件：

-  $ n \leq a $ 

此时先手可以一次取完，胜。

- $ b+2=n $

先手取一个，此时剩 $ b+1 $ 个，由于后手最多取 $ b $ 个，无法一次取完，故先手胜。

- $ b \leq a $ 且 $ n \bmod (a+1) \neq 0 $

此时容易看出，当前情况可以转移到 $ b=2 $ 情况。

代码：
```cpp
#include<iostream>
using namespace std;
int n,a,b;
int main(){
	cin>>n>>a>>b;
	if(a>=n||b==n-2||a>=b&&n%(a+1)!=0) {
		cout<<"Takahashi"<<endl;
	}else{
		cout<<"Aoki"<<endl;
	}
	return 0;
}
```


---

## 作者：shAdomOvO (赞：0)

# 题解

[题目链接](https://www.luogu.com.cn/problem/AT1712)
首先，告诉我们总共有多少石子，和两人分别一次能拿多少石子，可以写出判断
```cpp
if(a>=n||(n%(a+1)!=0&&a>=b)||b+2==n&&a>=n-2)
```

我来一一解释：

### 第一个：
```cpp
a>=n
```
很明显，先手能一次取完，便一定能够获胜。

### 第二个：

```cpp
(n%(a+1)!=0&&a>=b)
```

$ a+1 $ 表示后手无论取什么数，先手都能取一个对应的数组成 $ a+1 $ , 而 $ a \ge b $ 是因为防止后手 $ b>a+1 $ ,取得胜利。

### 第三个： 
```cpp
b+2==n&&a>=n-2
```


这也是我跟其它题解看法不同的地方。如果只有 $ b+2=n $ 的话，很容易举出反例：

若 $ n=10,a=2,b=8 $ ，此时先手先取一个，此是后手也取一个，那不论如何，后手也会获胜，所以，只有在先手已取两个子的情况下，能全部取完，那么先手才能获胜。
 
##  代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b;
int main(){
    cin>>n>>a>>b;
    if(a>=n||(n%(a+1)!=0&&a>=b)||b+2==n&&a>=n-2)cout<<"Takahashi"<<endl;
    else cout<<"Aoki"<<endl;
    return 0;
}

```

 
 

---

## 作者：atarashiTLE (赞：0)

### 思路：
直接讲正解好了。

先看正解的判断条件：`a>=n||n%(a+1)&&a>=b||n==b+2`。

`a>=n`:可以一次取完，先手必胜。

`n==b+2`:显然有先手必胜条件（取$1$个）。

`n%(a+1)&&a>=b`:先手只需要转移到`n`为`b+2`时的状态就行了。`b+2`用来判定`Takahashi`是否为真的先手。

code:
```cpp
#include<iostream>
#define int long long
using namespace std;
signed main()
{
   int n,a,b;
   cin>>n>>a>>b;
   if(a>=n||n%(a+1)&&a>=b||n==b+2)
      cout<<"Takahashi"<<endl;
   else
      cout<<"Aoki"<<endl;
   return 0;
}
```
注意：不开`long long`见祖宗。

---

