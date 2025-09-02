# [ABC072C] Together

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc072/tasks/arc082_a

長さ $ N $ の整数列 $ a_1,a_2,...,a_N $ が与えられます。

各 $ 1\ <\ =i\ <\ =N $ に対し、$ a_i $ に $ 1 $ 足すか、$ 1 $ 引くか、なにもしないかの三つの操作からどれか一つを選んで行います。

この操作の後、ある整数 $ X $ を選んで、$ a_i=X $ となる $ i $ の個数を数えます。

うまく操作を行い、$ X $ を選ぶことで、この個数を最大化してください。

## 说明/提示

### 制約

- $ 1\ <\ =N\ <\ =10^5 $
- $ 0\ <\ =a_i\ <\ 10^5\ (1\ <\ =i\ <\ =N) $
- $ a_i $ は整数

### Sample Explanation 1

例えば操作後の数列を $ 2,2,3,2,6,9,2 $ とすることができて、$ X=2 $ とすると $ 4 $ を得ることができ、これが最大です。

## 样例 #1

### 输入

```
7
3 1 4 1 5 9 2```

### 输出

```
4```

## 样例 #2

### 输入

```
10
0 1 2 3 4 5 6 7 8 9```

### 输出

```
3```

## 样例 #3

### 输入

```
1
99999```

### 输出

```
1```

# 题解

## 作者：信息向阳花木 (赞：2)

题目 Latex 好像炸了，重新排版点 [这里](https://www.luogu.com.cn/paste/45krcvb7)。

由于 **每个数** 都可以对其进行 **任何** 操作，所以我们可以把每个数所有操作后的值算出来，放进 **桶** 里，然后枚举取最大的 $X$。

看程序更形象：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,maxx,ans;
int x,b[100010]; //b 是桶。 
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>x; 
		maxx=max(x,maxx); //记录最大范围。 
		b[x]++;b[x-1]++;b[x+1]++;
	}
	for(int i=0;i<=maxx+1;i++){//最大的数也有可能进行加 1 操作。
		ans=max(b[i],ans);//注意求的不是 x 而是有多少 a[i] 等于 x。 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：亦枫 (赞：2)

## Solution

题意：给你 $ n $ 个数 $ a_1,a_2,…,a_n $。

现在，你可以对 $ a_i $ 进行一些操作：

1.给 $ a_i $ 加1

2.给 $ a_i $ 减1

对于每个数进行操作后，看会有多少个 $ a_i = X $ 。

对于每个 $ a_i $，统计数值大小为 $ a_i-1 $，$ a_i+1 $ 和 $ a_i $ 的数共有多少个，再相加。即可。

那么，我们只要用桶的思想就可以了，将 $ n $ 个数的值用桶来记录下来。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a[100005],cnt[100005],ans;
int main() {
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)scanf("%d",&a[i]),cnt[a[i]]++,cnt[a[i]+1]++,cnt[a[i]-1]++;
	printf("%d\n",*max_element(cnt,cnt+100000));//找到最大值
	return 0;
}

```


---

## 作者：77777_1031 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT3524)

[更好的阅读体验](https://tsygoon.blog.luogu.org/solution-at3524)

~~题外话：好像莫得人用双指针诶~~
##  Part 1 题意分析
 题意：给你 $n$ 个数 $a_i$，你可以把每个数加一个 $\{-1,0,1\}$ 中的数，然后选择一个所有元素的值相同的子列,求子列长度的最大值。
 
 分析：因为我们要尽可能的把小的数往大加，大的数减小，但我们最大只能加 $1$，最小也只能减 $1$，所以这个序列最小最大的数的差一定小于等于 $2$。如果要求区间长度的最大值那么这个区间最大和最小值的差一定为 $2$。如果这个序列初始最大和最小值的差就小于等于 $2$，那么直接输出序列的长度即可。
 
 总结：我们可以先排个序，然后双指针寻找一个差为 $2$ 的长度最大区间，
##  Part 2 有关双指针
~~（dalao自动略过，不对，dalao们不会来康我的题解）~~

  双指针算法是指利用两个指针遍历数组（链表），左右指针相向前进或同向前进，在遍历过程中根据某种限制条件进行筛选，通常可以把时间复杂度降低至 $O(n)$。
  
  [一些阔以练习双指针的题](https://www.luogu.com.cn/training/127978)
##  Part 3 代码
```c
#include <bits/stdc++.h>
using namespace std;
int n;
int a[100001];
int l=1,r=1,t=0;
int ans=0;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    if((a[n]-a[1])<=2){cout<<n<<endl;return 0;}
    while(r<=n){
        if((a[r]-a[l])<=2){
            r++;
            t++;
            if(t>ans)ans=t;
        }
        else{l++;t--;}
    }
    cout<<ans<<endl;
    return 0;//完结撒花～～
}
```
[AC记录](https://www.luogu.com.cn/record/63703546)

[我的博客](https://tsygoon.blog.luogu.org)

最后的话：看都看了，不点个赞再走嘛？谢谢呐。

$\mathit{by 2021.11.27}$ 我的第二篇题解。

---

## 作者：monstersqwq (赞：1)

思路：

用一个数组 t 作为桶，记录序列中的数字（读入）。

枚举每一个 X，因为只有 X-1、X、X+1 才能通过某种操作变为 X，于是对于每一个 X 来说，答案就是 $t_{X-1}+t_X+t_{X+1}$ 每次更新答案，最后输出即可（AT题中不换行，听取WA声一片）

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>//可爱的头文件 
using namespace std;
int n,t[100005];//桶 
int ans=-1;//存储答案 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		t[x]++;
	}
	for(int i=1;i<=100000;i++)
	{
		ans=max(ans,t[i-1]+t[i]+t[i+1]);//更新答案 
	}
	cout<<ans<<endl;//输出答案 
    return 0;
}
```


