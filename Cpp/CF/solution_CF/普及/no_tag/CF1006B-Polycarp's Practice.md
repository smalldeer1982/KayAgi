# Polycarp's Practice

## 题目描述

#### 题目翻译

给定长度为n的序列，要求分成k段，最大化每段最大值的和

## 样例 #1

### 输入

```
8 3
5 4 2 6 5 1 9 2
```

### 输出

```
20
3 2 3```

## 样例 #2

### 输入

```
5 1
1 1 1 1 1
```

### 输出

```
1
5
```

## 样例 #3

### 输入

```
4 2
1 2000 2000 2
```

### 输出

```
4000
2 2
```

# 题解

## 作者：jiang_cheng (赞：8)

# 一篇适合萌新~~（就像我）~~的题解

------------
## 先附上代码：
~~~cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
 
using namespace std;
 
int n, k, m;
long long ans;
 
struct E {
  int a, b;
} e[2001];
 
bool C(E e1, E e2) {
  return e1.a > e2.a;
}
 
bool B(E e1, E e2) {
  return e1.b < e2.b;
}
 
int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a;
    e[i].b = i;
  }
  sort(e + 1, e + n + 1, C);
  for (int i = 1; i <= k; i++) {
    ans += e[i].a;
  }
  cout << ans << endl;
  sort(e + 1, e + 1 + k, B);
  for (int i = 1; i <= k; i++) {
    if (i != k && i != 1) {
      m = e[i].b - e[i - 1].b;
      cout << m << " ";
      n -= m;
    } else if (i == 1 && k != 1) {
      cout << e[1].b << " ";
      n -= e[1].b;
    } else {
      cout << n;
    }
  }
return 0;
}
~~~

------------

## 思路
#### 用两次排序（结构体哦~）
#### 第一次，排这些数大小，并选较大的k个数相加，求出的即为最大化每段最大值的和
#### 第二次，排选中的k个数的位置大小，小的前，求出来的即为这些数在原数列上出现的地方。
#### 最后循环：特判头和尾，其余用现在循环到的数的位置减去上个数的位置算出的就是每段多长，并输出。

------------

##### 终于写完一篇题解了~~（记得点赞！！！）~~





---

## 作者：K_Madoka (赞：4)

#### 这是一道挺简单的题，只需要快排sort两下就行了。
思路：先把每个位上的数值从高到低排一下，取前k个，再把位置从低到高排一下，分摊到每一组。
####  附上代码吧

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5;
struct num
{
	int val,pos;
}a[maxn];
int cmp(num a, num b)
{
	return a.val>b.val;
}
int cmp2(num a, num b)
{
	return a.pos<b.pos;
}
int main()
{
	int n, k, ans=0;
	cin >> n >> k;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i].val;
		a[i].pos=i;	
	}
	sort(a+1,a+n+1,cmp);//无敌排列
	for(int i=1;i<=k;i++)ans+=a[i].val;
	cout<<ans<<endl;
	sort(a+1,a+k+1,cmp2);//无敌排列
	if(k==1)//特殊情况
	{
		cout<<n<<endl;
		return 0;
	}
	else
	{
		for(int i=1;i<=k;i++)
		{
			if(i==1)cout<<a[i].pos;
			else if(i==k)cout<<' '<<n-a[k-1].pos;
			else cout<<' '<<a[i].pos-a[i-1].pos; 
		}
	}
	cout<<endl;
	return 0;
} 
```
哈哈，又写了一篇题解。

---

## 作者：_Cloud_ (赞：3)

## 贪心

### 思路：贪前k个最大值
开一个结构体，记录id,num（下标，数值）。

sort排序两遍，第一遍排序数值（降序）找前k大的数，全部选中。

第二遍按下标排序，每次记前面一次选中的数的下标，当再次找到选中值的时候，用当前下标i减去上一次下标p即为答案。

#### 注意：最后一次输出不是i-p,而是n-p（后面也要包含）

### $Code$

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 2005;

struct Node {
    int num, id;
} a[N];

bool cmp1(Node x, Node y) {//第一遍排序
    return x.num > y.num;
}

bool cmp2(Node x, Node y) {//第二遍排序
    return x.id < y.id;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i].num),
        a[i].id = i;
    
    sort(a + 1, a + 1 + n, cmp1);

    int ans = 0;

    for (int i = 1; i <= k; i++) {
        // printf("%d\n", ans);
        ans += a[i].num;//前i个最大值一定能被选中
        a[i].num = -2147483647;//选中并附极小值，防止和其他值撞车
    }

    sort(a + 1, a + 1 + n, cmp2);

    printf("%d\n", ans);

    int p = 0;

    for (int i = 1; i <= n; i++) {
        if (a[i].num == -2147483647 && k) {//遍历到选中值
            if (k == 1) {//特判最后一次
                printf("%d\n", n - p);
                k--;
            } else {
                printf("%d ", i - p);
                p = i;
                k--;
            }
        }
    }

    return 0;
}
```




