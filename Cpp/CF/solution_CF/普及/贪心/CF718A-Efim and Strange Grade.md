# Efim and Strange Grade

## 题目描述

Efim just received his grade for the last test. He studies in a special school and his grade can be equal to any positive decimal fraction. First he got disappointed, as he expected a way more pleasant result. Then, he developed a tricky plan. Each second, he can ask his teacher to round the grade at any place after the decimal point (also, he can ask to round to the nearest integer).

There are $ t $ seconds left till the end of the break, so Efim has to act fast. Help him find what is the maximum grade he can get in no more than $ t $ seconds. Note, that he can choose to not use all $ t $ seconds. Moreover, he can even choose to not round the grade at all.

In this problem, classic rounding rules are used: while rounding number to the $ n $ -th digit one has to take a look at the digit $ n+1 $ . If it is less than $ 5 $ than the $ n $ -th digit remain unchanged while all subsequent digits are replaced with $ 0 $ . Otherwise, if the $ n+1 $ digit is greater or equal to $ 5 $ , the digit at the position $ n $ is increased by $ 1 $ (this might also change some other digits, if this one was equal to $ 9 $ ) and all subsequent digits are replaced with $ 0 $ . At the end, all trailing zeroes are thrown away.

For example, if the number $ 1.14 $ is rounded to the first decimal place, the result is $ 1.1 $ , while if we round $ 1.5 $ to the nearest integer, the result is $ 2 $ . Rounding number $ 1.299996121 $ in the fifth decimal place will result in number $ 1.3 $ .

## 说明/提示

In the first two samples Efim initially has grade $ 10.245 $ .

During the first second Efim can obtain grade $ 10.25 $ , and then $ 10.3 $ during the next second. Note, that the answer $ 10.30 $ will be considered incorrect.

In the third sample the optimal strategy is to not perform any rounding at all.

## 样例 #1

### 输入

```
6 1
10.245
```

### 输出

```
10.25
```

## 样例 #2

### 输入

```
6 2
10.245
```

### 输出

```
10.3
```

## 样例 #3

### 输入

```
3 100
9.2
```

### 输出

```
9.2
```

# 题解

## 作者：Binary_Lee (赞：4)

## [题面传送门](https://www.luogu.com.cn/problem/CF718A)

### 解决思路

首先考虑贪心。在小数部分，一定是越靠前的四舍五入结果越大。比如 $0.142638$，如果你先四舍五入 $8$ 变成 $0.14264$ ，那就白白浪费了一次机会，因为如果直接四舍五入 $6$ 可以变成更大的 $0.143$ 。

那多次四舍五入机会有什么用呢？就是你把第一个可行的数四舍五入后，就可能发生连锁反应，产生新的可以四舍五入的数，详见样例二。

所以我们确定了基本思路：找出小数部分第一个可以四舍五入的数，操作后看能不能产生新的可以四舍五入的数，直到无法操作或次数用完为止。

