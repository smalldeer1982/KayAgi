# Shooshuns and Sequence 

## 题目描述

有一天，shooshuns发现了$n$个整数的序列，写在黑板上。 shooshuns可以执行一个操作，该操作包括两个步骤：

1. 找到当前序列中第$k$个数字，并将相同的数字添加到序列的末尾；
2. 删除当前序列的第一个数字。
shooshuns想知道板子上的所有数字将要进行多少次操作，才可以让所有数字相同。

## 说明/提示

样例$1$：\
第一个操作之后，将具有顺序$[1，1，1]$。 因此，一个操作足以使所有数字相同，所以答案等于$1$。

样例$2$：\
序列将永远不会让所有数字相同。它始终将包含两个不同的数字$3$和$1$。因此，答案等于$-1$。

## 样例 #1

### 输入

```
3 2
3 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 1
3 1 1
```

### 输出

```
-1
```

# 题解

## 作者：wmrqwq (赞：4)

# 原题链接

[CF222A Shooshuns and Sequence](https://www.luogu.com.cn/problem/CF222A)

# 题目简述

第 $1$ 行输入 $n$，$k$，第 $2$ 行输入 $n$ 个数，现在有 $2$ 种操作：

1. 找到当前序列中第 $k$ 个数字，并将相同的数字添加到序列的末尾；

2. 删除当前序列的第 $1$ 个数字。

最后输出至少需要多少次操作才能让序列中的所有数字都相同，如果无解，则输出 $-1$。

# 解题思路

首先输入 $n$，$k$，以及 $n$ 个数，然后判断这个序列是不是无解的，如果无解，则直接输出 $-1$，并 ```return 0;``` 否则就判断至少需要经过多少次操作才能让序列中的所有数字都相同。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000010],n,k,sum;//sum代表至少需要几次操作才能让序列中的所有数字都相同
int main()
{
    cin>>n>>k;//输入n,k
    for(int i=1;i<=n;i++)
    	cin>>a[i];//输入n个数
    for(int i=k;i<n;i++)
		if(a[i+1]!=a[i])//如果是无解的
		{
			cout<<-1<<endl;//输出-1
			return 0;//停止程序
		}
    for(int i=0;i<n;i++)
		if(a[i]!=a[k])//如果a[i]和a[k]不相等
			sum=i;//那么就把最少操作次数修改为i
    cout<<sum<<endl;//输出sum，记得换行！！！
}
```


---

## 作者：Big_Brain (赞：2)

按照惯例，先放[题目传送门](https://www.luogu.com.cn/problem/CF222A)

## 题意简述

给定一个长度为 $n$ 的字符串，对字符串进行一组操作：

1. 将字符串中的第 $k$ 项复制到字符串的最后；

2. 将字符串的第 $1$ 项删去。

问至少需要经过几组操作，使字符串各项都相等。

## 思路总结

### 题目无解的情况：

如果一个数字 $a_{i}$ 的位置在 $a_{k}$ 及以后，也就是 ${i}\geq{k}$ ，那么在删去若干次第 $1$ 项后，$a_{i}$ 就一定会到达 $a_{k}$ 的位置。在到达 $a_{k}$ 的位置后， $a_{i}$ 就会被复制到字符串的末尾，回到一开始的位置，永远无法被删去。

因此，只有在 $a_{k}$ 及其以后的所有数字全部相等，本题才会有解。

给出这段的代码：

```cpp
for(int i=k;i<=n;i++){
    if(a[i]!=a[k]){
        puts("NO");
        exit(0);
    }
}
```

### 题目有解的情况：

现在，我们假定在 $a_{k}$ 之后所有的数字都相等，以思考有解的情况。

因为在 $a_{k}$ 后的数字不会变动，所以在题目有解时，我们会让 $a_{1}$ ~ $a_{n}$ 之间的所有数字全部变得相等。但是，只要有一个数字 $a_{i}$ 与 $a_{k}$ 不相等，则为了将 $a_{i}$ 删去，我们需要将 $a_{i}$ 之前的所有数全都进行一次操作，此时进行操作的组数自然就是 $i$ 组了。

给出这段的代码：

```cpp
for(int i=1;i<k;i++){
    if(a[i]!=a[k])ans=i;
}
```

## 最后，上完整代码

```cpp
#include<bits/stdc++.h>
#define NO {puts("-1");exit(0);}//输出NO，退出程序
using namespace std;
inline int read()//int的快读模板
{
    char c=getchar(),f=0;int t=0;
    for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
    for(;c>='0'&&c<='9';c=getchar()) t=(t<<1)+(t<<3)+(c^48);
    return f?-t:t;
}
inline string readstr(){//string的快读模板
    char ch=getchar();string x;
    while(ch==' '||ch=='\n')ch=getchar();
    while(ch!=' '&&ch!='\n')x+=ch,ch=getchar();return x;
}
inline void write(int x)//int的输出模板
{
    static int t[25];int tp=0;  
    if(x==0) return(void)(putchar('0'));else if(x<0) putchar('-'),x=-x;
    while(x) t[tp++]=x%10,x/=10;while(tp--) putchar(t[tp]+48);
}
int a[1919810];//不得不说，这题的数据范围太水了，但是为了保险，数组开大一点
int main(){
    int n=read(),ans=0;
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=k;i<=n;i++){//可以看前文的解释
        if(a[i]!=a[k])NO
    }
    for(int i=1;i<k;i++){//同上，看文
        if(a[i]!=a[k])ans=i;
    }
    write(ans);
}
//珍爱生命，远离抄袭
```


---

## 作者：hanyuchen2019 (赞：2)

思维难度巨大的一题。~~(对于我这种菜鸡来说)~~

### part 1 是否有解？

首先，肯定不能直接模拟操作，因为有无解的情况存在。所以说，我们要找出一个结论：在XXX的情况下，可以达到目标状态，即所有数字相同。

假设有一个数据长这样：
```
5 4
a b c A B
```
可以看到，$k$ 之前的部分用小写字母表示，而 $k$ 和之后的部分用大写字母表示。

开始模拟：

1. 复制 $A$ 到结尾，删除 $a$。 `b c A B A`
2. 复制 $B$ 到结尾，删除 $b$。 `c A B A B`
3. 复制 $A$ 到结尾，删除 $c$。 `A B A B A`
4. 复制 $B$ 到结尾，删除 $A$。 `B A B A B`

……

可以看到，几步操作后，所有的小写字母全没了。这也就告诉我们，如果有解，即所有数字相等，就一定要让所有的大写字母相等。

于是我们可以推出一个结论：只有 $k$ 和之后的部分所有数字相同的情况下，有解。

我们就可以写出如下判断是否有解的代码：

```cpp
for(reg i=k;i<=n;i++)
{
	if(s[k]!=s[i])
	{
		cout<<-1;
		return 0;
	}
}
```

### part 2 要操作几次？

已经可以确定是否有解了，是不是就可以模拟了？其实根本不需要。

再模拟一组数据：
```
5 4
a b c A A
```
1. ~~`a`~~$\ \ $`b c A A A`
1. ~~`b`~~$\ \ $`c A A A A`
1. ~~`c`~~$\ \ $`A A A A A`

可以看到，如果 $a,b,c\ne A$，那么 $ans=3$，即 $k-1$；

而如果在小写字母部分的最后有一些与 $A$ 相同的数，每有一个，$ans-1$。

就像这样：
```
6 5
a b A A|A A

