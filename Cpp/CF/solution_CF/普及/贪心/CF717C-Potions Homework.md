# Potions Homework

## 题目描述

Harry Water, Ronaldo, Her-my-oh-knee and their friends have started a new school year at their MDCS School of Speechcraft and Misery. At the time, they are very happy to have seen each other after a long time. The sun is shining, birds are singing, flowers are blooming, and their Potions class teacher, professor Snipe is sulky as usual. Due to his angst fueled by disappointment in his own life, he has given them a lot of homework in Potions class.

Each of the $ n $ students has been assigned a single task. Some students do certain tasks faster than others. Thus, they want to redistribute the tasks so that each student still does exactly one task, and that all tasks are finished. Each student has their own laziness level, and each task has its own difficulty level. Professor Snipe is trying hard to improve their work ethics, so each student’s laziness level is equal to their task’s difficulty level. Both sets of values are given by the sequence $ a $ , where $ a_{i} $ represents both the laziness level of the $ i $ -th student and the difficulty of his task.

The time a student needs to finish a task is equal to the product of their laziness level and the task’s difficulty. They are wondering, what is the minimum possible total time they must spend to finish all tasks if they distribute them in the optimal way. Each person should receive one task and each task should be given to one person. Print the answer modulo $ 10007 $ .

## 说明/提示

In the first sample, if the students switch their tasks, they will be able to finish them in $ 3+3=6 $ time units.

## 样例 #1

### 输入

```
2
1
3
```

### 输出

```
6
```

# 题解

## 作者：bigclever (赞：4)

## 思路：
因为是要使得任两个数的乘积的和最小，那么肯定是要让**越大的数乘上越小的数**，所以我们将数组 $a$ 排好序之后，让第 $i$ 个数乘第 $n-i+1$ 个数（也就是从后往前数的第 $i$ 个数）就行了。

注意每次运算都要**取模**，防止溢出。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],ans;//取了模就不用开long long啦
const int mod=10007;
int main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)ans=(ans+(a[i]%mod)*(a[n-i+1]%mod))%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：Zq_water (赞：4)

思路很简单，排好序后分别从两边枚举。因为要想使总和最小，最好是，最大数乘上最小数。

```cpp
#include <cstdio>
#include <algorithm>
#define MOD 10007
using namespace std;
long long n,a[100005],ans;
int main(){
    scanf("%d",&n);
    for(long long i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(long long i=1,j=n;i<=n;i++,j--) ans=(ans+(a[i]*a[j])%MOD)%MOD;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Steve_xh (赞：2)

# 题面

[题目传送门](https://www.luogu.com.cn/problem/CF717C)

**题目大意：**

给定一段序列 $a$ 和它的长度 $n$，并使另一个序列 $b$ 使其为 $a$ 打乱后的结果，求最小的 $v=(\sum\limits_{i=1}^{n}a_ib_i)\bmod 10007$。

# 思路

要求乘积最小，那肯定得是每次最大数乘最小数啦，证明也很简单，两个相差远的数的乘积总是比两个相差近的数的乘积小，所以把 $a$ 从大到小排序，每次将两个相差最远的数相乘，不断累加（这两步每一步都要 $\bmod 10007$），最后就能求出最小的 $v$ 啦。

等等，你说 $a$ 一开始不一定是有序的？那可不用管。因为排序后的 $a_i$ 与现在的 $a_i$ 的位置都是有联系的，例如我把原本 $a_3$ 的位置移到了 $a_5$，那么其他的数也是这样的，也就是说按照 $a$ 排序前后的位置关系，$a_ib_i$ 的相对应位置也是同样规律变化的，所以根本不用管位置问题。

# 代码

```cpp
#include<bits/stdc++.h>
#define MOD 10007
#define int long long//十年OI一场空，不开long long见祖宗！
using namespace std;
int n,a[100005],ans=0;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);//排序
    for(int i=1,j=n;i<=n;i++,j--)//从两个最远的地方开始步步逼近
        ans=(ans+(a[i]*a[j])%MOD)%MOD;//每一步都要模MOD，不然可能会溢出
    cout<<ans;
    return 0;
}
```

---

## 作者：Bpds1110 (赞：2)

[**原题传送门**](https://www.luogu.com.cn/problem/CF717C)
# 题面：
给定 $N$ 个数，要求你将这 $N$ 个数重新排列，并算出相应的乘积，要求乘积的和最小。
# Solution:
首先，用暴力枚举一定会超时。我们不妨想一想一种新的贪心思路，**如果将大数和大数相乘，所得的结果会非常大；但如果将大数与小数相乘，结果就会相对更小**。所以，我们要**避免两个大数**相乘。假设有两个数 $x$ 和 $y$，令 $y$ 比 $x$ 小 $4$，那么根据题意一共有两种答案，第一种是 $x^2+y^2=x^2+(x-4)^2=2x^2-16$，第二种是 $2xy=2x(x-4)=2x^2-8x$，又因 $x$ 至少为 $4$，得出 $2x^2-8x≤2x^2-16$。第二种贪心策略得出的答案明显比第一种小。再举个例子，假设输入以下样例。
```
2
1 3
```
这有两种可能，分别为 $1$ 乘 $3$ 加 $3$ 乘 $1$，或 $1$ 乘 $1$ 加 $3$ 乘 $3$。第一种答案为 $6$，而第二种答案为 $10$。显然，第一种利用**大数与小数相乘**得到的结果为最优。
# Code:
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=10007;
const int N=1e5+1;
ll n,i,ans,a[N];
int main()
{
	cin>>n;
	for(i=1;i<=n;++i) 
		cin>>a[i];
	sort(a+1,a+1+n);//贪心，先排序 
	for(i=1;i<=n;++i)
		ans=(ans+a[i]*a[n-i+1])%mod;//累加乘积并取模 
	cout<<ans;
	return 0;
}

```


