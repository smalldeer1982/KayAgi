# Can I Square?

## 题目描述

Calin 有 $n$ 个桶，第 $i$ 个桶中有 $a_i$ 个边长为 $1$ 的木块。

Calin 能否用所有给定的木块拼成一个正方形？

## 说明/提示

在第一个测试用例中，Calin 可以拼成一个 $3 \times 3$ 的正方形。

在第二个测试用例中，Calin 可以拼成一个 $4 \times 4$ 的正方形。

在第三个测试用例中，Calin 不能用所有给定的木块拼成一个正方形。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1
9
2
14 2
7
1 2 3 4 5 6 7
6
1 3 5 7 9 11
4
2 2 2 2```

### 输出

```
YES
YES
NO
YES
NO```

# 题解

## 作者：KidA (赞：3)

检验 

$$
\sqrt{\sum_{i=1}^{n} a_i}
$$

是否为整数即可。

实现：

```cpp
int n; double s=0.0; cin>>n;
for(int i=1;i<=n;i++) cin>>a[i],s+=a[i];
cout<<(sqrt(s)==(int)(sqrt(s))?"YES\n":"NO\n");
```

---

## 作者：DrAlfred (赞：1)

摘要：数学，模拟

[传送门：https://www.luogu.com.cn/problem/CF1915C](https://www.luogu.com.cn/problem/CF1915C)

## 题意

$ t $ 组数据。每次给定一个长度为 $ n $ 的数组 $ a $，求其和是否为完全平方数。

## 分析思路

由题，我们只要计算数列的和 $x$，判断 $x$ 是否为完全平方数，即 $\lfloor \sqrt x \rfloor ^ 2 = x$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
long long t, n, x, sum;
inline void solve(void) {
    cin >> n, sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> x, sum += x;
    }
    if ((ll)sqrtl(sum) * (ll)sqrtl(sum) == sum) {
        puts("YES");
    } else {
        puts("NO");
    }
}
int main(int argc, char const *argv[]) {
    cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：Lemon_zqp (赞：1)

### 思路
这题很典型，他说有 $n$ 个桶，每个桶里有若干个木块，问能不能拼成一个大的正方行。其实就是把所有数加起来，然后看一下这个数是不是一个完全平方数即可。也就是拿总和开个根号，然后求总和的根号乘总和的根号，是否等于总和即可。
### 代码
```

#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
 
signed main()
{
	int t;
	cin >> t;
	while(t--){
		int n, ans = 0;
		cin >> n;
		while(n--){
			int a;
			cin >> a;
			ans += a;
		}
		int aa = sqrt(ans);//开根号
		if(aa * aa == ans){//根号乘根号是否等于总和
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}
	} 
	return 0;
}
```


---

## 作者：Jasoncwx (赞：0)

[题目传送门！](/problem/CF1915C)
## 题目思路
我们只需要先算出这个数列的和，然后再判断它是否为正方形数，即它是否为一个整数的平方。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        long long sum=0;
        cin>>n;
        while(n--){
            int t;cin>>t;sum+=t;//求和
        }
        if(int(sqrt(sum))*sqrt(sum)==sum)cout<<"YES";//是某个整数的平方
        else cout<<"NO";
        cout<<endl;
    }
}
```


---

## 作者：coderJerry (赞：0)

### 题目大意
$t$ 组数据。每次 $n$ 个数，问他们全部加起来是否为完全平方数。
### 题目分析
数据不大，所以照着题意模拟即可。每次算出 $n$ 个数的和，再检查是否为完全平方数。但是记得每次把求和变量清零，且由于 $n≤2\times10^5,a_i≤10^9$，所以要开 ```long long```。

这里讲解一下如何判断 $x$ 是否为完全平方数：

设 $\sqrt{x}=k+p$ （$k$ 是整数，$p$ 是小数）。如果 $x$ 是完全平方数，那么 $\sqrt{x}$ 是整数，即 $p=0$，也就是说 $k^2=x$。所以我们用 ```c++``` 转换变量类型的方法转换把它的小数部分去掉。最后再计算 $k^2$ 是否等于 $x$ 即可。
### AC代码
[~~足足跑了差不多半秒。~~](https://codeforces.com/contest/1915/submission/239447248)
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[200010],sum;
bool check(int x){
	double r=sqrt(x);
	if(((int)r)*((int)r)==x) return true;
	return false;//判断平方数
}
signed main(){
	cin>>t;
	while(t--){
		sum=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i];//计算 n 个数的和
		}
		if(check(sum)) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：raozf (赞：0)

## 题意:
 $T$ 组数据，每组数据输入一个数 $n$，问是否能用 $n$ 个 $1 × 1$ 的小正方形组成一个大正方形。
 
## 思路:
既然要组成大正方形，那么面积必须是完全平方数，用变量累加即可。

## Code:

```cpp

#include <bits/stdc++.h>
#define int long long // 要开 long long
using namespace std;
const int N = 2e5 + 3;
int t;
int n;
int a[N];
int sum = 0;
signed main(){
	cin >> t;
	while (t--) { // T 组数据
		sum = 0; // 多测清空
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			sum += a[i]; // sum 累加和
		}
		// 居然不卡精度 ?
		if (int(sqrt(sum)) != sqrt(sum)) { // 判断是否为完全平方数
			cout << "NO\n"; // 无法组成
		} else {
			cout << "YES\n"; // 可以组成
		}
	}
	return 0; // 结束
}

```

---

