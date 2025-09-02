# Swap and Delete

## 题目描述

有一个只含 $\texttt{0}$ 和 $\texttt{1}$ 的字符串 $s$，你可以对它进行如下两种操作：

1. 耗费一个金币，从 $s$ 中删除 $1$ 个字符。

2. 将 $s$ 中任意两字符互换位置（免费）。

定义一个字符串 $t$ 是美的代表对于所有满足 $1 \le i \le \left|t\right|$ 的 $i$，$s_i \ne t_i$ 。

你可以进行任意多次操作，假设 $s$ 修改后变为了 $s'$，问最少花费多少金币能使最终得到的 $s'$ 是美的。

## 样例 #1

### 输入

```
4
0
011
0101110001
111100```

### 输出

```
1
1
0
4```

# 题解

## 作者：_luouhgy_ (赞：3)


## 题目大意
一个 $01$ 字符串 $s$，可以交换任意两个位置的元素，代价为 $0$；或删除一个元素，代价为 $1$。使得进行交换或删除后的字符串的每个 $t_i$ 和 $s_i$ 都不同，最少要用多少代价。

题目其实问我们把一个字符串 $s$ 中的所有 $1$ 都改为 $0$，把所有 $0$ 都给成 $1$，一共需要操作几次。
## 思路
有点贪心的意思。

因为交换两个元素不仅一次可以满足两个元素，代价还为 $0$，所以我们要尽可能多交换两个元素，剩下的再删除。

操作 $1$ 用的次数最多为字符串中 $1$ 的个数，也就是将字符串中所有的 $1$ 都删除；操作 $0$ 用的次数最多为字符串中 $0$ 的个数，也就是将字符串中所有的 $0$ 删除。每发现一个可以交换的 $1$ 或者是 $0$，就将操作 $1$ 用的次数或操作 $0$ 用的次数减少 $1$。 
## Code
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int t;
int cnt1;//字符串中操作1的次数
int cnt0;//字符串中操作0的次数
string s;
int main(){
    cin>>t;
    while(t--){
        cnt1=0,cnt0=0;//初始化
        cin>>s;
        int len=s.size();
        for(int i=0;i<len;i++){
        	if(s[i]=='0')cnt1++;//字符串中0的个数
			else cnt0++;//字符串中1的个数
		}
        for(int i=0;i<len;i++){
        	if(s[i]=='0'){
            	if(cnt0)//可以交换一个0
					cnt0--;//字符串中操作0的次数-1
				else//0已经交换完了
					break;
			}else{
				if(cnt1)//可以交换一个1
					cnt1--;//字符串中操作1的次数-1
				else//1已经交换完了
					break;
			}
		}
        cout<<cnt1+cnt0<<endl;//字符串中操作1的次数+字符串中操作0的次数
    }
    return 0;//完工
}
```


---

## 作者：UncleSam_Died (赞：2)

### 解题思路
我们将题意转化一下：
- 求 $s$ 的反转后的字符串的一个最长前缀，使其满足可以通过 $s$ 得到。

显然，交换不会改变每种字符的数量。那么，我们先把 $s$ 求出其中 $0$ 的数量 $s0$，和 $1$ 的数量 $s1$，然后将 $s$ 每位反转（$0$ 变 $1$），然后从第一位开始，记录此时的 $0$ 的数量 $t0$ 和 $1$ 的数量 $t1$，如果这个时候有 $t0=s0 \wedge t1=s1$，那么直接输出 $n-i$ 即可；如果 $t0>s0\vee t1>s1$，那么输出 $n-i+1$。

### AC 代码
```cpp
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#include<cstring>
#define N 200005
char s[N];
inline void work(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	int s0=0,s1=0;
	for(register int i=1;i<=n;++i){
		if(s[i]=='0') ++s0;
		else ++s1;
	}int t1=0,t0=0;
	for(register int i=1;i<=n;++i){
		if(s[i]=='0') ++t1;
		else ++t0;
		if(t1==s1&&t0==s0){
			printf("%d\n",n-i);
			return;
		}else if(t1>s1||t0>s0){
			printf("%d\n",n-i+1);
			return;
		}
	}
}signed main(){
	srand(114514);
	srand(rand());
	srand(time(0));
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int T;scanf("%d",&T);
	while(T--) work();
	return 0;
}



