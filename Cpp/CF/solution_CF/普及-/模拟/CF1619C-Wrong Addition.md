# Wrong Addition

## 题目描述

Tanya is learning how to add numbers, but so far she is not doing it correctly. She is adding two numbers $ a $ and $ b $ using the following algorithm:

1. If one of the numbers is shorter than the other, Tanya adds leading zeros so that the numbers are the same length.
2. The numbers are processed from right to left (that is, from the least significant digits to the most significant).
3. In the first step, she adds the last digit of $ a $ to the last digit of $ b $ and writes their sum in the answer.
4. At each next step, she performs the same operation on each pair of digits in the same place and writes the result to the left side of the answer.

For example, the numbers $ a = 17236 $ and $ b = 3465 $ Tanya adds up as follows:

 $ $$$ \large{ \begin{array}{r} + \begin{array}{r} 17236\\ 03465\\ \end{array} \\ \hline \begin{array}{r} 1106911 \end{array} \end{array}}  $ $ </p><ul> <li> calculates the sum of  $ 6 + 5 = 11 $  and writes  $ 11 $  in the answer. </li><li> calculates the sum of  $ 3 + 6 = 9 $  and writes the result to the left side of the answer to get  $ 911 $ . </li><li> calculates the sum of  $ 2 + 4 = 6 $  and writes the result to the left side of the answer to get  $ 6911 $ . </li><li> calculates the sum of  $ 7 + 3 = 10 $ , and writes the result to the left side of the answer to get  $ 106911 $ . </li><li> calculates the sum of  $ 1 + 0 = 1 $  and writes the result to the left side of the answer and get  $ 1106911 $ . </li></ul><p>As a result, she gets  $ 1106911 $ .</p><p>You are given two positive integers  $ a $  and  $ s $ . Find the number  $ b $  such that by adding  $ a $  and  $ b $  as described above, Tanya will get  $ s $ . Or determine that no suitable  $ b$$$ exists.

## 说明/提示

The first test case is explained in the main part of the statement.

In the third test case, we cannot choose $ b $ that satisfies the problem statement.

## 样例 #1

### 输入

```
6
17236 1106911
1 5
108 112
12345 1023412
1 11
1 20```

### 输出

```
3465
4
-1
90007
10
-1```

# 题解

## 作者：smartdevil (赞：1)

# 题意：
现在定义一种新的加法运算，每一位相加直接写到左侧，例

 $17236+3465$ 会被写成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/io3kvuw4.png)

算出 $6+5=11$，在答案中写入 $11$。

算出 $3+6=9$，并将结果写到答案的左侧得到 $911$。

算出 $2+4=6$，并将结果写到答案的左侧得到 $6911$。

算出 $7+3=10$，并将结果写在答案的左侧得到 $106911$。

算出 $1+0=1$，并将结果写到答案的左侧得到 $1106911$。

告诉你 $a,c$，请你回答一个 $b$ 使得 $a+b=c$。

 本题有多组数据

# 想法：
不难看出，$b$ 是唯一的，正面来做可能比较麻烦，但是给了和与加数，可以将加法改为减法，让 $c-a$ 来得到 $b$。

如果 $c_i \geq a_i$，说明两个加数 $a_i$ 和 $b_i$ 相加的和没有进位，那就直接用 $c_i-a_i$。

也可以直接判断，当 $c_i<a_i$ 时把前面的数乘十加上被减数，判断是否是 $c_i\geq 10$。如果是，存入数组，否则输出 $-1$。

如果 $c_i<a_i$，那么就看前一位是否为 $1$，如果不为 $1$，那就是两个数相加进了不止 $1$ 位，显然无解，输出 $-1$；如果是 $1$，那 $c_i+10-a_i$ 就可以了。

如果其中一个数的数位输出完了，另一个数还有剩余，那也是无解，输出 $-1$。

---

## 作者：Charles_with_wkc (赞：1)

