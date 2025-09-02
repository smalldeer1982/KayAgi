# Lesha and array splitting

## 题目描述

One spring day on his way to university Lesha found an array $ A $ . Lesha likes to split arrays into several parts. This time Lesha decided to split the array $ A $ into several, possibly one, new arrays so that the sum of elements in each of the new arrays is not zero. One more condition is that if we place the new arrays one after another they will form the old array $ A $ .

Lesha is tired now so he asked you to split the array. Help Lesha!

## 样例 #1

### 输入

```
3
1 2 -3
```

### 输出

```
YES
2
1 2
3 3
```

## 样例 #2

### 输入

```
8
9 -12 3 4 -4 -10 7 3
```

### 输出

```
YES
2
1 2
3 8
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
4
1 2 3 -5
```

### 输出

```
YES
4
1 1
2 2
3 3
4 4
```

# 题解

## 作者：_byta (赞：3)

首先，如果全部的数累加和不为零，那分成一段就行。

接下来考虑和为零的情况。对于这种情况，我们可以找到第一个不为零的位置。

将序列在它这个位置左右分开，这样可以使两段都不为零。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],sum,k=0,yoy;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	if (sum!=0) 
	{
	   printf("YES\n");
	   cout<<"1"<<endl<<"1"<<" "<<n;
	}
	else
	{
		for (int i=1;i<=n;i++)
		{
			if (a[i]!=0) 
			{
			    printf("YES\n2\n1 %d\n%d %d\n",i,i+1,n);
			    return 0;
			}
		}
		printf("NO\n");
	}
}
```




---

## 作者：lichenzhen (赞：2)

## 题目大意
输入一个序列，看看它能否被分成所有的数的和不为 $0$ 的几段，一段也可以。如果可以输出`YES`和段数及每一段的开始数字和结束数字，不可以就输出`NO`。

## 题目解法
一道比较简单的题目，根据题意思考一下。

主要就是分情况讨论，我们把这个序列之和定义为 $a$。

若 $a \ne 0$，那么此时我们就把这个序列分成一段就可以了。

否则 $a = 0$，此时要分为两种情况。

如果序列中的每一个数都是 $0$ 那么无论怎么分每段之和都是不是 $0$。

否则，我们考虑分成两段，把从序列中第个数到第一个不为 $0$ 的数分成一段，后面的分成一段。

这第一段之和就是第一个不为 $0$ 的数。后面肯定还有不为零的数，因为如果没有序列之和不可能是 $0$，所以第二段的数之和就是第二段所有不为 $0$ 的数之和。

之后代码就好实现了。

### 参考代码
```cpp
#include<iostream>
using namespace std;
int l[100010],n,a;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>l[i],a+=l[i];
    if(a!=0){
        cout<<"YES\n"<<"1\n"<<1<<" "<<n;
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(l[i]){
            cout<<"YES\n"<<"2\n"<<1<<" "<<i<<"\n"<<i+1<<" "<<n;
            return 0;
        }
    }
    cout<<"NO";
}
```

---

## 作者：ttq012 (赞：1)

这道题是一个模拟题。

我们可以记录一个前缀和数组 `s`。如果所有的数都是 $0$，就无解。

然后我们暴力枚举中间的一个位置，如果 $s_i\ne 0$ 且 $s_n - s_i \ne 0$，那么说明可以分成区间 $[1, i]$ 和区间 $[i + 1, n]$，打印答案。

如果 $s_n \ne 0$，可以直接打印区间 $[1, n]$。

否则无解

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[1000010];
int s[1000010];

int main()
{
    int n;
    cin >> n;
    bool flag = false;
    for (int i = 1; i <= n; i ++)
        scanf ("%d", &a[i]), s[i] = a[i] + s[i - 1], flag |= s[i];
    if (! flag) // 全是0，没有办法分
        puts("NO");
    else
    {
        for (int i = 1; i <= n; i ++) // 枚举每一个分界点，如果分界点为n，说明只分一段
            if (s[i] && s[n] - s[i]) // 代表区间 [1, i] 和区间 [i + 1, n]
            {
                if (i == n) // 这个只用分一段，需要特判
                    printf ("1\n1 %d\n", n);
                else // 需要分成两段
                    printf ("2\n%d %d\n%d %d\n", 1, i, i + 1, n); // 正好是区间 [1, i] 和区间 [i + 1, n]
                return 0;
            }
        puts("NO"); // 肯定没有
    }
    return 0;
}

```


---

## 作者：力巴尔 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF754A)

思路：

设数组中所有数的和为 $s$。

若所有数都为 $0$，则输出 NO；

否则如果 $s = 0$，则输出 YES，并找到数组中第一个不为 $0$ 的数，即可将数组分为两段；

