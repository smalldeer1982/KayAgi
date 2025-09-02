# Little Robber Girl's Zoo

## 题目描述

Little Robber Girl likes to scare animals in her zoo for fun. She decided to arrange the animals in a row in the order of non-decreasing height. However, the animals were so scared that they couldn't stay in the right places.

The robber girl was angry at first, but then she decided to arrange the animals herself. She repeatedly names numbers $ l $ and $ r $ such that $ r-l+1 $ is even. After that animals that occupy positions between $ l $ and $ r $ inclusively are rearranged as follows: the animal at position $ l $ swaps places with the animal at position $ l+1 $ , the animal $ l+2 $ swaps with the animal $ l+3 $ , ..., finally, the animal at position $ r-1 $ swaps with the animal $ r $ .

Help the robber girl to arrange the animals in the order of non-decreasing height. You should name at most $ 20000 $ segments, since otherwise the robber girl will become bored and will start scaring the animals again.

## 说明/提示

Note that you don't have to minimize the number of operations. Any solution that performs at most $ 20000 $ operations is allowed.

## 样例 #1

### 输入

```
4
2 1 4 3
```

### 输出

```
1 4
```

## 样例 #2

### 输入

```
7
36 28 57 39 66 69 68
```

### 输出

```
1 4
6 7
```

## 样例 #3

### 输入

```
5
1 2 1 2 1
```

### 输出

```
2 5
3 4
1 4
1 4
```

# 题解

## 作者：linch (赞：5)

## 题意
简单来说，就是对 $n$ 个数进行从小到大冒泡排序。输出交换的过程。

## 解决
我们可以直接用两层循环来解决。先从 $1$ 循环到 $n$，嵌套一个从 $n$ 到 $i$ 的循环，重复判断：如果 $a_{j}<a_{j-1}$，交换并输出。这样每次循环能确定一个元素的位置，直到循环结束就能实现排序。这里给出一段 Python 代码。

## 代码
```python
# 输入 n。
n=int(input())
# 输入数组。
a=list(map(int, input().split()))
# 冒泡排序。
for i in range(1,n):
    # 遍历数组，从后往前。
    for j in range(n-1, i-1,-1):
    	# 交换。
        if a[j]<a[j-1]:
            # Python 独有的交换方式。
            a[j],a[j-1]=a[j-1],a[j]
            # 输出。
            print(j,j+1)

```

---

## 作者：hjqhs (赞：1)