# 思路：
告诉你 $?$ 和 $c$ 请你求出一个 $b$，使得 $a + b = c$，我们可以转变一下思路，变成 $a - c = b$ 这样的问题。然后直接暴力减法。
# 分析：
很明显存储用 string，最后输出答案用 long long，很简单我们可以考虑一种极端情况 $a = 1$ 并且 $c = 10^{18}$ 那么不开 long long 见祖宗。
# 判断：
1. 判断当前的被减数是否比减数要大：如果比它大，就正常减；如果比它小，**被减数前面的数乘十加上被减数**，再减去减数。在被减数比减数小时，判断得出的数字是否大于 $10$ 或者小于 $0$。

2. 如果大于 $10$ 则输出 $-1$，否则进行存储。

3. 如果长度不相等直接输出 $-1$。

4. 输出结果的时候，记得去除前导 $0$。

# 核心代码
```cpp
if(c.size()<a.size()){
	cout<<-1<<endl;
	continue;
}
if(c[i]<a[j]&&(c[i-1]-'0')*10+(c[i]-'0')-(a[j]-'0')>=0){
	if(n[top]>=10||n[top]<0){
		cout<<-1<<endl;
		flag=1;
		f=1;
		break;
	}
	else{
		n[top]=(c[i-1]-'0')*10+(c[i]-'0')-(a[j]-'0');
	}
	top++;
	i--;
}
else if(c[i]<a[j]){
	cout<<-1<<endl;
	flag=1;
	f=1;
	break;
}
if(flag==0){
	int x=0;
	for(int i=top-1;i>=0;i--){
		if(a[i]==0&&x!=1){
			continue;
		}
		else if((a[i]!=0)||(a[i]==0&&x==1)||(a[i]-'0')){
			if(a[i]>=10){
				a[i]-='0';
			}
			x=1;
			f++;
			cout<<a[i];
		}
	}
	cout<<endl;
}
if(f==0){
	cout<<-1<<endl;
}
```
本人没有 CFOJ 的账号，所以就不展示 $\text{\color{green}AC}$ 代码了。

---

## 作者：Tulip_ (赞：1)

~~因为其他大佬的都看不懂，而自己解出来了，就想着讲清楚点。~~

也是作为蒟蒻视角讲解。

### 题意

告诉你 $a, c$，请你回答一个 $b$ 使得 $a + b = c$，但是方法不同。

例子如下。

$\large \begin{array}{r} \begin{array}{r} 1106911\\ -\ 17236\\ \end{array} \\ \hline \begin{array}{r} 3465 \end{array} \end{array}$

因为 $1<6$，所以要用 $11-6$，得到 $5$。

而下一个就是 $9-3$，得到 $6$。

以此推理，就得到 $3465$。

### 思路

我们需要 `long long` 的 $T$，`string` 的 $a,c$，最后是储存答案的 `long long` 的 $n_{20}$。

之后就是暴力（按照顺序倒着减）。

---

#### 我们需要判断：

1. 判断当前的被减数是否比减数要大。

如果比它大，就正常减；

如果比它小，就**将被减数前面的数乘十加上被减数**，再减去减数。

例如：$13-5$，$3$ 比 $5$ 小，所以我们要将 $3$ 前面的 $1 \times 10$ 得到 $13$，再减去 $5$，得到 $8$。

2. 在被减数比减数小时，判断得出的数字是否大于 $10$ 或者小于 $0$。

如果大于 $10$，说明不成立，输出 `-1`，**记得标记**；如果小于 $10$，就将它**储存进数组**。

#### 一，二步骤，代码如下。

```cpp
if(c[i]<a[j]&&(c[i-1]-'0')*10+(c[i]-'0')-(a[j]-'0')>=0){
  //j是a的移动坐标，i是cj是a的移动坐标。（步骤一）
	if(n[o]>=10||n[o]<0){//步骤二
		cout<<-1;		
		p=1,l=1;
		break;
	}else{
		n[o]=(c[i-1]-'0')*10+(c[i]-'0')-(a[j]-'0');
	}
	o++;
	i--;
	}else if(c[i]<a[j]){
		cout<<-1;
		p=1,l=1;
		break;
	}
```

