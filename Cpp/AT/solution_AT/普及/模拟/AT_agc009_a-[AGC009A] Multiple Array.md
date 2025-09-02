# [AGC009A] Multiple Array

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jrex2017/tasks/agc009_a

$ N $ 項からなる数列 $ A_1,...,A_N $ があり、$ N $ 個のボタンがあります。 $ i(1\ ≦\ i\ ≦\ N) $ 個目のボタンを押すと、数列 $ A $ の $ 1 $ 項目から $ i $ 項目までの値が $ 1 $ ずつ増加します。

数列 $ B_1,...,B_N $ が与えられます。高橋君は、これらのボタンを何回か押して、すべての $ i $ に対し、$ A_i $ が $ B_i $ の倍数になるようにします。

高橋君がボタンを押す回数の最小値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 0\ ≦\ A_i\ ≦\ 10^9(1\ ≦\ i\ ≦\ N) $
- $ 1\ ≦\ B_i\ ≦\ 10^9(1\ ≦\ i\ ≦\ N) $

### Sample Explanation 1

$ 1 $ つめのボタンを $ 2 $ 回、$ 2 $ つめのボタンを $ 2 $ 回、$ 3 $ つめのボタンを $ 3 $ 回押せばよいです。

## 样例 #1

### 输入

```
3
3 5
2 7
9 4```

### 输出

```
7```

## 样例 #2

### 输入

```
7
3 1
4 1
5 9
2 6
5 3
5 8
9 7```

### 输出

```
22```

# 题解

## 作者：zjyqwq (赞：5)

### AT2290 [AGC009A] Multiple Array题解

Pascal题解。


------------
#### 解题思路
本题重点在如何按合理的顺序按按钮。

因为后面的按钮会改变前面的数，而前面的按钮不会改变后面的数，所以，我们要从后往前依次按按钮。

接下来，按题意模拟即可。

当然，也不是真正的模拟，不是一个一个加上去的。

我们可以直接计算当前数需要按得按钮数，可以用 $O(1)$ 的时间复杂度。

计算方法：对于当前的 $b[i]$ ，我们要将当前的 $ans$ (目前为止按了几次按钮) 加上当前的 $a[i]$ 再模当前的 $b[i]$ ,得到的余数便是要按的次数。


------------
#### 注意事项
 - 本题的 $a[]$ 和 $b[]$ 较大，要开六十四位整型。


------------
#### 代码
```pascal
var
n,i,s:int64;
a,b:array[0..100005]of int64;//一定要定义int64啊！！！
 begin
  readln(n);
  for i:=1 to n do
   readln(a[i],b[i]);//输入
  for i:=n downto 1 do//循环一定要倒着来。
   s:=s+(b[i]-(a[i]+s)mod b[i]) mod b[i];//用公式颓。
  write(s);
 end.
```
~~我是不会告诉你我交了5次才AC的。~~

---

## 作者：Level_Down (赞：2)

题意不再赘述，这篇题解主要讲述一下这道题贪心思路的原理，因为个人感觉这道题的其他题解都讲的不是很清楚。

我们可以拿样例1来看一看：

```
3
3 5
2 7
9 4
```

在这个样例中我们发现想要修改 $a_3$ 就只能按第三个按钮，所以按第三个按钮使 $a_3$ 变为 $b_3$ 的倍数是**必做**的。

按完第三个按钮后，我们发现第二个按钮的情况和之前的第三个按钮一样了，以此类推，我们才得出计算答案时循环从后往前的贪心思路。

