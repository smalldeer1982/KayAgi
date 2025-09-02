# Fixed Point Guessing

## 题目描述

This is an interactive problem.

Initially, there is an array $ a = [1, 2, \ldots, n] $ , where $ n $ is an odd positive integer. The jury has selected $ \frac{n-1}{2} $ disjoint pairs of elements, and then the elements in those pairs are swapped. For example, if $ a=[1,2,3,4,5] $ , and the pairs $ 1 \leftrightarrow 4 $ and $ 3 \leftrightarrow 5 $ are swapped, then the resulting array is $ [4, 2, 5, 1, 3] $ .

As a result of these swaps, exactly one element will not change position. You need to find this element.

To do this, you can ask several queries. In each query, you can pick two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ). In return, you will be given the elements of the subarray $ [a_l, a_{l + 1}, \dots, a_r] $ sorted in increasing order.

Find the element which did not change position. You can make at most $ \mathbf{15} $ queries.

The array $ a $ is fixed before the interaction and does not change after your queries.

Recall that an array $ b $ is a subarray of the array $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

In the first test, the interaction proceeds as follows.

 SolutionJuryExplanation $ \texttt{2} $ There are 2 test cases. $ \texttt{5} $ In the first test case, the hidden array is $ [4,2,5,1,3] $ , with length $ 5 $ . $ \texttt{? 1 4} $  $ \texttt{1 2 4 5} $ The solution requests the subarray $ [4,2,5,1] $ in increasing order, and the jury responds with $ [1,2,4,5] $ . $ \texttt{? 3 5} $  $ \texttt{1 3 5} $ The solution requests the subarray $ [5,1,3] $ in increasing order, and the jury responds with $ [1,3,5] $ . $ \texttt{! 2} $ The solution has somehow determined that $ a_2=2 $ , and outputs it. Since the output is correct, the jury continues to the next test case. $ \texttt{3} $ In the second test case, the hidden array is $ [1,3,2] $ , with length $ 3 $ . $ \texttt{? 1 1} $  $ \texttt{1} $ The solution requests the number $ [1] $ only, and the jury responds with $ [1] $ . $ \texttt{! 1} $ The solution has determined that $ a_1=1 $ , and outputs it. Since the output is correct and there are no more test cases, the jury and the solution exit.Note that the line breaks in the example input and output are for the sake of clarity, and do not occur in the real interaction.

## 样例 #1

### 输入

```
2
5

1 2 4 5

1 3 5

3

1```

### 输出

```
? 1 4

? 3 5

! 2

? 1 1

! 1```

# 题解

## 作者：bmatrix (赞：5)

观察题面：$n\le10^4$，询问次数 $\le15$，因此考虑二分。

用 $x$ 表示没有被交换过的那个元素。

考虑当询问区间 $[l,r]$ 时，得到的序列满足什么条件，才能确定 $x$ 在这个区间内。

考虑一个在交换前的序列的 $[l,r]$ 区间内的元素 $y$，由题意 $a_y=y$。设和 $y$ 交换的元素为 $z$，则 $z$ 和区间 $[l,r]$ 的关系只有两种情况：
- $z\notin[l,r]$。此时这个区间会“进来”一个外面的元素，“出去”一个里面的元素。
- $z\in[l,r]$。此时这两个元素还在区间内。

因此，**如果一个区间内的元素全部被交换过，则在评测机回答的序列中，值在 $\bold[l,r]$ 之间的元素个数一定是偶数。**  
（可以理解为：要么出去，要么成对留下）

那么我们只要查出值在 $[l,r]$ 之间的元素个数，如果为奇，说明 $x$ 在区间 $[l,r]$ 中；为偶则不在。