3. 在这因为害怕有特殊情况，所以判断了 $a,c$ 的大小比较，这就不用多说。

#### 步骤三，代码如下。

```cpp
if(c.size()<a.size()){
	cout<<-1<<endl;
	continue;
}
```

4. 随后就是输出答案，在**这可能有前导 $0$**，所以也要**加标记**。

但是我们之前的标记，也要判断。

如果输出过 `-1`，则不管；否则输出答案，答案**不用加空格**。

但看到题目，多组数据，则输出完每个答案，就要统一换行。

#### 步骤四，代码如下。

```cpp
if(p==0){
	int v=0;
	for(int i=o-1;i>=0;i--){
		if(a[i]==0&&v!=1)continue;
		else if((a[i]!=0)||(a[i]==0&&v==1)||(a[i]-'0')){
			if(a[i]>=10)a[i]-='0';
				v=1,l++,cout<<a[i];
		}
	}
}
if(l==0)cout<<-1;
cout<<endl;//统一换行
```

整体代码就简单啦！

自己思考把空的地方补种补充出来吧！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
string a,c; 
int n[20];
signed main(){
    cin>>T;
	while(T--){
		//补充步骤吧！
	}
	return 0;
}
```

~~不要把上面的代码复制过来，会错的哟！~~

[AC](https://www.luogu.com.cn/record/162430153)

---

## 作者：Skykguj (赞：1)

我是蒟蒻，不会大佬们那些高深的做法，就模拟一下吧。

### 题意分析：

现在定义一种新的加法运算，每一位相加直接写到左侧，不进位，例如：

$17236 +3465$ 会被写成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/io3kvuw4.png)

算出 $6+5=11$，在答案中写入 $11$。  
算出 $3+6=9$，并将结果写到答案的左侧得到 $911$。  
算出 $2+4=6$，并将结果写到答案的左侧得到 $6911$。  
算出 $7+3=10$， 并将结果写在答案的左侧得到 $106911$。  
算出 $1+0=1$，并将结果写到答案的左侧得到 $1106911$。

所以得到 $17236 +3465 = 1106911$。

告诉你 $a, c$，请你回答一个 $b$ 使得 $a + b = c$。

我的想法是定义一种新的减法运算，是加法运算的逆运算，算出 $c - a$ 的结果 $res$，如果 $c = plus(a, res)$，输出 $res$ 否则输出 $-1$。

### 加法代码

```cpp
long long plus (long long res, long long sub)
{
    std::vector <int> tmp;
    std::string ansstr;
    long long maxn = std::max(res, sub);
    while (maxn > 0)
    {
        tmp.insert(tmp.begin(), sub % 10 + res % 10); // 将每两位结果求出
        sub /= 10, maxn /= 10, res /= 10;
    }
    for (int i = 0; i < tmp.size(); i++) ansstr += std::to_string(tmp[i]); // 合并为字符串
    return std::atoll(ansstr.c_str()); // 转为 int
}
```

### 减法代码

 - 若无解，则求出一个错误的结果。

```cpp
while (after > 0)
{
    bsub = after % 10; after /= 10;
    sub = before % 10; before /= 10;
    if (sub > bsub) 
    {
        if (bsub == 0) bsub = after % 10 * 10;
        else bsub = bsub + after % 10 * 10;
        after /= 10;
    }
    ans.insert(ans.begin(), bsub - sub);
}

if (ans.front() == 0) ans.erase(ans.begin());
long long res = 0;
for (int i = 0; i < ans.size(); i++) { res += ans[i]; res *= 10; }
res /= 10;
```

### Code :

```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

std::vector <short int> ans;
long long t, before, after;

