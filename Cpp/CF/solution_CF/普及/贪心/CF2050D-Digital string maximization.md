# Digital string maximization

## 题目描述

给你一个由 $0$ 至 $9$ 的数字组成的字符串 $s$ 。在一次运算中，您可以选取该字符串中除 $0$ 或最左边数字之外的任意数字，将其减少 $1$ ，然后将其与左边的数字对调。

例如，从字符串 $1023$ 中进行一次运算，可以得到 $1103$ 或 $1022$ 。

找出任意多次运算后所能得到的字典序最大的字符串。

## 样例 #1

### 输入

```
6
19
1709
11555
51476
9876543210
5891917899```

### 输出

```
81
6710
33311
55431
9876543210
7875567711```

# 题解

## 作者：Drifty (赞：5)

### Solution

如果说一个数往前换超过了 $9$ 那么这个数就会变成 $0$，一定劣。

那么我们对于每一个 $i$，往后枚举 $9$ 位，看哪个数换过来最大，如果相同取最左边的，就可以了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int T, n;
void solve() {
    string s; cin >> s;
    for (int i = 0; i < (int)s.size(); i ++) {
        int res = s[i], pos = i;
        for (int j = i + 1; j < min((int)s.size(), i + 11); j ++) 
            if ((int)s[j] - (j - i) > res) res = (int)s[j] - (j - i), pos = j;
        for (int j = pos; j > i; j --) swap(s[j], s[j - 1]), s[j - 1] --;
    }
    cout << s << '\n';
}
int main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    cin >> T;
    while (T --) solve();
    return 0;
}
```

---

## 作者：xuyifei0302 (赞：1)

# 大致题意
给定一个数字串，可以交换相邻两位，但原来靠右的需要 $-1$，随意操作最大化字符串代表的数字。
# 题目解法
要想让整个数最大，就要让高位上的数尽可能大。但是，若要把一个数向前交换 $x$ 个位置，这个数就要 $-x$, 由于每一位上的数都是 $\le 9$，所以我们就可以确定，对于每一个数，它最多往前移 $9$ 个格子。所以，对于每一位，我们考虑将它后面的 $9$ 个格子上的数移到这个位置上，取这个格子上的数和后面 $9$ 个格子上的数移到这个位置上的值取最大值。这步操作为常数级别，所以总复杂度为 $O(n)$。

下面是代码环节：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> s;
		int len = s.size();
		s = " " + s;
		for (int i = 1; i <= len; i ++) {
			int maxn = s[i] - '0', num = i;
			for (int j = 1; j <= 9 && i + j <= len; j ++) {
				if (maxn < s[i + j] - '0' - j) {
					maxn = s[i + j] - '0' - j;
					num = i + j;
				}
			}
			if (num == i) {
				continue;
			}
			for(int j = num; j > i; j --) {
				swap(s[j], s[j - 1]);
			}
			s[i] = maxn + '0'; 
		}
		for (int i = 1; i <= len; i ++) {
			cout << s[i];
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：yehongxin (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/CF2050D)
#### [原题传送门](https://codeforces.com/problemset/problem/2050/D)
## 题目大意
给出一串数字，可以交换相邻两个位置的数，使其变成交换后最大的数，再右边的数每向左交换就要 $-1$。
## 解题思路
这一题解决方法是贪心，当位置在 $i$ 时，就往后面枚举，找到换到左边最大的数即可，并且相邻的数需要相差 $2$ 及以上，否则交换完毕后会比原数小。如 $12$，交换完后为 $11$，比原数小。
## Ac Code


```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n;
string s;
int main(){
	cin>>T;//输入数字串的个数
	for(int i=1;i<=T;i++)
	{
		cin>>s;
		for (int i=1;i<s.size();i++)
		{
			if(s[i]=='0')continue;//当这一位数为0时，不交换
			int wz=i;//记录位置
			while(wz>=1&&s[wz]-s[wz-1]>=2)//当位置大于1时，且相邻得数相差2时
			{
				s[wz]--;//把这个位置的数减1
				swap(s[wz],s[wz-1]);//交换
				wz--; //位置减1，继续交换
			}
		}
		cout<<s<<endl;
	}
	return 0;
}
```

#### THE END

---

## 作者：HYdroKomide (赞：0)

### 题意：

给定一个数字串，可以交换相邻两位，但原来靠右的需要 $-1$，随意操作最大化字符串代表的数字。

### 思路：

显然一个字符向前交换的次数不会超过 $9$。对于一个位置，枚举其后十个值即可，所以复杂度非常的低。

对于一个位置，从后十个字符中找到交换到当前位置后答案最大的情况，并且实施操作即可。容易发现这样贪心一定是最优的。

### 程序如下：

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n;
char a[200005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",a+1);
		n=strlen(a+1);
		for(int i=1;i<=n;i++){
			int curmx=0,curpos=i;
			for(int j=i;j<=i+10&&j<=n;j++){
				if(a[j]-'0'-(j-i)>curmx){
					curmx=a[j]-'0'-(j-i);
					curpos=j;
				}
			}
			for(int j=curpos;j>i;j--){
				swap(a[j],a[j-1]);
				a[j-1]--;
			}
		}
		for(int i=1;i<=n;i++)printf("%c",a[i]);
		puts("");
	}
	return 0;
}
```

### THE END

---

## 作者：The_foolishest_OIer (赞：0)

贪心。

模拟样例可以发现，如果对右边的两个数字进行操作之后比原来的情况更优，就直接交换，如数字 $58$，操作之后可得数字 $75$，$75 > 58$，所以就直接交换。

但是注意一点，并不是右边的数字比左边的数字大就可以进行操作，比如数字 $67$，操作之后可得数字 $66$，而 $66 < 67$。

归纳可得，当右边的数字比左边的数字大 $2$ 及以上时，可以进行操作。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T,n;
string s;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> s;
	n = s.length();
	for (int i = 1 ; i < n ; i++){
		if (s[i] == '0') continue;
		int pos = i; // 第几位
		while (pos >= 1 && s[pos] - s[pos - 1] >= 2){ // 不是最左边的数并且右边的数字比左边的数字大 2 及以上
			s[pos]--;
			swap(s[pos],s[pos - 1]);
			pos--; // 进行操作
		}
	}
	cout << s << endl;
}
signed main(){
	close();
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

