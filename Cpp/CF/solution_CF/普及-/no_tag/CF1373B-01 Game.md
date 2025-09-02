# 01 Game

## 题目描述

**题目大意**

`Alice`和`Bob`在玩游戏。

初始有一个仅由`01`构成的字符串。`Alice`和`Bob`轮流进行游戏，`Alice`先行。轮到某个人的时候，他需要从原串中找到并删除两个相邻且不同的字符（`01`或`10`），无法操作者输。

两人都用最优的策略进行，你需要确定谁能够赢得游戏。

## 样例 #1

### 输入

```
3
01
1111
0011```

### 输出

```
DA
NET
NET```

# 题解

## 作者：听取MLE声一片 (赞：3)

~~水题一道~~。

本题思路：贪心。

贪心策略：分别求字符串中的0,1个数，算01个数的最小值，将最小值对2取模，余数为0输出“NET”，否则输“DA”。

算法讲解：无论原字符串的字母如何排列，总会有一组01是靠在一起的，将它们删除后，如果01个数都不为0，那么就会出现新的两个数并在一起，以此类推，直到01中有一个个数归零。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
string a; 
int main()
{
	cin>>n;
	while(n--){
		cin>>a;
		int ans1=0,ans2=0,ans;
		for(int i=0;i<a.length();i++){
			if(a[i]=='0')
				ans1++;
			else ans2++;
		}
		ans=min(ans1,ans2);
		if(ans%2==0)
			cout<<"NET\n";
		else cout<<"DA\n";
	}
	return 0;
}

