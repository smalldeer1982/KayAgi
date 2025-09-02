# Queue

## 题目描述

There are $ n $ schoolchildren, boys and girls, lined up in the school canteen in front of the bun stall. The buns aren't ready yet and the line is undergoing some changes.

Each second all boys that stand right in front of girls, simultaneously swap places with the girls (so that the girls could go closer to the beginning of the line). In other words, if at some time the $ i $ -th position has a boy and the $ (i+1) $ -th position has a girl, then in a second, the $ i $ -th position will have a girl and the $ (i+1) $ -th one will have a boy.

Let's take an example of a line of four people: a boy, a boy, a girl, a girl (from the beginning to the end of the line). Next second the line will look like that: a boy, a girl, a boy, a girl. Next second it will be a girl, a boy, a girl, a boy. Next second it will be a girl, a girl, a boy, a boy. The line won't change any more.

Your task is: given the arrangement of the children in the line to determine the time needed to move all girls in front of boys (in the example above it takes 3 seconds). Baking buns takes a lot of time, so no one leaves the line until the line stops changing.

## 说明/提示

In the first test case the sequence of changes looks as follows: MFM $ → $ FMM.

The second test sample corresponds to the sample from the statement. The sequence of changes is: MMFF $ → $ MFMF $ → $ FMFM $ → $ FFMM.

## 样例 #1

### 输入

```
MFM
```

### 输出

```
1
```

## 样例 #2

### 输入

```
MMFF
```

### 输出

```
3
```

## 样例 #3

### 输入

```
FFMMM
```

### 输出

```
0
```

# 题解

## 作者：decoqwq (赞：26)

题目大意：
给你一个队列，$M$表示男生，$F$表示女生，每秒一个男生能和右边一个女生交换位置，问你需要多少秒所有女生都换到最左边。

思路：
对于一个女生而言，它需要换到最左边，意味着她至少需要换她前面所有男生个数次，我们通过递推，$O(n)$扫一遍来解决这个最大次数。如果她前面有个女生，那么她也至少需要前面那个女生的次数$+1$次，否则就是男生数量，我们取最大值即可。
```cpp
#include <bits/stdc++.h> 
using namespace std;
string s;
int main()
{
	cin>>s;
	int ans=0,m=0;
	int len=s.size();
	for(int i=0;i<len;i++)
	{
		if(s[i]=='M') 
		{
			m++;
		}
		if(s[i]=='F'&&m>0)
		{
			ans=max(ans+1,m);
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：郑朝曦zzx (赞：4)

# 一 解题思路
我们来讨论一下，对于某个 F 所需的最少移动次数。

- 她至少要与她前面的所有 M 交换位置，也就是至少要移动前面 M 的个数。

- 如果她前面有 F，那么她的移动步数就至少是前面那个 F 的移动步数 + 自己等待的一秒。

所以我们有转移方程：
$ ans = \max(ans + 1, cnt)$

$ans + 1$ 指的是情况二，等一秒 + 前面移动时间

$cnt$ 表示前面的 M 个数。

# 二 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
string s;
int ans, cnt;
int main()
{
	cin >> s;
	for (int i = 0; i < s.length(); ++i)
	{
		if (s[i] == 'M') ++cnt;
		if (s[i] == 'F' && cnt) ans = max(ans + 1, cnt);
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：Fr0sTy (赞：3)

## 题意概述
------------

`F` 代表女生，`M` 代表男生。 每次如果男生在女生左边，调换男女生位置。直到所有女生都在男生的左边。

很显然，每秒钟不止一个女生可以换位置。（如 **样例 2**）


## 思路
------------
### 思路 1 （TLE on #8）

模拟每一秒调换，直到满足要求。

```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
int times;
bool check() {
	bool flag=false;
	for(register int i=0;i<str.size();i++) {
		if(str[i]=='M') flag=true;
		if(str[i]=='F'&&flag) return false; 
	}
	return true;
}
int main() {
	cin>>str;
	while(!check()) {
		for(register int i=str.size()-1;i>=0;i--) {
			if(str[i]=='F'&&i!=0) {
				if(str[i-1]=='M') {
					swap(str[i],str[i-1]);
					i--;
				}
			}
		}
		times++;
	}
	cout<<times;
	return 0;
}
//code by TheCedar
```

这个代码的**最坏**时间复杂度是 $O(n^2)$。一看看数据限制： $1 \leqslant n \leqslant 1 \times 10^6$ 。显然超时。

这里具体坑点也不说了，反正过不了。

### 思路 2 （AC）

既然要让所有女生换到最左边，与其枚举每一秒，还不如让每一个女生一次直接换到最左。

当然，如果有一个女生在这个女生的左边且两个女生在一起。那么后者将会在前者**后 1 秒**到达左边。

反之，如果一个女生左边相邻位置没有女生，那么她到达最左边就是前面男生的个数。

**重要的一点：** 在这些女生到达最左边的时间里，应该**取最大值**。

因为每秒，所有可以调换位置的女生都可以进行调换，所以在最后一个女生到达最左边时，其他女生已经到达。

#### 变量说明

设某女生前男生个数为 $cnt$，我们每扫到一个男生就 `cnt++` 即可。

设最后一个女生到达左边的时间为 $times$。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
string str;
int cnt,times;
int main() {
	cin>>str;
	for(int i=0;i<str.size();i++) {
		if(str[i]=='M') cnt++;
		if(str[i]=='F'&&cnt>0) times=max(times+1,cnt);
	}
	printf("%d",times);
	return 0;
}
//code by TheCedar
```

