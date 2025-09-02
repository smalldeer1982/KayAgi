# osu!mania

## 题目描述

你正在玩你最喜欢的节奏游戏 osu!mania。你的谱面布局由 $n$ 行 $4$ 列组成。由于底部的音符距离你更近，你将首先处理最底部的那一行，最后处理最顶部的那一行。每一行恰好包含一个音符，用 '#' 表示。

对于每一个音符 $1, 2, \dots, n$，按照处理顺序，输出该音符所在的列编号。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
4
#...
.#..
..#.
...#
2
.#..
.#..
1
...#```

### 输出

```
4 3 2 1 
2 2 
4```

# 题解

## 作者：ybc2026lhy (赞：1)

[博客食用效果更佳](https://www.luogu.com.cn/article/rx6r8l0t)

##### 分析：
这道题只需要根据题意寻找即可。我是在输入时就寻找每一行的 \# 号，然后再用一个数组把答案存储下来，再统一输出。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	cin>>T;
	while(T--){
		int n,ans[505];
		char s[505][10];
		cin>>n;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=4;j++){
				cin>>s[i][j];
				if(s[i][j]=='#'){//边输入边寻找
					ans[i]=j;//存储位置
				}
			}
		}
		for(int i=n;i>=1;i--){
			cout<<ans[i]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

[AC记录](https://codeforces.com/submissions/cqbzlhy)

---

## 作者：cqbzrjx (赞：1)

[原题传送门](https://codeforces.com/problemset/problem/2009/B)

## 分析

~~一眼模拟题~~，开个数组 $res_i$ 表示当前 $i$ 行音符所在的列数。当 $c_{i,j}$ 为 ```#``` 时，直接记录即可。最后再倒序输出。

时间复杂度：$O(n ^ 2 \times t)$。

## Code

```cpp
/*
Codeforces CF2009B osu!mania  
*/
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a;i <= b;i++)
#define per(i,a,b) for(int i = a;i >= b;i--)
#define pb push_back
#define PII pair<int,int>
using namespace std;
typedef long long ll;
const int maxn = 5005;
int t,n;
int res[maxn];//存储包含应符的地址
char c[maxn][maxn];
inline void solve()
{
	cin>>n;
	memset(res,0,sizeof res);//多测不清空
	rep(i,1,n)
	{
		rep(j,1,4)
		{
			cin>>c[i][j];
			if(c[i][j] == '#') res[i] = j;//看题
		}
	}
	per(i,n,1)//题目要求从下往上
	{
		cout<<res[i]<<" ";
	}
	cout<<"\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

[AC submissions](https://codeforces.com/contest/2009/submission/279794156)

---

## 作者：RoamingDuck (赞：0)

### 题目传送门
[洛谷](https://www.luogu.com.cn/problem/CF2009B)

[原题](http://codeforces.com/problemset/problem/2009/B)

### 思路
考虑每读入一行进行遍历，记录答案到数组里，记录 $res_i$ 为第 $i$ 个音符出现的列数。

因为题目说明要从底部处理音符，所以得到的 $res$ 数组翻转一下就是要得到的答案。


```cpp
#include <iostream>
#include <string>
#include <vector>
#define ll long long
using namespace std;

ll t;

ll n;
string str;

ll res[501];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    while (t--)
    {
        cin >> n;

        for (ll i = 1; i <= n; i++)
        {
            cin >> str;

            for (ll j = 0; str[j]; j++)
                if (str[j] == '#')
                    res[i] = j + 1; // 记录列数
        }

        for (ll i = n; i >= 1; i--) // 翻转输出
            cout << res[i] << ' ';

        cout << '\n';
    }
    return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目大意

给你一个 $4$ 列，$n$ 行的矩阵。

求每一行 `#` 的位置，倒序输出。

## 题目分析

考虑每行读入，通过枚举寻找答案。

存入数组后，倒序输出。

---

## 作者：Lfz312g (赞：0)

# CF2009B osu!mania
## 题目分析
找出每一行的 ```#```，倒序输出即可。  
这里使用 ```stack``` 先进后出的特性实现。

```cpp
#include <iostream>
#include <stack>
using namespace std;
void solve()
{
	int n;
	cin>>n;
	stack<int> s;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=4;j++)
		{
			char x;
			cin>>x;
			if (x=='#') s.push(j);
		}
	}
	while (!s.empty())
	{
		cout<<s.top()<<' ';
		s.pop();
	}
	putchar('\n');
}
int main()
{
	int t;
	cin>>t;
	while (t--) solve();
}
```

---

## 作者：cly312 (赞：0)

每次读入一个字符串，枚举哪一个位置出现了 `#`，倒序存入答案数组，然后正序输出即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> result(n);
		for (int i = 0; i < n; ++i) {
			string row;
			cin >> row;
			for (int j = 0; j < 4; ++j) {
				if (row[j] == '#') {
					result[n - i - 1] = j + 1;
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			cout << result[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
```

---

