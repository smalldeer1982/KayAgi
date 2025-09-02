# Economy Game

## 题目描述

Kolya is developing an economy simulator game. His most favourite part of the development process is in-game testing. Once he was entertained by the testing so much, that he found out his game-coin score become equal to $ 0 $ .

Kolya remembers that at the beginning of the game his game-coin score was equal to $ n $ and that he have bought only some houses (for $ 1234567 $ game-coins each), cars (for $ 123456 $ game-coins each) and computers (for $ 1234 $ game-coins each).

Kolya is now interested, whether he could have spent all of his initial $ n $ game-coins buying only houses, cars and computers or there is a bug in the game. Formally, is there a triple of non-negative integers $ a $ , $ b $ and $ c $ such that $ a×1234567+b×123456+c×1234=n $ ?

Please help Kolya answer this question.

## 说明/提示

In the first sample, one of the possible solutions is to buy one house, one car and one computer, spending $ 1234567+123456+1234=1359257 $ game-coins in total.

## 样例 #1

### 输入

```
1359257
```

### 输出

```
YES```

## 样例 #2

### 输入

```
17851817
```

### 输出

```
NO```

# 题解

## 作者：cyffff (赞：5)

# CF681B Economy Game
[原题链接](https://www.luogu.com.cn/problem/CF681B)
## 题面
给定一个正整数 $n$ $(1<n<10^9)$ ，判断是否存在自然数 $a,b,c$ 满足 $a×1234567+b×123456+c×1234=n$。
## 思路
十分明显，这道题就是道暴力枚举的题目。~~没想到这道题是怎么上黄的。~~ 当然，直接三重循环枚举 $a,b,c$ 是否满足条件会超时，不过循环$2$次以 $a,b$ 求 $c$可否满足是可以过的。不说了，直接上代码。
****
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long//没必要开long long，数据在1e9范围内
int main(){
	LL n;
	cin>>n;
	for(LL a=0;a<=n/1234567;a++){
		for(LL b=0;b<=(n-a*1234567)/123456;b++){
			if((n-a*1234567-b*123456)%1234==0){//判断c是否可取整
				cout<<"YES";
				return 0;
			}
		}
	}
	cout<<"NO";//没找到满足条件的c
    return 0;
}
```
轻松AC，数据点最多也只用了$15ms$，整道题总用时也只有$662ms$，还是比较少时间的，排在最优解第二名，也算不错了。一道黄题就~~水~~做完了，再见qwq。

---

## 作者：orange166 (赞：2)

这是一个python题解。
##  其实这题很水
#### 题面：  
给定一个正整数 $n$ $(1<n<1e9)$， 判断是否存在自然数 $a,b,c$ 满足 $a×1234567+b×123456+c×1234=n$ .  
### 解决方法：  
直接暴力枚举即可，注意 $n^3$ 会超时。不过用 $n^2$ 的暴力加判断即可，只要拿到一种解决方案就可以输出了。 ~~不知道怎么是道黄题，建议改橙~~ 


### 代码： 

```python
import sys  #exit 的头文件
import math
a=int(input())
for i in range(0, a // 1234567 +1):   
    for j in range (0, (a-i*1234567) // 123456 +1):  #注意循环的条件
        if (a-i*1234567-j*123456) % 1234==0:
            print("YES")
            sys.exit(0) #直接结束运行
print("NO")  #如果有可行情况,已经输出并结束了

``` 
#### AC纪录：[here](https://www.luogu.com.cn/record/39194895)




---

## 作者：smoothset (赞：1)

### 水题，注意防超时，用O(n^3)会超时
**题目很简单，就是求是否存在a,b,c使得$a*1234567+b*123456+c*1234=n$成立。但如果直接枚举$a,b,c$看式子是否满足就会超时。所以，做这个题的时候只能枚举$a$和$b$，再判断$(n-(a*1234567+b*123456))$ $%$ $1234=0$ 是否成立即可。**
```cpp
#include <cstdio>
#include <cctype>
void r(int &x)
{
    x = 0;
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
}
const int house = 1234567, car = 123456, model = 1234;
int n;
int main()
{
    r(n);
    for (int i = 0;i * house <= n; i++)
        for (int j = 0;j * car + i * house <= n; j++)
            if ((n - i * house - car * j) % model == 0)
                return !printf ("YES");
    printf("NO");
    return 0;
}

```


---

## 作者：BotDand (赞：0)

# Problems
给定一个正整数$n(1<n<{10^9})$,判断是否存在自然数$a,b,c$满足$a×1234567+b×123456+c×1234=n$。
# Answer
因数据不大，可以暴力枚举$a$和$b$（$c$就不用了，$a$和$b$知道了，$c$是可以算出来的）。

确定$a$的枚举范围：$10^9÷1234567≈100$；

$b$的枚举范围：$10^9÷123456≈1000$。

然后就可以枚举啦~

但是这里要注意一点：a和b的枚举初值应该是$0$。
# Code
```pascal
var
  n:int64;
  a,b:longint;
begin
  readln(n);
  for a:=0 to 100 do for b:=0 to 1000 do//从0开始
    if n>=a*1234567+b*123456 then//判断是否比n要小
      if (n-a*1234567-b*123456) mod 1234=0 then//如果可以整除
        begin
          writeln('YES');exit;//说明有方案，退出
        end;
  writeln('NO');//无方案
end.
```

---

## 作者：yf最qhhh (赞：0)

**题意：**
找三个数 $a,b,c$ 使 $a×1234567+b×123456+c×1234=n$

**思路：**
暴力模拟！但如果写三重循环来枚举是肯定会错的，所以我们要有智慧的暴力。
用两层循环来模拟 $a$ 和 $b$ 的情况，但想一想，如果要使 $C×$ 一个数等于另一个数，那么只需要看另一个数模 $C$ 的余数是否为 $0$。

**代码：**
```cpp
#include<bits/stdc++.h>
#define rll register long long
#define ll long long
using namespace std;

int main(){
	rll n,i,j;
	scanf("%lld",&n);
	for(i=0;i<=n;i+=1234567){
		for(j=0;j<=n-i;j+=123456){//前两个数的枚举，而且j必须<=n-i，这个错害我调了好久qwq
			if((n-i-j)%1234==0)return printf("YES"),0;//余数为0直接输出YES并return 0
		}
	}
	return printf("NO"),0;//否则为NO
}

```


---

