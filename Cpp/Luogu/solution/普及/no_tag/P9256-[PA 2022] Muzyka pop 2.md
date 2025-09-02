# [PA 2022] Muzyka pop 2

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 2 [Muzyka pop 2](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/muz/)**

你可能还记得，Matthew 喜欢流行音乐。他刚刚编好一首新歌，就差给这首歌谱一个结尾了。

Matthew 想让这个结尾包含一些非空的音符，这些音符用其响度表示，响度是一个正整数。Matthew 可以使用任何响度的音符，但结尾的任务是逐渐淡出整首歌——出于这个原因，结尾的音符响度必须形成一个严格递减的序列。

你可能知道或记得，流行音乐中好的节拍是很重要的。这次 Matthew 发现响度为 $x$ 的音符的节拍值为 $x$ 的二进制形式中 $1$ 的个数。考虑这首歌的剩余部分，他想让这个结尾所有音符的节拍值之和恰好为 $n$。

帮他找到这个正确的音符响度序列。可以证明总存在至少一个满足条件的序列，因此你的任务是输出字典序最小的序列。

注：如果对于两个数字序列 $A$ 和 $B$，在两序列第一个不同的位置，$A$ 序列中这个位置包含的整数比 $B$ 序列的小，我们称数字序列 $A$ 的字典序比 $B$ 的字典序小。如果不存在这个位置，则称更短的那个数字序列字典序更小。例如，序列 $[1, 10000000]$ 的字典序小于序列 $[2,2]$，序列 $[4, 2, 20, 30, 40]$ 的字典序小于 $[4, 2, 100, 1]$，并且序列 $[5,4,3,2]$ 的字典序小于序列 $[5,4,3,2,1]$。

## 说明/提示

对于 $100\%$ 的数据，满足：

$1\le n\le 10 ^ 6$。

## 样例 #1

### 输入

```
3```

### 输出

```
2
3 1
```

## 样例 #2

### 输入

```
10```

### 输出

```
6
7 5 4 3 2 1
```

# 题解

## 作者：LoongPig (赞：4)

## 题意解释

题目主要意思是让你构造一个严格递减的序列使它满足 $\sum \text{popcount}=n$。

## 题目思路

先把 $n$ 范围以内的数的二进制位下 $1$ 的个数加起来。

然后用贪心的思维倒序枚举并去掉每个可以去掉的数。

最后把序列输出出来就好了。


