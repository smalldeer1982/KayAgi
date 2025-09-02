# Ehab Is an Odd Person

## 题目描述

You're given an array $ a $ of length $ n $ . You can perform the following operation on it as many times as you want:

- Pick two integers $ i $ and $ j $ $ (1 \le i,j \le n) $ such that  $ a_i+a_j $ is odd, then swap $ a_i $ and $ a_j $ .

What is lexicographically the smallest array you can obtain?

An array $ x $ is [lexicographically smaller](https://en.wikipedia.org/wiki/Lexicographical_order) than an array $ y $ if there exists an index $ i $ such that $ x_i<y_i $ , and $ x_j=y_j $ for all $ 1 \le j < i $ . Less formally, at the first index $ i $ in which they differ, $ x_i<y_i $

## 说明/提示

In the first example, we can swap $ 1 $ and $ 4 $ since $ 1+4=5 $ , which is odd.

## 样例 #1

### 输入

```
3
4 1 7
```

### 输出

```
1 4 7 ```

## 样例 #2

### 输入

```
2
1 1
```

### 输出

```
1 1 ```

# 题解

## 作者：宁_缺 (赞：7)

## 今天发的第三篇题解...
不要觉得我奇怪，我还奇怪为啥CF题咋题解这么少，而且还长...于是就想着发一个短些的
#### 感觉这种水题也没啥好推导的，直接说做法吧：
看序列的奇偶，全是奇或全是偶直接输出，否则排序输出，好像也没别的了。。。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100001];
int main(){
	bool o=0,j=0;cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i],((a[i]&1)?j:o)=1;
	if(o&&j)sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：CircleOO (赞：6)

不难发现，这道题目是涉及到字典序最小的序列问题。这种情况下，我们可以考虑使用排序：如果我们把这个序列从小到大排序，那么这种情况下的字典序一定是最小的。

但是，由于题干中给了一个限制条件（和为奇数的一对数才可以交换），我们似乎并不能把每一个元素放在一个位置，也就不一定能实现排序了。

我们可以先从特殊情况入手：

**如果这个序列中所有数字奇偶性相同**（即任意两数之和一定为偶数），我们**无法进行任何的交换**。因此，我们需要把序列按原样输出。


**如果这个序列中既出现了奇数，又出现了偶数**（即存在至少一对数之和为奇数），该怎么做呢？**事实上，我们可以对任意两个数进行交换。**

证明：对于一对和为奇数的数，能够直接交换。

对于一对和为偶数的数，一定能够找到一个和这两个数奇偶性都不相同的数，三者进行轮换。

例如:

[a,b,c]，a和b都为偶数，c为奇数

[c,b,a]，此时交换了c和a

[b,c,a]，此时交换了b和c

[b,a,c]，此时交换了a和c。可以看到，我们完成了两者之间的交换。

可以看到，在这种情况下，由于我们可以对于任何一对数进行交换，我们可以直接对于这个序列进行排序，也就能得到字典序最小的序列了。

下面附上代码：


```cpp
#include <bits/stdc++.h>
//本题目的解题思路：
// 如果一个数组中所有的元素的奇偶性相同，就不能进行任何替换
// 如果一个数组中两种奇偶性都出现过，那么可以交换任意两个数
// 证明：对于任意的两个数a,b，如果奇偶性不同，可以直接交换
// 如果奇偶性相同，则找到一个奇偶性和它们都不同的c，a,b,c轮换
using namespace std;
const int MAXN=1e5+10;
int n;
int arr[MAXN];
bool hasOdd=false,hasEven=false;//是否出现奇数，是否出现偶数 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
		if(arr[i]%2==0)hasEven=true;
		else hasOdd=true;
	}
	if(hasOdd^hasEven){//如果只出现了一个，就按照原样输出 
		for(int i=1;i<=n;i++){
			cout<<arr[i]<<" ";
		}
	}else{//否则排序后输出 
		sort(arr+1,arr+n+1);
		for(int i=1;i<=n;i++){
			cout<<arr[i]<<" "; 
		}
	}
	return 0;
}
```



一点感悟：这道题的题面很具有迷惑性，有一定的思维难度，但是想清楚了以后代码难度并不高。个人认为做这种题目，多猜想或许是个不错的方法（比如这题，可以想想能不能把数换到任意位置）。


---

## 作者：Rulu (赞：3)

分析
------------
#### 根据奇偶性求解。

由题可知，数列中相邻两数相加为奇数。就将它们交换。
其实这一过程就是在进行排序。  
排序条件就是相加为奇数。   

根据以下公式:  

 >  $a=$   奇数  
   $b=$   偶数  
   $a+b=a$  
   $a+a=b$  
   $b+b=b$    