对于每一个循环，只需要计算 $a_i$ 变为 $b_i$ 倍数需要按的按钮次数，再加到总数里面即可，于是本题迎刃而解。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a[100005],b[100005],ans,t;
//十年OI一场空，不开longlong见祖宗。 
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		{
			cin >> a[i] >> b[i];
		}
	for (int i = n; i >= 1; i--)
		{
			a[i] += t; //因为按比i大的按钮时a[i]的值也会变，故用累加器t累加改变的值，一次性加上。
			//或者把ans当累加器用也行。 
			if (a[i] % b[i] == 0) continue;
			t += b[i] - (a[i] % b[i]),ans += b[i] - (a[i] % b[i]);//累加答案。 
		}	
	cout << ans << endl;	
	return 0;	
} 
```


---

## 作者：Temperature_automata (赞：2)

洛谷终于能测AT了，点个赞。

话不多说，我们进入正题

本题主要测试选手的逆序思维
### 【part 1】题意简述
按下第i个按钮，a[1...i]全+1，求按多少个键试每个数为指定数的倍数      
### 【part 2】算法&思路分析

十年OI一场空，不开longlong见祖宗。（haha）

请注意数据范围哦 ~~作者为此调试一小时~~

因为按后面的按钮会影响前面的按钮，所以……

# 循环要倒着写

这其实就是本题重点了。剩下的咱模拟就行。

注意，求与b[i]倍数最小的差用( ( ( a[i] ) / b[i] ) + 1 ) * b[i] - a[i]

记得加上后面加的哟(＾Ｕ＾)ノ~ＹＯ
   
   
   
### 【part 3】代码分析
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

long long n , a[100005] , b[100005] , ans , num ; 

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin >> n ;
	for ( int i = 1 ; i <= n ; i ++ ) {
		cin >> a[i] >> b[i] ;
	}
	for ( int i = n ; i > 0 ; i -- ) {
		if ((a[i]+num)%b[i]) {//记住加num！
			long long sum = ( ( ( a[i] + num ) / b[i] ) + 1 ) * b[i] - a[i] - num ;//记住加减num！
			ans += sum , num += sum ;
		}
	}
	cout << ans ;
	return 0;
                                                                             防抄袭
}
```
###### 

---

## 作者：Lithium_Chestnut (赞：1)

### 大概思路

没什么算法，直接模拟就行了，注意的是后面第二个循环一定要倒着跑，从 $n$ 到 $1$ 进行循环，里面套个判断，让答案加上 $a_i$ 变成 $b_i$ 的**倍数的次数**。

`AtCoder` 两大特性就不多说了。

### $std$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100001],b[100001],ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    for(int i=n;i>=1;i--)
	{
        a[i]+=ans;
        if(a[i]%b[i]!=0) ans+=a[i]-a[i]%b[i];
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：零殇 (赞：0)

#### 题意

给你长度都为$n$的序列$A$和$B$，一次可以让$A[1]-A[i]$都加$1$，求最少几次能让所有$A[i]$都为$B[i]$的倍数。

#### 思路

首先，因为一次会让$A[1]-A[i]$都加$1$，为了不影响我们已经获得的结果结果，我们从后往前遍历。

因为每一次都会让前面的所有数都影响，因此我们要把现在遍历到的$A[i]$加上我们操作的次数。

```
a[i]+=flag;//flag为计数器
```

然后判断，如果$A[i]$不是$B[i]$的倍数，那么我们就把它修改。

我们用用$temp$记录$A[i]$除以$B[i]$的余数，那么$A[i]$距离下一个$B[i]$的倍数则为$B[i]-temp$。

```
if(temp!=0)
{
	temp=b[i]-temp;
	flag+=temp;
	a[i]+=temp;
}
```

最后，上完整代码：
```
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[100001],b[100001];
int main()
{
	long long flag=0,temp;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&a[i],&b[i]);
	for(int i=n;i>=1;i--)
	{
		a[i]+=flag;
		temp=a[i]%b[i];
		if(temp!=0)
		{
			temp=b[i]-temp;
			flag+=temp;
			a[i]+=temp;
		}
	}
	cout<<flag<<endl;
	return 0;
}
```
完结撒花~

---

## 作者：zfn07 (赞：0)

本题只需模拟即可,要注意的是要从n到1循环。因为按下第 
i个按钮，数列A是从第1项到第i项的值各增加1。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long a[100005],b[100005],ans=0,i,n;
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(i=n;i>=1;i--){//再次重复一遍:是从n到1循环！！！
		a[i]+=ans;//把之前应该加的加起来
		if(a[i]%b[i]!=0)
			ans+=b[i]-a[i]%b[i];//让ans加上使a[i]变成b[i]的倍数的次数
	}
	cout<<ans<<endl;//输出
	return 0; 
} 
```


---

## 作者：纸片人 (赞：0)

二话不说先上代码

```c
#include<bits/stdc++.h>
using namespace std;
long long n,a[100005],b[100005],ans;
int main(){
    long long i,j;
    cin>>n;
    for(i=1;i<=n;i++)
        cin>>a[i]>>b[i];
    for(i=n;i>=1;i--){
        a[i]+=ans;
        for(j=a[i]/b[i];;j++)
            if(j*b[i]>=a[i])
                break;
        ans+=j*b[i]-a[i];
    }
    cout<<ans<<endl;
    return 0;
}

