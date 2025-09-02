# Devu and Partitioning of the Array

## 题目描述

Devu being a small kid, likes to play a lot, but he only likes to play with arrays. While playing he came up with an interesting question which he could not solve, can you please solve it for him?

Given an array consisting of distinct integers. Is it possible to partition the whole array into $ k $ disjoint non-empty parts such that $ p $ of the parts have even sum (each of them must have even sum) and remaining $ k $ - $ p $ have odd sum? (note that parts need not to be continuous).

If it is possible to partition the array, also give any possible way of valid partitioning.

## 样例 #1

### 输入

```
5 5 3
2 6 10 5 9
```

### 输出

```
YES
1 9
1 5
1 10
1 6
1 2
```

## 样例 #2

### 输入

```
5 5 3
7 14 2 9 5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 3 1
1 2 3 7 5
```

### 输出

```
YES
3 5 1 3
1 7
1 2
```

# 题解

## 作者：Naganorhara_Yoimiya (赞：1)

# C:Devu and Partitioning of the Array
## 题目大意
给出一个数组，要求将其划分为 $k$ 份，其中 $p$ 份的和为偶数，剩下的和为奇数。求有无方案满足以及若满足，输出一种可能的方案。
## 思路
我们先把偶数**一个一个**（指 $p$ 份中每份只放 $1$ 个偶数）填满 $p$ 格，如果偶数不够，就拿两个奇数凑上去。（因为奇数 + 奇数 = 偶数）。

接下来，用类似的思路填满 $k-p$ 格奇数，如果奇数不够用，直接输出 ``NO`` 即可。 

接下来，看有没有剩下：

如果偶数有多，那么随便放（我这里是把多的偶数加在了和是偶数这里），因为偶数与任何数相加都不会改变奇偶。

如果奇数有多，那么两个两个放，因为两个奇数和为偶数。

直接把剩下的数堆在一个格子里就可以了，因为偶数 + 偶数 = 偶数，加多少都不会影响原来的奇偶性。

但是如果最后剩下 $1$ 个奇数，输出无解。

于是，按照上述思路，我们得到了以下代码：
```cpp
int main(){
	...
	//偶数放满 
	while(cnto < p && o.size() > 0){
		int e = o.size();
		ou[++cnto].push_back(o[e-1]);
		o.pop_back();
	}
	//偶数不够，奇数凑 
	if(cnto < k){
		while(cnto < p && j.size() > 1){
			int e = j.size();
			cnto++;
			ou[cnto].push_back(j[e-1]);
			j.pop_back();
			ou[cnto].push_back(j[e-2]);
			j.pop_back();
		}
	}
	//偶数实在凑不够了 
	if(cnto < p){
		cout << "NO";
		return 0;
	}
	int cntj = 0;
	//奇数处理完 
	while(cntj < k - p && j.size() > 0){
		int e = j.size();
		cntj++;
		ji[cntj].push_back(j[e-1]);
		j.pop_back();
		if(cntj == k - p) break;
	}
	if(j.size() == 0 && cntj < k - p) {
			cout << "NO";
			return 0;
		} 
	//处理剩余偶数 
	while(o.size() > 0){
		int e = o.size();
		ou[1].push_back(o[e-1]);
		o.pop_back();
	}
	//处理剩余奇数
	while(j.size() > 1){
		int e = j.size();
		ou[1].push_back(j[e-1]);
		j.pop_back();
		ou[1].push_back(j[e-2]);
		j.pop_back();
	}
	if(j.size() != 0) cout << "NO";
	else {
		cout << "YES\n";
		...
	}
	return 0;
}
```
满心欢喜地交了上去，发现 ``WA on test 60``。

这是为什么呢？我们看一看，此时 $p=0$。

我们重新审视一下我们的思路：
```
如果偶数有多，那么随便放（我这里是把多的偶数加在了和是偶数这里），因为偶数与任何数相加都不会改变奇偶。
```
那么，偶数是 $0$ 呢？我们只能堆在奇数这一边。

