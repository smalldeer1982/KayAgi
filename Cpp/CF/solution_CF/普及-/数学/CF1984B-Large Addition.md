# Large Addition

## 题目描述

A digit is large if it is between $ 5 $ and $ 9 $ , inclusive. A positive integer is large if all of its digits are large.

You are given an integer $ x $ . Can it be the sum of two large positive integers with the same number of digits?

## 说明/提示

In the first test case, we can have $ 658 + 679 = 1337 $ .

In the second test case, it can be shown that no numbers of equal length and only consisting of large digits can add to $ 200 $ .

In the third test case, we can have $ 696\,969 + 696\,969 = 1\,393\,938 $ .

In the fourth test case, we can have $ 777 + 657 = 1434 $ .

## 样例 #1

### 输入

```
11
1337
200
1393938
1434
98765432123456789
11111111111111111
420
1984
10
69
119```

### 输出

```
YES
NO
YES
YES
NO
YES
NO
YES
YES
NO
NO```

# 题解

## 作者：xhhhh36 (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF1984B)
# 题意
共有 $T$ 组数据。每组数据给定一个数，询问它能否表示成两个 large 数的和，如果能输出 YES，否则输出 NO。其中一个数为 large 数的条件是这个数的各个数位都由数字 $5$ 到 $9$ 组成。
# 思路
可以发现两个 large 数相加每一位都一定会出现进位，所以如果所以一个数能表示成两个 large 数相加，这个数的最高位必须为 $1$（上一位的进位），最后一位不能为 $9$（最小为 $0$，最大为 $8$），中间的每一位都不能为 $0$（因为有上一位的进位）。那么这题就做完了。
# AC code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int x;
void work(){
	cin>>x;
	if (x%10==9){
		cout<<"NO"<<endl;
		return ;
	}x/=10;
	while (x>10){
		if (x%10==0) {
			cout<<"NO"<<endl;
			return ;
		}
		x/=10;
	}
	if (x!=1) cout<<"NO"<<endl;
	else cout<<"YES"<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	int T;cin>>T;
	while (T--) work();
	return 0;
}
```

---

## 作者：cute_overmind (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1984B)

食用注意，本文偏向于证明结论，代码请移步。
### 题目大意
定义：一个数的数位上的数如果介于 $5$ 到 $9$，且每个数位上的数够满足这个条件，那么称这个数为大数。

给定你 $t$ 个数，问在这 $t$ 个数中有哪些数可以分解为两个大数相加。如果可以输出 `yes`，反之输出 `no`。

### 题目分析
考虑从高位进行遍历。

经观察数据样例发现，若给出的数最高位不为 $1$，那么可以直接输出。

[试证明提出结论。](https://www.luogu.com.cn/paste/gym8v91t)

接下来思考在中间部分的数位应该如何处理。

在刚才的证明结论发现，如果这个数可以被分解为两个大数，那么中间的每一个数位应该会有前面的一个进位，那么就应满足：
$$1\le x \le 9$$
而个位相对特殊，因为没有前面的进位，所以条件应该是：
$$0\le x \le 8$$

所以接下来开始遍历即可。

---

## 作者：zhanglh (赞：2)

### Description

给定一个数，查询这个数是否可以拆成两个位数相同，且每位都满足 $\text{large}$ 的数之和。

### Solution

对于给定的数 $n$，拆开每位来考虑。

根据定义，每一位数都至少为 $5$，因此每两位数相加都必然会进位。两个加数的位数相同，所以和会大一位。因此 $n$ 的最高位必然是 $1$。

中间除了个位的每一位，等于两个 $5$ 到 $9$ 的数之和，再加上进位的 $1$，范围就是 $1$ 到 $9$。而个位不会加 $1$，范围自然是 $0$ 到 $8$。

```
#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

ll n;

inline void solve() {
    scanf("%lld", &n);
    ll x;
    bool flag = true;
    for (int i = 1; ; i ++ ) {
        if (!n) {
            if (x != 1) flag = false;
            break;
        }
        x = n % 10;
        n /= 10;
        if (i == 1 && x == 9) {
            flag = false;
            break;
        }
        if (i > 1 && x == 0) {
            flag = false;
            break;
        }
    }
    if (flag) puts("YES");
    else puts("NO");
}

