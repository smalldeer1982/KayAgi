# Lucky?

## 题目描述

A ticket is a string consisting of six digits. A ticket is considered lucky if the sum of the first three digits is equal to the sum of the last three digits. Given a ticket, output if it is lucky or not. Note that a ticket can have leading zeroes.

## 说明/提示

In the first test case, the sum of the first three digits is $ 2 + 1 + 3 = 6 $ and the sum of the last three digits is $ 1 + 3 + 2 = 6 $ , they are equal so the answer is "YES".

In the second test case, the sum of the first three digits is $ 9 + 7 + 3 = 19 $ and the sum of the last three digits is $ 8 + 9 + 4 = 21 $ , they are not equal so the answer is "NO".

In the third test case, the sum of the first three digits is $ 0 + 4 + 5 = 9 $ and the sum of the last three digits is $ 2 + 0 + 7 = 9 $ , they are equal so the answer is "YES".

## 样例 #1

### 输入

```
5
213132
973894
045207
000000
055776```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：5k_sync_closer (赞：4)

# 题意
给你 $n$ 个六位数，对于每一个六位数，问它的 前三位之和 与 后三位之和 是否相等。

这 $n$ 个六位数中，可能存在一些六位数带前导零。
# 思路
模拟即可，可以把每个六位数单字符读入，

判断读到的 前三个数字之和 与 后三个数字之和 是否相等。

```cpp
int g() //读入一位数字
{
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    return c - '0';
}
```
# 代码
```cpp
#include <cstdio>
int g()
{
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    return c - '0';
}
int T, a, b;
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        a = g() + g() + g();
        b = g() + g() + g();
        puts(a == b ? "YES" : "NO");
    }
    return 0;
}
```


---

## 作者：mxtx (赞：3)

# 题目大意
给你 $t$ 个由六个数字组成的六位号码，如果这个号码前三位的和等于后三位的和，输出 `yes` ，否则输出 `no` 。 ~~盲猜红题~~

# 思路
只要把这堆号码当整数读入，然后用位值原理把号码的六位都剥离，再判断一下就行了。看一下数据范围， $t\le 1000$ ，很好，不用开 long long 。

# Code
码风不好看请谅解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tikcet_number;//别问我为什么是tikcet_number，问就是打错了，后面懒得改了
int main()
{
    scanf("%d",&n); //t你总得读入吧
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&tikcet_number);
        int g,s,b,q,w,sw; //个、十、百、千、万、十万
        g=tikcet_number%10;
        s=(tikcet_number/10)%10;
        b=(tikcet_number/100)%10;
        q=(tikcet_number/1000)%10;
        w=(tikcet_number/10000)%10;
        sw=tikcet_number/100000;
        //六位一个一个剥离
        if(g+s+b==q+w+sw)//慢慢判断
        {
            printf("yes\n");
        }
        else
        {
            printf("no\n");
        }
    }
    return 0;//好习惯
}
```

---

## 作者：Engulf (赞：2)

给定长度 $6$ 的字符串 $s$，判断 $s$ 的前三个数字和后三个数字的和是否相等。

```cpp
// author: TMJYH09
// create time: 2022/05/10 22:45:24
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int s1=0;
        for(int i=0;i<s.size();i++){
            if(i<3)s1+=s[i]-'0';
            else s1-=s[i]-'0';
        }
        cout<<(s1==0?"YES\n":"NO\n");
    }
    return 0;
}
```

---

## 作者：ttq012 (赞：0)

**SOLUTION**

提供一个字符串哈希做法。

我们将前三个数的和看做字符串的第一个数，后三个数的和看做字符串的第二个数，然后直接跑字符串哈希，求区间 $[1, 1]$ 和区间 $[2, 2]$ 的区间哈希和即可。

**AC CODE**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unsigned long long ull;
ull bit[10], h[10];
const int base = 13331;

ull get(int x, int y) {
    return h[y] - (h[x - 1] - 1) * bit[y - x + 1];
}

signed main() {
    int T;
    cin >> T;
    while (T --) {
        char S[10];
        scanf ("%s", S + 1);
        int s[3];
        s[1] = S[1] + S[2] + S[3];
        s[2] = S[4] + S[5] + S[6];
        h[0] = bit[0] = 1;
        for (int i = 1; i <= 2; i ++)
            h[i] = h[i - 1] * base + s[i];
        for (int i = 1; i <= 2; i ++)
            bit[i] = bit[i - 1] * base;
        ull l = get(1, 1);
        ull r = get(2, 2);
        if (l == r)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}


```


---

## 作者：OLE_OIer (赞：0)

这道题很简单。根据题意模拟即可。

为了避免在整型变量中的复杂计算，我们使用字符串来实现。实现步骤是这样的：

1. 先输入字符串。
2. 将字符串的 $6$ 位字符开数组存储。
3. 判断前三位之和是否等于后三位之和。之后输出。

代码附上：
```cpp
//CF1676A Lucky?
#include<bits/stdc++.h>
#define int long long
#define elif else if
using namespace std;
void func(){
	string c;
	int a[10];//存储六个数字
	cin>>c;
	for(int i=0;i<=5;++i) a[i+1]=c[i]-'0';//将六个数字转为整型变量
	if(a[1]+a[2]+a[3]==a[4]+a[5]+a[6]) cout<<"YES\n";//判断并输出。
	else cout<<"NO\n";
}
signed main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=1;i<=n;++i) func();
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

简单题。

只需要读入一个字符串，求这个字符串的前三位的和和后三位的和，然后判断两个字符串是否相等即可。

时间复杂度 $\mathcal O(T)$。

```python
T = int(input())
for _ in range(0, T):
    s = input()
    a = 0
    b = 0
    for i in range(0, 3):
        a += int(s[i])
    for i in range(3, 6):
        b += int(s[i])
    if (a == b):
        print("YES")
    else:
        print("NO");

```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

根据题意直接比较即可。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
char a[10];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",a+1);
		int n1=(a[1]-'0')+(a[2]-'0')+a[3]-'0';//前三位数之和
		int n2=(a[4]-'0')+(a[5]-'0')+a[6]-'0';//后三位数之和
		printf(n1==n2?"YES\n":"NO\n");
	}
	return 0;
}

```


---