---

## 作者：信守天下 (赞：2)

## 题目描述

给定长度为n的序列，要求分成k段，最大化每段最大值的和

## 输入格式
第一行$n$和$k$ (1 <= $k$ <= $n$ <= 2000)

第二行序列$a(1)$ ,$a(2)$ , ... ,$a(n)$(1 <= $a(i)$ <=2000)

## 输出格式
输出最大化的值以及k段的长度（输出任意一种）
# CF传送门[CF1004B](https://codeforces.com/contest/1006/problem/B)
# 思路
1,排序排出前$k$个数值
 
2,再把位置从低到高排一下,还原数组

3,碰到前$k$个数中其中一个数就分割,分摊到每一组。
# $code$
~~~cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int kMaxN = 1000001;
struct A{
  int x, y;
}a[kMaxN];
int cmp1(A a1 , A a2) {
  return a1.x > a2.x;//从大到小排数值
}
int cmp2(A a1 , A a2) {
  return a1.y < a2.y;//排位置
}
int main() {
  int n , k , ans = 0;
  cin >> n >> k;
  for (int i = 1; i <= n; i++){
    cin >> a[i].x;//读数
    a[i].y = i;//位置
  }
  sort(a + 1, a + n + 1, cmp1);//第一次排序
  for (int i = 1; i <= k; i++) ans += a[i].x;//ans存最大值的和
  cout << ans << endl;
  sort(a + 1, a + k + 1, cmp2);//还原数组
  if (k == 1){//特判
    cout << n;
    return 0;
  }else{
    for (int i = 1 ; i <= k ; i++) {
      if (i == 1)cout << a[i].y << " ";
      else if (i == k)cout << n - a[k - 1].y << " ";
      else cout << a[i].y - a[i - 1].y << " ";
    }
  }
  return 0;//圆滑的结束
}
~~~
# 本蒟蒻第一篇题解，支持一下吧！

---

## 作者：Eason_AC (赞：2)

## Content
给定一个长度为 $n$ 的数列，试将其分成 $k$ 段，使得每一段中的最大值的和最大。