long long plus (long long res, long long sub)
{
    std::vector <int> tmp;
    std::string ansstr;
    long long maxn = std::max(res, sub);
    while (maxn > 0)
    {
        tmp.insert(tmp.begin(), sub % 10 + res % 10);
        sub /= 10, maxn /= 10, res /= 10;
    }
    for (int i = 0; i < tmp.size(); i++) ansstr += std::to_string(tmp[i]);
    return std::atoll(ansstr.c_str());
}

int main()
{
    std::cin >> t;

    while (t--)
    {
        long long bsub = 0, sub = 0, tb, ta;
        std::cin >> before >> after;
		
        // before 加法运算之前的数，即减数，after 同理，为被减数。
        
        tb = before, ta = after; // 备份减数和被减数，后面运算会改变 before 和 after。

        while (after > 0)
        {
            bsub = after % 10; after /= 10;
            sub = before % 10; before /= 10;
            if (sub > bsub) 
            {
                if (bsub == 0) bsub = after % 10 * 10;
                else bsub = bsub + after % 10 * 10;
                after /= 10;
            }
            //std::cout << bsub << '-' << sub << std::endl;
            ans.insert(ans.begin(), bsub - sub);
        }

        if (ans.front() == 0) ans.erase(ans.begin());
        long long res = 0;
        for (int i = 0; i < ans.size(); i++) { res += ans[i]; res *= 10; }
        res /= 10;
        if (plus (res, tb) != ta) res = -1; // 若无解，输出 -1。
        while(!ans.empty()) { ans.erase(ans.begin()); } // 每一轮回答后要清空 ans。
        std::cout << res << std::endl;
    }
    return 0;
}
```

---

## 作者：StayAlone (赞：1)

### 题意
现在定义一种新的加法运算，每一位相加直接写到左侧，例如：

$17236 +3465$ 会被写成这样：

![](https://i.niupic.com/images/2021/12/26/9StC.png)

~~不知道为啥这个 Latex 放到这里显示不出来。。。~~

算出 $6+5=11$，在答案中写入 $11$。  
算出 $3+6=9$，并将结果写到答案的左侧得到 $911$。  
算出 $2+4=6$，并将结果写到答案的左侧得到 $6911$。  
算出 $7+3=10$， 并将结果写在答案的左侧得到 $106911$。  
算出 $1+0=1$，并将结果写到答案的左侧得到 $1106911$。  

所以得到 $17236 +3465 = 1106911$。

告诉你 $a, c$，请你回答一个 $b$ 使得 $a + b = c$。  

**本题有多组数据。**

### 思路

经过简单的思考，可以发现 $b$ 是唯一的。因为每一位进位与不进位的个位互不相同。所以可以双指针直接模拟。

如果这一位上 $c_i \geqslant a_i$，说明不进位；反之就是进位了。不进位的时候这一位 $b_i = c_i - a_i$。进位的时候判断一下 $c_i$ 往前一位是不是 $1$，如果不是就无解。如果是 $c_i = c_i + 10 - a_i$。

如果有一个数走完了，还有一个数没走完，也是无解。

注意一下实现的细节，就没了。

[AC code 记录](https://www.luogu.com.cn/record/65826251)  

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i = j; i <= int(n); ++i)
#define rep2(i, j, n) for (int i = j; i >= int(n); --i)
#define rep(i, x) for (int i = pnt[x]; i; i = nxt[i])
#define ptc putchar
#define ......
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 1e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc
{
	template <typename T>
	il void read(T &x)
	
	template <typename T>
	il void write(T x)
}
// 奇妙缺省源
using namespace stupid_lrc;
string a, b, ans;

il bool ct(string k, int y, int len)
{
	rep1(i, y, len - 1) if (k[i] ^ '0') return false;
	return true;
}

int main()
{
	int T = read(); while (T--)
	{
		cin >> a >> b; ans = "";
		int len1 = a.size(), len2 = b.size();
		if (len2 < len1)
		{
			puts("-1"); continue;
		}
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		while (len1 < len2) ++len1, a += '0';
		while (len1 > len2) ++len2, b += '0';
		int l = 0, r = 0; bool f = true;
		while (r < len2)
		{
			if (b[r] >= a[l]) ans += char(b[r] - a[l] + '0'), ++l, ++r;
			else if (r + 1 > len2 - 1 || b[r + 1] != '1')
			{
				f = false; break;
			}
			else ans += char(10 + b[r] - '0' - a[l] + '0' + '0'), ++l, r += 2;
		}
		f = ct(a, l, len1) && ct(b, r, len2);
		reverse(ans.begin(), ans.end());
		int t = 0, x = ans.size();
		while (ans[t] == '0' && t + 1 < x) ++t;
		string opt = "";
		rep1(i, t, x - 1) opt += ans[i];
		if (!f) puts("-1"); else cout << opt << '\n';
	}
	rout;
}
```