同时需要注意一些细节。例如，若小数部分第一位若可以四舍五入，就要改动整数部分，因此也就没有小数部分了。同时，处理整数部分时还可能出现满 $10$ 进位的情况。小数部分不会出现 $10$ 进位的情况，因为可以满 $10$ 进位的话，只可能是前一位为 $9$，而 $9$ 可以四舍五入，所以就不会扫到这一位。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long 
using namespace std;
string s;
int n,t,z[200005],x[200005],i,cz,cx,lst;
bool fl;
signed main(){
	IOS;TIE;
	cin>>n>>t>>s;
	for(i=0;s[i]!='.';i++)  z[++cz]=s[i]-'0';
	i++;
	for(;i<s.size();i++) x[++cx]=s[i]-'0';
	lst=cx;
	for(int i=1;i<=cx;i++){
		if(x[i]>=5){   //找到第一个可以四舍五入的
			for(int j=i;j>=1;j--){
				if(x[j]>=5) lst=j-1,x[lst]++,t--;  //连锁反应
				if(!t) break;  //次数不够了
			}
			break;
		}
	}
	if(x[0]){   //向整数进位
		fl=1;
		int tmp=cz;
		z[tmp]++;
		while(z[tmp]>9) z[tmp-1]++,z[tmp]=0,tmp--;  //满10进位
	}
	if(z[0]) cout<<z[0];
	for(int i=1;i<=cz;i++) cout<<z[i];
	if(!fl){   //是否有小数部分
		cout<<'.';
		for(int i=1;i<=lst;i++) cout<<x[i];
	}
	cout<<endl;
	return 0;
} 
```

---

## 作者：When (赞：2)

#### 算法

贪心+无数有趣的细节

**高能预警：** 本题**细节较多**，请仔细食用。

#### 思路

从小数点往后搜，直到遇见第一个$\geq 5$的数字，它就是我们要四舍五入的第一个。然后从它开始往回搜，只要$\geq 5$就四舍五入。

#### 正确性

小数点后位数靠前的数字越大，值越大，所以我们将第一个能“$5$入”的点“入”掉（因为这样才能使得“入”过去的$1$价值最大）。

那为什么往回搜的时候能入则入呢？

+ 因为往回搜的数必然是小于$5$的，只有当前的数往前进了位才有可能$\geq 5$，所以我们只能给当前数进位（如果它可以）。

#### 细节

+ 整数位上不能四舍五入（但可以进位）！
+ 小数位与整数位的进位要分开处理！
+ 可能出现一个也不能进的情况！
+ 整数的最高位有可能进$1$！ （如：$99.459$）
+ 记得判断没有小数点的情况！

大概就这么多了……

#### 参考代码

```cpp
/*
 * @Author: When_C 
 * @Date: 2020-11-19 19:29:11 
 * @Last Modified by: When_C
 * @Last Modified time: 2020-11-19 19:49:45
 */
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 2e5 + 10;
int n,t,a[maxn],top;
char c[maxn];

int main(){
    scanf("%d%d%s", &n, &t, c + 1);
    int loc,pos = -1;
    for(int i = 1; i <= n; ++ i){
        if(c[i] >= '0' && c[i] <= '9') a[++top] = c[i] - '0';
        else loc = top + 1;
    }
    for(int i = loc; i <= top; ++ i)
        if(a[i] >= 5){pos = i; break;}
    if(pos > 0){
        int pre = 1; pos -= 1; t -= 1;
        for(int i = pos; i >= 1; -- i){
            if(!pre && (!t || i < loc)) break;
            a[i] += pre; pre = 0;
            if(a[i] > 10) pre = 1, a[i] %= 10;
            if(a[i] == 10){
                pre = 1; a[i] %= 10;
                if(i >= loc) pos -= 1;
            } 
            if(a[i] >= 5 && t && i >= loc) pre += 1, pos -= 1, t--;
        }
        if(pre) a[0] = 1;
    }
    if(a[0]) printf("%d", a[0]);
    for(int i = 1; i <= pos; ++ i){
        printf("%d", a[i]);
        if(i == loc - 1 && i != pos) printf(".");
    }
    if(pos < 0) printf("%s", c + 1);
    return 0;
}
```



---

## 作者：世末OIer (赞：2)

其实，这一道题除了贪心，我们还可以dp。

dp[i]表示考虑到第i位时最少需要多少次才能使它进位。

三种情况：

s[i]>'4':只需要一次，直接进位。

s[i]=='4':dp[i+1]+1次（在+1后才能进位）

s[i]<'4' :dp[i]=INF (完全没有指望，因为进位只能进一次)

我们知道，越靠近小数点的四舍五入的效率越高。

所以说，我们只需要从小数点往后枚举，只要dp[i]<=t就是答案了。

下面贴上代码:

```cpp

