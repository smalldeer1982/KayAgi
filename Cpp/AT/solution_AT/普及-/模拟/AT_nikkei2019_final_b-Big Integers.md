# Big Integers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_b

長さ $ N $ の整数列 $ A $、長さ $ M $ の整数列 $ B $、整数 $ K $ が与えられます。 値 $ X,Y $ を以下のように定義します。

- $ X=\ \sum_{i=1}^N\ A_i\ \times\ K^{N-i}\ =\ A_1\ \times\ K^{N-1}\ +\ A_2\ \times\ K^{N-2}\ +\ ...\ +\ A_N\ \times\ K^0 $
- $ Y=\ \sum_{i=1}^M\ B_i\ \times\ K^{M-i}\ =\ B_1\ \times\ K^{M-1}\ +\ B_2\ \times\ K^{M-2}\ +\ ...\ +\ B_M\ \times\ K^0 $

$ X $ と $ Y $ のどちらが小さいかを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 2\ \leq\ K\ \leq\ 10^9 $
- $ 0\ \leq\ A_i\ \leq\ K-1 $
- $ 1\ \leq\ A_1 $
- $ 0\ \leq\ B_i\ \leq\ K-1 $
- $ 1\ \leq\ B_1 $
- 入力される値はすべて整数である。

### Sample Explanation 1

$ X=123,Y=124 $ であり、 $ X\ <\ Y $ であるので `X` と出力します。

## 样例 #1

### 输入

```
3 3 10
1 2 3
1 2 4```

### 输出

```
X```

## 样例 #2

### 输入

```
4 3 13
1 2 3 4
4 5 6```

### 输出

```
Y```

## 样例 #3

### 输入

```
4 4 2
1 1 0 1
1 1 0 1```

### 输出

```
Same```

# 题解

## 作者：xiaoshumiao (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_nikkei2019_final_b)

## 简要题意

给你两个 $k$ 进制下的数 $X$ 和 $Y$，问哪个更小。

## 分析

由于 $X,Y$ 太大，仅靠 int，long long 这些基本数据类型是不行的。我们可以用数组分别来存两个数。例如，$x_i$ 表示 $X$ 从左往右的第 $i$ 位。我们先比较 $X$ 和 $Y$ 的长度，再按从左往右的顺序依次比较 $X$ 和 $Y$ 的每一位。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=100005;
int a[MAXN];
int main() {
  int n,m,k,b;
  scanf("%d%d%d",&n,&m,&k);
  if(n!=m) {
  	printf("%c",(n<m?'X':'Y'));
  	return 0;
  }
  for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
  for(int i=1;i<=m;i++) {
  	cin>>b;
  	if(a[i]!=b) {
  	  printf("%c",(a[i]<b?'X':'Y'));
  	  return 0;
  	}
  }
  printf("Same");
  return 0;
}
```

---

## 作者：LYJ_B_O_Creation (赞：1)

题目思路：
-
通过题目，我们不难知道这道题只是让我们判断 $a$ 序列组成的数和 $b$ 序列组成的数哪个大，（例子：如果 $a$ 序列为 $1$ $2$ $3$ $4$ 那么组成的数就是 $1234$，$b$ 序列为 $4$ $5$ $6$ 那么组成的数就是 $456$，由于 $1234$ 大于 $456$，所以输出 `Y`），以下为写代码的整体步骤。

**第一步**：输入 $n$，$m$，$k$，$a$ 序列和 $b$ 序列。

**第二步**：由于小学学过一个知识：两个数的数位哪个多，那个数就是最大的。所以判断 $n$ 和 $m$ 哪个大，如果 $n>m$ 输出 `Y` 终止程序；如果 $m>n$ 输出 `X` 终止程序，当两个判断都不成立，那么进行接下来的操作。

**第三步**：弄一个循环，从 $1$ 到 $n$，判断 $a_i$ 和 $b_i$ 哪个大，当 $a_i>b_i$ 时，输出 `Y`，结束程序；当 $b_i>a_i$ 时，输出 `X`，同样结束程序。

**第四步**：如果每一位都相同，那两个数就相同，所以输出 `Same`。

代码：
-
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void s(int x , int y[10000])
{
	for(int i = 1;i <= x;i++) cin >> y[i];
}
signed main() 
{
	int n , m , k , a[100005] , b[100005];
	cin >> n >> m >> k;
	s(n , a);
	s(m , b);
	if(n > m)
	{
		cout << "Y" << endl;
		return 0;
	}
	if(m > n)
	{
		cout << "X" << endl;
		return 0;
	}
	for(int i = 1;i <= n;i++)
	{
		if(a[i] > b[i]) 
		{
			cout << "Y" << endl;
			return 0;
		}
		if(b[i] > a[i]) 
		{
			cout << "X" << endl;
			return 0;
		}
	}
	cout << "Same" << endl;
	return 0;
}
```

