# Palindrome Transformation

## 题目描述

Nam is playing with a string on his computer. The string consists of $ n $ lowercase English letters. It is meaningless, so Nam decided to make the string more beautiful, that is to make it be a palindrome by using 4 arrow keys: left, right, up, down.

There is a cursor pointing at some symbol of the string. Suppose that cursor is at position $ i $ ( $ 1<=i<=n $ , the string uses 1-based indexing) now. Left and right arrow keys are used to move cursor around the string. The string is cyclic, that means that when Nam presses left arrow key, the cursor will move to position $ i-1 $ if $ i>1 $ or to the end of the string (i. e. position $ n $ ) otherwise. The same holds when he presses the right arrow key (if $ i=n $ , the cursor appears at the beginning of the string).

When Nam presses up arrow key, the letter which the text cursor is pointing to will change to the next letter in English alphabet (assuming that alphabet is also cyclic, i. e. after 'z' follows 'a'). The same holds when he presses the down arrow key.

Initially, the text cursor is at position $ p $ .

Because Nam has a lot homework to do, he wants to complete this as fast as possible. Can you help him by calculating the minimum number of arrow keys presses to make the string to be a palindrome?

## 说明/提示

A string is a palindrome if it reads the same forward or reversed.

In the sample test, initial Nam's string is: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486C/c2c9513e216627ba8dba5e20f24d19bb9e05137a.png) (cursor position is shown bold).

In optimal solution, Nam may do $ 6 $ following steps:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486C/69c8590618c960ba2fbb8128394f526e54e905cd.png)The result, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486C/f8fb95d3cc7310b730ff830a0c29f176cf3c201f.png), is now a palindrome.

## 样例 #1

### 输入

```
8 3
aeabcaez
```

### 输出

```
6
```

# 题解

## 作者：Dry_ice (赞：7)

## 大体思路：贪心

## Details
- 左右 $2$ 个指针移动
- 记得要初始化每个字符的变换次数
- 然后直接用指针判断移动方向进行贪心
- 注意**环形**，记得 ```mod 26``` ！

## CODE（有部分注释）

```cpp
#include <stdio.h>
const int N=100005;
inline int ab(int a) { //绝对值
	return a>0? a : -a;
}
inline int mn(int a, int b) { //求较小值
	return a>b ? b : a;
}
inline int chg(char a, char b) { //环形移动
	int t=ab(a-b);
	return mn(t, 26-t);
}
int a[N];
char s[N];
int main() {
	int n, p;
	scanf("%d %d %s", &n, &p, s);
	p--;
	if (p>=n/2) p=n-1-p;
	int ans=0, L=-1, R=-1; //答案和两个指针
	for (int i=0; i<n/2; i++) { //贪心
		int k=chg(s[i], s[n-1-i]); //移动
		if (k && L==-1 /*判断*/) L=i; //移动左指针
		if (k) R=i; //移动右指针
		ans+=k; //累计答案
	}
	if (ans!=0) //特殊情况
		ans+=mn(ab(p-L), ab(p-R))+(R-L);
	printf("%d\n", ans); //输出答案
	return 0;
}

```
## The end. Thanks.

~~（走过记得赞过~~

---

## 作者：AC_Automation (赞：6)

貌似现在只有一篇$O(n\log n)$的题解？给一个$O(n)$的吧。

