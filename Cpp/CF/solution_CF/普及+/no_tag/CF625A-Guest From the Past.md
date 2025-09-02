# Guest From the Past

## 题目描述

Kolya Gerasimov loves kefir very much. He lives in year 1984 and knows all the details of buying this delicious drink. One day, as you probably know, he found himself in year 2084, and buying kefir there is much more complicated.

Kolya is hungry, so he went to the nearest milk shop. In 2084 you may buy kefir in a plastic liter bottle, that costs $ a $ rubles, or in glass liter bottle, that costs $ b $ rubles. Also, you may return empty glass bottle and get $ c $ ( $ c&lt;b $ ) rubles back, but you cannot return plastic bottles.

Kolya has $ n $ rubles and he is really hungry, so he wants to drink as much kefir as possible. There were no plastic bottles in his 1984, so Kolya doesn't know how to act optimally and asks for your help.

## 说明/提示

In the first sample, Kolya can buy one glass bottle, then return it and buy one more glass bottle. Thus he will drink $ 2 $ liters of kefir.

In the second sample, Kolya can buy two plastic bottle and get two liters of kefir, or he can buy one liter glass bottle, then return it and buy one plastic bottle. In both cases he will drink two liters of kefir.

## 样例 #1

### 输入

```
10
11
9
8
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10
5
6
1
```

### 输出

```
2
```

# 题解

## 作者：封禁用户 (赞：2)