---

## 作者：__delta_epsilon__ (赞：1)

## 题意

给定长为 $N$ 的数组 $A$，长为 $M$ 的数组 $B$，和一个正整数 $K$，设：

- $ X=\sum_{i=1}^{N}{A_i}\times K^{N-i}$
- $ Y=\sum_{i=1}^{M}{B_i}\times K^{M-i}$

若 $X<Y$，输出 `X`，若 $X>Y$，输出 `Y`，否则输出 `Same`。

## 分析

根据小学时就学过的 $N$ 进制转换，上面的两个式子就是告诉你，$X,Y$ 是两个 $K$ 进制数，数位分别为 $A, B$ 两个数组，比较他们的大小，输出小的那一个。

但你可能会想，万一有数位大于或等于 $K$ 怎么办呢？如果你问出了这种问题，请您看【数据范围】谢谢。（$0\le A_i,B_i\le K-1,A_1,B_1\ge1$）

再根据小学时就学过的比较数的大小的方法，模拟即可：

- 数位多的数大

```cpp
if(M > N) {cout << 'X'; return 0;} // 注意，输出小的那个数
if(M < N) {cout << 'Y'; return 0;}
```
- 如果数位一样多，从最高位开始，最高位大的就大，若相同，比较第二位，以此类推，直到最后一位。

```cpp
for(int i = 1; i <= N; i++) {
    if(A[i] > B[i]) {
        cout << 'Y'; return 0; // 同理，注意输出小的数
    }
    if(A[i] < B[i]) {
        cout << 'X'; return 0;
    }
}
```
- 如果每一位都相同，那两个数就相同。
```
cout << "Same"; // 因为前面判断完直接 return 0; 所以不需要特判，剩下的一定是相同的
```

## 总代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int N, M, K, A[100200], B[100200];
signed main(){
	cin >> N >> M >> K;
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int j = 1; j <= M; j++) cin >> B[j];
	if(N > M) {cout << 'Y'; return 0;}
	if(M > N) {cout << 'X'; return 0;}
	for(int i = 1; i <= N; i++) {
	    if(A[i] > B[i]) {
	        cout << 'Y'; return 0;
	    }
	    if(A[i] < B[i]) {
	        cout << 'X'; return 0;
	    }
	}
	cout << "Same";
	return 0;
}
```

稍微压了一下行。AC [记录](https://www.luogu.com.cn/record/96668739)。

---

## 作者：xiaoyang111 (赞：0)

# AT_nikkei2019_final_b 题解

## 前言

[题目传送门](https://www.luogu.com.cn/problem/AT_nikkei2019_final_b)

[可能会更好的阅读体验](https://www.luogu.com.cn/blog/xiaoyang111/solution-at-nikkei2019-final-b)

## 正篇开始

### 思路

此题我开始想的是模拟，看到数据范围很大，可能会爆精度，我选择了自带高精度的语言，没想到就算时间限制有两秒，但还是超时了，所以模拟别想了。

我们仔细看题，发现 $A$ 和 $B$ 转换成 $X$ 和 $Y$ 不就是把 $K$ 进制数 $A$ 和 $B$ 转换成十进制数 $X$ 和 $Y$ 吗？这样想，这个题就好做了。

同一进制比较方法类似高精度比较，先比较位数，如果第一个数位数比第二个数位数多，那么第一个数就大。相反，如果第二个数位数比第一个数位数多，那么第二个数就大。如果位数一样，就从高到低一次比较，哪一位上的数大哪一个数就大。高精度比较的思路就类似小学学的整数比较那样。

### 代码

我的代码是先输入 $A$ 数组，然后在输入 $B$ 数组的时候比较。

下面是我的代码，代码风格可能有些难看，请见谅。

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main(){
	int n,m,k;//定义。
	cin >> n >> m >> k;//输入。
	if (n>m){//如果第一个数的数位多。
		cout<<"Y\n";//输出。
		return 0;//退出程序。
	}else if (n<m){//如果第二个数的数位多。
		cout<<"X\n";//输出。
		return 0;//退出程序。
	}else{//他们的位数是相同的。
		vector<int> a(n);//定义第一个数。
		for (int i=0;i<n;++i){//输入。
			cin >> a[i];//输入第一个个数组的每一个数字。
		}
		for (int i=0;i<m;++i){//输入加判断。
			int t;//定义第二个数的每一位数字。
			cin >> t;//输入第二个数的每一位数字。
			if (t>a[i]){//一位一位比
				cout<<"X\n";//第一个数小。
				return 0;//退出程序。
			}
			if (t<a[i]){//一位一位比
				cout<<"Y\n";//第二个数小。
				return 0;//退出程序。
			}
		}
	}
	cout<<"Same\n";//如果没有比较出来就说明相等。
	return 0;
}
```

