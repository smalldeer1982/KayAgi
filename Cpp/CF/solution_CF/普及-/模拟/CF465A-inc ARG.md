# inc ARG

## 题目描述

Sergey is testing a next-generation processor. Instead of bytes the processor works with memory cells consisting of $ n $ bits. These bits are numbered from $ 1 $ to $ n $ . An integer is stored in the cell in the following way: the least significant bit is stored in the first bit of the cell, the next significant bit is stored in the second bit, and so on; the most significant bit is stored in the $ n $ -th bit.

Now Sergey wants to test the following instruction: "add $ 1 $ to the value of the cell". As a result of the instruction, the integer that is written in the cell must be increased by one; if some of the most significant bits of the resulting number do not fit into the cell, they must be discarded.

Sergey wrote certain values ​​of the bits in the cell and is going to add one to its value. How many bits of the cell will change after the operation?

## 说明/提示

In the first sample the cell ends up with value $ 0010 $ , in the second sample — with $ 0000 $ .

## 样例 #1

### 输入

```
4
1100
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1111
```

### 输出

```
4
```

# 题解

## 作者：Ryan_Yu (赞：4)

此题是一道大模拟水题。

先定义一个变量 $flag$ ，用以判断是否进位了。

注意： $flag$ 需先置为 $1$ ，因为一开始需先加上 $1$ 。

然后进行判断：

当 $a_i$ 本身就为 $1$ 并且 $flag$ 等于 $1$ 时， $ans\gets ans+1$ 。$flag$ 仍为 $1$ （因为是连续进位）。

当 $a_i$ 本身就为 $0$ 并且 $flag$ 等于 $1$ 时，  $ans\gets ans+1$ 同时跳出循环。

遇到其他情况直接跳出循环即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,ans,flag;string a;
//flag变量既可以是int型，也可以是bool型。
int main()
{
    cin>>n>>a;
    flag=1;
    for(i=0;i<n;i++)
        {
            if(a[i]=='1'&&flag==1)
                {
                    ans++;
                    a[i]=0;
                }
            else if(a[i]=='0'&&flag==1)
                {
                    ans++;
                    break;
                }
            else
                break;
        }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：Fcersoka (赞：3)

~~我也来水一篇题解 ！~~  
题目应该都能看懂 ，这里便不再作解释 。  
首先 ，我们知道二进制数上的每一位只能是 $0$ 或 $1$,二进制是逢 $2$ 进一位的 ，所以 ，要想当前数位改变 ，后一位必须是 $1$。接下来就好办了 ，从低位一直枚举到高位 ，如果是 $1$，答案就累加 ，只要枚举到 $0$ 了 ，就结束循环 。  
这里还有一点要注意 ，就是改变了不在这个数上的数位 ，是不算改变了的 。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[101],s=1,ans=1;
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		scanf("%1d",&a[i]);//只读入一位
	}
	while(a[s]) {
		ans++;//答案累加
		s++;
	}
	if(ans>n) {//如果改变了其它数位是不算的
		cout<<n;
	} else
		cout<<ans<<endl;
	return 0;
}
```
感谢您的观看 ，再见 ！

---

## 作者：Chtholly_L (赞：0)

### 题意：

给你一个**倒序**的二进制数，问它加一后有多少位变化了。

---

### 分析：

二进制的加法和十进制一样，只不过把满十进一改为了满二进一，举个例子：

$1100_{(2)}+1=1101_{(2)}$

$1101_{(2)}+1=1110_{(2)}$

由此我们可以发现，从最后一位往前扫，如果是一就变成零，如果是零就变成一，然后停止。

据此我们可以定义一个计数器，从最后一位开始往前扫（由于题目的原因，我们按照输入顺序，从前往后扫就可以了），依次枚举每一位。计数器先加一，如果这一位是一，就继续循环，否则跳出循环。

注意坑点：

1. 输入的为倒序，那么如果输入 $1100$，那么实际上就是 $0011$。因此我们直接从字符串开头开始向后扫。

2. 如果加一后多了一位就输出原来的长度。例如 $1111_{(2)}+1=10000_{(2)}$，输出 $4$。

---

### 代码：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int main(){
    string s;
    int n;
    cin>>n>>s;
    int cnt=0;  //计数器
    for(int i=0;i<n;i++){
        cnt++;
        if(s[i]=='1'){
            continue;
        }
        else{
            break;
        }
    }
    cout<<cnt<<endl;
    return 0;
}
```


