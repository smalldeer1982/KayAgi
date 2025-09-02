# Product of Three Numbers

## 题目描述

给定一个数 $n$ ，请求出三个不相同的整数 $a,b,c$ 且 $2 \leq a,b,c$ ，使得 $a \cdot b \cdot c =n$。

如果有多个答案，输出任一合法解。

本题有多组数据。

## 样例 #1

### 输入

```
5
64
32
97
2
12345```

### 输出

```
YES
2 4 8 
NO
NO
NO
YES
3 5 823```

# 题解

## 作者：封禁用户 (赞：3)

一道很水很水的黄题。

考虑枚举因数，第一次枚举求出 $n$ 最小的因数，记为 $a$，第二次枚举区间 $[a+1,\frac{n}{a}]$ 中最小的因数，记为 $b$。如果 $a$ 和 $b$ 中有一个求不出来，或者求完以后 $\frac{n}{ab}$ 的值等于 $1,a,b$ 三个数中的任何一个，就是无解，否则有解，答案是 $a,b,\frac{n}{ab}$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		int a=-1,b=-1; 
		for(int i=2;i*i<=n;i++){//枚举最小因数
			if(n%i==0){
				a=i;
				n/=i;
				break;
			}
		}
		if(a==-1){
			cout<<"NO"<<endl;
			continue;
		}
		for(int i=a+1;i*i<=n;i++){//第二次枚举区间 [a+1,n/a]
			if(n%i==0){
				b=i;
				n/=i;
				break;
			}
		}
		if(b==-1||n==a||n==b||n==1)cout<<"NO"<<endl;//无解
		else cout<<"YES\n"<<a<<" "<<b<<" "<<n<<endl;//输出答案
	}
	return 0;
}
```


---

## 作者：YooLc407 (赞：2)

## 题目大意

给定正整数 $n$ ， 求三个互不相同的整数 $a,b,c$ ，使得 $a\cdot b \cdot c = n$ 且 $2\le a,b,c$ 。输出任意一组解。

## 思路

既然是任意一组解，那么直接就在 $[2,\sqrt{n}]$ 枚举因数即可，不过要求三个数，我们直接将求出的因数再分解一次就可以了。注意三个数不能重复。

## 部分代码

```cpp
pair<int, int> check(int n,int cur)
{
	for(int i = 2; i * i < n; ++i) // 这里不取等是为了判重
	{
		if(i == cur) continue; // 也是判重用
		if(n % i == 0)
			return make_pair(i, n / i);
	}
	return make_pair(-1, -1); // 无解
}
void solve()
{
	int n;
	n = read();
	pair<int, int> res = check(n, 0);
	pair<int, int> res2 = check(res.second, res.first);
	// 分解第二个因数（较大）
	if(res.first == -1 || res2.first == -1)
	{
		puts("NO");
	}
	else
	{	
		printf("YES\n");
		printf("%d %d %d\n", res.first, res2.first, res2.second);
	}
}
```

---

## 作者：cq_loves_Capoo (赞：1)

好久没发过题解了/ts   
   
这道题目感觉像恶评/kk 连我这种菜鸡都会做。   
   
第一步是找一个数的因数，可以从 $2$ 到 $\sqrt{x}$ 去找因数，给出这一步比较简练的代码：   
  
```
for (int i=2; i<=sqrt(x); i++) {
	if (x%i == 0) {
		return i;
	}	
}
```
  
那么找到因数了，剩下的就是一些简单的操作。   
  
>1.先进行第一次找因数，如果没找到，直接输出 NO 。   
>2. $n$ 除掉第一个因数，然后继续找第二个因数，但必须从第一个因数 $+1$ 开始找，因为是不能重复的。   
>3.一个小小的特判（我想了五分钟/kk），如果 $n$ 和第二个因数相等，也就是不能分解成三个相同的因数，继续输出 NO 。   
>4.如果前面都没有输出 NO，就分别输出 第一个因数、第二个因数、$n$。   
   
给出一份差劲的代码（刚换码风体谅一下）：    
   
```
#include<bits/stdc++.h>
#define endl '\n'
#pragma GCC optimize(3)

using namespace std;
int T;

inline int split (int x, int y) {//找因数 
	for (int i=y+1/*因为不能重复，所以就要设 y+1*/; i<=sqrt(x)/*开平方根，不然会超时*/; i++) {
		if (x%i == 0) {
			return i;
		}
	}
	return -1;
}

