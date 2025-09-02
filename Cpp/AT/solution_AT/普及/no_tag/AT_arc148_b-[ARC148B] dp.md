# [ARC148B] dp

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc148/tasks/arc148_b

`d` と `p` からなる長さ $ L $ の文字列 $ T $ に対して、$ T $ を $ 180 $ 度回転した文字列を $ f(T) $ と表します。より厳密には、$ f(T) $ を次の条件を満たす文字列として定めます。

- $ f(T) $ は `d` と `p` からなる長さ $ L $ の文字列である。
- $ 1\ \leq\ i\ \leq\ L $ であるすべての整数 $ i $ について、$ f(T) $ の $ i $ 文字目は $ T $ の $ L\ +\ 1\ -\ i $ 文字目と異なる。

例えば $ T\ = $ `ddddd` のとき $ f(T)\ = $ `ppppp`, $ T\ = $ `dpdppp` のとき $ f(T)= $ `dddpdp` です。

`d` と `p` からなる長さ $ N $ の文字列 $ S $ が与えられます。  
 あなたは次の操作を **$ 0 $ 回以上 $ 1 $ 回以下**行うことができます。

- $ 1\ \leq\ L\ \leq\ R\ \leq\ N $ である整数の組 $ (L,\ R) $ を $ 1 $ つ選び、$ S $ の $ L $ 文字目から $ R $ 文字目までからなる部分文字列を $ T $ とする。そして、$ S $ の $ L $ 文字目から $ R $ 文字目までを $ f(T) $ に置き換える。

例えば $ S= $ `dpdpp`, $ (L,R)=(2,4) $ の場合、$ T= $ `pdp`, $ f(T)= $ `dpd` なので $ S $ は `ddpdp` に変化します。

最終的な $ S $ としてあり得る文字列のうち辞書順最小のものを出力してください。

  辞書順とは？文字列 $ S\ =\ S_1S_2\ldots\ S_{|S|} $ が文字列 $ T\ =\ T_1T_2\ldots\ T_{|T|} $ より**辞書順で小さい**とは、下記の 1. と 2. のどちらかが成り立つことを言います。 ここで、$ |S|,\ |T| $ はそれぞれ $ S,\ T $ の長さを表します。

1. $ |S|\ \lt\ |T| $ かつ $ S_1S_2\ldots\ S_{|S|}\ =\ T_1T_2\ldots\ T_{|S|} $。
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |S|,\ |T|\ \rbrace $ が存在して、下記の $ 2 $ つがともに成り立つ。 
  - $ S_1S_2\ldots\ S_{i-1}\ =\ T_1T_2\ldots\ T_{i-1} $
  - $ S_i $ が $ T_i $ よりアルファベット順で小さい文字である。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5000 $
- $ S $ は `d` と `p` からなる長さ $ N $ の文字列
- $ N $ は整数

### Sample Explanation 1

$ (L,\ R)\ =\ (2,\ 5) $ とします。$ T\ = $ `pdpp`, $ f(T)\ = $ `ddpd` なので、操作後の $ S $ は `dddpdd` になります。 得られる文字列のうち `dddpdd` が辞書順最小なので、これを出力します。

### Sample Explanation 2

操作を行わないことが最適な場合もあります。

## 样例 #1

### 输入

```
6
dpdppd```

### 输出

```
dddpdd```

## 样例 #2

### 输入

```
3
ddd```

### 输出

```
ddd```

## 样例 #3

### 输入

```
11
ddpdpdppddp```

### 输出

```
ddddpdpdddp```

# 题解

## 作者：CaiZi (赞：1)

