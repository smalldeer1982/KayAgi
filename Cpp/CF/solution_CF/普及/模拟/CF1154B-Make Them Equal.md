# Make Them Equal

## 题目描述

You are given a sequence $ a_1, a_2, \dots, a_n $ consisting of $ n $ integers.

You can choose any non-negative integer $ D $ (i.e. $ D \ge 0 $ ), and for each $ a_i $ you can:

- add $ D $ (only once), i. e. perform $ a_i := a_i + D $ , or
- subtract $ D $ (only once), i. e. perform $ a_i := a_i - D $ , or
- leave the value of $ a_i $ unchanged.

It is possible that after an operation the value $ a_i $ becomes negative.

Your goal is to choose such minimum non-negative integer $ D $ and perform changes in such a way, that all $ a_i $ are equal (i.e. $ a_1=a_2=\dots=a_n $ ).

Print the required $ D $ or, if it is impossible to choose such value $ D $ , print -1.

For example, for array $ [2, 8] $ the value $ D=3 $ is minimum possible because you can obtain the array $ [5, 5] $ if you will add $ D $ to $ 2 $ and subtract $ D $ from $ 8 $ . And for array $ [1, 4, 7, 7] $ the value $ D=3 $ is also minimum possible. You can add it to $ 1 $ and subtract it from $ 7 $ and obtain the array $ [4, 4, 4, 4] $ .

## 样例 #1

### 输入

```
6
1 4 4 7 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
2 2 5 2 5
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4
1 3 3 7
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
2
2 8
```

### 输出

```
3
```

# 题解

## 作者：sunson (赞：3)

本题是一道不错的模拟题，有不少坑
思路如下
1. 如果超过3个数，直接输出-1

2. 如果一共有1个数，输出0

3. 如果2个，差为偶数，输出差的一半，否则输出差

4. 如果3个，max与min差为偶数，差的一半等于中间值，输出max-中间值。否则输出-1

这里用了map判重，用priority_queue记录min,max

~~stl大法好~~

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<int>q;
map<int,int>mp;
int mian(){
	int n;cin>>n;
	for(int i=1;i<=n;i++){
		int t;cin>>t;
		if(!mp.count(t)){
			mp[t]++;
			if(mp.size()>3){
				cout<<-1<<endl;
				return 0;
			}
			else q.push(t);
		}
	}
	switch(q.size()){
		case 1:{
			cout<<0<<endl;
			break;
		}
		case 2:{
			int a=q.top();q.pop();
			int b=q.top();
			if((a-b)%2==0)cout<<(a-b)/2<<endl;
			else cout<<a-b<<endl;
			break;
		}
		case 3:{
			int a=q.top();q.pop();
			int c=q.top();q.pop();
			int b=q.top();
			if((a-b)%2==0&&a-(a-b)/2==c)cout<<(a-b)/2<<endl;
			else cout<<-1<<endl;
			break;
		}
	}
	return 0;
}
```

---

## 作者：Sun_wtup (赞：2)

# CF1154B Make Them Equal 题解
[题目传送](https://www.luogu.com.cn/problem/CF1154B)
## 题意
给出一个长度为 $n$ 的序列，要将序列中的数通过加或减（也可以不变）一个固定的数 $D$，使这个序列中的数全部相等，并使 $D$ 最小。
## 思路与分析
这是一道数学题，其实也不算，因为数据很小，可以直接枚举 $D$。对于每一个 $D$，为了让每个数相等，有下面几种方案：
  - 将最大值减 $D$，将最小值加 $D$，其他不变。
  - 将最大值减 $D$，其他的不变。
  - 将最小值加 $D$，其他的不变。
  - 都不变。
  
总结一下，对于每个最大值，如果剩下的每个数加 $D$ 或加 $2\times D$ 或不动都能变成最大值，就说明这个 $D$ 是合法的，输出即可。
## 实现
双层循环枚举，外层枚举 $D$，内层枚举 $n$，详见代码。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<'='<<x<<std::endl
#define int long long
int n;
int a[100005];
int maxn = -0x7fffffff;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (register int i = 1; i <= n; i++) {
		cin >> a[i];
		maxn = max (a[i], maxn);//找最大值
	}
	for (register int i = 0; i <= 200; i++) {
		bool flag = 0;
		for (register int j = 1; j <= n; j++) {
			if (a[j] + i != maxn and a[j] + i + i != maxn and a[j] != maxn) {//判断
				flag = 1;
				break;
			}
		}	
		if (!flag) {
			cout << i;
			return 0;//其实可以更简洁
		}
	}
	cout << -1;
	return 0;
}
```
本蒟蒻水平有限，如有不周之处，请见谅。


