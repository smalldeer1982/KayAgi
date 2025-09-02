# Bear and String Distance

## 题目描述

------------
Limak是一只小北极熊。他喜欢单词——只由小写字母构成，长度为n的单词。

他规定dist(s,s')的值为s与s'在26个字母中的间距。如，dist(c,e)=dist(e,c)=2,dist(a,z)=dist(z,a)=25。

而且，当dist两个单词时，其值为dist第一个字母+dist第二个字母+……
如，dist(af,db)=dist(a,d)+dist(f,b)=3+4=7,dist(bear,roar)=16+10+0+0=26。                   

现在，Limak给你一个字母或单词s和值k，令你寻找一个s'使dist(s,s')=k。输出s'。如果没有合适的s'，输出-1。

注意：最好用标准输入输出流，如C++的cin和cout，Java的Scanner/System.out 。

## 样例 #1

### 输入

```
4 26
bear
```

### 输出

```
roar```

## 样例 #2

### 输入

```
2 7
af
```

### 输出

```
db
```

## 样例 #3

### 输入

```
3 1000
hey
```

### 输出

```
-1
```

# 题解

## 作者：TiAmo_qwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF628C)


---
题目大意：

给定长度为 $n$ 的字符串 $s$ 和一个数 $k$，求 $\text{dist}(s,s')=k$。



---

$\text{dist}(s,s')$ 定义：$s$ 与 $s'$ 在 $26$ 个字母中的间距。

当 $s$ 和 $s'$ 是字符时。

例如：$\text{dist}(\texttt{c},\texttt{e})=2$。


---
当 $s$ 和 $s'$ 是字符串时。

例如：$\text{dist}(\texttt{af},\texttt{db})=\text{dist}(\texttt{a},\texttt{d})+\text{dist}(\texttt{f},\texttt{b})=4+3=7$。


---

思路：

我的思路跟楼上楼下的不一样。

先是利用递归来把 $k$ 分解，分解的个数跟字符串 $s$ 的长度相同。例如：字符串 $s$ 的长度为 $4$，$k$ 为 $8$，则可以把 $k$ 分解成 $2+2+2+2$。

判断 $s _ {i}$ 加或减 $k$ 分解成的第 $i$ 个数是否在 $a$ 到 $z$ 之间，若可以，$sum$ 加 $1$，$s _ {i} $ 加或减 $k$ 分解的第 $i$ 个数后的值存进 $s' _ {i} $ 中。若 $sum$ 的值与 $s$ 的长度相同，说明 $s'$ 成立。

成立之后用 $flag$ 存值为 $1$，表示已经找到了，若 $flag$ 是 $0$，就输出 $-1$。否则，输出 $s'$。



---

如果有不会的就私信问我。管理员求过。

---

## 作者：_Passerby_ (赞：0)

[Link-CF](https://codeforces.com/problemset/problem/628/B)
[Link-Luogu](https://www.luogu.com.cn/problem/CF628B)

【题目大意】

给定一个字符串 $s$，统计 $s$ 有多少个字串构成的数能被 $4$ 整除。

【解题思路】

若字串长度为 $1$，只需要扫一遍字符串判断就行。

若字符串长度 $> 1$，考虑 $4$ 的整除条件。

我们知道，如果一个数最后两位组成的两位数能被 $4$ 整除，则这个数能被 $4$ 整除。

这样，我们只需要判断字符串里连续两个数组成的两位数是否能被被四整除，如果能，则可以依次选取它前面的 $0$ 个、$1$ 个、$2$ 个数……

所以，如果 $a_i$ 与 $a_{i + 1}$ 组成的两位数可以被 $4$ 整除，则一共有 $i$ 种选法。统计答案的时候都加起来即可。

形式化地，有答案

$$
Ans = \sum_{i = 1}^{n - 1}[(a[i] \times 10 + a[i+1]) \bmod 4]\times i+\sum_{i=1}^{n}[a[i] \bmod 4]
$$

其中，$a[i]$ 表示 $s[i]$ 构成的整数中，第 $i$ 位的数字。

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF628C)
## 思路
这题可以使用贪心算法。
## 做法
从 $1$ 到 $n$ 依次遍历。对于当前位置，有两个值为 $a$ 与 $b$。$a$ 等于 $\operatorname{dist(a,s_i)}$，$b$ 等于 $\operatorname{dist(z,s_i)}$。如果当前的 $k$ 比 $a$ 和 $b$ 都大，那么就将答案字符串的第 $i$ 位赋值 `a` 和 `z` 中离 $s_i$ 最距离最远的一个。如果 `a` 或 `z` 中有一个离 $s_i$ 的距离比 $k$ 大，那么就找 `a` 到 `z` 中离 $s_i$ 距离为 $k$ 的合法字母，将答案字符串赋值为对应字符。每次操作后，$k$ 都要减去对应值。当 $k$ 为 $0$ 赋值为 $s_i$。如果最后的 $k$ 不为 $0$ 那么输出 `-1`，合法输出答案字符串。 
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be begin()
#define en end()
using namespace std;
typedef long long LL;
typedef int I;
I n,k;
char s[100010],t[100010];//t 为答案字符串 
I main(){
	scanf("%d%d%s",&n,&k,s + 1);
	for(I i = 1;i <= n;i++){
		if(!k){//k 为 0 不需要改变当前位置 
			t[i] = s[i];
			continue;
		}
		I dis1 = abs(s[i] - 'a'),dis2 = abs(s[i] - 'z');//两种选择 
		if(k < dis1 && k < dis2){//k 比它们都小 
			t[i] = s[i] - k;//找到一个距离为 k 的字符 
			k = 0;//更新 k 
		}else if(k < dis1 && k >= dis2){//k 大于其中一个 
			t[i] = s[i] - k;
			k = 0;//更新 k 
		}else if(k < dis2 && k >= dis1){//k 大于其中一个 
			t[i] = s[i] + k;
			k = 0;//更新 k 
		}else{//k 比它们都大 
			k -= max(dis1,dis2);
			if(dis1 >= dis2){
				t[i] = s[i] - dis1;
			}else{
				t[i] = s[i] + dis2;
			}
		}
	}
	if(k){//不存在答案 
		printf("-1\n");
	}else{//输出答案字符串 
		for(I i = 1;i <= n;i++){
			printf("%c",t[i]);
		}
	}
	return 0;
}
```

---

## 作者：Light_az (赞：0)

题目要求构造一个字符串，长度与给定字符串相同，要求每个对应位置的字符差的绝对值之和等于 $k$。

显然贪心，对于 $s_i$，我们尝试选择 $a$ 或者 $z$ 和它匹配，取两者差的绝对值的最大值，如果 $k$ 大于等于这个最大值，说明可以构造，否则直接分类讨论输出，然后将 $k$ 赋值为 $0$ 即可，细节解释在代码中：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define ps push_back
#define sz(x) ((ll)x.size())
#define mem(f,x) memset(f,x,sizeof(f))
#define all(x) x.begin(),x.end()
#define lc id*2
#define rc id*2+1
#define V vector<ll>
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
char ch;
char s[N];
int main(){
	cin>>n>>k;
	F(i,1,n){
		cin>>s[i];
		cnt+=max(abs(s[i]-'a'),abs(s[i]-'z'));//求最值
	}
	if(cnt<k){//最值小于k，一定无解
		cout<<-1;
		return 0;
	}
	F(i,1,n){
		ll mx=max(abs(s[i]-'a'),abs(s[i]-'z'));//取最值
		if(k>=mx){//k大于最值
			if(abs(s[i]-'a')>abs(s[i]-'z')) cout<<"a";//输出最值
			else cout<<"z";
			k-=mx;//减去
		}
		else{
			if(s[i]+k<='z') cout<<(char)(s[i]+k);//输出合法的字符
			else cout<<(char)(s[i]-k);
			k=0;//直接赋值0
		}
	}
	return 0;
}

```


---

## 作者：EthanOI (赞：0)

这个题目说得太复杂了，用一句话概括，就是对于一个字符串 $s$ ，是否存在字符串 $s'$ s.t. $\sum\limits_{i=1}^n\left\vert s[i]-s'[i]\right\vert=k$

事实上，我们可以得到 $\sum\limits_{i=1}^n\left\vert s[i]-s'[i]\right\vert$ 的取值范围为 $[0,\sum\limits_{i=1}^n\left\vert \max(s[i]-\text{a},\text{z}-s[i])\right\vert]$ ，因此，只需求出上限与 $k$ 的大小即可

需要注意的是，当 $k$ 被递减到 $0$ 后，就可以推出循环，并且在减到最小之前时，要判断相减后 $k$ 是否为正

[$\mathcal{AC\text{ }CODE}$](https://www.luogu.com.cn/record/76830737)（ c++ 版）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k;
char c[100010];
signed main()
{
	cin >> n >> k >> c;
	for (int i = 0; i < n; i++)
	{
		if (abs(c[i] - 'a') >= abs(c[i] - 'z'))
		{
			if (k < (c[i] - 'a')) c[i] -= k, k = 0;
			else k -= (c[i] - 'a'), c[i] = 'a';
		}
		else 
		{
			if (k < ('z' - c[i])) c[i] += k, k = 0;
			else k -= ('z' - c[i]), c[i] = 'z';
		}
		if (k == 0) break;
	}
	if (k) cout << -1;
	else cout << c;
	return 0;
}
```
不抄代码，从我做起

---

## 作者：hxhhxh (赞：0)

## 大意

给你一个长度为 $ n $ 字符串 $ s $ 和一个正整数 $ k $ ，求任意一个长度为 $ n $ 字符串 $ t $ ，使得

$$ \sum_{i=1}^n \lvert s_i - t_i \rvert = k $$

或者说不存在。

## 思路

因为题目要求求的是任意一个，所以应该尽量最大化每一个 $ \lvert s_i - t_i \rvert $ ，直到 $ k $ 被耗尽。

如果 $ s_i - {}\! $ `a` $ \leq $ `z` $ \! {} -s_i $ ，那么让 $ t_i $ 取`z`时消耗的 $ k $ 值最多，反之取`a`。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
char ch[1000006];
int dis(char a,char b){
	return abs(a-b);
}
signed main(){
	cin>>n>>k>>ch+1;
	for(int i=1;i<=n;i++){
		if(dis(ch[i],'a')>=dis(ch[i],'z')){
			while(k&&ch[i]>'a'){
				ch[i]--;
				k--;
			}
		}
		else{
			while(k&&ch[i]<'z'){
				ch[i]++;
				k--;
			}
		}
		if(k==0) break;
	}
	if(k) cout<<-1;
	else cout<<ch+1;
	return 0;
}
```

---