时间复杂度 $O(n)$，轻松过掉此题。

---

## 作者：ChikHid (赞：2)

(住:这是本蒟蒻第一篇题解，难得发现一题可以写题解并会做的题)

------------
#### 题目简化：
将一个字符串中的所有的'F'都移到左边，每次操作只能将若干个'F'与在左边离他最近的'M'进行交换，输出进行了多少次操作。

~~(我是不是把一道dp做成了字符串...)~~

### 思路(差不多就推出了公式):

(渐渐回到了dp)

对于每一个'F'而言，它需要换到最左边，意味着它至少需要换它前面所有'M'个数次，这样我们便可以使用个变量x用来记录当前第i个人前面有多少个'M'，这个'F'所需的交换次数就是x。

还有一种情况，就是如果这个'F'前还有多个'F'怎么办？我们可以发现，这个'F'必须在与上一个'F'之间有'M'才能交换位置，否则便得上个'F'与某个'M'交换位置后，才能使这个'F'与上一个'F'之间有'M'，便可交换，所以，在这个'F'与上一个'F'之间有'M'时，交换次数为x,否则便是上个'F'的次数+1，在推理下去，便可以推出总的操作次数是最后的'F'的次数的最大值，这就是公式。

### 稍微理一理：

我们用i表示询问到了第i位，x表示前面已经有了多少个'M'，ans表示当前的F用了几次。

### pascal代码附上：
```
uses math;                        //数学库，就是下面的max
var
  i,x,ans:longint;
  s:string;
begin
  readln(s);
  x:=0;                           //x表示有多少个'M'
  for i:=1 to length(s) do        //i表示询问到了第几位
  begin
    if (s[i]='M') then
      inc(x);                     //如果是'M'则x++
    if (s[i]='F')and(x>0) then
      ans:=max(ans+1,x);          //如果是女生则判断最大值,记得前一个F要加1
  end;
  writeln(ans);
end.
```
这就是代码，简单易懂。
(不要复制题解)

---

## 作者：alex_liu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF353D)
## 思路：
既然队列里的男生不能主动调换位置，那我们何尝不只考虑女生呢？

题意中说女生只能与前一个男生交换，那么就让她一直换到第一个男生的最前面不就好了？

~~大模拟水题~~

## 代码:
```cpp
#include<bits/stdc++.h> 
using namespace std;
string s;
int main(){
	cin>>s;//输入 
    int ans=0,men=0,len=s.size();//ans是需要移动的步数，men是当前女生前面的男生人数，len是此队列的长度
	for(int i=0;i<len;i++){//枚举每个人的操作
		if(s[i]=='M')men++;//男生：计数器+1 
		if(s[i]=='F'&&men>0)ans=max(ans+1,men);//女生：移动 
	}
	printf("%d\n",ans);//输出移动步数 
	return 0;//完美结束 
}
```


---

## 作者：蒟蒻abcd (赞：1)

