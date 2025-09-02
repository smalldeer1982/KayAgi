# [ABC081C] Not so Diverse

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc081/tasks/arc086_a

高橋君は，$ N $ 個のボールを持っています． 最初，$ i $ 番目のボールには，整数 $ A_i $ が書かれています．

高橋君は，いくつかのボールに書かれている整数を書き換えて，$ N $ 個のボールに書かれている整数が $ K $ 種類以下になるようにしたいです．

高橋君は，少なくとも何個のボールの整数を書き換える必要があるでしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ \leq\ N $
- 与えられる数値はすべて整数

### Sample Explanation 1

例えば，$ 5 $ 番目のボールに書かれている整数を $ 2 $ に変更すると，ボールに書かれている整数は $ 1,\ 2 $ の $ 2 $ 種類となります． 一方，まったく書き換えを行わずに，ボールに書かれている整数の種類数を $ 2 $ 以下にすることはできないので，$ 1 $ を出力します．

### Sample Explanation 2

最初，ボールに書かれている整数の種類数は $ 2 $ なので，まったく書き換えを行う必要はありません．

## 样例 #1

### 输入

```
5 2
1 1 2 2 5```

### 输出

```
1```

## 样例 #2

### 输入

```
4 4
1 1 2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
10 3
5 1 3 2 4 1 1 2 3 4```

### 输出

```
3```

# 题解

## 作者：Fearliciz (赞：4)

题目大意：有 $N$ 个球，这 $N$ 个球上每个都有一个数字，现在需要更改一些球上的数字（可以重复）使得球上新的数字不同的个数不大于 $K$。

首先这里可以用一个桶来存储出现的次数。

```
for(int i=1;i<=N;i++){
	cin>>a[i];
	bucket[a[i]]++;
}
```

然后排一下序，最后统计要改的次数。

```
int ans=0;
for(int i=1;i<=N-K;i++)
	ans+=bucket[i];
cout<<ans;
```

这就构成了我们的完整代码。

```cpp
#include <bits/stdc++.h> //万能头 
using namespace std;

const int NR=2e5+10;
int bucket[NR],a[NR]; //bucket数组用来计数 

int main()
{
	int N,K;
	cin>>N>>K;
	for(int i=1;i<=N;i++){
		//在此处读入数字，计数。 
		cin>>a[i];
		bucket[a[i]]++;
	}
	
	sort(bucket+1,bucket+N+1); //使用sort快排（当然也可以手打）。 
	
	int ans=0;
	for(int i=1;i<=N-K;i++) //结束条件是N-K，因为只要超出K的部分就要更改。 
		ans+=bucket[i]; //因为前面排过序，所以就可以直接累加较小的次数。 
	cout<<ans;
	return 0; //好习惯。 
}
```

总结：
这道题其实就是在考察桶排序和快速排序。


---

## 作者：Cripple_Abyss (赞：3)

# [题目传送门](https://www.luogu.com.cn/problem/AT3719)

## 题目解法：

- 输入数据

- 把每个数字出现的次数统计一下，放进一个数组（桶）里

- 把这个数组从小到大进行排序

- 将该数组下表为 $1$ ~  $n$ - $k$ 的所有数出现的次数累加起来

- 输出累加和即可

## Code ：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,s[200005],ans;
int main() {
	cin>>n>>k;
	for (int i=1; i<=n; i++) {
		int x;
		cin>>x;
		s[x]++;
	}
	sort(s+1,s+n+1);
	for (int i=1; i<=n-k; i++)
		ans+=s[i];
	cout<<ans;
	return 0;
}

```

都看到这里了，点个赞呗QwQ

---

## 作者：lxgw (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/AT3719)
## 题意
有 n 个球，每个球上有一个序号 $x_i$，现在要在球上重写序号，要求重写后，球上的新序号不同的个数不能大于 k ，求最小的要重写的球的个数。
## 思路
把每个球上出现的序号的次数用一个数组 t 存起来，然后把它从小到大排一遍，因为最多写 k 个序号，又要求最小的改动，所以要把 $t_1$ 到 $t_{n-k}$ （出现次较为少的）加起来，把和输出就好了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,x,t[200010],ans;
void qs(int l,int r)//qs,quick sort的缩写，快速排序
{
//快排运用分治思想，以基准数为轴，将数组分段，轴左边都比轴小，轴右边都比轴大，
//再将其两段分别进行快排，直到分段后最左边的数的下角标等于或大于最右边的数的下角标时停止。
    int mid=t[(l+r)/2];//中间数（基准数）
    int i=l,j=r;
    while(i<j)
	{
        while(t[i]<mid) i++;//查找左半部分比基准数大的数
        while(t[j]>mid) j--;//查找右半部分比基准数小的数
        if(i<=j)swap(t[i],t[j]),i++,j--;//如果有一组数不满足从小到大的条件，就把它们交换
    }
    if(l<j) qs(l,j);//分治处理左部分
    if(i<r) qs(i,r);//分治处理右部分
}
int main() 
{
	cin>>n>>k;//输入
	for(int i=1;i<=n;i++)cin>>x,t[x]++;//不断输入x（即a[i]），并且用t数组存下每个序号的出现次数
	qs(1,n);//排序
	for(int i=1;i<=n-k;i++)ans+=t[i];//把t[1]到t[n-k]加起来
	cout<<ans;//输出答案
	return 0;
}

```

