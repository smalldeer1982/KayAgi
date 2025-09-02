# Making a String

## 题目描述

You are given an alphabet consisting of $ n $ letters, your task is to make a string of the maximum possible length so that the following conditions are satisfied:

- the $ i $ -th letter occurs in the string no more than $ a_{i} $ times;
- the number of occurrences of each letter in the string must be distinct for all the letters that occurred in the string at least once.

## 说明/提示

For convenience let's consider an alphabet consisting of three letters: "a", "b", "c". In the first sample, some of the optimal strings are: "cccaabbccbb", "aabcbcbcbcb". In the second sample some of the optimal strings are: "acc", "cbc".

## 样例 #1

### 输入

```
3
2 5 5
```

### 输出

```
11
```

## 样例 #2

### 输入

```
3
1 1 2
```

### 输出

```
3
```

# 题解

## 作者：那一条变阻器 (赞：2)

~~这道题怎么上提高的？？？明明连普及都算不上好吧？~~


------------
## 进入正题~~~
读题，把题意化简一下就是：
#### **给你n个字母，每个字母最多用ai次，而且每个字母的使用次数都必须不一样（0当然除外啦），问能做的最长串**
他让我们最最长的，那我们就得把所有字母都用上。

但是有每个字母的使用次数，所以我们尽量让每个字符都用完，但实在有相同的，就将它减少一个，万一减少了之后又有用过的呢？

~~那就不做了~~减少了之后还有相同的呢？那就继续减，直到为0。

那这样高的次数被弄到0了会不会很亏呀？当然不会！即时这个数不减，另一个与之次数相同的也会减，那么就是一样的了。思路就这些！

至于实现，可以用桶排序的思想，如果这个数用了，就放这个数的桶里，下次有没有相同的，就可以直接查询这个桶，由于空间太大，数组装不下，就用的map来储存（~~那万恶的STL呀~~）


------------
接下来就是本蒟蒻的代码啦！
```cpp
#include<bits/stdc++.h> 
using namespace std;
map<long long , int> a; //由于数据很大，要开longlong，左边存了数字，那么右边自然就是存储这个桶有没有数的信息了 
long long n , ans = 0 , p; //n是数据范围，ans是答案个数，p是输入的数 
int main( ){
    cin >> n;
    while(n--){ //开始水题 
    	a[0] = 0; //由于0是可以重复的，要特殊处理，所以每次都设为空桶 
        cin >> p;
        while(a[p]) p--; //这个桶有就减少，直到遇到空桶 
        a[p] = 1; //这个桶有人啦 
        ans += p;
    }
    cout << ans;
    return 0;
}
```

## 溜啦溜啦

---

## 作者：wmrqwq (赞：1)

# 原题链接