对于这道题，我最想知道的是：这为什么是紫题！  
这题是我在模拟赛中做的。当时，我还以为是求逆序对。但是，仔细一看，发现不是逆序对。为什么呢？原来，同一秒钟可以交换多个男生和女生。  
可是女生不会让女生（因为都是女的），所以当女生堵在一起的时候，就得重新算过了。我觉得吧，这题也就那么点难度。  
接下来附上我这像贪心的动归（或者说是像动归的贪心）。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001]={0};
int main()
{
//	freopen("queue.in","r",stdin);
//	freopen("queue.out","w",stdout);
	string s;
	cin>>s;
	int last=-1,count=-1;
	int l=s.size();
	for(int i=0;i<l;i++)
	{
		if(s[i]=='M')continue;
		count++;
		if(last==-1){last=i;a[i]=i-count;continue;}
		if(a[last]==0){last=i;a[i]=i-count;continue;}
		a[i]=max(i-count,a[last]+1);
		last=i;
	}
	cout<<a[last]<<endl;
	return 0;
}
```  
谢谢。

---

## 作者：0xFF (赞：1)

#### 题目大意


------------
给定一个由 ```M & F``` 组成的序列，每次可以交换相邻位置上的两个字符（两个字符必须一个为 ```M```，另一个为```F```），在一秒内，多次操作可以同时进行，但是每一秒内，一个字符只能进行一次操作。问最少需要多少秒能够把原序列换成是左边全是 ```F``` 并且右边全是 ```M``` 的序列。

#### 题目分析


------------
考虑每一个 ```F``` 想要移动到左边的步数。

如果一个 ```F``` 的左边全都是 ```M```，那么此 ```F``` 移动至最左侧的步数即为其左边 ```M``` 的个数。

但是如果与这个 ```F``` 相邻的也是一个 ```F```，那么这一秒此 ```F``` 是无法交换的，所以其答案为其相邻的 ```F``` 的答案加上一。

综上，我们只需要扫一遍整个序列，如果读入的字符是 ```M``` 就让记录 ```M``` 个数的 ```cnt++```，如果读入的字符是 ```F``` 就令记录答案更新。

#### 代码实现


------------

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define int long long

using namespace std;
string s;
signed main(){
	cin>>s;
	int ans = 0 , cnt = 0;
	int len = s.size();
	for(int i=0;i<len;i++){
		if(s[i] == 'M'){
			cnt++;
		}
		if(s[i] == 'F' && cnt > 0){
			ans = max(ans+1,cnt);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Xhesika_Frost (赞：0)

有男有女的情况下光考虑女生就行了。

这个题目有个小规律，对于每一个女生，它的时间是取 $max(上一个女生的时间+1，她前面的男生数量)$。

这是为什么呢，考虑一下什么时候一个女生的时间会受她前一个女生影响。如果俩个女生离得比较近，那么就有可能存在撞车的情况，即前一个女生停住了，导致后一个女生的某一时刻不能移动，浪费了一次移动机会。

那么为什么会是 $+1$ 呢？想一下当后面的女生是不会影响前面的女生撞上了之后。她们就"合为一体"了，后面的人比前面的人有一次移动的延迟，所以后面的人只会比前面的人晚走一次移动 。

这样我们就可以理解这个递推的正确之处了。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<stack>
#include<algorithm>
using namespace std;
template<class T>inline void read(T &x)
{
    x=0;register char c=getchar();register bool f=0;
    while(!isdigit(c))f^=c=='-',c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if(f)x=-x;
}
template<class T>inline void print(T x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar('0'+x%10);
}
string s;
int ans;
int la;
int tot;
int main(){
	cin>>s;
	int n=s.length();
	s=' '+s;
	for(int i=1;i<=n;++i){
		if(s[i]=='M'){
			tot++;
		}
		if(s[i]=='F'){
			if(tot){
				ans=max(tot,la+1);
				la=ans;
			}
		}
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：zct_sky (赞：0)

### Description:
-----
给你一个字符串，其中，$M$ 表示男生，$F$ 表示女生，每秒可将一个女生和她右边的男生交换位置，请问至少需要几秒才能将所有女生都换到左边。
### Solution:
-----
对于任何一个女生来说，要换到左边，则她前面有几个男生就要换几次。

如果她前面也有女生，那么她需要换前面那个女生换的次数 +1 和前面男生个数的最大值，也就是说，假设她前面那个女生换的次数为 $a$，且她前面有 $b$ 个男生，那么她就要换 $\max(a+1,b)$ 次。
### Code:
-----
```c++
#include<bits/stdc++.h>
using namespace std;
string a;
int m,ans,l; 
int main(){
	cin>>a;
	l=a.length();
    for(int i=0;i<l;i++)
    	if(a[i]=='M')m++;
    	else if(m)ans=max(ans+1,m);
	cout<<ans;
    return 0;
}
```

---

## 作者：A_Đark_Horcrux (赞：0)

> 每秒如果一个女生前边有一个男生，两个人就可以进行调换位子。

很显然，对于第一个女生，前边有多少个男生换多少次就行了。

但是对于之后的女生可能出现这样的情况：

```
MFFFFFFFFFFFFFFFFFFFFF
```

大 堵 车

可以发现，每一个前面排的也是女生的女生，需要等前一个女生把一个男生交换到后面，自己前面才有男生可以交换。因此所需时间为前一个女生所需时间加一

考虑记录一个 f 数组表示每个女生交换完所需的时间，如果前面是女生，则时间为前一个女生所需时间加一，否则为前面的男生数量。

```cpp
#include<iostream>
using namespace std;
int s,maxx,k,i,f[100010]; string a;
int main()
{
	cin>>a; while(a[i]=='F') i++;//前面的跳过
	for(i;i<a.size();i++)
	{
		if(a[i]=='M') s++;//记录男生个数
		else
		{
			f[++k]=(a[i-1]=='F'?f[k-1]+1:s);//转移
			maxx=max(f[k],maxx);//记录最大秒数
		}
	}
	printf("%d",maxx);
	return 0;
}
```

---