二分法缩小询问范围，$l=r$ 时结束循环。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e4 + 5;
int main() {
    int t, n; 
    cin >> t;
    while(t--) {
        cin >> n;
        int l = 1, r = n;
        do {
            int mid = (l + r) / 2;
            cout << "? " << l << ' ' << mid << endl;
            int cnt = 0, x;
            for(int i = l; i <= mid; ++i) {
                cin >> x;
                if(x >= l && x <= mid) ++cnt;
            }
            if(cnt & 1) r = mid;
            else l = mid + 1;
        } while(r > l);
        cout << "! " << l << endl;
    }
    return 0;
}
```

---

## 作者：Super_Cube (赞：2)

# Solution

先来考虑如果询问 $[l,r]$，怎么判断不动点是否在区间内？

对于下标 $x\in[l,r]$，假设与其交换的下标为 $y$，如果 $a_x\in[l,r]$，则 $y\in[l,r]$（因为交换操作使得 $a_x\gets y$）；若 $a_x\not\in [l,r]$，则 $y\not\in[l,r]$，不会对区间有贡献。所以得到结论：若询问 $[l,r]$ 给出的序列中值在 $[l,r]$ 的个数为偶数，那么不动点不在区间内。

对于原问题，尝试二分出不动点位置。若当前二分到的位置为 $x$，利用前面所述判断 $[1,x]$ 中是否存在不动点，若有右边界左调，否则左边界右调。

# Code
```cpp
#include<bits/stdc++.h>
int T,n,l,r,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		l=1;r=n;
		while(l<=r){
			int mid=l+r>>1,cnt=0;
			printf("? 1 %d\n",mid);fflush(stdout);
			for(int i=1,x;i<=mid;++i)
				scanf("%d",&x),cnt^=(x<=mid);
			if(cnt&1)ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("! %d\n",ans);fflush(stdout);
	}
	return 0;
}
```

---

## 作者：ningago (赞：2)

## 扯淡

在开场 $12min$ 后，群里出现了这样一张图：![](https://cdn.luogu.com.cn/upload/image_hosting/b26uda5w.png)

>-D?

>-????

>-?

>-/bx

>-Dtm 交互

## 题解

作为一个训练有素的 oier，看到数字 $15$ ，我们知道这一定是个卡着算出来的数字，不难注意到 $\log_2 n=\log_2 10^4 = 13.28...$。

根据交互题的多年经验，肯定要跟二分扯上点什么关系。

于是我们转换成了考虑这样一个问题：给定区间 $[l,r]$ 及其升序排序，如何判断关键点在不在区间内？

注意到交换是成对出现的，如果区间长度为奇数的话会很难操作，我们不妨把区间长度看作偶数（事实上，在二分中可以通过一些方法将查询全部变为偶数长度。

对于 $[l,r]$ 中的元素 $a_i$，它的交换情况可能有三种：与区间内元素交换，与区间外交换，不交换（关键点）。

形式化地说，$a_i$ 要么与 $a_j(j\in[l,r])$ 交换，要么与 $a_j(j\not\in [l,r])$ 交换，要么与 $a_j(j=i)$ 交换。（尽管第三种情况是属于第一种的，为了方便分类讨论这样处理）

我们发现如果是区间内交换的话，显然必然有另一个 $a_j$ 与之匹配，也就是说区间内交换的 $a_i$ 的个数是偶数。

但特殊情况就在于，根据区间内交换的定义，关键点也属于区间内交换，这样的话就是奇数。

因此，对于某个区间 $[l,r]$ ，我们判断了“区间内交换”的个数的奇偶性，就判断了关键点在不在区间内部。

（事实上，你可以判断“区间外交换”，这是一模一样的。）

解决了这个问题就是二分的模板了。

## 细节

有个问题，上文提到的将区间长度变成偶数的方式如何实现？

显然不能无脑加一，比如区间 $[1,5]$ ，$mid=3$，无脑加一就变成了 $mid=4$，询问次数就寄寄了。

于是我们对于这种情况，取 $mid+1$ 和 $mid-1$ 中更优的那个，如果一样，就无脑 $+1$ 就行了。

## Code:

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
#define N 100010

int T,n;
int a[N];

int main()
{
	cin >> T;
	while(T--)
	{
		cin >> n;
		int l = 1,r = n,mid,ans;
		while(l <= r)
		{
			mid = l + r >> 1;
			if(r - l + 1 == 1)
			{
				ans = mid;
				break;
			}
			if(r - l + 1 == 2)
			{
				//printf("A\n");
				int x;
				cout.flush();
				cout << '?' << ' ' << l << ' ' << l << '\n';
				cin >> x;
				if(x == l)
					ans = l;
				else
					ans = r;
				break;
			}
			if((mid - l + 1) & 1)
			{//分讨好的读者大可不必这样写
				if(r - mid < mid - l + 1)
					mid--;
				else
					mid++;
			}
			cout.flush();
			cout << '?' << ' ' << l << ' ' << mid << '\n';
			int cnt = 0;
			for(int i = 1;i <= (mid - l + 1);i++)
			{
				cin >> a[i];
				if(a[i] < l || a[i] > mid)
					cnt++;
			}
			if(cnt & 1)
				r = mid;
			else
				l = mid;
		}
		cout.flush();
		cout << "! " << ans << '\n';
	}
	return 0;
}
```