```

---

## 作者：Withershine (赞：2)

# 翻译
给定一个字符串 $s$，你有两种操作：
1. 删除一个字符。（花费一枚金币）
2. 交换某两个字符的位置。（不花费金币）

假设经过若干次操作后得到的字符串为 $t$。

$t$ 是好的当且仅当对于任意的 $i$（$1 \le i \le |t|$，$|t|$ 为字符串 $t$ 的长度），均满足 $t_i \ne s_i$。（$s$ 是原本的字符串）

自然，空串一定是好的。

问最小花费。

多测。

# 思路
记录每个 $s$ 的 `0` 和 `1` 的数量，第二次遍历时直接遍历 $s$ 串，$s$ 串为 `1` 则填 `0`，为 `0` 则填 `1`。当无法继续填时直接输出剩余的 `0` 和 `1` 总字符数。因为此时后面的不管怎么填一定会有相同，只能全删。

# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
using namespace std;
ll T;
char s[200005];
signed main()
{
    // freopen("in.in" , "r" , stdin);
    // freopen("out.out" , "w" , stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--)
    {
        cin >> s + 1;
        ll len = strlen(s + 1) , num0 = 0 , num1 = 0;
        fr(i , 1 , len)
        {
            if(s[i] == '0')
            {
                num0++;
            }
            else
            {
                num1++;
            }
        }
        fr(i , 1 , len)
        {
            if(s[i] == '0')
            {
                if(num1 == 0)
                {
                    break;
                }
                num1--;
            }
            else
            {
                if(num0 == 0)
                {
                    break;
                }
                num0--;
            }
        }
        cout << num1 + num0 << '\n';
    }
    return 0;
}
```


---

## 作者：IOI_official (赞：2)

# 思路。
这是一道挺简单的贪心，由于题目中说交换操作免费，所以我们尽量使用交换，不能交换了再用删除。

求要用的钱也很简单，我们用两个变量分别储存字符串中 $0$ 和 $1$ 的个数，然后开始交换，从字符串开头枚举到字符串结尾，如果遇到 $0$，就将 $1$ 的数量减 $1$，反之亦然。

**要在每次减之前判断一下数量是否为空，为空就跳出，防止变成负数。**

最后要删除的数量就是 $0$ 剩下的数量加 $1$ 剩下的数量。

# AC代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,z,o,c;
string s;
int main(){
	cin>>t;
	while(t--){
		c=z=o=0;
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(s[i]=='0'){
				z++;
			}
			else o++;
		}
		for(int i=0;i<s.size();i++){
			if(s[i]=='0'){
				if(o>0)
					o--;
				else break;
			}
			else{
				if(z>0){
					z--;
				}
				else break;
			}
		}
		cout<<o+z<<endl;
	}
	return 0;
}
```

---

## 作者：__zhuruirong__ (赞：1)

## 题目大意

给你一个 01 字符串 $s$，可以交换任意两个位置和删除一个元素，交换代价为 $0$，删除代价为 $1$，问最少要用多少代价，使得操作后的字符串的每个 $t_i$ 和 $s_i$ 都不同。

## 分析

显然，通过交换，可以让任意一个元素到达任意一个位置，所以可以考虑将所有 $1$ 换到换以前的 $0$ 的位置，$0$ 换到换以前的 $1$ 的位置，可以让 $s$ 和 $t$ 完全不相同，但是 $s$ 可能没有足够的 $1$ 或 $0$，所以当 $1$ 或 $0$ 不够用时，剩下的元素只能删除。

## AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int T, sum1, sum2;
string s;

signed main() {
    cin >> T;
    while(T--) {
        sum1 = sum2 = 0;
        cin >> s;
        for(int i = 0; i < s.size(); i++)
            if(s[i] == '0')
                sum1++;
            else
                sum2++;
        for(int i = 0; i < s.size(); i++)
            if(s[i] == '0')
                if(sum2)
                    sum2--;
                else
                    break;
            else
                if(sum1)
                    sum1--;
                else
                    break;
        cout << sum1 + sum2 << endl;
    } 

    return 0;
}

```

---

## 作者：Bc2_ChickenDreamer (赞：1)

## CF1913B Swap and Delete 题解