int main() {
    int T; scanf("%d", &T);
    while (T -- ) solve();
    return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
显然，两个 $>5,\le9$ 的数相加一定会进位，且仅不可能是 $9$ 结尾。所以，我们只要每次枚举最后一位，模拟进位的逆操作判断是否有个位为 $9$ 的时候即可。此外，如果当前数 $<0$ 了不合法。

[Code](https://codeforces.com/problemset/submission/1984/264880847)。

---

## 作者：Just_A_Sentence (赞：1)

简单模拟题。

从最低位开始向最高位运算，由于两个加数都要在 $5$ 到 $9$ 之间，所以和肯定在 $10$ 至 $18$ 之间，一位一位判断即可。

代码思路就是每次操作先除以 $10$（去掉最低位），然后减去 $1$（退位），在操作时判断末位是否为 $9$，如果是就退出并输出 `NO`（和不可能是 $9$ 或 $19$）。

附代码：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		long long n;
		scanf("%lld",&n);
		while(n>0){
			if(n%10==9){//末位在任何时刻都不可能是 9。
				printf("NO\n");
				break;
			}
			if(n>=100) n=n/10-1;//还剩超过两位时正常退位。
			else if(n>=10&&n<=18||n==0){//只剩两位时判断。
				printf("YES\n");
				break;
			}
			else{
				printf("NO\n");
				break;
			}
		}
	}
	return 0;
}
~~~

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1984B)
### 思路
任意两个仅由 $5$ 到 $9$ 组成的数字一定会进位，例如 $555+555=1110$，所以满足条件的数第一位必为 $1$，而且满足条件的数最后一位不会是 $9$，因为任意两个 $5$ 到 $9$ 中的数字相加的和不会等于 $9$ 或者 $19$，并且由于 $5$ 到 $9$ 中的两个数字加起来一定会进位，而每一位上的加和又不可能是 $9$，所以这个数字中间的数位也不能为 $0$。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    for (int i=0;i<t;i++)
    {
        string s;
        cin>>s;
        int q=0;
        int c=s.length();
        for (int j=0;j<c;j++)
        {
            if (j==0&&s[j]!='1')
            {
                cout<<"No"<<endl;
                q=1;
                break;
            }
            else
            {
                if (j==c-1&&s[c-1]=='9')
                {
                    cout<<"No"<<endl;
                    q=1;
                    break;
                }
                if (j!=c-1&&s[j]=='0')
                {
                    cout<<"No"<<endl;
                    q=1;
                    break;
                }
            }
        }
        if (q==0)
        {
            cout<<"Yes"<<endl;
        }
    }
}
```

---

## 作者：wloving (赞：0)

## 题目分析

阅读题面可知，题目需要我们去判断一个整数 $x$ 是否能被两个相同位数的大数相加所表达。对于大数的定义，题面中描述是：数字的每一位都是 $5\sim 9$ 的数字。

对于 $5\sim 9$ 的数字，相加能得到的最小值为 $10$，而对于十进制数字来说，每一位的最大值为 $9$ 所以 $x$ 一定会被拆分为两个更小的位数的数字。且对于十进制加法来说，两数相加的进位最多为 $1$。所以数字 $x$ 的最高位一定为 $1$。其它位一定无法独立地被分解为两个大数相加，必然是需要从前面借一位。

那么，在计算时，就需要考虑从前面借一位，以及留一位借给后面。对于 $5\sim 9$ 的数字，两两相加的数值范围是 $10\sim 18$。我们每一位的组成范围考虑借位之后就是在 $10\sim 18$ 中。

结合样例图示理解一下过程：

![](https://cdn.luogu.com.cn/upload/image_hosting/73w0xzyk.png)

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
bool chk(string s) {
  int len = s.length();
  int num = 1;
  if (s[0] > '1') return 0;//首位大于1的一定无法分解为两个大数
  for (int i = 1; i < len; i++) {//从高位开始遍历
    num = 10 + s[i] - '0';//单独一位无法分解为两个大数，需要从前面借一位
    if (i < len - 1) {//不是最高位时，考虑留一位借给后一位
      if (num - 1 < 10 || num - 1 > 18) return 0;//两个大数相加的范围是10~18
      num = 1;
    } else {//最后一位不用考虑留一位
      if (num < 10 || num > 18) return 0;
    }
  }
  return 1;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  string num;
  cin >> t;
  while (t--) {
    cin >> num;
    if (chk(num)) {//判断num是否能分解为两个大数相加
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
```