所以，我们应该将有数多余情况进行进一步处理：

如果不能堆在和为偶数处，我们就堆在和为奇数处，否则放在和为偶数处。

这下就可以 AC 了。
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
int n,p,k;
int a[maxn+100];
vector<int> j,o,ji[maxn+100],ou[maxn+100];
bool vis[maxn+100];
int main(){
	//ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> k >> p;
	for(int i = 1;i <= n;i++) cin >> a[i];
	int cnto = 0;
	memset(vis,0,sizeof(vis));
	for(int i = 1;i <= n;i++){
		if(a[i] % 2 == 0) o.push_back(a[i]);
		else j.push_back(a[i]); 
	}
	//偶数放满 
	while(cnto < p && o.size() > 0){
		int e = o.size();
		ou[++cnto].push_back(o[e-1]);
		o.pop_back();
	}
	//偶数不够，奇数凑 
	if(cnto < k){
		while(cnto < p && j.size() > 1){
			int e = j.size();
			cnto++;
			ou[cnto].push_back(j[e-1]);
			j.pop_back();
			ou[cnto].push_back(j[e-2]);
			j.pop_back();
		}
	}
	//偶数实在凑不够了 
	if(cnto < p){
		cout << "NO";
		return 0;
	}
	int cntj = 0;
	//奇数处理完 
	while(cntj < k - p && j.size() > 0){
		int e = j.size();
		cntj++;
		ji[cntj].push_back(j[e-1]);
		j.pop_back();
		if(cntj == k - p) break;
	}
	if(j.size() == 0 && cntj < k - p) {
		cout << "NO";
		return 0;
	} 
	//处理剩余偶数 
	while(o.size() > 0){
		int e = o.size();
		if(p != 0){
			ou[1].push_back(o[e-1]);
			o.pop_back();
		}
		else{
			ji[1].push_back(o[e-1]);
			o.pop_back();
		}
	}
	//处理剩余奇数
	while(j.size() > 1){
		int e = j.size();
		if(p != 0){
			ou[1].push_back(j[e-1]);
			j.pop_back();
			ou[1].push_back(j[e-2]);
			j.pop_back();
		}
		else{
			ji[1].push_back(j[e-1]);
			j.pop_back();
			ji[1].push_back(j[e-2]);
			j.pop_back();
		}
	}
	if(j.size() != 0) cout << "NO";
	else {
		cout << "YES\n";
		for(int i = 1;i <= k - p;i++){
			cout << ji[i].size() << " ";
			for(int j = 0;j < ji[i].size();j++){
				cout << ji[i][j] << " ";
			}
			cout << '\n';
		}
		for(int i = 1;i <= p;i++){
			cout << ou[i].size() << " ";
			for(int j = 0;j < ou[i].size();j++){
				cout << ou[i][j] << " "; 
			}
			cout << '\n';
		}
	}
	return 0;
}
```

---

## 作者：fyn1234 (赞：1)

题目传送门：[（洛谷）](https://www.luogu.com.cn/problem/CF439C)[
（CodeForces）](https://codeforces.com/problemset/problem/439/C)

~~[可能更好的食用体验](https://www.luogu.com.cn/article/gresns4q)~~

## 题意
将 $n$ 分成 $k$ 堆，要求 $p$ 堆的每堆中所有数之和为偶数，其余 $k-p$ 堆的每堆中所有数之和为奇数。

## solution
首先将奇数和偶数分别存储到两个队列（也可以是其他的数据结构）里，并且记下它们的个数。

接着判断一下 `NO` 的情况，有以下三种：

- **奇数个数不足 $k-p$ 个**（因为只能用奇数+奇数组合成偶数，而偶数无法组合出奇数）

- **有多余的奇数**（在奇数够了之后可以用每两个奇数可以组合成一个偶数，但是如果奇数的个数是奇数就会多出来一个）

- **偶数个数不足**（如果偶数个数+（剩余的奇数个数 $\div 2$） $<p$ 那么无解）

接下来我们往 $k-p$ 堆中每堆放一个奇数，剩下的 $p$ 堆中，每堆放一个偶数。（如果有偶数就放，如果没有就放两个奇数）

如果有剩余的话，直接无脑堆到第一个就行了（堆偶数不会改变奇偶性，而剩余的奇数又有偶数个）。

最后输出就好了。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
queue<int> ou,ji;
long long oou,jji;
vector<int> ans[N];
int main(){
	long long n,k,p;
	cin>>n>>k>>p;
	for(int i = 1;i<=n;i++){//输入
		long long x;
		cin>>x;
		if(x%2==0){
			++oou;
			ou.push(x);
		} 
		else {
			++jji;
			ji.push(x);
		}
	}
	long long need = k-p;
	if(jji<need || (jji-need)%2!=0 || oou+(jji-need)/2<p){//判断无解的情况
		cout<<"NO";
		return 0;
	}
	for(int i = 1;i<=need;i++){//放奇数
		ans[i].push_back(ji.front());
		ji.pop();
	}
	for(int i = need+1;i<=k;i++){//放偶数
		if(!ou.empty()){
			ans[i].push_back(ou.front());
			ou.pop();
		}
		else{
			ans[i].push_back(ji.front());
			ji.pop();
			ans[i].push_back(ji.front());
			ji.pop();
		}
	}
	while(!ou.empty()){//放剩余的偶数
		ans[1].push_back(ou.front());
		ou.pop();
	}
	while(!ji.empty()){//放剩余的奇数
		ans[1].push_back(ji.front());
		ji.pop();
	}
	cout<<"YES"<<endl;
	for(int i = 1;i<=k;i++){
		cout<<ans[i].size();
		for(auto j:ans[i]) cout<<" "<<j;
		cout<<endl;
	}
	return 0;
}

```