#include<bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
#define ll long long
#define mp make_pair
using namespace std;
string s;
int n,t;
const int Mx=1e9+7;
int dp[200005];
int main(){
	int i,j;
	cin>>n>>t>>s;
	memset(dp,63,sizeof(dp));
	dp[s.size()]=0;
	for(i=s.size()-1;s[i]!='.';--i){                  //dp
		if(s[i]=='.') break;
		if(s[i]=='4'){
			if(i!=s.size()-1) dp[i]=dp[i+1]+1;
		}else if(s[i]>'4') dp[i]=1;
	}
	for(;i<s.size();++i) if(s[i]!='.') if(dp[i]<=t) break;
	if(dp[i]) ++s[i-1];                           //样例三
	s=s.substr(0,i);                             //后面的没用了
	--i;
	while(s[i]!='.'){
		if(s[i]=='9'+1){
			s[i]='0';
			++s[i-1];
			--i;
		}else break;      //一定要break！
	}
	if(s[i]=='.'+1){
		s[i]='.';
		++s[i-1];
		--i;
		while(i){
			if(s[i]=='9'+1){
				s[i]='0';
				++s[i-1];
				--i;
			}else break;   //一定要break！
		}
		if(s[0]=='9'+1){
			s[0]='0';
			s='1'+s;
		}
	}
	while(s[s.size()-1]==0) s=s.substr(0,s.size()-1);   //去除末尾的0
	if(s[s.size()-1]=='.') s=s.substr(0,s.size()-1);    //去除末尾的小数点
	cout<<s<<endl;
	return 0;
}

```

---

## 作者：Dream_It_Possible (赞：2)

这题是一道十分经典又明显的贪心题。

我们发现小数点后越靠前的**>=5的数“五入”** _价值最大_ ，那我们可以每次贪心的找出从左往右第一个**>=5的数**，更改，再找出从左往右第二个**>=5的数**，更改，以此类推,一直做t次。

对于<=4的数根本无用，无需更改。

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
string s;
int main()
{
    int n,t;
    scanf("%d%d",&n,&t);
    cin>>s;
    int i=0;
    while(s[i]!='.')i++;
    while(i<n&&s[i]<'5')i++;
    if(i==n)
    {
        cout<<s<<endl;
        return 0;
    }
    i--;int len=0;
    while(t>0)
    {
        if(s[i]!='.')
        s[i]++;
        else{
            i--;len=i;
            while(i>=0&&s[i]=='9')s[i--]='0';
            if(i==-1)cout<<'1';
            else s[i]++;
            break;
        }
        if(s[i]<'5')
        {
            len=i;
            break;
        }
        else
        {
            len=i;
            i--;
        }
        t--;
    }
    for(int k=0;k<=len;k++)
        cout<<s[k];
    cout<<endl;
}
```

---

## 作者：Empty_Dream (赞：1)

### CF718A 解题报告

#### 题意 

给你一个长度为 $n$ 的浮点数，**最多**四舍五入 $t$ 次，求可以得到的最大值。

注意：

- 四舍五入之针对小数部分，不针对整数部分。
- 输出时不能有前缀 $0$，和后缀 $0$。
- 当最大的数变成整数了，就不输出小数点。

#### 分析

根据题面，很容易想到要用贪心，只需要再加那么一点的模拟就好了。

贪心的思路非常简单，我们发现当一个数四舍五入后，它后面的数都会变成 $0$，所以我们可以选择尽可能靠左的位置进行四舍五入，使得最终结果最大。

先找到第一个可以四舍五入的位置，即在小数点之后且大于等于 $5$ 的数；然后模拟每一次进位，在过程中特判一下是否小数部分全没了，如果没了就向整数部分进位。

输出的时候再特判一下小数点是否在最后一位，最后输出就好了。

~~优化~~：在处理四舍五入进位的时候可以不用实时的 `erase` 可以直接将 $n$ 减去 $1$ 来实现缩短长度的效果，输出的时候使用 `substr` 进行输出就好了。

#### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int n, t, cnt;
string s;

