# Odd Swap Sort

## 题目描述

#### 题目大意

给定一个数列 $a_1,a_2,...,a_n$ 。

你可以执行若干次如下的操作：

- 选择一个整数 $i\ (\ 1\leq i< n\ )$ ，如果 $a_i+a_{i+1}$ 为奇数，交换 $a_i$ 和 $a_{i+1}$ 。

问是否可以将该数列排序成单调不降数列。

## 样例 #1

### 输入

```
4
4
1 6 31 14
2
4 2
5
2 9 6 7 10
3
6 6 6```

### 输出

```
Yes
No
No
Yes```

# 题解

## 作者：Galois_Field_1048576 (赞：2)

题目不翻译了。  
考虑在**原**数列中的两个数 $a_i,a_j$，如果 $a_i$ 和 $a_j$ 的奇偶性相同，那么 $a_i,a_j$ 的相对方位不会变（也就是说若 $i<j$，则进行操作后的数组 $a'$ 中 $i$ 的位置 < $j$ 的位置，反之亦然）。  
那么如果 $a_j>a_i$ 且 $j>i$ 呢，那么只能输出 `no` 了。  
否则输出 `yes`。  
```cpp
/*
 * @Date: 2022-02-14 23:13:54
 * @LastEditors: 1048576
 * @FilePath: \code\CF1638B.cpp
 * @MajorAlgorithm:
 */
#include <bits/stdc++.h>
using namespace std;
int t, n, a[100005], odd, even;
bool flg;
int main()
{
    cin >> t;
    while (t--)
    {
        odd = even = -0x3f3f3f3f;
        flg = 0;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            if (a[i] & 1)
            {
                odd = max(odd, a[i]);
                if (a[i] < odd)
                {
                    cout << "NO" << endl;
                    flg = 1;
                    break;
                }
            }
            else
            {
                even = max(even, a[i]);
                if (a[i] < even)
                {
                    cout << "NO" << endl;
                    flg = 1;
                    break;
                }
            }
        if (!flg)
            cout << "YES" << endl;
    }
    return 0;
}
```

---

## 作者：清烛 (赞：2)

upd：感谢评论区，fixed a typo.

注意到奇偶性相同的数字加起来为偶数，即其相对位置是不会发生改变的。

所以只要对于一个数，其前面有比他大的奇偶性相同的数，就不可能排好序。

否则我们总能通过将奇偶性不同的相邻数字交换以达到排序的目的。

```cpp
const int maxn = 1e5 + 5;
int n, a[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        set<int> odd, even;
        bool flg = 1;
        FOR(i, 1, n) {
            if (a[i] & 1) {
                if (!odd.empty() && (*odd.rbegin()) > a[i])
                flg = 0;
                odd.insert(a[i]);
            } else {
                if (!even.empty() && (*even.rbegin()) > a[i])
                flg = 0;
                even.insert(a[i]);
            }
        }
        print(flg ? "YES" : "NO");
    }
    return output(), 0;
}
```

---

## 作者：miao5 (赞：0)

不错的一道结论题。

题目给你一个数组 $a$，你每次操作可以选择两个相邻的数，如果这两个数的奇偶性不同，那么你可以交换这两个数，求能不能经过若干次操作，把数组 $a$ 变成非降序的数组。

首先，一个数如果不在它在非降序数组里应该在的位置，那么我们必须通过操作把它换过去。我们观察性质可以得知，如果这个数的位置和目标位置之间必须没有奇偶性与这个数相同的数，否则我们就不能把这个数换过去。

之后这道题就变成了判断对于数组中的所有同奇偶性的数，所组成的子数组是不是一个非降序的数组。

这样的话我们对于奇数和偶数各维护一个当前最大值，之后从 $1$ 到 $n$ 枚举一遍数组，如果遇到一个数比同奇偶性的当前最大值要小，那么就代表这个更小的数要换到最大值的前面，但是由于这两个数是同奇偶性的，那么就可以判定不合法了。