---

## 作者：一扶苏一 (赞：2)

[本场题解博客](https://www.cnblogs.com/yifusuyi/p/10727303.html)

# B

## Description

给定一个长度为 $n$ 的序列，请你选择一个非负整数 $D$，然后将序列中的所有元素要么加上 $D$，要么减去 $D$，要么不做改变，使得修改后的序列所有元素都相等。最小化 $D$

## Limitation

$1~\leq~n~\leq~100,~\forall~i~\in~[1,n],~1~\leq~a_i~\leq~100$

## Solution

考虑一个显然的事实是 $0~\leq~D~\leq~100$

证明上考虑如果 $D~>~100$，由于 $a_i~\leq~100$，则所有的 $a_i$ 都不可能减掉 $D$。同时如果存在一个 $a_j$ 使得 $a_j$ 的操作是加上 $D$ 的话，那么其他所有 $a$ 的操作都一定是加上 $D$。因为他们初始都小于 $100$，但是 $a_j$ 操作后的值大于 $100$，所以必须都加上 $D$。由此导出所有的 $a$ 都相同，那么 $D = 0$ 显然优于 $D~>~100$。另外如果没有任何一个 $a_i$ 的操作是加上 $D$ 的话，那么 $D = 0$ 显然仍然是最优的。

于是我们考虑枚举 $D$。考虑第一个位置只有 $a_1 - D,~a_1,~a_1 + D$ 三种可能，将这种情况分别向后枚举看是否合法即可。

## Code

```cpp
const int maxn = 109;

int n;
int MU[maxn];

void check(int x, int k);

int main() {
  freopen("1.in", "r", stdin);
  qr(n);
  for (int i = 1; i <= n; ++i) qr(MU[i]);
  int ans = 0;
  while (ans <= 100) {
    check(MU[1], ans);
    check(MU[1] - ans, ans);
    check(MU[1] + ans, ans);
    ++ans;
  }
  puts("-1");
  return 0;
}

void check(int x, int k) {
  if (x < 0) return;
  for (int i = 1; i <= n; ++i) {
    if ((MU[i] != x) && (abs(MU[i] - x) != k)) return;
  }
  qw(k, '\n', true);
  exit(0);
}
```

---

## 作者：Nuclear_Fish_cyq (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1154B)

[CF 原题传送门](https://codeforces.com/problemset/problem/1154/B)

[提交记录](https://www.luogu.com.cn/record/127154835)

## 题目大意

有一个长度为 $n$ 的序列，对于每一个数，你可以把它进行下列操作中的一种一次：

- 加上 $D$

- 减去 $D$

- 不进行操作

给定这个序列，求出是否存在非负整数 $D$，使得存在一种操作方案使得操作后这个序列里的数全部相等。如果存在 $D$，输出 $D$ 的最小值。否则，输出 `-1`。

## 做法

首先我们可以注意到的一个点是把这个序列去重对于答案是没有影响的。如果 $D$ 不存在，那么去重后的序列肯定也不存在满足条件的 $D$。如果 $D$ 存在 且 $D\ne0$，那么由于任何值相同的数进行的操作也相同那么去重后的序列的 $D$ 也不会变。如果 $D=0$，那么很显然这个序列的全部数初始就相同，因为操作无法改变任何数。那么，去重之后也是只剩一个数，不会影响结果。

有了这些，我们就可以愉快地去重再处理序列了。接下来我们分去重后的序列数的个数来进行分类讨论。

### 当去重后的数个数大于三时：

那么由于操作只有三种，很显然是无解的。

### 当去重后的数个数等于三时：

我们设这三个数从小到大分别为 $a_1,a_2,a_3$。

那么，显然的，如果 $D$ 存在，那么肯定 $a_1$ 进行的操作是加上 $D$，$a_2$ 不变，$a_3$ 进行的操作是减去 $D$。那么，只有 $a_2 - a_1 = a_3 - a_2$ 时 $D$ 存在，且 $D = a_2 - a_1$。当然，如果你想写 $a_1 + a_3 = 2a_2$ 的话也无所谓，只要等价就好。

### 当去重后的数个数等于二时：

$D$ 一定存在。如果去重后的两个数之差是偶数，那么我们就可以让这两个数小的加 $D$，大的减 $D$，$D$ 就是两个数之差的一半，这样子得到的 $D$ 一定是最小的。如果这两个数之差是奇数，那么我们可以让它们大的不变，小的加 $D$，这样子 $D$ 就是这两个数之差，可以证明这个 $D$ 是唯一的。

### 当去重后的数个数等于一时：

对于任意非负整数 $D$，都满足要求。那么不如直接让 $D=0$，一定最小。

上代码。码风可能比较奇怪，请不要太在意。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, a[100];

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(a, a + n);
	n = unique(a, a + n) - a;//STL去重
	if(n > 3){
		cout << -1 << endl;
	}
	else if(n == 3){
		if(a[0] + a[2] == a[1] * 2){
			cout << a[1] - a[0] << endl;
		}
		else{
			cout << -1 << endl;
		}
	}
	else if(n == 2){
		if((a[1] - a[0]) % 2){
			cout << a[1] - a[0] << endl;
		}
		else{
			cout << (a[1] - a[0]) / 2 << endl;
		}
	}
	else{
		cout << 0 << endl;
	}
	return 0;
}

```


---

## 作者：b6e0_ (赞：1)

[CF题面传送门](https://codeforces.com/problemset/problem/1154/B) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1154B) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1154B)

发现题解里大多数是根据不同数的个数分类讨论的，这里发一个暴力做法的题解。

可以发现，最终的答案一定小于 $200$（懒得想，其实是 $100$）。我们用一维枚举答案。记枚举到的答案为 $i$，如果可行，那么把所有数最后变成的同一个数的一个可能是 $\max\{a_i\}-i$。再扫描每个数判断即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int main()
{
	int n,i,j,maxv=0;
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i],maxv=max(maxv,a[i]);
	for(i=0;i<200;i++)
	{
		for(j=1;j<=n;j++)
			if(!(a[j]==maxv-i||a[j]+i==maxv-i||a[j]-i==maxv-i))
				break;
		if(j>n)
		{
			cout<<i;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```
时间复杂度为 $\mathcal O(n^2)$。

---

## 作者：Harrylzh (赞：0)

考虑分不同情况进行相应的解决：
- 根据题意，如果可行，最多只有三种不同的值，所以超过三种直接输出 `-1 `。
- 如果刚好有三种不同的值，最大值减 $d$ 和最小值加 $d$ 一定等于中间值才可行，如果可行输出中间值减去最小值，不可行则输出 `-1`。
- 如果刚好有两种不同的值，使最大值减 $d$ 等于最小值即可，但如果最大值与最小值的差为偶数，可以使最小值加上 $d$ 等于最大值减去 $d$，$d$ 相比上一种更少。
- 如果所有值都相同，直接输出 `0`。

在处理上可以先把数组去重，可以同时得到不同值的个数以及升序的所有不同值。

代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int l[100+5];
int a[100+5],t=0;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>l[i];
    //去重
    sort(l+1,l+n+1);
    a[++t]=l[1];
    for(int i=2;i<=n;i++)
    {
        if(l[i]!=l[i-1])
        {
            a[++t]=l[i];
        }
    }
    //分情况讨论
    if(t==1) cout<<0<<endl;
    else if(t==2)
    {
        if((a[2]-a[1])%2==0) cout<<(a[2]-a[1])/2<<endl;
        else cout<<(a[2]-a[1])<<endl;
    }
    else if(t==3)
    {
        if(a[3]-a[2]==a[2]-a[1]) cout<<a[2]-a[1]<<endl;
        else cout<<-1<<endl;
    }
    else
    {
        cout<<-1<<endl;
    }
    return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：0)

### 思路
如果数字种类 $>3$ 的话，那么无论如何都无法使得所有数相等。举个例子：如果有 $1,2,3,4$，不存在 $d$ 可以让所有数相等的。这一点很容易就能想到。因为一个数只有三种选择，对于严格最大值来说，应该减到这个数列的中间值，而对于严格最小值来说，加到中间值。并且与中间值相差的量是相等的。如果只有两种数，大的数减去两数之和的一半，而小的数加上原来的和的一半。一种数就固定为 $0$ 啦。
### 代码
经过上文一通分析后，代码就很容易了。
```cpp
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define dy; ios::sync_with_stdio(false),cin.tie(),cout.tie();
#define int long long
#define re register
#define For(i,l,r) for(re int i=l;i<=r;i++)
const int N=1e3+5;
inline void read(int &x){
	   x=0;int f=1;
	   char c=getchar();
	   while(!isdigit(c)){
			if(c=='-') f=-1;
			c=getchar();
	   }while(isdigit(c)){
			x=x*10+c-'0';
			c=getchar();
	   }x*=f;
}
inline void write(int x){
	   if(x<0){x=-x;putchar('-');}
	   if(x>9) write(x/10);
	   putchar(x%10+'0');
}int n,x[N],Maxn=-1,Minn=1e9,mid;
set<int> k;
signed main(){
	dy;cin>>n;
	For(i,1,n){
		cin>>x[i];
		Maxn=max(Maxn,x[i]);
		Minn=min(Minn,x[i]);
		k.insert(x[i]);
	}
	if(k.size()>3){
		cout<<-1;
		return 0;
	}else if(k.size()==1){
		cout<<0;
	}else if(k.size()==2){
		int c=(Maxn-Minn)/2;
		if(Minn+c==Maxn-c) cout<<c;
		else cout<<Maxn-Minn;
	}else{
		For(i,1,n) if(x[i]!=Maxn&&x[i]!=Minn){mid=x[i];break;}
		if(Maxn-mid==mid-Minn) cout<<Maxn-mid;
		else cout<<-1;
	}
	return 0;
}
```

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

（本题中 $d$ 是公差的意思，$a_{i}$ 是数组元素的意思）

数列题。

对于唯一 A 掉的紫题是数列题的我来说，这题的思路很好找。

很显然，先将此数列去重，排序，然后看它的长度。

由于数据范围很小，所以开布尔数组去重以减小码量。

当只剩下一个数时，很明显所有其他数都相同（或本来只有这一个数）。

存储公差为 $0$。

当剩下两个数时，如果 $d$ 为偶数，那么可以将原数组插入一个数，大小为 $a_{0}$ $+$ $\frac{d}{2}$。

于是到了三个数的情况。三个数时，根据等差中项可知：

$$2 \times a_{1}=a_{0}+a_{2}$$

只有在此情况时，才能得到答案为 $d$。

不满足的都无解。

易证，将原长度为二的数组扩项后的数组都满足条件，公差为 $\frac{d}{2}$。

但是，公差只能为整数，所以原公差为奇数的长度为二的数列不满足条件。

所以需要特判。

另外，由于只能操作一次，所以长度大于三的数列都无解。

代码如下。

```cpp
#include<iostream>
using namespace std;
bool l[150];
int q[3]={0,0,0};
int main(){
	int n,t,s=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&t);
		l[t]=1;
	}
	for(int i=0;i<=100;i++){
		if(l[i]&&s<3){
			q[s]=i;
			s++;
		}else if(l[i]&&s==3){
			printf("-1");
			return 0;
		}
	}
	t=q[2]-q[1];//没什么用的省空间算法
	s=q[1]-q[0];//同上
	if(q[1]==0){
		n=0;
	}else if(q[2]==0){
		n=(s%2?s:s/2);
	}else{
		n=(t==s?s:-1);
	}
	printf("%d",n);	
    return 0;
}
```




---

## 作者：kaceqwq (赞：0)

# 题目大意：
给定一个长度为 $n$ 的序列，问能否将序列中的所有数要么加上 $D$，要么减去 $D$，要么不做改变，使得修改后的序列所有元素都相等。求出最小的 $D$。若无解，输出 -1。

# 分析：
我们观察题面发现，数据范围十分的小。所以我们直接暴力枚举 $D$ 即可，由题意可知，要求平均值，一个数要不然就是可以被序列最大数减 $D$ 或减 $2D$ 得到，要不然它自己就是最大数，但是如果都不满足，说明现在的 $D$ 是不可行的。所以对于序列中的每一个数，判断它能否由序列最大数与枚举的 $D$ 运算得到，如果不能，就枚举下一个 $D$。如果整个序列都能被得到，那么就说明找到了最小的 $D$， 直接输出即可。但是如果枚举完了也没有找到，说明无解，就输出 -1。

# Code：
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int n, a[1000005], zd = -2147483647;
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		zd = max (zd, a[i]);  // 找出序列中的最大数
	}
	int j;
	for (int i = 0; i < 200; i++) {  //数据很小，直接枚举 D
		for (j = 1; j <= n; j++) if (a[j] != zd - i && a[j] + i != zd - i && a[j] - i != zd - i) break;  
        //如果都不能得到，就枚举下一个 D
		if (j > n) {  //如果全部数都满足，直接输出现在枚举的 D
			cout << i << '\n';
			return 0;
		}
	}
	cout << -1 << '\n'; //如果无解，输出 -1
	return 0;
}
```



---

## 作者：TheSky233 (赞：0)

## Description

给定序列 $a_{1 \cdots n}$，求一个最小非负整数 $D$，使得序列中元素要么加上它，要么减去它，要么不改变，使最后序列元素都相等。

（其实翻译少了一句，如果无解，输出 $-1$）。

## Solution

思路：模拟，分类讨论。

1. 当序列的元素值都相等时，直接输出 $0$ 即可。

2. 当序列有两个不相同的序列元素值的时候，如果较大值减去较小值的差为偶数，输出差值的一半（小的加上一半，大的减去一半）；如果为奇数，输出差值。

3. 当序列有三个不相同的序列元素值时，如果**最大值减较大值**的差等于**较大值减最小值**的差，输出这个差值；否则无解，输出 $-1$。

4. 当序列有超过四个不相同的序列元素值时，无论如何都不可能实现，输出 $-1$。

关于排序和判重，可以用 STL 中的 ```set``` 来实现。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[105];
set<int> s;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],s.insert(a[i]);
    if(s.size()>3) cout<<-1<<endl;
    if(s.size()==3){
        set<int>::iterator it=s.end(); it--; it--;
        if(*it-*s.begin()!=*s.rbegin()-*it) cout<<-1<<endl;
        else cout<<*it-*s.begin()<<endl;
    }
    if(s.size()==2){
        if((*s.rbegin()-*s.begin())&1) cout<<*s.rbegin()-*s.begin()<<endl;
        else cout<<((*s.rbegin()-*s.begin())>>1)<<endl;
    }
    if(s.size()==1){
        cout<<0<<endl;
    }
    return 0;
}
```