完结撒花~

谢谢 qwq

---

## 作者：chengni (赞：1)

用桶排记录每个数字，先判断是否已经符合，不符合则排一边顺序，用i和j记录两头，循环访问记录，刚好到k时输出。


```cpp
#include<bits/stdc++.h>

using namespace std;

int a[2000010];

int main(){
	int l=100000,r=0;
	int n,k;
	cin>>n>>k;
	int d;
	for(int i=1;i<=k;i++)
	{
		cin>>d;
		a[d]++;
		l=min(l,d);
		r=max(r,d);
	}
	if(r-i+1<=k) {
		cout<<0;
		return 0;
	}
	sort(a+l,a+r+1);
	int ans=0;
	while(r-l+1>k)
	{
		ans+=a[l];
		l++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：int32 (赞：0)

### 前言

> 咕一一，值一一。

### 题意

给定一个长度为 $n$ 的序列，要求修改一些数使得序列中只有 $k$ 种数字。求最少的修改数。

### 思路

既然要改动数最小，那么就要改**出现次数更少**的数字。

那么开一个桶 $bucket$，记录每个数字出现次数。将这个桶从小到大排序，$\sum_{i=1}^{n-k} bucket_i$ 就是答案。（提示：综合第一句话思考为什么）

时间复杂度 $\mathcal{O(n\log n)}$，瓶颈在于排序。

### Code

```cpp
/*
read(),write() 为快读快写。
fr(a,b,c,d) 表示 for(int a=b;a<=c;a+=d).
*/
fr(i,1,n,1) a[i]=read(),++b[a[i]];//记录出现次数
sort(a+1,a+n+1);//排序
fr(i,1,n-k,1) v+=b[i];//计算答案
write(v);
```

---

## 作者：Cocoly1990 (赞：0)

大概就是要改动一些数使得$N$个球上只有$k$种数。

很显然，我们要是改动次数尽可能少，那么就应该去**改动出现次数比较少的数**。

所以我们直接利用**桶**把每个数出现的次数记到数组$t$里，$sort$一波。

因为$sort$是从小到大，所以最后的答案应该是 $\sum\limits_{i=1}^{n-k} t_i$ 

解释一下为什么最后要加到$n-k$，因为不管怎么样最多有$n$种数，哪怕没有$n$种，后面加的都是$0$，不影响结果。

综合时间复杂度 $\mathcal{O}(nlogn)$ ，可以过。

---

## 作者：TLMPEX (赞：0)

这道题考察快速排序和桶。

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int vis[200010];
int main(){
	int n,m,i,k,z=0;
	cin>>n>>m;//输入
	for(i=1;i<=n;i++){
		cin>>k;//输入
		vis[k]++;//下标为k的数加一
	}
	sort(vis+1,vis+n+1);//快排
	for(i=1;i<=n-m;i++)//多了n-m个数
		z+=vis[i];
	cout<<z;//输出
}
```


---

## 作者：梦理乾坤 (赞：0)

首先输入, 然后用一个数据结构（桶）来记录每个输出现的次数, 然后排序, 然后$t$从$1$到$n - k$一个个枚举加到$ans$里去

最后输出

### 就这么简单

AC的代码

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 200010;

int t[N];