---

## 作者：RainCQwQ (赞：0)

# CF1984B Solution
## 思路分析
首先看到样例，显而易见的，发现所有开头不是 $1$ 的全部都被输出 `NO`，明显不是巧合，是因为只要是两个大于 $5$ 的数相加一定是会进位的，而题目中说：

> Can it be the sum of two large positive integers with the same number of digits?
> 
> 它可以是两个具有相同位数的 large 正整数的总和吗？

因而得到这个整数的第一位一定是 $1$。

再来看个位，最小应该是 $5 + 5 = 10$（取 $0$ 进 $1$），最大则是 $9 + 9 = 18$（取 $8$ 进 $1$），得个位在 $0 \sim 8$ 之间。

对于剩余的位数，与个位相同，但要加上进位的 $1$，得剩余位在 $1 \sim 9$ 之间。

## Code
```cpp
#include <iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        if(s[0]!='1'||s[s.size()-1]=='9') 
        {
            cout<<"NO"<<endl;
            continue;
        }
        for(int i=1;i<s.size()-1;i++) if(s[i]=='0') goto no;
        cout<<"YES"<<endl;
        continue;
        no:
        cout<<"NO"<<endl;
    }
    return 0;
}
```

---

## 作者：ttq012 (赞：0)

### B

考虑从低位到高位模拟过程。如果在枚举到某一位的值的时候，值为 $9$，那么因为 $9$ 和 $19$ 均不可以被分成两个 $5\sim 9$ 的数的和，所以必然无解。否则必然可以分成两个 $5\sim 9$ 的数的和。设这个位置的值为 $x$，那么会让答案减去 $10+x$。如果减到一个位置的时候，答案不够减，那么就必然存在无解。如果枚举到第一位的时候剩下的值仍然不为 $0$，那么无解（没有地方可以退位），否则有解。

时间复杂度为 $O(|n|)$，其中 $|n|$ 重定义为 $n$ 在 $10$ 进制下的位数。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000100;
char s[N];
int a[N];
signed main() {
    int T;
    cin>>T;
    while(T--){
        scanf("%s",s+1);
        bool ok=true;
        int n=strlen(s+1);
        for(int i=1;i<=n;i++)a[i]=s[i]^48;
        a[0]=a[n+1]=a[n+2]=a[n+3]=a[n+4]=a[n+5]=0;
        for(int i=n;i>1;i--){
            if(a[i]==9){ok=false;break;}
            a[i-1]--;
            for(int j=i-1;j;j--){
                if(a[j]>=0)break;
                a[j-1]--,a[j]+=10;
            }
            if(a[0]<0){ok=false;break;}
        }
        cout<<((ok&&!a[1])?"YES":"NO")<<'\n';
    }
}
```

---

## 作者：ztksc07 (赞：0)

# 题解：CF1984B Large Addition

#### 前置知识：加法竖式。

## 题目大意

定义“大数”是每一位都介于 $5$ 与 $9$ 之间的数。给定一个正整数 $x$，求这个数能否表示为两个位数相同的“大数”的和。

## 解题思路

我们用加法竖式的思路解这道题。我们先取两个位数相同且每位最小的“大数”，如 $555$，并用加法竖式加起来：

![](https://cdn.luogu.com.cn/upload/image_hosting/01bl8ryt.png)

因为我们取的是最小的情况，所以结果的每一位都只可能比 $1110$ 的每一位要大，于是结论就出来了：$x$ 的末位大于 $0$，剩余位大于 $1$。

然而结论真的是这样吗？我们再用数学方法验证一下。

末位的情况：末位由于没有进位，所以大于等于 $5+5$ 的末位 $0$，小于等于 $9+9$ 的末位 $8$。

中间位的情况：中间位必须有进位，所以大于等于 $5+5$ 的末位 $0$ 再加 $1$，小于等于 $9+9$ 的末位 $8$ 再加 $1$，即大于等于 $1$ 小于等于 $9$。

首位的情况：首位只有进位，所以必须等于 $1$。

理清思路后，代码就很好写了。把 $x$ 每一位分离，按照上述规则分别判断即可。

时间复杂度 $O(t \times \log_{10} x)$，稳过。

## 代码实现

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,cnt;
long long tmp,x,w;
bool flag;
int main(){
	scanf("%d",&t);
	while(t--){//多组数据 
		scanf("%lld",&x);
		flag=cnt=0;
		tmp=x;
		while(tmp){//数位分离 
			cnt++;
			w=tmp%10;
			if(cnt==1){//分类讨论 
				if(!(0<=w&&w<=8)){
					printf("NO\n");
					flag=1;
					break;
				}
			}else if(w==tmp){
				if(w!=1){
					printf("NO\n");
					flag=1;
					break;
				}
			}else{
				if(!(1<=w&&w<=9)){
					printf("NO\n");
					flag=1;
					break;
				}
			}
			tmp/=10;
		}
		if(!flag) printf("YES\n");
	}
	return 0;
} 
```