**数据范围：$1\leqslant k,n,a_i\leqslant 2000$。**
## Solution
我们不难发现，最优的方案其实就是将前 $k$ 大的数各自单独放在一段里面，所以我们排序得到前 $k$ 大的数，再找到他们的位置。那么如何记录每一段里面的其他数呢？我的方案是，将前 $k-1$ 大的数作为每一段的最后一个数存储，剩下的那个数所在的段就是没有被前面的 $k-1$ 个段占的部分，这下就可以轻松地解决问题了。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int a[2007], sum, n, k, ids[2007];
struct node {
	int val, id;
	bool operator < (const node& ou) const {return val > ou.val;}
}a1[2007];

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		a1[i].val = a[i], a1[i].id = i;
	}
	sort(a1 + 1, a1 + n + 1);
	for(int i = 1; i <= k; ++i) ids[i] = a1[i].id, sum += a1[i].val;
	sort(ids + 1, ids + k + 1);
	printf("%d\n", sum);
	int lastans = 0;
	for(int i = 1; i < k; ++i) {printf("%d ", ids[i] - ids[i - 1]); lastans += ids[i] - ids[i - 1];}
	printf("%d", n - lastans);
	return 0;
}
```

---

## 作者：Weak_Konjak (赞：1)

## 分析
首先，题目中说分成了k段，要让每段最大值之和最大。

那么,一共就只有k个数相加，那么如何使它最大呢？

这k个数就是前k大的数，所以最大化的值就是前k大的数之和，那k段的长度呢？

将前k大的数在原数列中加粗，则序列长度就是后面的数下标减去前一个数的下标：

### 样例1：

8 3

**4** 2 **6** 5 1 **9** 2

第1段长度：**4**的下标

第2段长度：**6**的下标减去**4**的下标

第3段长度：**n**减去**4**的下标

### 	注意：
	第一段比较特殊，由于前面没数可减，所以不用减

	最后一段比较特殊，因为要覆盖全数列，所以应该用n去减，不然最后的2无处可去

## 代码实现思路

先从大到小排序，累加前k的值，就是最大值。

为求序列长度，需要求出下标，这时，就要用到结构体。

定义struct number 包含 数值num 和 下标data

对结构体进行排序，就可以得到前k大的数的下标，将其存入新数组a，

对新数组a进行排序，最后输出a[i]-a[i-1]（最后一个特别处理）


## 代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[2001],n,k,ans;
struct number{
	int num;
	int data;
}s[2001];
bool cmp(number a,number b){
	return a.num>b.num;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>s[i].num;
		s[i].data=i;
	}
	sort(s+1,s+1+n,cmp);
	for(int i=1;i<=k;i++) a[i]=s[i].data,ans+=s[i].num;
	sort(a+1,a+1+k);
	cout<<ans<<endl;
	for(int i=1;i<k;i++){
		cout<<a[i]-a[i-1]<<' ';
	}
	cout<<n-a[k-1];
}
```


---

## 作者：小闸蟹 (赞：1)

```cpp
// 首先，我们能观察到这一题要求的最大获利就是数列前k大的数之和
// 通过排序，我们能找出前k大的数
// 然后，我们把这前k大的数的位置找出来，用它们来作为隔板分割数列
// 注意头尾的操作，开头记个0，尾部记个n
#include <iostream>
#include <vector>
#include <algorithm>

class Pair
{
public:
    int Key, Pos;   // 记在Pos位上的数为Key

    Pair() = default;
    Pair(int k, int p)
        : Key(k), Pos(p)
    {
    }

    bool operator<(const Pair &rhs) const noexcept
    {
        return Key > rhs.Key || (Key == rhs.Key && Pos < rhs.Pos);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<Pair> Vec(n);
    for (int i = 0; i < n; ++i)
    {
        int t;
        std::cin >> t;
        Vec[i] = Pair(t, i + 1);
    }
    std::sort(Vec.begin(), Vec.end());

    int Ans = 0;    // 前k大的数之和
    for (int i = 0; i < k; ++i)
    {
        Ans += Vec[i].Key;
    }
    std::cout << Ans << std::endl;

    std::vector<int> Arr(k);
    for (int i = 0; i < k; ++i)
    {
        Arr[i] = Vec[i].Pos;
    }
    std::sort(Arr.begin(), Arr.end());

    int Last = 0;   // 开头记个0
    for (int i = 0; i < k - 1; ++i)
    {
        std::cout << Arr[i] - Last << ' ';  // 中间的直接两两相减即可
        Last = Arr[i];
    }
    std::cout << n - Last << std::endl; // 尾部记个n

    return 0;
}
```

---

## 作者：Parat_rooper (赞：0)

# 题面翻译：

 有一个表示题单难度的序列 $a$，小$P$需要在刚好$k$天的时间里按顺序解决所有的题目，每天至少解决$1$道题。

每天的得分为当天解决的最难题目，求最大得分以及每天做的题目数量（答案不唯一）。

**解题思路：**

看前面几位大佬都是两遍排序过的，我这里提供一种不同~~也更复杂~~的思路：

**考虑贪心**

最大得分没什么好说了，排序后取前k个

有点难搞的是每天的题目数，我的方法是再掏一个数组代替原数组，排序啥的都用它，还得是结构体，因为要存位置，搞定最大得分后，标记每个前k大的数

接下来扫一遍原数组，对于每个含前k大数的区间，其必然能从那个前k大数处断开，分成两段，一段是从那数向前扩展的，一段是向后扩展的

于是两重循环

上代码：

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int kMaxN = 2001;

