# 値札

## 题目描述

[problemUrl]: https://atcoder.jp/contests/bitflyer2018-final/tasks/bitflyer2018_final_a

すぬけ君は、店を開こうとしています。$ N $ 個の商品を販売する予定です。 $ i $ 番目の商品は、$ p_i $ 円で販売されます。

すぬけ君は、それぞれの価格の末尾についた `0` をたくさん書くのが大変に感じたので、 $ N $ 個全ての商品の値札の末尾に連続する `0` を全ての商品について同じ個数だけ取り除き、 会計の時にその分の `0` を補完することにしました。

商品の値札 $ 1 $ 枚あたり、 `0` を最大何個取り除けるかを求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 100 $
- $ 1\ <\ =\ p_i\ <\ =\ 10^9 $
- $ p_i $ は整数

### Sample Explanation 1

それぞれ、末尾についた `0` を $ 1 $ つだけ取り除くことができ、すると値札には $ 30 $, $ 25 $, $ 600 $, $ 73 $ と書かれることになります。

## 样例 #1

### 输入

```
4
300
250
6000
730```

### 输出

```
1```

## 样例 #2

### 输入

```
5
10000000
30000000
150000000
200000000
990000000```

### 输出

```
7```

## 样例 #3

### 输入

```
4
100101100
110010000
100001001
110011000```

### 输出

```
0```

# 题解

## 作者：Nuyoah_awa (赞：3)

### 题目大意
给定 $n$ 个数，求所有数末尾 $0$ 的个数的最小值。

### 题目分析
由于 $1 \le n \le 100$，$n$ 不大，我们可以计算每个数末尾 $0$ 的个数然后求最小值。

求末尾 $0$ 的个数有两种方法：

1. 以数字读入，并进行拆位，看末尾有几个 $0$。

2. 以字符串读入，看字符串末尾有几个 $0$ 字符。

两种算法时间复杂度都差不多，大概是 $O(n)$ 的。

### code

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int INF = 1e9;
int n, ans = INF; 

