# Mahmoud and Ehab and the even-odd game

## 题目描述

Mahmoud和Ehab正在玩一款叫做“奇偶”的游戏。Ehab选择了一个他最喜欢的整数n然后他们开始玩这个游戏（从Mahmoud开始）在每个人的回合中，他必须选择一个数a，然后从n中减去它。

条件：

     1<=a<=n.
     如果轮到Mahmoud，a必须是偶数。
     但如果轮到Ehab，a必须是奇数。
     
如果当前的玩家不能选择任何满足条件的数字，他就会输。请输出谁获胜了。

## 说明/提示

在样例1中，Mahmoud不能选择任何一个整数，因为没有一个正偶数小于（等于）1。所以Ehab获胜了。

在样例2中，Mahmoud应当选择a为2。从n中减去2。轮到Ehab的回合了，此时n=0。因为没有小于（等于）0的正奇数，所以Mahmoud获胜了。

## 样例 #1

### 输入

```
1
```

### 输出

```
Ehab```

## 样例 #2

### 输入

```
2
```

### 输出

```
Mahmoud```

# 题解

## 作者：lukelin (赞：2)

**前言**  
很多题解都没有讲为什么这样做，所以窝来发一篇题解  

**题意简述**  
一个数n，Mahmoud珂以取(即如果取$k$，使$n = n - k$)一个正偶数，Ehab珂以取一个正奇数，一个人如果不能取了(对于Mahmoud和Ehab $n = 0$，对于Mahmoud $n = 1$)，对方就赢了。  
Mahmoud先手，问谁会赢。  

**解法**  
很简单，如果n是奇数那么Mahmoud一次铁定取不玩，因为奇数减偶数为仍为奇数，所以剩下的肯定是奇数，那么Ehab讲把它取到0必胜；如果n为偶数Mahmoud一次去玩，Ehab必败。  
简单来说，就是$n$为奇数Ehab胜，否则Mahmoud胜  

**代码**  
```cpp
#include <cstdio> 
#define ll long long

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int main(){
    ll n = read();
    if (n == 0)
        printf("Ehab");
    else if(n & 1)
        printf("Ehab");
    else
        printf("Mahmoud");
    return 0;
}
```

---

## 作者：小闸蟹 (赞：1)

```cpp
// 这一题真的是入门难度无疑了
// 只要判断输入的数的奇偶性就好了
// 若是奇数，则后手赢；若是偶数，则先手赢
#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    if (n % 2 == 1)
    {
        std::puts("Ehab");
    }
    else
    {
        std::puts("Mahmoud");
    }

    return 0;
}
```

---

## 作者：RioBlu (赞：0)

这一题可以说是判断奇偶数

## Python2
```
a=input()
b=a%2
if b==0:
    print "Mahmoud"
if b==1:
    print "Ehab"
```
## C++
```
#include <bits/stdc++.h>
using namespace std;
long long a;
int main()
{
	cin>>a;
	if(a%2==1)//a mod 2 是不是1
	cout<<"Ehab"<<endl;
	else//否则
	cout<<"Mahmoud"<<endl;
	return 0;
}
```
## Pascal
```
var
n:integer;
begin
   readln(n);
   if n mod 2 = 0 then
   write('Mahmoud')
   else
   write('Ehab');
   readln;
end.
```

---

## 作者：applese (赞：0)

这是一道入门题目吧（恶意评分让这道题目上了普及，但是还是让我来解释解释吧QAQ

不过令我震惊的是：
```
为什么UKE啊啊啊啊啊
```

好吧，那还是进入正题：

观点：

首先：一个数不是偶数就是奇数（所以只需要一个if和else即可QAQ

第二：只有能被2整除的才可以是偶数QAQ

第三：实现程序：
```
#include<iostream>
using namespace std;
int main()
{
    long long a;    //定义
    cin>>a;
    if(a%2==0) cout<<"Mahmoud";    //判断并按照要求输出
    else cout<<"Ehab";
    return 0;
}
```

题解可能几乎相同，但是我的解法可能稍有**详细和简略**，若有疑问，请在**右侧**发表，谢谢QAQ

---