题目传送>>[CF625A](https://www.luogu.com.cn/problem/CF625A)  
### 题意简述：  
- 带 $n$ 卢布去买牛奶喝，买一塑料瓶装需 $a$ 卢布，买一玻璃瓶装需 $b$ 卢布，喝完每瓶玻璃瓶装牛奶后返还玻璃瓶可获得 $c$ 卢布，求最多可喝多少瓶牛奶。  
- $1\le n \le 10^{18}$，$1\le a \le 10^{18}$，$1\le c \le b \le 10^{18}$。
  
### 题目分析:  
此题进行贪心，要想用手中的 $n$ 卢布尽可能买最多的买牛奶喝，优先选择购买实际成本小的牛奶，然后再看剩余卢布是否能买尽可能多的另一种牛奶即可。而对于两种牛奶的实际成本，塑料瓶装牛奶当然就是 $a$ 卢布，而玻璃瓶装牛奶由于每返还一玻璃瓶可获返现 $c$ 卢布，所以玻璃瓶装牛奶的实际成本为 $b-c$ 卢布。 但是需要注意的是，在玻璃瓶装牛奶实际成本小于塑料瓶装牛奶时，我们并不能直接就选择玻璃瓶装牛奶，而是还需判断当前手中卢布是否足以购买一瓶玻璃瓶装牛奶，不然在上一玻璃瓶装牛奶的玻璃瓶已经换现，而此时还未购买新一瓶玻璃瓶装牛奶，你哪来的玻璃瓶换现？    
#### 注意题目数据范围，需要使用 long long。
### Code:  
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;   //类型定义long long为ll，避免频繁使用时累手
int main()
{
	//freopen("milk.in","r",stdin);   //定义输入文件名
	//freopen("milk.out","w",stdout);   //定义输出文件名
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	ll n, a, b, c;   //定义手中卢布，每瓶塑料瓶装牛奶的单价，每瓶玻璃瓶装牛奶的单价，每个玻璃瓶的换现
	ll ans = 0;   //定义可喝牛奶瓶数
	cin >> n >> a >> b >> c;
	if (n>=b && b - c < a)   //可买玻璃瓶装牛奶且其实际成本小于塑料瓶装牛奶的
	{
		ans = (n - b) / (b - c) + 1;   //可喝玻璃瓶装牛奶数
		n -= (b - c) * ans;   //买完玻璃瓶装牛奶后手中余钱
	}
	ans += n / a;   //可喝塑料瓶装牛奶数
	cout << ans;
	//fclose(stdin);fclose(stdout);   //关闭文件
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/iu45k38p.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：yukari1735 (赞：1)

题意为有 $ n $ 块钱，有两种买饮料的方法，第一种花费 $ a $ 元，第二种花费 $ b $ 元但返还 $ c $ 元。求你最多能买几瓶饮料。
不难看出其具有最优子结构性质，即当你在花掉 $ n $ 元钱时的购买数量是从当你花掉 $ n-a $ 元和 $ n-(b-c) $ 时这两个子问题中的最优选择 $ +1 $，但是本题数据 $ 1 \leq n \leq 10^{18} $，我们就要考虑贪心选择。

实际上，我们无须考虑所有子问题的选择，只需要选择 $ a $ 和 $ b-c $ 中花费较少的一种，一直买下去即可。但是第二种饮料其具有一个实际花费 $ b-c $，还有一个形式花费 $ b $，我们在买第二种饮料时必须保证余钱 $ n \geq b $，尽管其实际买一次只花费 $ b-c $ 元钱。

如果 $ n < b $，我们必不能买第二种饮料，只考虑第一种即可。反之如果 $ n \geq b $，我们在买完第二种饮料之后，因为其实际花费与形式花费之间的差值，我们必然会剩下一些余钱，这些钱虽然大于实际花费 $ b-c $，但是却小于形式花费 $ b $，因此这些余钱拿来买第一种饮料。

本题数据需开 $ longlong$。

CODE:
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll n,a,b,c,ans,k;
void input(){
	scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
}
void solve(){
	if(b-c<=a&&n>=b) ans=(n-b)/(b-c)+1,ans+=(n-ans*(b-c))/a;
	else ans=n/a;
}
void output(){
	printf("%lld",ans);
}
int main(){
	input();
	solve();
	output();
	return 0;
}
```


---

## 作者：_YyD_ (赞：0)

显然是贪心，可以把第二种买法看成只要 $b-c$ 元，当然，必须要又 $b$ 元。

这样，就只需要对比 $a$ 和 $b-c$ 就行了，尽量买小的。

核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a,b,c;
int main(){
	cin>>n>>a>>b>>c;
	if(b-c<a&&b<=n)
	t=(n-b)/(b-c)+1,
	n-=t*(b-c);//一个细节处理，这样可以保证每次有足够（>b）的钱来买  
	cout<<t+n/a;
	return 0;
}
```


---

## 作者：_lfxxx_ (赞：0)

**题目传送门：[CF625A Guest From the Past](https://www.luogu.com.cn/problem/CF625A)**
### 题意：
~~其实就是翻译~~

你有 $n$ 块钱，有两种买饮料的方法，第一种花费 $a$ 元，第二种花费 $b$ 元但返还 $c$ 元。求你最多能买几瓶饮料。

### 思路：
不难看出，用贪心做。如果 $b-c<a$ ，就一直买第二种，直到不能买为止。剩下的钱再买第一种。

否则就只买第一种。

于是我们首次可以打出以下代码（主要的）：
```cpp
if(b-c<a)
	while(n>=b){
		n-=b-c;
		s++;
	}
cout<<s+n/a;
```
显然， $10^{18}$ 的数据范围告诉我们这样会 T ，所以我们必须将中间的 $\texttt{while}$ 改成除法。（$\texttt{while}$ 浪费了大量的时间）

首先，每次减了 $(b-c)$ 所以除数为 $(b-c)$ 。被除数也挺好想的，其实就是 $(n-b)$ 。但是，这没有算上第一次，因此我们还要 $+1$ 。所以这一部分代码可以这样写：
```cpp
if(n>=b&&b-c<a){//n不大于b买不起
		s=(n-b)/(b-c)+1;
		n-=(b-c)*s;//这行代码的意思是买完后还有多少钱
	}
```
整体的代码我就不贴了，剩下的代码挺简单的。

---

## 作者：封禁用户 (赞：0)

题目传送门：[CF625A Guest From the Past](https://www.luogu.com.cn/problem/CF625A)

**题目大意：** 一瓶饮料有两种买法，可以花费$a$元买一瓶，也可以用$b$元买一瓶然后获得$c$元，一开始有$n$元，求最多能买多少瓶饮料。

**题解：** 贪心，如果$b-c<a$，且$n\ge b$，那就买$b$元的，$n$先减去$b$再看看够买多少瓶，然后再加一瓶，余款再购买$a$元的。（貌似是红题？）

$Code:$

```pascal
var n,a,b,c,ans:int64;
begin
  readln(n,a,b,c);
  if(b-c<a) and (n>=b) then begin ans:=(n-b) div (b-c)+1;dec(n,(b-c)*ans); end;
  inc(ans,n div a);
  write(ans);
end.
```


---

