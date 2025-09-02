# Reverse Sort

## 题目描述

题目共给出 $t(1 \le t \le 1000)$ 组数据，每组数据包含一个正整数 $n(1 \le n \le 1000)$ 和一个长度为 $n$ 的 $01$ 串 $s$， 现在你需要在 $s$ 中选出一个子序列，将这个子序列中的字符翻转（如字符串 $10100$， 选出子序列 $1100$， 翻转得到 $0011$， 放回原串中得到 $00011$），使得翻转后的字符串字典序最小。

## 样例 #1

### 输入

```
3
7
0011111
5
10100
6
001000```

### 输出

```
0
1
4 1 3 4 5 
1
3 3 5 6```

# 题解

## 作者：Jerrlee✅ (赞：5)

## 题意
题意：给定 `01` 串，你可以进行以下操作：

- 翻转其中一个子序列。

用最少操作次数，使所有 $0$ 排在 $1$ 的前面。
## 思路
任何二进制字符串 $s$ 最多 $1$ 次操作即可成字典序！

设 $s$ 中 $0$ 的数量为 `cnt`，$s$ 中 $1$ 的数量为 `cnt1`。

最终排序好的字符串的第一个 `cnt` 位置将为 $0$，其余 `cnt1` 位置将为 $1$（它是按非降序排序的）。

关键观察：对于位于 $s$ 的第一个 `cnt1` 位置的每一个 $1$，都有一个位于 $s$ 的最后一个 `cnt1` 位置的 $0$。

如果字符串尚未排序，则在一个操作中选择由 $s$ 的第一个 `cnt` 位置中的所有 $1$ 以及 $s$ 的最后一个 `cnt1` 位置中的所有 $0$ 组成的子序列。可以看出，因为 $0$ 和 $1$ 的数量相等，所以解法正确。
## 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define sf sizeof
#define con continue
int a[1001];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,c=0,f=1;
        string s;
        cin>>n>>s;
        memset(a,0,sf a);
        for(int i=0;i<n;i++){
            if(s[i]=='1') c++,a[i]=1;
            if(i>0&&s[i]<s[i-1]) f=0;
        }
        if(f){cout<<0<<endl;con;}
        int h=0;
        for(int i=n-c;i<n;i++) if(s[i]=='0') h+=2;
        cout<<1<<endl<<h;
        for(int i=0;i<n;i++){
            if(i<n-c&&s[i]=='1') cout<<" "<<i+1;
            if(i>n-c-1&&s[i]=='0') cout<<" "<<i+1;
        }
        cout<<endl;
    }
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/62606884)