## 结语
完结撒花！（如有不严谨之处还望大佬们帮忙指出）

---

## 作者：huangxianghui (赞：1)

# 题目大意
将一堆数分成k堆，其中 $p$ 堆是偶数堆（和为偶数）， $k-p$ 堆是奇数堆（简洁明了）
# solution
这道题的坑点真的多，我也就交了三十多次而已

首先判断NO：
#### 1.奇数总共不超过 $k-p$ 个（你奇数都不够，你能用偶数凑出奇数？）
#### 2.所有数总和的奇偶性和 $k-p$ 不一样（总和取决于奇数有几个，奇数堆有奇数个，你再怎么样你也无法让总和变成偶数的，同理，反过来也一样）
#### 3.（此处假设偶数有 $a$ 个，奇数有 $b$ 个）当 $b-2*(p-a)<(k-p)$ 时( $p>a$ )，无解
这里解释起来有点麻烦：假设我们每个偶数堆都只放一个偶数，结果还是凑不够p个偶数堆，那么只能用奇数凑，两个奇数凑成一个偶数，但是这样就有可能导致后面奇数堆需要的奇数不够了，这时候也需要输出NO

------------
然后由于本题特性(spj)，所以这个堆就我们自己构造了

下面看代码

```
#include<bits/stdc++.h>
#define f(i,a,b) for (int i=a;i<=b;i++)
#define ll long long
using namespace std;
const int maxn=1e5+10;
int n,k,p,num;
int a[maxn],len1,len2;
bool l[maxn];
vector<int> qi,ou;
ll sum;
inline ll read()
{
	ll l=0,f=1;
	char c=getchar();
	while (c<'0' || c>'9')
	{
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0' && c<='9') l=(l<<3)+(l<<1)+(c^48),c=getchar();
	return l*f;
}
int main()
{
	n=read(),k=read(),p=read();
	f(i,1,n)
	{
		a[i]=read(),sum+=a[i];
		if (a[i]%2) qi.push_back(a[i]);
		else ou.push_back(a[i]);
	}
	len1=qi.size(),len2=ou.size();
	if (len1<k-p || sum%2!=(k-p)%2) cout<<"NO";
	else
	{
		if (len2<p && (len1-((p-len2)*2))<(k-p)) cout<<"NO";
		else
		{
			cout<<"YES"<<endl;
			num=0;
			int po=1;
			while (po<p && num<len2) cout<<1<<' '<<ou[num]<<endl,po++,num++;//前面所有偶数堆只放一个偶数
			if (num<len2)//偶数多出来了
			{
				if (po<=p)//前面还没塞满
				{
					cout<<len2-num+(((len1-(k-p))>0)?(len1-(k-p)):0)<<' ';//连着多出来的奇数全部给他塞到最后一个偶数堆，由于前面已经判断过NO，所以这里相安无事。
					for (int i=num; i<len2; i++) cout<<ou[i]<<' ';
					for (num=0; num<len1-(k-p); num++) cout<<qi[num]<<' ';
					cout<<endl;
					for (; num<len1; num++) cout<<1<<' '<<qi[num]<<endl;//剩下的奇数堆每堆只放一个奇数
				}
				else//前面塞满了
				{
					cout<<len2-num+1<<' ';//偶数塞到下一个奇数堆，再配一个奇数
					for (int i=num; i<len2; i++) cout<<ou[i]<<' ';
					cout<<qi[0]<<' ';
					cout<<endl;
					for (num=1,po=1; po<(k-p); po++,num++) cout<<"1 "<<qi[num]<<endl;//只放一个奇数
					if (len1-num>0)//多出来的放到最后一堆
					{
						cout<<len1-num<<' ';
						for (; num<len1; num++) cout<<qi[num]<<' ';
					}
				}
			}
			else//偶数少了
			{
				for (num=0; num<len1 && po<p; num+=2,po++) cout<<2<<' '<<qi[num]<<' '<<qi[num+1]<<endl;//用奇数凑偶数
				if (po<=p && (len1-num)-(k-p)>0)
				{
					cout<<(len1-num)-(k-p)<<' ';
					for (; num<len1-(k-p); num++) cout<<qi[num]<<' ';//多出来的放到最后一个偶数堆，后面相安无事
					cout<<endl;
					for (; num<len1; num++) cout<<1<<' '<<qi[num]<<endl;
				}
				else
				{
					for (po=0; po<(k-p-1); num++,po++) cout<<1<<' '<<qi[num]<<endl;//跟前面一样
					cout<<len1-num<<' ';
					for (; num<len1; num++) cout<<qi[num]<<' ';//仍然丢到最后一堆
				}
			}
		}
	}
}
```
反正这么零零总总算下来，坑点还是比较多的，只要构造的时候把多出来的数丢到最后一堆就没有什么太大的问题

