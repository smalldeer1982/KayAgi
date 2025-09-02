# Replace Character

## 题目描述

给定一个长度为 $n$ 的字符串 $s$，只包含小写英文字母。

你只能进行一次如下操作：

- 选择任意两个下标 $i$ 和 $j$ ($1\le i,j\le n$)，允许选择 $i=j$。
- 将 $s_i$ 赋值为 $s_j$。

你需要最小化 $s$ 不同排列的个数。输出在一次操作后满足条件的任何一个字符串 $s$。

字符串的一个排列是打乱其字符顺序后形成的新字符串。比如 `bac` 是 `abc` 的一个排列，而 `bcc` 不是。

## 样例 #1

### 输入

```
6
3
abc
4
xyyx
8
alphabet
1
k
10
aabbccddee
6
ttbddq```

### 输出

```
cbc
yyyx
alphaaet
k
eabbccddee
tttddq```

# 题解

## 作者：封禁用户 (赞：3)

## 题解：CF2047B Replace Character

### 题意简述

你可以选一对 $i,j$ 使得 $s_j \to s_i$，可以选择 $i = j$。请让这个字符串的不同排列最少。

### 解题思路

~~打表~~观察可得，若**让序列里出现次数最多的字母“吃掉”出现次数最少的字母**，那么答案就是最优的。依题意模拟即可，复杂度 $O(n)$。

### 具体实现

**桶**找最多最少。

- 如果最多字母 $=$ 最少字母，那么意味着整个序列都是这个字母，随便找一对 $i=j$ 操作即可。
- 否则找到第一个最少字母的位置，将其赋值为出现最多的字母。

输出这个序列即可。

### 参考代码

~~赛时代码~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t , n , tong[30] , maxt , maxp , mint , minp;
char a[15];
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		memset(tong , 0 , sizeof(tong));
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
			tong[a[i] - 'a']++;
		}
		maxt = mint = 0;
		maxp = -1;
		mint = 1000000007;
		for(int i = 0 ; i < 26 ; i++)
		{
			if(tong[i] > maxt)
			{
				maxt = tong[i];
				maxp = i;
			}
		}
		for(int i = 0 ; i < 26 ; i++)
		{
			if(!tong[i])
			{
				continue;
			}
			if(tong[i] <= mint)
			{
				mint = tong[i];
				minp = i;
			}
		}
		if(maxp == minp)
		{
			for(int i = 1 ; i <= n ; i++)
			{
				a[i] = minp + 'a';
			}
		}
		else
		{
			for(int i = 1 ; i <= n ; i++)
			{
				if(a[i] - 'a' == minp)
				{
					a[i] = maxp + 'a';
					break;
				}
			}
		}
		for(int i = 1 ; i <= n ; i++)
		{
			cout << a[i];
		}
		cout << '\n';
	}
	return 0; 
}
```

第一次打 [CF 比赛](https://codeforces.com/bestRatingChanges/15807442)，被 D 题虐了 awa。

---

## 作者：nannangua (赞：1)

由题目可知，我们需要找到 $ i,j $ 然后将 $ s_i $ 进行一次修改为 $ s_j $ 的操作。   

根据题目即可想出一种通俗易懂的思路，那就是找出 $ s $ 中出现次数最多的字母 $ n $ 和出现次数最少的字母 $ m $，将 $ n $ 与 $ m $ 替换，即可做所能形成的不同排列最少。

最后附上代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
int n,cnt=0,b[28];
char a[12],c,d;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int minn=1e5+6,maxx=0,l=0;
		memset(b,0,sizeof(b));
		memset(a,0,sizeof(a));
		cin>>n>>a;
		if(n==1){
			cout<<a<<endl;
			continue;
		}
		else if(n==2){
			cout<<a[0]<<a[0]<<endl; 
			continue;
		}
		for(int i=0;i<n;i++) ++b[a[i]-96]; 
		c=0,d=0;
		for(int i=1;i<=26;i++)
		{
			if(b[i]!=0 && b[i]<minn) 
			{
				minn=b[i];
				c=i+96;
			}
			if(b[i]>=maxx)
			{
				maxx=b[i];
				d=i+96; 
			} 
		}
		if(c==d) 
		{
			cout<<a<<endl;
			continue;
		}
		for(int i=0;i<n;i++)
		{
			if(a[i]==c && l==0) 
			{
				cout<<d;
				l=1;
			}
			else cout<<a[i];
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：hgcnxn (赞：1)

## CF2047B Replace Character题解

### 题目大意

给定一个长为 $n$ 的、仅由小写字母组成的字符串 $s$。你可以进行一次操作：

- 将 $s_i$ 修改为 $s_j$。

要求修改后的字符串所能形成的不同排列最少。输出修改后的字符串。

### 思路

假设该字符串中有 $a_1$ 个字符 $c_1$，$a_2$ 个字符 $c_2 \ldots a_m$ 个字符 $c_m$，且 $a_1\ge a_2\ge\ldots\ge a_m\ge 1$ 则该字符串能形成的不同排列个数为 
$$C_n^{a_1}\times C_{n-a_1}^{a_2}\times\ldots\times C_{a_{m-1}+a_m}^{a_{m-1}}\times C_{a_m}^{a_m}$$

也就是

$$\frac{n!}{\prod\limits_{i=1}^{m}a_i!}$$

**所以我们要做的，就是最大化它的分母。**

那么，我们只需要将其中一个 $c_m$ 修改为 $c_1$，即可。

### 代码

赛时的实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,mx,mn;
struct node{int id,num;};
string s;
bool cmp(node x,node y){return x.num>y.num;}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>s;
		node a[26];
		for(int i=0;i<26;i++){
			a[i].id=i;
			a[i].num=0;
		}
		for(int i=0;i<n;i++)a[s[i]-'a'].num++;
		sort(a,a+26,cmp);
		mx=a[0].id;
		mn=25;
		while(a[mn].num==0)mn--;
		mn=a[mn].id;
		for(int i=0;i<n;i++){
			if(s[i]==mn+'a'){
				s[i]=mx+'a';
				break;
			}
		}
		cout<<s<<"\n";
	}
	return 0;
}
```

