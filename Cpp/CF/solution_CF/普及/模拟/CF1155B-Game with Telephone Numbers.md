# Game with Telephone Numbers

## 题目描述

一个数字序列$s$是电话号码，当且仅当$|s|=11$ (长度为$11$)，并且第一位是$8$。

```Vasya``` 和 ```Petya``` 在玩一个游戏，最初他们有一个长度为 $n$ 的数字序列 $s$。两人轮流对当前序列进行操作，每次操作必须从当前序列选中一个数字将它删去。```Vasya``` 先手，```Petya```后手。

比如当前数字序列为```1121``` ，下一轮可能变成 ```111``` ,```121``` ,```112```。

当 $|s|=11$ 时游戏结束，如果**最后的** $s$ 是电话号码，那么  ```Vasya``` 赢，否则 ```Petya``` 赢。

而您需要判断 ```Vasya``` 有没有必胜策略。

## 说明/提示

样例 $1$ 中 ```Vasya``` 应该删掉第二个字符，字符串变为 $880011223344$。此后无论```Petya```如何操作，开头都会是$8$。

样例 $2$ 中 ```Petya``` 可以在 ```Vasya``` 之后立即删去开头的$8$，这样序列中根本就不存在$8$了。

## 样例 #1

### 输入

```
13
8380011223344
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
15
807345619350641
```

### 输出

```
NO
```

# 题解

## 作者：Andy_Li (赞：3)

# CF1155B Game with Telephone Numbers 题解

## 题意

给你一个长度为 $n$（$n$ 为奇数）的字符串，每个人每次可以删除一个字符，删到还剩 $11$ 位时停止。如果还剩 $11$ 位时第一个字符是 $8$，那么先手获胜，否则后手获胜。保证双方都是用最优策略。

## 思路

先手的最优策略是删除第 $\frac{(n-11)}{2} + 1$ 个 $8$ 前面所有不是 $8$ 的数。

后手的最优策略是删除从前往后以此删 $8$。

先跑一遍字符串，查出 $8$ 的个数。如果 $8$ 的个数比后手的操作次数少就是后手赢。

然后找到第 $\frac{(n-11)}{2} + 1$ 个 $8$ 的位置，判断该位置与 $n-11$ 也就是两人删除次数的大小。如果能在两人删除次数总和次内将第 $\frac{(n-11)}{2} + 1$ 个 $8$ 的位置前的所有数删除，则先手赢，否则后手赢。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	cin.tie(0);
	std::ios::sync_with_stdio(false);
	//srand((unsigned)time(NULL));
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n,cnt=0,pos=0;
	cin>>n;
	string s;
	cin>>s;
	if(n==100000)
		return 0;
	for(int i=0;i<s.size();i++)
		if(s[i]=='8')
			cnt++;
	if(cnt<=(n-11)/2)
	{
		cout<<"NO";
		return 0;
	}
	cnt=0;
	for(int i=0;i<s.size();i++)
		if(s[i]=='8')
		{
			cnt++;
			if(cnt==(n-11)/2+1)
			{
				pos=i;
				break;
			}
		}
//	cout<<pos<<endl;
	if(pos<=n-11)
		cout<<"YES";
	else
		cout<<"NO";
	return 0;
}
```

---

## 作者：冒泡ioa (赞：2)

> [博客链接](http://bubbleioa.top/archives/872)

一开始还以为是博弈论（~~我傻了~~）……结果一个简单的贪心就OK了

一轮游戏会将数字取到只剩11个，如果序列中前 $n-10$ 个元素中，8的数量大于其他的数量，那么显然先手会把其中不是8的取完，先手必胜。如果不大于，后手会把所有的8取完，先手必败。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;int a[100005]; 

int main(){
	cin>>n;int cnt=0;
	for(int i=1;i<=n;i++)scanf("%1d",&a[i]);
	for(int i=1;i<=n-10;i++){
		 if(a[i]==8)cnt++;
		 else cnt--;
	}
	if(cnt>0)printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
```


---

## 作者：xukuan (赞：1)

字符串模拟

Vasya肯定删掉开头非8的

Petya肯定删掉开头是8的

模拟即可

顺路说一下，Pascal的delete是O(1)的，而C++的erase会被卡到O(n)

Pascal万岁！！！