最后来一组奇奇怪怪的hack数据：
```
3 2 0
1 2 3
```


---

## 作者：longlong_int (赞：0)

## 题目大意

给定 $n$ 个整数，要求把这些整数分成 $k$ 个部分，记 $s_i$ 为第 $i$ 个部分中所有数之和，则这 $k$ 个部分的要求为：$s_1,s_2,s_3,\dots,s_p$ 都为偶数，$s_{p+1},s_{p+2},\dots,s_k$ 均为奇数。

## 思路

### 判断 YES/NO

不难发现，$s_1+s_2+s_3+\dots+s_p$ 一定为偶数，但是 $s_{p+1}+s_{p+2}+\dots+s_k$ 的奇偶性取决于 $k-p$ 的奇偶性。

所以，$s_1+s_2+s_3+\dots+s_k$ 和 $k-p$ 除以 $2$ 同余。

所以我们算出数列的所有整数之和，然后看一下是否和 $k-p$ 同余就可以了。

**注意判断出 `YES` 后不能直接输出，因为后面可能出现奇偶性对了但不够分的情况。我这里是手动模拟的 `stringstream` 做法。**

### 分偶数

我们在输入时把奇数、偶数先分别筛出来，存储在两个 `std::vector` 中。

这部分不难，如果偶数还没用完，那我们就拿出一个偶数。如果偶数用完了我们就拿出两个奇数（这时候奇数用完了就说明不够分，直接输出 `NO`）。