## Sol

首先，我们统计 $s$ 的 $0$ 和 $1$ 的数量，然后遍历 $s$。如果 $s_i$ 串为 $1$，则在另一个字符串填 $0$，否则填 $1$。当没有办法继续填时输出 $s$ 的长度减去另一个字符串的长度。因为此时后面不管怎么填一定会有相同的。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>

using namespace std;

using ll = long long;

#define mtest for (cin >> t; t; -- t)

const int kMaxN = 1e5 + 10, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;

string s;

auto C() {
  int zr = 0, one = 0;
  for (int i = 0; i < s.size(); ++ i) {
    s[i] == '0'? ++ zr : ++ one;
  }
  return make_pair(one, zr);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  mtest {
    cin >> s;
    int a = C().first, b = C().second;
    string s2 = "";
    for (int i = 0; i < s.size(); ++ i) {
      if (s[i] == '0') {
        if (a > 0) {
          s2 += "1";
          -- a;
        } else {
          break;
        }
      } else {
        if (b > 0) {
          -- b;
          s2 += "0";
        } else {
          break;
        }
      }
    }
    cout << s.size() - s2.size() << '\n';
  }
  return 0;
}
```

---

## 作者：GenesisCrystal (赞：1)

~~模拟赛时发现做法假了。~~

## Soulution

题目中很具有特色的一句话：将 $s$ 中任意两字符互换位置（免费）。

所以一个明显的贪心思路就出来了：尽量多用 $\text{Swap}$ 操作。

首先记录 $0$ 或 $1$ 的次数，然后从 $0$ 开始枚举，如果 $c_{s_{i}} = 0$，那么令答案为 $n - i$，否则将 $c_{s_i} \gets c_{s_i}-1$。如果 $c_{0} = c_{1}$，即 $1$ 的个数和 $0$ 的一样，此时答案为 $0$。

## Code

```cpp
#include <iostream>

using namespace std;

int t, n;
string s;

