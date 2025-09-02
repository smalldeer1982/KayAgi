# Little Elephant and Problem

## 题目描述

The Little Elephant has got a problem — somebody has been touching his sorted by non-decreasing array $ a $ of length $ n $ and possibly swapped some elements of the array.

The Little Elephant doesn't want to call the police until he understands if he could have accidentally changed the array himself. He thinks that he could have accidentally changed array $ a $ , only if array $ a $ can be sorted in no more than one operation of swapping elements (not necessarily adjacent). That is, the Little Elephant could have accidentally swapped some two elements.

Help the Little Elephant, determine if he could have accidentally changed the array $ a $ , sorted by non-decreasing, himself.

## 说明/提示

In the first sample the array has already been sorted, so to sort it, we need 0 swap operations, that is not more than 1. Thus, the answer is "YES".

In the second sample we can sort the array if we swap elements 1 and 3, so we need 1 swap operation to sort the array. Thus, the answer is "YES".

In the third sample we can't sort the array in more than one swap operation, so the answer is "NO".

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
3 2 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4
4 3 2 1
```

### 输出

```
NO
```

# 题解

## 作者：Ryan_Yu (赞：6)

如果想通过一次交换使数列成为不下降序列，就必须是交换前的数列与交换后的数列不相同处最多等于 $2$ 。

先将 $a$ 数组中的数存入 $b$ 数组，再将 $a$ 数组按从小到大的顺序排序。

排序后的 $a$ 数组就成为了不下降序列，然后比较 $a,b$ 二数组，如果不相同处大于 $2$ ，输出 `NO` ，否则输出 `YES` 。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int a[maxn],b[maxn],i,dif,n;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
        {
            cin>>a[i];
            b[i]=a[i];
        }
    sort(a+1,a+1+n);
    for(i=1;i<=n;i++)
        if(a[i]!=b[i])
            dif++;
    if(dif<=2)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
    return 0;
}
```


---

## 作者：LLGZ (赞：1)

### 题意分析

给定一个$n$长度序列，在只交换一次的条件下，成为一个升序序列，可以则输出YES，反之NO。

### 思路

要定义**两个数组**，一个用来储存未排序的，一个储存升序排完的。因为交换一次要移动两个数的位置，所以判断排序完的序列与原序列所变的位置个数**是否等于2**

附上代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int a[100100],b[100100];//a储存升序序列，b储存原序列
int main()
{
  int n;
  scanf("%d",&n);
  
  for(int i=1;i<=n;i++)
  {
  	scanf("%d",&a[i]);
  	b[i]=a[i];//同时赋值
  }
  sort(a+1,a+1+n);//sort默认升序排列
  
  int t=0;
  for(int i=1;i<=n;i++)
  if(a[i]!=b[i])//与原序列变化位置数量
  t++;
  
  if(t==2)//判断是否为2
  printf("YES");
  else printf("NO");
  
  return 0;
}
```



---

## 作者：pigstd (赞：1)

### 此题思路:用一个辅助数组，对这个数组排序后，如果不同的数字>2,则说明不行，否则就可以了

c++ 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=1e5+10;
int n,sum,num[M],a[M];//num数字辅助

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        cin>>num[i],a[i]=num[i];
    sort(num+1,num+1+n);
    for (int i=1;i<=n;i++)
        if (a[i]!=num[i])
            sum++;//统计不同的数字
    if (sum==0||sum==2)
        printf("YES");
    else
        printf("NO");
    return 0;
}
```

---

## 作者：Viston (赞：1)

