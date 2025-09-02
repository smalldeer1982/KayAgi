# Ehab and a Special Coloring Problem

## 题目描述

You're given an integer $ n $ . For every integer $ i $ from $ 2 $ to $ n $ , assign a positive integer $ a_i $ such that the following conditions hold:

- For any pair of integers $ (i,j) $ , if $ i $ and $ j $ are coprime, $ a_i \neq a_j $ .
- The maximal value of all $ a_i $ should be minimized (that is, as small as possible).

A pair of integers is called [coprime](https://en.wikipedia.org/wiki/Coprime_integers) if their [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) is $ 1 $ .

## 说明/提示

In the first example, notice that $ 3 $ and $ 4 $ are coprime, so $ a_3 \neq a_4 $ . Also, notice that $ a=[1,2,3] $ satisfies the first condition, but it's not a correct answer because its maximal value is $ 3 $ .

## 样例 #1

### 输入

```
4
```

### 输出

```
1 2 1 ```

## 样例 #2

### 输入

```
3
```

### 输出

```
2 1```

# 题解

## 作者：I_like_magic (赞：4)

这道题其实不难。

$\gcd(i,j)=1$，其实就是 $i$ 与 $j$ 互质。

如果 $i$ 与 $j$ 不互质，那么我们一定要让 $a_i$ 与 $a_j$ 相同，只有这样，才能使 $a$ 序列中的最大值最小化。

所以，我们可以使用埃氏筛法，当筛到质数时，给它和它的倍数都赋值为一个新数。

AC Code:

```cpp
#include<iostream>
using namespace std;
int n;
int a[100005];
int c;
signed main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        if(a[i])continue; //非质数
        c++; //一个新数字
        for(int j=1;j*i<=n;j++){
            a[i*j]=c; //倍数赋值为 c
        }
    }
    for(int i=2;i<=n;i++){ //从 2 开始
        cout<<a[i]<<" ";
    }
    return 0; //完美收尾
}
```

---

## 作者：Provicy (赞：2)

有一种想法就是我们让一个数尽可能多的被这个序列中一些位置同时使用。

那么，显然我们可以使一些最大公约数相同的下标这个位置上的数相同。所以我们从每个质数开始往上枚举，并给其赋值。这其实就和埃氏筛法差不多。然后就从 $2$ 到 $n$ 枚举，如果这个位置已经被染色就跳过，否则这个位置的下标一定是质数，然后把这个数的倍数都染色即可。

感性考虑一下其正确性，对于某个质数 $p$，原来某个被其染色的数不由其染色，那么因为这个数无法由前面的数所染色，又不确定后面是否有一个数能将其染色，故这是正确的。

代码如下：

```cpp
#include <bits/stdc++.h>
#define ri register
using namespace std; const int N=200010;
inline int read()
{
	int s=0,w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar(); return s*w;
}
int n,p[N],cnt;
int main()
{
    n=read();
    for(ri int i=2;i<=n;i++)
    {
    	if(p[i]) continue; cnt++;
    	for(ri int j=i;j<=n;j+=i) p[j]=cnt;
	}
	for(ri int i=2;i<=n;i++) printf("%d ",p[i]); puts("");
    return 0;
}
```


---

## 作者：幽界の冥神 (赞：1)

讲点好理解的， 大家都知道埃氏筛法吧

不会的可以看一下：

```cpp
bool p[1000005];
int f[30005], tot;
---------------------
memset (p, 1, sizeof (p));
p[0] = p [1] = 0;
for (int i = 2; i <= n; ++i) {
    if (p[i]) {
        f[++tot] = i;
   	    for (int j = i * 2; j <= n; j += i) {
      	    p[i] = 0;
        }
    }
}
```



其中若$p[i] == 1$，则该数是质数

那么同样的，这道题也可以用类筛法来解决

```cpp
for (int i = 2; i <= n; ++i)
    if (!a[i]) {
        ++num;
        for (int j = i; j <= n; j += i) 
            a[j] = num;
    }
```

意思就是说 :

如果当前这个数没有被任何数赋值即 （$a[j] == 0$）,那么说明这个数与前面比它小的所有数都互质，则它得被单独赋新值，而$num$从$1$开始保证了$a[i]$中的每个元素最小，接下来直接输出$a$数组就可以了

完整代码 :
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define N 2000005

using namespace std;

int n, a[N], num;
int main () {
    scanf ("%d", &n);
    for (int i = 2; i <= n; ++i)
        if (!a[i]) {
            ++num;
            for (int j = i; j <= n; j += i) a[j] = num;
        }
    for (int i = 2; i <= n; ++i)
        printf("%d ", a[i]);
    return 0;
}
```

---

## 作者：Trimsteanima (赞：1)

要构造一个数组，$i$从$2$到$n$，需满足任意一对$i,j$，如果$gcd(i,j)=1$，则$a[i]!=a[j]$。使满足这个条件的数组中的最大值最小化，要输出这个数组。当$j$为$i$的倍数时，$gcd(i,j)$一定不为$1$，所以可以使所有下标为$i$的倍数的位置的值都与下标为$i$的位置的值一样，这样既可以满足要求，也可以保证数组中的最大值最小化。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
int n, cnt, a[N];
int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        if (a[i] == 0) {
            cnt++;
            for (int j = i; j <= n; j += i)
                a[j] = cnt;
        };
    for (int i = 2; i < n; i++)
        printf("%d ", a[i]);
    printf("%d\n", a[n]);
    return 0;
}
```

---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1174C)