int main(){
	cin >> n >> t >> s;
	while (cnt < n && s[cnt] != '.') cnt++;
	while (cnt < n && s[cnt] < '5') cnt++;//求出最靠左的可以四舍五入的位置
	if (cnt == n){//特判如果都不能四舍五入
		cout << s;
		return 0;
	}
	while (t > 0 && s[cnt] >= '5'){//当能四舍五入的时候
		n = cnt--;
		if (s[cnt] == '.'){//特判小数部分取完了
			s[--cnt]++;
			while (cnt > 0 && s[cnt] > '9') s[cnt] = '0', s[--cnt]++;//向整数位进位
			if (cnt == 0 && s[cnt] > '9') s = "10" + s.substr(1, n);//特判最高位进位
			break;
		}
		t--, s[cnt]++;
	}
	if (s[n-1] == '.') n--;//特判如果没有小数部分了
	cout << s.substr(0,n);
	return 0;
}
```



---

## 作者：lizulong (赞：1)

## 思路

贪心题，也可以用 dp 做。

就拿 1.299996121 来举例，如果只四舍五入一次的话，舍哪一位会导致结果最大呢？

只需要全部枚举一遍，不难发现，对于所有舍的情况，更新后的数会小于不舍的数，所以凡是舍的情况都可以跳过。

而对于能进位的数，越靠近小数点，进位之后的数越大，所以对于从左至右的第一个能进位的数对其操作是最有利的。

但如果能操作不止一次该怎么办呢？

我们拿样例 2 举例。
```
in
6 2
10.245

out
10.3
```
显然，样例是先操作千分位，进位之后再操作百分位。

也恰巧说明，我们找到第一个能进位的数之后，只需要往反方向搜，一直搜到小数点或操作次数不够为止。

### 代码（WA）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,t,m,r;
string in; 
void jinwei(int x){	
	if(x==m || t<=0) return; 
	if(in[x]>='5' && in[x]<='9')
		in[x-1]++,r=x;
	t--;	
	jinwei(x-1);
	return;
}
signed main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>t;
	r=n;
	cin>>in;
	for(int i=0;i<n;i++) if(in[i]=='.') {m=i;break;}
	if(m==0) m=n;
	for(int i=m+1;i<n;i++){
		if(in[i]>='5' && in[i]<='9'){
			jinwei(i);
			break;//不搜了往回搜
		}
	}
	for(int i=0;i<r;i++) cout<<in[i];
	return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/9n5lnt3v.png)

这个代码可以说是漏洞百出。

- 没有判断满十进一的情况
- 没有判断进位的下一位是小数点的情况
- 输出也没判断特殊情况
- 没有判断进位到了最高位时的情况

把这些全都加上！

## 代码（AC）

[AC记录](https://www.luogu.com.cn/record/127662991)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,t,m,r;//r是用来清后缀的 m是小数点的坐标 
string in; 
void jinwei(int x){	
	if(x==m || t<=0) return;//一直搜到小数点或操作次数不够为止
	if(in[x]>='5' && in[x]<='9'){
		if(in[x-1]=='.') in[x-2]++;//跳过小数点 
		in[x-1]++,r=x;
	}
	t--;	
	jinwei(x-1);//往前递归下去 
	return;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>t;
	r=n;
	cin>>in;
	for(int i=0;i<n;i++) if(in[i]=='.') {m=i;break;}
	if(m==0) m=n;//判断没有小数点的情况 
	for(int i=m+1;i<n;i++){
		if(in[i]>='5' && in[i]<='9'){//只操作能进位的情况 
			jinwei(i);
			break;//不搜了往回搜
		}
	}
	for(int i=r-1;i>=0;i--){//满十进一 
		if(i==0&&in[i]-'0'>=10) cout<<1;//判断进位到了最高位时直接输出1 
		if(in[i]=='.') continue; //跳过小数点 
		if(in[i]-'0'>=10) {
			if(in[i-1]=='.') in[i-2]++;//判断进位到小数点的情况 
			else in[i-1]++;
			in[i]=in[i]-10;
		}
	}
	for(int i=0;i<r;i++)
		if( (in[i]>='0'&&in[i]<='9') || (in[i]=='.') )cout<<in[i];//输出的特殊判断 
	return 0;
}
```
## 总结
该题整体难度不大，只是有很多细节要注意，尤其是小数点。

