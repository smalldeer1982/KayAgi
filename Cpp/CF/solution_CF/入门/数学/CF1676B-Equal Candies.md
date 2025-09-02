# Equal Candies

## 题目描述

There are $ n $ boxes with different quantities of candies in each of them. The $ i $ -th box has $ a_i $ candies inside.

You also have $ n $ friends that you want to give the candies to, so you decided to give each friend a box of candies. But, you don't want any friends to get upset so you decided to eat some (possibly none) candies from each box so that all boxes have the same quantity of candies in them. Note that you may eat a different number of candies from different boxes and you cannot add candies to any of the boxes.

What's the minimum total number of candies you have to eat to satisfy the requirements?

## 说明/提示

For the first test case, you can eat $ 1 $ candy from the second box, $ 2 $ candies from the third box, $ 3 $ candies from the fourth box and $ 4 $ candies from the fifth box. Now the boxes have $ [1, 1, 1, 1, 1] $ candies in them and you ate $ 0 + 1 + 2 + 3 + 4 = 10 $ candies in total so the answer is $ 10 $ .

For the second test case, the best answer is obtained by making all boxes contain $ 5 $ candies in them, thus eating $ 995 + 995 + 0 + 995 + 995 + 995 = 4975 $ candies in total.

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
6
1000 1000 5 1000 1000 1000
10
1 2 3 5 1 2 7 9 13 5
3
8 8 8
1
10000000```

### 输出

```
10
4975
38
0
0```

# 题解

## 作者：OLE_OIer (赞：1)

这道题难度较低，主要考察了基本数学知识。

思路是这样的：要使大家的糖果数量全部相等，至少要把大家的糖果吃到和最少的那一个一样多。最后统计吃的数量。

那么怎样获取最小值呢？我们可以在输入的时候用打擂台的方法取最小值。

代码附上：
```cpp
//CF1676B Equal Candies
#include<bits/stdc++.h>
#define int long long
#define elif else if
using namespace std;
void func(){
	int n,minn=1e9,tot=0;//minn表示最小值，tot表示糖果总数。
	cin>>n;
	vector<int>a(n+10,0);
	for(int i=1;i<=n;++i){
		cin>>a[i];
		minn=min(minn,a[i]);//打擂台取最小值
		tot+=a[i];//累加获取总数。
	}
	cout<<tot-minn*n<<"\n";//用糖果总数减去剩下的数量得到吃了多少。
}
signed main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=1;i<=n;++i) func();
	return 0;
}
```

---

## 作者：Engulf (赞：1)

给出数组 $a_1\sim a_n$，每次可以对一个 $a_i$ 减一，问使数组所有元素相等的最少步数。

因为只能减少不能增加，所以算出 $\min\limits_{i=1}^na_i$，进行统计。

```cpp
// author: TMJYH09
// create time: 2022/05/10 22:48:01
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        int n;cin>>n;
        vector <int> a(n);
        int mn=0x3f3f3f3f;
        for(auto &i:a)cin>>i,mn=min(mn,i);
        int ans=0;
        for(auto &i:a)ans+=(i-mn);
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

# 题意
有 $n$ 盒糖，第 $i$ 盒糖中有 $a_i$ 颗糖。

你现在可以吃掉一些糖，使得每盒糖中剩余的糖数相等。

问你最少需要吃掉几颗糖。
# 思路
可以看出，设 $m=\min\limits_{i=1}^n a_i$，则最后每盒糖中剩余的糖数一定不大于 $m$。

所以把每盒糖都吃到剩下 $m$ 颗时，吃掉的糖数最少。
# 代码
```cpp
#include <cstdio>
int T, n, m, s, a[150];
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);m = 1e9;s = 0;
        for(int i = 1;i <= n;++i) scanf("%d", &a[i]), a[i] < m && (m = a[i]);
        for(int i = 1;i <= n;++i) s += a[i] - m;
        printf("%d\n", s);
    }
    return 0;
}
```


---

## 作者：ttq012 (赞：0)

简单题。

容易发现，找到最少的那一盒糖作为基准值，然后将其他的糖全部吃到基准值的数量即可。

时间复杂度 $\mathcal O(T\cdot n)$。

**Code**

```python
T = int(input())

for _ in range(0, T):
    n = int(input())
    s = input().split()
    a = []
    for i in range(0, n):
        a.append(int(s[i]))
    minv = 666666666
    for i in range(0, n):
        if (minv > a[i]):
            minv = a[i]
    ans = 0
    for i in range(0, n):
        ans += (a[i] - minv)
    print(ans)

```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

显然，所有朋友能拿到最多糖果的方案，就是让所有朋友拿到原糖果中最少的那一盒的数量。

可以参考一下著名的木桶原理。

那么，我们需要统计两个数：所有糖果总和、最小的那一盒的糖果数量。

然后计算即可。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
int n;
int a[55];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int minn=0x7fffffff,sum=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			sum+=a[i];
			if(a[i]<minn)
			{
				minn=a[i];
			}
		}
		printf("%d\n",sum-minn*n);//计算答案
	}
	return 0;
}

```


---

## 作者：hyc1026 (赞：0)

这道题直接模拟即可。

找到这些数的最小值之后，再将每个盒子的糖果吃到还剩最小值，将吃的糖果数累加最后输出。

配合代码注释理解效果更好！

AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[1010]; //用于存储盒子中有几个糖果

int main()
{
	int n,t;
	cin >> t;
	while(t--) //t组数据
	{
		cin >> n; //输入盒子数量
		for(int i=1; i<=50; i++) a[i] = 0;
		int m = 100000000; //用于统计最小值，注意初值要赋的大一些
		for(int i=1; i<=n; i++)
		{
			cin >> a[i];
			m = min(m,a[i]); //计算最小值
		}
		long long cnt = 0; //统计一共要吃多少糖果
		for(int i=1; i<=n; i++)
		{
			cnt += (a[i] - m); //吃掉糖果知道还剩下最小值，以保持每个盒子个数相等
		}
		cout << cnt << endl; //输出，别忘了换行
	}
}
```

---