我们先预处理出来每一个字符要想和其对应位置的字符相同，所需的操作次数。  
以样例为例子：
```
aeabcaez
10011001
```
$\texttt{a}$变成$\texttt{z}$要1步，$\texttt{b}$变成$\texttt{c}$要1步  
然后分类讨论k的位置即可，详见代码注释
```cpp
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int c[100005]; 
int f(char ch1,char ch2){
	int x=ch1-96,y=ch2-96;
	return min(abs(x-y),min(abs(x+26-y),abs(x-y-26)));
}//预处理
int main(){
	int n,k,ans=0;
	string s;
	cin>>n>>k>>s;
	k--;
	for(int i=0;i<n;i++){
		c[i]=f(s[i],s[n-i-1]);
	}
	int L=-1,R=-1;
	if(k<n/2){//k在前半部分
		for(int i=0;i+i<=n;i++)if(c[i]){L=i;break;}
		for(int i=n/2-1;i>=0;i--)if(c[i]){R=i;break;}//确认要经过的范围
		if(L==R&&L==-1){
			cout<<0;
			return 0;
		}//直接回文串的话处理掉就行
		if(k<=L){
			ans+=R-k;
		}//k在要经过范围左侧
		else if(k>=R){
			ans+=k-L;
		}//右侧
		else{
			ans+=R-L+min(k-L,R-k); 
		}//内部
		for(int i=L;i<=R;i++){
			ans+=c[i];
		}
		cout<<ans;
	}
	else{//k在后半部分，其他同上
		for(int i=n/2;i<=n;i++)if(c[i]){L=i;break;}
		for(int i=n;i>=n/2;i--)if(c[i]){R=i;break;}
		if(L==R&&L==-1){
			cout<<0;
			return 0;
		}
		if(k<=L){
			ans+=R-k;
		}
		else if(k>=R){
			ans+=k-L;
		}
		else{
			ans+=R-L+min(k-L,R-k); 
		}
		for(int i=L;i<=R;i++){
			ans+=c[i];
		}
		cout<<ans;
		
	}
	return 0;
}
```
很明显，时间复杂度是$O(n)$的

---

## 作者：Elma_ (赞：4)

发现对于一个位置 $x$，和它的对应位置 $y$，无论修改 $x$ 还是修改 $y$ 所需的操作次数是相同的。因此我们可以预处理出每一个位置上的字符和它对应位置上的字符相同所需的操作数。

左半部分和右半部分最后是对称的，因此我们发现一定只需要修改某一半的部分，这取决于 $p$ 最开始在左半部分还是右半部分，显然当 $p$ 最开始在左半部分时我们只修改左半部分的字符，反之亦然。

处理出最靠左的需要修改的字符位置 $l$ 和最靠右的需要修改的字符位置 $r$，然后是一个简单的分类讨论计算出移动需要耗费的操作数，这一部分可以直接看代码。最后加上修改字符的操作数即为答案。需要注意原串本身就是一个回文串的情况，时间复杂度 $O(n)$。

```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define pii pair<int, int>
#define mp make_pair
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

int n, p, ans, l = -1, r = -1;
int tmp[maxn]; string s;

inline int calc(char x, char y) {
	int X = x - 96, Y = y - 96;
	return min(abs(X - Y), min(abs(X + 26 - Y), abs(X - 26 - Y)));
}

int main(void) {
	n = read(), p = read() - 1, cin >> s;
	for (int i = 0;i < n;i++) tmp[i] = calc(s[i], s[n - i - 1]);
	if (p < (n >> 1)) {
		for (int i = 0;i < (n >> 1);i++) if (tmp[i]) { l = i; break; }
		for (int i = (n >> 1) - 1;i >= 0;i--) if (tmp[i]) { r = i;break; }
	} else {
		for (int i = (n >> 1);i <= n;i++) if (tmp[i]) { l = i; break; }
		for (int i = n;i >= (n >> 1);i--) if (tmp[i]) { r = i; break; }
	}
	if (l == r && l == -1) return puts("0"), 0;
	if (p < l) ans += r - p;
	else if (p > r) ans += p - l;
	else ans += r - l + min(p - l, r - p);
	for (int i = l;i <= r;i++) ans += tmp[i];
	printf("%d\n", ans);
	return 0; 
}
```


---

## 作者：OIerYang (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF486C)

## 知识点：贪心，分类讨论

### 重点：
- 根据光标位置和需改变的位置分类
- 它有两种改变方式