[AC记录（CF）](https://codeforces.com/contest/1605/submission/135145357)

---

## 作者：wzy2021 (赞：1)

我们来看一下这道题：

其实是要把 $1$ 都放在 后面，$0$ 都放在前面。

具体一点，假设 $1$ 的个数为 $k$ 个，字符串长度为 $len$，

那么我们要将 $1$ 放在 $len - k + 1$ 到 $len$，将 $0$ 放在 $1$ 到 $len - k$，分两种情况：

1. $len - k + 1$ 到 $len$ 全是 $1$，则答案为 $0$。
1. 不全为 $1$，即有 $0$，假定有 $m$ 个 $0$ 在 $len - k + 1$ 到 $len$，显然在 $1$ 到 $len - k$ 也有 $m$ 个 $1$，那我们把这 $2m$ 个字符反转，则会变成后面 $m$ 个变成 $1$，前面 $m$ 个变成 $0$，即总体的$len - k + 1$ 到 $len$ 就全是 $1$ 了，$1$ 到 $len - k$ 就全是 $0$ 了，满足条件！

代码时间到：
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
 
const int maxn = 1010;
int num1[maxn], num2[maxn], ans1[maxn], ans2[maxn];
// num1[i]表示从前往后第i个1所在的位置，num2[i]表示从后往前第i个0所在的位置
char c[maxn];
 
int main() {
    int T; scanf ("%d", &T);
    while (T --) {
        int n; scanf ("%d%s", &n, c + 1);
        int c1 = 0, c2 = 0;
        for (int i = 1; i <= n; ++i) if (c[i] == '1') num1[++c1] = i;
        for (int i = n; i >= 1; --i) if (c[i] == '0') num2[++c2] = i;
        int cnt = 0;
        for (int i = 1; i <= min (c1, c2); ++i) {
            if (num1[i] < num2[i]) {
                ans1[++cnt] = num1[i]; ans2[cnt] = num2[i];
            } else break;
        }
        if (cnt == 0) {
            printf ("0\n"); 这个 0 记得别忘记特判哦！
        } else {
            printf ("1\n%d ", 2 * cnt);
            for (int i = 1; i <= cnt; ++i) printf ("%d ", ans1[i]);
            for (int i = cnt; i >= 1; --i) printf ("%d ", ans2[i]); // 这里记得要倒叙输出！
            printf ("\n");
        }
    }
    return 0;
}
```


---

## 作者：Jur_Cai (赞：1)

### 题意
给你一个 01 序列，每次可以选择一个不上升的子序列进行翻转，求最少操作几次能使原序列变成不下降序列，并输出方案。
### 分析
由于是 01 串，序列最后情况就是前面全是 0，后面全是 1。那我们就只需要后半段中的 0 和前半段中的 1 交换位置即可，很显然就只需要一次操作。实现的时候就记一下全部 1 的位置，在处理一下哪些 1 是不用换位置的，本人实现方法可能有些麻烦 QwQ。

```
#include<bits/stdc++.h>
using namespace std;
char s[1005];
int pos1[1005],pos0[1005];
int main() {
	int T,n;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		scanf("%s",s+1);
		int cnt1=0;
		for(int i=1; i<=n; i++)
			if(s[i]=='1') pos1[++cnt1]=i;//默认所有的 1 都需要交换位置
		int cnt0=0;
		for(int i=n; i>=1; i--) {
			if(cnt1==cnt0) break;
			if(s[i]=='0') pos0[++cnt0]=i;//记录可以交换的位置，即后半段中 0 的位置
			else cnt1--;//本来就在后半段的 1 就不用交换了
		}
		if(cnt1) {
			cout<<1<<'\n';
			cout<<cnt1+cnt0<<" ";
			for(int i=1; i<=cnt1; i++) cout<<pos1[i]<<" ";
			for(int i=cnt0; i>=1; i--) cout<<pos0[i]<<" ";
			putchar('\n');
		} else cout<<0<<'\n';
	}
}

```

---

## 作者：feicheng (赞：1)

### Description

给定一个 $01$ 序列 $a$，长度为 $n$，每次你可以任选 $k$ 个元素，记他们的下标为 $i_1,i_2,\cdots i_k$（默认 $i$ 是递增的），要求 $a_{i_1}\ge a_{i_2}\ge\cdots a_{i_k}$，此时你可以将 $(a_{i_1},a_{i_k}),(a_{i_2},a_{i_{k-1}}),\cdots,(a_{i_{\left\lfloor k/2\right\rfloor}},a_{i_{\left\lfloor k/2\right\rfloor+1}})$ 交换，问最少多少次可以将序列排成升序，并且要求输出序列。

多测。

**数据范围**：

$1\le T,n\le 1000$

### Solution

结论题。。。

结论就是：答案不超过 $1$。

因为考虑每个 $1$，找距离他最远的还没有被选的 $0$，如果能找到就说明他们两个会进行交换，如果选不到说明这个 $1$ 之后已经没有 $0$ 了，也就是说已经升序了，所以最多一次就会排完。

如果 $0$ 比 $1$ 多，那么在 $1$ 被找完的时候，前面的 $1$ 一定已经被交换了，所以也是同理的。

操作序列就是每次找到的 $0$ 和 $1$ 的位置。

### Code

```cpp
int n, t;
bool a[N], vis[N];
char s[N];
 
