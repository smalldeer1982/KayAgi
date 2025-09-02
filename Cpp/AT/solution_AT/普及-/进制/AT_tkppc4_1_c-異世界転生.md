# 異世界転生

## 题目描述

给你一个十进制数 $n$ 和一个 $m$ 进制数 $x$，已知 $n_{(10)}=x_{(m)}$，请你求出 $m$ 的值，数据保证有解。

## 说明/提示

$n$ 是一个十进制整数。

$9\leq n\leq 10^{18}$。

$1\leq |x| \leq60$。

$2\leq m\leq 10$，且 $m$ 是一个整数。

translated by @[zhuweiqi](https://www.luogu.com.cn/user/909294)。

## 样例 #1

### 输入

```
334 334```

### 输出

```
10```

## 样例 #2

### 输入

```
5191491411 46533757523```

### 输出

```
8```

# 题解

## 作者：_7Mr (赞：3)

# 思路
我们枚举 $m$ 每次枚举的时候，将当前进制相对应的数算出来，看看是否与 $x$ 相等，如果相等就直接输出，否则就到下一个进制。

这里有个小技巧，我们可以直接用字符串类型来判断，大大节省了码量。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF INT_MAX
using namespace std;
int n,m;
string x;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>x;
	for(m=2;m<=10;m++){//枚举
		string a;
		int nn=n;//转换成相对应的数
		while(nn){
			a=char(nn%m+'0')+a;
			nn/=m;
		}
		if(a==x){//看看是否相等
			cout<<m<<endl;
			return 0;
		}
	}
	return 0;
}

```

---

## 作者：liupan2010 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_tkppc4_1_c)

容易看出，这题实际上是一道 $10$ 进制转 $m$ 进制的板子题。

具体的进制转换的过程可见 [B3619 题解](https://www.luogu.com.cn/problem/solution/B3619)。

然后从 $2$ 到 $10$ 枚举，将 $n$ 转换成 $m$ 进制后再与 $x$ 做对比，满足要求输出即可。

注意 $9\le n\le10^{18}$，所以要开 $\texttt{long long}$。还有，输出要换行！

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
string dic="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string ten_to_n(long long x,int base){
	string ans="";
	while(x){
		ans+=dic[x%base];
		x/=base;
	}
	reverse(ans.begin(),ans.end());
	return ans;
}
long long x;
string y;
int main(){
	cin>>x>>y;
	for(int i=2;i<=10;i++){
		if(ten_to_n(x,i)==y){
			cout<<i<<endl;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

# 题目描述

[異世界転生](https://www.luogu.com.cn/problem/AT_tkppc4_1_c)

理解后发现它是一题考察 $10$ 进制转换成 $m$ 进制的题目。

### 注意事项

转换进制要用短除法，不懂的同学可以[点这里](https://blog.csdn.net/weixin_43642751/article/details/130043724)。

# 算法思路

枚举 $m(2 \sim 10)$，把 $n$ 转换成 $m$ 进制，再和 $x$ 比较。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=110;
ll n,m,a[N],b[N];
string s;
bool cmp(ll x[],ll y[])
{
	if(x[0]!=y[0])
	{
		return false;
	}
	for(int i=1;i<=x[0];i++)
	{
		if(x[i]!=y[i])
		{
			return false;
		}
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>s;
	reverse(s.begin(),s.end());
	a[0]=s.size();
	for(int i=1;i<=a[0];i++)
	{
		a[i]=s[i-1]-'0';
	}
	for(int i=2;i<=10;i++)
	{
		m=n;
		b[0]=0;
		while(m)
		{
			b[++b[0]]=m%i;
			m/=i;
		}
		if(cmp(a,b))
		{
			cout<<i<<"\n";
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

### 题意

给定 $n,x$，已知 $n_{(10)}=x_{(m)}$，求 $m$。

$9\le n\le10^{18},1\le |x|\le60,2\le m\le 10$。

### 思路

由于 $2\le m\le 10$，所以可以枚举所有的 $m$，然后将 $n$ 转换为 $m$ 进制，判断是否与 $x$ 相等。

进制转换可参考 [B3619](https://www.luogu.com.cn/problem/B3619)。

注意开 `long long`。

### 代码

```
#include<bits/stdc++.h>
using namespace std;

inline long long read(){//快读
	char c=getchar();long long x=0,f=1;
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-48;
	return x*f;
}

string dict="0123456789";

