# 【MX-X7-T1】[LSOT-3] 分蛋糕

## 题目背景

原题链接：<https://oier.team/problems/X7B>。

这里原本有一个相当魔怔的影射当代营销号的题目背景，不过由于过于魔怔被删去了。

## 题目描述

有两个正整数 $a$ 和 $b$，每次可以选择以下操作之一：

1. $a\gets a\times 2$。
2. $b\gets b-1$。
3. $b\gets b+1$。

求使得 $a=b$ 的最小操作次数。

## 说明/提示

**【样例解释 #1】**

初始 $a=1$，$b=5$。

- 进行操作 $1$，变成 $a=2$，$b=5$。
- 进行操作 $1$，变成 $a=4$，$b=5$。
- 进行操作 $2$，变成 $a=4$，$b=4$。

总操作次数为 $3$。可以证明不存在操作次数更少的方案。

**【数据范围】**

对于 $28\%$ 的数据，$a,b\le 20$。

对于 $60\%$ 的数据，$a,b\le 5000$。

对于全部的数据，$1\le a,b\le 10^9$。

## 样例 #1

### 输入

```
1 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
114514 1919810
```

### 输出

```
87590
```

# 题解

## 作者：jinhangdong (赞：5)

枚举操作 $1$ 进行几次，然后可以算出这是的答案，取最小值就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,Min=1e9;
signed main()
{
	cin>>a>>b;
	for(int i=1;i<=31;++i)
	{
		Min=min(Min,i+abs(a-b));//计算操作次数
		a*=2;
	}
	cout<<Min-1;//其实是比i少乘1次，所以减1
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：3)

## 思路

对于这一道题，我们通过暴力模拟的方法计算答案。

为了操作次数最小，我们只需要 $a←a\times 2$ 即可，其余我们多次 $b←b±1$ 即可。