如果 $s \not = 0$，则输出 YES，这时候将整个数组分为一段就行了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n + 2], s = 0, b = 0, x = 99999;
    for (int i = 1;i <= n;i++)
    {
        cin>>a[i];
        if (a[i] != 0)
        {
            b = 1;
            x = min(x, i);
        }
        s += a[i];
    }
    if (b == 0)
        puts("NO");
    else if (s != 0)
        cout<<"YES"<<endl<<1<<endl<<"1 "<<n;
    else
        cout<<"YES"<<endl<<"2"<<endl<<"1 "<<x<<endl<<x + 1<<" "<<n;
}
```


---

## 作者：InversionShadow (赞：0)

## CF754A Lesha and array splitting 题解

套路题

+ 如果序列中全是 $0$，怎么分都不行，输出 `NO`。

+ 如果序列的和不等于 $0$，是可以的，因为 $1\sim n$ 的和不为 $0$，输出 `1 n`。

+ 如果序列的和等于 $0$ 并且不全是 $0$，找出第一个不为 $0$ 的地方，因为 $1\sim i$ 不为 $0$，$i+1\sim n$ 也不会为 $0$。

### Code:

```cpp
#include <iostream>
#include <algorithm>
#define int long long

using namespace std;

const int MAXN = 2e5 + 100;

int n, a[MAXN], sum;

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i]; 
    sum += a[i];
  } 
  bool flag = 1;
  for (int i = 1; i <= n; i++) {
    flag = (a[i] == 0);
    if (!flag) { // 如果不全为 0
      break;
    }
  }
  if (flag) { 
    cout << "NO";
    return 0;
  }
  if (sum) { // 和不为 0
    cout << "YES\n" << "1\n" << "1 " << n;
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    if (a[i]) {
      cout << "YES\n" << "2\n" << 1 << " " << i << "\n" << i + 1 << " " << n;
      return 0;
    }
  } 
  cout << "NO"; 
  return 0;
}
```


---

## 作者：syhnumber1 (赞：0)

本题可以分成以下几种情况

- 数组里全部是 $0$。这种情况下，不管分成几段，每段的和都为 $0$。
- 数组的总和不为 $0$。这种情况下，分成一段也可以符合规则。
- 数组的总和为 $0$。这种情况下，不能分成一段，因为那样不符合规则，但可以分成两段，只要建一个前缀和数组，从第一项往后查，如果不为零就输出并跳出循环。

AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[110],s[120];
bool flag=true;
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]!=0){
			flag=false;//求数组里所有元素是否都等于0 
		}
		s[i]=s[i-1]+a[i];
	}
	if(flag){//如果等于0，输出NO 
		printf("NO\n");
		return 0;
	}
	printf("YES\n");//否则先输出YES 
	if(s[n]!=0){//特判全部元素之和是否不等于0 
		printf("1\n");
		printf("1 %lld\n",n);
		return 0;
	}
	printf("2\n");
	for(long long i=1;i<=n;i++){
		if(s[i]!=0){//如果不等于0就输出
			printf("1 %lld\n",i);
			printf("%lld %lld\n",i+1,n);
			return 0;
		}
	}
	return 0;
} 
```

---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF754A)

# 题意简述

给定一个数组，问能否把它分成几段（一段也可以），使得每一段之和都不为 $0$？

若可以，则输出 `YES`，下一行输出段数，之后每行输出每一段的开始位置和结束位置（闭区间）；否则输出 `NO`。

# Solution

简单模拟练手题。

首先判断数组元素是否每一个都为 $0$，如果是，输出 `NO`。

然后判断数组所有元素加起来是否为 $0$：

* 如果不是，则分成 $1$ 段就可以，直接输出：

```cpp
YES
1
1 n //开始位置和结束位置
```

* 如果不是，累加数组元素（其实就是前缀和），如果某个位置的前缀和不为 $0$，直接分两段输出。

# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[105];
bool pd() {//判断数组所有元素是否都为 0
    int flag = 0;
    for(int i=1; i<=n; i++) {
        if(a[i]) flag = 1;
    }
    if(!flag) return true;
    return false;
}
bool pd1() {//判断数组所有元素的和是否等于 0
    int sum = 0;
    for(int i=1; i<=n; i++) sum+=a[i];
    if(sum == 0) return true;
    return false; 
}
int main() {
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%d", &a[i]);
    if(pd()) {//如果每一个元素都为 0 
        printf("NO"); 
        return 0;
    }
    if(!pd1()) {//如果和不为 0 
        printf("YES\n1\n1 %d", n);
        return 0;
    }
    for(int i=1; i<=n; i++) {//遍历数组的每一个位置 
        int ans = 0;
        for(int j=1; j<=i; j++) ans+=a[j];
        if(ans) {//如果和不为 0 
            printf("YES\n2\n1 %d\n%d %d", i, i+1, n);
            return 0;
        } 
    }
    return 0;
}
```

By 2022.6.28 蒟蒻的第十七篇题解

---

## 作者：Southern_Dynasty (赞：0)

分类讨论。

首先考虑第一种情况：若整段序列的和不为 $0$，直接分成一段即可。

接下来是第二种情况：若整段序列的和为 $0$，我们考虑枚举 $1$ 到 $n$ 范围中的 $i$，若 $a_i$ 不为 $0$，那么直接将序列分为 $1$ 到 $i$ 和 $i+1$ 到 $n$ 两段序列即可保证每一段的和都不为 $0$，原因显然。

最后一种情况：整段序列的和为 $0$ 且每一项都为 $0$。这是唯一无解的情况，因为无论怎样分配，和都为 $0$。所以直接输出 `NO` 即可。

因此我们只需要维护一个 `cnt` 变量来存储整个序列的和，然后按照以上三种情况讨论即可。

## $\text{Code:}$

```cpp
#include<bits/stdc++.h>
#define gt getchar
#define pt putchar
#define y1 y233
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
using namespace std;
inline int read(){
   	int x=0,f=1;char ch=gt();
   	while(!isdigit(ch)){if(ch=='-')f=-1;ch=gt();}
   	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gt();}return x*f;
}
inline void print(int x){
   	if(x<0)pt('-'),x=-x;
   	if(x>9)print(x/10);
   	pt(x%10+48);
}
inline void println(int x){
	print(x);
	pt('\n');
}
int n,a[105],cnt;
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		cnt+=a[i];
	}
	if(cnt!=0){
		puts("YES\n");
		printf("1\n1 %d\n",n);
		return 0;
	}
	for(int i=1;i<=n;++i){
		if(a[i]!=0){
			printf("YES\n2\n");
			printf("1 %d\n%d %d\n",i,i+1,n);
			return 0;
		}
	}	
	printf("NO\n");
	return 0;
}
```


---

## 作者：YuanZihan1225 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF754A)

# 前言

简单参考了其他几位大佬的代码，发现我的方法略有复杂，大家可以多看几种方法，多一点思路。然后题意已经说的够明白了，我就不再说明。

# 进入正题

我们可以将问题分为以下几个子问题：

1. 显然，一个全为 0 的序列是没有办法合法划分的，直接输出 NO 。

2. 对于一个不为 0 的数，则就可以让这一个数单独成一个区间。

3. 对于一个 0 ，可以考虑将其与后面的第一个不为 0 的区间，可用 While 循环解决，细节见代码。

4. 如果分至最后一个区间时最后一个区间中全是 0 ，则考虑将其与前面一个区间合并，具体见下图：

最开始是这样，两个区间：

![](https://cdn.luogu.com.cn/upload/image_hosting/lv08r85r.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这个时候就需要将第一个区间和第二个区间合并， l 为第一个区间的，而 r 为第二个区间的：

![](https://cdn.luogu.com.cn/upload/image_hosting/h6x7optv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

# 代码见下

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[105], ans, al[105], ar[105];//用al,ar来存区间左右端点
bool flag = true;//标记区间是否全为0
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		if(a[i])
			flag = false;
	}
	if(flag)
		return puts("NO"), 0;//小压行
	int l, r;
	for(l = 1; l <= n; l++)
	{
		r = l;
		while(a[r] == 0 && r <= n)//用while与后面的区间合并
			r++;
		al[++ans] = l, ar[ans] = r, l = r;//存储区间
	}
	if(ar[ans] == n + 1)//判断是否满足第四种情况
		ar[ans - 1] = n, ans--;
	puts("YES");
	cout << ans << endl;
	for(int i = 1; i <= ans; i++)
		cout << al[i] << " " << ar[i] << endl;
	return 0;
}
```


---

## 作者：Misaka_Mik0t0 (赞：0)

显然，当数列里每个数都是 $0$ 时，不可以。因为不管是哪个子段的和均为 $0$。

当整个数列中不全为 $0$ 时分为两种情况：
- 假若整个数列之和不为 $0$，直接把整个数列算作一段。
- 若整个数列之和为 $0$，则找到数列中第一个不为 $0$ 的数，将它及它之前的数分为第一段，后面的所有数分为第二段，这样每一段的和都不为 $0$。第一段之和为这个数；第二段之和为这个数的绝对值。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[105],s,flag=1; 
//flag用来存放数列是不是全是0。1代表是，0代表不是
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&p[i]);
		s+=p[i];//s用来存放数列的和
		if(p[i])flag=0;
	}
	if(flag){
		printf("NO");
		return 0;
	}
	if(s){
		printf("YES\n1\n1 %d",n);
		return 0;
	}
	int i=1;
	for(;!p[i];++i);//求出第一个不为0的数
	printf("YES\n2\n1 %d\n%d %d",i,i+1,n);
	return 0;
}
```

---