代码有详细注释：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int dis[N],ans,mii=1e9,mij=1e9,mai,maj;
void solve(){
	int n,k;cin>>n>>k;
	string s;cin>>s;s=' '+s;//读入s,将s的字母变成1~n
	for(int i=1;i<=n/2;i++){
		int j=n-i+1;
		if(s[i]>s[j]){
			ans+=min(s[i]-s[j],-s[i]+s[j]+26);//求出两种变化的最小值
			mii=min(mii,i);mai=max(mai,i);
			mij=min(mij,j);maj=max(maj,j);
			//把需改变的最大最小算出,对下面分类讨论有用
		}
		else if(s[i]<s[j]){
			ans+=min(s[j]-s[i],-s[j]+s[i]+26);
			mii=min(mii,i);mai=max(mai,i);
			mij=min(mij,j);maj=max(maj,j);
			//同上
		}
	}
	if(mii==1e9)cout<<ans,exit(0);//s本身就是回文
	if(k%2==1&&k==(n/2+1))ans+=k-mii;//k是s的中心
	else if(k<=n/2){//k在前半边
		if(mii<=k&&k<=mai)ans+=2*min(mai-k,k-mii)+max(mai-k,k-mii);
		else ans+=k-mii;
	}
	else {//k在后半边
		if(mij<=k&&k<=maj)ans+=2*min(k-mij,maj-k)+max(k-mij,maj-k);
		else ans+=k-mij;
	}
	//上方是在计算光标左右移动的最小值
	cout<<ans;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int T;T=1;
	// cin>>T;
	while(T--)solve();
	return 0;
}
```
看的这么认真,点个赞再走吧！

---

## 作者：cwd2023 (赞：2)

# CF486C题解
### by cwd2023
致管理员：本人多次提交题解是因为改正了一些格式上的错误，并非恶意刷提交，给您带来不便深感抱歉。

---

### 题意简述：
有一个字符串和一个有初始位置的指针，你需要通过四种操作以尽量小的代价使它成为回文串。

**操作**：指针左右移动或当前位置的字母上下调整。


---


### 思路：
1. 由于它是目标是一个回文串，所以我们只需要处理一半，且左半边和右半边效果相同。

    - 如：第 $i$ 个位置的字母是 $c1$，第 $n-i+1$ 个位置是$c2$（人话：与 $c1$ 对应的位置）。

    - 则：无论 $c1$ 在左还是在右，无论我想让 $c1$ 变为 $c2$，还是让 $c2$ 变为 $c1$，代价都是 $\min(\lvert c1-c2\rvert,26-\lvert c1-c2\rvert)$。

    - 即：从 $c1$ 加到 $c2$，和从 $c1$ 减到 $c2$ 的最小值（这里 $c1$ 代表较小者，$c2$ 代表较大者，所以公式中加了绝对值）。

2. 在左半边的区间内，指针也不一定是每个位置都要跑一遍，例如左区间的最前或最后有一段不用改动，则指针只需要在中间的一段内跑。我们可以用一个 $l$ 和一个  $r$ 来记录这个需要改动的区间。

3. 知道 $l$ 和 $r$ 后，指针移动的代价是多少呢？
 
     - 首先，从 $l$ 到 $r$ 肯定要跑一遍，代价是 $r-l$。
       
     - 其次，我们要先让它到一个端点后再开始在 $l$ 到 $r$ 内跑，即为 $p$ 分别到两端点距离的最小值：$\min(\lvert p-l \rvert,\lvert p-r \rvert)$。

所以，代价为：$\min(\lvert p-l \rvert,\lvert p-r \rvert)+r-l$。


---


#### 思路3详解：

例如：


|...|l|...|r|...|
|:-:|:-:|:-:|:-:|:-:|

1. 当 $p$ 在 $l$ 左侧：

|...|p|...|l|...|r|...|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|

$p$ 需要移动：

$\min(l-p,r-p)+r-l=\min(l-p,r-l+l-p)=l-p+r-l=r-p$

2. 当 $p$ 在 $l$ 和 $r$ 之间：

|...|l|...|p|...|r|...|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|

$p$ 需要移动：

$\min(p-l,r-p)+r-l$

3. 当 $p$ 在 $r$ 右侧：

|...|l|...|r|...|p|...|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|

$p$ 需要移动：

$\min(p-r,p-l)+r-l=\min(p-r,p-r+r-l)+r-l=p-r+r-l=p-l$

整合一下就是 $\min(\lvert p-l \rvert,\lvert p-r \rvert)+r-l$。

---

### Code：
#### 详细注释版：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,p,l,r,ans;
string s;
ll fun(char a,char b){
	return min(abs(a-b),26-abs(a-b));
}//求出转换字母的代价，对应思路1。
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0),cin.tie(0);
	cin>>n>>p>>s,s=' '+s;
	if(p>(n+1)/2)p=n-p+1;
//若p不在左区间，将p翻转，并视为在左区间。
//对应思路1，左右区间效果相同。
	for(ll i=1;i<=(n+1)/2;i++){
		ll k=fun(s[i],s[n-i+1]);
		if(k&&l==0)l=i;
		if(k)r=i;//对应思路2。
		ans+=k;
	}
	if(ans>0)ans+=min(abs(p-l),abs(p-r))+r-l;
//对应思路3，指针移动的代价。
//如果s原本就是回文串，即 ans=0，就不需要这一步。
	cout<<ans<<"\n";
	return 0;
}
```
#### 无注释版：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,p,l,r,ans;
string s;
ll fun(char a,char b){
	return min(abs(a-b),26-abs(a-b));
}
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0),cin.tie(0);
	cin>>n>>p>>s,s=' '+s;
	if(p>(n+1)/2)p=n-p+1;
	for(ll i=1;i<=(n+1)/2;i++){
		ll k=fun(s[i],s[n-i+1]);
		if(k&&l==0)l=i;
		if(k)r=i;
		ans+=k;
	}
	if(ans>0)ans+=min(abs(p-l),abs(p-r))+r-l;
	cout<<ans<<"\n";
	return 0;
}
```

最后，希望本篇题解对你有所帮助，感谢观看。
### 望管理员通过！

---

## 作者：苏黎世 (赞：1)

这题大体是贪心，先处理改字符，再处理位置。

首先要知道，若一个位置是i，那么它的对应位置就是n-i+1。

这里我用的是string，再开一个b数组存该位置用不用修改。

然后先看每个位置用不用改字符，再判断p的移动距离。

那么处理修改的代码就是：
```cpp
s = ' ' + s;
//make sure 1 - n is char
for(int i = 1;i <= n/2; ++i)
{
	if(s[i] == s[n - i + 1])
	  b[i] = b[n - i + 1] = 0;
	else
	{
		char f1 = max(s[i], s[n - i + 1]);
		char f2 = min(s[i], s[n - i + 1]);
  		b[i] = b[n - i + 1] = min(f1 - f2, f2+26-f1);
  		ans += b[i];
	}
}//check change
```
再然后是判断位置：
```cpp
if(p > n/2)
	p = n - p + 1;