int main()
{
    int n, k;
    cin >> n >> k;  //输入n和k

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        t[x]++;  //用桶记录每个字符出现的次数
    }

    sort(t + 1, t + 1 + n);  //sort一下，找到最少出现的一些数字，方便后面改

    int ans = 0;
    for (int i = 1; i <= n - k; i++)
        ans += t[i];  //将最少出现的并且需要改的改掉，将次数加到答案里去

    cout << ans << endl;  //输出答案
    return 0;             //结束
}
```
希望管理员过
谢谢

---

## 作者：Snow_Dreams (赞：0)

这道题可以用一个cnt数组来存每个数字出现的个数

然后使用stl中的sort来排序cnt数组，将小的放前面

接着定义ans来统计现在有多少个cnt数组里不为0

最后直到
```cpp
ans==k，aum+=cnt[i]
```
（cnt[i]>0时才加）

最后输出sum，结束程序

---

## 作者：PC_DOS (赞：0)

由于要求改写次数尽可能少，因此要改写出现得最少的数字。因此本题可以借用桶排序的思想，记录每个数字出现的次数并按次数从大到小排序，之后对第K+1项到最后一项求和即为所要改写的最少次数。

代码:

```
#include <iostream>
#include <algorithm>
using namespace std; //头文件和命名空间
int arrCount[200005] = { 0 }; //定义存放每个数字出现次数的数组并初始化为0
bool cmp(int iNum1, int iNum2){ //降序排序判断函数
	return iNum1 > iNum2;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nCount, nDiff, i, iTemp, iSum=0; //nCount-球的个数；nDiff-不同的数的个数；i-循环计数器；iTemp-输入暂存；iSum-累加器
	cin >> nCount >> nDiff; //读入球的个数和不同的数的个数
	for (i = 1; i <= nCount; ++i){ //读入数字并计数
		cin >> iTemp; //读入数字
		++arrCount[iTemp]; //计数
	}
	sort(arrCount, arrCount + 200005,cmp); //降序排序(使用STL提供的快速排序函数)
	for (i = nDiff; arrCount[i] != 0; ++i){ //对第K+1项到最后一项求和，控制遇到值为0的项结束缩短时间
		iSum += arrCount[i]; //累加
	}
	cout << iSum << endl; //输出
	return 0; //结束
}
```

---

## 作者：Iron_Heart (赞：0)

## 思路

可以使用桶解决。

定义一个桶 `cnt`，每读入一个数 $x$ 就将 $cnt_x$ 加 $1$。

然后对这个桶排序。

“在 $N$ 个球上最多写入 $K$ 个不同的数”，也就是说 $1$ ~ $n$ 中有 $N - K$ 个数是不能被写入的。

由于题目要求最小的重写球数，因此 `cnt` 的前 $N - K$ 小的元素值即为答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int cnt[200100], n, k, ans;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        ++cnt[x];
    }
    sort(cnt + 1, cnt + n + 1);
    for (int i = 1; i <= (n - k); ++i) {
        ans += cnt[i];
    }
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：_Empty (赞：0)

根据题意
```java

有N个球，第I个球上写入整数Ai。

改变一些球的数字，以便在N个球上最多写入K个不同的数。

找到所需重写的最小球数。
```
我们只要先读入这些球，再桶，sort排序接着根据题意一波操作

```
#include<bits/stdc++.h>//懒人头文件不作解释
#define ll long long//个人喜好,使ll=long long
using namespace std;
ll a[999999],n,m,nn,mm;//long long开不开都一样，是可以过的(n个9我最爱
int main(){
   cin>>n>>m;//输入n,m
   for(int i=1;i<=n;++i)    cin>>mm,a[mm]++;//循环输入题目中的球
   sort(a+1,a+n+1);//sort排序找出最小的球
   for(int i=n;i>n-m;i--)   nn+=a[i];//这个用来统计最多数
   cout<<n-nn<<endl;//输出
   return 0;//许多人都丧失的习惯
}
```
虽然速度有点慢，但至少过了，最后温馨提示：
### 莫抄题解
求管理大大通过

---

## 作者：happybob (赞：0)

本题其实很简单，桶排序，主要因为Ai <= n（看题面后面），所以排序一下然后n - k慢慢加上去就OK了，我用的是stable_sort（稳定排序），比sort快了6ms（可能是评测机问题吧……复杂度一样的）

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int arr[200005];

int main()
{
    int n, k, sum = 0, y;
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
    {
        cin >> y;
        arr[y]++;
    }
    stable_sort(arr + 1, arr + n + 1);
    for(int i = 1; i <= n - k; i++)
    {
        sum += arr[i];
    }
    cout << sum << endl;
    return 0;
}
```


---

## 作者：不到前10不改名 (赞：0)

//先用桶记录再进行快排
```
#include<stdio.h>
#include<algorithm>
using namespace std;
int n,k,i,j,srx[200001],sry,t,p;
int main()
{
   scanf("%d%d",&n,&k);
   for(i=1;i<=n;++i)
   {scanf("%d",&t);
   srx[t]++;}//统计每个数字的出现次数
   sort(srx+1,srx+n+1);//因为这题保障srx[i]严格小于n，所以直接sort到n就可以了~
   for(i=n;i>n-k;--i)//i>n-k,一开始错在这了...
   sry+=srx[i];//最多数的个数
   printf("%d",n-sry);//这里要拿总数-多数的个数
   return 0;
}
```

---