int main() {
  for (cin >> t; t; t--) {
    cin >> s, n = s.size();
    int c[2] = {};
    for (int i = 0; i < n; i++) {
      c[s[i] - '0']++;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (!c[(s[i] - '0') ^ 1]) {
        ans = n - i;
        break;
      }
      c[(s[i] - '0') ^ 1]--;
    }
    cout << ans << '\n';
  }
  return 0;
}
```
代码超短，请放心食用。

---

## 作者：_wzx (赞：0)

# 分析

题目中给了两种操作：

- 第一种是在字符串中删除一个字符，需要花一个金币；

- 第二种是交换任意两个字符的位置，不需花费金币。

所以由此可见我们要用的是贪心的思想，即尽量多种第二种操作，尽量少做第一种操作。

# 思路

我们首先要得到字符串中 $0$ 和 $1$ 的数量，再对字符串遍历，如果当前的字符是 $0$ ，则看还剩多少个 $1$ ，如果没有了就退出循环，反之亦然。





# Code

```cpp
#include <bits/stdc++.h> //万能头(本人比较懒)
#define endl '\n'
typedef long long ll;
using namespace std;
string str;
int t;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--)
    {
        int cnt_0 = 0, cnt_1 = 0;
        cin >> str;
        int len = str.length();
        for (int i = 0; i < len; i++)
        {
            if (str[i] == '0')
                cnt_0++; //统计0的数量
            else
                cnt_1++; //统计1的数量
        }
        for (int i = 0; i < len; i++)
        {
            if (str[i] == '0')
            {
                if (cnt_1 > 0)
                    cnt_1--;
                else
                    break; // 如果减不下去了，退出循环。
            }
            else
            {
                if (cnt_0 > 0)
                    cnt_0--;
                else
                    break; // 如果减不下去了，退出循环。
            }
        }
        if (cnt_0 == 0 && cnt_1 == 0)
            cout << 0 << endl;
        else
            cout << cnt_0 + cnt_1 << endl; //输出他们的和
    }
    return 0; // 完结撒花
}
```


---

## 作者：DHT666 (赞：0)

## 题意
给定 $01$ 字符串，有两种操作：

- 删除一个元素，花费 $1$。
- 交换两个元素，免费。

定义字符串 $t$ 是美的，代表 $1\le i\le t$ 的 $i$ 满足 $s_i\ne t_i$。

求使得给出字符串经过操作变美的最小花费。

## 思路
贪心，因为交换两个元素不需要花费，所以所有字符可以随意移动。

相当于要用原来的 $0$ 和 $1$ 组成一个原串的反串。

于是记录 $0$ 和 $1$ 出现的次数，组成原串的反串，不够的只好删掉。

## 代码
~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int t;
string s,tot;

int main() {
	cin>>t;
	while(t--) {
		bool f = 0;
		cin>>s;
		int len = s.size(),cnt0 = 0,cnt1 = 0;
		for(int i=0;i<len;i++) {
			if(s[i] == '0') cnt0++; // 记录 0 和 1 出现的次数
			else cnt1++; 
		}
		for(int i=0;i<len;i++) {
			if(s[i] == '0') cnt1--; // 构造反串
			else cnt0--;
			if(cnt0 < 0 || cnt1 < 0) {
				cout<<len - i<<endl; // 不够就删掉剩余的
				f = 1;
				break;
			}
		}
		if(!f) cout<<0<<endl; // 够
	}
	
	return 0;
}
~~~

---

## 作者：The_jester_from_Lst (赞：0)

本题考虑贪心。

对于每一个 $s$ 串，我们遍历统计其中 $1$ 和 $0$ 的数量。显然对于题目要求的 $s_i \ne t_i$，我们可以理解为将 $1$ 变成 $0$，$0$ 变成 $1$。既然如此我们再次遍历 $s$ 串，若 $s_i$ 为 $0$，让 $1$ 的数量减一，否则让 $0$ 的数量减一，一旦出现某一个不够减，说明后面都填不下去了，此时后面的全部需要删去，所以最少金币量即是此时还没遍历到的 $s_i$ 的数量。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(){
	int jya=0,ysc=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')ysc=-1;ch=getchar();}
	while(isdigit(ch)){jya=jya*10+(ch-'0');ch=getchar();}
	return jya*ysc;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)wr(x/10);
	putchar(x%10+'0');
}
int t,ls,yi,ling;
string s;
signed main(){
	t=rd();
	while(t--){
		cin>>s;
		ls=s.size();
		yi=ling=0;
		for(int i=0;i<ls;++i)if(s[i]=='1')++yi;
		ling=ls-yi;
		for(int i=0;i<ls;++i){
			if(s[i]=='1'){
				if(ling>0)--ling;
				else break;
			}
			else {
				if(yi>0)--yi;
				else break;
			}
		}
		wr(yi+ling);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：_qingshu_ (赞：0)

# 题意:

有一个只包含 $\texttt{0}$ 和 $\texttt{1}$ 的字符串，你可以进行两种操作。

- 耗费一个金币，删除一个字符。

- 交换两个字符的位置。

对于结果美的定义为任意 $1\le i \le |t|$ 满足 $s_i \ne t_i$。

求最小花费。

# 思路：

首先，要使得每一个字符 $\texttt{0}$ 都有一个对应的 $\texttt{1}$ 且每一个字符 $\texttt{1}$ 都有一个对应的 $\texttt{0}$，所以有理想的情况 $\texttt{0}$ 的个数与 $\texttt{1}$ 的个数一定是相等的，不然一定会有多出来的。

可以记录一下原串中两种字符的个数，然后取小。

再思考删除过后的情况，因为这是一个字符串，即使删除了一个字符后面的也会往前面补位，就像是样例 $3$。

我们就无法保证 $t$ 最前面的 $|s|$ 个字符与现在 $s$ 的各个字符都可以匹配，所以我们需要再扫一遍字符串 $t$，然后每出现一个字符 $\texttt{1}$，我们就把 $s$ 中 $\texttt{0}$ 的个数减一，代表把一个 $\texttt{0}$ 交换到该位置上。为 $\texttt{0}$ 同理，最后如果出现了后面不存在某种字符了，我们就把后面的全部删去，也就是耗费与当前匹配字符同种字符的个数。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		long long one=0,zro=0,res=0;
		for(int i=0;i<n.size();i++){
			if(n[i]-'0'){
				one++;
			}
			else{
				zro++;
			}
		}
		res=abs(zro-one);
		one=min(one,zro);
		zro=min(one,zro);
		for(int i=0;i<n.size();i++){
			if(n[i]-'0'){
				if(zro){
					zro--;
				}
				else{
					res+=one;
					break;
				} 
			}
			else{
				if(one){
					one--;
				}
				else{
					res+=zro;
					break;
				}
			}
		}
		cout<<res<<endl;
	}
} 
```

