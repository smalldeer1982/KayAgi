# 「SiR-1」Popsicle

## 题目背景

然而如何优雅地摆烂？

## 题目描述

猫猫有若干个雪糕棒排成一排，每个雪糕棒上有一个 $0\sim 9$ 的数字，并且满足最左边的雪糕棒上写的数字不为 $0$。猫猫认为这一排雪糕棒从左到右依次构成了十进制正整数 $n$。

猫猫认为 $0$ 是美好的，所以她会尽可能把 $n$ 变成 $0$，也就是把所有雪糕棒都拿走。

猫猫每次会进行一次操作。每次操作选择一个数字非 $0$ 的雪糕棒，并将其减 $1$。这之后，如果最左边有连续的一些数字为 $0$ 的雪糕棒（也即 $n$ 出现了前导 $0$），猫猫会把这些雪糕棒拿走。

小老鼠会来捣乱，它会在某个时刻（可能是所有操作开始之前，也可能是猫猫任意一次操作之后）改变某个雪糕棒上的一个数字。小老鼠**总共只能改变一个数字**。

小老鼠希望操作次数尽量多，猫猫希望操作次数尽量少，所以她想知道二者都使用最优策略时，她的操作次数。

## 说明/提示

### 样例解释 1

对于第一组数据，小老鼠可以一开始就将 $1100$ 变为 $1109$，这样猫猫共需要 $1 + 1 + 9$ 次操作把 $n$ 变为 $0$。

### 数据规模与约定

**本题采用捆绑测试。**

+ Subtask 0（13 pts）：$n \leq 99$。
+ Subtask 1（13 pts）：$n = 10^k$，$k$ 为自然数。
+ Subtask 2（13 pts）：$n = 10^k - 1$，$k$ 为正整数。
+ Subtask 3（13 pts）：$n \leq 999\ 999$。
+ Subtask 4（48 pts）：无特殊限制。

对于所有数据，$1 \leq T \leq 3333$，$1 \leq n \leq 9\ 999\ 999\ 999\ 999(=10^{13} - 1)$，毕竟猫猫最多一捆只有 $13$ 根雪糕嘛。

## 样例 #1

### 输入

```
2
1100
11332132121```

### 输出

```
11
28```

# 题解

## 作者：lilong (赞：13)

由题意可知，猫猫至少需要进行 $n$ 的数位和次操作。注意到一个关键信息，当有前导 $0$ 时猫猫会立刻拿走该雪糕棒，因此此时不能修改其数值。所以结论也就出来了：当 $n$ 中存在 $0$ 时，答案为 $n$ 的数位和加 $9$，否则当任意一位修改为 $1$ 时，修改其为 $9$，答案为 $n$ 的数位和加 $8$。

代码如下：
```cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while( T -- )
    {
	   	int ans = 0,mi = 9;
		string s;
		cin >> s;
		for( int i = 0 ; i < s.size() ; i ++ )
			ans += s[i] - '0',mi = min( mi , s[i] - '0' );
    	if( mi == 0 ) cout << ans + 9 << endl;
    	else cout << ans + 8 << endl;
    }
    return 0;
}
```


---

## 作者：Hisaishi_Kanade (赞：5)

## Problem

因为是 A 题还是写一下吧。

+ 给你一个数 $n$。
+ 一次操作给 $n$ 的某个数位 $-1$，并立刻去掉所有前导 $0$。
+ 一次 trick 在某个时刻改变 $n$ 的某个数位。
+ 对于所有可能的 trick 情况，求最优策略下把 $n$ 删完的操作次数的最大值。
+ 多组数据，$1 \leq T \leq 3333$，$1 \leq n \leq 10^{13} - 1$。
+ 嗯对，搬的讲评。

## Solution

事实上，在没有 trick 的时候，样例解释已经给出了提示，答案为 $n$ 的数位和。

如果有 trick，要求最优策略下最大，显然 trick 尽可能会让 $0 \rightarrow 9$，这样答案会 $+9$。


这样过了第一组样例，但是没过第二组样例。怎么会事呢？

注意到无论怎么删都肯定会在最后一步产生一个 $1$，所以 trick 带来的贡献至少是 $1 \rightarrow 9$ 即 $8$。

由于时刻删除前导 $0$，可以选择从前往后每次只删最高位，这样 **在原数没有 $\bm 0$ 时** 不可能在过程中产生任何 $0$。

在这时给答案 $+8$ 即可。

时间复杂度 $\mathcal O(T\log n)$。


---

## 作者：AKPC (赞：4)