inline void solve() {
	cin >> n >> (s + 1);
	for (int i = 1; i <= n; ++i) {
		a[i] = vis[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		a[i] = (s[i] == '1');
	}
	std::vector<int> op;
	for (int i = 1; i <= n; ++i) {
		if (a[i]== 1) {
			for (int j = n; j >= i + 1; --j) {
				if (a[j] == 0 && !vis[j]) {
					op.push_back(i);
					op.push_back(j);
					vis[j] = 1;
					break;
				}
			}
		}
	}
	if (!op.size()) {
		cout << 0 << '\n';
		return;
	}
	cout << 1 << '\n';
	cout << op.size() << " ";
	std::sort(op.begin(), op.end());
	for (auto it : op) {
		cout << it << " ";
	}
	cout << '\n';
}
```


---

## 作者：Lan_yan (赞：0)

不要管样例的第三个数据，它是吓唬你的。

## 题目

给你一个只有字符 $0$ 和字符 $1$ 的字符串，可以选定一个子串**在原有的位置**翻转。

问最少要多少步这样的操作使该字符串所有的 $0$ 在前面，所有的 $1$ 在后面。

但是，输出中要将每一步翻转的子串下标输出出来。

## 思考

设一个字符串 $s$。

设该字符串中字符 $0$ 的个数为 $a$，字符 $1$ 的个数为 $b$。

那么，我们要的新字符串前 $a$ 个字符一定为 $0$，后 $b$ 个字符一定为 $1$。

拿第二组样例来说，$s$ 字符串为 `10100`，期望最后为 `00011`。

其中，$a = 3$，$b = 2$。

在 $s$ 的前 $a$ 个本该为 $0$ 的字符中，有 $s_1$ 和 $s_3$ 为 $1$。

那么，在 $s$ 的后 $b$ 个本该为 $1$ 的字符中，一定**有且只有** $2$ 个字符为 $0$。

那么，我们只要把所有字符与期望字符不同的挑出来，因为在前 $a$ 个字符中只挑字符 $0$，后 $b$ 个字符中只挑字符 $1$。

又因为 $0$ 和 $1$ 一一对应，所以选出的新字符串格式一定为前面 $x$ 个 $0$，后面 $x$ 个 $1$。

所以，我们只要统计在 $0$ 的区域中 $1$ 的数量，在 $1$ 的区域中 $0$ 的数量并统计出它们的下标即可。

## 代码

```cpp
#include<bits/stdc++.h>//万能头百看不厌
using namespace std;
int t,n;
char s[1005];//原字符串s
int main()
{
	int i;
	scanf("%d",&t);
	while(t--)
	{
		int b=0,j=0;
		scanf("%d",&n);
		cin>>s;
		for(i=0;i<n;i++)if(s[i]=='1')b++;//有b个1，有a=n-b个0
		for(i=n-b;i<n;i++)
		{
			if(s[i]=='1')j++;
		}//在1的区域中1的数量
		if(b==j)//已经是期望字符串了
		{
			printf("0\n");continue;
		}
		printf("1\n%d",(b-j)*2);//因为有落单的0就会有落单的1，所以要乘2
		for(i=0;i<n-b;i++)//0的区域中1的下标
		{
			if(s[i]=='1')printf(" %d",i+1);
		}
		for(i=n-b;i<n;i++)//1的区域中0的下标
		{
			if(s[i]=='0')printf(" %d",i+1);
		}
		printf("\n");
	}
	return 0;
}
```

完结撒花！

---

## 作者：GoodLuckCat (赞：0)

首先，这道题我们可以想到在过程中，这个字符串的 $0$ 的个数与 $1$ 的个数不变。所以，目标字符串是唯一的。我们可以先构造出这个目标字符串，然后看和原来字符串哪里的位置不同，这个位置就是需要翻转的。但是因为我们输入的时候用的是字符串，默认从 $0$ 开始编号下标，但是仔细观察样例，是要从 $1$ 的下标开始计算的，所以在输出时要加上 $1$ 才能对上。~~就因为这个我被坑了好久。~~

在构造目标字符串时因为 $0$ 和 $1$ 的个数不变，所以可以先统计 $0$ 和 $1$ 分别有几个，再拼在一起。

AC 代码如下（码风正常）：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,n0=0,n1=1,s=0;
        string s1,s2="";
        cin>>n>>s1;
        for(char i:s1)
        {
            if(i=='0')n0++;
            else n1++;
        }
        for(int i=1;i<=n0;i++)s2+='0';
        for(int i=1;i< n1;i++)s2+='1';
        if(s1==s2)cout<<"0\n";
        else
        {
            cout<<"1\n";
            for(int i=0;i<n;i++)if(s1[i]!=s2[i])s++;
            cout<<s<<' ';
            for(int i=0;i<n;i++)if(s1[i]!=s2[i])cout<<i+1<<' ';
        }
    }
    return 0;
}
```

---

## 作者：Rookie_t (赞：0)

这是一道结论题。

首先，我们可以找出 $s$ 中 $0$ 的数量和 $s$ 中 $1$ 的数量。

我们设有 $sum1$ 个 $0$ 和 $sum2$ 个 $1$。

对于最后的答案，前 $sum1$ 位一定是 $0$，后面每位都是 $1$。

接下来我们可以遍历一遍 $s$ 根据规则判断需要需要交换的点的个数。

交换的次数肯定是 $1$ 次。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll T,n;
string s;
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		cin>>n>>s;
		bool b = 0;
		ll sum1 = 0,sum2 = 0;
		for(int i = 0;i<n;i++){//求sum1 
			if(s[i] == '0'){
				sum1++;
			}
		}
		for(int i = 0;i<sum1;i++){
			if(s[i] == '1'){
				b = 1;
				break;
			}
		}
		if(!b){
			cout<<0<<endl;
			continue;
		}///求sum2
		sum2 = 0; 
		for(int i = 0;i<n;i++){
			if(s[i] == '1' && i<sum1){
				sum2++;
			}
			if(s[i] == '0' && i>=sum1){
				sum2++;
			}
		}		
		//输出 
		cout<<1<<endl<<sum2;
		for(int i = 0;i<sum1;i++){
			if(s[i] == '1'){
				cout<<" "<<i+1;
			}
		}
		for(int i = sum1;i<n;i++){
			if(s[i] == '0'){
				cout<<" "<<i+1;
			}
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：wei2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1605B)

## 思路：
分类讨论。

第一种情况，操作次数为 $0$，为什么会是 $0$ 呢？这显而易见它本身字典序就最小。如何判定字符串字典序本身就最小呢？首先我们知道这是 `01` 串，可以知道 $0$ 全部在前便说明原本字典序就最小，遍历计算零的数量，然后发现没有 $1$ 的话，也就是升序情况，就可得出这种情况。

第二种情况，操作次数不为 $0$，仔细观察可以发现操作次数一定为 $1$ ，因为我们知道 $0$ 和 $1$ 的个数是永远不变，假设有 `len0` 个 $0$，那么也就要把 $1$ 到 `len0` 中的一和 `len0` 到 $n$ 之间的零调换，遍历一遍输出即可。  

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		string s;
		int n,len0=0;
		bool ok=0;
		cin>>n>>s;
		for(int i=0;i<n;i++){
			if(s[i]=='0'){
				len0++;
			}
		}
		for(int i=0;i<len0;i++){
			if(s[i]=='1'){
				ok=1;
			}
		}
		if(!ok){
			cout<<0<<endl;
			continue;
		}
		cout<<1<<endl;
		int len1=0;
		for(int i=0;i<len0;i++){
			if(s[i]=='1'){
				len1++;
			}
		}
		for(int i=len0;i<n;i++){
			if(s[i]=='0'){
				len1++;
			}
		}
		cout<<len1<<" ";
		for(int i=0;i<len0;i++){
			if(s[i]=='1'){
				cout<<i+1<<" ";
			}
		}
		for(int i=len0;i<n;i++){
			if(s[i]=='0'){
				cout<<i+1<<" ";
			}
		}
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：YangXiaopei (赞：0)

注意：本题开了 Special Judge。

## Solution:

很简单的一道题目。

可以发现，不管怎么翻转，$1$ 和 $0$ 的个数都是不变的，那我们就可以锁定最后的结果是什么。

我们设一共有 $cnt1$ 个 $0$，那么就有 $n - cnt1$ 个 $1$，则前 $cnt1$ 个是 $0$，后 $n - cnt1$ 个是 $1$。

那我们接下来只要扫一遍 $s$，只要 $s_i$ 与预定的值不一样，那这个点就是要交换的。

那就下来就是求要交换几次。有个结论，必然是 $1$ 次。

我们设前 $cnt1$ 中有 $m$ 个 $1$，那后 $n - cnt1$ 个中就必然有 $m$ 个 $0$。

那我们只需把这 $2m$ 个数交换即可。

注意判 $0$。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
string s;
int main(){
	cin >> t;
	while(t--){
		cin >> n >> s;
		int f = 0, cnt1 = 0, cnt2 = 0;
		for(int i = 0; i < n; i++){
			if(s[i] == '0'){
				cnt1++;
			}
		}
		for(int i = 0; i < cnt1; i++){
			if(s[i] == '1'){
				f = 1;
				break;
			}
		}
		if(!f){
			cout << 0 << "\n";
			continue;
		}
		cnt2 = 0;
		for(int i = 0; i < cnt1; i++){
			if(s[i] == '1'){
				cnt2++;
			}
		}
		for(int i = cnt1; i < n; i++){
			if(s[i] == '0'){
				cnt2++;
			}
		}
		cout << 1 << "\n";
		cout << cnt2;
		for(int i = 0; i < cnt1; i++){
			if(s[i] == '1'){
				cout << " " << i + 1;
			}
		}
		for(int i = cnt1; i < n; i++){
			if(s[i] == '0'){
				cout << " " << i + 1;
			}
		}
		cout << "\n";
	}
	return 0;
} 
```

---

## 作者：shredded_beef_qwq (赞：0)

## 具体思路
不管是怎样的数据，我们都只需要一次操作，也就是只需要一次提取的操作，我们只需要将后面的所有 $0$ 和前面的 $1$ 交换,把 $0$ 全部放在前面。如果所有的 $0$ 全部都在前面。那就输出 $0$。我们可以枚举数组将后面的所有 $0$ 都提取出来，然后在记录后面有多少个 $1$ 并将它们也提取出来，然后将 $1$ 的总个数减去后面记录的 $1$ 的个数再加上后面 $0$ 的个数就是总操作个数了，最后我们在输出提取出来的 $1$ 和 $0$ 就可以了。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int f0[1010],f1[1010];
int main(){
	int t;
	cin>>t;
	int n;
	char s[2010];
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>s[i];
		int cnt0=0,cnt1=0;
		for(int i=1;i<=n;i++)
			if(s[i]=='1') f1[++cnt1]=i;
		for(int i=n;i>=1;i--){
			if(cnt0==cnt1) break;
			if(s[i]=='0') f0[++cnt0]=i;
			else cnt1--;
		}	
		if(cnt1==0) cout<<"0"<<endl;
		else{
			cout<<"1"<<endl<<cnt1+cnt0<<" ";
			for(int i=1;i<=cnt1;i++) cout<<f1[i]<<" ";
			for(int i=cnt0;i>=1;i--) cout<<f0[i]<<" ";
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：ImmortalWatcher (赞：0)

发现每次发现一个前面的 $1$ 就把它跟后面的 $0$ 翻转即可。

所以只用一次操作就可以了。

实现考虑用双指针，每次找到一个前面的 $1$ 和后面的 $0$，然后加入答案。

**code**

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[1010],ans[1010],cnt;
char s[1010];
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		bool bj=false;
		scanf("%s",s+1);
		for (int i=1;i<=n;i++)
			a[i]=s[i]-'0';
		for (int i=1;i<n;i++)
			if (a[i]==1&&a[i+1]==0)
			{
				bj=true;
				break;
			}
		if (!bj)
		{
			puts("0");
			continue;
		}
		int i=1,j=n;
		cnt=0;
		while (i<j)
		{
			while (i<j&&a[i]!=1) i++;
			while (i<j&&a[j]!=0) j--;
			if (i>=j) break;
			ans[++cnt]=i;ans[++cnt]=j;
			i++;j--;
		}
		puts("1");
		sort(ans+1,ans+1+cnt);
		printf("%d ",cnt);
		for (int i=1;i<=cnt;i++)
			printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}
```


---

## 作者：yangzd (赞：0)

# 题目大意：

给定01串，你可以进行以下操作：

+ 选取其中一个子序列，**翻转**后放回原位

给出最少操作次数和具体操作，使得所有 $0$ 排在 $1$ 的前面。

# 分析：

总可以通过一次操作解决。

设字符串的某位置后有 $x$ 个 $0$，前面恰好有 $x$ 个 $1$ ，选中这些 $0$ 和 $1$ ，并进行翻转，恰好前面的所有 $1$ 和后面的所有 $0$ 对调，满足要求。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	ios::sync_with_stdio(0);
	
	long long t;
	
	cin >> t;
	
	while (t--)
	{ 
		long long n;
		
		cin >> n;
		
		char c[n+1];
		
		cin >> c;
		
		vector<long long> v;
		
		for(long long i=0; i<n; i++)
		{
		    if(count(c,c+i,'1')==0)
				continue;
				
		    if(count(c,c+i,'1')==count(c+i,c+n,'0'))
		    {
		        cout << "1" << endl << 2*count(c,c+i,'1') << " ";
		        
		        for(long long j=0; j<i; j++)
					if(c[j]=='1')
						cout << j+1 << " ";
						
		        for(long long j=i; j<n; j++)
					if(c[j]=='0')
						cout << j+1 << " ";
						
		        cout << endl;
		        
		        continue;
		    }
		}
		
		cout << "0" << endl;
	} 
	
	return 0;
}
```

---