ans=2
```
也就是说，答案为 $n-$ 右边那些 $A$ 的数量，即从最后往前数字相同部分数字的个数。

**总结一下，如果 $k$ 和之后的部分所有数字不相同，无解；**

**否则结果为： $n-$ 从最后往前数字相同部分数字的个数。**

### part 3 Code

```cpp
#include<iostream>
#define reg register int
using namespace std;
int s[100005];
int main()
{
	int n,k,t,f;
	cin>>n>>k;
	for(reg i=1;i<=n;i++)//读入
		cin>>s[i];
	for(reg i=k;i<=n;i++)//判断是否有解
	{
		if(s[k]!=s[i])
		{
			cout<<-1;
			return 0;
		}
	}
    
	bool tmp=true;//特判已经符合要求（即数字全相等）的情况，否则容易WA
	for(reg i=1;i<=n;i++)
		if(s[i]!=s[1])
		{
			tmp=false;
			break;
		}
	if(tmp)
	{
		cout<<0;
		return 0;
	}
    
	int ans=n;
	for(reg i=n;i>=1;i--)//倒着枚举后面相等的部分
	{
		if(s[n]==s[i])
			ans--;//每有一个与后面相等的,ans-1
		else
			break;
	}
	cout<<ans;
	return 0;
}
```
码字不易，点个赞呗~

---

## 作者：_int123_ (赞：1)

题目：

## Shooshuns and Sequence

### 题意：

有一天，shooshuns 发现了 $n$ 个整数的序列，写在黑板上。shooshuns 可以执行一个操作，该操作包括两个步骤：

1. 找到当前序列中第 $k$ 个数字，并将相同的数字添加到序列的末尾；
2. 删除当前序列的第一个数字。
shooshuns 想知道板子上的所有数字将要进行多少次操作，才可以让所有数字相同。

### 思路：

1. 先判断是否无解，对于一个数 $i$ 满足 $i>k$，不难发现，经过有限次操作后，一定会到 $k$ 的位置上，然后变到末尾，所以，当第 $k$ 个数以后的数不等于第 $k$ 个数时无解。如果无解，输出 $-1$。

2. 然后再对序列中的数进行删除直到全部都为 $1$ 个相同的数为止。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,k;
int a[1000005];
int ans;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速
    cin>>n>>k;//输入
    for(int i=1;i<=n;i++) cin>>a[i];//输入
    for(int i=k;i<n;i++)//对无解情况特判
		if(a[i]!=a[i+1])
		{
			cout<<"-1";
			return 0;
		}
    for(int i=0;i<n;i++)//删除数，记录答案
		if(a[i]!=a[k]) ans=i;
    cout<<ans;//输出
    return 0;
}
```