[CF624B Making a String](https://www.luogu.com.cn/problem/CF624B)

# 题目简述

现在有 $n$ 个字母，要将这些字母拼成一个尽可能长的字符串，但是每个字母出现的次数不能相等，求这个字符串长度的最大值。

# 解题思路

首先输入 $n$，再输入每个字母出现的次数，最后建造一个桶，存储桶内的每个数字，使得桶内每个数字不相同的情况下桶内的数字之和最大，但是，需要注意的是，桶内的数字最少为 $0$，而不是负数。

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define QWQ return 0
long long a[1000010],n,sum,ans;//n表示有几个字母，sum表示存储单个字母的答案，ans存储最终答案
int main()
{
	cin>>n;//输入n
	for(long long i=0;i<n;i++)
		cin>>a[i];//输入每个字母出现了多少次
	sort(a,a+n);//快排a数组
	sum+=a[n-1]+1;
	for(long long i=n-1;i>=0;i--)//为防止出现重复，从大到小枚举
	{
	    if(sum>a[i])//如果sum大于a[i]的话，则桶中的元素无需减少
	    	sum=a[i];
	    else if(sum)//否则桶中的元素减少1
	    	sum--;
	    ans+=sum;//ans增加桶中的元素
	}
	cout<<ans<<endl;//输入答案
    QWQ;//华丽的结束
}

```


---

## 作者：feicheng (赞：1)

## 题意简述
给定 $n$ 个元素，第 $i$ 个元素可以选择 $t_i$ 次，每个元素的选择次数不能相同（0除外），求最多选择次数。
$2\le n\le26,1\le t_i\le10^9$
## 思路讲解
考虑到 $n$ 的范围很小，所以我们可以枚举每一个元素的最大选择次数相加。然后再用一个 `map` 来存某个次数是否出现过即可。在这里需要一个贪心的思想，每次先看能否选择到该元素的最大出现次数，如果不行就递减。这样子能够保证选到的一定是最优解。

由于次数有可能达到 $10^9$，所以要开`long long`

时间复杂度：$O(n\log n)$ （其中 `log` 是 `map` 的复杂度）
## 代码实现
```cpp
/*If you are full of hope,you will be invincible*/
#include <bits/stdc++.h>
#define ri register int
typedef long long ll;
std::mt19937 hpy(time(nullptr));
constexpr int inf(0x3f3f3f3f);
int n;
ll ans,x;
std::map<ll,int> p;
int main(int argc,const char *argv[]){
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	for(ri i = 1;i <= n;++i) {
		p[0] = 0;//由于0可以选无限次，所以我们要初始化p[0]=0
		std::cin >> x;
		while(p[x]) --x;//贪心的选择，如果没有被选就选这个
		ans += x,p[x] = 1;//进行标记
	}
  	std::cout << ans;
	return 0;
}
```

---

## 作者：Aragron_II (赞：1)

又是一道[恶评题](https://www.luogu.com.cn/problem/CF624B)


------------
#### 题意：
一个字符串由 $ n  $ 种字符构成，现在给定每种字符出现的最多次数，让你构造一个字符串，使得出现过的字符的个数各不相同，求字符串最长长度。

#### 思路：
循环模拟字符串（其实就是一串数列），出现次数从高到低排序，能用最多的就用最多的，不能就减一，到0为止。
最后输出最长长度 $ ans $ 。

#### 注意:
$ ans $ 需要开long long。

#### 代码:
```c
#include <bits/stdc++.h> 
using namespace std;
int n,num,a[50];
long long ans=0;
int main(){
	cin>>n;//输入长度
	for(int i=1;i<=n;i++) cin>>a[i];//输入“字符串”
	sort(a+1,a+1+n);//将数列从小到大排序
	num=a[n]+1;
	for(int i=n;i>=1;i--) {
		if(num>a[i]) num=a[i];//大于当前数则赋值
		else if(num) num--;//否则判断num是否为正，若果是则-1
		ans+=num;//计数
	}
	cout<<ans<<endl;	//输出
	return 0;
}
```


---

## 作者：NKL丶 (赞：1)

题目更简述：  
给你$n$个数字，把它们变成完成不一样的几个数字（每一次变化只能用减法，也可以这个数字变成$0$），然后统计这时数列的总和。  
纯暴力即可，不需要太多的东西，只需要注意开$long long$（我这里用的$unsigned long long$）。
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long n,a[30],sum,x,vis;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];//输入
    for(int i=1;i<=n;i++)//双重循环，不停减少
        for(int j=1;j<=n;j++)
            if(a[i]==a[j]&&a[i]!=0&&i!=j){j=0;a[i]--;}//相等，不为0（最后的数列可以出现多个0），不是它本身，则重新搜一遍，并-1
    for(int i=1;i<=n;i++)sum+=a[i];//统计和
    cout<<sum<<endl;//输出
    return 0;
}
```


---

## 作者：Molina (赞：1)

# 题目大意：
[题目链接](https://www.luogu.com.cn/problem/CF624B) 

给了你 $ n $ 个字母组成字符串。在字符串中，每一个字母最多用 $ a_i $ 次。注意：组成字符串时，每个字母的除 $ 0 $ 外的使用次数需要不同。

求组成的字符串最长为多少。
# 本题思路：
### 分析：
本题思路很简单，但是细节有点多。

因为要使组成的字符串最长，所以最好让每个字符使用次数用完，而且还要满足，除 $ 0 $ 外的使用次数不同，很好想到用**桶**的思想来记录每个字母的使用次数。

可看一看本题数据范围 $ 2 \le n \le 26 $ 与 $ a_i \le 10^9 $，虽然 $ n $ 的数据很小，可 $ a_i $ 的数据不能让我们直接用数组来存数据了。这里我们介绍一种**暴力**的办法，当然也可以用别的方法来存，有别人用了，这里就不再赘述。

### 步骤：
这里 $ n $ 的数据超级小，直接暴力完全没问题。

输入，将数组排序，用一个变量来存当前最大的使用次数。接着我们开一个循环，从大到小走一遍，若查询到的数比当前变量小，证明没有重复，将变量赋值为当前的数；反之，若大于等于当前变量，将变量减一，将查询到的数赋值为当前变量。

**注意：**这里要特判一下，若变量为 $ 0 $ 了，证明之后的数对答案都没用贡献了，将当前查询到的下标记下来，退出循环。

然后我们从记录的下标开始累加答案，输出即可。
# 代码来咯~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[30],ans=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)  cin>>a[i];
	sort(a+1,a+n+1);//排序
	long long dq=a[n],xb=1;//dq为当前的查询的最大次数，xb就是下标
	for(int i=n-1;i>=1;i--){
		if(a[i]<dq){
			dq=a[i];
		}
		else if(a[i]>=dq){
			a[i]=dq-1;
			dq--;
		}
		if(dq==0){//特判
			xb=i;
			break;
		}
	}
	for(int i=xb;i<=n;i++){//累加答案
		ans+=a[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Space_Gold_Trash (赞：1)

贼简单的一道题

直接上代码

```c
#include<bits/stdc++.h> 
#define ull unsigned long long
using namespace std;
map<ull,bool>a;
int main( ){
	ull n,ans=0,i,j,k;
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>k;         //输入一个处理一个
		while(a[k]&&k>=1)k--;      //如果已经被用过就--，因为
                                   不管是哪一个--，代价均为1
		a[k]=1;                    //a[k]=1，标记k已经有了
		ans+=k;                    //ans加上k
	}
	cout<<ans<<endl;               //华丽结束
}
```

warm tip:

std::ios::sync_with_stdio(false);要放在cin前，否则要亮

结束感谢帮我发现的大佬@ZhanLang

---

## 作者：naroto2022 (赞：0)

# CF624B 题解

### 题意

现在有 $n$ 个字母，第 $i$ 个字母最多用有 $a_i$ 次，要将这些字母拼成一个尽可能长的字符串，但是每个字母出现的次数不能相等，求这个字符串长度的最大值。

### 思路

思路其实挺简单的：现将数组排序一下，这样个数一样的字母就排在一起了，接下来就设一个临时变量 $cnt$，然后从字母个数大的开始加，这样就可以防止出现重复，这里 $cnt$ 就有大作用了：统计第 $i$ 个字母实际用几次，由题意就有下面两种情况：

1. $cnt\geqslant a[i]$，这样说明第 $i$ 个字母用的次数与其他已经遍历过的都不一样，（因为我们是从有的字母数大的开始遍历的）此时，将 $cnt$ 赋值成 $a[i]$ 就行了。
2. $0<cnt<a[i]$，这就说明第 $i$ 个字母与前面遍历过的字母重复了，所以此时只需要将 $cnt$ 减一。

最优只要将答案 $ans$ 加上 $cnt$ 就行了。

### 总结

1. 开 long long，不开 long long 见祖宗。
2. 分类讨论。
3. 排序。
4. 特殊初始化。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//快排要用
using namespace std;
long long n,ans,a[105],cnt;//不开long long见祖宗
int main(){
	scanf("%lld",&n);
	for(int i=1; i<=n; i++) scanf("%lld",&a[i]);
	sort(a+1,a+1+n);//排序一下，这样用的次数一样的字母就在一起了。
	cnt=a[n]+1;//初始化，因为第一个要特殊加一。
	for(int i=n; i>=1; i--){
		if(cnt>a[i]) cnt=a[i];//如果cnt比a[i]大，则cnt=a[i]
		//这里就体现了为啥一开始要特殊加一
		else if(cnt) cnt--;//如果是正的，就减一。
		ans+=cnt;//加一下。
	} 
	printf("%lld",ans); 
	return 0;
}
```


---

## 作者：__Octhyccc__ (赞：0)

题目意思翻译已经说的很清楚了，不讲了。

采取一种类似于桶排的思想，对于每个输入的 $a_i$，我们都可以检查在当前字符串中有没有出现过 $a_i$ 次的字母，若没有就把 $a_i$ 标记，下次不能再用，若标记了就将 $a_i$ 减 $1$，直到 $0\ge a_i$ 为止，为什么要判下界呢？我给一个 hack 数据：

```
26
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
```
这个数据应该输出 $1$，但是你不判下界答案应该是 $-299$，你一直将 $a_i$ 减 $1$，万一减出来个负数，再加给计数器会让计数器变小的。对于这种当 $a_i$ 一直减，并且小于等于 $0$ 的话就略过就行了。

然后，想开个数组的，但 $10^9$ 的数组你怎么开去！

~~（要么 RE，要么 MLE，套餐也行。）~~

所以说，这题用 map 比较合适，$a_i\le 10^9$，所以一只 int 装不下。**开 long long**！然后用 bool 类型来标记是否出现过就可以过了。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,ans,n;
map<long long,bool>m;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lld",&a);
		while(m[a]==1)a--;
		if(a<=0)continue;//一定注意！
		m[a]=1;
		ans+=a;
	}
	printf("%lld",ans);//这个地方用 %lld，因为是 long long。
	return 0;
}
```

---

## 作者：ssSSSss_sunhaojia (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/CF624B)
# 题目大意：
给定 $n$ 个数，每个数最多取 $a_i$ 次，且要满足每次取的个数都不同，除非不取。问取的个数之和最多为多少。
# 思路：
枚举这 $n$ 个数，对于每一个数，求出它最多能取的个数，这里可以考虑用一个 map 维护每一种取的个数分别被取多少次。最后累加答案就行了。

# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
LL n, a[1001001], ans; 
map <LL, LL> cnt; 
int main(){
	IOS;
	cin >> n; 
	for(re int i = 1; i <= n; i ++) cin >> a[i]; //输入
	for(re int i = 1; i <= n; i ++) { //枚举n个数
		while(cnt[a[i]] && a[i] != 0) a[i] --; //找到它最大能取的个数
		cnt[a[i]] ++; //更新
	}
	ans = 0; 
	for(re int i = 1; i <= n; i ++) ans += a[i]; //累加答案
	cout << ans; 
	return 0;
}

```

---

## 作者：lytqwq (赞：0)

模拟，不解释，只有7个人过

注意开long long

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 27
long long int n,a[N],s;
long long int used[N],top;
int main()
{
	cin>>n;
	for(long long int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(long long int i=n;i>=1;i--)
	{
		for(long long int o=a[i];o>=0;o--)
		{
			long long int ok=1;
			for(long long int k=1;k<=top;k++)
			{
				if(used[k]==o)
				{
					ok=0;
					break;
				}
			}
			if(ok==1)
			{
				used[++top]=o;
				s+=o;
				break;
			}
		}
	}
	cout<<s;
}
```


---

