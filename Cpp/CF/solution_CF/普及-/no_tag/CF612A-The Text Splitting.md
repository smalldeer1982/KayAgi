# The Text Splitting

## 题目描述

You are given the string $ s $ of length $ n $ and the numbers $ p,q $ . Split the string $ s $ to pieces of length $ p $ and $ q $ .

For example, the string "Hello" for $ p=2 $ , $ q=3 $ can be split to the two strings "Hel" and "lo" or to the two strings "He" and "llo".

Note it is allowed to split the string $ s $ to the strings only of length $ p $ or to the strings only of length $ q $ (see the second sample test).

## 样例 #1

### 输入

```
5 2 3
Hello
```

### 输出

```
2
He
llo
```

## 样例 #2

### 输入

```
10 9 5
Codeforces
```

### 输出

```
2
Codef
orces
```

## 样例 #3

### 输入

```
6 4 5
Privet
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
8 1 1
abacabac
```

### 输出

```
8
a
b
a
c
a
b
a
c
```

# 题解

## 作者：linyihdfj (赞：2)

## A.The Text Splitting ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16419311.html)
### 题目描述： ###
[原题面](https://codeforces.com/problemset/problem/612/A)
### 题目分析： ###
就是要把长度为 $n$ 的字符串分成长度为 $q$ 和 $p$ 的字符串若干，没有任何特殊限制，而且 $n$ 的范围很小。

那么我们就枚举有多少个被分成的 $q$ 长度的字符串，然后判断是否剩下的可以被分成几个长度为 $p$ 的字符串就好了，知道了这两个值剩下就暴力模拟就出来了。
### 代码详解： ###

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,p,q,l = -1,r = -1;
	string s;
	cin>>n>>p>>q;
	cin>>s;
	for(int i=0; i<=n; i++){
		if(n >= i * p && (n - i * p) % q == 0){
			l = i;
			r = (n - l * p) / q;
			break;
		}
	} 
	if(l == -1 || r == -1){
		cout<<-1<<endl;
		return 0;
	}
	printf("%d\n",l + r);
	bool flag = false;
	for(int i=0; i<l * p; i++){
		if(i % p == 0 && i != 0)
			printf("\n");
		cout<<s[i];
		flag = true;
	}
	if(flag)
		cout<<endl;
	for(int i=0; i<r * q; i++){
		if(i % q == 0 && i != 0)
			cout<<endl;
		cout<<s[i + l * p];
	}
	return 0;
}
```
可能就是对于换行需要特殊注意一下


---

## 作者：Otue (赞：0)



## 基本题意
把字符串分成若干个长为 $p$ 或 $q$ 的字符串，不能就输出 `-1`，否则输出分成了几个字符串以及分成的字符串。
## 思路
其实就是找到一组 $x,y$，使得 $xp+yq=n$。

结合只有 $100$ 的数据范围，于是可以暴力枚举求出 $x,y$。然后再输出  $x$ 个长度为 $p$ ，$y$ 个长度为 $q$ 的字符串即可。

当然还有一种适合大数据的暴力枚举方法：先枚举长度为 $p$ 的字符串选了多少个，于是根据总长为 $n$ 可以算出长度为 $q$ 的选多少个。
## 代码
实现 $1$：
```c++
#include <bits/stdc++.h>
using namespace std;

int n, p, q, idp, idq;
string s;
int t;

int main() {
	cin >> n >> p >> q;
	cin >> s;
	for (int i = 0; i <= 100; i++) {
		for (int j = 0; j <= 100; j++) {
			if (i * p + j * q == n) {   //暴力枚举，无脑
				idp = i;
				idq = j;
				break;
			}
		}
	}
	if (idp == 0 && idq == 0) puts("-1"), exit(0);
	cout << idp + idq << endl;
	while (idp--) {   //输出x个长度为p的字符串
		for (int i = t; i <= t + p - 1; i++) cout << s[i];
		puts("");
		t += p; 
	} 
	while (idq--) {   //输出y个长度为q的字符串
		for (int i = t; i <= t + q - 1; i++) cout << s[i];
		puts("");
		t += q; 
	} 
} 
```
实现 $2$：
```c++
#include <bits/stdc++.h>
using namespace std;

int n, p, q, idp, idq;
string s;
int t;