string ttx(long long n,long long m){//进制转换
	string ans="";
	while(n){
		ans+=dict[n%m];
		n/=m;
	}
	string t="";
	for(long long i=ans.length()-1; i>=0; i--) t+=ans[i];
	return t; 
}

int main(){
	long long n=read();
	string x;
	cin>>x;
	for(int i=2; i<=10; i++){
		string ni=ttx(n,i);
		if(ni==x){//判断是否相等
			cout<<i;
			break;
		}
	}
	return 0;
}
```

---

## 作者：zhuweiqi (赞：1)

枚举题，需要一点进制转换的功底。

思路：把所有的 $m$ 枚举一遍就可以了，每次枚举时，先把 $n$ 转换成 $i$ 进制的数，然后再判断 $n_{(i)}$ 是否等于 $x_{(m)}$，如果是就说明这个 $i$ 就是我们要求的 $m$ 的值，输出它即可，如果不是就继续枚举下去，直到找到答案为止。当然，我们枚举时还可以加个优化，即从最小的可能作为答案的 $i$ 开始枚举，使得 $x$ 可能是一个 $i$ 进制数并且 $x$ 肯定不是一个 $i-1$ 进制数，这样可以节约一点时间，比如说，当 $n=10$，$x=22$ 时，我们可以直接从 $3$ 开始枚举，因为 $x$ 显然不可能为二进制数。上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
	long long n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n;
}
int l1,l2;
char a[65];
int main(){
	long long n=read();
	scanf("%s",a+1);
	l1=strlen(a+1);
	int m=2;
	for(int i=1;i<=l1;i++){
		if(a[i]>='0' && a[i]<='9') m=max(m,(a[i]^48)+1);
		else m=max(m,a[i]-'A'+10);
	}
	for(;;m++){
		long long x=n,i=l1,flag=0;
		while(x){
			int now=x%m;
			if(now<10){
				if(a[i]-'0'!=now){
					flag=1;
					break;
				}
			}
			else {
				if(a[i]-'A'+10!=now){
					flag=1;
					break;
				}
			}
			x/=m;
			i--;
			if(i<1){
				if(x) flag=1;
				break;
			}
		}
		if(flag==0 && i==0){
			printf("%d",m);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：CCDYJXZ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_tkppc4_1_c)。

**题意**：

只需思考一下就能发现，这道题实际上就是求十进制 $n$ 在多少进制，也就是题目说的 $m$ 进制的情况下才能等于 $x$。

**思路**：

可以直接暴力枚举所有从 $2$ 到 $10$ 的进制。**但注意到数据范围后**，必须开 ```long long```。然后只需将 $n$ 转换到此时枚举的进制后判断是否与 $x$ 一样就行，非常简单的一道板子题，会短除法看得懂题就能解决。


------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f,s=1;
char d[40]={"0123456789"};//存储进制的表示。 
string ai(long long a,int s)
{
	string dd="",ss="";int g;
	while(a){
		dd+=d[a%s];
		a/=s;
	}//短除法求进制表示。 
	g=dd.size();
	for(int i=0;i<g;i++)
		ss+=dd[g-i-1];//倒序。 
	return ss;
 } 
int main(){	
	long long a;string s,d;
	cin>>a>>s;
	for(int i=2;i<=10;i++){//枚举每种进制。 
		d=ai(a,i);
		if(d==s){//一样就输出。 
			cout<<i;
			return 0;
		}
	}
	return 0;
}
```
蒟蒻的一篇题解，如有不满请见谅。

---

## 作者：CleverRaccoon (赞：0)

## 题目