---

## 作者：atarashiTLE (赞：0)

### 思路：
发现它是二进制数，考虑暴力模拟，可以通过，不提供代码。

考虑另一种做法。看一眼前面的模拟：
![](https://cdn.luogu.com.cn/upload/image_hosting/176ehj8m.png)

发现变化的只是最前面的所有 $1$。于是发现可以一遍`while`循环找到答案（答案最后加一（进位）即可）。

- code:
```cpp
#include <iostream>
#include <string>
#define int long long
using namespace std;
string c;
signed main()
{
    cin >> c >> c;
    int ans = 0;
    while (c[ans] == '1' && ans < c.size())
        ans++;
    if (ans >= c.size())
        ans--;
    cout << ans + 1 << endl;
    return 0;
}
```

完结撒花![qq_emoji: cy](https://xn--9zr.tk/cy)

---

## 作者：tribool4_in (赞：0)

这题本质上就是让你求一个倒过来的二进制数 $+1$ 会有几个位置的数会发生变化，注意增加一位不算！

考虑对于某一位加 1，它一定会变化，如果这位数为 1，则它还会进位，就是将下一位加 1，所以可以计算从开头开始连续的 1 的个数，记为 ```cnt```，如果 ```cnt==n``` 即全为 1，则变化个数为 ```n```，否则除了开头连续的 1 会变化以外，还会在后面进一位，则答案为 ```cnt+1```。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, cnt = 0;
char s[1000];
int main() {
	scanf("%d%s", &n, s);
	for (int i = 0; i < n; i++) {
		if (s[i] == '1') cnt++;
		else break;
	}
	if (cnt == n) cout << cnt << endl;
	else cout << cnt + 1 << endl;
	return 0;
}

```


---

## 作者：奥斯卡小冰人 (赞：0)

这道题首先读入这些数，将 $string$ 类型转换为 $int$ ，然后将第一个数 $+1$ ，随后循环累加变化的和。因为从左到右为从低到高，所以循环直接从 $0$ 到 $n-1$ 即可。

$AC$ 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string t;
    int n,sum = 0,f[100];
    cin >> n;
    cin >> t;
    for(int i = 0;i < n;i++) f[i] = t[i] - 48;
    f[0]++;//最低位+1
    for(int i = 0;i < n;i++) 
    {
        if(f[i] > 1) f[i] = 0,f[i + 1]++;//如果有进位 则进位
        if(f[i] != t[i] - 48) sum++;//如果有变化 + 1
        else break;//如果没变化则表示没有进位 这样的话后面也不会变化 退出循环
    }
    cout << sum;
    return 0;
}
```


---

## 作者：codemap (赞：0)

一道很简单的水题

本质上就是给你一个倒过来的二进制数

然后将这个数+1,求有几个位置的数会发生变化

可以很简单的考虑一下:

若一个位置+1,若它是1,则会变化,且会进位

若它是0,则会变化,但不会进位,所以在它之后的位置都不会+1,也不会变化

所以第一个0出现的位置即为答案

所以只要从从第一位往后枚举,若是1,则继续,若是0,则输出当前位置,结束程序

这里还要注意一下若没有0,要在最后输出n

上代码
```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,i;
    string a;
    cin>>n>>a;
    for(i=0;i<n;i++)//string是从0到n-1位
        if(a[i]=='0')//如果当前位是0
        {
            cout<<i+1;//注意,以为是从0开始,所以要输出i+1
            return 0;//直接终止程序
        }
    cout<<n;//如果运行到这里说明没有0,直接输出n
    return 0;
}
```
# 请勿抄袭

---

## 作者：hanyuchen2019 (赞：0)

我的思路有一些投机取巧=.=

随便弄几个例子：

```
0101==>1101 ans=1 无进位
1010==>0110 ans=2 最前面有一个1
1101==>0011 ans=3 有两个1，因进位变了3个数
1111==>0000 ans=4 都是1，但就像样例2一样，多出的一位不考虑（坑）
```
我们就会发现，最终的答案完全取决于最前面数字 $1$ 的个数。

极简代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int n,ans;string s;
	cin>>n>>s;
    
	for(ans=0;ans<n&&s[ans]=='1';ans++);//从头找1的数量
 
	if(ans==n)cout<<ans;//特判全1的情况
	else cout<<ans+1;//否则输出1的数量+1，因为后面的一个0会变成1
 	return 0;
}

```

---