水！
### 思路
一眼看以为直接改变雪糕棒中最小的数为 $9$ 就行，其实错的，因为老鼠可以在任意时候改变数字。

那么，如果开局没有 $0$ 和 $1$，为何不在某个数变为 $1$ 的时候把它改成 $9$ 呢？这也是最佳方案。反之，直接选择将最小的数改为 $9$ 即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,minn,ans,s;
signed main(){
	cin>>n;
	while (n--){
		cin>>s;ans=0,minn=114514;
		for (int i=0;i<=log10(s);i++) ans+=s/(int)pow(10,i)%10,minn=min(minn,s/(int)pow(10,i)%10);
		if (minn>1) minn=1;
		ans+=(9-minn);cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 P9354 「SiR-1」Popsicle](https://www.luogu.com.cn/problem/P9354)

## 解题思路

1. 对于猫猫，每次只能将一个雪糕棒的数字减 $1$。在没有小老鼠影响的情况下，操作次数为 $n$ 的各位数字之和。

2. 对于小老鼠，只能改变一个数字，要使操作次数尽量多：

- 如果有 $0$，最优策略是将 $0$ 改成 $9$，使操作次数增加 $9$ 次。
- 否则没有 $0$，在猫猫把一个雪糕棒的数字减到 $1$ 时，把 $1$ 改成 $9$，使操作次数增加 $8$ 次。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		ll n;
		cin>>n;
		int sum=0;
		bool k=0;
		while(n)
		{
			if(n%10==0)k=1;
			sum+=n%10;
			n/=10;
		}
		cout<<sum+(k?9:8)<<'\n';
	}
	return 0;
}
```

---

## 作者：_5t0_0r2_ (赞：1)

# 分析：
如果，小老鼠不做操作，那么猫猫需要操作的次数就是 $n$ 每位数的和。

如果小老鼠用了操作，就有两种情况：

1. 如果 $n$ 中有 $0$，小老鼠就可以把它变成 $9$，这样猫猫的操作次数就是本来 $n$ 每位数的和加 $9$。
2. 如果 $n$ 中没有有 $0$，小老鼠就可以在任意一位数变为 $1$ 时将其变为 $9$，这样猫猫的操作次数就是本来 $n$ 每位数的和加 $8$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;string n;
int main(){
	cin >> t;
	for(int i = 1;i <= t;i++){
		cin >> n;
		int ans = 0;
		bool judge = false;
		for(int j = 0;j < n.length();j++){
			if(n[j] == '0')//判断是否有0
				judge = true;
			ans += n[j] - '0';
		}
		if(judge)
			ans += 9;
		else
			ans += 8;
		printf("%d\n", ans);
	}
}
```


---

## 作者：251Sec (赞：1)

如果不更改任何一位数，答案显然为数位和。

如果原数中存在 $0$，那么直接改成 $9$ 即可，答案为数位和加 $9$，显然不可能更大。

如果原数不存在 $0$，那么猫猫可以从左往右依次把每个位置的数字变成 $0$ 然后取掉，这样全程不会产生 $0$，但一定会产生 $1$，这时把这个数改成 $9$，答案为数位和加 $8$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll w;
int T;
ll ans;
bool fl;
int main() {
    scanf("%d", &T);
    while (T--) {
        ans = 8; fl = false;
        scanf("%lld", &w);
        while (w) {
            ans += w % 10;
            fl |= !(w % 10);
            w /= 10;
        }
        ans += fl;
        printf("%lld\n", ans);
    }
	return 0;
}
```

---

## 作者：xiaoming007 (赞：1)

## 思路

既然要让猫猫所进行的操作次数最大，那么肯定将一个数变 $9$。

显然可以在一个数变成 $1$ 时进行恶作剧，此时可以让猫猫多操作 $8$ 次。

但是由于小老鼠可以在猫猫操作之前进行恶作剧，那么此时就可以在该数 $= 0$ 时变成 $1$，此时可以让猫猫多操作 $9$ 次。

最后输出原来总和加多操作的即可。

## 代码

```cpp
//Author: Saint_ying_xtf
//xiaoming007 = Saint_ying_xtf
#include <iostream>

using namespace std;
typedef long long ll;

int main(){
    ll T;
    scanf("%lld", &T);
    while(T--){
        ll n;
        scanf("%lld", &n);
        int cnt = 8;
        bool flag = false;
        while(n > 0){
            if(n % 10 == 0 && flag == false) cnt += 1, flag = true;
            cnt += n % 10;
            n /= 10;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
```

---