**注意我们的循环条件是 `i < p`，因为有可能出现 $\textbf{\textit{k\space=\space p}}$ 的情况，如果不做处理会少一组数（Sample #24）。**

### 分奇数

先分 $k-p-1$ 组，每组一个奇数。最后一组把剩下的奇数和偶数一锅端，反正奇偶性验证过。

注意当 $k \neq p$ 时补一个偶数。

## CODE

**十年 OI 一场空，不开_______见祖宗。（填空）**

```CPP
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

const int N = 1e5 + 10;
int arr[N];
vector<int> odd, even;

signed main()
{
	int n, k, p;
	cin >> n >> k >> p;
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
		sum += arr[i];
		if (arr[i] & 1)
			odd.push_back(arr[i]);
		else
			even.push_back(arr[i]);
	}
	string s;
	if (((k - p) & 1) ^ (sum & 1))
	{
		cout << "NO\n";
		return 0;
	}
	else
		s += "YES\n";

	for (int i = 1; i < p; i++) 
	{
		if (even.empty())
		{
			if (odd.empty())
			{
				cout << "NO" << endl;
				return 0;
			}
			int a = odd.back();
			odd.pop_back();
			if (odd.empty())
			{
				cout << "NO" << endl;
				return 0;
			}
			int b = odd.back();
			odd.pop_back();
			s += "2 " + to_string(a) + " " + to_string(b) + endl;
		}
		else
		{
			s += "1 " + to_string(even.back()) + endl;
			even.pop_back();
		}
	}

	if (k != p)
	{
		if (p != 0)
		{
			if (even.empty())
			{
				if (odd.empty())
				{
					cout << "NO" << endl;
					return 0;
				}
				int a = odd.back();
				odd.pop_back();
				if (odd.empty())
				{
					cout << "NO" << endl;
					return 0;
				}
				int b = odd.back();
				odd.pop_back();
				s += "2 " + to_string(a) + " " + to_string(b) + endl;
			}
			else
			{
				s += "1 " + to_string(even.back()) + endl;
				even.pop_back();
			}
		}
		for (int i = 1; i <= (k - p - 1); i++)
		{
			if (odd.empty())
			{
				cout << "NO" << endl;
				return 0;
			}
			s += "1 " + to_string(odd.back()) + endl;
			odd.pop_back();
		}
	}

	if ((odd.size() + even.size()))
	{
		s += to_string(odd.size() + even.size()) + " ";
		for (int i : odd)
		{
			s += to_string(i) + " ";
		}
		for (int i : even)
		{
			s += to_string(i) + " ";
		}
	}
	cout << s << endl;
	return 0;
}
```

# THE END

---

## 作者：ZLCT (赞：0)