---

## 作者：joker_opof_qaq (赞：1)

### 题目大意

定义一个新运算，将进位写到当前位的前面的加法。

给你一个加数，和运算结果，求另一个加数。

### 做法

算出来当前两个末尾之差，设它为 $t$：

-  如果 $t \geq 0$ 则直接将 $b$ 这一位设为 $t$。
  
-  如果 $t < 0$ 看前一位，如果为 $1$ 则将 $t+10$ 加入 $b$ 的末尾。

-  如果 $t < 0$ 且前一位不等于 $1$ 则无解。

代码就不给了，大模拟自己模拟就行了。

---

## 作者：mcDinic (赞：0)

[更好的阅读体验](https://www.cnblogs.com/yjy-3054188405/p/16497571.html)

似乎没人写记忆化搜索的，我就来一波（当然，写动态规划也是可以的，毕竟记忆化搜索只是动态规划的递归形式，不过蒟蒻太菜了，只想到搜索，而没有一开始就想到动规）。

我们把加法转化成减法，开始分割数字 $c$，枚举情况。由于 $b$ 是十进制的，所以 $c$ 的每一段都由一个或两个数字组成（把这一段组成的数减去 $a$ 对应的数字，就能算出 $b$ 这一位是多少），至于判别条件很容易想到，详见代码。

为了保险起见，我还加了个记忆化，这样对于不行的情况，遇到可直接剪枝（其实这种橙题根本不需要记忆化，当然写都写了，我也不把它删除）。

## Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define linf 0x3f3f3f3f3f3f3f3f
#define inf 0x7fffffff
#define v e[i].y
using namespace std;
inline ll read(){
    char ch=getchar();ll x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();return x*w;
}
inline void write(ll x){
	if(x<0)x=-x,putchar('-');
    if(x<10){putchar(48+x);return;}
    write(x/10),putchar((x+10)%10+48);
}
ll T=read(),a,c,aa[25],cc[25],at,ct,ans[25],t;
bool dp[25][25];
bool dfs(int x,int y){//x:c,y:a
    if(x==ct)return y>=at?1:(dp[x][y]=0);
    if(dp[x][y]==0)return 0;
    if(cc[x+1]-aa[y+1]>=0&&cc[x+1]-aa[y+1]<10){
        ans[++t]=cc[x+1]-aa[y+1];
        if(dp[x+1][y+1]=dfs(x+1,y+1))return 1;
        t--;
    }
    if(x<=ct-2&&cc[x+2]!=0&&cc[x+2]*10+cc[x+1]-aa[y+1]>=0&&cc[x+2]*10+cc[x+1]-aa[y+1]<10){
        ans[++t]=cc[x+2]*10+cc[x+1]-aa[y+1];
        if(dp[x+2][y+1]=dfs(x+2,y+1))return 1;
        t--;
    }
    return dp[x][y]=0;
}
int main(){
    while(T--){
        memset(aa,0,sizeof(aa));
        memset(cc,0,sizeof(cc));
        for(int i=0;i<=23;i++)for(int j=0;j<=23;j++)dp[i][j]=1;
        a=read(),c=read(),at=ct=t=0;
        while(a)aa[++at]=(a+10)%10,a/=10;
        while(c)cc[++ct]=(c+10)%10,c/=10;
        if(dfs(0,0)){
            while(t&&ans[t]==0)t--;
            if(t==0)ans[++t]=0;
            for(int i=t;i>=1;i--)putchar(ans[i]+48);
        }
        else printf("-1");
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：yanhao40340 (赞：0)

题意已经说的很清楚了。不懂的看题面。

既然定义了一种新的加法，那么我们就可以定义其逆运算——减法。

运算规则其实很简单。例如 $401106911-17236$ ：

1. 先用 $1-6$ ，发现不够减，那么借一位变成 $11-6$ ，得 $5$ 。

2. 然后用 $9-3$ ，可以减，那么得 $6$ 。

3. 接着用 $6-2$ ，可以减，那么得 $4$ 。

4. 之后用 $0-7$ ，不够减，借一位之后得 $3$ 。

5. 最后用 $1-1$ ，减完了，得 $0$ 。

目前答案为 $03465$ 。

之后我们发现被减数还有 $40$ 没有参与运算，那么就把 $40$ 补到答案前面。

所以 $401106911-17236=4003465$ 。

现在还需要判无解。显然，如果最后被减数减完了仍然不够减，那么直接无解。

而且如果要借位，那么被借的那一位只能是 $1$ 。

实现起来是 $O(\log n)$ 的，可以通过本题（而且还挺快）。

###代码

```cpp
#include <iostream>
#include <string>
#define num(x) (x-'0')
using namespace std;
typedef long long ll;//不开long long见祖宗
string getstr(){//字符串输入加速模板
	char f='\0';string s;
	while (f=='\n'||f=='\0'||f==' ') f=getchar();
	while (f!='\n'&&f!='\0'&&f!=' ') s+=f,f=getchar();
	return s;
}
ll Pow(ll power,ll base){//快速幂（其实还没预处理快）
	ll res=1;
	while (base){
		if (base&1) res=power*res;
		power=power*power,base>>=1;
	}
	return res;
}
ll operator -(string s,string t){//重载运算-
	if (s.size()<t.size()) return -1;
	int tmps=s.size()-1,tmpt=t.size()-1;ll ans=0,tmp=0;
	while (tmpt!=-1){
		if (tmps==-1) return -1;
		if (s[tmps]>=t[tmpt]) ans+=(s[tmps]-t[tmpt])*Pow(10,tmp),--tmps,--tmpt;
		else if (tmps==0) return -1;
		else if (s[tmps-1]!='1') return -1;
		else ans+=(10+num(s[tmps])-num(t[tmpt]))*Pow(10,tmp),tmps-=2,--tmpt;
		++tmp;
	}
	if (tmps>=0){
		for (int i=tmps;i>=0;--i)
			ans+=num(s[i])*Pow(10,tmp),++tmp;
	}
	return ans;
}
int main(){
	int t;scanf("%d",&t);
	while (t--){
		string a=getstr(),b=getstr();
		printf("%lld\n",b-a);
	}
	return 0;
} 
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

现在定义一种新的加法运算，每一位相加直接写到左侧，例如：

$17236+3465$ 会被写成这样：

$$~~~17236$$

$$+03465$$

$$----------$$

$$1106911$$

算出 $6+5=11$，在答案中写入 $11$。  

算出 $3+6=9$，并将结果写到答案的左侧得到 $911$。 

算出 $2+4=6$，并将结果写到答案的左侧得到 $6911$。 

算出 $7+3=10$， 并将结果写在答案的左侧得到 $106911$。 

算出 $1+0=1$，并将结果写到答案的左侧得到 $1106911$。  

所以得到 $17236 +3465 = 1106911$。

告诉你 $a, c$，请你回答一个 $b$ 使得 $a + b = c$。  

# 题目分析

观察题目，发现实际上就是把进位也作为结果的加法。

因为我们要做减法，所以如果相减的时候减出负数就进位即可。

# 代码

```cpp
int T;

int main(){
    cin >> T;
    while(T--){
    	string A,S; 
        cin >> A >> S;
        lenA = A.length() , lenS = S.length();
        rep(i,0,lenA-1) a[lenA-i] = A[i] - '0';
        rep(i,0,lenS-1) s[lenS-i] = S[i] - '0';
        rep(i,0,lenS+1) b[i] = 0; 
        int j = 1 , i = 1 , p;
        bool ans = true;
        while(1){
            p = i;
            if(j > lenS) break;
            if(i > lenA) a[i] = 0;
            if(s[j] >= a[i]){
                b[i] = s[j] - a[i];
                j += 1;
            } else{
                if(s[j+1] > 1 || s[j+1] < 1){
                    ans = false;
                    break;
                }
                b[i] = s[j] + s[j+1] * 10 - a[i];
                j += 2;
            }
            ++i;
        }
        if(!ans || i <= lenA){
            cout << "-1\n";
            continue;
        }
        bool leadZero = true;
        bool isZero = true;
        per(i,p,1){
            if(b[i]) leadZero = false;
            else if(leadZero) continue;
            cout << b[i];
            isZero = false;
        }
        if(isZero) cout << "-1";
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：heaksicn (赞：0)

## 1 题意
对于两个数 $a$ 和 $b$ ，定义加法为：
- 将较短的数补上前导 $0$
- 从低到高枚举，将每一位的数字相加，放至答案的前面
- 记答案为 $s$
现在给出 $a$ 和 $s$ ，请求出 $b$ 。  
多组数据。
## 2 思路
~~大模拟题~~。  
首先，将 $s$ 和 $a$ 的每一位分离出来，将长度记为 $lens$ 和 $lena$ 。  
枚举 $a$ 的每一位，将 $s$ 现在的指针与 $a_i$ 相减。  
如果差小于 $0$ ，再枚举 $s$ 的下一位，如果差大于 $9$ 的话，那么直接无解。  
否则记录答案。  
将 $s$ 剩下的位数直接补到 $b$ 的后面。  
最后输出即可。  
时间复杂度 $O(Tlena)$。
## 3 code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int T;
int a[25],s[25],b[25];
ll q,p;
int lb;
bool check(){//查看答案是否为0（好像没用）
	for(int i=1;i<=lb;i++){
		if(b[i]) return 0;
	}
	return 1;
}
int main(){
	T=read();
	while(T--){
		cin>>q>>p;
		int la=0;
		while(q){//分离数位
			a[++la]=q%10;
			q/=10;
		}
		int ls=0;
		while(p){//分离数位
			s[++ls]=p%10;
			p/=10;
		}
		ll ans=0;
		bool flag=0;
		int qp=1;
		lb=0;
		for(int i=1;i<=la;i++){//枚举每一位
			if(qp>ls){//a>s
				cout<<-1;
				flag=1;
				break;
			}
			int now=s[qp]-a[i];//差
			if(now<0){//差小于0
				qp++;//枚举下一位
				if(qp>ls){
					cout<<-1;
					flag=1;
					break;
				}
				now+=10*s[qp];//加上
			}
			if(now>9||now<0){//还是不行
				cout<<-1;//输出-1
				flag=1;
				break;
			}
			b[++lb]=now;//下一位
			qp++;
		}
		if(qp<=ls){//补足前导0
			for(int i=qp;i<=ls;i++) b[++lb]=s[i];
		}
		if(!flag){
			if(check()){//答案为0
				cout<<0;
				cout<<endl;
				continue;
			}
			bool fl=0;
			for(int i=lb;i>=1;i--){//输出
				if(b[i]!=0) fl=1;//前导0
				if(b[i]==0&&fl==0) continue;
				cout<<b[i];
			}
		}
		cout<<endl;
	}
	return 0;
}
```


---