---

## 作者：kczw (赞：0)

# 题意
一共有 $t$ 组数据，对于每组数据给定一个由 `0` 和 `1` 组成的字符串 $S$。

现在需要你修改字符的排列顺序以及删去字符串的一部分，使得删除剩下的字符串与 $S$ 同样长度的前缀没有一位字符相同。问最小需要几次操作。
# 思路
对于每一个 $S$ 我们可以存储字符 `0` 和 `1` 的个数，然后遍历 $S$。如果遍历到 `0` 则判断有没有多余的 `1` 可以补上，如果有便继续遍历，如果没有，则多余的 `0` 必须全部删去，并且无需继续遍历。遍历到 `1` 与上文操作类似。

因为 $t$ 组数据的 $S$ 的总长度 $\le2\times10^5$，所以时间复杂度完全可以过一秒。
# 实现
```cpp
#include<iostream>
#include<stdio.h>
using namespace std;
int t,use,pos,num[2];
char x[200005];
int main(){
	scanf("%d",&t);
	x[0]=getchar();
	while(t--){num[0]=num[1]=use=pos=0;
		x[++pos]=getchar();
		while(x[pos]=='0'||x[pos]=='1'){
			num[x[pos]-'0']++;
			x[++pos]=getchar();
		}for(int i=1;i<=pos;i++){
			if(x[i]=='1'){
				if(!num[0]){use+=num[1];break;}
				num[0]--;
			}else{
				if(!num[1]){use+=num[0];break;}
				num[1]--;
			}
		}printf("%d\n",use);
	}return 0;
}
```

---

## 作者：_anll_ (赞：0)

博客内享用效果更佳哦！
## 题目大意
给定一个 $01$ 字符串 $s$，你可以对它进行如下两种操作：

1. 耗费一个金币，从 $s$ 中删除一个字符；

1. 不耗费金币，将 $s$ 中任意两个字符互换。

令修改后的字符串为 $t$，问你最多耗费多少金币，可以让每一个 $t_i$ 与 $s_i$ 都不同。

## 大体思路
~~我怎么会告诉你我在赛时被一道橙题卡得痛不欲生。~~

我们发现，每一个 $s_i$ 都需要对应与他不同的字符。所以我们通过两次遍历解决问题。

第一次把其原有的 $0$ 和 $1$ 的个数存一下，第二次就按照 $s_i$ 去消耗 $0$ 和 $1$ 的个数，如果 $s_i$ 是 $0$ 就把 $1$ 的个数减一个，反之亦然。

直到 $0$ 或 $1$ 的个数不支持填充，那就需要把 $s$ 后面的所有字符都删掉，所以我们输出剩下的 $0$ 和 $1$ 的数量就好啦。

## 代码演示
赛时代码放这啦，如果前面表述有不清楚的地方，还请结合代码理解。

```cpp
#include<iostream>
#define int long long
using namespace std;
int t,one,zero;
string s;
signed main(){
	cin>>t;
	while(t--){
		cin>>s;
		one=zero=0;
		for(int i=0;i<s.size();i++){
			if(s[i]=='0') zero+=1;
			if(s[i]=='1') one+=1;
		}
		int i;
		for(i=0;i<s.size();i++){
			if(s[i]=='0') one-=1;
			if(s[i]=='1') zero-=1;
			if(zero<0||one<0) break;
		}
		cout<<(int)s.size()-i<<endl;
	}
	return 0;
}
```


---

## 作者：_Mortis_ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1913B)
# 题意
给定一个 $01$ 字符串 $s$，有两种操作：

1.删除一个字符（代价 $1$）

2.交换两个字符的位置（免费）

最少要用多少代价，使得操作后的字符串的每个 $t_{i}$ 和 $s_{i}$ 都不同。
# 思路
显然，每个字符都可以通过交换达到任意一个位置，交换也不会改变每种字符的数量。