#### 可得：
 
 两数相加为奇数：这两数必一奇一偶，需排序输出。

 其余情况（两数相加为偶数）：两奇，两偶，需直接输出。
 
 
 代码
------------
```
#include<bits/stdc++.h>
using namespace std;
int a[1000001];
int main()
{
	int n;
	cin>>n;
	bool b=0;
	bool c=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//n个数 
		if(a[i]%2==0)//判断奇偶性 
		{
			b=1;//偶 
		}
		else
		{
			c=1;//奇 
		}
	}
	if(b==1&&c==1)//一奇一偶 
	{
		sort(a+1,a+n+1);//排序 
	}
	//两奇，两偶，无需排序  
	for(int i=1;i<=n;i++)
	{
		cout<<a[i]<<" ";//输出 
	}
	return 0; 
}
```


---

## 作者：TLMPEX (赞：1)

~~其实这道题很水。~~

思路：如果既有偶数又有奇数，则排序输出。如果只有偶数没有奇数或者只有奇数没有偶数那就不能交换，只能直接输出原序列。

代码。
```c
#include<bits/stdc++.h>
using namespace std;
int k[100001];
int main(){
	int n,i,a=0,b=0;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>k[i];
		if(k[i]%2==0)b=1;//如果有偶数，则b标记为1
		else a=1;//否则为奇数，a标记为1
	}
	if(a&&!b||b&&!a){//如果只有偶数或只有奇数，那就直接输出原序列
		for(i=1;i<=n;i++)
			cout<<k[i]<<" ";
	}
	else{//否则排序后在输出
		sort(k+1,k+n+1);
		for(i=1;i<=n;i++)
			cout<<k[i]<<" ";
	}
}
```


---

## 作者：OoXiao_QioO (赞：0)

这是 $\verb!CF!$ 不能交题以来我的第一份题解。

# 思路

做这道题之前，我们需要了解一些小学学习的关奇偶数的知识，即

- 奇数 $+$ 奇数 $=$ 偶数。

- 偶数 $+$ 偶数 $=$ 偶数。

- 奇数 $+$ 偶数 $=$ 奇数。

而且题目说明了相邻两个数相加为奇数才能进行交换，而两个数相加为奇数的只有奇数 $+$ 偶数 $=$ 奇数这一种方法，所以我们就可以来判断这个序列里面是否存在奇数和偶数就可以了，因为不管只有偶数还是只有奇数，怎么都找不出来相加为奇数的两个数，所以这种情况只能输出原序列，而同时出现偶数和奇数的时候，就可以交换这两个数，交换一次又一次，最后得到的序列的字典序肯定最小，输出一下就可以了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int odd,even,i,n,a[10001];
    cin>>n;
    odd = even = 0;//初始都没有出现奇数和偶数
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]%2)
            odd = 1;//找到奇数了。
        else
            even = 1;//找到偶数了。
    }
    if(odd^even)//用异或的方法判断有没有出现奇数和偶数，大家都知道在异或中，相同为 0，不同为 1，所以这里假设的就是没有出现偶数和奇数的一种方案。
    {
        for(i=1;i<=n;i++)//因为不能交换，所以输出一下原序列就可以了。
            printf("%d ",a[i]);
        return 0;
    }
    //否则就是出现了奇数和偶数。
    sort(a+1,a+1+n);//先给序列排个序。
    for(i=1;i<=n;i++)//从小到大输出。
        printf("%d ",a[i]);
    return 0;
}
```


---

## 作者：清清老大 (赞：0)

## 思路

两个数相加为奇数，则两数必为一奇一偶。

如果全是奇数或偶数，那么没法移动，输出原数列。

如果既有奇数也有偶数，那么如果想交换两个偶数，可以通过其中的一个奇数来交换，如果想交换两个奇数，可以通过其中的一个偶数来交换，相当于可以随便交换。因为从小到大排列的数字典序最小，所以直接排序后输出。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,a[110101];

int main()
{
    bool odd = 0,even = 0;
    cin >> n;
    for(int i = 0;i < n;i ++)
    {
        scanf("%d",&a[i]);
        if(a[i] % 2)
        {
            odd = 1;
        }
        else
        {
            even = 1;
        }
    }
    if(odd && even)
    {
        sort(a,a + n);
    }
    for(int i = 0;i < n;i ++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
```


---

## 作者：ModestCoder_ (赞：0)

感性理解得到一个超级大结论：如果存在两个数奇偶性不同，整个数列就能排序；否则直接输出

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
using namespace std;
int n, x, a[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	n = read();
	a[1] = read();
	for (int i = 2; i <= n; ++i) a[i] = read(), x |= ((a[1] + a[i]) & 1);
	if (x) sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
	return 0;
}
```


---

