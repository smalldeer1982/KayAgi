# Alyona and Mex

## 题目描述

Someone gave Alyona an array containing $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ . In one operation, Alyona can choose any element of the array and decrease it, i.e. replace with any positive integer that is smaller than the current one. Alyona can repeat this operation as many times as she wants. In particular, she may not apply any operation to the array at all.

Formally, after applying some operations Alyona will get an array of $ n $ positive integers $ b_{1},b_{2},...,b_{n} $ such that $ 1<=b_{i}<=a_{i} $ for every $ 1<=i<=n $ . Your task is to determine the maximum possible value of mex of this array.

Mex of an array in this problem is the minimum positive integer that doesn't appear in this array. For example, mex of the array containing $ 1 $ , $ 3 $ and $ 4 $ is equal to $ 2 $ , while mex of the array containing $ 2 $ , $ 3 $ and $ 2 $ is equal to $ 1 $ .

## 说明/提示

In the first sample case if one will decrease the second element value to $ 2 $ and the fifth element value to $ 4 $ then the mex value of resulting array $ 1 $ $ 2 $ $ 3 $ $ 3 $ $ 4 $ will be equal to $ 5 $ .

To reach the answer to the second sample case one must not decrease any of the array elements.

## 样例 #1

### 输入

```
5
1 3 3 3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
2 1
```

### 输出

```
3
```

# 题解

## 作者：liuyifan (赞：1)

## 水题(就是题意比较难读懂,如果沥青题意就很水了)

题意：给定一个序列，你可以对这里面的数用小于它的数来代替，最后让你求，改完后的最大的序列中缺少的最小的数

根本思路：尽量凑1 2 3 4 5,如果没有了，就输出

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
#define lowbit(x) x&(-x)//树状数组模板
using namespace std;
int a[1000005],n,ans;
int main()
{
    while(scanf("%d",&n)==1)//多组数据,CF传统
	{
		ans=0;//记得清零
		for(reg int i=1;i<=n;i++)scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        for(reg int i=1;i<=n;i++)if(ans<a[i])ans++;//统计凑的数量
        printf("%d",++ans);//因为初始为1,所以要++
//        ++ans和ans++的区别:
//		{
//            设ans=1;
//            cout<<++ans输出2
//            cout<<ans++输出1,但是在输出完后ans会变成2
//		}
    }
    return 0;
}
```


---

## 作者：_YyD_ (赞：0)

可以算是个贪心吧。

贪心思路就是尽量拿小的来凑小的。

证明就是小的可以变得大的也可以，大的可以的小的不一定行。

来看看代码：

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
int a[200000],n,cnt=1;
int main(){
	cin>>n;
	rep(i,1,n)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	rep(i,1,n)if(a[i]>=cnt)cnt++;
	cout<<cnt;
	return 0;
}
```


---

## 作者：清清老大 (赞：0)

## 题意

给出一个数组，可以任意减小一个元素，可以减小任意次。输出减小后数组中没有出现的最小正整数的最大可能值

## 思路

如果要使没有出现的最小正整数最大，就要尽量凑出 $1,2,3,...$ 这样的数列。

先将数组从小到大排列， $ans$ 从一开始，每次遇到大于等于 $ans$ 的数，就将这个数减小到 $ans$ ， $ans$ 增加 $1$ ，最后的 $ans$ 值即为所求。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,ans = 1,a[121212];
    cin >> n;
    for(int i = 0;i < n;i ++)
    {
        cin >> a[i];
    }
    sort(a,a + n);
    for(int i = 0;i < n;i ++)
    {
        if(ans <= a[i])
        {
            ans ++;
        }
    }
    cout << ans;
}
```


---