---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT3524)

小学生又双叒叕来写题解啦！

每个数都不受限制的可以变成三个数，那我们就用数组存每个数的变身情况，每次都给那三个数对应的计数器加一即可。

然后呢？

大家的思路都是在最后再遍历一次数组，并找最大值。

实际上根本不需要这一个重新搜的动作，只需在**每次加计数器时都比较一次**即可。

这样就对常数做了优化。

实际上可以利用指针进行进一步的优化，但没必要，反正总体的时间效率差别不大，就没必要浪费十几行再优化常数了。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int box[100005];
int main()
{
	int n, maxn = -1;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		box[x-1]++, maxn = max(maxn, box[x-1]);  //一边走一边判断。 
		box[x]++, maxn = max(maxn, box[x]);
		box[x+1]++, maxn = max(maxn, box[x+1]);
	}
	printf("%d\n", maxn);   //勿忘祖传换行。 
	return 0;
}
```


---

## 作者：iiawaKL (赞：0)

对于一个数，你可以对其进行三个操作中的其中一个：

1.将这个数+1

1.将这个数-1

1.啥都不做

现在，我们就可以理解为：只要x等于这个数-1，或等于这个数+1，或等于这个数，那么就可以使当前位置满足“ai = X”。

这时候，我们就可以用Map记录对于每一个X，满足ai=x的i有多少个。然后从1枚举到100000（数据范围）找出最大满足数量输出即可。

Code->

```
#include<bits/stdc++.h> 
typedef long long ll;
using namespace std;
int a[100010];
map<int,int> mp;
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		mp[a[i]]++;
	}
	int mx=0;
	for(int i=0;i<n;i++)mx=max(mx,mp[a[i]]+mp[a[i]-1]+mp[a[i]+1]);
	cout<<mx<<endl;
	return 0;
}
```


---

## 作者：智子·起源 (赞：0)

### ~~楼下大佬的详细版~~

#### 思路：

对于一个数，你可以对其进行三个操作中的其中一个：

1. 将这个数+1

2. 将这个数-1

3. 啥都不做

现在，我们就可以理解为：只要x等于这个数-1，或等于这个数+1，或等于这个数，那么就可以使当前位置满足“ai = X”。

这时候，我们就可以用一个数组记录对于每一个X，满足ai=x的i有多少个。然后从1枚举到100000（数据范围）找出最大满足数量输出即可。

上代码：
```cpp
#include<iostream>
using namespace std;
int n,a,f[100001],ans;
int main()
{
  cin>>n;
  for(int i=0;i<n;i++)
  {
    cin>>a;
    f[a-1]++,f[a+1]++,f[a]++;//把当前数可以符合的x的符合量++
  }
  for(int i=1;i<=100000;i++)if(f[i]>ans)ans=f[i];//找最大符合个数
  cout<<ans<<endl;//输出答案
  return 0;
}
```


---

## 作者：yzhang (赞：0)

有人要枚举X，不可能的，O（n*n）,TLE!!!

实际还是暴力水过，O（n），类似于桶排的方法...

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[500005];
int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		int x;
		cin>>x;
		a[x]++;//核心部分，把上下能修改到的地方都数量加1
		a[x-1]++;
		a[x+1]++;
	}
	int maxv=0;
	for(int i=0;i<=500000;i++)//比大小
		if(a[i]>maxv)
			maxv=a[i];
	cout<<maxv;
	return 0;
 } 
```

---