# CF439C Devu and Partitioning of the Array
## 题目翻译
给定 $n$ 个数，要把他们分成 $k$ 堆，保证其中 $p$ 堆的和是偶数，其余是奇数，问是否能有一种合法方案，若有则构造一组。
## solution
首先我们不难观察到所有的偶数都是凑数的，因为加上一个偶数是不会改变数的奇偶的。\
由此我们可以进一步推出，我们所有数的和必须和 $k-p$ 的奇偶性相同。这不难理解，我们把所有堆都加起来，一共若有奇数个奇数堆，则最终所有数的和一定是奇数，否则一定是偶数。\
接下来由于题目没有限制每堆的个数，所以一个很直观的想法就是先把每堆都放 $1/2$ 个元素使满足条件，剩下元素的和反正是偶数，随便放一堆里就行。\
奇数堆好说，每堆放一个奇数即可，若奇数数量不够那就肯定无解了，因为偶数不可能凑出奇数。\
在放偶数堆时我们要分两种情况：一个偶数，两个奇数。\
所以只有这两种加起来数量还不够时才无解。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,p;
vector<int>odd,even;
vector<int>ans[112345];
signed main(){
    cin>>n>>k>>p;p=k-p;
    for(int i=1;i<=n;++i){
        int x;cin>>x;
        if(x&1)odd.push_back(x);
        else even.push_back(x);
    }
    int len1=(int)odd.size(),len2=(int)even.size();
    if(len1+p&1){
        cout<<"NO\n";
        return 0;
    }
    if(p>len1){
        cout<<"NO\n";
        return 0;
    }
    for(int i=1;i<=p;++i){
        ans[i].push_back(odd[--len1]);odd.pop_back();
    }
    if(len1/2+len2<k-p){
        cout<<"NO\n";
        return 0;
    }
    cout<<"YES\n";
    for(int i=p+1;i<=k;++i){
        if(len2){ans[i].push_back(even[--len2]);even.pop_back();}
        else{
            ans[i].push_back(odd[--len1]);odd.pop_back();
            ans[i].push_back(odd[--len1]);odd.pop_back();
        }
    }
    while(len1){ans[k].push_back(odd[--len1]);odd.pop_back();}
    while(len2){ans[k].push_back(even[--len2]);even.pop_back();}
    for(int i=1;i<=k;++i){
        cout<<ans[i].size()<<' ';
        for(int j:ans[i])cout<<j<<' ';
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：Last_kiss_Snow_Dog6 (赞：0)

一个模拟题，很容易想到把奇数和偶数分开，然后注意奇数与偶数之间的相加后的奇偶性。然后，模拟分配过程。规定这 $ k-p $ 个奇数数组中每个只有一个奇数，所以先分配这 $ k-p $ 个数组。之后仅利用偶数分配好 $ p $ 个偶数组，之后把剩下的奇数每两个分配到一个偶数数组中。这样做好处在于不需要分好多种情况讨论，只需在分配过程中看是否无法分配，据此判断，也不需要刻意构造一个放剩余元素的数组注意 ：$ p $ 等于 $ 0 $ 的时候需要特判，因为要分配，所以需要循环这 $ p $ 个偶数数组（下标从零开始）。


```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = (int)1e5 + 5;

int n, k, p;
int ar[maxn];
int a[maxn], b[maxn];
int cnt1, cnt2;
vector<int> vt[maxn];

bool judge()
{
    if(p == 0)
    {
        for(int i = 0; i < cnt2; ++i) vt[0].push_back(b[i]);
        int mv = 0;
        for(int i = 0; i < k; ++i)
        {
            if(mv == cnt1) return false;
            vt[i].push_back(a[mv++]);
        }
        if((cnt1 - k) & 1) return false;
        else
        {
            for(int i = k; i < cnt1; ++i) vt[0].push_back(a[i]);
        }
    }
    else
    {
        int mv1 = 0;
        int mv2 = 0;
        for(int i = k - 1; i > p - 1; --i)
        {
            if(mv1 == cnt1) return false;
            vt[i].push_back(a[mv1++]);
        }

        int t = p;
        while(mv2 < cnt2)
        {
            t %= p;
            vt[t].push_back(b[mv2++]);
            t++;
        }

        while(mv1 < cnt1)
        {
            t %= p;
            if(mv1 != cnt1 - 1)
            {
                vt[t].push_back(a[mv1++]);
                vt[t].push_back(a[mv1++]);
            }
            else return false;
            t++;
        }
        if(vt[p - 1].size() == 0) return false;
        return true;
    }
}

int main()
{
    scanf("%d%d%d", &n, &k, &p);
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &ar[i]);
        if(ar[i] & 1) a[cnt1++] = ar[i];
        else b[cnt2++] = ar[i];
    }
    if(judge())
    {
        printf("YES\n");
        for(int i = 0; i < k; ++i)
        {
            printf("%d", vt[i].size());
            for(int j = 0; j < vt[i].size(); ++j) printf(" %d", vt[i][j]);
            putchar('\n');
        }
    }
    else printf("NO\n");
    return 0;
}


```

---

## 作者：Plozia (赞：0)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/113766117)

以下用 $ev$ 表示奇数堆的个数，$od$ 表示偶数堆的个数，不考虑无解的情况。

首先这里有三个式子：

1. 奇数+奇数=偶数
2. 偶数+偶数=偶数
3. 奇数+偶数=奇数

所以我们可以看见，对于奇数堆而言，我们需要有奇数个奇数来填充每一堆，而这是 CF 的构造题，于是对于奇数堆：我们取出 $ev$ 个奇数填到每一堆里面。

那么还有数字剩下来，我们要怎么做呢？

对于偶数堆：我们先用一个偶数填充，偶数不够了就用两个奇数填充。

对于奇数堆：在偶数堆填完之后把剩下所有的全部填入第一堆奇数堆。

特别的，当 $od=0$ 时，直接填到第一堆。

当 $ev=0$ 时，先用偶数，再用奇数填充。

现在考虑无解情况。

1. 奇数堆个数太多，$ev$ 不够用。
2. 奇数堆填完之后，剩下的奇数个数为奇数。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, k, p, cnteven, cntodd, ev, od;
vector <int> even, odd, ans[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void work(int Point1, int Point2)
{
	while (Point2 < cntodd) ans[1].push_back(odd[Point2++]);
	if (cnteven == Point1 || !((cnteven - Point1) & 1))
	{
		while (Point1 < cnteven) ans[1].push_back(even[Point1++]);
		printf("YES\n");
		for (int i = 1; i <= k; ++i)
		{
			printf("%d ", ans[i].size());
			for (int j = 0; j < ans[i].size(); ++j) printf("%d ", ans[i][j]);
			printf("\n");
		}
	}
	else printf("NO\n");
}

int main()
{
	n = read(), k = read(), p = read();
	int Point1 = 0, Point2 = 0;
	for (int i = 1; i <= n; ++i)
	{
		int t = read();
		if (t & 1) {even.push_back(t); cnteven++;}
		else {odd.push_back(t); cntodd++;}
	}
	od = p, ev = k - p;
	if (cnteven < ev) {printf("NO\n"); return 0;}
	for (int i = 1; i <= ev; ++i)
	{
		int num = i;
		ans[num].push_back(even[Point1]); Point1++;
	}
	for (int i = 1; i <= od; ++i)
	{
		int num = ev + i;
		if (Point2 < cntodd)
		{
			ans[num].push_back(odd[Point2]); Point2++;
		}
		else if (Point1 + 1 < cnteven)
		{
			ans[num].push_back(even[Point1++]);
			ans[num].push_back(even[Point1++]);
		}
		else {printf("NO\n"); return 0;}
	}
	if (od == 0) {work(Point1, Point2); return 0;}
	while (Point2 < cntodd)
	{
		ans[ev + 1].push_back(odd[Point2++]);
	}
	if (((cnteven - Point1) & 1) && cnteven != Point1) {printf("NO\n"); return 0;}
	else while (Point1 < cnteven)
	{
		ans[ev + 1].push_back(even[Point1++]);
	}
	printf("YES\n");
	for (int i = 1; i <= k; ++i)
	{
		printf("%d ", ans[i].size());
		for (int j = 0; j < ans[i].size(); ++j) printf("%d ", ans[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Alarm5854 (赞：0)

这道题目题意比较好理解，然而有很多的坑点，需要注意。

------
首先是判无解，无解的条件如下：

- 序列里面的奇数个数小于 $k-p$。
- 序列里面的奇数个数的奇偶性与 $k-p$ 不同。
- 序列里面的偶数个数加上奇数个数与 $k-p$ 的差的一半之后的和不足 $p$。

第一点是比较好理解的，毕竟偶数不会产生奇数。

第二点是如果说奇偶性不同，那么选完 $k-p$ 个奇数之后，必定还剩奇数个奇数，这些数是不可能全部变为偶数的。  

第三点就是偶数数量不够，而至少要两个奇数才能凑成一个偶数，这时候如果将奇数个数用到只剩 $k-p$ 个后，偶数的个数仍然不足 $p$，那么就显然无解。

------
判完无解之后，处理有解部分，这时候 $k=p$ 要特别处理，因为当 $k\neq p$ 时，可以用一部分偶数来加入奇数堆里面，而 $k=p$ 的时候就不行了，因为没有奇数了。这时先处理前面 $k-1$ 个，这些按照先把偶数一个一个的输出，如果不够就拿奇数两个两个拼在一起输出，当输出 $k-1$ 个数的时候，把剩余部分全部一起输出。

其他情况下，偶数的输出如上，只不过这时候是把 $p$ 个数都按照上面的一个一个的输出偶数或两个两个的输出奇数，接下来处理输出奇数的时候，定义一个临时变量，将这个变量加上序列中剩余的数，当它为奇数的时候就输出并清零临时变量，这样处理前 $k-p-1$ 个奇数，最后一个奇数就是拿剩余部分一起输出的。

代码如下（又臭又长）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int read() {
	char c = 0;
	int x = 0, f = 1;
	while (!isdigit(c = getchar()))
		f -= 2 * (c == '-');
	while (isdigit(c)) {
		x = x * 10 + f * (c - 48);
		c = getchar();
	}
	return x;
}
vector<int> vec;
int n, k, p, s, odd, cnt, det, tot, a[N], v[N], b[N];
void out() {
	int sz = vec.size();
	printf("%d ", sz);
	for (int i = 0; i < sz; ++i)
		printf("%d ", vec[i]);
	puts("");
	vec.clear();//顺便清空数组
}
void solve() {//单独处理k=p
	for (int i = 1; i <= n; ++i) {
		if (cnt == p - 1)
			break;
		if (a[i] & 1)
			continue;
		v[i] = 1;
		printf("1 %d\n", a[i]);
		++cnt;
	}
	for (int i = 1; i <= n; ++i) {//把未用的数据加入b数组
		if (v[i])
			continue;
		b[++tot] = i;
	}
	det = 1;
	while (cnt < p - 1) {
		s ^= a[b[det]] & 1;
		vec.push_back(a[b[det]]);
		++det;
		if (!s) {
			++cnt;
			out();
		}
	}
	for (int i = det; i <= tot; ++i)
		vec.push_back(a[b[i]]);
	out();
}
int main() {
	n = read();
	k = read();
	p = read();
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
		if (a[i] & 1)
			++odd;
	}
	if (odd + p < k) {//奇数个数小于k-p
		puts("NO");
		return 0;
	}
	if ((odd + p - k) & 1) {//奇偶性不同
		puts("NO");
		return 0;
	}
	if (n - odd + (odd + p - k) / 2 < p) {//偶数个数不够
		puts("NO");
		return 0;
	}
	puts("YES");//一定有解
	if (p == k) {
		solve();
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		if (cnt == p)
			break;
		if (a[i] & 1)
			continue;
		v[i] = 1;
		printf("1 %d\n", a[i]);
		++cnt;
	}
	for (int i = 1; i <= n; ++i) {
		if (v[i])
			continue;
		b[++tot] = i;
	}
	det = 1;
	while (cnt < p) {
		s ^= a[b[det]] & 1;
		vec.push_back(a[b[det]]);
		++det;
		if (!s) {
			++cnt;
			out();
		}
	}
	p = k - p;
	cnt = 0;
	if (!p)
		return 0;
	while (cnt < p - 1) {//还要处理最后一个奇数，所以只处理前p-1个
		s ^= a[b[det]] & 1;
		vec.push_back(a[b[det]]);
		++det;
		if (s) {
			++cnt;
			out();
			s = 0;
		}
	}
	while (det <= tot) {
		vec.push_back(a[b[det]]);
		++det;
	}
	out();
	return 0;
}
```

---