---

## 作者：H2O_TX (赞：0)

又是一道水题？~~（感觉洛谷上CF题好多都是虚高~~

首先有一个很明显的结论，一定要在从左往右第一个能进位的地方进位，然后接下来就不用管后面的了。

证明方法：小数的大小比较。

接下来就是按照题目模拟，从刚刚确定的那一位开始向前遍历，依次四舍五入。当然，如果这一位无法进位，那就可以直接退出并输出答案了。

**有几个需要注意的点**：

1. 只有整数部分时不要输出小数点。
2. 整数部分可能需要进位，例如 $99.9$。

思路很简单，稍微有些坑。

贴代码（附有注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5+10;
int n,t;
char a[N];

int main()
{
    cin>>n>>t>>a+1;
    int big;
    for(int i=1;i<=n;i++)
        if(a[i]=='.')
        {
            big=i+1;//记录下小数部分的开始
            break;
        }
    int st=n;
    for(int i=big;i<=n;i++)
    {
        if(a[i]<='4') continue;
        while(t&&i>=big&&a[i]>='5')
        {
            if(i==big) a[i-2]++;
            else a[i-1]++;
            i--,t--;
        }
        st=i;//记录下最后一位
        break;
    }
    if(st==big-1) st--;//此时最后一位是".",需要跳过
    int now=st;
    if(st<big)
    {
        a[0]='0';
        while(a[now]>'9')//处理整数部分的进位
        {
            a[now-1]++;
            a[now]='0';
            now--;
        }
    }
    for(int i=min(1,now);i<=st;i++) cout<<a[i];
    return 0;
}

```

### 谢谢观看！


---

## 作者：Ryo_Yamada (赞：0)

很直接的一道题，细节比起大模拟还是少很多。

很显然的贪心，我们每次选取小数点后第一个数位 $>4$ 四舍五入，而每次都不需要重新找，因为这个位置前面的数位一定全部 $\le 4$，所以能够满足 $>4$ 的只有当前进到的这位。

如果都进完了，即没有小数，高精度计算原数的下取整 $+1$ 即可。

$\text{Code}$：

```cpp
int n, T;
string s, t;

int main() {
	cin >> n >> T;
	cin >> s;
	rep(i, 0, s.size() - 1) if(s[i] == '.') {
		t = s.substr(i + 1, s.size() - i - 1);
		break;
	}
	int ps = -1;
	rep(i, 0, t.size() - 1) if(t[i] > '4') {
		ps = i;
		break;
	}
	if(ps == -1) {
		cout << s << endl;
		return 0;
	}
	while(T--) {
		--ps;
		if(ps < 0) {
			string ans = "";
			rep(i, 0, s.size() - 1) if(s[i] == '.') break; else ans += s[i];
			per(i, ans.size() - 1, 0) {
				if(ans[i] == '9') ans[i] = '0';
				else {
					++ans[i];
					break;
				}
			}
			if(ans[0] == '0') {
				pc('1');
				cout << ans << endl;
			}
			else cout << ans << endl;
			return 0;
		}
		++t[ps];
		if(t[ps] < '5') {
			rep(i, 0, s.size() - 1) {
				pc(s[i]);
				if(s[i] == '.') break;
			}
			rep(i, 0, ps) pc(t[i]);
			pc('\n');
			return 0;
		}
	}
	rep(i, 0, s.size() - 1) {
		pc(s[i]);
		if(s[i] == '.') break;
	}
	rep(i, 0, ps) pc(t[i]);
	pc('\n');
	return 0;
}
```


---

