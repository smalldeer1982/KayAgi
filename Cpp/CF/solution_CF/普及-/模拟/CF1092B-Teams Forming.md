# Teams Forming

## 题目描述

There are $ n $ students in a university. The number of students is even. The $ i $ -th student has programming skill equal to $ a_i $ .

The coach wants to form $ \frac{n}{2} $ teams. Each team should consist of exactly two students, and each student should belong to exactly one team. Two students can form a team only if their skills are equal (otherwise they cannot understand each other and cannot form a team).

Students can solve problems to increase their skill. One solved problem increases the skill by one.

The coach wants to know the minimum total number of problems students should solve to form exactly $ \frac{n}{2} $ teams (i.e. each pair of students should form a team). Your task is to find this number.

## 说明/提示

In the first example the optimal teams will be: $ (3, 4) $ , $ (1, 6) $ and $ (2, 5) $ , where numbers in brackets are indices of students. Then, to form the first team the third student should solve $ 1 $ problem, to form the second team nobody needs to solve problems and to form the third team the second student should solve $ 4 $ problems so the answer is $ 1 + 4 = 5 $ .

In the second example the first student should solve $ 99 $ problems to form a team with the second one.

## 样例 #1

### 输入

```
6
5 10 2 3 14 5
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
1 100
```

### 输出

```
99
```

# 题解

## 作者：Trimsteanima (赞：2)

读懂题目后会发现很好贪心
所以就直接上代码吧
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, i, ans, a[1000];
int main() {
	cin >> n;
	for (i = 0; i < n; i++) cin >> a[i];
	sort(a, a + n);
	for (i = 0; i < n; i += 2)
		ans += a[i + 1] - a[i];
	cout << ans;
	return 0;
}
```

---

## 作者：Mikemao666 (赞：1)

题目传送门:[Here](https://www.luogu.com.cn/problem/CF1092B)

这道题看描述时一脸懵逼：分组？刷题？什么鬼。。。

但如果你**静下心来，冷静思考**，就会发现：**这道题是一道大水题！**
 
### 题面
题目说有$n$个人，分为$\frac{n}{2}$ 个$team$，使得每个$team$中两个人的能力相同

Q：怎么提升能力呢?

~~教练~~A：刷题啊

...

**正题**

题目要求每个$team$中的$a_2-a_1$最小所以我们就可以想到：STL中的$sort$!

把学生的能力值从小到大排序，然后从1开始循环，每次循环把$ans$累加$a_2-a_1$，最后输出$ans$,就$perfect$了！

 _— 什么？怎么简单_ 
 _— 真的..._

### **code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int team[101],n,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>team[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n-1;i+=2)ans+=(team[i+1]-team[i]);
   //for(int i=2;i<=n;i+=2)ans+=(team[i]-team[i-1]);is also ok
   cout<<ans;
	return 0;
}
```
完结撒世纪末彼岸花❀~

 

---

## 作者：YYen (赞：0)

### 思路：贪心
假设四个数 $ a < b < c < d $ ，那么 $ (d - c) + (b - a) $ 必然小于 $ (d - a) + (c - b) $ 。也就是，在贪心角度的，一定是能力相近的两名学生进行配对分组就能达到最优。因此最终做法就是， $ n $ 个学生按照能力值排序，之后两两相邻为一组，计算能力值的差就是答案。
### 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int a[105];

int main()
{
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i += 2) ans += a[i + 1] - a[i];
    cout << ans << endl;
    return 0;
}
```



---

## 作者：Mr_Avalan (赞：0)

### 题目大意

有 $n$ 个学生，第 $i$ 个学生的能力值为 $a_i$($1<=i<=n$)，每次可以把任意一个学生的能力值加 $1$，求最少需要操作多少次才能使每个人都可以有找到和自己能力值相同的人。

### 分析

因为是求最小值，所以用贪心求解。首先将他们排好序，其实他们和谁分成一组就已经清楚了，第 $2*i$ 个人要和第 $2*i-1$ 个人组队($1<=i$<=n/2)，想清楚以后代码就很好实现了。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101],ans=0;
int n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//输入
	}
	sort(a+1,a+n+1);//STL快排
	for(int i=1;i<=n;i+=2)//因为在考虑i的时候i+1就已经考虑了
	{//所以每次加2
		ans+=a[i+1]-a[i];//要加的值就是a[i+1]和a[i]的差
	}
	cout<<ans;//输出
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个学生，每个学生有一个能力值 $a_i$。现在想把学生两两分成一组，但是不能让每个组里面的学生能力值不相同，因此可以通过刷题来提升自己的能力值，每次解出一道题，能力值加 $1$，求问这些学生总共应该刷多少道题目才能够全部都能两两分成一组？

**数据范围：$2\leqslant n\leqslant 100,1\leqslant a_i\leqslant 100$，保证 $n$ 是偶数。**
## Solution
我们直接从小到大排序，这样可以保证两两一组之间的差是最小的，所以每两个组一组，然后求出他们之间的差值，就可以保证能力值相差最小，即需要解出的题目数量最小。
## Code
```cpp
int n, a[107], ans;

int main() {
	getint(n);
	_for(i, 1, n)	getint(a[i]);
	sort(a + 1, a + n + 1);
	_spfor(i, 1, n, 2)
		ans += (a[i + 1] - a[i]);
	writeint(ans);
	return 0;
}
```

---

## 作者：WKAHPM (赞：0)

这题的基本思想就是贪心吧

题目就是让你两两分组，使得每组能力值的差值最小

设$a_{1},a_{2},···,a_{n}$表示每个学生的能力值

且满足：$a_{1} \le a_{2} \le ··· \le a_{n}$

则对于任意一个能力值$a_{i}$，它的最优匹配为$a_{i+1}$（$i$为奇数）

考虑到$a_{1}$，我们不取$a_{i-1}$（你想想$a_{1-1}$是什么）

假设存在一个能力值$a_{k}$ ($k> i+1$)，使得$a_{k}-a_{i}< a_{i+1}-a_{i}$

即: $a_{k}<a_{i+1}$

∵ $a_{i+1}<a_{k}$

∴ 不存在这样的$k$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[110],ans; 
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);//要先排序
	for(int i=1;i<=n;i+=2) //i要为奇数
	{    
		ans+=a[i+1]-a[i];//答案加上两个能力值的差
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Zechariah (赞：0)

排序贪心，因为对于a>b>c>d,a-d+b-c>a-b+c-d,所以ab cd分组比ad bc分组要更优
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 3e4 + 10, mod = 998244353;
using namespace std;
namespace fast_IO {
    long long read()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int a[N];

int main()
{
    rg int n = fast_IO::read(), ans = 0;
    for (rg int i = 1; i <= n; ++i)a[i] = fast_IO::read();
    sort(a + 1, a + n + 1);
    for (rg int i = n; i >= 2; i -= 2)ans += a[i] - a[i - 1];
    fast_IO::write(ans);
    return 0;
}


```

---

## 作者：Ouaoan (赞：0)


贪心就好了，把长度最相近的两根配对一定是最优的。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define read(x) scanf("%d",&x)
#define maxn 100

int n;
int a[maxn+5];

int main() {
	read(n);
	for(int i=1;i<=n;i++) {
		read(a[i]);
	}
	
	sort(a+1,a+n+1);
	
	int ans=0;
	for(int i=1;i<=n;i+=2) {
		if(a[i]!=a[i+1]) {
			ans+=a[i+1]-a[i];
		}
	}
	
	printf("%d",ans);
	
	return 0;
}
```

---