如果奇数和偶数各自所组成的子数组，都满足不降序，那么就可以判定合法。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int read(){
	int s=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)){
		s=s*10+c-'0';
		c=getchar();
	}
	return s;
}
int a[200005];
int main(){
	int t;
	t=read();
	while(t--){
		int n;
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		int x=0,y=0;
		bool flag=0;
		for(int i=1;i<=n;i++){
			if(a[i]%2==0){
				if(a[i]<x) flag=1;
				else x=a[i];
			}
			else{
				if(a[i]<y) flag=1;
				else y=a[i];
			}
		}
		if(flag) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}
```

---

## 作者：zhongcy (赞：0)

[CF Problem](https://codeforces.com/problemset/problem/1638/B)


### Solution

------------

条件 $ a_i + a_{ i + 1 } $ 是奇数意味着我们只能交换两个不同奇偶性的元素。

令 $ a $ 中的奇数序列为 $ o $。若 $ o $ 不是非递减数列，则必然存在至少一个 $ i $ 使  $ o_i > o_{ i + 1 } $。显然，这两个数无法交换，因为 $ o_i + o_{ i + 1 } $ 为偶数。故 $ o $ 必为非递减数列。

对于 $ a $ 中的偶数序列 $ e $，同理有  $ e $ 必为非递减数列。


### Code

------------

若直接暴力 $ O ( n ^ 2 ) $ 求解，显然过不了本题。因此可以考虑定义两个变量，分别表示离当前最近的奇数和偶数。

如果当前枚举到奇数，且记录的奇数比它大，则说明奇数序列不是非递减数列。

同理，如果当前枚举到偶数，且记录的偶数比它大，则说明偶数序列不是非递减数列。

时间复杂度 $ O ( tn ) $ 。


```cpp
#include<bits/stdc++.h>
#define N 100001
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)
	{
		int n;cin>>n;
		int a[N];
		for(int i=1;i<=n;i++)
			cin>>a[i];
		bool f=1;//记录答案
		int last_odd=0,last_even=0;//记录离当前最近的奇数和偶数
		for(int i=1;i<=n;i++)
		{
			if(a[i]%2)
			{
				if(a[last_odd]>a[i]){f=0;break;}//记录的奇数比当前数大
				last_odd=i;//更新奇数
			}
			else
			{
				if(a[last_even]>a[i]){f=0;break;}//记录的偶数比当前数大
				last_even=i;//更新偶数
			}
		}
		if(f) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
} 
```



---

## 作者：lsr1409111459 (赞：0)

### 2.CF1638B Odd Swap Sort

#### 2.1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1638B)）

##### 2.1.1 题目大意

给定一个数列 $a_1,a_2,...,a_n$ 。

你可以执行若干次如下的操作：

- 选择一个整数 $i\ (\ 1\leq i< n\ )$ ，如果 $a_i+a_{i+1}$ 为奇数，交换 $a_i$ 和 $a_{i+1}$ 。

问是否可以将该数列排序成非递减数列。

##### 2.1.2 输入格式

第一行一个整数 $t\ (\ 1\leq t\leq 10^5\ )$ ，表示测试组数。

每组第一行一个整数 $n\ (\ 1\leq n\leq 10^5)$ ，表示数列的长度。

每组第二行 $n$ 个整数 $a_1,a_2,...,a_n\ (\ 1\leq a_i\leq 10^9\ )$ ，表示给定的数列。

可以保证 $t$ 组测试的 $n$ 的和不超过 $2·10^5$ 。

##### 2.1.3 输出格式

共 $t$ 行。

对于每组测试，如果你可以将该数列排序成非递减数列，输出 ``Yes`` ；否则，输出 ``No`` 。

##### 2.1.4 样例

###### 输入 #1

```cpp
4
4
1 6 31 14
2
4 2
5
2 9 6 7 10
3
6 6 6
```

###### 输出 #1

```cpp
Yes
No
No
Yes
```

##### 2.1.5 样例解释

- 第一组测试，可以交换 $31$ 和 $14$ （ $31+14=45$ 是奇数）然后得到非递减数列 $[1,6,14,31]$ 。
- 第二组测试，我们想要得到非递减数列就一定要交换 $4$ 和 $2$ ，但这是不可能的，因为 $4+2=6$ 是偶数。
- 第三组测试，没有方法可以使其排序成非递减数列。
- 第四组测试，该数列已经是非递减数列了。

#### 2.2 解题思路

冒泡排序！我们回顾冒泡排序，如果想将一个数放到它该放的位置上，则它需要和它后面所有比它小的数字交换。所以本题我们要考虑的就是：是否有数字存在后面有 **比它小** 的数字且 **奇偶性** 和它相同。

我们可以 $O(n^2)$ 暴力的去判断这个事情，不过看了眼数据范围，还是算了。

我们考虑从后往前考虑，一个数一定会和它前面所有比它大的数字交换。所以我们只需要从后向前枚举，记录枚举过的数列中最小的奇数和偶数。

如果当前枚举到奇数且记录的奇数比它小，则说明该奇数后面存在一个 **比它小** 的 **奇数** 。

同理，如果当前枚举到偶数且记录的偶数比它小，则说明该偶数后面存在一个 **比它小** 的 **偶数** 。

上述两种情况都是无法将原数列排序成非递减数列的。其它情况即可以。

#### 2.3 解题代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int T,n;
int a[100010];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        int odd=2147483647,even=2147483646;//初始的奇偶数一定比所有数都大（大于1e9）
        bool flag=true;
        for(int i=n;i>=1;i--)
        {
            if(a[i]%2)
            {
                if(odd<a[i]){flag=false;break;}
                odd=a[i];
            }
            else
            {
                if(even<a[i]){flag=false;break;}
                even=a[i];
            }
        }
        if(flag)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

#### 2.4 解题心得

千万别想复杂。此题考场上首先想将原数列排序然后记录下标，发现做不了。又想二分答案，写完发现不满足答案单调。在实现算法前一定要考虑算法是否正确，否则实现也是白实现。

此题考场接近一小时，为 D 题没时间做造成不小的影响。

---

## 作者：TernaryTree (赞：0)

## 题目大意

给定 $n$ 个元素的数列 $s$，每次可以将相邻两个相加为奇数的元素交换，问有没有一种方法经过若干次交换使 $s$ 非严格递增（$\forall 1\le i\le n - 1, s_i \le s_{i+1}$）。

## 思路分析

因为每次交换的两个数相加为奇数，所以绝对是一奇一偶。

也就是说，奇数之间的顺序不会发生变化，偶数之间的顺序也不会发生变化，只也奇偶之间才会产生顺序的变化。

那么该题就转化成：奇数子序列是否非严格递增与偶数子序列是否非严格递增。

因为如果奇数子序列呈非严格递增且偶数子序列呈非严格递增时，总有一种方法使整个数列非严格递增。

所以只要判断奇偶，并判断非严格递增就可以了。

## 完整代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 1;

int t, n;
int arr[maxn];
int odd_last = 0, even_last = 0;
bool flag = false;

void init() {
    flag = false;
    odd_last = even_last = 0;
}

int main() {
    cin >> t;
    while (t--) {
        init();
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
            if (arr[i] % 2 == 0) {
                if (arr[i] < arr[even_last] && !flag) {
                    cout << "No" << endl;
                    flag = true;
                }
                even_last = i;
            } else {
                if (arr[i] < arr[odd_last] && !flag) {
                    cout << "No" << endl;
                    flag = true;
                }
                odd_last = i;
            }
        }
        if (!flag) cout << "Yes" << endl;
    }
    return 0;
}

```