//check step
int i = 1, j = n/2;
   
while(i <= j)
{
   if(b[i] != 0 && b[j] != 0)
     break;
   if(b[i] == 0) i++;
   if(b[j] == 0) j--;
}
   
if(ans != 0)
{
	if(j <= p) ans += p - i;
	else if(i >= p) ans += j - p;
	else ans += min(abs(p-i),abs(j-p)), ans += j-i;
}
```
最后再综合起来就行了。

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int maxn = 1e5 + 5;
int n, p, g[maxn], st = 0, ans;
string s;
int b[maxn];
int main()
{
	cin >> n >> p >> s ;
	s = ' ' + s;//make sure 1 - n is char
	for(int i = 1;i <= n/2; ++i)
	{
		if(s[i] == s[n - i + 1])
		  b[i] = b[n - i + 1] = 0;
		else
		{
			char f1 = max(s[i], s[n - i + 1]);
            char f2 = min(s[i], s[n - i + 1]);
            b[i] = b[n - i + 1] = min(f1 - f2, f2+26-f1);
            ans += b[i];
		}
	}//check change
	
	if(p > n/2)
	  p = n - p + 1;
	//check step
    int i = 1, j = n/2;
    
	while(i <= j)
    {
        if(b[i] != 0 && b[j] != 0)
		  break;
        if(b[i] == 0) i++;
        if(b[j] == 0) j--;
    }
    
    if(ans != 0)
    {
        if(j <= p) ans += p - i;
        else if(i >= p) ans += j - p;
        else ans += min(abs(p-i),abs(j-p)), ans += j-i;
    }
    cout<<ans;
}
```


---

## 作者：X2H_tato (赞：1)

### 题意

给你一个指针，可以左右移动，指向的小写字母可以，改变，但都是有花费的a - b 和 a - z花费1，指针移动也要花费，一个单位花费1，问你把当前字符串变成回文串的最小花费是多少。

### 思路


　　首先对于字母的调整肯定是有一个最优值得，无法改变的，能改变的就是我们是改变左区间的还是右边的呢？

　　我们可以记录改变字母的最大区间长度（一半的区间），我们从0遍历到中间，得到左区间的范围，如过p在左区间就用这个范围，否则用右区间的范围，所以不如直接把p对称到左区间

　　然后求距离分类就好了，注意别忘了一开始直接是回文串的判断
  
### 代码



