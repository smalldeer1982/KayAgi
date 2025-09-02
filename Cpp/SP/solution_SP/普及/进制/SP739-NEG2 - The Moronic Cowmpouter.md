# NEG2 - The Moronic Cowmpouter

## 题目描述

Inexperienced in the digital arts, the cows tried to build a calculating engine (yes, it's a cowmpouter) using binary numbers (base 2) but instead built one based on base negative 2! They were quite pleased since numbers expressed in base -2 do not have a sign bit.

 You know number bases have place values that start at 1 (base to the 0 power) and proceed right-to-left to base^1, base^2, and so on. In base -2, the place values are 1, -2, 4, -8, 16, -32, ... (reading from right to left). Thus, counting from 1 goes like this: 1, 110, 111, 100, 101, 11010, 11011, 11000, 11001, and so on.

 Eerily, negative numbers are also represented with 1's and 0's but no sign. Consider counting from -1 downward: 11, 10, 1101, 1100, 1111, and so on.

 Please help the cows convert ordinary decimal integers (range -2,000,000,000 .. 2,000,000,000) to their counterpart representation in base -2.

## 样例 #1

### 输入

```
-13```

### 输出

```
110111```

# 题解

## 作者：冒泡ioa (赞：4)

[个人博客同题题解](http://bubbleioa.top/poj3191-the-moronic-cowmpouter/)
## 提示（这个提示poj上有的）
Hint  
Explanation of the sample:   
Reading from right-to-left:  
1\*1 + 1\*-2 + 1\*4 + 0\*-8 +1\*16 + 1\*-32 = -13
## 题目大意
输入一个十进制 N(−2,000,000,000≤N≤2,000,000,000) ，输出它的-2进制数
# 题解
平常我们很少会涉及到负进制，按照提示所给内容，我们应该很快能想到第一种做法，
第一种想法，我们去枚举每一个负二进制数，对于每一个负二进制数，我们将它转换成十进制数，看看是不是一样。  
代码如下：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n;
long long p[32];
 
void init(){
    cin>>n;
    p[0]=1;
    for(int i=1;i<=31;i++){
        p[i]=p[i-1]*-2;
    }
}
 
inline bool jud(int num){
    int res=0,cnt=0;
    while(num){
        if(num&1)res+=p[cnt];
        ++cnt;
        num>>=1;
    }
    if(res==n)return 1;
    return 0;
}
 
void out(int num){
    int tmp[200],t=0;
    while(num){
        if(num&1)tmp[++t]=1;
        else tmp[++t]=0;
        num>>=1;
    }
    for(int i=t;i>=1;i--)printf("%d",tmp[i]);
}
 
int main(){
    init();
    for(long long i=1;i<=2000000000LL;i++){
        if(jud(i)){
            // cout<<"!!"<<i<<endl;
            out(i);
            break;
        }
    }
    return 0;
}

```
然而上面的做法会T，那么我们能不能直接从十进制算到负二进制呢？  
这个需要好好观察一下提示，  
我们发现如果要确定当前位是0还是1，只要对下一个为1时取余就知道了，如果余数为0，那么当前这个数自然是后面位的倍数了，取0，否则就取1.

然后减去当前还剩的数，继续往后走。

最后减到0就可以了。
## 代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int MAXN=1e5+7;
const int inf =1e9;
int ans[1000];
long long n;
long long pw(int a,int b){//很普通的快速幂
    long long sum=1;
    long long base=a;
    while(b){
        if(b&1)sum*=base;
        base*=base;
        b>>=1;
    }
    return sum;
}
int main(){
    scanf("%lld",&n);
    int top=0;
    if(!n)ans[top++]=0;//0的时候特判
    while(n){
        if(n%(pw(-2,top+1)))ans[top]=1;
        else ans[top]=0;
        n-=ans[top]*pw(-2,top);//相当于不断把n这个10进制数拆分成-2进制数
        top++;
    }
    while(top)printf("%d",ans[--top]);
    return 0;
}
```

---

## 作者：zxh923 (赞：2)

# SP739 NEG2 - The Moronic Cowmpouter 题解

[题目传送门](https://www.luogu.com.cn/problem/SP739)

### 思路

这道题其实就是一个简单的进制转换，只不过要转换成负进制而已。

那如何转换呢？显然的是，我们需要规避掉负的余数。

所以我们需要判断，如果余数是负的，那我们就把它加上 $2$，并且把商加上 $1$，这样就不会出现负的余数；反之不动即可。

这道题输出最好用字符串，否则会遇到一些奇怪的问题。

而且我们要特判一下 $0$，直接输出 $0$ 即可。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,cnt,x;
string n;
char ans[]="01";
int main(){
	cin>>a;
	if(a==0){//特判
		cout<<0;
		return 0;
	}
	while(a){
		cnt++;
		x=a%-2;
		a/=-2;
		if(x<0)x+=2,a++;
		n=ans[x]+n;
	}
	cout<<n;
	return 0;
}
```

### 附录

如果这道题学会了，推荐大家去做[这道题](https://www.luogu.com.cn/problem/P1017)。

---

## 作者：ivyjiao (赞：2)

我们考虑这道题一个数最大可能会有多少 $-2$ 进制位呢？$34$ 个。

于是我们便有了一个朴素的搜索：对于每个进制位，枚举其 $1$ 和 $0$ 的情况，如果枚举到了要找的那个数就直接输出。

但是这样的复杂度高达 $O(2^n)$，无法通过。

我们再考虑，一个数的 $-2$ 进制数拆成两边，一定是每边选一些数，然后进行组合。在这里我们把前 $16$ 位分一边，后 $16$ 为分一边。

如：

$$114514=(0000000000000110|1100001101010110)_{-2}$$

$$1919810=(0000000001101101|0101111101000110)_{-2}$$

于是考虑双向搜索。

时间复杂度 $O(2^{\frac n 2})$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,power[101];
map<int,string> mp;
void dfs1(int x,string y,int z){
	if(z>17) return;
	if(x==n){
		for(int i=y.size()-1;i>=0;i--) cout<<y[i];
		exit(0);
	}
	mp[x]=y;
	dfs1(x+power[z],y+"1",z+1);
	dfs1(x,y+"0",z+1);
}
void dfs2(int x,string y,int z){
	if(z>34) return;
	if(mp[n-x]!=""){
		for(int i=y.size()-1;i>=0;i--) cout<<y[i];
		for(int i=mp[n-x].size()-1;i>=0;i--) cout<<mp[n-x][i];
		exit(0);
	}
	dfs2(x+power[z],y+"1",z+1);
	dfs2(x,y+"0",z+1);
}
signed main(){
	cin>>n;
	if(n==0) puts("0");
	for(int i=0;i<=34;i++){
		power[i]=pow(-2,i);
	}
	dfs1(0,"",0);
	dfs2(0,"",17);
}
```

---

## 作者：qi__ (赞：2)

因为 -2 进制不常用~~没用过~~，所以很多人看见这道题都以为很难，但其实这就是一道进制转换的板子。

相信板子大家都会敲，这道题的关键是余数 $<1$ 时需要将余数 $+2$，商 $+1$，因为这是 -2 进制，后面输出会炸掉。

因为~~对 STL 的喜爱~~码风问题，本篇题解用 stack 逆序输出。

stack 经常用来逆序输出。

逆序输出板子:
```cpp
stack<int>s;
int tmp;
for(int i=1;i<=n;i++){
	cin>>tmp;
   	s.push(tmp);
}
while(!s.empty()){
	cout<<s.top()<<' ';
	s.pop();
}
```
 完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
void change(int n){//进制转换计算器
	if (!n) cout << "0";//特判
	else{
	    stack<int>s;//STL大法好！
	    int tmp;
	    while (n!=0){
	        tmp = n % -2;
	        n /= -2;
	        if (tmp < 0)//这里是关键
	        {
	            tmp += 2;
	            n++;
	        }
	        s.push(tmp);
	    }
	    while(!s.empty()){
	    	cout<<s.top();//用栈逆序输出
			s.pop();
		}
	}
}
int main(){//简洁明了的主函数
    cin >> n;
    change(n);
    return 0;
}
```

---

## 作者：xujingyu (赞：1)

将十进制 $n$ 数转为**正**进制数的步骤为：

1. 取出 $\dfrac{n}{\text{进制}}$ 的余数；
2. 将该式子的商设为新的 $n$；
3. 逆序取余数即为结果。

而转 $-2$ 进制类似转正进制，只需要将 $n$ 不断除以 $-2$，储存余数。但是注意余数有两种情况：$0$ 或 $-1$。如果余数是 $-1$ 的话，我们把它变成 $1$。但是变成 $1$ 后表示的数（$n$）会发生改变，所以将 $n+1$ 来弥补少了的 $2$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string ans;

signed main()
{
	scanf("%d",&n);
	if(!n)//特判
	{
		printf("0");
		return 0;
	}
	while(n)
	{
		int yu = n % -2;//取余数
		n /= -2;
		if(yu < 0)//余数为-1
		{
			yu += 2;
			n++;
		}
		ans = (char)(yu + '0') + ans;//逆序得到答案
	}
	cout << ans;
	return 0;
}
```

---

## 作者：LiJinLin_AFO (赞：1)

# SP739 题解

这是一道简单的模拟。

众所周知，十进制转 $x$ 进制（$1<x\le 36$）的步骤，就是不断求 $n$ 除以 $x$ 的余数，每次求余数后 $n$ 等于 $n$ 除以 $x$ 的商，再将这些依次求出的余数倒序输出。

但是，本题要求转负进制，我们需要注意：求得的余数会小于等于 $0$。在本题，我们只需要给小于 $0$ 的余数变成 $1$，并且给 $n$ 加上 $1$ 即可。因为余数变成了 $1$，表示的数就会减 $2$，所以需要将 $n$ 加上 $1$，弥补余数变为 $1$ 所给表示的数减去的 $2$。

```cpp
#include<iostream>
#include<string>
using namespace std;
string ans;
int main(){
	int n;
	cin>>n;
	if(!n){
		cout<<0;
		return 0;
	}
	while(n){
		int yu=n%-2;
		n/=-2;
		if(yu==-1) yu+=2,++n;
		ans=(char)(yu+'0')+ans;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：EuphoricStar (赞：1)

和正进制转换差不多。

要注意的一点是用系统的 $\%$ 运算符时必须注意检查余数是不是负数。如果余数 $<$ $0$，那么余数 += $2$，商++。

**注意特判 $0$**

~~超简洁的~~代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

char jz[] = "01";
string res = "";
int n, a;

int main()
{
    cin >> n;
    if (!n) { cout << "0"; return 0; }
    while (n)
    {
        a = n % -2;
        n /= -2;
        if (a < 0)
        {
            a += 2;
            n++;
        }
        res = jz[a] + res;
    }
    cout << res;

    return 0;
}
```


---

## 作者：minVan (赞：0)

**题目大意**

给定 $x$，求 $x$ 的 $-2$ 进制数。

**解题思路**

从后往前枚举 $x$ 的每一位，若 $x \bmod (-2)$ 为负数，则这一位为 $x\bmod(-2)+2$，并且 $x\gets x\div(-2)+1$；否则这一位为 $x\bmod(-2)$，$x\gets x\div(-2)$。

注意要特判 $x=0$ 的情况。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x;
string ans = "";
int main() {
    cin >> n;
    if(!n) { cout << 0; return 0; }
    while(n) {
        x = n % -2;
        n /= -2;
        if(x < 0) { x += 2, ++n; }
        ans = ans + char(x + '0');
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}
```

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/SP739)

[SPOJ 链接](https://www.spoj.com/problems/NEG2/)

题目大意：

输入一个数 $n$（$-2^9\leq n\leq2^9$），输出 $n$ 的 $-2$ 进制。

思路：

我们可以使用[快速幂](https://oiwiki.org/math/binary-exponentiation/#%E8%BF%87%E7%A8%8B)来计算 $(-2)^n$。我们发现，如果要判断当前的一位为 $0$ 还是 $1$，可以做以下判断：如果 $n\equiv0\pmod{(-2)^{k+1}}$，那么第 $k+1$ 位就是 $0$，否则就是 $1$。然后，如果第 $k+1$ 位是 $1$，我们就把 $n$ 减去 $(-2)^k$，最后把位数加上 $1$。最后输出就大功告成了。

坑点：

1. 我们需要特判 $n=0$ 时的情况！
1. 最后我们要倒序输出！
1. 别忘了存储位数的变量加上 $1$！
1. 全程开 ```long long```，否则炸精度！

上代码：
```cpp
#include <iostream>
using namespace std;

int ans[1001];// 存储答案的数组

inline long long ksm(const int &a, const int &b){// 快速幂模板
    long long ans = 1, base = a, temp = b;
    while (temp){
        if (temp & 1){
            ans *= base;
        }
        base *= base;
        temp >>= 1;
    }
    return ans;
}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    long long n;
    cin >> n;
    int top = 0;
    if (n == 0){// n=0 特判要注意！
        ans[top++] = 0;
    }
    while (n){
        if (n % ksm(-2, top + 1)){
            ans[top] = 1;
        } else {
            ans[top] = 0;
        }
        n -= ans[top] * ksm(-2, top);
        top++;// 位数变量加 1 要注意！
    }
    while (top){
        cout << ans[--top];// 倒序输出要注意！
    }
    cout << "\n";
    return 0;
}
```

---

## 作者：cmk666 (赞：0)

[题目链接](/problem/SP739)

题目大意：给出 $10$ 进制的 $n$，转化成 $-2$ 进制。

设 $n$ 转化成 $-2$ 进制后低位到高位分别是 $a_0,a_1,\cdots,a_{m-1},a_m$，则 $n=(-2)^ma_m+(-2)^{m-1}a_{m-1}+\cdots+(-2)^1a_1+a_0$。

可以看出，除了 $a_0$，别的数都是 $-2$ 的倍数。那么，用 $n\bmod-2$ 就可以求出 $a_0$。

然后，令 $n\gets n\operatorname{div}(-2)$，其中 $\operatorname{div}$ 是整除运算，则相当于所有 $-2$ 的质数都 $-1$，那么又可以按上述方法求出 $a_1$。因此一直递归即可，到 $n=0$ 时结束。

记得要特判 $0$，还有 C++ 中模一个负数可能会得到负数，记得将它变成正的即可。

时间复杂度 $O(\log n)$。核心代码如下：
```cpp
int n;
inline void f(int x)
{
	if ( !x ) return;
	int y = x % -2; x /= -2;
	if ( y < 0 ) y += 2, x++; // 修正余数
	f(x), putchar(y + '0');
}
int main()
{
	read(n), f(n); n == 0 && putchar('0'); // 特判 0
	return putchar('\n'), 0;
}
```

---

## 作者：rai1gun (赞：0)

### 1.题意

将一个 $10$ 进制整数 $n$ 转为 $-2$ 进制。

### 2.方法

考虑到 $10$ 进制转 $2$ 进制时，是不断取余，最后倒叙输出。

转为 $-2$ 进制同理。

我们可以根据样例验证一下：

$1 \times (-2)^0 + 1 \times (-2)^1 + 1 \times (-2)^2 + 0 \times (-2)^3 +1 \times (-2)^4 + 1 \times (-2)^5 = -13$

看来就是这个道理没跑了。

需要注意的地方是，如果余数 $<0$，那么将该数 $+1$，必将余数 $+2$。

错误代码 1：
```cpp
#include<bits/stdc++.h>
// 快读省略
using namespace std;
const int N = 1e5+5;
int n,a[N],cnt;
int main(){
	read(n);
	while(n){
		int M=n%-2;
		n/=-2;
		if(M<0) n++,M+=2;
		a[++cnt]=M;
	}
	F2(i,cnt,1,1) print(a[i]);
	return 0;
}
```
诶这为啥会错捏？我们发现当我们输入 $0$ 的时候它会输出一团空气。

所以，我们只需要在开始的地方特判一下 $0$ 的情况即可 AC。

---