这题蛮善良的，因为长度为 $100$ 的数组最多有 $\frac{100 \times 99}{2} = 4950$ 个逆序对，所以即使每次交换的区间为 $2$，即最多减少一个逆序对，我们依然能在题目要求的 $20000$ 次内完成排序。  
那么题目解法很明显了，冒泡排序过程中输出交换的两数下标。此题建议评橙。  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,a[N];
void bubble_sort(int *a){
	bool flag=true;
	while(flag){
		flag=false;
		for(int i=1;i<n;++i){
			if(a[i]>a[i+1]){
				cout<<i<<' '<<i+1<<'\n';
				flag=true;
				swap(a[i],a[i+1]);
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	bubble_sort(a);
	return 0;
}
```

---

## 作者：very_easy (赞：1)

# 题意
将一个有 $n$ 个元素的序列排成非递减序列，每次操作可以指定区间进行交换，要求将他从小到大排序。
# 思路
从题面就能看出这题是一共简单的冒泡排序 $+$ 输出方案。

因为题目意思是可以指定区间，去间可以是一个数（我是这么理解的）所以就是冒泡排序。

只需要每次交换时都输出一下交换的两个数就可以。
# 代码
```c++
#include<iostream>
using namespace std;
const int N=2e4+5;
int a[N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){//冒泡排序
		for(int j=i+1;j<=n;j++){
			if(a[i]>a[j]){
				swap(a[i],a[j]);
				cout<<a[i]<<" "<<a[j]<<endl;//方案
			}
		}
	}
	return 0;
}
```

---

## 作者：_Jonny_404 (赞：0)

1.6：修改了部分的数组下标。

与楼上题解巧合，是用冒泡排序，但在输出方面有区别。

因为 $1 \le n \le 100$，且冒泡排序的时间复杂度为 $\mathcal{O}(n^2)$ ，所以用冒泡排序最多要比较 $10^{4}$ 次（准确来讲是 $(99+1)\times 99 \div 2=4950$ 次），远在 $20000$ 次之内，用题目的时间限制也不会超时，因此复杂度是没问题了。

由于每次是交换相邻的 $2$ 个数，符合冒泡排序的规则，所以用冒泡排序是准没错了（这样的话题目里的 $l$ 和 $r$ 是不是对程序没有影响了？），每次交换 $a_{j-1}$ 和 $a_{j}$ 时输出 $j-1$ 和 $j$ 即可 AC。

AC 代码如下：

```cpp
#include<iostream>
using namespace std;

int n;
int a[110];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++)
	{
		for(int j=n;j>i;j--)
			if(a[j]<a[j-1])
			{
				cout<<j-1<<" "<<j<<endl;
				swap(a[j-1],a[j]);
			}
	}
	return 0;
}
```

---

## 作者：xzggzh1 (赞：0)

题意：

将一个 $n$ $(1 \leq n \leq 100)$个元素的序列排成非递减序列，每次操作可以指定区间$[ L，R ]$（区间内元素个数为偶数），将区间内第一项与第二项交换，第三项与第四项交换，第五项与第六项……在 $20000$ 次内完成排序，输出每次操作。

---

我们只考虑每次操作一个长度为 $2$ 的区间，就是交换相邻项，让序列变得有序。

你想到了啥？ 对，冒泡排序。

众所周知，冒泡排序的交换次数在 $O(n^2)$ 左右，当然这个 $n^2$ 在绝大多数情况下是超过实际比较次数的。

所以可以在 $20000$ 操作内完成 $ 100 $ 个数的排序。

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=105;
inline int R()
{
    char c;int res,sign=1;
    while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
    while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
    return res*sign;
}
int a[Maxn],n,h[Maxn*Maxn][2],top;
int main()
{
	n=R();
	for(int i=1;i<=n;i++) a[i]=R();
	for(int i=1;i<=n;i++)
	for(int j=n;j>i;j--)
	{
		if(a[j]<a[j-1])
		{
			swap(a[j],a[j-1]);
			h[++top][0]=j-1;
			h[  top][1]=j;
		}
	}
	for(int i=1;i<=top;i++)
		printf("%d %d\n",h[i][0],h[i][1]);
}
```

---

## 作者：drah_yrev (赞：0)

## 思路
指定数组的第 $n$ 项与第 $n+1$ 调换，让数组变得有序。

对！你想的没错！是冒泡排序，先循环 $n$ 次，再循环 $n\sim i$ 次，每一次都要寻找逆序对，进行交换并输出。

时间复杂度：$O(n^2)$，最多要排序 $100\times100\div2=5000$ 次，时间充裕。


## 代码
```cpp
#include<iostream>
using namespace std;
int a[100],n,h[10000][2],top;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=n;j>i;j--){
			if(a[j]<a[j-1]){
				swap(a[j],a[j-1]);
				cout<<j-1<<" "<<j<<endl;
			}
		}
   }
}

```


---

## 作者：zhongboxuan123 (赞：0)

# 题意
这题很基础，题面简化为，指定一个区间 $[L,R]$ 中的对应位置进行交换，我们可以考虑使区间只有两个元素，即 $L$ 与 $R$ 相邻进行交换，也就是将相邻两数交换应将 $n$ 个数进行冒泡排序，交换所有逆序对，使其从小到大排序，并且输出交换过程。

# 解法
很简单，只需要使用冒泡排序的模板，即两层循环并加上中间过程的输出即可通过。
# 代码如下	
```cpp
#include<bits/stdc++.h>
#define MX 100
using namespace std;
int a[MX + 10];
int main(){
	int n;
	cin >> n;
	for(int i = 1;;i <= n;i ++){
		cin >> a[i];
	}
	for(int i = 1;i <= n;i ++){
		for(int j = i + 1;j <= n;j ++){
			if(a[i] > a[j]){
				swap(a[i],a[j]);
				cout << i << " " << j << endl;
			}
		}
	}
	return 0;
}
```

---

