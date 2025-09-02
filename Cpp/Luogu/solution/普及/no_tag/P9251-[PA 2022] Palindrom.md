# [PA 2022] Palindrom

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda próbna [Palindrom](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/pal/)**

Bytie 参加了计算机俱乐部，因此知道了什么是回文串。回文串是从左向右读和从右向左读一样的单词。比如 `oko`，`kajak`，`kobyłamamałybok` 和 `ababbaba` 都是回文串，但是 `kajaki`，`zoo`，`alamakota` 和 `abaababa` 都不是回文串。

他迅速打开了笔记本并写下了一个只包含 `a` 和 `b` 两个字母的单词。然而在回忆了一会儿后，他想起这个单词不一定是一个回文串，因此他决定修改一下！在一秒内，它可以选择两个相邻的字母并交换他们的位置。他是否可以通过有限次操作（或者什么也不做）把这个字符串变成一个回文串？如果可以的话，最少要多少秒才可以？请帮他写一个程序计算这个最小时间。

## 说明/提示

对于 $100\%$ 的数据，满足：

字符串长度不超过 $2 \times 10^5$。

## 样例 #1

### 输入

```
abbaaab
```

### 输出

```
2```

## 样例 #2

### 输入

```
ab```

### 输出

```
-1```

# 题解

## 作者：Kevin_Mamba (赞：5)

### 题意

给定只包含两个字母的字符串，每次操作可交换相邻的两个字母。求将字符串变成一个回文串的最小操作次数。若无法变成回文串，输出 $-1$。

### 解题

看到简短题面，又看到是个灰题，就感觉这题不简单。但其实这题最多评橙。

* 先看不可能的情况。

你会发现，经过无数次操作后，字符串能变成它本身的任意一个排列。

也就是说，只有它本身包含的字母使它不能回文以外，否则他就一定能变回文。

设字符串长度为 $len$，`a` 字符的数量是 $s$。**当且仅当 $len$ 为偶数且 $s$ 为奇数时无解。**

* 再说说有解的最小操作次数。

我们把回文的条件看成是成轴对称。

**假设我们删去一种字符，另一种字符成轴对称的话，那么删去的字符也一定成轴对称，整个字符串就会回文。否则必不回文。**

所以我们就删去字符 `b`，只看 `a`。设 `a` 的位置的数列为 $A(A_i<A_{i+1})$。最优的做法就是要让 位置 $A_k,A_{i-k+1}(k\le\lceil \frac{s}{2}\rceil)$ 成中心轴对称。

代码也就很好写了。

### 写题

$94$ 分的话记得开 $\mathrm {long\ long}$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;

char s[N];

int len,tot,a[N];

long long ans;

bool odd(int x) { return x&1; }

