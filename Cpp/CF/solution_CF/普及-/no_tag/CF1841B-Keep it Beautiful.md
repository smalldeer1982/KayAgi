# Keep it Beautiful

## 题目描述

The array $ [a_1, a_2, \dots, a_k] $ is called beautiful if it is possible to remove several (maybe zero) elements from the beginning of the array and insert all these elements to the back of the array in the same order in such a way that the resulting array is sorted in non-descending order.

In other words, the array $ [a_1, a_2, \dots, a_k] $ is beautiful if there exists an integer $ i \in [0, k-1] $ such that the array $ [a_{i+1}, a_{i+2}, \dots, a_{k-1}, a_k, a_1, a_2, \dots, a_i] $ is sorted in non-descending order.

For example:

- $ [3, 7, 7, 9, 2, 3] $ is beautiful: we can remove four first elements and insert them to the back in the same order, and we get the array $ [2, 3, 3, 7, 7, 9] $ , which is sorted in non-descending order;
- $ [1, 2, 3, 4, 5] $ is beautiful: we can remove zero first elements and insert them to the back, and we get the array $ [1, 2, 3, 4, 5] $ , which is sorted in non-descending order;
- $ [5, 2, 2, 1] $ is not beautiful.

Note that any array consisting of zero elements or one element is beautiful.

You are given an array $ a $ , which is initially empty. You have to process $ q $ queries to it. During the $ i $ -th query, you will be given one integer $ x_i $ , and you have to do the following:

- if you can append the integer $ x_i $ to the back of the array $ a $ so that the array $ a $ stays beautiful, you have to append it;
- otherwise, do nothing.

After each query, report whether you appended the given integer $ x_i $ , or not.

## 说明/提示

Consider the first test case of the example. Initially, the array is $ [] $ .

- trying to append an integer $ 3 $ . The array $ [3] $ is beautiful, so we append $ 3 $ ;
- trying to append an integer $ 7 $ . The array $ [3, 7] $ is beautiful, so we append $ 7 $ ;
- trying to append an integer $ 7 $ . The array $ [3, 7, 7] $ is beautiful, so we append $ 7 $ ;
- trying to append an integer $ 9 $ . The array $ [3, 7, 7, 9] $ is beautiful, so we append $ 9 $ ;
- trying to append an integer $ 2 $ . The array $ [3, 7, 7, 9, 2] $ is beautiful, so we append $ 2 $ ;
- trying to append an integer $ 4 $ . The array $ [3, 7, 7, 9, 2, 4] $ is not beautiful, so we don't append $ 4 $ ;
- trying to append an integer $ 6 $ . The array $ [3, 7, 7, 9, 2, 6] $ is not beautiful, so we don't append $ 6 $ ;
- trying to append an integer $ 3 $ . The array $ [3, 7, 7, 9, 2, 3] $ is beautiful, so we append $ 3 $ ;
- trying to append an integer $ 4 $ . The array $ [3, 7, 7, 9, 2, 3, 4] $ is not beautiful, so we don't append $ 4 $ .

## 样例 #1

### 输入

```
3
9
3 7 7 9 2 4 6 3 4
5
1 1 1 1 1
5
3 2 1 2 3```

### 输出

```
111110010
11111
11011```

# 题解

## 作者：ran_qwq (赞：6)

## 题目大意

定义一个数组是「漂亮的」当且仅当存在 $k\in[0,n-1]$，使得 $[a_{k+1},a_{k+2},\dots,a_n,a_1,a_2,\dots,a_k]$ 单调不降。

特殊的，如果 $a$ 的长度为 $0$ 或 $1$，它也是「漂亮的」。

初始时，数组 $a$ 为空。

给你 $q$ 次操作，每次给你一个数 $x$。如果把 $x$ 加到 $a$ 的末尾，$a$ 仍是「漂亮的」，就把 $x$ 加到 $a$ 的末尾，否则不加。

问每次操作能否把 $x$ 加进去。

## 题目思路

**结论：把 $a$ 首尾相连。如果不存在或只存在一对相邻的数，前面的数大于后面的，那么 $a$ 就是「漂亮的」。**

证明：

- 若不存在这样的相邻的数，则 $a$ 本身就是单调不降的，当然是「漂亮的」。

- 若只存在一对，则可以把这一对断开，前面那一段放到后面去，$a$ 就是「漂亮的」。