我们可以累加 $s$ 中 $0$ 和 $1$ 的数量，再遍历 $s$ 串，$s_{i}$ 为 $1$ 就填 $0$，否则填 $1$。

如果不能再填就输出剩余 $0$ 和 $1$ 的数量，因为后面不管怎么填都会相同，只能全部删除。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,sum0,sum1;
string s;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(cin>>T;T--;){
		sum0=sum1=0;
		cin>>s;
		for(int i=0;i<s.size();i++)
			if(s[i]=='0')sum0++;
			else sum1++;
		for(int i=0;i<s.size();i++)
			if(s[i]=='0'){
				if(sum1)sum1--;
				else break;
			}
			else{
				if(sum0)sum0--;
				else break;
			}
		cout<<sum0+sum1<<"\n";
	}
	return 0;
}
```
### [AC记录](https://www.luogu.com.cn/record/141247517)

---

## 作者：liuyi0905 (赞：0)

大家题意应该都看懂了，下面来介绍一下此题的做法。

1. 维护 $sum_0,sum_1$ 分别表示 $s$ 中字符 $\texttt0$ 和 $\texttt1$ 的数量。

2. 按题意去模拟：
>1. 如果 $s_i$ 为字符 $\texttt0$，则需要用一个 $\texttt1$ 来凑，如果没有 $\texttt1$ 了，则后面的字符都需要删除，答案即为 $|s|-i$。
>2. 如果 $s_i$ 为字符 $\texttt1$，同理。

3. 没有遇到需要删除的情况，则答案就是 $0$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
    for(cin>>t;t;t--){
        cin>>s;
        int sum[2]={0};
        for(int i=0;i<s.size();i++)sum[s[i]-'0']++;
        bool flag=0;
        for(int i=0;i<s.size();i++)
            if(s[i]=='0'){
                sum[1]--;
                if(sum[1]<0){flag=1,cout<<s.size()-i<<"\n";break;}
            }
            else{
                sum[0]--;
                if(sum[0]<0){flag=1,cout<<s.size()-i<<"\n";break;}
            }
        if(!flag)cout<<"0\n";
    }
    return 0;
}
```

---

## 作者：myyyIisq2R (赞：0)

## [CF1913B Swap and Delete](https://www.luogu.com.cn/problem/CF1913B)

## 题意
给出一个 `01` 序列，问通过若干次调换顺序使新序列前缀与原序列前缀每一位均不相同时后缀的最小长度。

## 思路
既然要最小长度，那么我们不如尽可能把序列中能凑出相反的数往前堆，当没有数能继续放时，输出剩余数的个数。

有点抽象，解释一下。

对于 `0101110001` 这串序列，有 $5$ 个 $1$ 和 $5$ 个 $0$。
之后我们将 $1$ 和 $0$ 从前往后凑成新序列，使得每一位都与原序列相反。
得到 `1010001110`。

剩余 $0$ 个数，刚好拼完，那么输出 $0$。

## 细节

```cpp

#include  <bits/stdc++.h>
#define int long long 
using namespace std;

signed main()
{

	cin.tie(0);
	cout.tie(0); 
	int T;
	cin>>T;
	while(T--)
	{
		string s;
		cin>>s;
		s = "=" +s;
		int cnt0{},cnt1{};
		for(int i{1};i<s.length();i++)
		{
			if(s[i] == '0') cnt0++;
			if(s[i] == '1') cnt1++;
		}
		//if(cnt0 == cnt1) cout<<0<<"\n";
		
		{
			//cout<<"sn";
			//cout<<max(cnt0,cnt1)<<"\n";
			bool ok = false;
			for(int i{1};i<s.length();i++)
			{
				//cout<<cnt0<<" "<<cnt1<<" "<<i<<"\n";
				if(s[i] == '0') 
				{
					if(cnt1 == 0) 
					{
						//cout<<"sb\n";
						cout<<s.length()-i<<"\n";
						ok = true;
						break;
					}
					cnt1--;
				}
				if(s[i] == '1') 
				{
					if(cnt0 == 0)
					{
						//cout<<"sn\n";
						cout<<s.length()-i<<"\n";
						ok = true;
						break;
					}
					cnt0--;
				}
				
				
			}
			if(!ok) cout<<"0\n";
		}
		
	}
 } 
```

---