int n, a[kMaxN], an[kMaxN], ans, k, tot;
int c[kMaxN];

struct p
{
  int num, wei;
}b[kMaxN];

bool cmp(p o, p q) 
{
  return o.num < q.num;
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i].num = a[i];
    b[i].wei = i;
  }
  sort (b + 1, b + n + 1, cmp);
  for (int i = 0; i < k; i++) {
    ans += b[n - i].num;
    c[b[n - i].wei] = 1;
  }
  cout << ans << endl;
  for (int i = 1; i <= n; i++) {
    if (c[i] == 1) {
      tot++;
      an[tot] = 1;
      for (int j = i - 1; j >= 1; j--) {
        if (c[j]) {
          break;
        }
        an[tot] ++;
      }
      for (int j = i + 1; j <= n; j++) {
        if (c[j]) {
          break;
        }
        c[j] = 2;
        an[tot] ++;
      }
    }
  }
  for (int i = 1; i <= k; i++) {
    cout << an[i] << " ";
  }
  return 0;
}
```


---

## 作者：qhy_ (赞：0)

~~这是蒟蒻的第一篇题解~~~~

## 思路
1.首先大小排序

2.再按位置排序

3.输出最大值总和，输出位置差

------------
### 传送门：[CF1006B](https://codeforces.com/contest/1006/problem/B)

### 上代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k, nums;
int ans;
struct node {
  int num;
  int vol;
} a[2000];

bool cmp1(node x, node y) {
  return x.vol > y.vol;//大小排序
}

bool cmp2(node x, node y) {
  return x.num < y.num;//序号排序
}

int main() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i].vol;
    a[i].num = i + 1;
  }
  sort(a, a + n, cmp1);//大小排序
  sort(a, a + k, cmp2);//把前k大的数进行序号排序
  for (int i = 0; i < k; i++) {
    ans += a[i].vol;//算总值
  }
  cout << ans << endl;输出总值
  for (int i = 0; i < k - 1; i++) {
    nums += a[i].num - a[i - 1].num;//目前做题总数
    cout << a[i].num - a[i - 1].num << ' ';//输出位置差
  }
  cout << n - nums << endl;//剩下的全部做完
  return 0;
}
```


---

## 作者：intawl (赞：0)


题目描述：   
  
>给定长度为n的序列，要求分成k段，最大化每段最大值的和   
>$1 \le n, k, a_i \le 2000$  
  
思路：最大化每段最大值的和，那么可以先将整个序列排序，找出前 $k$ 大的数并做标记。 接着再将它变回原来的序列，将它分段。    
  
分段方法：   
  
从 1 开始寻找，如果找到一个是前 k 大的数，就将它断开，如果是最后一个数，便可以把后面的也分给这一段。   
  
时间复杂度 $O(nlogn)$。    
   
code:   
   
```
#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 5;

struct ints {
	int x, y;//该数字的值，编号
	bool f;//是否是前 k 大
} a[N];

int n, k;

inline bool cmp_1 (ints a, ints b) {//将数字的值从大到小排序
	return a.x > b.x;
}

inline bool cmp_2 (ints a, ints b) {//将位置从小到大排序
	return a.y < b.y;
}

signed main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) {
    	int c; cin >> c;
    	a[i] = {c, i, 0};//数值、位置、是否前 k 大的存储
	}
	sort (a + 1, a + 1 + n, cmp_1);//第一次排序
	
	int sum = 0;
	for (int i = 1; i <= k; i ++) a[i].f = 1, sum += a[i].x;//因为题目还要求和，故这里直接处理和
	cout << sum << endl;
	
	sort (a + 1, a + 1 + n, cmp_2);//排序方便分段
	int cnt = 0;
	for (int i = 1; i <= n; i ++) {
		++ cnt;
		if (a[i].f) {//若这个数是前 k 大的数
			-- k;//方便判断是否是最后一个
			if (k) cout << cnt << " ";//如果不是最后一个，则输出长度
			else cout << n - i + cnt;//否则输出剩下的长度，这里可以用 return cout << n - i + cnt, 0 代替
			cnt = 0; //因为这段已经归上一份了，所以长度清零
		}
	}
	return 0;
}

```

---

