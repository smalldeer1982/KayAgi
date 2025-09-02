# Game

## 题目描述

Two players play a game.

Initially there are $ n $ integers $ a_1, a_2, \ldots, a_n $ written on the board. Each turn a player selects one number and erases it from the board. This continues until there is only one number left on the board, i. e. $ n - 1 $ turns are made. The first player makes the first move, then players alternate turns.

The first player wants to minimize the last number that would be left on the board, while the second player wants to maximize it.

You want to know what number will be left on the board after $ n - 1 $ turns if both players make optimal moves.

## 说明/提示

In the first sample, the first player erases $ 3 $ and the second erases $ 1 $ . $ 2 $ is left on the board.

In the second sample, $ 2 $ is left on the board regardless of the actions of the players.

## 样例 #1

### 输入

```
3
2 1 3
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
2 2 2
```

### 输出

```
2```

# 题解

## 作者：Register (赞：4)

### 水题，看着大佬的解法太复杂了，我就来发个简单点的
	第一个人想让剩下的数最小，那他就擦每一次最大的
    第二个人想让剩下的数最大，那他就擦每一次最小的
    最后每次剩下的数就在中间，下图分别陈列了n为奇数还是偶数的规律：
![](https://cdn.luogu.com.cn/upload/pic/35220.png)
奉上代码：
```cpp
#include <iostream>//cin、cout需要
#include <algorithm>//sort库
using namespace std;
int main(){
    int n,a[1001];
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);//排序
    if(n%2) cout<<a[n/2+1]<<endl;//奇数
    else cout<<a[n/2]<<endl;//偶数
    return 0;
}
```

---

## 作者：开心的猪 (赞：1)

从题目可以看出，第一个人希望剩下的数字最小，于是他会擦掉剩下的中最大的那个数，同理，第二个人会擦掉最小的那个。所以说可以先预处理一下（sort）。需要注意的是：如果数字的数目是奇数，那么输出的应该是最中间的那一个，但是，由于第一个人先走，如果是偶数，将会输出最中间的那对数字中较小的那个。

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int a;
	scanf("%d", &a);
	int b[a];
	for(int i=0; i<a; i++)
	{
		scanf("%d", &b[i]);
	}
	sort(b, b+a);
	if(a%2==1)
	{
		printf("%d", b[a/2]);
	}
	else
	{
		printf("%d", b[a/2-1]);
	}
	return 0;
}
```


---

## 作者：Neoomgg (赞：1)

一道水题，根据题意模拟即可：
```python
n = int(input())
h = list(map(int, input().split()))
i = 0
while len(h) != 1:
    '''第一个人：目标——擦掉较大数，以获得较小数'''
    if i % 2 == 0:
        h.remove(max(h))
    '''第二个人：目标——擦掉较小数，以获得较大数'''
    else:
        h.remove(min(h))
    i += 1
print(h[0])

```

---

## 作者：林家三少 (赞：0)

	CF题+1
    
其实就是一个排序+判断

我们不用模拟，自己画个图就会发现：

	3
    2 1 3
    排序后：
    1 2 3
    输出第 n(3)/2+1 个
    2
    最终答案
    2
    
    再来一个
    4 
    3 1 2 4
    排序后：
    1 2 3 4
    输出第 n(4)/2 个
    2
    最终答案
    2
    
这就对了呀！

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>  //文件头
using namespace std;
int n;  //定义变量
int a[1000+10];
int main()
{
	cin>>n;  //输入
	for(int i=1;i<=n;i++)
		cin>>a[i];  //循环输入数组
	sort(a+1,a+1+n);  //排序
	if(n%2==0)  //判断奇偶
		cout<<a[n/2];  //偶就输出这个
	else
		cout<<a[n/2+1];  //奇就输出这个
	return 0;  //完美结束
}
```


---