inline void mains() {
	int n = 0; cin >> n;
	int cnt1 = split (n, 1);//找第一个因数 
	if (cnt1 == -1) {
		cout << "NO" << endl;//输出 NO 
		return;// 并且退出这次的操作。 
	}
	n /= cnt1;
	int cnt2 = split (n, cnt1);//找第二个因数 
	if (cnt2 == -1) {
		cout << "NO" << endl;
		return;//同上 
	}
	n /= cnt2;
	if (cnt2 == n) {//一个小小的特判 
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl << cnt1 << " " << cnt2 << " " << n << endl;//输出 
}

signed main() {
	ios::sync_with_stdio(false);
	cin >> T;//多组测试数据 
	while (T--) mains();
}
```   
   
如果有疑问，可以私信问窝，有时间的话会帮助解答的喵。

---

## 作者：Eason_cyx (赞：0)

比较容易的一道题。

### 思路：

我们首先枚举 $a$，如果这个数连一个真因数都没有的话，说明它是质数，直接输出 $\texttt{NO}$。否则，我们继续枚举 $b$，和 $a$ 同理。如果对于这个数，我们顺利的找到了 $a$ 和 $b$，那么答案就是 $\frac{n}{ab}$。

注意一下小细节：

- 如果 $b = a$，那么是不成立的，需要再循环中特判。
 
- 如果 $\frac{n}{ab} = a$ 或者 $\frac{n}{ab} = b$，以及$\frac{n}{ab} = 1$这三种情况，那么前两种就重复了，第三种的 $c$ 不成立，这三种情况下是无解的。

- 在找完 $a$ 和 $b$ 时，都要特判是否为 $0$，如果为 $0$ 则无解。

- 如果以上几种情况都没有，就可以输出了。注意要先输出 $\texttt{YES}$ 并换行。

这样就可以写出代码了。
```
#include <iostream>
using namespace std;
int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        int a = 0,b = 0,c = 0;
        for(int i = 2;i * i <= n;i++) {
            if(n % i == 0) {
                n /= i;
                a = i;
                break;
            }
        }
        if(a == 0) {
            cout << "NO" << endl;
            continue;
        }
        for(int i = 2;i * i <= n;i++) {
            if(n % i == 0 && i != a) {
                n /= i;
                b = i;
                break;
            }
        }
        if(b == 0 || b == a) {
            cout << "NO" << endl;
            continue;
        }
        if(n == 1 || n == a || n == b) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES\n" << a << ' ' << b << ' ' << n << endl;
    }
    return 0;
}
```
### 总结：
本题其实代码难度和思维难度都不高，比较注重小细节，建议评橙。

---

## 作者：zeekliu (赞：0)

我们设三个数 $ x,y,z $，他们都是 $ n $ 的因数。

此处的 $ x $ 表示 $ n $ 最小的因数，$ y $ 表示第二小的因数 $ (x \neq y) $，$ z = \frac{n}{xy} $。

所以只要 $ x \neq y $ 且 $ y \neq z $ 且 $ x \neq 1,y \neq 1,z \neq 1 $ 即可。

那就两个循环呗，其中任何一个不满足要求，直接过。

代码：

```cpp
//CF1294C 22-09-21
#include <bits/stdc++.h>
using namespace std;

int main() 
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int _; cin>>_;
	while (_--)
	{
		int n; cin>>n;
		int x=-1,y=-1,z=-1;
		for (int i=2;i<=sqrt(n);i++)
			if (n%i==0) { x=i,n/=i; break; }
		if (x==-1) { cout<<"NO"<<endl; continue; }
		for (int i=x+1;i<=sqrt(n);i++)
			if (n%i==0) { y=i,n/=i; break; }
		if (y==-1) { cout<<"NO"<<endl; continue; }
		z=n;
		if (z==1 || z==x || z==y) cout<<"NO"<<endl;
		else cout<<"YES"<<endl<<x<<" "<<y<<" "<<z<<endl;
	}
	exit(0);
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：  

使得 $a \times b\times c=n~~~~(a\ne b\ne c)$   

思路：   