## Conclusion
以 $255ms$ 排在最优解第三，祝大家 $\color{green}\texttt{AC}$ 愉快！

---

## 作者：xh39 (赞：0)

题目要分几种情况讨论。

数值有4种及以上,无解。

数值有3种:自行判断。

数值有2种:如果数值是偶数,就可以一个加一半,一个减一半。

数值有1种:0

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],b[3]; //尽量把数组多开几个。
bool mark[105]={0};
int main(){
    int n,i,sum=0,d;
    cin>>n;
    for(i=0;i<n;i++){
        cin>>a[i];
        if(!mark[a[i]]){
            mark[a[i]]=1;
            b[sum++]=a[i];
            if(sum>=4){
                cout<<-1;
                return 0; //立刻返回。
            }
        }
    }
    sort(b,b+sum);
    if(sum==1){
        cout<<0;
    }else if(sum==2){
        if(((b[1]-b[0])&1)==0){ //&1是位运算,之句话是判断是不是偶数。
            cout<<((b[1]-b[0])>>1); //a>>n的结果就是a÷2ⁿ。
        }else{
            cout<<b[1]-b[0];
        }
    }else{
        if(b[1]-b[0]==b[2]-b[1]){ //不能加上,减去同一个数。
            cout<<b[1]-b[0];
        }else{
            cout<<-1;
        }
    }
    return 0;
}
```

---