[R69409852](https://www.luogu.com.cn/record/69409852)，完美AC。

---

## 作者：CmsMartin (赞：0)

## 题意简述

现在有一个序列 $a_1 , a_2,\dots,a_n$ ，你可以交换相邻两个和为奇数的数，问是否能够使序列有序。可以输出 `Yes` , 不可以输出 `No`。

[题目传送门](https://codeforces.com/problemset/problem/1638/B)

## 思路

也是一道水题。

显然这道题跟逆序对有关。由于交换排序，所以每一对逆序对都一定会被交换。所以只需检查逆序对中是否有和为偶数的就行了。

我们可以建立两个 `multiset` 来分别保存奇数和偶数。根据奇偶性，显然 奇数+偶数=奇数。所以如果 $a_i$ 是奇数，那么我们只需在奇数多重集中查找 $a_i$ 。若 $a_i$ 不为第一个元素，则表示有可以与其和为偶数的逆序对，答案为 `No`，若为第一个元素，则删除该元素（因为逆序对是统计向后的元素，前面的元素为冗余信息）。如果 $a_i$ 是偶数，那么我们只需在偶数多重集中查找 $a_i$ 。若 $a_i$ 不为第一个元素，则表示有可以与其和为偶数的逆序对，答案为 `No`，若为第一个元素，则删除该元素（因为逆序对是统计向后的元素，前面的元素为冗余信息）。
## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int T;
int N;
int Num[200010];
multiset< int > odd;
multiset< int > even;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        cin >> N;
        odd.clear();
        even.clear();
        for(int i = 1; i <= N; i++) {
            cin >> Num[i];
            if(Num[i] % 2 == 0) {
                even.insert(Num[i]);
            }
            else {
                odd.insert(Num[i]);
            }
        }
        for(int i = 1; i <= N; i++) {
            if(Num[i] % 2 == 0) {
                multiset< int >::iterator it = even.find(Num[i]);
                if(it != even.begin()) {
                    cout << "No" << endl;
                    goto end;
                }
                even.erase(it);
            }
            if(Num[i] % 2 == 1) {
                multiset< int >::iterator it = odd.find(Num[i]);
                if(it != odd.begin()) {
                    cout << "No" << endl;
                    goto end;
                }
                odd.erase(it);
            }
        }
        cout << "Yes" << endl;
        end:
            continue;
    }   
    return 0;
}
```

---

## 作者：windflower (赞：0)

**简要题意：**
>当且仅当两个相邻的数之和为奇数才可以交换这两个数的位置，请问能否通过交换使得整个序列有序。  

**思路分析：**  
首先，只有相邻的数能够交换，这一点和冒泡排序很像。那么我们也可以参考其思路。每一轮都将最小的待排序数移到最左边。显然每一轮冒泡时，对之前几轮已经有序的最左边的数没有影响。那么我们就可以递推地来理解。 n 个数进行一轮排序后，最左边的已经是最小的了，那么只需要判断后 $n-1$ 个数是否能排成有序。

**关键点：**
- 每次将最小的移至最左边。
- 每一轮不改变元素的相对位置（除了最小的元素）。
- 若最小的无法移到最左边，则无法排成有序。

那么答案就呼之欲出了，在某一轮排序后，无序部分最小的元素左侧的元素必须均与该元素奇偶性不同。  
又知道，无序部分的最小元素一定比它左侧的无序部分元素小，比有序部分元素大。那么就可以进一步简化成：对任意元素，其左侧的比它大的元素必须均与该元素奇偶性不同。  

~~我第一遍就是照着这个思路打代码的，还离散化后用了两个树状数组不知道哪里 WA 了。写题解得时候才发现树状数组忘记初始化 0 了，加了初始化以后光初始化就超时了 emmm 。~~    

后来仔细一想，发现题目还可以简化得更简单：任意元素左侧比它大得元素都与它奇偶性不同，逆否命题就是任意元素左侧与它奇偶性相同得元素都比它小。那么就更简单了，只需要奇数元素和偶数元素分别单调递增就行了。  

**附 AC 代码：**  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		vector<int>odd,even;
		while(n--){
			scanf("%d",&a);
			if(a%2)odd.push_back(a);
			else even.push_back(a);
		}
		int flag=0;
		for(int i=1;i<odd.size();i++)if(odd[i]<odd[i-1])flag=1;
		for(int i=1;i<even.size();i++)if(even[i]<even[i-1])flag=1;
		if(flag)cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}
```
  
  
**附超时的树状数组代码:** 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N],b[N],c[N],t,n;
struct bitset{
	int a[N];
	void clear(){
		memset(a,0,sizeof(a));
	}
	void add(int x,int y){
		while(x<=n){
			a[x]+=y;
			x+=x&-x;
		}
	}
	int ask(int x){
		int sum=0;
		while(x){
			sum+=a[x];
			x-=x&-x;
		}
		return sum;
	}
}odd,even;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		odd.clear();
		even.clear();
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),c[i]=b[i]=a[i];
		sort(a+1,a+n+1);
		int len=unique(a+1,a+n+1)-a-1;
		for(int i=1;i<=n;i++)b[i]=lower_bound(a+1,a+len+1,b[i])-a;
		for(int i=1;i<=n;i++){
			if(c[i]%2){
				odd.add(b[i],1);
				if(odd.ask(len)-odd.ask(b[i])){
					cout<<"NO"<<endl;
					goto end;
				}
			}else{
				even.add(b[i],1);
				if(even.ask(len)-even.ask(b[i])){
					cout<<"NO"<<endl;
					goto end;
				}
			}
		}
		cout<<"YES"<<endl;
		end:;
	}
	return 0;
}
```


---