------------
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define inf (1 << 28)
using namespace std;
const int maxn = 1e5 + 1e2;
char s[maxn];
int main()
{
    int len,p;
    while(~scanf("%d%d",&len,&p))
    {
        scanf("%s",s);
        //左右对称的！！！
        if(p > len / 2)
            p = len - p;
        else
            p--;

        int ret = 0;
        int first = -1;
        int last = -1;
        for(int i = 0; i < len / 2;++i)
        {
            char a = s[i];
            char b = s[len - 1 - i];
            if(a == b)continue;
            if(first == -1)first = i;
            last = max(last,i);
            if(a < b)swap(a,b);
            int cost = min(a - b,b - a + 26);
            ret += cost;
        }
        if(first == -1 && last == -1)
            ret = 0;
        else if(p <= first)
            ret += last - p;
        else if(p >= last)
            ret += min(p - first,len - p + last);
        else
        {
            ret += last - first;
            ret += min(p - first,last - p);
        }
        printf("%d\n",ret);

    }
    return 0;
}
```


---

## 作者：谦谦君子 (赞：1)

## 思路
#### 根据指针起始位置，可以判断移动的时候在左、右的哪半部分移动，初始化求出字符需要变化的次数，然后贪心求出指针移动的次数。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
char s[100007];
int x[100007],y[100007];
int main()
{
    int len,p,count=0,num=0,j;
    scanf("%d%d%s",&len,&p,s+1);
    if(len==1)
    {
        printf("0\n");
        return 0;
    }
    if(len&1)j=len/2+2;
    else j=len/2+1;
    for(int i=len/2;i>=0&&j<=len;i--,j++)
        if(s[i]!=s[j])
        {
            int a=s[i]-'a';
            int b=s[j]-'a';
            int minn=min(a,b);
            int maxx=max(a,b);
            count+=min(maxx-minn,minn+26-maxx);
            x[num]=i;
            y[num++]=j;
        }
    sort(x,x+num);
    sort(y,y+num);
    if(p<=len/2)
    {
        if(num!=0)
        if(num==1)count+=fabs(x[0]-p);
        else
        {
            int flag=0;
            int aa=min(fabs(x[num-1]-p),fabs(p-x[0]));
            if(x[0]<=p)
            {
            	flag++;
                count+=(p-x[0]);
            }
            if(x[num-1]>p)
            {
            	flag++;
                count+=(x[num-1]-p);
            }
            if(flag==2)count+=aa;
        }
    }
    else
    {
        if(num!=0)
        if(num==1)count+=fabs(y[0]-p);
        else
        {
            int flag=0;
            int aa=min(fabs(y[num-1]-p),fabs(p-y[0]));
            if(y[0]<=p)
            {
            	flag++;
                count+=(p-y[0]);
            }
            if(y[num-1]>p)
            {
            	flag++;
                count+=(y[num-1]-p);
            }
            if(flag==2)count+=aa;
        }
    }
    printf("%d\n",count);
    return 0;
}
```

---

## 作者：WA_TERBRAIN (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF486C)

这道题是一个回文题，如果是回文题，那么就处理一半的字符串就行了。我选择处理左半部分的字符串。

**question1** 处理左半部分的字符串,如果初始光标在右边怎么办。

**answer1** 很简单，只需要将初始光标对称到左边就行了。

不难发现，对于一个字符，他的改动次数为

```
(min(abs((int)(s[i] - s[j])),26 - abs((int)(s[i] - s[j]))) % 26)
```
那么，本体的最大难点~~但也不难~~来了，左移（右移）次数怎么求呢。

观察一会就会知道，无论哪种遍历方法，都会经过左端点到右端点的路程，于是，问题转化为了求最短到达端点的路程。即左端点与右端点关于p点的距离的最小值 + 左右端点的距离（与其他端点无关）。

好的，上代码：