如果 $a$ 是「漂亮的」，现在要加一个数 $x$ 进去。设 $a$ 末尾的数为 $a_m$，则相邻的数少了 $(a_m,a_1)$，多了 $(a_m,x)$ 和 $(x,a_1)$。判断大小关系来维护前面的数大于后面的的相邻的数的个数就可以了。

```cpp
void solve()
{
	n=read(),cnt=0,lst=-1;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();if(lst<0) {printf("1"),lst=i;continue;}
		int x=(a[lst]>a[i])+(a[i]>a[1])-(a[lst]>a[1]);
		if(cnt+x<=1) cnt+=x,lst=i,printf("1");
		else printf("0");
	}
	puts("");
}
```

---

## 作者：xiazha (赞：2)

## 思路

模拟题，可以在线处理，我将这题分为了四种情况。

1. 在第 $i$ 个点之前，数组还没有被分为两部分，那么 $a_i$ 如果大于等于上一个满足条件的数，就满足条件。

2. 在第 $i$ 个点之前，数组还没有被分为两部分，但是不满足第一个条件，如果可以将它移到 $a_1$ 前（也就是 $a_i\le a_1$），说明也满足条件，并且需将标记有没有被分成两部分的变量 $flag$ 更新。

3. 在第 $i$ 个点之前，数组已经被分为两部分，如果 $a_i \le a_1$ 同时 $a_i$ 又大于上一个满足条件的第二部分的数，就满足条件。

4. 如果以上三种情况都不满足，说明当前的 $a_i$ 不可以加入到“beautiful”数组里。

注意，因为 $a_1$ 无论怎样都是满足条件的，所以需要将 $a_1$ 单独输入，并先输出一个 ```1``` 。


## 代码
```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200002],l,sum;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>a[1];
		cout<<1;
		l=1,sum=a[1];
		for(int i=2;i<=n;i++) {
			cin>>a[i];
			if(l==1&&a[i]>=sum) cout<<1,sum=a[i];
			else if(l==1&&a[i]<=a[1]) sum=a[i],l=2,cout<<1;
			else if(l==2&&a[i]<=a[1]&&a[i]>=sum) sum=a[i],cout<<1;
			else cout<<0;
		}
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：szhqwq (赞：1)

## $\tt{Solution}$

考虑模拟。

根据题目，只要加进来的数满足条件，那么**必须**要将此数加入其中，这一点在赛事的时候出题组也发过公告。

那么，我们就需要考虑，什么情况下一个数才能被加进来：

1. 加进来的数 $a_i$ 大于上一个数 $a_{i - 1}$，前提条件是此时 $2 \le i \le k$，使用一个标记来记录，满足则输出 `1`；

2. 如果已经过了 $k$ 的高峰（$i > k$），那么需要判断其是否小于第一个加入进来的数（一定为 $a_1$，代码中用的 `Min` 即为 $a_1$），输出 `1`；

3. 现在正处于 $k$ 的转折处，那么如果此时已经标记过经过了 $k$ 的高峰（$i > k$），那么输出 `0`，否则输出 `1`，标记经过高峰；

4. 以上条件均不满足，输出 `0`。

## $\tt{AC \ Code \ of}$ [$\tt{CF1841B}$](https://www.luogu.com.cn/problem/CF1841B)

[Link](https://codeforces.com/contest/1841/submission/209425779)

---

## 作者：rainygame (赞：0)

> 本题解中的“有序”指“不降”。

首先我们通过分析可以得到，“Beautiful”数组一定是下面两个中的一个：

- 本来就有序。
- 可以把数组分为两个部分，使得两个部分分别有序，且第二个部分的最后一个小于等于第一部分的第一个。因为这样才可以把第一个移到第二个前面。

那我们就可以模拟这个操作，用一个变量表示是否已经需要分开。

如果原来没有需要分开，那就判断 $x$ 是否大于等于最后一个，如果是就可以插入，如果不是就判断可否分开（即是否满足上述要求），如果可以就分开插入，否则不插入。

对于已经需要分开的，就要看看这个 $x$ 插入后是否满足要求，如果满足就插入，否则不插入。

当然，如果使用 STL，一开始要判空。

时间复杂度 $O(\sum q)$，空间复杂度 $O(q)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, q, x, cnt;
vector<int> vec;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> t;
	
	while (t--){
		cin >> q;
		vec.clear();
		cnt = 0;
		while (q--){
			cin >> x;
			if (vec.empty()){
				cout << '1';
				vec.push_back(x);
				continue;
			}
			
			if (cnt){
				if (vec.back() <= x && vec.front() >= x){
					cout << '1';
					vec.push_back(x);
				}else cout << '0';
			}else{
				if (vec.back() > x){
					if (vec.front() >= x){
						cout << '1';
						vec.push_back(x);
						++cnt;
					}else cout << '0';
				}else{
					cout << '1';
					vec.push_back(x);
				}
			}
		}
		cout << '\n';
	}
	
	return 0;
}

```