完结撒花！！！

---

## 作者：_ZML_ (赞：1)

# 分析

这题是一个很水的题，就是对一个序列有 $2$ 种操作方法，一种是对第 $K$ 个数以前的数的第一个进行删除，另一个则是在整个序列后添加这第 $K$ 个数，使得整个序列为同一个数字，显然，后者是无效操作，则只需要判断第 $K$ 个数以后有无与第 $K$ 个不同的数，有则无解，反之有解。若有解，然后再对前面的数进行删除至全部都为第 $K$ 个数为止。

# [代码](https://www.luogu.com.cn/paste/8h254e3a)

---

## 作者：nightwatch.ryan (赞：1)

## 题意
有两种操作。
- 找到当前序列中第 $k$ 个数字，并将相同的数字添加到序列的末尾。
- 删除当前序列的第 $1$ 个数字。

最后输出最少多少次可以使序列里的所有数字都相同，若没有答案（无解），则输出 $-1$。
## 思路
- （无解的情况）观察发现，我们在序列最后插入第 $k$ 个数，删除第一个数，也就是说第 $k$ 个数之后的数就会一直在序列里，如果他们不相等，则本题就无解，反之则有解。
- （有解的情况）先假定第 $k$ 个数字之后的所有数字都是相同的,如果题目有解则最后会把所有数都变成一样的。但如果有一个数字与第 $i$ 个和第 $k$ 个不相等，则我们要把第 $i$ 个删除，故我们要将第 $i$ 个之前的所有数字，都进行操作，所以要进行的操作次数也必然是 $i$。

## 代码
```cpp
#include<iostream>
const int MAXN=1e5+5;
int a[MAXN],res,n,k;
int main(){
	std::cin.tie(),std::cout.tie();
	std::cin>>n>>k;
	for(int i=1;i<=n;i++)
		std::cin>>a[i];
	for(int i=k;i<n;i++){
		if(a[i+1]!=a[i]){
			std::cout<<-1;
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
		if(a[i]!=a[k])
			res=i;
	std::cout<<res;
}
```



---

## 作者：lightningZ (赞：1)

## 思路
这题我认为应该先判断一下**无解**的情况，在观察几个样例后我们发现，因为我们会在队尾加入第 $k$ 个数，并删除第一个数，也就是说从第 $k$ 个数之后的所有数一定会一直待在队列里，那如果他们不相等，就肯定不会有解。

然后我们再来看有解的情况，最坏的情况是要进行 $n$ 次操作（因为肯定有解，所以进行 $n$ 次操作之后就会开始循环），如果数列里有相等的数，那么我们就可以少删一次，所以我们的答案就会减少 $1$。