---

## 作者：lewis_lu_CH3COOH (赞：0)

## 题意
比较两个 $K$ 进制数 $X,Y$。若 $X<Y$，输出 `X`。若 $Y<X$，输出 `Y`，相同则输出 `Same`。

## 分析
因为两数的进制相同，所以比较两数的大小时不用考虑它们的进制，其比较方法与十进制数比较方法相同。两数比较时首先比较它们的位数，位数大的一定较大，反之较小。若两数位数相同，从两数的最高位开始逐位比较。当该位两数大小不同，直接输出结果并结束程序。若比较完后，两数完全相同，输出 `Same` 即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005];

int main() {
	int n,m,k;
	cin>>n>>m>>k;
	if(n>m) {//比较位数
		cout<<"Y"<<endl;
		return 0;
	} else if(n<m) {
		cout<<"X"<<endl;
		return 0;
	}
	for(int i=1; i<=n; i++) {
		cin>>a[i];
	}
	for(int i=1; i<=m; i++) {//逐位比较
		int s;
		cin>>s;
		if(s>a[i]) {
			cout<<"X"<<endl;
			return 0;
		} else if(s<a[i]) {
			cout<<"Y"<<endl;
			return 0;
		}
	}
	cout<<"Same"<<endl;
	return 0;
}
```

---

## 作者：Soul_Seeker (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_nikkei2019_final_b)

# 题目大意

这题看上去很难实际上超级超级超级水！！！！！！！

实际上就是给定一个 $n$ 位的高精正整数 $X$，和一个 $m$ 位的高精正整数 $Y$，求他俩哪一个数小，若 $X$ 小输出 $X$，若 $Y$ 小则输出 $Y$，否则输出 `Same`。

没错，题目中的 $K$ **没有用！！！**

# 思路详解

就是比大小，先比每一个数的位数，若两个数的位数相同，就从最高位开始比较，看他们哪个大即可。如果两个数完全相同，就输出 `Same`。

~~这题应该一年级都做得出来吧……~~

# 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, k, a[100005], b[100005];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> k;//这题由于是高精，直接给了我们每个数的位数，都不用我们自己算了捏
	for (int i = 0; i < n; i++)cin >> a[i];
	for (int i = 0; i < m; i++)cin >> b[i];//输入
	if (n > m)return cout << "Y\n", 0;//如果x的位数比y的位数大，则直接输出Y
	else if (n < m)return cout << "X\n", 0;//如果m比n大，则输出X
	else for (int i = 0; i < n; i++)//如果两个位数一样
			if (a[i] > b[i])return cout << "Y\n", 0;
			else if (b[i] > a[i])return cout << "X\n", 0;
	cout << "Same\n";//一定要换行
	return 0;
}

```

---

## 作者：fish_love_cat (赞：0)

通过简单的推导（当然也可以手玩样例）可以发现，题面中的公式，其实就是一个 $k$ 进制数转十进制数的公式。所以这题本质上就是一个 $k$ 进制数的比大小，那我们就可以借机取巧了。

众所周知，相同进制比大小，与十进制比大小方式相同：首先看位数，然后从高到低逐级比较即可。这样便可以省去换十进制这一步，提高我们的代码效率。

那么，代码就不难得出了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[100005];
int main(){
    cin>>n>>m>>k;
    if(n>m){
        cout<<"Y\n";
        return 0;
    }else if(n<m){//位数
        cout<<"X\n";
        return 0;
    }
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<m;i++){
        int x;
        cin>>x;
        if(x>a[i]){
            cout<<"X\n";
            return 0;
        }else if(x<a[i]){//逐级
            cout<<"Y\n";
            return 0;
        }
    }
    cout<<"Same\n";
    return 0;
}
```

---

## 作者：zzyxl_qaq (赞：0)

[题目传送门](/problem/AT_nikkei2019_final_b)

#### 思路简述

在小学的时候，我们都学过如何比较两个数的大小：

1. 位数多的数大。

2. 位数相同的情况下，由高位向低位一次判断，若当前位不同则当前位大的数大。如果所有位置都一样，那么两个数一样大。

而本题就是要比较两个 $K$ 进制数的大小，那么我们可以根据上面的思路写出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005];
int main(){
    int n,m,k;
    cin>>n>>m>>k;
    if(n>m)cout<<"Y\n";
    else if(n<m)cout<<"X\n";//判断位数
    else{
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++){
            cin>>b[i];
            if(a[i]==b[i])continue;
            if(a[i]>b[i])cout<<"Y\n";
            else if(a[i]<b[i])cout<<"X\n";//逐位判断
            return 0;//不同直接退出
        }
        cout<<"Same\n";//全部相同就相等
    }
}
```


