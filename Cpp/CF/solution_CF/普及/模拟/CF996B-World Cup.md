# World Cup

## 题目描述

Allen wants to enter a fan zone that occupies a round square and has $ n $ entrances.

There already is a queue of $ a_i $ people in front of the $ i $ -th entrance. Each entrance allows one person from its queue to enter the fan zone in one minute.

Allen uses the following strategy to enter the fan zone:

- Initially he stands in the end of the queue in front of the first entrance.
- Each minute, if he is not allowed into the fan zone during the minute (meaning he is not the first in the queue), he leaves the current queue and stands in the end of the queue of the next entrance (or the first entrance if he leaves the last entrance).

Determine the entrance through which Allen will finally enter the fan zone.

## 说明/提示

In the first example the number of people (not including Allen) changes as follows: $ [\textbf{2}, 3, 2, 0] \to [1, \textbf{2}, 1, 0] \to [0, 1, \textbf{0}, 0] $ . The number in bold is the queue Alles stands in. We see that he will enter the fan zone through the third entrance.

In the second example the number of people (not including Allen) changes as follows: $ [\textbf{10}, 10] \to [9, \textbf{9}] \to [\textbf{8}, 8] \to [7, \textbf{7}] \to [\textbf{6}, 6] \to \\ [5, \textbf{5}] \to [\textbf{4}, 4] \to [3, \textbf{3}] \to [\textbf{2}, 2] \to [1, \textbf{1}] \to [\textbf{0}, 0] $ .

In the third example the number of people (not including Allen) changes as follows: $ [\textbf{5}, 2, 6, 5, 7, 4] \to [4, \textbf{1}, 5, 4, 6, 3] \to [3, 0, \textbf{4}, 3, 5, 2] \to \\ [2, 0, 3, \textbf{2}, 4, 1] \to [1, 0, 2, 1, \textbf{3}, 0] \to [0, 0, 1, 0, 2, \textbf{0}] $ .

## 样例 #1

### 输入

```
4
2 3 2 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
10 10
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6
5 2 6 5 7 4
```

### 输出

```
6
```

# 题解

## 作者：Siteyava_145 (赞：3)

第一眼模拟，但是感觉可以优化一下。

# 思路：

处理出每一个数会在第几轮变为 $0$，再取最小值。在最小值的前提下位置位置要保证是最靠前的（会先被走到）

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],ans[100005];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        ans[i]=(a[i]-i+n)/n;//第几轮会变为0，(也就是数值 - 离1号的距离 + 1 + n)/2
    }
    int minn=0x7fffffff,pos;
    for(int i=1;i<=n;i++){
        if(ans[i]<minn){//注意是<，不是<=
            minn=ans[i];
            pos=i;
        }
    }
    cout<<pos;
}
```

好像是最优解。

---

## 作者：andyli (赞：2)

注意到 CF 自带 O2 优化，因此直接按题意模拟即可。  
记录减量 $t$ ，为当前经过的分钟数，再用 $a_i-t$ 即可得到当前队列真实的人数。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
const int maxn = 100005;

int A[maxn];
int main() {
    int n;
    io.read(n);
    for (int i = 1; i <= n; i++)
        io.read(A[i]);
    int p = 1, t = 0;
    while (A[p] - t > 0) {
        p++;
        t++;
        if (p > n)
            p = 1;
    }
    writeln(p);
    return 0;
}
```

---

## 作者：wanghanjun (赞：0)

看到这道题，首先想到的是暴力枚举，然而会TLE。。。

但其实我们是可以用O(1)的效率算出来一个点在多久后变成0的，所以就好办了，我们只需要找到Allen可走的圈数最少的点即可(如果有重复当然选靠前的一个了)

放代码：
```
#include <iostream>
using namespace std;

const int MAXN=100005;
int a[MAXN],n,x,mina=0x3f3f3f3f,id;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		a[i]=(x-i+n)/n;
                //Allen最多走到这个点上几次
	}
	for(int i=1;i<=n;i++){
		if(mina>a[i]){
			id=i;
			mina=a[i];
                        //找最小值
		}
	}
	cout<<id<<endl;
	return 0;
}
```

---