int main()
{
    scanf("%d", &n);
    for(int i = 1, a, sum;i <= n;i++)
    {
        scanf("%d", &a);
        sum = 0;
        while(a % 10 == 0)
            sum++, a /= 10;
        ans = min(ans, sum);
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：fkcufk (赞：2)


[洛谷链接](https://www.luogu.com.cn/problem/AT_bitflyer2018_final_a)

[AT 链接](https://atcoder.jp/contests/bitflyer2018-final/tasks/bitflyer2018_final_a)

解析：

本题输入的 $N$ 个整数可以使用 `string` 来输入。

我们可以先定义一个字符串。

然后每一步都取字符串末尾有几个 $0$。

最后取最小值即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int mn=0x3f3f3f3f; // min 去正无穷
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
        string s;
		cin>>s;
		int t=s.size()-1;
        int x=0;
		while(s[t]=='0'){
			x++,t--;
		}
        mn=min(x,mn);
	}
	cout<<mn;
	return 0;
}
```

---

## 作者：Acceptedit_ (赞：1)

看题解区里没这种解法的，就来发一发吧。

首先输入 $n$ 和每个 $a_i$。

然后循环，用布尔型变量 $f$ 表示每个数是否末尾都还有 $0$（如果还有共同的 $0$ 那么 $f$ 是 `False`，否则是 `True`）。然后对数组 $a$ 进行遍历，只要发现有一项除以 $10$ 除不尽了（证明这一项末尾没有 $0$ 了）就把 $f$ 设成 `True`（C++ 中 `1` 就相当于 `True`）。否则就把这一项末尾的一个 $0$ 去掉。

循环完了判断，如果中途记录了有任意一项末尾没 $0$ 了就退出并输出答案，否则答案加 $1$。

代码：

```cpp
#include <iostream>
#define qwq ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 优化 cin,cout。
#define r(i, a, b) for(int i = a; i <= b; i++) // 可以简化代码。
using namespace std;
int n, a[110], ans;
bool f = 0; // 初始 f=0（False）
int main() {
    cin >> n;
    r(i, 1, n) cin >> a[i];
    while(1) {
        r(i, 1, n)
            if(a[i] % 10) f = 1; // 这一项末尾没有 0 了就设置 f=1（True）
            else a[i] /= 10;
        if(f) break; // 只要不能所有数同时去 0 了就跳出循环
        ans++;
    }
    cout << ans << endl; // 注意换行！
    return 0;
}
```


---

## 作者：Pink_Cut_Tree (赞：1)

### 题意

给定 $N$ 个正整数，求这些数末尾共同的 $0$ 的数量。

### 分析

我们可以写一个无限循环，让这 $N$ 个数每次都除以 $10$，每一次都判断这些数是否都是 $10$ 的倍数，如果是，计数器自增 $1$，否则，输出计数器的值。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std; 
int num[105];
int n;
bool check(){ //这是一个判断每一个数是否都是10的倍数的函数
	for(int i=1;i<=n;i++){
		if(num[i]%10!=0){
			return false;
		}
	}
return true;
}
void divide(){ //这是一个让数组内每一个数都除以10的函数
	for(int i=1;i<=n;i++){
		num[i]/=10;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>num[i];
	}
	int ans=0; //计数器
	while(true){
		if(check()){ //如果每一个数是否都是10的倍数
			ans++;
			divide();
		}
		else{
			break;
		}
	}
	cout<<ans<<"\n"; //输出一定要换行！
return 0;	
}
```


---

## 作者：ht__QAQ__ (赞：1)

## 大意：
- 给你 $n$ 个数，求这 $n$ 个数至少末尾有几个 $0$。

## 分析：

- 求每个数的末尾有几个 $0$，在把有几个 $0$ 从小到大排序，那么至少有的就是最小的数。

## 思路：
- 建个函数，来求末尾有几个 $0$。

1. 如果字符是 $0$，下一步。
2. 循环判断后面全是 $0$，不是则退出，记数归 $0$，重新回到第 $1$ 步。
3. 若后面全是，退出函数，返回记数的值。
4. 如果全扫完了，没有，返回 $0$。

### 函数代码：
```cpp
int get(string n){
	int a,s=n.size(),z=0;
	for(int i=0;i<s;i++){
		if(n[i]=='0'){
			int j=i;
			while(j!=s){
				if(n[j]!='0'){
					z=0;
					break;
				}
				z++;
				j++;
			}
			if(j==s)
				return z;
		}
	}
	return z;
}
```

---

## 后记：

这是本人第二篇题解。

管理辛苦了！

by：2023.04.22


---

## 作者：yzm0325 (赞：1)

又没有一行输入多个数的情况了，发 Python3 题解。

### 思路

首先输入。

接下来输入每个数，然后对这个数不断除以 $10$（使用地板除法，即除完后向下取整）并将记录 $0$ 数量的变量加一，直到对 $10$ 取模不等于 $0$（即末尾没有 $0$ 了）为止。然后更新答案。

最后输出。

有一些细节，已经标注在注释里了。

### code

```python
n = int(input()) # 把输入转换成 int 类型。
ans = 1e10 # ans 记录答案，要取一个较大的值。
for i in range(n):
    a = int(input())
    _sum = 0 # 用来记录目前的 a 末尾 0 的个数。
    # 注意 sum 是 Python3 中的关键字，前面要加一个下划线！
    while a % 10 == 0: 
        _sum += 1 # sum++ 是 C/C++ 的语法，放在 Python 里是不对的。
        a = a // 10 # Python 里的整除是 //。
    ans = min(ans, _sum)
print(ans)
```

完结撒花！

---

## 作者：prt_xcdh (赞：0)

# 题意

给点 $\verb!n!$ 个整数，求出所有数末尾 $\verb!0!$ 的个数。

# 思路
这道题可用 $\verb!int!$，我用的是 $\verb!string!$ 类型，先定义一个 $\verb!sum!$ 赋 $\verb!int!$ 类型的最大值，先输入 $\verb!int!$ 次字符串, 每次的 $\verb!l!$ 是开头, $\verb!l!$ 是每个字符串的末尾，再循环判断如果每个末尾是 $\verb!0!$，就缩小范围, 最后求 $\verb!l!$ 和 $\verb!sum!$ 的最小值。

# CODE

```c++
#include<bits/stdc++.h>
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
using namespace std;
string s;
int main() {
	int n,sum=0x3f3f3f3f,l=0,r=0;
	cin>>n;
	f(i,1,n,1){
		cin >> s;
		r=s.size()-1,l=0;
		while(s[r]=='0')l++,r--;
		sum=min(sum,l);
	}
	cout << sum;
    return 0;
}
```





---

## 作者：Bc2_ChickenDreamer (赞：0)

## AT_bitflyer2018_final_a 値札 题解

### 题目分析

我们先看到数据范围，$n$ 很小，我们就可以一一遍历有几个 $0$。首先。我们定义一个 $ans$ 并把它赋值为极大值，用来记录结果，在定义一个 $sum$ 并把它赋值为 $0$，用来记录每个数字 $0$ 的个数。然后循环输入，从最后一个字符遍历，只要探测到了 $0$ 就把 $sum$ 加 $1$，否则中断循环。遍历完之后把 $ans$ 赋值为 $ans$ 和 $sum$ 的最小值，最后输出即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define qwq ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
const int N = -1;
int n, ans = INT_MAX;//定义 n 和 ans，并把 ans 赋值为极大值

signed main()
{
	cin >> n;
	while (n --)//循环输入
	{
		string a;
		cin >> a;//输入数字
		int lena = a.size() - 1, sum = 0;
		for (int i = lena; i >= 0; -- i)//循环遍历
		{
			if (a[i] == '0')//如果是 0
				++ sum;//sum 加 1
			else//否则
				break;//中断遍历
		} 
		ans = min(ans, sum);//把 ans 赋值为 ans 和 sum 的最小值
	}
	cout << ans;//输出
	return 0;
}
```


---

## 作者：_dAAAAAAN_ (赞：0)

### 题意

给定 $N$ 个正整数，求这些数末尾共同的 $0$ 的数量。

### 思路

输入字符串，然后把每个字符串从后往前遍历。找出每个字符串的末尾有几个 $0$，用数组 $a$ 存储这些数据。最后把数组从小到大排序，输出 $a_1$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10005],cnt;
string s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		cnt=s.size()-1;
		while(s[cnt]=='0'){
			a[i]++;
			cnt--;
		}
	}
	sort(a+1,a+n+1);
	cout<<a[1]<<"\n";
	return 0;
} 
```

---

## 作者：Gaogao2011 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_bitflyer2018_final_a)

### 题意

输入 $n$ 个正整数，输出这些数末尾共同的 $0$ 的数量。

### 思路

水题，建议评红。

**每次输入** 都枚计算末尾 $0$ 的个数，最后取 **最小值** 即可。

**那么如何计算正整数数 $x$ 末尾 0 的个数？**

众所周知，根据位置原理求 $x$ 的各位数字的方法如下。

* 个位 $ = x \bmod 10$

* 十位 $ = x \div 10 \bmod 10$

依次类推。因此 **只要这一位数字为 0**，就把计数变量加 1，以此得出最终 $0$ 的个数。

### 代码

**完整代码:**


```

#include <bits/stdc++.h>
using namespace std;
int count(int x) {
	int ans = 0;
	while (x % 10 == 0) {
		ans++;
		x /= 10;
	}
	return ans;
}
int main() {
	int n, mn = 1e9;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		if (count(x) < mn) {
			mn = count(x);
		}
	}
	printf("%d\n", mn);
	return 0;	
}


```


---

## 作者：CleverRaccoon (赞：0)

## 题目

[题目传送门](https://www.luogu.com.cn/problem/AT_bitflyer2018_final_a)

给定 $N$ 个正整数，求这些数末尾共同的 $0$ 的数量。

## 思路

每次输入的数字很容易想到用 `int` 类型来存，但是本人认为使用 `string` 类型更加方便，代码更加直观。

可以在读入的同时进行处理，**从后往前**遍历每个读进来的字符串，使用一个变量 $cnt$ 来记录当前字符串末尾 $0$ 的数量，遍历字符串时，只要字符串的当前数字是 $0$，就将变量 $cnt$ 的值加一。只要遇到了不是 $0$ 的数字，就终止遍历。

用变量 $ans$ 记录最终答案，因为要求末尾共同的0的数量，所以要求的是0最少多少个，每次找到一个字符串末尾 $0$ 的个数后，更新 $ans$ 为更小的答案，即 $ans = \min(ans,cnt)$。

## 细节

1. 变量 $ans$ 最开始要设为一个较大的数字，因为每次要取小。
2. 比较是否为 $0$ 时，要与字符 $0$ 进行比对，而不是数字 $0$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, ans = 0xff;    // ans记录这些数末尾共同的0数量，初始化为较大的一个值
    cin >> n;
    string num;
    while(n--) {
        cin >> num; // 将数字当作字符串来处理，边读边做
        int cnt = 0;
        // 从右往左遍历字符串，使用cnt来记录0的个数，遇到非0就停止
        for(int i = num.size() - 1; i >= 0; --i, ++cnt)
            if(num[i] != '0')	// '0'而不是0
                break;
        ans = min(ans, cnt);    // 因为要求末尾共同的0的数量，所以要求的是0最少多少个
    }
    cout << ans;
    return 0;
}
```

题解就到这里了，有什么问题欢迎私信交流，谢谢大家！



---

## 作者：huyixuanpi (赞：0)

## 题意
给定 $N$ 个正整数，求所有的 $N$ 个整数的末尾都有的 $K$ 个 $0$ 的最大 $K$ 是？

## 分析思路
其实这道题很水。

通过分析样例，我们发现，其实这道题就在求所有整数后 $0$ 个数最小的值。

将每一个整数除以 $10$，然后计算末尾数字为零的次数。对于整数 `12300`，`12300->1230->123` 一共进行了三次运算，所以答案是 $3$。对 $N$ 个整数计数次数，最小值为答案。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,n,ans=1e9,num; 
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n ;i++)
	{
		num = 0;
		scanf("%d",&a);
		while(a%10==0)
		{
			num++;
			a/=10;
		}
		ans=min(ans,num);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：tbdsh (赞：0)

# 题意

[题目传送门](https://www.luogu.com.cn/problem/AT_bitflyer2018_final_a)

输入 $n(1\le n \le 100)$ 个正整数 $p_i(1 \le p_i \le 10^9)$,输出这些数末尾共同的 $0$ 的数量。

# 分析

## 思路

通过分析样例二：

#### 输入

```
5
10000000
30000000
150000000
200000000
990000000
```

### 输出

```
7
```

可以发现，这里面末尾 $0$ 数量最少的数 $30000000$ 的末尾 $0$ 的数量就是答案，由此推测末尾 $0$ 数量最少的数的末尾 $0$ 的数量就是答案。

## 实现

输入 $p$ 后循环判断末尾是否为 $0$ 并且 $p$ 是否为 $0$。是就 `cnt++`，否则退出循环，将 $ans$ 更新为 $\min(ans,cnt)$。最后输出 $ans$ 即可。

时间复杂度：$O(n)$。

# Code

```cpp
#include<bits/stdc++.h>

using namespace std;
int n, ans = INT_MAX, p;
int main(){
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> p;
    int cnt = 0;
    while(p % 10 == 0 && p){
      p /= 10;
      cnt++;
    }
    ans = min(ans, cnt);
  }
  cout << ans << "\n";
  return 0;
} 
```



---

## 作者：_ChongYun_ (赞：0)

# 解析

首先，我们发现这题就是道妥妥的模拟题。

可是我们又发现了一个问题，整数不好遍历。于是我们就可以用`c++`大法里的`to_string`函数，这个函数可以把数转化成字符串。

然后我们把这些字符串装在一个数组里面，用一个双重循环倒着遍历每一个字符。为什么要倒着？因为题目说的是末尾的`0`。如果遍历到一个`0`，答案就加一。否则就`break`。

最后我们在这些答案中取一个最小值就是它们共用`0`最大值了。

[~~一次过的~~AC记录](https://www.luogu.com.cn/record/96654748)

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
string a[114514];
long long ans=INT_MAX,sum=0;
int main(){
	cin>>t;
	int tn=0;
	while(t--){
		tn++;
		cin>>n;
		a[tn]=to_string(n);
	}
	for(int i=1;i<=tn;i++){
		for(int j=a[i].size()-1;j>0;j--){
			if(a[i][j]=='0'){
				sum++;
			}else{
				break;
			}
		}
		ans=min(ans,sum);
		sum=0;
	}
	cout<<ans<<endl;
	return 0;
}

```


---