## [ARC148B] dp 题解
**[题目链接](https://www.luogu.com.cn/problem/AT_arc148_b)**
### 题目分析
这个操作其实就是将字符串翻转，然后把所有 `d` 换成 `p`，把所有 `p` 换成 `d`。

首先有一个简单的 $O(n^3)$ 暴力，枚举操作时左右端点，然后进行 $O(n)$ 的操作即可。

看到字典序就应该想到贪心。

由于我们要让 $S$ 字典序最小，我们应该把第一个 `p` 变为 `d`，于是我们现在确定了左端点，仅需要枚举右端点并进行操作。时间复杂度 $O(n^2)$。
### 代码展示
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m=-1;
string a,b,c;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>a;
	for(int i=0;i<=n-1;i++){
		if(a[i]=='p'){
			m=i;
			break;
		}
	}
	if(m==-1){
		cout<<a;
	}
	else{
		c.push_back('z');
		for(int i=m;i<=n-1;i++){
			b=a;
			for(int j=m;j<=i;j++){
				if(b[j]=='d'){
					b[j]='p';
				}
				else{
					b[j]='d';
				}
			}
			for(int j=m;2*j<=i+m;j++){
				swap(b[j],b[i-j+m]);
			}
			c=min(c,b);
		}
	}
	cout<<c;
	return 0;
}
```
**[提交记录](https://www.luogu.com.cn/record/163688632)**

---

## 作者：__Creeper__ (赞：1)

### 题意

给你一个字符串，让你进行 $0$ 或 $1$ 次操作后，求字典序最小字符串。选择一个 $[l,r]$ 的区间，让字符 $d$ 变成 $p$，$p$ 变成 $d$，再把它反过来即可。

### 思路

因为要使字典序最小，所以第一个 $p$ 一定要变成 $d$，枚举右端点再进行判断即可，因为 $n \le 5000$ 所以时间复杂度 $O(n^2)$ 可以通过。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() 
{
	int n, l;
	string a, ans;
	cin >> n >> a;
	ans = a;	
	for ( int i = 0; i < n; i++ ) 
	{
		if ( a[i] == 'p' ) // 找到第一个'p'的位置，也就是操作区间的左端点
		{
			l = i;
			break;
		}
	}
	if ( l == -2e9 ) // 没有找到直接输出原字符串
	{
		cout << a;
	}
	else 
	{
		string s;
		for ( int r = l; r < n; r++ ) 
		{
			s = a;
			for ( int i = l; i <= r; i++ ) // 对称
			{
				if ( s[i] == 'd' )
				{
					s[i] = 'p';
				}
				else
				{
					s[i] = 'd';
				}
			}
			for ( int i = l, j = r; i <= j; i++, j-- ) 
			{
				swap ( s[i], s[j] );
			}		
			ans = min ( ans, s );
		}
		cout << ans;
	}
	return 0;
}
```

---

## 作者：Mierstan085 (赞：1)

# 解法

既然字典序需要最小，那么不难发现要尽可能的让开头的字符为 `d`。

那么我们可以直接暴力，令左端点为下标最小的 `p` 的位置，然后枚举右端点，每一次 check 即可。

# 代码

发现第一篇题解的马蜂简直跟我的一模一样啊，思路也很像。

```cpp
// Problem: [ARC148B] dp
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc148_b
// Memory Limit: 1 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string a, minn;
    cin >> n >> a;
    minn = a;

    int l = INT_MIN; // 其实设 -1 也可以，设一个 < 0 的小值。
    for (int i = 0; i < n; i++) {
        if (a[i] == 'p') {
            l = i;
            break;
        }
    }

    if (l == INT_MIN)
        cout << a;
    else {
        string s;
        for (int r = l; r < n; r++) {
            s = a;
            for (int i = l; i <= r; i++) {
                if (s[i] == 'd')
                    s[i] = 'p';
                else
                    s[i] = 'd';
            }

            for (int i = l, j = r; i <= j; i++, j--) {
                swap(s[i], s[j]);
            }

            minn = min(minn, s);
        }

        cout << minn;
    }
}

```

---

## 作者：Merge_all (赞：1)

### 题意：
给定一个字符串，对于某一个区间的每一位重新赋值，使得其对称（**只有一次机会**）。输出**字典序最小的答案**。
### 思路
找到**第一个** $\texttt p$，并将它改成 $ \texttt d$，最后枚举右端点暴力判断即可。
### 时间复杂度：
第一层循环枚举第一个 $ \texttt p$ 的下标到 $n$，第二层循环进行对称，时间复杂度：$O(n^2)$。