int main() {
	cin>>s;
	len=strlen(s);
	for(int i=0;i<len;i++) {
		if(s[i]=='a') {
			a[++tot]=i+1;	
		}
	}
	if(!odd(len)&&odd(tot)) return puts("-1"),0;
	for(int i=1;i<=(tot>>1);i++) {
		ans+=abs(a[i]-len+a[tot-i+1]-1);
	}
	if(odd(len)&&odd(tot)) {
		ans+=abs(a[(tot+1)>>1]-((len+1)>>1));
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：David_yang (赞：4)

[传送门](https://www.luogu.com.cn/problem/P9251)

第十篇题解，如有不妥请~~忽视~~指出。

## 题目大意：

给你一个只包含 `a` 和 `b` 的字符串，每次操作能交换**相邻**两个字母的位置。问最少经过几次操作能使字符串变成回文串？无解输出 $-1$。

## 算法或数据结构：

只需想一想就可以了。

## 解析：

在讲之前先强调一下，注意是**相邻**字母！！！我就是这样被卡了很久……

首先判断无解。很容易想到，当字符串总长度为偶数且 $a$ 的个数（或 $b$ 的个数）为奇数时无解。这部分比较简单，直接特判就行了。

然后就是正常情况。可以发现，我们现在只需要看 $a$（或 $b$）就行了，因为其中一种字母对称另一种字母也就对称了。我现在以 $a$ 为例。

在输入的时候，我们就把每个 $a$ 的位置记录下来。判断了无解之后计算每个 $a$ 应该移动几次，加起来。最后在输出前，再判断一下 $a$ 的个数是否为奇数，如果是，那么就把最中间的 $a$ 移到整个字符串的最中间，再算一下要以多少次就行了。

我讲得有点抽象，那就看一下我的代码。再提醒一句：**不开 long long 见祖宗！**

## Code:


```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum,a[200005],t;
string s;
int main()
{
	cin>>s;
	int len=s.length();
	for(int i=0;i<len;i++)
	{
		if(s[i]=='a')                   //记录每个a的位置
		{
			a[t]=i;
			t++;
		}
	}
	if(!(len&1) && t&1)                 //判断无解
	{
		printf("-1");
		return 0;
	}
	for(int i=0;i<(t>>1);i++)
	{
		sum+=abs(len-1-a[i]-a[t-i-1]);  //计算每个a应该移动多少次，注意要取绝对值
	}
	if(t&1)
	{
		sum+=abs((len>>1)-a[t>>1]);     //如果有落单的，那么把这个a移到整个字符串的最中间
	}
	printf("%lld",sum);
	return 0;
}
```

注：代码已 AC 过，请放心食用。

最后，浏览过看过也要赞过！

---

## 作者：rc_Taurus (赞：2)

大家好，我是Wechis

[题目传送门](https://www.luogu.com.cn/problem/P9251)

# solution

## 思考

这题如果你只输出 $-1$ 会拿到 $27$ 分的好成绩！

那么问题来了，什么样的情况下会输出 $-1$ 呢？

先让我们举几个不会输出 $-1$ 的情况：

- abab
- bbabaaab

再举几个会输出 $-1$ 的情况：

- aabbba
- bbbabb

众所周知，每一个 $S_i$ 都可通过跟相邻两个字母交换位置以去到任意一个位置。

联系上面的例子，我们可以得出：

- 如果字符串长度为偶数，两种字符的数量为奇数，输出 $-1$。

- 如果字符串长度为奇数，则进入下一段的计算。

下一段就模拟，然后你就轻轻松松……错了。

原因：没开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int cnta,res,len;
signed main(){
	cin>>s;
	for(int i=0;i<s.size();i++)cnta+=(s[i]=='a'?1:0);
	len=s.size();
	if(!(s.size()&1)&&(cnta&1))cout<<-1;
	else{
	s=' '+s;
		deque<int>dq;
		for(int i=1;i<=s.size();i++){
			if(s[i]=='a')dq.push_back(i);
		}
		while(dq.size()>1){
			res+=abs(dq.front()+dq.back()-len-1);
			dq.pop_front();
			dq.pop_back();
		}
		if(dq.size())res+=abs((len+1)/2-dq.front());
		cout<<res<<endl;
	}
	return 0;
}
```

---

## 作者：Star_F (赞：2)

一道较为难的橙题。

## 题目大意：

给定一个只包含两个字母的字符串，每次操作可交换相邻的两个字母。求将字符串变成一个回文串的最小操作次数。

若无法变成回文串，输出 $-1$。

## 题目分析：
我们先考虑较为简单的情况，就是什么时候输出 $-1$。

- 如果字符串长度为偶数，那么为了保持回文，两种字符的数量必须为分别偶数，如果不是输出 $-1$。

- 如果字符串长度为技术，那么为了保持回文，两种字符的数量可以相等或者不等，所以不用输出 $-1$。

也就是说，当字符串长度为偶数，且两种字符串数量为奇数的时候输出 $-1$。

再来考虑求出最小的操作次数。

我们发现，如果字字符串回文，那么如果只保留其中一个字符也回文，所以我们只需要考虑其中一种字母。

所以，我们可以用一个双端队列求出操作次数。（本质就是模拟过程）。

具体看代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
#define DEBUG(x) cerr << #x << '=' << x << endl

inline int rd() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

void print(ll x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
    return;
}

namespace Star_F {
    void Main() {
        string s;
        cin >> s;
        int len = s.size();
        s = ' ' + s;  //下标从1开始，方便计算。

        deque<int> q;   
        ll ans = 0;

        FOR(i, 1, len) {
            if (s[i] == 'a') q.push_back(i);
        }

        if (len % 2 == 0 && q.size() % 2 == 1) {  //-1的情况。
            print(-1);
            putchar('\n');
            return;
        }

        while (q.size() > 1) {
            ans += abs(q.front() + q.back() - len - 1);    //因为要让q.front 和 q.back 对称，而且每次只能移动1，所以加起来-长度-1，就是让q.front 和 q.back 变成对称的最小操作次数。
            q.pop_front();
            q.pop_back();
        }

        if (q.size()) ans += abs((len + 1) / 2 - q.front());  //如果有剩余
        
        print(ans);
        putchar('\n');
    }
}

signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    return Star_F::Main(), 0;
}

```

---

## 作者：_TheShadow_ (赞：1)

## 题意
给定一个只有 2 种字符的字符串，判断是否能通过交换操作得到一个回文串，输出最小操作次数。
## 思路
首先，我们需要知道回文数的一些性质：
给定一个字符串一个长度为 $len$ 的字符串 $A$，有 $A_i = A_{len-i+1}$  $(1 \le i \le len)$。

通过阅读题目和分析样例，我们可以获得一个性质：
**当字符串中的其中一种字符形成回文，那么另一种字符也一定形成了回文。** 因此，对于字符串A，我们只需考虑其中的一类字符。

## 代码
```cpp
#include  <bits/stdc++.h>
#define ll long long
using namespace std;
ll ans, cnt, i;
ll a[200005];
string s;
signed main() {
	
	cin >> s;
	ll len = s.size();
	for(i = 0;i < len;i++) {
		if(s[i] == 'a')
			a[++cnt] = i+1;
	}        //记录a的位置 
	if(len%2==0 && cnt%2==1) {
		cout << -1;
		return 0;
	}        //特判,如果cnt为偶数且len为奇数时无解,参考楼上 
	
	
	for(i = 1;i <= cnt/2;i++)         //计算答案
		ans += abs(a[i]+a[cnt-i+1]-len-1);
	
	if(len%2==1 && cnt%2==1)
		ans += abs(a[(cnt+1)/2]-(len+1)/2);
	
	cout << ans;
	return 0;
}
```


''''''

---

## 作者：xujiadashaoye (赞：1)

如果要无解，那么在删除所有能配对的 $a$，$b$ 后，一定会剩有一个 $a$ 和一个 $b$。  
所以，$a$，$b$ 的个数都为奇数，字符串长度为偶数时，无解。

假设 $a$ 的位置构成回文，而 $b$ 的位置没有，那么总会存在一个 $b$ 的位置，使得关于对称轴的位置是 $a$，与条件不符。   
所以只要 $a$ 构成回文，$b$ 也构成回文。

### 构造回文：
将所有 $a$ 的位置放在一个列表 $v$ 里，使用两个变量 $i$ 和 $j$，分别指向 $v$ 的开头和结尾。将两个值加起来，用 $s$ 的长度去减再减 $1$，就是这一次操作需要移动的长度。

另外，当 $i=j$ 时，就是到了 $v$ 长度为奇数的中间数，需要用 $s$ 的中间数减去它，加在答案中。

由于步骤数可能很多，所以要开 long long。

[AC记录](https://www.luogu.com.cn/record/169568052)
### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	string s;cin>>s;
	vector<int>v(0);
	for(int i=0;i<s.size();i++){
		if(s[i]=='a')v.push_back(i);
	}
	if(s.size()%2==0&&v.size()%2==1){
		cout<<-1;
		return 0;
	}
	ll ans=0,t=-1;
	for(int i=0,j=v.size()-1;j>=i;i++,j--){
		if(i==j)t=i;
		if(i>=j)break;
		int k=v[i]+v[j]+1;
		int m=abs((int)(s.size()-k));
		ans+=m;
	}
	if(t!=-1){
		ans+=abs(int(s.size()/2-v[t]));
	}
	cout<<ans;
	return 0;
}



```

---

## 作者：Galsang (赞：1)

## 题意

给定一个只包含字符 a 和 b 的字符串，求将次字符串变为回文串的最小操作次数，若无法变为回文串则输出 - 1。

## 题解

回文串的性质：给定一个长度为 $len$ 的字符串 $S$，有 $S_i= S_{len-i+1}\left ( 1\le i\le len \right )$

通过阅读题目和分析样例，我们还可以获得一些性质：

1. 当字符串中的其中一种字符形成回文，那么另一种字符也**一定**形成了回文。

2. 当两种字符的数量都为奇数时，该字符串**一定**无法变为回文串。

因此，可以考虑定义一个双端队列用于存放字符串中字符 a 的下标（由于性质 1，我们可以忽略掉字符 b），每次取出队首和队尾算出操作次数，最后输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long int
//一定要记得开long long不然94pts 
string s;
deque<int>q;
int ans,len;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>s,len=s.size(),s=' '+s;//这里是为了方便存下标 
	for(int i=1;i<=len;i++)
		if(s[i]=='a')q.push_back(i);//下标入队 
	if(len%2==0&&q.size()%2==1)//特判性质2的无解情况 
	{
		cout<<-1<<endl;
		return 0;
	}
	while(q.size()>1)
	{//因为是两个两个地删，所以要留下一个防多删一个导致RE的情况 
		ans+=abs(q.front()+q.back()-len-1);//计算操作次数 
		q.pop_front(),q.pop_back();//删掉 
	}
	if(q.size())ans+=abs((len+1)/2-q.front());//特判还剩一个的情况 
	cout<<ans<<endl;//输出 
	return 0;
}
```

## 写在最后

一定要记得开 long long 啊！

---

## 作者：hy8z (赞：1)

## [题目](https://www.luogu.com.cn/problem/P9251)
#### 题目大意：
请你操作一个由 `a` 和 `b` 组成的字符串，每次操作可以交换相邻的两个字符串，求将原字符串变成回文字符串的最少次数，变不成输出 `-1`。

## 思路
先考虑回文字符串的性质：从后面和前面读都是一样的，这就意味着我们可以从前面一次考虑每一个 `a`，去对应从后往前数相应的 `a`，用一个变量 $ans$ 来储存每个后半部分的 `a` 需要交换的次数。


### 情况一
如果不能构成一个回文字符串，就是说这个字符串长度一定是偶数，且 `a` 的个数一定是奇数，这样 `a` 就不能平均分配到前半边和后半边，也就不能构成一个回文字符串。


### 情况二
如果可以构成一个回文字符串，可以用一个 $A$ 来存储每一个  `a` 的位置，用 $l$ 来存储字符串的长度,用 $numa$ 来存储字符串里有多少个 `a`。从而我们可以只考虑 `a`， `a` 对称了 `b` 也就对称了。对于每一个 $A_i(1 \le i \le \lfloor\frac{l}{2}\rfloor)$，只需要使其与 $A_{numa-i+1}$ 对称，即在字符串中的位置相加为 $l+1$ 就行了。

我们还需要考虑一种特殊情况。假如说字符串长度为奇数， `a` 的个数也为奇数，就意味着有一个 `a` 要移到字符串正中央。方法与上面差不多，图在下面，不多赘述。
![](https://cdn.luogu.com.cn/upload/image_hosting/770iqhnh.png)



```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200001],ans=0;
//a数组用来存储每个字符“a“的位置，ans存储答案
int main()
{
    string s;
    cin>>s;
    long long l=s.size(),numa=0;
    //numa存储字符串里有几个”a“ 之前一直没用l来存储s的长度，73分。知道为什么的大佬可以讲一下
    for(int i=0;i<l;i++)
	{
		if(s[i]=='a')//如果是”a“
		{
			numa++;
			a[numa]=i+1;//在a数组里增加一个新的字符”a“的位置
		}
	}
    if(l%2==0&&numa%2==1)
    //判断不能换成回文字符串的情况
    {
    	cout<<"-1";
    	return 0;
	}
	for(int i=1;i<=numa/2;i++)
	//依次看前面半段的”a“，看后面和看前面都是一样的
	{
		ans+=abs(a[i]+a[numa-i+1]-(l+1));
	}
	if(l%2==1&&numa%2==1)
	//如果字符串中间是”a“的情况
	{
		ans+=abs(a[numa/2+1]-(l+1)/2);
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：zhengpie (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9251)

### 1.思路

首先，如果你按照题意，随便将样例中的输入变换一下，你会发现，任意变换后的结果是原字符串的全排列！

所以，我们发现，当原字符串的全排列中的任意一个排列都不符合题意时无解。

不难发现，当字符串长度 $len$ 是偶数，且 $a,b$ 出现的次数都是奇数时，无解。

然后考虑有解的情况。可以发现，当 $a$ 出现的地方回文了，那么 $b$ 也一定会回文。于是，我们只需考虑一个字符即可。看大家都考虑 $a$，那我就考虑 $b$ 吧。（其实都一样）

设其在原数列中的位置为 $pos\_b_i$，那么只需让  $pos\_b_k$ 与  $pos\_b_i-k+1$ 关于中点对称即可。

### 2.完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s;
int cntb,posb[1919810],ans;
signed main() 
{
	cin>>s;
	int len = s.size();
	for(int i = 0;i < len;i++)
		if(s[i] == 'b') posb[++cntb] = i + 1;	
	if(!(len % 2) && (cntb % 2))
	{
		cout<<-1;
		return 0;
	}
	for(int i = 1;i <= cntb / 2;i++)
		ans += abs(posb[i] + posb[cntb - i + 1] - len - 1);
	if(len % 2 == 1 && cntb % 2 == 1)
		ans += abs(posb[(cntb + 1) / 2] - (len + 1) / 2);
	cout<<ans;
	return 0;
}
```

---

## 作者：joker_opof_qaq (赞：1)

### 题意简述
现在有一个字符串 $S$,仅由两种字母组成，你仅可以交换相邻的字符，现在求出将这个字符串变成回文串的最少交换次数，若无法通过该操作完成，输出 $-1$。

### 解法
- 无解情况
思考一下，若我们有 $x$ 个字符 `a`,$y$ 个字符 `b`,且满足 $x$ 和 $y$ 均为奇数，此时，必有一个落单的 `a`和一个落单的 `b`。无法配对，所以无解。

- 有解，如何求最小值

回文是不是意味着轴对称。不难发现，如果 `a` 出现的地方回文了，那么 `b` 也一定回文(`a` 回文，意味着 `a` 仅仅对应着 `a` 则 `b` 无法对应 `a`，必也回文)

举个例子当 $S$ 为 `aabab` 时，我们可以这么考虑，先看第一位和第五位，发现需交换，找最近的第四个，如果是 `b` 就继续往左找，直到找到换过来，此时发现第五位满足了，则固定不动，看第二四位，发现不同，则其中之一和第三位交换，即满足，再次固定不动，看第三位，第三位仅仅有自己，不许考虑，那么就做完了，共进行了两次交换，答案即为 $2$。

所以我们只需要让 $a_i$ 和 $a_{len-i+1}$ 对称即可，并完成后固定不动，不要再做交换，继续考虑第 $a_{i+1}$ 和 $a_{len-i+2}$。

---

## 作者：Milkshakefairytale (赞：0)

## 大致题意
给定一个只含 $ a $，$ b $ 两种的字符串，问你需要交换几次，才能使这个字符串变成回文串。如果本身就是或者永远无法完成的话就输出 -1。

## 题目分析

### 情况一：输出 -1（无解）

本身就是回文串能够很好理解，但永远无法完成是什么情况？我们可以从字符串的长度来考虑：

- 如果字符串的长度是偶数，当 $ a $ 和 $ b $ 的字符个数是奇数的时候，就永远无法完成回文串交换的工作，因为两边不可能有同样的 $ a $ 和 $ b $，当 $ a $ 和 $ b $ 的字符个数是偶数那就可以完成交换工作。

- 如果字符串的长度是奇数，那 $ a $ 和 $ b $ 的字符个数一定是一奇一偶，只需要把奇数字符个数的字符放在中间，两边的 $ a $ 和 $ b $ 字符个数一样就行。
 
所以符合条件的只有一种情况，就是字符串的长度是偶数并且当 $ a $ 和 $ b $ 的字符个数是奇数的时候，输出 -1。

### 情况二：输出交换次数（有解）

判断完上面两种情况我们就可以考虑有解的情况了。

我们可以把题目简化一下，如果 $ a $ 关于中心对称，$ b $ 也会关于中心对称。所以我们可以只考虑 $ a $ 关于中心是否对称的问题就行了。

### 做法
通过双向队列来维护，把输入的 $ a $ 的下标弹入，每次取出队首的下标和队尾的下标进行计算操作就行了。

---

## 作者：xiaokang_suancai (赞：0)

# P9251 题解
[题目传送门](https://www.luogu.com.cn/problem/P9251)
## 题意简述
给定一个只包含字符 $\texttt a, \texttt b$ 的字符串，每次操作可以交换两个不同字符，求至少操作几次能使该字符串回文。如果不能实现则输出 $-1$ 。
## 思路分析
以下内容中，我们记字符串长度为 $len$，$\texttt a$ 出现的数量为 $num$ 。

首先，我们来讨论无解的情况。我们不难发现，如果 $len$ 为偶数，只有当 $num$ 也为偶数的时候，字符串才有解。

**所以，当且仅当 $len$ 为偶数且 $num$ 为奇数时，字符串无解。这种情况直接输出 $-1$ 即可。**

接着，再来看最小操作次数怎么解决。我们不妨把字符串回文看做字符串成轴对称。很明显，当一种字符轴对称时，另一种字符也一定轴对称。因此，为了方便，我们可以直接删去 $\texttt b$ ，只要能使 $\texttt a$ 的位置成轴对称，就是最优解了。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005];
int cnt,a[200005];
long long ans;
// 十年 OI 一场空，不开 long long 见祖宗
int main()
{
	cin>>s;
	int len=strlen(s);
	for(int i=0;i<len;i++) // 判断 'a' 出现的位置
	{
		if(s[i]=='a')
			a[++cnt]=i+1;
	}
	if(len%2==0&&cnt%2==1) // 判断无解的情况，上面已经讲了，不再赘述
	{
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=cnt/2;i++)
		ans+=abs(a[i]-len+a[cnt+1-i]-1);
	if(len%2==1&&cnt%2==1) // 特判 len 奇数时需要中间字符的情况
		ans+=abs(a[(cnt+1)/2]-(len+1)/2);
	cout<<ans;
	return 0;
}
```

---

## 作者：zbrprogrammer (赞：0)

### [PA 2022 Palindrom](https://www.luogu.com.cn/problem/P9251)

#### 题意：

> 给定一个只有 2 种字符的字符串，判断是否能通过交换操作得到一个回文串，输出最小操作次数。

#### 分析：

字符集大小为 2 的回文串有以下性质：

- 两种字符构成的子序列一定关于原串中轴轴对称。
  
- 两种字符的个数不能同时为奇数。
  

由此，可以得出可行性判断过程：统计字符个数，若同时为奇数，则不可行。

对于最小操作次数，有以下限制：

- 交换两个相同字符不产生贡献，舍去。
  
- 同时将两个字符调整至正确位置与只对一个字符调整产生消耗相同，因此只需考虑一侧。
  
- 调整一种字符的同时也对另一种字符进行了调整，所以只统计一种字符。
  

由此，可以得出答案：采用双端队列维护其中一个字符，计算队列侧对应字符的位置差，求和即可。

**记得开 `long long`**。

#### Code:

```cpp
#include<bits/stdc++.h>
#define int long long 
#ifndef ONLINE_JUDGE
		#define DEBUG(x) std::cerr<<#x<<":"<<x<<endl
		#define DEBUGP(x) std::cerr<<#x<<":"<<x<<endl;system("pause")
		#define FILE(x) freopen(#x ".in","r",stdin);freopen(#x ".out","w",stdout);
#else
	 #define DEBUG(x)
	 #define DEBUGP(x)
	 #define FILE(x)
#endif
using namespace std;
string S;
deque<int>q;
int cnta,cntb,ans=0;
signed main(){
	cin >> S;
	for(int i=1;i<=S.size();i++){
		if(S[i-1]=='a'){
			cnta++;
			q.push_back(i);
		}
		else if(S[i-1]=='b')cntb++;
	}
	if(cnta%2&&cntb%2){
		printf("-1");
		return 0;
	}
	while(q.size()>1){//如果是奇数，会保留一位作为中间位，否则全部弹出
		long long tmp=q.front()-(S.size()+1-q.back());//统计答案
		ans+=abs(tmp);
		q.pop_front();q.pop_back();
	}
	if(cnta%2){//计算中间位
		long long tmp=(S.size()+1)/2-q.front();
		ans+=abs(tmp);
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：Il1_1_3 (赞：0)

# P9251 [PA 2022] Palindrom 题解

[题目传送门](https://www.luogu.com.cn/problem/P9251)

## 题意
给定一个仅由字符 $a,b$ 构成的字符串，每次可以交换相邻的两个字符，
求最少交换多少次可以构成一个回文字符串。若不能实现，输出 $-1$。
## 思路
回文串的性质：一个长度为 $t$ 的字符串 $S$，满足 $S_a=S_{t-a+1} (1 \le a \le t)$。

这道题的输出分为两类:
- **不可能**的情况：**长度 $lent$ 为偶，字符 $a$ 的个数 $m$ 为奇。**

    ~~证明就不必了吧~~  偶数长度的字符串可以被分成长度**相等**的前后两部分，而奇数个字符 $a$ 不能平均分配。
  
- 再来看有解的情况：

  对于本题，**删去所有字符 $b$ 后，若剩下的字符 $a$ 呈对称，那么整个字符串也回文。**

  只需记录下 $to$ 个字符 $a$ 在字符串中的位置到数组 $A$ 中，最终使：

  $A_{i+1}=A_{to-i}(0 \le i < \dfrac{to}{2},to\equiv0\pmod{2})$

  $A_{i+1}=A_{to-i}(0 \le i < \dfrac{to+1}{2},to\equiv1\pmod{2})$

  即可。

  贴上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int K=114514*2;//开太小容易RE 
int l,to,a[K];
long long ans;//一定开long long!!! 
char st[K];
bool odev(int t)
{	
	return t%2==0?0:1;
}
int main() 
{
	cin>>st;
	l=strlen(st);
	for(int i=0;i<l;i++) //判断'a' 
		if(st[i]=='a') 
		{
			to++;
			a[to]=i+1;	
		}
	if((!odev(l))&&odev(to)) //不可能的情况 
	{
		cout << "-1";
		return 0;
	}
	for(int i=1;i<=(to/2);i++)
		ans+=abs(a[i]-l+a[to-i+1]-1);
	if(odev(l)&&odev(to)) //中间情况 
		ans+=abs(a[(to+1)/2]-((l+1)/2));
	cout << ans << endl;
	return 0;
}
```
   成功了！[测评结果](https://www.luogu.com.cn/record/169482827)
   
   附上两个失败记录：
   
   [没开 long long（94 pts）](https://www.luogu.com.cn/record/169485478)
   
   [数组不够大（46 pts）](https://www.luogu.com.cn/record/169485956)

## 说在最后

发现自己思路没问题但总差几分，一定要检查 long long 的使用（这道题我也被 long long 卡住了 QwQ）。

---

## 作者：Seqfrel (赞：0)

# P9251 [PA 2022] Palindrom 题解

## 题目大意

给定一个仅包含 `a` 和 `b` 两个字符的字符串，每次可以交换相邻两个字符，求其变成一个回文字符串的最小编辑距离，如果不能成为回文字符串，输出 $-1$。

## 解题思路

考察回文字符串。

不难发现，如果字符串长度为偶数且 `a` 字母的数量为奇数，那么 `b` 字母的数量也为奇数，则任何情况下都不能构成回文字符串，输出 $-1$。

而由于此字符串只包含 `a` 和 `b` 两个字母，那么如果一个字母的位置以最中间的字符为对称轴对称，另一个字母就可以填入空位，构成完整的回文字符串。

![](https://cdn.luogu.com.cn/upload/image_hosting/yiqk5mp9.png)

就像这样，字符 `a` 的位置依次为 $1$、$3$、$5$，以中心字符的位置 $3$ 对称，那么字符 `b` 就可以直接填入剩余的空位中。

于是我们单独存储 `a` 字母的位置，然后求此数组中位置距离对称位置的距离并累加即可。

我们可以固定 `a` 字母位置的前半段为对称位置，求 `a` 字母后半段位置距离前半段位置所对应的对称位置的距离，代码实现起来非常简单，$a[cnta-i+1]$ 为 `a` 字母后半段的位置，$len-a[i]+1$ 为前半段位置所对应的对称位置，遍历每个 $i$ 即可。

需要注意的是，如果给定字符串的长度为奇数，且 `a` 字母的数量也为奇数个，那么 `a` 字母就必定会是中间字符，需要单独判断距离中间字符位置的距离。

## 代码实现

```cpp
#include<iostream>
#include<cmath>
#include<string>
using namespace std;
const int maxn=2e5+10;//字符串最大长度 
int len,cnta;
int a[maxn];//存储a字母位置的数组 
long long ans;
string s;
int main(){
	cin>>s;
	len=s.size();
	for(int i=0;i<len;i++){
		if(s[i]=='a'){
			cnta++;
			a[cnta]=i+1;
		} 
	}
	if(len%2==0&&cnta%2==1){//判断是否不可能构成回文串 
		cout<<-1;return 0;
	}
	for(int i=1;i<=(cnta/2);i++){
		ans+=abs(a[cnta-i+1]-len+a[i]-1);//这里是化简过的式子
	}
	if(len%2==1&&cnta%2==1) {//判断是否需要中央字符 
		ans+=abs(a[(cnta+1)/2]-((len+1)/2));
	}
	cout<<ans;
	return 0;
}
```

## 一些坑点

因为字符串最大长度为 $2e5$，所以最大交换次数可能会超过 int 类型变量的最大值，需要开 long long 类型变量。

---

## 作者：zhoujiefu (赞：0)

题意很简洁明了，我们可以按照题意一步一步想。首先先想一想什么情况下无解。不难想到，如果总长度是一个偶数，其中一种字母（这里和后面都选 a ）的个数是奇数，这样无论如何都无法变成回文串。因为回文串需要在两边有同样的字母，而一种字母的个数是奇数，另一种也一定是奇数。因此不可能变成回文串。

 再考虑怎么操作可以使得操作次数最少。考虑回文的性质：$S_i=S_{{len}-i+1}$。也就是说，如果一种字母是回文的，那么另一种也是。所以我们就不考虑 b，
设序列 $A$ 记录所有字母 a 出现的位置，然后让序列满足 $S_i=S_{{len}-i+1}$，具体实现见代码。
 
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
string s;
int len,tot,a[N],ans;//len是长度，tot是a的个数
signed main(){
	cin>>s;
	len=s.size();
	for(int i=0;i<len;i++){
		if(s[i]=='a'){
			a[++tot]=i+1;//记录a的位置
		}
	}
	if(len%2==0&&tot%2==1){//特判
	    cout<<-1;
	    return 0;
	}
	for(int i=1;i<=tot/2;i++) {//计算答案
		ans+=abs(a[i]-len+a[tot-i+1]-1);
	}
	if(len%2==1&&tot%2==1){
		ans+=abs(a[(tot+1)/2]-((len+1)/2));
	}
	cout<<ans;
	return 0;
}
```

---