```
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define ll long long
#define u unsigned
using namespace std;
int n,p;
string s;
int a[100001];
int b[100001];
long long ans;
int m1,m2;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> n >> p;
	p--;
	cin >> s;
	for(int i = 0,j = n - 1;i<n / 2;i++,j--)
	a[i] = (min(abs((int)(s[i] - s[j])),26 - abs((int)(s[i] - s[j]))) % 26)/*单个字符修改次数*/,ans+=1LL * a[i];
	if(p > (n - 1) / 2) p = n - p - 1;//对称 
	for(int i = 0;i < n / 2;i++)if(a[i])b[i] = p - i;//每个需要修改的字符到p点的距离。 
	for(int i = 0;i<n / 2;i++)
		if(b[i]){
			m1 = b[i];
			break;
		}
	for(int i = n / 2 - 1;i >= 0;i--)
	if(b[i]){
		m2 = b[i];
		break;
	}
	ans += 1LL * min(abs(m1) ,abs(m2))/*关于p点的距离的最小值*/ + 1LL * abs(m2 - m1)/*左右端点的距离*/; 
	cout << ans;
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF486C Palindrome Transformation
## 题目翻译
给定一个长度为 $n$ 的字符串 $s$，初使有个光标位于 $p$ 处，每次操作可以选择以下两种：
1. 将光标向左/右移动一格。
2. 将光标所在位置的字符 $+1/-1$，其中 $z+1=a,a-1=z$。

现在要求最少多少次操作使得原字符串变成一个回文串。
## 几个小观察
#### 1
假设我们现在选定了一个字符 $s_i$，我们要把它变成字符 $c$，一共有两种方案：不断 $+1$；不断 $-1$。\
而我们要操作数最少，那肯定就会选这两种方案操作数少的那一种。
#### 2
如果有 $s_i\ne s_{n-i+1}$，那我们一定至少要对 $s_i$ 或 $s_{n-i+1}$ 其中一个进行 $2$ 操作。这是显然的，否则不可能构成回文串。\
那我们现在说我们不仅至少对这两个地方操作一次，并且我们只可能在其中一个地方进行操作 $2$。\
我们考虑假设两个地方都进行操作 $2$，其实它们的操作贡献都是让 $s_i$ 与 $s_{n-i+1}$ 的差 $-1$。那么与其可能多花一些移动操作不如只在其中一个地方操作。
#### 3
我们只会在 $s_{\lceil{\frac{n}{2}}\rceil}$ 的一侧操作。\
我们来证明一下：\
假设我们的 $p$ 在 $\lceil{\frac{n}{2}}\rceil$ 左边，那么我们要去 $\lceil{\frac{n}{2}}\rceil$ 右边就一定要跨过 $\lceil{\frac{n}{2}}\rceil$，根据第 $2$ 个观察，我们所走的 $\lceil{\frac{n}{2}}\rceil\sim n-p+1$ 这些区间都不会进行 $2$ 操作。那我们跨过右边去只能去更改 $n-p+1\sim n$ 这些区间。\
而我们考虑如果我们到达 $\lceil{\frac{n}{2}}\rceil$ 后向右走的操作都变成向左走，那我们依然可以花费同样的步数走到左侧对称位置。\
而由于 $n-p+1\sim n$ 对称到左边后变成了 $1\sim p-1$，所以我们这样还多出一种先向左走再向右走的方案。所以我们这种策略一定是不劣甚至更优的。
## 最终解法
最终答案我们分为移动代价和更改代价分类讨论，更改代价我们在第 $1$ 个观察时已经确定好策略了，并且这些无论如何移动都是固定的代价。\
接下来我们考虑移动代价，我们可以记录需要更改的最左和最右位置，若起始点在这两个位置之间，那么我们就取向左或向右最近的点，这样可以使得多余路径最短。若起点在这两点之外，那直接走到最远的那个点就不会产生任何多余路径，一定是最优的。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,pos,ans;
string s,s1,s2;
signed main(){
    cin>>n>>pos>>s;
    if(n&1){
        if(pos==n/2+1){ans++;pos--;}
        else if(pos>n/2)pos--;
        s=s.substr(0,n/2)+s.substr(n/2+1);
    }
    n=(int)s.size();
    if(pos>n/2){
        pos=n-pos+1;
    }
    s1=s.substr(0,n/2);s2=s.substr(n/2);
    reverse(s2.begin(),s2.end());
    pos--;
    int l=0,r=n/2-1;
    for(;l<=r;++l){
        if(s1[l]!=s2[l])break;
    }
    for(;l<=r;--r){
        if(s1[r]!=s2[r])break;
    }
    if(l>r){
        cout<<"0\n";
        return 0;
    }
    ans+=r-l;
    if(pos>l&&pos<r){
        ans+=min(pos-l,r-pos);
    }else if(pos<=l){
        ans+=l-pos;
    }else{
        ans+=pos-r;
    }
    for(int i=l;i<=r;++i){
        int d=max(s1[i],s2[i])-min(s1[i],s2[i]);
        ans+=min(d,26-d);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