1. 先枚举最小的 $a$ ，（以下程序的返回值为最小因数（有部分优化），即 $a$ 的值） 
```cpp
int query(int n){
	if(n%2==0) return 2;
	for(int i=3;i<=sqrt(n);i+=2){
		if(n%i==0) return i;
	}
	return n;
} 
```
2. 再枚举最小的 $b$ ，（同理）
```cpp
		for(int i=a+1;i<=sqrt(n);i++){
			if(n%i==0){
				b=i;
				break;
			}
		}
```
3. 得到 $c$ ，并判断是否符合条件



### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

int t,n;

int query(int n){
	if(n%2==0) return 2;
	for(int i=3;i<=sqrt(n);i+=2){
		if(n%i==0) return i;
	}
	return n;
}

int main()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int a=query(n),b=-1,c=-1;
		n/=a;
		for(int i=a+1;i<=sqrt(n);i++){
			if(n%i==0){
				b=i;
				break;
			}
		}
		c=n/b;
		if(b==-1||c==-1||b==c){
			printf("NO\n");
		}else{
			printf("YES\n");
			printf("%d %d %d\n",a,b,c);
		}
	}
	return 0;
}
```

---

## 作者：GoldenFishX (赞：0)

~~用了个神奇的方法卡过去了~~

~~时间复杂度：O(能过)~~

### 主要思路

- 先用一个数组a存下所有的因数（除了1），顺便求出n是否是质数，是质数就直接输出```NO```

- 然后在a中枚举前两个数（枚举前两个数就可以得出第3个数），然后判断答案是否可行。

- 找出第一个答案后，由于只要输出任意解，所以直接退出循环就行了。

### 代码部分

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 5;
int a[MAXN];  //存因子
int cnt = 0;  //因子的个数
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    bool f = 1;
    for (int i = 2; i * i <= n; i++) {  //首先判断是否是质数,顺便存下因子
      if (n % i == 0) {
        a[cnt++] = i;
        a[cnt++] = n / i;
        f = 0;
      }
    }
    if (f) { //为质数的情况
      cout << "NO\n";
    } else {
      int ans1 = 0, ans2, ans3;  //三个数
      for (int i = 0; i < cnt; ++i) {	//枚举第一个数
        for (int j = 0; j < cnt; ++j) {//枚举第二个数	
          int x = n / a[i] / a[j];  //第三个数
          if (a[i] != a[j]  && a[i] != x && a[j] != x && x > 1) { //第一个数、第二个数、第三个数互不相等，第三个数不为1
              ans1 = a[i], ans2 = a[j], ans3 = n / a[i] / a[j];//记录答案
              break;
            }
        }
        if (ans1 != 0) { //如果有答案了，就退出
          break;
        }
      }
      if (ans1 == 0) { //没有发现答案的情况
        cout << "NO\n";
      } else {
        cout << "YES\n" << ans1 << " " << ans2 << " " << ans3 << endl;
      }
    }
  }
  return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## [题目传送门。](https://www.luogu.com.cn/problem/CF1294C)

简单来说：

我们可以枚举 $n$ 的最小的两个因数，设它们分别为 $a$，$b$；

则另外一个因数为 $\frac{n}{ab}$。

~~所以我们可以直接输出~~。

所以我们需要几个判定才输出：

- $a=n$ 或 $b=n$ 时，不满足，输出 $\tt NO$。

- 如果 $n$ 连 $3$ 个因数都没有，直接输出 $\tt NO$。

写出代码，此题终。

```
#include<iostream>
using namespace std;
int n,t,flag,a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		flag=1;a=0;b=0;
		for(int i=2;i*i<=n;i++){
			if(n%i==0){
				n/=i;
				if(a==0)a=i;
				else {
					b=i;
					if(n!=1)flag=0;
					else flag=1;
					break;
				}
			}
		}
		if(n==a||n==b)flag=1;
		if(flag)cout<<"NO\n";
		else cout<<"YES\n"<<a<<' '<<b<<' '<<n<<endl;
	}
	return 0;
}
```

（**为什么不考虑 $a=b$ 呢？** 因为 $b$ 一定在 $a$ 之后被赋值，则 $b$ 一定大于 $a$。）

（**关于时间复杂度：** 外层循环 $\operatorname{O}(t)$，内层循环 $\operatorname{O}(\sqrt{n})$，总时间复杂度约为 $\operatorname{O}(t\sqrt{n})$，按 $t\leq100,n\leq10^9$ 来算，总时间复杂度约为 $\operatorname{O}(100\times31622.78)=\operatorname{O}(3162278)$，不会 $\tt TLE$。）

---