[题目传送门](https://www.luogu.com.cn/problem/AT_tkppc4_1_c)


## 思路

由于只有可能是 $2$ 到 $10$ 进制，所以直接枚举每种进制，进行进制转换，判断是否与 $x$ 相等即可。

怎么进制转换呢？

## 进制转换

**短除法！**

假设当前要将十进制数字转换为 $n$ 进制。将十进制数除以 $n$ 得到的整数部分保留，作为下一次除以 $n$ 时的被除数，依次记下得到的余数，重复上述步骤，直到整数部分为 $0$ 结束，将记录下的余数逆序输出，则为该十进制对应的 $n$ 进制数。

上栗子：将十进制下的 $89$ 转化为二进制。

![](https://cdn.luogu.com.cn/upload/image_hosting/31aw5tml.png)

最后的答案就是：$1011001$。

## 代码

明白了进制转换，这题就简单多了，下面是代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 进制转换
string tenToK(ll n, ll k) {
	string res = "";
	while(n) {  // 除到0为止
		res = (char)(n % k + '0') + res;    // 加上当前的余数
		n /= k; // 继续除
	}
	return res;
}

int main() {
    ll n;
    string x;
    cin >> n >> x;
    for(int i = 2; i <= 10; ++i)    // 循环枚举每种进制
        if(tenToK(n, i) == x) { // 判断数字是否相等
            cout << i;
            break;
        }
    return 0;
}
```

谢谢大家！完结撒花！

---

## 作者：jsisonx (赞：0)

一道进制转换+枚举的题。

枚举 $i$，每次枚举算出一个 $i$ 进制数，在与给出的 $m$ 进制数相比较。如果符合就输出 $i$，否则就继续枚举。

### 注意开 long long！
# 代码
```cpp
#include<iostream>
#include<cstring>
#include<math.h>
using namespace std;
int main(){
	long long n,h=0,l=0,yes=1;
	int x[65],z[65];
	cin>>n;
	long long m=n;//记录n，避免进制转换时找不到
	char y[65];
	cin>>y;
	for(int i=0;i<strlen(y);i++){
		z[i]=y[i]-'0';
	}
	for(int i=2;i<=10;i++){
		l=0;
		yes=1;
		n=m;
		h=0;
		while(n!=0){
			x[h]=n%i;
			n=n/i;
			h++;
		}//进制转换
		if(strlen(y)!=h){
			yes=0;
			continue;
		}
		for(int j=h-1;j>=0;j--){
			if(x[j]!=z[l]){
				yes=0;
				break;
			}
			l++;
		}//枚举每一位与原数比较
		if(yes==1){
			cout<<i<<endl;//找到就输出
			return 0;
		}
	}
	return 0;
}
```
如何进行进制转换？
## 短除法！
[短除法见这里](https://wenku.baidu.com/view/e23ac7aaa2c7aa00b52acfc789eb172ded6399fa.html?_wkts_=1682944612463&bdQuery=%E7%94%A8%E7%9F%AD%E9%99%A4%E6%B3%95%E8%BF%9B%E5%88%B6%E8%BD%AC%E6%8D%A2)


---

## 作者：_colin1112_ (赞：0)

## 思路

不难发现，这是一道判断进制的题。

我们只需枚举 $2$ 到 $10$ 的进制，判断有没有一样的就行了。

tips：数据范围：$10^{18}$，要开 `long long`。

-----

AC Code：

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E=1e6+114514;
ll n;
string d;
char test[E]={"0123456789"};
string zhuanhuan(ll x,ll a){
	string arr;
	while(x){
		arr+=test[x%a];
		x/=a;
	}
	reverse(arr.begin(), arr.end());
	return arr;
}
int main(){
	cin >>n>>d;
	for(int i=2;i<=10;i++){
		if(zhuanhuan(n,i)==d){
			cout <<i<<endl;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Kobe_BeanBryant (赞：0)

### 思路：
1. 枚举 $ m $ 次，算出当前进制对应的数。
2. 判断是否与 $ x $ 相等。
3. 如果相等，我们就直接输出。
4. 否则，遍历到下一个进制重复上面的步骤。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
string x;
signed main(){
    cin>>n>>x;
    m=2;
    while(m<=10){
        char a;
        int y=n;
        while(y) a=y%m+'0'+a,y/=m;
        if(a==x){
            cout<<m<<endl;
            return 0;
        }
        m++;
    }
    return 0;
}
```

---

## 作者：_Gabriel_ (赞：0)

### 思路

本题就是把十进制转换成 $m$ 进制的题。

就是从 $2$ 到 $10$ 枚举一下 $m$，把 $n$ 转化成 $m$ 进制的数，再与 $x$ 进行对比，一样则输出 $m$。

#### 注意：$n$ 要开 long long!

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
int a[N], ans;

string s = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string binary_invert(ll n, int binary) {
	string ans = ""; 
	while (n) {
		ans += s[n % binary];
		n /= binary;
	}
	reverse(ans.begin(), ans.end());//倒序函数 
	return ans;
} 

int main() {
	ll n;
	string x; 
	cin >> n >> x;
	for (int i = 2; i <= 10; i++) {
		if (binary_invert(n, i) == x) {
			cout << i;
			break;
		}
	}
	return 0;
}
```


---