---

## 作者：lmndiscyhyzdxss (赞：1)

### 题目大意
一个长度为 $ n $ 的数组 $ a $ ，重新排列后得到 $ b $ 数组，问 $ a_i \times b_i $ 的和的最小值为几。
### 题目分析
我们肯定不可能让两个大的相乘，只有让最大的乘最小的才能取到最小值，也就是 $ a_i \times a_{n-i}+1 $。       
为了不让结果过大，需要每加一次就用结果 $ \bmod 10007 $ 即可，记得开 long long。
### AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[100010],n,ans=0;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) ans=(ans+a[i]*a[n-i+1])%10007;
    cout<<ans;
    return 0;
}
```


---

## 作者：xzggzh1 (赞：1)

题意：

每个人有一个懒惰值，每个任务有个难度，一开始每个人的任务的难度和懒惰值都为 $a_i$，完成任务时间是懒惰值乘以难度，现在重新分配任务，问花费的时间最小是多少。结果模 $10007$ 。


---

就是让懒的人完成简单点任务。

证明如下：

对于两个人的懒惰程度和对应任务的难度 $x_1,x_2,y_1,y_2$ ，令

$$x_1 \leq x_2,y_1 \leq y_2$$


有：

$$x_1 * y_1+x_2*y_2 \leq x_1*y_2+x_2*y_1$$

移项相消即可看出。

---

记得开`long long`。

代码：

```cpp
#include <bits/stdc++.h> 
inline int R()
{
    char c;int res,sign=1;
    while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
    while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
    return res*sign;
}
using namespace std;
int a[100001];
signed main(){
    int n,ans=0;
    n=R();
    for(int i=1;i<=n;++i) a[i]=R();
    sort(a+1,a+1+n);
    for(int i=1;i<=n;++i) ans=(ans+a[i]*a[n-i+1]%10007)%10007;
    printf("%d",ans);
}
```

---

## 作者：yghjsk (赞：0)

# 题意：
给我们 $n$ 个数，我们要把这些数排列，求出前后相应的乘积，但加起来的和必须是所有方案中最小的，并且把结果对 $10007$ 取余后输出。
# 思路：
因为题目是求乘起来的和最小值，所以我们就要尽量避免大的数与大的数相乘，要用大数去配小数相乘。这道题就不难了。那么只要先把原来的数组从小到大排序之后，然后头尾递增相乘在得出相加的和就行了（记住，要边加边取余，否则会爆数据）！
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1,j=n;i<=n;i++,j--)ans=(ans+(a[i]*a[j])%10007)%10007;
    cout<<ans;
    return 0;
}
```