```pascal
var
 n,p1,p2:int64;
 s:string;
begin
 readln(n);
 readln(s);
 p1:=1; p2:=1;
 while n>11 do
  begin
   //Vasya的回合
   while (p1<=n) and (s[p1]='8') do inc(p1);//找到要删除的
   if p1>n then//长度超过，也就是说前面都是8
    begin
     writeln('YES');
     exit;
    end;
   delete(s,p1,1); if(p1<>1) then dec(p1);
   //删掉，后退一位
   //这里注意一下，因为还有另一个人的删除，所以如果你不在队头，可能漏过一位，要退下

	//Petya的回合，下面重复就不再贴注释了
   while (p2<=n) and (s[p2]<>'8') do inc(p2);
   if p2>n then
    begin
     writeln('NO');
     exit;
    end;
   delete(s,p2,1); if(p2<>1) then dec(p2);
   
   dec(n); dec(n);
  end;
 if s[1]='8' then writeln('YES')
 else writeln('NO');
end.

```

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1155B Game with Telephone Numbers 题解
### 分析
当游戏结束时会剩下 $11$ 位数字，则最后 $10$ 个数字双方肯定不会动，因此只要考虑 $n-10$ 以内的数就可以了。

若在 $1$ 到 $n-10$ 个数字中，$8$ 出现的次数大于其他数字出现次数之和，则先手可以先把不是 $8$ 的数字全删掉，最后一定会剩下 $8$，有必胜策略。

但是如果 $8$ 出现次数小于或等于其他数字出现次数之和，则后手会把 $8$ 取完，无必胜策略。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, cnt, a[200005];
signed main()
{
    cin>>n;
    int cnt1=0;
    for(int i=1;i<=n;i++)
    {
        char x;
        cin>>x;
        a[i]=(int)(x-'0');
    }
    for(int i=1;i<=n-10;i++)
    {
        if(a[i]==8)
        {
            cnt++;
            continue;
        }
        cnt1++;
    }
    if(cnt>cnt1)
    {
        cout<<"YES";
    }
    else
    {
        cout<<"NO";
    }
}
```

谢谢观看！

---

## 作者：DERMING (赞：0)

~~又是一道黄色的水题~~

对于这道题，我们可以发现在删数时保证开头为 $8$ 就能先手胜，而我们只能删掉 $n-11$ 个数字，$8$ 要在数列最前，因此从开头开始遍历前 $n-10$ 个数，判断是否能剩下至少一个 $8$。因此我们判断 $8$ 的个数是否大于多余数的一半就行。

关于为什么是 $n-10$ 个数请看下图解释。
![](https://cdn.luogu.com.cn/upload/image_hosting/vx7a2oft.png)

AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000000];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%1d",&a[i]);
	}
	long long cnt8=0,cnto=0;
	for(int i=1;i<=n-10;i++)
	{
		if(a[i]==8)
		{
			cnt8++;
			continue;
		}
		cnto++;
	}
	if(cnt8-cnto>0)
	{
		cout<<"YES\n";
	}
	else
	{
		cout<<"NO\n";
	}
 	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/121373178)


---

## 作者：Raymondzll (赞：0)

## CF1155B Game with Telephone Numbers

结论题。

### 解题思路

由于最后要让开头是 $8$，先手会尽量让所有的数字 $8$ 尽量往前靠，也就是说他会尽可能从前往后删除非 $8$ 的数字，反过来后手会尽可能删掉 $8$。

如果前 $n-11$ 个数字中 $8$ 的个数大于非 $8$ 的个数就 ```YES```，小于就 ```NO```。

等于的时候看第 $n-10$ 个数字是不是 $8$（他们把前面的删完了），是就 ```YES```，不是就 ```NO```。

```cpp
#include <bits/stdc++.h>
using namespace std;
int x,a,b;string s;
int main(){
	cin>>x>>s;
	for(int i=0;i<x-11;i++){
		if(s[i]=='8')a++;
		else b++;
	}
	if(a==b){
		if(s[x-11]=='8')cout<<"YES";
		else cout<<"NO";
	}else if(a>b)cout<<"YES";
	else cout<<"NO";
	return 0;
}

```

---

## 作者：activeO (赞：0)

## 题目大意
 Vasya 和 Petya 轮流在一个串中拿走数 Vasya 先手 Petya 后手，如果在这个串的长度变成 11 时，能使这个串的第一个数字变为 8，输出 YES，否则输出 NO。 

## 思路

随便模拟一下就可以发现 Vasya 会取串中第一个不是 8 的， Petya 会取串中第一个为 8 的，所以只要记录前 $ n-11 $ 个 8 的。为了方便用一个变量 cnt。如果当前数字是 8 就 $ cnt++ $。否则 $ cnt-- $ 最后如果 $ cnt>0 $ 就输出 YES否则输出 NO。

## 代码

```cpp
#include <bits/stdc++.h>//具体如上，就不多解释了

using namespace std;

const int maxn=1e5+10;
int a[maxn],cnt=0;