---

## 作者：mark0575 (赞：0)

## 思路：

由于数据范围比较大，我们不可能去纯模拟。通过题目的样例，我们可以把一个序列分成两个部分，这两部分都满足单调不减。第一部分是开头部分，第二部分是末尾部分。我们假设 $max1$ 为第一部分的最大值，$max2$ 为第二部分的最大值，$min1$ 为第一部分的最小值，$flag$ 表示是否有第二部分。如果 $flag=1$，表示有第二部分，否则为没有。如果 $a_i\geq max1$ 并且 $flag=0$，那么我们就可以把 $a_i$ 加入序列中，并更新最大值和最小值。如果不满足上面的条件但 $flag=0$，那么我们可以让 $a_i$ 与 $min1$ 作比较。如果 $a_i\leq min1$，我们就可以把 $a_i$ 加入序列中，将 $flag$ 变为 $1$，并更新 $max2$。如果 $flag=1$ 并且 $a_i\leq min1$ 并且 $a_i\geq max2$，那么我们就将 $a_i$ 加入序列中，并更新 $max2$。如果都不满足上面的条件就输出 $0$。

## AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n;
int a[2010101];
int max(int a,int b)
{
	if(a>b)
	{
		return a;
	}
	return b;
}
int min(int a,int b)
{
	if(a<b)
	{
		return a;
	}
	return b;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		int maxx=0,minn=1e9,ma=0,flag=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]>=maxx&&!flag)//整个序列呈单调不减
			{
				cout<<1;
				maxx=max(maxx,a[i]);
				minn=min(minn,a[i]);
				continue;
			}
			if(!flag&&a[i]<=minn)//可以通过移动
			{
				cout<<1;
				flag=1;
				ma=max(ma,a[i]);
				continue;
			}
			if(flag)
			{
				if(a[i]>=ma&&a[i]<=minn)//在原有基础上
				{
					cout<<1;
					ma=max(ma,a[i]);
					continue;
				}
			}
			cout<<0;
		}
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：wuyin331 (赞：0)

# 题意
称一个数组 $[a_1, a_2, \dots, a_k]$ 是好的，则数组存在一个数 $ i \in [0, k-1]$ 移动 $a_{i+1}, a_{i+2}, \dots, a_{k-1}, a_k$ 至数组的前面，为 $[a_{i+1}, a_{i+2}, \dots, a_{k-1}, a_k, a_1, a_2, \dots, a_i]$，被修改后的数组是单调不降的。

给你一个空数组，有 $q$ 次询问，对于第 $i$ 次询问，如果添加一个 $x_{i}$ 在数组的尾部，这个数组是一个好数组，则添加 $a_{i}$ 在数组的尾部。否则不添加。
# 题解
对于最初一个空数组来说，是肯定能被加入的。接下来的询问，设数组上一个被添加的数为 $a_{t}$，注意不是 $a_{i-1}$，因为数不一定会被添加。如果要做到单调不减，则需要有 $a_{t} \le x_{i}$。注意到我们有一次修改的机会，则如果有 $a_{t} > x_{i}$，且 $a_{1} \ge a_{i}$。那么这个数也是可以添加的。修改后就没有这次机会了，之后的数需要有 $a_{t} \le x_{i}$，且 $x_{i} \le a_{1}$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t,n,l,f,h,num;
	cin>>t;
	while(t--){
		cin>>n;
		cin>>l;f=1,h=l;//l为数组上一个元素，h为第一个元素 
		cout<<'1';
		for(int i=2;i<=n;i++){
			cin>>num;
			if(f){
			if(l<=num){
				cout<<'1';
				l=num;
				continue;	
			}
			else{
				if(num<=h){
				cout<<'1';
				l=num;f=0;
				continue;
			}
			}
		}
			else{
				if(l<=num&&num<=h) {
				cout<<'1';
				l=num;
				continue;
			}
			}
			cout<<'0';
		}
		cout<<'\n';
	}
	return 0;
}
```


---

