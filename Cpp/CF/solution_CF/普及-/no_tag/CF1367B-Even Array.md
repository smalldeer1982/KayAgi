# Even Array

## 题目描述

You are given an array $ a[0 \ldots n-1] $ of length $ n $ which consists of non-negative integers. Note that array indices start from zero.

An array is called good if the parity of each index matches the parity of the element at that index. More formally, an array is good if for all $ i $ ( $ 0 \le i \le n - 1 $ ) the equality $ i \bmod 2 = a[i] \bmod 2 $ holds, where $ x \bmod 2 $ is the remainder of dividing $ x $ by 2.

For example, the arrays \[ $ 0, 5, 2, 1 $ \] and \[ $ 0, 17, 0, 3 $ \] are good, and the array \[ $ 2, 4, 6, 7 $ \] is bad, because for $ i=1 $ , the parities of $ i $ and $ a[i] $ are different: $ i \bmod 2 = 1 \bmod 2 = 1 $ , but $ a[i] \bmod 2 = 4 \bmod 2 = 0 $ .

In one move, you can take any two elements of the array and swap them (these elements are not necessarily adjacent).

Find the minimum number of moves in which you can make the array $ a $ good, or say that this is not possible.

## 说明/提示

In the first test case, in the first move, you can swap the elements with indices $ 0 $ and $ 1 $ , and in the second move, you can swap the elements with indices $ 2 $ and $ 3 $ .

In the second test case, in the first move, you need to swap the elements with indices $ 0 $ and $ 1 $ .

In the third test case, you cannot make the array good.

## 样例 #1

### 输入

```
4
4
3 2 7 6
3
3 2 6
1
7
7
4 9 2 1 18 3 0```

### 输出

```
2
1
-1
0```

# 题解

## 作者：Cult_style (赞：2)

题目大意：给你$n$个数，$a$[$0$…$n$-1],要使第$a_i$和$i$的奇偶性相同，你可以将两个数互换位置，问最少的互换次数是多少，如果无法实现，输出$-1$。

首先，判断$a_i$和$i$的奇偶性是否相等，如果不相等，分两种情况判断：

- $i$%$2$==$1$ $a$++
- $i$%$2$==$0$ $b$++

做到这两步，就统计出了要和奇数交换的($a$)和要和偶数交换的($b$)，那么如果$a$==$b$那就可以，输出$a,b$之一即可，如果$a$!=$b$，输出"-1"
```
#include<bits/stdc++.h>
using namespace std;
int t;
int n,c;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int a=0,b=0; 
		for(int i=1;i<=n;i++){
			scanf("%d",&c);
			if(c%2!=(i-1)%2) ((i-1)%2==1)?a++:b++;
		}
		int x=n/2,y=0;
		(n%2==0)?y=n/2:y=n/2+1;
		(a==b)?printf("%d\n",a):printf("-1\n"); 
	}
	
	return 0;
}
```


---

## 作者：liuyongle (赞：1)

#### 思路分析

将索引的奇偶校验与元素的奇偶校验不匹配的所有位置都分成两个数组。 如果偶数索引中有奇数，则将此索引添加到 $e$ （even）数组中。否则，如果奇数索引中有偶数，则将此索引添加到 $o$ （odd）数组中。注意，如果 $o$ 和 $e$ 数组的大小不相等，则没有答案。 否则，可以通过精确执行 $|o|$ 来使数组变“好”。 只需交换 $o$ 和 $e$ 数组中的所有元素即可完成操作。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
using ld = long double;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    int a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x % 2 != i % 2) {
            if (i % 2 == 0) {
                a++;
            } else {
                b++;
            }
        }
    }
    if (a != b) {
        cout << -1 << endl;
    } else {
        cout << a << endl;
    }
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        solve();
    }
}
```

---

## 作者：PeaceSunset (赞：0)

这道题是一道非常简单的**思维题**。

#### 思路：

当 $a_i$ 的奇偶性与 $i$ 的奇偶性不同时，接下来有两种情况：

- $i$ 为奇数。

- $i$ 为偶数。

我们设置两个变量 $ji$、$ou$，分别表示以上两种情况出现的次数。

那么当 $ji=ou$ 时，说明是可以一一替换的，所以替换次数就是 $ji$ 或者 $ou$ 二者任选其一。

反之，当 $ji \neq ou$ 时，说明没办法进行两两替换，那么输出 $-1$ 即可。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int ji=0,ou=0;
		for(int i=1;i<=n;i++){
			cin>>a;
			if(a%2!=(i-1)%2){
				if(a%2)ji++;
				else ou++;
			}
		}
		if(ji==ou)cout<<ji<<"\n";
		else cout<<"-1\n";
	}
	return 0;
} 
```


---

## 作者：Yh0326 (赞：0)

思路很简单。

直接求出错位的奇数偶数各有多少，若不相等则输出 $-1$ ,否则输出错位的奇数个数。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[50];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int c0=0,c1=0;
        for(int i=0;i<n;++i){
            scanf("%d",a+i);
            if((a[i]&1)!=(i&1)){
                if((a[i]&1)){
                    ++c1;
                }
                else ++c0;
            }
        }
        if(c1!=c0){cout<<"-1\n";}
        else{
            cout<<c1<<'\n';
        }
    }
}
```
管理员大大求过！

---

## 作者：dead_X (赞：0)

# 题意
给定 $n$ 个数，问能不能交换一些数，使每个数与自己的位置关于 $2$ 同余，能则输出最小交换次数。
# 思路
贪心。

1. 如果所有数的**奇偶数**个数与序列中所有位置的**奇偶数**个数不相等，肯定不能。

证明：如果能，最后每个数模 $2$ 的值一定与它的位置相等。

2. 如果一个数已经满足了要求，那么这个数一定不会移动。

证明：
* 如果这个数移动之后也满足要求，那么这个移动什么也没有改变。
* 如果这个数移动之后不满足要求，那它还要再移一次，显然浪费。

综上，每一次移动一定是将两个不满足并且交换后满足的两个数交换。

实现十分简单，找到**奇数位上为偶数的数**的个数，然后再找到**偶数位上为奇数的数**的个数，一样就输出，不一样就无解。
# 代码
```
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003];
using namespace std;
int main()
{
	int T=read();
	while(T--)
	{
		int n=read(),x=0,y=0;
		for(int i=0; i<n; i++) if((read()-i)&1) if(i&1) x++; else y++;
		if(x!=y) puts("-1"); else printf("%d\n",x);
	}
	return 0;
}
```

---

## 作者：registerGen (赞：0)

# Solution

首先把那些 $a_i\bmod2\ne i\bmod2$ 的元素拿出来。

考虑在这些元素中任取两个，如果这两个元素下标模 $2$ 不同，则交换后这两个元素将都符合要求，否则交换后这两个元素将都 **不** 符合要求。

于是我们记录 $cnt_1,cnt_2$，分别表示 $a_i\bmod2\ne i\bmod2\land i\bmod2=1$ 的元素个数和 $a_i\bmod2\ne i\bmod2\land i\bmod2=0$ 的元素个数。

若 $cnt_1\ne cnt_2$，则无解；否则答案为 $cnt_1$（至少交换这么多次）。

# Code

```cpp
#include<cstdio>
#include<algorithm>

const int N=40;

int a[N+10],n;

inline void work()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	int cnt1=0,cnt2=0;
	for(int i=0;i<n;i++)
		if(a[i]%2!=i%2)
		{
			if(i%2==0)cnt1++;
			else cnt2++;
		}
	if(cnt1==cnt2)printf("%d\n",cnt1);
	else puts("-1");
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)work();
	return 0;
}
```

---