int main() {
	cin >> n >> p >> q;
	cin >> s;
	for (int i = 0; i <= n / p; i++) {  //只枚举长度为p的选择多少个
		if ((n - i * p) % q == 0) {   //先要除的尽
			idp = i;
			idq = (n - i * p) / q;  //就可以算出长度为q的选择多少个
			break;
		}
	}
	if (idp == 0 && idq == 0) puts("-1"), exit(0);
	cout << idp + idq << endl;
	while (idp--) {
		for (int i = t; i <= t + p - 1; i++) cout << s[i];
		puts("");
		t += p; 
	} 
	while (idq--) {
		for (int i = t; i <= t + q - 1; i++) cout << s[i];
		puts("");
		t += q; 
	} 
} 
```

---

## 作者：i_dont_know_who_am_i (赞：0)

一道简单的模拟。

读题：把一个字符串分成若干个长为 $p$ 或 $q$ 的字符串，不能就输出 $-1$，否则输出分成了几个字符串以及分成的字符串。

数据范围极小，考虑暴力枚举。

这其实就是在解一个不定式方程，设可以分成 $x$ 个长度为 $p$ 的子串，$y$ 个长度为 $q$ 的子串，可得到方程

$$xp+yq=n$$

注意这里 $x$ 和 $y$ 都是非负整数，不难发现只需要枚举取多少个长度为 $p$ 的子串，并且剩下的长度能被 $q$ 整除，这就是最终答案。

上代码：

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int main(){
    int n,p,q;
    cin >>n>>p>>q;
    string s;
    cin >>s;
    int ans=-1;//既用来判断是否有解，又用来存储子串个数，一举两得
    int cntp=0,cntq=0;
    for(int i=0;i<=n/p;i++){
        if((n-i*p)%q==0){
            ans=i+(n-i*p)/q;
            cntp=i;
            cntq=(n-i*p)/q;
            break;
        }
    }//进行判断
    cout<<ans<<endl;
    if(ans!=-1){
        for(int i=0;i<cntp*p;i++){
        	if(i%p==0&&i!=0)cout<<endl;
        	cout<<s[i];
        }
        for(int i=0;i<cntq*q;i++){
        	if(i%q==0&&cntp*p+i!=0)cout<<endl;
        	cout<<s[cntp*p+i];
        }
    }//输出每个子串
}
```


---

## 作者：hxhhxh (赞：0)

## 大意

给定一个长度为 $ n $ 的字符串 $ S $ 和两个正整数 $ p $ 和 $ q $ ，将 $ S $ 拆分成若干个子字符串，使得它们的长度全部为 $ p $ 或 $ q $ 之中的一种。任意写出一种方案。

## 思路

$ 1 \leq p,q \leq n \leq 100 $ 。

显然可以枚举 $ p $ 长度的字串的个数 $ i $ 。

那么剩下 $ n - i \times p $ ，所以当 $ q \mid ( n - i \times p ) $ 时有解。

因为只要求输出任意一组解，只要找到有解就可以直接构造然后 `return 0;` 。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char ch[105];
int n,a,b;
bool asa;
signed main(){
	scanf("%lld %lld %lld %s",&n,&a,&b,ch+1);
	for(int i=0,t;i*a<=n;i++){
		if((n-i*a)%b) continue;
		t=(n-i*a)/b;
		printf("%lld\n",i+t);
		for(int j=1;j<=i*a;j++){
			putchar(ch[j]);
			if(j%a==0) putchar('\n');
		}
		for(int j=1;j<=t*b;j++){
			putchar(ch[i*a+j]);
			if(j%b==0) putchar('\n');
		}
		asa=true;
		break;
	}
	if(!asa) cout<<-1;
	return 0;
}
```

---

## 作者：djh233 (赞：0)


**题意：**

给定一个长度为 $n$ 的字符串 $s$ 和两个整数 $p$ 和 $q$ ，问能否把字符串 $s$ 拆分成若干个长度为 $p$ 和 $q$ 的子串，子串的长度
可以全部为 $p$ ，也可以全部为 $q$ 。

**数据范围：** $1\le p,q\le n\le 10^2$ 。

**做法：**

比赛一开始想了一个假做法，就是用扩欧判断是否有解并且求 $px+qy=n$ 的一组解，然后进行输出，由于想得太急了，以至于没考虑到会有负解的情况，后来又开始对负解进行一通魔改，还是过不了，最后终于想通放弃扩欧。然后发现 $n,p,q$ 的大小只有 $10^2$ ，于是直接暴力枚举拆成长度为 $p$ 和 $q$ 的子串的个数，然后暴力统计。

十分显然，本题是一个极其暴力和简单的模拟，但由于考虑过于鲁莽，加上没看数据范围，导致写了错误解法，“调试+魔改”浪费了一个多小时，应充分从中吸取教训。

**时间复杂度：**$O(n^4)$ 。

$Code:$

```cpp
#include <bits/stdc++.h>

using namespace std;

string ans[110];

void solve()
{
    int n,p,q;
    string s;
    scanf("%d%d%d",&n,&p,&q);
    cin>>s; s=' '+s;

    for(int cntp=0;cntp*p<=n;cntp++)
    {
        for(int cntq=0;cntq*q<=n;cntq++)
        {
            memset(ans,0,sizeof(ans));
            int tot=0,pos=0;
            for(int i=1;i<=cntp;i++)
            {
                ++tot;
                for(int j=1;j<=p;j++) ans[tot]+=s[++pos];
                if(pos==n)
                {
                    printf("%d\n",tot);
                    for(int i=1;i<=tot;i++) cout<<ans[i]<<'\n';
                    return ;
                }
            }
            for(int i=1;i<=cntq;i++)
            {
                ++tot;
                for(int j=1;j<=q;j++) ans[tot]+=s[++pos];
                if(pos==n)
                {
                    printf("%d\n",tot);
                    for(int i=1;i<=tot;i++) cout<<ans[i]<<'\n';
                    return ;
                }
            }
        }
    }
    puts("-1");
}

int main()
{
    solve();
    return 0;
}
```


---