End.

---

## 作者：LRL65 (赞：1)

思路： **二分**

- 怎么看出来二分的呢？

要学会关注数据范围。只能问 $15$ 次，而 $2^{14} \leq 10^4 \leq 2^{15} $ ，所以第一个想到的就是二分。

- 如何二分？

注意到 $n$ 是个奇数，所以考虑奇偶性。我们发现一个性质：**当一个区间内 原本属于这个区间的数 的个数为奇数时**，那个没交换的数必定在这个区间内。很简单就能证明，因为只能两两交换，每个数只能经历一次交换，总个数为奇数，那么必有一个是没有交换的。如果你还没有理解，可以举个例子，比如: `3 2 1 5……` 你看，前四个数中有 $3$ 个是属于 $1 \sim 4$ 这个区间内的，也就是原来的区间内的，所以答案必在这个区间内。

那么实现就很简单了，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,x;
int main() {
    cin>>t;
    while(t--) {
        cin>>n;
        int l=1,r=n;
        while(l<r) { 
            int mid=(l+r)>>1;
            cout<<"? "<<l<<" "<<mid<<endl;
            fflush(stdout);
            int cnt=0;
            for(int i=l;i<=mid;i++) {
                cin>>x;
                if(x>=l&&x<=mid)cnt++;
            } 
            if(cnt%2==1)r=mid;
            else l=mid+1;
        }
        cout<<"! "<<l<<endl;
        fflush(stdout);
    }
}
```


---

## 作者：FReQuenter (赞：0)

## 题意

这是一道交互题。

给你一个 $n$ ，有一个长度为 $n$ 的数列（ $n$  是奇数）。这个数列中，除了一个数，其他的数都两两交换了。你可以通过 `? l r` 的格式询问，来获取 $l$ 和 $r$ 中的所有数。最多只能询问 $15$ 次。以 `! ans` 的形式输出答案。

## 思路

因为只能两两交换，每个数只能交换一次，那么在同一个区间内，每个数有两种交换方法：

- 和区间外的数交换。如果答案不在区间内，一旦交换奇数个数，剩下奇数个数就无法在本区间内交换完成。

- 和区间内的数交换。同样也只能交换偶数个数，原因同上。

综上，一旦一个区间里出现了奇数个外区间的数，那答案一定在这个区间里。

考虑到只能查询 $15$ （ $\log 10^4 \le 15$ ）次，我们考虑使用二分。我们可以二分区间的左右端点，将它一分为二。若答案在当前区间内，则将当前区间一分为二继续二分，否则二分另一半区间。时间复杂度 $O(n \log n)$ 。

## 代码

```cpp
#include<iostream>
using namespace std;
bool check(int l,int mid){
    int ans=0;
    cout<<"? "<<l<<' '<<mid<<endl;
    for(int i=l;i<=mid;i++){
        int x;
        cin>>x;
        if(x<l||x>mid) ans++;
        //统计多少个数不在区间里
    }
    return ((mid-l+1-ans)&1);
    //如果在区间里的数是奇数，则说明答案在区间里
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int l=1,r=n;
        while(l<r){
            int mid=(l+r)>>1;
            if(check(l,mid)) r=mid;
            else l=mid+1;
        }
        cout<<"! "<<l<<endl;
    }
}
```

---