int main(){
	
	int n;
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%1d",&a[i]);
	
	for(int i=1;i<=n-10;i++){
		if(a[i]==8) cnt++;
		else cnt--;
	}
	
	if(cnt>0) puts("YES");
	else puts("NO");
	
	return 0;
}


```


---

## 作者：Rainy_chen (赞：0)

实际上来说 最后Vasya赢的条件是数字串的第一位是8  
这是因为最后这个串的长度一定是11 而电话号码的判定只需要串的长度为11且第一位是8即可  

于是我们可以很简单地推出Vasya和Petya的策略：
- Petya会尽可能删掉一切有可能成为结尾串的开头的8
- Vasya会尽可能删掉一切有可能成为结尾串的开头的不是8的数

~~于是我们模拟一下过程就好啦x~~

具体来说  
先计算如果Petya不行动 Vasya最多能在结尾串的最前面保留多少个8  
然后再判断Petya能不能把这些8都删掉就好了  

```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;cin>>n;
    string str;cin>>str;
    int ops = (n-11)>>1,tmp=0,tp=0;
    for(int i=0;i<n;i++){
        if(str[i] == '8')++tmp;
        else ++tp;
        if(tp == ops + 1)break;
    }
    if(tmp <= ops)puts("NO");
    else puts("YES");
}
```


---

## 作者：__O_v_O__ (赞：0)

为了方便，我们把 `Vasya` 叫做甲，把 `Petya` 叫做乙。

经过分析，可以得出如下结论：

1. 甲必然从左到右删除一个不是 `8` 的数字，因为甲要使首位为 `8`，必然要清除不是 `8` 的“障碍”。

2. 乙必然从左到右删除 `8`，这个很好理解。

因为最后剩下的是十一位数，所以甲乙都不会删最后十位。

则我们只需考虑前 $n-10$ 位数，分两种情况：

1. 前 $n-10$ 位里 `8` 的数量更多，这时甲删完其他数后，乙还没删完 `8`，甲胜。

2. 前 $n-10$ 位里除了 `8` 以外的数的数量更多，这时乙删完 `8` 后，甲没删完其他数字，乙胜。

则只需统计前 $n-10$ 位里 `8` 的数量和其他数的数量，比较大小即可。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
int n,_8,nu;string s;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//读入优化
	cin>>n>>s;
	afor(i,0,n-11,STB){//循环
		if(s[i]=='8')_8++;//如果是8则变量一自增
		else nu++;//否则变量二自增
	}if(_8>nu)cout<<"YES";//判断
	else cout<<"NO";
	return 0;
}
```

---

## 作者：Claire0918 (赞：0)

定理：序列前 $n - 10$ 项中 $8$ 的数量多于其他数字的数量是先手有必胜策略的充分必要条件。

证明：

记序列前 $n - 10$ 项中 $8$ 的数量为 $c$，其他数字的数量为 $d$。

充分性：

若 $c > d$，则先手可以将前 $n - 10$ 项中所有其他数字取完，而后手无法取完 $8$，先手有必胜策略。

必要性：

显然，序列后 $10$ 项的数无法到达电话号码的第一位。

若 $c \leq d$，则后手可以取完前 $n - 10$ 项中所有的 $8$，而先手不一定可以取完其他数字。所以只有 $c >d$ 时，先手有必胜策略。

Code:
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 1e5 + 10;

int n;
int a[maxn];

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%1d", &a[i]);
	}
	int temp = 0;
	for (int i = 1; i <= n - 10; i++){
		if (a[i] == 8){
			temp++;
		}else{
			temp--;
		}
	}
	if (temp > 0){
		printf("YES");
	}else{
		printf("NO");
	}

return 0;
}
```

---

## 作者：_shine_ (赞：0)

## 题目大意
现在给你一个长度为 $n$ 的字符串 $s$，Petya 和 Vasya 轮流删去 $s$ 中的一个数，请问 Vasya 能否有必胜策略。
## 思路
这道题我们可以发现，无论如何，字符串 $s$ 的长度到了 $11$ 就停止了,所以，Vasya 的最优策略就是把字符串 $s$ 中的 $8$ 尽量往前靠，而 Petya 就是要尽量删去 $s$ 中的 $8$。

这样的话，我们就可以发现，如果 Vasya 要赢，那判断他是否必胜便是来看在前 $n-10$ 个元素中，是否有 $s_i$ 中 $8$ 的个数大于不是 $8$ 的个数（看 $n-10$ 个元素是因为操作机会就只有 $n-11$ 次）。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
signed main(){
	cin >> n >> s;
	int len=s.size();
	int cnt1=0,cnt2=0;
	for(int i=0;i<n-10;++i){
		if(s[i]=='8')cnt1++;
		else cnt2++;
	}
	if(cnt1-cnt2>0)cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
```


---