---

## 作者：The_FAKIR (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF717C)

## 题目大意

有一长度为 $n$ 的数组 $a_i$，求其重排后的数组 $b_i$，使 $v=\sum\limits_{i=1}^na_ib_i$ 最小，输出 $v \bmod 10007$ 的结果。


------------

## 分析
因为题目是求最小值，所以我们就要尽量避免大的数与大的数相乘。
这里给大家举个~~栗~~例子，假设总共 $a$ 数组只有有两个数 $3$ 和 $4$，那么总共有两种配对方法：$3$ 乘 $3$ 加 $4$ 乘 $4$ 和 $3$ 乘 $4$ 加 $4$ 乘 $3$，通过计算得出第一种方法的值为 $25$，而第二种方法的值为 $24$，很明显第二种方法更小。

所以我们可以得出结论：**要用大数去配小数，尽量避免大的数与大的数相乘。**

知道了这个结论，这道题就不难了。那么只要先把原先的数组 $a$ 从小到大排序一下，然后再倒序与原数组相乘就好啦！


------------

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,k;
int a[100010];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    k=n;
    for(int i=1;i<=n;i++){
        ans+=a[i]*a[k];
        k--;
    }
    cout<<ans;
    return 0;
} 
```


---

## 作者：liukangyi (赞：0)

# 题目大意
给你一个长度为 $n$ 的数列 $a$，让你将 $a$ 数组重新打乱后，使得 $\sum_{i=1}^na_ib_i$ 最小（$b$ 数组为打乱后的数组），并请你输出总和。


------------
# 分析
这道题让我们求最小值，那么假设现在有数 $a$ 与数 $b$，且 $a$  小于 $b$，如果我们用 $b$ 去乘 $b$，$a$ 去乘 $a$ 的话，那么值肯定会比用 $a$ 乘 $b$ 与 $b$ 乘 $a$ 大。所以，我们求最小值应用**最大的对应最小的，第二大的对应第二小的，第三大的对应第三小的，以此类推**。


------------
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int a[100010],b[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(a+1,a+1+n);
	sort(b+1,b+1+n,greater<int>());
	for(int i=1;i<=n;i++)
		ans+=a[i]*b[i];
	cout<<ans;
	return 0;
} 
```





---

## 作者：JAMES__KING (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF717C)

拿到题，先用小数据模拟一下。

$2$

$x$ $y$

$x$ 比 $y$ 大，它们的差值为 $z$。

第一种方法 : $ x ^ 2 + y ^ 2 = x ^ 2 + ( x - z ) ^2 = 2 x ^ 2 - 2 x z + z ^ 2$

第二种方法 : $ 2 x y = 2 x ( x - z ) = 2 x ^ 2 - 2 x z$

由于 $ z \ge 0$，

所以 $ z ^ 2 \ge 0$，

那么 $ 2 x ^ 2 - 2 x z \le 2 x ^ 2 - 2 x z + z ^ 2$，

第二种贪心策略显然比第一种贪心策略更优。

再结合题目进行分析：

因为题目是求乘起来的和的最小值，所以我们就要尽量避免大的数与大的数相乘，那么便要用大数去配小数相乘。只要先把原来的数组从小到大排序之后，然后头尾递增相乘在得出相加的和就行了！

注释代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,a[100005];
int main()
{
   cin>>n;
   for(int i=1;i<=n;i++) cin>>a[i];
   sort(a+1,a+1+n);//排序，让大的和小的配在一起
   for(int i=1;i<=n;i++) sum=(sum+a[i]*a[n-i+1])%10007;//边循环边计算，注意取余。
   cout<<sum;
   return 0;
}
```


---

