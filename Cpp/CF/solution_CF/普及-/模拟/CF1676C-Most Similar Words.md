# Most Similar Words

## 题目描述

You are given $ n $ words of equal length $ m $ , consisting of lowercase Latin alphabet letters. The $ i $ -th word is denoted $ s_i $ .

In one move you can choose any position in any single word and change the letter at that position to the previous or next letter in alphabetical order. For example:

- you can change 'e' to 'd' or to 'f';
- 'a' can only be changed to 'b';
- 'z' can only be changed to 'y'.

The difference between two words is the minimum number of moves required to make them equal. For example, the difference between "best" and "cost" is $ 1 + 10 + 0 + 0 = 11 $ .

Find the minimum difference of $ s_i $ and $ s_j $ such that $ (i < j) $ . In other words, find the minimum difference over all possible pairs of the $ n $ words.

## 说明/提示

For the second test case, one can show that the best pair is ("abb","bef"), which has difference equal to $ 8 $ , which can be obtained in the following way: change the first character of the first string to 'b' in one move, change the second character of the second string to 'b' in $ 3 $ moves and change the third character of the second string to 'b' in $ 4 $ moves, thus making in total $ 1 + 3 + 4 = 8 $ moves.

For the third test case, there is only one possible pair and it can be shown that the minimum amount of moves necessary to make the strings equal is $ 35 $ .

For the fourth test case, there is a pair of strings which is already equal, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
6
2 4
best
cost
6 3
abb
zba
bef
cdu
ooo
zzz
2 7
aaabbbc
bbaezfe
3 2
ab
ab
ab
2 8
aaaaaaaa
zzzzzzzz
3 1
a
u
y```

### 输出

```
11
8
35
0
200
4```

# 题解

## 作者：Engulf (赞：2)

$n$ 非常小，可以直接暴力枚举每两组字符串，取最小值即可。

```cpp
// author: TMJYH09
// create time: 2022/05/10 22:53:38
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int calc(string a,string b){
    int ans=0;
    for(int i=0;i<a.size();i++){
        int cost=min(abs(a[i]-b[i]),abs(a[i]-b[i])+26);
        ans+=cost;
    }
    return ans;
}

void solve(){
    int n,m;
    cin>>n>>m;
    vector <string> a(n);
    for(auto &i:a)cin>>i;
    int ans=0x3f3f3f3f;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            ans=min(ans,calc(a[i],a[j]));
        }
    }
    cout<<ans<<endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int _;cin>>_;while(_--)solve();
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

# 题意
定义长度为 $n$ 的字符串 $a,b$ 的差异度为 $\sum\limits_{i=1}^n|a_i-b_i|$，

$|a_i-b_i|$ 表示 $a_i$ 与 $b_i$ 在字母表上的距离，

给你 $n$ 个字符串，让你找一对字符串 $a,b$ 使得它们的差异度最小，输出这个最小值。
# 思路
观察到 $n$ 很小，我们可以 $O(n^2)$ 枚举每一对字符串，

对每一对字符串计算差异度，总复杂度 $O(n^2m)$，可以接受。
# 代码
```cpp
#include <cstdio>
#include <cstring>
int f(int x) {return x >= 0 ? x : -x;}
int T, n, m, q;char s[150][15];
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);q = 1e9;
        for(int i = 1;i <= n;++i) scanf("%s", s[i]);
        for(int i = 1, t;i <= n;++i)
            for(int j = i + 1;j <= n;++j)
            {
                t = 0;
                for(int k = 0;k < m;++k)
                    t += f(s[i][k] - s[j][k]);
                if(t < q) q = t;
            }
        printf("%d\n", q);
    }
    return 0;
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

这里先讲讲，对于每对字符串，如何求出最小操作次数。

其实也不难，对于每对字符，求出两个字符的 ASCII 值之差，即为这两个字符的最小操作次数；而这些最小操作次数之和，就是字符串的最小操作次数。

那就简单多了。鉴于数据范围很小，可以用暴力解法。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t;
int n,m;
char s[55][10];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s[i]+1);
		}
		int ans=0x3fffffff;
		for(int i=1;i<n;i++)//计算一对字符串的最小操作次数
		{
			for(int j=i+1;j<=n;j++)
			{
				int temp=0;
				for(int k=1;k<=m;k++)
				{
					temp+=abs(s[i][k]-s[j][k]);//计算字符之间的最小操作次数
				}
				ans=min(ans,temp);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：OLE_OIer (赞：0)

这道题是一道基本的字符串处理题。

题意如下：现在有 $n$ 个字符串，我们要获取它们之间差别指数的最小值。

两个字符串之间的差别指数是它们对应字符差值的绝对值之和，于是就可以直接模拟求解。

最小值怎么获取呢？当然可以用打擂台的方法来实现了。

代码附上：
```cpp
//CF1676C Most Similar Words
#include<bits/stdc++.h>
#define int long long
#define elif else if
using namespace std;
int dif(string a,string b){//获取两个字符串之间差别指数的函数
	int len=a.length(),tot=0;//len存储字符串长度，tot存储两个字符串之间的差别指数。
	for(int i=0;i<len;++i) tot+=abs(a[i]-b[i]);//累加获取差别指数。
	return tot;
}
void func(){
	int n,len,minn=1e9;//minn存储差别指数的最小值。
	cin>>n>>len;
	string s[60];
	for(int i=1;i<=n;++i) cin>>s[i];
	for(int i=1;i<=n;++i){
		for(int j=1;j<i;++j) minn=min(minn,dif(s[i],s[j]));//打擂台获取最小值。
	}
	cout<<minn<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=1;i<=n;++i) func();
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

**Solution**

简单题。

由于数据范围很小，所以我们可以直接暴力枚举任意两个字符串，然后暴力求这两个字符串中的两个字符需要多少次操作可以相等，求最小值即可。

时间复杂度 $\mathcal O(T\cdot r^2\cdot c)$。

坑：不能枚举两个相同的字符串！

**AC Code**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

int f[200010][2];

string s[1000010];

int bq(int a) {
    return a > 0 ? a : -a;
}

signed main() {
    int T;
    cin >> T;
    while (T --) {
        int r, c, mi = 0x3f3f3f3f;
        cin >> r >> c;
        for (int i = 1; i <= r; i ++) cin >> s[i];
        for (int i = 1; i <= r; i ++)
            for (int j = i + 1; j <= r; j ++) {
                int ans = 0;
                for (int k = 0; k < c; k ++) {
                    ans += bq(s[i][k] - s[j][k]);
                }
                mi = min(mi, ans);
            }
        cout << mi << '\n';
    }
    return 0;
}

```


---