## 题目标程

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int popcnt(int x) {
//计算 x 这个数在二进制下有多少个 1
	int cnt = 0;
	while (x) {
		cnt += x & 1;
		x >>= 1; //x /= 2
	}
	return cnt;
}
int n, m, sum = 0;
vector<int> DragonPig;
int main() {
	scanf("%d", &n);
	m = n;
	while (m--) {
		sum += popcnt(m + 1);//计算 1 ~ n 每个数在二进制下 1 的个数的和
	}
	for (int i = n; i >= 1; i--) {
		if (sum - popcnt(i) >= n) {//判断能不能去掉
			sum -= popcnt(i);
		} else {
			DragonPig.push_back(i);//不能去掉就把它加入序列
		}
	}
	printf("%d\n", (int)DragonPig.size());
	for (auto dragonpig : DragonPig) {
		printf("%d ", dragonpig);
	}
	/*
	用不了 auto 的可以这么写：
	for (int i = 0; i < (int)DragonPig.size(); i++) {
		printf("%d ", DragonPig[i]);
	}
	*/

	return 0;//完结撒花！
}
```

这是本蒟蒻的第一篇题解，求过求过。

---

## 作者：xiewendongTony (赞：3)

## 题目大意

设函数 $\operatorname{popcount}(x)$ 为二进制下 $x$ 中含有 $1$ 的个数，给定正整数 $n$，要求 1 个严格递减，长度为 $k$ 的序列，使得 $\displaystyle\sum_{i=1}^k\operatorname{popcount}(i)=n$，且字典序最小。

## 思路与实现

定义一个变量 $sum$，我们可以先将 $sum\gets\displaystyle\sum_{i=1}^n\operatorname{popcount}(i)$，然后枚举 $i$ 从 $n$ 到 $1$，如果 $sum-\operatorname{popcount}(i)\geq n$，那么 $sum\gets sum-\operatorname{popcount}(i)$，否则加入至序列当中，这样既保证了字典序最小，又保证严格递减。

注：$\operatorname{popcount}$ 可使用 C++ 20 中的 `popcount` 实现，详见[这篇文章](https://www.luogu.com.cn/article/l86yn4aw)中 C++ 20 的 `bit` 库。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[1000010];
int main(){
    int n,sum=0,cnt=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        sum+=popcount((unsigned)i);
    for(int i=n;i;i--){
        if(sum-popcount((unsigned)i)<n)
            ans[++cnt]=i;
        else
            sum-=popcount((unsigned)i);
    }
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++)
        printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：All_Wrong_Answer (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9256)

## 题目大意：

设一个 $f(q)$ 表示二进制下的 $q$ 中含有 $1$ 的个数，构造出一个严格递减且字典序最小的数组 $m$ 使得 $\sum_{i = 1}^{|m|} f(m_i) = n$，这里的 $|m|$ 指的是数组 $m$ 中的元素个数。

## 算法：

**贪心**，首先要找到一个最小的 $p$ 使得 $\sum_{i = 1}^{p} f(i) \ge n$，$p$ 将作为 $m$ 中的第一个元素，再将 $p-1$ 到 $1$ 设为 $m$ 的第 $2$ 到 $p$ 个元素，因为要保持字典序最小，取更大的 $p$ 一定是劣的。

接下来进行贪心，先将设 $t=\sum_{i = 1}^{p} f(i)$，从大到小枚举 $p-1$ 到 $1$，如果 $t-f(j) \ge n$ $(p < j \le 1 )$ 成立，就在答案中中删去 $j$，并将 $t$ 减去 $f(j)$，当 $t=n$ 时，说明找到答案了，就不需要再删除元素了。

## 完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int x;
int lowbit(int n){return n&-n;};
int f(int q){
	int s=0;
	while(1){
		if(q==0) break;
		s++;
		q-=lowbit(q);
	}
	return s;
}//函数，定义见上文 
int s=0;
int vs=0;
int das=0;
int da[1000005];
int main(){
	cin>>x;
	while(1){
		s++;
		vs+=f(s);
		if(vs>=x) break;
	}
	int ff=0;
	for(int i=s;i>=1;i--){
		if(vs==x) ff=1;//找到答案，不用再删了 
		if(vs-f(i)>=x&&ff==0) vs-=f(i);//可以删 
		else da[++das]=i;//不能删，累加总个数并记录答案 
	}
	cout<<das<<endl;
	for(int i=1;i<=das;i++) cout<<da[i]<<" ";
	return 0;
}

```

---

## 作者：封禁用户 (赞：1)

## 题意

给定一个整数 $n$，找到一个严格递减的序列，其中每个数字的二进制表示中包含的 $1$ 的个数之和等于 $n$，并要求这个序列是字典序最小的。

## 思路

这个题就只需要贪心就好了，逐步增加数字 $x$ 并检查二进制表示中 $1$ 的个数来实现。由于题目要求序列是字典序最小的，因此每次选择尽可能小的数字 $x$。

## Code

```cpp
#include <iostream>

using namespace std;

int bit_power(int x) 
{
	int bits = 0;
	while (x > 0) 
	{
		if (x % 2 == 1) 
		{
      		++ bits;
    	}
    	x >>= 1;
  	}

	return bits;
}

int main() 
{
	int n;
	cin >> n;

  	int bits = 0;
  	int x = 1;
  	while (bits + bit_power(x) <= n) 
	{
    	bits += bit_power(x);
    	++ x;
  	}
  	bits += bit_power(x);

	int result[1000007];
  	int k = 0;
  	while (x >= 1) 
	{
    	if (bits - bit_power(x) >= n) 
     		bits -= bit_power(x);
		else 
		{
      		result[k] = x;
      		++ k;
    	}
    	-- x;
  	}

  	cout << k << endl;
  	for (int i = 0; i < k; ++ i) 
	{
    	cout << result[i] << " ";
  	}

  	cout << endl;

	return 0;
}

```

---

## 作者：shihaocheng110909 (赞：0)