有一个情况需要特判：即有可能这不是最优解，需要 $a$ 再乘 $2$，然后 $b$ 多次减 $1$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	if(a>b){
		cout<<a-b<<endl;
		return 0;
	}
	int cnt=0;
	int cnt2=0;
	while(a*2<=b){
		cnt++,cnt2++;
		a*=2;
	}
	cnt=cnt+b-a;
	cnt2=cnt2+a*2-b;
	cout<<min(cnt,cnt2+1)<<endl;
	return 0;
}
```

---

## 作者：zlqwq (赞：2)

按照 $a$ 和 $b$ 的大小进行分类讨论。

如果 $a>b$ 就很简单，答案即为 $a-b$。

比较有思维含量的是 $a<b$ 的情况，我们发现 $a$ 的自增方式只有乘二这一种，当然也可以让 $b-1$。但很容易发现 $a$ 自己乘二这种方式一定是不劣的，因为第一种可以减少 $a$ 的差距且 $a$ 一定是大于等于 $1$ 的数，而第二种只能减少 $1$ 的差距。

所以我们让 $a$ 一直乘二，一直到 $2a<b$，因为我们不知道让 $b$ 加还是减，所以再次分类讨论，取小的答案加上即可。


```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
int a,b;
int ans=0;
signed main(){
	cin>>a>>b;
	if(a==b){
		cout<<0;
		return 0;
	}
	if(a<b){
		while(a<b){
			a*=2;
			ans++;
		}
		ans--;
		a/=2;
		ans+=min(1+2*a-b,b-a);
		cout<<ans;
	}
	else{
		cout<<a-b;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11560)

我们考虑一种简单的贪心。由于 $\times 2$ 要比 $\pm 1$ 优很多，所以我们先尽量 $\times 2$。分两种情况：
1. 将 $a$ 乘上尽可能多的 $2$ 但不能超过 $b$ 的值。
2. 将 $a$ 乘上尽可能少的 $2$ 但要超过 $b$ 的值。

最后取 $\min$ 即可。别忘记特判 $a \ge b$ 的情况。代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,t;
int fpow(int x,int y){//手写 pow 函数 
	int ans=1;
	for(int i=1;i<=y;i++) ans*=x;
	return ans;
}
int main(){
	cin>>a>>b;
	if(a>=b){//特判 
		cout<<a-b;
		return 0;
	}
	for(int i=1;i<=50;i++){
		if(a*fpow(2,i)>b){//结果超过 b 了 
			cout<<min(i+a*fpow(2,i)-b,i-1+b-a*fpow(2,i-1));//输出两种情况的最小值 
			return 0;
		}
	}
}
```

---

## 作者：Wish_kazdel (赞：1)

## 思路
主要就是纯模拟。根据题目我们可以简单得出如果要让次数尽可能的小，先变化 $a$，直到 $a$ 的下次变化比 $b$ 大，再变化 $b$，详细见代码。


---

## 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int minOperations(int a, int b) {
    int operations = 0;
    //分类讨论
    if (a > b) {
        return a - b;
    }//如果a比b大，则直接返回a-b
    
    while (a < b) {
        if(a * 2 > b){
        	operations++;
        	int x1=operations+a*2-b;
        	int x2=b-a+operations-1;
        	return min(x1,x2);//取a变化前后最小值
		}else{
			a*=2;
			operations++;
			if(a==b) return operations;
		}
}
}
int main() {
    int a, b;
    cin >> a >> b;
    
    cout << minOperations(a, b) << endl;
    
    return 0;
}
```

---

## 作者：longlong666 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11560)
## 思路
尽量将 $a$ 靠近 $b$ 后取两者之差即可。

具体分以下三种情况：

- 当 $a>b$ 时，$a$ 无法通过乘 $2$ 以靠近 $b$ 答案为 $a-b$。
- 当 $a=b$ 时，无需进行任何操作，答案为 $0$。
- 当 $a<b$ 时，使 $a$ 乘多次以靠近 $b$ 使答案减少，具体看代码。
## 代码
~~~cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10;
int a,b,ans1,ans2;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>a>>b;
	if(a>b){//特判,a无法乘2以靠近b
		cout<<a-b<<endl;
		return 0;
	}
	else if(a==b){//特判
		cout<<0<<endl;
		return 0;
	}
	while(a<=b){a*=2;ans1++;}//尽量乘,取大于b的最小
	ans2=ans1; ans1+=a-b;
	while(a>b){a/=2;ans2--;}//取小于b的最大
	ans2+=b-a;
	cout<<min(ans1,ans2)<<endl;
	return 0;
}
~~~

---

## 作者：DoubleQLzn (赞：0)

可以从 $1$ 操作入手。对于执行 $i$ 次 $1$ 操作，由于其它操作只能将 $b$ 加 $1$ 或者减 $1$，所以在这种情况下的答案就是 $i+|b-a^{i-1}|$，循环比较求和即可。

注意，答案应当初始化为 $|b-a|$，即执行 $0$ 次一操作时的答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int a,b;
	cin >> a >> b;
	int mi = abs(b - a);
	for (int i = 1;i <= 40;i++)
	{
		a = a * 2;
		mi = min(mi,abs(b - a) + i);
	}
	cout << mi;
	return 0;
}
```

~~好像是 MX 赛时一血/二血~~

---

## 作者：YBJ1006 (赞：0)

不难发现，尽量让 $a$ 变，代价更小。

所以只需让 $a$ 一直乘以  $2$ 即可。我们发现答案就是取  $a\gets a\times 2$ 过程中与  $b$ 差值最小的时候。具体见代码。

赛时代码，写的比较烂。
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll a, b;
    cin >> a >> b;
    ll aa = a, bb = b;
    int cnt = 0;
    while ((a << 1) <= b)
    {
        a <<= 1;
        cnt++;
    }
    cnt += abs(b - a);

    int cnt1 = 0;
    while ((aa << 1) <= bb)
    {
        aa <<= 1;
        cnt1++;
    }
    aa <<= 1;
    cnt1++;
    cnt1 += abs(bb - aa);
    cout << min(cnt,cnt1);

    return 0;
}
```

---

