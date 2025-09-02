# Removing Columns

## 题目描述

给你一个$n$*$m$的小写字符矩阵，你可以选择删除一些列，使得剩下的字符矩阵的每一行的字符串从上到下的字典序非减。

求最少删除多少列

## 样例 #1

### 输入

```
1 10
codeforces
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4 4
case
care
test
code
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 4
code
forc
esco
defo
rces
```

### 输出

```
4
```

# 题解

## 作者：lukelin (赞：2)

思路很简单，这一列主要是判断上一列排序相同的元素是否符合排列
注意开两个数组倒来倒去(可能我比较菜)

放个代码

```cpp
#include <string>
#include <cstdio>
#include <iostream>
#define ll long long

using namespace std;

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

string s[105];
int is_not_same[105];
int is_not_same2[105];

int main(){
    int n = read(), m = read();
    for (int i = 0; i < n; ++i)
        cin >> s[i];
    int cnt = 0;
    for (int i = 0; i < m; ++i){
        for (int j = 1; j < n; ++j)
            is_not_same2[j] = is_not_same[j];
        int j;
        for (j = 1; j < n; ++j){
            if (!is_not_same[j]){
                if (s[j - 1][i] > s[j][i]){
                    ++cnt;
                    break;
                }
                else if (s[j - 1][i] == s[j][i])
                    is_not_same2[j] = 0;
                else
                    is_not_same2[j] = 1;
            }
        }
        if (j == n){
            for (j = 1; j < n; ++j)
                is_not_same[j] = is_not_same2[j];
        }
    }
    printf("%d", cnt);
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

此题，说实话水也不是特别水，但也不是特别难。可能有些同学不知道C++中b>a这种，那么，我们就用数字来代替他！

这一题的思路是：首先先比前两个单词，一个一个比下去，如果前面一个大于后面一个，那么就break；否则，就删。一样就继续比。记住，删完之后要从第一个单词的第一个字母再比一次，放心，不会TLE的。

以下是用数字来实现大小比较的代码↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
int number[105][105],ans=0,n,m;
char c;
void clean(int g)
{
    for(int x=1;x<=n;x++)
        number[x][g]=-1;//将他变成-1，不再影响大小比较  
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            cin>>c;
            number[i][j]=c-'a';//变成数字
        }
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(number[i+1][j]>number[i][j])//后面一个单词比前面一个大
            break;
            else if(number[i+1][j]<number[i][j])
            {
                clean(j);
                ans++; 
                i=1;//重新开始比 
                j=1;
            }
        } 
    }
    cout<<ans;//输出变换的次数 
    return 0;
} 
```

当然，也可以直接用字母比较大小↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
char number[105][105];int ans=0,n,m;
void clean(int g)
{
    for(int x=1;x<=n;x++)
        number[x][g]=' ';//将他变成空格，不再影响大小比较  
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            cin>>number[i][j];
        }
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(number[i+1][j]>number[i][j])//后面一个单词比前面一个大
            break;
            else if(number[i+1][j]<number[i][j])
            {
                clean(j);
                ans++; 
                i=1;//重新开始比 
                j=1;
            }
        } 
    }
    cout<<ans;//输出变换的次数 
    return 0;
} 
```

---

## 作者：enyyyyyyy (赞：0)

- 思路：判断每一次的 $s_{j,i}$ 和 $s_{j-1,i}$ 的大小，去打标记，标记成立则把答案加一，循环后清空标记。

- 复杂度：$O(n^2)$。

- 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll n, m, ans, f[1005], vis;
char s[1005][1005];
int main() {
	n = read(), m = read();//读入
	for (ll i = 1; i <= n; i++)scanf("%s", s[i] + 1);//加一使字符串从1开始遍历
	for (ll i = 1; i <= m; i++) {
		for (ll j = 2; j <= n; j++) if (s[j][i] < s[j - 1][i] && !f[j]) vis = 1;//如果小于并且第一次，打上标记
		if (vis) ans++;//标记成立，答案加一
		else for (ll j = 2; j <= n; j++) if (s[j][i] > s[j - 1][i]) f[j] = 1;//如果大于，表示遍历过了
		vis = 0;//重中之重，清空
	}
	print(ans);//输出
	return 0;
}
```


---