```

因为按钮会叠加，所以从后往前扫。

每次 for(i=n;i>=1;i--) 循环完毕的 j*b[i]-a[i] 就是第i个按钮要按的次数。

可自行手动模拟。

---

## 作者：Zhouyc2009 (赞：0)

### 题目大意
对于每一个 $i$，题目要求使 $a_i\ \bmod\ b_i=0$，每一次按第 $i$ 个按钮可以使 $a_1$ 到 $a_i$ 的值累加 $1$，求最少的按按钮次数。

可以发现，如果先按编号小的按钮，再按编号大的按钮，那么按编号大的按钮的时候就会影响到比它编号小的 $a_i$ 的值，所以我们要从后往前枚举 $i$。

我们对于每一个 $i$ ，当前 $a_i$ 的值就是最初 $a_i$ 的值加上已经按按钮的次数，所以我们用 $sum$ 表示已经按按钮的次数，用 $ans$ 表示当前需要按按钮的次数，即可得出公式。

#### 公式：$ans=(b_i-(a_i+sum)\ \bmod\ b_i)\ \bmod\ b_i$

循环条件要注意一下，要从后往前循环，因为按正常 $1 \sim n$ 循环，后面的按钮改变了前面的按钮，会萌生出一系列的问题。

而从后往前循环就没有这种问题了。

#### 温馨提示：数据较大，要开`int64`，下面代码里循环变量也开了 `int64`，洛谷是可以用的，但如果在自己的电脑上，就可能会炸。

## AC代码：
```
var
  sum,n,i:int64;//题目数据较大，得定int64
  a,b:array[-10..100100]of int64;
begin
  readln(n);
  for i:=1 to n do readln(a[i],b[i]);
  for i:=n downto 1 do
    inc(sum,(b[i]-(a[i]+sum) mod b[i]) mod b[i]);//套公式并累加
  writeln(sum)；
end.
```

---

## 作者：cjZYZtcl (赞：0)

## 这题很明显是模拟
枚举每一个点要按几次按钮，最后加起来输出就可以了。

但是要注意枚举的顺序。

如果从前往后枚举，那么在枚举当前的点的时候之前的点还要去更新，会麻烦，而且时间复杂度也很高。

所以要从后往前枚举。

### 那怎么求要按几次按钮呢？

因为题目说要让 $a_i$ 是 $b_i$ 的倍数，所以我们只需要把当前 $a_i$ 加上已经按过的按钮次数，然后求一下除以 $b_i$ 的余数，最后用 $b_i$ 去减去这个余数，再模一下 $b_i$ 就得出了按几次按钮。~~（萌新解法，勿喷）~~

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[100005], b[100005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read(), b[i] = read();
	}
	int sum = 0;
	for(int i = n; i >= 1; i--){
		sum += (b[i] - (a[i] + sum) % b[i]) % b[i];
	}
	write(sum);
}
```


---