### 代码：

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int r[1000005], n, L;
string s, tmp, ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> s;
	tmp = s, ans = s;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'p') {
			L = i;
			break;
		}
	}
	for (int R = L; R < n; R++) {
		s = tmp;
		int l = L, r = R;
		for (int j = l, k = r; j <= r; j++, k--) {
			if (tmp[k] == 'd')
				s[j] = 'p';
			else
				s[j] = 'd';
		}
		ans = min(ans, s);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：zcr0202 (赞：1)

## 题目大意

给你一个字符串，让你进行 $0$ 或 $1$ 次操作后，求字典序最小字符串。

操作：选择一个 $[l,r]$ 的区间，让字符 $d$ 变成 $p$，$p$ 变成 $d$，再把它反过来即可。

## 解题思路

首先，为了满足字典序最小，左端点必须是整个字符串中从左往右数的第一个字符为 $p$ 的坐标，这可以简单证明一下。然后枚举右端点，求出进行一次操作后字典序最小的字符串即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, l = -1;
string a, s, minn;
int main() {
	cin >> n;
	cin >> a;
	minn = a;
	for(int i = 0; i < n; i++) {
		if(a[i] == 'p') {
			l = i;
			break;
		}
	}
	if(l == -1) {
		cout << a;
		return 0;
	}
	else {
		for(int r = l; r < n; r++) {
			s = a;
			for(int i = l; i <= r; i++) {
				if(s[i] == 'd') s[i] = 'p';
				else s[i] = 'd';
			}
			for(int i = l, j = r; i <= j; i++, j--) {
				swap(s[i], s[j]);
			}
			if(s < minn) {
				minn = s;
			}
		}
		cout << minn;
		return 0;
	}
}
```

---

## 作者：__ikun__horro__ (赞：1)

题目要求字典序最小，而且只有 d 和 p 两种字母。所以我们要让在前面的 p 变成 d，可以先找到第一个 p 作为左端点，想让它变成 d，就要找到后面的一个 p 作为右端点，然后暴力枚举就可以了。时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, l, r;
string s, t, ans;
int main() {
	cin >> n >> s;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'p') {     //找到第一个p作为左端点
			l = i;
			break;
		}
	}
	ans = s;     //记录答案
	for (r = l; r < n; r++) {     //枚举右端点
		if (s[r] == 'd') continue;
		t = s;     //计算重新赋值后的结果
		for (int i = l; i <= r; i++) {
			if (s[i] == s[r + l - i]) {
				t[i] = (t[i] == 'd' ? 'p' : 'd');     //对字符取反
			}
		}
		ans = min(ans, t);     //更新答案
	}
	cout << ans;
	return 0;
}
```

---

## 作者：jijidawang (赞：1)

数据范围就是明示平方复杂度 .

首先根据字典序定义左端点必然是最左的 $\tt p$，这样翻转过去之后如果右边有 $\tt p$ 这个就可以变成 $\tt d$，否则必然不优 .

于是枚举右端点暴力判即可，时间复杂度 $\Theta(n^2\log n)$，用基数排序可以优化到 $\Theta(n^2)$ .

*不要尝试线性找右端点，会变得不幸*

```cpp
int n;
string s;
int main()
{
	scanf("%d", &n);
	cin >> s; s = "$" + s;
	int l = -1;
	for (int i=1; i<=n; i++)
		if (s[i] == 'p'){l = i; break;}
	if (!~l){cout << s.substr(1) << endl; return 0;}
	set<string> S;
	for (int r=l; r<=n; r++)
	{
		string now(s);
		reverse(now.begin()+l, now.begin()+1+r);
		for (int i=l; i<=r; i++) now[i] = (now[i] == 'd') ? 'p' : 'd';
		S.insert(now);
	}
	cout << S.begin() -> substr(1) << endl;
	return 0;
}

```

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/AT_arc148_b)

## 题意

给定一个字符串，对于某一个区间的每一位重新赋值，使得其对称，**仅一次机会**。输出字典序最小的答案。

## 思路

由题意可知，第一个 p 需改成 d，然后枚举右端点暴力判断即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,k,t,w,l,r;
string a,s,ans;
int main(){
    cin>>n>>s;
    for(i=0;i<n;i++)
        if(s[i]=='p'){
            k=i;//找操作区间左端点
            break;
        }
    a=ans=s;
    for(i=k;i<n;i++){//枚举右端点
        s=a;
        t=k;w=i;
        l=t;r=w;
        while(l<=w){
            if(a[r]=='d') s[l]='p';
            else s[l]='d';
            l++;r--;
        }
        ans=min(ans,s);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## 思路
考虑贪心，遇到的第一个 $p$ 为 $l$，然后暴力枚举 $r$ 找答案即可。

时间复杂度 $O(N^2)$。
## Code
```cpp

#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
string s,bk,ret;
int l;
int r[1000005],tot;

signed main(){
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='d'){
			continue;
		}
		else{
			l=i;
			break;
		}
	}
	bk=s;
	ret=s;
	for(int i=l;i<n;i++){
		s=bk;
		int L=l,R=i;
		for(int j=L,k=R;j<=R;j++,k--){
			if(bk[k]=='d'){
				s[j]='p';
			}
			else{
				s[j]='d';
			}
		}
		if(s<ret){
			ret=s;
		}
	}
	cout<<ret<<'\n';
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 思路

因为只有一次机会，所以第一个 `p` 一定要改成 `d`，然后枚举右端点再暴力翻转求最小字典序即可，时间复杂度为 $O(n^2)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int r[1000005];
int main()
{
	int n,l;
	string s,ss,ans;
	cin>>n>>s;
	for(int i=0;i<n;i++)//找出第一个p，作为left 
	{
		if(s[i]=='p')
		{
			l=i;
			break;
		}
	}
	ss=s;//备份一个s
	ans=s;//字典序最小的答案
	for(int i=l;i<n;i++)
	{
		s=ss;
		int ll=l,rr=i;//双指针枚举右端点再暴力翻转求最小字典序
		for(int j=ll,k=rr;j<=rr;j++,k--)
		{
			if(ss[k]=='d') s[j]='p';
			else s[j]='d';
		}
		if(s<ans) ans=s;
	}
	cout<<ans;
	return 0;
}

```


---