最后别忘了特判全部相等的情况。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<k;i++) scanf("%d",&a[i]);
	for(int i=k;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[k]!=a[i])//无解的情况，因为懒所以边输入边判断（不过好像更麻烦了）
		{
			printf("-1");
			return 0;
		}
	}
	bool flag=true;
	for(int i=1;i<=n;i++)//判断全部相等
		if(a[i]!=a[1])
		{
			flag=false;
			break;
		}
	if(flag)
	{
		printf("0");
		return 0;
	}
	int ans=n;//最坏情况
	for(int i=n;i>=1;i--)
	{
		if(a[n]==a[i]) ans--;
		else break;
	}
	printf("%d",ans);
	return 0;
}
```

感谢观看

---

## 作者：Cloote (赞：1)

这道题乍一看

# 典型的水题

然后开心的开始模拟

结果开心的WA了

这让了稍稍冷静了一下

### 第一步：先把目标放在输出-1上

观察后发现一个神奇的规律

只要第k个数后所有数都不相同

必定永远不会让所有数字相同

~~然后在模拟前加了下面这一段代码~~

```cpp
for(int i=k;i<=n-1;i++)
{
	if(a[i]!=a[i+1])
	{
		cout<<-1;
		return 0;
	}
}
```
提交上去

听取WA声一片

### 第二步：弃模拟从找规律

~~花了约半小时手动枚举数据点~~ 发现又有一个神奇的规律

因为步骤相当于循环第k个数之后的所有数，慢慢舍弃之前的数

所以又发现：所得的步骤数就是在第k个数之前所有数最后一个与第k个数不相同的数

又有了下面这段代码
```cpp
for(int i=k-1;i>=1;i--)
{
	if(a[i]!=a[k])
	{
		cout<<i;
		return 0;
	}
}
```
提交上去

又WA了

原因是没有特判所有数都相等的情况

~~之后的几次RE和MLE是因为我没有看见n<=1e5~~

以下是AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int a[N];
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=k;i<=n-1;i++)//判断-1的情况
	{
		if(a[i]!=a[i+1])
		{
			cout<<-1;
			return 0;
		}
	}
	for(int i=k-1;i>=1;i--)//找出所需步骤数
	{
		if(a[i]!=a[k])
		{
			cout<<i;
			return 0;
		}
	}
	cout<<0;//特判
	return 0;
}
//完结撒花！！
```


---

## 作者：XiaoQuQu (赞：1)