## 思路

一道数学题。

只需要用埃氏筛进行筛选，再输出就行了 $2\thicksim n$。

想学埃氏筛的请看[haozinojc](https://www.luogu.com.cn/user/644337)的[这篇](https://www.luogu.com.cn/blog/644337/guan-yu-san-zhong-shai-fa)文章。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
const int N=2e6+10;//为2000010
int n,sum,a[N];//定义
int main()
{
    cin>>n;//输入
	//以下为埃氏筛
    for(int i=2;i<=n;i++)
    {
		if(a[i]==0)
		{
		    sum++;
		    for(int j=i;j<=n;j+=i)a[j]=sum;   
		}
	}
    for(int i=2;i<=n;i++)cout<<a[i]<<" ";//输出元素
    return 0;//好习惯
}
```


---

## 作者：haozinojc (赞：0)

一道带点**数学**的大水题。

### 思路：

一个数如果是质数，那么它与它前面的所有数都互质。

那么接下来写一个简单的**埃氏筛**就行了。

[想学埃氏筛的请点进来。](https://www.luogu.com.cn/blog/644337/guan-yu-san-zhong-shai-fa)

**注：范围是从 $2$ 到 $n$。**

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10; 
int n,cnt,a[N];
signed main(){
	cin>>n;
	for(int i=2;i<=n;i++){
		if(a[i])continue;
		cnt++;
		for(int j=i;j<=n;j+=i)a[j]=cnt;
	}
	for(int i=2;i<=n;i++)cout<<a[i]<<" ";
	return 0;
} 
```


---

## 作者：lianchanghua (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1174C)

### 题目大意
你有一个长度为 $n$ 的数组,满足：

- 对于任意一对 $i$,$j$，如果 $i$,$j$ 互质，则 $a[i]$ $\ne$ $a[j]$。
- 使序列中的 $\max$ 最小。

输出这个序列的第二个位置到最后一个位置的值。

### 思路
因为题目要求 $i$,$j$ 互质，所以我们可以先用埃式筛法，当筛到质数时，将它的倍数全部赋值成当前的值，最后输出即可。

### 代码实现
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,cnt,p[100005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++){
        if(p[i]!=0)				continue;
        else{
			cnt++;
			for(int j=1;j*i<=n;j++)	p[i*j]=cnt;
		}
    }
    for(int i=2;i<=n;i++)	cout<<p[i]<<" ";
    return 0;
}
```

---