---

## 作者：Moon_Traveller (赞：0)

[>> 传送门 <<](https://www.luogu.com.cn/problem/AT_nikkei2019_final_b)

[>> 原OJ传送门 <<](https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_b)

## 题目大意

这道题看起来有点吓人，但其实就是给出两个 $K$ 进制数。让我们比较它们的大小。

## 思路

还记得小时候学过的“两个数的比较方法”吗——

1. 比较位数，位数大的数大。
2. 位数相同时，比较最高位，最高位大的数大。
3. 最高位相同，比较下一位，以此类推，直到找完所有位数为止。

这个方法也适用于其他进制的比较，我们用代码模拟即可。

## 代码

```cpp
#include <iostream>
using namespace std;

int n, m, k;
int a[100005], b[100005];

int main()
{
    cin >> n >> m >> k;
    if(n > m) // 比较位数，位数大的数更大
    {
        cout << "Y" << endl;
        return 0;
    }
    if(m > n)
    {
        cout << "X" << endl;
        return 0;
    }
    for(int i = 1; i <= n; i++) // 位数相同，比较各个数位的数
    {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++)
    {
        cin >> b[i];
        if(a[i] > b[i]) // 比较各个数位
        {
            cout << "Y" << endl;
            return 0;
        }
        if(b[i] > a[i])
        {
            cout << "X" << endl;
            return 0;
        }
    }
    cout << "Same" << endl; // 全部遍历完仍然分不出大小，说明相等
    return 0;
}
```

---

## 作者：prt_xcdh (赞：0)

# 思路

这道题就是让我们找一下 $\verb!A!$ 数列和 $\verb!B!$ 数列哪一个小, 我们可以先比较一下哪一个数列比较长，如果 $\verb!N > M!$，就输出 $\verb!Y!$ 反之则输出 $\verb!X!$， 如果 $\verb!N!$ 和 $\verb!M!$ 相同并且 $\verb!A!$ 数列和 $\verb!B!$ 数列相同，则输出 $\verb!Same!$， 如果都不是，我们就可以一位一位的比较了。

# CODE

```cpp
#include<bits/stdc++.h>
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
using namespace std;
const int maxn = 1e5+10;
int a[maxn],b[maxn],x,y,kkk;
inline string kk(){
    f(i,1,x,1){
        if(a[i]<b[i])return "X";
        else if(a[i]>b[i])return "Y";

    }
    return "Same";

}
int main() {
    cin >> x>>y>>kkk;
    if(x>y){//如果第一个大于第二个 
        cout << "Y";
        return 0;
    }
    else if(x<y){//如果第二个大于第一个 
        cout << "X";
        return 0;
    }
    f(i,1,x,1){//输入a数组 
        cin>>a[i]; 
    }
    f(i,1,y,1){//输入b数组 
        cin>>b[i];
    }
    cout << kk();
    return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

## 思路

看到数字 $X$ 和 $Y$ 的形成方式，怎么样，是不是感觉很熟悉？每个数都要乘以 $K$ 的几次方，这难道不是转进制中的**按权展开再求和**吗？所以这个题的意思就是让你将 $A$ 和 $B$ 按权展开，求和，最后比较大小，那么我们此时就可以用比较进制数的大小的方法去比较，先比较长度，长度一样就一位一位比较，最后得出答案。

## 代码

```cpp
#include<bits/stdc++.h>
int a[114514], b[1919810], lena, lenb, k;
inline std::string bj(){
    for(int i = 1; i <= lena; i++) if(a[i] != b[i]){//一位一位比较，如果不同就返回这一位数的大小关系
        return (a[i] > b[i] ? "Y" : "X");
    }
    return "Same";//全部一样的情况
}
main(){
    std::cin >> lena >> lenb >> k;
    for(int i = 1; i <= lena; i++) std::cin >> a[i];
    for(int i = 1; i <= lenb; i++) std::cin >> b[i];
    std::cout << (lena > lenb ? "Y" : (lena < lenb ? "X" : bj())) << std::endl;//先比较长度
    return 0;
}
```

---