This Explanation is written by viston. (If you do many red subjects ,you'll sometimes see me).

好的让我们开始讲中文！  

这一道题呢，~~我一开始居然还没有找到规律来~~，想了各种高端算法23333   

后来一想，交换两个元素，并不会改变中间元素的位置   

(╯‵□′)╯︵┻━┻那岂不是扫一遍就行了....   

~~（以后千万不要把红题想得太复杂）~~    

具体见代码
```
#include<bits/stdc++.h>
using namespace std;
int a,b[100020],c[100020],ans=0,i,j;
int main()
{
	cin>>a;
	for(i=1;i<=a;i++)
	{
		cin>>b[i];//输入排序前的数组
		c[i]=b[i];//方便等下比较
	}
	sort(c+1,c+a+1);//我才不会手写二分
	for(i=1;i<=a;i++)
	if(c[i]==b[i])//开始比较了惹
		continue;
	else			//如果不同，说明他交换过
		ans++;
	if(ans==2||ans==0)//不交换&&交换一次的情况
		cout<<"YES";
	else
		cout<<"NO";
	return 0;
}
```
See you Next red subject!

---

## 作者：happybob (赞：0)

这里讲一个双端队列和小根堆配合的解法，不需要sort，但思路与其他题解类似

两个队列，一个是双端队列，另一个小根堆

小根堆升序排序，双端队列储存

最后看看不一样的数据有几个

代码：
```cpp
#include <iostream>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, less<int> > que;

deque<int> a;

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for(register int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        a.push_back(x);
        que.push(x);
    }
    int cnt = 0;
    while(!a.empty())
    {
        if(que.top() != a.back())
        {
            cnt++;
        }
        que.pop();
        a.pop_back();
    }
    cout << (cnt == 0 || cnt == 2 ? "YES" : "NO") << endl;
    return 0;
}
```
2.09s

AC：[https://www.luogu.com.cn/record/42283992](https://www.luogu.com.cn/record/42283992)

---

## 作者：Eason_AC (赞：0)

## Notice
由于第一次使用 Ubuntu 写代码，所以代码风格可能和之前的题解有所不同，请见谅qwq。
## Content
有一个长度为 $n$ 的序列 $a_1,a_2,a_3,...,a_n$，求是否可以通过不多于一次的交换使得这个序列变成非降序序列。

**数据范围：$2\leqslant n\leqslant 10^5,a_i\leqslant 10^9$。**
## Solution
我们可以开两个数组，一个就是我们当前的数组，另外一个做辅助用。首先我们将辅助数组一一对应赋值为输入的数组的值。然后对这个辅助数组非降序排序。我们知道，交换一次会有 $2$ 个值与原来的不同，所以我们将输入的数组和排序后的数组比较看有多少个值不同，如果不同的数量 $> 2$，那么就无法通过最多一次的交换使得这个序列变成非降序序列，否则可以。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, a[100007], a1[100007], scnt;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		a1[i] = a[i];
	}
	sort(a1 + 1, a1 + n + 1);
	for(int i = 1; i <= n; ++i)
		if(a1[i] != a[i])	scnt++;
	if(scnt <= 2)	printf("YES");
	else	printf("NO");
	return 0;
}
```

---

## 作者：judgejudge (赞：0)

# 通俗易懂！！！
这道题其实我们可以这么想：**如果一个数组不交换位置或者交换一次位置，那么它们至多变动2个数字！！！**

举个例子：
| 1 | 3 | 2 | 4 | 5 |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 2 | 3 |  4| 5 |
| 0 | 1 | 1 | 0 | 0 |

（此处0代表没变化，1代表变化）

显而易见，只要2和3交换位置即可。“1”的个数是2，不大于2，则输出YES

| 5 | 4 | 3 | 2 | 1 |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| 1 | 2 | 3 | 4 | 5 |
| 1 |1  | 0 | 1 | 1 |

此处“1”的个数是4，大于2，输出NO

那么我们可以**输入一个数组，然后再把这个数组的数储存到另一个数组中去，进行排序后比较**，如果有两个以内的数字变动，输出YES，不是则输出NO

奉上AC代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[1000001],b[1000001];//定义两个数组
int sum=0;
int main(){
	int i,j,k,n;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];//把数组1的数储存到数组2当中去
	}
	sort(a+1,a+n+1);
	for(i=1;i<=n;i++)
	if(a[i]!=b[i])sum++;//如果发现不同，“1”的个数++
	if(sum>2)cout<<"NO"<<endl;//大于2，输出NO
	else cout<<"YES"<<endl;//反之，输出YES
	return 0;
}
```


---

## 作者：_Empty (赞：0)

这是一篇给新手看的题解！

## **题意**:

```
给出一个长度为n(2<=n<=10000)
的序列，判断在一次交换（即交换序列中的两个数）
后能否使它成为不下降序列。
```


```
简单，我的做法与大佬们都不同，他们判断>2的，而我判断<2的
```


其中代码中的**三目运算符**((ans==0||ans==2)?YES():NO();)即为

---
```
if(ans==1||ans==2) YES();
else NO();
```
---
其中 `YES` 函数 输出 "`YES`"; `NO` 函数 输出 "`NO`"
```
#include<bits/stdc++.h>//万能头文件不做解释
using namespace std;
int b[100005],n,ans,a[100005];//定义数组b[],a[]与变量n，ans
void YES(){//定义YES函数
	cout<<"YES";//如果判断成功输出YES
}
void NO(){//定义NO函数
	cout<<"NO";//如果判断失败输出NO
}                 
int main(){//main函数
    cin>>n;//输入n
    for(int i=1;i<=n;i++)	cin>>b[i],a[i]=b[i];//按题目要求输入加赋值
    sort(b+1,b+1+n);//sort排序一遍
    for(int i=1;i<=n;i++)
        if (a[i]!=b[i])   ans++;
    (ans==0||ans==2)?YES():NO();//三目运算符
    return 0;//收尾
}
```

---