## 注意事项

一定记得开 `long long`。

---

## 作者：Lu_xZ (赞：0)

### B

如果首位不等于 $1$，无解。

否则可以推出两个数 $a + b = x$ 每一位的和，且这个和一定属于 $[10, 18]$，否则无解。

例如：$1393938$。

+ $a_0 + b_0 = 18$。
+ $a_1 + b_1 = 13 - 1$（一定有进位）。
+ $a_2 + b_2 = 19 - 1$。

以此类推。

```cpp
void solve() {
	ll x; cin >> x;
	auto s = to_string(x);
	int n = s.length();
	if(s[0] != '1') {
		cout << "NO\n";
		return;
	}
	for(int i = 0; i <= n - 2; ++ i) {
		int x = 10 + s[i + 1] - '0';
		if(i != n - 2) -- x;
		if(x < 10 || x > 18) {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
}
```

---

## 作者：roumeideclown (赞：0)

## 题意简述

若一个数字在 $5$ 与 $9$ 之间，则我们称这个数字是“大”的。当一个正整数所有数位上的数字都是“大”的时，这个正整数也是“大”的。

给定一个正整数 $x$（$10 \le x \le 10^{18}$），请判断它能否由两个“大”的且长度相等的正整数相加得到。

## 解法分析

对于 $x$，不妨对每个数位分别考察。

假设 $ x$ 满足题意。

对于首位，由于两加数长度相等，则 $x$ 的首位必由两加数首位（$5$ 到 $9$）相加进位得到，因此首位必为 $1$。

对于第二位至倒数第二位，由于两加数都是“大”的，即每一位数都在 $5$ 到 $9$ 之间，因此每一位上的加法都有进位，所以 $x$ 的第二位至倒数第二位均不可能为 $0$，其余数字都是可能的。

对于末位，显然不可能为 $9$。

## 代码实现

```cpp
#include<bits/stdc++.h>
//#pragma G++ optimize(2,3,"Ofast")
using namespace std;
typedef long long ll;
void solve() {
	ll x;
	scanf("%lld",&x); //输入
	x=x-x%10+(x%10+1)%10; //将最后一位加上 1 再模 10，即 1 变 2,2 变 3，…，8 变 9,9 变 0
  //这样处理有一个好处，由于最后一位不可能为 9，中间的数位不可能为 0，
  //所以将这样处理后中间数位和最后一位可以一起判断
  //当然将中间数位和最后一位分开处理也是可以的
	while(x>9) { 
		if(x%10==0) { //若为 0 则不行
			printf("NO\n");
			return;
		}
		x/=10; //从后往前遍历数位
	}
	if(x==1) printf("YES\n"); //首位为 1 可以，否则不行
	else printf("NO\n");
}
int main() {
//  ios::sync_with_stdio(false);
//  cin.tie(0),cout.tie(0);
	int t;
	scanf("%d",&t);
	while(t--) solve(); //多组数据
	return 0;
}
```

---