刷 1200 偶然刷到的一题，虽然是 1200，但是感觉不那么显然，[题目链接](https://codeforces.com/problemset/problem/222/A)。

考虑操作一次这个序列会发生什么变化，显然，对于 $[k,n]$ 这个整体来说，无论操作多少次，里面元素只是相对位置变化了而已，所以说只要 $[k,n]$ 中有不同的元素，那么就一定无解。

反之，如果  $[k,n]$ 里的元素全部相同，那么在最多删 $k$ 次以后，所有元素都会变的相同，也就是一定有解。但是，如果存在一个 $x$，使得 $[x,k]$ 这段区间内也都相同，那么显然我们只需要删到 $x$，也就是操作 $x$ 次，就能使得序列全部相同了。

```cpp
const int MAXN = 1e5 + 5;
int a[MAXN], n, k;
signed main(void) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int las = a[k], ans = 0;
    for (int i = k; i <= n; ++i) {
        if (a[i] != las) {
            cout << -1 << endl;
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (a[i] != las) ans = i;
    }
    cout << ans << endl;
    return 0;
}
```



---

## 作者：sun_qy (赞：0)

# CF222A Shooshuns and Sequence 题解

[洛谷原题链接](https://www.luogu.com.cn/problem/CF222A)
[CF原题链接](https://codeforces.com/problemset/problem/222/A)

## 题意简述

shooshuns 珂以对一个有 $n$ 个整数的序列执行两种操作：

1. 找到当前序列中第 $k$ 个数字 ${a_k}$，并将 ${a_k}$ 添加到序列的末尾。

2. 删除当前序列中的第一个数字。

## 思路

1. 对无解情况的判断：手动模拟可以发现，某一时刻 ${a_k}$ 之**右**的数（下标大于k）的数在一定次数的操作后一定会到 ${a_k}$ 处，因此原问题有解的必要条件是从 ${a_k}$ 开始往后**所有数**都相等。

2. 然后重复执行第二种操作直至序列中所有数都相等即珂。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int s = 0, f = 1;
	char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') f *= (-1);
		c = getchar();
	}
	while(isdigit(c)) {
		s = (s << 1) + (s << 3) + c - '0';
		c = getchar();
	}
	return s * f;
}
const int N = (114514 + 114514) * (-11 - 4 + 5 + 14) + 114 * 514 + 114 * 51 * 4 + 1 + 145 * 14 - 11 / 4 + 51 / 4; //1e6+5
int a[N];
signed main() {
	int n = read(), k = read();
	for(register int i = 1; i <= n; i ++) a[i] = read();
	for(register int i = k; i < n; i ++)
		if(a[i] != a[i + 1])
			return 0 & printf("-1\n"); //无解情况 
	int res = 0;
	for(int i = 0; i < n; i ++)
		if(a[i] != a[k]) res = i;
	printf("%d\n", res);
	return 0; //完结撒花！ 
} 
```

---

## 作者：Rookie_t (赞：0)

首先输入 $n$ 和 $k$ 以及 $n$ 个数。

如果数组中相邻两项不相同，即 $a_i \neq a_{i+1}$，直接输出无解。

如果有解就判断至少需要经过多少次操作才能让序列中的所有数字都相同。

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 1000010
using namespace std;
int a[maxn],n,k,ans;
signed main(){
	ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i = 1;i<=n;i++)
    	cin>>a[i];
    for(int i = k;i<n;i++)
		if(a[i+1] != a[i]){
			cout<<-1<<endl;
			return 0;
		}
    for(int i=0;i<n;i++)
		if(a[i]!=a[k])
			ans = i;
    cout<<ans<<endl;
    return 0;
}    
``` 

---

## 作者：Dongliang1 (赞：0)

## 题意：
有一个有 $n$ 个整数的序列,你可以执行一个操作，该操作包括两个步骤：
1. 找到当前序列中第 $k$ 个数字，并将相同的数字添加到序列的末尾。
2. 删除当前序列的第一个数字。

输出使序列每个元素都相同的最小操作次数。如果无法实现，就输出 `−1` 。

## 思路：
首先我们判断什么时候无法实现：
1. 当 $a_i=a_k(i\ge k)$ 时:对于所有 $a_j \ne a_k (j < k)$ 我们都可以通过一次操作完成对该数的更改。
2. 当 $a_i \ne a_k(i\ge k)$ 时:我们无法通过操作更改 $a_k$ 之后与 $a_k$ 不同的数。

那么显然的，当第 2 种情况时，无法实现题目要求，所以我们应提前判断这种情况并输出 $-1$。

对于可以实现的情况，我们枚举从 $1$ 到 $k$ 然后输出最后一个与 $a_k$ 不相同的数,这就是答案。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=100005;

int a[N];

int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    //判断是否有解
    for(int i=k+1;i<=n;i++)
    {
        if(a[i]!=a[k])
        {
            cout<<-1<<"\n";
            return 0;
        }
    }
    //如果有解，则求出最小值
    int ans=0;
    for(int i=1;i<k;i++)
    {
        if(a[i]!=a[k])
        {
            ans=i;
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```


---

## 作者：achjuncool (赞：0)

# 做法

我们来模拟一下操作的过程：

```
n = 5, k = 3
[a b c d e]
 a[b c d e c]
 a b[c d e c d]
 a b c[d e c d e]
 a b c d[e c d e c]
 a b c d e[c d e c d]
 a b c d e c[d e c d e]
 ...
```

可以发现：

1. 原序列后面的部分实际上就是在重复 $[k,n]$ 这个子串。

2. $k-1$ 次操作后，即从现序列为原序列的 $[k,n+k-1]$ 开始，现序列的变化会进入一个长度为 $n - k + 1$ 的周期。

根据第一点，我们可以在原序列后面不停地加上 $[k,n]$ 这个子串。

根据第二点，我们只需要添加 $(k-1)+[(n-k+1)-1]$ 即 $n-1$ 个字符即可。

另外，原序列从右往左看一定存在一个最长的所有数字都相同的子串，如果这个子串长度正好为 $n$，则直接输出 `0`，否则找出这个子串的左端点 $pos$，则最后符合条件的序列的左端点最小为 $pos$，所以右端点最小为 $pos + n - 1$。

因此，在原序列后面加 $[k,n]$ 这个子串时，应添加 $max(n-1,pos+n-1)$ 即 $pos+n-1$ 个（$1\le pos$）。

在最后得到的序列中找出最靠左的长度为 $n$ 的符合条件的子串，并根据左端点 $l$ 推出答案 $l - 1$。

找不到就输出 `-1`。

代码中 $a$ 数组开到了 $3e5$，即 $n+(n+pos-1)$ 的最大值。

~~感觉我把这题做得很烦~~

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define qwq ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
ll n, k, a[300005], tot, cur, lst, pos;
int main(){
	qwq;
	cin >> n >> k;
	for(ll i = 1; i <= n; i++) cin >> a[i];
	for(pos = n; pos >= 1; pos--){
		if(pos == 1){
			cout << 0 << endl;
			return 0;
		}
		if(a[pos] != a[pos - 1]) break;
	}
	tot = n;
	for(ll i = 1, j = k; i <= pos + n - 1; i++, j++){
		a[++tot] = a[j];
		if(j >= n) j = k - 1;
	}
	cur = 1, lst = a[1];
	for(ll i = 2; i <= tot; i++){
		if(a[i] == lst) cur++;
		else cur = 1;
		lst = a[i];
		if(cur == n){
			cout << i - n << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;
}
```

---

## 作者：fuzhelin1984 (赞：0)

## 题意

给定一个含有 $ n $ 个元素的序列和一个 $ k $。

现在有一种操作：

首先将序列中的第 $ k $ 个元素再复制一份然后把它置于序列的末尾，再把序列中的第一个元素删除。问你需要几次操作使序列中的每个元素相等，并且存在无解的情况。

## 思路

首先判断无解的情况，由于 $ k $ 的存在，我们很容易发现，下标大于等于 $ k $ 的元素是不会被删除的。所以只要 $ k $ 后的元素中有互不相同的就会导致无解。

然后输出操作次数，可以直接模拟，也可以通过遍历可删除元素得出结果。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 101000;
int a[N];
int main()
{
	int n,k;
	cin >> n >> k;
	for(int i = 1;i <= n;++i) cin >> a[i];
	for(int i = k;i < n;++i) if(a[i] != a[i+1]) return cout<<"-1",0;
	for(int i = k-1;i >= 1;--i) if(a[i] != a[k]) return cout<<i,0;
	return cout<<"0",0;
}

```



---

## 作者：Harry_Meng (赞：0)

# CF222A Shooshuns and Sequence 题解
## 题目分析
[题目传送门](https://www.luogu.com.cn/problem/CF222A)

给定一个数列，然后进行一些操作：

1.找到当前序列中某个数字，并将相同的数字添加到序列的末尾。

2.删除当前序列的第一个数字。

求：数列的所有数字将要进行多少次操作，才可以让所有数字相同。

## 思路分析
1.判断无法实现的情况：只要题目所给出的第几个数之后所有的数不相同，直接输出并结束程序。

2.不断的读题~~并通过测试数据~~寻找规律。发现：**所得的步骤数就是在某个数之前所有数最后一个与某数不相同的数**。

3.注意特判所有数都相等的情况，即直接输出并结束程序。
## 注意事项
1.数据范围在**英文**中，中文翻译里面**没有**。

2.千万不要忘记特判所有数都相等的情况。

PS：[原CF题目](http://codeforces.com/problemset/problem/222/A)。
## Code
```cpp
#include<iostream>
#include<cstdio>
#define N 100005
using namespace std;
int n,k;
int a[N];
int read(){   //快读函数 
	int x=0,f=1;
	char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-'){
		ch=getchar();
	}
	if(ch=='-'){
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);   //使用位运算，速度更快。 
		ch=getchar();
	}
	return x*f;
}
int main(){
	n=read();   //快读 
	k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=k;i<=n-1;i++){   //判断是否有解，如果a[i]!=a[i+1]，直接输出-1并return 0。 
		if(a[i]!=a[i+1]){
			printf("-1");
			return 0;
		}
	}
	for(int i=k-1;i>=1;i--){   //找出所需步骤数。 
		if(a[i]!=a[k]){
			printf("%d",i);   //直接输出i并return 0。 
			return 0;
		}
	}
	printf("0");   //注意特判：所有数都相等，则输出0（即不需要进行任何操作） 。 
	return 0;
}
```


---