---

## 作者：Drifty (赞：1)

### Solution

乱贪。就是你注意到多重集 $\{n_1\cdot s_1,n_2\cdot s_2,\ldots,n_m\cdot s_m\}$ 的排列数是 $x=\frac{n!}{n_1!n_2!\cdots n_m!}$，因此我们想要通过改变一个数使得 $x$ 尽可能小，那我们肯定是让最大的一个 $n_i$ 加上一，最小的 $n_j$ 减一。

### Code

```cpp
#pragma GCC optimize(2, 3)
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int n, T;
string s;
int main() {
    cin.tie(NULL), cout.tie(NULL)
    -> sync_with_stdio(false);
    cin >> T;
    while (T --) {
        cin >> n >> s;
        vector <int> cnt(256);
        for (int i = 0; i < n; i ++) cnt[s[i]] ++;
        char ans = 'a', ppt = 'a';
        int pos = -1, minn = 1000;
        for (char i = 'a'; i <= 'z'; i ++) {
            if (cnt[i] > 0) {
                if (cnt[i] >= pos) ans = i, pos = cnt[i];
                if (cnt[i] <= minn) ppt = i, minn = cnt[i]; 
            }
        }
        if (ans == ppt) {
            for (int i = 0; i < n; i ++) {
                if (s[i] != ppt) {s[i] = ans; break;}
            }
        }
        else for (int i = 0; i < n; i ++) {
            if (s[i] == ppt) {s[i] = ans; break;}
        }
        cout << s << '\n';
    }
    return 0;
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意：

一个非常短的小写字母串，可以进行一次下标间的赋值操作，问如何得到最少的不同排列个数。

### 思路：

没有想到其它题解那样特别精妙的方法（主要是不会证），发现 $n$ 极小，于是愉快地打一个暴力。

回顾一下多重集合的排列公式，设我们有 $n$ 个元素，第 $i$ 种元素出现了 $k_i$ 次，排列数如下：

$$\dfrac{n!}{\prod k_i!}$$

直接枚举所有不同的赋值方法，开桶存字符串不同字符的个数，用上述公式计算，找到最小值即可。代码很丑且十分的暴力，但不用证明结论。

复杂度 $O(n^3+n^2w)$，$w$ 为桶大小。

### 程序如下：

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int T,a[30];
char str[15];
int factorial(int x){
	int ret=1;
	for(int i=2;i<=x;i++)ret*=i;
	return ret;
}
int main(){
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d%s",&n,str+1);
		char ans[15];
		int mn=2e9;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				char tmp[15];
				for(int k=1;k<=n;k++)tmp[k]=str[k];
				tmp[j]=tmp[i];
				memset(a,0,sizeof(a));
				for(int k=1;k<=n;k++)a[tmp[k]-'a']++;
				int cur=factorial(n);
				for(int k=0;k<26;k++)cur/=factorial(a[k]);
				if(cur<mn){
					mn=cur;
					for(int k=1;k<=n;k++)ans[k]=tmp[k];
				}
			}
		}
		for(int i=1;i<=n;i++)printf("%c",ans[i]);
		puts("");
	}
	return 0;
}
```

### THE END

---