[rt](https://www.luogu.com.cn/problem/P9256)

## 思路：

贪心。首先，我们可以这样想：由于字典序是逐位比较，我们希望最大的数最小。最好的话也就是成一个等差数列，且所有数的二进制下的 $1$ 的总数正好为 $n$。

如果不能的话，由于字典序是逐位比较，可以先把数加上，我们假设多了 $k$，那么我们就要从后面尽可能把大的数删除，使 $1$ 的总数等于 $n$。

理论可行，实践开始！

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int num[1000005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a=i;
		while(a)
		{
			num[i]+=a%2;
			a/=2;
		}
	}
	int ans=0,tmp=0,cnt=0;
	for(int i=1;ans<n;i++)
	{
		ans+=num[i],tmp=i,cnt++;
	}
	if(ans==n)
	{
		cout<<cnt<<endl;
		for(int i=tmp;i>=1;i--)
		{
			cout<<i<<' ';
		}
	}
	else
	{
		int anss=ans;
		for(int i=tmp;i>=1;i--)
		{
			if(anss-n>=num[i])anss-=num[i],cnt--;
		}
		cout<<cnt<<endl;
		for(int i=tmp;i>=1;i--)
		{
			if(ans-n>=num[i])ans-=num[i];
			else cout<<i<<' ';
		}
	}
	return "不要CTJ！";
}
```

---

## 作者：TempestMiku (赞：0)

# [题目](https://www.luogu.com.cn/problem/P9256)

## 题意

构造一个字典序最小且严格递减的序列使之满足 $\sum \operatorname{popcount}=n$。

## 分析

采取贪心策略，我们先找见符合条件的最小要求，即找见 $x$ 使得 $\sum\limits_{i=0}^{x}\operatorname{popcount}\le n$，然后从 $x$ 开始倒序枚举，如果刚好不满足就记录答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    void WritE(int x){
        if(x<0) putchar('-'),x=-x;
        if(x>9) WritE(x/10);
        putchar(x%10+48);
    }
    void write(int x){
        WritE(x);
        puts("");
    }
    void Write(int x){
        WritE(x);
        putchar(' ');
    }
}
using namespace Testify;
#define P(x) (__builtin_popcount(x))
const int N=1e6+5;
int n,k,sum=0,x=0;
int stk[N],top;
signed main(void){
    n=read();
    while(sum<=n){
        x++;
        sum+=P(x);
    }
    for(register int i=x;i>=1;i--){
        if(sum-P(i)>=n){
            sum-=P(i);
        }
        else{
            stk[++top]=i;
        }
    }
    write(top);
    for(register int i=1;i<=top;i++){
        Write(stk[i]);
    }
    return 0;
}
```


---

## 作者：bochibochi (赞：0)

首先为了最小化序列的第一个元素，我们找到一个最小的 $x$，使得 $\sum_{i=1}^{x}\textrm {popcount}(i)\le n$。这样序列第一个元素最小值为 $x$，而且取更大的数一定不优，所以只能取 $x$。

然后考虑 $x,x-1,\cdots,2,1$ 这个序列，从大到小贪心删数。

```cpp
#include<iostream>
#include<vector>
using namespace std;
vector<int> v;
int main()
{
    int n, s = 0, x = 0;
    cin >> n;
    while(s < n) s += __builtin_popcount(++x);
    for(int i = x; i >= 1; i--)
    {
        if(s-__builtin_popcount(i) >= n) s -= __builtin_popcount(i);
        else v.emplace_back(i);
    }
    cout << v.size() << endl;
    for(auto a: v) cout << a << " ";
    return 0;
}
```

---

## 作者：Usada_Pekora (赞：0)

题意：构造一个字典序最小的下降正整数序列 $a$，使得 $\sum\limits_{x\in a}\operatorname{popcount}(x) = n$。

首先要让序列最大值最小，这是显然的，我们从小到大找到一个前缀 $\operatorname{popcount}$ 和恰好 $\geq n$ 的数 $m$，这个数就是整个序列的最值，容易发现选择更大的数不会更好。

然后得到了序列 ${m,\dots ,1}$，从大到小删数，因为当我们可以删掉 $x$，删掉比它小的一些数并不会更优。

```cpp
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	int mx = 0, sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += __builtin_popcount(i);
		if (sum >= n) {
			mx = i;
			break;
		}
	}
	vector<int> ans;
	for (int i = mx; i >= 1; i--) {
		if (sum - __builtin_popcount(i) >= n)
			sum -= __builtin_popcount(i);
		else
			ans.emplace_back(i);
	}
	cout << ans.size() << '\n';
	for (int i : ans)
		cout << i << ' ';
	return 0;
}
```

---