```

---

## 作者：AgrumeStly (赞：1)

这题好水，就是简单的模拟+字符串。

### $\sf Translation$

给定一个 $01$ 串，如果 $0$ 出现的次数和 $1$ 出现的次数的最小值是奇数，输出 `DA` ，否则输出 `NET`

多测。

### $\sf Solution$

#### 法一

简单模拟+字符串，如果你是刚刚学字符串的萌新，推荐先看看 [这题](https://www.luogu.com.cn/problem/P5015)，这两题类似，都是统计一个字符串里面的字符的情况。

那么我们可以定义两个变量分别存储 $0$ 的出现次数和 $1$ 的出现次数。

#### $\sf Code$

```cpp
/*
  Problem:CF1373B
  Date:28/06/20 21:29
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#define line cout << endl
using namespace std;
int t;
int main () {
	cin >> t;
	int _1, _0;
	while (t--) {
		string s;
		cin >> s;
		int len = s.length();
		for (int i = 0; i < len; i++) {
			if (s[i] == '1') _1++;//如果当前字符是1 
			else _0++;
		}
		cout << (min (_1, _0) % 2 == 0 ? "NET" : "DA") << endl;//取最小值/判断奇偶/输出 
		_1 = 0, _0 = 0;//清零 
	}
	return 0;
}
```

#### 法二

利用 c++ 的 STL 中的 `count` 函数。

`count` 的用法：

`count` 共有 3 个参数：

`count(begin, end, c);`

其中 begin 代表字符串的起始位置，end 代表终止位置，c 代表要统计的字符。

那在这道题里面，我们就可以用 `count` 函数统计 $0$ 和 $1$ 的个数。

#### $\sf Code$

```cpp
/*
  Problem:CF1373B
  Date:28/06/20 21:29
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#define line cout << endl
using namespace std;
int t;
int main () {
	cin >> t;
	int _1, _0;
	while (t--) {
		string s;
		cin >> s;
		cout << (min (count (s.begin (), s.end (), '0'), count (s.begin (), s.end (), '1')) % 2 == 0 ? "NET" : "DA") << endl;//统计/取最小值/判断奇偶/输出 
	}
	return 0;
}
```

---

## 作者：b6e0_ (赞：1)

[CF题面传送门](https://codeforces.com/contest/1373/problem/B) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1373B) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1373B)

赛后发现赛时做复杂了。

## 赛时做法：栈

由于erase函数会出现一些bug（不好写），所以就用栈来模拟删除的过程了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		int i,tot=0;
		cin>>s;
		stack<int>st;
		for(i=0;i<s.size();i++)
			if(s[i]=='0')
				if(st.size()&&st.top())//如果能删
				{
					st.pop();//就删
					tot++;
				}
				else
					st.push(0);//否则压栈
			else
				if(st.size()&&!st.top())//如果能删
				{
					st.pop();//就删
					tot++;
				}
				else
					st.push(1);//否则压栈
		if(tot&1)//判断奇偶
			cout<<"DA\n";
		else
			cout<<"NET\n";
	}
	return 0;
}
```
## 赛后做法：统计

$0$和$1$中少的一方一定能被删除。反证法：如果少的一方（假设为$1$）最后剩下了一些字符没能被删去，那么字符串就形如$00\cdots11\cdots00\cdots$，这样开头的$0$或结尾的$0$和中间的$1$就能组队删去。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		int i,tot0=0,tot1=0;
		cin>>s;
		for(i=0;i<s.size();i++)
			if(s[i]=='0')
				tot0++;
			else
				tot1++;
		if(min(tot0,tot1)&1)//取小，判断奇偶
			cout<<"DA\n";
		else
			cout<<"NET\n";
	}
	return 0;
}
```
两种做法时间复杂度都为$O(t|s|)$。

---

## 作者：cyh_toby (赞：1)

# 题意
原题：[CF1373B 【01 Game】](https://www.luogu.com.cn/problem/CF1373B)

不加赘述

# 分析

容易发现，只要串里面存在至少一 $0$ 和至少一个 $1$ 就一定能操作。因此最终只会有三种局面
- 只剩 $1$
- 只剩 $0$
- 没有剩下

又由于每次需要删去一个 $0$ 和一个 $1$ ，因此操作次数共为 $cnt = \min(cnt_0\,,\,cnt_1)$

那么判断 $cnt$ 的奇偶即可得出答案。

# 源码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 105;

char s[N];
int n, cnt1, cnt0;

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		cnt1 = cnt0 = 0;
		
		scanf("%s", s+1);
		n = strlen(s+1);
		for (int i = 1; i <= n; i++) {
			if (s[i] == '1')
				cnt1++;
			else
				cnt0++;
		}
		
		int cnt = min(cnt1, cnt0);
		if (cnt % 2 == 0) 
			puts("NET");
		else
			puts("DA");
	}
	return 0;
}
```

---

## 作者：xgwpp6710 (赞：0)

首先，只要`0`和`1`都还有，就取得下去。

因此只需要看`0`和`1`中较少的数数量奇偶性。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,cnt,c[2];
	string s;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>s;
		c[1]=c[0]=0;
		for(int j=0;j<=s.size()-1;j++) c[s[j]-48]++;//统计
		cnt=min(c[0],c[1]);
		cout<<(cnt%2?"DA\n":"NET\n");//三目，相当于if else
	}
	return 0;
}
```

---

## 作者：45dinо (赞：0)

~~切CF，学俄语~~

这里介绍一个数学做法。

由题意得，每一次必然会消去一个 $1$ 和一个 $0$ ，当且仅当 $1$ 或 $0$ 的个数等于 $0$ 时，无法操作。

所以操作的轮数等于 $1$ 和 $0$ 的最小值。

所以把 $s$ 的 $1$ 和 $0$ 的个数统计出来，如果是偶数就输出 ```NET``` （网？），否则输出 ```DA```（HP某组织？）。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,num1,num0,minn;
string s;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s);
		num1=num0=0;
		for(int i=0;i<s.size();i++)
			if(s[i]=='1')
				num1++;
			else
				num0++;
		minn=min(num1,num0);
		if(minn%2)
			puts("DA");
		else
			puts("NET");
	}
	return 0;
}
```


---

## 作者：SpeedStar (赞：0)

#### 算法分析

对于本题中的01串可操作次数为00和11中出现次数的最小值，如果这个数是奇数，那么$Alice$将会赢得游戏，否则将会输掉游戏。

#### C++代码

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		string s;
		cin >> s;
		cout << (min(count(s.begin(), s.end(), '0'), count(s.begin(), s.end(), '1')) % 2 == 1 ? "DA\n" : "NET\n");
	}
	
	return 0;
}
```


---

## 作者：_jimmywang_ (赞：0)

我们发现，每一次操作，都会少一个0和1。你减着减着，最后要么就没数了， 要么是只剩一个多一点的数。

 所以其实操作次数就是少一点的那个数了。。。
 
 $code:$
 
 ```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll t;
int main(){
	t=d;
	while(t--){
		ll a=0,b=0;
		string s;
		cin>>s;
		f(i,0,s.size()-1){if(s[i]=='1')a++;else b++;}
		if(min(a,b)%2)cout<<"DA\n";
		else cout<<"NET\n";
	}
	return 0;
}
```


---

## 作者：159号程序员 (赞：0)

这道题难度偏高，反正我调了好几次。

题目大意：

有一个 $01$ 字符串 $a$，你要求出 $a$ 里面 $0$ 的个数和 $1$ 的个数，之后取最小的数，如果为奇数，输出 `DA`，否则输出 `NET`。

我们可以建立两个变量：$x$ 和 $y$，来存储 $1$ 的个数和 $0$ 的个数，最后再取最小值判断奇偶数即可。

_AC Code_

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T, x = 0, y = 0, ans;
    cin >> T;
    while(T--) //有 T 组数据。
    {
        string a;
        cin >> a; //输入 01 字符串。
        x = y = 0;
        for(int i = 0; i < a.length(); i++) //循环遍历字符串。
        {
            if(a[i] == '1') //1的数量+1
            {
                x++;
            }
            else //除了1，就是0，所以可以不判断，给0的数量+1。
            {
                y++;
            }
        }
        ans = min(x, y) % 2; //	利用 min() 函数找到最小值，并且对2取余。
        if(ans) //如果为奇数，输出 DA。
        {
            cout << "DA" << endl;
        }
        else //否则，输出 NET
        {
            cout << "NET" << endl;
        }
    }
    return 0;
}
```

---

